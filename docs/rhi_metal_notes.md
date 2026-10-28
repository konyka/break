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

`suspended` 标志**没有生产 setter**：唯一的直接置位入口是 `ENGINE_RHI_TEST`
钩子 `rhi_test_metal_set_suspended`（`rhi_metal.m` 私有导出，测试目标经
`engine_rhi_metal` 库级 `ENGINE_RHI_TEST=1` 编译置位，先例同
`engine_rhi_headless`）。生产 iOS 生命周期由 `ios_main.m` 的 scene delegate
和宿主 poll 实现：后台在条件变量上等待、不调用 frame API，恢复时经
`platform_mobile_notify_resume` 更新 WSI。后端的 suspended 检查仍是宿主误调时
的防御性兜底，它自身不构成完整的 pause/resume 生命周期。CI lane 保持
compile-only；本机 Simulator 的 lifecycle 证据不升级 GPU_RUNTIME。

## Task 8：pipeline 字段映射 + FBO/MRT/shadow bind 契约（R616-R619）

### encoder 生命周期规则

**同一 cmd buffer 同时最多一个 encoder open。** 切换 render target 或
encoder 类型时先 `endEncoding` 当前 encoder（已录工作留在 command
buffer 里），再以新 `MTLRenderPassDescriptor` 开下一个——Metal 没有
GL 的 "bind framebuffer" 概念，FBO 切换 == 换 pass descriptor 重建
encoder。统一入口：`metal_end_render_encoder` /
`metal_open_render_pass`（后者顺带把 viewport/scissor 钉到目标全尺寸，
对齐 VK bind 路径的 non-flipped viewport + full scissor）。unbind 族
（offscreen/MRT/shadow/cubemap-depth）= endEncoding + 重开屏幕 pass
（`metal_screen_unbind`：color 用 `loadAction=Clear` + `cmd->clear_color`
——VK unbind 以烘焙色清屏的等价形态，颜色所有权在
`rhi_cmd_clear_color`；depth 恒清 1.0）。

### RHIPipelineDesc → MTLRenderPipelineDescriptor 逐项映射

| 字段 | Metal 映射 |
|---|---|
| `vert`/`frag` | slot payload 取 `id<MTLFunction>` → `vertexFunction`/`fragmentFunction`；`is_shadow_depth` 允许 frag 为 null handle（fragmentFunction=nil，depth-only pass） |
| `vertex_stride`+`font_vertex`/`skinned_vertex`/`is_shadow_depth`/`no_vertex_input` | `MTLVertexDescriptor`，布局表逐字段移植自 rhi_vk.c `vk_build_graphics_pipeline`（font 32B float2+float2+float4；skinned 64B float3×2+float2+uint4+float4；shadow 仅 float3@0；stride==12 仅 float3@0；默认 float3+float3+float2），全 bufferIndex 0、PerVertex |
| `depth_compare_lequal`/`depth_write_disable` | 缓存的 `MTLDepthStencilState`（Less/LessEqual × write on/off 四态 + 第五态 Always+write off，`MetalBackend.depth_states[5]` 懒建）。**R445**：write_disable 且非 lequal → 第五态（深度测试全关）。**bind 时无条件 `setDepthStencilState:`**——depth state 是 encoder 粘滞状态，跳过设置会让前一条 pipeline 的 state 残留生效（评审修复 C2；回归 `r445_pipeline_overrides_sticky_depth_state`） |
| `disable_culling`/`wireframe`/winding | Metal 的 cull/fill/winding 是 **encoder 状态**（非 PSO），payload 记录、bind 时 `setCullMode:`/`setTriangleFillMode:`/`setFrontFacingWinding:Clockwise`（VK frontFace 对齐） |
| `alpha_blend`/`alpha_blend_color_only` | attachment blendingEnabled + srcAlpha/oneMinusSrcAlpha Add（rgb/alpha 同式）；color_only 且 >1 attachment 时 RT1 关混合（Metal 恒有 independent blend，无 VK 的 feature 门） |
| `point_list` | payload 记录，`rhi_cmd_draw` 用 `MTLPrimitiveTypePoint`（R168-C） |
| `color_format` | 默认（`R8G8B8A8_UNORM==0`）= swapchain 格式（macOS 为 BGRA8）；否则经格式映射层。**Metal 无 VK 的 render-pass variant 机制**：pipeline 绑定单格式，跨格式复用需按 format 建多条 pipeline（已知边界，引擎集成归 Task 11） |
| `sample_count` | `rasterSampleCount`（0→1），超 capabilities 位集 fail-closed |
| `mrt_attachment_count`/`mrt_formats` | 逐 attachment 设 pixelFormat（≤5，共享 `rhi_mrt_formats_valid` 门）；`depthAttachmentPixelFormat=Depth32Float`（所有 RHI pass 都带 D32 深度，屏幕 pass 自 Task 8 起也带——见下） |
| `terrain_layout`/`water_layout`/`combined_aa_layout`/`combined_color_layout`/`uses_textures`/`uses_texel_buffer`/`uses_storage` | 存入 payload `desc` 拷贝（VK build_desc 同形），绑定表/偏移消费归 Task 11 |
| `is_compute` | fail-closed 记日志（Task 9 家族） |

