# RHI 后端证据台账

- 冻结日期：2026-10-14（基线）；上位规格：`docs/superpowers/specs/2026-10-14-multi-backend-rhi-design.md` §2
- 证据等级（严格递增，升级必须有对应收据）：`NONE → COMPILED → HEADLESS → NATIVE_SURFACE → GPU_RUNTIME → BENCHMARK_COMPARABLE`
- 收据字段（每次等级变更必填，benchmark 类收据遵循 `docs/rhi_benchmark_receipt_schema.md`）：日期 / 机器 / GPU / 驱动版本 / 执行命令 / 结果（CI run URL 或本地 run 标识）
- 纪律：编译成功 ≠ GPU-runtime；模拟器证据只计入 COMPILED/HEADLESS；MoltenVK 证据不计入原生 Metal；Proton 只作兼容参考；headless stub（`engine_rhi_headless`）永不构成 GPU 证据。

## 基线矩阵（2026-10-14 冻结）

| 平台 × 后端 | 当前等级 | 依据 | 收据 |
|---|---|---|---|
| Linux X11 × OpenGL | GPU_RUNTIME | CI `gl` lane（Xvfb + 真 GL） | CI run：GitHub Actions `gl` job，2026-10-14 前最近一次 green run |
| Linux X11 × Vulkan | GPU_RUNTIME（lavapipe/llvmpipe，软渲染） | CI `vk` / `linux-graphics-smoke` lane | CI run：`vk` job 最近 green run |
| Linux Wayland × GL/VK | NATIVE_SURFACE | CI `wayland-gl` / `wayland-vk`（weston headless） | CI run：`wayland-*` job 最近 green run |
| Windows × Vulkan | GPU_RUNTIME（本机 + CI win32 runtime trio） | 本机 `build-win-vk/`、CI `windows-clang` | 本机：`cmake --build build-win-vk && ctest --test-dir build-win-vk -LE "graphics|fuzz"` 全绿（2026-10-14，Task 1 记录） |
| Windows × D3D12 | HEADLESS（contract/gate only） | `engine/src/rhi/rhi_d3d12.c/h` 仅编入 gate 测试，未接入 `RHIBackend` | 本机：`test_d3d12_*` gate 测试（2026-10-14） |
| macOS × Vulkan(MoltenVK) | GPU_RUNTIME | CI `macos-vulkan`（133/133 CTest, 2026-10-13） | CI run：`macos-vulkan` job，2026-10-13 |
| macOS/iOS × 原生 Metal | NONE | 无代码 | — |
| Android × Vulkan | COMPILED（host-injected ANativeWindow） | `engine/src/rhi/rhi_vk.c:1482-1700` | 源码审查记录（2026-10-14 冻结） |
| iOS × Vulkan(MoltenVK) | COMPILED（host-injected CAMetalLayer） | `engine/src/platform/platform_compat.h:86-95` | 源码审查记录（2026-10-14 冻结） |
| OHOS | NONE（UNAVAILABLE，fail-closed） | `engine/src/platform/platform_compat.h:111-120`；`engine/CMakeLists.txt:1073-1075` FATAL_ERROR | 契约测试 `test_platform_compat_harmonyos` |

## 变更规则

1. 等级升级必须在本表对应行更新「当前等级」并追加收据（日期/机器/GPU/驱动/命令/结果）。
2. 已知异常（如 NVIDIA 616.56 混合 GPU 的 `VK_ERROR_DEVICE_LOST` 与 Hi-Z {1,1}）只登记在规格 §7，不作为本表等级依据。
3. 本表由 `test_rhi_evidence_register`（`engine/tests/test_rhi_evidence_register.cmake`）做存在性与行完整性 gate。

## 本机冻结证据检查（opt-in）

`test_rhi_evidence_register` 对本机冻结证据文件（`<repo>/.scratch-vkprobe/` 目录与
`<repo>/engine/profile_trace.json`）的存在性检查**默认关闭**：fresh clone 与 CI 不携带这些
冻结产物，行完整性与证据等级 token 检查（可移植部分）始终执行。

在持有冻结证据的机器上启用方式（二选一）：

1. 通过 CMake cache 变量透传（推荐）：configure 时加
   `-DRHI_EVIDENCE_REQUIRE_LOCAL_FROZEN=ON`。`engine/CMakeLists.txt` 的测试注册区定义了
   `option(RHI_EVIDENCE_REQUIRE_LOCAL_FROZEN "..." OFF)` 并在
   `test_rhi_evidence_register` 注册行透传
   `-DRHI_EVIDENCE_REQUIRE_LOCAL_FROZEN=${RHI_EVIDENCE_REQUIRE_LOCAL_FROZEN}`，
   之后正常 `ctest` 即可。
2. 直接脚本调用：`ctest` 前手动运行
   `cmake -DREPO_ROOT=<repo> -DEVIDENCE_DOC=<repo>/docs/rhi_backend_evidence.md -DRHI_EVIDENCE_REQUIRE_LOCAL_FROZEN=ON -P engine/tests/test_rhi_evidence_register.cmake`。

## 收据追加（计划 B：WSI / Vulkan-first，2026-10-15）

| 日期 | 机器 | GPU / 驱动 | 命令 | 结果 |
|---|---|---|---|---|
| 2026-10-15 | 本机（Windows） | NVIDIA GeForce RTX 4060 Laptop / driver_version=2588573696（NVIDIA 解码 617.42） | `ctest --test-dir build-vk -R 'rhi_fault\|vk_alloc_fault\|isolation_gates\|vk_probe\|vk_surface_abi\|wsi\|platform_size' --output-on-failure` | 16/16 PASS；含 graphics 标签的 `test_rhi_vk_alloc_fault`（真 GPU 分配失败注入）与 `test_rhi_fault_injection`（out-of-date/device-lost/surface-loss 注入）→ Windows × Vulkan 维持 GPU_RUNTIME |
| 2026-10-15 | 本机（Windows） | 同上 | `rhi_swapchain_bench` → `build-vk/rhi_receipt_local.json`（Task 7 产出）；`cmake -DRECEIPT=build-vk/rhi_receipt_local.json -P engine/tests/test_rhi_benchmark_receipt_validate.cmake` | 收据校验通过：fps_avg=2120.57 / fps_p1=622.21 / frame_ms_avg=0.4716 / frame_ms_p99=1.6072，evidence_level=GPU_RUNTIME，runner=local |
| 2026-10-15 | 本机（Windows） | 同上 | `ctest --test-dir build-vk -R '^test_vulkan$' --output-on-failure` | init 日志行有效（`Vulkan GPU:`、`VK: swapchain present mode=IMMEDIATE images=3 vsync=off`；一次性探针实测 feature_bits=0x7、dynamic_rendering=1、synchronization2=1、device_type=2(discrete)、surface=B8G8R8A8_SRGB，探针已还原不入库）；graphics 段失败为本机已知环境性失败（混合 GPU 驱动，规格 §7 风险登记），不构成新收据、也不降级既有等级 |
| 2026-10-15 | — | — | `steam-deck-vulkan-benchmark` lane（`.github/workflows/ci.yml`） | 仓库变量 `ENABLE_GPU_LANES` 未开启（self-hosted runner 未上线）→ lane 存在但无运行收据；Linux X11/Wayland 的 WSI 接线仅有 token 级契约证据（`test_platform_wsi_wiring_contract` / `test_platform_wsi_lifecycle_*`，本机无 Linux 编译环境），各等级不变 |
