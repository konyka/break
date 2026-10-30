/* break_authority: the server-side reference engine. Intents come in, the
 * server's own ledgers decide, and a fixed verdict comes out. The client
 * never supplies a result (no damage value, no balance, no item count). */

#include "test_framework.h"

#include <authority/break_authority.h>

#include <stdint.h>
#include <string.h>

#define NOW_US(ms) ((u64)(ms) * 1000u)

#define PRICE_ITEM1 10
#define HUGE_ITEM 64u

/* The item table belongs to the game server: the library has none built in. */
static BreakAuthority *make(void) {
    BreakAuthority *a = break_authority_create(8u);
    if (a == NULL) return NULL;
    if (!break_authority_define_item(a, 1u, PRICE_ITEM1) ||
        !break_authority_define_item(a, 2u, 25) ||
        !break_authority_define_item(a, 3u, 100) ||
        !break_authority_define_item(a, 4u, 1000) ||
        !break_authority_define_item(a, HUGE_ITEM, INT64_MAX / 2)) {
        break_authority_destroy(a);
        return NULL;
    }
    return a;
}

TEST(item_table_is_server_defined_and_bounded) {
    BreakAuthority *a = break_authority_create(2u);
    ASSERT_NOT_NULL(a);
    ASSERT_FALSE(break_authority_define_item(a, 0u, 5));       /* id 0 is reserved */
    ASSERT_FALSE(break_authority_define_item(a, 1u, 0));       /* price must be positive */
    ASSERT_FALSE(break_authority_define_item(a, 1u, -3));
    ASSERT_TRUE(break_authority_define_item(a, 1u, 5));
    ASSERT_FALSE(break_authority_define_item(a, 1u, 6));       /* no silent re-pricing */
    ASSERT_EQ(break_authority_item_price(a, 1u), 5);
    ASSERT_EQ(break_authority_item_price(a, 2u), 0);           /* undefined = 0 */
    for (u32 id = 2u; id <= BREAK_AUTHORITY_MAX_ITEMS; id++) {
        ASSERT_TRUE(break_authority_define_item(a, id, 1));
    }
    ASSERT_FALSE(break_authority_define_item(a, BREAK_AUTHORITY_MAX_ITEMS + 1u, 1)); /* table full */
    ASSERT_FALSE(break_authority_define_item(NULL, 5u, 1));
    break_authority_destroy(a);
}

TEST(create_bounds_and_session_lifecycle) {
    BreakAuthority *a;
    ASSERT_TRUE(break_authority_create(0u) == NULL);
    ASSERT_TRUE(break_authority_create(BREAK_AUTHORITY_MAX_SESSIONS + 1u) == NULL);
    a = make();
    ASSERT_NOT_NULL(a);
    ASSERT_TRUE(break_authority_open_session(a, 1u, 100));
    ASSERT_FALSE(break_authority_open_session(a, 1u, 100));    /* duplicate id */
    ASSERT_FALSE(break_authority_open_session(a, 0u, 100));    /* 0 is reserved */
    ASSERT_FALSE(break_authority_open_session(a, 2u, -1));     /* negative start */
    ASSERT_EQ(break_authority_balance(a, 1u), 100);
    ASSERT_EQ(break_authority_health(a, 1u), BREAK_AUTHORITY_START_HEALTH);
    break_authority_close_session(a, 1u);
    ASSERT_EQ(break_authority_balance(a, 1u), -1);              /* unknown session */
    ASSERT_TRUE(break_authority_open_session(a, 1u, 5));        /* id can be reused after close */
    ASSERT_EQ(break_authority_balance(a, 1u), 5);               /* with a fresh ledger */
    /* table full */
    for (u64 id = 2u; id <= 8u; id++) ASSERT_TRUE(break_authority_open_session(a, id, 0));
    ASSERT_FALSE(break_authority_open_session(a, 9u, 0));
    break_authority_destroy(a);
    break_authority_destroy(NULL);
    ASSERT_EQ(break_authority_balance(NULL, 1u), -1);
}

