# 多后端 RHI 迁移设计规格（Vulkan / Metal / D3D12 / OpenGL 退役）

> **2026-10-26 决定（取代下文关于 OpenGL 退役/删除的全部表述）**：OpenGL 长期保留，作为 `fallback_chain` 的最后一级降级方案和跨后端渲染效果对比基准，不再计划移除。下文 "退役/删除/兼容迁移期" 等措辞与 §6 删除条件保留为历史记录，不再是计划。当前策略与执行见 `docs/rhi_rollback_runbook.md` 与契约测试 `test_rhi_rollout_config_contract`、`test_rhi_golden_parity`。

- 日期：2026-10-14
- 状态：已批准（auto 模式，决策依据用户提供的完整目标方案）
- 范围：PureCEngine 渲染硬件接口（RHI）从「编译期二选一（OpenGL/Vulkan）」迁移为「编译期多后端、每 runtime 单后端」，最终在新 major release 中删除 OpenGL。

## 1. 目标与非目标

### 1.1 目标后端矩阵

| 平台 | 目标后端 | 证据要求 |
|---|---|---|
| Android | Vulkan | native-surface + GPU-runtime |
| Linux / Steam Deck / Linux Steam | Vulkan | native-surface + GPU-runtime + benchmark-comparable |
| macOS / iOS | 原生 Metal（MTLDevice/MTLCommandQueue/CAMetalLayer） | native-surface + GPU-runtime（真机） |
| Windows / Steam Windows | 原生 D3D12（DXGI/D3D12/DRED） | native-surface + GPU-runtime + benchmark-comparable |
| Proton | 仅作兼容验证路径 | 独立 CI lane，不计入 Windows D3D12 证据 |
| OHOS (HarmonyOS) | UNAVAILABLE（fail-closed） | 直到存在真实 native surface |
| OpenGL | 兼容迁移期保留 | 全部原生后端认证后于新 major release 删除 |

### 1.2 非目标

- 不引入运行时后端热切换（vtable 动态分发）。性能最优决策：保持编译期单后端、直接符号链接，函数调用零额外开销。
- 不用 MoltenVK 冒充原生 Metal 证据；不用 D3D11On12 或 OpenGL wrapper 冒充 D3D12。
- 不把编译成功（compiled）误报为 GPU-runtime。证据等级严格分离。
- 模拟器证据只能证明 compile/lifecycle，不能证明 GPU-runtime。

## 2. 证据等级模型（沿用现有体系）

代码：`engine/src/platform/platform_compat.h:49-56` `EngineSupportEvidenceLevel`：
`NONE → COMPILED → HEADLESS → NATIVE_SURFACE → GPU_RUNTIME → BENCHMARK_COMPARABLE`。

每个平台 × 后端组合必须在证据台账（`docs/rhi_backend_evidence.md`）中记录当前等级与收据（CI run / 本地 run 的日期、机器、GPU、驱动、命令、结果）。升级等级必须有对应收据；收据格式遵循 benchmark receipt schema（见 §8.3）。

### 2.1 当前已知证据基线（2026-10-14 冻结）

| 平台 × 后端 | 当前等级 | 依据 |
|---|---|---|
| Linux X11 × OpenGL | GPU-runtime | CI `gl` lane（Xvfb + 真 GL） |
| Linux X11 × Vulkan | GPU-runtime（lavapipe/llvmpipe，软渲染） | CI `vk` / `linux-graphics-smoke` lane |
| Linux Wayland × GL/VK | native-surface | CI `wayland-gl` / `wayland-vk`（weston headless） |
| Windows × Vulkan | GPU-runtime（本机 + CI win32 runtime trio） | `build-win-vk/`、CI `windows-clang` |
| Windows × D3D12 | HEADLESS（contract/gate only） | `rhi_d3d12.c/h` 仅编入 gate 测试，未接入 `RHIBackend` |
| macOS × Vulkan(MoltenVK) | GPU-runtime | CI `macos-vulkan`（133/133 CTest, 2026-10-13） |
| macOS/iOS × 原生 Metal | NONE | 无代码 |
| Android × Vulkan | COMPILED（host-injected ANativeWindow） | `rhi_vk.c:1482-1700` |
| iOS × Vulkan(MoltenVK) | COMPILED（host-injected CAMetalLayer） | `platform_compat.h:86-95` |
| OHOS | NONE（UNAVAILABLE, fail-closed） | `platform_compat.h:111-120`；`engine/CMakeLists.txt:1073-1075` FATAL_ERROR |

