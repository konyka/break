#include "test_framework.h"
#include <ai/break_ai.h>
#include <stdlib.h>

static f32 seg_point_dist(Vec3 a, Vec3 b, Vec3 p) {
    f32 abx = b.e[0] - a.e[0];
    f32 abz = b.e[2] - a.e[2];
    f32 apx = p.e[0] - a.e[0];
    f32 apz = p.e[2] - a.e[2];
    f32 ab2 = abx * abx + abz * abz;
    f32 t = ab2 > 0.0f ? (apx * abx + apz * abz) / ab2 : 0.0f;
    if (t < 0.0f) t = 0.0f;
    if (t > 1.0f) t = 1.0f;
    f32 cx = a.e[0] + abx * t;
    f32 cz = a.e[2] + abz * t;
    f32 dx = p.e[0] - cx;
    f32 dz = p.e[2] - cz;
    return sqrtf(dx * dx + dz * dz);
}

static bool crosses_wall(Vec3 a, Vec3 b) {
    f32 dx = b.e[0] - a.e[0];
    f32 dz = b.e[2] - a.e[2];
    if (fabsf(dx) < 1.0e-6f) {
        return a.e[0] >= 10.0f && a.e[0] <= 11.0f &&
               ((a.e[2] >= 0.0f && a.e[2] <= 16.0f) || (b.e[2] >= 0.0f && b.e[2] <= 16.0f));
    }
    for (int i = 0; i <= 20; i++) {
        f32 t = (f32)i / 20.0f;
        f32 x = a.e[0] + dx * t;
        f32 z = a.e[2] + dz * t;
        if (x >= 10.0f && x <= 11.0f && z >= 0.0f && z <= 16.0f) {
            return true;
        }
    }
    return false;
}

TEST(straight_path_stays_on_the_line) {
    f32 *h = (f32 *)calloc(32u * 32u, sizeof(f32));
    ASSERT_NOT_NULL(h);
    BreakNavHeightfield field;
    memset(&field, 0, sizeof(field));
    field.heights = h;
    field.width = 32;
    field.depth = 32;
    field.cell = 1.0f;
    field.height_scale = 1.0f;
    BreakNavMesh *mesh = break_nav_bake_heightfield(&field, 45.0f, 0.0f);
    ASSERT_NOT_NULL(mesh);
    Vec3 start = vec3(2.2f, 0, 4.2f);
    Vec3 end = vec3(28.4f, 0, 4.2f);
    BreakNavPath path;
    memset(&path, 0, sizeof(path));
    ASSERT_EQ(break_nav_find_path(mesh, start, end, &path), BREAK_NAV_OK);
    ASSERT_TRUE(path.count >= 2u);
    ASSERT_FLOAT_EQ(path.points[0].e[0], start.e[0], 1e-4);
    ASSERT_FLOAT_EQ(path.points[0].e[2], start.e[2], 1e-4);
    ASSERT_FLOAT_EQ(path.points[path.count - 1].e[0], end.e[0], 1e-4);
    ASSERT_FLOAT_EQ(path.points[path.count - 1].e[2], end.e[2], 1e-4);
    for (u32 i = 1; i + 1 < path.count; i++) {
        ASSERT_TRUE(seg_point_dist(start, end, path.points[i]) <= 1.0f);
    }
    break_nav_mesh_destroy(mesh);
    free(h);
}

