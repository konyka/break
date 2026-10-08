/**
 * @file my_theme.h
 * @brief Theme: a style sheet mapping (widget type, optional name) to
 * styles, plus transactional text loading.
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
#define MY_THEME_MAX_SCOPE_LIMITS 4u
#define MY_THEME_MAX_CONTAINER_QUERY_BYTES 255u
#define MY_THEME_MAX_PROPERTY_VALUE_BYTES 255u
#define MY_THEME_SCOPE_ROOT_IMPLICIT MY_THEME_MAX_ANCESTORS
#define MY_THEME_MAX_BYTES (4u * 1024u * 1024u)

/** @brief Fixed-size ancestor selector component; no lookup allocation. */
typedef struct my_theme_ancestor_t {
  char widget_type[MY_THEME_TYPE_LEN];
  char name[MY_THEME_NAME_LEN];
  char style_class[MY_THEME_NAME_LEN];
} my_theme_ancestor_t;

/** @brief R621: one @scope limit selector — the subject compound plus a
 * bounded ancestor path above it (nearest-first, per-edge child flags). */
typedef struct my_theme_scope_limit_t {
  my_theme_ancestor_t subject;
  u32 ancestor_count;
  my_theme_ancestor_t ancestors[MY_THEME_MAX_ANCESTORS];
  bool ancestor_direct_path[MY_THEME_MAX_ANCESTORS];
} my_theme_scope_limit_t;

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
  u32 scope_limit_count;
  my_theme_scope_limit_t scope_limits[MY_THEME_MAX_SCOPE_LIMITS];
  u32 scope_limit_root_index[MY_THEME_MAX_SCOPE_LIMITS];
  int32_t specificity[MY_STATE_COUNT][MY_STYLE_MAX_PROPS];
  /**< CSS specificity parallel to style.props. */
  my_style_t style;
  /* R670: deferred @container condition ("" = unconditional). Entries
   * with a condition are skipped by the cascade unless the element's
   * nearest ancestor query container satisfies it. R675: pair2 is the
   * outer condition of a nested @container (conjunction; depth ≥ 3
   * keeps the innermost two). */
  char container_query[MY_THEME_MAX_CONTAINER_QUERY_BYTES + 1u];
  char container_name[MY_THEME_NAME_LEN];
  char container_query2[MY_THEME_MAX_CONTAINER_QUERY_BYTES + 1u];
  char container_name2[MY_THEME_NAME_LEN];
} my_theme_entry_t;

/** @brief R671: one registered custom property (@property). `syntax` is
 * the raw syntax string (stored, enforcement is a later slice);
 * `initial` is the raw initial-value token stream when has_initial. */
typedef struct my_theme_property_def_t {
  char name[MY_STYLE_KEY_LEN];
  char syntax[64];
  bool inherits;
  bool has_initial;
  char initial[MY_THEME_MAX_PROPERTY_VALUE_BYTES + 1u];
} my_theme_property_def_t;

/** @brief Theme (style sheet). */
typedef struct my_theme_t {
  const my_allocator_t* allocator;
  my_darray_t* entries; /**< my_theme_entry_t* */
  my_darray_t* property_defs; /**< my_theme_property_def_t* (R671) */
} my_theme_t;

my_theme_t* my_theme_create(const my_allocator_t* allocator);
void my_theme_destroy(my_theme_t* theme);

/** @brief Deep-copy a theme for transactional loading. NULL on allocation
 * failure; values, selector metadata and cascade specificity are copied. */
my_theme_t* my_theme_clone(const my_theme_t* source);

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

/** @brief Extended write with bounded @scope exclusion selectors.
 *
 * A scope limit root index may equal MY_THEME_SCOPE_ROOT_IMPLICIT to denote
 * an omitted scope root. In that form the limit is searched on the complete
 * widget parent chain and no ancestor selector is added.
 */
my_ret_t my_theme_set_ex5(my_theme_t* theme, const char* widget_type,
                          const char* name, const char* style_class,
                          const my_theme_ancestor_t* ancestors,
                          size_t ancestor_count,
                          const bool* ancestor_direct_path,
                          const my_theme_ancestor_t* scope_limits,
                          size_t scope_limit_count,
                          const size_t* scope_limit_root_indices,
                          my_widget_state_t state, const char* key,
                          const my_value_t* value, int32_t specificity);

