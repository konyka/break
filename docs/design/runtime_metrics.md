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

本块只交付进程内注册表与文本编码。远程推送见第 20 节，采集端的严格解码见第 19 节（阈值告警求值见第 14 节，有界历史采样见第 15 节，计数器窗口增量见第 18 节）；指标值的语义绑定（哪些子系统注册哪些 name）由各消费者在后续切片接线，本库不预置任何业务 name。既有 Lua/TSan、条件 skip 与完整 sanitizer 边界不变。

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
- 不保留状态：持续时长去抖见第 16 节，触发/恢复边沿见第 17 节，投递见第 21 节。

## 15. 有界历史采样

`BreakRuntimeMetricsHistory` 是调用方持有的定长环：`depth` 帧（1..`BREAK_RUNTIME_METRICS_HISTORY_MAX_DEPTH`=256），每帧至多 `width` 个样本（0 取默认 64，上限 `BREAK_RUNTIME_METRICS_MAX_CAPACITY`），仅在 create 时分配。单线程、无锁；`record()` 内部调用 `break_runtime_metrics_snapshot`，因此必须在该注册表的拥有线程上调用。

- `break_runtime_metrics_history_record(history, metrics, tick)`：快照注册表写入新帧并打上调用方提供的 `tick`；环满时覆盖最旧帧（计入 `evicted`）。`tick` 必须严格大于上一帧，否则 `INVALID`。快照宽于 `width` → `OVERLOAD`（计入 `width_drops`），环不变；非拥有线程的 `REJECTED` 透传，环不变。快照先写入独立 scratch，成功后才提交，失败不会污染已有帧。
- `break_runtime_metrics_history_frame(history, age, out, capacity, out_count, out_tick)`：取回第 `age` 新的帧（0 为最新）。无该帧 → `STALE`、`*out_count = 0`；`out` 不足 → `OVERLOAD` 并报所需数量；`out_tick` 可为 NULL。
- `break_runtime_metrics_history_stats`：`recorded`/`evicted`/`width_drops`/`frames`。
- 边界：不做降采样、聚合窗口或速率计算，也不持久化；帧可直接交给第 14 节的告警求值。

## 16. 持续告警（去抖）

`break_runtime_metrics_history_evaluate_alerts(history, rules, rule_count, sustain, fired, fired_capacity, out_count)` 在第 15 节的历史环上求值：一条规则只有在**最新 `sustain` 帧每一帧**都按第 14 节语义触发时才算触发，单帧尖峰不会报警。保留帧数少于 `sustain`（包括 `sustain` 大于环深度）时不触发，因为窗口未被证实。输出顺序、`OVERLOAD` 与规则校验同第 14 节；另外 history 为 NULL、`sustain` 为 0 或超过 `BREAK_RUNTIME_METRICS_HISTORY_MAX_DEPTH` 回 `INVALID`。与历史环同线程调用，无状态。恢复通知的边沿见第 17 节；告警投递仍未实现。

## 17. 告警边沿（触发与恢复）

`break_runtime_metrics_history_alert_edges(history, rules, rule_count, sustain, edges, edge_capacity)` 比较两个持续窗口：以最新帧结尾的窗口与早一帧结尾的窗口（各 `sustain` 帧，语义同第 16 节）。每条规则输出一个 `BreakRuntimeMetricAlertEdge`：`STEADY`（未变）、`RAISED`（在最新帧开始触发）、`CLEARED`（在最新帧恢复）。帧数不足的窗口视为不触发，因此第一次被证实的窗口报 `RAISED`。

- `sustain` 必须小于历史深度（`INVALID` 否则），保证环满后上一窗口仍可证实；其余校验同第 16 节。`edge_capacity < rule_count` → `OVERLOAD`。任何错误都不写 `edges`。
- 无状态：调用方每记录一帧调用一次，即可对每次转变恰好得到一次边沿；漏调会漏掉中间转变。边沿的文本编码与投递见第 21 节。

