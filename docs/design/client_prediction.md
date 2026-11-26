# 客户端预测与服务端校正（`break_prediction`）

状态：2026-11-27 交付第一块。`missing_capabilities.md` 对账列表把「预测与回滚」列为未实现。本文件交付其中与传输无关的核心：一个纯 C、确定性的预测器，负责在客户端立即应用本地输入，并在服务端快照到达时回滚和重放。不包含传输、序列化、确认协议，也没有接入 World 或 `core_app`。

源码：`engine/src/network/break_prediction.{h,c}`。测试：`engine/tests/test_break_prediction.c`（14 例）。

## 1. 模型

- 状态和输入都是调用方定义的定长字节块。调用方提供 `step(user, state, input, out_state)`，推进一个 tick。它必须是确定性的，并且写满 `out_state` 的每个字节，因为状态比较用的是 `memcmp`，结构体的填充字节也要写。
- 预测器从一个已确认的 `(tick, state)` 开始。`apply_input(tick, input)` 只接受下一个 tick（`predicted_tick + 1`），立即在预测状态上运行 `step`，并保留这个输入，直到某个快照覆盖它。
- 服务端始终是权威。`reconcile(tick, state)` 收到服务端在某个 tick 之后的真实状态，按以下规则处理：
  - `tick` 小于已确认的 tick：返回 STALE，什么都不变。快照迟到或乱序都走这条路径。
  - `tick` 在已确认 tick 和最新预测 tick 之间（含两端）：丢掉该快照覆盖的输入，把快照和客户端当时对该 tick 的预测逐字节比较。相同就不重算；不同则回滚到快照，用客户端自己的 `step` 重放剩余输入。重复收到已确认 tick 的快照也按这条规则处理，因此服务端可以对同一 tick 再次纠正。
  - `tick` 超过最新预测 tick：说明服务端运行了客户端没有输入的 tick，这是一次 resync，丢弃所有待确认输入，从快照处继续预测。

## 2. 存储与失败语义

- 待确认输入放在大小为 `capacity` 的环形缓冲区里，每个输入旁边存着运行它之后的预测状态，所以判断是否预测错误不需要重算。预测状态就是最新输入那一格的状态，没有待确认输入时就是已确认状态。
- 重放先写入同样大小的 scratch 环，所有 `step` 都成功后才拷回。任何一次 `step` 返回 false，`apply_input` 或 `reconcile` 都返回 FAILED，预测器保持调用前的状态，同一快照之后还可以重试。
- 内存为 `2 * capacity * state_size + capacity * input_size + state_size`，在 `create` 时一次分配。上限：状态 16 KiB、输入 4 KiB、容量 1024，最大约 36 MiB。
- 环满（`capacity` 个输入都在等确认）时 `apply_input` 返回 FULL，不改变任何东西。调用方应该降低输入频率，或者等确认。
- `pending_input(i)` 按从旧到新的顺序列出待确认输入及其 tick，供调用方重发服务端可能没收到的输入。
- 统计：接受的输入、接受的快照、回滚次数、resync 次数、重放输入总数、STALE 次数。

单线程拥有者，不加锁，与仓库其他网络构件一致。

## 3. 测试与变异

14 例，先以未定义函数链接失败为 RED：
- 输入立即生效；快照与预测一致时只丢弃已覆盖输入、不调用 `step`。
- 预测错误时回滚并重放，重放使用客户端自己的规则；快照正好是最新 tick 时不重放、直接采用服务端状态。
- 快照超过预测（含恰好多一个 tick）时 resync；旧快照 STALE 且不改变任何东西；重复的已确认 tick 作为纠正接受。
- tick 必须连续、容量限制与环回绕、待确认输入按顺序列出。
- 失败的 `step` 不改变预测器，修好后同一快照可以重放成功。
- 参数校验和上限值可用；初始状态被拷贝。
- 只有最后一个字节不同也算预测错误。
- 随机性质测试：400 个 tick，服务端随机加阻力，快照随机迟到、乱序、重复。每一步都检查「预测状态 = 已确认快照 + 客户端重放」，最后一个快照之后双方逐字节一致。

32 项变异判红。首轮 3 项存活：resync 边界差一、resync 时 head 不归零、只比较前 `state_size - 1` 个字节。补「恰好多一个 tick 的 resync」和「最后一个字节不同」两例后都判红。

