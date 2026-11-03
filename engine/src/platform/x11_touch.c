#include <platform/x11_touch.h>

#ifdef ENGINE_X11_XINPUT2

InputExtResult x11_touch_event(InputExtended *input, u32 width, u32 height,
                               Window window, int event_type,
                               const XIDeviceEvent *event, u64 dispatch_ms)
{
    InputTouchPhase phase;
    i64 source_id;
    if (input == NULL || event == NULL || event->event != window ||
        event->sourceid < 0 || event->detail < 0)
        return INPUT_EXT_INVALID;
    source_id = ((i64)(u32)event->sourceid << 32) | (i64)(u32)event->detail;
    if (event_type == XI_TouchEnd)
        return input_extended_touch_end(input, source_id, false, dispatch_ms);
    if (event_type == XI_TouchBegin) phase = INPUT_TOUCH_PRESS;
    else if (event_type == XI_TouchUpdate) phase = INPUT_TOUCH_MOVE;
    else return INPUT_EXT_INVALID;
    return input_extended_touch_pixels(input, phase, source_id,
                                       (f32)event->event_x, (f32)event->event_y,
                                       width, height, dispatch_ms, NULL);
}

InputExtResult x11_touch_cancel(InputExtended *input, u64 dispatch_ms)
{
    if (input == NULL) return INPUT_EXT_INVALID;
    return input_extended_cancel_all(input, dispatch_ms);
}

#endif
