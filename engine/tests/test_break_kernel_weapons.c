#include "test_framework.h"
#include <kernel/break_kernel_internal.h>
#include <core/platform_thread.h>
#include <stdint.h>

#define AMMO_ID   1u
#define WEAPON_ID 1u

static World *make_world(void) {
    World *world = world_create();
    world_register_component(world, BREAK_KERNEL_POSITION_COMPONENT, sizeof(Vec3));
    return world;
}

static BreakKernel *make_kernel(World *world, u32 max_actors) {
    BreakKernelConfig cfg;
    cfg.max_classes = 0;
    cfg.max_actors = max_actors;
    return break_kernel_create(world, &cfg);
}

static Entity spawn_pawn(BreakKernel *kernel) {
    ComponentType comps[1] = {BREAK_KERNEL_POSITION_COMPONENT};
    BreakKernelClassDesc desc;
    desc.name = "pawn";
    desc.components = comps;
    desc.component_count = 1;
    desc.lua_module = NULL;
    u32 class_id = 0;
    BreakKernelError registered = break_kernel_register_class(kernel, &desc, &class_id);
    if (registered == BREAK_KERNEL_REJECTED) {
        class_id = 1;
    } else if (registered != BREAK_KERNEL_OK) {
        return ENTITY_NULL;
    }
    BreakKernelSpawn spawn;
    spawn.class_id = class_id;
    spawn.position = vec3(0, 0, 0);
    Entity entity = ENTITY_NULL;
    if (break_kernel_spawn(kernel, &spawn, &entity) != BREAK_KERNEL_OK) {
        return ENTITY_NULL;
    }
    return entity;
}

static bool define_standard_weapon(BreakKernel *kernel) {
    BreakKernelItemDesc ammo = {AMMO_ID, 30u};
    BreakKernelWeaponDesc weapon = {WEAPON_ID, AMMO_ID, 7u, 2u, 2u, 3u};
    return break_kernel_item_define(kernel, &ammo) == BREAK_KERNEL_OK &&
           break_kernel_weapon_define(kernel, &weapon) == BREAK_KERNEL_OK;
}

static bool load_standard_weapon(BreakKernel *kernel, Entity actor, u32 ammo_count) {
    return break_kernel_inventory_add(kernel, actor, AMMO_ID, ammo_count) == BREAK_KERNEL_OK &&
           break_kernel_weapon_begin_reload(kernel, actor) == BREAK_KERNEL_OK &&
           break_kernel_weapon_tick(kernel, actor, 3u) == BREAK_KERNEL_OK;
}

static BreakKernelFireIntent sentinel_intent(void) {
    BreakKernelFireIntent intent;
    intent.shooter = ENTITY_NULL;
    intent.weapon_id = 88u;
    intent.damage = 99u;
    intent.sequence = 77u;
    return intent;
}

static void destroy_kernel(BreakKernel *kernel, World *world) {
    break_kernel_destroy(kernel);
    world_destroy(world);
}

TEST(fire_cooldown_reload_and_intent_follow_authoritative_state) {
    World *world = make_world();
    BreakKernel *kernel = make_kernel(world, 2);
    ASSERT_NOT_NULL(kernel);
    Entity actor = spawn_pawn(kernel);
    ASSERT_TRUE(entity_valid(actor));
    ASSERT_TRUE(define_standard_weapon(kernel));
    BreakKernelFireIntent fire = sentinel_intent();
    BreakKernelFireIntent before = fire;
    ASSERT_EQ(break_kernel_weapon_fire(kernel, actor, &fire), BREAK_KERNEL_REJECTED);
    ASSERT_TRUE(memcmp(&fire, &before, sizeof(fire)) == 0);
    ASSERT_EQ(break_kernel_weapon_equip(kernel, actor, 2u), BREAK_KERNEL_STALE);
    ASSERT_EQ(break_kernel_weapon_equip(kernel, actor, WEAPON_ID), BREAK_KERNEL_OK);
    u32 magazine = 0;
    ASSERT_EQ(break_kernel_weapon_ammo(kernel, actor, &magazine), BREAK_KERNEL_OK);
    ASSERT_EQ(magazine, 0u);
    ASSERT_TRUE(load_standard_weapon(kernel, actor, 7u));
    ASSERT_EQ(break_kernel_weapon_ammo(kernel, actor, &magazine), BREAK_KERNEL_OK);
    ASSERT_EQ(magazine, 2u);

    ASSERT_EQ(break_kernel_weapon_fire(kernel, actor, &fire), BREAK_KERNEL_OK);
    ASSERT_EQ(fire.shooter.index, actor.index);
    ASSERT_EQ(fire.shooter.generation, actor.generation);
    ASSERT_EQ(fire.weapon_id, WEAPON_ID);
    ASSERT_EQ(fire.damage, 7u);
    ASSERT_EQ(fire.sequence, 1u);
    ASSERT_EQ(break_kernel_weapon_ammo(kernel, actor, &magazine), BREAK_KERNEL_OK);
    ASSERT_EQ(magazine, 1u);

    fire = sentinel_intent();
    before = fire;
    ASSERT_EQ(break_kernel_weapon_fire(kernel, actor, &fire), BREAK_KERNEL_REJECTED);
    ASSERT_TRUE(memcmp(&fire, &before, sizeof(fire)) == 0);
    ASSERT_EQ(break_kernel_weapon_tick(kernel, actor, 1u), BREAK_KERNEL_OK);
    ASSERT_EQ(break_kernel_weapon_fire(kernel, actor, &fire), BREAK_KERNEL_REJECTED);
    ASSERT_EQ(break_kernel_weapon_tick(kernel, actor, 1u), BREAK_KERNEL_OK);
    ASSERT_EQ(break_kernel_weapon_fire(kernel, actor, &fire), BREAK_KERNEL_OK);
    ASSERT_EQ(fire.sequence, 2u);
    ASSERT_EQ(break_kernel_weapon_ammo(kernel, actor, &magazine), BREAK_KERNEL_OK);
    ASSERT_EQ(magazine, 0u);

    fire = sentinel_intent();
    before = fire;
    ASSERT_EQ(break_kernel_weapon_fire(kernel, actor, &fire), BREAK_KERNEL_REJECTED);
    ASSERT_TRUE(memcmp(&fire, &before, sizeof(fire)) == 0);
    ASSERT_EQ(break_kernel_weapon_begin_reload(kernel, actor), BREAK_KERNEL_OK);
    u32 reload_slot = break_kernel_actor_slot(kernel, actor);
    ASSERT_NEQ(reload_slot, UINT32_MAX);
    u32 reload_now = kernel->actors[reload_slot].now_tick;
    u32 reload_next_fire = kernel->actors[reload_slot].next_fire_tick;
    u32 reload_finish = kernel->actors[reload_slot].reload_finish_tick;
    ASSERT_EQ(break_kernel_weapon_begin_reload(kernel, actor), BREAK_KERNEL_REJECTED);
    ASSERT_EQ(kernel->actors[reload_slot].now_tick, reload_now);
    ASSERT_EQ(kernel->actors[reload_slot].next_fire_tick, reload_next_fire);
    ASSERT_EQ(kernel->actors[reload_slot].reload_finish_tick, reload_finish);
    ASSERT_TRUE(kernel->actors[reload_slot].reloading);
    u32 reload_reserve = 0;
    ASSERT_EQ(break_kernel_inventory_count(kernel, actor, AMMO_ID, &reload_reserve), BREAK_KERNEL_OK);
    ASSERT_EQ(reload_reserve, 5u);
    ASSERT_EQ(break_kernel_weapon_fire(kernel, actor, &fire), BREAK_KERNEL_REJECTED);
    ASSERT_TRUE(memcmp(&fire, &before, sizeof(fire)) == 0);
    ASSERT_EQ(break_kernel_weapon_tick(kernel, actor, 2u), BREAK_KERNEL_OK);
    ASSERT_EQ(break_kernel_weapon_ammo(kernel, actor, &magazine), BREAK_KERNEL_OK);
    ASSERT_EQ(magazine, 0u);
    ASSERT_EQ(break_kernel_weapon_tick(kernel, actor, 1u), BREAK_KERNEL_OK);
    ASSERT_EQ(break_kernel_weapon_ammo(kernel, actor, &magazine), BREAK_KERNEL_OK);
    ASSERT_EQ(magazine, 2u);
    u32 reserve = 0;
    ASSERT_EQ(break_kernel_inventory_count(kernel, actor, AMMO_ID, &reserve), BREAK_KERNEL_OK);
    ASSERT_EQ(reserve, 3u);
    ASSERT_EQ(break_kernel_weapon_fire(kernel, actor, &fire), BREAK_KERNEL_OK);
    ASSERT_EQ(fire.sequence, 3u);
    destroy_kernel(kernel, world);
}