验证：normal / ASan+UBSan（含 leak 检测）/ TSan 下 14/14；Windows 实机 MSVC（`/W4 /WX`）14/14；`build-current-vk` 非 fuzz 全量 461/461，fuzz 23/23。

## 4. 未交付

- 发送通道：已交付。两种报文登记为 `break_net` 消息（第 7 节），服务端的会话层收发由 `break_prediction_session` 完成（第 8 节）。
- 接入 World/ECS：已交付到组件这一层。预测器可以绑定到 ECS World 中一个实体的一个组件，服务端也可以用同一个 step 推进权威组件（第 9 节）。还没有接到 `break_ecs_replication` 的快照/增量流和 `core_app`。
- 插值与平滑：其他实体的快照插值已由 `break_snapshot_interp` 交付（第 6 节）；本地实体在校正后的状态跳变仍立即生效，平滑留给表现层。
- 服务端的延迟补偿（回溯命中判定）：已由 `break_lag_compensation` 交付，见 `docs/design/lag_compensation.md`。

## 5. Wire 格式与服务端输入收件箱（`break_prediction_wire`）

源码：`engine/src/network/break_prediction_wire.{h,c}`。测试：`engine/tests/test_break_prediction_wire.c`（9 例）、`engine/tests/fuzz_prediction_wire.c`。

**输入批次**（客户端到服务端，小端）：`"BRPI"`、u8 版本 1、u8 数量（1..32）、u16 输入大小、u64 第一个 tick，然后是按 tick 从旧到新排列的输入。客户端每次发送最旧的至多 32 个待确认输入，所以丢一个报文没有代价，只要后面还有批次到达即可。发最旧的而不是最新的，是因为服务端必须按 tick 顺序应用，跳过缺口的输入反正用不上。

**快照**（服务端到客户端）：`"BRPS"`、u8 版本 1、三个保留字节（必须为 0）、u64 tick、u32 状态大小，然后是状态字节。tick 是服务端最后应用的输入 tick，客户端把它原样交给 `break_prediction_reconcile`。

**解码规则**：两种报文都是不可信输入。解码器只接受唯一一种编码，以下情况都返回 INVALID 并清零输出：
- 魔数或版本错误、保留字段非 0。
- 大小与接收方配置不一致。
- 数量为 0 或超过 32、第一个 tick 为 0 或最后一个 tick 会溢出。
- 缓冲区过短，或带有尾随字节。

解码出的指针指向输入缓冲区，不复制。

**服务端收件箱** `BreakPredictionInbox` 记录服务端期待的下一个 tick。`inbox_accept` 对批次中 tick 等于期待值的输入依次调用模拟的 `apply`。无论批次怎样乱序、重复或重叠，每个输入都恰好应用一次，并且按顺序。
- 批次从期待值之后开始（中间有缺口）：整批不应用，计入 `gaps`，等后续批次补上。
- `apply` 返回 false：停在该输入，返回 FAILED，下一次从这里继续。

**测试**：报文布局逐字节固定；批次往返并在待确认过多时发最旧的 32 个；容量不足时返回 FULL 并给出大小、不写字节；两种报文的逐截断（每个截断放进大小恰好的堆块）、尾随字节和每个字段的畸形值；收件箱的去重、重叠、缺口和 `apply` 拒绝。

端到端用例：一个会预测的客户端与一个带阻力（客户端不知道）的权威服务端，经过一个丢 30%、延迟 0..3 tick、会重复和乱序的信道运行 600 tick。检查以下几点：
- 服务端恰好按顺序应用 600 个输入，确实收到过重复批次。
- 客户端确实发生过预测错误，并且从未触发 resync。
- 信道排空后，客户端的预测状态与服务端逐字节一致。

**变异**：31 项。首轮 6 项存活：编码容量差一、数量上限、输入大小字段、快照大小字段、缺口判断差一、快照状态大小上限。补边界用例后都判红，第二轮又补了输入大小上限一例。1 项等价变异：`end <= next_tick` 改成 `<`，相等时走通用路径，结果同样是全部计为重复、不应用。

