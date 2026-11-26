/* Server side of client prediction over break_net: input batches reach the
 * per-connection inbox through the session manager's handler, malformed or
 * unknown traffic is refused, and snapshots go out through the reactor. */
#include "test_framework.h"

#include <network/break_net_message.h>
#include <network/break_prediction_session.h>

#include <snow/acceptor.h>
#include <snow/endpoint.h>
#include <string.h>

/* A reactor bound to an ephemeral loopback port, as in
 * test_break_replication_session: send() queues outbound messages that the
 * test dequeues with break_net_reactor_poll_outbound_for_test. */
typedef struct {
    SnowAcceptor *acceptor;
    BreakNetReactor *reactor;
} Transport;

static bool transport_start(Transport *t) {
    BreakNetReactorConfig config = {BREAK_NET_DRIVE_STEP, 0, 4u, 1000, 1000u, 1u, false};
    SnowEndpoint *endpoint = NULL;
    memset(t, 0, sizeof *t);
    if (SnowEndpointCreate(&endpoint) != SNOW_OK ||
        SnowEndpointSetHost(endpoint, "127.0.0.1") != SNOW_OK ||
        SnowEndpointSetPort(endpoint, 0) != SNOW_OK ||
        SnowAcceptorCreate(endpoint, &t->acceptor) != SNOW_OK) {
        SnowEndpointDestroy(endpoint);
        return false;
    }
    SnowEndpointDestroy(endpoint);
    if (SnowAcceptorBind(t->acceptor, 1) != SNOW_OK) return false;
    t->reactor = break_net_reactor_create(&config);
    return t->reactor != NULL && break_net_reactor_set_acceptor(t->reactor, t->acceptor) &&
           break_net_reactor_start(t->reactor);
}

static void transport_stop(Transport *t) {
    if (t->reactor) {
        (void)break_net_reactor_stop(t->reactor, 1000u);
        break_net_reactor_destroy(t->reactor);
    }
    if (t->acceptor) SnowAcceptorDestroy(t->acceptor);
    memset(t, 0, sizeof *t);
}

typedef struct {
    BreakConnectionKey connections[64];
    u64 ticks[64];
    i32 values[64];
    u32 n;
    u32 refuse_at; /* 0: never; n: the n-th call returns false */
} Applied;

static bool record(void *user, BreakConnectionKey connection, u64 tick, const void *input) {
    Applied *a = (Applied *)user;
    i32 v;
    if (a->refuse_at != 0u && a->n + 1u == a->refuse_at) return false;
    memcpy(&v, input, sizeof v);
    a->connections[a->n] = connection;
    a->ticks[a->n] = tick;
    a->values[a->n] = v;
    a->n++;
    return true;
}

static bool copy_step(void *user, const void *state, const void *input, void *out_state) {
    (void)user;
    memcpy(out_state, state, 8u);
    memcpy(out_state, input, 4u);
    return true;
}

/* A client predictor whose pending inputs are `values`, ticks first..first+n-1. */
static usize client_batch(u64 first, const i32 *values, u32 n, u8 *out, usize cap) {
    static const u8 start[8] = {0};
    BreakPredictionConfig cfg;
    BreakPrediction *p = NULL;
    usize len = 0u;
    memset(&cfg, 0, sizeof cfg);
    cfg.state_size = 8u;
    cfg.input_size = 4u;
    cfg.capacity = 64u;
    cfg.step = copy_step;
    cfg.initial_tick = first - 1u;
    cfg.initial_state = start;
    if (break_prediction_create(&cfg, &p) != BREAK_PREDICTION_OK) return 0u;
    for (u32 i = 0u; i < n; ++i) (void)break_prediction_apply_input(p, first + i, &values[i]);
    if (break_prediction_wire_encode_inputs(p, out, cap, &len) != BREAK_PREDICTION_OK) len = 0u;
    break_prediction_destroy(p);
    return len;
}

