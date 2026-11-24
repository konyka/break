# 复制分片重组池周期过期调度实施计划

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** 为重组池提供可选、确定性的所有者线程周期过期调度，并在分片准入前自动执行到期维护。

**Architecture:** 在现有池对象内保存调度策略和纪元，复用 `pool_expire`；不改变流路由、预算、高水位或手动 expire。默认禁用，零分配、零线程、零锁。

**Tech Stack:** C11、现有 C 测试框架、CMake/CTest、`break_replication_core`。

## Global Constraints

- 设计来源：`docs/superpowers/specs/2026-11-24-replication-expiry-scheduler-design.md`。
- 旧单流 API、池现有 API 默认行为和现有 24 项测试不变。
- 首次 tick 立即检查；后续 `now-last_tick>=interval` 才执行；回退不改纪元；长间隔只执行一次。
- `push_at` 在任何分片准入前 tick；`interval=0` 每次到期，`max_idle=0` 到期时清理全部计时流。
- disable 保留流并关闭调度；reset 保留策略但清除纪元；手动 expire 不推进纪元。
- C11、仓库/Google 命名；不读墙钟、不创建线程、不加锁、不接 session/网络。

---

### Task 1: 池内周期过期策略

**Files:**
- Modify: `engine/src/network/break_replication_fragment.h`
- Modify: `engine/src/network/break_replication_fragment.c`
- Test: `engine/tests/test_break_replication_fragment.c`
- Append: `docs/design/ecs_snapshot_replication_aoi.md`
- Append: `docs/design/runtime_asset_streaming.md`
- Append: `docs/design/runtime_hot_reload.md`
- Append: `docs/Implementation_Status.md`
- Append: `docs/cross_engine/missing_capabilities.md`

**Interfaces:**

```c
void break_replication_reassembly_pool_set_expiry_schedule(
    BreakReplicationReassemblyPool *pool,
    uint64_t interval, uint64_t max_idle);
void break_replication_reassembly_pool_disable_expiry_schedule(
    BreakReplicationReassemblyPool *pool);
size_t break_replication_reassembly_pool_tick(
    BreakReplicationReassemblyPool *pool, uint64_t now);
```

- [ ] **Step 1: 写四组失败测试**

新增 `reassembly_pool_expiry_schedule_honors_interval_and_activity`：set(10,5)，delta 1 在 t=100 开始；t=104 完全重复刷新；t=109 tick 因调度间隔未到返回 0；t=110 tick 到期且 idle=6，返回 1 并清空 pending。

新增 `reassembly_pool_expiry_schedule_runs_before_admission_and_survives_reset`：容量 1、set(10,5)，delta 10 在 t=100 开始，delta 11 在 t=105 为 OVER_LIMIT；t=110 重试 delta 11 时先驱逐 delta 10，再返回 COMPLETE/INCOMPLETE（由测试分片数决定）且 completed id 正确。随后加入一个未完成流并 reset；断言 pending 清零，reset 后第一次 tick 不等 interval，策略仍能驱逐之后创建的计时流。

新增 `reassembly_pool_expiry_schedule_zero_disable_and_reenable`：set(0,0) 时新流在下一次同时间 tick 被驱逐；disable 后 tick 大时间值返回 0 且 pending 不变；重新 set(100,5) 后第一次 tick 立即按既有 last_activity 驱逐，而不是等待 100。

新增 `reassembly_pool_expiry_schedule_clock_rollback_and_single_pass`：set(10,5)，t=100 开始两个流，t=50 tick 返回 0 且不清流，t=109 不触发，t=110 一次返回两个驱逐；再验证很长间隔只调用一次 expire，通过重复刷新一个流使“若错误 catch-up 就会再次驱逐”的情形可区分。

- [ ] **Step 2: 确认 RED**

Run: `cmake --build engine/build --target test_break_replication_fragment -j8`
Expected: 缺少三个调度 API 导致编译失败。

- [ ] **Step 3: 最小实现调度字段和入口**

池增加 enabled、interval、max_idle、last_tick、tick_initialized。实现 set/disable/tick；第一次 tick 设置纪元并立即 expire，回退不改纪元，到期只执行一次并记录 now。`push_at` 在校验与路由前调用 `(void)break_replication_reassembly_pool_tick(pool, now)`。reset 清 tick_initialized/last_tick，保留 enabled/interval/max_idle；disable 清 enabled 和纪元但不清流。

- [ ] **Step 4: 确认 focused GREEN 和旧行为**

Run: `./engine/build/test_break_replication_fragment`
Expected: 新 4 项与旧 24 项全部通过，共 28/28。

- [ ] **Step 5: 定向变异**

逐一临时修改并确认测试行为判红后恢复：首次 tick 不立即执行、`>=` 改 `>`、push 在准入后维护、回退按无符号差值、disable 后仍 tick、reset 丢失策略、reset 保留旧纪元、长间隔循环 catch-up。`-Werror` 下用 `(void)` 避免 unused buildfail，buildfail 不算判红。

- [ ] **Step 6: 完整和 sanitizer 验证**

```bash
cmake --build engine/build -j8
ctest --test-dir engine/build -j8 --timeout 120 --output-on-failure
cmake -S engine -B engine/build-gl -DCMAKE_BUILD_TYPE=Debug -DENGINE_ENABLE_WAYLAND=ON -DENGINE_RHI_BACKEND=opengl
cmake --build engine/build-gl -j8
ctest --test-dir engine/build-gl -j8 --timeout 120 --output-on-failure
cmake -S engine -B engine/build-asan -DCMAKE_BUILD_TYPE=Debug -DENGINE_ENABLE_WAYLAND=ON -DENGINE_USE_ASAN=ON
cmake --build engine/build-asan --target test_break_replication_fragment -j8
./engine/build-asan/test_break_replication_fragment
cmake -S engine -B engine/build-tsan -DCMAKE_BUILD_TYPE=Debug -DENGINE_ENABLE_WAYLAND=ON -DENGINE_RHI_BACKEND=opengl -DENGINE_USE_TSAN=ON
cmake --build engine/build-tsan --target test_break_replication_fragment -j8
./engine/build-tsan/test_break_replication_fragment
```

Expected: 完整套件零失败，既有 4 个平台条件 skip 单列；focused sanitizer 28/28。不得声称完整 sanitizer suite、真实网络或 session 验收。

- [ ] **Step 7: 文档、提交、评审与推送**

在五份文档末尾追加 2026-11-24 小节，记录契约、RED/GREEN、变异和验证；把“周期调度器”从本项剩余缺口移除，保留“应用必须 tick；无后台线程；session/网络与真实验收未做”。提交：

```bash
git add engine/src/network/break_replication_fragment.{h,c} engine/tests/test_break_replication_fragment.c docs
git commit -m "feat(replication): schedule pooled fragment expiry"
```

独立 reviewer 同时判定 spec compliance 与 quality，整分支再审查；修复发现项后 `git push origin HEAD:master`。用完整 SHA 核验 CI、windows-d3d12、Proton 上游 run-id，必要时 QUIC/arm64，再单独追加远端收据。
