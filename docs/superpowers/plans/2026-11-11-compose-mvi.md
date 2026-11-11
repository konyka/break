# Compose + MVI Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** 在现有 myui 上交付 C11/C++20 声明式 Compose 与完整 MVI，保留 keyed 身份并验证真实 Vulkan/OpenGL 输入和像素。

**Architecture:** C11 核心负责双缓冲描述树、diff、remember、store 与 UI-affine 调度；myui adapter 负责可回滚 stage 与无失败 commit；C++20 提供类型安全 RAII DSL。唯一结构发布顺序是 `sink.stage → tree.finalize → sink.commit`，tree 独占 remember/generation，adapter 独占 listener/widget/snapshot。

**Tech Stack:** C11、C++20、现有 myui/PAL/`my_ui_command`/emitter lease、CMake/CTest、Wayland、Vulkan、OpenGL、ASan+UBSan、TSan。

## Global Constraints

- 工作树 `/home/timeshift/opensource/break/.worktrees/compose-mvi`，分支 `compose-mvi`；实现代理串行、只读评审可并行。每任务 scoped commit 与独立规格/质量评审，不建 PR，构建和并行 CTest 均 `-j3`。
- 新代码不用外部引擎前缀或旧应用领域名。C 使用 `MyCompose*`/snake_case；C++ 使用 `breakxx::compose`、PascalCase、`kMax...`、尾部 `_`、move-only RAII、`[[nodiscard]]`。
- 固定上限：nodes 256、child links 255、depth 32、properties 512、events 256、diff ops 1024、remember 64×256 bytes、string arena 64 KiB、State 16 KiB、Intent 64、request slot 32、completion 32、payload 256 bytes、每 Intent 8 Effects、key/type/name 64 bytes。超限为 `MY_COMPOSE_OVERLOAD`，不静默截断。
- 每节点最多 64 properties、32 events、4 remember slots；slot 不超过 256 bytes 且对齐不超过 `max_align_t`。node/store generation 到 `UINT32_MAX` 退休 slot 或返回 `OVERLOAD`，request id 到 `UINT64_MAX` 返回 `OVERLOAD`，绝不回绕。
- keyed 身份为 `(parent,key,type)`，unkeyed 按直接子节点绝对位置；同 key 换 type 替换，跨 parent 不保留；MOVE 不得变成 DELETE+CREATE。
- outbox 与 outstanding 共用 32 个 request slot。State 发布前必须预检 `outbox + outstanding + 本批 Effect <= 32`；executor OK 只做无失败的 outbox→outstanding 移动。
- MVI 提交前失败保持原 State/outbox/outstanding/FIFO；view/tree/stage 失败保留已提交的新 State 和最后有效 UI，并设置 pending-view。恢复前不 reduce、不转换 completion、不 dispatch Effect，下一 pump 先重试同一 State revision。
- C ABI 不含 STL/异常/C++ ownership。复杂 State 显式 clone/dispose 预分配对象，不能 memcpy STL/拥有所有权对象。内部 Intent/Effect/Completion 各有 inline 256-byte payload，复制后不引用调用方内存。
- listener 强制写入当前节点 owner，Runtime/adapter 必须共用 Store，reducer 前再次核对 owner。事件只 enqueue Intent；reducer 不做 I/O；worker 不直接访问 Store/myui。
- tree finalize 是 remember dispose/node generation 的唯一所有者，恰好各一次；adapter commit 只处理 listener lease、owner 表、removed notify、widget unref 和快照。
- stage detach 不调用 removed hook；commit 才 notify。回滚不得提前清理 focus/grab/IME/selection，属性恢复必须已拥有、无分配且不可失败。
- Runtime 非拥有 Store/sink，调用方先销毁 Runtime，再在 UI 线程销毁 Store/sink。completion 使用原子状态+refcount+安全 lease，重投不得持有裸 Store/Runtime 指针。
- 新层预热后不逐帧 malloc；既有 myui children/string/listener 和超过 32 个直接子节点的 paint snapshot 分配单独记录。
- Vulkan 默认，OpenGL 最后降级和同机对照；Linux 仅 Wayland。record/null/headless 不冒充 GPU/声卡/听测；CI 图形测试必须实际执行且零 skip。
- 每项新行为先观察目标 RED 再实现 GREEN；每任务至少一个生产变异被测试杀死并恢复。Critical/Important 清零后才进入下一任务。历史文档不改写。