/** @brief R621: ex5 with full limit SELECTOR PATHS — each limit is a
 * subject compound plus a bounded nearest-first ancestor path with per-edge
 * child flags (CSS complex scoping limits). A widget is excluded when some
 * element between it and the scope root (inclusive of itself, bounded by
 * the limit's root index) matches subject+path. */
my_ret_t my_theme_set_ex6(my_theme_t* theme, const char* widget_type,
                          const char* name, const char* style_class,
                          const my_theme_ancestor_t* ancestors,
                          size_t ancestor_count,
                          const bool* ancestor_direct_path,
                          const my_theme_scope_limit_t* scope_limits,
                          size_t scope_limit_count,
                          const size_t* scope_limit_root_indices,
                          my_widget_state_t state, const char* key,
                          const my_value_t* value, int32_t specificity);

/** @brief ex6 plus the deferred @container condition (R670): entries
 * are keyed by the condition too — same selector, different condition,
 * different entry. Empty strings = unconditional. */
my_ret_t my_theme_set_ex7(my_theme_t* theme, const char* widget_type,
                          const char* name, const char* style_class,
                          const my_theme_ancestor_t* ancestors,
                          size_t ancestor_count,
                          const bool* ancestor_direct_path,
                          const my_theme_scope_limit_t* scope_limits,
                          size_t scope_limit_count,
                          const size_t* scope_limit_root_indices,
                          my_widget_state_t state, const char* key,
                          const my_value_t* value, int32_t specificity,
                          const char* container_query,
                          const char* container_name);

/** @brief ex7 plus the outer condition of a nested @container (R675):
 * the entry applies only when BOTH condition pairs match. Empty strings
 * = unconditional. */
my_ret_t my_theme_set_ex8(my_theme_t* theme, const char* widget_type,
                          const char* name, const char* style_class,
                          const my_theme_ancestor_t* ancestors,
                          size_t ancestor_count,
                          const bool* ancestor_direct_path,
                          const my_theme_scope_limit_t* scope_limits,
                          size_t scope_limit_count,
                          const size_t* scope_limit_root_indices,
                          my_widget_state_t state, const char* key,
                          const my_value_t* value, int32_t specificity,
                          const char* container_query,
                          const char* container_name,
                          const char* container_query2,
                          const char* container_name2);

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
 * @brief var()-resolving lookup (R666): like my_theme_get_for_widget,
 * but a declaration whose value mentions var( is substituted against the
 * element's custom properties (own cascade first, then DOM inheritance),
 * with fallback chains and cycle detection. Returns false when the
 * property is absent or invalid at computed-value time (unset); `out`
 * is invalid at computed-value time (unset); `out` must be initialized
 * by the caller and is meaningful only when the call returns true.
 */
bool my_theme_get_for_widget_var(const my_theme_t* theme,
                                 const struct my_widget_t* widget,
                                 my_widget_state_t state, const char* key,
                                 my_value_t* out);

/** @brief R688: resolve a theme-cascade property's computed value to
 * its substituted TEXT — unlike my_theme_get_for_widget_var the result
 * is not probed into a typed value, so percentage spellings ("50%")
 * survive. Local-style strings are the caller's literal domain (the
 * R667 contract). Implemented in my_css.c. Returns false when
 * unresolved. */
bool my_theme_get_for_widget_var_text(const my_theme_t* theme,
                                       const struct my_widget_t* widget,
                                       my_widget_state_t state,
                                       const char* key, char* out,
                                       size_t cap);

/** @brief R670/R673: evaluate a deferred @container condition for an
 * element — walk from `anchor` upward (inclusive) for the nearest
 * qualifying ancestor. Size queries require a query container
 * (container-type size/inline-size) and evaluate against its layout
 * rect; style() queries accept any ancestor and compare the custom
 * property value as raw text. When `container_name` is non-empty the
 * ancestor must also carry that name. Implemented in my_css.c. */
bool my_theme_container_matches(const my_theme_t* theme,
                                const struct my_widget_t* anchor,
                                const char* container_query,
                                const char* container_name);

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
 * @return MY_RET_OK, or an error when a line is invalid or allocation fails.
 */
my_ret_t my_theme_load_str(my_theme_t* theme, const char* str);

#endif /* MY_THEME_H */
