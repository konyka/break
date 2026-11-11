# Compose + MVI Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** 在现有 myui 上交付 C11/C++20 声明式 Compose 与完整 MVI，保留 keyed 身份并验证真实 Vulkan/OpenGL 输入和像素。

**Architecture:** C11 核心负责双缓冲描述树、diff、remember、store 与 UI-affine 调度；独立 myui adapter 负责事务应用和 PAL command；C++20 提供类型安全 RAII DSL。设计合同固定于 `docs/superpowers/specs/2026-11-11-compose-mvi-design.md`，本计划不扩大其范围。

**Tech Stack:** C11、C++20、现有 myui/PAL/`my_ui_command`、CMake/CTest、Wayland、Vulkan、OpenGL、ASan+UBSan、TSan。

## Global Constraints

- 工作树为 `/home/timeshift/opensource/break/.worktrees/compose-mvi`，分支 `compose-mvi`；每任务 scoped commit、独立规格/质量评审，不建 PR，所有构建/并行 CTest 使用 `-j3`。
- 新代码不得使用外部引擎前缀或旧应用领域名；C 使用 `MyCompose*`/snake_case，C++ 使用 `breakxx::compose`、PascalCase、`kMax...`、尾部 `_`、move-only RAII、`[[nodiscard]]`。
- 固定上限：nodes 256、child links 255、depth 32、properties 512、events 256、diff ops 1024、remember 64×256 bytes、string arena 64 KiB、State 16 KiB、Intent 64、Effect/Completion 32、message 256 bytes、每 Intent 最多 8 Effects、key/type/name 64 bytes。超限为 `MY_COMPOSE_OVERLOAD`，不得静默截断。
- 每节点最多 64 properties、32 events、4 remember slots；remember 不超过 256 bytes 且对齐不超过 `max_align_t`。
- keyed 身份为 `(parent,key,type)`，unkeyed 按直接子节点绝对位置；同 key 换 type 必须替换；MOVE 不得变成 DELETE+CREATE。
- C ABI 不含 STL/异常/C++ ownership。复杂 State 必须显式 clone/dispose 预分配对象，不能 memcpy STL 或拥有所有权对象。
- reducer 不执行 I/O；事件只 enqueue Intent；worker 不直接访问 Store/myui。store、owner、request 三代身份任一失效都丢弃 completion 并计数。
- Intent 提交与 UI reconcile 是独立原子边界：reducer 失败不提交 State/Effect；UI stage 失败完整回滚 myui，但已提交 State 不重复 reduce。
- 新层预热后不逐帧 malloc；既有 myui children/string/listener 和超过 32 个直接子节点的 paint snapshot 分配必须如实记录。
- Vulkan 默认，OpenGL 只作最后降级与同机对照；Linux 仅 Wayland。record/null/headless 不冒充 GPU、声卡或听测；CI 图形测试必须进入实际执行 regex 且零 skip 才授予图形证据。
- 每项新行为先观察目标 RED，再实现 GREEN；每任务至少一个生产变异被测试杀死并恢复。独立评审 Critical/Important 清零才进入下一任务。
- 文档只补充当前事实，不改写历史。测试生成物只写构建树或 `test_tmp`，正式字体/资产不由测试重写。

---

### Task 1: C11 描述树与 keyed diff

**Files:**
- Create: `engine/src/myui/mycompose/my_compose.h/.c`、`my_compose_tree.h/.c`、`my_compose_internal.h`
- Create: `engine/tests/test_mycompose_tree.c`
- Modify: `engine/CMakeLists.txt`

**Interfaces:**
- Produces: `MyComposeStatus`、`MyComposeNodeHandle`、`MyComposeString`、`MyComposeValue`、`MyComposeNodeDesc`、`MyComposeDiff`、`MyComposeTreeBuilder`。
- API: `my_compose_tree_builder_create/destroy/begin/end/commit`、`my_compose_tree_builder_node/property`、`my_compose_tree_builder_diff`。

- [ ] **Step 1: 先注册测试并写 keyed 行为 RED**

建立 `@root`→`@column`，声明 keyed button A/B、同位置 type 替换、A/B reorder、unkeyed 插入和重复 key。首次 commit 后重新 build，断言 no-op 为 0；交换 A/B 后两个 handle 不变且 diff 为 MOVE；A 改为 edit 后旧 handle 失效并出现 DELETE+CREATE；同 parent 重复 key 返回 `DUPLICATE_KEY`。

