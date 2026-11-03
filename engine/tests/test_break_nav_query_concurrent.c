#include "test_framework.h"
#include <ai/break_ai.h>
#include <ai/break_nav_internal.h>
#include <core/platform_thread.h>
#include <stdatomic.h>

#define QUERY_THREAD_COUNT 4u
#define QUERY_ITERATIONS 8u

typedef struct ConcurrentQuery {
    BreakNavMesh *mesh;
    atomic_uint *ready;
    atomic_bool *start;
    u32 index;
    BreakNavError status;
} ConcurrentQuery;

static bool endpoint_equal(Vec3 a, Vec3 b) {
    return fabsf(a.e[0] - b.e[0]) <= 1.0e-5f &&
           fabsf(a.e[2] - b.e[2]) <= 1.0e-5f;
}

static PLATFORM_THREAD_RET run_concurrent_queries(PLATFORM_THREAD_ARG argument) {
    ConcurrentQuery *query = (ConcurrentQuery *)argument;
    atomic_fetch_add_explicit(query->ready, 1u, memory_order_release);
    while (!atomic_load_explicit(query->start, memory_order_acquire)) {
        platform_thread_yield();
    }
    query->status = BREAK_NAV_FAILED;
    for (u32 i = 0; i < QUERY_ITERATIONS; i++) {
        Vec3 start = vec3(0.5f, 0.0f, 0.5f + (f32)query->index);
        Vec3 end = vec3(255.5f, 0.0f, 0.5f + (f32)query->index);
        BreakNavPath path;
        BreakNavError status = break_nav_find_path(query->mesh, start, end, &path);
        if (status != BREAK_NAV_OK) {
            query->status = status;
            return PLATFORM_THREAD_RETURN;
        }
        if (path.count < 2 || !endpoint_equal(path.points[0], start) ||
            !endpoint_equal(path.points[path.count - 1], end)) {
            query->status = BREAK_NAV_FAILED;
            return PLATFORM_THREAD_RETURN;
        }
    }
    query->status = BREAK_NAV_OK;
    return PLATFORM_THREAD_RETURN;
}

TEST(public_queries_on_one_mesh_are_independent_across_threads) {
    enum { SIZE = 256 };
    f32 *heights = (f32 *)calloc((size_t)SIZE * SIZE, sizeof(f32));
    ASSERT_NOT_NULL(heights);
    BreakNavHeightfield field;
    memset(&field, 0, sizeof(field));
    field.heights = heights;
    field.width = SIZE;
    field.depth = SIZE;
    field.cell = 1.0f;
    field.height_scale = 1.0f;
    BreakNavMesh *mesh = break_nav_bake_heightfield(&field, 45.0f, 0.0f);
    ASSERT_NOT_NULL(mesh);
    BreakNavPath sequential;
    BreakNavError sequential_status = break_nav_find_path(mesh, vec3(0.5f, 0, 0.5f),
                                                          vec3(255.5f, 0, 0.5f), &sequential);
    if (sequential_status != BREAK_NAV_OK) {
        printf("  sequential query status %d\n", (int)sequential_status);
    }
    ASSERT_EQ(sequential_status, BREAK_NAV_OK);

    atomic_uint ready;
    atomic_bool start;
    atomic_init(&ready, 0u);
    atomic_init(&start, false);
    ConcurrentQuery queries[QUERY_THREAD_COUNT];
    PlatformThread threads[QUERY_THREAD_COUNT];
    for (u32 i = 0; i < QUERY_THREAD_COUNT; i++) {
        queries[i].mesh = mesh;
        queries[i].ready = &ready;
        queries[i].start = &start;
        queries[i].index = i;
        queries[i].status = BREAK_NAV_FAILED;
        ASSERT_TRUE(platform_thread_create(&threads[i], run_concurrent_queries, &queries[i]));
    }
    while (atomic_load_explicit(&ready, memory_order_acquire) < QUERY_THREAD_COUNT) {
        platform_thread_yield();
    }
    atomic_store_explicit(&start, true, memory_order_release);
    for (u32 i = 0; i < QUERY_THREAD_COUNT; i++) {
        platform_thread_join(threads[i]);
    }
    for (u32 i = 0; i < QUERY_THREAD_COUNT; i++) {
        if (queries[i].status != BREAK_NAV_OK) {
            printf("  query thread %u status %d\n", i, (int)queries[i].status);
        }
        ASSERT_EQ(queries[i].status, BREAK_NAV_OK);
    }
    break_nav_mesh_destroy(mesh);
    free(heights);
}

TEST(workspace_pool_exhaustion_is_bounded_and_output_is_unchanged) {
    f32 heights[64];
    memset(heights, 0, sizeof(heights));
    BreakNavHeightfield field;
    memset(&field, 0, sizeof(field));
    field.heights = heights;
    field.width = 8;
    field.depth = 8;
    field.cell = 1.0f;
    field.height_scale = 1.0f;
    BreakNavMesh *mesh = break_nav_bake_heightfield(&field, 45.0f, 0.0f);
    ASSERT_NOT_NULL(mesh);
    BreakNavWorkspace *workspaces[BREAK_NAV_QUERY_POOL_CAPACITY];
    u32 slots[BREAK_NAV_QUERY_POOL_CAPACITY];
    for (u32 i = 0; i < BREAK_NAV_QUERY_POOL_CAPACITY; i++) {
        workspaces[i] = break_nav_workspace_pool_acquire(mesh, &slots[i]);
        ASSERT_NOT_NULL(workspaces[i]);
        for (u32 n = 0; n < i; n++) {
            ASSERT_NEQ(slots[i], slots[n]);
        }
    }
    BreakNavPath output;
    memset(&output, 0x52, sizeof(output));
    BreakNavPath before = output;
    ASSERT_EQ(break_nav_find_path(mesh, vec3(0.5f, 0, 0.5f),
                                  vec3(7.5f, 0, 7.5f), &output), BREAK_NAV_OVERLOAD);
    ASSERT_EQ(memcmp(&output, &before, sizeof(output)), 0);
    for (u32 i = 0; i < BREAK_NAV_QUERY_POOL_CAPACITY; i++) {
        break_nav_workspace_pool_release(mesh, slots[i]);
    }
    ASSERT_EQ(break_nav_find_path(mesh, vec3(0.5f, 0, 0.5f),
                                  vec3(7.5f, 0, 7.5f), &output), BREAK_NAV_OK);
    break_nav_mesh_destroy(mesh);
}

TEST_MAIN_BEGIN()
    RUN_TEST(public_queries_on_one_mesh_are_independent_across_threads);
    RUN_TEST(workspace_pool_exhaustion_is_bounded_and_output_is_unchanged);
TEST_MAIN_END()
