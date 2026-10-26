# Runtime backend selection and OpenGL fallback

Status: **delivered with limits** (2026-10-26, branch `sdd/rhi-runtime-fallback`; evidence in §8). Owner decision history: OpenGL is retained permanently as the last-resort fallback and the rendering-comparison reference; the default backend on Linux and Windows is Vulkan; this document adds the **runtime** fallback that was previously only a build-time choice.

## 1. Goal and non-goals

Goal: with `ENGINE_RHI_BACKEND=auto`, one binary contains both the Vulkan and the OpenGL backend. At device creation it tries Vulkan first; if Vulkan device creation fails, it creates an OpenGL device on the **same platform window** and continues with OpenGL for the rest of the process. The choice is explicit and observable.

Non-goals (NOT delivered):
- No fallback after a successful device creation. Device loss, present failure, or a driver crash mid-run does **not** switch backends: all GPU resources would have to be re-created, which is a separate project.
- No switching back to Vulkan at runtime, and no two live devices on different backends.
- D3D12 and Metal are not part of the runtime chain. They stay explicit single-backend builds (`-DENGINE_RHI_BACKEND=d3d12|metal`). The mechanism is generic enough to add them later.
- No change to single-backend builds: explicit `vulkan` / `opengl` / `metal` / `d3d12` builds keep exactly one backend, no dispatch layer, no new overhead.

## 2. Build shapes

| `ENGINE_RHI_BACKEND` | Backends linked | Device creation |
|---|---|---|
| `auto` on Linux/Windows, Vulkan deps + GL available | Vulkan + OpenGL + dispatch | runtime chain `vulkan -> opengl` |
| `auto` with Vulkan deps missing | OpenGL only (as today) | OpenGL, configure-time warning |
| `vulkan`, `opengl`, `metal`, `d3d12` (explicit) | exactly one | requested backend, fail closed |

`ENGINE_RHI_BACKEND_EFFECTIVE` stays `vulkan` for the multi-backend shape (Vulkan is the primary), so shader-variant selection, test registration and receipts are unchanged. A new `ENGINE_RHI_MULTI_BACKEND` compile definition marks the multi-backend shape.

## 3. Dispatch mechanism

The app calls the public `rhi_*` API exactly as before; no app source changes are needed to route calls.

Facts this design relies on (verified 2026-10-26 against `libengine.a`, `libengine_rhi_opengl.a`, `libengine_rhi_vulkan.a`):
- The core (`libengine.a`) and the backends export **disjoint** symbol sets: 72 core `rhi_*` functions, 132 backend `rhi_*` functions. The 132 are identical between GL and VK except five VK-only test helpers.
- The two backend libraries share **no** global symbol outside those 132, so they can be linked into one binary once their API symbols are namespaced.
- No code takes the address of a public `rhi_*` function (verified before this work; the generated binding tables now take the addresses of the namespaced `rhi_gl_*` / `rhi_vk_*` functions, which is the mechanism itself).

Mechanism:
1. `engine/src/rhi/dispatch/rhi_backend_api.txt` lists the 132 backend API names and is the single source of truth.
2. Each backend is compiled with a namespace header (`rhi_gl_*` / `rhi_vk_*`) in the multi-backend shape only. The namespace covers exactly the 132 names; core helpers are untouched.
3. `RHIApi` is a table of 132 function pointers whose types are copied from the public declarations. One table is bound per backend.
4. The public `rhi_*` symbols in a multi-backend binary are small forwarders in the dispatch layer that call through the **active** table. They are real functions, not macros, so public headers do not change and no function-like macro can leak into tests or apps.
5. Before any device is created, the active table is a stub table: every entry logs once and returns a zero/failure value instead of crashing.
6. Creation and destruction of the active table are owned by the runtime module, not by the generic forwarders.

The generated files are committed (no build-time code generation, no new build dependency). A contract test keeps them in sync with `rhi_backend_api.txt`, and an `nm` contract test pins the exported-symbol shape.

