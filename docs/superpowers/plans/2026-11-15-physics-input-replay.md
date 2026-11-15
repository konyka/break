# 物理输入录制与回放文件格式（2026-11-15）

## 目标
在世界快照（`65884bb1`）之上补齐「输入录制格式」：记录施加冲量和 step，编码成固定的
小端字节格式，回放时逐步比对状态哈希，第一处分歧给出记录下标。

## 接口（`engine/src/physics/physics_replay.h`）
- `PhysicsReplayRecord`：`op`（STEP / IMPULSE）、body 句柄、3 个 f32、step 之后的状态哈希。
- `physics_replay_init(replay, storage, capacity)`：调用方提供存储，不分配内存。
- `physics_replay_impulse(replay, world, body, impulse)`：施加并记录；body 无效或存储满返回 false，世界不变。
- `physics_replay_step(replay, world, dt)`：step 并记录 step 后的哈希。
- `physics_replay_encode(replay, buf, cap, &size)`：头部 `PRPL`、版本 1、记录数，每条 32 字节小端。
- `physics_replay_decode(replay, data, size)`：校验魔数、版本、op、长度精确相等、记录数不超过容量、浮点有限；失败时 replay 不变。
- `physics_replay_run(replay, world, &divergent)`：在调用方已恢复的世界上重放，返回 OK / DIVERGED / INVALID，`divergent` 给出第一条哈希不符的 step 记录下标。

## 步骤
1. 头文件 + 返回失败的桩，RED 测试 `test_physics_replay`：录制→编码→解码→快照恢复→回放一致；篡改一个冲量值后回放报告分歧下标；坏输入逐项拒绝。
2. GREEN 实现。
3. 变异：去掉每项校验、哈希比对、小端编码字段，测试都必须失败。
4. 全量 ctest，追加文档，提交推送。

## Status
完成。`test_physics_replay` 4/4；变异 33 项全部被捕获。`test_core_app_contract_compat` 与 `test_core_app_ctest_config_contract` 用 `git archive HEAD` 配置，新文件提交前会报找不到源文件，提交后重跑通过。
