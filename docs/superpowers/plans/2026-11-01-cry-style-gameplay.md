# Cry 式游戏能力补齐 Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:executing-plans (or subagent-driven-development) to implement this plan task by task. Steps use checkbox (`- [x]`) syntax for tracking.

**Goal:** 按 [`docs/design/core_style_runtime.md`](../../design/core_style_runtime.md) 补齐可玩原型（游戏内核、导航与行为、运动混合），再分别补世界表现和布娃娃/载具。本文是实施计划；设计合同以该文档为准。

文末完成定义已满足：下面的步骤都已落地。再开目标时以新的完成定义为准，不要把容量上限当成未完成的计划步骤。

**Architecture:** `break_game` 与 `break_ai` 是正式可选 C11 静态库，不链入 `engine` / `engine_demo` / `dxx_break`。关卡字节和导航烘焙输入都由宿主回调或纯 CPU 缓冲喂入，这两个库不包含 RHI。动画与物理增量落在现有 `engine/src/animation` 和 `engine/src/physics`。植被、昼夜、VisArea、地形块落在 `engine/src/renderer`。

**Tech Stack:** C11；现有 ECS（`engine/src/ecs/ecs.h`）、`InputState`（`engine/src/platform/input.h`）、`PhysicsWorld` / `CharacterController`、`AnimBlendState`、`scene_serial`（仅集成层调用）、CTest、ASan/UBSan/TSan。

## Global Constraints

- 开始写代码前以设计文档第 4–10 节为合同。本计划的接口块是该合同的 C 表面，实现时可以加静态函数，不能加设计文档范围外的系统（武器、Flow Graph、RVO、布料、语音、CVar）。
- TDD：每个任务先写失败测试，确认红，再实现到绿。
- 新库顶层放在 `engine/CMakeLists.txt`，`ENGINE_BUILD_TESTS=OFF` 时也产出。每个新库配一个 `test_*_target_contract.cmake`，断言不在 `engine`、`engine_demo`、`dxx_break` 的链接行上，且生产归档没有测试钩子符号。
- 容量用尽返回各库的 `OVERLOAD`。失败路径不部分提交：要么状态前进，要么与调用前字节级一致（测试钉住）。
- Game 线程约定与 `break_lua` 相同：create 记录 owner 线程，跨线程调用返回 `REJECTED`。不给这些对象加互斥锁。
- 热路径（`tick`、`physics_step`、寻路、混合评估）不调用 `malloc`。上限在 create 时一次分配。
- 三棵树：normal、`ENGINE_USE_ASAN`+UBSan、`ENGINE_USE_TSAN`。阶段 A–C 与 E 的 focused 测试不链渲染后端。阶段 D 的 CPU 裁剪测试同样不链 GPU；只有植被绘制和昼夜 uniform 写入才进 graphics 标签。
- 每个阶段结束时在 `docs/Implementation_Status.md` 顶部追加一条，列出测试名和未交付边界。不要把设计文档改成“已交付”，除非该阶段的三棵树已经跑过。
- 一个任务一次提交。提交说明用仓库现有语气，写为什么。

## 依赖

A 完成后再开始 B 和 C。B 与 C 可以并行。F 等 B 和 C 都绿。D 与 E 等 F 的原型测试绿，然后彼此并行。不要为了 D 或 E 回头改 A 的公共结构体布局；要加字段就新版本化侧车，并让旧测试仍通过。

---

## 阶段 A：游戏内核（`break_game`）

### Task A1: 库骨架与 Actor 类注册

**Files:**

- Create: `engine/src/game/break_game.h`
- Create: `engine/src/game/break_game.c`
- Create: `engine/tests/test_break_game_actor.c`
- Modify: `engine/CMakeLists.txt`

**Interfaces:**

```c
typedef enum BreakGameError {
    BREAK_GAME_OK = 0,
    BREAK_GAME_INVALID,
    BREAK_GAME_CLOSED,
    BREAK_GAME_OVERLOAD,
    BREAK_GAME_OOM,
    BREAK_GAME_TIMEOUT,
    BREAK_GAME_STALE,
    BREAK_GAME_REJECTED,
    BREAK_GAME_FAILED
} BreakGameError;

typedef struct BreakGame BreakGame;

typedef struct BreakGameConfig {
    u32 max_classes;   /* 0 => 64，硬上限 64 */
    u32 max_actors;    /* 0 => 4096，硬上限 4096 */
} BreakGameConfig;

typedef struct BreakGameClassDesc {
    const char *name;                 /* 1..63 字节，NUL 结尾 */
    const ComponentType *components;  /* 生成时按序 add */
    u32 component_count;              /* 硬上限 16 */
    const char *lua_module;           /* 可为 NULL */
} BreakGameClassDesc;

BreakGame *break_game_create(World *world, const BreakGameConfig *config);
void       break_game_destroy(BreakGame *game);

BreakGameError break_game_register_class(BreakGame *game,
                                         const BreakGameClassDesc *desc,
                                         u32 *out_class_id);
```

