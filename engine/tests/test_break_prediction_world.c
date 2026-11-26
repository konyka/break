/* Prediction bound to an ECS World: the client keeps one entity's component
 * equal to the predicted state, and the server steps the authoritative
 * component with each input it accepts. */
#include "test_framework.h"

#include <ecs/ecs.h>
#include <network/break_prediction_world.h>

#include <string.h>

enum { kBody = 3u, kOther = 4u, kBig = 5u, kUnregistered = 6u, kWide = 7u };

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
    i32 drag;
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

/* Fills a whole BREAK_PREDICTION_MAX_STATE_BYTES state: byte i becomes
 * old byte i + the input byte. */
static bool wide_step(void *user, const void *state, const void *input, void *out_state) {
    const u8 *s = (const u8 *)state;
    u8 *o = (u8 *)out_state;
    (void)user;
    for (u32 i = 0u; i < BREAK_PREDICTION_MAX_STATE_BYTES; ++i)
        o[i] = (u8)(s[i] + *(const u8 *)input);
    return true;
}

static Entity spawn(World *w, i32 pos, i32 vel) {
    Entity e = world_create_entity(w);
    Body *b = (Body *)world_add_component(w, e, kBody);
    b->pos = pos;
    b->vel = vel;
    return e;
}

static Body body_in(World *w, Entity e) {
    Body b;
    memcpy(&b, world_get_component(w, e, kBody), sizeof b);
    return b;
}

static BreakPredictionWorldConfig client_config(World *w, Entity e, StepCtx *ctx) {
    BreakPredictionWorldConfig cfg;
    memset(&cfg, 0, sizeof cfg);
    cfg.world = w;
    cfg.entity = e;
    cfg.component = kBody;
    cfg.input_size = (u32)sizeof(Push);
    cfg.capacity = 8u;
    cfg.step = body_step;
    cfg.user = ctx;
    cfg.initial_tick = 10u;
    return cfg;
}

static World *make_world(void) {
    World *w = world_create();
    world_register_component(w, kBody, (u32)sizeof(Body));
    world_register_component(w, kOther, 2u);
    return w;
}

TEST(the_component_follows_the_prediction_as_inputs_run) {
    StepCtx ctx = {0u, 0u, 0};
    World *w = make_world();
    Entity e = spawn(w, 5, 1);
    BreakPredictionWorldConfig cfg = client_config(w, e, &ctx);
    BreakPredictionWorld *pw = NULL;
    Push in = {2};
    Body b;
    ASSERT_EQ(break_prediction_world_create(&cfg, &pw), BREAK_PREDICTION_OK);
    ASSERT_NOT_NULL(pw);
    ASSERT_EQ(break_prediction_state_size(break_prediction_world_predictor(pw)), (u32)sizeof(Body));
    ASSERT_EQ(break_prediction_input_size(break_prediction_world_predictor(pw)), (u32)sizeof(Push));
    ASSERT_EQ(break_prediction_confirmed_tick(break_prediction_world_predictor(pw)), 10u);
    ASSERT_EQ(break_prediction_world_apply_input(pw, 11u, &in), BREAK_PREDICTION_OK);
    b = body_in(w, e);
    ASSERT_EQ(b.vel, 3);
    ASSERT_EQ(b.pos, 8);
    ASSERT_EQ(break_prediction_world_apply_input(pw, 12u, &in), BREAK_PREDICTION_OK);
    b = body_in(w, e);
    ASSERT_EQ(b.vel, 5);
    ASSERT_EQ(b.pos, 13);
    ASSERT_EQ(break_prediction_pending_count(break_prediction_world_predictor(pw)), 2u);
    break_prediction_world_destroy(pw);
    world_destroy(w);
}

