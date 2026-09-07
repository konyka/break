/**
 * @file my_css.c
 * @brief CSS subset parser + theme bridge (M18a) — subset spec in
 * my_css.h / docs/css.md.
 */
#include "myui/my_css.h"

#include <errno.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#include "myc/my_str.h"

/* ---------------- lexer-ish helpers ---------------- */

typedef struct css_p_t {
  const my_allocator_t* allocator;
  const char* s;
  size_t len;
  size_t pos;
  int32_t line;
  int32_t col;
  my_css_error_t* err;
  uint32_t flags;
  const my_css_media_context_ex_t* media;
  bool failed;
  my_css_import_resolver_fn_t resolve_import;
  void* import_context;
  size_t import_total_bytes;
  size_t import_count;
  size_t import_depth;
  char import_stack[MY_CSS_MAX_IMPORT_DEPTH]
                   [MY_CSS_MAX_IMPORT_PATH_BYTES + 1u];
  my_css_selector_t scope_selectors[MY_CSS_MAX_SCOPE_NESTING];
  bool scope_has_root[MY_CSS_MAX_SCOPE_NESTING];
  size_t scope_count;
  char layer_names[MY_CSS_MAX_LAYERS][MY_CSS_MAX_LAYER_NAME_BYTES + 1u];
  uint32_t layer_ranks[MY_CSS_MAX_LAYERS];
  size_t layer_count;
} css_p_t;

static my_css_error_code_t css_error_code_for(const char* msg) {
  if (strcmp(msg, "oom") == 0) {
    return MY_CSS_ERROR_OOM;
  }
  if (strcmp(msg, "CSS input exceeds resource budget") == 0) {
    return MY_CSS_ERROR_INPUT_LIMIT;
  }
  if (strcmp(msg, "unknown CSS parse flags") == 0) {
    return MY_CSS_ERROR_UNKNOWN_POLICY;
  }
  if (strcmp(msg, "CSS import resolution failed") == 0 ||
      strcmp(msg, "CSS import cycle detected") == 0 ||
      strcmp(msg, "CSS import depth exceeded") == 0 ||
      strcmp(msg, "CSS import limit exceeded") == 0 ||
      strcmp(msg, "invalid CSS import path") == 0 ||
      strcmp(msg, "CSS import path too long") == 0) {
    return MY_CSS_ERROR_IMPORT;
  }
  if (strcmp(msg, "CSS scope nesting depth exceeded") == 0 ||
      strcmp(msg, "scope ancestor depth exceeded") == 0) {
    return MY_CSS_ERROR_UNSUPPORTED_FEATURE;
  }
  if (strcmp(msg, "unsupported @-rule") == 0) {
    return MY_CSS_ERROR_UNSUPPORTED_FEATURE;
  }
  return MY_CSS_ERROR_SYNTAX;
}

static void css_fail(css_p_t* p, const char* msg) {
  p->failed = true;
  if (p->err != NULL && p->err->msg[0] == '\0') {
    p->err->line = p->line;
    p->err->col = p->col;
    p->err->code = css_error_code_for(msg);
    if (strcmp(msg, "unsupported @-rule") == 0) {
      p->err->capability = (uint32_t)MY_CSS_FEATURE_AT_RULES;
    } else if (strcmp(msg, "CSS scope nesting depth exceeded") == 0 ||
               strcmp(msg, "scope ancestor depth exceeded") == 0 ||
               strcmp(msg, "@scope nesting depth exceeded") == 0 ||
               strcmp(msg, "invalid @scope root selector") == 0 ||
               strcmp(msg, "invalid @scope limit selector") == 0 ||
               strcmp(msg, "unsupported @scope syntax") == 0) {
      p->err->capability = (uint32_t)MY_CSS_FEATURE_SCOPE;
    } else {
      p->err->capability = 0u;
    }
    snprintf(p->err->msg, sizeof(p->err->msg), "%s", msg);
  }
}

static void css_mark_scope_error(css_p_t* p) {
  if (p->err != NULL && p->err->msg[0] != '\0') {
    p->err->capability = (uint32_t)MY_CSS_FEATURE_SCOPE;
  }
}

static int c_peek(css_p_t* p) {
  return p->pos < p->len ? (unsigned char)p->s[p->pos] : -1;
}

static int c_next(css_p_t* p) {
  int c = c_peek(p);
  if (c >= 0) {
    p->pos++;
    if (c == '\n') {
      p->line++;
      p->col = 1;
    } else {
      p->col++;
    }
  }
  return c;
}

static bool c_failed(css_p_t* p) {
  return p->failed;
}

/** @brief Whitespace + comments. Returns true for actual whitespace, which
 * is significant as the descendant combinator; comments alone are not. */
static bool c_ws(css_p_t* p) {
  bool separated = false;
  for (;;) {
    int c = c_peek(p);
    if (c == ' ' || c == '\t' || c == '\n' || c == '\r') {
      separated = true;
      c_next(p);
      continue;
    }
    if (c == '/' && p->pos + 1 < p->len && p->s[p->pos + 1] == '*') {
      separated = true;
      c_next(p);
      c_next(p);
      while (c_peek(p) >= 0 &&
             !(c_peek(p) == '*' && p->pos + 1 < p->len &&
               p->s[p->pos + 1] == '/')) {
        c_next(p);
      }
      if (c_peek(p) < 0) {
        css_fail(p, "unterminated comment");
        return separated;
      }
      c_next(p);
      c_next(p);
      continue;
    }
    break;
  }
  return separated;
}

static bool c_ident_char(int c) {
  return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') ||
         (c >= '0' && c <= '9') || c == '_' || c == '-';
}

/** @brief Read an identifier into out (NUL-terminated). */
static bool c_ident(css_p_t* p, char* out, size_t cap) {
  size_t n = 0;
  while (c_ident_char(c_peek(p))) {
    if (n + 1 >= cap) {
      css_fail(p, "identifier too long");
      return false;
    }
    out[n++] = (char)c_next(p);
  }
  out[n] = '\0';
  return n > 0;
}

static bool css_number(css_p_t* p, double* out, bool* integral) {
  size_t start = p->pos;
  size_t n;
  size_t digits_before = 0;
  size_t digits_after = 0;
  size_t exponent_digits = 0;
  char token[64];
  char* end;
  int c;

  c = c_peek(p);
  if (c == '+' || c == '-') {
    c_next(p);
  }
  while ((c = c_peek(p)) >= '0' && c <= '9') {
    digits_before++;
    c_next(p);
  }
  if (c_peek(p) == '.') {
    c_next(p);
    while ((c = c_peek(p)) >= '0' && c <= '9') {
      digits_after++;
      c_next(p);
    }
  }
  if (digits_before == 0 && digits_after == 0) {
    p->pos = start;
    return false;
  }
  if (c_peek(p) == 'e' || c_peek(p) == 'E') {
    c_next(p);
    c = c_peek(p);
    if (c == '+' || c == '-') {
      c_next(p);
    }
    while ((c = c_peek(p)) >= '0' && c <= '9') {
      exponent_digits++;
      c_next(p);
    }
    if (exponent_digits == 0) {
      p->pos = start;
      return false;
    }
  }
  n = p->pos - start;
  if (n >= sizeof(token)) {
    p->pos = start;
    return false;
  }
  memcpy(token, p->s + start, n);
  token[n] = '\0';
  errno = 0;
  *out = strtod(token, &end);
  if (end == token || *end != '\0' || errno == ERANGE || !isfinite(*out)) {
    p->pos = start;
    return false;
  }
  if (integral != NULL) {
    *integral = digits_after == 0 && exponent_digits == 0;
  }
  return true;
}

/* ---------------- selectors ---------------- */

/** @brief One selector item, e.g. `button.primary:hover`. */
static bool c_selector(css_p_t* p, my_css_selector_t* out) {
  bool universal = false;

  memset(out, 0, sizeof(*out));
  out->state = -1;
  if (c_peek(p) == '*') {
    c_next(p);
    universal = true;
  }
  /* type (optional, leading ident) */
  if (c_ident_char(c_peek(p)) && c_peek(p) != '-') {
    /* note: classes start with '.', ids with '#' — plain ident = type */
    if (!c_ident(p, out->widget_type, sizeof(out->widget_type))) {
      css_fail(p, "expected selector");
      return false;
    }
  }
  if (c_peek(p) == '-') { /* idents may not START with '-' here */
    css_fail(p, "bad selector");
    return false;
  }
  /* .class / #id components; classes are stored as a required set.
   * Components are ADJACENT in CSS — no whitespace allowed (whitespace
   * is the descendant combinator, significant). */
  while (c_peek(p) == '.' || c_peek(p) == '#') {
    int kind = c_next(p);
    char buf[MY_CSS_NAME_LEN];
    if (!c_ident(p, buf, sizeof(buf))) {
      css_fail(p, "bad selector component");
      return false;
    }
    if (kind == '.') {
      size_t have = strlen(out->style_class);
      size_t need = strlen(buf);
      if (have > 0) {
        if (have + 1 + need >= sizeof(out->style_class)) {
          css_fail(p, "selector classes too long");
          return false;
        }
        out->style_class[have++] = ' ';
      } else if (need >= sizeof(out->style_class)) {
        css_fail(p, "selector class too long");
        return false;
      }
      memcpy(out->style_class + have, buf, need + 1);
    } else {
      if (out->id[0] != '\0') {
        css_fail(p, "multiple ids on one selector");
        return false;
      }
      snprintf(out->id, sizeof(out->id), "%s", buf);
    }
  }
  if (out->widget_type[0] == '\0' && out->style_class[0] == '\0' &&
      out->id[0] == '\0' && c_peek(p) != ':' && !universal) {
    css_fail(p, "empty selector");
    return false;
  }
  /* pseudo */
  if (c_peek(p) == ':') {
    char pseudo[16];
    c_next(p);
    if (!c_ident(p, pseudo, sizeof(pseudo))) {
      css_fail(p, "bad pseudo class");
      return false;
    }
    if (my_str_eq(pseudo, "hover")) {
      out->state = MY_STATE_HOVER;
    } else if (my_str_eq(pseudo, "pressed")) {
      out->state = MY_STATE_PRESSED;
    } else if (my_str_eq(pseudo, "disabled")) {
      out->state = MY_STATE_DISABLED;
    } else {
      css_fail(p, "unsupported pseudo class");
      return false;
    }
  }
  return true;
}

static bool c_ancestor_copy(css_p_t* p, my_css_ancestor_t* ancestor,
                            const my_css_selector_t* selector) {
  if (selector->state != -1 || selector->widget_type[0] == '\0') {
    css_fail(p, "ancestor must have a type and no pseudo class");
    return false;
  }
  if (strlen(selector->id) >= sizeof(ancestor->id) ||
      strlen(selector->style_class) >= sizeof(ancestor->style_class)) {
    css_fail(p, "ancestor selector too long");
    return false;
  }
  snprintf(ancestor->widget_type, sizeof(ancestor->widget_type), "%s",
           selector->widget_type);
  snprintf(ancestor->id, sizeof(ancestor->id), "%s", selector->id);
  snprintf(ancestor->style_class, sizeof(ancestor->style_class), "%s",
           selector->style_class);
  return true;
}

/* ---------------- declaration values ---------------- */

typedef struct css_named_color_t {
  const char* name;
  uint32_t rgba;
} css_named_color_t;

