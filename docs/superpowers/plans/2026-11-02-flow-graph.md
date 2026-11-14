# Flow Graph Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** 交付可执行、可安全序列化且可由 myui/undo 编辑的有界 Flow Graph。

**Architecture:** 新建独立 `break_flow` 图资产与运行时库，运行时通过 `break_kernel` 原子动作批次修改实体。`BreakEditorDoc` 持有图资产，图命令保存前后版本化字节以保证 undo/redo 的 id 和连接完全恢复；独立 myui 列表面板调用这些命令。

**Tech Stack:** C11、CTest、`test_framework.h`、现有 BreakKernel/ECS、BreakEditorCmdStack、myui widgets；无新依赖。

## Global Constraints

- 所有写操作仅在 `/home/timeshift/opensource/break/.worktrees/cry-flow-ai`，分支 `cry-wave1-flow-ai`；不 push、不建 PR、不改 `docs/Implementation_Status.md`。
- 热路径不临时分配；节点硬上限 256、连接硬上限 1024，超限报错，不静默截断。
- LogicThread 独占运行时和实体修改；持久实体身份使用 `{index, generation}`。
- 新库不链入 `engine`、`engine_demo`、`dxx_break`；不重命名或复用 `rule_engine` 冒充 Flow Graph。
- 每组行为先真实 RED 再 GREEN；环、预算、序列化防护和原子动作执行变异检查。
- normal、ASan+UBSan、TSan focused 均以 `cmake --build ... -j3` 构建并实际运行。
- 设计文档：`docs/design/flow_graph.md`。最终报告：`.superpowers/sdd/flow-graph-report.md`。

## File Structure

- `engine/src/kernel/break_flow.h`：公开图、端口、序列化、运行时 API 与硬上限。
- `engine/src/kernel/break_flow_internal.h`：图/运行时固定存储布局和内部验证函数。
- `engine/src/kernel/break_flow_graph.c`：节点、连接、稳定 id、端口检查、DFS 环检测。
- `engine/src/kernel/break_flow_serial.c`：v1 小端编码与 fail-closed 解码。
- `engine/src/kernel/break_flow_runtime.c`：确定性队列、求值、预算、延迟和动作暂存。
- `engine/src/kernel/break_kernel_flow.c`：LogicThread 实体动作批次预校验与原子提交。
- `engine/src/editor/editor_flow.h/.c`：文档图资产访问和 undoable 图命令。
- `engine/apps/editor/editor_panel_flow.c`：真实 myui 节点列表、连接和属性编辑。
- `engine/tests/test_break_flow_graph.c`：图结构、端口、容量与环。
- `engine/tests/test_break_flow_serial.c`：往返与恶意/损坏字节。
- `engine/tests/test_break_flow_runtime.c`：执行、队列、预算、原子性和 owner。
- `engine/tests/test_editor_flow.c`：图命令 undo/redo。
- `engine/tests/test_editor_shell.c`：真实 Flow 面板 emitter 端到端用例。
- `engine/CMakeLists.txt`：库、测试、editor/test shell 源文件注册。

---

### Task 1: 有界图、显式端口与环检测

**Files:**
- Create: `engine/src/kernel/break_flow.h`, `engine/src/kernel/break_flow_internal.h`, `engine/src/kernel/break_flow_graph.c`
- Create: `engine/tests/test_break_flow_graph.c`
- Modify: `engine/CMakeLists.txt:678`

**Interfaces:**
- Produces: `BreakFlowGraph`, `BreakFlowNodeDesc`, `BreakFlowLinkDesc`, `break_flow_graph_create/destroy`, `break_flow_node_add/remove/set/get/at`, `break_flow_link_add/remove/get/at`, `break_flow_graph_validate`, `break_flow_graph_revision`。
- Error surface: `BREAK_FLOW_OK/INVALID/OVERLOAD/STALE/REJECTED/FAILED/TIMEOUT`。

- [ ] **Step 1: 写稳定 id、端口、环和失败原子的失败测试**

测试必须包含以下实际断言模式：

