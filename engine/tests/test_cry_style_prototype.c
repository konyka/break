#include "test_framework.h"
#include <game/break_game.h>
#include <ai/break_ai.h>
#include <animation/animation.h>
#include <physics/character.h>
#include <stdlib.h>

static bool ray_yes(void *user, Vec3 from, Vec3 to) {
    (void)user;
    (void)from;
    (void)to;
    return true;
}

static int g_enters;
static int g_leaves;

static void on_area(u32 area_id, Entity entity, BreakGameAreaEvent event, void *user) {
    (void)area_id;
    (void)entity;
    (void)user;
    if (event == BREAK_GAME_AREA_ENTER) g_enters++;
    if (event == BREAK_GAME_AREA_LEAVE) g_leaves++;
}

TEST(prototype_player_moves_on_a_floor) {
    PhysicsWorld *pw = physics_world_create(8);
    physics_body_create(pw, vec3(0, 0, 0), vec3(40, 0.5f, 40), 0, true, 0);
    World *world = world_create();
    world_register_component(world, BREAK_GAME_POSITION_COMPONENT, sizeof(Vec3));
    BreakGame *game = break_game_create(world, NULL);
    ComponentType comps[1] = {BREAK_GAME_POSITION_COMPONENT};
    BreakGameClassDesc desc;
    desc.name = "player";
    desc.components = comps;
    desc.component_count = 1;
    desc.lua_module = NULL;
    u32 class_id = 0;
    ASSERT_EQ(break_game_register_class(game, &desc, &class_id), BREAK_GAME_OK);
    BreakGameSpawn spawn;
    spawn.class_id = class_id;
    spawn.position = vec3(0, 1, 0);
    Entity player = ENTITY_NULL;
    ASSERT_EQ(break_game_spawn(game, &spawn, &player), BREAK_GAME_OK);
    CharacterController cc = character_create(vec3(0, 1, 0), 0.3f, 1.8f);
    BreakGameMoveInput in;
    in.forward = 1;
    in.strafe = 0;
    in.camera_yaw = 0;
    in.jump = false;
    for (int i = 0; i < 180; i++) {
        BreakGameMoveOutput wish;
        ASSERT_EQ(break_game_move_wish(&in, &wish), BREAK_GAME_OK);
        character_update(&cc, pw, 1.0f / 60.0f, wish.wish, false);
    }
    ASSERT_TRUE(cc.position.e[2] - 0.0f > 2.0f);
    Vec3 *pos = (Vec3 *)world_get_component(world, player, BREAK_GAME_POSITION_COMPONENT);
    ASSERT_NOT_NULL(pos);
    *pos = cc.position;
    break_game_destroy(game);
    world_destroy(world);
    physics_world_destroy(pw);
}

TEST(prototype_enemy_paths_around_a_wall) {
    enum { N = 32 };
    f32 *heights = (f32 *)calloc(N * N, sizeof(f32));
    ASSERT_NOT_NULL(heights);
    for (u32 z = 0; z < 24; z++) heights[z * N + 16] = 12.0f;
    BreakNavHeightfield field;
    memset(&field, 0, sizeof(field));
    field.heights = heights;
    field.width = N;
    field.depth = N;
    field.cell = 1;
    field.height_scale = 1;
    BreakNavMesh *mesh = break_nav_bake_heightfield(&field, 40.0f, 0.0f);
    ASSERT_NOT_NULL(mesh);
    Vec3 start = vec3(4.5f, 0, 8.0f);
    Vec3 end = vec3(26.5f, 0, 8.0f);
    BreakNavPath path;
    ASSERT_EQ(break_nav_find_path(mesh, start, end, &path), BREAK_NAV_OK);
    f32 length = 0;
    for (u32 i = 1; i < path.count; i++) {
        f32 dx = path.points[i].e[0] - path.points[i - 1].e[0];
        f32 dz = path.points[i].e[2] - path.points[i - 1].e[2];
        length += sqrtf(dx * dx + dz * dz);
    }
    ASSERT_TRUE(length > 22.0f);

    BreakSight sight;
    sight.eye = start;
    sight.forward = vec3(1, 0, 0);
    sight.distance = 40;
    sight.half_angle_rad = 0.6f;
    BreakSightTarget target;
    target.entity = (Entity){2, 1};
    target.point = end;
    Entity visible[2];
    u32 seen = 0;
    ASSERT_EQ(break_sight_query(&sight, &target, 1, ray_yes, NULL, visible, 2, &seen), BREAK_NAV_OK);
    ASSERT_EQ(seen, 1u);

    BreakNode nodes[5];
    memset(nodes, 0, sizeof(nodes));
    nodes[0].kind = BREAK_NODE_SELECTOR;
    nodes[0].child_begin = 1;
    nodes[0].child_count = 3;
    nodes[1].kind = BREAK_NODE_LEAF;
    nodes[1].leaf = BREAK_LEAF_ATTACK;
    nodes[2].kind = BREAK_NODE_SEQUENCE;
    nodes[2].child_begin = 4;
    nodes[2].child_count = 1;
    nodes[3].kind = BREAK_NODE_LEAF;
    nodes[3].leaf = BREAK_LEAF_IDLE;
    nodes[4].kind = BREAK_NODE_LEAF;
    nodes[4].leaf = BREAK_LEAF_CHASE;
    BreakBlackboard board;
    memset(&board, 0, sizeof(board));
    board.seen = true;
    board.last_seen = end;
    board.target = target.entity;
    BreakNavFollower follower;
    break_nav_follow_reset(&follower, &path, 0.3f);
    BreakBehaveResult result;
    ASSERT_EQ(break_behavior_tick(nodes, 5, 0, &board, &follower, start, 1.0f, &result), BREAK_BEHAVE_RUNNING);
    ASSERT_TRUE(fabsf(result.wish.e[0]) + fabsf(result.wish.e[2]) > 0.1f);
    break_nav_mesh_destroy(mesh);
    free(heights);
}

