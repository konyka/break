# 物理补全、布娃娃姿态驱动与载具框架

日期：2026-11-02  
分支：`cry-wave1-physics`

## 1. 目标与边界

在现有 `PhysicsWorld` 上补齐三类可调用能力：

- 锥 twist 约束：锚点重合、摆动角上下限、扭转角上下限、双刚体角修正和零惯性保护。
- 载具：持久控制状态、四个独立轮接触实体、悬挂、接地驱动、制动、侧向抓地与转向。
- 布娃娃：从事务式激活到销毁回收，并将刚体世界姿态经绑定偏移和父姿态换算成骨架局部 TRS；物理驱动期间 IK 不得改写同一姿态。

同时补齐自动休眠/显式唤醒、销毁回收、容量和失败原子性。绳索、布料、软体和破坏仍使用原世界；不新建并行物理系统，不提高 `PHYSICS_MAX_CONSTRAINTS` 或布娃娃骨数上限，不修改动画 morph 文件或 `docs/Implementation_Status.md`。

## 2. 方案取舍

### 采用：扩展当前世界和固定状态槽

约束继续复用 `PhysicsWorld.constraints`，载具轮采用四个内嵌射线接触记录，布娃娃复用原刚体和约束槽。优点是容量、碰撞、BVH、销毁和测试都沿现有路径，改动集中且热路径无需分配。

### 不采用：独立刚体轮和悬挂约束图

每个车轮建立球体/圆柱刚体再连接底盘可增加视觉轮体，但会引入轮体碰撞过滤、更多约束容量压力和额外的销毁事务。当前需求允许明确等价的轮接触实体，因此本轮以射线轮提供物理行为；`VehicleWheel` 的世界位置和接触点可供以后视觉轮同步。

### 不采用：只输出布娃娃世界矩阵

刚体矩阵既不是关节世界矩阵，也不是 `Skeleton.current_pose` 所存的蒙皮矩阵。直接覆盖会产生骨骼拉伸、错位和父空间错误。必须显式经过“刚体→关节世界→父局部 TRS→现有骨架求值”的数据流。

## 3. 公共接口与状态

### 3.1 锥 twist 约束

新增 `ConeTwistDesc` 和 `physics_constraint_add_cone_twist`：

```c
typedef struct ConeTwistDesc {
    u32 body_a, body_b;
    Vec3 anchor_local_a, anchor_local_b;
    Vec3 axis_local_a, axis_local_b;
    f32 swing_min, swing_max; /* 弧度，0 <= min <= max <= PI */
    f32 twist_min, twist_max; /* 弧度，-PI <= min <= max <= PI */
} ConeTwistDesc;

u32 physics_constraint_add_cone_twist(PhysicsWorld *pw, const ConeTwistDesc *desc);
```

创建时保存两端参考姿态。零/零范围表示锁在参考姿态，不沿用铰链的“零/零无限制”特例。非法刚体、自连接、非有限值、退化轴和非法范围返回 `UINT32_MAX`，不得消耗槽。容量仍共享 `PHYSICS_MAX_CONSTRAINTS`。

### 3.2 休眠与唤醒

`RigidBody` 增加 `sleeping`。位置与姿态连续静止达到固定帧阈值后进入休眠；休眠刚体不积分，但仍参与碰撞查询。`physics_body_wake`、`physics_body_set_pose`、冲量、位置推动、有效轮接触力和约束修正会唤醒相关动态刚体。销毁静态支撑时唤醒世界中的动态刚体，避免悬空休眠。

零惯性轴表示该局部轴不可转动。角约束按局部轴投影计算有效逆惯性；全零惯性或两端均不可绕修正轴转动时跳过该角修正，不除零、不写 NaN，也不靠强行把惯性改成 1 冒充解锁。

### 3.3 载具轮接触实体

`Vehicle` 内嵌四个 `VehicleWheel` 和规范化后的 `VehicleControlState`。每个轮记录局部/世界位置、接地刚体、接触点/法线、压缩量和悬挂力；无独立刚体 id，这是明确的射线轮接触模型。控制输入先拒绝非有限值并夹到 `[-1,1]`（制动为 `[0,1]`），再保存本帧状态。

每次 `vehicle_step` 独立投射四道悬挂射线：

1. 由命中距离得到压缩量，由底盘线速度和轮臂角速度得到悬挂阻尼力；只保留非负支撑力。
2. 接地轮才贡献驱动、制动和侧向抓地，空中控制输入不能制造水平加速度。
3. 前轮方向按转向角偏转，横摆响应随前进速度和轴距变化；零横摆惯性时保持不可转。
4. 汇总力写回同一个底盘刚体，不逐轮创建临时对象或分配内存。

`vehicle_destroy` 回收底盘并清空控制/轮状态；创建失败保持调用者原对象不变。原有 `vehicle_create`、`vehicle_step`、`vehicle_enter`、`vehicle_exit` 保持可用。

### 3.4 布娃娃局部 TRS 与 IK 互斥

`RagdollBone` 增加所拥有约束 id、关节相对刚体的绑定平移/旋转和局部绑定缩放。激活参数增加可选 `IKSystem *ik`：

