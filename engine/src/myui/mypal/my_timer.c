/**
 * @file my_timer.c
 * @brief Timer manager driven by the main loop (injectable clock).
 */
#include "mypal/my_timer.h"

#include "myc/my_darray.h"

typedef struct my_timer_entry_t my_timer_entry_t;

typedef enum my_timer_location_t {
  MY_TIMER_LOCATION_NONE = 0,
  MY_TIMER_LOCATION_HEAP,
  MY_TIMER_LOCATION_PENDING,
  MY_TIMER_LOCATION_CURRENT
} my_timer_location_t;

typedef struct my_timer_index_slot_t {
  uint32_t id;
  struct my_timer_entry_t* entry;
  uint8_t state;
} my_timer_index_slot_t;

struct my_timer_entry_t {
  uint32_t id;
  my_timer_callback_t callback;
  void* ctx;
  my_emitter_context_lease_t* lease;
  uint32_t interval_ms;
  uint64_t next_fire_ms;
  bool active; /**< false after remove; swept after fire */
  bool blocked_at_clock_limit; /**< saturated periodic deadline already fired */
  bool indexed;
  my_timer_location_t location;
  size_t heap_index;
  size_t pending_index;
  struct my_timer_entry_t* previous_current;
};

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
  my_timer_index_slot_t* index_slots;
  size_t index_capacity;
  size_t index_size;
  size_t index_tombstones;
};

#define MY_TIMER_INDEX_EMPTY 0u
#define MY_TIMER_INDEX_USED 1u
#define MY_TIMER_INDEX_DELETED 2u
#define MY_TIMER_HEAP_INDEX_NONE SIZE_MAX

static size_t timer_index_hash(uint32_t id, size_t capacity) {
  uint32_t value = id;
  value ^= value >> 16;
  value *= 0x7feb352du;
  value ^= value >> 15;
  value *= 0x846ca68bu;
  value ^= value >> 16;
  return (size_t)value & (capacity - 1u);
}

static my_timer_entry_t* timer_index_find(const my_timer_manager_t* mgr,
                                          uint32_t id) {
  size_t index;
  size_t probes;
  if (mgr == NULL || mgr->index_capacity == 0u || id == 0u) return NULL;
  index = timer_index_hash(id, mgr->index_capacity);
  for (probes = 0u; probes < mgr->index_capacity; ++probes) {
    const my_timer_index_slot_t* slot = &mgr->index_slots[index];
    if (slot->state == MY_TIMER_INDEX_EMPTY) return NULL;
    if (slot->state == MY_TIMER_INDEX_USED && slot->id == id) {
      return slot->entry;
    }
    index = (index + 1u) & (mgr->index_capacity - 1u);
  }
  return NULL;
}

static my_ret_t timer_index_rehash(my_timer_manager_t* mgr,
                                   size_t capacity) {
  my_timer_index_slot_t* slots;
  size_t i;
  if (mgr == NULL || capacity < 16u ||
      (capacity & (capacity - 1u)) != 0u) {
    return MY_RET_INVALID_PARAMS;
  }
  slots = (my_timer_index_slot_t*)my_mem_calloc(
      mgr->allocator, capacity, sizeof(my_timer_index_slot_t));
  if (slots == NULL) return MY_RET_OOM;
  for (i = 0u; i < mgr->index_capacity; ++i) {
    const my_timer_index_slot_t* old = &mgr->index_slots[i];
    size_t index;
    if (old->state != MY_TIMER_INDEX_USED) continue;
    index = timer_index_hash(old->id, capacity);
    while (slots[index].state == MY_TIMER_INDEX_USED) {
      index = (index + 1u) & (capacity - 1u);
    }
    slots[index] = *old;
  }
  my_mem_free(mgr->allocator, mgr->index_slots);
  mgr->index_slots = slots;
  mgr->index_capacity = capacity;
  mgr->index_tombstones = 0u;
  return MY_RET_OK;
}

static my_ret_t timer_index_prepare_insert(my_timer_manager_t* mgr) {
  size_t occupied;
  size_t threshold;
  if (mgr->index_capacity == 0u) {
    return timer_index_rehash(mgr, 16u);
  }
  threshold = mgr->index_capacity - mgr->index_capacity / 4u;
  occupied = mgr->index_size + mgr->index_tombstones;
  if (occupied >= threshold) {
    if (mgr->index_size >= threshold) {
      if (mgr->index_capacity > SIZE_MAX / 2u) return MY_RET_OOM;
      return timer_index_rehash(mgr, mgr->index_capacity * 2u);
    }
    return timer_index_rehash(mgr, mgr->index_capacity);
  }
  return MY_RET_OK;
}

