/**
 * @file my_conf_json.c
 * @brief JSON codec (M17a): full RFC 8259 — recursive-descent parser
 * (escapes incl. \uXXXX surrogate pairs, number boundaries) and
 * compact/pretty serializer.
 */
#include "myc/myconf/my_conf.h"

#include <errno.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

/* ---------------- parser ---------------- */

typedef struct json_p_t {
  const my_allocator_t* allocator;
  const char* s;
  size_t len;
  size_t pos;
  int32_t line; /* 1-based */
  int32_t col;  /* 1-based */
  int depth;    /* nesting guard */
  my_conf_error_t* err;
} json_p_t;

#define JSON_MAX_DEPTH 64

static void json_fail(json_p_t* p, const char* msg) {
  if (p->err != NULL && p->err->msg[0] == '\0') {
    p->err->line = p->line;
    p->err->col = p->col;
    p->err->offset = (int64_t)p->pos;
    snprintf(p->err->msg, sizeof(p->err->msg), "%s", msg);
  }
}

static int json_peek(json_p_t* p) {
  return p->pos < p->len ? (unsigned char)p->s[p->pos] : -1;
}

static int json_next(json_p_t* p) {
  int c = json_peek(p);
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

static void json_skip_ws(json_p_t* p) {
  int c;
  while ((c = json_peek(p)) == ' ' || c == '\t' || c == '\n' || c == '\r') {
    json_next(p);
  }
}

static bool json_expect(json_p_t* p, char c, const char* msg) {
  json_skip_ws(p);
  if (json_peek(p) != c) {
    json_fail(p, msg);
    return false;
  }
  json_next(p);
  return true;
}

static my_conf_node_t* json_value_rec(json_p_t* p);

/** @brief Depth-guarded wrapper (hostile nesting -> clean error). */
static my_conf_node_t* json_value(json_p_t* p) {
  my_conf_node_t* n;
  if (p->depth >= JSON_MAX_DEPTH) {
    json_fail(p, "nesting too deep");
    return NULL;
  }
  p->depth++;
  n = json_value_rec(p);
  p->depth--;
  return n;
}

/** @brief "..." — returns an owned string (NUL-free content kept raw). */
static char* json_string_raw(json_p_t* p) {
  size_t cap = 16, n = 0;
  char* out;
  if (!json_expect(p, '"', "expected string")) {
    return NULL;
  }
  out = (char*)my_mem_alloc(p->allocator, cap);
  if (out == NULL) {
    json_fail(p, "oom");
    return NULL;
  }
  for (;;) {
    int c = json_next(p);
    if (c < 0) {
      json_fail(p, "unterminated string");
      goto fail;
    }
    if (c == '"') {
      break;
    }
    if (c == '\\') {
      c = json_next(p);
      switch (c) {
        case '"': case '\\': case '/': break;
        case 'b': c = '\b'; break;
        case 'f': c = '\f'; break;
        case 'n': c = '\n'; break;
        case 'r': c = '\r'; break;
        case 't': c = '\t'; break;
        case 'u': {
          /* \uXXXX with surrogate pairing -> UTF-8 */
          unsigned long cp = 0;
          int k;
          for (k = 0; k < 4; k++) {
            int h = json_next(p);
            cp <<= 4;
            if (h >= '0' && h <= '9') cp |= (unsigned long)(h - '0');
            else if (h >= 'a' && h <= 'f') cp |= (unsigned long)(h - 'a' + 10);
            else if (h >= 'A' && h <= 'F') cp |= (unsigned long)(h - 'A' + 10);
            else {
              json_fail(p, "bad \\u escape");
              goto fail;
            }
          }
          if (cp >= 0xD800 && cp <= 0xDBFF) {
            /* high surrogate: need \uDC00..\uDFFF next */
            unsigned long lo = 0;
            if (json_next(p) != '\\' || json_next(p) != 'u') {
              json_fail(p, "lone high surrogate");
              goto fail;
            }
            for (k = 0; k < 4; k++) {
              int h = json_next(p);
              lo <<= 4;
              if (h >= '0' && h <= '9') lo |= (unsigned long)(h - '0');
              else if (h >= 'a' && h <= 'f') lo |= (unsigned long)(h - 'a' + 10);
              else if (h >= 'A' && h <= 'F') lo |= (unsigned long)(h - 'A' + 10);
              else {
                json_fail(p, "bad \\u escape");
                goto fail;
              }
            }
            if (lo < 0xDC00 || lo > 0xDFFF) {
              json_fail(p, "bad low surrogate");
              goto fail;
            }
            cp = 0x10000 + ((cp - 0xD800) << 10) + (lo - 0xDC00);
          } else if (cp >= 0xDC00 && cp <= 0xDFFF) {
            json_fail(p, "lone low surrogate");
            goto fail;
          }
          /* encode UTF-8 */
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
              char* bigger;
              cap *= 2;
              bigger = (char*)my_mem_realloc(p->allocator, out, cap);
              if (bigger == NULL) {
                json_fail(p, "oom");
                goto fail;
              }
              out = bigger;
            }
            memcpy(out + n, enc, (size_t)en);
            n += (size_t)en;
          }
          continue;
        }
        default:
          json_fail(p, "bad escape");
          goto fail;
      }
    } else if ((unsigned char)c < 0x20) {
      json_fail(p, "control char in string");
      goto fail;
    }
    if (n + 2 > cap) {
      char* bigger;
      cap *= 2;
      bigger = (char*)my_mem_realloc(p->allocator, out, cap);
      if (bigger == NULL) {
        json_fail(p, "oom");
        goto fail;
      }
      out = bigger;
    }
    out[n++] = (char)c;
  }
  out[n] = '\0';
  return out;
