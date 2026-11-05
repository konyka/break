# Physics Extended Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** 在现有物理世界上交付稳定锥 twist 约束、射线轮载具、布娃娃局部 TRS/IK 互斥及完整生命周期防护。

**Architecture:** 复用 `PhysicsWorld` 的刚体、约束槽、BVH 和固定步长；四轮以 `Vehicle` 内嵌接触实体表示。布娃娃保存骨体到关节的绑定偏移，写出局部 TRS 后复用 `skeleton_apply_local_trs`。所有可变状态留在 GameThread，热路径仅使用固定数组和栈。

**Tech Stack:** C11、现有 physics/animation C API、CTest、`test_framework.h`、CMake、GCC ASan/UBSan/TSan。

## Global Constraints

- 只修改 `.worktrees/cry-physics` 的 `cry-wave1-physics` 分支，不 push、不创建 PR。
- 遵循总设计第 4、5、6、8 节和 `docs/design/physics_extended.md`；不提高固定容量冒充功能。
- 每个行为先测试并观察 RED，再最小实现转 GREEN；不能以接口缺失的编译失败作为唯一 RED 证据。
- 构建并行度固定 `-j3`；focused normal、ASan+UBSan、TSan 都必须实际运行。
- 不修改 `docs/Implementation_Status.md` 或动画 morph 文件。
- 热路径不分配；失败事务化；约束极限、姿态换算、失败回滚、容量均做真实变异并恢复。

---

### Task 1: 锥 twist 约束与角限位

**Files:**
- Create: `engine/tests/test_physics_cone_twist.c`
- Modify: `engine/src/physics/physics.h`
- Modify: `engine/src/physics/physics.c`
- Modify: `engine/CMakeLists.txt`

**Interfaces:**

```c
typedef struct ConeTwistDesc {
    u32 body_a, body_b;
    Vec3 anchor_local_a, anchor_local_b;
    Vec3 axis_local_a, axis_local_b;
    f32 swing_min, swing_max;
    f32 twist_min, twist_max;
} ConeTwistDesc;
u32 physics_constraint_add_cone_twist(PhysicsWorld *pw, const ConeTwistDesc *desc);
```

- [ ] **Step 1: 写约束行为失败测试**

用手算姿态覆盖：X 轴 60° swing 被 `[0,30°]` 截到 30°；Y 轴 +45°/-45° twist 分别被 `[-20°,20°]` 截断；界内 10° 不变；锚点最终重合。静态 A 不动，双动态端都按有效逆惯性旋转。零惯性轴不被强改，全部有限。非法范围、NaN、零轴和满容量返回 `UINT32_MAX` 且计数不变。核心断言：

```c
ASSERT_FLOAT_EQ(axis_angle(pw->bodies[b].orientation), (f32)M_PI / 6.0f, 2e-3f);
ASSERT_FLOAT_EQ(twist_y(pw->bodies[b].orientation), 20.0f * (f32)M_PI / 180.0f, 2e-3f);
ASSERT_EQ(full->constraint_count, (u32)PHYSICS_MAX_CONSTRAINTS);
```

在 CMake 按 `test_physics_hinge` 模式注册 `test_physics_cone_twist`。

- [ ] **Step 2: 观察接口 RED，再观察行为 RED**

Run:

```bash
cmake -S engine -B build-physics-normal -DENGINE_RHI_BACKEND=opengl
cmake --build build-physics-normal -j3 --target test_physics_cone_twist
```

Expected: 首次因新接口缺失而编译失败。随后只增加描述、槽字段和返回 `UINT32_MAX` 的最小入口，再构建运行；Expected: 创建/限位断言失败，确认不是只靠编译 RED。

- [ ] **Step 3: 实现创建验证和稳定角投影**

在 `DistanceConstraint` 增加 cone 类型、B 轴、两端参考姿态和四个角限位。创建完整验证后才写槽并增加计数。角修正核心按有效逆惯性分配：

