#include "test_framework.h"
#include <kernel/break_kernel.h>
#include <stdio.h>

typedef struct {
    int loads;
    int unloads;
    BreakKernelError load_result;
    char path[256];
} LevelProbe;

static BreakKernelError on_load(void *user, World *world, const char *path) {
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

static void count_tick(BreakKernel *kernel, Entity entity, f32 dt, void *user) {
    (void)kernel;
    (void)entity;
    (void)dt;
    int *n = (int *)user;
    (*n)++;
}

TEST(level_open_adopts_sidecar_and_rolls_back) {
    char dir[128];
    char side[160];
    test_tmp(dir, sizeof(dir), "kernel_level");
    snprintf(side, sizeof(side), "%s_side.txt", dir);

    World *world = world_create();
    world_register_component(world, BREAK_KERNEL_POSITION_COMPONENT, sizeof(Vec3));
    BreakKernel *kernel = break_kernel_create(world, NULL);
    ComponentType comps[1] = {BREAK_KERNEL_POSITION_COMPONENT};
    BreakKernelClassDesc desc;
    desc.name = "mob";
    desc.components = comps;
    desc.component_count = 1;
    desc.lua_module = NULL;
    u32 id = 0;
    ASSERT_EQ(break_kernel_register_class(kernel, &desc, &id), BREAK_KERNEL_OK);
    int ticks = 0;
    break_kernel_set_tick(kernel, id, count_tick, &ticks);

    Entity a = world_create_entity(world);
    Entity b = world_create_entity(world);
    Entity extra = world_create_entity(world);
    FILE *file = fopen(side, "wb");
    ASSERT_NOT_NULL(file);
    fprintf(file, "# comment\n%u mob\n%u mob\n", a.index, b.index);
    fclose(file);

    LevelProbe probe;
    memset(&probe, 0, sizeof(probe));
    probe.load_result = BREAK_KERNEL_FAILED;
    BreakKernelLevelHooks hooks;
    hooks.load = on_load;
    hooks.unload = on_unload;
    hooks.user = &probe;
    ASSERT_EQ(break_kernel_level_open(kernel, &hooks, "scene.bscn", side), BREAK_KERNEL_FAILED);
    ASSERT_EQ(probe.loads, 1);
    ASSERT_EQ(probe.unloads, 0);
    ASSERT_EQ(ticks, 0);

    probe.load_result = BREAK_KERNEL_OK;
    ASSERT_EQ(break_kernel_level_open(kernel, &hooks, "scene.bscn", side), BREAK_KERNEL_OK);
    ASSERT_STR_EQ(probe.path, "scene.bscn");
    break_kernel_tick(kernel, 0.1f);
    ASSERT_EQ(ticks, 2);
    ASSERT_EQ(break_kernel_level_open(kernel, &hooks, "scene.bscn", side), BREAK_KERNEL_REJECTED);
    ASSERT_EQ(probe.loads, 2);

    ASSERT_EQ(break_kernel_level_close(kernel), BREAK_KERNEL_OK);
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
    ASSERT_EQ(break_kernel_level_open(kernel, &hooks, "scene.bscn", side), BREAK_KERNEL_FAILED);
    ASSERT_EQ(probe.unloads, 2);
    ASSERT_TRUE(world_entity_exists(world, c));
    ASSERT_TRUE(world_entity_exists(world, d));
    ticks = 0;
    break_kernel_tick(kernel, 0.1f);
    ASSERT_EQ(ticks, 0);
    ASSERT_EQ(probe.loads, loads_before + 1);

    ASSERT_EQ(break_kernel_level_open(kernel, &hooks, "scene.bscn", NULL), BREAK_KERNEL_OK);
    ticks = 0;
    break_kernel_tick(kernel, 0.1f);
    ASSERT_EQ(ticks, 0);
    ASSERT_EQ(break_kernel_level_close(kernel), BREAK_KERNEL_OK);
    remove(side);

    break_kernel_destroy(kernel);
    world_destroy(world);
}

typedef struct {
    World *world;
    BreakKernel *kernel;
    u32 class_id;
    int ticks;
    LevelProbe probe;
    BreakKernelLevelHooks hooks;
    char side[160];
} LevelFixture;

static bool level_fixture_open(LevelFixture *f, const char *tag) {
    memset(f, 0, sizeof(*f));
    char dir[128];
    test_tmp(dir, sizeof(dir), tag);
    snprintf(f->side, sizeof(f->side), "%s_side.txt", dir);
    f->world = world_create();
    if (!f->world) return false;
    world_register_component(f->world, BREAK_KERNEL_POSITION_COMPONENT, sizeof(Vec3));
    f->kernel = break_kernel_create(f->world, NULL);
    if (!f->kernel) return false;
    ComponentType comps[1] = {BREAK_KERNEL_POSITION_COMPONENT};
    BreakKernelClassDesc desc;
    desc.name = "mob";
    desc.components = comps;
    desc.component_count = 1;
    desc.lua_module = NULL;
    if (break_kernel_register_class(f->kernel, &desc, &f->class_id) != BREAK_KERNEL_OK) return false;
    break_kernel_set_tick(f->kernel, f->class_id, count_tick, &f->ticks);
    f->hooks.load = on_load;
    f->hooks.unload = on_unload;
    f->hooks.user = &f->probe;
    f->probe.load_result = BREAK_KERNEL_OK;
    return true;
}

static void level_fixture_close(LevelFixture *f) {
    remove(f->side);
    break_kernel_destroy(f->kernel);
    world_destroy(f->world);
}

static bool write_side(const char *path, const char *text) {
    FILE *file = fopen(path, "wb");
    if (!file) return false;
    fputs(text, file);
    fclose(file);
    return true;
}

/* Blank lines, indentation, CRLF endings and trailing blanks are accepted. */
TEST(sidecar_tolerates_whitespace_and_crlf) {
    LevelFixture f;
    ASSERT_TRUE(level_fixture_open(&f, "kernel_level_ws"));
    Entity a = world_create_entity(f.world);
    Entity b = world_create_entity(f.world);
    char text[160];
    snprintf(text, sizeof(text), "\r\n   \n\t%u\tmob  \r\n  # note\n%u mob\t\n", a.index, b.index);
    ASSERT_TRUE(write_side(f.side, text));
    ASSERT_EQ(break_kernel_level_open(f.kernel, &f.hooks, "s.bscn", f.side), BREAK_KERNEL_OK);
    break_kernel_tick(f.kernel, 0.1f);
    ASSERT_EQ(f.ticks, 2);
    ASSERT_EQ(break_kernel_level_close(f.kernel), BREAK_KERNEL_OK);
    level_fixture_close(&f);
}

/* Each malformed row fails with its own error and the scene is unloaded:
 * a missing class name, a dead entity index, a repeated entity, a NUL byte,
 * a missing file. */
TEST(sidecar_errors_roll_back_the_scene) {
    LevelFixture f;
    ASSERT_TRUE(level_fixture_open(&f, "kernel_level_err"));
    Entity a = world_create_entity(f.world);
    char text[160];
    snprintf(text, sizeof(text), "%u\n", a.index);
    ASSERT_TRUE(write_side(f.side, text));
    ASSERT_EQ(break_kernel_level_open(f.kernel, &f.hooks, "s.bscn", f.side), BREAK_KERNEL_INVALID);
    snprintf(text, sizeof(text), "%u mob\n", 9999u);
    ASSERT_TRUE(write_side(f.side, text));
    ASSERT_EQ(break_kernel_level_open(f.kernel, &f.hooks, "s.bscn", f.side), BREAK_KERNEL_STALE);
    snprintf(text, sizeof(text), "%u mob\n%u mob\n", a.index, a.index);
    ASSERT_TRUE(write_side(f.side, text));
    ASSERT_EQ(break_kernel_level_open(f.kernel, &f.hooks, "s.bscn", f.side), BREAK_KERNEL_REJECTED);
    FILE *nul = fopen(f.side, "wb");
    ASSERT_NOT_NULL(nul);
    fputs("1 mob", nul);
    fputc('\0', nul);
    fclose(nul);
    ASSERT_EQ(break_kernel_level_open(f.kernel, &f.hooks, "s.bscn", f.side), BREAK_KERNEL_INVALID);
    remove(f.side);
    ASSERT_EQ(break_kernel_level_open(f.kernel, &f.hooks, "s.bscn", f.side), BREAK_KERNEL_FAILED);
    ASSERT_EQ(f.probe.loads, 5);
    ASSERT_EQ(f.probe.unloads, 5);
    ASSERT_TRUE(world_entity_exists(f.world, a));
    break_kernel_tick(f.kernel, 0.1f);
    ASSERT_EQ(f.ticks, 0);
    /* the kernel is still usable after the failures */
    ASSERT_EQ(break_kernel_level_open(f.kernel, &f.hooks, "s.bscn", NULL), BREAK_KERNEL_OK);
    ASSERT_EQ(break_kernel_level_close(f.kernel), BREAK_KERNEL_OK);
    level_fixture_close(&f);
}

/* Closing twice reports CLOSED; bad arguments are refused before the load
 * hook runs; an empty sidecar path behaves like no sidecar. */
TEST(level_open_and_close_arguments) {
    LevelFixture f;
    ASSERT_TRUE(level_fixture_open(&f, "kernel_level_args"));
    ASSERT_EQ(break_kernel_level_close(f.kernel), BREAK_KERNEL_CLOSED);
    ASSERT_EQ(break_kernel_level_open(f.kernel, NULL, "s.bscn", NULL), BREAK_KERNEL_INVALID);
    ASSERT_EQ(break_kernel_level_open(f.kernel, &f.hooks, "", NULL), BREAK_KERNEL_INVALID);
    ASSERT_EQ(break_kernel_level_open(f.kernel, &f.hooks, NULL, NULL), BREAK_KERNEL_INVALID);
    BreakKernelLevelHooks no_load = f.hooks;
    no_load.load = NULL;
    ASSERT_EQ(break_kernel_level_open(f.kernel, &no_load, "s.bscn", NULL), BREAK_KERNEL_INVALID);
    ASSERT_EQ(f.probe.loads, 0);
    ASSERT_EQ(break_kernel_level_open(f.kernel, &f.hooks, "s.bscn", ""), BREAK_KERNEL_OK);
    ASSERT_EQ(f.probe.loads, 1);
    ASSERT_EQ(break_kernel_level_close(f.kernel), BREAK_KERNEL_OK);
    ASSERT_EQ(break_kernel_level_close(f.kernel), BREAK_KERNEL_CLOSED);
    ASSERT_EQ(f.probe.unloads, 1);
    /* a hook set without unload still closes */
    BreakKernelLevelHooks no_unload = f.hooks;
    no_unload.unload = NULL;
    ASSERT_EQ(break_kernel_level_open(f.kernel, &no_unload, "s.bscn", NULL), BREAK_KERNEL_OK);
    ASSERT_EQ(break_kernel_level_close(f.kernel), BREAK_KERNEL_OK);
    ASSERT_EQ(f.probe.unloads, 1);
    ASSERT_EQ(break_kernel_level_close(NULL), BREAK_KERNEL_INVALID);
    level_fixture_close(&f);
}

TEST_MAIN_BEGIN()
    RUN_TEST(level_open_adopts_sidecar_and_rolls_back);
    RUN_TEST(sidecar_tolerates_whitespace_and_crlf);
    RUN_TEST(sidecar_errors_roll_back_the_scene);
    RUN_TEST(level_open_and_close_arguments);
TEST_MAIN_END()
