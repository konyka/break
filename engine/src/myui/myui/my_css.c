/**
 * @file my_css.c
 * @brief CSS subset parser + theme bridge (M18a) — subset spec in
 * my_css.h / docs/css.md.
 */
#include "myui/my_css.h"
#include "myui/my_widget.h"

#include <errno.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#include "myc/my_str.h"

/* ---------------- lexer-ish helpers ---------------- */

/* R622: one root item of an @scope selector list — subject compound plus
 * its own ancestor path (leaner than my_css_selector_t: limits live on the
 * frame, not per root item). */
typedef struct css_scope_root_t {
  my_css_ancestor_t subject;
  u32 ancestor_count;
  my_css_ancestor_t ancestors[MY_CSS_MAX_ANCESTORS];
  bool ancestor_direct_path[MY_CSS_MAX_ANCESTORS];
} css_scope_root_t;

/* R622: one active @scope frame — bounded root selector list plus the
 * limits shared by all root items. */
typedef struct css_scope_frame_t {
  u32 root_count; /* 0 = implicit root */
  css_scope_root_t roots[MY_CSS_MAX_SCOPE_NESTING];
  u32 scope_limit_count;
  my_css_scope_limit_t scope_limits[MY_CSS_MAX_SCOPE_NESTING];
} css_scope_frame_t;

/* Cap on the root-list cross-product expansion per rule selector
 * (nested scopes multiply their root counts). */
