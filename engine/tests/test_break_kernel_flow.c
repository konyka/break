#include "test_framework.h"
#include <core/platform_thread.h>
#include <kernel/break_kernel.h>
#include <math.h>
#include <string.h>

static World *make_world(void) {
    World *world = world_create();
    world_register_component(world, BREAK_KERNEL_POSITION_COMPONENT, sizeof(Vec3));
    return world;
}

static BreakKernel *make_kernel(World *world, Entity *out_actor) {
    BreakKernelConfig cfg = {0u, 2u};
    BreakKernel *kernel = break_kernel_create(world, &cfg);
    if (!kernel) return NULL;
    ComponentType comps[1] = {BREAK_KERNEL_POSITION_COMPONENT};
    BreakKernelClassDesc desc = {"pawn", comps, 1u, NULL};
    u32 class_id = 0u;
    BreakKernelSpawn spawn;
    if (break_kernel_register_class(kernel, &desc, &class_id) != BREAK_KERNEL_OK) {
        break_kernel_destroy(kernel);
        return NULL;
    }
    spawn.class_id = class_id;
    spawn.position = vec3(1.0f, 2.0f, 3.0f);
    if (break_kernel_spawn(kernel, &spawn, out_actor) != BREAK_KERNEL_OK) {
        break_kernel_destroy(kernel);
        return NULL;
    }
    BreakKernelItemDesc item = {3u, 10u};
    if (break_kernel_item_define(kernel, &item) != BREAK_KERNEL_OK) {
        break_kernel_destroy(kernel);
        return NULL;
    }
    return kernel;
}

static BreakKernelEntityAction position_action(Entity actor, f32 x, f32 y, f32 z) {
    BreakKernelEntityAction action;
    memset(&action, 0, sizeof(action));
    action.type = BREAK_KERNEL_ENTITY_SET_POSITION;
    action.entity = actor;
    action.position = vec3(x, y, z);
    return action;
}

static BreakKernelEntityAction item_action(Entity actor, u32 count) {
    BreakKernelEntityAction action;
    memset(&action, 0, sizeof(action));
    action.type = BREAK_KERNEL_ENTITY_INVENTORY_ADD;
    action.entity = actor;
    action.item_id = 3u;
    action.count = count;
    return action;
}

TEST(late_inventory_failure_does_not_apply_earlier_position) {
    World *world = make_world();
    Entity actor = ENTITY_NULL;
    BreakKernel *kernel = make_kernel(world, &actor);
    ASSERT_NOT_NULL(kernel);
    BreakKernelEntityAction actions[2] = {
        position_action(actor, 8.0f, 9.0f, 10.0f), item_action(actor, 11u)};
    ASSERT_EQ(break_kernel_entity_actions_apply(kernel, actions, 2u),
              BREAK_KERNEL_OVERLOAD);
    Vec3 *pos = (Vec3 *)world_get_component(world, actor, BREAK_KERNEL_POSITION_COMPONENT);
    ASSERT_NOT_NULL(pos);
    ASSERT_FLOAT_EQ(pos->e[0], 1.0f, 0.0f);
    ASSERT_FLOAT_EQ(pos->e[1], 2.0f, 0.0f);
    ASSERT_FLOAT_EQ(pos->e[2], 3.0f, 0.0f);
    u32 count = 99u;
    ASSERT_EQ(break_kernel_inventory_count(kernel, actor, 3u, &count), BREAK_KERNEL_OK);
    ASSERT_EQ(count, 0u);
    break_kernel_destroy(kernel);
    world_destroy(world);
}

TEST(valid_batch_commits_position_and_inventory_together) {
    World *world = make_world();
    Entity actor = ENTITY_NULL;
    BreakKernel *kernel = make_kernel(world, &actor);
    ASSERT_NOT_NULL(kernel);
    BreakKernelEntityAction actions[2] = {
        position_action(actor, 8.0f, 9.0f, 10.0f), item_action(actor, 10u)};
    ASSERT_EQ(break_kernel_entity_actions_apply(kernel, actions, 2u), BREAK_KERNEL_OK);
    Vec3 *pos = (Vec3 *)world_get_component(world, actor, BREAK_KERNEL_POSITION_COMPONENT);
    ASSERT_FLOAT_EQ(pos->e[0], 8.0f, 0.0f);
    ASSERT_FLOAT_EQ(pos->e[1], 9.0f, 0.0f);
    ASSERT_FLOAT_EQ(pos->e[2], 10.0f, 0.0f);
    u32 count = 0u;
    ASSERT_EQ(break_kernel_inventory_count(kernel, actor, 3u, &count), BREAK_KERNEL_OK);
    ASSERT_EQ(count, 10u);
    break_kernel_destroy(kernel);
    world_destroy(world);
}