TEST(spend_deducts_server_price_and_adds_the_item) {
    BreakAuthority *a = make();
    ASSERT_NOT_NULL(a);
    ASSERT_TRUE(break_authority_open_session(a, 1u, 1000));
    /* item 1 costs PRICE_ITEM1 per unit in the server's table */
    ASSERT_EQ(break_authority_intent_spend(a, 1u, 1u, 1u, 3u, NOW_US(0)), BAUTH_OK);
    ASSERT_EQ(break_authority_balance(a, 1u), 1000 - 3 * PRICE_ITEM1);
    ASSERT_EQ(break_authority_item_count(a, 1u, 1u), 3u);
    ASSERT_EQ(break_authority_item_count(a, 1u, 2u), 0u);
    break_authority_destroy(a);
}

TEST(spend_denials_change_nothing) {
    BreakAuthority *a = make();
    ASSERT_NOT_NULL(a);
    ASSERT_TRUE(break_authority_open_session(a, 1u, 50));
    u32 afford = (u32)(50 / PRICE_ITEM1);
    /* not enough funds */
    ASSERT_EQ(break_authority_intent_spend(a, 1u, 1u, 1u, afford + 1u, NOW_US(0)), BAUTH_DENIED_FUNDS);
    ASSERT_EQ(break_authority_balance(a, 1u), 50);
    ASSERT_EQ(break_authority_item_count(a, 1u, 1u), 0u);
    /* zero and over-cap quantities */
    ASSERT_EQ(break_authority_intent_spend(a, 1u, 2u, 1u, 0u, NOW_US(0)), BAUTH_DENIED_LIMIT);
    ASSERT_EQ(break_authority_intent_spend(a, 1u, 3u, 1u, BREAK_AUTHORITY_MAX_QTY + 1u, NOW_US(0)), BAUTH_DENIED_LIMIT);
    /* unknown item */
    ASSERT_EQ(break_authority_intent_spend(a, 1u, 4u, 0xffffu, 1u, NOW_US(0)), BAUTH_DENIED_INVALID);
    /* unknown session */
    ASSERT_EQ(break_authority_intent_spend(a, 99u, 1u, 1u, 1u, NOW_US(0)), BAUTH_DENIED_NO_SESSION);
    ASSERT_EQ(break_authority_balance(a, 1u), 50);
    /* a denied intent still consumed its sequence number: replaying it is a replay */
    ASSERT_EQ(break_authority_intent_spend(a, 1u, 1u, 1u, 1u, NOW_US(0)), BAUTH_DENIED_REPLAY);
    break_authority_destroy(a);
}

TEST(price_times_quantity_overflow_is_denied_not_wrapped) {
    BreakAuthority *a = make();
    ASSERT_NOT_NULL(a);
    ASSERT_TRUE(break_authority_open_session(a, 1u, INT64_MAX));
    /* HUGE_ITEM costs INT64_MAX/2 per unit: qty 3 already exceeds i64 */
    ASSERT_EQ(break_authority_intent_spend(a, 1u, 1u, HUGE_ITEM, 3u, NOW_US(0)),
              BAUTH_DENIED_INVALID);
    ASSERT_EQ(break_authority_intent_spend(a, 1u, 2u, HUGE_ITEM, BREAK_AUTHORITY_MAX_QTY, NOW_US(0)),
              BAUTH_DENIED_INVALID);
    /* qty 2 is exactly INT64_MAX - 1: representable, so a plain funds check */
    ASSERT_EQ(break_authority_intent_spend(a, 1u, 3u, HUGE_ITEM, 2u, NOW_US(0)), BAUTH_OK);
    ASSERT_EQ(break_authority_balance(a, 1u), INT64_MAX - (INT64_MAX / 2) * 2);
    /* a grant that would overflow the balance is refused too */
    ASSERT_TRUE(break_authority_open_session(a, 2u, INT64_MAX));
    ASSERT_EQ(break_authority_grant_server(a, 2u, 1), BAUTH_DENIED_LIMIT);
    ASSERT_EQ(break_authority_balance(a, 2u), INT64_MAX);
    ASSERT_EQ(break_authority_grant_server(a, 2u, -1), BAUTH_DENIED_INVALID); /* grants are non-negative */
    break_authority_destroy(a);
}

