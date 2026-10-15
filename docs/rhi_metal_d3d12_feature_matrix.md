# Metal / D3D12 特性矩阵（规划态）

两个后端的公开入口均为现有 `rhi_*` 符号集（`engine/src/rhi/rhi.h`）；本表跟踪各特性面在后端内的落地状态。状态枚举：NONE（无代码）/ PLANNED（已排期）/ HEADLESS / NATIVE_SURFACE / GPU_RUNTIME / BENCHMARK_COMPARABLE。

| 特性面 | Metal（计划 C） | D3D12（计划 D） |
|---|---|---|
| 设备创建 / 销毁 | PLANNED（MTLDevice/MTLCommandQueue） | GPU_RUNTIME（计划 D Task 3：adapter 打分、三队列、fence 双槽 pacing、sticky device-lost latch、DRED；Task 4 补 destroy 前强制 drain） |
| Surface / swapchain | PLANNED（`platform_surface_native()` 返回 CAMetalLayer） | GPU_RUNTIME（计划 D Task 4：HWND → flip-model swapchain，3 back buffers，resize/drain/present 接线；契约测试的哨兵 HWND 仅在显式 opt-in（`BREAK_D3D12_TEST_FALLBACK_HWND=1`）下走设备持有的隐藏 fallback 窗口，生产语义 fail-closed 报 INVALID_ARGUMENT） |
| Render pass / pipeline contract | PLANNED（消费 `RHIPipelineDesc` capability contract 字段） | PLANNED |
| Push constants / 绑定模型 | PLANNED（`rhi_cmd_push_constants` → setBytes 映射） | PLANNED（root constants） |
| Compute / storage | PLANNED | PLANNED |
| 加速结构（BLAS/TLAS） | PLANNED（`rhi_acceleration_structure_get_vk_handle` 不适用；后端内转换，公开 ABI 不变） | PLANNED（同上） |
| Present damage / buffer age | PLANNED | HEADLESS（计划 D Task 4：RHIPresentRect→dirty rects 已接线（top-left 原点同约定，x/y/w/h → left/top/right/bottom 角点换算），但本机 FLIP_DISCARD/FLIP_SEQUENTIAL 下 dirty-rect Present1 均被运行时以 DXGI_ERROR_INVALID_CALL 拒绝 → 自动回落 full-surface present；damage 仅为优化，不回传失败） |
| 验证 gate | PLANNED（Metal validation layer） | PLANNED（DRED + debug layer） |
| Shader 路径 | MSL：`metal-shaderconverter` 或手写 MSL + `xcrun metal` → `.metallib`（构建期） | HLSL → DXIL：dxc（沿用 `test_d3d12_shader_compile_gate` 的 dxc 定位），SDK 版本锁定在计划 F |
| 当前证据等级 | NONE | GPU_RUNTIME（本机 RTX 4060 Laptop：`test_d3d12_device_contract` + `test_d3d12_swapchain_contract` 绿，2026-10-15，收据见 `.superpowers/sdd/2026-10-14-rhi-plan-d-d3d12/task-4-report.md`） |

## D3D12 决策记录（计划 D Task 4）

- **Back buffer 数 = 3**：flip model（`DXGI_SWAP_EFFECT_FLIP_DISCARD`）下 present engine 与 GPU 各可持有一帧，3 缓冲避免 CPU 在 `frame_fence` 等待上 stall；`rhi_frame_index` 双槽语义索引 per-frame command allocator 环（2 槽），与 swapchain 缓冲数解耦。
- **Present damage 原点**：RHIPresentRect 本来就是 top-left 原点，与 `DXGI_PRESENT_PARAMETERS` dirty rects 同约定——**不调用** `rhi_present_damage_to_bottom_left`（GL/EGL 专用）。字段语义不同（w/h vs right/bottom），做角点换算。
- **RENDER_TARGET→PRESENT barrier 在 submit 记录**（非 present）：command list 在 submit 时 Close，present 阶段已无录制面。
- **Present1 实参**：本机 inbox DXGI 在 `pPresentParameters == NULL` 时于 dxgi.dll 内 AV → 恒传零初始化结构体（文档上等价于"无 damage"）。

## 纪律

- 禁止用 MoltenVK 冒充原生 Metal 证据，禁止用 D3D11On12 / GL wrapper 冒充 D3D12（规格 §1.2）。
- 本表任何等级提升必须同步更新 `docs/rhi_backend_evidence.md` 并附收据。
