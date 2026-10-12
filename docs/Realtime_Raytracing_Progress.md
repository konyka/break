# Real-Time Ray Tracing Progress

## Current Plan Status

The implementation is being delivered in Vulkan-first TDD slices. OpenGL keeps
the existing raster/TSR fallback and does not claim ray-tracing or DLSS support.

### Completed

- Confirmed the repository's RHI boundary: OpenGL and Vulkan backends, C11,
  CMake/CTest, and an existing TSR path.
- Obtained official NVIDIA Streamline source locally at
  `third_party/streamline` (v2.14.1) plus the official release runtime at
  `third_party/streamline-bin/v2.14.1` (selective extraction, gitignored).
  Neither is bundled into the public repository.
- Added capability-driven render path selection for raster, TSR, and optional
  DLSS without selecting DLSS unless all vendor/runtime/API prerequisites exist.
- Added Vulkan native-device interop for Streamline integration boundaries.
- Vulkan device selection now prefers discrete GPUs (hybrid laptops no longer
  pin the integrated adapter); `RE_VK_DEVICE_INDEX` still overrides explicitly.
- Added Vulkan acceleration-structure capability detection and an opaque,
  generation-safe BLAS/TLAS resource lifecycle.
- Added addressable AS-input buffer usage and one-triangle BLAS build-size
  query.
- Builds are one-shot submissions (private command buffer + queue wait), so
  acceleration structures are complete and inputs safely destroyable on
  return; AS storage buffers carry device-address usage and memory flags.
- Added a TLAS one-instance path: stable 64-byte instance record encoding
  (pure, headless-tested), BLAS device-address query, TLAS size query, and
  one-shot TLAS build.
- Verified on the RTX 4060 Laptop GPU: BLAS sizes (AS=2560, scratch=1920),
  geometry-backed BLAS build, and one-instance TLAS build all pass with the
  validation gate at zero.
- Added an opt-in ray-tracing trace probe (`rt_trace`, gated behind
  `BREAK_RT_TRACE=1`): full ray-tracing pipeline, SBT, and one-pixel readback
  machinery with verified raygen execution; see the TODO list for the open
  `traceRayEXT` dispatch investigation.
- Integrated a C-mirrored Streamline 2.14.1 loader (`sl_dlss`): dynamic
  `sl.interposer.dll` load, `slInit` with a DLSS feature request, adapter-
  scoped `slIsFeatureSupported`, classified fail-closed reasons, and safe
  shutdown. Headless contract test covers the missing-runtime path. On the
  RTX 4060 the probe reports DLSS supported on the adapter (all plugins pass
  NVIDIA signature verification).
- The accepted cross-platform architecture is now explicit: Vulkan is the
  only backend allowed to select RT/DLSS; OpenGL remains direct/TSR/raster
  fallback and never loads NVIDIA runtime DLLs. Vulkan RT has reached the
  isolated RTX pixel milestone; Vulkan DLSS is still detection/initialization
  only, not frame evaluation.
- Added focused GL and Vulkan RHI tests and retained explicit fallback behavior.

## Verified Results

The following focused tests pass in both GL and Vulkan configurations:

- `test_rhi_capabilities`
- `test_rhi_native`
- `test_render_features`
- `test_shader_io` (Vulkan configuration)

On the available Vulkan device, the smoke test currently reports:

- unbuilt BLAS/TLAS lifecycle: pass;
- one-triangle BLAS size query: pass (`AS=464`, `scratch=308` on the test device);
- one-triangle BLAS build recording: pass;
- Vulkan validation messages: `0`.

## Cross-Platform Validation Matrix

