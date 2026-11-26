/* Client-side prediction with server reconciliation: inputs run at once on a
 * predicted state, server snapshots drop what they cover, and a mismatch rolls
 * back to the snapshot and replays the inputs the server has not seen. */
#include "test_framework.h"

#include <network/break_prediction.h>

#include <stdlib.h>
#include <string.h>

/* A 1-D body: position and velocity, moved by an acceleration input. */
typedef struct {
    i32 pos;
    i32 vel;
} Body;

typedef struct {
    i32 accel;
} Push;

typedef struct {
    u32 calls;
    u32 fail_at; /* 0: never fail; n: the n-th call fails */
    i32 drag;    /* the "server" can use a different rule to force mispredictions */
} StepCtx;

static bool body_step(void *user, const void *state, const void *input, void *out_state) {
    StepCtx *ctx = (StepCtx *)user;
    const Body *s = (const Body *)state;
    const Push *in = (const Push *)input;
    Body next;
    ctx->calls++;
    if (ctx->fail_at != 0u && ctx->calls == ctx->fail_at) return false;
    next.vel = s->vel + in->accel - ctx->drag;
    next.pos = s->pos + next.vel;
    memcpy(out_state, &next, sizeof next);
    return true;
}

static BreakPredictionConfig body_config(StepCtx *ctx, const Body *start, u32 capacity) {
    BreakPredictionConfig cfg;
    memset(&cfg, 0, sizeof cfg);
    cfg.state_size = (u32)sizeof(Body);
    cfg.input_size = (u32)sizeof(Push);
    cfg.capacity = capacity;
    cfg.step = body_step;
    cfg.user = ctx;
    cfg.initial_tick = 10u;
    cfg.initial_state = start;
    return cfg;
}

static BreakPrediction *make(StepCtx *ctx, u32 capacity) {
    static const Body start = {0, 0};
    BreakPredictionConfig cfg = body_config(ctx, &start, capacity);
    BreakPrediction *p = NULL;
    memset(ctx, 0, sizeof *ctx);
    return break_prediction_create(&cfg, &p) == BREAK_PREDICTION_OK ? p : NULL;
}

static Body body_of(const void *state) {
    Body b;
    memcpy(&b, state, sizeof b);
    return b;
}

/* What the server computes for ticks 11..`last` from {0,0} with `drag`. */
static Body server_state(const i32 *accels, u32 count, i32 drag) {
    StepCtx ctx;
    Body s = {0, 0};
    memset(&ctx, 0, sizeof ctx);
    ctx.drag = drag;
    for (u32 i = 0u; i < count; ++i) {
        Push in = {accels[i]};
        Body next;
        (void)body_step(&ctx, &s, &in, &next);
        s = next;
    }
    return s;
}

TEST(inputs_run_at_once_on_the_predicted_state) {
    StepCtx ctx;
    BreakPrediction *p = make(&ctx, 8u);
    Push a = {3}, b = {1};
    ASSERT_NOT_NULL(p);
    ASSERT_EQ(break_prediction_predicted_tick(p), 10u);
    ASSERT_EQ(break_prediction_confirmed_tick(p), 10u);
    ASSERT_EQ(break_prediction_apply_input(p, 11u, &a), BREAK_PREDICTION_OK);
    ASSERT_EQ(break_prediction_apply_input(p, 12u, &b), BREAK_PREDICTION_OK);
    ASSERT_EQ(break_prediction_predicted_tick(p), 12u);
    ASSERT_EQ(break_prediction_confirmed_tick(p), 10u);
    ASSERT_EQ(break_prediction_pending_count(p), 2u);
    /* tick 11: vel 3 pos 3; tick 12: vel 4 pos 7 */
    ASSERT_EQ(body_of(break_prediction_predicted_state(p)).pos, 7);
    ASSERT_EQ(body_of(break_prediction_predicted_state(p)).vel, 4);
    ASSERT_EQ(body_of(break_prediction_confirmed_state(p)).pos, 0);
    break_prediction_destroy(p);
}