### 屏幕 pass 深度附件

VK swapchain pass 带 D32 深度附件；Metal 屏幕 pass 自 Task 5 起只有
color。Task 8 的 pipeline 一律声明 `depthAttachmentPixelFormat=D32Float`，
Metal 校验要求 pass 与 PSO 格式一致，故 `MetalBackend` 增
`screen_depth`（drawable 尺寸的私有 D32 texture，尺寸漂移时懒重建；
旧 texture 由在飞帧的 encoder retain，release 不悬垂）。屏幕 pass
depth 恒 `Clear 1.0 / Store`（VK parity）。

### FBO 族（R616/R617/R618/R619）

Metal 无 framebuffer 对象：`RHIOffscreenFBO`/`RHIMRTFBO`/
`RHIShadowMap`/`RHICubemapDepthFBO` = texture 句柄组 + 小 payload
（offscreen 带 R619 clear_color 与 MSAA texture；MRT 带 attachment
计数与格式表）。bind = 现场组 `MTLRenderPassDescriptor`：

- `rhi_offscreen_fbo_bind`：color `Clear`（per-FBO clear color，默认
  {0.05,0.05,0.1,1.0}）+ depth `Clear 1.0`；`bind_load`：全 `Load`。
  由 `fbo_bind_clears_default_and_bind_load_preserves` 像素级钉死
  （含 ±1 unorm 舍入容差）。
- `rhi_mrt_fbo_bind`：每 attachment `Clear (0,0,0,0)` + depth `Clear 1.0`；
  `bind_load` 全 `Load`。`mrt_two_attachments_distinct_colors` 钉双色
  分别落位；`mrt_five_attachments_create_and_clear` 钉 5 上限 + 6 拒绝。
- `rhi_cmd_bind_shadow_map` / `rhi_cubemap_depth_fbo_bind_face`：
  depth-only pass `Clear 1.0`（无 load 孪生，R618）；cubemap 经
  `depthAttachment.slice` 选面。D32 读回全 1.0f 钉死。
- MSAA FBO：`MTLTextureType2DMultisample` color/depth +
  `storeAction=MultisampleResolve` 到单样 resolve texture 的完整支路
  已实现（`color_resolve_supported==true` 的消费点），但经公开 API
  **当前不可达**：共享校验器 `rhi_offscreen_fbo_desc_validate` 要求
  color+depth resolve 双支持，而 Task 3 把 `depth_resolve_supported`
  fail-closed 为 false——`offscreen_fbo_msaa_desc_fails_closed` 钉死
  该门（VK 同形门）。

### shader 过渡路径（Task 8 内嵌桩 → Task 10 切换）

`rhi_shader_create{,_compute}` 走 `newLibraryWithSource:` 运行时编译，
entry 约定 `vs_main`/`fs_main`/`cs_main`；payload 同时 retain
library + function（function 不得长于 library）。Task 10 的 manifest/
metallib 加载落地后改为从 `MetalBackend.library` 解析函数，本路径只
保留为测试桩。

### 顺手项（Task 8 内闭环）

- `device_lost_latch` → `_Atomic bool`（completion handler 在任意队列
  写、API 线程读；`metal_note_device_lost` 改 `atomic_exchange` 只记
  首次日志）。Task 4/5 评审遗留 minor。
