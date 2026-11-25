# Runtime World Snapshot Notice Data Plane Implementation Plan
> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** 用 16 字节 direct notice 把生产线程的 latest-current publication 接到唯一 owner drain，在有限连接预算内恢复现有 World Session full/delta、attempt、ACK 与 shutdown，而不改变网络 wire。

**Architecture:** 生产线程只 build/publish/submit 标量；adapter 的 owner drain 每次最多 acquire 一把 snapshot lease，并以 round-robin cursor 驱动既有 `break_world_session_publish_snapshot()`。World Session 先暴露实际 active attempt target，adapter 再按实际 target 与 publication epoch 判账；lease 不跨 drain，continuation 只保存标量。四个提交分别提供 active-attempt 身份、基础 notice 评审门、完整恢复评审门、真实 socket/文档/最终验收评审门。

**Tech Stack:** C11、CMake/CTest、RuntimeBus/RuntimeQueue、BreakWorldSnapshotPublication/BreakWorldSnapshotLease、BreakWorldSession、BRWD/BRFG/BRWC、Snowflake 真实 TCP loopback、PlatformThread/C11 atomics、ASan+UBSan、TSan。

## Global Constraints

- `BreakRuntimeWorldPublishCurrentNotice` 固定 **16 字节**，只含 `level_generation` 与必须为零的 `reserved_zero`；kind 固定 **0x5754**，version 固定 **1**。
- notice 必须使用 `BREAK_RUNTIME_MESSAGE_FLAG_CONTROL`；现有 **56 字节** `BreakRuntimeWorldCommand`、五类控制命令和全 control-reserved queue 不变。
- 首版**不支持外部 Bus**：不注册、不订阅 `0x5754`；外部 Bus publish 必须 `REJECTED` 且 `delivered=0`，direct submit 不经过 Bus。
- `publication == NULL` 的默认行为不变；此时非零 budget 使 create 失败。publication 非空时 `publish_connection_budget == 0` 取 **8**，允许值为 **1..64**，大于 64 create 失败；每次 drain 还受 `max_connections` 限制。
- publication、Bus、Session 都是 borrowed，必须晚于 adapter 销毁；producer 不调用 World Session，owner drain 是唯一 Session publish 入口，publication 锁内不做 diff、编码、AOI、发送或回调。
- lease 不跨 drain；每次 drain 最多 acquire 一次并统一 release。每连接每次 drain 最多调用一次 `publish_snapshot()`；OVERLOAD 和终态调用也消耗连接预算。
- `control_pending` 仍只表示 ACK/NEED_FULL transport retry；`transport_overloads` 不混入数据面 OVERLOAD；`applied` 不冒充发布成功计数。
- `pending = queue enqueued-dequeued + control_pending + publish_pending`；continuation 必须计入 pending，destroy 与 Coordinator 不能只检查 queue。
- 所有网络 configure 使用固定 Snowflake **`4ab761fc58a9d15970f295e231003c99a7d44df8`** 和私有路径 **`/home/timeshift/opensource/break/.worktrees/snowflake-pin-4ab761fc`**，并显式 `-DBREAK_ENABLE_SNOWFLAKE=ON -DSNOWFLAKE_SOURCE_DIR=/home/timeshift/opensource/break/.worktrees/snowflake-pin-4ab761fc`。
- 遵循现有 **C11/Google 风格**；文档只追加带 **2026-11-25** 日期的小节，不改写历史收据，不预写远端结果。
- 不改变 BRWD/BRFG/BRWC wire，不新增 wire 消息；未完成 socket 写入或对端 ACK 不得宣称完成。
- 排除共享 live `World *`、多连接 inbound 写同一 World、权威 simulation 合并/权限仲裁/预测/回滚/authority handoff、跨 World 持久 NetEntity 身份、AOI/witness/scope/Real/Ghost 合并、自动换级/自动 rebaseline、资产选择/加载、在线 schema 协商、inbound completion 自动映射、每 tick 或每 publication epoch 可靠广播、跨连接原子同 epoch 广播、exactly-once 交付、BRFG correlation 扩展和 core_app 自动接线。
- Task 2 是故意拆出的中间评审门，只证明无 active attempt 的基础路径；E1/E2、有限预算恢复、完整 pending/destroy/Coordinator 恢复必须等 Task 3，**不得把 Task 2 的中间提交称为完整数据面**。

---

### Task 1: 暴露 World Session 实际 active attempt 身份

**Files:**
- Modify: `engine/src/ecs/world_session.h`
- Modify: `engine/src/ecs/world_session.c`
- Test: `engine/tests/test_world_session_recovery.c`

**Interfaces:**
- Consumes: 既有 `break_world_session_publish_snapshot(BreakWorldSession *, BreakConnectionKey, BreakWorldSnapshot *, u64)`、`break_world_session_sender_state(const BreakWorldSession *, BreakConnectionKey, BreakWorldSessionSenderState *)`，以及测试中的 `fixture_init_scaled()`、`set_value()`、`collect_attempt_for_connection()`、`clear_attempt()`、`fixture_dispose()`。active attempt 会忽略本次传入的 target/level 并续发旧字节。
- Produces: 在 `BreakWorldSessionSenderState` 尾部追加以下两个字段，不改变函数签名、history、delta id、ACK 或 wire：

```c
typedef struct {
    size_t history_count;
    size_t history_bytes;
    u64 confirmed_snapshot_id;
    u64 confirmed_tick;
    u64 next_delta_id;
    bool attempt_pending;
    u64 attempt_target_snapshot_id;
    u64 attempt_target_tick;
} BreakWorldSessionSenderState;
```

`attempt_pending == false` 时两个字段均为 0；active 时是 `state->attempt.target` 的实际 immutable id/tick，而非调用参数。Task 2/3 将直接读取这两个字段。

- [ ] **Step 1: 配置固定依赖的 focused 构建树**

```sh
cmake -S engine -B engine/build-runtime-world-data-plane -G Ninja \
  -DCMAKE_BUILD_TYPE=Debug -DENGINE_BUILD_TESTS=ON \
  -DENGINE_RHI_BACKEND=opengl -DCORE_APP_ENABLE_NETWORK=ON \
  -DBREAK_ENABLE_SNOWFLAKE=ON \
  -DSNOWFLAKE_SOURCE_DIR=/home/timeshift/opensource/break/.worktrees/snowflake-pin-4ab761fc
```

Expected: configure 成功并打印 pinned commit `4ab761fc58a9d15970f295e231003c99a7d44df8` verified。

- [ ] **Step 2: 用现有 recovery 夹具写 E1/E2、错误 level、resume、close/reopen、rebaseline 的 RED 测试**

在 `test_world_session_recovery.c` 新增 `TEST(world_session_sender_state_reports_actual_active_snapshot_attempt)` 并注册到 `TEST_MAIN_BEGIN`。使用 64 字节 fragment 让 full 分片；队列完全饱和时 E1 建立 attempt 但没有 fragment 被接受。核心测试代码如下， outbound drain 循环沿用本文件既有 `break_net_reactor_poll_outbound_for_test()` + `break_net_message_release()` 写法：

```c
Fixture fixture;
BreakWorldSnapshot *e1 = NULL, *e2 = NULL, *e3 = NULL;
BreakWorldSessionSenderState state;
AttemptWire resumed;
BreakNetOwnedMessage outbound;
u64 outbound_key = 0u;

ASSERT_TRUE(fixture_init_scaled(&fixture, 4u, 16384u, 4096u, 64u, 8u, 64u));
ASSERT_TRUE(set_value(fixture.authoritative, 42u));
e1 = break_world_snapshot_build(fixture.authoritative, fixture.schemas, 10u);
ASSERT_TRUE(set_value(fixture.authoritative, 99u));
e2 = break_world_snapshot_build(fixture.authoritative, fixture.schemas, 20u);
ASSERT_TRUE(set_value(fixture.authoritative, 123u));
e3 = break_world_snapshot_build(fixture.authoritative, fixture.schemas, 30u);
ASSERT_NOT_NULL(e1);
ASSERT_NOT_NULL(e2);
ASSERT_NOT_NULL(e3);

for (usize i = 0u; i < BREAK_NET_OUTBOUND_QUEUE_CAPACITY; ++i) {
    ASSERT_EQ(break_net_reactor_send(fixture.reactor, 11u,
                                     BREAK_NET_MESSAGE_ID_PING, 1u, "x", 1u),
              BREAK_NET_SEND_OK);
}
ASSERT_EQ(break_world_session_publish_snapshot(fixture.session, 11u, e1, TEST_LEVEL),
          BREAK_NET_SEND_OVERLOAD);
ASSERT_TRUE(break_world_session_sender_state(fixture.session, 11u, &state));
ASSERT_TRUE(state.attempt_pending);
ASSERT_EQ(state.attempt_target_snapshot_id, break_world_snapshot_id(e1));
ASSERT_EQ(state.attempt_target_tick, 10u);

/* E2 与错误 level 都不能替换 active E1。 */
ASSERT_EQ(break_world_session_publish_snapshot(fixture.session, 11u, e2, TEST_LEVEL),
          BREAK_NET_SEND_OVERLOAD);
ASSERT_TRUE(break_world_session_sender_state(fixture.session, 11u, &state));
ASSERT_EQ(state.attempt_target_snapshot_id, break_world_snapshot_id(e1));
ASSERT_EQ(state.attempt_target_tick, 10u);
ASSERT_EQ(break_world_session_publish_snapshot(fixture.session, 11u, e2, 8u),
          BREAK_NET_SEND_OVERLOAD);
ASSERT_TRUE(break_world_session_sender_state(fixture.session, 11u, &state));
ASSERT_EQ(state.attempt_target_snapshot_id, break_world_snapshot_id(e1));
ASSERT_EQ(state.attempt_target_tick, 10u);

while (break_net_reactor_poll_outbound_for_test(
           fixture.reactor, &outbound_key, &outbound) == BREAK_NET_EVENT_OK) {
    ASSERT_EQ(outbound.message_id, BREAK_NET_MESSAGE_ID_PING);
    break_net_message_release(&outbound);
}
ASSERT_EQ(break_world_session_publish_snapshot(fixture.session, 11u, e2, 8u),
          BREAK_NET_SEND_OK);
ASSERT_TRUE(collect_attempt_for_connection(&fixture, 11u, &resumed));
ASSERT_EQ(resumed.target_snapshot_id, break_world_snapshot_id(e1));
ASSERT_EQ(resumed.target_tick, 10u);
ASSERT_TRUE(break_world_session_sender_state(fixture.session, 11u, &state));
ASSERT_FALSE(state.attempt_pending);
ASSERT_EQ(state.attempt_target_snapshot_id, 0u);
ASSERT_EQ(state.attempt_target_tick, 0u);
clear_attempt(&resumed);

/* close/reopen 后身份归零。 */
for (usize i = 0u; i < BREAK_NET_OUTBOUND_QUEUE_CAPACITY; ++i) {
    ASSERT_EQ(break_net_reactor_send(fixture.reactor, 11u,
                                     BREAK_NET_MESSAGE_ID_PING, 1u, "x", 1u),
              BREAK_NET_SEND_OK);
}
ASSERT_EQ(break_world_session_publish_snapshot(fixture.session, 11u, e2, TEST_LEVEL),
          BREAK_NET_SEND_OVERLOAD);
ASSERT_TRUE(break_world_session_close(fixture.session, 11u));
ASSERT_FALSE(break_world_session_sender_state(fixture.session, 11u, &state));
ASSERT_EQ(state.attempt_target_snapshot_id, 0u);
ASSERT_EQ(state.attempt_target_tick, 0u);
while (break_net_reactor_poll_outbound_for_test(
           fixture.reactor, &outbound_key, &outbound) == BREAK_NET_EVENT_OK) {
    break_net_message_release(&outbound);
}
ASSERT_TRUE(break_world_session_open(fixture.session, 11u));
ASSERT_TRUE(break_world_session_sender_state(fixture.session, 11u, &state));
ASSERT_FALSE(state.attempt_pending);
ASSERT_EQ(state.attempt_target_snapshot_id, 0u);
ASSERT_EQ(state.attempt_target_tick, 0u);

/* rebaseline 复用现有 attempt 清理路径，也必须归零。 */
for (usize i = 0u; i < BREAK_NET_OUTBOUND_QUEUE_CAPACITY; ++i) {
    ASSERT_EQ(break_net_reactor_send(fixture.reactor, 11u,
                                     BREAK_NET_MESSAGE_ID_PING, 1u, "x", 1u),
              BREAK_NET_SEND_OK);
}
ASSERT_EQ(break_world_session_publish_snapshot(fixture.session, 11u, e3, TEST_LEVEL),
          BREAK_NET_SEND_OVERLOAD);
ASSERT_TRUE(break_world_session_sender_state(fixture.session, 11u, &state));
ASSERT_TRUE(state.attempt_pending);
ASSERT_EQ(state.attempt_target_snapshot_id, break_world_snapshot_id(e3));
ASSERT_EQ(state.attempt_target_tick, 30u);
ASSERT_TRUE(break_world_session_rebaseline(fixture.session, 8u));
ASSERT_TRUE(break_world_session_sender_state(fixture.session, 11u, &state));
ASSERT_FALSE(state.attempt_pending);
ASSERT_EQ(state.attempt_target_snapshot_id, 0u);
ASSERT_EQ(state.attempt_target_tick, 0u);

break_world_snapshot_release(e3);
break_world_snapshot_release(e2);
break_world_snapshot_release(e1);
fixture_dispose(&fixture);
```

- [ ] **Step 3: 构建并确认字段缺失导致 RED**

```sh
cmake --build engine/build-runtime-world-data-plane \
  --target test_world_session_recovery -j2
```

Expected: 编译失败，诊断指出 `BreakWorldSessionSenderState` 没有 `attempt_target_snapshot_id` / `attempt_target_tick` 成员；不得通过删除断言或复制调用方 E2 值来消除 RED。

- [ ] **Step 4: 最小实现尾部字段与实际 attempt 映射**

在 `world_session.h` 的 `attempt_pending` 后追加上述两个 `u64`，不要重排旧字段。在 `break_world_session_sender_state()` 中只增加：

```c
out_state->attempt_pending = state->attempt.active;
out_state->attempt_target_snapshot_id = state->attempt.active
    ? break_world_snapshot_id(state->attempt.target) : 0u;
out_state->attempt_target_tick = state->attempt.active
    ? break_world_snapshot_tick(state->attempt.target) : 0u;
```

`world_session_clear_attempt()` 已经 `memset` attempt，close/reopen 已经释放或重建连接，rebaseline 已逐连接调用 `world_session_clear_attempt()`；不要新增第二套清理状态，也不要改 `next_delta_id`、full/delta、history 或 wire。

- [ ] **Step 5: 运行 GREEN 与既有 recovery 回归**

```sh
cmake --build engine/build-runtime-world-data-plane \
  --target test_world_session_recovery test_world_session -j2
ctest --test-dir engine/build-runtime-world-data-plane --output-on-failure \
  -R '^(test_world_session_recovery|test_world_session)$'
```

Expected: 两个 CTest 均 PASS；新测试证明 E1 active 时传 E2/错误 level 仍报告 E1，resume/close/reopen/rebaseline 后均为 0，既有测试不回归。

- [ ] **Step 6: 定向变异与 focused sanitizer**

