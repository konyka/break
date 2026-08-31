/**
 * @file my_conf_toml.c
 * @brief TOML subset parser (M17b) into a my_conf tree — see my_conf.h
 * for the supported subset. Line-oriented with a recursive value
 * parser; errors carry 1-based line/col.
 */
#include "myc/myconf/my_conf.h"

#include <errno.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#include "myc/my_darray.h"
#include "myc/my_str.h"

typedef struct toml_p_t {
  const my_allocator_t* allocator;
  const char* s;
  size_t len;
  size_t pos;
  int32_t line;
  int32_t col;
  my_conf_error_t* err;
  bool failed;             /**< set regardless of err (M17b fix) */
  my_conf_node_t* root;
  my_conf_node_t* cur;     /**< current table (weak) */
  my_darray_t* tables;     /**< defined table paths (char*), dup check */
} toml_p_t;

static void toml_fail(toml_p_t* p, const char* msg) {
  p->failed = true;
  if (p->err != NULL && p->err->msg[0] == '\0') {
    p->err->line = p->line;
    p->err->col = p->col;
    p->err->offset = (int64_t)p->pos;
    snprintf(p->err->msg, sizeof(p->err->msg), "%s", msg);
  }
}

static int t_peek(toml_p_t* p) {
  return p->pos < p->len ? (unsigned char)p->s[p->pos] : -1;
}

static int t_next(toml_p_t* p) {
  int c = t_peek(p);
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

static void t_skip_inline_ws(toml_p_t* p) {
  while (t_peek(p) == ' ' || t_peek(p) == '\t') {
    t_next(p);
  }
}

/** @brief ws incl. newlines (inside [..] / {..} values). */
static void t_skip_ws(toml_p_t* p) {
  int c;
  while ((c = t_peek(p)) == ' ' || c == '\t' || c == '\n' || c == '\r') {
    t_next(p);
  }
}

static bool t_failed(toml_p_t* p) {
  return p->failed;
}

/** @brief Parse a key: bare [A-Za-z0-9_-]+ or "quoted". Owned copy. */
static char* t_key(toml_p_t* p) {
  size_t start;
  size_t n;
  char* out;
  t_skip_inline_ws(p);
  if (t_peek(p) == '"') {
    /* quoted key: no escapes per the subset (documented) */
    t_next(p);
    start = p->pos;
    while (t_peek(p) != '"' && t_peek(p) >= 0 && t_peek(p) != '\n') {
      t_next(p);
    }
    if (t_peek(p) != '"') {
      toml_fail(p, "unterminated quoted key");
      return NULL;
    }
    n = p->pos - start;
    t_next(p);
  } else {
    int c;
    start = p->pos;
    while ((c = t_peek(p)) >= 0 &&
           ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') ||
            (c >= '0' && c <= '9') || c == '_' || c == '-')) {
      t_next(p);
    }
    n = p->pos - start;
    if (n == 0) {
      toml_fail(p, "missing key");
      return NULL;
    }
  }
  out = (char*)my_mem_alloc(p->allocator, n + 1);
  if (out == NULL) {
    toml_fail(p, "oom");
    return NULL;
  }
  memcpy(out, p->s + start, n);
  out[n] = '\0';
  return out;
}

/* ---------------- values ---------------- */

static my_conf_node_t* t_value(toml_p_t* p);