```c
f32 angular_weight(const RigidBody *b, Vec3 axis_w) {
    if (b->inv_mass <= 0.0f) return 0.0f;
    Quat q = rigid_orientation(b);
    Vec3 n = quat_rotate_vec3(quat_inverse(q), axis_w);
    f32 w = 0.0f;
    for (int i = 0; i < 3; i++) {
        if (b->inertia_diag.e[i] > 0.0f)
            w += n.e[i] * n.e[i] / b->inertia_diag.e[i];
    }
    return w;
}
```

`apply_angular_delta(a,b,axis,angle)` 对 B 施加正最短弧、对 A 施加反向最短弧，分母为零直接返回。swing 由两世界轴夹角和 `atan2(|cross|,dot)` 得到；twist 由去除参考姿态后的相对四元数投影并规范到 `[-PI,PI]`。越界时施加最短弧，并只移除向界外的相对角速度。平移锚点继续走同一约束投影循环，不增加分配。

- [ ] **Step 4: 转绿并做限位变异**

Run: `cmake --build build-physics-normal -j3 --target test_physics_cone_twist test_physics_hinge test_physics_slider && ctest --test-dir build-physics-normal -R 'physics_(cone_twist|hinge|slider)' --output-on-failure`
Expected: 全通过。临时删除 swing 越界分支，确认 swing 测试 RED；恢复。临时删除 twist 越界分支，确认 twist 测试 RED；恢复并复跑。

- [ ] **Step 5: 提交约束阶段**

```bash
git add engine/src/physics/physics.[ch] engine/tests/test_physics_cone_twist.c engine/CMakeLists.txt
git commit -m "physics: add stable cone twist constraints"
```

### Task 2: 休眠、唤醒和零惯性生命周期

**Files:**
- Modify: `engine/src/physics/physics.h`
- Modify: `engine/src/physics/physics.c`
- Modify: `engine/tests/test_physics.c`
- Modify: `engine/tests/test_physics_cone_twist.c`

**Interfaces:**

```c
void physics_body_wake(PhysicsWorld *pw, u32 body_id);
```

- [ ] **Step 1: 写休眠/唤醒失败测试**

构造无重力静止体，静止达到阈值后断言 `sleeping`、保存位置并多次 step 不积分；`physics_body_apply_impulse` 后同帧速度生效且位置移动。`physics_body_set_pose`、`physics_push_body` 和 cone 限位修正分别唤醒。零惯性体绕锁定轴有角速度时保持原姿态且全部分量有限。销毁约束/停放骨体后新增刚体能复用槽。

- [ ] **Step 2: 运行并确认行为 RED**

Run: `cmake --build build-physics-normal -j3 --target test_physics test_physics_cone_twist && ./build-physics-normal/test_physics && ./build-physics-normal/test_physics_cone_twist`
Expected: `sleeping` 字段/唤醒接口首次编译 RED；最小加入状态但不跳积分后，休眠和唤醒行为断言 RED。

- [ ] **Step 3: 实现自动休眠和事件唤醒**

连续静止达到 60 帧且线/角速度低于阈值时置 `sleeping` 并清零速度。积分循环跳过休眠体，碰撞仍保留。所有公开姿态/冲量/推动入口调用 `physics_body_wake`；接触或约束实际移动动态体前也唤醒。`physics_body_park` 唤醒其余动态体，防止支撑销毁后永久悬空。revive/create 明确清除 sleeping。零惯性继续使用锁定语义，角投影沿用 Task 1 的零分母保护。

- [ ] **Step 4: 回归并提交**

Run: `ctest --test-dir build-physics-normal -R 'test_physics$|physics_cone_twist|physics_hinge|physics_slider|test_character' --output-on-failure`
Expected: 全通过，无既有 rest/BVH 回归。

```bash
git add engine/src/physics/physics.[ch] engine/tests/test_physics.c engine/tests/test_physics_cone_twist.c
git commit -m "physics: add sleeping and explicit wake paths"
```

### Task 3: 载具控制与四轮接触