**fuzz**：`fuzz_prediction_wire`（smoke 种子 89，进 CI 三处 fuzz 构建列表）。种子取库自身编码的 3 输入和 40 输入批次，以及一个快照；变异包括字节翻转、插入、删除、截断，以及覆写 tick、数量和大小字段的极值。不变量：
- 不越界。
- 拒绝时输出为零。
- 接受的批次长度恰好、指针在输入内。
- 接受的快照重新编码后逐字节相同。
- 收件箱按严格 tick 顺序应用，且不超过批次数量。

种子 89 和 113 各 200000 次在 ASan+UBSan+leak 下干净。负向对照 4 项均判红：批次长度只查下限、快照长度只查下限（heap-buffer-overflow）、不查保留字节、去掉缺口判断。

**验证**：normal / ASan+UBSan / TSan 下 `test_break_prediction` 14/14、`test_break_prediction_wire` 9/9。Windows 实机 MSVC（`/W4 /WX`）14/14、9/9，fuzz 20000 次干净；首次在实机上编译时 C4310（常量截断转换）报错，已改为先赋给 `u32` 再截断。`build-current-vk` 非 fuzz 全量 462/462，fuzz 24/24。

## 6. 远端实体的快照插值（`break_snapshot_interp`）

源码：`engine/src/network/break_snapshot_interp.{h,c}`。测试：`engine/tests/test_break_snapshot_interp.c`（12 例）。

预测只用于本地实体。其他实体的快照按固定 tick 频率到达，但会迟到、不均匀，偶尔乱序；收到一帧画一帧会让它们抖动。做法是按「估计的服务端时间减去插值延迟」渲染，在这个时刻前后的两个快照之间混合：位置线性插值，朝向用四元数 slerp 并取较短的弧。

- 每个实体一个 `BreakSnapshotInterp`，最多保存 32 个快照，按 tick 排序。重复 tick 返回 DUPLICATE；缓冲区满时丢掉最旧的，但比最旧的还旧的快照返回 TOO_OLD。输入的四元数会被归一化，零四元数和非有限值被拒绝。
- `sample(render_tick)` 接受小数 tick：
  - 在两个快照之间：插值（INTERPOLATED）。
  - 超过最新快照：沿最后一段速度外推，最多 `max_extrapolate_ticks` 个 tick，之后停在外推终点（EXTRAPOLATED，然后 HELD）。只有一个快照、外推关闭，或最后一段本身是传送，都直接停在最新快照。这样丢一个包时实体不会立刻冻住，长时间断线时也不会一直飞出去。
  - 早于最旧快照：停在最旧快照（HELD）。
- 两个快照之间的间隔超过 `max_gap_ticks` 时不混合，视为传送或离开视野：渲染时间到达较新的快照之前一直显示较旧的那个，恰好等于上限时仍然混合。
- `discard_before(tick)` 丢掉更旧的快照，但保留 `tick` 之前最新的一个，后续采样仍需要用它混合。
- 两个朝向几乎相同时改用归一化线性插值，避免除以接近 0 的 sin。

**测试**：线性插值与端点；slerp 的中点和四分之一点、取反的四元数走同一条较短弧、几乎相同的朝向不产生 NaN；归一化与拒绝；乱序到达后排序、重复；外推、外推上限、外推关闭、单个快照；传送后不外推；超过间隔上限不混合而恰好等于上限仍混合；早于最旧快照；满缓冲区丢最旧、拒绝更旧、之后仍可插入中间的 tick；`discard_before` 的保留规则、恰好落在 tick 上、NaN 不丢任何快照；参数校验。随机性质测试：200 个 tick，25% 丢包，随机迟到最多 3 个 tick，每次采样检查朝向是单位四元数，并在两个已到达快照之间与直接计算的线性插值比较。

**变异**：31 项。首轮 6 项存活：
- slerp 的第一个权重写错：中点处两个权重相等，所以中点测试看不出来；补四分之一点后判红。
- `discard_before` 的比较 `<=` 改成 `<`：补「恰好落在 tick 上」一例后判红。
- 与第一个快照比较时 `<=` 改成 `<`，以及这一分支里「恰好在第一个快照上并且可以混合」的两项特判：这段特判没有可观察的效果，因为插值路径在 t=0 时给出同样的位姿，只是结果码不同。删掉特判，改为只在严格早于第一个快照时返回 HELD；其余情况交给插值路径。
- `discard_before` 对 NaN 的检查：NaN 比较恒为假，本来就不会丢弃任何快照，删掉该检查并在注释里写明，补一例固定这一行为。

