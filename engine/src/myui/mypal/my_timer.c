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
  my_emitter_context_lease_t* lease;
  uint32_t interval_ms;
  uint64_t next_fire_ms;
  bool active; /**< false after remove; swept after fire */
  bool blocked_at_clock_limit; /**< saturated periodic deadline already fired */
  struct my_timer_entry_t* previous_current;
} my_timer_entry_t;

struct my_timer_manager_t {
  const my_allocator_t* allocator;
  my_timer_now_fn_t now_fn;
  void* now_ctx;
  my_darray_t* timers; /**< active heap of my_timer_entry_t* */
  my_darray_t* pending; /**< entries added while callbacks are running */
  uint32_t next_id;
  bool id_wrapped;
  bool destroy_requested;
  bool disposing;
  unsigned int operating;
  int firing; /**< > 0 while callbacks run */
  my_timer_entry_t* current; /**< callback entry, temporarily outside arrays */
};

static uint64_t timer_deadline(uint64_t now, uint32_t interval_ms) {
  uint64_t interval = (uint64_t)interval_ms;
  return interval > UINT64_MAX - now ? UINT64_MAX : now + interval;
}

static bool timer_id_in_use(const my_timer_manager_t* mgr, uint32_t id) {
  size_t i, n = my_darray_size(mgr->timers);
  for (i = 0; i < n; i++) {
    const my_timer_entry_t* t =
        (const my_timer_entry_t*)my_darray_get(mgr->timers, i);
    if (t->id == id) {
      return true;
    }
  }
  n = my_darray_size(mgr->pending);
  for (i = 0; i < n; i++) {
    const my_timer_entry_t* t =
        (const my_timer_entry_t*)my_darray_get(mgr->pending, i);
    if (t->id == id) {
      return true;
    }
  }
  {
    const my_timer_entry_t* current = mgr->current;
    while (current != NULL) {
      if (current->id == id) return true;
      current = current->previous_current;
    }
  }
  return false;
}

static size_t timer_entry_count(const my_timer_manager_t* mgr) {
  size_t count = my_darray_size(mgr->timers);
  size_t pending = my_darray_size(mgr->pending);
  if (count > SIZE_MAX - pending) {
    return SIZE_MAX;
  }
  count += pending;
  {
    const my_timer_entry_t* current = mgr->current;
    while (current != NULL) {
      if (count == SIZE_MAX) return SIZE_MAX;
      count++;
      current = current->previous_current;
    }
  }
  return count;
}

static bool timer_before(const my_timer_entry_t* left,
                         const my_timer_entry_t* right) {
  return left->next_fire_ms < right->next_fire_ms ||
         (left->next_fire_ms == right->next_fire_ms && left->id < right->id);
}

static void timer_heap_swap(my_darray_t* heap, size_t left, size_t right) {
  void* item = heap->items[left];
  heap->items[left] = heap->items[right];
  heap->items[right] = item;
}

static void timer_heap_sift_up(my_darray_t* heap, size_t index) {
  while (index != 0u) {
    size_t parent = (index - 1u) / 2u;
    if (timer_before((const my_timer_entry_t*)heap->items[parent],
                     (const my_timer_entry_t*)heap->items[index])) {
      break;
    }
    timer_heap_swap(heap, parent, index);
    index = parent;
  }
}

static void timer_heap_sift_down(my_darray_t* heap, size_t index) {
  size_t size = heap->size;
  for (;;) {
    size_t smallest = index;
    size_t left = index * 2u + 1u;
    size_t right = left + 1u;
    if (left < size &&
        timer_before((const my_timer_entry_t*)heap->items[left],
                     (const my_timer_entry_t*)heap->items[smallest])) {
      smallest = left;
    }
    if (right < size &&
        timer_before((const my_timer_entry_t*)heap->items[right],
                     (const my_timer_entry_t*)heap->items[smallest])) {
      smallest = right;
    }
    if (smallest == index) {
      return;
    }
    timer_heap_swap(heap, index, smallest);
    index = smallest;
  }
}

static my_timer_entry_t* timer_heap_pop(my_darray_t* heap) {
  my_timer_entry_t* result;
  if (heap == NULL || heap->size == 0u) {
    return NULL;
  }
  result = (my_timer_entry_t*)heap->items[0];
  heap->size--;
  if (heap->size != 0u) {
    heap->items[0] = heap->items[heap->size];
    timer_heap_sift_down(heap, 0u);
  }
  return result;
}

