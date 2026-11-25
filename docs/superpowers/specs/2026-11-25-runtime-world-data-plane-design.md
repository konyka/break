# Runtime World Snapshot Notice 数据面设计

日期：2026-11-25  
状态：已实施（2026-11-25 提交 9f21c28f）。

## 目标与边界

把现有三个独立能力连接起来：

1. owner 在 ECS 结构屏障后构建并发布 immutable snapshot；
2. Runtime 生产线程提交固定大小的 `PUBLISH_CURRENT` notice；
3. 唯一 owner drain 获取一把 snapshot lease，在有限连接预算内驱动现有 World Session full/delta 与 BRWD/BRFG 发送。

本切片只覆盖 outbound handoff。复用每连接 full/delta、ACK、history、NEED_FULL、OVERLOAD attempt 和真实 socket，不改变 BRWD/BRFG wire，也不把 diagnostic World 或 snapshot 当作共享 live World。

明确排除：

- 跨线程传递或共享 live `World *`，多连接 inbound 写同一 World；
- 权威 simulation 合并、权限仲裁、预测、回滚和 authority handoff；
- 跨 World 持久 NetEntity 身份；
- AOI、witness/scope 和 Real/Ghost 路径合并；
- 自动换级、自动 rebaseline、资产选择/加载和在线 schema 协商；
- inbound completion 到 Runtime Bus 的映射或目的 World 自动选择；
- 每 tick 或每 publication epoch 可靠广播，跨连接原子同 epoch 广播；
- exactly-once 网络或对端交付声明；
- BRFG correlation 扩展和 core_app 自动接线。

## 方案比较

### A：标量 notice + latest-current mailbox（采用）

生产者只提交标量。publication 保存 latest current，owner drain 每次最多 acquire 一把 lease，并在有界预算内 fan-out。

优点：RuntimeOwnedMessage 不需要析构；notice 丢弃不泄漏 lease；复用现有 attempt/history；可用少量标量状态完成去重、续发和 shutdown。

代价：中间 epoch 可合并；不同 drain 可使用不同 current；active attempt 续发成功不等于 latest current 已完成，必须按实际 attempt 身份判账。

### B：有界 lease-owning queue

每个 epoch 独立持有 lease并排队，可提供更精确的 epoch 顺序。但需要新的带析构队列、逐订阅者 retain、慢连接内存上限和 shutdown 回收，且仍不能保证对端 exactly-once。当前切片不采用。

### C：调用方同步 fan-out

调用方直接逐连接调用 World Session。它要求调用方已经是 owner 线程，无法解决跨线程生产；编码和发送会阻塞调用方，增加预算后又需要 A 的 continuation 状态。当前不采用。

## 硬约束

- 现有 Runtime adapter queue 将全部容量保留给 control。notice 是请求 owner 执行发布的控制 handoff，必须使用 `BREAK_RUNTIME_MESSAGE_FLAG_CONTROL`，不能改成普通 data flag。
- `break_world_session_publish_snapshot()` 遇到 active attempt 会续发旧字节并忽略新 target。只有先暴露实际 active attempt 的 target，才能区分 E1 与 E2。
- notice 不携带 publication epoch。实际去重只使用 owner drain acquire 到的 lease epoch。
- publication CLOSED、单连接 INVALID/CLOSED 和其他终态必须清 continuation，不能形成永久 TIMEOUT。
- 现有 56 字节 `BreakRuntimeWorldCommand`、五类控制命令、默认全 control-reserved queue 和 `publication == NULL` 的行为不变。

## 公共合同

### Notice 与 direct submit

