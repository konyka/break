/**
 * @file explorer_internal.h
 * @brief Shared contract between the explorer core and the per-platform
 *        runners (X11 / Wayland / Win32 / Cocoa). app_t stays opaque to
 *        the platform modules.
 */
#ifndef EXPLORER_INTERNAL_H
#define EXPLORER_INTERNAL_H

#include <stdint.h>
#include "myr/my_vgcanvas.h"

#define EX_W 960
#define EX_H 560

typedef struct app_t app_t;

/* Core lifecycle (font resolution is cross-platform inside the core). */
app_t* ex_app_create(void);
void ex_app_destroy(app_t* app);

/* Software path: render one frame, then blit these BGRA pixels. */
void ex_frame_soft(app_t* app);
const uint8_t* ex_lcd_pixels(app_t* app);
uint32_t ex_lcd_stride(app_t* app);

/* GL path: create a vgcanvas bound to the CURRENT desktop-GL context
 * (WGL / NSOpenGL / EGL-ES2) and render one frame through it. */
void ex_gl_vg_create(app_t* app);
void ex_frame_gl(app_t* app);

/* Input translation shared by every platform runner. */
void ex_pointer(app_t* app, int32_t x, int32_t y, int kind); /* 0=move 1=click */
void ex_wheel(app_t* app, int dir);                          /* +1 zoom in */
void ex_key(app_t* app, int ch);                             /* ascii */

/* Platform runners implemented per OS (see ex_platform_*.c|m). */
int ex_run_win32(app_t* app, int gl);
int ex_run_cocoa(app_t* app, int gl);

#endif
