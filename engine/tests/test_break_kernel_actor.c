#include "test_framework.h"
#include <kernel/break_kernel.h>
#include <core/platform_thread.h>

static World *make_world(void) {
    World *world = world_create();
    world_register_component(world, BREAK_KERNEL_POSITION_COMPONENT, sizeof(Vec3));
    world_register_component(world, 1, sizeof(u32));
    return world;
}

static BreakKernel *make_kernel(World *world, u32 max_actors) {
    BreakKernelConfig cfg;
    cfg.max_classes = 0;
    cfg.max_actors = max_actors;
    return break_kernel_create(world, &cfg);
}

TEST(create_rejects_null_world_and_over_cap) {
    ASSERT_TRUE(break_kernel_create(NULL, NULL) == NULL);
    World *world = world_create();
    BreakKernelConfig cfg;
    cfg.max_classes = 65;
    cfg.max_actors = 1;
    ASSERT_TRUE(break_kernel_create(world, &cfg) == NULL);
    cfg.max_classes = 1;
    cfg.max_actors = 4097;
    ASSERT_TRUE(break_kernel_create(world, &cfg) == NULL);
    break_kernel_destroy(NULL);
    world_destroy(world);
}

TEST(register_class_ids_names_and_caps) {
    World *world = make_world();
    BreakKernel *kernel = make_kernel(world, 4);
    ASSERT_NOT_NULL(kernel);
    ComponentType comps[1] = {BREAK_KERNEL_POSITION_COMPONENT};
    BreakKernelClassDesc desc;
    desc.name = "pawn";
    desc.components = comps;
    desc.component_count = 1;
    desc.lua_module = "mod.pawn";
    u32 id = 0;
    ASSERT_EQ(break_kernel_register_class(kernel, &desc, &id), BREAK_KERNEL_OK);
    ASSERT_EQ(id, 1u);
    u32 untouched = 99;
    desc.name = "pawn";
    ASSERT_EQ(break_kernel_register_class(kernel, &desc, &untouched), BREAK_KERNEL_REJECTED);
    ASSERT_EQ(untouched, 99u);
    desc.name = "";
    ASSERT_EQ(break_kernel_register_class(kernel, &desc, &untouched), BREAK_KERNEL_INVALID);
    ASSERT_EQ(untouched, 99u);
    desc.name = "too_many";
    ComponentType many[17];
    for (u32 i = 0; i < 17; i++) many[i] = 0;
    desc.components = many;
    desc.component_count = 17;
    ASSERT_EQ(break_kernel_register_class(kernel, &desc, &untouched), BREAK_KERNEL_INVALID);
    desc.components = comps;
    desc.component_count = 1;
    for (u32 i = 0; i < 63; i++) {
        char name[16];
        snprintf(name, sizeof(name), "c%u", i);
        desc.name = name;
        u32 got = 0;
        ASSERT_EQ(break_kernel_register_class(kernel, &desc, &got), BREAK_KERNEL_OK);
        ASSERT_EQ(got, i + 2u);
    }
    desc.name = "overflow";
    ASSERT_EQ(break_kernel_register_class(kernel, &desc, &untouched), BREAK_KERNEL_OVERLOAD);
    ASSERT_EQ(untouched, 99u);
    break_kernel_destroy(kernel);
    world_destroy(world);
}

typedef struct {
    BreakKernel *kernel;
    BreakKernelError err;
} ThreadProbe;

static PLATFORM_THREAD_RET register_off_thread(PLATFORM_THREAD_ARG arg) {
    ThreadProbe *probe = (ThreadProbe *)arg;
    ComponentType comps[1] = {0};
    BreakKernelClassDesc desc;
    desc.name = "worker";
    desc.components = comps;
    desc.component_count = 1;
    desc.lua_module = NULL;
    u32 id = 0;
    probe->err = break_kernel_register_class(probe->kernel, &desc, &id);
    return PLATFORM_THREAD_RETURN;
}

TEST(register_from_other_thread_is_rejected) {
    World *world = make_world();
    BreakKernel *kernel = make_kernel(world, 2);
    ThreadProbe probe;
    probe.kernel = kernel;
    probe.err = BREAK_KERNEL_OK;
    PlatformThread thread;
    ASSERT_TRUE(platform_thread_create(&thread, register_off_thread, &probe));
    platform_thread_join(thread);
    ASSERT_EQ(probe.err, BREAK_KERNEL_REJECTED);
    ComponentType comps[1] = {0};
    BreakKernelClassDesc desc;
    desc.name = "worker";
    desc.components = comps;
    desc.component_count = 1;
    desc.lua_module = NULL;
    u32 id = 0;
    ASSERT_EQ(break_kernel_register_class(kernel, &desc, &id), BREAK_KERNEL_OK);
    ASSERT_EQ(id, 1u);
    break_kernel_destroy(kernel);
    world_destroy(world);
}

