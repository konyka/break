/**
 * @file my_css.h
 * @brief CSS subset parser + theme bridge (M18a).
 *
 * Subset (boundaries are deliberate; everything else is an error or a
 * skip-with-warning in compatibility mode, see docs/css.md):
 *  - Rules: `selector[, selector...] { key: value; ... }`, C comments.
 *    `@media all` and `@media screen` are flattened while parsing; bounded
 *    conditional media is evaluated by my_css_parse_media_ex(), including
 *    `width >= 800px` and `400px <= width < 800px` range predicates, while all
 *    bounded quoted `@import` can be expanded through an explicit resolver;
 *    other @rules are skipped whole with a warning by the default parser and
 *    bounded `@supports` boolean expressions are evaluated while parsing for
 *    supported style keys; strict mode rejects unsupported at-rules.
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

#include <stdint.h>

#include "myc/my_value.h"
#include "myui/my_style.h"
#include "myui/my_theme.h"

#define MY_CSS_TYPE_LEN 24
#define MY_CSS_NAME_LEN 32
#define MY_CSS_MAX_BYTES (4u * 1024u * 1024u)
#define MY_CSS_MAX_ANCESTORS 4u
#define MY_CSS_MAX_AT_RULE_NESTING 4u
#define MY_CSS_MAX_MEDIA_QUERY_BYTES 256u
#define MY_CSS_MAX_SUPPORTS_QUERY_BYTES 256u
#define MY_CSS_MAX_SUPPORTS_NESTING 4u
#define MY_CSS_MAX_LAYERS 64u
#define MY_CSS_MAX_LAYER_NAME_BYTES 128u
#define MY_CSS_MAX_IMPORT_DEPTH 8u
#define MY_CSS_MAX_IMPORTS 64u
#define MY_CSS_MAX_IMPORT_PATH_BYTES 256u
#define MY_CSS_MAX_SCOPE_NESTING 4u
#define MY_CSS_SCOPE_ROOT_IMPLICIT MY_CSS_MAX_ANCESTORS
#define MY_CSS_LAYER_SPECIFICITY_STRIDE 100000
#define MY_CSS_UNLAYERED_ORDER UINT32_MAX

typedef enum my_css_parse_flags_t {
  MY_CSS_PARSE_DEFAULT = 0u,
  MY_CSS_PARSE_STRICT_AT_RULES = 1u << 0
} my_css_parse_flags_t;

/** @brief Features implemented by this bounded CSS subset. */
typedef enum my_css_feature_t {
  MY_CSS_FEATURE_RULES = 1u << 0,
  MY_CSS_FEATURE_SELECTORS = 1u << 1,
  MY_CSS_FEATURE_TYPED_VALUES = 1u << 2,
  MY_CSS_FEATURE_CASCADE = 1u << 3,
  MY_CSS_FEATURE_AT_RULES = 1u << 4,
  MY_CSS_FEATURE_CONDITIONAL_MEDIA = 1u << 5,
  MY_CSS_FEATURE_SUPPORTS = 1u << 6,
  MY_CSS_FEATURE_LAYERS = 1u << 7,
  MY_CSS_FEATURE_IMPORTS = 1u << 8,
  MY_CSS_FEATURE_SCOPE = 1u << 9
} my_css_feature_t;

/** @brief Device capabilities available to conditional media evaluation. */
typedef enum my_css_media_capability_t {
  MY_CSS_MEDIA_CAP_HOVER = 1u << 0,
  MY_CSS_MEDIA_CAP_POINTER_COARSE = 1u << 1,
  MY_CSS_MEDIA_CAP_POINTER_FINE = 1u << 2,
  MY_CSS_MEDIA_CAP_ANY_POINTER_COARSE = 1u << 3,
  MY_CSS_MEDIA_CAP_ANY_POINTER_FINE = 1u << 4,
  MY_CSS_MEDIA_CAP_COLOR_SRGB = 1u << 5,
  MY_CSS_MEDIA_CAP_COLOR_P3 = 1u << 6,
  MY_CSS_MEDIA_CAP_COLOR_REC2020 = 1u << 7,
  MY_CSS_MEDIA_CAP_HDR = 1u << 8
} my_css_media_capability_t;

