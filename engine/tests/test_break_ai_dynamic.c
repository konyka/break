#include "test_framework.h"
#include <ai/break_ai.h>
#include <core/platform_thread.h>

typedef struct DynamicFixture {
    f32 heights[81];
    BreakNavMesh *mesh;
    BreakAiRuntime *ai;
} DynamicFixture;

static bool fixture_init(DynamicFixture *fixture, u32 max_obstacles, u32 max_cached_paths) {
    memset(fixture, 0, sizeof(*fixture));
    BreakNavHeightfield field;
    memset(&field, 0, sizeof(field));
    field.heights = fixture->heights;
    field.width = 9;
    field.depth = 9;
    field.cell = 1.0f;
    field.height_scale = 1.0f;
    fixture->mesh = break_nav_bake_heightfield(&field, 45.0f, 0.0f);
    if (!fixture->mesh) {
        return false;
    }
    BreakAiRuntimeDesc desc;
    memset(&desc, 0, sizeof(desc));
    desc.max_obstacles = max_obstacles;
    desc.max_cached_paths = max_cached_paths;
    fixture->ai = break_ai_runtime_create(fixture->mesh, &desc);
    return fixture->ai != NULL;
}

static void fixture_destroy(DynamicFixture *fixture) {
    break_ai_runtime_destroy(fixture->ai);
    break_nav_mesh_destroy(fixture->mesh);
}

static BreakAiObstacleDesc wall(f32 min_z, f32 max_z) {
    BreakAiObstacleDesc desc;
    desc.min_x = 4.0f;
    desc.min_z = min_z;
    desc.max_x = 5.0f;
    desc.max_z = max_z;
    return desc;
}

static Vec3 left_point(void) {
    return vec3(1.5f, 0.0f, 4.5f);
}

static Vec3 right_point(void) {
    return vec3(7.5f, 0.0f, 4.5f);
}

TEST(dynamic_wall_blocks_reopen_and_versions_reject_stale_paths) {
    DynamicFixture fixture;
    ASSERT_TRUE(fixture_init(&fixture, 2, 4));
    BreakAiPath old_path;
    ASSERT_EQ(break_ai_find_path(fixture.ai, left_point(), right_point(), 1, &old_path), BREAK_NAV_OK);
    ASSERT_EQ(old_path.nav_version, 1u);
    ASSERT_TRUE(break_ai_path_is_current(fixture.ai, &old_path));

    BreakAiObstacleDesc full_wall = wall(-1.0f, 10.0f);
    BreakAiObstacleHandle handle;
    ASSERT_EQ(break_ai_obstacle_add(fixture.ai, &full_wall, &handle), BREAK_NAV_OK);
    ASSERT_EQ(break_ai_nav_version(fixture.ai), 2u);
    ASSERT_FALSE(break_ai_path_is_current(fixture.ai, &old_path));

    BreakAiPath output;
    memset(&output, 0x5a, sizeof(output));
    BreakAiPath before = output;
    ASSERT_EQ(break_ai_find_path(fixture.ai, left_point(), right_point(), 1, &output), BREAK_NAV_STALE);
    ASSERT_EQ(memcmp(&output, &before, sizeof(output)), 0);
    ASSERT_EQ(break_ai_find_path(fixture.ai, left_point(), right_point(), 2, &output), BREAK_NAV_FAILED);
    ASSERT_EQ(memcmp(&output, &before, sizeof(output)), 0);

    ASSERT_EQ(break_ai_obstacle_remove(fixture.ai, handle), BREAK_NAV_OK);
    ASSERT_EQ(break_ai_nav_version(fixture.ai), 3u);
    ASSERT_FALSE(break_ai_path_is_current(fixture.ai, &old_path));
    ASSERT_EQ(break_ai_find_path(fixture.ai, left_point(), right_point(), 3, &output), BREAK_NAV_OK);
    ASSERT_EQ(output.nav_version, 3u);
    ASSERT_EQ(break_ai_obstacle_remove(fixture.ai, handle), BREAK_NAV_STALE);
    ASSERT_EQ(break_ai_nav_version(fixture.ai), 3u);
    fixture_destroy(&fixture);
}

