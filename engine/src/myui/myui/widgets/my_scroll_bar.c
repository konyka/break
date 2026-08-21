/**
 * @file my_scroll_bar.c
 * @brief Vertical scroll bar widget.
 */
#include "myui/widgets/my_scroll_bar.h"

static float sb_clamp(float v, float lo, float hi) {
  return v < lo ? lo : v > hi ? hi : v;
}

static float sb_thumb_len(my_scroll_bar_t* b) {
  float track = (float)((my_widget_t*)b)->rect.h;
  float len = track * sb_clamp(b->page_size, 0.0f, 1.0f);
  return len < MY_SCROLL_BAR_MIN_THUMB ? (float)MY_SCROLL_BAR_MIN_THUMB : len;
}

static float sb_thumb_y(my_scroll_bar_t* b) {
  float track = (float)((my_widget_t*)b)->rect.h;
  float len = sb_thumb_len(b);
  float movable = track - len;
  return movable > 0.0f ? sb_clamp(b->value, 0.0f, 1.0f) * movable : 0.0f;
}

static void sb_set_internal(my_scroll_bar_t* b, float v, bool notify) {
  v = sb_clamp(v, 0.0f, 1.0f);
  if (v != b->value) {
    b->value = v;
    my_widget_invalidate((my_widget_t*)b, NULL);
    if (notify) {
      my_emitter_emit(((my_widget_t*)b)->emitter, "changed", NULL);
    }
  }
}

static void sb_from_y(my_scroll_bar_t* b, int32_t local_y, bool is_thumb) {
  float track = (float)((my_widget_t*)b)->rect.h;
  float len = sb_thumb_len(b);
  float movable = track - len;
  float y;
  if (movable <= 0.0f) {
    return;
  }
  y = (float)local_y - (is_thumb ? (float)b->drag_off : len / 2.0f);
  sb_set_internal(b, y / movable, true);
}

static my_ret_t sb_on_event(my_widget_t* widget, const my_event_t* event) {
  my_scroll_bar_t* b = (my_scroll_bar_t*)widget;
  int32_t lx, ly;
  switch (event->type) {
    case MY_EVENT_POINTER_DOWN:
      lx = event->u.pointer.x;
      ly = event->u.pointer.y;
      my_widget_global_to_local(widget, &lx, &ly);
      {
        float ty = sb_thumb_y(b);
        float tl = sb_thumb_len(b);
        if ((float)ly >= ty && (float)ly < ty + tl) {
          b->dragging = true;
          b->drag_off = ly - (int32_t)ty;
        } else {
          /* track click: page up/down */
          float step = sb_clamp(b->page_size, 0.05f, 1.0f);
          sb_set_internal(b, (float)ly < ty ? b->value - step
                                            : b->value + step,
                          true);
        }
      }
      return MY_RET_OK;
    case MY_EVENT_POINTER_MOVE:
      if (b->dragging) {
        lx = event->u.pointer.x;
        ly = event->u.pointer.y;
        my_widget_global_to_local(widget, &lx, &ly);
        sb_from_y(b, ly, true);
        return MY_RET_OK;
      }
      return MY_RET_FAIL;
    case MY_EVENT_POINTER_UP:
      if (b->dragging) {
        b->dragging = false;
        return MY_RET_OK;
      }
      return MY_RET_FAIL;
    case MY_EVENT_KEY_DOWN: {
      float step = sb_clamp(b->page_size, 0.02f, 1.0f);
      switch (event->u.key.key) {
        case MY_KEY_DOWN:
        case MY_KEY_RIGHT:
          sb_set_internal(b, b->value + 0.02f, true);
          return MY_RET_OK;
        case MY_KEY_UP:
        case MY_KEY_LEFT:
          sb_set_internal(b, b->value - 0.02f, true);
          return MY_RET_OK;
        case MY_KEY_PAGE_DOWN:
          sb_set_internal(b, b->value + step, true);
          return MY_RET_OK;
        case MY_KEY_PAGE_UP:
          sb_set_internal(b, b->value - step, true);
          return MY_RET_OK;
        case MY_KEY_HOME:
          sb_set_internal(b, 0.0f, true);
          return MY_RET_OK;
        case MY_KEY_END:
          sb_set_internal(b, 1.0f, true);
          return MY_RET_OK;
        default:
          return MY_RET_FAIL;
      }
    }
    default:
      return MY_RET_FAIL;
  }
}

static void sb_on_paint(my_widget_t* widget, my_vgcanvas_t* vg) {
  my_scroll_bar_t* b = (my_scroll_bar_t*)widget;
  my_widget_state_t state = my_widget_current_state(widget, b->dragging);
  uint32_t track_c = my_widget_style_get_color(widget, MY_STATE_NORMAL,
                                               MY_STYLE_BG_COLOR, 0xE8E8E8FFu);
  uint32_t thumb_c = my_widget_style_get_color(widget, state, MY_STYLE_FG_COLOR,
                                               0x9E9E9EFFu);
  float ty = sb_thumb_y(b);
  float tl = sb_thumb_len(b);

  my_vgcanvas_set_fill_color(vg, my_color_from_rgba32(track_c));
  my_vgcanvas_fill_rounded_rect(vg, &(my_rectf_t){0, 0, (float)widget->rect.w,
                                                 (float)widget->rect.h},
                                (float)widget->rect.w / 2.0f);
  my_vgcanvas_set_fill_color(vg, my_color_from_rgba32(thumb_c));
  my_vgcanvas_fill_rounded_rect(vg, &(my_rectf_t){1, ty + 1,
                                                 (float)widget->rect.w - 2,
                                                 tl - 2},
                                (float)widget->rect.w / 2.0f - 1.0f);
}

static const my_widget_vtable_t s_sb_vtable = {sb_on_paint, sb_on_event, NULL, NULL};

my_widget_t* my_scroll_bar_create(const my_allocator_t* allocator) {
  my_scroll_bar_t* b =
      (my_scroll_bar_t*)my_mem_calloc(allocator, 1, sizeof(my_scroll_bar_t));
  if (b == NULL) {
    return NULL;
  }
  if (my_widget_init((my_widget_t*)b, allocator, &s_sb_vtable, "scroll_bar") !=
      MY_RET_OK) {
    my_mem_free(allocator, b);
    return NULL;
  }
  b->page_size = 0.2f;
  ((my_widget_t*)b)->widget_type = "scroll_bar";
  ((my_widget_t*)b)->focusable = true;
  return (my_widget_t*)b;
}

my_ret_t my_scroll_bar_set_value(my_widget_t* bar, float value) {
  if (bar == NULL) {
    return MY_RET_INVALID_PARAMS;
  }
  sb_set_internal((my_scroll_bar_t*)bar, value, false);
  return MY_RET_OK;
}

float my_scroll_bar_get_value(my_widget_t* bar) {
  return bar != NULL ? ((my_scroll_bar_t*)bar)->value : 0.0f;
}

my_ret_t my_scroll_bar_set_page_size(my_widget_t* bar, float page_size) {
  my_scroll_bar_t* b = (my_scroll_bar_t*)bar;
  if (bar == NULL) {
    return MY_RET_INVALID_PARAMS;
  }
  b->page_size = sb_clamp(page_size, 0.0f, 1.0f);
  my_widget_invalidate(bar, NULL);
  return MY_RET_OK;
}

float my_scroll_bar_get_page_size(my_widget_t* bar) {
  return bar != NULL ? ((my_scroll_bar_t*)bar)->page_size : 0.0f;
}