```c
BreakFlowConfig cfg = {4u, 8u};
BreakFlowGraph *g = break_flow_graph_create(&cfg);
BreakFlowNodeDesc event = {0};
event.type = BREAK_FLOW_NODE_EVENT;
event.event_key = 7u;
ASSERT_EQ(break_flow_node_add(g, &event, &event_id), BREAK_FLOW_OK);
ASSERT_EQ(break_flow_node_add(g, &sequence, &sequence_id), BREAK_FLOW_OK);
BreakFlowLinkDesc edge = {BREAK_FLOW_PORT_EXEC, event_id,
    BREAK_FLOW_EVENT_EXEC_OUT, sequence_id, BREAK_FLOW_EXEC_IN};
ASSERT_EQ(break_flow_link_add(g, &edge, &edge_id), BREAK_FLOW_OK);
ASSERT_EQ(break_flow_link_add(g, &cycle, &untouched), BREAK_FLOW_REJECTED);
ASSERT_EQ(untouched, UINT32_MAX);
ASSERT_EQ(break_flow_graph_link_count(g), 1u);
```

另测删除后新 id 不复用、重复 event key、非法方向/类型、重复输入、容量满和删除级联。

- [ ] **Step 2: 注册目标并确认 RED**

在 `break_kernel` 后注册 `break_flow` 静态库及 `test_break_flow_graph`。运行：

```bash
cmake -S engine -B build-flow-normal -DENGINE_RHI_BACKEND=opengl -DBREAK_ENABLE_CRYPTO=OFF
cmake --build build-flow-normal --target test_break_flow_graph -j3
```

预期：首次因头文件/目标不存在而配置或编译失败；若先放空实现，测试必须因行为断言失败，不能停在链接桩。

- [ ] **Step 3: 实现图存储和完整验证**

节点/连接数组按索引即 id 分配；`next_node_id/next_link_id` 只增且不复用。添加连接时先写入一个空槽，调用全图三色 DFS，失败则清空该槽并恢复 next-id/revision。节点 set 在临时副本上验证属性与所有关联端口后提交。

```c
static bool dfs_visit(const BreakFlowGraph *g, u32 id, u8 *state) {
    if (state[id] == 1u) return false;
    if (state[id] == 2u) return true;
    state[id] = 1u;
    for (u32 i = 1u; i <= g->max_links; ++i) {
        const BreakFlowLink *link = &g->links[i];
        if (link->used && link->desc.source_node == id &&
            !dfs_visit(g, link->desc.target_node, state)) return false;
    }
    state[id] = 2u;
    return true;
}
```

实际实现用创建时分配的 `visit_state` 工作区，禁止递归深度超过 256；可用显式三色迭代栈替代上述逻辑以消除运行时栈顾虑。

- [ ] **Step 4: GREEN 与回归**

```bash
cmake --build build-flow-normal --target test_break_flow_graph -j3
./build-flow-normal/test_break_flow_graph
```

预期：全部图测试通过，非法操作前后 revision、计数和序列化前的 next-id 状态不变。

- [ ] **Step 5: 环防护变异并恢复**

临时令 DFS 对回边返回成功，重跑测试，预期环用例 RED；立即恢复并重跑 GREEN。记录命令和结果到最终报告。

- [ ] **Step 6: 提交**

```bash
git add engine/src/kernel/break_flow* engine/tests/test_break_flow_graph.c engine/CMakeLists.txt
git commit -m "flow: add bounded graph with explicit ports"
```

---

### Task 2: 版本化安全序列化

**Files:**
- Create: `engine/src/kernel/break_flow_serial.c`, `engine/tests/test_break_flow_serial.c`
- Modify: `engine/src/kernel/break_flow.h`, `engine/src/kernel/break_flow_internal.h`, `engine/CMakeLists.txt`

**Interfaces:**
- Produces: `break_flow_serialized_size`, `break_flow_serialize`, `break_flow_deserialize(const void *bytes, usize len, BreakFlowGraph **out)`。
- Consumes: Task 1 的全图验证和固定容量配置。

- [ ] **Step 1: 写往返和损坏输入失败测试**

往返后逐节点/连接比较，并验证删除后的 next-id 保留。以有效字节为母体分别变异版本、header size、total size、node/link count、next-id、名称长度、节点类型、非有限浮点、delay=0、悬空 source/target、非法端口、重复 id 和环；每个用例要求：