注意：NVIDIA 616.56 混合 GPU 机器上的 `VK_ERROR_DEVICE_LOST` 与 Hi-Z {1,1} 异常**不能**直接作为源码修复依据，必须在健康设备上独立复现后才可立项修复（见 §7 风险登记）。

## 3. 现状关键事实（探索结论，2026-10-14）

1. `rhi.h`（871 行）是唯一公开 API；C 语言、编译期切换：`rhi.c:408-415` unity-include 恰好一个后端（`ENGINE_VULKAN → rhi_vk.c`，否则 `rhi_gl.c`）。两后端导出相同 `rhi_*` 符号，永远不能同时链接——这正好满足「每个 runtime build 只链接一个 native backend」。
2. `rhi.h` 中的 Vulkan 泄漏点（需中性化）：
   - `RHIPipelineDesc` 的 push-constant 布局布尔（`terrain_layout`/`water_layout`/`combined_aa_layout`/`combined_color_layout`，rhi.h:260-265）与 render-pass 兼容字段（rhi.h:266-281）；
   - `rhi_cmd_push_constants`（对齐 `vkCmdPushConstants` 语义，rhi.h:573-580）、`rhi_push_range_fits`/`rhi_push_helper_range_ok`；
   - `rhi_pipeline_get_uniform_location` 在 VK 下返回 push-constant 字节偏移（main.c 有 434 处调用，属高 churn 点）；
   - `rhi_acceleration_structure_get_vk_handle`（rhi.h:420）、`rhi_vk_validation_*`（rhi.h:838-841）公开 vk 命名函数；
   - `RHINativeHandleType` 只有 `RHI_NATIVE_HANDLE_VULKAN`；`RHINativeDevice`/`RHITextureNativeInfo` 按 Vk 形状定义；
   - TLAS 实例记录硬编码为 `VkAccelerationStructureInstanceKHR` ABI（rhi.h:68-71）；
   - 隐式 swapchain render pass：`rhi_cmd_begin_render_pass(cmd)` 不带 target（rhi.h:530-531）；
   - 显式 layout transition API（rhi.h:639-643, 811）；
   - `rhi_frame_index` 暴露 Vulkan 双槽语义（rhi.h:470-471）。