## 4. Selection rules

`rhi_device_create(backend, ...)` keeps its explicit meaning: it creates exactly the requested backend if that backend is linked, otherwise fails (`UNAVAILABLE`). It never falls back by itself. On success it installs that backend's table as active.

`rhi_device_create_compiled(window_native, surface_native, display_native, w, h)` is the chain entry used by the apps (`main.c`, `editor_main.c`, `dxx_break_main.c`, `rhi_swapchain_bench.c`):
1. Chain default: `vulkan`, then `opengl`.
2. `BREAK_RHI_BACKEND=opengl|vulkan` restricts the chain to that one backend (reason `explicit-env`). An unknown value logs a warning and uses the default chain.
3. `BREAK_RHI_NO_FALLBACK=1` keeps only the first chain entry.
4. Every failed entry emits `RHIEVT` `fallback` with the backend and result; a successful entry emits `backend_selected` with the backend actually used.
5. If every entry fails, the function returns NULL and the last result is reported. Nothing is partially created: a failed backend create cleans up after itself, as in the single-backend builds.

`rhi_runtime_active_backend()` reports the active backend name (`vulkan` / `opengl` / `none`) for diagnostics and tests. In the multi-backend build `rhi_rollout_compiled_backend()` / `rhi_rollout_compiled_reason()` return the runtime choice once a device exists (see §8); single-backend builds keep the compile-time answer.

Platform coupling: both backends can be created from the same `Platform`. X11 gives both the same window and display; Wayland gives GL the `wl_egl_window` and VK the `wl_surface`; Windows gives both the HWND. No window is recreated and no second window appears. (Verified on X11 only, §8.)

## 5. Failure semantics

- Fallback happens only on device-creation failure. Errors after that point keep their current meaning and never trigger a backend switch.
- An explicit backend request that is not linked fails closed; it never silently selects another backend.
- A call made before any device exists returns a failure value from the stub table, with one log line, instead of dereferencing a null table.
- The stub table, the selection logic, and the event sequence are unit-testable without a GPU through injected factory callbacks and a mock table.

## 6. Testing

- `test_rhi_runtime_select` (headless): chain order, primary failure to fallback, all-fail, env restriction, no-fallback switch, unknown env value, event sequence, stub-table behavior, forwarder routing through a mock table.
- `test_rhi_dispatch_contract`: generated files match `rhi_backend_api.txt` (each name exactly once in the table, the forwarders, the namespace headers, and each binding file).
- `test_rhi_multi_backend_symbols`: `nm` shape of the multi-backend libraries and of one app binary (no duplicate public `rhi_*` definitions, backend symbols namespaced).
- Graphics lane: `test_vulkan` still exercises Vulkan in the multi-backend build. A new smoke test creates a real device through `rhi_device_create_compiled`, forces the Vulkan creation to fail through a test hook, and asserts that the resulting device is OpenGL; it also covers `BREAK_RHI_BACKEND=opengl`.
- Existing suites must stay green on single-backend builds (no dispatch) and on the multi-backend default build.

## 7. Documentation obligations

The runbook currently describes runtime fallback configuration that nothing reads. After this lands, the runbook, `docs/cross_engine/graphics_backend_audit.md` finding 5, the Stage 6 todo and the roadmap must describe the mechanism above, including the non-goals in §1.

## 8. Delivered (2026-10-26)

Implementation: `engine/src/rhi/dispatch/` (generated by `engine/tools/gen_rhi_dispatch.py`; `--check` verifies), `engine/src/rhi/rhi_runtime.{h,c}` (chain logic), `engine/src/rhi/rhi_runtime_backends.c` (real Vulkan/OpenGL factories, multi-backend build only), `engine/src/rhi/rhi_backend_namespace.h`. CMake: `ENGINE_RHI_MULTI_BACKEND` (default ON) takes effect only when `auto` resolves to Vulkan on Linux/Windows; `ENGINE_RHI_MULTI_BACKEND_ACTIVE` records the result.