TEST(a_correction_rewrites_the_component_with_the_replayed_state) {
    StepCtx ctx = {0u, 0u, 0};
    World *w = make_world();
    Entity e = spawn(w, 0, 0);
    BreakPredictionWorldConfig cfg = client_config(w, e, &ctx);
    BreakPredictionWorld *pw = NULL;
    BreakPredictionReconcile rep;
    Push in = {1};
    Body server = {100, 0}; /* after tick 11 the server put the body elsewhere */
    Body b;
    ASSERT_EQ(break_prediction_world_create(&cfg, &pw), BREAK_PREDICTION_OK);
    ASSERT_EQ(break_prediction_world_apply_input(pw, 11u, &in), BREAK_PREDICTION_OK);
    ASSERT_EQ(break_prediction_world_apply_input(pw, 12u, &in), BREAK_PREDICTION_OK);
    ASSERT_EQ(break_prediction_world_reconcile(pw, 11u, &server, &rep), BREAK_PREDICTION_OK);
    ASSERT_TRUE(rep.mispredicted);
    ASSERT_EQ(rep.replayed, 1u);
    b = body_in(w, e);
    ASSERT_EQ(b.vel, 1);
    ASSERT_EQ(b.pos, 101);
    break_prediction_world_destroy(pw);
    world_destroy(w);
}

TEST(edits_made_outside_the_predictor_are_overwritten) {
    StepCtx ctx = {0u, 0u, 0};
    World *w = make_world();
    Entity e = spawn(w, 0, 0);
    BreakPredictionWorldConfig cfg = client_config(w, e, &ctx);
    BreakPredictionWorld *pw = NULL;
    Push in = {1};
    Body *raw;
    Body b;
    ASSERT_EQ(break_prediction_world_create(&cfg, &pw), BREAK_PREDICTION_OK);
    raw = (Body *)world_get_component(w, e, kBody);
    raw->pos = 999;
    ASSERT_EQ(break_prediction_world_apply_input(pw, 11u, &in), BREAK_PREDICTION_OK);
    b = body_in(w, e);
    ASSERT_EQ(b.pos, 1);
    ASSERT_EQ(b.vel, 1);
    break_prediction_world_destroy(pw);
    world_destroy(w);
}

TEST(a_failure_leaves_both_the_predictor_and_the_component_unchanged) {
    StepCtx ctx = {0u, 2u, 0}; /* the second step fails */
    World *w = make_world();
    Entity e = spawn(w, 0, 0);
    BreakPredictionWorldConfig cfg = client_config(w, e, &ctx);
    BreakPredictionWorld *pw = NULL;
    Push in = {1};
    Body b;
    ASSERT_EQ(break_prediction_world_create(&cfg, &pw), BREAK_PREDICTION_OK);
    ASSERT_EQ(break_prediction_world_apply_input(pw, 11u, &in), BREAK_PREDICTION_OK);
    ASSERT_EQ(break_prediction_world_apply_input(pw, 12u, &in), BREAK_PREDICTION_FAILED);
    b = body_in(w, e);
    ASSERT_EQ(b.pos, 1);
    ASSERT_EQ(break_prediction_predicted_tick(break_prediction_world_predictor(pw)), 11u);
    ASSERT_EQ(break_prediction_world_apply_input(pw, 13u, &in), BREAK_PREDICTION_INVALID);
    ASSERT_EQ(break_prediction_world_reconcile(pw, 5u, &b, NULL), BREAK_PREDICTION_STALE);
    b = body_in(w, e);
    ASSERT_EQ(b.pos, 1);
    /* a failed call writes nothing, so a local edit survives it */
    ((Body *)world_get_component(w, e, kBody))->pos = 77;
    ASSERT_EQ(break_prediction_world_apply_input(pw, 13u, &in), BREAK_PREDICTION_INVALID);
    ASSERT_EQ(break_prediction_world_reconcile(pw, 5u, &b, NULL), BREAK_PREDICTION_STALE);
    b = body_in(w, e);
    ASSERT_EQ(b.pos, 77);
    break_prediction_world_destroy(pw);
    world_destroy(w);
}

