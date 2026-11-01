#include "test_framework.h"
#include <renderer/mesh_buffer.h>

TEST(mesh_buffer_describes_a_vertex_upload_and_draw) {
    Decal decal;
    memset(&decal, 0, sizeof(decal));
    decal.position = vec3(0.0f, 3.0f, 0.0f);
    decal.normal = vec3(0.0f, 1.0f, 0.0f);
    decal.size = 2.0f;
    decal.material = 9;
    MeshBuffer buf;
    u32 dropped = 0;
    ASSERT_TRUE(mesh_buffer_from_decals(&buf, &decal, 1, &dropped));
    ASSERT_EQ(dropped, 0u);
    ASSERT_EQ(buf.count, 4u);
    ASSERT_FLOAT_EQ(buf.verts[2].px, 1.0f, 1e-4);

    RHIBufferDesc upload;
    memset(&upload, 0, sizeof(upload));
    ASSERT_TRUE(mesh_buffer_upload_desc(&buf, &upload));
    ASSERT_EQ(upload.usage, RHI_BUFFER_USAGE_VERTEX);
    ASSERT_EQ(upload.size, 4u * sizeof(MeshStageVertex));
    ASSERT_TRUE(upload.initial_data == buf.verts);
    ASSERT_TRUE(rhi_buffer_desc_validate(&upload));

    MeshDrawDesc draw;
    memset(&draw, 0, sizeof(draw));
    ASSERT_TRUE(mesh_buffer_draw_desc(&buf, &draw));
    ASSERT_EQ(draw.vertex_count, 4u);
    ASSERT_EQ(draw.stride, (u32)sizeof(MeshStageVertex));

    VoxelVertex block;
    block.position = vec3(1.0f, 2.0f, 3.0f);
    block.normal = vec3(0.0f, 0.0f, 1.0f);
    ASSERT_TRUE(mesh_buffer_from_voxels(&buf, &block, 1, &dropped));
    ASSERT_EQ(buf.count, 1u);
    ASSERT_TRUE(mesh_buffer_upload_desc(&buf, &upload));
    ASSERT_EQ(upload.size, sizeof(MeshStageVertex));
    ASSERT_TRUE(rhi_buffer_desc_validate(&upload));

    Vec3 ribbon[2];
    ribbon[0] = vec3(-0.5f, 1.0f, 0.0f);
    ribbon[1] = vec3(0.5f, 1.0f, 0.0f);
    ASSERT_TRUE(mesh_buffer_from_road(&buf, ribbon, 2, &dropped));
    ASSERT_EQ(buf.count, 2u);
    ASSERT_TRUE(mesh_buffer_draw_desc(&buf, &draw));
    ASSERT_EQ(draw.vertex_count, 2u);

    memset(&buf, 0, sizeof(buf));
    ASSERT_FALSE(mesh_buffer_upload_desc(&buf, &upload));
    ASSERT_FALSE(mesh_buffer_draw_desc(&buf, &draw));
    ASSERT_FALSE(mesh_buffer_from_decals(NULL, &decal, 1, &dropped));
}

TEST_MAIN_BEGIN()
    RUN_TEST(mesh_buffer_describes_a_vertex_upload_and_draw);
TEST_MAIN_END()