3. 错误模型已部分存在：`RHIResult`（rhi.h:338-349）已含 `OK/ERROR/INVALID_ARGUMENT/UNAVAILABLE/UNSUPPORTED/BUSY/OUT_OF_DATE/SURFACE_LOST/DEVICE_LOST/SYNC_FAILED`；`*_ex` 入口（rhi.c:50-159）+ `ENGINE_RHI_TEST` 故障注入钩子（rhi.h:861-864）。**决策：不新增枚举值**，用文档+契约测试固定映射（见 §4.2）。
4. Frame 生命周期已存在 acquire/begin/submit/present/resize/drain 别名族（rhi.h:450-471；rhi.c:117-159），需固化为契约并补 destroy 语义测试。
5. 构建：无 `engine_rhi_*` target（grep 零命中）；`RHI_CORE_SOURCES`（engine/CMakeLists.txt:238-243）编入 `engine` 静态库；后端 .c 被 unity-include 且被 `test_rhi_backend_internal_contract.cmake:180-208` 强制要求（同时禁止 `rhi_metal.c`/`ENGINE_RHI_BACKEND_METAL`/`ENGINE_RHI_BACKEND_D3D12` token——该测试必须随拆分同步重写，属计划内 TDD-red→green）。`ENGINE_RHI_BACKEND=auto|opengl|vulkan` 选择器与 `ENGINE_VULKAN` 兼容层在 engine/CMakeLists.txt:129-148。
6. WSI：surface 创建硬编码在 `rhi_vk.c:1468-1706` 的 `#ifdef` 链（Win32/MetalEXT/Wayland/Android/Xlib）；PAL 只提供 `platform_window_native/platform_display_native/platform_surface_native` 三个不透明句柄（platform.h:113-118）。`platform_wsi.h` 已有纯契约状态机（UNAVAILABLE/CREATED/RESIZED/LOST/SUSPENDED/DESTROYING + swapchain generation），未接真实 swapchain。OHOS 不在 WSI 枚举中，仅 platform_compat.h fail-closed。
7. 测试基础设施：CTest + 纯 C `main()` 返回非零即失败；`engine/tests/test_framework.h`；CMake 脚本契约测试（`cmake -P`）是既定 TDD-gate 惯例；`SKIP_RETURN_CODE 77` 为环境依赖 gate 的 skip 约定；labels：`headless/platform_contract/graphics/platform_runtime/fuzz/hardening`。
8. 工作树当前有未提交 WIP：`rhi.h/rhi.c/rhi_backend_internal.h/rhi_gl.c/rhi_ownership.c/rhi_vk.c` 修改 + 新文件 `platform_wsi.h`、`rhi_d3d12.c/h`、`test_d3d12_lifetime_hresult_contract.c`、`test_d3d12_native_failure.c`、`test_platform_wsi_lifecycle.c` 等。计划 Task 1 必须先验证并提交这些 WIP，再开始新工作。
9. 用户临时 artifacts（**任何步骤不得修改/删除/移动**）：`.scratch-vkprobe/`（AMD surface-caps 探测源码与 fresh-* 配置证据）、`engine/profile_trace.json`（profiler trace 格式样例）、`.tmp/`、仓库根 `d3d12_shader_gate.hlsl/.dxil`。

## 4. 架构决策

### 4.1 后端链接模型：编译期单后端、独立静态库（性能最优）

- 决策：废除 `rhi.c` 的 unity-include，把每个后端编译为独立静态库 `engine_rhi_vulkan` / `engine_rhi_opengl` /（后续）`engine_rhi_metal` / `engine_rhi_d3d12`，各库导出同一组 `rhi_*` 符号；`engine` 核心库只含 `RHI_CORE_SOURCES`（rhi.c 的调度/校验部分、ownership、validation、resources、present_history）。最终可执行文件链接 `engine` + 恰好一个后端库。
- 性能理由：保持直接符号调用，无 vtable/函数指针间接跳转，零分发开销；链接器仍可 IPO/LTO 跨库内联（现有 `ENGINE_ENABLE_IPO=ON` 保留）。
- 不采用运行时多后端共存：避免符号冲突与二进制膨胀；运行时切换的需求不存在于任何目标平台。
- 兼容：`ENGINE_VULKAN` ON/OFF 与 `ENGINE_RHI_BACKEND=auto|opengl|vulkan` 语义不变（auto 在 Windows/Linux 默认 vulkan 保持现状…实际现状是 auto→平台默认，维持 `ENGINE_RHI_BACKEND_EFFECTIVE` 机制），新增 `metal`/`d3d12` 选择值（当前被 selector FATAL_ERROR 拒绝，届时放开）。
- Headless：纯逻辑测试只链接 `engine`（无后端）；需要一个可链接符号占位时提供 `engine_rhi_headless`（全部入口 fail-closed 返回 `RHI_RESULT_UNAVAILABLE`），禁止把 headless stub 误当 GPU 证据。

### 4.2 统一错误状态映射（不新增枚举）

| 统一状态 | RHIResult | 说明 |
|---|---|---|
| 初始化失败 | `RHI_RESULT_ERROR`（参数错误时 `INVALID_ARGUMENT`） | `rhi_device_create_ex` 返回 NULL + out_result |
| surface 不可用 | `RHI_RESULT_SURFACE_LOST` / 平台缺失时 `UNAVAILABLE` | OHOS fail-closed 用 `UNAVAILABLE` |
| device lost | `RHI_RESULT_DEVICE_LOST`（sticky latch） | 所有阻塞等待 fail-fast |
| resize / out-of-date | `RHI_RESULT_OUT_OF_DATE` | swapchain 自动重建失败时经 `dev->lifecycle_result` 暴露 |
| feature unsupported | `RHI_RESULT_UNSUPPORTED` | 能力探测失败路径 |
| 同步失败 | `RHI_RESULT_SYNC_FAILED` | fence/semaphore 等待失败 |