- frame_end/device_destroy/clear_color 的 encoder 收尾统一走
  `metal_end_render_encoder`。

### 评审修复轮（C1/C2/I1/I2 + M1/M2 记录）

- **C1（pass 内 clear_color 劫持屏幕 pass）**：`RHICmdBuffer` 记录当前 pass
  目标（`pass_kind`/`pass_target`/`pass_w,h`/`pass_face`，各 bind 路径与
  屏幕 pass 开口处设置，`metal_end_render_encoder` 复位）。pass 内
  `rhi_cmd_clear_color` 重开**同一目标**的 pass 对齐 VK
  `vkCmdClearAttachments` 语义：color attachment 0 Clear = 调用者颜色
  （offscreen 覆盖 R619 per-FBO 色；MRT 其余 attachment Load 保留），
  **depth Load**（VK 清 color 不动 depth）；depth-only 目标（shadow/cube
  face）重开 depth Clear 1.0；屏幕目标 depth Load。回归
  `mrt_clear_color_after_bind_targets_mrt`（bind→clear_color→读回 att0 蓝、
  att1 保留）。
- **C2**：见上表 R445 行。
- **I1（pass 切换后 bound_pipeline 滞留）**：`metal_end_render_encoder`
  一并复位 `bound_pipeline = RHI_HANDLE_NULL`（VK unbind_shadow_map 的
  `current_pipeline = NULL` parity）；draw 对空句柄走既有 fail-closed
  日志分支。回归 `pass_switch_invalidates_bound_pipeline`（修复前真机
  SIGSEGV exit=139——encoder 无 PSO 直接 drawPrimitives；修复后日志 +
  `rhi_device_idle` 存活断言通过）。
- **I2（MRC new* +1 再 retain 泄漏）**：去掉本 Task 新增的 5 处多余
  retain（shader library/function、depth state cache、render PSO、
  screen_depth、render-target texture alloc），释放点不变。注：Task 7
  资源族（buffer/texture/sampler create）存在同形模式，超出本次修复
  范围，列为后续清理候选。
- **M1（记录）**：unbind 重开屏幕 pass 的清屏色用 `cmd->clear_color`
  （`rhi_cmd_clear_color` 拥有权），VK 烘焙 {0.2,0.25,0.35,1.0}；
  rhi.h 未规定该值，引擎每帧显式 set，差异无可观测影响。
- **M2（记录）**：`metal_screen_unbind` 的 viewport 用 caller 的
  screen_w/h，而 `metal_ensure_screen_depth` 的深度纹理尺寸取
  dev->width/height——viewport 参数可与 dev 尺寸短暂不一致（调用者传
  逻辑尺寸），深度纹理永远跟 drawable 实际尺寸；两者语义不同属预期。

## Task 9：compute / blit / screenshot / indirect / gpu timer

### compute

- `rhi_pipeline_create` 的 `is_compute` 分支：compute shader 句柄走
  `desc->frag`（VK 约定），`newComputePipelineStateWithFunction:`，payload
  `compute` + `is_compute`；深度/顶点状态不适用。
- encoder 生命周期扩展：同一 cmd 同时最多一个 encoder 的规则覆盖 compute
  ——`metal_open_render_pass` 先关 compute encoder；`metal_ensure_compute_encoder`
  先关 render encoder；`frame_end`/destroy 走 `metal_end_encoders` 两者并关。
- `rhi_cmd_dispatch`：`dispatchThreadgroups:threadsPerThreadgroup:`，threadgroup
  = min(pipeline `maxTotalThreadsPerThreadgroup`, 64)（8x8 惯例的 1D 形式）；
  dispatch 计数单位是**组**（VK parity，调用者自己除以组尺寸）。
- `rhi_cmd_bind_storage_buffer` → `setBuffer:offset:0 atIndex:`；
  `rhi_cmd_bind_image_texture`/`_cubemap_face` → `setTexture:atIndex:`，mip/face
  经 `newTextureViewWithPixelFormat:textureType:levels:slices:`（2D 视图，new*
  +1 即用即 release）；`rhi_cmd_memory_barrier` → 仅 compute encoder 内
  `memoryBarrierWithScope:Buffers|Textures`（跨 encoder hazard Metal 自动跟踪）。

