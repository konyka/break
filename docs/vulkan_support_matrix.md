# Vulkan 支持矩阵

证据等级定义与收据规则见 `docs/rhi_backend_evidence.md`；本表只列 Vulkan 形态的后端，原生 Metal/D3D12 见 `docs/rhi_metal_d3d12_feature_matrix.md`。CI lane 名为计划 F Task 7 后的六类 lane（`.github/workflows/ci.yml`），最近全绿 run：https://github.com/konyka/break/actions/runs/38990768014 （@3c92a06b，2026-10-17，含 `evidence-receipt-*` 收据 artifact）。

## 最低版本与已用扩展（实际实现，`engine/src/rhi/rhi_vk.c`）

- **最低 Vulkan 版本 = 1.2**：instance `apiVersion = VK_API_VERSION_1_2`（rhi_vk.c vk_init）；shaderc 运行时编译 target env `vulkan 1.2` / SPIR-V 1.5（`shaderc_compile_options_set_target_env`），两端对齐。
- **实例扩展**：`VK_KHR_surface` + 平台 WSI 扩展（由 `platform_vk_required_instance_extensions` 按平台提供：X11=`VK_KHR_xcb_surface`、Wayland=`VK_KHR_wayland_surface`、Windows=`VK_KHR_win32_surface`、macOS(MoltenVK)=`VK_EXT_metal_surface`、Android=`VK_KHR_android_surface`）；可选 `VK_EXT_debug_utils`（存在才启用，R438 validation 消息计数）；`VK_EXT_validation_features` 仅在 `BREAK_VK_SYNC_VALIDATION=1` 时请求（同步验证）。
- **设备扩展**：`VK_KHR_swapchain`（必需，缺失 FATAL）；ray-tracing 组（可选，探测 feature_bits 后启用）：`VK_KHR_acceleration_structure`、`VK_KHR_ray_tracing_pipeline`、`VK_KHR_ray_query`、`VK_KHR_deferred_host_operations`、`VK_KHR_pipeline_library`；`VK_KHR_portability_subset`（设备报告即强制启用，缺失且需要时报 FATAL）；`VK_EXT_device_fault`（可选，R576 vendor fault forensics）。
- **只探测不消费**（capability 迁移期字段，`dynamic_rendering_supported` / `synchronization2_supported`）：`VK_KHR_dynamic_rendering`、`VK_KHR_synchronization2`。

## 平台矩阵

| 平台 | Vulkan 形态 | 最低 Vulkan | 证据等级 | 收据 | 已知限制 |
|---|---|---|---|---|---|
| Linux X11 | 原生（Xcb surface） | 1.2 | GPU_RUNTIME（CI lavapipe **软渲染** + 本机真 GPU） | CI `lane-gpu-runtime-linux-vk`（run 38990768014，收据注明 lavapipe）+ validation lane `lane-validation-linux-vk`；本机真 GPU 见台账 Windows 行注（test_vulkan 日志） | CI 侧为 **software-rendering（lavapipe/llvmpipe），不计入硬件 GPU 证据**；台账行内必须注明软渲染 |
| Linux Wayland | 原生（`VK_KHR_wayland_surface`，weston headless） | 1.2 | NATIVE_SURFACE | CI `lane-native-surface-wayland`（run 38990768014） | weston headless compositor（无 GPU 断言）；兼容期另有 `wayland-gl` lane（GL，DEPRECATED） |
| Windows | 原生（Win32 surface；D3D12 已是首选后端，Vulkan 为 fallback 形态） | 1.2 | GPU_RUNTIME + BENCHMARK_COMPARABLE（本机真 GPU benchmark 收据） | 本机 `build-vk/`（RTX 4060 Laptop，`rhi_receipt_local.json` + `docs/receipts/rhi_receipt_windows_vulkan_planf.json` 基线）；CI `lane-headless-windows-clang`（headless 面） | 本机 NVIDIA 混合 GPU 环境性 DEVICE_LOST（规格 §7 登记，见下「已知风险」） |
| macOS | MoltenVK（`VK_EXT_metal_surface`） | 1.2（loader） | GPU_RUNTIME | 本机 M2 133/133（2026-10-13，台账）；CI `lane-native-surface-cocoa`（run 38990768014） | **不计入原生 Metal 证据**（原生 Metal 见特性矩阵文档） |
| iOS | MoltenVK（host-injected CAMetalLayer） | 1.2 | COMPILED | `engine/src/platform/platform_compat.h`（源码审查，2026-10-14 冻结） | 模拟器不计 GPU_RUNTIME；无真机收据（OpenGL 删除闸门 BLOCKED 原因之一） |
| Android | 原生（host-injected `ANativeWindow`，`VK_KHR_android_surface`） | 1.2 | COMPILED | `engine/src/rhi/rhi_vk.c`（host-injected 路径，源码审查） | 需 `ENGINE_ANDROID_NATIVE_WINDOW=ON`；无仓库 runtime/CI 收据 |
| OHOS (HarmonyOS) | — | — | NONE（UNAVAILABLE，fail-closed） | `engine/CMakeLists.txt` harmonyos FATAL_ERROR；`test_platform_compat_harmonyos` | native surface 存在前保持不可用 |
| Proton (Wine/vkd3d-proton) | 兼容层（D3D12 契约在 vkd3d-proton 上的兼容验证） | 1.2（vkd3d-proton 要求 ≥1.3 的功能子集按需） | compat-verified（**兼容参考，不计入 Windows 原生证据**） | `proton-d3d12.yml` workflow；CI `lane-proton`（steamrt sniper 钉 digest 容器构建，周跑，收据 `evidence-receipt-proton`） | 等级不进本表任何行；仅回归兼容面 |
| Steam Deck | 原生（真 GPU，X11/Wayland） | 1.2 | GPU_RUNTIME + BENCHMARK_COMPARABLE（lane 预期；runner 未上线） | `lane-benchmark-steam-deck-vk`（`ENABLE_GPU_LANES` 门控 self-hosted runner；bench 收据 + 生成器重建 BENCHMARK_COMPARABLE 收据） | 当前 `ENABLE_GPU_LANES` 未置值 → lane skipped、无运行收据（诚实标注，不虚报） |

