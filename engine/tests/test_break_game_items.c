#include "test_framework.h"
#include <game/break_game.h>
#include <stdint.h>

#define AMMO_ID   1u
#define MEDKIT_ID 2u

static World *make_world(void) {
    World *world = world_create();
    world_register_component(world, BREAK_GAME_POSITION_COMPONENT, sizeof(Vec3));
    return world;
}

static BreakGame *make_game(World *world) {
    BreakGameConfig cfg;
    cfg.max_classes = 0;
    cfg.max_actors = 2;
    return break_game_create(world, &cfg);
}

static u32 register_pawn(BreakGame *game) {
    ComponentType comps[1] = {BREAK_GAME_POSITION_COMPONENT};
    BreakGameClassDesc desc;
    desc.name = "pawn";
    desc.components = comps;
    desc.component_count = 1;
    desc.lua_module = NULL;
    u32 id = 0;
    if (break_game_register_class(game, &desc, &id) != BREAK_GAME_OK) {
        return 0;
    }
    return id;
}

static Entity spawn_actor(BreakGame *game, u32 class_id) {
    BreakGameSpawn spawn;
    spawn.class_id = class_id;
    spawn.position = vec3(0, 0, 0);
    Entity entity = ENTITY_NULL;
    if (break_game_spawn(game, &spawn, &entity) != BREAK_GAME_OK) {
        return ENTITY_NULL;
    }
    return entity;
}

static bool define_standard_items(BreakGame *game) {
    BreakGameItemDesc ammo = {AMMO_ID, 30u};
    BreakGameItemDesc medkit = {MEDKIT_ID, 2u};
    return break_game_item_define(game, &ammo) == BREAK_GAME_OK &&
           break_game_item_define(game, &medkit) == BREAK_GAME_OK;
}

static void destroy_game(BreakGame *game, World *world) {
    break_game_destroy(game);
    world_destroy(world);
}

TEST(item_definition_enforces_exact_bounds) {
    World *world = make_world();
    BreakGame *game = make_game(world);
    ASSERT_NOT_NULL(game);
    BreakGameItemDesc desc = {AMMO_ID, 30u};
    ASSERT_EQ(break_game_item_define(game, &desc), BREAK_GAME_OK);
    ASSERT_EQ(break_game_item_define(game, &desc), BREAK_GAME_REJECTED);
    desc.item_id = 0;
    ASSERT_EQ(break_game_item_define(game, &desc), BREAK_GAME_INVALID);
    desc.item_id = 65;
    ASSERT_EQ(break_game_item_define(game, &desc), BREAK_GAME_INVALID);
    desc.item_id = 3;
    desc.stack_limit = 0;
    ASSERT_EQ(break_game_item_define(game, &desc), BREAK_GAME_INVALID);
    desc.stack_limit = 1000001u;
    ASSERT_EQ(break_game_item_define(game, &desc), BREAK_GAME_INVALID);
    desc.item_id = BREAK_GAME_MAX_ITEMS;
    desc.stack_limit = 1000000u;
    ASSERT_EQ(break_game_item_define(game, &desc), BREAK_GAME_OK);
    destroy_game(game, world);
}