fail:
  my_mem_free(p->allocator, out);
  return NULL;
}

static my_conf_node_t* json_number(json_p_t* p) {
  size_t start = p->pos;
  bool is_double = false;
  char buf[64];
  size_t n = 0;
  int c = json_peek(p);
  if (c == '-') {
    json_next(p);
  }
  c = json_peek(p);
  if (c == '0') {
    json_next(p);
    /* a digit straight after 0 is a leading-zero error */
    if (json_peek(p) >= '0' && json_peek(p) <= '9') {
      json_fail(p, "leading zero");
      return NULL;
    }
  } else if (c >= '1' && c <= '9') {
    while (json_peek(p) >= '0' && json_peek(p) <= '9') {
      json_next(p);
    }
  } else {
    json_fail(p, "bad number");
    return NULL;
  }
  if (json_peek(p) == '.') {
    is_double = true;
    json_next(p);
    if (json_peek(p) < '0' || json_peek(p) > '9') {
      json_fail(p, "bad fraction");
      return NULL;
    }
    while (json_peek(p) >= '0' && json_peek(p) <= '9') {
      json_next(p);
    }
  }
  c = json_peek(p);
  if (c == 'e' || c == 'E') {
    is_double = true;
    json_next(p);
    c = json_peek(p);
    if (c == '+' || c == '-') {
      json_next(p);
    }
    if (json_peek(p) < '0' || json_peek(p) > '9') {
      json_fail(p, "bad exponent");
      return NULL;
    }
    while (json_peek(p) >= '0' && json_peek(p) <= '9') {
      json_next(p);
    }
  }
  n = p->pos - start;
  if (n >= sizeof(buf)) {
    json_fail(p, "number too long");
    return NULL;
  }
  memcpy(buf, p->s + start, n);
  buf[n] = '\0';
  if (is_double) {
    double d = strtod(buf, NULL);
    if (!isfinite(d)) {
      json_fail(p, "number is not finite");
      return NULL;
    }
    return my_conf_new_double(p->allocator, d);
  }
  {
    long long v;
    /* int64 overflow (strtoll sets ERANGE and clamps) falls back to
     * DOUBLE — documented; "-0" stays INT64 (no string round-trip
     * tricks, errno is the authority) */
    errno = 0;
    v = strtoll(buf, NULL, 10);
    if (errno == ERANGE) {
      double d = strtod(buf, NULL);
      if (!isfinite(d)) {
        json_fail(p, "number is not finite");
        return NULL;
      }
      return my_conf_new_double(p->allocator, d);
    }
    return my_conf_new_int64(p->allocator, (int64_t)v);
  }
}

/** @brief Consume a literal ("true"/"false"/"null"); false on mismatch
 * (the mismatching char is NOT consumed, so the error position is
 * exact). */
static bool json_match(json_p_t* p, const char* word) {
  size_t k;
  for (k = 0; word[k] != '\0'; k++) {
    if (json_peek(p) != word[k]) {
      json_fail(p, "bad literal");
      return false;
    }
    json_next(p);
  }
  return true;
}

