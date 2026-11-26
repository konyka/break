# Runtime 指标注册表（runtime_metrics）

设计归属：`docs/design/runtime_overview.md` §6（Message/Task 的 drop/overload metrics 可观测）、
`docs/design/runtime_network.md`（`publish_progress` 一节标注「指标协议与远程采集、告警仍是缺口」）。
本文件给出**指标协议**的第一块：一个进程内、线程安全、非阻塞的命名指标注册表，以及把快照编码成可被远程采集器消费的稳定文本格式。远程传输、历史采样与告警仍不在本块范围。

## 1. 定位

- 属于 formal OPTIONAL 的 `runtime_core` 静态库，和 `runtime_profiler` 一样不链进 `engine`/`engine_demo`/`dxx_break`；消费者显式 opt-in。
- 这是**指标**（counter/gauge 的数值聚合），与 `runtime_profiler`（span/instant 事件流）互补：profiler 回答「什么时候发生了什么」，metrics 回答「现在各计数是多少」。两者都不改动 `engine/src/core/profiler.c`。
- 不引入任何新线程。注册表由创建线程拥有；快照/编码只在拥有线程调用。

## 2. 数据模型

- 每条指标是一个命名槽：`name`（≤ `BREAK_RUNTIME_METRICS_NAME_CAPACITY-1` 字节、非空）、`kind`（COUNTER 或 GAUGE）、`u64 value`。
- COUNTER 只增（`add` 累加，`value` 单调不减）；GAUGE 可任意 `set`（表示瞬时量，如队列深度、打开连接数）。两种 kind 不可互换：对已存在的 name 用不匹配的 kind 操作返回 `INVALID`。
- 槽位总数有界（`capacity`，默认 64、硬上限 1024）。首次见到的 name 占一个槽；槽满后再出现新 name → `OVERLOAD` 并计数，已存在的 name 不受影响。
- name 查找用线性扫描（容量小、远低于 profiler ring 的热度）。所有读写在一把 leaf 互斥锁下完成，锁序上不回调任何 runtime 子系统，与 profiler 的并发约定一致。

## 3. 热路径契约

- `break_runtime_metrics_add(reg, name, kind, delta)` 与 `break_runtime_metrics_set(reg, name, kind, value)` 可从任意线程调用，非阻塞、不分配、不回调：在短互斥下定位/创建槽并更新。
  - COUNTER 的 `add` 把 `delta` 累加进 `value`（溢出饱和到 `UINT64_MAX`，计 `saturations`，绝不回绕）。
  - GAUGE 的 `set` 覆盖 `value`。
  - 用 `add` 操作 GAUGE、或用 `set` 操作 COUNTER，或 kind 与已存在槽不符 → `INVALID`，不改任何状态。
  - 槽满且 name 不存在 → `OVERLOAD`，计 `overflow_drops`。
  - 关闭后 → `CLOSED`。
- 槽一旦创建不删除（生命周期内 name 集合单调增长），因此地址与索引稳定，便于未来历史采样引用。

## 4. 拥有线程 API

- `break_runtime_metrics_snapshot(reg, out, capacity, out_count)`：把当前所有槽拷进调用方数组（`name`/`kind`/`value`），升序按创建顺序。容量不足 → `OVERLOAD` 且 `out_count` 返回所需条数。非拥有线程 → `REJECTED`。
- `break_runtime_metrics_encode(reg, buf, capacity, out_len)`：把快照编码成稳定文本行格式，一行一指标：

  ```
  BRKM1 <name> <kind> <value>\n
  ```

  `BRKM1` 是版本前缀（Break Runtime Metrics v1），`<kind>` 为 `counter`/`gauge`，`<value>` 十进制 `u64`。行按创建顺序输出。`buf` 不足 → `OVERLOAD` 且 `out_len` 返回所需字节（不含 NUL），`buf`（capacity>0 时）置空。这一格式供远程采集器逐行解析，字段定长、无需转义（name 禁止空白与换行，创建时校验）。
- `break_runtime_metrics_stats(reg, out)`：可观测计数（`tracked` 当前槽数、`overflow_drops`、`saturations`、`updates`、`closed_rejects`），任意状态合法。

## 5. 生命周期

