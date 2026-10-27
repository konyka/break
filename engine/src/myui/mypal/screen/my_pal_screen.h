#ifndef MY_PAL_SCREEN_H
#define MY_PAL_SCREEN_H

#include "mypal/my_pal.h"

/** SCREEN_EVENT_MANAGER subtype used by a cooperating manager to request close. */
#define MY_PAL_SCREEN_MANAGER_CLOSE 0x4d595543u

my_pal_t* my_pal_screen_create(const my_allocator_t* allocator);
void* my_pal_screen_native_context(my_pal_t* pal);
void* my_pal_screen_native_window(my_pal_window_t* win);
uint32_t my_pal_screen_test_post_count(my_pal_window_t* win);

#endif
