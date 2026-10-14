# Vulkan 支持矩阵

证据等级定义与收据规则见 `docs/rhi_backend_evidence.md`；本表只列 Vulkan 形态的后端，原生 Metal/D3D12 见 `docs/rhi_metal_d3d12_feature_matrix.md`。

| 平台 | Vulkan 形态 | 证据等级 | 依据/收据 |
|---|---|---|---|
| Linux X11 | 原生 Vulkan | GPU_RUNTIME（lavapipe/llvmpipe 软渲染） | CI `vk` / `linux-graphics-smoke` lane |
| Linux Wayland | 原生 Vulkan | NATIVE_SURFACE | CI `wayland-vk`（weston headless） |
| Windows | 原生 Vulkan | GPU_RUNTIME | 本机 `build-win-vk/` + CI `windows-clang` |
| macOS | MoltenVK | GPU_RUNTIME | CI `macos-vulkan`（133/133 CTest, 2026-10-13）；**不计入原生 Metal 证据** |
| iOS | MoltenVK（host-injected CAMetalLayer） | COMPILED | `engine/src/platform/platform_compat.h:86-95`；模拟器不计 GPU_RUNTIME |
| Android | 原生 Vulkan（host-injected ANativeWindow） | COMPILED | `engine/src/rhi/rhi_vk.c:1482-1700` |
| OHOS (HarmonyOS) | — | NONE（UNAVAILABLE，fail-closed） | `engine/CMakeLists.txt` harmonyos FATAL_ERROR |

## 说明

- Shader 路径：GLSL → SPIR-V，运行时 shaderc（target env Vulkan 1.2 / SPIR-V 1.5），见规格 §4.7。
- 软渲染（lavapipe/llvmpipe）收据必须在台账行内注明「软渲染」，不得与硬件 GPU 收据混用。
- 已知 NVIDIA 616.56 混合 GPU 异常只登记在规格 §7，不进入本表。
