# RHI Metal 后端笔记（计划 C）

## Task 3：设备/命令队列与能力映射

`engine_rhi_metal`（`engine/src/rhi/rhi_metal.m`，单一 Objective-C TU，手动引用计数
`-fno-objc-arc`）。`rhi_device_create` 的 `window_native` 即 `CAMetalLayer *`
（macOS 由 `window_cocoa.m` 的 `platform_window_native` 提供；iOS 经
`PlatformConfig.native_window` 注入）。`MTLCreateSystemDefaultDevice()` 返回 nil
时 fail-closed 返回 NULL（wrapper 报 `RHI_RESULT_ERROR`；无 Metal 的平台在
selector 层已 fail-closed，此处是运行时兜底）。

### 能力映射表（由 test_rhi_metal_device_contract 固定）

| RHICapabilities 字段 | Metal 来源 | 契约 |
|---|---|---|
| `backend` | `RHI_BACKEND_METAL` | 固定 |
| `color_sample_counts` | `[device supportsTextureSampleCount:{1,2,4,8}]` 逐探测 → `rhi_sample_count_bit` 位集 | 至少含 1x；缺 1x 则 create fail-closed |
| `depth_sample_counts` | 同上 | 至少含 1x |
| `surface_sample_count` | 恒 1 | CAMetalLayer drawable 不可 MSAA；MSAA 只能经 offscreen resolve |
| `color_resolve_supported` | true | `storeActionMultisampleResolve` |
| `depth_resolve_supported` | false | fail-closed：自定义 depth resolve 不纳入本计划 |
| `scissor_supported` | true | `setScissorRect:` |
| `present_target_preserved` | false | drawable 内容不保证保留 |
| `present_damage_supported` | false | CAMetalLayer 无 damage 机制 |
| `present_buffer_age_supported` | false | 同上 |
| `feature_bits` | `[device supportsRaytracing]`（respondsToSelector 门控）→ `RHI_FEATURE_ACCELERATION_STRUCTURE \| RHI_FEATURE_RAY_QUERY`；否则 0 | `RHI_FEATURE_RAY_TRACING_PIPELINE` **永不置位**（Metal intersection-function 模型无 raygen pipeline 等价，fail-closed） |

### RHIDeviceInfo

| 字段 | 值 |
|---|---|
| `device_name` | `[device.name UTF8String]` |
| `vendor_id` | `0x106B`（Apple）当 `[device supportsFamily:MTLGPUFamilyApple1]`，否则 0 |
| `device_id` | 0 |
| `api_version` | `(3u << 22)`（Metal 3 baseline，macOS 14 / Xcode 15 提供） |
| `driver_version` | 0 |

### 格式映射层（`engine/src/rhi/rhi_metal_format.h`，纯 C11、平台无关）

`RHIMetalFormat` 序数刻意**不**等于 `MTLPixelFormat` 常量，使该头可在任意平台编译；
`rhi_metal.m` 用 `_Static_assert` 把序数钉到真实常量（INVALID==MTLPixelFormatInvalid==0 +
六个格式两两不等）。readback 字节契约（R587/R593/R602）：RGBA8/BGRA8=4、RG16F=4、
RGBA16F=8、R32F=4、D32=4（D32 按 f32 每 texel 4 字节）。

两槽 frame pacing：`rhi_metal_frame_slot(counter) = counter % 2`；
`rhi_metal_slot_wait_value(counter) = counter >= 2 ? counter - 2 : 0`
（wait(0) 在未 signal 时立即成立，前两帧不等待）。消费在 Task 5（帧生命周期）；
Task 4 的 bounded drain 单独用 `drain_event` + `drain_counter` 递增的
shared-event 值（Task 5 起 frame/drain 两个事件分离：单一事件的 signaledValue
单调递增，共用会让 drain signal 提前满足帧等待）。

### 生命周期

`rhi_device_destroy`：先经实现内 idle drain（Task 5 起 = 帧 signal 等待 +
Task 4 bounded queue drain：空 command buffer + `encodeSignalEvent:` +
`MTLSharedEvent waitUntilSignaledValue:timeoutMS:` 20s，覆盖队列上全部已调度
工作，对齐 `rhi_d3d12_drain_gpu` 语义），再经 `metal_quiesce_handlers`
（`pending_handlers` 原子计数轮询，20s 上限）quiesce 所有 completion handler，
最后 release 全部 Obj-C 句柄（drawable / frame_cmd / library / frame_event /
drain_event / queue / device）。`layer` 不归 RHI 拥有，不 release。

## Task 4：device-lost 闩锁（sticky latch）

