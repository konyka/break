#include "ui/debug_ui.h"

#include <stdarg.h>
#include <stdio.h>
#include <string.h>

#include "core/log.h"
#include "myr/my_font.h"
#include "myr/my_vgcanvas.h"
#include "myr/my_vgcanvas_break_rhi.h"

#define DEBUG_UI_MAX_LINES 32

void debug_ui_init(DebugUI *ui) {
  if (ui == NULL) return;
  memset(ui, 0, sizeof(*ui));
  ui->visible = true;
  ui->sticky_start = -1;
}

void debug_ui_init_renderer(DebugUI *ui, RHIDevice *dev) {
  if (ui == NULL) return;
  ui->device = dev;
}

void debug_ui_begin(DebugUI *ui) {
  if (ui == NULL) return;
  ui->line_count = 0;
}

void debug_ui_text(DebugUI *ui, const char *fmt, ...) {
  va_list args;
  if (ui == NULL || !ui->visible || ui->line_count >= DEBUG_UI_MAX_LINES) return;
  va_start(args, fmt);
  vsnprintf(ui->lines[ui->line_count], sizeof(ui->lines[0]), fmt, args);
  va_end(args);
  ui->line_count++;
}

void debug_ui_end(DebugUI *ui) {
  (void)ui;
}

void debug_ui_sticky_begin(DebugUI *ui, bool refresh) {
  u32 i;
  if (ui == NULL) return;
  ui->sticky_start = (i32)ui->line_count;
  ui->sticky_refresh = refresh;
  if (!refresh) {
    for (i = 0; i < ui->sticky_count && ui->line_count < DEBUG_UI_MAX_LINES;
         i++) {
      memcpy(ui->lines[ui->line_count], ui->sticky_lines[i],
             sizeof(ui->lines[0]));
      ui->line_count++;
    }
  }
}

void debug_ui_sticky_end(DebugUI *ui) {
  u32 i;
  if (ui == NULL || ui->sticky_start < 0) return;
  if (ui->sticky_refresh) {
    ui->sticky_count = ui->line_count - (u32)ui->sticky_start;
    for (i = 0; i < ui->sticky_count; i++) {
      memcpy(ui->sticky_lines[i], ui->lines[(u32)ui->sticky_start + i],
             sizeof(ui->lines[0]));
    }
  }
  ui->sticky_start = -1;
}

static void ensure_renderer(DebugUI *ui, u32 width, u32 height) {
  if (ui->vg != NULL) {
    if (width != ui->vg_width || height != ui->vg_height) {
      my_vgcanvas_break_rhi_resize(ui->vg, width, height);
      ui->vg_width = width;
      ui->vg_height = height;
    }
    return;
  }
  if (ui->font == NULL) {
    my_font_t *font =
        my_font_stb_create(NULL, "assets/LiberationSans-Regular.ttf", 256);
    if (font == NULL) {
      font = my_font_bitmap_create(NULL);
    }
    ui->font = font;
  }
  ui->vg = my_vgcanvas_break_rhi_create(NULL, ui->device, width, height);
  if (ui->vg == NULL) return;
  ui->vg_width = width;
  ui->vg_height = height;
  if (ui->font != NULL) {
    my_vgcanvas_set_font((my_vgcanvas_t *)ui->vg, (my_font_t *)ui->font, 18);
  }
  ui->initialized = true;
}

void debug_ui_render(DebugUI *ui, RHICmdBuffer *cmd, u32 logical_w,
                     u32 logical_h, u32 drawable_w, u32 drawable_h) {
  u32 i;
  f32 y;
  if (ui == NULL || !ui->visible || ui->line_count == 0 || cmd == NULL) return;
  if (logical_w == 0 || logical_h == 0 || drawable_w == 0 || drawable_h == 0)
    return;
  ensure_renderer(ui, drawable_w, drawable_h);
  if (ui->vg == NULL) {
    for (i = 0; i < ui->line_count; i++) {
      LOG_INFO("[UI] %s", ui->lines[i]);
    }
    return;
  }
  my_vgcanvas_t *vg = (my_vgcanvas_t *)ui->vg;
  my_vgcanvas_break_rhi_set_cmd(vg, cmd);
  (void)my_vgcanvas_set_scale(vg, (f32)drawable_w / (f32)logical_w);
  if (my_vgcanvas_begin_frame(vg, NULL) != MY_RET_OK) return;
  my_vgcanvas_set_fill_color(vg, my_color_rgba(255, 255, 255, 255));
  y = 4.0f;
  for (i = 0; i < ui->line_count; i++) {
    (void)my_vgcanvas_draw_text(vg, ui->lines[i], 4.0f, y);
    y += 20.0f;
  }
  (void)my_vgcanvas_end_frame(vg);
}

void debug_ui_toggle(DebugUI *ui) {
  if (ui != NULL) ui->visible = !ui->visible;
}

void debug_ui_shutdown(DebugUI *ui) {
  if (ui == NULL) return;
  if (ui->vg != NULL) my_vgcanvas_destroy((my_vgcanvas_t *)ui->vg);
  if (ui->font != NULL) my_font_destroy((my_font_t *)ui->font);
  memset(ui, 0, sizeof(*ui));
  ui->sticky_start = -1;
}
