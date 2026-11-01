#include "test_framework.h"
#include <renderer/mesh_stage.h>

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

TEST_MAIN_BEGIN()
    RUN_TEST(stage_packs_decal_voxel_and_road_bytes);
TEST_MAIN_END()
