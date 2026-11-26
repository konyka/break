# core_app Runtime 发布接线实施计划

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** 让 `--world-replication` 下的生产 core_app 在结构屏障后把权威 World 发布为 immutable snapshot，并经 Runtime direct notice 驱动既有 adapter fanout，legacy 全量发布降为可回退开关。

**Architecture:** transport 拥有 `BreakWorldSnapshotPublication`，与 `world_authoritative`/`world_schemas` 同生命周期；每 tick 在 `net_world_update` 之后构建快照、publish、再 `submit_publish_current`，由 adapter owner drain 完成 full/delta。

**Tech Stack:** C11、core_app transport、BreakWorldSnapshot/Publication、BreakRuntimeWorldSession、CTest、ASan+UBSan、TSan。

## Global Constraints

- 只改 `engine/apps/core_app/core_app_net_transport.[ch]`、`core_app.[ch]`（如需）与对应测试；不改 Runtime/World/snapshot 库。
- world off 不创建 publication、不 submit notice、trace 与五子系统不变。
- 不新增 wire；BRWD/BRFG/BRWC、0x5753、0x5754 布局不变。
- `break_world_snapshot_publication_publish` 会拒绝：tick == 0、schema hash 不匹配、closed/epoch 耗尽、level 低于 current、同 level 且 tick 未递增。计划必须据此设计失败分支，不得假设 publish 一定成功。
- publication 必须在 adapter 之后销毁；adapter destroy TIMEOUT 时不得先销毁 publication。
- 每个手工 configure 使用 `-DBREAK_ENABLE_SNOWFLAKE=ON -DSNOWFLAKE_SOURCE_DIR=/home/timeshift/opensource/break/.worktrees/snowflake-pin-4ab761fc -DCORE_APP_ENABLE_NETWORK=ON`。
- C11/Google 风格；文档只追加 2026-11-26 小节。

---

### Task 1: publication 生命周期与 tick 发布点

**Files:**
- Modify: `engine/apps/core_app/core_app_net_transport.h`
- Modify: `engine/apps/core_app/core_app_net_transport.c`
- Test: `engine/tests/test_core_app_net_transport.c`

**Interfaces:**
- Consumes: `break_schema_hash(world_schemas)`、`break_world_snapshot_build(world_authoritative, world_schemas, tick)`、`break_world_snapshot_publication_create/publish/close/destroy`、`break_world_snapshot_release`、`break_runtime_world_session_submit_publish_current`、既有 `net_tick()`、`net_world_initialize_level()`、`net_destroy()`。
- Produces:

```c
/* CoreAppNetTransport 内新增字段 */
BreakWorldSnapshotPublication *world_publication;
bool world_use_legacy_publish;

/* CoreAppNetWorldStats 末尾追加 */
u64 snapshot_build_failures;
u64 publish_rejected;
u64 notice_overloads;

/* CoreAppNetTransportConfig 末尾追加 */
bool world_use_legacy_publish; /* default false */
```

- [ ] **Step 1: 写 world off 不创建 publication 的 RED 测试**

```c
TEST(world_publication_default_off_creates_nothing)
{
    CoreAppNetTransport *t = NULL;
    CoreAppNetTransportConfig config = test_transport_config();
    config.world_replication = false;
    ASSERT_EQ(core_app_net_transport_create(&config, &t), BREAK_RUNTIME_OK);
    ASSERT_NULL(core_app_net_transport_world_publication(t));
    ASSERT_EQ(core_app_net_transport_world_publication_epoch(t, &epoch), BREAK_RUNTIME_INVALID);
    core_app_net_transport_destroy(t);
}
```

- [ ] **Step 2: 写 world on 首 tick 发布与 epoch 递增的 RED 测试**

```c
TEST(world_publication_first_tick_publishes_and_advances)
{
    /* world_replication = true，打开一个连接，tick(1)，断言：
     * - publication 非空，publish_epoch == 1
     * - adapter publish_progress().observed_publication_epoch == 1
     * - 该连接 history_count == 1（一次 full）
     * - snapshot_build_failures/publish_rejected/notice_overloads 均为 0 */
}
```

- [ ] **Step 3: 写 build/publish 失败分支的 RED 测试**

用 `tick(0)` 触发 publish 拒绝（`tick == 0` 是 publish 的明确拒绝条件之一）：

```c
    /* tick(0) 时 build 可能成功但 publish 拒绝：publish_rejected += 1、
     * adapter 未收到 notice、连接 history_count 仍为 0、world_stats 其他计数不变 */
```

- [ ] **Step 4: 写 level rebaseline 重建 publication 的 RED 测试**

```c
    /* 先 tick 到 level 7 并发布；随后以 level 8 走 net_world_initialize_level 的 rebaseline 路径，
     * 断言：旧 publication 已 close+destroy、新 publication 的 level_generation == 8、
     * 下一个 tick 发布成功且两连接重新收到 full。 */
```

- [ ] **Step 5: 写关闭顺序的 RED 测试**

```c
    /* destroy 时：adapter 先销毁、publication 后销毁。
     * 用 adapter destroy 返回 TIMEOUT 的既有注入路径断言 publication 未被释放
     * （world_publication 仍非空、仍可 acquire）。 */
```

- [ ] **Step 6: 写 legacy 开关的 RED 测试**

```c
    /* world_use_legacy_publish = true：走 net_world_publish_slot，不 submit notice，
     * adapter publish_progress().observed_publication_epoch 保持 0，连接仍收到 full。 */
```

- [ ] **Step 7: 确认 RED**

