# core_app 生产侧 Runtime 发布接线设计

日期：2026-11-26
状态：设计完成，待实施。文中新增接口均为提案。

## 背景与现状（已核实）

- 生产 `core_app_net_transport.c` 已持有 `world_authoritative`（6 个固定 POD 组件 schema）与 `world_schemas`，并有每槽 `world_diagnostics` 与 `world_session`。
- 现有发布走 legacy 通道：`net_world_publish_slot()` 直接调用 `break_world_session_publish(session, key, world_authoritative, current_tick)`，按槽逐条发送，且以「已有 history 且无 pending attempt」作为跳过条件。
- Runtime 通道 `break_runtime_world_session_submit_publish_current()` 已实现但**生产侧从未调用**；`BreakRuntimeWorldSessionConfig.publication` 在所有生产路径上都是 NULL。
- tick 顺序为：`net_world_update()`（ECS 结构变更）→ `net_world_tick_drain()` → 逐槽 legacy 发布。发布点在结构屏障之后，与 Runtime 的 owner-drain 语义相容。

结论：缺口是「publication 生命周期 + 由谁触发 publish-current」两件事，不是缺少 World 或缺少 Runtime adapter。

## 目标

让 `--world-replication` 下的生产 transport 在每次结构屏障后把当前权威 World 发布为 immutable snapshot，并经 Runtime direct notice 驱动既有 adapter 的 fanout，同时保持 legacy 通道可作为回退基线。

## 非目标

- 不改 BRWD/BRFG/BRWC wire，不新增消息 kind。
- 不做权威 simulation 合并、inbound apply 到权威 World、预测/回滚、AOI 裁剪、自动换级。
- 不改变 world off 行为：不创建 publication、不注册 adapter、不产生新 trace。
- 不改 `fair_outbound_admission` 默认值与既有 per-connection diagnostic World 语义。

## 方案比较

**A（采用）：publication 由 transport 拥有，tick 内 publish 后再 submit notice。**

transport 在 `net_world_create()` 末尾创建 publication（与 `world_schemas`/`world_authoritative` 同生命周期），并在 tick 的发布点先 `break_world_snapshot_build()` + `break_world_snapshot_publication_publish()`，随后 `submit_publish_current()`，由 adapter 的 owner drain 完成既有 full/delta 逻辑。legacy `net_world_publish_slot()` 退役或降级为回退开关。

优点：publication 与 World 同源同生命周期，顺序清晰；notice 只带 level，不复制快照；失败路径集中。

代价：需要一个「本 tick 快照」的临时引用管理与失败回滚。

**B：由 core_app 应用层拥有 publication 并注入 transport。** 需要跨越 core_app 生命周期与 hooks 边界，改动面更大，且 hooks 目前只传 `world_adapter_register`/`world_adapter`。放弃。

**C：保留 legacy，只在需要时并行发 notice。** 会出现同 tick 双发（legacy full + Runtime full），重复带宽且难判定权威性。放弃。

## 详细设计

### 生命周期

- `net_world_create()`：在 `world_session` 创建成功之后创建 `BreakWorldSnapshotPublication`，配置 `schema_hash = break_schema_hash(world_schemas)`、`level_generation = 0`。创建失败视为 `net_world_create` 失败，走既有回滚。
- 首次 level 初始化（`net_world_initialize_level` 的 rebaseline 路径）成功后，用新 level 重建 publication（先 close+destroy 旧实例，再以该 level 创建），因为 publication 的 `level_generation` 参与准入校验。
- `net_destroy()`：先 destroy adapter（既有顺序不变），再 `close` + `destroy` publication，最后销毁 session/reactor/World。
- 允许 publication 在 adapter 之前 close：语义是「丢弃未完成的 fanout」，不得因此形成永久 TIMEOUT。

### 每 tick 的发布点

在 `net_tick()` 现有结构屏障之后、`net_world_tick_drain()` 之前插入：

