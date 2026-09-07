# myui 后续阶段方案与状态

## 本轮补充：Vulkan 关闭配置链接缺陷修复（2026-09-07）

TDD 先在非 Vulkan 后端测试中锁定完整 instance API 的安全失败契约，随后补齐
`my_vgcanvas_vulkan_instance_acquire_with_extensions()` stub。修复后重新配置的 ASan/UBSan
构建成功链接 `test_myui_window_manager`，并完成 vgcanvas、Break PAL、窗口管理器、MVVM 和
shader I/O 五套定向测试，合计 **379/379**；未发现 ASan/UBSan 报告。

该验证覆盖无 Vulkan SDK/能力的静态配置，不等价于真实窗口 WSI。Vulkan 开启配置的离屏与
headless 回归仍需保持，并由真实 X11/Wayland/Win32/macOS runner 继续验证设备、surface、
swapchain 和 validation-layer 生命周期。

## 本轮补充：Vulkan WSI 依赖边界（2026-09-07）

`myr` 不再强制定义 X11/Wayland Vulkan 平台宏，避免 Windows/macOS 交叉编译被错误
Linux 头文件污染；surface 创建继续由 PAL/宿主负责，myr 只消费 opaque handle 和
Vulkan core API。配置契约测试同时拒绝该类平台泄漏。

当前源码在 lavapipe 无显示环境下完成 Vulkan 离屏 `test_myui_vgcanvas_backend` **1/1**，
并完成 headless CTest **98/98**；窗口 WSI、真实设备和 validation layers 仍需平台 CI。

Vulkan instance 生命周期同时改为显式临时 lease：窗口 PAL surface 创建使用
`my_vgcanvas_vulkan_instance_acquire()`/`release()`，失败路径不会遗留全局 instance/device；
`my_vgcanvas_vulkan_instance()` 仅做无副作用 peek。主工程和 lavapipe 离屏回归已复验。

独立 myui CMake 入口补齐 `project(myui LANGUAGES C)` 与 strict C11 baseline，消除
standalone 配置警告并避免继承调用方的非标准 C dialect；关闭可选依赖后的六模块聚合构建
通过，配置契约测试覆盖此入口。

## 本轮补充：渲染后端显式能力开关（2026-09-07）

TDD 先锁定 `MYUI_GLES2`、`MYUI_GL_DESKTOP`、`MYUI_VULKAN` 选项和 Vulkan shader
生成目标的模块相对路径。修复后，后端关闭时不再探测或链接对应依赖；开启 Vulkan
时由 `generate_includes.cmake` 调用 `glslangValidator` 生成 SPIR-V include，避免
调用方顶层目录变化造成目标失效。主工程 `myui_core` 与可复用 `myui` 聚合入口共享
同一能力语义，Engine Vulkan/macOS 仍自动启用 Vulkan。

待验证：Windows/macOS 原生图形库实际运行时、无图形开发包的跨编译器矩阵，以及
Vulkan validation layers 下的真实 swapchain 生命周期。

## 本轮完成：可复用 CMake 依赖边界与 PAL target（2026-09-06）

TDD 先扩展 `test_myr_dependency_config`，锁定 `myc`、`myr`、`myui`、`mymvvm`、
`mymvvm_myui` 和 `mypal` 不得引用调用方的 `${CMAKE_SOURCE_DIR}`，并要求每个模块从
自身位置推导 `MYUI_SOURCE_DIR` 与 `MYUI_ENGINE_SOURCE_DIR`。修复后新增可复用的
`mypal` CMake target，包含 PAL 公共核心、事件/媒体/timer 和 deterministic dummy port；
`myui` 入口显式要求先加入 `mypal`，避免独立集成在链接阶段才暴露缺少 target。

`MYUI_SOURCE_DIR` 指向 `engine/src/myui`，`MYUI_ENGINE_SOURCE_DIR` 指向 `engine/src`，
分别覆盖 myui 模块头与仓库公共 `core/*` 头，避免单一 include 根导致的隐式路径错误。
FreeType/HarfBuzz、GLES/OpenGL/Vulkan 仍按可选依赖关闭；真实 X11/Wayland/Win32/Cocoa
port 继续由 engine 宿主选择，不把窗口系统库引入 headless 子项目。

验证：配置契约测试通过；隔离顶层按 `myc -> myr -> mypal -> myui -> mymvvm ->
mymvvm_myui` 构建，在关闭字体、YAML、BiDi 和图像选项时 **87/87**；主工程
`test_myui_font`、`test_myui_loader`、`test_myui_text_layout`、依赖配置测试 **4/4**。

## 本轮补充：glyph bitmap lease 与 cache 淘汰安全（2026-09-06）

TDD 先加入容量为 1 的 FreeType/STB cache 淘汰回归：取得 glyph A 后取得
glyph B 强制淘汰，仍可安全读取 A 的 bitmap。修复后，字体 API 返回显式 glyph
lease；FreeType/STB 只淘汰零引用的固定 cache entry，缓存全部被占用时把新
entry 放入 font-owned overflow list，直到 lease 释放或 font 销毁统一回收；overflow
数量受 `min(cache_capacity, MY_FONT_MAX_GLYPH_OVERFLOW_ENTRIES)` 硬预算约束，超限
返回 `MY_RET_OOM` 并保留已有 lease。这样不需要每次命中分配，也不会释放调用方仍在消费的 bitmap。

soft、GLES2、Vulkan、Break RHI、text layout、paragraph 和 text-area 已在
消费后释放 lease。调用方不得复制 live `my_glyph_t`，必须对每次成功查询调用
一次 `my_font_glyph_release()`，且 font 必须保持有效到最后一个 lease 释放。
内置 bitmap font 也使用 owner lease，销毁请求后拒绝新的 glyph 查询并延迟到最后
一个 lease 释放；字体链销毁时子 face 同样遵循该延迟回收协议。
普通字体专项当前为 **82/82**；ASan/UBSan、STB-only 和 Clang TSan 字体专项也均为
**82/82**。FreeType/STB 的 destroy 请求会延迟到最后一个
glyph lease 释放，但 provider 调用本身仍须避免与 destroy 并发进入，宿主必须
外部串行化新的 provider 调用与 destroy 请求。

## 本轮补充：FreeType provider 并发访问收口（2026-09-06）

TDD 先新增共享 face 并发回归，复现了多个线程同时切换字号、访问 glyph cache 和执行
HarfBuzz shaping 时的 `FT_Face` 状态竞争与堆损坏。修复后，FreeType 字体对象为
`FT_Face`、当前字号、glyph/capability cache 提供对象级跨平台互斥；进程级
`FT_Library` 初始化使用原子自旋初始化保护。锁不进入字体链选择、paragraph/layout cache
或绘制路径，不同 face 之间不共享锁。普通、ASan/UBSan 字体专项均为 **73/73**，STB-only
专项为 **73/73**。

该阶段只保证同一 FreeType face 的并发 provider 调用安全，不把裸 `my_font_t*` 变成可跨线程
销毁句柄；宿主仍须保证销毁发生在所有调用返回后。Clang/GCC TSan 的完整证据仍受当前
构建环境影响：GCC TSan 链接缺少 `/usr/lib64/libtsan.so.2.0.0`，需修复工具链后复跑。

## 本轮补充：STB provider 并发访问收口（2026-09-06）

共享 STB 字体对象的 TDD 并发回归覆盖字号切换、glyph cache、metrics、measure、coverage
查询和诊断计数。实现增加对象级跨平台互斥，避免 `stbtt_fontinfo` 与 LRU cache 的并发
读写；`measure` 在同一锁内计算行高，避免锁内重入 metrics 包装器。不同 face 使用独立锁，
正常 cache 热路径不增加分配或全局竞争。

普通 FreeType+STB、ASan/UBSan 和 STB-only 字体专项当前均为 **74/74**；该保证不覆盖
跨线程对象销毁，宿主必须先结束所有 provider 调用。

## 本轮补充：模块 factory 实例绑定事务（2026-09-06）

YAML 动态 factory 的 module callback lease 现在覆盖 factory 返回到实例绑定完成的
完整事务；绑定失败时也在 lease 仍活跃期间销毁候选 widget。这样模块 quiesce 不会在
factory 已返回但实例计数尚未建立的窗口内提前通过，失败回滚也不会把模块析构代码暴露
给并发卸载。正常非模块 factory、绘制、布局和事件热路径不增加锁、分配或额外分支；仅
动态模块 YAML 创建冷路径保留一次已有的 module lease。

