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

## 实现记录（2026-11-26）：adapter 侧已接入

本文规划的 adapter 接入已实现，采用上文「选项 B」。

- **配置**：`BreakRuntimeWorldSessionConfig` 新增 `publish_keep`、`publish_keep_user_for`、
  `publish_keep_ctx`。`publish_keep == NULL`（默认）时行为与接入前完全一致；`publish_keep`
  需要 publication，缺 publication 或「只给 user 解析器不给 filter」都在 create 时返回 NULL。
- **发布路径**：`runtime_world_publish_connection` 改调
  `break_world_session_publish_snapshot_filtered_id`，并把 attempt 身份对账的
  `lease_id/lease_tick` 换成回传的 `target_id/target_tick`（该连接过滤视图的身份）。
  `publish_keep` 为空时回传即 lease 身份，因此既有记账逐位不变。
  publication epoch 仍取自 lease，不随过滤改变。
- **每连接 scope**：`publish_keep_user_for(ctx, connection_key)` 为每条连接返回谓词 user
  （例如其 `BreakNetEntityScope`）；未提供时所有连接共用 `publish_keep_ctx`。

### 验证

`test_runtime_world_session` 60/60（原 57 例，新增 3 例；normal/ASan+UBSan 含 leak 检测/TSan
均 60/60）：

1. `publish_keep_requires_a_publication_and_a_filter`：无 publication 的 filter、无 filter 的
   user 解析器都被 create 拒绝。
2. `publish_keep_fans_one_target_into_per_connection_views`：一份共享已发布 target，两条连接
   用不同 scope，各自以**自己过滤视图的 id/tick** 被 ACK 后 `confirmed_snapshot_id` 才前进，
   且都不等于共享 target 的 id。
3. `publish_keep_overload_resume_tracks_the_filtered_view_identity`：填满出站队列迫使过滤
   fanout 进入 OVERLOAD，断言每条连接 pending attempt 的 `attempt_target_snapshot_id` 等于
   自己的视图 id、`attempt_publication_epoch` 非零、`retry_publish` 为真；排空后同一不可变
   attempt 续发完成，`publish_terminal` 为 0，两条连接都不再 dirty。

既有回归：`test_world_session_loopback` 10/10、`test_world_session_recovery` 31/31 不变。

### 变异检查

- **「永不过滤」**（filter 分支短路成未过滤发布）：用例 2 判红（ACK 与实际 attempt 不匹配，
  `confirmed` 无法前进）。注意：初版用例只断言 history 计数与 dirty 标志时该变异存活，
  补上「按各自视图 id ACK」后才判红，已按此加强。
- **「用 lease 身份而非视图身份对账」**（`same_current`/`after_current` 换回 lease）：经分析与
  实测确认为**等价变异**，在 adapter 当前控制流下分歧不可达。两条路径互斥：
  `had_active == false`（无进行中 attempt）时，`attempt_publication_epoch` 的
  `!had_active || after_current` 直接短路，身份比较不参与；`had_active == true` 时，
  `break_world_session_publish_snapshot_filtered_id` 在 `state->attempt.active` 分支提前返回
  续发结果，回传的 `target_id/target_tick` 取自该 attempt 自身，根本不执行过滤，因此与 lease
  比较和与回传值比较得到相同结论。曾按 `publish_unknown_old_attempt_does_not_complete_current`
  的形状写过 E1→E2 过滤用例试图暴露该分歧：正确实现与变异实现的
  `publish_dirty/completed/attempt_epoch` 探针输出完全相同，证明不可达，该用例已删除而不是
  留作假阳性保护。实现保留视图身份仍是正确取向（语义更准确，且一旦将来续发路径改为重新过滤
  就会变得可达），但不为等价变异编造测试。

## 仍未交付

- core_app `net_world_publish_runtime` 未设置 `publish_keep`（原因见下节「core_app 接线的实际
  结论」：该 World 无位置/空间索引/witness，没有 AOI 数据来源，不属于可接线项）。
- 权威 simulation 合并、inbound apply、预测回滚、共享 live World 不在本切片。

## core_app 接线的实际结论（2026-11-26 勘察）

原计划的「core_app `net_world_publish_runtime` 设置 `publish_keep`」在当前 core_app 形态下
**没有可用的 AOI 数据来源**，因此不作为实现项，改记为前置条件未满足。

勘察结果（`engine/apps/core_app/core_app_net_transport.c`）：

- World 侧：`net_world_create` 建立 `world_authoritative`，注册的 schema 只有 POD 计数类组件
  （`u32` 等，无位置/朝向），并创建固定 `CORE_APP_WORLD_OBJECT_COUNT` 个实体作为诊断对象。
  该 World 没有空间索引，也没有任何 witness/观察者状态。
- aspect 侧确实有 AOI：`aspect_index`（`break_spatial_index_create(16.0f)`）、
  `aspect_aoi[]`、`aspect_scopes[]`，由 `net_aspect_sync_slot` 调 `break_aoi_compute` 维护。
  但它服务的是 `aspect_objects[CORE_APP_ASPECT_OBJECT_COUNT]`（2 个固定诊断对象），
  与 `world_objects[]` 是两套互不相关的身份，aspect 的 `BreakAoIEntityId` 不是 World Entity，
  也没有经 `break_net_entity_map` 绑定到 World。

因此在 core_app 里启用过滤，必须先为 World 诊断对象编造位置分量、空间索引与 witness，
或把 aspect 的 AOI 身份经 `BreakNetEntityMap` 映射到 World Entity。两者都不是「接线」，
而是给一个刻意保持为固定 POD 计数器的诊断 World 新增空间语义；在没有产品需求驱动前
不实现（YAGNI）。

真正需要 AOI 裁剪的接入点是有空间语义的宿主：它自己持有 World、位置组件、空间索引与每连接
witness，用 `break_aoi_compute` 得到 scope，经 `break_net_entity_map` 绑定 `BreakNetEntityId`，
填 `BreakNetEntityScope`，再把 `break_net_entity_scope_keep` 作为 `publish_keep`、
以 `publish_keep_user_for` 按连接返回该 scope 交给 adapter。本仓库已交付这条链路的全部库级
与 adapter 级部件并有回归保护；缺的只是一个具备空间语义的宿主应用，不是缺实现。