先备份 `world_session.c`，分别做两个可构建变异并在每个变异后运行上一步两个 CTest：把 active id/tick 都写成 0，预期新测试在 E1 active 断言失败；把 id 错写为 `next_delta_id`，预期 id 断言失败。每个变异后从备份恢复，最终再跑 GREEN。随后配置并运行 ASan+UBSan：

```sh
cmake -S engine -B engine/build-runtime-world-data-plane-asan -G Ninja \
  -DCMAKE_BUILD_TYPE=Debug -DENGINE_BUILD_TESTS=ON \
  -DENGINE_RHI_BACKEND=opengl -DCORE_APP_ENABLE_NETWORK=ON \
  -DENGINE_USE_ASAN=ON -DENGINE_USE_UBSAN=ON \
  -DBREAK_ENABLE_SNOWFLAKE=ON \
  -DSNOWFLAKE_SOURCE_DIR=/home/timeshift/opensource/break/.worktrees/snowflake-pin-4ab761fc
cmake --build engine/build-runtime-world-data-plane-asan \
  --target test_world_session_recovery test_world_session -j2
ASAN_OPTIONS=detect_leaks=1 UBSAN_OPTIONS=halt_on_error=1 \
  ctest --test-dir engine/build-runtime-world-data-plane-asan \
  --output-on-failure -R '^(test_world_session_recovery|test_world_session)$'
```

Expected: 两个变异均 RED，恢复后 normal 与 ASan+UBSan 全绿，无 sanitizer/leak 诊断，源码中无残留变异。

- [ ] **Step 7: 实现者先提交，controller 随后评审该提交**

实现者完成上述验证后先执行：

```sh
git diff --check
git add engine/src/ecs/world_session.h engine/src/ecs/world_session.c \
  engine/tests/test_world_session_recovery.c
git commit -m "feat(world): expose active snapshot attempt identity"
```

controller 以该提交 SHA 和其 RED/GREEN、sanitizer 证据组成 review package，随后进行独立评审；不得以未提交 HEAD 作为评审对象。

Expected: 提交后 `git status --short` 不含本任务文件；controller 的独立评审确认只暴露实际 attempt 身份，评审通过后才进入 Task 2。

---

### Task 2: 新增 direct notice、配置/统计与无 active attempt 的基础 fanout

**Files:**
- Modify: `engine/src/runtime/runtime_world_session.h`
- Modify: `engine/src/runtime/runtime_world_session.c`
- Modify: `engine/src/runtime/runtime_world_session_lifecycle.h`
- Test: `engine/tests/test_runtime_world_session.c`
- Test: `engine/tests/test_runtime_world_session_target_contract.cmake`

**Interfaces:**
- Consumes: Task 1 的 `BreakWorldSessionSenderState.attempt_target_snapshot_id/attempt_target_tick`；既有 `open_connection()`、`make_target()`、`publish_target()`、`control_via_adapter()`、`clear_outbound()`、`fixture_init_without_adapter()`、`fixture_attach()`、`fixture_dispose()`；真实 publication API：

```c
BreakWorldSnapshotAcquireResult break_world_snapshot_publication_acquire(
    BreakWorldSnapshotPublication *publication, BreakWorldSnapshotLease *out_lease);
bool break_world_snapshot_publication_publish(
    BreakWorldSnapshotPublication *publication,
    BreakWorldSnapshot *snapshot, u64 level_generation);
void break_world_snapshot_publication_close(BreakWorldSnapshotPublication *publication);
void break_world_snapshot_lease_release(BreakWorldSnapshotLease *lease);
```

- Produces: 以下公共 ABI 与私有状态是本任务和后续任务的精确接口。公共字段只能追加到现有 Config/Stats 尾部：

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

/* BreakRuntimeWorldSessionConfig 尾部： */
BreakWorldSnapshotPublication *publication; /* borrowed; NULL disables */
u32 publish_connection_budget;              /* 0 = 8; allowed 1..64 */

/* BreakRuntimeWorldSessionStats 尾部： */
u64 publish_overloads;
u64 publish_terminal;
bool publish_pending;
```

在 `runtime_world_session.c` 内定义并初始化后续任务使用的完整标量状态；本任务只要求无 active attempt 的基本路径：

```c
typedef struct {
    u64 key;
    u64 epoch;
    u64 completed_publication_epoch;
    u64 terminal_publication_epoch;
    u64 attempt_publication_epoch;
    u64 attempt_target_snapshot_id;
    u64 attempt_target_tick;
    bool retry_publish;
} RuntimeWorldConnection;

/* BreakRuntimeWorldSession 的字段： */
BreakWorldSnapshotPublication *publication;
u32 publish_connection_budget;
u64 publish_overloads;
u64 publish_terminal;
bool publish_request;
bool publish_continuation;
u64 publish_request_level;
u64 publish_observed_epoch;
usize publish_cursor;
```

私有 helper 的固定签名如下；Task 3 在同一签名内补齐 attempt 判账与恢复：

```c
static bool runtime_world_publish_pending_locked(
    const BreakRuntimeWorldSession *adapter);
static void runtime_world_clear_connection_publish(
    RuntimeWorldConnection *connection);
static void runtime_world_clear_publish(
    BreakRuntimeWorldSession *adapter, bool clear_attempts);
static BreakRuntimeError runtime_world_apply_notice(
    BreakRuntimeWorldSession *adapter,
    const BreakRuntimeWorldPublishCurrentNotice *notice);
static BreakRuntimeError runtime_world_publish_connection(
    BreakRuntimeWorldSession *adapter, usize slot,
    const BreakWorldSnapshotLease *lease, bool *out_called);
static bool runtime_world_recompute_continuation(
    BreakRuntimeWorldSession *adapter, u64 current_epoch);
static BreakRuntimeError runtime_world_publish_current(
    BreakRuntimeWorldSession *adapter);

/* 后续任务继续使用的测试 helper： */
static bool fixture_attach_publication(
    Fixture *fixture, u32 queue_capacity, u32 max_connections,
    BreakWorldSnapshotPublication *publication, u32 publish_connection_budget);
static bool fixture_init_publication(
    Fixture *fixture, u64 level, u32 max_connections, u32 publish_connection_budget);
static BreakRuntimeError submit_current(Fixture *fixture, u64 level, u64 correlation_id);
```

`runtime_world_publish_pending_locked()` 返回 `publish_request || publish_continuation`；`runtime_world_pending_locked()` 把它作为一个布尔 pending 加入既有 queue/control pending。`runtime_world_clear_connection_publish()` 只清 completed/terminal/attempt 三个 epoch、attempt target id/tick 和 retry 这六类 publication 判账字段，保留 key/epoch。

- [ ] **Step 1: 写布局、配置、direct submit、外部 Bus 与默认兼容 RED 断言**

在 `test_runtime_world_session.c` 增加 `_Static_assert`：`sizeof(notice)==16`、`offsetof(level_generation)==0`、`offsetof(reserved_zero)==8`，并保留现有 `BreakRuntimeWorldCommand==56` 的全部断言。新增 `TEST(publish_notice_layout_submit_and_external_bus_contract)`，核心断言为：

```c
BreakRuntimeWorldPublishCurrentNotice notice = {7u, 0u};
BreakRuntimeWorldPublishCurrentNotice bad = {7u, 1u};
BreakRuntimeWorldSessionConfig config;
BreakRuntimeWorldSessionStats stats;
BreakRuntimeMessageView view;
BreakWorldSnapshotPublicationConfig publication_config;
BreakWorldSnapshotPublication *publication;
u32 delivered = 99u;

ASSERT_TRUE(fixture_init_without_adapter(&fixture, 7u));
memset(&config, 0, sizeof(config));
memset(&publication_config, 0, sizeof(publication_config));
publication_config.schema_hash = break_schema_hash(fixture.schemas);
publication_config.level_generation = 7u;
publication = break_world_snapshot_publication_create(&publication_config);
ASSERT_NOT_NULL(publication);
fixture.publication = publication;

/* publication=NULL 且 budget!=0，或 budget>64，create 必须为 NULL。 */
config.session = fixture.session;
config.bus = fixture.bus;
config.subscriber_name = NULL;
config.queue_capacity = 1u;
config.max_connections = 2u;
config.publication = NULL;
config.publish_connection_budget = 1u;
ASSERT_EQ(break_runtime_world_session_create(&config), NULL);
config.publication = publication;
config.publish_connection_budget = 65u;
ASSERT_EQ(break_runtime_world_session_create(&config), NULL);

/* budget=0 合法并选择 8；direct submit 只入自有 control queue。 */
config.publish_connection_budget = 0u;
fixture.adapter = break_runtime_world_session_create(&config);
ASSERT_NOT_NULL(fixture.adapter);
ASSERT_EQ(break_runtime_world_session_submit_publish_current(
              fixture.adapter, NULL, HIGH_CID), BREAK_RUNTIME_INVALID);
ASSERT_EQ(break_runtime_world_session_submit_publish_current(
              fixture.adapter, &bad, HIGH_CID), BREAK_RUNTIME_INVALID);
ASSERT_EQ(break_runtime_world_session_submit_publish_current(
              fixture.adapter, &notice, HIGH_CID), BREAK_RUNTIME_OK);
ASSERT_EQ(break_runtime_world_session_submit_publish_current(
              fixture.adapter, &notice, HIGH_CID), BREAK_RUNTIME_OVERLOAD);
break_runtime_world_session_stats(fixture.adapter, &stats);
ASSERT_EQ(stats.submitted, 1u);
ASSERT_EQ(stats.drained, 0u);
ASSERT_EQ(stats.next_sequence, 2u);
ASSERT_EQ(stats.queued, 1u);
ASSERT_EQ(stats.publish_overloads, 0u);

/* kind 未注册，普通 Bus publish 不可进入 adapter。 */
memset(&view, 0, sizeof(view));
view.kind = BREAK_RUNTIME_WORLD_SESSION_PUBLISH_CURRENT_KIND;
view.version = BREAK_RUNTIME_WORLD_SESSION_PUBLISH_CURRENT_VERSION;
view.sequence = UINT64_MAX;
view.correlation_id = HIGH_CID;
view.data = &notice;
view.size = sizeof(notice);
ASSERT_EQ(break_runtime_bus_publish(fixture.bus, &view, &delivered),
          BREAK_RUNTIME_REJECTED);
ASSERT_EQ(delivered, 0u);
break_runtime_world_session_stats(fixture.adapter, &stats);
ASSERT_EQ(stats.queued, 1u);

break_runtime_world_session_close(fixture.adapter);
ASSERT_EQ(break_runtime_world_session_submit_publish_current(
              fixture.adapter, &notice, HIGH_CID), BREAK_RUNTIME_CLOSED);
/* fixture_dispose 先 drain/destroy adapter，再 close/destroy publication。 */
fixture_dispose(&fixture);
```

另用既有 `fixture_init(&fixture, 7u, 2u)` 跑一个未配置 publication 的默认兼容断言：旧 `break_runtime_world_session_submit()` 的 OPEN 仍成功，新 notice 返回 `BREAK_RUNTIME_REJECTED`，Session sender state 与 `next_sequence` 不变。queue capacity=1 且全部 reserved_control，首个 notice 能入队也同时证明它不是 data flag。

- [ ] **Step 2: 增加真实 publication 测试夹具并写 pre-drain/S1 full 断言**

保留现有 `fixture_attach()` 默认传 `publication=NULL,budget=0`，新增测试 helper：

```c
static bool fixture_attach_publication(Fixture *fixture, u32 queue_capacity,
                                       u32 max_connections,
                                       BreakWorldSnapshotPublication *publication,
                                       u32 publish_connection_budget)
{
    BreakRuntimeWorldSessionConfig config;
    memset(&config, 0, sizeof(config));
    config.session = fixture->session;
    config.bus = fixture->bus;
    config.queue_capacity = queue_capacity;
    config.max_connections = max_connections;
    config.publication = publication;
    config.publish_connection_budget = publish_connection_budget;
    fixture->adapter = break_runtime_world_session_create(&config);
    return fixture->adapter != NULL;
}

static bool fixture_init_publication(Fixture *fixture, u64 level,
                                     u32 max_connections, u32 publish_connection_budget)
{
    BreakWorldSnapshotPublicationConfig config;
    if (!fixture_init_without_adapter(fixture, level)) return false;
    memset(&config, 0, sizeof(config));
    config.schema_hash = break_schema_hash(fixture->schemas);
    config.level_generation = level;
    fixture->publication = break_world_snapshot_publication_create(&config);
    return fixture->publication &&
           fixture_attach_publication(fixture, 0u, max_connections,
                                      fixture->publication, publish_connection_budget);
}

static BreakRuntimeError submit_current(Fixture *fixture, u64 level, u64 correlation_id)
{
    BreakRuntimeWorldPublishCurrentNotice notice = {level, 0u};
    return break_runtime_world_session_submit_publish_current(
        fixture->adapter, &notice, correlation_id);
}
```

在 `Fixture` 尾部增加 `BreakWorldSnapshotPublication *publication`；`fixture_dispose()` 必须先 close/drain/destroy adapter，再 close/destroy publication，然后才销毁 Bus/Session/World。新增 `TEST(publish_notice_basic_s1_full_has_no_pre_drain_effects)`：用 `open_connection()` 打开 KEY_A， `make_target(&fixture,42u,10u)` 构建 S1， `break_world_snapshot_publication_publish(...,7u)` 发布 epoch1。提交 notice 后以 `memcmp` 比较提交前后的 `BreakWorldSessionSenderState`、`BreakWorldSessionStats`，并断言 `break_net_reactor_outbound_count()==0`。随后：

```c
ASSERT_EQ(submit_current(&fixture, 7u, HIGH_CID), BREAK_RUNTIME_OK);
/* 此处比较 before/after，必须完全无副作用。 */
ASSERT_EQ(break_runtime_world_session_drain(fixture.adapter, 1u, &drained),
          BREAK_RUNTIME_OK);
ASSERT_EQ(drained, 1u);
ASSERT_TRUE(break_world_session_sender_state(fixture.session, KEY_A, &after));
ASSERT_EQ(after.history_count, 1u);
ASSERT_EQ(after.next_delta_id, 2u);
ASSERT_FALSE(after.attempt_pending);
break_world_session_stats(fixture.session, &world_after);
ASSERT_EQ(world_after.published_full_packets, 1u);
ASSERT_EQ(world_after.published_delta_packets, 0u);
break_runtime_world_session_stats(fixture.adapter, &stats);
ASSERT_FALSE(stats.publish_pending);
ASSERT_EQ(break_runtime_world_session_pending(fixture.adapter), 0u);
```

- [ ] **Step 3: 写同 target 的独立 full/delta 与重复 notice 去重断言**

新增 `TEST(publish_notice_connections_keep_independent_full_delta_and_dedup)`。KEY_A/KEY_B 都由 `open_connection()` 打开；S1 drain 后只通过既有 `control_via_adapter(...BREAK_RUNTIME_WORLD_COMMAND_ACK, KEY_A, epoch_a, 7u, 1u, s1, ...)` ACK A。发布同 World 后续构建的 S2/tick20，再提交 notice。以 `BreakWorldSessionStats` 和每连接 sender state 精确断言：

```c
BreakRuntimeWorldSessionStats runtime_stats;
u64 submitted_before;
u64 drained_before;