loader 专项当前 **120/120** 通过。真实 `dlclose`/`FreeLibrary`/Cocoa bundle unload`、
宿主线程串行化和动态模块自定义 widget 析构仍需平台宿主验证，框架不自动执行动态库卸载。

## 本轮补充：CSS `@scope to` 隐式根与边界校验（2026-09-06）

`@scope to <selector> { ... }` 现在支持省略起点的标准形式。隐式根不引入祖先路径，
边界选择器使用固定哨兵记录，并沿当前节点到根的父链做有界匹配；显式根仍在到达根
后停止搜索，边界节点自身和其后代均被排除。嵌套 scope 的每个边界独立保留，主题
查询热路径仍只有固定深度指针遍历，不增加分配、锁或渲染后端分支。

TDD 新增隐式根边界匹配、嵌套显式/隐式边界、universal/compound `to` selector、有限
selector list、malformed `to` 语法及 capability 诊断回归；普通 `test_myui_css` 当前
**103/103** 通过。
带组合器的复杂 selector、超过 4 项的 selector list、复杂条件 at-rule 组合和真实平台
runtime 矩阵仍属于未完成边界。

## 本轮补充：window-manager on_open callback lease（2026-09-06）

窗口管理器新增 `my_window_manager_set_on_open_owned()` 与
`my_window_manager_set_on_open_lease()`。替换 hook 时先提交新 lease/回调状态，再释放旧
owned context 或 lease；如果替换发生在 `on_open` 重入期间，旧状态进入 retired 队列，最
外层 manager callback 返回后才统一释放，避免 destructor 在原 callback 仍使用 context 时
提前执行。manager 销毁也会统一回收当前 hook。无效 lease 注册失败且不转移所有权；打开
窗口时失效 lease 会跳过 callback，已取得临时 lease 引用的 callback 可以安全完成。兼容
的 `my_window_manager_set_on_open()` 保持 borrowed 语义。

TDD 覆盖失效后跳过、替换释放、callback 重入替换、callback 重入 manager teardown 和
manager teardown，普通与 ASan/UBSan 专项 `test_myui_window_manager` 当前均为
**235/235** 通过。该 API 保护 callback context，不改变 `on_open`、window 或 manager
的 UI 线程亲和性。

## 本轮补充：菜单与 dialog callback lease（2026-09-06）

新增 `my_menu_popup_lease()` 与 `my_dialog_open_lease()`，为独立 callback API 提供与
emitter 相同的 invalidation/lifetime 协议。打开成功后 menu/dialog 持有一份 lease 引用，
调用方可立即释放自己的引用；lease 失效后跳过尚未开始的 callback，已经进入的 callback
可以完成。关闭、窗口关闭、manager 销毁和打开失败都会释放内部引用，最终 destructor
恰好执行一次。无效 lease 注册失败且不转移所有权，普通 borrowed/owned API 继续兼容。

TDD 覆盖 menu/dialog 的无效注册、失效后跳过、callback 内失效、提前 unref、窗口关闭和
manager 销毁；专项 `test_myui_window_manager` 当前 **226/226** 通过。剩余限制是 UI API 仍要求在所属主循环
线程调用；lease 只保护 callback context，不把 menu/dialog/window 句柄变成跨线程句柄。

## 本轮补充：emitter borrowed context lease（2026-09-06）

新增 `my_emitter_context_lease_t`、`my_emitter_on_lease()`、`my_widget_on_lease()`、
`my_window_add_close_listener_lease()` 与 `my_window_manager_add_destroy_listener_lease()`，为原本由调用方借用的
event context 提供显式失效边界。owner 在释放 context 前调用 `invalidate()`；之后不会
启动新的 guarded callback，已进入回调的调用允许自然返回。emitter 持有一份 lease 引用，
调用方可以在注册成功后立即释放自己的引用，最终 listener 移除或 emitter 销毁时恰好执行
一次 context destructor。失效注册会拒绝且不转移所有权。

lease 的失效/准入闸门只在 guarded callback 的冷生命周期边界执行；普通 emitter listener
路径不增加原子或自旋开销。TDD 覆盖回调内失效、失效后跳过、提前 unref、无效注册、一次性
析构、widget 转发、window close 和 manager destroy 生命周期，普通
`test_myui_window_manager` **219/219** 通过。该能力已接入 emitter/widget/window/manager，
菜单/dialog 的独立 callback API 已在本轮迁移。

## 本轮补充：字体 descent vtable 边界（2026-09-06）

新增 `my_font_descent()` 公共安全包装器，空字体、空 vtable 或缺失 `descent` slot
统一返回 0；字体链的 descent 聚合改为经过该包装器，不再直接调用可选后端函数指针。
该检查为 O(1)，不增加 shaping、布局或绘制热路径的分配与锁。TDD 新增缺失 metric slot
回归，普通 `test_myui_font` **72/72** 通过。

## 本轮补充：LCD 渲染后端 vtable 边界（2026-09-06）

`my_lcd_*` 抽象层现在与 PAL、font 和 canvas 保持一致：空 LCD/空 vtable 的查询返回零、
空 buffer 或无效 pixel-format 值，绘制和帧操作返回 `MY_RET_INVALID_PARAMS`；存在 vtable
但缺少具体 slot 时返回 `MY_RET_NOT_SUPPORTED`。destroy 同样为无操作安全入口。该修改覆盖
soft、GLES、Vulkan 和平台 LCD 共用的最底层 render-target 调用，避免部分初始化后端触发
空函数指针。

防护是固定 O(1) 指针判断，无缓存、无分配、无锁；TDD 覆盖空 vtable 和全部基础 LCD
查询/绘制 slot，普通 `test_myui_vgcanvas_backend` **35/35** 通过。

## 本轮补充：MVVM target 与 array vtable 边界（2026-09-06）

`my_binding_target_*` 与 `my_view_model_array_*` 公共包装器现在会先校验对象、vtable 和所需
slot。空对象/空 vtable 返回确定错误或零值，缺失可选 target slot 返回
`MY_RET_NOT_SUPPORTED`；items binding 创建和重建也在访问 `rebuild_items` 前完成同一检查。
这避免应用自定义 MVVM 适配器的部分初始化或析构竞态变成空函数指针调用。

所有检查是固定 O(1) 指针判断，不增加绑定通知、列表刷新、布局或绘制路径的分配与锁。
TDD 覆盖空 vtable、全空 vtable、items binding 创建和 array 各操作；普通
`test_myui_mvvm` **40/40** 通过。

## 本轮补充：emitter listener ID 回绕安全（2026-09-06）

监听器 ID 分配现在不会产生 `0`，也不会在 `uint32_t` 回绕后复用仍活动的 ID。正常
单调分配路径保持 O(1)；仅在 ID 回绕后的冷路径扫描固定当前监听器集合，若所有候选都
不可用则注册失败，不破坏既有监听器。该保护位于订阅/注销生命周期边界，不增加事件
分发、布局或绘制热路径的锁、分配和扫描。

TDD 先复现 `UINT32_MAX -> 0` 的回绕错误，再验证最大 ID、回绕后的冲突跳过和三条监听器
均可安全注销；普通与 ASan/UBSan `test_myui_window_manager` 均为 **214/214**。

## 本轮补充：MVVM 绑定规则严格解析（2026-09-06）

绑定规则解析器现在拒绝空选项、重复选项、未配对或多余的括号，并拒绝在
`Condition=...` 条件体后追加普通选项；合法的嵌套校验器参数仍可解析。选项去重使用
固定整数位图，括号检查为单次有界扫描，不增加绑定或绘制热路径分配/锁开销。`Items=`
和选项形式的 `Condition=` 继续明确返回 `MY_RET_NOT_SUPPORTED`，只有
`v:items={...}` 与 `v:visible={Condition=...}` 专用语法有效，避免把未定义语义误当成
可执行绑定。

TDD 先覆盖空选项、括号边界、重复选项、条件混用和嵌套参数；普通
`test_myui_mvvm` **37/37** 通过。该修复保持解析失败时的候选规则不可发布，并保留现有
`Items`/条件绑定实现与公开 ABI。

## 本轮补充：规则引擎销毁路径与 ASan 收口（2026-09-06）

修复表达式树销毁遍历：使用显式节点栈完整释放 `first`/`second` 分支，避免包含
`and`/`or` 的规则在程序销毁时泄漏。修复事实撤回时结构化值和字符串所有权被清空但未
释放的问题，同时保留撤回事件回调所需的快照生命周期，直到事实集销毁。补齐 RETE 外部
网络、查询 proof 和 query fixture 的显式清理，避免把测试夹具遗漏误判为库泄漏。

本轮 TDD/验证结果：普通构建完整 CTest **99/99**，Redis source-backed 完整 CTest
**99/99**，ASan/UBSan 完整 CTest **99/99**，`git diff --check` 通过。修复未修改
`/home/timeshift/opensource/redis-8.10.1`；Redis 仍通过 `deps/hiredis` 源码接入。

## 本轮补充：Redis 值解码失败原子性（2026-09-06）

Redis `GET` 的合法 bulk-string 仍需通过本地类型与 payload 长度校验；解码失败或字符串
结果分配失败时，现在保留调用方已有的 `re_value_t` 与 provider 上一次字符串存储，只有
完整解码成功后才发布候选结果。新增 malformed payload fake-server TDD 回归；Redis
source-backed 专项测试为 **54/54**。

## 本轮补充：Redis GET RESP 类型校验（2026-09-06）

Redis provider 对 `GET` 仅接受 `NIL` 或 bulk-string 回复；其他 RESP 类型统一报告
`RE_PROVIDER_ERROR_SERIALIZATION`，并保持调用方已有值不变。新增本地 RESP fake-server
TDD 回归，source-backed Redis 专项测试为 **53/53**。

## 本轮补充：Redis DEL 异常整数响应校验（2026-09-06）

Redis provider 现在只把 `DEL` 的非负整数作为有效结果；负整数或非整数回复都会报告
`RE_PROVIDER_ERROR_SERIALIZATION`，不再把损坏 RESP 数据误作删除成功。新增本地 RESP
fake-server TDD 回归；source-backed Redis 专项测试为 **52/52**。

## 本轮补充：Redis PTTL 异常响应校验（2026-09-06）

Redis provider 现在只接受 `PTTL` 的 `-1`（无过期）、`-2`（不存在）和非负整数；
其他负值会在转换为无符号 TTL 前报告 `RE_PROVIDER_ERROR_SERIALIZATION`，并保持调用方
输出不变。新增本地 RESP fake-server TDD 回归，验证异常响应不会产生超大 TTL；source-backed
Redis 专项测试为 **51/51**。

## 本轮补充：Redis TTL 有符号边界（2026-09-06）

Redis provider 在进入 hiredis 网络调用前拒绝大于 `INT64_MAX` 毫秒的 TTL，并返回
`RE_STATUS_LIMIT`；这样无符号公共 API 不会把不可表示的值交给 Redis 的有符号
`PSETEX` 参数。TDD 通过延迟本地服务验证该请求不进入阻塞网络路径，Redis source-backed
构建的 rule-engine 专项测试全部通过。

## 本轮补充：timer 清理唯一释放门禁（2026-09-06）

新增 `timer_remove_releases_each_entry_once` 回归，使用注入 allocator 检查非回调期间
移除 timer 后的 heap sweep 以及 manager 销毁不会重复释放同一条目。该测试覆盖 timer
删除的冷路径，不改变非冷却状态的无 timer 约束，也不增加 timer heap 的运行时复杂度；
普通与 ASan `test_myui_window_manager` 均为 **213/213**。

## 本轮补充：跨 face variation glyph 选择（2026-09-06）

字体 vtable 新增可选的 `(base codepoint, variation selector)` 覆盖查询；FreeType 使用
`FT_Face_GetCharVariantIndex()` 提供确定结果，字体链在 cluster 选择时优先采用已确认拥有
实际变体 glyph 的 face。没有该查询的 STB、bitmap 和第三方 provider 仍保留 unknown 兼容
回退，不会被误判为不支持。TDD 新增真实 Noto CJK TTC 的前 face 缺失 IVS、后 face 提供
IVS 的链级 glyph golden；普通、ASan/UBSan、STB-only 字体专项均通过。

此阶段只关闭 provider-specific variation 覆盖选择，不等同完整跨字体 GSUB/GPOS 上下文、
跨字体 token shaping 或完整 RTL OpenType corpus；这些仍保留在未完成能力矩阵。

## 本轮补充：RTL GSUB/GPOS 组合边界 golden（2026-09-06）

新增 Noto Arabic RTL golden，覆盖 Arabic mark 的基字符 byte cluster 合并、零 advance 与
非零 GPOS offset，以及 Arabic comma 和 Eastern Arabic-Indic 数字的视觉逆序、glyph id、
advance 和 byte cluster。断言使用 HarfBuzz 的真实 cluster 语义，不把组合标记误当成独立
逻辑字符；字体专项当前为 **71/71**。这批 golden 扩大了单字体证据，但仍不代表完整
RTL GSUB/GPOS：跨字体上下文、全部 language-system、复杂多段落重排和完整字体 corpus
继续保留在未完成矩阵。

## 本轮补充：跨平台 clipboard UTF-8 边界统一（2026-09-06）

新增 `platform_utf8_validate()`，以显式长度验证完整 UTF-8 payload；所有平台的 clipboard 写入和接收均拒绝 overlong、
surrogate、超范围码点、截断序列和嵌入 NUL。X11 与 Wayland 的本地缓存、X11 selection
接收完成及 Wayland 非阻塞 pipe 接收均在交付缓存前使用该校验；Wayland 的最大 payload
边界与 X11 统一为允许恰好 `16 MiB`，终止字节单独计入容量。非法或超限数据只失败当前
clipboard 请求，不覆盖旧缓存。TDD 新增平台文本纯逻辑回归，覆盖合法、空值、各类非法
UTF-8 和显式 NUL；平台文本、dummy PAL、window manager 及 Wayland 构建/测试均通过。
Wayland 精确 `16 MiB` 接收边界另增加 EOF/超限单字节探测，避免合法上限 payload 因没有
终止字节而永久保持 `PENDING`。

## 本轮补充：shaping unsupported 回退收口（2026-09-06）

公共 shaping 层现在区分明确的 `UNSUPPORTED` 和 `UNKNOWN`：当 provider 已确认请求的
language/script/features 不支持时，带显式 feature 的请求直接返回
`MY_RET_NOT_SUPPORTED`，不再降级后调用 `shape_ex` 并静默丢失 feature；无 feature 的旧
请求仍保留 language、script 到 legacy shape 的兼容回退。新增 TDD 红测覆盖 provider 未
支持 feature 时不应被调用且结果保持为空，修复后 `test_myui_font` 为 **67/67**。该策略
不改变 HarfBuzz 支持的真实 language-system/features 行为，也不增加绘制热路径开销。

## 本轮补充：共享引用计数溢出保护（2026-09-06）

新增 `myc/my_ref_count.h`，为 `atomic_uint` 与 `atomic_size_t` 提供无锁 CAS 饱和递增和
释放 helper。UI object、MVVM context/异步状态、undo manager、UI command/scope、image
loader lease、list adapter lease 均不再使用无保护的 `atomic_fetch_add` 递增；达到计数上限
时拒绝递增并保持饱和值，释放也不跨过饱和值。该策略优先保证安全性：极端计数饱和会让对象
常驻，但不会回绕为 0 导致错误析构；正常路径仍是单个原子操作的低开销边界检查，不进入
绘制热路径。TDD 新增上限稳定性回归，覆盖最大值拒绝递增、`MAX-1` 成功到达上限和饱和
释放不回绕。

本轮验证：`test_myui_window_manager` **205/205**，完整 CTest **99/99**，`git diff --check`
通过。该修复不改变 `/home/timeshift/opensource/redis-8.10.1` 参考源码，也不改变 XML/YAML
配置策略；Wayland 协议 XML 仍仅作为构建依赖。

## 本轮完成：emitter 重入销毁安全（2026-09-06）

`my_emitter_destroy()` 在监听器回调中被调用时现在只发布关闭标记，延迟到最外层
`my_emitter_emit()` 收尾后释放监听器数组，并立即停止同轮后续监听器。嵌套 emit 只在
最外层返回时释放，避免回调栈继续访问已释放 emitter。TDD 覆盖 emitter 自毁、owned
context 注销释放一次、析构释放一次以及 context 析构重入；普通和 ASan
`test_myui_window_manager` 均为 **204/204**。

## 本轮补充：同步回调自毁安全（2026-09-06）

编辑器和按钮的事件事务现在在进入 widget handler 时持有临时引用，覆盖同步
`changed`/`click` 回调返回后的布局、失效区域和冷却状态访问；编辑器的输入、删除、
IME、粘贴以及撤销/重做路径也保留事务级引用。监听器可以在回调中移除并释放自身，
不会把后续 handler 代码变成悬空访问。引用只存在于事件/历史操作边界，不进入绘制热路径，
不增加锁、分配或跨平台后端分支。

TDD 覆盖 edit/text-area typed input、button keyboard click、node view、checkbox、slider、
scroll bar 以及 MVVM emitter 的自毁回归；普通 `test_myui_window_manager` **198/198**、
`test_myui_mvvm` **35/35**，ASan 定向套件同样通过。保护只位于事件/通知事务边界，不进入
绘制热路径。timer 回调仍遵循所属 UI loop 的取消协议：控件/窗口销毁链先取消 timer，
timer manager 在 callback 重入销毁时延迟释放；因此不引入会阻塞析构的强引用。

当前剩余是需要真实宿主环境才能证明的边界：Windows/macOS/Wayland/X11 窗口线程与
clipboard/IME/present/buffer-age runtime 矩阵、动态模块真实卸载、完整 RTL/OpenType 与
UAX#14/CSS 能力，以及通用 borrowed callback context 的自动失效协议。

最新仓库基线：完整 CTest **99/99**；window manager **204/204**；MVVM **35/35**；
YAML loader **114/114**。默认构建、ASan/UBSan 定向 loader/window-manager/MVVM、Clang
TSAN 定向 loader/window-manager/MVVM，以及 `MYUI_UI_YAML=OFF` loader stub 门禁均通过。

本轮补齐动态 YAML schema 的 `MY_PROP_COLOR` 端到端转换：严格校验已接受的
`0..0xFFFFFFFF` 整数现在会以 `MY_VALUE_UINT32` 原样交给 property setter，不再在 factory
创建后因未实现转换而失败；负数和超范围值继续在回调前拒绝。转换是单字段标量赋值，无额外
分配或绘制路径成本；TDD 覆盖 RGBA32 传递和两种无效边界。

窗口和 window manager 的生命周期监听器现在也提供 owned context 入口：
`my_window_add_close_listener_owned()` 与
`my_window_manager_add_destroy_listener_owned()`。主动注销或生命周期结束时 context
析构函数恰好执行一次；borrowed 入口保持兼容。该能力只运行于关闭/销毁冷路径，不增加
绘制、布局或事件分发热路径成本。

TDD 还覆盖了 owned listener destructor 释放最后一个 window creator 引用或请求 manager
销毁的重入顺序；listener 记录会先摘除并释放，再执行 destructor，避免回调返回后访问
已失效 owner。普通和 ASan `test_myui_window_manager` 均为 **204/204**。

owned listener 的 destructor 运行时 owner 可能已经进入销毁流程；实现先从监听器容器摘除
并释放记录，再调用 destructor。因此 destructor 可以安全地释放最后一个 window 引用或
请求 manager 销毁；borrowed API 不接管 context，调用方必须保证其 context 生命周期。

## 本轮补充：List adapter lease 生命周期收口（2026-09-05）

公共 `list_view` 保留原有 borrowed `my_list_view_set_adapter()` 兼容入口，同时新增
`my_list_adapter_lease_t` 与 `my_list_view_set_adapter_lease()`。lease 使用原子引用计数，
列表在替换/销毁前先回收 active/pool rows，再释放自身 lease；因此 adapter 不会在列表仍
持有由其创建的 row 时提前析构。lease API 的引用操作不进入绘制或滚动热路径，也不使用
全局锁；adapter 的 vtable/实例在 lease 存续期间必须保持不变，直接 UI API 仍只允许在
所属 loop 调用。

安装失败或重入返回 `MY_RET_INVALID_PARAMS`/`MY_RET_PENDING` 时，当前 adapter、rows 和
滚动状态保持不变；旧 borrowed API 仍由调用方负责实例生命周期。MVVM `items_adapter`
已切换为 target-held lease + list-held lease，模板替换和 binding target 销毁不再直接释放
列表可能正在使用的 adapter。TDD 新增 lease 替换、失败保持旧 adapter 和最终析构一次回归；
普通 `test_myui_window_manager` 当前为 **184/184**，普通 `test_myui_mvvm` 为 **33/33**。

## 本轮补充：Scroll view 内容弱引用失效（2026-09-05）

`scroll_view` 在自己的 direct-child 移除 hook 中清空 `content` 并复位 offset；因此调用方
直接执行 `my_widget_remove_child(my_scroll_view_widget(view), content)` 后，后续测量、滚动和
查询不再访问已释放 widget。该 hook 仅在低频树变更运行，不影响滚动/绘制路径，也不改变
内容替换的候选提交语义。TDD 新增 direct-remove 后的安全查询与滚动回归；普通、ASan 和
Clang TSAN `test_myui_window_manager` 均为 **184/184**。

## 本轮补充：Image loader 缓存隔离与输入校验（2026-09-05）

图片缓存键由单独的路径改为 `(loader, lease, path)`，不同 loader 或不同生命周期 lease 使用
相同路径时不会互相复用像素结果；缓存先复制 RGBA 数据，再通过原 loader 的 `free_data`
释放临时结果，不再把 loader 私有内存错误接管到缓存。带 lease 的 loader 由 image 与缓存
条目共同持有引用，最后一次 unref 才执行 release callback；borrowed loader 不进入缓存，
每次绘制后释放临时数据，宿主仍须自行保证其生命周期。loader vtable、图像指针、尺寸和
乘法容量在调用前均有固定边界检查；非法 loader 保持原设置不变并返回 `MY_RET_INVALID_PARAMS`。

该修复只发生在图片加载冷路径，命中仍为 O(1)，绘制热路径不增加锁或分配。缓存改为每个
 UI loop 线程的固定容量 LRU，命中/未命中统计为原子计数；`my_image_cache_clear()` 只清理
调用线程缓存，条目释放 callback 也在调用线程运行。TDD 覆盖同名路径隔离、lease 与缓存
联合持有、borrowed 临时数据、原 loader 释放以及非法 vtable/数据安全失败；普通
`test_myui_window_manager` 当前为 **184/184**，ASan 与 Clang TSAN 定向测试同步通过。

## 本轮补充：Animator widget 生命周期与时间边界（2026-09-06）

动画记录现在持有目标 widget 的强引用，完成、停止、子树移除和 manager 销毁时统一释放；
调用方在提交动画后释放 creator 引用不会让 timer 回调访问悬空对象。完成记录在 tick/停止
冷路径回收，避免长期运行的界面累积失效动画记录。

开始时间与延迟使用差值判断，避免 `start + delay` 溢出；时钟回拨不会提前完成。动画 ID 分配
始终跳过 0 和当前仍使用的 ID，回绕后仍保持唯一；无安全 ID 时提交失败，不改变活动动画。
这些保护不增加帧内锁或分配，仍使用单个共享 timer；回调重入停止只延迟到 tick 结束回收，
不会在数组遍历期间压缩记录。TDD 新增动画延迟上界、widget 释放和回调重入回归；普通
`test_myui_window_manager` 当前为 **184/184**，ASan 与 Clang TSAN 定向测试通过。

## 本轮补充：共享撤销管理器延迟销毁（2026-09-06）

共享 `undo_manager` 原先由应用直接销毁，而 edit/text-area 仍保留借用指针，控件随后析构
会调用已释放 manager。现在 manager 使用 owner 引用加注册控件引用：应用销毁请求会立即
关闭新记录和路由、清空历史，但实际存储延迟到所有注册控件注销后释放；edit/text-area
无需改变 widget ABI 即可安全完成析构和显式解绑。该 API 仍不允许调用方在 destroy 返回后
继续访问 manager 句柄，也不提供跨线程 targets 数组并发修改。

TDD 新增 edit/text-area manager-first 销毁与解绑回归；普通 `test_myui_window_manager`
当前为 **184/184**，ASan 与 Clang TSAN 定向测试通过。

另新增 window-held manager 引用回归：窗口绑定会保留一份 manager 引用，窗口解绑或销毁时
释放该引用，避免所有控件注销后窗口仍保存悬空 manager 指针。

## 本轮补充：编辑器异步 clipboard 回调生命周期（2026-09-06）

`my_edit` 与 `my_text_area` 的异步 paste timer 在调用 PAL clipboard 重试前取得 widget
临时引用，并在所有返回路径释放。这样 `changed` listener 可以在 paste 事务中移除并释放
自身，事务剩余路径和 timer 清理仍可安全完成；同步输入、绘制热路径和 PAL ABI 不变。

TDD 新增 edit/text-area 的 self-removing `changed` listener 回归，并让 dummy PAL 可注入
指定次数的 `MY_RET_PENDING` clipboard 读取，确保测试走真实重试路径。普通
`test_myui_window_manager` 当前为 **186/186**；下一步仍需在真实 X11/Wayland/Win32/macOS
clipboard 异步传输矩阵验证异常撤销、selection owner 消失和 loop 关闭竞态。

## 本轮补充：MVVM 跨线程属性提交（2026-09-05）

`my_mvvm_context_set_property_async()` 将标量或字符串值在生产者线程复制后，投递到绑定窗口
所属的 PAL loop；模型 setter、变更通知以及 data/items/condition binding 的 UI target 更新
全部在 loop 线程执行。借用语义的 `MY_VALUE_POINTER` 明确拒绝，避免把裸指针误当成跨线程
安全快照。`my_mvvm_context_notify_change_async()` 保留用于模型存储已由宿主同步完成后的
兼容通知；不能用它绕过模型自身的数据竞争。

异步请求采用每个 binding session 64 个 pending 的无锁 CAS 配额，超出配额返回
`MY_RET_PENDING`；字符串快照限制为 4 KiB，避免高频 worker 或恶意输入造成无界内存峰值。
请求完成、提交失败和 scope 丢弃都会归还配额。

MVVM context 持有独立 command scope，context 或 window manager 销毁会取消未执行通知，排队
请求只保留 VM 引用和固定大小的属性快照，不保留 binding target 裸指针。TDD 新增工作线程
属性提交、字符串快照、pointer 拒绝、context 销毁和 manager-first 销毁覆盖；本轮又增加
bulk data/condition/items 刷新、四 worker 并发提交及 worker 线程释放 context 回归，普通
`test_myui_mvvm` 当前为 **32/32**。核心 `mymvvm` 仍保持 GUI/PAL-free，异步能力位于
`mymvvm_myui` 适配层；窗口、widget、manager、timer 和 RHI 直接操作仍要求所属 UI loop。

`my_mvvm_context_ref()` 必须在 worker 开始使用异步 API 前调用，并由生命周期 owner 通过
`my_mvvm_context_unref()` 释放；`my_mvvm_context_destroy()` 只释放 creator reference。
最后一个引用即使在 worker 线程释放，也会把 context 的最终 widget、binding listener 和
command scope 清理投递回绑定 loop，避免 UI 对象在线程外析构。绑定 loop 必须存活到所有
context 引用释放及其排队清理完成。

## 本轮补充：MVVM template context 所有权（2026-09-05）

新增 `my_mvvm_register_template_owned()` 与 `my_mvvm_unregister_template()`，为长期
item-template `builder_ctx` 提供显式 owner 和恰好一次析构语义；同名替换先更新 registry
再释放旧 context，失败注册不转移所有权。普通、ASan 和 Clang TSAN
`test_myui_mvvm` 均通过 **32/32**。旧 `my_mvvm_register_template()` 仍保持 borrowed
context 兼容行为，builder 线程亲和性和调用方生命周期责任不变。

## 本轮补充：异步导航请求生命周期（2026-09-05）

新增 `my_navigator_wm_request_async()`：请求在提交时复制，只允许进入 navigator 所属的
PAL loop，并使用 navigator 自有 command scope；页面 factory 和 window manager 操作不会在
producer 线程执行。
navigator 或 manager 销毁会取消尚未执行的请求；异步 API 还拒绝 foreign loop，并传播
window manager 打开失败。page 可通过 `my_navigator_wm_add_page_owned()` 转移 factory context
所有权，析构时恰好释放一次；也可通过 `my_navigator_wm_add_page_lease()` 绑定可失效的
factory context lease。lease 失效后尚未开始的 factory 会被跳过，已经进入的 factory
可以自然完成；普通、ASan 和 Clang TSAN `test_myui_mvvm` 均通过 **43/43**。
同步 `my_navigator_request()` 仍是调用方串行化的弱引用 API；页面 factory 若重入销毁
navigator，销毁会延迟到最外层 request 返回，默认注册立即失效，当前请求停止后续
window-manager 操作。通用默认 navigator 的跨线程注册/替换和 loop 销毁与 producer 并行
仍需宿主遵守生命周期协议。

## 本轮补充：拥有上下文的 UI command 调度（2026-09-05）

新增独立于冻结 PAL vtable 的 `my_ui_command_t` sidecar。command 以显式
`execute/context/destructor` 创建，提交时只向既有 `post_event` 投递一个拥有引用的
command 事件；同一 command 不能重复入队，取消与回调重入均由原子状态机处理。command
只在 PAL loop 线程执行，执行后或 loop 销毁丢弃队列时均恰好释放一次 context；提交失败
会释放队列引用并恢复为可重新提交状态。该设计不改变任何渲染后端或 PAL vtable ABI，
Break 与 dummy 后端共享事件 payload 回收协议。

TDD 覆盖 Break/dummy 执行一次、重复提交、取消、loop 销毁回收，以及 command 回调重入
关闭窗口和无窗口 manager 执行；`test_myui_break_pal` **23/23**、
`test_myui_window_manager` **168/168** 通过。window/manager 现在各自提供可保留的
command scope：关闭时取消尚未执行的任务，重新打开 window 时恢复 scope；调用方仍须保持 loop 对象存活到所有提交
完成；command context 中的 widget/window/manager 仍是调用方借用关系，需由调用方在
关闭前取消或使用外部引用/专用 lease 保活，不能把 command API 误解为通用 borrowed
pointer 自动失效机制。

## 本轮补充：PAL 并发事件投递与 IME 所有权（2026-09-05）

`my_pal_main_loop_post_event()` 的跨线程保证现在在 Break 和 dummy 两个后端统一实现：生产者在
loop 对象仍存活时可并发入队，队列使用锁保护的 O(1) 链式 FIFO，分配和 IME 字符串复制均发生在
锁外，消费端在 loop 线程按队列顺序派发。dummy 不再使用 `darray` 的头部删除，因此 burst 或多
生产者负载不会出现 O(n) 出队搬移或扩容临界区。

`IME_PREEDIT` 和 `IME_COMMIT` 的文本为队列所有的深拷贝，投递返回后调用方可立即修改其原始
buffer；`MY_EVENT_USER.data` 仍是调用方借用，不提供隐式所有权或析构。loop 销毁会释放未派发的
IME 复制文本；销毁与生产者并发不属于 API 契约，调用方必须先停止/等待所有生产者。

TDD 覆盖 Break/dummy 的四生产者并发投递和 IME 快照，普通、ASan 和 Clang TSAN
`test_myui_break_pal` 均为 **17/17**；普通/ASan `test_myui_window_manager` 仍为 **161/161**。
排除网络、网络复制和 Vulkan 宿主限制后 CTest **96/96** 通过。GNU TSAN 因当前机器缺少
`/usr/lib64/libtsan.so.2.0.0` 无法链接，未作为通过证据。

该阶段不改变 UI 线程亲和性：widget、window manager、dialog 和 timer 的直接调用仍必须在所属
主循环线程完成。拥有上下文的跨线程 UI command API 已通过独立 sidecar 实现，不破坏冻结
PAL vtable，并定义了 manager/window scope 关闭期间的任务析构语义；后续仍需完善通用
lease/borrowed-pointer 失效协议，不能把 command scope 当作所有异步指针的自动保活机制。

## 本轮补充：UI command dispatch 线程闸门（2026-09-07）

此前 `my_ui_command_dispatch()` 虽由 PAL handler 使用，但公开入口本身缺少当前 loop
上下文证明，外部线程可以绕过提交路径直接调用。现在 command 记录目标 loop，PAL
事件泵在 handler 前后建立内部、线程局部的 dispatch token；无 token 或 token 属于另一
个 loop 时 dispatch 直接跳过，合法事件仍只执行一次。token 仅位于内部头文件，不扩展
冻结 PAL vtable，正常 command 提交和执行不增加锁、堆分配或渲染热路径开销。

TDD 新增直接 dispatch 与错误 loop 的负向回归，以及公共/内部头文件边界契约；
`test_myui_break_pal` **29/29**、`test_shader_io` **26/26**、`test_myui_window_manager`
**235/235** 和 `test_myui_mvvm` **43/43** 通过。通用 borrowed pointer 自动失效、真实
宿主 UI 线程调度和平台 runtime 矩阵仍需后续验证。

## 本轮补充：窗口关闭通知与 popup 生命周期收口（2026-09-05）

窗口管理器现在在移除窗口时先发布一次 close 通知，再解绑窗口的 loop、动画管理器和
manager 借用状态。通知列表采用 ID 记录，回调执行前摘除当前记录，因此回调中注销、添加或
触发其他生命周期操作不会重复调用；窗口最终销毁也会幂等清理剩余记录。窗口关闭后重新入栈
会重新启用该通知状态。

菜单 popup 与 dialog 都使用该协议：菜单关闭时取消 hover timer、销毁 overlay 并清空
`overlay/box/win/wm`，dialog 清空 modal/manager 借用状态并移除 manager listener。这样即使
调用方保留 window creator 引用，关闭后推进主循环也不会触发悬空菜单 timer 或 dialog 回调。

TDD 新增外部持有 window 引用时的菜单关闭、关闭后重开和 dialog 直接关闭回归；普通及 ASan
`test_myui_window_manager` 均为 **161/161**，普通及 ASan `test_myui_mvvm` 均为 **17/17**。
排除网络、网络复制和 Vulkan 宿主限制后 CTest 为 **96/96**；X11 runtime 测试因当前无
display 按标准 skip。

仍未实现的边界是跨线程 UI 操作、通用 borrowed pointer 自动失效、callback context 所有权
租约，以及真实宿主上的 GPU/IME/present/buffer-age 全平台 runtime 证据；当前 API 继续要求
所有 UI 生命周期操作在所属主循环线程执行。

## 本轮补充：Dialog manager 失效协议（2026-09-05）

dialog 打开时登记 window manager 销毁监听，正常关闭、打开失败和 dialog 销毁都会注销。
如果 manager 先销毁，监听回调会清空 dialog 的 borrowed manager 指针和 listener ID；
dialog 随后关闭或释放时不会再访问已释放 manager。dialog window 仍由自身 creator 引用
独立保活，manager 的栈引用释放后不会改变 window 的最终销毁责任，也不形成循环所有权。

TDD 新增 manager-first teardown 回归；普通及 ASan `test_myui_window_manager` 均为
**154/154**。当前仍未提供跨线程 UI 操作、回调上下文所有权和通用 borrowed pointer
自动失效保证；调用方必须在所属主循环线程管理 dialog、window 和 manager。

## 本轮补充：Menu 子模型独立销毁协议（2026-09-05）

`my_menu_destroy(submenu)` 现在会先关闭子模型的 popup/timer，再从父模型摘除对应的
submenu item，并清空父模型的 `open_sub`；父菜单之后继续操作或销毁时不会保留已释放的
子模型指针。父模型递归销毁使用内部路径，避免把已经摘链的子模型再次释放。

TDD 新增独立 submenu 销毁及已弹出 submenu 销毁回归；普通及 ASan
`test_myui_window_manager` 均为 **156/156**。
菜单选择 callback 上下文仍是调用方借用数据，跨线程模型修改和通用 callback lease
仍未实现，调用方必须在所属 UI 主循环线程操作菜单模型。

## 本轮补充：Menu manager-first 销毁（2026-09-05）

菜单 popup 现在登记 window manager 销毁监听；manager 先销毁时，overlay 随窗口树销毁并
清理 hover timer，同时清空菜单的 `overlay/box/win/wm` 借用关系。正常关闭、弹出失败和
模型销毁路径都会注销监听，manager-first teardown 后再次 dismiss/destroy 不访问悬空对象。

TDD 新增 manager-first 菜单销毁回归；普通及 ASan `test_myui_window_manager` 均为
**157/157**。菜单 callback 上下文仍由调用方保持有效，跨线程模型修改仍未提供支持。

## 本轮补充：List adapter 重入边界（2026-09-05）

`list_view` 同步可见行时进入保护状态并临时保活自身；adapter 回调内再次刷新、换
adapter、改滚动位置、改行高或换绑 scrollbar 均返回 `MY_RET_PENDING`，避免递归破坏
active/pool。scrollbar 反向同步也有 guard，正常路径不增加分配或逐帧扫描。

TDD 新增 adapter 重入回归；普通及 ASan `test_myui_window_manager` 均为 **159/159**。
adapter 仍为借用 vtable/实例，跨线程修改必须由所属 UI 主循环串行化，未提供自动同步。

## 本轮补充：Closed window 借用状态失效（2026-09-05）

`my_window_manager_close()` 现在先用临时引用保护 window，让 destroy chain 在有效 loop/
animator manager 上取消 tooltip、node-view flow 和 button timer；如果调用方仍保留 window
引用，关闭完成后才清空 `wm/loop/anim_mgr`，避免外部继续调用时看到悬空 manager。manager
整体销毁沿用同一顺序。

TDD 新增 closed-window borrowed-state 回归；普通及 ASan `test_myui_window_manager`
均为 **158/158**。跨线程 close、异步 callback 上下文所有权和全局 weak-reference
自动失效仍未实现。

## 本轮补充：节点视图通用移除生命周期（2026-09-05）

widget 树新增可选的父节点级 `child_removed_hook`。回调在直接 child 的 `parent` 清空前
执行，既不改变已有 `removed_hook` 的 root 语义，也不增加绘制热路径的扫描和分配；相比
扩展公共 vtable，它不会要求所有历史及第三方 vtable 聚合初始化器同步改写。

`node_view` 通过该回调统一回收节点模型的弱引用：移除节点会删除所有相关 link，清除
selection、selected/drag/preview/magnet/embedded-grab 状态，并停止不再需要的 flow timer。
标准节点删除和调用方直接 `my_widget_remove_child(view, node)` 的行为一致。view 销毁前还
会解除节点的反向 `view` 指针，使外部保留的 node 引用仍可安全查询和销毁。

TDD 新增通用移除及外部保留节点用例；普通和 ASan 定向测试均为 **152/152**。当前边界
仍是显式覆盖的 node-view 关系；菜单、MVVM、自定义控件及其他借用指针关系仍需逐项定义
失效协议，不能据此宣称所有 weak reference 自动安全。

## 本轮补充：MVVM target 与 CloseWindow 生命周期（2026-09-05）

`my_widget_target_t` 改为持有 widget 的 target-lifetime 引用。绑定期间调用方释放 creator
引用或把 widget 从树中移除，都不会让 VM listener 访问悬空控件；目标销毁时释放该引用，
不引入 widget 与 binding context 的循环所有权。items binding 的 list 分支改用真实
`my_list_view_is_instance()`，不再让可写 `widget_type` 决定是否强转访问 list 私有结构。

`CloseWindow=true` 的额外 click listener 由 MVVM context 保存 `(widget, listener_id)`，
上下文销毁前注销；绑定中途失败会回滚已安装的 listener。普通及 ASan
`test_myui_mvvm` 均为 **14/14**。跨线程绑定变更、通用 binding target 自动失效和窗口
manager/导航器的完整弱引用失效协议仍需独立的 owner/lease 设计。

## 本轮补充：Navigator 默认注册生命周期（2026-09-05）

默认 navigator 注册仍是弱引用，但新增 `my_navigator_clear_default(nav)` 条件清除。
`my_navigator_wm_destroy()` 在释放页面表前解除自身注册；如果期间已安装新的默认
navigator，旧实例销毁不会覆盖新实例。销毁后请求返回 `MY_RET_NOT_FOUND`，不访问已释放
对象。普通与 ASan `test_myui_mvvm` 均为 **15/15**；跨线程注册/请求并发仍需独立同步
协议，当前 API 不承诺并发安全。

## 本轮补充：组合控件和窗口栈事务边界（2026-09-05）

`scroll_view` 的 opaque API 不再只依赖 NULL 判断：所有入口使用真实 vtable 校验，
普通 widget 强转不会访问私有字段。替换内容遵循候选提交，先尝试挂载新 child，成功后
才移除旧 child；挂载失败保留原内容、滚动位置和 scrollbar 同步状态。

窗口 manager 现在拒绝重复打开同一窗口。dialog 同样拒绝仍打开的实例；如果 manager
拒绝打开，dialog 会回滚前置窗口 scrim、modal 标志、callback 与 borrowed manager 指针。
list adapter 必须提供 count/create/bind 回调，替换 adapter 时会销毁旧活跃与池化行并
丢弃动态高度缓存，避免不同 row 私有约定交叉；非法动态高度使用固定行高回退。动态
prefix sum 使用显式 `int64_t` 存储，不受 32 位指针宽度影响，超大 count/高度采用饱和
计算，回收池 OOM 会释放临时保活引用。

TDD 当前 `test_myui_window_manager` **157/157**。adapter 仍是借用指针，调用方必须在
绑定期间保持其 vtable 与实例有效；跨线程 adapter 变更与通用对象弱引用自动失效仍是
后续架构工作。

## 本轮补充：widget 专用 API 类型与节点模型边界（2026-09-05）

专用 widget API 现在使用真实 vtable 指针进行 O(1) 实例识别，而不是信任可写的
`widget_type` 字符串。编辑器、文本区、节点、节点视图、富文本标签以及已覆盖的
checkbox/slider 等入口在访问派生字段前完成校验；错误查询返回中性值，错误写入不
改变对象状态。节点视图的连接模型还要求两个节点都是当前 view 的直接子节点，且
输出/输入方向和 slot 均在模型范围内；因此跨 view link、错误方向和越界 slot 在绘制
前就被拒绝。socket 几何输出指针为空时也不会写入。

TDD 新增普通 widget 专用 API 查询/写入回归及节点模型归属回归，当前
`test_myui_window_manager` 为 **144/144**。本轮只覆盖已审计公开入口；通用 weak
引用、所有历史控件 API 和第三方自定义 widget 的生命周期仍不应被推断为自动安全。

## 本轮补充：滚动条绑定类型边界（2026-09-05）

三个滚动容器的绑定入口现在在注册 listener 前验证目标确实是
`my_scroll_bar`；scrollbar 自身的 value/page-size 读写入口也执行同一实例校验。
普通 widget、伪造的 widget 类型和 NULL 以外的非法对象都会被拒绝，已有合法绑定保持
不变；这样避免后续同步路径把任意 widget 强制转换为 scrollbar 而产生未定义行为。TDD 新增拒绝及不换绑回归，普通
`test_myui_window_manager` 当前 **141/141** 通过。绑定现在持有一个非循环的 link
reference，调用方释放自己的最后一个引用后 scrollbar 仍可安全工作；解绑和容器析构
会释放该引用。通用 weak-reference 自动失效仍属于其他对象关系的后续架构工作。

## 本轮补充：CSS `@layer` 解析期级联（2026-09-05）

新增有界 `@layer` block、逗号层序声明、嵌套层及晚到层序重排。规则保存层
rank，theme bridge 在解析期按层顺序稳定提交；未分层 CSS 最后提交，仍保留
既有 selector specificity 与源码顺序语义。层名、层数量和嵌套深度均受固定
预算约束，重复、空、超长和 malformed layer 输入在分配规则前拒绝。

TDD 覆盖层级压过 selector specificity、未分层规则优先、显式层序、晚声明
层序、capability registry 和非法层名；另增加有界 `@import` resolver、循环检测、
共享总预算、路径安全和失败事务测试；另加入受限 `@scope root { ... }` 到固定祖先
路径的映射，`test_myui_css` 当时为 **82/82** 通过；该段为历史记录，当前能力以文档
顶部的 `@scope to` 记录和实现状态矩阵为准。

## 本轮补充：CSS `@scope` 根选择器与 at-rule 组合（2026-09-06）

`@scope` 根选择器现在支持带类型、class、id、通配符以及省略根的形式。省略根不额外
增加祖先约束；其他形式统一映射到既有固定祖先路径，因此主题查询仍无需解析 CSS，且
不增加绘制热路径分支。`@scope` 可与 `@media`、`@supports` 和 `@layer` 有界嵌套组合，
解析期同时传递媒体匹配、supports 结果、层级 rank 和 scope ancestor，不改变已有
事务性失败行为。

TDD 新增 class/id/universal/implicit root 匹配、主题祖先匹配和四层 at-rule 组合回归；
当时普通 `test_myui_css` **99/99** 通过；selector list 已在本文顶部后续记录完成。带
组合器的复杂 CSS Scoping `to` selector、复杂条件 at-rule 组合和真实平台 runtime 仍
属于未完成边界。

## 本轮补充：profile-aware SA callback 接入 paragraph（2026-09-05）

补齐 SA dictionary profile 的实际语义透传：新增
`my_line_break_apply_dictionary_profile()` 和
`my_text_paragraph_process_n_break_profile_callback_ex()`。旧
`my_line_break_dictionary_fn` 与旧 paragraph 入口保持 ABI/行为兼容；新
callback 在每个连续 SA run 收到已校验的 version/locale profile，paragraph
换行直接消费该 callback 的边界结果。输入 scalar、profile、预算和 run
长度在回调前统一拒绝，固定栈 scratch 成功后提交，失败不污染原边界。

TDD 新增 locale 透传、未知版本、预算拒绝、失败回滚和真实 paragraph
换行用例；`test_myui_text_layout` **122/122** 通过。该能力仍是词典接入
契约，不内置 Thai 或其他语言词典；locale-specific UAX#14 tailoring、
产品级 SA dictionary 数据、版本化语言 golden corpus 仍未完成。

## 本轮补充：内置 Thai SA 基线词典（2026-09-05）

新增固定只读 Thai (`th-Thai`) 小型词典 corpus，以及可直接接入 paragraph
profile callback 的适配器。实现只使用静态表和固定栈 scratch；先验证整个
SA run 可由已知词完整覆盖，再按最长匹配提交边界。未知词、部分匹配、非法
scalar、超长 run 和不支持 locale 均不会产生猜测断点，失败也不污染输入边界。

TDD 新增支持矩阵、最长匹配、未知词保守回退和输入事务性测试；
`test_myui_text_layout` 当前 **124/124** 通过。该 corpus 只是跨平台确定性
fallback，不是完整 Thai 词典；locale-specific tailoring、完整语言 corpus
和产品级词典质量仍保留在未完成项中。

## 本轮补充：滚动条监听生命周期收口（2026-09-05）

修复 `scroll_view`、`list_view` 和 `text_area` 链接外部 `scroll_bar` 时未保存
listener ID 的架构缺陷。重复绑定不再累积 `changed` 回调；换绑、传入 `NULL`
和控件析构都会移除旧监听，新增监听失败则保留旧连接。绑定连接持有一个非循环的
link reference，解绑或控件析构时释放；调用方不需要为活动连接额外保留 bar 引用。

TDD 新增三个滚动容器的重复绑定、析构后滚动条事件、解绑和外部引用先释放回归；普通及
ASan `test_myui_window_manager` 均为 **141/141** 通过。

## 本轮补充：跨字体组合簇段落断行与回归（2026-09-05）

paragraph wrap 现在以字体 shaping 返回的 cluster 边界作为不可拆分边界；跨 face 的
combining cluster 不会在附加符号前被拆到下一物理行。新增 Cantarell/Noto Sans 回归，
使用 `a + U+0305 + b` 验证窄宽度下前两个 codepoint 保持同一行；测试输入同时修正为
相邻字符串字面量，避免 C 编译器把 `\\x85b` 误解析为越界十六进制转义。

本轮同时完成冷却按钮、paragraph mapping、字体 provider 直调和 RHI 质量事务的架构审计：
按钮非冷却状态不创建 timer，冷却状态最多一个 timer，单调时钟查询不依赖 timer 存在；
paragraph line-layout cache 保持固定 4 槽并在 OOM 时保留旧缓存；RHI sample-count 仍采用
`create -> validate -> submit -> activate -> retire` 事务，失败不触碰 active resource。
审计未关闭以下边界：跨物理段落增量 visual rebreaking、完整跨 face GSUB/GPOS 上下文、
locale-specific UAX#14 tailoring、完整 CSS at-rule 语义和真实宿主 retained-buffer runtime。

验证结果：默认 `test_myui_font` **66/66**、`test_myui_text_layout` **119/119**、
`test_myui_window_manager` **138/138**，完整 CTest **99/99**；ASan 字体/文本分别
**66/66**、**119/119**，STB-only 字体/文本分别 **66/66**、**119/119**。
`git diff --check` 与乱码扫描通过。

本阶段还补齐 FreeType/STB direct `measure` vtable 的 4 MiB 有界输入校验，并将 ZWNJ 纳入
字体链 cluster 归属；绕过公共 measure 包装层也不会无界读取，阿拉伯连接控制符不会单独
切换 face。新增回归后字体测试为 **66/66**。

## 本轮补充：RTL OpenType GSUB/GPOS golden（2026-09-05）

新增 Noto Sans Arabic/Hebrew 真实字体 golden，验证 RTL glyph 顺序、byte cluster、26.6
advance、face identity 和 `used_complex_shaping`。TDD 先暴露 provider 清空结果时丢失
`rtl` 标志，随后在 FreeType provider 与公共 `my_font_shape_ex()` 提交边界恢复该字段；
字体测试当前为 **66/66**，并加入同一 Arabic variable font 的 300/900 weight advance
golden。当前证据限定在单一字体、单一 RTL run，跨字体 token shaping、
跨物理段落 visual rebreaking 及更完整 language/feature corpus 仍未完成。

本阶段同时收口字体链 `shape_ex` vtable 直调边界：入口会清零结果、校验 4 MiB 文本和
shaping 参数，并保留 RTL 标志；新增直调 provider 回归后字体测试为 **61/61**。这只
解决 provider 生命周期/输入安全问题，不代表已实现跨 face 的上下文 token shaping。

本阶段补齐跨 face grapheme cluster 归属：combining mark、variation selector、emoji
modifier、tag 与 ZWJ sequence 不再按 codepoint 断开；链在冷路径先选择可覆盖整个 cluster
的 face，再保留原有按 face run shaping 的提交顺序。Cantarell/Noto Sans 的 `a + U+0305`
和 Cantarell/Noto Color Emoji ZWJ golden 已覆盖；measure 宽度也改为沿同一 cluster 的选定
face 累加，避免附着 mark 被重复计宽，字体测试为 **64/64**。跨 face 的完整
GSUB/GPOS 上下文协商、locale presentation 与 token shaping 仍属于后续工作。

## 本轮补充：OpenType language-system golden（2026-09-05）

新增真实 FreeType/HarfBuzz `locl` golden，验证 Source Code Pro 在 `cyrl` 下按 `ru` 与
`sr` 选择不同 glyph（`795`/`871`），并锁定 byte cluster、advance 与失败清理契约。
测试按像素字号验证 advance，不依赖 `hb-shape` 的 design-unit 输出；普通与 ASan
`test_myui_font` 均通过，当前为 **66/66**。这只证明已接入的 language-system 选择路径，
不等同完整 OpenType language feature 规划、跨字体 variation 或复杂 RTL GSUB 完成。

## 本轮补充：Redis 8.10.1 依赖验证（2026-09-05）

此前 Redis 依赖缺口已用 `/home/timeshift/opensource/redis-8.10.1` 的未修改
`deps/hiredis` 打通：CMake 构建私有静态客户端并保持公共 ABI 不暴露 hiredis 类型；真实
`127.0.0.1:6379` 服务上的 timeout probe、prefix URL roundtrip 及完整 Redis 配置 CTest
均通过，完整回归为 **99/99**。系统客户端缺失时仍按安全契约显式禁用，不静默切换内存后端。

## 本轮补充：FreeType shaping provider 输入边界（2026-09-05）

修复 FreeType/HarfBuzz `shape_ex` vtable 可绕过公共 API 输入预算的问题：provider 现在
独立校验 UTF-8 文本的 4 MiB 有界 NUL、shape 参数，并在任何 HarfBuzz 操作前清空结果。
这样直接 provider 调用不会触发 `hb_buffer_add_utf8(..., -1, ...)` 的无界输入扫描，失败
也不会提交部分 glyph-run。TDD 新增直接 vtable 超限输入测试，`test_myui_font` 为
**56/56**；required-feature 依赖具体字体的用例仍按环境条件显式 skip。

## 本轮补充：EDID/CTA 边界防御（2026-09-05）

X11 RandR EDID 冷路径现在只接受完整的 128 字节 block 序列，并检查
`XRRGetOutputProperty()` 的 `bytes_after`，属性被截断时保持既有 sRGB/unknown 回退。
CTA 解析按扩展事务提交：空扩展和未知 extended tag 不会误报 HDR，HDR Static Metadata
必须包含完整 descriptor 与 EOTF 字段；checksum、block length 或尾部 block 不完整时，
不会保留同一扩展中此前扫描到的部分 HDR 结果。新增 TDD 覆盖上述边界，
`test_platform_display_media` 当前为 **8/8**。

## 本轮补充：Win32 媒体缓存失效与消息防御（2026-09-05）

Win32 runtime TDD 现在覆盖媒体快照在 `WM_SETTINGCHANGE` 后递增代际并重新采集，
以及缺少 suggested `RECT` 的畸形 `WM_DPICHANGED` 消息安全忽略。Win32 源文件以
Windows 11 `DISPLAYCONFIG_DEVICE_INFO_GET_ADVANCED_COLOR_INFO_2` 的数值兼容宏
保持旧 SDK 可编译，并使用 `MONITORINFO` 基类转换满足不同 Windows SDK 的函数原型。
Linux 主机上的 Windows 目标语法检查以 Zig Windows headers、`-Wall -Wextra -Werror`
通过；该检查不替代 Windows runner 上的真实窗口、注册表和 Display Configuration runtime。

## 本轮补充：Wayland 媒体快照缓存（2026-09-05）

Wayland 媒体查询已改为固定快照：首次冷查询组装 pointer/touch/sRGB 事实，后续查询
仅复制固定大小结构，不重复计算；seat capability 变化会在协议事件路径失效快照并
递增饱和媒体代际。代际达到上限时仍会失效缓存，避免饱和后继续返回旧设备事实。
新增 runtime 快照稳定性测试；实现不增加渲染帧、锁或分配。

## 本轮补充：X11 RandR EDID 媒体能力（2026-09-05）

X11 媒体冷路径现在读取当前窗口所属 RandR 输出的有界 `EDID` 属性。共享解析器校验
EDID base checksum 和完整 CTA block，在色度主色接近 Display P3/Rec.2020 时声明对应
gamut；只有 HDR Static Metadata block 明确包含 PQ/HLG EOTF 才声明 HDR。属性缺失、
截断、坏 checksum、未知色度或不完整扩展不会改变既有 sRGB fallback，也不会伪造 HDR。
纯解析 TDD 与 X11 runtime capability 层级断言已加入；Wayland、Win32、Cocoa 的现有
能力策略不受影响。真实 X11 HDR/广色域硬件矩阵仍需在物理显示器 CI/宿主环境验证。

## 本轮补充：Win32 Display Configuration HDR 查询（2026-09-05）

Win32 媒体查询现在通过动态解析 `user32.dll` 的 Display Configuration API，按窗口所在
显示器匹配 active source，再读取 Windows 11 的 `ADVANCED_COLOR_INFO_2`。只有同时得到
当前显示源且系统明确报告 HDR supported、user enabled 和 active HDR mode 时才设置 HDR；
旧版 `ADVANCED_COLOR_INFO` 只表示 WCG/HDR 的混合 advanced-color 状态，因此不用于宣称 HDR。
查询失败、路径变化、旧系统或内存不足均保持 `PLATFORM_MEDIA_KNOWN_HDR` 未知，不把宽色域
或默认显示器能力误映射到当前窗口。结果保存在 `Platform` 快照中；设置/显示器/输入设备
消息只使快照失效，下一次媒体冷查询才重新枚举，正常查询为 O(1) 复制且不产生分配、锁
或图形后端调用。Win32 媒体代际同步递增，样式刷新会重新采集当前事实。Win32 HDR 能力
层级 TDD 已加入 platform runtime 测试。

## 本轮补充：GLX damage-present runtime 门禁（2026-09-05）

新增 `test_rhi_x11_runtime`，在可连接的 X11 环境中真实创建 OpenGL/GLX RHI，关闭测试
vsync，连续执行有界 damage frame，读取后端有效重绘区域并完成 present/destroy 生命周期。
测试同时校验 retained-present 能力必须包含 damage-present 与 buffer-age 两项；无显示服务或
OpenGL/GLX 不可用时返回 CTest 标准 skip，不把缺少驱动误报为通过。当前 X11/Mesa runtime
执行通过；扩展未实际提供时仍验证安全全屏路径，真实 buffer-age 轮转仍需支持该扩展的 GPU/窗口环境。
默认构建完整 CTest 现为 **98/98**，`git diff --check` 通过。

## 本轮补充：damage-present 坐标系收口（2026-09-06）

RHI 的 `RHIPresentRect`、BreakUI scissor 与 damage history 均统一为 drawable top-left
坐标。此前 Wayland EGL damage-present 在最终提交层直接传递 top-left `y`，而 EGL/GLX
damage 扩展要求 bottom-left 坐标，可能让局部提交落在错误区域。现由
`rhi_present_damage_to_bottom_left()` 在 EGL/GLX 调用前一次性转换，固定最多 16 个矩形，
不引入锁、堆分配或 history 热路径扫描；失败则拒绝该 native submit 并由既有保守路径清空
history。TDD 覆盖多区域、原地转换、容量不足和越界输入；`test_rhi_capabilities` 普通、
ASan/UBSan、Clang TSan 均为 **40/40**。

## 本轮补充：X11 媒体能力缓存与设备变化刷新（2026-09-05）

X11 的媒体能力查询现在在 `Platform` 初始化阶段完成一次 XInput2 探测和设备枚举，
后续 `platform_get_media_context()` 只复制已验证快照，不再重复执行协议查询或分配设备
列表。根窗口监听 `XI_HierarchyChanged`，设备层级变化时在事件冷路径刷新
`hover`、`pointer`、`any-pointer` 能力并递增媒体代际；XInput2 缺失、版本不满足或查询
失败时继续使用核心 X11 指针语义。该路径不进入绘制和样式匹配热路径，保留失败回退和
已知位契约；X11 runtime 测试目标现在显式继承 `ENGINE_X11_XINPUT2`，确保增强断言实际
参与编译。默认构建完整 CTest 为 **97/97**，X11 runtime、Vulkan、Wayland 和 YAML-off
定向门禁均通过。真实 X11 设备热插拔事件在 CI 之外仍需宿主环境覆盖。

## 本轮补充：Windows/macOS 系统媒体偏好采集（2026-09-05）

Windows 媒体查询现在在冷路径读取鼠标/触控指标、`AppsUseLightTheme` 和客户端区域动画设置；仅在
原生查询成功时分别设置 `color-scheme` 与 `reduced-motion` 的 known 位，注册表缺失或
系统 API 失败则保持 unknown，不把默认值伪造成事实。macOS 查询窗口 effective appearance
和辅助功能的 reduce-motion 状态，使用同样的 known 契约。Windows 的主题/设置、显示器、
输入设备消息以及 Cocoa backing-property 变化都会递增媒体代际，宿主可据此触发已有的
窗口级样式刷新；查询不进入逐帧绘制热路径。

TDD 增加 Windows 鼠标/触控及原生动画设置一致性测试和 Cocoa 主题/减弱动画 known 位测试；Windows
新增 `advapi32` 显式链接，避免注册表查询依赖隐式链接。Linux X11/Wayland 继续只声明
可稳定证明的 pointer/hover 与 sRGB；X11 在 XInput2 可用时按设备类采集 coarse/fine/hover，
扩展缺失时回退到核心指针语义；macOS Cocoa 还会从窗口当前屏幕的 Color Space 识别 Display P3，
并从系统 EDR selector 识别 HDR；Windows/Linux 的 Rec.2020 仍不在没有明确平台证据时声明。

## 本轮补充：响应式 CSS 媒体事实冷路径刷新（2026-09-05）

窗口现在保存最后一次成功应用 CSS 时的完整媒体快照（逻辑 viewport、screen、颜色方案、
reduced-motion、设备能力和 known 位）。宿主在系统偏好、输入设备或显示能力变化时可调用
`my_window_refresh_media_style()`，窗口管理器可调用 `my_window_manager_refresh_media()`
批量刷新；快照未变化时直接返回 `MY_RET_NOT_FOUND`，不克隆主题、不分配内存、不触碰热路径。
检测到变化后使用现有 `clone -> parse -> apply` 事务，失败保留旧主题和旧快照，成功后一次性
替换并使窗口失效。resize 继续复用同一快照更新路径。Dummy PAL TDD 覆盖 dark/light
切换、窗口管理器批量刷新和无变化短路，窗口管理器测试为 **138/138**。

该接口解决平台事实变化不会自动反映到响应式样式的问题，但不伪造平台事实；X11、Wayland
报告各后端能稳定证明的 pointer/hover、触控与 sRGB，Win32/Cocoa 另外报告成功采集的系统
颜色方案与 reduced-motion，Cocoa 在实际窗口屏幕可验证时报告 P3/HDR。Windows/Linux 的
Linux 的真实 HDR/P3、Windows 的 P3/Rec.2020、完整系统偏好通知和全平台 runtime CI 仍属于后续
工作。窗口管理器的扩展刷新入口会传播 OOM/其他提交错误；BreakUI 只有在
所有窗口刷新成功后确认媒体代际，避免资源压力造成永久不重试。

本轮同时补齐了受限的 CSS `@media not`：`not` 只允许修饰单个媒体特性，已知事实按
布尔值取反，unknown 仍不匹配；与媒体类型、`and` 或逗号查询组合会被严格拒绝。该实现
保持解析期展开，不增加主题查询热路径的分支、锁或分配。CSS 测试现为 **69/69**。

## 本轮补充：RHI 命令缓冲 owner 隔离（2026-09-05）

GL 命令返回当前设备绑定句柄，Vulkan 命令返回 backend 绑定句柄；所有带
`RHICmdBuffer *` 的命令入口都校验句柄、当前设备和活动帧，帧结束、设备切换、NULL 或
错误 owner 均安全丢弃。显式设备参数的间接绘制也拒绝非当前活动设备，Vulkan 内部
uniform buffer 重绑改用真实命令句柄。该方案沿用 O(1)、无锁、无分配的热路径，不改变
冻结 RHI ABI，并阻止旧命令指针把状态写入新设备。

四套配置的 `test_rhi_capabilities` 均通过（当前 **38/38**）；默认配置完整 CTest
**97/97** 通过，`git diff --check` 通过。隐式 `g_current_device`、GL 帧状态和 GL
状态缓存现为线程局部，并在设备切换时失效，因此不同线程不会继承或覆盖彼此的当前设备，
也不会复用另一设备的缓存句柄。每个设备还通过无锁原子 owner 保证从 `frame_begin` 到
`present` 只能存在一个活动帧，线程局部 owner 同时拒绝一个线程重入第二个设备；非 owner
的结束/呈现调用安全忽略，失败路径会释放 owner。
原生上下文仍必须由宿主按线程亲和性管理。真正的多线程并行录制、跨线程提交和多个设备共享队列，仍需
引入显式 command context、queue 和同步协议。

## 本轮补充：RHI 后端入口生命周期审计（2026-09-04）

Vulkan 的公共设备入口现在在访问 backend_data 前执行 NULL-safe 检查，覆盖设备销毁、
resize、frame begin/end/present、frame index、vsync 和 GPU timer 创建；GL/Vulkan 的
uniform location 查询也拒绝 NULL 设备或名称。该修复保持热路径为单次指针判断，不增加
锁、分配或跨后端分支。绑定单元继续由 RHI_MAX_TEXTURE_UNITS == 16 统一约束，Vulkan
image/texture 命令在验证设备、句柄、unit、mip 成功后才修改 pass/barrier 状态。

TDD 新增 NULL uniform 查询与未初始化 Vulkan backend 的 timer 创建回归，并同步到
test_rhi_capabilities。当前仍需复跑四套后端构建和 sanitizer 定向门禁；跨设备句柄
复用仍是明确禁止的使用契约，因保持现有两字段句柄 ABI，尚未引入设备 cookie。

## 本轮补充：RHI 句柄设备隔离（2026-09-04）

资源池代际序号现由进程级原子单调计数器分配，而不是每个设备独立从相同初值生成；这样
在不改变两字段句柄 ABI、句柄大小和后端热路径的前提下，阻断相同索引/代际组合在多个
设备间误命中。销毁后的旧句柄仍由 `alive` 和代际校验拒绝，槽位复用只产生新的进程级
代际。TDD 已在四套 RHI 构建覆盖跨设备误用和陈旧句柄；未来如需支持句柄跨进程传输，
仍必须引入显式设备 cookie/导入导出协议，当前 API 不提供该语义。

> 当前状态说明（2026-09-04）：本文前部按时间倒序保留阶段记录，早期记录中的测试计数和“首个差异/约 1511 项差异”是历史观测，不代表当前基线。当前 Unicode 17 `LineBreakTest.txt` 已通过 **60,487/60,487** 个边界；仍未完成的是 locale-specific tailoring、SA dictionary 产品策略、完整各平台 runtime CI（X11/Wayland smoke 已接入）、完整 RTL GSUB/跨段落重排及完整 CSS at-rule 语义。

## 本轮补充：text-area 单行 wrapped 增量重排（2026-09-04）

wrapped text-area 的局部编辑现在在物理行数量不变且未启用折叠时只重排编辑所在物理行，
并复用后续物理行的 visual-line 对象；后续行的相对 byte/CP 范围不受影响，不再重复
shaping。候选 visual-line 数组仍采用提交前隔离、成功后一次切换的事务策略，OOM 或
边界错误不会破坏旧 cache。插入/删除导致物理行数量变化、折叠或宽度/字体变化时仍
退回全量安全重建。TDD 已验证后缀指针稳定、changed-row-only shaping、尾部空物理行复用、
连续空行、末行编辑和跨行删除；普通/ASan `test_myui_window_manager` 为 **134/134**。

空文档、尾部空行和连续空行由 paragraph 的零长度 visual-line 表示，并已覆盖单行增量
路径，避免旧 cache 的物理行数推断因最后一行为空而失真。候选数组转移仍是一个需要持续
故障注入覆盖的事务边界；后缀 darray 扩容失败、配置变更和复杂 RTL 跨段落重排继续走保守
全量路径，不将这组局部 TDD 宣称为完整跨段落重排。

## 本轮补充：SA dictionary profile 契约（2026-09-04）

新增版本化 SA dictionary profile：`version == 1`，locale 为最多 64 字节的有界 ASCII
BCP-47 风格子标签。底层 `my_line_break_apply_dictionary_ex()` 与 paragraph profile
入口在 callback 和对象分配前执行统一校验；旧三字段 options 和旧入口保持兼容，避免
通过扩展公开结构破坏 ABI。非法版本、空子标签、非法字符和超长 locale 均安全拒绝，
profile 与 dictionary callback 不成对时同样拒绝，
TDD 已覆盖成功透传、失败回滚和非法 Unicode scalar 拒绝，文本布局测试当前为 **118/118**。

该 profile 是词典 tailoring 的身份/配置门禁，不是内置词典，也不代表已经完成 locale
词典质量、版本化 golden corpus 或产品级语言策略；这些仍保留在未完成矩阵中。

本轮新增 `verify_myui_sa_dictionary`：它复用正式 YAML parser 读取有界 fixture，检查 `version`、
BCP-47 风格 `locale`、SA scalar 序列、最大 run 预算和 boundary golden，并通过独立的确定性
callback 回放。正例、未来版本、非法 Unicode scalar、非法 locale 和 golden mismatch 已注册
为 CTest 负向门禁。fixture
故意只覆盖三字符 Thai smoke run，用于验证接入契约而非伪造产品级词典；后续仍需由语言
策略提供真实词典实现、Unicode/UCD 版本、词典版本和多语言 golden corpus。

## 本轮补充：媒体 provider 并发注销生命周期（2026-09-04）

媒体快照查询现在持有固定 slot token；注销立即阻止新查询，但不会复用或释放仍在途
查询持有的 provider context，最后一个查询退出后才延迟回收。该路径不忙等、不改变
冻结的 PAL ABI，普通与 ASan 并发回归均通过。

## 本轮补充：冷却按钮键盘激活与严格断行验证（2026-09-04）

冷却按钮的焦点键盘路径现以 `Return`/`Space` 的成对 `key_down`/`key_up` 状态驱动，
避免重复按键、错键释放、焦点切换和指针/键盘混合输入造成重复 click 或永久 pressed；
计时仍由 PAL 单调时钟和唯一 16ms 动画 timer 驱动。`test_myui_window_manager` 当前为
**127/127**，普通、STB-only、YAML-off 和 ASan 定向构建均通过。

同时新增严格 `LineBreakTest.txt` 验证器和正反例 CTest。它保证语料解析和失败报告可复现，
但不改变断行热路径；完整 UAX#14 的 East Asian/locale tailoring、SA dictionary golden
corpus、组合标记全上下文及全部规则交互仍未实现。

## 本轮补充：Unicode 17 断行严格语料验证器（2026-09-04）

新增 `verify_myui_line_break`，严格解析 `LineBreakTest.txt` 的 UTF-8 marker，校验 Unicode
scalar value、单行预算、marker 数量和尾部内容，并通过 `my_line_break_state_feed()` 验证每个
边界。正例、断行不匹配和代理项畸形输入均由 CTest 锁定。该工具只增强验证链路，不改变运行时
热路径；完整 UAX#14 的 East Asian/locale tailoring、SA dictionary golden corpus 及全部
规则交互仍未完成，不能把“验证器可用”解释为“实现已完整”。本机 Unicode 17 官方语料
当前已通过 **60,487/60,487** 个边界；本节是验证器建设阶段的历史记录，后续工作聚焦
locale tailoring、SA dictionary golden corpus 和真实平台策略。

## 本轮补充：扩展图形范围的生成与规则校准（2026-09-04）

已完成 Unicode 17 `Extended_Pictographic ∩ Cn` 范围生成，并按显式 `Line_Break=ID`
拆分为 `ID_ExtPictUnassigned` 与 `XX_ExtPictUnassigned`。运行时采用静态有序范围二分
查找，不读取外部数据、不分配、不加锁；`ID/XX × EM`、Hangul/HL/SA/HY/HH/NU/IS
前置规则已加入 TDD 回归。文本布局测试为 **105/105**。

仍未完成：locale-specific tailoring、组合标记的产品级语言策略、SA dictionary
golden corpus，以及真实平台语言策略；默认 Unicode 17 官方语料的零差异验证已经
完成，不能把历史阶段的诊断数字继续作为当前状态。

## 本轮补充：Unicode 17 断行边界优先级校准（2026-09-04）

TDD 先加入 `QU → CB`、Hangul/SA、`HY/HH → SA`、数字分隔符/Hangul、
`ID_ExtPictUnassigned × EM`、`OP`、`XX_ExtPictUnassigned` 和 `RI` 回归，再以最小
固定规则修复。对象边界、Hangul、复杂脚本和扩展图形判断均保持 O(1)、无分配、无锁，
不进入任何 PAL/RHI 后端分支。普通文本布局为 **105/105**。

官方 Unicode 17 完整语料仍约有 1511 项诊断差异；这些差异不能简单用类别二元规则消除，
后续需分别建设 East Asian/locale tailoring、组合标记完整上下文和 SA dictionary
golden corpus，当前实现继续明确为可移植实用子集。

## 本轮补充：Unicode 17 SP 后 IS/QU 断行例外（2026-09-04）

已根据官方 `LineBreakTest.txt` 修正 `SP × IS`（空格与逗号等 `IS` 不断）、`SP ÷ NS`
（U+3005/U+203C 可断），并保留
`SP ÷ opening-QU/neutral-QU` 与 `SP × closing-QU` 的差异；ZWJ 和 emoji modifier 继续按 LB18 在
`SP` 后可断。TDD 回归已在普通、Sanitizer、STB-only、
无 BiDi 四个文本布局变体中通过，均为 **103/103**；核心 MyUI CTest 为 3/3。闭合标点
后的空格上下文已覆盖 `CL/CP/EX/IS` 到 `NS/CJ` 的 LB16 不起行约束，`SY` 不被过度纳入。
emoji modifier 仅与 `EB` 保持连续，普通字符与 `EM` 可断。完整
LB4–LB6 硬换行方向和 CRLF 原子性也已锁定。完整
`B2 → VF/VI` 与 `CB` 对象优先级也已锁定。完整
普通 combining mark 与 `CB` 的附着边界也已锁定。完整
UAX#14 golden corpus、locale tailoring、SA dictionary corpus 和全部规则交互仍未完成。

## 本轮补充：Unicode 17 SP 后 CM/GL 解析优先级（2026-09-04）

`SP` 后的 combining mark、Unicode glue 和 `VF` 现在按 LB9/LB18 允许断行，同时继续
保护硬断行、ZWSP、WJ/ZWJ、引号、闭合标点和 `NS/SY`；开括号后的消费型空格仍由
streaming 状态保持连续。实现保持固定类别检查、O(1)、无分配、无锁。TDD 扩展空格后
类别回归，普通 `test_myui_text_layout` 为 **102/102**；完整 UAX#14 交互和官方 golden
corpus 仍属于未完成矩阵。

## 本轮补充：Unicode 17 Hebrew HL 类别覆盖（2026-09-04）

Hebrew 上下文判定现在直接复用生成表的 `MY_LB_HL`，覆盖 FB1D–FB4F 兼容 Hebrew 字形，
不再依赖只覆盖基本 Hebrew 区段的手写范围。solidus、maqaf 和引号规则保持既有语义，
实现仍为 O(1)、无分配、无锁。TDD 新增 FB1D solidus 回归，普通
`test_myui_text_layout` 为 **102/102**；完整 UAX#14 golden corpus 仍属于未完成矩阵。

## 本轮补充：Unicode 17 空格后置断行优先级（2026-09-04）

断行器现在在 `SP` 后按 Unicode 17 LB18 优先级处理 `BA/IN/CJ/HH/HY/BB/B2` 等类别，
避免目标类别的前置禁止规则错误覆盖空格后的断点；`SY`、闭合标点、`NS`、引号、ZWSP、
组合标记和硬断行仍保持各自保护语义。实现保持固定类别检查、O(1)、无分配、无锁。TDD
新增空格后类别回归，普通 `test_myui_text_layout` 为 **102/102**；完整 UAX#14 交互和
官方 golden corpus 仍属于未完成矩阵。

## 本轮补充：Unicode 17 Indic virama 跨组合标记状态（2026-09-04）

流式状态机现在在 `VI`（combining mark）提前返回前保存 virama 上下文；后续连续普通
组合标记继承该状态，直到下一个非组合字符到达后重置。这样
`AK/AS/DottedCircle VI CM* x AK/DottedCircle` 不会错误产生断点。实现保持固定状态、
O(1)、无分配、无锁。TDD 新增跨两个组合标记回归，普通 `test_myui_text_layout` 为
**99/99**；完整 LB28 交互和官方 golden corpus 仍属于未完成矩阵。

## 本轮补充：Unicode 17 BB 前置断行类别（2026-09-03）

生成器现在保留 UCD `BB` 为独立类别 `MY_LB_BB`，不再将其错误折叠为 `HY`。BB 前方可
断、后方不可断，不会继承 HY 的后置断行语义；`BA/HY/B2` 仍按各自方向处理。实现保持固定类别查找、
O(1)、无分配、无锁。TDD 新增 BB 边界回归，普通 `test_myui_text_layout` 为 **99/99**；
完整 UAX#14 交互和官方 golden corpus 仍属于未完成矩阵。

## 本轮补充：Unicode 17 B2 双向断行类别（2026-09-03）

生成器现在保留 UCD `B2` 为独立类别 `MY_LB_B2`，不再折叠成只允许断在后方的 `HY`。
因此 U+2014、U+2E3A 等 B2 字符前后均可断；连续 B2 以及 `B2 SP* B2` 继续由 LB17 保护。实现保持
固定类别查找、O(1)、无分配、无锁。TDD 新增 B2 方向性与空格上下文回归，普通
`test_myui_text_layout` 为 **99/99**；完整 UAX#14 交互和官方 golden corpus 仍属于
未完成矩阵。

## 本轮补充：Unicode 17 LB25 数字状态覆盖（2026-09-03）

流式断行状态机现在以生成的 `NU/IS/SY` 类别识别所有 Unicode 数字、数字分隔符和
solidus，不再只依赖少量手写数字范围；指数和数字运算符状态因此覆盖 Devanagari、数学
字母数字等 UCD `NU` 字符。实现保持固定状态、O(1)、无分配、无锁。TDD 新增跨脚本数字
状态回归，普通 `test_myui_text_layout` 为 **96/96**。完整 LB25 交互、locale tailoring
和官方 golden corpus 仍属于未完成矩阵。

## 本轮完成：Unicode 17 Indic LB28 定向断行（2026-09-03）

断行器不再将 `AP/AK/AS/VF/VI` 视为通用 alphabetic run。UAX#14 LB28.11--LB28.14
改为明确的方向性匹配：`AP x AK/AS/DottedCircle`、
`AK/AS/DottedCircle x VF/VI` 和流式
`AK/AS/DottedCircle VI x AK/DottedCircle` 保持不可断；反向或无 virama 上下文的
`AK x AP`、`AK x AK`、`AK x AS`、`AS x AK` 允许断行。实现只复用既有 starter，
每个 codepoint 为 O(1)、无分配、无锁。

TDD 从官方 Unicode 17 `LineBreakTest.txt` 选取 Kawi、Balinese、Batak 样例锁定
方向性和跨 Latin 边界，普通 `test_myui_text_layout` 为 **98/98**。完整 golden corpus、
locale tailoring 与 SA dictionary corpus 仍在未完成矩阵中。

## 本轮完成：STB CFF/CID 深层边界安全（2026-09-03）

STB CFF 路径现在在解析前验证 CFF header 和连续 INDEX 的范围、offset size、offset
单调性及末端对象 payload；CFF 表在目录中被截断时立即失败。vendored STB 的 CFF
buffer 同步改用真实 `CFF ` 表长度，消除原先固定 512 MiB 读取窗口造成的越界风险。
运行期非法 charstring glyph、CID FDSelect 和 INDEX 索引改为安全返回空结果；合法 CFF
OTF 的 `CharStrings` 数量还必须匹配 `maxp.numGlyphs`，加载和 glyph 栅格化保持可用，
每个对象的 INDEX payload 也必须非空且完整。CID CFF 的 FDArray 逐项验证 Font DICT，
并检查其 Private 区、Private DICT Subrs 相对偏移和 Subr INDEX 的有界性；CID FDSelect
偏移也会被保存并交给后续运行期选择逻辑。修改不进入绘制热路径。

TDD 新增截断 CFF、正常 CFF、正常 CID CFF 以及三类 CID Font DICT Private 畸形输入
回归；普通、ASan/UBSan、Vulkan 与 STB-only 字体测试均通过 **55/55**，文本布局测试
均通过 **96/96**。尚未完成的是 CFF/CFF2 charstring 指令、DICT 操作语义和其他
OpenType 表验证；当前偏移、INDEX、FDSelect 和 subr 入口边界安全不等于完整 OpenType
解析。

本阶段还增加了 Type 2 CharStrings、Global Subr 和 Local Subr 的有界词法扫描：数字操作数
和转义操作不会越过对象末端，stem hint 数量用于限制 hintmask/cntrmask 的 mask 字节，
可证明的主字形 subr 调用操作数会校验，调用 Subr 后对未知栈上下文不作错误的强约束，
保留 opcode 直接拒绝；未知 Subr 栈部分只验证 token 字节宽度，避免误解析调用方 hint mask；
CFF DICT 已知操作符的固定/偶数操作数基数和尾部悬空操作数也拒绝。
该扫描只做构造期安全检查，不替代完整
Type 2 interpreter；CFF1 DICT 中 vendored STB 不支持的数字编码也在进入第三方解析器前
拒绝，避免触发断言路径；
TDD `stb_rejects_malformed_type2_charstrings` 加入截断数字、截断转义与保留 opcode 回归，
`stb_rejects_malformed_cff_dict_operands` 覆盖已知操作符缺少操作数；普通、ASan/UBSan、
Vulkan 与 STB-only 字体测试为 **55/55**，文本布局测试为 **96/96**。

## 本轮完成：STB 复合 glyph 图遍历优化（2026-09-03）

将构造期复合 glyph 图校验从“节点栈 + 每次返回重置组件游标”改为显式帧栈，每个帧
保存 glyph 节点、记录边界、当前组件游标和 `MORE_COMPONENTS` 状态。每条组件边只被
解析一次，复杂度为 O(V+E)；所有状态仍由调用方 allocator 事务分配，分配失败安全返回，
不递归、不增加运行期布局或绘制成本。统一的组件步进函数以剩余长度检查所有参数宽度，
因此记录末尾的 `MORE_COMPONENTS` 不会被错误接受。

TDD 新增 `stb_accepts_deep_component_chain_without_recursion`，覆盖 128 层以上的无环
复合链；普通、ASan/UBSan、Vulkan 和 STB-only 字体测试均通过 **48/48**，文本布局
回归同时通过。未完成项仍包括完整 glyph 坐标语义、复合 glyph 指令和深层 OpenType/CFF、
COLR/SVG 结构验证，以及真实 Wayland/X11/Win32/Cocoa runtime 矩阵。

## 本轮完成：STB sfnt/TTC 容器边界校验（2026-09-03）

STB 构造路径增加无分配容器校验：验证 sfnt/TTC 头和版本、TTC face 数组、选中
face 的 sfnt 目录长度、所有表目录记录的 offset/length 不越过文件 payload，并验证
TrueType 必需表固定字段、cmap format 4 数组/索引范围、`loca/glyf` 偏移和 glyph
header 最小长度、复合 glyph 组件索引/参数记录及组件图无环性。
截断 TTC 和越界表偏移会在第三方解析器读取前直接失败；校验只发生在字体加载冷
路径，不增加 glyph/measure 热路径扫描。

TDD 新增 `stb_rejects_truncated_ttc_header`、`stb_rejects_out_of_range_table_offset`、
`stb_rejects_short_required_table`、`stb_rejects_out_of_range_cmap_glyph_index` 和
`stb_rejects_short_glyph_record`、`stb_rejects_out_of_range_component_glyph`、
`stb_rejects_component_cycle`、`stb_rejects_out_of_range_simple_glyph_instruction`、
`stb_rejects_truncated_simple_glyph_coordinates`；
普通、ASan/UBSan、Vulkan 与 STB-only `test_myui_font` 均通过 **47/47**。这不是完整
OpenType 验证：glyph 坐标字节流的全部语义、表内部记录、CFF/CFF2 子结构及 COLR/SVG 内容仍依赖后端解析器，STB
不支持的轮廓格式继续安全失败。

## 本轮完成：STB glyph cache OOM 事务（2026-09-03）

STB glyph cache 现在遵循 `load -> validate -> copy -> publish` 提交顺序：临时 stb 位图
先复制到调用方 allocator，并在尺寸乘法溢出或 OOM 时立即回收；只有复制成功后才驱逐
LRU entry 和写入新 entry。这样失败重试不会得到伪造的空 glyph，也不会丢失原有缓存内容。
实现只影响 glyph 冷路径，不增加锁、逐帧扫描或公共字体 vtable 字段。

TDD 新增 `stb_glyph_oom_does_not_poison_cache`，普通 `test_myui_font` **40/40** 通过。
FreeType、Vulkan 与 Sanitizer 构建使用相同的事务性缓存要求；完整 OpenType
language-specific feature 选择、RTL GSUB、跨字体 variation 覆盖及完整 UAX#14 corpus 仍
属于未完成项。

## 本轮完成：STB TTC face index 支持（2026-09-03）

STB 字体构造新增 `my_font_stb_create_ex()`，可在 TrueType Collection 中选择显式
`face_index`；普通 TTF 对非零 index 明确拒绝，非法 TTC index 也不会回退到 face 0。
字体链在 FreeType 不可用或加载失败时继续把 `my_font_source_t.face_index` 传给 STB，
因此 CJK/多字面 TTC 不再依赖 FreeType 才能被正确选面。公共旧构造器保持 face 0
兼容行为，未增加 vtable 字段或热路径分配。

TDD 使用运行时生成的双 face TrueType Collection fixture，覆盖非零 face 选择与普通
TTF 非零 index 拒绝；普通、ASan/UBSan、Vulkan 及 STB-only `test_myui_font` 均通过
`40/40`。系统 CJK VF TTC 若为 CFF2 格式仍由 STB 安全拒绝，不将其误报为 STB
TrueType 支持证据。

STB 文件读取另外受 `MY_FONT_STB_MAX_FILE_BYTES`（64 MiB）限制；超限、空文件或文件
定位失败在 payload 分配前拒绝，避免文件长度直接驱动无界内存申请。回归
`stb_rejects_oversized_file_before_allocation` 验证超限路径不申请文件 payload。

## 本轮完成：动态模块实例 quiesce 契约（2026-09-03）

为解决 class registry 只保护 callback、却不知道 widget 实例是否仍依赖模块代码的架构
缺陷，新增显式 `my_widget_class_module_t` token。宿主注册模块 class 时使用
`my_widget_class_runtime_register_module()`；通过 `my_widget_class_acquire()` 取得 lease
后创建实例，并调用 `my_widget_class_bind_instance()`，或直接使用推荐的
`my_widget_class_create()`。widget 的基础销毁链自动解绑实例计数。

卸载采用非阻塞、可审计的两阶段顺序：

1. `my_widget_class_module_begin_unload(module)` 停止新的 callback lease 和 module class
   注册；callback 内调用会快速返回 `MY_RET_NOT_SUPPORTED`。
2. 注销 module class，停止新的类型查找；等待所有已取得 lease 的 callback 返回。
3. 销毁全部 module-owned widget 实例；实例计数归零后调用
   `my_widget_class_module_try_unload(module)`。
4. 只有 `try_unload()` 返回 `MY_RET_OK` 才允许宿主执行平台动态库卸载，随后调用
   `my_widget_class_module_destroy()` 释放 token。

module token 使用稳定地址的引用协调：创建者持有一个 owner reference，跨线程或跨组件传递
前调用 `my_widget_class_module_retain()`，使用结束调用
`my_widget_class_module_release()`。`destroy()` 只接受 owner reference 仍为唯一引用的
已 quiesce token，并将 token 标记为 destroyed；地址保留至进程退出，因此并发迟到调用会
返回 `MY_RET_NOT_SUPPORTED`，不会解引用已释放内存。框架仍不会替宿主执行动态库卸载，宿主
必须在 `try_unload()` 成功后完成 `dlclose`、`FreeLibrary` 或 Cocoa bundle unload；任何
已缓存的 module callback 指针也必须先停止使用。

实现只在生命周期冷路径加锁；lease/instance 计数不进入普通绘制热路径，也不改变 PAL、
RHI 或平台 frozen vtable ABI。静态 fake module TDD 覆盖实例存活拒绝、callback 重入拒绝、
自动解绑、推荐创建路径、loader factory/migration 绑定、非法参数、重复替换计数、schema-ex/chain 变体、注销后的最终 quiesce、引用阻止销毁、销毁后 fail-closed 及未知 token 拒绝；普通 loader **119/119**，YAML-off
为 **2/2**。该阶段没有声称完成真实 `dlclose`、`FreeLibrary`、Cocoa bundle unload 或
Wayland/X11/Win32 runtime quiesce。

## 本轮完成：PAL 定时器堆调度优化（2026-09-03）

PAL timer manager 现在使用按截止时间和稳定 ID 排序的最小堆：添加定时器为
O(log n)，读取下一次等待时间为 O(1)，处理到期条目为每项 O(log n)，不再为
每次主循环等待或 tick 扫描全部按钮和其他 timer。按 ID 删除仍需 O(n) 查找，找到后
堆调整为 O(log n)；删除不是逐 tick 热路径，后续若生命周期规模成为瓶颈再引入有界
ID 索引表。回调期间新增的 timer 放入 bounded
生命周期内的 pending 队列；当前回调条目放在内联 current 槽位，回调结束后直接回到
活动堆，因此正常 fire 不需要 deferred 动态容器。回调内新增 timer 不会在同一轮提前触发，
回调内删除、周期重调度和销毁仍保持原有安全语义。pending 条目只有成功进入活动堆后才
从队列移除，临时 OOM 不会让仍被按钮持有的 timer ID 丢失。

补充：timer callback 调用 `my_timer_manager_destroy()` 时只发布关闭标记，最外层 `fire()`
完成当前 entry 收尾后才释放 manager；关闭标记发布后，同一轮剩余 timer 不再执行，嵌套
`fire()` 也立即返回。TDD 新增 callback-destroy 回归，普通和 sanitizer
`test_myui_window_manager` 均为 **235/235**。新增 `my_timer_add_lease()` 为 timer callback
context 提供与 emitter 相同的 invalidation 协议：owner 可在 teardown 前失效 lease，后续
未开始 callback 被跳过并释放 timer，callback 内失效仍允许当前调用自然返回。
manager teardown 进入幂等 disposing 状态；lease destructor 重入 destroy、add、remove、due
或 fire 均 fail-closed，不访问已开始释放的 timer 数组；`due_in_ms()` 会在计算等待时间时
清理失效的堆根，避免向主循环返回短暂的 `0ms` 忙等。

该优化不引入线程、平台或 RHI 依赖；堆仅使用既有 allocator/darray，deadline 仍采用
`uint64_t` 饱和加法，ID 回绕仍检查 active、pending 和 current 条目。普通
`test_myui_window_manager` **123/123** 通过，覆盖回调内新增/删除、非根失效项、时钟
回拨、`UINT64_MAX` 边界、fire 零分配、pending OOM 保留和嵌套 fire 的 current 链安全。
后续若引入跨线程 timer API，必须另行设计 owner loop 和
同步契约，不能直接把当前单线程 manager 当作线程安全队列。

## 本轮补充：Window manager 回调重入销毁（2026-09-06）

repaint、PAL event、surface event、window close 和 close-listener 路径统一使用 manager
callback depth。回调中销毁 manager 只发布延迟请求；当前事务完成后才执行完整 teardown，
并停止同一帧后续窗口绘制。`on_open` 的 owned hook 替换/销毁同样通过 retired 队列延迟
上下文 destructor 到最外层 callback 返回之后。TDD 新增 paint、event、close-listener、
owned `on_open` 替换及 manager teardown 重入回归；普通与 sanitizer
`test_myui_window_manager` 均为 **235/235**。

## 本轮补充：BreakUI GPU AA pending 事务收口（2026-09-03）

BreakUI 的 Break RHI AA 请求在下一渲染边界提交；如果提交前恢复当前 active level，
现在会撤销 pending target switch，不触碰当前 target。非法 level 不会清除 pending，
避免错误输入改变后续质量请求。普通与 ASan/UBSan `test_myui_vgcanvas_backend`
均为 **34/34**，既有 11 个 myui/Break 专项 CTest 全部通过。

本文记录 `myui` 与 Break `Platform/RHI` 整合中仍未完成的能力、架构风险和
可执行的性能优先实施顺序。每个阶段必须先增加跨后端失败契约，再实现，最后
通过定向测试、构建矩阵和 sanitizer 门禁。

## 本轮完成：text-area Unicode JUSTIFY（2026-09-03）

text area 的 justify 分隔符计数、拉伸边界、RTL visual layout 和无 shaping 绘制回退统一
使用 `my_line_break_is_breaking_space()`。Unicode breaking space 不再被当作普通文字，
光标、IME anchor、选区矩形和绘制的剩余宽度分配保持一致；无 shaping 回退同时按 codepoint
而非 UTF-8 字节计算词宽，避免多字节空格放大宽度。实现仅增加有界单次扫描，无分配、无锁，
不改变 canvas/PAL/RHI ABI。

TDD 新增 `text_area_justify_cursor_tracks_unicode_breaking_space`，普通
`test_myui_window_manager` **125/125** 通过；Vulkan、YAML-off 与 ASan/UBSan 继续复用
同一核心实现验证。

## 本轮完成：Unicode breaking-space wrap 收口（2026-09-03）

paragraph wrap 现在复用 `my_line_break_is_breaking_space()`，统一识别 ASCII、U+2000..U+2006、
U+2008..U+200A、U+205F 和 U+3000。断点回退、行首和行尾裁剪不再只处理 ASCII 空格，
避免 Unicode 空格残留在上一行或成为下一行的首字符。判定为固定范围 O(1)，无分配、无锁，
并保持既有 paragraph/text-area 共享断行路径。

TDD 新增连续 Unicode 空格 wrap 与 helper 边界回归，普通 `test_myui_text_layout` **91/91** 通过；完整
UAX#14 locale tailoring、SA dictionary corpus 和 golden corpus 仍保留在未完成矩阵。

## 本轮完成：帧级 MyUI 性能观测基础设施（2026-09-03）

新增 `myr/my_ui_metrics` 固定容量 8 帧 ring buffer，覆盖 logical draw、layout、dirty
面积、glyph atlas miss、image cache miss 和 font fallback。record 热路径不分配、不加锁；
关闭状态不写入，计数溢出饱和，嵌套 frame 只发布最外层样本。canvas wrapper 只在后端
操作成功且参数有效时计数，后端 `end_frame` 失败会 abort 当前样本，不发布半成品指标。

BreakUI 推荐帧入口现在建立外层 metrics scope，shared-surface 的 layout、damage 和多个
窗口的 canvas 绘制可归入同一个样本；资源、窗口快照、surface 或合成流程提前失败均会
收口 abort，避免 owner frame 泄漏。指标语义明确为 logical UI 统计，不冒充底层 GPU draw
call 或最终 compositor damage。

TDD 新增 fake canvas wrapper 成功/失败/非法参数、end failure 以及真实窗口 dirty 统计回归；
普通 metrics **6/6**、vgcanvas backend **34/34**、window-manager **124/124**，myui core 定向构建通过。
最终门禁已完成：Redis 配置 CTest **84/84**，Vulkan syntax/window/backend 分别
**7/7、124/124、35/35**，ASan/UBSan syntax/window 分别 **7/7、124/124**，
YAML-off 裁剪配置 CTest **83/83**，并新增 `test_myui_loader_disabled` **2/2**
验证关闭路径的能力声明和 stub 行为。真实平台 runtime profiling 不在当前 headless 证据内。

YAML-off 之前无条件注册完整 loader 测试，导致裁剪构建错误执行依赖 YAML 的用例；现由
`MYUI_UI_YAML` 选择完整 loader 或禁用路径测试，避免把配置契约误报为实现回归。

## 本轮完成：增量语法状态收敛与稳定后缀复用（2026-09-03）

编辑器语法缓存现在分离源码 dirty、旧状态快照和当前 token ready 状态。改单行只替换
文本并保持 lazy lexer 预算；如果跨行输入/输出状态未变化，未修改后缀直接复用旧 token
快照，不再无条件清空或逐行重扫。块注释等跨行状态变化只传播到实际收敛位置，后续独立
源码修改仍单独失效，避免状态收敛错误恢复。收敛判断和稳定后缀复用不分配，保持大文档
编辑的有界单帧预算。

TDD 新增普通后缀复用、块注释传播、状态收敛、后续源码修改和稳定后缀零分配测试；
`test_myui_syntax` **7/7**、`test_myui_window_manager` **124/124**，普通和 ASan/UBSan
定向回归通过。该优化不改变渲染后端 ABI。

## 本轮完成：OpenType language cache key 归一化（2026-09-03）

FreeType/HarfBuzz 的 language-system capability cache 现在对语言标签做有界 ASCII
大小写折叠，因此 `ZH-CN` 与 `zh-cn` 不会触发两次 GSUB/GPOS 表扫描。归一化仅用于
provider 的语言解析和缓存 key，不声称完成完整 BCP-47/locale canonicalization；语言
结构、别名和 locale tailoring 仍由后续 OpenType/UAX 阶段负责。输入仍受既有 64 字节
预算保护，缓存容量和热路径分配契约不变。

TDD 新增 `freetype_capability_cache_normalizes_language_tag_case`，普通字体测试
**35/35** 通过；无 FreeType/HarfBuzz 构建继续显式回退。

布局层的 glyph-run 与 visual-boundary cache 也已采用同一有界 ASCII language key
归一化；公开 shaping 参数和 provider 实际输入保持不变。新增 TDD
`text_layout_shape_cache_normalizes_language_tag_case`，普通/Vulkan/ASan 文本布局分别
**88/88** 通过。

另外修复 SA dictionary 回调可以改写 run 起点 `allow_before[0]` 的边界缺陷；该槽位
现在始终保持调用前值，失败回调仍不提交任何内部边界。普通/Vulkan/ASan 文本布局门禁
均为 **87/87**（包含该回归）。

## 本轮完成：BreakUI damage-aware frame bridge（2026-09-03）

新增 `break_ui_frame_begin()` 作为 BreakUI 宿主的唯一推荐帧入口。它在固定容量数组中
收集 drawable damage，并以 `FULL/PARTIAL/SKIP` 规划器统一门控：surface 无效、present
目标不保证保留、后端不支持 damage 或输入异常时只能走普通全屏帧；只有全部能力满足时才
调用 `rhi_frame_begin_damage()`。无 dirty 且没有 buffer-age 历史需求时才允许安全跳帧；
Wayland buffer-age 场景即使当前 dirty 为空也继续开始帧，让 RHI 合并历史 damage，避免
轮转 buffer 时丢失旧像素。`break_ui_render()` 使用本帧后端实际 partial 状态，不再使用
跨帧的请求开关推断 swapchain 是否可局部合成。

TDD 覆盖能力缺失全屏退化、空 damage 跳帧、buffer-age 不跳帧和非法 damage；普通
`test_break_ui_damage` **29/29**、关键 BreakUI/RHI CTest **7/7**、ASan/UBSan 定向
回归通过。当前仍未完成真实宿主的 runtime smoke：Wayland compositor、X11/Win32/Cocoa
窗口保留语义及真实 Vulkan runtime 需要对应平台设备与 compositor 证据。

## 本轮完成：YAML 窗口 CSS 响应式媒体样式（2026-09-03）

YAML 根窗口的 CSS `style` 现在保存源文本与加载前主题基线。窗口创建和每次逻辑
尺寸 resize 都在冷路径按 `my_pal_window_get_size()` 构造一次
`my_css_media_context_t`，只用逻辑 viewport 评估 `@media`，物理 drawable/HiDPI scale
不参与 breakpoint。重算采用 `clone -> parse/apply -> swap` 候选事务；CSS 解析、复制
或应用失败时保留当前主题和旧源样式，不会产生半应用主题。正常 resize 不增加逐帧
媒体查询、锁或分配；主题查询仍是已展开规则的热路径。普通 `test_myui_loader`
**87/87**、`test_myui_css` **65/65**、`test_myui_window_manager` **117/117** 通过，
覆盖逻辑 viewport、resize 切换和失败保留。

## 本轮补充：PAL 媒体能力快照接入（2026-09-03）

PAL 通过版本化的媒体 provider 扩展提供平台无关的冷路径快照，冻结的
`my_pal_vtable_t` 不追加媒体函数；兼容包装 `my_pal_get_media_context()` 只返回基础
事实。Break 适配器将宿主 Platform 的媒体事实映射到该扩展，Dummy PAL 提供确定性测试注入。X11、
Win32、Cocoa 声明可稳定证明的 `screen`、fine pointer、hover 与 sRGB；Wayland 仅在
seat 暴露 pointer 时声明指针能力。未知能力、HDR、色域升级及系统偏好不会被猜测，
缺少 provider 时安全返回 `MY_RET_NOT_SUPPORTED` 和零能力。窗口 CSS 将快照转换为
`my_css_media_context_ex_t`，仍只在样式加载/resize 冷路径评估，主题热路径不增加媒体查询。
旧的 `my_css_media_context_t` 及 `my_css_parse_media_ex()` 保持原布局和兼容语义；需要
known mask 时使用 `my_css_parse_media_ex2()` / `my_theme_load_css_media_ex2()`。
TDD 覆盖空对象、部分 vtable、provider 版本校验、provider 注销、Dummy 能力条件和默认
screen 语义；普通 CSS 为 **67/67**、loader 为 **90/90**、Break PAL 为 **8/8**。

## 本轮完成：dirty suffix 批量折行与 OOM 收口（2026-09-03）

开启 wrap 且没有折叠范围时，编辑后的 dirty physical-row suffix 现在只创建一次
`my_text_paragraph_t`，再按共享硬换行偏移映射回 visual lines；未受影响的前缀对象继续
复用。该路径保持逻辑顺序、CRLF/Unicode 硬换行和 shaping cluster 不可拆分语义，折叠
场景仍使用逐物理行安全路径，避免把折叠状态错误带入 paragraph。候选 paragraph、visual
line 数组和映射失败均事务性回退到旧缓存；`ta_vline_push()` 在数组扩容失败时释放已
分配的行对象，避免 OOM 泄漏。

正常 dirty suffix 只增加一次 paragraph 级输入/测量准备，复杂度仍为 suffix 字节数加
输出 visual lines，热路径无锁；普通/ASan `test_myui_window_manager` **113/113** 通过。

## 本轮完成：my_text_area 编辑事务与历史一致性（2026-09-03）

`my_text_area` 的插入、选区替换、删除和 undo/redo 重放现在统一经过范围、UTF-8、
`max_len` 与容量预检。容量预留成功后才记录用户 undo，历史记录失败或文档预留失败
均保持文本、光标、选区和历史不变；选区替换使用单个 replace patch，undo 能一次恢复
被替换内容。程序化 `set_text()` 也只在语法候选和文本扩容成功后清理该 widget 的历史，
失败不会破坏旧历史。`ta_pos_of()` 支持可选列输出，键盘 ASCII 临时缓冲显式 NUL 终止，
避免 sanitizer 下的越界读取。

该设计保持编辑热路径无锁；已有文本容量可复用时不分配，扩容仍采用倍增策略，预检仅
做有界整数/UTF-8 检查。TDD 新增扩容 OOM、选区替换 OOM、删除历史 OOM、`set_text()`
失败保留历史、undo peek/commit 和 `max_len` 失败回归；普通 `test_myui_window_manager`
**110/110**、ASan/UBSan **110/110**、无 BiDi **99/99** 通过；`test_myui_text_layout` **75/75**、
YAML-off 与 Vulkan `myui_core` 构建通过。

undo/redo 重放采用 `peek -> apply -> commit` 顺序：编辑器或文本区文档应用失败时不移动
undo 游标，shared undo manager 也不会因 owner 应用失败而丢失历史；该提交点不引入锁或
额外文档复制。

## 本轮完成：统一硬换行分隔符契约（2026-09-03）

新增 `my_line_break_hard_break_len()` 作为 paragraph 与 text area 共用的硬换行识别入口，
统一处理 LF、VT、FF、CR、CRLF、NEL（U+0085）、LINE SEPARATOR（U+2028）和 PARAGRAPH SEPARATOR
（U+2029）。CRLF 被视为一个分隔符，分隔符不计入行内容或逻辑 codepoint 数量，避免
paragraph、行偏移缓存、几何、折行、语法切片和光标定位出现规则漂移。识别只扫描最多
三个 UTF-8 字节，无分配、无锁，普通 LF 路径保持常数级开销。

TDD 先覆盖 paragraph 的 CRLF/NEL/VT/FF 分行，再覆盖 text area 行缓存，普通
`test_myui_text_layout` **78/78**、ASan/UBSan **78/78**，普通 `test_myui_window_manager`
**111/111**、ASan/UBSan **111/111** 通过。完整 UAX#14 的 locale tailoring 和 golden
corpus 仍保留在未完成清单中。

## 本轮完成：my_edit 事务与跨后端边界（2026-09-03）

`my_edit` 的文本替换现在先构造完整的新文本及 password mask，两个缓冲区均成功后才
提交 widget 状态；分配失败不会改变文本、光标、选区或掩码，也不会发出 `changed`。undo
记录和 changed 事件均在成功提交之后发生，避免“文本未插入但历史已写入”的事务破坏。
`my_edit_set_text()`、`my_edit_set_password()` 现在向调用方返回实际 OOM，失败保持旧状态；
删除路径复用同一 replace 事务。正常路径无锁，仅保留必要的一次文本复制和（密码模式）
一次掩码生成。

测量、命中、光标、IME anchor 和绘制入口统一使用 edit 的有效字体（自身字体优先，否则
窗口默认字体），paint 入口显式同步 canvas font state。fallback cell 宽度、IME 预编辑宽度、
选择区和光标坐标采用 64 位中间值及 `int32_t` 饱和转换，避免极大 glyph advance 在各渲染
后端坐标中回绕。未扩展 PAL/window/canvas frozen vtable。

TDD 新增 OOM 插入、password 替换/删除/切换、测量字体一致性和极大字体坐标回归；普通
`test_myui_window_manager` **102/102**，ASan/UBSan **102/102**，无 BiDi **93/93**，
`test_myui_text_layout` **75/75** 通过。完整跨 face token shaping、RTL GSUB/justify 和
真实平台 runtime 仍在下方未完成矩阵中。

## 本轮完成：undo 栈事务与 replace 语义（2026-09-03）

公共 `my_undo_stack` 现在支持不可批量的 replace patch，同时保存 deleted/inserted 两组
字节；单行编辑器的选区替换因此可被一次 undo 完整恢复，redo 也重新应用替换。连续退格
合并会正确保留 NUL 终止字节，所有长度相加和 `len + 1` 均先做 `size_t` 溢出检查。

记录操作采用候选 entry 提交：entry、payload 和动态数组扩容全部成功后才丢弃 redo 分支
或超出容量的旧 entry；OOM 时保留原有 undo/redo 状态。正常批量输入仍为一次 realloc，
非批量记录只增加一次候选 entry，不改变 undo 查询复杂度或 frozen ABI。

TDD 新增选区替换恢复、超大长度拒绝、连续退格终止字节、redo 分支 OOM 保留和容量 OOM
保留最旧历史测试；普通 `test_myui_window_manager` **102/102**、ASan/UBSan **102/102**、
无 BiDi **93/93**、`test_myui_text_layout` **75/75** 通过。

## 本轮完成：text area 几何与滚动边界（2026-09-03）

`my_text_area` 的 glyph advance、visual line 高度、滚动内容高度、游标/IME 坐标和绘制
范围现在统一使用 64 位中间值或饱和转换；无字体 fallback 的 `size_t * 8` 计算也在
乘法前受限于 `INT32_MAX`。视觉行文本切片会先验证起点和长度位于当前文本缓冲区内，
损坏或过期缓存不会触发越界访问。正常路径仍为 O(1) 饱和检查、无额外分配和无锁。

TDD 新增接近 `INT32_MAX` glyph advance、损坏 visual-line slice 和越界 visual-line 查询
测试，覆盖 boundary cache、paint、cursor、极限滚动值及失效缓存拒绝；普通
`test_myui_window_manager` 为 **91/91**，无 BiDi 配置为 **82/82**，ASan/UBSan 定向测试
为 **91/91**，`git diff --check` 通过。

该阶段只解决 text area 的数值和缓存安全，不改变文本模型或渲染后端 ABI；完整 UAX#14、
OpenType language-specific shaping、复杂 RTL 跨段落 rebreaking 等能力仍按下方未完成清单
处理。

## 本轮完成：矩形端点溢出防护（2026-09-03）

`my_rect_t` 的半开区间端点统一使用 64 位中间值计算，覆盖命中测试、交集、并集和
dirty rectangle 接触判断，避免 `x + w`/`y + h` 在极限坐标处发生有符号回绕。输出仍
保持现有 `int32_t` ABI；当结果尺寸超出可表达范围时饱和到 `INT32_MAX`，空矩形和
负尺寸继续按既有空语义处理。正常路径只增加固定次数的整数提升，不分配、不加锁，
不会改变 dirty merge 的摊销复杂度。

TDD 覆盖 `INT32_MIN` 起点、跨越 `INT32_MAX` 的端点、半开包含、交集/并集饱和以及
dirty merge，`test_break_ui_damage` 当前为 **24/24**。后续仍需在真实平台 runtime
矩阵中验证极限逻辑坐标到 drawable 坐标的转换。

窗口几何审计同时收口模态窗口居中和 tooltip 定位：居中坐标通过共享 64 位中间值 helper
计算并饱和回写，tooltip 文本宽度、光标偏移和边缘翻转在加减前检查范围；dirty 快照扩容
在乘法前拒绝 `size_t` 回绕。正常路径仍为 O(1) 定位/扩容检查，不增加每帧分配或锁。
TDD 后 `test_break_ui_damage` 为 **24/24**，`test_myui_window_manager` 为 **84/84**。

同一阶段继续收口菜单和节点编辑器的尺寸边界：菜单宽高、边缘翻转和子菜单锚点改用
64 位中间值，节点自动尺寸的标题、socket、子节点端点累加改用 64 位并饱和回写，防止
极限 UTF-8 文本、超大子节点坐标和深层菜单导致负尺寸或坐标回绕。TDD 新增极限菜单弹出
与节点自动尺寸用例，`test_myui_window_manager` 当前为 **86/86**，ASan 同样通过。

节点视图的 socket 距离、socket 中心、命中/框选边界、拖拽偏移和子菜单命中判断现在统一
使用 64 位端点或饱和偏移，避免 `abs(int32_t)` 和端点加法在极限坐标处回绕。soft/LCD
像素循环也使用 64 位终点；Break RHI drawable 尺寸在进入 signed UI rectangle ABI 前拒绝
超范围值。TDD 后 `test_myui_window_manager` 为 **88/88**，`test_myui_vgcanvas_backend`
为 **33/33**，`test_break_ui_damage` 为 **24/24**。

BreakUI 公开的 `u32` logical/drawable 尺寸现在通过统一 helper 校验后才进入 myui 的
`int32_t` rectangle、canvas clip 和窗口 resize；超出 signed ABI 的尺寸被拒绝，render 和
present-damage 查询也采用相同边界。该检查是 O(1)、无分配、无锁，并保持各平台后端一致。
TDD 新增尺寸契约用例，`test_myui_break_pal` 当前为 **7/7**。

## 本轮完成：跨后端 stroke 线帽与连接语义（2026-09-03）

共享 `my_vggeometry` 现统一实现 `butt`、`round`、`square` 三种线帽及
`miter`、`round`、`bevel` 三种连接。miter 采用固定 4 倍半线宽上限，超限安全退化为
bevel，避免尖角输入产生无界几何；闭合 contour 的首顶点也纳入连接处理，开放 contour
保持端点语义。soft 的 AA union 与 GPU/Break RHI/Vulkan/GLES2 使用相同的几何契约，
setter 和公共 inline API 拒绝未知枚举值。该路径不扩展 frozen vtable；正常 stroke 仍按
contour/segment 线性构建，AA 仅使用既有 union 路径的有界工作缓冲。TDD 新增 square cap、
bevel corner、closed round join 和非法 style 回归；普通几何测试为 **7/7**，vgcanvas
backend 测试为 **32/32**。

## 本轮完成：共享几何输入边界（2026-09-03）

共享 `my_vggeometry` 的底层路径、变换、primitive、fill 和 stroke 入口现在独立执行
非有限值、正数/枚举和 clip 尺寸校验，不再只依赖 canvas inline wrapper。非法 path
输入不会创建 contour 或追加 point；非法变换保持旧状态；fill/stroke 的错误会由
GLES2、Vulkan 和 Break RHI 传播，阻止提交半成品几何。底层 primitive 对非法值安全忽略，
正常路径仍为固定次数检查，不增加渲染帧扫描。TDD 新增非有限 path、非法 transform/style、
空 clip 和非法 primitive 回归；普通几何测试为 **10/10**，后端测试保持 **32/32**。

共享几何输出还维护首个错误状态：顶点扩容失败、输出溢出或变换后非有限值会被记录，
后续 `fill/stroke` 返回该错误，GPU primitive 不再提交静默截断的三角形；`begin_verts()`
开始新的输出事务时清除状态。Bezier 追加失败会回滚到调用前的 point/contour 计数，
clip 扫描使用 64 位端点迭代避免极限高度自增溢出。失败 allocator 回归验证无半成品输出，
普通几何测试现为 **13/13**。

## 本轮完成：CSS `@supports` 有界逻辑条件（2026-09-03）

CSS 现支持有界的 `and`、`or`、`not` 逻辑表达式，原子条件为
`(property: value)`。实现复用既有声明值解析器和 key alias，只接受已实现的颜色与数值
样式属性；匹配规则在解析期展开，不匹配 block 整体丢弃，主题查询热路径不读取 supports
状态。查询受固定 `MY_CSS_MAX_SUPPORTS_QUERY_BYTES` 和
`MY_CSS_MAX_SUPPORTS_NESTING` 预算限制。

严格模式对不支持的 supports 语法、属性和值返回稳定的
`MY_CSS_ERROR_UNSUPPORTED_FEATURE`，并将 `capability` 标记为
`MY_CSS_FEATURE_SUPPORTS`；兼容模式沿用未知 at-rule 策略，跳过 block 并告警。普通
`test_myui_css` 已扩展至 **64/64**，覆盖匹配/不匹配、alias、逻辑优先级、深度、预算、主题桥接和
错误能力标识。

## 本轮完成：CSS 设备能力媒体条件（2026-09-02）

条件媒体解析现在支持一次性 `my_css_media_context_t.capabilities` 位掩码：
`hover`、`pointer`/`any-pointer`、`color-gamut` 和 `dynamic-range`。能力只在解析冷路径
评估，匹配后的规则被扁平化，主题查询热路径不读取平台、窗口或渲染后端状态，也不增加
每帧分配。`color-gamut` 按能力等级匹配（`rec2020` 满足 `p3` 和 `srgb`，`p3` 满足
`srgb`）；`dynamic-range: standard` 保持默认兼容语义。

媒体上下文拒绝未知能力位；未知 capability 值、单位或语法按既有严格/兼容策略处理，
不会静默应用不确定规则。该 API 只定义跨后端输入契约，不负责从 X11、Win32、Wayland、
macOS 或 Vulkan/GL 运行时采集设备能力；真实平台能力采集与 runtime CI 仍在后续清单。
TDD 新增设备能力匹配、色域等级、未知值和未知位回归；普通 CSS 测试为 **55/55**。

## 最近收口：共享容器容量安全（2026-09-02）

通用 `my_darray` 已补齐容量倍增、元素字节数和 `size + 1` 的 `size_t` 边界检查；极限
容量失败时保留旧数组状态并不调用 allocator。TDD 覆盖容量回绕与 size 回绕，普通
`test_myui_layout` 为 **6/6**。后续动态数组审计继续遵循“先测试失败语义、再实现、最后
跑 sanitizer”的顺序；当前未完成项仍是完整 OpenType/UAX#14、复杂 RTL 增量重排、完整
CSS at-rule 语义和真实平台 runtime 矩阵，而不是把这些能力误标为已实现。

公共 canvas API 的空句柄和缺失 vtable 槽位契约也已收口：空对象返回参数错误，合法对象的
不支持扩展返回 `MY_RET_NOT_SUPPORTED`，普通 `test_myui_vgcanvas_backend` 为 **32/32**。

PAL 公共 wrapper 的空对象、空 vtable 和部分 vtable 路径也已收口：必选操作返回
`MY_RET_INVALID_PARAMS`，可选操作返回 `MY_RET_NOT_SUPPORTED` 或安全默认值；检查位于
inline 边界，正常路径无分配、无锁、无 ABI 布局变化。TDD `test_myui_break_pal` 为
**6/6**，避免错误平台适配器在初始化失败时解引用空函数指针。

字体测量的宽度边界也已收口：bitmap、stb、FreeType、字体链统一使用宽累加并饱和到
`INT32_MAX`，TDD `test_myui_font` 为 **30/30**；这只解决数值安全，不代表完整 OpenType
语言特性或 provider-specific VS15/VS16 变体覆盖已实现。

## 本轮完成：VS15/VS16 shaping 基础契约（2026-09-02）

FreeType/HarfBuzz shaping buffer 现在启用 `HB_BUFFER_FLAG_REMOVE_DEFAULT_IGNORABLES`：未被
字体变体表或组合规则消费的 VS15/VS16 不再输出独立 glyph，也不会制造额外 advance；保留
原始 UTF-8 byte cluster，选择器仍附着于前一个基字符。真正存在于字体中的 variation glyph
仍由 HarfBuzz 在 shaping 阶段选择，ZWJ emoji sequence 不受该清理策略破坏。

该策略只影响 OpenType provider 的输出清理，不向 soft、GLES2、Vulkan 或 Break RHI 泄漏
HarfBuzz 类型，也不增加绘制帧分配。TDD 新增 VS15/VS16 cluster、真实 CJK IVS glyph 选择和
ZWJ 保留回归；普通 `test_myui_font` 为 **32/32**，ASan/UBSan、Vulkan 和无 HarfBuzz 配置的
字体/布局测试均通过。完整 language-specific feature
选择、RTL GSUB、跨字体 variation 覆盖和 locale-specific presentation 仍保留在后续清单。

Canvas 状态 setter 现拒绝 NaN、Inf 和非正 line width，避免非法数值污染跨后端 transform
或几何状态；几何、曲线、文字和图像入口也拒绝非有限坐标，失败保持旧状态，普通
`test_myui_vgcanvas_backend` 为 **30/30**。

## 当前已完成

- PAL 定时器契约已收紧：`interval_ms == 0` 在创建前拒绝，避免手动或原生主循环因
  周期零而忙循环；定时器 ID 在 `uint32_t` 回绕时跳过仍保留的 ID 和 0，避免冲突。等待时间
  超过 `UINT32_MAX` 时返回饱和值，时钟异常回拨不会因窄化截断制造过短的主循环等待。
  首次 deadline 与周期重调度仍使用 `uint64_t` 饱和加法；活跃 timer 已按 deadline
  使用最小堆调度，避免大规模冷却按钮导致每次等待和 tick 的全量扫描。周期 timer 在
  `UINT64_MAX` 时钟上界触发后进入不可立即到期状态，避免主循环忙循环；时钟回拨后按新
采样重新计算 deadline。普通窗口管理器测试为 **123/123**，新增零间隔、回拨等待、回调
重入、堆删除顺序、时钟上界防忙循环、fire 零分配和 pending OOM 保留契约测试。

- 冷却按钮已完成：按钮成功 click 后以 PAL 单调时钟建立截止时间，冷却期间拒绝
  pointer down/up 重入；只在冷却期间创建一个 16ms 按钮级 timer 驱动失效和遮罩动画，
  截止时间到达后自动停止。release timer 创建失败会立即清除 pressed 状态，不影响 click
  和 deadline。remaining/progress 查询均做过期检测、饱和转换和无 PAL
  回退，销毁与 duration=0 会清理 timer。所有按钮 API 通过专用 vtable 身份校验拒绝
  非按钮对象，错误路径不触碰按钮私有字段。soft/GLES/Vulkan/Break RHI 统一复用
  `fill_rect` 与 RGBA 颜色，不引入后端特定 shader。

- 通用属性路由已完成内置实例校验：class descriptor callback 执行前比较真实 vtable，
  不再把公开可写的 `widget_type` 当作安全类型证明。伪造类型返回
  `MY_RET_INVALID_PARAMS`，旧自定义 class 使用 `NULL` checker 保持兼容；热路径为 O(1)、
  无锁、无分配。普通与 ASan `test_myui_loader` 均为 **81/81**。

- 局部 widget 样式成功写入后会触发 retained invalidation；失败写入不污染旧样式，也不
  产生额外重绘。
- 局部样式非法 state/key 请求在首次分配前拒绝，不创建空样式对象；成功写入才产生一次
  既有的 retained invalidation。
- 局部样式首次合法写入采用候选提交，值复制 OOM 或容量失败不会留下空样式，也不会
  改变 dirty 状态。

- CSS universal、多 class、最多 4 级祖先路径、typed descendant/direct-child 链、祖先
  type/class/id、selector specificity、source order 和 normal-slot specificity fallback。
  路径匹配使用固定数组并且查询零分配；`@media all`/`@media screen` 已在解析期展开，
  不进入主题查询热路径，媒体嵌套有固定深度上限。
- 未知 CSS `@` 规则仍按兼容策略跳过，但跳过器现在能正确处理字符串转义、注释和嵌套
  block 的大括号，不会吞掉后续合法规则；结构错误仍硬失败，声明值错误仍按既有
  lenient 规则告警并跳过。
- UI 配置已移除 XML API，统一使用 YAML。loader 要求根对象包含字符串 `type`，控件属性
  使用类型化 YAML 标量，子控件使用 `children` 序列，MVVM 绑定使用 `bindings` map，
  窗口主题使用 `style` 字符串；CSS style 使用严格 at-rule 策略，样式解析/写入失败和
  文件读取 OOM 会传播为整个加载失败并保留错误信息。非法类型、错误容器和 XML 输入均拒绝。
- button 的 YAML `cooldown` 属性已接入 builtin schema，使用非负有界整数配置点击后的冷却
  时长；运行时继续使用单调时钟、固定 16ms 动画 tick 和到期自动停止计时器。
- YAML loader 直接消费 `my_conf` 类型树，不做字符串属性二次解析；整数范围、有限浮点、
  绑定规则 512 bytes 上限、setter/layouter 分配失败和严格 layout 语法均有明确失败路径，
  避免配置输入污染运行时树。
- YAML loader/parser TDD 定向测试现为 `85/85`，覆盖控件、嵌套子节点、绑定、错误类型、
  非 YAML 标记拒绝、输入大小、行数、block/flow 深度、集合规模和标量大小；UI 配置不再
  维护 XML DOM 资源预算或 XML 兼容层（两者均不属于目标）。flow/map key 同样受 1 MiB 限制，序列内联 map
  也拒绝重复键，避免替换语义掩盖配置错误。
- YAML loader 现提供只读 capability registry 和稳定错误分类；调用方可在加载前查询 YAML
  schema、children、bindings、CSS style 及资源预算，失败后可通过 `my_ui_error_code_t` 区分
  参数、预算、语法、schema、未知控件、资源和样式错误；`field` 提供首个可识别的 YAML key；
  旧的 line/message 字段保持兼容。migration/factory 回调在 loader 读租约内执行时，
  递归注册、动态 schema 替换、class registry 注册和 freeze 会快速返回
  `MY_RET_NOT_SUPPORTED`；该防护已由 factory、migration 与 runtime factory 三条独立 TDD 用例覆盖，
  两个 registry 共用同一线程局部 callback 深度。
- `my_ui_loader_query_type()` 已提供内置 widget 的属性/事件 schema 查询，并显式区分自定义
  factory 与有 schema 的内置 class；公共字段和 `window` 根字段均可查询。严格 schema 入口
  会拒绝内置 class 的未知字段；`my_ui_loader_register_schema()` 已允许自定义 factory 提供
  静态属性/事件契约并参与相同检查；属性/事件表自身有 64/32 项硬上限和终止符校验。现支持
  `my_ui_loader_register_schema_ex()` 的有界 schema version、borrowed migration callback
  以及最多 16 步的连续 migration chain；迁移在 factory 前递归执行并保持失败事务性，动态
  生成 schema 现通过 `my_ui_loader_register_dynamic_schema()` 支持显式计数、owned
  descriptor 副本、allocator 传递和替换事务；debug allocator 回归覆盖动态→动态→静态替换
  的 owned storage 释放；registry 注册前会拒绝保留字段冲突和重复 descriptor，并保持失败替换
  的旧条目不变。class registry 同样执行有界名称、属性类型、保留字段和重复 descriptor
  校验，并复制类型/属性/事件名称到 immutable snapshot；built-in 批量注册失败会整批回滚。
  应用完成启动期注册后应调用 `my_widget_class_freeze()` 和 `my_ui_loader_freeze()`；
  冻结后启动期注册返回 `MY_RET_NOT_SUPPORTED`；首次查找与启动期注册由同步原语串行化，freeze
  发布后查找进入无锁只读快路径。loader 另提供冻结后的 runtime factory/schema 注册与注销，
  继续使用读写租约和 owned schema 事务，内建 `window`/class 不可覆盖。严格
  入口已增加声明属性的标量类型与范围预检，错误路径提供
  固定预算内的嵌套定位并安全截断。严格入口现在会在任意 factory/window 创建前预检公共
  字段、窗口字段、layout/bindings/children 容器和整棵子树；路径达到预算后固定返回
  `<path-truncated>`，文件入口与字符串入口保持同一诊断契约。
- CSS 数值输入的有限值、整数范围和颜色 alpha 边界检查。
- UAX#14 实用子集的上下文规则：UnicodeData `Mn/Mc/Me` combining mark、数字小数分隔符、指数符号、
  货币/百分号、Hebrew quotes、Regional Indicator、ZWNJ、非断行连字符/BOM glue 和
  Hangul Jamo/LV/LVT 组合；新增
  shaping-aware paragraph model，按逻辑 codepoint 范围输出换行段，保护 ligature cluster
- CSS 解析增加严格策略模式：兼容入口仍跳过未知 at-rule，严格入口拒绝未实现的 at-rule
  与未知策略位。主题桥接的 `my_theme_load_css_ex()` 使用“现有 entries 深拷贝到候选主题、
  CSS 全部写入成功后交换”的事务语义；解析、复制或写入失败均保持活动主题及 specificity
  不变，生产配置不会半加载。legacy `my_theme_load_str()` 也采用相同候选交换策略，坏行
  不会留下半主题；默认主题初始化和新属性值复制也具备失败回滚；当前仅支持恒真的
  `@media all`/`@media screen` 容器；带一次性媒体上下文的有限条件 `@media` 也已在解析期
  评估，未匹配 block 不进入主题；现支持有界的 `width/height` CSS range 比较（例如
  `width >= 800px`、`400px <= width < 800px`），以及 hover、pointer、any-pointer、
  color-gamut 和 dynamic-range 设备能力条件，并在解析期完成扁平化；另支持有界的
  `@supports` 有界 `and`/`or`/`not` 逻辑表达式和 `(property: value)` 原子查询。其他完整
  at-rule 语义仍未实现；设备能力的
  真实平台采集也仍未实现。
  legacy 文本主题入口另有 `MY_THEME_MAX_BYTES` 有界 NUL 扫描。
  不被拆分，并已接入 text area 的 wrap 重排。新增 Unicode glue（NBSP、figure space、
  narrow NBSP、word joiner）、ZWJ、variation selector、Emoji modifier 和 tag sequence
  扩展的不可断边界，所有规则均为 O(1) 上下文判断。
- 软件开放 contour 的 fill 自动闭合；开放 stroke 不自动闭合。
- 共享 surface damage 的逻辑坐标到 drawable scissor 纯函数；向外取整、裁剪和
  64 位乘法均有测试；新增 `SKIP/PARTIAL/FULL` 合成决策层，能力缺失、碎片过多或面积
  过大时安全回退全屏，当前默认 swapchain 仍不宣称保留未更新像素。
- 编辑器光标闪烁、变高列表 prefix-sum、跨后端 nearest/bilinear 已存在，不再作为
  未实现能力记录。
- text area wrap 重排采用候选 cache 事务：分配失败或 paragraph 构建失败不会清空旧
  visual lines，dirty 标志保持到下一次成功重建，避免 OOM 时文本内容静默消失。
- text area wrap 重排现采用前缀复用 + 后缀候选事务：编辑只从受影响物理行开始重排，
  未受影响的 visual-line 对象保持稳定；候选构建失败时保留旧缓存，避免大文档编辑每次
  修改都重新分配和扫描全文。
- MVVM data/condition binding 的初始同步现纳入创建事务：目标 setter 失败会向调用方传播，
  并清理已注册 listener、validator 和绑定对象，不再留下“注册成功但视图未同步”的半状态；
  正常路径仍为一次同步和后续事件直达，不引入队列或帧级分配。
- MVVM context 切换现采用旧 VM 保留引用的回滚事务：新 VM 任一绑定重订阅/刷新失败时，
  新监听会被清理，旧 VM 和旧监听会恢复，避免 data/items/condition 绑定出现混合来源；
  正常切换仍为有界绑定遍历，不引入异步队列。
- MVVM items 绑定现采用引用保活和候选提交：数组属性显式置空会提交空列表，错误类型、
  新数组监听失败或目标重建失败会保留旧数组和旧监听；普通容器在模板校验通过前不会清空
  现有子控件。data、items、condition 均监听 `props` 批量通知；MVVM 定向测试当前为
  **10/10**，普通和 ASan/UBSan 均通过。
- text area 已支持可选物理行号栏和非重叠物理行折叠：默认关闭行号和折叠，折叠只保留
  header 行，wrap 时隐藏物理行不会生成 visual line；可见物理行有缓存，编辑导致物理
  行结构变化时安全清除折叠，避免偏移引用失效。可见行缓存 OOM 时使用不分配内存的线性
  回退，继续隐藏折叠行，不以错误的全物理行视图替代正确性。
- text area justify 在 wrap 的普通 LTR 路径中统一正文、选区和光标的 stretched-space
  坐标，避免固定 cell 宽度造成命中和编辑位置漂移；paragraph 已提供全局 logical boundary
  与局部 visual boundary 的无分配映射包装；RTL wrap 的绘制、选区和 IME 光标也统一使用
  visual 空格拉伸坐标；选区矩形的空间前缀通过单次 visual-boundary 遍历计算，避免长行
  多片段选择的 O(n²) 重复边界查找。复杂 RTL 的跨段落增量重排仍按后续能力处理。
- text area IME 候选框锚点已复用 wrapped visual-line index 与 justify 边界，跨 visual line
  的候选框 y 坐标和拉伸空格后的 x 坐标保持一致；平台只消费 PAL 的统一全局坐标。
- text area 变宽字体的非 wrap 点击、水平滚动、光标和 IME 坐标已统一使用 glyph advance，
  无字体才走固定 cell fallback；当前 visual line 边界计算保持无额外缓存。
- text area pointer 垂直命中对负坐标和超出底部坐标做有符号边界钳制，避免负值转换为
  `size_t` 后错误跳到文档末尾；正常路径仍为常数开销。
- UI 几何增长器现统一检查容量倍增、元素字节数乘法和零元素边界；共享 geometry、soft、
  GLES2、Break RHI 与 Vulkan state stack 的正常增长策略不变，异常尺寸在 allocator 前安全
  返回。TDD 验证普通后端 **30/30**、几何 **3/3**，ASan 后端 **30/30**。
- text area pointer y 命中复用统一的字体 line-height，避免带额外 leading 的字体按字号
  提前切换到下一行；不增加缓存或每帧扫描。
- text area 的 wrap 分页已按缓存中的 visual line 实现 `MY_KEY_PAGE_UP/DOWN`：长物理行
  会按 viewport 行数正确跨越，折叠行继续保持隐藏；目标查找复用已有二分索引和 RTL 边界
  映射，不新增 visual-line cache 分配且索引路径为 O(log V)。
- text area 绘制已使用 widget 生命周期内的可复用 scratch buffer：同一内容的后续重绘不再
  为每个 visual line 和光标临时分配字符串，容量仅在更长行出现时增长；普通 LTR 路径的
  scratch buffer 保持零新增 allocator 调用，分配失败继续走既有安全回退。
- JUSTIFY 单词绘制已改为 scratch buffer 原地切分并恢复分隔符，不再按单词分配临时字符串；
  连续绘制的分配契约覆盖普通 wrap 与 JUSTIFY 两条高频路径。
- visual-line cache 已保存 paragraph 提供的物理行内 byte 区间；绘制和光标文本准备直接
  复制缓存范围，避免长物理行按每个 visual line 重复扫描 UTF-8，保持可见字节数级别的
  工作量和既有 codepoint 坐标 API。
- RTL 绘制已在 widget scratch 文本未变化时跨帧复用 layout：默认方向对齐、选区矩形共享
  同一对象，光标方向判断和 visual-x 计算也只构建一次；scratch 改变会事务式失效旧对象，
  居中/右对齐等无需方向 layout 的路径继续保持快速分支。
- text area 已加入当前热物理行的 glyph boundary 前缀缓存：命中测试、光标、选区和 IME
  查询复用同一组 advance，重复边界查询为 O(1)；文本 revision、字体或字号变化会失效，
  OOM 时保留原逐 codepoint fallback，不为整篇文档增加几何缓存。
- 文本布局与 paragraph 入口增加 4 MiB 字节预算；超限输入在缓存、复制和字体测量前
  有界拒绝，拒绝路径不调用调用方 allocator，正常路径保持原有缓存与排版复杂度。
- 字体 shaping 公共入口增加独立 4 MiB 输入预算；超限文本在进入旧 provider、字体链或
  HarfBuzz 前拒绝，避免直接 API 绕过 layout 的输入限制。
- 公共 UTF-8 解码器严格拒绝 overlong、surrogate、超范围码点、非法 continuation 和
  截断序列；异常输入返回 `U+FFFD` 并单字节重新同步。检查无分配且为 O(1) 每个 codepoint，
  所有布局、字体链和后端入口共享这一安全边界。
- 新增后端无关的 `my_syntax_cache_t` 行级增量 lexer：C-like/YAML 词法 token、跨行
  block-comment 状态、后缀失效和每次重建预算均有明确边界；text area 现以懒创建和
  `syntax_line_budget` 消费 ready 行，并在非 RTL、有字体路径进行 token 颜色分段绘制。
  默认关闭时保持零 cache、零全文扫描；无字体、RTL、justify 继续回退整行绘制。
- vgcanvas 已提供零分配的 capability 查询；AA/filter 请求先检查能力，状态只在后端
  成功后更新并对重复请求短路。GL 只有当前 surface 报告 multisample 时才暴露 level 2；
  Break RHI/Vulkan 的真实 offscreen target 已支持设备能力允许的 2x+ 路径。
- 独立 Vulkan vgcanvas 现按 physical-device 与 image-format 能力报告 1x/2x/4x AA；
  level 切换、resize 和 swapchain out-of-date 重建均先构造 candidate target、render pass、
  pipeline 与 descriptor 资源，设备空闲且候选完整后一次性交换。创建、验证或提交失败只
  清理 candidate，不销毁 active；候选 MSAA 失败不再静默降级。顶层 `ENGINE_VULKAN` 现在
  同时启用 `myui_core` 的 Vulkan 编译定义与链接依赖。
- 新增后端无关的 sample-count/resize 事务 helper：候选资源按 `create -> validate ->
  submit -> activate -> retire` 提交；创建、验证或提交失败只销毁 candidate，保留
  active resource、样本数和尺寸。相同请求零分配、零重建；支持的样本数通过显式的
  power-of-two capability mask 表示。该 helper 已由 fake 状态机覆盖；BreakUI 的 resize
  与 AA 切换已接入同等的 candidate/active/retire 生命周期，独立 Vulkan vgcanvas 仍保留
  自己的 backend-specific target 边界。
- Break RHI 已新增只读 `RHICapabilities` 查询：统一报告后端类型、颜色/深度样本数能力、
  当前 surface 样本数和 resolve 能力；GL 从当前上下文查询，Vulkan 从 physical-device
  sample-count limits 与 depth-stencil resolve properties 查询。查询本身无分配、无同步、
  无状态改变。
- RHI 新增 `RHIOffscreenFBODesc` 与无副作用的 descriptor validation；旧创建 API 明确保持
  `1x`，不会因新增能力改变现有渲染行为。OpenGL 的 descriptor 路径已实现 multisample
  color/depth renderbuffer、单采样可读 texture 和切换时 resolve；Vulkan 使用 multisample
  color/depth attachment、单采样 resolve attachment 及匹配 sample-count 的 render-pass/
  pipeline variant。能力不足时明确拒绝，不静默降级。
- 已修复 resize 与 AA 请求同帧合并时 pending 请求被清除的缺陷；候选 target 激活后仍会
  保留尚未满足的 AA 请求，直到下一次 render 边界成功切换。OpenGL 候选 FBO 的 multisample
  renderbuffer、resolve FBO 和可采样纹理也统一走失败清理路径，避免资源泄漏。
- 已加入可选 OpenType shaping 契约：启用 `MYUI_HARFBUZZ` 且存在 FreeType/HarfBuzz 时，
  字体后端输出 glyph id、cluster、26.6 advance/offset；`shape_ex` 额外透传 direction、
  script、language 和有界 features。缺少依赖或后端不支持显式参数时返回
  `MY_RET_NOT_SUPPORTED`。Break RHI、GLES/OpenGL、Vulkan 和 soft canvas 的纯 LTR 路径
  已消费 glyph-run，并使用独立 glyph-id raster/cache key；shaping 失败仍回退 Unicode
  codepoint 路径。
- script resolver 已修正 Thai (`Thai`) 与 Thaana (`Thaa`) 的 OpenType tag 区分；BiDi 构建直接
  复用 SheenBidi Unicode 17 primary Script 数据，并接入仓库内由 Unicode 17.0.0
  `ScriptExtensions.txt` 生成的静态扩展表；Common/Inherited 字符先匹配前序
  Script_Extensions 候选，再匹配后序候选，避免共享字符在错误 script run 中 shaping。普通
  Common/Inherited 字符仍按邻接 run 优先继承前序 script，段首才使用后继 script，避免组合
  附加符号被错误送入相邻字体 script；当前还覆盖 Armenian、Georgian、Ethiopic、Myanmar、
  Khmer、Lao、Tamil、Telugu、Kannada 和 Malayalam 的常用 Unicode block 及 Greek、Armenian、
  Georgian、Ethiopic、Myanmar、Khmer 的常用 supplementary block；无 BiDi 构建保留常用
  block fallback；Arabic Common 标点
  与基本区/补充区 variation selector 不再误触发 script 分段或 bidi 路径；Hiragana、Katakana
  与半角 Kana fallback 已接入，常见长音符在同一 Katakana run 内保持连续。运行时表查找为
  O(log R)，无文件访问和额外分配；生成入口为 `tools/generate_myui_script_extensions.sh`。
- variation selector 的 fallback 契约已统一：bitmap、FreeType、stb、字体链、text-area 几何和
  soft/GLES/Vulkan/Break RHI 非 shaping 路径均不绘制独立 VS glyph、不增加 advance，字体链也
  不因 VS 切换 face；VS15/VS16 的 emoji/text presentation 仍依赖 OpenType provider。普通
  `test_myui_font` 现为 `29/29`（required feature 用例在无样本字体的机器上显式 skip）。
- feature policy 的公共输入边界已统一：所有 provider 在调用前拒绝空项、尾逗号和超过 32
  项的列表；`my_font_shape_features_normalize()` 无堆分配地统一 tag 顺序、`+/-` 语法和
  范围冲突，重复声明采用最后声明覆盖；规范结果同时进入 provider、paragraph 所有权和
  visual-boundary cache。FreeType/HarfBuzz 复用同一上限，输入/输出 buffer allocation
  失败时返回 OOM 并保持 glyph-run 事务为空。`my_font_shape_support_query()` 已提供
  GSUB/GPOS language-system 能力查询、feature tag 存在性检查、字体链聚合和逐级回退；缺失
  feature 明确返回 unsupported，且不会因不同 feature 请求错误命中旧 capability 缓存。FreeType
  读取 GSUB/GPOS LangSys required feature；required tag 的用户禁用请求会被提升为启用，普通
  feature 的显式关闭保持有效，隐式 script 也使用 HarfBuzz 推断结果。language-specific
  feature 选择和完整 OpenType feature 计划仍未实现。
- 真实 FreeType/HarfBuzz golden 验证 VS 附着 glyph 保持零 advance 与原始 byte cluster；
  fallback 则不创建独立 VS glyph。普通 `test_myui_font` 现为 `29/29`。
- FreeType glyph cache 现在在缓存提交前完成位图分配；OOM、尺寸乘法溢出或重试不会把空 glyph
  写入缓存，也不会先驱逐旧条目。可变字体 `wght` 坐标数组 OOM 会完整回滚 face/object，权重
  转换使用饱和整数运算。TDD 验证普通/ASan `test_myui_font` **29/29**。
- text layout shaping 增加固定 4 槽 LRU glyph-run cache；命中键包含字体、字号、方向、script、
  language 和 canonical features，命中后不再分配源数组或重新调用 provider。缓存写入失败
  保留当前结果，缓存复制失败只返回本次 OOM；layout 不拥有字体，字体及其 face 必须保持存活。
  TDD 新增参数隔离、缓存写入失败、命中单次输出分配和 LRU 淘汰用例，`test_myui_text_layout` 为 `66/66`。
- paragraph 新增 `my_text_paragraph_process_ex()`；换行测量与 glyph shaping 共享 direction、
  script、language 和 features，language/features 复制到 paragraph 所有权内，并通过
  `my_text_paragraph_shape_params()` 提供只读访问。参数复制失败保持构造事务回滚。
- paragraph 新增 `my_text_paragraph_line_layout()`，按需缓存逻辑换行段的视觉 layout；固定
  4 槽 LRU 在命中期间返回稳定指针，多行彼此隔离，单行 OOM 不污染缓存并可重试，paragraph
  销毁时统一释放已构建对象。
- text area 的绘制、命中测试、光标和 IME 现在共享按 visual line 的固定容量 RTL layout 缓存；
  缓存同时检查文本、字体、字号和 shaping revision。几何 shaping 使用
  `my_text_layout_process_n()`，不再为每次查询复制临时 NUL 字符串；soft、GLES2、Vulkan
  和 Break RHI 继续只消费公共 canvas API。
- RTL layout 缓存现扩展为固定 4 槽 LRU，绘制、命中测试、光标和 IME 访问共享多行 visual
  line 结果；空槽优先复用，满槽淘汰最久未使用项，新布局构建成功后才替换旧项。文本、字体
  或 shaping 参数改变时统一清空，避免 stale mapping；多行 RTL 连续重绘通过 TDD 验证不再
  产生 allocator 调用。
- paragraph 新增 `my_text_paragraph_process_n_ex()` 与 `my_text_paragraph_process_n()`，仅读取
  NUL-free 精确 slice；text area wrap 直接传入物理行范围，行 shaping 在自有副本中暂时隔离
  行尾 NUL，避免 provider 越过当前物理行。新增 slice、嵌入 NUL、空 slice 与跨物理行 shaping
  回归测试；当前 `test_myui_text_layout` 为 `72/72`。
- YAML UI 文件入口现于 payload 分配前检查 4 MiB 文件预算；超限输入立即关闭文件并失败，
  不再先申请整文件缓冲；文件中的嵌入 NUL 也明确拒绝，避免后续 YAML 字节被 C 字符串
  截断。字符串 loader 与 parser 的既有行数、深度、集合和标量预算保持不变；JSON、TOML
  与 BSON 直解析入口同样受 4 MiB 输入预算保护。
- RHI 窗口截图现提供带目标缓冲区长度的统一 RGBA8 API；GL 和 Vulkan 均在后端读回前
  校验 drawable 边界、零尺寸、乘法溢出和目标容量。Vulkan 继续使用一次性 staging
  buffer 与队列等待，失败返回 `false` 且不触碰目标缓冲；截图是诊断路径，不进入每帧热路径。

## 未完成能力

| 能力 | 当前边界 | 主要风险 | 完成判据 |
| --- | --- | --- | --- |
| OpenType shaping | 可选 HarfBuzz + FreeType glyph-run 已接入四个 canvas；字体 API 支持 direction/script/language/features；BiDi 构建复用 SheenBidi Unicode 17 primary Script 与仓库内 Unicode 17 Script_Extensions 表，paragraph 按 resolved Script 拆分 run，并保留 byte cluster 与失败回滚；无 BiDi 构建复用静态扩展表和常用 primary fallback；Common 标点、Inherited、variation selector 与假名归属已修正；非 shaping fallback 不产生独立 VS glyph；OpenType provider 清理未消费的 VS15/VS16 并保留 ZWJ 组合；字体链已支持 provider 可确认的跨 face variation glyph 覆盖选择；公共 feature 边界、规范化、冲突覆盖、GSUB/GPOS feature 存在性和 HarfBuzz buffer allocation 检查已统一；provider、字体链和 text-layout 聚合层共享 `MY_FONT_SHAPE_MAX_GLYPHS` 输出预算；每个 layout 提供固定 4 槽 LRU glyph-run cache | glyph/advance 与逻辑边界错配、字体缓存跨 key 污染、复杂 RTL 视觉顺序错误、未知 provider 的 variation 能力、font lifetime 不满足缓存契约 | 保持 glyph-id/codepoint 独立缓存；golden glyph/advance、超大 provider 输出、禁用依赖回退和四后端构建；后续补完整跨字体 variation corpus、language-specific feature 选择和完整 RTL GSUB |
| 复杂 RTL rebreaking | paragraph 按逻辑范围生成 cluster-safe wrapped lines，并在断行测量时复用 visual bidi glyph-run；text area 已消费该模型，RTL 行内映射、同一物理行及相邻物理行之间的全局 visual-line 水平导航、跨 face glyph-run、paragraph shaping 参数、全局 logical ↔ 局部 visual boundary 包装及单段落 JUSTIFY 的绘制/选区/光标联动已接入；跨 visual-line navigation cursor 解决共享 logical boundary 的连续箭头归属；GSUB/GPOS language-system 与 requested feature 存在性可查询；跨物理段落 visual rebreaking、跨段落增量预算和复杂多段落 JUSTIFY 联动仍未完成 | 光标、选区和 line hit-test 在 bidi run/换行边界错位 | 段落模型 golden visual order、重排后逻辑映射、跨 visual-line selection 契约；后续补完整 script/features run shaping 与跨物理段落增量 mapping |
| 高级编辑器 | 物理行折叠支持严格包含嵌套、有界 YAML v1 状态快照、legacy v0/无版本快照显式升级、可见行缓存 O(rows+ranges) 构建、OOM 正确性回退、行号栏、wrap 增量缓存、visual-line 分页、绘制 scratch 复用、行级 lexer、LTR/RTL 受限 token 着色已实现；完整 RTL GSUB、跨 face token shaping 和 JUSTIFY 联动未实现 | 大文档单帧 O(n) 卡顿、折叠后索引失效、token 状态跨行污染 | 继续保持 lexer/cache 单帧预算，并补齐 paragraph/run 级 RTL shaping |
| 真 partial present | 已完成后端无关的 `SKIP/PARTIAL/FULL` 决策、RHI 有界 damage 帧接口、Wayland EGL buffer-age/damage-present 接入和 dxx 集成；Wayland 在 `EGL_BUFFER_PRESERVED` 成功协商后使用固定容量 history 合并 age>1 重绘区域，history 仅在 swap 成功后更新，失败/resize 自动清除；GLX 仅在同时检测到 `GLX_EXT_buffer_age`、`GLX_EXT_swap_buffers_with_damage`、运行时交换函数和有效固定容量 history 时启用等价路径，其他 X11 驱动继续安全全屏；新增 X11/Wayland platform runtime smoke；Vulkan 仍安全全屏，`VK_KHR_incremental_present` 不启用为能力位，因为该扩展不保证 present 后 swapchain image 内容可被 `LOAD`；Win32/macOS 仍安全全屏 | 未损伤区域内容丢失、WSI 内容保留语义误用、Vulkan 缺少标准 buffer-age/内容保留契约、真实平台能力未覆盖 | Weston/Xvfb 只验证窗口与事件生命周期；仍需真实 Wayland/GLX buffer-age 轮转、Win32/macOS retained-buffer 语义、异常 present 及具备明确 image 保留保证的 Vulkan/WSI 方案 |
| 完整 UAX#14 默认规则 | Unicode 17 `LineBreakTest.txt` 已通过 60,487/60,487 边界；SA dictionary 基础 callback 和 paragraph/wrap 接入已完成；核心状态机固定内存、无分配、无锁 | locale-specific tailoring、调用方 SA dictionary 质量和真实平台语言策略 | 版本化 UCD golden corpus 已完成；后续补 locale dictionary corpus、超长输入预算和产品级 tailoring 契约 |
| 完整 CSS/YAML UI | CSS 已支持最多 4 级祖先路径、descendant/direct-child 链及祖先 type/class/id；主题桥接和 YAML 窗口 style 已有严格诊断与失败回滚；CSS 现提供只读 capability registry 和稳定错误码；`@media all`/`@media screen` 在解析期展开且嵌套有界；新增带一次性上下文的条件媒体解析期评估，支持有界 viewport、orientation、颜色方案、reduced-motion、width/height range，以及 hover、pointer、any-pointer、color-gamut、dynamic-range 设备能力条件；受限 `@media not` 仅修饰单个媒体特性并保留 unknown 语义，查询热路径无媒体分支；YAML UI loader 已替代 XML、采用类型化 schema，支持有界 schema version/migration chain、动态 owned schema，并提供 loader 级 capability registry/error code；query 结果复制到调用者固定存储，动态 schema 替换以跨平台读写租约保护并等待在途加载/查询结束；class registry 已支持冻结后的不可变 table snapshot 运行期新增、替换和删除，loader factory/schema 也支持冻结后的低频运行期新增、替换和删除，旧 descriptor 指针保持进程期稳定；运行期动态 schema 在校验和完整 owned copy 成功后才发布，OOM/非法参数保持旧条目；CSS/YAML/JSON/TOML/BSON 入口均有 4 MiB 输入预算 | 其他 at-rule 语义、HDR/P3 等缺少明确证据的设备能力、全平台 runtime CI；动态 class/factory 回调代码卸载仍需调用方 quiesce 实例和读者 | 将 registry/error 契约扩展到更细 schema 定位；补媒体能力 golden corpus 与真实平台上下文接入，并完成真实平台 runtime 证据 |
| 平台 runtime CI | 平台配置契约已统一：`platform_create()` 在所有后端进入原生 API 前拒绝 NULL/空标题/非法 UTF-8/零尺寸/超限尺寸；对象查询/控制路径已统一 NULL-safe，媒体/剪贴板失败输出有确定状态；X11 smoke 已接入 Xvfb graphics CI，Wayland smoke 已接入 Weston headless GL/Vulkan CI；Windows 已有无 graphics 的 platform smoke（UTF-8 标题、非法输入、WM_SIZE、销毁）；macOS smoke 已接入 macOS runner | 构建和 headless compositor smoke 通过但 DPI、IME、present、buffer-age 在真实宿主失败；Windows/macOS 证据依赖对应 runner | Windows/macOS 原生 smoke + 各平台启动 smoke + HiDPI/IME/resize/present/buffer-age 证据；当前 Xvfb/Weston smoke 不代表 GPU/WGL/Vulkan 全部成功 |

### 冷却按钮契约

`my_button_set_cooldown(button, duration_ms)` 设置下一次成功 click 后采用的默认冷却时长。
`duration_ms == 0` 会禁用冷却并立即取消动画 timer；修改非零 duration 不会中断当前
冷却，只影响下一次 click。`my_button_is_cooling_down()` 每次按当前 PAL 单调时钟检查
deadline，不能以 timer 是否存在作为业务判断。`remaining_ms` 返回饱和值，
`cooldown_progress` 返回 `[0, 1]`，其中 `1` 表示刚开始、`0` 表示完成。
当 PAL 明确报告 `reduced-motion` 时，按钮仍实时执行冷却检测并显示静态遮罩，但不创建
16ms 动画 timer，而是只保留一个冷却周期级完成 timer 以在截止时清除遮罩；偏好在下一次
冷却周期开始时重新采样。unknown 不等同于 reduce，保证
缺少平台事实时不牺牲既有动画行为。
remaining/progress 每次查询只读取一次 PAL 时钟，并在该采样值上完成比较和饱和换算，
保证时钟边界瞬间的结果一致且不产生无符号下溢。时钟回拨时最短按压保护不会提前
释放；deadline 饱和到 `UINT64_MAX` 时仍按起始时间计算有限冷却，并跳过无法到期的
动画 timer，避免主循环忙循环。

冷却中的按钮不进入 pressed 状态，也不发出 `click`。成功 click 先建立 deadline 再
发射事件，防止同步回调重入绕过限制。动画是从上到下的半透明公共 canvas 遮罩；timer
抖动不会改变实际冷却时长。没有 PAL/loop 时查询仍安全，按钮可在挂载后正常获得动画
驱动；timer 创建失败不影响 deadline 检测和输入安全。

按钮同时支持指针和键盘激活：焦点按钮的 Return/Space 使用成对的 `key_down`/`key_up`
状态，只对首次按下的同一按键发出一次 `click`；重复按下、错键释放和冷却期间的键盘
输入均被拒绝，避免不同 PAL 输入后端产生重复激活。

性能约束：非冷却状态无 timer、无逐帧扫描、无堆分配；冷却期间每个按钮最多一个
timer，每 tick 只读取单调时间、计算进度和 invalidate。按钮销毁始终先移除 timer，
避免回调访问已释放对象。

## 实施顺序

### 阶段 A：基础契约与观测

1. 保持 `my_vgcanvas` 公共 API 稳定；新增只读 RHI capability query，不让 widget
   直接依赖 Vulkan/OpenGL 类型。
2. 为所有候选资源采用 `create -> validate -> submit -> activate -> retire` 状态机；
   失败只释放 candidate，不触碰 active resource。resize 与 sample-count 必须共用
   同一事务，避免窗口尺寸变化和质量切换产生两个不一致的生命周期。
3. 为每帧记录 damage area、draw calls、atlas misses、layout passes 和 fallback
   次数；默认关闭高成本日志，诊断模式才采样。

### 阶段 B：GPU AA

1. 先写 fake device 的能力和事务测试：支持/不支持/创建失败/提交失败/重复设置。
2. RHI 提供 color/depth sample count 和 resolve compatibility 查询；GL 读取已创建
   surface 能力，Vulkan 使用 physical-device limits 与 depth-stencil resolve properties。
3. 离屏 target 增加 sample-count descriptor；MSAA color/depth 与单采样 resolve target
   一起候选创建，render pass/pipeline 全部验证后再激活。Vulkan shadow/MRT 多采样 pipeline
   在 attachment 契约完整实现前明确拒绝，避免误用 1x render pass。
4. 旧 target 保持可用直到新 target 首次提交成功；resize、DPI、device lost 都走
   同一事务路径。设备不支持时返回 `MY_RET_NOT_SUPPORTED`，不静默降低用户设置。

### 阶段 C：可选 HarfBuzz shaping

1. CMake 自动检测 HarfBuzz，默认可选；关闭或缺失时保留现有 Arabic fallback。
2. 以 UTF-32 paragraph/run 为输入，按 script、direction、font identity 和字号
   分割 shaping run；输出 glyph id、advance、offset 与 logical span。当前已落地
   `my_font_shape_ex()` 与 `my_text_layout_shape_ex()`，显式参数只在 provider 支持时生效，
   旧 `shape` callback 保持兼容。
3. 缓存键必须包含字体身份、face index、字号、script、direction、feature set 和
   text hash；当前 layout 持有固定 4 槽 LRU glyph-run cache，canonical shaping
   参数参与键，缓存写入失败只放弃缓存、不影响当前结果；命中复制失败只影响本次调用。
4. 已接入测量与 Break RHI、GLES/Vulkan/soft 的 glyph upload；任一后端失败
   不改变其他后端路径。BiDi 构建已使用 SheenBidi Unicode 17 primary Script 数据，无 BiDi
   构建保留常用 block fallback；当前仍不覆盖完整 UAX#24 script extensions；Common Arabic
   标点及 variation selector 视为不触发 script 分段的字符；
  完整 script extensions 语义、provider-specific variation glyph 覆盖、OpenType feature 选择、跨段落
  增量 shaping 与完整 RTL/复杂 GSUB 仍需后续 golden corpus 验证；script/language
  capability 查询和默认回退已接入。

### 阶段 D：段落、编辑器和断行

1. 已新增 paragraph model，保留逻辑 codepoint 范围并让 text area wrap 共用该结果；
   shaping 参数可通过 `my_text_paragraph_process_ex()` 保持换行测量一致。下一步把每个 line
   的 visual layout、justify、selection、cursor 也统一到 paragraph-owned mapping。
2. 使用增量 dirty paragraph 队列和每帧预算；长文档只重排受影响行及其邻接上下文。
3. 行号、折叠和语法高亮只消费行模型，不进入 widget paint 回调；折叠区间使用
   checked interval tree，所有偏移转换做边界检查。

### 阶段 E：Present 与平台矩阵

1. 先让平台报告 damage/retained-buffer/partial-present 能力；没有三者时继续全屏
   composite，禁止仅凭 dirty rect 设置 scissor。
2. 有 retained backbuffer 时按 dirty area 与全屏成本阈值选择局部合成；合并区域超过
   预算即全屏，避免碎片化 draw call。
3. Wayland 使用 compositor 认可的 damage API；X11/Win32/Cocoa 分别验证 buffer age、
   swap semantics 和 resize；Vulkan WSI 只在 explicit synchronization 契约成立时启用。

## 统一 TDD 与安全门禁

- 单元：每个新增能力先有失败测试；测试输入覆盖空值、边界、溢出、分配失败和重复调用。
- 跨后端：`build-myui`、`build-myui-vk`、Wayland GL/VK；X11 smoke 在 Xvfb graphics
  job 执行，Wayland smoke 在 Weston headless job 执行，当前主机没有 runtime 服务时只
  报告 build/headless 证据，不声称运行时通过。
- Sanitizer：ASan/UBSan 覆盖 CSS、文本、damage、资源生命周期；线程相关改动再跑
  TSan，协议队列不允许等待外部 owner。
- 性能：固定 corpus 对比布局时间、峰值内存、draw call、atlas miss 和 composite
  像素面积；性能优化不得牺牲 active resource 回滚和输入预算。
- 交付：文档、测试和实现一起提交；`git diff --check`、乱码扫描、工作区清洁后才推送。

## 已完成：syntax token byte range cache（2026-08-26）

- 以 TDD 新增 `syntax_cache_records_utf8_token_byte_ranges`，先验证多字节 UTF-8
  identifier、ASCII keyword 和 number 的 codepoint/byte 范围同时准确记录。
- lexer 在已有 `at/cp` 单次扫描中填充 `start_byte/len_bytes`；text area syntax paint
  直接使用范围裁剪 wrapped visual line，删除每个 token 调用 `ta_byte_at_cp()` 的
  物理行首扫描，连续 token 绘制不再产生 token 数量乘行长度的重复工作。
- 复杂度：词法分析 O(line bytes + token count)，整 token 绘制 O(1)，每个 visual line
  最多处理其首尾边界 token；codepoint 坐标、后端中立 API、lexer 行预算和失败回退
  行为保持不变。
- 验证：normal/ASan 的 `test_myui_text_layout` **14/14**、
  `test_myui_window_manager` **55/55** 通过，Vulkan `myui_core` 构建通过；全量
  非图形 ctest 仍受当前构建目录缺少历史测试二进制影响，且已有无关的网络测试失败，
  不将这些结果归因于本改动。后续继续审查 paragraph-owned mapping、HarfBuzz shaping
  与 partial present。

## 已完成：visual line physical-row index cache（2026-08-26）

- 以 TDD 新增 `text_area_visual_line_index_cache_tracks_folds_and_edits`，覆盖 wrap
  行映射、折叠隐藏行、整段编辑后的重建；新增
  `text_area_visual_line_index_cache_oom_falls_back` 覆盖索引分配失败回退。
- `my_text_area` 为每个物理行缓存首尾 visual index，命中后只在该物理行的连续 visual
  段内二分；缓存不改变 visual line 所有权、paragraph byte span 或后端 API。
- 映射最多分配 `2 * physical_line_count * sizeof(size_t)`，OOM 时释放候选并回到旧的
  全量二分，不重试每次查询；折叠、编辑、wrap/字号/宽度重排统一失效，避免旧索引
  指向新文本。
- 验证：normal/ASan 的 `test_myui_window_manager` **57/57**、
  `test_myui_text_layout` **14/14** 通过，Vulkan `myui_core` 构建、
  `git diff --check` 与乱码/控制字符扫描通过。

## 已完成：RTL interaction layout cache（2026-08-27）

- 以 TDD 新增 `text_area_rtl_hit_test_reuses_layout`，先证明连续 pointer hit-test 会
  重复分配 visual line 文本和 layout，再实现 widget-owned 单条缓存。
- 键盘左右移动、上下移动、Home/End、PageUp/PageDown 与 pointer hit-test 共享当前
  visual line 的 layout；缓存键包含 text revision、物理行、byte span、字体和字号，
  文本编辑与字体变化自动失效。
- 命中路径无临时复制、无 layout 分配；纯 LTR 仍无 layout 开销，OOM 或 layout 失败
  保持原有安全回退。生命周期在 widget destroy 中释放，核心 API 与 soft/GLES/Vulkan/
  Break RHI 边界不变。
- 验证：normal `test_myui_window_manager` **58/58** 通过；ASan、Vulkan 和文档门禁
  在本阶段收尾复验。

## 已完成：text layout visual boundary prefix cache（2026-08-27）

- 以 TDD 新增 `text_layout_reuses_font_boundary_prefix_cache`，验证视觉 x、命中测试和
  selection rects 首次计算字形宽度，连续查询不再重复调用 glyph；字号变化会重建。
- `my_text_layout_t` 按调用者 layout 缓存 visual boundary 前缀和，键为字体指针与字号。
  `visual_x` 为 O(1)，`logical_at_x` 在前缀和上二分，selection rects 复用宽度，首次
  建立为 O(visual items)。
- 分配失败保留旧缓存并回退原逐字形路径；缓存由 layout destroy 释放，不影响全局 LRU
  master、glyph-run、soft/GLES/Vulkan/Break RHI API 或字体无关的 bidi 映射。
- 验证：normal/ASan `test_myui_text_layout` **15/15**，normal/ASan
  `test_myui_window_manager` **58/58**，Vulkan `myui_core` 构建和编码门禁通过。

## 已完成：selection rect bounded output（2026-08-29）

- 以 TDD 新增 `text_layout_visual_rects_honors_output_capacity`，先复现多视觉片段时
  API 返回值超过 `cap` 的契约缺陷。
- `my_text_layout_visual_rects()` 在缓存和逐字形回退路径都严格返回 `0..cap`，写满
  输出后立即结束，避免在 text area/edit 只请求固定小数组时继续扫描。
- 保持 RTL 分段顺序、字体宽度、OOM 回退和跨后端绘制行为不变；公共头文件同步明确
  有界返回契约。
- 验证：`test_myui_text_layout` **16/16** 通过；normal/ASan/Vulkan 门禁已复验。

## 已完成：fold-state YAML legacy migration（2026-08-29）

- 以 TDD 新增 `text_area_fold_state_yaml_roundtrip_and_transaction` 的显式 v0 输入断言，
  先验证 loader 错误拒绝 legacy 版本号。
- `version: 0` 现在表示旧版 `folds` schema，与既有无 version legacy 输入使用相同的严格
  字段、范围、数量和字节预算；成功导入后 exporter 始终生成 `version: 1`，形成可观测的
  单向升级，不增加绘制或编辑热路径成本。
- 保持未知版本拒绝和事务回滚语义；不恢复 XML 兼容层，不引入全局迁移状态。
- 验证：normal/ASan `test_myui_window_manager` **58/58**，Vulkan `myui_core` 构建及
  编码门禁通过；LeakSanitizer 继续使用 `detect_leaks=0` 规避当前 ptrace 环境限制。

## 已完成：RTL syntax token painting（2026-08-29）

- 以 TDD 新增 `text_area_rtl_syntax_colors_tokens`，旧实现因 RTL 保护分支退回整行普通
  颜色，测试先验证带 YAML keyword 的 RTL 行与无高亮基线完全相同。
- RTL token 绘制复用 `my_text_layout_t` 的 visual UTF-8 与 visual boundary prefix，按
  visual-order 连续片段设置 token 颜色；token logical 范围用二分查找，避免 token 数量乘
  visual item 数量的扫描。LTR 路径保持原单次 token 测量。
- 新增 `my_text_layout_visual_boundary_x()`，将视觉边界坐标作为公共 core 契约；不依赖
  GL、Vulkan、soft、Break RHI 或平台类型。复杂 RTL GSUB、跨 face fallback 与 JUSTIFY
  token 联动仍由 shaping/paragraph 阶段处理。
- 同步修复内置 bitmap font 的 1bpp-to-8bpp 边界缺陷：创建时展开固定 8x8 alpha 块，避免
  绘制时越界读取，并保持每帧零格式转换。
- 验证：normal/ASan `test_myui_window_manager` **59/59**、normal/ASan
  `test_myui_text_layout` **16/16**，Vulkan `myui_core` 构建及编码门禁通过；LeakSanitizer
  使用 `detect_leaks=0`。

## 已完成：跨字体 glyph-run 事务与 RTL run 顺序（2026-08-31）

- 以 TDD 新增字体链跨 face shaping 测试：Latin/CJK 连续片段分别调用对应 face，输出
  glyph 保存实际字体身份，cluster 继续使用原始 UTF-8 byte offset；四个绘制后端的
  glyph-id 栅格化与 atlas/texture cache 均按 `(font, glyph id, size, key kind)` 区分。
- 字体链的 LTR 单 face 路径保持原有快速路径；RTL 仅在确实跨 face 时建立有界 run 表，
  以逆序提交 face run，避免 CJK fallback 片段在视觉顺序中落到错误位置。候选结果全部
  成功后才交付，任一 segment、扩容或 allocator 失败都会释放候选并清空结果。
- 新增逐分配点 OOM 回滚测试和跨 face RTL 顺序测试；未声明 HarfBuzz/FreeType 时测试
  仍编译为显式 skip，不改变旧 codepoint fallback。
- 当前已把 paragraph bidi run 的 direction、logical byte cluster 和实际字体身份统一
  交给 glyph-run API，并接入四个 canvas；仍未宣称完整 RTL OpenType，script/features
  配置、selection/cursor/justify 的 paragraph-owned glyph mapping 还需继续完善。
- 验证：普通字体/后端测试 **8/8、24/24**，Vulkan 字体/后端测试 **8/8、25/25**，
  ASan 字体/后端测试 **8/8、24/24**；无 HarfBuzz 配置也完成 **8/8、24/24**，其中
  shaping 专项按契约 skip。以上是构建目录定向证据，不替代 Windows/macOS/Wayland
  真实 runtime 验证。

## 已完成：OpenType capability feature 校验（2026-09-02）

- 以 TDD 增加 FreeType/HarfBuzz capability 用例：查询不仅验证 GSUB/GPOS 的 script/language
  system，还验证 requested feature tag 是否存在；`liga` 等真实 tag 可通过，`zzzz` 等未知
  tag 明确返回 unsupported。
- capability LRU 现在把 canonical feature set 纳入键，避免无 feature、已知 feature 和未知
  feature 请求互相污染；请求 feature 先去重，检查最多 32 个 tag，运行时不执行无界表扫描。
- required feature 优先级现已接入：FreeType 读取 GSUB/GPOS LangSys required tag，用户对该
  tag 的 `-tag`/`tag=0` 请求会被提升为启用；普通 feature 的显式关闭不改变。隐式 script
  使用 HarfBuzz buffer 推断结果；诊断入口只返回固定上限内的整数 tag/count。
- 语义保持保守：feature 不存在时只影响 capability 判定，shape provider 仍遵循已有兼容回退；
  language-specific feature 选择和完整 OpenType feature 计划仍未实现。
- 验证：普通 `test_myui_font` **29/29**、无 BiDi `test_myui_font` **29/29**、ASan 字体
  `25/25`、无 HarfBuzz 字体/布局构建通过；required feature 用例在没有对应系统字体时显式
  skip；普通配置排除环境挂起的 Vulkan runtime 后
  CTest **81/81**。

## 已完成：RTL 多行 layout LRU 缓存（2026-09-02）

- 以 TDD 新增 `text_area_rtl_paint_caches_multiple_visual_lines`，先证明单槽缓存对四行
  RTL 文本的第二帧会反复分配，再实现固定容量缓存并验证第二帧零新增分配。
- `my_text_area_t` 现在内置 4 槽 RTL layout LRU；槽位键包含物理行、visual byte span、
  text/shaping revision、字体和字号。构建失败保留旧槽，替换与失效均释放明确，避免 OOM
  半成品和 layout 泄漏。旧 `rtl_layout` 字段仅作为最近命中 layout 的兼容镜像。
- 验证：普通、无 HarfBuzz、ASan 的 `test_myui_window_manager` 分别 **75/75**；普通、
  无 HarfBuzz、ASan 的 text layout/font/backend 核心测试分别为 **57/26/26**。非图形全量
  CTest 中除现有网络端口受限的 `test_network`、`test_net_replication` 外，其余测试通过。

## 已完成：数字上下文断行状态（2026-09-02）

- 以 TDD 新增指数符号、货币符号和百分号数值序列测试，锁定 `1e-10`、`$10%` 等序列不被
  换行拆开。
- `my_line_break_state_t` 增加有界 numeric context；指数标记、指数正负号、货币和百分号
  规则在 streaming feed 中处理，不增加堆分配，也不改变 Regional Indicator 成对状态。
- 普通、无 HarfBuzz、ASan 的 `test_myui_text_layout` 均为 **72/72**；SA dictionary 基础 callback、
  locale-specific numeric tailoring、完整 UCD 版本规则仍保留在未完成清单。

## 已完成：paragraph bidi glyph-run 接入（2026-09-01）

- 新增 `my_text_layout_shape()`：按布局的视觉 bidi run 还原逻辑 UTF-8 输入，按 resolved
  direction 调用字体 shaping，再按视觉顺序合并 glyph；cluster 映射回原始 UTF-8 byte
  offset，并保留实际 face 身份。
- soft、GLES2、Vulkan、Break RHI 的复杂文本绘制和测量统一消费该 glyph-run；字体不支持
  shaping 时显式回退原 visual codepoint 路径，其他错误不提交部分结果。
- 输入长度、run 数量、数组乘法、重复 logical mapping 和 allocator OOM 均有边界检查；
  layout 还保存 caller-owned logical UTF-8 副本，拒绝不匹配输入或非 codepoint 边界的
  provider cluster；输出采用候选事务，失败时清空结果，避免 selection/cursor 使用半成品。
- 当前仍未宣称完整 Unicode script/features shaping：有限 script 分段、OpenType feature
  透传和 script/language capability 回退已完成；UAX#24 script resolution、variation selector、跨段落增量
  rebreaking 和 JUSTIFY selection 联动留作后续阶段。
- paragraph 断行测量现在对需要 bidi 的行先走 `my_text_layout_shape()`，按 visual run 的
  resolved direction shaping；cluster 不在 UTF-8 codepoint 起点时整段失败，不静默忽略
  provider 输出。无 HarfBuzz 时保持原有 codepoint fallback。
- 验证：文本布局 **40/40**，普通字体/后端 **11/11、26/26**，无 BiDi **40/40、67/67**，
  ASan/UBSan 字体/布局/后端/窗口 **11/11、37/37、26/26、71/71**；Vulkan、Wayland GL/VK 的 `myui_core`
  配置构建通过。
  `engine/build` 全量 CTest 中实际存在的 77 个测试全部通过；4 个未生成的可选
  rule-engine 目标为 `Not Run`，不属于本轮源码回归失败。

## 已完成：shaping-aware text geometry 与字体回调安全（2026-09-01）

- 以 TDD 新增连字 `fi` 的 text-area 非 wrap pointer hit-test；几何缓存现在使用 shaping glyph
  advance 和 cluster span，selection、命中测试及 IME 坐标共享同一视觉前缀和。
- 修复字体抽象层的可选 vtable 回调契约：`measure`、`get_glyph`、metrics、destroy 和
  `get_glyph_id` 缺失时安全返回，不再解引用空函数指针；shape-only font 继续可用于布局几何。
- 修复 YAML 折叠快照测试中重复覆盖输出指针的泄漏，明确导出字符串由调用方按传入 allocator
  释放，保持解析事务和版本迁移语义不变。
- 验证：普通、无 HarfBuzz、Vulkan、ASan 四套构建的 `test_myui_text_layout`、
  `test_myui_font`、`test_myui_vgcanvas_backend`、`test_myui_window_manager` 均通过，
  每套 **4/4**；ASan 同时通过新增 shape-only 路径且无泄漏报告。

## 已完成：RTL text-area geometry 与 IME boundary 对齐（2026-09-01）

- 以 TDD 新增非 wrap/wrap RTL IME spot 测试，以及 RTL logical boundary geometry 测试，锁定
  光标、绘制和平台候选框不能分别使用 logical cell x 的契约。
- text area 的 RTL IME 更新现在复用 widget-owned layout cache，按 shaping visual advance、
  paragraph direction 和 LEFT/CENTER/RIGHT 对齐计算坐标；wrap 模式也不再使用固定 cell 宽度。
- geometry prefix 的填充改为 logical boundary -> visual x，而不是把 visual boundary index 当作
  logical boundary，修复 RTL 水平滚动和可见性查询的坐标倒置；LTR/ligature 路径保持原有缓存。
- 验证：普通、无 HarfBuzz、Vulkan、ASan 配置均通过相关 text-area、text-layout、font 和
  canvas 测试；完整 OpenType script/features、跨段落增量 rebreaking 和 RTL JUSTIFY 联动仍
  保持在未完成列表中。

## 已完成：无 shaping provider 的 RTL geometry 回退（2026-09-01）

- 以 TDD 新增无 HarfBuzz/无 shaping provider 的 RTL logical boundary 测试，确保 bitmap 等
  基础字体的水平可见性和 IME 坐标仍按视觉顺序计算。
- 新增长度受限的 `my_text_layout_may_need_bidi_n()` 预扫描；geometry 只在目标物理行确实
  含 bidi codepoint 时创建 layout，普通 LTR 行保持无 layout 的快速路径。
- 验证：新增 text-layout 预扫描测试和 text-area 全量测试通过；后续完整 OpenType
  script/features、跨段落增量 rebreaking 和 RTL JUSTIFY 联动仍保持未完成。

## 已完成：shaping 参数敏感的 geometry cache（2026-09-01）

- 以 TDD 新增 `text_layout_boundary_cache_keys_shaping_parameters`，fake `shape_ex`
  provider 对不同 feature 返回不同 advance；同一 layout/font/size 切换参数时必须重新
  shaping，切回旧参数也不能误用新 geometry。
- 新增 `my_text_layout_visual_x_ex()`、`my_text_layout_visual_boundary_x_ex()`、
  `my_text_layout_logical_at_x_ex()` 和 `my_text_layout_visual_rects_ex()`；旧 API 继续
  使用兼容默认参数。boundary cache key 现在包含字体、字号、direction、script、
  language 内容和 features 内容，字符串由 layout 复制并受既有预算保护。
- `my_text_area_set_shaping_params()` 以事务方式复制、校验和规范化参数；等价 feature 列表
  不产生伪 revision；text area 的 wrap、
  geometry、光标、selection、IME 查询共用 shaping revision 和显式 geometry API，参数
  变更不会留下旧 boundary。新增所有权、超长输入和失败保持旧状态测试。
- 验证：`test_myui_text_layout` **36/36**、`test_myui_window_manager` **71/71**；
  无 BiDi 配置的 `test_myui_text_layout` **36/36**、`test_myui_window_manager` **67/67**；
  普通 build-myui-tests 构建通过。完整 OpenType script resolution、variation selector、
  完整 language-system feature 选择、跨段落增量 rebreaking 和 RTL JUSTIFY 联动仍未完成。
- 四个 canvas 现通过 base canvas 的同步 shaping 上下文支持
  `my_vgcanvas_draw_text_ex()`/`my_vgcanvas_measure_text_ex()`；旧 vtable 布局和默认 API
  保持兼容。上下文只在调用期间有效，避免跨帧悬空指针；各后端继续以当前 glyph-id/
  font/size cache 消费结果。新增 soft 参数透传 golden advance 测试，GLES/Vulkan/Break
  RHI 共享同一 helper 并完成编译验证。

## 已完成：字体 setter 与动态容量边界（2026-09-02）

- TDD 锁定 `set_font()` 的统一参数语义：字号必须大于零，失败不改变旧字体/字号；soft、
  GLES/OpenGL、Vulkan 和 Break RHI 的实现保持一致。
- 几何输出、路径容器、状态栈和 Vulkan 延迟释放队列拒绝计数/容量回绕；文本布局、paragraph、
  syntax 及 YAML 行/标量缓冲拒绝终止字节与倍增溢出。正常扩容仍为摊销增长，不增加每帧分配。
- 普通 myui 聚焦测试 **12/12**、backend ASan/UBSan **1/1** 通过。全量 CTest 因既有
  `test_vulkan` runtime 长时间无输出而主动停止，需在可用 Vulkan runtime 上单独复验。

## 已完成：图形集成测试同步稳定性（2026-09-02）

- `test_vulkan` 在测试设备创建后关闭 vsync，消除 GLX 交换缓冲对 compositor refresh event
  的隐式依赖；生产运行时 vsync 默认和 API 不变。
- OpenGL 图形集成测试的 IBL、golden、间接绘制、材质数组和 deferred 数组门禁通过；全量
  CTest 已恢复为 **82/82**。Vulkan/Wayland/Windows/macOS 的实际设备与 compositor smoke
  仍属于平台 runtime 验证，不因本机 OpenGL 通过而提前关闭。

## 仍未完成：下一阶段明确边界

## 本轮补充：Vulkan WSI 扩展 sidecar（2026-09-07）

新增 ABI-safe 的 `my_pal_vulkan_provider_t` 注册表，避免为了 Vulkan WSI 扩展协商而
追加 frozen PAL vtable 字段。provider 查询经过固定容量、ABI、输出数组深拷贝和注销期间的
in-flight 生命周期校验；myr 窗口路径可在初始化前查询扩展，实例状态保存实际启用集合，
活动实例拒绝未在首次创建时启用的扩展。扩展数组不跨调用保存，正常绘制热路径不增加
锁、分配或扫描。

该 sidecar 不替代 `vk_create_surface`：宿主仍须提供与自身 VkInstance 所属的 surface
创建实现，Break PAL 因复用宿主 RHI 的 device/swapchain 仍保持不拥有 myui Vulkan surface
的安全边界。TDD 已覆盖 ABI 错误、失败输出清零、异常成功输出、替换和注销；真实
Windows/Wayland/X11/macOS WSI 创建与 compositor present 仍需平台 runtime CI。

## 本轮补充：Vulkan 全局生命周期并发闸门（2026-09-07）

Vulkan 共享 instance/device 的初始化、引用计数、peek 和最终销毁现在由 C11
`atomic_flag` 保护。该锁只存在于全局资源的冷生命周期路径；canvas 的绘制、提交、
缓存和布局路径不持有该锁。初始化失败仍统一清零状态，多个线程并发获取不会重复创建
设备或在失败清理期间观察到半初始化句柄。

TDD 新增多线程 acquire/release 回归，并把 `test_myui_vgcanvas_backend` 显式链接
`Threads::Threads`。该测试在无 Vulkan 设备时允许全量安全失败，在有设备时要求所有 lease
完成后全局 peek 为空；跨线程使用同一个 canvas、跨线程销毁 canvas 以及 PAL/UI 句柄的
线程亲和性仍不由此 API 放宽。

## 本轮补充：Vulkan PAL WSI 扩展协商与离屏先行兼容（2026-09-07）

窗口 PAL 现在按实际平台返回借用的 Vulkan instance extension 列表；myr 不再猜测或
强制启用 Linux/Windows/macOS WSI。Vulkan 实例初始化会校验请求集合并保存已启用集合，
活动实例不能被不安全地“升级”；为兼容离屏 canvas 先于窗口 canvas 创建的常见顺序，
首次无 WSI 请求时只把当前 loader 支持的 WSI 扩展作为一次性可选预留，并不创建 surface，
从而保持单实例/单设备共享和窗口后续创建能力。窗口路径仍必须由 PAL 显式声明扩展，
缺失扩展或 swapchain 能力时安全返回 `MY_RET_NOT_SUPPORTED`。

TDD 新增 PAL 可选扩展查询的空对象/部分 vtable 契约和 Break 平台扩展映射回归；普通
myui PAL/backend 专项与 Vulkan 构建回归通过。真实 Windows WSI、macOS MoltenVK、
Wayland/X11 compositor present 仍需平台 runtime CI；多 Vulkan instance/context 并行
隔离不在本轮范围内。

## 本轮完成：Menu 操作重入与级联销毁安全（2026-09-06）

菜单 popup 的关闭和销毁路径现在具备单线程操作深度保护：overlay destroy chain 会先摘除
所有弱引用、timer、窗口/manager listener 及 owned callback state，再调用 context destructor。
如果 destructor 重入销毁菜单，释放会延迟到最外层操作结束；父菜单、打开的 submenu 和窗口
关闭链也会逐级失效，不再把悬空模型交给 hover timer 或事件回调。该设计只保护所属 UI loop
上的重入，不把裸菜单句柄变成跨线程安全句柄。

TDD 新增菜单/窗口级联销毁和 owned context destructor 重入回归；普通、ASan/UBSan 及
Clang TSan 窗口管理专项均为 207/207。仍未完成项包括通用 borrowed callback context
自动失效协议、跨线程菜单操作，以及真实平台 compositor 下的 popup/IME/输入矩阵。

## 本轮完成：动态 class lease 线程归属安全（2026-09-06）

class callback lease 现在带有跨平台获取线程标识，只有获取线程可以释放；外部线程释放会
安全保持 lease 活跃，不会减少 snapshot/module 计数或清理获取线程的 registry callback
guard。这样 module quiesce 的等待条件不会被错误打破，动态代码卸载仍必须在所有 callback
和 module-owned 实例结束后执行。

TDD 新增跨线程 release 回归，普通 loader **115/115** 通过。未完成边界仍包括真实
`dlclose`/`FreeLibrary`/Cocoa bundle unload` 的宿主验证，以及 module token 本身的外部线程
串行化；框架不能在宿主已经释放裸 module token 后自动恢复其生命周期。