- [x] 写失败测试：create/destroy；超硬上限的 config 返回 NULL；重名类 `REJECTED`；第 65 个类 `OVERLOAD`；组件数 17 `INVALID`；空名字 `INVALID`；`out_class_id` 从 1 起单调递增。跨线程 register 返回 `REJECTED`（测试里用一个记录过 owner 的探针，第二线程只在 `BREAK_GAME_TESTING` 下编译）。
- [x] 跑测试，确认红。
- [x] 实现 create 时一次分配类表和 Actor 槽。`world` 只借用，destroy 不销毁 `World`。
- [x] 加 target contract 并在 `ENGINE_BUILD_TESTS=OFF` 的树上确认库存在且未被 `engine` 链接。
- [x] normal / ASan+UBSan / TSan 三棵树 focused 测试通过。

### Task A2: 生成、销毁、脚本 tick 槽

**Files:**

- Modify: `engine/src/game/break_game.h`
- Modify: `engine/src/game/break_game.c`
- Create: `engine/src/game/break_game_actor.c`
- Modify: `engine/tests/test_break_game_actor.c`

**Interfaces:**

```c
typedef void (*BreakGameTickFn)(BreakGame *game, Entity entity, f32 dt, void *user);

typedef struct BreakGameSpawn {
    u32 class_id;
    Vec3 position;
} BreakGameSpawn;

BreakGameError break_game_spawn(BreakGame *game, const BreakGameSpawn *spawn, Entity *out_entity);
BreakGameError break_game_despawn(BreakGame *game, Entity entity);
void           break_game_set_tick(BreakGame *game, u32 class_id, BreakGameTickFn fn, void *user);
void           break_game_tick(BreakGame *game, f32 dt);
```

- [x] 写失败测试：spawn 创建的实体带有类声明的全部组件且字节为 0，位置组件写上 `spawn.position`（约定组件 0 是 3 个 `f32` 的位置，测试在 register 前 `world_register_component`）；未知 class id `STALE`；满 4096 `OVERLOAD` 且 `World` 实体数不变；despawn 后同一 Entity 值 `STALE`；generation 复用后旧 Entity 值仍然 `STALE`；tick 只调用存活实例，dt 原样传入；despawn 发生在 tick 回调里时，本次 tick 不再访问该槽（测试用回调里 despawn 自己，ASan 树必须干净）。
- [x] 确认红，然后实现。tick 开始时复制一张存活 id 快照（固定数组，create 时分配），回调只服务快照。
- [x] Lua 模块名只存储，不在本任务创建 `lua_State`。绑定现有 `break_lua` 是 Task F1。
- [x] 三棵树通过。

### Task A3: ActionMap

**Files:**

- Create: `engine/src/game/break_game_actions.c`
- Modify: `engine/src/game/break_game.h`
- Create: `engine/tests/test_break_game_actions.c`
- Modify: `engine/CMakeLists.txt`

**Interfaces:**

```c
typedef enum BreakGameBindSource {
    BREAK_GAME_BIND_KEY = 1,
    BREAK_GAME_BIND_MOUSE_BUTTON,
    BREAK_GAME_BIND_MOUSE_AXIS,   /* 0 = dx, 1 = dy, 2 = wheel */
    BREAK_GAME_BIND_PAD_BUTTON,
    BREAK_GAME_BIND_PAD_AXIS
} BreakGameBindSource;

typedef struct BreakGameBinding {
    BreakGameBindSource source;
    i32 code;          /* 键/按钮/轴编号，含义与 InputState 一致 */
    i32 pad;           /* 仅手柄；其它源必须为 0 */
    f32 scale;         /* 数字量按下时贡献 scale；轴贡献 raw * scale */
} BreakGameBinding;

typedef struct BreakGameActionDesc {
    const char *name;
    const BreakGameBinding *bindings;
    u32 binding_count;             /* 硬上限 8 */
} BreakGameActionDesc;

typedef struct BreakGameActionValue {
    bool down;
    f32 axis;
} BreakGameActionValue;

BreakGameError break_game_bind_actions(BreakGame *game,
                                       const BreakGameActionDesc *actions,
                                       u32 count);
BreakGameError break_game_eval_actions(BreakGame *game, const InputState *input,
                                       BreakGameActionValue *out, u32 cap);
```

- [x] 写失败测试：64 个动作可绑定，第 65 个整表拒绝且旧表不变；一个动作 9 个绑定 `INVALID` 且旧表不变；键按下时 `down` 为真且 axis 等于 scale；正负轴相加后钳到 [-1, 1]；`cap` 小于已绑定数量返回 `OVERLOAD` 且不写 `out`；替换绑定后旧键不再产生动作。
- [x] 确认红，然后实现。`break_game_eval_actions` 不分配。
- [x] 三棵树通过。

### Task A4: 移动适配

**Files:**

- Create: `engine/src/game/break_game_move.c`
- Modify: `engine/src/game/break_game.h`
- Create: `engine/tests/test_break_game_move.c`

**Interfaces:**

```c
typedef struct BreakGameMoveInput {
    f32 forward;     /* [-1, 1] */
    f32 strafe;      /* [-1, 1] */
    f32 camera_yaw;  /* 弧度，0 朝向 +Z */
    bool jump;
} BreakGameMoveInput;

typedef struct BreakGameMoveOutput {
    Vec3 wish;       /* 世界 XZ，y = 0，长度不超过 1 */
    bool jump;
    f32 yaw;
} BreakGameMoveOutput;

BreakGameError break_game_move_wish(const BreakGameMoveInput *in, BreakGameMoveOutput *out);
```