该映射由契约测试 `test_rhi_error_contract.c` 用 `ENGINE_RHI_TEST` 注入钩子固定，所有后端共用。

### 4.3 Frame 生命周期契约

`acquire(rhi_frame_acquire_ex) → begin(记录开始) → submit(rhi_frame_end_ex/rhi_frame_submit_ex) → present(rhi_present_ex)`；`resize(rhi_device_resize_ex)`、`drain(rhi_device_drain_ex)`、`destroy(rhi_device_destroy)`。语义约束（写入契约测试）：
- acquire 之前设备必须 READY；LOST 时全部返回 `DEVICE_LOST`；
- begin 之前必须有成功 acquire（同一调用内完成亦可，但状态机只能有一对 in-flight acquire→submit）；
- present 只能在成功 submit 之后；
- out-of-date 时 backend 自动重建 swapchain，重建失败 → `lifecycle_result = OUT_OF_DATE/SURFACE_LOST` 且后续 frame 调用 fail-fast；
- destroy 前必须 drain（实现内强制 idle），in-flight destroy 由 WSI 状态机（DESTROYING）保护。

### 4.4 rhi.h 中性化策略

- 新建 `engine/src/rhi/rhi_native_vulkan.h`：`RHINativeDevice`、`RHITextureNativeInfo`、`rhi_acceleration_structure_get_vk_handle`、`rhi_vk_validation_*` 等 Vulkan 形状类型与函数迁入；`rhi.h` 只保留 `RHINativeHandleType` 枚举（扩展 `RHI_NATIVE_HANDLE_METAL/D3D12`）与不透明 `void *` 访问器原型。GL/VK 现有调用点通过包含新头保持编译。
- `RHIPipelineDesc` 的布局布尔与 render-pass 兼容字段保留为「capability contract」字段（重命名注释为后端中性的 pipeline contract 提示，禁止简单改名伪装跨平台：每个字段必须有 ≥1 个后端的真实消费与契约测试）。
- `rhi_pipeline_get_uniform_location` 是最大调用点（main.c 434 处）：保留函数与语义（VK=push-constant 偏移，GL=uniform location，Metal/D3D12=各自绑定槽索引），ABI 迁移阶段（计划 E）再逐调用点迁移到 reflection 绑定。
- TLAS 实例记录：新 major 前维持 VK ABI + 文档化；Metal/D3D12 后端在各自后端内做格式转换，不改公开 ABI。

### 4.5 WSI / surface adapter

- 新建 `engine/src/platform/platform_vk_surface.h/.c`：`RHIResult platform_create_vulkan_surface(Platform *p, void *vk_instance, uint64_t *out_surface)`（用 `uint64_t`/`void *` 避免 platform 层依赖 Vulkan 头——platform 层只允许依赖 OS API 的分层规则不变）。把 `rhi_vk.c:1657-1706` 的五段 `#ifdef` surface 创建迁移进去；`rhi_vk.c` 改为调用它。
- `platform_wsi.h` 状态机接入真实生命周期：resize/suspend/resume/lost/destroying 事件由 window_*.c 上报，RHI 消费。逻辑尺寸 vs 物理 drawable 尺寸语义不变（`platform_get_logical_size` / `platform_get_drawable_size`）。
- OHOS 继续 fail-closed：不加入 WSI 枚举；`ENGINE_VULKAN` on OHOS 维持 FATAL_ERROR。
- Metal/D3D12 的 surface 获取：`platform_surface_native()` 在 Cocoa 已返回 `CAMetalLayer*`（Metal 直接用），Win32 返回 HWND（D3D12 swapchain 用）——无需新 PAL API。

### 4.6 Capability contract 替代后端分支

renderer 中的 `#ifdef ENGINE_VULKAN` 分支逐步替换为 `RHICapabilities` 查询（已存在：sample counts、resolve/scissor、present damage/buffer age、feature bits）。迁移期需要新增的能力位（如 `push_constants_supported`、`max_push_constant_size`、`hiz_supported`）先加字段 + 契约测试，再改 renderer 消费。禁止简单改名伪装跨平台。