另外 3 项（满缓冲时插入点不前移、丢最旧时不前移、只有一个快照仍外推）在测试中以失败或 ASan 越界判红。

**验证**：normal / ASan+UBSan / TSan 下 12/12；Windows 实机 MSVC（`/W4 /WX`）12/12；`build-current-vk` 非 fuzz 全量 464/464，fuzz 24/24。`test_repo_naming_contract` 首次运行时抓到头文件注释中的禁用词，已改正。

## 7. 在 `break_net` 消息注册表中登记

两种报文登记为 `break_net` 的正式消息，信封层会先按上限拒绝过大的载荷，再交给解码器：

| 消息 | id | 方向 | 版本 | 载荷上限 | 阶段 | 重复策略 |
| --- | --- | --- | --- | --- | --- | --- |
| `BREAK_NET_MESSAGE_ID_PREDICTION_INPUT` | `0x400c` | 对端到服务端 | 1..1 | 64 KiB | AUTHENTICATED | IDEMPOTENT |
| `BREAK_NET_MESSAGE_ID_PREDICTION_SNAPSHOT` | `0x400d` | 服务端到对端 | 1..1 | 20 + 16 KiB | AUTHENTICATED | IDEMPOTENT |

重复策略取 IDEMPOTENT，因为批次按设计会重叠和重发，由服务端的收件箱去重。

**修正一个上限问题**：登记时测试发现，原先的批次上限是 32 个输入，每个最多 4096 字节，合计 131 KiB，超过了信封 64 KiB 的载荷上限，这样的批次根本发不出去。现在批次总长（含头部）上限为 `BREAK_PREDICTION_WIRE_MAX_INPUT_MESSAGE` = 64 KiB：
- 编码端在 32 个和「能装进 64 KiB 的个数」中取较小者。例如 4096 字节的输入每批 15 个。
- 解码端拒绝超过 64 KiB 的批次，即使数量和长度一致也拒绝。

注册表的上限与这个值一致，所以信封层和解码器对「最大的合法批次」给出同一个答案。

**测试**：
- `test_break_session` 检查两条消息的 id、上限、版本、阶段和重复策略，并检查上限等于解码器能接受的最大报文。信封编码时，恰好等于上限的载荷可以编码，多 1 字节返回 OVER_LIMIT。注册表总数从 31/32 变为 33/34。
- `test_break_prediction_wire` 新增「大输入的批次装进一个信封」一例：20 个 4096 字节输入每批发 15 个；16 个时数量和长度一致，但超过 64 KiB，被拒绝。
- 两项变异（编码端不按 64 KiB 截断、解码端不查总长）都判红。
- `fuzz_prediction_wire` 种子 89 跑 200000 次干净。

**验证**：
- Snowflake 构建（ASan+UBSan）下 `test_break_session` 43/43，`-L network` 28/28，`-L "snowflake|editor"` 33/33。
- `build-current-vk` 非 fuzz 全量 464/464，fuzz 24/24。
- Windows 实机 MSVC 全量构建通过，`test_break_prediction_wire` 10/10，网络、预测、会话、World 相关测试全部通过。

本提交自身的远端工作流结果不在此预写。

## 8. 会话层接线（`break_prediction_session`）

`engine/src/network/break_prediction_session.{h,c}` 把服务端的输入收件箱和快照发送接到 `break_net` 会话管理器与 reactor 上，编入 `break_net`（只在 `BREAK_ENABLE_SNOWFLAKE=ON` 时构建）。

- **连接**：每个打开的连接占一个槽，槽里有一个 `break_prediction_inbox` 和一个拒绝计数。`open(conn, first_tick)` 从 `first_tick` 开始收输入；`first_tick` 为 0、连接已打开、槽已满都返回 false。`close` 释放槽，重新打开的连接从新的起点开始。槽数为 1..4096。
- **接收**：`attach(session, manager)` 为 `0x400c` 注册 handler。handler 解码批次，把每个新输入按 tick 顺序交给调用方的 `apply` 一次，并附带连接号。重复和缺口计入统计。
- **失败语义**：批次解码失败、或者来自没有打开的连接，handler 返回 false。会话管理器把它记为 HANDLER_FAILED，但对非认证消息不会关闭会话；本模块把它计入该连接的 `rejected()`。是否断开持续发坏批次的对端，由调用方根据 `rejected()` 决定。`apply` 返回 false 时批次停在该输入，handler 同样失败，下一个批次从同一 tick 继续。
- **发送**：`send_snapshot(conn, state)` 用该连接收件箱的最后 tick 编码快照，经 `break_net_reactor_send` 以 `0x400d`、版本 `BREAK_PREDICTION_WIRE_VERSION` 发出。没有 reactor（只收模式）、连接没有打开、state 为 NULL 时返回 `BREAK_NET_SEND_INVALID`。
- **线程**：所有调用都在轮询会话管理器的逻辑线程上进行，本模块不加线程、锁或原子操作。

