# 复制分片多 delta 并发重组池实施计划

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** 在不改变旧单流重组器语义的前提下，提供有界、可过期、可识别乱序完成 delta 的多流重组池。

**Architecture:** 新 `BreakReplicationReassemblyPool` 与旧类型同在 `break_replication_fragment.{h,c}`，每个槽复用现有单流逻辑。池按 `delta_id` 路由，以共享负载预算和已退出高水位约束新流；不引入线程、锁或网络依赖。

**Tech Stack:** C11、现有 C 测试框架、CMake/CTest、`break_replication_core`。

## Global Constraints

- 设计唯一来源：`docs/superpowers/specs/2026-11-23-replication-reassembly-pool-design.md`。
- 旧 `BreakReplicationReassembler` 的 API、单流取代语义和现有 15 项测试保持不变。
- `stream_capacity` 为 1..64，`max_pending_bytes` 为 1..`BREAK_REPLICATION_MAX_REASSEMBLY_SIZE`；不新增结果枚举。
- 所有新 API 为所有者线程语义；不读墙钟、不创建线程、不加锁、不接 session/网络。
- 遵循仓库现有 C11/Google 命名与格式；禁止引入外部引擎前缀和禁用产品用词。
- 每个任务先确认 RED，再实现到 GREEN；最终做定向变异、完整 Vulkan/OpenGL、项目选项 ASan+UBSan/TSan、文档与独立评审。

---

### Task 1: 池生命周期与多 delta 交织完成

**Files:**
- Modify: `engine/src/network/break_replication_fragment.h`
- Modify: `engine/src/network/break_replication_fragment.c`
- Test: `engine/tests/test_break_replication_fragment.c`

**Interfaces:**
- Consumes: 现有 `BreakReplicationFragment`、`BreakReplicationReassemblyResult` 和 `break_replication_reassembly_free`。
- Produces:

```c
#define BREAK_REPLICATION_REASSEMBLY_POOL_MAX_STREAMS 64u
typedef struct BreakReplicationReassemblyPool BreakReplicationReassemblyPool;
BreakReplicationReassemblyPool *break_replication_reassembly_pool_create(
    uint64_t expected_base_id, size_t stream_capacity, size_t max_pending_bytes);
void break_replication_reassembly_pool_destroy(BreakReplicationReassemblyPool *pool);
BreakReplicationReassemblyResult break_replication_reassembly_pool_push_at(
    BreakReplicationReassemblyPool *pool, const BreakReplicationFragment *fragment,
    uint64_t now, uint64_t *completed_delta_id,
    uint8_t **payload, size_t *payload_size);
size_t break_replication_reassembly_pool_pending_streams(
    const BreakReplicationReassemblyPool *pool);
size_t break_replication_reassembly_pool_pending_bytes(
    const BreakReplicationReassemblyPool *pool);
```

- [ ] **Step 1: 写生命周期和交织完成失败测试**

新增 `reassembly_pool_validates_configuration_and_null_calls`：断言容量 0/65、预算 0/`BREAK_REPLICATION_MAX_REASSEMBLY_SIZE+1` 创建为 NULL；合法创建后两个 pending 查询为 0；NULL 池查询为 0、push 返回 `INVALID`，且三个可选输出被清零；destroy(NULL) 安全。

新增 `reassembly_pool_reassembles_three_interleaved_deltas`：用 `break_replication_fragment_payload` 分别创建 delta 10、11、12，每个至少 3 个分片。按 `[10.0,11.0,12.0,11.1,10.1,12.1,12.2,10.2,11.2]` 推送；前八项中完成项的 `completed_delta_id` 与 payload 必须对应该 delta，最后三项完成顺序由分片数决定但每个结果都逐字节匹配。明确断言任意时刻 pending 流数等于已见未完成 delta 数，三个不同 delta 可同时在池内。至少一次在较新 delta 已活跃时推送较旧 delta，证明不会取代。

核心断言形式：

