#pragma once

#include <platform/input_extended.h>
#include <wayland-client.h>

InputExtResult wayland_touch_down(InputExtended *input, u32 width, u32 height,
                                  struct wl_surface *target,
                                  struct wl_surface *surface, i32 id,
                                  wl_fixed_t x, wl_fixed_t y, u32 os_time_ms,
                                  u64 dispatch_ms);
InputExtResult wayland_touch_motion(InputExtended *input, u32 width, u32 height,
                                    i32 id, wl_fixed_t x, wl_fixed_t y,
                                    u32 os_time_ms, u64 dispatch_ms);
InputExtResult wayland_touch_up(InputExtended *input, i32 id, u32 os_time_ms,
                                u64 dispatch_ms);
InputExtResult wayland_touch_cancel(InputExtended *input, u64 dispatch_ms);
