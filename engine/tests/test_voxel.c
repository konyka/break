#include "test_framework.h"
#include <renderer/voxel.h>
#include <stdlib.h>

TEST(voxel_exposes_outer_faces_only) {
    u8 one = 1;
    VoxelVertex verts[24];
    u32 dropped = 99;
    u32 n = voxel_build_faces(&one, 1, 1, 1, 1.0f, verts, 24, &dropped);
    ASSERT_EQ(n, 24u);
    ASSERT_EQ(dropped, 0u);
    bool saw_up = false;
    for (u32 i = 0; i < n; i += 4) {
        if (verts[i].normal.e[1] > 0.9f) {
            saw_up = true;
            ASSERT_FLOAT_EQ(verts[i].position.e[1], 1.0f, 1e-5);
        }
    }
    ASSERT_TRUE(saw_up);

    u8 pair[2] = {1, 1};
    VoxelVertex *many = (VoxelVertex *)calloc(64, sizeof(VoxelVertex));
    ASSERT_NOT_NULL(many);
    n = voxel_build_faces(pair, 2, 1, 1, 1.0f, many, 64, &dropped);
    ASSERT_EQ(n, 40u);
    free(many);

    u8 empty = 0;
    n = voxel_build_faces(&empty, 1, 1, 1, 1.0f, verts, 4, &dropped);
    ASSERT_EQ(n, 0u);

    n = voxel_build_faces(&one, 1, 1, 1, 1.0f, verts, 4, &dropped);
    ASSERT_EQ(n, 4u);
    ASSERT_EQ(dropped, 5u);
}

TEST_MAIN_BEGIN()
    RUN_TEST(voxel_exposes_outer_faces_only);
TEST_MAIN_END()