static BreakSessionManager *authenticated(BreakConnectionKey a, BreakConnectionKey b) {
    BreakSessionConfig cfg = {0};
    BreakSessionManager *m = break_session_manager_create(&cfg);
    if (!m) return NULL;
    if (!break_session_manager_bind(m, a) || !break_session_manager_begin_auth(m, a) ||
        !break_session_manager_auth_succeeded(m, a))
        return NULL;
    if (b != 0u && (!break_session_manager_bind(m, b) || !break_session_manager_begin_auth(m, b) ||
                    !break_session_manager_auth_succeeded(m, b)))
        return NULL;
    return m;
}

static bool deliver(BreakSessionManager *m, BreakConnectionKey from, const u8 *bytes, usize len,
                    u32 sequence) {
    BreakNetEvent ev;
    memset(&ev, 0, sizeof ev);
    ev.type = BREAK_NET_EVENT_MESSAGE_RECEIVED;
    ev.connection_key = from;
    ev.message.message_id = BREAK_NET_MESSAGE_ID_PREDICTION_INPUT;
    ev.message.protocol_version = 1u;
    ev.message.sequence = sequence;
    ev.message.data = (void *)bytes;
    ev.message.size = len;
    return break_session_manager_apply_adapter_event(m, &ev);
}

static BreakPredictionSessionConfig base_config(Applied *a, BreakNetReactor *reactor) {
    BreakPredictionSessionConfig cfg;
    memset(&cfg, 0, sizeof cfg);
    cfg.reactor = reactor;
    cfg.max_connections = 4u;
    cfg.input_size = 4u;
    cfg.state_size = 8u;
    cfg.apply = record;
    cfg.apply_user = a;
    return cfg;
}

TEST(batches_from_two_connections_reach_their_own_inbox_in_order) {
    Applied a;
    BreakPredictionSessionConfig cfg;
    BreakPredictionSession *ps;
    BreakSessionManager *m = authenticated(1u, 2u);
    BreakPredictionSessionStats st;
    const i32 first[] = {10, 11, 12};
    const i32 second[] = {20, 21};
    u8 buf[256];
    usize len;
    u64 last = 0u;
    memset(&a, 0, sizeof a);
    cfg = base_config(&a, NULL);
    ps = break_prediction_session_create(&cfg);
    ASSERT_NOT_NULL(ps);
    ASSERT_NOT_NULL(m);
    ASSERT_TRUE(break_prediction_session_attach(ps, m));
    ASSERT_TRUE(break_prediction_session_open(ps, 1u, 1u));
    ASSERT_TRUE(break_prediction_session_open(ps, 2u, 1u));
    len = client_batch(1u, first, 3u, buf, sizeof buf);
    ASSERT_TRUE(deliver(m, 1u, buf, len, 1u));
    len = client_batch(1u, second, 2u, buf, sizeof buf);
    ASSERT_TRUE(deliver(m, 2u, buf, len, 1u));
    /* connection 1 resends 1..3 plus a new 4: only 4 is applied */
    {
        const i32 more[] = {10, 11, 12, 13};
        len = client_batch(1u, more, 4u, buf, sizeof buf);
        ASSERT_TRUE(deliver(m, 1u, buf, len, 2u));
    }
    ASSERT_EQ(a.n, 6u);
    ASSERT_EQ(a.connections[0], 1u);
    ASSERT_EQ(a.values[2], 12);
    ASSERT_EQ(a.connections[3], 2u);
    ASSERT_EQ(a.values[4], 21);
    ASSERT_EQ(a.connections[5], 1u);
    ASSERT_EQ(a.ticks[5], 4u);
    ASSERT_EQ(a.values[5], 13);
    ASSERT_TRUE(break_prediction_session_last_tick(ps, 1u, &last));
    ASSERT_EQ(last, 4u);
    ASSERT_TRUE(break_prediction_session_last_tick(ps, 2u, &last));
    ASSERT_EQ(last, 2u);
    break_prediction_session_stats(ps, &st);
    ASSERT_EQ(st.connections, 2u);
    ASSERT_EQ(st.batches, 3u);
    ASSERT_EQ(st.applied, 6u);
    ASSERT_EQ(st.duplicates, 3u);
    ASSERT_EQ(st.rejected, 0u);
    ASSERT_EQ(st.gaps, 0u);
    /* a batch that starts past the next expected tick waits */
    {
        const i32 later[] = {30, 31};
        len = client_batch(10u, later, 2u, buf, sizeof buf);
        ASSERT_TRUE(deliver(m, 2u, buf, len, 2u));
        break_prediction_session_stats(ps, &st);
        ASSERT_EQ(st.gaps, 1u);
        ASSERT_EQ(st.applied, 6u);
        ASSERT_EQ(st.batches, 4u);
    }
    break_session_manager_destroy(m);
    break_prediction_session_destroy(ps);
}

