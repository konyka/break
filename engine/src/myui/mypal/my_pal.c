/**
 * @file my_pal.c
 * @brief Platform entry point: dispatches to the compile-time port.
 */
#include "mypal/my_pal.h"

#include "mypal/dummy/my_pal_dummy.h"

#if defined(MYUI_PAL_X11)
#include "mypal/x11/my_pal_x11.h"
#elif defined(MYUI_PAL_WAYLAND)
#include "mypal/wayland/my_pal_wayland.h"
#elif defined(MYUI_PAL_LINUX_FB)
#include "mypal/linux_fb/my_pal_linux_fb.h"
#elif defined(MYUI_PAL_WIN32)
#include "mypal/win32/my_pal_win32.h"
#elif defined(MYUI_PAL_COCOA)
#include "mypal/cocoa/my_pal_cocoa.h"
#endif

my_pal_t* my_pal_create(const my_allocator_t* allocator) {
#if defined(MYUI_PAL_X11)
  my_pal_t* pal = my_pal_x11_create(allocator);
  if (pal != NULL) {
    return pal;
  }
  return my_pal_dummy_create(allocator);
#elif defined(MYUI_PAL_WAYLAND)
  {
    my_pal_t* pal = my_pal_wayland_create(allocator);
    if (pal != NULL) {
      return pal;
    }
    return my_pal_dummy_create(allocator);
  }
#elif defined(MYUI_PAL_LINUX_FB)
  return my_pal_linux_fb_create(allocator, NULL, NULL, NULL);
#elif defined(MYUI_PAL_WIN32)
  return my_pal_win32_create(allocator);
#elif defined(MYUI_PAL_COCOA)
  return my_pal_cocoa_create(allocator);
#else
  return my_pal_dummy_create(allocator);
#endif
}
