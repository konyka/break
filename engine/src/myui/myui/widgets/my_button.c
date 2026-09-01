/**
 * @file my_button.c
 * @brief Minimal push button widget.
 */
#include "myui/widgets/my_button.h"

#include "myc/my_str.h"
#include "myui/my_window.h"

#include <stdint.h>

#define BUTTON_COOLDOWN_TICK_MS 16

static uint64_t button_now_ms(const my_button_t* b) {
  my_pal_t* pal = my_window_pal_of_widget((my_widget_t*)b);
  return pal != NULL ? my_pal_time_now_ms(pal) : 0;
}

static uint64_t button_saturating_deadline(uint64_t now, uint32_t duration) {
  uint64_t deadline = now + (uint64_t)duration;
  return deadline < now ? UINT64_MAX : deadline;
}

static void button_stop_cooldown_timer(my_button_t* b) {
  if (b->cooldown_timer != 0 && b->cooldown_loop != NULL) {
    my_pal_main_loop_remove_timer(b->cooldown_loop, b->cooldown_timer);
  }
  b->cooldown_timer = 0;
  b->cooldown_loop = NULL;
}

static void button_cancel_release_timer(my_button_t* b) {
  if (b->release_timer != 0) {
    if (b->release_loop != NULL) {
      my_pal_main_loop_remove_timer(b->release_loop, b->release_timer);
    }
    b->release_timer = 0;
    b->release_loop = NULL;
  }
}

static my_ret_t button_cooldown_cb(void* ctx);

static void button_ensure_cooldown_timer(my_button_t* b) {
  my_pal_main_loop_t* loop;
  if (!my_button_is_cooling_down((const my_widget_t*)b) ||
      b->cooldown_timer != 0) {
    return;
  }
  loop = my_window_loop_of_widget((my_widget_t*)b);
  if (loop == NULL) {
    return;
  }
  b->cooldown_timer = my_pal_main_loop_add_timer(
      loop, button_cooldown_cb, b, BUTTON_COOLDOWN_TICK_MS);
  if (b->cooldown_timer != 0) {
    b->cooldown_loop = loop;
  }
}

static my_color_t button_state_color(my_button_t* b) {
  my_widget_t* w = (my_widget_t*)b;
  my_widget_state_t state = my_widget_current_state(w, b->pressed);
  uint32_t fallback;
  switch (state) {
    /* M24b: the former color_normal/hover/pressed/disabled struct fields,
     * inlined as literals (identical values, rgb -> 0xRRGGBBAA) */
    case MY_STATE_DISABLED:
      fallback = 0x787878FFu; /* rgb(120,120,120) */
      break;
    case MY_STATE_PRESSED:
      fallback = 0x9696A0FFu; /* rgb(150,150,160) */
      break;
    case MY_STATE_HOVER:
      fallback = 0xDCDCE6FFu; /* rgb(220,220,230) */
      break;
    default:
      fallback = 0xC8C8C8FFu; /* rgb(200,200,200) */
      break;
  }
  return my_color_from_rgba32(
      my_widget_style_get_color(w, state, MY_STYLE_BG_COLOR, fallback));
}

static void button_on_paint(my_widget_t* widget, my_vgcanvas_t* vg) {
  my_button_t* b = (my_button_t*)widget;
  button_ensure_cooldown_timer(b);
  my_widget_state_t state = my_widget_current_state(widget, b->pressed);
  uint32_t border = my_widget_style_get_color(
      widget, state, MY_STYLE_BORDER_COLOR, 0x000000FFu);
  int32_t radius =
      my_widget_style_get_int(widget, state, MY_STYLE_ROUND_RADIUS, 4);
  my_vgcanvas_set_fill_color(vg, button_state_color(b));
  my_vgcanvas_fill_rounded_rect(vg, &(my_rectf_t){0, 0, (float)widget->rect.w,
                                                 (float)widget->rect.h},
                                (float)radius);
  my_vgcanvas_set_stroke_color(vg, my_color_from_rgba32(border));
  my_vgcanvas_set_line_width(vg, 1);
  my_vgcanvas_stroke_rect(vg, &(my_rectf_t){0, 0, (float)widget->rect.w,
                                            (float)widget->rect.h});
  if (my_button_is_cooling_down((const my_widget_t*)b)) {
    float progress = my_button_cooldown_progress((const my_widget_t*)b);
    my_vgcanvas_set_fill_color(vg, my_color_from_rgba32(0x00000040u));
    my_vgcanvas_fill_rect(vg, &(my_rectf_t){0, 0, (float)widget->rect.w,
                                           (float)widget->rect.h * progress});
  }
  /* text: real draw_text when a font is set on the backend (M7a) */
  if (b->text != NULL) {
    int32_t tw = 0, th = 0;
    int32_t font_size =
        my_widget_style_get_int(widget, state, MY_STYLE_FONT_SIZE, 14);
    my_vgcanvas_set_font(vg, NULL, font_size);
    if (my_vgcanvas_measure_text(vg, b->text, &tw, &th) == MY_RET_OK) {
      uint32_t fg = my_widget_style_get_color(widget, state,
                                              MY_STYLE_FG_COLOR, 0x212121FFu);
      my_vgcanvas_set_fill_color(vg, my_color_from_rgba32(fg));
      my_vgcanvas_draw_text(vg, b->text,
                            ((float)widget->rect.w - (float)tw) / 2.0f,
                            ((float)widget->rect.h - (float)th) / 2.0f);
    } else {
      my_vgcanvas_draw_text(vg, b->text, 0, 0); /* placeholder, ignored */
    }
  }
}

