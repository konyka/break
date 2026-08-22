/**
 * @file my_view_model.h
 * @brief MVVM view model: properties + commands + change notification.
 *
 * Contract (implemented by app code, or my_view_model_dummy for tests):
 *  - get_prop/set_prop: named properties as my_value_t;
 *  - can_exec/exec: named commands with an optional args string;
 *  - after a property changes the model calls
 *    my_view_model_notify_change(vm, "name") which emits "prop:<name>"
 *    (or "props" for a bulk change when name is NULL) on the embedded
 *    emitter. Binding layers listen to these.
 *
 * Subclassing: embed my_view_model_t first, call my_view_model_init in
 * the factory, override base.destroy to free subclass data and then call
 * my_view_model_destroy() + my_object_destroy() (same chain convention
 * as my_widget).
 */
#ifndef MY_VIEW_MODEL_H
#define MY_VIEW_MODEL_H

#include "myc/my_emitter.h"
#include "myc/my_object.h"
#include "myc/my_value.h"

typedef struct my_view_model_t my_view_model_t;

/** @brief view_model vtable; can_exec/exec may be NULL (no commands). */
typedef struct my_view_model_vtable_t {
  my_ret_t (*get_prop)(my_view_model_t* vm, const char* name, my_value_t* value);
  my_ret_t (*set_prop)(my_view_model_t* vm, const char* name,
                       const my_value_t* value);
  bool (*can_exec)(my_view_model_t* vm, const char* cmd, const char* args);
  my_ret_t (*exec)(my_view_model_t* vm, const char* cmd, const char* args);
} my_view_model_vtable_t;

/** @brief view_model base "class". */
struct my_view_model_t {
  my_object_t base;                 /**< ref counting + destroy chain */
  const my_view_model_vtable_t* vtable;
  my_emitter_t* emitter;            /**< "prop:<name>" / "props" events */
};

/** @brief Initialize an already-allocated view model (subclass factories). */
my_ret_t my_view_model_init(my_view_model_t* vm, const my_allocator_t* allocator,
                            const my_view_model_vtable_t* vtable);

/** @brief Base cleanup for the destroy chain (frees the emitter). */
void my_view_model_destroy(my_view_model_t* vm);

static inline my_view_model_t* my_view_model_ref(my_view_model_t* vm) {
  return vm != NULL ? (my_view_model_t*)my_object_ref((my_object_t*)vm) : NULL;
}

static inline void my_view_model_unref(my_view_model_t* vm) {
  if (vm != NULL) {
    my_object_unref((my_object_t*)vm);
  }
}

my_ret_t my_view_model_get_prop(my_view_model_t* vm, const char* name,
                                my_value_t* value);
my_ret_t my_view_model_set_prop(my_view_model_t* vm, const char* name,
                                const my_value_t* value);
bool my_view_model_can_exec(my_view_model_t* vm, const char* cmd,
                            const char* args);
my_ret_t my_view_model_exec(my_view_model_t* vm, const char* cmd,
                            const char* args);

/**
 * @brief Notify property change: emits "prop:<name>"; NULL name emits
 * "props" (bulk change). Models call this after mutating state.
 */
my_ret_t my_view_model_notify_change(my_view_model_t* vm, const char* name);

/* ---------------- dummy implementation (tests/demos) ---------------- */

/** @brief Command handler for the dummy view model. */
typedef my_ret_t (*my_dummy_command_fn_t)(void* ctx, const char* args);

/**
 * @brief Generic property-bag view model. set_prop automatically fires
 * "prop:<name>".
 */
my_view_model_t* my_view_model_dummy_create(const my_allocator_t* allocator);

/** @brief Register a command on a dummy view model (can_exec -> true). */
my_ret_t my_view_model_dummy_add_command(my_view_model_t* vm, const char* name,
                                         my_dummy_command_fn_t fn, void* ctx);

#endif /* MY_VIEW_MODEL_H */
