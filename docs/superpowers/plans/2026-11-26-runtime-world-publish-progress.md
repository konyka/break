# Runtime World 发布进度摘要实施计划

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** 增加只读的 adapter 级发布进度摘要，回答“最近推进到哪个 publication epoch、还有几条连接未完成、是否还有待处理 request/续发”，不引入指标协议或网络暴露。

**Architecture:** 新结构体与函数；在 adapter mutex 内一次遍历统计连接数与脏连接数，并复制 observed epoch 与两个 pending 布尔。判脏复用与逐连接快照完全相同的表达式,避免口径分叉。

**Tech Stack:** C11、CMake/CTest、现有 `test_runtime_world_session` 夹具、ASan+UBSan、TSan。

## Global Constraints

- 不新增/修改 wire；BRWC/BRWD/BRFG、`0x5753`、`0x5754`、56/16 字节布局不变。
- 不改 drain、pending、判账、shutdown；查询不得推进状态机，不得调用 World Session、publication 或 queue。
- 新结构体与函数只追加；既有布局与签名不变。
- 持 adapter mutex 一段短临界区；不得在已持有它的 owner 路径重入。
- `adapter == NULL` 返回 `false` 且输出清零。
- `dirty_connections` 的判据必须与 `BreakRuntimeWorldConnectionSnapshot.publish_dirty` 逐字一致。
- C11/Google 风格；显式网络 configure 使用 `CORE_APP_ENABLE_NETWORK=ON`、`BREAK_ENABLE_SNOWFLAKE=ON` 与固定 pin `4ab761fc58a9d15970f295e231003c99a7d44df8`。
- 文档只追加 2026-11-26 小节，不改历史收据，不预写远端结果。

---

### Task 1: 库级摘要与单元测试

**Files:**
- Modify: `engine/src/runtime/runtime_world_session.h`
- Modify: `engine/src/runtime/runtime_world_session.c`
- Test: `engine/tests/test_runtime_world_session.c`

**Interfaces:**
- Consumes: 私有 `RuntimeWorldConnection` 全部标量、adapter 的 `publish_observed_epoch`/`publish_request`/`publish_continuation`/`max_connections`；测试夹具 `fixture_init()`、`fixture_init_publication()`、`open_connection()`、`make_target()`、`submit_current()`、`clear_outbound()`、`break_runtime_world_session_connection_snapshots()`。
- Produces:

```c
typedef struct {
    u64 observed_publication_epoch;
    u32 open_connections;
    u32 dirty_connections;
    bool request_pending;
    bool continuation_pending;
} BreakRuntimeWorldPublishProgress;

bool break_runtime_world_session_publish_progress(
    const BreakRuntimeWorldSession *adapter,
    BreakRuntimeWorldPublishProgress *out_progress);
```

- [ ] **Step 1: 写 NULL 与空 adapter 的 RED 测试**

```c
TEST(publish_progress_reports_adapter_level_state)
{
    Fixture fixture;
    BreakRuntimeWorldPublishProgress progress;

    memset(&progress, 0xAB, sizeof(progress));
    ASSERT_FALSE(break_runtime_world_session_publish_progress(NULL, &progress));
    ASSERT_EQ(progress.observed_publication_epoch, 0u);
    ASSERT_EQ(progress.open_connections, 0u);
    ASSERT_EQ(progress.dirty_connections, 0u);
    ASSERT_FALSE(progress.request_pending);
    ASSERT_FALSE(progress.continuation_pending);

    ASSERT_TRUE(fixture_init(&fixture, 7u, 3u));
    ASSERT_TRUE(break_runtime_world_session_publish_progress(fixture.adapter, &progress));
    ASSERT_EQ(progress.observed_publication_epoch, 0u);
    ASSERT_EQ(progress.open_connections, 0u);
    ASSERT_EQ(progress.dirty_connections, 0u);
    ASSERT_FALSE(progress.request_pending);
    ASSERT_FALSE(progress.continuation_pending);
    fixture_dispose(&fixture);
}
```