## 本轮完成：动态 class lease 复制安全（2026-09-06）

class callback lease 现在绑定原始 lease 存储地址；复制后的结构不能在同一线程重复释放
snapshot/module 计数，`bind_instance()` 也拒绝复制品。只有获取线程中的原始 lease 可以
结束 callback guard，保证 module quiesce 等待不会被伪造释放打破。

TDD 新增复制 lease 释放回归，普通 loader **116/116** 通过。真实动态库卸载、宿主对裸
module token 的外部串行化和跨线程 UI 操作仍属于未完成边界。

## 本轮完成：字体链 shaping 能力选择与输入预算（2026-09-06）

字体 fallback chain 对显式 shaping 请求按“完整 cluster 覆盖 + face capability”选择，
避免首 face 覆盖字符却不支持 `liga`、script 或 language-system 时直接失败或静默丢失
feature。每次调用对各 face 的 capability 只查询一次；无显式请求继续使用无额外查询的
快速路径。链创建同时限制最多 256 个 source/path，并在分配前检查容量溢出。

TDD 新增显式 feature fallback 与超大 source 数量回归；普通、ASan/UBSan、Clang TSan
字体专项均为 69/69。完整 language-specific feature 选择、跨字体 variation corpus、
复杂 RTL GSUB 和跨段落增量 rebreaking 仍属于未完成能力。