```c
ASSERT_EQ(my_compose_tree_builder_begin(builder), MY_COMPOSE_OK);
ASSERT_EQ(add_node(builder, root, "a", "button", &a), MY_COMPOSE_OK);
ASSERT_EQ(add_node(builder, root, "a", "edit", &duplicate), MY_COMPOSE_DUPLICATE_KEY);
ASSERT_EQ(my_compose_tree_builder_diff(builder)->count, 0u);
```

同时写 nodes/depth/properties/events/string arena/diff ops 边界测试，第 257 个节点、33 层、第 513 个 property、第 257 个 event 和过长字符串必须为 `OVERLOAD`。

- [ ] **Step 2: 运行 RED，再只补声明/stub 证明行为失败**

配置/构建应先因缺少 `mycompose` API RED；添加公共声明和返回 `MY_COMPOSE_FAILED` 的最小 stub 后，测试必须因期待 OK/diff 而失败，不能只留编译失败证据。

```bash
cmake -S engine -B build-compose-normal -DCMAKE_BUILD_TYPE=Debug \
  -DENGINE_BUILD_TESTS=ON -DENGINE_RHI_BACKEND=auto -DBREAK_ENABLE_SNOWFLAKE=OFF
cmake --build build-compose-normal --target test_mycompose_tree -j3
./build-compose-normal/test_mycompose_tree
```

- [ ] **Step 3: 实现双缓冲、校验和 diff**

根节点由首个 parent=零 handle 的 `@root` 声明产生，parent 必须先声明。NodeDesc 的字符串只在调用时借用，写入固定 arena。child link 保存 parent→first child/next sibling，不能依靠递归无界遍历。

```c
typedef struct MyComposeNodeHandle { uint32_t index, generation; } MyComposeNodeHandle;
typedef struct MyComposeIntent {
    uint32_t type;
    uint32_t payload_size;
    const uint8_t *payload;
    MyComposeNodeHandle owner;
    MyComposeStatus result;
} MyComposeIntent;
MyComposeStatus my_compose_tree_builder_begin(MyComposeTreeBuilder *builder);
MyComposeStatus my_compose_tree_builder_node(MyComposeTreeBuilder *builder,
    const MyComposeNodeDesc *desc, MyComposeNodeHandle *out_handle);
MyComposeStatus my_compose_tree_builder_property(MyComposeTreeBuilder *builder,
    MyComposeNodeHandle node, const char *name, const MyComposeValue *value);
MyComposeStatus my_compose_tree_builder_event(MyComposeTreeBuilder *builder,
    MyComposeNodeHandle node, const char *name, const MyComposeIntent *intent);
MyComposeStatus my_compose_tree_builder_end(MyComposeTreeBuilder *builder);
MyComposeStatus my_compose_tree_builder_commit(MyComposeTreeBuilder *builder);
```

先扫描同 parent keys，再匹配旧/new。keyed 只匹配 `(parent,key,type)`；unkeyed 用绝对位置；MOVE 只改变 sibling link。commit 交换 current/next，index 复用时 generation 严格递增。任何 end 错误销毁 next 临时内容，current 不变。

- [ ] **Step 4: focused、全量和变异**

运行 `test_mycompose_tree`、全量非图形；临时把 keyed 匹配条件去掉 type，确认“同 key 换 type 不保留”RED，恢复后 GREEN。临时放宽 duplicate preflight，确认 next node count 与当前树保持不变的断言 RED。

```bash
ctest --test-dir build-compose-normal --output-on-failure -j3 \
  -R '^(test_mycompose_tree|test_myui_)'
ctest --test-dir build-compose-normal -LE 'graphics|fuzz' --output-on-failure -j3
```

- [ ] **Step 5: 独立评审并提交**

评审纯 C 依赖边界、身份算法、容量与失败原子性。通过后提交 `feat: add declarative tree diff`。

### Task 2: remember 与节点代际

**Files:**
- Create: `engine/src/myui/mycompose/my_compose_remember.h/.c`
- Modify: `my_compose_tree.[ch]`、`my_compose_internal.h`
- Create: `engine/tests/test_mycompose_remember.c`