TEST(reload_without_reserve_rejects_and_failed_deduction_can_retry) {
    World *world = make_world();
    BreakKernel *kernel = make_kernel(world, 2);
    ASSERT_NOT_NULL(kernel);
    Entity actor = spawn_pawn(kernel);
    Entity other = spawn_pawn(kernel);
    ASSERT_TRUE(entity_valid(actor));
    ASSERT_TRUE(entity_valid(other));
    ASSERT_TRUE(define_standard_weapon(kernel));
    ASSERT_EQ(break_kernel_weapon_equip(kernel, actor, WEAPON_ID), BREAK_KERNEL_OK);
    ASSERT_TRUE(load_standard_weapon(kernel, actor, 2u));
    BreakKernelFireIntent fire;
    ASSERT_EQ(break_kernel_weapon_fire(kernel, actor, &fire), BREAK_KERNEL_OK);
    ASSERT_EQ(break_kernel_weapon_tick(kernel, actor, 2u), BREAK_KERNEL_OK);
    ASSERT_EQ(break_kernel_weapon_fire(kernel, actor, &fire), BREAK_KERNEL_OK);
    ASSERT_EQ(break_kernel_weapon_tick(kernel, actor, 2u), BREAK_KERNEL_OK);
    ASSERT_EQ(break_kernel_weapon_begin_reload(kernel, actor), BREAK_KERNEL_REJECTED);
    ASSERT_EQ(break_kernel_inventory_add(kernel, actor, AMMO_ID, 2u), BREAK_KERNEL_OK);
    ASSERT_EQ(break_kernel_weapon_begin_reload(kernel, actor), BREAK_KERNEL_OK);
    ASSERT_EQ(break_kernel_inventory_transfer(kernel, actor, other, AMMO_ID, 1u), BREAK_KERNEL_OK);
    u32 slot = break_kernel_actor_slot(kernel, actor);
    ASSERT_NEQ(slot, UINT32_MAX);
    u32 now = kernel->actors[slot].now_tick;
    u32 next_fire = kernel->actors[slot].next_fire_tick;
    u32 reload_finish = kernel->actors[slot].reload_finish_tick;

    ASSERT_EQ(break_kernel_weapon_tick(kernel, actor, 3u), BREAK_KERNEL_OVERLOAD);
    ASSERT_EQ(kernel->actors[slot].now_tick, now);
    ASSERT_EQ(kernel->actors[slot].next_fire_tick, next_fire);
    ASSERT_EQ(kernel->actors[slot].reload_finish_tick, reload_finish);
    ASSERT_TRUE(kernel->actors[slot].reloading);
    u32 magazine = 99u;
    u32 reserve = 99u;
    ASSERT_EQ(break_kernel_weapon_ammo(kernel, actor, &magazine), BREAK_KERNEL_OK);
    ASSERT_EQ(magazine, 0u);
    ASSERT_EQ(break_kernel_inventory_count(kernel, actor, AMMO_ID, &reserve), BREAK_KERNEL_OK);
    ASSERT_EQ(reserve, 1u);
    BreakKernelFireIntent before = sentinel_intent();
    fire = before;
    ASSERT_EQ(break_kernel_weapon_fire(kernel, actor, &fire), BREAK_KERNEL_REJECTED);
    ASSERT_TRUE(memcmp(&fire, &before, sizeof(fire)) == 0);

    ASSERT_EQ(break_kernel_inventory_add(kernel, actor, AMMO_ID, 1u), BREAK_KERNEL_OK);
    ASSERT_EQ(break_kernel_weapon_tick(kernel, actor, 3u), BREAK_KERNEL_OK);
    ASSERT_EQ(break_kernel_weapon_ammo(kernel, actor, &magazine), BREAK_KERNEL_OK);
    ASSERT_EQ(magazine, 2u);
    ASSERT_EQ(break_kernel_inventory_count(kernel, actor, AMMO_ID, &reserve), BREAK_KERNEL_OK);
    ASSERT_EQ(reserve, 0u);
    destroy_kernel(kernel, world);
}

TEST(fire_rejects_during_reload_with_round_and_expired_cooldown) {
    World *world = make_world();
    BreakKernel *kernel = make_kernel(world, 1);
    ASSERT_NOT_NULL(kernel);
    Entity actor = spawn_pawn(kernel);
    ASSERT_TRUE(entity_valid(actor));
    ASSERT_TRUE(define_standard_weapon(kernel));
    ASSERT_EQ(break_kernel_weapon_equip(kernel, actor, WEAPON_ID), BREAK_KERNEL_OK);
    ASSERT_TRUE(load_standard_weapon(kernel, actor, 2u));
    BreakKernelFireIntent fire;
    ASSERT_EQ(break_kernel_weapon_fire(kernel, actor, &fire), BREAK_KERNEL_OK);
    ASSERT_EQ(fire.sequence, 1u);
    ASSERT_EQ(break_kernel_weapon_tick(kernel, actor, 2u), BREAK_KERNEL_OK);
    ASSERT_EQ(break_kernel_inventory_add(kernel, actor, AMMO_ID, 2u), BREAK_KERNEL_OK);
    ASSERT_EQ(break_kernel_weapon_begin_reload(kernel, actor), BREAK_KERNEL_OK);
    u32 slot = break_kernel_actor_slot(kernel, actor);
    ASSERT_NEQ(slot, UINT32_MAX);
    ASSERT_EQ(kernel->actors[slot].magazine, 1u);
    ASSERT_EQ(kernel->actors[slot].now_tick, 5u);
    ASSERT_EQ(kernel->actors[slot].next_fire_tick, 5u);
    ASSERT_TRUE(kernel->actors[slot].reloading);
    u32 reload_finish = kernel->actors[slot].reload_finish_tick;

    fire = sentinel_intent();
    BreakKernelFireIntent before = fire;
    ASSERT_EQ(break_kernel_weapon_fire(kernel, actor, &fire), BREAK_KERNEL_REJECTED);
    ASSERT_TRUE(memcmp(&fire, &before, sizeof(fire)) == 0);
    ASSERT_EQ(kernel->actors[slot].weapon_id, WEAPON_ID);
    ASSERT_EQ(kernel->actors[slot].magazine, 1u);
    ASSERT_EQ(kernel->actors[slot].now_tick, 5u);
    ASSERT_EQ(kernel->actors[slot].next_fire_tick, 5u);
    ASSERT_EQ(kernel->actors[slot].reload_finish_tick, reload_finish);
    ASSERT_TRUE(kernel->actors[slot].reloading);
    ASSERT_EQ(kernel->fire_sequence, 1u);
    destroy_kernel(kernel, world);
}

