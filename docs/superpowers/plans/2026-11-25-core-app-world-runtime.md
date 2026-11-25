# Core App World Runtime Integration Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** 在 `--world-replication` 下让 core_app 的 open/close 和本地 ACK/NEED_FULL 经过实际 Runtime adapter，并保证 session/Bus 生命周期组合安全。

**Architecture:** transport 持有 BreakWorldSession 与 adapter；首 tick 用 rebaseline 初始化而非替换。Coordinator 先销毁 adapter，再销毁 network/session/reactor，最后关闭 net_bus；FAILED 时先 abandon 再手动回收。

**Tech Stack:** C11、BreakRuntimeWorldSession、BreakRuntimeCoordinator、BreakWorldSession、真实 socket、CTest、ASan+UBSan、TSan。

## Global Constraints

- 仅 `--world-replication` 开启时创建 adapter/subscription；默认关闭的 trace、五子系统和依赖边界不变。
- 首 tick 不得 destroy/recreate session；初始化后 adapter 借用同一有效 session。
- open/close/本地 ACK/NEED_FULL 经 adapter queue + owner drain；入站 0x400B 仍直接处理，不转成再次发 ACK。
- adapter 先于 network 销毁，session/reactor 后于 adapter，net_bus 最后关闭；FAILED 先 abandon 再手动回收。
- 不做 snapshot/BRWD 数据面、自动后续换级、共享 live World、权威合并或默认全局公平调度。
- 所有 configure 使用 `-DBREAK_ENABLE_SNOWFLAKE=ON -DSNOWFLAKE_SOURCE_DIR=/home/timeshift/opensource/break/.worktrees/snowflake-pin-4ab761fc` 和 `-DCORE_APP_ENABLE_NETWORK=ON`。
- 遵循现有 C11/Google 风格；文档只追加带日期的小节，不重写历史收据。

---

### Task 1: adapter 注册、初始化与控制路径

**Files:**
- Modify: `engine/apps/core_app/core_app.c`
- Modify: `engine/apps/core_app/core_app_net_transport.h`
- Modify: `engine/apps/core_app/core_app_net_transport.c`
- Modify: `engine/src/runtime/runtime_world_session_lifecycle.h`
- Modify: `engine/src/runtime/runtime_world_session_lifecycle.c`
- Modify: `engine/CMakeLists.txt`
- Test: `engine/tests/test_core_app_net_transport.c`
- Test: `engine/tests/test_core_app_target_contract.cmake`
- Test: `engine/tests/test_runtime_world_session.c`

**Interfaces:**
- Consumes: `BreakRuntimeWorldSession`、Coordinator、transport session 与 net_bus。
- Produces:

```c
BreakRuntimeError core_app_net_transport_world_adapter_register(
    CoreAppNetTransport *transport, BreakRuntimeBus *bus,
    BreakRuntimeCoordinator *coordinator);
BreakRuntimeWorldSession *core_app_net_transport_world_adapter(
    CoreAppNetTransport *transport);
BreakRuntimeError core_app_net_transport_world_submit(
    CoreAppNetTransport *transport,
    const BreakRuntimeWorldCommand *command, u64 correlation_id);
```

`BreakRuntimeWorldSessionLifecycle` 末尾增加可选 `on_destroy(void *user_data)`。

- [ ] **Step 1: 写默认关闭、注册和首 tick 失败测试**

world off 时 adapter/subscription 不存在且旧 trace/五子系统不变。world on 时注册真实 adapter，首 tick 前后 `CoreAppNetWorldTestView.session` 指针相同，open 可取得非零 connection_epoch；close/reopen 后旧 epoch 返回 STALE。反向恢复 destroy/recreate 必须使断言或 ASan 判红。

- [ ] **Step 2: 写控制路径与 on_destroy 失败测试**

