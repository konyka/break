#include <platform/input_extended.h>

#include <math.h>
#include <stdint.h>
#include <string.h>

#define INPUT_TAP_MAX_MS 300u
#define INPUT_LONG_PRESS_MS 500u
#define INPUT_SWIPE_MAX_MS 700u
#define INPUT_SINGLE_TRAVEL_SQ 0.0016f
#define INPUT_SWIPE_DISTANCE_SQ 0.0064f
#define INPUT_PINCH_EPSILON 0.000001f

static InputExtResult touch_result(InputExtended *s, InputExtResult result)
{
    s->touch_last_error = result;
    return result;
}

static void increment_bounded(u64 *value)
{
    if (*value != UINT64_MAX) (*value)++;
}

void input_extended_note_overload(InputExtended *s)
{
    if (s == NULL) return;
    increment_bounded(&s->dropped_touch_events);
    s->touch_last_error = INPUT_EXT_OVERLOAD;
}

static i32 find_source(const InputExtended *s, i64 source_id)
{
    for (u32 i = 0; i < INPUT_MAX_TOUCH_POINTS; i++) {
        if (s->touches[i].id != 0 && s->touches[i].source_id == source_id)
            return (i32)i;
    }
    return -1;
}

static i32 free_touch_slot(const InputExtended *s)
{
    for (u32 i = 0; i < INPUT_MAX_TOUCH_POINTS; i++) {
        if (s->touches[i].id == 0) return (i32)i;
    }
    return -1;
}

static u32 next_generation(u32 generation)
{
    generation++;
    return generation == 0u ? 1u : generation;
}

static InputTouchId make_id(u32 slot, u32 generation)
{
    return ((InputTouchId)generation << 32) | (InputTouchId)(slot + 1u);
}

static bool record_touch(InputExtended *s, InputTouchId id, i64 source_id,
                         InputTouchPhase phase, f32 x, f32 y, u64 time_ms)
{
    InputTouchEvent *event;
    if (s->touch_event_count >= INPUT_MAX_TOUCH_EVENTS) return false;
    event = &s->touch_events[s->touch_event_count++];
    event->id = id;
    event->source_id = source_id;
    event->phase = phase;
    event->x = x;
    event->y = y;
    event->time_ms = time_ms;
    return true;
}

static bool record_gesture(InputExtended *s, InputGestureType type,
                           InputTouchId primary_id, f32 x, f32 y,
                           f32 dx, f32 dy, f32 scale, f32 rotation)
{
    InputGesture *gesture;
    if (s->gesture_count >= INPUT_MAX_GESTURE_EVENTS) {
        increment_bounded(&s->dropped_gestures);
        return false;
    }
    gesture = &s->gestures[s->gesture_count++];
    memset(gesture, 0, sizeof(*gesture));
    gesture->type = type;
    gesture->primary_id = primary_id;
    gesture->x = x;
    gesture->y = y;
    gesture->dx = dx;
    gesture->dy = dy;
    gesture->scale = scale;
    gesture->rotation = rotation;
    return true;
}

static void reset_pinch(InputExtended *s)
{
    s->pinch_active = false;
    s->pinch_start_distance = 0.0f;
    s->pinch_start_angle = 0.0f;
}

static void start_pinch(InputExtended *s)
{
    const InputTouch *a = NULL;
    const InputTouch *b = NULL;
    f32 dx, dy;
    if (s->touch_count != 2u) {
        reset_pinch(s);
        return;
    }
    for (u32 i = 0; i < INPUT_MAX_TOUCH_POINTS; i++) {
        if (s->touches[i].id == 0) continue;
        if (a == NULL) a = &s->touches[i];
        else {
            b = &s->touches[i];
            break;
        }
    }
    dx = b->x - a->x;
    dy = b->y - a->y;
    s->pinch_start_distance = sqrtf(dx * dx + dy * dy);
    s->pinch_start_angle = atan2f(dy, dx);
    s->pinch_active = s->pinch_start_distance > INPUT_PINCH_EPSILON;
}

