/**
 * @file my_items_binding.c
 * @brief Items binding: array vm -> target list rebuild.
 */
#include "mymvvm/my_items_binding.h"

#include <string.h>

static void on_items_changed(void* ctx, const char* event, void* data);
static void on_array_prop_changed(void* ctx, const char* event, void* data);

/** @brief Resolve the array vm from the bound vm property. */
static my_view_model_array_t* resolve_array(my_items_binding_t* b) {
  my_view_model_t* vm = my_binding_context_get_view_model(b->ctx);
  my_value_t v;
  my_view_model_array_t* arr = NULL;
  if (vm == NULL) {
    return NULL;
  }
  my_value_init(&v, NULL);
  if (my_view_model_get_prop(vm, b->rule.vm_prop, &v) == MY_RET_OK &&
      v.type == MY_VALUE_POINTER) {
    arr = (my_view_model_array_t*)my_value_get_pointer(&v);
  }
  my_value_reset(&v);
  return arr;
}

static void props_from_child(void* ctx, size_t index, const char* key,
                             my_value_t* value) {
  my_items_binding_t* b = (my_items_binding_t*)ctx;
  my_view_model_t* child;
  if (b->array == NULL) {
    return;
  }
  child = my_view_model_array_get_item(b->array, index);
  if (child != NULL) {
    my_view_model_get_prop(child, key, value);
  }
}

my_ret_t my_items_binding_rebuild(my_items_binding_t* b) {
  size_t count;
  if (b->array == NULL || b->target->vtable->rebuild_items == NULL) {
    return MY_RET_OK;
  }
  count = my_view_model_array_get_count(b->array);
  return b->target->vtable->rebuild_items(b->target, b->rule.item_template,
                                          count, props_from_child, b);
}

my_ret_t my_items_binding_rebind(my_items_binding_t* b) {
  my_view_model_t* vm;
  if (b == NULL) {
    return MY_RET_INVALID_PARAMS;
  }
  b->array = resolve_array(b);
  if (b->array != NULL) {
    b->array_listener_id =
        my_emitter_on(b->array->emitter, "items_changed", on_items_changed, b);
    if (b->array_listener_id == 0) {
      b->array = NULL;
      return MY_RET_OOM;
    }
  }
  vm = my_binding_context_get_view_model(b->ctx);
  if (vm != NULL) {
    char event[MY_RULE_NAME_LEN + 8];
    snprintf(event, sizeof(event), "prop:%s", b->rule.vm_prop);
    b->vm_listener_id = my_emitter_on(vm->emitter, event, on_array_prop_changed, b);
    if (b->vm_listener_id == 0) {
      if (b->array_listener_id > 0) {
        my_emitter_off(b->array->emitter, b->array_listener_id);
        b->array_listener_id = 0;
      }
      b->array = NULL;
      return MY_RET_OOM;
    }
  }
  return my_items_binding_rebuild(b);
}

static void on_items_changed(void* ctx, const char* event, void* data) {
  (void)event;
  (void)data;
  my_items_binding_rebuild((my_items_binding_t*)ctx);
}

static void on_array_prop_changed(void* ctx, const char* event, void* data) {
  my_items_binding_t* b = (my_items_binding_t*)ctx;
  (void)event;
  (void)data;
  /* the array object itself was swapped: re-resolve and re-subscribe */
  if (b->array != NULL && b->array_listener_id > 0) {
    my_emitter_off(b->array->emitter, b->array_listener_id);
    b->array_listener_id = 0;
  }
  b->array = resolve_array(b);
  if (b->array != NULL) {
    b->array_listener_id =
        my_emitter_on(b->array->emitter, "items_changed", on_items_changed, b);
  }
  my_items_binding_rebuild(b);
}

my_items_binding_t* my_items_binding_create(const my_allocator_t* allocator,
                                            my_binding_context_t* ctx,
                                            my_binding_target_t* target,
                                            const my_binding_rule_t* rule) {
  my_items_binding_t* b;
  if (ctx == NULL || target == NULL || rule == NULL ||
      target->vtable->rebuild_items == NULL) {
    return NULL;
  }
  b = (my_items_binding_t*)my_mem_calloc(allocator, 1, sizeof(my_items_binding_t));
  if (b == NULL) {
    return NULL;
  }
  b->ctx = ctx;
  b->allocator = allocator;
  b->target = target;
  b->rule = *rule;
  if (my_items_binding_rebind(b) != MY_RET_OK) {
    my_items_binding_destroy(b);
    return NULL;
  }
  return b;
}

void my_items_binding_destroy(my_items_binding_t* b) {
  my_view_model_t* vm;
  if (b == NULL) {
    return;
  }
  if (b->array != NULL && b->array_listener_id > 0) {
    my_emitter_off(b->array->emitter, b->array_listener_id);
  }
  vm = my_binding_context_get_view_model(b->ctx);
  if (vm != NULL && b->vm_listener_id > 0) {
    my_emitter_off(vm->emitter, b->vm_listener_id);
  }
  my_mem_free(b->allocator, b);
}
