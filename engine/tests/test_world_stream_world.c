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

TEST(stream_commit_vfs_loads_a_versioned_mesh) {
    char root[512];
    char ok_path[560];
    char bad_path[560];
    char short_path[560];
    char over_path[560];
    ASSERT_NOT_NULL(test_tmp(root, sizeof(root), "break-stream-tile-test"));
    int n = snprintf(ok_path, sizeof(ok_path), "%s/tile_1_0.bin", root);
    ASSERT_TRUE(n > 0 && (usize)n < sizeof(ok_path));
    n = snprintf(bad_path, sizeof(bad_path), "%s/tile_0_0.bin", root);
    ASSERT_TRUE(n > 0 && (usize)n < sizeof(bad_path));
    n = snprintf(short_path, sizeof(short_path), "%s/tile_0_1.bin", root);
    ASSERT_TRUE(n > 0 && (usize)n < sizeof(short_path));
    n = snprintf(over_path, sizeof(over_path), "%s/tile_1_1.bin", root);
    ASSERT_TRUE(n > 0 && (usize)n < sizeof(over_path));
    remove(ok_path);
    remove(bad_path);
    remove(short_path);
    remove(over_path);
    TEST_RMDIR(root);
    ASSERT_EQ(TEST_MKDIR(root), 0);

    MeshStageVertex vert;
    memset(&vert, 0, sizeof(vert));
    vert.px = 4.0f;
    vert.py = 5.0f;
    vert.pz = 6.0f;
    vert.ny = 1.0f;
    vert.material = 3;
    FILE *out = fopen(ok_path, "wb");
    ASSERT_NOT_NULL(out);
    u32 magic = STREAM_TILE_MAGIC;
    u32 version = STREAM_TILE_VERSION;
    u32 vcount = 1;
    ASSERT_EQ(fwrite(&magic, 4, 1, out), 1u);
    ASSERT_EQ(fwrite(&version, 4, 1, out), 1u);
    ASSERT_EQ(fwrite(&vcount, 4, 1, out), 1u);
    ASSERT_EQ(fwrite(&vert, sizeof(vert), 1, out), 1u);
    fclose(out);

    out = fopen(bad_path, "wb");
    ASSERT_NOT_NULL(out);
    u32 bad_magic = 1;
    ASSERT_EQ(fwrite(&bad_magic, 4, 1, out), 1u);
    ASSERT_EQ(fwrite(&version, 4, 1, out), 1u);
    ASSERT_EQ(fwrite(&vcount, 4, 1, out), 1u);
    ASSERT_EQ(fwrite(&vert, sizeof(vert), 1, out), 1u);
    fclose(out);

    out = fopen(short_path, "wb");
    ASSERT_NOT_NULL(out);
    ASSERT_EQ(fwrite(&magic, 4, 1, out), 1u);
    ASSERT_EQ(fwrite(&version, 4, 1, out), 1u);
    ASSERT_EQ(fwrite(&vcount, 4, 1, out), 1u);
    fclose(out);

    out = fopen(over_path, "wb");
    ASSERT_NOT_NULL(out);
    u32 too_many = STREAM_TILE_MAX_VERTS + 1u;
    ASSERT_EQ(fwrite(&magic, 4, 1, out), 1u);
    ASSERT_EQ(fwrite(&version, 4, 1, out), 1u);
    ASSERT_EQ(fwrite(&too_many, 4, 1, out), 1u);
    fclose(out);

    VFS *vfs = vfs_create();
    ASSERT_NOT_NULL(vfs);
    ASSERT_TRUE(vfs_mount_dir(vfs, root));
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
    ASSERT_EQ(tile->vertex_count, 1u);
    ASSERT_FLOAT_EQ(tile->verts[0].px, 4.0f, 1e-4);
    ASSERT_EQ(tile->verts[0].material, 3u);
    Entity first = slots[1];
    u32 count = world->entity_count;

    applied = world_stream_commit_vfs(world, vfs, &load, 1, slots, 2, 2, &rejected);
    ASSERT_EQ(applied, 1u);
    ASSERT_EQ(slots[1].generation, first.generation);
    ASSERT_EQ(world->entity_count, count);

    StreamWant bad;
    bad.tile_x = 0;
    bad.tile_z = 0;
    bad.resident = true;
    applied = world_stream_commit_vfs(world, vfs, &bad, 1, slots, 2, 2, &rejected);
    ASSERT_EQ(applied, 0u);
    ASSERT_EQ(rejected, 1u);
    ASSERT_FALSE(entity_valid(slots[0]));

    StreamWant trunc;
    trunc.tile_x = 0;
    trunc.tile_z = 1;
    trunc.resident = true;
    applied = world_stream_commit_vfs(world, vfs, &trunc, 1, slots, 2, 2, &rejected);
    ASSERT_EQ(applied, 0u);
    ASSERT_EQ(rejected, 1u);
    ASSERT_FALSE(entity_valid(slots[2]));

    StreamWant over;
    over.tile_x = 1;
    over.tile_z = 1;
    over.resident = true;
    applied = world_stream_commit_vfs(world, vfs, &over, 1, slots, 2, 2, &rejected);
    ASSERT_EQ(applied, 0u);
    ASSERT_EQ(rejected, 1u);
    ASSERT_FALSE(entity_valid(slots[3]));

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
    remove(ok_path);
    remove(bad_path);
    remove(short_path);
    remove(over_path);
    TEST_RMDIR(root);
}

TEST_MAIN_BEGIN()
    RUN_TEST(stream_commit_spawns_and_removes_tile_entities);
    RUN_TEST(stream_commit_vfs_loads_a_versioned_mesh);
TEST_MAIN_END()