TEST(malformed_and_unknown_traffic_is_refused_and_counted) {
    Applied a;
    BreakPredictionSessionConfig cfg;
    BreakPredictionSession *ps;
    BreakSessionManager *m = authenticated(1u, 3u);
    BreakPredictionSessionStats st;
    BreakSessionApplyStats ms;
    const i32 one[] = {7};
    u8 buf[64];
    usize len;
    memset(&a, 0, sizeof a);
    cfg = base_config(&a, NULL);
    ps = break_prediction_session_create(&cfg);
    ASSERT_NOT_NULL(ps);
    ASSERT_NOT_NULL(m);
    ASSERT_TRUE(break_prediction_session_attach(ps, m));
    ASSERT_TRUE(break_prediction_session_open(ps, 1u, 1u));
    len = client_batch(1u, one, 1u, buf, sizeof buf);
    buf[0] = 'X';
    ASSERT_FALSE(deliver(m, 1u, buf, len, 1u));
    ASSERT_EQ(break_session_manager_last_result(m), BREAK_SESSION_APPLY_HANDLER_FAILED);
    ASSERT_EQ(break_prediction_session_rejected(ps, 1u), 1u);
    /* a batch sized for another input size is malformed too */
    {
        static const u8 start[8] = {0};
        BreakPredictionConfig pc;
        BreakPrediction *p = NULL;
        u8 wide[8] = {1, 2, 3, 4, 5, 6, 7, 8};
        memset(&pc, 0, sizeof pc);
        pc.state_size = 8u;
        pc.input_size = 8u;
        pc.capacity = 4u;
        pc.step = copy_step;
        pc.initial_state = start;
        ASSERT_EQ(break_prediction_create(&pc, &p), BREAK_PREDICTION_OK);
        ASSERT_EQ(break_prediction_apply_input(p, 1u, wide), BREAK_PREDICTION_OK);
        ASSERT_EQ(break_prediction_wire_encode_inputs(p, buf, sizeof buf, &len),
                  BREAK_PREDICTION_OK);
        break_prediction_destroy(p);
        ASSERT_FALSE(deliver(m, 1u, buf, len, 2u));
        ASSERT_EQ(break_prediction_session_rejected(ps, 1u), 2u);
    }
    /* connection 3 is authenticated but was never opened here */
    len = client_batch(1u, one, 1u, buf, sizeof buf);
    ASSERT_FALSE(deliver(m, 3u, buf, len, 1u));
    ASSERT_EQ(break_prediction_session_rejected(ps, 3u), 0u);
    ASSERT_EQ(a.n, 0u);
    /* the session itself is kept: a good batch still works afterwards */
    ASSERT_EQ(break_session_manager_state(m, 1u), BREAK_SESSION_AUTHENTICATED);
    ASSERT_TRUE(deliver(m, 1u, buf, len, 3u));
    ASSERT_EQ(a.n, 1u);
    break_prediction_session_stats(ps, &st);
    ASSERT_EQ(st.rejected, 3u);
    ASSERT_EQ(st.batches, 1u);
    break_session_manager_apply_stats(m, &ms);
    ASSERT_EQ(ms.handler_failed, 3u);
    break_session_manager_destroy(m);
    break_prediction_session_destroy(ps);
}