```c
ASSERT_EQ(break_replication_reassembly_pool_push_at(
              pool, &fragments10[0], 100u, &completed_id, &assembled, &assembled_size),
          BREAK_REPLICATION_REASSEMBLY_INCOMPLETE);
ASSERT_EQ(break_replication_reassembly_pool_push_at(
              pool, &fragments11[0], 101u, &completed_id, &assembled, &assembled_size),
          BREAK_REPLICATION_REASSEMBLY_INCOMPLETE);
ASSERT_EQ(break_replication_reassembly_pool_pending_streams(pool), 2u);
```

- [ ] **Step 2: 确认 RED**

Run: `cmake --build engine/build --target test_break_replication_fragment -j8`
Expected: 编译失败，缺少 `BreakReplicationReassemblyPool` 和池 API。

- [ ] **Step 3: 最小实现池存储、路由和完成回收**

在同一 `.c` 内定义固定槽数组；槽持有内嵌单流重组器、`delta_id` 与 active 标记。create 用 `calloc` 分配一次槽数组并初始化每槽 `expected_base_id`；销毁逐槽调用现有 `clear_reassembly`。push 先清零输出并复用现有分片校验，再按 delta 找槽；新 delta 使用空槽，COMPLETE 时记录 id、回收槽。此任务先实现 create 配置检查和基本 pending 查询，不添加隐式取代。

- [ ] **Step 4: 确认 GREEN 与旧行为**

Run: `./engine/build/test_break_replication_fragment`
Expected: 新 2 项与旧 15 项全部通过。

- [ ] **Step 5: 提交任务切片**

```bash
git add engine/src/network/break_replication_fragment.{h,c} engine/tests/test_break_replication_fragment.c
git commit -m "feat(replication): interleave fragment streams in a bounded pool"
```

### Task 2: 满槽、共享负载预算与完成高水位

**Files:**
- Modify: `engine/src/network/break_replication_fragment.c`
- Modify: `engine/src/network/break_replication_fragment.h`（只补契约注释）
- Test: `engine/tests/test_break_replication_fragment.c`

**Interfaces:**
- Consumes: Task 1 的池 API 和单流 `push_at`。
- Produces: `OVER_LIMIT` 的满槽/共享预算语义、`completed_delta_id` 的乱序完成高水位规则；公共签名不变。

- [ ] **Step 1: 写满槽失败原子测试**

新增 `reassembly_pool_capacity_rejection_preserves_active_streams`：容量 2 的池让 delta 10、11 各保留一个未完成流；delta 12 返回 `OVER_LIMIT`，输出清零，pending 流数和字节不变；随后 delta 10、11 都能完成。完成一个槽后 delta 12 可开始。新流严格小于最大已完成 delta 时返回 `CONFLICT`；等于最大已完成 delta 可按单流规则重新开始；活跃较旧流在较新流完成后仍可完成。

- [ ] **Step 2: 写共享预算测试**

新增 `reassembly_pool_enforces_one_shared_payload_budget`：创建容量 3、预算等于两个分片负载之和的池；第一流占一部分后，第二流追加会超过预算的分片返回 `OVER_LIMIT` 且状态不变；完全相同重复分片仍返回 `DUPLICATE` 而不误算新预算；释放/完成一个流后，之前超预算的新流可接受。另测活跃流追加方向的预算拒绝，不能只在新流 start 路径检查。

```c
ASSERT_EQ(break_replication_reassembly_pool_pending_bytes(pool), first_size);
ASSERT_EQ(break_replication_reassembly_pool_push_at(
              pool, &over_budget, 110u, &id, &bytes, &size),
          BREAK_REPLICATION_REASSEMBLY_OVER_LIMIT);
ASSERT_EQ(bytes, NULL);
ASSERT_EQ(size, 0u);
ASSERT_EQ(break_replication_reassembly_pool_pending_bytes(pool), first_size);
```

- [ ] **Step 3: 确认 RED**

Run: `cmake --build engine/build --target test_break_replication_fragment -j8 && ./engine/build/test_break_replication_fragment`
Expected: 编译成功，新断言因无共享预算/高水位或错误容量行为而失败。

- [ ] **Step 4: 实现统一预算预检和已退出高水位**