TEST(sequence_replay_and_gap_rules) {
    BreakAuthority *a = make();
    ASSERT_NOT_NULL(a);
    ASSERT_TRUE(break_authority_open_session(a, 1u, 100000));
    ASSERT_EQ(break_authority_intent_spend(a, 1u, 0u, 1u, 1u, NOW_US(0)), BAUTH_DENIED_INVALID); /* seq 0 reserved */
    ASSERT_EQ(break_authority_intent_spend(a, 1u, 5u, 1u, 1u, NOW_US(0)), BAUTH_OK);
    ASSERT_EQ(break_authority_intent_spend(a, 1u, 5u, 1u, 1u, NOW_US(0)), BAUTH_DENIED_REPLAY);
    ASSERT_EQ(break_authority_intent_spend(a, 1u, 7u, 1u, 1u, NOW_US(1)), BAUTH_OK);     /* out of order inside the window */
    ASSERT_EQ(break_authority_intent_spend(a, 1u, 6u, 1u, 1u, NOW_US(2)), BAUTH_OK);     /* late but fresh */
    ASSERT_EQ(break_authority_intent_spend(a, 1u, 6u, 1u, 1u, NOW_US(3)), BAUTH_DENIED_REPLAY);
    /* a jump past the allowed gap is refused and does not move the window */
    ASSERT_EQ(break_authority_intent_spend(a, 1u, 7u + BREAK_AUTHORITY_MAX_GAP + 1u, 1u, 1u, NOW_US(4)), BAUTH_DENIED_GAP);
    ASSERT_EQ(break_authority_intent_spend(a, 1u, 8u, 1u, 1u, NOW_US(5)), BAUTH_OK);
    /* a very old number is too old to tell apart from a replay */
    ASSERT_EQ(break_authority_intent_spend(a, 1u, 8u + 200u, 1u, 1u, NOW_US(6)), BAUTH_OK);
    ASSERT_EQ(break_authority_intent_spend(a, 1u, 9u, 1u, 1u, NOW_US(7)), BAUTH_DENIED_REPLAY);
    /* sequence numbers are per session */
    ASSERT_TRUE(break_authority_open_session(a, 2u, 100000));
    ASSERT_EQ(break_authority_intent_spend(a, 2u, 5u, 1u, 1u, NOW_US(8)), BAUTH_OK);
    break_authority_destroy(a);
}

TEST(rate_limit_uses_the_injected_clock) {
    BreakAuthority *a = make();
    ASSERT_NOT_NULL(a);
    ASSERT_TRUE(break_authority_open_session(a, 1u, 1000000));
    u64 seq = 1u;
    u32 ok = 0u;
    /* a burst at one instant: at most BREAK_AUTHORITY_RATE_BURST pass */
    for (u32 i = 0u; i < BREAK_AUTHORITY_RATE_BURST + 5u; i++) {
        BreakAuthVerdict v = break_authority_intent_spend(a, 1u, seq++, 1u, 1u, NOW_US(1000));
        if (v == BAUTH_OK) ok++;
        else ASSERT_EQ(v, BAUTH_DENIED_RATE);
    }
    ASSERT_EQ(ok, BREAK_AUTHORITY_RATE_BURST);
    /* a denied-by-rate intent costs no funds and no item */
    ASSERT_EQ(break_authority_item_count(a, 1u, 1u), BREAK_AUTHORITY_RATE_BURST);
    /* after a second the bucket refills */
    ASSERT_EQ(break_authority_intent_spend(a, 1u, seq++, 1u, 1u, NOW_US(2500)), BAUTH_OK);
    /* the clock going backwards refills nothing */
    for (int i = 0; i < 40; i++) (void)break_authority_intent_spend(a, 1u, seq++, 1u, 1u, NOW_US(2500));
    ASSERT_EQ(break_authority_intent_spend(a, 1u, seq++, 1u, 1u, NOW_US(1)), BAUTH_DENIED_RATE);
    break_authority_destroy(a);
}