/** @brief Basic string "..." with TOML escapes. Owned. */
static char* t_basic_string(toml_p_t* p) {
  size_t cap = 16, n = 0;
  char* out = (char*)my_mem_alloc(p->allocator, cap);
  if (out == NULL) {
    toml_fail(p, "oom");
    return NULL;
  }
  t_next(p); /* opening quote */
  for (;;) {
    int c = t_next(p);
    if (c < 0 || c == '\n') {
      toml_fail(p, "unterminated string");
      goto fail;
    }
    if (c == '"') {
      break;
    }
    if (c == '\\') {
      c = t_next(p);
      switch (c) {
        case '"': case '\\': break;
        case 'b': c = '\b'; break;
        case 'f': c = '\f'; break;
        case 'n': c = '\n'; break;
        case 'r': c = '\r'; break;
        case 't': c = '\t'; break;
        case 'u': case 'U': {
          int digits = c == 'u' ? 4 : 8;
          unsigned long cp = 0;
          int k;
          for (k = 0; k < digits; k++) {
            int h = t_next(p);
            cp <<= 4;
            if (h >= '0' && h <= '9') cp |= (unsigned long)(h - '0');
            else if (h >= 'a' && h <= 'f') cp |= (unsigned long)(h - 'a' + 10);
            else if (h >= 'A' && h <= 'F') cp |= (unsigned long)(h - 'A' + 10);
            else {
              toml_fail(p, "bad unicode escape");
              goto fail;
            }
          }
          {
            char enc[4];
            int en = 0;
            if (cp < 0x80) {
              enc[en++] = (char)cp;
            } else if (cp < 0x800) {
              enc[en++] = (char)(0xC0 | (cp >> 6));
              enc[en++] = (char)(0x80 | (cp & 0x3F));
            } else if (cp < 0x10000) {
              enc[en++] = (char)(0xE0 | (cp >> 12));
              enc[en++] = (char)(0x80 | ((cp >> 6) & 0x3F));
              enc[en++] = (char)(0x80 | (cp & 0x3F));
            } else {
              enc[en++] = (char)(0xF0 | (cp >> 18));
              enc[en++] = (char)(0x80 | ((cp >> 12) & 0x3F));
              enc[en++] = (char)(0x80 | ((cp >> 6) & 0x3F));
              enc[en++] = (char)(0x80 | (cp & 0x3F));
            }
            while (n + (size_t)en + 1 > cap) {
              char* b2;
              cap *= 2;
              b2 = (char*)my_mem_realloc(p->allocator, out, cap);
              if (b2 == NULL) {
                toml_fail(p, "oom");
                goto fail;
              }
              out = b2;
            }
            memcpy(out + n, enc, (size_t)en);
            n += (size_t)en;
          }
          continue;
        }
        default:
          toml_fail(p, "bad escape");
          goto fail;
      }
    }
    if (n + 2 > cap) {
      char* b2;
      cap *= 2;
      b2 = (char*)my_mem_realloc(p->allocator, out, cap);
      if (b2 == NULL) {
        toml_fail(p, "oom");
        goto fail;
      }
      out = b2;
    }
    out[n++] = (char)c;
  }
  out[n] = '\0';
  return out;
fail:
  my_mem_free(p->allocator, out);
  return NULL;
}

/** @brief Literal string '...' (no escapes). Owned. */
static char* t_literal_string(toml_p_t* p) {
  size_t start;
  char* out;
  size_t n;
  t_next(p); /* opening quote */
  start = p->pos;
  while (t_peek(p) != '\'' && t_peek(p) >= 0 && t_peek(p) != '\n') {
    t_next(p);
  }
  if (t_peek(p) != '\'') {
    toml_fail(p, "unterminated literal string");
    return NULL;
  }
  n = p->pos - start;
  t_next(p);
  out = (char*)my_mem_alloc(p->allocator, n + 1);
  if (out == NULL) {
    toml_fail(p, "oom");
    return NULL;
  }
  memcpy(out, p->s + start, n);
  out[n] = '\0';
  return out;
}

/** @brief Strip underscores into buf (values only). */
static void t_clean_num(toml_p_t* p, char* buf, size_t cap, size_t start,
                        size_t end) {
  size_t i, n = 0;
  for (i = start; i < end && n + 1 < cap; i++) {
    if (p->s[i] != '_') {
      buf[n++] = p->s[i];
    }
  }
  buf[n] = '\0';
}

