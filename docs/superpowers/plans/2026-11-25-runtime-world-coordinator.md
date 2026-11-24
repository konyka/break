# Runtime World Coordinator Lifecycle Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** 用真实 Coordinator 驱动 World Session 控制桥的六阶段关闭、TIMEOUT 恢复和 adapter-only 销毁。

**Architecture:** adapter 提供 subsystem descriptor 与可选外部 hooks，通用 Coordinator 不改。drain 以真实 pending 决定 TIMEOUT，命令级拒绝不阻止最终关闭。

**Tech Stack:** C11、BreakRuntimeCoordinator、BreakRuntimeWorldSession、RuntimeBus/Queue、CTest、ASan+UBSan、TSan。

## Global Constraints

- 通用 Coordinator 和 runtime_core 不改；适配代码只加入现有 runtime_world_session target。
- 只销毁 adapter；Bus、World Session、publication 由调用方清理，不虚构 adapter worker。
- pending 非零或 transport OVERLOAD 才 TIMEOUT；已消费的 STALE/INVALID/REJECTED/CLOSED 不得造成永久停机。
- 不做 snapshot/BRWD 数据面、core_app authoritative World、共享 live World 或权威合并。
- 所有 configure 使用 `-DBREAK_ENABLE_SNOWFLAKE=ON -DSNOWFLAKE_SOURCE_DIR=/home/timeshift/opensource/break/.worktrees/snowflake-pin-4ab761fc`。
- 遵循 C11/Google 风格与现有命名；文档只追加带日期的小节，不改写历史收据。

---

### Task 1: subsystem 注册与正常六阶段关闭

**Files:**
- Create: `engine/src/runtime/runtime_world_session_lifecycle.h`
- Create: `engine/src/runtime/runtime_world_session_lifecycle.c`
- Modify: `engine/src/runtime/runtime_world_session.h`
- Modify: `engine/CMakeLists.txt`
- Test: `engine/tests/test_runtime_world_session.c`
- Test: `engine/tests/test_runtime_world_session_target_contract.cmake`

**Interfaces:**
- Consumes: `BreakRuntimeCoordinator`、`BreakRuntimeWorldSession` 的 close/drain/pending/destroy。
- Produces: spec 中的 `BreakRuntimeWorldSessionLifecycle` 与 `break_runtime_world_session_register_subsystem` 精确签名。

- [ ] **Step 1: 写正常关闭失败测试**

用真实 Coordinator、adapter、direct 与外部 Bus 命令注册 subsystem。记录六阶段调用顺序而非替换实现；stop 后要求 STOPPED、命令恰好应用一次、adapter 已释放，Bus/session/publication 仍可查询并由调用方销毁。另测 adapter 已关闭或 Coordinator 非 CREATED 时 REJECTED，且原状态不变。

- [ ] **Step 2: 确认 RED**

Run:

```sh
cmake --build engine/build --target test_runtime_world_session -j2
```

Expected: 新 lifecycle 头/源或注册函数缺失；不得用手工 close/drain/destroy 代替 Coordinator。

- [ ] **Step 3: 实现 descriptor 与六阶段**

注册时复制 lifecycle，默认 budget=32、NULL hooks=no-op。stop_admission/close_queues 共用幂等 close；stop_producers/join 调外部 hook；drain 按真实 pending 返回 OK/TIMEOUT/其他错误；destroy 仅在 pending=0 时调用 adapter destroy，false 映射 TIMEOUT。

- [ ] **Step 4: GREEN、变异与 focused sanitizer**

运行 adapter、Runtime Core、World、Session、bridge normal/ASan+UBSan/TSan。变异提前 destroy 或重复 close/unsubscribe，正常顺序用例必须判红后恢复。验证 target contract 仍禁止 runtime_core 依赖 ECS/网络。

- [ ] **Step 5: 提交**

