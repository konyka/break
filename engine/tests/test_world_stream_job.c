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
    ASSERT_EQ(applied, 1u);
    ASSERT_EQ(rejected, 1u);
    ASSERT_TRUE(resident[1]);
    ASSERT_FALSE(resident[0]);

    StreamWant unload;
    unload.tile_x = 1;
    unload.tile_z = 0;
    unload.resident = false;
    applied = world_stream_apply(tasks, &unload, 1, resident, 2, 2, &rejected);
    ASSERT_EQ(applied, 1u);
    ASSERT_FALSE(resident[1]);
    ASSERT_EQ(world_stream_apply(NULL, &unload, 1, resident, 2, 2, &rejected), 0u);
    task_system_destroy(tasks);
}

TEST_MAIN_BEGIN()
    RUN_TEST(stream_apply_sets_resident_bits_on_the_task_system);
TEST_MAIN_END()