**Interfaces:**
- Consumes: Task 1 builder、handle、current/next commit。
- Produces: `MyComposeRememberOps`、`my_compose_tree_builder_remember()`、`my_compose_tree_builder_remember_get()`。

- [ ] **Step 1: 写生命周期 RED**

注册带 init/dispose 计数和递增销毁序号的 slot。相同 keyed reorder 后指针与值不变；type 替换、节点删除分别逆序 dispose；aborted next build 只 dispose 新建 slot；旧 generation `remember_get` 返回 `STALE`；同 local slot 换 `type_tag` 返回 `TYPE_MISMATCH`。

```c
MyComposeStatus my_compose_tree_builder_remember(
    MyComposeTreeBuilder *builder, MyComposeNodeHandle node,
    uint32_t local_slot, uint64_t type_tag, uint32_t size, uint32_t alignment,
    const MyComposeRememberOps *ops, void **out_storage);
ASSERT_EQ(my_compose_tree_builder_remember_get(builder, old, 0u, &storage),
          MY_COMPOSE_STALE);
```

覆盖 local_slot≥4、第 65 个 slot、size>256、alignment>`max_align_t`、dispose 逆序和重复 get。

- [ ] **Step 2: 先观察 RED，再实现固定 slot**

运行测试，先得到 API/行为 RED。slot 使用内部对齐存储，初始化仅在身份首次出现时；匹配节点直接复用。commit 按深度降序、同级声明逆序 dispose 消失节点，随后使 generation 失效。next build 失败不得销毁 current slot。

- [ ] **Step 3: GREEN、ASan 与变异**

运行普通 focused 和 ASan+UBSan focused；临时把 type 替换路径改为保留 slot，确认 old pointer/dispose 断言 RED，恢复 GREEN。

```bash
cmake -S engine -B build-compose-asan -DCMAKE_BUILD_TYPE=Debug \
  -DENGINE_BUILD_TESTS=ON -DENGINE_RHI_BACKEND=auto \
  -DENGINE_USE_ASAN=ON -DENGINE_USE_UBSAN=ON
cmake --build build-compose-asan --target test_mycompose_remember -j3
ASAN_OPTIONS=detect_leaks=1 UBSAN_OPTIONS=halt_on_error=1 \
  ./build-compose-asan/test_mycompose_remember
```

- [ ] **Step 4: 独立评审并提交**

通过后提交 `feat: preserve composition memory by identity`。

### Task 3: MVI Store、原子 reducer 与三代身份

**Files:**
- Create: `engine/src/myui/mycompose/my_compose_store.h/.c`
- Create: `engine/tests/test_mycompose_store.c`
- Modify: `my_compose.h`、CMake targets

**Interfaces:**
- Consumes: Task 1 的 `MyComposeIntent`，事件 payload 在入队时复制，completion 的 `result` 原样传给 reducer。
- Produces: `MyComposeEffect/Batch`、`MyComposeCompletion`、`MyComposeStateOps`、`MyComposeReducer`、`MyComposeExecutor`、`MyComposeStore`。
- API: create/destroy、dispatch/complete、register/invalidate owner、reduce/dispatch_effects、restart/close、state/diagnostics。

- [ ] **Step 1: 写 FIFO、原子性和旧完成 RED**

State 为 `uint32_t count`，Intent A 增加 1、B 增加 10。两个 Intent 必须顺序得到 1、11。clone 失败、reducer 失败、第 9 个 effect、outbox 满均保持 State/outbox 不变。executor 首次 `PENDING` 时 effect 不丢，下一 drain 才注册 request。

```c
typedef struct MyComposeStateOps {
    void *context;
    MyComposeStatus (*clone)(void *, const void *, uint32_t, void *, uint32_t, uint32_t *);
    void (*dispose)(void *, void *, uint32_t);
} MyComposeStateOps;
typedef MyComposeStatus (*MyComposeReducer)(void *context,
    const MyComposeIntent *intent, const void *state, uint32_t state_size,
    void *candidate, uint32_t *candidate_size, MyComposeEffectBatch *effects);
typedef MyComposeStatus (*MyComposeExecutor)(void *context,
                                             const MyComposeEffect *effect);
MyComposeStatus my_compose_store_dispatch(MyComposeStore *, const MyComposeIntent *);
MyComposeStatus my_compose_store_reduce(MyComposeStore *);
MyComposeStatus my_compose_store_dispatch_effects(MyComposeStore *);
MyComposeStatus my_compose_store_complete(MyComposeStore *, const MyComposeCompletion *);
const MyComposeDiagnostics *my_compose_store_diagnostics(const MyComposeStore *);
```

