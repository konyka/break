#include "test_framework.h"
#include <kernel/break_kernel.h>
#include <stdint.h>

#define AMMO_ID   1u
#define MEDKIT_ID 2u

static World *make_world(void) {
    World *world = world_create();
    world_register_component(world, BREAK_KERNEL_POSITION_COMPONENT, sizeof(Vec3));
    return world;
}

static BreakKernel *make_kernel(World *world) {
    BreakKernelConfig cfg;
    cfg.max_classes = 0;
    cfg.max_actors = 2;
    return break_kernel_create(world, &cfg);
}

static u32 register_pawn(BreakKernel *kernel) {
    ComponentType comps[1] = {BREAK_KERNEL_POSITION_COMPONENT};
    BreakKernelClassDesc desc;
    desc.name = "pawn";
    desc.components = comps;
    desc.component_count = 1;
    desc.lua_module = NULL;
    u32 id = 0;
    if (break_kernel_register_class(kernel, &desc, &id) != BREAK_KERNEL_OK) {
        return 0;
    }
    return id;
}

static Entity spawn_actor(BreakKernel *kernel, u32 class_id) {
    BreakKernelSpawn spawn;
    spawn.class_id = class_id;
    spawn.position = vec3(0, 0, 0);
    Entity entity = ENTITY_NULL;
    if (break_kernel_spawn(kernel, &spawn, &entity) != BREAK_KERNEL_OK) {
        return ENTITY_NULL;
    }
    return entity;
}

static bool define_standard_items(BreakKernel *kernel) {
    BreakKernelItemDesc ammo = {AMMO_ID, 30u};
    BreakKernelItemDesc medkit = {MEDKIT_ID, 2u};
    return break_kernel_item_define(kernel, &ammo) == BREAK_KERNEL_OK &&
           break_kernel_item_define(kernel, &medkit) == BREAK_KERNEL_OK;
}

static void destroy_kernel(BreakKernel *kernel, World *world) {
    break_kernel_destroy(kernel);
    world_destroy(world);
}

TEST(item_definition_enforces_exact_bounds) {
    World *world = make_world();
    BreakKernel *kernel = make_kernel(world);
    ASSERT_NOT_NULL(kernel);
    BreakKernelItemDesc desc = {AMMO_ID, 30u};
    ASSERT_EQ(break_kernel_item_define(kernel, &desc), BREAK_KERNEL_OK);
    ASSERT_EQ(break_kernel_item_define(kernel, &desc), BREAK_KERNEL_REJECTED);
    desc.item_id = 0;
    ASSERT_EQ(break_kernel_item_define(kernel, &desc), BREAK_KERNEL_INVALID);
    desc.item_id = 65;
    ASSERT_EQ(break_kernel_item_define(kernel, &desc), BREAK_KERNEL_INVALID);
    desc.item_id = 3;
    desc.stack_limit = 0;
    ASSERT_EQ(break_kernel_item_define(kernel, &desc), BREAK_KERNEL_INVALID);
    desc.stack_limit = 1000001u;
    ASSERT_EQ(break_kernel_item_define(kernel, &desc), BREAK_KERNEL_INVALID);
    desc.item_id = BREAK_KERNEL_MAX_ITEMS;
    desc.stack_limit = 1000000u;
    ASSERT_EQ(break_kernel_item_define(kernel, &desc), BREAK_KERNEL_OK);
    destroy_kernel(kernel, world);
}