TEST(fire_with_unknown_equipped_weapon_is_stale_and_atomic) {
    World *world = make_world();
    BreakKernel *kernel = make_kernel(world, 1);
    ASSERT_NOT_NULL(kernel);
    Entity actor = spawn_pawn(kernel);
    ASSERT_TRUE(entity_valid(actor));
    ASSERT_TRUE(define_standard_weapon(kernel));
    ASSERT_EQ(break_kernel_weapon_equip(kernel, actor, WEAPON_ID), BREAK_KERNEL_OK);
    ASSERT_TRUE(load_standard_weapon(kernel, actor, 2u));
    u32 slot = break_kernel_actor_slot(kernel, actor);
    ASSERT_NEQ(slot, UINT32_MAX);
    kernel->actors[slot].weapon_id = 2u;
    BreakKernelFireIntent fire = sentinel_intent();
    BreakKernelFireIntent before = fire;

    ASSERT_EQ(break_kernel_weapon_fire(kernel, actor, &fire), BREAK_KERNEL_STALE);
    ASSERT_TRUE(memcmp(&fire, &before, sizeof(fire)) == 0);
    ASSERT_EQ(kernel->actors[slot].weapon_id, 2u);
    ASSERT_EQ(kernel->actors[slot].magazine, 2u);
    ASSERT_EQ(kernel->actors[slot].now_tick, 3u);
    ASSERT_EQ(kernel->actors[slot].next_fire_tick, 0u);
    ASSERT_EQ(kernel->actors[slot].reload_finish_tick, 0u);
    ASSERT_FALSE(kernel->actors[slot].reloading);
    ASSERT_EQ(kernel->fire_sequence, 0u);
    destroy_kernel(kernel, world);
}

TEST(unequip_returns_magazine_atomically_and_rolls_back_capacity_failure) {
    World *world = make_world();
    BreakKernel *kernel = make_kernel(world, 2);
    ASSERT_NOT_NULL(kernel);
    Entity actor = spawn_pawn(kernel);
    Entity other = spawn_pawn(kernel);
    ASSERT_TRUE(entity_valid(actor));
    ASSERT_TRUE(entity_valid(other));
    ASSERT_TRUE(define_standard_weapon(kernel));
    ASSERT_EQ(break_kernel_weapon_equip(kernel, actor, WEAPON_ID), BREAK_KERNEL_OK);
    ASSERT_TRUE(load_standard_weapon(kernel, actor, 2u));
    ASSERT_EQ(break_kernel_inventory_add(kernel, actor, AMMO_ID, 29u), BREAK_KERNEL_OK);
    u32 slot = break_kernel_actor_slot(kernel, actor);
    ASSERT_NEQ(slot, UINT32_MAX);
    u32 now = kernel->actors[slot].now_tick;
    u32 next_fire = kernel->actors[slot].next_fire_tick;
    u32 reload_finish = kernel->actors[slot].reload_finish_tick;
    bool reloading = kernel->actors[slot].reloading;

    ASSERT_EQ(break_kernel_weapon_unequip(kernel, actor), BREAK_KERNEL_OVERLOAD);
    ASSERT_EQ(kernel->actors[slot].weapon_id, WEAPON_ID);
    ASSERT_EQ(kernel->actors[slot].now_tick, now);
    ASSERT_EQ(kernel->actors[slot].next_fire_tick, next_fire);
    ASSERT_EQ(kernel->actors[slot].reload_finish_tick, reload_finish);
    ASSERT_EQ(kernel->actors[slot].reloading, reloading);
    u32 magazine = 0;
    ASSERT_EQ(break_kernel_weapon_ammo(kernel, actor, &magazine), BREAK_KERNEL_OK);
    ASSERT_EQ(magazine, 2u);
    u32 reserve = 0;
    ASSERT_EQ(break_kernel_inventory_count(kernel, actor, AMMO_ID, &reserve), BREAK_KERNEL_OK);
    ASSERT_EQ(reserve, 29u);
    ASSERT_EQ(break_kernel_inventory_transfer(kernel, actor, other, AMMO_ID, 29u), BREAK_KERNEL_OK);
    ASSERT_EQ(break_kernel_weapon_unequip(kernel, actor), BREAK_KERNEL_OK);
    ASSERT_EQ(break_kernel_inventory_count(kernel, actor, AMMO_ID, &reserve), BREAK_KERNEL_OK);
    ASSERT_EQ(reserve, 2u);
    magazine = 99u;
    ASSERT_EQ(break_kernel_weapon_ammo(kernel, actor, &magazine), BREAK_KERNEL_REJECTED);
    ASSERT_EQ(magazine, 99u);
    ASSERT_EQ(break_kernel_weapon_unequip(kernel, actor), BREAK_KERNEL_REJECTED);
    ASSERT_EQ(break_kernel_inventory_count(kernel, actor, AMMO_ID, &reserve), BREAK_KERNEL_OK);
    ASSERT_EQ(reserve, 2u);
    destroy_kernel(kernel, world);
}

TEST(unequip_capacity_failure_preserves_reload_and_cooldown) {
    World *world = make_world();
    BreakKernel *kernel = make_kernel(world, 2);
    ASSERT_NOT_NULL(kernel);
    Entity actor = spawn_pawn(kernel);
    Entity other = spawn_pawn(kernel);
    ASSERT_TRUE(entity_valid(actor));
    ASSERT_TRUE(entity_valid(other));
    ASSERT_TRUE(define_standard_weapon(kernel));
    ASSERT_EQ(break_kernel_weapon_equip(kernel, actor, WEAPON_ID), BREAK_KERNEL_OK);
    ASSERT_TRUE(load_standard_weapon(kernel, actor, 2u));
    BreakKernelFireIntent fire;
    ASSERT_EQ(break_kernel_weapon_fire(kernel, actor, &fire), BREAK_KERNEL_OK);
    ASSERT_EQ(break_kernel_weapon_tick(kernel, actor, 2u), BREAK_KERNEL_OK);
    ASSERT_EQ(break_kernel_inventory_add(kernel, actor, AMMO_ID, 30u), BREAK_KERNEL_OK);
    ASSERT_EQ(break_kernel_weapon_begin_reload(kernel, actor), BREAK_KERNEL_OK);
    u32 slot = break_kernel_actor_slot(kernel, actor);
    ASSERT_NEQ(slot, UINT32_MAX);
    ASSERT_EQ(kernel->actors[slot].now_tick, 5u);
    ASSERT_EQ(kernel->actors[slot].next_fire_tick, 5u);
    ASSERT_EQ(kernel->actors[slot].reload_finish_tick, 8u);
    ASSERT_TRUE(kernel->actors[slot].reloading);

    ASSERT_EQ(break_kernel_weapon_unequip(kernel, actor), BREAK_KERNEL_OVERLOAD);
    ASSERT_EQ(kernel->actors[slot].weapon_id, WEAPON_ID);
    ASSERT_EQ(kernel->actors[slot].magazine, 1u);
    ASSERT_EQ(kernel->actors[slot].now_tick, 5u);
    ASSERT_EQ(kernel->actors[slot].next_fire_tick, 5u);
    ASSERT_EQ(kernel->actors[slot].reload_finish_tick, 8u);
    ASSERT_TRUE(kernel->actors[slot].reloading);
    ASSERT_EQ(kernel->fire_sequence, 1u);
    u32 reserve = 0;
    ASSERT_EQ(break_kernel_inventory_count(kernel, actor, AMMO_ID, &reserve), BREAK_KERNEL_OK);
    ASSERT_EQ(reserve, 30u);
    ASSERT_EQ(break_kernel_inventory_transfer(kernel, actor, other, AMMO_ID, 30u), BREAK_KERNEL_OK);
    ASSERT_EQ(break_kernel_weapon_unequip(kernel, actor), BREAK_KERNEL_OK);
    ASSERT_EQ(break_kernel_inventory_count(kernel, actor, AMMO_ID, &reserve), BREAK_KERNEL_OK);
    ASSERT_EQ(reserve, 1u);
    destroy_kernel(kernel, world);
}