TEST(a_matching_snapshot_drops_covered_inputs_without_replaying) {
    StepCtx ctx;
    BreakPrediction *p = make(&ctx, 8u);
    const i32 accels[] = {3, 1, -2};
    BreakPredictionReconcile rep;
    Body srv;
    u32 calls_before;
    ASSERT_NOT_NULL(p);
    for (u32 i = 0u; i < 3u; ++i) {
        Push in = {accels[i]};
        ASSERT_EQ(break_prediction_apply_input(p, 11u + i, &in), BREAK_PREDICTION_OK);
    }
    srv = server_state(accels, 2u, 0);
    calls_before = ctx.calls;
    ASSERT_EQ(break_prediction_reconcile(p, 12u, &srv, &rep), BREAK_PREDICTION_OK);
    ASSERT_FALSE(rep.mispredicted);
    ASSERT_FALSE(rep.resync);
    ASSERT_EQ(rep.acknowledged, 2u);
    ASSERT_EQ(rep.replayed, 0u);
    ASSERT_EQ(ctx.calls, calls_before); /* nothing re-run */
    ASSERT_EQ(break_prediction_confirmed_tick(p), 12u);
    ASSERT_EQ(break_prediction_predicted_tick(p), 13u);
    ASSERT_EQ(break_prediction_pending_count(p), 1u);
    ASSERT_EQ(body_of(break_prediction_predicted_state(p)).pos,
              server_state(accels, 3u, 0).pos);
    break_prediction_destroy(p);
}

TEST(a_mismatch_rolls_back_and_replays_unacknowledged_inputs) {
    StepCtx ctx;
    BreakPrediction *p = make(&ctx, 8u);
    const i32 accels[] = {3, 1, -2, 5};
    BreakPredictionReconcile rep;
    BreakPredictionStats st;
    Body srv, expect;
    ASSERT_NOT_NULL(p);
    for (u32 i = 0u; i < 4u; ++i) {
        Push in = {accels[i]};
        ASSERT_EQ(break_prediction_apply_input(p, 11u + i, &in), BREAK_PREDICTION_OK);
    }
    /* The server applied drag 1 the client did not know about. */
    srv = server_state(accels, 2u, 1);
    ASSERT_EQ(break_prediction_reconcile(p, 12u, &srv, &rep), BREAK_PREDICTION_OK);
    ASSERT_TRUE(rep.mispredicted);
    ASSERT_FALSE(rep.resync);
    ASSERT_EQ(rep.acknowledged, 2u);
    ASSERT_EQ(rep.replayed, 2u);
    ASSERT_EQ(break_prediction_pending_count(p), 2u);
    /* Replay uses the client's own rule (drag 0) on top of the server's state. */
    expect = srv;
    for (u32 i = 2u; i < 4u; ++i) {
        StepCtx plain;
        Push in = {accels[i]};
        Body next;
        memset(&plain, 0, sizeof plain);
        (void)body_step(&plain, &expect, &in, &next);
        expect = next;
    }
    ASSERT_EQ(body_of(break_prediction_predicted_state(p)).pos, expect.pos);
    ASSERT_EQ(body_of(break_prediction_predicted_state(p)).vel, expect.vel);
    ASSERT_EQ(body_of(break_prediction_confirmed_state(p)).pos, srv.pos);
    break_prediction_stats(p, &st);
    ASSERT_EQ(st.inputs, 4u);
    ASSERT_EQ(st.snapshots, 1u);
    ASSERT_EQ(st.corrections, 1u);
    ASSERT_EQ(st.replayed, 2u);
    ASSERT_EQ(st.resyncs, 0u);
    break_prediction_destroy(p);
}

