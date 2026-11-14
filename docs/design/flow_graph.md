# Flow Graph 运行时、序列化与编辑设计

日期：2026-11-02
子项目：P2（`cry-wave1-flow-ai`）

## 1. 目标与边界

交付一个真正可执行的 C11 Flow Graph，而不是重命名 `rule_engine`。图包含有界稳定节点 id、显式端口、事件、数学/比较、实体动作、延迟、顺序/条件分支、环检测、每帧节点预算和确定性事件队列。版本化二进制序列化拒绝损坏的长度、引用、类型和范围。编辑器使用现有 myui 列表与输入控件编辑节点、连接和属性，所有修改进入 `BreakEditorDoc` 已有的 undo/redo 命令栈。

不实现通用脚本语言、不引入新 UI 框架、不把 Flow Graph 链入 `engine`、`engine_demo` 或 `dxx_break`。本设计采用整数 tick 延迟，不用墙钟时间；LogicThread 独占运行时可变状态和实体动作。

## 2. 方案取舍

### 采用：独立图资产 + 有界运行时 + 原子实体动作批次

`break_flow` 分为图资产与运行时。资产只保存节点、连接和稳定 id；运行时借用资产和 `BreakKernel`，创建时预分配事件队列、动作批次及快照。实体动作先暂存，在 tick 末尾由 `break_kernel` 一次校验并提交。这样图求值失败或动作失败不会留下半个 tick 的世界修改。

### 备选：节点回调直接修改 World

优点是节点种类容易扩展，缺点是任意回调无法在失败时回滚，并会把 `World` 指针泄漏到图资产/编辑器边界，故不采用。

### 备选：把规则引擎扩展成 Flow Graph

可复用部分匹配代码，但规则匹配的事实/规则语义与显式端口、执行流、延迟事件不同，容易形成同名异义模块，故不采用。

## 3. 图数据模型

硬上限为 256 个节点、1024 条连接；创建时可选择更小容量，零值使用默认值。节点和连接数组在创建时分配，运行 tick 不分配内存。

节点 id 与连接 id 从 1 单调分配，删除后不在该图生命周期内复用；序列化保存 next-id，加载及 undo/redo 后仍保持身份稳定。公开读取按 id 升序，迭代顺序不依赖哈希或指针。

节点类型：

- `EVENT`：由数值 event key 触发，输出执行端口和事件数值端口；同一图中 event key 唯一。
- `MATH_ADD/SUBTRACT/MULTIPLY/DIVIDE`：两个数值输入、一个数值输出；未连接输入使用节点属性默认值。除零及非有限结果报错。
- `COMPARE_LESS/EQUAL/GREATER`：两个数值输入，输出 0 或 1。
- `ENTITY_SET_POSITION`：目标为带 generation 的 `Entity`，XYZ 可连接数值输入，未连接时使用节点属性。
- `ENTITY_ADD_ITEM`：目标 `Entity` 与 item id 为属性，数量可连接数值输入；数量必须为有限正整数且在物品范围内。
- `DELAY`：保存 1..65535 tick 的延迟，到期后继续执行并保留事件上下文。
- `SEQUENCE`：两个显式执行输出，按 Then0、Then1 顺序入队。
- `BRANCH`：按数值条件是否非零选择 True/False 执行输出。

每个连接显式记录 `{id, kind, source_node, source_port, target_node, target_port}`。`kind` 为 EXEC 或 VALUE，端口模式由节点类型和端口号决定；创建连接时同时验证两端方向、类型、节点存在性和范围。每个 VALUE 输入最多一条入边，每个 EXEC 输出最多一条出边；VALUE 输出可扇出。

添加连接后对所有 EXEC/VALUE 边做三色 DFS；若出现环，新增连接回滚，图及 next-id 不变。节点属性更新若改变类型，先验证所有既有连接仍满足端口模式，失败时保留旧节点。删除节点级联删除其连接，作为一个图修订。

## 4. 运行时与确定性

`BreakFlowRuntime` 记录创建线程为 owner；非 owner 的 post/tick/reset 返回 `REJECTED`。图资产带 revision，图被编辑后旧运行时拒绝 tick，必须 `reset` 清除队列并重新绑定 revision，避免延迟项指向已删除或改义节点。

外部 `post(event_key, entity, value)` 只负责有界入队。队列项含目标节点、到期 tick、单调 sequence、事件上下文和 delay-resume 标记。每轮选择 `(due_tick, sequence)` 最小项，不依赖数组交换顺序。事件 key 不存在、队列满、容量超界均明确报错且不静默截断。

每次 `tick` 处理当前到期项，随后 tick 计数加一。节点执行和纯数值节点求值都消耗同一个每帧预算；预算耗尽返回 `TIMEOUT`，当前尚未完成的节点及其新入队项/暂存动作不提交，已完成前缀保留到下一帧继续。正常耗尽到期队列返回 `OK`。

事件、顺序分支及延迟 continuation 共用此队列，因此相同图、输入调用顺序和预算产生相同动作与顺序。延迟至少跨一个 tick，不允许零延迟形成即时递归。

## 5. 失败原子与实体动作

运行时在 tick 起点备份固定队列、sequence 和 tick。节点执行期间，实体动作只写入固定容量动作批次。发生无效数值、引用失效、队列溢出或实体提交失败时，恢复 tick 起点运行时状态；由于实体动作尚未提交，World 保持不变。

