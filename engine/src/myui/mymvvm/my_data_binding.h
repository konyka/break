/**
 * @file my_data_binding.h
 * @brief Data binding internals (used by my_binding_context).
 */
#ifndef MY_DATA_BINDING_H
#define MY_DATA_BINDING_H

#include "mymvvm/my_binding_context.h"
#include "mymvvm/my_value_converter.h"
#include "mymvvm/my_value_validator.h"

/** @brief One data binding between a vm property and a target property. */
typedef struct my_data_binding_t {
  my_binding_context_t* ctx;
  const my_allocator_t* allocator;
  my_binding_target_t* target;       /**< weak */
  my_binding_rule_t rule;
  const my_value_converter_t* converter; /**< borrowed (registry) */
  my_value_validator_t* validator;   /**< owned when parameterized */
  bool validator_owned;
  uint32_t vm_listener_id;
  uint32_t target_listener_id;
  bool updating;                     /**< echo-loop guard */
} my_data_binding_t;

my_data_binding_t* my_data_binding_create(const my_allocator_t* allocator,
                                          my_binding_context_t* ctx,
                                          my_binding_target_t* target,
                                          const my_binding_rule_t* rule);

void my_data_binding_destroy(my_data_binding_t* binding);

/** @brief Push vm -> target (applies converter). */
my_ret_t my_data_binding_push(my_data_binding_t* binding);

/** @brief Pull target -> vm (convert_back + validator). */
my_ret_t my_data_binding_pull(my_data_binding_t* binding);

/** @brief Re-subscribe to a (new) view model and push. */
my_ret_t my_data_binding_rebind(my_data_binding_t* binding, my_view_model_t* vm);

#endif /* MY_DATA_BINDING_H */