TEST(a_destroyed_entity_or_removed_component_refuses_without_advancing) {
    StepCtx ctx = {0u, 0u, 0};
    World *w = make_world();
    Entity e = spawn(w, 0, 0);
    Entity f = spawn(w, 0, 0);
    BreakPredictionWorldConfig cfg = client_config(w, e, &ctx);
    BreakPredictionWorld *pw = NULL;
    BreakPredictionWorld *pf = NULL;
    Push in = {1};
    Body server = {7, 7};
    BreakPredictionReconcile rep;
    ASSERT_EQ(break_prediction_world_create(&cfg, &pw), BREAK_PREDICTION_OK);
    cfg.entity = f;
    ASSERT_EQ(break_prediction_world_create(&cfg, &pf), BREAK_PREDICTION_OK);
    world_destroy_entity(w, e);
    ASSERT_EQ(break_prediction_world_apply_input(pw, 11u, &in), BREAK_PREDICTION_INVALID);
    memset(&rep, 0xab, sizeof rep);
    ASSERT_EQ(break_prediction_world_reconcile(pw, 11u, &server, &rep), BREAK_PREDICTION_INVALID);
    ASSERT_FALSE(rep.mispredicted);
    ASSERT_EQ(rep.replayed, 0u);
    memset(&rep, 0xab, sizeof rep);
    ASSERT_EQ(break_prediction_world_reconcile(NULL, 11u, &server, &rep), BREAK_PREDICTION_INVALID);
    ASSERT_EQ(rep.acknowledged, 0u);
    ASSERT_EQ(break_prediction_predicted_tick(break_prediction_world_predictor(pw)), 10u);
    ASSERT_EQ(ctx.calls, 0u);
    world_remove_component(w, f, kBody);
    ASSERT_EQ(break_prediction_world_apply_input(pf, 11u, &in), BREAK_PREDICTION_INVALID);
    ASSERT_EQ(break_prediction_predicted_tick(break_prediction_world_predictor(pf)), 10u);
    break_prediction_world_destroy(pw);
    break_prediction_world_destroy(pf);
    world_destroy(w);
}

TEST(create_validates_the_binding) {
    StepCtx ctx = {0u, 0u, 0};
    World *w = make_world();
    Entity e = spawn(w, 0, 0);
    Entity bare = world_create_entity(w);
    BreakPredictionWorldConfig cfg = client_config(w, e, &ctx);
    BreakPredictionWorld *pw = (BreakPredictionWorld *)&ctx;
    ASSERT_EQ(break_prediction_world_create(NULL, &pw), BREAK_PREDICTION_INVALID);
    ASSERT_EQ(break_prediction_world_create(&cfg, NULL), BREAK_PREDICTION_INVALID);
    cfg.world = NULL;
    ASSERT_EQ(break_prediction_world_create(&cfg, &pw), BREAK_PREDICTION_INVALID);
    ASSERT_TRUE(pw == NULL);
    cfg = client_config(w, bare, &ctx); /* entity without the component */
    ASSERT_EQ(break_prediction_world_create(&cfg, &pw), BREAK_PREDICTION_INVALID);
    cfg = client_config(w, e, &ctx);
    cfg.component = 9u; /* never registered */
    ASSERT_EQ(break_prediction_world_create(&cfg, &pw), BREAK_PREDICTION_INVALID);
    ASSERT_NOT_NULL(world_add_component(w, e, kUnregistered));
    cfg.component = kUnregistered; /* attached but never registered: size 0 */
    ASSERT_EQ(break_prediction_world_create(&cfg, &pw), BREAK_PREDICTION_INVALID);
    cfg.component = ECS_MAX_COMPONENTS;
    ASSERT_EQ(break_prediction_world_create(&cfg, &pw), BREAK_PREDICTION_INVALID);
    {
        Entity big = world_create_entity(w);
        world_register_component(w, kBig, BREAK_PREDICTION_MAX_STATE_BYTES + 1u);
        ASSERT_NOT_NULL(world_add_component(w, big, kBig));
        cfg = client_config(w, big, &ctx);
        cfg.component = kBig; /* larger than a predictor state */
        ASSERT_EQ(break_prediction_world_create(&cfg, &pw), BREAK_PREDICTION_INVALID);
        ASSERT_EQ(break_prediction_world_step_authoritative(w, big, kBig, body_step, &ctx, &ctx),
                  BREAK_PREDICTION_INVALID);
        ASSERT_EQ(ctx.calls, 0u);
    }
    cfg = client_config(w, e, &ctx);
    cfg.step = NULL;
    ASSERT_EQ(break_prediction_world_create(&cfg, &pw), BREAK_PREDICTION_INVALID);
    cfg = client_config(w, e, &ctx);
    cfg.capacity = 0u;
    ASSERT_EQ(break_prediction_world_create(&cfg, &pw), BREAK_PREDICTION_INVALID);
    ASSERT_TRUE(pw == NULL);
    ASSERT_EQ(break_prediction_world_apply_input(NULL, 11u, &ctx), BREAK_PREDICTION_INVALID);
    ASSERT_EQ(break_prediction_world_reconcile(NULL, 11u, &ctx, NULL), BREAK_PREDICTION_INVALID);
    ASSERT_TRUE(break_prediction_world_predictor(NULL) == NULL);
    break_prediction_world_destroy(NULL);
    world_destroy(w);
}

