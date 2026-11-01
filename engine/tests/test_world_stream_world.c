#include "test_framework.h"
#include <renderer/world_stream_world.h>

TEST(stream_commit_spawns_and_removes_tile_entities) {
    World *world = world_create();
    ASSERT_NOT_NULL(world);
    Entity slots[4];
    for (u32 i = 0; i < 4u; i++) slots[i] = ENTITY_NULL;

    StreamWant load;
    load.tile_x = 1;
    load.tile_z = 0;
    load.resident = true;
    u32 rejected = 0;
    u32 applied = world_stream_commit(world, &load, 1, slots, 2, 2, &rejected);
    ASSERT_EQ(applied, 1u);
    ASSERT_EQ(rejected, 0u);
    ASSERT_TRUE(entity_valid(slots[1]));
    ASSERT_TRUE(world_entity_exists(world, slots[1]));
    ASSERT_EQ(world->entity_count, 2u);
    Entity first = slots[1];

    applied = world_stream_commit(world, &load, 1, slots, 2, 2, &rejected);
    ASSERT_EQ(applied, 1u);
    ASSERT_EQ(slots[1].index, first.index);
    ASSERT_EQ(slots[1].generation, first.generation);
    ASSERT_EQ(world->entity_count, 2u);

    StreamWant bad;
    bad.tile_x = 9;
    bad.tile_z = 0;
    bad.resident = true;
    applied = world_stream_commit(world, &bad, 1, slots, 2, 2, &rejected);
    ASSERT_EQ(applied, 0u);
    ASSERT_EQ(rejected, 1u);
    ASSERT_EQ(slots[1].generation, first.generation);

    StreamWant unload;
    unload.tile_x = 1;
    unload.tile_z = 0;
    unload.resident = false;
    applied = world_stream_commit(world, &unload, 1, slots, 2, 2, &rejected);
    ASSERT_EQ(applied, 1u);
    ASSERT_EQ(rejected, 0u);
    ASSERT_FALSE(entity_valid(slots[1]));
    ASSERT_FALSE(world_entity_exists(world, first));

    ASSERT_EQ(world_stream_commit(NULL, &load, 1, slots, 2, 2, &rejected), 0u);
    world_destroy(world);
}

TEST_MAIN_BEGIN()
    RUN_TEST(stream_commit_spawns_and_removes_tile_entities);
TEST_MAIN_END()
