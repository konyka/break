/**
 * @file my_style.c
 * @brief Style: per-state key/value property set.
 */
#include "myui/my_style.h"

#include <string.h>

void my_style_init(my_style_t* style, const my_allocator_t* allocator) {
  size_t i, j;
  if (style == NULL) {
    return;
  }
  style->allocator = allocator;
  for (i = 0; i < MY_STATE_COUNT; i++) {
    style->counts[i] = 0;
    for (j = 0; j < MY_STYLE_MAX_PROPS; j++) {
      my_value_init(&style->props[i][j].value, allocator);
    }
  }
}

void my_style_reset(my_style_t* style) {
  size_t i, j;
  if (style == NULL) {
    return;
  }
  for (i = 0; i < MY_STATE_COUNT; i++) {
    for (j = 0; j < MY_STYLE_MAX_PROPS; j++) {
      my_value_reset(&style->props[i][j].value);
    }
    style->counts[i] = 0;
  }
}

static my_style_prop_t* find_prop(my_style_t* style, my_widget_state_t state,
                                  const char* key) {
  size_t i;
  if (state >= MY_STATE_COUNT) {
    return NULL;
  }
  for (i = 0; i < style->counts[state]; i++) {
    if (strncmp(style->props[state][i].key, key, MY_STYLE_KEY_LEN) == 0) {
      return &style->props[state][i];
    }
  }
  return NULL;
}

my_ret_t my_style_set(my_style_t* style, my_widget_state_t state, const char* key,
                      const my_value_t* value) {
  my_style_prop_t* prop;
  if (style == NULL || key == NULL || value == NULL || state >= MY_STATE_COUNT ||
      strlen(key) >= MY_STYLE_KEY_LEN) {
    return MY_RET_INVALID_PARAMS;
  }
  prop = find_prop(style, state, key);
  if (prop == NULL) {
    if (style->counts[state] >= MY_STYLE_MAX_PROPS) {
      return MY_RET_OOM;
    }
    prop = &style->props[state][style->counts[state]++];
    strncpy(prop->key, key, MY_STYLE_KEY_LEN - 1);
    prop->key[MY_STYLE_KEY_LEN - 1] = '\0';
  }
  return my_value_copy(&prop->value, value);
}

my_ret_t my_style_set_color(my_style_t* style, my_widget_state_t state,
                            const char* key, uint32_t rgba) {
  my_value_t v;
  my_value_init(&v, NULL);
  my_value_set_uint32(&v, rgba);
  return my_style_set(style, state, key, &v);
}

my_ret_t my_style_set_int(my_style_t* style, my_widget_state_t state,
                          const char* key, int32_t value) {
  my_value_t v;
  my_value_init(&v, NULL);
  my_value_set_int32(&v, value);
  return my_style_set(style, state, key, &v);
}

const my_value_t* my_style_get(const my_style_t* style, my_widget_state_t state,
                               const char* key) {
  const my_style_prop_t* prop;
  if (style == NULL || key == NULL) {
    return NULL;
  }
  prop = find_prop((my_style_t*)style, state, key);
  if (prop == NULL && state != MY_STATE_NORMAL) {
    prop = find_prop((my_style_t*)style, MY_STATE_NORMAL, key);
  }
  return prop != NULL ? &prop->value : NULL;
}
