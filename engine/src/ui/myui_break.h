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

#include "myc/my_error.h"
#include "platform/platform.h"
#include "rhi/rhi.h"

typedef struct BreakUI BreakUI;

/** @brief Whether a public BreakUI size fits myui's signed rectangle ABI. */
static inline bool break_ui_dimensions_fit_myui(u32 width, u32 height) {
  return width != 0u && height != 0u && width <= (u32)INT32_MAX &&
         height <= (u32)INT32_MAX;
}

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
/* Apply CSS media changes reported by the platform event loop. */
void break_ui_refresh_media(BreakUI *ui);
/* Begin a frame after damage collection. A NULL result with out_skip=true is
 * an intentional no-op; otherwise callers must use the returned command.
 * A successful command also opens the optional MyUI metrics owner frame;
 * break_ui_render() commits it or discards it on any render failure. */
RHICmdBuffer *break_ui_frame_begin(BreakUI *ui, u32 width, u32 height,
                                   bool *out_skip, bool *out_partial);
void break_ui_render(BreakUI *ui, RHICmdBuffer *cmd, u32 width, u32 height);
bool break_ui_get_present_damage(BreakUI *ui, u32 width, u32 height,
                                 RHIPresentRect *rects, u32 capacity,
                                 u32 *out_count);
void break_ui_set_present_partial(BreakUI *ui, bool enabled);
/* Queue a transactional AA target switch; activation occurs before the next
 * render pass. The active target remains usable if creation fails. */
my_ret_t break_ui_set_antialias_level(BreakUI *ui, int level);

void *break_ui_window(BreakUI *ui);
struct my_window_t *break_ui_get_window(BreakUI *ui);
struct my_window_manager_t *break_ui_get_window_manager(BreakUI *ui);
struct my_pal_t *break_ui_get_pal(BreakUI *ui);
struct my_pal_main_loop_t *break_ui_get_loop(BreakUI *ui);

#endif /* MYUI_BREAK_H */
