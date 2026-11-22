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
    PhysicsBodyHandle body_a, body_b;
    Vec3 anchor_local_a, anchor_local_b;
    Vec3 axis_local_a, axis_local_b;
    f32 swing_min, swing_max; /* 弧度，0 <= min <= max <= PI */
    f32 twist_min, twist_max; /* 弧度，-PI <= min <= max <= PI */
} ConeTwistDesc;

PhysicsConstraintHandle physics_constraint_add_cone_twist(
    PhysicsWorld *pw, const ConeTwistDesc *desc);
```

创建时保存两端参考姿态。零/零范围表示锁在参考姿态，不沿用铰链的“零/零无限制”特例。非法刚体、自连接、非有限值、退化轴和非法范围返回 `PHYSICS_CONSTRAINT_HANDLE_INVALID`，不得消耗槽。容量仍共享 `PHYSICS_MAX_CONSTRAINTS`。相对旋转与 twist 投影统一在当前 A-local 坐标系计算，世界轴只用于施加修正。

### 3.2 休眠与唤醒

`RigidBody` 增加 `sleeping`。休眠在接触和约束求解后统一评估：稳定支撑接触允许休眠，非支撑方向的运动接触、非零约束速度、约束删除、冲量、姿态推动和实际位置/角度修正都会唤醒。休眠刚体不积分，但仍参与碰撞查询；持续低速运动不会因接触将速度消零而误睡。

零惯性轴表示该局部轴不可转动。角约束按局部轴投影计算有效逆惯性；全零惯性或两端均不可绕修正轴转动时跳过该角修正，不除零、不写 NaN，也不靠强行把惯性改成 1 冒充解锁。

### 3.3 载具轮接触实体

`Vehicle` 内嵌四个 `VehicleWheel` 和规范化后的 `VehicleControlState`。每个轮记录局部/世界位置、接地 `PhysicsBodyHandle`、接触点/法线、压缩量和悬挂力；无独立刚体 id，这是明确的射线轮接触模型。控制输入先拒绝非有限值并夹到 `[-1,1]`（制动为 `[0,1]`），再保存本帧状态。

每次 `vehicle_step` 独立投射四道悬挂射线：

1. 由命中距离得到压缩量，由底盘线速度和轮臂角速度得到悬挂阻尼力；只保留非负支撑力。
2. 接地轮才贡献驱动、制动和侧向抓地，空中控制输入不能制造水平加速度。
3. 前轮方向按转向角偏转，横摆绕当前 chassis up 轴并按该轴有效逆惯性响应；零有效横摆惯性时保持不可转，制动使用 chassis forward 方向，抓地按各轮右向计算。
4. 汇总力写回同一个底盘刚体，不逐轮创建临时对象或分配内存。

`vehicle_destroy` 回收底盘并清空控制/轮状态；创建失败保持调用者原对象不变。原有 `vehicle_create`、`vehicle_step`、`vehicle_enter`、`vehicle_exit` 保持可用。

### 3.4 布娃娃局部 TRS 与 IK 互斥

`RagdollBone` 保存所拥有的 `PhysicsBodyHandle`、`PhysicsConstraintHandle`、关节相对刚体的绑定平移/旋转和局部绑定缩放。激活参数增加可选 `IKSystem *ik`：

```c
bool ragdoll_activate(Ragdoll *rd, PhysicsWorld *pw,
                      const Skeleton *sk, IKSystem *ik);
void ragdoll_deactivate(Ragdoll *rd, PhysicsWorld *pw);
bool ragdoll_write_local_trs(const Ragdoll *rd, const PhysicsWorld *pw,
                             const Skeleton *sk, Vec3 *out_local_pos,
                             Quat *out_local_rot, Vec3 *out_local_scale);
