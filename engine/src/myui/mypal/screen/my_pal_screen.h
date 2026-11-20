#ifndef MY_PAL_SCREEN_H
#define MY_PAL_SCREEN_H

#include "mypal/my_pal.h"

/** SCREEN_EVENT_MANAGER subtype used by a cooperating manager to request close. */
#define MY_PAL_SCREEN_MANAGER_CLOSE 0x4d595543u

typedef struct my_pal_screen_ime_state_t {
  bool enabled;
  const char* surrounding;
  int32_t cursor;
  int32_t anchor;
  int32_t spot_x;
  int32_t spot_y;
} my_pal_screen_ime_state_t;

my_pal_t* my_pal_screen_create(const my_allocator_t* allocator);
void* my_pal_screen_native_context(my_pal_t* pal);
void* my_pal_screen_native_window(my_pal_window_t* win);

/* Clipboard text is stored per PAL instance in this process, never by Screen. */
bool my_pal_screen_clipboard_is_process_local(void);
/* Screen has no native preedit/surrounding/spot protocol in this port. */
bool my_pal_screen_has_native_ime(void);

typedef struct my_pal_screen_software_cursor_state_t {
  my_cursor_t shape;
  int32_t x;
  int32_t y;
  bool enabled;
  bool has_position;
  bool visible;
} my_pal_screen_software_cursor_state_t;

/* Opt in to an application-composited cursor on this window's software LCD.
 * Changes appear on the next software, CPU GLES readback, or Vulkan readback
 * frame. The native pointer-session path is unchanged. */
my_ret_t my_pal_screen_software_cursor_set_enabled(my_pal_window_t* win,
                                                   bool enabled);
my_ret_t my_pal_screen_test_software_cursor_state(
    my_pal_window_t* win, my_pal_screen_software_cursor_state_t* out);

void* my_pal_screen_test_native_pointer_session(my_pal_window_t* win);
/* surrounding is borrowed until the next IME setter or window destruction. */
my_ret_t my_pal_screen_test_ime_state(my_pal_window_t* win,
                                      my_pal_screen_ime_state_t* out);
uint32_t my_pal_screen_test_post_count(my_pal_window_t* win);

#endif
