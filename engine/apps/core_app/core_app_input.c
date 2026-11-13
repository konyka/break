#include "core_app_input.h"

#include <stdlib.h>
#include <string.h>

struct CoreAppInput {
    InputState state;
    InputExtended extended;
    u32 tick;
    u64 time_ms;
    bool started;
    InputExtResult touch_status;
    InputExtResult haptic_status;
    u64 haptic_request_id;
};

static BreakRuntimeError from_ext(InputExtResult result) {
    switch (result) {
    case INPUT_EXT_OK:
        return BREAK_RUNTIME_OK;
    case INPUT_EXT_OVERLOAD:
        return BREAK_RUNTIME_OVERLOAD;
    case INPUT_EXT_STALE:
        return BREAK_RUNTIME_STALE;
    case INPUT_EXT_DISCONNECTED:
    case INPUT_EXT_UNSUPPORTED:
    case INPUT_EXT_REJECTED:
        return BREAK_RUNTIME_REJECTED;
    case INPUT_EXT_INVALID:
        return BREAK_RUNTIME_INVALID;
    default:
        return BREAK_RUNTIME_FAILED;
    }
}

static InputTouchPhase touch_phase(CoreAppScenarioTouchPhase phase) {
    switch (phase) {
    case CORE_APP_SCENARIO_TOUCH_DOWN:
        return INPUT_TOUCH_PRESS;
    case CORE_APP_SCENARIO_TOUCH_MOVE:
        return INPUT_TOUCH_MOVE;
    case CORE_APP_SCENARIO_TOUCH_UP:
        return INPUT_TOUCH_RELEASE;
    default:
        return INPUT_TOUCH_CANCEL;
    }
}

CoreAppInput *core_app_input_create(void) {
    CoreAppInput *input = (CoreAppInput *)calloc(1u, sizeof(*input));
    if (!input) return NULL;
    input_init(&input->state);
    input_extended_init(&input->extended);
    return input;
}

void core_app_input_destroy(CoreAppInput *input) {
    free(input);
}

BreakRuntimeError core_app_input_begin_tick(CoreAppInput *input, u32 tick,
                                            u64 time_ms) {
    if (!input || (input->started && tick <= input->tick)) {
        return BREAK_RUNTIME_INVALID;
    }
    input_new_frame(&input->state);
    input_extended_new_frame(&input->extended);
    input_extended_update(&input->extended, time_ms);
    input->tick = tick;
    input->time_ms = time_ms;
    input->started = true;
    input->touch_status = INPUT_EXT_OK;
    return BREAK_RUNTIME_OK;
}

BreakRuntimeError core_app_input_apply(CoreAppInput *input,
                                       const CoreAppScenarioEvent *event) {
    if (!input || !event || !input->started || event->tick != input->tick) {
        return BREAK_RUNTIME_INVALID;
    }
    switch (event->kind) {
    case CORE_APP_SCENARIO_KEY:
        if (event->key_code < 0 || event->key_code >= INPUT_MAX_KEYS) {
            return BREAK_RUNTIME_INVALID;
        }
        input_set_key(&input->state, event->key_code, event->key_down != 0);
        return BREAK_RUNTIME_OK;
    case CORE_APP_SCENARIO_TOUCH: {
        InputExtResult result = input_extended_touch(
            &input->extended, touch_phase(event->touch_phase),
            event->touch_source, event->x, event->y, input->time_ms, NULL);
        input->touch_status = result;
        return from_ext(result);
    }
    case CORE_APP_SCENARIO_PAD: {
        GamepadState *pad;
        if (event->pad >= INPUT_MAX_GAMEPADS || event->axis >= INPUT_MAX_AXES) {
            return BREAK_RUNTIME_INVALID;
        }
        pad = &input->state.gamepads[event->pad];
        pad->connected = true;
        pad->axes[event->axis] = event->value;
        return BREAK_RUNTIME_OK;
    }
    default:
        return BREAK_RUNTIME_INVALID;
    }
}

BreakRuntimeError core_app_input_frame(const CoreAppInput *input,
                                       CoreAppInputFrame *out) {
    u32 i;
    if (!out) return BREAK_RUNTIME_INVALID;
    memset(out, 0, sizeof(*out));
    if (!input) return BREAK_RUNTIME_INVALID;
    out->state = input->state;
    for (i = 0u; i < INPUT_MAX_TOUCH_POINTS; ++i) {
        if (input->extended.touches[i].id != 0u &&
            out->touch_count < CORE_APP_INPUT_MAX_TOUCHES) {
            out->touches[out->touch_count++] = input->extended.touches[i];
        }
    }
    for (i = 0u; i < input->extended.gesture_count &&
                 i < CORE_APP_INPUT_MAX_GESTURES; ++i) {
        out->gestures[out->gesture_count++] = input->extended.gestures[i];
    }
    out->touch_status = input->touch_status;
    out->haptic_status = input->haptic_status;
    out->haptic_request_id = input->haptic_request_id;
    out->tick = input->tick;
    out->time_ms = input->time_ms;
    return BREAK_RUNTIME_OK;
}

BreakRuntimeError core_app_input_request_area_haptic(CoreAppInput *input,
                                                     u32 pad, f32 low, f32 high,
                                                     u32 duration_ms) {
    u64 request_id = 0u;
    InputExtResult result;
    if (!input) return BREAK_RUNTIME_INVALID;
    result = input_extended_request_haptic(&input->extended, pad, low, high,
                                           duration_ms, &request_id);
    input->haptic_status = result;
    input->haptic_request_id = request_id;
    return from_ext(result);
}

BreakRuntimeError core_app_input_haptic_result(CoreAppInput *input,
                                               u64 request_id,
                                               InputExtResult *out) {
    if (!out) return BREAK_RUNTIME_INVALID;
    *out = INPUT_EXT_INVALID;
    if (!input) return BREAK_RUNTIME_INVALID;
    *out = input_extended_haptic_result(&input->extended, request_id);
    return BREAK_RUNTIME_OK;
}

void core_app_input_backend_pad(CoreAppInput *input, u32 pad, bool connected,
                                bool feedback_available, u32 connection_serial) {
    if (!input) return;
    input_extended_backend_pad(&input->extended, pad, connected,
                               feedback_available, connection_serial);
}

BreakRuntimeError core_app_input_pump_haptics(CoreAppInput *input,
                                              InputHapticExecuteFn execute,
                                              void *context) {
    if (!input || !execute) return BREAK_RUNTIME_INVALID;
    return from_ext(input_extended_haptic_pump(&input->extended, execute, context));
}