- [x] 写失败测试：yaw 0、forward 1 得到 +Z；yaw 为 π/2、forward 1 得到 +X（误差 1e-5）；strafe 与 forward 同时为 1 时 wish 长度为 1；NaN 输入 `INVALID` 且 `out` 不变。
- [x] 确认红，然后实现。本任务不调用 `character_update`；集成测试放在 F1。
- [x] 三棵树通过。

### Task A5: 关卡加载侧车

**Files:**

- Create: `engine/src/game/break_game_level.c`
- Modify: `engine/src/game/break_game.h`
- Create: `engine/tests/test_break_game_level.c`

**Interfaces:**

```c
typedef BreakGameError (*BreakGameLevelLoadFn)(void *user, World *world, const char *path);
typedef void (*BreakGameLevelUnloadFn)(void *user, World *world);

typedef struct BreakGameLevelHooks {
    BreakGameLevelLoadFn load;
    BreakGameLevelUnloadFn unload;
    void *user;
} BreakGameLevelHooks;

BreakGameError break_game_level_open(BreakGame *game, const BreakGameLevelHooks *hooks,
                                     const char *scene_path, const char *actor_sidecar);
BreakGameError break_game_level_close(BreakGame *game);
```

侧车是 UTF-8 文本：每行 `entity_index class_name`，`#` 开头为注释，空行跳过。硬上限 4096 行、文件 1 MiB。

- [x] 写失败测试：load 回调被调用一次且路径原样传入；回调失败时 Actor 数仍为 0 且内核无“已加载”标记；侧车两行把对应实体登记成已注册类（测试预先 `world_create_entity`）；未知类名整份失败且不保留部分登记；重复 open `REJECTED`；close 调用 unload 并 despawn 内核登记的 Actor，不销毁宿主额外创建的实体；第二个关卡在 close 之后可以 open。
- [x] 确认红，然后实现。解析用调用方栈上的有界缓冲，失败时已 spawn 的本批 Actor 全部 despawn。
- [x] 三棵树通过。

### Task A6: Area 触发区

**Files:**

- Create: `engine/src/game/break_game_area.c`
- Modify: `engine/src/game/break_game.h`
- Create: `engine/tests/test_break_game_area.c`

**Interfaces:**

```c
typedef enum BreakGameAreaEvent {
    BREAK_GAME_AREA_ENTER = 1,
    BREAK_GAME_AREA_LEAVE = 2
} BreakGameAreaEvent;

typedef struct BreakGameAreaDesc {
    Vec3 center;
    Vec3 half_extent;  /* 任一分量 > 0 则为 AABB；全 0 则用 radius */
    f32 radius;
} BreakGameAreaDesc;

typedef void (*BreakGameAreaFn)(u32 area_id, Entity entity, BreakGameAreaEvent event, void *user);

BreakGameError break_game_area_add(BreakGame *game, const BreakGameAreaDesc *desc, u32 *out_id);
void           break_game_set_area_callback(BreakGame *game, BreakGameAreaFn fn, void *user);
BreakGameError break_game_area_tick(BreakGame *game);
```

位置读 Actor 的位置组件。滞回 0.25 m：进入用体积边界，离开用边界再外扩 0.25 m。

- [x] 写失败测试：从外走进盒子得到一次 ENTER；停在内部再 tick 不产生事件；走出外扩边界得到一次 LEAVE；在边界 0.1 m 内往返不产生第二对事件；第 257 个区域 `OVERLOAD`；已 despawn 的 Actor 不再产生 LEAVE 以外的事件（despawn 本身补一次 LEAVE，且只一次）。
- [x] 确认红，然后实现。每区域一份定长 inside 位图，create 时按 `max_actors` 分配。
- [x] 三棵树通过。阶段 A 结束时更新 `docs/Implementation_Status.md`：写明 `break_game` 未链入 `engine`，Lua 模块名尚未执行。

---

## 阶段 B：导航与行为（`break_ai`）

`break_ai` 只依赖 `core`、`math` 和物理查询所需的最小声明。不要包含 `renderer/terrain.h`。高度图输入是下面的 POD。

### Task B1: 高度图烘焙成导航块

**Files:**

- Create: `engine/src/ai/break_ai.h`
- Create: `engine/src/ai/break_nav_bake.c`
- Create: `engine/tests/test_break_nav_bake.c`
- Modify: `engine/CMakeLists.txt`

**Interfaces:**

```c
typedef struct BreakNavHeightfield {
    const f32 *heights; /* row-major，格子 (z * width + x) */
    u32 width;
    u32 depth;
    f32 origin_x;
    f32 origin_z;
    f32 cell;
    f32 height_scale;
} BreakNavHeightfield;

typedef struct BreakNavMesh BreakNavMesh;

BreakNavMesh *break_nav_bake_heightfield(const BreakNavHeightfield *field,
                                         f32 walkable_slope_deg, f32 agent_radius);
void          break_nav_mesh_destroy(BreakNavMesh *mesh);
```