---

### Task 1: C11 描述树与 keyed diff

**Files:**
- Create: `engine/src/myui/mycompose/my_compose.h/.c`、`my_compose_tree.h/.c`、`my_compose_internal.h`
- Create: `engine/tests/test_mycompose_tree.c`
- Modify: `engine/CMakeLists.txt`

**Interfaces:**
- Produces: `MyComposeStatus`、`MyComposeNodeHandle`、`MyComposeString`、`MyComposeValue`、`MyComposeIntent`、`MyComposeNodeDesc`、`MyComposeDiff`、`MyComposeTreeBuilder`。
- API: builder create/destroy/begin/end/finalize、node/property/event、diff。

- [ ] **Step 1: 写身份、输入和容量 RED**

建立 `@root`→`@column`，覆盖 keyed A/B、unkeyed 混合、跨 parent 同 key、同 key 换 type、重复 key。首次 finalize 后 no-op=0；交换 A/B 只产生 MOVE 且 handle 不变；换 type 为 DELETE+CREATE；跨 parent 也为 DELETE+CREATE；重复 key 在 next/current 改变前失败。

```c
ASSERT_EQ(add_node(builder, root, "a", "button", &a), MY_COMPOSE_OK);
ASSERT_EQ(add_node(builder, root, "a", "edit", &duplicate), MY_COMPOSE_DUPLICATE_KEY);
ASSERT_EQ(my_compose_tree_builder_diff(builder)->count, 0u);
```

边界必须包含第 257 节点、33 层、第 513 全局 property、同节点第 65 property、第 257 全局 event、同节点第 33 event、diff op 1025、字符串超限/嵌入 NUL。property/event payload 复制后修改调用方 buffer 不得改变树。

- [ ] **Step 2: 先看到 RED，再实现双缓冲和校验**

先因缺 API/target RED；补声明和 `MY_COMPOSE_FAILED` stub 后必须仍因行为断言 RED。配置：

```bash
cmake -S engine -B build-compose-normal -DCMAKE_BUILD_TYPE=Debug \
  -DENGINE_BUILD_TESTS=ON -DENGINE_RHI_BACKEND=auto -DBREAK_ENABLE_SNOWFLAKE=OFF
cmake --build build-compose-normal --target test_mycompose_tree -j3
./build-compose-normal/test_mycompose_tree
```

公共类型与入口：

```c
typedef struct MyComposeNodeHandle { uint32_t index, generation; } MyComposeNodeHandle;
typedef struct MyComposeIntent {
    uint32_t type, payload_size;
    const uint8_t *payload;
    MyComposeNodeHandle owner;
    uint32_t result;
} MyComposeIntent;
MyComposeStatus my_compose_tree_builder_begin(MyComposeTreeBuilder *);
MyComposeStatus my_compose_tree_builder_node(MyComposeTreeBuilder *,
    const MyComposeNodeDesc *, MyComposeNodeHandle *);
MyComposeStatus my_compose_tree_builder_property(MyComposeTreeBuilder *,
    MyComposeNodeHandle, const char *, const MyComposeValue *);
MyComposeStatus my_compose_tree_builder_event(MyComposeTreeBuilder *,
    MyComposeNodeHandle, const char *, const MyComposeIntent *);
MyComposeStatus my_compose_tree_builder_end(MyComposeTreeBuilder *);
MyComposeStatus my_compose_tree_builder_finalize(MyComposeTreeBuilder *);
```

