/**
 * @file my_slider.c
 * @brief Horizontal slider widget.
 */
#include "myui/widgets/my_slider.h"

#define SLIDER_TRACK_H 6
#define SLIDER_KNOB 16

static float slider_clamp(my_slider_t* s, float v) {
  if (v < s->min) {
    v = s->min;
  }
  if (v > s->max) {
    v = s->max;
  }
  if (s->step > 0.0f) {
    int n = (int)((v - s->min) / s->step + 0.5f);
    v = s->min + (float)n * s->step;
    if (v < s->min) {
      v = s->min;
    }
    if (v > s->max) {
      v = s->max;
    }
  }
  return v;
}

static void slider_set_internal(my_widget_t* widget, float v, bool notify) {
  my_slider_t* s = (my_slider_t*)widget;
  v = slider_clamp(s, v);
  if (v != s->value) {
    s->value = v;
    my_widget_invalidate(widget, NULL);
    if (notify) {
      my_emitter_emit(widget->emitter, "changed", NULL);
    }
  }
}

static void slider_set_from_x(my_widget_t* widget, int32_t global_x) {
  my_slider_t* s = (my_slider_t*)widget;
  int32_t lx = global_x;
  int32_t ly = 0;
  float frac;
  my_widget_global_to_local(widget, &lx, &ly);
  if (widget->rect.w <= SLIDER_KNOB) {
    return;
  }
  frac = (float)(lx - SLIDER_KNOB / 2) / (float)(widget->rect.w - SLIDER_KNOB);
  if (frac < 0.0f) {
    frac = 0.0f;
  }
  if (frac > 1.0f) {
    frac = 1.0f;
  }
  slider_set_internal(widget, s->min + frac * (s->max - s->min), true);
}

static void slider_on_paint(my_widget_t* widget, my_vgcanvas_t* vg) {
  my_slider_t* s = (my_slider_t*)widget;
  my_widget_state_t state = my_widget_current_state(widget, s->dragging);
  const my_value_t* knob_v = my_widget_style_get(widget, state,
                                                 MY_STYLE_BORDER_COLOR);
  uint32_t track_c = my_widget_style_get_color(widget, state,
                                               MY_STYLE_BG_COLOR, 0xD0D0D0FFu);
  uint32_t fill_c = my_widget_style_get_color(widget, state,
                                              MY_STYLE_FG_COLOR, 0x3F51B5FFu);
  float cy = (float)widget->rect.h / 2.0f;
  float frac = (s->max > s->min) ? (s->value - s->min) / (s->max - s->min) : 0.0f;
  float knob_x = frac * (float)(widget->rect.w - SLIDER_KNOB);
  /* M24b: knob default is plain white, an explicit style overrides it
   * (replaces the old 0xFFFFFF00 sentinel hack; same paint output) */
  uint32_t knob_rgb = knob_v != NULL ? my_value_get_uint32(knob_v)
                                     : 0xFFFFFFFFu;

  my_vgcanvas_set_fill_color(vg, my_color_from_rgba32(track_c));
  my_vgcanvas_fill_rounded_rect(
      vg, &(my_rectf_t){0, cy - SLIDER_TRACK_H / 2.0f, (float)widget->rect.w,
                        SLIDER_TRACK_H},
      SLIDER_TRACK_H / 2.0f);
  my_vgcanvas_set_fill_color(vg, my_color_from_rgba32(fill_c));
  my_vgcanvas_fill_rounded_rect(
      vg, &(my_rectf_t){0, cy - SLIDER_TRACK_H / 2.0f,
                        knob_x + SLIDER_KNOB / 2.0f, SLIDER_TRACK_H},
      SLIDER_TRACK_H / 2.0f);
  my_vgcanvas_set_fill_color(vg, my_color_from_rgba32(knob_rgb));
  my_vgcanvas_fill_rounded_rect(
      vg, &(my_rectf_t){knob_x, cy - SLIDER_KNOB / 2.0f, SLIDER_KNOB,
                        SLIDER_KNOB},
      SLIDER_KNOB / 2.0f);
}

static my_ret_t slider_on_event(my_widget_t* widget, const my_event_t* event) {
  my_slider_t* s = (my_slider_t*)widget;
  switch (event->type) {
    case MY_EVENT_POINTER_DOWN:
      s->dragging = true;
      slider_set_from_x(widget, event->u.pointer.x);
      return MY_RET_OK;
    case MY_EVENT_POINTER_MOVE:
      if (s->dragging) {
        slider_set_from_x(widget, event->u.pointer.x);
        return MY_RET_OK;
      }
      return MY_RET_FAIL;
    case MY_EVENT_POINTER_UP:
      if (s->dragging) {
        s->dragging = false;
        return MY_RET_OK;
      }
      return MY_RET_FAIL;
    default:
      return MY_RET_FAIL;
  }
}

static const my_widget_vtable_t s_slider_vtable = {slider_on_paint,
                                                   slider_on_event, NULL, NULL};

my_widget_t* my_slider_create(const my_allocator_t* allocator) {
  my_slider_t* s = (my_slider_t*)my_mem_calloc(allocator, 1, sizeof(my_slider_t));
  if (s == NULL) {
    return NULL;
  }
  if (my_widget_init((my_widget_t*)s, allocator, &s_slider_vtable, "slider") !=
      MY_RET_OK) {
    my_mem_free(allocator, s);
    return NULL;
  }
  s->min = 0.0f;
  s->max = 100.0f;
  ((my_widget_t*)s)->focusable = true;
  ((my_widget_t*)s)->widget_type = "slider";
  return (my_widget_t*)s;
}

my_ret_t my_slider_set_value(my_widget_t* slider, float value) {
  if (slider == NULL) {
    return MY_RET_INVALID_PARAMS;
  }
  slider_set_internal(slider, value, false);
  return MY_RET_OK;
}

float my_slider_get_value(my_widget_t* slider) {
  return slider != NULL ? ((my_slider_t*)slider)->value : 0.0f;
}

my_ret_t my_slider_set_range(my_widget_t* slider, float min, float max) {
  my_slider_t* s = (my_slider_t*)slider;
  if (slider == NULL || min >= max) {
    return MY_RET_INVALID_PARAMS;
  }
  s->min = min;
  s->max = max;
  slider_set_internal(slider, s->value, false);
  return MY_RET_OK;
}

my_ret_t my_slider_set_step(my_widget_t* slider, float step) {
  if (slider == NULL || step < 0.0f) {
    return MY_RET_INVALID_PARAMS;
  }
  ((my_slider_t*)slider)->step = step;
  return MY_RET_OK;
}