## 本轮完成：UAX#14 类别与上下文规则（2026-09-03）

Unicode 17.0.0 断行生成器现在保留 `QU`、`HH`、`HL`、`SY`、`NU`、`PR`、`PO`、
`IS`、`BA`、`IN`、`CB`、`EB`、`EM`、`CJ` 和 `ZW` 类别。断行 helper 已覆盖空格前后、
引号双侧、希伯来 maqaf、`HL × HY/HH × HL` Hebrew 连字符、数字前后缀/分隔符、
acronym 与 solidus 的有界上下文、
`BA/IN/CJ` 前置禁止断点、`CB` 独立对象边界和 `EB × EM` emoji 组合；原有组合标记
starter、RI 配对、Hangul、ZWSP、开括号后连续空格和硬换行语义保持不变。普通 `test_myui_text_layout` 当前为 **86/86**，
生成器二次生成与提交数据 `cmp` 一致。

该阶段仍是 UAX#14 的可移植实用子集：完整 locale tailoring、SA dictionary、全部
golden corpus、复杂 East Asian tailoring 和与 shaping 的完整联动继续保留在未完成矩阵。

本轮补充修复流式断行状态对 Unicode breaking spaces 的识别：开括号后的 EM SPACE、
EN SPACE、THIN SPACE、MEDIUM MATHEMATICAL SPACE、IDEOGRAPHIC SPACE 等现在与 ASCII
空格一样不会让后续内容提前断开；NBSP、ZWSP 等非同类空白继续遵循各自 glue/break
语义。该判断是固定范围的 codepoint 检查，无分配、无锁；TDD 新增 Unicode 空格回归，
普通文本布局测试 **89/89** 通过。