TEST(overlapping_obstacles_do_not_reopen_early) {
    DynamicFixture fixture;
    ASSERT_TRUE(fixture_init(&fixture, 2, 2));
    BreakAiObstacleDesc full_wall = wall(-1.0f, 10.0f);
    BreakAiObstacleHandle first;
    BreakAiObstacleHandle second;
    ASSERT_EQ(break_ai_obstacle_add(fixture.ai, &full_wall, &first), BREAK_NAV_OK);
    ASSERT_EQ(break_ai_obstacle_add(fixture.ai, &full_wall, &second), BREAK_NAV_OK);
    ASSERT_EQ(break_ai_obstacle_remove(fixture.ai, first), BREAK_NAV_OK);
    BreakAiPath output;
    ASSERT_EQ(break_ai_find_path(fixture.ai, left_point(), right_point(), 4, &output), BREAK_NAV_FAILED);
    ASSERT_EQ(break_ai_obstacle_remove(fixture.ai, second), BREAK_NAV_OK);
    ASSERT_EQ(break_ai_find_path(fixture.ai, left_point(), right_point(), 5, &output), BREAK_NAV_OK);
    fixture_destroy(&fixture);
}

TEST(obstacle_update_is_atomic_and_noop_does_not_advance_version) {
    DynamicFixture fixture;
    ASSERT_TRUE(fixture_init(&fixture, 1, 2));
    BreakAiObstacleDesc full_wall = wall(-1.0f, 10.0f);
    BreakAiObstacleHandle handle;
    ASSERT_EQ(break_ai_obstacle_add(fixture.ai, &full_wall, &handle), BREAK_NAV_OK);
    BreakAiObstacleDesc invalid = wall(5.0f, 2.0f);
    ASSERT_EQ(break_ai_obstacle_update(fixture.ai, handle, &invalid), BREAK_NAV_INVALID);
    ASSERT_EQ(break_ai_nav_version(fixture.ai), 2u);
    BreakAiPath output;
    ASSERT_EQ(break_ai_find_path(fixture.ai, left_point(), right_point(), 2, &output), BREAK_NAV_FAILED);

    BreakAiObstacleDesc partial = wall(-1.0f, 2.0f);
    ASSERT_EQ(break_ai_obstacle_update(fixture.ai, handle, &partial), BREAK_NAV_OK);
    ASSERT_EQ(break_ai_nav_version(fixture.ai), 3u);
    ASSERT_EQ(break_ai_find_path(fixture.ai, left_point(), right_point(), 3, &output), BREAK_NAV_OK);
    ASSERT_EQ(break_ai_obstacle_update(fixture.ai, handle, &partial), BREAK_NAV_OK);
    ASSERT_EQ(break_ai_nav_version(fixture.ai), 3u);
    fixture_destroy(&fixture);
}

TEST(obstacle_capacity_failure_preserves_live_slot_and_version) {
    DynamicFixture fixture;
    ASSERT_TRUE(fixture_init(&fixture, 1, 1));
    BreakAiObstacleDesc full_wall = wall(-1.0f, 10.0f);
    BreakAiObstacleHandle first;
    ASSERT_EQ(break_ai_obstacle_add(fixture.ai, &full_wall, &first), BREAK_NAV_OK);
    BreakAiObstacleHandle output;
    memset(&output, 0x6b, sizeof(output));
    BreakAiObstacleHandle before = output;
    BreakAiObstacleDesc second_desc = wall(0.0f, 1.0f);
    ASSERT_EQ(break_ai_obstacle_add(fixture.ai, &second_desc, &output), BREAK_NAV_OVERLOAD);
    ASSERT_EQ(memcmp(&output, &before, sizeof(output)), 0);
    ASSERT_EQ(break_ai_nav_version(fixture.ai), 2u);
    ASSERT_EQ(break_ai_obstacle_remove(fixture.ai, first), BREAK_NAV_OK);
    ASSERT_EQ(break_ai_obstacle_add(fixture.ai, &second_desc, &output), BREAK_NAV_OK);
    ASSERT_EQ(output.index, first.index);
    ASSERT_NEQ(output.generation, first.generation);
    ASSERT_EQ(break_ai_obstacle_remove(fixture.ai, first), BREAK_NAV_STALE);
    ASSERT_EQ(break_ai_nav_version(fixture.ai), 4u);
    fixture_destroy(&fixture);
}

