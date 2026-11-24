# core_app aspect 复制接入设计（2026-11-24）

## 现状

- `core_app` 是服务端：`core_app_net_transport.c` 创建 STEP reactor、
  SessionManager 和 TLS listener，注册 snapshot/physics/clock/voice handler，
  没有 `0x4009` handler，没有任何 `BreakAspectStore` 或 AOI。
- bridge 与 `BreakAspectSession` 已在 master：`break_replication_session`
  负责每连接重组与有界完成队列，`break_aspect_session_drain` 是唯一的
  `break_aspect_apply` 入口，expected base 为 inbound store 的 schema hash。
- 既有约束：网络输入不得反向修改 simulation（`core_app.h:37-46`、
  `core_app_net_transport.h:7-11`）。`break_aspect_apply` 不会创建未知对象，
  需要 handle 已存在或被 adopt。

## 范围

新增默认关闭的 `--aspect-replication` 服务端选项。开启后 transport 自己持有
authoritative store（发送）与 inbound store（接收诊断），用现有
`BreakAspectReplication` 按 AOI 向客户端发送 BRA1 分片，并用
`BreakAspectSession` 接收、重组、在 net_tick 里 drain。

不做：World delta 协议、把 inbound 数据应用到 simulation、level 切换的
rebaseline 策略、可靠恢复、编辑器接入。这些保持缺口。

## 权威与 handle 策略

- 两个 store 以完全相同的顺序注册同一组 schema，因此 schema hash 相同。
- 复制对象是现有 `entities[]` 中的两个只读 POD 实体，handle 使用固定的
  保留区间（1、2），authoritative store 与 inbound store 都以同一组 handle
  创建/adopt。这样 `break_aspect_apply` 在 inbound store 上总能找到对象，
  不需要新增协商消息。
- inbound store 只用于诊断：它证明收到的包通过了 BRA1/schema 校验并被
  drain，不会写回 simulation，也不影响 snapshot/physics 的权威路径。
- 所有客户端共享 inbound store 的 handle 命名空间；inbound 数据只用于观测，
  不区分来源连接做权威合并。需要区分来源时后续再按连接拆 store。

## 生命周期

- `net_start`：创建两个 store、spatial index、`BreakAspectReplication`、
  `BreakAspectSession`（`bridge.reactor = t->reactor`），注册 0x4009 handler
  （user_data 为 `break_aspect_session_bridge(session)`）。时钟与
  `break_aspect_session_tick` 使用同一单位。
- `net_pump` 在 `net_slot_add` 成功后、apply adapter event 之前，按
  **reactor connection key** 同时 open bridge 连接与 AOI 连接；任一步失败
  则回滚并拒绝该连接。close 时先 `break_aspect_replication_disconnect` 再
  `break_aspect_session_close`，并清理该 slot 的 AOI scope。
- `net_tick` 在 `net_pump` 之后调用 `break_aspect_session_tick(now)` 与
  `break_aspect_session_drain(budget)`；shutdown 的 `net_drain` 同样执行。
- 发送回调只做 `break_aspect_session_send(session, key, fragment)`，由
  bridge 以 0x4009/v1 编码后经 reactor 发送。`OVERLOAD` 原样返回，AOI 的
  dirty/baseline 状态只在完整成功后清除。
- welcome 先于任何复制流量；`net_send_pending` 中 AOI sync 放在 welcome
  之后、其它应用流量之前。无 level 时仍不新增网络轮询路径（保持现状）。

## 配置与诊断

- `--aspect-replication` 只在 `--network` 下有效；help、解析、`net_option_seen`
  同步更新；默认关闭时行为与 trace 完全不变。
- 新增 `event=network_aspect_stats` trace 行（仅开启时输出）：open/close、
  applied/rejected/drained、发送分片数、bridge 完成队列深度、dropped。
  不改既有 `network_stats` 文本，避免影响既有精确断言。

## 验证

- TDD：先写 transport 生命周期与配置测试（默认关闭、无 `--network` 时拒绝、
  open/close/tick/drain、关闭清理），再写真实 loopback。
- 真实 loopback：扩展 `test_core_app_net_client` 增加 aspect 模式：AUTH 后
  接收 BRA1 分片并本地重组；向服务端发送乱序/重复分片及 schema 不匹配包；
  断言服务端 trace 的 applied/rejected/drained 与发送计数。
- 反向控制：移除 0x4009 注册时 loopback 失败，恢复后通过。
- 既有 `test_core_app_network_offline`、全部既有 loopback 与 lifecycle 测试
  必须保持通过，证明默认关闭兼容。
- 完整 Vulkan/OpenGL、focused ASan+UBSan/TSan，文档追加新小节。