`break_kernel_entity_actions_apply` 接收有界 `SET_POSITION` / `INVENTORY_ADD` 批次。它先验证 owner、所有 generation 句柄、位置组件、有限坐标、物品定义、正整数数量及同 actor/item 的聚合堆叠上限，再一次写入。任一动作失败则整批不修改。该入口也可被其他 LogicThread 消费者直接调用，并有独立测试。

预算耗尽不是执行失败：已完成动作前缀在帧尾提交，未完成节点仍留在队列。动作提交只在节点处理结束或预算停止时发生一次。

## 6. 版本化安全序列化

格式为小端、显式逐字段编码的 `BREAKFG` v1，不把 C 结构体内存直接写盘。固定头包含版本、头长、总长度、节点/连接容量与数量、next-node-id、next-link-id；节点记录包含显式 id、类型、名称长度与字节、event key、Entity index/generation、item id、delay 和 IEEE-754 属性位；连接记录包含全部显式端口字段。

解析先验证最小/精确总长度、乘法溢出和硬上限，再逐记录验证名称可打印且 NUL 规则明确、枚举/有限浮点/delay/item/entity 范围、id 严格递增、next-id 大于所有使用 id，以及连接端口和引用。最后再次执行全图验证与环检测。未知版本、截断、尾随字节、重复/越界 id、悬空引用、非法端口和环均失败；输出图只在完整成功后返回，调用方原图不受影响。序列化提供所需长度查询和容量不足无修改错误。

## 7. 编辑器与 myui

`BreakEditorDoc` 持有一份默认容量的 Flow Graph 资产。新增 `editor_flow.h/.c` 提供节点增删改、连接/断开 API。每个操作先在克隆图上执行并重新验证，再生成一个包含修改前后版本化图字节的命令；apply/revert 通过完整校验的反序列化构造新图，成功后一次交换指针，失败保持原图和命令游标不变。该快照命令只用于图编辑，既有实体命令机制不变；它保证删除/恢复、next-id 和复杂连接完全一致。图指针为借用指针，undo/redo/reset 后需重新获取。

myui 新增底部 `Flow` 标签页，采用有界节点列表而非另造画布：

- 节点行显示稳定 id、类型和名称；点击选择。
- Add Event / Add Sequence / Delete 按钮修改图。
- 名称与常用属性通过 `my_edit` 的 activate 提交；非法输入不产生命令。
- source node/port、target node/port 与 EXEC/VALUE 选择通过有界数值输入建立连接；按连接 id 断开。
- 列表和状态随命令栈 revision 与图实例身份刷新，new/reset 替换图时不留旧行；Ctrl+Z/Y 继续走现有全局 undo/redo。
- Flow 是底部 tab index 2，设置解析与序列化持久化该页；连接草稿只在 Connect/Disconnect 时提交命令。

headless dummy-PAL 测试直接对真实 widget emitter 发送 click/activate，验证 UI → 图修改 → undo → redo，而不是只测试面板辅助函数。

## 8. 测试与变异证据

先写目标行为测试并记录真实 RED，再实现 GREEN：

1. 图 id/容量/端口/环检测及失败原子。
2. 数学、比较、事件值、顺序与条件分支、真实位置/背包动作。
3. 延迟、确定性队列、预算跨帧继续、revision/owner 防护。
4. 动作批次中途失败时 World 与队列不变。
5. 序列化往返及版本、截断、尾随、长度、名称、引用、范围、环等损坏输入。
6. 编辑器命令增删改/连接 undo/redo 和真实 myui emitter 路径。

关键变异至少覆盖：关闭环检测必须使环测试变红；忽略每帧预算必须使预算测试变红；放宽序列化引用/范围检查必须使对应损坏输入测试变红；实体批次缺少预校验必须使原子性测试变红。每个变异完成后立即恢复生产源码并重跑正常测试。

focused normal、ASan+UBSan、TSan 均使用 `-j3` 构建并运行 Flow/Application/Editor 测试；TSan 另跑跨线程拒绝探针。最终运行相关既有回归、`git diff --check`，并进行只读代码审查。未执行的真实 GPU 交互、人工视觉检查和跨平台设备验证不作为已完成证据。

2026-11-10 跨平台补充：MSVC `/W4 /WX` 不接受测试直接对 `position(&f)` 返回对象的数组成员做下标（C4223）。测试现通过 `position_x()` 内的命名 `Vec3` lvalue 读取 `e[0]`，保持 12 项运行时行为与全部数值断言不变；Flow 生产代码和公共 API 未改。Linux 上 MSVC 兼容 Clang AST 合同及 clang-cl 语法检查只作本地证据，native MSVC 仍由后续 CI 验证。

## 9. 生命周期与保存边界

Flow Graph 的二进制序列化是独立侧车格式；本轮不暗中改变 BSCN 格式。`BreakEditorDoc` 的 new/reset 会重置图，现有 scene load 不声称加载 Flow 侧车。编辑器 UI 提供图内编辑与 undo；磁盘读写由调用方使用公开序列化 API 完成。运行时 reset 会清空待处理事件，调用方必须在编辑资产后显式执行。