根由首个 parent=零 handle 的 `@root` 声明，parent 必须先声明。next 每次从空构建；keyed 先查同 parent duplicate，再按 `(parent,key,type)` 匹配，unkeyed 用绝对位置。commit 改名为 finalize，避免与 adapter commit 混淆。slot 到 `UINT32_MAX` 永久退休，内部近溢出种子必须测试。

- [ ] **Step 3: GREEN、全量和变异**

运行 focused 与全量非图形。临时忽略 type、允许跨 parent 复用或跳过 duplicate preflight，分别必须 RED，恢复 GREEN。factory 不属于本层，重复 key 断言检查 next/current 未变。

- [ ] **Step 4: 独立评审并提交**

通过后提交 `feat: add declarative tree diff`。

### Task 2: remember 与节点代际

**Files:**
- Create: `engine/src/myui/mycompose/my_compose_remember.h/.c`
- Modify: `my_compose_tree.[ch]`、`my_compose_internal.h`
- Create: `engine/tests/test_mycompose_remember.c`

**Interfaces:**
- Produces: `MyComposeRememberOps`、`my_compose_tree_builder_remember()`、`remember_get()`。
- tree finalize 独占 dispose/generation；后续 adapter 不重复调用。

- [ ] **Step 1: 写生命周期 RED**

相同 keyed reorder 保持 slot 指针和值；type 替换/节点删除按深度与声明逆序 dispose；aborted next 只销毁新 slot；旧 generation `remember_get=STALE`；同 local slot 换 type tag=`TYPE_MISMATCH`。每次 finalize 后每个消失 slot 恰好 dispose 一次。

```c
MyComposeStatus my_compose_tree_builder_remember(
    MyComposeTreeBuilder *, MyComposeNodeHandle, uint32_t local_slot,
    uint64_t type_tag, uint32_t size, uint32_t alignment,
    const MyComposeRememberOps *, void **out_storage);
ASSERT_EQ(my_compose_tree_builder_remember_get(builder, old, 0u, &storage),
          MY_COMPOSE_STALE);
```

覆盖 local_slot≥4、第 65 slot、size>256、alignment 为 0/非 2 的幂/超过 `max_align_t`。dispose 必须 no-fail 且不执行 I/O。

- [ ] **Step 2: 先 RED，再实现固定 slot**

slot 使用内部对齐存储，仅首次身份初始化；匹配复用。finalize 逆序 dispose 消失节点、推进 generation、交换 current/next。失败路径不得触碰 current slot。重复 finalize 不得再次 dispose 同一旧代际。

- [ ] **Step 3: ASan+UBSan 与变异**

运行普通 focused 和 sanitizer focused。临时保留 type-replaced slot 或重复 dispose，测试必须 RED，恢复 GREEN。

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

### Task 3: MVI Store、原子 reducer 与 request slot

**Files:**
- Create: `engine/src/myui/mycompose/my_compose_store.h/.c`
- Create: `engine/tests/test_mycompose_store.c`
- Modify: `my_compose.h`、CMake targets

**Interfaces:**
- Consumes: Task 1 Intent；入队时复制到独立 inline payload。
- Produces: `MyComposeEffect/Batch`、`MyComposeCompletion`、`MyComposeStateOps`、`MyComposeReducer`、`MyComposeExecutor`、`MyComposeStore`。
- API: create/destroy、dispatch/complete、register/invalidate owner、reduce/dispatch_effects、restart/close、state/diagnostics、effect_batch_append。

- [ ] **Step 1: 写 FIFO、原子性和 slot 耗尽 RED**

State 为 `uint32_t count`，A=+1、B=+10，FIFO 后 count=11。clone/reducer/batch/outbox 失败均不得改变 State/FIFO。第 9 个 Effect 必须通过公共 append 产生，返回 `OVERLOAD`、batch 不变且 sticky，candidate 正确 dispose。

