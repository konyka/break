# 复制分片 session bridge 设计（2026-11-24）

## 目标与范围

在现有 `break_net` 中增加每连接 `BreakReplicationReassemblyPool` 的真实 session 接缝，并注册 `0x4009` 分片消息。发送走 wire codec 与 `BreakNetReactor`，接收经 registry/envelope/session phase 后进入 pool，完成包再进入有界 FIFO，由所有者线程显式取出。

本项交付库级 session/reactor 接线与至少一个真实 loopback 验收。aspect `BRA1` 接入、生产应用启用、World delta wire、可靠重传/恢复和完整资产下载均不在本项。

## 方案比较

- **采用：bridge 持有连接池与完成队列，session 只调用 handler。** 依赖方向保持 `break_net -> break_replication_core`，bridge 不依赖 aspect/World；宿主在 open/close 事件点显式同步生命周期。
- callback 直接 apply aspect。会减少一层，但把网络线程/会话 handler 与业务所有权耦合，无法证明 drain 前状态不变，不采用。
- 无界完成列表或每消息独立堆对象。实现简单但失去背压与连接隔离，不采用。

## 消息注册与 wire

- `BREAK_NET_MESSAGE_ID_REPLICATION_FRAGMENT = 0x4009`，protocol v1，payload limit `BREAK_NET_MAX_PAYLOAD_SIZE`，`AUTHENTICATED + IDEMPOTENT`。
- default registry count 在 crypto 开启/关闭时由 29/28 变为 **30/29**。
- 负载使用已交付的 BRFG/v1 codec。session 的 duplicate policy 只处理传输序号，业务重复片仍由 pool 判定。
- 连接 handler 只接受该 ID/v1 和已经 open 的 connection key。畸形 wire、超出 bridge 配置的片大小/count、base/checksum/conflict/high-water/预算拒绝均返回 false；现有 session 对非 AUTH handler false 只记录 `HANDLER_FAILED`，不会隐式关闭连接。
- `INCOMPLETE`、完全相同的 `DUPLICATE` 和 `COMPLETE` 返回 true。完成队列本地溢出仍返回 true 并计 dropped，不能把本地背压伪装成对端协议错误。

## 公共类型与配置

```c
typedef struct BreakReplicationSessionBridge BreakReplicationSessionBridge;
typedef uint64_t (*BreakReplicationSessionClockFn)(void *user);

typedef struct BreakReplicationSessionBridgeConfig {
    BreakNetReactor *reactor; /* borrowed, may be NULL for receive-only tests */
    size_t max_connections;
    size_t stream_capacity;              /* 1..64 per connection */
    size_t max_pending_bytes_per_connection; /* 1..16 MiB */
    size_t max_total_pending_bytes;      /* >= connection product */
    size_t max_fragment_bytes;           /* 1..65496 */
    size_t max_fragment_count;           /* 1..1048576 */
    size_t completion_capacity;          /* > 0 */
    size_t max_completion_packet_bytes;  /* 1..16 MiB */
    size_t max_completion_queue_bytes;   /* >= packet cap */
    bool expiry_enabled;
    uint64_t expiry_interval;
    uint64_t expiry_max_idle;
    BreakReplicationSessionClockFn clock; /* required, owner thread only */
    void *clock_user;
} BreakReplicationSessionBridgeConfig;
```

create 校验所有范围与乘法溢出，并要求 `max_connections * max_pending_bytes_per_connection <= max_total_pending_bytes`。这样全局 pending 上限由配置静态保证，不会在完全相同重复片上误算新增字节。元数据、完成临时缓冲、已移交 payload 不属于该预算，文档必须明确；completion queue 另受条数和字节限制。

## 生命周期、发送与 tick

```c
BreakReplicationSessionBridge *break_replication_session_bridge_create(
    const BreakReplicationSessionBridgeConfig *config);
void break_replication_session_bridge_destroy(BreakReplicationSessionBridge *bridge);
bool break_replication_session_connection_open(
    BreakReplicationSessionBridge *bridge, BreakConnectionKey connection,
    uint64_t expected_base_id);
bool break_replication_session_connection_close(
    BreakReplicationSessionBridge *bridge, BreakConnectionKey connection);
BreakNetSendResult break_replication_session_send_fragment(
    BreakReplicationSessionBridge *bridge, BreakConnectionKey connection,
    const BreakReplicationFragment *fragment);
size_t break_replication_session_bridge_tick(BreakReplicationSessionBridge *bridge,
                                             uint64_t now);
```