注册 `{index=1,generation=1}` owner，dispatch effect 得到 request=1；restart、owner invalidate、close 后对应 completion 必须为 `STALE` 且不调用 reducer。request id 不回绕；零 owner 仍核对 store/request。completion 满队列必须显式 overload，drain 后恢复。

- [ ] **Step 2: 先 RED，再实现 Store**

State slot 为 2×16 KiB；clone 后才允许 reducer 修改 candidate。EffectBatch 固定 8 项，core 在提交时覆盖 store/owner/request 元数据。`reduce` 只提交完整 Intent；`dispatch_effects` 在 view 后调用，OK 注册 outstanding，PENDING 保留队首，FAILED 记录拒绝且不注册完成。

owner 表按 node index 保存当前 generation；`register_owner` 替换旧代际，`invalidate_owner` 使旧代际失效。`restart` 清 pending/outbox/outstanding 并推进 store generation，保留 State；`close` 拒绝新输入。store/state/diagnostics 只在 UI owner 线程访问。

- [ ] **Step 3: focused、并发误用和变异**

验证 FIFO、effect overload/drain recovery、completion overload、restart/delete/close、错误 StateOps dispose 次数。非 owner 线程 dispatch 必须 `CONFLICT`；TSan 下 worker 只能通过测试 command bridge 注入 completion。临时漏掉 owner generation 检查，旧 completion RED，恢复 GREEN。

- [ ] **Step 4: 独立评审并提交**

通过后提交 `feat: add transactional MVI store`。

### Task 4: myui 身份、detach 与样式删除原语

**Files:**
- Modify: `engine/src/myui/myui/my_widget.[ch]`、`my_style.[ch]`、`my_theme.c`
- Create: `engine/tests/test_mycompose_widget_primitives.c`
- Modify: `engine/CMakeLists.txt`

**Interfaces:**
- Produces: `my_widget_reorder_child`、`my_widget_insert_child`、`my_widget_detach_child`、`my_style_unset`、`my_widget_style_unset`。

- [ ] **Step 1: 写指针/focus/selection 保留 RED**

在真实 dummy window 中建立 A/B edit，保存文本 selection、focus/grab 和指针。reorder B→A 前，A/B 指针、文本选择、focus/grab 不变，children 顺序正确。detach 后 child parent 为 NULL、dispatcher 清除目标且调用方持有唯一 tree ref；reinsert 恢复同一指针。remove_child 原行为不变。

```c
my_ret_t my_widget_reorder_child(my_widget_t *parent, my_widget_t *child, size_t index);
my_ret_t my_widget_insert_child(my_widget_t *parent, my_widget_t *child, size_t index);
my_ret_t my_widget_detach_child(my_widget_t *parent, my_widget_t *child,
                                my_widget_t **out_child);
my_ret_t my_widget_style_unset(my_widget_t *widget, my_widget_state_t state,
                               const char *key);
```

style unset 删除 local override 后回退 theme，缺失 key 返回 `MY_RET_NOT_FOUND`；越界 index、非 child、循环 attach 必须拒绝。

- [ ] **Step 2: 先 RED，再实现原语**

reorder 只移动 darray 元素，不改 parent/ref/focus。insert 只接受 detached child 且 index≤count。detach 复用现有 removed hook/layout/invalidation，但把引用交给 out 参数；remove 改为 detach+unref。`my_style_unset` reset value 并压缩同 state 数组，widget wrapper 使旧/新区域失效。

- [ ] **Step 3: GREEN 和变异**

运行 focused 与既有 widget/dispatcher/edit/focus 测试；临时把 reorder 实现成 remove+add，focus/selection RED，恢复 GREEN。ASan+UBSan 检查 detach 引用无泄漏/UAF。

- [ ] **Step 4: 独立评审并提交**

通过后提交 `feat: add identity-preserving widget operations`。

### Task 5: myui diff 事务与事件绑定

