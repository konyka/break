# 物品、背包与权威武器开火

## 交付边界

`break_game` 现已提供固定物品表、事务式背包和每 Actor 武器状态机。物品与武器 id 都是 1..64；表内嵌在 `BreakGame`，运行中的物品和武器操作不动态分配内存。

本切片只生成服务端权威的开火意图。命中检测、目标选择、生命扣减、死亡、弹道、网络复制和客户端伤害裁决均未交付。`BreakGameFireIntent.damage` 完全来自宿主定义的武器配置，不是目标已受伤的结果。

## 公开 API

```c
typedef struct BreakGameWeaponDesc {
    u32 weapon_id;
    u32 ammo_item_id;
    u32 damage;
    u32 magazine_capacity;
    u32 fire_interval_ticks;
    u32 reload_ticks;
} BreakGameWeaponDesc;

typedef struct BreakGameFireIntent {
    Entity shooter;
    u32 weapon_id;
    u32 damage;
    u64 sequence;
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

定义约束：`weapon_id` 与 `ammo_item_id` 为 1..64，弹药物品必须已经定义；`damage` 为 1..10000，`magazine_capacity` 为 1..1000，`reload_ticks >= 1`。射速间隔允许为 0。重复定义返回 `REJECTED`，未知定义返回 `STALE`，越界参数返回 `INVALID`。

所有公开调用只允许 `BreakGame` 创建线程。Actor 调用通过 `break_game_actor_slot` 同时检查 index 和 generation；despawn 后的旧句柄返回 `STALE`。失败不会写出部分 intent 或弹药查询结果。

## 状态与时序

每个 Actor 保存当前武器、弹匣、本地 tick、下次可开火 tick、装填完成 tick 和装填标志。装备会重置这些状态并把弹匣置为配置容量；这一步不扣背包备弹。已装备时重复装备返回 `REJECTED`。

开火只在未装填、弹匣非空且 `now_tick >= next_fire_tick` 时成功。成功后弹匣减一，下一开火时刻为 `now_tick + fire_interval_ticks`，并输出 shooter、weapon_id、damage 和 sequence。序号从 1 开始，在整个 `BreakGame` 上单调递增；未装备、冷却、空弹匣、装填中或过期句柄造成的拒绝都不消耗弹药、不推进序号，也不改输出。

`break_game_weapon_tick` 的 `elapsed_ticks` 必须大于 0。tick 加法、装填完成时刻、开火冷却加法和全局序号递增都在提交前检查溢出；这些 `INVALID/OVERLOAD` 路径不改武器或序号状态。

装填时序如下：

1. `begin_reload` 要求弹匣未满、当前不在装填且备弹非零；此时只设置完成 tick，不扣备弹。
2. 完成 tick 之前，tick 只推进时间，弹匣不变。
3. 到达完成 tick 后，内部按槽事务助手一次性扣除 `capacity - magazine` 发备弹，再把弹匣填满并清除装填状态。
4. 如果备弹在开始装填后被转走，扣减返回 `OVERLOAD`，弹匣、备弹和装填状态不变；已经推进的本地 tick 保留。补入备弹后再次 tick 即可重试，不会部分扣弹。
5. 开始时装填没有备弹返回 `REJECTED`。弹匣已满或尚未到期的重复 begin 也返回 `REJECTED`。已到期装填再次调用 begin 会复用同一原子完成路径，因此即使 `now_tick == UINT32_MAX`、正数 tick 已无法推进，也能在补弹后通过 begin 重试。

退弹时，unequip 先把当前弹匣余弹加入同一 Actor 的背包。背包容量不足返回 `OVERLOAD`，装备、弹匣、装填和背包全部保持原值；容量足够才提交并清空武器状态。成功 unequip 会取消未完成的装填。despawn 清空武器状态和该槽背包，Entity generation 复用不会继承装备、冷却或装填；全局开火序号不随 Actor 重置。

内部物品助手只接受正的 `u32` 数量，分别执行按槽增加与扣减。武器代码不以负数调用公开 `break_game_inventory_add`，也不绕过物品 id、堆叠上限或余量校验。

## 验证

测试位于 `engine/tests/test_break_game_weapons.c`，共 9 个真实状态机测试，覆盖定义边界、开火与冷却、装填精确时刻、部分备弹不足时的原子回滚与重试、有限背包空间下的退弹回滚、owner/generation、完整溢出状态、最大 tick 重试、despawn 槽复用和 intent 内容。

TDD RED 先看到新增类型/API 缺失的编译失败；最小声明和桩加入后，有效开火断言在 `test_break_game_weapons.c:85` 失败，8/8 测试失败。实现后首次 GREEN 为 8/8。

正常树：

```bash
cmake -S engine -B build-cry-final
cmake --build build-cry-final -j6 --target test_break_game_weapons
./build-cry-final/test_break_game_weapons
ctest --test-dir build-cry-final -R 'break_game|cry_style' --output-on-failure
```

结果为武器 9/9，focused 9/9。

ASan+UBSan 与 TSan 树均运行 Actor、物品、武器和 Cry 原型四个 focused 测试：

```bash
cmake -S engine -B build-game-asan
cmake --build build-game-asan -j6 --target \
  test_break_game_items test_break_game_weapons \
  test_break_game_actor test_cry_style_prototype
ctest --test-dir build-game-asan \
  -R '^(test_break_game_items|test_break_game_weapons|test_break_game_actor|test_cry_style_prototype)$' \
  --output-on-failure

cmake -S engine -B build-game-tsan
cmake --build build-game-tsan -j6 --target \
  test_break_game_items test_break_game_weapons \
  test_break_game_actor test_cry_style_prototype
ctest --test-dir build-game-tsan \
  -R '^(test_break_game_items|test_break_game_weapons|test_break_game_actor|test_cry_style_prototype)$' \
  --output-on-failure
```

两树均为 4/4，无 sanitizer 报告。初始 8 项套件的变异验证中，临时跳过上弹扣备弹使备弹断言及失败重试测试变红（6/8）；临时移除冷却判断使第二次立即开火断言变红（7/8）。评审补强后，临时在扣弹失败时扣空现有备弹、在退弹容量不足时部分填满背包，均使 9 项套件按预期变为 8/9。所有变异恢复后，正常树 9/9、ASan+UBSan 4/4、TSan 4/4 再次通过。