TEST(definition_and_equipment_validate_descriptors_and_state) {
    World *world = make_world();
    BreakKernel *kernel = make_kernel(world, 1);
    ASSERT_NOT_NULL(kernel);
    Entity actor = spawn_pawn(kernel);
    ASSERT_TRUE(entity_valid(actor));
    BreakKernelWeaponDesc desc = {WEAPON_ID, AMMO_ID, 7u, 2u, 2u, 3u};
    ASSERT_EQ(break_kernel_weapon_define(kernel, &desc), BREAK_KERNEL_STALE);
    BreakKernelItemDesc ammo = {AMMO_ID, 30u};
    ASSERT_EQ(break_kernel_item_define(kernel, &ammo), BREAK_KERNEL_OK);
    ASSERT_EQ(break_kernel_weapon_define(kernel, NULL), BREAK_KERNEL_INVALID);
    ASSERT_EQ(break_kernel_weapon_define(NULL, &desc), BREAK_KERNEL_INVALID);
    ASSERT_EQ(break_kernel_weapon_define(kernel, &desc), BREAK_KERNEL_OK);
    ASSERT_EQ(break_kernel_weapon_define(kernel, &desc), BREAK_KERNEL_REJECTED);

    desc.weapon_id = 0;
    ASSERT_EQ(break_kernel_weapon_define(kernel, &desc), BREAK_KERNEL_INVALID);
    desc.weapon_id = 65;
    ASSERT_EQ(break_kernel_weapon_define(kernel, &desc), BREAK_KERNEL_INVALID);
    desc.weapon_id = 2;
    desc.ammo_item_id = 0;
    ASSERT_EQ(break_kernel_weapon_define(kernel, &desc), BREAK_KERNEL_INVALID);
    desc.ammo_item_id = 65;
    ASSERT_EQ(break_kernel_weapon_define(kernel, &desc), BREAK_KERNEL_INVALID);
    desc.ammo_item_id = 2;
    ASSERT_EQ(break_kernel_weapon_define(kernel, &desc), BREAK_KERNEL_STALE);
    desc.ammo_item_id = AMMO_ID;
    desc.damage = 0;
    ASSERT_EQ(break_kernel_weapon_define(kernel, &desc), BREAK_KERNEL_INVALID);
    desc.damage = 10001u;
    ASSERT_EQ(break_kernel_weapon_define(kernel, &desc), BREAK_KERNEL_INVALID);
    desc.damage = 7;
    desc.magazine_capacity = 0;
    ASSERT_EQ(break_kernel_weapon_define(kernel, &desc), BREAK_KERNEL_INVALID);
    desc.magazine_capacity = 1001u;
    ASSERT_EQ(break_kernel_weapon_define(kernel, &desc), BREAK_KERNEL_INVALID);
    desc.magazine_capacity = 2;
    desc.reload_ticks = 0;
    ASSERT_EQ(break_kernel_weapon_define(kernel, &desc), BREAK_KERNEL_INVALID);
    desc.reload_ticks = 3;
    desc.weapon_id = 64;
    desc.damage = 10000u;
    desc.magazine_capacity = 1000u;
    desc.fire_interval_ticks = UINT32_MAX;
    desc.reload_ticks = 1;
    ASSERT_EQ(break_kernel_weapon_define(kernel, &desc), BREAK_KERNEL_OK);

    ASSERT_EQ(break_kernel_weapon_equip(kernel, actor, 0), BREAK_KERNEL_INVALID);
    ASSERT_EQ(break_kernel_weapon_equip(kernel, actor, 2), BREAK_KERNEL_STALE);
    ASSERT_EQ(break_kernel_weapon_equip(kernel, actor, WEAPON_ID), BREAK_KERNEL_OK);
    ASSERT_EQ(break_kernel_weapon_equip(kernel, actor, WEAPON_ID), BREAK_KERNEL_REJECTED);
    ASSERT_EQ(break_kernel_weapon_equip(kernel, actor, 64u), BREAK_KERNEL_REJECTED);
    u32 equipped_slot = break_kernel_actor_slot(kernel, actor);
    ASSERT_NEQ(equipped_slot, UINT32_MAX);
    ASSERT_EQ(kernel->actors[equipped_slot].weapon_id, WEAPON_ID);
    ASSERT_EQ(kernel->actors[equipped_slot].magazine, 0u);
    ASSERT_EQ(break_kernel_weapon_begin_reload(kernel, actor), BREAK_KERNEL_REJECTED);
    u32 magazine = 0;
    ASSERT_EQ(break_kernel_weapon_ammo(kernel, actor, &magazine), BREAK_KERNEL_OK);
    ASSERT_EQ(magazine, 0u);
    destroy_kernel(kernel, world);
}

TEST(stale_handles_and_invalid_arguments_leave_weapon_state_unchanged) {
    World *world = make_world();
    BreakKernel *kernel = make_kernel(world, 1);
    ASSERT_NOT_NULL(kernel);
    Entity actor = spawn_pawn(kernel);
    ASSERT_TRUE(entity_valid(actor));
    ASSERT_TRUE(define_standard_weapon(kernel));
    ASSERT_EQ(break_kernel_weapon_equip(kernel, actor, WEAPON_ID), BREAK_KERNEL_OK);
    ASSERT_TRUE(load_standard_weapon(kernel, actor, 2u));
    Entity stale = actor;
    stale.generation++;
    BreakKernelFireIntent fire = sentinel_intent();
    BreakKernelFireIntent before = fire;
    u32 magazine = 99u;
    u32 slot = break_kernel_actor_slot(kernel, actor);
    ASSERT_NEQ(slot, UINT32_MAX);

    ASSERT_EQ(break_kernel_weapon_equip(kernel, stale, WEAPON_ID), BREAK_KERNEL_STALE);
    ASSERT_EQ(break_kernel_weapon_unequip(kernel, stale), BREAK_KERNEL_STALE);
    ASSERT_EQ(break_kernel_weapon_begin_reload(kernel, stale), BREAK_KERNEL_STALE);
    ASSERT_EQ(break_kernel_weapon_tick(kernel, stale, 1u), BREAK_KERNEL_STALE);
    ASSERT_EQ(break_kernel_weapon_fire(kernel, stale, &fire), BREAK_KERNEL_STALE);
    ASSERT_TRUE(memcmp(&fire, &before, sizeof(fire)) == 0);
    ASSERT_EQ(break_kernel_weapon_ammo(kernel, stale, &magazine), BREAK_KERNEL_STALE);
    ASSERT_EQ(magazine, 99u);
    ASSERT_EQ(break_kernel_weapon_equip(NULL, actor, WEAPON_ID), BREAK_KERNEL_INVALID);
    ASSERT_EQ(break_kernel_weapon_unequip(NULL, actor), BREAK_KERNEL_INVALID);
    ASSERT_EQ(break_kernel_weapon_begin_reload(NULL, actor), BREAK_KERNEL_INVALID);
    ASSERT_EQ(break_kernel_weapon_fire(kernel, actor, NULL), BREAK_KERNEL_INVALID);
    ASSERT_EQ(break_kernel_weapon_ammo(kernel, actor, NULL), BREAK_KERNEL_INVALID);
    ASSERT_EQ(kernel->actors[slot].weapon_id, WEAPON_ID);
    ASSERT_EQ(kernel->actors[slot].magazine, 2u);
    ASSERT_EQ(kernel->actors[slot].now_tick, 3u);
    ASSERT_EQ(kernel->actors[slot].next_fire_tick, 0u);
    ASSERT_EQ(kernel->actors[slot].reload_finish_tick, 0u);
    ASSERT_FALSE(kernel->actors[slot].reloading);
    ASSERT_EQ(kernel->fire_sequence, 0u);
    ASSERT_EQ(break_kernel_weapon_tick(NULL, actor, 1u), BREAK_KERNEL_INVALID);
    ASSERT_EQ(break_kernel_weapon_fire(NULL, actor, &fire), BREAK_KERNEL_INVALID);
    ASSERT_TRUE(memcmp(&fire, &before, sizeof(fire)) == 0);
    ASSERT_EQ(break_kernel_weapon_ammo(NULL, actor, &magazine), BREAK_KERNEL_INVALID);
    ASSERT_EQ(magazine, 99u);

    ASSERT_EQ(break_kernel_weapon_tick(kernel, actor, 0), BREAK_KERNEL_INVALID);
    ASSERT_EQ(kernel->actors[slot].now_tick, 3u);
    ASSERT_EQ(break_kernel_weapon_fire(kernel, actor, &fire), BREAK_KERNEL_OK);
    ASSERT_EQ(fire.sequence, 1u);
    ASSERT_EQ(break_kernel_weapon_ammo(kernel, actor, &magazine), BREAK_KERNEL_OK);
    ASSERT_EQ(magazine, 1u);
    destroy_kernel(kernel, world);
}

