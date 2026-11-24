# Runtime ↔ World Session 控制面适配器设计（2026-11-25）

## 目标与边界

新增独立可选 `runtime_world_session` bridge，把 Runtime owned message 中的标量
控制映射到既有 `BreakWorldSession`：open、close、rebaseline、ACK、NEED_FULL。
生产者线程只提交 bounded bytes，唯一 World Session 调用点是 owner-thread
`break_runtime_world_session_drain`。

不包含 snapshot/lease/BRWD/BRFG 数据面、core_app authoritative World 接线、
Runtime Coordinator 自动注册、共享 live World、权威 simulation 合并、跨
World 持久身份、预测回滚或完整资产链。`runtime_core` 不增加对 ECS、网络或
Snowflake 的依赖。

## 方案比较

1. **独立 bridge + 既有 RuntimeBus/Queue（采用）**。复用 typed kind、bounded
   copy、reserved control、generation、FIFO 和关闭唤醒，不另造消息框架。
2. 直接在生产者调用 World Session。会违反 owner-thread 与网络回调边界，
   不能解决背压和关闭顺序，不采用。
3. 完整 BRWD 数据面映射。需要解决 16/64 MiB 限制、completion correlation、
   聚合字节预算和 snapshot 生命周期，应另立项目。
4. 权威 full-state 合并。缺少权限、稳定身份、确定性排序和冲突策略，不在
   控制面项目内扩大。

## BRWC correlation 兼容

新增：

```c
BreakNetSendResult break_world_session_send_control_correlated(
    BreakWorldSession *session, BreakConnectionKey connection,
    const BreakWorldSessionControl *control, u64 correlation_id);
```

旧 `break_world_session_send_control` 委托新函数并传 0。新函数复用
`break_net_reactor_send_correlated`，BRWC payload、版本、level、长度和连接
状态机完全不变；只有 envelope correlation extension 可携带完整 u64。
旧路径仍 cid=0。Runtime sequence 不截断为网络 u32 sequence，既有网络逐
连接序号继续由 reactor 分配。

## 控制命令与身份代次

新增 Runtime kind `BREAK_RUNTIME_WORLD_SESSION_CONTROL_KIND = 0x5753`，
version 1，固定 56 字节 payload：

```c
typedef enum {
    BREAK_RUNTIME_WORLD_COMMAND_OPEN = 1,
    BREAK_RUNTIME_WORLD_COMMAND_CLOSE = 2,
    BREAK_RUNTIME_WORLD_COMMAND_REBASELINE = 3,
    BREAK_RUNTIME_WORLD_COMMAND_ACK = 4,
    BREAK_RUNTIME_WORLD_COMMAND_NEED_FULL = 5
} BreakRuntimeWorldCommandKind;

typedef struct {
    u32 kind;
    u32 reserved_zero;
    u64 connection_key;
    u64 connection_epoch;
    u64 level_generation;
    u64 delta_id;
    u64 target_snapshot_id;
    u64 target_tick;
} BreakRuntimeWorldCommand;
```

`connection_key` 保留完整 u64。`connection_epoch` 是 bridge 本地分配的连接
身份代次：open 时必须为 0，成功后分配一个非零、严格递增且不复用的值；
close/reopen 后旧 epoch 的命令在 owner 处拒绝。rebaseline 是 session-wide，
要求 key/epoch 都为 0，但保持各连接 epoch；level 必须严格递增。

open/close/ACK/NEED_FULL 要求 key/epoch 与 bridge 当前槽一致，level 等于
当前 session level。未知 key/epoch 返回 STALE；重复 open 返回 REJECTED；
非法 level、回退 level 或已排队旧 level 返回 STALE 且不调用 World Session。
level、Runtime queue generation 和 publication epoch 是三个独立概念，不能
互相替代。

命令的 reserved_zero 必须为 0。ACK 要求非零 delta id/target id；NEED_FULL
要求 delta id=0，target id/tick 可取 last-good 或 0。open/close/rebaseline
不使用 delta/target 字段，必须全 0。命令不包含任何 World、Snapshot 或 lease
指针。

## Bridge API 与所有权

```c
typedef struct BreakRuntimeWorldSession BreakRuntimeWorldSession;

typedef struct {
    BreakWorldSession *session;       /* borrowed, owner-thread */
    BreakRuntimeBus *bus;            /* borrowed */
    const char *subscriber_name;     /* NULL = "world_session" */
    u32 queue_capacity;              /* 0 = 64, allowed 1..256 */
    u32 max_connections;             /* 0 = 8, allowed 1..64 */
} BreakRuntimeWorldSessionConfig;

typedef struct {
    u64 submitted;
    u64 drained;
    u64 applied;
    u64 rejected;
    u64 stale_rejected;
    u64 transport_overloads;
    u64 next_sequence;
    usize queued;
    bool control_pending;
} BreakRuntimeWorldSessionStats;

BreakRuntimeWorldSession *break_runtime_world_session_create(
    const BreakRuntimeWorldSessionConfig *config);
bool break_runtime_world_session_destroy(
    BreakRuntimeWorldSession *adapter);
BreakRuntimeError break_runtime_world_session_submit(
    BreakRuntimeWorldSession *adapter,
    const BreakRuntimeWorldCommand *command,
    u64 correlation_id);
void break_runtime_world_session_close(
    BreakRuntimeWorldSession *adapter);
BreakRuntimeError break_runtime_world_session_drain(
    BreakRuntimeWorldSession *adapter, usize max_messages,
    usize *out_drained);
usize break_runtime_world_session_pending(
    const BreakRuntimeWorldSession *adapter);
bool break_runtime_world_session_connection_epoch(
    const BreakRuntimeWorldSession *adapter, u64 connection_key,
    u64 *out_epoch);
void break_runtime_world_session_stats(
    const BreakRuntimeWorldSession *adapter,
    BreakRuntimeWorldSessionStats *out_stats);
```