### blit 命令族（fill/update/copy）

`metal_blit_interlude`：先关现有 encoder，在帧 command buffer 上开临时 blit
encoder，编码后即 endEncoding（对象 autoreleased）。`fill_buffer` 保持 VK 的
u32-word/4 字节对齐契约，但 Metal `fillBuffer:range:value:` 只接受**字节**
pattern——非字节齐值的 u32 fail-closed（引擎调用方全部填 0）；offset+size 按
R425 钳制。`update_buffer` 保持 VK 65536B/4B 对齐上限，经临时 shared staging
buffer（command buffer retain 至执行）。`copy_buffer` 双侧钳制。
**已知边界**：blit/compute 插入段结束后不自动恢复原 render pass（VK 的
suspend/resume 语义）——调用方需以 bind_load 重绑；自动 resume 决策归 Task 11。

### screenshot（rhi.h:815-826 / R577）

acquire→present 窗口语义在 Metal 的等价实现：drawable 自 acquire retain 到
**present**（frame_end 不再提前释放），`rhi_screenshot` 先经 `metal_drain`
有界 drain（绝不裸 waitUntilCompleted），再 blit drawable texture → shared
staging → `metal_commit_wait`。present 后 drawable==nil → false + LOG。
region 走共享 `rhi_screenshot_region_validate`。字节序 = drawable 原生 BGRA
（VK 裸拷贝 BGRA swapchain 同）。前提：`layer.framebufferOnly=NO`（device
create 时置位；默认 YES 禁止 blit 读回）。

### indirect

`draw_indirect`/`draw_indexed_indirect`：arg record ABI 与 VK 位级一致
（16B/20B 五字段），Metal 原生 `indirectBuffer:` 单条命令按 draw_count 循环
（Metal 无多 draw indirect buffer 批量入口）。index buffer 经
`rhi_cmd_bind_index_buffer` 记录（cmd 簿记，draw 时应用）；`draw_indexed`/
`draw_base` 顺带接线（同族最小面）。`_count` 变体 fail-closed（见矩阵决策记录）。

### gpu timer

见矩阵「Metal 决策记录（计划 C Task 9）」。支持的主机上：stage-boundary 采样
仅 render encoder 合法 → pass 外的 begin/end 挂进 `cmd->pending_timers[]`，
本帧下一个 pass 开口时补采样（`metal_drain_pending_timer_samples`，并重定向
完成门槛到实际落点帧）；`sampled_mask` 双 bit 防止读到未落地样本；
`elapsed_ms` 轮询 frame_event signaledValue（VK R430 不等待 parity），mach
timebase 换算 ms。**挂起表是裸指针**：`rhi_gpu_timer_destroy` 扫描
`frame_cmd->pending_timers[]` 摘除自身（评审修复 I2，回归
`gpu_timer_destroy_with_pending_sample_is_safe`）；降级主机（csb==nil）同样
挂起/摘除，路径在所有主机一致可测。

### screenshot 调用时序（评审记录 M6）

契约合法窗口是 acquire→present 全程，但 **mid-frame（frame_end 前）调用读到
的是上一个提交帧的像素**（录制中未提交的工作不可见，VK `vkDeviceWaitIdle`
同语义）；引擎只应在 frame_end 后 / present 前调用（main.c 既有截图点）。

## Task 12：加速结构（MTLAccelerationStructure）+ MSL buffer 索引分配表

RT 能力门 = Task 3 capability bit（supportsRaytracing）+ macOS 13+（triangle
descriptor 的 vertexFormat 为 13+ API）——任一缺失全入口 fail-closed
（NULL/false/no-op+LOG，`*_ex` 经既有能力契约暴露 UNSUPPORTED）。
`RHI_FEATURE_RAY_TRACING_PIPELINE` 永不置位。BLAS build 复用 RHI buffer 的
MTLBuffer（zero-copy）；TLAS 走 VK-ABI 64B record →
`MTLAccelerationStructureUserIDInstanceDescriptor` 转换（转置/解包逐项见
rhi_metal.m `metal_as_convert_tlas_record` 注释），BLAS 数组经
`instancedAccelerationStructures` 提供、索引 0。

