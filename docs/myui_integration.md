# myui 集成与 Break RHI 后端

## 可选渲染后端配置（2026-09-07）

可复用入口提供 `MYUI_GLES2`、`MYUI_GL_DESKTOP` 和 `MYUI_VULKAN` 三个显式选项。
选项关闭时不会执行对应的依赖探测、不会向 target 添加头文件或链接库，并保留同名
API 的安全 stub；软件后端因此可在无图形开发包的 headless 环境独立构建。Vulkan
默认关闭，只有显式开启才查找 Vulkan；Break 工程设置 `ENGINE_VULKAN=ON` 或 macOS
平台时会自动启用 myui Vulkan 能力。

Vulkan GLSL 源文件位于 `engine/src/myui/myr/vulkan_shaders`，已提交的 `.inc` 是构建
输入，不依赖宿主仓库根目录。安装 `glslangValidator` 后，可在启用 `MYUI_VULKAN` 的
构建中执行 `cmake --build <build-dir> --target vulkan_shaders_regen`；生成器使用
模块自身的 CMake 脚本，不读取或写入 `${CMAKE_SOURCE_DIR}` 外部路径。

Vulkan canvas 只消费 PAL 创建好的 opaque surface handle，不在 `myr` 内定义
`VK_USE_PLATFORM_XLIB_KHR` 或 `VK_USE_PLATFORM_WAYLAND_KHR`，因此不会把 X11/Wayland
头文件泄漏到 Windows、macOS 或其他交叉编译目标。各平台 PAL/宿主负责选择并创建对应
WSI surface，渲染模块只依赖 Vulkan core API。

WSI instance 扩展通过版本化 `my_pal_vulkan_provider_t` sidecar 查询，不改变 frozen PAL
window vtable。provider 返回的数组只借用到查询结束，最多 8 个名称；公共查询会将名称
复制到调用方固定存储，窗口路径再把该固定存储传给 Vulkan，避免 provider 在查询后释放
数组造成悬空指针。myr 也会复制扩展名到共享实例状态，并拒绝活动实例未启用的新增扩展。
sidecar 只负责协商，surface 的创建与销毁仍必须由 PAL 既有 `vk_create_surface` slot 和
myui canvas 所有权协议完成。
没有 provider 的旧 PAL 继续使用兼容路径；没有 surface slot 的 PAL 不会被误判为完整
Vulkan 窗口后端。

窗口 PAL 创建 surface 前必须使用 `my_vgcanvas_vulkan_instance_acquire()`，在 surface
创建失败或 canvas 创建失败时调用 `my_vgcanvas_vulkan_instance_release()`；成功创建
canvas 后也要释放这个临时 lease，canvas 自身会持有长期 backend 引用。旧的
`my_vgcanvas_vulkan_instance()` 现在只是无副作用 peek，不会隐式初始化 Vulkan。

## Glyph bitmap lease（2026-09-06）

`my_font_get_glyph()` 和 `my_font_get_glyph_id()` 返回的 bitmap 通过 glyph
lease 借用。调用方必须在消费完 bitmap 后调用 `my_font_glyph_release()`，并在
释放字体前释放所有成功取得的 glyph；字体销毁请求会延迟到最后一个 glyph lease
释放，因此调用方可以安全地先发起 destroy、再释放 glyph，但 live glyph 结构不能
复制后分别释放。
FreeType/STB 的 cache 淘汰不会释放仍有 lease 的位图：缓存满时只淘汰零引用
槽位，必要时使用 font-owned overflow entry；overflow entry 数量最多为
`min(cache_capacity, MY_FONT_MAX_GLYPH_OVERFLOW_ENTRIES)`，超出预算返回
`MY_RET_OOM`，不会释放仍被 lease 持有的 bitmap。正常命中和绘制路径不产生额外
分配或全局锁竞争。

soft、GLES2、Vulkan 和 Break RHI 已在上传/采样完成后释放 glyph lease；布局、
段落和 text-area 的 advance-only 查询也会立即释放。该 lease 只保护 bitmap
生命周期，不把 font 句柄变成可并发销毁对象；宿主仍须保证 font 在所有 lease
释放前保持有效。

内置 bitmap font 也遵循同一协议：成功的 glyph 查询持有轻量 owner lease，先执行
`my_font_destroy()` 时延迟释放 font，最后一次 `my_font_glyph_release()` 后完成回收；
销毁请求发布后不再接受新的 glyph 查询。

## window-manager `on_open` callback context lease（2026-09-06）

`on_open` 的长期 context 可使用 `my_window_manager_set_on_open_owned()` 或
`my_window_manager_set_on_open_lease()`。owned 入口在 hook 被替换或 manager 销毁时调用
一次 destructor；lease 入口成功后 manager 持有一份引用，调用方可释放自己的引用，并在
owner teardown 前调用 `my_emitter_context_lease_invalidate()`。打开窗口时，无效 lease 会
跳过新的 callback；已经开始的 callback 可自然完成。替换 hook 采用先取得新状态、再释放
旧状态的提交顺序；若 setter 在 `on_open` callback 内重入，旧 owned context/lease 会进入
retired 队列，最外层 manager callback 返回后再释放，因此 destructor 不会在原 callback
返回前运行。分配失败不会丢失当前 hook，也不会转移新 lease/owned context 的所有权。

旧的 `my_window_manager_set_on_open()` 仍是 borrowed 兼容入口。上述 lease 只保护 callback
context，不保活 `my_window_manager_t` 或 `my_window_t`，所有 hook 和窗口操作仍必须在所属
UI 主循环线程执行。

## 菜单与 dialog callback context lease（2026-09-06）

菜单选择和 dialog 结果 callback 也支持 `my_emitter_context_lease_t`。菜单使用
`my_menu_popup_lease()`，dialog 使用 `my_dialog_open_lease()`；成功注册后控件持有一份
lease 引用，调用方可以立即 `my_emitter_context_lease_unref()` 自己的引用。owner teardown
前先调用 `my_emitter_context_lease_invalidate()`，随后尚未开始的 callback 会被跳过，已经
进入的 callback 允许返回；callback 内失效同样安全。关闭、窗口关闭、manager 销毁和打开
失败都会释放内部引用，lease 的 context destructor 在最后一个引用释放时恰好执行一次。

无效 lease 的注册返回 `MY_RET_INVALID_PARAMS` 且不转移所有权。普通
`my_menu_popup()`/`my_dialog_open()` 和 owned 入口保持 ABI/行为兼容；lease 保护的是
callback context，不保护 menu、dialog、window 或 manager 本身，所有 UI 操作仍必须在
所属主循环线程执行。

## Event context lease（2026-09-06）

需要让 borrowed event context 在 owner 销毁前失效时，使用 lease API：

```c
my_emitter_context_lease_t* lease =
    my_emitter_context_lease_create(a, context, destroy_context);
uint32_t id = my_emitter_on_lease(emitter, "changed", callback, lease);
/* owner teardown: invalidate before releasing its context */
my_emitter_context_lease_invalidate(lease);
my_emitter_context_lease_unref(lease);
```

成功注册后 emitter 持有 lease 引用；`invalidate()` 会阻止尚未开始的回调，已经进入的
回调可以完成。移除 listener 或销毁 emitter 后最后一个引用执行一次 destructor。调用方必须
在 owner teardown 前失效 lease，并保持 lease 句柄本身存活到完成失效；普通 `my_emitter_on()`
仍是完全 borrowed 兼容入口。widget 事件可使用同一协议的 `my_widget_on_lease()`，无需访问
widget 内部 emitter。`my_window_add_close_listener_lease()` 和
`my_window_manager_add_destroy_listener_lease()` 采用同一 lease：关闭/销毁前已失效的 context
不会进入 callback，listener 拆除后才释放其 lease 引用。lease 闸门仅作用于 guarded listener，
不增加普通事件分发的同步开销。

## 字体 metric vtable 边界（2026-09-06）

字体后端的 `descent` 是可选 vtable slot。调用方应使用 `my_font_descent()`，而不是直接
解引用 `font->vtable->descent`；空字体、空 vtable 或缺失 slot 返回 0。内置 font chain
同样遵守该契约，确保部分初始化或能力不完整的跨平台字体后端不会触发空函数指针。
检查是 O(1)，不进入字体 shaping 和布局的额外分配路径。

## FreeType 字体并发访问边界（2026-09-06）

同一个 `my_font_ft_t` 可以被多个工作线程并发调用 `measure`、字形查询、glyph-id
rasterization、shaping、capability/variation 查询；FreeType 的 `FT_Face`、当前字号和
内部 LRU cache 由字体对象级跨平台互斥保护。锁只覆盖 provider 的状态访问，不进入字体链
选择、paragraph/layout cache 或绘制后端的热路径；不同字体对象之间不会共享该互斥，因此
并发访问不同 face 不会产生不必要的串行化。FreeType 进程级 library 初始化也使用一次性
无锁快路径加自旋初始化保护。

字体对象的销毁仍必须由宿主在所有调用返回后执行；该锁不是对象生命周期引用，也不把
`my_font_t*` 变成可跨线程销毁的句柄。STB、bitmap 和第三方 provider 的线程保证仍由
各自 provider 契约决定。缺少 FreeType/HarfBuzz 的构建继续走显式回退，不因该同步策略
增加平台依赖。

## LCD 渲染后端 vtable 边界（2026-09-06）

`my_lcd_*` 对空 LCD、空 vtable 和缺失 slot 统一安全失败：查询返回零、空 framebuffer 或
无效 pixel-format，帧/绘制操作分别返回 `MY_RET_INVALID_PARAMS` 或
`MY_RET_NOT_SUPPORTED`；destroy 无操作安全。检查是 O(1) 指针判断，位于每次调用的 API
边界，不添加分配、锁或后端特例，故 soft、GLES、Vulkan 与平台 LCD 保持同一契约。

## MVVM target 与 array vtable 边界（2026-09-06）

所有 `my_binding_target_*` 和 `my_view_model_array_*` 包装器都先检查对象、vtable 与所需
callback slot。无效 target/array 不会解引用空 vtable：写入类接口返回确定错误，查询类
接口返回零/空值，缺失 target 能力返回 `MY_RET_NOT_SUPPORTED`。items binding 在创建和重建
前也校验 `rebuild_items`，使自定义适配器部分初始化安全失败。判断仅为固定 O(1) 指针检查，
不进入绘制或布局热路径。

## Emitter listener ID 回绕安全（2026-09-06）

监听器 ID 保持非零且在活动监听器生命周期内唯一。正常注册使用单调 O(1) 分配；达到
`UINT32_MAX` 后进入回绕冷路径，从 ID `1` 开始跳过仍活动的 ID，并在没有可用 ID 时
返回失败，不影响现有监听器。事件分发、布局和绘制路径不执行该扫描。

## MVVM 绑定规则严格解析（2026-09-06）

绑定规则解析在进入 MVVM 创建事务前完成固定大小的语法校验。解析器拒绝空选项、重复
选项、未配对/多余括号，以及在 `Condition=...` 专用条件体后追加普通选项；嵌套的
validator 参数仍按匹配括号复制到固定容量字段。选项去重使用位图，括号检查为一次线性
扫描，不进入布局、绘制或事件热路径。

`v:items={items, ItemTemplate=row}` 和 `v:visible={Condition=flag}` 是专用语法；
`Items=`、选项形式的 `Condition=` 继续返回 `MY_RET_NOT_SUPPORTED`，避免未定义的
绑定语义被静默接受。无效规则不会发布部分填充的 binding rule。

## Shaping 能力回退契约（2026-09-06）

`my_font_shape_support_query()` 明确返回 `MY_FONT_SHAPE_UNSUPPORTED` 时，公共
`my_font_shape_ex()` 不会继续把带有 language/script/features 的请求伪装成成功；尤其是
requested OpenType feature 不支持时直接返回 `MY_RET_NOT_SUPPORTED`，避免 provider 静默忽略
feature。没有显式 feature 的旧请求仍可按 language -> script -> legacy `shape` 顺序回退；
能力为 `UNKNOWN` 时保留最佳努力调用，以兼容未实现 capability provider 的旧字体。这样
“不支持”和“未知”在安全性与兼容性之间有明确边界，且只发生在 shaping 冷路径。

## 引用计数溢出契约（2026-09-06）

内部共享对象、UI command/scope、image loader lease 和 list adapter lease 的引用递增均使用
无锁 CAS 饱和保护：计数达到 `UINT_MAX`/`SIZE_MAX` 时拒绝继续递增，不允许回绕到 0；对应
释放操作对饱和值不做递减，因此对象保持安全但可能常驻，避免溢出制造提前析构和 UAF。该
检查只发生在引用生命周期边界，不进入绘制、布局或滚动热路径。应用不应依赖计数达到上限
来管理资源，正常所有权仍须成对 `ref`/`unref`；跨线程取得引用前必须仍持有一个有效引用。

## 回调与 widget 生命周期

`changed`、`click` 等同步监听器允许在回调中移除并释放当前 widget。edit、text-area 和
button 的事件入口会在 handler 整体执行期间持有临时引用，因此回调返回后仍可安全完成
光标/IME、冷却和失效区域更新；编辑器撤销/重做回调同样遵循该事务边界。宿主自定义 widget
若在 emitter 返回后继续访问自身，应采用相同的 `my_widget_ref()`/`my_widget_unref()`
模式；仅依赖 parent tree 引用不足以覆盖“监听器移除自身”的场景。node view、checkbox、
slider、scroll bar 和 MVVM 通知也遵循同一事务规则。该保护不改变单线程 UI loop 约束，
也不替代异步 timer、window manager 和动态 module lease 的关闭顺序。

`my_emitter_destroy()` 也支持在 listener callback 内调用：实现只标记 emitter 关闭，
停止当前 emit 的后续 listener，并在最外层 emit 返回时释放 listener 存储。嵌套 emit
不会提前 dispose。调用方在 destroy 调用后不得再次使用 emitter 句柄；widget/view-model
等拥有 emitter 的对象仍应通过自身生命周期引用保证回调返回前的外层事务安全。

需要让长期 callback context 由 emitter 管理时，使用 `my_emitter_on_owned()`；注销或 emitter
销毁会恰好调用一次 context destructor，注册失败不转移所有权。borrowed `my_emitter_on()`
保持兼容，但 context 生命周期仍由调用方负责。

窗口生命周期监听器同样区分 borrowed 和 owned：需要在窗口关闭或 window manager 销毁时
自动释放 context 时，分别使用 `my_window_add_close_listener_owned()` 或
`my_window_manager_add_destroy_listener_owned()`。成功注册后所有权转移，主动注销和自然
销毁都恰好释放一次；注册失败不转移所有权。监听器与 destructor 仍只能在所属 UI loop
上注册、注销和执行，跨线程调用应改用 `my_ui_command_t`。

实现顺序保证 listener 记录先摘除并释放，再调用 owned context destructor；因此 destructor
可以安全地释放最后一个 window creator 引用或请求 manager 销毁，而不会让 listener API 在
回调返回后继续访问已失效 owner。destructor 本身仍须遵守所属 UI loop 约束。

timer callback 的 context 默认是所属 loop 的借用指针，不会自动延长 widget 生命周期。
因此组件销毁必须在同一 UI loop 上先取消 timer，再释放 widget；窗口/控件销毁链已实现该
顺序。需要在 owner teardown 前主动失效 context 时，可使用 `my_timer_add_lease()`；定时器
持有 lease 引用，失效后尚未开始的 callback 会被跳过并释放定时器，已经开始的 callback
可以自然完成。若 callback 可能重入销毁 timer manager，manager 会延迟到最外层 `fire()` 返回
后释放，并停止同一轮后续 timer。跨线程场景必须使用 `my_ui_command_t` 投递到 loop，不能
直接调用 timer、widget、window 或 RHI API。

本文描述 `engine/src/myui`、`engine/external/SheenBidi` 和
`engine/apps/duanxianxia` 如何接入 Break 引擎的 `Platform` 与 `RHI`。

## List adapter 生命周期

高频刷新优先使用 borrowed adapter；调用方必须让 vtable 和实例覆盖整个绑定周期：
`my_list_view_set_adapter(list, adapter)` 不取得实例所有权。需要把实例生命周期交给
列表时，使用 `my_list_adapter_lease_create()` 创建 lease，再调用
`my_list_view_set_adapter_lease()`；成功后列表持有一份引用，调用方可释放自己的 lease
引用。替换和列表销毁会先回收 active/pool rows，再执行 lease destroy callback；失败或
同步重入不会改变当前 adapter。lease 的引用计数适合跨线程持有，但 adapter vtable 回调
和列表 API 仍只能在所属 UI loop 执行，lease destroy callback 则运行在最终 unref 所在线程。

旧 borrowed API 与 lease API 不应混用同一 adapter 的独立所有权 token；共享同一实例时
应共享同一个 lease 引用。adapter vtable/实例在 lease 存续期间不得修改。

`scroll_view` 的内容仍由 widget tree 持有；除了 `my_scroll_view_set_content()` 替换外，允许
调用方直接从 `my_scroll_view_widget(view)` 移除当前内容。容器的 child-remove hook 会立即
清空内容借用指针并复位 offset，因此后续滚动和测量安全地按空内容处理。该失效处理只运行在
树修改冷路径。

## Image loader 生命周期与缓存

`my_image_set_loader()` 是 borrowed API：loader 的 vtable 和实例必须覆盖所有使用该 image
的绘制周期，传入 NULL 会恢复默认 loader；非法或不完整 vtable 被拒绝且不替换当前 loader。
图片缓存使用 `(loader, lease, path)` 作为键，避免同一 loader 的不同生命周期 token 发生
缓存串线。缓存写入前复制 RGBA 像素并调用 loader 的 `free_data`，所以缓存不依赖 loader
返回对象的分配器或释放方式。加载失败、空像素、非正尺寸和 RGBA 字节数溢出都只绘制占位框，
不会写入缓存；缓存命中仍为 O(1)，这些校验不进入绘制命中后的分配路径。

`my_image_set_loader_lease()` 可为动态 loader 建立显式生命周期保护：image 和缓存条目各持有
一份 lease 引用，最后一份引用释放时才调用 release callback。借用 loader 使用
`my_image_set_loader()` 时不会进入缓存，返回的临时像素在本次绘制后立即通过该 loader 的
`free_data` 释放；因此 borrowed loader 不会被隐式保活，宿主仍须保证 vtable、实例和释放回调
覆盖整个绘制周期。缓存是每个 UI loop 线程的固定容量 LRU，避免跨 loop 锁竞争；命中/未命中
统计使用原子计数，`my_image_cache_clear()` 只清理调用线程的缓存，缓存条目的 lease release
callback 也在调用线程执行。外部销毁 borrowed loader 前必须先停止所有 image 绘制。

## Animator 生命周期与时间边界

`my_animator_animate()` 创建记录后会持有目标 widget 的一份引用，动画完成、显式停止、目标
子树移除或 animator manager 销毁时释放该引用；调用方可以在提交动画后释放自己的 widget
引用，不会让 timer 回调访问悬空对象。动画记录只在 manager 的动画数组中维护，完成记录在
tick/停止冷路径回收，不会随长时间运行的界面无限增长。

动画开始时间与延迟判断使用差值比较，避免 `start + delay` 在 `uint64_t` 上溢出；时钟回拨时
动画不会提前完成。动画 ID 始终为非零值，回绕时跳过仍在使用的 ID；无法分配安全 ID 时
提交失败且不发布半成品。动画仍只在所属 UI loop 执行，非动画状态不创建 timer，活动状态
最多共享一个 animator timer，回调中停止动画只标记记录失效，tick 结束后统一回收，避免
重入压缩动画数组。公共 widget/layout API 和所有 canvas 后端保持不变。

## 编辑器异步 clipboard 生命周期

`my_edit` 和 `my_text_area` 的 paste 在所属 UI loop 上重试 PAL 返回的
`MY_RET_PENDING`。paste timer 回调进入编辑事务前先取得 widget 临时引用，事务结束后再
释放；因此 `changed` listener 即使在 paste 过程中移除并释放当前控件，回调剩余路径也不会
访问悬空对象。timer 创建、重试和销毁仍只发生在所属 UI loop，失焦、子树移除和控件销毁
会取消 timer。

该保护位于异步回调冷路径，不给同步输入或绘制热路径增加锁、分配或全局扫描。PAL port
只需遵守 `clipboard_get_text_alloc()` 的 `MY_RET_PENDING` 契约；dummy PAL 提供可控的
pending-read 测试注入，用于覆盖真实异步 clipboard 的生命周期行为。

共享撤销管理器也采用显式关闭而非悬空销毁：应用调用 `my_undo_manager_destroy()` 后立即
禁止新的记录、undo/redo 和 batch 操作并清空历史；已注册的 edit/text-area 仍可安全完成
析构并注销，最后一个注册控件退出后才回收 manager 存储。管理器本身仍要求调用方在所有
使用者完成后不再访问其句柄；该延迟回收只解决控件持有的 manager 借用指针，不提供任意
线程并发调用保护。

## 跨线程 UI command 与生命周期 scope（2026-09-05）

需要从工作线程触发 UI 操作时，使用 `my_ui_command_t`，不要直接调用 widget、window、
window manager、timer 或 RHI API。command 通过既有 PAL `post_event` 进入目标 loop，
`execute` 只在 loop 线程执行；`created -> queued -> running -> done/cancelled` 原子状态机
拒绝重复提交，取消和 loop 销毁丢弃都不会重复执行或释放 context。提交失败会释放队列引用并
恢复可重试状态，调用方仍负责释放自己的 command 引用。

将 command 绑定到 window 或 manager 时，先取得
`my_window_command_scope_ref()` 或 `my_window_manager_command_scope_ref()`，再调用
`my_ui_command_submit_scoped()`。window/manager 关闭会取消尚未运行的 command；window
重新打开时会 reopen 自身 scope；同一 scope 可管理多个 sibling command。调用方必须在所有
producer 停止且提交完成前保持 PAL loop 存活，并在提交完成后释放 scope 引用。

scope 只管理 command 的取消和 scope 本身的引用，不会复制或自动保活 context 中借用的
widget/window/manager 指针。需要把 UI 对象放进异步 context 时，应使用对象明确提供的外部
引用或专用 lease，并在 loop 线程执行前检查业务状态；无法建立有效 owner/lease 时应拒绝
提交，而不是保存裸指针。`MY_EVENT_USER.data` 同样仍是调用方借用指针。

