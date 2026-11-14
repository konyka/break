# core_app checkpoint：车辆物理运行态

## 背景

`runtime_N.bin`（版本 2，68 字节正文）只保存用户、追踪者、动态墙标志和物品数。
车辆底盘是 `stage_physics` 新建并预置 120 步的刚体；读档时按场景重建，所以存档时
用户坐在车里、车已开出一段距离的状态会丢失：读档后车回到出生点、`occupied=0`。
`scene_state_save` 是 `main.c` 的旧格式（相机、太阳角、全部刚体按槽位顺序），
与 core_app 的分代 checkpoint 不兼容，不直接复用。

## 方案

- `runtime_N.bin` 升到版本 3，正文 68 → 124 字节，偏移 68 起追加：
  底盘 position（12）、velocity（12）、orientation（16，4×f32）、
  angular_velocity（12）、rest_frames（4）。
- flags 新增三位：`VEHICLE_OCCUPIED`（16）、`VEHICLE_SLEEPING`（32）、
  `INTERACT_DOWN`（64，交互键按下沿状态，否则读档后同一按键会再触发一次上/下车）。
- `control`（throttle/steer/brake）不保存：`vehicle_step` 每个 tick 都由输入重写。
- 解码时全部浮点必须有限；orientation 长度平方需在 (0.5, 2)，否则 `INVALID`，
  走 `stage=checkpoint` 拒绝，当前关卡不变。版本 2 文件按版本号拒绝。
- `app_apply_state` 解析底盘句柄（失效返回 STALE → `stage=state`），写回
  position / step_start_position / velocity / orientation / angular_velocity /
  rest_frames / sleeping，以及 `vehicle.occupied` 和 `interact_was_down`。
- 状态哈希覆盖新正文，所以 roundtrip 的哈希相等断言自动覆盖车辆段。

## TDD

- RED：在 `test_core_app_lifecycle_roundtrip`（`SIM_MODE=roundtrip`）中加
  `vehicle_continuation`：同一输入序列（上车、前进、tick 60 存档）分两次运行，
  一次直跑到 100，一次在 tick 61 读档后跑到 101；断言读档后 `occupied=1`，
  且读档后 40 个 tick 的 vehicle / user 行与直跑逐字节相同。
  改前判红：读档后车辆丢失乘坐者，轨迹分叉。
- 失败矩阵新增 `vehicle_nan`（底盘 position.x 写 NaN）、`vehicle_quat`
  （orientation 全零），重算 manifest 哈希，期望 `stage=checkpoint`。
- 变异：去掉 occupied 写回、去掉 position 写回、去掉 NaN 检查、去掉四元数长度检查，
  各自判红。

## 验证

normal 全量、ASan/TSan 下 core_app lifecycle、archive 契约、CI 与 windows-d3d12。