static bool emit_pinch(InputExtended *s)
{
    const InputTouch *a = NULL;
    const InputTouch *b = NULL;
    f32 dx, dy, distance, angle, rotation;
    if (s->touch_count != 2u) {
        reset_pinch(s);
        return true;
    }
    for (u32 i = 0; i < INPUT_MAX_TOUCH_POINTS; i++) {
        if (s->touches[i].id == 0) continue;
        if (a == NULL) a = &s->touches[i];
        else {
            b = &s->touches[i];
            break;
        }
    }
    dx = b->x - a->x;
    dy = b->y - a->y;
    distance = sqrtf(dx * dx + dy * dy);
    angle = atan2f(dy, dx);
    if (!s->pinch_active) {
        if (distance <= INPUT_PINCH_EPSILON) return true;
        s->pinch_active = true;
        s->pinch_start_distance = distance;
        s->pinch_start_angle = angle;
    }
    rotation = angle - s->pinch_start_angle;
    if (rotation > 3.14159265358979323846f) rotation -= 6.28318530717958647692f;
    else if (rotation < -3.14159265358979323846f) rotation += 6.28318530717958647692f;
    return record_gesture(s, INPUT_GESTURE_PINCH, a->id,
                          (a->x + b->x) * 0.5f, (a->y + b->y) * 0.5f,
                          0.0f, 0.0f, distance / s->pinch_start_distance,
                          rotation);
}

static void update_travel(InputTouch *touch, f32 x, f32 y)
{
    f32 dx = x - touch->start_x;
    f32 dy = y - touch->start_y;
    f32 travel_sq = dx * dx + dy * dy;
    if (travel_sq > touch->max_travel_sq) touch->max_travel_sq = travel_sq;
}

static InputExtResult end_touch(InputExtended *s, i32 slot,
                                InputTouchPhase phase, f32 x, f32 y,
                                u64 time_ms, InputTouchId *out_id)
{
    InputTouch *touch = &s->touches[slot];
    InputTouchId id = touch->id;
    InputExtResult result = INPUT_EXT_OK;
    bool recorded = record_touch(s, id, touch->source_id, phase, x, y, time_ms);
    if (out_id != NULL) *out_id = id;
    if (!recorded) {
        increment_bounded(&s->dropped_touch_events);
        result = INPUT_EXT_OVERLOAD;
    } else if (phase == INPUT_TOUCH_RELEASE && !touch->gesture_blocked) {
        u64 elapsed = time_ms >= touch->start_time_ms
                          ? time_ms - touch->start_time_ms : UINT64_MAX;
        f32 dx = x - touch->start_x;
        f32 dy = y - touch->start_y;
        f32 distance_sq = dx * dx + dy * dy;
        update_travel(touch, x, y);
        if (elapsed <= INPUT_TAP_MAX_MS &&
            touch->max_travel_sq <= INPUT_SINGLE_TRAVEL_SQ) {
            if (!record_gesture(s, INPUT_GESTURE_TAP, id, x, y,
                                0.0f, 0.0f, 1.0f, 0.0f))
                result = INPUT_EXT_OVERLOAD;
        } else if (!touch->long_press_sent && elapsed <= INPUT_SWIPE_MAX_MS &&
                   distance_sq >= INPUT_SWIPE_DISTANCE_SQ) {
            if (!record_gesture(s, INPUT_GESTURE_SWIPE, id, x, y,
                                dx, dy, 1.0f, 0.0f))
                result = INPUT_EXT_OVERLOAD;
        }
    }
    memset(touch, 0, sizeof(*touch));
    s->touch_count--;
    reset_pinch(s);
    return touch_result(s, result);
}

void input_extended_init(InputExtended *s)
{
    if (s == NULL) return;
    memset(s, 0, sizeof(*s));
    atomic_flag_clear(&s->haptic_lock);
    s->abi_version = INPUT_EXTENDED_ABI_VERSION;
    s->struct_size = (u32)sizeof(*s);
}

void input_extended_new_frame(InputExtended *s)
{
    if (s == NULL) return;
    s->touch_event_count = 0u;
    s->gesture_count = 0u;
    s->touch_last_error = INPUT_EXT_OK;
    for (u32 i = 0; i < INPUT_MAX_TOUCH_POINTS; i++) {
        if (s->touches[i].id != 0) s->touches[i].phase = INPUT_TOUCH_HELD;
    }
}