TEST(prototype_locomotion_and_trigger) {
    AnimLocoSample samples[2] = {{0.0f, 1}, {4.0f, 2}};
    AnimLoco1D loco;
    ASSERT_TRUE(anim_loco1d_init(&loco, 0, samples, 2));
    AnimBlendState state;
    anim_blend_state_init(&state, 4);
    anim_loco1d_apply(&loco, &state, 0.0f);
    f32 walk = state.layers[0].clip_index == 1 ? state.layers[0].weight : state.layers[1].weight;
    f32 run = state.layers[0].clip_index == 2 ? state.layers[0].weight : state.layers[1].weight;
    ASSERT_TRUE(walk > run);
    anim_loco1d_apply(&loco, &state, 4.0f);
    walk = state.layers[0].clip_index == 1 ? state.layers[0].weight : state.layers[1].weight;
    run = state.layers[0].clip_index == 2 ? state.layers[0].weight : state.layers[1].weight;
    ASSERT_TRUE(run > walk);
    anim_blend_state_destroy(&state);

    World *world = world_create();
    world_register_component(world, BREAK_GAME_POSITION_COMPONENT, sizeof(Vec3));
    BreakGame *game = break_game_create(world, NULL);
    ComponentType comps[1] = {BREAK_GAME_POSITION_COMPONENT};
    BreakGameClassDesc desc;
    desc.name = "player";
    desc.components = comps;
    desc.component_count = 1;
    desc.lua_module = NULL;
    u32 class_id = 0;
    ASSERT_EQ(break_game_register_class(game, &desc, &class_id), BREAK_GAME_OK);
    BreakGameSpawn spawn;
    spawn.class_id = class_id;
    spawn.position = vec3(10, 0, 0);
    Entity player = ENTITY_NULL;
    ASSERT_EQ(break_game_spawn(game, &spawn, &player), BREAK_GAME_OK);
    BreakGameAreaDesc area;
    area.center = vec3(0, 0, 0);
    area.half_extent = vec3(1, 1, 1);
    area.radius = 0;
    u32 area_id = 0;
    ASSERT_EQ(break_game_area_add(game, &area, &area_id), BREAK_GAME_OK);
    g_enters = 0;
    g_leaves = 0;
    break_game_set_area_callback(game, on_area, NULL);
    ASSERT_EQ(break_game_area_tick(game), BREAK_GAME_OK);
    ASSERT_EQ(g_enters, 0);
    Vec3 *pos = (Vec3 *)world_get_component(world, player, BREAK_GAME_POSITION_COMPONENT);
    *pos = vec3(0, 0, 0);
    ASSERT_EQ(break_game_area_tick(game), BREAK_GAME_OK);
    ASSERT_EQ(g_enters, 1);
    ASSERT_EQ(break_game_area_tick(game), BREAK_GAME_OK);
    ASSERT_EQ(g_enters, 1);
    *pos = vec3(1.4f, 0, 0);
    ASSERT_EQ(break_game_area_tick(game), BREAK_GAME_OK);
    ASSERT_EQ(g_leaves, 1);
    break_game_destroy(game);
    world_destroy(world);
}

TEST_MAIN_BEGIN()
    RUN_TEST(prototype_player_moves_on_a_floor);
    RUN_TEST(prototype_enemy_paths_around_a_wall);
    RUN_TEST(prototype_locomotion_and_trigger);
TEST_MAIN_END()