TEST(a_component_of_the_largest_state_size_is_accepted_on_both_sides) {
    World *w = make_world();
    Entity e = world_create_entity(w);
    BreakPredictionWorldConfig cfg;
    BreakPredictionWorld *pw = NULL;
    u8 add = 3u;
    u8 *raw;
    world_register_component(w, kWide, BREAK_PREDICTION_MAX_STATE_BYTES);
    raw = (u8 *)world_add_component(w, e, kWide);
    ASSERT_NOT_NULL(raw);
    memset(raw, 1, BREAK_PREDICTION_MAX_STATE_BYTES);
    ASSERT_EQ(break_prediction_world_step_authoritative(w, e, kWide, wide_step, NULL, &add),
              BREAK_PREDICTION_OK);
    raw = (u8 *)world_get_component(w, e, kWide);
    ASSERT_EQ(raw[0], 4u);
    ASSERT_EQ(raw[BREAK_PREDICTION_MAX_STATE_BYTES - 1u], 4u);
    memset(&cfg, 0, sizeof cfg);
    cfg.world = w;
    cfg.entity = e;
    cfg.component = kWide;
    cfg.input_size = 1u;
    cfg.capacity = 2u;
    cfg.step = wide_step;
    cfg.initial_tick = 1u;
    ASSERT_EQ(break_prediction_world_create(&cfg, &pw), BREAK_PREDICTION_OK);
    ASSERT_EQ(break_prediction_world_apply_input(pw, 2u, &add), BREAK_PREDICTION_OK);
    raw = (u8 *)world_get_component(w, e, kWide);
    ASSERT_EQ(raw[BREAK_PREDICTION_MAX_STATE_BYTES - 1u], 7u);
    break_prediction_world_destroy(pw);
    world_destroy(w);
}

TEST(the_server_steps_the_authoritative_component) {
    StepCtx ctx = {0u, 0u, 0};
    World *w = make_world();
    Entity e = spawn(w, 5, 1);
    Push in = {2};
    Body b;
    ASSERT_EQ(break_prediction_world_step_authoritative(w, e, kBody, body_step, &ctx, &in),
              BREAK_PREDICTION_OK);
    b = body_in(w, e);
    ASSERT_EQ(b.vel, 3);
    ASSERT_EQ(b.pos, 8);
    ctx.fail_at = 2u;
    ASSERT_EQ(break_prediction_world_step_authoritative(w, e, kBody, body_step, &ctx, &in),
              BREAK_PREDICTION_FAILED);
    b = body_in(w, e);
    ASSERT_EQ(b.pos, 8);
    ASSERT_EQ(break_prediction_world_step_authoritative(w, e, kOther, body_step, &ctx, &in),
              BREAK_PREDICTION_INVALID);
    ASSERT_EQ(break_prediction_world_step_authoritative(w, e, 9u, body_step, &ctx, &in),
              BREAK_PREDICTION_INVALID);
    ASSERT_NOT_NULL(world_add_component(w, e, kUnregistered)); /* ECS allows size 0 */
    ASSERT_EQ(break_prediction_world_step_authoritative(w, e, kUnregistered, body_step, &ctx, &in),
              BREAK_PREDICTION_INVALID);
    ASSERT_EQ(ctx.calls, 2u);
    ASSERT_EQ(break_prediction_world_step_authoritative(NULL, e, kBody, body_step, &ctx, &in),
              BREAK_PREDICTION_INVALID);
    ASSERT_EQ(break_prediction_world_step_authoritative(w, e, kBody, NULL, &ctx, &in),
              BREAK_PREDICTION_INVALID);
    ASSERT_EQ(break_prediction_world_step_authoritative(w, e, kBody, body_step, &ctx, NULL),
              BREAK_PREDICTION_INVALID);
    world_destroy_entity(w, e);
    ASSERT_EQ(break_prediction_world_step_authoritative(w, e, kBody, body_step, &ctx, &in),
              BREAK_PREDICTION_INVALID);
    world_destroy(w);
}

