/**
 * @file my_animator.c
 * @brief Property animations driven by a 16ms main-loop timer.
 */
#include "myui/my_animator.h"

#include <string.h>

#define MY_ANIM_TICK_MS 33 /* 30 fps frame cap (matches the wm paint tick) */

/* ---------------- easing ---------------- */

float my_easing_linear(float t) {
  return t;
}

float my_easing_ease_in(float t) {
  return t * t;
}

float my_easing_ease_out(float t) {
  float u = 1.0f - t;
  return 1.0f - u * u;
}

float my_easing_ease_in_out(float t) {
  return t * t * (3.0f - 2.0f * t); /* smoothstep */
}

/* ---------------- manager ---------------- */

typedef struct my_anim_t {
  uint32_t id;
  my_widget_t* widget; /**< weak; cancelled on removal via stop_widget */
  char prop[4];        /**< "x" "y" "w" "h" "xy" */
  float from_x, from_y;
  float to_x, to_y;
  uint64_t start_ms;
  uint32_t duration_ms;
  uint32_t delay_ms;
  my_easing_fn_t easing;
  int repeat_count; /**< extra plays; 0 = once, -1 = forever */
  bool yoyo;
  my_anim_update_cb_t on_update;
  my_anim_done_cb_t on_done;
  void* cb_ctx;
  bool active;
} my_anim_t;

struct my_animator_manager_t {
  const my_allocator_t* allocator;
  my_pal_t* pal;
  my_pal_main_loop_t* loop;
  my_darray_t* anims; /**< my_anim_t* */
  uint32_t next_id;
  uint32_t timer_id;
  bool timer_active;
};

static my_ret_t anim_tick(void* ctx);

static void ensure_timer(my_animator_manager_t* mgr) {
  if (!mgr->timer_active && my_animator_manager_active_count(mgr) > 0) {
    mgr->timer_id =
        my_pal_main_loop_add_timer(mgr->loop, anim_tick, mgr, MY_ANIM_TICK_MS);
    mgr->timer_active = mgr->timer_id > 0;
  }
}

static void drop_timer(my_animator_manager_t* mgr) {
  if (mgr->timer_active) {
    my_pal_main_loop_remove_timer(mgr->loop, mgr->timer_id);
    mgr->timer_active = false;
  }
}

my_animator_manager_t* my_animator_manager_create(const my_allocator_t* allocator,
                                                  my_pal_t* pal,
                                                  my_pal_main_loop_t* loop) {
  my_animator_manager_t* mgr;
  if (pal == NULL || loop == NULL) {
    return NULL;
  }
  mgr = (my_animator_manager_t*)my_mem_calloc(allocator, 1,
                                              sizeof(my_animator_manager_t));
  if (mgr == NULL) {
    return NULL;
  }
  mgr->allocator = allocator;
  mgr->pal = pal;
  mgr->loop = loop;
  mgr->next_id = 1;
  mgr->anims = my_darray_create(allocator, 0);
  if (mgr->anims == NULL) {
    my_mem_free(allocator, mgr);
    return NULL;
  }
  return mgr;
}

void my_animator_manager_destroy(my_animator_manager_t* mgr) {
  size_t i, n;
  if (mgr == NULL) {
    return;
  }
  drop_timer(mgr);
  n = my_darray_size(mgr->anims);
  for (i = 0; i < n; i++) {
    my_mem_free(mgr->allocator, my_darray_get(mgr->anims, i));
  }
  my_darray_destroy(mgr->anims);
  my_mem_free(mgr->allocator, mgr);
}

size_t my_animator_manager_active_count(my_animator_manager_t* mgr) {
  size_t i, n, count = 0;
  if (mgr == NULL) {
    return 0;
  }
  n = my_darray_size(mgr->anims);
  for (i = 0; i < n; i++) {
    if (((my_anim_t*)my_darray_get(mgr->anims, i))->active) {
      count++;
    }
  }
  return count;
}

uint32_t my_animator_animate(my_animator_manager_t* mgr, my_widget_t* widget,
                             const char* prop, float to_x, float to_y,
                             uint32_t duration_ms, uint32_t delay_ms,
                             my_easing_fn_t easing, int repeat_count, bool yoyo,
                             my_anim_update_cb_t on_update,
                             my_anim_done_cb_t on_done, void* ctx) {
  my_anim_t* a;
  if (mgr == NULL || widget == NULL || prop == NULL || strlen(prop) >= 4 ||
      (strcmp(prop, "x") != 0 && strcmp(prop, "y") != 0 &&
       strcmp(prop, "w") != 0 && strcmp(prop, "h") != 0 &&
       strcmp(prop, "xy") != 0)) {
    return 0;
  }
  a = (my_anim_t*)my_mem_calloc(mgr->allocator, 1, sizeof(my_anim_t));
  if (a == NULL) {
    return 0;
  }
  a->id = mgr->next_id++;
  a->widget = widget;
  strcpy(a->prop, prop);
  a->from_x = strcmp(prop, "y") == 0 ? (float)widget->rect.y
                                     : (float)widget->rect.x;
  a->from_y = (float)widget->rect.y;
  if (strcmp(prop, "w") == 0) {
    a->from_x = (float)widget->rect.w;
  } else if (strcmp(prop, "h") == 0) {
    a->from_x = (float)widget->rect.h;
  }
  a->to_x = to_x;
  a->to_y = to_y;
  a->start_ms = my_pal_time_now_ms(mgr->pal);
  a->duration_ms = duration_ms > 0 ? duration_ms : 1;
  a->delay_ms = delay_ms;
  a->easing = easing != NULL ? easing : my_easing_linear;
  a->repeat_count = repeat_count;
  a->yoyo = yoyo;
  a->on_update = on_update;
  a->on_done = on_done;
  a->cb_ctx = ctx;
  a->active = true;
  if (my_darray_push(mgr->anims, a) != MY_RET_OK) {
    my_mem_free(mgr->allocator, a);
    return 0;
  }
  ensure_timer(mgr);
  return a->id;
}

