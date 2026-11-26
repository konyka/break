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

本块只交付进程内注册表与文本编码。远程传输（把编码推给采集器）、历史采样（时间序列保留）、聚合窗口与告警规则仍未实现；指标值的语义绑定（哪些子系统注册哪些 name）由各消费者在后续切片接线，本库不预置任何业务 name。既有 Lua/TSan、条件 skip 与完整 sanitizer 边界不变。