```c
typedef struct MyComposeStateOps {
    void *context;
    MyComposeStatus (*clone)(void *, const void *, uint32_t, void *, uint32_t, uint32_t *);
    void (*dispose)(void *, void *, uint32_t);
} MyComposeStateOps;
typedef MyComposeStatus (*MyComposeReducer)(void *, const MyComposeIntent *,
    const void *, uint32_t, void *, uint32_t *, MyComposeEffectBatch *);
typedef MyComposeStatus (*MyComposeExecutor)(void *, const MyComposeEffect *);
MyComposeStatus my_compose_effect_batch_append(MyComposeEffectBatch *,
    uint32_t type, const void *payload, uint32_t payload_size);
const MyComposeDiagnostics *my_compose_store_diagnostics(const MyComposeStore *);
```

跨多个 drain 让 32 个 Effect 都被接受但无 completion，outbox 可为空而 outstanding=32；下一个带 Effect Intent 必须在 reducer/State 发布前返回 `OVERLOAD`，不得调用 executor。无 Effect Intent 仍可提交。executor PENDING 保留队首，drain 后恢复。

- [ ] **Step 2: 实现 Store 与三代校验**

State slot 为 2×16 KiB，clone 后才允许 reducer 修改 candidate。EffectBatch append 每项最多 256 bytes，sticky 错误使本 Intent 失败。发布前检查 `outbox+outstanding+batch<=32`；OK 只做无失败 slot 移动。

owner 表按 node index 保存当前 generation，注册替换、失效退休；入队和 reduce 前都核对。restart 清 pending/outbox/outstanding 并推进 store generation，保留 State；close 拒绝新输入。request id 不回绕。

completion 队列独立为 32，接受 completion 才消费 outstanding 并转 Intent；队列满返回 `OVERLOAD` 且 outstanding 保留，worker 后续可重试。`reduce` 每次最多转换 32 个 completion、处理总计最多 64 个 Intent（含 completion-derived），result 原样传递。

- [ ] **Step 3: 真实 owner、预算与变异**

注册 `{1,1}` owner，effect 得到 request=1；restart、owner invalidate、close 后 completion 必须 STALE 且不 reduce。排队后删除 owner 的 Intent 也不得 reduce。验证 65 个 Intent 与 33 个 completion 的 FIFO/预算。临时漏掉 owner 检查或 outstanding 预检，必须 RED，恢复 GREEN。

- [ ] **Step 4: 独立评审并提交**

通过后提交 `feat: add transactional MVI store`。

### Task 4: myui 结构、通知与样式删除原语

**Files:**
- Modify: `engine/src/myui/myui/my_widget.[ch]`、`my_style.[ch]`、`my_theme.c`
- Create: `engine/tests/test_mycompose_widget_primitives.c`
- Modify: `engine/CMakeLists.txt`

**Interfaces:**
- Produces: `my_widget_reorder_child`、`my_widget_insert_child`、`my_widget_detach_child`、`my_widget_notify_child_removed`、`my_style_unset`、`my_widget_style_unset`。

- [ ] **Step 1: 写指针和清理时机 RED**

真实 dummy window 中建立 A/B edit，保存文本 selection、focus/grab/IME 与指针。reorder 后指针/选择/focus/grab 不变。stage detach 后 parent=NULL、调用方持 ref，但 removed hook 次数为 0，selection/focus/grab/IME 尚未清理；reinsert 恢复同一指针且状态不变。显式 notify 后才执行既有清理。

```c
my_ret_t my_widget_reorder_child(my_widget_t *, my_widget_t *, size_t);
my_ret_t my_widget_insert_child(my_widget_t *, my_widget_t *, size_t);
my_ret_t my_widget_detach_child(my_widget_t *, my_widget_t *, my_widget_t **);
void my_widget_notify_child_removed(my_widget_t *, my_widget_t *);
my_ret_t my_widget_style_unset(my_widget_t *, my_widget_state_t, const char *);
```

既有 remove_child 必须仍是 notify→detach→unref。style unset 回退 theme，缺失 key=`MY_RET_NOT_FOUND`；越界、非 child、循环 attach 拒绝。

- [ ] **Step 2: 实现无通知 detach 与显式通知**

