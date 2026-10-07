/**
 * @file my_pal_win32.h
 * @brief Win32 PAL port: message-pump windows, DIB lcd, WGL GLES2.
 */
#ifndef MY_PAL_WIN32_H
#define MY_PAL_WIN32_H

#include "myc/my_mem.h"
#include "mypal/my_pal.h"

my_pal_t* my_pal_win32_create(const my_allocator_t* allocator);

#endif