open/ACK/NEED_FULL 在 submit 前不改变 World/BRWC，drain 后按 FIFO 各出现一次；高位 cid 保留且没有旧直接发送的重复。入站 ACK 仅裁剪本地 history。`on_destroy` 仅在成功销毁时调用一次，TIMEOUT/FAILED/abandon 不调用；network destroy TIMEOUT 后 rollback 不二次访问 adapter。

- [ ] **Step 3: 确认 RED**

Run:

```sh
cmake --build engine/build --target test_core_app_net_transport test_runtime_world_session -j2
```

Expected: 新 helper、on_destroy 或 adapter 行为缺失导致 compile/link RED。

- [ ] **Step 4: 实现注册和初始化**

首 tick 用 `break_world_session_rebaseline` 替换 destroy/recreate，level 0 直接初始化。`world_adapter_register` 在 Coordinator CREATED 时创建 adapter 并注册，失败仅销毁未注册 adapter。world off 直接 OK，不创建任何对象。

- [ ] **Step 5: 实现 open/close/控制转换和回滚**

open/close 使用 adapter submit+drain 与 connection_epoch；本地控制带原 level/delta/target/tick，保存首个 cid 供重试。入站 handler 不变。`on_destroy` 清 transport adapter 指针；正常停止 adapter 先于 network，回滚先 abandon/drain/destroy adapter，再处理 network 和 net_bus。

- [ ] **Step 6: 链接与 GREEN/变异/sanitizer**

仅在 network+Snowflake enabled 时把 `runtime_world_session` 链入 core_app 和 transport test，保持离线依赖门禁。运行 transport、runtime_world_session、core_app target/network focused normal/ASan+UBSan/TSan。至少变异：首 tick 替换 session、控制绕过 adapter、on_destroy 未清指针，均判红后恢复。

- [ ] **Step 7: 提交**

```sh
git add engine/CMakeLists.txt engine/apps/core_app/core_app.c \
  engine/apps/core_app/core_app_net_transport.[ch] \
  engine/src/runtime/runtime_world_session_lifecycle.[ch] \
  engine/tests/test_core_app_net_transport.c \
  engine/tests/test_core_app_target_contract.cmake \
  engine/tests/test_runtime_world_session.c
git commit -m "feat(core-app): register world control lifecycle"
```

### Task 2: 真实 loopback、组合关闭、文档与完整验收

**Files:**
- Test: `engine/tests/test_core_app_net_client.c`
- Test: `engine/tests/test_core_app_network.cmake`
- Test: `engine/tests/test_core_app_lifecycle.cmake`
- Test: `engine/tests/test_core_app_net_transport.c`
- Modify: `docs/design/runtime_overview.md`
- Modify: `docs/design/runtime_message_model.md`
- Modify: `docs/design/runtime_network.md`
- Modify: `docs/design/session_protocol.md`
- Modify: `docs/design/online_session_network.md`
- Modify: `docs/design/core_app_integration.md`
- Modify: `docs/Implementation_Status.md`
- Modify: `docs/cross_engine/missing_capabilities.md`

**Interfaces:**
- Consumes: Task 1 adapter 注册、submit/drain、on_destroy 与回滚。
- Produces: 真实生产控制路径、组合关闭/回滚证据，不改变 BRWD/BRWC 数据面。

- [ ] **Step 1: 强化真实 world loopback**

客户端读取服务端 ACK/NEED_FULL，验证 envelope correlation extension 非零且高位保留、每个控制只出现一次、BRWC payload/target/level 不变；服务端入站客户端控制仍按旧 uncorrelated 兼容。断言 adapter drain 前无效果，drain 后 target 一致，旧直接发送没有重复。

- [ ] **Step 2: 强化组合关闭与 FAILED 回滚**

覆盖 adapter drain TIMEOUT 阻断 network destroy，network destroy TIMEOUT 后 on_destroy 已清指针，CREATED/FAILED 回滚先 abandon/manual drain 再 network。入站 World 仍仅改变对应 diagnostic World，simulation/physics/权威 trace 不变。

- [ ] **Step 3: 反向控制与完整回归**