reorder 只移动 darray 元素，不改 parent/ref/focus。insert 只接 detached child 且 index≤count。detach 复用布局/invalidation，但不调用 removed hook；notify 独立调用原 hook。remove 改为 notify+detach+unref。`my_style_unset` reset value 并压缩数组，wrapper 使旧/新区域失效。

- [ ] **Step 3: GREEN、sanitizer 和变异**

运行 focused 与既有 widget/dispatcher/edit/focus 测试。临时把 reorder 实现成 remove+add，focus/selection 必须 RED；临时在 detach 中提前 notify，清理时机测试必须 RED。ASan+UBSan 验证引用无泄漏/UAF。

- [ ] **Step 4: 独立评审并提交**

通过后提交 `feat: separate widget staging from removal notification`。

### Task 5: myui 事务、省略语义与唯一 finalize

**Files:**
- Create: `engine/src/myui/mycompose_myui/my_compose_myui.h/.c`、`my_compose_myui_internal.h`
- Modify: `engine/src/myui/myui/my_widget_class.h/.c`、`my_widget_class_builtin.c`，以及使用的文本控件属性实现
- Create: `engine/tests/test_mycompose_myui.c`
- Modify: `engine/CMakeLists.txt`

**Interfaces:**
- Produces: `MyComposeMyui`、`my_compose_myui_stage/commit/rollback`、`my_compose_myui_sink()`。
- sink stage 后必须由调用方执行 tree finalize，再 sink commit；adapter 不调用 remember dispose。
- `my_prop_desc_t` 新增可选 capture/discard/no-fail restore 事务回调。

- [ ] **Step 1: 写真实树 stage/rollback/省略 RED**

dummy window 绑定 Store/adapter。首次创建 button/edit/row/column；reorder 保持指针/focus；type change 替换；delete 只在 commit 清 focus/IME。listener 强制使用当前节点 owner，省略 event 只吊销 listener lease，不推进保留节点 owner generation。

分别注入 factory OOM、property set failure、insert failure、第一次/第二次 detach failure、style capacity failure 和恢复点错误，断言原 children/order/property/style/selection/focus/grab/IME/remember 完全恢复且只执行原错误的回滚。duplicate key 在 factory 前失败；外部手工 reorder 返回 `CONFLICT`。

```c
MyComposeStatus my_compose_myui_stage(MyComposeMyui *, const MyComposeDiff *);
void my_compose_myui_commit(MyComposeMyui *);
void my_compose_myui_rollback(MyComposeMyui *);
ASSERT_EQ(my_compose_myui_stage(adapter, &bad_diff), MY_COMPOSE_FAILED);
my_compose_myui_rollback(adapter);
ASSERT_TRUE(tree_matches_snapshot(adapter, &before));
ASSERT_EQ(adapter->stats.factory_calls_after_duplicate, 0u);
```

测试内 `TreeSnapshot` 保存有序 widget 指针、属性、selection/IME/focus/grab 与 dispose 次数，`tree_matches_snapshot` 逐项比较，不能只比较根指针。

- [ ] **Step 2: 实现 preflight、事务恢复与两阶段发布**

POD 属性保存值；可能分配的属性必须在 descriptor 提供 capture/discard/no-fail restore。字符串恢复用已拥有 buffer/state swap，文本 capture 包括 selection/IME；缺回调的字符串属性在 preflight `NOT_SUPPORTED`。rollback 不分配、不执行 removed hook，恢复不得再次调用可能失败的普通 setter。

stage 创建/更新/插入/MOVE/结构 detach 全成功后才允许发布。Runtime 的固定顺序为：

```text
sink.stage(diff)
tree.finalize()        // 唯一 remember dispose + node generation
sink.commit()          // listener/owner/notify/unref/snapshot only
```

commit 不分配、不失败；step 中每个 remember 恰好 dispose 一次、每个旧代际恰好失效一次。stage 失败只走 rollback，不 finalize。

