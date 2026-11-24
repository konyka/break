# World Snapshot Publication Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** 用短锁与引用计数提供安全只读 snapshot lease，并让多个 World session 连接复用同一 immutable target。

**Architecture:** 新 publication 模块只负责 current/lease/close 生命周期；World session 新增 borrowed snapshot 发布入口，旧 World API 构建 snapshot 后复用同一路径。网络、diff、渲染与音频不接触 publication 锁。

**Tech Stack:** C11、PlatformMutex、BreakWorldSnapshot、BreakWorldSession、BRFG/BRWD/BRWC、CTest、ASan+UBSan、TSan。

## Global Constraints

- publish/close 仅 owner 调用；destroy 前先 close 并停止并发 API，旧 lease 可晚于 publication 销毁释放。
- 锁内只做状态检查、retain、指针/元数据更新；不得在锁内构建、diff、编码、发送、drain、回调、渲染或处理音频。
- 新 level 不得小于 current；publication 同 level tick 严格递增；schema/tick/level/closed/epoch 准入失败不改变 current。
- session 每连接独立 full/delta、confirmed/history、ACK/NEED_FULL、OVERLOAD 和 rebaseline；不得跨连接共享可变 World。
- 不新增 wire 消息，不做 Runtime Core 映射、自动换级、资产链、权威合并、预测回滚或通用 epoch 回收。
- 所有 configure 使用 `-DBREAK_ENABLE_SNOWFLAKE=ON -DSNOWFLAKE_SOURCE_DIR=/home/timeshift/opensource/break/.worktrees/snowflake-pin-4ab761fc`。
- 遵循现有 C11/Google 风格与命名；文档只追加带日期的新小节，不重写历史收据。

---

### Task 1: 只读 snapshot publication 与 lease

**Files:**
- Create: `engine/src/ecs/world_snapshot_publication.h`
- Create: `engine/src/ecs/world_snapshot_publication.c`
- Create: `engine/tests/test_world_snapshot_publication.c`
- Modify: `engine/CMakeLists.txt`
- Test: `engine/tests/test_replication_target_contract.cmake`

**Interfaces:**
- Consumes: `BreakWorldSnapshot` retain/release/getters 与 `PlatformMutex`。
- Produces: spec 中的 `BreakWorldSnapshotPublicationConfig`、`BreakWorldSnapshotLease`、`BreakWorldSnapshotAcquireResult` 及 create/destroy/publish/acquire/close/lease_release 六个函数；签名逐字采用 spec。

- [ ] **Step 1: 注册测试并写生命周期失败用例**

新测试覆盖：create 后 EMPTY；S1 publish/acquire 的 snapshot/level/epoch；owner 发布 S2、close、destroy 后 S1 lease 字节不变；live World 后续修改不改变 S1；lease_release 后字段清零，第二次 release 为 no-op；NULL 参数返回 INVALID 或 false。

测试链接 formal `break_ecs_replication`，不得直接编入 publication.c。给 `test_replication_target_contract.cmake` 的 formal source 列表增加 `world_snapshot_publication.c`。

- [ ] **Step 2: 写准入、close/acquire 竞态失败用例**

准入覆盖错误 schema、零 tick、同 level 非递增 tick、较小 level、close 后 publish；每次失败后 acquire 仍是旧 current/epoch。高 level 允许相同 tick 和同一 snapshot 指针，初始 level 0 合法。

用真实 PlatformThread 反复执行 acquire 与 close：结果只能是 OK 且 snapshot 有效，或 CLOSED；join 后 destroy，最后释放已得 lease。不得使用固定 sleep 证明竞态，使用原子起点与有界循环。

- [ ] **Step 3: 确认 RED**

Run:

```sh
cmake -S engine -B engine/build -G Ninja \
  -DCMAKE_BUILD_TYPE=Debug -DENGINE_BUILD_TESTS=ON \
  -DENGINE_RHI_BACKEND=opengl -DCORE_APP_ENABLE_NETWORK=ON \
  -DBREAK_ENABLE_SNOWFLAKE=ON \
  -DSNOWFLAKE_SOURCE_DIR=/home/timeshift/opensource/break/.worktrees/snowflake-pin-4ab761fc
cmake --build engine/build --target test_world_snapshot_publication -j2
```