```c
BreakFlowGraph *loaded = (BreakFlowGraph *)(uintptr_t)1u;
ASSERT_EQ(break_flow_deserialize(corrupt, corrupt_len, &loaded),
          BREAK_FLOW_INVALID);
ASSERT_TRUE(loaded == NULL);
ASSERT_EQ(break_flow_deserialize(corrupt, corrupt_len - 1u, &loaded),
          BREAK_FLOW_INVALID);
```

同时测试输出缓冲区不足时不写长度成功值、尾随字节拒绝和空图往返。

- [ ] **Step 2: 构建运行确认 RED**

```bash
cmake --build build-flow-normal --target test_break_flow_serial -j3
./build-flow-normal/test_break_flow_serial
```

预期：缺少序列化符号或所有安全断言失败。

- [ ] **Step 3: 实现显式编码与事务式解码**

使用字节读写助手，禁用 packed struct 直接 I/O：

```c
static void put_u32(u8 *p, u32 v) {
    p[0] = (u8)v; p[1] = (u8)(v >> 8);
    p[2] = (u8)(v >> 16); p[3] = (u8)(v >> 24);
}
static bool take_u32(BreakFlowReader *r, u32 *out) {
    if (r->pos > r->len || r->len - r->pos < 4u) return false;
    *out = (u32)r->bytes[r->pos] |
           ((u32)r->bytes[r->pos + 1u] << 8) |
           ((u32)r->bytes[r->pos + 2u] << 16) |
           ((u32)r->bytes[r->pos + 3u] << 24);
    r->pos += 4u;
    return true;
}
```

先在栈上解析固定头并检查 `len == total_size`，再创建目标图；节点和连接 id 必须升序，最后 `break_flow_graph_validate` 和精确末尾检查。任何路径释放临时图并把 `*out=NULL`。

- [ ] **Step 4: GREEN**

```bash
cmake --build build-flow-normal --target test_break_flow_serial test_break_flow_graph -j3
./build-flow-normal/test_break_flow_graph && ./build-flow-normal/test_break_flow_serial
```

预期：往返和所有损坏输入用例通过。

- [ ] **Step 5: 引用/范围防护变异并恢复**

分别临时跳过 target 存在检查和 delay 下界检查；对应测试必须 RED。每次恢复后跑 GREEN，记录证据。

- [ ] **Step 6: 提交**

```bash
git add engine/src/kernel/break_flow* engine/tests/test_break_flow_serial.c engine/CMakeLists.txt
git commit -m "flow: add validated versioned serialization"
```

---

### Task 3: LogicThread 原子实体动作批次

**Files:**
- Create: `engine/src/kernel/break_kernel_flow.c`, `engine/tests/test_break_kernel_flow.c`
- Modify: `engine/src/kernel/break_kernel.h`, `engine/CMakeLists.txt`

**Interfaces:**
- Produces: `BreakKernelEntityAction`（SET_POSITION/INVENTORY_ADD）和 `BreakKernelError break_kernel_entity_actions_apply(BreakKernel *, const BreakKernelEntityAction *, u32 count)`。
- Consumes: `break_kernel_actor_slot`、物品定义、已有 position component 和 owner 检查。

- [ ] **Step 1: 写真实 World 原子性测试**

生成 actor、定义堆叠上限 10 的物品；批次先 SET_POSITION，再 INVENTORY_ADD 11。断言返回 `OVERLOAD`，position 仍逐位等于原值、背包为 0。随后合法批次同时改变两者。加入同 actor/item 两个动作聚合超限、stale generation、NaN 坐标、未定义物品和非 owner 拒绝。

- [ ] **Step 2: 确认 RED**

将 `flow` 加入既有 application test foreach 后：

```bash
cmake --build build-flow-normal --target test_break_kernel_flow -j3
./build-flow-normal/test_break_kernel_flow
```

预期：缺少新 API 或原子断言失败。

- [ ] **Step 3: 实现全量预校验后提交**

第二遍扫描累加同一 actor slot/item 的先前增量，使用 `u64` 计算最终数量。只有全部动作通过后才写 position/inventory：

```c
u64 total = (u64)application->inventories[slot * stride + item];
for (u32 k = 0; k < i; ++k) {
    if (same_actor_and_item(actions, k, i)) total += actions[k].count;
}
total += actions[i].count;
if (total > application->items[item].stack_limit) return BREAK_KERNEL_OVERLOAD;
```