TEST(a_snapshot_for_the_latest_tick_replays_nothing_and_adopts_the_server) {
    StepCtx ctx;
    BreakPrediction *p = make(&ctx, 8u);
    const i32 accels[] = {2, 2};
    BreakPredictionReconcile rep;
    Body srv;
    ASSERT_NOT_NULL(p);
    for (u32 i = 0u; i < 2u; ++i) {
        Push in = {accels[i]};
        ASSERT_EQ(break_prediction_apply_input(p, 11u + i, &in), BREAK_PREDICTION_OK);
    }
    srv = server_state(accels, 2u, 1);
    ASSERT_EQ(break_prediction_reconcile(p, 12u, &srv, &rep), BREAK_PREDICTION_OK);
    ASSERT_TRUE(rep.mispredicted);
    ASSERT_EQ(rep.replayed, 0u);
    ASSERT_EQ(break_prediction_pending_count(p), 0u);
    ASSERT_EQ(memcmp(break_prediction_predicted_state(p), &srv, sizeof srv), 0);
    ASSERT_EQ(break_prediction_predicted_tick(p), 12u);
    break_prediction_destroy(p);
}

TEST(a_snapshot_past_the_prediction_resyncs) {
    StepCtx ctx;
    BreakPrediction *p = make(&ctx, 8u);
    Push in = {4};
    Body srv = {100, 7};
    BreakPredictionReconcile rep;
    BreakPredictionStats st;
    ASSERT_NOT_NULL(p);
    ASSERT_EQ(break_prediction_apply_input(p, 11u, &in), BREAK_PREDICTION_OK);
    ASSERT_EQ(break_prediction_reconcile(p, 15u, &srv, &rep), BREAK_PREDICTION_OK);
    ASSERT_TRUE(rep.resync);
    ASSERT_EQ(rep.acknowledged, 1u);
    ASSERT_EQ(rep.replayed, 0u);
    ASSERT_EQ(break_prediction_pending_count(p), 0u);
    ASSERT_EQ(break_prediction_confirmed_tick(p), 15u);
    ASSERT_EQ(break_prediction_predicted_tick(p), 15u);
    ASSERT_EQ(memcmp(break_prediction_predicted_state(p), &srv, sizeof srv), 0);
    /* prediction continues from the snapshot's tick */
    ASSERT_EQ(break_prediction_apply_input(p, 12u, &in), BREAK_PREDICTION_INVALID);
    ASSERT_EQ(break_prediction_apply_input(p, 16u, &in), BREAK_PREDICTION_OK);
    break_prediction_stats(p, &st);
    ASSERT_EQ(st.resyncs, 1u);
    break_prediction_destroy(p);
}

/* The first tick past the prediction is already a resync: the client has no
 * input for it, so nothing pending can be kept. */
TEST(a_snapshot_one_tick_past_the_prediction_resyncs) {
    StepCtx ctx;
    BreakPrediction *p = make(&ctx, 8u);
    Push in = {2};
    Body srv = {40, 3};
    BreakPredictionReconcile rep;
    ASSERT_NOT_NULL(p);
    ASSERT_EQ(break_prediction_apply_input(p, 11u, &in), BREAK_PREDICTION_OK);
    ASSERT_EQ(break_prediction_apply_input(p, 12u, &in), BREAK_PREDICTION_OK);
    ASSERT_EQ(break_prediction_reconcile(p, 13u, &srv, &rep), BREAK_PREDICTION_OK);
    ASSERT_TRUE(rep.resync);
    ASSERT_EQ(rep.acknowledged, 2u);
    ASSERT_EQ(break_prediction_pending_count(p), 0u);
    ASSERT_EQ(break_prediction_predicted_tick(p), 13u);
    ASSERT_EQ(memcmp(break_prediction_predicted_state(p), &srv, sizeof srv), 0);
    ASSERT_EQ(break_prediction_apply_input(p, 14u, &in), BREAK_PREDICTION_OK);
    ASSERT_EQ(break_prediction_pending_count(p), 1u);
    break_prediction_destroy(p);
}