- `create(config,out)`：config 可为 NULL（取默认容量）。count 与 byte 校验先于分配。调用线程成为拥有线程。
- `close`：停止 `add`/`set`（→ CLOSED），幂等，NULL no-op。快照/编码在关闭后仍可读（用于最终导出）。
- `destroy`：释放注册表，NULL no-op；无 worker 线程，生产者静默后任意状态可调。

## 6. 错误分类

- `INVALID`：NULL 参数、空/超长 name、name 含空白、kind 不符、config 容量越界、快照/编码缓冲不足以外的参数错误。
- `REJECTED`：从非拥有线程 snapshot/encode。
- `CLOSED`：关闭后 add/set。
- `OVERLOAD`：槽满（record）或缓冲不足（snapshot/encode）。
- `OOM`：create 分配失败。

## 7. 边界

本块只交付进程内注册表与文本编码。远程传输（把编码推给采集器）、历史采样（时间序列保留）与聚合窗口仍未实现（阈值告警求值见第 14 节）；指标值的语义绑定（哪些子系统注册哪些 name）由各消费者在后续切片接线，本库不预置任何业务 name。既有 Lua/TSan、条件 skip 与完整 sanitizer 边界不变。

## 8. 子系统接线：Bus 聚合导出（第一处 name 绑定）

`break_runtime_bus_export_metrics(bus, metrics)`（`runtime_bus.h`）把消息总线的累计计数汇总后写入注册表，作为第一处真实 name 绑定，验证注册表设计：

- 导出的 9 个量：`bus.published`、`bus.delivered`、`bus.dropped`、`bus.version_rejects`、`bus.size_rejects`、`bus.quota_rejects`（按 kind 求和）、`bus.unknown_kind_rejects`（总线级）、`bus.kinds`、`bus.subscribers`（计数）。
- 全部以 **GAUGE** 写入（`set`），而非 counter。总线自身的计数是累计值，用 gauge 覆盖当前累计值使「重复导出同一累计值」幂等、不会二次累加；下次总线前进后再导出，gauge 自然抬升。
- 锁序：先在总线锁下求和，释放总线锁后再进注册表（注册表自带 leaf 锁，不得在持总线锁时进入），与 profiler 的锁序约定一致。
- 任一 `set` 失败（槽满、关闭、kind 不符）立即返回该错误并停止导出，可能已落部分 gauge；调用方应保证注册表容量足够（≥9 加上其它来源）。

这不改变第 7 节边界：仍无远程传输、历史采样与告警；这只是把一个子系统的既有计数接到注册表，后续子系统按同样方式各自接线。


## 9. 子系统接线：Queue 计数导出（按前缀）

`break_runtime_queue_export_metrics(queue, metrics, prefix)`（`runtime_queue.h`）把单个队列的观测计数写入注册表。队列是多实例（每个订阅者一个），因此按调用方给的 `prefix` 命名，导出 6 个 GAUGE：`<prefix>.enqueued`、`.dequeued`、`.overload_rejects`、`.stale_rejects`、`.closed_rejects`、`.high_water`。

- 同样用 GAUGE（`set`）使重复导出幂等；不同 `prefix` 并存，互不覆盖。
- `prefix` 为 NULL/空 → `INVALID`；过长 prefix 使 `<prefix>.overload_rejects` 超出注册表 name 预算时，由 `break_runtime_metrics_set` 返回 `INVALID` 并停止导出（不静默截断）。
- 先取队列 stats（队列自有锁），再进注册表 leaf 锁，不交叉持锁。

这不改变第 7 节边界。Bus（§8）与 Queue（§9）是前两处子系统 name 绑定；task、world session 等后续各自按同样方式接线。


## 10. 子系统接线：Task 队列计数导出（按前缀）

`break_runtime_task_queue_export_metrics(queue, metrics, prefix)`（`runtime_task.h`）把任务队列的 8 个观测计数按 `prefix` 写入注册表为 GAUGE：`<prefix>.submitted`、`.forwarded`、`.overload_rejects`、`.closed_rejects`、`.forward_rejects`、`.high_water`、`.completions_published`、`.completions_dropped`。与 queue（§9）同构：gauge 幂等、按前缀多实例并存、过长 prefix 由注册表 name 校验回 INVALID、先取 stats 再进注册表 leaf 锁。Bus（§8）、Queue（§9）、Task（§10）为前三处子系统 name 绑定；world session 等后续接线。这不改变第 7 节边界。


