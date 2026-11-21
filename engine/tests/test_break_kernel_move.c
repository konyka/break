#include "test_framework.h"
#include <kernel/break_kernel.h>
#include <math.h>

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

static BreakKernelMoveInput input(f32 forward, f32 strafe, f32 yaw, bool jump) {
    BreakKernelMoveInput in;
    in.forward = forward;
    in.strafe = strafe;
    in.camera_yaw = yaw;
    in.jump = jump;
    return in;
}

/* Inputs beyond [-1, 1] are clamped, so a stick reading of 3 moves no
 * faster than 1 and diagonal input is normalized to length 1. */
TEST(move_clamps_axes_and_diagonals) {
    BreakKernelMoveOutput out;
    BreakKernelMoveInput in = input(3.0f, 0.0f, 0.0f, false);
    ASSERT_EQ(break_kernel_move_wish(&in, &out), BREAK_KERNEL_OK);
    ASSERT_FLOAT_EQ(out.wish.e[2], 1.0f, 1e-6);
    in = input(-5.0f, -5.0f, 0.0f, false);
    ASSERT_EQ(break_kernel_move_wish(&in, &out), BREAK_KERNEL_OK);
    ASSERT_FLOAT_EQ(out.wish.e[0], -0.70710678f, 1e-5);
    ASSERT_FLOAT_EQ(out.wish.e[2], -0.70710678f, 1e-5);
    /* inputs inside the unit circle keep their length */
    in = input(0.3f, 0.4f, 0.0f, false);
    ASSERT_EQ(break_kernel_move_wish(&in, &out), BREAK_KERNEL_OK);
    ASSERT_FLOAT_EQ(sqrtf(out.wish.e[0] * out.wish.e[0] + out.wish.e[2] * out.wish.e[2]), 0.5f, 1e-5);
}

/* Strafe is to the camera's right: at yaw 0 (facing +Z) right is +X, and
 * turning the camera by pi turns the wish with it. */
TEST(move_strafe_is_camera_right_and_rotates_with_yaw) {
    BreakKernelMoveOutput out;
    BreakKernelMoveInput in = input(0.0f, 1.0f, 0.0f, false);
    ASSERT_EQ(break_kernel_move_wish(&in, &out), BREAK_KERNEL_OK);
    ASSERT_FLOAT_EQ(out.wish.e[0], 1.0f, 1e-6);
    ASSERT_FLOAT_EQ(out.wish.e[2], 0.0f, 1e-6);
    in = input(1.0f, 0.0f, 3.14159265f, false);
    ASSERT_EQ(break_kernel_move_wish(&in, &out), BREAK_KERNEL_OK);
    ASSERT_FLOAT_EQ(out.wish.e[0], 0.0f, 1e-5);
    ASSERT_FLOAT_EQ(out.wish.e[2], -1.0f, 1e-5);
    ASSERT_FLOAT_EQ(out.wish.e[1], 0.0f, 0.0f);
}

/* Jump and yaw pass through unchanged. */
TEST(move_passes_jump_and_yaw_through) {
    BreakKernelMoveOutput out;
    BreakKernelMoveInput in = input(0.0f, 0.0f, 0.75f, true);
    ASSERT_EQ(break_kernel_move_wish(&in, &out), BREAK_KERNEL_OK);
    ASSERT_TRUE(out.jump);
    ASSERT_FLOAT_EQ(out.yaw, 0.75f, 0.0f);
    ASSERT_FLOAT_EQ(out.wish.e[0], 0.0f, 0.0f);
    in.jump = false;
    ASSERT_EQ(break_kernel_move_wish(&in, &out), BREAK_KERNEL_OK);
    ASSERT_FALSE(out.jump);
}

/* Every non-finite field and NULL pointers are rejected without writing. */
TEST(move_rejects_every_bad_field) {
    BreakKernelMoveOutput out;
    memset(&out, 0x77, sizeof(out));
    BreakKernelMoveOutput kept = out;
    BreakKernelMoveInput in = input(0.0f, INFINITY, 0.0f, false);
    ASSERT_EQ(break_kernel_move_wish(&in, &out), BREAK_KERNEL_INVALID);
    in = input(0.0f, 0.0f, -INFINITY, false);
    ASSERT_EQ(break_kernel_move_wish(&in, &out), BREAK_KERNEL_INVALID);
    in = input(0.0f, 0.0f, NAN, false);
    ASSERT_EQ(break_kernel_move_wish(&in, &out), BREAK_KERNEL_INVALID);
    ASSERT_EQ(break_kernel_move_wish(NULL, &out), BREAK_KERNEL_INVALID);
    in = input(0.0f, 0.0f, 0.0f, false);
    ASSERT_EQ(break_kernel_move_wish(&in, NULL), BREAK_KERNEL_INVALID);
    ASSERT_EQ(memcmp(&out, &kept, sizeof(out)), 0);
}

TEST_MAIN_BEGIN()
    RUN_TEST(move_wish_faces_yaw_and_rejects_nan);
    RUN_TEST(move_clamps_axes_and_diagonals);
    RUN_TEST(move_strafe_is_camera_right_and_rotates_with_yaw);
    RUN_TEST(move_passes_jump_and_yaw_through);
    RUN_TEST(move_rejects_every_bad_field);
TEST_MAIN_END()
