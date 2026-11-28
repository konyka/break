/* Per-identity message/byte rate limit shared across connections. */
#include "test_framework.h"

#include <string.h>

#include <network/break_identity_rate.h>

static const u8 kA[8] = {'u', 's', 'e', 'r', '-', '0', '0', 'A'};
static const u8 kB[8] = {'u', 's', 'e', 'r', '-', '0', '0', 'B'};

static BreakIdentityRateConfig small_config(void)
{
    BreakIdentityRateConfig c;
    c.msg_per_sec = 10u;
    c.msg_burst = 2u;
    c.byte_per_sec = 1000u;
    c.byte_burst = 100u;
    c.max_identities = 4u;
    c.idle_ms = 10000u;
    return c;
}

TEST(identity_buckets_survive_reconnects)
{
    /* the same identity on two connections draws from one bucket, so a
     * reconnect does not refill it */
    BreakIdentityRateConfig c = small_config();
    BreakIdentityRate *r = break_identity_rate_create(&c);
    ASSERT_NOT_NULL(r);
    ASSERT_EQ(break_identity_rate_admit(r, kA, 1u, 0u), BREAK_MSG_RATE_OK);
    ASSERT_EQ(break_identity_rate_admit(r, kA, 1u, 0u), BREAK_MSG_RATE_OK);
    ASSERT_EQ(break_identity_rate_admit(r, kA, 1u, 0u), BREAK_MSG_RATE_MESSAGES);
    /* another identity has its own bucket */
    ASSERT_EQ(break_identity_rate_admit(r, kB, 1u, 0u), BREAK_MSG_RATE_OK);
    /* 100 ms refills one message token for A */
    ASSERT_EQ(break_identity_rate_admit(r, kA, 1u, 99u), BREAK_MSG_RATE_MESSAGES);
    ASSERT_EQ(break_identity_rate_admit(r, kA, 1u, 100u), BREAK_MSG_RATE_OK);
    ASSERT_EQ(break_identity_rate_count(r), 2u);
    ASSERT_EQ(break_identity_rate_denied(r), 2u);
    break_identity_rate_destroy(r);
}

TEST(identity_byte_bucket_is_independent)
{
    BreakIdentityRateConfig c = small_config();
    BreakIdentityRate *r = break_identity_rate_create(&c);
    ASSERT_NOT_NULL(r);
    ASSERT_EQ(break_identity_rate_admit(r, kA, 64u, 0u), BREAK_MSG_RATE_OK);
    ASSERT_EQ(break_identity_rate_admit(r, kA, 64u, 0u), BREAK_MSG_RATE_BYTES);
    break_identity_rate_destroy(r);
}

TEST(identity_table_is_bounded_and_fails_closed)
{
    /* a full table refuses a new identity (FULL) instead of evicting a
     * live one, so a flood of fresh identities cannot reset limits */
    BreakIdentityRateConfig c = small_config();
    BreakIdentityRate *r;
    u8 key[8] = {0};
    u32 i;
    c.max_identities = 3u;
    r = break_identity_rate_create(&c);
    ASSERT_NOT_NULL(r);
    for (i = 0u; i < 3u; i++) {
        key[0] = (u8)(i + 1u);
        ASSERT_EQ(break_identity_rate_admit(r, key, 1u, 0u), BREAK_MSG_RATE_OK);
    }
    key[0] = 9u;
    ASSERT_EQ(break_identity_rate_admit(r, key, 1u, 0u), BREAK_IDENTITY_RATE_FULL);
    ASSERT_EQ(break_identity_rate_count(r), 3u);
    /* the refusal is counted as a denial */
    ASSERT_EQ(break_identity_rate_denied(r), 1u);
    /* a known identity still resolves */
    key[0] = 1u;
    ASSERT_EQ(break_identity_rate_admit(r, key, 1u, 0u), BREAK_MSG_RATE_OK);
    break_identity_rate_destroy(r);
}

TEST(idle_identities_are_reclaimed)
{
    /* an identity idle for idle_ms frees its slot for a new one; an active
     * identity keeps its slot and its (drained) bucket */
    BreakIdentityRateConfig c = small_config();
    BreakIdentityRate *r;
    u8 key[8] = {0};
    c.max_identities = 2u;
    c.idle_ms = 1000u;
    r = break_identity_rate_create(&c);
    ASSERT_NOT_NULL(r);
    ASSERT_EQ(break_identity_rate_admit(r, kA, 1u, 0u), BREAK_MSG_RATE_OK);
    ASSERT_EQ(break_identity_rate_admit(r, kA, 1u, 0u), BREAK_MSG_RATE_OK);
    ASSERT_EQ(break_identity_rate_admit(r, kB, 1u, 500u), BREAK_MSG_RATE_OK);
    key[0] = 7u;
    /* at 999 ms A is not yet idle long enough: still full */
    ASSERT_EQ(break_identity_rate_admit(r, key, 1u, 999u), BREAK_IDENTITY_RATE_FULL);
    /* at 1000 ms A has been idle for idle_ms: its slot is reclaimed */
    ASSERT_EQ(break_identity_rate_admit(r, key, 1u, 1000u), BREAK_MSG_RATE_OK);
    ASSERT_EQ(break_identity_rate_count(r), 2u);
    /* B was active at 500 ms and was kept */
    ASSERT_EQ(break_identity_rate_admit(r, kB, 1u, 1000u), BREAK_MSG_RATE_OK);
    break_identity_rate_destroy(r);
}

