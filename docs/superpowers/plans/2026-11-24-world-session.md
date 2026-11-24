# World session 接线与基线恢复实施计划（2026-11-24）

**Goal:** 把 BRWD 包接入 session bridge，owner 线程应用，并提供每连接基线、
ACK 裁剪与 full 回退。

**Contract:** `docs/superpowers/specs/2026-11-24-world-session-design.md`。

### Task 1: 可配置消息 ID 与接收 drain

- [ ] 失败测试：bridge 可配置消息 ID（默认 0x4009）、registry 0x400A/0x400B
      与 32/31 计数；world_session open/close、drain 才应用、拒绝路径、
      基线推进。
- [ ] 确认 RED。
- [ ] 实现 `world_session.{h,c}` 接收侧与 registry/bridge 配置项，加入构建和
      CTest（labels `ecs;replication;session;wire`）。
- [ ] focused GREEN：新测试、bridge 19/19、aspect session 12/12、
      session 43/43、wire 9/9、fragment 28/28、ECS 35/35、
      world delta wire 23/23。
- [ ] 至少 6 项变异判红后恢复；focused ASan+UBSan/TSan。
- [ ] 提交 `feat(ecs): wire world deltas into sessions`。

### Task 2: 基线恢复与真实 loopback

- [ ] need_full 限流、full 回退、ACK 裁剪、OVERLOAD 同包重试、重连清零的
      失败测试后实现。
- [ ] 真实 socket loopback：AUTH、乱序/重复 BRWD 分片、need_full/full 证据；
      移除 0x400A 注册的反向控制。
- [ ] 完整 Vulkan/OpenGL，focused sanitizer；既有 core_app 不回归。
- [ ] 追加文档：session_protocol.md、runtime_network.md、
      online_session_network.md、ecs_snapshot_replication_aoi.md、
      Implementation_Status.md、cross_engine/missing_capabilities.md。
- [ ] 提交 `test(ecs): cover world session recovery`，任务与整分支评审后
      push master，核验 CI/Windows/QUIC/Proton 并补收据。

所有 configure 使用 `-DBREAK_ENABLE_SNOWFLAKE=ON
-DSNOWFLAKE_SOURCE_DIR=<pin 4ab761fc 检出>`；命名遵循项目禁用词约定。
