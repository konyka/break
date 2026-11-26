# Runtime World Session 的按连接 AOI 过滤接入（设计）

状态：设计，未实现。本文规划把已交付的按连接 AOI 裁剪原语接入 `BreakRuntimeWorldSession`
共享发布 fan-out 路径，供 core_app `--world-replication` 实际按连接裁剪。先设计后实现，
实现时采用 TDD。

## 背景与已交付基础

- `break_world_snapshot_filter(snapshot, keep, user)`：从 immutable snapshot 派生只含谓词接纳
  实体的新视图，hash/id 与直接 build 同一组实体一致，可直接走 delta。
- `break_net_entity_scope_keep` / `BreakNetEntityScope`：把连接的稳定 `BreakNetEntityId` 集合
  变成上述谓词。
- `break_world_session_publish_filtered`：对权威 World 现场 build 后按连接裁剪再发布。
- `break_world_session_publish_snapshot_filtered`：对共享 immutable target 按连接裁剪出私有
  视图再发布，target 借用不变，可 fan-out 给多条连接。

以上均为库级、已通过 TDD/变异/ASan+UBSan/TSan 与全量 CTest。

## 现状：共享 target fan-out 不裁剪

`engine/src/runtime/runtime_world_session.c` 的 `runtime_world_publish_connection`（约 334 行）
对每条连接调用 `break_world_session_publish_snapshot(session, key, lease->snapshot, level)`，
即所有连接收到同一份完整 target。core_app `net_world_publish_runtime` 先把权威 snapshot
publish 给 `BreakWorldSnapshotPublication`，adapter 再 acquire lease 并 fan-out。

## 关键约束：per-connection target 身份

`runtime_world_publish_connection` 用 `lease_id = break_world_snapshot_id(lease->snapshot)`
和 `lease_tick` 做三件事：

1. attempt 身份对账：`same_current`、`after_current`（OVERLOAD 续发时判断新 attempt 是否
   就是本 lease 的 target）。
2. publication epoch 归属：`attempt_publication_epoch`、`held_publication_epoch` 等按 lease
   epoch 记账。
3. 幂等/去重：`same_saved` 保留 E1 等历史 attempt 的 epoch。

如果每条连接把 lease target 裁剪成自己的视图，该连接 attempt 的 target id 变成**过滤视图的
id**，不再等于共享 `lease_id`。直接把 334 行换成 `publish_snapshot_filtered` 会让上述对账全部
落空：`same_current`/`after_current` 永远为假，epoch 记账错位，OVERLOAD 续发与 ACK 流程紊乱。

因此接入 AOI **不是** 把一个调用替换成过滤版本，而要让 per-connection 记账改用“该连接应得的
目标 id”。

## 方案

### 配置

`BreakRuntimeWorldSessionConfig` 增加可选：

```c
BreakWorldSnapshotEntityFilter publish_keep; /* NULL = 不裁剪，现状行为 */
void *(*publish_keep_user_for)(void *ctx, u64 connection_key); /* 每连接 scope */
void *publish_keep_ctx;
```

`publish_keep == NULL` 时行为与今天逐字节一致（默认关闭，零风险）。非 NULL 时，fanout 对每条
连接用 `publish_keep_user_for(ctx, key)` 取该连接的 `BreakNetEntityScope*`（或等价 user），
调用 `break_world_session_publish_snapshot_filtered`。

### per-connection 目标 id

在 publish 之前，为每条 ready 连接预计算它这次应得的目标视图 id/tick：

- 选项 A（精确）：fanout 时先 `break_world_snapshot_filter(lease->snapshot, keep, user)` 得到
  视图，取其 id/tick 作为对账基准，再把这个视图交给一个新的
  `break_world_session_publish_snapshot_view`（接收已 build 好的视图，避免重复过滤）。缺点：
  需要再加一个库级入口；优点：adapter 记账只需把 `lease_id/lease_tick` 换成 `view_id/view_tick`。
- 选项 B（在原语内回传）：扩展 `break_world_session_publish_snapshot_filtered` 增加可选
  `out_target_id`/`out_target_tick`，publish 时回传实际视图 id/tick，adapter 用它对账。
  优点：不重复过滤；缺点：改已交付原语签名（可用新函数名避免破坏）。

倾向选项 B 的“新函数 + 回传”：新增
`break_world_session_publish_snapshot_filtered_id(..., u64 *out_id, u64 *out_tick)`，
`runtime_world_publish_connection` 把 `lease_id/lease_tick` 替换为回传值用于 `same_current` 等。
`publish_keep == NULL` 时回传等于 lease id/tick，保持现状。

### epoch 归属不变

publication epoch 仍来自 lease，不随过滤改变；每条连接的 `held/attempt/completed/terminal_
publication_epoch` 语义不变，只是 target id/tick 改用该连接视图的值。

## TDD 计划

库级（非 Snowflake 优先，能在 `build-current-vk` 跑的先跑）：

1. `break_world_session_publish_snapshot_filtered_id` 回传过滤视图 id/tick；NULL keep 回传
   lease id/tick。RED：未定义引用。
2. 变异：回传 lease id 而非视图 id、NULL keep 不回传。

adapter 级（Snowflake，`build-aoi-net`，`test_runtime_world_session`）：

3. 两条连接不同 scope，同一 publish 各自收到自己视图，`continuation`/`dirty`/epoch 记账正确。
4. OVERLOAD 续发：被裁连接的续发 attempt identity 用视图 id 对账，不误判为“换了 target”。
5. NULL keep 回归：所有既有 `test_runtime_world_session` 用例逐位不变。
6. 变异：adapter 仍用 lease_id 对账（应使 overload 续发用例 RED）。

core_app 级（`test_core_app_net_transport` / loopback）：

7. `--world-replication` 打开 per-connection scope 后，两个对端各自 drain 出自己可见实体集合，
   `network_world_stats` 的 applied/need_full 等计数一致。

## 边界

- 本设计不涉及权威 simulation 合并、inbound apply、预测回滚、共享 live World。
- scope 的来源（`break_aoi_compute` → `BreakNetEntityScope`）的生产组装单列一个 core_app 切片。
- 默认 `publish_keep == NULL`，不改变现有生产行为；启用过滤是显式 opt-in。
