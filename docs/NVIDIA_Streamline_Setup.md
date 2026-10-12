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
- The current RHI exposes OpenGL and Vulkan, but does not yet expose the native
  Vulkan handles and resource-state transitions required by Streamline.
- DLSS runtime detection is enabled on Windows/NVIDIA builds, but DLSS image
  evaluation is not enabled yet. The current integration verifies the official
  runtime, initializes Streamline manually, passes native Vulkan handles, and
  queries adapter support; resource tagging and `slEvaluateFeature` remain a
  separate implementation slice.
- Until the Vulkan interop layer and an approved Streamline release package are
  available, the engine must select direct or TSR fallback.

The current loader now passes the native Vulkan instance/device/physical-device
and graphics queue family through `slSetVulkanInfo` using Streamline's manual
hooking mode. Failed initialization is classified and fully torn down so a
later probe can retry; OpenGL/non-Windows paths remain fail-closed.

Actual DLSS evaluation is intentionally not claimed yet. Streamline Vulkan
tagging requires the native `VkImage`, `VkDeviceMemory`, `VkImageView`, image
layout, format, extent, and lifecycle for color/depth/motion-vector resources.
The RHI now exposes a narrow read-only `rhi_texture_get_native_info` API on
Vulkan (image, memory, view, layout, format, extent, mip count and layers);
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
