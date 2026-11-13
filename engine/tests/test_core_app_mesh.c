#include "test_framework.h"

#include "../apps/core_app/core_app_mesh.h"

#include <string.h>

/* Two scene vertices in the 32-byte contract: pos3 + normal3 + uv2. */
static void scene_vertices(u8 out[64]) {
    const f32 first[8] = {1.0f, 2.0f, 3.0f, 0.0f, 1.0f, 0.0f, 0.25f, 0.75f};
    const f32 second[8] = {-4.0f, 5.5f, -6.5f, 0.0f, 0.0f, 1.0f, 0.5f, 0.125f};
    memcpy(out, first, sizeof(first));
    memcpy(out + 32u, second, sizeof(second));
}

TEST(mesh_convert_reads_the_32_byte_scene_layout) {
    u8 source[64];
    MeshVertex out[2];
    scene_vertices(source);
    memset(out, 0, sizeof(out));
    ASSERT_TRUE(core_app_mesh_convert_vertices(source, 2u, out, 2u));
    /* Field order is the contract: a flat memcpy over a 32-byte source would
     * land the second vertex's position inside the first vertex's UVs. */
    ASSERT_EQ(out[0].px, 1.0f);
    ASSERT_EQ(out[0].py, 2.0f);
    ASSERT_EQ(out[0].pz, 3.0f);
    ASSERT_EQ(out[0].ny, 1.0f);
    ASSERT_EQ(out[0].u, 0.25f);
    ASSERT_EQ(out[0].v, 0.75f);
    ASSERT_EQ(out[1].px, -4.0f);
    ASSERT_EQ(out[1].py, 5.5f);
    ASSERT_EQ(out[1].pz, -6.5f);
    ASSERT_EQ(out[1].nz, 1.0f);
    ASSERT_EQ(out[1].u, 0.5f);
    ASSERT_EQ(out[1].v, 0.125f);
    ASSERT_EQ(out[0].material, 0u);
    ASSERT_EQ(out[1].material, 0u);
}

TEST(mesh_convert_rejects_capacity_overflow_without_writing) {
    u8 source[64];
    MeshVertex out[2];
    MeshVertex before[2];
    scene_vertices(source);
    memset(out, 0, sizeof(out));
    memset(before, 0, sizeof(before));
    ASSERT_FALSE(core_app_mesh_convert_vertices(source, 3u, out, 2u));
    ASSERT_EQ(memcmp(out, before, sizeof(out)), 0);
}

TEST(mesh_convert_rejects_null_source_for_nonzero_count) {
    MeshVertex out[1];
    ASSERT_FALSE(core_app_mesh_convert_vertices(NULL, 1u, out, 1u));
    ASSERT_TRUE(core_app_mesh_convert_vertices(NULL, 0u, out, 1u));
}

TEST_MAIN_BEGIN()
    RUN_TEST(mesh_convert_reads_the_32_byte_scene_layout);
    RUN_TEST(mesh_convert_rejects_capacity_overflow_without_writing);
    RUN_TEST(mesh_convert_rejects_null_source_for_nonzero_count);
TEST_MAIN_END()
