#include "ui/imgui.h"

#include <stdarg.h>
#include <stdio.h>
#include <string.h>

#include "myr/my_vgcanvas_break_rhi.h"

#define IM_COL_PANEL_R 0.08f
#define IM_COL_PANEL_G 0.08f
#define IM_COL_PANEL_B 0.10f
#define IM_COL_PANEL_A 0.82f

static my_color_t im_color(f32 r, f32 g, f32 b, f32 a) {
  return my_color_rgba((u8)(r * 255.0f + 0.5f), (u8)(g * 255.0f + 0.5f),
                       (u8)(b * 255.0f + 0.5f), (u8)(a * 255.0f + 0.5f));
}

static bool im_hit(const ImUI *ui, f32 x, f32 y, f32 w, f32 h) {
  return ui->mouse_x >= x && ui->mouse_x < x + w && ui->mouse_y >= y &&
         ui->mouse_y < y + h;
}

static bool im_press(ImUI *ui, u32 id, bool hovered) {
  bool pressed = ui->mouse_down && !ui->mouse_prev_down;
  bool released = !ui->mouse_down && ui->mouse_prev_down;
  if (hovered) ui->hot_id = id;
  if (ui->active_id == id) {
    if (released) {
      ui->active_id = 0;
      return hovered;
    }
    return false;
  }
  if (hovered && pressed && ui->active_id == 0) ui->active_id = id;
  return false;
}

static f32 im_clamp(f32 value, f32 minv, f32 maxv) {
  if (value < minv) return minv;
  if (value > maxv) return maxv;
  return value;
}

static f32 im_norm(f32 value, f32 minv, f32 maxv) {
  if (maxv <= minv) return 0.0f;
  return im_clamp((value - minv) / (maxv - minv), 0.0f, 1.0f);
}

static f32 im_map(f32 mouse_x, f32 x, f32 w, f32 minv, f32 maxv) {
  if (w <= 0.0f) return minv;
  return im_clamp(minv + (mouse_x - x) / w * (maxv - minv), minv, maxv);
}

static void im_rect(ImUI *ui, f32 x, f32 y, f32 w, f32 h, my_color_t color) {
  if (ui->font == NULL || ui->font->vg == NULL || w <= 0.0f || h <= 0.0f) return;
  my_vgcanvas_set_fill_color(ui->font->vg, color);
  my_vgcanvas_fill_rect(ui->font->vg, &(my_rectf_t){x, y, w, h});
}

static void im_text(ImUI *ui, f32 x, f32 y, const char *text, my_color_t color) {
  if (ui->font == NULL || ui->font->vg == NULL || text == NULL) return;
  my_vgcanvas_set_fill_color(ui->font->vg, color);
  my_vgcanvas_draw_text(ui->font->vg, text, x, y);
}

static f32 im_text_width(ImUI *ui, const char *text) {
  int32_t width = 0;
  if (ui->font == NULL || ui->font->vg == NULL || text == NULL ||
      my_vgcanvas_measure_text(ui->font->vg, text, &width, NULL) != MY_RET_OK) {
    return text != NULL ? (f32)strlen(text) * 8.0f : 0.0f;
  }
  return (f32)width;
}

bool font_renderer_init(FontRenderer *font, RHIDevice *dev, const char *path,
                        f32 size) {
  if (font == NULL || dev == NULL || size <= 0.0f) return false;
  memset(font, 0, sizeof(*font));
  font->device = dev;
  font->size = size;
  font->font = my_font_stb_create(NULL, path, 256);
  if (font->font == NULL) font->font = my_font_bitmap_create(NULL);
  font->vg = my_vgcanvas_break_rhi_create(NULL, dev, 1, 1);
  if (font->font == NULL || font->vg == NULL) {
    if (font->vg != NULL) my_vgcanvas_destroy(font->vg);
    if (font->font != NULL) my_font_destroy(font->font);
    memset(font, 0, sizeof(*font));
    return false;
  }
  my_vgcanvas_set_font(font->vg, font->font, (int32_t)size);
  return true;
}

void font_renderer_shutdown(FontRenderer *font) {
  if (font == NULL) return;
  if (font->vg != NULL) my_vgcanvas_destroy(font->vg);
  if (font->font != NULL) my_font_destroy(font->font);
  memset(font, 0, sizeof(*font));
}