/** @brief Datetime-ish? 1979-05-27... or 07:32:00... (kept as STR). */
static bool t_is_datetime(toml_p_t* p) {
  size_t i;
  /* YYYY-MM-DD */
  if (p->pos + 4 < p->len) {
    for (i = 0; i < 4; i++) {
      if (p->s[p->pos + i] < '0' || p->s[p->pos + i] > '9') {
        break;
      }
    }
    if (i == 4 && p->s[p->pos + 4] == '-') {
      return true;
    }
  }
  /* HH:MM:SS */
  if (p->pos + 2 < p->len && p->s[p->pos] >= '0' && p->s[p->pos] <= '9' &&
      p->s[p->pos + 1] >= '0' && p->s[p->pos + 1] <= '9' &&
      p->s[p->pos + 2] == ':') {
    return true;
  }
  return false;
}

static my_conf_node_t* t_number_or_special(toml_p_t* p) {
  int c = t_peek(p);
  bool neg = false;
  bool is_double = false;
  char buf[96];
  /* sign */
  if (c == '+' || c == '-') {
    neg = c == '-';
    t_next(p);
    c = t_peek(p);
  }
  /* inf / nan */
  if (c == 'i' || c == 'n') {
    static const char INF[] = "inf";
    static const char NAN_S[] = "nan";
    const char* w = c == 'i' ? INF : NAN_S;
    size_t k;
    for (k = 0; w[k] != '\0'; k++) {
      if (t_next(p) != w[k]) {
        toml_fail(p, "bad number");
        return NULL;
      }
    }
    if (c == 'i') {
      return my_conf_new_double(p->allocator, neg ? -HUGE_VAL : HUGE_VAL);
    }
    return my_conf_new_double(p->allocator, NAN);
  }
  /* datetime -> STR verbatim (until ws/comment/eol/bracket) */
  if (t_is_datetime(p)) {
    size_t ds = p->pos;
    char* out;
    size_t n;
    while ((c = t_peek(p)) > ' ' && c != ',' && c != ']' && c != '}' &&
           c != '#') {
      t_next(p);
    }
    n = p->pos - ds;
    out = (char*)my_mem_alloc(p->allocator, n + 1);
    if (out == NULL) {
      toml_fail(p, "oom");
      return NULL;
    }
    memcpy(out, p->s + ds, n);
    out[n] = '\0';
    {
      my_conf_node_t* node = my_conf_new_str(p->allocator, out);
      my_mem_free(p->allocator, out);
      return node;
    }
  }
  /* hex/oct/bin */
  if (c == '0' && p->pos + 1 < p->len) {
    int base = 0;
    char p2 = p->s[p->pos + 1];
    if (p2 == 'x' || p2 == 'X') base = 16;
    if (p2 == 'o' || p2 == 'O') base = 8;
    if (p2 == 'b' || p2 == 'B') base = 2;
    if (base != 0) {
      long long v;
      size_t ds;
      t_next(p);
      t_next(p);
      ds = p->pos;
      while ((c = t_peek(p)) >= 0 &&
             ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'f') ||
              (c >= 'A' && c <= 'F') || c == '_')) {
        t_next(p);
      }
      if (p->pos == ds) {
        toml_fail(p, "empty hex/oct/bin literal");
        return NULL;
      }
      t_clean_num(p, buf, sizeof(buf), ds, p->pos);
      errno = 0;
      v = strtoll(buf, NULL, base);
      if (errno == ERANGE) {
        toml_fail(p, "integer overflow");
        return NULL;
      }
      return my_conf_new_int64(p->allocator,
                               (int64_t)(neg ? -v : v));
    }
  }
  /* decimal / float */
  {
    size_t ds = p->pos;
    while ((c = t_peek(p)) >= 0 &&
           ((c >= '0' && c <= '9') || c == '_' || c == '.' || c == 'e' ||
            c == 'E' || c == '+' || c == '-')) {
      if (c == '.' || c == 'e' || c == 'E') {
        is_double = true;
      }
      t_next(p);
    }
    if (p->pos == ds) {
      toml_fail(p, "bad number");
      return NULL;
    }
    t_clean_num(p, buf, sizeof(buf), ds, p->pos);
    if (is_double) {
      double d = strtod(buf, NULL);
      if (!isfinite(d)) {
        toml_fail(p, "number is not finite");
        return NULL;
      }
      return my_conf_new_double(p->allocator, neg ? -d : d);
    }
    /* leading zero check (TOML forbids 01) */
    if (buf[0] == '0' && buf[1] != '\0') {
      toml_fail(p, "leading zero");
      return NULL;
    }
    errno = 0;
    {
      long long v = strtoll(buf, NULL, 10);
      if (errno == ERANGE) {
        /* keep the JSON codec's rule: overflow -> DOUBLE */
        double d = strtod(buf, NULL);
        if (!isfinite(d)) {
          toml_fail(p, "number is not finite");
          return NULL;
        }
        return my_conf_new_double(p->allocator,
                                  (double)(neg ? -d : d));
      }
      return my_conf_new_int64(p->allocator, (int64_t)(neg ? -v : v));
    }
  }
}

