#include "test_framework.h"
#include <game/break_game_internal.h>
#include <core/platform_thread.h>
#include <stdint.h>

#define AMMO_ID   1u
#define WEAPON_ID 1u

static World *make_world(void) {
    World *world = world_create();
    world_register_component(world, BREAK_GAME_POSITION_COMPONENT, sizeof(Vec3));
    return world;
}

static BreakGame *make_game(World *world, u32 max_actors) {
    BreakGameConfig cfg;
    cfg.max_classes = 0;
    cfg.max_actors = max_actors;
    return break_game_create(world, &cfg);
}

static Entity spawn_pawn(BreakGame *game) {
    ComponentType comps[1] = {BREAK_GAME_POSITION_COMPONENT};
    BreakGameClassDesc desc;
    desc.name = "pawn";
    desc.components = comps;
    desc.component_count = 1;
    desc.lua_module = NULL;
    u32 class_id = 0;
    BreakGameError registered = break_game_register_class(game, &desc, &class_id);
    if (registered == BREAK_GAME_REJECTED) {
        class_id = 1;
    } else if (registered != BREAK_GAME_OK) {
        return ENTITY_NULL;
    }
    BreakGameSpawn spawn;
    spawn.class_id = class_id;
    spawn.position = vec3(0, 0, 0);
    Entity entity = ENTITY_NULL;
    if (break_game_spawn(game, &spawn, &entity) != BREAK_GAME_OK) {
        return ENTITY_NULL;
    }
    return entity;
}

static bool define_standard_weapon(BreakGame *game) {
    BreakGameItemDesc ammo = {AMMO_ID, 30u};
    BreakGameWeaponDesc weapon = {WEAPON_ID, AMMO_ID, 7u, 2u, 2u, 3u};
    return break_game_item_define(game, &ammo) == BREAK_GAME_OK &&
           break_game_weapon_define(game, &weapon) == BREAK_GAME_OK;
}

static BreakGameFireIntent sentinel_intent(void) {
    BreakGameFireIntent intent;
    intent.shooter = ENTITY_NULL;
    intent.weapon_id = 88u;
    intent.damage = 99u;
    intent.sequence = 77u;
    return intent;
}

static void destroy_game(BreakGame *game, World *world) {
    break_game_destroy(game);
    world_destroy(world);
}