## 18. 计数器窗口增量（速率）

`break_runtime_metrics_history_delta(history, name, span, out_delta, out_ticks)` 返回 COUNTER `name` 在第 `span` 旧帧与最新帧之间的增长：`*out_delta = 最新值 - 旧值`，`*out_ticks`（可为 NULL）为两帧 tick 差。调用方用二者自行算速率，本库不引入浮点。

- `STALE`：保留帧不足 `span + 1`（环满时 `span` 等于深度会回绕到最新帧本身，故同样 STALE）、任一帧缺该 name、旧帧不是 counter 或旧值大于新值（不可比）。
- `INVALID`：history/name/out_delta 为 NULL、`span` 为 0、最新帧中该 name 是 GAUGE（gauge 可下降，差值不是增长）。
- 任何错误不写输出；与历史环同线程。不做多帧平均、分位数或降采样。

## 19. 采集端严格解码

`break_runtime_metrics_decode(text, len, out, capacity, out_count)` 是 `encode` 的逆，供远程采集器解析**不可信**字节；纯函数，任意线程。`text` 按长度读取，不要求 NUL 结尾。

- 每行必须严格为 `BRKM1 <name> <counter|gauge> <value>\n`：name 同注册表规则（1..47 字节、无 ≤0x20 字节）；value 为规范十进制（无符号、无前导零，"0" 除外），不超过 `UINT64_MAX`；单空格分隔、仅 LF 行尾（CR 非法）、无空行、无重复 name、行数不超过 `BREAK_RUNTIME_METRICS_MAX_CAPACITY`。内嵌 NUL 因不属于合法 name 字节而被拒。
- 任何违规 → 整体 `INVALID`，`*out_count = 0`，`out` 不写；合法输入但 `capacity` 不足 → `OVERLOAD` 并报所需行数，`out` 不写。格式错误优先于容量不足。
- 空输入合法（0 行）。round-trip：`decode(encode(snapshot))` 与 `snapshot` 逐项相等。
- 不含传输本身：HTTP 推送见第 20 节。

## 20. HTTP 推送到采集器

`break_runtime_metrics_push_http(ctx, metrics)`（`engine/src/runtime/runtime_metrics_push_http.{c,h}`）把注册表当前编码 POST 到 `<base_url>/metrics`，`Content-Type: text/x-break-metrics`。它是独立静态库 `runtime_metrics_push_http`（依赖 `runtime_core` 与 `break_http`），与 `break_crash_upload_http` 同构：`runtime_core` 归档保持无网络符号，engine/engine_demo/dxx_break/editor 不链接它。

- 传输规则沿用 `break_http`：https 必须给 CA 文件，明文 http 只允许回环地址，不跟随重定向，连接与总 I/O 时间有界。
- 只有完整的 HTTP 200 回答算 `OK`；连接/TLS 失败、超时、URL 被拒、非 200、畸形回答一律 `FAILED`，重试由调用方安排。
- 本地拒绝且不发起连接：ctx/metrics 为 NULL、base URL 为空/无 NUL/以 `/` 结尾/拼接后超长 → `INVALID`；非注册表拥有线程 → `REJECTED`；编码超过 `BREAK_RUNTIME_METRICS_PUSH_HTTP_MAX_BYTES`（64 KiB）→ `OVERLOAD`；编码缓冲分配失败 → `OOM`。
- 先以零容量 encode 取所需长度，再按长度一次分配并编码；空注册表推送空 body。
- 调用阻塞至多 `break_http` 的时间预算，应放在诊断线程步进中，不能在热路径调用。仅 POSIX（同 `break_http`）；无 Windows 实现。告警投递见第 21 节。

## 21. 告警边沿编码与投递

`break_runtime_metrics_encode_alert_edges(rules, edges, count, buf, capacity, out_len)`（`runtime_metrics.h`，纯函数，任意线程）把第 17 节的边沿编码为稳定文本，每个**非 STEADY** 边沿一行，按规则顺序：

