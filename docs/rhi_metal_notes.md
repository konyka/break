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
（wait(0) 在未 signal 时立即成立，前两帧不等待）。消费在 Task 4。

### 生命周期

`rhi_device_destroy`：先 drain（空 command buffer commit + `waitUntilCompleted`，
覆盖队列上全部已调度工作，对齐 `rhi_d3d12_drain_gpu` 语义），再 release 全部
Obj-C 句柄（drawable / library / frame_event / queue / device）。`layer` 不归 RHI
拥有，不 release。Metal 无公开 device-lost 通知 API；device-lost 检测（command
buffer 完成状态 + shared-event 超时）在 Task 4 落地，本任务 `device_lost_latch`
字段保留未消费。
