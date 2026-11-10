#include "platform/platform_wsi.h"

#ifndef EXPECTED_BACKEND_VALUE
#error "EXPECTED_BACKEND_VALUE is required"
#endif

_Static_assert(PLATFORM_WSI_BACKEND_WAYLAND == 1, "Wayland ABI changed");
_Static_assert(PLATFORM_WSI_BACKEND_WIN32 == 2, "Win32 ABI changed");
_Static_assert(PLATFORM_WSI_BACKEND_COCOA == 3, "Cocoa ABI changed");
_Static_assert(PLATFORM_WSI_BACKEND_ANDROID == 4, "Android ABI changed");
_Static_assert(PLATFORM_WSI_BACKEND_IOS == 5, "iOS ABI changed");
_Static_assert((int)PLATFORM_WSI_COMPILE_BACKEND == EXPECTED_BACKEND_VALUE,
               "platform macro priority or unavailable sentinel changed");
