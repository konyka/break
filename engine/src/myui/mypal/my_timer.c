/**
 * @file my_timer.c
 * @brief Timer manager driven by the main loop (injectable clock).
 */
#include "mypal/my_timer.h"

#include "myc/my_darray.h"

typedef struct my_timer_entry_t {
  uint32_t id;
  my_timer_callback_t callback;
  void* ctx;
  uint32_t interval_ms;
  uint64_t next_fire_ms;
  bool active; /**< false after remove; swept after fire */
} my_timer_entry_t;

struct my_timer_manager_t {
  const my_allocator_t* allocator;
  my_timer_now_fn_t now_fn;
  void* now_ctx;
  my_darray_t* timers; /**< my_timer_entry_t* */
  uint32_t next_id;
  int firing; /**< > 0 while callbacks run */
};

my_timer_manager_t* my_timer_manager_create(const my_allocator_t* allocator,
                                            my_timer_now_fn_t now_fn,
                                            void* now_ctx) {
  my_timer_manager_t* mgr =
      (my_timer_manager_t*)my_mem_calloc(allocator, 1, sizeof(my_timer_manager_t));
  if (mgr == NULL) {
    return NULL;
  }
  mgr->allocator = allocator;
  mgr->now_fn = now_fn;
  mgr->now_ctx = now_ctx;
  mgr->next_id = 1;
  mgr->timers = my_darray_create(allocator, 0);
  if (mgr->timers == NULL) {
    my_mem_free(allocator, mgr);
    return NULL;
  }
  return mgr;
}

void my_timer_manager_destroy(my_timer_manager_t* mgr) {
  size_t i, n;
  if (mgr == NULL) {
    return;
  }
  n = my_darray_size(mgr->timers);
  for (i = 0; i < n; i++) {
    my_mem_free(mgr->allocator, my_darray_get(mgr->timers, i));
  }
  my_darray_destroy(mgr->timers);
  my_mem_free(mgr->allocator, mgr);
}

uint32_t my_timer_add(my_timer_manager_t* mgr, my_timer_callback_t callback,
                      void* ctx, uint32_t interval_ms) {
  my_timer_entry_t* t;
  if (mgr == NULL || callback == NULL) {
    return 0;
  }
  t = (my_timer_entry_t*)my_mem_calloc(mgr->allocator, 1, sizeof(my_timer_entry_t));
  if (t == NULL) {
    return 0;
  }
  t->id = mgr->next_id++;
  t->callback = callback;
  t->ctx = ctx;
  t->interval_ms = interval_ms;
  t->next_fire_ms =
      (mgr->now_fn != NULL ? mgr->now_fn(mgr->now_ctx) : 0) + interval_ms;
  t->active = true;
  if (my_darray_push(mgr->timers, t) != MY_RET_OK) {
    my_mem_free(mgr->allocator, t);
    return 0;
  }
  return t->id;
}

static void my_timer_sweep(my_timer_manager_t* mgr) {
  size_t i = 0;
  while (i < my_darray_size(mgr->timers)) {
    my_timer_entry_t* t = (my_timer_entry_t*)my_darray_get(mgr->timers, i);
    if (!t->active) {
      my_darray_remove_at(mgr->timers, i);
      my_mem_free(mgr->allocator, t);
    } else {
      i++;
    }
  }
}

my_ret_t my_timer_remove(my_timer_manager_t* mgr, uint32_t id) {
  size_t i, n;
  if (mgr == NULL) {
    return MY_RET_INVALID_PARAMS;
  }
  n = my_darray_size(mgr->timers);
  for (i = 0; i < n; i++) {
    my_timer_entry_t* t = (my_timer_entry_t*)my_darray_get(mgr->timers, i);
    if (t->id == id) {
      t->active = false;
      if (mgr->firing == 0) {
        my_darray_remove_at(mgr->timers, i);
        my_mem_free(mgr->allocator, t);
      }
      return MY_RET_OK;
    }
  }
  return MY_RET_NOT_FOUND;
}

uint32_t my_timer_manager_due_in_ms(my_timer_manager_t* mgr) {
  uint64_t now, best;
  size_t i, n;
  bool found = false;
  if (mgr == NULL) {
    return UINT32_MAX;
  }
  now = mgr->now_fn != NULL ? mgr->now_fn(mgr->now_ctx) : 0;
  best = 0;
  n = my_darray_size(mgr->timers);
  for (i = 0; i < n; i++) {
    const my_timer_entry_t* t = (const my_timer_entry_t*)my_darray_get(mgr->timers, i);
    if (t->active && (!found || t->next_fire_ms < best)) {
      best = t->next_fire_ms;
      found = true;
    }
  }
  if (!found) {
    return UINT32_MAX;
  }
  if (best <= now) {
    return 0;
  }
  return (uint32_t)(best - now);
}

uint32_t my_timer_manager_fire(my_timer_manager_t* mgr) {
  uint64_t now;
  uint32_t fired = 0;
  size_t i, n;
  if (mgr == NULL) {
    return 0;
  }
  now = mgr->now_fn != NULL ? mgr->now_fn(mgr->now_ctx) : 0;
  mgr->firing++;
  /* iterate by index with captured n: removals during callbacks only flip
   * active flags, additions are ignored this round */
  n = my_darray_size(mgr->timers);
  for (i = 0; i < n; i++) {
    my_timer_entry_t* t = (my_timer_entry_t*)my_darray_get(mgr->timers, i);
    if (t->active && t->next_fire_ms <= now) {
      t->next_fire_ms = now + t->interval_ms; /* reschedule before cb */
      fired++;
      if (t->callback(t->ctx) != MY_RET_OK) {
        t->active = false;
      }
    }
  }
  mgr->firing--;
  if (mgr->firing == 0) {
    my_timer_sweep(mgr);
  }
  return fired;
}
