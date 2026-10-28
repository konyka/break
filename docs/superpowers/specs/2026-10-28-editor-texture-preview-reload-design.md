# Editor image preview + texture hot reload — design (2026-10-28)

## 1. Goal

The shader hot reload design (2026-10-27) left texture hot reload undelivered because no editor code owned a texture asset. This sub-project adds that consumer and then reloads it:

1. Clicking an image file (`.png`, `.jpg`, `.jpeg`, `.bmp`, `.tga`) in the asset browser shows a preview. The preview owns its own `RHITexture`, drawn with `my_vgcanvas_break_rhi_blit_texture`.
2. When that file changes on disk, the preview reloads it: a Runtime Core worker reads and decodes, the shell thread swaps the GPU texture. A failed reload keeps the previous texture.

Out of scope: material/scene texture reload, mip chains, sRGB handling, formats other than RGBA8, more than one preview at a time, Windows/macOS live runs.

## 2. Approaches considered

A. **Own preview owner on Runtime Core reload (chosen).** Same shape as `editor_shader_reload`: one coordinator, 1 worker, small slot table. The worker reads the file and its `validate` hook checks the image header with `stbi_info_from_memory` (format recognised, dimensions in bounds) without decoding; the owner `commit` hook decodes the borrowed bytes into owned staging pixels; the shell tick creates the new `RHITexture` and destroys the old one only after the new one exists. Runtime Core's hooks only pass the raw file bytes (validate may not keep state, commit may not retain the pointer), so the decode has to happen in commit. The 4096x4096 bound keeps that decode bounded on the shell thread; this cost is documented rather than hidden. Reuses tested machinery and the same failure semantics.

B. `async_loader` + `decode_pipeline`. Already decodes textures off-thread, but it is the game asset path with a global singleton, mip generation and its own slot lifecycle; driving it from the editor would couple the two and still leave the swap to write.

C. Decode on the shell thread. Simplest, but a large image would stall the UI and it does not exercise the worker path the roadmap asks for.

## 3. Units

- `engine/src/editor/editor_image.{h,c}` (in `break_editor`, pure CPU, no RHI): `break_editor_image_probe(bytes, size, &w, &h)` (header only, `stbi_info_from_memory`), `break_editor_image_decode(bytes, size, out)` (`stbi_load_from_memory` forcing 4 channels), both reject width/height 0 or > 4096; an owned `BreakEditorImage { u32 w, h; u8 *rgba; }` with `break_editor_image_free`; `break_editor_image_is_supported_name(name)` (case-insensitive extension check). Unit-testable with in-memory PNG/BMP bytes.
- `engine/apps/editor/editor_image_preview.{h,c}`: the owner. `create(device-or-NULL)`, `set_path(abs_path)` (validates, re-targets the watcher, queues a load), `tick()` (filewatch poll, commit pump, finish attempt, GPU swap), `texture()`, `stats()` (`attempts`, `reloads`, `failed`, `last_result`, `width`, `height`, `busy`), `shutdown()`/`destroy()` with the retryable bounded stop of the shader owner. Without a device (headless tests) it keeps the decoded image and counts the swap but creates no GPU texture; tests use the existing fake RHI to count texture creates/destroys.
- `editor_panel_assets.c`: image rows route to the preview instead of the "not loadable" note. A preview widget under the asset list paints the texture (aspect fit) or a placeholder text.
- `editor_panels.c` shell tick calls the preview tick before `frame_begin`, as for the shader owner.
- i18n: new keys for the preview placeholder and the console lines (loaded / reload applied / reload failed, kept old), en-US and zh-CN.

## 4. Data flow and failure rules

```
file change / set_path -> pending
tick: no attempt active + pending -> break_runtime_reload_request(path)
worker: VFS read -> validate hook = header probe (fails -> FAILED_KEEP_OLD)
owner tick: commit_owner -> commit hook decodes into owned staging pixels
            (decode fails -> FAILED_KEEP_OLD)
tick: terminal COMMITTED + staging -> create RHITexture(w, h, RGBA8, data)
      success -> destroy old texture, publish new, reloads++
      failure -> keep old texture, failed++
```

- The commit queue is pumped every tick (the 2026-10-28 shader reload fix applies from the start).
- Changes during an attempt set one trailing pending flag; only the latest file content is applied.
- `set_path` to a different file cancels the live request; a late result for the old path is dropped by its request handle.
- The decoded pixels cross threads only through Runtime Core staging; the hooks never touch RHI or widgets.
- Paths over the bounded capacity are rejected, never truncated.

## 5. Testing

- `test_editor_image` (new): probe and decode PNG and BMP bytes generated in the test with `stb_image_write`, truncated/garbage input fails, zero and oversized dimensions fail, extension check.
- `test_editor_shell` (new cases, real temp dir, real VFS/worker/filewatch, fake RHI): clicking an image row loads it (1 texture create, size reported); rewriting the file with a different size reloads it (new create, old destroyed, reported size changes); replacing it with garbage keeps the old texture (`failed` +1, no destroy); switching to another image cancels cleanly; shutdown with a live request is bounded.
- Live: real editor on Vulkan and OpenGL, click a PNG in the asset browser, rewrite it externally, screenshot pixels of the preview region change; garbage keeps the last image.

## 6. Not delivered

Material or scene textures, texture dependency tracking, mips, sRGB, HDR formats, multiple previews, GPU upload on a worker, Windows/macOS live runs.
