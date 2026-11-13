#include "core_app_simulation.h"

#include <math.h>
#include <stdlib.h>
#include <string.h>

#define CORE_APP_KEY_SPACE 32
#define CORE_APP_KEY_F5 275
#define CORE_APP_KEY_F9 279
#define CORE_APP_USER_RADIUS 0.4f
#define CORE_APP_USER_HEIGHT 2.0f

struct CoreAppSimulation {
    CoreAppSimulationDesc desc;
    CharacterController character;
    u64 tick_count;
};

static BreakGameBinding key_binding(i32 code, f32 scale) {
    BreakGameBinding binding;
    memset(&binding, 0, sizeof(binding));
    binding.source = BREAK_GAME_BIND_KEY;
    binding.code = code;
    binding.scale = scale;
    return binding;
}

static BreakGameBinding pad_binding(BreakGameBindSource source, i32 code, f32 scale) {
    BreakGameBinding binding;
    memset(&binding, 0, sizeof(binding));
    binding.source = source;
    binding.code = code;
    binding.pad = 0;
    binding.scale = scale;
    return binding;
}

static BreakGameError bind_actions(BreakGame *actor_runtime) {
    static const char *const names[CORE_APP_ACTION_COUNT] = {
        "forward", "back", "left", "right", "jump",
        "interact", "fire", "save", "load"
    };
    BreakGameBinding bindings[CORE_APP_ACTION_COUNT][2];
    u32 counts[CORE_APP_ACTION_COUNT];
    BreakGameActionDesc actions[CORE_APP_ACTION_COUNT];
    u32 i;
    bindings[CORE_APP_ACTION_FORWARD][0] = key_binding('w', 1.0f);
    bindings[CORE_APP_ACTION_FORWARD][1] =
        pad_binding(BREAK_GAME_BIND_PAD_AXIS, GAMEPAD_AXIS_LEFT_Y, -1.0f);
    counts[CORE_APP_ACTION_FORWARD] = 2u;
    bindings[CORE_APP_ACTION_BACK][0] = key_binding('s', 1.0f);
    counts[CORE_APP_ACTION_BACK] = 1u;
    bindings[CORE_APP_ACTION_LEFT][0] = key_binding('a', 1.0f);
    counts[CORE_APP_ACTION_LEFT] = 1u;
    bindings[CORE_APP_ACTION_RIGHT][0] = key_binding('d', 1.0f);
    bindings[CORE_APP_ACTION_RIGHT][1] =
        pad_binding(BREAK_GAME_BIND_PAD_AXIS, GAMEPAD_AXIS_LEFT_X, 1.0f);
    counts[CORE_APP_ACTION_RIGHT] = 2u;
    bindings[CORE_APP_ACTION_JUMP][0] = key_binding(CORE_APP_KEY_SPACE, 1.0f);
    bindings[CORE_APP_ACTION_JUMP][1] =
        pad_binding(BREAK_GAME_BIND_PAD_BUTTON, GAMEPAD_BTN_SOUTH, 1.0f);
    counts[CORE_APP_ACTION_JUMP] = 2u;
    bindings[CORE_APP_ACTION_INTERACT][0] = key_binding('e', 1.0f);
    bindings[CORE_APP_ACTION_INTERACT][1] =
        pad_binding(BREAK_GAME_BIND_PAD_BUTTON, GAMEPAD_BTN_WEST, 1.0f);
    counts[CORE_APP_ACTION_INTERACT] = 2u;
    bindings[CORE_APP_ACTION_FIRE][0] = key_binding(INPUT_MOUSE_LEFT, 1.0f);
    bindings[CORE_APP_ACTION_FIRE][0].source = BREAK_GAME_BIND_MOUSE_BUTTON;
    bindings[CORE_APP_ACTION_FIRE][1] =
        pad_binding(BREAK_GAME_BIND_PAD_BUTTON, GAMEPAD_BTN_RB, 1.0f);
    counts[CORE_APP_ACTION_FIRE] = 2u;
    bindings[CORE_APP_ACTION_SAVE][0] = key_binding(CORE_APP_KEY_F5, 1.0f);
    counts[CORE_APP_ACTION_SAVE] = 1u;
    bindings[CORE_APP_ACTION_LOAD][0] = key_binding(CORE_APP_KEY_F9, 1.0f);
    counts[CORE_APP_ACTION_LOAD] = 1u;
    for (i = 0u; i < CORE_APP_ACTION_COUNT; ++i) {
        actions[i].name = names[i];
        actions[i].bindings = bindings[i];
        actions[i].binding_count = counts[i];
    }
    return break_game_bind_actions(actor_runtime, actions, CORE_APP_ACTION_COUNT);
}