Deviations from §3-§4:
- The active table is an `_Atomic` pointer with acquire/release, and the once-only stub log is an `atomic_flag`: the command-buffer submit thread (`renderer/cmd_buffer.c`) issues `rhi_cmd_*` calls, so a plain global would race.
- `rhi_rollout_set_runtime_selection()` (core) records the chain's choice, so later `RHIEVT` lines (`device_lost`, `present_failure`) name the backend actually in use. Single-backend builds never call it and keep the compile-time answer.
- The five VK-only test helpers (`rhi_vk_validation_*`, `rhi_vk_set_alloc_failure_for_test`) are not part of the dispatch table and stay unrenamed in the Vulkan backend.
- `editor` and `dxx_break` now create their device with `rhi_device_create_compiled`. `rhi_swapchain_bench` deliberately keeps explicit per-backend creation: it is a per-backend benchmark and must not silently measure the fallback.

Verified on this host (Linux X11; Vulkan = NVIDIA RTX A5000 through NVK, OpenGL = Mesa 26.2.4 4.6 compatibility):
- Fresh default configure resolves to the multi-backend build; full build exit 0. `engine_demo` carries exactly one public definition per backend API name and 131 namespaced symbols per backend (`test_rhi_multi_backend_symbols`).
- Headless: `ctest -LE 'graphics|fuzz'` 205/205 on the multi-backend tree, 204/204 on an explicit OpenGL tree, 205/205 on an explicit Vulkan tree.
- Graphics on the multi-backend tree: `ctest -L graphics` 8/8, including `test_vulkan` (golden MAE 0.00, Vulkan validation on) and `test_rhi_runtime_fallback_{default,forced,env_opengl}`. Each fallback case clears to magenta on the real window, reads the frame back through the chosen backend, and checks the centre pixel.
- `editor` runs on Vulkan by default and on OpenGL with `BREAK_RHI_FAIL_VULKAN=1`; the log shows `fallback(vulkan)` then `backend_selected(opengl, config-fallback)`.
- ASan + UBSan multi-backend tree: dispatch and selection unit tests and all three real-window fallback cases, zero reports. TSan: three reader threads against 20 000 table swaps, zero reports.
- Unit evidence: `test_rhi_dispatch` 44 checks, `test_rhi_runtime_select` 49 checks; mutations (dropped forwarder, missing rename, mis-routed forwarder, no fallback, ignored env, table not installed, failed create resetting a live device's table to the stub) all fail the tests.
- A failed create restores the previously installed table, so a later failing `rhi_device_create` does not strand a live device on the stub table.
- Real (non-hook) Vulkan failures also fall back cleanly on this host: missing ICD (`VK_ICD_FILENAMES=/nonexistent.json`, fails before the instance), invalid `RE_VK_DEVICE_INDEX` (fails after instance + surface), and an injected depth-memory allocation failure (fails after VkDevice + swapchain on the window). Each renders and reads back on OpenGL; ASan + UBSan report nothing beyond a 13 KB leak inside the Vulkan driver that a normal successful Vulkan run shows too.

Not verified: Windows and Wayland runtime fallback (no such host); CI. The `engine_demo` OpenGL shader link error noted at delivery (`vWorldPos` explicit location with no matching output) was a separate bug in `pbr_clustered_arr.vert` and is fixed (commit `1e09e998`); with `BREAK_RHI_FAIL_VULKAN=1` the full demo scene now runs on OpenGL. The slow GL runs measured at the time (60 frames in about 100 s) were an environment effect, not an engine cost: the GNOME session was screen-locked, and mutter/Xwayland throttles frame callbacks for invisible windows to 1 per second, which a vsync-on `glXSwapBuffers` waits on (a standalone GLX program shows the same 1 swap/s). With the screen unlocked, `engine_demo` on OpenGL runs at the 60 FPS vsync cap, also through the multi-backend forced fallback; Vulkan (MAILBOX present) is not throttled this way.
