# 动态 AI、局部避障、编组与智能对象

日期：2026-11-02

## 1. 目标与边界

本设计在现有 `break_ai` 中补齐 P3：GameThread 提交的动态障碍会改变实际 A* 可通行区域；导航版本和查询缓存拒绝陈旧结果；局部避障使用位置与速度；编组具有稳定槽位和确定性跟随；智能对象支持预约、释放和竞争拒绝；agent、障碍及其他运行对象都有创建时容量和事务式失败。

不建立第二套导航系统，不引入 RHI、渲染器、物理或 ECS 可变状态的跨线程访问。`BreakAiRuntime` 借用既有 `BreakNavMesh`，运行期障碍、查询、agent、编组和智能对象都只能在创建 runtime 的 GameThread 上调用；非 owner 调用返回 `BREAK_NAV_REJECTED`。销毁 mesh 前必须先销毁 runtime。

障碍是按 XZ 轴对齐矩形定义的运行时覆盖层。矩形覆盖其中心落在范围内的已烘焙多边形；它不是连续碰撞体，也不改变基础高度图。局部避障是固定候选集上的有界最优速度选择，不承诺替代全局路径或完整 ORCA。编组跟随负责确定性地趋向槽位，调用方可把输出速度再送入局部避障；本切片不增加编组级路径规划。智能对象每个实例只有一个当前预约者，不实现等待队列。

## 2. 方案取舍

采用“预分配 runtime 侧车 + 同一 A* 核心”。基础 mesh 和 runtime 各有一份创建时分配的 A* 工作区，动态查询额外接收每个 base poly 的阻挡计数。A* 的堆、评分、前驱和路径压缩逻辑仍由 `break_nav_query.c` 提供，旧 `break_nav_find_path` 也改为无热路径分配。

不采用“每次变化重新烘焙高度图”：它会在 GameThread 分配大块内存，使障碍更新代价与整图大小耦合，也不能自然表达重叠障碍的独立生命周期。

不采用“独立动态网格/第二套查询算法”：它会复制邻居、A*、路径上限和错误语义，增加两套实现漂移的风险。

## 3. 固定容量与所有权

```c
#define BREAK_AI_MAX_OBSTACLES 4096u
#define BREAK_AI_MAX_AGENTS 1024u
#define BREAK_AI_MAX_CACHED_PATHS 256u
#define BREAK_AI_MAX_SMART_OBJECTS 1024u
#define BREAK_AI_MAX_FORMATIONS 256u
#define BREAK_AI_MAX_FORMATION_MEMBERS 32u

typedef struct BreakAiRuntimeDesc {
    u32 max_obstacles;
    u32 max_agents;
    u32 max_cached_paths;
    u32 max_smart_objects;
    u32 max_formations;
} BreakAiRuntimeDesc;

BreakAiRuntime *break_ai_runtime_create(BreakNavMesh *mesh,
                                        const BreakAiRuntimeDesc *desc);
void break_ai_runtime_destroy(BreakAiRuntime *runtime);
```

所有容量在 create 时检查并分配；超过编译期硬上限返回 `NULL`。容量为 0 表示禁用对应对象类型。创建失败释放全部分配，不留下可观察的半对象。create 记录 owner thread；运行期不加互斥锁，也不把 OS 线程类型放进公共 AI API。

`BreakNavError` 保持原枚举值不变，在末尾增加 `BREAK_NAV_STALE` 和 `BREAK_NAV_REJECTED`。无效输入返回 `INVALID`，容量或输出空间不足返回 `OVERLOAD`，句柄或导航版本失效返回 `STALE`，跨线程、重复创建、竞争或生命周期冲突返回 `REJECTED`，合法查询无法到达返回 `FAILED`。除特别说明的 getter 外，失败不修改输出或 runtime 状态。

## 4. 动态障碍、版本和查询缓存

```c
typedef struct { u32 index, generation; } BreakAiObstacleHandle;
typedef struct { f32 min_x, min_z, max_x, max_z; } BreakAiObstacleDesc;
typedef struct { BreakNavPath path; u32 nav_version; } BreakAiPath;

BreakNavError break_ai_obstacle_add(BreakAiRuntime *, const BreakAiObstacleDesc *,
                                    BreakAiObstacleHandle *out);
BreakNavError break_ai_obstacle_update(BreakAiRuntime *, BreakAiObstacleHandle,
                                       const BreakAiObstacleDesc *);
BreakNavError break_ai_obstacle_remove(BreakAiRuntime *, BreakAiObstacleHandle);
u32 break_ai_nav_version(const BreakAiRuntime *);
BreakNavError break_ai_find_path(BreakAiRuntime *, Vec3 start, Vec3 end,
                                 u32 expected_version, BreakAiPath *out);
bool break_ai_path_is_current(const BreakAiRuntime *, const BreakAiPath *);
```