typedef struct {
    BreakKernel *kernel;
    Entity actor;
    Entity equip_actor;
    Entity reload_actor;
    BreakKernelWeaponDesc desc;
    BreakKernelError errors[7];
    BreakKernelFireIntent fire;
    u32 magazine;
} ThreadProbe;

static PLATFORM_THREAD_RET weapon_calls_off_thread(PLATFORM_THREAD_ARG arg) {
    ThreadProbe *probe = (ThreadProbe *)arg;
    probe->errors[0] = break_kernel_weapon_define(probe->kernel, &probe->desc);
    probe->errors[1] = break_kernel_weapon_equip(probe->kernel, probe->equip_actor, WEAPON_ID);
    probe->errors[2] = break_kernel_weapon_unequip(probe->kernel, probe->actor);
    probe->errors[3] = break_kernel_weapon_begin_reload(probe->kernel, probe->reload_actor);
    probe->errors[4] = break_kernel_weapon_tick(probe->kernel, probe->actor, 1u);
    probe->errors[5] = break_kernel_weapon_fire(probe->kernel, probe->actor, &probe->fire);
    probe->errors[6] = break_kernel_weapon_ammo(probe->kernel, probe->actor, &probe->magazine);
    return PLATFORM_THREAD_RETURN;
}

TEST(all_public_calls_reject_non_owner_without_mutating_state) {
    World *world = make_world();
    BreakKernel *kernel = make_kernel(world, 3);
    ASSERT_NOT_NULL(kernel);
    Entity actor = spawn_pawn(kernel);
    Entity equip_actor = spawn_pawn(kernel);
    Entity reload_actor = spawn_pawn(kernel);
    ASSERT_TRUE(entity_valid(actor));
    ASSERT_TRUE(entity_valid(equip_actor));
    ASSERT_TRUE(entity_valid(reload_actor));
    ASSERT_TRUE(define_standard_weapon(kernel));
    ASSERT_EQ(break_kernel_weapon_equip(kernel, actor, WEAPON_ID), BREAK_KERNEL_OK);
    ASSERT_TRUE(load_standard_weapon(kernel, actor, 2u));
    ASSERT_EQ(break_kernel_weapon_equip(kernel, reload_actor, WEAPON_ID), BREAK_KERNEL_OK);
    ASSERT_TRUE(load_standard_weapon(kernel, reload_actor, 2u));
    BreakKernelFireIntent setup_fire;
    ASSERT_EQ(break_kernel_weapon_fire(kernel, reload_actor, &setup_fire), BREAK_KERNEL_OK);
    ASSERT_EQ(setup_fire.sequence, 1u);
    ASSERT_EQ(break_kernel_inventory_add(kernel, reload_actor, AMMO_ID, 5u), BREAK_KERNEL_OK);
    ASSERT_EQ(break_kernel_weapon_begin_reload(kernel, reload_actor), BREAK_KERNEL_OK);
    ASSERT_EQ(break_kernel_inventory_transfer(kernel, reload_actor, actor, AMMO_ID, 5u), BREAK_KERNEL_OK);
    ASSERT_EQ(break_kernel_weapon_tick(kernel, reload_actor, 3u), BREAK_KERNEL_OVERLOAD);
    ASSERT_EQ(break_kernel_inventory_add(kernel, reload_actor, AMMO_ID, 5u), BREAK_KERNEL_OK);
    u32 setup_reload_slot = break_kernel_actor_slot(kernel, reload_actor);
    ASSERT_NEQ(setup_reload_slot, UINT32_MAX);
    kernel->actors[setup_reload_slot].now_tick = 6u;
    ThreadProbe probe;
    probe.kernel = kernel;
    probe.actor = actor;
    probe.equip_actor = equip_actor;
    probe.reload_actor = reload_actor;
    probe.desc.weapon_id = 2;
    probe.desc.ammo_item_id = AMMO_ID;
    probe.desc.damage = 9;
    probe.desc.magazine_capacity = 3;
    probe.desc.fire_interval_ticks = 1;
    probe.desc.reload_ticks = 1;
    probe.fire = sentinel_intent();
    BreakKernelFireIntent before = probe.fire;
    probe.magazine = 99u;
    PlatformThread thread;
    ASSERT_TRUE(platform_thread_create(&thread, weapon_calls_off_thread, &probe));
    platform_thread_join(thread);
    for (u32 i = 0; i < 7; i++) {
        ASSERT_EQ(probe.errors[i], BREAK_KERNEL_REJECTED);
    }
    ASSERT_TRUE(memcmp(&probe.fire, &before, sizeof(probe.fire)) == 0);
    ASSERT_EQ(probe.magazine, 99u);
    u32 magazine = 77u;
    ASSERT_EQ(break_kernel_weapon_ammo(kernel, equip_actor, &magazine), BREAK_KERNEL_REJECTED);
    ASSERT_EQ(magazine, 77u);
    ASSERT_EQ(break_kernel_weapon_equip(kernel, equip_actor, WEAPON_ID), BREAK_KERNEL_OK);
    u32 reload_slot = break_kernel_actor_slot(kernel, reload_actor);
    ASSERT_NEQ(reload_slot, UINT32_MAX);
    ASSERT_EQ(kernel->actors[reload_slot].magazine, 1u);
    ASSERT_EQ(kernel->actors[reload_slot].now_tick, 6u);
    ASSERT_EQ(kernel->actors[reload_slot].reload_finish_tick, 6u);
    ASSERT_TRUE(kernel->actors[reload_slot].reloading);
    u32 reserve = 0;
    ASSERT_EQ(break_kernel_inventory_count(kernel, reload_actor, AMMO_ID, &reserve), BREAK_KERNEL_OK);
    ASSERT_EQ(reserve, 5u);
    ASSERT_EQ(break_kernel_weapon_begin_reload(kernel, reload_actor), BREAK_KERNEL_OK);
    ASSERT_EQ(kernel->actors[reload_slot].magazine, 2u);
    ASSERT_EQ(break_kernel_inventory_count(kernel, reload_actor, AMMO_ID, &reserve), BREAK_KERNEL_OK);
    ASSERT_EQ(reserve, 4u);
    ASSERT_EQ(break_kernel_weapon_define(kernel, &probe.desc), BREAK_KERNEL_OK);
    ASSERT_EQ(break_kernel_weapon_ammo(kernel, actor, &magazine), BREAK_KERNEL_OK);
    ASSERT_EQ(magazine, 2u);
    BreakKernelFireIntent fire;
    ASSERT_EQ(break_kernel_weapon_fire(kernel, actor, &fire), BREAK_KERNEL_OK);
    ASSERT_EQ(fire.sequence, 2u);
    destroy_kernel(kernel, world);
}