TEST(a_refusing_apply_stops_the_batch_and_the_next_batch_resumes) {
    Applied a;
    BreakPredictionSessionConfig cfg;
    BreakPredictionSession *ps;
    BreakSessionManager *m = authenticated(1u, 0u);
    BreakPredictionSessionStats st;
    const i32 values[] = {1, 2, 3, 4};
    u8 buf[128];
    usize len;
    u64 last = 0u;
    memset(&a, 0, sizeof a);
    cfg = base_config(&a, NULL);
    ps = break_prediction_session_create(&cfg);
    ASSERT_NOT_NULL(ps);
    ASSERT_NOT_NULL(m);
    ASSERT_TRUE(break_prediction_session_attach(ps, m));
    ASSERT_TRUE(break_prediction_session_open(ps, 1u, 1u));
    len = client_batch(1u, values, 4u, buf, sizeof buf);
    a.refuse_at = 3u;
    ASSERT_FALSE(deliver(m, 1u, buf, len, 1u));
    ASSERT_EQ(a.n, 2u);
    ASSERT_TRUE(break_prediction_session_last_tick(ps, 1u, &last));
    ASSERT_EQ(last, 2u);
    a.refuse_at = 0u;
    ASSERT_TRUE(deliver(m, 1u, buf, len, 2u));
    ASSERT_EQ(a.n, 4u);
    ASSERT_EQ(a.ticks[2], 3u);
    break_prediction_session_stats(ps, &st);
    ASSERT_EQ(st.apply_failed, 1u);
    ASSERT_EQ(st.rejected, 0u);
    ASSERT_EQ(break_prediction_session_rejected(ps, 1u), 0u);
    break_session_manager_destroy(m);
    break_prediction_session_destroy(ps);
}

TEST(a_snapshot_goes_out_with_the_last_applied_tick) {
    Applied a;
    Transport t;
    BreakPredictionSessionConfig cfg;
    BreakPredictionSession *ps;
    BreakSessionManager *m = authenticated(5u, 0u);
    const i32 values[] = {3, 4, 5};
    const u8 state[8] = {9, 8, 7, 6, 5, 4, 3, 2};
    u8 buf[128];
    usize len;
    uint64_t to = 0u;
    BreakNetOwnedMessage out;
    BreakPredictionSnapshot snap;
    BreakPredictionSessionStats st;
    memset(&a, 0, sizeof a);
    ASSERT_TRUE(transport_start(&t));
    cfg = base_config(&a, t.reactor);
    ps = break_prediction_session_create(&cfg);
    ASSERT_NOT_NULL(ps);
    ASSERT_NOT_NULL(m);
    ASSERT_TRUE(break_prediction_session_attach(ps, m));
    ASSERT_TRUE(break_prediction_session_open(ps, 5u, 1u));
    len = client_batch(1u, values, 3u, buf, sizeof buf);
    ASSERT_TRUE(deliver(m, 5u, buf, len, 1u));
    ASSERT_EQ(break_prediction_session_send_snapshot(ps, 5u, state), BREAK_NET_SEND_OK);
    memset(&out, 0, sizeof out);
    ASSERT_EQ(break_net_reactor_poll_outbound_for_test(t.reactor, &to, &out), BREAK_NET_EVENT_OK);
    ASSERT_EQ(to, 5u);
    ASSERT_EQ(out.message_id, BREAK_NET_MESSAGE_ID_PREDICTION_SNAPSHOT);
    ASSERT_EQ(out.protocol_version, 1u);
    ASSERT_EQ(break_prediction_wire_decode_snapshot((const u8 *)out.data, out.size, 8u, &snap),
              BREAK_PREDICTION_OK);
    ASSERT_EQ(snap.tick, 3u);
    ASSERT_EQ(memcmp(snap.state, state, sizeof state), 0);
    break_net_message_release(&out);
    /* refused before anything reaches the reactor */
    ASSERT_EQ(break_prediction_session_send_snapshot(ps, 6u, state), BREAK_NET_SEND_INVALID);
    ASSERT_EQ(break_prediction_session_send_snapshot(ps, 5u, NULL), BREAK_NET_SEND_INVALID);
    ASSERT_EQ(break_net_reactor_poll_outbound_for_test(t.reactor, &to, &out), BREAK_NET_EVENT_EMPTY);
    break_prediction_session_stats(ps, &st);
    ASSERT_EQ(st.snapshots_sent, 1u);
    break_session_manager_destroy(m);
    break_prediction_session_destroy(ps);
    transport_stop(&t);
}

