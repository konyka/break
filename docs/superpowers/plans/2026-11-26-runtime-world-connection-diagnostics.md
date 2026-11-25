# Runtime World Connection Diagnostics Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** 给 Runtime World adapter 增加只读的逐连接诊断快照，让发布卡住时能定位到具体连接，而不改变任何行为、wire 或默认语义。

**Architecture:** 新增一个公共 POD 结构和一个查询函数；函数在 adapter mutex 内复制每条已打开连接的标量判账字段，不调用 World Session、publication 或 queue。`publish_dirty` 复用与 `runtime_world_recompute_continuation` 相同的单连接判据。

**Tech Stack:** C11、CMake/CTest、现有 `test_runtime_world_session` 夹具、ASan+UBSan、TSan。

## Global Constraints

- 不新增或修改任何 wire 消息；BRWC/BRWD/BRFG、`0x5753`、`0x5754` 与 56/16 字节布局不变。
- 不改变 drain、pending、stats、`fair_outbound_admission` 默认值或 shutdown 顺序；查询不得推进状态机。
- 新结构体与函数只追加；已有结构体布局与函数签名不变。
- 查询持 adapter mutex 复制标量，不得在持有该 mutex 的 owner 路径内重入。
- `capacity` 不足时写入 `capacity` 项并返回**实际打开连接数**；`adapter == NULL` 返回 0。
- 只返回 `connection_key != 0` 的槽位，按 slot 升序。
- C11/Google 风格；所有显式网络 configure 使用 `CORE_APP_ENABLE_NETWORK=ON`、`BREAK_ENABLE_SNOWFLAKE=ON` 与固定 pin `4ab761fc58a9d15970f295e231003c99a7d44df8`。
- 文档只追加 2026-11-26 小节，不改写历史收据，不预写远端结果。

---

### Task 1: 库级只读快照与单元测试

**Files:**
- Modify: `engine/src/runtime/runtime_world_session.h`
- Modify: `engine/src/runtime/runtime_world_session.c`
- Test: `engine/tests/test_runtime_world_session.c`

**Interfaces:**
- Consumes: 私有 `RuntimeWorldConnection`（`key/epoch/completed_publication_epoch/terminal_publication_epoch/attempt_publication_epoch/attempt_target_snapshot_id/attempt_target_tick/retry_publish`）、adapter 字段 `publish_observed_epoch`、既有 `Fixture`/`open_connection()`/`make_target()`/`publish_target()`/`control_via_adapter()`/`clear_outbound()`。
- Produces:

```c
typedef struct {
    u64 connection_key;
    u64 connection_epoch;
    u64 completed_publication_epoch;
    u64 terminal_publication_epoch;
    u64 attempt_publication_epoch;
    u64 attempt_target_snapshot_id;
    u64 attempt_target_tick;
    bool retry_publish;
    bool publish_dirty;
} BreakRuntimeWorldConnectionSnapshot;

usize break_runtime_world_session_connection_snapshots(
    const BreakRuntimeWorldSession *adapter,
    BreakRuntimeWorldConnectionSnapshot *out_snapshots,
    usize capacity);
```

- [ ] **Step 1: 写空 adapter 与容量边界的 RED 测试**

在 `test_runtime_world_session.c` 增加 `TEST(connection_snapshots_report_per_connection_state)`，先写：

```c
Fixture fixture;
BreakRuntimeWorldConnectionSnapshot snaps[4];
usize count;

ASSERT_EQ(break_runtime_world_session_connection_snapshots(NULL, snaps, 4u), 0u);
ASSERT_TRUE(fixture_init(&fixture, 7u, 4u));
ASSERT_EQ(break_runtime_world_session_connection_snapshots(fixture.adapter, NULL, 0u), 0u);
ASSERT_EQ(break_runtime_world_session_connection_snapshots(fixture.adapter, snaps, 0u), 0u);
ASSERT_EQ(break_runtime_world_session_connection_snapshots(fixture.adapter, NULL, 4u), 0u);
fixture_dispose(&fixture);
```

- [ ] **Step 2: 写三连接、截断与顺序的 RED 测试**

```c
u64 epoch_a = 0u, epoch_b = 0u, epoch_c = 0u;
ASSERT_TRUE(open_connection(&fixture, KEY_A, 7u, &epoch_a));
ASSERT_TRUE(open_connection(&fixture, KEY_B, 7u, &epoch_b));
ASSERT_TRUE(open_connection(&fixture, KEY_C, 7u, &epoch_c));
ASSERT_EQ(break_runtime_world_session_connection_snapshots(fixture.adapter, NULL, 0u), 3u);
memset(snaps, 0, sizeof(snaps));
ASSERT_EQ(break_runtime_world_session_connection_snapshots(fixture.adapter, snaps, 1u), 3u);
ASSERT_EQ(snaps[0].connection_key, KEY_A);
ASSERT_EQ(snaps[1].connection_key, 0u); /* 未写入 */
memset(snaps, 0, sizeof(snaps));
ASSERT_EQ(break_runtime_world_session_connection_snapshots(fixture.adapter, snaps, 4u), 3u);
ASSERT_EQ(snaps[0].connection_key, KEY_A);
ASSERT_EQ(snaps[0].connection_epoch, epoch_a);
ASSERT_EQ(snaps[1].connection_key, KEY_B);
ASSERT_EQ(snaps[2].connection_key, KEY_C);
ASSERT_EQ(snaps[3].connection_key, 0u);
```