TEST(add_validates_input_and_preserves_count_on_overload) {
    World *world = make_world();
    BreakGame *game = make_game(world);
    ASSERT_NOT_NULL(game);
    u32 class_id = register_pawn(game);
    ASSERT_NEQ(class_id, 0u);
    Entity actor = spawn_actor(game, class_id);
    ASSERT_TRUE(entity_valid(actor));
    ASSERT_TRUE(define_standard_items(game));
    ASSERT_EQ(break_game_inventory_add(game, actor, AMMO_ID, 0u), BREAK_GAME_INVALID);
    ASSERT_EQ(break_game_inventory_add(game, actor, 0u, 1u), BREAK_GAME_INVALID);
    ASSERT_EQ(break_game_inventory_add(game, actor, 65u, 1u), BREAK_GAME_INVALID);
    ASSERT_EQ(break_game_inventory_add(game, actor, 3u, 1u), BREAK_GAME_STALE);
    Entity stale = actor;
    stale.generation++;
    ASSERT_EQ(break_game_inventory_add(game, stale, AMMO_ID, 1u), BREAK_GAME_STALE);
    u32 count = 777u;
    ASSERT_EQ(break_game_inventory_count(game, stale, AMMO_ID, &count), BREAK_GAME_STALE);
    ASSERT_EQ(count, 777u);
    ASSERT_EQ(break_game_inventory_count(game, actor, 3u, &count), BREAK_GAME_STALE);
    ASSERT_EQ(count, 777u);
    ASSERT_EQ(break_game_inventory_count(game, actor, AMMO_ID, NULL), BREAK_GAME_INVALID);
    ASSERT_EQ(break_game_inventory_add(game, actor, AMMO_ID, 25u), BREAK_GAME_OK);
    ASSERT_EQ(break_game_inventory_add(game, actor, AMMO_ID, 6u), BREAK_GAME_OVERLOAD);
    ASSERT_EQ(break_game_inventory_count(game, actor, AMMO_ID, &count), BREAK_GAME_OK);
    ASSERT_EQ(count, 25u);
    ASSERT_EQ(break_game_inventory_add(game, actor, AMMO_ID, UINT32_MAX), BREAK_GAME_OVERLOAD);
    ASSERT_EQ(break_game_inventory_count(game, actor, AMMO_ID, &count), BREAK_GAME_OK);
    ASSERT_EQ(count, 25u);
    ASSERT_EQ(break_game_inventory_add(game, actor, MEDKIT_ID, 3u), BREAK_GAME_OVERLOAD);
    ASSERT_EQ(break_game_inventory_count(game, actor, MEDKIT_ID, &count), BREAK_GAME_OK);
    ASSERT_EQ(count, 0u);
    destroy_game(game, world);
}

TEST(transfer_updates_both_inventories_and_rolls_back_capacity_failure) {
    World *world = make_world();
    BreakGame *game = make_game(world);
    ASSERT_NOT_NULL(game);
    u32 class_id = register_pawn(game);
    ASSERT_NEQ(class_id, 0u);
    Entity from = spawn_actor(game, class_id);
    Entity to = spawn_actor(game, class_id);
    ASSERT_TRUE(entity_valid(from));
    ASSERT_TRUE(entity_valid(to));
    ASSERT_TRUE(define_standard_items(game));
    ASSERT_EQ(break_game_inventory_add(game, from, AMMO_ID, 25u), BREAK_GAME_OK);
    ASSERT_EQ(break_game_inventory_transfer(game, from, to, AMMO_ID, 10u), BREAK_GAME_OK);
    u32 from_count = 0;
    u32 to_count = 0;
    ASSERT_EQ(break_game_inventory_count(game, from, AMMO_ID, &from_count), BREAK_GAME_OK);
    ASSERT_EQ(from_count, 15u);
    ASSERT_EQ(break_game_inventory_count(game, to, AMMO_ID, &to_count), BREAK_GAME_OK);
    ASSERT_EQ(to_count, 10u);
    ASSERT_EQ(break_game_inventory_add(game, from, AMMO_ID, 15u), BREAK_GAME_OK);
    ASSERT_EQ(break_game_inventory_transfer(game, from, to, AMMO_ID, 21u), BREAK_GAME_OVERLOAD);
    ASSERT_EQ(break_game_inventory_count(game, from, AMMO_ID, &from_count), BREAK_GAME_OK);
    ASSERT_EQ(from_count, 30u);
    ASSERT_EQ(break_game_inventory_count(game, to, AMMO_ID, &to_count), BREAK_GAME_OK);
    ASSERT_EQ(to_count, 10u);
    destroy_game(game, world);
}