**Files:**
- Modify: `engine/src/physics/vehicle.h`
- Modify: `engine/src/physics/vehicle.c`
- Modify: `engine/tests/test_vehicle.c`

**Interfaces:**

```c
typedef struct VehicleWheel {
    Vec3 local_position, world_position, contact_point, contact_normal;
    u32 ground_body;
    f32 compression, suspension_force;
    bool grounded;
} VehicleWheel;
typedef struct VehicleControlState { f32 throttle, steer, brake; } VehicleControlState;
void vehicle_destroy(Vehicle *v, PhysicsWorld *pw);
```

- [ ] **Step 1: 写轮状态、空中和回收失败测试**

平地静置后四轮均接地且压缩量非负；只在单个轮下放置地面时其他轮不伪造接触。空中 throttle 不产生水平加速度或抓地减速。输入 2/-2/2 被保存为 1/-1/1，NaN 输入保持上一控制状态。满容量创建失败不改变原 `Vehicle`；destroy 后 chassis 为 tombstone，再创建其他刚体复用该槽。保留原有悬挂、驱动和 blocked-exit 测试。

- [ ] **Step 2: 观察行为 RED**

先只加入状态字段和空 `vehicle_destroy`，不填轮接触。Run: `cmake --build build-physics-normal -j3 --target test_vehicle && ./build-physics-normal/test_vehicle`
Expected: 接地状态、空中驱动、控制持久化和回收断言失败。

- [ ] **Step 3: 实现固定四轮悬挂与控制**

每轮从底盘局部位置投射 `suspension_rest + wheel_radius`；以 `compression = reach - hit_distance`、轮点速度计算非负 spring/damper 力。记录命中的 body/point/normal。仅接地轮累计驱动、制动与侧向抓地；`dt` 用于指数或夹取的速率衰减，不使用帧率相关的固定 `1-brake`。前轮按 `steer * max_steer` 改方向，横摆目标由速度和轴距推导，零惯性轴不写入角速度。创建用临时 `Vehicle`，成功才整体赋值；destroy 幂等回收并清零。

- [ ] **Step 4: 回归并提交**

Run: `cmake --build build-physics-normal -j3 --target test_vehicle test_physics && ./build-physics-normal/test_vehicle && ./build-physics-normal/test_physics`
Expected: 全通过，120 帧悬挂稳定且 60 帧接地驱动达到既有速度阈值。

```bash
git add engine/src/physics/vehicle.[ch] engine/tests/test_vehicle.c
git commit -m "physics: model vehicle wheel contacts and controls"
```

### Task 4: 布娃娃局部 TRS、IK 互斥与回收

**Files:**
- Modify: `engine/src/physics/ragdoll.h`
- Modify: `engine/src/physics/ragdoll.c`
- Modify: `engine/src/animation/animation.h`
- Modify: `engine/src/animation/animation.c`
- Modify: `engine/tests/test_ragdoll.c`
- Modify: `engine/CMakeLists.txt`

**Interfaces:**

```c
void anim_ik_set_physics_suspended(IKSystem *ik, bool suspended);
bool ragdoll_activate(Ragdoll *rd, PhysicsWorld *pw, const Skeleton *sk, IKSystem *ik);
void ragdoll_deactivate(Ragdoll *rd, PhysicsWorld *pw);
bool ragdoll_write_local_trs(const Ragdoll *rd, const PhysicsWorld *pw,
                             const Skeleton *sk, Vec3 *p, Quat *q, Vec3 *s);
```

- [ ] **Step 1: 写手算局部姿态和互斥失败测试**

建立根关节和子关节，根世界旋转 90°、子刚体相对根再旋转 90°，并将根平移到非零位置。手算子局部平移和旋转，断言输出不是世界值；缩放保持绑定值。`ragdoll_write_pose` 后再用独立世界矩阵乘 `inverse_bind` 检查蒙皮结果。父索引使用 `{UINT32_MAX,0,1}` 之外的合法顺序，验证不依赖 `j-1` 创建顺序。