TEST(fire_cooldown_reload_and_intent_follow_authoritative_state) {
    World *world = make_world();
    BreakGame *game = make_game(world, 2);
    ASSERT_NOT_NULL(game);
    Entity actor = spawn_pawn(game);
    ASSERT_TRUE(entity_valid(actor));
    ASSERT_TRUE(define_standard_weapon(game));
    BreakGameFireIntent fire = sentinel_intent();
    BreakGameFireIntent before = fire;
    ASSERT_EQ(break_game_weapon_fire(game, actor, &fire), BREAK_GAME_REJECTED);
    ASSERT_TRUE(memcmp(&fire, &before, sizeof(fire)) == 0);
    ASSERT_EQ(break_game_weapon_equip(game, actor, 2u), BREAK_GAME_STALE);
    ASSERT_EQ(break_game_weapon_equip(game, actor, WEAPON_ID), BREAK_GAME_OK);
    u32 magazine = 0;
    ASSERT_EQ(break_game_weapon_ammo(game, actor, &magazine), BREAK_GAME_OK);
    ASSERT_EQ(magazine, 2u);
    ASSERT_EQ(break_game_inventory_add(game, actor, AMMO_ID, 5u), BREAK_GAME_OK);

    ASSERT_EQ(break_game_weapon_fire(game, actor, &fire), BREAK_GAME_OK);
    ASSERT_EQ(fire.shooter.index, actor.index);
    ASSERT_EQ(fire.shooter.generation, actor.generation);
    ASSERT_EQ(fire.weapon_id, WEAPON_ID);
    ASSERT_EQ(fire.damage, 7u);
    ASSERT_EQ(fire.sequence, 1u);
    ASSERT_EQ(break_game_weapon_ammo(game, actor, &magazine), BREAK_GAME_OK);
    ASSERT_EQ(magazine, 1u);

    fire = sentinel_intent();
    before = fire;
    ASSERT_EQ(break_game_weapon_fire(game, actor, &fire), BREAK_GAME_REJECTED);
    ASSERT_TRUE(memcmp(&fire, &before, sizeof(fire)) == 0);
    ASSERT_EQ(break_game_weapon_tick(game, actor, 1u), BREAK_GAME_OK);
    ASSERT_EQ(break_game_weapon_fire(game, actor, &fire), BREAK_GAME_REJECTED);
    ASSERT_EQ(break_game_weapon_tick(game, actor, 1u), BREAK_GAME_OK);
    ASSERT_EQ(break_game_weapon_fire(game, actor, &fire), BREAK_GAME_OK);
    ASSERT_EQ(fire.sequence, 2u);
    ASSERT_EQ(break_game_weapon_ammo(game, actor, &magazine), BREAK_GAME_OK);
    ASSERT_EQ(magazine, 0u);

    fire = sentinel_intent();
    before = fire;
    ASSERT_EQ(break_game_weapon_fire(game, actor, &fire), BREAK_GAME_REJECTED);
    ASSERT_TRUE(memcmp(&fire, &before, sizeof(fire)) == 0);
    ASSERT_EQ(break_game_weapon_begin_reload(game, actor), BREAK_GAME_OK);
    u32 reload_slot = break_game_actor_slot(game, actor);
    ASSERT_NEQ(reload_slot, UINT32_MAX);
    u32 reload_now = game->actors[reload_slot].now_tick;
    u32 reload_next_fire = game->actors[reload_slot].next_fire_tick;
    u32 reload_finish = game->actors[reload_slot].reload_finish_tick;
    ASSERT_EQ(break_game_weapon_begin_reload(game, actor), BREAK_GAME_REJECTED);
    ASSERT_EQ(game->actors[reload_slot].now_tick, reload_now);
    ASSERT_EQ(game->actors[reload_slot].next_fire_tick, reload_next_fire);
    ASSERT_EQ(game->actors[reload_slot].reload_finish_tick, reload_finish);
    ASSERT_TRUE(game->actors[reload_slot].reloading);
    u32 reload_reserve = 0;
    ASSERT_EQ(break_game_inventory_count(game, actor, AMMO_ID, &reload_reserve), BREAK_GAME_OK);
    ASSERT_EQ(reload_reserve, 5u);
    ASSERT_EQ(break_game_weapon_fire(game, actor, &fire), BREAK_GAME_REJECTED);
    ASSERT_TRUE(memcmp(&fire, &before, sizeof(fire)) == 0);
    ASSERT_EQ(break_game_weapon_tick(game, actor, 2u), BREAK_GAME_OK);
    ASSERT_EQ(break_game_weapon_ammo(game, actor, &magazine), BREAK_GAME_OK);
    ASSERT_EQ(magazine, 0u);
    ASSERT_EQ(break_game_weapon_tick(game, actor, 1u), BREAK_GAME_OK);
    ASSERT_EQ(break_game_weapon_ammo(game, actor, &magazine), BREAK_GAME_OK);
    ASSERT_EQ(magazine, 2u);
    u32 reserve = 0;
    ASSERT_EQ(break_game_inventory_count(game, actor, AMMO_ID, &reserve), BREAK_GAME_OK);
    ASSERT_EQ(reserve, 3u);
    ASSERT_EQ(break_game_weapon_fire(game, actor, &fire), BREAK_GAME_OK);
    ASSERT_EQ(fire.sequence, 3u);
    destroy_game(game, world);
}