烘焙规则：相邻格子高度差形成的坡度大于 `walkable_slope_deg` 的边不可走；可走格子按 32 m 块合并成多边形（本任务允许一格一多边形，合并是优化，测试不要求合并数量）。`agent_radius` 把可走区域向内缩，缩完断开的格子保持不可走。

- [x] 写失败测试：平坦 64×64、cell 1 m 的高度图烘焙出可查询的块；中间一排高度 +10 m 的墙把左右分成不连通的两侧（用 B2 的连通查询，本任务先暴露 `break_nav_same_component` 测试探针，或在本任务写出两个多边形中心之间是否共享块邻接）；坡度恰好等于阈值可走，超过阈值不可走；`width*depth` 溢出或超过 1024×1024 `OVERLOAD`（返回 NULL）；NULL 高度指针返回 NULL。
- [x] 确认红，然后实现。分配只发生在 bake/destroy。
- [x] target contract 与三棵树。

### Task B2: A* 与漏斗拉直

**Files:**

- Create: `engine/src/ai/break_nav_query.c`
- Modify: `engine/src/ai/break_ai.h`
- Create: `engine/tests/test_break_nav_query.c`

**Interfaces:**

```c
typedef struct BreakNavPath {
    Vec3 points[256];
    u32 count;
} BreakNavPath;

typedef enum BreakNavError {
    BREAK_NAV_OK = 0,
    BREAK_NAV_INVALID,
    BREAK_NAV_OVERLOAD,
    BREAK_NAV_FAILED
} BreakNavError;

BreakNavError break_nav_find_path(const BreakNavMesh *mesh, Vec3 start, Vec3 end,
                                  BreakNavPath *out);
```

- [x] 写失败测试：无障碍时路径端点是起终点，中间点偏离直线不超过一个格子；墙两侧 `FAILED` 且 `out->count` 保持调用前的值；绕行墙时折线不穿过墙段（用高度图里那排墙的 AABB 做线段测试）；起终点在网格外 `FAILED`；强制一条需要超过 256 个拐点的走廊返回 `OVERLOAD`（测试构造一条锯齿通道，或在 `BREAK_AI_TESTING` 下把拐点上限降到 4）。
- [x] 确认红，然后实现。开放表是定长二叉堆，容量等于多边形上限，满则 `OVERLOAD`。
- [x] 三棵树通过。

### Task B3: 路径跟随

**Files:**

- Create: `engine/src/ai/break_nav_follow.c`
- Modify: `engine/src/ai/break_ai.h`
- Create: `engine/tests/test_break_nav_follow.c`

**Interfaces:**

```c
typedef struct BreakNavFollower {
    BreakNavPath path;
    u32 cursor;
    f32 arrive_radius;
} BreakNavFollower;

void break_nav_follow_reset(BreakNavFollower *f, const BreakNavPath *path, f32 arrive_radius);
Vec3 break_nav_follow_wish(BreakNavFollower *f, Vec3 position, f32 speed, f32 dt);
bool break_nav_follow_arrived(const BreakNavFollower *f);
```

`wish` 是本帧位移，长度不超过 `speed * dt`。到达当前点的 `arrive_radius` 后 cursor 前进。

- [x] 写失败测试：沿两个点走完后 arrived 为真且 wish 为 0；速度 0 不推进 cursor；dt 为负或 NaN 时 wish 为 0 且 cursor 不变。
- [x] 确认红，然后实现。
- [x] 三棵树通过。

### Task B4: 视野感知

**Files:**

- Create: `engine/src/ai/break_perception.c`
- Modify: `engine/src/ai/break_ai.h`
- Create: `engine/tests/test_break_perception.c`

**Interfaces:**

```c
typedef struct BreakSight {
    Vec3 eye;
    Vec3 forward;     /* 调用方保证近似单位长度；否则 INVALID */
    f32 distance;
    f32 half_angle_rad;
} BreakSight;

typedef struct BreakSightTarget {
    Entity entity;
    Vec3 point;
} BreakSightTarget;

typedef bool (*BreakSightRayFn)(void *user, Vec3 from, Vec3 to);

BreakNavError break_sight_query(const BreakSight *sight,
                                const BreakSightTarget *targets, u32 target_count,
                                BreakSightRayFn ray_clear, void *user,
                                Entity *out_visible, u32 cap, u32 *out_count);
```

`ray_clear` 返回 true 表示线段上没有遮挡。本任务不链接 `PhysicsWorld`；F1 用 `physics_raycast` 包一层适配器。

- [x] 写失败测试：锥外目标不出现；锥内但 ray 返回 false 的目标不出现；锥内且 ray 为 true 的目标按输入顺序写出；`target_count` 9 返回 `OVERLOAD`（上限 8）且 `out_count` 不变；`cap` 小于可见数时写出 `cap` 个并返回 `OVERLOAD`。
- [x] 确认红，然后实现。
- [x] 三棵树通过。

### Task B5: 行为树与黑板

**Files:**

- Create: `engine/src/ai/break_behavior.c`
- Modify: `engine/src/ai/break_ai.h`
- Create: `engine/tests/test_break_behavior.c`

**Interfaces:**