/* The configured input size is the one the decoder checks: an 8-byte bridge
 * takes 8-byte batches and refuses 4-byte ones. */
TEST(the_configured_input_size_is_enforced) {
    static const u8 start[8] = {0};
    Applied a;
    BreakPredictionSessionConfig cfg;
    BreakPredictionSession *ps;
    BreakSessionManager *m = authenticated(1u, 0u);
    BreakPredictionConfig pc;
    BreakPrediction *p = NULL;
    u8 wide[8] = {5, 0, 0, 0, 9, 9, 9, 9};
    u8 buf[64];
    usize len = 0u;
    const i32 narrow[] = {1};
    memset(&a, 0, sizeof a);
    cfg = base_config(&a, NULL);
    cfg.input_size = 8u;
    ps = break_prediction_session_create(&cfg);
    ASSERT_NOT_NULL(ps);
    ASSERT_NOT_NULL(m);
    ASSERT_TRUE(break_prediction_session_attach(ps, m));
    ASSERT_TRUE(break_prediction_session_open(ps, 1u, 1u));
    memset(&pc, 0, sizeof pc);
    pc.state_size = 8u;
    pc.input_size = 8u;
    pc.capacity = 4u;
    pc.step = copy_step;
    pc.initial_state = start;
    ASSERT_EQ(break_prediction_create(&pc, &p), BREAK_PREDICTION_OK);
    ASSERT_EQ(break_prediction_apply_input(p, 1u, wide), BREAK_PREDICTION_OK);
    ASSERT_EQ(break_prediction_wire_encode_inputs(p, buf, sizeof buf, &len), BREAK_PREDICTION_OK);
    break_prediction_destroy(p);
    ASSERT_TRUE(deliver(m, 1u, buf, len, 1u));
    ASSERT_EQ(a.n, 1u);
    ASSERT_EQ(a.values[0], 5);
    len = client_batch(2u, narrow, 1u, buf, sizeof buf);
    ASSERT_FALSE(deliver(m, 1u, buf, len, 2u));
    ASSERT_EQ(break_prediction_session_rejected(ps, 1u), 1u);
    break_session_manager_destroy(m);
    break_prediction_session_destroy(ps);
}

TEST(a_receive_only_bridge_cannot_send) {
    Applied a;
    BreakPredictionSessionConfig cfg;
    BreakPredictionSession *ps;
    const u8 state[8] = {0};
    memset(&a, 0, sizeof a);
    cfg = base_config(&a, NULL);
    ps = break_prediction_session_create(&cfg);
    ASSERT_NOT_NULL(ps);
    ASSERT_TRUE(break_prediction_session_open(ps, 1u, 1u));
    ASSERT_EQ(break_prediction_session_send_snapshot(ps, 1u, state), BREAK_NET_SEND_INVALID);
    {
        BreakPredictionSessionStats st;
        break_prediction_session_stats(ps, &st);
        ASSERT_EQ(st.snapshots_sent, 0u);
    }
    break_prediction_session_destroy(ps);
}

