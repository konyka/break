/**
 * @file my_binding_context.c
 * @brief Binding context: rule application + view model lifecycle.
 */
#include "mymvvm/my_binding_context.h"

#include "myc/my_darray.h"
#include "mymvvm/my_command_binding.h"
#include "mymvvm/my_condition_binding.h"
#include "mymvvm/my_data_binding.h"
#include "mymvvm/my_items_binding.h"

/** @brief Tagged union of binding kinds held by the context. */
typedef struct binding_entry_t {
  my_binding_rule_type_t kind;
  union binding_ptr_t {
    my_data_binding_t* data;
    my_command_binding_t* command;
    my_items_binding_t* items;
    my_condition_binding_t* condition;
    void* ptr;
  } u;
} binding_entry_t;

struct my_binding_context_t {
  const my_allocator_t* allocator;
  my_view_model_t* vm;     /**< owned reference */
  my_darray_t* bindings;   /**< binding_entry_t* */
};

my_binding_context_t* my_binding_context_create(const my_allocator_t* allocator,
                                                my_view_model_t* vm) {
  my_binding_context_t* ctx =
      (my_binding_context_t*)my_mem_calloc(allocator, 1,
                                           sizeof(my_binding_context_t));
  if (ctx == NULL) {
    return NULL;
  }
  ctx->allocator = allocator;
  ctx->vm = my_view_model_ref(vm);
  ctx->bindings = my_darray_create(allocator, 0);
  if (ctx->bindings == NULL) {
    my_view_model_unref(ctx->vm);
    my_mem_free(allocator, ctx);
    return NULL;
  }
  return ctx;
}

static void entry_destroy(my_binding_context_t* ctx, binding_entry_t* e) {
  switch (e->kind) {
    case MY_RULE_COMMAND:
      my_command_binding_destroy(e->u.command);
      break;
    case MY_RULE_ITEMS:
      my_items_binding_destroy(e->u.items);
      break;
    case MY_RULE_CONDITION:
      my_condition_binding_destroy(e->u.condition);
      break;
    default:
      my_data_binding_destroy(e->u.data);
      break;
  }
  my_mem_free(ctx->allocator, e);
}

void my_binding_context_destroy(my_binding_context_t* ctx) {
  size_t i, n;
  if (ctx == NULL) {
    return;
  }
  n = my_darray_size(ctx->bindings);
  for (i = 0; i < n; i++) {
    entry_destroy(ctx, (binding_entry_t*)my_darray_get(ctx->bindings, i));
  }
  my_darray_destroy(ctx->bindings);
  my_view_model_unref(ctx->vm);
  my_mem_free(ctx->allocator, ctx);
}

my_view_model_t* my_binding_context_get_view_model(my_binding_context_t* ctx) {
  return ctx != NULL ? ctx->vm : NULL;
}

static void detach_bindings(my_binding_context_t* ctx) {
  size_t i, n;
  n = my_darray_size(ctx->bindings);
  for (i = 0; i < n; i++) {
    binding_entry_t* e = (binding_entry_t*)my_darray_get(ctx->bindings, i);
    if (e->kind == MY_RULE_DATA && e->u.data->vm_listener_id > 0 &&
        ctx->vm != NULL) {
      my_emitter_off(ctx->vm->emitter, e->u.data->vm_listener_id);
      e->u.data->vm_listener_id = 0;
      if (e->u.data->vm_all_listener_id > 0) {
        my_emitter_off(ctx->vm->emitter, e->u.data->vm_all_listener_id);
        e->u.data->vm_all_listener_id = 0;
      }
    } else if (e->kind == MY_RULE_ITEMS) {
      if (e->u.items->array != NULL && e->u.items->array_listener_id > 0) {
        my_emitter_off(e->u.items->array->emitter,
                       e->u.items->array_listener_id);
        e->u.items->array_listener_id = 0;
      }
      if (e->u.items->array != NULL) {
        my_view_model_array_unref(e->u.items->array);
        e->u.items->array = NULL;
      }
      if (e->u.items->vm_listener_id > 0 && ctx->vm != NULL) {
        my_emitter_off(ctx->vm->emitter, e->u.items->vm_listener_id);
        e->u.items->vm_listener_id = 0;
      }
      if (e->u.items->vm_all_listener_id > 0 && ctx->vm != NULL) {
        my_emitter_off(ctx->vm->emitter, e->u.items->vm_all_listener_id);
        e->u.items->vm_all_listener_id = 0;
      }
    } else if (e->kind == MY_RULE_CONDITION &&
               e->u.condition->vm_listener_id > 0 && ctx->vm != NULL) {
      my_emitter_off(ctx->vm->emitter, e->u.condition->vm_listener_id);
      e->u.condition->vm_listener_id = 0;
      if (e->u.condition->vm_all_listener_id > 0) {
        my_emitter_off(ctx->vm->emitter, e->u.condition->vm_all_listener_id);
        e->u.condition->vm_all_listener_id = 0;
      }
    }
  }
}

