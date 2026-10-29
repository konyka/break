/* Per-connection message and byte rate limit (token buckets on an injected
 * millisecond clock). */
#include "test_framework.h"

#include <network/break_msg_rate.h>

TEST(burst_then_refill_by_elapsed_time)
{
    BreakMsgRate r;
    /* 10 msgs/s, burst 5; 1000 B/s, burst 400 */
    ASSERT_TRUE(break_msg_rate_init(&r, 10u, 5u, 1000u, 400u, 0u));
    for (u32 i = 0u; i < 5u; i++) {
        ASSERT_EQ(break_msg_rate_admit(&r, 10u, 0u), BREAK_MSG_RATE_OK);
    }
    ASSERT_EQ(break_msg_rate_admit(&r, 10u, 0u), BREAK_MSG_RATE_MESSAGES);
    /* 100 ms later one message token is back (10/s) */
    ASSERT_EQ(break_msg_rate_admit(&r, 10u, 99u), BREAK_MSG_RATE_MESSAGES);
    ASSERT_EQ(break_msg_rate_admit(&r, 10u, 100u), BREAK_MSG_RATE_OK);
    ASSERT_EQ(break_msg_rate_admit(&r, 10u, 100u), BREAK_MSG_RATE_MESSAGES);
    /* refill never exceeds the burst */
    ASSERT_EQ(break_msg_rate_admit(&r, 1u, 100000u), BREAK_MSG_RATE_OK);
    ASSERT_EQ(break_msg_rate_messages_available(&r), 4u);
    ASSERT_EQ(break_msg_rate_denied(&r), 3u);
}

TEST(bytes_are_limited_independently)
{
    BreakMsgRate r;
    ASSERT_TRUE(break_msg_rate_init(&r, 1000u, 1000u, 1000u, 400u, 0u));
    ASSERT_EQ(break_msg_rate_admit(&r, 300u, 0u), BREAK_MSG_RATE_OK);
    /* 100 bytes left: a 200-byte message is refused and costs nothing */
    ASSERT_EQ(break_msg_rate_admit(&r, 200u, 0u), BREAK_MSG_RATE_BYTES);
    ASSERT_EQ(break_msg_rate_admit(&r, 100u, 0u), BREAK_MSG_RATE_OK);
    ASSERT_EQ(break_msg_rate_messages_available(&r), 998u);
    /* larger than the whole byte burst: never admissible */
    ASSERT_EQ(break_msg_rate_admit(&r, 401u, 1000000u), BREAK_MSG_RATE_BYTES);
    /* 200 ms -> 200 bytes back */
    ASSERT_TRUE(break_msg_rate_init(&r, 1000u, 1000u, 1000u, 400u, 0u));
    ASSERT_EQ(break_msg_rate_admit(&r, 400u, 0u), BREAK_MSG_RATE_OK);
    ASSERT_EQ(break_msg_rate_admit(&r, 200u, 200u), BREAK_MSG_RATE_OK);
    ASSERT_EQ(break_msg_rate_admit(&r, 1u, 200u), BREAK_MSG_RATE_BYTES);
}

TEST(fractional_refill_accumulates_and_time_never_runs_backwards)
{
    BreakMsgRate r;
    /* 3 msgs/s: one token every 333.3 ms; 10 calls 40 ms apart = 400 ms */
    ASSERT_TRUE(break_msg_rate_init(&r, 3u, 1u, 1000000u, 1000000u, 0u));
    ASSERT_EQ(break_msg_rate_admit(&r, 1u, 0u), BREAK_MSG_RATE_OK);
    u32 ok = 0u;
    for (u64 t = 40u; t <= 400u; t += 40u) {
        if (break_msg_rate_admit(&r, 1u, t) == BREAK_MSG_RATE_OK) ok++;
    }
    ASSERT_EQ(ok, 1u); /* the remainder is kept, not dropped per call */
    /* a clock going backwards adds nothing and does not underflow */
    ASSERT_EQ(break_msg_rate_admit(&r, 1u, 10u), BREAK_MSG_RATE_MESSAGES);
    ASSERT_EQ(break_msg_rate_admit(&r, 1u, 734u), BREAK_MSG_RATE_OK);
}

TEST(bad_configuration_is_rejected)
{
    BreakMsgRate r;
    ASSERT_FALSE(break_msg_rate_init(NULL, 1u, 1u, 1u, 1u, 0u));
    ASSERT_FALSE(break_msg_rate_init(&r, 0u, 1u, 1u, 1u, 0u));
    ASSERT_FALSE(break_msg_rate_init(&r, 1u, 0u, 1u, 1u, 0u));
    ASSERT_FALSE(break_msg_rate_init(&r, 1u, 1u, 0u, 1u, 0u));
    ASSERT_FALSE(break_msg_rate_init(&r, 1u, 1u, 1u, 0u, 0u));
    ASSERT_EQ(break_msg_rate_admit(NULL, 1u, 0u), BREAK_MSG_RATE_INVALID);
    /* huge rates and a far-future clock do not overflow */
    ASSERT_TRUE(break_msg_rate_init(&r, UINT32_MAX, UINT32_MAX, UINT32_MAX,
                                    UINT32_MAX, 0u));
    ASSERT_EQ(break_msg_rate_admit(&r, UINT32_MAX, UINT64_MAX), BREAK_MSG_RATE_OK);
    ASSERT_EQ(break_msg_rate_messages_available(&r), UINT32_MAX - 1u);
}

TEST_MAIN_BEGIN()
    RUN_TEST(burst_then_refill_by_elapsed_time);
    RUN_TEST(bytes_are_limited_independently);
    RUN_TEST(fractional_refill_accumulates_and_time_never_runs_backwards);
    RUN_TEST(bad_configuration_is_rejected);
TEST_MAIN_END()
