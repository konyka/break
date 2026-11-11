# Compose + MVI 设计

日期：2026-11-11

## 目标与边界

在现有 myui 上提供 C11 与 C++20 的声明式 UI 和 MVI：同一份状态驱动节点树，输入只产生 Intent，reducer 纯计算新 State 与 Effect，异步结果经 UI loop 回到 State。 keyed reorder 必须保留 widget 身份、remember、文本选择、focus/grab；资源不足、非法输入和旧代际完成必须明确拒绝，不能静默截断。

不引入新的窗口、布局、输入、IME、主题、异步或包管理框架，不追求 Jetpack Compose 源码/二进制兼容。Vulkan 保持默认，OpenGL 只做最后降级和同机画面对照；record/null/headless 不授予 GPU、声卡或听测证据。

## 方案选择

采用三层：

1. `engine/src/myui/mycompose`：独立 C11 composition、双缓冲描述树、keyed diff、remember、MVI store 与 UI-affine scheduler。只依赖 C 标准库和仓库基础类型，不依赖 RHI 或 myui。
2. `engine/src/myui/mycompose_myui`：把 diff 应用到真实 myui 树，复用 `my_widget_class_create()`、`my_widget_set_prop()`、layout、dispatcher、focus/IME、close listener 和 `my_ui_command`。
3. `engine/src/myui/mycompose/my_compose.hpp`：完整 C++20 move-only RAII、fluent builder、typed remember 和 typed Store，不只是 create/destroy 薄封装。

另两个方案不采用：只做 C++ DSL 会使 C 无法使用同一 composition/MVI 语义并造成双实现；另建独立声明式窗口树会绕过现有 myui 输入、主题和生命周期。

## 模块和文件责任

- `my_compose.h/.c`：公共 C 类型、状态码、配置、诊断与 umbrella API。
- `my_compose_tree.h/.c`：描述树构建、key 校验、双缓冲、diff、remember 生命周期。
- `my_compose_store.h/.c`：Intent FIFO、原子 reducer、StateOps、Effect outbox、代际与 completion。
- `my_compose_runtime.h/.c`：UI 线程上的 drain→reduce→render→reconcile→dispatch 顺序；通过抽象 sink 解耦 myui。
- `my_compose_internal.h`：固定存储、slot/generation、队列和诊断内部结构，不进入公共 ABI。
- `mycompose_myui/my_compose_myui.h/.c`：myui sink、property/style/layout 映射、事务 journal、事件 listener 与命令 scope。
- `mycompose/my_compose.hpp`：header-only C++20 DSL；C ABI 仍由 `mycompose`/`mycompose_myui` targets 提供。

新 CMake targets 为 `mycompose`、`mycompose_myui` 和仅含头文件的 `mycompose_cpp20`。`mycompose` 不链接 myui/RHI；`mycompose_myui` 链接 `mycompose` 与 `myui_core`；C++20 只由使用该层的应用和测试启用。既有 `BreakUI` ABI 不变，应用在 `break_ui_pump()` 后显式调用 `my_compose_myui_pump()`。

## 固定容量与存储

以下值包含根节点，字符串容量包含终止 NUL；全局容量均按一个 Runtime 实例计算，不是每节点容量。构建和 diff 使用两份预分配描述存储，不在 steady-state 扩容。

```c
#define MY_COMPOSE_MAX_NODES 256u
#define MY_COMPOSE_MAX_CHILD_LINKS 255u
#define MY_COMPOSE_MAX_DEPTH 32u
#define MY_COMPOSE_MAX_PROPERTIES 512u
#define MY_COMPOSE_MAX_EVENTS 256u
#define MY_COMPOSE_MAX_DIFF_OPS 1024u
#define MY_COMPOSE_MAX_REMEMBER 64u
#define MY_COMPOSE_REMEMBER_BYTES 256u
#define MY_COMPOSE_STRING_BYTES 65536u
#define MY_COMPOSE_STATE_BYTES 16384u
#define MY_COMPOSE_INTENT_CAPACITY 64u
#define MY_COMPOSE_EFFECT_CAPACITY 32u
#define MY_COMPOSE_COMPLETION_CAPACITY 32u
#define MY_COMPOSE_MESSAGE_BYTES 256u
#define MY_COMPOSE_MAX_EFFECTS_PER_INTENT 8u
#define MY_COMPOSE_KEY_BYTES 64u
#define MY_COMPOSE_TYPE_BYTES 64u
#define MY_COMPOSE_NAME_BYTES 64u
```