| Platform | Toolchain | GPU / Driver | Display | Config | Focused tests | test_vulkan | AS path |
|---|---|---|---|---|---|---|---|
| Windows | MSVC 19.51 | AMD Radeon iGPU (Vulkan) | Win32 | GL + Vulkan | 4/4 pass | AS smoke pass, validation 0; pre-existing MSAA/golden failures | supported: lifecycle, size query, build |
| Windows | MSVC 19.51 | NVIDIA RTX 4060 (proprietary) | Win32 | Vulkan | 4/4 pass | AS + TLAS pass (2560/1920), DLSS probe supported, gate 0 | full BLAS + TLAS builds; DLSS runtime detected |
| Linux (Fedora 44, GNOME Wayland) | GCC 16.2 | Intel UHD (ANV) | native Wayland | GL + Vulkan | 4/4 pass each | all passed, gate 0 | skip (no RT extensions) — fail-closed verified |
| Linux (Fedora 44, GNOME Wayland) | GCC 16.2 | NVIDIA RTX A5000 (NVK/nouveau) | native Wayland | Vulkan | 4/4 pass | all passed, gate 0 | skip (no RT extensions under NVK) — fail-closed verified on RTX hardware |
| macOS 26.7 (Apple M2) | Apple clang 21 | Apple M2 (MoltenVK) | Cocoa | Vulkan | 4/4 pass | all passed, gate 0, clean shutdown | skip (no RT extensions) — fail-closed verified |

Linux display note: the Fedora desktop is a native GNOME Wayland session; the
Wayland rows above run `ENGINE_ENABLE_WAYLAND=ON` against
`window_wayland.c` + `VK_USE_PLATFORM_WAYLAND_KHR` directly on
`wayland-0` (no Xwayland). Earlier exploratory runs on the same host went
through the Xwayland compatibility layer (`DISPLAY=:0` + the mutter Xwayland
authority) and produced the same pass/fail-closed results; the matrix records
the native-path runs. `test_sl_dlss` runs only on Windows; on Linux the DLSS
probe correctly reports unavailable.

The Linux and macOS runs used the local Vulkan SDKs already present on those
machines. No credentials or machine account details are stored in this
repository.

A CMake linking fix surfaced by this sweep: `test_rhi_native` previously linked
platform graphics libraries only on Windows; it now mirrors the full platform
link matrix used by `test_rhi_capabilities` (GL/GLX/Wayland EGL, Vulkan, macOS
frameworks).

## Known Limitations

- **AMD Windows driver limitations (integrated GPU, fully diagnosed)**:
  1. `accelerationStructureHostCommands` is not supported. The engine queries
     this feature at init and only attempts host builds when supported;
     otherwise it falls back to device builds.
  2. `VK_FORMAT_R32G32B32A32_SFLOAT` lacks the
     `VK_FORMAT_FEATURE_ACCELERATION_STRUCTURE_VERTEX_BUFFER_BIT_KHR` buffer
     feature. `VK_FORMAT_R32G32B32_SFLOAT` is the correct format (confirmed
     by clean validation).
  3. Device-side `vkCmdBuildAccelerationStructuresKHR` "succeeds" (submit +
     wait return VK_SUCCESS) but produces an AS the hardware cannot traverse.
     Buffer data is confirmed correct via readback; device addresses are valid
     GPU VAs; build-size queries and validation are clean. Direct BLAS tracing
     is not a legal diagnostic (VUID 03579), so only TLAS tracing is retained.
- Device teardown on the NVIDIA Windows driver intermittently emits four
  "object in use by command buffer" validation messages from legacy
  pipeline/buffer destroys; `rhi_device_destroy` now waits frame fences and
  resets command buffers first, and the AS/DLSS paths themselves stay at zero.
  Same suite is deterministically clean on AMD, Intel/ANV, NVK, and MoltenVK.
- The first ray-traced pixel remains blocked: RT pipeline, SBT, raygen shader
  execution, miss shader dispatch, and image readback are all verified working
  end-to-end. The miss shader dispatches correctly (blue pixel on AMD proves
  the full pipeline works), but the BLAS built by the AMD device-side path
   contains no traceable geometry. NVIDIA RTX 4060 validation is now healthy
   after reboot, but the device-side AS build still produces an untraversable
   structure; the ray-query probe returns no committed hit before the driver
   enters the known DEVICE_LOST path.
