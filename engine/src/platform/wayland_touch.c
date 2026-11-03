#include <platform/wayland_touch.h>

InputExtResult wayland_touch_down(InputExtended *input, u32 width, u32 height,
                                  struct wl_surface *target,
                                  struct wl_surface *surface, i32 id,
                                  wl_fixed_t x, wl_fixed_t y, u32 os_time_ms,
                                  u64 dispatch_ms)
{
    (void)os_time_ms;
    if (input == NULL || target == NULL || surface != target)
        return INPUT_EXT_INVALID;
    return input_extended_touch_pixels(input, INPUT_TOUCH_PRESS, id,
                                       (f32)wl_fixed_to_double(x),
                                       (f32)wl_fixed_to_double(y),
                                       width, height, dispatch_ms, NULL);
}

InputExtResult wayland_touch_motion(InputExtended *input, u32 width, u32 height,
                                    i32 id, wl_fixed_t x, wl_fixed_t y,
                                    u32 os_time_ms, u64 dispatch_ms)
{
    (void)os_time_ms;
    if (input == NULL) return INPUT_EXT_INVALID;
    return input_extended_touch_pixels(input, INPUT_TOUCH_MOVE, id,
                                       (f32)wl_fixed_to_double(x),
                                       (f32)wl_fixed_to_double(y),
                                       width, height, dispatch_ms, NULL);
}

InputExtResult wayland_touch_up(InputExtended *input, i32 id, u32 os_time_ms,
                                u64 dispatch_ms)
{
    (void)os_time_ms;
    if (input == NULL) return INPUT_EXT_INVALID;
    return input_extended_touch_end(input, id, false, dispatch_ms);
}

InputExtResult wayland_touch_cancel(InputExtended *input, u64 dispatch_ms)
{
    if (input == NULL) return INPUT_EXT_INVALID;
    return input_extended_cancel_all(input, dispatch_ms);
}