该 sidecar 不扩展冻结的 PAL main-loop vtable，也不假设特定 OS 或渲染后端；Break、dummy、
GLES2、Vulkan 和 soft 路径共享同一投递语义。当前已验证普通、ASan 和 Clang TSAN 的
Break/dummy command 测试各 **23/23**，window-manager 当前 **184/184**。

## CSS `@layer`（2026-09-05）

CSS parser 现在支持有界 `@layer name { ... }`、`@layer a, b;` 层序声明和
嵌套层。层名称、层数量与 at-rule 深度均有固定预算；重复层序项、空名称、
超长名称和非法结构在解析期拒绝。层序声明可以出现在层块之后，解析完成时
会统一刷新已经收集的规则 rank。

层规则在进入 theme bridge 前按最终 layer rank 稳定展开，未分层规则最后应用；
theme 查询仍只执行既有 selector cascade，不增加 layer 分支、锁或分配。分层
规则的 specificity 使用有界负偏移，避免破坏既有 theme 中未分层的 specificity
和源码覆盖行为。当前实现覆盖 CSS layer、有界 `@import` 以及受限 `@scope` 的
cascade 语义；scope root 支持 type/class/id/universal/implicit root，`to` 边界支持
有界 type/class/id/universal compound selector 及最多 4 项的 selector list。作用域规则
通过固定祖先路径和边界哨兵匹配，可与 `@media`、`@supports` 和 `@layer` 有界组合；带
组合器的复杂 selector、超过 4 项的列表和完整 CSS Scoping 规范语义仍未实现。

## 跨字体组合簇断行（2026-09-05）

paragraph wrapping consumes the same shaping cluster boundaries used by the font chain. A
combining mark remains attached to its base even when the selected face is different from
the primary face; narrow-width wrapping therefore cannot split the cluster. The contract is
backend-neutral and applies to soft, GLES2, Vulkan, and Break RHI consumers through the shared
paragraph model. This does not provide full cross-face GSUB/GPOS context negotiation.

The regression uses `a + U+0305 + b` with Cantarell and Noto Sans fallback faces. Default
paragraph/font/window-manager gates pass at **119/119**, **66/66**, and **138/138**; the
full default CTest suite passes **99/99**. ASan and STB-only font/text gates also pass.

## Profile-aware SA dictionaries (2026-09-05)

The line-break layer also exposes `my_line_break_apply_dictionary_profile()`.
Its additive options type keeps the legacy dictionary callback ABI unchanged
while passing the validated, versioned locale profile to each contiguous SA
run. The paragraph layer provides
`my_text_paragraph_process_n_break_profile_callback_ex()` so the same contract
is used by actual wrapping, not only by standalone line-break calls.

The callback receives borrowed pointers only for the duration of the call. Run
boundaries are copied to a fixed-size stack scratch buffer and committed only
after a successful callback; invalid Unicode scalars, unknown profile versions,
missing locales, zero budgets, and oversized runs are rejected before callback
execution. The path performs no heap allocation, lock, or renderer/backend
call. This is an integration contract, not a built-in Thai or other language
dictionary; production dictionary data and locale-specific quality goldens
remain deployment responsibilities.

## Built-in Thai SA dictionary (2026-09-05)

For deployments that need a deterministic baseline without shipping a separate
dictionary provider, `my_line_break_apply_builtin_dictionary()` provides a
small, version-1 `th-Thai` corpus and
`my_line_break_builtin_dictionary_callback()` adapts it to paragraph wrapping.
The corpus is compiled into static read-only tables; lookup uses bounded stack
state only and performs no I/O, heap allocation, lock acquisition, or renderer
call. The complete SA run must be segmentable by known entries before any
boundary is committed, and unknown or partially matched runs remain
unbreakable. This conservative behavior is intentional: it prevents a partial
dictionary from introducing unsafe word breaks.

The built-in corpus is a portable fallback, not a complete Thai dictionary and
does not claim locale-specific UAX #14 tailoring. Production applications
should provide a versioned dictionary callback and golden corpus for their
supported languages; unsupported built-in profiles return `MY_RET_NOT_SUPPORTED`.

## Scroll-bar listener lifetime (2026-09-05)

`my_scroll_view`, `my_list_view`, and `my_text_area` treat linked scroll bars
as weak external siblings, but retain the listener ID created for each link.
Rebinding the same bar is idempotent; switching bars or passing `NULL` removes
the old listener, and widget destruction removes it as well. This prevents
callback accumulation and stops later `changed` events from calling a
destroyed scroll container. Listener installation is transactional: if the
new subscription cannot be created, the previous link remains active. The
bar remains caller-owned and must outlive an active link.

## GLX damage-present runtime 门禁（2026-09-05）

`test_rhi_x11_runtime` 在 X11 环境中真实创建 OpenGL/GLX RHI，连续开始有界 damage frame，
读取后端合并后的有效区域，并完成 `frame_end -> present -> destroy` 生命周期。能力断言要求
retained-present 同时具备 damage-present 与 buffer-age；没有可连接显示服务或 GLX 驱动时按
CTest 标准 skip。当前 X11/Mesa runtime 通过；该门禁不伪造未提供扩展的能力，也不替代支持
buffer-age 的真实 GPU 多缓冲轮转验证。

## Unicode 17 扩展图形范围生成（2026-09-04）

`my_line_break.c` 使用 `my_extended_pictographic_data.h` 中的静态有序范围表区分
`ID_ExtPictUnassigned` 与 `XX_ExtPictUnassigned`。该表由
`tools/generate_myui_extended_pictographic_data.sh` 根据 Unicode 17
`emoji-data.txt`、`DerivedGeneralCategory.txt` 和 `LineBreak.txt` 的属性交集生成，
构建时不读取 UCD 文件。查询为无分配、无锁的有序二分查找；所有 PAL/RHI/渲染后端共享
同一个断行实现。当前覆盖的关键范围包括 `1F02C..1F02F`、`1F8D9..1F8FF`、
`1FC00..1FFFD`，以及官方语料要求的 `U+EFFFD` 特例。

## 断行边界优先级校准（2026-09-04）

断行热路径补齐了几项 Unicode 17 高置信优先级：`QU → CB` 不拆分，Hangul 与 `SA`
不错误合并，`HY/HH → SA` 保持连续，数字分隔符到 Hangul 可断，
`ID_ExtPictUnassigned × EM` 保持连续，非空格到普通 `OP` 不断，
`AL/ID/SA → XX_ExtPictUnassigned` 不断，普通字符到 `RI` 可断；U+2329 的 East Asian
开括号例外保持不变。相关规则均为固定类别/码点判断，不增加分配、锁或渲染后端依赖。
普通文本布局 TDD 为 **115/115**；Unicode 17 官方 `LineBreakTest.txt` 已通过 60,487/60,487
个边界。核心路径覆盖默认规则，locale tailoring 与调用方 SA dictionary 通过显式上层配置提供。

## 断行规则补充（2026-09-04）

断行器遵循 Unicode 17 官方语料中的 `SP × IS` 例外，例如空格与逗号之间不产生候选
断点，同时允许 `SP ÷ NS`（如 U+3005/U+203C）。`SP` 后的 `QU` 仅在目标为 opening
quote（如 U+00AB）或中性 `QU`（如 ASCII `"`）时允许断点，closing quote（如 U+00BB）仍与空格保持连续。该优先级
位于通用 LB18 空格规则之前；ZWJ 和 emoji modifier 在 `SP` 后则遵循 LB18 允许断行。
查询仍为常数时间、无分配、无锁；streaming state 额外保存闭合标点后的空格上下文，
覆盖 `CL/CP/EX/IS` 到 `NS/CJ` 的 LB16 不起行约束（`SY` 保持可断），并由四个文本布局
构建变体和核心 MyUI CTest 覆盖。`CB` 对象后的 breaking space、combining mark 与
joiner extension 保持连续，`CB` 与普通字符仍保留对象边界断点。
emoji modifier 仅在 `EB × EM` 时保持连续，脱离 `EB` 后遵循普通断行规则。
`B2` 后的 `VF/VI` 保留 break-both 的前置断点语义。
`CB` 后的 `VF/VI` 保留对象边界断点，普通 combining mark 则继续附着。
硬换行遵循 LB4–LB6：断点位于硬换行之后，CRLF 不拆分；该逻辑由 paragraph 的物理行
切分与底层断行状态共同保障。

## UAX#14 断行类别与上下文

断行数据由 `tools/generate_myui_line_break_data.sh` 从 Unicode 17.0.0
`LineBreak.txt` 生成。除默认的 `AL/SA/SP/HY/ID/NS/OP` 外，公共类别还保留
`QU`、`HH`、`HL`、`SY`、`NU`、`PR`、`PO`、`IS`、`BA`、`IN`、`CB`、`EB`、`EM`、
`CJ` 和 `ZW`，避免把不同规则错误折叠成同一个标点类别。当前上下文契约包括：
空格不允许在其前方断行、空格后的 CM/GL/VF 按 LB9/LB18 重新解析、引号双侧不拆分、完整 UCD `HL` Hebrew 字母与 maqaf 绑定、数字/前后缀/
分隔符序列保持连续、`BA/IN/CJ` 前置禁止断点、`BB` 仅前方可断且后方不拆、`B2` 前后可断但 `B2 SP* B2` 不断、`HL × HY/HH × HL` Hebrew 连字符
绑定、`EB × EM` emoji 组合、`CB`
独立对象边界、开括号后的连续空格与其后内容保持同一候选行，以及 `ZWSP` 只在其后
提供断点。查询为常数级类别查找，无分配和锁，
streaming state 额外保存 RI、starter、Indic 组合上下文、跨组合标记的 virama 状态和有限数字上下文。`AP/AK/AS/VF/VI`
类别按 Unicode 17 数据保留；组合边界使用固定状态和 starter 回溯，不在断行热路径分配。
`LB28.11`--`LB28.14` 按方向而非“所有 Indic 都是字母”处理：`AP` 仅与
`AK/AS/DottedCircle` 粘连，`AK/AS/DottedCircle` 仅在 virama 相关序列中保留边界；
例如 `AK x AP`、`AK x AK` 和 `AS x AK` 可断，而
`AK/AS/DottedCircle x VI/VF` 及 `AK/AS/DottedCircle VI x AK/DottedCircle`
不可断。流式状态保留前一个 starter 以覆盖后一个上下文规则；每次 feed 仍为 O(1)、无锁、
无分配。

paragraph wrap 通过公共 `my_line_break_is_breaking_space()` 消费同一 breaking-space 定义，
断点回退以及行首/行尾裁剪同时覆盖 ASCII 和 Unicode breaking spaces；因此 U+2003、U+205F、
U+3000 等不会因 paragraph 层仍只检查 ASCII 而残留在错误的物理行。该 helper 为 O(1)、无
分配、无锁，text area 继续通过 paragraph 间接复用。

text area 的 JUSTIFY 计数、光标/IME 边界、选区矩形和软件绘制回退也复用该 helper；Unicode
breaking space 会像 ASCII 空格一样参与剩余宽度分摊。UTF-8 路径按 codepoint 单次扫描，
不引入逐帧分配或锁，visual layout 与无 shaping 回退保持相同语义。

这些规则由 `test_myui_text_layout` 的 TDD 用例覆盖（当前 **119/119**）；当前实现是可移植的实用 UAX#14
子集，不宣称完成全部 East Asian tailoring、locale tailoring、SA 词典实现、完整规则
交互或全部 UAX#14 golden corpus。

## Text area 事务边界

`my_text_area` 的编辑入口先执行范围、UTF-8、`max_len` 和容量预检，再写入 undo，最后
执行原地替换；因此 soft、GLES2、Vulkan 和 Break RHI 看到的文档状态始终与历史状态
一致。选区替换记录一个不可批量的 replace patch，undo/redo 不会丢失被替换文本。任何
OOM、历史分配失败或长度约束失败都保持文本、光标、选区及历史不变。

程序化 `set_text()` 先准备语法候选、扩容和文本复制，成功后才清理当前 widget 的 undo
历史；失败可以安全重试。该状态机不依赖具体平台或渲染后端，容量已存在时不分配，扩容
采用倍增策略。键盘 ASCII 输入使用显式 NUL 终止缓冲，坐标转换允许省略列输出，避免
跨编译器和 sanitizer 配置下的边界差异。TDD 门禁为普通/ASan **110/110**，无 BiDi
**99/99**，文本布局 **75/75**；YAML-off 与 Vulkan 核心构建通过。

undo/redo 使用 `peek -> apply -> commit` 提交点：公共栈先只读 patch，widget 成功应用后
才推进游标；shared manager 同样在 owner 存在且应用成功后提交，避免后端或分配失败造成
文档与历史游标分叉。

## 增量语法缓存

编辑器 lexer cache 为每行保留 token 和跨行状态快照，并分离源码修改与上游状态传播。
`my_syntax_cache_replace_line()` 只复制新行文本并标记源码 dirty，实际词法分析由
`my_syntax_cache_ensure()` 按行预算执行；这样保持原有 lazy ready 契约。若新旧跨行输入/
输出状态一致，未修改后缀直接恢复旧快照，不发生分配或逐行重扫；块注释等状态变化只向后
传播到状态收敛点。独立修改的后续行具有自己的 dirty 标记，不会被收敛短路覆盖。

正常稳定后缀的收敛判断为常数级，跨行状态改变只处理实际传播范围，资源上限、OOM 事务
语义和 C/YAML lexer 行为保持不变。

## 配置裁剪与最终门禁

`MYUI_UI_YAML=ON` 构建完整 YAML loader；关闭时 `myui_core` 不包含 YAML loader 实现，
能力 registry 返回零 YAML 特性，load/register 等入口安全返回 stub 结果。CMake 在关闭
YAML 时注册 `test_myui_loader_disabled`，而不是执行依赖 YAML 的完整 loader 测试，确保
size-trimmed 构建的测试结果与实际能力一致。

当前最终门禁：默认核心定向测试为 syntax **7/7**、metrics **6/6**、window-manager
**124/124**、vgcanvas backend **34/34**；Vulkan 对应 window/backend 为 **124/124**、
**35/35**；ASan/UBSan syntax/window 为 **7/7、124/124**；YAML-off CTest **83/83**
及禁用 loader **2/2**；Redis 源码 hiredis 配置 CTest **84/84**。这些是 headless/build
矩阵证据，不替代真实 Wayland/X11/Win32/Cocoa/Vulkan runtime smoke。

## Wrap dirty suffix 批量处理

wrap 模式且没有折叠范围时，编辑造成的 dirty physical-row suffix 只创建一次
`my_text_paragraph_t`，随后按共享硬换行范围映射回 visual lines；未受影响的前缀继续复用。
折叠模式保留逐物理行路径，避免把折叠状态错误带入 paragraph。paragraph、visual-line
数组或物理映射失败都会恢复旧缓存，visual-line 候选对象在 darray 扩容失败时立即释放。
该路径按 suffix 字节和输出 visual lines 线性处理，不在每帧引入锁或无界分配；单行编辑在
物理行数不变且无折叠时进一步只重排 changed row，并复用后续 visual-line 对象。尾部空行和
连续空行以零长度 visual line 保留，避免物理行数推断遗漏空尾行；末行编辑和跨行删除则由
TDD 锁定为保守安全路径。当前对插入或删除硬换行的编辑，也会在 suffix 的物理行起点和
byte 边界严格匹配时复用 suffix 对象；复用只调整 `phys`，不改动 suffix 的物理行内
`start_byte/len_bytes/start_cp/len_cp`，因此多字节文本和跨行合并不会产生局部坐标漂移。
当 `vlines_dirty` 在编辑前已经存在、存在折叠范围、边界无法匹配或物理行变化不安全时，
路径自动退回完整 dirty suffix 重建。候选 darray、paragraph 和新 visual lines 均在成功
前保持私有；任何 OOM 恢复旧 `vlines` 及其对象所有权，成功提交后才释放受影响中间段，
避免重复释放或悬空指针。该优化的编辑阶段为 O(delta + changed visual lines)，稳定 suffix
为 O(1) 对象迁移；普通 window-manager 回归为 **212/212**，并覆盖删除换行、多字节
替换、预先 dirty 缓存和复用路径 OOM。

## 统一硬换行

paragraph 和 text area 共用 `my_line_break_hard_break_len()`，支持 LF、VT、FF、CR、CRLF、NEL、
U+2028 和 U+2029。CRLF 只产生一个物理行边界，分隔符不会进入行文本、几何或逻辑
codepoint 计数；因此 soft、GLES2、Vulkan 和 Break RHI 消费的 visual-line 范围一致。
helper 只做有界字节检查，热路径无分配、无锁。普通/ASan text-layout 为 **78/78**，
window-manager 为 **111/111**。

流式断行状态还将 Unicode breaking spaces 视为“开括号后的连续空格”上下文，覆盖
U+2000..U+2006、U+2008..U+200A、U+205F 和 U+3000，并保留 ASCII 空格的既有行为。
这只用于 LB18 风格的开括号上下文，不会把 NBSP、WORD JOINER 或 ZWSP 误分类；判断
在每个 codepoint 上为 O(1)，不增加热路径分配或锁。Unicode 空格回归由
`test_myui_text_layout` 覆盖。

## 跨后端 stroke 线帽与连接

`my_vgcanvas` 的 stroke 样式在所有 bundled backend 中遵循同一契约：线帽支持
`MY_LINE_CAP_BUTT`、`MY_LINE_CAP_ROUND`、`MY_LINE_CAP_SQUARE`，连接支持
`MY_LINE_JOIN_MITER`、`MY_LINE_JOIN_ROUND`、`MY_LINE_JOIN_BEVEL`。GLES2、Vulkan 和
Break RHI 复用 `my_vggeometry_stroke()` 生成相同三角形；soft backend 的无 AA 与 AA union
路径也采用相同端点/连接规则。miter 长度限制为半线宽的 4 倍，超过限制退化为 bevel，
从而保证输入极端尖角时几何规模和坐标有界。公共 setter 先校验枚举，失败不改变状态。
闭合 contour 的首尾连接会被处理，开放 contour 不自动闭合，square 线帽只延长开放端点。

该设计保持 frozen vtable 布局不变，并将风格差异收敛在共享几何层；正常路径不读取平台或
RHI 特定类型，也不增加每帧分配。soft AA union 继续使用既有按 clip 宽度的工作缓冲，
GPU 路径继续按一次几何上传提交。

共享几何层也有独立的输入安全边界：直接使用 `my_vggeometry` 时，path 坐标、Bezier
控制点、变换、线宽、线帽/连接枚举和 clip 尺寸均经过校验；失败不会追加 point、创建
非法 contour 或改变既有 transform。GLES2、Vulkan、Break RHI 会传播 fill/stroke 的
几何错误，不会把无效顶点继续提交。无返回值的 primitive 对非法浮点输入安全忽略。

几何输出带有首错状态：扩容失败或输出溢出不会静默丢顶点，后续 `fill/stroke` 返回
`MY_RET_OOM`/对应错误，GLES2、Vulkan、Break RHI 和图像背景合成路径均在提交前检查；
Bezier 中途失败会回滚新增点，clip 的扫描边界采用 64 位迭代。每个新的顶点输出事务由
`begin_verts()` 清除旧错误，便于安全重试且不影响已完成的旧绘制提交。

## 目标

- 复用 `myui` 的 widget、窗口、MVVM、Bidi/断行、字体和图像加载能力。
- 不绑定特定 OS 窗口或 GL/Vulkan API：所有后端统一通过 `Platform` 与 `RHI`。
- 在 GL 和 Vulkan 上使用同一套 CPU 三角化和双缓冲动态 VBO 路径。
- 用可测试的桥接层隔离平台输入、IME 与渲染后端。

## RHI 线程边界

RHI 的隐式命令目标 `g_current_device`、GL 帧活动标记和 GL 状态缓存均为线程局部；每个
设备还维护一个无锁原子帧 owner。
工作线程不会继承渲染线程的当前设备，也不会把另一设备的 pipeline、纹理、FBO 或
viewport 缓存当作有效状态；同一线程切换设备时缓存会一次性失效。该设计保持命令入口
O(1)、无锁、无分配。每个设备从 `rhi_frame_begin()` 成功到 `rhi_present()` 返回期间只能有
一个活动帧，且每个线程同时只能持有一个设备的活动帧；非 owner 线程的
`rhi_frame_end()`/`rhi_present()` 会安全忽略。这不等价于完整的
并行 command context：同一设备的原生 GL/EGL/GLX 上下文仍必须由宿主固定在线程上，跨线程
提交必须被调用方禁止。需要并行录制或共享队列时，
应使用后续显式 command context、queue ownership 和 fence 协议，而不能把 `RHICmdBuffer *`
跨线程传递。
设备销毁会先尝试占据同一 owner 状态；活动帧或并发销毁存在时安全拒绝，不会释放仍被帧使用的
后端资源。调用方应在 `rhi_present()` 完成后重试销毁。
同一空闲门禁也保护 resize 与 vsync 切换，避免在 GL/Vulkan 活动帧中重建或修改 present
目标；调用方应把这些控制请求合并到下一帧开始前执行。

## 单行编辑器安全与字体一致性

`my_edit` 的文本替换、选区删除和密码掩码使用候选缓冲区提交：文本与掩码都准备成功后
才交换状态。分配失败保持原文、光标、选区和掩码，且不发送 `changed`、不写入 undo；
`my_edit_set_text()`/`my_edit_set_password()` 将 OOM 传回调用方。该路径不依赖平台或渲染
后端，也不改动 frozen vtable，正常编辑仅保留必要的一次文本复制和（密码模式）一次掩码
生成。

测量、命中测试、IME anchor 和绘制均使用同一个有效字体：edit 自身字体优先，未设置时
继承窗口默认字体；paint 入口显式设置 canvas 字体，避免 canvas 之前残留的字体状态造成
光标与实际 glyph 错位。fallback cell、极大 glyph advance、IME 预编辑和 selection/cursor
坐标使用 64 位中间值并饱和回写，soft、GLES2、Vulkan、Break RHI 共享相同边界语义。

公共 undo 栈的 replace patch 保存 deleted/inserted 两组字节，因此选区替换不会丢失撤销
所需的原文。undo entry、payload 和 redo/容量裁剪采用提交后修改顺序；任一分配或容量
扩展失败都保留旧历史和 redo 分支。连续退格合并的缓冲区包含终止字节，并对所有长度
加法执行 `size_t` 边界检查。

