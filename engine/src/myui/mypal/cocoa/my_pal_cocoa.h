/**
 * @file my_pal_cocoa.h
 * @brief macOS PAL port: Cocoa windows, NSBitmapImageRep lcd, NSOpenGL.
 */
#ifndef MY_PAL_COCOA_H
#define MY_PAL_COCOA_H

#include "myc/my_mem.h"
#include "mypal/my_pal.h"

my_pal_t* my_pal_cocoa_create(const my_allocator_t* allocator);

#endif
