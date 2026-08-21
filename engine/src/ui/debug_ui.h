#pragma once
#include <core/types.h>
#include <rhi/rhi.h>

typedef struct DebugUI {
    char lines[32][128];
    u32 line_count;
    i32 sticky_start;
    bool sticky_refresh;
    char sticky_lines[32][128];
    u32 sticky_count;
    bool visible;
    bool initialized;
    RHIDevice *device;
    void *font;
    void *vg;
    u32 vg_width;
    u32 vg_height;
} DebugUI;

void debug_ui_init(DebugUI *ui);
void debug_ui_init_renderer(DebugUI *ui, RHIDevice *dev);
void debug_ui_begin(DebugUI *ui);
void debug_ui_text(DebugUI *ui, const char *fmt, ...);
void debug_ui_end(DebugUI *ui);
void debug_ui_sticky_begin(DebugUI *ui, bool refresh);
void debug_ui_sticky_end(DebugUI *ui);
/* Draw in logical layout units into a physical RHI drawable. */
void debug_ui_render(DebugUI *ui, RHICmdBuffer *cmd, u32 logical_w,
                     u32 logical_h, u32 drawable_w, u32 drawable_h);
void debug_ui_toggle(DebugUI *ui);
void debug_ui_shutdown(DebugUI *ui);