## 已知风险：NVIDIA 616.56 混合 GPU

与规格 §7 风险登记一致，固定两条规则：

1. 该机器上的 `VK_ERROR_DEVICE_LOST` 与 Hi-Z {1,1} 异常**不作为源码修复依据**，必须在健康设备上独立复现后才可立项修复。
2. `TV_ONLY_PSHADOW`/`TV_ONLY_GBUFFER` 隔离门（`engine/src/test_vulkan.c:5600-5642`）**永久保留**，不得删除或并入 CI；由 `test_vulkan_isolation_gates` 契约测试钉死。

## 实测数据行（计划 B，2026-10-15）

填写纪律：禁止无收据填表。只有携带收据的 lane 填实测值；其余 lane 标注「本次无收据」，等级沿用上表，数据列待对应 CI 日志（`Vulkan GPU:` 与 `VK: swapchain present mode=` 两行，见 `rhi_vk.c`）补齐。`feature_bits` 位定义见 `rhi.h` `RHIFeatureBits`；`dynamic_rendering_supported`/`synchronization2_supported` 为迁移期「只探测不消费」字段（`rhi_vk.c` vk_init）。

| Lane | adapter（device_type / device_name） | surface format | present mode | feature_bits | dynamic_rendering | synchronization2 | 收据 |
|---|---|---|---|---|---|---|---|
| Windows（本机，GPU_RUNTIME） | discrete(2) / NVIDIA GeForce RTX 4060 Laptop GPU（driver_version=2588573696，NVIDIA 解码 617.42） | B8G8R8A8_SRGB(50) + SRGB_NONLINEAR(0) | IMMEDIATE（vsync=off，images=3） | 0x7（RAY_TRACING_PIPELINE \| RAY_QUERY \| ACCELERATION_STRUCTURE） | 1 | 1 | 2026-10-15 本机 `ctest --test-dir build-vk -R '^test_vulkan$'` 日志行（`Vulkan GPU:` / `VK: swapchain present mode=`）+ 一次性探针打印（feature_bits/device_type/surface format，取完即还原、不入库）+ `build-vk/rhi_receipt_local.json`（`rhi_swapchain_bench`，GPU_RUNTIME，经 `test_rhi_benchmark_receipt_validate` 校验） |
| Linux X11（CI `lane-gpu-runtime-linux-vk`，lavapipe **软渲染**） | 本次无收据 | 本次无收据 | 本次无收据 | 探测逻辑存在（`test_rhi_vk_probe` 全绿，COMPILED 级）+ 运行值待 CI 日志 | 同左 | 同左 | 本机无 Linux 编译环境；需 CI 日志两行（软渲染值不计入硬件 GPU 证据） |
| Linux Wayland（CI `lane-native-surface-wayland`，weston headless） | 本次无收据 | 本次无收据 | 本次无收据 | 同上 | 同上 | 同上 | 同上 |
| macOS MoltenVK（CI `lane-native-surface-cocoa`） | 本次无收据 | 本次无收据 | 本次无收据 | 同上 | 同上 | 同上 | 同上 |

Metal native note: a GPU-wedge timeout can leave a submitted command buffer's
completion handler pending while teardown releases the Metal backend. This
requires a native macOS timeout test before claiming the timeout path safe;
Linux builds intentionally do not claim that coverage.
