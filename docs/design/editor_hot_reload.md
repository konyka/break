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

Viewport shader hot reload was delivered later (2026-10-27) as its own subproject; see §7. Still NOT delivered: texture hot reload inside the editor, VFS PAK enumeration, cross-device asset dependency graph, async GPU upload, render-scene/SCENE_NODES ownership, remote load/save, Windows/macOS runtime verification. `scene_load_binary` keeps its existing file-based behavior for other callers.

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

## 7. Viewport shader hot reload (delivered 2026-10-27)

Design `docs/superpowers/specs/2026-10-27-editor-viewport-shader-reload-design.md`, plan `docs/superpowers/plans/2026-10-27-editor-viewport-shader-reload.md`. Separate owner from the scene reload above; the two share no state.

- `editor_shader_source.{h,c}`: one bounded resolver for first load and reload. Roots in priority order: `BREAK_SHADER_DIR`, `.`, `engine`, `../engine`, `../../engine`; the backend variant (`_vk`) comes from the device caps. Over-long roots are skipped, never truncated.
- `editor_viewport3d.c`: a transactional candidate build (VS, FS, pipeline, bindings, `u_mvp`/`u_color`, VBO when missing). Only a complete candidate is published; any failure leaves pipeline, bindings, locations and VBO untouched. A failed first load is recoverable by a later event or manual request, and never retried every frame.
- `editor_shader_reload.{h,c}`: owned by the viewport. One Runtime Core coordinator (1 worker, 4 slots) requests the vertex and fragment files as two real VFS paths (roots mounted in reverse priority). The worker only reads and size-checks; the owner commit copies bytes; both terminal states must be COMMITTED before the shell-thread GPU apply, which happens in `break_editor_shell_tick`, before `frame_begin`. Changes during an attempt set one trailing pending flag.
- Watching: every bounded candidate path is registered with `filewatch_add_with_missing`, an opt-in variant that also reports existing -> missing, so deleting a higher-priority pair falls back automatically. `filewatch_add` (scene reload, game `asset/hotreload.c`) keeps its old rule. The watcher is still a lossy whole-second mtime poll; `Ctrl+Shift+R` is the deterministic fallback.
- `Ctrl+Shift+R` only queues a request (exact Ctrl+Shift chord; `R` and `Shift+R` stay Scale). Results go to the console; the render debugger shows `shader reload: watching|manual-only|shutdown-pending busy=.. applied=.. failed=..` or `unavailable` when no owner exists.
- Shutdown is retryable: a worker that does not stop in time makes viewport/shell destroy return false and keep every borrowed resource; `editor_main` then reports retained resources instead of tearing down the device under a live worker.

Evidence (branch `sdd/editor-shader-reload`):
- Headless (real watcher/VFS/Runtime Core, fake RHI recording separate vertex and fragment revisions): `test_editor_shell` 77 (Snowflake OFF) / 102 (ON); `test_hotreload` 6 incl. the opt-in delete-notify rule. Mutations: feeding vertex bytes as fragment, and reverting to the legacy watcher, each turn the intended test red.
- Full non-graphics suites: OpenGL 204/204, Vulkan 205/205, multi-backend 204 + 1 skip, Snowflake 208/208. ASan+UBSan and TSan: `test_editor_shell` 10 runs each at 102/102, `test_hotreload` and `test_runtime_reload` green, zero sanitizer reports; fuzz smoke 6/6.
- Live, real windows (X11 via Xwayland on this host, NVK Vulkan and Mesa OpenGL, `/tmp/mb/editor` with `BREAK_SHADER_DIR` on a temporary shader copy, one proxy entity added through the document API under gdb): screenshot pixels of the proxy cube changed with each valid fragment edit (grey -> magenta -> cyan), stayed magenta after an invalid edit (the backend logged the compile error), did not change when content changed without an mtime change, and turned yellow after `Ctrl+Shift+R` (issued at the shell dispatcher via gdb, because XTEST keys did not reach the window under Xwayland). Same sequence on both backends. Artifacts: `.superpowers/sdd/2026-10-27-editor-viewport-shader-reload/live/`. OpenGL needed a longer settle time on one run; nothing else differed.

Fix 2026-10-28 (dead commit commands): when the fragment admission of an attempt fails, the attempt cancels its vertex request at once. If the worker had already read that file it still publishes a commit command, which is now dead and sits in the owner's 4-entry commit queue until `break_runtime_reload_commit_owner` skips it. The tick used to pump that queue only while an attempt was active, and an attempt that fails at admission is never active, so back-to-back failures filled the queue and the next valid reload was rejected as a commit overload (`failed_keep_old`). This only happened when the worker overtook the owner thread between the two admissions, i.e. on loaded machines: CI failed `shader_reload_second_request_admission_failure_recovers` intermittently, and this host reproduced it 5–7 of 20 runs with every core busy. The tick now pumps the commit queue every time (outside an attempt it can only reclaim dead commands). `shader_reload_dead_commit_commands_do_not_block_next_reload` forces the interleaving with a test-only seam between the two admissions (`break_editor_shader_reload_set_between_requests_for_test`, `BREAK_EDITOR_SHELL_TESTING` only): red 3/3 without the fix, green with it; the loaded stress run went from 7/20 failures to 0/40.