static bool button_point_inside(my_widget_t* widget, int32_t gx, int32_t gy) {
  int32_t lx = gx, ly = gy;
  my_widget_global_to_local(widget, &lx, &ly);
  return lx >= 0 && ly >= 0 && lx < widget->rect.w && ly < widget->rect.h;
}

bool my_button_is_cooling_down(const my_widget_t* button) {
  const my_button_t* b;
  if (button == NULL) {
    return false;
  }
  b = (const my_button_t*)button;
  return b->cooldown_until_ms != 0 && button_now_ms(b) < b->cooldown_until_ms;
}

uint32_t my_button_cooldown_remaining_ms(const my_widget_t* button) {
  const my_button_t* b;
  uint64_t remaining;
  if (!my_button_is_cooling_down(button)) {
    return 0;
  }
  b = (const my_button_t*)button;
  remaining = b->cooldown_until_ms - button_now_ms(b);
  return remaining > UINT32_MAX ? UINT32_MAX : (uint32_t)remaining;
}

float my_button_cooldown_progress(const my_widget_t* button) {
  const my_button_t* b;
  uint32_t remaining;
  if (button == NULL) {
    return 0.0f;
  }
  b = (const my_button_t*)button;
  if (b->cooldown_active_ms == 0 || !my_button_is_cooling_down(button)) {
    return 0.0f;
  }
  remaining = my_button_cooldown_remaining_ms(button);
  if (remaining >= b->cooldown_active_ms) {
    return 1.0f;
  }
  return (float)remaining / (float)b->cooldown_active_ms;
}

/* keep the pressed visual visible at least this long; with frame
 * coalescing a quick click would otherwise never paint it */
#define BUTTON_PRESS_MIN_MS 120

static my_ret_t button_cooldown_cb(void* ctx) {
  my_button_t* b = (my_button_t*)ctx;
  if (!my_button_is_cooling_down((const my_widget_t*)b)) {
    b->cooldown_until_ms = 0;
    b->cooldown_active_ms = 0;
    b->cooldown_timer = 0;
    b->cooldown_loop = NULL;
    my_widget_invalidate((my_widget_t*)b, NULL);
    return MY_RET_FAIL;
  }
  my_widget_invalidate((my_widget_t*)b, NULL);
  return MY_RET_OK;
}

static void button_start_cooldown(my_button_t* b) {
  if (b->cooldown_ms == 0) {
    b->cooldown_until_ms = 0;
    b->cooldown_active_ms = 0;
    button_stop_cooldown_timer(b);
    return;
  }
  b->cooldown_active_ms = b->cooldown_ms;
  b->cooldown_until_ms =
      button_saturating_deadline(button_now_ms(b), b->cooldown_ms);
  button_ensure_cooldown_timer(b);
  my_widget_invalidate((my_widget_t*)b, NULL);
}

static my_ret_t button_release_cb(void* ctx) {
  my_button_t* b = (my_button_t*)ctx;
  b->release_timer = 0;
  b->release_loop = NULL;
  b->pressed = false;
  my_widget_invalidate((my_widget_t*)b, NULL);
  return MY_RET_FAIL; /* one-shot */
}