提交阶段仅做已无失败路径的 `memcpy` 和整数写，不调用可能中途失败的新分配。

- [ ] **Step 4: GREEN 与既有 application 回归**

```bash
cmake --build build-flow-normal --target test_break_kernel_flow test_break_kernel_items test_break_kernel_actor -j3
ctest --test-dir build-flow-normal -R 'test_break_kernel_(flow|items|actor)$' --output-on-failure
```

预期：三项目标全部通过。

- [ ] **Step 5: 原子性变异并恢复**

临时改为逐动作直接提交，原子性测试必须因 position 已改变而 RED；恢复后重跑 GREEN。

- [ ] **Step 6: 提交**

```bash
git add engine/src/kernel/break_kernel* engine/tests/test_break_kernel_flow.c engine/CMakeLists.txt
git commit -m "application: add atomic entity action batches"
```

---

### Task 4: 数学、比较、事件与顺序执行

**Files:**
- Create: `engine/src/kernel/break_flow_runtime.c`, `engine/tests/test_break_flow_runtime.c`
- Modify: `engine/src/kernel/break_flow.h`, `engine/src/kernel/break_flow_internal.h`, `engine/CMakeLists.txt`

**Interfaces:**
- Produces: `BreakFlowRuntime`, `break_flow_runtime_create/destroy/reset/post/tick`, `break_flow_runtime_pending_count`, `break_flow_runtime_now_tick`。
- Consumes: Task 1 端口图、Task 3 原子动作批次。

- [ ] **Step 1: 写数学/比较/分支和事件值测试**

构造 `EVENT -> SEQUENCE -> BRANCH -> ENTITY_SET_POSITION`，以 event value 和常量输入比较；Then0/Then1 各写不同位置或物品。直接运行真实 `post`/`tick`，断言位置与物品，而不是调用内部求值函数。覆盖加减乘除、除零无动作、重复 post 的 FIFO 顺序和 revision 未 reset 时 `REJECTED`。

- [ ] **Step 2: 确认 RED**

```bash
cmake --build build-flow-normal --target test_break_flow_runtime -j3
./build-flow-normal/test_break_flow_runtime
```

预期：缺少运行时或执行结果未产生。

- [ ] **Step 3: 实现固定队列和数值拉取求值**

队列创建时分配，post 追加 `{due_tick, sequence, target, context}`；每轮扫描最小 `(due_tick, sequence)`。数值输入沿 VALUE 边递归求值，EVENT_VALUE 只接受当前上下文的事件节点。每帧结束一次调用原子动作批次。

- [ ] **Step 4: GREEN**

```bash
cmake --build build-flow-normal --target test_break_flow_runtime -j3
./build-flow-normal/test_break_flow_runtime
```

预期：所有数学/比较/顺序/真实动作测试通过。

- [ ] **Step 5: 提交**

```bash
git add engine/src/kernel/break_flow* engine/tests/test_break_flow_runtime.c engine/CMakeLists.txt
git commit -m "flow: execute events math and entity actions"
```

---

### Task 5: 延迟、预算、失败回滚与线程防护

**Files:**
- Modify: `engine/src/kernel/break_flow_runtime.c`, `engine/src/kernel/break_flow.h`
- Modify: `engine/tests/test_break_flow_runtime.c`

**Interfaces:**
- Produces: `BreakFlowRuntimeConfig {u32 max_events, max_actions, node_budget}`、`BREAK_FLOW_TIMEOUT` 的跨帧继续语义、owner `REJECTED`。

- [ ] **Step 1: 添加延迟/预算/原子失败测试**

测试 delay=2 时前两次 tick 不动作、第三次到期；预算=2 时每帧最多两个节点/纯值求值步骤且动作最终跨三帧完成。构造合法 SET_POSITION 后接 ADD_ITEM 聚合溢出，断言 tick 返回错误、队列/sequence/tick 与起始相同、World 不变。用 `platform_thread` 在另一线程调用 post/tick/reset 并断言 `REJECTED`。

- [ ] **Step 2: 运行确认 RED**

```bash
cmake --build build-flow-normal --target test_break_flow_runtime -j3
./build-flow-normal/test_break_flow_runtime
```

