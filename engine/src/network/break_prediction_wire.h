#pragma once
/* Wire messages for break_prediction: the client's input batch and the
 * server's state snapshot. Both are untrusted on receipt.
 *
 * Input batch (client -> server), little-endian:
 *   "BRPI" | u8 version = 1 | u8 count (1..MAX_BATCH) | u16 input_size
 *   | u64 first_tick | count * input_size bytes, oldest first.
 * The batch carries every input the server may not have seen yet (the
 * predictor's pending list), so one lost datagram costs nothing as long as a
 * later batch arrives. Ticks are first_tick, first_tick + 1, ...
 *
 * Snapshot (server -> client):
 *   "BRPS" | u8 version = 1 | u8 reserved = 0 | u16 reserved = 0
 *   | u64 tick | u32 state_size | state_size bytes.
 * `tick` is the last input tick the server applied; the client passes it
 * with the state to break_prediction_reconcile.
 *
 * Decoders accept exactly one encoding: wrong magic or version, a non-zero
 * reserved field, a size other than the receiver's configured size, a count
 * of 0 or above the limit, a batch larger than
 * BREAK_PREDICTION_WIRE_MAX_INPUT_MESSAGE, a tick that would overflow, a short buffer or a
 * trailing byte are all INVALID, and the output is zeroed. Decoded byte
 * pointers point into the input buffer.
 *
 * Server side, break_prediction_inbox keeps the next tick it expects from one
 * client and hands each new input to the simulation exactly once, whatever
 * order, duplication or overlap the batches arrive with. Inputs that skip
 * ahead of a missing tick are not applied (the simulation stays in order);
 * the server waits for a later batch to fill the hole.
 * Design: docs/design/client_prediction.md section 5. Pure C, no allocation,
 * one owner. */

#include <network/break_prediction.h>

#ifdef __cplusplus
extern "C" {
#endif

#define BREAK_PREDICTION_WIRE_VERSION 1u
#define BREAK_PREDICTION_WIRE_MAX_BATCH 32u
/* A batch never exceeds this many bytes, header included, so it fits one
 * break_net envelope (64 KiB payload). With large inputs this caps the count
 * below BREAK_PREDICTION_WIRE_MAX_BATCH: 4096-byte inputs go 15 at a time. */
#define BREAK_PREDICTION_WIRE_MAX_INPUT_MESSAGE (64u * 1024u)
#define BREAK_PREDICTION_WIRE_INPUT_HEADER 16u
#define BREAK_PREDICTION_WIRE_SNAPSHOT_HEADER 20u
#define BREAK_PREDICTION_WIRE_INPUT_SIZE(count, input_size) \
    (BREAK_PREDICTION_WIRE_INPUT_HEADER + (count) * (input_size))
#define BREAK_PREDICTION_WIRE_SNAPSHOT_SIZE(state_size) \
    (BREAK_PREDICTION_WIRE_SNAPSHOT_HEADER + (state_size))

typedef struct BreakPredictionInputBatch {
    u64 first_tick;
    u32 count;
    u32 input_size;
    const u8 *inputs; /* count * input_size bytes */
} BreakPredictionInputBatch;

typedef struct BreakPredictionSnapshot {
    u64 tick;
    u32 state_size;
    const u8 *state;
} BreakPredictionSnapshot;

/* Encodes the oldest pending inputs, oldest first, as many as fit both
 * BREAK_PREDICTION_WIRE_MAX_BATCH and BREAK_PREDICTION_WIRE_MAX_INPUT_MESSAGE:
 * the server applies inputs in tick order, so the newest wait for a later
 * batch when more are pending. With no
 * pending input *out_len is 0 and nothing is written. FULL when `capacity`
 * is too small: *out_len gets the size and nothing is written. INVALID on
 * NULL. */
BreakPredictionResult break_prediction_wire_encode_inputs(const BreakPrediction *p, u8 *out,
                                                          usize capacity, usize *out_len);

BreakPredictionResult break_prediction_wire_decode_inputs(const u8 *in, usize len,
                                                          u32 input_size,
                                                          BreakPredictionInputBatch *out);

/* FULL when `capacity` is too small (*out_len gets the size); INVALID on a
 * NULL argument or a state_size of 0 or above BREAK_PREDICTION_MAX_STATE_BYTES. */
BreakPredictionResult break_prediction_wire_encode_snapshot(u64 tick, const void *state,
                                                            u32 state_size, u8 *out,
                                                            usize capacity, usize *out_len);

BreakPredictionResult break_prediction_wire_decode_snapshot(const u8 *in, usize len,
                                                            u32 state_size,
                                                            BreakPredictionSnapshot *out);

typedef struct BreakPredictionInbox {
    u64 next_tick;    /* the tick of the next input to apply */
    u64 applied;      /* inputs handed to the simulation */
    u64 duplicates;   /* inputs already applied, skipped */
    u64 gaps;         /* batches that started past next_tick */
} BreakPredictionInbox;

/* `first_tick` is the client's first input tick (its initial confirmed tick
 * + 1). */
void break_prediction_inbox_init(BreakPredictionInbox *box, u64 first_tick);

/* Calls apply(user, tick, input) for each input of `batch` with
 * tick == next_tick, in order, advancing next_tick after each. Stops at the
 * first false from apply (that input stays unapplied). *out_applied gets the
 * number applied by this call. INVALID on NULL arguments; FAILED when apply
 * returned false. */
typedef bool (*BreakPredictionApplyFn)(void *user, u64 tick, const void *input);
BreakPredictionResult break_prediction_inbox_accept(BreakPredictionInbox *box,
                                                    const BreakPredictionInputBatch *batch,
                                                    BreakPredictionApplyFn apply, void *user,
                                                    u32 *out_applied);

/* The tick the server's snapshot should carry: the last input applied. */
u64 break_prediction_inbox_last_tick(const BreakPredictionInbox *box);

#ifdef __cplusplus
} /* extern "C" */
#endif