/* States are compared byte for byte: a difference in the last byte alone is
 * still a misprediction. */
TEST(a_difference_in_the_last_state_byte_is_a_misprediction) {
    StepCtx ctx;
    BreakPrediction *p = make(&ctx, 8u);
    Push in = {1};
    unsigned char srv[sizeof(Body)];
    BreakPredictionReconcile rep;
    ASSERT_NOT_NULL(p);
    ASSERT_EQ(break_prediction_apply_input(p, 11u, &in), BREAK_PREDICTION_OK);
    ASSERT_EQ(break_prediction_apply_input(p, 12u, &in), BREAK_PREDICTION_OK);
    memcpy(srv, break_prediction_confirmed_state(p), sizeof srv);
    {
        Body first;
        StepCtx plain;
        Body zero = {0, 0};
        memset(&plain, 0, sizeof plain);
        (void)body_step(&plain, &zero, &in, &first);
        memcpy(srv, &first, sizeof srv);
    }
    srv[sizeof srv - 1u] ^= 0x01u;
    ASSERT_EQ(break_prediction_reconcile(p, 11u, srv, &rep), BREAK_PREDICTION_OK);
    ASSERT_TRUE(rep.mispredicted);
    ASSERT_EQ(rep.replayed, 1u);
    ASSERT_EQ(memcmp(break_prediction_confirmed_state(p), srv, sizeof srv), 0);
    break_prediction_destroy(p);
}

TEST(old_and_repeated_snapshots_are_stale_and_change_nothing) {
    StepCtx ctx;
    BreakPrediction *p = make(&ctx, 8u);
    const i32 accels[] = {1, 1, 1};
    BreakPredictionReconcile rep;
    BreakPredictionStats st;
    Body srv, before;
    ASSERT_NOT_NULL(p);
    for (u32 i = 0u; i < 3u; ++i) {
        Push in = {accels[i]};
        ASSERT_EQ(break_prediction_apply_input(p, 11u + i, &in), BREAK_PREDICTION_OK);
    }
    srv = server_state(accels, 2u, 0);
    ASSERT_EQ(break_prediction_reconcile(p, 12u, &srv, &rep), BREAK_PREDICTION_OK);
    before = body_of(break_prediction_predicted_state(p));
    /* an older one, delivered late */
    srv = server_state(accels, 1u, 5);
    memset(&rep, 0xAB, sizeof rep);
    ASSERT_EQ(break_prediction_reconcile(p, 11u, &srv, &rep), BREAK_PREDICTION_STALE);
    ASSERT_EQ(rep.acknowledged, 0u);
    ASSERT_FALSE(rep.mispredicted);
    ASSERT_EQ(break_prediction_confirmed_tick(p), 12u);
    ASSERT_EQ(break_prediction_pending_count(p), 1u);
    ASSERT_EQ(memcmp(break_prediction_predicted_state(p), &before, sizeof before), 0);
    break_prediction_stats(p, &st);
    ASSERT_EQ(st.stale, 1u);
    ASSERT_EQ(st.snapshots, 1u);
    break_prediction_destroy(p);
}

TEST(a_repeat_of_the_confirmed_tick_is_accepted_as_a_correction) {
    StepCtx ctx;
    BreakPrediction *p = make(&ctx, 8u);
    const i32 accels[] = {1, 1, 1};
    BreakPredictionReconcile rep;
    Body srv;
    ASSERT_NOT_NULL(p);
    for (u32 i = 0u; i < 3u; ++i) {
        Push in = {accels[i]};
        ASSERT_EQ(break_prediction_apply_input(p, 11u + i, &in), BREAK_PREDICTION_OK);
    }
    srv = server_state(accels, 2u, 0);
    ASSERT_EQ(break_prediction_reconcile(p, 12u, &srv, &rep), BREAK_PREDICTION_OK);
    /* The server corrects tick 12 again (for example after its own rollback). */
    srv.pos += 50;
    ASSERT_EQ(break_prediction_reconcile(p, 12u, &srv, &rep), BREAK_PREDICTION_OK);
    ASSERT_TRUE(rep.mispredicted);
    ASSERT_EQ(rep.acknowledged, 0u);
    ASSERT_EQ(rep.replayed, 1u);
    ASSERT_EQ(body_of(break_prediction_confirmed_state(p)).pos, srv.pos);
    break_prediction_destroy(p);
}