/** @brief [ v, v, ... ] — may span lines. */
static my_conf_node_t* t_array(toml_p_t* p) {
  my_conf_node_t* arr = my_conf_new_array(p->allocator);
  if (arr == NULL) {
    toml_fail(p, "oom");
    return NULL;
  }
  t_next(p); /* '[' */
  t_skip_ws(p);
  if (t_peek(p) == ']') {
    t_next(p);
    return arr;
  }
  for (;;) {
    my_conf_node_t* v;
    t_skip_ws(p);
    v = t_value(p);
    if (v == NULL) {
      goto fail;
    }
    if (my_conf_array_push(arr, v) != MY_RET_OK) {
      my_conf_destroy(v);
      toml_fail(p, "oom");
      goto fail;
    }
    t_skip_ws(p);
    if (t_peek(p) == '#') { /* comment inside a multi-line array */
      while (t_peek(p) != '\n' && t_peek(p) >= 0) {
        t_next(p);
      }
      t_skip_ws(p);
    }
    if (t_peek(p) == ',') {
      t_next(p);
      t_skip_ws(p);
      if (t_peek(p) == ']') { /* trailing comma allowed in arrays */
        t_next(p);
        return arr;
      }
      continue;
    }
    if (t_peek(p) == ']') {
      t_next(p);
      return arr;
    }
    toml_fail(p, "expected ',' or ']' in array");
    goto fail;
  }
fail:
  my_conf_destroy(arr);
  return NULL;
}

/** @brief { k = v, ... } inline table (single line per the subset). */
static my_conf_node_t* t_inline_table(toml_p_t* p) {
  my_conf_node_t* obj = my_conf_new_object(p->allocator);
  if (obj == NULL) {
    toml_fail(p, "oom");
    return NULL;
  }
  t_next(p); /* '{' */
  t_skip_inline_ws(p);
  if (t_peek(p) == '}') {
    t_next(p);
    return obj;
  }
  for (;;) {
    char* key;
    my_conf_node_t* v;
    key = t_key(p);
    if (key == NULL) {
      goto fail;
    }
    t_skip_inline_ws(p);
    if (t_peek(p) != '=') {
      my_mem_free(p->allocator, key);
      toml_fail(p, "expected '=' in inline table");
      goto fail;
    }
    t_next(p);
    t_skip_inline_ws(p);
    v = t_value(p);
    if (v == NULL) {
      my_mem_free(p->allocator, key);
      goto fail;
    }
    if (my_conf_object_set(obj, key, v) != MY_RET_OK) {
      my_mem_free(p->allocator, key);
      my_conf_destroy(v);
      toml_fail(p, "oom");
      goto fail;
    }
    my_mem_free(p->allocator, key);
    t_skip_inline_ws(p);
    if (t_peek(p) == ',') {
      t_next(p);
      continue;
    }
    if (t_peek(p) == '}') {
      t_next(p);
      return obj;
    }
    toml_fail(p, "expected ',' or '}' in inline table");
    goto fail;
  }
fail:
  my_conf_destroy(obj);
  return NULL;
}

