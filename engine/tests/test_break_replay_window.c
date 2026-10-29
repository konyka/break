/* Sliding anti-replay window for application messages (RFC 4303 §3.4.3
 * style): accepts each 64-bit sequence number at most once, accepts late
 * arrivals inside the window, rejects anything older than the window. */
#include "test_framework.h"

#include <network/break_replay_window.h>

TEST(fresh_window_accepts_in_order_and_rejects_duplicates)
{
    BreakReplayWindow w;
    break_replay_window_init(&w);
    ASSERT_EQ(break_replay_window_check_and_mark(&w, 1u), BREAK_REPLAY_OK);
    ASSERT_EQ(break_replay_window_check_and_mark(&w, 2u), BREAK_REPLAY_OK);
    ASSERT_EQ(break_replay_window_check_and_mark(&w, 2u), BREAK_REPLAY_DUPLICATE);
    ASSERT_EQ(break_replay_window_check_and_mark(&w, 1u), BREAK_REPLAY_DUPLICATE);
    ASSERT_EQ(break_replay_window_highest(&w), 2u);
    /* 0 is reserved (never a valid sequence) */
    ASSERT_EQ(break_replay_window_check_and_mark(&w, 0u), BREAK_REPLAY_INVALID);
}

TEST(late_arrivals_inside_the_window_are_accepted_once)
{
    BreakReplayWindow w;
    break_replay_window_init(&w);
    ASSERT_EQ(break_replay_window_check_and_mark(&w, 100u), BREAK_REPLAY_OK);
    /* 37..99 never arrived: each may arrive once, late */
    ASSERT_EQ(break_replay_window_check_and_mark(&w, 99u), BREAK_REPLAY_OK);
    ASSERT_EQ(break_replay_window_check_and_mark(&w, 37u), BREAK_REPLAY_OK);
    ASSERT_EQ(break_replay_window_check_and_mark(&w, 37u), BREAK_REPLAY_DUPLICATE);
    /* 100 - 64 = 36 is outside a 64-wide window */
    ASSERT_EQ(break_replay_window_check_and_mark(&w, 36u), BREAK_REPLAY_TOO_OLD);
    ASSERT_EQ(break_replay_window_highest(&w), 100u);
}

TEST(a_jump_slides_the_window_and_forgets_old_marks)
{
    BreakReplayWindow w;
    break_replay_window_init(&w);
    for (u64 s = 1u; s <= 64u; s++) {
        ASSERT_EQ(break_replay_window_check_and_mark(&w, s), BREAK_REPLAY_OK);
    }
    /* jump by exactly the window width: everything before is too old */
    ASSERT_EQ(break_replay_window_check_and_mark(&w, 128u), BREAK_REPLAY_OK);
    ASSERT_EQ(break_replay_window_check_and_mark(&w, 64u), BREAK_REPLAY_TOO_OLD);
    ASSERT_EQ(break_replay_window_check_and_mark(&w, 65u), BREAK_REPLAY_OK);
    ASSERT_EQ(break_replay_window_check_and_mark(&w, 127u), BREAK_REPLAY_OK);
    ASSERT_EQ(break_replay_window_check_and_mark(&w, 127u), BREAK_REPLAY_DUPLICATE);
    /* a huge jump does not wrap or overflow */
    ASSERT_EQ(break_replay_window_check_and_mark(&w, UINT64_MAX), BREAK_REPLAY_OK);
    ASSERT_EQ(break_replay_window_check_and_mark(&w, UINT64_MAX), BREAK_REPLAY_DUPLICATE);
    ASSERT_EQ(break_replay_window_check_and_mark(&w, UINT64_MAX - 63u), BREAK_REPLAY_OK);
    ASSERT_EQ(break_replay_window_check_and_mark(&w, UINT64_MAX - 64u), BREAK_REPLAY_TOO_OLD);
    ASSERT_EQ(break_replay_window_check_and_mark(&w, 128u), BREAK_REPLAY_TOO_OLD);
}

TEST(check_without_mark_does_not_consume)
{
    BreakReplayWindow w;
    break_replay_window_init(&w);
    /* verify-then-commit: a message is checked, authenticated, then marked */
    ASSERT_EQ(break_replay_window_check(&w, 5u), BREAK_REPLAY_OK);
    ASSERT_EQ(break_replay_window_check(&w, 5u), BREAK_REPLAY_OK);
    ASSERT_EQ(break_replay_window_highest(&w), 0u);
    ASSERT_EQ(break_replay_window_check_and_mark(&w, 5u), BREAK_REPLAY_OK);
    ASSERT_EQ(break_replay_window_check(&w, 5u), BREAK_REPLAY_DUPLICATE);
}

TEST(null_window_is_invalid)
{
    ASSERT_EQ(break_replay_window_check_and_mark(NULL, 1u), BREAK_REPLAY_INVALID);
    ASSERT_EQ(break_replay_window_check(NULL, 1u), BREAK_REPLAY_INVALID);
    ASSERT_EQ(break_replay_window_highest(NULL), 0u);
    break_replay_window_init(NULL);
}

TEST_MAIN_BEGIN()
    RUN_TEST(fresh_window_accepts_in_order_and_rejects_duplicates);
    RUN_TEST(late_arrivals_inside_the_window_are_accepted_once);
    RUN_TEST(a_jump_slides_the_window_and_forgets_old_marks);
    RUN_TEST(check_without_mark_does_not_consume);
    RUN_TEST(null_window_is_invalid);
TEST_MAIN_END()