预期：新增延迟、预算或回滚断言失败。

- [ ] **Step 3: 实现节点级与 tick 级快照**

tick 起点复制队列到预分配 backup；当前项先按值复制并出队以释放容量，节点内新增项只追加到尾部。预算停止时按保存的交换位置恢复当前项、移除其新入队项并还原 `action_count`，因此当前项可重试且满容量队列也能推进。真正执行失败时恢复整个 tick 快照；预算停止则提交已完成前缀并保留余队。

- [ ] **Step 4: GREEN**

```bash
cmake --build build-flow-normal --target test_break_flow_runtime -j3
./build-flow-normal/test_break_flow_runtime
```

预期：延迟、逐帧预算、失败原子和跨线程拒绝全部通过。

- [ ] **Step 5: 预算变异并恢复**

临时忽略 `node_budget` 比较，预算测试必须 RED；恢复后重跑 GREEN。

- [ ] **Step 6: 提交**

```bash
git add engine/src/kernel/break_flow* engine/tests/test_break_flow_runtime.c
git commit -m "flow: bound scheduling and roll back failures"
```

---

### Task 6: BreakEditorDoc 图命令与 undo/redo

**Files:**
- Create: `engine/src/editor/editor_flow.h`, `engine/src/editor/editor_flow.c`, `engine/tests/test_editor_flow.c`
- Modify: `engine/src/editor/editor_doc.c`, `engine/src/editor/editor_internal.h`, `engine/src/editor/editor_doc.h`, `engine/CMakeLists.txt`

**Interfaces:**
- Produces: `break_editor_doc_flow_graph`, `break_editor_flow_add_node/remove_node/set_node/connect/disconnect`。
- Consumes: Task 2 序列化、`break_editor_cmd_stack_push_applied`、现有 `break_editor_undo/redo`。

- [ ] **Step 1: 写命令栈失败测试**

通过公开编辑 API 添加 Event/Sequence、连接、改属性、删除；每步检查 stack undo count。逐次 undo 比较图节点/连接/next-id，再 redo 比较完全相同。非法连接和非法属性不得增加 stack revision。reset 后图为空且历史清空。

- [ ] **Step 2: 确认 RED**

```bash
cmake --build build-flow-normal --target test_editor_flow -j3
./build-flow-normal/test_editor_flow
```

预期：缺少图文档 API 或 undo 行为断言失败。

- [ ] **Step 3: 实现前后字节命令**

命令构造依次序列化 before、反序列化克隆、在克隆上执行一个操作、序列化 after；apply 先反序列化目标字节到新图，成功后才交换 `doc->flow_graph`。析构释放两段固定上限字节。doc create/destroy/reset 补齐图生命周期，任何分配失败保持旧文档不变。

- [ ] **Step 4: GREEN 与编辑器核心回归**

```bash
cmake --build build-flow-normal --target test_editor_flow test_editor_doc test_editor_cmd -j3
ctest --test-dir build-flow-normal -R 'test_editor_(flow|doc|cmd)$' --output-on-failure
```

预期：新旧测试全部通过。

- [ ] **Step 5: 提交**

```bash
git add engine/src/editor engine/tests/test_editor_flow.c engine/CMakeLists.txt
git commit -m "editor: make flow graph edits undoable"
```

---

### Task 7: myui Flow 节点列表、连接和属性编辑

**Files:**
- Create: `engine/apps/editor/editor_panel_flow.c`
- Modify: `engine/apps/editor/editor_shell_internal.h`, `engine/apps/editor/editor_panels.c`, `engine/apps/editor/editor_panels.h`
- Modify: `engine/tests/test_editor_shell.c`, `engine/CMakeLists.txt`

**Interfaces:**
- Consumes: Task 6 编辑 API 与现有 `editor_shell_refresh_all`。
- Produces: 底部 tab index 2 的 `editor-flow-panel`，稳定 widget 名称 `editor-flow-add-event`, `editor-flow-add-sequence`, `editor-flow-delete`, `editor-flow-name`, `editor-flow-connect`, `editor-flow-disconnect` 及连接输入字段。

- [ ] **Step 1: 写真实 widget emitter 失败测试**

