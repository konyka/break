#include <network/break_prediction.h>

#include <stdlib.h>
#include <string.h>

/* Pending input i (0 = oldest) lives in ring slot (head + i) % capacity, next
 * to the state the client predicted after running it. The predicted state is
 * therefore the slot of the newest input, or the confirmed state when nothing
 * is pending. Replays write into a scratch ring and are copied over only when
 * every step succeeded, so a failed step changes nothing. */
struct BreakPrediction {
    u32 state_size;
    u32 input_size;
    u32 capacity;
    BreakPredictionStepFn step;
    void *user;
    u64 confirmed_tick;
    u32 head;
    u32 count;
    u8 *confirmed;    /* state_size */
    u8 *inputs;       /* capacity * input_size */
    u8 *states;       /* capacity * state_size: prediction after each input */
    u8 *scratch;      /* capacity * state_size: replay output */
    BreakPredictionStats stats;
};

static u32 slot_of(const BreakPrediction *p, u32 i) { return (p->head + i) % p->capacity; }

static u8 *input_at(const BreakPrediction *p, u32 i) {
    return p->inputs + (usize)slot_of(p, i) * p->input_size;
}

static u8 *state_at(const BreakPrediction *p, u32 i) {
    return p->states + (usize)slot_of(p, i) * p->state_size;
}

static const u8 *predicted(const BreakPrediction *p) {
    return p->count == 0u ? p->confirmed : state_at(p, p->count - 1u);
}

BreakPredictionResult break_prediction_create(const BreakPredictionConfig *cfg,
                                              BreakPrediction **out) {
    BreakPrediction *p;
    usize ring_states;
    if (out) *out = NULL;
    if (!cfg || !out || !cfg->step || !cfg->initial_state) return BREAK_PREDICTION_INVALID;
    if (cfg->state_size == 0u || cfg->state_size > BREAK_PREDICTION_MAX_STATE_BYTES ||
        cfg->input_size == 0u || cfg->input_size > BREAK_PREDICTION_MAX_INPUT_BYTES ||
        cfg->capacity == 0u || cfg->capacity > BREAK_PREDICTION_MAX_CAPACITY)
        return BREAK_PREDICTION_INVALID;
    p = (BreakPrediction *)calloc(1u, sizeof *p);
    if (!p) return BREAK_PREDICTION_OOM;
    ring_states = (usize)cfg->capacity * cfg->state_size;
    p->confirmed = (u8 *)malloc(cfg->state_size);
    p->inputs = (u8 *)malloc((usize)cfg->capacity * cfg->input_size);
    p->states = (u8 *)malloc(ring_states);
    p->scratch = (u8 *)malloc(ring_states);
    if (!p->confirmed || !p->inputs || !p->states || !p->scratch) {
        break_prediction_destroy(p);
        return BREAK_PREDICTION_OOM;
    }
    p->state_size = cfg->state_size;
    p->input_size = cfg->input_size;
    p->capacity = cfg->capacity;
    p->step = cfg->step;
    p->user = cfg->user;
    p->confirmed_tick = cfg->initial_tick;
    memcpy(p->confirmed, cfg->initial_state, cfg->state_size);
    *out = p;
    return BREAK_PREDICTION_OK;
}

void break_prediction_destroy(BreakPrediction *p) {
    if (!p) return;
    free(p->confirmed);
    free(p->inputs);
    free(p->states);
    free(p->scratch);
    free(p);
}

BreakPredictionResult break_prediction_apply_input(BreakPrediction *p, u64 tick,
                                                   const void *input) {
    u32 slot;
    if (!p || !input) return BREAK_PREDICTION_INVALID;
    if (tick != p->confirmed_tick + p->count + 1u) return BREAK_PREDICTION_INVALID;
    if (p->count == p->capacity) return BREAK_PREDICTION_FULL;
    slot = slot_of(p, p->count);
    /* Step into the scratch slot so a failing step leaves everything as it was. */
    if (!p->step(p->user, predicted(p), input, p->scratch + (usize)slot * p->state_size))
        return BREAK_PREDICTION_FAILED;
    memcpy(p->inputs + (usize)slot * p->input_size, input, p->input_size);
    memcpy(p->states + (usize)slot * p->state_size, p->scratch + (usize)slot * p->state_size,
           p->state_size);
    p->count++;
    p->stats.inputs++;
    return BREAK_PREDICTION_OK;
}

