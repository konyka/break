/**
 * @file my_css.h
 * @brief CSS subset parser + theme bridge (M18a).
 *
 * Subset (boundaries are deliberate; everything else is an error or a
 * skip-with-warning, see docs/css.md):
 *  - Rules: `selector[, selector...] { key: value; ... }`, C comments.
 *    @rules (@media/@import/...) are skipped whole with a warning.
 *  - Selector items: `type` / `.class` / `#id` / `type.class` /
 *    `type#id`; optional pseudo `:hover`/`:pressed`/`:disabled` (none =
 *    all four states); `type type2...` descendant is SIMPLIFIED to
 *    bounded descendant paths (up to MY_CSS_MAX_ANCESTORS); comma groups.
 *    `>` direct-child combinators may be chained, and ancestor components
 *    support type/class/id. Multiple classes are stored as a required class
 *    set. Pseudos other than the three above are rejected; ancestor pseudos
 *    are rejected because ancestor state is not part of the theme lookup key.
 *  - Declaration values: colors `#rgb`/`#rrggbb`/`#rrggbbaa`/
 *    `rgb(r,g,b)`/`rgba(r,g,b,a)` (alpha 0-1 float or 0-255 int), named
 *    colors (red green blue white black gray/grey orange yellow purple
 *    pink cyan transparent), sizes `Npx`/integers, floats, quoted strings;
 *    other identifiers pass through as strings.
 *  - Cascade: selector specificity is compared before source order. A bare
 *    rule writes only the NORMAL slot; state lookups use that slot only when
 *    the requested state has no property, and retain the normal rule's
 *    specificity. Same-specificity later writes override earlier ones.
 *  - A malformed declaration is SKIPPED with a warning (lenient mode);
 *    a malformed selector/rule structure is a hard error with line/col.
 */
#ifndef MY_CSS_H
#define MY_CSS_H

#include "myc/my_value.h"
#include "myui/my_style.h"
#include "myui/my_theme.h"

#define MY_CSS_TYPE_LEN 24
#define MY_CSS_NAME_LEN 32
#define MY_CSS_MAX_BYTES (4u * 1024u * 1024u)
#define MY_CSS_MAX_ANCESTORS 4u

/** @brief One ancestor component in a bounded selector path. */
typedef struct my_css_ancestor_t {
  char widget_type[MY_CSS_TYPE_LEN];
  char id[MY_CSS_NAME_LEN];
  char style_class[MY_CSS_NAME_LEN];
} my_css_ancestor_t;

/** @brief Parse/bridge error with 1-based position. */
typedef struct my_css_error_t {
  int32_t line;
  int32_t col;
  char msg[96];
} my_css_error_t;

/** @brief One parsed selector (already decomposed). */
typedef struct my_css_selector_t {
  char widget_type[MY_CSS_TYPE_LEN]; /**< "" = any type */
  char id[MY_CSS_NAME_LEN];          /**< "" = none (#id == widget name) */
  char style_class[MY_CSS_NAME_LEN]; /**< space-separated required classes */
  char ancestor_type[MY_CSS_TYPE_LEN]; /**< legacy single-ancestor view */
  bool ancestor_direct; /**< direct-child combinator (`A > B`) */
  u32 ancestor_count; /**< bounded path length; zero keeps legacy fields */
  my_css_ancestor_t ancestors[MY_CSS_MAX_ANCESTORS];
  bool ancestor_direct_path[MY_CSS_MAX_ANCESTORS];
  int32_t state; /**< -1 = all states; else my_widget_state_t */
} my_css_selector_t;

/** @brief One declaration (value typed: UINT32 color / INT32 / DOUBLE / STR). */
typedef struct my_css_decl_t {
  char key[MY_STYLE_KEY_LEN];
  my_value_t value;
} my_css_decl_t;

/** @brief One rule: selector group + declarations. */
typedef struct my_css_rule_t {
  my_darray_t* selectors; /**< my_css_selector_t* */
  my_darray_t* decls;     /**< my_css_decl_t* */
} my_css_rule_t;

/** @brief Parsed sheet (opaque-ish; use the accessors). */
typedef struct my_css_sheet_t {
  const my_allocator_t* allocator;
  my_darray_t* rules; /**< my_css_rule_t* */
} my_css_sheet_t;

/** @brief Parse a CSS subset sheet within MY_CSS_MAX_BYTES. NULL on
 * structural or budget error (err filled when non-NULL). Declaration-level
 * problems only warn + skip. */
my_css_sheet_t* my_css_parse(const my_allocator_t* allocator,
                             const char* css, size_t len,
                             my_css_error_t* err);

void my_css_sheet_destroy(my_css_sheet_t* sheet);

size_t my_css_rule_count(const my_css_sheet_t* sheet);
const my_css_rule_t* my_css_rule(const my_css_sheet_t* sheet, size_t index);
size_t my_css_selector_count(const my_css_rule_t* rule);
const my_css_selector_t* my_css_selector(const my_css_rule_t* rule,
                                         size_t index);
size_t my_css_decl_count(const my_css_rule_t* rule);
const my_css_decl_t* my_css_decl(const my_css_rule_t* rule, size_t index);

/* ---------------- theme bridge ---------------- */

/**
 * @brief Load a CSS sheet into the theme. Selectors map to extended
 * theme entries (type/id/class/ancestor,state); no-pseudo writes the
 * NORMAL slot and relies on state fallback. Key aliases:
 * background-color→bg_color, color→fg_color,
 * border-color→border_color, border-width→border_width,
 * border-radius→round_radius, font-size→font_size; other keys pass
 * through unchanged. Later rules override earlier ones (source order),
 * and CSS coexists with the text format (same-key later write wins).
 */
my_ret_t my_theme_load_css(my_theme_t* theme, const char* css);

#endif /* MY_CSS_H */
