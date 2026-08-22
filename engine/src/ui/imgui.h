#pragma once
#include <core/types.h>
#include <rhi/rhi.h>
#include "myr/my_font.h"
#include "myr/my_vgcanvas.h"

typedef struct FontRenderer {
  my_font_t *font;
  my_vgcanvas_t *vg;
  RHIDevice *device;
  f32 size;
  bool frame_open;
} FontRenderer;

typedef struct {
  FontRenderer *font;
  f32 screen_w, screen_h;
  f32 mouse_x, mouse_y;
  bool mouse_down, mouse_prev_down;
  u32 hot_id, active_id;
  f32 origin_x, origin_y, cursor_y, panel_w, row_h, pad;
  u32 widget_count;
} ImUI;

bool font_renderer_init(FontRenderer *font, RHIDevice *dev, const char *path,
                        f32 size);
void font_renderer_shutdown(FontRenderer *font);

void imui_init(ImUI *ui, FontRenderer *font);
/* Layout and pointer coordinates are logical; the canvas is physical. */
void imui_begin(ImUI *ui, f32 logical_w, f32 logical_h, f32 drawable_w,
                f32 drawable_h, f32 mouse_x, f32 mouse_y, bool mouse_down);
void imui_end(ImUI *ui, RHICmdBuffer *cmd);
void imui_panel(ImUI *ui, f32 x, f32 y, f32 w, f32 h);
void imui_label(ImUI *ui, const char *fmt, ...);
bool imui_button(ImUI *ui, u32 id, const char *label);
bool imui_checkbox(ImUI *ui, u32 id, const char *label, bool *value);
bool imui_slider_float(ImUI *ui, u32 id, const char *label, f32 *value,
                       f32 minv, f32 maxv);
bool imui_collapsing_header(ImUI *ui, u32 id, const char *label, bool *open);
bool imui_radio(ImUI *ui, u32 id, const char *label, i32 *value, i32 option);
bool imui_slider_int(ImUI *ui, u32 id, const char *label, i32 *value,
                     i32 minv, i32 maxv);
void imui_reset_input(ImUI *ui, bool mouse_down);