TEST(inputs_must_be_for_the_next_tick_and_respect_capacity) {
    StepCtx ctx;
    BreakPrediction *p = make(&ctx, 3u);
    Push in = {1};
    Body srv;
    const i32 accels[] = {1, 1, 1};
    BreakPredictionStats st;
    ASSERT_NOT_NULL(p);
    ASSERT_EQ(break_prediction_apply_input(p, 10u, &in), BREAK_PREDICTION_INVALID);
    ASSERT_EQ(break_prediction_apply_input(p, 12u, &in), BREAK_PREDICTION_INVALID);
    ASSERT_EQ(break_prediction_apply_input(p, 11u, NULL), BREAK_PREDICTION_INVALID);
    ASSERT_EQ(break_prediction_apply_input(NULL, 11u, &in), BREAK_PREDICTION_INVALID);
    for (u64 t = 11u; t <= 13u; ++t) ASSERT_EQ(break_prediction_apply_input(p, t, &in), BREAK_PREDICTION_OK);
    ASSERT_EQ(break_prediction_apply_input(p, 14u, &in), BREAK_PREDICTION_FULL);
    ASSERT_EQ(break_prediction_predicted_tick(p), 13u);
    ASSERT_EQ(break_prediction_pending_count(p), 3u);
    /* an acknowledgement frees room; the ring wraps */
    srv = server_state(accels, 2u, 0);
    ASSERT_EQ(break_prediction_reconcile(p, 12u, &srv, NULL), BREAK_PREDICTION_OK);
    ASSERT_EQ(break_prediction_apply_input(p, 14u, &in), BREAK_PREDICTION_OK);
    ASSERT_EQ(break_prediction_apply_input(p, 15u, &in), BREAK_PREDICTION_OK);
    ASSERT_EQ(break_prediction_apply_input(p, 16u, &in), BREAK_PREDICTION_FULL);
    break_prediction_stats(p, &st);
    ASSERT_EQ(st.inputs, 5u);
    break_prediction_destroy(p);
}

TEST(pending_inputs_are_listed_oldest_first_across_the_ring) {
    StepCtx ctx;
    BreakPrediction *p = make(&ctx, 3u);
    const i32 accels[] = {1, 2, 3, 4, 5};
    u64 tick = 0u;
    const void *bytes = NULL;
    Body srv;
    ASSERT_NOT_NULL(p);
    for (u32 i = 0u; i < 3u; ++i) {
        Push in = {accels[i]};
        ASSERT_EQ(break_prediction_apply_input(p, 11u + i, &in), BREAK_PREDICTION_OK);
    }
    srv = server_state(accels, 2u, 0);
    ASSERT_EQ(break_prediction_reconcile(p, 12u, &srv, NULL), BREAK_PREDICTION_OK);
    for (u32 i = 3u; i < 5u; ++i) {
        Push in = {accels[i]};
        ASSERT_EQ(break_prediction_apply_input(p, 11u + i, &in), BREAK_PREDICTION_OK);
    }
    for (u32 i = 0u; i < 3u; ++i) {
        Push got;
        ASSERT_EQ(break_prediction_pending_input(p, i, &tick, &bytes), BREAK_PREDICTION_OK);
        memcpy(&got, bytes, sizeof got);
        ASSERT_EQ(tick, 13u + i);
        ASSERT_EQ(got.accel, accels[2u + i]);
    }
    ASSERT_EQ(break_prediction_pending_input(p, 3u, &tick, &bytes), BREAK_PREDICTION_INVALID);
    ASSERT_EQ(break_prediction_pending_input(p, 0u, NULL, &bytes), BREAK_PREDICTION_INVALID);
    ASSERT_EQ(break_prediction_pending_input(p, 0u, &tick, NULL), BREAK_PREDICTION_INVALID);
    break_prediction_destroy(p);
}