Expected: 新头文件或源文件缺失导致 configure/compile/link RED。

- [ ] **Step 4: 实现 publication 与 formal 链接**

把新源加入 `break_ecs_replication` 和 `break_ecs_replication_test`，两者 PUBLIC 链接 `Threads::Threads`。publish 先验证再在锁内 retain/swap，旧 publication 引用在锁外 release：

```c
break_world_snapshot_retain(snapshot);
old = publication->current;
publication->current = snapshot;
publication->current_level = level_generation;
publication->current_tick = break_world_snapshot_tick(snapshot);
publication->publication_epoch++;
platform_mutex_unlock(&publication->mutex);
break_world_snapshot_release(old);
```

close 在锁内设置 closed 并移出 current；acquire 在锁内检查 closed/current 后 retain。所有失败路径保持状态且不消费调用者引用。

- [ ] **Step 5: GREEN、变异与 sanitizer**

Run normal、ASan+UBSan、TSan 的 `test_world_snapshot_publication` 和 `test_replication_target_contract`，ASan 显式 `detect_leaks=1`。至少验证：漏 close 状态检查使竞态用例失败；漏 acquire retain 由旧 lease 失效断言或 sanitizer 判红；恢复后全绿。记录实际用例数，不用无法达到的 epoch 值伪造溢出测试。

- [ ] **Step 6: 提交**

```sh
git add engine/CMakeLists.txt engine/src/ecs/world_snapshot_publication.[ch] \
  engine/tests/test_world_snapshot_publication.c \
  engine/tests/test_replication_target_contract.cmake
git commit -m "feat(ecs): publish immutable world snapshots"
```

### Task 2: World session 共享 snapshot fan-out

**Files:**
- Modify: `engine/src/ecs/world_session.h`
- Modify: `engine/src/ecs/world_session.c`
- Test: `engine/tests/test_world_session.c`
- Test: `engine/tests/test_world_session_recovery.c`

**Interfaces:**
- Consumes: Task 1 的 immutable snapshot 生命周期；不依赖 publication 类型或锁。
- Produces:

```c
BreakNetSendResult break_world_session_publish_snapshot(
    BreakWorldSession *session, BreakConnectionKey connection,
    BreakWorldSnapshot *target, u64 level_generation);
```

- [ ] **Step 1: 写两连接 fan-out 失败测试**

A/B 从同一 S1 收 full 后释放调用方 lease；只有 A ACK 后，A 可用 S1→S2 delta，B 仍 full。publisher 当前到 S3 时，B 的 delta 必须仍以自己的 confirmed/newest-unacknowledged target 为 base。比较 target id/tick、每连接 history 和独立 confirmed，不能只比较全局统计。

- [ ] **Step 2: 写背压、失败原子与 rebaseline 失败测试**

A OVERLOAD 时 B 能继续，A 后续续发完全相同 attempt。错误 schema、零 tick、同 level 已有 base 时的非递增 tick、错误 level 均返回 INVALID 且 sender state 不变。level 7→8 后旧 S1 lease 仍可读，但作为新代输入返回 INVALID；A/B 都重新 full 并独立等待当前 ACK。active attempt 存在时，新旧 API 都忽略本次 target 并续发原 attempt。

- [ ] **Step 3: 确认 RED**

Run:

```sh
cmake --build engine/build --target test_world_session test_world_session_recovery -j2
```

Expected: 缺少 `break_world_session_publish_snapshot` 声明或定义。

- [ ] **Step 4: 实现统一 borrowed-target 路径**

内部 helper 接收一个 owned target 引用，所有失败路径恰好 release 一次；成功时 attempt 接管。旧 API build 后传入，新 API retain 后传入：

```c
BreakWorldSnapshot *owned = break_world_snapshot_build(world, session->schemas, tick);
if (!world_session_build_attempt_from_snapshot(session, state, owned,
                                               session->level_generation)) {
    return BREAK_NET_SEND_INVALID;
}
```

