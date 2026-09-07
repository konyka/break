/**
 * @file my_emitter.c
 * @brief Event emitter implementation (mark-and-sweep removal).
 */
#include "myc/my_emitter.h"

#include <stdint.h>
#include <stdatomic.h>

#include "myc/my_darray.h"
#include "myc/my_ref_count.h"
#include "myc/my_str.h"

struct my_emitter_context_lease_t {
  atomic_uint ref_count;
  atomic_bool valid;
  atomic_flag gate;
  const my_allocator_t* allocator;
  void* ctx;
  my_emitter_context_lease_destroy_fn_t destroy_ctx;
};

typedef struct my_listener_t {
  uint32_t id;
  char* event;
  my_event_callback_t callback;
  void* ctx;
  my_event_context_destroy_fn_t destroy_ctx;
  my_emitter_context_lease_t* lease;
  bool active; /**< false after my_emitter_off(), swept after the current emit */
} my_listener_t;

struct my_emitter_t {
  const my_allocator_t* allocator;
  my_darray_t* listeners; /**< my_listener_t* elements */
  uint32_t next_id;
  int emitting; /**< > 0 while an emit is in progress */
  bool destroy_requested;
  bool sweeping;
  bool disposing;
};

my_emitter_context_lease_t* my_emitter_context_lease_create(
    const my_allocator_t* allocator, void* ctx,
    my_emitter_context_lease_destroy_fn_t destroy_ctx) {
  my_emitter_context_lease_t* lease =
      (my_emitter_context_lease_t*)my_mem_calloc(allocator, 1u,
                                                 sizeof(*lease));
  if (lease == NULL) return NULL;
  atomic_init(&lease->ref_count, 1u);
  atomic_init(&lease->valid, true);
  atomic_flag_clear(&lease->gate);
  lease->allocator = allocator;
  lease->ctx = ctx;
  lease->destroy_ctx = destroy_ctx;
  return lease;
}

my_emitter_context_lease_t* my_emitter_context_lease_ref(
    my_emitter_context_lease_t* lease) {
  if (lease == NULL || !my_ref_count_try_ref(&lease->ref_count)) {
    return NULL;
  }
  return lease;
}

void my_emitter_context_lease_unref(my_emitter_context_lease_t* lease) {
  if (lease == NULL || !my_ref_count_release(&lease->ref_count)) return;
  if (lease->destroy_ctx != NULL) lease->destroy_ctx(lease->ctx);
  my_mem_free(lease->allocator, lease);
}

void my_emitter_context_lease_invalidate(my_emitter_context_lease_t* lease) {
  if (lease == NULL) return;
  while (atomic_flag_test_and_set_explicit(&lease->gate,
                                           memory_order_acquire)) {
  }
  atomic_store_explicit(&lease->valid, false, memory_order_release);
  atomic_flag_clear_explicit(&lease->gate, memory_order_release);
}

bool my_emitter_context_lease_is_valid(
    const my_emitter_context_lease_t* lease) {
  return lease != NULL &&
         atomic_load_explicit(&lease->valid, memory_order_acquire);
}

void* my_emitter_context_lease_context(
    my_emitter_context_lease_t* lease) {
  void* ctx;
  if (lease == NULL) return NULL;
  while (atomic_flag_test_and_set_explicit(&lease->gate,
                                           memory_order_acquire)) {
  }
  ctx = atomic_load_explicit(&lease->valid, memory_order_acquire)
            ? lease->ctx
            : NULL;
  atomic_flag_clear_explicit(&lease->gate, memory_order_release);
  return ctx;
}

my_emitter_t* my_emitter_create(const my_allocator_t* allocator) {
  my_emitter_t* e = (my_emitter_t*)my_mem_calloc(allocator, 1, sizeof(my_emitter_t));
  if (e == NULL) {
    return NULL;
  }
  e->allocator = allocator;
  e->next_id = 1;
  e->listeners = my_darray_create(allocator, 0);
  if (e->listeners == NULL) {
    my_mem_free(allocator, e);
    return NULL;
  }
  return e;
}

static void my_listener_free(my_emitter_t* e, my_listener_t* l) {
  if (l != NULL && l->destroy_ctx != NULL) {
    l->destroy_ctx(l->ctx);
  }
  if (l == NULL) {
    return;
  }
  my_mem_free(e->allocator, l->event);
  my_emitter_context_lease_unref(l->lease);
  my_mem_free(e->allocator, l);
}