void imui_init(ImUI *ui, FontRenderer *font) {
  if (ui == NULL) return;
  memset(ui, 0, sizeof(*ui));
  ui->font = font;
  ui->pad = 6.0f;
  ui->row_h = font != NULL ? (f32)my_font_line_height(font->font, (int32_t)font->size) + 6.0f
                           : 22.0f;
}

void imui_begin(ImUI *ui, f32 logical_w, f32 logical_h, f32 drawable_w,
                f32 drawable_h, f32 mouse_x, f32 mouse_y, bool mouse_down) {
  if (ui == NULL) return;
  ui->screen_w = logical_w;
  ui->screen_h = logical_h;
  ui->mouse_x = mouse_x;
  ui->mouse_y = mouse_y;
  ui->mouse_down = mouse_down;
  ui->hot_id = 0;
  ui->widget_count = 0;
  if (ui->font != NULL && ui->font->font != NULL) {
    ui->row_h = (f32)my_font_line_height(ui->font->font,
                                          (int32_t)ui->font->size) + 6.0f;
    if (ui->font->vg != NULL) {
      my_vgcanvas_break_rhi_resize(ui->font->vg, (u32)drawable_w,
                                    (u32)drawable_h);
      (void)my_vgcanvas_set_scale(
          ui->font->vg, logical_w > 0.0f ? drawable_w / logical_w : 1.0f);
      ui->font->frame_open = my_vgcanvas_begin_frame(ui->font->vg, NULL) == MY_RET_OK;
    }
  }
}

void imui_end(ImUI *ui, RHICmdBuffer *cmd) {
  if (ui == NULL) return;
  if (ui->font != NULL && ui->font->vg != NULL && ui->font->frame_open) {
    my_vgcanvas_break_rhi_set_cmd(ui->font->vg, cmd);
    (void)my_vgcanvas_end_frame(ui->font->vg);
    ui->font->frame_open = false;
  }
  ui->mouse_prev_down = ui->mouse_down;
}

void imui_panel(ImUI *ui, f32 x, f32 y, f32 w, f32 h) {
  if (ui == NULL) return;
  ui->origin_x = x;
  ui->origin_y = y;
  ui->cursor_y = y + ui->pad;
  ui->panel_w = w;
  im_rect(ui, x, y, w, h, im_color(IM_COL_PANEL_R, IM_COL_PANEL_G,
                                   IM_COL_PANEL_B, IM_COL_PANEL_A));
}

void imui_label(ImUI *ui, const char *fmt, ...) {
  char text[256];
  va_list args;
  if (ui == NULL || fmt == NULL) return;
  va_start(args, fmt);
  vsnprintf(text, sizeof(text), fmt, args);
  va_end(args);
  im_text(ui, ui->origin_x + ui->pad, ui->cursor_y, text,
          im_color(0.9f, 0.9f, 0.9f, 1.0f));
  ui->cursor_y += ui->row_h;
  ui->widget_count++;
}

bool imui_button(ImUI *ui, u32 id, const char *label) {
  if (ui == NULL) return false;
  f32 x = ui->origin_x + ui->pad;
  f32 y = ui->cursor_y;
  f32 w = ui->panel_w - ui->pad * 2.0f;
  f32 h = ui->row_h - 4.0f;
  bool clicked = im_press(ui, id, im_hit(ui, x, y, w, h));
  f32 r = ui->active_id == id ? 0.16f : ui->hot_id == id ? 0.30f : 0.22f;
  f32 g = ui->active_id == id ? 0.40f : ui->hot_id == id ? 0.34f : 0.24f;
  f32 b = ui->active_id == id ? 0.62f : ui->hot_id == id ? 0.42f : 0.30f;
  im_rect(ui, x, y, w, h, im_color(r, g, b, 1.0f));
  im_text(ui, x + (w - im_text_width(ui, label)) * 0.5f, y + 2.0f, label,
          im_color(1.0f, 1.0f, 1.0f, 1.0f));
  ui->cursor_y += ui->row_h;
  ui->widget_count++;
  return clicked;
}