完整声明的省略表示恢复首次绑定/factory 默认：property/layout 恢复默认，style unset，event 吊销 listener；显式 `MyComposeValue.none` 对 property/layout 同省略，style 为 unset。row/column 保留 intrinsic layouter，普通节点默认 absolute+AUTO。覆盖四类 set→omit、显式 none、更新、回滚及省略后旧事件不投递。

- [ ] **Step 3: listener 代际与资源验证**

旧 listener 在 type change/delete 后不得 dispatch，省略 event 不再投递，保留节点 owner 不被误推进。window close 使 Store close。运行普通及 ASan+UBSan focused、既有 myui 全套；临时在 stage detach 提前 notify 或在 adapter 再次 dispose remember，必须 RED。

- [ ] **Step 4: 独立评审并提交**

通过后提交 `feat: apply declarative diffs transactionally to myui`。

### Task 6: Runtime、pending-view 与安全 completion

**Files:**
- Create: `engine/src/myui/mycompose/my_compose_runtime.h/.c`
- Modify: `mycompose_myui/my_compose_myui.[ch]`
- Create: `engine/tests/test_mycompose_runtime.c`、`test_mycompose_async.c`
- Modify: `engine/CMakeLists.txt`

**Interfaces:**
- Produces: `MyComposeView`、`MyComposeSinkOps`、`MyComposeRuntimeConfig`、`MyComposeRuntime`、`my_compose_runtime_create/destroy/pump/restart`、`my_compose_myui_pump()`。
- Runtime 非拥有 Store/sink；先 Runtime destroy，再 UI-thread Store/sink destroy。

- [ ] **Step 1: 写调度、pending-view 与重投销毁 RED**

记录调用顺序，必须 `reduce→sink.stage→tree.finalize→sink.commit→dispatch_effects`。两个排队 Intent 首次 view 失败后，下一 pump 不得 reduce 第二个 Intent 或 dispatch effect；同一 State revision 重试成功后才继续。65 Intent/33 completion 遵守 Task 3 总预算，reducer/executor 不重复。

```c
typedef MyComposeStatus (*MyComposeView)(void *,
    MyComposeTreeBuilder *, const void *, uint32_t);
typedef struct MyComposeSinkOps {
    MyComposeStore *store;
    MyComposeStatus (*stage)(void *, const MyComposeDiff *);
    void (*commit)(void *);
    void (*rollback)(void *);
} MyComposeSinkOps;
typedef struct MyComposeRuntimeConfig {
    MyComposeStore *store;
    MyComposeView view;
    void *view_context;
    MyComposeSinkOps sink;
} MyComposeRuntimeConfig;
```

Runtime create 必须要求 `config.store == config.sink.store`。事件回调中直接 pump 返回 `CONFLICT`。真实点击产生 Effect 后删除该节点，旧 completion 必须 STALE，不能进入另一 Store。

构造 completion queue 满且 callback 已执行、worker 暂停在重投前；随后 close/destroy Runtime 和 Store，再恢复 worker。post 失败、STALE、CANCELLED、scope cancel 均必须是非成功终态并释放引用，不得 UAF/伪 accepted。

- [ ] **Step 2: 实现 Runtime 和 lease 命令桥**

view/diff 或 sink stage 失败设置 pending-view，下一 pump 先以同一 State revision 重建，期间不 reduce/convert/dispatch。sink stage 成功后才 tree finalize 与 sink commit，成功才清 pending-view 并 dispatch outbox。

completion context 使用原子 PENDING/ACCEPTED/RETRY/CANCELLED 与 refcount，worker/UI command 各持引用。worker 重投只持 completion 和安全 emitter lease；UI callback 经 lease 取 Store。队列满写 `OVERLOAD` 且不消费 outstanding；接受后才转 Intent。post 失败与 cancel 释放双方引用。

window close 先失效 Store lease、推进代际，再关 scope。Store destroy 在 UI 线程先失效 lease、关 scope 再释放；正在执行的 callback 与 UI destroy 不并发，worker 后续只能看到失效 lease 并安全释放。worker 不得持裸 Store/Runtime。