## 帧级性能指标

`myr/my_ui_metrics` 提供可选的固定容量（8 帧）ring buffer，用于在不改变
渲染后端 ABI 的前提下观测 MyUI 帧。指标由 owner loop 使用，当前不提供跨线程
同步；关闭时所有 record 入口只做快速 enabled/in-frame 判断，不写 ring、不分配、
不上锁。计数采用 `uint64_t` 饱和加法，帧可嵌套但只有最外层成功结束才发布一个样本。
后端提交失败通过 abort 丢弃整个当前样本，避免把失败绘制误报为有效帧。

`draw_calls` 表示成功的 MyUI logical drawing operation（primitive、text 或 image），
不等同于 GL/Vulkan 实际底层 draw call；`damage_rects` 和
`damage_area_pixels` 是逻辑 dirty rect 数量及面积，不是 compositor 最终提交面积；
`atlas_misses` 是 glyph cache miss，`fallbacks` 是字体链选择 fallback 的次数，可能
来自 measure、shape 或 glyph 查询，不只是真实绘制。

BreakUI 推荐调用顺序为 `break_ui_pump()`、`break_ui_frame_begin()`、
`break_ui_render()`。成功获取 RHI 命令后，BreakUI 建立一个外层 metrics frame，窗口
layout/damage 与 canvas 的嵌套 frame 因而属于同一个样本；命令获取失败、尺寸/资源失败、
窗口快照失败、surface 绘制失败和其它提前退出均 abort。旧的直接 `break_ui_render()`
调用仍可工作，但没有宿主 frame 时只能统计 canvas 自身的局部 frame。

该实现已经以 headless fake canvas、soft backend、窗口管理器及 sanitizer 构建验证；
这些证据不等同于真实 Wayland/X11/Win32/Cocoa compositor、Vulkan WSI 或 GPU driver
runtime profiling 通过。

## 增量合成安全边界

BreakUI 的 surface 重绘和最终 composite 分为两个独立阶段。surface 已经是持久的
offscreen target，窗口 dirty 集合可先在逻辑坐标中收集，再通过
`break_ui_damage_to_drawable_scissor()` 做保守的 drawable 映射；映射使用向外取整、裁剪和
64 位乘法，避免高 DPI 缩放下漏画边缘。

最终 composite 由 `break_ui_surface_composite_decide()` 返回 `SKIP`、`PARTIAL` 或 `FULL`：
只有 offscreen surface 有效、RHI 明确声明 scissor 可用、并且平台明确保证 present target
保留未更新像素时，才允许局部 scissor。dirty 碎片超过 8 个，或合并后的 scissor 超过
drawable 面积 60%，自动回退全屏；空 damage 仅在 present target 保留时跳过 composite。
所有无效尺寸、能力缺失、surface 重建、resize、AA 切换和绘制失败均走全屏/不绘制的安全
路径，不凭 dirty rect 猜测 swapchain 内容。

RHI 现在提供 `rhi_frame_begin_damage()`，在帧开始前接收有界的 drawable damage 区域；帧开始
后可用 `rhi_frame_get_damage()` 读取后端根据 buffer age 合并后的有效重绘区域。它会拒绝
空尺寸、负坐标、越界区域和超过 16 个矩形的输入，拒绝后回到普通帧路径。Wayland EGL
只有同时检测到 `EGL_EXT_buffer_age`、`eglSwapBuffersWithDamageKHR/EXT` 和成功协商的
`EGL_BUFFER_PRESERVED` 时才启用局部路径；GLX 只有同时检测到 `GLX_EXT_buffer_age`、
`GLX_EXT_swap_buffers_with_damage`、对应运行时函数和有效固定容量 history 时才启用。两条路径
都会按有效 buffer age 合并历史区域，并把统一的 top-left 区域转换为 API 所需的 bottom-left
坐标；尺寸在进入 API 整数类型前保持受限。GLX 的损坏交换 API 无成功返回值，调用返回后才
提交 history，resize 仍重建 history；缺少任一前提或未知 age 时安全全屏。Win32 WGL、Vulkan
和 macOS 当前保持能力关闭。

present 状态采用保守更新：EGL history 仅在 swap 成功后记录实际提交区域；GLX 的损坏交换
接口没有成功返回值，仅在调用返回后记录。resize、EGL swap 失败或 history 缺口都会强制
全屏并清除旧 history；因此可检测的局部优化失败不会污染下一帧的保留像素假设。

`RHIPresentRect` 在 RHI 和 BreakUI 中一律使用 drawable 的 top-left 原点。仅在调用
`eglSwapBuffersWithDamage*` 或 `glXSwapBuffersWithDamageEXT` 的最后一层，
`rhi_present_damage_to_bottom_left()` 才以固定容量、无堆分配方式转换为原生 bottom-left
坐标；该入口先复用有界区域校验，并支持同一数组原地转换。这样 history、scissor 和 UI
damage 不会混入两种坐标系。TDD 覆盖多矩形、原地转换、容量不足和越界输入；RHI 专项普通、
ASan/UBSan 与 Clang TSan 均为 40/40。

Dirty rectangle 的几何端点也不直接使用 32 位加法。`my_rect_contains()`、
`my_rect_intersect()`、`my_rect_union()` 和内部接触判断先在 64 位中间值上计算半开区间
边界，再将结果写回既有 `int32_t` 矩形；宽度超过 ABI 可表达范围时安全饱和。这样高 DPI
映射、极限负坐标和接近 `INT32_MAX` 的窗口不会因端点回绕而误命中、漏合并或错误地产生
空交集。该保护只增加固定整数运算，不引入 dirty 列表扫描之外的额外分配。

窗口管理器的模态居中使用共享 `my_rect_center_axis_i32()`，以 64 位中间值计算并在写回
`int32_t` 前饱和，避免大坐标或负坐标下的定位回绕。tooltip 的文本宽度和光标偏移同样在
加法前做 `size_t`/64 位边界检查；BreakUI dirty 快照数组在 `count * sizeof` 前拒绝回绕。
这些检查均位于低频布局/提示框路径，不改变绘制热路径的分配模型。

菜单弹窗和节点编辑器沿用同一边界策略：菜单文本宽度、项目高度、窗口边缘翻转及子菜单
锚点先在 64 位中间值上计算，节点自动尺寸对标题、socket 和嵌入子节点的端点累加后再
安全饱和为 `int32_t`。因此极端坐标不会在弹窗命中区域、节点布局或不同 canvas 后端之间
产生不一致；常规路径仍是线性内容测量，未增加每帧分配。

菜单 popup 的关闭和销毁必须在所属 UI loop 执行。关闭、窗口关闭、manager 销毁及 overlay
destroy chain 都会先取消 hover timer、摘除窗口/manager/overlay 弱引用和 owned callback
state，再调用 callback context destructor；如果 destructor 重入销毁菜单，模型释放会延迟到
最外层菜单操作结束，并同步摘除父菜单的 submenu item。该保护只覆盖同一 UI loop 的重入，
不把 `my_menu_t*` 变为跨线程句柄；跨线程调用必须通过宿主事件队列串行化。

节点视图的 socket 命中距离使用 64 位差值，节点端点、框选边界和拖拽位移使用共享矩形
端点/饱和偏移 helper；soft/LCD 的裁剪循环同样不依赖 32 位 `origin + extent`。Break RHI
后端在创建/resize 前验证 drawable 尺寸可表示为 `int32_t`，保证 soft、GLES2、Vulkan 和
Break RHI 对极限尺寸采用一致的拒绝契约。

BreakUI 的公开尺寸入口同样要求 logical/drawable 宽高非零且不超过 `INT32_MAX`；初始化、
render 和 present-damage 查询共享 `break_ui_dimensions_fit_myui()`，不会在桥接层先截断
再调用窗口或 canvas。该校验位于 API 边界，正常帧不增加扫描、分配或锁。

## Text area 数值边界

`my_text_area` 将字体 advance、visual line 高度和滚动位置视为可能来自不可信 provider 的
输入。glyph boundary cache 的 advance 累加使用饱和整数，`size_t` codepoint 数量乘固定
fallback cell 宽度前先检查乘法；内容高度、可视行 y、游标和 IME 坐标使用 64 位中间值后
再写回现有 `int32_t` 坐标。滚动条 content/max 计算也遵循同一契约，避免超大文档或极端
字体把坐标回绕成负值。

绘制和 RTL layout 取 visual-line 文本时先校验物理行起点、byte offset 和长度不超过当前
文本缓冲区；失效缓存安全返回空行而不是访问越界。所有保护均为固定次数边界检查，未引入
逐帧分配、锁或新的 vtable 字段。该层的数值安全由 `test_myui_window_manager` 的超大
advance 与损坏 visual-line slice 回归及 ASan/UBSan 门禁覆盖。
公开的 `my_text_area_visual_line_at()` 对越界 index 返回 `NULL`，调用者不应依赖内部缓存
对无效索引的末行回退行为。

滚动容器的 `set_scroll_bar()` 是低频绑定入口，不接受任意 `my_widget_t`：传入值必须
通过 `my_scroll_bar_is_instance()`，否则返回 `MY_RET_INVALID_PARAMS` 且保留原绑定。
校验发生在 listener 注册和 scrollbar 状态同步之前，因此不会把不兼容 widget 布局
解释为 `my_scroll_bar_t`。绑定对象由容器持有一个非循环 link reference，在解绑或容器
销毁时释放；调用方可以在绑定后释放自己的引用，且不会产生容器与 scrollbar 之间的
所有权环。该契约把对象生命周期和 listener 生命周期统一起来，同时把错误输入隔离在
API 边界。
`my_scroll_bar_set_value()`、`my_scroll_bar_set_page_size()` 以及对应 getter 也拒绝
非 scrollbar 实例；非法 getter 返回 `0.0f`，不读取不兼容对象内存。

GL X11 只有在 `GLX_EXT_buffer_age`、`GLX_EXT_swap_buffers_with_damage`、运行时函数入口和
固定容量 history 同时可用时才声明像素保留能力；其他 X11 驱动与 Win32 WGL、Vulkan、macOS
继续使用全屏 composite。这是有意的安全默认值，不是未检查的性能开关。Vulkan 仍不启用
`VK_KHR_incremental_present`：该扩展是 compositor 优化提示，并不保证 present 后 swapchain
image 内容可被 `LOAD`，所以不能满足 retained-buffer 的硬前提。

## Vulkan vgcanvas 质量事务

独立 Vulkan vgcanvas 将 portable AA level 映射为明确的 sample count：level 0/1/2
分别对应 1x/2x/4x。能力来自 physical-device 与实际颜色格式的交集，不支持的 level
在调用 Vulkan 前返回 `MY_RET_NOT_SUPPORTED`。当前 sample count、target 尺寸、render pass、
pipeline 和 descriptor 资源必须属于同一个候选组，候选全部创建并完成初始化后才交换到
active；失败只销毁候选，保留旧 target、pipeline、尺寸和 capability。

AA 切换与 resize 使用同一条候选重建路径。resize 请求在下一帧边界合并，多个请求只保留
最后尺寸；重建期间不修改 active 尺寸或 clip。窗口 out-of-date 也复用该路径，避免先销毁
旧 swapchain 再发现新资源创建失败。MSAA 创建失败不再静默降级到 1x；初始设备能力查询
决定默认质量，运行时显式请求失败则保持原质量。

## 冷却按钮

按钮冷却是 widget 层能力，不依赖 Break RHI、OpenGL、Vulkan 或软件 canvas 的私有类型：

```c
my_button_set_cooldown(button, 1500);
if (!my_button_is_cooling_down(button)) {
    /* 可选：显示或启用业务操作 */
}
```

成功 click 后按钮保存 PAL 提供的单调 deadline。冷却期间 pointer、Return 和 Space
激活均被拒绝且不产生 `click`；键盘激活采用成对的 `key_down`/`key_up`，只对首次
按下的同一按键发出一次 click，重复按下或错键释放不会重复触发。查询接口实时检测
deadline，因此 timer 丢失、主循环暂时停顿或窗口未
挂载都不会绕过限制。按钮只在冷却期间启用一个 16ms timer（PAL 明确报告
`reduced-motion` 时改为一个冷却周期级完成 timer），timer tick 触发局部
invalidate，绘制通过公共 `my_vgcanvas_fill_rect()` 输出半透明进度遮罩。冷却完成后
timer 自动停止，按钮销毁流程、`my_button_set_cooldown(button, 0)` 也会移除它。release
timer 创建失败时立即清除 pressed 状态；timer 只负责视觉刷新，不影响 click 业务判定
和 cooldown deadline。启用 reduced-motion 时仍显示静态遮罩并实时拒绝重入；unknown 不
会被当作 reduced-motion，避免平台查询失败改变默认行为；偏好在每个冷却周期开始时采样，
周期内不重复查询 provider。
按钮绘制帧只采样一次 PAL 时钟，并复用同一快照计算 active、remaining 和遮罩进度；不会因
连续查询跨过 deadline 而绘制与交互状态不一致。
每次 remaining/progress 查询只采样一次 PAL 时钟，再完成截止时间比较和换算，避免时钟
在连续读取间跨过 deadline 造成下溢或错误的大剩余值。若 PAL 时钟回拨，最短按压释放
保护按 elapsed=0 处理，不会提前释放；若 deadline 加法饱和到 `UINT64_MAX`，按钮仍按
已记录的起始时间和有限 duration 计算剩余时间，但不创建永远无法到期的周期 timer。

通用属性路由同样不信任 YAML 或调用方可写的 `widget_type` 字符串。内置 class 在
`my_widget_set_prop()`/`my_widget_get_prop()` 的 descriptor callback 前执行固定 vtable
身份校验；伪造类型、错误控件和空对象在访问控件私有字段前失败。checker 是 O(1) 的函数
指针比较，不分配、不加锁、不扫描子树；自定义 class 的 checker 可为 `NULL` 以保持旧的
不透明兼容语义。

widget 专用 API 采用相同的真实 vtable 身份边界：普通 widget、伪造类型字符串或空
对象在访问派生字段前被拒绝，查询接口返回中性值，写入接口返回
`MY_RET_INVALID_PARAMS`。节点视图连接还校验节点直接属于当前 view、socket 方向和
slot 范围，避免跨 view 或不可绘制 link 污染模型。该检查是 O(1) 类型比较，不分配、
不加锁，也不进入绘制热路径；它不等同于通用 weak 引用的自动失效。

节点视图还注册了可选的父节点级 `child_removed_hook`。该回调在直接 child 脱离前只做
模型弱引用清理，不在树结构尚未完成变更时向应用发事件；标准 `remove_node()` 在移除
完成后再发送 `changed`，避免监听器重入销毁 view 后继续执行树操作。view 销毁前解除
node 的反向 `view` 指针，外部保留 node 引用时也不会回访已销毁的 view；这一协议仅覆盖
node-view 已知关系，其他借用指针仍须由对应模块定义生命周期。

组合控件的低频替换入口使用候选提交而非“先清旧状态”：`scroll_view` 仅在新内容成功
挂载后才释放旧内容，`list_view` 更换 adapter 时销毁旧 adapter 创建的活跃/池化 row 并
清除高度索引；动态高度索引使用显式 64 位元素，回收池 OOM 会释放临时引用。窗口栈拒绝
同一窗口重复打开；dialog 若无法打开会回滚临时 modal、scrim、
回调和 manager 状态。这些检查和回收都位于绑定、创建或替换路径，不增加帧内分配或
渲染后端分支。

MVVM widget target 采用 target-lifetime 的 widget 引用，避免绑定期间调用方释放 creator
引用或把控件从树中移除后，VM listener 继续访问悬空对象。`CloseWindow=true` 的额外
click listener 由 `my_mvvm_context_t` 保存 listener ID，并在 context 销毁和绑定失败回滚
路径注销；items binding 判断 list-view 使用真实 vtable 身份而不是可写 `widget_type`。
这些引用与注销操作只发生在绑定、替换和销毁冷路径，不增加绘制热路径开销。

item template 默认注册接口继续使用调用方借用的 `builder_ctx`；如果上下文需要由
MVVM registry 管理，使用 `my_mvvm_register_template_owned()`，并提供一次性的析构回调。
替换同名模板或显式调用 `my_mvvm_unregister_template()` 时，旧 owned context 恰好释放
一次；注册失败不转移所有权。该 API 解决模板注册的长期 context 生命周期，但不改变
builder 回调必须在 UI owner loop 执行的约束。

默认 navigator 采用条件清除协议：`my_navigator_wm_destroy()` 只在全局默认项仍指向
自身时清除注册，因此替换后的新 navigator 不会被旧实例析构误清理；没有默认实例时
`my_navigator_request()` 返回 `MY_RET_NOT_FOUND`。注册表仍是进程级非拥有弱引用，跨线程
注册与请求必须由宿主串行化，当前实现不额外引入全局锁。

需要从非 UI 线程或异步任务发起导航时，使用
`my_navigator_wm_request_async()`，不要把 `my_navigator_request()` 当作跨线程 API。

MVVM 跨线程更新使用 `my_mvvm_context_set_property_async()`：它先复制标量/字符串值，再在
绑定窗口的 UI loop 线程调用 VM setter，因此 setter 的通知和 data/items/condition binding
刷新不会发生在 worker 线程。`MY_VALUE_POINTER` 是借用指针，异步属性提交会拒绝它。若宿主
已经在线程安全模型层完成了存储修改，只需触发通知，可使用
`my_mvvm_context_notify_change_async()`；该接口不会替宿主解决模型存储的数据竞争。
context 或所属 window manager 销毁时，尚未执行的异步请求会被 scope 取消。
每个绑定 session 最多同时保留 64 个 pending 请求，超限返回 `MY_RET_PENDING`；字符串快照
最多 4 KiB。该配额在执行、提交失败或销毁丢弃时释放，防止 worker 侧请求堆积导致无界内存
增长。
worker 使用上述异步 API 前必须先调用 `my_mvvm_context_ref()`，完成生产任务后调用
`my_mvvm_context_unref()`；`my_mvvm_context_destroy()` 只释放 creator reference。最后一个
引用在 worker 线程释放时，context 的 widget、binding listener 和 command scope 清理会延迟
到绑定 UI loop 执行。绑定 loop 必须存活到所有 context 引用释放及排队清理完成。
异步入口在提交前复制固定大小的 `my_navigator_request_t`，并且只接受 navigator 所属的
PAL loop，通过 navigator 自有 command scope 投递；页面 factory 和 window manager 操作只在
该 loop 线程执行。page factory 可以重入销毁 navigator；此时默认注册立即失效，当前 request
停止后续 window-manager 操作，页面表和 command scope 延迟到最外层 request 返回后释放。
navigator 或其所属 manager 销毁时，scope 取消尚未运行的请求，队列丢弃仍会释放 owned
request。page factory 可使用 `my_navigator_wm_add_page_lease()` 绑定 invalidatable lease；
lease 失效后跳过尚未开始的 factory，已进入 factory 的调用允许自然完成。loop 必须保持
存活到所有 producer 停止和请求完成；未使用 lease 时 page factory 的 `ctx` 仍是调用方借用
数据，需要由应用自行保证其生命周期。同步 request 的 factory 重入销毁由
navigator 延迟到最外层 request 边界处理，但不提供跨线程注册、替换或请求同步。

动画不参与业务判定：帧率、timer 抖动、GL/Vulkan 提交延迟只影响遮罩刷新，不影响
deadline。所有后端都获得同一输入和视觉契约；不支持透明混合的后端仍执行公共绘制，
由该后端的颜色语义处理，不引入 shader 分支。

局部样式通过 `my_widget_style_set()` 修改成功后会立即提交 widget 级 dirty/invalidation，
覆盖 retained surface 的旧区域；样式写入失败时保持旧状态且不产生无效重绘。该失效路径
与渲染后端无关，正常成功写入只增加一次既有的局部失效调用。
首次创建局部样式前会校验 state 和 key 长度；非法请求不会创建空样式对象或消耗分配预算。
首次合法写入采用候选样式提交：值复制成功后才挂载 `local_style`，OOM/容量失败会释放
候选且不改变 widget 状态。

MVVM 绑定同样采用失败即回滚的创建契约。data binding 在注册 VM/target listener 后，必须
先完成一次 `vm -> view` 初始同步；目标 setter 返回错误时，绑定不会加入 context，并会
释放已注册 listener、validator 和绑定对象。condition binding 的首次求值也传播目标 setter
错误，因此 loader 或调用方不会得到“绑定成功但界面仍是旧值”的假成功结果。正常成功路径
仍只执行一次初始同步，后续通知保持同步 O(1) 分发，不引入队列、锁或额外帧分配。
上下文切换也采用同一事务：新 VM 的任一 data/items/condition 绑定重订阅或初始刷新失败时，
会解除新 VM 监听、恢复旧 VM 引用并重新建立旧监听；调用方收到错误，旧视图关系保持可用。

PAL timer 的首次 deadline 和周期重调度统一采用 `uint64_t` 饱和加法；当单调时钟接近
`UINT64_MAX` 时不会回绕到过去并提前触发。定时器仍由调用方提供的 PAL 时钟驱动，未改变
正常时钟下的周期语义。`interval_ms == 0` 会在创建前拒绝，避免零周期回调让主循环
忙循环；定时器 ID 回绕时跳过 0 和仍保留在管理器中的 ID。`due_in_ms()` 对超过 `UINT32_MAX`
的等待返回饱和值，因此即使时钟输入暂时回拨，也不会因窄化溢出导致过短等待。

定时器内部按 `next_fire_ms` 和 ID 维护最小堆：添加、重新入堆和到期条目处理为 O(log n)，
`due_in_ms()` 为 O(1)，触发路径只处理已到期的根节点，不再随 timer 总数线性扫描。按
ID 删除仍需 O(n) 定位，定位后的堆调整为 O(log n)；删除主要发生在控件生命周期路径，
不进入每 tick 热路径。回调期间新增条目
进入 pending 队列；当前回调条目保存在内联 current 槽位，回调完成后直接回到活动堆，
因此正常 fire 不使用 deferred 动态容器。新增 timer 不会在同一轮提前触发；回调内删除
只标记失效并在安全点回收。pending 条目只有成功进入活动堆后才从队列移除，临时 OOM
不会让调用方持有的 timer ID 失效。嵌套 fire 使用无分配的 current 链，内层回调可以安全
移除外层当前 timer，恢复顺序不被破坏。该 manager 仍是单线程 owner-loop 组件，不对跨线程
调用作线程安全承诺。回调内调用 `my_timer_manager_destroy()` 会延迟到最外层 `fire()`
收尾，并立即停止同一轮剩余 timer；destroy 请求后不得继续调用该 manager。teardown 期间
manager API 均 fail-closed，避免 lease destructor 重入访问已释放数组。普通窗口管理器
`due_in_ms()` 会清理失效 lease 的堆根，不会因已失效 timer 返回短暂的 `0ms` 忙等；清理
期间 manager 的 add/remove/due/fire 入口也 fail-closed。普通窗口管理器定向测试为
**235/235**。