bool imui_checkbox(ImUI *ui, u32 id, const char *label, bool *value) {
  if (ui == NULL) return false;
  f32 x = ui->origin_x + ui->pad;
  f32 y = ui->cursor_y;
  f32 box = ui->row_h - 8.0f;
  bool clicked = im_press(ui, id, im_hit(ui, x, y, ui->panel_w - ui->pad * 2.0f, box));
  if (clicked && value != NULL) *value = !*value;
  im_rect(ui, x, y, box, box, im_color(0.20f, 0.22f, 0.26f, 1.0f));
  if (value != NULL && *value)
    im_rect(ui, x + 3.0f, y + 3.0f, box - 6.0f, box - 6.0f,
            im_color(0.30f, 0.72f, 0.95f, 1.0f));
  im_text(ui, x + box + 6.0f, y + 1.0f, label, im_color(0.9f, 0.9f, 0.9f, 1.0f));
  ui->cursor_y += ui->row_h;
  ui->widget_count++;
  return clicked;
}

bool imui_slider_float(ImUI *ui, u32 id, const char *label, f32 *value,
                       f32 minv, f32 maxv) {
  if (ui == NULL) return false;
  f32 x = ui->origin_x + ui->pad;
  f32 y = ui->cursor_y;
  f32 w = ui->panel_w - ui->pad * 2.0f;
  f32 h = ui->row_h - 6.0f;
  bool hovered = im_hit(ui, x, y, w, h);
  bool changed = false;
  bool pressed = ui->mouse_down && !ui->mouse_prev_down;
  if (hovered) ui->hot_id = id;
  if (ui->active_id == id) {
    if (ui->mouse_down && value != NULL) {
      f32 next = im_map(ui->mouse_x, x, w, minv, maxv);
      if (next != *value) { *value = next; changed = true; }
    } else if (!ui->mouse_down) {
      ui->active_id = 0;
    }
  } else if (hovered && pressed && ui->active_id == 0) {
    ui->active_id = id;
    if (value != NULL) {
      f32 next = im_map(ui->mouse_x, x, w, minv, maxv);
      if (next != *value) { *value = next; changed = true; }
    }
  }
  im_rect(ui, x, y, w, h, im_color(0.16f, 0.17f, 0.20f, 1.0f));
  f32 t = im_norm(value != NULL ? *value : minv, minv, maxv);
  im_rect(ui, x, y, w * t, h, im_color(0.18f, 0.46f, 0.66f, 1.0f));
  im_rect(ui, x + (w - 6.0f) * t, y - 1.0f, 6.0f, h + 2.0f,
          im_color(0.85f, 0.88f, 0.95f, 1.0f));
  char text[128];
  snprintf(text, sizeof(text), "%s: %.2f", label != NULL ? label : "",
           value != NULL ? (double)*value : 0.0);
  im_text(ui, x + 4.0f, y - 1.0f, text, im_color(1.0f, 1.0f, 1.0f, 1.0f));
  ui->cursor_y += ui->row_h;
  ui->widget_count++;
  return changed;
}

static void im_fold_marker(ImUI *ui, f32 x, f32 y, bool open) {
  my_color_t color = im_color(0.85f, 0.88f, 0.95f, 1.0f);
  if (open) {
    im_rect(ui, x, y, 8.0f, 2.0f, color);
    im_rect(ui, x + 2.0f, y + 2.0f, 4.0f, 2.0f, color);
    im_rect(ui, x + 3.0f, y + 4.0f, 2.0f, 2.0f, color);
  } else {
    im_rect(ui, x, y, 2.0f, 8.0f, color);
    im_rect(ui, x + 2.0f, y + 2.0f, 2.0f, 4.0f, color);
    im_rect(ui, x + 4.0f, y + 3.0f, 2.0f, 2.0f, color);
  }
}