TEST(tick_cooldown_reload_and_sequence_overflow_are_atomic) {
    World *world = make_world();
    BreakKernel *kernel = make_kernel(world, 1);
    ASSERT_NOT_NULL(kernel);
    Entity actor = spawn_pawn(kernel);
    ASSERT_TRUE(entity_valid(actor));
    ASSERT_TRUE(define_standard_weapon(kernel));
    ASSERT_EQ(break_kernel_weapon_equip(kernel, actor, WEAPON_ID), BREAK_KERNEL_OK);
    ASSERT_TRUE(load_standard_weapon(kernel, actor, 2u));
    u32 slot = break_kernel_actor_slot(kernel, actor);
    ASSERT_NEQ(slot, UINT32_MAX);
    BreakKernelActor *state = &kernel->actors[slot];
    BreakKernelFireIntent fire = sentinel_intent();
    BreakKernelFireIntent before = fire;

    state->now_tick = UINT32_MAX;
    state->next_fire_tick = UINT32_MAX;
    ASSERT_EQ(break_kernel_weapon_fire(kernel, actor, &fire), BREAK_KERNEL_OVERLOAD);
    ASSERT_TRUE(memcmp(&fire, &before, sizeof(fire)) == 0);
    ASSERT_EQ(state->weapon_id, WEAPON_ID);
    ASSERT_EQ(state->now_tick, UINT32_MAX);
    ASSERT_EQ(state->next_fire_tick, UINT32_MAX);
    ASSERT_EQ(state->reload_finish_tick, 0u);
    ASSERT_FALSE(state->reloading);
    ASSERT_EQ(state->magazine, 2u);
    ASSERT_EQ(kernel->fire_sequence, 0u);

    state->now_tick = 0;
    state->next_fire_tick = 0;
    kernel->fire_sequence = UINT64_MAX;
    ASSERT_EQ(break_kernel_weapon_fire(kernel, actor, &fire), BREAK_KERNEL_OVERLOAD);
    ASSERT_TRUE(memcmp(&fire, &before, sizeof(fire)) == 0);
    ASSERT_EQ(state->weapon_id, WEAPON_ID);
    ASSERT_EQ(state->now_tick, 0u);
    ASSERT_EQ(state->next_fire_tick, 0u);
    ASSERT_EQ(state->reload_finish_tick, 0u);
    ASSERT_FALSE(state->reloading);
    ASSERT_EQ(state->magazine, 2u);
    ASSERT_EQ(kernel->fire_sequence, UINT64_MAX);

    kernel->fire_sequence = 0;
    state->now_tick = UINT32_MAX;
    ASSERT_EQ(break_kernel_weapon_tick(kernel, actor, 1u), BREAK_KERNEL_OVERLOAD);
    ASSERT_EQ(state->weapon_id, WEAPON_ID);
    ASSERT_EQ(state->now_tick, UINT32_MAX);
    ASSERT_EQ(state->next_fire_tick, 0u);
    ASSERT_EQ(state->reload_finish_tick, 0u);
    ASSERT_FALSE(state->reloading);
    ASSERT_EQ(state->magazine, 2u);
    ASSERT_EQ(kernel->fire_sequence, 0u);
    state->now_tick = 0;
    ASSERT_EQ(break_kernel_weapon_fire(kernel, actor, &fire), BREAK_KERNEL_OK);
    ASSERT_EQ(fire.sequence, 1u);
    ASSERT_EQ(break_kernel_inventory_add(kernel, actor, AMMO_ID, 5u), BREAK_KERNEL_OK);
    state->now_tick = UINT32_MAX - 1u;
    state->next_fire_tick = 0;
    ASSERT_EQ(break_kernel_weapon_begin_reload(kernel, actor), BREAK_KERNEL_OVERLOAD);
    ASSERT_EQ(state->weapon_id, WEAPON_ID);
    ASSERT_EQ(state->now_tick, UINT32_MAX - 1u);
    ASSERT_EQ(state->next_fire_tick, 0u);
    ASSERT_EQ(state->reload_finish_tick, 0u);
    ASSERT_FALSE(state->reloading);
    ASSERT_EQ(state->magazine, 1u);
    ASSERT_EQ(kernel->fire_sequence, 1u);
    u32 reserve = 0;
    ASSERT_EQ(break_kernel_inventory_count(kernel, actor, AMMO_ID, &reserve), BREAK_KERNEL_OK);
    ASSERT_EQ(reserve, 5u);
    destroy_kernel(kernel, world);
}

TEST(failed_reload_near_max_tick_rolls_back_and_can_retry) {
    World *world = make_world();
    BreakKernel *kernel = make_kernel(world, 2);
    ASSERT_NOT_NULL(kernel);
    Entity actor = spawn_pawn(kernel);
    Entity other = spawn_pawn(kernel);
    ASSERT_TRUE(entity_valid(actor));
    ASSERT_TRUE(entity_valid(other));
    ASSERT_TRUE(define_standard_weapon(kernel));
    ASSERT_EQ(break_kernel_weapon_equip(kernel, actor, WEAPON_ID), BREAK_KERNEL_OK);
    ASSERT_TRUE(load_standard_weapon(kernel, actor, 3u));
    BreakKernelFireIntent fire;
    ASSERT_EQ(break_kernel_weapon_fire(kernel, actor, &fire), BREAK_KERNEL_OK);
    u32 slot = break_kernel_actor_slot(kernel, actor);
    ASSERT_NEQ(slot, UINT32_MAX);
    BreakKernelActor *state = &kernel->actors[slot];
    state->now_tick = UINT32_MAX - 3u;
    state->next_fire_tick = 0;
    ASSERT_EQ(break_kernel_weapon_begin_reload(kernel, actor), BREAK_KERNEL_OK);
    ASSERT_EQ(state->reload_finish_tick, UINT32_MAX);
    ASSERT_EQ(break_kernel_inventory_transfer(kernel, actor, other, AMMO_ID, 1u), BREAK_KERNEL_OK);
    ASSERT_EQ(break_kernel_weapon_tick(kernel, actor, 3u), BREAK_KERNEL_OVERLOAD);
    ASSERT_EQ(state->weapon_id, WEAPON_ID);
    ASSERT_EQ(state->magazine, 1u);
    ASSERT_EQ(state->now_tick, UINT32_MAX - 3u);
    ASSERT_EQ(state->next_fire_tick, 0u);
    ASSERT_EQ(state->reload_finish_tick, UINT32_MAX);
    ASSERT_TRUE(state->reloading);
    ASSERT_EQ(kernel->fire_sequence, 1u);
    u32 reserve = 99u;
    ASSERT_EQ(break_kernel_inventory_count(kernel, actor, AMMO_ID, &reserve), BREAK_KERNEL_OK);
    ASSERT_EQ(reserve, 0u);

    ASSERT_EQ(break_kernel_inventory_add(kernel, actor, AMMO_ID, 1u), BREAK_KERNEL_OK);
    ASSERT_EQ(break_kernel_weapon_tick(kernel, actor, 3u), BREAK_KERNEL_OK);
    ASSERT_EQ(state->weapon_id, WEAPON_ID);
    ASSERT_EQ(state->now_tick, UINT32_MAX);
    ASSERT_EQ(state->next_fire_tick, 0u);
    ASSERT_FALSE(state->reloading);
    ASSERT_EQ(state->reload_finish_tick, 0u);
    ASSERT_EQ(state->magazine, 2u);
    ASSERT_EQ(kernel->fire_sequence, 1u);
    ASSERT_EQ(break_kernel_inventory_count(kernel, actor, AMMO_ID, &reserve), BREAK_KERNEL_OK);
    ASSERT_EQ(reserve, 0u);
    destroy_kernel(kernel, world);
}