```c
typedef struct BreakBlackboard {
    Entity target;
    Vec3 last_seen;
    bool seen;
    bool attack;
} BreakBlackboard;

typedef enum BreakNodeKind {
    BREAK_NODE_SELECTOR = 1,
    BREAK_NODE_SEQUENCE,
    BREAK_NODE_LEAF
} BreakNodeKind;

typedef enum BreakLeafKind {
    BREAK_LEAF_IDLE = 1,
    BREAK_LEAF_CHASE,
    BREAK_LEAF_ATTACK
} BreakLeafKind;

typedef struct BreakNode {
    BreakNodeKind kind;
    BreakLeafKind leaf;   /* 仅 LEAF */
    u16 child_begin;
    u16 child_count;
} BreakNode;

typedef enum BreakBehaveStatus {
    BREAK_BEHAVE_SUCCESS = 1,
    BREAK_BEHAVE_FAILURE,
    BREAK_BEHAVE_RUNNING
} BreakBehaveStatus;

typedef struct BreakBehaveResult {
    BreakBehaveStatus status;
    Vec3 wish;            /* CHASE 时由跟随器填，其它叶子为 0 */
    bool attack;
} BreakBehaveResult;

BreakBehaveStatus break_behavior_tick(const BreakNode *nodes, u32 node_count, u32 root,
                                      BreakBlackboard *board,
                                      BreakNavFollower *follower,
                                      Vec3 self_position, f32 dt,
                                      BreakBehaveResult *out);
```

树的形状由测试写死：选择（序列（能看见则刷新 last_seen，然后 CHASE），ATTACK 当距离 < 1.5 m，否则 IDLE）。叶子语义：IDLE 成功且 wish 为 0；CHASE 在未到达时 RUNNING 并写出 wish，到达则 SUCCESS；ATTACK 在距离 < 1.5 m 时 SUCCESS 且 `attack` 为真，否则 FAILURE。

- [x] 写失败测试：看不见且没有 last_seen 时 IDLE；看见时黑板记下目标点且 wish 指向路径；距离 1 m 且看见时 ATTACK 为真、wish 为 0；节点索引越界返回 FAILURE 且黑板不变。
- [x] 确认红，然后实现。选择节点返回第一个非 FAILURE 的子节点。序列在 FAILURE 处停下。
- [x] 三棵树通过。

### Task B6: 胶囊侧向避障

**Files:**

- Create: `engine/src/ai/break_steer.c`
- Modify: `engine/src/ai/break_ai.h`
- Create: `engine/tests/test_break_steer.c`

**Interfaces:**

```c
typedef struct BreakSteerNeighbor {
    Vec3 position;
    f32 radius;
} BreakSteerNeighbor;

Vec3 break_steer_avoid(Vec3 self, f32 self_radius, Vec3 wish,
                       const BreakSteerNeighbor *neighbors, u32 count);
```

`count` 硬上限 16，超出时忽略多出来的并保持函数纯值返回（测试通过长度和方向断言，不报错码）。

- [x] 写失败测试：无邻居时 wish 原样返回；正前方重叠的邻居把结果推向侧向，且结果不再指向邻居中心（点积小于原 wish 与指向邻居的单位向量的点积）；半径为 0 的邻居忽略。
- [x] 确认红，然后实现。
- [x] 三棵树通过，并更新 `docs/Implementation_Status.md`：导航是离线烘焙、运行时不雕刻；无群组、无智能对象。

---

## 阶段 C：运动混合、挂点、瞄准

改现有动画模块。保持 `anim_blend_evaluate` 的输出数组布局。

### Task C1: 一维速度混合

**Files:**

- Modify: `engine/src/animation/animation.h`
- Create: `engine/src/animation/anim_locomotion.c`
- Create: `engine/tests/test_anim_locomotion.c`
- Modify: `engine/CMakeLists.txt`（测试目标；源文件加入现有 engine 动画列表）

**Interfaces:**

```c
#define ANIM_LOCO_SAMPLES 4

typedef struct AnimLocoSample {
    f32 speed;
    u32 clip_index;
} AnimLocoSample;

typedef struct AnimLoco1D {
    AnimLocoSample samples[ANIM_LOCO_SAMPLES];
    u32 count;
    u32 layer;
} AnimLoco1D;

bool anim_loco1d_init(AnimLoco1D *loco, u32 layer,
                      const AnimLocoSample *samples, u32 count);
void anim_loco1d_apply(const AnimLoco1D *loco, AnimBlendState *state, f32 speed);
```

`init` 要求 speed 严格递增且 count 为 2..4。`apply` 把权重写到 `layer` 以及调用方预先 `anim_layer_play` 好的相邻层约定：本任务只用 `loco->layer` 一个层播放权重最高的剪辑，并把次高剪辑的权重写进 `layer+1`（调用方保证 `layer+1 < ANIM_MAX_LAYERS`）。速度低于第一样本时只用第一样本；高于最后样本时只用最后样本。

- [x] 写失败测试：速度不递增时 init 返回 false 且对象字节不变；速度位于两样本中点时两层权重都在 0.5±1e-4；速度等于跑步样本时跑步层权重为 1、步行层为 0。
- [x] 确认红，然后实现。
- [x] 三棵树通过。