- [ ] **Step 2: 写三连接未发布与 budget=1 进度迁移的 RED 测试**

```c
    ASSERT_TRUE(open_connection(&fixture, KEY_A, 7u, &epoch_a));
    ASSERT_TRUE(open_connection(&fixture, KEY_B, 7u, &epoch_b));
    ASSERT_TRUE(open_connection(&fixture, KEY_C, 7u, &epoch_c));
    ASSERT_TRUE(break_runtime_world_session_publish_progress(fixture.adapter, &progress));
    ASSERT_EQ(progress.open_connections, 3u);
    ASSERT_EQ(progress.dirty_connections, 0u);

    ASSERT_TRUE(break_world_snapshot_publication_publish(fixture.publication, s1, 7u));
    ASSERT_EQ(submit_current(&fixture, 7u, 0u), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_runtime_world_session_drain(fixture.adapter, 1u, &drained), BREAK_RUNTIME_OK);
    ASSERT_TRUE(break_runtime_world_session_publish_progress(fixture.adapter, &progress));
    ASSERT_EQ(progress.observed_publication_epoch, 1u);
    ASSERT_FALSE(progress.request_pending);
    ASSERT_TRUE(progress.continuation_pending);
    ASSERT_EQ(progress.dirty_connections, 2u); /* budget=1 只服务了一条连接 */

    for (u32 round = 0u; round < 8u && progress.continuation_pending; ++round) {
        ASSERT_EQ(break_runtime_world_session_drain(fixture.adapter, 0u, &drained),
                  BREAK_RUNTIME_OK);
        ASSERT_TRUE(break_runtime_world_session_publish_progress(fixture.adapter, &progress));
    }
    ASSERT_FALSE(progress.continuation_pending);
    ASSERT_EQ(progress.dirty_connections, 0u);
```

- [ ] **Step 3: 写只读性与逐连接一致性的 RED 测试**

```c
    break_runtime_world_session_stats(fixture.adapter, &before_stats);
    (void)break_runtime_world_session_connection_snapshots(fixture.adapter, before_snaps, 4u);
    ASSERT_TRUE(break_runtime_world_session_publish_progress(fixture.adapter, &progress));
    break_runtime_world_session_stats(fixture.adapter, &after_stats);
    (void)break_runtime_world_session_connection_snapshots(fixture.adapter, after_snaps, 4u);
    ASSERT_EQ(memcmp(&before_stats, &after_stats, sizeof(before_stats)), 0);
    ASSERT_EQ(memcmp(before_snaps, after_snaps, sizeof(before_snaps)), 0);

    dirty = 0u;
    for (usize i = 0u; i < count; ++i) dirty += after_snaps[i].publish_dirty ? 1u : 0u;
    ASSERT_EQ(progress.dirty_connections, dirty);
```

- [ ] **Step 4: 确认 RED**

```sh
cmake --build engine/build --target test_runtime_world_session -j2
```

Expected: 因结构体/函数未声明而编译失败；不得删断言消除。

- [ ] **Step 5: 最小实现**

头文件在逐连接快照之后追加结构体与声明。实现：

```c
bool break_runtime_world_session_publish_progress(
    const BreakRuntimeWorldSession *adapter,
    BreakRuntimeWorldPublishProgress *out_progress)
{
    if (!out_progress) return false;
    memset(out_progress, 0, sizeof(*out_progress));
    if (!adapter) return false;
    platform_mutex_lock((PlatformMutex *)(uintptr_t)&adapter->mutex);
    out_progress->observed_publication_epoch = adapter->publish_observed_epoch;
    out_progress->request_pending = adapter->publish_request;
    out_progress->continuation_pending = adapter->publish_continuation;
    for (usize i = 0u; i < adapter->max_connections; ++i) {
        const RuntimeWorldConnection *connection = &adapter->connections[i];
        bool dirty;
        if (connection->key == 0u) continue;
        ++out_progress->open_connections;
        dirty = connection->retry_publish ||
                connection->attempt_publication_epoch != 0u ||
                connection->attempt_target_snapshot_id != 0u ||
                connection->attempt_target_tick != 0u ||
                (adapter->publish_observed_epoch != 0u &&
                 connection->completed_publication_epoch != adapter->publish_observed_epoch &&
                 connection->terminal_publication_epoch != adapter->publish_observed_epoch);
        if (dirty) ++out_progress->dirty_connections;
    }
    platform_mutex_unlock((PlatformMutex *)(uintptr_t)&adapter->mutex);
    return true;
}
```