void input_extended_update(InputExtended *s, u64 time_ms)
{
    if (s == NULL) return;
    for (u32 i = 0; i < INPUT_MAX_TOUCH_POINTS; i++) {
        InputTouch *touch = &s->touches[i];
        if (touch->id == 0 || touch->gesture_blocked || touch->long_press_sent ||
            touch->max_travel_sq > INPUT_SINGLE_TRAVEL_SQ ||
            time_ms < touch->start_time_ms ||
            time_ms - touch->start_time_ms < INPUT_LONG_PRESS_MS)
            continue;
        if (record_gesture(s, INPUT_GESTURE_LONG_PRESS, touch->id,
                           touch->x, touch->y, 0.0f, 0.0f, 1.0f, 0.0f)) {
            touch->long_press_sent = true;
        } else {
            s->touch_last_error = INPUT_EXT_OVERLOAD;
        }
    }
}

InputExtResult input_extended_touch(InputExtended *s, InputTouchPhase phase,
                                    i64 source_id, f32 x, f32 y, u64 time_ms,
                                    InputTouchId *out_id)
{
    i32 slot;
    if (out_id != NULL) *out_id = 0;
    if (s == NULL || !isfinite(x) || !isfinite(y) ||
        x < 0.0f || x > 1.0f || y < 0.0f || y > 1.0f ||
        (phase != INPUT_TOUCH_PRESS && phase != INPUT_TOUCH_MOVE &&
         phase != INPUT_TOUCH_RELEASE && phase != INPUT_TOUCH_CANCEL))
        return INPUT_EXT_INVALID;
    slot = find_source(s, source_id);
    if (phase == INPUT_TOUCH_PRESS) {
        InputTouch touch;
        InputTouchId id;
        u32 generation;
        if (slot >= 0) return touch_result(s, INPUT_EXT_INVALID);
        slot = free_touch_slot(s);
        if (slot < 0) {
            increment_bounded(&s->dropped_touch_events);
            return touch_result(s, INPUT_EXT_OVERLOAD);
        }
        generation = next_generation(s->touch_generations[slot]);
        id = make_id((u32)slot, generation);
        if (!record_touch(s, id, source_id, phase, x, y, time_ms)) {
            increment_bounded(&s->dropped_touch_events);
            return touch_result(s, INPUT_EXT_OVERLOAD);
        }
        memset(&touch, 0, sizeof(touch));
        touch.id = id;
        touch.source_id = source_id;
        touch.phase = phase;
        touch.x = x;
        touch.y = y;
        touch.start_x = x;
        touch.start_y = y;
        touch.start_time_ms = time_ms;
        touch.gesture_blocked = s->touch_count != 0u;
        if (s->touch_count != 0u) {
            for (u32 i = 0; i < INPUT_MAX_TOUCH_POINTS; i++) {
                if (s->touches[i].id != 0) s->touches[i].gesture_blocked = true;
            }
        }
        s->touch_generations[slot] = generation;
        s->touches[slot] = touch;
        s->touch_count++;
        if (s->touch_count == 2u) start_pinch(s);
        else reset_pinch(s);
        if (out_id != NULL) *out_id = id;
        return touch_result(s, INPUT_EXT_OK);
    }
    if (slot < 0) return touch_result(s, INPUT_EXT_STALE);
    if (phase == INPUT_TOUCH_RELEASE || phase == INPUT_TOUCH_CANCEL)
        return end_touch(s, slot, phase, x, y, time_ms, out_id);
    {
        InputTouch *touch = &s->touches[slot];
        InputTouchId id = touch->id;
        if (!record_touch(s, id, source_id, phase, x, y, time_ms)) {
            increment_bounded(&s->dropped_touch_events);
            return touch_result(s, INPUT_EXT_OVERLOAD);
        }
        update_travel(touch, x, y);
        touch->x = x;
        touch->y = y;
        touch->phase = INPUT_TOUCH_MOVE;
        if (out_id != NULL) *out_id = id;
        if (!emit_pinch(s)) return touch_result(s, INPUT_EXT_OVERLOAD);
    }
    return touch_result(s, INPUT_EXT_OK);
}

InputExtResult input_extended_touch_pixels(InputExtended *s, InputTouchPhase phase,
                                           i64 source_id, f32 x, f32 y,
                                           u32 width, u32 height, u64 time_ms,
                                           InputTouchId *out_id)
{
    if (out_id != NULL) *out_id = 0;
    if (s == NULL || width == 0u || height == 0u || !isfinite(x) || !isfinite(y) ||
        x < 0.0f || y < 0.0f || x > (f32)width || y > (f32)height) {
        if (s != NULL) s->touch_last_error = INPUT_EXT_INVALID;
        return INPUT_EXT_INVALID;
    }
    return input_extended_touch(s, phase, source_id, x / (f32)width,
                                y / (f32)height, time_ms, out_id);
}