Metal 没有公开的 device-lost 通知 API，检测完全靠两条路径：(1) 每个提交的
command buffer 经 `metal_commit` 挂 `addCompletedHandler:` 检查
`MTLCommandBufferStatusError`；(2) `rhi_device_idle` / destroy 的 drain 用
20s 超时的 `MTLSharedEvent` 等待（`waitUntilCompleted` 无超时，对 wedge GPU 会
无限挂起——Task 3 评审移交项）。闩锁置位（`metal_note_device_lost`）时同步写
`dev->status = RHI_DEVICE_STATUS_LOST` 并
`rhi_device_set_lifecycle_result(dev, RHI_RESULT_DEVICE_LOST)`，之后所有阻塞
等待 fail-fast（对齐 VK R578 / rhi.h:854-858 与 D3D12 fence 超时语义）。
`rhi_device_lost` 返回 `dev->status == LOST || mb->device_lost_latch`（前者覆盖
ENGINE_RHI_TEST 注入路径）。

### Metal 错误 → RHIResult 映射表（契约测试固定）

| Metal 情形 | 检测点 | RHI 语义 |
|---|---|---|
| `MTLCreateSystemDefaultDevice()` nil | create | `RHI_RESULT_ERROR`（平台缺失在 selector 已 `UNAVAILABLE` fail-closed） |
| `window_native` 不是 CAMetalLayer | create | `RHI_RESULT_INVALID_ARGUMENT` |
| `nextDrawable` 重试超时（1s 截止，1ms 退避） | acquire（Task 5 已接线） | `lifecycle_result = RHI_RESULT_OUT_OF_DATE`，后续 frame 调用 fail-fast |
| layer nil / drawable texture nil | acquire（Task 5 已接线） | `RHI_RESULT_SURFACE_LOST` |
| command buffer `status == MTLCommandBufferStatusError` | completedHandler / `rhi_device_idle` / frame_end | sticky latch → `RHI_RESULT_DEVICE_LOST`；`error.code == MTLCommandBufferErrorDeviceRemoved`（macOS 13+，低版本按通用 error 同样 latch） |
| `MTLSharedEvent` 等待超时（20s，对齐 rhi.h:855 的 VK 20s 语义） | drain（Task 4）/ acquire 帧 pacing / idle 帧等待（Task 5 已接线） | 首报 `RHI_RESULT_SYNC_FAILED`；超时后置 device-lost 闩锁，后续调用经闩锁报 `RHI_RESULT_DEVICE_LOST`（对齐 VK 的 fence-unsignaled→lost 语义，rhi.h:854-858） |
| 挂起中 acquire（iOS host 暂停） | acquire（`mb->suspended`，Task 6 接线） | `RHI_RESULT_BUSY` |
| ray tracing API 在 `[device supportsRaytracing]==NO` | RT 族 | `RHI_RESULT_UNSUPPORTED` |

## Task 5：drawable acquire/present/resize + 帧状态机映射

规格 §4.3 帧生命周期到 Metal 的逐项映射（由 `test_rhi_metal_frame_lifecycle`
固定，graphics lane，真机验证）：

| 规格 §4.3 阶段 | RHI 入口 | Metal 实现 |
|---|---|---|
| acquire | `rhi_frame_acquire_ex` → `rhi_frame_begin` | (1) 双槽 pacing：`slot = frame_counter % 2`；`frame_counter >= 2` 时 `[frame_event waitUntilSignaledValue:frame_counter-2 timeoutMS:20000]`，超时 → SYNC_FAILED + 闩锁；(2) `[layer nextDrawable]` 重试循环（1s 截止、1ms 退避，期间 pump 一个 `@autoreleasepool`），nil 超时 → `lifecycle_result=OUT_OF_DATE` + fail-fast；(3) drawable 尺寸校验：`layer.drawableSize` ≠ dev 宽高 → 采用 layer 实际尺寸并更新 dev（windowDidResize → cocoa_update_drawable_size 已维护 layer 尺寸） |
| begin | 同上（acquire 内完成） | `[queue commandBuffer]`；retain 进 `RHICmdBuffer`；render encoder 延迟到首个 `rhi_cmd_begin_render_pass` 用当前 drawable texture 建 `MTLRenderPassDescriptor` |
| submit | `rhi_frame_end_ex`/`rhi_frame_submit_ex` → `rhi_frame_end` | endEncoding（若开）→ `[cmd presentDrawable:drawable]` → `[cmd encodeSignalEvent:frame_event value:frame_counter]` → `metal_commit`（挂 completedHandler）→ 释放 drawable 引用。**present 在 commit 前 attach 是 Metal 硬约束**，故 Metal 后端把 present 语义并入 frame_end |
| present | `rhi_present_ex` → `rhi_present` | 簿记 no-op：`frame_counter++`、清 damage 状态；帧 owner 校验已由 rhi.c 保证「present 只能在成功 submit 之后」 |
| resize | `rhi_device_resize_ex` → `rhi_device_resize` | 更新 `dev->width/height`；**不**写 `layer.drawableSize`（所有权在 window 层）；下次 acquire 自动采用新尺寸（对齐「swapchain 自动重建」语义） |
| drain | `rhi_device_drain_ex` → `rhi_device_idle` | 等待最后一次提交的 signal：`frame_counter >= 1` 时 `waitUntilSignaledValue:frame_counter-1 timeoutMS:20000`（0 帧时立即成功）；超时 → SYNC_FAILED + 闩锁。之后仍跑 Task 4 的 `metal_drain`（drain_event 有界 drain）：覆盖非帧提交与 frame 0 的退化 signal（值 0 == 初始 signaledValue），并保持诊断探针语义 |
| destroy | `rhi_device_destroy_ex` → `rhi_device_destroy` | 强制 drain（实现内 idle，§4.3「destroy 前必须 drain」）→ `metal_quiesce_handlers` → release |

