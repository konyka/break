# 复制分片 session bridge 实施计划

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** 通过 `0x4009` 把 canonical 分片接入真实 session/reactor，并以每连接 pool、有界完成 FIFO 和显式 owner drain 交付完成包。

**Architecture:** `break_replication_session.{h,c}` 编入现有 `break_net` 与 `break_net_test`，依赖 `break_replication_core` 的 wire/pool，不依赖 aspect/World。宿主显式调用 open/close/tick，session handler 只重组并入队。

**Tech Stack:** C11、Snowflake `BreakNetReactor`、`BreakSessionManager`、现有 C 测试框架、CMake/CTest。

## Global Constraints

- 设计与全部 API 以 `docs/superpowers/specs/2026-11-24-replication-session-bridge-design.md` 为准。
- `0x4009`、v1、AUTHENTICATED+IDEMPOTENT、payload<=65536；registry count crypto on/off 为 30/29。
- 每连接独立 expected base/pool；总 pending 由创建配置乘积静态限制，完成队列另限条数与字节。
- handler 不调用 aspect/World；完成包只有 poll 才转移所有权。close 清理 pool 和未取 completion。
- 非 AUTH handler false 只使 session 记录 HANDLER_FAILED；本地完成队列 overflow 返回 true 并计 dropped，不覆盖旧项。
- 所有者线程，无新增线程/锁/后台维护；不接生产 core_app/editor、aspect、World delta、可靠恢复。
- 所有 normal/GL/ASan/TSan configure 都必须显式使用 `-DBREAK_ENABLE_SNOWFLAKE=ON -DSNOWFLAKE_SOURCE_DIR="$SNOWFLAKE_SOURCE_DIR"`；`SNOWFLAKE_SOURCE_DIR` 指向 pin `4ab761fc58a9d15970f295e231003c99a7d44df8` 的独立检出，不能用未固定版本或禁用 loopback。

---

### Task 1: Registry、bridge 生命周期、收发与有界完成队列

**Files:**
- Create: `engine/src/network/break_replication_session.h`
- Create: `engine/src/network/break_replication_session.c`
- Create: `engine/tests/test_break_replication_session.c`
- Modify: `engine/src/network/break_net_message_registry.h`
- Modify: `engine/src/network/break_net_message_registry.c`
- Modify: `engine/tests/test_break_session.c`
- Modify: `engine/CMakeLists.txt`

**Interfaces:** spec 中的 `BreakReplicationSessionBridgeConfig`、Stats、Completion 及以下函数全部在本任务一次实现，后续任务不新增公共签名：

```c
BreakReplicationSessionBridge *break_replication_session_bridge_create(
    const BreakReplicationSessionBridgeConfig *config);
void break_replication_session_bridge_destroy(BreakReplicationSessionBridge *bridge);
bool break_replication_session_connection_open(
    BreakReplicationSessionBridge *, BreakConnectionKey, uint64_t expected_base_id);
bool break_replication_session_connection_close(
    BreakReplicationSessionBridge *, BreakConnectionKey);
BreakNetSendResult break_replication_session_send_fragment(
    BreakReplicationSessionBridge *, BreakConnectionKey,
    const BreakReplicationFragment *fragment);
size_t break_replication_session_bridge_tick(
    BreakReplicationSessionBridge *, uint64_t now);
bool break_replication_session_handle_message(
    BreakConnectionKey, const BreakNetOwnedMessage *, void *user_data);
size_t break_replication_session_poll_completed(
    BreakReplicationSessionBridge *, BreakReplicationSessionCompletion *out,
    size_t out_capacity);
void break_replication_session_completion_release(
    BreakReplicationSessionCompletion *completion);
void break_replication_session_bridge_stats(
    const BreakReplicationSessionBridge *, BreakReplicationSessionBridgeStats *out);
```

- [ ] **Step 1: 写 registry 与 bridge 失败测试**

在 `test_break_session` 增加 `0x4009` 定义断言和 30/29 count。新测试覆盖：非法 create 配置/乘积溢出；open 非零/重复/容量、close 清理和 key reuse；两连接 expected base 隔离；两个 delta 交织、重复和冲突；completion FIFO、条数/字节/单包上限、poll ownership、close dropped；send 的未知连接/base/config 拒绝和 reactor 结果；无流量 tick 与 disable。测试 apply hook 只能在 poll 后由测试显式调用，handler 阶段计数必须为 0。

- [ ] **Step 2: 确认 RED**

Run: `cmake --build engine/build --target test_break_replication_session test_break_session -j8`
Expected: 新目标/API/消息 ID 不存在导致配置或编译失败，registry count 断言也应在可构建切片失败。

- [ ] **Step 3: 实现 registry 和 bridge**