每个节点最多 64 个属性和 32 个事件，与 myui schema 上限一致。每个节点最多 4 个 remember local slot；`remember` 内容最大 256 字节，对齐不超过 `max_align_t`。C State 默认是两个 16 KiB inline slot；复杂 State 必须在 StateOps 中显式 clone/dispose 预分配对象，C 存储只保存其句柄，不得 memcpy STL/拥有所有权对象。

MVI 提交前的任一容量耗尽返回 `MY_COMPOSE_OVERLOAD`，原 State、原 outbox/outstanding 和原 FIFO 不变；outbox 与 outstanding 共用 32 个 request slot，预检必须把本批 Effect 计入。view/tree/diff 的容量失败保留已经提交的新 State 和最后有效 UI，并设置 pending-view，不回退 State、不重复 reduce。diff op 超过 1024 也在触摸 myui 前失败。诊断记录具体容量。新层自身在预热后无逐帧 malloc；现有 myui children/string/listener 分配、超过 32 个直接子节点的 paint snapshot 分配，以及用户 State/字符串内部成本仍单独计量，不虚报整个帧路径零分配。

## C 数据模型和状态码

C ABI 只含 opaque handle、POD、固定视图和错误码，不含 STL、异常或 C++ ownership。

```c
typedef struct MyComposeRuntime MyComposeRuntime;
typedef struct MyComposeStore MyComposeStore;
typedef struct MyComposeTreeBuilder MyComposeTreeBuilder;

typedef struct MyComposeNodeHandle {
    uint32_t index;
    uint32_t generation;
} MyComposeNodeHandle;

typedef struct MyComposeString {
    const char *data;
    uint32_t size;
} MyComposeString;

typedef struct MyComposeIntent {
    uint32_t type;
    uint32_t payload_size;
    const uint8_t *payload;
    MyComposeNodeHandle owner;
    uint32_t result; /* MyComposeStatus：普通事件为 OK，completion 原样携带 */
} MyComposeIntent;

typedef enum MyComposeStatus {
    MY_COMPOSE_OK = 0,
    MY_COMPOSE_INVALID,
    MY_COMPOSE_STALE,
    MY_COMPOSE_OVERLOAD,
    MY_COMPOSE_DUPLICATE_KEY,
    MY_COMPOSE_TYPE_MISMATCH,
    MY_COMPOSE_NOT_SUPPORTED,
    MY_COMPOSE_CONFLICT,
    MY_COMPOSE_PENDING,
    MY_COMPOSE_CANCELLED,
    MY_COMPOSE_FAILED
} MyComposeStatus;
```

输入字符串/payload 只在调用时借用，写入前复制到固定存储。`MyComposeValue` 是 none/bool/int32/uint32/int64/float/double/string/color 的显式 tag union；不直接暴露 myui pointer value。handle 的 index 可复用，generation 不复用；零 handle 表示无 owner，根节点由 builder 创建时返回有效身份。

`MyComposeDiagnostics` 至少包含 accepted/rejected intent、reducer failure、effect overload、stale completion、reconcile/rollback、remember dispose 和各项容量 high-water。接受过的 Intent/Effect 不因后续 overload 被静默丢弃；拒绝必须同步返回给调用方。

## Composition 与 keyed diff

builder 每个帧从空 next 描述开始，按声明顺序生成节点。`NodeDesc` 包含 parent、key、type、property/event/style/layout 视图；`@row`、`@column`、`@stack` 是 adapter intrinsic kind，分别复用现有 linear/absolute layout，其它 type 走 myui class factory。kind/type 同时参与身份，避免同名 class 与 intrinsic 冲突。

匹配规则精确为：

- keyed 节点身份是 `(parent identity, key, type)`；key 在同一 parent 内必须唯一，与 type 无关。重复 key 在任何 factory/property 修改前返回 `DUPLICATE_KEY`。
- keyed 节点只在同一 parent 内复用。同 key 换 type 不复用，旧节点及其 remember/listener 被销毁后创建新代际。
- unkeyed 节点按同一 parent 的直接子节点绝对位置匹配；同位置 type 不同同样替换。插入节点导致的位置变化是明确的 unkeyed 状态迁移语义，需要稳定身份时必须提供 key。
- keyed reorder 生成 MOVE，不生成 DELETE+CREATE；同一 myui widget 指针、remember、selection、focus/grab 保留。跨 parent 移动不保留身份。

