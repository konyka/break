/**
 * @file my_items_binding.h
 * @brief Items binding internals (used by my_binding_context).
 *
 * The bound vm property must be a MY_VALUE_POINTER holding a
 * my_view_model_array_t*. On "items_changed" (and once at bind time) the
 * binding asks the target to refresh: target->rebuild_items(template,
 * count, props_cb, ctx); row properties are read live from each child
 * view model. Targets may virtualize and update their adapters in place.
 */
#ifndef MY_ITEMS_BINDING_H
#define MY_ITEMS_BINDING_H

#include "mymvvm/my_binding_context.h"
#include "mymvvm/my_view_model_array.h"

/** @brief One items binding between an array vm property and a target. */
typedef struct my_items_binding_t {
  my_binding_context_t* ctx;
  const my_allocator_t* allocator;
  my_binding_target_t* target; /**< weak */
  my_binding_rule_t rule;
  my_view_model_array_t* array; /**< resolved from the vm prop (weak) */
  uint32_t array_listener_id;
  uint32_t vm_listener_id; /**< re-resolve when the prop itself changes */
} my_items_binding_t;

my_items_binding_t* my_items_binding_create(const my_allocator_t* allocator,
                                            my_binding_context_t* ctx,
                                            my_binding_target_t* target,
                                            const my_binding_rule_t* rule);

void my_items_binding_destroy(my_items_binding_t* binding);

/** @brief Subscribe to the context's current vm and refresh the target. */
my_ret_t my_items_binding_rebind(my_items_binding_t* binding);

/** @brief Rebuild the target's item list (also called on changes). */
my_ret_t my_items_binding_rebuild(my_items_binding_t* binding);

#endif /* MY_ITEMS_BINDING_H */
