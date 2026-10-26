# Editor hot reload implementation plan

Contract: `docs/design/editor_hot_reload.md`. Branch `sdd/editor-hot-reload`.

Constraints: C11 production code; existing Runtime Core/VFS/FileWatch APIs; no second worker pool; TDD with captured RED evidence; no Windows/macOS claims; no direct doc writes from worker threads; no new public behavior for other scene loaders.

## Task 1 — Memory scene loading

- Add `scene_load_binary_memory(World*, Scene*, const void*, size_t)` by extracting the existing reader body from `scene_load_binary`; keep the file API as a wrapper with the same bounds/errors.
- Add `break_editor_doc_load_bytes(doc, scene_path, bytes, size)` using the existing fresh-world REPLACE/sidecar semantics, without re-reading the BSCN path.
- Tests in `test_editor_scene`: saved scene loads identically through file and memory; malformed memory fails without changing the document; sidecar behavior and undo-stack clearing match the file API.
- RED first: the new APIs do not exist; then implement and run scene/editor suites.

## Task 2 — Hot-reload coordinator and shell integration

- Add `editor_hot_reload.{h,c}` under `engine/apps/editor`: host-owned VFS + Runtime Core coordinator + legacy scene FileWatcher; shell-borrowed tick/commit; basename-to-VFS mapping; one-save suppression; dirty-doc skip; fail-closed set_scene/shutdown.
- Wire shell attach/tick/detach and `editor_main` lifecycle. Route asset-browser successful loads through a helper that updates `scene_path` and the watcher after a successful load.
- Tests with real temp directories: external valid edit, invalid edit, dirty preservation, own-save suppression, scene switching, bounded shutdown. No sleeps longer than needed; poll with a deadline.
- Run the new tests before and after implementation, plus editor suites on normal/ASan/TSan trees.

## Task 3 — Asset listing refresh and closeout

- Expose bounded `break_editor_assets_refresh`; add a structured root watcher and drain at most 32 events per shell tick, refreshing only the current listing/panel.
- Add create/modify/delete listing tests and confirm the document is untouched by directory-only events.
- Live smoke on Vulkan and OpenGL if the host display permits; otherwise record exactly what was not run.
- Update `docs/design/editor_hot_reload.md` evidence, `docs/design/roadmap_2026-10-22.md`, `docs/Implementation_Status.md`, and the runtime expansion todo/deferred ledger.
- Independent review, `git diff --check`, full suites, then merge.

Explicitly out of scope: shader/texture hot reload, PAK enumeration, SCENE_NODES ownership, remote load/save, production conflict resolution, and Windows/macOS runtime evidence.