每个 base poly 保存 `u32 blocked_count`。add 先验证句柄容量、矩形、至少影响一个多边形以及版本可递增，再一次性增加计数；remove 按保存的原矩形减少同一批计数。重叠障碍不会因移除其中一个而提前开路。update 先完整验证新矩形和版本，再减少旧计数、增加新计数并替换描述；相同矩形为无操作。所有提交前检查保证失败时版本、计数、槽位和输出均不变。

导航版本初值为 1，每次有效 add/update/remove 增加 1，失败和无操作不增加；到 `UINT32_MAX` 后需要变更的操作返回 `REJECTED`，不环绕。句柄由槽 index 和 generation 组成，空槽复用时 generation 增加，旧句柄返回 `STALE`。

`break_ai_find_path` 要求 `expected_version` 等于当前版本，否则返回 `STALE`。缓存键包含精确 start/end 和版本；只有当前版本的完整匹配可命中。版本变化无需清空缓存，旧项自然不可命中并会被确定性轮转替换。成功输出携带当前版本；`FAILED/INVALID/OVERLOAD/STALE/REJECTED` 均不改 `out`。`break_ai_path_is_current` 使持有旧路径的跟随者能明确拒绝继续使用它。

动态 A* 先沿用 base component 快速排除，再把 `blocked_count != 0` 的起点、终点和邻居视为不可通行。因而整墙会真实断开路径，移除后同一 A* 可重新找到路径；不可达返回 `FAILED`，不伪造空路径或直达路径。

## 5. 无分配 A* 工作区

`BreakNavWorkspace` 在 bake/runtime create 时按 `poly_count` 分配 `gscore/fscore/came/closed/heap/chain`。`break_nav_query.c` 暴露内部共享入口：

```c
BreakNavError break_nav_find_path_workspace(const BreakNavMesh *mesh,
                                            BreakNavWorkspace *workspace,
                                            const u32 *blocked_counts,
                                            Vec3 start, Vec3 end,
                                            BreakNavPath *out);
```

旧公共查询传入 mesh 自有工作区和 `NULL` 阻挡表；动态查询传入 runtime 工作区和计数表。查询过程只使用调用栈上的定长数组和已分配工作区，不调用 `malloc/calloc/realloc/free`。

## 6. 带速度的有界局部避障与 agent

```c
typedef struct { Vec3 position, velocity; f32 radius; } BreakSteerAgent;
typedef struct {
    Vec3 position, velocity;
    f32 radius, max_speed;
} BreakAiAgentDesc;

BreakNavError break_steer_avoid_velocity(
    Vec3 self, Vec3 self_velocity, f32 self_radius, f32 max_speed,
    Vec3 desired_velocity, const BreakSteerAgent *neighbors, u32 count,
    f32 horizon, Vec3 *out_velocity);

BreakNavError break_ai_agent_add(BreakAiRuntime *, Entity, const BreakAiAgentDesc *);
BreakNavError break_ai_agent_update(BreakAiRuntime *, Entity, const BreakAiAgentDesc *);
BreakNavError break_ai_agent_remove(BreakAiRuntime *, Entity);
BreakNavError break_ai_agent_avoid(BreakAiRuntime *, Entity self,
                                   Vec3 desired_velocity, f32 horizon,
                                   Vec3 *out_velocity);
```

新避障函数最多接收 `BREAK_STEER_MAX_NEIGHBORS` 个邻居，超限返回 `OVERLOAD`，不再静默截断。候选包括期望速度、当前速度、零速度，以及以期望方向为基准的固定角度/速度采样。每个候选按“与期望速度偏差 + 预测碰撞代价”评分；预测使用 `candidate - neighbor.velocity` 的相对速度和 horizon 内最近距离。固定候选顺序解决同分，输出速度长度不超过 `max_speed`。所有输入必须有限，半径/速度/horizon 必须合法，失败不改输出。

runtime 以带 generation 的 `Entity` 作为 agent 身份。重复 add 返回 `REJECTED`，未知 update/remove/avoid 返回 `STALE`，容量满返回 `OVERLOAD`。agent avoid 确定性地选择最近 16 个邻居，距离同分按 Entity index/generation 排序，然后调用同一速度避障函数。agent 若仍属于编组或持有智能对象预约，remove 返回 `REJECTED`，避免遗留悬空拥有者。

旧 `break_steer_avoid` 保留以兼容已有调用；新行为只由显式速度 API 提供。