```sh
git add engine/CMakeLists.txt engine/src/runtime/runtime_world_session.[ch] \
  engine/src/runtime/runtime_world_session_lifecycle.[ch] \
  engine/tests/test_runtime_world_session.c \
  engine/tests/test_runtime_world_session_target_contract.cmake
git commit -m "feat(runtime): bind world control lifecycle"
```

### Task 2: TIMEOUT 恢复、外部 join、文档与完整验收

**Files:**
- Test: `engine/tests/test_runtime_world_session.c`
- Modify: `docs/design/runtime_overview.md`
- Modify: `docs/design/runtime_message_model.md`
- Modify: `docs/design/runtime_network.md`
- Modify: `docs/design/session_protocol.md`
- Modify: `docs/Implementation_Status.md`
- Modify: `docs/cross_engine/missing_capabilities.md`

**Interfaces:**
- Consumes: Task 1 的 subsystem 注册和真实 pending/destroy。
- Produces: drain/join TIMEOUT 精确恢复证据，不改变通用 Coordinator。

- [ ] **Step 1: 写有界 drain 恢复用例**

budget 小于排队数，首次 stop 返回 TIMEOUT/DRAINING，join/destroy 未发生；后续 stop 只恢复 drain，直到 pending=0 后 join/destroy。不得重新 stop_admission/close。

- [ ] **Step 2: 写 transport 与终态恢复用例**

饱和 outbound 前排高位 cid ACK、后排 NEED_FULL，首次形成 control_pending 和 TIMEOUT；连续重试保持 control/level/epoch/cid，解除后 applied 只一次。另在 pending 后关闭 transport，CLOSED 清 pending并计 rejected，后续 queue 项仍 drain，最终 STOPPED 而非永久 TIMEOUT。

- [ ] **Step 3: 写外部生产者和 join TIMEOUT 用例**

direct 与外部 Bus 混合提交，close 前全部恰好一次；close 后 queue CLOSED 不增加 pending，退订后 delivered=0。join 首次 TIMEOUT 保持 STOPPING，重试仅恢复 join 并恰好 destroy 一次。分别覆盖“仅 queue 非零”和“queue+control_pending 非零”，重复 stop 不重复 callback。

- [ ] **Step 4: 反向控制与回归**

分别变异：STALE 永久 TIMEOUT、pending 未清就 destroy、join 重试重复 destroy；相关用例必须判红后恢复。运行 Runtime、World、adapter、Session、bridge、core_app focused normal/ASan+UBSan/TSan，既有 Lua longjmp 和 editor/core_app 进程限制单列。

- [ ] **Step 5: 追加文档**

六份文档各追加 `2026-11-25` 小节，记录六阶段、pending 与 TIMEOUT、外部 join、adapter-only 销毁，以及未做的数据面和权威合并。追加说明 core_app 已有 `"network"` subsystem 注册，旧描述不再代表当前缺失；不得把该事实写成 World adapter 已注册。

- [ ] **Step 6: 提交并在最终 HEAD 跑完整双后端**

```sh
git add engine/tests/test_runtime_world_session.c docs
git commit -m "test(runtime): cover world control shutdown retries"
cmake --build engine/build -j2
ctest --test-dir engine/build --output-on-failure -j2
cmake --build engine/build-vulkan -j2
ctest --test-dir engine/build-vulkan --output-on-failure -j2
```

记录注册数、执行通过、条件 skip、失败数和耗时；新增 lifecycle 文件必须已进入 HEAD 再运行 archive 契约。

- [ ] **Step 7: 独立评审、推送与收据**

完成任务和整分支评审，修复所有 Critical/Important 后复验。确认最终 HEAD 双后端、focused sanitizer 和工作树干净后推送 `HEAD:master`；核验 CI、Windows、QUIC（若触发）、Proton 和 contract，再追加远端收据。条件 skip、Proton 77 和混合 TSan 不升级为原生 GPU 或完整 sanitizer 验收。
