# Runtime World Session Control Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** 用独立 Runtime bridge 将标量 World 控制可靠地交给 owner-thread World Session，同时保留连接代次、level、correlation 和背压。

**Architecture:** RuntimeBus/Queue 负责 copied control bytes；bridge 仅在 drain 调用 World Session。新增本地 connection_epoch 防同 key 重连串代，BRWC 仅增加 correlation 传递，payload 和既有 wire 不变。

**Tech Stack:** C11、RuntimeBus/Queue、BreakWorldSession、BRWC、真实 socket、CTest、ASan+UBSan、TSan。

## Global Constraints

- `runtime_core` 不依赖 ECS/网络/Snowflake；适配器编译为独立 `runtime_world_session` / `runtime_world_session_test`。
- 控制命令固定 56 字节，全部使用 control-reserved queue；生产者不调用 World，owner drain 是唯一应用入口。
- connection_epoch、level、Runtime queue generation、publication epoch 不互相替代；Runtime sequence 不映射为网络 u32 sequence。
- 不搬运 snapshot/BRWD/BRFG，不接 core_app authoritative World，不做 Runtime Coordinator 自动注册或权威合并。
- OVERLOAD 不 inline、不丢控制；pending 未清空不得 destroy；默认 fair_outbound_admission=false 行为不变。
- 所有 configure 使用 `-DBREAK_ENABLE_SNOWFLAKE=ON -DSNOWFLAKE_SOURCE_DIR=/home/timeshift/opensource/break/.worktrees/snowflake-pin-4ab761fc`。
- 遵循现有 C11/Google 风格；文档只追加带日期的小节，不重写历史收据。

---

### Task 1: BRWC correlation 兼容

**Files:**
- Modify: `engine/src/ecs/world_session.h`
- Modify: `engine/src/ecs/world_session.c`
- Test: `engine/tests/test_world_session_recovery.c`
- Test: `engine/tests/test_world_session_loopback.c`

**Interfaces:**
- Consumes: 既有 `break_net_reactor_send_correlated` 与 envelope extension。
- Produces:

```c
BreakNetSendResult break_world_session_send_control_correlated(
    BreakWorldSession *session, BreakConnectionKey connection,
    const BreakWorldSessionControl *control, u64 correlation_id);
```

- [ ] **Step 1: 写 v1/v2 correlation 失败测试**

初始 level 的旧入口必须 cid=0；新入口使用 `0xF123456789ABCDEF`，在真实 socket 的 0x400B envelope 中逐位保留，BRWC 32 字节 payload 不变。rebaseline 后新入口携带另一个高位 cid，BRWC v2 的 40 字节和 level 不变；网络 sequence 仍按每连接 u32 递增。

- [ ] **Step 2: 确认 RED**

Run:

```sh
cmake --build engine/build --target test_world_session_recovery test_world_session_loopback -j2
```

Expected: 缺少新函数声明或定义；旧入口 cid=0 断言不得删除。

- [ ] **Step 3: 实现兼容包装**

旧函数调用新函数并传 0；新函数保留全部既有 control/version/level/length 校验，只把发送改为 `break_net_reactor_send_correlated(..., correlation_id)`。不得修改 BRWC payload、registry 或 ACK/NEED_FULL 状态。

- [ ] **Step 4: GREEN、变异和 sanitizer**

Run world session/recovery/loopback、Session、bridge normal/ASan+UBSan/TSan。临时把 correlated 发送改回非 correlated，真实高位 cid 用例必须判红；恢复后全绿。记录直接计数和日志。

- [ ] **Step 5: 提交**

```sh
git add engine/src/ecs/world_session.[ch] \
  engine/tests/test_world_session_recovery.c engine/tests/test_world_session_loopback.c
git commit -m "feat(ecs): correlate world control messages"
```

### Task 2: Runtime 控制适配器

**Files:**
- Create: `engine/src/runtime/runtime_world_session.h`
- Create: `engine/src/runtime/runtime_world_session.c`
- Create: `engine/tests/test_runtime_world_session.c`
- Create: `engine/tests/test_runtime_world_session_target_contract.cmake`
- Modify: `engine/CMakeLists.txt`

**Interfaces:**
- Consumes: Task 1 correlated BRWC、RuntimeBus/Queue、World Session API。
- Produces: spec 中的 config/command/stats 类型、create/destroy/submit/close/drain/pending/connection_epoch/stats 函数。`BreakRuntimeWorldCommand` 静态断言 `sizeof == 56`。

- [ ] **Step 1: 写 create/submit/drain 失败测试**

覆盖 kind/version/56-byte 格式、默认 queue 64 全 reserved、非法 config、key 0、两个高 32 位非零 key、duplicate open、unknown close、容量失败。open drain 后查询 epoch 构造 close/ACK，A 的 ACK/NEED_FULL/close 不改变 B；旧 epoch 在同 key reopen 后返回 STALE 且不修改新连接。

- [ ] **Step 2: 写 level、correlation 与 FIFO 失败测试**

覆盖初始 level 0、相同/倒退/排队旧 level、level 7→8 后旧 ACK 不裁剪新 history、两连接独立 full/ACK。高位 u64 correlation 经 bus/queue/drain 到 BRWC 保留；cid 0 保持 uncorrelated；Runtime sequence 从 1 成功递增且与 wire sequence 无关。A1/B1/A2 交错提交和有界 drain 保持 FIFO。

