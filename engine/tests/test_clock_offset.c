#include "test_framework.h"

#include <core/clock_offset.h>

#include <stdint.h>

static ClockOffsetSample sample(u64 t0, u64 t1, u64 t2, u64 t3)
{
    ClockOffsetSample s = {t0, t1, t2, t3};
    return s;
}

/* A probe with B = A + offset, one-way delays `out` and `back`, hold time
 * `hold`, sent at A time `at`. */
static ClockOffsetSample probe(u64 at, i64 offset, u64 out, u64 back, u64 hold)
{
    u64 t1 = (u64)((i64)(at + out) + offset);
    return sample(at, t1, t1 + hold, at + out + hold + back);
}

TEST(clock_offset_measures_offset_and_delay)
{
    ClockOffsetMeasure m;
    ClockOffsetSample s = probe(1000u, 5000, 40u, 40u, 7u);
    ASSERT_EQ(clock_offset_measure(&s, &m), CLOCK_OFFSET_OK);
    ASSERT_EQ(m.offset_us, 5000);
    ASSERT_EQ(m.delay_us, 80);

    s = probe(100000u, -30000, 10u, 10u, 0u);
    ASSERT_EQ(clock_offset_measure(&s, &m), CLOCK_OFFSET_OK);
    ASSERT_EQ(m.offset_us, -30000);
    ASSERT_EQ(m.delay_us, 20);

    s = sample(0u, 2u, 2u, 1u); /* sum 3 -> 1 */
    ASSERT_EQ(clock_offset_measure(&s, &m), CLOCK_OFFSET_OK);
    ASSERT_EQ(m.offset_us, 1);
    ASSERT_EQ(m.delay_us, 1);
    s = sample(10u, 6u, 6u, 13u); /* sum -4 + -7 = -11 -> -6 */
    ASSERT_EQ(clock_offset_measure(&s, &m), CLOCK_OFFSET_OK);
    ASSERT_EQ(m.offset_us, -6);
    ASSERT_EQ(m.delay_us, 3);
    s = sample(0u, CLOCK_OFFSET_MAX_US, CLOCK_OFFSET_MAX_US, 0u);
    ASSERT_EQ(clock_offset_measure(&s, &m), CLOCK_OFFSET_OK);
    ASSERT_EQ(m.offset_us, (i64)CLOCK_OFFSET_MAX_US);
    ASSERT_EQ(m.delay_us, 0);
}

TEST(clock_offset_rejects_impossible_samples)
{
    ClockOffsetMeasure m = {77, 77};
    ClockOffsetSample bad[] = {
        sample(10u, 0u, 0u, 9u),                     /* t3 < t0 */
        sample(0u, 10u, 9u, 20u),                    /* t2 < t1 */
        sample(0u, 100u, 200u, 50u),                 /* hold longer than the round trip */
        sample(CLOCK_OFFSET_MAX_US + 1u, 0u, 0u, CLOCK_OFFSET_MAX_US + 2u),
        sample(0u, CLOCK_OFFSET_MAX_US + 1u, CLOCK_OFFSET_MAX_US + 1u, 1u),
        sample(0u, 0u, CLOCK_OFFSET_MAX_US + 1u, CLOCK_OFFSET_MAX_US + 2u),
        sample(0u, 0u, 0u, CLOCK_OFFSET_MAX_US + 1u),
    };
    for (usize i = 0; i < sizeof bad / sizeof bad[0]; ++i) {
        ASSERT_EQ(clock_offset_measure(&bad[i], &m), CLOCK_OFFSET_INVALID);
        ASSERT_EQ(m.offset_us, 77);
    }
    ASSERT_EQ(clock_offset_measure(NULL, &m), CLOCK_OFFSET_INVALID);
    ASSERT_EQ(clock_offset_measure(&bad[0], NULL), CLOCK_OFFSET_INVALID);

    ClockOffsetEstimator e;
    ClockOffsetEstimate est;
    clock_offset_init(&e);
    ASSERT_EQ(clock_offset_estimate(&e, &est), CLOCK_OFFSET_EMPTY);
    ASSERT_EQ(clock_offset_add(&e, &bad[0]), CLOCK_OFFSET_INVALID);
    ASSERT_EQ(e.rejected, 1u);
    ASSERT_EQ(clock_offset_estimate(&e, &est), CLOCK_OFFSET_EMPTY);
    ClockOffsetSample good = probe(0u, 300, 5u, 5u, 1u);
    ASSERT_EQ(clock_offset_add(&e, &good), CLOCK_OFFSET_OK);
    ASSERT_EQ(clock_offset_add(&e, &bad[1]), CLOCK_OFFSET_INVALID);
    ASSERT_EQ(e.rejected, 2u);
    ASSERT_EQ(clock_offset_estimate(&e, &est), CLOCK_OFFSET_OK);
    ASSERT_EQ(est.offset_us, 300);
    ASSERT_EQ(est.samples, 1u);
    ASSERT_EQ(clock_offset_add(NULL, &good), CLOCK_OFFSET_INVALID);
    ASSERT_EQ(clock_offset_add(&e, NULL), CLOCK_OFFSET_INVALID);
    ASSERT_EQ(clock_offset_estimate(NULL, &est), CLOCK_OFFSET_INVALID);
    ASSERT_EQ(clock_offset_estimate(&e, NULL), CLOCK_OFFSET_INVALID);
}

