# P2 Flow Graph 交付与 fix round 1 报告

日期：2026-11-03
分支：`cry-wave1-flow-ai`
基线：`48e64a2a`；fix round 1 起点：`7a7964cf`

## 1. 状态

P2 与 reviewer agent-181 的 fix round 1 已完成。Flow Graph 是独立 C11 生产实现，不是 `rule_engine` 改名或接口桩。运行时、版本化序列化、实体原子动作、编辑器命令和真实 myui 控件均已接线。未 push、未创建 PR、未修改 master 或其他 P 子项目。

本报告随 fix round 1 一并提交。

## 2. 已交付行为

- 固定容量图：节点硬上限 256、连接硬上限 1024；id 单调且删除后不复用；显式 EXEC/VALUE 端口、引用与端口模式检查。
- EVENT、加减乘除、LESS/EQUAL/GREATER、SET_POSITION、ADD_ITEM、DELAY、SEQUENCE、BRANCH。
- 全图环检测；失败不消耗 id、不改变计数或 revision；零配置逐字段使用硬容量默认值。
- 固定事件队列按 `(due_tick, sequence)` 确定性调度；延迟、顺序分支、事件来源上下文和 revision reset。
- 节点执行与纯数值求值共享每帧预算；`TIMEOUT` 保留可继续状态；满容量队列也能推进。
- tick 级失败原子：队列、sequence、tick 恢复；动作只在帧尾提交，失败不留下 World 修改。
- `break_game_entity_actions_apply` 对位置与背包批次进行 owner、generation、组件、有限值、物品和聚合堆叠预校验，再一次提交。
- `BREAKFG` v1 小端序列化：精确长度、版本、容量、next-id、名称、枚举、有限浮点、实体范围、引用、端口、环校验；解码只返回完整图。
- `BreakEditorDoc` 持有图；公开编辑 API 生成带前后验证字节的现有命令栈命令，undo/redo 恢复节点、连接、属性及 next-id。
- myui 底部 Flow 页是真实节点列表：行选择、Add Event/Add Sequence/Delete、名称/event key/item id/delay/a/b/c/entity 属性编辑、显式端口连接与断开。
- 面板随 command-stack revision 和图实例刷新；new/reset 不留旧行；Flow tab index 2 可持久化；列表具有稳定 `editor-flow-list` widget 名称。
- 真实消费者：编辑器中的图直接交给 `BreakFlowRuntime`，通过 post/tick 改变实际 ECS actor 位置。
- `break_flow` 未链入 `engine`、`engine_demo` 或 `dxx_break`；运行 tick 不分配内存。

## 3. Reviewer agent-181 逐项处理

### Important 1 — queue/rollback 覆盖

新增 `engine/tests/test_break_flow_runtime.c` 覆盖：

- `delay_continuations_preserve_fifo_with_following_events`：同一 event key 的合法值 1、2、3，验证 delay continuation 与后续事件顺序、pending 和 tick。
- `failed_sequence_restores_sequence_and_retry_has_no_duplicates_or_loss`：首次动作提交因堆叠失败，恢复两个原始事件及 next_sequence；释放容量后追加第三事件并重试，最终背包恰好增加三次且位置按 FIFO 为 3。
- `invalid_event_value_source_rolls_back_entire_tick`：EVENT_VALUE 来自非当前事件，前置 ADD_ITEM 与位置均不提交，队列、tick、next_sequence 恢复。
- 新增只读 `break_flow_runtime_next_sequence`，直接观察回滚计数，不改变生产调度。

行为变异：

- 反转 sequence 比较：9/11，重试 FIFO 位置错误；恢复后 11/11（后续比较测试加入为 12/12）。
- 将两处 next_sequence 恢复值改为 `backup+1`：9/11，重试和错误来源用例均失败；恢复后通过。
- 允许任意事件作为 EVENT_VALUE 来源：10/11，错误来源被提交；恢复后通过。

