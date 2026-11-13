#pragma once

#include "scenario.h"

#include <core/types.h>
#include <platform/input.h>
#include <platform/input_extended.h>
#include <runtime/runtime_types.h>

#define CORE_APP_INPUT_MAX_TOUCHES INPUT_MAX_TOUCH_POINTS
#define CORE_APP_INPUT_MAX_GESTURES INPUT_MAX_GESTURE_EVENTS

typedef struct CoreAppInputFrame {
    InputState state;
    InputTouch touches[CORE_APP_INPUT_MAX_TOUCHES];
    u32 touch_count;
    InputGesture gestures[CORE_APP_INPUT_MAX_GESTURES];
    u32 gesture_count;
    InputExtResult touch_status;
    InputExtResult haptic_status;
    u64 haptic_request_id;
    u32 tick;
    u64 time_ms;
} CoreAppInputFrame;

typedef struct CoreAppInput CoreAppInput;

CoreAppInput *core_app_input_create(void);
void core_app_input_destroy(CoreAppInput *input);
BreakRuntimeError core_app_input_begin_tick(CoreAppInput *input, u32 tick,
                                            u64 time_ms);
BreakRuntimeError core_app_input_apply(CoreAppInput *input,
                                       const CoreAppScenarioEvent *event);
BreakRuntimeError core_app_input_frame(const CoreAppInput *input,
                                       CoreAppInputFrame *out);
BreakRuntimeError core_app_input_request_area_haptic(CoreAppInput *input,
                                                     u32 pad, f32 low, f32 high,
                                                     u32 duration_ms);
BreakRuntimeError core_app_input_haptic_result(CoreAppInput *input,
                                               u64 request_id,
                                               InputExtResult *out);
BreakRuntimeError core_app_input_snapshot(const InputState *state,
                                          const InputExtended *extended,
                                          CoreAppInputFrame *out);
BreakRuntimeError core_app_input_pad_generation(const CoreAppInput *input, u32 pad,
                                                u32 *out);
void core_app_input_backend_pad(CoreAppInput *input, u32 pad, bool connected,
                                bool feedback_available, u32 connection_serial);
BreakRuntimeError core_app_input_pump_haptics(CoreAppInput *input,
                                              InputHapticExecuteFn execute,
                                              void *context);
