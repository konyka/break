# 复制分片 wire codec 实施计划

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** 提供无分配、显式小端、可严格拒绝畸形输入的复制分片 wire codec。

**Architecture:** 新 `break_replication_wire.{h,c}` 编入 `break_replication_core`，复用内存 fragment 类型和结果枚举；decode 借用输入数据，不接网络。

**Tech Stack:** C11、现有 C 测试框架、CMake/CTest、`break_replication_core`。

## Global Constraints

- 设计来源：`docs/superpowers/specs/2026-11-24-replication-wire-codec-design.md`。
- 40 字节头、BRFG、v1、显式 little-endian、最大数据 65496、最大 wire payload 65536。
- 网络 delta_id 非零；count 1..1048576 且 index<count；数据非空；decode 精确消费整个输入。
- decode 不验证 FNV-1a，输出借用输入；所有失败输出清零，encode 容量/校验失败不写缓冲。
- 不新增消息 ID、session/reactor/aspect 接线、分配、线程、锁或结果枚举。

---

### Task 1: Canonical wire codec 与 focused 目标

**Files:**
- Create: `engine/src/network/break_replication_wire.h`
- Create: `engine/src/network/break_replication_wire.c`
- Create: `engine/tests/test_break_replication_wire.c`
- Modify: `engine/CMakeLists.txt`（core 源列表与 focused 测试）
- Append: `docs/design/runtime_network.md`
- Append: `docs/design/online_session_network.md`
- Append: `docs/Implementation_Status.md`
- Append: `docs/cross_engine/missing_capabilities.md`

**Interfaces:**

```c
#define BREAK_REPLICATION_WIRE_VERSION 1u
#define BREAK_REPLICATION_WIRE_HEADER_SIZE 40u
#define BREAK_REPLICATION_WIRE_MAX_FRAGMENT_COUNT 1048576u
#define BREAK_REPLICATION_WIRE_MAX_FRAGMENT_DATA_SIZE \
    (BREAK_NET_MAX_PAYLOAD_SIZE - BREAK_REPLICATION_WIRE_HEADER_SIZE)
BreakReplicationFragmentResult break_replication_wire_encoded_size(
    const BreakReplicationFragment *fragment, size_t *out_size);
BreakReplicationFragmentResult break_replication_wire_encode(
    const BreakReplicationFragment *fragment,
    uint8_t *out, size_t capacity, size_t *out_size);
BreakReplicationFragmentResult break_replication_wire_decode(
    const void *data, size_t size, BreakReplicationFragment *out_fragment);
```

- [ ] **Step 1: 先写测试和 CMake 目标**

新增 `test_break_replication_wire`，至少五组：
1. delta=1、base=2、index=3、count=4、checksum=`0x11223344`、data=`aa bb cc dd` 的 44 字节 canonical 比对；头为 `42 52 46 47 01 00 28 00`，checksum 字节为 `44 33 22 11`。
2. 现有 fragmenter 生成多片，经 encode/decode/pool 重组一致；65496 数据片成功，65497 返回 OVER_LIMIT。
3. NULL/空数据/delta0/count0/count超限/index越界/容量差一均拒绝且输出清零或缓冲保持 sentinel。
4. 对 canonical 输入每个截断长度 0..43 都拒绝；尾随、坏 magic/version/header、空数据、delta0、index/count、长度字段不符均拒绝且 out 全零。
5. decode 的 data 指针恰好为输入+40；未对齐输入地址也安全，所有标量值一致。

- [ ] **Step 2: 确认 RED**

Run: `cmake --build engine/build --target test_break_replication_wire -j8`
Expected: 目标、头或函数尚不存在而配置/编译失败。

- [ ] **Step 3: 最小实现 codec 和目标接线**

把源加入 `break_replication_core`，新增测试 executable/CTest（network;replication;fragmentation labels，TIMEOUT 20）。实现固定偏移的 get/put16/32/64，完整校验后才写输出；decode 不使用 packed struct 或未对齐整数读取。

- [ ] **Step 4: 确认 focused GREEN 与既有 fragment 回归**

```bash
./engine/build/test_break_replication_wire
./engine/build/test_break_replication_fragment
```

Expected: 新测试全通过，旧池/调度器 28/28。

- [ ] **Step 5: 定向变异**

逐一成功构建并行为判红后恢复：delta 端序反转、magic 改错、header 接受非 40、容量检查差一、decode 接受尾随、接受 delta0、decode data 偏移错误、漏 count/index 校验。buildfail 不算判红。

- [ ] **Step 6: 完整和 sanitizer 验证**

```bash
cmake --build engine/build -j8
ctest --test-dir engine/build -j8 --timeout 120 --output-on-failure
cmake -S engine -B engine/build-gl -DCMAKE_BUILD_TYPE=Debug -DENGINE_ENABLE_WAYLAND=ON -DENGINE_RHI_BACKEND=opengl
cmake --build engine/build-gl -j8
ctest --test-dir engine/build-gl -j8 --timeout 120 --output-on-failure
cmake -S engine -B engine/build-asan -DCMAKE_BUILD_TYPE=Debug -DENGINE_ENABLE_WAYLAND=ON -DENGINE_USE_ASAN=ON
cmake --build engine/build-asan --target test_break_replication_wire test_break_replication_fragment -j8
./engine/build-asan/test_break_replication_wire
./engine/build-asan/test_break_replication_fragment
cmake -S engine -B engine/build-tsan -DCMAKE_BUILD_TYPE=Debug -DENGINE_ENABLE_WAYLAND=ON -DENGINE_RHI_BACKEND=opengl -DENGINE_USE_TSAN=ON
cmake --build engine/build-tsan --target test_break_replication_wire test_break_replication_fragment -j8
./engine/build-tsan/test_break_replication_wire
./engine/build-tsan/test_break_replication_fragment
```

Expected: 完整套件零失败，既有 4 条件 skip 单列；focused sanitizer 全通过。不声称真实网络/session 或完整 sanitizer suite 验收。

- [ ] **Step 7: 文档、评审和推送**

追加 2026-11-24 文档，记录格式、接口、RED/GREEN、变异与验证；保留消息注册、session/aspect、真实网络与 World delta 协议缺口。提交 `feat(replication): add canonical fragment wire codec`。任务和整分支独立评审后 `git push origin HEAD:master`，核验 CI/Windows/Proton 并另写收据。