TEST(invalid_obstacle_does_not_create_or_advance_version) {
    DynamicFixture fixture;
    ASSERT_TRUE(fixture_init(&fixture, 1, 1));
    BreakAiObstacleHandle output;
    memset(&output, 0x19, sizeof(output));
    BreakAiObstacleHandle before = output;
    BreakAiObstacleDesc desc = wall(0.0f, 0.0f);
    desc.min_x = 100.0f;
    desc.max_x = 101.0f;
    ASSERT_EQ(break_ai_obstacle_add(fixture.ai, &desc, &output), BREAK_NAV_FAILED);
    ASSERT_EQ(memcmp(&output, &before, sizeof(output)), 0);
    ASSERT_EQ(break_ai_nav_version(fixture.ai), 1u);
    BreakAiRuntimeDesc too_large;
    memset(&too_large, 0, sizeof(too_large));
    too_large.max_obstacles = BREAK_AI_MAX_OBSTACLES + 1u;
    ASSERT_TRUE(break_ai_runtime_create(fixture.mesh, &too_large) == NULL);
    fixture_destroy(&fixture);
}

typedef struct OwnerProbe {
    BreakAiRuntime *ai;
    BreakNavError result;
} OwnerProbe;

static PLATFORM_THREAD_RET reject_obstacle_from_worker(PLATFORM_THREAD_ARG argument) {
    OwnerProbe *probe = (OwnerProbe *)argument;
    BreakAiObstacleDesc desc = wall(-1.0f, 10.0f);
    BreakAiObstacleHandle handle;
    probe->result = break_ai_obstacle_add(probe->ai, &desc, &handle);
    return PLATFORM_THREAD_RETURN;
}

TEST(runtime_mutations_reject_non_owner_thread) {
    DynamicFixture fixture;
    ASSERT_TRUE(fixture_init(&fixture, 1, 1));
    OwnerProbe probe;
    probe.ai = fixture.ai;
    probe.result = BREAK_NAV_OK;
    PlatformThread thread;
    ASSERT_TRUE(platform_thread_create(&thread, reject_obstacle_from_worker, &probe));
    platform_thread_join(thread);
    ASSERT_EQ(probe.result, BREAK_NAV_REJECTED);
    ASSERT_EQ(break_ai_nav_version(fixture.ai), 1u);
    BreakAiPath output;
    ASSERT_EQ(break_ai_find_path(fixture.ai, left_point(), right_point(), 1, &output), BREAK_NAV_OK);
    fixture_destroy(&fixture);
}

TEST_MAIN_BEGIN()
    RUN_TEST(dynamic_wall_blocks_reopen_and_versions_reject_stale_paths);
    RUN_TEST(overlapping_obstacles_do_not_reopen_early);
    RUN_TEST(obstacle_update_is_atomic_and_noop_does_not_advance_version);
    RUN_TEST(obstacle_capacity_failure_preserves_live_slot_and_version);
    RUN_TEST(invalid_obstacle_does_not_create_or_advance_version);
    RUN_TEST(runtime_mutations_reject_non_owner_thread);
TEST_MAIN_END()
