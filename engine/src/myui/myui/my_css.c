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
  bool failed;
} css_p_t;

static void css_fail(css_p_t* p, const char* msg) {
  p->failed = true;
  if (p->err != NULL && p->err->msg[0] == '\0') {
    p->err->line = p->line;
    p->err->col = p->col;
    snprintf(p->err->msg, sizeof(p->err->msg), "%s", msg);
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

static my_css_rule_t* css_rule_new(const my_allocator_t* allocator) {
  my_css_rule_t* r =
      (my_css_rule_t*)my_mem_calloc(allocator, 1, sizeof(my_css_rule_t));
  if (r == NULL) {
    return NULL;
  }
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
static void css_skip_atrule(css_p_t* p) {
  int depth = 0;
  char quote = '\0';
  MY_LOGW("my_css: skipping @-rule (unsupported)");
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

/** @brief One rule: selectors { declarations }. */
static my_css_rule_t* css_rule(css_p_t* p) {
  my_css_rule_t* r = css_rule_new(p->allocator);
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

my_css_sheet_t* my_css_parse(const my_allocator_t* allocator,
                             const char* css, size_t len,
                             my_css_error_t* err) {
  css_p_t p;
  my_css_sheet_t* sheet;
  if (css == NULL) {
    return NULL;
  }
  if (err != NULL) {
    memset(err, 0, sizeof(*err));
  }
  memset(&p, 0, sizeof(p));
  p.allocator = allocator;
  p.s = css;
  p.len = len;
  p.line = 1;
  p.col = 1;
  p.err = err;
  if (len > MY_CSS_MAX_BYTES) {
    css_fail(&p, "CSS input exceeds resource budget");
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
  for (;;) {
    my_css_rule_t* r;
    c_ws(&p);
    if (c_failed(&p)) {
      goto fail;
    }
    if (c_peek(&p) < 0) {
      break;
    }
    if (c_peek(&p) == '@') {
      c_next(&p);
      css_skip_atrule(&p);
      if (c_failed(&p)) {
        goto fail;
      }
      continue;
    }
    r = css_rule(&p);
    if (r == NULL) {
      goto fail;
    }
    if (my_darray_push(sheet->rules, r) != MY_RET_OK) {
      css_rule_destroy(allocator, r);
      css_fail(&p, "oom");
      goto fail;
    }
  }
  return sheet;
fail:
  my_css_sheet_destroy(sheet);
  return NULL;
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

my_ret_t my_theme_load_css(my_theme_t* theme, const char* css) {
  my_css_sheet_t* sheet;
  size_t ri, si, di;
  my_ret_t ret = MY_RET_OK;
  if (theme == NULL || css == NULL) {
    return MY_RET_INVALID_PARAMS;
  }
  sheet = my_css_parse(theme->allocator, css, strlen(css), NULL);
  if (sheet == NULL) {
    return MY_RET_FAIL;
  }
  for (ri = 0; ri < my_css_rule_count(sheet); ri++) {
    const my_css_rule_t* rule = my_css_rule(sheet, ri);
    for (si = 0; si < my_css_selector_count(rule); si++) {
      const my_css_selector_t* sel = my_css_selector(rule, si);
      my_theme_ancestor_t ancestors[MY_THEME_MAX_ANCESTORS];
      int32_t specificity = 0;
      const char* p;
      size_t ai;
      memset(ancestors, 0, sizeof(ancestors));
      for (ai = 0; ai < sel->ancestor_count; ai++) {
        snprintf(ancestors[ai].widget_type, sizeof(ancestors[ai].widget_type),
                 "%s", sel->ancestors[ai].widget_type);
        snprintf(ancestors[ai].name, sizeof(ancestors[ai].name), "%s",
                 sel->ancestors[ai].id);
        snprintf(ancestors[ai].style_class,
                 sizeof(ancestors[ai].style_class), "%s",
                 sel->ancestors[ai].style_class);
      }
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
        size_t ai;
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
          ret = my_theme_set_ex4(
              theme, sel->widget_type, sel->id, sel->style_class,
              ancestors, sel->ancestor_count,
              sel->ancestor_direct_path, (my_widget_state_t)sel->state,
              d->key, &d->value, specificity + 100);
        } else {
          /* no pseudo: write ONLY the normal slot — the state->normal
           * fallback covers the rest, so pseudo rules (more specific)
           * always win regardless of source order (CSS specificity) */
          ret = my_theme_set_ex4(
              theme, sel->widget_type, sel->id, sel->style_class,
              ancestors, sel->ancestor_count,
              sel->ancestor_direct_path, MY_STATE_NORMAL, d->key, &d->value,
              specificity);
        }
        if (ret != MY_RET_OK) {
          break;
        }
      }
    }
  }
  my_css_sheet_destroy(sheet);
  return ret;
}