`connection_epoch` 查询在 key 未知时返回 false 并写 0；open drain 成功后，
调用方用它构造后续命令，不能猜测内部代次。

create 注册/匹配 kind（max_payload=56、control=true、quota 无限），创建全
control-reserved queue 并订阅，不调用 World Session。submit 做无状态格式
校验后通过 bus 发布；Runtime sequence 从 1 开始且只在成功入队后递增，
溢出返回 OVERLOAD，与 wire sequence 无关。correlation_id=0 保持
uncorrelated；新因果链由调用方使用 `break_runtime_correlation_next`，不得
复用对端 cid。

submit 在 close 后返回 CLOSED；bus/queue 满返回 OVERLOAD，不 inline、不修改
World。消息是 bounded copied bytes，不含生产者指针。bridge 不伪造现有 bool
API 无法提供的 OOM 分类。

drain 仅 owner 调用，按 FIFO 消费后执行对应 World API，并释放 owned
message。`max_messages=0` 是 OK 空操作。stale/invalid/REJECTED 会计数但不
阻塞其他命令；drain 返回本批首个非 OK 结果。out_drained 统计实际消费的
命令数，不是重试次数。

## OVERLOAD 与关闭

ACK/NEED_FULL 发送遇到 transport OVERLOAD 时，bridge 保存同一 control、
level、connection_epoch 和 cid，返回 OVERLOAD 并暂停本批后续 drain。下一次
drain 先重试该 pending control，成功后才继续 FIFO；不会重新生成内容或让新
控制越过它。终态 INVALID/CLOSED 计 rejected 并清除 pending。每次 OVERLOAD
都计数，成功只计一次 applied。

close 仅停止 bridge admission 并关闭 Runtime queue，保留已排队与 pending
控制供 drain；不关闭或销毁 World Session。close 后 submit 返回 CLOSED。
`pending = queue enqueued-dequeued + pending control`。destroy 在 pending 非
零时返回 false 且资源不变；pending 为零才 unsubscribe、destroy queue 和
bridge。调用方随后才安全销毁 session/publication。

该顺序对应 Coordinator 的 stop_admission→close_queues→drain→join/destroy，
但本项不注册 coordinator callback。destroy 不做隐式 World apply，TIMEOUT
重试只表示原 pending 保持不变。

## 验证

- kind/56-byte 格式、key 0、两个高 32 位非零 key、u64 correlation 高位不丢；
  旧 BRWC cid=0，新 correlated 路径高位 cid 经真实 socket 保留。
- open/close/reopen、重复 open、unknown close、容量失败；A 的 ACK/NEED_FULL/
  close 不修改 B。同 key 新 epoch 拒绝旧控制。
- level 0 初始、相同/倒退/排队旧 level 拒绝；level 7→8 后旧 ACK 不裁剪新
  history，两连接分别 full/ACK。queue generation/publication epoch 不参与
  该判定。
- 固定 56-byte 控制与既有 Runtime 16 MiB exact/+1 回归分开；网络 64 KiB、
  completion 16 MiB、Runtime 16 MiB、BRWD 64 MiB 不混用。
- A1/B1/A2 FIFO 与有界 drain；queue 满显式 OVERLOAD，排空后同 cid/内容
  重试；transport pending 重试保持原 control/cid/cursor。
- close 后 FIFO drain、pending 非零拒绝 destroy、清空后成功；
  既有 lease 与 World Session 生命周期不依赖 bridge。
- 默认 `fair_outbound_admission=false` 不变；显式 true 的既有公平测试不变。
- 每项生产缺陷修复附定向变异判红并恢复，focused normal、ASan+UBSan
  （显式 leak 检测）、TSan 和完整 Vulkan/OpenGL；独立任务与整分支评审后
  推送并核验远端矩阵。


## 修订（2026-11-25）：共享 Bus 外部 ingress 与 shutdown 竞态

本修订替代前文关于 direct submit 经 Bus fan-out、`submitted-drained` pending
以及“清空后才 unsubscribe”的三处实现描述，公共函数签名和 56 字节布局不变。

- `break_runtime_world_session_submit` 现在只执行 `break_runtime_message_copy` 和
  `break_runtime_queue_enqueue`，精确使用本次调用的结果，不再发布到 Bus，也不
  观察 enqueued 差值。kind 注册与订阅继续服务合法外部生产者；直接 Bus publish
  会向每个匹配 adapter 投递独立副本。`submitted` 只计自有 submit 成功，
  `drained` 则包括自有和外部消息，二者不得相减作为 queue occupancy。
- `stats.queued` 与 `pending()` 统一使用 Runtime queue 实际的
  `enqueued-dequeued`；`pending()` 再加 `control_pending`。因此外部投递不会伪造
  submitted，也不会在 drained 大于 submitted 时造成无符号下溢。
- destroy 首先置 closed 并 `queue_close`，随后 unsubscribe 并记录
  `unsubscribed`，最后才按实际 pending 判定。pending 非零仍返回 false，但此后
  direct submit=CLOSED、外部 Bus 不再有该订阅者，drain 可继续；清零后的重试
  跳过重复退订并释放资源。可能成功的 destroy 仍要求调用方外部 quiesce，World
  调用依旧只能发生在 owner drain。
- connection epoch 耗尽是终态 `BREAK_RUNTIME_REJECTED` 并计 rejected，不再是
  未计数的 OVERLOAD。耗尽边界只通过 `BREAK_RUNTIME_TESTING` seam 覆盖，正式库
  不包含该 seam。
