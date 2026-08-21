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
 *    "any ancestor of that type" (no full path); comma groups. NOT
 *    supported: `A > B` child combinator, `.class#id` combined
 *    class+id without type, multiple classes on one selector,
 *    pseudo other than the three above, `*`.
 *  - Declaration values: colors `#rgb`/`#rrggbb`/`#rrggbbaa`/
 *    `rgb(r,g,b)`/`rgba(r,g,b,a)` (alpha 0-1 float or 0-255 int), named
 * declaration values: colors `#rgb`/`#rrggbb`/`#rrggbbaa`/
 *    `rgb(r,g,b)`/`rgba(r,g,b,a)` (alpha 0-1 float or 0-255 int), named
 *    colors (red green blue white black gray/grey orange yellow purple
 *    pink cyan transparent), sizes `Npx`/integers, floats, quoted
 *    strings; other identifiers pass through as strings.
 *  - Cascade: a pseudo rule is more specific than a bare rule at any
 *    source position (bare rules write only the NORMAL slot and the
 *    state->normal fallback covers the rest — so `button:hover` always
 *    beats `button` for hover, matching real CSS specificity);
 *    same-specificity later writes override earlier ones (source
 *    order).
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
  char style_class[MY_CSS_NAME_LEN]; /**< "" = none (one class word) */
  char ancestor_type[MY_CSS_TYPE_LEN]; /**< "" = none (descendant: any
                                        * ancestor of this type) */
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

/** @brief Parse a CSS subset sheet. NULL on structural error (err
 * filled). Declaration-level problems only warn + skip. */
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
 * theme entries (type/id/class/ancestor,state); no-pseudo writes all
 * four states. Key aliases: background-color→bg_color, color→fg_color,
 * border-color→border_color, border-width→border_width,
 * border-radius→round_radius, font-size→font_size; other keys pass
 * through unchanged. Later rules override earlier ones (source order),
 * and CSS coexists with the text format (same-key later write wins).
 */
my_ret_t my_theme_load_css(my_theme_t* theme, const char* css);

#endif /* MY_CSS_H */