**Files:**
- Create: `engine/src/myui/mycompose_myui/my_compose_myui.h/.c`、`my_compose_myui_internal.h`
- Create: `engine/tests/test_mycompose_myui.c`
- Modify: `engine/CMakeLists.txt`

**Interfaces:**
- Consumes: tree diff、remember、Store、Task 4 原语、myui class registry/dispatcher。
- Produces: `MyComposeMyui`、`my_compose_myui_create/destroy/apply`、`my_compose_myui_sink()`；intrinsic `@root/@row/@column/@stack`。

- [ ] **Step 1: 写真实树 apply/rollback RED**

用 dummy window 绑定 Store 和 adapter。首次 apply 创建 class button/edit 与 row/column；同 key reorder 保持指针/focus；type change 替换；delete 清 focus/IME。事件 callback 只 enqueue Intent，不在 emitter 内 reduce/reconcile。

分别注入 factory OOM、property set failure、insert failure、detach failure、style capacity failure，断言原 children/order/属性/style/focus/grab/remember 完全恢复。duplicate key 在任何 factory 前失败。外部手工 reorder 后 apply 返回 `CONFLICT`。

```c
MyComposeStatus my_compose_myui_apply(MyComposeMyui *adapter,
                                      const MyComposeDiff *diff);
ASSERT_EQ(my_compose_myui_apply(adapter, &bad_diff), MY_COMPOSE_FAILED);
ASSERT_TRUE(tree_matches_snapshot(adapter, &before));
ASSERT_EQ(adapter->stats.factory_calls_after_duplicate, 0u);
```

- [ ] **Step 2: 实现 preflight、journal 和 commit**

保存 dispatcher grabbed/focused/hovered 和 old prop/style 值。创建先 detached，属性/listener 成功后 insert；MOVE 使用 reorder；删除区域只 detach 最高节点并保留引用。失败逆序撤销并恢复 dispatcher；事务中的 programmatic listener 被抑制。commit 先使旧 listener/handle generation 失效，逆序 dispose remember，再 unref 删除子树并发布快照。

style 删除调用 `my_widget_style_unset`；字符串 old value 用 `my_value_copy/reset`。commit 不分配；任何内部不变量破坏进入 `FAILED`，不返回部分成功。

- [ ] **Step 3: 验证 listener 代际与资源释放**

旧 listener id/generation 在 type change/delete 后不得 dispatch；重新插入的新 key 获得新 generation。window close listener 使 Store close，之后事件/completion 为 STALE/CANCELLED。运行普通及 ASan+UBSan focused、既有 myui 全套，变异 remove+add 代替 MOVE 必须 RED。

- [ ] **Step 4: 独立评审并提交**

通过后提交 `feat: apply declarative diffs transactionally to myui`。

### Task 6: UI Runtime、PAL completion 与异步销毁

**Files:**
- Create: `engine/src/myui/mycompose/my_compose_runtime.h/.c`
- Modify: `mycompose_myui/my_compose_myui.[ch]`
- Create: `engine/tests/test_mycompose_runtime.c`、`test_mycompose_async.c`
- Modify: `engine/CMakeLists.txt`

**Interfaces:**
- Produces: `MyComposeView`、`MyComposeSinkOps`、`MyComposeRuntimeConfig`、`MyComposeRuntime`、`my_compose_runtime_create/destroy/pump/restart`、`my_compose_myui_pump()`。
- Runtime 非拥有引用 Store 和 sink；调用方必须先销毁 Runtime，再销毁 Store/sink。

- [ ] **Step 1: 写帧顺序与异步代际 RED**

记录 sink 调用顺序，必须 `reduce→view/diff/apply/commit→dispatch_effects`。view 失败不再次 reduce，下帧重试同 State；已提交 effect 不重复启动。事件回调中直接 pump 必须 `CONFLICT`。

worker completion 只能经 `my_ui_command_scope` 回 loop。覆盖 restart、owner delete、window close、scope cancel、completion queue 32 满、executor PENDING 后 drain、destroy 与 worker 竞争。共享交付状态必须被 worker 读到 `OVERLOAD` 后有界重试，不能依赖 `my_ui_command` 忽略的 execute 返回值。