TEST(reload_without_reserve_rejects_and_failed_deduction_can_retry) {
    World *world = make_world();
    BreakGame *game = make_game(world, 2);
    ASSERT_NOT_NULL(game);
    Entity actor = spawn_pawn(game);
    Entity other = spawn_pawn(game);
    ASSERT_TRUE(entity_valid(actor));
    ASSERT_TRUE(entity_valid(other));
    ASSERT_TRUE(define_standard_weapon(game));
    ASSERT_EQ(break_game_weapon_equip(game, actor, WEAPON_ID), BREAK_GAME_OK);
    BreakGameFireIntent fire;
    ASSERT_EQ(break_game_weapon_fire(game, actor, &fire), BREAK_GAME_OK);
    ASSERT_EQ(break_game_weapon_tick(game, actor, 2u), BREAK_GAME_OK);
    ASSERT_EQ(break_game_weapon_fire(game, actor, &fire), BREAK_GAME_OK);
    ASSERT_EQ(break_game_weapon_tick(game, actor, 2u), BREAK_GAME_OK);
    ASSERT_EQ(break_game_weapon_begin_reload(game, actor), BREAK_GAME_REJECTED);
    ASSERT_EQ(break_game_inventory_add(game, actor, AMMO_ID, 2u), BREAK_GAME_OK);
    ASSERT_EQ(break_game_weapon_begin_reload(game, actor), BREAK_GAME_OK);
    ASSERT_EQ(break_game_inventory_transfer(game, actor, other, AMMO_ID, 1u), BREAK_GAME_OK);
    u32 slot = break_game_actor_slot(game, actor);
    ASSERT_NEQ(slot, UINT32_MAX);
    u32 now = game->actors[slot].now_tick;
    u32 next_fire = game->actors[slot].next_fire_tick;
    u32 reload_finish = game->actors[slot].reload_finish_tick;

    ASSERT_EQ(break_game_weapon_tick(game, actor, 3u), BREAK_GAME_OVERLOAD);
    ASSERT_EQ(game->actors[slot].now_tick, now + 3u);
    ASSERT_EQ(game->actors[slot].next_fire_tick, next_fire);
    ASSERT_EQ(game->actors[slot].reload_finish_tick, reload_finish);
    ASSERT_TRUE(game->actors[slot].reloading);
    u32 magazine = 99u;
    u32 reserve = 99u;
    ASSERT_EQ(break_game_weapon_ammo(game, actor, &magazine), BREAK_GAME_OK);
    ASSERT_EQ(magazine, 0u);
    ASSERT_EQ(break_game_inventory_count(game, actor, AMMO_ID, &reserve), BREAK_GAME_OK);
    ASSERT_EQ(reserve, 1u);
    BreakGameFireIntent before = sentinel_intent();
    fire = before;
    ASSERT_EQ(break_game_weapon_fire(game, actor, &fire), BREAK_GAME_REJECTED);
    ASSERT_TRUE(memcmp(&fire, &before, sizeof(fire)) == 0);

    ASSERT_EQ(break_game_inventory_add(game, actor, AMMO_ID, 1u), BREAK_GAME_OK);
    ASSERT_EQ(break_game_weapon_tick(game, actor, 1u), BREAK_GAME_OK);
    ASSERT_EQ(break_game_weapon_ammo(game, actor, &magazine), BREAK_GAME_OK);
    ASSERT_EQ(magazine, 2u);
    ASSERT_EQ(break_game_inventory_count(game, actor, AMMO_ID, &reserve), BREAK_GAME_OK);
    ASSERT_EQ(reserve, 0u);
    destroy_game(game, world);
}

TEST(unequip_returns_magazine_atomically_and_rolls_back_capacity_failure) {
    World *world = make_world();
    BreakGame *game = make_game(world, 2);
    ASSERT_NOT_NULL(game);
    Entity actor = spawn_pawn(game);
    Entity other = spawn_pawn(game);
    ASSERT_TRUE(entity_valid(actor));
    ASSERT_TRUE(entity_valid(other));
    ASSERT_TRUE(define_standard_weapon(game));
    ASSERT_EQ(break_game_weapon_equip(game, actor, WEAPON_ID), BREAK_GAME_OK);
    ASSERT_EQ(break_game_inventory_add(game, actor, AMMO_ID, 29u), BREAK_GAME_OK);
    u32 slot = break_game_actor_slot(game, actor);
    ASSERT_NEQ(slot, UINT32_MAX);
    u32 now = game->actors[slot].now_tick;
    u32 next_fire = game->actors[slot].next_fire_tick;
    u32 reload_finish = game->actors[slot].reload_finish_tick;
    bool reloading = game->actors[slot].reloading;

    ASSERT_EQ(break_game_weapon_unequip(game, actor), BREAK_GAME_OVERLOAD);
    ASSERT_EQ(game->actors[slot].weapon_id, WEAPON_ID);
    ASSERT_EQ(game->actors[slot].now_tick, now);
    ASSERT_EQ(game->actors[slot].next_fire_tick, next_fire);
    ASSERT_EQ(game->actors[slot].reload_finish_tick, reload_finish);
    ASSERT_EQ(game->actors[slot].reloading, reloading);
    u32 magazine = 0;
    ASSERT_EQ(break_game_weapon_ammo(game, actor, &magazine), BREAK_GAME_OK);
    ASSERT_EQ(magazine, 2u);
    u32 reserve = 0;
    ASSERT_EQ(break_game_inventory_count(game, actor, AMMO_ID, &reserve), BREAK_GAME_OK);
    ASSERT_EQ(reserve, 29u);
    ASSERT_EQ(break_game_inventory_transfer(game, actor, other, AMMO_ID, 29u), BREAK_GAME_OK);
    ASSERT_EQ(break_game_weapon_unequip(game, actor), BREAK_GAME_OK);
    ASSERT_EQ(break_game_inventory_count(game, actor, AMMO_ID, &reserve), BREAK_GAME_OK);
    ASSERT_EQ(reserve, 2u);
    magazine = 99u;
    ASSERT_EQ(break_game_weapon_ammo(game, actor, &magazine), BREAK_GAME_REJECTED);
    ASSERT_EQ(magazine, 99u);
    ASSERT_EQ(break_game_weapon_unequip(game, actor), BREAK_GAME_REJECTED);
    ASSERT_EQ(break_game_inventory_count(game, actor, AMMO_ID, &reserve), BREAK_GAME_OK);
    ASSERT_EQ(reserve, 2u);
    destroy_game(game, world);
}