**"device address" 选型**：Metal 4 把 `MTLResourceID` 改为不透明 struct
（无 u64 转换），故 `get_device_address` 返回**合成地址 = payload 指针**，
转换侧经 `MetalBackend.as_registry` 线性查找回 payload——自洽闭环，
记录在 `metal_as_convert_tlas_record` 注释。

### MSL buffer 索引分配表（跨 Task 10-12 的全局契约）

| 索引 | 用途 | 来源 |
|---|---|---|
| 0 | 顶点 buffer（`MTLVertexDescriptor.layouts[0].bufferIndex`，`rhi_cmd_bind_vertex_buffer` 仍为 Task 13 stub——接入时不得改动 flattened 资源索引方案，顶点流语义独立） | Task 8 |
| 0..24 | flattened shader 资源（uniform/buffer block：`set*8+binding`，实测语料最大 24；flatten 护栏 `nb>27` fail-closed） | Task 10/12 |
| 25..27 | 预留增长（未分配） | — |
| 28 | ray-query 加速结构（`setAccelerationStructure:atBufferIndex:`） | Task 12 |
| 29 | push constants（`setVertex/Fragment/Bytes:`） | Task 10/11 |
| 30 | `spvBufferSizeConstants`（spirv-cross 为 SSBO `.length()` 自动保留） | 工具链 |

纹理索引：`set*16+binding`（image/samplerBuffer）与 combined sampler 的
`set*4+binding`（sampler 同值）；sampler 上限 15。索引越界/重复由 metal
编译器诚实失败 + reflection 一致性测试抽查。

### 已知边界（Task 12 评审 M3）

`rhi_cmd_bind_acceleration_structure` 只做 slot 解析、不查
`metal_rt_available`：无 RT 能力的主机上 `create` 已 fail-closed，合法 AS
句柄根本不存在，故 bind 的能力门在真实主机不可达（bogus handle 走
LOG_ERROR + no-op，已有断言）。bind 索引 28 与 flatten 护栏（`nb>27`）
共同保证 shader 资源永不落到 AS 槽。


## Task 14 移交清单（Task 15 处置完毕，2026-10-16）

1. **spvBufferSizeConstants（P0，已修）**：MetalShader/MetalPipeline 在 shader
   创建时从 MSL 文本解析 buffer-size 常数表（alias→signature buffer(N) 映射）；
   cmd 记录 storage 绑定（generation 校验句柄），dispatch 重放绑定（I2 同规则）
   并经 setBytes 把各 SSBO 字节数喂到 buffer(25)；graphics 管线带 bsc 声明时
   vertex stage 重放 SSBO + setVertexBytes。缺绑定 fail-closed。TDD：
   `buffer_size_constants_fed_to_kernel` 红（readback 无写入）→绿；M2 上
   42/42（含 METAL_DEVICE_WRAPPER_TYPE=1）。（commit 74cb7723）
2. **rhi_cmd_bind_material_textures（已修，低成本）**：VK 9 槽契约照搬
   （albedo/shadow/mr/normal/emissive/ssao + IBL 槽 albedo 兜底，单一 combined
   sampler），terrain 贴图通道生效（commit f7bf5c7c）。**_ibl 变体未修**：
   14 参数含 cubemap + 点影数组语义，排期见第 6 项。
3. **defrd_inject_define（已删）**：复用 `shader_inject_define`（#version 扫描版），
   消除首行切分的字节等价脆弱点（commit 74cb7723）。
4. **indirect_count 阴影（维持 fail-closed，留缺口）**：
   `rhi_cmd_draw_indexed_indirect_count` 无 Metal 等价，MTLIndirectCommandBuffer
   是另一套编码模型、软件 count 展开需回读（引入同步点）——成本均超本计划
   余量。如实登记：CSM/点影 unified shadow compaction 绘制阶段在 Metal 下
   no-op（LOG_ERROR），CSM/点影深度图为引擎功能缺口。