static my_ret_t timer_heap_push(my_darray_t* heap, my_timer_entry_t* timer) {
  my_ret_t ret = my_darray_push(heap, timer);
  if (ret == MY_RET_OK) {
    timer_heap_sift_up(heap, heap->size - 1u);
  }
  return ret;
}

static void timer_entry_free(const my_timer_manager_t* mgr,
                             my_timer_entry_t* timer) {
  if (timer == NULL) return;
  my_emitter_context_lease_unref(timer->lease);
  my_mem_free(mgr->allocator, timer);
}

static void timer_free_array(const my_timer_manager_t* mgr,
                             my_darray_t* array) {
  size_t i, n = my_darray_size(array);
  for (i = 0; i < n; i++) {
    my_timer_entry_t* timer =
        (my_timer_entry_t*)my_darray_get(array, i);
    timer_entry_free(mgr, timer);
  }
}

static uint32_t timer_allocate_id(my_timer_manager_t* mgr) {
  size_t entry_count;
  size_t attempts = 0;
  uint32_t candidate = mgr->next_id;

  if (candidate == 0u) {
    candidate = 1u;
  }
  if (!mgr->id_wrapped) {
    mgr->next_id = candidate == UINT32_MAX ? 1u : candidate + 1u;
    if (candidate == UINT32_MAX) {
      mgr->id_wrapped = true;
    }
    return candidate;
  }
  entry_count = timer_entry_count(mgr);
  if (entry_count >= (size_t)UINT32_MAX) {
    return 0u;
  }
  /* There is a free non-zero id after at most entry_count occupied ids. */
  if (!timer_id_in_use(mgr, candidate)) {
    mgr->next_id = candidate == UINT32_MAX ? 1u : candidate + 1u;
    return candidate;
  }
  while (attempts < entry_count) {
    candidate = candidate == UINT32_MAX ? 1u : candidate + 1u;
    attempts++;
    if (!timer_id_in_use(mgr, candidate)) {
      mgr->next_id = candidate == UINT32_MAX ? 1u : candidate + 1u;
      return candidate;
    }
  }
  return 0u;
}

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
  mgr->pending = my_darray_create(allocator, 0);
  if (mgr->timers == NULL || mgr->pending == NULL) {
    my_darray_destroy(mgr->pending);
    my_darray_destroy(mgr->timers);
    my_mem_free(allocator, mgr);
    return NULL;
  }
  return mgr;
}

static void timer_manager_dispose(my_timer_manager_t* mgr) {
  if (mgr == NULL) {
    return;
  }
  if (mgr->disposing) {
    return;
  }
  mgr->disposing = true;
  timer_free_array(mgr, mgr->timers);
  timer_free_array(mgr, mgr->pending);
  my_darray_destroy(mgr->timers);
  my_darray_destroy(mgr->pending);
  my_mem_free(mgr->allocator, mgr);
}

void my_timer_manager_destroy(my_timer_manager_t* mgr) {
  if (mgr == NULL) {
    return;
  }
  if (mgr->disposing) {
    return;
  }
  /* A callback may destroy its owning loop/manager. Keep the manager alive
   * until the outermost fire has unwound, because the current entry is still
   * being finalized by that fire. */
  if (mgr->firing != 0 || mgr->operating != 0u) {
    mgr->destroy_requested = true;
    return;
  }
  timer_manager_dispose(mgr);
}

static uint32_t timer_add_internal(
    my_timer_manager_t* mgr, my_timer_callback_t callback, void* ctx,
    my_emitter_context_lease_t* lease, uint32_t interval_ms) {
  my_timer_entry_t* t;
  uint32_t id;
  if (mgr == NULL || callback == NULL || mgr->destroy_requested ||
      mgr->disposing || mgr->operating != 0u ||
      (lease != NULL && !my_emitter_context_lease_is_valid(lease))) {
    return 0;
  }
  if (interval_ms == 0u) {
    return 0;
  }
  t = (my_timer_entry_t*)my_mem_calloc(mgr->allocator, 1, sizeof(my_timer_entry_t));
  if (t == NULL) {
    return 0;
  }
  id = timer_allocate_id(mgr);
  if (id == 0u) {
    timer_entry_free(mgr, t);
    return 0;
  }
  t->id = id;
  t->callback = callback;
  t->ctx = ctx;
  t->lease = lease != NULL ? my_emitter_context_lease_ref(lease) : NULL;
  if (lease != NULL && t->lease == NULL) {
    timer_entry_free(mgr, t);
    return 0;
  }
  t->interval_ms = interval_ms;
  t->next_fire_ms = timer_deadline(
      mgr->now_fn != NULL ? mgr->now_fn(mgr->now_ctx) : 0, interval_ms);
  t->active = true;
  if ((mgr->firing == 0 ? timer_heap_push(mgr->timers, t)
                         : my_darray_push(mgr->pending, t)) != MY_RET_OK) {
    timer_entry_free(mgr, t);
    return 0;
  }
  return t->id;
}