TEST(rate_denied_intent_does_not_burn_its_sequence_number) {
    BreakAuthority *a = make();
    ASSERT_NOT_NULL(a);
    ASSERT_TRUE(break_authority_open_session(a, 1u, 1000000));
    u64 seq = 1u;
    for (u32 i = 0u; i < BREAK_AUTHORITY_RATE_BURST; i++) {
        ASSERT_EQ(break_authority_intent_spend(a, 1u, seq++, 1u, 1u, NOW_US(1000)), BAUTH_OK);
    }
    u64 denied_seq = seq;
    ASSERT_EQ(break_authority_intent_spend(a, 1u, denied_seq, 1u, 1u, NOW_US(1000)), BAUTH_DENIED_RATE);
    /* the same number, retried after the refill, is still fresh */
    ASSERT_EQ(break_authority_intent_spend(a, 1u, denied_seq, 1u, 1u, NOW_US(5000)), BAUTH_OK);
    break_authority_destroy(a);
}

TEST(attack_uses_only_server_side_numbers) {
    BreakAuthority *a = make();
    ASSERT_NOT_NULL(a);
    ASSERT_TRUE(break_authority_open_session(a, 1u, 0));
    ASSERT_TRUE(break_authority_open_session(a, 2u, 0));
    i32 hp = break_authority_health(a, 2u);
    ASSERT_EQ(break_authority_intent_attack(a, 1u, 1u, 2u, NOW_US(0)), BAUTH_OK);
    ASSERT_EQ(break_authority_health(a, 2u), hp - BREAK_AUTHORITY_ATTACK_DAMAGE);
    ASSERT_EQ(break_authority_health(a, 1u), hp);            /* the attacker is untouched */
    /* targets: self, unknown, closed */
    ASSERT_EQ(break_authority_intent_attack(a, 1u, 2u, 1u, NOW_US(1)), BAUTH_DENIED_INVALID);
    ASSERT_EQ(break_authority_intent_attack(a, 1u, 3u, 77u, NOW_US(2)), BAUTH_DENIED_NO_SESSION);
    ASSERT_EQ(break_authority_intent_attack(a, 99u, 1u, 2u, NOW_US(3)), BAUTH_DENIED_NO_SESSION);
    /* kill the target: health never goes below 0 */
    u64 seq = 4u;
    for (int i = 0; i < 200 && break_authority_health(a, 2u) > 0; i++) {
        (void)break_authority_intent_attack(a, 1u, seq++, 2u, NOW_US(10 + i * 600));
    }
    ASSERT_EQ(break_authority_health(a, 2u), 0);
    ASSERT_EQ(break_authority_intent_attack(a, 1u, seq++, 2u, NOW_US(900000)), BAUTH_DENIED_INVALID); /* dead target */
    /* a dead attacker cannot attack */
    ASSERT_EQ(break_authority_intent_attack(a, 2u, 1u, 1u, NOW_US(900001)), BAUTH_DENIED_INVALID);
    ASSERT_EQ(break_authority_health(a, 1u), hp);
    /* closed target */
    break_authority_close_session(a, 2u);
    ASSERT_EQ(break_authority_intent_attack(a, 1u, seq++, 2u, NOW_US(900002)), BAUTH_DENIED_NO_SESSION);
    break_authority_destroy(a);
}

TEST(grant_is_a_server_only_entry_with_checked_arithmetic) {
    BreakAuthority *a = make();
    ASSERT_NOT_NULL(a);
    ASSERT_TRUE(break_authority_open_session(a, 1u, 10));
    ASSERT_EQ(break_authority_grant_server(a, 1u, 5), BAUTH_OK);
    ASSERT_EQ(break_authority_balance(a, 1u), 15);
    ASSERT_EQ(break_authority_grant_server(a, 99u, 5), BAUTH_DENIED_NO_SESSION);
    ASSERT_EQ(break_authority_grant_server(NULL, 1u, 5), BAUTH_DENIED_INVALID);
    break_authority_destroy(a);
}

