/**
 * @file my_emitter.c
 * @brief Event emitter implementation (mark-and-sweep removal).
 */
#include "myc/my_emitter.h"

#include "myc/my_darray.h"
#include "myc/my_str.h"

typedef struct my_listener_t {
  uint32_t id;
  char* event;
  my_event_callback_t callback;
  void* ctx;
  bool active; /**< false after my_emitter_off(), swept after the current emit */
} my_listener_t;

struct my_emitter_t {
  const my_allocator_t* allocator;
  my_darray_t* listeners; /**< my_listener_t* elements */
  uint32_t next_id;
  int emitting; /**< > 0 while an emit is in progress */
};

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
  my_mem_free(e->allocator, l->event);
  my_mem_free(e->allocator, l);
}

void my_emitter_destroy(my_emitter_t* emitter) {
  size_t i, n;
  if (emitter == NULL) {
    return;
  }
  n = my_darray_size(emitter->listeners);
  for (i = 0; i < n; i++) {
    my_listener_free(emitter, (my_listener_t*)my_darray_get(emitter->listeners, i));
  }
  my_darray_destroy(emitter->listeners);
  my_mem_free(emitter->allocator, emitter);
}

uint32_t my_emitter_on(my_emitter_t* emitter, const char* event,
                       my_event_callback_t callback, void* ctx) {
  my_listener_t* l;
  if (emitter == NULL || event == NULL || callback == NULL) {
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
  l->id = emitter->next_id++;
  l->callback = callback;
  l->ctx = ctx;
  l->active = true;
  if (my_darray_push(emitter->listeners, l) != MY_RET_OK) {
    my_listener_free(emitter, l);
    return 0;
  }
  return l->id;
}

/** @brief Physically remove and free all listeners marked inactive. */
static void my_emitter_sweep(my_emitter_t* emitter) {
  size_t i = 0;
  while (i < my_darray_size(emitter->listeners)) {
    my_listener_t* l = (my_listener_t*)my_darray_get(emitter->listeners, i);
    if (!l->active) {
      my_darray_remove_at(emitter->listeners, i);
      my_listener_free(emitter, l);
    } else {
      i++;
    }
  }
}

my_ret_t my_emitter_off(my_emitter_t* emitter, uint32_t id) {
  size_t i, n;
  if (emitter == NULL) {
    return MY_RET_INVALID_PARAMS;
  }
  n = my_darray_size(emitter->listeners);
  for (i = 0; i < n; i++) {
    my_listener_t* l = (my_listener_t*)my_darray_get(emitter->listeners, i);
    if (l->id == id) {
      l->active = false;
      if (emitter->emitting == 0) {
        my_darray_remove_at(emitter->listeners, i);
        my_listener_free(emitter, l);
      }
      return MY_RET_OK;
    }
  }
  return MY_RET_NOT_FOUND;
}

my_ret_t my_emitter_emit(my_emitter_t* emitter, const char* event, void* event_data) {
  size_t i, n;
  if (emitter == NULL || event == NULL) {
    return MY_RET_INVALID_PARAMS;
  }
  emitter->emitting++;
  /* n is captured up front: listeners added during this emit are skipped,
   * and removals during emit only flip active flags, so indices stay valid. */
  n = my_darray_size(emitter->listeners);
  for (i = 0; i < n; i++) {
    my_listener_t* l = (my_listener_t*)my_darray_get(emitter->listeners, i);
    if (l->active && my_str_eq(l->event, event)) {
      l->callback(l->ctx, event, event_data);
    }
  }
  emitter->emitting--;
  if (emitter->emitting == 0) {
    my_emitter_sweep(emitter);
  }
  return MY_RET_OK;
}