### Important 2 — 容量、深度和恶意序列化

新增 `engine/tests/test_break_flow_graph.c`：

- `link_capacity_overflow_preserves_count_revision_and_next_id`：两条合法连接达到配置上限，第三条返回 OVERLOAD，输出 id、count、revision 和完整序列化字节（含 next-link-id）不变。
- `deepest_value_chain_validates_and_rejects_cycle_atomically`：256 个数学节点、255 条 VALUE 边通过全图验证；最深回边原子拒绝。
- 容量防护变异允许第三条连接：7/8，容量用例失败；恢复后 8/8。

扩充 `engine/tests/test_break_flow_serial.c`：

- header `link_count` 超硬上限与 `next_link_id` 回退均拒绝。
- 重复 link id、独立 source 悬空、独立 target 悬空、非法端口和环均返回 INVALID 且输出图为 NULL。
- 仅放宽重复 id 检查仍被最终计数校验拒绝；叠加跳过最终图校验后，重复 id 等恶意输入被错误接受，证明两层防护均有效。恢复后 6/6，ASan 下无临时图泄漏。

### Minor 1 — 零配置真实缺陷

`break_flow_graph_create` 原先整体覆盖配置后拒绝零字段，违背设计默认值合同。

- RED：`zero_config_fields_use_independent_defaults` 中 `{0,0}` 返回 NULL，图测试 5/6。
- 修复：`max_nodes==0` 与 `max_links==0` 分别在范围检查前替换为各自硬上限。
- GREEN：`{0,0}`、`{0,1}`、`{1,0}` 均创建成功；超硬上限仍返回 NULL，6/6（最终图测试 8/8）。

### Minor 2 — 比较与真实 UI 属性 emitter

`equal_and_greater_comparisons_cover_true_and_false_branches` 覆盖：

- EQUAL 的 true/false；GREATER 的 true/false；均执行真实分支并修改 actor 位置。
- 将 EQUAL 改为 `!=`、GREATER 改为 `<` 后 11/12；恢复后 12/12。

`flow_panel_delay_and_action_properties_emit_undo_and_redo` 覆盖：

- 通过编辑命令创建 Delay/Action 后，对真实节点行发送 click。
- 对 `editor-flow-delay/a/b/c/entity` 发送真实 activate，验证图字段和命令数。
- delay 2→5、a 0→7、b 0→8、c 0→9、entity 12:34→56:78；每项 undo/redo 均恢复正确字段，最终 7 个命令。
- 初次 RED 是列表缺少稳定 widget 名称，已补 `editor-flow-list`；修复后 147/147。
- entity 回调行为变异不再写回字段时 146/147；恢复后 147/147。

## 4. 既有 TDD 与变异证据摘要

首轮实现已保留真实 RED→GREEN 记录：图 0/5→5/5、序列化 0/5→后续 6/6、实体动作 0/4→4/4、运行时 0/8→后续 12/12、编辑器图命令 0/3→3/3、myui 初始 145/146→后续 147/147。

关键变异还包括：

- DFS 接受回边会使环测试失败。
- 跳过序列化最终图校验会使 next-id、引用、范围等损坏输入被接受。
- 预校验阶段提前写 position 会破坏实体动作原子性并被测试捕获。
- 移除实际预算判断会使预算用例失败；一个轻微 `>`/`>=` 变异曾存活，未伪称杀伤。
- reset 列表残留、Flow 设置丢失和非法实体 index 均先 RED 后修复。

## 5. 最终构建与输出

所有构建均使用 `-j3`，目录均在本工作树。

### normal

```bash
cmake --build build-flow-normal --target editor \
  test_break_flow_graph test_break_flow_serial test_break_flow_runtime \
  test_break_game_flow test_editor_flow test_editor_shell test_editor_settings -j3
ctest --test-dir build-flow-normal \
  -R 'break_flow|break_game|editor_(flow|doc|cmd|shell|settings|i18n)$|test_break_editor_target_contract$' \
  --output-on-failure
```

