# Metal / D3D12 特性矩阵（Metal 规划态 / D3D12 已落地 GPU_RUNTIME）

两个后端的公开入口均为现有 `rhi_*` 符号集（`engine/src/rhi/rhi.h`）；本表跟踪各特性面在后端内的落地状态。状态枚举：NONE（无代码）/ PLANNED（已排期）/ HEADLESS / NATIVE_SURFACE / GPU_RUNTIME / BENCHMARK_COMPARABLE。

| 特性面 | Metal（计划 C） | D3D12（计划 D） |
|---|---|---|
| 设备创建 / 销毁 | PLANNED（MTLDevice/MTLCommandQueue） | GPU_RUNTIME（计划 D Task 3：adapter 打分、direct+compute+copy 三队列、fence 双槽 pacing、sticky device-lost latch、DRED；Task 4 补 destroy 前强制 drain；Task 8 升级为全队列 fence drain，覆盖 in-flight Present——debug layer 实抓 OBJECT_DELETED_WHILE_STILL_IN_USE 的修复） |
| Surface / swapchain | PLANNED（`platform_surface_native()` 返回 CAMetalLayer） | GPU_RUNTIME（计划 D Task 4：HWND → flip-model swapchain，3 back buffers，resize/drain/present 接线；vsync 经 `rhi_set_vsync` → Present1 SyncInterval（`DXGI_PRESENT_ALLOW_TEARING` 仅 vsync=0 路径）；契约测试的哨兵 HWND 仅在显式 opt-in（`BREAK_D3D12_TEST_FALLBACK_HWND=1`）下走设备持有的隐藏 fallback 窗口，生产语义 fail-closed 报 INVALID_ARGUMENT） |
| Render pass / pipeline contract | GPU_RUNTIME（计划 C Task 8，M2 收据：`RHIPipelineDesc` 全字段映射 MTLRenderPipelineDescriptor——顶点布局表逐字段移植 VK、R445 深度规则（Always+write-off 缓存态，bind 无条件 set）、blend/cull/wireframe（encoder 态）/point_list/color_format/MRT ≤5；R616-R619 FBO/MRT/shadow/cubemap-depth bind 契约（loadAction Clear/Load）；indirect：`draw_indirect`/`draw_indexed_indirect` 原生 `indirectBuffer:` 循环（arg ABI 与 VK 位级一致，16B/20B）；**`_count` 变体无 Metal 等价 → fail-closed LOG_ERROR + no-op，不声明能力位**；`test_rhi_metal_resources` 31/31 绿） | GPU_RUNTIME（计划 D Task 5：graphics/compute PSO 全字段映射（fill/cull/depth func+write mask/blend/RTV formats/DSV D32/sample count/topology/输入布局）；MRT ≤5 经 `rhi_mrt_formats_valid` 校验；indirect 三族 `ExecuteIndirect`（stride 必须等于 command signature 步长，不符 WARN 拒绝）；`test_d3d12_pipeline_contract` 真 GPU 绿） |
| Push constants / 绑定模型 | PLANNED（`rhi_cmd_push_constants` → setBytes 映射） | GPU_RUNTIME（root 32BIT_CONSTANTS 占 b0，128B compute / 256B graphics，按 64-DWORD 根签名预算钳制，越界 push 走丢弃语义（VK 对齐）；Task 6 补 256B uniform staging + 按 DWORD 对齐 dirty 区间 flush） |
| Compute / storage | GPU_RUNTIME（计划 C Task 9，M2：MTLComputePipelineState + 懒开 compute encoder dispatch（threadgroup=min(maxTotal,64)）；STORAGE→`setBuffer:atIndex:`、IMAGE/cube-face→`setTexture:atIndex:`（mip/face 经 texture view）；`rhi_cmd_memory_barrier`→`memoryBarrierWithScope:`（仅 compute encoder 内有意义）；fill/update/copy_buffer 经 blit 插入段；screenshot = bounded drain + drawable blit（framebufferOnly=NO 于 create 时置位）） | GPU_RUNTIME（compute dispatch；STORAGE→UAV 表 / IMAGE→SRV 表绑定；`rhi_cmd_memory_barrier` → 全 UAV barrier） |
| 加速结构（BLAS/TLAS） | PLANNED（`rhi_acceleration_structure_get_vk_handle` 不适用；后端内转换，公开 ABI 不变） | GPU_RUNTIME（计划 D Task 7：ID3D12Device5/ID3D12GraphicsCommandList4 DXR BLAS/TLAS；OPTIONS5.RaytracingTier < 1.0 一律 fail-closed；`storage_size=0` = 后端延迟定尺寸（prebuild 查询）；TLAS 实例记录与 VK ABI 位级一致（`_Static_assert` 钉死）；公开 ABI 不变） |
| Present damage / buffer age | PLANNED | HEADLESS（计划 D Task 4：RHIPresentRect→dirty rects 已接线（top-left 原点同约定，x/y/w/h → left/top/right/bottom 角点换算），但本机 FLIP_DISCARD/FLIP_SEQUENTIAL 下 dirty-rect Present1 均被运行时以 DXGI_ERROR_INVALID_CALL 拒绝 → 自动回落 full-surface present；damage 仅为优化，不回传失败） |
| 验证 gate | PLANNED（Metal validation layer） | GPU_RUNTIME（计划 D Task 8：`ENGINE_D3D12_DEBUG`（Debug 默认 ON，可显式覆盖）启用 debug layer + GPU-based validation；DRED（auto breadcrumbs + page fault）全配置强制；PIX 捕获 runbook 见 `docs/rhi_rollback_runbook.md`） |
| Shader 路径 | MSL：`metal-shaderconverter` 或手写 MSL + `xcrun metal` → `.metallib`（构建期） | HLSL → DXIL 已落地（GPU_RUNTIME）：手写 HLSL 旁挂（`engine/shaders/*_hlsl.{vert,frag}`，blit/myui 管线，sibling 断言禁静默跳过）+ 构建期 dxc 编译 DXIL SM 6.0（vendored `external/VulkanSDK/Bin/dxc.exe` 优先，CI 用 Windows SDK 自带 dxc）；HLSL 文本反射 → root 绑定 / uniform 偏移表 |
| 当前证据等级 | NONE | GPU_RUNTIME（本机 RTX 4060 Laptop，2026-10-15：device/swapchain/pipeline/shader/dxr 契约 + WARP floor（gpu=WARP）6/6 绿；收据见 `docs/rhi_backend_evidence.md` 计划 D 收据追加） |