激活后 `anim_ik_solve` 不得改变旋转；deactivate 后 IK 恢复。约束满/骨体满/非法父关系失败时比较世界约束数组、活动计数、body count 和 `Ragdoll` 哨兵，确保完全不变；成功后 deactivate 移除自有约束、停放骨体并允许容量复用。

- [ ] **Step 2: 观察接口与行为 RED**

更新 CMake 让 `test_ragdoll` 链接 `animation.c` 和 `skeleton.c` 所需的最小真实依赖。先加新签名/空写出但不实现父空间换算。Run: `cmake --build build-physics-normal -j3 --target test_ragdoll test_animation && ./build-physics-normal/test_ragdoll`
Expected: 局部 TRS、IK 屏蔽和回滚断言失败；`test_animation` 继续构建作为既有 IK 基线。

- [ ] **Step 3: 实现绑定偏移、事务激活和写出**

从 `current_pose * inverse(inverse_bind)` 取得激活时关节世界 TRS；验证有限性和父图。骨体创建时保存 `body_to_joint_p/q` 与绑定局部 scale。所有创建记录在临时 `Ragdoll`，锥 twist 约束保存到自己的 constraint id；失败倒序 remove/park，成功才赋给调用者并挂起 IK。

写出先填充所有关节世界 p/q，再按真实父索引计算：

```c
out_q[j] = quat_normalize(quat_mul(quat_inverse(world_q[parent]), world_q[j]));
out_p[j] = quat_rotate_vec3(quat_inverse(world_q[parent]),
                            vec3_sub(world_p[j], world_p[parent]));
for (int k = 0; k < 3; k++) out_p[j].e[k] /= parent_world_s.e[k];
```

`parent_world_s` 是父链绑定局部缩放的逐分量乘积。根输出世界 p/q，scale 使用绑定值。`ragdoll_write_pose` 复用固定 32 项栈数组和 `skeleton_apply_local_trs`。deactivate 只移除自己的约束、停放自己的骨体、恢复 IK 原挂起状态并清零 `Ragdoll`。

- [ ] **Step 4: 转绿并做姿态/回滚变异**

Run: `cmake --build build-physics-normal -j3 --target test_ragdoll test_animation && ./build-physics-normal/test_ragdoll && ./build-physics-normal/test_animation`
Expected: 全通过。临时把子 `local_q/local_p` 改成世界值，确认姿态测试 RED；恢复。临时注释失败路径的约束 remove，通过可重复失败/容量夹具确认回滚测试 RED；恢复并复跑。

- [ ] **Step 5: 提交布娃娃阶段**

```bash
git add engine/src/physics/ragdoll.[ch] engine/src/animation/animation.[ch] engine/tests/test_ragdoll.c engine/CMakeLists.txt
git commit -m "physics: drive skeleton local poses from ragdolls"
```

### Task 5: 容量变异、热路径审计与三树验证

**Files:**
- Modify only if a regression test requires it: `engine/src/physics/*`, `engine/tests/test_*.c`
- Create: `.superpowers/sdd/physics-extended-report.md`

**Interfaces:** 使用 Tasks 1–4 的正式接口，不新增测试专用生产接口。

- [ ] **Step 1: 容量变异和热路径检查**

临时把 cone 创建的容量检查改成允许覆盖活动槽，确认满容量/计数测试 RED；恢复。临时把布娃娃可用容量检查删除，确认创建失败与原子性测试 RED；恢复。检查 `physics_step`、约束求解、`vehicle_step`、`ragdoll_write_local_trs/write_pose` 的调用段不含分配函数，新增存储均为固定数组。

- [ ] **Step 2: normal focused 回归**

Run:

```bash
cmake --build build-physics-normal -j3 --target test_physics test_physics_cone_twist test_physics_hinge test_physics_slider test_vehicle test_ragdoll test_animation test_character
ctest --test-dir build-physics-normal -R 'test_physics$|physics_cone_twist|physics_hinge|physics_slider|test_vehicle|test_ragdoll|test_animation$|test_character' --output-on-failure
```