static my_conf_node_t* json_value_rec(json_p_t* p) {
  int c;
  json_skip_ws(p);
  c = json_peek(p);
  if (c < 0) {
    json_fail(p, "unexpected end");
    return NULL;
  }
  if (c == '{') {
    my_conf_node_t* obj = my_conf_new_object(p->allocator);
    if (obj == NULL) {
      json_fail(p, "oom");
      return NULL;
    }
    json_next(p);
    json_skip_ws(p);
    if (json_peek(p) == '}') {
      json_next(p);
      return obj;
    }
    for (;;) {
      char* key;
      my_conf_node_t* val;
      json_skip_ws(p);
      key = json_string_raw(p);
      if (key == NULL) {
        my_conf_destroy(obj);
        return NULL;
      }
      if (!json_expect(p, ':', "expected ':'")) {
        my_mem_free(p->allocator, key);
        my_conf_destroy(obj);
        return NULL;
      }
      val = json_value(p);
      if (val == NULL) {
        my_mem_free(p->allocator, key);
        my_conf_destroy(obj);
        return NULL;
      }
      if (my_conf_object_set(obj, key, val) != MY_RET_OK) {
        my_mem_free(p->allocator, key);
        my_conf_destroy(val);
        my_conf_destroy(obj);
        json_fail(p, "oom");
        return NULL;
      }
      my_mem_free(p->allocator, key);
      json_skip_ws(p);
      c = json_next(p);
      if (c == ',') {
        json_skip_ws(p);
        if (json_peek(p) == '}') {
          json_fail(p, "trailing comma");
          my_conf_destroy(obj);
          return NULL;
        }
        continue;
      }
      if (c == '}') {
        return obj;
      }
      json_fail(p, "expected ',' or '}'");
      my_conf_destroy(obj);
      return NULL;
    }
  }
  if (c == '[') {
    my_conf_node_t* arr = my_conf_new_array(p->allocator);
    if (arr == NULL) {
      json_fail(p, "oom");
      return NULL;
    }
    json_next(p);
    json_skip_ws(p);
    if (json_peek(p) == ']') {
      json_next(p);
      return arr;
    }
    for (;;) {
      my_conf_node_t* val = json_value(p);
      if (val == NULL) {
        my_conf_destroy(arr);
        return NULL;
      }
      if (my_conf_array_push(arr, val) != MY_RET_OK) {
        my_conf_destroy(val);
        my_conf_destroy(arr);
        json_fail(p, "oom");
        return NULL;
      }
      json_skip_ws(p);
      c = json_next(p);
      if (c == ',') {
        json_skip_ws(p);
        if (json_peek(p) == ']') {
          json_fail(p, "trailing comma");
          my_conf_destroy(arr);
          return NULL;
        }
        continue;
      }
      if (c == ']') {
        return arr;
      }
      json_fail(p, "expected ',' or ']'");
      my_conf_destroy(arr);
      return NULL;
    }
  }
  if (c == '"') {
    char* s = json_string_raw(p);
    my_conf_node_t* n;
    if (s == NULL) {
      return NULL;
    }
    n = my_conf_new_str(p->allocator, s);
    my_mem_free(p->allocator, s);
    return n;
  }
  if (c == 't') {
    if (!json_match(p, "true")) {
      return NULL;
    }
    return my_conf_new_bool(p->allocator, true);
  }
  if (c == 'f') {
    if (!json_match(p, "false")) {
      return NULL;
    }
    return my_conf_new_bool(p->allocator, false);
  }
  if (c == 'n') {
    if (!json_match(p, "null")) {
      return NULL;
    }
    return my_conf_new_null(p->allocator);
  }
  if (c == '-' || (c >= '0' && c <= '9')) {
    return json_number(p);
  }
  json_fail(p, "unexpected character");
  return NULL;
}

my_conf_node_t* my_conf_parse_json(const my_allocator_t* allocator,
                                   const char* data, size_t len,
                                   my_conf_error_t* err) {
  json_p_t p;
  my_conf_node_t* root;
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
  if (len > MY_CONF_JSON_MAX_BYTES) {
    json_fail(&p, "JSON input exceeds resource budget");
    return NULL;
  }
  root = json_value(&p);
  if (root == NULL) {
    return NULL;
  }
  json_skip_ws(&p);
  if (p.pos < p.len) {
    json_fail(&p, "trailing garbage");
    my_conf_destroy(root);
    return NULL;
  }
  return root;
}

/* ---------------- serializer ---------------- */

typedef struct json_w_t {
  const my_allocator_t* allocator;
  char* buf;
  size_t len;
  size_t cap;
  bool pretty;
  int depth;
  bool oom;
} json_w_t;

static void jw_raw(json_w_t* w, const char* s, size_t n) {
  size_t needed;
  if (w->oom) {
    return;
  }
  if (n > (size_t)MY_CONF_JSON_MAX_BYTES ||
      w->len > (size_t)MY_CONF_JSON_MAX_BYTES - n) {
    w->oom = true;
    return;
  }
  needed = w->len + n;
  if (needed + 1u > w->cap) {
    char* bigger;
    while (needed + 1u > w->cap) {
      if (w->cap > ((size_t)MY_CONF_JSON_MAX_BYTES + 1u) / 2u) {
        w->cap = (size_t)MY_CONF_JSON_MAX_BYTES + 1u;
        break;
      }
      w->cap *= 2u;
    }
    if (needed + 1u > w->cap) {
      w->oom = true;
      return;
    }
    bigger = (char*)my_mem_realloc(w->allocator, w->buf, w->cap);
    if (bigger == NULL) {
      w->oom = true;
      return;
    }
    w->buf = bigger;
  }
  memcpy(w->buf + w->len, s, n);
  w->len += n;
  w->buf[w->len] = '\0';
}