InputExtResult input_extended_touch_end(InputExtended *s, i64 source_id,
                                        bool cancel, u64 time_ms)
{
    i32 slot;
    InputTouch *touch;
    if (s == NULL) return INPUT_EXT_INVALID;
    slot = find_source(s, source_id);
    if (slot < 0) return touch_result(s, INPUT_EXT_STALE);
    touch = &s->touches[slot];
    return end_touch(s, slot, cancel ? INPUT_TOUCH_CANCEL : INPUT_TOUCH_RELEASE,
                     touch->x, touch->y, time_ms, NULL);
}

InputExtResult input_extended_cancel_all(InputExtended *s, u64 time_ms)
{
    InputExtResult result = INPUT_EXT_OK;
    if (s == NULL) return INPUT_EXT_INVALID;
    for (u32 i = 0; i < INPUT_MAX_TOUCH_POINTS; i++) {
        InputTouch *touch;
        InputExtResult ended;
        if (s->touches[i].id == 0) continue;
        touch = &s->touches[i];
        ended = end_touch(s, (i32)i, INPUT_TOUCH_CANCEL,
                          touch->x, touch->y, time_ms, NULL);
        if (ended != INPUT_EXT_OK) result = ended;
    }
    return touch_result(s, result);
}

enum {
    HAPTIC_SLOT_FREE = 0,
    HAPTIC_SLOT_QUEUED,
    HAPTIC_SLOT_RUNNING,
    HAPTIC_SLOT_COMPLETE,
};

static void haptic_lock(const InputExtended *s)
{
    atomic_flag *lock = (atomic_flag *)&s->haptic_lock;
    while (atomic_flag_test_and_set_explicit(lock, memory_order_acquire)) {
    }
}

static void haptic_unlock(const InputExtended *s)
{
    atomic_flag *lock = (atomic_flag *)&s->haptic_lock;
    atomic_flag_clear_explicit(lock, memory_order_release);
}

InputExtResult input_extended_pad_status(const InputExtended *s, u32 pad,
                                         InputPadFeedbackStatus *out)
{
    if (s == NULL || out == NULL || pad >= INPUT_MAX_GAMEPADS)
        return INPUT_EXT_INVALID;
    haptic_lock(s);
    *out = s->pads[pad];
    haptic_unlock(s);
    return INPUT_EXT_OK;
}

void input_extended_backend_pad(InputExtended *s, u32 pad, bool connected,
                                bool feedback_available, u32 connection_serial)
{
    InputPadFeedbackStatus *status;
    if (s == NULL || pad >= INPUT_MAX_GAMEPADS) return;
    haptic_lock(s);
    status = &s->pads[pad];
    if (connected && (!status->connected || s->pad_serials[pad] != connection_serial)) {
        status->generation = next_generation(status->generation);
    }
    status->connected = connected;
    status->feedback_available = connected && feedback_available;
    s->pad_serials[pad] = connection_serial;
    haptic_unlock(s);
}

InputExtResult input_extended_request_haptic(InputExtended *s, u32 pad,
                                             f32 low, f32 high, u32 duration_ms,
                                             u64 *out_request_id)
{
    InputExtResult result = INPUT_EXT_OK;
    u32 slot;
    if (out_request_id != NULL) *out_request_id = 0;
    if (s == NULL || out_request_id == NULL || pad >= INPUT_MAX_GAMEPADS ||
        !isfinite(low) || !isfinite(high) ||
        low < 0.0f || low > 1.0f || high < 0.0f || high > 1.0f ||
        duration_ms > INPUT_HAPTIC_MAX_DURATION_MS)
        return INPUT_EXT_INVALID;
    haptic_lock(s);
    if (!s->pads[pad].connected) {
        result = INPUT_EXT_DISCONNECTED;
        goto done;
    }
    if (!s->pads[pad].feedback_available) {
        result = INPUT_EXT_UNSUPPORTED;
        goto done;
    }
    for (slot = 0; slot < INPUT_MAX_HAPTIC_COMMANDS; slot++) {
        if (s->haptic_slots[slot].state == HAPTIC_SLOT_FREE) break;
    }
    if (slot == INPUT_MAX_HAPTIC_COMMANDS) {
        result = INPUT_EXT_OVERLOAD;
        goto done;
    }
    s->next_request_id++;
    if (s->next_request_id == 0) s->next_request_id++;
    s->haptic_slots[slot].command.request_id = s->next_request_id;
    s->haptic_slots[slot].command.pad = pad;
    s->haptic_slots[slot].command.generation = s->pads[pad].generation;
    s->haptic_slots[slot].command.low = low;
    s->haptic_slots[slot].command.high = high;
    s->haptic_slots[slot].command.duration_ms = duration_ms;
    s->haptic_slots[slot].result = INPUT_EXT_PENDING;
    s->haptic_slots[slot].state = HAPTIC_SLOT_QUEUED;
    s->haptic_count++;
    if (out_request_id != NULL) *out_request_id = s->next_request_id;

done:
    haptic_unlock(s);
    return result;
}

