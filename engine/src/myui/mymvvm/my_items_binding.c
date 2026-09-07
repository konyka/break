/**
 * @file my_items_binding.c
 * @brief Items binding: array vm -> target list rebuild.
 */
#include "mymvvm/my_items_binding.h"

#include <string.h>

static void on_items_changed(void* ctx, const char* event, void* data);
static void on_array_prop_changed(void* ctx, const char* event, void* data);
static void on_vm_props_changed(void* ctx, const char* event, void* data);

/** @brief Resolve the array vm from the bound vm property. */
static my_view_model_array_t* resolve_array(my_items_binding_t* b,
                                            bool* valid) {
  my_view_model_t* vm = my_binding_context_get_view_model(b->ctx);
  my_value_t v;
  my_view_model_array_t* arr = NULL;
  if (valid != NULL) {
    *valid = true;
  }
  if (vm == NULL) {
    return NULL;
  }
  my_value_init(&v, NULL);
  if (my_view_model_get_prop(vm, b->rule.vm_prop, &v) == MY_RET_OK) {
    if (v.type == MY_VALUE_POINTER) {
      arr = my_view_model_array_ref(
          (my_view_model_array_t*)my_value_get_pointer(&v));
    } else if (v.type != MY_VALUE_NONE && valid != NULL) {
      *valid = false;
    }
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
  if (b == NULL || b->target == NULL ||
      b->target->vtable == NULL ||
      b->target->vtable->rebuild_items == NULL) {
    return MY_RET_NOT_SUPPORTED;
  }
  count = b->array != NULL ? my_view_model_array_get_count(b->array) : 0;
  b->last_error = b->target->vtable->rebuild_items(
      b->target, b->rule.item_template, count, props_from_child, b);
  return b->last_error;
}

my_ret_t my_items_binding_rebind(my_items_binding_t* b) {
  my_view_model_t* vm;
  bool valid;
  if (b == NULL) {
    return MY_RET_INVALID_PARAMS;
  }
  if (b->array != NULL && b->array_listener_id > 0) {
    my_emitter_off(b->array->emitter, b->array_listener_id);
    b->array_listener_id = 0;
  }
  if (b->array != NULL) {
    my_view_model_array_unref(b->array);
    b->array = NULL;
  }
  vm = my_binding_context_get_view_model(b->ctx);
  if (b->vm_listener_id > 0 && vm != NULL) {
    my_emitter_off(vm->emitter, b->vm_listener_id);
    b->vm_listener_id = 0;
  }
  if (b->vm_all_listener_id > 0 && vm != NULL) {
    my_emitter_off(vm->emitter, b->vm_all_listener_id);
    b->vm_all_listener_id = 0;
  }
  b->array = resolve_array(b, &valid);
  if (!valid) {
    return MY_RET_INVALID_PARAMS;
  }
  if (b->array != NULL) {
    b->array_listener_id =
        my_emitter_on(b->array->emitter, "items_changed", on_items_changed, b);
    if (b->array_listener_id == 0) {
      my_view_model_array_unref(b->array);
      b->array = NULL;
      return MY_RET_OOM;
    }
  }
  if (vm != NULL) {
    char event[MY_RULE_NAME_LEN + 8];
    snprintf(event, sizeof(event), "prop:%s", b->rule.vm_prop);
    b->vm_listener_id = my_emitter_on(vm->emitter, event, on_array_prop_changed, b);
    if (b->vm_listener_id == 0) {
      if (b->array_listener_id > 0) {
        my_emitter_off(b->array->emitter, b->array_listener_id);
        b->array_listener_id = 0;
      }
      my_view_model_array_unref(b->array);
      b->array = NULL;
      return MY_RET_OOM;
    }
    b->vm_all_listener_id =
        my_emitter_on(vm->emitter, "props", on_vm_props_changed, b);
    if (b->vm_all_listener_id == 0) {
      my_emitter_off(vm->emitter, b->vm_listener_id);
      b->vm_listener_id = 0;
      if (b->array_listener_id > 0) {
        my_emitter_off(b->array->emitter, b->array_listener_id);
        b->array_listener_id = 0;
      }
      my_view_model_array_unref(b->array);
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

static void on_vm_props_changed(void* ctx, const char* event, void* data) {
  on_array_prop_changed(ctx, event, data);
}

static void on_array_prop_changed(void* ctx, const char* event, void* data) {
  my_items_binding_t* b = (my_items_binding_t*)ctx;
  my_view_model_array_t* old_array = b->array;
  uint32_t old_listener_id = b->array_listener_id;
  my_view_model_array_t* candidate;
  uint32_t candidate_listener_id = 0;
  bool valid;
  my_ret_t ret;
  (void)event;
  (void)data;
  candidate = resolve_array(b, &valid);
  if (!valid) {
    b->last_error = MY_RET_INVALID_PARAMS;
    return;
  }
  if (candidate == old_array) {
    my_view_model_array_unref(candidate);
    return;
  }
  if (candidate != NULL) {
    candidate_listener_id = my_emitter_on(
        candidate->emitter, "items_changed", on_items_changed, b);
    if (candidate_listener_id == 0) {
      my_view_model_array_unref(candidate);
      b->last_error = MY_RET_OOM;
      return;
    }
  }
  b->array = candidate;
  b->array_listener_id = candidate_listener_id;
  ret = my_items_binding_rebuild(b);
  if (ret != MY_RET_OK) {
    if (candidate != NULL && candidate_listener_id > 0) {
      my_emitter_off(candidate->emitter, candidate_listener_id);
    }
    if (candidate != NULL) {
      my_view_model_array_unref(candidate);
    }
    b->array = old_array;
    b->array_listener_id = old_listener_id;
    b->last_error = ret;
    return;
  }
  if (old_array != NULL && old_listener_id > 0) {
    my_emitter_off(old_array->emitter, old_listener_id);
  }
  if (old_array != NULL) {
    my_view_model_array_unref(old_array);
  }
}

my_items_binding_t* my_items_binding_create(const my_allocator_t* allocator,
                                            my_binding_context_t* ctx,
                                            my_binding_target_t* target,
                                            const my_binding_rule_t* rule,
                                            my_ret_t* error) {
  my_items_binding_t* b;
  my_ret_t ret;
  if (error != NULL) {
    *error = MY_RET_FAIL;
  }
  if (ctx == NULL || target == NULL || rule == NULL ||
      target->vtable == NULL ||
      target->vtable->rebuild_items == NULL) {
    if (error != NULL) {
      *error = MY_RET_NOT_SUPPORTED;
    }
    return NULL;
  }
  b = (my_items_binding_t*)my_mem_calloc(allocator, 1, sizeof(my_items_binding_t));
  if (b == NULL) {
    if (error != NULL) {
      *error = MY_RET_OOM;
    }
    return NULL;
  }
  b->ctx = ctx;
  b->allocator = allocator;
  b->target = target;
  b->rule = *rule;
  ret = my_items_binding_rebind(b);
  if (ret != MY_RET_OK) {
    if (error != NULL) {
      *error = ret;
    }
    my_items_binding_destroy(b);
    return NULL;
  }
  if (error != NULL) {
    *error = MY_RET_OK;
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
  if (b->array != NULL) {
    my_view_model_array_unref(b->array);
  }
  vm = my_binding_context_get_view_model(b->ctx);
  if (vm != NULL && b->vm_listener_id > 0) {
    my_emitter_off(vm->emitter, b->vm_listener_id);
  }
  if (vm != NULL && b->vm_all_listener_id > 0) {
    my_emitter_off(vm->emitter, b->vm_all_listener_id);
  }
  my_mem_free(b->allocator, b);
}
