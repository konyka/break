# Editor asset hot reload

Status: delivered (2026-10-26, branch `sdd/editor-hot-reload`). Stage 4 subproject 4, the missing hot-reload half of the asset browser. This is an editor integration of the existing Runtime Core coordinator, not a second reload/thread architecture. Implementation: `engine/apps/editor/editor_hot_reload.{h,c}`.

## 1. Scope and non-goals

Delivered scope:
- Watch the current `.bscn` scene file. External changes are read by a Runtime Core worker and committed on the editor shell thread through `break_runtime_reload_commit_owner`.
- A valid external scene replaces the document using the existing REPLACE/world-swap semantics; selection is reconciled and the whole shell refreshes.
- A malformed, unreadable, or failed load leaves the current document, names, and undo history intact (`FAILED_KEEP_OLD`).
- A document with unsaved local edits (dirty and command history) is never overwritten by an external event. The event is reported and skipped.
- The editor's own saves do not reload: the hash of the saved bytes is the baseline, a later event whose bytes hash the same is skipped, and a reload that was staged before a save is dropped as stale.
- The asset browser's current directory listing refreshes while the editor runs: at most once per second the shell re-lists the one directory the panel shows and repaints only if the listing changed.
- Asset-browser scene loads and the CLI scene path share the same `scene_path` and watcher.

NOT delivered: shader/texture hot reload inside the editor, VFS PAK enumeration, cross-device asset dependency graph, async GPU upload, render-scene/SCENE_NODES ownership, remote load/save, Windows/macOS runtime verification. `scene_load_binary` keeps its existing file-based behavior for other callers.

## 2. Ownership and data flow

The editor host owns `BreakEditorHotReload`; the shell borrows it and drives it once per `break_editor_shell_tick`, exactly like the remote session host. Destroying it detaches it from a live shell; destroying the shell first orphans it safely.

```text
shell tick: filewatch_poll (legacy single-file FileWatcher, mtime compare)
        -> callback only sets `pending`
shell tick: break_runtime_reload_request(scene basename)
Runtime Core worker: VFS read into owned staging bytes + BSCN magic check
        -> bounded commit queue
shell tick: break_runtime_reload_commit_owner -> commit hook:
        stale epoch? same hash as baseline? unsaved edits? -> skip
        else break_editor_doc_load_bytes(staged BSCN, scene_path)
        -> selection reconcile + shell refresh
shell tick: break_runtime_reload_poll consumes the terminal state
```

The coordinator's `notify_file_event`/`pump_events` seam is deliberately not used: requests it starts return no handle, so the host could never `poll` them and their table slots would never be released. The host issues `break_runtime_reload_request` itself, keeps the handle, and polls it every tick.

`FileWatcher` is only polled by the shell thread. The Runtime Core worker never touches the editor document, widgets, selection, Lua, or RHI. The commit hook receives borrowed staging bytes and does not retain them. The coordinator runs one worker with 4 request slots.

The VFS mount is the scene's parent directory; the coordinator path is the scene basename, so absolute paths and `..` never cross the VFS boundary. Watch paths are bounded by the existing `FILEWATCH_MAX_PATH` (256) / `VFS_MAX_PATH` (260) limits; an over-limit path disables watching with a visible console line instead of truncating (Ctrl+S still works, it has its own larger bound).

## 3. Loading and failure rules

`scene_load_binary_memory` is the memory form of the existing BSCN reader, with the file reader kept as a thin wrapper. `break_editor_doc_load_bytes` uses the same fresh-world staging and sidecar handling as `break_editor_doc_load`, but parses the exact coordinator staging bytes. The sidecar is read from the scene path at commit time; the BSCN is never re-read from disk by the commit hook.

