/**
 * @file my_style.h
 * @brief Style: a small per-state key/value property set.
 *
 * Four state slots (normal/hover/pressed/disabled); lookups fall back to
 * normal when a key is absent in the requested state. Colors are stored
 * as MY_VALUE_UINT32 0xRRGGBBAA. Keys are short strings ("bg_color",
 * "fg_color", "border_color", "border_width", "round_radius",
 * "font_size", ...).
 */
#ifndef MY_STYLE_H
#define MY_STYLE_H

#include "myc/my_value.h"
#include "myui/my_style_keys.h"

/** @brief Widget visual states (style slots). */
typedef enum my_widget_state_t {
  MY_STATE_NORMAL = 0,
  MY_STATE_HOVER,
  MY_STATE_PRESSED,
  MY_STATE_DISABLED,
  MY_STATE_COUNT
} my_widget_state_t;

#define MY_STYLE_MAX_PROPS 16
#define MY_STYLE_KEY_LEN 32

/** @brief One key/value property (inline storage). */
typedef struct my_style_prop_t {
  char key[MY_STYLE_KEY_LEN];
  my_value_t value;
} my_style_prop_t;

/** @brief Style property set for all states. */
typedef struct my_style_t {
  const my_allocator_t* allocator;
  my_style_prop_t props[MY_STATE_COUNT][MY_STYLE_MAX_PROPS];
  size_t counts[MY_STATE_COUNT];
} my_style_t;

/** @brief Initialize an empty style (NULL allocator = default). */
void my_style_init(my_style_t* style, const my_allocator_t* allocator);

/** @brief Release all property values (strings). */
void my_style_reset(my_style_t* style);

/**
 * @brief Set (or replace) a property. MY_RET_OOM when the state slot is
 * full (MY_STYLE_MAX_PROPS).
 */
my_ret_t my_style_set(my_style_t* style, my_widget_state_t state, const char* key,
                      const my_value_t* value);

/** @brief Convenience: set a color (0xRRGGBBAA). */
my_ret_t my_style_set_color(my_style_t* style, my_widget_state_t state,
                            const char* key, uint32_t rgba);

/** @brief Convenience: set an int32. */
my_ret_t my_style_set_int(my_style_t* style, my_widget_state_t state,
                          const char* key, int32_t value);

/**
 * @brief Look up a property; falls back to the normal state.
 * NULL when unset in both.
 */
const my_value_t* my_style_get(const my_style_t* style, my_widget_state_t state,
                               const char* key);

#endif /* MY_STYLE_H */
