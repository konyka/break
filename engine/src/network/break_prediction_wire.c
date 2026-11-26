#include <network/break_prediction_wire.h>

#include <string.h>

static const u8 k_input_magic[4] = {'B', 'R', 'P', 'I'};
static const u8 k_snapshot_magic[4] = {'B', 'R', 'P', 'S'};

static void put_u16(u8 *p, u32 v) {
    p[0] = (u8)v;
    p[1] = (u8)(v >> 8);
}

static void put_u32(u8 *p, u32 v) {
    for (u32 i = 0u; i < 4u; ++i) p[i] = (u8)(v >> (8u * i));
}

static void put_u64(u8 *p, u64 v) {
    for (u32 i = 0u; i < 8u; ++i) p[i] = (u8)(v >> (8u * i));
}

static u32 get_u16(const u8 *p) { return (u32)p[0] | ((u32)p[1] << 8); }

static u32 get_u32(const u8 *p) {
    return (u32)p[0] | ((u32)p[1] << 8) | ((u32)p[2] << 16) | ((u32)p[3] << 24);
}

static u64 get_u64(const u8 *p) {
    u64 v = 0u;
    for (u32 i = 0u; i < 8u; ++i) v |= (u64)p[i] << (8u * i);
    return v;
}

BreakPredictionResult break_prediction_wire_encode_inputs(const BreakPrediction *p, u8 *out,
                                                          usize capacity, usize *out_len) {
    u32 count, input_size;
    usize need;
    u64 first_tick = 0u;
    const void *bytes = NULL;
    if (!out_len) return BREAK_PREDICTION_INVALID;
    *out_len = 0u;
    if (!p || (!out && capacity != 0u)) return BREAK_PREDICTION_INVALID;
    count = break_prediction_pending_count(p);
    if (count == 0u) return BREAK_PREDICTION_OK;
    if (count > BREAK_PREDICTION_WIRE_MAX_BATCH) count = BREAK_PREDICTION_WIRE_MAX_BATCH;
    input_size = break_prediction_input_size(p);
    need = BREAK_PREDICTION_WIRE_INPUT_HEADER + (usize)count * input_size;
    *out_len = need;
    if (capacity < need) return BREAK_PREDICTION_FULL;
    (void)break_prediction_pending_input(p, 0u, &first_tick, &bytes);
    memcpy(out, k_input_magic, 4u);
    out[4] = (u8)BREAK_PREDICTION_WIRE_VERSION;
    out[5] = (u8)count;
    put_u16(out + 6, input_size);
    put_u64(out + 8, first_tick);
    for (u32 i = 0u; i < count; ++i) {
        u64 tick = 0u;
        (void)break_prediction_pending_input(p, i, &tick, &bytes);
        memcpy(out + BREAK_PREDICTION_WIRE_INPUT_HEADER + (usize)i * input_size, bytes,
               input_size);
    }
    return BREAK_PREDICTION_OK;
}

BreakPredictionResult break_prediction_wire_decode_inputs(const u8 *in, usize len,
                                                          u32 input_size,
                                                          BreakPredictionInputBatch *out) {
    u32 count;
    u64 first_tick;
    if (!out) return BREAK_PREDICTION_INVALID;
    memset(out, 0, sizeof *out);
    if (!in || input_size == 0u || input_size > BREAK_PREDICTION_MAX_INPUT_BYTES)
        return BREAK_PREDICTION_INVALID;
    if (len < BREAK_PREDICTION_WIRE_INPUT_HEADER || memcmp(in, k_input_magic, 4u) != 0 ||
        in[4] != BREAK_PREDICTION_WIRE_VERSION)
        return BREAK_PREDICTION_INVALID;
    count = in[5];
    if (count == 0u || count > BREAK_PREDICTION_WIRE_MAX_BATCH) return BREAK_PREDICTION_INVALID;
    if (get_u16(in + 6) != input_size) return BREAK_PREDICTION_INVALID;
    first_tick = get_u64(in + 8);
    /* Tick 0 is the starting confirmed tick, never an input; the last tick
     * must not wrap. */
    if (first_tick == 0u || first_tick > UINT64_MAX - (count - 1u)) return BREAK_PREDICTION_INVALID;
    if (len != BREAK_PREDICTION_WIRE_INPUT_HEADER + (usize)count * input_size)
        return BREAK_PREDICTION_INVALID;
    out->first_tick = first_tick;
    out->count = count;
    out->input_size = input_size;
    out->inputs = in + BREAK_PREDICTION_WIRE_INPUT_HEADER;
    return BREAK_PREDICTION_OK;
}

