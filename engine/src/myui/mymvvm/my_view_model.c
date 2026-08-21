/**
 * @file my_view_model.c
 * @brief view_model base + dummy property-bag implementation.
 */
#include "mymvvm/my_view_model.h"

#include <string.h>

#include "myc/my_darray.h"
#include "myc/my_str.h"

/* ---------------- base ---------------- */

my_ret_t my_view_model_init(my_view_model_t* vm, const my_allocator_t* allocator,
                            const my_view_model_vtable_t* vtable) {
  if (vm == NULL) {
    return MY_RET_INVALID_PARAMS;
  }
  memset(vm, 0, sizeof(*vm));
  vm->base.ref_count = 1;
  vm->base.allocator = allocator;
  vm->vtable = vtable;
  vm->emitter = my_emitter_create(allocator);
  if (vm->emitter == NULL) {
    return MY_RET_OOM;
  }
  return MY_RET_OK;
}

void my_view_model_destroy(my_view_model_t* vm) {
  if (vm != NULL) {
    my_emitter_destroy(vm->emitter);
    vm->emitter = NULL;
  }
}

my_ret_t my_view_model_get_prop(my_view_model_t* vm, const char* name,
                                my_value_t* value) {
  if (vm == NULL || name == NULL || value == NULL) {
    return MY_RET_INVALID_PARAMS;
  }
  if (vm->vtable == NULL || vm->vtable->get_prop == NULL) {
    return MY_RET_NOT_SUPPORTED;
  }
  return vm->vtable->get_prop(vm, name, value);
}

my_ret_t my_view_model_set_prop(my_view_model_t* vm, const char* name,
                                const my_value_t* value) {
  if (vm == NULL || name == NULL || value == NULL) {
    return MY_RET_INVALID_PARAMS;
  }
  if (vm->vtable == NULL || vm->vtable->set_prop == NULL) {
    return MY_RET_NOT_SUPPORTED;
  }
  return vm->vtable->set_prop(vm, name, value);
}

bool my_view_model_can_exec(my_view_model_t* vm, const char* cmd,
                            const char* args) {
  if (vm == NULL || cmd == NULL || vm->vtable == NULL ||
      vm->vtable->can_exec == NULL) {
    return false;
  }
  return vm->vtable->can_exec(vm, cmd, args);
}

my_ret_t my_view_model_exec(my_view_model_t* vm, const char* cmd,
                            const char* args) {
  if (vm == NULL || cmd == NULL) {
    return MY_RET_INVALID_PARAMS;
  }
  if (vm->vtable == NULL || vm->vtable->exec == NULL) {
    return MY_RET_NOT_SUPPORTED;
  }
  return vm->vtable->exec(vm, cmd, args);
}

my_ret_t my_view_model_notify_change(my_view_model_t* vm, const char* name) {
  char event[80];
  if (vm == NULL) {
    return MY_RET_INVALID_PARAMS;
  }
  if (name == NULL) {
    return my_emitter_emit(vm->emitter, "props", NULL);
  }
  snprintf(event, sizeof(event), "prop:%s", name);
  return my_emitter_emit(vm->emitter, event, NULL);
}

/* ---------------- dummy ---------------- */

typedef struct dummy_prop_t {
  char* name;
  my_value_t value;
} dummy_prop_t;

typedef struct dummy_command_t {
  char* name;
  my_dummy_command_fn_t fn;
  void* ctx;
} dummy_command_t;

typedef struct my_view_model_dummy_t {
  my_view_model_t base;
  const my_allocator_t* allocator;
  my_darray_t* props;     /**< dummy_prop_t* */
  my_darray_t* commands;  /**< dummy_command_t* */
} my_view_model_dummy_t;

static dummy_prop_t* dummy_find_prop(my_view_model_dummy_t* d, const char* name) {
  size_t i, n = my_darray_size(d->props);
  for (i = 0; i < n; i++) {
    dummy_prop_t* p = (dummy_prop_t*)my_darray_get(d->props, i);
    if (my_str_eq(p->name, name)) {
      return p;
    }
  }
  return NULL;
}

static my_ret_t dummy_get_prop(my_view_model_t* vm, const char* name,
                               my_value_t* value) {
  my_view_model_dummy_t* d = (my_view_model_dummy_t*)vm;
  dummy_prop_t* p = dummy_find_prop(d, name);
  if (p == NULL) {
    return MY_RET_NOT_FOUND;
  }
  return my_value_copy(value, &p->value);
}

