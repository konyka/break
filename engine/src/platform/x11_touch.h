#pragma once

#include <platform/input_extended.h>

#ifdef ENGINE_X11_XINPUT2
#include <X11/extensions/XInput2.h>

InputExtResult x11_touch_event(InputExtended *input, u32 width, u32 height,
                               Window window, int event_type,
                               const XIDeviceEvent *event, u64 dispatch_ms);
InputExtResult x11_touch_cancel(InputExtended *input, u64 dispatch_ms);
#endif