bool imui_collapsing_header(ImUI *ui, u32 id, const char *label, bool *open) {
  if (ui == NULL) return false;
  f32 x = ui->origin_x + ui->pad;
  f32 y = ui->cursor_y;
  f32 w = ui->panel_w - ui->pad * 2.0f;
  f32 h = ui->row_h - 4.0f;
  bool clicked = im_press(ui, id, im_hit(ui, x, y, w, h));
  bool is_open = open != NULL && *open;
  if (clicked && open != NULL) {
    *open = !*open;
    is_open = *open;
  }
  f32 r = ui->active_id == id ? 0.14f : ui->hot_id == id ? 0.24f : 0.16f;
  f32 g = ui->active_id == id ? 0.30f : ui->hot_id == id ? 0.26f : 0.17f;
  f32 b = ui->active_id == id ? 0.48f : ui->hot_id == id ? 0.32f : 0.20f;
  im_rect(ui, x, y, w, h, im_color(r, g, b, 1.0f));
  im_fold_marker(ui, x + 5.0f, y + (h - 8.0f) * 0.5f, is_open);
  im_text(ui, x + 20.0f, y + 2.0f, label,
          im_color(0.95f, 0.95f, 0.95f, 1.0f));
  ui->cursor_y += ui->row_h;
  ui->widget_count++;
  return is_open;
}

bool imui_radio(ImUI *ui, u32 id, const char *label, i32 *value, i32 option) {
  if (ui == NULL) return false;
  f32 x = ui->origin_x + ui->pad;
  f32 y = ui->cursor_y;
  f32 box = ui->row_h - 8.0f;
  bool clicked = im_press(ui, id,
                          im_hit(ui, x, y, ui->panel_w - ui->pad * 2.0f, box));
  if (clicked && value != NULL) *value = option;
  im_rect(ui, x, y, box, box, im_color(0.20f, 0.22f, 0.26f, 1.0f));
  if (value != NULL && *value == option) {
    im_rect(ui, x + 3.0f, y + 3.0f, box - 6.0f, box - 6.0f,
            im_color(0.30f, 0.72f, 0.95f, 1.0f));
  }
  im_text(ui, x + box + 6.0f, y + 1.0f, label,
          im_color(0.90f, 0.90f, 0.90f, 1.0f));
  ui->cursor_y += ui->row_h;
  ui->widget_count++;
  return clicked;
}

bool imui_slider_int(ImUI *ui, u32 id, const char *label, i32 *value,
                     i32 minv, i32 maxv) {
  f32 x;
  f32 y;
  f32 w;
  f32 h;
  bool hovered;
  bool changed = false;
  bool pressed;
  i32 next;
  char text[128];
  if (ui == NULL || value == NULL || minv > maxv) return false;
  x = ui->origin_x + ui->pad;
  y = ui->cursor_y;
  w = ui->panel_w - ui->pad * 2.0f;
  h = ui->row_h - 6.0f;
  hovered = im_hit(ui, x, y, w, h);
  pressed = ui->mouse_down && !ui->mouse_prev_down;
  if (hovered) ui->hot_id = id;
  if (ui->active_id == id) {
    if (ui->mouse_down) {
      next = (i32)(im_map(ui->mouse_x, x, w, (f32)minv, (f32)maxv) + 0.5f);
      if (next < minv) next = minv;
      if (next > maxv) next = maxv;
      if (next != *value) {
        *value = next;
        changed = true;
      }
    } else {
      ui->active_id = 0;
    }
  } else if (hovered && pressed && ui->active_id == 0) {
    ui->active_id = id;
    next = (i32)(im_map(ui->mouse_x, x, w, (f32)minv, (f32)maxv) + 0.5f);
    if (next < minv) next = minv;
    if (next > maxv) next = maxv;
    if (next != *value) {
      *value = next;
      changed = true;
    }
  }
  im_rect(ui, x, y, w, h, im_color(0.16f, 0.17f, 0.20f, 1.0f));
  im_rect(ui, x, y, w * im_norm((f32)*value, (f32)minv, (f32)maxv), h,
          im_color(0.18f, 0.46f, 0.66f, 1.0f));
  im_rect(ui, x + (w - 6.0f) * im_norm((f32)*value, (f32)minv, (f32)maxv),
          y - 1.0f, 6.0f, h + 2.0f, im_color(0.85f, 0.88f, 0.95f, 1.0f));
  snprintf(text, sizeof(text), "%s: %d", label != NULL ? label : "", *value);
  im_text(ui, x + 4.0f, y - 1.0f, text,
          im_color(1.0f, 1.0f, 1.0f, 1.0f));
  ui->cursor_y += ui->row_h;
  ui->widget_count++;
  return changed;
}

void imui_reset_input(ImUI *ui, bool mouse_down) {
  if (ui == NULL) return;
  ui->active_id = 0;
  ui->hot_id = 0;
  ui->mouse_prev_down = mouse_down;
}