```c
typedef MyComposeStatus (*MyComposeView)(void *context,
    MyComposeTreeBuilder *builder, const void *state, uint32_t state_size);
typedef struct MyComposeSinkOps {
    void *context;
    MyComposeStatus (*apply)(void *context, const MyComposeDiff *diff);
} MyComposeSinkOps;
typedef struct MyComposeRuntimeConfig {
    MyComposeStore *store;
    MyComposeView view;
    void *view_context;
    MyComposeSinkOps sink;
} MyComposeRuntimeConfig;
MyComposeStatus my_compose_runtime_pump(MyComposeRuntime *runtime);
ASSERT_EQ(my_compose_runtime_pump(runtime), MY_COMPOSE_OK);
ASSERT_EQ(trace, "reduce,view,apply,commit,dispatch");
ASSERT_EQ(my_compose_store_diagnostics(store)->stale_completions, 1u);
```

- [ ] **Step 2: 实现 Runtime 和命令桥**

Runtime create 保存 UI thread id、Store、view、sink；builder 每帧重建 next。sink apply 成功后才 tree commit。effect executor 只从 UI 调用。myui command context 持有 delivery 状态和 completion 所有权，UI callback 在队列满时写 `OVERLOAD`，接受后才释放；scope close 只取消未执行 command，已执行 callback 由 Store 代际拒绝。

window close 先推进 store/owner 代际并关闭 Runtime scope。destroy 停止新 effect、关闭 scope、使 close/listener lease 失效，再销毁 Runtime；worker 不得持有 Runtime 指针。

- [ ] **Step 3: 普通/ASan/TSan 与故障注入**

运行正常、close/restart/delete、queue full、worker destroy race；ASan+UBSan 无 UAF/leak，TSan 无 data race。临时让 worker 直接调用 `my_compose_store_complete`，owner-thread guard 必须 RED，恢复 command bridge GREEN。

- [ ] **Step 4: 独立评审并提交**

通过后提交 `feat: schedule compose effects through the UI loop`。

### Task 7: C++20 RAII DSL 与 C parity

**Files:**
- Create: `engine/src/myui/mycompose/my_compose.hpp`
- Create: `engine/tests/test_mycompose_cpp20.cpp`、`test_mycompose_cpp20_header.cpp`、`compose_parity_fixture.h`
- Modify: `engine/CMakeLists.txt`

**Interfaces:**
- Produces: `breakxx::compose::{Runtime,Store,Builder,NodeScope,Intent,EffectBatch,StateOps}`；`Remember<T>`、`Runtime::Create/Pump/Restart`。
- C++ Runtime/Store 通过共享内部 Core 保持绑定稳定，move 只转移 wrapper，禁止 moved-from 使用；C++ 对象地址不作为持久身份。

- [ ] **Step 1: 写 C/C++ parity 与 RAII RED**

同一 `compose_parity_fixture.h` 驱动 C 和 C++：相同 keyed reorder、type change、intent 序列产生相同 canonical diff、State 和 Effect payload。C++ `NodeScope` 支持 `Row/Column/Stack/Element/Key/Property/Style/OnEvent`。

```cpp
auto store = Store<Counter>::Create(
    Counter{0},
    [](const Counter &current, Counter &candidate, const Intent &,
       EffectBatch &) {
        candidate.count = current.count + 1;
        return MY_COMPOSE_OK;
    });
ASSERT_TRUE(store.has_value());
auto moved = std::move(*store);
ASSERT_EQ(moved.Dispatch(Intent{.type = 1}), MY_COMPOSE_OK);
auto *slot = builder.Remember<Selection>(0u, [] { return Selection{2, 4}; });
ASSERT_EQ(slot->end, 4);
```

验证 move-only Runtime/Store、非 trivial remember 析构、local slot 换类型 `TYPE_MISMATCH`、异常转 `MY_COMPOSE_FAILED`、无异常构建 callback contract、自包含头和真实 C/C++ 链接。

- [ ] **Step 2: 实现 header-only DSL**

`NodeScope` 析构只关闭已打开 parent，sticky error 不抛跨 C ABI。`Remember<T>` 检查尺寸/对齐并 placement new。Store 预建 current/candidate `std::optional<State>`；`StateOps<T>::Clone/Destroy` 可定制，EffectBatch 使用 `std::array`。trampoline 捕获异常（无异常构建要求 `noexcept`）。公共 C 头保持 `extern "C"` 和 C11 pedantic。

- [ ] **Step 3: parity、header、ASan+UBSan 与变异**