static void my_listener_discard(my_emitter_t* e, my_listener_t* l) {
  if (l == NULL) {
    return;
  }
  my_mem_free(e->allocator, l->event);
  my_emitter_context_lease_unref(l->lease);
  my_mem_free(e->allocator, l);
}

static bool my_emitter_listener_id_in_use(const my_emitter_t* emitter,
                                          uint32_t id) {
  size_t i;
  size_t count = my_darray_size(emitter->listeners);
  for (i = 0; i < count; i++) {
    const my_listener_t* listener =
        (const my_listener_t*)my_darray_get(emitter->listeners, i);
    if (listener != NULL && listener->active && listener->id == id) {
      return true;
    }
  }
  return false;
}

static uint32_t my_emitter_allocate_listener_id(my_emitter_t* emitter) {
  uint32_t candidate = emitter->next_id;
  uint32_t start;

  if (candidate != 0u) {
    emitter->next_id = candidate == UINT32_MAX ? 0u : candidate + 1u;
    return candidate;
  }

  candidate = 1u;
  start = candidate;
  do {
    if (!my_emitter_listener_id_in_use(emitter, candidate)) {
      emitter->next_id = candidate == UINT32_MAX ? 0u : candidate + 1u;
      return candidate;
    }
    candidate = candidate == UINT32_MAX ? 1u : candidate + 1u;
  } while (candidate != start);

  return 0u;
}

static void my_emitter_dispose(my_emitter_t* emitter) {
  size_t i, n;
  if (emitter == NULL) {
    return;
  }
  emitter->disposing = true;
  n = my_darray_size(emitter->listeners);
  for (i = 0; i < n; i++) {
    my_listener_free(emitter,
                     (my_listener_t*)my_darray_get(emitter->listeners, i));
  }
  my_darray_destroy(emitter->listeners);
  my_mem_free(emitter->allocator, emitter);
}

void my_emitter_destroy(my_emitter_t* emitter) {
  if (emitter == NULL) {
    return;
  }
  if (emitter->destroy_requested || emitter->disposing) {
    return;
  }
  if (emitter->emitting != 0 || emitter->sweeping) {
    emitter->destroy_requested = true;
    return;
  }
  my_emitter_dispose(emitter);
}

uint32_t my_emitter_on(my_emitter_t* emitter, const char* event,
                       my_event_callback_t callback, void* ctx) {
  my_listener_t* l;
  if (emitter == NULL || event == NULL || callback == NULL ||
      emitter->destroy_requested || emitter->sweeping ||
      emitter->disposing) {
    return 0;
  }
  l = (my_listener_t*)my_mem_calloc(emitter->allocator, 1,
                                    sizeof(my_listener_t));
  if (l == NULL) {
    return 0;
  }
  l->event = my_strdup(emitter->allocator, event);
  if (l->event == NULL) {
    my_mem_free(emitter->allocator, l);
    return 0;
  }
  l->id = my_emitter_allocate_listener_id(emitter);
  if (l->id == 0u) {
    my_listener_discard(emitter, l);
    return 0;
  }
  l->callback = callback;
  l->ctx = ctx;
  l->active = true;
  if (my_darray_push(emitter->listeners, l) != MY_RET_OK) {
    my_listener_discard(emitter, l);
    return 0;
  }
  return l->id;
}

uint32_t my_emitter_on_owned(my_emitter_t* emitter, const char* event,
                             my_event_callback_t callback, void* ctx,
                             my_event_context_destroy_fn_t destroy_ctx) {
  my_listener_t* l;
  if (emitter == NULL || event == NULL || callback == NULL ||
      destroy_ctx == NULL || emitter->destroy_requested || emitter->sweeping ||
      emitter->disposing) {
    return 0;
  }
  l = (my_listener_t*)my_mem_calloc(emitter->allocator, 1, sizeof(my_listener_t));
  if (l == NULL) {
    return 0;
  }
  l->event = my_strdup(emitter->allocator, event);
  if (l->event == NULL) {
    my_mem_free(emitter->allocator, l);
    return 0;
  }
  l->id = my_emitter_allocate_listener_id(emitter);
  if (l->id == 0u) {
    my_listener_discard(emitter, l);
    return 0;
  }
  l->callback = callback;
  l->ctx = ctx;
  l->destroy_ctx = destroy_ctx;
  l->active = true;
  if (my_darray_push(emitter->listeners, l) != MY_RET_OK) {
    my_listener_discard(emitter, l);
    return 0;
  }
  return l->id;
}