当前树与 next 树按上述规则生成 create/update/move/delete diff。每个消失节点都有逻辑 delete，tree finalize 是 remember dispose 与 node generation 失效的唯一所有者，按深度从深到浅、同级按声明逆序且各执行一次；myui 结构只 detach 每个被删除区域的最高节点，避免父节点先脱离后无法定位子节点。slot generation 到达 `UINT32_MAX` 后永久退休该 slot，不再分配或回绕。所有 remember/listener/completion 访问均核对 generation，adapter 不得重复 dispose 或推进代际。

`remember(local_slot)` 的身份是 `(node identity, local_slot)`。相同节点重排不销毁；节点删除或 type 替换销毁。相同 local slot 换 C++ 类型返回 `TYPE_MISMATCH`，不覆盖未析构对象。C++ 使用 placement construction 和注册的 dispose trampoline，支持非 trivially copyable 类型，但不保存跨代 C 指针作为永久身份。

## MVI 原子性与调度

UI listener 只复制固定大小 Intent 入队，不直接调用 reducer、修改 State 或重绘。listener 绑定强制把事件模板的 owner 写为发出事件的当前节点 handle，adapter 与 Runtime 必须使用同一个 Store；零 owner 仅用于明确的应用级 Intent。Store 在入队和 reducer 前都重新核对 owner，排队期间删除节点也会使 Intent 变为 STALE。每个内部 Intent/Effect/Completion 都有独立 inline 256-byte payload，复制后不再引用调用方内存。

`break_ui_pump()` 完成真实输入派发后，应用调用 `my_compose_myui_pump()`：

1. 若没有 pending-view，最多把 32 个有效 completion 转为 Intent，并处理总计最多 64 个 Intent（包括 completion-derived Intent）。store/owner/request 任一代际不符只计 STALE，不进入 reducer。
2. 按 FIFO 取出 Intent，先由 StateOps clone 当前 State 到 candidate。reducer 只执行 `current + intent -> candidate + effect batch`，不得 I/O、post Intent 或访问 myui。
3. EffectBatch 只能通过 checked append 添加，最多 8 项且每项最多 256 bytes；append 失败不修改 batch 并设置 sticky OVERLOAD。clone、reducer、batch 或容量失败，dispose candidate，当前 State/outbox/outstanding/FIFO 不变。
4. 预检 `outbox + outstanding + 本批 Effect <= 32`，再原子发布 candidate，写入 `{store generation, owner generation, request id}` 并加入 outbox。outbox 与 outstanding 共用这 32 个 slot，executor OK 只做无失败的 outbox→outstanding 移动。
5. 构建当前 State 的 next view，执行 sink stage、tree finalize、sink commit。成功后清除 pending-view，再从 UI 线程 dispatch outbox。`PENDING` 保留队首，其它 executor 失败记录拒绝且不得注册 request。
6. view/stage 失败保留已提交 State 和最后有效 UI，设置 pending-view，不 dispatch 本批 Effect。后续 pump 先以同一 State revision 重试 view；恢复前不 reduce 新 Intent、不转换 completion、不 dispatch Effect，成功后才继续 FIFO。

MVI 提交与 view reconcile 是独立边界：view 失败不撤销已提交 State，也不重复执行 reducer；pending-view 保证不会在下一次重试前推进 State。Reducer 不能递归产生 Intent，因此没有无界重入。65 个 Intent、33 个 completion、两个排队 Intent 与首次 view 失败都必须有顺序/预算测试，executor 和 reducer 不得重复执行。

每个 Runtime 只有一个 UI owner 线程，普通 Dispatch 也只能从该线程调用；worker 不直接访问 Store。restart 推进 store generation、清 pending/outbox/outstanding 但保留 State/UI，由调用方提交新 Intent。节点删除只推进该 owner generation；window close 同时推进 store/owner 代际并关闭 Runtime scope。node/store generation 到达 `UINT32_MAX` 时退休 slot 或返回 `OVERLOAD`，request id 到达 `UINT64_MAX` 返回 `OVERLOAD`，均不回绕复用。