### Task C2: 挂点

**Files:**

- Modify: `engine/src/animation/skeleton.h`
- Create: `engine/src/animation/skeleton_socket.c`
- Create: `engine/tests/test_skeleton_socket.c`

**Interfaces:**

```c
#define SKELETON_MAX_SOCKETS 32

typedef struct SkeletonSocket {
    char name[32];
    u32 joint;
    Vec3 local_offset;
    bool used;
} SkeletonSocket;

bool skeleton_socket_set(Skeleton *sk, const char *name, u32 joint, Vec3 local_offset);
bool skeleton_socket_get(const Skeleton *sk, const char *name, Vec3 *out_world);
```

`get` 使用 `current_pose[joint]`。未知名字或 joint 越界返回 false，不写 `out_world`。

- [x] 写失败测试：单位矩阵关节加偏移 (0,1,0) 得到该世界点；覆盖同名挂点后用新关节；第 33 个名字返回 false 且前 32 个仍可查询。
- [x] 确认红，然后实现。
- [x] 三棵树通过。

### Task C3: 瞄准与注视槽

**Files:**

- Modify: `engine/src/animation/animation.h`
- Modify: `engine/src/animation/animation.c`（只加两个薄封装，求解仍走 `anim_ik_set_target`）
- Create: `engine/tests/test_anim_aim.c`

**Interfaces:**

```c
typedef enum AnimIkSlot {
    ANIM_IK_SLOT_AIM = 0,
    ANIM_IK_SLOT_LOOK = 1
} AnimIkSlot;

void anim_ik_set_slot(IKSystem *ik, AnimIkSlot slot,
                      u32 root, u32 mid, u32 tip,
                      Vec3 target, Vec3 pole, f32 weight);
```

槽位固定占用 `IKTarget` 下标 0 和 1。`root/mid/tip` 任一 ≥ 64 时函数不修改该槽（层遮罩表达不了这些关节，瞄准链必须落在可遮罩范围）。

- [x] 写失败测试：设置 AIM 后 `targets[0]` 的关节和权重与参数一致，`targets[1]` 仍为未激活；关节 64 被拒绝且槽保持原值；权重 0 时 `anim_ik_solve` 不改局部旋转（用一条已知两骨链做前后比较）。
- [x] 确认红，然后实现。
- [x] 三棵树通过。更新 `docs/Implementation_Status.md`：无变形、无面部、无压缩、IK 不读物理。

---

## 阶段 F：可玩原型（B 与 C 都绿之后）

### Task F1: headless 关卡脚本

**Files:**

- Create: `engine/tests/test_cry_style_prototype.c`
- Modify: `engine/CMakeLists.txt`

测试自己搭 `World`、`PhysicsWorld`、`BreakGame`、`BreakNavMesh`、`AnimLoco1D`，不打开窗口。

- [x] 地面是一个静态盒子。玩家 Actor 用 Task A4 的 wish 驱动 `character_update`，前进轴为 1、yaw 为 0、dt 累计 3 秒后水平位移 > 2 m。
- [x] 高度图中间有一堵墙。敌人起点和玩家起点分居墙的两侧开口。`break_nav_find_path` 的长度大于两点直线距离。行为树在 `BreakSightRayFn` 返回真时走出非零 wish。
- [x] 速度 0 时步行剪辑权重高于跑步；速度等于跑步样本时相反。
- [x] 触发区：玩家坐标从区外步进区内，回调恰好一次 ENTER；再步进到滞回外，恰好一次 LEAVE。
- [x] 三棵树通过。更新 `docs/Implementation_Status.md` 和设计文档第 1 节的状态句：可玩原型已交付，D/E 仍是设计-only。同时写明此测试没有 GPU、没有声音、没有网络。

---

## 阶段 D：世界表现与流式（F 绿之后，可与 E 并行）

### Task D1: 植被实例

**Files:**

- Create: `engine/src/renderer/vegetation.h`
- Create: `engine/src/renderer/vegetation.c`
- Create: `engine/tests/test_vegetation.c`

**Interfaces:**

```c
typedef struct VegetationDesc {
    const u8 *density; /* 与地形格子对齐，0 表示不放 */
    u32 width;
    u32 depth;
    f32 cell;
    u32 prototype_count; /* 1..8，density % prototype_count 选原型 */
} VegetationDesc;

typedef struct VegetationInstance {
    Vec3 position;
    u32 prototype;
} VegetationInstance;

typedef struct VegetationBuild {
    VegetationInstance *instances; /* 调用方缓冲 */
    u32 capacity;
    u32 count;
    u32 dropped;
} VegetationBuild;

bool vegetation_build(const VegetationDesc *desc, const f32 *heights, f32 height_scale,
                      VegetationBuild *out);
```

- [x] 写失败测试：全 0 密度得到 0 实例；一个非零格子得到 1 个实例且 y 等于该格高度；容量小于非零格子数时 `count == capacity` 且 `dropped` 为差值；`width*depth` 溢出返回 false。
- [x] 确认红，然后实现 CPU 构建。GPU 绘制另开 graphics 测试，只断言实例缓冲字节数，不作为本任务门槛。
- [x] CPU 测试三棵树通过。