#define MY_CSS_MEDIA_CAP_ALL ((uint32_t)(MY_CSS_MEDIA_CAP_HOVER | \
                                         MY_CSS_MEDIA_CAP_POINTER_COARSE | \
                                         MY_CSS_MEDIA_CAP_POINTER_FINE | \
                                         MY_CSS_MEDIA_CAP_ANY_POINTER_COARSE | \
                                         MY_CSS_MEDIA_CAP_ANY_POINTER_FINE | \
                                         MY_CSS_MEDIA_CAP_COLOR_SRGB | \
                                         MY_CSS_MEDIA_CAP_COLOR_P3 | \
                                         MY_CSS_MEDIA_CAP_COLOR_REC2020 | \
                                         MY_CSS_MEDIA_CAP_HDR))

/** @brief Media facts for which the platform also knows the negative state. */
typedef enum my_css_media_known_t {
  MY_CSS_MEDIA_KNOWN_HOVER = 1u << 0,
  MY_CSS_MEDIA_KNOWN_POINTER = 1u << 1,
  MY_CSS_MEDIA_KNOWN_ANY_POINTER = 1u << 2,
  MY_CSS_MEDIA_KNOWN_COLOR_GAMUT = 1u << 3,
  MY_CSS_MEDIA_KNOWN_HDR = 1u << 4,
  MY_CSS_MEDIA_KNOWN_COLOR_SCHEME = 1u << 5,
  MY_CSS_MEDIA_KNOWN_REDUCED_MOTION = 1u << 6
} my_css_media_known_t;

#define MY_CSS_MEDIA_KNOWN_ALL ((uint32_t)(MY_CSS_MEDIA_KNOWN_HOVER | \
                                           MY_CSS_MEDIA_KNOWN_POINTER | \
                                           MY_CSS_MEDIA_KNOWN_ANY_POINTER | \
                                           MY_CSS_MEDIA_KNOWN_COLOR_GAMUT | \
                                           MY_CSS_MEDIA_KNOWN_HDR | \
                                           MY_CSS_MEDIA_KNOWN_COLOR_SCHEME | \
                                           MY_CSS_MEDIA_KNOWN_REDUCED_MOTION))

/** @brief Runtime facts captured once before parsing a CSS sheet. */
typedef struct my_css_media_context_t {
  uint32_t viewport_width_px;
  uint32_t viewport_height_px;
  bool screen;
  bool prefers_dark;
  bool prefers_reduced_motion;
  uint32_t capabilities;
} my_css_media_context_t;

/** @brief Extended media context with explicit fact knowledge. */
typedef struct my_css_media_context_ex_t {
  my_css_media_context_t base;
  uint32_t known;
} my_css_media_context_ex_t;

/** @brief Stable machine-readable CSS parse/bridge failure category. */
typedef enum my_css_error_code_t {
  MY_CSS_ERROR_NONE = 0,
  MY_CSS_ERROR_INVALID_PARAMS,
  MY_CSS_ERROR_INPUT_LIMIT,
  MY_CSS_ERROR_UNKNOWN_POLICY,
  MY_CSS_ERROR_UNSUPPORTED_FEATURE,
  MY_CSS_ERROR_SYNTAX,
  MY_CSS_ERROR_OOM,
  MY_CSS_ERROR_IMPORT
} my_css_error_code_t;

/** @brief Imported source returned by a resolver during parsing. */
typedef struct my_css_import_source_t {
  const char* css;
  size_t len;
  void (*release)(void* context, const char* css, size_t len);
  void* release_context;
} my_css_import_source_t;

/** @brief Resolve one quoted @import path on the parser's cold path. */
typedef bool (*my_css_import_resolver_fn_t)(
    void* context, const char* path, size_t path_len,
    my_css_import_source_t* source);

/** @brief Optional parser extensions; all imported sources remain bounded. */
typedef struct my_css_parse_options_t {
  uint32_t flags;
  const my_css_media_context_ex_t* media;
  my_css_import_resolver_fn_t resolve_import;
  void* import_context;
} my_css_parse_options_t;