Shader `#include` (delivered 2026-10-29): a line whose first non-blank text is `#include "name"` is replaced by `shaders/<name>` from the first root that has it (same priority as the stage files), on the owner thread, before the GPU apply — both for the first load and for every reload (`break_editor_shader_source_expand`). Names are relative `[A-Za-z0-9_.-/]` with no `..`, no leading `/`, no empty segment; nesting is bounded at 4, cycles, missing files, `#include <...>`, unterminated names and output above `SHADER_MAX_FILE_BYTES` fail the attempt and keep the current shaders. Every include met (up to 16 distinct paths, also on failure, so a missing include that reappears retriggers) is added to the watcher in every root (`break_editor_shader_reload_watch_deps`); editing only an included file reloads the shader. Not handled: `#line` remapping (compiler errors report expanded line numbers), conditional includes (`#if` around an `#include` is ignored — the include always expands), and dependencies that are no longer included stay watched until the editor exits. Tests: `test_editor_shell` `shader_source_expands_includes_with_bounds` (nesting, root priority, low-root-only file, dependency list, every failure case, depth bound) and `shader_reload_follows_included_files` (a fragment that starts including a file; editing only the include; deleting it keeps the old pipeline; restoring it recovers). Mutation: not watching the dependencies turns the second test red. Live (Vulkan and OpenGL, temporary shader root whose fragment shaders `#include "editor_tint.glsl"`): rewriting only `editor_tint.glsl` while the editor runs turns the proxy cube magenta (0 → 13456 px on both backends) and logs "shader reload: applied shader pair". On OpenGL a tint that ignores its input made the compiler drop `u_color`, the uniform lookup failed and the old shaders stayed — the existing keep-old rule, not an include issue.

Not delivered: device migration, async GPU compile, Windows/macOS live runs. Texture hot reload was delivered on 2026-10-28 for the asset-browser image preview (§8).

## 8. Image preview and texture hot reload (delivered 2026-10-28)

Design `docs/superpowers/specs/2026-10-28-editor-texture-preview-reload-design.md`, plan `docs/superpowers/plans/2026-10-28-editor-texture-preview-reload.md`.

- Clicking a `.png`/`.jpg`/`.jpeg`/`.bmp`/`.tga` row in the asset browser opens it in a preview under the list (label with the size or state, image area with aspect-fit blit). `.bscn` rows still load scenes; other files still log "not loadable".
- `break_editor_image` (`src/editor/editor_image.{h,c}`, in `break_editor`): header probe and RGBA8 decode through stb_image, both rejecting a zero side or one above 4096.
- `editor_image_preview.{h,c}` (owned by the assets panel): one Runtime Core reload coordinator (1 worker) on a VFS mounted at the file's directory, `filewatch_add_with_missing` on the file. The worker only probes the header; the commit hook on the owner thread decodes (Runtime Core's hooks pass raw bytes only, so the decode cannot move to the worker without a new seam; the 4096 bound caps it); the shell tick creates the new `RHITexture` and destroys the old one only after the new one exists. Any failure (unreadable, probe, decode, texture create) keeps the current texture. The commit queue is pumped every tick (§7 fix). Picking another file in the same directory cancels the live request and re-targets the watcher; another directory restarts the coordinator. Without a device the preview still decodes and reports the size; attaching a device uploads the current image once. Shutdown is bounded and retryable like the shader owner.
- Tests: `test_editor_image` 5; `test_editor_shell` +5 (load and watcher reload with a new size, old texture destroyed; garbage and failed GPU create keep the old texture, then recovery; switching files while the worker holds the old request applies only the new file and stops watching the old one; headless decode, device attach/detach, bounded shutdown with a held worker; the panel click opens the preview and a `.txt` click leaves it). Mutations: dropping the probe bound, not cancelling on a file switch, and disabling the image branch in the panel each turn the intended test red.
- Live (X11 via Xwayland, NVK Vulkan and Mesa OpenGL, `/tmp/mb/editor`, asset root and selection set through gdb at the shell tick because XTEST input does not reach the window): a 64x32 red PNG appears in the preview; rewriting it externally as a 32x64 green PNG replaces it (the green region is narrower and taller); overwriting with garbage keeps the green image (`reloads=2 failed=1`). A red-over-blue test image renders upright on both backends. Artifacts: `.superpowers/sdd/2026-10-28-editor-texture-preview/live/`.

Not delivered: material or scene textures, mips, sRGB, more than one preview, decoding on the worker, Windows/macOS live runs.