窗口管理器的 repaint、PAL event、surface event 和 close 事务也维护 callback depth。若
widget 绘制、事件处理或 window close listener 请求 `my_window_manager_destroy()`，manager
会在当前事务返回后再释放，当前帧会停止后续窗口绘制，事件/close 收尾不会访问已释放的
manager。该机制不增加正常绘制的锁或分配；`on_open` callback 同样受此保护。

## Unicode 断行边界

### 严格语料验证

可执行文件 `verify_myui_line_break` 接受一个 Unicode `LineBreakTest.txt` 文件，严格检查
每个码点前的 `÷/×` marker（首个 marker 表示字符串起点，末尾 marker 必须为 `÷`），并使用与 paragraph 相同的 streaming state。它限制单行输入预算，
拒绝代理项、超出 `U+10FFFF` 的值、缺失 marker 和尾部垃圾；发现首个差异时报告行号和边界，
适合在 CI 中固定 Unicode 版本后运行：

```sh
cmake --build build-myui --target verify_myui_line_break
build-myui/verify_myui_line_break /path/to/LineBreakTest.txt
```

该工具提供可重复的 Unicode 17 默认规则验收；本机官方语料当前已通过 60,487/60,487 个
边界。运行时继续保持性能优先的固定状态、无分配、无锁设计。仓库 CTest 同时保留通过和
预期失败的最小 fixture，确保验证器不会把错误输入静默当成通过。

`my_line_break_allowed()` 在所有 PAL/RHI 后端共享，文本排版不会因渲染后端不同而
产生不同换行。当前上下文规则除组合音标、数值标点、希伯来引号和 Regional Indicator
外，还保护 NBSP/figure space/narrow NBSP/word joiner、ZWJ、variation selector、
Emoji modifier、Unicode tag sequence 以及 Hangul Jamo/LV/LVT 组合；这些判断不分配内存，
也不扫描整段文本。UCD 的 `SA` 类别保留为 `MY_LB_SA`，可通过
`my_line_break_options_t` 和 `my_line_break_apply_dictionary()` 对连续 SA run 注入有界
dictionary 边界。每个连续 SA run 最多 256 个 codepoint，使用固定 scratch；回调失败或
预算超限不会提交部分边界修改。

combining-mark 与 LineBreak 表固定使用 Unicode UCD 17.0.0；`tools/generate_myui_line_break_data.sh`
和 combining 生成脚本会在离线生成阶段校验版本，运行时只消费仓库内静态区间表，不读取机器上的
UCD 文件。paragraph 可通过 `my_text_paragraph_process_break_ex()` 和
`my_text_paragraph_process_n_break_ex()` 传递同一 dictionary 选项，wrap 测量会实际消费
回调产生的边界。需要可审计 locale 身份时，使用新增的
`my_text_paragraph_process_break_profile_ex()`、
`my_text_paragraph_process_n_break_profile_ex()` 或
`my_line_break_apply_dictionary_ex()` 传入版本化 profile。profile 固定为版本 1、locale
最多 64 字节且必须与 dictionary callback 成对出现；旧入口保持兼容。完整 locale numeric tailoring、完整 UCD 版本化规则和 locale-specific
dictionary 仍属于后续能力；当前是实用子集，不能宣称为完整 UAX#14 实现。

数值上下文还覆盖数字两侧的斜线：`1/2` 在斜线前后保持同一数值序列，离开该序列后
恢复普通断行。该规则使用固定状态转移，运行时 O(1)、无分配；它不把一般文本中的
斜线全局标记为 glue，也不改变后端 API 或绘制热路径。

## 编辑器折叠与行号

`my_text_area` 的行号栏和折叠均属于 widget/core 能力，不依赖 GL、Vulkan 或 Break RHI
私有类型。行号栏通过 `my_text_area_set_line_numbers()` 启用；折叠通过
`my_text_area_set_folded_range(area, start_row, end_row, true)` 设置，范围为闭区间，首行
作为 header 保留可见，后续物理行隐藏。严格包含嵌套允许，交叉或同起点重叠请求拒绝，
不会改变文本缓冲区和逻辑 row/column 坐标。折叠状态可通过
`my_text_area_folds_to_yaml()` / `my_text_area_folds_from_yaml()` 保存和恢复；YAML 仅允许
`version: 1`、显式 legacy 的 `version: 0`（以及无版本 legacy 快照）、`folds` 数组及
`start`/`end` 整数字段；legacy 导入后由 exporter 统一升级为 `version: 1`，导入采用
事务替换。

折叠打开后，text area 为可见物理行建立缓存；wrap visual-line cache 只为可见行生成
段落。缓存构建按排序折叠区间维护有限活动栈，复杂度为 O(物理行数 + 折叠区间数)。默认
无折叠路径直接复用物理行 offset cache，不创建可见行映射，也不增加逐帧全文扫描。插入或删除导致物理行数量变化时清除折叠区间，避免把旧行号误用于新文本；仅修改
行内内容时保留折叠并从受影响行增量重排。折叠行仍由同一逻辑文本、光标、选区和命中
测试接口消费，绘制后端只接收公共 canvas 命令。

可见行缓存分配失败时不退化为显示全部物理行：count、index 和 row 映射改用不分配内存
的线性回退，继续隐藏折叠行。该回退只发生在 OOM 路径，复杂度可为 O(物理行数 × 折叠
区间数)；正常路径仍保持 O(物理行数 + 折叠区间数)，优先保证折叠语义和光标/滚动映射的
正确性。

text area 的 `MY_TEXT_ALIGN_JUSTIFY` 仅在 wrap 且当前物理行还有后续 visual line 时拉伸
分隔空格；普通 LTR 的绘制、选区和光标边界共用同一份空格宽度计算，不再用固定 cell 宽度
造成输入位置漂移。该计算只扫描当前 visual line，不分配额外缓存；paragraph 现在提供
`my_text_paragraph_line_visual_of_logical()` 与
`my_text_paragraph_line_logical_at_visual()`，将局部 visual layout 映射回全局 logical
boundary，避免跨行 RTL 光标/选区重复实现偏移换算。RTL wrap 的 JUSTIFY 绘制按 visual
顺序逐词提交，光标和选区矩形同时累加 visual 空格的拉伸量；文本、编辑和命中测试不再
分别使用 logical 顺序或未拉伸前缀。

IME 候选框锚点也消费同一 visual-line 映射：wrap 时使用 visual line index 计算 y，justify
时使用实际 stretched-space 边界计算 x，再通过 widget 的全局坐标转换交给 PAL。这样
Wayland、Win32、Cocoa 等平台只接收统一的逻辑候选框位置，不需要知道渲染后端或字体实现。

非 wrap 文本的点击、水平滚动、光标和 IME 锚点也使用字体 glyph advance；无字体时才回退
到 8px cell。wrap 视图只对当前 visual line 计算局部边界，避免每帧构建整段 glyph 缓存，
并让变宽字体在所有输入与绘制路径保持一致。

pointer 命中测试先以有符号坐标处理垂直位置，再转换为 visual-row 索引；控件上方点击
固定落到第一行，下方点击固定落到最后一个可见 visual line，避免负值转 `size_t` 后下溢
跳到文档末尾。坐标与行数计算使用有符号/无符号边界检查，不增加常态分配。

pointer 的 y 命中使用与绘制、滚动和 IME 相同的字体 line-height，而不是配置字号；字体
额外 leading 不会使点击提前落到下一 visual line。该路径只读取既有字体度量，保持 O(1)。

键盘 `MY_KEY_PAGE_UP` / `MY_KEY_PAGE_DOWN` 在 wrap 模式下按 viewport 的 visual line
移动，而不是按物理行移动；长物理行中的分页因此不会停留在原行。目标 visual line 通过
已有缓存的二分索引和数组访问定位，再复用当前的 RTL 边界映射；分页不新增 visual-line
cache 分配，索引路径复杂度为 O(log V)，其中 V 是缓存中的 visual line 数。需要 RTL 边界
映射时沿用现有的单行 layout 临时对象。折叠行不会重新出现，因为目标来自同一份可见
visual-line cache。非 wrap 模式保持可见物理行分页语义。

text area 绘制使用 widget 生命周期内的可复用 scratch buffer 组装 visual line 文本；容量只
在遇到更长行时按需增长，普通重绘不再为每个 visual line 分配和释放临时字符串。光标锚点
也复用同一 buffer，避免长文档闪烁或滚动时的 allocator 抖动。buffer 只属于 myui widget，
不依赖软件、GL、Vulkan 或平台后端；分配失败时保留原有的单行跳过/光标 fallback 行为。
JUSTIFY 绘制进一步在该 buffer 内原地临时切分单词，绘制和测量完成后恢复空格分隔符，
避免每个单词创建独立字符串；因此普通 LTR/可见行路径不随单词数产生堆分配。

每个 wrapped visual line 同时保存 paragraph 计算出的物理行内 byte 区间。绘制、光标和
可见行文本准备直接使用该区间，不再对每个段从物理行首重复扫描 UTF-8；长物理行的绘制
复杂度因此按可见字节数推进，而不是产生 visual-line 数乘以行长度的重复扫描。非 wrap
视图生成等价的整行区间，公开的 codepoint 坐标契约保持不变。

RTL visual line 的 layout 由 widget 持有的固定 4 槽 LRU 缓存管理，在文本内容未变化时跨帧
保留，并由默认方向对齐、选区几何和光标 visual-x 计算共享；连续重绘不再复制 layout。
缓存键包含物理行、visual byte span、文本 revision、字体、字号和 shaping revision，命中时
只更新 LRU 时间戳。缓存容量固定，不在绘制热路径扩容；文本、字体或 shaping 参数变化时
一次性失效所有槽位。居中、右对齐和不涉及选区的 JUSTIFY 路径不额外构建仅用于默认方向
对齐的 layout，保持快速路径。layout 仍由 myui text-layout 层管理，渲染后端只消费公共
绘制命令。

RTL wrap 的 `LEFT`/`RIGHT` 采用 widget 内部的固定大小 visual-line navigation cursor 记录
当前视觉行身份。当相邻 visual line 共享同一 logical boundary 时，连续箭头不会因重新用
`(physical row, logical column)` 反查而停留在旧行；跨物理行时直接进入相邻 visual line 的
视觉 home/end。文本、wrap、字体或 shaping 变化会使该 cursor 失效，外部点击和编辑仍重新
解析当前位置；该状态不分配内存，也不参与绘制帧路径。

text area 还为当前热物理行缓存 codepoint boundary 到 glyph advance 的前缀和。命中测试、
光标、选区和 IME 几何查询共享该前缀和；缓存键包含物理行、文本 revision、shaping
revision、字体指针和字号，文本编辑、字体配置或 shaping 配置变化后自动重建。正常重复
查询为 O(1)，首次建立仍是当前行长度级别；分配失败回退到原有逐 codepoint 扫描，不影响
坐标正确性。

### Shaping 参数与几何一致性

`my_text_layout_visual_x_ex()`、`my_text_layout_visual_boundary_x_ex()`、
`my_text_layout_logical_at_x_ex()` 和 `my_text_layout_visual_rects_ex()` 接受同一份
`my_font_shape_params_t`。旧 API 保留默认参数兼容路径。layout 的 boundary cache 不仅
按字体和字号命中，还按 `rtl`、script、language 内容和 features 内容命中；字符串键由
layout 自己复制，且沿用字体 shaping 的 64/1024 字节预算，避免调用方释放或修改参数后
污染几何结果。

`my_text_area_set_shaping_params()` 对参数字符串做有界校验、无堆分配规范化和事务复制；
等价 feature 列表不会造成伪 revision 失效。设置成功会使
wrap paragraph、热行 geometry、光标、selection、IME hit-test 的 shaping revision 失效；
换行使用 `my_text_paragraph_process_ex()`，几何使用上述 `_ex` API。这样不同 language、
feature 或 direction 不会复用旧 advance/cluster boundary。渲染后端仍只消费公共 canvas
命令，shape provider 不存在时回退到安全的 glyph advance 路径。`my_vgcanvas_draw_text_ex()`
和 `my_vgcanvas_measure_text_ex()` 在同步调用期间注入同一 shaping 参数，soft、GLES2、
Vulkan 与 Break RHI 共用该路径；旧 API 保持默认参数和旧 vtable 布局。参数上下文不跨帧
保存，避免悬空指针，glyph/advance 结果仍由各后端当前帧事务消费。

### 增量语法行模型

`my_syntax_cache_t` 位于 `myr`，不依赖任何渲染后端。它支持 C-like 和 YAML 的有限词法
分类（keyword、identifier、number、string、comment、punctuation），token 坐标使用
codepoint 范围；跨行 `/* ... */` 状态会传播到后缀。`my_syntax_cache_replace_line()`
只使修改行及其后缀失效，`my_syntax_cache_ensure()` 每次最多重建调用方指定的行数，
因此绘制或输入路径不会被迫扫描全文。源文件、单行和单行 token 数量都有固定上限，
超限直接拒绝。

text area 在启用语法高亮后懒创建该 cache，并在 paint 前按 `syntax_line_budget` 增量推进；
ready 的有字体行进行 token 分段绘制，RTL 行先复用 visual layout，再按 visual-order
片段和 token 颜色绘制。默认关闭时不创建 cache、不启动 timer，也不扫描全文。无字体和
cache 未 ready 时继续使用原整行绘制；JUSTIFY 仍使用受限的逐词绘制，复杂 RTL GSUB
与跨 face shaping 不在该 lexer 契约内。

文本布局和 paragraph 入口同样受 4 MiB 字节预算约束：预检最多读取预算边界，超限在
缓存查找、文本复制和字体排版前失败，不触发调用方 allocator。该预算保护布局冷路径的
恶意超长输入，正常输入仍复用既有全局 layout master cache、paragraph 增量缓存和各后端
的 glyph 路径。

## CSS/YAML 解析边界

CSS 仍采用明确的 subset 契约：结构性 selector/rule 错误返回带行列号的失败；声明
值错误保持兼容模式，告警后跳过，不污染已解析规则。`@media all` 和 `@media screen`
在解析阶段展开为普通规则，不把 viewport、平台或渲染后端状态带入主题查询；媒体容器
嵌套深度受 `MY_CSS_MAX_AT_RULE_NESTING` 限制。未知 `@` 规则不会执行；带条件的 `@media`
在使用媒体上下文入口时于解析期评估，否则按兼容/严格策略处理。未知规则的跳过器会识别引号及反斜杠转义、块注释和嵌套大括号，避免字符串或注释中的
`}` 截断规则范围。该行为不等于完整 at-rule 支持。需要避免配置静默失效时使用
`my_css_parse_ex(..., MY_CSS_PARSE_STRICT_AT_RULES, ...)` 或
`my_theme_load_css_ex(..., MY_CSS_PARSE_STRICT_AT_RULES)`；严格模式拒绝未知策略位和
未实现的 at-rule，并返回解析失败，主题桥接在解析阶段失败时保持原主题不变，默认
`my_css_parse()`/`my_theme_load_css()` 的兼容行为不变。

条件媒体查询还支持受限的 `not`：它只能修饰一个媒体特性（例如
`not (prefers-color-scheme: dark)`），不能与媒体类型或 `and` 继续组合。扩展媒体上下文
中的未知事实保持 unknown，`not` 不会把 unknown 错误地变成匹配；只有已知 true/false
才分别取反/保持。窗口媒体快照比较按字段完成，不依赖结构体 padding，因此不同编译器和
后端 ABI 下不会因未定义 padding 误触发主题重载。

`@supports` 支持有界的 `and`、`or`、`not` 逻辑表达式，原子条件为
`(property: value)`，复用 CSS 声明值解析器和现有 key alias，并在解析期展开。查询固定受
`MY_CSS_MAX_SUPPORTS_QUERY_BYTES` 和 `MY_CSS_MAX_SUPPORTS_NESTING` 限制；未知属性和值、
非法运算符在严格模式下返回 `MY_CSS_ERROR_UNSUPPORTED_FEATURE`，`capability` 指向
`MY_CSS_FEATURE_SUPPORTS`，兼容模式则跳过整个 block。展开后的主题查询不再重复评估
supports 条件，因此不增加渲染帧分配、锁或后端分支。

能力判断不应通过试解析或字符串匹配完成。`my_css_capabilities()` 返回进程级只读注册表，
其中 `supported_features`、`supported_parse_flags`、`max_bytes` 和 `max_ancestors` 是稳定的
资源/能力边界；该查询无分配、无锁、无渲染后端状态。解析错误同时提供稳定的
`my_css_error_code_t`，严格模式拒绝未实现 at-rule 时将 `code` 设为
`MY_CSS_ERROR_UNSUPPORTED_FEATURE` 并把 `capability` 指向相关的
`MY_CSS_FEATURE_AT_RULES` 或 `MY_CSS_FEATURE_SUPPORTS`；
预算超限和未知策略分别使用 `MY_CSS_ERROR_INPUT_LIMIT` 与
`MY_CSS_ERROR_UNKNOWN_POLICY`。原有 `line`、`col` 和 `msg` 字段继续保留，旧调用方无需修改。

`@import` 通过 `my_css_parse_with_options()` 和
`my_theme_load_css_with_options()` 的显式 resolver 接入。resolver 只接收引号包裹的
有界相对路径，并返回 CSS 源；解析器在冷路径递归展开，保留导入点的规则顺序和当前
`@media`/`@layer` 上下文。根文档与导入文档共享 `MY_CSS_MAX_BYTES` 总预算，同时限制
导入深度、次数和路径长度；活动路径重复会被识别为循环。源可提供可选 `release` 回调，
解析完成或失败后恰好释放一次。resolver 失败、循环或预算超限会使整张 sheet 失败，主题
bridge 在候选提交前失败，不发布半成品。严格模式下没有 resolver 的 `@import` 返回
`MY_CSS_ERROR_UNSUPPORTED_FEATURE` 并标识 `MY_CSS_FEATURE_IMPORTS`；兼容模式跳过该导入。
解析器本身拒绝绝对路径、路径穿越、空路径段、反斜杠、控制字符和 Windows 盘符；生产
resolver 仍应限制根目录并拒绝不可信符号链接。

需要启用条件媒体时，调用 `my_css_parse_media_ex()` 或
`my_theme_load_css_media_ex()` 并传入一次性的 `my_css_media_context_t`。这两个旧入口
保持原有结构体布局和兼容语义；需要区分“已知为否”和“未知”时，使用布局扩展的
`my_css_media_context_ex_t` 与 `my_css_parse_media_ex2()` /
`my_theme_load_css_media_ex2()`。当前支持
`screen`、`min/max-width`、`min/max-height`、精确 `width/height`（仅 `px`）、
以及有界 CSS range 比较（例如 `width >= 800px`、`400px <= width < 800px`）、
`orientation`、`prefers-color-scheme`、`prefers-reduced-motion`、`hover`、`pointer`、
`any-pointer`、`color-gamut` 和 `dynamic-range`；逗号表示 OR，
同一 query 内的 `and` 表示 AND。query 长度固定限制为
`MY_CSS_MAX_MEDIA_QUERY_BYTES`，不支持的单位、特性或语法在严格模式下失败；匹配结果
在解析期展开，未匹配 block 整体丢弃，因此主题查询热路径不读取 viewport 或偏好状态。
设备能力通过 `my_css_media_context_t.capabilities` 显式位掩码传入，只允许
`MY_CSS_MEDIA_CAP_ALL` 内的位；未知位和值均拒绝。`color-gamut` 使用等级语义：
`p3` 满足 `srgb`，`rec2020` 满足 `p3` 和 `srgb`；`dynamic-range: standard` 是默认
兼容条件。上下文由调用方在解析前一次性采集，解析器不负责平台能力发现，因此该契约
不会把 X11、Win32、Wayland、macOS 或 GL/Vulkan 类型泄漏到 CSS 层。
旧的 `my_css_parse_ex()`/`my_theme_load_css_ex()` 未提供上下文时仍保持兼容行为，条件
媒体不会被静默应用。

应用层如需让 YAML 窗口的设备媒体条件使用宿主事实，窗口会通过 PAL 的版本化可选
媒体 provider 一次性取得平台无关快照，再映射到 CSS 扩展上下文。冻结的
`my_pal_vtable_t` 布局不包含媒体函数，旧 PAL vtable 不会被读取越界；旧的
`my_pal_get_media_context()` 仍作为兼容包装，仅返回基础事实。provider 使用
`MY_PAL_MEDIA_PROVIDER_ABI_VERSION` 与 `size` 校验，应在 PAL 销毁流程中注销。注销会
先阻止新查询，并在途查询退出后再释放 provider context。查询只在
冷路径执行；注册表锁不进入渲染帧和主题查找热路径，不暴露 X11、Wayland、Win32、Cocoa 或 RHI 类型；未实现的 PAL 返回
`MY_RET_NOT_SUPPORTED`，窗口按安全默认（`screen`、零设备能力）继续。Linux 原生平台
只声明可稳定证明的 pointer/hover 与 sRGB；X11 在 XInput2 可用时按设备类采集 coarse/fine
及 hover，扩展不可用时回退核心指针语义，并在当前 RandR 输出的 EDID 可验证时识别
Display P3/Rec.2020 与 CTA PQ/HLG HDR；Windows/macOS 在冷路径读取可用的系统颜色
方案与 reduced-motion 偏好，Windows 还将系统鼠标/触控指标映射为 pointer 能力。Cocoa
会从窗口当前屏幕的 Color Space 识别 Display P3/Rec.2020，并从可用的 EDR selector 识别 HDR；Win32
通过当前窗口匹配的 Display Configuration 2 读取明确 supported、enabled 且 active 的 HDR 状态；旧版
advanced-color 接口不区分 WCG 与 HDR。X11、Wayland 和 Win32 结果缓存于 `Platform` 快照，
设置/显示器/输入设备消息只使快照失效，正常读取为 O(1) 复制；Cocoa 的显示/外观查询仍
在媒体冷路径按当前窗口重新采样。Windows/Linux
的 P3/Rec.2020 在没有可靠平台证据时保持未知，不通过猜测改变样式。Break 适配器复用宿主
Platform 快照，Dummy PAL 可注入快照用于确定性测试。Break 平台适配器还暴露无分配的
`platform_get_media_generation()`：X11 RandR、Wayland seat/output、Win32 显示/设置/
输入设备/DPI 和 Cocoa backing-scale 事件递增饱和代际；`break_ui_pump()` 只在代际变化
时调用 `my_window_manager_refresh_media()`，因此不会把 CSS 重建放入逐帧热路径。代际
通知只表示“事实可能变化”，不增加未知能力，也不替代媒体快照的最终校验。
需要处理资源失败的宿主可使用 `my_window_manager_refresh_media_ex()` 获取明确返回码；
任一窗口提交失败时，调用方不会确认新的媒体代际，后续冷路径会重试，已成功窗口保持
已提交状态而不会重复分配。