TEST(a_failing_step_leaves_the_predictor_unchanged) {
    StepCtx ctx;
    BreakPrediction *p = make(&ctx, 8u);
    const i32 accels[] = {1, 2, 3};
    BreakPredictionReconcile rep;
    BreakPredictionStats st;
    Body srv, predicted;
    ASSERT_NOT_NULL(p);
    ctx.fail_at = 1u;
    {
        Push in = {9};
        ASSERT_EQ(break_prediction_apply_input(p, 11u, &in), BREAK_PREDICTION_FAILED);
    }
    ASSERT_EQ(break_prediction_predicted_tick(p), 10u);
    ASSERT_EQ(break_prediction_pending_count(p), 0u);
    ctx.fail_at = 0u;
    for (u32 i = 0u; i < 3u; ++i) {
        Push in = {accels[i]};
        ASSERT_EQ(break_prediction_apply_input(p, 11u + i, &in), BREAK_PREDICTION_OK);
    }
    predicted = body_of(break_prediction_predicted_state(p));
    /* the second replayed step fails: the whole reconcile is undone */
    srv = server_state(accels, 1u, 3);
    ctx.fail_at = ctx.calls + 2u;
    ASSERT_EQ(break_prediction_reconcile(p, 11u, &srv, &rep), BREAK_PREDICTION_FAILED);
    ASSERT_EQ(rep.replayed, 0u);
    ASSERT_EQ(break_prediction_confirmed_tick(p), 10u);
    ASSERT_EQ(break_prediction_pending_count(p), 3u);
    ASSERT_EQ(memcmp(break_prediction_predicted_state(p), &predicted, sizeof predicted), 0);
    ASSERT_EQ(body_of(break_prediction_confirmed_state(p)).pos, 0);
    break_prediction_stats(p, &st);
    ASSERT_EQ(st.snapshots, 0u);
    ASSERT_EQ(st.corrections, 0u);
    /* the same snapshot succeeds once the step works again */
    ctx.fail_at = 0u;
    ASSERT_EQ(break_prediction_reconcile(p, 11u, &srv, &rep), BREAK_PREDICTION_OK);
    ASSERT_EQ(rep.replayed, 2u);
    break_prediction_destroy(p);
}

