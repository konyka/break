#ifndef BREAK_PREDICTION_SESSION_H
#define BREAK_PREDICTION_SESSION_H

/* Server side of client prediction over break_net: one input inbox per open
 * connection, fed by the session manager's handler for
 * BREAK_NET_MESSAGE_ID_PREDICTION_INPUT, and snapshot sending through the
 * reactor as BREAK_NET_MESSAGE_ID_PREDICTION_SNAPSHOT
 * (network/break_prediction_wire.h, docs/design/client_prediction.md
 * section 8).
 *
 * The handler decodes the batch and hands each new input to `apply` once and
 * in tick order (break_prediction_inbox_accept). A batch that does not
 * decode, or that arrives for a connection never opened here, fails the
 * handler: the session manager records HANDLER_FAILED and keeps the session
 * open (its rule for non-auth messages), and this bridge counts it as
 * rejected. Closing a peer that keeps sending bad batches is the caller's
 * policy, from break_prediction_session_rejected(). An `apply` that returns
 * false stops the batch at that input and also fails the handler; the next
 * batch resumes from the same tick.
 *
 * Every call is owner-thread only (the logic thread that polls the session
 * manager); the bridge adds no thread, lock or atomic. */

#include <network/break_net_adapter.h>
#include <network/break_prediction_wire.h>
#include <network/break_session.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct BreakPredictionSession BreakPredictionSession;

/* Called for each input in tick order; `connection` is the sender. */
typedef bool (*BreakPredictionSessionApplyFn)(void *user, BreakConnectionKey connection,
                                              u64 tick, const void *input);

typedef struct BreakPredictionSessionConfig {
    BreakNetReactor *reactor;  /* borrowed; NULL for receive-only use */
    size_t max_connections;    /* 1..4096 */
    u32 input_size;            /* 1..BREAK_PREDICTION_MAX_INPUT_BYTES */
    u32 state_size;            /* 1..BREAK_PREDICTION_MAX_STATE_BYTES */
    BreakPredictionSessionApplyFn apply;
    void *apply_user;
} BreakPredictionSessionConfig;

typedef struct BreakPredictionSessionStats {
    size_t connections;
    u64 batches;          /* decoded and accepted */
    u64 rejected;         /* failed to decode, or for an unknown connection */
    u64 apply_failed;     /* batches stopped by apply returning false */
    u64 applied;          /* inputs handed to apply */
    u64 duplicates;       /* inputs already applied */
    u64 gaps;             /* batches that started past the next expected tick */
    u64 snapshots_sent;
} BreakPredictionSessionStats;

BreakPredictionSession *break_prediction_session_create(const BreakPredictionSessionConfig *cfg);
void break_prediction_session_destroy(BreakPredictionSession *session);

/* Registers this bridge as the manager's handler for
 * BREAK_NET_MESSAGE_ID_PREDICTION_INPUT. */
bool break_prediction_session_attach(BreakPredictionSession *session,
                                     BreakSessionManager *manager);

/* Starts tracking `connection`; its first input tick is `first_tick`
 * (the client's initial confirmed tick + 1). False when already open, when
 * max_connections are open, or on NULL. */
bool break_prediction_session_open(BreakPredictionSession *session,
                                   BreakConnectionKey connection, u64 first_tick);
bool break_prediction_session_close(BreakPredictionSession *session,
                                    BreakConnectionKey connection);

/* The last input tick applied for `connection` (what its snapshot carries);
 * false when the connection is not open. */
bool break_prediction_session_last_tick(const BreakPredictionSession *session,
                                        BreakConnectionKey connection, u64 *out_tick);

/* Encodes `state` with the connection's last applied tick and sends it.
 * BREAK_NET_SEND_INVALID when the connection is not open, there is no
 * reactor or the state is NULL; otherwise the reactor's result. */
BreakNetSendResult break_prediction_session_send_snapshot(BreakPredictionSession *session,
                                                          BreakConnectionKey connection,
                                                          const void *state);

/* Batches from `connection` that failed to decode since it was opened; 0
 * when the connection is not open. */
u64 break_prediction_session_rejected(const BreakPredictionSession *session,
                                      BreakConnectionKey connection);

void break_prediction_session_stats(const BreakPredictionSession *session,
                                    BreakPredictionSessionStats *out);

#ifdef __cplusplus
}
#endif

#endif
