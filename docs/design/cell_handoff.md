# 跨分区 authority 交接

## 目标

大世界会被分成多个 cell，每个实体在任一时刻只由一个 cell 权威模拟。实体越过边界时，要把权威从一个 cell 交给相邻 cell，并满足三点：任何时刻最多一个 cell 是权威，交接过程中不丢失写入，网络丢包、重复和乱序都不破坏前两点。`BreakCell`（`engine/src/network/break_cell_handoff.{h,c}`，属于 `break_replication_core`）实现一个 cell 在交接中的一方。它与传输无关：发出的消息交给配置的 `send` 回调，收到的消息交给 `break_cell_receive`，重传和超时由 `break_cell_tick` 驱动。

不在范围内：cell 的划分与负载均衡、跨进程传输、持久化、AoI 可见性迁移、客户端连接迁移。划分、负载均衡与跨进程传输已在后续各节实现。

## 协议

源 cell S、目标 cell T，每次发起交接 S 分配一个事务号 txn：

| 消息 | 方向 | 含义 |
|---|---|---|
| OFFER(txn, epoch, state) | S → T | S 仍是权威，仍可写 |
| ACCEPT(txn, nonce) | T → S | T 建立 receiving 记录，nonce 标识这条记录；没有空间时回 REJECT |
| COMMIT(txn, nonce, epoch + 1, 最新状态) | S → T | S 在发送前放弃权威 |
| COMMIT_ACK(txn, nonce) | T → S | T 成为权威（只对该 nonce 的记录生效）；S 收到后删除记录 |
| ABORT(txn, nonce 或 0) | S → T | offer 超时，或回应 S 无法使用的 ACCEPT；T 删除对应的 receiving 记录 |

OFFER 和 COMMIT 重传到得到回应为止，ACCEPT 重传到记录被提交或中止为止。offer 只在 S 仍是权威时才会超时，COMMIT 从不放弃。

## 为什么最多一个权威

- S 在发送 COMMIT 之前放弃权威，T 只在收到与自己 nonce 相同的 COMMIT 时才成为权威。所以两者不会同时是权威。
- receiving 记录只会因两种原因消失：被提交，或收到 ABORT。而 S 从不中止已经提交的事务。因此一条找不到 receiving 记录的 COMMIT 一定已经生效过，T 直接回 COMMIT_ACK 是安全的。
- 一个 OFFER 如果其 epoch 不低于 S 提交时的 epoch，就只可能来自已经应用了该提交的 T（只有 T 能产生这个 epoch），所以它也能立即释放 S。COMMIT_ACK 丢失后实体又被交回 S 时，靠这一条立即接受交回；没有这一条，S 重传的 COMMIT 到达 T 后也会被确认（T 已没有 receiving 记录），只是要多等一个重传周期。
- epoch 只在提交时加一，所以权威的 epoch 单调增长。

## 写入不丢失

交接期间 S 仍可写。COMMIT 携带 S 放弃权威那一刻的状态，T 从这个状态继续。

## 测试

`test_break_cell_handoff`（8 例）：
- 生成、写入、读取、容量上限与参数校验；
- 干净交接：OFFER 期间的写入随 COMMIT 送达，epoch 加一，S 的记录在 ACK 后释放；
- 目标已满时拒绝，源保留实体；
- 超时中止后，迟到的 ACCEPT 收到 ABORT，目标删除记录，再次交接正常；
- COMMIT_ACK 丢失时，交回的 OFFER 释放旧源；
- 畸形或过时的消息被忽略并计数；
- 旧源等待 ACK 时，过期的重复 OFFER 在目标上建立陈旧记录，旧源用 ABORT 清掉它，之后 COMMIT 重传得到确认，旧源被释放；
- 混沌测试：4 个 cell、12 个实体，8 种网络模式（含丢包、重复、乱序和最多 30 步的延迟）各 20 个种子，每次 3000 步随机写入与交接。每一步都检查最多一个权威、epoch 不回退；网络恢复后检查每个实体恰好一个所有者、没有进行中的记录，计数器等于被接受的写入次数。每种模式实际发生 8,600~51,000 次交接。

变异检查。以下变异均被检出：COMMITTING 仍算权威、忽略 COMMIT 的 nonce、提交时不加 epoch、COMMITTING 收到任何 OFFER 都释放、陈旧 OFFER 替换活动记录、对已提交事务的任何 ACCEPT 都不回 ABORT、收到无法使用的 ACCEPT 时不回 ABORT、COMMIT 不带状态。有两处未被检出，原因已核实：
- ABORT 的 nonce 检查：带 nonce 的 ABORT 只会遇到同一事务的陈旧记录，删除它同样安全，所以这项检查只是防御性的；
- 把“epoch 不低于”改为“高于”：只影响释放的快慢，不影响正确性（见上文）。

