# Editor render debugger panel

Status: design (2026-10-26). Stage 4 subproject 6 ("render panel" — the last missing diagnostics panel). Precedents: `editor_panel_profiler.c`, `editor_panel_network.c` (`docs/design/editor_remote.md` §4).

## 1. Scope

A **pure-view** diagnostics panel in the editor's right column that answers "what is the renderer doing right now": which backend is running, on which GPU, with which capabilities, how the viewport pass behaved last frame, and how many RHI resource slots are in use.

Non-goals (NOT delivered): frame capture, per-draw inspection, shader/pipeline inspection, texture viewer, GPU timing queries, render settings or any control (it never changes rendering), remote render control (`editor_remote.md` §9).

## 2. Data sources (all read-only)

| Source | What | Read through |
|---|---|---|
| RHI device | backend, device name, vendor/device id, API/driver version | `rhi_device_get_info` |
| RHI device | capability summary (shader variant, compute, indirect, push constants, MSAA bits, present damage) | `rhi_device_get_capabilities` |
| RHI device | status (ready / lost), frame index | `rhi_device_get_status`, `rhi_frame_index` |
| RHI device | resource slots in use / capacity | new read-only `rhi_device_resource_usage` (core `rhi_resources.c`; counts from the existing free-list, no backend involvement) |
| Runtime selection | backend actually selected and why (`platform-default` / `explicit-env` / `config-fallback`) | `rhi_rollout_compiled_backend` / `rhi_rollout_compiled_reason` (runtime-aware since the fallback work) |
| Viewport pass | last frame: FBO size, entity proxies drawn, gizmo handles drawn, draw calls, init state (ready / failed / not attempted), skipped reason | new `break_editor_viewport3d_last_stats` (CPU counters the render function already has; no GPU readback) |

The panel never calls any `rhi_*` function that creates, destroys, binds, records or presents. A source-scan test pins that (same technique as the network panel).

## 3. Device ownership

The shell has no RHI device today (the dummy-PAL test path has none at all). `break_editor_shell_set_render_device(shell, device)` attaches a **borrowed** device; `editor_main` attaches it after creating the shell and detaches it before `rhi_device_destroy` (the existing shutdown order already destroys the shell first). With no device the panel shows exactly one row, `render: no device`.

## 4. Rows

Fixed storage, 16 rows x 96 bytes, no allocation on refresh:

```
[0] backend: <vulkan|opengl|metal|d3d12> (<reason>) status=<ready|lost|unknown> frame=<n>
[1] gpu: <device name, truncated>
[2] ids: vendor=0x<v> device=0x<d> api=<a> driver=<d>
[3] caps: shader=<glsl|glsl_vk|...> compute=<0|1> indirect=<0|1> push=<bytes>
[4] caps: msaa=0x<color bits> damage=<0|1> buffer_age=<0|1>
[5] resources: <used>/<capacity> slots
[6] viewport: <ready|failed|not-initialised> fbo=<w>x<h>
[7] viewport: proxies=<n> gizmo=<n> draws=<n> skipped=<reason|none>
```

## 5. Refresh and threading

At most 4 refreshes per second from `break_editor_shell_tick` (250 000 us), first tick after create or device attach/detach always refreshes, injectable clock for tests — identical to the network panel. Shell thread only; the device is borrowed on the same thread that renders.

## 6. Layout

Right column, under the network panel, `h:20%`. Widget names `editor-render-panel`, `editor-render-label`, `editor-render-list`.

## 7. Tests

- Headless (dummy PAL, no device): one `render: no device` row; layout under the network panel; row bounds; throttle; NULL safety; source scan (no mutating `rhi_*` calls).
- Headless with a fake device: `rhi_device_resource_usage` counts allocations and frees exactly (core-only test linked with `engine_rhi_headless`).
- Viewport stats: counters after `break_editor_viewport3d_render` on the headless path are deterministic (render is a guarded no-op without a device → `skipped=no-device`).
- Live (graphics, manual smoke): `editor` on Vulkan and on OpenGL (`BREAK_RHI_BACKEND=opengl`) — rows show the right backend, GPU name and non-zero draws; recorded as smoke evidence, not a ctest.