媒体 provider 注册表对在途查询采用固定 slot token：注销会立即阻止新查询，但不会复用
或释放仍被查询持有的 provider context；最后一个查询退出后才回收 context。这样 PAL
销毁不依赖忙等，也不会让查询线程在 PAL 已释放后再次解引用 PAL 指针。provider 回调
仍不得递归销毁所属 PAL；回调内重新注册返回 `MY_RET_PENDING`。

主题桥接加载采用候选主题事务：解析成功后先深拷贝现有 entries（包括每个 state 的
style value 与 specificity），再把 CSS 声明应用到候选主题；只有全部复制和写入成功才
交换 entries。复制、解析或 CSS 写入任一点 OOM/失败都只销毁候选对象，活动主题及其旧值
保持不变。该路径位于公共 theme 层，不依赖 soft、GLES2、Vulkan 或 Break RHI。

legacy `my_theme_load_str()` 复用公共 `my_theme_clone()`，文本主题的所有行也先写入候选
主题，成功后才交换 entries；坏行、字符串复制和扩容失败不会污染原主题。默认主题的
逐属性初始化同样检查返回值，不能返回半初始化的默认主题。
文本主题 C-string 入口还受 `MY_THEME_MAX_BYTES` 4 MiB 有界 NUL 扫描保护。

YAML loader 使用统一的 `my_conf` 类型树，不引入第三方 YAML 运行库。UI 文档的根节点
必须是 map，并包含字符串 `type`；普通属性直接作为同名键，子控件放在 `children` 数组，
绑定放在 `bindings` map，主题放在 `style` 字符串。例如：

窗口 `style` 不含 `{` 时使用 legacy 文本主题格式；含 CSS block 时使用严格 CSS 策略。
两种格式的解析、主题复制或写入失败都会使 YAML 窗口加载失败，而不是返回一个未完整
应用样式的窗口。样式应用完成后窗口树才交付调用方；CSS 主题本身仍使用候选深拷贝和
成功交换事务，查询热路径不增加分配。

含 CSS block 的窗口样式还会保留源文本和加载前主题基线。窗口创建时，以及逻辑窗口
尺寸发生 resize 时，loader/window 层只在冷路径按 `my_pal_window_get_size()` 采样一次
viewport，并重新评估 `@media`。媒体断点使用逻辑像素，不使用物理 drawable 尺寸或
HiDPI scale，因此不同渲染后端的 breakpoint 语义一致。重算遵循
`clone -> parse/apply -> swap`：候选主题完整成功后才替换当前主题；失败时保留当前主题、
旧 CSS 源和旧媒体结果。正常帧的主题查询只读取已展开规则，不重复执行媒体判断。

```yaml
type: widget
layout: linear:v:8
children:
  - type: label
    text: Hello
  - type: button
    text: Apply
    cooldown: 1500
    bindings:
      click: apply_command
```

loader 只接受 YAML 类型匹配的值：布尔属性必须是 YAML bool，整数属性必须在 `int32_t`
范围内，浮点属性必须有限，`children` 必须是 sequence，`bindings` 的值必须是 string。
button 的 `cooldown` 是非负毫秒整数；成功 click 后才开始计时，负值在严格 schema 校验或
属性 setter 阶段拒绝。
绑定展开到固定 512-byte 规则缓冲，超限直接失败。解析失败或 widget 构造失败不会返回
部分构造树，也不会保留临时配置树。通用 YAML parser 额外限制输入 4 MiB、65536 行、
256 层 block/flow 嵌套、单容器 4096 个子项和 1 MiB 标量；这些限制在 `my_conf` 层执行，
不会因其他调用方绕过 UI loader 而失效。map key 也适用 1 MiB 上限；所有 map 形式（包括
sequence 内联 map）均拒绝重复键，防止静默覆盖已验证的配置。

通用 `name`、`tooltip`、`class` setter 的分配失败会终止候选 widget；`layout` 仅接受
`default` 或格式完整且间距在 `int32_t` 范围内的 `linear:h[:spacing]`/`linear:v[:spacing]`，
不再把未知轴向或溢出数字静默转换为有效布局。

`my_ui_load_file()` 在读取文件 payload 前执行同一 4 MiB 文件预算检查；超限文件会先关闭
文件再返回错误，不会按攻击者提供的文件长度申请完整缓冲区。文件中的嵌入 NUL 也会被
拒绝，而不是被 C 字符串 API 截断；`test_myui_loader` 的文件级资源边界回归与字符串级
预算回归均纳入测试门禁。

文件 payload 分配失败和实际读取失败同样写入 `my_ui_error_t`，避免 I/O/OOM 路径返回
无诊断的 NULL。窗口 `style` 的 CSS/legacy 主题加载失败也会在窗口交付前传播，合法 CSS
样式则通过严格 at-rule 入口应用。

YAML loader 同样提供 `my_ui_loader_capabilities()` 只读注册表，可在构造 widget 前查询
YAML schema、`children`、`bindings` 与 CSS style 能力，以及 factory 数量、绑定规则和输入
预算。`my_ui_error_t` 的 `my_ui_error_code_t` 将参数、输入预算、YAML 语法、schema、未知
控件、资源和样式失败分开；原有 `line` 与 `message` 字段保持不变。注册表和错误分类均
不参与绘制帧路径，不增加渲染后端依赖或热路径分配。`field` 返回首个可识别的 YAML key
（例如 `children`、`visible` 或 `style`），无法映射到单一 key 时返回 `document` 或空值。
`path` 返回固定 128 字节预算内的嵌套位置，例如 `children[0].children[0].visible`；路径
过深时使用 `<path-truncated>`，不会为诊断分配内存或让错误路径越界。
`my_ui_loader_query_type()` 以零分配方式返回内置 widget class 的属性类型、属性数量和事件
列表；仅注册了自定义 factory 的类型会明确标记 `factory_registered`，但不会假定其有 schema，
避免把不透明 factory 的未知属性错误地宣称为可验证能力。

`my_ui_type_info_t` 同时包含所有 built-in type 共用的 `name`、`tooltip`、`class`、几何、
可见性、layout 参数和 layout 字段；`window` 根节点额外暴露 `title` 与 `style`。显式
`my_ui_load_str_ex()` / `my_ui_load_file_ex()` 支持 `MY_UI_LOAD_STRICT_SCHEMA`：它对有公开
schema 的内置类型和 `my_ui_loader_register_schema()` 注册的 factory 拒绝未知 key，并在
`field` 返回该 key；默认入口保留兼容的未知字段忽略行为，未带 schema 的自定义 factory
仍由其自身管理未知属性。

自定义 schema 可使用 `my_ui_loader_register_schema_ex()` 声明当前 `schema_version` 和迁移
回调，也可使用 `my_ui_loader_register_schema_chain()` 声明最多 16 个连续的单版本迁移步骤。
公共 `version` 为有界非负整数；省略时按当前版本兼容，低于当前版本的显式值必须
由 callback/完整链路迁移，未来版本直接拒绝。迁移在严格校验和 factory/window 创建之前对私有
`my_conf` 树执行，并递归覆盖 `children`；任一节点迁移失败、OOM、类型改变或超过 YAML
深度预算都会销毁整棵候选配置树，保留 `field`/`path` 诊断且不创建部分 widget。链路表、callback、
属性表和事件表均为 borrowed 数据，必须覆盖注册周期；class registry 的类型名、属性名和
事件名会复制到 owned snapshot；旧的 `register`/`register_schema`
API 默认 schema version 为 1，因此没有 `version` 的既有 YAML 无需修改。
registry 注册会拒绝 `type`、公共字段、`children`、`bindings`、`title`、`style` 等保留
字段冲突，以及重复属性/事件名；校验失败发生在替换旧条目前，旧注册条目保持不变。

需要让自定义类型也具备可验证契约时，使用 `my_ui_loader_register_schema()` 注册静态
`my_prop_desc_t` 属性表和事件表；该 API 不复制表、不申请内存，调用方必须保证表的生命周期
覆盖整个 loader 注册周期。带 schema 的 factory 会参与严格未知 key 检查，未带 schema 的旧
`my_ui_loader_register()` 仍保持不透明兼容行为。未知 load policy 单独返回
`MY_UI_ERROR_UNKNOWN_POLICY`，不会与 YAML 内容错误混淆。

class registry 与 YAML factory registry 均采用启动期冻结、运行期冷路径热插拔的性能优先模型。
应用完成所有内置/自定义注册后调用 `my_widget_class_freeze()` 和
`my_ui_loader_freeze()`；两者幂等。启动期注册在冻结后返回 `MY_RET_NOT_SUPPORTED`，class registry
的运行期变更必须使用 `my_widget_class_runtime_register()` 或
`my_widget_class_runtime_unregister()`；YAML factory/schema 仍遵循 loader 自身的冻结契约。class registry
的 type、属性和事件名称均限制在固定 64 字节内，属性表最多
64 项、事件表最多 32 项，并拒绝 loader 保留字段、重复项和非法属性类型；任一校验失败
都不会替换旧条目。class registry 会复制类型名、属性名和事件名；factory、setter/getter
和 instance checker 回调仍由调用方持有并保证注册表使用期间有效。built-in 批量注册失败时
整批回滚。`my_ui_loader_query_type()` 会将类型名、属性描述符名称和事件名称复制到
`my_ui_type_info_t` 的固定有界存储，返回指针在该结构被覆盖前稳定，不依赖 registry
内部表的生命周期。class registry 运行期使用不可变 table snapshot 并以 release 原子发布；
冻结后的查找只加载当前表并做有界查找，无读锁、分配或部分复制可见性。旧 table 和旧 class
descriptor snapshot 保留到进程退出，以保证已返回的 class 指针稳定；该 API 适合低频模块切换，
不适合每帧或无界高频注册。runtime unregister 只影响新查找，不销毁旧 class 指针对应的快照。
运行期 loader/schema 热插拔必须通过 loader 的注册 API：多个查询/加载读者可并行，
替换写者会阻止新读者并等待在途读者结束后再释放旧 dynamic schema；不能绕过 freeze 契约
直接并发写入进程级表。factory/migration 回调不得递归注册。registry 读锁可以覆盖一次
load 的查找、schema 预检、migration 和 factory 生命周期，因此回调不得递归调用任何
registry 写 API，包括注册、动态 schema 替换和 freeze。实现使用线程局部 callback 深度
在写入口快速返回 `MY_RET_NOT_SUPPORTED`，不会在读锁内等待写锁，也不在加载热路径
分配或增加额外锁；class registry 的注册和 freeze 入口也使用同一守卫，不能从 loader
回调绕过启动期只读契约。回调返回后深度立即恢复，即使回调报告失败也不会污染后续加载。

需要运行时生成 schema 时使用 `my_ui_loader_register_dynamic_schema()`。该 API 接收显式的
属性/事件数量，在固定上限内复制 descriptor 名称和回调元数据到 registry-owned 存储；输入数组
只需保持到函数返回。复制使用传入的 allocator，且该 allocator 及其 context 必须保持有效直到
动态 schema 被替换或进程退出。替换旧条目时先完成全部复制和校验，失败返回 `MY_RET_OOM`
或 `MY_RET_INVALID_PARAMS` 且旧 schema 保持不变。启动期动态 schema 仍只能在 freeze 前注册；
冻结后可使用 `my_ui_loader_runtime_register_schema()` 或
`my_ui_loader_runtime_register_dynamic_schema()` 做低频 factory/schema 新增或替换，使用
相同的写租约等待在途查询/加载结束后再发布。`my_ui_loader_runtime_unregister()` 只影响新
查找，旧加载读者不会看到被释放的 owned schema；`window` 和 built-in class 不允许被覆盖或
删除。owned schema 随条目替换或注销释放，不把临时生成器数组或其 allocator 生命周期泄漏到
渲染线程；替换期间的失败仍保留旧条目。
严格 schema 还会在 factory 创建前检查已声明属性的 YAML 标量类型、`int32_t`/`float` 范围
和颜色整数范围，并以该属性名写入 `field`；这样错误配置不会先产生部分 widget 或触发
自定义 setter 副作用。严格入口还会在创建任何 widget/window 前校验 `type`、公共字段、
`children`、`bindings`、窗口 `title/style` 及 layout 语法，并递归预检整棵子树；因此父
factory 不会因后代节点的 schema 错误而先产生副作用。嵌套错误路径一旦达到固定预算就
保持为 `<path-truncated>`，不会继续拼接造成误导。
当编译时关闭 `MYUI_UI_YAML` 时，query、load 和 schema-register API 都保留安全的
`MY_RET_NOT_SUPPORTED` stub，避免裁剪构建产生 ABI/链接分叉。

通用 `my_conf_load_file()` 的 JSON 文件入口也使用独立的 `MY_CONF_FILE_MAX_BYTES` 4 MiB
预算，并在申请 payload 前拒绝超限文件；该入口不改变 YAML UI loader 的类型化 schema。
直接 `my_conf_parse_json()` 同样受 `MY_CONF_JSON_MAX_BYTES` 4 MiB 输入预算保护，避免从
内存 API 绕过文件入口限制。
JSON 写出器也受同一 4 MiB 输出预算保护，超限序列化返回失败，不会产生不可重新加载的
配置文件；程序化配置树中的 `NaN`/`Inf` 等非有限浮点值同样拒绝写出。
JSON parser 同时拒绝 `strtod` 溢出的非有限数字，保证 RFC 数字输入不会落入不可序列化
的运行期值。
YAML 与 TOML 普通数字的 `strtod` 溢出也会失败；TOML 的显式 `inf`/`nan` 保持兼容。
CSS 内存解析入口受 `MY_CSS_MAX_BYTES` 4 MiB 预算保护，超限输入在创建 sheet 前拒绝；
主题桥接沿用同一限制。
结构错误状态独立于可选的错误输出对象，调用方传入 `NULL` 仍不会接受畸形 CSS。
selector 最多包含 4 个祖先 compound。路径按目标到根方向匹配：空白是可跨层的
descendant，`>` 只接受直接父节点；祖先支持 type/class/id 组合，但不接受伪类（祖先
状态不在主题查询键中）。匹配使用主题条目内的固定数组，不在绘制或查询热路径分配；
超过深度、重复/悬空 combinator 和错误祖先形式在解析期拒绝。单祖先仍填充旧的
`ancestor_type`/`ancestor_direct` 观察字段，旧 `my_theme_set_ex*()` API 保持兼容。
TOML 与 BSON 直解析入口分别受 `MY_CONF_TOML_MAX_BYTES` 和
`MY_CONF_BSON_MAX_BYTES` 4 MiB 预算保护，所有配置树解析入口均在节点分配前拒绝超限输入。
BSON 写出器也受同一输出预算保护，超限时释放候选缓冲并返回失败。

UI 配置不再支持 XML，loader 不再暴露 XML capability/API，`my_xml.*` 和 `test_myui_xml` 已移除；Wayland 协议生成所需的
`.xml` 文件仍属于平台协议输入，与 myui UI schema 无关。

集成基线是上游 `myui` commit `676bfd10f96992a3efa100d67118690063c279cf`。
上游源码以 vendored 形式置于本仓库，平台与 RHI 适配层只在 `mypal/break`、
`myr/my_vgcanvas_break_rhi.c` 和 `src/ui/myui_break*` 中实现，避免把 Break API
反向泄漏到 widget、MVVM 或文本排版核心。

## 目录

```text
engine/
├── external/SheenBidi/            # BiDi + Arabic shaping
├── src/myui/
│   ├── mypal/break/               # Break PAL adapter
│   ├── myr/my_vgcanvas_break_rhi.c # Break RHI vgcanvas backend
│   └── ...                        # myui core
├── src/ui/
│   ├── myui_break.h/c             # BreakUI 应用桥
│   └── myui_break_input.h/c       # Platform key -> myui key
├── apps/duanxianxia/
│   ├── dxx_app.h/c                # 可复用的 dxx 首页组合
│   └── dxx_break_main.c           # Break RHI 可执行入口
└── shaders/ui_img*                # RHI UI image pipeline
```

## CMake 目标与选项

| 目标 | 说明 |
|------|------|
| `myui_core` | myui 核心静态库，包含 font/image/yaml/bidi/mvvm/widget 子系统 |
| `break_myui` | `my_pal_break` + RHI vgcanvas + `BreakUI` 桥 |
| `dxx_core` | duanxianxia 视图构建器 |
| `dxx_break` | Break-aware duanxianxia demo |

| 选项 | 默认 | 说明 |
|------|------|------|
| `MYUI_FONT_STB` | ON | stb_truetype 字体后端；`my_font_stb_create_ex()` 支持显式 TrueType Collection face index |
| `MYUI_FONT_FREETYPE` | ON（找到 FreeType 时） | 启用 hinting、TTC 多字面和 CJK 默认字体 |
| `MYUI_HARFBUZZ` | ON（同时找到 FreeType 与 HarfBuzz 时） | 优先使用 CMake package target，回退 pkg-config；启用 OpenType shaping |
| `MYUI_IMAGE_STB` | ON | stb_image 解码 |
| `MYUI_UI_YAML` | ON | YAML UI loader |
| `MYUI_BIDI` | ON | 内置 SheenBidi |

独立 myui CMake 入口遵循同一依赖策略：FreeType 使用 `Freetype::Freetype`，HarfBuzz
优先使用 `harfbuzz::harfbuzz`，没有 CMake package 时回退 `PkgConfig::HARFBUZZ`；缺少
可选依赖时保持对应字体后端关闭，不影响软件、OpenGL 或 Vulkan 其它路径。
独立构建还可通过 `-DMYUI_THIRD_PARTY_DIR=/path/to/dependencies` 覆盖 stb 与 SheenBidi
目录；`MYUI_SOURCE_DIR` 和 `MYUI_ENGINE_SOURCE_DIR` 均由模块位置推导，不依赖调用方的
`${CMAKE_SOURCE_DIR}` 布局，也不会把顶层工程误当成头文件根。
可复用入口按 `myc -> myr -> mypal -> myui -> mymvvm -> mymvvm_myui` 顺序加入。
其中 `mypal` 默认提供无窗口系统的 dummy port，真实 X11/Wayland/Win32/Cocoa port
仍由 engine 宿主目标选择，避免把平台库带入 headless 或嵌入式构建。配置回归
`test_myr_dependency_config` 会检查五个模块的路径契约和 PAL target；隔离顶层构建已
在关闭字体、YAML、BiDi 和图像可选项时完成 `87/87` 编译。

网络模块的 UDP 测试使用 `net_udp_create(0)` 获取内核临时端口，并通过
`net_socket_get_local_address()` 构造 loopback 目标，不依赖固定端口或进程号哈希；该 API
在 Linux、Windows 等支持 IPv4 `getsockname()` 的平台保持相同语义。

## 构建与测试

```bash
# OpenGL
cmake -S engine -B build-myui -DENGINE_BUILD_TESTS=OFF
cmake --build build-myui --target dxx_break break_myui myui_core dxx_core -j

# Vulkan
cmake -S engine -B build-myui-vk -DENGINE_BUILD_TESTS=OFF -DENGINE_VULKAN=ON
cmake --build build-myui-vk --target dxx_break break_myui -j

# Headless myui 单元测试
cmake -S engine -B build-myui-tests -DENGINE_BUILD_TESTS=ON -DENGINE_VULKAN=OFF
cmake --build build-myui-tests -j
ctest --test-dir build-myui-tests -R 'test_break_ui_input|test_myui_vggeometry|test_myui_window_manager|test_myui_font' --output-on-failure

# Wayland + OpenGL
cmake -S engine -B build-myui-wayland -DENGINE_ENABLE_WAYLAND=ON -DENGINE_BUILD_TESTS=ON
cmake --build build-myui-wayland --target dxx_break -j

# Wayland + Vulkan
cmake -S engine -B build-myui-wayland-vk -DENGINE_ENABLE_WAYLAND=ON -DENGINE_VULKAN=ON -DENGINE_BUILD_TESTS=OFF
cmake --build build-myui-wayland-vk --target dxx_break -j
```

运行 `dxx_break`：

```bash
./build-myui/dxx_break          # OpenGL
./build-myui-vk/dxx_break       # Vulkan
```

默认字体候选会优先选择系统的简体中文 CJK 字体：Linux 为 Noto Sans CJK SC（TTC 第
`2` 面）、Windows 为微软雅黑/宋体、macOS 为苹方。FreeType 可用时会正确加载 TTC
中的目标面并使用字形 hinting；若 CMake 未找到 FreeType，则只支持独立 TTF/OTF 的
`stb_truetype` 回退，不能正确解析 Noto 的可变 TTC。

可用 `BREAK_MYUI_FONT=/path/to/font.ttf` 覆盖默认字体；当覆盖文件是 TTC 时，配合
`BREAK_MYUI_FONT_FACE=<non-negative-index>` 选择面（例如 Linux Noto Sans CJK SC 为
`2`）。覆盖 TTC 需要启用 `MYUI_FONT_FREETYPE`。着色器搜索顺序为当前目录、`engine/`、
`../engine/`、`../../engine/`，也可用 `BREAK_SHADER_DIR` 指向引擎根目录。

## 桥接结构

### Break PAL (`my_pal_break`)

包装已有 `Platform *` 和 `RHIDevice *`：