注册 `0x4009`，更新 count。bridge 创建连接数组、completion 数组和 64 KiB scratch；open 创建 pool 并设置调度，close 释放 pool 和该连接队列项。实现严格 handler、FIFO poll/release、stats 与 send。队列满/字节不足不覆盖，payload 始终由 free API 释放。文件加入 `break_net` 源列表，使 `break_net_test` 通过现有 SOURCES 属性自动包含；新增测试链接 `break_net_test break_online`，TIMEOUT 30，labels `network;snowflake;session;replication`。

- [ ] **Step 4: 确认 focused GREEN 和回归**

```bash
./engine/build/test_break_replication_session
./engine/build/test_break_session
./engine/build/test_break_replication_wire
./engine/build/test_break_replication_fragment
```

Expected: 全部通过；旧 wire 9/9、fragment 28/28 不变。

- [ ] **Step 5: 定向变异并提交**

覆盖：消息 ID/count 错、连接路由错、completion 覆盖、queue 字节漏扣、close 不释放、send 使用错误 ID、handler 绕过队列、tick 漏连接。每项成功构建并行为判红后恢复，buildfail 不算。提交 `feat(replication): bridge fragment streams to sessions`。

### Task 2: 真实 loopback、文档和完整验收

**Files:**
- Modify: `engine/tests/test_break_replication_session.c`
- Modify: `engine/tests/test_break_session.c`（仅必要 registry/phase 补充）
- Append: `docs/design/session_protocol.md`
- Append: `docs/design/online_session_network.md`
- Append: `docs/design/runtime_network.md`
- Append: `docs/design/ecs_snapshot_replication_aoi.md`
- Append: `docs/Implementation_Status.md`
- Append: `docs/cross_engine/missing_capabilities.md`

**Interfaces:** 只使用 Task 1 API，不新增公共类型或函数。

- [ ] **Step 1: 写真实 socket loopback 测试**

复用 `test_break_session.c` 的 loopback 模式：启动真实 `BreakNetReactor`，manager 设置 AUTH handler 和 `0x4009` bridge handler；raw client 先完成 AUTH，再按乱序发送至少两个 delta 的 BRFG 分片（含完全相同重复）。服务端经 `break_session_manager_poll_adapter` 驱动，断言完成队列内容/FIFO/连接/base/delta/payload。定义测试消费计数，只有显式 `poll_completed` 后才增加；drain 前必须为 0。close 后同 key reopen 不继承旧高水位。

- [ ] **Step 2: 确认 loopback 先失败再修复**

先运行新用例，记录缺消息注册/phase/路径断言的 RED；若 Task 1 已使路径通过，则用临时禁用 `0x4009` registry 项证明该用例确实依赖真实注册，再恢复。不得把未经 socket 的 handler 直调算作 loopback。

- [ ] **Step 3: 运行完整与 sanitizer 验证**

```bash
cmake --build engine/build -j8
ctest --test-dir engine/build -j8 --timeout 120 --output-on-failure
cmake -S engine -B engine/build-gl -DCMAKE_BUILD_TYPE=Debug -DENGINE_ENABLE_WAYLAND=ON -DENGINE_RHI_BACKEND=opengl
cmake --build engine/build-gl -j8
ctest --test-dir engine/build-gl -j8 --timeout 120 --output-on-failure
cmake -S engine -B engine/build-asan -DCMAKE_BUILD_TYPE=Debug -DENGINE_ENABLE_WAYLAND=ON -DENGINE_USE_ASAN=ON
cmake --build engine/build-asan --target test_break_replication_session test_break_session test_break_replication_wire test_break_replication_fragment -j8
ctest --test-dir engine/build-asan --output-on-failure -R '^(test_break_replication_session|test_break_session|test_break_replication_wire|test_break_replication_fragment)$'
cmake -S engine -B engine/build-tsan -DCMAKE_BUILD_TYPE=Debug -DENGINE_ENABLE_WAYLAND=ON -DENGINE_RHI_BACKEND=opengl -DENGINE_USE_TSAN=ON
cmake --build engine/build-tsan --target test_break_replication_session test_break_session test_break_replication_wire test_break_replication_fragment -j8
ctest --test-dir engine/build-tsan --output-on-failure -R '^(test_break_replication_session|test_break_session|test_break_replication_wire|test_break_replication_fragment)$'
```

Expected: 完整套件零失败，既有 4 条件 skip 单列；focused sanitizer 全通过。若本机 Snowflake/QEMU 环境失败，必须先定位并区分环境，不能省略 loopback 后声称接线通过。

- [ ] **Step 4: 文档、评审和推送**

追加 2026-11-24 文档：消息表/count、API、队列/预算/所有权、真实 loopback 和验证数字；历史范围记录不改，用最新小节收口“无 session 接线”，保留生产应用、aspect、World delta、可靠恢复与完整资产链缺口。提交 `test(replication): cover session fragment loopback`。任务和整分支独立评审后 push master，核验 CI/Windows/QUIC/Proton 并写单独收据。
