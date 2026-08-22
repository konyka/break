/**
 * @file my_checkbox.c
 * @brief Checkbox widget.
 */
#include "myui/widgets/my_checkbox.h"

#include "myc/my_str.h"

#define CHECK_BOX_SIZE 16
#define CHECK_TEXT_GAP 6

static void checkbox_on_paint(my_widget_t* widget, my_vgcanvas_t* vg) {
  my_checkbox_t* c = (my_checkbox_t*)widget;
  my_widget_state_t state = my_widget_current_state(widget, c->pressed);
  uint32_t bg = my_widget_style_get_color(widget, state, MY_STYLE_BG_COLOR,
                                          0xFFFFFFFFu);
  uint32_t border = my_widget_style_get_color(widget, state, MY_STYLE_BORDER_COLOR,
                                              0x9E9E9EFFu);
  uint32_t fg = my_widget_style_get_color(widget, state, MY_STYLE_FG_COLOR,
                                          0x212121FFu);
  int32_t by = (widget->rect.h - CHECK_BOX_SIZE) / 2;
  float bx = 0, bw = (float)CHECK_BOX_SIZE;

  my_vgcanvas_set_fill_color(vg, my_color_from_rgba32(bg));
  my_vgcanvas_fill_rounded_rect(vg, &(my_rectf_t){bx, (float)by, bw, bw}, 3);
  my_vgcanvas_set_stroke_color(vg, my_color_from_rgba32(border));
  my_vgcanvas_set_line_width(vg, 1);
  my_vgcanvas_stroke_rect(vg, &(my_rectf_t){bx, (float)by, bw, bw});

  if (c->mixed) {
    my_vgcanvas_set_fill_color(vg, my_color_from_rgba32(fg));
    my_vgcanvas_fill_rect(vg, &(my_rectf_t){bx + 4, (float)by + 4, bw - 8,
                                            bw - 8});
  } else if (c->checked) {
    /* check mark: two stroked segments (crisp with the AA rasterizer) */
    float x0 = bx + 3.5f, y0 = (float)by + bw * 0.55f;
    float x1 = bx + bw * 0.45f, y1 = (float)by + bw - 4.0f;
    float x2 = bx + bw - 3.0f, y2 = (float)by + 3.0f;
    my_vgcanvas_set_stroke_color(vg, my_color_from_rgba32(fg));
    my_vgcanvas_set_line_width(vg, 2);
    my_vgcanvas_begin_path(vg);
    my_vgcanvas_move_to(vg, x0, y0);
    my_vgcanvas_line_to(vg, x1, y1);
    my_vgcanvas_line_to(vg, x2, y2);
    my_vgcanvas_stroke(vg);
  }

  if (c->text != NULL) {
    int32_t tw = 0, th = 0;
    if (my_vgcanvas_measure_text(vg, c->text, &tw, &th) == MY_RET_OK) {
      my_vgcanvas_set_fill_color(vg, my_color_from_rgba32(fg));
      my_vgcanvas_draw_text(vg, c->text, bx + bw + CHECK_TEXT_GAP,
                            ((float)widget->rect.h - (float)th) / 2.0f);
    }
  }
}

static my_ret_t checkbox_on_event(my_widget_t* widget, const my_event_t* event) {
  my_checkbox_t* c = (my_checkbox_t*)widget;
  switch (event->type) {
    case MY_EVENT_POINTER_DOWN:
      c->pressed = true;
      return MY_RET_OK;
    case MY_EVENT_POINTER_UP:
      if (!c->pressed) {
        return MY_RET_FAIL;
      }
      c->pressed = false;
      c->checked = !c->checked;
      c->mixed = false;
      my_widget_invalidate(widget, NULL);
      my_emitter_emit(widget->emitter, "changed", NULL);
      return MY_RET_OK;
    default:
      return MY_RET_FAIL;
  }
}

static const my_widget_vtable_t s_checkbox_vtable = {checkbox_on_paint,
                                                     checkbox_on_event, NULL, NULL};

static void checkbox_destroy_chain(my_object_t* obj) {
  my_checkbox_t* c = (my_checkbox_t*)obj;
  my_mem_free(c->allocator, c->text);
  my_widget_destroy((my_widget_t*)c);
  my_object_destroy(obj);
}

my_widget_t* my_checkbox_create(const my_allocator_t* allocator,
                                const char* text) {
  my_checkbox_t* c =
      (my_checkbox_t*)my_mem_calloc(allocator, 1, sizeof(my_checkbox_t));
  if (c == NULL) {
    return NULL;
  }
  if (my_widget_init((my_widget_t*)c, allocator, &s_checkbox_vtable,
                     "checkbox") != MY_RET_OK) {
    my_mem_free(allocator, c);
    return NULL;
  }
  ((my_object_t*)c)->destroy = checkbox_destroy_chain;
  c->allocator = allocator;
  if (text != NULL) {
    c->text = my_strdup(allocator, text);
    if (c->text == NULL) {
      my_object_unref((my_object_t*)c);
      return NULL;
    }
  }
  ((my_widget_t*)c)->focusable = true;
  ((my_widget_t*)c)->widget_type = "checkbox";
  return (my_widget_t*)c;
}

my_ret_t my_checkbox_set_text(my_widget_t* checkbox, const char* text) {
  my_checkbox_t* c = (my_checkbox_t*)checkbox;
  char* copy;
  if (checkbox == NULL) {
    return MY_RET_INVALID_PARAMS;
  }
  copy = my_strdup(c->allocator, text);
  if (text != NULL && copy == NULL) {
    return MY_RET_OOM;
  }
  my_mem_free(c->allocator, c->text);
  c->text = copy;
  my_widget_invalidate(checkbox, NULL);
  return MY_RET_OK;
}

my_ret_t my_checkbox_set_checked(my_widget_t* checkbox, bool checked) {
  my_checkbox_t* c = (my_checkbox_t*)checkbox;
  if (checkbox == NULL) {
    return MY_RET_INVALID_PARAMS;
  }
  if (c->checked != checked || c->mixed) {
    c->checked = checked;
    c->mixed = false;
    my_widget_invalidate(checkbox, NULL);
  }
  return MY_RET_OK;
}

bool my_checkbox_get_checked(my_widget_t* checkbox) {
  return checkbox != NULL && ((my_checkbox_t*)checkbox)->checked;
}

my_ret_t my_checkbox_set_mixed(my_widget_t* checkbox, bool mixed) {
  my_checkbox_t* c = (my_checkbox_t*)checkbox;
  if (checkbox == NULL) {
    return MY_RET_INVALID_PARAMS;
  }
  c->mixed = mixed;
  my_widget_invalidate(checkbox, NULL);
  return MY_RET_OK;
}
