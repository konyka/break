/**
 * @file my_gl_desktop_internal.h
 * @brief Test seam for the Win32 WGL pointer-resolution contract of
 *        my_gl_desktop.c.
 *
 * The desktop GL table on Windows resolves GL 1.2+/2.0 entry points
 * through wglGetProcAddress, which documents several garbage return
 * values for unavailable extensions (0, 1, 2, 3, -1 depending on the
 * driver lineage). The helpers below convert between function pointers
 * and integer addresses through a union (defined behavior in C11) so
 * the rejection logic stays unit-testable and -pedantic clean without
 * casting function pointers through void*.
 */
#ifndef MY_GL_DESKTOP_INTERNAL_H
#define MY_GL_DESKTOP_INTERNAL_H

#include "myc/my_types.h"

#include <stdbool.h>
#include <stdint.h>

#ifdef _WIN32

typedef void (*my_gl_desktop_proc_t)(void);

/** @brief Integer address -> proc pointer (C11 union type punning). */
my_gl_desktop_proc_t my_gl_desktop_proc_from_address(uintptr_t address);

/** @brief Proc pointer -> integer address (C11 union type punning). */
uintptr_t my_gl_desktop_proc_to_address(my_gl_desktop_proc_t proc);

/**
 * @brief True when a wglGetProcAddress return value is a callable
 * pointer rather than one of the documented garbage sentinels
 * (0, 1, 2, 3, (uintptr_t)-1).
 */
bool my_gl_desktop_wgl_proc_usable(my_gl_desktop_proc_t proc);

#endif /* _WIN32 */

#endif /* MY_GL_DESKTOP_INTERNAL_H */
