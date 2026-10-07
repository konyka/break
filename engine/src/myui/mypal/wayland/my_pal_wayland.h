/**
 * @file my_pal_wayland.h
 * @brief Wayland PAL port: xdg-shell windows, wl_shm lcd, EGL GLES2.
 */
#ifndef MY_PAL_WAYLAND_H
#define MY_PAL_WAYLAND_H

#include "myc/my_mem.h"
#include "mypal/my_pal.h"

my_pal_t* my_pal_wayland_create(const my_allocator_t* allocator);

#endif
