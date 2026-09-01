/**
 * @file my_theme.h
 * @brief Theme: a style sheet mapping (widget type, optional name) to
 * styles, plus a minimal text loader.
 *
 * Text format (one rule per line, '#' starts hex colors, blank lines and
 * lines starting with ';' are ignored):
 *   button.normal.bg_color=#FF4081
 *   button[ok].pressed.bg_color=#C60055
 *   label.font_size=16            (no state = applied to ALL states)
 * Values: #RRGGBB / #RRGGBBAA (color), integers, floats, else strings.
 */
#ifndef MY_THEME_H
#define MY_THEME_H

#include <core/types.h>
#include "myc/my_darray.h"
#include "myui/my_style.h"

#define MY_THEME_TYPE_LEN 24
#define MY_THEME_NAME_LEN 32
#define MY_THEME_MAX_ANCESTORS 4u

/** @brief Fixed-size ancestor selector component; no lookup allocation. */
typedef struct my_theme_ancestor_t {
  char widget_type[MY_THEME_TYPE_LEN];
  char name[MY_THEME_NAME_LEN];
  char style_class[MY_THEME_NAME_LEN];
} my_theme_ancestor_t;

/** @brief One theme rule: style for a (type [, name][, class]
 * [, bounded ancestor path]) selector. */
typedef struct my_theme_entry_t {
  char widget_type[MY_THEME_TYPE_LEN]; /**< e.g. "button"; "" = any */
  char name[MY_THEME_NAME_LEN];        /**< CSS #id == widget name; empty = none */
  char style_class[MY_THEME_NAME_LEN]; /**< CSS required classes; empty = none */
  char ancestor_type[MY_THEME_TYPE_LEN]; /**< legacy single-ancestor view */
  bool ancestor_direct; /**< direct-child selector instead of any ancestor */
  u32 ancestor_count;
  my_theme_ancestor_t ancestors[MY_THEME_MAX_ANCESTORS];
  bool ancestor_direct_path[MY_THEME_MAX_ANCESTORS];
  int32_t specificity[MY_STATE_COUNT][MY_STYLE_MAX_PROPS];
  /**< CSS specificity parallel to style.props. */
  my_style_t style;
} my_theme_entry_t;

/** @brief Theme (style sheet). */
typedef struct my_theme_t {
  const my_allocator_t* allocator;
  my_darray_t* entries; /**< my_theme_entry_t* */
} my_theme_t;

my_theme_t* my_theme_create(const my_allocator_t* allocator);
void my_theme_destroy(my_theme_t* theme);

/** @brief Set a property on the (type, name) rule (name NULL/"" = type-wide). */
my_ret_t my_theme_set(my_theme_t* theme, const char* widget_type, const char* name,
                      my_widget_state_t state, const char* key,
                      const my_value_t* value);

/** @brief Convenience: set a color (0xRRGGBBAA). */
my_ret_t my_theme_set_color(my_theme_t* theme, const char* widget_type,
                            const char* name, my_widget_state_t state,
                            const char* key, uint32_t rgba);

/** @brief Convenience: set an int32. */
my_ret_t my_theme_set_int(my_theme_t* theme, const char* widget_type,
                          const char* name, my_widget_state_t state,
                          const char* key, int32_t value);

/**
 * @brief Look up a property for a widget of type/name.
 * Resolution: (type+name, state) -> (type+name, normal) -> (type, state)
 * -> (type, normal). NULL when unresolved.
 */
const my_value_t* my_theme_get(const my_theme_t* theme, const char* widget_type,
                               const char* name, my_widget_state_t state,
                               const char* key);

/**
 * @brief Extended rule write (M18a CSS bridge): style_class is a
 * space-separated required class set, and ancestor_type is the legacy
 * single-ancestor descendant requirement. Same selector rewrites in place
 * (source-order override).
 */
my_ret_t my_theme_set_ex(my_theme_t* theme, const char* widget_type,
                         const char* name, const char* style_class,
                         const char* ancestor_type, my_widget_state_t state,
                         const char* key, const my_value_t* value);

/** @brief Extended selector write with direct-child support. */
my_ret_t my_theme_set_ex2(my_theme_t* theme, const char* widget_type,
                          const char* name, const char* style_class,
                          const char* ancestor_type, bool ancestor_direct,
                          my_widget_state_t state, const char* key,
                          const my_value_t* value);

/** @brief Extended write with an explicit CSS specificity score. */
my_ret_t my_theme_set_ex3(my_theme_t* theme, const char* widget_type,
                          const char* name, const char* style_class,
                          const char* ancestor_type, bool ancestor_direct,
                          my_widget_state_t state, const char* key,
                          const my_value_t* value, int32_t specificity);

/** @brief Extended write for a bounded multi-level selector path.
 * Ancestors are ordered nearest-to-farthest from the target. Each path flag
 * applies between the target/current match and that ancestor: true means
 * direct-child, false means descendant search. The operation copies inputs.
 */
my_ret_t my_theme_set_ex4(my_theme_t* theme, const char* widget_type,
                          const char* name, const char* style_class,
                          const my_theme_ancestor_t* ancestors,
                          size_t ancestor_count,
                          const bool* ancestor_direct_path,
                          my_widget_state_t state, const char* key,
                          const my_value_t* value, int32_t specificity);

struct my_widget_t;

/**
 * @brief Widget-aware lookup with the CSS cascade (M18a): #id > .class
 * > type (state -> normal fallback at each level; descendant selectors
 * need an ancestor of the given type). Reduces to the plain (type,name)
 * chain for text-format-only themes.
 */
const my_value_t* my_theme_get_for_widget(const my_theme_t* theme,
                                          const struct my_widget_t* widget,
                                          my_widget_state_t state,
                                          const char* key);

/**
 * @brief Virtual-part lookup (M19b): for drawn parts that are not real
 * widgets (node headers, sockets, links). `owner` anchors the
 * descendant search INCLUSIVE (CSS `node .header` hits when the owner
 * is a node). Cascade is the same #id > .class > type.
 */
const my_value_t* my_theme_get_part(const my_theme_t* theme,
                                    const struct my_widget_t* owner,
                                    const char* part_type,
                                    const char* part_class,
                                    my_widget_state_t state,
                                    const char* key);

/** @brief Virtual-part color with theme climbing + fallback (widgets
 * painting drawn parts; M19b). */
uint32_t my_widget_part_color(struct my_widget_t* widget,
                              const char* part_type, const char* part_class,
                              my_widget_state_t state, const char* key,
                              uint32_t fallback);

/** @brief Built-in default theme (light palette for window/button/label). */
my_theme_t* my_theme_default_create(const my_allocator_t* allocator);

/**
 * @brief Load rules from text (see file header for the format).
 * @return MY_RET_OK, or MY_RET_INVALID_PARAMS on the first bad line.
 */
my_ret_t my_theme_load_str(my_theme_t* theme, const char* str);

#endif /* MY_THEME_H */
