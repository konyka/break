# 跨分区 authority 交接

## 目标

大世界会被分成多个 cell，每个实体在任一时刻只由一个 cell 权威模拟。实体越过边界时，要把权威从一个 cell 交给相邻 cell，并满足三点：任何时刻最多一个 cell 是权威，交接过程中不丢失写入，网络丢包、重复和乱序都不破坏前两点。`BreakCell`（`engine/src/network/break_cell_handoff.{h,c}`，属于 `break_replication_core`）实现一个 cell 在交接中的一方。它与传输无关：发出的消息交给配置的 `send` 回调，收到的消息交给 `break_cell_receive`，重传和超时由 `break_cell_tick` 驱动。

不在范围内：cell 的划分与负载均衡、跨进程传输、持久化、AoI 可见性迁移、客户端连接迁移。

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