void ragdoll_write_pose(const Ragdoll *rd, const PhysicsWorld *pw, Skeleton *sk);
```

`IKSystem` 同时支持手动挂起和 ragdoll 所有权计数。每次成功激活 acquire，停用 release；任一 ragdoll 存活时 `anim_ik_solve` 都被屏蔽，只有最后一个所有者停用才恢复，因此两种停用顺序均正确。

激活先在临时 `Ragdoll` 中验证骨架和容量，再创建骨体与锥 twist 约束。父关系使用 `Skeleton.joint_parents`，不假定父索引为 `j-1`。创建事务记录受影响 body/constraint slot 的原值、count 和 `bvh_dirty`；任一中途失败直接恢复快照，包括 tombstone generation，不靠 park/remove 造成二次副作用，并保持 `rd` 和 IK 状态不变。

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

每帧顺序保持为：载具/外部控制 → 现有积分与接触 → 约束位置和角投影 → 约束速度处理 → kill floor → post-step → 布娃娃局部 TRS 写出。LogicThread 独占所有可变状态。

## 5. 错误、容量与生命周期

- 约束满、骨体容量不足、非法描述、非法父关系均失败，不静默截断。
- 持久 body/constraint 身份均为 `{index,generation}`。park 递增 body generation 并解绑关联约束；constraint remove 递增 slot generation 并唤醒有效动态端点。求解、remove、write、revive、deactivate 及 main 的持久消费者都校验 generation，旧所有者不能操作复用后的新对象；main 对 stale 身份明确重建或跳过。revive 只接受当前 parked tombstone 的 generation，live body 不得 revive；scene 对 live body 直接恢复状态且不推进身份，对 parked body 输出权威新句柄，main 只向匹配恢复前身份的 `CRigidBody` 提交。
- body/constraint generation 到达 `UINT32_MAX` 后不再回绕：slot 永久标记 `retired`，创建跳过，resolve/revive/remove 拒绝退休身份，避免最早句柄再次有效。
- 布娃娃创建按“新增槽 + 非退休可复用 tombstone”计算可用容量；事务分配预测与真实 create 使用相同的 retired/free 判定。中途失败直接恢复实际受影响 slot 原值和计数，不用 park 代替完整回滚。
- `physics_step` 的 dt、body create/revive 的 position/extent/mass/shape、pose、impulse、push、vehicle create/step 输入在任意写入前验证有限性，NaN/±Inf 原子拒绝；负有限 extent 继续既有 clamp。
- 约束/骨体销毁幂等；布娃娃停用只移除自己拥有的约束，不影响世界中已有约束。
- 载具和布娃娃热路径均无 `malloc/calloc/realloc/free`；世界创建/销毁维持现有分配边界。Lua 在 bind/shutdown 管理固定容量 serial/generation/epoch/retired 映射，保留既有初始数字 id ABI；同一世界重绑保留映射，跨 world/失败重绑不重置历史 public id 游标，新 id 严格大于历史最大 id，旧变量不能命中新 occupant。map epoch 到达 `UINT32_MAX` 后永久停用映射，不回绕重新开放 adoption。
- Lua spawn 在 `physics_body_create` 前镜像其 slot 选择并验证映射、serial、历史 public id 游标和 53 位上限；serial/public id 耗尽退休映射 slot。预检成功后只提交确定性映射和发号游标，不在创建失败后用 park 回滚，因此分配失败不改变物理世界。
- LogicThread 独占所有可变状态。

## 6. 验证与变异

先写行为测试并观察真实 RED，再写最小实现。重点覆盖：

- 锥 twist 正/反 swing 和 twist 上下限、合法区间内自由运动、锚点、静态端、双动态端、零惯性、NaN/Inf/退化轴、满容量和槽复用。
- 休眠后不积分、冲量/姿态/约束唤醒，零惯性不产生非有限值。
- 每轮独立接触状态、空中无驱动/抓地、悬挂稳定、控制夹取、非有限输入拒绝、创建失败与销毁回收。
- 非单位父姿态和平移下的局部 TRS 手算结果、非线性父索引、蒙皮矩阵、IK 挂起/恢复、布娃娃创建失败完全回滚、停用后槽复用。

关键变异至少包括：删除 swing/twist 限位、把父局部换算改成直接世界写回、漏删回滚约束、取消容量检查。变异必须让对应测试变红，随后恢复并复跑。最终在 normal、ASan+UBSan、TSan 三棵树以 `-j3` 构建并运行 focused 物理/动画测试，再执行 `git diff --check`。

## 7. 限制

射线轮不是独立碰撞轮体，不模拟轮胎几何侧壁、复杂 Pacejka 力矩或每个轮的刚体转动惯量；本轮提供的是固定容量、可测试的悬挂/接地/驱动框架。布娃娃只覆盖最多 32 个显式骨架关节，未加入自动人体比例生成或自碰撞过滤组。以上限制不以提高上限或伪造物理量规避。

## 补充（2026-11-15）：世界快照与确定性回放

`physics.h` 新增进程内快照接口，用于回放和回滚：

- `physics_snapshot_size(pw)`：保存当前世界所需字节数（头部 + `count` 个 `RigidBody` + 全部 64 个约束槽）。
- `physics_snapshot_save(pw, buf, cap, &size)`：容量不足返回 false，缓冲区不写，`*out_size` 总是给出所需字节数。保存会把 BVH 标脏，让原运行和恢复后的运行都从同一状态重建 broadphase。
- `physics_snapshot_restore(pw, buf, size)`：校验魔数、版本、`RigidBody`/约束结构大小、body 数不超过世界容量、长度精确相等；任何一项失败都返回 false，世界不变。恢复 body、约束、世界碰撞统计，并把 BVH 标脏。
- `physics_state_hash(pw)`：对每个 body 的位置、速度、朝向、角速度和睡眠状态做 FNV-1a，供回放比对与网络同步诊断。

快照是同一构建内的内存格式，不是线格式或磁盘格式；接触回调和 post-step 钩子不保存。测试 `physics_snapshot_replay_is_bit_identical` 在发生碰撞后保存，跑 30 步记录结果，再删除约束、新增 body、恢复、重跑 30 步，断言哈希、碰撞统计和全部 `RigidBody` 字节逐位相同。仍缺：跨平台确定性、输入录制文件格式、网络同步。

## 补充（2026-11-15）：输入录制与回放文件格式

`engine/src/physics/physics_replay.{h,c}` 在世界快照之上记录输入：

- `physics_replay_impulse` 施加并记录冲量；`physics_replay_step` 执行 step 并记录 step 后的 `physics_state_hash`。body 无效、冲量或 dt 非有限、dt 不为正、记录存储已满时返回 false，世界和记录都不变。存储由调用方提供，不分配内存。
- 编码格式（小端）：12 字节头部（魔数 `PRPL`、版本 1、记录数），每条记录 32 字节（op、body index、generation、3 个 f32 位模式、u64 step 后哈希）。
- `physics_replay_decode` 校验魔数、版本、记录数不超过容量、长度精确相等、每条 op 合法、浮点有限且 dt 为正；先校验全部记录再写入，失败时 replay 不变。
- `physics_replay_run` 在调用方已用快照恢复的世界上重放，返回 OK / DIVERGED / INVALID，`out_divergent` 给出第一条哈希不符的 step 记录下标。

哈希一致性只在同一构建、同一平台内成立；跨平台浮点确定性仍未保证。


## 补充（2026-11-20）：arm64 物理验证

arm64 lane 新增刚体核心、replay、sync、hinge、cone-twist、identity、ragdoll、vehicle 八项，共 135 例（83/4/13/3/8/5/10/9），统一选择达到八十项。原生与交叉 focused 均为 8/8，无新增 skip。

replay 与 sync 在单进程内比较两个世界或同一录制，因此 arm64 通过只说明同一 arm64 构建在单进程内自洽，不代表不同构建/编译器之间、或 x86-64 与 arm64 之间可逐位回放或保持 lockstep。物理源码当前未使用 `-ffp-contract=off`，编译器可能按构建不同融合乘加；跨架构确定性需要交换录制的专门测试，并很可能需要固定浮点收缩策略。cloth、rope、soft-body、destructible 与 slider 尚未纳入 arm64 选择。


## 补充（2026-11-20）：arm64 扩展物理验证

arm64 lane 新增 slider、cloth、rope、soft-body、destructible 五项和 character（30 例），统一选择达到八十六项，所有以物理模块为主体的已注册测试至此均在 arm64 运行。原生与交叉 focused 均为 6/6，无新增 skip。

五个扩展模块各只有一个测试场景（静态断言点 12/24/10/15/30，含循环）。场景覆盖了主路径：绳索链接与满世界拒绝、布料钉住顶行后回拉、破坏仅在超过阈值后发生、滑块消除垂直偏移并遵守限位、软体在高刚度下恢复偏移。已知缺口：单场景内首个失败断言会提前返回并遮住后续检查，CTest 汇总只报 1 例。


## 补充（2026-11-21）：x86-64 与 arm64 逐位一致

此前的结论是物理哈希只在同一构建、同一平台内一致。本次实测找到了跨架构分歧的根因并修复。

- **现象**：同一场景（静态地面、一个盒子、一个球，每 10 步对盒子施加冲量，步长 1/60 秒）在 x86-64 与 arm64 上第 35 步起状态哈希不同；第 35 步只有两个物体 y 方向速度的最后几位不同（`c02c4522` 与 `c02c4520` 互换）。在不支持 FMA 的 x86-64 基线目标上 `-O0`、`-O2`、`-O2 -ffp-contract=off` 三组哈希相同，那里没有可融合的乘加，因此这一处分歧不来自浮点收缩。
- **根因**：`math.h` 的 `fast_rsqrt` 在有 SSE 时用 `rsqrtss` 估值加一次牛顿迭代（约 22 位精度），在 arm64 上回退为 `1.0f / sqrtf(x)`。两种结果最后几位不同，经 `vec3_len`、`vec3_normalize`、`quat_normalize` 与碰撞法线进入每一步。临时让 x86 也走 `1.0f / sqrtf` 后，x86 哈希与 arm64 完全一致。
- **修复**：`fast_rsqrt` 在所有架构上都返回正确舍入的 `1.0f / sqrtf(x)`。在本机的 1 亿次调用基准中两者均约 2 纳秒/次，没有可测的性能差异。
- **TDD**：`test_physics_replay` 新增 `replay_scene_matches_the_cross_architecture_golden_hashes`，在第 40、120、240 步断言固定哈希 `cf6e44ff4ac4618f`、`bf2164b335a6d86c`、`deda1a2df61f4dcd`。修复前 x86 在第 40 步失败，修复后 x86 与 arm64（QEMU）都通过；该测试已在 arm64 lane 内，因此 CI 的 x86 与 arm64 job 会同时守住这组值。
- **浮点收缩（评审发现）**：逐位一致还依赖 `a*b+c` 不被融合成 FMA。Clang（含 AppleClang）默认 `-ffp-contract=on`，GCC 在 GNU 模式下默认 `fast`；在支持 FMA 的目标上（arm64、x86-64-v3），融合会改变最后几位，场景第 40 步哈希变为 `643a46aeea8c1b8d`。arm64 lane 只是因为 GCC 在 ISO C 模式（`CMAKE_C_EXTENSIONS OFF`）下关闭了收缩才碰巧一致，macOS 的 AppleClang（Apple Silicon）构建会失败。`engine/CMakeLists.txt` 现在对 `src/physics/*.c` 与 `src/math/*.c` 设置源文件属性 `-ffp-contract=off`（Clang/GNU），作用于引擎库与所有测试目标中的这些文件，与此前 meshopt 的处理一致。用 Clang Release `-march=x86-64-v3 -ffp-contract=fast` 复现：加该属性前金标准用例失败，加后通过；110 个物理与数学编译单元均带上该选项。
- **仍未覆盖**：`sinf`、`cosf`、`tanf` 与 `atan2f` 由各平台 libm 提供，不同 glibc 版本之间 `atan2f` 实测有 1 ULP 差异（例如 glibc 2.39 与 2.44 在 `atan2f(0.1, 0.7)` 上不同）。本场景中所有物体角速度始终为 0，`integrate_orientation` 在调用 `quat_from_axis_angle` 之前返回，240 步内 `sinf`、`cosf`、`tanf`、`atan2f` 调用次数均为 0（评审以链接期包装函数计数），因此金标准不覆盖旋转，也不受各平台 libm 差异影响。带旋转或 hinge、cone-twist、slider 的场景需要先做跨平台核对，才能作为金标准；Windows、macOS 的 libm 未验证。

### 追加：带旋转的金标准

上面的金标准场景不调用三角函数。`test_physics_replay` 新增 `spinning_body_matches_the_cross_architecture_golden_hashes`：盒子经 `physics_body_set_pose` 设置非零转动惯量与恒定角速度，240 步内调用 `sinf` 与 `cosf` 各 240 次（以链接期包装函数计数确认）。第 40、120、240 步哈希 `861e49280274a41b`、`edda241ce0d8ffa8`、`ac68585b95a1886d` 在 glibc 2.39 x86-64、glibc 2.44 x86-64 与 glibc 2.39 arm64（QEMU）上完全一致。注意：只设置 `angular_velocity` 而不设置转动惯量时，零惯量轴被视为无限大惯量，方向不积分、也不调用三角函数。`atan2f` 在 glibc 版本间的 1 ULP 差异仍只影响 hinge、cone-twist、slider 约束，这些路径尚无金标准。

### 追加：确定性 `math_atan2f`

hinge、cone-twist、slider 约束的角度原先由平台 `atan2f` 计算，glibc 2.39 与 2.44 之间有 1 ULP 差异，带限位铰链场景因此在两台 x86-64 机器上第 40 步分歧。物理现改用 `math.h` 中只由 IEEE 加减乘除与比较构成的 `math_atan2f`（最大误差约 3.2e-7 弧度，要求包含文件以 `-ffp-contract=off` 编译），`test_physics_replay` 新增铰链金标准，`test_math` 固定其位模式并能检出 FMA 收缩。物理中仍依赖平台 libm 的有 `quat_from_axis_angle` 的 `sinf`/`cosf`（已测环境与 CI 各平台一致）、软体创建时的 `sinf`/`cosf`，以及载具中常量参数的 `tanf`。铰链金标准只在 glibc 2.44 主机上能检出回退到平台 `atan2f`。

### 追加：确定性源码契约

金标准哈希只在平台确实不同时失败（例如只有 glibc 2.44 能检出改回平台 `atan2f`），因此另有宿主契约 `test_physics_determinism_contract` 在任何主机上检查三条源码规则：物理不调用平台 `atan2`/`atan2f`、`fast_rsqrt` 为正确舍入的 `1.0f / sqrtf`、physics/math/`test_math.c` 在 `-ffp-contract=off` 列表中。

### 追加：确定性 `math_sincosf`

`quat_from_axis_angle`、软体创建与载具原先仍使用平台 `sinf`/`cosf`/`tanf`。现在 `math.h` 新增 `math_sincosf`（double 中 Cody-Waite 约减 + musl float 核，|x| ≤ 2^28 时误差低于 3e-8，结果与 FMA 收缩无关），前两处改用它，载具的 `tanf(0.55f)` 改为逐位相同的字面量。物理代码不再调用任何平台三角函数；`test_physics_determinism_contract` 禁止 `src/physics/` 调用 `sin`/`cos`/`tan`/`sincos`，并要求 `quat_from_axis_angle` 使用 `math_sincosf`。`test_math` 用与 glibc 舍入不同的输入固定位模式，因此回退到平台函数会在任何 libm 上失败。

### 追加：并行接触求解与批量 BVH refit

`physics_world_set_parallel_for` 让接触阶段在多个 job 上运行（`physics_task_parallel_for` 基于引擎 `TaskSystem`）。宽相配对按 BVH 子树任务并行收集，并按遍历顺序拼接；有质量刚体按配对连成岛，岛内按原顺序求解；无质量刚体与世界统计由串行重放按配对顺序写入。因此结果与串行逐位相同，与 job 数和执行顺序无关。设置接触回调、配对数低于阈值（默认 4096，可按世界设置）或只有一个岛时保持串行。两轮 BVH refit 改为先写叶子、再按节点下标倒序一次性重算内部节点，32k 刚体串行步长由 10.5 ms 降到 3.6 ms，状态哈希不变。`test_physics_parallel` 在多种 job 数与执行顺序下逐步比较串行与并行世界。

### 追加：并行积分与积分后 BVH refit（2026-11-22）

`physics_step` 的积分和积分后叶子 refit 合并为每个刚体一次 `physics_integrate_body` 加 `physics_refit_range`。非 CCD 刚体在这两步中只读写自己和自己的叶子，所以设置了 `parallel_for` 时可以按连续刚体区间分给多个 job（`physics_integrate_parallel`），每个 job 积分并写自己区间的叶子，内部节点仍由调用线程一次性重算。每个刚体执行的运算与串行循环完全相同，结果逐位一致。以下情况保持串行：
- 世界刚体数低于阈值。阈值默认 `PHYSICS_PARALLEL_MIN_BODIES`（8192），可用 `physics_world_set_parallel_min_bodies` 按世界设置；
- 有醒着的 CCD 刚体：它的扫掠读取本步已积分的刚体，串行顺序本身就是结果的一部分。

积分前的 refit 仍然串行。它只被 CCD 扫掠读取，而有 CCD 刚体时积分本就串行，拆到 job 上收益很小，也无法用测试区分对错。

在 16 线程 x86-64 上，刚体全部醒着且无接触时，每步耗时如下（串行 → 并行）：2048 个刚体 0.128 → 0.129 ms，8192 个 0.540 → 0.468 ms，32768 个 2.725 → 2.267 ms。剩余时间主要是串行的积分前 refit、内部节点 refit、配对查询和步末的 kill-floor 与睡眠检查。`test_physics_parallel` 新增 5 例：逆序 job 下 240 步逐位一致且每步只派发一次；在 `TaskSystem` worker 上逐位一致；醒着的 CCD 刚体使积分保持串行；带 CCD 刚体时接触并行、积分串行，仍逐位一致；默认阈值使测试场景保持串行。世界比较另外包含所有 BVH 节点的包围盒。

### 追加：主循环启用物理并行调度器（2026-11-22）

`engine/src/main.c` 在创建 `TaskSystem` 后调用 `physics_world_set_parallel_for(physics, physics_task_parallel_for, tasks, PHYSICS_MAX_PARALLEL_JOBS)`，在 `task_system_destroy` 前调用 `physics_world_set_parallel_for(physics, NULL, NULL, 0u)` 解除。接触求解和积分是否真的并行仍由各自的阈值决定（配对数 4096、刚体数 8192），并行结果与串行逐位相同。演示场景只有 18 个刚体，且主程序物理世界容量固定为 256，低于积分并行的默认 8192 阈值，所以仅增大当前场景也不会进入并行积分；通用 API 在更大容量、足够非 CCD 刚体和已挂接 dispatcher 时由 `test_physics_parallel` 覆盖。主程序没有独立的 8192 刚体压力模式。源码契约 `test_main_physics_dispatch_contract` 检查三件事：包含了 `physics/physics_task.h`；挂接位于 `task_system_create` 之后、第一次 `physics_step` 之前；解除位于 `task_system_destroy` 之前。