**测试**：`test_break_prediction_session` 8 例，先以链接失败为 RED。测试用 Snowflake 的回环 reactor 和真实会话管理器，把会话推进到已认证状态后投递 `MESSAGE_RECEIVED` 事件；出站快照用 `break_net_reactor_poll_outbound_for_test` 取出后再解码比对。覆盖两个连接各自按序应用、重叠批次去重、缺口、坏批次和未打开连接的拒绝、apply 中途失败后续传、快照携带最后 tick、输入长度与配置不符时拒绝、只收模式不能发送、开关连接与上限、配置校验。

**变异**：25 项。其中「`find` 不检查槽是否在用」一项起初存活，补上「新建会话对连接 0 查不到」的断言后判红。「`send_snapshot` 不检查 reactor 为 NULL」是等价变异：`break_net_reactor_send_correlated` 对 NULL reactor 同样返回 `BREAK_NET_SEND_INVALID`。这个检查仍然保留，让只收模式的语义不依赖下层实现。其余全部判红。

**验证**：
- Snowflake ASan+UBSan 构建 8/8 无泄漏，`-L "network|snowflake|editor|session"` 59/59。
- TSan 构建 8/8；`-L "network|snowflake|session"` 32/33，唯一失败是 `test_core_app_network_offline`，即本机 Fedora 上已记录的 Lua longjmp CHECK 环境问题，与本改动无关。
- `build-current-vk` 非 fuzz 全量 464/464，fuzz 24/24。
- Windows 实机 MSVC 全量构建通过，相关测试 24/24。Windows 构建没有开 Snowflake，所以本模块不在其中编译。

仍未交付：把预测接入 World/ECS。组件层的绑定见第 9 节。

本提交自身的远端工作流结果不在此预写。

## 9. 绑定到 ECS World 的组件（`break_prediction_world`）

`engine/src/network/break_prediction_world.{h,c}` 把预测器的状态绑定到 ECS World 里一个实体的一个组件上。状态就是这个组件的字节，`state_size` 取组件注册时的大小。这个模块不依赖 Snowflake。

- **客户端**：`break_prediction_world_create` 读取实体当前的组件值作为已确认状态，并创建一个预测器。每次 `apply_input` 或 `reconcile` 成功后，都把预测状态写回组件，读 World 的系统看到的就是预测结果。预测器是唯一的事实来源：在它之外对组件的修改，会被下一次成功调用覆盖。失败的调用不写组件，所以这种修改在失败调用之后仍然保留。
- **服务端**：`break_prediction_world_step_authoritative(world, entity, component, step, user, input)` 用同一个 step 函数推进权威 World 里的组件，可以直接放在 `break_prediction_session` 的 apply 回调中。两边运行同一个确定性 step，快照才能对上。step 返回 false 时组件不变，结果为 FAILED。
- **实体或组件消失**：实体被销毁、组件被移除时，调用返回 INVALID，不运行 step，预测器也不前进。`reconcile` 在任何非 OK 结果下都会把 report 清零。
- **校验**：组件 id 越界、实体不存在、实体没有该组件，都由 `world_get_component` 返回 NULL 判定，组件大小只在它成功后才读取。ECS 允许实体挂一个从未注册过的组件 id，此时大小为 0。客户端靠 `break_prediction_create` 的 state_size 检查拒绝这种情况，服务端单独检查。组件大于 `BREAK_PREDICTION_MAX_STATE_BYTES` 时两边都拒绝；恰好等于上限时可以使用。
- World 是借用的，必须比绑定活得久。所有调用都在拥有者线程上进行，本模块不加线程、锁或原子操作。

