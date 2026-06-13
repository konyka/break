#include <ui/imgui.h>
#include <string.h>
#include <stdarg.h>
#include <stdio.h>

/* Visual theme (RGBA, 0..1) */
#define IM_COL_PANEL_R 0.08f
#define IM_COL_PANEL_G 0.08f
#define IM_COL_PANEL_B 0.10f
#define IM_COL_PANEL_A 0.82f

static void im_rect(ImUI *ui, f32 x, f32 y, f32 w, f32 h,
                    f32 r, f32 g, f32 b, f32 a) {
    if (!ui->font) return;
    font_renderer_draw_rect(ui->font, x, y, w, h, ui->screen_w, ui->screen_h, r, g, b, a);
}

static void im_text(ImUI *ui, f32 x, f32 y, const char *s,
                    f32 r, f32 g, f32 b, f32 a) {
    if (!ui->font) return;
    font_renderer_draw(ui->font, s, x, y, ui->screen_w, ui->screen_h, r, g, b, a);
}

static f32 im_text_w(ImUI *ui, const char *s) {
    if (!ui->font) return (f32)strlen(s) * 8.0f;
    return font_renderer_text_width(ui->font, s);
}

void imui_init(ImUI *ui, FontRenderer *font) {
    memset(ui, 0, sizeof(*ui));
    ui->font = font;
    ui->pad = 6.0f;
    ui->row_h = font ? font_renderer_line_height(font) + 6.0f : 22.0f;
}

void imui_begin(ImUI *ui, f32 screen_w, f32 screen_h,
                f32 mouse_x, f32 mouse_y, bool mouse_down) {
    ui->screen_w = screen_w;
    ui->screen_h = screen_h;
    ui->mouse_x = mouse_x;
    ui->mouse_y = mouse_y;
    ui->mouse_down = mouse_down;
    ui->hot_id = 0;
    ui->widget_count = 0;
    if (ui->font) {
        ui->row_h = font_renderer_line_height(ui->font) + 6.0f;
        font_renderer_begin(ui->font);
    }
}

void imui_end(ImUI *ui, RHICmdBuffer *cmd) {
    if (ui->font && cmd)
        font_renderer_end(ui->font, cmd, ui->screen_w, ui->screen_h);
    /* latch edge state for next frame's pressed/released detection */
    ui->mouse_prev_down = ui->mouse_down;
}

void imui_panel(ImUI *ui, f32 x, f32 y, f32 w, f32 h) {
    ui->origin_x = x;
    ui->origin_y = y;
    ui->cursor_y = y + ui->pad;
    ui->panel_w = w;
    im_rect(ui, x, y, w, h,
            IM_COL_PANEL_R, IM_COL_PANEL_G, IM_COL_PANEL_B, IM_COL_PANEL_A);
}

void imui_label(ImUI *ui, const char *fmt, ...) {
    char buf[256];
    va_list args;
    va_start(args, fmt);
    vsnprintf(buf, sizeof(buf), fmt, args);
    va_end(args);

    im_text(ui, ui->origin_x + ui->pad, ui->cursor_y, buf, 0.9f, 0.9f, 0.9f, 1.0f);
    ui->cursor_y += ui->row_h;
    ui->widget_count++;
}

bool imui_button(ImUI *ui, u32 id, const char *label) {
    f32 x = ui->origin_x + ui->pad;
    f32 y = ui->cursor_y;
    f32 w = ui->panel_w - ui->pad * 2.0f;
    f32 h = ui->row_h - 4.0f;

    bool hovered = imui_hit(ui->mouse_x, ui->mouse_y, x, y, w, h);
    bool clicked = imui_press_logic(id, hovered, ui->mouse_down, ui->mouse_prev_down,
                                    &ui->hot_id, &ui->active_id);

    f32 r = 0.22f, g = 0.24f, b = 0.30f;
    if (ui->active_id == id)      { r = 0.16f; g = 0.40f; b = 0.62f; }
    else if (ui->hot_id == id)    { r = 0.30f; g = 0.34f; b = 0.42f; }

    im_rect(ui, x, y, w, h, r, g, b, 1.0f);
    f32 tw = im_text_w(ui, label);
    im_text(ui, x + (w - tw) * 0.5f, y + 2.0f, label, 1.0f, 1.0f, 1.0f, 1.0f);

    ui->cursor_y += ui->row_h;
    ui->widget_count++;
    return clicked;
}