static void jw_str(json_w_t* w, const char* s) {
  jw_raw(w, s, strlen(s));
}

static void jw_indent(json_w_t* w) {
  int i;
  if (!w->pretty) {
    return;
  }
  jw_str(w, "\n");
  for (i = 0; i < w->depth * 2; i++) {
    jw_str(w, " ");
  }
}

static void jw_string(json_w_t* w, const char* s) {
  jw_str(w, "\"");
  for (; s != NULL && *s != '\0'; s++) {
    if (w->oom) {
      return;
    }
    unsigned char c = (unsigned char)*s;
    switch (c) {
      case '"': jw_str(w, "\\\""); break;
      case '\\': jw_str(w, "\\\\"); break;
      case '\b': jw_str(w, "\\b"); break;
      case '\f': jw_str(w, "\\f"); break;
      case '\n': jw_str(w, "\\n"); break;
      case '\r': jw_str(w, "\\r"); break;
      case '\t': jw_str(w, "\\t"); break;
      default:
        if (c < 0x20) {
          char esc[8];
          snprintf(esc, sizeof(esc), "\\u%04x", c);
          jw_str(w, esc);
        } else {
          jw_raw(w, (const char*)s, 1); /* UTF-8 passes through */
        }
        break;
    }
  }
  jw_str(w, "\"");
}

static void jw_value(json_w_t* w, my_conf_node_t* node) {
  char num[40];
  size_t i, n;
  if (node == NULL) {
    jw_str(w, "null");
    return;
  }
  switch (my_conf_type(node)) {
    case MY_CONF_NULL:
      jw_str(w, "null");
      break;
    case MY_CONF_BOOL:
      jw_str(w, my_conf_as_bool(node, false) ? "true" : "false");
      break;
    case MY_CONF_INT64:
      snprintf(num, sizeof(num), "%lld",
               (long long)my_conf_as_int64(node, 0));
      jw_str(w, num);
      break;
    case MY_CONF_DOUBLE: {
      double d = my_conf_as_double(node, 0.0);
      if (d == (double)(long long)d && d < 9.0e15 && d > -9.0e15) {
        /* integral doubles print with .0 so the type survives a
         * round trip (1.5 stays 1.5, 2.0 must not become "2") */
        snprintf(num, sizeof(num), "%.1f", d);
      } else {
        snprintf(num, sizeof(num), "%.17g", d);
      }
      jw_str(w, num);
      break;
    }
    case MY_CONF_STR:
      jw_string(w, my_conf_as_str(node, ""));
      break;
    case MY_CONF_OBJECT:
      jw_str(w, "{");
      w->depth++;
      n = my_conf_child_count(node);
      for (i = 0; i < n; i++) {
        my_conf_node_t* c = my_conf_child(node, i);
        jw_indent(w);
        jw_string(w, my_conf_key(c));
        jw_str(w, w->pretty ? ": " : ":");
        jw_value(w, c);
        if (i + 1 < n) {
          jw_str(w, ",");
        }
      }
      w->depth--;
      if (n > 0) {
        jw_indent(w);
      }
      jw_str(w, "}");
      break;
    case MY_CONF_ARRAY:
      jw_str(w, "[");
      w->depth++;
      n = my_conf_child_count(node);
      for (i = 0; i < n; i++) {
        jw_indent(w);
        jw_value(w, my_conf_child(node, i));
        if (i + 1 < n) {
          jw_str(w, ",");
        }
      }
      w->depth--;
      if (n > 0) {
        jw_indent(w);
      }
      jw_str(w, "]");
      break;
    default:
      break;
  }
}

char* my_conf_to_json_str(const my_allocator_t* allocator,
                          my_conf_node_t* node, bool pretty) {
  json_w_t w;
  memset(&w, 0, sizeof(w));
  w.allocator = allocator;
  w.cap = 128;
  w.buf = (char*)my_mem_alloc(allocator, w.cap);
  if (w.buf == NULL) {
    return NULL;
  }
  w.buf[0] = '\0';
  w.pretty = pretty;
  jw_value(&w, node);
  if (pretty) {
    jw_str(&w, "\n");
  }
  if (w.oom) {
    my_mem_free(allocator, w.buf);
    return NULL;
  }
  return w.buf;
}