TEST(definition_and_equipment_validate_descriptors_and_state) {
    World *world = make_world();
    BreakGame *game = make_game(world, 1);
    ASSERT_NOT_NULL(game);
    Entity actor = spawn_pawn(game);
    ASSERT_TRUE(entity_valid(actor));
    BreakGameWeaponDesc desc = {WEAPON_ID, AMMO_ID, 7u, 2u, 2u, 3u};
    ASSERT_EQ(break_game_weapon_define(game, &desc), BREAK_GAME_STALE);
    BreakGameItemDesc ammo = {AMMO_ID, 30u};
    ASSERT_EQ(break_game_item_define(game, &ammo), BREAK_GAME_OK);
    ASSERT_EQ(break_game_weapon_define(game, NULL), BREAK_GAME_INVALID);
    ASSERT_EQ(break_game_weapon_define(NULL, &desc), BREAK_GAME_INVALID);
    ASSERT_EQ(break_game_weapon_define(game, &desc), BREAK_GAME_OK);
    ASSERT_EQ(break_game_weapon_define(game, &desc), BREAK_GAME_REJECTED);

    desc.weapon_id = 0;
    ASSERT_EQ(break_game_weapon_define(game, &desc), BREAK_GAME_INVALID);
    desc.weapon_id = 65;
    ASSERT_EQ(break_game_weapon_define(game, &desc), BREAK_GAME_INVALID);
    desc.weapon_id = 2;
    desc.ammo_item_id = 0;
    ASSERT_EQ(break_game_weapon_define(game, &desc), BREAK_GAME_INVALID);
    desc.ammo_item_id = 65;
    ASSERT_EQ(break_game_weapon_define(game, &desc), BREAK_GAME_INVALID);
    desc.ammo_item_id = 2;
    ASSERT_EQ(break_game_weapon_define(game, &desc), BREAK_GAME_STALE);
    desc.ammo_item_id = AMMO_ID;
    desc.damage = 0;
    ASSERT_EQ(break_game_weapon_define(game, &desc), BREAK_GAME_INVALID);
    desc.damage = 10001u;
    ASSERT_EQ(break_game_weapon_define(game, &desc), BREAK_GAME_INVALID);
    desc.damage = 7;
    desc.magazine_capacity = 0;
    ASSERT_EQ(break_game_weapon_define(game, &desc), BREAK_GAME_INVALID);
    desc.magazine_capacity = 1001u;
    ASSERT_EQ(break_game_weapon_define(game, &desc), BREAK_GAME_INVALID);
    desc.magazine_capacity = 2;
    desc.reload_ticks = 0;
    ASSERT_EQ(break_game_weapon_define(game, &desc), BREAK_GAME_INVALID);
    desc.reload_ticks = 3;
    desc.weapon_id = 64;
    desc.damage = 10000u;
    desc.magazine_capacity = 1000u;
    desc.fire_interval_ticks = UINT32_MAX;
    desc.reload_ticks = 1;
    ASSERT_EQ(break_game_weapon_define(game, &desc), BREAK_GAME_OK);

    ASSERT_EQ(break_game_weapon_equip(game, actor, 0), BREAK_GAME_INVALID);
    ASSERT_EQ(break_game_weapon_equip(game, actor, 2), BREAK_GAME_STALE);
    ASSERT_EQ(break_game_weapon_equip(game, actor, WEAPON_ID), BREAK_GAME_OK);
    ASSERT_EQ(break_game_weapon_equip(game, actor, WEAPON_ID), BREAK_GAME_REJECTED);
    ASSERT_EQ(break_game_weapon_begin_reload(game, actor), BREAK_GAME_REJECTED);
    u32 magazine = 0;
    ASSERT_EQ(break_game_weapon_ammo(game, actor, &magazine), BREAK_GAME_OK);
    ASSERT_EQ(magazine, 2u);
    destroy_game(game, world);
}

