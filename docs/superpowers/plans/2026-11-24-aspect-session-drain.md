# Aspect session drain 实施计划（2026-11-24）

**Goal:** 在 owner 线程把 session bridge 的完成包 drain 到 aspect store，并把
发送侧 fragment_size 上限收窄到 BRFG/v1 数据片上限。

**Contract:** `docs/superpowers/specs/2026-11-24-aspect-session-drain-design.md`。
不新增线程/锁，不在网络回调 apply，不接生产 core_app/editor。

### Task 1: fragment_size 收窄与 drain 模块

- [ ] 写失败测试：`break_online_aspect_replication` 配置 fragment_size=65536
      返回 BREAK_RUNTIME_INVALID，65496 仍接受；新模块 open/drain/stats 行为。
- [ ] 确认 RED（新 API 未声明/未定义）。
- [ ] 修改 `break_online_aspect_replication.c` 上限为
      `BREAK_REPLICATION_WIRE_MAX_FRAGMENT_DATA_SIZE`；新增
      `break_online_aspect_session.{h,c}` 与测试，接入 `break_net` 源列表和
      CTest（labels `network;snowflake;session;replication;aspect`）。
- [ ] focused GREEN：新测试、bridge 19/19、session 43/43、wire 9/9、
      fragment 28/28、现有 aspect/online 测试不回归。
- [ ] 至少 5 项定向变异判红后恢复，ASan+UBSan/TSan focused。
- [ ] 提交 `feat(replication): drain session completions into aspects`。

### Task 2: 真实 loopback、完整验证与文档

- [ ] 真实 socket：AUTH 后由现有 aspect 发送路径产生 BRA1 分片，对端 bridge
      入队；断言 drain 前 store 无对象，drain 后对象与字段正确；schema 不匹配
      的包计入 rejected；同 key 重开不继承高水位。
- [ ] 临时禁用 0x4009 注册证明测试依赖真实注册，再恢复。
- [ ] 完整 Vulkan/OpenGL CTest，focused ASan+UBSan/TSan；记录 4 个既有条件
      skip，不把它们算作通过。
- [ ] 追加文档：session_protocol.md、online_session_network.md、
      runtime_network.md、ecs_snapshot_replication_aoi.md、
      Implementation_Status.md、cross_engine/missing_capabilities.md。
- [ ] 提交 `test(replication): cover aspect session loopback`，任务与整分支
      独立评审后 push master，核验 CI/Windows/QUIC/Proton 并补收据。
