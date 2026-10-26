# Editor asset hot reload

Status: design (2026-10-26). Stage 4 subproject 4, the missing hot-reload half of the asset browser. This is an editor integration of the existing Runtime Core coordinator, not a second reload/thread architecture.

## 1. Scope and non-goals

Delivered scope:
- Watch the current `.bscn` scene file. External changes are read by Runtime Core workers and committed on the editor shell thread through `break_runtime_reload_commit_owner`.
- A valid external scene replaces the document using the existing REPLACE/world-swap semantics; selection is reconciled and the whole shell refreshes.
- A malformed, unreadable, or failed load leaves the current document, names, and undo history intact (`FAILED_KEEP_OLD`).
- A local dirty document is never overwritten by an external event. The event is reported and skipped while dirty.
- An editor-originated save suppresses its own next file event, so save does not reload the same bytes and erase undo history.
- The asset browser's current directory listing refreshes on filesystem events through the existing structured directory watcher.
- Asset-browser scene loads and the CLI scene path share the same `scene_path` and watcher.

NOT delivered: shader/texture hot reload inside the editor, VFS PAK enumeration, cross-device asset dependency graph, async GPU upload, render-scene/SCENE_NODES ownership, remote load/save, Windows/macOS runtime verification. `scene_load_binary` keeps its existing file-based behavior for other callers.

## 2. Ownership and data flow

The editor host owns `BreakEditorHotReload`; the shell borrows it and drives it once per `break_editor_shell_tick`, exactly like the remote session host. The host detaches and destroys it before destroying the shell.

```text
FileWatcher callback (shell thread in this integration)
        -> break_runtime_reload_notify_file_event(logical_path)
Runtime Core worker: VFS read into owned staging bytes + validate
        -> bounded commit queue
shell tick: pump_events + commit_owner
        -> break_editor_doc_load_bytes(staged BSCN, scene_path)
        -> selection reconcile + shell refresh
```

`FileWatcher` and the structured directory watcher are only polled by the shell thread. Runtime Core workers never touch the editor document, widgets, selection, Lua, or RHI. Commit hooks receive borrowed staging bytes and must not retain them.

The VFS mount is the scene's parent directory; the coordinator path is the scene basename, so absolute paths and `..` never cross the VFS boundary. Watch paths are bounded by the existing `FILEWATCH_MAX_PATH`/`VFS_MAX_PATH` limits; over-limit paths disable watching with a visible log instead of truncating.

## 3. Loading and failure rules

`scene_load_binary_memory` is the memory form of the existing BSCN reader, with the file reader kept as a thin wrapper. `break_editor_doc_load_bytes` uses the same fresh-world staging and sidecar handling as `break_editor_doc_load`, but parses the exact coordinator staging bytes. The sidecar is read from the scene path at commit time; the BSCN is never re-read from disk by the commit hook.

- External valid BSCN: commit, clear stale selection through the existing selection sync, refresh the shell.
- External invalid BSCN or a commit failure: `FAILED_KEEP_OLD`; no doc mutation, log the failure.
- Dirty doc: do not commit, keep local edits and command history, log that the external change was skipped. No silent conflict resolution.
- Internal save: `break_editor_hot_reload_note_saved` suppresses one event for that scene. A subsequent real external edit is a new event and is processed normally.
- Scene changes (CLI, asset browser): stop the old watcher/coordinator, create the new one only after a successful load/path update; failed path setup leaves the old scene/document intact.
- Shutdown: `break_runtime_reload_shutdown` runs before `break_editor_hot_reload_destroy`; worker completion cannot race shell/doc destruction. A timeout is reported and does not claim a clean shutdown.

## 4. Directory listing

The existing `FileWatch` recursive watcher watches the assets root. The shell drains at most 32 events per tick; any event refreshes the current directory model through the bounded `break_editor_assets_refresh` path and repaints the assets panel. Event loss follows the existing watcher overflow/rescan contract; no claim of reliable per-file delivery is made.

## 5. Tests and evidence

- BSCN memory/path equivalence, malformed input, and failed-load document preservation.
- Real temp-directory watcher integration: external valid edit commits; invalid edit keeps old; dirty doc is preserved; own-save suppression; scene switching; bounded shutdown.
- Directory create/modify/delete refreshes the asset listing without changing the document.
- Full editor and non-graphics suites on OpenGL, Vulkan, multi-backend, and Snowflake trees; ASan+UBSan/TSan for the new paths.
- Live editor smoke where available: external scene edit appears without a manual reload, on both Vulkan and OpenGL. Windows/macOS and CI remain unverified.

## 6. Explicit lifecycle contract

`create(shell, scene_path)` allocates VFS/coordinator/watchers and starts Runtime Core workers. `set_scene` is the only scene-switch operation. `tick` is shell-thread-only. `note_saved` only changes the one-event suppression counter. `destroy` is host-side and must follow detach + bounded coordinator shutdown; no worker callback may reference the shell after that point.