TEST(stale_handles_and_invalid_arguments_leave_weapon_state_unchanged) {
    World *world = make_world();
    BreakGame *game = make_game(world, 1);
    ASSERT_NOT_NULL(game);
    Entity actor = spawn_pawn(game);
    ASSERT_TRUE(entity_valid(actor));
    ASSERT_TRUE(define_standard_weapon(game));
    ASSERT_EQ(break_game_weapon_equip(game, actor, WEAPON_ID), BREAK_GAME_OK);
    Entity stale = actor;
    stale.generation++;
    BreakGameFireIntent fire = sentinel_intent();
    BreakGameFireIntent before = fire;
    u32 magazine = 99u;

    ASSERT_EQ(break_game_weapon_equip(game, stale, WEAPON_ID), BREAK_GAME_STALE);
    ASSERT_EQ(break_game_weapon_unequip(game, stale), BREAK_GAME_STALE);
    ASSERT_EQ(break_game_weapon_begin_reload(game, stale), BREAK_GAME_STALE);
    ASSERT_EQ(break_game_weapon_tick(game, stale, 1u), BREAK_GAME_STALE);
    ASSERT_EQ(break_game_weapon_fire(game, stale, &fire), BREAK_GAME_STALE);
    ASSERT_TRUE(memcmp(&fire, &before, sizeof(fire)) == 0);
    ASSERT_EQ(break_game_weapon_ammo(game, stale, &magazine), BREAK_GAME_STALE);
    ASSERT_EQ(magazine, 99u);
    ASSERT_EQ(break_game_weapon_fire(game, actor, NULL), BREAK_GAME_INVALID);
    ASSERT_EQ(break_game_weapon_ammo(game, actor, NULL), BREAK_GAME_INVALID);
    ASSERT_EQ(break_game_weapon_tick(NULL, actor, 1u), BREAK_GAME_INVALID);
    ASSERT_EQ(break_game_weapon_fire(NULL, actor, &fire), BREAK_GAME_INVALID);
    ASSERT_EQ(break_game_weapon_ammo(NULL, actor, &magazine), BREAK_GAME_INVALID);

    u32 slot = break_game_actor_slot(game, actor);
    ASSERT_NEQ(slot, UINT32_MAX);
    u32 now = game->actors[slot].now_tick;
    ASSERT_EQ(break_game_weapon_tick(game, actor, 0), BREAK_GAME_INVALID);
    ASSERT_EQ(game->actors[slot].now_tick, now);
    ASSERT_EQ(break_game_weapon_fire(game, actor, &fire), BREAK_GAME_OK);
    ASSERT_EQ(fire.sequence, 1u);
    ASSERT_EQ(break_game_weapon_ammo(game, actor, &magazine), BREAK_GAME_OK);
    ASSERT_EQ(magazine, 1u);
    destroy_game(game, world);
}

typedef struct {
    BreakGame *game;
    Entity actor;
    BreakGameWeaponDesc desc;
    BreakGameError errors[7];
    BreakGameFireIntent fire;
    u32 magazine;
} ThreadProbe;