TEST(aggregate_additions_and_invalid_handles_are_preflighted) {
    World *world = make_world();
    Entity actor = ENTITY_NULL;
    BreakKernel *kernel = make_kernel(world, &actor);
    ASSERT_NOT_NULL(kernel);
    BreakKernelEntityAction actions[2] = {item_action(actor, 6u), item_action(actor, 5u)};
    ASSERT_EQ(break_kernel_entity_actions_apply(kernel, actions, 2u), BREAK_KERNEL_OVERLOAD);
    u32 count = 99u;
    ASSERT_EQ(break_kernel_inventory_count(kernel, actor, 3u, &count), BREAK_KERNEL_OK);
    ASSERT_EQ(count, 0u);
    Entity stale = actor;
    stale.generation++;
    actions[0] = position_action(actor, 7.0f, 7.0f, 7.0f);
    actions[1] = item_action(stale, 1u);
    ASSERT_EQ(break_kernel_entity_actions_apply(kernel, actions, 2u), BREAK_KERNEL_STALE);
    Vec3 *pos = (Vec3 *)world_get_component(world, actor, BREAK_KERNEL_POSITION_COMPONENT);
    ASSERT_FLOAT_EQ(pos->e[0], 1.0f, 0.0f);
    actions[1] = item_action(actor, 1u);
    actions[1].item_id = 4u;
    ASSERT_EQ(break_kernel_entity_actions_apply(kernel, actions, 2u), BREAK_KERNEL_STALE);
    actions[1] = position_action(actor, NAN, 0.0f, 0.0f);
    ASSERT_EQ(break_kernel_entity_actions_apply(kernel, actions, 2u), BREAK_KERNEL_INVALID);
    ASSERT_FLOAT_EQ(pos->e[0], 1.0f, 0.0f);
    break_kernel_destroy(kernel);
    world_destroy(world);
}

typedef struct {
    BreakKernel *kernel;
    BreakKernelEntityAction action;
    BreakKernelError result;
} ThreadProbe;

static PLATFORM_THREAD_RET apply_off_thread(PLATFORM_THREAD_ARG arg) {
    ThreadProbe *probe = (ThreadProbe *)arg;
    probe->result = break_kernel_entity_actions_apply(probe->kernel, &probe->action, 1u);
    return PLATFORM_THREAD_RETURN;
}

TEST(non_logic_thread_is_rejected_without_mutation) {
    World *world = make_world();
    Entity actor = ENTITY_NULL;
    BreakKernel *kernel = make_kernel(world, &actor);
    ASSERT_NOT_NULL(kernel);
    ThreadProbe probe;
    probe.kernel = kernel;
    probe.action = position_action(actor, 6.0f, 6.0f, 6.0f);
    probe.result = BREAK_KERNEL_OK;
    PlatformThread thread;
    ASSERT_TRUE(platform_thread_create(&thread, apply_off_thread, &probe));
    platform_thread_join(thread);
    ASSERT_EQ(probe.result, BREAK_KERNEL_REJECTED);
    Vec3 *pos = (Vec3 *)world_get_component(world, actor, BREAK_KERNEL_POSITION_COMPONENT);
    ASSERT_FLOAT_EQ(pos->e[0], 1.0f, 0.0f);
    break_kernel_destroy(kernel);
    world_destroy(world);
}

TEST_MAIN_BEGIN()
    RUN_TEST(late_inventory_failure_does_not_apply_earlier_position);
    RUN_TEST(valid_batch_commits_position_and_inventory_together);
    RUN_TEST(aggregate_additions_and_invalid_handles_are_preflighted);
    RUN_TEST(non_logic_thread_is_rejected_without_mutation);
TEST_MAIN_END()
