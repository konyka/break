# core_app aspect 复制接入实施计划（2026-11-24）

**Goal:** 以默认关闭的 `--aspect-replication` 在 core_app transport 中启用
AOI 发送与 session drain，保持 simulation 权威边界和默认行为不变。

**Contract:** `docs/superpowers/specs/2026-11-24-core-app-aspect-replication-design.md`。

### Task 1: 配置与 transport 生命周期

- [ ] 失败测试：`--aspect-replication` 出现在 help；不带 `--network` 时报错；
      默认关闭时 transport 不创建 aspect 状态；开启后 open/close/tick/drain、
      close 清理与析构顺序正确。
- [ ] 确认 RED。
- [ ] 实现 `main.c` 选项与 `core_app_net_transport.{h,c}`：两个 store、固定
      handle、AOI、BreakAspectSession、0x4009 handler、open/close、net_tick
      drain、发送回调与 `network_aspect_stats` trace。
- [ ] focused GREEN：`test_core_app_net_transport`、`test_core_app_target_contract`
      及 bridge/aspect 既有测试不回归。
- [ ] 定向变异（不在 net_tick drain、close 不释放、open 使用错误 key、
      默认也创建 aspect、统计不计数）判红后恢复。
- [ ] focused ASan+UBSan/TSan，提交
      `feat(core-app): add optional aspect replication transport`。

### Task 2: 真实 loopback、完整验证与文档

- [ ] `test_core_app_net_client` 增加 aspect 模式与
      `test_core_app_network.cmake` 用例：AUTH 后接收 BRA1 并本地重组；
      向服务端乱序/重复发送及 schema 不匹配包；断言 trace 计数。
- [ ] 移除 0x4009 注册的反向控制，随后恢复。
- [ ] 既有 offline/loopback/lifecycle 全部通过；完整 Vulkan/OpenGL；
      focused sanitizer。
- [ ] 追加文档：session_protocol.md、online_session_network.md、
      runtime_network.md、ecs_snapshot_replication_aoi.md、core_app 文档、
      Implementation_Status.md、cross_engine/missing_capabilities.md。
      保留 World delta、inbound 到 simulation、level rebaseline、可靠恢复缺口。
- [ ] 提交 `test(core-app): cover aspect replication loopback`，任务与整分支
      独立评审后 push master，核验 CI/Windows/QUIC/Proton 并补收据。

所有 configure 使用 `-DBREAK_ENABLE_SNOWFLAKE=ON
-DSNOWFLAKE_SOURCE_DIR=<pin 4ab761fc 检出>`；新增命名遵循仓库命名合同。