5. **y-flip（已取证 + 修 readback）**：present 朝向正确（GL 约定：NDC +Y 朝上、
   正视口；VK 走负视口高度故其 readback 天然 bottom-up）。`rhi_screenshot`
   曾以 top-down 交付违反 GL bottom-up 契约（main.c BMP 写出依赖之），
   已在后端翻转行序（commit bc1e5481）；修复后 Metal 与 MoltenVK 的
   BREAK_SCREENSHOT 截图朝向一致（逐像素 + 目视）。注意
   `rhi_texture_read_pixels` 仍是 top-down（测试用中心像素，方向无关）——
   若未来有引擎消费方依赖 bottom-up 需另评。
6. **binder stub 面（部分修，部分留）**：已修 `bind_textures_multi`（postfx
   TAA/SSR/DoF 等 sampler 绑定，commit f7bf5c7c）与 `bind_material_textures`。
   遗留（LOG_ERROR fail-loud，不构成崩溃）：`bind_material_textures_ibl`
   （PBR 贴图路径——Metal demo 当前以 fallback 贴图渲染）、
   `bind_texel_buffers`（clustered 光照数据）、`set_shadow_viewport`、
   `transition_depth_to_read`、`clear_color_attachment`/`clear_depth`（命令级，
   已有 pass 级等价物兜底）、`set_depth_func_*`/`set_cull_face`（encoder 态）。
   engine_demo 在 METAL_DEVICE_WRAPPER_TYPE=1 下 --frames 10 退出 0（附
   pixelFormat 变体缓存：postfx 管线声明 BGRA8 却绘入 R16F FBO 的引擎级
   UB——VK/D3D12 驱动容忍、Metal validation 拒绝——后端按 open pass 实际
   color0 重建管线态，见 f7bf5c7c）。
7. **M4（iOS 量程）**：texture flatten 公式上界 34（set2b2）超 iOS [[texture]]
   上限 31。2026-10-27 本机 Simulator 的默认 FORWARD 已有真实帧与截图，但只覆盖
   当前实际绑定组合；更大 set/binding 和真机 GPU family 的量程仍需复评，CI 仍 build-only。
8. **M6（已处置）**：gen_metal_shader_manifest 宿主/目标分离——iOS 交叉编译
   时宿主编译 `gen_metal_shader_manifest_host`（CMakeLists M6 注释）。
   `xcrun metal` SDK 与 `CMAKE_OSX_SYSROOT` 一致：设备 `iphoneos`、Simulator
   `iphonesimulator`；不能将设备版 metallib 直接用于 Simulator。宿主 manifest
   工具另用 macOS 目标三元组及 SDK，并清理 Xcode 传入的目标环境；自动重配置
   实测产物为 macOS `platform 1`，不会混入 Simulator `platform 7`。
9. **iOS lifecycle（2026-10-27 已补本机 harness）**：`ios_main.m` 以 UIWindowScene
   创建 Metal view，并接入 viewport、主触摸和 suspend/resume。本机已完成安装、
   300 帧与正常 shutdown、RHI/屏幕截图及同进程后台恢复。XCTest 旋转/点击 1/1
   通过，窗口完成竖→横→竖切换，主按钮 down/up 由引擎线程消费；横屏稳定期的
   simctl 截图为 2622x1206，画面完整且 HUD 朝向正确。CI lane 仍 compile-only，
   真机 GPU_RUNTIME 未覆盖。详见 Build_Guide 的 Simulator 命令和
   `docs/rhi_backend_evidence.md` 的证据台账。
10. **clustered 实例化品红色块（2026-10-27 已修）**：默认 FORWARD clustered 路径下，
    ECS 实例化的 DamagedHelmet 在 Metal 渲染成大块品红，MoltenVK 正常。根因是
    `metal_uniform_location` 先命中 `uses_storage` 短表（仅 `push.view/proj`，供粒子用），
    而 R590/R591 的 clustered 实例化/蒙皮管线也设了 `uses_storage`（顶点 SSBO），
    于是 `u_camera_pos`、`u_ambient`、光源计数和材质系数全部解析为 -1，片元读到
    陈旧的 push 字节。修复后该短表只用于非 clustered 的 storage 管线，与 VK 反射结果
    一致。`test_rhi_metal_resources` 新增
    `clustered_storage_variant_keeps_clustered_push_table`（实例化与蒙皮两种变体），
    该用例在修复前失败、修复后通过；截图中品红像素计数从 11719 降为 0。
