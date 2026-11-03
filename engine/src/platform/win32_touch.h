#pragma once

#include <platform/input_extended.h>
#include <windows.h>

InputExtResult win32_touch_message(InputExtended *input, u32 width, u32 height,
                                   UINT count, const TOUCHINPUT *inputs,
                                   BOOL query_ok, POINT origin, BOOL origin_ok,
                                   u64 dispatch_ms);
InputExtResult win32_touch_cancel(InputExtended *input, u64 dispatch_ms);
