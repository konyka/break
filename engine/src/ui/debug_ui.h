#pragma once
#include <core/types.h>
#include <rhi/rhi.h>
#include <ui/font.h>

typedef struct {
    char   lines[32][128];
    u32    line_count;
    /* R446: sticky section — see debug_ui_sticky_begin/end. A throttle-gated
     * block of debug_ui_text calls used to vanish on non-throttle frames,
     * shifting every line below it and visibly flickering the whole UI. */
    i32    sticky_start;      /* line index where the open section began, -1 = none */
    bool   sticky_refresh;    /* open section re-emits (true) or replays (false) */
    char   sticky_lines[32][128];
    u32    sticky_count;
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
/* R446: wrap a throttle-gated emission block. On refresh frames the block
 * emits normally and the lines are cached; on stale frames the cached lines
 * are replayed at the same position so the block's footprint never changes. */
void debug_ui_sticky_begin(DebugUI *ui, bool refresh);
void debug_ui_sticky_end(DebugUI *ui);
void debug_ui_render(DebugUI *ui, RHICmdBuffer *cmd, u32 screen_w, u32 screen_h);
void debug_ui_toggle(DebugUI *ui);
void debug_ui_shutdown(DebugUI *ui);
