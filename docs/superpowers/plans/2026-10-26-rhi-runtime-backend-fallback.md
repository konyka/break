# Runtime backend selection + OpenGL fallback — implementation plan

Design contract: `docs/design/rhi_runtime_backend.md` (read it first). Branch `sdd/rhi-runtime-fallback`.

Hard constraints:
- Single-backend builds (`-DENGINE_RHI_BACKEND=vulkan|opengl|metal|d3d12`, and `auto` without Vulkan deps) must be byte-for-byte unaffected in behaviour: no dispatch layer, no renamed symbols, existing tests unchanged.
- TDD per task: write the failing test first, keep the failure output, then implement.
- No build-time code generation and no new build dependency. Generated files are committed and kept honest by a contract test.
- Every graphics test binary runs under `timeout 180`. Never run `GOLDEN_UPDATE=1` against the committed goldens in `engine/tests/golden` (use a scratch copy if a reference must be regenerated).
- Do not change the committed Vulkan goldens. OpenGL goldens were regenerated on 2026-10-26 and must not move.

## Task 1 — API inventory, generator, dispatch layer (headless TDD)

1. `engine/src/rhi/dispatch/rhi_backend_api.txt`: the 132 backend API names. Derive them from `nm -g --defined-only` on `libengine_rhi_opengl.a` (they are exactly the shared GL/VK exports; the five `rhi_vk_*` VK-only test helpers are excluded).
2. `engine/tools/gen_rhi_dispatch.py` (dev-time generator, committed): reads the name list and the declarations in `engine/src/rhi/*.h`, emits into `engine/src/rhi/dispatch/`:
   - `rhi_api.h`: `RHIApi` struct (one correctly typed function pointer per name), plus the runtime-module declarations.
   - `rhi_dispatch.c`: active-table pointer, a stub table whose entries log once and return a zero/failure value, and one public forwarder per name **except** `rhi_device_create` and `rhi_device_create_compiled` (owned by the runtime module).
   - `rhi_api_bind_gl.c`, `rhi_api_bind_vk.c`: fill a table from the backend symbols, compiled with the rename headers so the same source text binds `rhi_gl_*` / `rhi_vk_*`.
   - `rhi_backend_rename_gl.h`, `rhi_backend_rename_vk.h`: one `#define rhi_<name> rhi_gl_<name>` / `rhi_vk_<name>` per name.
   The generator must fail loudly on a declaration it cannot parse instead of emitting wrong code. All 132 declarations are plain (no function-pointer, variadic or array arguments), verified 2026-10-26.
3. `rhi_device_create_compiled` definitions inside `rhi_gl.c` / `rhi_vk.c` are compiled out in the multi-backend shape (the runtime module owns that entry point). Each backend source includes `rhi/rhi_backend_namespace.h` first; that header applies the rename header only when its `RHI_BACKEND_NAMESPACE_*` macro is defined.
4. `test_rhi_dispatch_contract.cmake`: every listed name appears exactly once in the table, in the forwarders, in both rename headers and in the matching binding file; no extra names; creation entry points are absent from the forwarders.
5. `test_rhi_dispatch` (C, headless): includes `rhi_api.h`, installs a mock table, and proves (a) forwarders route to the active table, (b) switching the active table reroutes, (c) with no device created the stub table returns failure values and does not crash, (d) `rhi_device_create` / `rhi_device_create_compiled` are not in the generated forwarders.

## Task 2 — Runtime selection module (headless TDD)

`engine/src/rhi/rhi_runtime.c` (+ declarations in `dispatch/rhi_api.h` or a small public header):
- Implements `rhi_device_create` (explicit backend, no fallback; unlinked backend fails) and `rhi_device_create_compiled` (chain: `vulkan` then `opengl`).
- `BREAK_RHI_BACKEND=opengl|vulkan` restricts the chain; unknown values warn and use the default; `BREAK_RHI_NO_FALLBACK=1` disables the second entry.
- `RHIEVT` events: `fallback` on each failed chain entry, `backend_selected` on success, with the backend actually used. Extend the rollout reason whitelist if a new reason is needed (e.g. `create-failed`) and update `test_rhi_rollout_log` accordingly.
- `rhi_runtime_active_backend()` returns `vulkan` / `opengl` / `none`.
- Test hook: `BREAK_RHI_FAIL_VULKAN=1` makes the Vulkan creation attempt fail before touching the driver, so the real fallback can be exercised on a machine with a working Vulkan driver.
- Selection logic is separated behind injected factory callbacks so `test_rhi_runtime_select` runs without a GPU: primary ok, primary fails then fallback ok, all fail, env restriction, no-fallback, unknown env, event order, active-backend reporting.

## Task 3 — CMake multi-backend shape + apps

- Multi-backend shape only for `ENGINE_RHI_BACKEND=auto` on Linux/Windows when Vulkan deps are found and GL is available. `ENGINE_RHI_BACKEND_EFFECTIVE` stays `vulkan`; `ENGINE_RHI_MULTI_BACKEND` is defined for the engine, both backend libs and the apps.
- `engine_link_rhi_backend()` links `engine_rhi_vulkan` + `engine_rhi_opengl` in that shape; dispatch and runtime objects join the engine core target in that shape only.
- `test_rhi_multi_backend_symbols.cmake`: `nm` on the built libraries and on `engine_demo` — no duplicate public `rhi_*`, backend symbols namespaced, single-backend trees unaffected.
- `main.c` already uses `rhi_device_create_compiled`. Switch `editor_main.c`, `dxx_break_main.c` and `rhi_swapchain_bench.c` to the same entry point so they get the chain (they currently pick a backend with compile-time macros).
- Verify: a fresh default configure produces the multi-backend shape; explicit `vulkan` and `opengl` configures stay single-backend; `auto` with `-DCMAKE_DISABLE_FIND_PACKAGE_Vulkan=ON` still configures to OpenGL with a warning. Extend `test_rhi_backend_selection` if the shape assertions need it.

## Task 4 — Real verification + docs

- Headless: full `ctest -LE 'graphics|fuzz'` on the multi-backend default build and on an explicit-OpenGL build; focused new tests on both.
- Graphics (this machine has a working NVIDIA/NVK Vulkan driver and Intel/Mesa GL):
  - default multi-backend `test_vulkan`: ALL PASSED (Vulkan path, golden MAE 0.00);
  - runtime smoke: `rhi_device_create_compiled` with `BREAK_RHI_FAIL_VULKAN=1` yields an OpenGL device and a `fallback` event; `BREAK_RHI_BACKEND=opengl` yields OpenGL; default yields Vulkan; all on the same window, then clean destroy;
  - `engine_demo` with the forced failure runs on OpenGL (`RHIEVT backend_selected backend=opengl`).
- Docs: `docs/design/rhi_runtime_backend.md` status to delivered-with-limits (list what was actually verified), `docs/rhi_rollback_runbook.md` (runtime fallback now real; env switches added to the governance table), `docs/cross_engine/graphics_backend_audit.md` finding 5, `docs/design/roadmap_2026-10-22.md`, `docs/superpowers/plans/2026-10-22-runtime-expansion-todo.md`.
- Focused code review of the whole branch before merge; commit per task.

## Explicitly out of scope

Device-loss fallback after a successful create, switching back to Vulkan, two live devices, D3D12/Metal joining the chain, Windows/macOS runtime verification (no such machine here).