- The RT probe now uses the correct `rayPayloadInEXT` qualifier for miss and
  closest-hit stages (the previous `rayPayloadEXT` declaration was invalid for
  those receiving stages). `BREAK_RT_ONLY=1` provides a short, isolated RT
  lifecycle/teardown mode for future driver experiments without running the
  full graphics suite.
- RTX 4060 capability probing confirms all three required device features:
  `RHI_FEATURE_ACCELERATION_STRUCTURE=1`,
  `RHI_FEATURE_RAY_TRACING_PIPELINE=1`, and `RHI_FEATURE_RAY_QUERY=1`.
  The validation gate remains zero. A compute `rayQueryEXT` probe is now wired
  through the existing compute RHI: dedicated set-4 AS binding, AS descriptor
  pool capacity, shader compilation, dispatch, and host readback. It executes
  and reads `0x00000000` (no committed intersection) before the NVIDIA device
  enters its known DEVICE_LOST state, consistent with the device-side AS build
  producing an untraversable structure.
- The Vulkan device audit now reports a stable runtime matrix in the graphics
  suite: on the current RTX host, `NVIDIA GeForce RTX 4060 Laptop GPU`, vendor
  `0x10de`, device `0x28a0`, Vulkan API `1.4.351`, driver `0x9a4a8000`, and
  AS/RTP/RQ feature bits all enabled. This is runtime-reported data, not a
  hard-coded device table.
- DLSS is detection-only: `slInit`/`slIsFeatureSupported` report support, but
   `slSetVulkanInfo` currently returns an internal loader error when called in
   the full raw-Vulkan test process; resource tagging and `slEvaluateFeature`
   are not wired. The probe is opt-in (`BREAK_DLSS_PROBE=1`) because Streamline
   can create additional Vulkan/plugin state. A standalone Streamline probe
   process is the next safe integration step. The SL `Preferences.projectId`
   currently uses a placeholder engine identifier; an NVIDIA-issued
   project/application id is required before shipping (see the DLSS license's
  notification requirement).
- The DLSS API loader now exposes an explicit ready/unavailable status and
  fully resets it on failed initialization. Actual resource tagging remains
  intentionally deferred: the RHI must first expose native Vulkan image/view,
  memory, layout, format, extent, and lifecycle information for color, depth,
  motion-vector, and output resources. Passing incomplete placeholders to
  Streamline is not accepted as DLSS support.
- Linux RTX A5000 still runs NVK/nouveau. Secure Boot is disabled and the
  `akmod-nvidia` install path is prepared, but the provided login credential
  is not a sudo credential on that host, so the driver install and reboot
  need either a sudo-capable credential or an on-host manual
  `dnf install akmod-nvidia xorg-x11-drv-nvidia-cuda` + reboot.
- Latest Fedora check confirms the same state: `nouveau` is loaded, neither
  `akmod-nvidia` nor `kmod-nvidia` is installed, and the SSH account has no
  non-interactive sudo permission. No remote system change was attempted; a
  root-capable on-host installation remains required for proprietary-driver
  RT validation.
- Full `test_vulkan` still reports pre-existing failures on the Windows/AMD
  configuration in MSAA depth roundtrip and Vulkan golden-image drift. The same
  suite passes end-to-end (goldens included) on Linux/ANV and macOS/MoltenVK,
  which localizes those regressions to the Windows/AMD path; the new validation
  gate remains at zero everywhere the teardown issue above does not fire.
- No performance claim is made yet. Real RTX performance, VRAM, frame time,
  and image-quality budgets require a selected NVIDIA adapter and repeatable
  benchmark scenes.

## Next TODO

