# Gameplay Items And Weapons Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** 修复已有 Windows 构建回归，并为 Actor 增加事务式背包、武器、弹药与权威开火意图。

**Architecture:** 在现有 `break_game` 内按职责增加 items/weapons 两个 TU，状态按 Actor 槽索引并在 create 时一次分配。物品和武器定义由宿主配置；开火输出意图，不修改目标生命，不把客户端伤害值送入网络裁决。

**Tech Stack:** C11、现有 ECS/`BreakGame`、CTest、`test_framework.h`、GitHub Actions Windows 编译日志、ASan/UBSan/TSan。

## Global Constraints

- 遵循 `docs/superpowers/specs/2026-11-02-cry-capability-completion-design.md` 第 4、5、6、8 节。
- 每个行为先写测试并确认 RED，再实现；不得用删除 Windows 测试或放宽 `-Werror` 修复构建。
- 热路径不分配内存；任何失败保持调用前状态；所有 Entity 必须经 `break_game_actor_slot` 验证 generation。
- 保持 `break_game` 独立，`ENGINE_BUILD_TESTS=OFF` 时仍构建，不链入 `engine`、`engine_demo`、`dxx_break`。
- 完成每个任务后运行 focused normal/ASan+UBSan/TSan，更新 `docs/Implementation_Status.md` 顶部。

---

### Task 1: Windows 测试临时目录回归

**Files:**
- Modify: `engine/tests/test_world_stream_world.c`
- Modify: `docs/Implementation_Status.md`

**Interfaces:**
- Consumes: `test_tmp(buf, cap, name)`、`TEST_MKDIR(path)`、`TEST_RMDIR(path)`，已由 `engine/tests/test_framework.h` 提供。
- Produces: 在 Windows/Linux 上均可编译且路径按进程隔离的 `test_world_stream_world`。

- [ ] **Step 1: 固定 RED 证据并检查近期变更**

已保存 GitHub run `41276867563`：Clang/MSVC 在测试第 5 行找不到 `unistd.h`，MinGW 在第 61 行报告双参数 `mkdir`。检查 `git log -p -- engine/tests/test_world_stream_world.c`，确认这是测试引入的 POSIX 假设，而不是流式实现缺陷。先在当前代码中确认该文件仍直接包含 `unistd.h`、写死 `/tmp` 并调用 `rmdir/mkdir`。

- [ ] **Step 2: 用现有跨平台助手替换测试路径**

保留所有流式断言，只改变测试 fixture。目录由下面的模式生成，所有文件路径用 `snprintf` 并检查返回值：

```c
char root[512];
char path[560];
ASSERT_NOT_NULL(test_tmp(root, sizeof(root), "break-stream-tile-test"));
ASSERT_EQ(TEST_MKDIR(root), 0);
int n = snprintf(path, sizeof(path), "%s/tile_1_0.bin", root);
ASSERT_TRUE(n > 0 && (usize)n < sizeof(path));
```

删除 `<unistd.h>` 的直接包含（`test_framework.h` 已按平台提供它），清理用 `remove(path)` 和 `TEST_RMDIR(root)`。不能改动 `world_stream_world.c` 来迁就测试。

- [ ] **Step 3: 验证行为与跨平台编译**

Run: `cmake -S engine -B build-cry-final && cmake --build build-cry-final -j6 --target test_world_stream_world && ./build-cry-final/test_world_stream_world`
Expected: 全部既有测试通过。
Run: `cmake --build build-sdd-p4-asan -j6 --target test_world_stream_world && ./build-sdd-p4-asan/test_world_stream_world`
Expected: 全部通过，无 sanitizer 报告。
Run Windows CI 等价的 native Windows 编译（本机 Windows 可用时）；否则用可用 Windows 编译器检查此 TU，并将最终运行证据交给 push 后 CI，不提前声称 Windows 已通过。

- [ ] **Step 4: 文档与提交**

记录根因是测试 fixture 的 POSIX 依赖，修复未改生产逻辑，列出实际跑过的命令。提交：

```bash
git add engine/tests/test_world_stream_world.c docs/Implementation_Status.md
git commit -m "test: make streamed tile fixture portable"
```

### Task 2: 物品定义与事务式背包

**Files:**
- Modify: `engine/src/game/break_game.h`
- Modify: `engine/src/game/break_game_internal.h`
- Modify: `engine/src/game/break_game.c`
- Modify: `engine/src/game/break_game_actor.c`
- Create: `engine/src/game/break_game_items.c`
- Create: `engine/tests/test_break_game_items.c`
- Modify: `engine/CMakeLists.txt`
- Modify: `engine/tests/test_break_game_target_contract.cmake`

