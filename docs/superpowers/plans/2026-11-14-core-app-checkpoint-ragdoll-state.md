# core_app checkpoint：布娃娃运行态

## 背景

`runtime_N.bin` 版本 3 不保存布娃娃。R 键激活后存档，读档得到的是未激活的链条：
IK 重新接管，`ragdoll=0 owned=0`，轨迹和直跑分叉。

## 事实

- `ragdoll_activate` 用 `chain.current_pose` 建胶囊刚体：胶囊半高、刚体初始位置、
  cone-twist 锚点、`body_to_joint_pos/rot`、`local_scale` 都由激活瞬间的姿态决定。
- `DistanceConstraint` 没有 warm-start 冲量字段，约束本身无运行态。
- 激活后每 tick 的链条姿态完全由刚体状态推出（`ragdoll_write_local_trs`）。

## 方案

- 版本 4，正文 124 → 496 字节，文件 512 字节。偏移 124 起：
  - 3 个关节的激活姿态 `Mat4`（各 64 字节，按 `e[c][r]` 顺序），共 192 字节。
  - 3 块骨骼刚体，各 60 字节：position(12)、velocity(12)、orientation(16)、
    angular_velocity(12)、rest_frames(4)、body_flags(4，bit0 = sleeping)。
- flags 新增 `RAGDOLL_ACTIVE`（128），掩码 255。
- `CoreLevel` 新增 `ragdoll_pose[3]`：激活成功时记下 `chain.current_pose`。
- 读档：flag 置位时把保存的姿态写回 `chain.current_pose`，调用 `ragdoll_activate`
  重建同样的刚体与约束，再逐块覆盖刚体动态量。激活失败 → `stage=state`。
- 解码：所有浮点必须有限；激活时三块刚体的四元数长度平方需在 (0.5, 2)；
  body_flags 只允许 0/1；否则 `stage=checkpoint`。
- 已知限制：读档后刚体槽位按“动态墙 → 布娃娃”顺序分配，直跑中若动态墙晚于布娃娃
  创建，槽位顺序会不同（两者不接触，不影响当前场景）。

## TDD

- RED：`SIM_MODE=roundtrip` 新增 `ragdoll_continuation`。直跑：tick 10 按 R、
  tick 30 存档、tick 50 再按 R 收起、tick 70 退出；续跑：同样输入到 tick 30，
  tick 31 读档，收起键顺延到 tick 51，tick 71 退出。断言读档后 tick 31
  `ragdoll=1 solved=0 owned=1`，读档后 40 tick 的 ik / user 行与直跑逐字一致，
  ragdoll 收起事件也一致。
- 失败矩阵新增 `ragdoll_nan`（姿态矩阵写 NaN）、`ragdoll_quat`（置激活位但刚体
  四元数为零），期望 `stage=checkpoint`；`vehicle_*` 的长度检查改为 512。
- 变异：去掉姿态写回、去掉刚体覆盖、去掉四元数检查，各自判红。

## 验证

normal 全量；ASan/TSan 下 `test_core_app_lifecycle`；CI 与 windows-d3d12。
