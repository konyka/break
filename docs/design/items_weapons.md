# 物品、背包与权威武器开火

## 交付边界

`break_kernel` 现已提供固定物品表、事务式背包和每 Actor 武器状态机。物品与武器 id 都是 1..64；表内嵌在 `BreakKernel`，运行中的物品和武器操作不动态分配内存。

本切片只生成服务端权威的开火意图。命中检测、目标选择、生命扣减、死亡、弹道、网络复制和客户端伤害裁决均未交付。`BreakKernelFireIntent.damage` 完全来自宿主定义的武器配置，不是目标已受伤的结果。

## 公开 API

```c
typedef struct BreakKernelWeaponDesc {
    u32 weapon_id;
    u32 ammo_item_id;
    u32 damage;
    u32 magazine_capacity;
    u32 fire_interval_ticks;
    u32 reload_ticks;
} BreakKernelWeaponDesc;

typedef struct BreakKernelFireIntent {
    Entity shooter;
    u32 weapon_id;
    u32 damage;
    u64 sequence;
} BreakKernelFireIntent;

BreakKernelError break_kernel_weapon_define(BreakKernel *application,
                                        const BreakKernelWeaponDesc *desc);
BreakKernelError break_kernel_weapon_equip(BreakKernel *application, Entity entity,
                                       u32 weapon_id);
BreakKernelError break_kernel_weapon_unequip(BreakKernel *application, Entity entity);
BreakKernelError break_kernel_weapon_begin_reload(BreakKernel *application, Entity entity);
BreakKernelError break_kernel_weapon_tick(BreakKernel *application, Entity entity,
                                      u32 elapsed_ticks);
BreakKernelError break_kernel_weapon_fire(BreakKernel *application, Entity entity,
                                      BreakKernelFireIntent *out_intent);
BreakKernelError break_kernel_weapon_ammo(const BreakKernel *application, Entity entity,
                                      u32 *out_magazine);
```

定义约束：`weapon_id` 与 `ammo_item_id` 为 1..64，弹药物品必须已经定义；`damage` 为 1..10000，`magazine_capacity` 为 1..1000，`reload_ticks >= 1`。射速间隔允许为 0。重复定义返回 `REJECTED`，未知定义返回 `STALE`，越界参数返回 `INVALID`。

所有公开调用只允许 `BreakKernel` 创建线程。Actor 调用通过 `break_kernel_actor_slot` 同时检查 index 和 generation；despawn 后的旧句柄返回 `STALE`。失败不会写出部分 intent 或弹药查询结果。

## 状态与时序

每个 Actor 保存当前武器、弹匣、本地 tick、下次可开火 tick、装填完成 tick 和装填标志。equip 只选择武器并把弹匣置为 0，不赠送弹药；Actor 的 `now_tick` 和 `next_fire_tick` 在 unequip/equip 间保留。已装备时重复装备返回 `REJECTED`。

开火只在未装填、弹匣非空且 `now_tick >= next_fire_tick` 时成功。成功后弹匣减一，下一开火时刻为 `now_tick + fire_interval_ticks`，并输出 shooter、weapon_id、damage 和 sequence。序号从 1 开始，在整个 `BreakKernel` 上单调递增；未装备、冷却、空弹匣、装填中或过期句柄造成的拒绝都不消耗弹药、不推进序号，也不改输出。

`break_kernel_weapon_tick` 的 `elapsed_ticks` 必须大于 0。tick 加法、装填完成时刻、开火冷却加法和全局序号递增都在提交前检查溢出；这些 `INVALID/OVERLOAD` 路径不改武器或序号状态。

装填时序如下：

