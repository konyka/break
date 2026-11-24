# World delta wire codec 设计（2026-11-24）

## 现状与边界

- `BreakWorldSnapshot` 是不可变 ECS 快照；`break_world_delta_diff` 产生
  create/destroy 与 component add/remove/update 记录；
  `break_world_delta_apply` 要求 base/target 两个完整快照并在 staging World
  上原子替换。当前没有任何 World 快照或 delta 的线上编码。
- BRFG/v1 已提供分片、重组、session bridge；aspect 已示范 owner-thread
  drain。core_app 的 `0x4001` CSNP 全量快照保持原样，不改其格式或
  trailing 行为。

本子项目只做**版本化 World delta 编解码与目标重建校验**：一个独立的
`break_world_delta_wire` 模块。不做 session/bridge 接线、ACK/NACK、重传、
core_app 启用，也不把对端数据应用到服务端 simulation。这些留给后续子项目。

## 模块与格式

文件 `engine/src/ecs/world_delta_wire.{h,c}`（与 `world_delta.*` 同目录同命名
风格），函数 `break_world_delta_wire_*`。

```
BRWD | u16 version=1 | u16 kind(full=1/delta=2)
u64 schema_hash | u64 level_generation
u64 base_snapshot_id | u64 target_snapshot_id
u64 base_tick | u64 target_tick
u32 record_count
records[]: u8 kind | u64 entity_handle | u32 component_id | u32 byte_size | bytes
```

- 全部小端、显式逐字节读写，不使用 packed struct 或宿主 `usize`。
- `kind=full` 表示不依赖 base 的完整替换，records 描述目标世界的全部内容；
  `kind=delta` 必须与既有 `BreakWorldDeltaRecordKind` 一一对应。
- 校验：magic/version/kind、record 数量与字节上限、实体 handle 非零、
  component_id 非零、byte_size 与剩余长度精确一致、禁止尾随字节、
  target_tick > base_tick（full 允许 base_tick=0/base_id=0）。
  失败时输出清零、输入缓冲不被修改、错误码与现有
  `BreakWorldDeltaResult` 风格一致。

## 重建与哈希校验

`break_world_delta_wire_rebuild` 在调用方提供的 base 快照上应用记录，重建
target 快照并重新计算 `break_world_snapshot_id`，与 wire 的
`target_snapshot_id` 比较。线上的 hash 只作为断言，绝不直接信任。
schema_hash、level_generation、tick 与快照身份不一致时拒绝。
重建失败不改变调用方 World；应用仍走既有 `break_world_delta_apply` 的
staging 语义，本模块不直接写 World。

## ABI 限制

v1 只支持 `world_snapshot` 已接受的确定性 POD 组件字节。整型/浮点按组件
schema 声明的小端宽度编码；包含指针、资源引用或派生缓存的组件依然拒绝。
`usize` 等宿主相关字段不得出现在线上格式里。

## TDD 与验证

- 先写失败测试：round-trip full/delta、逐字节 golden、magic/version/kind、
  截断、尾随、count/size 溢出、handle/component 为零、tick 非递增、
  target hash 被篡改、base 不匹配、schema/level 不匹配、失败输出清零。
- 变异：端序反转、接受尾随、少校验 count、跳过 hash 重算、失败时留下输出、
  full 接受非零 base，均须判红。
- focused normal/ASan+UBSan(detect_leaks=1)/TSan 与完整 Vulkan/OpenGL；
  既有 ECS replication、bridge、aspect、core_app 测试不得回归。
- 文档追加新小节，保留 session 接线、ACK/恢复与生产启用缺口。