static const css_named_color_t NAMED_COLORS[] = {
    {"red", 0xFF0000FFu},   {"green", 0x008000FFu},
    {"blue", 0x0000FFFFu},  {"white", 0xFFFFFFFFu},
    {"black", 0x000000FFu}, {"gray", 0x808080FFu},
    {"grey", 0x808080FFu},  {"orange", 0xFFA500FFu},
    {"yellow", 0xFFFF00FFu}, {"purple", 0x800080FFu},
    {"pink", 0xFFC0CBFFu},  {"cyan", 0x00FFFFFFu},
    {"transparent", 0x00000000u},
};

static bool css_named_color(const char* name, uint32_t* out) {
  size_t i;
  for (i = 0; i < sizeof(NAMED_COLORS) / sizeof(NAMED_COLORS[0]); i++) {
    if (my_str_eq(name, NAMED_COLORS[i].name)) {
      *out = NAMED_COLORS[i].rgba;
      return true;
    }
  }
  return false;
}

static int hex_digit(int c) {
  if (c >= '0' && c <= '9') return c - '0';
  if (c >= 'a' && c <= 'f') return c - 'a' + 10;
  if (c >= 'A' && c <= 'F') return c - 'A' + 10;
  return -1;
}

/** @brief #rgb / #rrggbb / #rrggbbaa -> rgba32. */
static bool css_hex_color(css_p_t* p, uint32_t* out) {
  size_t start;
  size_t n;
  size_t i;
  c_next(p); /* '#' */
  start = p->pos;
  while (hex_digit(c_peek(p)) >= 0) {
    c_next(p);
  }
  n = p->pos - start;
  if (n != 3 && n != 6 && n != 8) {
    return false;
  }
  if (n == 3) {
    uint32_t r = (uint32_t)hex_digit(p->s[start]);
    uint32_t g = (uint32_t)hex_digit(p->s[start + 1]);
    uint32_t b = (uint32_t)hex_digit(p->s[start + 2]);
    *out = (r << 28) | (r << 24) | (g << 20) | (g << 16) | (b << 12) |
           (b << 8) | 0xFFu;
    return true;
  }
  {
    uint32_t v = 0;
    for (i = 0; i < n; i++) {
      v = (v << 4) | (uint32_t)hex_digit(p->s[start + i]);
    }
    if (n == 6) {
      v = (v << 8) | 0xFFu;
    }
    *out = v;
    return true;
  }
}

/** @brief rgb()/rgba() component list (fn already read; alpha: 0-1
 * float or 0-255). */
static bool css_func_color(css_p_t* p, const char* fn, uint32_t* out) {
  bool has_alpha;
  double comp[4] = {0, 0, 0, 1.0};
  int n = 0;
  has_alpha = my_str_eq(fn, "rgba");
  if (c_peek(p) != '(') {
    return false;
  }
  c_next(p);
  for (n = 0; n < (has_alpha ? 4 : 3); n++) {
    bool integral;
    c_ws(p);
    if (!css_number(p, &comp[n], &integral)) {
      return false;
    }
    (void)integral;
    c_ws(p);
    if (n + 1 < (has_alpha ? 4 : 3)) {
      if (c_peek(p) != ',') {
        return false;
      }
      c_next(p);
    }
  }
  if (c_peek(p) != ')') {
    return false;
  }
  c_next(p);
  {
    uint32_t r = comp[0] < 0 ? 0 : comp[0] > 255 ? 255 : (uint32_t)comp[0];
    uint32_t g = comp[1] < 0 ? 0 : comp[1] > 255 ? 255 : (uint32_t)comp[1];
    uint32_t b = comp[2] < 0 ? 0 : comp[2] > 255 ? 255 : (uint32_t)comp[2];
    uint32_t a;
    if (!has_alpha) {
      a = 255;
    } else if (comp[3] <= 0.0) {
      a = 0;
    } else if (comp[3] <= 1.0) {
      a = (uint32_t)(comp[3] * 255.0 + 0.5); /* 0-1 float */
    } else {
      a = comp[3] > 255 ? 255 : (uint32_t)comp[3]; /* 0-255 */
    }
    *out = (r << 24) | (g << 16) | (b << 8) | a;
  }
  return true;
}

/** @brief Parse one declaration value -> my_value_t. Lenient: returns
 * false on garbage (caller skips + warns). */
static bool css_value(css_p_t* p, my_value_t* out) {
  int c = c_peek(p);
  if (c == '#') {
    uint32_t rgba;
    if (!css_hex_color(p, &rgba)) {
      return false;
    }
    my_value_set_uint32(out, rgba);
    return true;
  }
  if (c == '"' || c == '\'') {
    int q = c_next(p);
    size_t start = p->pos;
    size_t n;
    while (c_peek(p) >= 0 && c_peek(p) != q) {
      c_next(p);
    }
    if (c_peek(p) != q) {
      return false;
    }
    n = p->pos - start;
    c_next(p);
    {
      char* buf = (char*)my_mem_alloc(p->allocator, n + 1);
      if (buf == NULL) {
        return false;
      }
      memcpy(buf, p->s + start, n);
      buf[n] = '\0';
      my_value_set_str(out, buf);
      my_mem_free(p->allocator, buf);
    }
    return true;
  }
  if ((c >= '0' && c <= '9') || c == '-' || c == '+') {
    /* number [px] */
    double number;
    bool integral;
    if (!css_number(p, &number, &integral)) {
      return false;
    }
    if (integral) {
      if (number < (double)INT32_MIN || number > (double)INT32_MAX) {
        return false;
      }
      my_value_set_int32(out, (int32_t)number);
    } else {
      my_value_set_double(out, number);
    }
    /* optional px unit */
    if (c_peek(p) == 'p' && p->pos + 1 < p->len && p->s[p->pos + 1] == 'x') {
      c_next(p);
      c_next(p);
    }
    return true;
  }
  if (c_ident_char(c)) {
    char id[24];
    uint32_t rgba;
    if (!c_ident(p, id, sizeof(id))) {
      return false;
    }
    if ((my_str_eq(id, "rgb") || my_str_eq(id, "rgba")) &&
        c_peek(p) == '(') {
      if (!css_func_color(p, id, &rgba)) {
        return false;
      }
      my_value_set_uint32(out, rgba);
      return true;
    }
    if (css_named_color(id, &rgba)) {
      my_value_set_uint32(out, rgba);
      return true;
    }
    my_value_set_str(out, id); /* unknown identifier -> string */
    return true;
  }
  return false;
}

/* ---------------- key aliases ---------------- */

typedef struct css_alias_t {
  const char* css;
  const char* key;
} css_alias_t;

static const css_alias_t KEY_ALIASES[] = {
    {"background-color", MY_STYLE_BG_COLOR}, {"background", MY_STYLE_BG_COLOR},
    {"color", MY_STYLE_FG_COLOR},           {"border-color", MY_STYLE_BORDER_COLOR},
    {"border-width", MY_STYLE_BORDER_WIDTH}, {"border-radius", MY_STYLE_ROUND_RADIUS},
    {"font-size", MY_STYLE_FONT_SIZE},
};

static void css_key_map(const char* key, char* out, size_t cap) {
  size_t i;
  for (i = 0; i < sizeof(KEY_ALIASES) / sizeof(KEY_ALIASES[0]); i++) {
    if (my_str_eq(key, KEY_ALIASES[i].css)) {
      snprintf(out, cap, "%s", KEY_ALIASES[i].key);
      return;
    }
  }
  snprintf(out, cap, "%s", key);
}

/* ---------------- rule parser ---------------- */

static my_css_rule_t* css_rule_new(const my_allocator_t* allocator,
                                   uint32_t layer_order) {
  my_css_rule_t* r =
      (my_css_rule_t*)my_mem_calloc(allocator, 1, sizeof(my_css_rule_t));
  if (r == NULL) {
    return NULL;
  }
  r->layer_order = layer_order;
  r->selectors = my_darray_create(allocator, 0);
  r->decls = my_darray_create(allocator, 0);
  if (r->selectors == NULL || r->decls == NULL) {
    if (r->selectors != NULL) {
      my_darray_destroy(r->selectors);
    }
    if (r->decls != NULL) {
      my_darray_destroy(r->decls);
    }
    my_mem_free(allocator, r);
    return NULL;
  }
  return r;
}

static void css_rule_destroy(const my_allocator_t* allocator,
                             my_css_rule_t* r) {
  size_t i, n;
  if (r == NULL) {
    return;
  }
  n = my_darray_size(r->selectors);
  for (i = 0; i < n; i++) {
    my_mem_free(allocator, my_darray_get(r->selectors, i));
  }
  n = my_darray_size(r->decls);
  for (i = 0; i < n; i++) {
    my_css_decl_t* d = (my_css_decl_t*)my_darray_get(r->decls, i);
    my_value_reset(&d->value);
    my_mem_free(allocator, d);
  }
  my_darray_destroy(r->selectors);
  my_darray_destroy(r->decls);
  my_mem_free(allocator, r);
}

/** @brief @rule: skip to the end of its block (or ';'). */
static void css_skip_atrule(css_p_t* p, bool warn) {
  int depth = 0;
  char quote = '\0';
  if (warn) {
    MY_LOGW("my_css: skipping @-rule (unsupported)");
  }
  while (c_peek(p) >= 0) {
    int c = c_peek(p);
    if (quote != '\0') {
      c_next(p);
      if (c == '\\' && c_peek(p) >= 0) {
        c_next(p);
      } else if (c == quote) {
        quote = '\0';
      }
      continue;
    }
    if (c == '/' && p->pos + 1 < p->len && p->s[p->pos + 1] == '*') {
      c_next(p);
      c_next(p);
      while (c_peek(p) >= 0 &&
             !(c_peek(p) == '*' && p->pos + 1 < p->len &&
               p->s[p->pos + 1] == '/')) {
        c_next(p);
      }
      if (c_peek(p) < 0) {
        css_fail(p, "unterminated @-rule comment");
        return;
      }
      c_next(p);
      c_next(p);
      continue;
    }
    c = c_next(p);
    if (c == '\'' || c == '"') {
      quote = (char)c;
      continue;
    }
    if (c == '{') {
      depth++;
    } else if (c == '}') {
      depth--;
      if (depth == 0) {
        return;
      }
    } else if (c == ';' && depth == 0) {
      return;
    }
  }
  if (quote != '\0') {
    css_fail(p, "unterminated @-rule string");
  } else if (depth > 0) {
    css_fail(p, "unterminated @-rule");
  }
}

static bool css_parse_rules(css_p_t* p, my_css_sheet_t* sheet,
                            bool nested, size_t media_depth,
                            uint32_t layer_id);
static bool css_skip_or_reject_atrule_with_capability(
    css_p_t* p, uint32_t capability);
static bool css_media_capabilities_valid(
    const my_css_media_context_ex_t* media);

static bool css_read_import_path(css_p_t* p, char* path, size_t cap,
                                 size_t* path_len) {
  size_t length = 0u;
  int quote;

  c_ws(p);
  quote = c_peek(p);
  if (quote != '\'' && quote != '"') return false;
  c_next(p);
  while (c_peek(p) >= 0 && c_peek(p) != quote) {
    int c = c_next(p);
    if (c == '\\') {
      c = c_peek(p);
      if (c < 0) return false;
      c = c_next(p);
    }
    if (c < 0 || c == '\n' || c == '\r' || c == '\0') return false;
    if (length + 1u >= cap) {
      css_fail(p, "CSS import path too long");
      return false;
    }
    path[length++] = (char)c;
  }
  if (c_peek(p) != quote) return false;
  c_next(p);
  c_ws(p);
  if (c_peek(p) != ';') return false;
  c_next(p);
  path[length] = '\0';
  *path_len = length;
  return length > 0u;
}

