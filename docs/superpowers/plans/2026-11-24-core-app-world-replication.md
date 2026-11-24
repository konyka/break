# core_app World 复制接入实施计划（2026-11-24）

**Goal:** 以默认关闭的 `--world-replication` 在 core_app transport 中发布
BRWD 并对独立诊断 World 做 drain，保持 simulation 权威边界与默认行为。

**Contract:** `docs/superpowers/specs/2026-11-24-core-app-world-replication-design.md`。

### Task 1: 配置与 transport 生命周期

- [ ] 失败测试：help/独立选项校验、默认关闭无 aspect/world 状态、open/close、
      tick/drain、full/delta 发布、析构顺序。
- [ ] 确认 RED。
- [ ] 实现 `main.c` 选项与 `core_app_net_transport.{h,c}`：world_session、
      0x400A/0x400B handler、发布与恢复、`network_world_stats`。
- [ ] focused GREEN：`test_core_app_net_transport`、target contract、
      world session/recovery、bridge、aspect、ECS、wire 不回归。
- [ ] 至少 5 项变异判红后恢复；focused ASan+UBSan/TSan。
- [ ] 提交 `feat(core-app): add optional world replication transport`。

### Task 2: 真实 loopback、完整验证与文档

- [ ] `test_core_app_net_client` 增加 world 模式与
      `test_core_app_network.cmake` 用例：BRWD 重建 target、need_full/full、
      乱序/重复、trace 计数；移除 0x400A 的反向控制。
- [ ] 既有 offline/loopback/lifecycle 全部通过；完整 Vulkan/OpenGL；
      focused sanitizer。
- [ ] 追加文档：session_protocol.md、runtime_network.md、
      online_session_network.md、ecs_snapshot_replication_aoi.md、
      core_app_integration.md、Implementation_Status.md、
      cross_engine/missing_capabilities.md。
- [ ] 提交 `test(core-app): cover world replication loopback`，任务与整分支
      独立评审后 push master，核验 CI/Windows/QUIC/Proton 并补收据。

所有 configure 使用 `-DBREAK_ENABLE_SNOWFLAKE=ON
-DSNOWFLAKE_SOURCE_DIR=<pin 4ab761fc 检出>`；命名遵循仓库命名合同。
