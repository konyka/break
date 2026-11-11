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

任一容量耗尽返回 `MY_COMPOSE_OVERLOAD`，原 State、原描述树和原 myui 树不变，诊断记录具体容量。diff op 超过 1024 也在触摸 myui 前失败。新层自身在预热后无逐帧 malloc；现有 myui children/string/listener 分配、超过 32 个直接子节点的 paint snapshot 分配，以及用户 State/字符串内部成本仍单独计量，不虚报整个帧路径零分配。

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
} MyComposeIntent;

typedef enum MyComposeStatus {
    MY_COMPOSE_OK = 0,
    MY_COMPOSE_INVALID,
    MY_COMPOSE_STALE,
    MY_COMPOSE_OVERLOAD,
    MY_COMPOSE_DUPLICATE_KEY,
    MY_COMPOSE_TYPE_MISMATCH,
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

当前树与 next 树按上述规则生成 create/update/move/delete diff。每个消失节点都有逻辑 delete，remember 在成功 commit 时按深度从深到浅、同级按声明逆序 dispose；myui 结构只 detach 每个被删除区域的最高节点，避免父节点先脱离后无法定位子节点。旧 generation 在 commit 后失效，所有 remember/listener/completion 访问均核对 generation。

`remember(local_slot)` 的身份是 `(node identity, local_slot)`。相同节点重排不销毁；节点删除或 type 替换销毁。相同 local slot 换 C++ 类型返回 `TYPE_MISMATCH`，不覆盖未析构对象。C++ 使用 placement construction 和注册的 dispose trampoline，支持非 trivially copyable 类型，但不保存跨代 C 指针作为永久身份。

## MVI 原子性与调度

UI 事件 listener 只把固定大小 Intent 入队，不直接调用 reducer、修改 State 或重绘。`break_ui_pump()` 完成真实输入派发后，应用调用 `my_compose_myui_pump()`，顺序为：

1. 把有效 completion 转为 Intent；store/owner/request 任一代际不符只计 `STALE`，不进入 reducer。
2. 按 FIFO 取出 Intent，先由 StateOps clone 当前 State 到 candidate。reducer 只执行 `current + intent -> candidate + effect batch`，不得 I/O、post Intent 或访问 myui。
3. 预检 candidate State 和 effect 剩余容量。clone、reducer 或容量检查失败，dispose candidate，当前 State 与 outbox 不变；不得部分提交 State 或部分 Effect。
4. 原子发布 candidate，为 Effect 写入 `{store generation, owner generation, request id}` 并加入 outbox。随后构建当前 State 的 next view、计算并应用 diff。
5. executor 只从 UI 线程取得 Effect 并启动工作。`PENDING` 表示暂时不能接受，Effect 留在 outbox，下一 pump 有界重试；其它失败保留诊断，不能把未接受写成完成。

MVI 提交与 view reconcile 是两个明确边界：view 失败不撤销已提交的 MVI State/Effect，也不重复执行 reducer；保留最后有效 myui 树，在下一 pump 重试同一 State 的 view。effect 是否被 executor 接受独立记录，不依赖像素结果。一次 pump 最多处理 64 个 Intent 和 32 个 completion，Reducer 不能递归产生 Intent，因此没有无界重入。

每个 Runtime 只有一个 UI owner 线程。普通 `Dispatch` 也只能从该线程调用；worker 不直接访问 Store。restart 推进 store generation、取消 outbox/outstanding request 但保留当前 State/UI，由调用方提交新 Intent 启动替代工作；节点删除只推进该 owner generation；window close 同时推进 store/owner 代际并关闭 Runtime 自有 command scope。request id 单调递增，溢出返回 `OVERLOAD`，绝不回绕复用。

## 异步生命周期

Effect executor 可以用任意 worker，但 worker 只创建 completion，并通过 Runtime 自有 `my_ui_command_scope` 提交到原 PAL loop。completion 容量为 32；满时 UI callback 只在 completion 的共享结果中写入 `OVERLOAD`，worker/executor 保留所有权并在后续有界尝试中重投，接受后才释放结果。`my_ui_command` 会忽略 execute 返回值，因此不得把 callback 返回值误当作 worker 已收到结果；共享结果只表达交付状态，不直接读写 MVI State。任何满队列路径都不能丢弃或伪造成功。`my_ui_command` 只负责 loop 交付，不直接调用 reducer。

window close listener 先关闭 Runtime scope、推进代际，再允许 widget teardown。Runtime destroy 先停止新 Effect，再关闭 scope、使 listener lease 失效、取消/释放 pending command，最后销毁 Store/remember/tree。worker 与 UI destroy 竞态必须由所有权和代际测试验证；不能 detach 一个仍引用 Runtime 的 callback。

## myui 事务适配与回滚

adapter 绑定期间独占其子树结构，调用方不得绕过 adapter add/remove/reorder。每次 apply 先比对当前快照，外部结构改变返回 `CONFLICT`。

为满足同父 reorder 与失败恢复，在 `my_widget.[ch]` 增加三个小原语：`my_widget_reorder_child`、`my_widget_insert_child`、`my_widget_detach_child`。reorder 不 remove+add，不触发 focus/grab 丢失；detach 将 tree 引用转移给事务而不销毁 widget；既有 `remove_child` 可用 detach+unref 保持原行为。

事务顺序：

1. 预检 duplicate/capacity/type/property/schema/当前快照，任何失败都不调用 factory。
2. 保存 focus/grab/hover、旧属性、旧顺序和事务代际；stage 创建 detached widget 并设置初始属性/listener。
3. stage 旧节点属性更新、插入新节点和保留节点 MOVE；最后按逆序 detach 删除子树，事务持有其引用，remember 尚未 dispose。
4. 任一 stage 失败，严格逆序恢复属性、顺序和 detach，销毁新节点，恢复 focus/grab/hover，返回原错误。事务期间 programmatic listener 事件被抑制，旧 remember 和 State 未受影响。
5. 全部 stage 成功后 commit：使旧 listener/handle generation 失效，逆序 dispose remember，unref 被删除子树，发布新快照。commit 只做已验证且不会分配失败的释放/发布；内部不变量破坏进入 `FAILED`，不能返回部分成功。

删除成功时现有 removed hook 清理 focus/grab/IME；rollback 使用保存的 dispatcher 状态恢复，且不向 MVI 注入伪造用户事件。property get 用于保存旧值；未知或不可恢复属性在 preflight 拒绝。创建、更新、移动、分离、回滚均需要故障注入测试，不能只测 happy path。

## C++20 DSL

命名沿用 `breakxx::quic`：`breakxx::compose` namespace、PascalCase 类型/方法、`kMax...` 常量、尾部 `_` 成员、move-only RAII、`[[nodiscard]]`、`std::optional`、`std::span`。不机械增加 break/cry 前缀。

`Runtime` 拥有 C runtime，删除 copy，move 后源对象无效，析构幂等；`Create()` 返回 `std::optional<Runtime>`。`Builder::Node()` 返回 move-only `NodeScope`，支持嵌套 `Row/Column/Stack/Element`、`Key`、`Property`、`Style`、`OnClick/OnEvent(Intent)`。NodeScope 析构只结束已打开的 scope，错误写入 Builder sticky status，不抛异常跨 C ABI。

`Remember<T>(local_slot, factory)` 返回指向 slot 的引用，placement 构造、move-only、正确析构；尺寸/对齐超限时编译期拒绝。`Store<State>` 持有预分配 current/candidate model；默认要求可 clone 的 State，非拷贝 State 必须提供 `StateOps<State>::Clone/Destroy`。EffectBatch 使用固定 `std::array`，不是逐 Intent `std::vector`。

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