static PLATFORM_THREAD_RET weapon_calls_off_thread(PLATFORM_THREAD_ARG arg) {
    ThreadProbe *probe = (ThreadProbe *)arg;
    probe->errors[0] = break_game_weapon_define(probe->game, &probe->desc);
    probe->errors[1] = break_game_weapon_equip(probe->game, probe->actor, WEAPON_ID);
    probe->errors[2] = break_game_weapon_unequip(probe->game, probe->actor);
    probe->errors[3] = break_game_weapon_begin_reload(probe->game, probe->actor);
    probe->errors[4] = break_game_weapon_tick(probe->game, probe->actor, 1u);
    probe->errors[5] = break_game_weapon_fire(probe->game, probe->actor, &probe->fire);
    probe->errors[6] = break_game_weapon_ammo(probe->game, probe->actor, &probe->magazine);
    return PLATFORM_THREAD_RETURN;
}

TEST(all_public_calls_reject_non_owner_without_mutating_state) {
    World *world = make_world();
    BreakGame *game = make_game(world, 1);
    ASSERT_NOT_NULL(game);
    Entity actor = spawn_pawn(game);
    ASSERT_TRUE(entity_valid(actor));
    ASSERT_TRUE(define_standard_weapon(game));
    ASSERT_EQ(break_game_weapon_equip(game, actor, WEAPON_ID), BREAK_GAME_OK);
    ThreadProbe probe;
    probe.game = game;
    probe.actor = actor;
    probe.desc.weapon_id = 2;
    probe.desc.ammo_item_id = AMMO_ID;
    probe.desc.damage = 9;
    probe.desc.magazine_capacity = 3;
    probe.desc.fire_interval_ticks = 1;
    probe.desc.reload_ticks = 1;
    probe.fire = sentinel_intent();
    BreakGameFireIntent before = probe.fire;
    probe.magazine = 99u;
    PlatformThread thread;
    ASSERT_TRUE(platform_thread_create(&thread, weapon_calls_off_thread, &probe));
    platform_thread_join(thread);
    for (u32 i = 0; i < 7; i++) {
        ASSERT_EQ(probe.errors[i], BREAK_GAME_REJECTED);
    }
    ASSERT_TRUE(memcmp(&probe.fire, &before, sizeof(probe.fire)) == 0);
    ASSERT_EQ(probe.magazine, 99u);
    ASSERT_EQ(break_game_weapon_define(game, &probe.desc), BREAK_GAME_OK);
    u32 magazine = 0;
    ASSERT_EQ(break_game_weapon_ammo(game, actor, &magazine), BREAK_GAME_OK);
    ASSERT_EQ(magazine, 2u);
    BreakGameFireIntent fire;
    ASSERT_EQ(break_game_weapon_fire(game, actor, &fire), BREAK_GAME_OK);
    ASSERT_EQ(fire.sequence, 1u);
    destroy_game(game, world);
}