1. 若 `world_replication`、`world_level_initialized`、`producing` 均为真且至少一个槽 `world_open`：
   - `BreakWorldSnapshot *snapshot = break_world_snapshot_build(world_authoritative, world_schemas, tick)`
   - 失败（OOM/哈希失败）→ `world_stats.snapshot_build_failures++`，本 tick 不发布，继续 drain（不得阻塞收包）。
   - `break_world_snapshot_publication_publish(publication, snapshot, level)`；发布后立即 `break_world_snapshot_release(snapshot)`（publication 自行 retain）。返回 false（同 level tick 未递增等）→ 计数并跳过 notice。
2. 发布成功才 `break_runtime_world_session_submit_publish_current(adapter, &(notice){level, 0}, 0)`；返回 OVERLOAD → 计数，本 tick 跳过（下一 tick 以更新 tick 重试，publication 已是 latest-current）。
3. `net_world_tick_drain()` 随后由 adapter 完成 fanout。

legacy `net_world_publish_slot()` 在同一 tick 内不再调用；保留函数体但默认不参与，新增 `world_use_legacy_publish` 配置位（默认 false）以便回退诊断。

### 配置与统计

- `CoreAppNetTransportConfig` 追加 `bool world_use_legacy_publish;`（默认 false，保持零初始化语义）。
- `CoreAppNetWorldStats` 追加 `u64 snapshot_build_failures; u64 publish_rejected; u64 notice_overloads;`。
- 不新增公共 Runtime API；`publish_progress()` 与 `connection_snapshots()` 直接可用于生产观测。

### 失败与关闭

- adapter destroy 失败（TIMEOUT）时保留 publication 与 session，走既有回滚；不得先 destroy publication。
- publication publish 失败不改变 Session 状态；下一 tick 重新构建。
- world off：不创建 publication、不 submit notice、trace 与五子系统不变。

### 测试策略（TDD）

1. world off：断言 `publication == NULL`、无 notice、既有 trace 与五子系统不变（失败）。
2. world on 首 tick：`snapshot_build_failures == 0`、publication 有 current、adapter `publish_progress().observed_publication_epoch == 1`，两连接各收到一次 full。
3. 连续 tick：发布 epoch 递增、`dirty_connections` 回到 0；重复同 tick 不重复发包。
4. build 失败注入（schema 注册后移除组件或注入 OOM hook）：计数增加、本 tick 无 notice、下一 tick 恢复。
5. notice OVERLOAD：计数增加、下一 tick 收敛、不丢连接。
6. level rebaseline：publication 以新 level 重建、旧 lease 仍可读但不再作为 current、连接重新 full。
7. 关闭顺序：adapter 先销毁，publication 后销毁；adapter destroy TIMEOUT 时 publication 不释放。
8. legacy 回退位：打开 `world_use_legacy_publish` 时走旧路径且不 submit notice。

定向变异：notice 放在 publish 之前、skip snapshot_release、关闭时先销毁 publication、world off 仍创建 publication，均应判红后恢复。

验证：`test_core_app_net_transport`、`test_runtime_world_session`、真实 loopback 的 normal/ASan+UBSan(`detect_leaks=1`)/TSan，最终双后端完整 CTest。

## 边界

本切片不关闭：权威 simulation 合并、inbound apply 到权威 World、预测/回滚、共享 live World、跨 World 持久身份、AOI、自动换级、资产链、可靠每 epoch 广播、指标协议与告警。实现后 core_app 才真正接入 Runtime 发布数据面；此前该接线不存在。

## 实施任务

1. **publication 与 tick 接线**：transport 字段、create/init/destroy 顺序、tick 发布点、legacy 开关、统计字段；对应单元与 loopback 测试，含四项变异。
2. **文档与最终验收**：六份设计/状态文档追加 2026-11-26 小节，双后端与合同，评审、推送与远端收据。

## 修订 1（2026-11-26，实施前核查）

实施前复查代码，发现上文方案 A 直接落地会出错，修订如下。上文保留作记录，以本节为准。

### 发现的问题