## 11. 子系统接线：World Session 适配器计数导出（按前缀）

`break_runtime_world_session_export_metrics(adapter, metrics, prefix)`（`runtime_world_session.h`）把 Runtime World Session 适配器的观测计数按 `prefix` 写入注册表为 11 个 GAUGE：`<prefix>.submitted`、`.drained`、`.applied`、`.rejected`、`.stale_rejected`、`.transport_overloads`、`.queued`、`.publish_overloads`、`.publish_terminal`、`.control_pending`、`.publish_pending`（后两个 Boolean 作 0/1 gauge）。单调 `next_sequence` 是身份而非指标，不导出。与 queue/task 同构：gauge 幂等、按前缀多实例、过长 prefix 由注册表 name 校验回 INVALID、取 stats 快照（任意线程）后进注册表 leaf 锁。Bus（§8）、Queue（§9）、Task（§10）、World Session（§11）为前四处子系统 name 绑定。这不改变第 7 节边界。


## 12. 子系统接线：Reload 协调器计数导出（按前缀）

`break_runtime_reload_export_metrics(reload, metrics, prefix)`（`runtime_reload.h`）把热重载协调器的 18 个观测计数按 `prefix` 写入注册表为 GAUGE：`<prefix>.requested`、`.merged`、`.events_notified`、`.events_coalesced`、`.event_overloads`、`.events_deferred`、`.committed`、`.failed_keep_old`、`.cancelled`、`.timed_out`、`.oom`、`.request_overloads`、`.commit_overloads`、`.closed_rejects`、`.stale_rejects`、`.stale_drops`、`.active`、`.high_water`。与前几处同构：gauge 幂等、按前缀多实例、过长 prefix 由注册表 name 校验回 INVALID、取 stats 快照后进注册表 leaf 锁。Bus（§8）、Queue（§9）、Task（§10）、World Session（§11）、Reload（§12）为前五处子系统 name 绑定。这不改变第 7 节边界。


## 13. 子系统接线：IO facade 计数导出（按前缀）

`break_runtime_io_export_metrics(metrics, prefix)`（`runtime_io.h`）把进程级 IO facade 的 13 个观测计数按 `prefix` 写入注册表为 GAUGE：`<prefix>.submitted`、`.completed`、`.failed`、`.cancelled`、`.timed_out`、`.overload_rejects`、`.closed_rejects`、`.stale_drops`、`.bytes_published`、`.notices_published`、`.notices_dropped`、`.active`、`.high_water`。IO facade 是进程单例（无句柄），故无实例维度但仍按 `prefix` 命名以便与其它来源区分。与前几处同构：gauge 幂等、过长 prefix 由注册表 name 校验回 INVALID；未 init 时 `break_runtime_io_stats` 的 INVALID 由导出透传。Bus（§8）、Queue（§9）、Task（§10）、World Session（§11）、Reload（§12）、IO（§13）为 runtime_core 全部六个带 stats 的子系统的 name 绑定。这不改变第 7 节边界。

## 14. 阈值告警求值

`break_runtime_metrics_evaluate_alerts(samples, sample_count, rules, rule_count, fired, fired_capacity, out_count)` 是无状态纯函数，任意线程可调：对一份快照（通常是 `break_runtime_metrics_snapshot` 的输出）逐条求值 `BreakRuntimeMetricAlertRule{name, op, threshold}`。`ABOVE` 在值**严格大于**阈值时触发，`BELOW` 在值**严格小于**阈值时触发，等于阈值不触发；快照中不存在该 name 的规则不触发。触发规则的下标按规则顺序写入 `fired`。

- `fired` 不足 → `OVERLOAD`，`*out_count` 为所需数量，`fired` 不写。
- `INVALID`（`*out_count = 0`）：`out_count` 为 NULL；计数非零而 samples/rules/fired 为 NULL；规则 name 为 NULL 或 op 未知；样本数或规则数超过 `BREAK_RUNTIME_METRICS_MAX_CAPACITY`。所有规则先校验后求值，不会部分写出。
- 不保留状态：不做去抖、持续时长、恢复通知或告警投递；这些与历史采样一起留待后续。