- External valid BSCN: commit, clear stale selection through the existing selection sync, refresh the shell.
- External invalid BSCN or a commit failure: `FAILED_KEEP_OLD`; no doc mutation, log the failure.
- Unsaved local edits: if the document is dirty AND has command history, do not commit, keep the edits and history, and log that the external change was skipped. No silent conflict resolution. Neither signal alone is the criterion: a scene loaded without a sidecar is dirty only because its names were generated (no history), and after Ctrl+S the document is clean but keeps its undo history; both must still follow external edits. Undoing back to the saved state stays dirty (documented conservative doc behavior), so it is also kept.
- Internal save: after a successful Ctrl+S `break_editor_hot_reload_note_saved` bumps a local epoch and re-hashes the saved file as the baseline. A reload staged before the save is dropped as stale (`skipped_stale`); a later event whose bytes hash the same as the baseline is skipped (`skipped_same`); a real external edit has different bytes and is processed normally. This replaces the first draft's "suppress exactly one event" counter, which is wrong when the filesystem emits zero or two events for a save.
- Scene changes (CLI, asset browser): the browser loads through `editor_shell_load_scene`, which updates `scene_path` and the watcher only after the load succeeded; a failed load leaves the old scene, document and watcher intact.
- Shutdown: `break_runtime_reload_shutdown` runs before `break_editor_hot_reload_destroy`; worker completion cannot race shell/doc destruction. A timeout is logged and the coordinator is leaked instead of freed under a running worker.

## 4. Directory listing

Design change from the first draft, which used the recursive `FileWatch` directory watcher: that watcher walks and registers every subdirectory when it is created. Measured on this machine, `filewatch_create_dir` took about 3 s on the repository root and about 0.5 s on `engine/`, and the browser's default root is the process working directory. A multi-second stall at startup (and again on every root change) is not acceptable for a view that only ever shows one directory level, and the watcher's own queue is 32 events deep with a root-level "events lost" fallback, so it would not have been a reliable per-file signal anyway.

Instead the shell tick calls `editor_panel_assets_tick`, which at most once per second (injectable clock for tests) calls the bounded `break_editor_assets_refresh` on the model. Refresh re-lists only the current directory into the existing 4096-entry cache (no allocation, filter kept) and reports whether the visible listing, position, or truncation flag changed; the panel repaints only on change. If the current directory vanished the model walks up to the nearest ancestor that still lists; if the root itself vanished it becomes a coherent empty listing and refresh returns false. Directory-only changes never touch the document.

Cost is one `readdir` plus an in-memory sort of at most 4096 entries per second. The listing can be up to one second stale; no per-file delivery guarantee is claimed.

## 5. Tests and evidence

Unit (`test_editor_shell`, real temp directories, real VFS + Runtime Core worker + legacy file watcher, mtimes set explicitly because the watcher compares whole seconds):
- valid external edit replaces the document and outliner; creation of a missing scene file loads it;
- invalid external bytes keep the document and the undo history; unsaved local edits are preserved and counted;
- a scene without a sidecar (dirty only for generated names) still follows later external edits;
- own save is not reloaded (hash baseline) and does not erase undo; an external edit after a save still reloads, twice (rename-over-file does not break the watcher);
- a reload staged before a save is dropped as stale;
- asset-browser scene switch re-points the watcher and `scene_path`; the old scene stops being watched;
- over-long scene path disables watching without truncating; teardown works in both orders.
- Four deliberate mutations (drop the unsaved-edits check, the stale check, the same-hash check, the asset-browser re-watch) each turned exactly the intended test red.
- `test_editor_assets`: `break_editor_assets_refresh` create/delete/rename detection, content-only edits report no change, filter kept, vanished directory walks up, vanished root is a coherent empty listing. `test_editor_shell`: the browser re-lists on its 1 s clock, repaints only on change, never touches the document, and survives the current directory vanishing; with the tick wiring removed both tests fail.

Live (`editor` driven through gdb, real windows, scene file replaced by rename plus mtime bump as an external tool would): on the default Vulkan path of the multi-backend build and on an OpenGL-only build, a missing scene appearing, a valid replacement (1 to 3 entities), an invalid replacement (document kept, failure counted) and a replacement while the document had unsaved edits (skipped) all behaved as above, with the console lines shown in the shell. This is a smoke of the logic inside a running editor, not a visual or GPU correctness claim.

Not run: Windows and macOS (the Win32 and kqueue/FSEvents `FileWatcher` backends are untouched and untested here), CI.

## 6. Explicit lifecycle contract

`create(shell)` allocates only the object; `set_scene` (called by the shell when a scene path is configured, a scene is loaded from the browser, or the object is attached) starts the VFS, coordinator and watcher, and stops the previous ones first. `tick` is shell-thread-only. `note_saved` is called by the shell after a successful Ctrl+S: it bumps the local epoch (so in-flight reloads become stale) and re-hashes the file as the new baseline. `destroy` detaches from a live shell, stops the watcher and shuts the coordinator down with a 2 s bound; if a worker does not stop in time it leaks the coordinator and the object rather than free them under a running thread, and logs an error. No worker callback references the shell.