uint32_t my_timer_add(my_timer_manager_t* mgr, my_timer_callback_t callback,
                      void* ctx, uint32_t interval_ms) {
  return timer_add_internal(mgr, callback, ctx, NULL, interval_ms);
}

uint32_t my_timer_add_lease(my_timer_manager_t* mgr,
                            my_timer_callback_t callback,
                            my_emitter_context_lease_t* lease,
                            uint32_t interval_ms) {
  return timer_add_internal(mgr, callback, NULL, lease, interval_ms);
}

static void my_timer_sweep_array(my_timer_manager_t* mgr,
                                 my_darray_t* array, bool heap) {
  size_t i = 0;
  while (i < my_darray_size(array)) {
    my_timer_entry_t* t = (my_timer_entry_t*)my_darray_get(array, i);
    if (!t->active) {
      if (heap) {
        size_t last = array->size - 1u;
        array->items[i] = array->items[last];
        array->size--;
        if (i < array->size) {
          if (i != 0u &&
              timer_before((const my_timer_entry_t*)array->items[i],
                           (const my_timer_entry_t*)array->items[(i - 1u) / 2u])) {
            timer_heap_sift_up(array, i);
          } else {
            timer_heap_sift_down(array, i);
          }
        }
      } else {
        my_darray_remove_at(array, i);
      }
      timer_entry_free(mgr, t);
    } else {
      i++;
    }
  }
}

static void my_timer_sweep(my_timer_manager_t* mgr) {
  my_timer_sweep_array(mgr, mgr->timers, true);
  my_timer_sweep_array(mgr, mgr->pending, false);
}

static bool timer_mark_inactive(my_darray_t* array, uint32_t id) {
  size_t i, n = my_darray_size(array);
  for (i = 0; i < n; i++) {
    my_timer_entry_t* t = (my_timer_entry_t*)my_darray_get(array, i);
    if (t->id == id) {
      t->active = false;
      return true;
    }
  }
  return false;
}

static bool timer_mark_current_inactive(my_timer_manager_t* mgr, uint32_t id) {
  my_timer_entry_t* current = mgr->current;
  while (current != NULL) {
    if (current->id == id) {
      current->active = false;
      return true;
    }
    current = current->previous_current;
  }
  return false;
}

my_ret_t my_timer_remove(my_timer_manager_t* mgr, uint32_t id) {
  if (mgr == NULL || mgr->destroy_requested || mgr->disposing ||
      mgr->operating != 0u) {
    return MY_RET_INVALID_PARAMS;
  }
  if (timer_mark_inactive(mgr->timers, id) ||
      timer_mark_inactive(mgr->pending, id) ||
      timer_mark_current_inactive(mgr, id)) {
    if (mgr->firing == 0) {
      my_timer_sweep(mgr);
    }
    return MY_RET_OK;
  }
  return MY_RET_NOT_FOUND;
}