TEST(wall_blocks_and_detour_misses_it) {
    enum { N = 24 };
    f32 *h = (f32 *)calloc(N * N, sizeof(f32));
    ASSERT_NOT_NULL(h);
    for (u32 z = 0; z < 16; z++) h[z * N + 10] = 20.0f;
    BreakNavHeightfield field;
    memset(&field, 0, sizeof(field));
    field.heights = h;
    field.width = N;
    field.depth = N;
    field.cell = 1.0f;
    field.height_scale = 1.0f;
    BreakNavMesh *mesh = break_nav_bake_heightfield(&field, 40.0f, 0.0f);
    ASSERT_NOT_NULL(mesh);
    Vec3 left = vec3(2.5f, 0, 8.0f);
    Vec3 right = vec3(18.5f, 0, 8.0f);
    BreakNavPath blocked;
    blocked.count = 42;
    for (u32 z = 0; z < N; z++) h[z * N + 10] = 20.0f;
    BreakNavMesh *full = break_nav_bake_heightfield(&field, 40.0f, 0.0f);
    ASSERT_EQ(break_nav_find_path(full, left, right, &blocked), BREAK_NAV_FAILED);
    ASSERT_EQ(blocked.count, 42u);
    break_nav_mesh_destroy(full);

    for (u32 z = 16; z < N; z++) h[z * N + 10] = 0.0f;
    BreakNavMesh *gap = break_nav_bake_heightfield(&field, 40.0f, 0.0f);
    ASSERT_NOT_NULL(gap);
    BreakNavPath path;
    ASSERT_EQ(break_nav_find_path(gap, left, right, &path), BREAK_NAV_OK);
    f32 length = 0.0f;
    for (u32 i = 1; i < path.count; i++) {
        ASSERT_FALSE(crosses_wall(path.points[i - 1], path.points[i]));
        f32 dx = path.points[i].e[0] - path.points[i - 1].e[0];
        f32 dz = path.points[i].e[2] - path.points[i - 1].e[2];
        length += sqrtf(dx * dx + dz * dz);
    }
    f32 straight = 16.0f;
    ASSERT_TRUE(length > straight);
    break_nav_mesh_destroy(gap);
    break_nav_mesh_destroy(mesh);
    free(h);
}

TEST(outside_and_too_many_corners) {
    f32 *h = (f32 *)calloc(8u * 8u, sizeof(f32));
    ASSERT_NOT_NULL(h);
    BreakNavHeightfield field;
    memset(&field, 0, sizeof(field));
    field.heights = h;
    field.width = 8;
    field.depth = 8;
    field.cell = 1.0f;
    field.height_scale = 1.0f;
    BreakNavMesh *mesh = break_nav_bake_heightfield(&field, 45.0f, 0.0f);
    BreakNavPath path;
    path.count = 3;
    ASSERT_EQ(break_nav_find_path(mesh, vec3(-1, 0, 1), vec3(2, 0, 1), &path), BREAK_NAV_FAILED);
    ASSERT_EQ(path.count, 3u);
    break_nav_mesh_destroy(mesh);
    free(h);

    enum { S = 280 };
    f32 *maze = (f32 *)malloc(sizeof(f32) * S * S);
    ASSERT_NOT_NULL(maze);
    for (u32 i = 0; i < S * S; i++) maze[i] = 50.0f;
    u32 x = 0;
    u32 z = 0;
    maze[0] = 0.0f;
    for (u32 step = 0; step < S - 1; step++) {
        if ((step % 2u) == 0u) x++;
        else z++;
        maze[z * S + x] = 0.0f;
    }
    field.heights = maze;
    field.width = S;
    field.depth = S;
    BreakNavMesh *long_mesh = break_nav_bake_heightfield(&field, 45.0f, 0.0f);
    ASSERT_NOT_NULL(long_mesh);
    path.count = 9;
    Vec3 a = vec3(0.5f, 0, 0.5f);
    Vec3 b = vec3((f32)x + 0.5f, 0, (f32)z + 0.5f);
    ASSERT_EQ(break_nav_find_path(long_mesh, a, b, &path), BREAK_NAV_OVERLOAD);
    ASSERT_EQ(path.count, 9u);
    break_nav_mesh_destroy(long_mesh);
    free(maze);
}

TEST_MAIN_BEGIN()
    RUN_TEST(straight_path_stays_on_the_line);
    RUN_TEST(wall_blocks_and_detour_misses_it);
    RUN_TEST(outside_and_too_many_corners);
TEST_MAIN_END()