/* S2 之前 full=2, delta=0；只有 A confirmed S1。 */
ASSERT_EQ(break_runtime_world_session_drain(fixture.adapter, 1u, &drained),
          BREAK_RUNTIME_OK);
break_world_session_stats(fixture.session, &after);
ASSERT_EQ(after.published_full_packets, 3u);  /* B 未 ACK，仍 full */
ASSERT_EQ(after.published_delta_packets, 1u); /* A 已 ACK，独立 delta */
ASSERT_TRUE(break_world_session_sender_state(fixture.session, KEY_A, &a_state));
ASSERT_TRUE(break_world_session_sender_state(fixture.session, KEY_B, &b_state));
ASSERT_EQ(a_state.confirmed_snapshot_id, break_world_snapshot_id(s1));
ASSERT_EQ(a_state.history_count, 1u);
ASSERT_EQ(a_state.next_delta_id, 3u);
ASSERT_EQ(b_state.confirmed_snapshot_id, 0u);
ASSERT_EQ(b_state.history_count, 1u); /* 已由实现修正为 1（full 会清旧 history），原计划写 2 */
ASSERT_EQ(b_state.next_delta_id, 3u);

before = after;
break_runtime_world_session_stats(fixture.adapter, &runtime_stats);
submitted_before = runtime_stats.submitted;
drained_before = runtime_stats.drained;
ASSERT_EQ(submit_current(&fixture, 7u, 0u), BREAK_RUNTIME_OK);
ASSERT_EQ(submit_current(&fixture, 7u, 0u), BREAK_RUNTIME_OK);
ASSERT_EQ(break_runtime_world_session_drain(fixture.adapter, 2u, &drained),
          BREAK_RUNTIME_OK);
ASSERT_EQ(drained, 2u);
break_runtime_world_session_stats(fixture.adapter, &runtime_stats);
ASSERT_EQ(runtime_stats.submitted, submitted_before + 2u);
ASSERT_EQ(runtime_stats.drained, drained_before + 2u);
break_world_session_stats(fixture.session, &after);
ASSERT_EQ(memcmp(&before, &after, sizeof(after)), 0);
```

两个 direct notice 成功入队，所以 `submitted` 增 2；两个都被实际消费，所以 `drained` 增 2。重复 notice 不能增加 `next_delta_id`、history 或新包；本测试不断言 `applied`，它绝不表示 publish 成功。

- [ ] **Step 4: 写 EMPTY、publication CLOSED、wrong-level 与无连接消费断言**

新增 `TEST(publish_notice_empty_closed_wrong_level_and_no_open_connections)`，分别使用真实 `break_world_snapshot_publication_acquire()` 验证 initial EMPTY、close 后 CLOSED。测试体内用独立作用域调用 `fixture_init_publication()`：先用 level=0 打开 KEY_A、publish level0/S1、submit/drain level0 notice并断言一个 full，证明 level 0 合法；EMPTY 与 wrong-level 场景先打开 KEY_A；无连接场景在 notice drain 前不打开任何连接；CLOSED 场景使用全新 publication。具体状态断言：

```c
/* 独立 level0 fixture：0 不是 wrong-level。 */
ASSERT_TRUE(fixture_init_publication(&fixture, 0u, 2u, 0u));
ASSERT_TRUE(open_connection(&fixture, KEY_A, 0u, &epoch_a));
s1 = make_target(&fixture, 42u, 10u);
ASSERT_TRUE(break_world_snapshot_publication_publish(fixture.publication, s1, 0u));
ASSERT_EQ(submit_current(&fixture, 0u, 0u), BREAK_RUNTIME_OK);
ASSERT_EQ(break_runtime_world_session_drain(fixture.adapter, 1u, &drained),
          BREAK_RUNTIME_OK);
break_world_session_stats(fixture.session, &world_after);
ASSERT_EQ(world_after.published_full_packets, 1u);
break_world_snapshot_release(s1);
fixture_dispose(&fixture);

/* 新的 EMPTY fixture：notice 被消费，不留下 continuation。 */
ASSERT_TRUE(fixture_init_publication(&fixture, 7u, 2u, 0u));
ASSERT_TRUE(open_connection(&fixture, KEY_A, 7u, &epoch_a));
ASSERT_EQ(submit_current(&fixture, 7u, 0u), BREAK_RUNTIME_OK);
ASSERT_EQ(break_runtime_world_session_drain(fixture.adapter, 1u, &drained),
          BREAK_RUNTIME_OK);
ASSERT_EQ(drained, 1u);
ASSERT_EQ(break_runtime_world_session_pending(fixture.adapter), 0u);
ASSERT_TRUE(break_world_session_sender_state(fixture.session, KEY_A, &sender));
ASSERT_EQ(sender.next_delta_id, 1u);
fixture_dispose(&fixture);

/* 新的 wrong-level fixture：8 对当前 Session 7 是 STALE。 */
ASSERT_TRUE(fixture_init_publication(&fixture, 7u, 2u, 0u));
ASSERT_TRUE(open_connection(&fixture, KEY_A, 7u, &epoch_a));
ASSERT_EQ(submit_current(&fixture, 8u, 0u), BREAK_RUNTIME_OK);
ASSERT_EQ(break_runtime_world_session_drain(fixture.adapter, 1u, &drained),
          BREAK_RUNTIME_STALE);
ASSERT_EQ(drained, 1u);
ASSERT_EQ(break_runtime_world_session_pending(fixture.adapter), 0u);
ASSERT_EQ(break_net_reactor_outbound_count(fixture.reactor), 0u);
fixture_dispose(&fixture);

/* 新的无连接 fixture：request 清空，未来 OPEN 不隐式发布。 */
ASSERT_TRUE(fixture_init_publication(&fixture, 7u, 2u, 0u));
s1 = make_target(&fixture, 42u, 10u);
ASSERT_TRUE(break_world_snapshot_publication_publish(fixture.publication, s1, 7u));
ASSERT_EQ(submit_current(&fixture, 7u, 0u), BREAK_RUNTIME_OK);
ASSERT_EQ(break_runtime_world_session_drain(fixture.adapter, 1u, &drained),
          BREAK_RUNTIME_OK);
ASSERT_EQ(break_runtime_world_session_pending(fixture.adapter), 0u);
ASSERT_TRUE(open_connection(&fixture, KEY_B, 7u, &epoch_b));
ASSERT_TRUE(break_world_session_sender_state(fixture.session, KEY_B, &sender));
ASSERT_EQ(sender.next_delta_id, 1u);
break_world_snapshot_release(s1);
fixture_dispose(&fixture);

/* 新的 CLOSED fixture：返回 CLOSED 且 publish_terminal=1，不形成 pending。 */
ASSERT_TRUE(fixture_init_publication(&fixture, 7u, 2u, 0u));
ASSERT_TRUE(open_connection(&fixture, KEY_A, 7u, &epoch_a));
break_world_snapshot_publication_close(fixture.publication);
ASSERT_EQ(submit_current(&fixture, 7u, 0u), BREAK_RUNTIME_OK);
ASSERT_EQ(break_runtime_world_session_drain(fixture.adapter, 1u, &drained),
          BREAK_RUNTIME_CLOSED);
break_runtime_world_session_stats(fixture.adapter, &stats);
ASSERT_EQ(stats.publish_terminal, 1u);
ASSERT_FALSE(stats.publish_pending);
fixture_dispose(&fixture);
```

每个作用域结束前由 `fixture_dispose()` 按 adapter→publication→Bus/Session/World 顺序清理；无连接部分不得复用已打开 KEY_A 的 fixture，每个子场景都检查 sender state 未被错误修改。

- [ ] **Step 5: 扩展 target contract 并确认 RED**

在 `test_runtime_world_session_target_contract.cmake` 保留现有 runtime_core/target/link 检查，增加精确检查：仍有 `queue_config.reserved_control = queue_config.capacity;`；仍有 `const u16 kinds[1] = {BREAK_RUNTIME_WORLD_SESSION_CONTROL_KIND};`；adapter source 含 `view.kind = BREAK_RUNTIME_WORLD_SESSION_PUBLISH_CURRENT_KIND`、`view.flags = BREAK_RUNTIME_MESSAGE_FLAG_CONTROL`、`break_world_snapshot_lease_release(&lease);`；不得含 `kinds[2]` 或 `"world_session.publish"`。从 direct submit 函数体提取区块，若匹配任何 `break_world_session_` 调用则 FATAL（包含变异测试插入的 `break_world_session_level_generation`），防止 submit 直接调用 Session；`runtime_world_publish_connection` 区块不得含 `break_world_snapshot_publication_acquire`，确保 acquire 不进入逐连接 helper。

```sh
cmake --build engine/build-runtime-world-data-plane \
  --target test_runtime_world_session -j2
```

Expected: 首先因新 notice 类型、Config/Stats 字段和 direct submit 符号缺失而编译 RED；实现后若删 control flag、注册外部 kind、在 submit 调 Session 或逐连接 acquire，contract 必须 RED。

- [ ] **Step 6: 实现公共 ABI、create 校验与 direct submit**

在公共头包含 `ecs/world_snapshot_publication.h`，逐字追加 Produces 中的 API。create 使用：

```c
if (!config->publication && config->publish_connection_budget != 0u) return NULL;
if (config->publish_connection_budget > 64u) return NULL;
adapter->publication = config->publication;
adapter->publish_connection_budget = config->publish_connection_budget == 0u
    ? 8u : config->publish_connection_budget;
```

direct submit 持 adapter mutex，顺序为 closed→publication configured→`notice && reserved_zero==0`→共享 `next_sequence`→`break_runtime_message_copy()`→既有 queue generation/enqueue；只有 enqueue OK 才 `submitted++`、`next_sequence++`。metadata 必须为：

```c
view.kind = BREAK_RUNTIME_WORLD_SESSION_PUBLISH_CURRENT_KIND;
view.version = BREAK_RUNTIME_WORLD_SESSION_PUBLISH_CURRENT_VERSION;
view.flags = BREAK_RUNTIME_MESSAGE_FLAG_CONTROL;
view.sequence = sequence;
view.correlation_id = correlation_id;
view.data = notice;
view.size = sizeof(*notice);
```

不得 Bus publish、不得 acquire、不得调用 World Session。INVALID/REJECTED 计 rejected，queue OVERLOAD 不改 sender/submitted/sequence，也不计 `publish_overloads`。

- [ ] **Step 7: 实现 drain 基础路径、latest-current lease 边界与简单 continuation**

queue poll 先识别 `0x5754/version1/size16`，再走既有 `0x5753`；两种消息都 `drained++`。合法 notice 只在 `notice.level_generation == break_world_session_level_generation(session)` 时设置 `publish_request=true` 和 request level。wrong-level notice 通过结果记账记录 STALE，但不覆盖、不清除此前合法 request/continuation，也不得立即从整个 drain 返回：queue 仍按 FIFO/`max_messages` 消费，批次末尾仍执行此前合法 request/continuation 对应的 `runtime_world_publish_current()`；将 STALE 保存为 `first_error`（若此前没有其他错误），最终返回首个非 OK。没有既有合法 request/continuation 时，wrong-level 自身不建立 fanout。REBASELINE 成功时清所有连接 fanout 状态与旧 request/continuation；CLOSE 成功时清该槽 fanout 状态；OPEN 从零状态开始。

`max_messages==0` 直接返回，不 acquire/续发。既有 `control_pending` 重试仍 OVERLOAD 时不处理 notice/continuation。批次末尾有 request/continuation 才调用一次 `runtime_world_publish_current()`：

```c
BreakWorldSnapshotLease lease;
BreakWorldSnapshotAcquireResult acquired;
memset(&lease, 0, sizeof(lease));
acquired = break_world_snapshot_publication_acquire(adapter->publication, &lease);
if (acquired == BREAK_WORLD_SNAPSHOT_ACQUIRE_EMPTY) {
    runtime_world_clear_publish(adapter, true);
    return BREAK_RUNTIME_OK;
}
if (acquired == BREAK_WORLD_SNAPSHOT_ACQUIRE_CLOSED) {
    adapter->publish_terminal++;
    runtime_world_clear_publish(adapter, true);
    return BREAK_RUNTIME_CLOSED;
}
if (acquired != BREAK_WORLD_SNAPSHOT_ACQUIRE_OK) {
    adapter->publish_terminal++;
    runtime_world_clear_publish(adapter, true);
    return BREAK_RUNTIME_INVALID;
}
/* 唯一出口释放；level mismatch 也走这里。 */
result = BREAK_RUNTIME_OK;
if (lease.level_generation != break_world_session_level_generation(adapter->session)) {
    adapter->publish_terminal++;
    runtime_world_clear_publish(adapter, true);
    result = BREAK_RUNTIME_STALE;
    goto release;
}
adapter->publish_request = false;
adapter->publish_observed_epoch = lease.publication_epoch;
/* 从 publish_cursor 最多扫描 max_connections，本任务的新 attempt 路径调用
 * break_world_session_publish_snapshot(session,key,lease.snapshot,lease.level)。 */
adapter->publish_continuation = runtime_world_recompute_continuation(
    adapter, lease.publication_epoch);
release:
break_world_snapshot_lease_release(&lease);
return result;
```

本任务的 `runtime_world_publish_connection()` 只承诺：`sender_state` 无 active、无旧 retry 时，completed/terminal 同 epoch clean skip；否则每连接调用一次 publish，OK 记 current completed，OVERLOAD 保存 retry 并继续其他连接，INVALID/CLOSED/其他错误记 current terminal 并继续。调用预算用 `min(publish_connection_budget,max_connections)`，clean skip 不耗预算，扫描耗尽时保存 cursor/continuation。完整 active target 判账与跨 drain 恢复由 Task 3 验收，本任务不得宣称那部分完成。

`stats()` 尾部填 `publish_overloads`、`publish_terminal` 和 `runtime_world_publish_pending_locked()`；`pending()` 加该布尔值。lifecycle 头注释把 pending 公式改为 queue+control+publish，现有 lifecycle.c 的 DRAIN→TIMEOUT 映射保持不变。

- [ ] **Step 8: 运行基础 GREEN 与兼容回归**

```sh
cmake --build engine/build-runtime-world-data-plane \
  --target test_runtime_world_session test_world_session_recovery \
  test_world_session test_world_snapshot_publication -j2
ctest --test-dir engine/build-runtime-world-data-plane --output-on-failure \
  -R '^(test_runtime_world_session|test_runtime_world_session_target_contract|test_world_session_recovery|test_world_session|test_world_snapshot_publication|test_replication_target_contract)$'
```

Expected: 全部 PASS；既有 56 字节控制、五类命令、默认 NULL、level 0、ACK/NEED_FULL、外部 `0x5753` Bus 与 Coordinator 测试保持原语义。新测试只覆盖无 active attempt 基础路径。

- [ ] **Step 9: 基础边界变异与 ASan+UBSan**

备份 `runtime_world_session.c`，依次执行并恢复四个变异：把 notice flags 改为 0，预期 capacity=1 的首个 submit 变成 OVERLOAD；在 direct submit 插入 `(void)break_world_session_level_generation(adapter->session);`，预期 target contract RED；注册/订阅 `0x5754`，预期外部 Bus REJECTED/delivered=0 测试与 contract RED；删除统一 lease release，预期 ASan leak 检查 RED。然后运行：

```sh
cmake --build engine/build-runtime-world-data-plane-asan \
  --target test_runtime_world_session test_world_session_recovery -j2
