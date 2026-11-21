#include "test_framework.h"
#include <renderer/voxel.h>
#include <stdlib.h>
#include <math.h>

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

static Vec3 cross3(Vec3 a, Vec3 b) {
    return vec3(a.e[1] * b.e[2] - a.e[2] * b.e[1], a.e[2] * b.e[0] - a.e[0] * b.e[2],
                a.e[0] * b.e[1] - a.e[1] * b.e[0]);
}

/* Every quad winds counter-clockwise seen from outside: the cross product
 * of its first two edges points along the face normal, and all four
 * corners lie on the face plane. */
TEST(voxel_quads_wind_outward_and_lie_on_the_face) {
    u8 one = 1;
    VoxelVertex verts[24];
    u32 dropped = 0;
    ASSERT_EQ(voxel_build_faces(&one, 1, 1, 1, 2.0f, verts, 24, &dropped), 24u);
    u32 seen = 0;
    for (u32 q = 0; q < 6u; q++) {
        const VoxelVertex *v = &verts[q * 4u];
        Vec3 n = v[0].normal;
        Vec3 c = cross3(vec3_sub(v[1].position, v[0].position), vec3_sub(v[2].position, v[1].position));
        ASSERT_TRUE(vec3_dot(c, n) > 0.0f);
        f32 plane = vec3_dot(v[0].position, n);
        for (u32 k = 1; k < 4u; k++) {
            ASSERT_FLOAT_EQ(vec3_dot(v[k].position, n), plane, 1e-5);
            ASSERT_EQ(memcmp(&v[k].normal, &n, sizeof(n)), 0);
        }
        /* outward faces sit on the far side of the 2-unit cube */
        ASSERT_FLOAT_EQ(plane, (n.e[0] + n.e[1] + n.e[2]) > 0.0f ? 2.0f : 0.0f, 1e-5);
        for (u32 axis = 0; axis < 3u; axis++) {
            if (n.e[axis] != 0.0f) seen |= 1u << (axis * 2u + (n.e[axis] > 0.0f ? 1u : 0u));
        }
    }
    ASSERT_EQ(seen, 0x3fu);
}

/* A 2x2x2 solid block exposes only its 24 outer faces; a hollow centre in a
 * 3x3x3 block adds 6 inner faces. */
TEST(voxel_hides_faces_between_solid_neighbours) {
    u8 cube[8];
    memset(cube, 1, sizeof(cube));
    VoxelVertex *verts = (VoxelVertex *)calloc(4096, sizeof(VoxelVertex));
    ASSERT_NOT_NULL(verts);
    u32 dropped = 0;
    ASSERT_EQ(voxel_build_faces(cube, 2, 2, 2, 1.0f, verts, 4096, &dropped), 24u * 4u);
    u8 shell[27];
    memset(shell, 1, sizeof(shell));
    shell[13] = 0;
    ASSERT_EQ(voxel_build_faces(shell, 3, 3, 3, 1.0f, verts, 4096, &dropped), (54u + 6u) * 4u);
    ASSERT_EQ(dropped, 0u);
    /* any non-zero value counts as solid, for the block and its neighbours */
    shell[13] = 200;
    ASSERT_EQ(voxel_build_faces(shell, 3, 3, 3, 1.0f, verts, 4096, &dropped), 54u * 4u);
    u8 kinds[2] = {7, 255};
    ASSERT_EQ(voxel_build_faces(kinds, 2, 1, 1, 1.0f, verts, 4096, &dropped), 40u);
    free(verts);
}

/* Bad sizes, a non-positive cell, oversized grids and NULL pointers build
 * nothing; a NULL drop counter is allowed. */
TEST(voxel_rejects_bad_grids) {
    u8 one = 1;
    VoxelVertex verts[24];
    u32 dropped = 9;
    ASSERT_EQ(voxel_build_faces(&one, 0, 1, 1, 1.0f, verts, 24, &dropped), 0u);
    ASSERT_EQ(dropped, 0u);
    ASSERT_EQ(voxel_build_faces(&one, 1, 1, 1, 0.0f, verts, 24, &dropped), 0u);
    ASSERT_EQ(voxel_build_faces(&one, 1, 1, 1, NAN, verts, 24, &dropped), 0u);
    ASSERT_EQ(voxel_build_faces(&one, 65, 1, 1, 1.0f, verts, 24, &dropped), 0u);
    ASSERT_EQ(voxel_build_faces(NULL, 1, 1, 1, 1.0f, verts, 24, &dropped), 0u);
    ASSERT_EQ(voxel_build_faces(&one, 1, 1, 1, 1.0f, NULL, 24, &dropped), 0u);
    ASSERT_EQ(voxel_build_faces(&one, 1, 1, 1, 1.0f, verts, 24, NULL), 24u);
}

TEST_MAIN_BEGIN()
    RUN_TEST(voxel_exposes_outer_faces_only);
    RUN_TEST(voxel_quads_wind_outward_and_lie_on_the_face);
    RUN_TEST(voxel_hides_faces_between_solid_neighbours);
    RUN_TEST(voxel_rejects_bad_grids);
TEST_MAIN_END()
