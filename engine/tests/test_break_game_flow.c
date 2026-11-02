#include "test_framework.h"
#include <core/platform_thread.h>
#include <game/break_game.h>
#include <math.h>
#include <string.h>

static World *make_world(void) {
    World *world = world_create();
    world_register_component(world, BREAK_GAME_POSITION_COMPONENT, sizeof(Vec3));
    return world;
}

static BreakGame *make_game(World *world, Entity *out_actor) {
    BreakGameConfig cfg = {0u, 2u};
    BreakGame *game = break_game_create(world, &cfg);
    if (!game) return NULL;
    ComponentType comps[1] = {BREAK_GAME_POSITION_COMPONENT};
    BreakGameClassDesc desc = {"pawn", comps, 1u, NULL};
    u32 class_id = 0u;
    BreakGameSpawn spawn;
    if (break_game_register_class(game, &desc, &class_id) != BREAK_GAME_OK) {
        break_game_destroy(game);
        return NULL;
    }
    spawn.class_id = class_id;
    spawn.position = vec3(1.0f, 2.0f, 3.0f);
    if (break_game_spawn(game, &spawn, out_actor) != BREAK_GAME_OK) {
        break_game_destroy(game);
        return NULL;
    }
    BreakGameItemDesc item = {3u, 10u};
    if (break_game_item_define(game, &item) != BREAK_GAME_OK) {
        break_game_destroy(game);
        return NULL;
    }
    return game;
}

static BreakGameEntityAction position_action(Entity actor, f32 x, f32 y, f32 z) {
    BreakGameEntityAction action;
    memset(&action, 0, sizeof(action));
    action.type = BREAK_GAME_ENTITY_SET_POSITION;
    action.entity = actor;
    action.position = vec3(x, y, z);
    return action;
}

static BreakGameEntityAction item_action(Entity actor, u32 count) {
    BreakGameEntityAction action;
    memset(&action, 0, sizeof(action));
    action.type = BREAK_GAME_ENTITY_INVENTORY_ADD;
    action.entity = actor;
    action.item_id = 3u;
    action.count = count;
    return action;
}

TEST(late_inventory_failure_does_not_apply_earlier_position) {
    World *world = make_world();
    Entity actor = ENTITY_NULL;
    BreakGame *game = make_game(world, &actor);
    ASSERT_NOT_NULL(game);
    BreakGameEntityAction actions[2] = {
        position_action(actor, 8.0f, 9.0f, 10.0f), item_action(actor, 11u)};
    ASSERT_EQ(break_game_entity_actions_apply(game, actions, 2u),
              BREAK_GAME_OVERLOAD);
    Vec3 *pos = (Vec3 *)world_get_component(world, actor, BREAK_GAME_POSITION_COMPONENT);
    ASSERT_NOT_NULL(pos);
    ASSERT_FLOAT_EQ(pos->e[0], 1.0f, 0.0f);
    ASSERT_FLOAT_EQ(pos->e[1], 2.0f, 0.0f);
    ASSERT_FLOAT_EQ(pos->e[2], 3.0f, 0.0f);
    u32 count = 99u;
    ASSERT_EQ(break_game_inventory_count(game, actor, 3u, &count), BREAK_GAME_OK);
    ASSERT_EQ(count, 0u);
    break_game_destroy(game);
    world_destroy(world);
}

TEST(valid_batch_commits_position_and_inventory_together) {
    World *world = make_world();
    Entity actor = ENTITY_NULL;
    BreakGame *game = make_game(world, &actor);
    ASSERT_NOT_NULL(game);
    BreakGameEntityAction actions[2] = {
        position_action(actor, 8.0f, 9.0f, 10.0f), item_action(actor, 10u)};
    ASSERT_EQ(break_game_entity_actions_apply(game, actions, 2u), BREAK_GAME_OK);
    Vec3 *pos = (Vec3 *)world_get_component(world, actor, BREAK_GAME_POSITION_COMPONENT);
    ASSERT_FLOAT_EQ(pos->e[0], 8.0f, 0.0f);
    ASSERT_FLOAT_EQ(pos->e[1], 9.0f, 0.0f);
    ASSERT_FLOAT_EQ(pos->e[2], 10.0f, 0.0f);
    u32 count = 0u;
    ASSERT_EQ(break_game_inventory_count(game, actor, 3u, &count), BREAK_GAME_OK);
    ASSERT_EQ(count, 10u);
    break_game_destroy(game);
    world_destroy(world);
}