static bool css_import_path_safe(const char* path, size_t length) {
  size_t start = 0u;
  size_t i;
  if (path == NULL || length == 0u || path[0] == '/' || path[0] == '\\') {
    return false;
  }
  for (i = 0u; i <= length; ++i) {
    if (i == length || path[i] == '/') {
      size_t segment_length = i - start;
      if (segment_length == 0u ||
          (segment_length == 1u && path[start] == '.') ||
          (segment_length == 2u && path[start] == '.' &&
           path[start + 1u] == '.')) {
        return false;
      }
      start = i + 1u;
      continue;
    }
    if (path[i] == '\\' || path[i] == ':' ||
        (unsigned char)path[i] < 0x20u) {
      return false;
    }
  }
  return true;
}

static bool css_parse_import_atrule(css_p_t* p, my_css_sheet_t* sheet,
                                    size_t media_depth, uint32_t layer_id) {
  char path[MY_CSS_MAX_IMPORT_PATH_BYTES + 1u];
  my_css_import_source_t source;
  const char* old_s;
  size_t old_len, old_pos, path_len;
  int32_t old_line, old_col;
  size_t i;
  bool parsed;

  if (!css_read_import_path(p, path, sizeof(path), &path_len)) {
    return css_skip_or_reject_atrule_with_capability(
        p, (uint32_t)MY_CSS_FEATURE_IMPORTS);
  }
  if (!css_import_path_safe(path, path_len)) {
    css_fail(p, "invalid CSS import path");
    return false;
  }
  if (p->resolve_import == NULL) {
    if ((p->flags & MY_CSS_PARSE_STRICT_AT_RULES) != 0u) {
      p->failed = true;
      if (p->err != NULL && p->err->msg[0] == '\0') {
        p->err->line = p->line;
        p->err->col = p->col;
        p->err->code = MY_CSS_ERROR_UNSUPPORTED_FEATURE;
        p->err->capability = (uint32_t)MY_CSS_FEATURE_IMPORTS;
        snprintf(p->err->msg, sizeof(p->err->msg), "%s",
                 "unsupported @-rule");
      }
      return false;
    }
    MY_LOGW("my_css: skipping @import without resolver");
    return true;
  }
  if (p->import_depth >= MY_CSS_MAX_IMPORT_DEPTH) {
    css_fail(p, "CSS import depth exceeded");
    return false;
  }
  if (p->import_count >= MY_CSS_MAX_IMPORTS) {
    css_fail(p, "CSS import limit exceeded");
    return false;
  }
  for (i = 0u; i < p->import_depth; ++i) {
    if (strcmp(p->import_stack[i], path) == 0) {
      css_fail(p, "CSS import cycle detected");
      return false;
    }
  }
  memset(&source, 0, sizeof(source));
  if (!p->resolve_import(p->import_context, path, path_len, &source)) {
    css_fail(p, "CSS import resolution failed");
    return false;
  }
  if ((source.css == NULL && source.len != 0u) ||
      source.len > MY_CSS_MAX_BYTES ||
      source.len > MY_CSS_MAX_BYTES - p->import_total_bytes) {
    if (source.release != NULL) {
      source.release(source.release_context, source.css, source.len);
    }
    css_fail(p, "CSS input exceeds resource budget");
    return false;
  }
  p->import_total_bytes += source.len;
  p->import_count++;
  snprintf(p->import_stack[p->import_depth],
           sizeof(p->import_stack[p->import_depth]), "%s", path);
  old_s = p->s;
  old_len = p->len;
  old_pos = p->pos;
  old_line = p->line;
  old_col = p->col;
  p->s = source.css != NULL ? source.css : "";
  p->len = source.len;
  p->pos = 0u;
  p->line = 1;
  p->col = 1;
  p->import_depth++;
  parsed = css_parse_rules(p, sheet, false, media_depth, layer_id);
  p->import_depth--;
  p->s = old_s;
  p->len = old_len;
  p->pos = old_pos;
  p->line = old_line;
  p->col = old_col;
  if (source.release != NULL) {
    source.release(source.release_context, source.css, source.len);
  }
  return parsed;
}

/** @brief One rule: selectors { declarations }. */
static my_css_rule_t* css_rule(css_p_t* p, uint32_t layer_id) {
  my_css_rule_t* r = css_rule_new(p->allocator, layer_id);
  my_css_selector_t compounds[MY_CSS_MAX_ANCESTORS + 1u];
  bool direct_between[MY_CSS_MAX_ANCESTORS + 1u];
  size_t compound_count = 0;
  bool pending_direct = false;
  if (r == NULL) {
    css_fail(p, "oom");
    return NULL;
  }
  /* selector group */
  for (;;) {
    my_css_selector_t sel;
    my_css_selector_t* slot;
    bool separated;
    size_t i;
    c_ws(p);
    if (c_failed(p)) {
      goto fail;
    }
    if (!c_selector(p, &sel)) {
      goto fail;
    }
    if (compound_count >= sizeof(compounds) / sizeof(compounds[0])) {
      css_fail(p, "selector ancestor depth exceeded");
      goto fail;
    }
    if (compound_count > 0u) {
      direct_between[compound_count] = pending_direct;
    }
    compounds[compound_count++] = sel;
    separated = c_ws(p);
    if (c_peek(p) == '>') {
      c_next(p);
      c_ws(p);
      if (c_peek(p) < 0 || c_peek(p) == '>' || c_peek(p) == ',' ||
          c_peek(p) == '{') {
        css_fail(p, "expected selector after '>'");
        goto fail;
      }
      pending_direct = true;
      continue;
    }
    if (separated && c_peek(p) != ',' && c_peek(p) != '{') {
      pending_direct = false;
      continue;
    }
    if (c_peek(p) != ',' && c_peek(p) != '{') {
      css_fail(p, "unexpected selector token");
      goto fail;
    }
    sel = compounds[compound_count - 1u];
    sel.ancestor_count = (u32)(compound_count - 1u);
    for (i = 0; i < compound_count - 1u; i++) {
      size_t source = compound_count - 2u - i;
      if (!c_ancestor_copy(p, &sel.ancestors[i], &compounds[source])) {
        goto fail;
      }
      sel.ancestor_direct_path[i] = direct_between[source + 1u];
    }
    if (p->scope_count > 0u) {
      size_t scope_index;
      size_t existing = sel.ancestor_count;
      size_t scope_root_count = 0u;
      if (existing + p->scope_count > MY_CSS_MAX_ANCESTORS) {
        size_t si;
        for (si = 0u; si < p->scope_count; ++si) {
          if (p->scope_has_root[si]) scope_root_count++;
        }
      }
      if (existing + scope_root_count > MY_CSS_MAX_ANCESTORS) {
        css_fail(p, "scope ancestor depth exceeded");
        goto fail;
      }
      scope_root_count = 0u;
      for (scope_index = 0u; scope_index < p->scope_count; ++scope_index) {
        const my_css_selector_t* scope =
            &p->scope_selectors[p->scope_count - scope_index - 1u];
        size_t root_index = MY_CSS_SCOPE_ROOT_IMPLICIT;
        if (p->scope_has_root[p->scope_count - scope_index - 1u]) {
          my_css_ancestor_t* ancestor =
              &sel.ancestors[existing + scope_root_count];
          memcpy(ancestor->widget_type, scope->widget_type,
                 sizeof(ancestor->widget_type));
          memcpy(ancestor->id, scope->id, sizeof(ancestor->id));
          memcpy(ancestor->style_class, scope->style_class,
                 sizeof(ancestor->style_class));
          sel.ancestor_direct_path[existing + scope_root_count] = false;
          root_index = existing + scope_root_count;
          scope_root_count++;
        }
        if (scope->scope_limit_count != 0u) {
          size_t limit_index;
          if (sel.scope_limit_count + scope->scope_limit_count >
              MY_CSS_MAX_SCOPE_NESTING) {
            css_fail(p, "scope limit depth exceeded");
            goto fail;
          }
          for (limit_index = 0u; limit_index < scope->scope_limit_count;
               ++limit_index) {
            sel.scope_limits[sel.scope_limit_count] =
                scope->scope_limits[limit_index];
            sel.scope_limit_root_index[sel.scope_limit_count] =
                (u32)root_index;
            sel.scope_limit_count++;
          }
        }
      }
      sel.ancestor_count = (u32)(existing + scope_root_count);
    }
    if (sel.ancestor_count == 1u && sel.ancestors[0].id[0] == '\0') {
      size_t type_len = strlen(sel.ancestors[0].widget_type);
      size_t class_len = strlen(sel.ancestors[0].style_class);
      if (type_len + (class_len > 0u ? 1u + class_len : 0u) <
          sizeof(sel.ancestor_type)) {
        memcpy(sel.ancestor_type, sel.ancestors[0].widget_type, type_len);
        if (class_len > 0u) {
          sel.ancestor_type[type_len] = '.';
          memcpy(sel.ancestor_type + type_len + 1u,
                 sel.ancestors[0].style_class, class_len);
        }
        sel.ancestor_type[type_len + (class_len > 0u ? 1u + class_len : 0u)] =
            '\0';
        sel.ancestor_direct = sel.ancestor_direct_path[0];
      }
    }
    slot = (my_css_selector_t*)my_mem_calloc(p->allocator, 1,
                                             sizeof(my_css_selector_t));
    if (slot == NULL) {
      css_fail(p, "oom");
      goto fail;
    }
    *slot = sel;
    if (my_darray_push(r->selectors, slot) != MY_RET_OK) {
      my_mem_free(p->allocator, slot);
      css_fail(p, "oom");
      goto fail;
    }
    if (c_peek(p) == ',') {
      c_next(p);
      compound_count = 0;
      pending_direct = false;
      continue;
    }
    break;
  }
  c_ws(p);
  if (c_peek(p) != '{') {
    css_fail(p, "expected '{'");
    goto fail;
  }
  c_next(p);
  /* declarations */
  for (;;) {
    char key[MY_STYLE_KEY_LEN];
    char mapped[MY_STYLE_KEY_LEN];
    my_css_decl_t* d;
    c_ws(p);
    if (c_failed(p)) {
      goto fail;
    }
    if (c_peek(p) == '}') {
      c_next(p);
      return r;
    }
    if (!c_ident(p, key, sizeof(key))) {
      css_fail(p, "expected declaration key");
      goto fail;
    }
    c_ws(p);
    if (c_peek(p) != ':') {
      /* lenient: skip to ';' or '}' with a warning */
      MY_LOGW("my_css: skipping malformed declaration (key '%s')", key);
      while (c_peek(p) >= 0 && c_peek(p) != ';' && c_peek(p) != '}') {
        c_next(p);
      }
      if (c_peek(p) == ';') {
        c_next(p);
        continue;
      }
      if (c_peek(p) == '}') {
        c_next(p);
        return r;
      }
      css_fail(p, "unterminated declaration");
      goto fail;
    }
    c_next(p);
    c_ws(p);
    d = (my_css_decl_t*)my_mem_calloc(p->allocator, 1, sizeof(my_css_decl_t));
    if (d == NULL) {
      css_fail(p, "oom");
      goto fail;
    }
    my_value_init(&d->value, p->allocator);
    if (!css_value(p, &d->value)) {
      /* lenient: skip to ';' or '}' with a warning */
      MY_LOGW("my_css: skipping bad value for '%s'", key);
      my_mem_free(p->allocator, d);
      while (c_peek(p) >= 0 && c_peek(p) != ';' && c_peek(p) != '}') {
        c_next(p);
      }
      if (c_peek(p) == ';') {
        c_next(p);
        continue;
      }
      if (c_peek(p) == '}') {
        c_next(p);
        return r;
      }
      css_fail(p, "unterminated declaration");
      goto fail;
    }
    css_key_map(key, mapped, sizeof(mapped));
    snprintf(d->key, sizeof(d->key), "%s", mapped);
    if (my_darray_push(r->decls, d) != MY_RET_OK) {
      my_value_reset(&d->value);
      my_mem_free(p->allocator, d);
      css_fail(p, "oom");
      goto fail;
    }
    c_ws(p);
    if (c_peek(p) == ';') {
      c_next(p);
      continue;
    }
    if (c_peek(p) == '}') {
      c_next(p);
      return r;
    }
    css_fail(p, "expected ';' or '}'");
    goto fail;
  }
fail:
  css_rule_destroy(p->allocator, r);
  return NULL;
}