**Interfaces:**

```c
#define BREAK_GAME_MAX_ITEMS 64u

typedef struct BreakGameItemDesc {
    u32 item_id;       /* 1..64 */
    u32 stack_limit;   /* 1..1000000 */
} BreakGameItemDesc;

BreakGameError break_game_item_define(BreakGame *game,
                                      const BreakGameItemDesc *desc);
BreakGameError break_game_inventory_add(BreakGame *game, Entity entity,
                                        u32 item_id, u32 count);
BreakGameError break_game_inventory_count(BreakGame *game, Entity entity,
                                          u32 item_id, u32 *out_count);
BreakGameError break_game_inventory_transfer(BreakGame *game,
                                             Entity from, Entity to,
                                             u32 item_id, u32 count);
```

- [ ] **Step 1: 写物品/背包失败测试**

注册两个 Actor、`ammo`（stack_limit=30）和 `medkit`（stack_limit=2）。覆盖：id 0/65、stack_limit 0/1000001 和重复定义被拒绝；add 0、未知物品、stale Entity 被拒绝；加 25 后再加 6 返回 `OVERLOAD` 且原数量仍为 25；成功转移 10 后来源为 15、目标为 10；目标只能再收 20 时转移 21 完整回滚；`from==to`、count 0 均拒绝；despawn 后旧句柄不可读写。测试核心断言形状：

```c
ASSERT_EQ(break_game_inventory_add(game, a, ammo, 25u), BREAK_GAME_OK);
ASSERT_EQ(break_game_inventory_add(game, a, ammo, 6u), BREAK_GAME_OVERLOAD);
ASSERT_EQ(break_game_inventory_count(game, a, ammo, &count), BREAK_GAME_OK);
ASSERT_EQ(count, 25u);
ASSERT_EQ(break_game_inventory_transfer(game, a, b, ammo, 10u), BREAK_GAME_OK);
```

- [ ] **Step 2: 构建并确认 RED**

在 CMake 按现有 `actor/actions/area` 模式注册 `test_break_game_items`，把它链到 `break_game`。

Run: `cmake -S engine -B build-cry-final && cmake --build build-cry-final -j6 --target test_break_game_items && ./build-cry-final/test_break_game_items`
Expected: 因接口尚未实现而编译或链接失败；若先写最小声明，则必须看到行为断言失败，不接受只因为函数名缺失的 RED 作为最终 TDD 证据。

- [ ] **Step 3: 实现固定容量状态与事务转移**

`BreakGame` 增加 65 项定义表和 `u32 *inventories`；create 按 `max_actors * 65` 分配并溢出检查，destroy 释放。索引为 `actor_slot * 65 + item_id`。`inventory_add` 先验证所有参数并计算 `old + count <= stack_limit`，成功才写；transfer 先同时验证双方和接收上限，再一次写两边。despawn 清零该槽的 65 项，防止 index/generation 复用继承物品。任何查询不修改状态。

- [ ] **Step 4: 验证与关键变异**

Run: `./build-cry-final/test_break_game_items && ./build-cry-final/test_break_game_actor && ctest --test-dir build-cry-final -R 'break_game|cry_style' --output-on-failure`
Expected: 全通过。
分别在三棵树运行该二进制。临时去掉 transfer 的接收上限检查，确认目标上限/回滚测试变红，随后恢复并再跑；不得提交变异体。

- [ ] **Step 5: 更新 target contract 和文档**

把 `break_game_items.c` 加入正式库与 contract 清单。文档记录容量、事务语义、despawn 清除规则。提交：

```bash
git add engine/src/game engine/tests/test_break_game_items.c engine/tests/test_break_game_target_contract.cmake engine/CMakeLists.txt docs
git commit -m "game: add transactional actor inventories"
```

### Task 3: 武器状态机与伤害意图

**Files:**
- Modify: `engine/src/game/break_game.h`
- Modify: `engine/src/game/break_game_internal.h`
- Modify: `engine/src/game/break_game.c`
- Modify: `engine/src/game/break_game_actor.c`
- Create: `engine/src/game/break_game_weapons.c`
- Create: `engine/tests/test_break_game_weapons.c`
- Modify: `engine/CMakeLists.txt`
- Modify: `engine/tests/test_break_game_target_contract.cmake`
- Create: `docs/design/gameplay_items_weapons.md`
- Modify: `docs/design/cry_style_gameplay.md`
- Modify: `docs/Implementation_Status.md`

**Interfaces:**