```
BRKA1 <raised|cleared> <name> <above|below> <threshold>\n
```

STEADY 不产生输出，全 STEADY 编码为空串。缓冲不足 → `OVERLOAD` 并报所需长度、`buf` 置空；规则 name 不符合注册表规则（以保证行可按空格切分）、op 或边沿值未知、NULL 数组、数量超上限 → `INVALID`，先校验后写出。

`break_runtime_metrics_push_alerts_http(ctx, rules, edges, count)`（`runtime_metrics_push_http.h`）把编码 POST 到 `<base_url>/alerts`，`Content-Type: text/x-break-alerts`，传输规则与第 20 节相同。没有转变时不发请求并返回 `OK`；只有 HTTP 200 为 `OK`，其余传输结果 `FAILED`；输入被编码器拒绝、base URL 非法 → `INVALID`；超过 64 KiB → `OVERLOAD`，均不发起连接。不触碰注册表，任意线程可调，但会阻塞，应放在诊断线程步进中。

典型接线：每次 `history_record` 之后调用 `history_alert_edges`，再把结果交给 `push_alerts_http`；投递失败时由调用方决定是否重发同一批边沿。不做重试队列、去重或多渠道路由。

## 22. 投递失败的有界重试队列

第 20、21 节的推送在失败时只返回 `FAILED`，不自行重试，所以想要 at-least-once 的调用方
原先必须自己维护 backlog。`BreakRuntimeMetricsRetryQueue`（`runtime_metrics.{h,c}`）就是这个
backlog：调用方持有的定长 FIFO，存放**已编码**的 payload 字节。它不起线程、不自行重试、
不做任何 I/O，由所有者在诊断线程步进中驱动。

- **所有权**：与注册表同构，所有调用仅限创建线程（其他线程 `REJECTED`）。因为只有所有者
  访问，实现不加锁；全部存储在 create 时一次分配，`enqueue` 不再分配。
- **容量**：`capacity`（1..256 条）与 `max_payload_bytes`（1..64 KiB，与推送的 64 KiB 上限
  一致）。零值或越界在 create 时 `INVALID`，分配失败 `OOM`。
- **满队列丢最旧**：队满时先淘汰最旧一条（计入 `dropped_oldest`）再接纳最新一条，仍返回
  `OK`。取向是“最新的遥测更有价值”，而不是拒收新数据。
- **逐条 attempts**：每条记录自己的投递尝试次数，`record_attempt` 对队首加一（在
  `UINT32_MAX` 饱和）并回报新值，调用方据此放弃毒 payload。槽位复用时 attempts 必须归零。
- **borrow 语义**：`peek` 借出队首字节，指针在下一次 `enqueue`/`release`/`destroy` 前有效；
  空队列时 `peek`/`record_attempt`/`release` 均为 `STALE`，不写输出。
- **统计**：`queued`、`enqueued`、`dropped_oldest`、`released`、`attempts`。

典型接线：`push_http`/`push_alerts_http` 返回 `FAILED` 时把这次编码的字节 `enqueue`；
每次诊断步进 `peek` 队首重发，成功则 `release`，失败则 `record_attempt`，attempts 超过
调用方阈值时 `release` 丢弃。队列只保存字节，不关心是 metrics 还是 alerts 编码。

仍不做：按渠道分队列、去重、批量合并、压缩、持久化到磁盘，以及自动退避计时（退避策略由
调用方的步进节奏决定）。

## 23. 重试队列的排空循环

第 22 节只提供 peek/record_attempt/release 原语，每个调用方都要自己写同一个循环。
`break_runtime_metrics_retry_drain(queue, send, user, max_sends, max_attempts, out)` 把它收进
库里：从队首开始，最多调用 `send` `max_sends` 次。

