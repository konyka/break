/**
 * @file my_condition_binding.c
 * @brief Condition binding: pushes a (possibly negated) vm bool prop.
 */
#include "mymvvm/my_condition_binding.h"

#include <stdio.h>

my_ret_t my_condition_binding_eval(my_condition_binding_t* b) {
  my_view_model_t* vm = my_binding_context_get_view_model(b->ctx);
  my_value_t v;
  my_value_t out;
  bool cond = false;
  if (vm == NULL) {
    return MY_RET_OK;
  }
  my_value_init(&v, NULL);
  if (my_view_model_get_prop(vm, b->rule.vm_prop, &v) == MY_RET_OK) {
    if (v.type == MY_VALUE_BOOL) {
      cond = my_value_get_bool(&v);
    } else if (v.type == MY_VALUE_INT32) {
      cond = my_value_get_int32(&v) != 0;
    } else if (v.type == MY_VALUE_STR) {
      const char* s = my_value_get_str(&v);
      cond = s != NULL && *s != '\0';
    }
  }
  my_value_reset(&v);
  if (b->rule.condition_negate) {
    cond = !cond;
  }
  my_value_init(&out, NULL);
  my_value_set_bool(&out, cond);
  my_binding_target_set_prop(b->target, b->rule.widget_prop, &out);
  my_value_reset(&out);
  return MY_RET_OK;
}

static void on_prop_changed(void* ctx, const char* event, void* data) {
  (void)event;
  (void)data;
  my_condition_binding_eval((my_condition_binding_t*)ctx);
}

my_ret_t my_condition_binding_rebind(my_condition_binding_t* b) {
  my_view_model_t* vm;
  char event[MY_RULE_NAME_LEN + 8];
  if (b == NULL) {
    return MY_RET_INVALID_PARAMS;
  }
  vm = my_binding_context_get_view_model(b->ctx);
  if (vm != NULL) {
    snprintf(event, sizeof(event), "prop:%s", b->rule.vm_prop);
    b->vm_listener_id = my_emitter_on(vm->emitter, event, on_prop_changed, b);
    if (b->vm_listener_id == 0) {
      return MY_RET_OOM;
    }
  }
  return my_condition_binding_eval(b);
}

my_condition_binding_t* my_condition_binding_create(
    const my_allocator_t* allocator, my_binding_context_t* ctx,
    my_binding_target_t* target, const my_binding_rule_t* rule) {
  my_condition_binding_t* b;
  if (ctx == NULL || target == NULL || rule == NULL) {
    return NULL;
  }
  b = (my_condition_binding_t*)my_mem_calloc(allocator, 1,
                                             sizeof(my_condition_binding_t));
  if (b == NULL) {
    return NULL;
  }
  b->ctx = ctx;
  b->allocator = allocator;
  b->target = target;
  b->rule = *rule;
  if (my_condition_binding_rebind(b) != MY_RET_OK) {
    my_condition_binding_destroy(b);
    return NULL;
  }
  return b;
}

void my_condition_binding_destroy(my_condition_binding_t* b) {
  my_view_model_t* vm;
  if (b == NULL) {
    return;
  }
  vm = my_binding_context_get_view_model(b->ctx);
  if (vm != NULL && b->vm_listener_id > 0) {
    my_emitter_off(vm->emitter, b->vm_listener_id);
  }
  my_mem_free(b->allocator, b);
}