static my_ret_t rebind_bindings(my_binding_context_t* ctx) {
  size_t i, n;
  my_ret_t ret = MY_RET_OK;
  n = my_darray_size(ctx->bindings);
  for (i = 0; i < n; i++) {
    binding_entry_t* e = (binding_entry_t*)my_darray_get(ctx->bindings, i);
    my_ret_t current = MY_RET_OK;
    if (e->kind == MY_RULE_DATA) {
      current = my_data_binding_rebind(e->u.data, ctx->vm);
    } else if (e->kind == MY_RULE_ITEMS) {
      current = my_items_binding_rebind(e->u.items);
      if (current == MY_RET_OK) {
        current = e->u.items->last_error;
      }
    } else if (e->kind == MY_RULE_CONDITION) {
      current = my_condition_binding_rebind(e->u.condition);
    }
    if (current != MY_RET_OK && ret == MY_RET_OK) {
      ret = current;
    }
  }
  return ret;
}

my_ret_t my_binding_context_set_view_model(my_binding_context_t* ctx,
                                           my_view_model_t* vm) {
  my_view_model_t* old_vm;
  my_ret_t ret;
  if (ctx == NULL) {
    return MY_RET_INVALID_PARAMS;
  }
  old_vm = ctx->vm;
  /* Keep the old reference until all bindings accept the new VM. */
  detach_bindings(ctx);
  ctx->vm = my_view_model_ref(vm);
  ret = rebind_bindings(ctx);
  if (ret != MY_RET_OK) {
    detach_bindings(ctx);
    my_view_model_unref(ctx->vm);
    ctx->vm = old_vm;
    (void)rebind_bindings(ctx);
    return ret;
  }
  my_view_model_unref(old_vm);
  return MY_RET_OK;
}

my_ret_t my_binding_context_bind(my_binding_context_t* ctx,
                                 my_binding_target_t* target,
                                 const char* rule_str) {
  my_binding_rule_t rule;
  binding_entry_t* e;
  my_ret_t ret;
  if (ctx == NULL || target == NULL || rule_str == NULL) {
    return MY_RET_INVALID_PARAMS;
  }
  ret = my_binding_rule_parse(rule_str, &rule);
  if (ret != MY_RET_OK) {
    return ret;
  }
  e = (binding_entry_t*)my_mem_calloc(ctx->allocator, 1, sizeof(binding_entry_t));
  if (e == NULL) {
    return MY_RET_OOM;
  }
  if (rule.type == MY_RULE_COMMAND) {
    e->kind = MY_RULE_COMMAND;
    e->u.command =
        my_command_binding_create(ctx->allocator, ctx, target, &rule);
    if (e->u.command == NULL) {
      my_mem_free(ctx->allocator, e);
      return MY_RET_FAIL;
    }
  } else if (rule.type == MY_RULE_ITEMS) {
    my_ret_t items_error = MY_RET_FAIL;
    e->kind = MY_RULE_ITEMS;
    e->u.items = my_items_binding_create(ctx->allocator, ctx, target, &rule,
                                         &items_error);
    if (e->u.items == NULL) {
      my_mem_free(ctx->allocator, e);
      return items_error;
    }
  } else if (rule.type == MY_RULE_CONDITION) {
    e->kind = MY_RULE_CONDITION;
    e->u.condition =
        my_condition_binding_create(ctx->allocator, ctx, target, &rule);
    if (e->u.condition == NULL) {
      my_mem_free(ctx->allocator, e);
      return MY_RET_FAIL;
    }
  } else {
    e->kind = MY_RULE_DATA;
    e->u.data = my_data_binding_create(ctx->allocator, ctx, target, &rule);
    if (e->u.data == NULL) {
      my_mem_free(ctx->allocator, e);
      return MY_RET_FAIL;
    }
  }
  if (my_darray_push(ctx->bindings, e) != MY_RET_OK) {
    entry_destroy(ctx, e);
    return MY_RET_OOM;
  }
  return MY_RET_OK;
}

my_ret_t my_binding_context_update_to_view(my_binding_context_t* ctx) {
  size_t i, n;
  if (ctx == NULL) {
    return MY_RET_INVALID_PARAMS;
  }
  n = my_darray_size(ctx->bindings);
  for (i = 0; i < n; i++) {
    binding_entry_t* e = (binding_entry_t*)my_darray_get(ctx->bindings, i);
    if (e->kind == MY_RULE_DATA) {
      my_data_binding_push(e->u.data);
    }
  }
  return MY_RET_OK;
}

my_ret_t my_binding_context_update_to_vm(my_binding_context_t* ctx) {
  size_t i, n;
  if (ctx == NULL) {
    return MY_RET_INVALID_PARAMS;
  }
  n = my_darray_size(ctx->bindings);
  for (i = 0; i < n; i++) {
    binding_entry_t* e = (binding_entry_t*)my_darray_get(ctx->bindings, i);
    if (e->kind == MY_RULE_DATA &&
        e->u.data->rule.mode == MY_BINDING_TWO_WAY) {
      my_data_binding_pull(e->u.data);
    }
  }
  return MY_RET_OK;
}