TEST(despawn_clears_weapon_state_and_generation_reuse_starts_clean) {
    World *world = make_world();
    BreakKernel *kernel = make_kernel(world, 1);
    ASSERT_NOT_NULL(kernel);
    Entity old = spawn_pawn(kernel);
    ASSERT_TRUE(entity_valid(old));
    ASSERT_TRUE(define_standard_weapon(kernel));
    ASSERT_EQ(break_kernel_weapon_equip(kernel, old, WEAPON_ID), BREAK_KERNEL_OK);
    ASSERT_TRUE(load_standard_weapon(kernel, old, 2u));
    BreakKernelFireIntent fire;
    ASSERT_EQ(break_kernel_weapon_fire(kernel, old, &fire), BREAK_KERNEL_OK);
    ASSERT_EQ(fire.sequence, 1u);
    ASSERT_EQ(break_kernel_inventory_add(kernel, old, AMMO_ID, 5u), BREAK_KERNEL_OK);
    ASSERT_EQ(break_kernel_weapon_begin_reload(kernel, old), BREAK_KERNEL_OK);
    ASSERT_EQ(break_kernel_despawn(kernel, old), BREAK_KERNEL_OK);
    ASSERT_EQ(break_kernel_weapon_fire(kernel, old, &fire), BREAK_KERNEL_STALE);

    Entity replacement = spawn_pawn(kernel);
    ASSERT_TRUE(entity_valid(replacement));
    ASSERT_EQ(replacement.index, old.index);
    ASSERT_NEQ(replacement.generation, old.generation);
    u32 magazine = 99u;
    ASSERT_EQ(break_kernel_weapon_ammo(kernel, replacement, &magazine), BREAK_KERNEL_REJECTED);
    ASSERT_EQ(magazine, 99u);
    u32 reserve = 99u;
    ASSERT_EQ(break_kernel_inventory_count(kernel, replacement, AMMO_ID, &reserve), BREAK_KERNEL_OK);
    ASSERT_EQ(reserve, 0u);
    ASSERT_EQ(break_kernel_weapon_equip(kernel, replacement, WEAPON_ID), BREAK_KERNEL_OK);
    ASSERT_EQ(break_kernel_weapon_ammo(kernel, replacement, &magazine), BREAK_KERNEL_OK);
    ASSERT_EQ(magazine, 0u);
    ASSERT_TRUE(load_standard_weapon(kernel, replacement, 2u));
    ASSERT_EQ(break_kernel_weapon_fire(kernel, replacement, &fire), BREAK_KERNEL_OK);
    ASSERT_EQ(fire.sequence, 2u);
    ASSERT_EQ(fire.shooter.generation, replacement.generation);
    destroy_kernel(kernel, world);
}

TEST(equip_cycles_conserve_ammo_and_start_empty) {
    World *world = make_world();
    BreakKernel *kernel = make_kernel(world, 1);
    ASSERT_NOT_NULL(kernel);
    Entity actor = spawn_pawn(kernel);
    ASSERT_TRUE(entity_valid(actor));
    ASSERT_TRUE(define_standard_weapon(kernel));
    ASSERT_EQ(break_kernel_weapon_equip(kernel, actor, WEAPON_ID), BREAK_KERNEL_OK);
    ASSERT_EQ(break_kernel_weapon_unequip(kernel, actor), BREAK_KERNEL_OK);
    ASSERT_EQ(break_kernel_weapon_equip(kernel, actor, WEAPON_ID), BREAK_KERNEL_OK);
    ASSERT_EQ(break_kernel_weapon_unequip(kernel, actor), BREAK_KERNEL_OK);
    u32 reserve = 99u;
    ASSERT_EQ(break_kernel_inventory_count(kernel, actor, AMMO_ID, &reserve), BREAK_KERNEL_OK);
    ASSERT_EQ(reserve, 0u);

    ASSERT_EQ(break_kernel_weapon_equip(kernel, actor, WEAPON_ID), BREAK_KERNEL_OK);
    u32 magazine = 99u;
    ASSERT_EQ(break_kernel_weapon_ammo(kernel, actor, &magazine), BREAK_KERNEL_OK);
    ASSERT_EQ(magazine, 0u);
    ASSERT_EQ(break_kernel_inventory_add(kernel, actor, AMMO_ID, 2u), BREAK_KERNEL_OK);
    ASSERT_EQ(break_kernel_weapon_begin_reload(kernel, actor), BREAK_KERNEL_OK);
    ASSERT_EQ(break_kernel_weapon_tick(kernel, actor, 3u), BREAK_KERNEL_OK);
    ASSERT_EQ(break_kernel_weapon_ammo(kernel, actor, &magazine), BREAK_KERNEL_OK);
    ASSERT_EQ(magazine, 2u);
    ASSERT_EQ(break_kernel_inventory_count(kernel, actor, AMMO_ID, &reserve), BREAK_KERNEL_OK);
    ASSERT_EQ(reserve, 0u);
    ASSERT_EQ(break_kernel_weapon_unequip(kernel, actor), BREAK_KERNEL_OK);
    ASSERT_EQ(break_kernel_inventory_count(kernel, actor, AMMO_ID, &reserve), BREAK_KERNEL_OK);
    ASSERT_EQ(reserve, 2u);
    ASSERT_EQ(break_kernel_weapon_equip(kernel, actor, WEAPON_ID), BREAK_KERNEL_OK);
    ASSERT_EQ(break_kernel_weapon_ammo(kernel, actor, &magazine), BREAK_KERNEL_OK);
    ASSERT_EQ(magazine, 0u);
    ASSERT_EQ(break_kernel_inventory_count(kernel, actor, AMMO_ID, &reserve), BREAK_KERNEL_OK);
    ASSERT_EQ(reserve, 2u);
    ASSERT_EQ(break_kernel_weapon_begin_reload(kernel, actor), BREAK_KERNEL_OK);
    ASSERT_EQ(break_kernel_weapon_tick(kernel, actor, 3u), BREAK_KERNEL_OK);
    ASSERT_EQ(break_kernel_weapon_ammo(kernel, actor, &magazine), BREAK_KERNEL_OK);
    ASSERT_EQ(magazine, 2u);
    ASSERT_EQ(break_kernel_inventory_count(kernel, actor, AMMO_ID, &reserve), BREAK_KERNEL_OK);
    ASSERT_EQ(reserve, 0u);
    ASSERT_EQ(break_kernel_weapon_unequip(kernel, actor), BREAK_KERNEL_OK);
    ASSERT_EQ(break_kernel_inventory_count(kernel, actor, AMMO_ID, &reserve), BREAK_KERNEL_OK);
    ASSERT_EQ(reserve, 2u);
    destroy_kernel(kernel, world);
}

TEST(reequip_preserves_actor_fire_cooldown) {
    World *world = make_world();
    BreakKernel *kernel = make_kernel(world, 1);
    ASSERT_NOT_NULL(kernel);
    Entity actor = spawn_pawn(kernel);
    ASSERT_TRUE(entity_valid(actor));
    ASSERT_TRUE(define_standard_weapon(kernel));
    ASSERT_EQ(break_kernel_weapon_equip(kernel, actor, WEAPON_ID), BREAK_KERNEL_OK);
    u32 slot = break_kernel_actor_slot(kernel, actor);
    ASSERT_NEQ(slot, UINT32_MAX);
    kernel->actors[slot].magazine = 2u;
    BreakKernelFireIntent fire;
    ASSERT_EQ(break_kernel_weapon_fire(kernel, actor, &fire), BREAK_KERNEL_OK);
    ASSERT_EQ(fire.sequence, 1u);
    ASSERT_EQ(kernel->actors[slot].next_fire_tick, 2u);
    ASSERT_EQ(break_kernel_weapon_unequip(kernel, actor), BREAK_KERNEL_OK);
    ASSERT_EQ(break_kernel_weapon_equip(kernel, actor, WEAPON_ID), BREAK_KERNEL_OK);
    kernel->actors[slot].magazine = 1u;

    fire = sentinel_intent();
    BreakKernelFireIntent before = fire;
    ASSERT_EQ(break_kernel_weapon_fire(kernel, actor, &fire), BREAK_KERNEL_REJECTED);
    ASSERT_TRUE(memcmp(&fire, &before, sizeof(fire)) == 0);
    ASSERT_EQ(kernel->actors[slot].magazine, 1u);
    ASSERT_EQ(kernel->actors[slot].now_tick, 0u);
    ASSERT_EQ(kernel->actors[slot].next_fire_tick, 2u);
    ASSERT_EQ(kernel->fire_sequence, 1u);
    ASSERT_EQ(break_kernel_weapon_tick(kernel, actor, 2u), BREAK_KERNEL_OK);
    ASSERT_EQ(break_kernel_weapon_fire(kernel, actor, &fire), BREAK_KERNEL_OK);
    ASSERT_EQ(fire.sequence, 2u);
    destroy_kernel(kernel, world);
}