static my_ret_t timer_index_insert(my_timer_manager_t* mgr,
                                   my_timer_entry_t* timer) {
  size_t index;
  size_t first_deleted = SIZE_MAX;
  my_ret_t ret;
  if (mgr == NULL || timer == NULL || timer->id == 0u) {
    return MY_RET_INVALID_PARAMS;
  }
  ret = timer_index_prepare_insert(mgr);
  if (ret != MY_RET_OK) return ret;
  index = timer_index_hash(timer->id, mgr->index_capacity);
  for (;;) {
    my_timer_index_slot_t* slot = &mgr->index_slots[index];
    if (slot->state == MY_TIMER_INDEX_EMPTY) {
      if (first_deleted != SIZE_MAX) slot = &mgr->index_slots[first_deleted];
      slot->id = timer->id;
      slot->entry = timer;
      slot->state = MY_TIMER_INDEX_USED;
      mgr->index_size++;
      if (first_deleted != SIZE_MAX) mgr->index_tombstones--;
      timer->indexed = true;
      return MY_RET_OK;
    }
    if (slot->state == MY_TIMER_INDEX_DELETED) {
      if (first_deleted == SIZE_MAX) first_deleted = index;
    } else if (slot->id == timer->id) {
      return MY_RET_FAIL;
    }
    index = (index + 1u) & (mgr->index_capacity - 1u);
  }
}

static void timer_index_remove(my_timer_manager_t* mgr,
                               my_timer_entry_t* timer) {
  size_t index;
  size_t probes;
  if (mgr == NULL || timer == NULL || !timer->indexed ||
      mgr->index_capacity == 0u) {
    return;
  }
  index = timer_index_hash(timer->id, mgr->index_capacity);
  for (probes = 0u; probes < mgr->index_capacity; ++probes) {
    my_timer_index_slot_t* slot = &mgr->index_slots[index];
    if (slot->state == MY_TIMER_INDEX_EMPTY) break;
    if (slot->state == MY_TIMER_INDEX_USED && slot->id == timer->id &&
        slot->entry == timer) {
      slot->entry = NULL;
      slot->state = MY_TIMER_INDEX_DELETED;
      mgr->index_size--;
      mgr->index_tombstones++;
      break;
    }
    index = (index + 1u) & (mgr->index_capacity - 1u);
  }
  timer->indexed = false;
}

static uint64_t timer_deadline(uint64_t now, uint32_t interval_ms) {
  uint64_t interval = (uint64_t)interval_ms;
  return interval > UINT64_MAX - now ? UINT64_MAX : now + interval;
}

static bool timer_before(const my_timer_entry_t* left,
                         const my_timer_entry_t* right) {
  return left->next_fire_ms < right->next_fire_ms ||
         (left->next_fire_ms == right->next_fire_ms && left->id < right->id);
}

static void timer_heap_swap(my_darray_t* heap, size_t left, size_t right) {
  my_timer_entry_t* item = (my_timer_entry_t*)heap->items[left];
  heap->items[left] = heap->items[right];
  heap->items[right] = item;
  ((my_timer_entry_t*)heap->items[left])->heap_index = left;
  ((my_timer_entry_t*)heap->items[right])->heap_index = right;
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
    ((my_timer_entry_t*)heap->items[0])->heap_index = 0u;
    timer_heap_sift_down(heap, 0u);
  }
  result->location = MY_TIMER_LOCATION_NONE;
  result->heap_index = MY_TIMER_HEAP_INDEX_NONE;
  return result;
}

static my_timer_entry_t* timer_heap_remove_at(my_darray_t* heap,
                                               size_t index) {
  my_timer_entry_t* result;
  size_t last;
  if (heap == NULL || index >= heap->size) return NULL;
  result = (my_timer_entry_t*)heap->items[index];
  last = heap->size - 1u;
  if (index != last) {
    heap->items[index] = heap->items[last];
    ((my_timer_entry_t*)heap->items[index])->heap_index = index;
  }
  heap->size = last;
  if (index < heap->size) {
    if (index != 0u &&
        timer_before((const my_timer_entry_t*)heap->items[index],
                     (const my_timer_entry_t*)heap->items[(index - 1u) / 2u])) {
      timer_heap_sift_up(heap, index);
    } else {
      timer_heap_sift_down(heap, index);
    }
  }
  result->location = MY_TIMER_LOCATION_NONE;
  result->heap_index = MY_TIMER_HEAP_INDEX_NONE;
  return result;
}