- `send` 返回 OK：释放该条，计入 `delivered`，继续下一条。
- `send` 返回其他值：记一次 attempt，计入 `failed`。若该条 attempts 已达到 `max_attempts`
  （0 表示永不放弃），释放并计入 `abandoned`，继续下一条；否则立即停止，让调用方等到下一次
  诊断步进再试（退避节奏由步进频率决定）。
- 空队列返回 OK 且计数全零；NULL queue/send/out 或 `max_sends == 0` 为 INVALID；非所有者
  线程 REJECTED。函数本身不做 I/O，`send` 通常包一层 `break_runtime_metrics_push_http` 一类的
  推送，阻塞时长由它决定，所以应放在诊断线程上调用。

停在第一次未达上限的失败上，是为了在采集端不可用时不把整个 backlog 连续打一遍。

验证：`test_runtime_metrics` 新增 4 例（共 39 例）：在发送预算内按序投递、失败后停止并保留
该条、毒 payload 达到上限后丢弃并继续、参数校验。五项变异判红：失败后继续、忽略发送预算、
永不放弃、上限比较差一、成功后不释放。

## 24. 重复 payload 的折叠（去重）

第 22 节的队列默认保留每一次 enqueue。采集端长时间不可用时，调用方往往把同一份未变化的
注册表编码反复推失败、反复入队；在满队列丢最旧的策略下，这些重复会把真正不同的遥测挤掉。
`BreakRuntimeMetricsRetryConfig.coalesce_repeats`（默认 false）打开后，若新 payload 与**最新
一条**长度相同且字节相同，则不存储，只计入 `coalesced` 并返回 OK。

只比较最新一条，所以检查是 O(payload)、不扫环；环中非相邻的重复仍会保留（队列不做全局
去重，那需要哈希索引且会改变 FIFO 语义）。长度必须相等才算重复，前缀不算。队列排空后不再
有比较目标，下一次 enqueue 照常存储。

默认关闭，既有调用方行为逐位不变。

验证：`test_runtime_metrics` 新增 3 例（共 42 例）：连续重复折叠且不同 payload 与前缀照常
入队、只与最新一条比较（环中旧的同值仍存储、全部释放后不误折叠）、关闭时每次重复都保留。
四项变异判红：忽略配置开关、与最旧一条比较、跳过长度检查、跳过字节比较。

## 25. 排空期间的重入保护

第 23 节的 `retry_drain` 把指向环内存储的指针交给 `send` 回调。复查时发现：若回调里重入调用
`enqueue`，在小环上会环绕覆盖**正在发送的那个槽位**，使回调手里的字节在发送途中被改写。
用一个 2 槽环、回调里连续 enqueue 两次的探针复现：发送中的 payload 首字节由 `a` 变为 `X`。
没有内存越界（ASan 无报告），但调用方可能把损坏的数据发出去，属于静默的数据完整性缺陷。

修复：队列在调用 `send` 前置 `draining`，返回后清除；期间 `enqueue`、`release` 与嵌套
`drain` 一律返回 `REJECTED`。drain 自身改用内部 `retry_pop` 与内联的 attempt 记账，
不经过被保护的公开入口。回调里发现的新 payload 应在 drain 返回后再入队。修复后同一探针不再
出现改写。

验证：`test_runtime_metrics` 新增 1 例（共 43 例），断言回调内 enqueue 得到 REJECTED、该次
投递仍然成功、drain 返回后 enqueue 恢复正常。两项变异判红：去掉 enqueue 的 draining 检查、
从不设置 draining。

这一缺陷是在没有新需求的情况下，对已推送代码做复查时发现的；原有测试只覆盖了「正常的」
回调，不能证明回调可以安全地触碰队列。

## 26. Windows 推送的前置条件（勘察，未实现）