TEST(add_validates_input_and_preserves_count_on_overload) {
    World *world = make_world();
    BreakKernel *kernel = make_kernel(world);
    ASSERT_NOT_NULL(kernel);
    u32 class_id = register_pawn(kernel);
    ASSERT_NEQ(class_id, 0u);
    Entity actor = spawn_actor(kernel, class_id);
    ASSERT_TRUE(entity_valid(actor));
    ASSERT_TRUE(define_standard_items(kernel));
    ASSERT_EQ(break_kernel_inventory_add(kernel, actor, AMMO_ID, 0u), BREAK_KERNEL_INVALID);
    ASSERT_EQ(break_kernel_inventory_add(kernel, actor, 0u, 1u), BREAK_KERNEL_INVALID);
    ASSERT_EQ(break_kernel_inventory_add(kernel, actor, 65u, 1u), BREAK_KERNEL_INVALID);
    ASSERT_EQ(break_kernel_inventory_add(kernel, actor, 3u, 1u), BREAK_KERNEL_STALE);
    Entity stale = actor;
    stale.generation++;
    ASSERT_EQ(break_kernel_inventory_add(kernel, stale, AMMO_ID, 1u), BREAK_KERNEL_STALE);
    u32 count = 777u;
    ASSERT_EQ(break_kernel_inventory_count(kernel, stale, AMMO_ID, &count), BREAK_KERNEL_STALE);
    ASSERT_EQ(count, 777u);
    ASSERT_EQ(break_kernel_inventory_count(kernel, actor, 3u, &count), BREAK_KERNEL_STALE);
    ASSERT_EQ(count, 777u);
    ASSERT_EQ(break_kernel_inventory_count(kernel, actor, AMMO_ID, NULL), BREAK_KERNEL_INVALID);
    ASSERT_EQ(break_kernel_inventory_add(kernel, actor, AMMO_ID, 25u), BREAK_KERNEL_OK);
    ASSERT_EQ(break_kernel_inventory_add(kernel, actor, AMMO_ID, 6u), BREAK_KERNEL_OVERLOAD);
    ASSERT_EQ(break_kernel_inventory_count(kernel, actor, AMMO_ID, &count), BREAK_KERNEL_OK);
    ASSERT_EQ(count, 25u);
    ASSERT_EQ(break_kernel_inventory_add(kernel, actor, AMMO_ID, UINT32_MAX), BREAK_KERNEL_OVERLOAD);
    ASSERT_EQ(break_kernel_inventory_count(kernel, actor, AMMO_ID, &count), BREAK_KERNEL_OK);
    ASSERT_EQ(count, 25u);
    ASSERT_EQ(break_kernel_inventory_add(kernel, actor, MEDKIT_ID, 3u), BREAK_KERNEL_OVERLOAD);
    ASSERT_EQ(break_kernel_inventory_count(kernel, actor, MEDKIT_ID, &count), BREAK_KERNEL_OK);
    ASSERT_EQ(count, 0u);
    destroy_kernel(kernel, world);
}

TEST(transfer_updates_both_inventories_and_rolls_back_capacity_failure) {
    World *world = make_world();
    BreakKernel *kernel = make_kernel(world);
    ASSERT_NOT_NULL(kernel);
    u32 class_id = register_pawn(kernel);
    ASSERT_NEQ(class_id, 0u);
    Entity from = spawn_actor(kernel, class_id);
    Entity to = spawn_actor(kernel, class_id);
    ASSERT_TRUE(entity_valid(from));
    ASSERT_TRUE(entity_valid(to));
    ASSERT_TRUE(define_standard_items(kernel));
    ASSERT_EQ(break_kernel_inventory_add(kernel, from, AMMO_ID, 25u), BREAK_KERNEL_OK);
    ASSERT_EQ(break_kernel_inventory_transfer(kernel, from, to, AMMO_ID, 10u), BREAK_KERNEL_OK);
    u32 from_count = 0;
    u32 to_count = 0;
    ASSERT_EQ(break_kernel_inventory_count(kernel, from, AMMO_ID, &from_count), BREAK_KERNEL_OK);
    ASSERT_EQ(from_count, 15u);
    ASSERT_EQ(break_kernel_inventory_count(kernel, to, AMMO_ID, &to_count), BREAK_KERNEL_OK);
    ASSERT_EQ(to_count, 10u);
    ASSERT_EQ(break_kernel_inventory_add(kernel, from, AMMO_ID, 15u), BREAK_KERNEL_OK);
    ASSERT_EQ(break_kernel_inventory_transfer(kernel, from, to, AMMO_ID, 21u), BREAK_KERNEL_OVERLOAD);
    ASSERT_EQ(break_kernel_inventory_count(kernel, from, AMMO_ID, &from_count), BREAK_KERNEL_OK);
    ASSERT_EQ(from_count, 30u);
    ASSERT_EQ(break_kernel_inventory_count(kernel, to, AMMO_ID, &to_count), BREAK_KERNEL_OK);
    ASSERT_EQ(to_count, 10u);
    destroy_kernel(kernel, world);
}