## 分区（2026-11-22）

`BreakCellPartition`（`engine/src/network/break_cell_partition.{h,c}`，属于 `break_replication_core`）把 XZ 平面划分为均匀网格。cell id 按行优先排列，即 `行 * 列数 + 列`，x 增大时列号增大，z 增大时行号增大。每个 cell 在两个轴上都覆盖左闭右开区间 `[min + i * size, min + (i + 1) * size)`。网格外的位置归最近的边缘 cell，所以每个位置恰好属于一个 cell，边缘 cell 永远不会把实体迁出网格。坐标不是有限值时映射到第 0 列或第 0 行。

`break_cell_partition_migrate_target(p, current, x, z, hysteresis)` 决定权威 cell 何时发起交接：实体到当前 cell 矩形的欧氏距离超过 `hysteresis` 时，才返回 `locate` 的结果，否则返回 `current`。所以在边界附近来回移动的实体不会被反复交接。`hysteresis` 为 0 时完全按 `locate` 判定。位置不是有限值时不迁移。当前 cell 未知，或 `hysteresis` 为负或非有限时，退回 `locate`。

调用方式：权威 cell 每次更新实体位置后调用一次；返回值与当前 cell 不同时，调用 `break_cell_begin_handoff`。分区是普通值类型，不分配内存，只读访问是线程安全的。

测试 `test_break_cell_partition`（5 例）：
- 行优先映射、左闭右开边界、越界钳制与非有限坐标；
- 非法网格参数，包括 cell 总数溢出；
- 滞后带：恰好等于阈值时不迁移，对角方向按欧氏距离计算，阈值为 0 时与 `locate` 一致，网格外缘不迁出，非有限位置不迁移；
- 端到端：实体沿直线穿过 3 个 cell，由 `BreakCell` 交接两次，最终归第 3 个 cell，始终只有一个权威；
- 在边界两侧 0.8 范围内来回抖动（阈值 1.0）200 步，没有发生任何交接。

变异检查（均被检出）：去掉滞后、按轴判定代替欧氏距离、阈值比较改为严格小于、边界越界判定差一、非有限位置照常迁移。分区只处理二维均匀网格；按负载拆分或合并 cell 尚未实现。

## 按负载分配（2026-11-22）

`break_cell_balance`（`engine/src/network/break_cell_balance.{h,c}`，属于 `break_replication_core`）把 cell 分配给服务器：
- 先按 Hilbert 曲线给所有 cell 排序。网格补成最小的 2 的幂正方形后计算曲线序号，在 2 的幂正方形网格上，相邻序号的 cell 在网格中也相邻，所以曲线上连续的一段是空间上紧凑的区域。
- 再把这个顺序切成每台服务器一段，使负载最大的服务器尽量轻：对上限做二分查找，用贪心装箱检查某个上限能否装进给定台数。在所有“按曲线顺序连续切分”的方案中，结果是最优的。
- `load[cell]` 由调用方定义，例如实体数或 CPU 时间。用不到的服务器不分配 cell。上限为 64 台服务器、4096 个 cell。

`break_cell_balance_needed(p, load, assign, servers, ratio)` 判断是否值得重新分配：当前方案下最忙的服务器负载超过最优最大值的 `ratio` 倍（`ratio` ≥ 1），或者方案中出现了不存在的服务器时，返回 true。空闲的世界永远不需要重新分配。用 `ratio` 留出余量，避免负载小幅波动时频繁迁移。

这个规划器只决定 cell 归属。把 cell 迁到另一台服务器，等于对其中每个实体执行一次 `BreakCell` 交接，由调用方完成。

测试 `test_break_cell_balance`（5 例）：
- Hilbert 顺序在 1×1 到 16×16 的 2 的幂网格上每个 cell 恰好一次且相邻步都是网格邻居，在 5×3 网格上每个 cell 恰好一次，容量不足时返回 0；
- 300 组随机网格（1~4 列、1~3 行）、随机负载（含零负载）、1~4 台服务器：每台服务器分到的 cell 都是曲线上的一段，报告的最大负载与实际一致，并且等于穷举所有切分得到的最优值；
- 热点 cell 独占一台服务器；
- 服务器多于 cell、各种非法参数、超过 cell 上限；
- 重新分配判定：均匀负载不需要；某台服务器负载增加 20% 时，在 1.25 倍阈值下不需要；增加到 3 倍时需要；30% 偏斜在 1.0 和 1.25 倍下需要、1.5 倍下不需要；最优方案在 1.0 倍下也不需要；非法服务器编号总是需要。

