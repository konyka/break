# Runtime World 发布进度摘要设计

日期：2026-11-26  
状态：设计完成，待实施。新增 API 为提案，当前源码尚未实现。

## 目标

现有诊断只有两种粒度：adapter 聚合统计（`submitted/drained/publish_overloads/publish_terminal/publish_pending`）与逐连接快照。运维还缺一个问题：“publish-current 这条链最近推进到哪个 publication epoch，还有几条连接没完成、有没有待处理的 request？”本切片增加一个**只读的 adapter 级发布进度摘要**，不新增 wire，不引入指标协议，也不暴露快照内容。

## 非目标

- 不做 Prometheus/OpenMetrics 导出，不打开 HTTP 或任何网络监听。
- 不做历史采样、滑动窗口、告警或远程上报。
- 不改变 drain、pending、判账或 shutdown 行为；查询不得推进状态机，也不得调用 World Session 或 publication。
- 不暴露 snapshot id 之外的快照内容、attempt 字节或 lease。

## 公共合同

```c
typedef struct {
    u64 observed_publication_epoch; /* 最近一次 drain acquire 到的 publication epoch；0 表示尚未 drain 过 */
    u32 open_connections;           /* 当前已打开连接数 */
    u32 dirty_connections;          /* 仍需发布的连接数，判据同 BreakRuntimeWorldConnectionSnapshot.publish_dirty */
    bool request_pending;           /* 有 notice 已消费但尚未在批次末尾 fanout */
    bool continuation_pending;      /* 仍有跨 drain 的 fanout 未完成 */
} BreakRuntimeWorldPublishProgress;

/* 持 adapter mutex 复制标量；adapter==NULL 时输出全零并返回 false。
 * 不调用 World Session、publication 或 queue，不改变任何状态。 */
bool break_runtime_world_session_publish_progress(
    const BreakRuntimeWorldSession *adapter,
    BreakRuntimeWorldPublishProgress *out_progress);
```

### 语义

- `observed_publication_epoch` 为 adapter 最近一次在 drain 中 acquire 到的 lease epoch；与逐连接快照使用同一个值，因此两者的“当前 epoch”口径一致。
- `dirty_connections` 用与 `publish_dirty` 完全相同的单连接判据计数，避免两处口径分叉。
- `open_connections` / `dirty_connections` 是同一临界区内的一致快照，不会出现“连接数小于脏连接数”这种跨快照错位。
- `request_pending` / `continuation_pending` 直接取自 adapter 布尔字段，用于区分“还没开始处理 notice”与“处理到一半还在续发”。
- 只读：不写 retry、不改 pending、不清 request/continuation。

## 线程模型

与 `stats()` 和逐连接快照一致：任意线程可调用，持 adapter mutex 一段短临界区。不得在已持有该 mutex 的 owner 路径里重入。

## 测试策略

1. 新建 adapter：全部为零/`false`，返回 `true`；`adapter == NULL` 返回 `false` 且输出清零。
2. 打开三连接、未发布：`open_connections == 3`、`dirty_connections == 0`、`observed_publication_epoch == 0`。
3. 发布 S1 并 drain 一次后：`observed_publication_epoch == 1`、`request_pending == false`；budget=1 时 `continuation_pending == true` 且 `dirty_connections` 等于尚未服务的连接数；空 queue 再 drain 后 `continuation_pending == false`、`dirty_connections == 0`。
4. 只读性：查询前后 `stats()`、`pending()`、逐连接快照逐字节不变。
5. 与逐连接快照一致性：`dirty_connections` 等于逐连接快照中 `publish_dirty` 为真的条目数。

定向变异：

- 让 `dirty_connections` 恒为 0 → 用例 3/5 判红。
- 让查询清零 `request_pending`/`continuation_pending` → 只读性用例判红。
- 用两次独立加锁分别统计连接数与脏连接数 → 一致性用例在并发下判红（或用测试钩子模拟中间状态）。

验证：`test_runtime_world_session` normal / ASan+UBSan（`detect_leaks=1`）/ TSan，加双后端完整 CTest。

## 文档与验收

- `docs/design/runtime_network.md`、`docs/design/runtime_overview.md` 各追加 2026-11-26 小节，说明摘要与连接级快照、`pending()` 的分工。
- `docs/Implementation_Status.md` 与 `docs/cross_engine/missing_capabilities.md` 追加记录，明确仍无指标协议、历史采样与告警。
- 独立任务评审与整分支评审后推送，最终 HEAD 跑双后端与合同，再写远端收据。

## 实施任务

1. **库级摘要与测试**：结构体、函数、上述 1–5 与三项变异。
2. **文档与最终验收**：四份文档、双后端、评审、推送与收据。
