#include "test_framework.h"
#include <kernel/break_kernel.h>

TEST(move_wish_faces_yaw_and_rejects_nan) {
    BreakKernelMoveInput in;
    BreakKernelMoveOutput out;
    memset(&out, 0x5a, sizeof(out));
    in.forward = 1.0f;
    in.strafe = 0.0f;
    in.camera_yaw = 0.0f;
    in.jump = false;
    ASSERT_EQ(break_kernel_move_wish(&in, &out), BREAK_KERNEL_OK);
    ASSERT_FLOAT_EQ(out.wish.e[0], 0.0f, 1e-5);
    ASSERT_FLOAT_EQ(out.wish.e[1], 0.0f, 1e-5);
    ASSERT_FLOAT_EQ(out.wish.e[2], 1.0f, 1e-5);

    in.camera_yaw = 1.5707963f;
    ASSERT_EQ(break_kernel_move_wish(&in, &out), BREAK_KERNEL_OK);
    ASSERT_FLOAT_EQ(out.wish.e[0], 1.0f, 1e-5);
    ASSERT_FLOAT_EQ(out.wish.e[2], 0.0f, 1e-5);

    in.camera_yaw = 0.0f;
    in.strafe = 1.0f;
    ASSERT_EQ(break_kernel_move_wish(&in, &out), BREAK_KERNEL_OK);
    f32 len = sqrtf(out.wish.e[0] * out.wish.e[0] + out.wish.e[2] * out.wish.e[2]);
    ASSERT_FLOAT_EQ(len, 1.0f, 1e-5);

    BreakKernelMoveOutput kept = out;
    in.forward = nanf("");
    ASSERT_EQ(break_kernel_move_wish(&in, &out), BREAK_KERNEL_INVALID);
    ASSERT_EQ(memcmp(&out, &kept, sizeof(out)), 0);
}

TEST_MAIN_BEGIN()
    RUN_TEST(move_wish_faces_yaw_and_rejects_nan);
TEST_MAIN_END()