1. **First ray-traced pixel: COMPLETE in isolated RTX validation.** The full RT
   pipeline (raygen/miss/closest-hit
   shaders, SBT with verified non-zero handles, descriptor set, traceRayEXT
   submission) is proven working — the raygen shader executes and the miss
   shader dispatches on AMD (blue). On the RTX 4060, `BREAK_RT_ONLY=1` plus
   `BREAK_RT_TRACE=1` returned `TRACE tlas -> {0,255,0,255} HIT(green)` and
   `RT-only result: PASS`; the full isolated path has therefore produced the
   first real ray-traced pixel. The normal full suite can still hit the
   machine's legacy multi-instance fence/DEVICE_LOST issue after the RT-only
   result; that is separate from the isolated RT proof. Earlier runs where
   `traceRayEXT` did not dispatch were caused by the device-side AS build producing
   a structurally invalid BVH: both AMD and NVIDIA neither report
   `accelerationStructureHostCommands` support (dual-path falls to device
   build), and the device-side build submits/completes without error but
   produces an AS the hardware cannot traverse. Capability probing confirms
   `RHI_FEATURE_RAY_QUERY=1` on RTX. The compute probe is implemented and
   bypasses the RT pipeline entirely; its current result remains no committed
   hit when the device-side AS is invalid,
   (b) update the NVIDIA driver (616.56 may have a WDDM AS build bug),
   (c) test on a discrete non-hybrid NVIDIA system.
2. Wire `slSetVulkanInfo` from `RHINativeDevice`, then DLSS resource tagging
   and `slEvaluateFeature` behind the existing capability gate (obtain an
   NVIDIA project id for anything beyond local development).
3. Add RT-on/RT-off image captures and GPU timestamp/VRAM reporting once the
   trace path is resolved.
4. Install the NVIDIA proprietary driver on the Fedora host (needs a sudo
   credential or on-host action), reboot, and rerun the RT suite on the
   RTX A5000.
5. Revisit the intermittent NVIDIA teardown validation messages and the
   Windows/AMD MSAA depth + golden-image regressions separately; do not weaken
   those tests to make the RT feature pass.
6. Do not submit or push vendor DLLs, local SDK trees, build directories, probe
   files, or generated profiles.

## Dependency Policy

- Public Streamline source and notices may be referenced, but local SDK content
  remains external/ignored.
- DLSS and Streamline runtime binaries are not committed by this project.
- Portable builds must continue to work without NVIDIA runtime files.
- Unsupported hardware or missing runtime must fall back to TSR/native/raster
  rendering with an explicit diagnostic reason.

- Native texture interop is now available as a read-only Vulkan audit (image, memory, view, layout, format, extent, mip count and layers); OpenGL fails closed. This enables the next ResourceTag slice but DLSS evaluation still requires real renderer color/depth/motion-vector/output resources and verified layout transitions.


- Added a fail-closed DLSS ResourceTag contract validator for Vulkan native texture metadata and the four required SR resource classes. Actual Streamline calls still need a small C++ ABI bridge for FrameToken/ViewportHandle and renderer-owned color/depth/motion-vector/output resources; no placeholder tags are emitted.


- Added an opaque C++ adapter boundary for future DLSS evaluation: the C11 renderer validates ResourceTag descriptors but never fabricates Streamline FrameToken/ViewportHandle virtual objects. Without an official SDK-backed adapter, evaluation fails closed; OpenGL remains independent.
- Added an optional Windows `STREAMLINE_ROOT` CMake target that compiles the
  SDK-backed C++ adapter and registers it only after the C loader validates the
  runtime and DLSS support. The adapter resolves `slGetNewFrameToken`,
  `slSetTagForFrame`, `slDLSSSetOptions`, and `slEvaluateFeature` from the
  loaded interposer; default builds do not include the SDK or NVIDIA binaries.
  It rejects tags requiring an unprovided command buffer, so real renderer
  resource-state transitions remain a prerequisite for enabling evaluation.


- Native texture interop now also reports the native Vulkan format separately from the abstract RHI format, allowing Streamline Resource construction to preserve the Vulkan ABI value.