预期 RED：函数未声明，编译失败。

- [ ] **Step 3: 写发布判账与只读性的 RED 测试**

用 publication fixture 发布 S1 并 drain 后：

```c
ASSERT_EQ(break_runtime_world_session_connection_snapshots(fixture.adapter, snaps, 4u), 2u);
/* A/B 各完成一次发布，dirty 为 false。 */
ASSERT_FALSE(snaps[0].publish_dirty);
ASSERT_EQ(snaps[0].completed_publication_epoch, snaps[1].completed_publication_epoch);
/* 查询前后聚合状态与 sender state 完全不变。 */
break_runtime_world_session_stats(fixture.adapter, &before_stats);
ASSERT_TRUE(break_world_session_sender_state(fixture.session, KEY_A, &before_a));
(void)break_runtime_world_session_connection_snapshots(fixture.adapter, snaps, 4u);
break_runtime_world_session_stats(fixture.adapter, &after_stats);
ASSERT_TRUE(break_world_session_sender_state(fixture.session, KEY_A, &after_a));
ASSERT_EQ(memcmp(&before_stats, &after_stats, sizeof(before_stats)), 0);
ASSERT_EQ(memcmp(&before_a, &after_a, sizeof(before_a)), 0);
```

- [ ] **Step 4: 写 OVERLOAD、CLOSE 与 REBASELINE 的 RED 测试**

```c
/* 队列满使 A 进入 OVERLOAD，B 不受影响。 */
ASSERT_EQ(break_runtime_world_session_connection_snapshots(fixture.adapter, snaps, 4u), 2u);
ASSERT_TRUE(snaps[0].retry_publish);
ASSERT_TRUE(snaps[0].publish_dirty);
ASSERT_NE(snaps[0].attempt_target_snapshot_id, 0u);
ASSERT_FALSE(snaps[1].publish_dirty);

/* CLOSE 后该连接消失，计数减一。 */
control_via_adapter(&fixture, BREAK_RUNTIME_WORLD_COMMAND_CLOSE, KEY_A, epoch_a, 7u);
ASSERT_EQ(break_runtime_world_session_connection_snapshots(fixture.adapter, snaps, 4u), 1u);
ASSERT_EQ(snaps[0].connection_key, KEY_B);

/* REBASELINE 后仍是一条连接，但 epoch 状态已重置。 */
ASSERT_TRUE(break_world_session_rebaseline(fixture.session, 8u));
ASSERT_EQ(break_runtime_world_session_connection_snapshots(fixture.adapter, snaps, 4u), 1u);
ASSERT_EQ(snaps[0].completed_publication_epoch, 0u);
ASSERT_FALSE(snaps[0].retry_publish);
```

- [ ] **Step 5: 确认 RED**

```sh
cmake --build engine/build --target test_runtime_world_session -j2
```

Expected: 因 `break_runtime_world_session_connection_snapshots` 未声明而编译失败；不得删断言消除 RED。

- [ ] **Step 6: 最小实现**

头文件追加结构体与函数声明（放在 `stats()` 之后）。实现：

```c
usize break_runtime_world_session_connection_snapshots(
    const BreakRuntimeWorldSession *adapter,
    BreakRuntimeWorldConnectionSnapshot *out_snapshots, usize capacity)
{
    usize opened = 0u;
    if (!adapter) return 0u;
    platform_mutex_lock((PlatformMutex *)(uintptr_t)&adapter->mutex);
    for (usize i = 0u; i < adapter->max_connections; ++i) {
        const RuntimeWorldConnection *c = &adapter->connections[i];
        BreakRuntimeWorldConnectionSnapshot snap;
        if (c->key == 0u) continue;
        memset(&snap, 0, sizeof(snap));
        snap.connection_key = c->key;
        snap.connection_epoch = c->epoch;
        snap.completed_publication_epoch = c->completed_publication_epoch;
        snap.terminal_publication_epoch = c->terminal_publication_epoch;
        snap.attempt_publication_epoch = c->attempt_publication_epoch;
        snap.attempt_target_snapshot_id = c->attempt_target_snapshot_id;
        snap.attempt_target_tick = c->attempt_target_tick;
        snap.retry_publish = c->retry_publish;
        snap.publish_dirty =
            c->retry_publish ||
            (adapter->publish_observed_epoch == 0u
                 ? c->attempt_publication_epoch != 0u
                 : (c->completed_publication_epoch != adapter->publish_observed_epoch &&
                    c->terminal_publication_epoch != adapter->publish_observed_epoch));
        if (out_snapshots && opened < capacity) out_snapshots[opened] = snap;
        ++opened;
    }
    platform_mutex_unlock((PlatformMutex *)(uintptr_t)&adapter->mutex);
    return opened;
}
```