- 完整 UAX#14 仍未实现：SA dictionary 基础 callback/wrap 接入已完成，但完整 locale
  dictionary tailoring、locale numeric tailoring、全部 UCD line-break 规则和 golden corpus
  仍待补齐。
- text area wrapped visual-line 的稳定 suffix 复用已完成并由 window-manager 回归覆盖：
  插入/删除硬换行、多字节 byte/physical 映射、预先 dirty 缓存禁用复用以及 OOM 事务回滚
  均已验证；剩余工作不再包括该缓存所有权边界。
- 完整 OpenType（language-specific features、RTL GSUB、跨字体 variation 覆盖和
  locale-specific presentation）仍未实现；VS15/VS16 的基础 cluster/零独立 glyph 契约已实现，
  复杂 RTL 跨段落增量 rebreaking 也未实现。
- 其他完整 CSS at-rule、设备能力扩展、X11/Win32/macOS/Wayland/Vulkan
  真正 retained-buffer partial present，以及 Windows/macOS/Wayland/X11/Vulkan runtime CI
  矩阵仍需后续阶段完成。
- class registry 的运行期 table snapshot 发布和 module instance quiesce token 已实现；
  宿主仍必须注销 module class、销毁实例并等待 `my_widget_class_module_try_unload()` 成功，
  registry 不自动执行平台动态库卸载。