ASAN_OPTIONS=detect_leaks=1 UBSAN_OPTIONS=halt_on_error=1 \
  ctest --test-dir engine/build-runtime-world-data-plane-asan \
  --output-on-failure -R '^(test_runtime_world_session|test_runtime_world_session_target_contract|test_world_session_recovery)$'
```

Expected: 每个变异可构建且判红，恢复后 normal/ASan+UBSan GREEN，无 leak/UB 诊断。

- [ ] **Step 10: 实现者先提交中间门，controller 随后评审该提交**

实现者完成基础路径验证后先执行：

```sh
git diff --check
git add engine/src/runtime/runtime_world_session.h \
  engine/src/runtime/runtime_world_session.c \
  engine/src/runtime/runtime_world_session_lifecycle.h \
  engine/tests/test_runtime_world_session.c \
  engine/tests/test_runtime_world_session_target_contract.cmake
git commit -m "feat(runtime): add snapshot publish notice"
```

controller 以该提交 SHA 和测试证据组成 review package，随后独立评审中间门，不得以未提交 HEAD 作为评审对象。

Expected: controller 的评审记录明确“基础 notice 与无 active fanout 已完成；E1/E2、预算恢复和完整 shutdown 尚未验收”，不把本提交描述为完整数据面；评审通过后才进入 Task 3。

---

### Task 3: 完成有限预算、实际 attempt 判账、生命周期恢复与真线程竞态

**Files:**
- Modify: `engine/src/runtime/runtime_world_session.c`
- Modify: `engine/src/runtime/runtime_world_session.h`
- Modify: `engine/src/runtime/runtime_world_session_lifecycle.h`
- Test: `engine/tests/test_runtime_world_session.c`
- Test: `engine/tests/test_runtime_world_session_target_contract.cmake`

**Interfaces:**
- Consumes: Task 1 的实际 active id/tick；Task 2 的 public notice/config/stats/submit、`RuntimeWorldConnection` 的 completed/terminal/attempt epoch、attempt target id/tick、retry 六类判账字段、adapter request/continuation/cursor 字段和七个私有 helper 签名；既有 `LifecycleProbe`、`lifecycle_trace()`、`lifecycle_stop_producers()`、`lifecycle_join()`、`lifecycle_on_destroy()`、`break_runtime_coordinator_start/stop()`；现有 `ConcurrentShared`、PlatformThread、`platform_thread_yield()` 与 C11 atomics。
- Produces: 完成 `runtime_world_publish_connection()`、`runtime_world_recompute_continuation()`、`runtime_world_publish_current()` 的下列行为，不新增公共函数或字段：

```c
/* 对 current lease，clean skip 的充分条件： */
!before.attempt_pending && !connection->retry_publish &&
connection->attempt_publication_epoch == 0u &&
connection->attempt_target_snapshot_id == 0u &&
connection->attempt_target_tick == 0u &&
(connection->completed_publication_epoch == lease->publication_epoch ||
 connection->terminal_publication_epoch == lease->publication_epoch)

/* pending 的精确定义： */
queued + (control_pending ? 1u : 0u) +
((publish_request || publish_continuation) ? 1u : 0u)
```

`publish_overloads` 只统计 Session 返回 `BREAK_NET_SEND_OVERLOAD`；`publish_terminal` 每次 acquire CLOSED/INVALID/level mismatch 计一次，每次连接 INVALID/CLOSED/未预期错误计一次，EMPTY 与 wrong-level notice 不计。continuation 在 queue 已空且 `max_messages>0` 时仍执行，不跨 drain 持 lease。

- [ ] **Step 1: 写 budget=1、跨 drain cursor 与默认 budget=8 的 RED 测试**

新增 `TEST(publish_budget_one_round_robin_continues_without_queue_message)`。用 Task 2 的 publication fixture、`open_connection()`、`make_target()`、`submit_current()`，budget=1，A/B 两连接：

```c
ASSERT_EQ(submit_current(&fixture, 7u, 0u), BREAK_RUNTIME_OK);
ASSERT_EQ(break_runtime_world_session_drain(fixture.adapter, 1u, &drained),
          BREAK_RUNTIME_OK);
ASSERT_EQ(drained, 1u);
ASSERT_TRUE(break_world_session_sender_state(fixture.session, KEY_A, &a_state));
ASSERT_TRUE(break_world_session_sender_state(fixture.session, KEY_B, &b_state));
ASSERT_EQ(a_state.history_count, 1u);
ASSERT_EQ(b_state.history_count, 0u);
ASSERT_EQ(break_runtime_world_session_pending(fixture.adapter), 1u);
break_runtime_world_session_stats(fixture.adapter, &stats);
ASSERT_TRUE(stats.publish_pending);
ASSERT_FALSE(stats.control_pending);

/* max_messages=0 不 acquire、不续发，B 与 pending 都必须保持。 */
ASSERT_EQ(break_runtime_world_session_drain(fixture.adapter, 0u, &drained),
          BREAK_RUNTIME_OK);
ASSERT_EQ(drained, 0u);
ASSERT_TRUE(break_world_session_sender_state(fixture.session, KEY_B, &b_state));
ASSERT_EQ(b_state.history_count, 0u);
ASSERT_EQ(break_runtime_world_session_pending(fixture.adapter), 1u);

/* queue 已空仍从 cursor=B 续发；A 同 epoch clean skip。 */
ASSERT_EQ(break_runtime_world_session_drain(fixture.adapter, 1u, &drained),
          BREAK_RUNTIME_OK);
ASSERT_EQ(drained, 0u);
ASSERT_EQ(break_runtime_world_session_pending(fixture.adapter), 0u);
ASSERT_TRUE(break_world_session_sender_state(fixture.session, KEY_A, &a_state));
ASSERT_TRUE(break_world_session_sender_state(fixture.session, KEY_B, &b_state));
ASSERT_EQ(a_state.history_count, 1u);
ASSERT_EQ(a_state.next_delta_id, 2u);
ASSERT_EQ(b_state.history_count, 1u);
```

为默认 8 做行为证明，把现有 fixture 初始化提取为 `fixture_init_without_adapter_scaled(fixture,level,max_connections)`，仅将 `config.bridge.max_connections` 改为参数，原 helper 固定转调 2。新增九连接测试：`KEY_A+i` 依次 `open_connection()`，publication 配置 budget=0，first drain 后恰 8 个连接 `history_count==1`、第 9 个为 0、pending=1；第二次空 queue drain 后第 9 个完成、其余 `next_delta_id` 不增加、pending=0。

```sh
cmake --build engine/build-runtime-world-data-plane \
  --target test_runtime_world_session -j2 && \
engine/build-runtime-world-data-plane/test_runtime_world_session
```

Expected: Task 2 的简单 continuation 若未保存 cursor/重算 pending，会在 B 未发送、pending 错误或默认第 8/9 连接边界处 RED；不得降低断言为只检查最终两个包。

- [ ] **Step 2: 写 A OVERLOAD 不阻塞 B 与 E1→E2 实际 attempt 判账 RED 测试**

给 runtime `Fixture` 增加 `bool fair_outbound_admission`，`reactor_start()` 的最后一个 `BreakNetReactorConfig` 字段使用该值；初始化时像 loopback fixture 一样在 `memset` 前后保存它，默认仍为 false。新增 `TEST(publish_overload_resumes_e1_before_latest_e2_and_does_not_block_b)`：

1. 设置 fair=true，A/B open，S1/tick10 发布为 epoch1。
2. A 先发送 `BREAK_NET_OUTBOUND_QUEUE_CAPACITY/2` 个 PING 填滿自己的 fair share；notice drain 必须返回 `BREAK_RUNTIME_OVERLOAD`，A `attempt_pending==true` 且 active id/tick=S1/10，B `history_count==1`。`publish_overloads==1`、`transport_overloads==0`、pending=1。
3. 用 `clear_outbound()` 释放 PING 与 B 的 BRWD；构建 S2/tick20 并 `break_world_snapshot_publication_publish()` 替换为 epoch2，不提交新 notice。
4. 下一次空 queue drain 用同一 continuation acquire E2。A 的 `publish_snapshot(E2)` 实际续发 E1；B 可推进 E2。此处以 A `history_count==1`、`next_delta_id==2` 且 pending 仍为 1 证明没有把续发 OK 误判为 E2 新建/完成；Task 4 的真实 socket 字节断言再独立证明 resumed target 确为 S1。
5. 后续 drain 在 A 无 active 后才创建 E2，断言 A `next_delta_id==3`、pending 最终为 0；重复 drain 不再改变 sender state。

关键断言序列：

```c
ASSERT_EQ(break_runtime_world_session_drain(fixture.adapter, 1u, &drained),
          BREAK_RUNTIME_OVERLOAD);
ASSERT_TRUE(a_state.attempt_pending);
ASSERT_EQ(a_state.attempt_target_snapshot_id, break_world_snapshot_id(s1));
ASSERT_EQ(a_state.attempt_target_tick, 10u);
ASSERT_EQ(b_state.history_count, 1u);
ASSERT_EQ(stats.publish_overloads, 1u);
ASSERT_EQ(stats.transport_overloads, 0u);
/* replace E2、drain 后：任何 OK 都把 E2 标 completed 的变异会在这里失败。 */
ASSERT_EQ(a_state.next_delta_id, 2u);
ASSERT_TRUE(stats.publish_pending);
/* 再 drain：真正创建 E2 后才允许 next_delta_id=3、pending=0。 */
```

另新增 unknown-old-attempt 场景：adapter 外用直接 Session API 为 A 建立旧 S0 OVERLOAD，再让 adapter acquire S1；第一次 OK 只完成未知旧 S0，不得标 S1 completed，必须再 drain 才创建 S1。断言第一次后 `next_delta_id==2` 且 pending=1，第二次后 `next_delta_id==3`。

- [ ] **Step 3: 写终态、per-connection dedup 与 NEED_FULL 不强制同 epoch 重发的 RED 测试**

新增 `TEST(publish_terminal_dedup_new_epoch_and_need_full_rules)`，覆盖以下精确序列：

- 先直接用既有 `publish_target()` 给 A 发送 tick100 的 history target，再让 publication epoch1 只有 tick10；adapter notice 调 Session 时 strict-tick 返回 INVALID。断言第一次 drain 返回 `BREAK_RUNTIME_INVALID`、`publish_terminal==1`、A retry/attempt 可通过后续行为证明已清、pending=0。随后再次 `submit_current(&fixture,7u,0u)`，同 epoch 的 clean-skip drain 必须返回 `BREAK_RUNTIME_OK`，`drained==1`，`publish_terminal` 仍严格等于 1，outbound/`next_delta_id` 均不增加；只有 `break_world_snapshot_publication_publish()` 成功推进到 publication epoch2/tick110 后，新 notice 才允许再次尝试并成功。
-  reactor stop 后新 notice 的单连接 CLOSED 映射为 `BREAK_RUNTIME_CLOSED`，`publish_terminal` 增 1，pending=0，`break_runtime_world_session_destroy()` 可成功；不得留下永久 TIMEOUT。
- 正常 S1 已完成时，通过既有 `control_via_adapter(...NEED_FULL...)` 设置 force_full；重复 S1 epoch notice 必须 clean skip，World stats 不变。发布 S2 epoch2 后必须新增一个 full 而非 delta，证明 NEED_FULL 没有清 completed epoch，也没有允许同 epoch 强制重发。

每个场景检查 `publish_overloads` 不吸收 INVALID/CLOSED，`transport_overloads` 不吸收数据面 OVERLOAD。

- [ ] **Step 4: 写 close/reopen、rebaseline、lease level mismatch 与 wrong-level 不取消 continuation 的 RED 测试**

新增 `TEST(publish_lifecycle_resets_scalar_state_and_cancels_old_level)`，声明 `Fixture fixture`、`BreakRuntimeWorldCommand close_a/rebase`、`BreakWorldSessionSenderState a_state/b_state`、`BreakWorldSessionStats before/after`、`BreakRuntimeWorldSessionStats stats`、`BreakWorldSnapshotLease lease`、`BreakWorldSnapshot *s1` 与 `BreakWorldSnapshot *s2`、`u64 epoch_a/epoch_b/old_epoch` 和 `usize drained`。以下四个独立 fixture 作用域都使用现有 helper，不引入伪调用。

close/reopen 使用 `control_via_adapter()` ACK 初始 S1，再用既有 56 字节 CLOSE command 关闭；reopen 后同 publication epoch 仍必须作为新 connection_epoch 从零发送 full：

```c
ASSERT_TRUE(fixture_init_publication(&fixture, 7u, 2u, 0u));
ASSERT_TRUE(open_connection(&fixture, KEY_A, 7u, &epoch_a));
s1 = make_target(&fixture, 42u, 10u);
ASSERT_NOT_NULL(s1);
ASSERT_TRUE(break_world_snapshot_publication_publish(fixture.publication, s1, 7u));
ASSERT_EQ(submit_current(&fixture, 7u, 0u), BREAK_RUNTIME_OK);
ASSERT_EQ(break_runtime_world_session_drain(fixture.adapter, 1u, &drained),
          BREAK_RUNTIME_OK);
ASSERT_TRUE(control_via_adapter(&fixture, BREAK_RUNTIME_WORLD_COMMAND_ACK,
                                KEY_A, epoch_a, 7u, 1u, s1, HIGH_CID));
break_world_session_stats(fixture.session, &before);

close_a = command(BREAK_RUNTIME_WORLD_COMMAND_CLOSE, KEY_A, epoch_a, 7u);
ASSERT_EQ(break_runtime_world_session_submit(fixture.adapter, &close_a, 0u),
          BREAK_RUNTIME_OK);
ASSERT_EQ(break_runtime_world_session_drain(fixture.adapter, 1u, &drained),
          BREAK_RUNTIME_OK);
ASSERT_EQ(drained, 1u);
old_epoch = epoch_a;
ASSERT_TRUE(open_connection(&fixture, KEY_A, 7u, &epoch_a));
ASSERT_TRUE(epoch_a > old_epoch);
ASSERT_EQ(submit_current(&fixture, 7u, 0u), BREAK_RUNTIME_OK);
ASSERT_EQ(break_runtime_world_session_drain(fixture.adapter, 1u, &drained),
          BREAK_RUNTIME_OK);
ASSERT_TRUE(break_world_session_sender_state(fixture.session, KEY_A, &a_state));
ASSERT_EQ(a_state.next_delta_id, 2u); /* 刚发送 delta_id=1 的 full。 */
ASSERT_EQ(a_state.history_count, 1u);
ASSERT_EQ(a_state.confirmed_snapshot_id, 0u);
ASSERT_FALSE(a_state.attempt_pending);
ASSERT_EQ(a_state.attempt_target_snapshot_id, 0u);
ASSERT_EQ(a_state.attempt_target_tick, 0u);
break_world_session_stats(fixture.session, &after);
ASSERT_EQ(after.published_full_packets, before.published_full_packets + 1u);
ASSERT_EQ(after.published_delta_packets, before.published_delta_packets);
break_world_snapshot_release(s1);
fixture_dispose(&fixture);
```

rebaseline 场景先用 budget=1 留下 level7/B continuation，再在提交 REBASELINE8 **之前**发布 level8 current。这样批次末尾 acquire 到的是匹配的 level8 lease，而不是 level mismatch：

```c
ASSERT_TRUE(fixture_init_publication(&fixture, 7u, 2u, 1u));
ASSERT_TRUE(open_connection(&fixture, KEY_A, 7u, &epoch_a));
ASSERT_TRUE(open_connection(&fixture, KEY_B, 7u, &epoch_b));
s1 = make_target(&fixture, 42u, 10u);
ASSERT_TRUE(break_world_snapshot_publication_publish(fixture.publication, s1, 7u));
ASSERT_EQ(submit_current(&fixture, 7u, 0u), BREAK_RUNTIME_OK);
ASSERT_EQ(break_runtime_world_session_drain(fixture.adapter, 1u, &drained),
          BREAK_RUNTIME_OK);