```c
#define BREAK_RUNTIME_WORLD_SESSION_PUBLISH_CURRENT_KIND 0x5754u
#define BREAK_RUNTIME_WORLD_SESSION_PUBLISH_CURRENT_VERSION 1u

typedef struct {
    u64 level_generation;
    u64 reserved_zero;
} BreakRuntimeWorldPublishCurrentNotice;

BREAK_STATIC_ASSERT(sizeof(BreakRuntimeWorldPublishCurrentNotice) == 16u,
                    "BreakRuntimeWorldPublishCurrentNotice must be 16 bytes");

BreakRuntimeError break_runtime_world_session_submit_publish_current(
    BreakRuntimeWorldSession *adapter,
    const BreakRuntimeWorldPublishCurrentNotice *notice,
    u64 correlation_id);
```

- `level_generation` 与 dequeue 时的 Session level 比较；level 0 合法。
- `reserved_zero` 必须为 0。
- 不包含 snapshot、lease、publication 指针、target id/tick 或 publication epoch。
- correlation 仅位于 Runtime message metadata，不进入 payload 或 BRFG。
- submit 可在生产线程调用，只做校验、bounded copy 和 enqueue；不得调用 publication 或 World Session。
- publication 未配置返回 REJECTED；adapter 已关闭返回 CLOSED；格式错误返回 INVALID；queue 满返回 OVERLOAD 且 sender state 不变。
- 与现有控制命令共用 adapter-local sequence，仅成功入队递增。`submitted` 统计两类 direct submit，`drained` 统计实际消费的控制命令与 notice；现有 `applied` 不冒充发布成功计数。

消息 metadata：

```text
kind = 0x5754
version = 1
flags = BREAK_RUNTIME_MESSAGE_FLAG_CONTROL
sequence = adapter-local sequence
correlation_id = caller value
size = 16
```

### Config 尾部追加

```c
BreakWorldSnapshotPublication *publication; /* borrowed; NULL disables */
u32 publish_connection_budget;              /* 0 = 8; allowed 1..64 */
```

- `publication == NULL && publish_connection_budget != 0` 时 create 失败。
- publication 非空且 budget 为 0 时取 8；大于 64 时 create 失败。
- 每次 drain 的实际连接调用预算还受 `max_connections` 限制。
- publication、Bus、Session 都是 borrowed，必须晚于 adapter 销毁。

### Stats 尾部追加

```c
u64 publish_overloads; /* publish_snapshot 返回 OVERLOAD 的次数 */
u64 publish_terminal;  /* 发布遇到终态的次数 */
bool publish_pending;  /* request 或 continuation 尚未终止 */
```

现有 `control_pending` 仍只表示 ACK/NEED_FULL transport retry；`transport_overloads` 不混入数据面 OVERLOAD。

### 外部 Bus

首版不注册、不订阅 `0x5754`。普通 Bus publish 因未知 kind 返回 REJECTED 且 delivered=0；direct submit 不经过 Bus。

这样避免多个 adapter 无意 fan-out和 Bus 部分 OVERLOAD 的重试歧义。未来若支持，必须明确部分投递后的重复风险，不能宣称 exactly-once。

### WorldSession active attempt 身份

在 `BreakWorldSessionSenderState` 尾部追加：

```c
u64 attempt_target_snapshot_id;
u64 attempt_target_tick;
```

- `attempt_pending == false` 时二者为 0。
- active 时返回实际 immutable attempt 的 target，而不是本次调用方传入的 target。
- 不改变 `break_world_session_sender_state()` 签名、发送结果、history 或 wire。

`next_delta_id` 在 attempt build 成功时已经递增，不能替代这两个字段判断实际完成的是哪个 target。

## Owner drain 与 coalescing

### 固定边界

1. 先重试现有 `control_pending`；仍 OVERLOAD 时结束，本次不处理新 notice 或 publish continuation。
2. 按 FIFO 消费最多 `max_messages` 个 queue message。现有控制命令保持当前语义；合法 notice 只合并 `publish_request`。wrong-level notice 返回 STALE，不覆盖已有合法 request。
3. 若本批有 request 或此前有 continuation，acquire 一次 publication。
4. 用同一 lease 在连接预算内 fan-out；每连接每次 drain 最多调用一次 `publish_snapshot()`。
5. 离开 drain 前经统一出口 release lease。所有 acquire 结果路径都遵守该边界。
6. 重新计算 continuation 和 `publish_pending`。

