/**
 * @file my_condition_binding.h
 * @brief Condition binding internals (used by my_binding_context).
 */
#ifndef MY_CONDITION_BINDING_H
#define MY_CONDITION_BINDING_H

#include "mymvvm/my_binding_context.h"

/** @brief One condition binding: vm bool prop -> target prop (e.g. visible). */
typedef struct my_condition_binding_t {
  my_binding_context_t* ctx;
  const my_allocator_t* allocator;
  my_binding_target_t* target; /**< weak */
  my_binding_rule_t rule;
  uint32_t vm_listener_id;
} my_condition_binding_t;

my_condition_binding_t* my_condition_binding_create(
    const my_allocator_t* allocator, my_binding_context_t* ctx,
    my_binding_target_t* target, const my_binding_rule_t* rule);

void my_condition_binding_destroy(my_condition_binding_t* binding);

/** @brief Subscribe to the context's current vm and evaluate once. */
my_ret_t my_condition_binding_rebind(my_condition_binding_t* binding);

/** @brief Evaluate and push the condition (also called on prop changes). */
my_ret_t my_condition_binding_eval(my_condition_binding_t* binding);

#endif /* MY_CONDITION_BINDING_H */