ASSERT_EQ(break_runtime_world_session_pending(fixture.adapter), 1u);

s2 = make_target(&fixture, 84u, 20u);
ASSERT_NOT_NULL(s2);
ASSERT_TRUE(break_world_snapshot_publication_publish(fixture.publication, s2, 8u));
rebase = command(BREAK_RUNTIME_WORLD_COMMAND_REBASELINE, 0u, 0u, 8u);
ASSERT_EQ(break_runtime_world_session_submit(fixture.adapter, &rebase, 0u),
          BREAK_RUNTIME_OK);
ASSERT_EQ(submit_current(&fixture, 7u, 0u), BREAK_RUNTIME_OK); /* 旧 level，STALE。 */
ASSERT_EQ(submit_current(&fixture, 8u, 0u), BREAK_RUNTIME_OK); /* 新合法 request。 */
break_world_session_stats(fixture.session, &before);
ASSERT_EQ(break_runtime_world_session_drain(fixture.adapter, 3u, &drained),
          BREAK_RUNTIME_STALE); /* 首个非 OK 来自旧 notice，fanout 仍执行。 */
ASSERT_EQ(drained, 3u);
ASSERT_EQ(break_world_session_level_generation(fixture.session), 8u);
ASSERT_TRUE(break_world_session_sender_state(fixture.session, KEY_A, &a_state));
ASSERT_TRUE(break_world_session_sender_state(fixture.session, KEY_B, &b_state));
ASSERT_EQ(a_state.next_delta_id, 2u); /* rebaseline 后 level8 delta_id=1。 */
ASSERT_EQ(a_state.history_count, 1u);
ASSERT_EQ(b_state.next_delta_id, 1u); /* budget=1，B 等下一 drain。 */
ASSERT_EQ(b_state.history_count, 0u);
break_world_session_stats(fixture.session, &after);
ASSERT_EQ(after.published_full_packets, before.published_full_packets + 1u);
break_runtime_world_session_stats(fixture.adapter, &stats);
ASSERT_EQ(stats.publish_terminal, 0u);
ASSERT_TRUE(stats.publish_pending);
ASSERT_EQ(break_runtime_world_session_pending(fixture.adapter), 1u);
memset(&lease, 0, sizeof(lease));
ASSERT_EQ(break_world_snapshot_publication_acquire(fixture.publication, &lease),
          BREAK_WORLD_SNAPSHOT_ACQUIRE_OK);
ASSERT_TRUE(lease.snapshot == s2);
ASSERT_EQ(lease.level_generation, 8u);
ASSERT_EQ(lease.publication_epoch, 2u);
break_world_snapshot_lease_release(&lease);
break_world_snapshot_release(s2);
break_world_snapshot_release(s1);
fixture_dispose(&fixture);
```

lease mismatch 必须使用另一个 publication 仍为 level7、Session 已 rebaseline 到 8 的 fixture，不能试图在刚发布 level8 的 publication 上倒退发布 level7：

```c
ASSERT_TRUE(fixture_init_publication(&fixture, 7u, 2u, 0u));
ASSERT_TRUE(open_connection(&fixture, KEY_A, 7u, &epoch_a));
s1 = make_target(&fixture, 42u, 10u);
ASSERT_TRUE(break_world_snapshot_publication_publish(fixture.publication, s1, 7u));
rebase = command(BREAK_RUNTIME_WORLD_COMMAND_REBASELINE, 0u, 0u, 8u);
ASSERT_EQ(break_runtime_world_session_submit(fixture.adapter, &rebase, 0u),
          BREAK_RUNTIME_OK);
ASSERT_EQ(break_runtime_world_session_drain(fixture.adapter, 1u, &drained),
          BREAK_RUNTIME_OK);
ASSERT_EQ(break_world_session_level_generation(fixture.session), 8u);
ASSERT_EQ(submit_current(&fixture, 8u, 0u), BREAK_RUNTIME_OK);
ASSERT_EQ(break_runtime_world_session_drain(fixture.adapter, 1u, &drained),
          BREAK_RUNTIME_STALE);
ASSERT_EQ(drained, 1u);
ASSERT_EQ(break_runtime_world_session_pending(fixture.adapter), 0u);
ASSERT_EQ(break_net_reactor_outbound_count(fixture.reactor), 0u);
break_runtime_world_session_stats(fixture.adapter, &stats);
ASSERT_EQ(stats.publish_terminal, 1u);
ASSERT_FALSE(stats.publish_pending);
break_world_snapshot_release(s1);
fixture_dispose(&fixture);
```

最后独立建立 level7/B continuation，只提交 wrong-level notice8。该 notice 记录 STALE 但不提前返回、不清 continuation；同一批次末尾仍执行 level7/B fanout，最终返回首个非 OK，即 STALE：

```c
ASSERT_TRUE(fixture_init_publication(&fixture, 7u, 2u, 1u));
ASSERT_TRUE(open_connection(&fixture, KEY_A, 7u, &epoch_a));
ASSERT_TRUE(open_connection(&fixture, KEY_B, 7u, &epoch_b));
s1 = make_target(&fixture, 42u, 10u);
ASSERT_TRUE(break_world_snapshot_publication_publish(fixture.publication, s1, 7u));
ASSERT_EQ(submit_current(&fixture, 7u, 0u), BREAK_RUNTIME_OK);
ASSERT_EQ(break_runtime_world_session_drain(fixture.adapter, 1u, &drained),
          BREAK_RUNTIME_OK);
ASSERT_EQ(break_runtime_world_session_pending(fixture.adapter), 1u);
ASSERT_EQ(submit_current(&fixture, 8u, 0u), BREAK_RUNTIME_OK);
ASSERT_EQ(break_runtime_world_session_drain(fixture.adapter, 1u, &drained),
          BREAK_RUNTIME_STALE);
ASSERT_EQ(drained, 1u);
ASSERT_TRUE(break_world_session_sender_state(fixture.session, KEY_A, &a_state));
ASSERT_TRUE(break_world_session_sender_state(fixture.session, KEY_B, &b_state));
ASSERT_EQ(a_state.next_delta_id, 2u); /* A 不重复发。 */
ASSERT_EQ(b_state.next_delta_id, 2u); /* 既有 continuation 在本批次末尾完成 B。 */
ASSERT_EQ(b_state.history_count, 1u);
ASSERT_EQ(break_runtime_world_session_pending(fixture.adapter), 0u);
break_runtime_world_session_stats(fixture.adapter, &stats);
ASSERT_EQ(stats.stale_rejected, 1u);
ASSERT_FALSE(stats.publish_pending);
break_world_snapshot_release(s1);
fixture_dispose(&fixture);
```

- [ ] **Step 5: 写 pending/destroy、publication CLOSED 与 Coordinator DRAIN 恢复 RED 测试**

新增 `TEST(publish_pending_gates_destroy_and_coordinator_resumes_fanout_cursor)`：

- budget=1、A/B、notice first drain 后 queue=0 但 `publish_pending=true`、`pending()==1`、`destroy()==false`；destroy 尝试已 close admission，后续 direct submit 返回 CLOSED。第二次空 queue drain 完成 B，pending=0、destroy=true；随后本地 `break_world_snapshot_publication_acquire()` 仍返回 OK，证明 publication/Session 是 borrowed。
- budget=1 first drain 后 close publication，下一 drain 返回 CLOSED，清 request/retry/continuation，pending=0，不永久 TIMEOUT；已存在 Session attempt 不被 adapter 假装 completed。
- Coordinator 使用现有 `LifecycleProbe` 和六阶段 hooks，`lifecycle.drain_budget=1`，adapter publication budget=1。第一次 `break_runtime_coordinator_stop()` 返回 TIMEOUT、state=`BREAK_RUNTIME_DRAINING`、phase 序列只到第一个 `"drain"`，A 已发/B 未发、`stop_producers_calls==1`。第二次 stop 必须从同一 drain/cursor 完成 B，再 join/destroy 返回 OK，总 phase 为 `stop_admission,stop_producers,close_queues,drain,drain,join,destroy`，A 不得重复发包；`on_destroy_calls==1` 后将 `fixture.adapter=NULL`。

Coordinator GREEN 前若 continuation 未计 pending，第一次 stop 会错误进入 join/destroy；该行为必须保持 RED 证据。

- [ ] **Step 6: 写生产线程与 owner drain 的真线程 barrier 竞态 RED 测试**

新增 `RuntimeNoticeRace`，字段只含 `Fixture *fixture`、`_Atomic u32 ready`、`_Atomic bool go`、`_Atomic bool done`、`_Atomic bool failed`、`u32 accepted`。线程函数在 `ready=1(memory_order_release)` 后用有界 yield 循环等待 `go(memory_order_acquire)`；主线程用有界循环等 ready 后再释放 go，不使用固定 sleep。生产线程每轮只做：

```c
BreakWorldSnapshot *snapshot = make_target(race->fixture, 100u + i, (u64)i + 1u);
if (!snapshot ||
    !break_world_snapshot_publication_publish(race->fixture->publication,
                                               snapshot, 7u)) {
    atomic_store_explicit(&race->failed, true, memory_order_release);
    break;
}
for (u32 spin = 0u; spin < 1000000u; ++spin) {
    BreakRuntimeError result = submit_current(race->fixture, 7u,
                                               UINT64_C(0xD5754) + i);
    if (result == BREAK_RUNTIME_OK) { race->accepted++; break; }
    if (result != BREAK_RUNTIME_OVERLOAD || spin == 999999u) {
        atomic_store_explicit(&race->failed, true, memory_order_release);
        break;
    }
    platform_thread_yield();
}
break_world_snapshot_release(snapshot);
```

主线程创建 PlatformThread 后，在同一 go barrier 下执行 owner-only `break_runtime_world_session_drain(...,4u)`，每次 drain 后 `clear_outbound()` 防止 transport backpressure，最多 1,000,000 次 yield 循环；join 后最多 1,024 次 drain 到 pending=0。生产线程不得调用任何 `break_world_session_*`。最后断言 `!failed`、`accepted==32`、最后 acquire 的 current 与 A 最新 history target 一致、`stats.submitted==33`（含 OPEN）、`stats.drained==33`、`publish_pending==false`；中间 publication epoch 允许 coalesce，不得断言 32 个网络包。

该测试与既有 `concurrent_ingress_close_drain_and_destroy_preserve_exactly_once` 都纳入 TSan，不允许用 sleep 制造“通过”。

- [ ] **Step 7: 运行 Task 3 行为 RED 并记录首个失败分支**

```sh
cmake --build engine/build-runtime-world-data-plane \
  --target test_runtime_world_session -j2 && \
engine/build-runtime-world-data-plane/test_runtime_world_session
```

Expected: 新测试在至少一个明确合同处失败：active E1 被误记为 E2、A OVERLOAD 阻断 B、预算 cursor 不恢复、continuation 未计 pending、close/reopen/rebaseline 状态未清、终态留下 pending，或 Coordinator 提前 destroy。保留实际失败输出作为 RED 证据，不修改测试预期迁就 Task 2 中间实现。

- [ ] **Step 8: 实现统一 lease/acquire 状态转移与 fair budget 扫描**

`runtime_world_publish_current()` 只在 request/continuation 存在时进入，一次 acquire、一个 `release:` 出口。精确转移：

```c
EMPTY:   clear request+continuation+observed_epoch+每连接 retry/attempt；return OK。
CLOSED:  publish_terminal++; 同上清理；return CLOSED。
INVALID: publish_terminal++; 同上清理；return INVALID。
OK+lease.level!=Session.level:
         publish_terminal++; 同上清理；return STALE。
OK+match: publish_request=false；observed_epoch=lease.publication_epoch；
         扫描 fanout；最后重算 continuation；release lease。
```

`runtime_world_clear_publish(adapter,true)` 清每连接 `retry_publish/attempt_publication_epoch/attempt_target_*`，但不清 Session attempt、completed 或 terminal；CLOSE 槽和 REBASELINE 则使用 `runtime_world_clear_connection_publish()` 清全部 per-connection publication 状态。`publish_cursor` 在 rebaseline 时归 0。

fanout 每轮从 cursor 起最多扫描 `max_connections` 个槽。空槽 clean skip 不耗预算；打开槽即使 completed==current 也先调用 `break_world_session_sender_state()`。满足 Consumes/Produces 的 clean-skip 条件时不调用 publish、不耗预算；否则若 calls==budget，保持 cursor 指向该槽并停止扫描。每次实际 publish（包括 OVERLOAD/INVALID/CLOSED）`calls++`；每次扫描后 cursor 前进到下一槽。单连接结果绝不提前中止其他连接。扫描结束后 `runtime_world_recompute_continuation()` 用无发送的 sender-state 查询检查所有打开连接：有 retry、保存的 attempt 标量、实际 active，或 `(completed!=current && terminal!=current)` 就为 true；无打开连接则为 false。

若既有 `control_pending` retry 仍 OVERLOAD，立即退出且不 acquire；若 retry 变为其他终态，清 control pending 后允许 queue/continuation 按既有终止语义继续。`max_messages==0` 始终不 acquire、不续发。

- [ ] **Step 9: 实现 OK/OVERLOAD/INVALID/CLOSED/default 的逐分支实际 attempt 判账**

将 `runtime_world_publish_connection()` 的核心写成下列等价 C 控制流。`before` 在调用前读取，`after` 在调用后再次读取；`same_current`、`same_saved` 使用 before 的实际 id/tick，不使用本次参数猜测：

```c
bool had_active = before.attempt_pending;
u64 old_id = before.attempt_target_snapshot_id;
u64 old_tick = before.attempt_target_tick;
bool same_current = had_active &&
    old_id == break_world_snapshot_id(lease->snapshot) &&
    old_tick == break_world_snapshot_tick(lease->snapshot);
bool same_saved = had_active && connection->attempt_target_snapshot_id != 0u &&
    old_id == connection->attempt_target_snapshot_id &&
    old_tick == connection->attempt_target_tick;
BreakNetSendResult sent = break_world_session_publish_snapshot(
    adapter->session, connection->key, lease->snapshot, lease->level_generation);
*out_called = true;