TEST(connections_open_close_and_respect_the_limit) {
    Applied a;
    BreakPredictionSessionConfig cfg;
    BreakPredictionSession *ps;
    BreakPredictionSessionStats st;
    u64 last = 99u;
    memset(&a, 0, sizeof a);
    cfg = base_config(&a, NULL);
    cfg.max_connections = 2u;
    ps = break_prediction_session_create(&cfg);
    ASSERT_NOT_NULL(ps);
    ASSERT_FALSE(break_prediction_session_last_tick(ps, 0u, &last)); /* unused slots never match */
    ASSERT_TRUE(break_prediction_session_open(ps, 1u, 1u));
    ASSERT_FALSE(break_prediction_session_open(ps, 1u, 1u)); /* already open */
    ASSERT_TRUE(break_prediction_session_open(ps, 2u, 50u));
    ASSERT_FALSE(break_prediction_session_open(ps, 3u, 1u)); /* full */
    ASSERT_TRUE(break_prediction_session_last_tick(ps, 2u, &last));
    ASSERT_EQ(last, 49u);
    ASSERT_TRUE(break_prediction_session_close(ps, 1u));
    ASSERT_FALSE(break_prediction_session_close(ps, 1u));
    ASSERT_EQ(break_prediction_session_rejected(ps, 0u), 0u);
    ASSERT_FALSE(break_prediction_session_last_tick(ps, 1u, &last));
    ASSERT_TRUE(break_prediction_session_open(ps, 3u, 1u)); /* the freed slot */
    /* a reopened connection starts fresh */
    ASSERT_TRUE(break_prediction_session_close(ps, 3u));
    ASSERT_TRUE(break_prediction_session_open(ps, 3u, 7u));
    ASSERT_TRUE(break_prediction_session_last_tick(ps, 3u, &last));
    ASSERT_EQ(last, 6u);
    break_prediction_session_stats(ps, &st);
    ASSERT_EQ(st.connections, 2u);
    ASSERT_TRUE(break_prediction_session_close(ps, 2u));
    ASSERT_FALSE(break_prediction_session_open(ps, 4u, 0u)); /* tick 0 is never an input, even with room */
    ASSERT_FALSE(break_prediction_session_last_tick(ps, 4u, &last));
    ASSERT_FALSE(break_prediction_session_open(NULL, 4u, 1u));
    ASSERT_FALSE(break_prediction_session_close(NULL, 4u));
    ASSERT_FALSE(break_prediction_session_last_tick(ps, 2u, NULL));
    ASSERT_EQ(break_prediction_session_rejected(NULL, 2u), 0u);
    break_prediction_session_destroy(ps);
    break_prediction_session_destroy(NULL);
}

TEST(create_validates_its_configuration) {
    Applied a;
    BreakPredictionSessionConfig cfg;
    memset(&a, 0, sizeof a);
    ASSERT_TRUE(break_prediction_session_create(NULL) == NULL);
    cfg = base_config(&a, NULL);
    cfg.max_connections = 0u;
    ASSERT_TRUE(break_prediction_session_create(&cfg) == NULL);
    cfg.max_connections = 4097u;
    ASSERT_TRUE(break_prediction_session_create(&cfg) == NULL);
    cfg = base_config(&a, NULL);
    cfg.input_size = 0u;
    ASSERT_TRUE(break_prediction_session_create(&cfg) == NULL);
    cfg.input_size = BREAK_PREDICTION_MAX_INPUT_BYTES + 1u;
    ASSERT_TRUE(break_prediction_session_create(&cfg) == NULL);
    cfg = base_config(&a, NULL);
    cfg.state_size = 0u;
    ASSERT_TRUE(break_prediction_session_create(&cfg) == NULL);
    cfg.state_size = BREAK_PREDICTION_MAX_STATE_BYTES + 1u;
    ASSERT_TRUE(break_prediction_session_create(&cfg) == NULL);
    cfg = base_config(&a, NULL);
    cfg.apply = NULL;
    ASSERT_TRUE(break_prediction_session_create(&cfg) == NULL);
    ASSERT_FALSE(break_prediction_session_attach(NULL, NULL));
    {
        BreakPredictionSession *ps;
        cfg = base_config(&a, NULL);
        cfg.max_connections = 4096u;
        ps = break_prediction_session_create(&cfg);
        ASSERT_NOT_NULL(ps);
        ASSERT_FALSE(break_prediction_session_attach(ps, NULL));
        break_prediction_session_destroy(ps);
    }
}

TEST_MAIN_BEGIN()
    RUN_TEST(batches_from_two_connections_reach_their_own_inbox_in_order);
    RUN_TEST(malformed_and_unknown_traffic_is_refused_and_counted);
    RUN_TEST(a_refusing_apply_stops_the_batch_and_the_next_batch_resumes);
    RUN_TEST(a_snapshot_goes_out_with_the_last_applied_tick);
    RUN_TEST(the_configured_input_size_is_enforced);
    RUN_TEST(a_receive_only_bridge_cannot_send);
    RUN_TEST(connections_open_close_and_respect_the_limit);
    RUN_TEST(create_validates_its_configuration);
TEST_MAIN_END()