uint32_t my_animator_move_to(my_widget_t* widget, int32_t x, int32_t y,
                             uint32_t duration_ms, my_easing_fn_t easing) {
  my_widget_t* root = widget;
  if (widget == NULL) {
    return 0;
  }
  while (root->parent != NULL) {
    root = root->parent;
  }
  if (root->anim_mgr == NULL) {
    return 0;
  }
  return my_animator_animate((my_animator_manager_t*)root->anim_mgr, widget, "xy",
                             (float)x, (float)y, duration_ms, 0, easing, 0,
                             false, NULL, NULL, NULL);
}

void my_animator_stop(my_animator_manager_t* mgr, uint32_t anim_id) {
  size_t i, n;
  if (mgr == NULL) {
    return;
  }
  n = my_darray_size(mgr->anims);
  for (i = 0; i < n; i++) {
    my_anim_t* a = (my_anim_t*)my_darray_get(mgr->anims, i);
    if (a->id == anim_id) {
      a->active = false;
      break;
    }
  }
  if (my_animator_manager_active_count(mgr) == 0) {
    drop_timer(mgr);
  }
}

void my_animator_stop_widget(my_animator_manager_t* mgr, my_widget_t* widget) {
  size_t i, n;
  if (mgr == NULL || widget == NULL) {
    return;
  }
  n = my_darray_size(mgr->anims);
  for (i = 0; i < n; i++) {
    my_anim_t* a = (my_anim_t*)my_darray_get(mgr->anims, i);
    my_widget_t* p = a->widget;
    while (p != NULL && p != widget) {
      p = p->parent;
    }
    if (p == widget) {
      a->active = false;
    }
  }
  if (my_animator_manager_active_count(mgr) == 0) {
    drop_timer(mgr);
  }
}

/* ---------------- ticking ---------------- */

static void anim_apply(my_anim_t* a, float eased) {
  my_widget_t* w = a->widget;
  my_rect_t r = w->rect;
  int32_t vx = (int32_t)(a->from_x + (a->to_x - a->from_x) * eased);
  int32_t vy = (int32_t)(a->from_y + (a->to_y - a->from_y) * eased);

  if (strcmp(a->prop, "x") == 0) {
    r.x = vx;
  } else if (strcmp(a->prop, "y") == 0) {
    r.y = vx;
  } else if (strcmp(a->prop, "w") == 0) {
    r.w = vx;
  } else if (strcmp(a->prop, "h") == 0) {
    r.h = vx;
  } else { /* "xy" */
    r.x = vx;
    r.y = vy;
  }
  (void)my_widget_set_layout_rect(w, &r);
  if (a->on_update != NULL) {
    a->on_update(w, a->cb_ctx);
  }
}

static my_ret_t anim_tick(void* ctx) {
  my_animator_manager_t* mgr = (my_animator_manager_t*)ctx;
  uint64_t now = my_pal_time_now_ms(mgr->pal);
  size_t i, n = my_darray_size(mgr->anims);

  for (i = 0; i < n; i++) {
    my_anim_t* a = (my_anim_t*)my_darray_get(mgr->anims, i);
    uint64_t elapsed;
    uint64_t cycle;
    float t;
    if (!a->active) {
      continue;
    }
    if (now < a->start_ms + a->delay_ms) {
      continue;
    }
    elapsed = now - a->start_ms - a->delay_ms;
    cycle = elapsed / a->duration_ms;
    if (a->repeat_count >= 0 && (int)cycle > a->repeat_count) {
      /* final frame, then done */
      float tf = (a->yoyo && (a->repeat_count % 2) == 1) ? 0.0f : 1.0f;
      anim_apply(a, a->easing(tf));
      a->active = false;
      if (a->on_done != NULL) {
        a->on_done(a->widget, a->cb_ctx);
      }
      continue;
    }
    t = (float)(elapsed % a->duration_ms) / (float)a->duration_ms;
    if (a->yoyo && (cycle % 2) == 1) {
      t = 1.0f - t;
    }
    anim_apply(a, a->easing(t));
  }

  if (my_animator_manager_active_count(mgr) == 0) {
    drop_timer(mgr);
  }
  return MY_RET_OK;
}
