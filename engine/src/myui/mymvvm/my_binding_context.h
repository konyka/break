/**
 * @file my_binding_context.h
 * @brief Binding context: applies binding rules between a view model and
 * UI targets.
 *
 * Update dispatching is SYNCHRONOUS (no queue): a vm property change
 * pushes to targets inside the notify call, a target change writes back
 * inside the event call. Manual full sync: my_binding_context_update_
 * to_view() / update_to_vm().
 */
#ifndef MY_BINDING_CONTEXT_H
#define MY_BINDING_CONTEXT_H

#include "mymvvm/my_binding_rule.h"
#include "mymvvm/my_binding_target.h"
#include "mymvvm/my_view_model.h"

/** @brief Binding context (opaque). */
typedef struct my_binding_context_t my_binding_context_t;

/**
 * @brief Create a context bound to vm (takes a reference; NULL vm
 * allowed, set later with my_binding_context_set_view_model).
 */
my_binding_context_t* my_binding_context_create(const my_allocator_t* allocator,
                                                my_view_model_t* vm);

void my_binding_context_destroy(my_binding_context_t* ctx);

/** @brief Replace the view model and re-wire data, items, and condition rules. */
my_ret_t my_binding_context_set_view_model(my_binding_context_t* ctx,
                                           my_view_model_t* vm);

my_view_model_t* my_binding_context_get_view_model(my_binding_context_t* ctx);

/**
 * @brief Apply one binding rule string between the vm and target.
 * Rules are kept for the context's lifetime.
 */
my_ret_t my_binding_context_bind(my_binding_context_t* ctx,
                                 my_binding_target_t* target,
                                 const char* rule_str);

/** @brief Push all data bindings vm -> target. */
my_ret_t my_binding_context_update_to_view(my_binding_context_t* ctx);

/** @brief Pull all TwoWay data bindings target -> vm. */
my_ret_t my_binding_context_update_to_vm(my_binding_context_t* ctx);

#endif /* MY_BINDING_CONTEXT_H */
