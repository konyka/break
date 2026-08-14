#include "test_framework.h"
#include <renderer/motion_history.h>
#include <math.h>

static Mat4 translated(float x, float y, float z) {
    Mat4 m = mat4_identity();
    m.e[3][0] = x;
    m.e[3][1] = y;
    m.e[3][2] = z;
    return m;
}

TEST(first_frame_is_invalid)
{
    MotionHistory h;
    motion_history_init(&h, 2);
    Mat4 first = translated(1, 2, 3);
    motion_history_begin_frame(&h);
    motion_history_set_current(&h, 0, 7, &first);

    Mat4 previous, current;
    ASSERT_FALSE(motion_history_get_pair(&h, 0, 7, &previous, &current));
    motion_history_commit(&h);
    motion_history_begin_frame(&h);
    ASSERT_FALSE(motion_history_get_pair(&h, 0, 7, &previous, &current));
    motion_history_destroy(&h);
}

TEST(second_frame_returns_previous_and_current)
{
    MotionHistory h;
    motion_history_init(&h, 2);

    motion_history_begin_frame(&h);
    Mat4 first = translated(1, 0, 0);
    motion_history_set_current(&h, 0, 3, &first);
    motion_history_commit(&h);

    motion_history_begin_frame(&h);
    Mat4 second = translated(4, 0, 0);
    motion_history_set_current(&h, 0, 3, &second);

    Mat4 previous, current;
    ASSERT_TRUE(motion_history_get_pair(&h, 0, 3, &previous, &current));
    ASSERT_FLOAT_EQ(previous.e[3][0], 1.0f, 0.0001f);
    ASSERT_FLOAT_EQ(current.e[3][0], 4.0f, 0.0001f);
    motion_history_destroy(&h);
}

TEST(generation_reuse_invalidates_history)
{
    MotionHistory h;
    motion_history_init(&h, 1);

    motion_history_begin_frame(&h);
    Mat4 first = translated(1, 0, 0);
    motion_history_set_current(&h, 0, 10, &first);
    motion_history_commit(&h);

    motion_history_begin_frame(&h);
    Mat4 reused = translated(9, 0, 0);
    motion_history_set_current(&h, 0, 11, &reused);

    Mat4 previous, current;
    ASSERT_FALSE(motion_history_get_pair(&h, 0, 11, &previous, &current));
    motion_history_destroy(&h);
}

TEST(missing_frame_invalidates_history)
{
    MotionHistory h;
    motion_history_init(&h, 1);
    Mat4 first = translated(1, 0, 0);
    Mat4 second = translated(3, 0, 0);

    motion_history_begin_frame(&h);
    motion_history_set_current(&h, 0, 5, &first);
    motion_history_commit(&h);
    motion_history_begin_frame(&h);
    motion_history_set_current(&h, 0, 5, &second);
    ASSERT_TRUE(motion_history_get_pair(&h, 0, 5, NULL, NULL));
    motion_history_commit(&h);

    motion_history_begin_frame(&h);
    motion_history_commit(&h); /* object was absent for one render frame */
    motion_history_begin_frame(&h);
    motion_history_set_current(&h, 0, 5, &first);
    ASSERT_FALSE(motion_history_get_pair(&h, 0, 5, NULL, NULL));
    motion_history_destroy(&h);
}

TEST(invalid_indices_are_safe)
{
    MotionHistory h;
    motion_history_init(&h, 1);
    Mat4 m = translated(0, 0, 0);
    motion_history_begin_frame(&h);
    ASSERT_FALSE(motion_history_set_current(&h, 4, 1, &m));
    ASSERT_FALSE(motion_history_get_pair(&h, 4, 1, NULL, NULL));
    motion_history_destroy(&h);
}

TEST_MAIN_BEGIN()
    RUN_TEST(first_frame_is_invalid);
    RUN_TEST(second_frame_returns_previous_and_current);
    RUN_TEST(generation_reuse_invalidates_history);
    RUN_TEST(missing_frame_invalidates_history);
    RUN_TEST(invalid_indices_are_safe);
TEST_MAIN_END()
