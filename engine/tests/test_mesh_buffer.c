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
    ASSERT_EQ(upload.size, 4u * sizeof(MeshVertex));
    ASSERT_TRUE(upload.initial_data == buf.verts);
    ASSERT_TRUE(rhi_buffer_desc_validate(&upload));

    MeshDrawDesc draw;
    memset(&draw, 0, sizeof(draw));
    ASSERT_TRUE(mesh_buffer_draw_desc(&buf, &draw));
    ASSERT_EQ(draw.vertex_count, 4u);
    ASSERT_EQ(draw.stride, (u32)sizeof(MeshVertex));
    ASSERT_EQ(draw.index_count, 6u);
    ASSERT_EQ(buf.indices[0], 0u);
    ASSERT_EQ(buf.indices[1], 1u);
    ASSERT_EQ(buf.indices[2], 2u);
    ASSERT_EQ(buf.indices[5], 3u);
    RHIBufferDesc indices;
    memset(&indices, 0, sizeof(indices));
    ASSERT_TRUE(mesh_buffer_index_desc(&buf, &indices));
    ASSERT_EQ(indices.usage, RHI_BUFFER_USAGE_INDEX);
    ASSERT_EQ(indices.size, 6u * sizeof(u32));
    ASSERT_TRUE(indices.initial_data == buf.indices);
    ASSERT_TRUE(rhi_buffer_desc_validate(&indices));

    VoxelVertex block;
    block.position = vec3(1.0f, 2.0f, 3.0f);
    block.normal = vec3(0.0f, 0.0f, 1.0f);
    ASSERT_TRUE(mesh_buffer_from_voxels(&buf, &block, 1, &dropped));
    ASSERT_EQ(buf.count, 1u);
    ASSERT_EQ(buf.index_count, 0u);
    ASSERT_FALSE(mesh_buffer_index_desc(&buf, &indices));
    ASSERT_TRUE(mesh_buffer_upload_desc(&buf, &upload));
    ASSERT_EQ(upload.size, sizeof(MeshVertex));
    ASSERT_TRUE(rhi_buffer_desc_validate(&upload));

    VoxelVertex face[4];
    for (u32 i = 0; i < 4u; i++) {
        face[i].position = vec3((f32)i, 0.0f, 0.0f);
        face[i].normal = vec3(0.0f, 1.0f, 0.0f);
    }
    ASSERT_TRUE(mesh_buffer_from_voxels(&buf, face, 4, &dropped));
    ASSERT_EQ(buf.count, 4u);
    ASSERT_EQ(buf.index_count, 6u);
    ASSERT_EQ(buf.indices[5], 3u);

    Vec3 ribbon[2];
    ribbon[0] = vec3(-0.5f, 1.0f, 0.0f);
    ribbon[1] = vec3(0.5f, 1.0f, 0.0f);
    ASSERT_TRUE(mesh_buffer_from_road(&buf, ribbon, 2, &dropped));
    ASSERT_EQ(buf.count, 2u);
    ASSERT_EQ(buf.index_count, 0u);
    ASSERT_TRUE(mesh_buffer_draw_desc(&buf, &draw));
    ASSERT_EQ(draw.vertex_count, 2u);
    ASSERT_EQ(draw.index_count, 0u);

    Vec3 strip[4];
    strip[0] = vec3(0.0f, 0.0f, 0.0f);
    strip[1] = vec3(1.0f, 0.0f, 0.0f);
    strip[2] = vec3(0.0f, 0.0f, 1.0f);
    strip[3] = vec3(1.0f, 0.0f, 1.0f);
    ASSERT_TRUE(mesh_buffer_from_road(&buf, strip, 4, &dropped));
    ASSERT_EQ(buf.count, 4u);
    ASSERT_EQ(buf.index_count, 6u);
    ASSERT_EQ(buf.indices[2], 3u);
    ASSERT_EQ(buf.indices[5], 2u);
    ASSERT_TRUE(mesh_buffer_index_desc(&buf, &indices));
    ASSERT_TRUE(rhi_buffer_desc_validate(&indices));

    memset(&buf, 0, sizeof(buf));
    ASSERT_FALSE(mesh_buffer_upload_desc(&buf, &upload));
    ASSERT_FALSE(mesh_buffer_index_desc(&buf, &indices));
    ASSERT_FALSE(mesh_buffer_draw_desc(&buf, &draw));
    ASSERT_FALSE(mesh_buffer_from_decals(NULL, &decal, 1, &dropped));
}

TEST(mesh_buffer_migrates_legacy_vertices_with_planar_uvs) {
    MeshStageVertex legacy[4];
    memset(legacy, 0, sizeof(legacy));
    legacy[0].px = -1.0f;
    legacy[0].pz = 2.0f;
    legacy[0].ny = 1.0f;
    legacy[0].material = 7u;
    legacy[1].px = 1.0f;
    legacy[1].py = 3.0f;
    legacy[1].nz = 1.0f;
    legacy[2].px = 1.0f;
    legacy[2].pz = -2.0f;
    legacy[2].ny = 1.0f;
    legacy[3].px = -1.0f;
    legacy[3].pz = -2.0f;
    legacy[3].ny = 1.0f;

    MeshBuffer buf;
    u32 dropped = 99u;
    ASSERT_TRUE(mesh_buffer_from_legacy(&buf, legacy, 4u, &dropped));
    ASSERT_EQ(dropped, 0u);
    ASSERT_EQ(sizeof(MeshStageVertex), 28u);
    ASSERT_EQ(sizeof(MeshVertex), 36u);
    ASSERT_EQ(buf.verts[0].material, 7u);
    ASSERT_FLOAT_EQ(buf.verts[0].u, -1.0f, 1e-6);
    ASSERT_FLOAT_EQ(buf.verts[0].v, 2.0f, 1e-6);
    ASSERT_FLOAT_EQ(buf.verts[1].u, 1.0f, 1e-6);
    ASSERT_FLOAT_EQ(buf.verts[1].v, 3.0f, 1e-6);

    MeshDrawDesc draw;
    ASSERT_TRUE(mesh_buffer_draw_desc(&buf, &draw));
    ASSERT_EQ(draw.stride, 36u);
    ASSERT_EQ(draw.index_count, 6u);
    ASSERT_EQ(buf.indices[5], 3u);
}

TEST_MAIN_BEGIN()
    RUN_TEST(mesh_buffer_describes_a_vertex_upload_and_draw);
    RUN_TEST(mesh_buffer_migrates_legacy_vertices_with_planar_uvs);
TEST_MAIN_END()
