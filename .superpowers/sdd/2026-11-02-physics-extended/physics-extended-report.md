# P5 fix round 1 完整修复报告

分支：`cry-wave1-physics`
基线：`5bd73fe2`
范围：agent-178 的 2 Critical、6 Important、1 Minor，全部逐项 TDD 修复；未 push。

## 交付与提交

- `63535ac7` — body/constraint generation 句柄及所有有效调用者迁移。
- `1860bb9a` — 非有限 dt/body/vehicle 输入在任何状态写入前原子拒绝。
- `4dade0fa` — cone twist 在当前 A-local 坐标系中分解和投影。
- `1775e075` — 布娃娃中途失败的完整世界快照回滚，含 tombstone generation。
- `7c065ff2` — 约束删除、稳定接触和非零约束速度的休眠一致性。
- `821076e6` — chassis 局部坐标转向、制动和有效横摆惯性。
- `cd6ad5a5` — 多 ragdoll 共享 IK 的所有权计数。
- 最终文档/报告提交见分支最后一次 `git log`。

公共 API 使用 `{index,generation}` 的 `PhysicsBodyHandle` 和 `PhysicsConstraintHandle`。BVH/Contact 的当步 slot 仍是纯内部索引，不提供旧裸 id 变更入口。Rope、cloth、soft body、destructible、ragdoll、vehicle、Lua、scene 与 main 均显式迁移。

## 每项 RED / GREEN 与测试文件

### Critical 1 — stale 身份

文件：`test_physics_identity.c`、`test_ragdoll.c`、`test_vehicle.c`、`test_character.c`、`test_rope.c`、`test_cloth.c`、`test_soft_body.c`、`test_destructible.c`、`test_script_lua.c` 及既有约束测试。

- 旧 constraint 删除复用槽和 park 后旧图绑定新 occupant：`0 passed, 2 failed`。
- 旧 ragdoll deactivate：`6 passed, 1 failed`；旧 vehicle destroy：`5 passed, 1 failed`。
- 修复后 identity `2/2`，ragdoll/vehicle `2/2` CTest；完整消费者 focused `14/14`，`engine` 目标编译通过。
- Lua 保留原数字 id ABI：首次创建仍为 1、2、3；slot 复用使用新 serial，并同时校验 serial 与 generation。Lua 回归 `25/25`。

### Critical 2 — 非有限输入

文件：`test_physics.c`、`test_vehicle.c`。

- RED：普通物理 `74 passed, 3 failed`，vehicle `6 passed, 1 failed`。
- dt、position、extent、mass、shape、pose、impulse、push 与 vehicle create/step 的 NaN/±Inf 均前置拒绝；快照和 caller 对象不变。
- GREEN：普通物理 `77/77`、vehicle `7/7`；FLT_MAX mass 与 FLT_MIN dt 对照保持有限。负有限 extent 保留 clamp。

### Important 1 — cone twist 坐标系

文件：`test_physics_cone_twist.c`。

- 旋转动态 A、双动态端和组合 swing/twist：`7 passed, 1 failed`，45° twist 未夹到 20°。
- 统一当前 A-local 相对旋转与投影后：`8/8`，并裁剪界外相对角速度。

### Important 2 — 布娃娃事务回滚

文件：`test_ragdoll.c`、`physics.c`（仅 `test_ragdoll` 编译的失败计数钩子）、`CMakeLists.txt`。

- 链接 RED：失败注入入口不存在。加入测试专用钩子后，4 组中途失败完整世界快照不相等。
- 覆盖第 1/2/3 个骨体失败和第 1/2 个约束失败；第一次创建失败无副作用。
- 直接恢复受影响 slot、count 与 `bvh_dirty`，不使用会产生二次副作用的 park 回滚。加入既有 tombstone 后，其 generation 和全部字段也恢复。
- GREEN：ragdoll `8/8`，随后共享 IK 后 `9/9`。

### Important 3/4 — 销毁、接触和速度休眠

文件：`test_physics.c`。