- 布局尺寸来自 `platform_get_logical_size()`；RHI device、swapchain、viewport 和
  BreakUI offscreen surface 使用 `platform_get_drawable_size()`。旧
  `platform_get_size()` 仅保留为平台原生事件单位兼容接口，不能再传给 RHI。
- `platform_get_content_scale()` 描述逻辑坐标到 drawable 像素的内容缩放；
  `platform_get_input_scale()` 描述平台输入坐标归一化到 myui 逻辑坐标所需的除数。
  X11/Win32 输入为物理像素，除数等于内容缩放；Wayland/Cocoa 输入已经是逻辑点，除数为 1。
- 即时调试 UI 同样遵循这条边界：布局和 hit-test 使用 logical 尺寸及已归一化的鼠标，
  `my_vgcanvas_break_rhi` 目标和 RHI compositing 使用 drawable 尺寸，并由 canvas scale
  将逻辑几何转换为物理像素。
- IME spot 转发至 `platform_ime_set_spot`。
- OpenGL 使用 `platform_window_native`，引擎 Vulkan 使用 `platform_surface_native`。
  Wayland 中前者是 `wl_egl_window`，后者是 `wl_surface`，不能交叉传给 RHI。
- Break PAL 不实现 `my_pal_window_vk_create_surface`：该可选接口要求返回由 myui
  私有 `VkInstance` 创建的 `VkSurfaceKHR`，而 BreakUI 已经复用宿主 RHI 的 device、
  swapchain 和 offscreen surface。返回 native handle 会违反 API 所有权与类型契约。
- timer 使用 `time_microseconds() / 1000`。
- 多个 myui 逻辑窗口共享一个 Break OS window、一个 RHI vgcanvas 和一次合成提交；
  root window 是唯一允许请求原生窗口拖动的窗口，dialog 的移动保持在共享表面坐标内。
- posted event 队列是带原子锁的 O(1) FIFO，不会因 burst 事件产生 `darray_remove_at(0)`
  的 O(n^2) 移动成本。
- `break_loop_run()` 是嵌入式 PAL 的 drain 操作：没有已排队事件或到期 timer 时立即返回，
  不负责阻塞等待，也不调用 OS `platform_poll()`。独立宿主必须在自己的每帧循环中按
  `platform_poll()` -> `break_ui_pump()` -> `break_ui_frame_begin()` ->
  `break_ui_render()` -> `rhi_frame_end/present` 顺序驱动。`break_ui_frame_begin()`
  在固定容量缓冲中收集 drawable damage，只有 surface、present target 保留能力、present
  damage 能力和后端实际 partial 状态都满足时才调用 `rhi_frame_begin_damage()`；否则调用
  普通全屏 `rhi_frame_begin()`。无变化且后端确认未更新像素保留时返回 `NULL` 并将
  `out_skip` 置为 true，此时宿主不得调用 `rhi_frame_end()` 或 `rhi_present()`。尺寸、
  damage 或设备状态异常均返回安全失败，不会将本应全屏绘制的帧误判为跳过。

### Clipboard

`clipboard_get_text_alloc` 是控件使用的完整文本接口：调用方以其 myui allocator
释放返回值，因此 edit/text-area 不再受早期 `256`/`4096` 字节临时缓冲限制。粘贴使用
一次过滤、一次文档插入和一条 undo 记录，避免逐字符重分配的 O(n^2) 行为。

所有平台的 clipboard 写入和外部 UTF-8 selection 在提交到 PAL 缓存前都按显式字节长度校验，拒绝
overlong、surrogate、超出 `U+10FFFF`、截断序列和嵌入 NUL，避免恶意 selection 穿透到
编辑器或 shaping；校验为单次 O(n) 扫描，不增加绘制路径开销。X11 与 Wayland 对本地和
接收完成的文本使用同一规则，且都允许不含终止字节的最大 `16 MiB` payload，并额外保留
一个 NUL 终止字节；Wayland 在达到上限时先用非阻塞单字节读取探测 EOF，恰好上限且已
结束的传输成功，仍有额外字节或校验失败时丢弃本次传输，不污染旧缓存。

- Windows 使用 `CF_UNICODETEXT`；Cocoa 使用 `NSPasteboardTypeString`，二者同步读取。
- X11 使用 `CLIPBOARD`/`UTF8_STRING`/`TARGETS`，含 `INCR` 分块传输；读取永不等待
  外部 owner。Wayland 使用 `wl_data_device` 和非阻塞 pipe，读取同样由 `platform_poll`
  增量推进，最多缓存 16 MiB。
- 外部 X11/Wayland selection 的第一次 `Ctrl+V` 返回 `MY_RET_PENDING` 并由控件的 10 ms
  临时 timer 自动完成；无需用户再次按键。失焦或销毁会取消 timer。
- 旧有有界 `clipboard_get_text` 保留给兼容调用方；新的控件路径使用分配式接口。

### 平台对象生命周期

`platform_create()` 在所有后端进入原生 API 前校验非空、合法 UTF-8 标题、包含 NUL 在内不
超过 `PLATFORM_MAX_WINDOW_TITLE_BYTES`（4096 字节）、非零尺寸和统一的
`PLATFORM_MAX_WINDOW_DIMENSION` 上限。窗口对象为空或已经销毁时，查询接口返回确定的
零/基准值，控制接口无副作用；媒体查询失败时清零输出快照，分配型剪贴板查询先清空
输出指针。`test_platform_config` 与 `test_platform_null_safety` 覆盖通用契约，X11 和
Wayland runtime smoke 进一步覆盖真实原生对象的创建、句柄获取、事件轮询和销毁。
runtime smoke 在没有可用显示服务器/compositor 时返回 CTest 标准 skip，不把构建或
协议单测当作真实 runtime 通过。Win32 的 `WM_SETTINGCHANGE`、显示器、输入设备和
DPI 事件只让媒体快照失效并递增饱和代际；缺少 suggested `RECT` 的 `WM_DPICHANGED`
会安全忽略，不解引用无效消息参数。媒体快照查询仍在冷路径完成，缓存命中只复制固定
大小结构。

宿主 `Engine` 应以 `Engine engine = {0}` 开始，并检查 `engine_init()` 返回值；初始化失败
后可直接调用 `engine_shutdown()`，未初始化的 `engine_frame()` 会安全返回 `false`。活动
平台不允许通过重复 `engine_init()` 覆盖，避免泄漏原生窗口和 RHI 关联状态。

### 文本事件边界

所有平台的 commit/preedit/delete 事件先进入 `PlatformTextQueue`，再由 `BreakUI` 消费：

- `PlatformTextEvent` 为不超过 64 字节的常见文本保留内联存储，超出部分由事件独占
  `utf8_extra`；出队后所有权转移给调用方，调用方必须调用
  `platform_text_event_destroy()`。
- 单个 UTF-8 事件最多 16 MiB，队列 payload 最多 32 MiB、最多 4096 个事件；超出预算、
  分配失败或平台查询失败时丢弃该事件，不阻塞窗口线程。相邻 preedit 更新合并为最后一条，
  避免 IME 高频更新造成无效排队和内存增长。
- 队列是环形 FIFO，出队不搬移剩余事件；平台销毁时通过
  `platform_text_queue_destroy()` 释放未消费文本。新增平台消费者也必须遵守这套所有权规则。
- UTF-16 平台（Win32/Cocoa）按实际 UTF-8 输出计长，不因最坏情况 3/4 倍临时缓冲而拒绝
  大段 ASCII 文本；非法 surrogate 使用 U+FFFD 替换。

### BreakUI (`myui_break`)

应用通常使用：

```c
BreakUI *ui = break_ui_create();
break_ui_init(ui, platform, device, font_path, w, h);
break_ui_pump(ui);
bool skip = false;
cmd = break_ui_frame_begin(ui, w, h, &skip, NULL);
if (!skip && cmd != NULL) {
  break_ui_render(ui, cmd, w, h);
  rhi_frame_end(device);
  rhi_present(device);
}
my_window_t *win = break_ui_get_window(ui);
```

`break_ui_pump` 将 `InputState` 翻译为 myui 的 pointer/key/IME 事件；
设置 window manager 后通过 `my_window_manager_on_pal_event` 路由，支持模态对话框规则。

### RHI vgcanvas (`my_vgcanvas_break_rhi`)

- 统一输出 myui font-vertex 布局：`x,y,u,v,r,g,b,a`。
- `1024x1024` RGBA glyph atlas，仅在脏时上传 mip 0；可容纳完整中文页面的
  千级不同字形，避免滚动后因图集耗尽而丢字。
- GLES/OpenGL 与 Vulkan 的 direct-mapped glyph cache 均使用
  `(font_identity, codepoint, device_font_size)` 作为命中条件；切换字体后即使字符和字号
  相同，也会重新上传字形纹理，不会显示上一字体的字形。canvas 只借用 `my_font_t *`，
  应用必须保证字体存活到 canvas 销毁或不再使用该字体之后。
- solid/image 分别使用双缓冲动态 VBO（按 `rhi_frame_index` 选择）。
- 路径和圆角矩形由共享 `my_vggeometry` CPU 三角化。
- OpenGL 使用 `font.vert/frag` + `ui_img.vert/frag`。

BreakUI 的 AA 设置通过 `break_ui_set_antialias_level()` 进入事务边界。请求不会在
widget paint 回调中销毁或替换当前 FBO；canvas 只记录 pending level，BreakUI 在下一次
render 边界创建候选 `RHIOffscreenFBO`，创建成功后再激活并回收旧目标。候选创建失败时
旧目标、尺寸和当前质量保持不变。level `0` 使用 1x，level `2` 在设备同时支持 color/
depth sample count 与 resolve 时使用 2x；旧 RHI 创建 API 仍固定 1x。
如果在下一帧提交前恢复当前 active level，BreakUI 会撤销 pending target switch 而不
重建 target；非法 level 不会修改 pending 状态，避免旧请求被误执行。
- Vulkan 使用 `font_vk.vert/frag` + `ui_img_vk.vert/frag`。

可选 OpenType shaping 通过 `my_font_shape()` 和 `my_font_shape_ex()` 暴露为后端中立的
glyph run：每个 glyph 携带 font glyph id、UTF-8 byte cluster 和 26.6 fixed-point
advance/offset。`my_font_shape_ex()` 额外接收 direction、OpenType script tag、language
和有界 feature 字符串。只有启用 `MYUI_HARFBUZZ`、FreeType 与 HarfBuzz 均可用的直接
FreeType face 支持显式 shaping；bitmap、stb 以及不支持显式参数的旧 provider 返回
`MY_RET_NOT_SUPPORTED`，旧的无参数 shaping callback 仍可通过 `my_font_shape()` 工作。
公共入口拒绝空 feature 项、尾逗号和超过 32 项的 feature 列表，并通过无堆分配的
`my_font_shape_features_normalize()` 统一 tag 顺序、`+/-` 语法和重叠范围的最后声明覆盖；
规范后的列表由 provider、paragraph 所有权和 visual-boundary cache 共享。HarfBuzz 输入/输出
buffer allocation 失败会安全返回 `MY_RET_OOM`，不会向调用方返回半成品 glyph run。
`my_font_shape_support_query()` 提供 script/language system capability 查询；FreeType/HarfBuzz
读取 GSUB/GPOS 表，并对最多 32 个去重后的 requested feature tag 做有界存在性检查。每个 tag
只要在兼容的 GSUB 或 GPOS language system 中存在即可通过；缺失 tag 返回
`MY_FONT_SHAPE_UNSUPPORTED`，不会静默声称该 feature 已生效。字体链聚合各 face 结果，固定
容量 LRU 的键包含 script、language 和 canonical feature set，避免不同 feature 请求错误命中。
language cache key 额外进行有界 ASCII 大小写折叠，避免 `ZH-CN`/`zh-cn` 造成重复表扫描；
这不是完整 BCP-47 canonicalization，也不实现 locale alias 或 tailoring。
text-layout 的 glyph-run 与 visual-boundary cache 使用同一规则，但只保存归一化 key，
不改 paragraph/text-area 对外持有的原始 shaping 参数；key 复制失败时保持原缓存状态。

SA dictionary 回调的 `allow_before[0]` 是 run 起点而非内部边界，调用者对该槽位的修改
不会提交；只有 `1..count-1` 的内部边界在回调成功后写回。回调失败保持整个 run 的旧
边界数组，且 run 长度继续受 `MY_LINE_BREAK_MAX_DICTIONARY_CODEPOINTS` 限制。
bitmap、stb、FreeType 和字体链的 measure 宽度使用宽累加并在 `INT32_MAX` 饱和，避免
4 MiB 文本或极大字号造成 `int32_t` 回绕；正常路径仍为 O(n)、无额外堆分配。普通
`test_myui_font` 现为 `51/51`。STB glyph cache 在驱逐旧 entry 前完成位图复制；OOM
或尺寸溢出只失败当前请求，不污染旧 cache entry，回归由
`stb_glyph_oom_does_not_poison_cache` 覆盖。FreeType 使用同等的提交前缓存契约。
STB 的 `my_font_stb_create_ex()` 与字体链支持显式 TrueType Collection face index；普通
TTF 的非零 index 会明确拒绝，避免无意加载 face 0。
STB 文件读取还受 `MY_FONT_STB_MAX_FILE_BYTES`（64 MiB）限制，超限文件在 payload
分配前拒绝；空文件和定位失败同样安全返回失败。构造期还会验证 sfnt/TTC 头、face
目录和每张表的 payload 范围；截断 TTC 或越界表偏移会在第三方解析器读取前拒绝。
该校验覆盖 STB 实际使用的固定字段、cmap format 4 数组和索引范围，并对 TrueType
复合 glyph 做组件索引、参数边界和组件图无环性检查；组件图使用显式帧栈按 O(V+E)
遍历，避免深组件图返回父节点后重复扫描；但不覆盖完整表内 OpenType/CFF
子结构。CFF 构造额外检查 header/INDEX 边界，并将 STB CFF buffer 限制在真实表长度；
CFF `CharStrings` 数量必须匹配 `maxp.numGlyphs`，每个对象的 INDEX payload 必须非空；
CID 的 FDArray 会逐项验证 Font DICT 的 Private size/offset、Subrs 相对偏移和 Subr INDEX，
FDSelect 偏移也会保存供运行期选择逻辑使用。CFF2/COLRv1 等不支持格式仍按显式失败处理，
完整 charstring/DICT 语义仍不在此边界校验承诺内；CFF1 DICT 的 vendored STB 不支持数字
编码会在构造期拒绝，避免进入断言路径。
Type 2 CharStrings、Global Subr 和 Local Subr 另外执行轻量有界词法扫描，验证数字、
转义 opcode、hint mask 字节和保留 opcode；主字形只在栈上下文可证明时校验 subr 调用操作数，
调用 Subr 后对栈和 hint 状态采用未知标记，避免误拒绝合法的调用方操作数。它只位于字体构造冷路径，
不重复实现完整 interpreter；未知 Subr 栈部分只验证 token 字节宽度。CFF DICT 的已知操作符还会
校验固定/偶数操作数基数和尾部悬空操作数，但仍不宣称完成全部 charstring/DICT 语义。

required LangSys feature 由 provider 读取并具有最高优先级：用户的 `-tag`/`tag=0` 不会关闭
required feature，普通 feature 的显式关闭仍然有效；隐式 script 也按 HarfBuzz buffer 推断的
script 检查 required feature。明确不支持时按同 script 默认 language、默认 script、legacy
provider 逐级回退，未知状态保持最佳努力。该策略不改变 `my_font_shape_params_t` ABI，也不
把 HarfBuzz 类型泄漏到公共接口；FreeType 诊断入口仅返回无平台类型的 tag/count。

所有上层文本入口共用严格 UTF-8 解码：overlong、surrogate、超范围码点、非法 continuation
和截断序列均转换为 `U+FFFD`，并只消费一个坏字节后重新同步。该路径不分配内存，避免恶意
输入通过布局、字体链或后端 provider 触发越界读取；合法 UTF-8 的解码复杂度保持 O(n)。
当前 Break RHI、GLES、Vulkan 和 soft canvas 的纯 LTR 路径已通过独立
`my_font_get_glyph_id()` raster API 消费 glyph run；四个
后端的 glyph cache 均把 font pointer、glyph/codepoint 数值、key 类型和字号作为键，避免把
glyph id 当作 Unicode codepoint 或发生缓存串线。shaping 失败时回退旧 codepoint 路径。
paragraph 的 `my_text_layout_shape_ex()` 会在未指定 script 时按 Unicode Script 属性拆分
连续 script segment，并把 language/features 透传到每个 segment；显式 script 则保持单一
shaping run。启用 `MYUI_BIDI` 时直接复用仓库内 SheenBidi Unicode 17 primary Script 数据，
并使用仓库内由 Unicode 17.0.0 `ScriptExtensions.txt` 生成的静态扩展表；关闭
`MYUI_BIDI` 时也复用该表，仅 primary Script 使用无额外依赖的常用 block fallback。扩展字符
通过前序/后序候选匹配解析，表查找为 O(log R)，不访问运行环境文件且不产生额外分配。RTL
segment 按 visual run 顺序提交，失败时整个 result 事务回滚。Hiragana、Katakana、半角 Kana
与常见长音符已纳入相邻 run 处理；该映射仍不覆盖完整 OpenType 语义；基本区与补充区
variation selector 已按 Inherited 处理；FreeType/HarfBuzz 还会移除未被 shaping 消费的 VS15/VS16
输出，保持 selector 附着于基字符且不产生独立 advance，并已用真实 Noto CJK IVS 验证变体 glyph
选择；完整 variation-selector 语义、language-specific
feature 选择、
每个 layout 还提供固定 4 槽、按字体/字号/方向/script/language/canonical features 区分的
glyph-run LRU；缓存写入失败不影响当前结果，布局销毁时释放缓存。跨 face 的完整 OpenType
shaping 仍未实现，缓存使用期间字体及其 face 身份必须保持有效。
非 shaping fallback 已统一让 variation selector 具有零 advance、无独立 bitmap，并将其留在前一
字体 face 的 shaping segment 中。OpenType provider 通过 HarfBuzz 选择字体支持的 variation glyph，
并清理未消费的 VS15/VS16；ZWJ sequence 仍由 HarfBuzz 正常组合。跨字体 variation 覆盖和
locale-specific emoji/text presentation 仍需要后续完整 OpenType 支持。
resolver 已区分 `Thai` 与 `Thaa` tag，并让 Common/Inherited 字符优先匹配前序
Script_Extensions 候选，再匹配后序候选，最后按邻接 script 归属；普通 Common/Inherited
字符仍优先归入前序 script（段首才使用后继 script），组合附加符号因此不会在相邻 script
边界被拆开；BiDi 构建的 primary Script 查询来自 SheenBidi Unicode 17 数据。扩展表生成入口为
`tools/generate_myui_script_extensions.sh`，构建不依赖 UCD 文件存在。
paragraph 可通过 `my_text_paragraph_process_ex()` 使用同一组参数进行换行测量；language/
features 会复制到 paragraph 自身，`my_text_paragraph_shape_params()` 返回只读的受管参数，
因此调用方释放或修改原字符串不会改变后续排版。旧的
`my_text_paragraph_process()` 保持默认参数和原有快速路径。
需要处理非 NUL-terminated 数据时使用 `my_text_paragraph_process_n_ex()`；该入口只读取
声明的 byte slice，拒绝嵌入 NUL，并由 paragraph 自己建立稳定副本。text area wrap 使用
该入口直接处理物理行范围，行 shaping 仅在 paragraph 自有副本中暂时隔离行尾 NUL，防止
provider 读取相邻物理行。
`my_text_paragraph_line_layout()` 按需为逻辑换行段建立 paragraph-owned visual layout；
重复查询在命中期间复用同一指针，固定 4 槽 LRU 满载后淘汰最久未使用的行。单行构建失败
不会留下半成品，后续可安全重试；paragraph 销毁时释放全部已建立的 line layouts，避免
widget 为每次命中测试重复重建 RTL 映射。
字体 shaping 入口本身也限制输入为 `MY_FONT_SHAPE_MAX_BYTES`（4 MiB），在调用 provider 或
HarfBuzz 前完成有界扫描；provider 输出另外受 `MY_FONT_SHAPE_MAX_GLYPHS` 有界限制，公共
入口、字体链和 text-layout 聚合层在复制前检查 `count`，超限时释放候选结果并返回失败，
不会把超大结果交给绘制、命中测试或 glyph-run cache。layout/paragraph 入口使用各自同等
大小的前置预算。
字体链的 `shape_ex` vtable 直调路径同样清零结果并执行上述文本/参数校验，成功结果保留
RTL 方向；这避免绕过 `my_font_shape_ex()` 包装后复用旧 glyph-run。该边界由
`font_chain_direct_shape_provider_initializes_result` 回归覆盖，但跨 face 的上下文 token
shaping 仍不在当前契约内。
字体链的 shaping face 选择以扩展 grapheme cluster 为最小单位：Unicode 17 combining mark、
variation selector、emoji modifier、tag 与 ZWJ sequence 会优先落在同一可覆盖 face，之后才
合并为连续 face run 并交给 HarfBuzz。这样 fallback 不会把基字符和附着 mark/emoji sequence
拆成独立 shaping 请求；cluster 检查仅发生在 shaping 冷路径，正常绘制不增加分配或后端分支。
它不实现跨 face 的 GSUB/GPOS 上下文协商，无法由单一 face 覆盖的 cluster 仍按首个基字符
的安全 fallback 规则处理。
同一 cluster 的度量也沿选定 face 处理其组成 codepoint，避免 fallback mark 被重复计宽；
FreeType/STB 的 direct `measure` vtable 入口同样执行 `MY_FONT_SHAPE_MAX_BYTES` 有界扫描，
ZWNJ 作为 cluster 控制符保留在同一 face 选择范围内。以上检查均位于冷路径，不增加逐帧
渲染锁、分配或后端调用。
同一 cluster 的度量也沿选定 face 处理其组成 codepoint，避免链路中 fallback mark 被重复
加到总宽度；该兼容度量路径仍保持无堆分配，完整 OpenType cluster advance 仍以 shaping
provider 的 glyph run 为准。

### Canvas 能力契约

控件只能通过 `my_vgcanvas.h` 的公共接口配置 canvas，不得把某个后端的
`my_vgcanvas_*_set_*` 函数用于通用绘制路径。窗口在创建、切换 GPU 后端和注入
canvas 时统一应用 DPI scale 与当前字体，因此软件、GLES/OpenGL、Vulkan 和嵌入式
Break RHI 路径不会再因创建分支不同而出现字号或坐标不一致。