## 本轮完成：UAX#14 数值与 Hangul 边界补齐（2026-09-03）

在不改变公开 ABI、无分配、无锁的前提下，断行状态机补齐已保留类别的高置信规则：
`HH` 与 `SY` 的前置禁止断点、LB24 字母与 `PR/PO` 数值前后缀粘连、`PR × ID/EB/EM`、
`ID/EB/EM × PO`、`HY × NU`，以及 Hangul 序列与数值前后缀的 LB27 组合。流式状态还保留
`B2 SP* B2` 和 `HL (HY|HH) × 非 HL` 的有限上下文。数字状态新增有界的“数字后缀已闭合”
状态，避免 `$10%x` 在 pair helper 的 LB24 规则下错误吞并后续普通文本。

TDD 先新增失败回归，再完成实现；普通 `test_myui_text_layout` 当前为 **94/94**。这批
规则仍属于可移植实用子集，不代表完整 UAX#14；LB25/LB28 的其余上下文交互、locale
tailoring、SA dictionary corpus 和版本化 golden corpus 仍保留在未完成矩阵。

## 本轮完成：loader 属性回调租约与重入保护（2026-09-03）

YAML loader 的动态 schema 属性 setter 现在在 loader 读租约内进入共享 callback guard，
与 factory、migration 使用同一线程局部深度计数。setter 回调递归修改 loader/class
registry 会快速返回 `MY_RET_NOT_SUPPORTED`，不会递归等待读写锁；guard 在 setter 返回
前后成对维护。新增 TDD 用例验证属性回调重入注册路径，`test_myui_loader` 为
**104/104**。该保护不改变属性解析热路径的分配和锁模型；真实动态库卸载、实例 quiesce
和跨平台 runtime smoke 仍需调用方与平台 CI 另行完成。
另有失败 setter 清理和子树阻塞期间 class replacement 的并发回归，确保错误路径与租约
收窄均不会留下永久锁定。