static my_conf_node_t* t_value(toml_p_t* p) {
  int c;
  t_skip_inline_ws(p);
  c = t_peek(p);
  if (c < 0 || c == '\n' || c == '#') {
    toml_fail(p, "missing value");
    return NULL;
  }
  if (c == '"') {
    char* s = t_basic_string(p);
    my_conf_node_t* n;
    if (s == NULL) {
      return NULL;
    }
    n = my_conf_new_str(p->allocator, s);
    my_mem_free(p->allocator, s);
    return n;
  }
  if (c == '\'') {
    char* s = t_literal_string(p);
    my_conf_node_t* n;
    if (s == NULL) {
      return NULL;
    }
    n = my_conf_new_str(p->allocator, s);
    my_mem_free(p->allocator, s);
    return n;
  }
  if (c == '[') {
    return t_array(p);
  }
  if (c == '{') {
    return t_inline_table(p);
  }
  if (c == 't' || c == 'f') {
    const char* w = c == 't' ? "true" : "false";
    size_t k;
    for (k = 0; w[k] != '\0'; k++) {
      if (t_next(p) != w[k]) {
        toml_fail(p, "bad literal");
        return NULL;
      }
    }
    return my_conf_new_bool(p->allocator, c == 't');
  }
  return t_number_or_special(p);
}

/* ---------------- tables ---------------- */

/** @brief Navigate/create the OBJECT chain for "a.b"; NULL on error. */
static my_conf_node_t* t_nav(toml_p_t* p, const char* path, size_t len,
                             bool create) {
  my_conf_node_t* cur = p->root;
  size_t i = 0;
  while (i < len) {
    size_t j = i;
    char* seg;
    my_conf_node_t* next = NULL;
    size_t k, n;
    while (j < len && path[j] != '.') {
      j++;
    }
    seg = (char*)my_mem_alloc(p->allocator, j - i + 1);
    if (seg == NULL) {
      toml_fail(p, "oom");
      return NULL;
    }
    memcpy(seg, path + i, j - i);
    seg[j - i] = '\0';
    n = my_conf_child_count(cur);
    for (k = 0; k < n; k++) {
      my_conf_node_t* c = my_conf_child(cur, k);
      if (my_conf_key(c) != NULL && strcmp(my_conf_key(c), seg) == 0) {
        next = c;
        break;
      }
    }
    if (next == NULL) {
      if (!create) {
        my_mem_free(p->allocator, seg);
        return NULL;
      }
      next = my_conf_new_object(p->allocator);
      if (next == NULL ||
          my_conf_object_set(cur, seg, next) != MY_RET_OK) {
        my_mem_free(p->allocator, seg);
        toml_fail(p, "oom");
        return NULL;
      }
    }
    my_mem_free(p->allocator, seg);
    if (my_conf_type(next) == MY_CONF_ARRAY) {
      /* [a.b] where b is a table array: step into its LAST table
       * (TOML semantics) */
      size_t cnt = my_conf_child_count(next);
      if (cnt == 0) {
        toml_fail(p, "empty table array in path");
        return NULL;
      }
      next = my_conf_child(next, cnt - 1);
    }
    if (my_conf_type(next) != MY_CONF_OBJECT) {
      toml_fail(p, "path conflicts with a scalar");
      return NULL;
    }
    cur = next;
    i = j + 1;
  }
  return cur;
}

/** @brief Record a defined table path (dup = error). */
static bool t_table_defined(toml_p_t* p, const char* path, size_t len) {
  size_t i, n = my_darray_size(p->tables);
  for (i = 0; i < n; i++) {
    const char* t = (const char*)my_darray_get(p->tables, i);
    if (strlen(t) == len && strncmp(t, path, len) == 0) {
      return true;
    }
  }
  return false;
}

