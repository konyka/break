# World delta wire codec 实施计划（2026-11-24）

**Goal:** 提供版本化 World delta 编解码与目标重建/hash 校验模块，供后续
session 接线与恢复协议使用。

**Contract:** `docs/superpowers/specs/2026-11-24-world-delta-wire-design.md`。

### Task 1: 编解码与重建

- [ ] 失败测试：full/delta round-trip、golden 字节、全部畸形/边界/篡改用例。
- [ ] 确认 RED（API 不存在）。
- [ ] 实现 `engine/src/ecs/world_delta_wire.{h,c}` 与
      `engine/tests/test_world_delta_wire.c`，加入构建与 CTest
      （labels `ecs;replication;wire`）。
- [ ] focused GREEN，既有 test_ecs_replication、bridge、aspect、core_app
      不回归；至少 6 项定向变异判红后恢复。
- [ ] focused ASan+UBSan/TSan，提交
      `feat(ecs): add versioned world delta wire codec`。

### Task 2: 完整验证与文档

- [ ] 补充真实多组件/多实体用例与 fuzz 入口（若仓库已有对应 fuzz 框架）。
- [ ] 完整 Vulkan/OpenGL CTest，focused sanitizer。
- [ ] 追加文档：runtime_network.md、ecs_snapshot_replication_aoi.md、
      session_protocol.md、Implementation_Status.md、
      cross_engine/missing_capabilities.md。
- [ ] 提交 `test(ecs): cover world delta wire edge cases`，任务与整分支评审后
      push master，核验 CI/Windows/QUIC/Proton 并补收据。

所有 configure 使用 `-DBREAK_ENABLE_SNOWFLAKE=ON
-DSNOWFLAKE_SOURCE_DIR=<pin 4ab761fc 检出>`；禁止 cry/game 等命名。