变异检查（均被检出）：二分条件差一、去掉 Hilbert 象限翻转、用 cell 序号代替曲线序号、切分时用 `>=`、忽略阈值、阈值比较改为 `>=`、忽略非法服务器编号、去掉 cell 上限。有两处未被检出，原因已核实：二分下界取 0 而不是最大单个负载，只是多几次迭代，结果相同；空闲判断与 `0 > ratio * 0` 等价。

## 跨进程传输（2026-11-22）

`break_cell_link`（`engine/src/network/break_cell_link.{h,c}`，独立静态库 `break_cell_link`，只在 `BREAK_ENABLE_CRYPTO` 打开时存在）把 `BreakCell` 的消息放到 UDP 上，每条消息一个数据报。用法：把 `break_cell_link_send` 设为 cell 的 `send` 回调，把 link 设为 `user`；cell 线程每个 tick 先调用 `break_cell_link_poll(link, cell, n)`，再调用 `break_cell_tick`。

线格式（小端，版本 2）：`magic 'BRC1'`、`version`、`type`、`from_cell`、`to_cell`、`state_size`、`entity`、`epoch`、`txn`、`nonce`、`sequence`、`key_id`（共 64 字节），然后是 `state`（最多 `BREAK_CELL_STATE_MAX` 字节），最后是对前面所有字节计算的 HMAC-SHA256（32 字节）。同一个世界的所有 cell 共用一个密钥（16~64 字节），密钥由调用方分发。

接收方只在以下条件都满足时才把消息交给 cell：长度与 `state_size` 一致；`key_id` 是自己持有的密钥（否则计入 `unknown_key`）；magic、版本、类型合法，序号和 `key_id` 不为 0；HMAC 一致（常量时间比较）；`from_cell` 是配置的对端，`to_cell` 是本 cell；序号通过该对端的重放窗口（`BreakReplayWindow`，64 个序号）。重放窗口只在 HMAC 验证通过后才标记，伪造的数据报不能占用序号。发送方拒绝 `from_cell` 不是本 cell 或 `to_cell` 不是已配置对端的消息，计入 `send_failed`。

序号从创建 link 时的墙钟微秒数开始递增，所以发送方重启后序号仍然高于重启前发出的所有序号，接收方不会把它当成重放。接收方自己重启时重放窗口清空，旧数据报可能再次送达；协议本身容忍重复消息（见上文），所以不影响正确性。传输不提供保密性：状态是明文，只保证来源与完整性。需要保密时应在 QUIC/TLS 通道上传输。

密钥轮换（2026-11-22）：每个 link 持有当前密钥（发送用）和上一个密钥（仍接受）。`break_cell_link_rotate_key(link, id, key, size)` 把新密钥设为当前密钥，原当前密钥降为上一个，更早的密钥丢弃；`id` 已被持有或密钥非法时不做任何改变并返回 false。`break_cell_link_retire_previous_key` 停止接受上一个密钥。不停机轮换的顺序：先让所有接收方轮换，再让所有发送方轮换，最后让所有 link 退役旧密钥。每个 link 都同时收发，所以实际做法是所有 link 依次调用 rotate（此时可能有一方先用新密钥发送，另一方仍以“上一个”接受旧密钥、以“当前”接受新密钥，见测试），全部完成后再调用 retire。`key_id` 不参与保密，只用来选择校验密钥，并由 HMAC 覆盖。

测试 `test_break_cell_link`（8 例）：
- 6 种消息类型 × 0~64 字节状态的往返编解码，固定字节布局；
- 编码参数校验：序号为 0、空指针、缓冲区不足一字节、状态过大、非法类型；
- 解码：每一种截断长度、多一个字节、每一个比特翻转都被拒绝；换密钥或密钥长度不同时 HMAC 不一致；序号为 0 的数据报即使 HMAC 正确也被拒绝；
- 创建参数校验：没有对端、对端过多、对端编号与本 cell 相同、对端编号重复、密钥过短或过长；创建后可以复用配置里的密钥缓冲区；
- 经回环 UDP 完成一次真实交接：OFFER 期间的写入随 COMMIT 送达，epoch 变为 2，任何时刻最多一个权威；
- 注入数据报：重放只送达一次，远低于窗口的序号被拒绝，伪造的数据报不会占用它声称的序号，未知发送方与发往其他 cell 的消息被拒绝，垃圾与截断数据报计入格式错误，发往未配置 cell 或冒充其他 cell 的发送被拒绝；
- 发送方重启后（同一端口、新的 link），新交接不被当作重放；
- 密钥轮换：非法轮换不改变 link；接收方先轮换、发送方在交接进行中轮换，交接照常完成且没有 HMAC 错误；退役后旧密钥被拒绝（`unknown_key`），声称新 `key_id` 却用旧密钥签名的数据报是 HMAC 错误；连续轮换两次后只保留最新两个密钥；`key_id` 为 0 时编码和解码都拒绝。