static my_ret_t t_table_mark(toml_p_t* p, const char* path, size_t len) {
  char* copy = (char*)my_mem_alloc(p->allocator, len + 1);
  if (copy == NULL) {
    return MY_RET_OOM;
  }
  memcpy(copy, path, len);
  copy[len] = '\0';
  if (my_darray_push(p->tables, copy) != MY_RET_OK) {
    my_mem_free(p->allocator, copy);
    return MY_RET_OOM;
  }
  return MY_RET_OK;
}

/** @brief [a.b.c] or [[a.b]] header. */
static bool t_header(toml_p_t* p) {
  bool is_array = false;
  size_t start, n;
  my_conf_node_t* parent;
  t_next(p); /* '[' */
  if (t_peek(p) == '[') {
    is_array = true;
    t_next(p);
  }
  t_skip_inline_ws(p);
  start = p->pos;
  while (t_peek(p) != ']' && t_peek(p) >= 0 && t_peek(p) != '\n') {
    t_next(p);
  }
  if (t_peek(p) != ']') {
    toml_fail(p, "unterminated table header");
    return false;
  }
  n = p->pos - start;
  t_next(p);
  if (is_array) {
    if (t_peek(p) != ']') {
      toml_fail(p, "unterminated table-array header");
      return false;
    }
    t_next(p);
  }
  /* trim spaces around the path */
  while (n > 0 && (p->s[start] == ' ' || p->s[start] == '\t')) {
    start++;
    n--;
  }
  while (n > 0 && (p->s[start + n - 1] == ' ' || p->s[start + n - 1] == '\t')) {
    n--;
  }
  if (n == 0) {
    toml_fail(p, "empty table header");
    return false;
  }
  if (!is_array && t_table_defined(p, p->s + start, n)) {
    toml_fail(p, "table redefined");
    return false;
  }
  if (is_array) {
    /* split off the last segment: navigate to the parent, then push a
     * new table onto the (created) array */
    size_t dot = n;
    size_t k;
    my_conf_node_t* par;
    my_conf_node_t* arr;
    char* seg;
    for (k = n; k > 0; k--) {
      if (p->s[start + k - 1] == '.') {
        dot = k - 1;
        break;
      }
    }
    if (dot == n) {
      par = p->root;
      dot = 0;
    } else {
      par = t_nav(p, p->s + start, dot, true);
      if (par == NULL) {
        return false;
      }
      dot++; /* skip '.' */
    }
    seg = (char*)my_mem_alloc(p->allocator, n - (dot - (dot > 0)) + 1);
    if (seg == NULL) {
      toml_fail(p, "oom");
      return false;
    }
    {
      size_t seg_off = dot;
      size_t seg_len = n - seg_off;
      memcpy(seg, p->s + start + seg_off, seg_len);
      seg[seg_len] = '\0';
    }
    /* find-or-create the ARRAY under par */
    arr = NULL;
    {
      size_t cn = my_conf_child_count(par);
      size_t ci;
      for (ci = 0; ci < cn; ci++) {
        my_conf_node_t* c = my_conf_child(par, ci);
        if (my_conf_key(c) != NULL && strcmp(my_conf_key(c), seg) == 0) {
          arr = c;
          break;
        }
      }
    }
    if (arr == NULL) {
      arr = my_conf_new_array(p->allocator);
      if (arr == NULL || my_conf_object_set(par, seg, arr) != MY_RET_OK) {
        my_mem_free(p->allocator, seg);
        toml_fail(p, "oom");
        return false;
      }
    }
    my_mem_free(p->allocator, seg);
    if (my_conf_type(arr) != MY_CONF_ARRAY) {
      toml_fail(p, "table array conflicts with existing table");
      return false;
    }
    {
      my_conf_node_t* t = my_conf_new_object(p->allocator);
      if (t == NULL || my_conf_array_push(arr, t) != MY_RET_OK) {
        toml_fail(p, "oom");
        return false;
      }
      p->cur = t;
    }
    return true;
  }
  if (t_table_mark(p, p->s + start, n) != MY_RET_OK) {
    toml_fail(p, "oom");
    return false;
  }
  /* t_nav creates the whole chain and returns its tail */
  parent = t_nav(p, p->s + start, n, true);
  if (parent == NULL) {
    return false;
  }
  p->cur = parent;
  return true;
}