### Task D2: 昼夜参数

**Files:**

- Create: `engine/src/renderer/time_of_day.h`
- Create: `engine/src/renderer/time_of_day.c`
- Create: `engine/tests/test_time_of_day.c`

**Interfaces:**

```c
typedef struct TimeOfDayLighting {
    Vec3 sun_dir;
    Vec3 sun_color;
    Vec3 ambient;
    f32 fog;
} TimeOfDayLighting;

void time_of_day_eval(f32 seconds, f32 day_length, TimeOfDayLighting *out);
```

`day_length` ≤ 0 时按 1 处理。`seconds` 对 `day_length` 取模。正午（周期的 0.5）太阳在 +Y，颜色偏白；午夜太阳在 -Y，太阳颜色为 0，环境色为测试钉住的常数。

- [x] 写失败测试：`seconds` 0 与 `day_length` 得到同一结果；正午 `sun_dir.y > 0.9`；午夜 `sun_color` 长度为 0；输出无 NaN。
- [x] 确认红，然后实现。接入地形 uniform 的渲染测试标 graphics，不阻塞本任务。
- [x] 三棵树通过。

### Task D3: VisArea / Portal

**Files:**

- Create: `engine/src/renderer/visarea.h`
- Create: `engine/src/renderer/visarea.c`
- Create: `engine/tests/test_visarea.c`

**Interfaces:**

```c
typedef struct VisPortal {
    Vec3 center;
    Vec3 half_extent;
    u32 neighbor_room; /* UINT32_MAX 表示室外 */
} VisPortal;

typedef struct VisRoom {
    Vec3 center;
    Vec3 half_extent;
    VisPortal portals[8];
    u32 portal_count;
    const u32 *object_ids;
    u32 object_count;
} VisRoom;

typedef struct VisQuery {
    const VisRoom *rooms;
    u32 room_count;
    Vec3 camera;
    Vec3 camera_forward;
    const u32 *outdoor_ids;
    u32 outdoor_count;
} VisQuery;

u32 visarea_visible(const VisQuery *query, u32 *out_ids, u32 cap, u32 *dropped);
```

- [x] 写失败测试：摄像机在房间内且没有门户时，输出只含该房间物体；门户邻接房间且视锥（用 forward 与门户中心夹角 < 90° 作为本任务的视锥，设计文档里的矩形裁剪在实现时收紧到门户四边，测试改用一个明显在矩形内和一个明显在矩形外的房间）能看见邻居；室外 id 始终在列表中；`cap` 不足时 `dropped > 0` 且不写越界。
- [x] 确认红，然后实现。房间数硬上限 128，每房间物体 512，超出在构建查询前由调用方保证；函数对超限输入返回 0 并置 `dropped` 为 object 总数。
- [x] 三棵树通过。

### Task D4: 对象块与地形窗口

**Files:**

- Create: `engine/src/renderer/world_stream.h`
- Create: `engine/src/renderer/world_stream.c`
- Create: `engine/tests/test_world_stream.c`

**Interfaces:**

```c
typedef struct StreamWant {
    u32 tile_x;
    u32 tile_z;
    bool resident; /* true = 应加载，false = 应卸载 */
} StreamWant;

u32 world_stream_want(u32 camera_tile_x, u32 camera_tile_z,
                      u32 tile_count_x, u32 tile_count_z,
                      const bool *resident, u32 resident_len,
                      StreamWant *out, u32 cap);
```

Chebyshev 距离 ≤ 1 且当前未驻留 → `resident` 输出 true。距离 ≥ 3 且当前驻留 → 输出 false。距离 2 不产生记录。

- [x] 写失败测试：摄像机在 (5,5)，(5,5) 未驻留时出现加载；(5,5) 已驻留时不出现；(8,5) 已驻留时出现卸载；(7,5) 不出现；`cap` 不够时返回值等于已写出的数量且不越界。
- [x] 确认红，然后实现。本任务不提交任务系统、不读 VFS。把 `StreamWant` 交给现有任务系统的集成留在状态文档的未交付列表里，除非测试已经用假的完成回调跑通加载提交。
- [x] 三棵树通过。更新 `docs/Implementation_Status.md`：贴花、体素地形、道路、绳索未做；流式不等于网络 AOI。

---

## 阶段 E：姿态、布娃娃、射线载具（F 绿之后，可与 D 并行）

### Task E1: 刚体朝向、角速度、局部锚点、铰链

**Files:**

- Modify: `engine/src/physics/physics.h`
- Modify: `engine/src/physics/physics.c`
- Modify: `engine/tests/test_physics.c`（若现有测试零初始化刚体，确认新字段零值保持旧行为）
- Create: `engine/tests/test_physics_hinge.c`

**Interfaces:**

```c
typedef struct PhysicsPose {
    Quat orientation;   /* 单位四元数；非单位时 step 开始时归一，零四元数换成单位 */
    Vec3 angular_velocity;
    Vec3 inertia_diag;  /* 0 分量视为无穷大，该轴不积分 */
} PhysicsPose;

void physics_body_set_pose(PhysicsWorld *pw, u32 body_id, const PhysicsPose *pose);

typedef struct HingeDesc {
    u32 body_a;
    u32 body_b;
    Vec3 anchor_local_a;
    Vec3 anchor_local_b;
    Vec3 axis_local_a;  /* 单位轴 */
    f32 limit_min;      /* 弧度，min==max==0 表示无限制 */
    f32 limit_max;
} HingeDesc;

u32 physics_constraint_add_hinge(PhysicsWorld *pw, const HingeDesc *desc);
```