## 7. 编组槽位与确定性跟随

```c
typedef struct { u32 index, generation; } BreakAiFormationHandle;

BreakNavError break_ai_formation_create(BreakAiRuntime *, const Entity *members,
                                        u32 member_count, f32 spacing,
                                        BreakAiFormationHandle *out);
BreakNavError break_ai_formation_destroy(BreakAiRuntime *, BreakAiFormationHandle);
BreakNavError break_ai_formation_slots(BreakAiRuntime *, BreakAiFormationHandle,
                                       Vec3 leader_position, Vec3 leader_forward,
                                       Vec3 *out_slots, u32 cap, u32 *out_count);
BreakNavError break_ai_formation_tick(BreakAiRuntime *, BreakAiFormationHandle,
                                      f32 dt, Vec3 *out_velocities,
                                      u32 cap, u32 *out_count);
```

成员顺序就是稳定槽位顺序，0 号是 leader。create 要求 1..32 个已注册且不重复的 agent、正有限 spacing；任何失败均不占用 formation 槽。槽位使用 XZ 平面 wedge：leader 在自身位置，后续成员按行在 leader 后方左右交替；无效/近零 forward 确定性回退到 +X。

slots 是纯计算。tick 从 leader 当前 agent 位置/速度得到编组框架，leader 输出其当前速度；跟随者使用既有 `break_nav_follow_wish` 的到达半径和限速语义趋向各自槽位，位移除以 `dt` 得到不超过 agent `max_speed` 的速度。输出严格按创建时成员顺序排列，重复调用和同输入重放得到相同结果。输出容量不足、无效 dt 或 stale handle 不改输出。

## 8. 智能对象预约

```c
typedef struct { u32 index, generation; } BreakAiSmartObjectHandle;

BreakNavError break_ai_smart_object_add(BreakAiRuntime *, Vec3 position,
                                        BreakAiSmartObjectHandle *out);
BreakNavError break_ai_smart_object_remove(BreakAiRuntime *,
                                           BreakAiSmartObjectHandle);
BreakNavError break_ai_smart_object_reserve(BreakAiRuntime *,
                                            BreakAiSmartObjectHandle, Entity agent);
BreakNavError break_ai_smart_object_release(BreakAiRuntime *,
                                            BreakAiSmartObjectHandle, Entity agent);
BreakNavError break_ai_smart_object_owner(BreakAiRuntime *,
                                          BreakAiSmartObjectHandle, Entity *out_owner);
```

对象位置由 add 保存，句柄含 generation。reserve 要求已注册 agent：空闲对象预约成功，同一 agent 重复预约幂等成功，另一 agent 竞争返回 `REJECTED` 且原拥有者不变。release 只接受当前拥有者；错误拥有者返回 `REJECTED`。owner 查询在空闲时返回 `ENTITY_NULL`。已预约对象不能 remove，持有预约的 agent 不能 remove；这些冲突不会清掉原预约。

## 9. 测试与变异证据

新增 focused 测试分别覆盖：

- 动态墙阻路、移除重新开路、无路径、重叠障碍、矩形更新和失败原子性。
- 版本递增、旧 expected version/旧路径拒绝、缓存不能跨版本命中、失败输出不变。
- agent/障碍/编组/智能对象容量，重复身份、stale generation 和 owner-thread 拒绝。
- 移动邻居的相对速度避障、速度上限、邻居上限、确定性及实际模拟不碰撞。
- wedge 槽位、成员顺序、跟随收敛、容量失败和相同输入重放。
- 预约竞争、同者幂等、错误释放、释放后重新预约和生命周期冲突。
- 源合同确认查询/避障/编组/预约热文件没有分配调用，`break_ai` 不包含 RHI，也未链入核心消费者。

至少在 normal 树上做四项临时变异并看到对应测试变红：忽略导航 expected version；让动态 A* 不检查阻挡计数；竞争 reserve 直接覆盖 owner；容量满错误被改成其他状态。变异后立即恢复并重跑。normal、ASan+UBSan、TSan 均用 `-j3` 构建并运行所有 `break_ai` focused 测试及旧 Cry 原型测试。最终进行只读评审或自审，修复 Critical/Important 后再提交报告。

## 10. 限制

本实现不承诺任意形状连续障碍的精确侵蚀；调用方需按 agent 半径烘焙基础 mesh，并用网格尺度合适的动态矩形。固定候选局部避障在极度拥挤时只能给出评分最优的有界速度，不是全局无死锁保证。编组不会自动为每个槽位规划独立 A* 路径。未运行 Windows 或真机图形验证；P3 的验证目标是确定性 CPU/headless 行为。
