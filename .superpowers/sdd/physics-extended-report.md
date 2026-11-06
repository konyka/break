# P5 物理补全交付报告

日期：2026-11-03
分支：`cry-wave1-physics`
状态：实现、focused 验证、自审与本地提交完成；未 push、未创建 PR。

## 交付内容

- 在现有 `PhysicsWorld.constraints[64]` 中加入锥 twist 约束：双端锚点、swing 上下限、twist 上下限、参考姿态、有效逆惯性分配、界外角速度裁剪及零惯性保护。
- 增加真实自动休眠与 `physics_body_wake`；冲量、姿态、推动、接触和实际约束修正唤醒。零误差约束不再阻止休眠。停放/销毁支撑会唤醒动态体，tombstone（包括显式销毁后的 slot 0）可复用。
- 载具保留一个底盘刚体，以四个内嵌射线轮接触实体实现独立悬挂、接地驱动、制动、侧向抓地和速度相关转向。控制状态持久化、限幅并拒绝非有限输入；创建失败不改调用者对象，destroy 幂等回收。
- 布娃娃使用真实骨架父索引和锥 twist 约束，保存骨体到关节的绑定偏移；写出父局部 TRS 时抵消父旋转及父链世界缩放，再通过 `skeleton_apply_local_trs` 生成蒙皮矩阵。激活挂起 IK，停用恢复原状态。
- 布娃娃激活完整预检父图、矩阵、骨体与约束容量；失败不提交临时 `Ragdoll`，防御性回滚撤销本次约束和骨体。停用只移除自己的约束。

## 主要文件

- `engine/src/physics/physics.c`, `physics.h`
- `engine/src/physics/character.c`, `character.h`
- `engine/src/physics/vehicle.c`, `vehicle.h`
- `engine/src/physics/ragdoll.c`, `ragdoll.h`
- `engine/src/animation/animation.c`, `animation.h`（仅 IK 挂起，不涉及 morph）
- `engine/tests/test_physics.c`, `test_physics_cone_twist.c`, `test_vehicle.c`, `test_ragdoll.c`
- `engine/CMakeLists.txt`
- `docs/design/physics_extended.md`
- `docs/superpowers/plans/2026-11-02-physics-extended.md`

未修改 `docs/Implementation_Status.md`、master 或其他子项目。

## RED / GREEN 证据

所有阶段均先写真实测试。接口编译 RED 后增加最小入口，再取得运行期行为 RED；不是仅用编译失败代替行为验证。

1. 锥 twist：入口 stub 后运行 `test_physics_cone_twist`，结果 `0 passed, 5 failed`；实现后 `5/5`，增加休眠覆盖后最终 `7/7`。
2. 休眠/唤醒：最小状态入口后普通物理测试为 `71 passed, 2 failed`，锥 twist 唤醒为 `5 passed, 1 failed`；实现后普通物理 `73/73`，focused 集合通过。
3. 载具：空轮状态/销毁入口后 `1 passed, 4 failed`；四轮接触、空中无驱动、控制及回收实现后 `5/5`，角色 sweep 回归 `30/30`。
4. 布娃娃：空写出/旧父关系实现下 `0 passed, 5 failed`；完整实现后 `5/5`。自审新增父缩放测试先得到 `5 passed, 1 failed`（局部 Y 预期 1、实际 2），修正后 `6/6`；动画回归 `37/37`。
5. 自审发现零误差约束阻止休眠，新增测试得到 `6 passed, 1 failed`；只在实际修正时唤醒后锥 twist `7/7`，完整 focused 集合再次通过。

## 变异证据

每项变异均临时修改生产代码、构建并运行，随后恢复和复跑；变异体未提交。

- 禁用 swing 上限：`3 passed, 2 failed`，正向/双动态 swing 测试失败。
- 禁用 twist 上限：`4 passed, 1 failed`，45° 未被截到 20°。
- 将子关节局部 TRS 错写为世界 TRS：`3 passed, 2 failed`，两个手算姿态测试失败。
- 绕过布娃娃约束容量预检并禁用回滚 remove：`2 passed, 3 failed`；三骨夹具在第二个约束处失败并留下约束，世界快照比较变红。
- 允许锥 twist 覆盖活动约束槽：`5 passed, 1 failed`，满容量创建不再返回 `UINT32_MAX`。

## 构建与测试

所有构建使用 `-j3`，工作目录均为本 worktree。

### Normal

```bash
cmake --build build-physics-normal -j3 --target \
  test_physics test_physics_cone_twist test_physics_hinge test_physics_slider \
  test_vehicle test_ragdoll test_animation test_character
ctest --test-dir build-physics-normal \
  -R 'test_physics$|physics_cone_twist|physics_hinge|physics_slider|test_vehicle|test_ragdoll|test_animation$|test_character' \
  --output-on-failure
```

结果：`8/8` 通过，`0` 失败。

### ASan + UBSan

配置：`-DENGINE_RHI_BACKEND=opengl -DENGINE_USE_ASAN=ON -DENGINE_USE_UBSAN=ON`。以相同 target 和 CTest 正则构建运行。

结果：首次及自审修复后复跑均 `8/8` 通过，无 AddressSanitizer、LeakSanitizer 或 UndefinedBehaviorSanitizer 报告。

### TSan

配置：`-DENGINE_RHI_BACKEND=opengl -DENGINE_USE_TSAN=ON`。以相同 target 和 CTest 正则构建运行。

结果：首次及自审修复后复跑均 `8/8` 通过，无 ThreadSanitizer 报告。

### 热路径与差异检查

对 `physics.c`、`character.c`、`vehicle.c`、`ragdoll.c` 检查分配调用，仅发现既有的 `physics_world_create` calloc 和 `physics_world_destroy` free。`physics_step`、约束求解、`vehicle_step`、布娃娃写出均只使用内嵌数组或定长栈。

`git diff --check` 在功能提交前及最终报告提交前执行，无空白错误。构建产物位于忽略的 `build-physics-*` 目录，不作为交付源码提交。

## 自审

自审覆盖数值退化、零惯性、容量、事务、姿态空间、IK 状态恢复、销毁和热路径。修复了两个重要问题：父缩放下的局部平移换算，以及零误差约束反复唤醒。最终未发现遗留的 Critical/Important 问题。按恢复指令执行的是当前会话自审，没有声称存在外部 reviewer。

## 提交

- `8190f940` — 设计文档
- `03b8f65f` — TDD 实施计划
- `75f0e8ee` — 锥 twist 约束
- `8c884474` — 休眠与唤醒
- `ac114798` — 载具轮接触与控制
- `7ddb2999` — 布娃娃局部姿态驱动
- `95635fc1` — 零误差约束休眠修复

最终文档/报告提交 id 以本分支最后一次 `git log` 为准。

## 限制与未覆盖范围

- 轮子是明确等价的射线接触实体，不是四个独立刚体；不模拟轮体侧壁碰撞、轮体转动惯量或 Pacejka 轮胎模型。轮 sweep 沿用现有 AABB 查询精度。
- 布娃娃固定最多 32 骨，假定输入是可分解、非剪切的 TRS 蒙皮绑定；未实现自动人体骨生成或专用自碰撞过滤组。
- 角约束采用固定迭代和现有刚体模型；线性约束速度仍沿用质心速度求解，不是完整接触/关节耦合的刚体张量引擎。
- 本次证据是 Linux/GCC focused 非图形测试，不是全仓全平台测试；未运行 Windows、真机 GPU 或交互驾驶/布娃娃视觉验收。