static void button_release(my_button_t* b) {
  my_widget_t* w = (my_widget_t*)b;
  my_pal_t* pal = my_window_pal_of_widget(w);
  my_pal_main_loop_t* loop = my_window_loop_of_widget(w);
  uint64_t now = pal != NULL ? my_pal_time_now_ms(pal) : 0;
  if (loop != NULL && pal != NULL && now - b->down_ms < BUTTON_PRESS_MIN_MS) {
    if (b->release_timer == 0) {
      b->release_timer = my_pal_main_loop_add_timer(
          loop, button_release_cb, b,
          (uint32_t)(BUTTON_PRESS_MIN_MS - (now - b->down_ms)));
      if (b->release_timer != 0) {
        b->release_loop = loop;
      }
    }
    return;
  }
  b->pressed = false;
}

static my_ret_t button_on_event(my_widget_t* widget, const my_event_t* event) {
  my_button_t* b = (my_button_t*)widget;
  switch (event->type) {
    case MY_EVENT_POINTER_DOWN: {
      my_pal_t* pal;
      if (my_button_is_cooling_down((const my_widget_t*)b)) {
        button_cancel_release_timer(b);
        b->pressed = false;
        my_widget_invalidate(widget, NULL);
        return MY_RET_FAIL;
      }
      if (b->release_timer != 0) { /* a fresh press cancels a pending release */
        button_cancel_release_timer(b);
      }
      pal = my_window_pal_of_widget(widget);
      b->down_ms = pal != NULL ? my_pal_time_now_ms(pal) : 0;
      b->pressed = true;
      my_widget_invalidate(widget, NULL);
      return MY_RET_OK;
    }
    case MY_EVENT_POINTER_UP:
      if (my_button_is_cooling_down((const my_widget_t*)b)) {
        button_cancel_release_timer(b);
        b->pressed = false;
        my_widget_invalidate(widget, NULL);
        return MY_RET_FAIL;
      }
      if (!b->pressed) {
        return MY_RET_FAIL;
      }
      button_release(b);
      my_widget_invalidate(widget, NULL);
      if (button_point_inside(widget, event->u.pointer.x, event->u.pointer.y)) {
        button_start_cooldown(b);
        my_emitter_emit(widget->emitter, "click", (void*)event);
      }
      return MY_RET_OK;
    default:
      return MY_RET_FAIL;
  }
}

static const my_widget_vtable_t s_button_vtable = {button_on_paint,
                                                   button_on_event, NULL, NULL};

static void button_destroy_chain(my_object_t* obj) {
  my_button_t* b = (my_button_t*)obj;
  button_cancel_release_timer(b);
  button_stop_cooldown_timer(b);
  my_mem_free(obj->allocator, b->text);
  my_widget_destroy((my_widget_t*)b);
  my_object_destroy(obj);
}

my_widget_t* my_button_create(const my_allocator_t* allocator, const char* text) {
  my_button_t* b = (my_button_t*)my_mem_calloc(allocator, 1, sizeof(my_button_t));
  if (b == NULL) {
    return NULL;
  }
  if (my_widget_init((my_widget_t*)b, allocator, &s_button_vtable, "button") !=
      MY_RET_OK) {
    my_mem_free(allocator, b);
    return NULL;
  }
  ((my_object_t*)b)->destroy = button_destroy_chain;
  if (text != NULL) {
    b->text = my_strdup(allocator, text);
    if (b->text == NULL) {
      my_object_unref((my_object_t*)b);
      return NULL;
    }
  }
  ((my_widget_t*)b)->focusable = true;
  ((my_widget_t*)b)->widget_type = "button";
  return (my_widget_t*)b;
}

my_ret_t my_button_set_text(my_widget_t* button, const char* text) {
  my_button_t* b = (my_button_t*)button;
  char* copy;
  if (button == NULL) {
    return MY_RET_INVALID_PARAMS;
  }
  copy = my_strdup(((my_object_t*)button)->allocator, text);
  if (text != NULL && copy == NULL) {
    return MY_RET_OOM;
  }
  my_mem_free(((my_object_t*)button)->allocator, b->text);
  b->text = copy;
  my_widget_invalidate(button, NULL);
  return MY_RET_OK;
}

my_ret_t my_button_set_cooldown(my_widget_t* button, uint32_t duration_ms) {
  my_button_t* b;
  if (button == NULL) {
    return MY_RET_INVALID_PARAMS;
  }
  b = (my_button_t*)button;
  b->cooldown_ms = duration_ms;
  if (duration_ms == 0) {
    b->cooldown_until_ms = 0;
    b->cooldown_active_ms = 0;
    button_stop_cooldown_timer(b);
    my_widget_invalidate(button, NULL);
  }
  return MY_RET_OK;
}
