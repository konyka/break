#pragma once
#include <core/types.h>
#include <ui/font.h>
#include <rhi/rhi.h>

/* ==========================================================================
 *  imgui.h - minimal immediate-mode GUI on top of the font renderer.
 *
 *  Widgets are identified by a caller-supplied stable u32 id. Interaction
 *  state (which item is hovered / being pressed) is tracked across frames in
 *  the ImUI context. The pure hit-testing and state-machine helpers are
 *  inline so they can be unit-tested without a GPU device.
 * ========================================================================== */

typedef struct {
    /* borrowed font renderer (may be NULL for headless logic-only use) */
    FontRenderer *font;
    f32 screen_w, screen_h;

    /* input snapshot for the current frame */
    f32  mouse_x, mouse_y;
    bool mouse_down;
    bool mouse_prev_down;

    /* interaction state (persist across frames) */
    u32 hot_id;     /* hovered this frame                */
    u32 active_id;  /* pressed and not yet released      */

    /* layout cursor */
    f32 origin_x, origin_y;
    f32 cursor_y;
    f32 panel_w;
    f32 row_h;
    f32 pad;
    u32 widget_count;
} ImUI;

/* ---- pure helpers (no rendering, safe to unit test) ------------------- */

static inline bool imui_hit(f32 mx, f32 my, f32 x, f32 y, f32 w, f32 h) {
    return mx >= x && mx < x + w && my >= y && my < y + h;
}

/* Map a mouse x position over a track [x, x+w] to a value in [minv, maxv]. */
static inline f32 imui_slider_map(f32 mx, f32 x, f32 w, f32 minv, f32 maxv) {
    f32 t = w > 0.0f ? (mx - x) / w : 0.0f;
    if (t < 0.0f) t = 0.0f;
    if (t > 1.0f) t = 1.0f;
    return minv + t * (maxv - minv);
}

/* Normalized [0,1] knob position for a value, clamped to the range. */
static inline f32 imui_slider_norm(f32 value, f32 minv, f32 maxv) {
    if (maxv == minv) return 0.0f;
    f32 t = (value - minv) / (maxv - minv);
    if (t < 0.0f) t = 0.0f;
    if (t > 1.0f) t = 1.0f;
    return t;
}

/* Button/checkbox press state machine. Updates *hot_id / *active_id and
 * returns true on a completed click (press + release over the widget). */
static inline bool imui_press_logic(u32 id, bool hovered, bool mouse_down,
                                    bool mouse_prev_down,
                                    u32 *hot_id, u32 *active_id) {
    bool clicked = false;
    if (hovered) *hot_id = id;
    bool pressed_now  = mouse_down && !mouse_prev_down;
    bool released_now = !mouse_down && mouse_prev_down;
    if (*active_id == id) {
        if (released_now) {
            if (hovered) clicked = true;
            *active_id = 0;
        }
    } else if (hovered && pressed_now && *active_id == 0) {
        *active_id = id;
    }
    return clicked;
}

/* Drop any in-progress interaction and re-sync the input edge latch.
 *
 * imui_begin/imui_end only run while the UI is drawn. When a panel is hidden
 * (e.g. toggled off) those calls are skipped, so active_id and mouse_prev_down
 * freeze at their last values. If a press was in progress when the panel closed
 * — or the button is released while it is hidden — the stale mouse_prev_down=1
 * combined with the next visible frame's mouse_up produces a phantom
 * released-edge, firing a spurious click/toggle on reopen (and a stuck active_id
 * blocks other widgets). Call this every frame the UI is NOT drawn, passing the
 * current mouse-button state, to keep the latch fresh and clear the active item. */
static inline void imui_reset_input(ImUI *ui, bool mouse_down) {
    ui->active_id      = 0;
    ui->hot_id         = 0;
    ui->mouse_down     = mouse_down;
    ui->mouse_prev_down = mouse_down;
}

/* ---- context lifecycle ------------------------------------------------ */

void imui_init(ImUI *ui, FontRenderer *font);

/* Begin a frame with the current input snapshot. */
void imui_begin(ImUI *ui, f32 screen_w, f32 screen_h,
                f32 mouse_x, f32 mouse_y, bool mouse_down);

/* Flush queued geometry to the command buffer and latch input edge state. */
void imui_end(ImUI *ui, RHICmdBuffer *cmd);

/* Begin a vertical layout panel at (x,y) with the given width and height.
 * Draws a translucent backdrop; widgets render on top in submission order. */
void imui_panel(ImUI *ui, f32 x, f32 y, f32 w, f32 h);

/* ---- widgets ---------------------------------------------------------- */

void imui_label(ImUI *ui, const char *fmt, ...);
bool imui_button(ImUI *ui, u32 id, const char *label);
bool imui_checkbox(ImUI *ui, u32 id, const char *label, bool *value);
bool imui_slider_float(ImUI *ui, u32 id, const char *label,
                       f32 *value, f32 minv, f32 maxv);