- [ ] **Step 3: 普通/ASan/TSan 与故障注入**

覆盖 close/restart/delete、queue full、post failure、scope cancel、worker destroy race。ASan+UBSan 无 UAF/leak，TSan 无 data race。临时让 worker 直接调用 `my_compose_store_complete`，owner-thread/lease guard 必须 RED，恢复 bridge GREEN。

- [ ] **Step 4: 独立评审并提交**

通过后提交 `feat: schedule compose effects through the UI loop`。

### Task 7: C++20 RAII DSL 与 C parity

**Files:**
- Create: `engine/src/myui/mycompose/my_compose.hpp`
- Create: `engine/tests/test_mycompose_cpp20.cpp`、`test_mycompose_cpp20_header.cpp`、`compose_parity_fixture.h`
- Modify: `engine/CMakeLists.txt`

**Interfaces:**
- Produces: `breakxx::compose::{Runtime,Store,Builder,NodeScope,Intent,EffectBatch,StateOps}`、`Remember<T>`、`Runtime::Create/Pump/Restart`。
- C++ Runtime/Store 通过共享内部 Core 稳定绑定，move 只转移 wrapper；C++ 对象地址不作为持久身份。

- [ ] **Step 1: 写 C/C++ parity、RAII 和异常 RED**

同一 fixture 在 C/C++ 产生相同 canonical diff、State 和 Effect payload。C++ `NodeScope` 支持 `Row/Column/Stack/Element/Key/Property/Style/OnEvent`。`Remember<T>` 返回 `T*`，失败为 nullptr 且 Builder sticky status 非 OK。

```cpp
auto store = Store<Counter>::Create(
    Counter{0}, [](const Counter &current, Counter &candidate,
                   const Intent &, EffectBatch &) {
        candidate.count = current.count + 1;
        return MY_COMPOSE_OK;
    });
ASSERT_TRUE(store.has_value());
auto moved = std::move(*store);
ASSERT_EQ(moved.Dispatch(Intent{.type = 1}), MY_COMPOSE_OK);
auto *slot = builder.Remember<Selection>(0u, [] { return Selection{2, 4}; });
ASSERT_NEQ(slot, nullptr);
ASSERT_EQ(slot->end, 4);
```

使用不可默认构造、不可拷贝赋值、move-only 自定义 Clone，以及构造/clone/reducer 抛异常 fixture，验证 State 原子性和析构次数。覆盖 moved-from、local slot 换类型、自包含头和真实 C/C++ 链接。

- [ ] **Step 2: 实现 header-only DSL**

`NodeScope` 析构只关闭已打开 parent，sticky error 不抛跨 C ABI。`Remember<T>` 检查尺寸/对齐并 placement new，失败返回 nullptr。

两个 State slot 都是 `std::optional<State>`，仅存活时 engaged：Clone 前 candidate reset，成功 Clone 后 engaged，失败/复用时 reset，禁止在活对象上重复 placement new。默认 Clone 用 copy construction，自定义 Clone 支持 move-only State。EffectBatch 用 `std::array`，trampoline 捕获异常（无异常构建要求 `noexcept`）。公共 C 头保持 `extern "C"` 和 C11 pedantic。

- [ ] **Step 3: parity、header、sanitizer 与变异**

分别运行 C fixture、C++ fixture、独立头 TU、跨语言 executable。临时让 C++ keyed identity 忽略 type 或在 engaged optional 上重复构造，测试必须 RED，恢复 GREEN。比较 canonical bytes，不比较对象地址。

- [ ] **Step 4: 独立评审并提交**

通过后提交 `feat: add C++20 compose DSL`。

### Task 8: 真实图形、fuzz、分配与交付文档

**Files:**
- Create: `engine/tests/test_mycompose_gpu.cpp`、`test_mycompose_image.c`、`fuzz_mycompose_tree.c`、`fuzz_mycompose_intent.c`
- Create: `docs/design/compose_mvi.md`
- Modify: `.github/workflows/ci.yml`、`docs/myui.md`、`docs/Build_Guide.md`、`docs/Implementation_Status.md`、`engine/CMakeLists.txt`