/* ---------------- sheet ---------------- */

static bool css_parse_rules(css_p_t* p, my_css_sheet_t* sheet,
                            bool nested, size_t media_depth,
                            uint32_t layer_id);

static bool css_skip_or_reject_atrule_with_capability(
    css_p_t* p, uint32_t capability) {
  if ((p->flags & MY_CSS_PARSE_STRICT_AT_RULES) != 0u) {
    p->failed = true;
    if (p->err != NULL && p->err->msg[0] == '\0') {
      p->err->line = p->line;
      p->err->col = p->col;
      p->err->code = MY_CSS_ERROR_UNSUPPORTED_FEATURE;
      p->err->capability = capability;
      snprintf(p->err->msg, sizeof(p->err->msg), "%s", "unsupported @-rule");
    }
    return false;
  }
  css_skip_atrule(p, true);
  return !c_failed(p);
}

static bool css_skip_or_reject_atrule(css_p_t* p) {
  return css_skip_or_reject_atrule_with_capability(
      p, (uint32_t)MY_CSS_FEATURE_AT_RULES);
}

static bool css_supports_property_value_ex(const char* query, size_t length,
                                           const my_allocator_t* allocator,
                                           bool* supported) {
  css_p_t value_parser;
  my_value_t value;
  char key[MY_STYLE_KEY_LEN];
  char mapped[MY_STYLE_KEY_LEN];
  bool supported_key = false;
  bool supported_type = false;

  memset(&value_parser, 0, sizeof(value_parser));
  value_parser.allocator = allocator;
  value_parser.s = query;
  value_parser.len = length;
  value_parser.line = 1;
  value_parser.col = 1;
  c_ws(&value_parser);
  if (!c_ident(&value_parser, key, sizeof(key))) return false;
  c_ws(&value_parser);
  if (c_peek(&value_parser) != ':') return false;
  c_next(&value_parser);
  c_ws(&value_parser);

  my_value_init(&value, allocator);
  if (!css_value(&value_parser, &value)) {
    my_value_reset(&value);
    return false;
  }
  c_ws(&value_parser);
  if (c_peek(&value_parser) >= 0) {
    my_value_reset(&value);
    return false;
  }

  css_key_map(key, mapped, sizeof(mapped));
  supported_key = my_str_eq(mapped, MY_STYLE_BG_COLOR) ||
                  my_str_eq(mapped, MY_STYLE_FG_COLOR) ||
                  my_str_eq(mapped, MY_STYLE_BORDER_COLOR) ||
                  my_str_eq(mapped, MY_STYLE_BORDER_WIDTH) ||
                  my_str_eq(mapped, MY_STYLE_ROUND_RADIUS) ||
                  my_str_eq(mapped, MY_STYLE_FONT_SIZE);
  if (supported_key) {
    if (my_str_eq(mapped, MY_STYLE_BG_COLOR) ||
        my_str_eq(mapped, MY_STYLE_FG_COLOR) ||
        my_str_eq(mapped, MY_STYLE_BORDER_COLOR)) {
      supported_type = my_value_type(&value) == MY_VALUE_UINT32;
    } else {
      supported_type = my_value_type(&value) == MY_VALUE_INT32 ||
                       my_value_type(&value) == MY_VALUE_DOUBLE;
    }
  }
  my_value_reset(&value);
  if (supported != NULL) {
    *supported = supported_key && supported_type;
  }
  return supported_key && supported_type;
}

typedef struct css_supports_expr_t {
  const char* text;
  size_t length;
  size_t position;
  size_t depth;
  const my_allocator_t* allocator;
} css_supports_expr_t;

static void css_supports_expr_ws(css_supports_expr_t* expr) {
  while (expr->position < expr->length &&
         (expr->text[expr->position] == ' ' ||
          expr->text[expr->position] == '\t' ||
          expr->text[expr->position] == '\r' ||
          expr->text[expr->position] == '\n')) {
    expr->position++;
  }
}

static bool css_supports_expr_word(css_supports_expr_t* expr,
                                    const char* word) {
  size_t length = strlen(word);
  size_t end;
  css_supports_expr_ws(expr);
  if (length > expr->length - expr->position ||
      memcmp(expr->text + expr->position, word, length) != 0) {
    return false;
  }
  end = expr->position + length;
  if (end < expr->length && c_ident_char((unsigned char)expr->text[end])) {
    return false;
  }
  expr->position = end;
  return true;
}

static bool css_supports_expr_parse(css_supports_expr_t* expr,
                                    bool* matches);

static bool css_supports_expr_atom(const char* text, size_t length,
                                   size_t depth,
                                   const my_allocator_t* allocator,
                                   bool* matches) {
  bool supported = false;
  css_supports_expr_t nested;
  if (css_supports_property_value_ex(text, length, allocator, &supported)) {
    *matches = supported;
    return true;
  }
  if (depth >= MY_CSS_MAX_SUPPORTS_NESTING) return false;
  nested = (css_supports_expr_t){text, length, 0u, depth + 1u, allocator};
  if (!css_supports_expr_parse(&nested, matches)) return false;
  css_supports_expr_ws(&nested);
  return nested.position == nested.length;
}

static bool css_supports_expr_primary(css_supports_expr_t* expr,
                                      bool* matches) {
  size_t start;
  size_t end;
  size_t nested = 0u;
  char quote = '\0';
  css_supports_expr_ws(expr);
  if (expr->position >= expr->length || expr->text[expr->position] != '(') {
    return false;
  }
  expr->position++;
  start = expr->position;
  while (expr->position < expr->length) {
    char c = expr->text[expr->position];
    if (quote != '\0') {
      if (c == '\\' && expr->position + 1u < expr->length) {
        expr->position += 2u;
        continue;
      }
      if (c == quote) quote = '\0';
      expr->position++;
      continue;
    }
    if (c == '\'' || c == '"') {
      quote = c;
      expr->position++;
      continue;
    }
    if (c == '(') {
      nested++;
    } else if (c == ')') {
      if (nested == 0u) break;
      nested--;
    }
    expr->position++;
  }
  if (quote != '\0' || expr->position >= expr->length ||
      expr->text[expr->position] != ')' || nested != 0u) {
    return false;
  }
  end = expr->position++;
  return css_supports_expr_atom(expr->text + start, end - start, expr->depth,
                                expr->allocator, matches);
}

static bool css_supports_expr_unary(css_supports_expr_t* expr,
                                     bool* matches) {
  size_t save = expr->position;
  if (css_supports_expr_word(expr, "not")) {
    if (!css_supports_expr_unary(expr, matches)) return false;
    *matches = !*matches;
    return true;
  }
  expr->position = save;
  return css_supports_expr_primary(expr, matches);
}

static bool css_supports_expr_and(css_supports_expr_t* expr, bool* matches) {
  bool right;
  if (!css_supports_expr_unary(expr, matches)) return false;
  for (;;) {
    size_t save = expr->position;
    if (!css_supports_expr_word(expr, "and")) {
      expr->position = save;
      return true;
    }
    if (!css_supports_expr_unary(expr, &right)) return false;
    *matches = *matches && right;
  }
}

static bool css_supports_expr_parse(css_supports_expr_t* expr,
                                    bool* matches) {
  bool right;
  if (!css_supports_expr_and(expr, matches)) return false;
  for (;;) {
    size_t save = expr->position;
    if (!css_supports_expr_word(expr, "or")) {
      expr->position = save;
      return true;
    }
    if (!css_supports_expr_and(expr, &right)) return false;
    *matches = *matches || right;
  }
}

static bool css_supports_condition(const char* query, size_t length,
                                   const my_allocator_t* allocator,
                                   bool* matches) {
  css_supports_expr_t parser;

  if (query == NULL || matches == NULL || length == 0u ||
      length > MY_CSS_MAX_SUPPORTS_QUERY_BYTES) {
    return false;
  }
  parser = (css_supports_expr_t){query, length, 0u, 0u, allocator};
  if (!css_supports_expr_parse(&parser, matches)) return false;
  css_supports_expr_ws(&parser);
  return parser.position == parser.length;
}

static bool css_read_atrule_prelude(css_p_t* p, char* out, size_t cap,
                                    size_t* length) {
  size_t used = 0u;
  char quote = '\0';
  while (c_peek(p) >= 0) {
    int c = c_peek(p);
    if (quote != '\0') {
      if (used + 1u >= cap) return false;
      out[used++] = (char)c_next(p);
      if (c == '\\' && c_peek(p) >= 0) {
        if (used + 1u >= cap) return false;
        out[used++] = (char)c_next(p);
      } else if (c == quote) {
        quote = '\0';
      }
      continue;
    }
    if (c == '\'' || c == '"') {
      quote = (char)c;
      if (used + 1u >= cap) return false;
      out[used++] = (char)c_next(p);
      continue;
    }
    if (c == '/' && p->pos + 1u < p->len && p->s[p->pos + 1u] == '*') {
      if (used + 2u >= cap) return false;
      out[used++] = (char)c_next(p);
      out[used++] = (char)c_next(p);
      while (c_peek(p) >= 0 &&
             !(c_peek(p) == '*' && p->pos + 1u < p->len &&
               p->s[p->pos + 1u] == '/')) {
        if (used + 1u >= cap) return false;
        out[used++] = (char)c_next(p);
      }
      if (c_peek(p) < 0) return false;
      if (used + 2u >= cap) return false;
      out[used++] = (char)c_next(p);
      out[used++] = (char)c_next(p);
      continue;
    }
    if (c == '{') break;
    if (used + 1u >= cap) return false;
    out[used++] = (char)c_next(p);
  }
  if (quote != '\0' || c_peek(p) != '{') return false;
  out[used] = '\0';
  *length = used;
  return true;
}

static bool css_parse_supports_atrule(css_p_t* p, my_css_sheet_t* sheet,
                                      size_t at_rule_depth,
                                      uint32_t layer_id) {
  char query[MY_CSS_MAX_SUPPORTS_QUERY_BYTES + 1u];
  size_t query_length = 0u;
  bool matches = false;

  c_ws(p);
  if (!css_read_atrule_prelude(p, query, sizeof(query), &query_length) ||
      !css_supports_condition(query, query_length, p->allocator, &matches)) {
    return css_skip_or_reject_atrule_with_capability(
        p, (uint32_t)MY_CSS_FEATURE_SUPPORTS);
  }
  if (at_rule_depth >= MY_CSS_MAX_AT_RULE_NESTING) {
    css_fail(p, "@supports nesting depth exceeded");
    return false;
  }
  if (!matches) {
    css_skip_atrule(p, false);
    return !c_failed(p);
  }
  c_next(p);
  return css_parse_rules(p, sheet, true, at_rule_depth + 1u, layer_id);
}