现有 `physics_constraint_add_ball` 的偏移改为局部空间：求解前用朝向旋转。零朝向（单位四元数）时结果与今天的世界偏移一致，旧测试必须仍然通过。铰链占用 `constraints[]` 的一个槽，满则返回 `UINT32_MAX`。

- [x] 写失败测试：单位四元数、零角速度的盒子在无碰撞时行为与改前测试一致（抽一条现有下落测试作对照）；绕 Y 的角速度在一个固定步后朝向变化量与 `ω * dt` 相差 < 1e-3；铰链两体在轴向上拉开后，若干步内锚点距离回到 < 1e-2 m；角度超过 `limit_max` 时下一步不再增大；第 65 个约束返回 `UINT32_MAX`。
- [x] 确认红，然后实现。静态体忽略角速度。
- [x] 三棵树通过，并重跑现有 `test_physics*`，确认旧距离约束测试仍绿。

### Task E2: 布娃娃

**Files:**

- Create: `engine/src/physics/ragdoll.h`
- Create: `engine/src/physics/ragdoll.c`
- Create: `engine/tests/test_ragdoll.c`

**Interfaces:**

```c
typedef struct RagdollBone {
    u32 joint;
    u32 body_id;
    u32 parent_bone; /* UINT32_MAX 表示根 */
} RagdollBone;

typedef struct Ragdoll {
    RagdollBone bones[32];
    u32 bone_count;
    bool active;
} Ragdoll;

bool ragdoll_activate(Ragdoll *rd, PhysicsWorld *pw, const Skeleton *sk);
void ragdoll_write_pose(const Ragdoll *rd, const PhysicsWorld *pw, Skeleton *sk);
```

`activate` 按关节当前世界位置创建动态胶囊（半径 0.05 m，长度为到父关节的距离），父子之间加铰链。失败时销毁本次已创建的刚体并返回 false。`write_pose` 把刚体位置和朝向写进 `current_pose`。

- [x] 写失败测试：两关节、父在原点、子在 (0,1,0)，激活后存在两个动态体；把子刚体移到 (0,1,0.2) 后 `write_pose` 的子关节平移含 0.2；激活失败注入（把约束上限填满）后物理世界刚体数与调用前相同。
- [x] 确认红，然后实现。
- [x] 三棵树通过。

### Task E3: 射线载具

**Files:**

- Create: `engine/src/physics/vehicle.h`
- Create: `engine/src/physics/vehicle.c`
- Create: `engine/tests/test_vehicle.c`

**Interfaces:**

```c
typedef struct VehicleInput {
    f32 throttle; /* [-1, 1] */
    f32 steer;    /* [-1, 1] */
    f32 brake;    /* [0, 1] */
} VehicleInput;

typedef struct Vehicle {
    u32 chassis;
    f32 wheel_radius;
    Vec3 wheel_local[4];
    f32 suspension_rest;
    f32 stiffness;
    bool occupied;
} Vehicle;

bool vehicle_create(Vehicle *v, PhysicsWorld *pw, Vec3 position);
void vehicle_step(Vehicle *v, PhysicsWorld *pw, const VehicleInput *in, f32 dt);
bool vehicle_enter(Vehicle *v);
bool vehicle_exit(Vehicle *v, PhysicsWorld *pw, Vec3 *out_feet);
```

`vehicle_step` 从每个 `wheel_local` 沿底盘 -Y 扫掠 `suspension_rest + wheel_radius`。命中则按压缩量在底盘上施加力。油门沿底盘前向加力，刹车削线速度，转向改角速度的 Y 分量。

`vehicle_exit` 在底盘右侧 1.5 m 处做一次扫掠，通过则写出落点并清 `occupied`，失败则保持 `occupied` 并返回 false。

- [x] 写失败测试：悬空车辆一步后仍存在底盘；放在静态盒子上的车辆在零输入下垂直速度在 2 秒模拟后绝对值 < 0.5（弹簧撑住，允许小振荡）；油门 1 持续 1 秒后水平速率 > 1 m/s；右侧被墙堵住时 exit 返回 false 且 `occupied` 仍为 true。
- [x] 确认红，然后实现。
- [x] 三棵树通过。更新 `docs/Implementation_Status.md`：无布料、无绳索、无软体、无可破坏物；载具没有轮子刚体。

---

## 完成定义

- 可玩原型：A、B、C、F 的测试在三棵树上通过，设计文档第 1 节写成已交付，并写明未进 `engine` 链接行。
- Cry 式关卡表现：D 与 E 各自的测试通过后分别改状态。D 的 GPU 画面和 E 的驾驶手感不由这些 CPU 测试证明，状态条目里保持这句话。
- 设计文档第 11 节的范围外清单保持未做。不要在本计划的提交里顺手实现它们。