TEST(clock_offset_picks_the_lowest_delay_in_a_sliding_window)
{
    ClockOffsetEstimator e;
    ClockOffsetEstimate est;
    clock_offset_init(&e);
    /* the true offset is 1000; delay asymmetry skews the noisy samples */
    ClockOffsetSample a = probe(0u, 1000, 10u, 400u, 0u); /* delay 410 */
    ClockOffsetSample b = probe(1000u, 1000, 3u, 3u, 2u); /* delay 6, exact */
    ClockOffsetSample c = probe(2000u, 1000, 300u, 20u, 0u);
    ASSERT_EQ(clock_offset_add(&e, &a), CLOCK_OFFSET_OK);
    ASSERT_EQ(clock_offset_add(&e, &b), CLOCK_OFFSET_OK);
    ASSERT_EQ(clock_offset_add(&e, &c), CLOCK_OFFSET_OK);
    ASSERT_EQ(clock_offset_estimate(&e, &est), CLOCK_OFFSET_OK);
    ASSERT_EQ(est.offset_us, 1000);
    ASSERT_EQ(est.delay_us, 6);
    ASSERT_EQ(est.error_us, 3u);
    ASSERT_EQ(est.samples, 3u);

    /* equal delay: the newer sample wins */
    ClockOffsetSample tie = sample(3000u, 4005u, 4005u, 3006u); /* delay 6, offset 1002 */
    ASSERT_EQ(clock_offset_add(&e, &tie), CLOCK_OFFSET_OK);
    ASSERT_EQ(clock_offset_estimate(&e, &est), CLOCK_OFFSET_OK);
    ASSERT_EQ(est.offset_us, 1002);

    /* five more noisy samples push b and tie out of the 8-sample window */
    for (u32 i = 0; i < 5u; ++i) {
        ClockOffsetSample n = probe(10000u + i * 1000u, 1000, 50u + i, 50u, 0u);
        ASSERT_EQ(clock_offset_add(&e, &n), CLOCK_OFFSET_OK);
    }
    ASSERT_EQ(e.count, CLOCK_OFFSET_WINDOW);
    ASSERT_EQ(clock_offset_estimate(&e, &est), CLOCK_OFFSET_OK);
    ASSERT_EQ(est.offset_us, 1002); /* a, b, c, tie, n0..n4: a was evicted, tie is still inside */
    ClockOffsetSample n5 = probe(20000u, 1000, 60u, 60u, 0u);
    ASSERT_EQ(clock_offset_add(&e, &n5), CLOCK_OFFSET_OK); /* evicts b */
    ASSERT_EQ(clock_offset_estimate(&e, &est), CLOCK_OFFSET_OK);
    ASSERT_EQ(est.offset_us, 1002);
    ClockOffsetSample n6 = probe(21000u, 1000, 70u, 70u, 0u);
    ASSERT_EQ(clock_offset_add(&e, &n6), CLOCK_OFFSET_OK); /* evicts c */
    ClockOffsetSample n7 = probe(22000u, 1000, 70u, 70u, 0u);
    ASSERT_EQ(clock_offset_add(&e, &n7), CLOCK_OFFSET_OK); /* evicts tie */
    ASSERT_EQ(clock_offset_estimate(&e, &est), CLOCK_OFFSET_OK);
    ASSERT_EQ(est.delay_us, 100); /* n0: 50 + 50 */
    ASSERT_EQ(est.offset_us, 1000);
    ASSERT_EQ(est.error_us, 50u);
    ASSERT_EQ(est.samples, CLOCK_OFFSET_WINDOW);
}

TEST(clock_offset_error_bound_covers_any_delay_split)
{
    static const u64 splits[][2] = {{0u, 101u}, {101u, 0u}, {50u, 51u}, {1u, 1u}, {7u, 0u}};
    for (usize i = 0; i < sizeof splits / sizeof splits[0]; ++i) {
        ClockOffsetEstimator e;
        ClockOffsetEstimate est;
        clock_offset_init(&e);
        ClockOffsetSample s = probe(10000u, -2500, splits[i][0], splits[i][1], 9u);
        ASSERT_EQ(clock_offset_add(&e, &s), CLOCK_OFFSET_OK);
        ASSERT_EQ(clock_offset_estimate(&e, &est), CLOCK_OFFSET_OK);
        i64 miss = est.offset_us - (-2500);
        if (miss < 0) miss = -miss;
        ASSERT_TRUE((u64)miss <= est.error_us);
        ASSERT_EQ(est.error_us, (u64)((splits[i][0] + splits[i][1] + 1u) / 2u));
    }
}

