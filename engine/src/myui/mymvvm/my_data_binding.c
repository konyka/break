/**
 * @file my_data_binding.c
 * @brief Data binding: vm property <-> target property synchronization.
 *
 * Semantics:
 *  - OneWay: initial push + live push on "prop:<name>".
 *  - TwoWay: OneWay + target "changed" event writes back
 *    (convert_back, then validator; an invalid value is REJECTED: the vm
 *    keeps its value and the target is restored from the vm).
 *  - Once: a single push at bind time, no listeners.
 */
#include "mymvvm/my_data_binding.h"

#include <stdio.h>
#include <string.h>

#include "myc/my_str.h"

static void vm_event_name(const char* prop, char* buf, size_t size) {
  snprintf(buf, size, "prop:%s", prop);
}

my_ret_t my_data_binding_push(my_data_binding_t* binding) {
  my_view_model_t* vm = my_binding_context_get_view_model(binding->ctx);
  my_value_t v;
  my_ret_t ret;
  if (vm == NULL) {
    return MY_RET_OK;
  }
  if (binding->updating) {
    return MY_RET_OK;
  }
  binding->updating = true;
  my_value_init(&v, NULL);
  ret = my_view_model_get_prop(vm, binding->rule.vm_prop, &v);
  if (ret == MY_RET_OK) {
    my_value_convert(binding->converter, &v);
    ret = my_binding_target_set_prop(binding->target, binding->rule.widget_prop,
                                     &v);
  }
  my_value_reset(&v);
  binding->updating = false;
  return ret;
}

my_ret_t my_data_binding_pull(my_data_binding_t* binding) {
  my_view_model_t* vm = my_binding_context_get_view_model(binding->ctx);
  my_value_t v;
  my_ret_t ret;
  char msg[64];
  if (vm == NULL) {
    return MY_RET_OK;
  }
  if (binding->updating) {
    return MY_RET_OK;
  }
  binding->updating = true;
  my_value_init(&v, NULL);
  ret = my_binding_target_get_prop(binding->target, binding->rule.widget_prop,
                                   &v);
  if (ret == MY_RET_OK) {
    ret = my_value_convert_back(binding->converter, &v);
  }
  if (ret == MY_RET_OK &&
      !my_value_validate(binding->validator, &v, msg, sizeof(msg))) {
    /* rejected: keep the vm value, restore the target from the vm */
    my_value_reset(&v);
    binding->updating = false;
    my_data_binding_push(binding);
    return MY_RET_FAIL;
  }
  if (ret == MY_RET_OK) {
    ret = my_view_model_set_prop(vm, binding->rule.vm_prop, &v);
  }
  my_value_reset(&v);
  binding->updating = false;
  return ret;
}

static void on_vm_prop_changed(void* ctx, const char* event, void* data) {
  my_data_binding_t* binding = (my_data_binding_t*)ctx;
  (void)event;
  (void)data;
  if (binding->rule.mode != MY_BINDING_ONCE) {
    my_data_binding_push(binding);
  }
}

static void on_target_changed(void* ctx, const char* event, void* data) {
  my_data_binding_t* binding = (my_data_binding_t*)ctx;
  (void)event;
  (void)data;
  if (binding->rule.mode == MY_BINDING_TWO_WAY) {
    my_data_binding_pull(binding);
  }
}

static my_ret_t resolve_converter(my_data_binding_t* b) {
  if (b->rule.converter[0] == '\0') {
    return MY_RET_OK;
  }
  b->converter = my_value_converter_find(b->rule.converter);
  return b->converter != NULL ? MY_RET_OK : MY_RET_NOT_FOUND;
}

static my_ret_t resolve_validator(const my_allocator_t* allocator,
                                  my_data_binding_t* b) {
  if (b->rule.validator[0] == '\0') {
    return MY_RET_OK;
  }
  if (my_str_eq(b->rule.validator, "range")) {
    int min, max;
    if (sscanf(b->rule.validator_args, "%d,%d", &min, &max) != 2) {
      return MY_RET_INVALID_PARAMS;
    }
    b->validator = my_value_validator_range_create(allocator, (int32_t)min,
                                                   (int32_t)max);
    b->validator_owned = true;
    return b->validator != NULL ? MY_RET_OK : MY_RET_OOM;
  }
  b->validator = (my_value_validator_t*)my_value_validator_find(b->rule.validator);
  return b->validator != NULL ? MY_RET_OK : MY_RET_NOT_FOUND;
}

static my_ret_t subscribe_vm(my_data_binding_t* b, my_view_model_t* vm) {
  char event[MY_RULE_NAME_LEN + 8];
  if (vm == NULL || b->rule.mode == MY_BINDING_ONCE) {
    return MY_RET_OK;
  }
  vm_event_name(b->rule.vm_prop, event, sizeof(event));
  b->vm_listener_id = my_emitter_on(vm->emitter, event, on_vm_prop_changed, b);
  return b->vm_listener_id > 0 ? MY_RET_OK : MY_RET_OOM;
}

my_data_binding_t* my_data_binding_create(const my_allocator_t* allocator,
                                          my_binding_context_t* ctx,
                                          my_binding_target_t* target,
                                          const my_binding_rule_t* rule) {
  my_data_binding_t* b;
  if (ctx == NULL || target == NULL || rule == NULL) {
    return NULL;
  }
  b = (my_data_binding_t*)my_mem_calloc(allocator, 1, sizeof(my_data_binding_t));
  if (b == NULL) {
    return NULL;
  }
  b->ctx = ctx;
  b->allocator = allocator;
  b->target = target;
  b->rule = *rule;
  if (resolve_converter(b) != MY_RET_OK ||
      resolve_validator(allocator, b) != MY_RET_OK ||
      subscribe_vm(b, my_binding_context_get_view_model(ctx)) != MY_RET_OK) {
    my_data_binding_destroy(b);
    return NULL;
  }
  if (rule->mode == MY_BINDING_TWO_WAY) {
    b->target_listener_id =
        my_binding_target_on_event(target, "changed", on_target_changed, b);
    if (b->target_listener_id == 0) {
      my_data_binding_destroy(b);
      return NULL;
    }
  }
  my_data_binding_push(b); /* initial sync */
  return b;
}

void my_data_binding_destroy(my_data_binding_t* binding) {
  my_view_model_t* vm;
  if (binding == NULL) {
    return;
  }
  vm = my_binding_context_get_view_model(binding->ctx);
  if (vm != NULL && binding->vm_listener_id > 0) {
    my_emitter_off(vm->emitter, binding->vm_listener_id);
    binding->vm_listener_id = 0;
  }
  if (binding->target_listener_id > 0) {
    my_binding_target_off_event(binding->target, binding->target_listener_id);
    binding->target_listener_id = 0;
  }
  if (binding->validator_owned) {
    my_value_validator_range_destroy(binding->validator);
  }
  my_mem_free(binding->allocator, binding);
}

my_ret_t my_data_binding_rebind(my_data_binding_t* binding, my_view_model_t* vm) {
  if (binding == NULL) {
    return MY_RET_INVALID_PARAMS;
  }
  binding->vm_listener_id = 0;
  if (subscribe_vm(binding, vm) != MY_RET_OK) {
    return MY_RET_OOM;
  }
  return my_data_binding_push(binding);
}