**测试**：`test_break_prediction_world` 9 例，先以链接失败为 RED。覆盖：
- 组件跟随预测。
- 校正后组件改写为重放结果。
- 外部修改被覆盖，失败调用不写组件。
- 失败时预测器和组件都不变。
- 实体销毁、组件移除时拒绝且不前进。
- 创建参数校验，包括未注册、大小为 0 和超过上限的组件。
- 最大状态大小在两端都可用。
- 服务端权威 step。
- 客户端和服务端两个 World 用相同输入运行 60 tick：服务端在 tick 30 自行移动实体，客户端随机收到晚 3 tick 的快照。期间确实出现分歧和校正，最后一次快照后客户端组件与服务端当前值相等。

**变异**：27 项，26 项判红。存活的是去掉 `create` 中 `!initial` 检查。有这个检查，实体没有组件时返回 INVALID；去掉后读取越界的组件大小，再由 `break_prediction_create` 因 `initial_state` 为 NULL 返回 INVALID，结果相同。所以这是等价变异，但检查必须保留：它挡住了越界读取 `component_sizes`。初版另有几项存活：重复的 `world_entity_exists` 检查和独立的组件 id 边界检查，前者与 `world_get_component` 的校验重复，已删除；把读取大小移到 `world_get_component` 成功之后，后者也随之删除。另外补了输入大小断言，以及最大状态大小一例。

**验证**：
- normal、ASan+UBSan、TSan 下 9/9。
- `build-current-vk` 非 fuzz 全量 465/465，fuzz 24/24。
- Windows 实机 MSVC 全量构建通过，本测试 9/9，相关测试 25/25。

### 9.1 从复制镜像 World 校正

客户端收到的服务端状态通常是 `break_world_session_drain` 应用到镜像 World 的增量。`break_prediction_world_reconcile_from_world(pw, mirror, mirror_entity, tick, report)` 读取镜像 World 里对应实体的同一个组件，把它作为 `tick` 的服务端状态进行校正，`tick` 取已应用增量的目标 tick。它只读镜像，不写镜像。镜像实体不存在、没有该组件，或组件大小与绑定不同时返回 INVALID。

**预测不能写进镜像 World。** 增量只能应用到与其基准快照完全相同的 World 上（`world_matches_snapshot` 逐字节比较）。预测值一旦写进镜像，服务端的下一个增量就会因 `BREAK_DELTA_BASE_MISMATCH` 应用失败。因此客户端要用两个 World：镜像 World 只接收增量，表现 World 绑定预测。两边的实体编号可以不同，调用时分别传入。

**测试**（`test_break_prediction_world` 增加 3 例，共 12 例，先以链接失败为 RED）：
- 端到端：服务端 World 逐 tick 推进，第 20 tick 自行移动实体。每隔随机若干 tick，用 `break_world_snapshot_build` 和 `break_world_delta_diff` 产生增量，客户端应用到镜像 World，再从镜像校正表现 World。期间至少有一次误预测，最后表现 World、镜像 World 和服务端三者相等。状态与基准相同时，增量返回 `BREAK_DELTA_ALREADY_APPLIED`，测试也接受这种情况。
- 反例：把预测绑定到镜像 World 本身，下一个增量返回 `BREAK_DELTA_BASE_MISMATCH`。这条测试把上面的限制固定下来。
- 镜像实体校验：没有组件、组件大小不同、镜像为 NULL、实体已销毁，都返回 INVALID 且 report 清零；镜像实体编号与绑定实体不同时也能正确校正。

**变异**：8 项，7 项判红。存活的是去掉 `!state` 检查：此时 NULL 的 state 交给 `break_prediction_reconcile`，同样返回 INVALID，属于等价变异。检查仍保留，因为后面的大小比较要读 `component_sizes`。

**验证**：normal、ASan+UBSan、TSan 下 12/12；`build-current-vk` 非 fuzz 465/465，fuzz 24/24；Windows 实机 MSVC 全量构建通过，本测试 12/12，相关测试 25/25。

仍未交付：
- 在 `core_app` 中启用：同时创建镜像 World 与表现 World，把预测输入经 `break_prediction_session` 发送。
- 预测之外，表现 World 中其他远端实体的同步，由调用方结合 `break_snapshot_interp` 完成。

本提交自身的远端工作流结果不在此预写。