### 4.7 Shader 策略

| 后端 | 着色语言 | 编译方式 |
|---|---|---|
| Vulkan | GLSL → SPIR-V | 现状：运行时 shaderc（target env Vulkan 1.2 / SPIR-V 1.5） |
| OpenGL | GLSL 源码 | 现状：直接使用（退役后删除） |
| Metal | MSL | 新增：离线 `metal-shaderconverter` 或手写 MSL + `xcrun metal` 编译为 `.metallib`，构建期生成；策略细节在计划 C 中固化 |
| D3D12 | HLSL → DXIL | 新增：dxc（沿用 `test_d3d12_shader_compile_gate` 的 dxc 定位逻辑），SDK 版本锁定（计划 F） |

### 4.8 构建所有权拆分（对应用户阶段 3）

- `engine_rhi_vulkan`：`src/rhi/rhi_vk.c`，`target_compile_definitions PRIVATE ENGINE_VULKAN=1`，链接 `Vulkan::Vulkan ${SHADERC_LIB}`。
- `engine_rhi_opengl`：`src/rhi/rhi_gl.c` + `glad`，链接平台 GL 库。
- `engine_rhi_headless`：`src/rhi/rhi_headless.c`（新，全入口 fail-closed）。
- 每个需要 RHI 的可执行 target 通过 helper 函数 `engine_link_rhi_backend(<target>)` 链接 `ENGINE_RHI_BACKEND_EFFECTIVE` 对应的后端库；headless 测试不调用该 helper。
- 契约测试重写：`test_rhi_backend_internal_contract.cmake` 改为断言「engine 不拥有任何后端源、后端库各自拥有恰好一个后端源、无 target 同时链接两个后端库」；`test_rhi_backend_selection.cmake` 扩展 metal/d3d12 选择值语义（未实现的平台上选择 metal/d3d12 仍须 FATAL_ERROR 并标记 UNAVAILABLE）。

## 5. 实施阶段总览（计划拆分）

| 计划文件 | 覆盖用户阶段 | 执行前提 |
|---|---|---|
| `2026-10-14-rhi-plan-a-evidence-abstraction-buildsplit.md` | 1（证据冻结）、2（RHI 中性化）、3（构建拆分）、11 的文档骨架 | 本机（Windows + Ninja/clang + VS2026，vendored Vulkan SDK 1.4.357.0）即可执行 |
| `2026-10-14-rhi-plan-b-wsi-vulkan-first.md` | 4（WSI 抽离）、5（Vulkan-first） | Linux X11/Wayland + Android 设备；本机可做 Win32 部分 |
| `2026-10-14-rhi-plan-c-metal.md` | 6（原生 Metal） | macOS + Xcode；iOS 真机 |
| `2026-10-14-rhi-plan-d-d3d12.md` | 7（原生 D3D12） | Windows + 锁定 Windows SDK/Agility SDK + dxc |
| `2026-10-14-rhi-plan-e-renderer-abi.md` | 8（renderer/shader ABI 迁移） | 计划 A 完成；各后端至少 HEADLESS |
| `2026-10-14-rhi-plan-f-release-deps-opengl-removal.md` | 9（发布回滚）、10（依赖锁定）、OpenGL 删除条件、11（CI/文档收尾） | B/C/D 认证完成 |

每个计划独立可交付、可测试；进入下一个计划前，前一个计划的 DoD（Definition of Done）必须全绿。

## 6. OpenGL 删除条件（**已取消**：2026-10-26 决定长期保留 OpenGL；以下仅作历史记录，不是计划）

