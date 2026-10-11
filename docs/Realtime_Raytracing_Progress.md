# Real-Time Ray Tracing Progress

## Current Plan Status

The implementation is being delivered in Vulkan-first TDD slices. OpenGL keeps
the existing raster/TSR fallback and does not claim ray-tracing or DLSS support.

### Completed

- Confirmed the repository's RHI boundary: OpenGL and Vulkan backends, C11,
  CMake/CTest, and an existing TSR path.
- Obtained official NVIDIA Streamline source locally at
  `third_party/streamline` (v2.14.1). The source is ignored and is not bundled
  into the public repository.
- Added capability-driven render path selection for raster, TSR, and optional
  DLSS without selecting DLSS unless all vendor/runtime/API prerequisites exist.
- Added Vulkan native-device interop for Streamline integration boundaries.
- Added Vulkan acceleration-structure capability detection and an opaque,
  generation-safe BLAS/TLAS resource lifecycle.
- Added addressable AS-input buffer usage and a one-triangle BLAS build-size
  query.
- Added a one-triangle BLAS build recording path using the existing frame command
  buffer, with render-pass suspension and validation-gated smoke coverage.
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

| Platform | Toolchain | GPU / Driver | Config | Focused tests | test_vulkan | AS path |
|---|---|---|---|---|---|---|
| Windows | MSVC 19.51 | AMD Radeon iGPU (Vulkan) | GL + Vulkan | 4/4 pass | AS smoke pass, validation 0; pre-existing MSAA/golden failures | supported: lifecycle, size query (464/308), build recording |
| Linux (Fedora 44) | GCC 16.2 | Intel UHD (ANV) | GL + Vulkan | 4/4 pass | all passed, validation 0 | skip (no RT extensions) — fail-closed verified |
| Linux (Fedora 44) | GCC 16.2 | NVIDIA RTX A5000 Mobile (NVK/nouveau) | Vulkan | — | device created, early checks pass | skip (no RT extensions under NVK) — fail-closed verified on RTX hardware |
| macOS 26.7 (Apple M2) | Apple clang 21 | Apple M2 (MoltenVK) | Vulkan | 4/4 pass | all passed, validation 0, clean shutdown | skip (no RT extensions) — fail-closed verified |

The Linux and macOS runs used the local Vulkan SDKs already present on those
machines; the Fedora graphics runs attached to the existing Xwayland session.
No credentials or machine account details are stored in this repository.

A CMake linking fix surfaced by this sweep: `test_rhi_native` previously linked
platform graphics libraries only on Windows; it now mirrors the full platform
link matrix used by `test_rhi_capabilities` (GL/GLX/Wayland EGL, Vulkan, macOS
frameworks).

## Known Limitations

- The current Vulkan test selects the AMD Radeon integrated GPU. NVIDIA RTX
  hardware has been enumerated on the host but has not yet been selected for a
  dedicated RT/DLSS run. On Linux, the RTX A5000 currently runs the NVK/nouveau
  stack, which exposes no RT extensions; a proprietary-driver Linux run and a
  Windows RTX-selected run remain outstanding.
- The current implementation stops before TLAS construction, shader binding
  tables, ray-tracing pipeline creation, ray dispatch, traversal shaders, and
  image-quality validation of ray-traced output.
- DLSS is not integrated yet. `nvngx_dlss.dll` is not present on the host.
  Streamline/DLSS release binaries must be obtained from NVIDIA's official
  release distribution, kept external to the source repository, signature
  checked, and packaged only under approved license terms.
- Full `test_vulkan` still reports pre-existing failures on the Windows/AMD
  configuration in MSAA depth roundtrip and Vulkan golden-image drift. The same
  suite passes end-to-end (goldens included) on Linux/ANV and macOS/MoltenVK,
  which localizes those regressions to the Windows/AMD path; the new validation
  gate remains at zero everywhere.
- No performance claim is made yet. Real RTX performance, VRAM, frame time,
  and image-quality budgets require a selected NVIDIA adapter and repeatable
  benchmark scenes.

## Next TODO

1. Add triangle data upload and completion-safe resource lifetime for the BLAS
   build smoke path.
2. Select the NVIDIA RTX 4060 adapter explicitly on Windows and rerun Vulkan
   validation on the discrete GPU and hybrid-display configuration; separately,
   arrange a proprietary-driver Linux run on the RTX A5000 (NVK cannot expose
   RT extensions).
3. Add a minimal TLAS/instance contract only after the BLAS path is stable.
4. Add Vulkan ray-tracing pipeline, shader groups, SBT, and one traversal scene.
5. Integrate official Streamline Vulkan interop and optional DLSS Super
   Resolution behind capability/runtime checks.
6. Add deterministic RT-on/RT-off image captures and GPU timestamp/VRAM reports.
7. Revisit the existing MSAA depth and golden-image regressions separately; do
   not weaken those tests to make the RT feature pass.
8. Do not submit or push vendor DLLs, local SDK trees, build directories, probe
   files, or generated profiles.

## Dependency Policy

- Public Streamline source and notices may be referenced, but local SDK content
  remains external/ignored.
- DLSS and Streamline runtime binaries are not committed by this project.
- Portable builds must continue to work without NVIDIA runtime files.
- Unsupported hardware or missing runtime must fall back to TSR/native/raster
  rendering with an explicit diagnostic reason.