第 20/21 节的 HTTP 推送标注「仅 POSIX」。勘察确认根因在底层传输：`break_http`
（`engine/src/net_http/break_http.{h,c}`）头部明确写明「POSIX only (sockets, poll). Windows is
not implemented.」，直接用 BSD socket 与 `poll`。`runtime_metrics_push_http` 只是其薄封装，
本身没有平台分支。

因此「Windows 指标推送」不是指标层的小切片，而要先把 `break_http` 的 socket/poll 层移植到
Winsock（`WSAStartup`、`SOCKET`、`WSAPoll`、错误码映射、TLS 的平台证书存储取舍等），属于独立
网络子系统移植。本机无 Windows 环境、Windows CI 通道当前排队未执行，无法在此验证，故不在此
实现，如实记为前置条件未满足；待 `break_http` 具备 Windows 传输后，推送层预计只需放宽
`_POSIX_C_SOURCE` 守卫即可复用。

## 27. 推送 + 重试队列 + 排空的组合（集成测试）

第 20/22/23 节的部件（HTTP 推送、重试队列、排空循环）按设计分别把重试调度留给调用方。
`test_runtime_metrics_push_http` 新增一个集成用例，证明它们按文档描述的方式组合成 at-least-once
投递，而不在库里新增编排代码（那会违反各自「重试由调用方安排」的边界）：

1. 向回环假采集端推送，采集端答 503 → `FAILED`；调用方把该次 `encode` 的字节 `enqueue` 进
   重试队列。
2. 稍后采集端恢复答 200，`retry_drain` 的 send 回调把队首字节解码重建为临时注册表并
   `push_http`；成功即 `delivered` 并 `release`，队列清空。

断言覆盖：失败后 `queued==1`；排空后 `delivered==1`、`failed==0`、`queued==0`、`released==1`，
且第二个采集端确实收到 `POST /metrics`。normal/ASan+UBSan（含 leak 检测）/TSan 均 10/10
（回环 socket + 线程，TSan 有意义）。这是集成证据，不改产品代码。

## 28. 历史窗口聚合（min/max/mean）

第 19 节的 `history_delta` 只看「最新帧 vs 第 span 旧帧」两端点，无法回答「最近 N 帧里
队列深度的波动区间与均值」这类问题。`break_runtime_metrics_history_aggregate(history, name,
window, out_min, out_max, out_mean, out_counted)` 在最新 `window` 帧（age 0 .. window-1）上
对 `name` 的每帧值求 min、max 与整型 mean（`sum / counted`，截断），并用 `out_counted` 报告
`window` 帧里有多少帧实际含该指标。COUNTER 与 GAUGE 通用（kind 由调用方自知）。任一 out 指针
可为 NULL。

边界与安全：

- `sum` 以饱和加法累计（`sum > UINT64_MAX - value` 时钳到 `UINT64_MAX`），因此长窗口的
  COUNTER 聚合不会静默回绕；mean 退化为 `UINT64_MAX / counted`，而非回绕后的小值。
- 只统计含 `name` 的帧：窗口内某帧缺该指标时跳过且不计入 `counted`，均值分母用实际帧数而非
  `window`，避免被缺帧稀释。
- 窗口内全部帧都无该指标 → `STALE`，不写任何 out（调用方的旧值不被污染）。
- 历史为空或 `window` 超过已保留帧数 → `STALE`。NULL history/name 或 `window==0` → `INVALID`。
- 与历史同线程调用，纯读，无锁。

测试（`test_runtime_metrics.c`）：窗口 min/max/mean 与 NULL out；仅统计在场帧 + 全缺帧 STALE；
饱和不回绕（帧 0=UINT64_MAX、帧 1=2，证明钳制值与回绕值不同）；参数校验（空历史、超窗、
NULL、window 0）。5/5 变异全部被捕获（min/max 比较翻转、关闭饱和、mean 除以 window、把缺帧
计入 counted）。normal/ASan+UBSan/TSan 下 47/47，runtime_core 标签 12/12（ASan）。