TEST(transfer_rejects_invalid_requests_and_insufficient_source_atomically) {
    World *world = make_world();
    BreakKernel *kernel = make_kernel(world);
    ASSERT_NOT_NULL(kernel);
    u32 class_id = register_pawn(kernel);
    ASSERT_NEQ(class_id, 0u);
    Entity from = spawn_actor(kernel, class_id);
    Entity to = spawn_actor(kernel, class_id);
    ASSERT_TRUE(entity_valid(from));
    ASSERT_TRUE(entity_valid(to));
    ASSERT_TRUE(define_standard_items(kernel));
    ASSERT_EQ(break_kernel_inventory_add(kernel, from, MEDKIT_ID, 1u), BREAK_KERNEL_OK);
    ASSERT_EQ(break_kernel_inventory_transfer(kernel, from, from, MEDKIT_ID, 1u), BREAK_KERNEL_INVALID);
    ASSERT_EQ(break_kernel_inventory_transfer(kernel, from, to, MEDKIT_ID, 0u), BREAK_KERNEL_INVALID);
    ASSERT_EQ(break_kernel_inventory_transfer(kernel, from, to, MEDKIT_ID, 2u), BREAK_KERNEL_OVERLOAD);
    u32 count = 99u;
    ASSERT_EQ(break_kernel_inventory_count(kernel, from, MEDKIT_ID, &count), BREAK_KERNEL_OK);
    ASSERT_EQ(count, 1u);
    ASSERT_EQ(break_kernel_inventory_count(kernel, to, MEDKIT_ID, &count), BREAK_KERNEL_OK);
    ASSERT_EQ(count, 0u);
    destroy_kernel(kernel, world);
}

TEST(despawn_invalidates_old_handle_and_clears_reused_slot) {
    World *world = make_world();
    BreakKernel *kernel = make_kernel(world);
    ASSERT_NOT_NULL(kernel);
    u32 class_id = register_pawn(kernel);
    ASSERT_NEQ(class_id, 0u);
    Entity old = spawn_actor(kernel, class_id);
    Entity other = spawn_actor(kernel, class_id);
    ASSERT_TRUE(entity_valid(old));
    ASSERT_TRUE(entity_valid(other));
    ASSERT_TRUE(define_standard_items(kernel));
    ASSERT_EQ(break_kernel_inventory_add(kernel, old, AMMO_ID, 25u), BREAK_KERNEL_OK);
    ASSERT_EQ(break_kernel_despawn(kernel, old), BREAK_KERNEL_OK);
    ASSERT_EQ(break_kernel_inventory_add(kernel, old, AMMO_ID, 1u), BREAK_KERNEL_STALE);
    u32 count = 88u;
    ASSERT_EQ(break_kernel_inventory_count(kernel, old, AMMO_ID, &count), BREAK_KERNEL_STALE);
    ASSERT_EQ(count, 88u);
    ASSERT_EQ(break_kernel_inventory_transfer(kernel, old, other, AMMO_ID, 1u), BREAK_KERNEL_STALE);
    ASSERT_EQ(break_kernel_inventory_transfer(kernel, other, old, AMMO_ID, 1u), BREAK_KERNEL_STALE);
    Entity replacement = spawn_actor(kernel, class_id);
    ASSERT_TRUE(entity_valid(replacement));
    ASSERT_EQ(break_kernel_inventory_count(kernel, replacement, AMMO_ID, &count), BREAK_KERNEL_OK);
    ASSERT_EQ(count, 0u);
    ASSERT_EQ(break_kernel_inventory_count(kernel, replacement, MEDKIT_ID, &count), BREAK_KERNEL_OK);
    ASSERT_EQ(count, 0u);
    destroy_kernel(kernel, world);
}

TEST_MAIN_BEGIN()
    RUN_TEST(item_definition_enforces_exact_bounds);
    RUN_TEST(add_validates_input_and_preserves_count_on_overload);
    RUN_TEST(transfer_updates_both_inventories_and_rolls_back_capacity_failure);
    RUN_TEST(transfer_rejects_invalid_requests_and_insufficient_source_atomically);
    RUN_TEST(despawn_invalidates_old_handle_and_clears_reused_slot);
TEST_MAIN_END()