```c
typedef struct BreakGameWeaponDesc {
    u32 weapon_id;             /* 1..64 */
    u32 ammo_item_id;          /* 已定义物品 */
    u32 damage;                /* 1..10000，由服务端配置 */
    u32 magazine_capacity;     /* 1..1000 */
    u32 fire_interval_ticks;
    u32 reload_ticks;          /* >= 1 */
} BreakGameWeaponDesc;

typedef struct BreakGameFireIntent {
    Entity shooter;
    u32 weapon_id;
    u32 damage;
    u64 sequence;              /* 从 1 起，全 BreakGame 单调 */
} BreakGameFireIntent;

BreakGameError break_game_weapon_define(BreakGame *game,
                                        const BreakGameWeaponDesc *desc);
BreakGameError break_game_weapon_equip(BreakGame *game, Entity entity,
                                       u32 weapon_id);
BreakGameError break_game_weapon_unequip(BreakGame *game, Entity entity);
BreakGameError break_game_weapon_begin_reload(BreakGame *game, Entity entity);
BreakGameError break_game_weapon_tick(BreakGame *game, Entity entity,
                                      u32 elapsed_ticks);
BreakGameError break_game_weapon_fire(BreakGame *game, Entity entity,
                                      BreakGameFireIntent *out_intent);
BreakGameError break_game_weapon_ammo(const BreakGame *game, Entity entity,
                                      u32 *out_magazine);
```

- [ ] **Step 1: 写武器失败测试**

定义 `ammo` 和武器（容量 2、伤害 7、射速间隔 2 tick、装填 3 tick），生成 Actor 并装备。覆盖：未装备/未知武器开火拒绝；装填没有弹药拒绝；有 5 发备弹时开始装填，3 tick 前不能完成，恰好 3 tick 后弹匣为 2、背包为 3；两次连续开火第一次成功、第二次因冷却拒绝，2 tick 后成功且序号为 1、2；弹匣为空时开火拒绝且不增加序号；装填中开火拒绝；输出含 shooter/weapon_id/damage，但 API 没有目标生命或命中结果。unequip 把弹匣余弹事务式退回背包，背包放不下时保持装备及弹匣不变。

核心断言：

```c
ASSERT_EQ(break_game_weapon_fire(game, actor, &fire), BREAK_GAME_OK);
ASSERT_EQ(fire.damage, 7u);
ASSERT_EQ(fire.sequence, 1u);
ASSERT_EQ(break_game_weapon_fire(game, actor, &fire), BREAK_GAME_REJECTED);
ASSERT_EQ(break_game_weapon_tick(game, actor, 2u), BREAK_GAME_OK);
ASSERT_EQ(break_game_weapon_fire(game, actor, &fire), BREAK_GAME_OK);
```

- [ ] **Step 2: 确认行为 RED**

Run: `cmake --build build-cry-final -j6 --target test_break_game_weapons && ./build-cry-final/test_break_game_weapons`
Expected: 新增接口缺失；给出最小声明后至少看到开火/装填行为断言失败，保存实际结果到任务记录，不虚构 RED。

- [ ] **Step 3: 实现有界状态机**

每 Actor 保存 weapon id、magazine、now tick、next fire tick、reload finish tick 和 reloading 标志。定义表按 65 项固定分配或内嵌。装填完成时通过物品 API 原子扣减备弹并填满到容量；扣减失败保持装填状态可重试。tick 加法检查溢出，非法 dt/溢出返回 `INVALID/OVERLOAD` 且不改状态。fire 仅在非装填、弹匣非空且 `now >= next_fire` 时扣一发、设置冷却并写 intent；任何拒绝不改变弹药和序号。unequip 先确认退弹容量再提交。despawn 清空武器状态，generation 复用不得继承。

- [ ] **Step 4: focused、sanitizer 与变异验证**

Run: `ctest --test-dir build-cry-final -R 'break_game|cry_style' --output-on-failure`
Expected: 全通过。
在 ASan+UBSan、TSan 树运行 `test_break_game_items`、`test_break_game_weapons`、`test_break_game_actor` 和 `test_cry_style_prototype`。临时跳过装填的库存扣减，确认备弹不变异时测试变红；临时允许冷却期间开火，确认第二个 fire 测试变红。恢复后重跑。

- [ ] **Step 5: 文档、独立评审与提交**

`gameplay_items_weapons.md` 写明 API、事务、时序、权威边界和真实测试命令；`cry_style_gameplay.md` 只把已完成的物品/武器缺口改为已交付，Flow Graph 等后续项保持未完成。派只读 reviewer 检查回滚、句柄、溢出和状态机，修复发现后再提交：

```bash
git add engine/src/game engine/tests/test_break_game_weapons.c engine/tests/test_break_game_target_contract.cmake engine/CMakeLists.txt docs
git commit -m "game: model weapons as authoritative fire intents"
```
