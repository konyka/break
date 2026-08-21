/**
 * @file my_command_binding.h
 * @brief Command binding internals (used by my_binding_context).
 */
#ifndef MY_COMMAND_BINDING_H
#define MY_COMMAND_BINDING_H

#include "mymvvm/my_binding_context.h"

/** @brief One command binding: target event -> vm command. */
typedef struct my_command_binding_t {
  my_binding_context_t* ctx;
  const my_allocator_t* allocator;
  my_binding_target_t* target; /**< weak */
  my_binding_rule_t rule;
  uint32_t target_listener_id;
} my_command_binding_t;

my_command_binding_t* my_command_binding_create(const my_allocator_t* allocator,
                                                my_binding_context_t* ctx,
                                                my_binding_target_t* target,
                                                const my_binding_rule_t* rule);

void my_command_binding_destroy(my_command_binding_t* binding);

#endif /* MY_COMMAND_BINDING_H */
