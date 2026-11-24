# World Session Rebaseline Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** 为 World session 提供无分配、全连接一致的显式 level 换代，并用带 generation 的控制消息阻止旧 ACK 碰撞。

**Architecture:** 固定槽位重组池原地复位 expected base，bridge 保留连接 key 并丢弃旧 completion。World session 清理每连接旧基线/历史/attempt；初始代沿用 BRWC/v1，换代后用 BRWC/v2 携带 level。

**Tech Stack:** C11、ECS World/snapshot/delta、BRFG/BRWD/BRWC、真实 socket Session、CTest、ASan+UBSan、TSan。

## Global Constraints

- 所有新入口均为 owner-thread；换代路径不分配、不加锁、不新增线程。
- 新 level 必须非零且严格大于当前值；同一 session 只有一个 active level。
- 初始代保持 32 字节 BRWC/v1；新代使用 40 字节 BRWC/v2，0x400B outer version 范围为 1..2，BRWD/v1 不变。
- 旧 attempt/history/completion/reassembly/control 不得进入新代；full 成功前 caller World 不变，每连接 ACK 独立。
- 不做自动换级、资产加载、schema online migration、混合 level、共享 live World、权威合并、Runtime Core 映射、预测回滚或完整资产链。
- 所有 configure 使用 `-DBREAK_ENABLE_SNOWFLAKE=ON -DSNOWFLAKE_SOURCE_DIR=/home/timeshift/opensource/break/.worktrees/snowflake-pin-4ab761fc`。
- 遵循仓库现有命名与 C11/Google 风格；文档只追加带日期的新小节，不重写历史收据。

---

### Task 1: 无分配 pool/bridge epoch 复位

**Files:**
- Modify: `engine/src/network/break_replication_fragment.h`
- Modify: `engine/src/network/break_replication_fragment.c`
- Modify: `engine/src/network/break_replication_session.h`
- Modify: `engine/src/network/break_replication_session.c`
- Test: `engine/tests/test_break_replication_fragment.c`
- Test: `engine/tests/test_break_replication_session.c`

**Interfaces:**
- Consumes: 既有 pool reset、固定 slot、bridge completion FIFO 与 expiry 配置。
- Produces:

```c
void break_replication_reassembly_pool_rebaseline(
    BreakReplicationReassemblyPool *pool, uint64_t expected_base_id);
void break_replication_session_rebaseline(
    BreakReplicationSessionBridge *bridge, uint64_t expected_base_id);
```

- [ ] **Step 1: 写 pool 失败测试**

新增 `reassembly_pool_rebaseline_changes_epoch_and_resets_stream_state`：创建 base A 的池，保留一个未完成流并完成另一个高水位流；设置非默认 expiry；调用新入口到 base B。断言旧 base 返回 `BREAK_REPLICATION_REASSEMBLY_BASE_MISMATCH`，新 base 的 delta 1 可开始，pending=0，retired 高水位不拒绝新 delta，expiry 策略仍按原配置工作；NULL 调用安全。

- [ ] **Step 2: 写 bridge 失败测试**

新增 `bridge_rebaseline_preserves_keys_and_drops_old_completions`：两个连接各有未完成流，至少一个旧 completion 已入队。调用新入口后断言 key/connection_count 不变、completion count/bytes=0、pending=0、dropped-completions 增加旧队列条数；旧 base 发送/接收均拒绝，新 base 可重组。旧 completion 的 payload 由 ASan+UBSan 验证已释放。

- [ ] **Step 3: 确认 RED**

Run:

```sh
cmake --build engine/build --target test_break_replication_fragment test_break_replication_session -j2
```

Expected: 因两个新符号未声明或未定义而编译/链接失败，不计行为通过。

- [ ] **Step 4: 最小实现**

pool 先调用既有 reset，再同步写 pool 与每个固定 slot 的 expected base。bridge 遍历所有打开 pool 调用该入口，并释放全部 completion：

```c
for (size_t i = 0; i < bridge->completion_count; ++i) {
    BreakReplicationSessionCompletion *entry = bridge_completion_at(bridge, i);
    break_replication_reassembly_free(entry->payload);
    memset(entry, 0, sizeof(*entry));
}
bridge->dropped_completions += bridge->completion_count;
bridge->completion_head = bridge->completion_count = bridge->completion_bytes = 0u;
```

不得重新分配 pool、slot、connection 或 completion 数组。

- [ ] **Step 5: GREEN 与定向变异**

Run:

```sh
ctest --test-dir engine/build --output-on-failure \
  -R '^(test_break_replication_fragment|test_break_replication_session)$'
```

Expected: 两套件及新增用例全过。分别让“只改 pool expected、不改 slot expected”和“忘记释放旧 completion”成为可构建变异，确认新用例判红后恢复。

- [ ] **Step 6: 提交**

```sh
git add engine/src/network/break_replication_fragment.[ch] \
  engine/src/network/break_replication_session.[ch] \
  engine/tests/test_break_replication_fragment.c \
  engine/tests/test_break_replication_session.c
git commit -m "feat(replication): support atomic stream rebaseline"
```

### Task 2: World session 与 BRWC/v2 换代

**Files:**
- Modify: `engine/src/ecs/world_session.h`
- Modify: `engine/src/ecs/world_session.c`
- Modify: `engine/src/network/break_net_message_registry.c`
- Test: `engine/tests/test_world_session.c`
- Test: `engine/tests/test_world_session_recovery.c`
- Test: `engine/tests/test_break_session.c`

**Interfaces:**
- Consumes: Task 1 的 `break_replication_session_rebaseline`。
- Produces:

```c
#define BREAK_WORLD_SESSION_CONTROL_WIRE_SIZE_V2 40u

bool break_world_session_rebaseline(
    BreakWorldSession *session, u64 level_generation);
u64 break_world_session_level_generation(
    const BreakWorldSession *session);
```

`BreakWorldSessionControl` 增加 `u64 level_generation`；旧
`BREAK_WORLD_SESSION_CONTROL_WIRE_SIZE` 保持 32。

- [ ] **Step 1: 写换代准入和基本恢复失败测试**

在 `test_world_session.c` 覆盖：NULL/零/相同/较小 generation 均 false 且状态不变；level 7 已有 full/delta/ACK 后切到 level 8，getter 返回 8，baseline/confirmed/history/attempt 清空且 next_delta_id=1；首个新包只能 full，ACK 后才允许 delta。

新增多连接用例：A/B 共同换代，A full+ACK 后 A 可 delta，B 未 ACK 时仍只能 full，A 的 ACK 不改变 B 的 confirmed。

- [ ] **Step 2: 写迟到控制与旧 attempt 失败测试**

在 `test_world_session_recovery.c` 覆盖：旧 OVERLOAD attempt 在换代后不得续发；特意复用 delta id、tick、entity/component 使 snapshot id 相同，旧 level 的 v2 ACK 和 NEED_FULL 均 false 且新 history/force_full 不变；初始 v1 在换代后也拒绝，当前 v2 ACK 才精确裁剪 history。

增加 wire 用例：初始发送仍产生 outer/payload v1 和 32 字节；换代后产生 outer/payload v2 和 40 字节，offset 32 为 level；错误 outer version、payload version、长度、零/旧/未来 level 均拒绝。坏 full 不修改 caller World/baseline，随后正确 full 恢复；close/reopen 保持当前 level 并清连接状态。

- [ ] **Step 3: 确认 RED**

Run:

```sh
cmake --build engine/build --target \
  test_world_session test_world_session_recovery test_break_session -j2
```

Expected: 新 API、字段或 v2 常量缺失导致编译/链接 RED。

- [ ] **Step 4: 实现 BRWC 双版本**

`BreakWorldSession` 保存 initial level 与 current level。v1 仅在外层/内层 version=1、长度 32 且 current==initial 时接受，并归入 initial level。v2 要求外层/内层 version=2、长度 40、offset 32 的 level==current。发送初始手工控制允许 level=0/initial；poll 控制总写 current；换代后 level=0 或不匹配返回 `BREAK_NET_SEND_INVALID`。

registry 仅把 0x400B 的 maximum_version 改为 2，消息数量、0x400A 和其他定义不变。

- [ ] **Step 5: 实现无分配 session 换代**

有效新 generation 先计算新 stream epoch，调用 Task 1 bridge 入口，再逐连接保留 key/history 数组并清理其余状态：

```c
world_session_clear_attempt(&state->attempt);
world_session_clear_history(state);
break_world_snapshot_release(state->baseline);
break_world_snapshot_release(state->confirmed);
state->baseline = state->confirmed = NULL;
state->next_delta_id = 1u;
state->force_full = true;
state->need_full_pending = state->ack_pending = false;
state->need_full_tick_valid = false;
```

同时清 ACK/NEED_FULL 保存值与 last_need_full_tick，再更新 current level；不得重置全 session 的单调统计或释放 history 数组。