临时恢复首 tick 替换 session、绕过 adapter 发送或不清理 adapter 指针，相关用例必须失败或由 sanitizer 检出，恢复后通过且生产无残留变异。运行 core_app network/offline/lifecycle、Runtime/World/Session/bridge normal/ASan+UBSan/TSan，既有 Lua longjmp 限制单列。

- [ ] **Step 4: 追加文档**

七份文档各追加 `2026-11-25` 小节，记录生产 adapter 注册、首 tick 不替换、open/ACK/NEED_FULL 路径、on_destroy 回滚顺序，以及未做的 snapshot/BRWD 数据面、自动后续换级和权威合并。core_app 已有 `"network"` 与新增 World adapter 必须分开描述，不预写远端结果。

- [ ] **Step 5: 提交并在最终 HEAD 跑完整双后端**

```sh
git add engine/tests/test_core_app_net_client.c \
  engine/tests/test_core_app_network.cmake \
  engine/tests/test_core_app_lifecycle.cmake \
  engine/tests/test_core_app_net_transport.c docs
git commit -m "test(core-app): cover world adapter lifecycle"
cmake --build engine/build -j2
ctest --test-dir engine/build --output-on-failure -j2
cmake --build engine/build-vulkan -j2
ctest --test-dir engine/build-vulkan --output-on-failure -j2
```

保持 `CORE_APP_ENABLE_NETWORK=ON`，记录注册数、执行通过、条件 skip、失败数和耗时；新增文件必须先进入 HEAD 再运行 archive 契约。

- [ ] **Step 6: 独立评审、推送与收据**

完成任务与整分支评审并修复所有 Critical/Important。确认最终 HEAD 双后端、focused sanitizer 和工作树干净后推送 `HEAD:master`；核验 CI、Windows、QUIC（若触发）、Proton 和 contract，再追加远端收据。条件 skip、Proton 77 和混合 TSan 不升级为原生 GPU 或完整 sanitizer 验收。


---

## 终审集中修复约束（2026-11-25）

本轮只关闭整分支终审的 generation lifecycle 与 hooks 合同缺口，不扩大原任务范围。

- [x] 先以同 key、不同槽的 pending CLOSE→OPEN 和取消 OPEN→同 key OPEN 回归复现旧连接
  对账污染，再实现全槽 key 代际所有权：旧 OPEN/CLOSE/补偿 CLOSE 未释放前延迟新 OPEN，
  断连后仍未关闭的旧 epoch 继续占有 key；OPEN 对账同时要求 epoch 相对提交前发生变化。
- [x] 回归逐槽检查旧 key/epoch/transition/diagnostic 释放、新 epoch 独立性、diagnostic
  World 归属及 opened/closed/open_count，而非只检查表面返回值。移除全槽门禁的可构建
  变异已使两条回归判红，恢复后重新通过。
- [x] 先以 pending OPEN 期间认证、真实 voice 接收入 jitter buffer、随后拒绝并复用槽位的
  回归复现资源遗留，再让延迟拒绝复用正常断连的完整槽位释放路径，覆盖
  voice/rate/mute、clock probe、physics 和 session 状态。移除该释放的可构建变异已判红，
  恢复后重新通过。
- [x] 将 hooks 半对校验移出 transport 条件并实际构建执行 `CORE_APP_NET_TRANSPORT=0`
  用例。离线任何非 NULL 成对 hooks 明确 INVALID；两个 NULL 保持五项，transport-enabled
  空 adapter 回退五项，真实 world on 六项不变，离线不新增 concrete transport 链接。
- 最终门禁：在最终提交 HEAD 重跑完整 OpenGL/Vulkan build 与未过滤 CTest，并记录注册、执行通过、
  条件 skip、失败和耗时；命名/target/archive/config 合同、`git diff --check`、无变异残留、
  工作树干净和无后台任务作为收尾门禁。focused sanitizer 与真实 loopback 结论写入本轮
  `final-review-fix-report.md`，既有 Lua/TSan 进程限制单列，不预写远端结果。
