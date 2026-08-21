/**
 * @file placeholder.c
 * @brief Placeholder page implementation (M14d).
 */
#include "placeholder.h"

#include <stdio.h>

#include "../dxx_theme.h"
#include "myui/widgets/my_button.h"
#include "myui/widgets/my_label.h"

typedef struct dxx_placeholder_t {
  my_widget_t base;
  my_widget_t* title; /* weak (child) */
  void (*on_back)(void* ctx);
  void* ctx;
} dxx_placeholder_t;

static void ph_on_paint(my_widget_t* widget, my_vgcanvas_t* vg) {
  my_vgcanvas_set_fill_color(vg, my_color_from_rgba32(DXX_COLOR_WHITE));
  my_vgcanvas_fill_rect(vg, &(my_rectf_t){0, 0, (float)widget->rect.w,
                                          (float)widget->rect.h});
}

static void ph_on_back_click(void* ctx, const char* event, void* data) {
  dxx_placeholder_t* ph = (dxx_placeholder_t*)ctx;
  (void)event;
  (void)data;
  if (ph->on_back != NULL) {
    ph->on_back(ph->ctx);
  }
}

static const my_widget_vtable_t s_ph_vtable = {ph_on_paint, NULL, NULL, NULL};

my_widget_t* dxx_placeholder_create(const my_allocator_t* allocator,
                                    void (*on_back)(void* ctx), void* ctx) {
  dxx_placeholder_t* ph = (dxx_placeholder_t*)my_mem_calloc(
      allocator, 1, sizeof(dxx_placeholder_t));
  my_widget_t* sub;
  my_widget_t* back;
  if (ph == NULL) {
    return NULL;
  }
  if (my_widget_init((my_widget_t*)ph, allocator, &s_ph_vtable,
                     "dxx_placeholder") != MY_RET_OK) {
    my_mem_free(allocator, ph);
    return NULL;
  }
  ph->on_back = on_back;
  ph->ctx = ctx;
  ph->title = my_label_create(allocator, "");
  my_label_set_align(ph->title, MY_TEXT_ALIGN_CENTER);
  my_widget_set_rect(ph->title, &(my_rect_t){0, 120, 1300, 30});
  my_widget_add_child((my_widget_t*)ph, ph->title);
  my_widget_unref(ph->title);
  sub = my_label_create(
      allocator, "该页面为复刻演示占位，原站此页为独立数据页面");
  my_label_set_align(sub, MY_TEXT_ALIGN_CENTER);
  my_widget_set_rect(sub, &(my_rect_t){0, 160, 1300, 24});
  my_widget_add_child((my_widget_t*)ph, sub);
  my_widget_unref(sub);
  back = my_button_create(allocator, "返回首页");
  my_widget_set_rect(back, &(my_rect_t){600, 220, 100, 36});
  my_widget_on(back, "click", ph_on_back_click, ph);
  my_widget_add_child((my_widget_t*)ph, back);
  my_widget_unref(back);
  return (my_widget_t*)ph;
}

void dxx_placeholder_set_title(my_widget_t* panel, const char* name) {
  dxx_placeholder_t* ph = (dxx_placeholder_t*)panel;
  if (panel == NULL || name == NULL) {
    return;
  }
  my_label_set_text(ph->title, name);
}