1. Android/Linux/Steam Vulkan 已认证（GPU-runtime + benchmark-comparable 收据）；
2. macOS/iOS 原生 Metal 已认证（真机 GPU-runtime，MoltenVK 证据不算）；
3. Windows D3D12 已认证（GPU-runtime + benchmark-comparable，Proton lane 仅兼容参考）；
4. 所有 renderer/UI 路径不再依赖 OpenGL（grep 证据：`ENGINE_VULKAN` off 路径无消费者）；
5. 无生产 consumer 依赖 OpenGL；
6. OpenGL 头文件、GLAD、GL 库链接、GL shader 路径、GL runtime 测试全部从最终 release target 消失；
7. 禁用 OpenGL 依赖后 clean-room build 成功（新 clone + 锁定依赖 + 从零 configure/build/test）；
8. 所有平台 consumer link/startup 成功；
9. major-release migration notice 已发布；
10. 旧版本已有可回滚版本（签名 + 离线可用 artifact）；
11. 产品/发布负责人书面确认 breaking removal。

## 7. 风险登记

| 风险 | 缓解 |
|---|---|
| NVIDIA 616.56 混合 GPU 的 `VK_ERROR_DEVICE_LOST` 与 Hi-Z {1,1} 异常 | 不作为源码修复依据；须在健康设备独立复现后立项；`TV_ONLY_PSHADOW`/`TV_ONLY_GBUFFER` 隔离测试保留 |
| MoltenVK 证据被误当原生 Metal 证据 | 证据台账中 MoltenVK 行与 Metal 行严格分列；CI lane 命名区分 `macos-vulkan` vs `macos-metal` |
| iOS/Android 模拟器证据膨胀 | 模拟器结果只计入 compile/lifecycle 等级 |
| Proton 结果被误当 Windows D3D12 证据 | Proton 独立 lane + 台账分列 |
| OHOS 被意外启用 | 维持 fail-closed FATAL_ERROR + `test_platform_compat_harmonyos` |
| 拆分后端后符号冲突/重复链接 | 契约测试断言无 target 链接两个后端库 |
| `rhi_pipeline_get_uniform_location` 434 调用点迁移风险 | 计划 E 逐批迁移 + deterministic readback oracle |
| 依赖版本漂移 | 计划 F 锁定全部 SDK/工具链版本 + hash 记录，禁止 release 用 latest |

## 8. 文档与 CI

### 8.1 文档更新清单
- `README.md`：后端矩阵与构建入口更新；
- `docs/Build_Guide.md`：新后端构建选项、依赖锁定版本、证据矩阵；
- `docs/Architecture_Overview.md`：§9 平台支持、RHI 分层图、后端链接模型；
- 新增 `docs/rhi_backend_evidence.md`（证据台账）；
- 新增 `docs/rhi_metal_d3d12_feature_matrix.md`；
- 新增 `docs/vulkan_support_matrix.md`；
- 新增 `docs/rhi_rollback_runbook.md`（rollback / device-loss runbook）；
- 新增 `docs/rhi_benchmark_receipt_schema.md`（benchmark receipt schema）。

### 8.2 CI lane 分离
headless / native-surface / GPU-runtime / validation / benchmark / Proton 六类 lane 分离；环境依赖 lane 用 `SKIP_RETURN_CODE 77` 约定；每个 lane 产出证据收据 artifact。

### 8.3 Benchmark receipt schema（要点）
JSON：`(schema_version, timestamp, platform, os_version, backend, gpu, driver_version, cpu, ram, build_commit, build_config, command, metrics{fps_avg, fps_p1, frame_ms_avg, frame_ms_p99}, evidence_level, runner)`；字段级校验脚本入 CI。

## 9. 过程规则

- TDD：先写失败测试 → 验证失败 → 最小实现 → 验证通过 → 提交。每个 task 独立可测。
- 测试全绿后才提交并推送 `origin master`（`git@github.com:konyka/break.git`）。
- **上下文压缩交接**：执行阶段上下文约 70% 时，先生成压缩交接，至少包含：当前 phase 与 todo 状态；已完成/失败/阻塞测试；修改文件与未提交文件；当前 commit/branch/remote 状态；平台矩阵及证据等级；未解决风险；下一步精确命令；明确说明哪些凭据、用户文件与临时 artifacts 不得触碰（`.scratch-vkprobe/`、`engine/profile_trace.json`、`.tmp/`、`d3d12_shader_gate.{hlsl,dxil}`、`.env`、SSH 私钥等）。
- 缺失 SDK 的平台只能标记 UNAVAILABLE，不得伪造证据。
