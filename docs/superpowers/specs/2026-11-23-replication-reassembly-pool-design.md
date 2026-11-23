# 复制分片多 delta 并发重组池设计（2026-11-23）

## 背景与目标

`BreakReplicationReassembler` 一次只保存一个 delta；较大的 delta 到达时会取代尚未完成的旧流。乱序网络交付下，一个丢失分片就可能让前一个 delta 永远无法完成。现有 `push_at`/`expire` 已解决单流空闲驱逐，但没有解决多 delta 并发重组。

本子项目新增一个有界 `BreakReplicationReassemblyPool`，按 `delta_id` 把分片路由到独立槽位。旧的单流类型、API 和取代语义不变；本项不接 session/网络，也不新增后台线程。

## 方案比较

- **采用：固定槽位池。** 创建时确定槽位数和共享负载预算，每个槽复用现有单流重组逻辑。优点是所有权、容量和过期规则都可确定性测试，旧代码路径不受影响；缺点是需要新增带 `completed_delta_id` 的完成接口。
- 修改现有重组器为隐式多流。调用方看不到新类型，但会改变“新 delta 取代旧 delta”的既有契约，也无法在不扩展输出参数的情况下可靠识别乱序完成的 delta，因此不采用。
- 调用方自行创建多个单流重组器。无需新库代码，但每个调用方都要重复实现路由、共享预算、槽位回收、高水位和逐流过期的组合逻辑，容易各自产生不一致，因此不采用。

## 公共契约

接口放在现有 `network/break_replication_fragment.h`，实现放在同一 `.c`，由正式可选 `break_replication_core` 承载：

```c
#define BREAK_REPLICATION_REASSEMBLY_POOL_MAX_STREAMS 64u

typedef struct BreakReplicationReassemblyPool BreakReplicationReassemblyPool;

BreakReplicationReassemblyPool *break_replication_reassembly_pool_create(
    uint64_t expected_base_id, size_t stream_capacity, size_t max_pending_bytes);
void break_replication_reassembly_pool_destroy(BreakReplicationReassemblyPool *pool);

BreakReplicationReassemblyResult break_replication_reassembly_pool_push_at(
    BreakReplicationReassemblyPool *pool, const BreakReplicationFragment *fragment,
    uint64_t now, uint64_t *completed_delta_id,
    uint8_t **payload, size_t *payload_size);

size_t break_replication_reassembly_pool_expire(
    BreakReplicationReassemblyPool *pool, uint64_t now, uint64_t max_idle);
size_t break_replication_reassembly_pool_pending_streams(
    const BreakReplicationReassemblyPool *pool);
size_t break_replication_reassembly_pool_pending_bytes(
    const BreakReplicationReassemblyPool *pool);
void break_replication_reassembly_pool_reset(BreakReplicationReassemblyPool *pool);
```

- `stream_capacity` 为 1..64，`max_pending_bytes` 为 1..`BREAK_REPLICATION_MAX_REASSEMBLY_SIZE`。非法配置或分配失败时 create 返回 NULL。
- `push_at` 与单流版本使用相同的分片形状、`base_id` 和 FNV-1a 校验。入口把可选输出清零；`completed_delta_id` 只在返回 `COMPLETE` 时有效，因此 delta 0 没有特殊保留值。
- 返回 `COMPLETE` 时，payload 所有权仍由 `break_replication_reassembly_free` 释放；payload 可为 NULL，此时完成结果被丢弃但槽位仍正常回收。
- 不新增结果枚举。没有空槽或新增负载会超过共享预算时返回 `OVER_LIMIT`，不覆盖、不隐式驱逐其他流。
- `expire` 驱逐所有达到空闲阈值的计时未完成流并返回数量；`pending_streams`/`pending_bytes` 对 NULL 返回 0。`reset` 清空全部流和高水位，保留创建配置。

## 路由、预算与高水位

1. 先按 `delta_id` 找活跃槽；找到后交给该槽，较大或较小的其他 delta 不打断它。相同分片刷新该槽活动时间，被拒绝的分片不刷新。
2. 新 delta 需要空槽。满槽返回 `OVER_LIMIT`；现有流及其时间戳保持不变。
3. 池维护“已退出高水位”，取已完成或已过期 delta 的最大值。新流若严格小于该值则返回 `CONFLICT`；等于该值时沿用单流语义，可以重新开始。已经活跃的较旧槽不受较新槽完成或过期影响，可以继续完成。
4. 新流开始或活跃槽接受新分片时，共享 `pending_bytes` 不得超出创建预算。完全相同的重复分片不重复占预算；校验失败、冲突、重复和容量拒绝均不改变预算。每个槽原有的分片元数据上限保持不变。
5. 完成时先移交拼装结果，再回收槽并推进高水位。拼装临时缓冲不计入 pending；其生命周期与现有单流相同。
6. `expire` 对每个槽独立使用调用者时钟：时钟回退按 0 空闲，`max_idle=0` 立即驱逐。被驱逐槽推进已退出高水位，但其活跃较旧槽不被连带清理。
7. 所有 API 都是所有者线程语义，不引入锁或原子操作。调用者必须串行调用同一池。

容量和预算检查必须失败原子：拒绝后，已有流之后仍能按未发生该拒绝时的规则完成。错误检查顺序保持单流原则：形状/base/checksum 先拒绝，路由冲突先于新增负载预算；新流的已退出高水位先于空槽检查。

## TDD 与验收

先在 `test_break_replication_fragment` 增加用例并确认编译 RED，再实现到 GREEN：

1. 创建参数、NULL 安全、可选输出清零和查询初值。
2. 至少三个 delta 的分片完全交织，按各自分片数完成；`completed_delta_id` 和每个 payload 与独立单流参考一致。
3. 槽位满返回 `OVER_LIMIT` 且不覆盖；某槽完成后可接收新 delta。
4. 共享预算在新流开始和活跃流追加两个方向都生效；重复分片不误计预算；拒绝后可通过驱逐其他流恢复。
5. 各槽独立过期、重复刷新、拒绝不刷新、时钟回退、一次 expire 驱逐多个、过期高水位和活跃较旧流继续完成。
6. 乱序完成与重新开始规则；reset 与同配置新池行为一致；旧 15 项单流测试不变。

定向变异至少覆盖：错误路由/槽位覆盖、漏输出 completed id、容量检查差一、共享预算漏加、重复重复计数、过期漏槽、错误推进或清空高水位、reset 漏状态。随后运行完整 Vulkan/OpenGL CTest，项目选项下的 ASan+UBSan/TSan focused 测试，更新设计/状态/缺口文档，经独立评审后推送并核验远端 CI、Windows 和 Proton 收据。

## 明确边界

本项只交付传输无关的重组池，不宣称完成 session/网络接线、周期调度器、加密认证或持久化。FNV-1a 仍只用于完整性校验，不能作为安全认证。