| 能力 | 软件 | GLES/OpenGL | Vulkan | Break RHI |
|------|------|-------------|--------|-----------|
| `my_vgcanvas_set_scale` | 支持 | 支持 | 支持 | 支持 |
| `my_vgcanvas_set_antialias_level` | 覆盖率 AA（0-2） | 0/非 0 映射 MSAA | `MY_RET_NOT_SUPPORTED` | `MY_RET_NOT_SUPPORTED` |
| `my_vgcanvas_set_scale_filter` | nearest/bilinear | nearest/bilinear | nearest/bilinear | nearest/bilinear |

### Offscreen target 与 MSAA 边界

Break RHI 的 `RHIOffscreenFBODesc` 是跨后端 target 描述，不暴露 OpenGL/Vulkan 类型。
`sample_count == 0` 表示兼容旧行为的 `1x`；旧的 `rhi_offscreen_fbo_create*()` API
始终创建 `1x`，避免升级后改变已有后处理链路。descriptor 在进入后端前会检查尺寸、
格式、power-of-two sample count、颜色样本能力及 resolve 能力，非法请求返回空 target。

OpenGL 的 `2x+` target 使用 multisample color/depth renderbuffer，另建单采样 color/depth
texture 供采样；离开 target 或切换 target 时执行一次 resolve，避免绘制过程中反复 resolve。
`RHIOffscreenFBO.color_tex` 和 `depth_tex` 始终指向可采样的单采样结果。

Vulkan 的 `2x+` target 使用 multisample color/depth image 和单采样 color/depth resolve
image；render pass 通过 depth-stencil resolve 完成 resolve，pipeline 按颜色格式和 sample
count 建立兼容 variant。`color_tex/depth_tex` 始终指向可采样的单采样 resolve 结果，MSAA
attachment 由 FBO 内部持有。设备必须同时支持 color/depth sample count 和至少一种 depth
resolve mode，否则返回空 target，不静默降级。旧的 `rhi_offscreen_fbo_create*()` API 仍固定
创建 `1x`；Vulkan shadow/MRT pipeline 的 `sample_count > 1` 当前明确拒绝。

图像过滤是 canvas 状态的一部分，默认值为 bilinear。GLES/OpenGL 的图像纹理缓存键为
`(rgba 指针, width, height, filter)`，避免同一位图在两种过滤模式间错误复用；没有扩展
回调的旧 GL 适配仍回退到原始 RGBA 上传接口。Vulkan 使用共享的 linear/nearest sampler，
并把 sampler 写入对应的 descriptor；字形 atlas 始终使用 linear。Break RHI 同样创建两种
sampler，并按 `(texture, sampler)` 划分 image batch，避免每个图像 quad 创建资源。公共
`my_vgcanvas_draw_image()` 调用方必须在缓存可能命中期间保持 bitmap 内容不变；需要更新
像素时应提供新的稳定 buffer identity，或主动让 canvas 生命周期结束。`my_image` 解码
缓存满足该生命周期要求。`ztpool` 的 PNG 分享导出是显式离屏软件渲染任务，因而保留
`my_vgcanvas_soft_create` 依赖；它不参与窗口的后端选择，也不会把软件 canvas 传给
GPU 控件路径。

### 能力盘点与阶段计划

本轮已经打通并由 TDD 锁定的能力包括：固定列 Grid 布局、文本编辑缓冲区容量倍增、
软件/GLES/OpenGL/Vulkan/Break RHI 的 nearest/bilinear 图像过滤、Mono 目标的 4x4
ordered dithering、MVVM 的 items 和 condition 绑定，以及文本布局的 UBA L4 镜像、
Arabic joining 和 mandatory Lam-Alef 覆盖映射。布局参数解析同时拒绝负数、非有限数和
超出 `int32_t`/百分比范围的输入；Grid、framebuffer stride、UTF-32/UTF-8 缓冲区和文本
逻辑/视觉索引的乘法与边界均经过溢出保护。CSS 已支持 universal selector、多 class
selector、typed direct-child selector，以及按 selector specificity 和 source order 的
cascade；普通规则在 hover/pressed/disabled 查询时保留 normal-slot 的 specificity。数值
解析拒绝孤立符号、非有限值和超出 `int32_t` 的整数，不会把恶意输入转换成未定义的资源
尺寸或颜色值。软件开放 contour fill 会按 fill 语义自动闭合，开放 stroke 仍保留端点语义。
结构错误会拒绝加载，不会静默生成错误主题。

X11 媒体能力使用初始化快照和 `XI_HierarchyChanged` 冷路径刷新：能力读取为 O(1) 快照
复制，设备枚举只在初始化或设备层级变化时发生；XInput2 不可用时回退核心指针语义。
该设计避免 CSS 媒体刷新或绘制路径重复触发 X11 协议请求，同时通过媒体代际通知宿主
调用窗口级样式刷新。X11 runtime 测试目标显式继承 XInput2 配置宏，增强设备能力断言
不会因 target 私有宏传播而被静默裁掉。

仍未实现或明确保留为后续阶段的能力如下：

| 范围 | 当前边界 | 后续方案 |
|------|----------|----------|
| GPU AA | Break RHI 的 `RHIOffscreenFBODesc` 已支持按设备能力创建真实 2x+ target；BreakUI 已接入窗口级 pending/事务切换和取消语义；Vulkan/GL 的真实窗口 runtime 协商仍缺本机矩阵 | 在各平台 runner 完成 target 创建/提交/resize 的 runtime smoke；失败时保持旧 target，不静默改变质量 |
| 复杂 RTL | 已支持单段落 UBA 重排、L4 镜像、Arabic joining、mandatory Lam-Alef、有限 script segment、paragraph shaping 参数和 cluster-safe bidi glyph-run；Common 标点与 variation selector 基础归类已修正；OpenType provider 会清理未消费的 VS15/VS16 并保留 ZWJ 组合；GSUB/GPOS language-system、requested feature 存在性、required feature 不可关闭优先级及 Noto Arabic/Hebrew RTL glyph/cluster golden 已接入；完整 UAX#24 语义、多段落增量 rebreaking、跨字体 token shaping 和完整 RTL GSUB corpus 仍未实现 | 增加完整 script resolution、跨字体 variation 覆盖、language system、段落级增量 mapping 和 line-break model，继续以多字体 golden 字形/视觉顺序测试锁定契约 |
| 编辑器 | 代码折叠（支持严格包含嵌套）、有界 YAML 折叠快照、行号栏、wrap 增量缓存、增量 lexer 和受限 token 分段着色已实现；完整 RTL token shaping 仍未实现 | 增加版本字段和 bidi shaping，保持单帧预算，避免大文档全文扫描 |
| 图像 | Mono 使用固定成本 4x4 ordered dithering；误差扩散和更高位深量化未实现 | 保持当前有界、可预测的 dither 路径；仅在实测收益明确时增加其他量化策略 |
| Present | 已实现后端无关的 `SKIP/PARTIAL/FULL` 决策和有界 damage 帧接口；Wayland EGL 在 buffer-age、保留 surface 和 damage-present 能力同时满足时执行局部 present；Vulkan、X11、Win32、macOS 仍安全全屏 | 为 Wayland 增加真实 compositor smoke；分别验证 X11/Win32/macOS 的 retained-buffer 语义，并在 Vulkan WSI 具备明确内容保留保证时再评估局部路径 |
| Vulkan/GL readback | `rhi_screenshot()` 提供统一 RGBA8 窗口/默认 framebuffer 读回；调用方必须提供目标字节数，区域越界、零尺寸、乘法溢出或容量不足均失败 | Vulkan 使用 swapchain `TRANSFER_SRC`、一次性 staging buffer 与完成等待；GL 使用受边界校验的 `glReadPixels`。该同步 API 仅用于诊断/截图，不用于每帧渲染 |
| CSS/YAML UI | CSS 支持最多 4 级祖先路径、descendant/typed `>` 链、祖先 type/class/id、specificity/source order、解析期条件媒体、有界 width/height range、显式设备能力位掩码，以及受限 `@scope` root/`to` 边界（含隐式 root、compound selector 和最多 4 项 selector list）；窗口保留媒体快照，宿主可在系统偏好/设备能力变化时通过 `my_window_refresh_media_style()` 或 `my_window_manager_refresh_media()` 仅对变化窗口事务重建样式，未变化时无主题分配；并提供只读 capability registry 与稳定错误码；完整 at-rule 语义仍未实现。YAML UI loader 已采用类型化 schema，支持逐 factory 属性/事件契约、有限 schema version、最多 16 步连续 migration chain、动态 owned schema，并提供 loader 级 capability registry/error code；冻结后支持低频 runtime factory/schema 新增、替换和注销，失败事务不发布半成品，内建类型受保护 | 增加更细 schema 定位；补真实平台能力采集和 golden corpus，继续评估完整 at-rule 和 callback 代码卸载契约，同时保持解析边界与运行期回滚 |
| 平台 | Windows/macOS 已有基础本机 CI runtime，但仍缺完整 HiDPI/输入/IME/显示设备矩阵；未启用的 GLES/Vulkan/Wayland 组合仍缺少本机门禁 | 在对应 runner 扩展 build、窗口生命周期、HiDPI/输入/IME 和显示能力矩阵；缺失能力保持 unknown，不以默认值冒充 |

实施原则：先写跨后端契约测试，再实现各 backend adapter；所有候选 GPU 资源采用“创建、
验证、提交、激活、回收”的状态转换，失败保留旧资源。当前通用事务实现位于
`engine/src/myui/myr/my_vgcanvas_quality_transaction.h` 和
`engine/src/myui/myr/my_vgcanvas_quality_transaction.c`，其能力 mask 仅接受幂次样本数，
并把 resize 与 sample-count 放在同一次提交中。RHI 的 `rhi_device_get_capabilities()` 只读
返回设备能力，不能替代 target/render-pass 的兼容性验证。缓存键必须包含影响结果的状态，输入长度、
索引乘法和行列尺寸必须在分配前检查，绘制线程不等待外部平台协议。这样可把性能优化
（缓存、批处理、增量布局）限制在不牺牲安全和可恢复性的范围内。

所有 UI 几何动态数组在容量倍增和元素字节数乘法前执行 `size_t` 上界检查；soft、GLES2、
Vulkan、Break RHI 及共享 `my_vggeometry` 使用同一失败语义。正常路径仍按倍增增长，溢出
路径不调用 allocator，也不修改旧数组和旧状态。

公共 `my_vgcanvas_*` inline API 在进入任一 backend vtable 前验证对象、vtable 和槽位：空
对象返回 `MY_RET_INVALID_PARAMS`，有效对象缺失槽位返回 `MY_RET_NOT_SUPPORTED`。这使 soft、
GLES2、Vulkan、Break RHI 以及自定义适配器共享一致的失败语义，并避免错误路径直接调用空
函数指针；质量能力状态仍只在后端提交成功后更新。

PAL 的公共 inline wrapper 也会在进入窗口、GL、主循环或平台 vtable 前验证对象和槽位：
空对象或缺失必选槽位返回 `MY_RET_INVALID_PARAMS`，可选能力缺失返回
`MY_RET_NOT_SUPPORTED` 或安全默认值（例如 Vulkan surface 为 `NULL`、scale 为 `1.0`）。
该检查只增加固定指针判断，不分配、不加锁；没有改变 frozen vtable 布局，旧的自定义
跨平台 PAL 适配器保持 ABI 兼容。TDD `test_myui_break_pal` 覆盖空对象和部分 vtable，
当前为 **6/6**。

同一入口还拒绝 NaN/Inf 坐标、非正 line width 和负/非有限圆角半径；状态 setter 或绘制调用
失败时不写入后端 state。正常输入只做固定次数的 `isfinite` 检查，不引入分配或逐像素扫描。

通用 `my_darray` 也遵循同一容量契约：倍增回绕、元素字节数溢出和 `size + 1` 回绕均在
写入前返回 `MY_RET_OOM`，避免配置、窗口管理器、主题和 MVVM 等共享容器在极端输入下破坏
其旧状态。该保护不改变常规追加的 O(1) 摊销复杂度，也不在热路径增加逐元素检查。

本轮定向 TDD 门禁为：`test_rhi_capabilities`（2/2）、`test_myui_css`（103/103）、
`test_myui_loader`（85/85）、
`test_myui_text_layout`（86/86）、`test_myui_window_manager`（113/113）、
`test_myui_mvvm`（10/10）、
`test_myui_vgcanvas_backend`（32/32）和 `test_break_ui_damage`（24/24）。其中 CSS 用例覆盖
universal、多 class、direct-child、specificity fallback、数值边界
和 malformed selector；文本用例覆盖 RTL visual mapping、Lam-Alef logical span 和选区；
backend 用例覆盖缩放、过滤、字体缓存隔离、开放 contour fill、Mono dither、framebuffer
尺寸/stride 溢出、能力查询、AA 支持/拒绝、失败回滚和幂等请求；damage 用例覆盖共享
surface 的结构/布局失效、失败回滚和逻辑到 drawable scissor 的向外取整与裁剪。
窗口 GPU 切换还会以 PAL 已协商的 multisample 状态覆盖 GL 查询结果，避免把驱动默认值
误当成 surface 能力。

Floating widget 的绘制与命中语义也分离：`floating=true` 且没有 `on_event` 的普通控件
是 paint-only overlay，不会吞掉其下方控件的 pointer hit-test；带 `on_event` 的浮层仍按
顶层交互控件处理。普通 `my_widget_create()` 控件允许保持 NULL vtable。

### 窗口状态机与尺寸边界

窗口把布局和渲染尺寸分成两个明确的单位：

- `my_pal_window_get_size()`、`MY_EVENT_RESIZE` 和 widget 矩形使用逻辑像素。
- `my_pal_gl_get_size()` 返回 GPU drawable 的物理像素，GLES viewport、Vulkan
  swapchain 和 canvas framebuffer resize 只能使用这个单位。
- 当 PAL 没有独立 drawable 查询时，窗口按 `logical_size * my_pal_get_scale_factor()`
  回退；实现端应尽量提供真实 drawable 查询，避免非整数缩放或 compositor 调整时误差。
- 平台层的等价 API 是 `platform_get_logical_size()`、
  `platform_get_drawable_size()`、`platform_get_content_scale()` 和
  `platform_get_input_scale()`；RHI 调用点只接收 drawable 尺寸，UI/PAL 调用点只接收
  logical 尺寸。
- 软件 canvas 绑定 PAL LCD 的物理尺寸。窗口自有软件 canvas 在 surface resize 时释放，
  下一次绘制按新 LCD 懒创建；注入式 canvas 不由窗口销毁，注入方必须先调整自己的目标，
  再发送逻辑尺寸 resize。
- 内容缩放可在逻辑尺寸和 drawable 尺寸均未变化时独立改变（例如跨 DPI 显示器或分数
  缩放 rounding）。`my_window_refresh_scale()` 是唯一的 canvas 重配入口：它更新 canvas
  scale、保持 widget 坐标不变并使整个逻辑窗口失效。`BreakUI` 在每帧收集 damage 前通过
  window manager 批量调用它；因此注入式 RHI canvas 先完成 drawable target resize，再由
  window 负责其 scale 和字体状态，不能由桥接层直接设置 canvas scale。随后直接录制
  dirty window，不重复查询平台 scale。
- widget 结构与几何变更必须通过公共 API 进入 root dirty sink：`add_child/remove_child`、
  `set_visible`、`set_rect`、layout params 和 layouter 变更都会请求布局并产生 damage；
  `set_rect` 同时覆盖旧位置和新位置。布局器与 `on_layout` 回调使用
  `my_widget_set_layout_rect()`，避免在布局过程中递归请求同一布局器，但仍保留旧/新区损伤。
- damage 在逐级转换为 root 坐标时会裁剪到每个祖先的可见 bounds，避免滚动内容或越界
  子控件扩大无效重录区域。删除父控件会先清空 retained child 的弱 `parent`，窗口 removal
  hook 同时清理 dispatcher 的 grab/focus/hover 和动画引用，防止结构变化留下悬空指针；
  移除 focus 时发出 `blur` 以关闭 IME，移除 hover 时恢复默认 cursor。
- 内容测量可能触发第二次布局（例如 auto-size 影响父布局）。`my_window_prepare_layout()`
  在最多 8 次有界 pass 内收敛，只遍历 pending 子树；`BreakUI` 必须在跨窗口收集 damage
  之前对全部逻辑窗口调用它，确保 layout 新增的 damage 也参与 overlap expansion。

绘制回调允许关闭、打开窗口或修改 widget 树。窗口管理器在每个绘制 tick 和每个共享
surface frame 开始时建立带强引用的窗口栈快照；绘制期间若 `windows_epoch` 变化，则停止
当前帧、恢复本帧 dirty 并让下一帧从 live 栈重新完整合成。widget 绘制同样快照当前父节点
的 child 引用，只绘制仍属于该父节点的 child；回调新加入的 child 延迟到下一帧，已移除的
child 不会在当前帧继续访问。这样既避免 UAF/跳过窗口，也避免 live 数组变更造成的越界。

`my_window_enable_gpu()` 的状态转换遵循以下规则：

1. 初始状态是 `MY_GPU_SOFT`，请求同一已完整安装的后端是幂等操作。
2. 先完整创建并验证候选 canvas/context，再一次性提交 active state；候选失败时旧
   后端保持可用。提交时释放旧 canvas 必须早于旧 GL context，确保 GPU 资源销毁时
   context 仍然有效。
3. 后端创建失败不会修改 active state，也不会把失败伪装成成功；`MY_GPU_AUTO` 只在
   合法枚举范围内按 GLES2、OpenGL、Vulkan 顺序尝试，全部失败时保留软件状态。
4. BreakUI 使用共享的 Break RHI canvas，窗口只借用它；`break_ui_render()` 负责重建
   RHI surface、resize canvas，再把逻辑 resize 事件交给 window manager。

端口实现不得把“窗口事件尺寸”“RHI framebuffer 尺寸”和“widget 布局尺寸”复用为一个
无单位的变量。新增 PAL 时应同时覆盖 scale=1 和 HiDPI resize，并验证首帧 viewport、
scissor、swapchain extent 与实际 drawable 一致。

### 平台与渲染后端矩阵

| 平台 | OpenGL 句柄 | Vulkan 句柄 | 文本/剪贴板路径 |
|------|-------------|-------------|-----------------|
| X11 | X11 `Window` + `Display` | X11 `Window` + `Display` | XIM、UTF-8、INCR |
| Wayland | `wl_egl_window` + `wl_display` | `wl_surface` + `wl_display` | `text-input-v3`、非阻塞 pipe |
| Win32 | `HWND` + `HINSTANCE` | `HWND` + `HINSTANCE` | IMM32、UTF-16 clipboard |
| Cocoa | `CAMetalLayer` | `CAMetalLayer` | `NSTextInputClient`、pasteboard |

`platform_window_native()` 表示 OpenGL/EGL 目标，`platform_surface_native()` 表示
Vulkan WSI 目标；应用不得仅凭“都是窗口句柄”互换这两个接口。

Wayland 在 `wl_surface.enter/leave` 中跟踪窗口实际覆盖的 output，选择其中最大的
整数 fallback scale。若 compositor 同时提供 `wp_fractional_scale_v1` 和 `wp_viewporter`，
则按 `preferred_scale / 120` 创建物理 backing buffer，保持
`wl_surface_set_buffer_scale(1)`，并用 `wp_viewport.set_destination()` 映射回逻辑尺寸；
`wl_egl_window`、Vulkan swapchain 和 `platform_get_drawable_size()` 都使用同一套半舍入
物理尺寸。协议不可用时仍使用整数 buffer scale，窗口跨显示器时不会提交被 compositor
放大的低分辨率缓冲。若 fractional-scale 或 viewporter global 在运行中撤销，平台会先
销毁其关联对象并原子回退到整数 scale；client-side Xcursor 则使用内容缩放的向上取整
buffer scale，避免 125%/150% 下由 compositor 放大较低分辨率光标。
macOS 在 resize 与 backing scale 变化时同时更新 `CAMetalLayer.contentsScale` 和
`drawableSize`，后者始终是 `view.bounds * backingScaleFactor` 的物理像素。

X11 通过 RandR topology 事件和每次 `ConfigureNotify` 的 root 坐标重选活动输出：最大
覆盖面积优先，无覆盖时选择窗口中心最近的输出，面积/距离相同时优先 primary 输出。新的
DPI/scale 会在后续 Bridge frame 由窗口 scale 刷新契约传递给 canvas；因此拖动窗口跨
不同 DPI 的 X11 显示器不会继续使用启动显示器的缩放。

## 性能取舍

- **CPU tessellate + 动态 VBO**：避免每帧切换大量 pipeline；GL/VK 行为一致，易调试。
- **字体隔离的字形缓存 + 单 1024px atlas**：减少 texture bind；图集仅新增字形时上传，
  direct-mapped cache 额外隔离字体身份，避免字体切换后的错误复用；容量覆盖当前中文页面
  的千级不同字形，图像按缓存 key 复用。
- **双缓冲 VBO**：与 RHI in-flight frame 对应，避免 CPU/GPU 写冲突。
- **MVVM 列表增量刷新**：`items_changed` 原地更新 `list_view` adapter，保留滚动位置和
  行池；只有模板切换才重新安装 adapter，避免行情等高频数据刷新跳回列表顶部。
- **MVVM items 事务**：items 属性必须是数组指针或显式 `MY_VALUE_NONE`；错误类型不会
  丢弃当前数组监听或视图，空值才会提交空列表。新数组先取得引用、订阅并完成目标重建，
  成功后才替换旧数组；模板不存在时在清理目标前返回错误。批量 `props` 通知会重新同步
  data、items 和 condition 绑定。
- **MVVM 上下文切换**：更换 ViewModel 时会同时解除并重新订阅 data、items 和 condition
  规则；旧模型不再驱动当前界面，列表会按新数据规模裁剪保留的滚动位置。
- **统一 canvas 配置**：窗口的 DPI scale 与字体配置在安装、后端切换和动态 scale 刷新时
  走同一入口，覆盖软渲染、GL、Vulkan 和 Break RHI 注入路径，避免后端创建分支的状态漂移。
- **stb 实现共享**：`stb_truetype_impl.c`、`stb_image_impl.c`、
  `stb_image_write_impl.c` 全局单实现，避免重复符号。