TEST(every_message_keeps_an_identity_active)
{
    /* A sends at 0 and again at 900 ms (refused by its drained bucket, but
     * still activity). At 1500 ms A has been quiet for only 600 ms, so its
     * slot is not reclaimed even though its first message was 1500 ms ago. */
    BreakIdentityRateConfig c = small_config();
    BreakIdentityRate *r;
    u8 key[8] = {0};
    c.max_identities = 1u;
    c.idle_ms = 1000u;
    c.msg_per_sec = 1u;
    c.msg_burst = 1u;
    r = break_identity_rate_create(&c);
    ASSERT_NOT_NULL(r);
    ASSERT_EQ(break_identity_rate_admit(r, kA, 1u, 0u), BREAK_MSG_RATE_OK);
    ASSERT_EQ(break_identity_rate_admit(r, kA, 1u, 900u), BREAK_MSG_RATE_MESSAGES);
    key[0] = 7u;
    ASSERT_EQ(break_identity_rate_admit(r, key, 1u, 1500u), BREAK_IDENTITY_RATE_FULL);
    break_identity_rate_destroy(r);
}

TEST(a_reclaimed_slot_starts_with_full_buckets)
{
    /* A drains its bucket and goes idle; the slot is taken by C, which
     * must get the full burst, not A's empty bucket. */
    BreakIdentityRateConfig c = small_config();
    BreakIdentityRate *r;
    u8 key[8] = {0};
    c.max_identities = 1u;
    c.idle_ms = 1000u;
    c.msg_per_sec = 1u;
    c.msg_burst = 2u;
    r = break_identity_rate_create(&c);
    ASSERT_NOT_NULL(r);
    ASSERT_EQ(break_identity_rate_admit(r, kA, 1u, 0u), BREAK_MSG_RATE_OK);
    ASSERT_EQ(break_identity_rate_admit(r, kA, 1u, 0u), BREAK_MSG_RATE_OK);
    key[0] = 3u;
    /* one second of refill would give A's old bucket one token, not two */
    ASSERT_EQ(break_identity_rate_admit(r, key, 1u, 1000u), BREAK_MSG_RATE_OK);
    ASSERT_EQ(break_identity_rate_admit(r, key, 1u, 1000u), BREAK_MSG_RATE_OK);
    ASSERT_EQ(break_identity_rate_admit(r, key, 1u, 1000u), BREAK_MSG_RATE_MESSAGES);
    break_identity_rate_destroy(r);
}

TEST(identity_rate_rejects_bad_configuration_and_arguments)
{
    BreakIdentityRateConfig c = small_config();
    BreakIdentityRate *r;
    ASSERT_TRUE(break_identity_rate_create(NULL) == NULL);
    c.msg_per_sec = 0u;
    ASSERT_TRUE(break_identity_rate_create(&c) == NULL);
    c = small_config();
    c.byte_burst = 0u;
    ASSERT_TRUE(break_identity_rate_create(&c) == NULL);
    c = small_config();
    c.max_identities = 0u;
    ASSERT_TRUE(break_identity_rate_create(&c) == NULL);
    c.max_identities = BREAK_IDENTITY_RATE_MAX_IDENTITIES + 1u;
    ASSERT_TRUE(break_identity_rate_create(&c) == NULL);
    c.max_identities = BREAK_IDENTITY_RATE_MAX_IDENTITIES;
    r = break_identity_rate_create(&c);
    ASSERT_NOT_NULL(r);
    ASSERT_EQ(break_identity_rate_admit(r, NULL, 1u, 0u), BREAK_MSG_RATE_INVALID);
    ASSERT_EQ(break_identity_rate_admit(NULL, kA, 1u, 0u), BREAK_MSG_RATE_INVALID);
    ASSERT_EQ(break_identity_rate_count(NULL), 0u);
    ASSERT_EQ(break_identity_rate_denied(NULL), 0u);
    break_identity_rate_destroy(r);
    break_identity_rate_destroy(NULL);
}

TEST_MAIN_BEGIN()
    RUN_TEST(identity_buckets_survive_reconnects);
    RUN_TEST(identity_byte_bucket_is_independent);
    RUN_TEST(identity_table_is_bounded_and_fails_closed);
    RUN_TEST(idle_identities_are_reclaimed);
    RUN_TEST(every_message_keeps_an_identity_active);
    RUN_TEST(a_reclaimed_slot_starts_with_full_buckets);
    RUN_TEST(identity_rate_rejects_bad_configuration_and_arguments);
TEST_MAIN_END()