static int g_ticks;
static Entity g_victim;

static void tick_despawn_victim(BreakKernel *kernel, Entity entity, f32 dt, void *user) {
    (void)user;
    g_ticks++;
    ASSERT_FLOAT_EQ(dt, 0.25f, 1e-6);
    if (entity.index != g_victim.index) {
        ASSERT_EQ(break_kernel_despawn(kernel, g_victim), BREAK_KERNEL_OK);
    }
}

TEST(spawn_writes_position_and_tick_skips_despawned) {
    World *world = make_world();
    BreakKernel *kernel = make_kernel(world, 4);
    ComponentType comps[2] = {BREAK_KERNEL_POSITION_COMPONENT, 1};
    BreakKernelClassDesc desc;
    desc.name = "pawn";
    desc.components = comps;
    desc.component_count = 2;
    desc.lua_module = NULL;
    u32 id = 0;
    ASSERT_EQ(break_kernel_register_class(kernel, &desc, &id), BREAK_KERNEL_OK);
    break_kernel_set_tick(kernel, id, tick_despawn_victim, NULL);
    BreakKernelSpawn spawn;
    spawn.class_id = id;
    spawn.position = vec3(3.0f, 4.0f, 5.0f);
    Entity first = ENTITY_NULL;
    Entity second = ENTITY_NULL;
    ASSERT_EQ(break_kernel_spawn(kernel, &spawn, &first), BREAK_KERNEL_OK);
    ASSERT_EQ(break_kernel_spawn(kernel, &spawn, &second), BREAK_KERNEL_OK);
    Vec3 *pos = (Vec3 *)world_get_component(world, first, BREAK_KERNEL_POSITION_COMPONENT);
    ASSERT_NOT_NULL(pos);
    ASSERT_FLOAT_EQ(pos->e[0], 3.0f, 1e-6);
    ASSERT_FLOAT_EQ(pos->e[1], 4.0f, 1e-6);
    ASSERT_FLOAT_EQ(pos->e[2], 5.0f, 1e-6);
    u32 *marker = (u32 *)world_get_component(world, first, 1);
    ASSERT_NOT_NULL(marker);
    ASSERT_EQ(*marker, 0u);
    g_ticks = 0;
    g_victim = second;
    break_kernel_tick(kernel, 0.25f);
    ASSERT_EQ(g_ticks, 1);
    ASSERT_EQ(break_kernel_despawn(kernel, second), BREAK_KERNEL_STALE);
    spawn.class_id = 99;
    Entity ignored = ENTITY_NULL;
    ASSERT_EQ(break_kernel_spawn(kernel, &spawn, &ignored), BREAK_KERNEL_STALE);
    break_kernel_destroy(kernel);
    world_destroy(world);
}

TEST(spawn_cap_does_not_create_an_entity) {
    World *world = make_world();
    BreakKernel *kernel = make_kernel(world, 1);
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
    Entity entity = ENTITY_NULL;
    ASSERT_EQ(break_kernel_spawn(kernel, &spawn, &entity), BREAK_KERNEL_OK);
    u32 count = world->entity_count;
    Entity extra = ENTITY_NULL;
    ASSERT_EQ(break_kernel_spawn(kernel, &spawn, &extra), BREAK_KERNEL_OVERLOAD);
    ASSERT_EQ(world->entity_count, count);
    ASSERT_FALSE(entity_valid(extra));
    break_kernel_destroy(kernel);
    world_destroy(world);
}

TEST(default_actor_cap_is_4096) {
    World *world = make_world();
    BreakKernel *kernel = break_kernel_create(world, NULL);
    ASSERT_NOT_NULL(kernel);
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
    spawn.position = vec3(1, 0, 0);
    for (u32 i = 0; i < 4096; i++) {
        Entity entity = ENTITY_NULL;
        ASSERT_EQ(break_kernel_spawn(kernel, &spawn, &entity), BREAK_KERNEL_OK);
    }
    u32 count = world->entity_count;
    Entity extra = ENTITY_NULL;
    ASSERT_EQ(break_kernel_spawn(kernel, &spawn, &extra), BREAK_KERNEL_OVERLOAD);
    ASSERT_EQ(world->entity_count, count);
    break_kernel_destroy(kernel);
    world_destroy(world);
}

TEST_MAIN_BEGIN()
    RUN_TEST(create_rejects_null_world_and_over_cap);
    RUN_TEST(register_class_ids_names_and_caps);
    RUN_TEST(register_from_other_thread_is_rejected);
    RUN_TEST(spawn_writes_position_and_tick_skips_despawned);
    RUN_TEST(spawn_cap_does_not_create_an_entity);
    RUN_TEST(default_actor_cap_is_4096);
TEST_MAIN_END()
