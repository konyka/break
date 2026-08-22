/**
 * @file my_value_validator.h
 * @brief Value validators (delegate pattern) + built-ins.
 *
 * is_valid() checks a value about to be written back to the model;
 * fix() (optional) repairs it in place. Built-ins: "not_empty"
 * (singleton) and range(min,max) (created per instance).
 */
#ifndef MY_VALUE_VALIDATOR_H
#define MY_VALUE_VALIDATOR_H

#include "myc/my_value.h"

/** @brief Value validator delegate. */
typedef struct my_value_validator_t {
  bool (*is_valid)(void* ctx, const my_value_t* value, char* msg,
                   size_t msg_size);
  my_ret_t (*fix)(void* ctx, my_value_t* value); /**< optional, may be NULL */
  void* ctx;
} my_value_validator_t;

/** @brief Validate (NULL validator = always valid). */
bool my_value_validate(const my_value_validator_t* validator,
                       const my_value_t* value, char* msg, size_t msg_size);

/** @brief The "not_empty" singleton validator. */
const my_value_validator_t* my_value_validator_not_empty(void);

/**
 * @brief Create a range validator for int values (inclusive bounds).
 * Destroy with my_value_validator_range_destroy().
 */
my_value_validator_t* my_value_validator_range_create(
    const my_allocator_t* allocator, int32_t min, int32_t max);

void my_value_validator_range_destroy(my_value_validator_t* validator);

/**
 * @brief Find a validator by name: custom registry first, then built-ins
 * ("not_empty"). Parameterized ones (range) are created by the parser.
 */
const my_value_validator_t* my_value_validator_find(const char* name);

/**
 * @brief Register a custom validator by name (borrowed ref; max 16).
 * Same-name registration replaces (including built-ins, with a warning).
 * Startup-time, single-threaded only (no locking by design).
 */
my_ret_t my_value_validator_register(const char* name,
                                     const my_value_validator_t* validator);

/** @brief Remove a custom registration (built-ins are not removable). */
my_ret_t my_value_validator_unregister(const char* name);

#endif /* MY_VALUE_VALIDATOR_H */