`rhi_frame_index` 返回 `(u32)(frame_counter % 2)`（rhi.h:470-471 双槽语义，
经钉死的 `rhi_metal_frame_slot` helper）；`rhi_set_vsync(false)` →
`layer.displaySyncEnabled = NO`（macOS 10.13+，respondsToSelector 门控），
true → YES。

### clear / render pass 语义（Task 5 最小集）

clear 用 render pass 的 `loadAction=MTLLoadActionClear` + `clearColor` 实现：
drawable 内容未定义，故每帧首 pass 即清（默认不透明黑，`rhi_cmd_clear_color`
覆盖）；pass 中再调 clear 时 endEncoding 当前 encoder（已录工作留在 command
buffer）并以新颜色重建 encoder。`rhi_cmd_begin_render_pass` 在无帧/无 drawable
时 fail-closed 记日志。像素级断言归 Task 9（screenshot）。

### completion handler 生命周期（Task 4 评审移交闭环）

`metal_commit` 的 completedHandler 捕获裸 `dev`/`mb`。Task 5 起帧提交复用
`metal_commit`，destroy 的 drain 只 quiesce 自己的 drain buffer，帧 buffer 的
handler 可能在 `free(mb)` 后触发（UAF）。机制：`MetalBackend.pending_handlers`
原子计数——`metal_commit` 在 commit 前 +1，handler 末尾 -1；destroy 在 drain 后
`metal_quiesce_handlers` 有界轮询（1ms 退避、20s 上限）至归零再释放。handler
只在 buffer 完成时触发，drain 成功后该轮询只等 handler 队列派发延迟；wedge GPU
上 buffer 永不完成、handler 永不触发，超时路径因此也不会遗留活 handler
（teardown 保持有界）。结构证据：`test_rhi_metal_frame_lifecycle` 三帧循环后
destroy 无崩溃；`test_rhi_metal_device_contract` 的 idle/drain 用例同路径。

### 帧 pacing 与 drain 的事件分离

frame 提交 signal `frame_event`（值 = `frame_counter`）；Task 4 drain 改为 signal
独立的 `drain_event`（值 = `++drain_counter`）。单一 MTLSharedEvent 的
signaledValue 单调递增，共用会让 drain 的计数值提前满足帧 pacing 等待——
两计数器两事件的分离是正确性要求（Task 4 移交：保持该分离）。已知退化：
`frame_counter == 2` 的 pacing 等待值为 0（== 初始 signaledValue，立即成立，
由 `test_rhi_metal_format_mapping` 钉死）；该窗口由 CAMetalLayer 自身的
drawable 数量背压覆盖。

## Task 6：suspended-acquire BUSY（iOS host 暂停防御）

`rhi_frame_begin` 入口检查 `mb->suspended`，置位时
`rhi_device_set_lifecycle_result(dev, RHI_RESULT_BUSY)` + 释放帧 owner +
返回 NULL（wrapper `rhi_frame_acquire_ex` 把 lifecycle_result 透传给
`out_result`）。BUSY 非粘性：清标志后 acquire 正常；`rhi_device_resize`
不走 acquire，挂起期间仍可调用。由 `test_rhi_metal_frame_lifecycle` 的
`suspended_acquire_is_busy_resize_and_recover` 用例固定。

### 已知边界

`suspended` 标志**没有生产 setter**：唯一的置位入口是 `ENGINE_RHI_TEST`
钩子 `rhi_test_metal_set_suspended`（`rhi_metal.m` 私有导出，测试目标经
`engine_rhi_metal` 库级 `ENGINE_RHI_TEST=1` 编译置位，先例同
`engine_rhi_headless`）。生产路径的 iOS 暂停语义由 window_mobile.c 的
host-injection 模型保证：宿主在 background 期间**自律不调用**任何 frame
API（window_mobile.c 是纯注入壳，无事件上报钩子，本计划不给它加）。后端
的 suspended 检查只是宿主误调时的防御性兜底，不构成完整的
pause/resume 生命周期实现；iOS 模拟器 lifecycle lane 归 Task 14。
