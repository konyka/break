#include "test_framework.h"
#include <game/break_game.h>

typedef struct {
    int enters;
    int leaves;
    Entity last;
    BreakGameAreaEvent last_event;
} AreaProbe;

static void on_area(u32 area_id, Entity entity, BreakGameAreaEvent event, void *user) {
    AreaProbe *probe = (AreaProbe *)user;
    ASSERT_EQ(area_id, 0u);
    probe->last = entity;
    probe->last_event = event;
    if (event == BREAK_GAME_AREA_ENTER) probe->enters++;
    if (event == BREAK_GAME_AREA_LEAVE) probe->leaves++;
}

static void set_pos(World *world, Entity entity, Vec3 pos) {
    Vec3 *p = (Vec3 *)world_get_component(world, entity, BREAK_GAME_POSITION_COMPONENT);
    if (p) {
        *p = pos;
    }
}

TEST(area_hysteresis_and_despawn_leave) {
    World *world = world_create();
    world_register_component(world, BREAK_GAME_POSITION_COMPONENT, sizeof(Vec3));
    BreakGameConfig cfg;
    cfg.max_classes = 0;
    cfg.max_actors = 8;
    BreakGame *game = break_game_create(world, &cfg);
    ComponentType comps[1] = {BREAK_GAME_POSITION_COMPONENT};
    BreakGameClassDesc desc;
    desc.name = "pawn";
    desc.components = comps;
    desc.component_count = 1;
    desc.lua_module = NULL;
    u32 id = 0;
    ASSERT_EQ(break_game_register_class(game, &desc, &id), BREAK_GAME_OK);
    BreakGameSpawn spawn;
    spawn.class_id = id;
    spawn.position = vec3(10, 0, 0);
    Entity entity = ENTITY_NULL;
    ASSERT_EQ(break_game_spawn(game, &spawn, &entity), BREAK_GAME_OK);

    BreakGameAreaDesc area;
    area.center = vec3(0, 0, 0);
    area.half_extent = vec3(1, 1, 1);
    area.radius = 0;
    u32 area_id = 99;
    ASSERT_EQ(break_game_area_add(game, &area, &area_id), BREAK_GAME_OK);
    ASSERT_EQ(area_id, 0u);
    AreaProbe probe;
    memset(&probe, 0, sizeof(probe));
    break_game_set_area_callback(game, on_area, &probe);

    ASSERT_EQ(break_game_area_tick(game), BREAK_GAME_OK);
    ASSERT_EQ(probe.enters, 0);

    set_pos(world, entity, vec3(1, 0, 0));
    ASSERT_EQ(break_game_area_tick(game), BREAK_GAME_OK);
    ASSERT_EQ(probe.enters, 1);
    ASSERT_EQ(break_game_area_tick(game), BREAK_GAME_OK);
    ASSERT_EQ(probe.enters, 1);

    set_pos(world, entity, vec3(1.1f, 0, 0));
    ASSERT_EQ(break_game_area_tick(game), BREAK_GAME_OK);
    ASSERT_EQ(probe.leaves, 0);
    set_pos(world, entity, vec3(0.9f, 0, 0));
    ASSERT_EQ(break_game_area_tick(game), BREAK_GAME_OK);
    ASSERT_EQ(probe.enters, 1);
    ASSERT_EQ(probe.leaves, 0);

    set_pos(world, entity, vec3(1.3f, 0, 0));
    ASSERT_EQ(break_game_area_tick(game), BREAK_GAME_OK);
    ASSERT_EQ(probe.leaves, 1);

    set_pos(world, entity, vec3(0, 0, 0));
    ASSERT_EQ(break_game_area_tick(game), BREAK_GAME_OK);
    ASSERT_EQ(probe.enters, 2);
    ASSERT_EQ(break_game_despawn(game, entity), BREAK_GAME_OK);
    ASSERT_EQ(probe.leaves, 2);
    ASSERT_EQ(break_game_area_tick(game), BREAK_GAME_OK);
    ASSERT_EQ(probe.leaves, 2);

    for (u32 i = 1; i < 256; i++) {
        u32 got = 0;
        ASSERT_EQ(break_game_area_add(game, &area, &got), BREAK_GAME_OK);
    }
    u32 overflow = 0;
    ASSERT_EQ(break_game_area_add(game, &area, &overflow), BREAK_GAME_OVERLOAD);

    break_game_destroy(game);
    world_destroy(world);
}

static int g_events;

static void count_area(u32 area_id, Entity entity, BreakGameAreaEvent event, void *user) {
    (void)area_id;
    (void)entity;
    (void)event;
    (void)user;
    g_events++;
}

TEST(area_defers_events_past_64) {
    World *world = world_create();
    world_register_component(world, BREAK_GAME_POSITION_COMPONENT, sizeof(Vec3));
    BreakGameConfig cfg;
    cfg.max_classes = 0;
    cfg.max_actors = 80;
    BreakGame *game = break_game_create(world, &cfg);
    ComponentType comps[1] = {BREAK_GAME_POSITION_COMPONENT};
    BreakGameClassDesc desc;
    desc.name = "pawn";
    desc.components = comps;
    desc.component_count = 1;
    desc.lua_module = NULL;
    u32 id = 0;
    ASSERT_EQ(break_game_register_class(game, &desc, &id), BREAK_GAME_OK);
    BreakGameSpawn spawn;
    spawn.class_id = id;
    spawn.position = vec3(0, 0, 0);
    for (int i = 0; i < 65; i++) {
        Entity entity = ENTITY_NULL;
        ASSERT_EQ(break_game_spawn(game, &spawn, &entity), BREAK_GAME_OK);
    }
    BreakGameAreaDesc area;
    area.center = vec3(0, 0, 0);
    area.half_extent = vec3(2, 2, 2);
    area.radius = 0;
    u32 area_id = 0;
    ASSERT_EQ(break_game_area_add(game, &area, &area_id), BREAK_GAME_OK);
    break_game_set_area_callback(game, count_area, NULL);
    g_events = 0;
    ASSERT_EQ(break_game_area_tick(game), BREAK_GAME_OVERLOAD);
    ASSERT_EQ(g_events, 64);
    g_events = 0;
    ASSERT_EQ(break_game_area_tick(game), BREAK_GAME_OK);
    ASSERT_EQ(g_events, 1);
    break_game_destroy(game);
    world_destroy(world);
}

TEST_MAIN_BEGIN()
    RUN_TEST(area_hysteresis_and_despawn_leave);
    RUN_TEST(area_defers_events_past_64);
TEST_MAIN_END()