TEST(create_and_reconcile_validate_their_arguments) {
    StepCtx ctx;
    Body start = {0, 0};
    BreakPredictionConfig cfg;
    BreakPrediction *p = (BreakPrediction *)&ctx;
    BreakPredictionStats st;
    memset(&ctx, 0, sizeof ctx);
    cfg = body_config(&ctx, &start, 4u);
    ASSERT_EQ(break_prediction_create(NULL, &p), BREAK_PREDICTION_INVALID);
    ASSERT_TRUE(p == NULL);
    ASSERT_EQ(break_prediction_create(&cfg, NULL), BREAK_PREDICTION_INVALID);
    cfg.state_size = 0u;
    ASSERT_EQ(break_prediction_create(&cfg, &p), BREAK_PREDICTION_INVALID);
    cfg.state_size = BREAK_PREDICTION_MAX_STATE_BYTES + 1u;
    ASSERT_EQ(break_prediction_create(&cfg, &p), BREAK_PREDICTION_INVALID);
    cfg = body_config(&ctx, &start, 4u);
    cfg.input_size = 0u;
    ASSERT_EQ(break_prediction_create(&cfg, &p), BREAK_PREDICTION_INVALID);
    cfg.input_size = BREAK_PREDICTION_MAX_INPUT_BYTES + 1u;
    ASSERT_EQ(break_prediction_create(&cfg, &p), BREAK_PREDICTION_INVALID);
    cfg = body_config(&ctx, &start, 0u);
    ASSERT_EQ(break_prediction_create(&cfg, &p), BREAK_PREDICTION_INVALID);
    cfg.capacity = BREAK_PREDICTION_MAX_CAPACITY + 1u;
    ASSERT_EQ(break_prediction_create(&cfg, &p), BREAK_PREDICTION_INVALID);
    cfg = body_config(&ctx, &start, 4u);
    cfg.step = NULL;
    ASSERT_EQ(break_prediction_create(&cfg, &p), BREAK_PREDICTION_INVALID);
    cfg = body_config(&ctx, &start, 4u);
    cfg.initial_state = NULL;
    ASSERT_EQ(break_prediction_create(&cfg, &p), BREAK_PREDICTION_INVALID);
    ASSERT_TRUE(p == NULL);
    /* the largest allowed sizes work */
    {
        void *big = calloc(1u, BREAK_PREDICTION_MAX_STATE_BYTES);
        ASSERT_NOT_NULL(big);
        cfg = body_config(&ctx, &start, BREAK_PREDICTION_MAX_CAPACITY);
        cfg.state_size = BREAK_PREDICTION_MAX_STATE_BYTES;
        cfg.input_size = BREAK_PREDICTION_MAX_INPUT_BYTES;
        cfg.initial_state = big;
        ASSERT_EQ(break_prediction_create(&cfg, &p), BREAK_PREDICTION_OK);
        break_prediction_destroy(p);
        free(big);
    }
    /* the initial state is copied */
    cfg = body_config(&ctx, &start, 4u);
    ASSERT_EQ(break_prediction_create(&cfg, &p), BREAK_PREDICTION_OK);
    ASSERT_EQ(break_prediction_state_size(p), (u32)sizeof(Body));
    ASSERT_EQ(break_prediction_input_size(p), (u32)sizeof(Push));
    ASSERT_EQ(break_prediction_state_size(NULL), 0u);
    ASSERT_EQ(break_prediction_input_size(NULL), 0u);
    start.pos = 99;
    ASSERT_EQ(body_of(break_prediction_predicted_state(p)).pos, 0);
    ASSERT_EQ(break_prediction_reconcile(p, 11u, NULL, NULL), BREAK_PREDICTION_INVALID);
    ASSERT_EQ(break_prediction_reconcile(NULL, 11u, &start, NULL), BREAK_PREDICTION_INVALID);
    break_prediction_stats(p, &st);
    ASSERT_EQ(st.snapshots, 0u);
    break_prediction_destroy(p);
    break_prediction_destroy(NULL);
}

/* Random inputs, random drag on the "server", snapshots arriving late, out of
 * order and repeated. After every step the predicted state must equal the
 * last accepted snapshot with the remaining inputs replayed by the client's
 * own rule, and after the final snapshot both sides agree exactly. */