Expected: 全部通过。

- [ ] **Step 3: ASan+UBSan focused 回归**

Run:

```bash
cmake -S engine -B build-physics-asan -DENGINE_RHI_BACKEND=opengl -DENGINE_USE_ASAN=ON -DENGINE_USE_UBSAN=ON
cmake --build build-physics-asan -j3 --target test_physics test_physics_cone_twist test_physics_hinge test_physics_slider test_vehicle test_ragdoll test_animation test_character
ctest --test-dir build-physics-asan -R 'test_physics$|physics_cone_twist|physics_hinge|physics_slider|test_vehicle|test_ragdoll|test_animation$|test_character' --output-on-failure
```

Expected: 全部通过，无 AddressSanitizer、LeakSanitizer 或 UndefinedBehaviorSanitizer 报告。

- [ ] **Step 4: TSan focused 回归**

Run:

```bash
cmake -S engine -B build-physics-tsan -DENGINE_RHI_BACKEND=opengl -DENGINE_USE_TSAN=ON
cmake --build build-physics-tsan -j3 --target test_physics test_physics_cone_twist test_physics_hinge test_physics_slider test_vehicle test_ragdoll test_animation test_character
ctest --test-dir build-physics-tsan -R 'test_physics$|physics_cone_twist|physics_hinge|physics_slider|test_vehicle|test_ragdoll|test_animation$|test_character' --output-on-failure
```

Expected: 全部通过，无 ThreadSanitizer 报告。若宿主机 TSan 运行时自身无法启动，记录完整诊断并用可用运行时重试，不把未运行写成通过。

- [ ] **Step 5: 只读评审和交付**

派只读 reviewer 检查正确性、事务、容量、数值稳定、热路径和测试有效性；修复全部 Critical/Important 并对每项修复先加回归测试。运行 `git diff --check`，检查状态中没有测试临时产物。报告写明 RED/GREEN/变异命令和结果、三树证据、提交 id、评审结果及射线轮/32 骨等限制，最后提交报告和剩余修复。


## Fix round 1 执行补充

- body/constraint 公共身份改为 `{index,generation}`；旧裸 id 变更入口已迁移，不保留兼容旁路。
- 非有限 dt/body/vehicle 输入在任意写入前拒绝；ragdoll 中途失败直接恢复受影响 slot 原值。
- cone twist 使用当前 A-local 相对坐标；休眠在接触和约束求解后统一评估。
- 载具使用 chassis up/forward 和有效逆惯性；共享 IK 使用 acquire/release 所有权计数。
- 最终证据与变异输出见 `.superpowers/sdd/2026-11-02-physics-extended/physics-extended-report.md`。

## Fix round 2 执行补充

- main 的 transform 同步、dangling 重建、live-set、elevator、编辑/调试/布局/克隆路径统一通过 `physics_body_resolve`；stale 身份明确重建或跳过，真实 `engine_demo` 构建覆盖 `main.c`。
- revive 对 live/tombstone 统一校验当前 generation；scene/main 显式使用当前 tombstone generation，旧 tombstone 句柄不能恢复新身份。
- body/constraint generation 在 `UINT32_MAX` 后永久退休 slot，所有创建和解析路径拒绝退休身份，不回绕产生 ABA。
- Lua 同一世界重绑保留 serial/generation/epoch/retired 映射；不同世界或失败重绑使旧 raw id 失效，超出 `u32` 的输入 serial 在截断前拒绝，耗尽后不再回绕。
- Lua spawn 在 body 创建前完成 slot、映射、serial 和 public id 预检，成功后只提交映射；映射不可用及两类耗尽均以完整 `PhysicsWorld` 和 body 数组快照验证原子性。
- `test_physics_identity` 为 `4/4`、`test_scene_state` 为 `11/11`、`test_script_lua` 为 `30/30`；normal、ASan+UBSan、TSan focused 均 `15/15`，三棵树分别构建 `engine_demo` 成功。RED、四项生产变异和限制详见上述报告。
