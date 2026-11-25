# Runtime World Session 逐连接诊断快照设计

日期：2026-11-26  
状态：设计完成，待实施。本文新增 API 均为提案，当前源码尚未实现。

## 目标

Runtime World adapter 目前只暴露进程级聚合统计（`BreakRuntimeWorldSessionStats`）。当发布卡住、pending 不归零或某条连接持续 OVERLOAD 时，运维无法回答“是哪条连接、卡在哪个阶段”。本切片增加**只读、按连接**的诊断快照查询，让 owner 侧能定位具体连接，而不读取或修改 World Session 内部状态。

## 非目标

- 不新增或修改任何 wire 消息（BRWC/BRWD/BRFG、0x5753、0x5754 全部不变）。
- 不暴露 World Session 私有 attempt 字节、快照内容或 lease。
- 不引入回调、不推送事件、不做指标导出格式或远程上报。
- 不改变 drain 行为、pending 语义、`fair_outbound_admission` 默认值或 shutdown 顺序。
- 不把诊断查询变成可写入口；查询不得推进状态机。

## 公共合同

```c
typedef struct {
    u64 connection_key;
    u64 connection_epoch;
    u64 completed_publication_epoch;
    u64 terminal_publication_epoch;
    u64 attempt_publication_epoch;
    u64 attempt_target_snapshot_id;
    u64 attempt_target_tick;
    bool retry_publish;
    bool publish_dirty;   /* 该连接相对最近一次 drain 仍待发布 */
} BreakRuntimeWorldConnectionSnapshot;

/* 返回 0..max_connections 中实际打开的连接数；按 slot 升序写入。
 * out_snapshots 可为 NULL，此时只返回计数。
 * capacity 为 0 时也只返回计数。 */
usize break_runtime_world_session_connection_snapshots(
    const BreakRuntimeWorldSession *adapter,
    BreakRuntimeWorldConnectionSnapshot *out_snapshots,
    usize capacity);
```

### 语义

- 只读：持 adapter mutex 复制标量，不调用 World Session、publication 或 queue。
- 只返回 `connection_key != 0` 的槽位，调用方无需知道 slot 编号。
- 顺序稳定：按 adapter 内部 slot 升序；同一时刻两次查询顺序一致。
- `capacity < 打开连接数` 时写入前 `capacity` 项并返回**实际打开连接数**，让调用方据此扩容重查；不得返回被截断的计数。
- `adapter == NULL` 返回 0。
- `publish_dirty` 定义：`retry_publish || completed_publication_epoch != 最近观察到的 publication epoch || terminal_publication_epoch != 最近观察到的 publication epoch`，与 `runtime_world_recompute_continuation` 的单连接判据一致；从未 drain 过（`publish_observed_epoch == 0`）时为 `retry_publish || attempt_publication_epoch != 0`。
- 字段直接来自该连接的 `RuntimeWorldConnection` 标量，不展示 World Session 的真实 attempt 状态；`attempt_*` 为 adapter 记录的判账值，未知时为 0。

### 默认兼容

- 新结构体与函数只追加，不改变任何已有结构体布局、函数签名或行为。
- 未配置 publication 的 adapter 同样可查询，`publish_dirty` 只在控制路径下为 false。
- 现有测试与调用方无需修改；新 API 不参与 pending、stats 或 lifecycle。

## 线程模型

与 `break_runtime_world_session_stats()` 一致：可在任意线程调用，持 adapter mutex 短临界区复制。不得在持有该 mutex 的 owner 路径内重入调用（现有 API 同样如此）。

## 测试策略

RED 在前，用现有 `Fixture` 构造两种 adapter：

1. 空 adapter：返回 0；`out_snapshots == NULL` 与 `capacity == 0` 均安全。
2. 三连接、capacity 递增 0/1/2/3：分别返回打开数，写入项按 slot 升序，key/epoch 正确，超出部分不写入且返回完整计数。
3. 发布后：`completed_publication_epoch` 反映最近 drain 的 epoch，`publish_dirty` 在 clean skip 后为 false。
4. OVERLOAD 连接：`retry_publish == true`、`attempt_target_*` 非零、`publish_dirty == true`，另一条连接不受影响。
5. CLOSE 后该 key 消失、计数减一；REBASELINE 后计数不变但 epoch 状态重置。
6. 只读性：查询前后 `BreakRuntimeWorldSessionStats`、`pending()`、World Session sender state 完全相等（`memcmp`）。
7. 线程：生产者线程持续 submit，owner 线程反复查询，断言不崩溃、每次返回的连接数不超过 `max_connections`；用原子 barrier，不用 sleep。

定向变异：

- 把只读复制改为返回未加锁指针 → ASan/TSan 或 memcmp 断言判红。
- 截断时返回 `capacity` 而非打开数 → capacity=1 用例判红。
- 把 `publish_dirty` 恒置 false → OVERLOAD 用例判红。
- 让查询清除 `retry_publish` → 只读性用例判红。

验证：`test_runtime_world_session` normal/ASan+UBSan（显式 `detect_leaks=1`）/TSan，外加 focus 的正常回归；不新增 wire 或平台专项。

## 文档与验收

- `docs/design/runtime_network.md`、`docs/design/runtime_overview.md` 各追加 2026-11-26 小节，说明逐连接只读诊断、字段语义与“不是权威 World 状态”。
- `docs/Implementation_Status.md`、`docs/cross_engine/missing_capabilities.md` 追加记录；明确仍缺远程指标导出、历史采样和告警。
- 独立任务评审、整分支评审后推送并在最终 HEAD 跑双后端完整 CTest 与合同，再写远端收据。

## 实施任务

1. **库级只读快照**：`runtime_world_session.h/.c` 增加结构与函数，`test_runtime_world_session.c` 覆盖上述 1–6，完成四项变异。
2. **线程与文档**：真线程用例、两份设计文档、状态与缺口文档，最终本地与远端验收。
