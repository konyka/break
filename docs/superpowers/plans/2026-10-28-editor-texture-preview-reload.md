# Editor image preview + texture hot reload — plan (2026-10-28)

Spec: `docs/superpowers/specs/2026-10-28-editor-texture-preview-reload-design.md`. Branch `sdd/editor-texture-preview`. TDD: each task writes its failing tests first.

## Task 1 — `break_editor_image` (pure CPU)

- `engine/src/editor/editor_image.{h,c}`: `BreakEditorImage`, `break_editor_image_probe`, `break_editor_image_decode`, `break_editor_image_free`, `break_editor_image_is_supported_name`; limits `BREAK_EDITOR_IMAGE_MAX_DIM 4096`.
- Add the TU to `break_editor` and `break_editor_test`; `break_editor` links `stb_image` PRIVATE.
- `engine/tests/test_editor_image.c` (+ CTest, labels `headless;editor`): PNG and BMP generated with `stbi_write_*_to_func` decode to the right size and first pixel; probe agrees with decode; empty, truncated and garbage input fail; a header claiming 4097 width fails probe and decode; extension check accepts `.PNG`/`.jpeg`, rejects `.bscn`, `png`, `.png.txt`, NULL.
- Update `test_break_editor_target_contract` if it pins the TU list.

## Task 2 — `editor_image_preview` owner

- `engine/apps/editor/editor_image_preview.{h,c}` following `editor_shader_reload.c`: own VFS (mount the file's directory), Runtime Core reload (1 worker, 4 slots), `filewatch_add_with_missing` on the current file, validate = probe, commit = decode into staging, tick pumps commits every time, trailing pending, retryable bounded shutdown, `BREAK_EDITOR_SHELL_TESTING` seam for the shutdown timeout.
- GPU swap in tick: device NULL -> keep staging as the "current" image and count it; device set -> `rhi_texture_create` RGBA8 1 mip; destroy the old texture only after success.
- Tests in `test_editor_shell` (fake RHI counts texture creates/destroys): load, reload with a new size, garbage keeps old, set_path to a second file, shutdown with a held worker (runtime test gate).
- Add the TU to `editor`, `test_editor_shell`, `fuzz_editor_remote`.

## Task 3 — asset browser wiring, preview widget, i18n

- Shell owns the preview (`editor_panels.c`), ticks it before `frame_begin`, attaches the device with the render panel.
- `editor_panel_assets.c`: image rows call `set_path` with the absolute path; preview widget below the list paints the texture with aspect fit, or the placeholder text.
- i18n keys (en-US + zh-CN): preview placeholder, preview loaded, reload applied, reload failed. `test_editor_i18n` coverage keeps passing.
- Tests: clicking an image row through the panel loads it; a `.bscn` row still loads the scene; other rows still log "not loadable".

## Task 4 — verification and docs

- Full ctest in the OpenGL, Vulkan, Snowflake, multi-backend and Release trees; graphics lanes; ASan/TSan `test_editor_shell` x3; `test_release_config_contract` (no new hooks in `editor`).
- Live on Vulkan and OpenGL: click a PNG, rewrite it externally, compare preview pixels; garbage keeps the last image.
- Docs: `docs/design/editor_hot_reload.md` §8, `docs/Implementation_Status.md`, roadmap and TODO ledger. Merge to master, push.
