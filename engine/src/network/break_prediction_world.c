#include "network/break_prediction_world.h"

#include <stdlib.h>
#include <string.h>

struct BreakPredictionWorld {
    World *world;
    Entity entity;
    ComponentType component;
    u32 size;
    BreakPrediction *prediction;
};

/* world_get_component validates the component id and the entity (index and
 * generation): a NULL from it covers a destroyed entity, a removed or
 * never-added component and an id out of range, so component_sizes is only
 * read after it succeeded. ECS lets an entity carry a component id that was
 * never registered (size 0); the client refuses it through
 * break_prediction_create's state_size check, the server path explicitly. */
static void *bound_component(const BreakPredictionWorld *pw) {
    return world_get_component(pw->world, pw->entity, pw->component);
}

static void write_back(BreakPredictionWorld *pw, void *dst) {
    memcpy(dst, break_prediction_predicted_state(pw->prediction), pw->size);
}

BreakPredictionResult break_prediction_world_create(const BreakPredictionWorldConfig *cfg,
                                                    BreakPredictionWorld **out) {
    BreakPredictionWorld *pw;
    BreakPredictionConfig pc;
    BreakPredictionResult r;
    const void *initial;
    u32 size;
    if (out) *out = NULL;
    if (!cfg || !out || !cfg->world) return BREAK_PREDICTION_INVALID;
    initial = world_get_component(cfg->world, cfg->entity, cfg->component);
    if (!initial) return BREAK_PREDICTION_INVALID; /* also keeps the size read in range */
    size = cfg->world->component_sizes[cfg->component];
    pw = (BreakPredictionWorld *)calloc(1u, sizeof *pw);
    if (!pw) return BREAK_PREDICTION_OOM;
    memset(&pc, 0, sizeof pc);
    pc.state_size = size;
    pc.input_size = cfg->input_size;
    pc.capacity = cfg->capacity;
    pc.step = cfg->step;
    pc.user = cfg->user;
    pc.initial_tick = cfg->initial_tick;
    pc.initial_state = initial;
    r = break_prediction_create(&pc, &pw->prediction);
    if (r != BREAK_PREDICTION_OK) {
        free(pw);
        return r;
    }
    pw->world = cfg->world;
    pw->entity = cfg->entity;
    pw->component = cfg->component;
    pw->size = size;
    *out = pw;
    return BREAK_PREDICTION_OK;
}

void break_prediction_world_destroy(BreakPredictionWorld *pw) {
    if (!pw) return;
    break_prediction_destroy(pw->prediction);
    free(pw);
}

BreakPredictionResult break_prediction_world_apply_input(BreakPredictionWorld *pw, u64 tick,
                                                         const void *input) {
    BreakPredictionResult r;
    void *dst;
    if (!pw) return BREAK_PREDICTION_INVALID;
    dst = bound_component(pw);
    if (!dst) return BREAK_PREDICTION_INVALID;
    r = break_prediction_apply_input(pw->prediction, tick, input);
    if (r == BREAK_PREDICTION_OK) write_back(pw, dst);
    return r;
}

BreakPredictionResult break_prediction_world_reconcile(BreakPredictionWorld *pw, u64 tick,
                                                       const void *state,
                                                       BreakPredictionReconcile *report) {
    BreakPredictionResult r;
    void *dst;
    if (report) memset(report, 0, sizeof *report);
    if (!pw) return BREAK_PREDICTION_INVALID;
    dst = bound_component(pw);
    if (!dst) return BREAK_PREDICTION_INVALID;
    r = break_prediction_reconcile(pw->prediction, tick, state, report);
    if (r == BREAK_PREDICTION_OK) write_back(pw, dst);
    return r;
}

BreakPredictionResult break_prediction_world_reconcile_from_world(
    BreakPredictionWorld *pw, World *mirror, Entity mirror_entity, u64 tick,
    BreakPredictionReconcile *report) {
    const void *state;
    if (report) memset(report, 0, sizeof *report);
    if (!pw || !mirror) return BREAK_PREDICTION_INVALID;
    state = world_get_component(mirror, mirror_entity, pw->component);
    if (!state || mirror->component_sizes[pw->component] != pw->size)
        return BREAK_PREDICTION_INVALID;
    return break_prediction_world_reconcile(pw, tick, state, report);
}

const BreakPrediction *break_prediction_world_predictor(const BreakPredictionWorld *pw) {
    return pw ? pw->prediction : NULL;
}

BreakPredictionResult break_prediction_world_step_authoritative(World *world, Entity entity,
                                                                ComponentType component,
                                                                BreakPredictionStepFn step,
                                                                void *user, const void *input) {
    u8 next[BREAK_PREDICTION_MAX_STATE_BYTES];
    void *current;
    u32 size;
    if (!world || !step || !input) return BREAK_PREDICTION_INVALID;
    current = world_get_component(world, entity, component);
    if (!current) return BREAK_PREDICTION_INVALID;
    size = world->component_sizes[component];
    if (size == 0u || size > BREAK_PREDICTION_MAX_STATE_BYTES) return BREAK_PREDICTION_INVALID;
    if (!step(user, current, input, next)) return BREAK_PREDICTION_FAILED;
    memcpy(current, next, size);
    return BREAK_PREDICTION_OK;
}