TEST(tick_cooldown_reload_and_sequence_overflow_are_atomic) {
    World *world = make_world();
    BreakGame *game = make_game(world, 1);
    ASSERT_NOT_NULL(game);
    Entity actor = spawn_pawn(game);
    ASSERT_TRUE(entity_valid(actor));
    ASSERT_TRUE(define_standard_weapon(game));
    ASSERT_EQ(break_game_weapon_equip(game, actor, WEAPON_ID), BREAK_GAME_OK);
    u32 slot = break_game_actor_slot(game, actor);
    ASSERT_NEQ(slot, UINT32_MAX);
    BreakGameActor *state = &game->actors[slot];
    BreakGameFireIntent fire = sentinel_intent();
    BreakGameFireIntent before = fire;

    state->now_tick = UINT32_MAX;
    state->next_fire_tick = UINT32_MAX;
    ASSERT_EQ(break_game_weapon_fire(game, actor, &fire), BREAK_GAME_OVERLOAD);
    ASSERT_TRUE(memcmp(&fire, &before, sizeof(fire)) == 0);
    ASSERT_EQ(state->weapon_id, WEAPON_ID);
    ASSERT_EQ(state->now_tick, UINT32_MAX);
    ASSERT_EQ(state->next_fire_tick, UINT32_MAX);
    ASSERT_EQ(state->reload_finish_tick, 0u);
    ASSERT_FALSE(state->reloading);
    ASSERT_EQ(state->magazine, 2u);
    ASSERT_EQ(game->fire_sequence, 0u);

    state->now_tick = 0;
    state->next_fire_tick = 0;
    game->fire_sequence = UINT64_MAX;
    ASSERT_EQ(break_game_weapon_fire(game, actor, &fire), BREAK_GAME_OVERLOAD);
    ASSERT_TRUE(memcmp(&fire, &before, sizeof(fire)) == 0);
    ASSERT_EQ(state->weapon_id, WEAPON_ID);
    ASSERT_EQ(state->now_tick, 0u);
    ASSERT_EQ(state->next_fire_tick, 0u);
    ASSERT_EQ(state->reload_finish_tick, 0u);
    ASSERT_FALSE(state->reloading);
    ASSERT_EQ(state->magazine, 2u);
    ASSERT_EQ(game->fire_sequence, UINT64_MAX);

    game->fire_sequence = 0;
    state->now_tick = UINT32_MAX;
    ASSERT_EQ(break_game_weapon_tick(game, actor, 1u), BREAK_GAME_OVERLOAD);
    ASSERT_EQ(state->weapon_id, WEAPON_ID);
    ASSERT_EQ(state->now_tick, UINT32_MAX);
    ASSERT_EQ(state->next_fire_tick, 0u);
    ASSERT_EQ(state->reload_finish_tick, 0u);
    ASSERT_FALSE(state->reloading);
    ASSERT_EQ(state->magazine, 2u);
    ASSERT_EQ(game->fire_sequence, 0u);
    state->now_tick = 0;
    ASSERT_EQ(break_game_weapon_fire(game, actor, &fire), BREAK_GAME_OK);
    ASSERT_EQ(fire.sequence, 1u);
    ASSERT_EQ(break_game_inventory_add(game, actor, AMMO_ID, 5u), BREAK_GAME_OK);
    state->now_tick = UINT32_MAX - 1u;
    state->next_fire_tick = 0;
    ASSERT_EQ(break_game_weapon_begin_reload(game, actor), BREAK_GAME_OVERLOAD);
    ASSERT_EQ(state->weapon_id, WEAPON_ID);
    ASSERT_EQ(state->now_tick, UINT32_MAX - 1u);
    ASSERT_EQ(state->next_fire_tick, 0u);
    ASSERT_EQ(state->reload_finish_tick, 0u);
    ASSERT_FALSE(state->reloading);
    ASSERT_EQ(state->magazine, 1u);
    ASSERT_EQ(game->fire_sequence, 1u);
    u32 reserve = 0;
    ASSERT_EQ(break_game_inventory_count(game, actor, AMMO_ID, &reserve), BREAK_GAME_OK);
    ASSERT_EQ(reserve, 5u);
    destroy_game(game, world);
}

TEST(failed_reload_at_max_tick_can_retry_without_advancing_time) {
    World *world = make_world();
    BreakGame *game = make_game(world, 2);
    ASSERT_NOT_NULL(game);
    Entity actor = spawn_pawn(game);
    Entity other = spawn_pawn(game);
    ASSERT_TRUE(entity_valid(actor));
    ASSERT_TRUE(entity_valid(other));
    ASSERT_TRUE(define_standard_weapon(game));
    ASSERT_EQ(break_game_weapon_equip(game, actor, WEAPON_ID), BREAK_GAME_OK);
    BreakGameFireIntent fire;
    ASSERT_EQ(break_game_weapon_fire(game, actor, &fire), BREAK_GAME_OK);
    ASSERT_EQ(break_game_inventory_add(game, actor, AMMO_ID, 1u), BREAK_GAME_OK);
    u32 slot = break_game_actor_slot(game, actor);
    ASSERT_NEQ(slot, UINT32_MAX);
    BreakGameActor *state = &game->actors[slot];
    state->now_tick = UINT32_MAX - 3u;
    state->next_fire_tick = 0;
    ASSERT_EQ(break_game_weapon_begin_reload(game, actor), BREAK_GAME_OK);
    ASSERT_EQ(state->reload_finish_tick, UINT32_MAX);
    ASSERT_EQ(break_game_inventory_transfer(game, actor, other, AMMO_ID, 1u), BREAK_GAME_OK);
    ASSERT_EQ(break_game_weapon_tick(game, actor, 3u), BREAK_GAME_OVERLOAD);
    ASSERT_EQ(state->weapon_id, WEAPON_ID);
    ASSERT_EQ(state->now_tick, UINT32_MAX);
    ASSERT_TRUE(state->reloading);
    ASSERT_EQ(break_game_inventory_add(game, actor, AMMO_ID, 1u), BREAK_GAME_OK);
    ASSERT_EQ(break_game_weapon_tick(game, actor, 1u), BREAK_GAME_OVERLOAD);
    ASSERT_EQ(state->weapon_id, WEAPON_ID);
    ASSERT_EQ(state->now_tick, UINT32_MAX);
    ASSERT_TRUE(state->reloading);
    u32 reserve = 0;
    ASSERT_EQ(break_game_inventory_count(game, actor, AMMO_ID, &reserve), BREAK_GAME_OK);
    ASSERT_EQ(reserve, 1u);

    ASSERT_EQ(break_game_weapon_begin_reload(game, actor), BREAK_GAME_OK);
    ASSERT_EQ(state->weapon_id, WEAPON_ID);
    ASSERT_EQ(state->now_tick, UINT32_MAX);
    ASSERT_FALSE(state->reloading);
    ASSERT_EQ(state->reload_finish_tick, 0u);
    ASSERT_EQ(state->magazine, 2u);
    ASSERT_EQ(break_game_inventory_count(game, actor, AMMO_ID, &reserve), BREAK_GAME_OK);
    ASSERT_EQ(reserve, 0u);
    destroy_game(game, world);
}