```c
bool ragdoll_activate(Ragdoll *rd, PhysicsWorld *pw,
                      const Skeleton *sk, IKSystem *ik);
void ragdoll_deactivate(Ragdoll *rd, PhysicsWorld *pw);
bool ragdoll_write_local_trs(const Ragdoll *rd, const PhysicsWorld *pw,
                             const Skeleton *sk, Vec3 *out_local_pos,
                             Quat *out_local_rot, Vec3 *out_local_scale);
void ragdoll_write_pose(const Ragdoll *rd, const PhysicsWorld *pw, Skeleton *sk);
```

`IKSystem` 增加物理驱动挂起状态和对应 setter；`anim_ik_solve` 在挂起时立即返回。布娃娃激活成功后保存并设置挂起状态，停用后恢复原状态。挂起期间即使调用方新增 IK target，求解仍被屏蔽。

激活先在临时 `Ragdoll` 中验证骨架和容量，再创建骨体与锥 twist 约束。父关系使用 `Skeleton.joint_parents`，不假定父索引为 `j-1`。任一失败移除本次全部约束、停放本次全部骨体，并保持 `rd` 和 IK 状态不变。

写出时先由刚体姿态和绑定偏移恢复每个关节的世界位置/旋转：

- `joint_q = body_q * body_to_joint_q`
- `joint_p = body_p + body_q * body_to_joint_p`

随后对根直接输出世界 TRS，对子关节使用：

- `local_q = inverse(parent_world_q) * joint_q`
- `local_p = component_divide(inverse(parent_world_q) * (joint_p - parent_world_p), parent_world_s)`

`parent_world_s` 是父链绑定局部缩放的逐分量乘积；零或非有限缩放拒绝写出。每个关节的局部缩放保留激活时绑定值。`ragdoll_write_pose` 调用上述接口后复用 `skeleton_apply_local_trs`，因此 `current_pose` 最终仍是正确的 `world * inverse_bind` 蒙皮矩阵。

## 4. 稳定求解与数据流

锥 twist 的平移部分沿用锚点投影。角部分以当前两轴夹角计算 swing，以创建时参考姿态消除后的相对四元数在当前摆轴上的投影计算 twist，并把角度规范到 `[-PI, PI]`。越界时生成最短弧修正；摆动角为零且需要非零下限则使用确定性的垂直轴，避免叉积退化。

角修正按两端有效逆惯性分配，A 承受反向、B 承受正向修正，固定迭代内收敛。限位修正同时只消除继续向界外的相对角速度，不消除合法切向运动。修正或速度裁剪会唤醒刚体。全部临时值位于大小固定的栈或世界/对象内嵌数组中。

每帧顺序保持为：载具/外部控制 → 现有积分与接触 → 约束位置和角投影 → 约束速度处理 → kill floor → post-step → 布娃娃局部 TRS 写出。GameThread 独占所有可变状态。

## 5. 错误、容量与生命周期

- 约束满、骨体容量不足、非法描述、非法父关系均失败，不静默截断。
- 布娃娃创建按“新增槽 + 可复用 tombstone”计算可用容量；回滚只撤销本次创建的约束和刚体。
- 约束/骨体销毁幂等；布娃娃停用只移除自己拥有的约束，不影响世界中已有约束。
- 载具和布娃娃热路径均无 `malloc/calloc/realloc/free`；世界创建/销毁维持现有分配边界。
- 本轮不引入跨线程句柄系统；调用方仍须在 GameThread 内保证对象未并发销毁或复用。

## 6. 验证与变异

先写行为测试并观察真实 RED，再写最小实现。重点覆盖：

- 锥 twist 正/反 swing 和 twist 上下限、合法区间内自由运动、锚点、静态端、双动态端、零惯性、NaN/Inf/退化轴、满容量和槽复用。
- 休眠后不积分、冲量/姿态/约束唤醒，零惯性不产生非有限值。
- 每轮独立接触状态、空中无驱动/抓地、悬挂稳定、控制夹取、非有限输入拒绝、创建失败与销毁回收。
- 非单位父姿态和平移下的局部 TRS 手算结果、非线性父索引、蒙皮矩阵、IK 挂起/恢复、布娃娃创建失败完全回滚、停用后槽复用。

关键变异至少包括：删除 swing/twist 限位、把父局部换算改成直接世界写回、漏删回滚约束、取消容量检查。变异必须让对应测试变红，随后恢复并复跑。最终在 normal、ASan+UBSan、TSan 三棵树以 `-j3` 构建并运行 focused 物理/动画测试，再执行 `git diff --check`。

## 7. 限制

射线轮不是独立碰撞轮体，不模拟轮胎几何侧壁、复杂 Pacejka 力矩或每个轮的刚体转动惯量；本轮提供的是固定容量、可测试的悬挂/接地/驱动框架。布娃娃只覆盖最多 32 个显式骨架关节，未加入自动人体比例生成或自碰撞过滤组。以上限制不以提高上限或伪造物理量规避。