变异检查（均被检出）：不接受上一个密钥、轮换时丢弃旧密钥、退役不生效、允许复用当前 `key_id`、未知 `key_id` 退回当前密钥、解码或编码允许 `key_id` 为 0、退役总返回成功、`key_id` 不写入线格式、发送时用旧 `key_id`；跳过 HMAC 比较、允许序号 0、不标记重放窗口、不检查 `to_cell`、不检查发送方是否已配置、序号从 1 开始、序号不递增、允许对端编号与本 cell 相同、允许重复对端、允许尾部多余字节、发送时不检查 `from_cell`、HMAC 错误计为格式错误、nonce 编码错误。

仍未实现：AoI 与客户端连接随交接迁移。密钥本身的分发由调用方负责。

## 崩溃恢复（2026-11-22）

`BreakCell` 可以把自己的全部状态写成快照，崩溃后从快照恢复（`break_cell_snapshot_size`、`break_cell_snapshot`、`break_cell_restore`，见 `break_cell_handoff.h`）。快照包含所有记录（包括 OFFERING、COMMITTING、RECEIVING 这些进行中的记录及其重传与超时计数），以及事务号和 nonce 计数器；不包含待发消息和统计。格式为小端的定长头部、逐条记录，最后是对前面所有字节的 FNV-1a 64 位哈希。哈希只用来发现存储损坏，不防篡改，快照应存放在可信的存储中。恢复时拒绝：截断、哈希不一致、magic 或版本不对、cell id 不同、记录数超过容量、实体重复、记录状态或状态长度非法、尾部多余字节。

只有快照还不够。如果 cell 先发出 COMMIT（放弃权威），再在写快照前崩溃，从旧快照恢复后它会认为自己仍是权威，而目标可能已经接受了 COMMIT，于是出现两个权威。所以新增配置项 `hold_outbox`：打开后，消息先进入发件箱，调用 `break_cell_flush` 时才真正发送。安全的顺序是每批调用之后：

1. `break_cell_snapshot`，并把快照写入持久存储；
2. `break_cell_flush`。

这样，对端看到的每一条消息都来自一个已经持久化的状态。从最新快照恢复的 cell 不会再次拥有已交出的实体，也不会复用事务号或 nonce；没来得及发出的消息随崩溃丢失，等同于网络丢包，协议本身能处理。最新快照之后的写入会随崩溃丢失。

测试（`test_break_cell_handoff` 新增 5 例，共 13 例）：
- 快照往返：源 cell 同时有 OWNED、OFFERING、COMMITTING 记录，目标有 RECEIVING 记录，tick 后计数器非零；恢复后的 cell 再次快照得到逐字节相同的结果，并能完成两个进行中的交接和一次新交接；
- 坏快照：每一种截断长度、每一个字节翻转、其他 cell 的快照、容量不足、缺少 send 回调、空指针都被拒绝；哈希正确但内容非法（重复实体、尾部多一个字节）也被拒绝；
- 发件箱：打开 `hold_outbox` 后，交接和重传只进入队列，flush 时按顺序发出并清空；关闭时直接发送；
- 带崩溃的混沌测试：4 个 cell、12 个实体，丢包 15%、重复 20%、乱序、最多 8 步延迟，每个 cell 每步有 3% 的概率在 flush 之后崩溃并从最新快照恢复。40 个种子共恢复 11,371 次崩溃，始终最多一个权威、epoch 不回退，网络恢复后每个实体恰好一个所有者，计数器不超过已接受的最大写入值；
- 反向顺序（先 flush 后快照）在同样的 40 个种子下全部破坏了上述性质，说明测试能区分两种顺序。

变异检查：不恢复事务号计数器、不恢复 nonce 计数器、不恢复 epoch、txn、nonce、peer、offer_age、since_send、状态数据，不检查 cell id、哈希、尾部字节、重复实体，不使用发件箱，flush 后不清空，均被检出。“记录数超过容量”的检查未被检出：没有这项检查时，`cell_alloc` 在容量用完后也会失败，恢复同样返回 NULL，所以这项检查只是提前拒绝。
