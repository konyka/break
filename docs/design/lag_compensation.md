# 服务端延迟补偿（`break_lag_compensation`）

状态：2026-11-27 交付。`docs/design/client_prediction.md` 第 4 节把「服务端的延迟补偿（回溯命中判定）」列为未交付，本文件交付这一项。它是纯 C、与传输无关的历史缓冲区加射线查询，没有接入 World、物理或 `core_app`。

源码：`engine/src/network/break_lag_compensation.{h,c}`。测试：`engine/tests/test_break_lag_compensation.c`（10 例）。

## 1. 为什么需要

客户端看到的世界比服务端落后一段时间，大约是往返延迟加上插值延迟。用户在客户端瞄准的是「当时看到的位置」。如果服务端用当前位置判定命中，移动中的目标在客户端上被打中，在服务端上却已经走开了。

延迟补偿让服务端保留每个 tick 所有实体的包围盒，在客户端报告的视图 tick 上做命中判定。

## 2. 接口与规则

- 每个服务端 tick 先调用 `begin_tick(tick)`，再对每个存活实体调用 `record(id, box)`。tick 必须连续加一。第一次调用可以从任意 tick 开始。
- 历史保留 `history_ticks` 个 tick，第 `t` 个 tick 存在第 `t % history_ticks` 个槽里。每个槽记录自己属于哪个 tick，所以旧槽不会被误认成新 tick。
- `raycast(view_tick, origin, direction, max_distance, ignore_id)` 在 `view_tick` 当时的包围盒上投射射线，返回最近的命中；距离相同时取较小的实体 id。`ignore_id` 用来跳过开枪者自己。射线起点在某个盒子里面时，命中距离为 0。方向向量会先归一化，所以距离和命中点都是世界单位。
- `box_at(tick, id)` 返回某个实体在某个 tick 的包围盒。

**不信任客户端的时钟**：
- 视图 tick 超前于当前 tick，或者比当前 tick 早超过 `max_rewind_ticks`，都返回 REJECTED。`max_rewind_ticks` 必须小于 `history_ticks`。因此客户端无法通过谎报视图 tick 打到很久以前或未来的位置。
- 只测试在视图 tick 当时确实记录过的实体。那时还没出生或已经消失的实体打不中。

**输入校验**：
- 包围盒的 min 大于 max，或者含有 NaN、无穷大，都会被拒绝。
- 实体 id 不能为 0；同一 tick 内同一个 id 只能记录一次；每个 tick 的实体数有上限 `max_entities`，超出时返回 FULL。
- 射线的起点、方向和距离必须有限；方向不能为零向量；距离不能为负。

内存为 `history_ticks * max_entities` 个条目加每个 tick 一个槽，在 `create` 时一次分配。上限是 4096 个实体、256 个 tick。单个 tick 内按记录顺序线性扫描，适用于单个房间或单个 AOI 内的实体数量；更大的规模需要先用空间索引筛选，这一步不在本模块内。

单线程拥有者（模拟线程），不加锁。

## 3. 测试与变异

10 例，先以链接失败为 RED：
- 移动目标在视图 tick 上命中、在当前 tick 上不命中，晚一个 tick 也不命中。
- 回溯窗口两端的边界：恰好 `max_rewind_ticks` 可以，多一个 tick 就拒绝，未来的 tick 拒绝。
- 历史被覆盖后无法再查询；被复用的槽会忘记旧 tick 的实体。
- 视图 tick 时尚不存在、或已经消失的实体。
- 最近命中优先、距离相同时取较小 id、跳过开枪者、射程边界。
- 任意方向的射线、未归一化的方向、起点在别处时命中点为世界坐标、平行于某条轴的射线。
- 记录规则：tick 顺序、id 为 0、重复 id、翻转或非有限的包围盒、FULL。
- 参数校验，包括非有限的起点。
- 随机性质测试：40 个 tick、24 个实体，每个 tick 30 次查询，视图 tick 随机落在回溯窗口内，与暴力参考实现比较结论和距离。

32 项变异中 29 项判红，3 项等价：
- `held()` 里的「年龄小于 `history_ticks`」与「槽属于这个 tick」两条检查互为冗余：超出历史的 tick，其槽一定已被更新的 tick 覆盖，`s->tick == tick` 会不成立；反过来，槽的 tick 对得上时年龄一定在范围内。单独去掉其中任意一条行为不变，同时去掉两条时 `history_older_than_its_length_is_gone` 判红。
- 去掉 `raycast` 中「视图 tick 不能超前」的检查：当前 tick 减去更大的视图 tick 会在无符号运算中回绕成很大的数，仍被回溯窗口挡掉。

首轮另有 2 项存活（命中点不加起点、不检查起点是否有限），补两例后判红。

normal / ASan+UBSan / TSan 下 10/10；Windows 实机 MSVC（`/W4 /WX`）10/10；`build-current-vk` 非 fuzz 全量 463/463，fuzz 24/24。

## 4. 未交付

- 接入 World/物理：包围盒由调用方从 ECS 或物理系统取出后记录，本模块不读 World。
- 空间索引：单 tick 内线性扫描。
- 命中判定之外的回溯（例如回溯后再做近战扫掠、范围伤害）。
- 视图 tick 的来源：客户端报告的视图 tick 应来自预测输入批次中的 tick 减去插值延迟，这一换算由调用方完成。

本提交自身的远端工作流结果不在此预写。