- [ ] **Step 6: GREEN 与回归**

```sh
cmake --build engine/build --target test_runtime_world_session -j2
./engine/build/test_runtime_world_session
```

Expected: 全绿，既有用例计数不变。

- [ ] **Step 7: 三项定向变异**

1. `dirty_connections` 恒 0 → Step 2/3 用例判红。
2. 查询内清 `request_pending`/`continuation_pending` → 只读性用例判红。
3. 在锁外分别统计连接数与脏连接数 → 一致性用例在并发下判红（若无法稳定判红，记录为“未能构造”，不得写成已判红）。

每次恢复后复跑 GREEN。

- [ ] **Step 8: ASan+UBSan 与 TSan**

```sh
cmake --build engine/build-asan --target test_runtime_world_session -j2
ASAN_OPTIONS=detect_leaks=1 UBSAN_OPTIONS=halt_on_error=1 ./engine/build-asan/test_runtime_world_session
cmake --build engine/build-tsan --target test_runtime_world_session -j2
TSAN_OPTIONS=halt_on_error=1 ./engine/build-tsan/test_runtime_world_session
```

Expected: 两者全绿，无 sanitizer/leak/race。

- [ ] **Step 9: 提交**

```sh
git diff --check
git add engine/src/runtime/runtime_world_session.h engine/src/runtime/runtime_world_session.c \
  engine/tests/test_runtime_world_session.c
git commit -m "feat(runtime): expose publish progress summary"
```

### Task 2: 文档与最终验收

**Files:**
- Modify: `docs/design/runtime_network.md`
- Modify: `docs/design/runtime_overview.md`
- Modify: `docs/Implementation_Status.md`
- Modify: `docs/cross_engine/missing_capabilities.md`

**Interfaces:**
- Consumes: Task 1 的 `BreakRuntimeWorldPublishProgress` 与函数。
- Produces: 四份文档追加；不新增生产 API。

- [ ] **Step 1: 追加四份文档**

- `runtime_network.md`：追加 2026-11-26 小节，说明摘要字段、`dirty_connections` 与逐连接快照同判据、与 `pending()` 的分工。
- `runtime_overview.md`：追加同日期小节，说明聚合统计、逐连接快照、发布进度摘要三者的分工。
- `Implementation_Status.md`：记录实际测试计数、变异结果，不预写远端。
- `missing_capabilities.md`：保留指标协议、历史采样、告警与共享 live World 等缺口。

- [ ] **Step 2: 提交**

```sh
git diff --check
git add docs
git commit -m "docs(runtime): describe publish progress summary"
```

- [ ] **Step 3: 最终 HEAD 双后端与合同**

```sh
cmake --build engine/build -j2 && ctest --test-dir engine/build --output-on-failure -j2
cmake --build engine/build-vulkan -j2 && ctest --test-dir engine/build-vulkan --output-on-failure -j2
```

记录注册、通过、条件 skip、失败与耗时。

- [ ] **Step 4: 评审、推送与收据**

独立任务评审与整分支评审后 fast-forward 推送 `HEAD:master`，监视 CI/Windows/QUIC/Proton，成功后从最新 `origin/master` 建独立收据工作区追加两份文档收据，提交 `docs(runtime): record publish progress verification` 并核验远端 SHA。