notice 是 coalescing invalidation request，不是同步 fan-out barrier。同批后到的 CLOSE/REBASELINE 会影响 batch 末尾的连接集合。`max_messages=0` 不 acquire、不续发。

### Lease 与 continuation

不跨 drain 持有 lease。adapter 只保存标量：fanout cursor、request level、观察到的 epoch，以及每连接 completed/terminal/attempt/retry 状态。World Session 的 attempt/history 已自行 retain target。

同一 drain 新创建的 attempt 使用同一 current lease；不同 drain 可使用不同 current；active attempt 始终可能更旧。因此不提供跨连接原子同 epoch 广播。

### 有限预算与公平游标

- budget 限制 `publish_snapshot()` 调用总数，包括 OVERLOAD 和终态调用。
- 固定连接表采用 round-robin cursor；每次尝试后前进，单连接 OVERLOAD 不中止其他连接。
- clean skip 不消耗调用预算；一轮最多扫描 `max_connections` 个槽。
- continuation 未清时，即使 queue 已空，`drain(max_messages > 0)` 仍继续 fan-out。
- 没有打开连接时 request 正常消费并清空，不等待未来 OPEN；未来 OPEN 不隐式发布 current，仍需新 notice。

## 每连接判账

每连接至少保存：

```text
completed_publication_epoch
terminal_publication_epoch
attempt_publication_epoch
attempt_target_snapshot_id / attempt_target_tick
retry_publish
```

这些字段带 level 语义，在 close/reopen/rebaseline 时清零。

`completed` 只表示 `publish_snapshot()` 返回 OK、所有 fragment 已被 reactor 接受；不表示 socket 已写完或对端 ACK。

### 调用前

即使 completed epoch 等于 current，也查询 sender state，防止忽略外部或此前遗留的 active attempt。记录调用前的实际 active target。clean skip 不调用 publish，但必须没有旧 attempt/retry。

### OK

返回 OK 后再次读取 sender state，以实际 `attempt_pending` 和 target 判账；不得只凭返回值清理 retry。

- 调用前没有 active attempt：OK 表示 current 已创建并完成 enqueue，记 `completed=current_epoch`。
- 调用前 active target 与 current lease 相同：记 `completed=current_epoch`。
- 与 adapter 保存的旧 attempt 相同：只记 `completed=attempt_publication_epoch`；current 若更新则仍保持 dirty。
- 与二者都不同：按未知旧 attempt 完成处理，不得把 current 标为 completed；current 随后仍需发送。
- 只有实际 active attempt 已结束时才清对应 attempt/retry 标量。

### OVERLOAD

- 保存 retry 和实际 active target；若该 attempt 是本轮以 current 创建，记 `attempt_publication_epoch=current_epoch`。
- 若尚未创建 attempt，则只保 retry，不虚构 attempt epoch。
- 不更新 completed，继续其他连接。

### 终态

- INVALID/CLOSED：清 retry/attempt，记 `terminal=current_epoch`，继续其他连接；相同 epoch 不自动重试，新 epoch 可再尝试。
- 未预期错误映射 FAILED，同样不得留下永久 continuation；不得伪装成可恢复 OVERLOAD。

### E1 → E2 示例

1. A 以 E1 创建 attempt 并 OVERLOAD：保存 attempt=E1，不记 completed。
2. publication current 前进到 E2。
3. 下轮 acquire E2，但 A 的 active target 仍为 E1。
4. `publish_snapshot(E2)` 续发 E1 并返回 OK：只记 completed=E1；A 相对 E2 仍 dirty，pending 保持。
5. cursor 已前进，其他连接不受阻。
6. 后续轮到 A 且没有 active attempt 时才创建 E2；成功后才记 E2 completed。

## Epoch 与生命周期

### 代次不能互换