typedef struct css_media_cursor_t {
  const char* text;
  size_t length;
  size_t position;
} css_media_cursor_t;

static void css_media_ws(css_media_cursor_t* cursor) {
  while (cursor->position < cursor->length &&
         (cursor->text[cursor->position] == ' ' ||
          cursor->text[cursor->position] == '\t' ||
          cursor->text[cursor->position] == '\r' ||
          cursor->text[cursor->position] == '\n')) {
    cursor->position++;
  }
}

static bool css_media_word(css_media_cursor_t* cursor, const char* word) {
  size_t word_length = strlen(word);
  size_t end;
  css_media_ws(cursor);
  if (word_length > cursor->length - cursor->position) return false;
  end = cursor->position + word_length;
  if (memcmp(cursor->text + cursor->position, word, word_length) != 0) {
    return false;
  }
  if (end < cursor->length && c_ident_char((unsigned char)cursor->text[end])) {
    return false;
  }
  cursor->position = end;
  return true;
}

static bool css_media_number_px(css_media_cursor_t* cursor, uint32_t* value) {
  uint64_t parsed = 0u;
  size_t digits = 0u;
  css_media_ws(cursor);
  while (cursor->position < cursor->length &&
         cursor->text[cursor->position] >= '0' &&
         cursor->text[cursor->position] <= '9') {
    parsed = parsed * 10u +
             (uint64_t)(cursor->text[cursor->position] - '0');
    if (parsed > UINT32_MAX) return false;
    cursor->position++;
    digits++;
  }
  if (digits == 0u || !css_media_word(cursor, "px")) return false;
  *value = (uint32_t)parsed;
  return true;
}

typedef enum css_media_relation_t {
  CSS_MEDIA_REL_LT,
  CSS_MEDIA_REL_LE,
  CSS_MEDIA_REL_EQ,
  CSS_MEDIA_REL_GE,
  CSS_MEDIA_REL_GT
} css_media_relation_t;

static bool css_media_relation(css_media_cursor_t* cursor,
                               css_media_relation_t* relation) {
  css_media_ws(cursor);
  if (cursor->position >= cursor->length) return false;
  if (cursor->text[cursor->position] == '<') {
    cursor->position++;
    if (cursor->position < cursor->length &&
        cursor->text[cursor->position] == '=') {
      cursor->position++;
      *relation = CSS_MEDIA_REL_LE;
    } else {
      *relation = CSS_MEDIA_REL_LT;
    }
    return true;
  }
  if (cursor->text[cursor->position] == '>') {
    cursor->position++;
    if (cursor->position < cursor->length &&
        cursor->text[cursor->position] == '=') {
      cursor->position++;
      *relation = CSS_MEDIA_REL_GE;
    } else {
      *relation = CSS_MEDIA_REL_GT;
    }
    return true;
  }
  if (cursor->text[cursor->position] == '=') {
    cursor->position++;
    *relation = CSS_MEDIA_REL_EQ;
    return true;
  }
  return false;
}

static bool css_media_compare(uint32_t actual, css_media_relation_t relation,
                              uint32_t expected) {
  switch (relation) {
    case CSS_MEDIA_REL_LT: return actual < expected;
    case CSS_MEDIA_REL_LE: return actual <= expected;
    case CSS_MEDIA_REL_EQ: return actual == expected;
    case CSS_MEDIA_REL_GE: return actual >= expected;
    case CSS_MEDIA_REL_GT: return actual > expected;
  }
  return false;
}

static bool css_media_capabilities_valid(
    const my_css_media_context_ex_t* media) {
  return media == NULL ||
         ((media->base.capabilities & ~MY_CSS_MEDIA_CAP_ALL) == 0u &&
          (media->known & ~MY_CSS_MEDIA_KNOWN_ALL) == 0u);
}

static bool css_media_fact_known(const my_css_media_context_ex_t* media,
                                uint32_t fact) {
  /* A zero known mask preserves the pre-known-mask API semantics. */
  return media != NULL &&
         (media->known == 0u || (media->known & fact) != 0u);
}

static bool css_media_context_known(const my_css_media_context_ex_t* media) {
  return media != NULL;
}

/* Returns 1 for a parsed range, 0 for legacy `name: value`, -1 for a
 * malformed range. Range predicates are flattened during parsing. */
static int css_media_range(css_media_cursor_t* cursor,
                           const my_css_media_context_ex_t* media,
                           bool* matches, bool* known) {
  size_t saved = cursor->position;
  char name[32];
  size_t name_length = 0u;
  uint32_t first_number = 0u;
  uint32_t second_number = 0u;
  css_media_relation_t first_relation;
  css_media_relation_t second_relation;
  bool first_is_number = false;
  bool result = true;
  css_media_cursor_t probe;

  css_media_ws(cursor);
  *known = css_media_context_known(media);
  if (cursor->position >= cursor->length) return -1;
  if (cursor->text[cursor->position] >= '0' &&
      cursor->text[cursor->position] <= '9') {
    if (!css_media_number_px(cursor, &first_number)) return -1;
    first_is_number = true;
  } else {
    while (cursor->position < cursor->length &&
           c_ident_char((unsigned char)cursor->text[cursor->position])) {
      if (name_length + 1u >= sizeof(name)) return -1;
      name[name_length++] = cursor->text[cursor->position++];
    }
    name[name_length] = '\0';
    if (name_length == 0u) return -1;
    probe = *cursor;
    css_media_ws(&probe);
    if (probe.position < probe.length && probe.text[probe.position] == ':') {
      cursor->position = saved;
      return 0;
    }
  }
  if (!css_media_relation(cursor, &first_relation)) return -1;

  if (!first_is_number) {
    if (!my_str_eq(name, "width") && !my_str_eq(name, "height")) return -1;
    if (!css_media_number_px(cursor, &first_number)) return -1;
    if (media != NULL) {
      uint32_t actual = my_str_eq(name, "width")
                            ? media->base.viewport_width_px
                            : media->base.viewport_height_px;
      result = css_media_compare(actual, first_relation, first_number);
    }
  } else {
    css_media_ws(cursor);
    name_length = 0u;
    while (cursor->position < cursor->length &&
           c_ident_char((unsigned char)cursor->text[cursor->position])) {
      if (name_length + 1u >= sizeof(name)) return -1;
      name[name_length++] = cursor->text[cursor->position++];
    }
    name[name_length] = '\0';
    if ((!my_str_eq(name, "width") && !my_str_eq(name, "height")) ||
        media == NULL) {
      if (name_length == 0u) return -1;
    }
    if (media != NULL) {
      uint32_t actual = my_str_eq(name, "width")
                            ? media->base.viewport_width_px
                            : media->base.viewport_height_px;
      result = css_media_compare(first_number, first_relation, actual);
    }
  }

  css_media_ws(cursor);
  if (cursor->position < cursor->length && cursor->text[cursor->position] != ')') {
    if (!first_is_number || !css_media_relation(cursor, &second_relation) ||
        !css_media_number_px(cursor, &second_number)) {
      return -1;
    }
    if (media != NULL) {
      uint32_t actual = my_str_eq(name, "width")
                            ? media->base.viewport_width_px
                            : media->base.viewport_height_px;
      result = result &&
               css_media_compare(actual, second_relation, second_number);
    }
  }
  css_media_ws(cursor);
  if (cursor->position >= cursor->length ||
      cursor->text[cursor->position++] != ')') return -1;
  *matches = result;
  return 1;
}

static bool css_media_feature(css_media_cursor_t* cursor,
                              const my_css_media_context_ex_t* media,
                              bool* matches, bool* known) {
  char name[32];
  char value[32];
  size_t name_length = 0u;
  size_t value_length = 0u;
  uint32_t number = 0u;
  int range_result;

  *known = true;

  css_media_ws(cursor);
  if (cursor->position >= cursor->length ||
      cursor->text[cursor->position++] != '(') {
    return false;
  }
  range_result = css_media_range(cursor, media, matches, known);
  if (range_result != 0) return range_result > 0;

  css_media_ws(cursor);
  while (cursor->position < cursor->length &&
         c_ident_char((unsigned char)cursor->text[cursor->position])) {
    if (name_length + 1u >= sizeof(name)) return false;
    name[name_length++] = cursor->text[cursor->position++];
  }
  name[name_length] = '\0';
  css_media_ws(cursor);
  if (cursor->position >= cursor->length ||
      cursor->text[cursor->position++] != ':') {
    return false;
  }
  css_media_ws(cursor);
  while (cursor->position < cursor->length &&
         cursor->text[cursor->position] != ')' &&
         cursor->text[cursor->position] != ' ' &&
         cursor->text[cursor->position] != '\t' &&
         cursor->text[cursor->position] != '\r' &&
         cursor->text[cursor->position] != '\n') {
    if (value_length + 1u >= sizeof(value)) return false;
    value[value_length++] = cursor->text[cursor->position++];
  }
  value[value_length] = '\0';
  css_media_ws(cursor);
  if (cursor->position >= cursor->length ||
      cursor->text[cursor->position++] != ')') {
    return false;
  }
  if (my_str_eq(name, "hover")) {
    if (!my_str_eq(value, "none") && !my_str_eq(value, "hover")) {
      return false;
    }
    *known = css_media_fact_known(media, MY_CSS_MEDIA_KNOWN_HOVER);
    *matches = *known &&
              (my_str_eq(value, "hover")
                   ? (media->base.capabilities & MY_CSS_MEDIA_CAP_HOVER) != 0u
                   : (media->base.capabilities & MY_CSS_MEDIA_CAP_HOVER) == 0u);
    return true;
  }
  if (my_str_eq(name, "pointer") || my_str_eq(name, "any-pointer")) {
    uint32_t coarse = my_str_eq(name, "pointer")
                          ? MY_CSS_MEDIA_CAP_POINTER_COARSE
                          : MY_CSS_MEDIA_CAP_ANY_POINTER_COARSE;
    uint32_t fine = my_str_eq(name, "pointer")
                        ? MY_CSS_MEDIA_CAP_POINTER_FINE
                        : MY_CSS_MEDIA_CAP_ANY_POINTER_FINE;
    if (!my_str_eq(value, "none") && !my_str_eq(value, "coarse") &&
        !my_str_eq(value, "fine")) {
      return false;
    }
    if (media == NULL ||
        !css_media_fact_known(media, my_str_eq(name, "pointer")
                                       ? MY_CSS_MEDIA_KNOWN_POINTER
                                       : MY_CSS_MEDIA_KNOWN_ANY_POINTER)) {
      *matches = false;
      *known = false;
    } else if (my_str_eq(value, "none")) {
      *matches = (media->base.capabilities & (coarse | fine)) == 0u;
    } else {
      *matches = (media->base.capabilities &
                  (my_str_eq(value, "coarse") ? coarse : fine)) != 0u;
    }
    return true;
  }
  if (my_str_eq(name, "color-gamut")) {
    uint32_t required;
    uint32_t available;
    if (my_str_eq(value, "srgb")) {
      required = MY_CSS_MEDIA_CAP_COLOR_SRGB;
    } else if (my_str_eq(value, "p3")) {
      required = MY_CSS_MEDIA_CAP_COLOR_P3;
    } else if (my_str_eq(value, "rec2020")) {
      required = MY_CSS_MEDIA_CAP_COLOR_REC2020;
    } else {
      return false;
    }
    available = media != NULL ? media->base.capabilities : 0u;
    if (!css_media_fact_known(media, MY_CSS_MEDIA_KNOWN_COLOR_GAMUT)) {
      *matches = false;
      *known = false;
      return true;
    }
    if (required == MY_CSS_MEDIA_CAP_COLOR_SRGB) {
      *matches = (available & (MY_CSS_MEDIA_CAP_COLOR_SRGB |
                               MY_CSS_MEDIA_CAP_COLOR_P3 |
                               MY_CSS_MEDIA_CAP_COLOR_REC2020)) != 0u;
    } else if (required == MY_CSS_MEDIA_CAP_COLOR_P3) {
      *matches = (available & (MY_CSS_MEDIA_CAP_COLOR_P3 |
                               MY_CSS_MEDIA_CAP_COLOR_REC2020)) != 0u;
    } else {
      *matches = (available & required) != 0u;
    }
    return true;
  }
  if (my_str_eq(name, "dynamic-range")) {
    if (!my_str_eq(value, "standard") && !my_str_eq(value, "high")) {
      return false;
    }
    *known = css_media_fact_known(media, MY_CSS_MEDIA_KNOWN_HDR);
    *matches = *known &&
               (my_str_eq(value, "standard") ||
                (media->base.capabilities & MY_CSS_MEDIA_CAP_HDR) != 0u);
    return true;
  }
  if (media == NULL) {
    *matches = false;
    *known = false;
    return true;
  }
  if (my_str_eq(name, "min-width") || my_str_eq(name, "max-width") ||
      my_str_eq(name, "width") || my_str_eq(name, "min-height") ||
      my_str_eq(name, "max-height") || my_str_eq(name, "height")) {
    css_media_cursor_t value_cursor = {value, value_length, 0u};
    if (!css_media_number_px(&value_cursor, &number) ||
        value_cursor.position != value_length) {
      return false;
    }
    if (my_str_eq(name, "min-width")) {
      *matches = media->base.viewport_width_px >= number;
    } else if (my_str_eq(name, "max-width")) {
      *matches = media->base.viewport_width_px <= number;
    } else if (my_str_eq(name, "width")) {
      *matches = media->base.viewport_width_px == number;
    } else if (my_str_eq(name, "min-height")) {
      *matches = media->base.viewport_height_px >= number;
    } else if (my_str_eq(name, "max-height")) {
      *matches = media->base.viewport_height_px <= number;
    } else {
      *matches = media->base.viewport_height_px == number;
    }
    return true;
  }
  if (my_str_eq(name, "orientation")) {
    if (!my_str_eq(value, "landscape") && !my_str_eq(value, "portrait")) {
      return false;
    }
    if (media == NULL) {
      *matches = false;
      *known = false;
      return true;
    }
    *matches = my_str_eq(value, "landscape")
                  ? media->base.viewport_width_px >= media->base.viewport_height_px
                  : media->base.viewport_width_px < media->base.viewport_height_px;
    return true;
  }
  if (my_str_eq(name, "prefers-color-scheme")) {
    if (!my_str_eq(value, "dark") && !my_str_eq(value, "light")) {
      return false;
    }
    *known = css_media_fact_known(media, MY_CSS_MEDIA_KNOWN_COLOR_SCHEME);
    *matches = *known &&
               (my_str_eq(value, "dark") == media->base.prefers_dark);
    return true;
  }
  if (my_str_eq(name, "prefers-reduced-motion")) {
    if (!my_str_eq(value, "reduce") &&
        !my_str_eq(value, "no-preference")) {
      return false;
    }
    *known = css_media_fact_known(media, MY_CSS_MEDIA_KNOWN_REDUCED_MOTION);
    *matches = *known &&
        (my_str_eq(value, "reduce") == media->base.prefers_reduced_motion);
    return true;
  }
  return false;
}

