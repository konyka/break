#pragma once
#include <core/types.h>
#include <rhi/rhi.h>
#include <ui/font.h>

typedef struct {
    char   lines[32][128];
    u32    line_count;
    bool   visible;
    bool   initialized;
    FontRenderer font;
    RHIDevice   *device;
} DebugUI;

void debug_ui_init(DebugUI *ui);
void debug_ui_init_renderer(DebugUI *ui, RHIDevice *dev);
void debug_ui_begin(DebugUI *ui);
void debug_ui_text(DebugUI *ui, const char *fmt, ...);
void debug_ui_end(DebugUI *ui);
void debug_ui_render(DebugUI *ui, RHICmdBuffer *cmd, u32 screen_w, u32 screen_h);
void debug_ui_toggle(DebugUI *ui);
void debug_ui_shutdown(DebugUI *ui);