TEST(random_lossy_snapshots_keep_prediction_consistent_with_the_server) {
    enum { k_ticks = 400, k_cap = 64 };
    StepCtx ctx;
    BreakPrediction *p = make(&ctx, k_cap);
    i32 accels[k_ticks];
    Body server[k_ticks + 1];
    StepCtx srv_ctx;
    u64 confirmed = 10u;
    u32 rng = 12345u;
    ASSERT_NOT_NULL(p);
    memset(&srv_ctx, 0, sizeof srv_ctx);
    server[0].pos = 0;
    server[0].vel = 0;
    for (u32 t = 0u; t < (u32)k_ticks; ++t) {
        Push in;
        rng = rng * 1103515245u + 12345u;
        accels[t] = (i32)((rng >> 16) % 7u) - 3;
        srv_ctx.drag = (i32)((rng >> 8) % 2u);
        in.accel = accels[t];
        (void)body_step(&srv_ctx, &server[t], &in, &server[t + 1u]);
        if (break_prediction_pending_count(p) == (u32)k_cap) {
            u64 ack = confirmed + 1u;
            ASSERT_EQ(break_prediction_reconcile(p, ack, &server[ack - 10u], NULL),
                      BREAK_PREDICTION_OK);
            confirmed = ack;
        }
        ASSERT_EQ(break_prediction_apply_input(p, 11u + t, &in), BREAK_PREDICTION_OK);
        rng = rng * 1103515245u + 12345u;
        if ((rng >> 20) % 3u == 0u) {
            /* deliver a snapshot for a tick between the confirmed one and now,
             * or an older one that must be refused */
            u64 now = 11u + t;
            u64 span = now - confirmed + 3u;
            u64 pick = confirmed + (u64)((rng >> 4) % (u32)span) - 2u;
            BreakPredictionResult r;
            if (pick > now) pick = now;
            if (pick < 10u) pick = 10u;
            r = break_prediction_reconcile(p, pick, &server[pick - 10u], NULL);
            if (pick < confirmed) {
                ASSERT_EQ(r, BREAK_PREDICTION_STALE);
            } else {
                ASSERT_EQ(r, BREAK_PREDICTION_OK);
                confirmed = pick;
            }
        }
        /* invariant: predicted = confirmed snapshot + client replay */
        {
            Body expect = server[confirmed - 10u];
            StepCtx plain;
            memset(&plain, 0, sizeof plain);
            for (u64 k = confirmed; k < 11u + t; ++k) {
                Push again = {accels[k - 10u]};
                Body next;
                (void)body_step(&plain, &expect, &again, &next);
                expect = next;
            }
            ASSERT_EQ(memcmp(break_prediction_predicted_state(p), &expect, sizeof expect), 0);
            ASSERT_EQ(break_prediction_pending_count(p), (u32)(10u + t + 1u - confirmed));
        }
    }
    ASSERT_EQ(break_prediction_reconcile(p, 10u + k_ticks, &server[k_ticks], NULL),
              BREAK_PREDICTION_OK);
    ASSERT_EQ(memcmp(break_prediction_predicted_state(p), &server[k_ticks], sizeof(Body)), 0);
    ASSERT_EQ(break_prediction_pending_count(p), 0u);
    break_prediction_destroy(p);
}

TEST_MAIN_BEGIN()
    RUN_TEST(inputs_run_at_once_on_the_predicted_state);
    RUN_TEST(a_matching_snapshot_drops_covered_inputs_without_replaying);
    RUN_TEST(a_mismatch_rolls_back_and_replays_unacknowledged_inputs);
    RUN_TEST(a_snapshot_for_the_latest_tick_replays_nothing_and_adopts_the_server);
    RUN_TEST(a_snapshot_past_the_prediction_resyncs);
    RUN_TEST(a_snapshot_one_tick_past_the_prediction_resyncs);
    RUN_TEST(a_difference_in_the_last_state_byte_is_a_misprediction);
    RUN_TEST(old_and_repeated_snapshots_are_stale_and_change_nothing);
    RUN_TEST(a_repeat_of_the_confirmed_tick_is_accepted_as_a_correction);
    RUN_TEST(inputs_must_be_for_the_next_tick_and_respect_capacity);
    RUN_TEST(pending_inputs_are_listed_oldest_first_across_the_ring);
    RUN_TEST(a_failing_step_leaves_the_predictor_unchanged);
    RUN_TEST(create_and_reconcile_validate_their_arguments);
    RUN_TEST(random_lossy_snapshots_keep_prediction_consistent_with_the_server);
TEST_MAIN_END()