- RED：约束删除不醒、持续地面接触不睡、纯速度约束不醒，`77 passed, 3 failed`。
- 中间证据：接触不断将 rest 清零，且慢速墙接触将最终速度消零，导致两类相反误判。
- 统一 step 末评估，并保留碰撞前相对速度与法线：重力支撑可休眠，非支撑运动接触和纯速度修正唤醒。
- GREEN：普通物理 `80/80`，地面支撑与 0.04 m/s 穿墙回归同时通过。

### Important 5 — 载具坐标与有效惯性

文件：`test_vehicle.c`、`physics.c`、`vehicle.c`。

- 底盘旋转 90° 后接地转向、制动和抓地：`8 passed, 1 failed`。
- 改为绕 chassis up 转向、按该轴有效逆惯性判断并按 chassis forward 制动后，主场景转绿。
- 零惯性对照随后暴露四元数归一化产生的 `3.55e-15` 伪非零重量，使用 `1e-12` 数值容差后 `9/9`。
- 零有效横摆惯性保持锁定，非零惯性正常转向。

### Important 6 — 多 ragdoll 共享 IK

文件：`test_ragdoll.c`、`animation.c`、`animation.h`、`ragdoll.c`、`ragdoll.h`。

- 两个 ragdoll 共享 IK，A→B/B→A 两种停用顺序：`8 passed, 1 failed`。
- acquire/release 计数分离于手动挂起；中途始终屏蔽 IK，最后一次停用才恢复。
- GREEN：ragdoll `9/9`、animation `37/37`。

### Minor

删除 `docs/design/physics_extended.md` 行尾空格，最终提交内容通过 `git diff --check`。

## 生产变异证据

变异均临时修改生产实现、构建运行，然后恢复；未提交变异体。

- 绕过 constraint generation：identity `1 passed, 1 failed`，旧 remove 删除新约束。
- twist 投影改回世界轴：cone `7 passed, 1 failed`，旋转 A 场景误差约 0.516 rad。
- 跳过布娃娃 body slot 恢复：4 组中途失败快照变红，最终 `8 passed, 4 failed`（当时含共享 IK 测试）。
- world Y 转向：vehicle `8 passed, 1 failed`。
- IK release 直接清零：共享 IK `8 passed, 1 failed`。
- 禁用实际唤醒函数：普通物理 `78 passed, 2 failed`，运动接触与纯速度约束均未唤醒。

恢复后 normal、ASan+UBSan、TSan focused 均重新通过。

## 三 lane 最终验证

所有构建均使用 `-j3`，target 为：

`test_physics test_physics_identity test_physics_hinge test_physics_slider test_physics_cone_twist test_vehicle test_ragdoll test_animation test_character test_rope test_cloth test_soft_body test_destructible test_script_lua`

CTest 选择：

```bash
-R 'test_physics$|physics_identity|physics_hinge|physics_slider|physics_cone_twist|test_ragdoll|test_vehicle|test_character|test_rope|test_cloth|test_soft_body|test_destructible|test_script_lua|test_animation$' --output-on-failure
```

- `build-physics-normal`：`14/14` 通过，0 失败；`engine` 目标同时构建通过。
- `build-physics-asan`（`ENGINE_USE_ASAN=ON`、`ENGINE_USE_UBSAN=ON`）：`14/14` 通过，无 ASan/LSan/UBSan 报告。
- `build-physics-tsan`（`ENGINE_USE_TSAN=ON`）：`14/14` 通过，无 ThreadSanitizer 报告。

热路径检查：`physics_step`、约束求解、`vehicle_step`、ragdoll 写出只使用内嵌数组或定长栈。分配仅为既有 `physics_world_create/destroy` 和 Lua bind/shutdown 的固定容量映射，不在上述热路径发生。

## 限制

- 轮子仍为射线接触实体，不是独立刚体；不含高级轮胎、轮体侧壁或转动惯量模型，sweep 精度沿用现有 AABB 查询。
- 布娃娃最多 32 骨，假定可分解、非剪切 TRS 绑定；没有自动人体骨生成或专用自碰撞过滤组。
- 线性约束速度仍使用现有质心速度模型，不是完整接触/关节耦合张量求解器。
- 证据范围为 Linux/GCC focused 非图形测试，未声称全仓、Windows、真机 GPU 或交互视觉验收。
