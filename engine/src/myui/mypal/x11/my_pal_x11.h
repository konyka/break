/**
 * @file my_pal_x11.h
 * @brief X11 PAL port: real windows, XImage presentation, EGL GLES2.
 */
#ifndef MY_PAL_X11_H
#define MY_PAL_X11_H

#include "myc/my_mem.h"
#include "mypal/my_pal.h"

my_pal_t* my_pal_x11_create(const my_allocator_t* allocator);

#endif