static bool css_media_query(css_media_cursor_t* cursor,
                            const my_css_media_context_ex_t* media,
                            bool* matches, bool* conditional) {
  bool query_matches = true;
  bool feature_matches = true;
  bool feature_known = true;
  bool has_type = false;
  bool need_and = false;
  bool negated = false;
  css_media_ws(cursor);
  if (css_media_word(cursor, "not")) {
    negated = true;
    css_media_ws(cursor);
  }
  if (cursor->position < cursor->length &&
      cursor->text[cursor->position] != '(') {
    if (css_media_word(cursor, "all")) {
      has_type = true;
    } else if (css_media_word(cursor, "screen")) {
      has_type = true;
      query_matches = media == NULL || media->base.screen;
    } else {
      return false;
    }
    if (negated) return false;
    need_and = true;
  }
  css_media_ws(cursor);
  while (cursor->position < cursor->length) {
    if (cursor->text[cursor->position] == ',') break;
    if (need_and && !css_media_word(cursor, "and")) {
      return false;
    }
    if (cursor->text[cursor->position] == '(') {
      if (!css_media_feature(cursor, media, &feature_matches,
                             &feature_known)) {
        return false;
      }
    } else if (!css_media_feature(cursor, media, &feature_matches,
                                  &feature_known)) {
      return false;
    }
    if (negated) {
      if (need_and) return false;
      if (feature_known) feature_matches = !feature_matches;
      else feature_matches = false;
    }
    need_and = true;
    *conditional = true;
    query_matches = query_matches && feature_matches;
    css_media_ws(cursor);
    if (negated && cursor->position < cursor->length) return false;
  }
  if (!has_type && !*conditional) return false;
  *matches = query_matches;
  return true;
}

static bool css_media_condition(css_p_t* p, const char* query, size_t length,
                                bool* matches, bool* conditional) {
  css_media_cursor_t cursor = {query, length, 0u};
  *matches = false;
  *conditional = false;
  for (;;) {
    bool query_matches;
    if (!css_media_query(&cursor, p->media, &query_matches, conditional)) {
      return false;
    }
    *matches = *matches || query_matches;
    css_media_ws(&cursor);
    if (cursor.position == cursor.length) return true;
    if (cursor.text[cursor.position++] != ',') return false;
  }
}

/* Media predicates are evaluated once while parsing; theme lookup stays hot. */
static bool css_parse_media_atrule(css_p_t* p, my_css_sheet_t* sheet,
                                   size_t media_depth,
                                   uint32_t layer_id) {
  char query[MY_CSS_MAX_MEDIA_QUERY_BYTES + 1u];
  size_t query_length = 0u;
  bool matches = false;
  bool conditional = false;

  c_ws(p);
  while (c_peek(p) >= 0 && c_peek(p) != '{') {
    if (query_length >= MY_CSS_MAX_MEDIA_QUERY_BYTES) {
      css_fail(p, "media query too long");
      return false;
    }
    query[query_length++] = (char)c_next(p);
  }
  query[query_length] = '\0';
  if (c_peek(p) != '{' ||
      !css_media_condition(p, query, query_length, &matches, &conditional)) {
    return css_skip_or_reject_atrule(p);
  }
  if (conditional && p->media == NULL) {
    return css_skip_or_reject_atrule(p);
  }
  if (media_depth >= MY_CSS_MAX_AT_RULE_NESTING) {
    css_fail(p, "@media nesting depth exceeded");
    return false;
  }
  c_ws(p);
  if (c_peek(p) != '{') {
    return css_skip_or_reject_atrule(p);
  }
  if (!matches) {
    css_skip_atrule(p, false);
    return !c_failed(p);
  }
  c_next(p);
  return css_parse_rules(p, sheet, true, media_depth + 1u, layer_id);
}

static bool css_layer_name_valid(const char* name, size_t length) {
  size_t i;
  if (name == NULL || length == 0u || length > MY_CSS_MAX_LAYER_NAME_BYTES) {
    return false;
  }
  for (i = 0u; i < length; ++i) {
    unsigned char c = (unsigned char)name[i];
    if (!c_ident_char(c) && c != '.') return false;
  }
  return name[0] != '.' && name[length - 1u] != '.' &&
         strstr(name, "..") == NULL;
}

static uint32_t css_layer_find_or_add(css_p_t* p, const char* name,
                                      size_t length) {
  size_t i;
  if (!css_layer_name_valid(name, length)) return MY_CSS_UNLAYERED_ORDER;
  for (i = 0u; i < p->layer_count; ++i) {
    if (strlen(p->layer_names[i]) == length &&
        memcmp(p->layer_names[i], name, length) == 0) {
      return (uint32_t)i;
    }
  }
  if (p->layer_count >= MY_CSS_MAX_LAYERS) {
    css_fail(p, "CSS layer limit exceeded");
    return MY_CSS_UNLAYERED_ORDER;
  }
  memcpy(p->layer_names[p->layer_count], name, length);
  p->layer_names[p->layer_count][length] = '\0';
  p->layer_ranks[p->layer_count] = (uint32_t)p->layer_count;
  return (uint32_t)p->layer_count++;
}

static bool css_apply_layer_order(css_p_t* p, const uint32_t* ids,
                                  size_t count) {
  bool listed[MY_CSS_MAX_LAYERS] = {false};
  uint32_t old_ranks[MY_CSS_MAX_LAYERS];
  size_t i;
  size_t next_rank = 0u;
  if (p == NULL || ids == NULL || count == 0u || count > p->layer_count) {
    return false;
  }
  for (i = 0u; i < p->layer_count; ++i) old_ranks[i] = p->layer_ranks[i];
  for (i = 0u; i < count; ++i) {
    if (ids[i] >= p->layer_count || listed[ids[i]]) return false;
    listed[ids[i]] = true;
    p->layer_ranks[ids[i]] = (uint32_t)next_rank++;
  }
  for (i = 0u; i < p->layer_count; ++i) {
    size_t candidate;
    uint32_t best_rank = UINT32_MAX;
    for (candidate = 0u; candidate < p->layer_count; ++candidate) {
      if (!listed[candidate] && old_ranks[candidate] < best_rank) {
        best_rank = old_ranks[candidate];
      }
    }
    if (best_rank == UINT32_MAX) break;
    for (candidate = 0u; candidate < p->layer_count; ++candidate) {
      if (!listed[candidate] && old_ranks[candidate] == best_rank) {
        listed[candidate] = true;
        p->layer_ranks[candidate] = (uint32_t)next_rank++;
        break;
      }
    }
  }
  return true;
}

static void css_finalize_layer_order(const css_p_t* p, my_css_sheet_t* sheet) {
  size_t i;
  if (p == NULL || sheet == NULL) return;
  for (i = 0u; i < my_darray_size(sheet->rules); ++i) {
    my_css_rule_t* rule =
        (my_css_rule_t*)my_darray_get(sheet->rules, i);
    if (rule->layer_order != MY_CSS_UNLAYERED_ORDER &&
        rule->layer_order < p->layer_count) {
      rule->layer_order = p->layer_ranks[rule->layer_order];
    }
  }
}

static bool css_read_layer_component(css_p_t* p, char* out, size_t cap) {
  size_t length = 0u;
  c_ws(p);
  while (c_peek(p) >= 0 && c_peek(p) != ',' && c_peek(p) != ';' &&
         c_peek(p) != '{' && c_peek(p) != '}' && c_peek(p) != ' ' &&
         c_peek(p) != '\t' && c_peek(p) != '\r' && c_peek(p) != '\n') {
    if (length + 1u >= cap) {
      css_fail(p, "CSS layer name too long");
      return false;
    }
    out[length++] = (char)c_next(p);
  }
  out[length] = '\0';
  return css_layer_name_valid(out, length);
}

