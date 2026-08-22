/**
 * @file my_value.h
 * @brief Dynamically typed value (scalar types, string, pointer).
 *
 * Values are stack-friendly: my_value_init() one, my_value_set_*() to
 * store, my_value_reset() to release (strings are deep-copied and owned).
 * Getters are strict: a type mismatch returns 0/false/NULL.
 *
 * The payload union is a named member (my_value_t::u) to stay valid C99
 * under -pedantic (anonymous unions are C11).
 */
#ifndef MY_VALUE_H
#define MY_VALUE_H

#include "myc/my_error.h"
#include "myc/my_mem.h"

/** @brief Type tag of a my_value_t. */
typedef enum my_value_type_t {
  MY_VALUE_NONE = 0,
  MY_VALUE_BOOL,
  MY_VALUE_INT32,
  MY_VALUE_UINT32,
  MY_VALUE_INT64,
  MY_VALUE_FLOAT,
  MY_VALUE_DOUBLE,
  MY_VALUE_STR,
  MY_VALUE_POINTER
} my_value_type_t;

/** @brief Dynamically typed value. */
typedef struct my_value_t {
  my_value_type_t type;            /**< active member of u */
  const my_allocator_t* allocator; /**< used to own copies of strings */
  union my_value_union_t {
    bool b;
    int32_t i32;
    uint32_t u32;
    int64_t i64;
    float f32;
    double f64;
    char* str;
    void* ptr;
  } u; /**< payload, named member for C99/-pedantic compatibility */
} my_value_t;

/** @brief Initialize v to MY_VALUE_NONE (NULL allocator = default). */
void my_value_init(my_value_t* v, const my_allocator_t* allocator);

/** @brief Release any owned payload (string) and reset to MY_VALUE_NONE. */
void my_value_reset(my_value_t* v);

/** @brief Type tag of v (MY_VALUE_NONE for NULL). */
my_value_type_t my_value_type(const my_value_t* v);

my_ret_t my_value_set_bool(my_value_t* v, bool value);
my_ret_t my_value_set_int32(my_value_t* v, int32_t value);
my_ret_t my_value_set_uint32(my_value_t* v, uint32_t value);
my_ret_t my_value_set_int64(my_value_t* v, int64_t value);
my_ret_t my_value_set_float(my_value_t* v, float value);
my_ret_t my_value_set_double(my_value_t* v, double value);
/** @brief Store a deep copy of s; NULL s resets to MY_VALUE_NONE. */
my_ret_t my_value_set_str(my_value_t* v, const char* s);
/** @brief Store a borrowed pointer (NOT owned, reset does not free it). */
my_ret_t my_value_set_pointer(my_value_t* v, void* ptr);

bool my_value_get_bool(const my_value_t* v);
int32_t my_value_get_int32(const my_value_t* v);
uint32_t my_value_get_uint32(const my_value_t* v);
int64_t my_value_get_int64(const my_value_t* v);
float my_value_get_float(const my_value_t* v);
double my_value_get_double(const my_value_t* v);
const char* my_value_get_str(const my_value_t* v);
void* my_value_get_pointer(const my_value_t* v);

/** @brief Deep-copy src into dst (dst must be initialized). */
my_ret_t my_value_copy(my_value_t* dst, const my_value_t* src);

#endif /* MY_VALUE_H */
