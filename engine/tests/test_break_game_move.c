#include "test_framework.h"
#include <game/break_game.h>

TEST(move_wish_faces_yaw_and_rejects_nan) {
    BreakGameMoveInput in;
    BreakGameMoveOutput out;
    memset(&out, 0x5a, sizeof(out));
    in.forward = 1.0f;
    in.strafe = 0.0f;
    in.camera_yaw = 0.0f;
    in.jump = false;
    ASSERT_EQ(break_game_move_wish(&in, &out), BREAK_GAME_OK);
    ASSERT_FLOAT_EQ(out.wish.e[0], 0.0f, 1e-5);
    ASSERT_FLOAT_EQ(out.wish.e[1], 0.0f, 1e-5);
    ASSERT_FLOAT_EQ(out.wish.e[2], 1.0f, 1e-5);

    in.camera_yaw = 1.5707963f;
    ASSERT_EQ(break_game_move_wish(&in, &out), BREAK_GAME_OK);
    ASSERT_FLOAT_EQ(out.wish.e[0], 1.0f, 1e-5);
    ASSERT_FLOAT_EQ(out.wish.e[2], 0.0f, 1e-5);

    in.camera_yaw = 0.0f;
    in.strafe = 1.0f;
    ASSERT_EQ(break_game_move_wish(&in, &out), BREAK_GAME_OK);
    f32 len = sqrtf(out.wish.e[0] * out.wish.e[0] + out.wish.e[2] * out.wish.e[2]);
    ASSERT_FLOAT_EQ(len, 1.0f, 1e-5);

    BreakGameMoveOutput kept = out;
    in.forward = nanf("");
    ASSERT_EQ(break_game_move_wish(&in, &out), BREAK_GAME_INVALID);
    ASSERT_EQ(memcmp(&out, &kept, sizeof(out)), 0);
}

TEST_MAIN_BEGIN()
    RUN_TEST(move_wish_faces_yaw_and_rejects_nan);
TEST_MAIN_END()
