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
Task 4 的 bounded drain 单独用 `drain_counter` 递增的 shared-event 值。

### 生命周期

`rhi_device_destroy`：先 drain（Task 4 起为 bounded drain：空 command buffer +
`encodeSignalEvent:` + `MTLSharedEvent waitUntilSignaledValue:timeoutMS:` 20s，
覆盖队列上全部已调度工作，对齐 `rhi_d3d12_drain_gpu` 语义），再 release 全部
Obj-C 句柄（drawable / library / frame_event / queue / device）。`layer` 不归 RHI
拥有，不 release。

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
| `nextDrawable` 重试超时（1s 截止） | acquire（Task 5） | `lifecycle_result = RHI_RESULT_OUT_OF_DATE`，后续 frame 调用 fail-fast |
| layer nil / drawable texture nil | acquire（Task 5） | `RHI_RESULT_SURFACE_LOST` |
| command buffer `status == MTLCommandBufferStatusError` | completedHandler / `rhi_device_idle` / frame_end | sticky latch → `RHI_RESULT_DEVICE_LOST`；`error.code == MTLCommandBufferErrorDeviceRemoved`（macOS 13+，低版本按通用 error 同样 latch） |
| `MTLSharedEvent` 等待超时（20s，对齐 rhi.h:855 的 VK 20s 语义） | drain（Task 4）/ acquire（Task 5） | 首报 `RHI_RESULT_SYNC_FAILED`；超时后置 device-lost 闩锁，后续调用经闩锁报 `RHI_RESULT_DEVICE_LOST`（对齐 VK 的 fence-unsignaled→lost 语义，rhi.h:854-858） |
| 挂起中 acquire（iOS host 暂停） | acquire（Task 5） | `RHI_RESULT_BUSY` |
| ray tracing API 在 `[device supportsRaytracing]==NO` | RT 族 | `RHI_RESULT_UNSUPPORTED` |

Task 4 落地行：create 两行（Task 3 已有）、command buffer 完成状态、drain 超时；
acquire/frame_end 行随 Phase 3 帧生命周期接线（`metal_commit` 已为其预留统一
commit 入口）。