TEST(transfer_rejects_invalid_requests_and_insufficient_source_atomically) {
    World *world = make_world();
    BreakGame *game = make_game(world);
    ASSERT_NOT_NULL(game);
    u32 class_id = register_pawn(game);
    ASSERT_NEQ(class_id, 0u);
    Entity from = spawn_actor(game, class_id);
    Entity to = spawn_actor(game, class_id);
    ASSERT_TRUE(entity_valid(from));
    ASSERT_TRUE(entity_valid(to));
    ASSERT_TRUE(define_standard_items(game));
    ASSERT_EQ(break_game_inventory_add(game, from, MEDKIT_ID, 1u), BREAK_GAME_OK);
    ASSERT_EQ(break_game_inventory_transfer(game, from, from, MEDKIT_ID, 1u), BREAK_GAME_INVALID);
    ASSERT_EQ(break_game_inventory_transfer(game, from, to, MEDKIT_ID, 0u), BREAK_GAME_INVALID);
    ASSERT_EQ(break_game_inventory_transfer(game, from, to, MEDKIT_ID, 2u), BREAK_GAME_OVERLOAD);
    u32 count = 99u;
    ASSERT_EQ(break_game_inventory_count(game, from, MEDKIT_ID, &count), BREAK_GAME_OK);
    ASSERT_EQ(count, 1u);
    ASSERT_EQ(break_game_inventory_count(game, to, MEDKIT_ID, &count), BREAK_GAME_OK);
    ASSERT_EQ(count, 0u);
    destroy_game(game, world);
}

TEST(despawn_invalidates_old_handle_and_clears_reused_slot) {
    World *world = make_world();
    BreakGame *game = make_game(world);
    ASSERT_NOT_NULL(game);
    u32 class_id = register_pawn(game);
    ASSERT_NEQ(class_id, 0u);
    Entity old = spawn_actor(game, class_id);
    Entity other = spawn_actor(game, class_id);
    ASSERT_TRUE(entity_valid(old));
    ASSERT_TRUE(entity_valid(other));
    ASSERT_TRUE(define_standard_items(game));
    ASSERT_EQ(break_game_inventory_add(game, old, AMMO_ID, 25u), BREAK_GAME_OK);
    ASSERT_EQ(break_game_despawn(game, old), BREAK_GAME_OK);
    ASSERT_EQ(break_game_inventory_add(game, old, AMMO_ID, 1u), BREAK_GAME_STALE);
    u32 count = 88u;
    ASSERT_EQ(break_game_inventory_count(game, old, AMMO_ID, &count), BREAK_GAME_STALE);
    ASSERT_EQ(count, 88u);
    ASSERT_EQ(break_game_inventory_transfer(game, old, other, AMMO_ID, 1u), BREAK_GAME_STALE);
    ASSERT_EQ(break_game_inventory_transfer(game, other, old, AMMO_ID, 1u), BREAK_GAME_STALE);
    Entity replacement = spawn_actor(game, class_id);
    ASSERT_TRUE(entity_valid(replacement));
    ASSERT_EQ(break_game_inventory_count(game, replacement, AMMO_ID, &count), BREAK_GAME_OK);
    ASSERT_EQ(count, 0u);
    ASSERT_EQ(break_game_inventory_count(game, replacement, MEDKIT_ID, &count), BREAK_GAME_OK);
    ASSERT_EQ(count, 0u);
    destroy_game(game, world);
}

TEST_MAIN_BEGIN()
    RUN_TEST(item_definition_enforces_exact_bounds);
    RUN_TEST(add_validates_input_and_preserves_count_on_overload);
    RUN_TEST(transfer_updates_both_inventories_and_rolls_back_capacity_failure);
    RUN_TEST(transfer_rejects_invalid_requests_and_insufficient_source_atomically);
    RUN_TEST(despawn_invalidates_old_handle_and_clears_reused_slot);
TEST_MAIN_END()
