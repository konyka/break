#pragma once
/* Client-side prediction with server reconciliation (rollback and replay).
 *
 * The client applies its own inputs immediately to a predicted state instead
 * of waiting a round trip for the server. The server stays authoritative: each
 * snapshot it sends is the true state after a given tick. reconcile() drops
 * the inputs that snapshot covers, compares the snapshot with what the client
 * predicted for that tick, and on a mismatch rolls back to the snapshot and
 * replays the inputs the server has not seen yet.
 *
 * State and input are caller-defined fixed-size byte blocks; the caller's
 * step function advances one tick: step(user, state, input, out_state). It
 * must be deterministic and must fill every byte of out_state (states are
 * compared with memcmp, so padding must be written too). A step that returns
 * false fails the call that ran it and leaves the predictor unchanged.
 *
 * Ticks: the predictor starts at a confirmed (tick, state). apply_input takes
 * exactly the next tick. A snapshot older than the confirmed tick is STALE.
 * A snapshot past the last predicted tick (the server ran ticks the client
 * has no input for) is a resync: every pending input is dropped and
 * prediction continues from the snapshot.
 *
 * Pure C, one allocation at create, no locking (one owner thread). Not a
 * wire format: framing, acknowledgement and transport stay with the caller.
 * Design: docs/design/client_prediction.md. */

#include <core/types.h>

#ifdef __cplusplus
extern "C" {
#endif

/* The predictor keeps the predicted state after every pending input (to tell
 * whether a snapshot matches) plus a replay scratch of the same size (so a
 * failed replay changes nothing): 2 * capacity * state_size bytes, at most
 * 32 MiB with these limits. */
#define BREAK_PREDICTION_MAX_STATE_BYTES (16u * 1024u)
#define BREAK_PREDICTION_MAX_INPUT_BYTES 4096u
#define BREAK_PREDICTION_MAX_CAPACITY 1024u

typedef enum BreakPredictionResult {
    BREAK_PREDICTION_OK = 0,
    BREAK_PREDICTION_INVALID, /* bad argument, or a tick that is not the next one */
    BREAK_PREDICTION_FULL,    /* `capacity` inputs already wait for the server */
    BREAK_PREDICTION_STALE,   /* snapshot older than the confirmed tick */
    BREAK_PREDICTION_FAILED,  /* the step function returned false */
    BREAK_PREDICTION_OOM
} BreakPredictionResult;

typedef bool (*BreakPredictionStepFn)(void *user, const void *state, const void *input,
                                      void *out_state);

typedef struct BreakPredictionConfig {
    u32 state_size;            /* 1..BREAK_PREDICTION_MAX_STATE_BYTES */
    u32 input_size;            /* 1..BREAK_PREDICTION_MAX_INPUT_BYTES */
    u32 capacity;              /* pending inputs, 1..BREAK_PREDICTION_MAX_CAPACITY */
    BreakPredictionStepFn step;
    void *user;
    u64 initial_tick;          /* confirmed tick the predictor starts from */
    const void *initial_state; /* state_size bytes, copied */
} BreakPredictionConfig;

typedef struct BreakPredictionReconcile {
    bool resync;        /* snapshot was past the last predicted tick */
    bool mispredicted;  /* snapshot differed from the prediction for its tick */
    u32 acknowledged;   /* pending inputs the snapshot covered and dropped */
    u32 replayed;       /* inputs re-run on top of the snapshot */
} BreakPredictionReconcile;

typedef struct BreakPredictionStats {
    u64 inputs;         /* accepted by apply_input */
    u64 snapshots;      /* accepted by reconcile (not STALE, not failed) */
    u64 corrections;    /* snapshots that caused a rollback */
    u64 resyncs;
    u64 replayed;       /* inputs re-run across all corrections */
    u64 stale;          /* STALE snapshots refused */
} BreakPredictionStats;

typedef struct BreakPrediction BreakPrediction;

/* INVALID on a NULL argument, a size or capacity out of range, or a NULL
 * step or initial_state; *out is NULL then. */
BreakPredictionResult break_prediction_create(const BreakPredictionConfig *cfg,
                                              BreakPrediction **out);
void break_prediction_destroy(BreakPrediction *p);

/* Runs `input` for `tick`, which must be predicted_tick + 1 (INVALID
 * otherwise), and keeps the input until a snapshot covers it. FULL when
 * `capacity` inputs are pending; nothing changes on any failure. */
BreakPredictionResult break_prediction_apply_input(BreakPrediction *p, u64 tick,
                                                   const void *input);

/* Applies the server's state after `tick` (state_size bytes). `report` may be
 * NULL; on a non-OK result it is zeroed. */
BreakPredictionResult break_prediction_reconcile(BreakPrediction *p, u64 tick,
                                                 const void *state,
                                                 BreakPredictionReconcile *report);

/* The i-th pending input, oldest first (i < pending_count), so the caller can
 * resend inputs the server may not have received. INVALID when out of range. */
BreakPredictionResult break_prediction_pending_input(const BreakPrediction *p, u32 i,
                                                     u64 *out_tick, const void **out_input);

const void *break_prediction_predicted_state(const BreakPrediction *p);
const void *break_prediction_confirmed_state(const BreakPrediction *p);
u64 break_prediction_predicted_tick(const BreakPrediction *p);
u64 break_prediction_confirmed_tick(const BreakPrediction *p);
u32 break_prediction_pending_count(const BreakPrediction *p);
u32 break_prediction_input_size(const BreakPrediction *p);
u32 break_prediction_state_size(const BreakPrediction *p);
void break_prediction_stats(const BreakPrediction *p, BreakPredictionStats *out);

#ifdef __cplusplus
} /* extern "C" */
#endif