```sh
cmake --build engine/build --target test_core_app_net_transport -j2
```

Expected: 因新字段与查询函数未声明而编译失败。

- [ ] **Step 8: 最小实现**

在 `core_app_net_transport.h` 追加三个统计字段、配置位与一个只读查询：

```c
BreakWorldSnapshotPublication *core_app_net_transport_world_publication(
    const CoreAppNetTransport *transport);
```

实现要点（按顺序）：

1. `net_world_create()` 末尾：`world_session` 成功后创建 publication，
   `schema_hash = break_schema_hash(t->world_schemas)`、`level_generation = 0`；失败返回 false 走既有回滚。
2. `net_world_initialize_level()` 的 rebaseline 成功分支：`close` + `destroy` 旧 publication，
   以新 level 重新 create；create 失败计 `world_stats.publish_rejected++` 并返回 false。
3. `net_tick()`：在 `net_world_update` 之后、`net_world_tick_drain` 之前，
   若非 legacy 且 world on 且有 open 连接：
   - `snapshot = break_world_snapshot_build(t->world_authoritative, t->world_schemas, tick)`；
     NULL → `snapshot_build_failures++`，跳过；
   - `ok = break_world_snapshot_publication_publish(t->world_publication, snapshot, level)`；
     `!ok` → `publish_rejected++`；无论成败 `break_world_snapshot_release(snapshot)`；
   - `ok` 时 `submit_publish_current(adapter, &{level,0}, 0)`；`OVERLOAD` → `notice_overloads++`；
   - legacy 分支改为调用既有 `net_world_publish_slot` 循环。
4. `net_destroy()`：既有 adapter 销毁成功之后再 `close` + `destroy` publication；
   adapter 未销毁成功时保留 publication。

- [ ] **Step 9: GREEN 与既有回归**

```sh
cmake --build engine/build --target test_core_app_net_transport test_core_app_net_client -j2
./engine/build/test_core_app_net_transport
ctest --test-dir engine/build -R '^test_core_app_network_world$' --output-on-failure
```

Expected: 新用例通过，既有 transport 与真实 loopback 仍通过。

- [ ] **Step 10: 四项定向变异**

1. 把 notice 提到 `publication_publish` 之前 → 首 tick 用例判红（adapter 拿到旧/空 lease）。
2. 删除 `break_world_snapshot_release(snapshot)` → ASan 泄漏判红。
3. 关闭时先销毁 publication → 关闭顺序用例判红。
4. world off 仍创建 publication → 默认关闭用例判红。

- [ ] **Step 11: ASan+UBSan 与 TSan**

```sh
cmake --build engine/build-asan --target test_core_app_net_transport test_core_app_net_client -j2
ASAN_OPTIONS=detect_leaks=1 UBSAN_OPTIONS=halt_on_error=1 ./engine/build-asan/test_core_app_net_transport
cmake --build engine/build-tsan --target test_core_app_net_transport test_core_app_net_client -j2
TSAN_OPTIONS=halt_on_error=1 ./engine/build-tsan/test_core_app_net_transport
```

- [ ] **Step 12: 提交**

```sh
git diff --check
git add engine/apps/core_app/core_app_net_transport.[ch] engine/tests/test_core_app_net_transport.c
git commit -m "feat(core-app): wire runtime snapshot publication"
```

### Task 2: 文档与最终验收

**Files:**
- Modify: `docs/design/core_app_integration.md`
- Modify: `docs/design/runtime_overview.md`
- Modify: `docs/design/runtime_network.md`
- Modify: `docs/Implementation_Status.md`
- Modify: `docs/cross_engine/missing_capabilities.md`

- [ ] **Step 1: 五份文档各追加 2026-11-26 小节**，说明 publication 归属、tick 顺序、legacy 回退位、失败计数，并明确仍不做权威合并/AOI/自动换级。
- [ ] **Step 2: 提交** `docs(core-app): describe runtime publish wiring`。
- [ ] **Step 3: 最终 HEAD 双后端完整 CTest**，记录注册/通过/条件 skip/失败/耗时。
- [ ] **Step 4: 评审、推送与收据**：任务与整分支评审后 fast-forward 推送，监视 CI/Windows/QUIC/Proton，成功后建收据工作区追加两份文档收据并核验 SHA。

## 执行修订（2026-11-26）

设计文档的「修订 1」把原三步拆成实际的三个提交，顺序如下：

1. `feat(ecs): report sender force_full in world session state` —— `BreakWorldSessionSenderState.force_full`，一个 RED 用例覆盖初始、NEED_FULL、全量发出、rebaseline 四种状态；同时修正一个依赖旧字段的既有用例（它在 NEED_FULL 之后沿用过期快照）。
2. `feat(runtime): gate world publish fanout on readiness and ACK wait` —— `publish_requires_ready` / `publish_waits_for_ack`、`set_publish_ready()`、`held_publication_epoch` 与快照字段；四个新用例，七项变异全部判红。
3. `feat(core-app): publish authoritative world through the runtime adapter` —— publication 生命周期、tick 发布点、单调快照 tick、三个失败计数、legacy 开关、构建失败注入；六个新用例，八项变异全部判红，真实 loopback 计数不变。

原来的 Step 4「rebaseline 重建 publication」取消：publication 以 level 0 创建后接受任何更高 level，lease 自带发布时的 level。
原来的 Step 5「关闭顺序注入」保留，实际验证方式是在 adapter destroy 返回 TIMEOUT 后断言 publication 仍可 acquire、销毁成功后为 NULL。
