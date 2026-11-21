#include "test_framework.h"
#include <renderer/world_stream_job.h>

TEST(stream_apply_sets_resident_bits_on_the_task_system) {
    TaskSystem *tasks = task_system_create(1);
    ASSERT_NOT_NULL(tasks);
    bool resident[4] = {false, false, false, false};
    StreamWant wants[2];
    wants[0].tile_x = 1;
    wants[0].tile_z = 0;
    wants[0].resident = true;
    wants[1].tile_x = 9;
    wants[1].tile_z = 0;
    wants[1].resident = true;
    u32 rejected = 0;
    u32 applied = world_stream_apply(tasks, wants, 2, resident, 2, 2, &rejected);
    bool loaded = resident[1];
    bool untouched = !resident[0];

    StreamWant unload;
    unload.tile_x = 1;
    unload.tile_z = 0;
    unload.resident = false;
    u32 rejected_unload = 0;
    u32 applied_unload = world_stream_apply(tasks, &unload, 1, resident, 2, 2, &rejected_unload);
    u32 without_tasks = world_stream_apply(NULL, &unload, 1, resident, 2, 2, &rejected_unload);
    /* the task system is a process-wide single instance: release it before
     * any assert can return, so a failure here does not break later cases */
    task_system_destroy(tasks);
    ASSERT_EQ(applied, 1u);
    ASSERT_EQ(rejected, 1u);
    ASSERT_TRUE(loaded);
    ASSERT_TRUE(untouched);
    ASSERT_EQ(applied_unload, 1u);
    ASSERT_FALSE(resident[1]);
    ASSERT_EQ(without_tasks, 0u);
}

/* Wants apply in order, so a later want for the same tile wins; the
 * row-major index uses the grid width. */
TEST(stream_apply_order_and_indexing) {
    TaskSystem *tasks = task_system_create(1);
    ASSERT_NOT_NULL(tasks);
    bool resident[6];
    memset(resident, 0, sizeof(resident));
    StreamWant wants[3];
    wants[0].tile_x = 2; wants[0].tile_z = 1; wants[0].resident = true;
    wants[1].tile_x = 0; wants[1].tile_z = 1; wants[1].resident = true;
    wants[2].tile_x = 0; wants[2].tile_z = 1; wants[2].resident = false;
    u32 rejected = 9;
    u32 applied = world_stream_apply(tasks, wants, 3, resident, 3, 2, &rejected);
    task_system_destroy(tasks);
    ASSERT_EQ(applied, 3u);
    ASSERT_EQ(rejected, 0u);
    ASSERT_TRUE(resident[5]);
    for (u32 i = 0; i < 5u; i++) ASSERT_FALSE(resident[i]);
}

/* Tiles past either edge are rejected; bad arguments apply nothing and
 * report zero rejections; a NULL rejection counter is allowed. */
TEST(stream_apply_rejects_out_of_range_and_bad_arguments) {
    TaskSystem *tasks = task_system_create(1);
    ASSERT_NOT_NULL(tasks);
    bool resident[4] = {false, false, false, false};
    StreamWant wants[3];
    wants[0].tile_x = 2; wants[0].tile_z = 0; wants[0].resident = true;
    wants[1].tile_x = 0; wants[1].tile_z = 2; wants[1].resident = true;
    wants[2].tile_x = 1; wants[2].tile_z = 1; wants[2].resident = true;
    u32 rejected = 0;
    u32 applied = world_stream_apply(tasks, wants, 3, resident, 2, 2, &rejected);
    u32 bad_rejected = 7;
    u32 bad[4];
    bad[0] = world_stream_apply(tasks, NULL, 1, resident, 2, 2, &bad_rejected);
    u32 after_null = bad_rejected;
    bad[1] = world_stream_apply(tasks, wants, 0, resident, 2, 2, &bad_rejected);
    bad[2] = world_stream_apply(tasks, wants, 1, NULL, 2, 2, &bad_rejected);
    bad[3] = world_stream_apply(tasks, wants, 1, resident, 0, 2, &bad_rejected);
    u32 no_counter = world_stream_apply(tasks, wants + 2, 1, resident, 2, 2, NULL);
    task_system_destroy(tasks);
    ASSERT_EQ(applied, 1u);
    ASSERT_EQ(rejected, 2u);
    ASSERT_TRUE(resident[3]);
    ASSERT_EQ(after_null, 0u);
    for (u32 i = 0; i < 4u; i++) ASSERT_EQ(bad[i], 0u);
    ASSERT_EQ(no_counter, 1u);
}

TEST_MAIN_BEGIN()
    RUN_TEST(stream_apply_sets_resident_bits_on_the_task_system);
    RUN_TEST(stream_apply_order_and_indexing);
    RUN_TEST(stream_apply_rejects_out_of_range_and_bad_arguments);
TEST_MAIN_END()