## D3D12 决策记录（计划 D Task 4）

- **Back buffer 数 = 3**：flip model（`DXGI_SWAP_EFFECT_FLIP_DISCARD`）下 present engine 与 GPU 各可持有一帧，3 缓冲避免 CPU 在 `frame_fence` 等待上 stall；`rhi_frame_index` 双槽语义索引 per-frame command allocator 环（2 槽），与 swapchain 缓冲数解耦。
- **Present damage 原点**：RHIPresentRect 本来就是 top-left 原点，与 `DXGI_PRESENT_PARAMETERS` dirty rects 同约定——**不调用** `rhi_present_damage_to_bottom_left`（GL/EGL 专用）。字段语义不同（w/h vs right/bottom），做角点换算。
- **RENDER_TARGET→PRESENT barrier 在 submit 记录**（非 present）：command list 在 submit 时 Close，present 阶段已无录制面。
- **Present1 实参**：本机 inbox DXGI 在 `pPresentParameters == NULL` 时于 dxgi.dll 内 AV → 恒传零初始化结构体（文档上等价于"无 damage"）。

## 纪律

- 禁止用 MoltenVK 冒充原生 Metal 证据，禁止用 D3D11On12 / GL wrapper 冒充 D3D12（规格 §1.2）。
- 本表任何等级提升必须同步更新 `docs/rhi_backend_evidence.md` 并附收据。

## Metal 决策记录（计划 C Task 9）

- **GPU timer 降级**：本计划 M2 真机（macOS 26 / Metal 4 运行时 / Apple G14）上
  `supportsCounterSampling:AtStageBoundary` 返回 YES，但
  `sampleCountersInBuffer:atSampleIndex:withBarrier:` 在 render/compute/blit 三种
  encoder 上全部硬断言 "not supported on this device"（不可 @try 捕获，直接 abort；
  探针程序实证）。无安全运行时探测手段 → Apple-family GPU + macOS 26+ 静态门控为
  降级模式（`elapsed_ms` 恒 0 + LOG_WARN 一次）。Metal 4 替代路径
  （MTL4CounterHeap）不在本计划范围。在支持的旧系统上：stage-boundary 采样仅
  render encoder 合法 → pass 外的 begin/end 挂起到本帧下一个 pass 开口采样。
- **indirect `_count`**：Metal 无 draw-indirect-with-count 等价
  （MTLIndirectCommandBuffer 是独立编码模型，出计划范围）→ fail-closed no-op +
  LOG_ERROR，能力位不声明。
- **screenshot**：drawable 自 acquire retain 到 present（frame_end 不再提前释放），
  layer 在 device create 时置 `framebufferOnly=NO`（VK/D3D12 swapchain 读回契约的
  Metal 前提）；字节序为原生 BGRA（与 VK 裸拷贝一致）。
