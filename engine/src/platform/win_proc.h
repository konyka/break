#pragma once
/* Typed function pointers from the Windows dynamic loaders.
 *
 * The loaders return a generic FARPROC (or the OpenGL loader's equivalent
 * PROC). Casting it straight to the typed function pointer is rejected by GCC
 * (-Wcast-function-type), and going through void * is rejected by -Wpedantic,
 * so the bytes are copied instead (the same approach platform_vk_surface.c
 * uses for the Vulkan loader).
 *
 * `dst` must be an lvalue of function-pointer type and `proc` an expression of
 * a pointer-sized function-pointer type. */
#include <string.h>

#define WIN_PROC_LOAD(dst, proc)                      \
    do {                                              \
        __typeof__(proc) win_proc_tmp_ = (proc);      \
        memcpy(&(dst), &win_proc_tmp_, sizeof(dst));  \
    } while (0)
