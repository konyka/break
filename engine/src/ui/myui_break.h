/**
 * @file myui_break.h
 * @brief BreakUI bridge: wires myui to Break's Platform and RHI.
 *
 * The bridge owns the PAL wrapper, main loop, window manager, root window,
 * font and RHI vgcanvas. Callers borrow the returned myui objects. The RHI
 * canvas is injected into windows, so the bridge owns its resize lifecycle.
 */
#ifndef MYUI_BREAK_H
#define MYUI_BREAK_H

#include <stddef.h>

#include "platform/platform.h"
#include "rhi/rhi.h"

typedef struct BreakUI BreakUI;

struct my_window_t;
struct my_font_source_t;
struct my_pal_t;
struct my_pal_main_loop_t;
struct my_window_manager_t;

BreakUI *break_ui_create(void);
bool break_ui_init(BreakUI *ui, Platform *platform, RHIDevice *device,
                   const char *font_path, u32 width, u32 height);
bool break_ui_init_with_fonts(BreakUI *ui, Platform *platform,
                              RHIDevice *device,
                              const struct my_font_source_t *font_sources,
                              size_t font_source_count, u32 width,
                              u32 height);
void break_ui_shutdown(BreakUI *ui);
void break_ui_destroy(BreakUI *ui);
void break_ui_pump(BreakUI *ui);
void break_ui_render(BreakUI *ui, RHICmdBuffer *cmd, u32 width, u32 height);

void *break_ui_window(BreakUI *ui);
struct my_window_t *break_ui_get_window(BreakUI *ui);
struct my_window_manager_t *break_ui_get_window_manager(BreakUI *ui);
struct my_pal_t *break_ui_get_pal(BreakUI *ui);
struct my_pal_main_loop_t *break_ui_get_loop(BreakUI *ui);

#endif /* MYUI_BREAK_H */
