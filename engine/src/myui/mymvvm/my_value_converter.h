/**
 * @file my_value_converter.h
 * @brief Value converters (delegate pattern) + a small name registry.
 *
 * convert() transforms model -> view, convert_back() view -> model.
 * Built-ins are shared singletons: "upper", "lower", "int_to_str",
 * "bool_negate".
 */
#ifndef MY_VALUE_CONVERTER_H
#define MY_VALUE_CONVERTER_H

#include "myc/my_value.h"

/** @brief Value converter delegate. */
typedef struct my_value_converter_t {
  my_ret_t (*convert)(void* ctx, my_value_t* value);
  my_ret_t (*convert_back)(void* ctx, my_value_t* value);
  void* ctx;
} my_value_converter_t;

/**
 * @brief Find a converter by name: custom registry first, then built-ins
 * ("upper", "lower", "int_to_str", "bool_negate"). NULL when unknown.
 */
const my_value_converter_t* my_value_converter_find(const char* name);

/**
 * @brief Register a custom converter by name (borrowed ref; max 16
 * custom entries). Registering a name that already exists REPLACES it
 * (including built-ins) and logs a warning. Call only at startup,
 * single-threaded (no locking by design).
 */
my_ret_t my_value_converter_register(const char* name,
                                     const my_value_converter_t* converter);

/** @brief Remove a custom registration (built-ins are not removable). */
my_ret_t my_value_converter_unregister(const char* name);

/** @brief Apply converter (model -> view). NULL conv = pass-through. */
my_ret_t my_value_convert(const my_value_converter_t* conv, my_value_t* value);

/** @brief Apply converter (view -> model). NULL conv = pass-through. */
my_ret_t my_value_convert_back(const my_value_converter_t* conv, my_value_t* value);

#endif /* MY_VALUE_CONVERTER_H */