if (sent == BREAK_NET_SEND_OVERLOAD) {
    adapter->publish_overloads++;
    connection->retry_publish = true;
    if (break_world_session_sender_state(adapter->session, connection->key, &after) &&
        after.attempt_pending) {
        bool after_current =
            after.attempt_target_snapshot_id == break_world_snapshot_id(lease->snapshot) &&
            after.attempt_target_tick == break_world_snapshot_tick(lease->snapshot);
        connection->attempt_target_snapshot_id = after.attempt_target_snapshot_id;
        connection->attempt_target_tick = after.attempt_target_tick;
        if (!had_active || after_current) {
            connection->attempt_publication_epoch = lease->publication_epoch;
        } else if (!same_saved) {
            connection->attempt_publication_epoch = 0u; /* 未知旧 attempt */
        } /* same_saved 保留原 attempt epoch，例如 E1。 */
    } else {
        connection->attempt_publication_epoch = 0u;
        connection->attempt_target_snapshot_id = 0u;
        connection->attempt_target_tick = 0u; /* 尚未创建 attempt，只保 retry */
    }
    return BREAK_RUNTIME_OVERLOAD; /* 调用方继续下一连接 */
}

if (sent == BREAK_NET_SEND_OK) {
    if (!break_world_session_sender_state(adapter->session, connection->key, &after) ||
        after.attempt_pending) {
        /* 当前 Session 合同是 OK 后 active 已结束；违反时按 FAILED 终态，
         * 不留下永久 continuation，也不伪造 completed。 */
        connection->retry_publish = false;
        connection->attempt_publication_epoch = 0u;
        connection->attempt_target_snapshot_id = 0u;
        connection->attempt_target_tick = 0u;
        connection->terminal_publication_epoch = lease->publication_epoch;
        adapter->publish_terminal++;
        return BREAK_RUNTIME_FAILED;
    }
    if (!had_active || same_current) {
        connection->completed_publication_epoch = lease->publication_epoch;
    } else if (same_saved && connection->attempt_publication_epoch != 0u) {
        connection->completed_publication_epoch = connection->attempt_publication_epoch;
    } /* 未知旧 attempt：completed 保持不变，current 仍 dirty。 */
    connection->retry_publish = false;
    connection->attempt_publication_epoch = 0u;
    connection->attempt_target_snapshot_id = 0u;
    connection->attempt_target_tick = 0u;
    return BREAK_RUNTIME_OK;
}

connection->retry_publish = false;
connection->attempt_publication_epoch = 0u;
connection->attempt_target_snapshot_id = 0u;
connection->attempt_target_tick = 0u;
connection->terminal_publication_epoch = lease->publication_epoch;
adapter->publish_terminal++;
if (sent == BREAK_NET_SEND_INVALID) return BREAK_RUNTIME_INVALID;
if (sent == BREAK_NET_SEND_CLOSED) return BREAK_RUNTIME_CLOSED;
return BREAK_RUNTIME_FAILED;
```

E1→E2 因而不歧义：E1 OVERLOAD 保存 attempt_epoch=E1；acquire E2 后 before=E1/same_saved，OK 只把 completed 写为 E1，清实际已结束的 attempt/retry；completed!=E2 使 continuation 保持，下一次无 active 才创建并完成 E2。任何 OK 一律写 current 是明确禁止的实现。

- [ ] **Step 10: 接入 drain、stats、close/reopen/rebaseline 与 lifecycle 注释**

queue message 消费保持 FIFO 和 `max_messages` 计数；wrong-level notice 只记录 STALE，不调用 `runtime_world_clear_publish()`，也不提前退出整个 drain。此前合法 request/continuation 必须保留到 batch 末尾并照常 fanout；wrong-level 自身不建立新 request。合法 notice 与 continuation 在 batch 末尾合并；同批后到 CLOSE/REBASELINE 自然影响最终连接集合。drain 最终返回首个非 OK（wrong-level 的 STALE 可成为 `first_error`，即使后续 fanout 成功），OVERLOAD 不掩盖后续逐连接处理，`out_drained` 只计 queue message，不计 continuation。

`runtime_world_pending_locked()` 使用本任务 Produces 的公式；`stats.publish_pending` 与 pending 同源。REBASELINE 成功清所有连接 fanout 状态和旧 request/continuation，CLOSE 成功清该槽，reopen 分配新 connection_epoch 后从零开始。`control_pending` 与 `transport_overloads` 不改含义。lifecycle 保持既有六阶段和 STALE/INVALID/REJECTED/CLOSED+pending0 可完成；只更新头注释，明确 DRAIN 后 `pending!=0 || result==OVERLOAD` 映射 TIMEOUT，下一次 stop 从同一 drain/cursor 恢复。

- [ ] **Step 11: 运行完整 focused GREEN**

```sh
cmake --build engine/build-runtime-world-data-plane \
  --target test_runtime_core test_runtime_bus test_runtime_world_session \
  test_ecs_replication test_world_snapshot_publication test_world_session \
  test_world_session_recovery test_world_session_loopback \
  test_break_session test_break_replication_session -j2
ctest --test-dir engine/build-runtime-world-data-plane --output-on-failure \
  -R '^(test_runtime_core|test_runtime_core_target_contract|test_runtime_bus|test_runtime_world_session|test_runtime_world_session_target_contract|test_ecs_replication|test_world_snapshot_publication|test_replication_target_contract|test_world_session|test_world_session_recovery|test_world_session_loopback|test_break_session|test_break_replication_session)$'
```

Expected: 注册 focused 项全部实际执行并 PASS，无 Not Run；E1/E2、九连接默认 budget、A/B OVERLOAD、终态、close/reopen/rebaseline、destroy、Coordinator 与两个真线程测试均通过。

- [ ] **Step 12: 运行 ASan+UBSan 与 TSan focused**

```sh
cmake -S engine -B engine/build-runtime-world-data-plane-tsan -G Ninja \
  -DCMAKE_BUILD_TYPE=Debug -DENGINE_BUILD_TESTS=ON \
  -DENGINE_RHI_BACKEND=opengl -DCORE_APP_ENABLE_NETWORK=ON \
  -DENGINE_USE_TSAN=ON -DBREAK_ENABLE_SNOWFLAKE=ON \
  -DSNOWFLAKE_SOURCE_DIR=/home/timeshift/opensource/break/.worktrees/snowflake-pin-4ab761fc
cmake --build engine/build-runtime-world-data-plane-asan \
  --target test_runtime_core test_runtime_bus test_runtime_world_session \
  test_ecs_replication test_world_snapshot_publication test_world_session \
  test_world_session_recovery test_world_session_loopback \
  test_break_session test_break_replication_session -j2
cmake --build engine/build-runtime-world-data-plane-tsan \
  --target test_runtime_core test_runtime_bus test_runtime_world_session \
  test_ecs_replication test_world_snapshot_publication test_world_session \
  test_world_session_recovery test_world_session_loopback \
  test_break_session test_break_replication_session -j2
ASAN_OPTIONS=detect_leaks=1 UBSAN_OPTIONS=halt_on_error=1 \
  ctest --test-dir engine/build-runtime-world-data-plane-asan \
  --output-on-failure -R '^(test_runtime_core|test_runtime_core_target_contract|test_runtime_bus|test_runtime_world_session|test_runtime_world_session_target_contract|test_ecs_replication|test_world_snapshot_publication|test_replication_target_contract|test_world_session|test_world_session_recovery|test_world_session_loopback|test_break_session|test_break_replication_session)$'
TSAN_OPTIONS=halt_on_error=1 \
  ctest --test-dir engine/build-runtime-world-data-plane-tsan \
  --output-on-failure -R '^(test_runtime_core|test_runtime_core_target_contract|test_runtime_bus|test_runtime_world_session|test_runtime_world_session_target_contract|test_ecs_replication|test_world_snapshot_publication|test_replication_target_contract|test_world_session|test_world_session_recovery|test_world_session_loopback|test_break_session|test_break_replication_session)$'
```

Expected: 两棵树的 focused 集合都实际执行且零失败，ASan 显式 leak 检测无报告，TSan 无 race 报告。

- [ ] **Step 13: 变异“任何 OK 都标 current”并恢复**

```sh
cp engine/src/runtime/runtime_world_session.c /tmp/runtime_world_session.c.task3
# 仅把 OK 判账替换为 completed_publication_epoch=lease->publication_epoch。
cmake --build engine/build-runtime-world-data-plane --target test_runtime_world_session -j2
engine/build-runtime-world-data-plane/test_runtime_world_session
cp /tmp/runtime_world_session.c.task3 engine/src/runtime/runtime_world_session.c
```

Expected: `publish_overload_resumes_e1_before_latest_e2_and_does_not_block_b` 在 E1 后误清 pending/缺 E2 处 RED；随后恢复源文件。

- [ ] **Step 14: 变异“不读取 active attempt 身份”并恢复**

```sh
cp engine/src/runtime/runtime_world_session.c /tmp/runtime_world_session.c.task3
# 仅把 had_active 的初始化强制为 false。
cmake --build engine/build-runtime-world-data-plane --target test_runtime_world_session -j2
engine/build-runtime-world-data-plane/test_runtime_world_session
cp /tmp/runtime_world_session.c.task3 engine/src/runtime/runtime_world_session.c
```

Expected: E1/E2 与 unknown-old-attempt 测试 RED，证明完成判账不能脱离 Task 1 两个字段；随后恢复源文件。

- [ ] **Step 15: 变异“A OVERLOAD 中止 fanout”并恢复**

```sh
cp engine/src/runtime/runtime_world_session.c /tmp/runtime_world_session.c.task3
# 仅把 OVERLOAD 的继续下一连接改为 goto done。
cmake --build engine/build-runtime-world-data-plane --target test_runtime_world_session -j2
engine/build-runtime-world-data-plane/test_runtime_world_session
cp /tmp/runtime_world_session.c.task3 engine/src/runtime/runtime_world_session.c
```

Expected: A OVERLOAD 后 B `history_count==1` 断言 RED；随后恢复源文件。

- [ ] **Step 16: 变异“删除 per-connection dedup”并恢复**

```sh
cp engine/src/runtime/runtime_world_session.c /tmp/runtime_world_session.c.task3
# 仅让 completed/terminal clean-skip 条件恒为 false。
cmake --build engine/build-runtime-world-data-plane --target test_runtime_world_session -j2
engine/build-runtime-world-data-plane/test_runtime_world_session
cp /tmp/runtime_world_session.c.task3 engine/src/runtime/runtime_world_session.c
```

Expected: 重复 notice 的 World stats `memcmp` 与 `next_delta_id` 断言 RED；随后恢复源文件。

- [ ] **Step 17: 变异“close/reopen/rebaseline 不清状态”并恢复**

```sh
cp engine/src/runtime/runtime_world_session.c /tmp/runtime_world_session.c.task3
# 仅删除 CLOSE 与 REBASELINE 的 runtime_world_clear_connection_publish 调用。
cmake --build engine/build-runtime-world-data-plane --target test_runtime_world_session -j2
engine/build-runtime-world-data-plane/test_runtime_world_session
cp /tmp/runtime_world_session.c.task3 engine/src/runtime/runtime_world_session.c
```

Expected: `publish_lifecycle_resets_scalar_state_and_cancels_old_level` 在新 connection_epoch/delta_id/旧 continuation 断言处 RED；随后恢复源文件。

- [ ] **Step 18: 变异“continuation 不计 pending”并恢复**

```sh
cp engine/src/runtime/runtime_world_session.c /tmp/runtime_world_session.c.task3
# 仅从 runtime_world_pending_locked 删除 publish_request||publish_continuation。
cmake --build engine/build-runtime-world-data-plane --target test_runtime_world_session -j2
engine/build-runtime-world-data-plane/test_runtime_world_session
cp /tmp/runtime_world_session.c.task3 engine/src/runtime/runtime_world_session.c
```

Expected: budget=1 的 destroy 与 Coordinator 首次 stop 断言 RED；随后恢复源文件。

- [ ] **Step 19: 变异“submit 直接调用 Session”并恢复**

```sh
cp engine/src/runtime/runtime_world_session.c /tmp/runtime_world_session.c.task3
# 仅在 direct submit 插入 (void)break_world_session_level_generation(adapter->session);
cmake --build engine/build-runtime-world-data-plane --target test_runtime_world_session -j2
ctest --test-dir engine/build-runtime-world-data-plane --output-on-failure \
  -R '^test_runtime_world_session_target_contract$'
cp /tmp/runtime_world_session.c.task3 engine/src/runtime/runtime_world_session.c
```

Expected: submit-owner target contract RED，pre-drain 行为测试仍保留；随后恢复源文件。

- [ ] **Step 20: 变异“notice 改成普通 data flag”并恢复**

```sh
cp engine/src/runtime/runtime_world_session.c /tmp/runtime_world_session.c.task3
# 仅把 notice 的 view.flags 改为 0，不改既有 56 字节控制 submit。
cmake --build engine/build-runtime-world-data-plane --target test_runtime_world_session -j2
engine/build-runtime-world-data-plane/test_runtime_world_session
cp /tmp/runtime_world_session.c.task3 engine/src/runtime/runtime_world_session.c
```

Expected: 全 control-reserved queue 的首个 direct notice submit 由 OK 变 OVERLOAD，布局/submit 测试 RED；随后恢复源文件。

- [ ] **Step 21: 变异“漏 release lease”并恢复**

```sh
cp engine/src/runtime/runtime_world_session.c /tmp/runtime_world_session.c.task3
# 仅删除 drain 统一出口的 break_world_snapshot_lease_release(&lease)。
cmake --build engine/build-runtime-world-data-plane-asan --target test_runtime_world_session -j2
ASAN_OPTIONS=detect_leaks=1 UBSAN_OPTIONS=halt_on_error=1 \
  engine/build-runtime-world-data-plane-asan/test_runtime_world_session
cp /tmp/runtime_world_session.c.task3 engine/src/runtime/runtime_world_session.c
cmake --build engine/build-runtime-world-data-plane-asan --target test_runtime_world_session -j2
ASAN_OPTIONS=detect_leaks=1 UBSAN_OPTIONS=halt_on_error=1 \
  engine/build-runtime-world-data-plane-asan/test_runtime_world_session
```

Expected: 变异运行时 LSan 报告 adapter 未释放的 snapshot lease并 RED；恢复源文件、重建后同一可执行文件 GREEN 且无 leak 报告。

- [ ] **Step 22: 变异“每连接分别 acquire”并恢复**

```sh
cp engine/src/runtime/runtime_world_session.c /tmp/runtime_world_session.c.task3
# 仅把 acquire 调用移入 runtime_world_publish_connection，使每连接各取 lease。
cmake --build engine/build-runtime-world-data-plane --target test_runtime_world_session -j2
ctest --test-dir engine/build-runtime-world-data-plane --output-on-failure \
  -R '^test_runtime_world_session_target_contract$'
cp /tmp/runtime_world_session.c.task3 engine/src/runtime/runtime_world_session.c
```

Expected: “`runtime_world_publish_connection` 不含 acquire”的 contract RED；随后恢复源文件，不以每连接 lease 代替统一 drain lease。

- [ ] **Step 23: 验证十项变异全部恢复且无生产残留**

```sh
cmake --build engine/build-runtime-world-data-plane --target test_runtime_world_session -j2
ctest --test-dir engine/build-runtime-world-data-plane --output-on-failure \
  -R '^(test_runtime_core|test_runtime_core_target_contract|test_runtime_bus|test_runtime_world_session|test_runtime_world_session_target_contract|test_ecs_replication|test_world_snapshot_publication|test_replication_target_contract|test_world_session|test_world_session_recovery|test_world_session_loopback|test_break_session|test_break_replication_session)$'