TEST(aggregate_additions_and_invalid_handles_are_preflighted) {
    World *world = make_world();
    Entity actor = ENTITY_NULL;
    BreakGame *game = make_game(world, &actor);
    ASSERT_NOT_NULL(game);
    BreakGameEntityAction actions[2] = {item_action(actor, 6u), item_action(actor, 5u)};
    ASSERT_EQ(break_game_entity_actions_apply(game, actions, 2u), BREAK_GAME_OVERLOAD);
    u32 count = 99u;
    ASSERT_EQ(break_game_inventory_count(game, actor, 3u, &count), BREAK_GAME_OK);
    ASSERT_EQ(count, 0u);
    Entity stale = actor;
    stale.generation++;
    actions[0] = position_action(actor, 7.0f, 7.0f, 7.0f);
    actions[1] = item_action(stale, 1u);
    ASSERT_EQ(break_game_entity_actions_apply(game, actions, 2u), BREAK_GAME_STALE);
    Vec3 *pos = (Vec3 *)world_get_component(world, actor, BREAK_GAME_POSITION_COMPONENT);
    ASSERT_FLOAT_EQ(pos->e[0], 1.0f, 0.0f);
    actions[1] = item_action(actor, 1u);
    actions[1].item_id = 4u;
    ASSERT_EQ(break_game_entity_actions_apply(game, actions, 2u), BREAK_GAME_STALE);
    actions[1] = position_action(actor, NAN, 0.0f, 0.0f);
    ASSERT_EQ(break_game_entity_actions_apply(game, actions, 2u), BREAK_GAME_INVALID);
    ASSERT_FLOAT_EQ(pos->e[0], 1.0f, 0.0f);
    break_game_destroy(game);
    world_destroy(world);
}

typedef struct {
    BreakGame *game;
    BreakGameEntityAction action;
    BreakGameError result;
} ThreadProbe;

static PLATFORM_THREAD_RET apply_off_thread(PLATFORM_THREAD_ARG arg) {
    ThreadProbe *probe = (ThreadProbe *)arg;
    probe->result = break_game_entity_actions_apply(probe->game, &probe->action, 1u);
    return PLATFORM_THREAD_RETURN;
}

TEST(non_game_thread_is_rejected_without_mutation) {
    World *world = make_world();
    Entity actor = ENTITY_NULL;
    BreakGame *game = make_game(world, &actor);
    ASSERT_NOT_NULL(game);
    ThreadProbe probe;
    probe.game = game;
    probe.action = position_action(actor, 6.0f, 6.0f, 6.0f);
    probe.result = BREAK_GAME_OK;
    PlatformThread thread;
    ASSERT_TRUE(platform_thread_create(&thread, apply_off_thread, &probe));
    platform_thread_join(thread);
    ASSERT_EQ(probe.result, BREAK_GAME_REJECTED);
    Vec3 *pos = (Vec3 *)world_get_component(world, actor, BREAK_GAME_POSITION_COMPONENT);
    ASSERT_FLOAT_EQ(pos->e[0], 1.0f, 0.0f);
    break_game_destroy(game);
    world_destroy(world);
}

TEST_MAIN_BEGIN()
    RUN_TEST(late_inventory_failure_does_not_apply_earlier_position);
    RUN_TEST(valid_batch_commits_position_and_inventory_together);
    RUN_TEST(aggregate_additions_and_invalid_handles_are_preflighted);
    RUN_TEST(non_game_thread_is_rejected_without_mutation);
TEST_MAIN_END()