1. **未认证连接会收到快照。** adapter 的 OPEN 在 `CONNECTION_OPENED` 时提交，早于 AUTH-v2。adapter fanout 对所有已 OPEN 连接发送，而 legacy 只对 `net_slot_sendable()`（已认证且已 welcome）的槽发送。照原方案接线会把权威 World 发给未认证的 TLS 对端，也会让 World 包先于 welcome 到达。
2. **流控语义不同。** legacy 是停等：已有 history 且无 pending attempt、无 force_full 时跳过，等 ACK 释放 history 再发下一个。adapter 每个新 publication epoch 都发。直接替换会改变真实 loopback 的 `full_publishes=1 delta_publishes=1` 等计数，也会持续堆积 history。
3. **adapter 未接 publication。** `world_adapter_register` 创建 adapter 时 `config.publication` 为 NULL，`submit_publish_current` 会返回 REJECTED。
4. **tick 可能回退。** core tick 在关卡重载时可能从头计数，而 World level 初始化后不再变化；publication 会拒绝同 level 下不递增的 tick，发布会永久停住。
5. **不需要重建 publication。** publication 以 level 0 创建后，接受任何 `level >= 0` 的发布，lease 带的是发布时的 level。原方案的"rebaseline 后重建"没有必要，删除。

### 修订后的方案

- **ECS：** `BreakWorldSessionSenderState` 末尾追加 `bool force_full`，如实反映 Session 内部的强制全量标志（NEED_FULL 或 rebaseline 置位，全量发出后清除）。
- **Runtime：** `BreakRuntimeWorldSessionConfig` 追加两个默认 false 的开关，两者都要求 `publication` 非空：
  - `publish_requires_ready`：新 OPEN 的连接默认不就绪。调用方用新增的 `break_runtime_world_session_set_publish_ready(adapter, key, epoch, ready)` 按 key+epoch 设置，错配返回 STALE。未就绪连接不参与 fanout、continuation 重算和 dirty 统计，attempt 标量保持不动。
  - `publish_waits_for_ack`：fanout 时按 Session 状态判断，连接没有进行中的 attempt、history 非空且没有 force_full 时视为"等待 ACK"，本次不发，把该连接的 `held_publication_epoch` 记为当前 epoch。与 completed/terminal 一样，held 等于当前 epoch 时连接视为干净，不算 dirty，也不触发 continuation。这一规则在每次 drain 内用当时的 Session 状态求值，不会因 transport 的判断过时而多发包。
  - `BreakRuntimeWorldConnectionSnapshot` 追加 `publish_ready` 与 `held_publication_epoch`。
- **transport：**
  - publication 在 `net_world_create()` 中以 level 0 创建，注册 adapter 时传入 `publication`，并设 `publish_requires_ready = true`。
  - 每 tick 在原 legacy 发布点（pump、tick_drain 之后，且 reactor 事件队列为空时）把每个 world_open 槽的就绪状态设为 `net_slot_sendable()`。
  - 有任一就绪槽需要新目标（history 为空或 force_full，且没有进行中的 attempt）时，构建快照并 publish，成功后提交 notice。之后只要 adapter `pending() != 0` 就 drain 一次，由 continuation 续发 OVERLOAD 留下的 attempt。
  - 快照 tick 使用 transport 内单调计数：`publish_tick = max(current_tick, publish_tick + 1)`。
  - 默认走 Runtime 路径；`world_use_legacy_publish` 为 true 时回到旧逐槽路径。
  - 新增统计 `snapshot_build_failures`、`publish_rejected`、`notice_overloads`，以及 test-only 的构建失败注入。
  - 销毁顺序不变：`net_destroy()` 先销毁 adapter，失败即返回；publication 在 `net_world_destroy()` 中 close+destroy，所以 adapter 未释放时 publication 一定保留。
- **验收：** 真实 loopback `test_core_app_network_world` 的既有计数不改，默认 Runtime 路径必须原样通过，以此证明与 legacy 等价。