/* ---------------- line loop ---------------- */

/** @brief Skip to the next line; a trailing comment is consumed. */
static void t_end_line(toml_p_t* p) {
  t_skip_inline_ws(p);
  if (t_peek(p) == '#') {
    while (t_peek(p) != '\n' && t_peek(p) >= 0) {
      t_next(p);
    }
  }
  if (t_peek(p) == '\r') {
    t_next(p);
  }
  if (t_peek(p) == '\n') {
    t_next(p);
  } else if (t_peek(p) >= 0) {
    toml_fail(p, "trailing garbage on line");
  }
}

static bool toml_run(toml_p_t* p) {
  while (!t_failed(p)) {
    int c;
    t_skip_inline_ws(p);
    c = t_peek(p);
    if (c < 0) {
      break;
    }
    if (c == '\n' || c == '\r') {
      t_next(p);
      continue;
    }
    if (c == '#') {
      while (t_peek(p) != '\n' && t_peek(p) >= 0) {
        t_next(p);
      }
      continue;
    }
    if (c == '[') {
      if (!t_header(p)) {
        break;
      }
      t_end_line(p);
      continue;
    }
    /* key = value */
    {
      char* key = t_key(p);
      my_conf_node_t* v;
      if (key == NULL) {
        break;
      }
      t_skip_inline_ws(p);
      if (t_peek(p) != '=') {
        my_mem_free(p->allocator, key);
        toml_fail(p, "expected '='");
        break;
      }
      t_next(p);
      v = t_value(p);
      if (v == NULL) {
        my_mem_free(p->allocator, key);
        break;
      }
      /* duplicate key check inside the current table */
      {
        size_t i, n = my_conf_child_count(p->cur);
        bool dup = false;
        for (i = 0; i < n; i++) {
          my_conf_node_t* cc = my_conf_child(p->cur, i);
          if (my_conf_key(cc) != NULL && strcmp(my_conf_key(cc), key) == 0) {
            dup = true;
            break;
          }
        }
        if (dup) {
          my_mem_free(p->allocator, key);
          my_conf_destroy(v);
          toml_fail(p, "duplicate key");
          break;
        }
      }
      if (my_conf_object_set(p->cur, key, v) != MY_RET_OK) {
        my_mem_free(p->allocator, key);
        my_conf_destroy(v);
        toml_fail(p, "oom");
        break;
      }
      my_mem_free(p->allocator, key);
      t_end_line(p);
    }
  }
  return !t_failed(p);
}

my_conf_node_t* my_conf_parse_toml(const my_allocator_t* allocator,
                                   const char* data, size_t len,
                                   my_conf_error_t* err) {
  toml_p_t p;
  size_t i, n;
  if (data == NULL) {
    return NULL;
  }
  if (err != NULL) {
    memset(err, 0, sizeof(*err));
  }
  memset(&p, 0, sizeof(p));
  p.allocator = allocator;
  p.s = data;
  p.len = len;
  p.line = 1;
  p.col = 1;
  p.err = err;
  if (len > MY_CONF_TOML_MAX_BYTES) {
    toml_fail(&p, "TOML input exceeds resource budget");
    return NULL;
  }
  p.root = my_conf_new_object(allocator);
  p.tables = my_darray_create(allocator, 0);
  if (p.root == NULL || p.tables == NULL) {
    my_conf_destroy(p.root);
    if (p.tables != NULL) {
      my_darray_destroy(p.tables);
    }
    return NULL;
  }
  p.cur = p.root;
  if (!toml_run(&p)) {
    my_conf_destroy(p.root);
    p.root = NULL;
  }
  n = my_darray_size(p.tables);
  for (i = 0; i < n; i++) {
    my_mem_free(allocator, my_darray_get(p.tables, i));
  }
  my_darray_destroy(p.tables);
  return p.root;
}