loader 使用 class descriptor 时，lease 只覆盖 create 与 typed property callback，随后
立即释放再构建公共属性和子树，避免运行期 class replacement 被无关的深层 YAML 节点拖住。
普通/Vulkan/ASan loader 均为 **104/104**，YAML-off 为 **2/2**。

## 本轮完成：事务句柄泄漏与 TMS 失败清理（2026-09-06）

修复规则引擎事务在重入回调和普通提交路径中的生命周期缺陷。事务提交/回滚后现在保留
可安全探测的 inactive tombstone，但通过新增 `re_facts_txn_destroy` 显式摘链并释放，
引擎自身的 firing transaction 在每次提交/回滚后自动释放。事实集延迟销毁会先断开退休
句柄与 facts 的关联，避免回调重入时 UAF；`re_tms_clone` 也会登记部分初始化条目，
确保分配失败时释放当前条目的 producer/premise 内存。普通事务、流式重入和 ASan/LeakSanitizer
定向测试均已通过。

## 本轮完成：动态 class callback lease（2026-09-03）

class registry 新增 `my_widget_class_acquire()`/`my_widget_class_release()`。lease 与具体
immutable snapshot 绑定并且 thread-affine；class factory、property 和 `is_instance` 调用
路径在 lease 内执行。runtime replace/unregister 发布新表后将旧 snapshot 标记为 retired，
等待在途 lease 归零再返回；lease 同时启用共享 callback guard，禁止回调递归修改 class/
loader registry，避免锁递归死锁。旧 descriptor 仍保留到进程退出，但外部调用 callback
必须先取得 lease；动态 widget 实例销毁和模块代码卸载顺序仍由调用方负责。