/* ---- decoder: the session id comes from the transport, never the payload ---- */

static void put_le32(u8 *p, u32 v) { p[0] = (u8)v; p[1] = (u8)(v >> 8); p[2] = (u8)(v >> 16); p[3] = (u8)(v >> 24); }
static void put_le64(u8 *p, u64 v) { for (int i = 0; i < 8; i++) p[i] = (u8)(v >> (8 * i)); }

TEST(decode_accepts_exactly_the_documented_layouts) {
    BreakAuthIntent in;
    u8 spend[1 + 8 + 4 + 4];
    u8 attack[1 + 8 + 8];
    spend[0] = BREAK_AUTH_INTENT_SPEND;
    put_le64(spend + 1, 42u);
    put_le32(spend + 9, 7u);
    put_le32(spend + 13, 3u);
    ASSERT_TRUE(break_authority_decode_intent(spend, sizeof(spend), &in));
    ASSERT_EQ(in.kind, BREAK_AUTH_INTENT_SPEND);
    ASSERT_EQ(in.sequence, 42u);
    ASSERT_EQ(in.item_id, 7u);
    ASSERT_EQ(in.qty, 3u);
    attack[0] = BREAK_AUTH_INTENT_ATTACK;
    put_le64(attack + 1, 43u);
    put_le64(attack + 9, 9u);
    ASSERT_TRUE(break_authority_decode_intent(attack, sizeof(attack), &in));
    ASSERT_EQ(in.kind, BREAK_AUTH_INTENT_ATTACK);
    ASSERT_EQ(in.sequence, 43u);
    ASSERT_EQ(in.target_session, 9u);
}

TEST(decode_rejects_everything_else) {
    BreakAuthIntent in;
    u8 buf[64];
    memset(buf, 0, sizeof(buf));
    ASSERT_FALSE(break_authority_decode_intent(NULL, 17u, &in));
    ASSERT_FALSE(break_authority_decode_intent(buf, 17u, NULL));
    ASSERT_FALSE(break_authority_decode_intent(buf, 0u, &in));
    buf[0] = BREAK_AUTH_INTENT_SPEND;
    put_le64(buf + 1, 5u); /* a valid sequence, so only the LENGTH can reject below */
    ASSERT_TRUE(break_authority_decode_intent(buf, 17u, &in));
    for (usize n = 1u; n < 17u; n++) ASSERT_FALSE(break_authority_decode_intent(buf, n, &in)); /* short */
    ASSERT_FALSE(break_authority_decode_intent(buf, 18u, &in));  /* trailing byte */
    ASSERT_FALSE(break_authority_decode_intent(buf, 64u, &in));
    buf[0] = BREAK_AUTH_INTENT_ATTACK;
    ASSERT_TRUE(break_authority_decode_intent(buf, 17u, &in));
    ASSERT_FALSE(break_authority_decode_intent(buf, 16u, &in));
    ASSERT_FALSE(break_authority_decode_intent(buf, 18u, &in));
    buf[0] = 0u;
    ASSERT_FALSE(break_authority_decode_intent(buf, 17u, &in));  /* unknown kind */
    buf[0] = 99u;
    ASSERT_FALSE(break_authority_decode_intent(buf, 17u, &in));
    /* sequence 0 is reserved */
    buf[0] = BREAK_AUTH_INTENT_SPEND;
    put_le64(buf + 1, 0u);
    ASSERT_FALSE(break_authority_decode_intent(buf, 17u, &in));
}