## 异步生命周期

Effect executor 可以用任意 worker，但 worker 只创建 completion，并通过 Runtime 自有 `my_ui_command_scope` 和 Store 的安全 emitter lease 提交到原 PAL loop。completion 队列容量为 32；接受 completion 时才消费 outstanding slot 并转为 Intent，队列满则不消费，UI callback 仅把共享交付状态写为 `OVERLOAD`，worker 保留 completion 并在有界重试中重投。

每个 completion context 使用原子交付状态和 refcount，worker 与 UI command 各持一个引用。状态至少包括 PENDING、ACCEPTED、RETRY、CANCELLED。重投只持有 completion 与安全 lease，不持裸 Store/Runtime 指针；UI callback 通过 lease 取得 Store，lease 失效后不访问 Store。post 失败、STALE、CANCELLED 都是非成功终态并释放双方引用，不能伪造成 accepted。`my_ui_command` 忽略 execute 返回值，因此共享状态才是 worker 的交付凭据。

window close 先使 Store lease 失效、推进代际，再关闭 Runtime scope，阻止新的提交并取消未执行 command。Runtime 非拥有 Store/sink，调用方必须先销毁 Runtime，再在 UI 线程销毁 Store/sink，不存在 double destroy。Store destroy 在 UI 线程先失效 lease、关闭 scope，再释放 Store；正在执行的 callback 与该 UI 线程销毁不能并发，worker 后续重投只能看到失效 lease 并安全释放。必须确定性测试“满队列 callback 已执行、worker 暂停在重投前、close/destroy 后恢复 worker”，以及 post 失败和 scope cancel。

## myui 事务适配与回滚

adapter 绑定期间独占其子树结构，调用方不得绕过 adapter add/remove/reorder。每次 stage 先比对当前快照，外部结构改变返回 `CONFLICT`。adapter 只提供 stage/commit/rollback，不再另有一条 remember/handle finalize 路径。

为满足同父 reorder 与事务回滚，在 `my_widget.[ch]` 增加 `my_widget_reorder_child`、`my_widget_insert_child`、`my_widget_detach_child`、`my_widget_notify_child_removed`。reorder 只移动顺序，不触发 focus/grab 丢失；detach 只改变结构并把 tree 引用交给事务，不调用 removed hook，不清理 focus/grab/IME。notify 才执行现有 removed hook；既有 `remove_child` 严格按 notify→detach→unref 保持行为。

事务顺序：

1. 预检 duplicate/capacity/type/property/schema/当前快照，任何失败都不调用 factory。保存首次绑定/factory 默认属性、旧顺序和事务代际。
2. 为每个更新准备不可失败的恢复记录：POD 属性保存值；可能分配的属性必须在 `my_prop_desc_t` 提供 capture/discard/no-fail restore。字符串恢复通过已拥有 buffer/state swap 完成，不得再次分配。文本 capture 同时保存 selection/IME；缺少事务回调的字符串属性在 preflight 返回 `NOT_SUPPORTED`。
3. stage 创建 detached widget、设置属性/listener、更新旧节点、插入新节点和 MOVE 保留节点；最后按逆序 detach 删除区域最高节点，事务持有其引用。此时尚未执行 removed hook，selection/focus/grab/IME 与 remember 未销毁。
4. 任一 stage 失败，严格逆序恢复结构、属性、selection/IME 和 layout，销毁新节点并返回原错误。rollback 不执行 removed hook，不分配、不 dispose 当前 remember，不向 MVI 注入伪造事件；第二次 detach、恢复点和 rollback 分配失败都必须注入验证。
5. stage 全成功后，Runtime 先调用唯一的 tree finalize，逆序 dispose remember 并推进 node generation，且恰好各一次；随后 adapter commit 只负责吊销旧 listener lease、注册新 owner、notify removed、unref 删除子树和发布快照。两步都不分配或失败，内部不变量破坏进入 `FAILED`，不能返回部分成功。

完整声明中的省略表示恢复首次绑定/factory 默认：property/layout 恢复默认值（row/column 保留 intrinsic layouter，普通节点默认 absolute+AUTO），style 删除 local override，event 只吊销对应 listener lease，不推进保留节点的 owner generation。显式 `MyComposeValue.none` 对 property/layout 同样恢复默认，style 表示 unset；无法恢复默认的属性在 preflight 拒绝。必须覆盖 property/event/style/layout 的 set→omit、显式 none、更新与回滚，省略后的旧 event 不得再投递。