- [ ] **Step 6: GREEN、变异和 focused sanitizer**

Run:

```sh
ctest --test-dir engine/build --output-on-failure \
  -R '^(test_world_session|test_world_session_recovery|test_break_session|test_break_replication_session|test_break_replication_fragment|test_world_delta_wire|test_ecs_replication)$'
```

Expected: 全部通过。至少验证四项可构建变异并恢复：接受相同 generation、保留旧 attempt、忽略 v2 level、A 的 ACK 错误推进 B。用 `ASAN_OPTIONS=detect_leaks=1` 跑 ASan+UBSan focused，用 `TSAN_OPTIONS=halt_on_error=1` 跑同组 TSan，记录实际计数与任何既有环境限制。

- [ ] **Step 7: 提交**

```sh
git add engine/src/ecs/world_session.[ch] \
  engine/src/network/break_net_message_registry.c \
  engine/tests/test_world_session.c \
  engine/tests/test_world_session_recovery.c \
  engine/tests/test_break_session.c
git commit -m "feat(ecs): rebaseline world sessions by level"
```

### Task 3: 同 socket 换代、文档与完整验收

**Files:**
- Test: `engine/tests/test_world_session_loopback.c`
- Modify: `docs/design/session_protocol.md`
- Modify: `docs/design/runtime_network.md`
- Modify: `docs/design/online_session_network.md`
- Modify: `docs/design/ecs_snapshot_replication_aoi.md`
- Modify: `docs/Implementation_Status.md`
- Modify: `docs/cross_engine/missing_capabilities.md`

**Interfaces:**
- Consumes: Task 2 的换代 API、BRWC/v2 和 Task 1 的 epoch 复位。
- Produces: 同一 TCP 连接内 level 7→8 的真实验收与文档证据，不改变公共签名。

- [ ] **Step 1: 写真实 socket 失败用例**

新增 `world_session_same_socket_rebaselines_and_rejects_late_traffic`：AUTH 后完成 level 7 full/ACK/delta；不重建 TCP 连接，双方显式换代到 8。注入旧 epoch 反序/重复片、旧 v1 和旧 v2 ACK/NEED_FULL，断言 World/baseline/history 不变；新代 delta 在 full 前触发 NEED_FULL，新 full drain 后 snapshot id 等于新 target，ACK 后才接受新 delta。记录双方连接 key 证明没有重连。

- [ ] **Step 2: 反向控制与恢复**

先运行新用例并记录结果。临时移除 v2 level 校验或 bridge epoch 更新，要求迟到旧流量使用例失败；恢复后重跑通过并确认源码无残留 diff。不得用直接 completion 注入替代真实网络路径。

- [ ] **Step 3: 回归与最终 sanitizer**

Run focused normal 覆盖 world session/recovery/loopback、bridge、fragment/wire、Session、ECS、World delta、core_app network world/offline/lifecycle。重跑 Task 2 sanitizer 选择并加入新 loopback；TSan 若复用 core_app 离线 target，既有 Lua longjmp 环境问题必须单列，不能写成通过。

- [ ] **Step 4: 追加文档**

在六份文档各加一个 `2026-11-24` 小节，记录无分配 epoch 复位、BRWC/v1 初始兼容、BRWC/v2 40 字节布局、严格递增 generation、逐连接 full/ACK，以及明确未做的自动换级、资产、共享 live World、Runtime Core 映射、权威合并和完整资产链。保留既有收据，不预写远端结果。

- [ ] **Step 5: 提交并在最终 HEAD 跑完整双后端**

```sh
git add engine/tests/test_world_session_loopback.c docs
git commit -m "test(ecs): cover world session level rebaseline"
cmake --build engine/build -j2
ctest --test-dir engine/build --output-on-failure -j2
cmake --build engine/build-vulkan -j2
ctest --test-dir engine/build-vulkan --output-on-failure -j2
```

Expected: 两套均 0 失败，记录注册数、执行通过、既有条件 skip 和总时间；archive 契约必须读取包含全部新文件的 HEAD。

- [ ] **Step 6: 独立评审、推送和远端收据**

完成任务评审与整分支评审；修复所有 Critical/Important 并复验。确认工作树干净、最终 HEAD 双后端和 focused sanitizer 证据后推送 `HEAD:master`。核验 CI、Windows、QUIC、Proton 的实际 run-id、结论和 contract，再从最新 master 追加文档收据；Proton 77 与条件 skip 不升级为原生 GPU 通过。