TEST(reequip_cancels_reload_without_granting_magazine) {
    World *world = make_world();
    BreakKernel *kernel = make_kernel(world, 1);
    ASSERT_NOT_NULL(kernel);
    Entity actor = spawn_pawn(kernel);
    ASSERT_TRUE(entity_valid(actor));
    ASSERT_TRUE(define_standard_weapon(kernel));
    ASSERT_EQ(break_kernel_weapon_equip(kernel, actor, WEAPON_ID), BREAK_KERNEL_OK);
    u32 slot = break_kernel_actor_slot(kernel, actor);
    ASSERT_NEQ(slot, UINT32_MAX);
    kernel->actors[slot].magazine = 0u;
    ASSERT_EQ(break_kernel_inventory_add(kernel, actor, AMMO_ID, 2u), BREAK_KERNEL_OK);
    ASSERT_EQ(break_kernel_weapon_begin_reload(kernel, actor), BREAK_KERNEL_OK);
    ASSERT_TRUE(kernel->actors[slot].reloading);
    ASSERT_EQ(break_kernel_weapon_unequip(kernel, actor), BREAK_KERNEL_OK);
    u32 reserve = 99u;
    ASSERT_EQ(break_kernel_inventory_count(kernel, actor, AMMO_ID, &reserve), BREAK_KERNEL_OK);
    ASSERT_EQ(reserve, 2u);

    ASSERT_EQ(break_kernel_weapon_equip(kernel, actor, WEAPON_ID), BREAK_KERNEL_OK);
    u32 magazine = 99u;
    ASSERT_EQ(break_kernel_weapon_ammo(kernel, actor, &magazine), BREAK_KERNEL_OK);
    ASSERT_EQ(magazine, 0u);
    ASSERT_EQ(break_kernel_inventory_count(kernel, actor, AMMO_ID, &reserve), BREAK_KERNEL_OK);
    ASSERT_EQ(reserve, 2u);
    ASSERT_FALSE(kernel->actors[slot].reloading);
    ASSERT_EQ(kernel->actors[slot].reload_finish_tick, 0u);
    ASSERT_EQ(break_kernel_weapon_tick(kernel, actor, 1u), BREAK_KERNEL_OK);
    ASSERT_EQ(break_kernel_weapon_ammo(kernel, actor, &magazine), BREAK_KERNEL_OK);
    ASSERT_EQ(magazine, 0u);
    ASSERT_EQ(break_kernel_weapon_begin_reload(kernel, actor), BREAK_KERNEL_OK);
    ASSERT_EQ(break_kernel_weapon_tick(kernel, actor, 2u), BREAK_KERNEL_OK);
    ASSERT_EQ(break_kernel_weapon_ammo(kernel, actor, &magazine), BREAK_KERNEL_OK);
    ASSERT_EQ(magazine, 0u);
    ASSERT_EQ(break_kernel_weapon_tick(kernel, actor, 1u), BREAK_KERNEL_OK);
    ASSERT_EQ(break_kernel_weapon_ammo(kernel, actor, &magazine), BREAK_KERNEL_OK);
    ASSERT_EQ(magazine, 2u);
    ASSERT_EQ(break_kernel_inventory_count(kernel, actor, AMMO_ID, &reserve), BREAK_KERNEL_OK);
    ASSERT_EQ(reserve, 0u);
    destroy_kernel(kernel, world);
}

TEST(weapon_tick_reload_failure_rolls_back_all_state_and_inventory) {
    World *world = make_world();
    BreakKernel *kernel = make_kernel(world, 1);
    ASSERT_NOT_NULL(kernel);
    Entity actor = spawn_pawn(kernel);
    ASSERT_TRUE(entity_valid(actor));
    ASSERT_TRUE(define_standard_weapon(kernel));
    ASSERT_EQ(break_kernel_weapon_equip(kernel, actor, WEAPON_ID), BREAK_KERNEL_OK);
    u32 slot = break_kernel_actor_slot(kernel, actor);
    ASSERT_NEQ(slot, UINT32_MAX);
    kernel->actors[slot].magazine = 0u;
    kernel->actors[slot].now_tick = 7u;
    kernel->actors[slot].next_fire_tick = 9u;
    kernel->actors[slot].reload_finish_tick = 10u;
    kernel->actors[slot].reloading = true;
    kernel->fire_sequence = 4u;
    ASSERT_EQ(break_kernel_inventory_add(kernel, actor, AMMO_ID, 1u), BREAK_KERNEL_OK);

    ASSERT_EQ(break_kernel_weapon_tick(kernel, actor, 4u), BREAK_KERNEL_OVERLOAD);
    ASSERT_EQ(kernel->actors[slot].weapon_id, WEAPON_ID);
    ASSERT_EQ(kernel->actors[slot].magazine, 0u);
    ASSERT_EQ(kernel->actors[slot].now_tick, 7u);
    ASSERT_EQ(kernel->actors[slot].next_fire_tick, 9u);
    ASSERT_EQ(kernel->actors[slot].reload_finish_tick, 10u);
    ASSERT_TRUE(kernel->actors[slot].reloading);
    ASSERT_EQ(kernel->fire_sequence, 4u);
    u32 reserve = 0;
    ASSERT_EQ(break_kernel_inventory_count(kernel, actor, AMMO_ID, &reserve), BREAK_KERNEL_OK);
    ASSERT_EQ(reserve, 1u);

    ASSERT_EQ(break_kernel_inventory_add(kernel, actor, AMMO_ID, 1u), BREAK_KERNEL_OK);
    ASSERT_EQ(break_kernel_weapon_tick(kernel, actor, 4u), BREAK_KERNEL_OK);
    ASSERT_EQ(kernel->actors[slot].magazine, 2u);
    ASSERT_EQ(kernel->actors[slot].now_tick, 11u);
    ASSERT_EQ(kernel->actors[slot].next_fire_tick, 9u);
    ASSERT_EQ(kernel->actors[slot].reload_finish_tick, 0u);
    ASSERT_FALSE(kernel->actors[slot].reloading);
    ASSERT_EQ(kernel->fire_sequence, 4u);
    ASSERT_EQ(break_kernel_inventory_count(kernel, actor, AMMO_ID, &reserve), BREAK_KERNEL_OK);
    ASSERT_EQ(reserve, 0u);
    destroy_kernel(kernel, world);
}

TEST_MAIN_BEGIN()
    RUN_TEST(fire_cooldown_reload_and_intent_follow_authoritative_state);
    RUN_TEST(reload_without_reserve_rejects_and_failed_deduction_can_retry);
    RUN_TEST(fire_rejects_during_reload_with_round_and_expired_cooldown);
    RUN_TEST(fire_with_unknown_equipped_weapon_is_stale_and_atomic);
    RUN_TEST(unequip_returns_magazine_atomically_and_rolls_back_capacity_failure);
    RUN_TEST(unequip_capacity_failure_preserves_reload_and_cooldown);
    RUN_TEST(definition_and_equipment_validate_descriptors_and_state);
    RUN_TEST(stale_handles_and_invalid_arguments_leave_weapon_state_unchanged);
    RUN_TEST(all_public_calls_reject_non_owner_without_mutating_state);
    RUN_TEST(tick_cooldown_reload_and_sequence_overflow_are_atomic);
    RUN_TEST(failed_reload_near_max_tick_rolls_back_and_can_retry);
    RUN_TEST(weapon_tick_reload_failure_rolls_back_all_state_and_inventory);
    RUN_TEST(equip_cycles_conserve_ammo_and_start_empty);
    RUN_TEST(reequip_preserves_actor_fire_cooldown);
    RUN_TEST(reequip_cancels_reload_without_granting_magazine);
    RUN_TEST(despawn_clears_weapon_state_and_generation_reuse_starts_clean);
TEST_MAIN_END()