事务中的 programmatic listener 事件被抑制。删除成功才由 notify 清理 focus/grab/IME；rollback 不需要也不允许重放这些 teardown。所有 capture、restore、listener 和 dispose 次数都通过真实测试核对，不能只比较节点指针。

## C++20 DSL

命名沿用 `breakxx::quic`：`breakxx::compose` namespace、PascalCase 类型/方法、`kMax...` 常量、尾部 `_` 成员、move-only RAII、`[[nodiscard]]`、`std::optional`、`std::span`。不机械增加 break/cry 前缀。

`Runtime` 拥有 C runtime，删除 copy，move 后源对象无效，析构幂等；`Create()` 返回 `std::optional<Runtime>`。`Builder::Node()` 返回 move-only `NodeScope`，支持嵌套 `Row/Column/Stack/Element`、`Key`、`Property`、`Style`、`OnClick/OnEvent(Intent)`。NodeScope 析构只结束已打开的 scope，错误写入 Builder sticky status，不抛异常跨 C ABI。

`Remember<T>(local_slot, factory)` 返回 `T*` 并在失败时返回 nullptr、写入 Builder sticky status；placement 构造、move-only、正确析构，尺寸/对齐超限时编译期拒绝。`Store<State>` 的两个 slot 都是 `std::optional<State>`，只在对象存活时 engaged：Clone 前 candidate 必须 reset 为 disengaged，成功 Clone 后才 engaged，失败/复用时 reset，禁止在活对象上重复 placement new。默认 Clone 使用 copy construction；不可默认构造、不可拷贝赋值、move-only State 必须提供自定义 `StateOps<State>::Clone`，并验证构造/clone/reducer 异常时的析构次数。EffectBatch 使用固定 `std::array`，不是逐 Intent `std::vector`。

所有 C++ callback 经 trampoline 捕获异常并转为 `MY_COMPOSE_FAILED`（无异常构建要求 callback `noexcept`）。C ABI 不出现 template/STL/异常，C++ 对象地址不成为跨代身份。提供同一 fixture 的 C/C++ diff/state/effect parity、自包含头编译和真实跨语言链接。

## 验证与证据等级

按 TDD 顺序：

1. 纯 C：no-op、insert/delete、duplicate key、type change、keyed/unkeyed 匹配、reorder、全部容量、Intent FIFO、reducer 原子性、remember 逆序 dispose。
2. myui adapter：widget 指针身份、文本 selection、focus/grab、删除清理、旧 listener generation、factory/property/detach 失败后的完整回滚。
3. C++20：C/C++ 同 fixture parity、RAII move、自包含头、extern "C"、跨语言链接和异常边界。
4. 异步：restart/delete/window close 后旧 completion、outbox/completion overload 与 drain recovery、worker/UI destroy 竞态、request 永不误投递。
5. 图形：在真实 Wayland 生产路径执行 `platform_poll`→`break_ui_pump`→Compose pump→render→readback→present，实际点击、键入、语言切换和 keyed reorder；Vulkan 默认，OpenGL 对照。断言关键区域像素和状态，不用 record/headless 冒充 GPU。
6. 普通全量、ASan+UBSan、TSan、显式 fuzz 和 allocation counter。新图形测试显式加入 CI 的执行 regex，不能只注册 label 就声称已执行。Weston/lavapipe 证明真实 API/窗口/像素，不冒充硬件 GPU。

每项功能先得到目标 RED 再实现 GREEN，至少对关键生产条件做变异并恢复。新增公共文档说明 API、帧顺序、容量、I18N/IME 接入和证据限制；历史文档不改写。独立规格/质量评审的 Critical/Important 清零后，才允许合入主分支。

## 非目标

本期不替换现有 editor、不迁移全部手写 myui 页面、不引入第二套响应式状态框架或协程运行时，不实现 Jetpack 兼容层，不承诺跨硬件像素逐字节一致，不把客户端状态当作安全权威。Compose 声明只影响 UI，不直接修改 ECS、渲染资源或网络状态；这些交互继续通过明确的 Intent/Effect 与现有命令边界完成。
