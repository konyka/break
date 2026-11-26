#include <network/break_prediction_session.h>

#include <stdlib.h>
#include <string.h>

#define PREDICTION_SESSION_MAX_CONNECTIONS 4096u

typedef struct {
    bool used;
    BreakConnectionKey connection;
    BreakPredictionInbox inbox;
    u64 rejected;
} Slot;

struct BreakPredictionSession {
    BreakNetReactor *reactor;
    size_t max_connections;
    u32 input_size;
    u32 state_size;
    BreakPredictionSessionApplyFn apply;
    void *apply_user;
    Slot *slots;
    u8 *snapshot_buf;
    BreakPredictionSessionStats stats;
};

/* The connection being dispatched, so the inbox's apply callback can pass it
 * on; set only for the duration of one inbox_accept call. */
typedef struct {
    BreakPredictionSession *session;
    BreakConnectionKey connection;
} ApplyCtx;

static bool forward_apply(void *user, u64 tick, const void *input) {
    ApplyCtx *ctx = (ApplyCtx *)user;
    return ctx->session->apply(ctx->session->apply_user, ctx->connection, tick, input);
}

static Slot *find(const BreakPredictionSession *s, BreakConnectionKey connection) {
    for (size_t i = 0u; i < s->max_connections; ++i) {
        if (s->slots[i].used && s->slots[i].connection == connection) return &s->slots[i];
    }
    return NULL;
}

BreakPredictionSession *break_prediction_session_create(const BreakPredictionSessionConfig *cfg) {
    BreakPredictionSession *s;
    if (!cfg || !cfg->apply || cfg->max_connections == 0u ||
        cfg->max_connections > PREDICTION_SESSION_MAX_CONNECTIONS || cfg->input_size == 0u ||
        cfg->input_size > BREAK_PREDICTION_MAX_INPUT_BYTES || cfg->state_size == 0u ||
        cfg->state_size > BREAK_PREDICTION_MAX_STATE_BYTES)
        return NULL;
    s = (BreakPredictionSession *)calloc(1u, sizeof *s);
    if (!s) return NULL;
    s->slots = (Slot *)calloc(cfg->max_connections, sizeof *s->slots);
    s->snapshot_buf = (u8 *)malloc(BREAK_PREDICTION_WIRE_SNAPSHOT_SIZE(cfg->state_size));
    if (!s->slots || !s->snapshot_buf) {
        break_prediction_session_destroy(s);
        return NULL;
    }
    s->reactor = cfg->reactor;
    s->max_connections = cfg->max_connections;
    s->input_size = cfg->input_size;
    s->state_size = cfg->state_size;
    s->apply = cfg->apply;
    s->apply_user = cfg->apply_user;
    return s;
}

void break_prediction_session_destroy(BreakPredictionSession *session) {
    if (!session) return;
    free(session->slots);
    free(session->snapshot_buf);
    free(session);
}

static bool handle_input(BreakConnectionKey connection, const BreakNetOwnedMessage *message,
                         void *user_data) {
    BreakPredictionSession *s = (BreakPredictionSession *)user_data;
    Slot *slot;
    BreakPredictionInputBatch batch;
    ApplyCtx ctx;
    u32 applied = 0u;
    BreakPredictionInbox before;
    BreakPredictionResult r;
    if (!s || !message) return false;
    slot = find(s, connection);
    if (!slot) {
        s->stats.rejected++;
        return false;
    }
    if (break_prediction_wire_decode_inputs((const u8 *)message->data, message->size,
                                            s->input_size, &batch) != BREAK_PREDICTION_OK) {
        slot->rejected++;
        s->stats.rejected++;
        return false;
    }
    ctx.session = s;
    ctx.connection = connection;
    before = slot->inbox;
    r = break_prediction_inbox_accept(&slot->inbox, &batch, forward_apply, &ctx, &applied);
    s->stats.applied += applied;
    s->stats.duplicates += slot->inbox.duplicates - before.duplicates;
    s->stats.gaps += slot->inbox.gaps - before.gaps;
    if (r != BREAK_PREDICTION_OK) {
        s->stats.apply_failed++;
        return false;
    }
    s->stats.batches++;
    return true;
}

bool break_prediction_session_attach(BreakPredictionSession *session,
                                     BreakSessionManager *manager) {
    if (!session || !manager) return false;
    return break_session_manager_set_message_handler(
        manager, BREAK_NET_MESSAGE_ID_PREDICTION_INPUT, handle_input, session);
}

bool break_prediction_session_open(BreakPredictionSession *session,
                                   BreakConnectionKey connection, u64 first_tick) {
    if (!session || first_tick == 0u || find(session, connection)) return false;
    for (size_t i = 0u; i < session->max_connections; ++i) {
        Slot *slot = &session->slots[i];
        if (slot->used) continue;
        memset(slot, 0, sizeof *slot);
        slot->used = true;
        slot->connection = connection;
        break_prediction_inbox_init(&slot->inbox, first_tick);
        session->stats.connections++;
        return true;
    }
    return false;
}

bool break_prediction_session_close(BreakPredictionSession *session,
                                    BreakConnectionKey connection) {
    Slot *slot;
    if (!session) return false;
    slot = find(session, connection);
    if (!slot) return false;
    memset(slot, 0, sizeof *slot);
    session->stats.connections--;
    return true;
}

bool break_prediction_session_last_tick(const BreakPredictionSession *session,
                                        BreakConnectionKey connection, u64 *out_tick) {
    const Slot *slot;
    if (!session || !out_tick) return false;
    slot = find(session, connection);
    if (!slot) return false;
    *out_tick = break_prediction_inbox_last_tick(&slot->inbox);
    return true;
}

BreakNetSendResult break_prediction_session_send_snapshot(BreakPredictionSession *session,
                                                          BreakConnectionKey connection,
                                                          const void *state) {
    const Slot *slot;
    usize len = 0u;
    BreakNetSendResult r;
    if (!session || !state || !session->reactor) return BREAK_NET_SEND_INVALID;
    slot = find(session, connection);
    if (!slot) return BREAK_NET_SEND_INVALID;
    if (break_prediction_wire_encode_snapshot(
            break_prediction_inbox_last_tick(&slot->inbox), state, session->state_size,
            session->snapshot_buf, BREAK_PREDICTION_WIRE_SNAPSHOT_SIZE(session->state_size),
            &len) != BREAK_PREDICTION_OK)
        return BREAK_NET_SEND_INVALID;
    r = break_net_reactor_send(session->reactor, connection,
                               BREAK_NET_MESSAGE_ID_PREDICTION_SNAPSHOT,
                               BREAK_PREDICTION_WIRE_VERSION, session->snapshot_buf, len);
    if (r == BREAK_NET_SEND_OK) session->stats.snapshots_sent++;
    return r;
}

u64 break_prediction_session_rejected(const BreakPredictionSession *session,
                                      BreakConnectionKey connection) {
    const Slot *slot;
    if (!session) return 0u;
    slot = find(session, connection);
    return slot ? slot->rejected : 0u;
}

void break_prediction_session_stats(const BreakPredictionSession *session,
                                    BreakPredictionSessionStats *out) {
    if (!out) return;
    if (!session) {
        memset(out, 0, sizeof *out);
        return;
    }
    *out = session->stats;
}
