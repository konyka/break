#include "test_framework.h"
#include <renderer/mesh_stage.h>
#include <math.h>

TEST(stage_packs_decal_voxel_and_road_bytes) {
    Decal decal;
    memset(&decal, 0, sizeof(decal));
    decal.position = vec3(0.0f, 3.0f, 0.0f);
    decal.normal = vec3(0.0f, 1.0f, 0.0f);
    decal.size = 2.0f;
    decal.material = 9;
    MeshStageVertex verts[8];
    memset(verts, 0, sizeof(verts));
    u32 dropped = 0;
    u32 bytes = decal_stage_quads(&decal, 1, verts, 8, &dropped);
    ASSERT_EQ(bytes, 4u * (u32)sizeof(MeshStageVertex));
    ASSERT_EQ(dropped, 0u);
    ASSERT_EQ(verts[0].material, 9u);
    ASSERT_FLOAT_EQ(verts[0].py, 3.0f, 1e-4);
    ASSERT_FLOAT_EQ(verts[2].px, 1.0f, 1e-4);
    ASSERT_FLOAT_EQ(verts[2].pz, 1.0f, 1e-4);
    ASSERT_FLOAT_EQ(verts[0].px, -1.0f, 1e-4);
    ASSERT_FLOAT_EQ(verts[0].pz, -1.0f, 1e-4);

    bytes = decal_stage_quads(&decal, 1, verts, 3, &dropped);
    ASSERT_EQ(bytes, 0u);
    ASSERT_EQ(dropped, 1u);

    VoxelVertex block;
    block.position = vec3(1.0f, 2.0f, 3.0f);
    block.normal = vec3(0.0f, 0.0f, 1.0f);
    bytes = voxel_stage_vertices(&block, 1, verts, 8, &dropped);
    ASSERT_EQ(bytes, (u32)sizeof(MeshStageVertex));
    ASSERT_FLOAT_EQ(verts[0].px, 1.0f, 1e-4);
    ASSERT_FLOAT_EQ(verts[0].nz, 1.0f, 1e-4);
    ASSERT_EQ(verts[0].material, 0u);

    Vec3 ribbon[2];
    ribbon[0] = vec3(-0.5f, 1.0f, 0.0f);
    ribbon[1] = vec3(0.5f, 1.0f, 0.0f);
    bytes = road_stage_ribbon(ribbon, 2, verts, 8, &dropped);
    ASSERT_EQ(bytes, 2u * (u32)sizeof(MeshStageVertex));
    ASSERT_FLOAT_EQ(verts[0].px, -0.5f, 1e-4);
    ASSERT_FLOAT_EQ(verts[1].px, 0.5f, 1e-4);
    ASSERT_FLOAT_EQ(verts[0].ny, 1.0f, 1e-4);
    bytes = road_stage_ribbon(ribbon, 2, verts, 1, &dropped);
    ASSERT_EQ(bytes, 0u);
    ASSERT_EQ(dropped, 1u);
}

/* A decal on a wall builds its quad in the wall plane: every corner is at
 * the same distance along the normal, half the size from the centre along
 * two perpendicular axes. */
TEST(decal_on_a_wall_stays_in_the_wall_plane) {
    Decal decal;
    memset(&decal, 0, sizeof(decal));
    decal.position = vec3(5.0f, 1.0f, 2.0f);
    decal.normal = vec3(1.0f, 0.0f, 0.0f);
    decal.size = 2.0f;
    MeshStageVertex verts[4];
    u32 dropped = 0;
    ASSERT_EQ(decal_stage_quads(&decal, 1, verts, 4, &dropped), 4u * (u32)sizeof(MeshStageVertex));
    for (u32 i = 0; i < 4u; i++) {
        ASSERT_FLOAT_EQ(verts[i].px, 5.0f, 1e-5);
        ASSERT_FLOAT_EQ(verts[i].nx, 1.0f, 1e-6);
        f32 dy = verts[i].py - 1.0f;
        f32 dz = verts[i].pz - 2.0f;
        ASSERT_FLOAT_EQ(dy < 0 ? -dy : dy, 1.0f, 1e-5);
        ASSERT_FLOAT_EQ(dz < 0 ? -dz : dz, 1.0f, 1e-5);
    }
    /* opposite corners are on opposite sides */
    ASSERT_FLOAT_EQ(verts[0].py + verts[2].py, 2.0f, 1e-5);
    ASSERT_FLOAT_EQ(verts[0].pz + verts[2].pz, 4.0f, 1e-5);
}