TEST(apply_routes_a_decoded_intent_with_the_transport_session) {
    BreakAuthority *a = make();
    BreakAuthIntent in;
    u8 spend[17];
    ASSERT_NOT_NULL(a);
    ASSERT_TRUE(break_authority_open_session(a, 5u, 1000));
    ASSERT_TRUE(break_authority_open_session(a, 6u, 1000));
    spend[0] = BREAK_AUTH_INTENT_SPEND;
    put_le64(spend + 1, 1u);
    put_le32(spend + 9, 1u);
    put_le32(spend + 13, 2u);
    ASSERT_TRUE(break_authority_decode_intent(spend, sizeof(spend), &in));
    /* the session is a separate argument: whatever the payload said, the
     * transport's identity is the one charged */
    ASSERT_EQ(break_authority_apply(a, 5u, &in, NOW_US(0)), BAUTH_OK);
    ASSERT_EQ(break_authority_item_count(a, 5u, 1u), 2u);
    ASSERT_EQ(break_authority_item_count(a, 6u, 1u), 0u);
    ASSERT_EQ(break_authority_apply(a, 5u, NULL, NOW_US(0)), BAUTH_DENIED_INVALID);
    break_authority_destroy(a);
}

/* ---- property test: the ledger invariants hold for any intent sequence ---- */

static u64 rng_state = 0x9e3779b97f4a7c15ull;
static u32 rnd(void) {
    rng_state ^= rng_state << 13;
    rng_state ^= rng_state >> 7;
    rng_state ^= rng_state << 17;
    return (u32)(rng_state >> 16);
}

TEST(invariants_hold_over_random_intents) {
    BreakAuthority *a = make();
    ASSERT_NOT_NULL(a);
    const u64 sessions = 4u;
    i64 total_granted = 0;
    for (u64 s = 1u; s <= sessions; s++) {
        ASSERT_TRUE(break_authority_open_session(a, s, 500));
        total_granted += 500;
    }
    u64 seq[5] = {0, 1, 1, 1, 1};
    u64 now = 0u;
    for (u32 i = 0u; i < 100000u; i++) {
        u64 s = 1u + rnd() % (sessions + 1u);            /* sometimes an unknown session */
        u32 what = rnd() % 5u;
        now += rnd() % 400000u;                           /* up to 0.4 s per step */
        u64 sq = (s <= sessions) ? seq[s] : 1u;
        if (rnd() % 7u == 0u) sq = 1u + rnd() % 50u;     /* replays and old numbers */
        if (what == 0u) {
            if (break_authority_grant_server(a, s, (i64)(rnd() % 100u)) == BAUTH_OK) {
                /* the sum of grants is only tracked for the sessions that exist */
            }
        } else if (what <= 2u) {
            (void)break_authority_intent_spend(a, s, sq, rnd() % 6u, rnd() % (BREAK_AUTHORITY_MAX_QTY + 3u), now);
        } else {
            (void)break_authority_intent_attack(a, s, sq, 1u + rnd() % (sessions + 1u), now);
        }
        if (s <= sessions) seq[s] += 1u + rnd() % 3u;
        /* invariants after every step */
        for (u64 t = 1u; t <= sessions; t++) {
            ASSERT_TRUE(break_authority_balance(a, t) >= 0);
            ASSERT_TRUE(break_authority_health(a, t) >= 0);
            ASSERT_TRUE(break_authority_health(a, t) <= BREAK_AUTHORITY_START_HEALTH);
        }
    }
    (void)total_granted;
    break_authority_destroy(a);
}

TEST_MAIN_BEGIN()
    RUN_TEST(item_table_is_server_defined_and_bounded);
    RUN_TEST(create_bounds_and_session_lifecycle);
    RUN_TEST(spend_deducts_server_price_and_adds_the_item);
    RUN_TEST(spend_denials_change_nothing);
    RUN_TEST(price_times_quantity_overflow_is_denied_not_wrapped);
    RUN_TEST(sequence_replay_and_gap_rules);
    RUN_TEST(rate_limit_uses_the_injected_clock);
    RUN_TEST(rate_denied_intent_does_not_burn_its_sequence_number);
    RUN_TEST(attack_uses_only_server_side_numbers);
    RUN_TEST(grant_is_a_server_only_entry_with_checked_arithmetic);
    RUN_TEST(decode_accepts_exactly_the_documented_layouts);
    RUN_TEST(decode_rejects_everything_else);
    RUN_TEST(apply_routes_a_decoded_intent_with_the_transport_session);
    RUN_TEST(invariants_hold_over_random_intents);
TEST_MAIN_END()
