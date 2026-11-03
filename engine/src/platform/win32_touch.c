#include <platform/win32_touch.h>

InputExtResult win32_touch_message(InputExtended *input, u32 width, u32 height,
                                   UINT count, const TOUCHINPUT *inputs,
                                   BOOL query_ok, POINT origin, BOOL origin_ok,
                                   u64 dispatch_ms)
{
    InputExtResult result = INPUT_EXT_OK;
    if (input == NULL) return INPUT_EXT_INVALID;
    if (count > INPUT_MAX_TOUCH_EVENTS) {
        input_extended_note_overload(input);
        (void)input_extended_cancel_all(input, dispatch_ms);
        return INPUT_EXT_OVERLOAD;
    }
    if (count == 0u || inputs == NULL || !query_ok || !origin_ok) {
        (void)input_extended_cancel_all(input, dispatch_ms);
        return INPUT_EXT_FAILED;
    }
    for (UINT i = 0; i < count; i++) {
        const TOUCHINPUT *touch = &inputs[i];
        InputExtResult event_result;
        InputTouchPhase phase;
        f32 x = (f32)touch->x / 100.0f - (f32)origin.x;
        f32 y = (f32)touch->y / 100.0f - (f32)origin.y;
        if ((touch->dwFlags & TOUCHEVENTF_UP) != 0) {
            event_result = input_extended_touch_end(input, (i64)touch->dwID,
                                                    false, dispatch_ms);
        } else {
            if ((touch->dwFlags & TOUCHEVENTF_DOWN) != 0) phase = INPUT_TOUCH_PRESS;
            else if ((touch->dwFlags & TOUCHEVENTF_MOVE) != 0) phase = INPUT_TOUCH_MOVE;
            else continue;
            event_result = input_extended_touch_pixels(input, phase,
                                                       (i64)touch->dwID, x, y,
                                                       width, height, dispatch_ms, NULL);
        }
        if (result == INPUT_EXT_OK && event_result != INPUT_EXT_OK)
            result = event_result;
    }
    return result;
}

InputExtResult win32_touch_cancel(InputExtended *input, u64 dispatch_ms)
{
    if (input == NULL) return INPUT_EXT_INVALID;
    return input_extended_cancel_all(input, dispatch_ms);
}