/* Client and server Worlds driven with the same inputs and the same rule,
 * except that the server moves the body once on its own at tick 30. Lossy,
 * late snapshots must bring the client back: after a snapshot three ticks
 * old, the replayed component equals the server's current one. */
TEST(client_and_server_worlds_converge_through_lossy_late_snapshots) {
    StepCtx cctx = {0u, 0u, 0};
    StepCtx sctx = {0u, 0u, 0};
    World *cw = make_world();
    World *sw = make_world();
    Entity ce = spawn(cw, 0, 0);
    Entity se = spawn(sw, 0, 0);
    BreakPredictionWorldConfig cfg = client_config(cw, ce, &cctx);
    BreakPredictionWorld *pw = NULL;
    BreakPredictionStats st;
    Body history[64];
    u32 seed = 12345u;
    u32 diverged = 0u;
    cfg.capacity = 64u;
    ASSERT_EQ(break_prediction_world_create(&cfg, &pw), BREAK_PREDICTION_OK);
    for (u64 t = 11u; t < 11u + 60u; ++t) {
        Push in;
        Body mine;
        Body theirs;
        seed = seed * 1103515245u + 12345u;
        in.accel = (i32)((seed >> 16) % 5u) - 2;
        ASSERT_EQ(break_prediction_world_apply_input(pw, t, &in), BREAK_PREDICTION_OK);
        ASSERT_EQ(break_prediction_world_step_authoritative(sw, se, kBody, body_step, &sctx, &in),
                  BREAK_PREDICTION_OK);
        if (t == 30u) ((Body *)world_get_component(sw, se, kBody))->pos += 50;
        history[t - 11u] = body_in(sw, se);
        if (((seed >> 8) & 3u) == 0u && t > 14u) {
            Body snap = history[t - 3u - 11u];
            ASSERT_EQ(break_prediction_world_reconcile(pw, t - 3u, &snap, NULL),
                      BREAK_PREDICTION_OK);
        }
        mine = body_in(cw, ce);
        theirs = body_in(sw, se);
        if (mine.pos != theirs.pos) diverged++;
    }
    ASSERT_TRUE(diverged > 0u); /* the server's own move was visible as a misprediction */
    {
        Body snap = history[67u - 11u];
        Body mine;
        Body theirs = body_in(sw, se);
        ASSERT_EQ(break_prediction_world_reconcile(pw, 67u, &snap, NULL), BREAK_PREDICTION_OK);
        mine = body_in(cw, ce);
        ASSERT_EQ(mine.pos, theirs.pos);
        ASSERT_EQ(mine.vel, theirs.vel);
    }
    break_prediction_stats(break_prediction_world_predictor(pw), &st);
    ASSERT_TRUE(st.corrections >= 1u);
    break_prediction_world_destroy(pw);
    world_destroy(cw);
    world_destroy(sw);
}

TEST_MAIN_BEGIN()
    RUN_TEST(the_component_follows_the_prediction_as_inputs_run);
    RUN_TEST(a_correction_rewrites_the_component_with_the_replayed_state);
    RUN_TEST(edits_made_outside_the_predictor_are_overwritten);
    RUN_TEST(a_failure_leaves_both_the_predictor_and_the_component_unchanged);
    RUN_TEST(a_destroyed_entity_or_removed_component_refuses_without_advancing);
    RUN_TEST(create_validates_the_binding);
    RUN_TEST(a_component_of_the_largest_state_size_is_accepted_on_both_sides);
    RUN_TEST(the_server_steps_the_authoritative_component);
    RUN_TEST(client_and_server_worlds_converge_through_lossy_late_snapshots);
TEST_MAIN_END()