InputExtResult input_extended_haptic_result(InputExtended *s, u64 request_id)
{
    InputExtResult result = INPUT_EXT_STALE;
    if (s == NULL || request_id == 0) return INPUT_EXT_INVALID;
    haptic_lock(s);
    for (u32 i = 0; i < INPUT_MAX_HAPTIC_COMMANDS; i++) {
        InputHapticSlot *slot = &s->haptic_slots[i];
        if (slot->state == HAPTIC_SLOT_FREE || slot->command.request_id != request_id)
            continue;
        if (slot->state == HAPTIC_SLOT_COMPLETE) {
            result = slot->result;
            memset(slot, 0, sizeof(*slot));
            s->haptic_count--;
        } else {
            result = INPUT_EXT_PENDING;
        }
        break;
    }
    haptic_unlock(s);
    return result;
}

InputExtResult input_extended_haptic_pump(InputExtended *s,
                                          InputHapticExecuteFn execute,
                                          void *context)
{
    if (s == NULL || execute == NULL) return INPUT_EXT_INVALID;
    haptic_lock(s);
    if (s->haptic_pumping) {
        haptic_unlock(s);
        return INPUT_EXT_REJECTED;
    }
    s->haptic_pumping = true;
    haptic_unlock(s);

    for (u32 budget = 0; budget < INPUT_HAPTIC_DRAIN_BUDGET; budget++) {
        InputHapticCommand command;
        InputExtResult result = INPUT_EXT_OK;
        u32 index = INPUT_MAX_HAPTIC_COMMANDS;
        haptic_lock(s);
        for (u32 offset = 0; offset < INPUT_MAX_HAPTIC_COMMANDS; offset++) {
            u32 candidate = (s->haptic_cursor + offset) % INPUT_MAX_HAPTIC_COMMANDS;
            if (s->haptic_slots[candidate].state == HAPTIC_SLOT_QUEUED) {
                index = candidate;
                break;
            }
        }
        if (index == INPUT_MAX_HAPTIC_COMMANDS) {
            s->haptic_pumping = false;
            haptic_unlock(s);
            return INPUT_EXT_OK;
        }
        s->haptic_cursor = (index + 1u) % INPUT_MAX_HAPTIC_COMMANDS;
        command = s->haptic_slots[index].command;
        if (!s->pads[command.pad].connected) {
            result = INPUT_EXT_DISCONNECTED;
        } else if (s->pads[command.pad].generation != command.generation) {
            result = INPUT_EXT_STALE;
        } else if (!s->pads[command.pad].feedback_available) {
            result = INPUT_EXT_UNSUPPORTED;
        }
        if (result != INPUT_EXT_OK) {
            s->haptic_slots[index].result = result;
            s->haptic_slots[index].state = HAPTIC_SLOT_COMPLETE;
            haptic_unlock(s);
            continue;
        }
        s->haptic_slots[index].state = HAPTIC_SLOT_RUNNING;
        haptic_unlock(s);

        result = execute(context, &command);
        if (result == INPUT_EXT_PENDING) result = INPUT_EXT_FAILED;

        haptic_lock(s);
        s->haptic_slots[index].result = result;
        s->haptic_slots[index].state = HAPTIC_SLOT_COMPLETE;
        haptic_unlock(s);
    }

    haptic_lock(s);
    s->haptic_pumping = false;
    haptic_unlock(s);
    return INPUT_EXT_OK;
}