static my_ret_t timer_heap_push(my_darray_t* heap, my_timer_entry_t* timer) {
  my_ret_t ret = my_darray_push(heap, timer);
  if (ret == MY_RET_OK) {
    timer->location = MY_TIMER_LOCATION_HEAP;
    timer->heap_index = heap->size - 1u;
    timer->pending_index = SIZE_MAX;
    timer_heap_sift_up(heap, heap->size - 1u);
  }
  return ret;
}

static void timer_entry_free(const my_timer_manager_t* mgr,
                             my_timer_entry_t* timer) {
  if (timer == NULL) return;
  timer_index_remove((my_timer_manager_t*)mgr, timer);
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
  entry_count = mgr->index_size;
  if (entry_count >= (size_t)UINT32_MAX) {
    return 0u;
  }
  /* There is a free non-zero id after at most entry_count occupied ids. */
  if (timer_index_find(mgr, candidate) == NULL) {
    mgr->next_id = candidate == UINT32_MAX ? 1u : candidate + 1u;
    return candidate;
  }
  while (attempts < entry_count) {
    candidate = candidate == UINT32_MAX ? 1u : candidate + 1u;
    attempts++;
    if (timer_index_find(mgr, candidate) == NULL) {
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
  my_mem_free(mgr->allocator, mgr->index_slots);
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
  t->location = mgr->firing == 0 ? MY_TIMER_LOCATION_HEAP
                                 : MY_TIMER_LOCATION_PENDING;
  t->heap_index = MY_TIMER_HEAP_INDEX_NONE;
  t->pending_index = mgr->firing == 0 ? SIZE_MAX : mgr->pending->size;
  if (timer_index_insert(mgr, t) != MY_RET_OK) {
    timer_entry_free(mgr, t);
    return 0;
  }
  if ((mgr->firing == 0 ? timer_heap_push(mgr->timers, t)
                        : my_darray_push(mgr->pending, t)) != MY_RET_OK) {
    timer_index_remove(mgr, t);
    timer_entry_free(mgr, t);
    return 0;
  }
  if (mgr->firing != 0) t->location = MY_TIMER_LOCATION_PENDING;
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

static void timer_pending_reindex_from(my_timer_manager_t* mgr, size_t start);

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
          ((my_timer_entry_t*)array->items[i])->heap_index = i;
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
        timer_pending_reindex_from(mgr, i);
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

static void timer_pending_reindex_from(my_timer_manager_t* mgr, size_t start) {
  size_t i;
  if (mgr == NULL) return;
  for (i = start; i < mgr->pending->size; ++i) {
    ((my_timer_entry_t*)mgr->pending->items[i])->pending_index = i;
  }
}

my_ret_t my_timer_remove(my_timer_manager_t* mgr, uint32_t id) {
  my_timer_entry_t* timer;
  if (mgr == NULL || mgr->destroy_requested || mgr->disposing ||
      mgr->operating != 0u) {
    return MY_RET_INVALID_PARAMS;
  }
  timer = timer_index_find(mgr, id);
  if (timer != NULL) {
    timer->active = false;
    if (mgr->firing == 0) {
      if (timer->location == MY_TIMER_LOCATION_HEAP) {
        timer = timer_heap_remove_at(mgr->timers, timer->heap_index);
        timer_entry_free(mgr, timer);
      } else if (timer->location == MY_TIMER_LOCATION_PENDING) {
        size_t last = mgr->pending->size - 1u;
        size_t index = timer->pending_index;
        if (index < mgr->pending->size) {
          if (index != last) {
            mgr->pending->items[index] = mgr->pending->items[last];
            ((my_timer_entry_t*)mgr->pending->items[index])->pending_index = index;
          }
          mgr->pending->size = last;
          timer_entry_free(mgr, timer);
        }
      } else {
        my_timer_sweep(mgr);
      }
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
      t->location = MY_TIMER_LOCATION_CURRENT;
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
        timer_pending_reindex_from(mgr, 0u);
        timer_entry_free(mgr, t);
      } else if (timer_heap_push(mgr->timers, t) == MY_RET_OK) {
        (void)my_darray_remove_at(mgr->pending, 0u);
        timer_pending_reindex_from(mgr, 0u);
        t->location = MY_TIMER_LOCATION_HEAP;
        continue;
      } else {
        break;
      }
    }
    my_timer_sweep(mgr);
  }
  return fired;
}
