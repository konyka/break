/**
 * @file nav_item.c
 * @brief Topbar text item implementation (M14b).
 */
#include "nav_item.h"

#include <string.h>

#include "myc/my_str.h"

#define NAV_PAD_X 8

typedef struct dxx_nav_item_t {
  my_widget_t base;
  char* text;
  uint32_t color;
  uint32_t hover_bg;
  int32_t font_size;
  bool bold;
  bool pressed;
} dxx_nav_item_t;

int32_t dxx_text_estimate(const char* utf8, int32_t font_size) {
  int32_t w = 0;
  const unsigned char* p = (const unsigned char*)utf8;
  if (utf8 == NULL) {
    return 0;
  }
  while (*p != '\0') {
    if (*p >= 0x80) { /* UTF-8 multibyte: count the lead byte only */
      w += font_size;
      p++;                          /* the lead byte */
      while ((*p & 0xC0) == 0x80) { /* then its continuation bytes */
        p++;
      }
      continue;
    }
    w += font_size / 2;
    p++;
  }
  return w;
}

static void nav_item_paint(my_widget_t* widget, my_vgcanvas_t* vg) {
  dxx_nav_item_t* it = (dxx_nav_item_t*)widget;
  int32_t tw = 0, th = 0;
  float x, y;
  if (widget->hovered && (it->hover_bg & 0xFFu) != 0) {
    my_vgcanvas_set_fill_color(vg, my_color_from_rgba32(it->hover_bg));
    my_vgcanvas_fill_rect(vg, &(my_rectf_t){0, 0, (float)widget->rect.w,
                                            (float)widget->rect.h});
  }
  if (it->text == NULL) {
    return;
  }
  my_vgcanvas_set_font(vg, NULL, it->font_size);
  if (my_vgcanvas_measure_text(vg, it->text, &tw, &th) != MY_RET_OK) {
    tw = dxx_text_estimate(it->text, it->font_size);
    th = it->font_size;
  }
  x = ((float)widget->rect.w - (float)tw) / 2.0f;
  y = ((float)widget->rect.h - (float)th) / 2.0f;
  my_vgcanvas_set_fill_color(vg, my_color_from_rgba32(it->color));
  my_vgcanvas_draw_text(vg, it->text, x, y);
  if (it->bold) {
    my_vgcanvas_draw_text(vg, it->text, x + 1.0f, y); /* fake bold */
  }
}

static my_ret_t nav_item_event(my_widget_t* widget, const my_event_t* event) {
  dxx_nav_item_t* it = (dxx_nav_item_t*)widget;
  if (event->type == MY_EVENT_POINTER_DOWN) {
    it->pressed = true;
    return MY_RET_OK;
  }
  if (event->type == MY_EVENT_POINTER_UP) {
    int32_t lx = event->u.pointer.x, ly = event->u.pointer.y;
    bool inside;
    if (!it->pressed) {
      return MY_RET_FAIL;
    }
    it->pressed = false;
    my_widget_global_to_local(widget, &lx, &ly);
    inside = lx >= 0 && ly >= 0 && lx < widget->rect.w && ly < widget->rect.h;
    if (inside) {
      my_emitter_emit(widget->emitter, "click", (void*)event);
    }
    return MY_RET_OK;
  }
  return MY_RET_FAIL;
}

static void nav_item_destroy_chain(my_object_t* obj) {
  dxx_nav_item_t* it = (dxx_nav_item_t*)obj;
  my_mem_free(obj->allocator, it->text);
  my_widget_destroy((my_widget_t*)it);
  my_object_destroy(obj);
}

static const my_widget_vtable_t s_nav_item_vtable = {nav_item_paint,
                                                     nav_item_event, NULL, NULL};

my_widget_t* dxx_nav_item_create(const my_allocator_t* allocator,
                                 const char* text, uint32_t rgba_color,
                                 bool bold, int32_t font_size,
                                 uint32_t hover_bg) {
  dxx_nav_item_t* it =
      (dxx_nav_item_t*)my_mem_calloc(allocator, 1, sizeof(dxx_nav_item_t));
  if (it == NULL) {
    return NULL;
  }
  if (my_widget_init((my_widget_t*)it, allocator, &s_nav_item_vtable,
                     "nav_item") != MY_RET_OK) {
    my_mem_free(allocator, it);
    return NULL;
  }
  ((my_object_t*)it)->destroy = nav_item_destroy_chain;
  it->text = my_strdup(allocator, text);
  it->color = rgba_color;
  it->hover_bg = hover_bg;
  it->font_size = font_size > 0 ? font_size : 14;
  it->bold = bold;
  return (my_widget_t*)it;
}

void dxx_nav_item_set_color(my_widget_t* item, uint32_t rgba_color) {
  if (item != NULL) {
    ((dxx_nav_item_t*)item)->color = rgba_color;
    my_widget_invalidate(item, NULL);
  }
}