- open 要求非零且未使用的 key，并为该连接创建 pool；expected base 属于该连接。重复 open 或容量满返回 false。close 销毁 pool，并释放该连接所有尚未取出的 completion；未知 close 返回 false。相同 key 后续 open 必须得到全新高水位和流状态。
- send 要求已 open、fragment.base_id 等于连接 expected base，且片大小/count 符合 bridge 配置。使用桥内一份 64 KiB owner scratch 编码，经 `break_net_reactor_send(..., 0x4009, 1, ...)` 发送。未知 key 为 `CLOSED`，参数/配置/codec 拒绝为 `INVALID`，reactor 结果原样返回；outbound overload 不重试、不丢发送侧状态，重试由调用方负责。
- tick 在每个已 open 连接上调用 pool_tick，返回本次总驱逐数；无流量也能过期。clock 与 tick 使用同一调用者时间单位。启用策略时 open 配置 pool set_expiry_schedule；禁用时不启用。
- 所有 API 都是所有者线程语义，不新增线程、锁或原子操作。reactor/clock/config 借用生命周期由调用者保证。

## 接收 handler 与完成队列

```c
typedef struct BreakReplicationSessionCompletion {
    BreakConnectionKey connection;
    uint64_t delta_id;
    uint8_t *payload;
    size_t payload_size;
} BreakReplicationSessionCompletion;

bool break_replication_session_handle_message(
    BreakConnectionKey connection, const BreakNetOwnedMessage *message,
    void *user_data);
size_t break_replication_session_poll_completed(
    BreakReplicationSessionBridge *bridge,
    BreakReplicationSessionCompletion *out, size_t out_capacity);
void break_replication_session_completion_release(
    BreakReplicationSessionCompletion *completion);
```

- `break_replication_session_handle_message` 可直接注册到 `break_session_manager_set_message_handler`。它用 config.clock 获取 now，decode 后应用 `max_fragment_bytes/max_fragment_count`，再调用该连接 pool_push_at。
- COMPLETE 必须满足 `completed_delta_id == fragment.delta_id`。payload 超过 `max_completion_packet_bytes`，或完成队列条数/总字节不足时，立即用 `break_replication_reassembly_free` 释放并计 dropped；不覆盖旧 completion。
- 成功入队的 completion 按 FIFO 保存 connection/delta/owned bytes。poll 最多移动 `out_capacity` 项给调用者并同步扣减 queue bytes；所有权随输出转移。`out=NULL` 或容量 0 返回 0。
- `completion_release` 释放 payload 并清零结构，NULL 为空操作。close 时未取出的 completion 同样释放并计 dropped。
- handler 不调用 aspect/World，也不把 message.data 保存到 pool 之外；只有 pool 返回的 owned completion 才进入队列。

## 统计

```c
typedef struct BreakReplicationSessionBridgeStats {
    size_t connections;
    size_t pending_bytes;
    size_t completion_count;
    size_t completion_bytes;
    uint64_t rejected_fragments;
    uint64_t duplicate_fragments;
    uint64_t completed_packets;
    uint64_t dropped_completions;
    uint64_t expired_streams;
} BreakReplicationSessionBridgeStats;
void break_replication_session_bridge_stats(
    const BreakReplicationSessionBridge *bridge,
    BreakReplicationSessionBridgeStats *out_stats);
```

stats 对 NULL bridge/out 为空操作（out 先清零）。pending/completion 数值是调用时快照，计数器单调递增；reset 通过 close/open 新连接实现，不提供全局隐式 reset。

## TDD 与验收

1. default registry 的 ID、版本、phase、duplicate、payload limit 和 30/29 count；旧消息不变。
2. create 配置边界、open 容量/重复、close/key reuse、连接隔离和 expected base。
3. 两连接、两个以上 delta 完全交织，重复/冲突/checksum/base；完成 id 与 payload 正确，drain 前测试 apply 计数为 0，drain 后才增加。
4. 完成队列条数和字节上限、单包上限、FIFO/所有权、close 清理；所有丢弃无泄漏。
5. send 的 canonical outbound、错误 base/大小/count、未知连接和 reactor overload；发送失败由调用方重试，bridge 不吞状态。
6. 无流量 tick 过期、clock 回退沿用 pool 契约、disable 策略。
7. 至少一个真实 Snowflake loopback：raw socket 经 AUTH 后发送 BRFG 分片，真实 registry/envelope/session/pool 重组，drain 后才消费完成包。
8. normal、完整 Vulkan/OpenGL、项目选项 ASan+UBSan/TSan focused；定向变异覆盖错误连接路由、queue 覆盖/字节漏扣、close 泄漏、send 头/ID、handler 直接 apply、tick 漏连接和 registry count。

文档明确本项是库级 session/reactor 证据，不是生产应用全面启用、可靠恢复、World delta 或完整资产服务。

## 后续边界

下一子项目才能把 aspect `fragment_size` 收窄到 65496，调用 bridge send/open/close/tick，并在 completion drain 中校验 `BRA1.schema_hash == expected_base` 后调用 `break_aspect_apply`。生产 core_app/editor 启用和跨进程恢复另设验收。
