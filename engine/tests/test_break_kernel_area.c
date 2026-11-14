#include "test_framework.h"
#include <kernel/break_kernel.h>

typedef struct {
    int enters;
    int leaves;
    Entity last;
    BreakKernelAreaEvent last_event;
} AreaProbe;

static void on_area(u32 area_id, Entity entity, BreakKernelAreaEvent event, void *user) {
    AreaProbe *probe = (AreaProbe *)user;
    ASSERT_EQ(area_id, 0u);
    probe->last = entity;
    probe->last_event = event;
    if (event == BREAK_KERNEL_AREA_ENTER) probe->enters++;
    if (event == BREAK_KERNEL_AREA_LEAVE) probe->leaves++;
}

static void set_pos(World *world, Entity entity, Vec3 pos) {
    Vec3 *p = (Vec3 *)world_get_component(world, entity, BREAK_KERNEL_POSITION_COMPONENT);
    if (p) {
        *p = pos;
    }
}

TEST(area_hysteresis_and_despawn_leave) {
    World *world = world_create();
    world_register_component(world, BREAK_KERNEL_POSITION_COMPONENT, sizeof(Vec3));
    BreakKernelConfig cfg;
    cfg.max_classes = 0;
    cfg.max_actors = 8;
    BreakKernel *kernel = break_kernel_create(world, &cfg);
    ComponentType comps[1] = {BREAK_KERNEL_POSITION_COMPONENT};
    BreakKernelClassDesc desc;
    desc.name = "pawn";
    desc.components = comps;
    desc.component_count = 1;
    desc.lua_module = NULL;
    u32 id = 0;
    ASSERT_EQ(break_kernel_register_class(kernel, &desc, &id), BREAK_KERNEL_OK);
    BreakKernelSpawn spawn;
    spawn.class_id = id;
    spawn.position = vec3(10, 0, 0);
    Entity entity = ENTITY_NULL;
    ASSERT_EQ(break_kernel_spawn(kernel, &spawn, &entity), BREAK_KERNEL_OK);

    BreakKernelAreaDesc area;
    area.center = vec3(0, 0, 0);
    area.half_extent = vec3(1, 1, 1);
    area.radius = 0;
    u32 area_id = 99;
    ASSERT_EQ(break_kernel_area_add(kernel, &area, &area_id), BREAK_KERNEL_OK);
    ASSERT_EQ(area_id, 0u);
    AreaProbe probe;
    memset(&probe, 0, sizeof(probe));
    break_kernel_set_area_callback(kernel, on_area, &probe);

    ASSERT_EQ(break_kernel_area_tick(kernel), BREAK_KERNEL_OK);
    ASSERT_EQ(probe.enters, 0);

    set_pos(world, entity, vec3(1, 0, 0));
    ASSERT_EQ(break_kernel_area_tick(kernel), BREAK_KERNEL_OK);
    ASSERT_EQ(probe.enters, 1);
    ASSERT_EQ(break_kernel_area_tick(kernel), BREAK_KERNEL_OK);
    ASSERT_EQ(probe.enters, 1);

    set_pos(world, entity, vec3(1.1f, 0, 0));
    ASSERT_EQ(break_kernel_area_tick(kernel), BREAK_KERNEL_OK);
    ASSERT_EQ(probe.leaves, 0);
    set_pos(world, entity, vec3(0.9f, 0, 0));
    ASSERT_EQ(break_kernel_area_tick(kernel), BREAK_KERNEL_OK);
    ASSERT_EQ(probe.enters, 1);
    ASSERT_EQ(probe.leaves, 0);

    set_pos(world, entity, vec3(1.3f, 0, 0));
    ASSERT_EQ(break_kernel_area_tick(kernel), BREAK_KERNEL_OK);
    ASSERT_EQ(probe.leaves, 1);

    set_pos(world, entity, vec3(0, 0, 0));
    ASSERT_EQ(break_kernel_area_tick(kernel), BREAK_KERNEL_OK);
    ASSERT_EQ(probe.enters, 2);
    ASSERT_EQ(break_kernel_despawn(kernel, entity), BREAK_KERNEL_OK);
    ASSERT_EQ(probe.leaves, 2);
    ASSERT_EQ(break_kernel_area_tick(kernel), BREAK_KERNEL_OK);
    ASSERT_EQ(probe.leaves, 2);

    for (u32 i = 1; i < 256; i++) {
        u32 got = 0;
        ASSERT_EQ(break_kernel_area_add(kernel, &area, &got), BREAK_KERNEL_OK);
    }
    u32 overflow = 0;
    ASSERT_EQ(break_kernel_area_add(kernel, &area, &overflow), BREAK_KERNEL_OVERLOAD);

    break_kernel_destroy(kernel);
    world_destroy(world);
}

static int g_events;

static void count_area(u32 area_id, Entity entity, BreakKernelAreaEvent event, void *user) {
    (void)area_id;
    (void)entity;
    (void)event;
    (void)user;
    g_events++;
}

TEST(area_defers_events_past_64) {
    World *world = world_create();
    world_register_component(world, BREAK_KERNEL_POSITION_COMPONENT, sizeof(Vec3));
    BreakKernelConfig cfg;
    cfg.max_classes = 0;
    cfg.max_actors = 80;
    BreakKernel *kernel = break_kernel_create(world, &cfg);
    ComponentType comps[1] = {BREAK_KERNEL_POSITION_COMPONENT};
    BreakKernelClassDesc desc;
    desc.name = "pawn";
    desc.components = comps;
    desc.component_count = 1;
    desc.lua_module = NULL;
    u32 id = 0;
    ASSERT_EQ(break_kernel_register_class(kernel, &desc, &id), BREAK_KERNEL_OK);
    BreakKernelSpawn spawn;
    spawn.class_id = id;
    spawn.position = vec3(0, 0, 0);
    for (int i = 0; i < 65; i++) {
        Entity entity = ENTITY_NULL;
        ASSERT_EQ(break_kernel_spawn(kernel, &spawn, &entity), BREAK_KERNEL_OK);
    }
    BreakKernelAreaDesc area;
    area.center = vec3(0, 0, 0);
    area.half_extent = vec3(2, 2, 2);
    area.radius = 0;
    u32 area_id = 0;
    ASSERT_EQ(break_kernel_area_add(kernel, &area, &area_id), BREAK_KERNEL_OK);
    break_kernel_set_area_callback(kernel, count_area, NULL);
    g_events = 0;
    ASSERT_EQ(break_kernel_area_tick(kernel), BREAK_KERNEL_OVERLOAD);
    ASSERT_EQ(g_events, 64);
    g_events = 0;
    ASSERT_EQ(break_kernel_area_tick(kernel), BREAK_KERNEL_OK);
    ASSERT_EQ(g_events, 1);
    break_kernel_destroy(kernel);
    world_destroy(world);
}

TEST_MAIN_BEGIN()
    RUN_TEST(area_hysteresis_and_despawn_leave);
    RUN_TEST(area_defers_events_past_64);
TEST_MAIN_END()
