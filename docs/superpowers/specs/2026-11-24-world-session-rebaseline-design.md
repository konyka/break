# World session 显式 level rebaseline 设计（2026-11-24）

## 目标与边界

为一个 `BreakWorldSession` 提供 owner 显式触发的 session-wide level 换代：
所有已打开连接进入同一个新 generation，旧流状态作废，新代先建立 full
基线，每个连接独立等待 ACK 后才恢复 delta。

本项只交付传输无关的库级策略与真实 socket 验收，不接 core_app 的自动换级，
不选择或加载资产，不做 schema online migration。混合 level、跨连接共享 live
World、多写入者合并、Runtime Core 映射、authority handoff、预测、回滚、
exactly-once 和完整资产链均不在范围内。

## 方案比较

1. **固定槽位原地复位（采用）**。重组池的 slot 与 reassembler 已在创建时
   分配；复位后写入新 expected base 不需要分配或可能失败的中途提交。
   它能保持连接 key 和 expiry 策略，同时清掉 high-water、未完成流和旧
   completion。
2. 预分配整套替换池。可以回滚分配失败，但增加整套临时内存、失败注入和
   多阶段提交复杂度；固定槽位已提供无分配方案，因此不采用。
3. 关闭并重开传输连接。能复用现有重置，但丢失会话连续性，不能证明同一
   TCP 连接内换代，因此不采用。
4. 每连接独立 level。需要长期维持多代历史、控制和 World 所有权，超出本项
   单一 active generation 的目标，因此不采用。

## 无分配 epoch 复位

新增：

```c
void break_replication_reassembly_pool_rebaseline(
    BreakReplicationReassemblyPool *pool, uint64_t expected_base_id);
void break_replication_session_rebaseline(
    BreakReplicationSessionBridge *bridge, uint64_t expected_base_id);
```

pool 入口复用 reset 释放所有未完成流、清 retired high-water 和 tick 纪元，
保留容量、pending 上限与 expiry 策略，再把 pool 和每个固定 slot 的
expected base 改为新值。NULL 是 no-op。

bridge 入口对所有已打开连接执行同一 pool 换代，保留 key、连接数和 expiry
配置；丢弃全部旧 completion，计入既有 dropped-completions 计数并清 queue
size/bytes。所有操作都是 owner-thread、无分配、无锁，不存在部分连接成功的
失败返回路径。旧 epoch 分片因 base 不匹配被拒绝，不能进入新代 World。

## World session 换代

新增：

```c
bool break_world_session_rebaseline(
    BreakWorldSession *session, u64 level_generation);
u64 break_world_session_level_generation(
    const BreakWorldSession *session);
```

新 generation 必须非零且严格大于当前值；NULL、零、相同或回退均返回
false 且不改变状态。成功后 getter 返回新值。严格递增避免重新使用旧 epoch。

每次成功换代对每个打开连接保留 key 和已分配的 history 数组，但释放
baseline、confirmed、未确认 history 和当前 attempt，重置 next_delta_id=1、
force_full=true、pending ACK/NEED_FULL、NEED_FULL 限速纪元。session 和
bridge 使用同一个由 protocol/schema/new level 计算的 stream epoch。

接收方的 caller World 在成功 drain 新 full 前保持旧内容；delta 在没有新代
baseline 时被拒绝并请求 full。full 仍在空 staging World 重建并原子替换。
各连接 confirmed/history 独立，连接 A 的 ACK 不得让连接 B 发布 delta。

## BRWC/v1 兼容与 BRWC/v2

现有 snapshot id 不包含 level；仅增加 BRWD 的 level 字段不能阻止迟到的旧
ACK 在 delta id、target id、tick 全部复用时误确认新 history。因此控制结构
新增 `level_generation`，并定义 40 字节 BRWC/v2：

```text
0..3   "BRWC"
4..5   payload version = 2, little-endian u16
6..7   kind, little-endian u16
8..15  delta_id
16..23 target_snapshot_id
24..31 target_tick
32..39 level_generation
```

0x400B registry 接受 outer protocol 1..2。BRWC/v2 使用 outer version 2；
ACK/NEED_FULL 的 level 必须等于当前 session level，否则 handler 返回 false，
不修改 history、confirmed 或 force_full。

初始 level 保持现有行为：继续收发 32 字节 BRWC/v1、outer/payload version 1，
旧常量 `BREAK_WORLD_SESSION_CONTROL_WIRE_SIZE` 保持 32，新增 v2 常量 40。
v1 接收值被归入 session 的初始 generation；一旦发生换代，v1 控制一律拒绝。
手工构造的初始控制允许 level=0 或初始 level；poll 产生的控制总是携带当前
level。换代后的发送必须携带当前非零 level，缺省或旧 level 返回 INVALID。
旧客户端因而在初始代保持兼容，但不能误参与新代恢复。

BRWD/v1 与 0x400A 不变。新的 delta id/tick/snapshot id 即使与旧代完全相同，
也只能由匹配新 level 的 BRWC/v2 确认。

## 验证

严格 TDD 覆盖：

- pool/bridge：旧流与 completion 清除、新 base 接受、旧 base 拒绝、key 与
  expiry 策略保留、high-water 重置、NULL 安全。
- 换代准入：非法 generation 不变；基本 full→ACK→delta；旧 OVERLOAD
  attempt 不续发；同 delta id/tick/snapshot id 的旧 ACK/NEED_FULL 不碰撞。
- 多连接共同换代但独立 ACK；坏 full 不修改 World/baseline，随后正确 full
  恢复；close/reopen 保持当前 level 且清空连接状态。
- 初始 v1 字节回归和 v2 精确布局、outer/payload version、长度、level 校验。
- 真实 AUTH socket 在同一 TCP 连接内 level 7→8，注入反序/重复旧片和迟到
  旧控制；drain 前 World 不变，drain 后只达到新 target。

每项生产修复必须有定向变异判红并恢复。最终运行相关 normal、
ASan+UBSan（显式 leak 检测）和 TSan focused，以及完整 Vulkan/OpenGL；
条件 skip 不计执行通过。独立任务评审和整分支评审通过后才推送，随后核验
远端矩阵并追加收据。