bool imui_checkbox(ImUI *ui, u32 id, const char *label, bool *value) {
    f32 x = ui->origin_x + ui->pad;
    f32 y = ui->cursor_y;
    f32 box = ui->row_h - 8.0f;

    bool hovered = imui_hit(ui->mouse_x, ui->mouse_y, x, y, ui->panel_w - ui->pad * 2.0f, box);
    bool clicked = imui_press_logic(id, hovered, ui->mouse_down, ui->mouse_prev_down,
                                    &ui->hot_id, &ui->active_id);
    if (clicked && value) *value = !*value;

    f32 r = 0.20f, g = 0.22f, b = 0.26f;
    if (ui->hot_id == id) { r = 0.28f; g = 0.30f; b = 0.36f; }
    im_rect(ui, x, y, box, box, r, g, b, 1.0f);
    if (value && *value)
        im_rect(ui, x + 3.0f, y + 3.0f, box - 6.0f, box - 6.0f, 0.30f, 0.72f, 0.95f, 1.0f);

    im_text(ui, x + box + 6.0f, y + 1.0f, label, 0.9f, 0.9f, 0.9f, 1.0f);

    ui->cursor_y += ui->row_h;
    ui->widget_count++;
    return clicked;
}

bool imui_slider_float(ImUI *ui, u32 id, const char *label,
                       f32 *value, f32 minv, f32 maxv) {
    f32 x = ui->origin_x + ui->pad;
    f32 y = ui->cursor_y;
    f32 w = ui->panel_w - ui->pad * 2.0f;
    f32 h = ui->row_h - 6.0f;

    bool hovered = imui_hit(ui->mouse_x, ui->mouse_y, x, y, w, h);
    bool changed = false;

    bool pressed_now = ui->mouse_down && !ui->mouse_prev_down;
    if (hovered) ui->hot_id = id;
    if (ui->active_id == id) {
        if (ui->mouse_down) {
            if (value) {
                f32 nv = imui_slider_map(ui->mouse_x, x, w, minv, maxv);
                if (nv != *value) { *value = nv; changed = true; }
            }
        } else {
            ui->active_id = 0;
        }
    } else if (hovered && pressed_now && ui->active_id == 0) {
        ui->active_id = id;
        if (value) {
            f32 nv = imui_slider_map(ui->mouse_x, x, w, minv, maxv);
            if (nv != *value) { *value = nv; changed = true; }
        }
    }

    /* track */
    im_rect(ui, x, y, w, h, 0.16f, 0.17f, 0.20f, 1.0f);
    /* fill + knob */
    f32 t = imui_slider_norm(value ? *value : minv, minv, maxv);
    im_rect(ui, x, y, w * t, h, 0.18f, 0.46f, 0.66f, 1.0f);
    f32 knob_w = 6.0f;
    f32 kx = x + (w - knob_w) * t;
    im_rect(ui, kx, y - 1.0f, knob_w, h + 2.0f, 0.85f, 0.88f, 0.95f, 1.0f);

    char buf[128];
    snprintf(buf, sizeof(buf), "%s: %.2f", label, (f64)(value ? *value : 0.0f));
    im_text(ui, x + 4.0f, y - 1.0f, buf, 1.0f, 1.0f, 1.0f, 1.0f);

    ui->cursor_y += ui->row_h;
    ui->widget_count++;
    return changed;
}