static bool css_parse_layer_atrule(css_p_t* p, my_css_sheet_t* sheet,
                                   size_t at_rule_depth,
                                   uint32_t parent_layer_id) {
  char name[MY_CSS_MAX_LAYER_NAME_BYTES + 1u];
  char full_name[MY_CSS_MAX_LAYER_NAME_BYTES + 1u];
  uint32_t ids[MY_CSS_MAX_LAYERS];
  size_t count = 0u;
  size_t length;
  uint32_t layer_order;
  c_ws(p);
  if (!css_read_layer_component(p, name, sizeof(name))) {
    css_fail(p, "invalid @layer name");
    return false;
  }
  length = strlen(name);
  c_ws(p);
  if (c_peek(p) == ',' || c_peek(p) == ';') {
    for (;;) {
      if (count >= MY_CSS_MAX_LAYERS) {
        css_fail(p, "CSS layer limit exceeded");
        return false;
      }
      layer_order = css_layer_find_or_add(p, name, length);
      if (layer_order == MY_CSS_UNLAYERED_ORDER) return false;
      ids[count++] = layer_order;
      c_ws(p);
      if (c_peek(p) == ';') {
        c_next(p);
        return css_apply_layer_order(p, ids, count);
      }
      if (c_peek(p) != ',') {
        css_fail(p, "expected ',' or ';' after @layer name");
        return false;
      }
      c_next(p);
      if (!css_read_layer_component(p, name, sizeof(name))) {
        css_fail(p, "invalid @layer order statement");
        return false;
      }
      length = strlen(name);
    }
  }
  if (c_peek(p) != '{') {
    css_fail(p, "expected '{' or ';' after @layer name");
    return false;
  }
  if (parent_layer_id != MY_CSS_UNLAYERED_ORDER) {
    const char* parent = p->layer_names[parent_layer_id];
    size_t parent_len = strlen(parent);
    if (parent_len + 1u + length > MY_CSS_MAX_LAYER_NAME_BYTES) {
      css_fail(p, "nested CSS layer name too long");
      return false;
    }
    memcpy(full_name, parent, parent_len);
    full_name[parent_len] = '.';
    memcpy(full_name + parent_len + 1u, name, length + 1u);
    name[0] = '\0';
    memcpy(name, full_name, parent_len + 1u + length);
    length += parent_len + 1u;
  }
  layer_order = css_layer_find_or_add(p, name, length);
  if (layer_order == MY_CSS_UNLAYERED_ORDER) return false;
  if (at_rule_depth >= MY_CSS_MAX_AT_RULE_NESTING) {
    css_fail(p, "@layer nesting depth exceeded");
    return false;
  }
  c_next(p);
  return css_parse_rules(p, sheet, true, at_rule_depth + 1u, layer_order);
}

static bool css_parse_scope_atrule(css_p_t* p, my_css_sheet_t* sheet,
                                   size_t at_rule_depth, uint32_t layer_id) {
  my_css_selector_t selector;
  my_css_selector_t limit;
  bool parsed;
  bool has_root = false;
  bool has_limit = false;
  bool limit_universal = false;
  size_t limit_count = 0u;

  c_ws(p);
  memset(&selector, 0, sizeof(selector));
  selector.state = -1;
  if (c_peek(p) != '{') {
    bool starts_to = c_peek(p) == 't' && p->pos + 2u < p->len &&
                     p->s[p->pos + 1u] == 'o' &&
                     !c_ident_char((unsigned char)p->s[p->pos + 2u]);
    if (starts_to) {
      char keyword[8];
      if (!c_ident(p, keyword, sizeof(keyword))) {
        css_fail(p, "invalid @scope syntax");
        return false;
      }
      has_limit = true;
    } else {
      if (!c_selector(p, &selector) || selector.state != -1) {
        css_fail(p, "invalid @scope root selector");
        return false;
      }
      has_root = true;
      c_ws(p);
      starts_to = c_peek(p) == 't' && p->pos + 2u < p->len &&
                  p->s[p->pos + 1u] == 'o' &&
                  !c_ident_char((unsigned char)p->s[p->pos + 2u]);
      if (starts_to) {
        char keyword[8];
        if (!c_ident(p, keyword, sizeof(keyword))) {
          css_fail(p, "invalid @scope syntax");
          return false;
        }
        has_limit = true;
      }
    }
    if (has_limit) {
      for (;;) {
        c_ws(p);
        memset(&limit, 0, sizeof(limit));
        limit.state = -1;
        limit_universal = c_peek(p) == '*';
        if (limit_count >= MY_CSS_MAX_SCOPE_NESTING ||
            !c_selector(p, &limit) || limit.state != -1 ||
            (!limit_universal && limit.widget_type[0] == '\0' &&
             limit.id[0] == '\0' && limit.style_class[0] == '\0')) {
          css_fail(p, "invalid @scope limit selector");
          css_mark_scope_error(p);
          return false;
        }
        memcpy(selector.scope_limits[limit_count].widget_type,
               limit.widget_type,
               sizeof(selector.scope_limits[limit_count].widget_type));
        memcpy(selector.scope_limits[limit_count].id, limit.id,
               sizeof(selector.scope_limits[limit_count].id));
        memcpy(selector.scope_limits[limit_count].style_class,
               limit.style_class,
               sizeof(selector.scope_limits[limit_count].style_class));
        limit_count++;
        c_ws(p);
        if (c_peek(p) != ',') break;
        c_next(p);
      }
      selector.scope_limit_count = (u32)limit_count;
    }
  }
  c_ws(p);
  if (c_peek(p) != '{') {
    css_fail(p, "unsupported @scope syntax");
    css_mark_scope_error(p);
    return false;
  }
  if (p->scope_count >= MY_CSS_MAX_SCOPE_NESTING ||
      at_rule_depth >= MY_CSS_MAX_AT_RULE_NESTING) {
    css_fail(p, "CSS scope nesting depth exceeded");
    return false;
  }
  if (has_root || selector.scope_limit_count != 0u) {
    p->scope_selectors[p->scope_count] = selector;
    p->scope_has_root[p->scope_count] = has_root;
    p->scope_count++;
  }
  c_next(p);
  parsed = css_parse_rules(p, sheet, true, at_rule_depth + 1u, layer_id);
  if (has_root || selector.scope_limit_count != 0u) {
    p->scope_count--;
    p->scope_has_root[p->scope_count] = false;
  }
  return parsed;
}

static bool css_parse_atrule(css_p_t* p, my_css_sheet_t* sheet,
                             size_t media_depth, uint32_t layer_id) {
  char name[MY_CSS_NAME_LEN];

  c_next(p); /* '@' */
  if (!c_ident(p, name, sizeof(name))) {
    css_fail(p, "expected @-rule name");
    return false;
  }
  if (my_str_eq(name, "media")) {
    return css_parse_media_atrule(p, sheet, media_depth, layer_id);
  }
  if (my_str_eq(name, "supports")) {
    return css_parse_supports_atrule(p, sheet, media_depth, layer_id);
  }
  if (my_str_eq(name, "layer")) {
    return css_parse_layer_atrule(p, sheet, media_depth, layer_id);
  }
  if (my_str_eq(name, "import")) {
    return css_parse_import_atrule(p, sheet, media_depth, layer_id);
  }
  if (my_str_eq(name, "scope")) {
    return css_parse_scope_atrule(p, sheet, media_depth, layer_id);
  }
  return css_skip_or_reject_atrule(p);
}

static bool css_parse_rules(css_p_t* p, my_css_sheet_t* sheet,
                            bool nested, size_t media_depth,
                            uint32_t layer_id) {
  for (;;) {
    my_css_rule_t* rule;

    c_ws(p);
    if (c_failed(p)) {
      return false;
    }
    if (c_peek(p) < 0) {
      if (nested) {
        css_fail(p, "unterminated @media");
        return false;
      }
      return true;
    }
    if (nested && c_peek(p) == '}') {
      c_next(p);
      return true;
    }
    if (c_peek(p) == '}') {
      css_fail(p, "unexpected '}'");
      return false;
    }
    if (c_peek(p) == '@') {
      if (!css_parse_atrule(p, sheet, media_depth, layer_id)) {
        return false;
      }
      continue;
    }
    rule = css_rule(p, layer_id);
    if (rule == NULL) {
      return false;
    }
    if (my_darray_push(sheet->rules, rule) != MY_RET_OK) {
      css_rule_destroy(p->allocator, rule);
      css_fail(p, "oom");
      return false;
    }
  }
}

my_css_sheet_t* my_css_parse_with_options(
    const my_allocator_t* allocator, const char* css, size_t len,
    const my_css_parse_options_t* options, my_css_error_t* err) {
  css_p_t p;
  my_css_sheet_t* sheet;
  uint32_t flags = options != NULL ? options->flags : MY_CSS_PARSE_DEFAULT;
  if (err != NULL) {
    memset(err, 0, sizeof(*err));
  }
  if (css == NULL) {
    if (err != NULL) {
      err->code = MY_CSS_ERROR_INVALID_PARAMS;
      snprintf(err->msg, sizeof(err->msg), "%s", "invalid CSS input");
    }
    return NULL;
  }
  memset(&p, 0, sizeof(p));
  p.allocator = allocator;
  p.s = css;
  p.len = len;
  p.line = 1;
  p.col = 1;
  p.err = err;
  p.flags = flags;
  p.media = options != NULL ? options->media : NULL;
  p.resolve_import = options != NULL ? options->resolve_import : NULL;
  p.import_context = options != NULL ? options->import_context : NULL;
  p.import_total_bytes = len;
  if ((flags & ~(uint32_t)MY_CSS_PARSE_STRICT_AT_RULES) != 0u) {
    css_fail(&p, "unknown CSS parse flags");
    return NULL;
  }
  if (len > MY_CSS_MAX_BYTES) {
    css_fail(&p, "CSS input exceeds resource budget");
    return NULL;
  }
  if (!css_media_capabilities_valid(p.media)) {
    css_fail(&p, "unsupported media capability");
    if (err != NULL) err->code = MY_CSS_ERROR_UNSUPPORTED_FEATURE;
    return NULL;
  }
  sheet = (my_css_sheet_t*)my_mem_calloc(allocator, 1,
                                         sizeof(my_css_sheet_t));
  if (sheet == NULL) {
    return NULL;
  }
  sheet->allocator = allocator;
  sheet->rules = my_darray_create(allocator, 0);
  if (sheet->rules == NULL) {
    my_mem_free(allocator, sheet);
    return NULL;
  }
  if (css_parse_rules(&p, sheet, false, 0u, MY_CSS_UNLAYERED_ORDER)) {
    css_finalize_layer_order(&p, sheet);
    return sheet;
  }
  my_css_sheet_destroy(sheet);
  return NULL;
}

my_css_sheet_t* my_css_parse_ex(const my_allocator_t* allocator,
                                const char* css, size_t len, uint32_t flags,
                                my_css_error_t* err) {
  my_css_parse_options_t options = {flags, NULL, NULL, NULL};
  return my_css_parse_with_options(allocator, css, len, &options, err);
}

my_css_sheet_t* my_css_parse(const my_allocator_t* allocator,
                             const char* css, size_t len,
                             my_css_error_t* err) {
  return my_css_parse_ex(allocator, css, len, MY_CSS_PARSE_DEFAULT, err);
}

my_css_sheet_t* my_css_parse_media_ex2(
    const my_allocator_t* allocator, const char* css, size_t len,
    uint32_t flags, const my_css_media_context_ex_t* media,
    my_css_error_t* err) {
  my_css_parse_options_t options = {flags, media, NULL, NULL};
  return my_css_parse_with_options(allocator, css, len, &options, err);
}