static my_ret_t dummy_set_prop(my_view_model_t* vm, const char* name,
                               const my_value_t* value) {
  my_view_model_dummy_t* d = (my_view_model_dummy_t*)vm;
  dummy_prop_t* p = dummy_find_prop(d, name);
  if (p == NULL) {
    p = (dummy_prop_t*)my_mem_calloc(d->allocator, 1, sizeof(dummy_prop_t));
    if (p == NULL) {
      return MY_RET_OOM;
    }
    p->name = my_strdup(d->allocator, name);
    my_value_init(&p->value, d->allocator);
    if (p->name == NULL || my_darray_push(d->props, p) != MY_RET_OK) {
      my_mem_free(d->allocator, p->name);
      my_mem_free(d->allocator, p);
      return MY_RET_OOM;
    }
  }
  my_value_reset(&p->value);
  my_value_init(&p->value, d->allocator);
  if (my_value_copy(&p->value, value) != MY_RET_OK) {
    return MY_RET_OOM;
  }
  return my_view_model_notify_change(vm, name);
}

static bool dummy_can_exec(my_view_model_t* vm, const char* cmd,
                           const char* args) {
  my_view_model_dummy_t* d = (my_view_model_dummy_t*)vm;
  size_t i, n = my_darray_size(d->commands);
  (void)args;
  for (i = 0; i < n; i++) {
    dummy_command_t* c = (dummy_command_t*)my_darray_get(d->commands, i);
    if (my_str_eq(c->name, cmd)) {
      return true;
    }
  }
  return false;
}

static my_ret_t dummy_exec(my_view_model_t* vm, const char* cmd,
                           const char* args) {
  my_view_model_dummy_t* d = (my_view_model_dummy_t*)vm;
  size_t i, n = my_darray_size(d->commands);
  for (i = 0; i < n; i++) {
    dummy_command_t* c = (dummy_command_t*)my_darray_get(d->commands, i);
    if (my_str_eq(c->name, cmd)) {
      return c->fn(c->ctx, args);
    }
  }
  return MY_RET_NOT_FOUND;
}

static const my_view_model_vtable_t s_dummy_vtable = {dummy_get_prop,
                                                      dummy_set_prop,
                                                      dummy_can_exec,
                                                      dummy_exec};

static void dummy_destroy_chain(my_object_t* obj) {
  my_view_model_dummy_t* d = (my_view_model_dummy_t*)obj;
  size_t i, n = my_darray_size(d->props);
  for (i = 0; i < n; i++) {
    dummy_prop_t* p = (dummy_prop_t*)my_darray_get(d->props, i);
    my_value_reset(&p->value);
    my_mem_free(d->allocator, p->name);
    my_mem_free(d->allocator, p);
  }
  my_darray_destroy(d->props);
  n = my_darray_size(d->commands);
  for (i = 0; i < n; i++) {
    dummy_command_t* c = (dummy_command_t*)my_darray_get(d->commands, i);
    my_mem_free(d->allocator, c->name);
    my_mem_free(d->allocator, c);
  }
  my_darray_destroy(d->commands);
  my_view_model_destroy((my_view_model_t*)d);
  my_object_destroy(obj);
}

my_view_model_t* my_view_model_dummy_create(const my_allocator_t* allocator) {
  my_view_model_dummy_t* d =
      (my_view_model_dummy_t*)my_mem_calloc(allocator, 1, sizeof(my_view_model_dummy_t));
  if (d == NULL) {
    return NULL;
  }
  if (my_view_model_init((my_view_model_t*)d, allocator, &s_dummy_vtable) !=
      MY_RET_OK) {
    my_mem_free(allocator, d);
    return NULL;
  }
  ((my_object_t*)d)->destroy = dummy_destroy_chain;
  d->allocator = allocator;
  d->props = my_darray_create(allocator, 0);
  d->commands = my_darray_create(allocator, 0);
  if (d->props == NULL || d->commands == NULL) {
    my_object_unref((my_object_t*)d);
    return NULL;
  }
  return (my_view_model_t*)d;
}

my_ret_t my_view_model_dummy_add_command(my_view_model_t* vm, const char* name,
                                         my_dummy_command_fn_t fn, void* ctx) {
  my_view_model_dummy_t* d = (my_view_model_dummy_t*)vm;
  dummy_command_t* c;
  if (d == NULL || name == NULL || fn == NULL ||
      d->base.vtable != &s_dummy_vtable) {
    return MY_RET_INVALID_PARAMS;
  }
  c = (dummy_command_t*)my_mem_calloc(d->allocator, 1, sizeof(dummy_command_t));
  if (c == NULL) {
    return MY_RET_OOM;
  }
  c->name = my_strdup(d->allocator, name);
  c->fn = fn;
  c->ctx = ctx;
  if (c->name == NULL || my_darray_push(d->commands, c) != MY_RET_OK) {
    my_mem_free(d->allocator, c != NULL ? c->name : NULL);
    my_mem_free(d->allocator, c);
    return MY_RET_OOM;
  }
  return MY_RET_OK;
}