- `level_generation`：World BRWD/BRWC 流级别。
- `publication_epoch`：单个 publication 实例内的 mailbox 单调序号，只用于去重和判账。
- `connection_epoch`：adapter 分配的 key 实例身份。
- Runtime queue generation：只保护 queue admission/close。
- BRFG stream_epoch：仍由 protocol/schema/level 计算，wire 不变。
- correlation：Runtime ingress 因果 metadata，不是投递去重键。
- snapshot id 是内容哈希，不是跨 World 或跨 level 持久身份。
- delta id 是每连接发送历史身份，不等于 publication epoch。

### CLOSE / reopen

CLOSE 复用现有 Session close，释放 active attempt/history，并清该槽全部 fanout 状态。同 key reopen 获得新 connection_epoch，dedup/terminal/attempt 从零开始，下一包必须 full。旧控制仍按现有 epoch 返回 STALE。

若 batch 末尾仍有同 level request，新连接可纳入实际 fan-out；旧 attempt 绝不能记到新 connection_epoch。

### REBASELINE

保持现有严格递增 level 和 connection epoch，清所有连接的 fanout 状态及旧 level continuation。rebaseline 前的旧 level request 取消，之后的新 level notice 可重新建立 request。

acquire 到的 lease level 与 Session 不一致时返回 STALE，不执行 Session publish，清 adapter continuation并等待对齐后的新 notice；不自动 rebaseline，不形成永久 TIMEOUT。推荐生产顺序：publish 新 level → submit REBASELINE → submit PUBLISH_CURRENT。

### EMPTY / CLOSED / wrong-level / duplicate

- EMPTY：notice 正常消费，无 sender 改动或 continuation；以后需要新 notice。
- publication CLOSED：返回 CLOSED，终止并清 request/retry，不再 acquire/retry。World Session 已存在的 attempt 仍由 Session 持有，不假装完成。
- acquire INVALID 或 lease level mismatch：终态丢弃本轮 request，不形成 pending。
- wrong-level notice：STALE，无 sender state 变化，也不取消已有合法 continuation。
- 重复 notice：同批合并；跨批由每连接 completed/terminal epoch 去重。没有旧 attempt 且 current 已完成时，不增加 next_delta_id、不产生新包。
- NEED_FULL 不清 completed epoch；恢复由后续新 publication epoch 触发 full，不能靠重复同 epoch notice 强制重发。

## Shutdown 与 Coordinator

```text
pending = queue enqueued-dequeued
        + control_pending
        + publish_pending
```

`publish_pending` 包括未解析 request、预算耗尽的 continuation、OVERLOAD retry，以及 E1 已完成但 latest E2 尚未完成的状态。

- pending 非零时 destroy=false；destroy 仍先 close admission/unsubscribe，再检查真实 pending。
- queue 已空不代表 publish 已完成。
- 单连接终态和 publication CLOSED 不得留下永久 pending。
- adapter destroy 成功只释放 adapter，不表示 Session attempt、reactor outbound 或对端 ACK 已清空。

Coordinator 继续复用六阶段：stop_admission → stop_producers → close_queues → drain → join → destroy。

- lifecycle.drain_budget 限制 queue message 数；publish_connection_budget 独立限制每次 DRAIN 的连接调用数。
- DRAIN 后 pending 非零或结果为 OVERLOAD，映射 TIMEOUT。
- 下一次 stop 从同一 DRAIN callback 和 fanout cursor 恢复，不重复 stop_admission/close。
- STALE/INVALID/REJECTED/CLOSED 且 pending=0 可完成；join/destroy 精确重试不变。

正常顺序：停止 snapshot producer 和 submit → drain/destroy adapter → close/destroy publication → 按既有 owner 顺序处理 Session/reactor/Bus。

允许 publication 提前 close，其语义是丢弃尚未完成的 adapter fanout，而不是可靠 drain。publication destroy 早于 adapter destroy 仍是借用生命周期错误。

## 线程与背压