11. **默认画面发白、头盔缺失、上下镜像叠加（2026-10-28 已修，4 处）**：同一机位
    （`BREAK_CAM=0,9,16,0,-25 BREAK_UI=0 BREAK_SCREENSHOT=60`）下，Metal 与 MoltenVK
    的平均绝对差（mad，缩略图 0–255）从 32 降到约 7，blinn 路径 6.7，与 VK 同量级。
    - `rhi_cmd_draw_indexed_base` / `rhi_cmd_draw_indexed_instanced_base` 之前只记
      LOG_ERROR 不绘制。命令缓冲 replay、mega 阴影、LOD、ECS LOD 的间接外绘制全部
      丢失。现按 `vkCmdDrawIndexed` 语义实现（`firstIndex` 折成字节偏移，
      `vertex_offset`→`baseVertex`，`first_instance`→`baseInstance`）。
    - storage buffer 绑定原先不分计算/图形，所有索引（0..24）在每次 storage 管线绘制时
      重放。cluster 剔除的 `light_data`（计算）与粒子 SSBO 会覆盖 vertex buffer 索引 0
      的网格顶点，头盔变成尖刺白块，且每帧不同。现在图形绑定单独记录
      （`bound_gfx_storage[]`），只重放该管线自己的 `set*8..set*8+7` 范围。
    - `rhi_cmd_bind_texel_buffers` 直接设到编码器、未记录。实例上传（blit）结束渲染
      编码器后，clustered 光照网格纹理（16/17）丢失。现记录到 `cmd->bound_texel[2]`，
      在 `metal_flush_push` 重放。
    - 离屏和 MRT pass 之前用默认视口，NDC y=-1 落在纹理最后一行，与 VK/GL/D3D12
      相反（后处理按 `uv = ndc*0.5+0.5` 采样）。运动模糊、SSS 等 pass 因此读到上下翻转的
      输入，最终画面叠上一份镜像。现在离屏/MRT pass 使用负高度视口，屏幕 pass 不变。
    - 另外：计算/blit 插入后保留已绑定图形管线；`rhi_cmd_bind_deferred_gbuf_textures`
      由 stub 改为按 VK 槽位实现。
    - 新增测试：`draw_indexed_base_honors_first_index_and_vertex_offset`、
      `texel_buffers_replay_across_blit_interlude`、
      `compute_storage_bind_does_not_clobber_graphics_vbo`、
      `offscreen_viewport_stores_ndc_minus_y_in_row_zero`，修复前均失败。
    - 延迟路径近黑已在第 12 条修复。
12. **延迟渲染整屏近黑（2026-10-28 已修）**：G-Buffer 几何 pass 回读显示 92 万像素里
    只写了约 1.7 千个，albedo 附件全为 0，光照 pass 本身没问题，只是无物可着色。
    原因：`deferred_bind_gbuffer_factors` 在 `bind_material` 和 `bind_vertex_buffer`
    之间调用 `rhi_cmd_update_buffer`，这在 Metal 上是 blit 插入，会结束渲染编码器并把
    MRT pass 标记为挂起。随后的顶点缓冲、`bind_texture`、`bind_material_textures`、
    `bind_textures_multi` 在 `render_encoder == nil` 时直接返回、没有恢复 pass，顶点缓冲
    没绑上，绘制被丢弃。此外片元纹理/采样器和顶点缓冲在 Metal 是编码器状态，VK 是
    命令缓冲状态，恢复 pass 时也没有被带回。
    修复（`rhi_metal.m`）：上述四个绑定函数先调用 `metal_resume_render_pass_if_needed`；
    片元纹理/采样器槽 0–31 与顶点缓冲在绑定时带 retain 记录，恢复 pass 时在重新应用
    管线前重放；新开 pass、帧开始和设备销毁时清空（`resuming` 标志避免恢复路径清空）。
    新增测试 `fragment_textures_and_vbo_replay_across_blit_interlude`，修复前失败。
    结果：延迟路径亮度 0.7→37.3（VK 37.7），与 VK 的 mad 37.0→4.5；
    默认 clustered 7.0、blinn 7.2，无回退。