沿用 `test_editor_shell.c` 的 `find`、`emit_click`、`emit_activate`：点击 Add Event/Add Sequence，设置名称并 activate，填写 `1,1 -> 2,0` EXEC 后点击 Connect；断言图有两节点一连接且 undo count 增加。执行 `break_editor_undo/redo` 后面板行文本和图同步；非法端口点击不产生命令。

- [ ] **Step 2: 确认 RED**

```bash
cmake --build build-flow-normal --target test_editor_shell -j3
./build-flow-normal/test_editor_shell
```

预期：找不到 Flow widgets 或图未变化。

- [ ] **Step 3: 实现有界 myui 面板**

使用 `my_list_view` 固定快照行、`my_button`、`my_edit` 和 linear layouter。按钮回调只调用 `break_editor_flow_*`，不直接改图或 World。选择/草稿文本是 view state；所有图修改后刷新列表和共享状态。将 Flow 源文件加入 production editor 与 headless shell 两套 target。

- [ ] **Step 4: GREEN 与 shell 全回归**

```bash
cmake --build build-flow-normal --target editor test_editor_shell -j3
./build-flow-normal/test_editor_shell
```

预期：包括 Flow emitter 用例在内的 shell 测试全部通过。

- [ ] **Step 5: 提交**

```bash
git add engine/apps/editor engine/tests/test_editor_shell.c engine/CMakeLists.txt
git commit -m "editor: add myui flow graph panel"
```

---

### Task 8: 三构建验证、审查与交付

**Files:**
- Create: `.superpowers/sdd/flow-graph-report.md`
- Modify: 仅审查确认属于本项目的文件

- [ ] **Step 1: normal focused 全回归**

```bash
cmake --build build-flow-normal -j3
ctest --test-dir build-flow-normal -R 'break_flow|break_kernel|editor_(flow|doc|cmd|shell)$' --output-on-failure
```

预期：所有选中测试通过；构建只使用 `-j3`。

- [ ] **Step 2: ASan+UBSan focused**

```bash
cmake -S engine -B build-flow-asan -DENGINE_RHI_BACKEND=opengl -DBREAK_ENABLE_CRYPTO=OFF -DENGINE_USE_ASAN=ON -DENGINE_USE_UBSAN=ON
cmake --build build-flow-asan --target test_break_flow_graph test_break_flow_serial test_break_flow_runtime test_break_kernel_flow test_editor_flow test_editor_shell -j3
ASAN_OPTIONS=detect_leaks=1 UBSAN_OPTIONS=halt_on_error=1 ctest --test-dir build-flow-asan -R 'break_flow|break_kernel_flow|editor_(flow|shell)$' --output-on-failure
```

预期：无 sanitizer 报告且全部通过。

- [ ] **Step 3: TSan focused**

```bash
cmake -S engine -B build-flow-tsan -DENGINE_RHI_BACKEND=opengl -DBREAK_ENABLE_CRYPTO=OFF -DENGINE_USE_TSAN=ON
cmake --build build-flow-tsan --target test_break_flow_runtime test_break_kernel_flow test_editor_flow -j3
TSAN_OPTIONS=halt_on_error=1 ctest --test-dir build-flow-tsan -R 'break_flow_runtime|break_kernel_flow|editor_flow$' --output-on-failure
```

预期：跨线程拒绝探针运行，无竞态报告且全部通过。

- [ ] **Step 4: 只读审查并修复**

派只读 reviewer 检查正确性、安全、原子性、固定容量、撤销语义和 target 边界；若当前工具无 Agent，则明确记录该限制并用独立 fresh-eyes 源码审查清单代替，不谎称已派 Agent。Critical/Important 修复必须新增或重跑相应 RED/GREEN。

- [ ] **Step 5: 最终检查与报告**

```bash
git diff --check
git status --short
```

报告列出设计/计划、每项 RED/GREEN、变异证据、三种构建命令与结果、测试清单、reviewer 发现及修复、提交 hash、未验证的真实 GUI/跨平台边界。

- [ ] **Step 6: 提交全部改动**

```bash
git add .superpowers/sdd/flow-graph-report.md
git commit -m "docs: record flow graph verification"
git status --short --branch
```

预期：工作树无未提交源文件；最终只报告实际运行过的验证。