BreakPredictionResult break_prediction_reconcile(BreakPrediction *p, u64 tick,
                                                 const void *state,
                                                 BreakPredictionReconcile *report) {
    BreakPredictionReconcile rep;
    u64 newest;
    u32 covered;
    memset(&rep, 0, sizeof rep);
    if (report) memset(report, 0, sizeof *report);
    if (!p || !state) return BREAK_PREDICTION_INVALID;
    if (tick < p->confirmed_tick) {
        p->stats.stale++;
        return BREAK_PREDICTION_STALE;
    }
    newest = p->confirmed_tick + p->count;
    if (tick > newest) {
        /* The server is ahead of every input the client sent: start over. */
        rep.resync = true;
        rep.acknowledged = p->count;
        p->head = 0u;
        p->count = 0u;
        p->confirmed_tick = tick;
        memcpy(p->confirmed, state, p->state_size);
        p->stats.snapshots++;
        p->stats.resyncs++;
        if (report) *report = rep;
        return BREAK_PREDICTION_OK;
    }
    covered = (u32)(tick - p->confirmed_tick);
    rep.acknowledged = covered;
    {
        const u8 *was = covered == 0u ? p->confirmed : state_at(p, covered - 1u);
        rep.mispredicted = memcmp(was, state, p->state_size) != 0;
    }
    if (rep.mispredicted) {
        const u8 *from = (const u8 *)state;
        for (u32 i = covered; i < p->count; ++i) {
            u8 *dst = p->scratch + (usize)slot_of(p, i) * p->state_size;
            if (!p->step(p->user, from, input_at(p, i), dst)) {
                return BREAK_PREDICTION_FAILED;
            }
            from = dst;
        }
        for (u32 i = covered; i < p->count; ++i) {
            u32 slot = slot_of(p, i);
            memcpy(p->states + (usize)slot * p->state_size,
                   p->scratch + (usize)slot * p->state_size, p->state_size);
        }
        rep.replayed = p->count - covered;
        p->stats.corrections++;
        p->stats.replayed += rep.replayed;
    }
    memcpy(p->confirmed, state, p->state_size);
    p->head = slot_of(p, covered);
    p->count -= covered;
    p->confirmed_tick = tick;
    p->stats.snapshots++;
    if (report) *report = rep;
    return BREAK_PREDICTION_OK;
}

BreakPredictionResult break_prediction_pending_input(const BreakPrediction *p, u32 i,
                                                     u64 *out_tick, const void **out_input) {
    if (!p || !out_tick || !out_input || i >= p->count) return BREAK_PREDICTION_INVALID;
    *out_tick = p->confirmed_tick + i + 1u;
    *out_input = input_at(p, i);
    return BREAK_PREDICTION_OK;
}

const void *break_prediction_predicted_state(const BreakPrediction *p) {
    return p ? predicted(p) : NULL;
}

const void *break_prediction_confirmed_state(const BreakPrediction *p) {
    return p ? p->confirmed : NULL;
}

u64 break_prediction_predicted_tick(const BreakPrediction *p) {
    return p ? p->confirmed_tick + p->count : 0u;
}

u64 break_prediction_confirmed_tick(const BreakPrediction *p) {
    return p ? p->confirmed_tick : 0u;
}

u32 break_prediction_pending_count(const BreakPrediction *p) { return p ? p->count : 0u; }

u32 break_prediction_input_size(const BreakPrediction *p) { return p ? p->input_size : 0u; }

u32 break_prediction_state_size(const BreakPrediction *p) { return p ? p->state_size : 0u; }

void break_prediction_stats(const BreakPrediction *p, BreakPredictionStats *out) {
    if (!out) return;
    if (!p) {
        memset(out, 0, sizeof *out);
        return;
    }
    *out = p->stats;
}
