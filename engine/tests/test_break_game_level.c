#include "test_framework.h"
#include <game/break_game.h>
#include <stdio.h>

typedef struct {
    int loads;
    int unloads;
    BreakGameError load_result;
    char path[256];
} LevelProbe;

static BreakGameError on_load(void *user, World *world, const char *path) {
    (void)world;
    LevelProbe *probe = (LevelProbe *)user;
    probe->loads++;
    snprintf(probe->path, sizeof(probe->path), "%s", path);
    return probe->load_result;
}

static void on_unload(void *user, World *world) {
    (void)world;
    LevelProbe *probe = (LevelProbe *)user;
    probe->unloads++;
}

static void count_tick(BreakGame *game, Entity entity, f32 dt, void *user) {
    (void)game;
    (void)entity;
    (void)dt;
    int *n = (int *)user;
    (*n)++;
}

TEST(level_open_adopts_sidecar_and_rolls_back) {
    char dir[128];
    char side[160];
    test_tmp(dir, sizeof(dir), "game_level");
    snprintf(side, sizeof(side), "%s_side.txt", dir);

    World *world = world_create();
    world_register_component(world, BREAK_GAME_POSITION_COMPONENT, sizeof(Vec3));
    BreakGame *game = break_game_create(world, NULL);
    ComponentType comps[1] = {BREAK_GAME_POSITION_COMPONENT};
    BreakGameClassDesc desc;
    desc.name = "mob";
    desc.components = comps;
    desc.component_count = 1;
    desc.lua_module = NULL;
    u32 id = 0;
    ASSERT_EQ(break_game_register_class(game, &desc, &id), BREAK_GAME_OK);
    int ticks = 0;
    break_game_set_tick(game, id, count_tick, &ticks);

    Entity a = world_create_entity(world);
    Entity b = world_create_entity(world);
    Entity extra = world_create_entity(world);
    FILE *file = fopen(side, "wb");
    ASSERT_NOT_NULL(file);
    fprintf(file, "# comment\n%u mob\n%u mob\n", a.index, b.index);
    fclose(file);

    LevelProbe probe;
    memset(&probe, 0, sizeof(probe));
    probe.load_result = BREAK_GAME_FAILED;
    BreakGameLevelHooks hooks;
    hooks.load = on_load;
    hooks.unload = on_unload;
    hooks.user = &probe;
    ASSERT_EQ(break_game_level_open(game, &hooks, "scene.bscn", side), BREAK_GAME_FAILED);
    ASSERT_EQ(probe.loads, 1);
    ASSERT_EQ(probe.unloads, 0);
    ASSERT_EQ(ticks, 0);

    probe.load_result = BREAK_GAME_OK;
    ASSERT_EQ(break_game_level_open(game, &hooks, "scene.bscn", side), BREAK_GAME_OK);
    ASSERT_STR_EQ(probe.path, "scene.bscn");
    break_game_tick(game, 0.1f);
    ASSERT_EQ(ticks, 2);
    ASSERT_EQ(break_game_level_open(game, &hooks, "scene.bscn", side), BREAK_GAME_REJECTED);
    ASSERT_EQ(probe.loads, 2);

    ASSERT_EQ(break_game_level_close(game), BREAK_GAME_OK);
    ASSERT_EQ(probe.unloads, 1);
    ASSERT_FALSE(world_entity_exists(world, a));
    ASSERT_FALSE(world_entity_exists(world, b));
    ASSERT_TRUE(world_entity_exists(world, extra));

    FILE *bad = fopen(side, "wb");
    ASSERT_NOT_NULL(bad);
    Entity c = world_create_entity(world);
    Entity d = world_create_entity(world);
    fprintf(bad, "%u mob\n%u nope\n", c.index, d.index);
    fclose(bad);
    int loads_before = probe.loads;
    ASSERT_EQ(break_game_level_open(game, &hooks, "scene.bscn", side), BREAK_GAME_FAILED);
    ASSERT_EQ(probe.unloads, 2);
    ASSERT_TRUE(world_entity_exists(world, c));
    ASSERT_TRUE(world_entity_exists(world, d));
    ticks = 0;
    break_game_tick(game, 0.1f);
    ASSERT_EQ(ticks, 0);
    ASSERT_EQ(probe.loads, loads_before + 1);

    ASSERT_EQ(break_game_level_open(game, &hooks, "scene.bscn", NULL), BREAK_GAME_OK);
    ticks = 0;
    break_game_tick(game, 0.1f);
    ASSERT_EQ(ticks, 0);
    ASSERT_EQ(break_game_level_close(game), BREAK_GAME_OK);
    remove(side);

    break_game_destroy(game);
    world_destroy(world);
}

TEST_MAIN_BEGIN()
    RUN_TEST(level_open_adopts_sidecar_and_rolls_back);
TEST_MAIN_END()