TEST(clock_offset_merge_shifts_are_non_negative)
{
    u64 a = 9u, b = 9u;
    clock_offset_merge_shifts(1500, &a, &b);
    ASSERT_EQ(a, 1500u);
    ASSERT_EQ(b, 0u);
    clock_offset_merge_shifts(-1500, &a, &b);
    ASSERT_EQ(a, 0u);
    ASSERT_EQ(b, 1500u);
    clock_offset_merge_shifts(0, &a, &b);
    ASSERT_EQ(a, 0u);
    ASSERT_EQ(b, 0u);
    clock_offset_merge_shifts(INT64_MIN, &a, &b);
    ASSERT_EQ(a, 0u);
    ASSERT_EQ(b, (u64)1u << 63);
    clock_offset_merge_shifts(INT64_MAX, &a, &b);
    ASSERT_EQ(a, (u64)INT64_MAX);
    ASSERT_EQ(b, 0u);
}

/* offset_i is peer i minus the server: every input lands on the server's
 * timeline moved by max(0, max offset_i) */
TEST(clock_offset_merge_shifts_many_aligns_every_peer)
{
    const i64 mixed[3] = {-500, 300, 0};
    u64 server = 9u;
    u64 peers[3] = {9u, 9u, 9u};
    ASSERT_TRUE(clock_offset_merge_shifts_many(mixed, 3u, &server, peers));
    ASSERT_EQ(server, 300u);
    ASSERT_EQ(peers[0], 800u);
    ASSERT_EQ(peers[1], 0u);
    ASSERT_EQ(peers[2], 300u);
    const i64 behind[2] = {-40, -7};
    ASSERT_TRUE(clock_offset_merge_shifts_many(behind, 2u, &server, peers));
    ASSERT_EQ(server, 0u);
    ASSERT_EQ(peers[0], 40u);
    ASSERT_EQ(peers[1], 7u);
    const i64 ahead[2] = {40, 7};
    ASSERT_TRUE(clock_offset_merge_shifts_many(ahead, 2u, &server, peers));
    ASSERT_EQ(server, 40u);
    ASSERT_EQ(peers[0], 0u);
    ASSERT_EQ(peers[1], 33u);
    const i64 extremes[2] = {INT64_MIN, INT64_MAX};
    ASSERT_TRUE(clock_offset_merge_shifts_many(extremes, 2u, &server, peers));
    ASSERT_EQ(server, (u64)INT64_MAX);
    ASSERT_EQ(peers[0], UINT64_MAX);
    ASSERT_EQ(peers[1], 0u);
}

TEST(clock_offset_merge_shifts_many_matches_the_two_input_helper)
{
    const i64 cases[5] = {1500, -1500, 0, INT64_MIN, INT64_MAX};
    for (u32 i = 0u; i < 5u; ++i) {
        u64 a = 1u, b = 1u, server = 2u, peer = 2u;
        clock_offset_merge_shifts(cases[i], &a, &b);
        ASSERT_TRUE(clock_offset_merge_shifts_many(&cases[i], 1u, &server, &peer));
        ASSERT_EQ(server, a);
        ASSERT_EQ(peer, b);
    }
}

TEST(clock_offset_merge_shifts_many_refuses_bad_arguments)
{
    const i64 one[1] = {5};
    u64 server = 9u;
    u64 peer = 9u;
    ASSERT_TRUE(!clock_offset_merge_shifts_many(NULL, 1u, &server, &peer));
    ASSERT_TRUE(!clock_offset_merge_shifts_many(one, 0u, &server, &peer));
    ASSERT_TRUE(!clock_offset_merge_shifts_many(one, 1u, NULL, &peer));
    ASSERT_TRUE(!clock_offset_merge_shifts_many(one, 1u, &server, NULL));
    ASSERT_EQ(server, 9u);
    ASSERT_EQ(peer, 9u);
}

TEST_MAIN_BEGIN()
    RUN_TEST(clock_offset_measures_offset_and_delay);
    RUN_TEST(clock_offset_rejects_impossible_samples);
    RUN_TEST(clock_offset_picks_the_lowest_delay_in_a_sliding_window);
    RUN_TEST(clock_offset_error_bound_covers_any_delay_split);
    RUN_TEST(clock_offset_merge_shifts_are_non_negative);
    RUN_TEST(clock_offset_merge_shifts_many_aligns_every_peer);
    RUN_TEST(clock_offset_merge_shifts_many_matches_the_two_input_helper);
    RUN_TEST(clock_offset_merge_shifts_many_refuses_bad_arguments);
TEST_MAIN_END()