uint32_t my_emitter_on_lease(my_emitter_t* emitter, const char* event,
                             my_event_callback_t callback,
                             my_emitter_context_lease_t* lease) {
  my_listener_t* l;
  if (emitter == NULL || event == NULL || callback == NULL || lease == NULL ||
      !my_emitter_context_lease_is_valid(lease) ||
      emitter->destroy_requested || emitter->sweeping || emitter->disposing) {
    return 0;
  }
  l = (my_listener_t*)my_mem_calloc(emitter->allocator, 1,
                                    sizeof(my_listener_t));
  if (l == NULL) return 0;
  l->event = my_strdup(emitter->allocator, event);
  if (l->event == NULL) {
    my_mem_free(emitter->allocator, l);
    return 0;
  }
  l->id = my_emitter_allocate_listener_id(emitter);
  if (l->id == 0u) {
    my_listener_discard(emitter, l);
    return 0;
  }
  l->lease = my_emitter_context_lease_ref(lease);
  if (l->lease == NULL) {
    my_listener_discard(emitter, l);
    return 0;
  }
  l->callback = callback;
  l->active = true;
  if (my_darray_push(emitter->listeners, l) != MY_RET_OK) {
    my_listener_discard(emitter, l);
    return 0;
  }
  return l->id;
}

/** @brief Physically remove and free all listeners marked inactive. */
static void my_emitter_sweep(my_emitter_t* emitter) {
  size_t i = 0;
  emitter->sweeping = true;
  while (i < my_darray_size(emitter->listeners)) {
    my_listener_t* l = (my_listener_t*)my_darray_get(emitter->listeners, i);
    if (!l->active) {
      my_darray_remove_at(emitter->listeners, i);
      my_listener_free(emitter, l);
    } else {
      i++;
    }
  }
  emitter->sweeping = false;
  if (emitter->destroy_requested) {
    my_emitter_dispose(emitter);
  }
}

my_ret_t my_emitter_off(my_emitter_t* emitter, uint32_t id) {
  size_t i, n;
  if (emitter == NULL || emitter->destroy_requested || emitter->sweeping ||
      emitter->disposing) {
    return MY_RET_INVALID_PARAMS;
  }
  n = my_darray_size(emitter->listeners);
  for (i = 0; i < n; i++) {
    my_listener_t* l = (my_listener_t*)my_darray_get(emitter->listeners, i);
    if (l->id == id) {
      l->active = false;
      if (emitter->emitting == 0) {
        emitter->sweeping = true;
        my_darray_remove_at(emitter->listeners, i);
        my_listener_free(emitter, l);
        emitter->sweeping = false;
        if (emitter->destroy_requested) {
          my_emitter_dispose(emitter);
        }
      }
      return MY_RET_OK;
    }
  }
  return MY_RET_NOT_FOUND;
}

my_ret_t my_emitter_emit(my_emitter_t* emitter, const char* event, void* event_data) {
  size_t i, n;
  if (emitter == NULL || event == NULL || emitter->destroy_requested ||
      emitter->sweeping || emitter->disposing) {
    return MY_RET_INVALID_PARAMS;
  }
  emitter->emitting++;
  /* n is captured up front: listeners added during this emit are skipped,
   * and removals during emit only flip active flags, so indices stay valid. */
  n = my_darray_size(emitter->listeners);
  for (i = 0; i < n; i++) {
    if (emitter->destroy_requested) {
      break;
    }
    my_listener_t* l = (my_listener_t*)my_darray_get(emitter->listeners, i);
    if (l->active && my_str_eq(l->event, event)) {
      void* ctx = l->lease != NULL
                      ? my_emitter_context_lease_context(l->lease)
                      : l->ctx;
      if (l->lease == NULL || ctx != NULL) {
        l->callback(ctx, event, event_data);
      }
    }
  }
  emitter->emitting--;
  if (emitter->emitting == 0 && emitter->destroy_requested) {
    my_emitter_dispose(emitter);
  } else if (emitter->emitting == 0) {
    my_emitter_sweep(emitter);
  }
  return MY_RET_OK;
}
