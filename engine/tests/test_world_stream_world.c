#include "test_framework.h"
#include <renderer/world_stream_world.h>
#include <stdio.h>
#include <sys/stat.h>

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

TEST(stream_commit_vfs_copies_tile_bytes_onto_the_entity) {
    char dir_path[512];
    test_tmp(dir_path, sizeof(dir_path), "stream-tile-test");
    char file_path[560];
    int file_n = snprintf(file_path, sizeof(file_path), "%s/tile_1_0.bin", dir_path);
    ASSERT_TRUE(file_n > 0 && (usize)file_n < sizeof(file_path));
    remove(file_path);
    TEST_RMDIR(dir_path);
    ASSERT_EQ(TEST_MKDIR(dir_path), 0);
    FILE *out = fopen(file_path, "wb");
    ASSERT_NOT_NULL(out);
    u8 payload[4] = {1, 2, 3, 4};
    ASSERT_EQ(fwrite(payload, 1, 4, out), 4u);
    fclose(out);

    VFS *vfs = vfs_create();
    ASSERT_NOT_NULL(vfs);
    ASSERT_TRUE(vfs_mount_dir(vfs, dir_path));
    World *world = world_create();
    ASSERT_NOT_NULL(world);
    Entity slots[4];
    for (u32 i = 0; i < 4u; i++) slots[i] = ENTITY_NULL;

    StreamWant load;
    load.tile_x = 1;
    load.tile_z = 0;
    load.resident = true;
    u32 rejected = 0;
    u32 applied = world_stream_commit_vfs(world, vfs, &load, 1, slots, 2, 2, &rejected);
    ASSERT_EQ(applied, 1u);
    ASSERT_EQ(rejected, 0u);
    StreamTileData *tile = (StreamTileData *)world_get_component(world, slots[1], STREAM_TILE_COMPONENT);
    ASSERT_NOT_NULL(tile);
    ASSERT_EQ(tile->x, 1u);
    ASSERT_EQ(tile->z, 0u);
    ASSERT_EQ(tile->size, 4u);
    ASSERT_EQ(tile->bytes[0], 1u);
    ASSERT_EQ(tile->bytes[3], 4u);
    Entity first = slots[1];
    u32 count = world->entity_count;

    applied = world_stream_commit_vfs(world, vfs, &load, 1, slots, 2, 2, &rejected);
    ASSERT_EQ(applied, 1u);
    ASSERT_EQ(slots[1].generation, first.generation);
    ASSERT_EQ(world->entity_count, count);

    StreamWant missing;
    missing.tile_x = 0;
    missing.tile_z = 1;
    missing.resident = true;
    applied = world_stream_commit_vfs(world, vfs, &missing, 1, slots, 2, 2, &rejected);
    ASSERT_EQ(applied, 0u);
    ASSERT_EQ(rejected, 1u);
    ASSERT_FALSE(entity_valid(slots[2]));

    StreamWant unload;
    unload.tile_x = 1;
    unload.tile_z = 0;
    unload.resident = false;
    applied = world_stream_commit_vfs(world, vfs, &unload, 1, slots, 2, 2, &rejected);
    ASSERT_EQ(applied, 1u);
    ASSERT_FALSE(world_entity_exists(world, first));
    ASSERT_EQ(world_stream_commit_vfs(world, NULL, &load, 1, slots, 2, 2, &rejected), 0u);

    world_destroy(world);
    vfs_destroy(vfs);
    remove(file_path);
    TEST_RMDIR(dir_path);
}

TEST_MAIN_BEGIN()
    RUN_TEST(stream_commit_spawns_and_removes_tile_entities);
    RUN_TEST(stream_commit_vfs_copies_tile_bytes_onto_the_entity);
TEST_MAIN_END()
