#pragma once

#include <core/types.h>
#include <platform/input.h>
#include <stdatomic.h>

#define INPUT_EXTENDED_ABI_VERSION 1u
#define INPUT_MAX_TOUCH_POINTS 16u
#define INPUT_MAX_TOUCH_EVENTS 32u
#define INPUT_MAX_GESTURE_EVENTS 16u
#define INPUT_MAX_HAPTIC_COMMANDS 32u
#define INPUT_HAPTIC_DRAIN_BUDGET 8u
#define INPUT_HAPTIC_MAX_DURATION_MS 5000u

typedef enum {
    INPUT_EXT_OK = 0,
    INPUT_EXT_INVALID,
    INPUT_EXT_OVERLOAD,
    INPUT_EXT_STALE,
    INPUT_EXT_DISCONNECTED,
    INPUT_EXT_UNSUPPORTED,
    INPUT_EXT_FAILED,
    INPUT_EXT_PENDING,
    INPUT_EXT_REJECTED,
} InputExtResult;

typedef u64 InputTouchId;

typedef enum {
    INPUT_TOUCH_PRESS = 0,
    INPUT_TOUCH_MOVE,
    INPUT_TOUCH_RELEASE,
    INPUT_TOUCH_CANCEL,
    INPUT_TOUCH_HELD,
} InputTouchPhase;

typedef enum {
    INPUT_GESTURE_TAP = 0,
    INPUT_GESTURE_LONG_PRESS,
    INPUT_GESTURE_SWIPE,
    INPUT_GESTURE_PINCH,
} InputGestureType;

typedef struct {
    InputTouchId id;
    i64 source_id;
    InputTouchPhase phase;
    f32 x, y;
    f32 start_x, start_y;
    f32 max_travel_sq;
    u64 start_time_ms;
    bool gesture_blocked;
    bool long_press_sent;
} InputTouch;

typedef struct {
    InputTouchId id;
    i64 source_id;
    InputTouchPhase phase;
    f32 x, y;
    u64 time_ms;
} InputTouchEvent;

typedef struct {
    InputGestureType type;
    InputTouchId primary_id;
    f32 x, y;
    f32 dx, dy;
    f32 scale;
    f32 rotation;
} InputGesture;

typedef struct {
    bool connected;
    bool feedback_available;
    u32 generation;
} InputPadFeedbackStatus;

typedef struct {
    u64 request_id;
    u32 pad;
    u32 generation;
    f32 low, high;
    u32 duration_ms;
} InputHapticCommand;

typedef InputExtResult (*InputHapticExecuteFn)(void *context,
                                               const InputHapticCommand *command);

typedef struct {
    InputHapticCommand command;
    InputExtResult result;
    u8 state;
} InputHapticSlot;

typedef struct {
    u32 abi_version;
    u32 struct_size;
    InputTouch touches[INPUT_MAX_TOUCH_POINTS];
    u32 touch_count;
    InputTouchEvent touch_events[INPUT_MAX_TOUCH_EVENTS];
    u32 touch_event_count;
    InputGesture gestures[INPUT_MAX_GESTURE_EVENTS];
    u32 gesture_count;
    u64 dropped_touch_events;
    u64 dropped_gestures;
    InputExtResult touch_last_error;
    u32 touch_generations[INPUT_MAX_TOUCH_POINTS];
    bool pinch_active;
    f32 pinch_start_distance;
    f32 pinch_start_angle;
    InputPadFeedbackStatus pads[INPUT_MAX_PADS];
    u32 pad_serials[INPUT_MAX_PADS];
    InputHapticSlot haptic_slots[INPUT_MAX_HAPTIC_COMMANDS];
    u32 haptic_count;
    u32 haptic_cursor;
    u64 next_request_id;
    bool haptic_pumping;
    atomic_flag haptic_lock;
} InputExtended;

void input_extended_init(InputExtended *s);
void input_extended_new_frame(InputExtended *s);
void input_extended_update(InputExtended *s, u64 time_ms);
InputExtResult input_extended_touch(InputExtended *s, InputTouchPhase phase,
                                    i64 source_id, f32 x, f32 y, u64 time_ms,
                                    InputTouchId *out_id);
InputExtResult input_extended_touch_pixels(InputExtended *s, InputTouchPhase phase,
                                           i64 source_id, f32 x, f32 y,
                                           u32 width, u32 height, u64 time_ms,
                                           InputTouchId *out_id);
InputExtResult input_extended_touch_end(InputExtended *s, i64 source_id,
                                        bool cancel, u64 time_ms);
InputExtResult input_extended_cancel_all(InputExtended *s, u64 time_ms);
void input_extended_note_overload(InputExtended *s);

InputExtResult input_extended_pad_status(const InputExtended *s, u32 pad,
                                         InputPadFeedbackStatus *out);
void input_extended_backend_pad(InputExtended *s, u32 pad, bool connected,
                                bool feedback_available, u32 connection_serial);
InputExtResult input_extended_request_haptic(InputExtended *s, u32 pad,
                                             f32 low, f32 high, u32 duration_ms,
                                             u64 *out_request_id);
InputExtResult input_extended_haptic_result(InputExtended *s, u64 request_id);
InputExtResult input_extended_haptic_pump(InputExtended *s,
                                          InputHapticExecuteFn execute,
                                          void *context);