#define MY_CSS_MAX_SCOPE_VARIANTS 16u

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
  const my_css_container_context_t* container; /* R663 */
  bool failed;
  my_css_import_resolver_fn_t resolve_import;
  void* import_context;
  size_t import_total_bytes;
  size_t import_count;
  size_t import_depth;
  char import_stack[MY_CSS_MAX_IMPORT_DEPTH]
                   [MY_CSS_MAX_IMPORT_PATH_BYTES + 1u];
  css_scope_frame_t scope_frames[MY_CSS_MAX_SCOPE_NESTING];
  size_t scope_count;
  /* R629: nested `&` rules are collected here during a rule's block and
   * flushed AFTER the parent rule is appended, preserving source order. */
  my_darray_t* nest_pending;
  /* R656: import-position conformance — top-level statement count (for the
   * @charset first-statement rule) and whether the @import window closed
   * (a top-level style rule or conditional at-rule was seen). */
  u32 top_statements;
  bool import_window_closed;
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
      strcmp(msg, "scope ancestor depth exceeded") == 0 ||
      strcmp(msg, "scope selector list expansion exceeded") == 0) {
    return MY_CSS_ERROR_UNSUPPORTED_FEATURE;
  }
  if (strcmp(msg, "unsupported @-rule") == 0 ||
      strcmp(msg, "unsupported nested @-rule") == 0) {
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
    if (strcmp(msg, "unsupported @-rule") == 0 ||
        strcmp(msg, "unsupported nested @-rule") == 0) {
      p->err->capability = (uint32_t)MY_CSS_FEATURE_AT_RULES;
    } else if (strcmp(msg, "CSS scope nesting depth exceeded") == 0 ||
               strcmp(msg, "scope ancestor depth exceeded") == 0 ||
               strcmp(msg, "scope selector list expansion exceeded") == 0 ||
               strcmp(msg, "@scope nesting depth exceeded") == 0 ||
               strcmp(msg, "invalid @scope root selector") == 0 ||
               strcmp(msg, "invalid @scope limit selector") == 0 ||
               strcmp(msg, ":scope outside @scope") == 0 ||
               strcmp(msg, ":scope requires an explicit scope root") == 0 ||
               strcmp(msg, ":scope must be unqualified and outermost") == 0 ||
               strcmp(msg, "unsupported @scope syntax") == 0) {
      p->err->capability = (uint32_t)MY_CSS_FEATURE_SCOPE;
    } else if (strcmp(msg, "& outside a rule") == 0 ||
               strcmp(msg, "invalid & nested selector") == 0 ||
               strcmp(msg, "CSS & nesting depth exceeded") == 0) {
      p->err->capability = (uint32_t)MY_CSS_FEATURE_NESTING;
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

/* R629: generic variant — pin an already-recorded error to a capability. */
static void css_mark_capability(css_p_t* p, uint32_t capability) {
  if (p->err != NULL && p->err->msg[0] != '\0') {
    p->err->capability = capability;
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
  /* R629: '&' = the parent-selector marker for CSS nesting (resolved by the
   * css_rule declaration block's nested-rule desugar). */
  if (c_peek(p) == '&') {
    c_next(p);
    out->nest_ref = true;
  }
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
      out->id[0] == '\0' && c_peek(p) != ':' && !universal &&
      !out->nest_ref) {
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
    } else if (my_str_eq(pseudo, "scope")) {
      /* R627: parse-time marker — the @scope splice in css_rule validates
       * and substitutes it. R639/R640: trailing class qualifiers and one
       * state qualifier may stack (`:scope.dark:hover`) — they merge into
       * the substituted root subject. An id or a second pseudo stays
       * rejected. */
      out->scope_ref = true;
      for (;;) {
        if (c_peek(p) == '.') {
          char buf[MY_CSS_NAME_LEN];
          size_t have;
          size_t need;
          c_next(p);
          if (!c_ident(p, buf, sizeof(buf))) {
            css_fail(p, "bad selector component");
            return false;
          }
          have = strlen(out->style_class);
          need = strlen(buf);
          if (have + (have > 0u ? 1u : 0u) + need >=
              sizeof(out->style_class)) {
            css_fail(p, "selector classes too long");
            return false;
          }
          if (have > 0u) {
            out->style_class[have++] = ' ';
          }
          memcpy(out->style_class + have, buf, need + 1u);
          continue;
        }
        if (c_peek(p) == ':' && out->state == -1) {
          char state_pseudo[16];
          c_next(p);
          if (!c_ident(p, state_pseudo, sizeof(state_pseudo))) {
            css_fail(p, "bad pseudo class");
            return false;
          }
          if (my_str_eq(state_pseudo, "hover")) {
            out->state = MY_STATE_HOVER;
          } else if (my_str_eq(state_pseudo, "pressed")) {
            out->state = MY_STATE_PRESSED;
          } else if (my_str_eq(state_pseudo, "disabled")) {
            out->state = MY_STATE_DISABLED;
          } else {
            css_fail(p, ":scope must be unqualified and outermost");
            return false;
          }
          continue;
        }
        break;
      }
      if (c_peek(p) == ':' || c_peek(p) == '#') {
        css_fail(p, ":scope must be unqualified and outermost");
        return false;
      }
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

/* R665: custom property (`--*`) value — CSS Custom Properties L1 stores
 * the raw token stream (ws-trimmed; `var()` stays unresolved text until
 * the substitution phase). The capture is quote/escape and ()/[]/{} depth
 * aware; a trailing top-level `!important` sets the flag and is stripped,
 * any other top-level '!' invalidates the declaration. */
static bool css_custom_value(css_p_t* p, my_value_t* out, bool* important) {
  size_t start = p->pos;
  size_t end;
  size_t bang = p->pos;
  unsigned bangs = 0u;
  char quote = '\0';
  unsigned depth = 0u;
  char* buf;
  for (;;) {
    int c = c_peek(p);
    if (c < 0) {
      return false;
    }
    if (quote != '\0') {
      if (c == '\\' && p->pos + 1u < p->len) {
        c_next(p);
        c_next(p);
        continue;
      }
      if (c == quote) {
        quote = '\0';
      }
      c_next(p);
      continue;
    }
    if (c == '\'' || c == '"') {
      quote = (char)c;
    } else if (c == '(' || c == '[' || c == '{') {
      depth++;
    } else if (c == '}' && depth == 0u) {
      break; /* the block's own close */
    } else if (c == ')' || c == ']' || c == '}') {
      if (depth == 0u) {
        return false; /* underflow: top-level ')' or ']' */
      }
      depth--;
    } else if (c == ';' && depth == 0u) {
      break;
    } else if (c == '!' && depth == 0u) {
      bang = p->pos;
      bangs++;
    }
    c_next(p);
  }
  end = p->pos;
  while (end > start &&
         (p->s[end - 1u] == ' ' || p->s[end - 1u] == '\t' ||
          p->s[end - 1u] == '\r' || p->s[end - 1u] == '\n')) {
    end--;
  }
  if (bangs > 0u) {
    /* only a single trailing `!important` (ws allowed after '!') is
     * legal; any other top-level '!' invalidates the declaration. */
    size_t b = bang + 1u;
    char word[16];
    size_t wl = 0u;
    while (b < end && (p->s[b] == ' ' || p->s[b] == '\t' ||
                       p->s[b] == '\r' || p->s[b] == '\n')) {
      b++;
    }
    while (b < end && c_ident_char((unsigned char)p->s[b]) &&
           wl + 1u < sizeof(word)) {
      word[wl++] = p->s[b++];
    }
    word[wl] = '\0';
    if (bangs != 1u || !my_str_eq(word, "important") || b != end) {
      return false;
    }
    *important = true;
    end = bang;
    while (end > start &&
           (p->s[end - 1u] == ' ' || p->s[end - 1u] == '\t' ||
            p->s[end - 1u] == '\r' || p->s[end - 1u] == '\n')) {
      end--;
    }
  }
  buf = (char*)my_mem_alloc(p->allocator, end - start + 1u);
  if (buf == NULL) {
    return false;
  }
  memcpy(buf, p->s + start, end - start);
  buf[end - start] = '\0';
  my_value_set_str(out, buf);
  my_mem_free(p->allocator, buf);
  return true;
}

/* R666: does the value text ahead mention a var( function token (any
 * bracket depth, quotes excluded)? Such declarations are stored as raw
 * text (css_custom_value) for lookup-time substitution instead of the
 * typed css_value path. Read-only scan; p is untouched. */
static bool css_value_mentions_var(const css_p_t* p) {
  size_t i = p->pos;
  char quote = '\0';
  unsigned depth = 0u;
  while (i < p->len) {
    char c = p->s[i];
    if (quote != '\0') {
      if (c == '\\' && i + 1u < p->len) {
        i += 2u;
        continue;
      }
      if (c == quote) {
        quote = '\0';
      }
      i++;
      continue;
    }
    if (c == '\'' || c == '"') {
      quote = c;
    } else if (c == '(' || c == '[' || c == '{') {
      depth++;
    } else if (c == ')' || c == ']' || c == '}') {
      if (depth == 0u) {
        break;
      }
      depth--;
    } else if (c == ';' && depth == 0u) {
      break;
    } else if (c == 'v' &&
               (i == 0u || !c_ident_char((unsigned char)p->s[i - 1u])) &&
               i + 3u < p->len && p->s[i + 1u] == 'a' &&
               p->s[i + 2u] == 'r' && p->s[i + 3u] == '(') {
      return true;
    }
    i++;
  }
  return false;
}

/* R669: container-type takes its keyword set; container-name is a
 * whitespace-separated ident list with `none` standing alone. */
static bool css_container_property_value_ok(const char* key,
                                            const char* text) {
  if (my_str_eq(key, "container-type")) {
    return my_str_eq(text, "normal") || my_str_eq(text, "size") ||
           my_str_eq(text, "inline-size");
  }
  /* container-name */
  {
    size_t i = 0u;
    size_t len = strlen(text);
    unsigned idents = 0u;
    bool saw_none = false;
    while (i < len) {
      char word[32];
      size_t wl = 0u;
      while (i < len && (text[i] == ' ' || text[i] == '\t' ||
                         text[i] == '\r' || text[i] == '\n')) {
        i++;
      }
      if (i >= len) {
        break;
      }
      if (!c_ident_char((unsigned char)text[i])) {
        return false;
      }
      while (i < len && c_ident_char((unsigned char)text[i])) {
        if (wl + 1u >= sizeof(word)) {
          return false;
        }
        word[wl++] = text[i++];
      }
      word[wl] = '\0';
      if (my_str_eq(word, "none")) {
        saw_none = true;
      }
      idents++;
    }
    if (idents == 0u) {
      return false;
    }
    return !saw_none || idents == 1u;
  }
}

/* R672: bounded @property syntax primitives — <color>/<length>/
 * <number>/<integer>/<string>/<percentage> and `*` (unknown syntax
 * strings carry no enforcement, documented). The text must parse as one
 * full value of the primitive's type. */
static bool css_syntax_is_primitive(const char* s) {
  return my_str_eq(s, "<color>") || my_str_eq(s, "<length>") ||
         my_str_eq(s, "<number>") || my_str_eq(s, "<integer>") ||
         my_str_eq(s, "<string>") || my_str_eq(s, "<percentage>");
}

static bool css_property_syntax_primitive_check(const char* prim,
                                                const char* text) {
  css_p_t probe;
  my_value_t v;
  bool ok;
  if (my_str_eq(prim, "<percentage>")) {
    /* R676: a number immediately followed by '%' — no intervening
     * whitespace, no other unit. Dedicated scan: the generic css_value
     * probe would swallow a `px` suffix before the '%' check. */
    double number;
    bool integral;
    memset(&probe, 0, sizeof(probe));
    probe.s = text;
    probe.len = strlen(text);
    probe.line = 1;
    probe.col = 1;
    c_ws(&probe);
    if (!css_number(&probe, &number, &integral)) {
      return false;
    }
    (void)number;
    (void)integral;
    if (c_peek(&probe) != '%') {
      return false;
    }
    c_next(&probe);
    c_ws(&probe);
    return c_peek(&probe) < 0;
  }
  if (!my_str_eq(prim, "<color>") && !my_str_eq(prim, "<length>") &&
      !my_str_eq(prim, "<number>") && !my_str_eq(prim, "<integer>") &&
      !my_str_eq(prim, "<string>")) {
    return true;
  }
  my_value_init(&v, NULL);
  memset(&probe, 0, sizeof(probe));
  probe.s = text;
  probe.len = strlen(text);
  probe.line = 1;
  probe.col = 1;
  c_ws(&probe);
  ok = css_value(&probe, &v);
  if (ok) {
    c_ws(&probe);
    ok = c_peek(&probe) < 0;
  }
  if (ok) {
    if (my_str_eq(prim, "<color>")) {
      ok = my_value_type(&v) == MY_VALUE_UINT32;
    } else if (my_str_eq(prim, "<length>") ||
               my_str_eq(prim, "<number>")) {
      ok = my_value_type(&v) == MY_VALUE_INT32 ||
           my_value_type(&v) == MY_VALUE_DOUBLE;
    } else if (my_str_eq(prim, "<integer>")) {
      ok = my_value_type(&v) == MY_VALUE_INT32;
    } else { /* <string>: quoted only */
      size_t first = 0u;
      while (text[first] == ' ' || text[first] == '\t' ||
             text[first] == '\r' || text[first] == '\n') {
        first++;
      }
      ok = my_value_type(&v) == MY_VALUE_STR &&
           (text[first] == '"' || text[first] == '\'');
    }
  }
  my_value_reset(&v);
  return ok;
}

/* R678: byte-exact ident alternative — the text trimmed of surrounding
 * whitespace equals the keyword (engine lowercase-exact convention). */
static bool css_syntax_ident_matches(const char* ident, const char* text) {
  const char* start = text;
  const char* end = text + strlen(text);
  size_t ident_len = strlen(ident);
  while (start < end && (*start == ' ' || *start == '\t' ||
                         *start == '\r' || *start == '\n')) {
    start++;
  }
  while (end > start && (end[-1] == ' ' || end[-1] == '\t' ||
                         end[-1] == '\r' || end[-1] == '\n')) {
    end--;
  }
  return (size_t)(end - start) == ident_len &&
         memcmp(start, ident, ident_len) == 0;
}

static bool css_syntax_ident_ok(const char* s, size_t length) {
  size_t i;
  if (length == 0u) {
    return false;
  }
  for (i = 0u; i < length; i++) {
    if (!c_ident_char((unsigned char)s[i])) {
      return false;
    }
  }
  return true;
}

/* R678: `a | b` combinations — the value matches when any trimmed
 * alternative accepts it. Ident alternatives compare byte-exact;
 * primitive alternatives reuse the R672/R676 gates. A combination
 * holding an unrecognized component (unknown primitive, malformed or
 * empty alternative) stays unenforced: the R672 unknown-string
 * deferral, applied per whole combination. */
static bool css_property_syntax_multichoice_check(const char* syntax,
                                                  const char* text) {
  char buf[64];
  char* cursor;
  snprintf(buf, sizeof(buf), "%s", syntax);
  cursor = buf;
  for (;;) {
    char* bar = strchr(cursor, '|');
    char* end = bar != NULL ? bar : cursor + strlen(cursor);
    char* start = cursor;
    while (start < end && (*start == ' ' || *start == '\t' ||
                           *start == '\r' || *start == '\n')) {
      start++;
    }
    while (end > start && (end[-1] == ' ' || end[-1] == '\t' ||
                           end[-1] == '\r' || end[-1] == '\n')) {
      end--;
    }
    *end = '\0';
    if (start == end) {
      return true; /* empty alternative: unenforced */
    }
    if (start[0] == '<') {
      if (!css_syntax_is_primitive(start)) {
        return true; /* unknown primitive: unenforced */
      }
      if (css_property_syntax_primitive_check(start, text)) {
        return true;
      }
    } else {
      if (!css_syntax_ident_ok(start, (size_t)(end - start))) {
        return true; /* malformed alternative: unenforced */
      }
      if (css_syntax_ident_matches(start, text)) {
        return true;
      }
    }
    if (bar == NULL) {
      break;
    }
    cursor = bar + 1;
  }
  return false;
}

static bool css_property_syntax_check(const char* syntax, const char* text) {
  if (syntax == NULL || syntax[0] == '\0' || my_str_eq(syntax, "*")) {
    return true;
  }
  if (strchr(syntax, '|') != NULL) {
    return css_property_syntax_multichoice_check(syntax, text);
  }
  if (!css_syntax_is_primitive(syntax)) {
    /* R680: a lone ident syntax string ("small") enforces byte-exact
     * — the same gate as an ident alternative inside a combination.
     * Anything else stays unenforced (R672 deferral). */
    if (css_syntax_ident_ok(syntax, strlen(syntax))) {
      return css_syntax_ident_matches(syntax, text);
    }
    return true; /* unknown syntax string: unenforced */
  }
  return css_property_syntax_primitive_check(syntax, text);
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
    {"container-type", MY_STYLE_CONTAINER_TYPE},
    {"container-name", MY_STYLE_CONTAINER_NAME},
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
static bool css_media_condition(css_p_t* p, const char* query, size_t length,
                                bool* matches, bool* conditional);
static bool css_supports_condition(const char* query, size_t length,
                                   const my_allocator_t* allocator,
                                   bool* matches);
static bool css_layer_name_valid(const char* name, size_t length);
static uint32_t css_layer_find_or_add(css_p_t* p, const char* name,
                                      size_t length);
static uint32_t css_layer_add_anonymous(css_p_t* p);
static bool css_container_query_matches(css_p_t* p, const char* query,
                                        size_t query_length, bool* matches);
static bool css_container_query_opens(css_p_t* p);

/* R654: !important lifts a declaration into a flat top cascade tier — the
 * boost must clear the deepest layered negative (-64*100000) plus the full
 * normal range (~90k); among important declarations the usual specificity
 * applies. */
#define MY_CSS_IMPORTANT_SPECIFICITY 10000000

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

/* R651: a bad media qualifier on @import — strict rejects with the IMPORTS
 * capability; compatibility mode skips just the import (the statement has
 * already been consumed, so no at-rule scan). */
static bool css_import_qualifier_fail(css_p_t* p) {
  if ((p->flags & MY_CSS_PARSE_STRICT_AT_RULES) != 0u) {
    return css_skip_or_reject_atrule_with_capability(
        p, (uint32_t)MY_CSS_FEATURE_IMPORTS);
  }
  MY_LOGW("my_css: skipping @import (invalid media qualifier)");
  return true;
}

/* R652/R653: qualifier text helpers — whitespace test and a balanced paren
 * group scan (quote/escape aware). Returns the index of the matching ')' of
 * the group opening at text[start]. */
static bool css_qualifier_is_ws(char c) {
  return c == ' ' || c == '\t' || c == '\r' || c == '\n';
}

static bool css_qualifier_group_end(const char* text, size_t length,
                                    size_t start, size_t* end) {
  size_t depth = 0u;
  char quote = '\0';
  size_t i;
  for (i = start; i < length; ++i) {
    char ch = text[i];
    if (quote != '\0') {
      if (ch == '\\' && i + 1u < length) {
        ++i;
        continue;
      }
      if (ch == quote) quote = '\0';
      continue;
    }
    if (ch == '\'' || ch == '"') {
      quote = ch;
    } else if (ch == '(') {
      depth++;
    } else if (ch == ')') {
      depth--;
      if (depth == 0u) {
        *end = i;
        return true;
      }
    }
  }
  return false;
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
  uint32_t import_layer = layer_id;

  if (!css_read_import_path(p, path, sizeof(path), &path_len)) {
    return css_skip_or_reject_atrule_with_capability(
        p, (uint32_t)MY_CSS_FEATURE_IMPORTS);
  }
  /* R651: optional media qualifier between the path and ';' — evaluated
   * with the full media-condition machinery (R650); a non-matching import
   * is skipped without resolving. */
  c_ws(p);
  if (c_peek(p) == ';') {
    c_next(p);
  } else {
    char query[MY_CSS_MAX_MEDIA_QUERY_BYTES + 1u];
    size_t query_length = 0u;
    size_t paren_depth = 0u;
    char quote = '\0';
    bool query_matches = false;
    bool conditional = false;
    for (;;) {
      int c = c_peek(p);
      if (c < 0) return css_import_qualifier_fail(p);
      if (quote != '\0') {
        if (query_length >= MY_CSS_MAX_MEDIA_QUERY_BYTES) {
          css_fail(p, "media query too long");
          return false;
        }
        query[query_length++] = (char)c_next(p);
        if (c == '\\' && c_peek(p) >= 0) {
          if (query_length >= MY_CSS_MAX_MEDIA_QUERY_BYTES) {
            css_fail(p, "media query too long");
            return false;
          }
          query[query_length++] = (char)c_next(p);
        } else if (c == quote) {
          quote = '\0';
        }
        continue;
      }
      if (c == '\'' || c == '"') {
        quote = (char)c;
      } else if (c == '(') {
        paren_depth++;
      } else if (c == ')' && paren_depth > 0u) {
        paren_depth--;
      } else if (c == ';' && paren_depth == 0u) {
        break;
      }
      if (query_length >= MY_CSS_MAX_MEDIA_QUERY_BYTES) {
        css_fail(p, "media query too long");
        return false;
      }
      query[query_length++] = (char)c_next(p);
    }
    /* the keyword-boundary checks below read one byte past the qualifier —
     * terminate so that byte is never uninitialized stack garbage. */
    query[query_length] = '\0';
    c_next(p); /* ';' */
    {
      /* R652/R653: the qualifier is a three-stage pipeline — an optional
       * leading `layer(name)` (R653), then an optional `supports(...)`
       * (R652), then the media query (R651). */
      const char* media_query = query;
      size_t media_length = query_length;
      size_t qpos = 0u;
      while (qpos < query_length && css_qualifier_is_ws(query[qpos])) qpos++;
      /* R653/R655: `layer(name)` — the imported rules carry the named
       * layer's order; bare `layer` (anonymous, R655) registers a fresh
       * order per occurrence. */
      if (query_length - qpos >= 5u &&
          memcmp(query + qpos, "layer", 5u) == 0 &&
          !c_ident_char((unsigned char)query[qpos + 5u])) {
        size_t gpos = qpos + 5u;
        size_t end = 0u;
        size_t name_start;
        size_t name_length;
        char full_name[MY_CSS_MAX_LAYER_NAME_BYTES + 1u];
        while (gpos < query_length && css_qualifier_is_ws(query[gpos])) {
          gpos++;
        }
        if (gpos >= query_length || query[gpos] != '(') {
          /* R655: bare `layer` — anonymous import layer, a fresh order per
           * occurrence. */
          import_layer = css_layer_add_anonymous(p);
          if (import_layer == MY_CSS_UNLAYERED_ORDER) {
            return css_import_qualifier_fail(p);
          }
          qpos = gpos;
        } else {
          if (!css_qualifier_group_end(query, query_length, gpos, &end)) {
            return css_import_qualifier_fail(p);
          }
        name_start = gpos + 1u;
        name_length = end - name_start;
        while (name_length > 0u &&
               css_qualifier_is_ws(query[name_start])) {
          name_start++;
          name_length--;
        }
        while (name_length > 0u &&
               css_qualifier_is_ws(query[name_start + name_length - 1u])) {
          name_length--;
        }
        if (!css_layer_name_valid(query + name_start, name_length)) {
          return css_import_qualifier_fail(p);
        }
        if (layer_id != MY_CSS_UNLAYERED_ORDER) {
          /* inside an @layer block the import layer nests (parent.name),
           * mirroring the @layer at-rule. */
          const char* parent = p->layer_names[layer_id];
          size_t parent_len = strlen(parent);
          if (parent_len + 1u + name_length > MY_CSS_MAX_LAYER_NAME_BYTES) {
            css_fail(p, "nested CSS layer name too long");
            return false;
          }
          memcpy(full_name, parent, parent_len);
          full_name[parent_len] = '.';
          memcpy(full_name + parent_len + 1u, query + name_start,
                 name_length);
          name_length += parent_len + 1u;
        } else {
          memcpy(full_name, query + name_start, name_length);
        }
        import_layer = css_layer_find_or_add(p, full_name, name_length);
        if (import_layer == MY_CSS_UNLAYERED_ORDER) {
          return css_import_qualifier_fail(p);
        }
        qpos = end + 1u;
        }
      }
      while (qpos < query_length && css_qualifier_is_ws(query[qpos])) qpos++;
      /* R652: `supports(...)` — exactly one balanced group after the
       * keyword; whatever follows is the media query. */
      if (query_length - qpos >= 9u &&
          memcmp(query + qpos, "supports", 8u) == 0 &&
          !c_ident_char((unsigned char)query[qpos + 8u])) {
        size_t gpos = qpos + 8u;
        size_t end = 0u;
        bool supports_matches = false;
        while (gpos < query_length && css_qualifier_is_ws(query[gpos])) {
          gpos++;
        }
        if (gpos < query_length && query[gpos] == '(') {
          if (!css_qualifier_group_end(query, query_length, gpos, &end)) {
            return css_import_qualifier_fail(p);
          }
          if (!css_supports_condition(query + gpos, end - gpos + 1u,
                                      p->allocator, &supports_matches)) {
            return css_import_qualifier_fail(p);
          }
          if (!supports_matches) {
            return true;
          }
          qpos = end + 1u;
        }
      }
      media_query = query + qpos;
      media_length = query_length - qpos;
      while (media_length > 0u && css_qualifier_is_ws(*media_query)) {
        media_query++;
        media_length--;
      }
      if (quote != '\0' || paren_depth != 0u) {
        return css_import_qualifier_fail(p);
      }
      if (media_length > 0u) {
        if (!css_media_condition(p, media_query, media_length,
                                 &query_matches, &conditional)) {
          return css_import_qualifier_fail(p);
        }
        if (conditional && p->media == NULL) {
          return css_import_qualifier_fail(p);
        }
        if (!query_matches) {
          return true;
        }
      }
    }
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
  parsed = css_parse_rules(p, sheet, false, media_depth, import_layer);
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

/** @brief Fill the legacy single-ancestor view, then push a heap copy of
 * SEL onto the rule's selector group. */
static bool css_rule_push_selector(css_p_t* p, my_css_rule_t* r,
                                   my_css_selector_t* sel) {
  my_css_selector_t* slot;
  if (sel->ancestor_count == 1u && sel->ancestors[0].id[0] == '\0') {
    size_t type_len = strlen(sel->ancestors[0].widget_type);
    size_t class_len = strlen(sel->ancestors[0].style_class);
    if (type_len + (class_len > 0u ? 1u + class_len : 0u) <
        sizeof(sel->ancestor_type)) {
      memcpy(sel->ancestor_type, sel->ancestors[0].widget_type, type_len);
      if (class_len > 0u) {
        sel->ancestor_type[type_len] = '.';
        memcpy(sel->ancestor_type + type_len + 1u,
               sel->ancestors[0].style_class, class_len);
      }
      sel->ancestor_type[type_len + (class_len > 0u ? 1u + class_len : 0u)] =
          '\0';
      sel->ancestor_direct = sel->ancestor_direct_path[0];
    }
  }
  slot = (my_css_selector_t*)my_mem_calloc(p->allocator, 1,
                                           sizeof(my_css_selector_t));
  if (slot == NULL) {
    css_fail(p, "oom");
    return false;
  }
  *slot = *sel;
  if (my_darray_push(r->selectors, slot) != MY_RET_OK) {
    my_mem_free(p->allocator, slot);
    css_fail(p, "oom");
    return false;
  }
  return true;
}

static bool css_parse_decl_block(css_p_t* p, my_css_rule_t* r,
                                 my_css_sheet_t* sheet, u32 depth,
                                 size_t at_depth);

/* R638: nested conditional groups evaluate their prelude with the same
 * machinery as the rules-level at-rules (defined further down). */
static bool css_skip_or_reject_atrule(css_p_t* p);
static bool css_skip_or_reject_atrule_with_capability(css_p_t* p,
                                                      uint32_t capability);
static bool css_read_atrule_prelude(css_p_t* p, char* out, size_t cap,
                                    size_t* length);
static bool css_supports_condition(const char* query, size_t length,
                                   const my_allocator_t* allocator,
                                   bool* matches);
static bool css_media_condition(css_p_t* p, const char* query, size_t length,
                                bool* matches, bool* conditional);

/* R629/R636/R641: the subset nests three levels (a nested rule's own block
 * takes further `&` rules down to depth 3; depth 4+ is rejected). */
#define MY_CSS_MAX_NEST_DEPTH 3u

/* R634: a nested rule's selector prelude is a comma group; each arm is
 * desugared against every parent selector (arms x variants cross product). */
#define MY_CSS_MAX_NEST_ARMS 8u

/* R629: parse one nested `&` rule at a declaration-block statement
 * boundary (the parser sits on the statement's first compound). The
 * selector path must hold exactly one parent marker; `&` alone/
 * `&:pseudo`/`&.class` merge onto the parent subject, while `& <path>`/
 * `& > <path>` place the parent at the outermost ancestor slot. R637: the
 * marker may sit at any compound position — at the subject slot the arm
 * compounds ahead of it become the parent's innermost ancestors; mid-chain
 * the whole parent selector lands in the marker's slot (its ancestors
 * travel with it). Parent selectors are already fully resolved (scope
 * spliced), so the desugar is a plain substitution — one variant per
 * parent selector, inheriting layer order and scope limits (root indices
 * shift past the substituted slots). R634: the prelude is a comma group —
 * each arm folds and substitutes independently into the same rule
 * (arm-major order). R636: the nested rule's own block takes one further
 * level of `&` rules — the parent's selectors are already fully desugared,
 * so the same substitution recurses unchanged. */
static bool css_nest_rule(css_p_t* p, my_css_rule_t* parent,
                          my_css_sheet_t* sheet, u32 depth, size_t at_depth) {
  my_css_selector_t arms[MY_CSS_MAX_NEST_ARMS][MY_CSS_MAX_ANCESTORS + 1u];
  bool arm_direct[MY_CSS_MAX_NEST_ARMS][MY_CSS_MAX_ANCESTORS + 1u];
  size_t arm_counts[MY_CSS_MAX_NEST_ARMS];
  size_t arm_marker[MY_CSS_MAX_NEST_ARMS];
  size_t arm_count = 0u;
  my_css_rule_t* nr;
  size_t ai, i, pi;
  if (depth >= MY_CSS_MAX_NEST_DEPTH) {
    css_fail(p, "CSS & nesting depth exceeded");
    return false;
  }
  /* parse the arm group: compound runs separated by top-level commas */
  for (;;) {
    my_css_selector_t(*compounds)[MY_CSS_MAX_ANCESTORS + 1u];
    bool* direct_between;
    size_t count = 0u;
    size_t marker_index = 0u;
    bool seen_marker = false;
    bool pending_direct = false;
    if (arm_count >= MY_CSS_MAX_NEST_ARMS) {
      css_fail(p, "invalid & nested selector");
      css_mark_capability(p, (uint32_t)MY_CSS_FEATURE_NESTING);
      return false;
    }
    compounds = &arms[arm_count];
    direct_between = arm_direct[arm_count];
    for (;;) {
      my_css_selector_t comp;
      bool separated;
      c_ws(p);
      memset(&comp, 0, sizeof(comp));
      comp.state = -1;
      if (!c_selector(p, &comp)) {
        css_mark_capability(p, (uint32_t)MY_CSS_FEATURE_NESTING);
        return false;
      }
      /* no :scope markers; no type/id-qualified marker (class/pseudo quals
       * merge; type can't follow '&' anyway). R637: the marker may sit at
       * any compound position; exactly one per arm. */
      if (comp.scope_ref ||
          (comp.nest_ref &&
           (comp.widget_type[0] != '\0' || comp.id[0] != '\0'))) {
        css_fail(p, "invalid & nested selector");
        return false;
      }
      if (comp.nest_ref) {
        if (seen_marker) {
          css_fail(p, "invalid & nested selector");
          return false;
        }
        seen_marker = true;
        marker_index = count;
      }
      if (count >= MY_CSS_MAX_ANCESTORS + 1u) {
        css_fail(p, "selector ancestor depth exceeded");
        css_mark_capability(p, (uint32_t)MY_CSS_FEATURE_NESTING);
        return false;
      }
      if (count > 0u) {
        direct_between[count] = pending_direct;
      }
      (*compounds)[count++] = comp;
      separated = c_ws(p);
      if (c_peek(p) == '>') {
        c_next(p);
        c_ws(p);
        pending_direct = true;
        continue;
      }
      if (c_peek(p) == '{' || c_peek(p) == ',') {
        break;
      }
      if (!separated) {
        css_fail(p, "invalid & nested selector");
        return false;
      }
      pending_direct = false; /* whitespace = descendant combinator */
    }
    if (!seen_marker) {
      css_fail(p, "invalid & nested selector");
      return false;
    }
    arm_marker[arm_count] = marker_index;
    arm_counts[arm_count] = count;
    arm_count++;
    if (c_peek(p) == ',') {
      c_next(p); /* next arm */
      continue;
    }
    break; /* '{' */
  }

  nr = css_rule_new(p->allocator, parent->layer_order);
  if (nr == NULL) {
    css_fail(p, "oom");
    return false;
  }
  for (ai = 0u; ai < arm_count; ++ai) {
    const my_css_selector_t* compounds = arms[ai];
    const bool* direct_between = arm_direct[ai];
    size_t count = arm_counts[ai];
    size_t marker = arm_marker[ai];
    my_css_selector_t nsel;
    /* subject = last compound (the marker itself when it sits there).
     * Ancestor compounds copy field-wise (no type requirement — the scope
     * splice convention); a pseudo state on an ancestor can't be expressed
     * → reject. R637: the marker may sit at any position — the whole parent
     * selector lands in its slot (parent ancestors travel with it, outward
     * of the parent subject but inward of the arm's outward compounds). */
    nsel = compounds[count - 1u];
    for (pi = 0u; pi < my_darray_size(parent->selectors); ++pi) {
      const my_css_selector_t* psel =
          (const my_css_selector_t*)my_darray_get(parent->selectors, pi);
      my_css_selector_t out;
      u32 pa;
      u32 j;
      if (psel == NULL) {
        continue;
      }
      pa = psel->ancestor_count;
      if (marker + 1u == count) {
        /* subject-slot marker (`.a &`, `.a &:hover`): merge the marker's
         * pseudo state and/or extra classes onto the parent subject; the
         * arm compounds ahead of the marker land OUTWARD of the parent's
         * own ancestors (`.x &` on `panel item` → `.x panel item`). A
         * state-qualified parent stays legal (it remains the subject). */
        size_t lead = count - 1u;
        if (lead + pa > MY_CSS_MAX_ANCESTORS) {
          css_fail(p, "selector ancestor depth exceeded");
          css_mark_capability(p, (uint32_t)MY_CSS_FEATURE_NESTING);
          css_rule_destroy(p->allocator, nr);
          return false;
        }
        for (i = 0u; i < lead; ++i) {
          if (compounds[lead - 1u - i].state != -1) {
            css_fail(p, "invalid & nested selector");
            css_rule_destroy(p->allocator, nr);
            return false;
          }
        }
        out = *psel;
        if (nsel.state >= 0) {
          out.state = nsel.state;
        }
        if (nsel.style_class[0] != '\0') {
          size_t have = strlen(out.style_class);
          size_t need = strlen(nsel.style_class);
          size_t sep = have > 0u ? 1u : 0u;
          if (have + sep + need >= sizeof(out.style_class)) {
            css_fail(p, "selector classes too long");
            css_rule_destroy(p->allocator, nr);
            return false;
          }
          if (sep != 0u) {
            out.style_class[have] = ' ';
          }
          memcpy(out.style_class + have + sep, nsel.style_class, need + 1u);
        }
        for (i = 0u; i < lead; ++i) {
          size_t source = lead - 1u - i;
          u32 slot = pa + (u32)i;
          memcpy(out.ancestors[slot].widget_type,
                 compounds[source].widget_type,
                 sizeof(out.ancestors[slot].widget_type));
          memcpy(out.ancestors[slot].id, compounds[source].id,
                 sizeof(out.ancestors[slot].id));
          memcpy(out.ancestors[slot].style_class,
                 compounds[source].style_class,
                 sizeof(out.ancestors[slot].style_class));
          /* the first (innermost) arm compound takes the edge parsed
           * against the marker; the rest keep their parsed edges. */
          out.ancestor_direct_path[slot] =
              i == 0u ? direct_between[lead] : direct_between[source + 1u];
        }
        out.ancestor_count = (u32)(lead + pa);
        /* the parent's ancestors never moved — scope limits carry over
         * unchanged. */
      } else {
        /* ancestor-slot marker: [inner arm compounds..., parent subject at
         * the marker slot, parent ancestors outward, outward arm
         * compounds...]. A state-qualified parent can't be expressed once
         * its subject becomes an ancestor; a state-qualified marker in an
         * ancestor slot can't be expressed either. */
        u32 m;
        u32 total;
        if (psel->state != -1 || compounds[marker].state != -1) {
          css_fail(p, "invalid & nested selector");
          css_rule_destroy(p->allocator, nr);
          return false;
        }
        m = (u32)(count - 2u - marker); /* marker slot (innermost-first) */
        total = m + 1u + pa + (u32)marker;
        if (total > MY_CSS_MAX_ANCESTORS) {
          css_fail(p, "selector ancestor depth exceeded");
          css_mark_capability(p, (uint32_t)MY_CSS_FEATURE_NESTING);
          css_rule_destroy(p->allocator, nr);
          return false;
        }
        memset(&out, 0, sizeof(out));
        out.state = nsel.state;
        snprintf(out.widget_type, sizeof(out.widget_type), "%s",
                 nsel.widget_type);
        snprintf(out.id, sizeof(out.id), "%s", nsel.id);
        snprintf(out.style_class, sizeof(out.style_class), "%s",
                 nsel.style_class);
        for (i = 0u; i < m; ++i) {
          size_t source = count - 2u - i;
          if (compounds[source].state != -1) {
            css_fail(p, "invalid & nested selector");
            css_rule_destroy(p->allocator, nr);
            return false;
          }
          memcpy(out.ancestors[i].widget_type, compounds[source].widget_type,
                 sizeof(out.ancestors[i].widget_type));
          memcpy(out.ancestors[i].id, compounds[source].id,
                 sizeof(out.ancestors[i].id));
          memcpy(out.ancestors[i].style_class, compounds[source].style_class,
                 sizeof(out.ancestors[i].style_class));
          out.ancestor_direct_path[i] = direct_between[source + 1u];
        }
        /* parent subject as the ancestor at the marker slot (the marker's
         * own class quals merge in), with the parsed edge flag kept. */
        snprintf(out.ancestors[m].widget_type,
                 sizeof(out.ancestors[m].widget_type), "%s",
                 psel->widget_type);
        snprintf(out.ancestors[m].id, sizeof(out.ancestors[m].id), "%s",
                 psel->id);
        if (compounds[marker].style_class[0] != '\0') {
          if (psel->style_class[0] != '\0') {
            int n = snprintf(out.ancestors[m].style_class,
                             sizeof(out.ancestors[m].style_class), "%s %s",
                             psel->style_class, compounds[marker].style_class);
            if (n < 0 || (size_t)n >= sizeof(out.ancestors[m].style_class)) {
              css_fail(p, "selector classes too long");
              css_rule_destroy(p->allocator, nr);
              return false;
            }
          } else {
            snprintf(out.ancestors[m].style_class,
                     sizeof(out.ancestors[m].style_class), "%s",
                     compounds[marker].style_class);
          }
        } else {
          snprintf(out.ancestors[m].style_class,
                   sizeof(out.ancestors[m].style_class), "%s",
                   psel->style_class);
        }
        out.ancestor_direct_path[m] = direct_between[marker + 1u];
        for (j = 0u; j < pa; ++j) {
          out.ancestors[m + 1u + j] = psel->ancestors[j];
          out.ancestor_direct_path[m + 1u + j] =
              psel->ancestor_direct_path[j];
        }
        /* arm compounds outward of the marker land beyond the parent's
         * chain; the first takes the edge parsed against the marker. */
        for (i = 0u; i < marker; ++i) {
          size_t source = marker - 1u - i;
          u32 slot = m + 1u + pa + (u32)i;
          if (compounds[source].state != -1) {
            css_fail(p, "invalid & nested selector");
            css_rule_destroy(p->allocator, nr);
            return false;
          }
          memcpy(out.ancestors[slot].widget_type,
                 compounds[source].widget_type,
                 sizeof(out.ancestors[slot].widget_type));
          memcpy(out.ancestors[slot].id, compounds[source].id,
                 sizeof(out.ancestors[slot].id));
          memcpy(out.ancestors[slot].style_class,
                 compounds[source].style_class,
                 sizeof(out.ancestors[slot].style_class));
          out.ancestor_direct_path[slot] =
              i == 0u ? direct_between[marker] : direct_between[source + 1u];
        }
        out.ancestor_count = total;
        /* the parent's scope limits carry over; root indices shift past the
         * substituted slots. */
        out.scope_limit_count = psel->scope_limit_count;
        for (j = 0u; j < psel->scope_limit_count; ++j) {
          out.scope_limits[j] = psel->scope_limits[j];
          out.scope_limit_root_index[j] =
              psel->scope_limit_root_index[j] == MY_CSS_SCOPE_ROOT_IMPLICIT
                  ? psel->scope_limit_root_index[j]
                  : psel->scope_limit_root_index[j] + m + 1u;
        }
      }
      if (!css_rule_push_selector(p, nr, &out)) {
        css_rule_destroy(p->allocator, nr);
        return false;
      }
    }
  }
  c_next(p); /* '{' */
  /* R629/R636: pend instead of pushing directly — css_parse_rules flushes
   * after the parent rule lands, preserving source order. The rule pends
   * BEFORE its block is parsed so that rules nested inside it (R636 second
   * level) land after it in flush order; once pended, the parse teardown
   * owns it on any later failure. */
  if (p->nest_pending == NULL) {
    p->nest_pending = my_darray_create(p->allocator, 0u);
    if (p->nest_pending == NULL) {
      css_rule_destroy(p->allocator, nr);
      css_fail(p, "oom");
      return false;
    }
  }
  if (my_darray_push(p->nest_pending, nr) != MY_RET_OK) {
    css_rule_destroy(p->allocator, nr);
    css_fail(p, "oom");
    return false;
  }
  if (!css_parse_decl_block(p, nr, sheet, depth + 1u, at_depth)) {
    return false;
  }
  return true;
}

/* R637: a block statement that does not start with '&' may still be a
 * nested rule (`.a & {}` — the marker sits mid-chain). Scan the statement:
 * a top-level `&` before the next `{`/`;`/`}` means nested rule. Quoted
 * spans are skipped so string values containing '&' stay declarations
 * (backslash escapes inside quotes are not interpreted — no subset value
 * needs them). */
static bool css_stmt_is_nested_rule(const css_p_t* p) {
  size_t pos = p->pos;
  int quote = 0;
  while (pos < p->len) {
    char c = p->s[pos];
    if (quote != 0) {
      if (c == quote) {
        quote = 0;
      }
    } else if (c == '"' || c == '\'') {
      quote = c;
    } else if (c == '&') {
      return true;
    } else if (c == '{' || c == ';' || c == '}') {
      return false;
    }
    pos++;
  }
  return false;
}

/* R638: a conditional group (@media/@supports) nested in a declaration
 * block. The prelude evaluates at parse time with the same machinery as
 * the rules-level at-rules — a matching group parses its statements
 * directly against the enclosing rule (declarations append in source
 * order, which for an identical selector IS the spec's split-rule
 * cascade; `&` statements desugar against the same parent; deeper
 * conditionals recurse), a non-matching group is skipped whole. R663:
 * kind 2 = @container (phase-1 unnamed size queries). */
#define CSS_NEST_COND_MEDIA 0
#define CSS_NEST_COND_SUPPORTS 1
#define CSS_NEST_COND_CONTAINER 2
/* forward: defined with the container at-rule machinery below. */
static bool css_container_features_valid(const char* query, size_t length);
static bool css_container_prelude_valid(const char* query, size_t length);
static void css_rule_stamp_container_condition(my_css_rule_t* r,
                                               const char* query,
                                               const char* name);
static bool css_parse_nested_conditional(css_p_t* p, my_css_rule_t* r,
                                         my_css_sheet_t* sheet, u32 depth,
                                         size_t at_depth, int kind) {
  bool matches = false;
  if (at_depth >= MY_CSS_MAX_AT_RULE_NESTING) {
    css_fail(p, kind == CSS_NEST_COND_MEDIA
                    ? "@media nesting depth exceeded"
                    : kind == CSS_NEST_COND_SUPPORTS
                          ? "@supports nesting depth exceeded"
                          : "@container nesting depth exceeded");
    return false;
  }
  c_ws(p);
  if (kind == CSS_NEST_COND_MEDIA) {
    char query[MY_CSS_MAX_MEDIA_QUERY_BYTES + 1u];
    size_t query_length = 0u;
    bool conditional = false;
    while (c_peek(p) >= 0 && c_peek(p) != '{') {
      if (query_length >= MY_CSS_MAX_MEDIA_QUERY_BYTES) {
        css_fail(p, "media query too long");
        return false;
      }
      query[query_length++] = (char)c_next(p);
    }
    query[query_length] = '\0';
    if (c_peek(p) != '{' ||
        !css_media_condition(p, query, query_length, &matches,
                             &conditional)) {
      return css_skip_or_reject_atrule(p);
    }
    if (conditional && p->media == NULL) {
      return css_skip_or_reject_atrule(p);
    }
  } else if (kind == CSS_NEST_COND_SUPPORTS) {
    char query[MY_CSS_MAX_SUPPORTS_QUERY_BYTES + 1u];
    size_t query_length = 0u;
    if (!css_read_atrule_prelude(p, query, sizeof(query), &query_length) ||
        !css_supports_condition(query, query_length, p->allocator,
                                &matches)) {
      return css_skip_or_reject_atrule_with_capability(
          p, (uint32_t)MY_CSS_FEATURE_SUPPORTS);
    }
  } else {
    /* R663: nested @container — CONTAINER capability. R679: without an
     * injected context the block defers to match time — it lands in a
     * sibling rule sharing the parent's selectors, stamped with the
     * condition (an enclosing rule-level @container's span stamp joins
     * as the second conjunct afterwards). */
    char query[MY_CSS_MAX_MEDIA_QUERY_BYTES + 1u];
    char name[MY_STYLE_KEY_LEN];
    size_t query_length = 0u;
    name[0] = '\0';
    c_ws(p);
    /* R679: an optional container name precedes the query (mirror of
     * the rule-level capture; `not`/`style(` stay query syntax). */
    if (c_peek(p) != '(') {
      size_t saved = p->pos;
      char word[MY_STYLE_KEY_LEN];
      if (c_ident(p, word, sizeof(word)) && !my_str_eq(word, "not") &&
          !(my_str_eq(word, "style") && c_peek(p) == '(') &&
          !c_ident_char((unsigned char)c_peek(p))) {
        snprintf(name, sizeof(name), "%s", word);
        c_ws(p);
      } else {
        p->pos = saved;
      }
    }
    if (!css_container_query_opens(p)) {
      return css_skip_or_reject_atrule_with_capability(
          p, (uint32_t)MY_CSS_FEATURE_CONTAINER);
    }
    while (c_peek(p) >= 0 && c_peek(p) != '{') {
      if (query_length >= MY_CSS_MAX_MEDIA_QUERY_BYTES) {
        css_fail(p, "media query too long");
        return false;
      }
      query[query_length++] = (char)c_next(p);
    }
    query[query_length] = '\0';
    while (query_length > 0u &&
           (query[query_length - 1u] == ' ' || query[query_length - 1u] == '\t' ||
            query[query_length - 1u] == '\r' || query[query_length - 1u] == '\n')) {
      query[--query_length] = '\0';
    }
    if (c_peek(p) != '{') {
      return css_skip_or_reject_atrule_with_capability(
          p, (uint32_t)MY_CSS_FEATURE_CONTAINER);
    }
    if (p->container == NULL) {
      /* R679 match-time deferral: the feature shape validates now; a
       * sibling rule carries the block, stamped with the condition. */
      my_css_rule_t* nr;
      size_t pend_before, si, sn, pi;
      if (!css_container_prelude_valid(query, query_length)) {
        return css_skip_or_reject_atrule_with_capability(
            p, (uint32_t)MY_CSS_FEATURE_CONTAINER);
      }
      pend_before =
          p->nest_pending != NULL ? my_darray_size(p->nest_pending) : 0u;
      nr = css_rule_new(p->allocator, r->layer_order);
      if (nr == NULL) {
        css_fail(p, "oom");
        return false;
      }
      sn = my_darray_size(r->selectors);
      for (si = 0u; si < sn; si++) {
        my_css_selector_t tmp =
            *(const my_css_selector_t*)my_darray_get(r->selectors, si);
        if (!css_rule_push_selector(p, nr, &tmp)) {
          css_rule_destroy(p->allocator, nr);
          return false;
        }
      }
      /* pend before the block parses (source order; the teardown owns
       * it on any later failure — the css_nest_rule discipline). */
      if (p->nest_pending == NULL) {
        p->nest_pending = my_darray_create(p->allocator, 0u);
        if (p->nest_pending == NULL) {
          css_rule_destroy(p->allocator, nr);
          css_fail(p, "oom");
          return false;
        }
      }
      if (my_darray_push(p->nest_pending, nr) != MY_RET_OK) {
        css_rule_destroy(p->allocator, nr);
        css_fail(p, "oom");
        return false;
      }
      c_next(p); /* '{' */
      if (!css_parse_decl_block(p, nr, sheet, depth, at_depth + 1u)) {
        return false;
      }
      /* stamp the sibling and everything pended during its block (&
       * desugars, deeper deferred @containers) — first-empty-slot, so
       * a deeper (inner) condition stamped by its own recursion keeps
       * pair1 and this one joins as pair2. */
      for (pi = pend_before; pi < my_darray_size(p->nest_pending); pi++) {
        css_rule_stamp_container_condition(
            (my_css_rule_t*)my_darray_get(p->nest_pending, pi), query, name);
      }
      return true;
    }
    /* R663 parse-time evaluation (host-injected context). Names need
     * the match layer — a named query still rejects in this mode
     * (rule-level contract). */
    if (name[0] != '\0' ||
        !css_container_query_matches(p, query, query_length, &matches)) {
      return css_skip_or_reject_atrule_with_capability(
          p, (uint32_t)MY_CSS_FEATURE_CONTAINER);
    }
  }
  if (!matches) {
    css_skip_atrule(p, false);
    return !c_failed(p);
  }
  c_next(p); /* '{' */
  return css_parse_decl_block(p, r, sheet, depth, at_depth + 1u);
}

/* R629: declaration block body (after '{', through the closing '}').
 * Statements whose prelude holds a top-level '&' are nested rules (R637:
 * the marker may sit mid-chain, not just at the statement start). R638:
 * `@media`/`@supports` statements are nested conditional groups. */
static bool css_parse_decl_block(css_p_t* p, my_css_rule_t* r,
                                 my_css_sheet_t* sheet, u32 depth,
                                 size_t at_depth) {
  for (;;) {
    char key[MY_STYLE_KEY_LEN];
    char mapped[MY_STYLE_KEY_LEN];
    my_css_decl_t* d;
    c_ws(p);
    if (c_failed(p)) {
      return false;
    }
    if (c_peek(p) == '&' || css_stmt_is_nested_rule(p)) {
      if (!css_nest_rule(p, r, sheet, depth, at_depth)) {
        return false;
      }
      continue;
    }
    if (c_peek(p) == '@') {
      char at_name[MY_STYLE_KEY_LEN];
      c_next(p);
      if (c_ident(p, at_name, sizeof(at_name))) {
        if (my_str_eq(at_name, "media") || my_str_eq(at_name, "supports") ||
            my_str_eq(at_name, "container")) {
          int kind = my_str_eq(at_name, "media")
                         ? CSS_NEST_COND_MEDIA
                         : my_str_eq(at_name, "supports")
                               ? CSS_NEST_COND_SUPPORTS
                               : CSS_NEST_COND_CONTAINER;
          if (!css_parse_nested_conditional(p, r, sheet, depth, at_depth,
                                            kind)) {
            return false;
          }
          continue;
        }
        /* R645: CSS Nesting admits only conditional group rules into a
         * declaration block; other nested @-rules reject truthfully. */
        css_fail(p, "unsupported nested @-rule");
        return false;
      }
      css_fail(p, "expected declaration key");
      return false;
    }
    if (c_peek(p) == '}') {
      c_next(p);
      return true;
    }
    if (!c_ident(p, key, sizeof(key))) {
      css_fail(p, "expected declaration key");
      return false;
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
        return true;
      }
      css_fail(p, "unterminated declaration");
      return false;
    }
    c_next(p);
    c_ws(p);
    d = (my_css_decl_t*)my_mem_calloc(p->allocator, 1, sizeof(my_css_decl_t));
    if (d == NULL) {
      css_fail(p, "oom");
      return false;
    }
    my_value_init(&d->value, p->allocator);
    {
      bool value_ok;
      if (key[0] == '-' && key[1] == '-') {
        /* R665: custom property — raw token-stream value (the capture
         * strips a trailing top-level `!important` itself, so the shared
         * '!' tail below never triggers for these). */
        value_ok = css_custom_value(p, &d->value, &d->important);
      } else if (css_value_mentions_var(p)) {
        /* R666: var() declarations are raw text until lookup-time
         * substitution. */
        value_ok = css_custom_value(p, &d->value, &d->important);
      } else if (my_str_eq(key, "container-type") ||
                 my_str_eq(key, "container-name")) {
        /* R669: container properties capture raw and validate the
         * keyword/ident-list shape (phase-2 slice 1). */
        value_ok = css_custom_value(p, &d->value, &d->important);
        if (value_ok &&
            !css_container_property_value_ok(key,
                                             my_value_get_str(&d->value))) {
          my_value_reset(&d->value);
          value_ok = false;
        }
      } else {
        value_ok = css_value(p, &d->value);
      }
      if (!value_ok) {
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
          return true;
        }
        css_fail(p, "unterminated declaration");
        return false;
      }
    }
    c_ws(p);
    /* R654: optional `!important` after the value — lowercase keyword with
     * optional whitespace after '!'. */
    if (c_peek(p) == '!') {
      char important_word[16];
      c_next(p);
      c_ws(p);
      if (!c_ident(p, important_word, sizeof(important_word)) ||
          !my_str_eq(important_word, "important")) {
        my_value_reset(&d->value);
        my_mem_free(p->allocator, d);
        css_fail(p, "expected 'important' after '!'");
        return false;
      }
      d->important = true;
    }
    css_key_map(key, mapped, sizeof(mapped));
    snprintf(d->key, sizeof(d->key), "%s", mapped);
    if (my_darray_push(r->decls, d) != MY_RET_OK) {
      my_value_reset(&d->value);
      my_mem_free(p->allocator, d);
      css_fail(p, "oom");
      return false;
    }
    c_ws(p);
    if (c_peek(p) == ';') {
      c_next(p);
      continue;
    }
    if (c_peek(p) == '}') {
      c_next(p);
      return true;
    }
    css_fail(p, "expected ';' or '}'");
    return false;
  }
}

/** @brief One rule: selectors { declarations }. */
static my_css_rule_t* css_rule(css_p_t* p, my_css_sheet_t* sheet,
                               size_t at_depth, uint32_t layer_id) {
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
    sel.ancestor_scope_ref_mask = 0u;
    sel.ancestor_nest_ref_mask = 0u;
    for (i = 0; i < compound_count - 1u; i++) {
      size_t source = compound_count - 2u - i;
      if (compounds[source].scope_ref) {
        /* R627: `:scope` ancestor marker — zeroed slot + mask bit; the
         * scope splice substitutes it with the innermost root. R639/R640:
         * a state or class qualifier can't be expressed on an ancestor →
         * reject. */
        if (compounds[source].state != -1 ||
            compounds[source].style_class[0] != '\0') {
          css_fail(p, ":scope must be unqualified and outermost");
          goto fail;
        }
        memset(&sel.ancestors[i], 0, sizeof(sel.ancestors[i]));
        sel.ancestor_scope_ref_mask |= (u32)1u << i;
        sel.ancestor_direct_path[i] = direct_between[source + 1u];
        continue;
      }
      if (compounds[source].nest_ref) {
        memset(&sel.ancestors[i], 0, sizeof(sel.ancestors[i]));
        sel.ancestor_nest_ref_mask |= (u32)1u << i;
        sel.ancestor_direct_path[i] = direct_between[source + 1u];
        continue;
      }
      if (!c_ancestor_copy(p, &sel.ancestors[i], &compounds[source])) {
        goto fail;
      }
      sel.ancestor_direct_path[i] = direct_between[source + 1u];
    }
    /* R627: `:scope` markers are valid only inside @scope, unqualified, and
     * only as the subject itself (:scope) or the outermost ancestor
     * (:scope > x / :scope x). */
    if (sel.scope_ref || sel.ancestor_scope_ref_mask != 0u) {
      u32 mask = sel.ancestor_scope_ref_mask;
      if (p->scope_count == 0u) {
        css_fail(p, ":scope outside @scope");
        goto fail;
      }
      if (sel.scope_ref && (sel.ancestor_count != 0u ||
                            sel.widget_type[0] != '\0' || sel.id[0] != '\0')) {
        /* R639/R640: state and class qualifiers are the allowed
         * qualifications — they merge into the substituted root subject. */
        css_fail(p, ":scope must be unqualified and outermost");
        goto fail;
      }
      if (mask != 0u &&
          ((mask & (mask - 1u)) != 0u ||
           mask != ((u32)1u << (sel.ancestor_count - 1u)))) {
        css_fail(p, ":scope must be unqualified and outermost");
        goto fail;
      }
    }
    /* R629: `&` markers only arise inside a rule's declaration block (the
     * nested-rule desugar resolves them there) — reaching a top-level rule
     * selector with one is misuse. */
    if (sel.nest_ref || sel.ancestor_nest_ref_mask != 0u) {
      css_fail(p, "& outside a rule");
      goto fail;
    }
    if (p->scope_count > 0u) {
      /* R622: enumerate the root-list cross-product (the innermost scope
       * varies fastest). Each variant appends every active scope's chosen
       * root path — the root subject with a descendant edge, then its own
       * path outward (R620) — plus that scope's limits bounded at the root
       * subject slot of THIS variant. */
      size_t variant_count = 1u;
      size_t scope_index;
      size_t vi;
      size_t limit_index;
      for (scope_index = 0u; scope_index < p->scope_count; ++scope_index) {
        const css_scope_frame_t* fr = &p->scope_frames[scope_index];
        if (fr->root_count != 0u) {
          variant_count *= fr->root_count;
        }
      }
      if (variant_count > MY_CSS_MAX_SCOPE_VARIANTS) {
        css_fail(p, "scope selector list expansion exceeded");
        goto fail;
      }
      /* R627: a `:scope` marker substitutes at the innermost ROOTED frame
       * (CSS: the innermost scope root). */
      bool need_scope_sub =
          (sel.scope_ref || sel.ancestor_scope_ref_mask != 0u);
      size_t sub_frame = (size_t)-1;
      if (need_scope_sub) {
        size_t si;
        for (si = 0u; si < p->scope_count; ++si) {
          if (p->scope_frames[p->scope_count - si - 1u].root_count != 0u) {
            sub_frame = si;
            break;
          }
        }
        if (sub_frame == (size_t)-1) {
          css_fail(p, ":scope requires an explicit scope root");
          goto fail;
        }
      }
      for (vi = 0u; vi < variant_count; ++vi) {
        my_css_selector_t variant = sel;
        size_t remainder = vi;
        u32 slot_pos = sel.ancestor_count;
        variant.scope_limit_count = 0u;
        for (scope_index = 0u; scope_index < p->scope_count; ++scope_index) {
          const css_scope_frame_t* fr =
              &p->scope_frames[p->scope_count - scope_index - 1u];
          size_t root_index = MY_CSS_SCOPE_ROOT_IMPLICIT;
          if (fr->root_count != 0u) {
            const css_scope_root_t* root =
                &fr->roots[remainder % fr->root_count];
            size_t ai;
            remainder /= fr->root_count;
            if (scope_index == sub_frame && variant.scope_ref) {
              /* R627 subject form (`:scope { ... }`): the rule subject
               * BECOMES the root subject; only the root's own path appends
               * (no extra slot). Limits keep the implicit boundary — the
               * queried widget IS the root, and the limit check tests it
               * directly. */
              memcpy(variant.widget_type, root->subject.widget_type,
                     sizeof(variant.widget_type));
              memcpy(variant.id, root->subject.id, sizeof(variant.id));
              memcpy(variant.style_class, root->subject.style_class,
                     sizeof(variant.style_class));
              /* R640: the `:scope` qualifier classes append to the root's
               * own classes (AND semantics). */
              if (sel.style_class[0] != '\0') {
                size_t have = strlen(variant.style_class);
                size_t need = strlen(sel.style_class);
                size_t sep = have > 0u ? 1u : 0u;
                if (have + sep + need >= sizeof(variant.style_class)) {
                  css_fail(p, "selector classes too long");
                  goto fail;
                }
                if (sep != 0u) {
                  variant.style_class[have] = ' ';
                }
                memcpy(variant.style_class + have + sep, sel.style_class,
                       need + 1u);
              }
              variant.scope_ref = false;
              root_index = MY_CSS_SCOPE_ROOT_IMPLICIT;
              if ((size_t)slot_pos + root->ancestor_count >
                  MY_CSS_MAX_ANCESTORS) {
                css_fail(p, "scope ancestor depth exceeded");
                goto fail;
              }
              for (ai = 0u; ai < root->ancestor_count; ++ai) {
                variant.ancestors[slot_pos] = root->ancestors[ai];
                variant.ancestor_direct_path[slot_pos] =
                    root->ancestor_direct_path[ai];
                slot_pos++;
              }
            } else if (scope_index == sub_frame) {
              /* R627 outermost-ancestor form (`:scope > x` / `:scope x`):
               * substitute the marker slot in place — the PARSED edge flag
               * onto the inner content stays — then the root's own path
               * follows outward. */
              u32 mark_k = 0u;
              while ((variant.ancestor_scope_ref_mask & ((u32)1u << mark_k)) ==
                     0u) {
                mark_k++;
              }
              variant.ancestors[mark_k] = root->subject;
              variant.ancestor_scope_ref_mask = 0u;
              root_index = mark_k;
              slot_pos = (u32)(mark_k + 1u);
              if ((size_t)slot_pos + root->ancestor_count >
                  MY_CSS_MAX_ANCESTORS) {
                css_fail(p, "scope ancestor depth exceeded");
                goto fail;
              }
              for (ai = 0u; ai < root->ancestor_count; ++ai) {
                variant.ancestors[slot_pos] = root->ancestors[ai];
                variant.ancestor_direct_path[slot_pos] =
                    root->ancestor_direct_path[ai];
                slot_pos++;
              }
            } else {
              if ((size_t)slot_pos + 1u + root->ancestor_count >
                  MY_CSS_MAX_ANCESTORS) {
                css_fail(p, "scope ancestor depth exceeded");
                goto fail;
              }
              root_index = slot_pos;
              variant.ancestors[slot_pos] = root->subject;
              variant.ancestor_direct_path[slot_pos] = false;
              slot_pos++;
              for (ai = 0u; ai < root->ancestor_count; ++ai) {
                variant.ancestors[slot_pos] = root->ancestors[ai];
                variant.ancestor_direct_path[slot_pos] =
                    root->ancestor_direct_path[ai];
                slot_pos++;
              }
            }
          }
          for (limit_index = 0u; limit_index < fr->scope_limit_count;
               ++limit_index) {
            if (variant.scope_limit_count >= MY_CSS_MAX_SCOPE_NESTING) {
              css_fail(p, "scope limit depth exceeded");
              goto fail;
            }
            variant.scope_limits[variant.scope_limit_count] =
                fr->scope_limits[limit_index];
            variant.scope_limit_root_index[variant.scope_limit_count] =
                (u32)root_index;
            variant.scope_limit_count++;
          }
        }
        variant.ancestor_count = slot_pos;
        if (!css_rule_push_selector(p, r, &variant)) {
          goto fail;
        }
      }
    } else {
      if (!css_rule_push_selector(p, r, &sel)) {
        goto fail;
      }
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
  /* declarations (+ R629 nested `&` rules) */
  if (!css_parse_decl_block(p, r, sheet, 0u, at_depth)) {
    css_rule_destroy(p->allocator, r);
    return NULL;
  }
  return r;
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

/* R649: @supports selector() — grammar-level probe: the argument must parse
 * as a non-empty chain of compound selectors (descendant and '>'
 * combinators) with full consumption. Context placement (`&` inside a rule,
 * `:scope` inside @scope) is not grammar, so those compounds parse as
 * supported. The probe runs with err=NULL — c_selector only raises the
 * local failed flag. */
static bool css_supports_selector_probe(const char* text, size_t length,
                                        const my_allocator_t* allocator,
                                        bool* matches) {
  css_p_t probe;
  size_t compounds = 0u;
  bool need_compound = true;
  memset(&probe, 0, sizeof(probe));
  probe.allocator = allocator;
  probe.s = text;
  probe.len = length;
  *matches = false;
  for (;;) {
    my_css_selector_t comp;
    bool separated;
    c_ws(&probe);
    if (c_peek(&probe) < 0) break;
    memset(&comp, 0, sizeof(comp));
    comp.state = -1;
    if (!c_selector(&probe, &comp)) return true;
    compounds++;
    need_compound = false;
    separated = c_ws(&probe);
    if (c_peek(&probe) == '>') {
      c_next(&probe);
      need_compound = true;
      continue;
    }
    if (!separated && c_peek(&probe) >= 0) return true;
  }
  *matches = compounds > 0u && !need_compound && !c_failed(&probe);
  return true;
}

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
  bool selector_fn = false;
  css_supports_expr_ws(expr);
  if (expr->position >= expr->length) return false;
  if (expr->text[expr->position] != '(') {
    /* R649: bare supports-selector-fn — `selector(...)` without a paren
     * wrapper is itself a supports-feature. */
    if (expr->length - expr->position >= 9u &&
        memcmp(expr->text + expr->position, "selector(", 9u) == 0) {
      selector_fn = true;
      expr->position += 9u;
    } else {
      return false;
    }
  } else {
    expr->position++;
  }
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
  if (selector_fn) {
    return css_supports_selector_probe(expr->text + start, end - start,
                                       expr->allocator, matches);
  }
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

/* R646: parse a media ratio value — `a/b` with positive integers, or a bare
 * integer meaning a/1. Components are capped at six digits so the u64
 * cross-multiplication in the evaluator stays trivially in range. */
static bool css_media_ratio(const char* text, size_t length, uint32_t* a,
                            uint32_t* b) {
  uint32_t parts[2] = {0u, 0u};
  size_t part = 0u;
  size_t digits = 0u;
  size_t i;
  for (i = 0u; i < length; ++i) {
    char ch = text[i];
    if (ch >= '0' && ch <= '9') {
      if (digits >= 6u) return false;
      parts[part] = parts[part] * 10u + (uint32_t)(ch - '0');
      digits++;
    } else if (ch == '/' && part == 0u && digits > 0u) {
      part = 1u;
      digits = 0u;
    } else {
      return false;
    }
  }
  if (digits == 0u || parts[0] == 0u) return false;
  if (part == 0u) parts[1] = 1u;
  if (parts[1] == 0u) return false;
  *a = parts[0];
  *b = parts[1];
  return true;
}

/* R647: consume a ratio token (digits with an optional `/digits` tail) from
 * the media cursor and validate it with css_media_ratio. */
static bool css_media_ratio_token(css_media_cursor_t* cursor, uint32_t* a,
                                  uint32_t* b) {
  size_t start;
  css_media_ws(cursor);
  start = cursor->position;
  while (cursor->position < cursor->length) {
    char ch = cursor->text[cursor->position];
    if ((ch >= '0' && ch <= '9') || ch == '/') {
      cursor->position++;
    } else {
      break;
    }
  }
  if (cursor->position == start) return false;
  return css_media_ratio(cursor->text + start, cursor->position - start, a,
                         b);
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

/* R647: u64 variant for the ratio cross-multiplication products. */
static bool css_media_compare_u64(uint64_t actual,
                                  css_media_relation_t relation,
                                  uint64_t expected) {
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
  uint32_t first_a = 0u;
  uint32_t first_b = 1u;
  uint32_t second_a = 0u;
  uint32_t second_b = 1u;
  css_media_relation_t first_relation;
  css_media_relation_t second_relation;
  bool first_is_number = false;
  bool ratio_domain = false;
  bool result = true;
  css_media_cursor_t probe;

  css_media_ws(cursor);
  *known = css_media_context_known(media);
  if (cursor->position >= cursor->length) return -1;
  if (cursor->text[cursor->position] >= '0' &&
      cursor->text[cursor->position] <= '9') {
    /* R647: a value-first range is px-domain (width/height) when the value
     * carries the px unit, ratio-domain (aspect-ratio) otherwise — a failed
     * px probe must not consume the digits. */
    probe = *cursor;
    if (css_media_number_px(&probe, &first_number)) {
      *cursor = probe;
    } else if (css_media_ratio_token(cursor, &first_a, &first_b)) {
      ratio_domain = true;
    } else {
      return -1;
    }
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
    if (my_str_eq(name, "aspect-ratio")) {
      /* R647: name-first ratio — `(aspect-ratio >= 16/9)`. */
      ratio_domain = true;
      if (!css_media_ratio_token(cursor, &first_a, &first_b)) return -1;
      if (media != NULL) {
        result = css_media_compare_u64(
            (uint64_t)media->base.viewport_width_px * (uint64_t)first_b,
            first_relation,
            (uint64_t)first_a * (uint64_t)media->base.viewport_height_px);
      }
    } else {
      if (!my_str_eq(name, "width") && !my_str_eq(name, "height")) return -1;
      if (!css_media_number_px(cursor, &first_number)) return -1;
      if (media != NULL) {
        uint32_t actual = my_str_eq(name, "width")
                              ? media->base.viewport_width_px
                              : media->base.viewport_height_px;
        result = css_media_compare(actual, first_relation, first_number);
      }
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
    if (ratio_domain) {
      /* R647: value-first ratio requires the aspect-ratio feature (a
       * non-empty unknown name is only tolerated without a media context,
       * mirroring the px-domain leniency). */
      if (!my_str_eq(name, "aspect-ratio") && media != NULL) return -1;
      if (name_length == 0u) return -1;
      if (media != NULL) {
        result = css_media_compare_u64(
            (uint64_t)first_a * (uint64_t)media->base.viewport_height_px,
            first_relation,
            (uint64_t)media->base.viewport_width_px * (uint64_t)first_b);
      }
    } else {
      /* R647: a recognized ratio-domain feature with a px value is a domain
       * error, not an unknown-name leniency case. */
      if (my_str_eq(name, "aspect-ratio") && media != NULL) return -1;
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
  }

  css_media_ws(cursor);
  if (cursor->position < cursor->length && cursor->text[cursor->position] != ')') {
    if (!first_is_number || !css_media_relation(cursor, &second_relation)) {
      return -1;
    }
    if (ratio_domain) {
      if (!css_media_ratio_token(cursor, &second_a, &second_b)) return -1;
      if (media != NULL) {
        result = result && css_media_compare_u64(
            (uint64_t)media->base.viewport_width_px * (uint64_t)second_b,
            second_relation,
            (uint64_t)second_a * (uint64_t)media->base.viewport_height_px);
      }
    } else {
      if (!css_media_number_px(cursor, &second_number)) return -1;
      if (media != NULL) {
        uint32_t actual = my_str_eq(name, "width")
                              ? media->base.viewport_width_px
                              : media->base.viewport_height_px;
        result = result &&
                 css_media_compare(actual, second_relation, second_number);
      }
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
  /* R646: aspect-ratio compares the viewport ratio against a/b by exact
   * u64 cross-multiplication (no float). */
  if (my_str_eq(name, "aspect-ratio") ||
      my_str_eq(name, "min-aspect-ratio") ||
      my_str_eq(name, "max-aspect-ratio")) {
    uint32_t a = 0u;
    uint32_t b = 0u;
    uint64_t lhs;
    uint64_t rhs;
    if (!css_media_ratio(value, value_length, &a, &b)) return false;
    lhs = (uint64_t)media->base.viewport_width_px * (uint64_t)b;
    rhs = (uint64_t)a * (uint64_t)media->base.viewport_height_px;
    if (my_str_eq(name, "aspect-ratio")) {
      *matches = lhs == rhs;
    } else if (my_str_eq(name, "min-aspect-ratio")) {
      *matches = lhs >= rhs;
    } else {
      *matches = lhs <= rhs;
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

/* R650: MQ4 boolean logic — media-in-parens may hold a nested condition;
 * one chain level is uniformly and or uniformly or; an item may carry a
 * leading `not`. */
#define MY_CSS_MAX_MEDIA_COND_DEPTH 4u

static bool css_media_cond(css_media_cursor_t* cursor,
                           const my_css_media_context_ex_t* media,
                           size_t depth, bool* matches, bool* known);

static bool css_media_item(css_media_cursor_t* cursor,
                           const my_css_media_context_ex_t* media,
                           size_t depth, bool allow_not, bool* matches,
                           bool* known) {
  bool negated = false;
  *known = true;
  css_media_ws(cursor);
  if (allow_not && css_media_word(cursor, "not")) negated = true;
  css_media_ws(cursor);
  if (cursor->position >= cursor->length ||
      cursor->text[cursor->position] != '(') {
    return false;
  }
  {
    css_media_cursor_t probe = *cursor;
    probe.position++;
    css_media_ws(&probe);
    if (probe.position < probe.length &&
        (probe.text[probe.position] == '(' ||
         css_media_word(&probe, "not"))) {
      /* nested condition in parens */
      if (depth >= MY_CSS_MAX_MEDIA_COND_DEPTH) return false;
      cursor->position++;
      if (!css_media_cond(cursor, media, depth + 1u, matches, known)) {
        return false;
      }
      css_media_ws(cursor);
      if (cursor->position >= cursor->length ||
          cursor->text[cursor->position] != ')') {
        return false;
      }
      cursor->position++;
      *known = true;
      if (negated) *matches = !*matches;
      return true;
    }
  }
  if (!css_media_feature(cursor, media, matches, known)) return false;
  if (negated) {
    if (*known) *matches = !*matches;
    else *matches = false;
  }
  return true;
}

static bool css_media_cond(css_media_cursor_t* cursor,
                           const my_css_media_context_ex_t* media,
                           size_t depth, bool* matches, bool* known) {
  bool item_matches = false;
  bool item_known = true;
  bool result;
  bool seen_separator = false;
  bool or_chain = false;
  (void)known;
  if (!css_media_item(cursor, media, depth, true, &item_matches,
                      &item_known)) {
    return false;
  }
  result = item_matches;
  for (;;) {
    css_media_cursor_t probe;
    bool next_matches = false;
    bool next_known = true;
    bool is_or;
    css_media_ws(cursor);
    if (cursor->position >= cursor->length) break;
    if (cursor->text[cursor->position] == ')' ||
        cursor->text[cursor->position] == ',') break;
    probe = *cursor;
    if (css_media_word(&probe, "and")) {
      is_or = false;
    } else {
      probe = *cursor;
      if (!css_media_word(&probe, "or")) return false;
      is_or = true;
    }
    if (!seen_separator) {
      seen_separator = true;
      or_chain = is_or;
    } else if (or_chain != is_or) {
      return false;
    }
    *cursor = probe;
    if (!css_media_item(cursor, media, depth, true, &next_matches,
                        &next_known)) {
      return false;
    }
    result = or_chain ? (result || next_matches) : (result && next_matches);
  }
  *matches = result;
  return true;
}

static bool css_media_query(css_media_cursor_t* cursor,
                            const my_css_media_context_ex_t* media,
                            bool* matches, bool* conditional) {
  bool query_matches = true;
  bool has_type = false;
  bool negated = false;
  bool only = false;
  css_media_ws(cursor);
  if (css_media_word(cursor, "not")) {
    negated = true;
    css_media_ws(cursor);
  }
  /* R648: legacy `only` modifier — a no-op synonym for the bare media type.
   * It cannot combine with `not` and requires a following type. */
  if (!negated && css_media_word(cursor, "only")) {
    only = true;
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
  }
  if (only && !has_type) return false;
  css_media_ws(cursor);
  if (has_type) {
    if (cursor->position < cursor->length &&
        cursor->text[cursor->position] != ',') {
      bool cond_matches = false;
      bool cond_known = true;
      /* a type query chains with `and` only. */
      if (!css_media_word(cursor, "and")) return false;
      if (!css_media_cond(cursor, media, 0u, &cond_matches, &cond_known)) {
        return false;
      }
      *conditional = true;
      query_matches = query_matches && cond_matches;
    }
  } else if (negated) {
    /* query-level not: one item, no continuation (existing contract). */
    css_media_cursor_t probe = *cursor;
    bool item_known = true;
    if (css_media_word(&probe, "not")) return false;
    if (!css_media_item(cursor, media, 0u, false, &query_matches,
                        &item_known)) {
      return false;
    }
    if (item_known) query_matches = !query_matches;
    else query_matches = false;
    *conditional = true;
    css_media_ws(cursor);
    if (cursor->position < cursor->length &&
        cursor->text[cursor->position] != ',') {
      return false;
    }
  } else if (cursor->position < cursor->length &&
             cursor->text[cursor->position] != ',') {
    bool cond_known = true;
    if (!css_media_cond(cursor, media, 0u, &query_matches, &cond_known)) {
      return false;
    }
    *conditional = true;
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

/* R673: style() container queries (bounded slice) — the query is exactly
 * one `style(--prop: value)` condition: no bare form, no and/or/not
 * mixing, custom properties only, and `var(` in the queried value
 * rejects (the query side is never substituted). container-type does
 * not gate style queries; evaluation compares the custom property value
 * on the nearest qualifying ancestor as whitespace-normalized raw text. */
static bool css_container_query_is_style(const char* query, size_t length) {
  size_t i = 0u;
  while (i < length &&
         (query[i] == ' ' || query[i] == '\t' || query[i] == '\r' ||
          query[i] == '\n')) {
    i++;
  }
  return length - i >= 6u && memcmp(query + i, "style(", 6u) == 0;
}

/* R681: split an and-only condition list at top-level `and` word
 * boundaries (paren- and quote-aware). Each slice is trimmed. Returns
 * the condition count: 1 when no top-level `and` separates conditions,
 * 0 when a mid-list `or`/`not` connective, an empty slice, unbalanced
 * parentheses or the cap puts the composition out of scope. A leading
 * `not` stays part of its slice (the media machinery negates it). */
#define MY_CSS_MAX_CONTAINER_CONDS 4u

static bool css_container_ws(char c) {
  return c == ' ' || c == '\t' || c == '\r' || c == '\n';
}

static size_t css_container_split_and(const char* query, size_t length,
                                      const char* conds[],
                                      size_t cond_lens[],
                                      size_t max_conds) {
  size_t count = 0u;
  size_t start = 0u;
  size_t i = 0u;
  char quote = '\0';
  size_t depth = 0u;
  while (i < length) {
    char c = query[i];
    if (quote != '\0') {
      if (c == '\\' && i + 1u < length) {
        i++;
      } else if (c == quote) {
        quote = '\0';
      }
      i++;
      continue;
    }
    if (c == '\'' || c == '"') {
      quote = c;
      i++;
      continue;
    }
    if (c == '(') {
      depth++;
      i++;
      continue;
    }
    if (c == ')') {
      if (depth == 0u) {
        return 0u;
      }
      depth--;
      i++;
      continue;
    }
    if (depth == 0u && css_container_ws(c) && i + 3u < length &&
        (memcmp(query + i + 1u, "and", 3u) == 0 ||
         (i + 2u < length && memcmp(query + i + 1u, "or", 2u) == 0) ||
         memcmp(query + i + 1u, "not", 3u) == 0)) {
      /* a top-level connective word: which one? */
      const char* word = query + i + 1u;
      size_t word_len = memcmp(word, "and", 3u) == 0 ||
                                memcmp(word, "not", 3u) == 0
                            ? 3u
                            : 2u;
      size_t after = i + 1u + word_len;
      if (after >= length || css_container_ws(query[after])) {
        size_t end;
        if (word_len != 3u || memcmp(word, "and", 3u) != 0) {
          return 0u; /* mid-list or/not: out of scope */
        }
        end = i;
        if (count >= max_conds) {
          return 0u;
        }
        while (end > start && css_container_ws(query[end - 1u])) {
          end--;
        }
        if (end == start) {
          return 0u;
        }
        conds[count] = query + start;
        cond_lens[count] = end - start;
        count++;
        i = after;
        while (i < length && css_container_ws(query[i])) {
          i++;
        }
        start = i;
        continue;
      }
    }
    i++;
  }
  if (quote != '\0' || depth != 0u) {
    return 0u;
  }
  if (count >= max_conds) {
    return 0u;
  }
  while (length > start && css_container_ws(query[length - 1u])) {
    length--;
  }
  if (length == start) {
    return 0u; /* empty trailing slice (dangling `and`) */
  }
  conds[count] = query + start;
  cond_lens[count] = length - start;
  return count + 1u;
}

static bool css_container_style_query_parse(const char* query, size_t length,
                                            char* prop, size_t prop_cap,
                                            const char** value,
                                            size_t* value_length) {
  size_t i = 0u, start, end, pl = 0u, depth = 1u;
  char quote = '\0';
  while (i < length &&
         (query[i] == ' ' || query[i] == '\t' || query[i] == '\r' ||
          query[i] == '\n')) {
    i++;
  }
  if (length - i < 6u || memcmp(query + i, "style(", 6u) != 0) {
    return false;
  }
  i += 6u;
  while (i < length &&
         (query[i] == ' ' || query[i] == '\t' || query[i] == '\r' ||
          query[i] == '\n')) {
    i++;
  }
  if (i + 2u >= length || query[i] != '-' || query[i + 1u] != '-' ||
      !c_ident_char((unsigned char)query[i + 2u])) {
    return false;
  }
  prop[pl++] = query[i++];
  prop[pl++] = query[i++];
  while (i < length && c_ident_char((unsigned char)query[i])) {
    if (pl + 1u >= prop_cap) {
      return false;
    }
    prop[pl++] = query[i++];
  }
  prop[pl] = '\0';
  while (i < length &&
         (query[i] == ' ' || query[i] == '\t' || query[i] == '\r' ||
          query[i] == '\n')) {
    i++;
  }
  /* R682: the bare form `style(--prop)` — the existence check. The
   * value out-params come back NULL/0. */
  if (i < length && query[i] == ')' && depth == 1u) {
    i++;
    while (i < length &&
           (query[i] == ' ' || query[i] == '\t' || query[i] == '\r' ||
            query[i] == '\n')) {
      i++;
    }
    if (i != length) {
      return false; /* trailing tokens after the bare form */
    }
    *value = NULL;
    *value_length = 0u;
    return true;
  }
  if (i >= length || query[i] != ':') {
    return false;
  }
  i++;
  while (i < length &&
         (query[i] == ' ' || query[i] == '\t' || query[i] == '\r' ||
          query[i] == '\n')) {
    i++;
  }
  start = i;
  while (i < length && depth > 0u) {
    char ch = query[i];
    if (quote != '\0') {
      if (ch == '\\' && i + 1u < length) {
        i++;
      } else if (ch == quote) {
        quote = '\0';
      }
    } else if (ch == '\'' || ch == '"') {
      quote = ch;
    } else if (ch == '(') {
      depth++;
    } else if (ch == ')') {
      depth--;
      if (depth == 0u) {
        break;
      }
    } else if (ch == 'v' && i + 4u <= length &&
               memcmp(query + i, "var(", 4u) == 0) {
      return false;
    }
    i++;
  }
  if (depth != 0u) {
    return false; /* unbalanced */
  }
  end = i;
  i++;
  while (i < length &&
         (query[i] == ' ' || query[i] == '\t' || query[i] == '\r' ||
          query[i] == '\n')) {
    i++;
  }
  if (i != length) {
    return false; /* trailing tokens: and/or/not mixing is out of scope */
  }
  while (end > start &&
         (query[end - 1u] == ' ' || query[end - 1u] == '\t' ||
          query[end - 1u] == '\r' || query[end - 1u] == '\n')) {
    end--;
  }
  if (end == start) {
    return false; /* the bare form style(--prop) is out of scope */
  }
  *value = query + start;
  *value_length = end - start;
  return true;
}

/* whitespace-normalized raw-text equality: both sides are trimmed and
 * internal whitespace runs collapse to a single space; otherwise the
 * comparison is byte exact. */
static int css_container_style_norm_next(const char* s, size_t length,
                                         size_t* pos) {
  size_t i = *pos;
  int c;
  if (i >= length) {
    return -1;
  }
  if (s[i] == ' ' || s[i] == '\t' || s[i] == '\r' || s[i] == '\n') {
    while (i < length &&
           (s[i] == ' ' || s[i] == '\t' || s[i] == '\r' || s[i] == '\n')) {
      i++;
    }
    c = ' ';
  } else {
    c = (unsigned char)s[i++];
  }
  *pos = i;
  return c;
}

static bool css_container_style_value_eq(const char* a, size_t a_length,
                                         const char* b, size_t b_length) {
  size_t i = 0u, j = 0u;
  while (a_length > 0u &&
          (*a == ' ' || *a == '\t' || *a == '\r' || *a == '\n')) {
    a++;
    a_length--;
  }
  while (a_length > 0u &&
         (a[a_length - 1u] == ' ' || a[a_length - 1u] == '\t' ||
          a[a_length - 1u] == '\r' || a[a_length - 1u] == '\n')) {
    a_length--;
  }
  while (b_length > 0u &&
         (*b == ' ' || *b == '\t' || *b == '\r' || *b == '\n')) {
    b++;
    b_length--;
  }
  while (b_length > 0u &&
         (b[b_length - 1u] == ' ' || b[b_length - 1u] == '\t' ||
          b[b_length - 1u] == '\r' || b[b_length - 1u] == '\n')) {
    b_length--;
  }
  for (;;) {
    int ca = css_container_style_norm_next(a, a_length, &i);
    int cb = css_container_style_norm_next(b, b_length, &j);
    if (ca != cb) {
      return false;
    }
    if (ca < 0) {
      return true;
    }
  }
}

/* R677: computed-value equality for a style() query against a
 * REGISTERED property. Both sides must parse as one full value of the
 * registered primitive's type and then compare typed: <color> bits,
 * numeric INT32/DOUBLE cross-type equality, <string> bytes with the
 * quoted form required on both sides. A side that fails to parse, or a
 * type mismatch against the primitive, never equals. Syntaxes without
 * a probeable computed form (<percentage>, `*`, unknown strings) keep
 * the whitespace-normalized raw-text comparison. */
static size_t css_container_style_first_nonspace(const char* s,
                                                 size_t length) {
  size_t i = 0u;
  while (i < length && (s[i] == ' ' || s[i] == '\t' || s[i] == '\r' ||
                        s[i] == '\n')) {
    i++;
  }
  return i;
}

static bool css_container_style_typed_eq(const char* syntax, const char* a,
                                         size_t a_length, const char* b,
                                         size_t b_length) {
  css_p_t pa, pb;
  my_value_t va, vb;
  bool ok = false;
  if (syntax == NULL ||
      (!my_str_eq(syntax, "<color>") && !my_str_eq(syntax, "<length>") &&
       !my_str_eq(syntax, "<number>") && !my_str_eq(syntax, "<integer>") &&
       !my_str_eq(syntax, "<string>"))) {
    return css_container_style_value_eq(a, a_length, b, b_length);
  }
  my_value_init(&va, NULL);
  my_value_init(&vb, NULL);
  memset(&pa, 0, sizeof(pa));
  pa.s = a;
  pa.len = a_length;
  pa.line = 1;
  pa.col = 1;
  memset(&pb, 0, sizeof(pb));
  pb.s = b;
  pb.len = b_length;
  pb.line = 1;
  pb.col = 1;
  c_ws(&pa);
  c_ws(&pb);
  if (css_value(&pa, &va) && css_value(&pb, &vb)) {
    c_ws(&pa);
    c_ws(&pb);
    if (c_peek(&pa) < 0 && c_peek(&pb) < 0) {
      if (my_str_eq(syntax, "<color>")) {
        ok = my_value_type(&va) == MY_VALUE_UINT32 &&
             my_value_type(&vb) == MY_VALUE_UINT32 &&
             my_value_get_uint32(&va) == my_value_get_uint32(&vb);
      } else if (my_str_eq(syntax, "<integer>")) {
        ok = my_value_type(&va) == MY_VALUE_INT32 &&
             my_value_type(&vb) == MY_VALUE_INT32 &&
             my_value_get_int32(&va) == my_value_get_int32(&vb);
      } else if (my_str_eq(syntax, "<string>")) {
        size_t fa = css_container_style_first_nonspace(a, a_length);
        size_t fb = css_container_style_first_nonspace(b, b_length);
        const char* sa;
        const char* sb;
        ok = my_value_type(&va) == MY_VALUE_STR &&
             my_value_type(&vb) == MY_VALUE_STR &&
             (sa = my_value_get_str(&va)) != NULL &&
             (sb = my_value_get_str(&vb)) != NULL && my_str_eq(sa, sb) &&
             fa < a_length && fb < b_length &&
             (a[fa] == '\'' || a[fa] == '"') &&
             (b[fb] == '\'' || b[fb] == '"');
      } else { /* <length>/<number>: numeric cross-type equality */
        double da = 0.0, db = 0.0;
        bool na = false, nb = false;
        if (my_value_type(&va) == MY_VALUE_INT32) {
          da = (double)my_value_get_int32(&va);
          na = true;
        } else if (my_value_type(&va) == MY_VALUE_DOUBLE) {
          da = my_value_get_double(&va);
          na = true;
        }
        if (my_value_type(&vb) == MY_VALUE_INT32) {
          db = (double)my_value_get_int32(&vb);
          nb = true;
        } else if (my_value_type(&vb) == MY_VALUE_DOUBLE) {
          db = my_value_get_double(&vb);
          nb = true;
        }
        ok = na && nb && da == db;
      }
    }
  }
  my_value_reset(&va);
  my_value_reset(&vb);
  return ok;
}

/* R663: container query phase-1 validation — every feature name in the
 * query must be a size feature (the media machinery evaluates them against
 * a synthetic viewport built from the container context); media types are
 * rejected up front. */
static bool css_container_feature_name_ok(const char* name) {
  return my_str_eq(name, "width") || my_str_eq(name, "height") ||
         my_str_eq(name, "min-width") || my_str_eq(name, "max-width") ||
         my_str_eq(name, "min-height") || my_str_eq(name, "max-height") ||
         my_str_eq(name, "aspect-ratio") || my_str_eq(name, "orientation");
}

static bool css_container_features_valid(const char* query, size_t length) {
  size_t i = 0u;
  char quote = '\0';
  /* a leading media type (all/screen/only) belongs to @media. */
  while (i < length &&
         (query[i] == ' ' || query[i] == '\t' || query[i] == '\r' ||
          query[i] == '\n')) {
    i++;
  }
  if (i < length && c_ident_char((unsigned char)query[i])) {
    char word[8];
    size_t wl = 0u;
    while (i < length && c_ident_char((unsigned char)query[i]) &&
           wl + 1u < sizeof(word)) {
      word[wl++] = query[i++];
    }
    word[wl] = '\0';
    if (my_str_eq(word, "all") || my_str_eq(word, "screen") ||
        my_str_eq(word, "only")) {
      return false;
    }
  }
  for (i = 0u; i < length; ++i) {
    if (quote != '\0') {
      if (query[i] == '\\' && i + 1u < length) {
        ++i;
      } else if (query[i] == quote) {
        quote = '\0';
      }
      continue;
    }
    if (query[i] == '\'' || query[i] == '"') {
      quote = query[i];
      continue;
    }
    if (query[i] == '(') {
      size_t j = i + 1u;
      char name[24];
      size_t nl = 0u;
      while (j < length &&
             (query[j] == ' ' || query[j] == '\t' || query[j] == '\r' ||
              query[j] == '\n')) {
        j++;
      }
      while (j < length && c_ident_char((unsigned char)query[j])) {
        if (nl + 1u >= sizeof(name)) return false;
        name[nl++] = query[j++];
      }
      name[nl] = '\0';
      if (nl == 0u || my_str_eq(name, "not") || my_str_eq(name, "and") ||
          my_str_eq(name, "or")) {
        continue;
      }
      if (!css_container_feature_name_ok(name)) return false;
    }
  }
  return true;
}

/* R681: validate a whole @container prelude — an and-only condition
 * list validates per condition (each slice is a style() form or a size
 * feature list). An unsplittable whole string (mid-list or/not)
 * validates through the legacy paths: a pure-size composition keeps
 * its media-machinery evaluation, a style() opener still rejects on
 * its single-condition form. */
static bool css_container_prelude_valid(const char* query, size_t length) {
  const char* conds[MY_CSS_MAX_CONTAINER_CONDS];
  size_t cond_lens[MY_CSS_MAX_CONTAINER_CONDS];
  size_t n = css_container_split_and(query, length, conds, cond_lens,
                                     MY_CSS_MAX_CONTAINER_CONDS);
  size_t ci;
  if (n == 0u) {
    if (css_container_query_is_style(query, length)) {
      char prop[MY_STYLE_KEY_LEN];
      const char* value;
      size_t value_length;
      return css_container_style_query_parse(query, length, prop,
                                             sizeof(prop), &value,
                                             &value_length);
    }
    return css_container_features_valid(query, length);
  }
  for (ci = 0u; ci < n; ci++) {
    if (css_container_query_is_style(conds[ci], cond_lens[ci])) {
      char prop[MY_STYLE_KEY_LEN];
      const char* value;
      size_t value_length;
      if (!css_container_style_query_parse(conds[ci], cond_lens[ci], prop,
                                           sizeof(prop), &value,
                                           &value_length)) {
        return false;
      }
    } else if (!css_container_features_valid(conds[ci], cond_lens[ci])) {
      return false;
    }
  }
  return true;
}

/* R663: does the container query open here? Phase 1 is unnamed only, but
 * `not` is query syntax (negation), not a container name — any other
 * leading ident is a name and rejected truthfully. */
static bool css_container_query_opens(css_p_t* p) {
  size_t saved = p->pos;
  char word[8];
  c_ws(p);
  if (c_peek(p) == '(') return true;
  /* R673: `style(` also opens a query (a different condition kind). */
  if (c_ident(p, word, sizeof(word)) &&
      (my_str_eq(word, "not") ||
       (my_str_eq(word, "style") && c_peek(p) == '(')) &&
      !c_ident_char((unsigned char)c_peek(p))) {
    p->pos = saved;
    return true;
  }
  p->pos = saved;
  return false;
}

/* R670: evaluate a size query against an explicit container size via the
 * media machinery with a synthetic viewport. Returns false only for a
 * malformed query; *matches carries the verdict. */
static bool css_container_eval_size_query(const char* query,
                                          size_t query_length, uint32_t width,
                                          uint32_t height, bool* matches) {
  css_p_t probe;
  my_css_media_context_ex_t synthetic;
  bool conditional = false;
  memset(&probe, 0, sizeof(probe));
  memset(&synthetic, 0, sizeof(synthetic));
  synthetic.base.viewport_width_px = width;
  synthetic.base.viewport_height_px = height;
  synthetic.base.screen = true;
  probe.s = query;
  probe.len = query_length;
  probe.line = 1;
  probe.col = 1;
  probe.media = &synthetic;
  return css_media_condition(&probe, query, query_length, matches,
                             &conditional);
}

/* R663: evaluate an @container query against the injected container size —
 * the media machinery with a synthetic viewport (phase 1 is unnamed size
 * queries only; per-element container resolution is R670). */
static bool css_container_query_matches(css_p_t* p, const char* query,
                                        size_t query_length, bool* matches) {
  /* R673: style() queries need the match-time element tree — like named
   * queries they reject in the host-injected parse-time mode. */
  if (p->container == NULL ||
      css_container_query_is_style(query, query_length) ||
      !css_container_features_valid(query, query_length)) {
    return false;
  }
  return css_container_eval_size_query(query, query_length,
                                       p->container->width_px,
                                       p->container->height_px, matches);
}

/* R671: @property — register a custom property (top level only; the
 * descriptors validate at block end: missing syntax/inherits drops the
 * rule leniently, unknown descriptors are skipped). */
static bool css_parse_property_atrule(css_p_t* p, my_css_sheet_t* sheet,
                                      bool nested) {
  char name[MY_STYLE_KEY_LEN];
  char syntax[64];
  char initial[MY_THEME_MAX_PROPERTY_VALUE_BYTES + 1u];
  bool has_syntax = false;
  bool has_inherits = false;
  bool inherits = false;
  bool has_initial = false;
  size_t i, n;

  if (nested) {
    /* bounded: registration is top-level only (the @import position
     * discipline). */
    return css_skip_or_reject_atrule(p);
  }
  c_ws(p);
  if (!c_ident(p, name, sizeof(name)) || name[0] != '-' || name[1] != '-') {
    return css_skip_or_reject_atrule(p);
  }
  c_ws(p);
  if (c_peek(p) != '{') {
    return css_skip_or_reject_atrule(p);
  }
  c_next(p);
  syntax[0] = '\0';
  initial[0] = '\0';
  for (;;) {
    char key[MY_STYLE_KEY_LEN];
    c_ws(p);
    if (c_peek(p) == '}') {
      c_next(p);
      break;
    }
    if (c_peek(p) < 0) {
      css_fail(p, "unterminated @property block");
      return false;
    }
    if (!c_ident(p, key, sizeof(key))) {
      /* lenient: skip to ';' or '}' */
      while (c_peek(p) >= 0 && c_peek(p) != ';' && c_peek(p) != '}') {
        c_next(p);
      }
      if (c_peek(p) == ';') {
        c_next(p);
      }
      continue;
    }
    c_ws(p);
    if (c_peek(p) != ':') {
      while (c_peek(p) >= 0 && c_peek(p) != ';' && c_peek(p) != '}') {
        c_next(p);
      }
      if (c_peek(p) == ';') {
        c_next(p);
      }
      continue;
    }
    c_next(p);
    c_ws(p);
    if (my_str_eq(key, "syntax")) {
      my_value_t v;
      my_value_init(&v, p->allocator);
      if (css_value(p, &v) && my_value_type(&v) == MY_VALUE_STR &&
          strlen(my_value_get_str(&v)) < sizeof(syntax)) {
        snprintf(syntax, sizeof(syntax), "%s", my_value_get_str(&v));
        has_syntax = true;
      }
      my_value_reset(&v);
    } else if (my_str_eq(key, "inherits")) {
      char word[8];
      if (c_ident(p, word, sizeof(word)) &&
          (my_str_eq(word, "true") || my_str_eq(word, "false"))) {
        inherits = my_str_eq(word, "true");
        has_inherits = true;
      }
    } else if (my_str_eq(key, "initial-value")) {
      my_value_t v;
      bool important = false;
      my_value_init(&v, p->allocator);
      if (css_custom_value(p, &v, &important) && !important &&
          strlen(my_value_get_str(&v)) <=
              MY_THEME_MAX_PROPERTY_VALUE_BYTES) {
        snprintf(initial, sizeof(initial), "%s", my_value_get_str(&v));
        has_initial = true;
      } else {
        has_initial = false; /* !important / oversized: descriptor invalid */
      }
      my_value_reset(&v);
    } else {
      /* unknown descriptor: skip its value raw */
      my_value_t v;
      bool important = false;
      my_value_init(&v, p->allocator);
      css_custom_value(p, &v, &important);
      my_value_reset(&v);
    }
    c_ws(p);
    if (c_peek(p) == ';') {
      c_next(p);
      continue;
    }
    if (c_peek(p) == '}') {
      continue; /* the loop head consumes it */
    }
    if (c_peek(p) < 0) {
      css_fail(p, "unterminated @property block");
      return false;
    }
  }
  if (!has_syntax || !has_inherits) {
    MY_LOGW("my_css: dropping @property %s (syntax/inherits required)",
            name);
    return true;
  }
  /* R672: an invalid initial invalidates the rule — initials that
   * mention var() defer the check to computed-value time. */
  if (has_initial && strstr(initial, "var(") == NULL &&
      !css_property_syntax_check(syntax, initial)) {
    MY_LOGW("my_css: dropping @property %s (initial fails syntax)", name);
    return true;
  }
  /* last registration wins. */
  n = my_darray_size(sheet->property_defs);
  for (i = 0u; i < n; i++) {
    my_theme_property_def_t* existing =
        (my_theme_property_def_t*)my_darray_get(sheet->property_defs, i);
    if (my_str_eq(existing->name, name)) {
      snprintf(existing->syntax, sizeof(existing->syntax), "%s", syntax);
      existing->inherits = inherits;
      existing->has_initial = has_initial;
      snprintf(existing->initial, sizeof(existing->initial), "%s", initial);
      return true;
    }
  }
  {
    my_theme_property_def_t* def = (my_theme_property_def_t*)my_mem_calloc(
        p->allocator, 1, sizeof(*def));
    if (def == NULL) {
      css_fail(p, "oom");
      return false;
    }
    snprintf(def->name, sizeof(def->name), "%s", name);
    snprintf(def->syntax, sizeof(def->syntax), "%s", syntax);
    def->inherits = inherits;
    def->has_initial = has_initial;
    snprintf(def->initial, sizeof(def->initial), "%s", initial);
    if (my_darray_push(sheet->property_defs, def) != MY_RET_OK) {
      my_mem_free(p->allocator, def);
      css_fail(p, "oom");
      return false;
    }
  }
  return true;
}

/* R670/R675: stamp a rule with a container condition — the first stamp
 * takes pair1, the second joins as pair2 (a conjunction); a third is
 * dropped (depth >= 3 keeps the innermost two, documented). The
 * innermost condition always lands first (inner blocks close first). */
static void css_rule_stamp_container_condition(my_css_rule_t* r,
                                               const char* query,
                                               const char* name) {
  if (r->container_query[0] == '\0') {
    snprintf(r->container_query, sizeof(r->container_query), "%s", query);
    snprintf(r->container_name, sizeof(r->container_name), "%s", name);
  } else if (r->container_query2[0] == '\0') {
    snprintf(r->container_query2, sizeof(r->container_query2), "%s", query);
    snprintf(r->container_name2, sizeof(r->container_name2), "%s", name);
  }
}

static bool css_parse_container_atrule(css_p_t* p, my_css_sheet_t* sheet,
                                       size_t at_rule_depth,
                                       uint32_t layer_id) {
  char query[MY_CSS_MAX_MEDIA_QUERY_BYTES + 1u];
  size_t query_length = 0u;
  char name[MY_STYLE_KEY_LEN];
  bool matches = false;

  name[0] = '\0';
  c_ws(p);
  /* R670: an optional container name precedes the query (`not` stays
   * query syntax, never a name). R673: `style(` too — the style()
   * function is a condition kind, not a name. */
  if (c_peek(p) != '(') {
    size_t saved = p->pos;
    char word[MY_STYLE_KEY_LEN];
    if (c_ident(p, word, sizeof(word)) && !my_str_eq(word, "not") &&
        !(my_str_eq(word, "style") && c_peek(p) == '(') &&
        !c_ident_char((unsigned char)c_peek(p))) {
      snprintf(name, sizeof(name), "%s", word);
      c_ws(p);
    } else {
      p->pos = saved;
    }
  }
  if (!css_container_query_opens(p)) {
    return css_skip_or_reject_atrule_with_capability(
        p, (uint32_t)MY_CSS_FEATURE_CONTAINER);
  }
  while (c_peek(p) >= 0 && c_peek(p) != '{') {
    if (query_length >= MY_CSS_MAX_MEDIA_QUERY_BYTES) {
      css_fail(p, "media query too long");
      return false;
    }
    query[query_length++] = (char)c_next(p);
  }
  query[query_length] = '\0';
  while (query_length > 0u &&
         (query[query_length - 1u] == ' ' || query[query_length - 1u] == '\t' ||
          query[query_length - 1u] == '\r' || query[query_length - 1u] == '\n')) {
    query[--query_length] = '\0';
  }
  if (c_peek(p) != '{') {
    return css_skip_or_reject_atrule_with_capability(
        p, (uint32_t)MY_CSS_FEATURE_CONTAINER);
  }
  if (p->container != NULL) {
    /* R663 parse-time evaluation (host-injected context). Names need
     * the match layer — a named query still rejects in this mode. */
    if (name[0] != '\0' ||
        !css_container_query_matches(p, query, query_length, &matches)) {
      return css_skip_or_reject_atrule_with_capability(
          p, (uint32_t)MY_CSS_FEATURE_CONTAINER);
    }
  } else {
    /* R670 match-time deferral: the feature shape validates now; the
     * query itself evaluates per element at theme lookup time. R681:
     * an and-only condition list (style() mixed with size features)
     * validates per condition. */
    if (!css_container_prelude_valid(query, query_length)) {
      return css_skip_or_reject_atrule_with_capability(
          p, (uint32_t)MY_CSS_FEATURE_CONTAINER);
    }
    matches = true;
  }
  if (at_rule_depth >= MY_CSS_MAX_AT_RULE_NESTING) {
    css_fail(p, "@container nesting depth exceeded");
    return false;
  }
  if (!matches) {
    css_skip_atrule(p, false);
    return !c_failed(p);
  }
  c_next(p);
  if (p->container != NULL) {
    return css_parse_rules(p, sheet, true, at_rule_depth + 1u, layer_id);
  }
  /* deferral: parse the block, then stamp the rules it created with the
   * condition (an inner @container stamps first and wins). */
  {
    size_t before = my_darray_size(sheet->rules);
    size_t i, after;
    if (!css_parse_rules(p, sheet, true, at_rule_depth + 1u, layer_id)) {
      return false;
    }
    after = my_darray_size(sheet->rules);
    for (i = before; i < after; i++) {
      my_css_rule_t* r = (my_css_rule_t*)my_darray_get(sheet->rules, i);
      css_rule_stamp_container_condition(r, query, name);
    }
    return true;
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

/* R655: an anonymous layer registers a fresh order slot with an empty name
 * (css_layer_name_valid rejects empty names, so the slot can never be found
 * again by a named lookup — each occurrence is its own layer). */
static uint32_t css_layer_add_anonymous(css_p_t* p) {
  if (p->layer_count >= MY_CSS_MAX_LAYERS) {
    css_fail(p, "CSS layer limit exceeded");
    return MY_CSS_UNLAYERED_ORDER;
  }
  p->layer_names[p->layer_count][0] = '\0';
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
  /* R655: anonymous block form `@layer { ... }` — a fresh layer per
   * occurrence (no name to concatenate under a parent layer). */
  if (c_peek(p) == '{') {
    layer_order = css_layer_add_anonymous(p);
    if (layer_order == MY_CSS_UNLAYERED_ORDER) return false;
    if (at_rule_depth >= MY_CSS_MAX_AT_RULE_NESTING) {
      css_fail(p, "@layer nesting depth exceeded");
      return false;
    }
    c_next(p);
    return css_parse_rules(p, sheet, true, at_rule_depth + 1u, layer_order);
  }
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

/* R621: parse one bounded complex selector — compounds joined by descendant
 * (whitespace) or child ('>') combinators — into OUT as the subject compound
 * plus nearest-first ancestors with per-edge child flags (the same fold as
 * css_rule's selector path; R620's scope-root loop generalized). Parsing
 * stops WITHOUT consuming the terminator: '{', ',' or ')' (the R626
 * parenthesized-prelude close), plus the 'to' keyword at compound-start
 * when stop_at_to is set (root preludes only — a limit compound named "to"
 * stays a plain type selector, as before R621). A dangling '>' at a
 * terminator and pseudo classes in any compound are
 * errors; the compound budget maps to "scope ancestor depth exceeded".
 * dangling '>' at a terminator and pseudo classes in any compound are
 * errors; the compound budget maps to "scope ancestor depth exceeded".
 * compound_count_out receives the raw compound count (0 = empty path — the
 * caller decides whether that is legal). */
static bool c_scope_selector_path(css_p_t* p, my_css_selector_t* out,
                                  bool stop_at_to, const char* invalid_msg,
                                  size_t* compound_count_out) {
  my_css_selector_t compounds[MY_CSS_MAX_ANCESTORS + 1u];
  bool direct_between[MY_CSS_MAX_ANCESTORS + 1u];
  size_t compound_count = 0u;
  bool pending_direct = false;
  size_t ci;
  memset(out, 0, sizeof(*out));
  out->state = -1;
  for (;;) {
    my_css_selector_t comp;
    bool separated;
    c_ws(p);
    if (c_peek(p) == '{' || c_peek(p) == ',' || c_peek(p) == ')' ||
        (stop_at_to && c_peek(p) == 't' && p->pos + 2u < p->len &&
         p->s[p->pos + 1u] == 'o' &&
         !c_ident_char((unsigned char)p->s[p->pos + 2u]))) {
      if (pending_direct) {
        css_fail(p, invalid_msg);
        css_mark_scope_error(p);
        return false;
      }
      break;
    }
    if (compound_count >= MY_CSS_MAX_ANCESTORS + 1u) {
      css_fail(p, "scope ancestor depth exceeded");
      css_mark_scope_error(p);
      return false;
    }
    memset(&comp, 0, sizeof(comp));
    comp.state = -1;
    if (!c_selector(p, &comp) || comp.state != -1 || comp.scope_ref ||
        comp.nest_ref) {
      css_fail(p, invalid_msg);
      css_mark_scope_error(p);
      return false;
    }
    if (compound_count > 0u) {
      direct_between[compound_count] = pending_direct;
    }
    compounds[compound_count++] = comp;
    separated = c_ws(p);
    if (c_peek(p) == '>') {
      c_next(p);
      c_ws(p);
      pending_direct = true;
      continue;
    }
    if (!separated && c_peek(p) != '{' && c_peek(p) != ',' &&
        c_peek(p) != ')') {
      css_fail(p, invalid_msg);
      css_mark_scope_error(p);
      return false;
    }
    pending_direct = false;
  }
  *compound_count_out = compound_count;
  if (compound_count == 0u) {
    return true;
  }
  *out = compounds[compound_count - 1u];
  out->ancestor_count = (u32)(compound_count - 1u);
  for (ci = 0u; ci + 1u < compound_count; ++ci) {
    size_t source = compound_count - 2u - ci;
    memcpy(out->ancestors[ci].widget_type, compounds[source].widget_type,
           sizeof(out->ancestors[ci].widget_type));
    memcpy(out->ancestors[ci].id, compounds[source].id,
           sizeof(out->ancestors[ci].id));
    memcpy(out->ancestors[ci].style_class, compounds[source].style_class,
           sizeof(out->ancestors[ci].style_class));
    out->ancestor_direct_path[ci] = direct_between[source + 1u];
  }
  return true;
}

static bool css_parse_scope_atrule(css_p_t* p, my_css_sheet_t* sheet,
                                   size_t at_rule_depth, uint32_t layer_id) {
  my_css_selector_t selector;
  my_css_selector_t limit;
  css_scope_root_t root_items[MY_CSS_MAX_SCOPE_NESTING];
  u32 root_item_count = 0u;
  bool parsed;
  bool has_root = false;
  bool has_limit = false;
  size_t limit_count = 0u;

  c_ws(p);
  memset(&selector, 0, sizeof(selector));
  selector.state = -1;
  if (c_peek(p) != '{') {
    /* R626: optional parenthesized preludes — the CSS-canonical
     * `@scope (root-list) [to (limit-list)]` form. Each side accepts its
     * own parens independently (bare forms keep working). */
    bool paren_root = false;
    bool starts_to;
    if (c_peek(p) == '(') {
      c_next(p);
      paren_root = true;
    }
    starts_to = !paren_root && c_peek(p) == 't' && p->pos + 2u < p->len &&
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
      /* R622: the root prelude is a bounded selector LIST of complex
       * selectors — items separated by ',', each via the shared path
       * parser ('to' terminates at compound-start). All items collect into
       * root_items; selector only carries the limits below. */
      for (;;) {
        my_css_selector_t item;
        css_scope_root_t* dst;
        size_t path_compounds = 0u;
        if (root_item_count >= MY_CSS_MAX_SCOPE_NESTING) {
          css_fail(p, "invalid @scope root selector");
          css_mark_scope_error(p);
          return false;
        }
        if (!c_scope_selector_path(p, &item, true,
                                   "invalid @scope root selector",
                                   &path_compounds)) {
          return false;
        }
        if (path_compounds == 0u) {
          css_fail(p, "invalid @scope root selector");
          return false;
        }
        dst = &root_items[root_item_count];
        memcpy(dst->subject.widget_type, item.widget_type,
               sizeof(dst->subject.widget_type));
        memcpy(dst->subject.id, item.id, sizeof(dst->subject.id));
        memcpy(dst->subject.style_class, item.style_class,
               sizeof(dst->subject.style_class));
        dst->ancestor_count = item.ancestor_count;
        memcpy(dst->ancestors, item.ancestors, sizeof(dst->ancestors));
        memcpy(dst->ancestor_direct_path, item.ancestor_direct_path,
               sizeof(dst->ancestor_direct_path));
        root_item_count++;
        has_root = true;
        c_ws(p);
        if (c_peek(p) != ',') break;
        c_next(p);
      }
      if (paren_root) {
        c_ws(p);
        if (c_peek(p) != ')') {
          css_fail(p, "invalid @scope root selector");
          css_mark_scope_error(p);
          return false;
        }
        c_next(p);
      }
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
      bool paren_limits = false;
      c_ws(p);
      if (c_peek(p) == '(') { /* R626: optional ( limit-list ) wrapper */
        c_next(p);
        paren_limits = true;
      }
      for (;;) {
        /* R621: each limit item is a bounded complex selector too — the
         * same path parser (',' terminates an item; 'to' is NOT special
         * here, a limit compound named "to" stays a type selector). */
        size_t path_compounds = 0u;
        c_ws(p);
        if (limit_count >= MY_CSS_MAX_SCOPE_NESTING ||
            !c_scope_selector_path(p, &limit, false,
                                   "invalid @scope limit selector",
                                   &path_compounds) ||
            path_compounds == 0u) {
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
        selector.scope_limits[limit_count].ancestor_count =
            limit.ancestor_count;
        memcpy(selector.scope_limits[limit_count].ancestors,
               limit.ancestors,
               sizeof(selector.scope_limits[limit_count].ancestors));
        memcpy(selector.scope_limits[limit_count].ancestor_direct_path,
               limit.ancestor_direct_path,
               sizeof(selector.scope_limits[limit_count]
                          .ancestor_direct_path));
        limit_count++;
        c_ws(p);
        if (c_peek(p) != ',') break;
        c_next(p);
      }
      if (paren_limits) {
        c_ws(p);
        if (c_peek(p) != ')') {
          css_fail(p, "invalid @scope limit selector");
          css_mark_scope_error(p);
          return false;
        }
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
    css_scope_frame_t* fr = &p->scope_frames[p->scope_count];
    u32 k;
    fr->root_count = has_root ? (u32)root_item_count : 0u;
    for (k = 0u; k < fr->root_count; ++k) {
      fr->roots[k] = root_items[k];
    }
    fr->scope_limit_count = selector.scope_limit_count;
    memcpy(fr->scope_limits, selector.scope_limits,
           sizeof(fr->scope_limits));
    p->scope_count++;
  }
  c_next(p);
  parsed = css_parse_rules(p, sheet, true, at_rule_depth + 1u, layer_id);
  if (has_root || selector.scope_limit_count != 0u) {
    p->scope_count--;
  }
  return parsed;
}

/* R656: @charset — a no-op statement valid only as the very first
 * top-level statement, with a (case-insensitive) utf-8 label: the engine
 * decodes UTF-8 only. Any other placement/label/form follows the usual
 * skip-or-reject convention. */
static bool css_parse_charset_atrule(css_p_t* p, bool nested,
                                     u32 statement_index) {
  static const char expected[] = "utf-8";
  char label[8];
  size_t length = 0u;
  int quote;
  size_t i;
  if (nested || statement_index != 0u) {
    return css_skip_or_reject_atrule(p);
  }
  c_ws(p);
  quote = c_peek(p);
  if (quote != '"' && quote != '\'') {
    return css_skip_or_reject_atrule(p);
  }
  c_next(p);
  while (c_peek(p) >= 0 && c_peek(p) != quote) {
    if (length + 1u >= sizeof(label)) {
      return css_skip_or_reject_atrule(p);
    }
    label[length++] = (char)c_next(p);
  }
  if (c_peek(p) != quote) {
    return css_skip_or_reject_atrule(p);
  }
  c_next(p);
  c_ws(p);
  if (c_peek(p) != ';') {
    return css_skip_or_reject_atrule(p);
  }
  c_next(p);
  if (length != 5u) {
    return css_skip_or_reject_atrule(p);
  }
  label[5] = '\0';
  for (i = 0u; i < 5u; ++i) {
    char c = label[i];
    if (c >= 'A' && c <= 'Z') c = (char)(c - 'A' + 'a');
    if (c != expected[i]) {
      return css_skip_or_reject_atrule(p);
    }
  }
  return true;
}

static bool css_parse_atrule(css_p_t* p, my_css_sheet_t* sheet,
                             size_t media_depth, uint32_t layer_id,
                             bool nested) {
  char name[MY_CSS_NAME_LEN];

  c_next(p); /* '@' */
  if (!c_ident(p, name, sizeof(name))) {
    css_fail(p, "expected @-rule name");
    return false;
  }
  if (my_str_eq(name, "charset")) {
    return css_parse_charset_atrule(p, nested, p->top_statements);
  }
  if (my_str_eq(name, "media")) {
    if (!nested) p->import_window_closed = true;
    return css_parse_media_atrule(p, sheet, media_depth, layer_id);
  }
  if (my_str_eq(name, "supports")) {
    if (!nested) p->import_window_closed = true;
    return css_parse_supports_atrule(p, sheet, media_depth, layer_id);
  }
  if (my_str_eq(name, "container")) {
    if (!nested) p->import_window_closed = true;
    return css_parse_container_atrule(p, sheet, media_depth, layer_id);
  }
  if (my_str_eq(name, "property")) {
    if (!nested) p->import_window_closed = true;
    return css_parse_property_atrule(p, sheet, nested);
  }
  if (my_str_eq(name, "layer")) {
    return css_parse_layer_atrule(p, sheet, media_depth, layer_id);
  }
  if (my_str_eq(name, "import")) {
    if (nested || p->import_window_closed) {
      return css_skip_or_reject_atrule_with_capability(
          p, (uint32_t)MY_CSS_FEATURE_IMPORTS);
    }
    return css_parse_import_atrule(p, sheet, media_depth, layer_id);
  }
  if (my_str_eq(name, "scope")) {
    if (!nested) p->import_window_closed = true;
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
      if (!css_parse_atrule(p, sheet, media_depth, layer_id, nested)) {
        return false;
      }
      if (!nested) p->top_statements++;
      continue;
    }
    rule = css_rule(p, sheet, media_depth, layer_id);
    if (rule == NULL) {
      return false;
    }
    if (my_darray_push(sheet->rules, rule) != MY_RET_OK) {
      css_rule_destroy(p->allocator, rule);
      css_fail(p, "oom");
      return false;
    }
    if (!nested) {
      p->top_statements++;
      p->import_window_closed = true;
    }
    /* R629: flush the rule's nested `&` rules after it (source order). */
    if (p->nest_pending != NULL) {
      size_t ni, nn = my_darray_size(p->nest_pending);
      for (ni = 0u; ni < nn; ++ni) {
        my_css_rule_t* nr =
            (my_css_rule_t*)my_darray_get(p->nest_pending, ni);
        if (my_darray_push(sheet->rules, nr) != MY_RET_OK) {
          /* leave the unflushed tail for the teardown cleanup */
          while (ni < nn) {
            css_rule_destroy(p->allocator,
                             (my_css_rule_t*)my_darray_get(p->nest_pending,
                                                           ni));
            ni++;
          }
          my_darray_clear(p->nest_pending);
          css_fail(p, "oom");
          return false;
        }
      }
      my_darray_clear(p->nest_pending);
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
  p.container = options != NULL ? options->container : NULL;
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
  sheet->property_defs = my_darray_create(allocator, 0);
  if (sheet->rules == NULL || sheet->property_defs == NULL) {
    if (sheet->rules != NULL) {
      my_darray_destroy(sheet->rules);
    }
    if (sheet->property_defs != NULL) {
      my_darray_destroy(sheet->property_defs);
    }
    my_mem_free(allocator, sheet);
    return NULL;
  }
  if (css_parse_rules(&p, sheet, false, 0u, MY_CSS_UNLAYERED_ORDER)) {
    css_finalize_layer_order(&p, sheet);
    if (p.nest_pending != NULL) {
      my_darray_destroy(p.nest_pending);
    }
    return sheet;
  }
  /* R629: an error path may leave unflushed nested rules — destroy them. */
  if (p.nest_pending != NULL) {
    size_t ni, nn = my_darray_size(p.nest_pending);
    for (ni = 0u; ni < nn; ++ni) {
      css_rule_destroy(allocator,
                       (my_css_rule_t*)my_darray_get(p.nest_pending, ni));
    }
    my_darray_destroy(p.nest_pending);
  }
  my_css_sheet_destroy(sheet);
  return NULL;
}

my_css_sheet_t* my_css_parse_ex(const my_allocator_t* allocator,
                                const char* css, size_t len, uint32_t flags,
                                my_css_error_t* err) {
  my_css_parse_options_t options = {flags, NULL, NULL, NULL, NULL};
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
  my_css_parse_options_t options = {flags, media, NULL, NULL, NULL};
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
                 MY_CSS_FEATURE_IMPORTS | MY_CSS_FEATURE_SCOPE |
                 MY_CSS_FEATURE_NESTING | MY_CSS_FEATURE_CONTAINER),
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
  n = my_darray_size(sheet->property_defs);
  for (i = 0; i < n; i++) {
    my_mem_free(sheet->allocator,
                (my_theme_property_def_t*)my_darray_get(sheet->property_defs,
                                                        i));
  }
  my_darray_destroy(sheet->property_defs);
  my_mem_free(sheet->allocator, sheet);
}

size_t my_css_rule_count(const my_css_sheet_t* sheet) {
  return sheet != NULL ? my_darray_size(sheet->rules) : 0;
}

size_t my_css_property_def_count(const my_css_sheet_t* sheet) {
  return sheet != NULL ? my_darray_size(sheet->property_defs) : 0u;
}

const my_theme_property_def_t* my_css_property_def(
    const my_css_sheet_t* sheet, size_t index) {
  if (sheet == NULL || index >= my_darray_size(sheet->property_defs)) {
    return NULL;
  }
  return (const my_theme_property_def_t*)my_darray_get(sheet->property_defs,
                                                       index);
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

/* R671: register one @property definition into a theme (last wins). */
static my_ret_t css_theme_register_property_def(
    my_theme_t* theme, const my_theme_property_def_t* def) {
  size_t i, n = my_darray_size(theme->property_defs);
  for (i = 0u; i < n; i++) {
    my_theme_property_def_t* existing =
        (my_theme_property_def_t*)my_darray_get(theme->property_defs, i);
    if (my_str_eq(existing->name, def->name)) {
      memcpy(existing, def, sizeof(*existing));
      return MY_RET_OK;
    }
  }
  {
    my_theme_property_def_t* copy = (my_theme_property_def_t*)my_mem_alloc(
        theme->allocator, sizeof(*copy));
    if (copy == NULL) {
      return MY_RET_OOM;
    }
    memcpy(copy, def, sizeof(*copy));
    return my_darray_push(theme->property_defs, copy);
  }
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
  /* R654: declaration tiers are applied in three phases — layered normal
   * (rank order), unlayered normal, then ALL important declarations in one
   * final flat pass. Same-entry conflicts resolve by overwrite order (the
   * theme's documented later-wins rule), so the important pass must come
   * last; cross-entry conflicts still compare the boosted specificity. */
  for (layer_pass = 0u; layer_pass <= MY_CSS_MAX_LAYERS + 1u; ++layer_pass) {
    bool important_pass = layer_pass == MY_CSS_MAX_LAYERS + 1u;
    uint32_t wanted_layer = layer_pass == MY_CSS_MAX_LAYERS
                                ? MY_CSS_UNLAYERED_ORDER
                                : (uint32_t)layer_pass;
    for (ri = 0; ri < my_css_rule_count(sheet); ri++) {
      const my_css_rule_t* rule = my_css_rule(sheet, ri);
      if (!important_pass && rule->layer_order != wanted_layer) continue;
    for (si = 0; si < my_css_selector_count(rule); si++) {
      const my_css_selector_t* sel = my_css_selector(rule, si);
      my_theme_ancestor_t ancestors[MY_THEME_MAX_ANCESTORS];
      my_theme_scope_limit_t scope_limits[MY_THEME_MAX_SCOPE_LIMITS];
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
        size_t li;
        if (ai >= MY_THEME_MAX_SCOPE_LIMITS ||
            sel->scope_limits[ai].ancestor_count > MY_THEME_MAX_ANCESTORS ||
            (sel->scope_limit_root_index[ai] != MY_CSS_SCOPE_ROOT_IMPLICIT &&
             sel->scope_limit_root_index[ai] >= sel->ancestor_count)) {
          ret = MY_RET_INVALID_PARAMS;
          break;
        }
        snprintf(scope_limits[ai].subject.widget_type,
                 sizeof(scope_limits[ai].subject.widget_type), "%s",
                 sel->scope_limits[ai].widget_type);
        snprintf(scope_limits[ai].subject.name,
                 sizeof(scope_limits[ai].subject.name), "%s",
                 sel->scope_limits[ai].id);
        snprintf(scope_limits[ai].subject.style_class,
                 sizeof(scope_limits[ai].subject.style_class), "%s",
                 sel->scope_limits[ai].style_class);
        scope_limits[ai].ancestor_count = sel->scope_limits[ai].ancestor_count;
        for (li = 0u; li < sel->scope_limits[ai].ancestor_count; ++li) {
          snprintf(scope_limits[ai].ancestors[li].widget_type,
                   sizeof(scope_limits[ai].ancestors[li].widget_type), "%s",
                   sel->scope_limits[ai].ancestors[li].widget_type);
          snprintf(scope_limits[ai].ancestors[li].name,
                   sizeof(scope_limits[ai].ancestors[li].name), "%s",
                   sel->scope_limits[ai].ancestors[li].id);
          snprintf(scope_limits[ai].ancestors[li].style_class,
                   sizeof(scope_limits[ai].ancestors[li].style_class), "%s",
                   sel->scope_limits[ai].ancestors[li].style_class);
          scope_limits[ai].ancestor_direct_path[li] =
              sel->scope_limits[ai].ancestor_direct_path[li];
        }
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
        const int32_t decl_specificity =
            specificity + (d->important ? MY_CSS_IMPORTANT_SPECIFICITY : 0);
        if (important_pass != d->important) continue;
        if (sel->state >= 0) {
          ret = my_theme_set_ex8(
              target, sel->widget_type, sel->id, sel->style_class,
              ancestors, sel->ancestor_count, sel->ancestor_direct_path,
              scope_limits, sel->scope_limit_count,
              scope_limit_root_indices, (my_widget_state_t)sel->state,
              d->key, &d->value, decl_specificity + 100,
              rule->container_query, rule->container_name,
              rule->container_query2, rule->container_name2);
        } else {
          /* no pseudo: write ONLY the normal slot — the state->normal
           * fallback covers the rest, so pseudo rules (more specific)
           * always win regardless of source order (CSS specificity) */
          ret = my_theme_set_ex8(
              target, sel->widget_type, sel->id, sel->style_class,
              ancestors, sel->ancestor_count, sel->ancestor_direct_path,
              scope_limits, sel->scope_limit_count,
              scope_limit_root_indices, MY_STATE_NORMAL, d->key, &d->value,
              decl_specificity, rule->container_query, rule->container_name,
              rule->container_query2, rule->container_name2);
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
  if (ret == MY_RET_OK) {
    for (di = 0u; di < my_darray_size(sheet->property_defs); di++) {
      ret = css_theme_register_property_def(
          candidate, (const my_theme_property_def_t*)my_darray_get(
                         sheet->property_defs, di));
      if (ret != MY_RET_OK) {
        break;
      }
    }
  }
  my_css_sheet_destroy(sheet);
  if (ret != MY_RET_OK) {
    my_theme_destroy(candidate);
    return ret;
  }
  old_entries = theme->entries;
  theme->entries = candidate->entries;
  candidate->entries = old_entries;
  {
    my_darray_t* old_defs = theme->property_defs;
    theme->property_defs = candidate->property_defs;
    candidate->property_defs = old_defs;
  }
  my_theme_destroy(candidate);
  return ret;
}

my_ret_t my_theme_load_css(my_theme_t* theme, const char* css) {
  return my_theme_load_css_with_options(theme, css, NULL);
}

/* R671: the theme's @property registry (linear scan — the registry is
 * tiny by design). */
static const my_theme_property_def_t* css_theme_property_def(
    const my_theme_t* theme, const char* name) {
  size_t i, n;
  if (theme == NULL) {
    return NULL;
  }
  n = my_darray_size(theme->property_defs);
  for (i = 0u; i < n; i++) {
    const my_theme_property_def_t* def =
        (const my_theme_property_def_t*)my_darray_get(theme->property_defs,
                                                      i);
    if (my_str_eq(def->name, name)) {
      return def;
    }
  }
  return NULL;
}

/* R666: var() lookup-time substitution. A custom property's value is the
 * element's own cascade first, then DOM inheritance (nearest ancestor
 * wins); only raw string values participate (R665 stores them as such).
 * R671: a registered inherits:false property stays local. */
static const my_value_t* css_var_custom_value(const my_theme_t* theme,
                                              const my_widget_t* widget,
                                              my_widget_state_t state,
                                              const char* name) {
  const my_widget_t* w = widget;
  const my_theme_property_def_t* def = css_theme_property_def(theme, name);
  while (w != NULL) {
    const my_value_t* v = my_theme_get_for_widget(theme, w, state, name);
    if (v != NULL) {
      return my_value_type(v) == MY_VALUE_STR ? v : NULL;
    }
    if (def != NULL && !def->inherits) {
      break;
    }
    w = w->parent;
  }
  return NULL;
}

#define CSS_VAR_MAX_DEPTH 8u
#define CSS_VAR_MAX_VISITING 16u
#define CSS_VAR_MAX_SUBST_BYTES 1024u

static bool css_var_emit(char* out, size_t cap, size_t* out_len, char c) {
  if (*out_len + 1u >= cap) {
    return false;
  }
  out[(*out_len)++] = c;
  return true;
}

/* Textually substitute var() references in text[0..length) into out.
 * visiting[] holds the custom-property names currently being expanded
 * (cycle detection: a re-entrant name is invalid → its fallback applies,
 * or the whole substitution fails). */
static bool css_var_substitute(const my_theme_t* theme,
                               const my_widget_t* widget,
                               my_widget_state_t state, const char* text,
                               size_t length, char* out, size_t cap,
                               size_t* out_len,
                               char visiting[][MY_STYLE_KEY_LEN],
                               unsigned visiting_count, unsigned depth) {
  size_t i = 0u;
  char quote = '\0';
  while (i < length) {
    char c = text[i];
    if (quote != '\0') {
      if (!css_var_emit(out, cap, out_len, c)) {
        return false;
      }
      if (c == '\\' && i + 1u < length) {
        i++;
        if (!css_var_emit(out, cap, out_len, text[i])) {
          return false;
        }
      } else if (c == quote) {
        quote = '\0';
      }
      i++;
      continue;
    }
    if (c == '\'' || c == '"') {
      quote = c;
      if (!css_var_emit(out, cap, out_len, c)) {
        return false;
      }
      i++;
      continue;
    }
    if (c == 'v' && (i == 0u || !c_ident_char((unsigned char)text[i - 1u])) &&
        i + 3u < length && text[i + 1u] == 'a' && text[i + 2u] == 'r' &&
        text[i + 3u] == '(') {
      size_t j = i + 4u;
      char name[MY_STYLE_KEY_LEN];
      size_t name_len = 0u;
      const char* fallback = NULL;
      size_t fallback_len = 0u;
      unsigned parens;
      bool cyclic = false;
      bool resolved = false;
      unsigned vi;
      while (j < length &&
             (text[j] == ' ' || text[j] == '\t' || text[j] == '\r' ||
              text[j] == '\n')) {
        j++;
      }
      if (j + 1u >= length || text[j] != '-' || text[j + 1u] != '-') {
        return false; /* malformed var(): a custom property name is due */
      }
      while (j < length && c_ident_char((unsigned char)text[j])) {
        if (name_len + 1u >= sizeof(name)) {
          return false;
        }
        name[name_len++] = text[j++];
      }
      name[name_len] = '\0';
      while (j < length &&
             (text[j] == ' ' || text[j] == '\t' || text[j] == '\r' ||
              text[j] == '\n')) {
        j++;
      }
      if (j < length && text[j] == ',') {
        size_t fb_start;
        size_t fb_end;
        char fb_quote = '\0';
        j++;
        while (j < length &&
               (text[j] == ' ' || text[j] == '\t' || text[j] == '\r' ||
                text[j] == '\n')) {
          j++;
        }
        fb_start = j;
        parens = 1u;
        while (j < length) {
          char fc = text[j];
          if (fb_quote != '\0') {
            if (fc == '\\' && j + 1u < length) {
              j += 2u;
              continue;
            }
            if (fc == fb_quote) {
              fb_quote = '\0';
            }
          } else if (fc == '\'' || fc == '"') {
            fb_quote = fc;
          } else if (fc == '(') {
            parens++;
          } else if (fc == ')') {
            parens--;
            if (parens == 0u) {
              break;
            }
          }
          j++;
        }
        if (parens != 0u) {
          return false; /* unbalanced fallback */
        }
        fb_end = j;
        while (fb_end > fb_start &&
               (text[fb_end - 1u] == ' ' || text[fb_end - 1u] == '\t' ||
                text[fb_end - 1u] == '\r' || text[fb_end - 1u] == '\n')) {
          fb_end--;
        }
        fallback = text + fb_start;
        fallback_len = fb_end - fb_start;
      } else if (j >= length || text[j] != ')') {
        return false; /* malformed var(): ',' or ')' is due */
      }
      if (j >= length) {
        return false;
      }
      i = j + 1u; /* past ')' */
      if (depth >= CSS_VAR_MAX_DEPTH) {
        return false;
      }
      for (vi = 0u; vi < visiting_count; vi++) {
        if (my_str_eq(visiting[vi], name)) {
          cyclic = true;
          break;
        }
      }
      if (!cyclic && visiting_count < CSS_VAR_MAX_VISITING) {
        const my_value_t* cv =
            css_var_custom_value(theme, widget, state, name);
        if (cv != NULL) {
          const char* cv_text = my_value_get_str(cv);
          const my_theme_property_def_t* def =
              css_theme_property_def(theme, name);
          /* R672: a registered property whose value fails its syntax is
           * guaranteed-invalid — the initial/fallback path takes over. */
          if (def == NULL ||
              css_property_syntax_check(def->syntax, cv_text)) {
            snprintf(visiting[visiting_count], MY_STYLE_KEY_LEN, "%s",
                     name);
            resolved = css_var_substitute(
                theme, widget, state, cv_text, strlen(cv_text), out, cap,
                out_len, visiting, visiting_count + 1u, depth + 1u);
          }
        }
        if (!resolved) {
          /* R671: an unset registered property falls back to its
           * initial value (before the var() fallback). */
          const my_theme_property_def_t* def =
              css_theme_property_def(theme, name);
          if (def != NULL && def->has_initial) {
            snprintf(visiting[visiting_count], MY_STYLE_KEY_LEN, "%s",
                     name);
            resolved = css_var_substitute(
                theme, widget, state, def->initial, strlen(def->initial),
                out, cap, out_len, visiting, visiting_count + 1u,
                depth + 1u);
          }
        }
      }
      if (!resolved && fallback != NULL) {
        resolved = css_var_substitute(theme, widget, state, fallback,
                                      fallback_len, out, cap, out_len,
                                      visiting, visiting_count, depth);
      }
      if (!resolved) {
        return false;
      }
      continue;
    }
    if (!css_var_emit(out, cap, out_len, c)) {
      return false;
    }
    i++;
  }
  return quote == '\0';
}

static bool css_value_copy_typed(const my_value_t* src, my_value_t* out) {
  switch (my_value_type(src)) {
    case MY_VALUE_UINT32:
      return my_value_set_uint32(out, my_value_get_uint32(src)) == MY_RET_OK;
    case MY_VALUE_INT32:
      return my_value_set_int32(out, my_value_get_int32(src)) == MY_RET_OK;
    case MY_VALUE_DOUBLE:
      return my_value_set_double(out, my_value_get_double(src)) == MY_RET_OK;
    case MY_VALUE_STR: {
      const char* s = my_value_get_str(src);
      return s != NULL && my_value_set_str(out, s) == MY_RET_OK;
    }
    default:
      return false;
  }
}

/* R670: does an ancestor's container_name list hold `name` (word-set
 * membership over the raw ident list)? */
static bool css_container_name_matches(const my_theme_t* theme,
                                       const my_widget_t* ancestor,
                                       const char* name) {
  const my_value_t* v =
      my_theme_get_for_widget(theme, ancestor, MY_STATE_NORMAL,
                              "container_name");
  const char* list;
  size_t name_len;
  if (v == NULL || my_value_type(v) != MY_VALUE_STR) {
    return false;
  }
  list = my_value_get_str(v);
  if (list == NULL) {
    return false;
  }
  name_len = strlen(name);
  while (*list != '\0') {
    const char* start;
    while (*list == ' ' || *list == '\t' || *list == '\r' ||
           *list == '\n') {
      list++;
    }
    start = list;
    while (*list != '\0' && *list != ' ' && *list != '\t' &&
           *list != '\r' && *list != '\n') {
      list++;
    }
    if ((size_t)(list - start) == name_len &&
        memcmp(start, name, name_len) == 0) {
      return true;
    }
  }
  return false;
}

/* R673/R677: evaluate one style() condition against a specific
 * ancestor — the custom property resolves there through the var()
 * machinery (own cascade → DOM inheritance, registered
 * inherits/initial honored); a registered property compares computed
 * values (typed by its syntax primitive), an unregistered property
 * compares whitespace-normalized raw text. */
static bool css_container_style_cond_matches(const my_theme_t* theme,
                                             const my_widget_t* ancestor,
                                             const char* cond,
                                             size_t cond_length) {
  char prop[MY_STYLE_KEY_LEN];
  char ref[MY_STYLE_KEY_LEN + 8u];
  const char* want;
  size_t want_length;
  char subst[CSS_VAR_MAX_SUBST_BYTES];
  size_t subst_length = 0u;
  char visiting[CSS_VAR_MAX_VISITING][MY_STYLE_KEY_LEN];
  int ref_length;
  if (!css_container_style_query_parse(cond, cond_length, prop,
                                       sizeof(prop), &want,
                                       &want_length)) {
    return false;
  }
  ref_length = snprintf(ref, sizeof(ref), "var(%s)", prop);
  if (ref_length < 0 || (size_t)ref_length >= sizeof(ref)) {
    return false;
  }
  if (!css_var_substitute(theme, ancestor, MY_STATE_NORMAL, ref,
                          (size_t)ref_length, subst, sizeof(subst),
                          &subst_length, visiting, 0u, 0u)) {
    return false;
  }
  {
    const my_theme_property_def_t* def = css_theme_property_def(theme, prop);
    if (want == NULL) {
      /* R682: the bare form asks whether the computed value differs
       * from the initial value. An unset property fails the
       * substitution above; an unset registered one resolves to its
       * initial and compares equal here. */
      if (def == NULL || !def->has_initial) {
        return true; /* any set value is non-initial */
      }
      return !css_container_style_typed_eq(def->syntax, subst, subst_length,
                                           def->initial,
                                           strlen(def->initial));
    }
    if (def != NULL) {
      return css_container_style_typed_eq(def->syntax, subst, subst_length,
                                          want, want_length);
    }
  }
  return css_container_style_value_eq(subst, subst_length, want,
                                      want_length);
}

bool my_theme_container_matches(const my_theme_t* theme,
                                const struct my_widget_t* anchor,
                                const char* container_query,
                                const char* container_name) {
  const my_widget_t* a = anchor;
  unsigned hops = 0u;
  const char* conds[MY_CSS_MAX_CONTAINER_CONDS];
  size_t cond_lens[MY_CSS_MAX_CONTAINER_CONDS];
  size_t n, ci;
  bool has_size = false;
  if (theme == NULL || container_query == NULL ||
      container_query[0] == '\0') {
    return false;
  }
  /* R681: an and-only condition list evaluates as a conjunction on one
   * query container; a single condition degenerates to the R670/R673
   * paths (merged here). An unsplittable whole string (pure size
   * or/not compositions) evaluates through the media machinery as
   * before. */
  n = css_container_split_and(container_query, strlen(container_query),
                              conds, cond_lens, MY_CSS_MAX_CONTAINER_CONDS);
  if (n == 0u) {
    conds[0] = container_query;
    cond_lens[0] = strlen(container_query);
    n = 1u;
  }
  for (ci = 0u; ci < n; ci++) {
    if (!css_container_query_is_style(conds[ci], cond_lens[ci])) {
      has_size = true;
      break;
    }
  }
  /* R673: pure-style lists take every ancestor as a candidate query
   * container (container-type gates size legs only); a list holding a
   * size leg resolves on the nearest size-qualified container so the
   * size legs have a rect to read. The name filters in both shapes;
   * the nearest qualifying container decides the whole conjunction. */
  while (a != NULL && hops++ < 16u) {
    if (has_size) {
      const my_value_t* type_v = my_theme_get_for_widget(
          theme, a, MY_STATE_NORMAL, "container_type");
      const char* type =
          (type_v != NULL && my_value_type(type_v) == MY_VALUE_STR)
              ? my_value_get_str(type_v)
              : NULL;
      if (type != NULL &&
          (my_str_eq(type, "size") || my_str_eq(type, "inline-size")) &&
          (container_name == NULL || container_name[0] == '\0' ||
           css_container_name_matches(theme, a, container_name))) {
        uint32_t w = a->rect.w > 0 ? (uint32_t)a->rect.w : 0u;
        uint32_t h = a->rect.h > 0 ? (uint32_t)a->rect.h : 0u;
        for (ci = 0u; ci < n; ci++) {
          bool leg = false;
          if (css_container_query_is_style(conds[ci], cond_lens[ci])) {
            leg = css_container_style_cond_matches(theme, a, conds[ci],
                                                   cond_lens[ci]);
          } else {
            bool verdict = false;
            leg = css_container_eval_size_query(conds[ci], cond_lens[ci],
                                               w, h, &verdict) &&
                  verdict;
          }
          if (!leg) {
            return false;
          }
        }
        return true;
      }
    } else if (container_name == NULL || container_name[0] == '\0' ||
               css_container_name_matches(theme, a, container_name)) {
      for (ci = 0u; ci < n; ci++) {
        if (!css_container_style_cond_matches(theme, a, conds[ci],
                                              cond_lens[ci])) {
          return false;
        }
      }
      return true;
    }
    a = a->parent;
  }
  return false;
}

bool my_theme_get_for_widget_var(const my_theme_t* theme,
                                 const struct my_widget_t* widget,
                                 my_widget_state_t state, const char* key,
                                 my_value_t* out) {
  const my_value_t* v;
  const char* raw;
  char subst[CSS_VAR_MAX_SUBST_BYTES];
  size_t subst_len = 0u;
  char visiting[CSS_VAR_MAX_VISITING][MY_STYLE_KEY_LEN];
  css_p_t probe;
  if (theme == NULL || widget == NULL || key == NULL || out == NULL) {
    return false;
  }
  v = my_theme_get_for_widget(theme, widget, state, key);
  if (v == NULL) {
    return false;
  }
  if (my_value_type(v) != MY_VALUE_STR) {
    return css_value_copy_typed(v, out);
  }
  raw = my_value_get_str(v);
  if (raw == NULL) {
    return false;
  }
  if (strstr(raw, "var(") == NULL) {
    return css_value_copy_typed(v, out);
  }
  if (!css_var_substitute(theme, widget, state, raw, strlen(raw), subst,
                          sizeof(subst), &subst_len, visiting, 0u, 0u)) {
    return false;
  }
  subst[subst_len] = '\0';
  memset(&probe, 0, sizeof(probe));
  probe.s = subst;
  probe.len = subst_len;
  probe.line = 1;
  probe.col = 1;
  c_ws(&probe);
  if (!css_value(&probe, out)) {
    return false;
  }
  c_ws(&probe);
  return c_peek(&probe) < 0;
}

my_ret_t my_theme_load_css_ex(my_theme_t* theme, const char* css,
                              uint32_t flags) {
  my_css_parse_options_t options = {flags, NULL, NULL, NULL, NULL};
  return my_theme_load_css_internal(theme, css, &options);
}

my_ret_t my_theme_load_css_media_ex(
    my_theme_t* theme, const char* css, uint32_t flags,
    const my_css_media_context_t* media) {
  if (media == NULL) return MY_RET_INVALID_PARAMS;
  {
    my_css_parse_options_t options = {flags, NULL, NULL, NULL, NULL};
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
    my_css_parse_options_t options = {flags, media, NULL, NULL, NULL};
    return my_theme_load_css_internal(theme, css, &options);
  }
}

my_ret_t my_theme_load_css_with_options(
    my_theme_t* theme, const char* css,
    const my_css_parse_options_t* options) {
  return my_theme_load_css_internal(theme, css, options);
}