/* Invalid decals are dropped and later valid ones still pack in order. */
TEST(decal_stage_drops_bad_decals) {
    Decal in[4];
    memset(in, 0, sizeof(in));
    for (u32 i = 0; i < 4u; i++) {
        in[i].normal = vec3(0, 1, 0);
        in[i].size = 1.0f;
        in[i].material = i;
    }
    in[0].size = 0.0f;
    in[1].position.e[1] = INFINITY;
    in[2].normal.e[0] = NAN;
    MeshStageVertex verts[8];
    u32 dropped = 0;
    ASSERT_EQ(decal_stage_quads(in, 4, verts, 8, &dropped), 4u * (u32)sizeof(MeshStageVertex));
    ASSERT_EQ(dropped, 3u);
    ASSERT_EQ(verts[0].material, 3u);
    ASSERT_EQ(decal_stage_quads(NULL, 1, verts, 8, &dropped), 0u);
    ASSERT_EQ(decal_stage_quads(in, 1, NULL, 8, &dropped), 0u);
}

/* Voxel and road staging truncate at capacity and count the rest; an odd
 * road point count drops the unpaired point. */
TEST(voxel_and_road_staging_truncate_and_count) {
    VoxelVertex block[3];
    for (u32 i = 0; i < 3u; i++) {
        block[i].position = vec3((f32)i, 0, 0);
        block[i].normal = vec3(0, 1, 0);
    }
    MeshStageVertex verts[4];
    u32 dropped = 0;
    ASSERT_EQ(voxel_stage_vertices(block, 3, verts, 2, &dropped), 2u * (u32)sizeof(MeshStageVertex));
    ASSERT_EQ(dropped, 1u);
    ASSERT_FLOAT_EQ(verts[1].px, 1.0f, 1e-6);
    Vec3 ribbon[5] = {vec3(0, 0, 0), vec3(1, 0, 0), vec3(0, 0, 1), vec3(1, 0, 1), vec3(9, 9, 9)};
    ASSERT_EQ(road_stage_ribbon(ribbon, 5, verts, 4, &dropped), 4u * (u32)sizeof(MeshStageVertex));
    ASSERT_EQ(dropped, 1u);
    ASSERT_FLOAT_EQ(verts[3].pz, 1.0f, 1e-6);
    ASSERT_EQ(road_stage_ribbon(ribbon, 5, verts, 3, &dropped), 2u * (u32)sizeof(MeshStageVertex));
    ASSERT_EQ(dropped, 2u);
    ASSERT_EQ(voxel_stage_vertices(NULL, 1, verts, 4, &dropped), 0u);
    ASSERT_EQ(road_stage_ribbon(NULL, 2, verts, 4, &dropped), 0u);
}

/* Migration picks the UV plane from the dominant normal axis: floors map
 * (x, z), X-facing walls (z, y), Z-facing walls (x, y). It refuses outputs
 * that are too small. */
TEST(migrate_projects_uvs_by_dominant_axis) {
    MeshStageVertex in[3];
    memset(in, 0, sizeof(in));
    in[0].px = 1; in[0].py = 2; in[0].pz = 3; in[0].ny = 1;
    in[1].px = 1; in[1].py = 2; in[1].pz = 3; in[1].nx = -1;
    in[2].px = 1; in[2].py = 2; in[2].pz = 3; in[2].nz = 1; in[2].material = 5;
    MeshVertex out[3];
    ASSERT_TRUE(mesh_vertices_migrate(in, 3, out, 3));
    ASSERT_FLOAT_EQ(out[0].u, 1.0f, 0.0f);
    ASSERT_FLOAT_EQ(out[0].v, 3.0f, 0.0f);
    ASSERT_FLOAT_EQ(out[1].u, 3.0f, 0.0f);
    ASSERT_FLOAT_EQ(out[1].v, 2.0f, 0.0f);
    ASSERT_FLOAT_EQ(out[2].u, 1.0f, 0.0f);
    ASSERT_FLOAT_EQ(out[2].v, 2.0f, 0.0f);
    ASSERT_EQ(out[2].material, 5u);
    ASSERT_FALSE(mesh_vertices_migrate(in, 3, out, 2));
    ASSERT_FALSE(mesh_vertices_migrate(NULL, 1, out, 3));
    ASSERT_TRUE(mesh_vertices_migrate(NULL, 0, NULL, 0));
}

TEST_MAIN_BEGIN()
    RUN_TEST(stage_packs_decal_voxel_and_road_bytes);
    RUN_TEST(decal_on_a_wall_stays_in_the_wall_plane);
    RUN_TEST(decal_stage_drops_bad_decals);
    RUN_TEST(voxel_and_road_staging_truncate_and_count);
    RUN_TEST(migrate_projects_uvs_by_dominant_axis);
TEST_MAIN_END()