- **共享表面 damage 合成**：逻辑窗口按 dirty rect 重录到一个 offscreen surface，
  布局先有界收敛，再统一收集并扩展重叠窗口 damage；合成阶段只提交一次全屏纹理 draw，
  dialog 开关不需要创建额外 OS surface。窗口 dirty 在 canvas 创建、begin/end frame
  和逐窗口录制成功前不会被不可逆消费；任一窗口或共享帧失败时恢复所有快照，并让下一帧
  重新覆盖整个逻辑窗口栈，避免 retained surface 留下半帧结果。
- **增量布局路径**：`need_layout` 表示当前 widget 需要运行 measure/layouter/on_layout，
  `subtree_need_layout` 只标记后代路径；窗口帧不会因一个深层 child 变化而遍历无关兄弟子树。
- **固定列 Grid**：可见、非 floating 子项按行主序执行线性布局阶段；行高取该行最大
  子项高度，列宽均分并把余数从左到右分配。行高缓存按需增长，稳态帧不重复分配子项临时数组。
- **非阻塞选择传输**：X11/Wayland 的 clipboard 协议只在事件循环推进，绝不在 render
  frame 等待外部进程；大文本粘贴也维持同一帧时间预算。
- **有界输入背压**：IME/剪贴板输入均有明确的 16 MiB 单文本上限和有限队列预算，
  将异常输入的最坏内存成本限制在可控范围，同时不阻塞渲染线程。

## IME 状态

| 平台 | OS/图形后端 | IME | Cursor/窗口 | Clipboard |
|------|-------------|-----|-------------|-----------|
| X11 | OpenGL、Vulkan | XIM + `Xutf8LookupString`；无 XIC 时仍保留 enabled 状态 | Arrow/Text/Hand；EWMH native move | UTF-8、`INCR`、异步读取 |
| Wayland | EGL OpenGL、Vulkan | `text-input-v3`（compositor 提供时） | cursor-shape-v1 或 Xcursor fallback；CSD + `xdg_toplevel_move` | `wl_data_device`、异步 pipe |
| Windows | WGL OpenGL、Vulkan | IMM32 `WM_IME_*` | Win32 cursor + caption drag | `CF_UNICODETEXT` |
| macOS | MoltenVK/Vulkan | `NSTextInputClient` | Cocoa cursor rect + native drag | `NSPasteboard` |

Wayland 的 `text-input-v3` 和 cursor-shape 均为可选协议：缺失时普通键盘提交和
Xcursor theme fallback 仍可工作。macOS 构建使用 Cocoa `CAMetalLayer` 提供 MoltenVK
surface；它不是独立 Metal RHI。

## 验证

当前验证项：

- X11 OpenGL/Vulkan、Wayland OpenGL/Vulkan 均严格构建 `dxx_break`；四个 Linux 后端
  均完成 8 秒窗口启动烟测且无崩溃。
- 全量 `ENGINE_BUILD_TESTS=ON` 构建通过，`ctest -LE graphics` 为 `53/53`，且是 CI
  门禁。
- `test_break_ui_input`、`test_break_ui_damage`、`test_myui_vggeometry`、
  `test_myui_window_manager`、`test_myui_break_pal`、`test_myui_mvvm`、`test_imgui_compat`、
  `test_myui_font` 通过；`test_myui_font` 验证 UTF-8 中文码点、TTC 简体中文字面和
  非空字形覆盖；`test_myui_mvvm` 验证大列表数据变更不重置滚动或扩大行池，并验证
  ViewModel 切换后 items/condition 不保留旧 listener。
  window-manager 用例覆盖超过旧 4 KiB 限制的完整 clipboard paste，以及注入 canvas 的
  HiDPI scale 继承及不伴随 resize 的动态 scale 刷新；`test_monitor_selection` 覆盖 X11
  跨输出的最大面积、最近输出和 primary tie-break 选择；`test_myui_vgcanvas_backend` 覆盖公共 scale/AA/filter 能力边界和
  GLES 图像坐标缩放与物理 drawable resize；`test_wayland` 覆盖跨 output 时的最大
  buffer scale 选择、fractional 125%/150% rounding、cursor backing scale 和 global/output
  移除后的安全回退。`test_break_ui_damage` 额外覆盖结构树增删、重复挂载/环拒绝、移动和
  layout params 的旧/新区 damage、布局二次收敛、clean sibling 跳过，以及父销毁后的 child
  弱引用脱离；`test_myui_window_manager` 覆盖 focus/IME、hover/cursor 和 pointer grab
  在 subtree 移除后的恢复，并验证事件处理器自移除后不会继续向父节点冒泡；共享 surface
  用例还验证 pointer 命中非 modal 底层窗口后，
  key/IME 继续路由到该窗口，窗口关闭后安全回退到顶层窗口。

窗口所有权约定：`my_window_manager_open()` 增加 manager 对 `my_window_t` 的独立引用，
调用方必须释放创建时持有的窗口引用；`my_window_widget()` 无论是否 CSD 都只返回借用
指针，不能对它执行 `unref`。这样 CSD 内容容器不会产生隐藏的额外引用，窗口关闭、
BreakUI shutdown 和 dialog 生命周期保持同一套释放规则。

## 架构边界与后续风险

- 共享 offscreen surface 会按逻辑窗口 dirty rect 重录；Wayland EGL 在内容保留和
  damage-present 契约满足时，最终 composite 使用有效 damage scissor 并提交局部区域。
  其他后端仍执行安全全屏 composite，窗口数量增加时合成带宽按整面尺寸增长；默认
  swapchain 没有保留 backbuffer/平台 partial-present 契约时，直接启用 scissor 会丢失
  未损伤区域。
- Wayland 当前固定使用 CSD，不协商 `xdg-decoration`；这是跨 compositor 行为一致性的
  取舍，代价是 title bar 和拖动逻辑由 myui 维护。
- 分数缩放依赖 compositor 同时支持 `wp_fractional_scale_v1` 与 `wp_viewporter`；旧
  compositor 自动降级为整数 `wl_output.scale`。Wayland CI job 使用 Weston headless
  compositor 执行 `test_platform_wayland_runtime`，验证真实 proxy 创建、初始 configure、
  poll 和销毁；125%/150% fractional-scale 仍建议在目标桌面环境做一次实机烟测。
- Wayland 的 `wl_registry.global_remove` 会按子对象到 manager 的顺序清理
  `text-input-v3`、clipboard、relative-pointer、pointer-constraints、cursor-shape、
  fractional-scale/viewporter 和 xdg-output；`wl_seat` 撤销时同时清空输入状态，随后
  新 global 可按当前 surface/seat 状态懒重建。这样 compositor 重启或 seat 热插拔不会
  继续向失效 proxy 发送请求。
- Vulkan vgcanvas 的纹理缓存按 frame fence 延迟释放，以免销毁仍被提交命令引用的
  descriptor；退休队列扩容失败时会保留原缓存条目并跳过该次替换，避免用错误资源
  所有权换取一次绘制。
- Break PAL 不拥有 `Platform` 或 `RHIDevice`，也不拥有 OS 主循环；调用方必须保证它们在
  `BreakUI` 和 PAL 销毁之后才销毁。Windows/macOS 的原生运行时验证仍由 CI 和对应设备提供。
- 文本队列到达预算时采用丢弃而不是阻塞或无限增长；如果应用需要可靠的编辑协议，应在
  上层实现 backpressure/重试，而不是直接绕过 `PlatformTextQueue`。
- `my_vgcanvas` 的 AA 仍是可选能力而非最低公分母语义；调用者必须处理
  `MY_RET_NOT_SUPPORTED`。GLES/OpenGL 的 MSAA 开关依赖已创建 surface 的样本能力；BreakUI
  的 Break RHI canvas 通过 offscreen FBO 事务支持设备能力允许的 2x 切换，失败时保留旧
  target。独立 Vulkan vgcanvas 仍保留自己的能力边界。nearest/bilinear 图像过滤已成为软件、GLES/OpenGL、
  Vulkan 和 Break RHI 的共同能力；Arabic 基础 shaping、L4 mirror 和 Mono ordered dither
  已落地；有限 script/features shaping 契约已落地，完整 OpenType shaping、复杂多段落文本和局部 present 仍按阶段计划处理。

## 语法高亮热路径

`my_syntax_token_t` 同时提供 codepoint 和 UTF-8 byte 范围。lexer 在单次线性扫描中
记录 `start_byte/len_bytes`，text area 绘制 wrapped visual line 时直接按 byte 范围
裁剪 token，不再对每个 token 从物理行首重复扫描 UTF-8。完整 token 的绘制为 O(1)，
整行 lexer 仍为 O(line bytes + token count)，并保留原有 codepoint 坐标供选择、光标和
跨行状态传播使用。byte 范围来自同一行的受限源文本，不能跨行复用；所有超出 visual
line 的 token 都跳过绘制，避免越界访问。

## 换行位置索引

wrap 模式额外维护物理行到 visual line 首尾索引的有界缓存。光标、IME 和命中测试先
按物理行取得紧凑的 `[first, last]` 区间，再在该区间内二分；重复查询从全量 visual
line 的 O(log V) 缩小为 O(log segments-of-row)，通常为常数级。折叠、文本编辑、宽度
和字体变化通过同一 visual-line dirty 路径使缓存失效；缓存只覆盖当前物理行数，隐藏行
使用 `SIZE_MAX` 哨兵。缓存分配失败或查询隐藏行时保留原有全量二分回退，不影响行为，
也不依赖 GL、Vulkan、软件 canvas 或平台类型。

## RTL 交互布局缓存

text area 对 RTL visual line 保留固定 4 槽的 widget-owned LRU layout 缓存，键包含文本
revision、物理行、visual byte span、字体指针、字号和 shaping revision。键盘导航、垂直
导航、分页、绘制及 pointer hit-test 共享这些 layout；命中时不再复制行文本或重新分配
layout，miss 时优先使用空槽，否则淘汰最久未使用槽。新 layout 只有构建成功后才替换旧槽，
因此 OOM 不会破坏既有缓存。文本、字体、shaping 参数或 visual line 范围变化会失效全部
槽位；纯 LTR 仍走零 layout 的快速路径，不依赖任何渲染后端。

## RTL 视觉宽度缓存

`my_text_layout` 对调用者持有的 layout 按字体指针和字号缓存 visual boundary 前缀和。
`visual_x`、`logical_at_x` 和 selection rects 共享该缓存：首次查询为 O(visual items)，
后续边界查询为 O(1)，命中测试为 O(log visual items)。layout 仍保持字体无关的逻辑与
视觉映射；字体或字号变化只重建宽度数组，分配失败回退原有逐字形计算，不改变结果。
selection rects 严格遵守输出 `cap`，写满后立即停止剩余视觉项扫描，避免小输出缓冲的
重复计算。
RTL token 绘制复用同一 visual boundary 前缀和，按 token 范围二分定位颜色，再以 visual
UTF-8 片段提交公共 canvas；纯 LTR 仍走原有单次 token 测量路径，避免新增热路径开销。
内置 bitmap font 在创建时将 1bpp 资源展开为 8bpp alpha，绘制只读取合法的固定 8x8
像素块，不在每帧做格式转换。

## 跨字体 shaping 边界

含 Unicode variation selector 的 cluster 现在同时检查基础字符和实际变体 glyph。FreeType
通过 `FT_Face_GetCharVariantIndex()` 确认 `(base, selector)`；当前置 face 只有基础 glyph、
后备 face 已确认拥有变体 glyph 时，字体链优先选择后备 face，避免在错误 face 上输出基础
glyph 加缺失 selector。没有该可选查询的 provider 保留 unknown 兼容候选，只有不存在已
确认 face 时才采用，不影响 STB、bitmap 或第三方 provider。查询只发生在 shaping/measure
的 cluster 选择路径，不进入 canvas 绘制热路径，也不引入锁或常驻缓存。

字体链在普通路径按 codepoint/cluster 选择 face；当存在显式 script、language 或
OpenType features 时，还会先按每个 face 查询一次 shaping capability，再选择同时覆盖
完整 cluster 且支持该请求的 face。这样首 face 即使覆盖字符但不支持 `liga` 或目标
language-system，也不会静默丢失请求。未知 capability 保留最佳努力回退，兼容旧 provider。
选定后在支持 HarfBuzz 的构建中按连续 face 区间调用 shaping。每个 glyph 携带实际 face
指针；因此同一个 glyph id 在不同 face 中不会污染 soft、GLES2、Vulkan 或 Break RHI 的
缓存。LTR 单 face 不创建 run 表，RTL 只有跨 face 时才分配固定大小的 run 描述并逆序
提交，所有候选输出在成功前保持私有，OOM 时恢复为空结果。链最多接受 256 个 source，
并在分配 face 数组前拒绝数量或乘法溢出。

paragraph 的 `my_text_layout_shape()` 现已将 SheenBidi visual runs 转换为按 direction 和
有限 script segment shaping 的 glyph-run；`my_text_layout_shape_ex()` 还支持显式
script/language/features。复杂 canvas 绘制与测量统一消费该结果。它仍不是完整 Unicode bidi
OpenType 实现：UAX#24 script extensions、language-specific
feature 选择、跨段落增量 shaping 尚未完成；required feature 优先级、script/language system
capability 查询与默认回退已接入。接入后续能力时必须维持 logical byte clusters、视觉
run 顺序、selection/cursor mapping 和后端
atlas key 的一致性。layout 的 caller-owned copy 同时保留原 logical UTF-8；glyph-run API
会拒绝非逐字节匹配的输入和不落在 UTF-8 codepoint 起点的 provider cluster，并在依赖关闭时保留显式
`MY_RET_NOT_SUPPORTED`/codepoint fallback。

Text area 的非 wrap 几何也复用 shaping 的 visual advance 和 cluster span：连字或其他多 codepoint
cluster 只占用一个 glyph advance，selection、IME spot 和 pointer hit-test 使用同一组前缀和，避免
绘制坐标与编辑坐标分叉。字体 vtable 的 `measure`、`get_glyph`、metrics、destroy 和 glyph-id
回调均允许为空；公共包装器返回 `MY_RET_NOT_SUPPORTED` 或零值，控件再使用有界默认行高，因而
shape-only provider 不会在不支持的栅格化路径中触发空函数指针。YAML 折叠导出返回的字符串由调用方
使用传入 allocator 释放，重复导出前必须先释放旧输出。

Text area 的 RTL 光标与 IME 候选框现在也使用同一套 visual boundary：非 wrap 和 wrap 模式均复用
widget-owned 的 RTL layout cache、shaping advance、段落方向和对齐偏移。逻辑光标位于 RTL 行首时
会落在视觉行尾，默认 LEFT 对齐的 RTL 行保持与绘制一致的右对齐；重复的焦点/光标更新不会再次
复制已缓存的 RTL 行文本。非 RTL 行继续走 geometry prefix 快速路径。

RTL geometry 的回退不依赖 HarfBuzz：当字体只提供基础 glyph API 时，text area 仅对含 bidi
codepoint 的物理行执行长度受限预扫描并复用既有 layout cache；普通 LTR 行不创建 bidi layout，
保持原有逐 glyph advance 路径。

## 边界安全与失败事务（2026-09-02）

Canvas 字体 setter 的公共契约要求字号为正数；`font == NULL` 只复用已有字体。四个后端在
修改状态前执行相同校验，非法字号返回 `MY_RET_INVALID_PARAMS`，不会留下半更新状态。几何
输出、soft/GLES 路径栈、Vulkan 退休纹理队列以及文本/YAML/syntax 容量增长均拒绝
`size_t` 加法、倍增或元素字节数回绕，扩容失败继续保留旧状态。

本阶段采用先测试后实现：无效字号回归用例、普通 myui 聚焦套件 **12/12** 和 backend
ASan/UBSan **1/1** 通过。完整 CTest 不纳入本阶段通过声明，因为 `test_vulkan` runtime
在无输出状态下被主动停止；这属于验证环境限制，不改变已通过的 headless 测试结论。

## 动态模块卸载顺序

动态 YAML factory 的 module callback lease 覆盖 factory 返回到 instance binding 完成的
整个创建事务；如果模块在 factory 返回前进入 unloading，绑定会安全失败，候选 widget 会
在 lease 仍活跃时销毁。这样 `try_unload()` 不会在实例计数发布前误判成功，也不会让失败
回滚调用已经卸载的 module-owned widget 代码。该保护只增加动态模块 YAML 创建冷路径的
lease 持有时间，普通 factory、绘制、布局和事件热路径不增加同步成本。

运行期 YAML factory/schema 和 widget class 可以绑定到同一个
`my_widget_class_module_t`。宿主必须按以下顺序关闭模块：调用
`my_widget_class_module_begin_unload()` 停止新 callback；注销 module-owned factory/class；
销毁所有由模块创建的 widget；确认 `my_widget_class_module_try_unload()` 返回
`MY_RET_OK`；最后才调用平台的 `dlclose`、`FreeLibrary` 或 Cocoa bundle unload，完成后
调用 `my_widget_class_module_destroy()`。框架不会自动卸载动态库，也不能保护绕过 lease
直接缓存并调用的外部函数指针。Wayland/X11/Win32/Cocoa 窗口线程和 compositor 的
quiesce 仍由平台宿主负责验证。YAML factory 可使用
`my_ui_loader_runtime_register_schema_module()` 或
`my_ui_loader_runtime_register_dynamic_schema_module()` 接入相同 token；factory、migration
和 typed-property callback 均计入在途 callback，创建出的 widget 在销毁前计入实例数。
带版本迁移的 factory 还可使用 `my_ui_loader_runtime_register_schema_ex_module()` 或
`my_ui_loader_runtime_register_schema_chain_module()`；所有注册变体共用相同的
`registered entry -> callback -> instance` 计数，不允许通过换用另一种 schema API 绕过卸载检查。
模块 token 使用稳定地址的引用协调：创建者持有一个 owner reference，跨线程或跨组件传递
前调用 `my_widget_class_module_retain()`，使用结束调用 `my_widget_class_module_release()`。
`my_widget_class_module_destroy()` 只接受 owner reference 仍为唯一引用的已 quiesce token，
并将 token 标记为 destroyed；token 地址保留至进程退出，迟到的 module-token 调用会返回
`MY_RET_NOT_SUPPORTED` 而不是访问悬空内存。宿主仍须在 `try_unload()` 成功后停止所有缓存的
callback 指针并执行平台动态库卸载；框架不自动调用 `dlclose`、`FreeLibrary` 或 Cocoa bundle
unload。引用计数只发生在模块注册/卸载冷路径，不进入绘制和事件分发热路径。
框架还会校验 token 是否由 registry 创建；未知或伪造地址的 module-token 调用统一返回
失败，不读取调用方提供地址，避免错误句柄导致崩溃。

`my_widget_class_lease_t` 也是线程亲和对象：它只能在获取线程中包围 class factory、
`is_instance` 或 property callback，并由同一线程调用 `my_widget_class_release()`。外部线程
释放请求会被拒绝且不会减少 lease 计数或清理获取线程的 registry guard；宿主应通过所属线程
的事件/任务队列完成释放，而不是转交 lease 结构。lease 还绑定原始结构地址，复制后的
lease 即使在同一线程调用 release 或 bind，也会被拒绝；只有原始 lease 可以结束计数和
callback guard。该规则防止卸载等待被错误打破，同时不在普通 widget 绘制路径增加锁或分配。

动态 schema 的 YAML 标量严格映射到 property descriptor：`string`、有界 `int32`、有限
`float`、`bool` 以及 `color`。其中 `color` 必须是 `0..0xFFFFFFFF` 的 YAML 整数，并以
`MY_VALUE_UINT32`（`0xRRGGBBAA`）交给 setter；负值和超出 `uint32` 的值在 factory 调用前
拒绝。转换在单个字段处理时完成，不分配额外颜色对象。

图形集成测试现在在 `test_render_init()` 成功创建 RHI device 后显式调用
`rhi_set_vsync(device, false)`。这只用于测试进程，避免 GLX/Wayland 的交换同步让多次
预计算 dispatch 依赖外部刷新事件；产品运行时仍由应用自己的 vsync 配置决定。修复后
OpenGL 集成测试与全量 CTest 均通过，最后结果为 **82/82**。
## Vulkan lifecycle and queue ownership

The Vulkan RHI uses one cleanup path for every initialization failure. Partial
swapchain views, framebuffers, semaphores, command buffers, uniform memory and
descriptor objects are tracked by creation count and released only when their
handles exist. Depth, render-pass and framebuffer creation return an explicit
status; callers must stop before recording commands when any attachment fails.

If graphics and present queues belong to different families, device creation
requests both families and the swapchain uses concurrent sharing with both
family indices. When they are the same family, exclusive sharing remains the
fast path. Swapchain recreation rebuilds the render-pass pair before depth and
framebuffer attachments so format changes cannot leave incompatible objects.

The implementation does not claim complete platform coverage: real X11,
Wayland, Win32 and macOS WSI runtime CI, allocator fault injection and device
lost recovery remain required validation work.

Surface format and present-mode enumeration is fail-closed: both Vulkan query
stages check their result and zero-length lists are rejected. Every Vulkan
memory allocation goes through a small validation wrapper that refuses the
`UINT32_MAX` sentinel returned when no compatible memory type exists. Resource
specific rollback remains responsible for destroying the already-created
buffer or image.

Instance and device extensions are capability-negotiated before creation.
Required surface/WSI, swapchain and platform portability extensions fail
initialization safely when unavailable; validation/debug-utils and device-fault
extensions remain optional. Physical-device enumeration checks both Vulkan
query stages and never consumes an undefined device list after an error.

The deferred mip-upload slot is explicitly owned by a `VKBackend`. A device
only reclaims its own fence, staging buffer and command buffer; another Vulkan
device cannot overwrite or reclaim the slot. This keeps multi-device teardown
from passing handles to the wrong `VkDevice` while preserving the non-blocking
single-upload fast path.

Physical-device selection is also fail-closed. Automatic selection chooses the
first adapter that exposes `VK_KHR_swapchain`, successfully answers surface
capability, format, and present-mode queries, and has both graphics and
present-capable queue families. `RE_VK_DEVICE_INDEX` remains available for
bring-up, but an invalid or unsuitable pinned index now fails initialization
instead of silently falling back to another adapter or selecting `gpus[0]`.
The selection probes run only during initialization; the frame path has no
additional capability-query cost.