BreakPredictionResult break_prediction_wire_encode_snapshot(u64 tick, const void *state,
                                                            u32 state_size, u8 *out,
                                                            usize capacity, usize *out_len) {
    usize need;
    if (!out_len) return BREAK_PREDICTION_INVALID;
    *out_len = 0u;
    if (!state || state_size == 0u || state_size > BREAK_PREDICTION_MAX_STATE_BYTES ||
        (!out && capacity != 0u))
        return BREAK_PREDICTION_INVALID;
    need = BREAK_PREDICTION_WIRE_SNAPSHOT_HEADER + (usize)state_size;
    *out_len = need;
    if (capacity < need) return BREAK_PREDICTION_FULL;
    memcpy(out, k_snapshot_magic, 4u);
    out[4] = (u8)BREAK_PREDICTION_WIRE_VERSION;
    out[5] = 0u;
    put_u16(out + 6, 0u);
    put_u64(out + 8, tick);
    put_u32(out + 16, state_size);
    memcpy(out + BREAK_PREDICTION_WIRE_SNAPSHOT_HEADER, state, state_size);
    return BREAK_PREDICTION_OK;
}

BreakPredictionResult break_prediction_wire_decode_snapshot(const u8 *in, usize len,
                                                            u32 state_size,
                                                            BreakPredictionSnapshot *out) {
    if (!out) return BREAK_PREDICTION_INVALID;
    memset(out, 0, sizeof *out);
    if (!in || state_size == 0u || state_size > BREAK_PREDICTION_MAX_STATE_BYTES)
        return BREAK_PREDICTION_INVALID;
    if (len != BREAK_PREDICTION_WIRE_SNAPSHOT_HEADER + (usize)state_size ||
        memcmp(in, k_snapshot_magic, 4u) != 0 || in[4] != BREAK_PREDICTION_WIRE_VERSION ||
        in[5] != 0u || get_u16(in + 6) != 0u || get_u32(in + 16) != state_size)
        return BREAK_PREDICTION_INVALID;
    out->tick = get_u64(in + 8);
    out->state_size = state_size;
    out->state = in + BREAK_PREDICTION_WIRE_SNAPSHOT_HEADER;
    return BREAK_PREDICTION_OK;
}

void break_prediction_inbox_init(BreakPredictionInbox *box, u64 first_tick) {
    if (!box) return;
    memset(box, 0, sizeof *box);
    box->next_tick = first_tick;
}

BreakPredictionResult break_prediction_inbox_accept(BreakPredictionInbox *box,
                                                    const BreakPredictionInputBatch *batch,
                                                    BreakPredictionApplyFn apply, void *user,
                                                    u32 *out_applied) {
    u64 end;
    if (out_applied) *out_applied = 0u;
    if (!box || !batch || !apply || !out_applied || (!batch->inputs && batch->count != 0u))
        return BREAK_PREDICTION_INVALID;
    if (batch->count == 0u) return BREAK_PREDICTION_OK;
    if (batch->first_tick > box->next_tick) {
        box->gaps++;
        return BREAK_PREDICTION_OK;
    }
    end = batch->first_tick + batch->count;
    if (end <= box->next_tick) {
        box->duplicates += batch->count;
        return BREAK_PREDICTION_OK;
    }
    box->duplicates += box->next_tick - batch->first_tick;
    while (box->next_tick < end) {
        const u8 *input =
            batch->inputs + (usize)(box->next_tick - batch->first_tick) * batch->input_size;
        if (!apply(user, box->next_tick, input)) return BREAK_PREDICTION_FAILED;
        box->next_tick++;
        box->applied++;
        (*out_applied)++;
    }
    return BREAK_PREDICTION_OK;
}

u64 break_prediction_inbox_last_tick(const BreakPredictionInbox *box) {
    return box && box->next_tick > 0u ? box->next_tick - 1u : 0u;
}