结果：19/19 CTest，0 失败；`test_editor_shell` 内 147/147；production `editor` 构建成功。

### ASan + UBSan

```bash
cmake --build build-flow-asan --target \
  test_break_flow_graph test_break_flow_serial test_break_flow_runtime \
  test_break_game_flow test_editor_flow test_editor_shell test_editor_settings -j3
ASAN_OPTIONS=detect_leaks=1 UBSAN_OPTIONS=halt_on_error=1 \
  ctest --test-dir build-flow-asan \
  -R 'break_flow|break_game_flow|editor_(flow|shell|settings)$' \
  --output-on-failure
```

结果：7/7 CTest，0 失败；无 ASan、LeakSanitizer 或 UBSan 报告。

### TSan

```bash
cmake --build build-flow-tsan --target \
  test_break_flow_runtime test_break_game_flow test_editor_flow -j3
TSAN_OPTIONS=halt_on_error=1 ctest --test-dir build-flow-tsan \
  -R 'break_flow_runtime|break_game_flow|editor_flow$' --output-on-failure
```

结果：3/3 CTest，0 失败；无 TSan 报告。实际执行 runtime post/tick/reset 和 game action 的跨线程拒绝探针。

### 文本与状态

最终提交前执行 `git diff --check`，无错误。提交后工作树干净。

## 6. 文件范围

fix round 1 修改：

- `engine/src/game/break_flow_graph.c`：逐字段零配置默认值。
- `engine/src/game/break_flow.h`：只读 next_sequence 诊断。
- `engine/src/game/break_flow_runtime.c`：诊断实现。
- `engine/apps/editor/editor_panel_flow.c`：列表稳定 widget 名称。
- `engine/tests/test_break_flow_graph.c`
- `engine/tests/test_break_flow_serial.c`
- `engine/tests/test_break_flow_runtime.c`
- `engine/tests/test_editor_shell.c`
- `.superpowers/sdd/flow-graph-report.md`

首轮主要实现仍位于：

- `engine/src/game/break_flow*`
- `engine/src/game/break_game_flow.c`
- `engine/src/editor/editor_flow.*`
- `engine/apps/editor/editor_panel_flow.c`
- `docs/design/flow_graph.md`
- `docs/superpowers/plans/2026-11-02-flow-graph.md`

## 7. 提交历史

- `01154dbe` docs: design bounded flow graph runtime and editing
- `4c963f9d` docs: plan test driven flow graph implementation
- `b49f0038` flow: add bounded graph with explicit ports
- `4b7c2fbd` flow: add validated versioned serialization
- `33a4e628` game: add atomic entity action batches
- `559bcb7e` flow: execute bounded deterministic graphs
- `043a7682` editor: make flow graph edits undoable
- `04ddef3b` editor: add myui flow graph panel
- `6e426e65` flow: harden editor state and entity bounds
- `7a7964cf` docs: align flow graph design with verified behavior
- fix round 1：本报告所在 HEAD 提交。

## 8. 审查与限制

- agent-181 的审查为静态独立审查；本 round 的构建和测试由本执行代理运行。没有声称 reviewer 重跑了这些测试。
- 未打开真实桌面窗口、未做 GPU/人工视觉检查；myui 证据来自 production 控件代码的 dummy-PAL 真实 widget emitter 和 headless shell。
- 采用真实节点列表，不是自由拖拽坐标画布；端口通过数值字段显式编辑。
- 未运行 Windows/macOS/移动平台或交叉编译；仅在当前 Linux/GCC 环境验证。
- Flow 二进制读写由公开 API 提供；没有新增 UI 文件对话框，也没有改变 BSCN。scene load 不声称加载 Flow 侧车。
- 编辑后已有 runtime 必须按公开合同 reset；编辑器替换图指针时，借用旧指针的调用方也必须重新获取/重建。