1. `begin_reload` 要求弹匣未满、当前不在装填且备弹非零；此时只设置完成 tick，不扣备弹。
2. 完成 tick 之前，tick 只推进时间，弹匣不变。
3. 到达完成 tick 后，先构造候选 `now_tick`，内部按槽事务助手一次性扣除 `capacity - magazine` 发备弹；所有可能失败的操作成功后才提交时间、弹匣和装填状态。
4. 如果备弹在开始装填后被转走，扣减返回 `OVERLOAD`，武器全部字段和 inventory 都保持调用前原值，包括 `now_tick`。补入备弹后从原时刻再次 tick 即可重试，不会部分扣弹或部分推进时间。
5. 开始时装填没有备弹返回 `REJECTED`。弹匣已满、装填尚未到期或已经处于装填状态时，重复 begin 均返回 `REJECTED`。到达完成 tick 后如果扣弹失败，武器和背包均回滚到原时刻；补弹后应从原时刻再次调用 tick 完成装填，而不是用 begin 绕过既定装填时序。

退弹时，unequip 先把当前弹匣余弹加入同一 Actor 的背包。背包容量不足返回 `OVERLOAD`，装备、弹匣、装填和背包全部保持原值；容量足够才提交。成功 unequip 取消装备和未完成的装填，但保留 Actor 的 `now_tick/next_fire_tick`；re-equip 仍为 0 弹匣，必须重新开始装填。despawn 才清空全部武器状态和该槽背包，Entity generation 复用不会继承装备、冷却或装填；全局开火序号不随 Actor 重置。

内部物品助手只接受正的 `u32` 数量，分别执行按槽增加与扣减。武器代码不以负数调用公开 `break_kernel_inventory_add`，也不绕过物品 id、堆叠上限或余量校验。

## 验证

测试位于 `engine/tests/test_break_kernel_weapons.c`，共 16 个真实状态机测试，覆盖定义边界、开火与冷却、非空弹匣装填中开火、未知已装备 weapon id、装填精确时刻、失败时完整 tick/inventory 回滚与重试、装备循环弹药守恒、跨装备冷却保留、装填中重装不赠弹、有限背包空间及非零装填/冷却下的退弹回滚、owner/generation、NULL 参数、完整溢出状态、最大 tick 重试、despawn 槽复用和 intent 内容。

TDD RED 先看到新增类型/API 缺失的编译失败；最小声明和桩加入后，有效开火断言在 `test_break_kernel_weapons.c:85` 失败，8/8 测试失败。实现后首次 GREEN 为 8/8。

正常树：

```bash
cmake -S engine -B build-cry-final
cmake --build build-cry-final -j6 --target test_break_kernel_weapons
./build-cry-final/test_break_kernel_weapons
ctest --test-dir build-cry-final -R 'break_kernel|core_style' --output-on-failure
```

结果为武器 16/16，focused 9/9。

ASan+UBSan 与 TSan 树均运行 Actor、物品、武器和 Cry 原型四个 focused 测试：

```bash
cmake -S engine -B build-application-asan
cmake --build build-application-asan -j6 --target \
  test_break_kernel_items test_break_kernel_weapons \
  test_break_kernel_actor test_core_style_prototype
ctest --test-dir build-application-asan \
  -R '^(test_break_kernel_items|test_break_kernel_weapons|test_break_kernel_actor|test_core_style_prototype)$' \
  --output-on-failure

cmake -S engine -B build-application-tsan
cmake --build build-application-tsan -j6 --target \
  test_break_kernel_items test_break_kernel_weapons \
  test_break_kernel_actor test_core_style_prototype
ctest --test-dir build-application-tsan \
  -R '^(test_break_kernel_items|test_break_kernel_weapons|test_break_kernel_actor|test_core_style_prototype)$' \
  --output-on-failure
```

两树均为 4/4，无 sanitizer 报告。初始 8 项套件的变异验证中，临时跳过上弹扣备弹使备弹断言及失败重试测试变红（6/8）；临时移除冷却判断使第二次立即开火断言变红（7/8）。评审补强后，临时在扣弹失败时扣空现有备弹、在退弹容量不足时部分填满背包，均使 9 项套件按预期变为 8/9。所有变异恢复后，正常树 9/9、ASan+UBSan 4/4、TSan 4/4 再次通过。
