# core_app World 复制接入设计（2026-11-24）

## 现状

- `world_session`（`7fe52ca3`）已提供 BRWD 接收、drain-only 应用、
  基线/ACK、need_full 限流、full 回退与 OVERLOAD 同包重试。
- core_app 现有 `--aspect-replication` 只复制两个固定 POD 对象，CSNP 全量
  快照路径不变；没有生产 `BreakWorldSnapshot` 或 World 接线。
- 权威边界不变：网络输入只能进诊断 store/World，不得反向修改 simulation。

## 范围

新增默认关闭的 `--world-replication` 服务端选项。开启后 transport 用
`world_session` 把两个 POD 实体的 World 表示按 BRWD 发给客户端，并接收
客户端的 BRWD 包到**独立的诊断 World**（不是 simulation World）。
默认仍走 CSNP，行为与 trace 完全不变。

不做：inbound 到 simulation 的合并、生产 level rebaseline、跨连接共享
World、Runtime Core 映射。这些保持缺口。

## 结构

- transport 持有 authoritative `BreakWorldSnapshot` 来源：两个只读 POD
  实体的 World 表示（固定 handle 与固定 component schema），以及独立的
  诊断 World。schema hash 与 level_generation 参与流纪元，与 aspect 互不
  影响。
- `net_start` 注册 0x400A/0x400B handler，创建 world_session；open/close
  与现有 aspect 生命周期共用 reactor connection key，失败回滚。
- `net_tick` 在 net_pump 后调用 world_session tick/drain（有界预算），并
  按 tick 发布：base 是最近确认快照，未知基线或 need_full 时发 full。
  OVERLOAD 保留同一不可变尝试；终态错误释放并计数。
- 诊断 World 只用于证明解码、重建、hash 校验和 apply；inbound 永不进入
  simulation。发送仍只读取 POD，不读取 World。

## 配置与诊断

- `--world-replication` 只在 `--network` 下有效，help/解析/`net_option_seen`
  同步；与 `--aspect-replication` 可独立或同时开启。
- 新增 `event=network_world_stats`（仅开启时输出）：open/close、applied、
  need_full、rejected、full_publishes、delta_publishes、sent_fragments、
  queue_depth、dropped。既有 `network_stats`、`network_aspect_stats` 不变。

## 验证

- TDD：配置与生命周期失败测试先行，再实现；真实 loopback 中客户端接收
  BRWD 并本地重建 target，与服务端 target snapshot ID 一致；base 不匹配
  触发 need_full/full；乱序/重复/超预算路径有计数证据。
- 反向控制：移除 0x400A 注册时 loopback 失败，恢复后通过。
- 默认关闭的既有 offline/loopback/lifecycle 全部通过；完整 Vulkan/OpenGL
  与 focused ASan+UBSan/TSan；文档追加新小节，保留生产合并、level 策略和
  跨连接共享缺口。
