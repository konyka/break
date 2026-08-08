/* Regression coverage for TaskSystem's documented process-wide singleton. */

#include "test_framework.h"
#include <task/task.h>

TEST(task_system_rejects_second_live_instance)
{
    TaskSystem *first = task_system_create(1);
    ASSERT_NOT_NULL(first);

    /* A second system would overwrite task.c's global ownership registry. */
    TaskSystem *second = task_system_create(1);
    ASSERT_TRUE(second == NULL);

    task_system_destroy(first);

    /* Destroy releases the singleton claim for a later engine lifetime. */
    TaskSystem *replacement = task_system_create(1);
    ASSERT_NOT_NULL(replacement);
    task_system_destroy(replacement);
}

TEST_MAIN_BEGIN()
    RUN_TEST(task_system_rejects_second_live_instance);
TEST_MAIN_END()
