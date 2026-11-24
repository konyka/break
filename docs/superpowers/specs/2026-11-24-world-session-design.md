# World session 接线与基线恢复设计（2026-11-24）

## 现状

- BRWD/v1（`546fc25e`）提供 full/delta 编码与重建校验，未接网络。
- session bridge 已支持每连接 BRFG 重组、完成 FIFO 与 owner poll；
  aspect session 示范了 drain 语义。core_app 只有 CSNP 全量快照，无基线、
  无 ACK。TCP/TLS 保序，主要风险是应用层队列丢弃、完成包丢弃和重连。
- `break_world_delta_apply` 需要 base/target 快照并做 staging 校验；
  World 不能直接由网络回调修改。

## 范围

新增 `engine/src/ecs/world_session.{h,c}`：把 BRWD 包接入 session bridge，
在 owner 线程 drain 为快照应用，并维护每连接基线与恢复状态。
不接 core_app，不做跨连接共享 World，不做 level rebaseline 的生产策略。

### 标识

- 外层 BRFG `base_id` 为固定 World 流纪元：由协议版本、schema hash、
  level_generation 计算。真正的 base 快照 ID 只在 BRWD 内层出现，因此
  ACK 基线变化不需要重建 pool。
- BRFG `delta_id` 为每连接单调递增的发送序号；ACK 指向
  `(delta_id, target_snapshot_id)`。

### 接收（`BreakWorldSession`）

- open 时指定 World 流纪元与初始空基线；close 释放该连接的基线。
- handler 只入队；`break_world_session_drain(session, connection, world, max)`
  才在 owner 线程执行：取出完成包 → BRWD 解码 → 基线匹配检查 →
  `break_world_delta_wire_rebuild` 重建 target 并核对 hash →
  `break_world_delta_apply` staging 应用 → 推进该连接的已确认基线。
- base 不匹配、schema/level 不匹配、hash 不匹配、apply 失败都计为
  `need_full`，该包被丢弃且基线不变；统计 applied/need_full/rejected。
- 新消息 ID 不与 0x4009 冲突：bridge 消息 ID 变为可配置（默认 0x4009），
  World 使用 `0x400A`（BRWD）与 `0x400B`（控制/恢复）。registry 计数
  30/29 → 32/31，AUTHENTICATED+IDEMPOTENT，payload 上限不变。

### 基线与恢复

- 每连接保存最近一个已确认 `(snapshot_id, tick)` 及不可变快照引用。
- 接收方在 drain 后返回需要恢复的事件；`need_full` 速率受限（每连接
  每 N tick 最多一次），控制消息 `0x400B` 携带 last good target id/tick。
- 发送侧（`break_world_session_publish`）对每个连接记录未确认历史；
  收到 need_full 或基线未知时发送 full 包（新的 delta_id），收到 ACK 后
  裁掉已确认历史。历史条数、字节数和单包大小均有界，超限退化为 full。
- OVERLOAD 重试同一不可变尝试，不重新生成部分内容；重连清空全部基线。
- 只保证 at-least-once 与最终一致，不承诺 exactly-once。

## TDD 与验证

- 先写失败测试：可配置消息 ID、registry 32/31、open/close、drain 才应用、
  base/hash/level 拒绝且基线不变、need_full 限流、full 回退、ACK 裁剪、
  OVERLOAD 重试同包、重连清零、完成队列满时的 full 回退。
- 真实 socket loopback：AUTH 后发送乱序/重复 BRWD 分片，客户端 drain 后
  World 与 target 快照 ID 一致；注入 base 不匹配触发 need_full/full。
- 至少 6 项变异判红；focused normal/ASan+UBSan/TSan 与完整 Vulkan/OpenGL；
  既有 ECS、bridge、aspect、core_app 不回归。
- 文档追加新小节，保留 core_app 启用、生产 level 策略与跨连接共享缺口。