TDD 新增 replace/unregister 并发等待及 callback 重入回归，`test_myui_loader` 当前为
**101/101**。该机制只证明 registry callback 的在途安全，不代表真实动态库卸载、窗口线程
quiesce 或跨平台模块 ABI 已验证。

## 本轮完成：Vulkan 初始化失败清理与双队列交换链（2026-09-07）

Vulkan RHI 的初始化失败路径现在统一进入 `vk_init_cleanup()`，由可重入的
`vk_shutdown()` 按句柄存在性释放 instance、debug messenger、surface、device、交换链、
部分创建的 image view/framebuffer/semaphore、render pass、descriptor 资源、command
buffer/pool、uniform ring 和 shader compiler。交换链对象记录已创建数量，部分创建失败不会
按 stale `swap_count` 访问空数组或重复销毁。depth/render-pass/framebuffer 创建改为返回
状态，初始化和交换链重建在附件不完整时安全失败，不再继续提交无效资源。

当 graphics queue 与 present queue 不同时，device 创建同时请求两个 queue family，交换链
使用 `VK_SHARING_MODE_CONCURRENT` 并显式传递两个 family；同族时仍使用 exclusive，避免
无必要的跨队列同步开销。交换链重建会重新创建与新格式匹配的 render pass，再创建 depth
和 framebuffer。

TDD 新增初始化清理、双队列共享和重建顺序契约；源码测试 **20/20**，RHI 能力测试
**40/40**，Vulkan 核心目标构建通过。真实 X11/Wayland/Win32/macOS WSI、设备丢失后恢复和
分配器故障注入仍需平台 CI/专用 Vulkan mock 验证。

## 本轮补充：Vulkan WSI 查询与内存类型失败闭合（2026-09-07）

交换链 surface format 和 present mode 的两阶段查询现在检查每次 Vulkan 返回值，并拒绝
零数量结果；列表分配失败或第二阶段查询失败时不再继续使用未定义的格式、present mode
或数组。所有 Vulkan 内存分配点统一经过 `vk_allocate_memory()`，在调用驱动前拒绝
`UINT32_MAX` memory type，避免把 `vk_find_memory()` 的失败哨兵传给 Vulkan；原有资源回滚
逻辑保持不变。

TDD 新增 WSI 查询失败闭合和无效 memory type 防护契约；源码测试 **22/22**，RHI 能力测试
**40/40**，engine Vulkan 构建通过。真实故障注入仍需专用 Vulkan allocator/mock；平台 WSI
runtime CI 和 device-lost recovery 继续属于开放验证边界。

## 本轮补充：Vulkan 扩展与设备枚举能力协商（2026-09-07）

Vulkan instance/device 扩展现在先探测后启用：平台必需的 surface、WSI、swapchain 和
macOS portability subset 缺失时初始化立即失败并走统一清理；validation/debug utils 与
device fault 仍是可选能力，缺失时安全降级。物理设备两阶段枚举均检查 `VkResult`，查询
失败不再被误判为“无 GPU”或继续读取未定义列表。

该策略将失败成本限制在初始化冷路径，不增加帧提交热路径开销，也避免在不支持扩展的驱动
上触发 `vkCreateInstance`/`vkCreateDevice` 的隐式失败。TDD 源码契约现为 **23/23**，RHI
能力测试 **40/40**，engine Vulkan 构建通过；完整 headless CTest 在允许本地 socket 绑定的
环境中 **98/98** 通过。真实多厂商扩展矩阵和故障注入仍需平台 CI。

## 本轮补充：Vulkan 延迟上传的多设备 owner 隔离（2026-09-07）

全局延迟 mip 上传槽现在记录所属 `VKBackend`。同一设备的下一次上传、frame begin 和
shutdown 可以等待并回收该槽；其他 Vulkan 设备不会使用错误的 `VkDevice`、command pool
或 fence 回收 pending 句柄，也不会因为另一设备存在 pending 上传而阻塞自己的 frame begin。
异设备尝试覆盖全局槽会安全拒绝，避免跨设备句柄污染。owner 使用 backend 指针而不是
`RHIDevice` 指针，避免设备释放后回收路径再次解引用悬空宿主对象。

TDD 新增多设备 owner 隔离契约；源码测试 **24/24**、RHI 能力测试 **40/40**、engine
Vulkan 构建通过。真实多设备同时提交、设备销毁竞态和 allocator fault injection 仍需
专用 Vulkan mock 或多设备 runtime CI。

## 本轮补充：Vulkan 物理设备适配性选择（2026-09-07）

物理设备选择随后收紧为统一适配性门禁：候选 GPU 必须支持
`VK_KHR_swapchain`，成功返回 surface capability、format、present-mode 查询，并同时具备
graphics 与 present queue。`RE_VK_DEVICE_INDEX` 现在也必须通过同一门禁；非法或不适配的
显式索引会安全失败，不再回退到 `gpus[0]`。这些检查仅位于 Vulkan 初始化冷路径，帧提交
热路径不增加查询或分配；真实多厂商 GPU/WSI 组合仍需平台 CI 验证。