my_css_sheet_t* my_css_parse_media_ex(
    const my_allocator_t* allocator, const char* css, size_t len,
    uint32_t flags, const my_css_media_context_t* media,
    my_css_error_t* err) {
  my_css_media_context_ex_t extended;
  if (media == NULL) {
    return my_css_parse_media_ex2(allocator, css, len, flags, NULL, err);
  }
  extended.base = *media;
  extended.known = 0u;
  return my_css_parse_media_ex2(allocator, css, len, flags, &extended, err);
}

const my_css_capabilities_t* my_css_capabilities(void) {
  static const my_css_capabilities_t capabilities = {
      (uint32_t)(MY_CSS_FEATURE_RULES | MY_CSS_FEATURE_SELECTORS |
                 MY_CSS_FEATURE_TYPED_VALUES | MY_CSS_FEATURE_CASCADE |
                 MY_CSS_FEATURE_AT_RULES | MY_CSS_FEATURE_CONDITIONAL_MEDIA |
                 MY_CSS_FEATURE_SUPPORTS | MY_CSS_FEATURE_LAYERS |
                 MY_CSS_FEATURE_IMPORTS | MY_CSS_FEATURE_SCOPE),
      (uint32_t)MY_CSS_PARSE_STRICT_AT_RULES, MY_CSS_MAX_BYTES,
      MY_CSS_MAX_ANCESTORS};
  return &capabilities;
}

void my_css_sheet_destroy(my_css_sheet_t* sheet) {
  size_t i, n;
  if (sheet == NULL) {
    return;
  }
  n = my_darray_size(sheet->rules);
  for (i = 0; i < n; i++) {
    css_rule_destroy(sheet->allocator,
                     (my_css_rule_t*)my_darray_get(sheet->rules, i));
  }
  my_darray_destroy(sheet->rules);
  my_mem_free(sheet->allocator, sheet);
}

size_t my_css_rule_count(const my_css_sheet_t* sheet) {
  return sheet != NULL ? my_darray_size(sheet->rules) : 0;
}

const my_css_rule_t* my_css_rule(const my_css_sheet_t* sheet, size_t index) {
  if (sheet == NULL || index >= my_darray_size(sheet->rules)) {
    return NULL;
  }
  return (const my_css_rule_t*)my_darray_get(sheet->rules, index);
}

size_t my_css_selector_count(const my_css_rule_t* rule) {
  return rule != NULL ? my_darray_size(rule->selectors) : 0;
}

const my_css_selector_t* my_css_selector(const my_css_rule_t* rule,
                                         size_t index) {
  if (rule == NULL || index >= my_darray_size(rule->selectors)) {
    return NULL;
  }
  return (const my_css_selector_t*)my_darray_get(rule->selectors, index);
}

size_t my_css_decl_count(const my_css_rule_t* rule) {
  return rule != NULL ? my_darray_size(rule->decls) : 0;
}

const my_css_decl_t* my_css_decl(const my_css_rule_t* rule, size_t index) {
  if (rule == NULL || index >= my_darray_size(rule->decls)) {
    return NULL;
  }
  return (const my_css_decl_t*)my_darray_get(rule->decls, index);
}

/* ---------------- theme bridge ---------------- */

static bool css_bounded_cstr_len(const char* css, size_t* length) {
  size_t i;
  for (i = 0; i < MY_CSS_MAX_BYTES; i++) {
    if (css[i] == '\0') {
      *length = i;
      return true;
    }
  }
  return false;
}

static my_ret_t my_theme_load_css_internal(
    my_theme_t* theme, const char* css,
    const my_css_parse_options_t* options) {
  my_css_sheet_t* sheet;
  my_theme_t* candidate;
  my_darray_t* old_entries;
  my_theme_t* target;
  size_t ri, si, di, layer_pass;
  my_ret_t ret = MY_RET_OK;
  size_t css_len;
  if (theme == NULL || css == NULL) {
    return MY_RET_INVALID_PARAMS;
  }
  if (!css_bounded_cstr_len(css, &css_len)) {
    return MY_RET_FAIL;
  }
  sheet = my_css_parse_with_options(theme->allocator, css, css_len, options,
                                    NULL);
  if (sheet == NULL) {
    return MY_RET_FAIL;
  }
  candidate = my_theme_clone(theme);
  if (candidate == NULL) {
    my_css_sheet_destroy(sheet);
    return MY_RET_OOM;
  }
  target = candidate;
  for (layer_pass = 0u; layer_pass <= MY_CSS_MAX_LAYERS; ++layer_pass) {
    uint32_t wanted_layer = layer_pass == MY_CSS_MAX_LAYERS
                                ? MY_CSS_UNLAYERED_ORDER
                                : (uint32_t)layer_pass;
    for (ri = 0; ri < my_css_rule_count(sheet); ri++) {
      const my_css_rule_t* rule = my_css_rule(sheet, ri);
      if (rule->layer_order != wanted_layer) continue;
    for (si = 0; si < my_css_selector_count(rule); si++) {
      const my_css_selector_t* sel = my_css_selector(rule, si);
      my_theme_ancestor_t ancestors[MY_THEME_MAX_ANCESTORS];
      my_theme_ancestor_t scope_limits[MY_THEME_MAX_SCOPE_LIMITS];
      size_t scope_limit_root_indices[MY_THEME_MAX_SCOPE_LIMITS];
      int32_t specificity = rule->layer_order == MY_CSS_UNLAYERED_ORDER
                                ? 0
                                : -((int32_t)(MY_CSS_MAX_LAYERS -
                                              rule->layer_order) *
                                    MY_CSS_LAYER_SPECIFICITY_STRIDE);
      const char* p;
      size_t ai;
      memset(ancestors, 0, sizeof(ancestors));
      memset(scope_limits, 0, sizeof(scope_limits));
      memset(scope_limit_root_indices, 0, sizeof(scope_limit_root_indices));
      for (ai = 0; ai < sel->ancestor_count; ai++) {
        snprintf(ancestors[ai].widget_type, sizeof(ancestors[ai].widget_type),
                 "%s", sel->ancestors[ai].widget_type);
        snprintf(ancestors[ai].name, sizeof(ancestors[ai].name), "%s",
                 sel->ancestors[ai].id);
        snprintf(ancestors[ai].style_class,
                 sizeof(ancestors[ai].style_class), "%s",
                 sel->ancestors[ai].style_class);
      }
      for (ai = 0u; ai < sel->scope_limit_count; ++ai) {
        if (ai >= MY_THEME_MAX_SCOPE_LIMITS ||
            (sel->scope_limit_root_index[ai] != MY_CSS_SCOPE_ROOT_IMPLICIT &&
             sel->scope_limit_root_index[ai] >= sel->ancestor_count)) {
          ret = MY_RET_INVALID_PARAMS;
          break;
        }
        snprintf(scope_limits[ai].widget_type,
                 sizeof(scope_limits[ai].widget_type), "%s",
                 sel->scope_limits[ai].widget_type);
        snprintf(scope_limits[ai].name, sizeof(scope_limits[ai].name), "%s",
                 sel->scope_limits[ai].id);
        snprintf(scope_limits[ai].style_class,
                 sizeof(scope_limits[ai].style_class), "%s",
                 sel->scope_limits[ai].style_class);
        scope_limit_root_indices[ai] = sel->scope_limit_root_index[ai];
      }
      if (ret != MY_RET_OK) break;
      if (sel->id[0] != '\0') {
        specificity += 10000;
      }
      for (p = sel->style_class; *p != '\0'; p++) {
        if (*p != ' ' && (p == sel->style_class || p[-1] == ' ')) {
          specificity += 100;
        }
      }
      if (sel->widget_type[0] != '\0') {
        specificity += 1;
      }
      if (sel->ancestor_count > 0u) {
        for (ai = 0; ai < sel->ancestor_count; ai++) {
          if (sel->ancestors[ai].id[0] != '\0') {
            specificity += 10000;
          }
          for (p = sel->ancestors[ai].style_class; *p != '\0'; p++) {
            if (*p != ' ' && (p == sel->ancestors[ai].style_class ||
                              p[-1] == ' ')) {
              specificity += 100;
            }
          }
          if (sel->ancestors[ai].widget_type[0] != '\0') {
            specificity += 1;
          }
        }
      } else if (sel->ancestor_type[0] != '\0') {
        specificity += 1;
        for (p = sel->ancestor_type; *p != '\0'; p++) {
          if (*p == '.') {
            specificity += 100;
          }
        }
      }
      for (di = 0; di < my_css_decl_count(rule); di++) {
        const my_css_decl_t* d = my_css_decl(rule, di);
        if (sel->state >= 0) {
          ret = my_theme_set_ex5(
              target, sel->widget_type, sel->id, sel->style_class,
              ancestors, sel->ancestor_count, sel->ancestor_direct_path,
              scope_limits, sel->scope_limit_count,
              scope_limit_root_indices, (my_widget_state_t)sel->state,
              d->key, &d->value, specificity + 100);
        } else {
          /* no pseudo: write ONLY the normal slot — the state->normal
           * fallback covers the rest, so pseudo rules (more specific)
           * always win regardless of source order (CSS specificity) */
          ret = my_theme_set_ex5(
              target, sel->widget_type, sel->id, sel->style_class,
              ancestors, sel->ancestor_count, sel->ancestor_direct_path,
              scope_limits, sel->scope_limit_count,
              scope_limit_root_indices, MY_STATE_NORMAL, d->key, &d->value,
              specificity);
        }
        if (ret != MY_RET_OK) {
          break;
        }
      }
      if (ret != MY_RET_OK) {
        break;
      }
    }
      if (ret != MY_RET_OK) {
        break;
      }
    }
    if (ret != MY_RET_OK) break;
  }
  my_css_sheet_destroy(sheet);
  if (ret != MY_RET_OK) {
    my_theme_destroy(candidate);
    return ret;
  }
  old_entries = theme->entries;
  theme->entries = candidate->entries;
  candidate->entries = old_entries;
  my_theme_destroy(candidate);
  return ret;
}

my_ret_t my_theme_load_css(my_theme_t* theme, const char* css) {
  return my_theme_load_css_with_options(theme, css, NULL);
}

my_ret_t my_theme_load_css_ex(my_theme_t* theme, const char* css,
                              uint32_t flags) {
  my_css_parse_options_t options = {flags, NULL, NULL, NULL};
  return my_theme_load_css_internal(theme, css, &options);
}

my_ret_t my_theme_load_css_media_ex(
    my_theme_t* theme, const char* css, uint32_t flags,
    const my_css_media_context_t* media) {
  if (media == NULL) return MY_RET_INVALID_PARAMS;
  {
    my_css_parse_options_t options = {flags, NULL, NULL, NULL};
    my_css_media_context_ex_t extended = {*media, 0u};
    options.media = &extended;
    return my_theme_load_css_internal(theme, css, &options);
  }
}

my_ret_t my_theme_load_css_media_ex2(
    my_theme_t* theme, const char* css, uint32_t flags,
    const my_css_media_context_ex_t* media) {
  if (media == NULL) return MY_RET_INVALID_PARAMS;
  {
    my_css_parse_options_t options = {flags, media, NULL, NULL};
    return my_theme_load_css_internal(theme, css, &options);
  }
}

my_ret_t my_theme_load_css_with_options(
    my_theme_t* theme, const char* css,
    const my_css_parse_options_t* options) {
  return my_theme_load_css_internal(theme, css, options);
}
