# 复制分片重组超时与驱逐实施计划（2026-11-23）

## 背景

`break_replication_reassembler` 一次只重组一个 delta。若某个分片永久丢失，未完成的 stream 会一直占用内存（最多 16 MiB），直到更新的 delta 到达。`ecs_snapshot_replication_aoi.md`、`runtime_asset_streaming.md` 与 `runtime_hot_reload.md` 都把 fragment timeout/eviction 列为未实现。

## 契约

- 时间由调用者提供（单调时钟，任意单位的 `uint64_t now`），模块不读墙钟，便于确定性测试。
- `break_replication_reassembler_push_at(r, fragment, now, payload, size)`：与 `push` 相同，并记录当前未完成 stream 最近一次被接受的分片时间（开始、新分片或重复分片都刷新）。`push` 等价于不更新时间戳的旧行为，保持兼容。（评审后修订：由 `push` 开始的 stream 为“未计时”，`expire` 不驱逐；`push_at` 只在开始新 stream、取代旧 stream 或刷新已计时 stream 时记录时间；被拒绝的分片从不刷新。）
- `break_replication_reassembler_expire(r, now, max_idle)`：若有未完成 stream 且 `now - last_activity >= max_idle`（`now` 早于记录时间视为 0 空闲），丢弃该 stream 并返回 true；否则 false。high-water 保留：更旧的 delta 仍为 CONFLICT；过期 delta 自身的迟到分片与完成后一样重新开始该 delta（沿用 `reassembler_repeated_fragment_after_complete_starts_new_state` 的既有语义），更新的 delta 正常开始。NULL 返回 false。
- `break_replication_reassembler_pending_bytes(r)`：未完成 stream 当前占用的负载字节数（不含每分片元数据），用于诊断；无 stream 或 NULL 为 0。
- 不新增结果枚举值，已有调用者的 `switch` 不受影响。

## TDD

1. `test_break_replication_fragment` 新增：未完成 stream 在 `max_idle` 前不过期、到期后过期并清零 pending；重复分片刷新时间；过期后同一 delta 的迟到分片重新开始、更旧 delta 为 CONFLICT、更新 delta 可完成；时钟回退不过期；无 stream 或已完成时 expire 为 false；NULL 安全；`push` 与 `push_at` 的结果逐位一致。
2. RED → 实现 → GREEN；变异：比较改为严格大于、不刷新重复分片、过期时清 high-water、回退时间按无符号回绕计算。
3. 完整 Vulkan/OpenGL；ASan+UBSan/TSan（项目选项）下 fragment 与相关 replication 测试；更新设计与状态文档；评审后推送并核验远端。
