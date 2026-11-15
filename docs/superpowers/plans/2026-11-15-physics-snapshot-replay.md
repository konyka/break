# 物理快照与确定性回放（2026-11-15）

## 目标
`missing_capabilities.md` 第 9 节仍缺「回放」。本切片给 `PhysicsWorld` 增加进程内快照，
从快照恢复后用同样的输入重跑，结果应与原运行逐位一致，并用状态哈希验证。

## 接口（`engine/src/physics/physics.h`）
- `usize physics_snapshot_size(const PhysicsWorld *pw)`：保存当前世界需要的字节数。
- `bool physics_snapshot_save(const PhysicsWorld *pw, void *buffer, usize capacity, usize *out_size)`：
  容量不足返回 false，`*out_size` 给出所需字节数，缓冲区不写。
- `bool physics_snapshot_restore(PhysicsWorld *pw, const void *buffer, usize size)`：
  校验魔数、版本、长度和 body 数不超过容量；任何一项失败都返回 false，世界保持原样。
- `u64 physics_state_hash(const PhysicsWorld *pw)`：对每个 body 的位置、速度、朝向、
  角速度、睡眠状态做 FNV-1a，供回放比对和网络同步诊断使用。

快照是同一构建内的内存格式，不是跨版本或跨平台的线格式。回调和 post-step 钩子不进快照。

## 步骤
1. RED：`physics_snapshot_replay_is_bit_identical`、`physics_snapshot_rejects_bad_input`、
   `physics_state_hash_tracks_motion`。
2. GREEN：实现以上 4 个函数。恢复后保证后续 step 与原运行一致（包括 BVH 状态）。
3. 变异：去掉 restore 中的 body 拷贝、约束拷贝、长度校验、哈希中的速度字段，测试都必须失败。
4. 全量 ctest，追加文档，提交推送。

## Status
完成。`test_physics` 83/83。变异 23 项全部被捕获（首轮存活的世界统计和 BVH 标脏变异通过让快照在碰撞后保存、补充断言消除）。全量 ctest 401/401（`build-core-app-master`）。