git diff --check
```

Expected: 恢复后的完整 focused 集合 GREEN；逐项保存“可构建、RED、恢复”的证据，搜索强制 `had_active=false`、flags=0、`goto done` 等变异片段确认无生产残留，未执行的变异不得记为完成。

- [ ] **Step 24: 实现者先提交完整恢复门，controller 随后评审该提交**

实现者确认十项变异均已恢复后先执行：

```sh
git diff --check
git add engine/src/runtime/runtime_world_session.c \
  engine/src/runtime/runtime_world_session.h \
  engine/src/runtime/runtime_world_session_lifecycle.h \
  engine/tests/test_runtime_world_session.c \
  engine/tests/test_runtime_world_session_target_contract.cmake
git commit -m "feat(runtime): recover snapshot publication fanout"
```

controller 以该提交 SHA、focused/sanitizer 结果和十项变异证据组成 review package，随后进行独立评审，不以未提交 HEAD 作为评审对象。

Expected: controller 逐项核对实际 attempt 判账、lease 边界、fair cursor、pending/Coordinator 和变异证据；本提交仍不包含真实 socket/最终验收，评审通过后才进入 Task 4。

---

### Task 4: 真实双 socket、真线程 loopback、文档与最终验收

**Files:**
- Test: `engine/tests/test_world_session_loopback.c`
- Modify: `engine/CMakeLists.txt`
- Modify: `docs/design/ecs_snapshot_replication_aoi.md`
- Modify: `docs/design/online_session_network.md`
- Modify: `docs/design/runtime_overview.md`
- Modify: `docs/design/runtime_message_model.md`
- Modify: `docs/design/runtime_network.md`
- Modify: `docs/design/runtime_thread_model.md`
- Modify: `docs/design/session_protocol.md`
- Modify: `docs/Implementation_Status.md`
- Modify: `docs/cross_engine/missing_capabilities.md`

**Interfaces:**
- Consumes: Task 3 的 direct submit/config/drain/pending/stats；现有 `socket_start_with_connections()`、`connect_authenticate()`、`socket_select_peer()`、`collect_published()`、`collect_published_pair_interleaved()`、`collect_published_with_payload()`、`write_attempt_ack()`、`write_shuffled_payload()`、`wait_completed()`、`wait_sender_confirmed_for_connection()`、`break_world_session_drain()`、`world_matches()`、`encode_full()`、`add_value()`、`pump()` 与 `TEST_DUAL_OUTBOUND_SHARE`。显式 fair admission 继续使用 `fixture.fair_outbound_admission=true`。
- Produces: 以下测试 helper 与完整真实路径，不改变生产 API：

```c
static bool socket_attach_runtime_publication(SocketFixture *fixture, u32 budget);
static BreakRuntimeError socket_submit_current(
    SocketFixture *fixture, u64 level_generation, u64 correlation_id);
static bool socket_publish_snapshot(
    SocketFixture *fixture, BreakWorldSnapshot *snapshot, u64 level_generation);
```

`SocketFixture` 尾部增加 borrowed/owned 测试状态 `BreakRuntimeBus *bus`、`BreakRuntimeWorldSession *adapter`、`BreakWorldSnapshotPublication *publication` 和两个连接的 adapter epoch。真实路径必须是 snapshot build → publication publish → direct notice → owner adapter drain → BRWD/BRFG → AUTH/socket → 每连接独立 remote World drain；不得直接注入 completion。

- [ ] **Step 1: 修改 loopback target 链接正式 Runtime adapter，保持 test seam 边界**

在 `engine/CMakeLists.txt` 将 `test_world_session_loopback` 的源扩展为 `tests/test_world_session_loopback.c src/core/log.c src/core/profiler.c src/platform/time.c`，沿用 `test_runtime_world_session` 的 Linux/Windows compile definitions 和系统库；链接改为：

```cmake
target_link_libraries(test_world_session_loopback PRIVATE
    runtime_world_session_test runtime_core)
```

`runtime_world_session_test` 已 PUBLIC 链接 `runtime_core_test break_net_test break_ecs_replication_test`，不要直接把 `runtime_world_session.c` 或 lifecycle.c 加进 executable，也不要改 `runtime_core` 的源/依赖。`runtime_core` 保留真实 Coordinator 链接语义，与现有 `test_runtime_world_session` 一致。

```sh
cmake -S engine -B engine/build-runtime-world-data-plane -G Ninja \
  -DCMAKE_BUILD_TYPE=Debug -DENGINE_BUILD_TESTS=ON \
  -DENGINE_RHI_BACKEND=opengl -DCORE_APP_ENABLE_NETWORK=ON \
  -DBREAK_ENABLE_SNOWFLAKE=ON \
  -DSNOWFLAKE_SOURCE_DIR=/home/timeshift/opensource/break/.worktrees/snowflake-pin-4ab761fc
cmake --build engine/build-runtime-world-data-plane \
  --target test_world_session_loopback -j2
```

Expected: 新 Runtime include/helper 尚未加入前可保持链接成功；若重复编入 adapter 源或漏正式链接，target/contract 检查必须失败。

- [ ] **Step 2: 给 SocketFixture 接 Runtime publication，同时保留全部旧测试默认路径**

在 loopback 源加入 `core/platform_thread.h`、`ecs/world_snapshot_publication.h`、`runtime/runtime_world_session.h` 与 `<stdatomic.h>`。实现 Produces 的三个 helper：

```c
static bool socket_attach_runtime_publication(SocketFixture *fixture, u32 budget)
{
    BreakWorldSnapshotPublicationConfig publication_config;
    BreakRuntimeWorldSessionConfig config;
    memset(&publication_config, 0, sizeof(publication_config));
    publication_config.schema_hash = break_schema_hash(fixture->schemas);
    publication_config.level_generation = TEST_LEVEL;
    fixture->publication = break_world_snapshot_publication_create(&publication_config);
    if (!fixture->publication ||
        break_runtime_bus_create(&fixture->bus) != BREAK_RUNTIME_OK) return false;
    memset(&config, 0, sizeof(config));
    config.session = fixture->session;
    config.bus = fixture->bus;
    config.subscriber_name = "world_loopback";
    config.max_connections = 2u;
    config.publication = fixture->publication;
    config.publish_connection_budget = budget;
    fixture->adapter = break_runtime_world_session_create(&config);
    return fixture->adapter != NULL;
}
```

`socket_submit_current()` 构造 `{level,0}` 并调用 Task 3 direct submit；`socket_publish_snapshot()` 只调用真实 publication publish。修改 `connect_authenticate()` 的最后一步：adapter==NULL 时仍直接 `break_world_session_open()`；adapter!=NULL 时构造既有 56 字节 OPEN（kind/key/level，epoch=0），submit+drain 1，并以 `break_runtime_world_session_connection_epoch()` 验证非零 epoch。`socket_select_peer()` 同时交换 active/inactive adapter epoch。

`socket_dispose()` 顺序固定：close adapter；有界 drain 到 pending=0；destroy adapter；close/destroy publication；destroy Bus；然后沿用既有 Session/manager/reactor/World 清理。不得让 publication 或 Bus 早于 adapter 销毁，旧 adapter==NULL 测试行为不变。

- [ ] **Step 3: 写真实双 socket direct notice、budget=1、独立 full/delta 与独立 ACK 的 RED 测试**

新增 `TEST(runtime_notice_real_dual_socket_budget_and_independent_ack)` 并注册。fixture 在 start 前设置 `fair_outbound_admission=true`，`socket_start_with_connections(&fixture,true,2u)` 后 `socket_attach_runtime_publication(&fixture,1u)`；A/B 都经修改后的 `connect_authenticate()` 完成真实 AUTH 和 adapter OPEN。

S1/tick10 路径的精确断言：

```c
/* submit 前记录 A/B sender state，submit 后 memcmp 必须相等。 */
LOOPBACK_CHECK(socket_submit_current(&fixture, TEST_LEVEL,
                                     UINT64_C(0xF123456789ABCDEF)) == BREAK_RUNTIME_OK);
LOOPBACK_CHECK(break_runtime_world_session_drain(fixture.adapter, 1u, &drained) ==
               BREAK_RUNTIME_OK);
LOOPBACK_CHECK(break_runtime_world_session_pending(fixture.adapter) == 1u);
socket_select_peer(&fixture, false);
LOOPBACK_CHECK(collect_published(&fixture, &a_first));
LOOPBACK_CHECK(a_first.kind == BREAK_WORLD_DELTA_WIRE_FULL);
LOOPBACK_CHECK(a_first.target_snapshot_id == break_world_snapshot_id(first));
LOOPBACK_CHECK(a_first.target_tick == 10u);

/* queue 空，第二次 drain 才给 B；A 不重复 full。 */
LOOPBACK_CHECK(break_runtime_world_session_drain(fixture.adapter, 1u, &drained) ==
               BREAK_RUNTIME_OK);
LOOPBACK_CHECK(drained == 0u);
LOOPBACK_CHECK(break_runtime_world_session_pending(fixture.adapter) == 0u);
socket_select_peer(&fixture, true);
LOOPBACK_CHECK(collect_published(&fixture, &b_first));
LOOPBACK_CHECK(b_first.kind == BREAK_WORLD_DELTA_WIRE_FULL);
LOOPBACK_CHECK(b_first.target_snapshot_id == a_first.target_snapshot_id);
```

只 ACK A：`socket_select_peer(false)` + `write_attempt_ack(...,1u,0u)` + `wait_sender_confirmed_for_connection(a_key,s1_id)`，然后确认 B `history_count==1 && confirmed_snapshot_id==0`。S2/tick20 再 notice、两次 budget drain，`collect_published_pair_interleaved()` 必须得到 A DELTA/base=S1、B FULL/base=0，两者 target=S2。随后分别 ACK A2/B2，并验证互不裁剪对方 history。

为了覆盖独立 remote World drain，不直接注入 completion：用现有 `encode_full()` 编 S1，`write_shuffled_payload()` 分别经两个真实 client socket 发送 delta_id=100 的 BRFG/BRWD，`wait_completed(&fixture,2u)` 后：

```c
LOOPBACK_CHECK(break_world_session_drain(fixture.session, a_key,
                                         fixture.remote, 1u) == 1u);
LOOPBACK_CHECK(world_matches(fixture.remote, fixture.schemas, 10u, first_id));
LOOPBACK_CHECK(break_world_entity_count(fixture.remote_secondary) == 0u);
LOOPBACK_CHECK(break_world_session_drain(fixture.session, b_key,
                                         fixture.remote_secondary, 1u) == 1u);
LOOPBACK_CHECK(world_matches(fixture.remote_secondary, fixture.schemas, 10u, first_id));
```

这验证每连接独立 remote World，不把两个 inbound 写进同一 World。

- [ ] **Step 4: 写显式 fair admission、E1/E2、本地 lease release 与 publication replace 恢复 RED 测试**

新增 `TEST(runtime_notice_real_socket_replaces_lease_and_recovers_e1_e2)`，仍用双 socket、budget=1、fair=true：

1. A 以 `TEST_DUAL_OUTBOUND_SHARE` 个 PING 填满自身份额，发布 E1/tick30 并 notice。第一次 drain A 返回 OVERLOAD，`attempt_target_snapshot_id==E1`、`publish_overloads==1`；第二次 drain 必须让 B 收到 E1 full，证明显式 fair admission 下 A 饱和不阻断 B。
2. `socket_select_peer(false)` 后逐个 `read_frame()` 读走 A 的全部 PING，不能用固定 sleep。构建 E2/tick40，publication publish 替换 current；本地 acquire 必须得到 E2 和新 epoch，`break_world_snapshot_lease_release()` 后断言 lease snapshot=NULL、level/epoch=0。释放调用方 E1 引用，验证 Session active attempt 仍拥有它。
3. 不提交新 notice， continuation 自行 acquire E2。下一次 budget drain 让 A 续发旧 E1，`collect_published_with_payload()` 比较 resumed id/tick=E1/30、字节与 `encode_full(e1)` 完全一致且不等于 E2；此时不得把 E2 标 completed。后续 drain 分别让 B/A 发 E2，最终两个 socket 都收到 E2 target，pending=0。
4. 最后再次 acquire current，确认仍是 E2；release 本地 lease。adapter drain 不持旧 lease，publication replace 后恢复不依赖调用方 E1 指针。

关键判账断言：

```c
LOOPBACK_CHECK(resumed.target_snapshot_id == e1_id);
LOOPBACK_CHECK(resumed.target_snapshot_id != e2_id);
LOOPBACK_CHECK(resumed.target_tick == 30u);
LOOPBACK_CHECK(actual_size == expected_size);
LOOPBACK_CHECK(memcmp(actual_payload, expected_payload, expected_size) == 0);
LOOPBACK_CHECK(break_runtime_world_session_pending(fixture.adapter) != 0u);
/* 只有后续真实 E2 attempt 才允许 pending=0。 */
```

- [ ] **Step 5: 写真实 socket 上生产线程/drain 的原子 barrier 竞态 RED 测试**

新增 `RuntimeSocketNoticeRace`，复用 Task 3 的两阶段 `_Atomic u32 ready` + `_Atomic bool go` 模式，另有 `done/failed/accepted`。库级与 socket 生产者的 go-gate 都必须有界自旋（上限 100000000 次），不得写成无界 `while (!go) yield();`；超时后设置 `failed` 与 `done` 并返回，保证任何退出路径都置 `done`，主线程 `platform_thread_join` 不会挂死。生产线程执行 8 轮：修改 fixture 的 authoritative World、build tick=i+1、publication publish、direct submit、release snapshot；它不得调用 Session、reactor、manager 或 remote World。主线程等待 ready、释放 go，在有界循环中 owner drain、`pump()` 和 `platform_thread_yield()`，join 后继续 drain 到 pending=0；不得使用固定 sleep 证明正确。

用 `break_world_snapshot_publication_acquire()` 读取 final current id 后 release。对每个连接，以 sender `next_delta_id-1` 得到实际创建的 attempt 数（中间 epoch 可 coalesce，不能假设 8 个），逐个 `socket_select_peer()` + `collect_published()` 读真实 BRFG，断言 target tick 严格递增且最后一个 target id=final current；A/B 分别验证。queue submit OVERLOAD 只允许用有界 yield retry，其他错误设置 failed。最终 `accepted==8`、`!failed`、`publish_pending==false`。

```sh
cmake --build engine/build-runtime-world-data-plane \
  --target test_world_session_loopback test_runtime_world_session -j2 && \
engine/build-runtime-world-data-plane/test_world_session_loopback
```

Expected: 在 Task 3 完整实现上若 loopback 接线有误，测试会在 AUTH 后 adapter 无连接、budget cursor、E1/E2、独立 ACK/World 或真线程 final current 处 RED；不得改成直接 `break_world_session_publish_snapshot()` 让测试变绿。

- [ ] **Step 6: 修正真实接线并运行 loopback/focused GREEN**

只允许修正测试 fixture/target 接线或 Task 3 已证明缺失的真实路径缺陷；若改生产代码，必须回到 Task 3 增加同样的公开行为断言并重跑其 focused/sanitizer。真实 GREEN 命令：

```sh
cmake --build engine/build-runtime-world-data-plane \
  --target test_runtime_core test_runtime_bus test_runtime_world_session \
  test_ecs_replication test_world_snapshot_publication test_world_session \
  test_world_session_recovery test_world_session_loopback \
  test_break_session test_break_replication_session -j2