不调用 World Session、publication 或 queue；不清除任何状态。

- [ ] **Step 7: GREEN 与回归**

```sh
cmake --build engine/build --target test_runtime_world_session -j2
./engine/build/test_runtime_world_session
```

Expected: 全部通过，既有用例计数不变。

- [ ] **Step 8: 四项定向变异**

依次改生产代码并重跑 `test_runtime_world_session`，每项均需判红后精确恢复：

1. 截断时返回 `capacity` 而非 `opened` → capacity=1 用例 RED。
2. `publish_dirty` 恒为 `false` → OVERLOAD 用例 RED。
3. 查询内清 `c->retry_publish` → 只读性 `memcmp` 用例 RED。
4. 去掉 mutex 改为直接返回槽位指针 → TSan 用例 RED（见 Task 2）。

- [ ] **Step 9: ASan+UBSan**

```sh
cmake --build engine/build-asan --target test_runtime_world_session -j2
ASAN_OPTIONS=detect_leaks=1 UBSAN_OPTIONS=halt_on_error=1 ./engine/build-asan/test_runtime_world_session
```

Expected: 全绿，无 sanitizer/leak 报告。

- [ ] **Step 10: 提交**

```sh
git diff --check
git add engine/src/runtime/runtime_world_session.h engine/src/runtime/runtime_world_session.c \
  engine/tests/test_runtime_world_session.c
git commit -m "feat(runtime): expose per-connection diagnostics snapshot"
```

### Task 2: 线程用例、文档与最终验收

**Files:**
- Test: `engine/tests/test_runtime_world_session.c`
- Modify: `docs/design/runtime_network.md`
- Modify: `docs/design/runtime_overview.md`
- Modify: `docs/Implementation_Status.md`
- Modify: `docs/cross_engine/missing_capabilities.md`

**Interfaces:**
- Consumes: Task 1 的 `BreakRuntimeWorldConnectionSnapshot` 与查询函数；既有 `ConcurrentShared`、`PlatformThread`、`platform_thread_yield()`、C11 atomics。
- Produces: 并发安全的只读查询证据与四份文档追加；不新增生产 API。

- [ ] **Step 1: 写真线程查询竞态用例**

生产者线程持续 `submit_current()`（OVERLOAD 时有界 yield 重试），主线程在有界循环内反复调用查询，断言每次返回 `<= max_connections`、所有写入项 `connection_key != 0`；join 后最终查询返回打开连接数。使用原子 ready/go barrier 与有界 yield，不用固定 sleep。

- [ ] **Step 2: TSan 与 normal 复跑**

```sh
cmake --build engine/build-tsan --target test_runtime_world_session -j2
TSAN_OPTIONS=halt_on_error=1 ./engine/build-tsan/test_runtime_world_session
cmake --build engine/build --target test_runtime_world_session -j2
./engine/build/test_runtime_world_session
```

Expected: 两者全绿，无 race 报告。

- [ ] **Step 3: 追加四份文档**

- `docs/design/runtime_network.md`：追加 2026-11-26 小节，说明逐连接只读诊断的字段、`publish_dirty` 判据与“不是权威 World 状态”。
- `docs/design/runtime_overview.md`：追加同日期小节，说明聚合统计与逐连接快照的分工。
- `docs/Implementation_Status.md`：追加本地实际计数，不预写远端。
- `docs/cross_engine/missing_capabilities.md`：保留远程指标导出、历史采样、告警与共享 live World 等缺口。

- [ ] **Step 4: 提交**

```sh
git diff --check
git add engine/tests/test_runtime_world_session.c docs/design/runtime_network.md \
  docs/design/runtime_overview.md docs/Implementation_Status.md \
  docs/cross_engine/missing_capabilities.md
git commit -m "test(runtime): cover per-connection diagnostics concurrency"
```

- [ ] **Step 5: 最终 HEAD 双后端与合同**

```sh
cmake --build engine/build -j2 && ctest --test-dir engine/build --output-on-failure -j2
cmake --build engine/build-vulkan -j2 && ctest --test-dir engine/build-vulkan --output-on-failure -j2
```

记录注册、通过、条件 skip、失败与耗时；4 个既有条件 skip 不计通过。

- [ ] **Step 6: 评审、推送与收据**

独立任务评审与整分支评审后，fast-forward 推送 `HEAD:master`，监视 CI/Windows/QUIC/Proton，成功后从最新 `origin/master` 建独立收据工作区追加两份文档收据，提交 `docs(runtime): record connection diagnostics verification` 并核验远端 SHA。
