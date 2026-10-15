# Vulkan 支持矩阵

证据等级定义与收据规则见 `docs/rhi_backend_evidence.md`；本表只列 Vulkan 形态的后端，原生 Metal/D3D12 见 `docs/rhi_metal_d3d12_feature_matrix.md`。

| 平台 | Vulkan 形态 | 证据等级 | 依据/收据 |
|---|---|---|---|
| Linux X11 | 原生 Vulkan | GPU_RUNTIME（lavapipe/llvmpipe 软渲染） | CI `vk` / `linux-graphics-smoke` lane |
| Linux Wayland | 原生 Vulkan | NATIVE_SURFACE | CI `wayland-vk`（weston headless） |
| Windows | 原生 Vulkan | GPU_RUNTIME | 本机 `build-win-vk/` + CI `windows-clang`（显式 `ENGINE_VULKAN=ON`） |
| macOS | MoltenVK | GPU_RUNTIME | CI `macos-vulkan`（显式 `ENGINE_VULKAN=ON`，133/133 CTest, 2026-10-13）；**不计入原生 Metal 证据** |
| iOS | MoltenVK（host-injected CAMetalLayer） | COMPILED | `engine/src/platform/platform_compat.h:86-95`；模拟器不计 GPU_RUNTIME |
| Android | 原生 Vulkan（host-injected ANativeWindow） | COMPILED | `engine/src/rhi/rhi_vk.c:1482-1700` |
| OHOS (HarmonyOS) | — | NONE（UNAVAILABLE，fail-closed） | `engine/CMakeLists.txt` harmonyos FATAL_ERROR |

## 说明

- Shader 路径：GLSL → SPIR-V，运行时 shaderc（target env Vulkan 1.2 / SPIR-V 1.5），见规格 §4.7。
- 软渲染（lavapipe/llvmpipe）收据必须在台账行内注明「软渲染」，不得与硬件 GPU 收据混用。
- 已知 NVIDIA 616.56 混合 GPU 异常的处理规则见文末「已知风险：NVIDIA 616.56 混合 GPU」节（与规格 §7 一致）；该异常不作为本表任何等级或数据行的依据。

## 已知风险：NVIDIA 616.56 混合 GPU

与规格 §7 风险登记一致，固定两条规则：

1. 该机器上的 `VK_ERROR_DEVICE_LOST` 与 Hi-Z {1,1} 异常**不作为源码修复依据**，必须在健康设备上独立复现后才可立项修复。
2. `TV_ONLY_PSHADOW`/`TV_ONLY_GBUFFER` 隔离门（`engine/src/test_vulkan.c:5600-5642`）**永久保留**，不得删除或并入 CI；由 `test_vulkan_isolation_gates` 契约测试钉死。

## 实测数据行（计划 B，2026-10-15）

填写纪律：禁止无收据填表。只有携带收据的 lane 填实测值；其余 lane 标注「本次无收据」，等级沿用首表，数据列待对应 CI 日志（`Vulkan GPU:` 与 `VK: swapchain present mode=` 两行，见 `rhi_vk.c`）补齐。`feature_bits` 位定义见 `rhi.h` `RHIFeatureBits`；`dynamic_rendering_supported`/`synchronization2_supported` 为迁移期「只探测不消费」字段（`rhi_vk.c` vk_init）。

| Lane | adapter（device_type / device_name） | surface format | present mode | feature_bits | dynamic_rendering | synchronization2 | 收据 |
|---|---|---|---|---|---|---|---|
| Windows（本机，GPU_RUNTIME） | discrete(2) / NVIDIA GeForce RTX 4060 Laptop GPU（driver_version=2588573696，NVIDIA 解码 617.42） | B8G8R8A8_SRGB(50) + SRGB_NONLINEAR(0) | IMMEDIATE（vsync=off，images=3） | 0x7（RAY_TRACING_PIPELINE \| RAY_QUERY \| ACCELERATION_STRUCTURE） | 1 | 1 | 2026-10-15 本机 `ctest --test-dir build-vk -R '^test_vulkan$'` 日志行（`Vulkan GPU:` / `VK: swapchain present mode=`）+ 一次性探针打印（feature_bits/device_type/surface format，取完即还原、不入库）+ `build-vk/rhi_receipt_local.json`（`rhi_swapchain_bench`，GPU_RUNTIME，经 `test_rhi_benchmark_receipt_validate` 校验） |
| Linux X11（CI `vk` / `linux-graphics-smoke`，lavapipe 软渲染） | 本次无收据 | 本次无收据 | 本次无收据 | 探测逻辑存在（`test_rhi_vk_probe` 全绿，COMPILED 级）+ 运行值待 CI 日志 | 同左 | 同左 | 本机无 Linux 编译环境；需 CI 日志两行 |
| Linux Wayland（CI `wayland-vk`，weston headless） | 本次无收据 | 本次无收据 | 本次无收据 | 同上 | 同上 | 同上 | 同上 |
| macOS MoltenVK（CI `macos-vulkan`） | 本次无收据 | 本次无收据 | 本次无收据 | 同上 | 同上 | 同上 | 同上 |

Metal native note: a GPU-wedge timeout can leave a submitted command buffer's
completion handler pending while teardown releases the Metal backend. This
requires a native macOS timeout test before claiming the timeout path safe;
Linux builds intentionally do not claim that coverage.