- producer 只能 build/publish/submit，不能调用 World Session。
- owner drain 是唯一 Session publish 入口；publication 锁内不得 diff、编码、AOI、发送或回调。
- 现有 adapter drain 在 mutex 内调用 Session/reactor；连接预算限制等待时间，本切片不宣称移除该锁或实现无锁 fan-out。
- 默认 `fair_outbound_admission=false` 保持全局 256 容量。A 占满全局队列时不承诺 B 成功。
- 双连接隔离测试显式 `fair_outbound_admission=true`，验证 A 达自身份额时 B 可推进；不修改默认 reactor config。

## 实施任务

### Task 1：暴露实际 active attempt 身份

文件：`world_session.[ch]`、`test_world_session_recovery.c`。

- 在 SenderState 尾部追加 target id/tick。
- 覆盖 E1 OVERLOAD、传 E2 或错误 level 续发仍显示 E1，以及 resume 成功、close、rebaseline 后归零。
- 既有 strict-tick、history、ACK、full/delta 和 wire 行为不变。

### Task 2：direct notice、fanout 状态机与生命周期

文件：`runtime_world_session.[ch]`、`runtime_world_session_lifecycle.[ch]`、`test_runtime_world_session.c`、`test_runtime_world_session_target_contract.cmake`。

- 增加 16 字节 notice、0x5754、direct submit、两个 config 字段和三个 stats 字段。
- pending 纳入 publish continuation；外部 Bus 不注册新 kind。
- 覆盖布局、pre-drain 无副作用、EMPTY/CLOSED/wrong-level、同 target full、独立 full/delta、重复 notice、budget continuation、E1/E2、终态、close/reopen/rebaseline、destroy 和 Coordinator 恢复。
- 保持 56 字节布局、全 control-reserved queue 和 runtime_core 依赖边界。

### Task 3：真实 socket、并发、文档与最终验收

文件：`test_world_session_loopback.c`、必要测试 target 配置、现有 Runtime World/snapshot 设计文档、`runtime_overview.md`、`runtime_message_model.md`、`runtime_network.md`、`runtime_thread_model.md`、`session_protocol.md`、`Implementation_Status.md`、`cross_engine/missing_capabilities.md`。

- 真实路径：snapshot build → publication publish → direct notice → owner adapter drain → BRWD/BRFG → AUTH/socket → 每连接独立 remote World drain。
- 覆盖双连接、独立 ACK、budget=1、显式 fair admission、E1/E2 和 lease release/replace 后恢复。
- 真线程测试使用原子起点/屏障和有界循环，不用固定 sleep 证明正确。
- 文档只追加带日期小节，不改写历史收据，不预写远端结果。

## 验证要求

严格 RED → GREEN。先让新增 API/布局/行为测试在旧实现失败，再写最小实现。

定向变异至少包括：

- 任意 OK 都把 current 标为 completed；
- 不读取 active attempt 身份；
- A OVERLOAD 后中止整个 fan-out；
- 删除 per-connection dedup；
- close/reopen/rebaseline 不清状态；
- continuation 不计 pending；
- submit 内直接调用 Session；
- notice 改成普通 data flag；
- 漏 release lease；
- 每连接分别 acquire。

每项均须可构建、判红、恢复，生产无残留变异。

所有网络 configure 使用固定 Snowflake `4ab761fc58a9d15970f295e231003c99a7d44df8` 和仓库指定私有路径。normal、ASan+UBSan（显式 `detect_leaks=1`）和 TSan 分别构建并实际执行 Runtime/World/publication/Session/loopback/bridge focused 集合；未构建或 Not Run 不计通过。

最终 HEAD 运行完整 OpenGL/Vulkan CTest，记录注册数、实际通过、条件 skip、失败数和耗时。条件 skip、既有 Lua longjmp、混合 TSan 和 Proton 77 不升级为原生 GPU 或完整 sanitizer 验收。

本切片完成后仍需后续项目处理共享 live World、权威 simulation 合并、跨 World 持久身份、自动换级、资产链和 inbound completion 映射。
