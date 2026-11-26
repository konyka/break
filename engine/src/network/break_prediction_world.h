#pragma once
/* Client prediction bound to one component of one entity in an ECS World.
 *
 * Client side: break_prediction_world_create reads the entity's component as
 * the confirmed state and owns a BreakPrediction whose state is that
 * component's bytes (state_size = the registered component size). Every
 * successful apply_input or reconcile writes the predicted state back into
 * the component, so systems that read the World see the prediction. The
 * predictor is the source of truth: an edit made to the component outside it
 * is overwritten by the next successful call.
 *
 * Server side: break_prediction_world_step_authoritative runs the same step
 * function on the authoritative World's component for one accepted input
 * (for example from break_prediction_session's apply callback). Running the
 * same deterministic step on both sides is what makes snapshots match.
 *
 * Failure: a call whose entity no longer exists or no longer has the
 * component returns INVALID before running any step; the predictor does not
 * advance. Any other failure leaves the predictor (see break_prediction.h)
 * and the component unchanged.
 *
 * The World is borrowed and must outlive the binding. Owner thread only:
 * no thread, lock or atomic. Design: docs/design/client_prediction.md
 * section 9. */

#include <ecs/ecs.h>
#include <network/break_prediction.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct BreakPredictionWorldConfig {
    World *world;              /* borrowed */
    Entity entity;             /* must have `component` at create */
    ComponentType component;   /* registered, size 1..BREAK_PREDICTION_MAX_STATE_BYTES */
    u32 input_size;            /* 1..BREAK_PREDICTION_MAX_INPUT_BYTES */
    u32 capacity;              /* 1..BREAK_PREDICTION_MAX_CAPACITY */
    BreakPredictionStepFn step;
    void *user;
    u64 initial_tick;          /* confirmed tick of the component's current value */
} BreakPredictionWorldConfig;

typedef struct BreakPredictionWorld BreakPredictionWorld;

/* INVALID on a NULL argument, an unregistered or out-of-range component, an
 * entity without the component, or a predictor setting out of range; *out
 * is NULL then. */
BreakPredictionResult break_prediction_world_create(const BreakPredictionWorldConfig *cfg,
                                                    BreakPredictionWorld **out);
void break_prediction_world_destroy(BreakPredictionWorld *pw);

/* break_prediction_apply_input, then the predicted state is written into
 * the component. */
BreakPredictionResult break_prediction_world_apply_input(BreakPredictionWorld *pw, u64 tick,
                                                         const void *input);

/* break_prediction_reconcile, then the predicted state is written into the
 * component. */
BreakPredictionResult break_prediction_world_reconcile(BreakPredictionWorld *pw, u64 tick,
                                                       const void *state,
                                                       BreakPredictionReconcile *report);

/* Reconciles from a replicated mirror World: the server's state for `tick`
 * is `mirror_entity`'s bound component in `mirror` (for example the World
 * break_world_session_drain applies deltas to, with `tick` the applied
 * delta's target tick). Only reads `mirror`. INVALID when the mirror entity
 * does not exist, lacks the component or has it at a different size;
 * otherwise as break_prediction_world_reconcile.
 *
 * The mirror must not be the World the prediction writes to: a delta
 * applies only to a World equal to its base snapshot, so a predicted value
 * in the mirror makes the next delta fail with BREAK_DELTA_BASE_MISMATCH. */
BreakPredictionResult break_prediction_world_reconcile_from_world(
    BreakPredictionWorld *pw, World *mirror, Entity mirror_entity, u64 tick,
    BreakPredictionReconcile *report);

/* The owned predictor, for pending inputs (resending), ticks and stats.
 * Advancing it directly bypasses the component write-back. */
const BreakPrediction *break_prediction_world_predictor(const BreakPredictionWorld *pw);

/* Server: replaces the component with step(user, component, input). INVALID
 * on a NULL world, step or input, an unregistered component, a component
 * larger than BREAK_PREDICTION_MAX_STATE_BYTES, or an entity without it;
 * FAILED (component unchanged) when the step returns false. */
BreakPredictionResult break_prediction_world_step_authoritative(World *world, Entity entity,
                                                                ComponentType component,
                                                                BreakPredictionStepFn step,
                                                                void *user, const void *input);

#ifdef __cplusplus
} /* extern "C" */
#endif
