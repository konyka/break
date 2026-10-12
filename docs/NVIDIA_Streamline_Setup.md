# NVIDIA Streamline and DLSS Setup

The engine keeps DLSS optional. Portable builds use the existing direct/TSR
paths and do not require NVIDIA binaries.

## Source

The official NVIDIA Streamline source is fetched locally at:

```text
third_party/streamline
```

The source tree is intentionally ignored by Git. Streamline release artifacts
and DLSS feature DLLs are distributed separately by NVIDIA and must be obtained
from the official release page:

<https://github.com/NVIDIA-RTX/Streamline/releases>

Do not commit `sl.interposer.dll`, `nvngx_dlss.dll`, `nvngx_dlssd.dll`, or other
vendor binaries to this repository. Place approved production binaries in the
runtime packaging directory selected by the build integration, and retain the
corresponding NVIDIA license and signature information.

## Current Scope

- Streamline source is available locally for API and integration work.
- The current RHI exposes OpenGL and Vulkan, including read-only native Vulkan
  device, texture, and recording command-buffer queries. Renderer-owned
  resource-state transitions and post-evaluation command-state restoration are
  not yet exposed as a complete Streamline contract.
- DLSS runtime detection is enabled on Windows/NVIDIA builds, but DLSS image
  evaluation is not enabled yet. The current integration verifies the official
  runtime, initializes Streamline manually, passes native Vulkan handles, and
  queries adapter support; resource tagging and `slEvaluateFeature` remain
  blocked by the missing command-state restoration contract.
- Until the command-state contract and an approved Streamline release package
  are available, the engine must select direct or TSR fallback.

The current loader now passes the native Vulkan instance/device/physical-device
and graphics queue family through `slSetVulkanInfo` using Streamline's manual
hooking mode. Failed initialization is classified and fully torn down so a
later probe can retry; OpenGL/non-Windows paths remain fail-closed.

Actual DLSS evaluation is intentionally not claimed yet. Streamline Vulkan
tagging requires the native `VkImage`, `VkDeviceMemory`, `VkImageView`, image
layout, format, extent, and lifecycle for color/depth/motion-vector resources.
The RHI now exposes a narrow read-only `rhi_texture_get_native_info` API on
Vulkan (image, memory, view, Vulkan image layout, abstract format, native
Vulkan format, extent, mip count and layers);
OpenGL fails closed. The next implementation slice can use this data to build
the Streamline `Resource`/`ResourceTag` mirrors. A C-side resource-tag contract
validator now rejects placeholders and non-Vulkan resources. Actual
`slSetTagForFrame`/`slEvaluateFeature` calls still require the official C++
FrameToken/ViewportHandle ABI (or a small C++ bridge), real color/depth/
motion-vector/output textures, and verified layout transitions. No placeholder
Vulkan resource structs are passed to Streamline.

The final C++ ABI boundary is explicit in the source: an optional
`SLDlssCppAdapter` callback owns the official Streamline `FrameToken`,
`ViewportHandle`, `ResourceTag`, `slSetTagForFrame`, and `slEvaluateFeature`
objects. The C11 engine only validates native Vulkan resources and calls that
opaque adapter. Without an adapter, `sl_dlss_evaluate_tags` fails closed. This
avoids fabricating C++ virtual-object layouts in the C renderer and keeps
portable/OpenGL builds independent of the NVIDIA SDK.

No in-tree C++ adapter is shipped in this C11 repository. A product build must
provide that adapter from an SDK-licensed C++ integration target before DLSS
evaluation can be enabled.

When configured with `-DSTREAMLINE_ROOT=<sdk-root>` on Windows, the CMake build
creates `sl_dlss_streamline_adapter` and registers it after the C loader has
successfully initialized and validated DLSS. The adapter resolves the official
Streamline entry points from the already-loaded interposer; it does not link
against or copy NVIDIA runtime binaries.

The RHI now exposes a read-only `rhi_cmd_buffer_get_native_info` contract for
the currently recording command buffer; OpenGL and non-recording/headless
paths fail closed. The DLSS API provides
`sl_dlss_evaluate_tags_with_command_buffer`, which requires that native handle
before forwarding an evaluation request.

The legacy `sl_dlss_evaluate_tags` entry point is now deliberately disabled;
it never forwards a request without an explicit recording command buffer.

The current adapter target is still intentionally non-executable for Vulkan:
manual hooking also requires host command-state restoration, and the current
RHI does not expose that hook safely. The SDK adapter therefore returns false
rather than passing null command buffers. DLSS remains on TSR/native fallback
until the full command-state contract is implemented.

Because the command-buffer contract is missing, adapter creation also returns
false and the C loader does not register an inert callback as if DLSS execution
were available. The target currently serves as an SDK/ABI compile gate.

The adapter registration is cleared whenever Streamline initialization is
aborted or `sl_dlss_shutdown` runs, so no callback can retain an unloaded
interposer module.

The C11 validator also requires a defined image layout, non-zero native Vulkan
format, mip count, and array-layer count before a descriptor can reach the
adapter.

## Official Integration Constraints

Streamline requires initialization before graphics API use, Vulkan device
registration through `slSetVulkanInfo`, capability checks through
`slIsFeatureSupported`, and tagged color/depth/motion-vector resources before
`slEvaluateFeature`. The engine must also restore command state after feature
evaluation and verify NVIDIA signatures before loading signed production
plugins.

See the vendored source documentation for the exact API contract:

- `third_party/streamline/docs/ProgrammingGuideDLSS.md`
- `third_party/streamline/docs/ProgrammingGuideManualHooking.md`
- `third_party/streamline/license.txt`
