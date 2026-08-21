/**
 * @file my_value_validator.c
 * @brief Built-in value validators.
 */
#include "mymvvm/my_value_validator.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "myc/my_error.h"
#include "myc/my_str.h"

/* ---------------- not_empty ---------------- */

static bool not_empty_is_valid(void* ctx, const my_value_t* value, char* msg,
                               size_t msg_size) {
  const char* s;
  (void)ctx;
  if (value == NULL || value->type != MY_VALUE_STR) {
    return true; /* only constrains strings */
  }
  s = my_value_get_str(value);
  if (s != NULL && *s != '\0') {
    return true;
  }
  if (msg != NULL && msg_size > 0) {
    snprintf(msg, msg_size, "must not be empty");
  }
  return false;
}

static const my_value_validator_t NOT_EMPTY = {not_empty_is_valid, NULL, NULL};

const my_value_validator_t* my_value_validator_not_empty(void) {
  return &NOT_EMPTY;
}

/* ---------------- range ---------------- */

typedef struct my_range_validator_t {
  my_value_validator_t base;
  const my_allocator_t* allocator;
  int32_t min;
  int32_t max;
} my_range_validator_t;

static int32_t value_as_int(const my_value_t* value, bool* ok) {
  const char* s;
  char* end = NULL;
  long v;
  *ok = true;
  switch (value->type) {
    case MY_VALUE_INT32:
      return my_value_get_int32(value);
    case MY_VALUE_UINT32:
      return (int32_t)my_value_get_uint32(value);
    case MY_VALUE_INT64:
      return (int32_t)my_value_get_int64(value);
    case MY_VALUE_DOUBLE:
      return (int32_t)my_value_get_double(value);
    case MY_VALUE_STR:
      s = my_value_get_str(value);
      v = strtol(s, &end, 10);
      if (end == s || *end != '\0') {
        *ok = false;
        return 0;
      }
      return (int32_t)v;
    default:
      *ok = false;
      return 0;
  }
}

static bool range_is_valid(void* ctx, const my_value_t* value, char* msg,
                           size_t msg_size) {
  my_range_validator_t* r = (my_range_validator_t*)ctx;
  bool ok;
  int32_t v = value_as_int(value, &ok);
  if (ok && v >= r->min && v <= r->max) {
    return true;
  }
  if (msg != NULL && msg_size > 0) {
    snprintf(msg, msg_size, "out of range [%d, %d]", (int)r->min, (int)r->max);
  }
  return false;
}

static my_ret_t range_fix(void* ctx, my_value_t* value) {
  my_range_validator_t* r = (my_range_validator_t*)ctx;
  bool ok;
  int32_t v = value_as_int(value, &ok);
  if (!ok) {
    v = r->min;
  }
  if (v < r->min) {
    v = r->min;
  }
  if (v > r->max) {
    v = r->max;
  }
  return my_value_set_int32(value, v);
}

my_value_validator_t* my_value_validator_range_create(
    const my_allocator_t* allocator, int32_t min, int32_t max) {
  my_range_validator_t* r =
      (my_range_validator_t*)my_mem_calloc(allocator, 1, sizeof(my_range_validator_t));
  if (r == NULL) {
    return NULL;
  }
  r->base.is_valid = range_is_valid;
  r->base.fix = range_fix;
  r->base.ctx = r;
  r->allocator = allocator;
  r->min = min;
  r->max = max;
  return (my_value_validator_t*)r;
}

void my_value_validator_range_destroy(my_value_validator_t* validator) {
  my_range_validator_t* r = (my_range_validator_t*)validator;
  if (r != NULL) {
    my_mem_free(r->allocator, r);
  }
}

/* ---------------- custom registry (startup-time, single-threaded) ---- */

#define MY_VALIDATOR_MAX_CUSTOM 16

typedef struct validator_entry_t {
  char name[24];
  const my_value_validator_t* validator;
} validator_entry_t;

static validator_entry_t g_validators[MY_VALIDATOR_MAX_CUSTOM];
static size_t g_validator_count = 0;

my_ret_t my_value_validator_register(const char* name,
                                     const my_value_validator_t* validator) {
  size_t i;
  if (name == NULL || validator == NULL || strlen(name) >= 24) {
    return MY_RET_INVALID_PARAMS;
  }
  for (i = 0; i < g_validator_count; i++) {
    if (my_str_eq(g_validators[i].name, name)) {
      g_validators[i].validator = validator;
      return MY_RET_OK;
    }
  }
  if (my_value_validator_find(name) != NULL) {
    MY_LOGW("validator '%s' overridden by custom registration", name);
  }
  if (g_validator_count >= MY_VALIDATOR_MAX_CUSTOM) {
    return MY_RET_OOM;
  }
  strncpy(g_validators[g_validator_count].name, name, 23);
  g_validators[g_validator_count].validator = validator;
  g_validator_count++;
  return MY_RET_OK;
}

my_ret_t my_value_validator_unregister(const char* name) {
  size_t i;
  if (name == NULL) {
    return MY_RET_INVALID_PARAMS;
  }
  for (i = 0; i < g_validator_count; i++) {
    if (my_str_eq(g_validators[i].name, name)) {
      g_validators[i] = g_validators[g_validator_count - 1];
      g_validator_count--;
      return MY_RET_OK;
    }
  }
  return MY_RET_NOT_FOUND;
}

const my_value_validator_t* my_value_validator_find(const char* name) {
  size_t i;
  if (name == NULL || *name == '\0') {
    return NULL;
  }
  for (i = 0; i < g_validator_count; i++) { /* custom first */
    if (my_str_eq(g_validators[i].name, name)) {
      return g_validators[i].validator;
    }
  }
  if (my_str_eq(name, "not_empty")) {
    return &NOT_EMPTY;
  }
  return NULL;
}

bool my_value_validate(const my_value_validator_t* validator,
                       const my_value_t* value, char* msg, size_t msg_size) {
  if (validator == NULL || validator->is_valid == NULL) {
    return true;
  }
  return validator->is_valid(validator->ctx, value, msg, msg_size);
}