池保存总 pending 字节、预算和 retired high-water。新流与活跃槽的新分片都按实际新增负载检查；已接收下标、fragment_count 冲突等情况交给单流逻辑，保证重复不被预算误拒。COMPLETE 时扣减槽 pending、回收并推进 high-water；新流严格小于 high-water 时返回 CONFLICT。拒绝路径不得修改槽或计数。

- [ ] **Step 5: 确认 GREEN**

Run: `./engine/build/test_break_replication_fragment`
Expected: 所有旧测试与 Task 1/2 新测试通过。

- [ ] **Step 6: 提交任务切片**

```bash
git add engine/src/network/break_replication_fragment.{h,c} engine/tests/test_break_replication_fragment.c
git commit -m "feat(replication): bound pooled reassembly memory"
```

### Task 3: 逐流过期、复位、变异和交付验证

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
- Produces:

```c
size_t break_replication_reassembly_pool_expire(
    BreakReplicationReassemblyPool *pool, uint64_t now, uint64_t max_idle);
void break_replication_reassembly_pool_reset(BreakReplicationReassemblyPool *pool);
```

- [ ] **Step 1: 写逐流过期与复位失败测试**

新增 `reassembly_pool_expires_each_stream_and_keeps_retirement_high_water`：三个计时流有不同活动时间；一次 expire 只清理到期者并返回准确数量；相同重复只刷新自己的槽，CHECKSUM_MISMATCH/BASE_MISMATCH/CONFLICT 不刷新；时钟回退不刷新为巨额空闲；`max_idle=0` 清理全部计时流。较新流过期的同时，活跃较旧流仍能完成；已过期高水位拒绝更旧的新流，等于该 id 的迟到分片可重新开始。

新增 `reassembly_pool_reset_matches_a_fresh_pool`：混合活跃流、高水位和 pending 字节后 reset，与同配置新池对同一输入序列的结果、输出、pending 计数一致；NULL reset/expire 安全。

- [ ] **Step 2: 确认 RED**

Run: `cmake --build engine/build --target test_break_replication_fragment -j8`
Expected: 缺少 pool expire/reset 定义导致链接失败，或新增行为断言失败。

- [ ] **Step 3: 实现 expire 和 reset**

逐槽调用现有 `break_replication_reassembler_expire`，成功时扣减该槽 pending、回收并推进 retired high-water；遍历所有槽而不是首个命中后返回。reset 清理所有槽、计数和 high-water，保留配置。

- [ ] **Step 4: 确认 focused GREEN 与定向变异**

Run: `./engine/build/test_break_replication_fragment`
Expected: 全部通过。

逐一临时变异并确认测试判红，再恢复：路由到错误槽、满槽覆盖、漏写 completed id、共享预算不累计、重复重复计预算、expire 只处理首槽、过期不推进 high-water、reset 漏清 pending。若删除代码触发 `-Werror` unused，使用 `(void)` 保持可编译；buildfail 不算判红。

- [ ] **Step 5: 运行完整与 sanitizer 验证**

```bash
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

Expected: 完整套件零失败；既有 4 个平台条件 skip 单列；focused sanitizer 全通过。不得把本项结果扩大到真实网络或生产服务验收。

- [ ] **Step 6: 追加文档并自审**

只在上述文档末尾追加 2026-11-23 小节，记录 API、预算/高水位/过期契约、测试数量、变异与验证证据；把“多 delta 并发重组”从未实现项移除，保留 session/网络接线和周期调度器为未完成。检查 spec/plan 无占位符、签名一致，旧文档不被覆盖。

- [ ] **Step 7: 独立评审、提交和远端核验**

先生成任务 diff，由独立 reviewer 同时判定 spec compliance 与 quality；修复 Critical/Important 和确认的 spec 缺口，再提交：

```bash
git add engine/src/network/break_replication_fragment.{h,c} engine/tests/test_break_replication_fragment.c docs
git commit -m "feat(replication): expire pooled fragment streams"
git push origin HEAD:master
```

推送后用完整 SHA 核验 CI、windows-d3d12、Proton 上游 run-id；必要时查 QUIC/arm64。另以一次文档收据提交记录远端结果，收据提交自身不再追加收据。