static f32 clamp_unit(f32 value) {
    if (value > 1.0f) return 1.0f;
    if (value < -1.0f) return -1.0f;
    return value;
}

CoreAppSimulation *core_app_simulation_create(const CoreAppSimulationDesc *desc) {
    CoreAppSimulation *simulation;
    if (!desc || !desc->world || !desc->actor_runtime || !desc->physics ||
        !world_entity_exists(desc->world, desc->user) ||
        !world_get_component(desc->world, desc->user,
                             BREAK_GAME_POSITION_COMPONENT) ||
        !isfinite(desc->spawn.e[0]) || !isfinite(desc->spawn.e[1]) ||
        !isfinite(desc->spawn.e[2])) {
        return NULL;
    }
    if (bind_actions(desc->actor_runtime) != BREAK_GAME_OK) return NULL;
    simulation = (CoreAppSimulation *)calloc(1u, sizeof(*simulation));
    if (!simulation) return NULL;
    simulation->desc = *desc;
    simulation->character = character_create(desc->spawn, CORE_APP_USER_RADIUS,
                                             CORE_APP_USER_HEIGHT);
    return simulation;
}

void core_app_simulation_destroy(CoreAppSimulation *simulation) {
    free(simulation);
}

BreakRuntimeError core_app_simulation_intent(CoreAppSimulation *simulation,
                                             const CoreAppInputFrame *frame,
                                             CoreAppMoveIntent *out) {
    BreakGameActionValue values[CORE_APP_ACTION_COUNT];
    f32 forward;
    f32 strafe;
    u32 i;
    if (out) memset(out, 0, sizeof(*out));
    if (!simulation || !frame || !out) return BREAK_RUNTIME_INVALID;
    if (break_game_eval_actions(simulation->desc.actor_runtime, &frame->state, values,
                                CORE_APP_ACTION_COUNT) != BREAK_GAME_OK) {
        return BREAK_RUNTIME_FAILED;
    }
    forward = values[CORE_APP_ACTION_FORWARD].axis - values[CORE_APP_ACTION_BACK].axis;
    strafe = values[CORE_APP_ACTION_RIGHT].axis - values[CORE_APP_ACTION_LEFT].axis;
    for (i = 0u; i < frame->touch_count; ++i) {
        const InputTouch *touch = &frame->touches[i];
        if (touch->phase == INPUT_TOUCH_RELEASE || touch->phase == INPUT_TOUCH_CANCEL) {
            continue;
        }
        forward += (touch->start_y - touch->y) / CORE_APP_TOUCH_STICK_RADIUS;
        strafe += (touch->x - touch->start_x) / CORE_APP_TOUCH_STICK_RADIUS;
        break;
    }
    out->forward = clamp_unit(forward);
    out->strafe = clamp_unit(strafe);
    out->jump = values[CORE_APP_ACTION_JUMP].down;
    out->interact = values[CORE_APP_ACTION_INTERACT].down;
    return BREAK_RUNTIME_OK;
}