ctest --test-dir engine/build-runtime-world-data-plane --output-on-failure \
  -R '^(test_runtime_core|test_runtime_core_target_contract|test_runtime_bus|test_runtime_world_session|test_runtime_world_session_target_contract|test_ecs_replication|test_world_snapshot_publication|test_replication_target_contract|test_world_session|test_world_session_recovery|test_world_session_loopback|test_break_session|test_break_replication_session)$'
```

Expected: focused 全部实际执行 PASS，旧 loopback 六项与新 Runtime socket/真线程用例共同通过，无 Not Run。

- [ ] **Step 7: 在真实 socket 路径复跑三项高价值变异并恢复**

备份 `runtime_world_session.c`，分别：任意 OK 标 current（真实 E1/E2 测试必须 RED）；A OVERLOAD 中止 fanout（fair=true 的 B full 必须失败）；删除统一 lease release（`ASAN_OPTIONS=detect_leaks=1` 直跑新 loopback，LSan 必须 RED）。每项恢复后重跑新 loopback。不得为让变异测试简单而加入 production test hook。

- [ ] **Step 8: 在真实 socket 变更上配置并预跑三套 focused sanitizer**

在提交前先用 ASan+UBSan/TSan 构建并运行同一 focused 正则，尽早排除接线问题；本步不替代 Task 4 提交后在最终 HEAD 的重跑：

```sh
cmake --build engine/build-runtime-world-data-plane-asan \
  --target test_runtime_core test_runtime_bus test_runtime_world_session \
  test_ecs_replication test_world_snapshot_publication test_world_session \
  test_world_session_recovery test_world_session_loopback \
  test_break_session test_break_replication_session -j2
cmake --build engine/build-runtime-world-data-plane-tsan \
  --target test_runtime_core test_runtime_bus test_runtime_world_session \
  test_ecs_replication test_world_snapshot_publication test_world_session \
  test_world_session_recovery test_world_session_loopback \
  test_break_session test_break_replication_session -j2
ASAN_OPTIONS=detect_leaks=1 UBSAN_OPTIONS=halt_on_error=1 \
  ctest --test-dir engine/build-runtime-world-data-plane-asan \
  --output-on-failure -R '^(test_runtime_core|test_runtime_core_target_contract|test_runtime_bus|test_runtime_world_session|test_runtime_world_session_target_contract|test_ecs_replication|test_world_snapshot_publication|test_replication_target_contract|test_world_session|test_world_session_recovery|test_world_session_loopback|test_break_session|test_break_replication_session)$'
TSAN_OPTIONS=halt_on_error=1 \
  ctest --test-dir engine/build-runtime-world-data-plane-tsan \
  --output-on-failure -R '^(test_runtime_core|test_runtime_core_target_contract|test_runtime_bus|test_runtime_world_session|test_runtime_world_session_target_contract|test_ecs_replication|test_world_snapshot_publication|test_replication_target_contract|test_world_session|test_world_session_recovery|test_world_session_loopback|test_break_session|test_break_replication_session)$'
```

Expected: normal、ASan+UBSan、TSan focused 均实际执行全绿；未构建或 Not Run 不计通过，ASan 必须显式 `detect_leaks=1`。

- [ ] **Step 9: 追加 snapshot/online/Runtime 总览三份日期小节**

以下文件各追加独立 `2026-11-25` 小节，不改写既有段落和历史数字：

- `docs/design/ecs_snapshot_replication_aoi.md`：immutable publication latest-current、lease/epoch 与 snapshot id 的区别、明确仍无 AOI/共享 live World。
- `docs/design/online_session_network.md`：outbound-only handoff、非可靠每 epoch 广播、非跨 World 持久身份、非权威合并。
- `docs/design/runtime_overview.md`：direct notice 架构、level/publication/connection/queue generation 等代次分离、target 依赖边界、core_app 不自动接线。

- [ ] **Step 10: 追加消息/网络/线程三份日期小节**

- `docs/design/runtime_message_model.md`：追加 `2026-11-25` 小节，记录 16 字节布局、0x5754/version1、control flag、共享 sequence/correlation、外部 Bus REJECTED、56 字节控制不变。
- `docs/design/runtime_network.md`：追加 `2026-11-25` 小节，记录预算/cursor、full/delta/ACK/NEED_FULL、E1/E2、fair admission 默认 false 与测试显式 true、wire 不变。
- `docs/design/runtime_thread_model.md`：追加 `2026-11-25` 小节，记录 producer/owner 线程纪律、锁边界、真线程 barrier、lease 不跨 drain。

- [ ] **Step 11: 追加协议/状态/缺口三份日期小节**

- `docs/design/session_protocol.md`：追加 `2026-11-25` 小节，记录 active attempt id/tick、逐分支判账、close/reopen/rebaseline、EMPTY/CLOSED/terminal 和实际已取得的 socket 证据。
- `docs/Implementation_Status.md`：追加 `2026-11-25` 小节，只记录已经实际运行的 RED/GREEN、变异、normal/ASan+UBSan/TSan 计数与限制；远端结果未发生前不写。
- `docs/cross_engine/missing_capabilities.md`：追加 `2026-11-25` 小节，保留共享 live World、权威合并、跨 World 身份、AOI、自动换级、资产链、inbound completion、可靠 epoch 广播等后续缺口。

九份文档都只追加新日期小节；标题可沿用各文件语言，但日期和本切片边界必须明确，不改写历史收据。

- [ ] **Step 12: 提交真实 socket 与文档评审门**

```sh
git diff --check
git add engine/CMakeLists.txt engine/tests/test_world_session_loopback.c \
  docs/design/ecs_snapshot_replication_aoi.md \
  docs/design/online_session_network.md docs/design/runtime_overview.md \
  docs/design/runtime_message_model.md docs/design/runtime_network.md \
  docs/design/runtime_thread_model.md docs/design/session_protocol.md \
  docs/Implementation_Status.md docs/cross_engine/missing_capabilities.md
git commit -m "test(runtime): verify snapshot notice data plane"
```

Expected: 提交只含本任务真实 socket、必要 target 配置和九份文档追加；若评审修改任一源码/测试，必须重新执行 focused sanitizer。

- [ ] **Step 13: 在最终 HEAD 配置并运行完整 OpenGL/Vulkan CTest 与合同**

先在最终提交 HEAD 上重跑 normal、ASan+UBSan、TSan focused，再跑完整双后端；不能使用 Step 8 的提交前结果代替：

```sh
git status --short
cmake --build engine/build-runtime-world-data-plane \
  --target test_runtime_core test_runtime_bus test_runtime_world_session \
  test_ecs_replication test_world_snapshot_publication test_world_session \
  test_world_session_recovery test_world_session_loopback \
  test_break_session test_break_replication_session -j2
cmake --build engine/build-runtime-world-data-plane-asan \
  --target test_runtime_core test_runtime_bus test_runtime_world_session \
  test_ecs_replication test_world_snapshot_publication test_world_session \
  test_world_session_recovery test_world_session_loopback \
  test_break_session test_break_replication_session -j2
cmake --build engine/build-runtime-world-data-plane-tsan \
  --target test_runtime_core test_runtime_bus test_runtime_world_session \
  test_ecs_replication test_world_snapshot_publication test_world_session \
  test_world_session_recovery test_world_session_loopback \
  test_break_session test_break_replication_session -j2
ctest --test-dir engine/build-runtime-world-data-plane --output-on-failure \
  -R '^(test_runtime_core|test_runtime_core_target_contract|test_runtime_bus|test_runtime_world_session|test_runtime_world_session_target_contract|test_ecs_replication|test_world_snapshot_publication|test_replication_target_contract|test_world_session|test_world_session_recovery|test_world_session_loopback|test_break_session|test_break_replication_session)$'
ASAN_OPTIONS=detect_leaks=1 UBSAN_OPTIONS=halt_on_error=1 \
  ctest --test-dir engine/build-runtime-world-data-plane-asan \
  --output-on-failure -R '^(test_runtime_core|test_runtime_core_target_contract|test_runtime_bus|test_runtime_world_session|test_runtime_world_session_target_contract|test_ecs_replication|test_world_snapshot_publication|test_replication_target_contract|test_world_session|test_world_session_recovery|test_world_session_loopback|test_break_session|test_break_replication_session)$'
TSAN_OPTIONS=halt_on_error=1 \
  ctest --test-dir engine/build-runtime-world-data-plane-tsan \
  --output-on-failure -R '^(test_runtime_core|test_runtime_core_target_contract|test_runtime_bus|test_runtime_world_session|test_runtime_world_session_target_contract|test_ecs_replication|test_world_snapshot_publication|test_replication_target_contract|test_world_session|test_world_session_recovery|test_world_session_loopback|test_break_session|test_break_replication_session)$'
cmake -S engine -B engine/build-runtime-world-data-plane-vk -G Ninja \
  -DCMAKE_BUILD_TYPE=Debug -DENGINE_BUILD_TESTS=ON \
  -DENGINE_RHI_BACKEND=vulkan -DCORE_APP_ENABLE_NETWORK=ON \
  -DBREAK_ENABLE_SNOWFLAKE=ON \
  -DSNOWFLAKE_SOURCE_DIR=/home/timeshift/opensource/break/.worktrees/snowflake-pin-4ab761fc
cmake --build engine/build-runtime-world-data-plane -j2
cmake --build engine/build-runtime-world-data-plane-vk -j2
ctest --test-dir engine/build-runtime-world-data-plane -N
ctest --test-dir engine/build-runtime-world-data-plane-vk -N
ctest --test-dir engine/build-runtime-world-data-plane --output-on-failure -j2
ctest --test-dir engine/build-runtime-world-data-plane-vk --output-on-failure -j2
ctest --test-dir engine/build-runtime-world-data-plane --output-on-failure \
  -R '^(test_runtime_world_session_target_contract|test_runtime_core_target_contract|test_replication_target_contract)$'
```

Expected: 最终 HEAD 的 normal、ASan+UBSan（显式 `detect_leaks=1`）、TSan focused 均实际执行全绿；两后端完整未过滤 CTest 均执行。逐项记录 focused 与完整矩阵的注册数、实际通过、条件 skip、失败数与耗时，合同全绿。条件 skip、既有 Lua longjmp、混合 TSan 和 Proton 77 不得升级为原生 GPU 或完整 sanitizer 验收。若最终 HEAD 不是干净提交或任何测试未构建/Not Run，不得记通过；修复后在新最终 HEAD 重跑本步及受影响的 focused。

- [ ] **Step 14: controller 评审四个实现提交，推送产品提交并等待远端成功**

controller 以 Task 1–4 的四个已提交实现 SHA 及各自证据组成 review package，独立评审设计覆盖、Task 2 中间门边界、E1/E2 判账、十项变异、真实 socket、最终矩阵和文档追加。评审范围是这四个实现提交；既有 design/plan 提交保留在分支历史中，但不计入四个实现提交，也不得以未提交 HEAD 代替 review package。修复全部 Critical/Important 后，先产生修复提交并在新 HEAD 重跑受影响验证与评审。确认工作树干净、最终产品 HEAD 满足 Step 13 后：

```sh
git fetch origin
git log --oneline origin/master..HEAD
git status --short
git push origin HEAD:master
PRODUCT_SHA=$(git rev-parse HEAD)
git fetch origin
test "$(git rev-parse origin/master)" = "$PRODUCT_SHA"
gh run list --branch master --commit "$PRODUCT_SHA" --limit 20 \
  --json databaseId,name,workflowName,headSha,status,conclusion,url
```

`git log --oneline origin/master..HEAD` 用于展示包括 design/plan 在内的全部待推送提交，不缩减前述四个实现提交的独立评审范围。产品 push 只允许 fast-forward；若 `origin/master` 已前进导致拒绝，不得 force push，必须整合新基线、重跑 Step 13 和独立评审后再推。

对实际触发且适用的 CI、Windows、QUIC 和 Proton run，从 JSON 取对应 `databaseId` 赋给 `RUN_ID`，执行 `gh run watch "$RUN_ID" --exit-status`，保存 run id、URL、`PRODUCT_SHA` 和结论。所有适用远端 run 最终成功后才允许进入收据步骤；Proton 77 等条件结果仍按既有平台边界单列，不升级为原生 GPU 证据。

Expected: 产品提交已 fast-forward 推到 master，`origin/master == PRODUCT_SHA`，适用 CI/Windows/QUIC/Proton 均取得该 SHA 的最终成功结果；历史 run、失败 run、条件 skip 或未触发 run 不得冒充本切片验收。

- [ ] **Step 15: 从最新 origin/master 建独立收据工作区，提交并核验文档收据**

只有 Step 14 的适用远端结果全部最终成功后才能写收据，不得预写。回到产品工作区获取最新 master，并从该精确远端基线创建独立的 detached 收据工作区：

```sh
PRODUCT_SHA=$(git rev-parse HEAD)
git fetch origin
RECEIPT_ROOT=/home/timeshift/opensource/break/.worktrees/runtime-world-data-plane-receipt
git worktree add --detach "$RECEIPT_ROOT" origin/master
cd "$RECEIPT_ROOT"
RECEIPT_BASE_SHA=$(git rev-parse HEAD)
```

在收据工作区中，仅向 `docs/Implementation_Status.md` 和 `docs/cross_engine/missing_capabilities.md` 各追加一个新的 **2026-11-25** 收据小节，记录实际 `PRODUCT_SHA`、CI/Windows/QUIC/Proton run id/URL/结论、条件限制，以及 `RECEIPT_BASE_SHA`；若 master 在产品推送后已有其他提交，必须区分产品验证 SHA 与收据基线 SHA。不得改写历史收据，也不得把未发生的结果写入文档。

配置收据工作区的合同树并实际运行命名与 Wayland CI/文档合同：

```sh
cmake -S engine -B engine/build-snapshot-notice-receipt -G Ninja \
  -DCMAKE_BUILD_TYPE=Debug -DENGINE_BUILD_TESTS=ON \
  -DENGINE_RHI_BACKEND=opengl -DCORE_APP_ENABLE_NETWORK=ON \
  -DBREAK_ENABLE_SNOWFLAKE=ON \
  -DSNOWFLAKE_SOURCE_DIR=/home/timeshift/opensource/break/.worktrees/snowflake-pin-4ab761fc
ctest --test-dir engine/build-snapshot-notice-receipt --output-on-failure \
  -R '^(test_repo_naming_contract|test_core_app_naming_contract|test_wayland_ci_migration_contract)$'
git diff --check
git add docs/Implementation_Status.md docs/cross_engine/missing_capabilities.md
git commit -m "docs(runtime): record snapshot notice verification"
RECEIPT_SHA=$(git rev-parse HEAD)
git push origin HEAD:master
git fetch origin
test "$(git rev-parse origin/master)" = "$RECEIPT_SHA"
git status --short
```

收据提交只含上述两份文档的新追加小节。push 必须 fast-forward；若远端在收据提交期间前进，不得 force push，应 fetch 后将该收据提交放到新的 `origin/master` 基线上，重跑同一命名/Wayland 合同，再推送并核验新 SHA。

Expected: 命名与 Wayland CI/文档合同全部实际 PASS；`docs(runtime): record snapshot notice verification` 已 fast-forward 推送，最终 `origin/master == RECEIPT_SHA`，收据工作区无未提交文档改动，所有远端收据都对应已发生的成功结果。
