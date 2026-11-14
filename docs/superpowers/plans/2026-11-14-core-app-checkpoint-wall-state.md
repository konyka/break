# Core App checkpoint：动态墙读档等价性

## 背景

文档在三处写着“仍未做：动态墙仍由标志重建”。需要先判断墙是否还有标志之外的运行态，再决定扩展存档格式还是只补证明。

## 代码事实（`engine/apps/core_app/core_app.c`）

- `app_tick_chaser`：目标进入视野且未加墙时，`break_ai_obstacle_add` 加入矩形 (1, 1, 4, 2)，`physics_body_create(..., 0.0f, true, 0u)` 建立质量为 0 的静态刚体，置 `wall_added`。
- 追踪者进入 x < 1.0、z < 1.5 后只调用 `break_ai_obstacle_remove` 并置 `wall_removed`，刚体保留，视线遮挡仍认它。
- `app_apply_state` 按 `WALL_ADDED`/`WALL_REMOVED` 执行同样的 add/remove，刚体参数相同。

静态刚体没有速度、休眠或接触累积，形状与位置固定；导航障碍只有在场/移除两种状态。因此两个标志就是墙的完整运行态，不扩展 `runtime_<g>.bin`。

## 步骤

1. 在 `test_core_app_lifecycle_roundtrip` 加 `wall_continuation`：
   - 现有 continuation（tick 90 存档、tick 91 读档）中，读档后 tick 92 的 `nav_version=2 path_current=1`，证明重建的墙在场。
   - 新增一对运行：tick 380 存档（此时墙已加入并已移除，nav_version=3），一次直跑到 tick 439，一次 tick 381 读档后跑到 tick 440；sim 行和 user 行逐字一致。
2. 变异：分别让 `app_apply_state` 跳过加墙和跳过移墙，两处都必须判红；恢复后 `cmp`。
3. 文档：把“仍未做”改为“已确认等价”，修正 Task 6 节把墙写成动态刚体的错误。
4. 全量验证后提交并推送。