BreakRuntimeError core_app_simulation_tick(CoreAppSimulation *simulation,
                                           const CoreAppInputFrame *frame) {
    CoreAppMoveIntent intent;
    BreakGameMoveInput move_input;
    BreakGameMoveOutput move_output;
    Vec3 *position;
    BreakRuntimeError result = core_app_simulation_intent(simulation, frame, &intent);
    if (result != BREAK_RUNTIME_OK) return result;
    position = (Vec3 *)world_get_component(simulation->desc.world,
                                           simulation->desc.user,
                                           BREAK_GAME_POSITION_COMPONENT);
    if (!position) return BREAK_RUNTIME_STALE;
    memset(&move_input, 0, sizeof(move_input));
    move_input.forward = intent.forward;
    move_input.strafe = intent.strafe;
    move_input.camera_yaw = 0.0f;
    move_input.jump = intent.jump;
    if (break_game_move_wish(&move_input, &move_output) != BREAK_GAME_OK) {
        return BREAK_RUNTIME_FAILED;
    }
    character_update(&simulation->character, simulation->desc.physics,
                     CORE_APP_FIXED_DT, move_output.wish, move_output.jump);
    *position = simulation->character.position;
    simulation->tick_count++;
    return BREAK_RUNTIME_OK;
}

BreakRuntimeError core_app_simulation_user_position(
    const CoreAppSimulation *simulation, Vec3 *out) {
    if (!simulation || !out) return BREAK_RUNTIME_INVALID;
    *out = simulation->character.position;
    return BREAK_RUNTIME_OK;
}

BreakRuntimeError core_app_simulation_place_user(CoreAppSimulation *simulation,
                                                Vec3 position) {
    Vec3 *component;
    if (!simulation || !isfinite(position.e[0]) || !isfinite(position.e[1]) ||
        !isfinite(position.e[2])) {
        return BREAK_RUNTIME_INVALID;
    }
    component = (Vec3 *)world_get_component(simulation->desc.world, simulation->desc.user,
                                            BREAK_GAME_POSITION_COMPONENT);
    if (!component) return BREAK_RUNTIME_STALE;
    simulation->character.position = position;
    simulation->character.velocity = vec3(0.0f, 0.0f, 0.0f);
    simulation->character.grounded = false;
    simulation->character.ground_body = PHYSICS_BODY_HANDLE_INVALID;
    *component = position;
    return BREAK_RUNTIME_OK;
}

BreakRuntimeError core_app_simulation_user_velocity(
    const CoreAppSimulation *simulation, Vec3 *out) {
    if (!simulation || !out) return BREAK_RUNTIME_INVALID;
    *out = simulation->character.velocity;
    return BREAK_RUNTIME_OK;
}

BreakRuntimeError core_app_simulation_restore_user(CoreAppSimulation *simulation,
                                                   Vec3 position, Vec3 velocity) {
    if (!simulation || !isfinite(velocity.e[0]) || !isfinite(velocity.e[1]) ||
        !isfinite(velocity.e[2])) {
        return BREAK_RUNTIME_INVALID;
    }
    BreakRuntimeError result = core_app_simulation_place_user(simulation, position);
    if (result != BREAK_RUNTIME_OK) return result;
    simulation->character.velocity = velocity;
    return BREAK_RUNTIME_OK;
}

u64 core_app_simulation_tick_count(const CoreAppSimulation *simulation) {
    return simulation ? simulation->tick_count : 0u;
}

u32 core_app_accumulator_advance(CoreAppAccumulator *accumulator, u64 elapsed_ns) {
    u64 total;
    u64 steps;
    if (!accumulator) return 0u;
    total = elapsed_ns > UINT64_MAX - accumulator->remainder_ns
                ? UINT64_MAX : accumulator->remainder_ns + elapsed_ns;
    steps = total / CORE_APP_FIXED_DT_NS;
    accumulator->remainder_ns = total - steps * CORE_APP_FIXED_DT_NS;
    if (steps > CORE_APP_MAX_SUBSTEPS) {
        u64 dropped = (steps - CORE_APP_MAX_SUBSTEPS) * CORE_APP_FIXED_DT_NS;
        accumulator->dropped_ns = dropped > UINT64_MAX - accumulator->dropped_ns
                                      ? UINT64_MAX : accumulator->dropped_ns + dropped;
        steps = CORE_APP_MAX_SUBSTEPS;
    }
    return (u32)steps;
}