/** @brief Immutable parser capability registry. */
typedef struct my_css_capabilities_t {
  uint32_t supported_features;
  uint32_t supported_parse_flags;
  size_t max_bytes;
  size_t max_ancestors;
} my_css_capabilities_t;


/** @brief Return the process-wide immutable CSS capability registry. */
const my_css_capabilities_t* my_css_capabilities(void);

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
  my_css_error_code_t code;
  uint32_t capability; /**< Missing or relevant my_css_feature_t bit. */
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
  u32 scope_limit_count;
  my_css_ancestor_t scope_limits[MY_CSS_MAX_SCOPE_NESTING];
  u32 scope_limit_root_index[MY_CSS_MAX_SCOPE_NESTING];
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
  uint32_t layer_order; /**< UINT32_MAX for unlayered, otherwise declaration rank */
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

/** @brief Parse with explicit policy flags. Strict at-rule mode accepts only
 * supported `@media`/`@supports`/`@layer`/`@import`/`@scope` containers and
 * rejects every other @-rule
 * instead of skipping it with a warning. At-rule nesting is bounded by
 * MY_CSS_MAX_AT_RULE_NESTING. `@supports` accepts bounded `and`/`or`/`not`
 * expressions over parenthesized `property: value` queries and is evaluated
 * while parsing. Bounded `@layer` blocks and order statements are flattened
 * while parsing. A bounded `@scope simple-selector [to selector-list] { ... }`
 * form applies descendant rules through the existing fixed ancestor path;
 * the omitted-root form is represented by a fixed internal boundary sentinel
 * and selector lists are capped by MY_CSS_MAX_SCOPE_NESTING. */
my_css_sheet_t* my_css_parse_ex(const my_allocator_t* allocator,
                                const char* css, size_t len,
                                uint32_t flags, my_css_error_t* err);

/** @brief Parse with bounded conditional-media evaluation at load time.
 * Supported predicates are media type (`all`/`screen`), width/height
 * min/max/exact in px, CSS range comparisons in px, orientation,
 * prefers-color-scheme, prefers-reduced-motion, hover/pointer, color-gamut
 * and dynamic-range. Matching rules are
 * flattened; nonmatching blocks
 * are discarded, so theme lookup remains independent of viewport state. */
my_css_sheet_t* my_css_parse_media_ex(
    const my_allocator_t* allocator, const char* css, size_t len,
    uint32_t flags, const my_css_media_context_t* media,
    my_css_error_t* err);

/** @brief Extended media parser; supports explicit known/unknown facts. */
my_css_sheet_t* my_css_parse_media_ex2(
    const my_allocator_t* allocator, const char* css, size_t len,
    uint32_t flags, const my_css_media_context_ex_t* media,
    my_css_error_t* err);

/** @brief Parse with conditional media and an optional bounded import resolver. */
my_css_sheet_t* my_css_parse_with_options(
    const my_allocator_t* allocator, const char* css, size_t len,
    const my_css_parse_options_t* options, my_css_error_t* err);

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

/** @brief Load CSS with the same explicit parser policy used by
 * my_css_parse_ex(). Parsing, cloning, or applying failure leaves the theme
 * untouched. */
my_ret_t my_theme_load_css_ex(my_theme_t* theme, const char* css,
                              uint32_t flags);

/** @brief Load CSS after evaluating conditional media at parse time. */
my_ret_t my_theme_load_css_media_ex(
    my_theme_t* theme, const char* css, uint32_t flags,
    const my_css_media_context_t* media);

/** @brief Extended media theme loader with explicit known/unknown facts. */
my_ret_t my_theme_load_css_media_ex2(
    my_theme_t* theme, const char* css, uint32_t flags,
    const my_css_media_context_ex_t* media);

/** @brief Load CSS with a bounded import resolver transactionally. */
my_ret_t my_theme_load_css_with_options(
    my_theme_t* theme, const char* css,
    const my_css_parse_options_t* options);

#endif /* MY_CSS_H */