uint32_t my_timer_manager_due_in_ms(my_timer_manager_t* mgr) {
  uint64_t now;
  my_timer_entry_t* first;
  uint32_t result;
  if (mgr == NULL) {
    return UINT32_MAX;
  }
  if (mgr->destroy_requested || mgr->disposing || mgr->operating != 0u) {
    return UINT32_MAX;
  }
  mgr->operating++;
  now = mgr->now_fn != NULL ? mgr->now_fn(mgr->now_ctx) : 0;
  while ((first = (my_timer_entry_t*)my_darray_get(mgr->timers, 0u)) != NULL &&
         (!first->active ||
          (first->lease != NULL &&
           !my_emitter_context_lease_is_valid(first->lease)))) {
    (void)timer_heap_pop(mgr->timers);
    timer_entry_free(mgr, first);
    if (mgr->destroy_requested) {
      break;
    }
  }
  if (mgr->destroy_requested) {
    mgr->operating--;
    if (mgr->operating == 0u && mgr->firing == 0) {
      timer_manager_dispose(mgr);
    }
    return UINT32_MAX;
  }
  first = (my_timer_entry_t*)my_darray_get(mgr->timers, 0u);
  if (first == NULL) {
    result = UINT32_MAX;
    goto done;
  }
  if (first->blocked_at_clock_limit) {
    if (now != UINT64_MAX) {
      first->next_fire_ms = timer_deadline(now, first->interval_ms);
      first->blocked_at_clock_limit = false;
    } else {
      result = UINT32_MAX;
      goto done;
    }
  }
  if (first->next_fire_ms <= now) {
    result = 0u;
    goto done;
  }
  if (first->next_fire_ms - now > (uint64_t)UINT32_MAX) {
    result = UINT32_MAX;
    goto done;
  }
  result = (uint32_t)(first->next_fire_ms - now);
done:
  mgr->operating--;
  if (mgr->operating == 0u && mgr->firing == 0 && mgr->destroy_requested) {
    timer_manager_dispose(mgr);
  }
  return result;
}

uint32_t my_timer_manager_fire(my_timer_manager_t* mgr) {
  uint64_t now;
  uint32_t fired = 0;
  my_timer_entry_t* t;
  if (mgr == NULL) {
    return 0;
  }
  if (mgr->destroy_requested || mgr->disposing || mgr->operating != 0u) {
    return 0;
  }
  now = mgr->now_fn != NULL ? mgr->now_fn(mgr->now_ctx) : 0;
  mgr->firing++;
  while ((t = timer_heap_pop(mgr->timers)) != NULL) {
    if (!t->active) {
      timer_entry_free(mgr, t);
      if (mgr->destroy_requested) {
        break;
      }
      continue;
    }
    if (t->blocked_at_clock_limit) {
      if (now == UINT64_MAX) {
        (void)timer_heap_push(mgr->timers, t);
        break;
      }
      t->next_fire_ms = timer_deadline(now, t->interval_ms);
      t->blocked_at_clock_limit = false;
    }
    if (t->next_fire_ms > now) {
      (void)timer_heap_push(mgr->timers, t);
      break;
    }
    t->next_fire_ms = timer_deadline(now, t->interval_ms);
    t->blocked_at_clock_limit = false;
    {
      my_timer_entry_t* previous = mgr->current;
      my_ret_t callback_result;
      void* callback_context = t->lease != NULL
                                   ? my_emitter_context_lease_context(t->lease)
                                   : t->ctx;
      if (t->lease != NULL && callback_context == NULL) {
        timer_entry_free(mgr, t);
        if (mgr->destroy_requested) {
          break;
        }
        continue;
      }
      fired++;
      t->previous_current = mgr->current;
      mgr->current = t;
      callback_result = t->callback(callback_context);
      mgr->current = previous;
      t->previous_current = NULL;
      if (callback_result != MY_RET_OK || mgr->destroy_requested) {
        t->active = false;
      }
    }
    if (mgr->destroy_requested) {
      timer_entry_free(mgr, t);
      break;
    }
    if (t->active && now == UINT64_MAX && t->next_fire_ms == UINT64_MAX) {
      /* No representable future millisecond exists at the clock limit. Keep
       * the periodic timer armed but prevent an immediate busy-loop refire. */
      t->blocked_at_clock_limit = true;
    }
    if (!t->active) {
      timer_entry_free(mgr, t);
    } else if (timer_heap_push(mgr->timers, t) != MY_RET_OK) {
      t->active = false;
      timer_entry_free(mgr, t);
    }
  }
  mgr->firing--;
  if (mgr->firing == 0 && mgr->destroy_requested) {
    timer_manager_dispose(mgr);
    return fired;
  }
  if (mgr->firing == 0) {
    while ((t = (my_timer_entry_t*)my_darray_get(mgr->pending, 0u)) != NULL) {
      if (!t->active) {
        (void)my_darray_remove_at(mgr->pending, 0u);
        timer_entry_free(mgr, t);
      } else if (timer_heap_push(mgr->timers, t) == MY_RET_OK) {
        (void)my_darray_remove_at(mgr->pending, 0u);
        continue;
      } else {
        break;
      }
    }
    my_timer_sweep(mgr);
  }
  return fired;
}