TEST(despawn_clears_weapon_state_and_generation_reuse_starts_clean) {
    World *world = make_world();
    BreakGame *game = make_game(world, 1);
    ASSERT_NOT_NULL(game);
    Entity old = spawn_pawn(game);
    ASSERT_TRUE(entity_valid(old));
    ASSERT_TRUE(define_standard_weapon(game));
    ASSERT_EQ(break_game_weapon_equip(game, old, WEAPON_ID), BREAK_GAME_OK);
    BreakGameFireIntent fire;
    ASSERT_EQ(break_game_weapon_fire(game, old, &fire), BREAK_GAME_OK);
    ASSERT_EQ(fire.sequence, 1u);
    ASSERT_EQ(break_game_inventory_add(game, old, AMMO_ID, 5u), BREAK_GAME_OK);
    ASSERT_EQ(break_game_weapon_begin_reload(game, old), BREAK_GAME_OK);
    ASSERT_EQ(break_game_despawn(game, old), BREAK_GAME_OK);
    ASSERT_EQ(break_game_weapon_fire(game, old, &fire), BREAK_GAME_STALE);

    Entity replacement = spawn_pawn(game);
    ASSERT_TRUE(entity_valid(replacement));
    ASSERT_EQ(replacement.index, old.index);
    ASSERT_NEQ(replacement.generation, old.generation);
    u32 magazine = 99u;
    ASSERT_EQ(break_game_weapon_ammo(game, replacement, &magazine), BREAK_GAME_REJECTED);
    ASSERT_EQ(magazine, 99u);
    u32 reserve = 99u;
    ASSERT_EQ(break_game_inventory_count(game, replacement, AMMO_ID, &reserve), BREAK_GAME_OK);
    ASSERT_EQ(reserve, 0u);
    ASSERT_EQ(break_game_weapon_equip(game, replacement, WEAPON_ID), BREAK_GAME_OK);
    ASSERT_EQ(break_game_weapon_ammo(game, replacement, &magazine), BREAK_GAME_OK);
    ASSERT_EQ(magazine, 2u);
    ASSERT_EQ(break_game_weapon_fire(game, replacement, &fire), BREAK_GAME_OK);
    ASSERT_EQ(fire.sequence, 2u);
    ASSERT_EQ(fire.shooter.generation, replacement.generation);
    destroy_game(game, world);
}

TEST_MAIN_BEGIN()
    RUN_TEST(fire_cooldown_reload_and_intent_follow_authoritative_state);
    RUN_TEST(reload_without_reserve_rejects_and_failed_deduction_can_retry);
    RUN_TEST(unequip_returns_magazine_atomically_and_rolls_back_capacity_failure);
    RUN_TEST(definition_and_equipment_validate_descriptors_and_state);
    RUN_TEST(stale_handles_and_invalid_arguments_leave_weapon_state_unchanged);
    RUN_TEST(all_public_calls_reject_non_owner_without_mutating_state);
    RUN_TEST(tick_cooldown_reload_and_sequence_overflow_are_atomic);
    RUN_TEST(failed_reload_at_max_tick_can_retry_without_advancing_time);
    RUN_TEST(despawn_clears_weapon_state_and_generation_reuse_starts_clean);
TEST_MAIN_END()