分别运行 C fixture、C++ fixture、独立头 TU、跨语言 executable。临时让 C++ keyed identity 忽略 type，C parity 必须 RED，恢复 GREEN。比较 canonical bytes，不比较对象地址。

- [ ] **Step 4: 独立评审并提交**

通过后提交 `feat: add C++20 compose DSL`。

### Task 8: 真实图形、fuzz、分配与交付文档

**Files:**
- Create: `engine/tests/test_mycompose_gpu.cpp`、`test_mycompose_image.c`、`fuzz_mycompose_tree.c`、`fuzz_mycompose_intent.c`
- Create: `docs/design/compose_mvi.md`
- Modify: `.github/workflows/ci.yml`、`docs/myui.md`、`docs/Build_Guide.md`、`docs/Implementation_Status.md`、`engine/CMakeLists.txt`

**Interfaces:**
- Consumes: 全部 C/C++ API、生产 BreakUI/Platform/RHI/font sources、`editor_i18n` 的 UI-thread 翻译模式。
- Produces: 可重复 Vulkan/OpenGL 输入与像素证据、容量/fuzz/分配报告和当前使用文档。

- [ ] **Step 1: 先让真实图形和 CI 执行合同 RED**

新增 C++ GPU 测试：State 持有 `BreakEditorLang` 和列表顺序，button Intent 只切换 State 中的语言，view 用 `break_editor_tr_lang()` 取英文/中文文本，另一 Intent keyed reorder；reducer 不调用 `break_editor_i18n_set_lang()` 或其它全局 setter。通过生产 `platform_poll→break_ui_pump→my_compose_myui_pump→render→readback→present` 注入点击、键盘和文本，验证 State、同一 widget 身份、英文/中文区域非背景像素、reorder 后正确 hit target。分别显式请求 Vulkan 与 OpenGL，禁止 silent fallback。

CI 合同先因 regex 缺少 `test_mycompose_gpu_vulkan|opengl` 而 RED。无显示/GPU 只能退出 77；真实目标环境必须零 skip，不能修改既有执行统计来掩盖。

- [ ] **Step 2: 运行真实图形并取得 GREEN**

复用 `test_myui_break_rhi_clip` 的 Platform+RHI+readback 生命周期和实际字体 sources。记录实际 backend/device/driver、窗口、readback 和 present。Vulkan 默认；OpenGL 对照使用相同 fixture，关键区域做颜色/覆盖率阈值与 State 断言，不要求跨硬件整帧逐字节相同。

```bash
ctest --test-dir build-compose-vk --output-on-failure -j3 -L graphics
ctest --test-dir build-compose-gl --output-on-failure -j3 \
  -R '^(test_mycompose_gpu_opengl|test_rhi_wayland_runtime|test_mesh_gpu_gl|test_world_presentation_gl)$'
```

更新 CI OpenGL regex 显式包含 `test_mycompose_gpu_opengl`，Vulkan 对应 lane 显式包含 `test_mycompose_gpu_vulkan`；解析日志确认两项实际 Passed、零 Skipped。

- [ ] **Step 3: fuzz、分配、普通和 sanitizer**

fuzz 输入为长度前缀 node/property/intent stream，任意截断、重复 key、深度/容量溢出必须返回状态且不越界、不死循环。每个 fuzz target 固定 seeds+短 smoke，注册既有 fuzz label，不用 fuzz 代替行为断言。

allocation counter 预热后包住 C build/diff/store 和 C++ DSL 热路径，新层计数为 0；另记录既有 myui 动态分配，不能总报 0。普通全量、ASan+UBSan 全量非图形、TSan runtime/async、no-tests、五个既有 fuzz+两个新 fuzz 全部实际执行。

- [ ] **Step 4: 文档、独立总评审与交付**

`compose_mvi.md` 给出 C/C++ 示例、帧顺序、所有容量、identity、MVI 事务、effect retry、I18N/IME、myui 独占边界和证据等级。Build Guide 加 target/CTest/Wayland 命令；Implementation_Status 只追加真实计数和设备，历史不改写。

做全分支独立评审、Critical/Important scoped 清零、`git diff --check`、fetch/冲突处理、最终 merged-result 验证后才直接 push master。未运行的平台/硬件/听测明确保留限制，不把 lavapipe 当硬件 GPU，不创建 PR。
