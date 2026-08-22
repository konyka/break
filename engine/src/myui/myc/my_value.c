/**
 * @file my_value.c
 * @brief Dynamically typed value.
 */
#include "myc/my_value.h"

#include "myc/my_str.h"

void my_value_init(my_value_t* v, const my_allocator_t* allocator) {
  if (v == NULL) {
    return;
  }
  v->type = MY_VALUE_NONE;
  v->allocator = allocator;
  v->u.ptr = NULL;
}

void my_value_reset(my_value_t* v) {
  if (v == NULL) {
    return;
  }
  if (v->type == MY_VALUE_STR) {
    my_mem_free(v->allocator, v->u.str);
  }
  v->type = MY_VALUE_NONE;
  v->u.ptr = NULL;
}

my_value_type_t my_value_type(const my_value_t* v) {
  return v != NULL ? v->type : MY_VALUE_NONE;
}

#define MY_VALUE_SET_SCALAR(name, type_tag, ctype, member) \
  my_ret_t name(my_value_t* v, ctype value) {              \
    if (v == NULL) {                                       \
      return MY_RET_INVALID_PARAMS;                        \
    }                                                      \
    my_value_reset(v);                                     \
    v->type = type_tag;                                    \
    v->u.member = value;                                   \
    return MY_RET_OK;                                      \
  }

MY_VALUE_SET_SCALAR(my_value_set_bool, MY_VALUE_BOOL, bool, b)
MY_VALUE_SET_SCALAR(my_value_set_int32, MY_VALUE_INT32, int32_t, i32)
MY_VALUE_SET_SCALAR(my_value_set_uint32, MY_VALUE_UINT32, uint32_t, u32)
MY_VALUE_SET_SCALAR(my_value_set_int64, MY_VALUE_INT64, int64_t, i64)
MY_VALUE_SET_SCALAR(my_value_set_float, MY_VALUE_FLOAT, float, f32)
MY_VALUE_SET_SCALAR(my_value_set_double, MY_VALUE_DOUBLE, double, f64)
MY_VALUE_SET_SCALAR(my_value_set_pointer, MY_VALUE_POINTER, void*, ptr)

my_ret_t my_value_set_str(my_value_t* v, const char* s) {
  char* copy;
  if (v == NULL) {
    return MY_RET_INVALID_PARAMS;
  }
  if (s == NULL) {
    my_value_reset(v);
    return MY_RET_OK;
  }
  copy = my_strdup(v->allocator, s);
  if (copy == NULL) {
    return MY_RET_OOM;
  }
  my_value_reset(v);
  v->type = MY_VALUE_STR;
  v->u.str = copy;
  return MY_RET_OK;
}

#define MY_VALUE_GET_SCALAR(name, type_tag, ctype, member, fallback) \
  ctype name(const my_value_t* v) {                                  \
    if (v == NULL || v->type != type_tag) {                          \
      return fallback;                                               \
    }                                                                \
    return v->u.member;                                              \
  }

MY_VALUE_GET_SCALAR(my_value_get_bool, MY_VALUE_BOOL, bool, b, false)
MY_VALUE_GET_SCALAR(my_value_get_int32, MY_VALUE_INT32, int32_t, i32, 0)
MY_VALUE_GET_SCALAR(my_value_get_uint32, MY_VALUE_UINT32, uint32_t, u32, 0)
MY_VALUE_GET_SCALAR(my_value_get_int64, MY_VALUE_INT64, int64_t, i64, 0)
MY_VALUE_GET_SCALAR(my_value_get_float, MY_VALUE_FLOAT, float, f32, 0.0f)
MY_VALUE_GET_SCALAR(my_value_get_double, MY_VALUE_DOUBLE, double, f64, 0.0)
MY_VALUE_GET_SCALAR(my_value_get_pointer, MY_VALUE_POINTER, void*, ptr, NULL)

const char* my_value_get_str(const my_value_t* v) {
  if (v == NULL || v->type != MY_VALUE_STR) {
    return NULL;
  }
  return v->u.str;
}

my_ret_t my_value_copy(my_value_t* dst, const my_value_t* src) {
  if (dst == NULL || src == NULL) {
    return MY_RET_INVALID_PARAMS;
  }
  switch (src->type) {
    case MY_VALUE_STR:
      return my_value_set_str(dst, src->u.str);
    case MY_VALUE_NONE:
      my_value_reset(dst);
      return MY_RET_OK;
    default:
      my_value_reset(dst);
      dst->type = src->type;
      dst->u = src->u;
      return MY_RET_OK;
  }
}