- [ ] **Step 3: 确认 RED 与 target contract**

Run:

```sh
cmake --build engine/build --target test_runtime_world_session -j2
```

Expected: 新头文件/源或 API 缺失。另在 contract 中证明 adapter 不在 `runtime_core` 源列表，production/test bridge target 分离且 test 不直接编入 adapter 源。

- [ ] **Step 4: 实现命令与身份管理**

实现固定槽 connection key/epoch 表：open 时分配非零严格递增 epoch，close/reopen 不复用；rebaseline key/epoch=0、level 严格增加且保持连接 epoch。未知 epoch/level 返回 STALE，重复 open 返回 REJECTED；stateless submit 校验在 bus 前完成，状态校验只在 owner drain 完成。

- [ ] **Step 5: 实现 owned queue、统计和 close/destroy**

submit 成功后 submitted/sequence 才递增。drain 消费后释放消息并按首个非 OK 返回，out_drained 只计实际消费。`pending = submitted-drained+control_pending`。close 停止 admission 和关闭 queue；pending 非零时 destroy=false 且资源不变，清空后 unsubscribe/destroy。

- [ ] **Step 6: GREEN、变异与 focused sanitizer**

Run adapter、world session/recovery/loopback、runtime facade/bus/core、Session、bridge normal/ASan+UBSan/TSan。至少变异：忽略 connection_epoch、接受相同 level、submit 时直接调用 World、pending 非零仍 destroy；均可构建判红后恢复。复用现有 Runtime 16 MiB exact/+1 回归，不以固定 56 字节命令替代该边界。

- [ ] **Step 7: 提交**

```sh
git add engine/CMakeLists.txt engine/src/runtime/runtime_world_session.[ch] \
  engine/tests/test_runtime_world_session.c \
  engine/tests/test_runtime_world_session_target_contract.cmake
git commit -m "feat(runtime): map world session control messages"
```

### Task 3: OVERLOAD、shutdown、文档与完整验收

**Files:**
- Test: `engine/tests/test_runtime_world_session.c`
- Test: `engine/tests/test_world_session_loopback.c`
- Modify: `docs/design/runtime_message_model.md`
- Modify: `docs/design/runtime_network.md`
- Modify: `docs/design/session_protocol.md`
- Modify: `docs/design/ecs_snapshot_replication_aoi.md`
- Modify: `docs/Implementation_Status.md`
- Modify: `docs/cross_engine/missing_capabilities.md`

**Interfaces:**
- Consumes: Task 1/2 的 correlated 控制、bridge pending/close/destroy、fair admission 配置。
- Produces: 有界背压和 shutdown 证据，不改变公共签名或数据面范围。

- [ ] **Step 1: 写 queue 与 transport OVERLOAD 用例**

将 queue 填到 control capacity，submit 返回 OVERLOAD 且 World 不变；排空后以相同 cid/内容重试成功。让 reactor OUTBOUND 饱和，ACK/NEED_FULL 首次 drain 返回 OVERLOAD，随后 drain 先重试同一 control/level/epoch/cid，成功后才处理下一命令；每次 OVERLOAD 计数，applied 只计一次。

- [ ] **Step 2: 写 shutdown 和默认兼容用例**

A1/B1/A2 入队后 close，submit 返回 CLOSED，已有消息按 FIFO drain 且恰好一次；pending 非零 destroy=false 并保留全部资源，清空后 destroy=true，最后由调用方销毁 session/publication。默认 fair_outbound_admission=false 全局行为不变，显式 true 的既有双连接公平用例不变。

- [ ] **Step 3: 反向控制与回归**

临时让 pending 重试生成新 correlation 或让 destroy 忽略 pending，相关用例必须判红后恢复。运行 Runtime、World、adapter、Session、bridge、core_app network/offline/lifecycle 与 transport normal/ASan+UBSan/TSan；既有 core_app/editor Lua longjmp 限制必须单列。

- [ ] **Step 4: 追加文档**

六份文档各追加 `2026-11-25` 小节：56 字节控制布局、connection_epoch、level/correlation 分离、owner drain、pending/shutdown、默认/opt-in admission，以及仍未做的 snapshot/BRWD 数据面、Coordinator 自动注册和权威合并。保留历史收据，不预写远端结果。

- [ ] **Step 5: 提交并在最终 HEAD 跑完整双后端**

```sh
git add engine/tests/test_runtime_world_session.c \
  engine/tests/test_world_session_loopback.c docs
git commit -m "test(runtime): cover world control lifecycle"
cmake --build engine/build -j2
ctest --test-dir engine/build --output-on-failure -j2
cmake --build engine/build-vulkan -j2
ctest --test-dir engine/build-vulkan --output-on-failure -j2
```

记录注册数、执行通过、条件 skip、失败数和耗时；新文件必须先进入 HEAD 再运行 archive 契约。

- [ ] **Step 6: 独立评审、推送与收据**

完成任务与整分支评审并修复所有 Critical/Important。确认最终 HEAD 双后端、focused sanitizer 和工作树干净后推送 `HEAD:master`；核验 CI、Windows、QUIC（若触发）、Proton 和 contract，再追加远端收据。条件 skip、Proton 77 和混合 TSan 不升级为原生 GPU 或完整 sanitizer 验收。