新 helper 在消耗 next_delta_id 前检查 target/schema/level/tick 和 base 单调性。full/delta/fragment/history 逻辑保持既有实现，不在 session 引入 publication 或 mutex。

- [ ] **Step 5: GREEN、变异与 focused sanitizer**

Run world session/recovery、bridge、fragment/wire、Session、ECS replication、World delta wire 和 publication focused。至少变异：忽略 target level、A ACK 错误推进 B、attempt 未保留 target 引用、错误使用 publisher current 代替连接 base；均须可构建判红后恢复。运行 ASan+UBSan（显式 leak 检测）与 TSan 同组。

- [ ] **Step 6: 提交**

```sh
git add engine/src/ecs/world_session.[ch] \
  engine/tests/test_world_session.c engine/tests/test_world_session_recovery.c
git commit -m "feat(ecs): fan out immutable world snapshots"
```

### Task 3: 双连接真实 socket、文档与完整验收

**Files:**
- Test: `engine/tests/test_world_session_loopback.c`
- Modify: `docs/design/session_protocol.md`
- Modify: `docs/design/runtime_network.md`
- Modify: `docs/design/online_session_network.md`
- Modify: `docs/design/ecs_snapshot_replication_aoi.md`
- Modify: `docs/Implementation_Status.md`
- Modify: `docs/cross_engine/missing_capabilities.md`

**Interfaces:**
- Consumes: Task 1 lease 与 Task 2 shared-snapshot 发布入口。
- Produces: 两认证连接共享 target 的真实恢复证据，不改变公共签名或 wire。

- [ ] **Step 1: 写双连接真实 socket 用例**

两个认证连接交错收到同一 S1 full；A 延迟 ACK 并触发 NEED_FULL，B 正常推进；共享 S2/S3 时各连接仍用自己的 base。验证相同 target id、独立 ACK/history、drain 前 World 不变、一个连接 OVERLOAD 不妨碍另一个。level 7→8 后旧 lease 可读但不能发布，新代两连接都 full。

- [ ] **Step 2: 反向控制与恢复**

临时删除 session 的 target level 校验或每连接 target retain，要求真实用例失败或由 sanitizer 检出；恢复后通过并确认 `engine/src` 无残留 diff。不得直接注入 completion 或用固定 sleep 代替有界 dispatch 条件。

- [ ] **Step 3: 回归与 sanitizer**

运行 publication/world session/recovery/loopback、bridge、fragment/wire、Session、ECS/ECS system/ECS replication、World delta、core_app network/offline/lifecycle 与 transport。重跑 ASan+UBSan（显式 leak 检测）和 TSan；core_app 的既有 Lua longjmp 与混合 TSan 不覆盖服务端必须单列。

- [ ] **Step 4: 追加文档**

六份文档各追加 `2026-11-25` 小节，记录短锁 acquire/replace、lease 与 close/destroy 所有权、准入规则、一次构建多连接 fan-out，以及仍不支持的共享 live World、权威合并、Runtime Core 映射和完整资产链。保留所有历史收据，不预写远端结果。

- [ ] **Step 5: 提交并在最终 HEAD 跑完整双后端**

```sh
git add engine/tests/test_world_session_loopback.c docs
git commit -m "test(ecs): cover shared snapshot fan-out"
cmake --build engine/build -j2
ctest --test-dir engine/build --output-on-failure -j2
cmake --build engine/build-vulkan -j2
ctest --test-dir engine/build-vulkan --output-on-failure -j2
```

记录注册数、执行通过、既有条件 skip、失败数和耗时。新增文件必须先进入 HEAD，再运行 archive 契约。

- [ ] **Step 6: 独立评审、推送与收据**

完成任务和整分支评审，修复全部 Critical/Important 后复验。确认最终 HEAD 双后端、focused sanitizer 和工作树状态后推送 `HEAD:master`；核验 CI、Windows、QUIC（若触发）、Proton 及 contract，再追加远端收据。条件 skip、Proton 77 和混合 TSan 不升级为原生 GPU 或完整 sanitizer 验收。