**Interfaces:**
- Consumes: 全部 C/C++ API、生产 BreakUI/Platform/RHI/font sources、`editor_i18n` 的 UI-thread 翻译模式。
- Produces: Vulkan/OpenGL 输入与像素证据、容量/fuzz/分配报告和当前使用文档。

- [ ] **Step 1: 先让真实图形和 CI 执行合同 RED**

C++ GPU 测试的 State 持有 `BreakEditorLang` 与列表顺序；Intent 只改 State，view 用 `break_editor_tr_lang()`，reducer 不调用全局语言 setter。生产路径 `platform_poll→break_ui_pump→my_compose_myui_pump→render→readback→present` 执行点击、键入和文本，验证 State、widget 身份、英文/中文区域像素和 reorder 后 hit target。分别显式 Vulkan/OpenGL，禁止 silent fallback。

CI 合同先因 regex 缺 `test_mycompose_gpu_vulkan/opengl` 而 RED。无显示/GPU 只能退出 77，真实目标环境必须零 skip。

- [ ] **Step 2: 显式配置、构建并取得真实 GREEN**

复用 `test_myui_break_rhi_clip` 的 Platform+RHI+readback 生命周期和实际字体 sources，记录 backend/device/driver、窗口、readback、present。Vulkan 默认，OpenGL 同 fixture 对照；比较关键区域颜色/覆盖率与 State，不要求跨硬件整帧逐字节一致。

```bash
cmake -S engine -B build-compose-vk -DCMAKE_BUILD_TYPE=Debug \
  -DENGINE_BUILD_TESTS=ON -DENGINE_RHI_BACKEND=vulkan -DBREAK_ENABLE_SNOWFLAKE=OFF
cmake --build build-compose-vk --target test_mycompose_gpu -j3
ctest --test-dir build-compose-vk --output-on-failure -j3 -L graphics

cmake -S engine -B build-compose-gl -DCMAKE_BUILD_TYPE=Debug \
  -DENGINE_BUILD_TESTS=ON -DENGINE_RHI_BACKEND=opengl -DBREAK_ENABLE_SNOWFLAKE=OFF
cmake --build build-compose-gl --target test_mycompose_gpu -j3
ctest --test-dir build-compose-gl --output-on-failure -j3 \
  -R '^(test_mycompose_gpu_opengl|test_rhi_wayland_runtime|test_mesh_gpu_gl|test_world_presentation_gl)$'
```

本地使用当前 Fedora Wayland 会话，CI 沿用既有 Weston 配置；不得启用 X11。CI OpenGL/Vulkan regex 显式加入对应 Compose 测试，解析日志确认实际 Passed、零 Skipped。

- [ ] **Step 3: fuzz、分配、普通和 sanitizer**

fuzz 输入为长度前缀 node/property/intent stream，截断、重复 key、深度/容量溢出必须返回状态且不越界、不死循环。固定 seeds+短 smoke，注册既有 fuzz label，不替代行为断言。

allocation counter 预热后包住 C build/diff/store 与 C++ DSL 热路径，新层为 0；既有 myui 分配单独记录。普通全量、ASan+UBSan 全量非图形、TSan runtime/async、no-tests、既有五个 fuzz+两个新 fuzz 全部实际执行。

- [ ] **Step 4: 文档、独立总评审与交付**

`compose_mvi.md` 给出 C/C++ 示例、唯一 finalize 顺序、容量、identity、MVI 原子边界、pending-view、effect retry、lease 生命周期、I18N/IME、myui 独占边界和证据等级。Build Guide 加 target/CTest/Wayland 命令；Implementation_Status 只追加真实计数和设备，历史不改写。

做全分支独立评审、Critical/Important scoped 清零、`git diff --check`、fetch/冲突处理、最终 merged-result 验证后才直接 push master。未运行的平台/硬件/听测明确保留限制，不把 lavapipe 当硬件 GPU，不创建 PR。
