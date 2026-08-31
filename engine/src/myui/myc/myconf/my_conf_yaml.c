/**
 * @file my_conf_yaml.c
 * @brief YAML subset parser (M17b) into a my_conf tree — see my_conf.h
 * for the supported subset and the hard-error list. Indent-block
 * recursive descent over pre-split lines; errors carry 1-based lines.
 */
#include "myc/myconf/my_conf.h"

#include <errno.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

/* ---------------- line model ---------------- */

typedef struct yline_t {
  size_t start;  /**< byte offset of the line's first char */
  size_t len;    /**< line length (no newline) */
  int32_t indent;/**< leading spaces */
  int32_t lineno;/**< 1-based */
  bool blank;    /**< empty or comment-only */
} yline_t;

typedef struct yaml_p_t {
  const my_allocator_t* allocator;
  const char* s;
  size_t len;
  yline_t* lines;
  size_t n_lines;
  size_t i;      /**< cursor over lines */
  size_t block_depth;
  size_t flow_depth;
  bool failed;
  my_conf_error_t* err;
} yaml_p_t;

static void y_fail(yaml_p_t* p, int32_t lineno, int32_t col,
                   const char* msg) {
  p->failed = true;
  if (p->err != NULL && p->err->msg[0] == '\0') {
    p->err->line = lineno;
    p->err->col = col;
    p->err->offset = 0;
    snprintf(p->err->msg, sizeof(p->err->msg), "%s", msg);
  }
}

static bool y_failed(yaml_p_t* p) {
  return p->failed;
}

/** @brief Split into lines; tab indentation is a hard error. */
static bool y_split(yaml_p_t* p) {
  size_t pos = 0;
  size_t cap = 16;
  int32_t lineno = 1;
  if (p->len > MY_CONF_YAML_MAX_BYTES) {
    y_fail(p, 1, 1, "YAML input exceeds resource budget");
    return false;
  }
  p->lines = (yline_t*)my_mem_alloc(p->allocator, cap * sizeof(yline_t));
  if (p->lines == NULL) {
    return false;
  }
  while (pos < p->len) {
    if (p->n_lines >= MY_CONF_YAML_MAX_LINES) {
      y_fail(p, lineno, 1, "YAML line count exceeds resource budget");
      return false;
    }
    size_t start = pos;
    size_t len;
    int32_t indent = 0;
    bool tab = false;
    yline_t* l;
    while (pos < p->len && p->s[pos] != '\n') {
      pos++;
    }
    len = pos - start;
    if (pos < p->len) {
      pos++; /* the \n */
    }
    /* strip a trailing \r */
    if (len > 0 && p->s[start + len - 1] == '\r') {
      len--;
    }
    while ((size_t)indent < len) {
      char c = p->s[start + indent];
      if (c == ' ') {
        indent++;
      } else if (c == '\t') {
        tab = true;
        break;
      } else {
        break;
      }
    }
    if (tab) {
      y_fail(p, lineno, indent + 1, "tab indentation");
      return false;
    }
    if (p->n_lines == cap) {
      yline_t* bigger;
      cap *= 2;
      bigger = (yline_t*)my_mem_realloc(p->allocator, p->lines,
                                        cap * sizeof(yline_t));
      if (bigger == NULL) {
        return false;
      }
      p->lines = bigger;
    }
    l = &p->lines[p->n_lines++];
    l->start = start;
    l->len = len;
    l->indent = indent;
    l->lineno = lineno++;
    /* blank: empty, spaces-only, or comment-only */
    l->blank = true;
    {
      size_t k;
      for (k = (size_t)indent; k < len; k++) {
        char c = p->s[start + k];
        if (c == '#') {
          break; /* comment to EOL */
        }
        if (c != ' ') {
          l->blank = false;
          break;
        }
      }
    }
  }
  return true;
}

/** @brief Next content (non-blank) line index >= p->i, or n_lines. */
static size_t y_next_content(yaml_p_t* p, size_t i) {
  while (i < p->n_lines && p->lines[i].blank) {
    i++;
  }
  return i;
}

/* ---------------- scalar / flow values ---------------- */

typedef struct yv_t {
  const my_allocator_t* allocator;
  const char* s;
  size_t len;
  size_t pos;
  yaml_p_t* p;      /**< for error reporting */
  int32_t lineno;
} yv_t;

static void yv_ws(yv_t* v) {
  while (v->pos < v->len && (v->s[v->pos] == ' ' || v->s[v->pos] == '\t')) {
    v->pos++;
  }
}

static int yv_peek(yv_t* v) {
  return v->pos < v->len ? (unsigned char)v->s[v->pos] : -1;
}

static my_conf_node_t* yv_value(yv_t* v);

/** @brief Double-quoted scalar with basic escapes. Owned. */
static char* yv_dq(yv_t* v) {
  size_t cap = 16, n = 0;
  char* out = (char*)my_mem_alloc(v->allocator, cap);
  if (out == NULL) {
    return NULL;
  }
  v->pos++; /* opening quote */
  for (;;) {
    int c = yv_peek(v);
    if (c < 0) {
      goto fail;
    }
    v->pos++;
    if (c == '"') {
      break;
    }
    if (c == '\\') {
      c = yv_peek(v);
      if (c < 0) {
        goto fail;
      }
      v->pos++;
      switch (c) {
        case 'n': c = '\n'; break;
        case 't': c = '\t'; break;
        case 'r': c = '\r'; break;
        case '"': case '\\': case '\'': break;
        case '0': c = '\0'; break;
        default:
          goto fail;
      }
    }
    if (n >= MY_CONF_YAML_MAX_SCALAR_BYTES) {
      goto fail;
    }
    if (n + 2 > cap) {
      char* b2;
      cap *= 2;
      b2 = (char*)my_mem_realloc(v->allocator, out, cap);
      if (b2 == NULL) {
        goto fail;
      }
      out = b2;
    }
    out[n++] = (char)c;
  }
  out[n] = '\0';
  return out;
fail:
  y_fail(v->p, v->lineno, 0, "double-quoted scalar exceeds resource budget or is invalid");
  my_mem_free(v->allocator, out);
  return NULL;
}

/** @brief Single-quoted scalar ('' -> '). Owned. */
static char* yv_sq(yv_t* v) {
  size_t cap = 16, n = 0;
  char* out = (char*)my_mem_alloc(v->allocator, cap);
  if (out == NULL) {
    return NULL;
  }
  v->pos++; /* opening quote */
  for (;;) {
    int c = yv_peek(v);
    if (c < 0) {
      goto fail;
    }
    v->pos++;
    if (c == '\'') {
      if (yv_peek(v) == '\'') { /* doubled quote */
        v->pos++;
      } else {
        break;
      }
    }
    if (n >= MY_CONF_YAML_MAX_SCALAR_BYTES) {
      goto fail;
    }
    if (n + 2 > cap) {
      char* b2;
      cap *= 2;
      b2 = (char*)my_mem_realloc(v->allocator, out, cap);
      if (b2 == NULL) {
        goto fail;
      }
      out = b2;
    }
    out[n++] = (char)c;
  }
  out[n] = '\0';
  return out;
fail:
  y_fail(v->p, v->lineno, 0, "single-quoted scalar exceeds resource budget or is invalid");
  my_mem_free(v->allocator, out);
  return NULL;
}

/** @brief Plain scalar: type-inferred node from a trimmed slice. */
static my_conf_node_t* yv_plain(yv_t* v, const char* s, size_t len) {
  if (len > MY_CONF_YAML_MAX_SCALAR_BYTES) {
    y_fail(v->p, v->lineno, 1, "YAML scalar exceeds resource budget");
    return NULL;
  }
  /* strip a trailing comment (" #" boundary) and trailing spaces */
  while (len > 0 && s[len - 1] == ' ') {
    len--;
  }
  {
    size_t k;
    for (k = 0; k + 1 < len; k++) {
      if (s[k] == ' ' && s[k + 1] == '#') {
        len = k; /* comment starts */
        while (len > 0 && s[len - 1] == ' ') {
          len--;
        }
        break;
      }
    }
  }
  if (len == 0 || (len == 1 && s[0] == '~') ||
      (len == 4 && strncmp(s, "null", 4) == 0) ||
      (len == 4 && strncmp(s, "Null", 4) == 0) ||
      (len == 4 && strncmp(s, "NULL", 4) == 0)) {
    return my_conf_new_null(v->allocator);
  }
  if ((len == 4 && strncmp(s, "true", 4) == 0) ||
      (len == 4 && strncmp(s, "True", 4) == 0)) {
    return my_conf_new_bool(v->allocator, true);
  }
  if ((len == 5 && strncmp(s, "false", 5) == 0) ||
      (len == 5 && strncmp(s, "False", 5) == 0)) {
    return my_conf_new_bool(v->allocator, false);
  }
  /* number? [+-]? digits [. digits] [eE ...] */
  {
    size_t k = 0;
    bool digits = false;
    bool dot = false;
    bool exp = false;
    if (k < len && (s[k] == '+' || s[k] == '-')) {
      k++;
    }
    while (k < len && s[k] >= '0' && s[k] <= '9') {
      k++;
      digits = true;
    }
    if (k < len && s[k] == '.') {
      dot = true;
      k++;
      while (k < len && s[k] >= '0' && s[k] <= '9') {
        k++;
        digits = true;
      }
    }
    if (k < len && (s[k] == 'e' || s[k] == 'E')) {
      exp = true;
      k++;
      if (k < len && (s[k] == '+' || s[k] == '-')) {
        k++;
      }
      while (k < len && s[k] >= '0' && s[k] <= '9') {
        k++;
        digits = true;
      }
    }
    if (digits && k == len) {
      char buf[64];
      if (len >= sizeof(buf)) {
        y_fail(v->p, v->lineno, 0, "number too long");
        return NULL;
      }
      memcpy(buf, s, len);
      buf[len] = '\0';
      if (dot || exp) {
        double d = strtod(buf, NULL);
        if (!isfinite(d)) {
          y_fail(v->p, v->lineno, 0, "number is not finite");
          return NULL;
        }
        return my_conf_new_double(v->allocator, d);
      }
      errno = 0;
      {
        long long iv = strtoll(buf, NULL, 10);
        if (errno == ERANGE) {
          double d = strtod(buf, NULL);
          if (!isfinite(d)) {
            y_fail(v->p, v->lineno, 0, "number is not finite");
            return NULL;
          }
          return my_conf_new_double(v->allocator, d);
        }
        return my_conf_new_int64(v->allocator, (int64_t)iv);
      }
    }
  }
  /* plain string */
  {
    char* out = (char*)my_mem_alloc(v->allocator, len + 1);
    my_conf_node_t* n;
    if (out == NULL) {
      return NULL;
    }
    memcpy(out, s, len);
    out[len] = '\0';
    n = my_conf_new_str(v->allocator, out);
    my_mem_free(v->allocator, out);
    return n;
  }
}

/** @brief Flow sequence [a, b] over the slice. */
static my_conf_node_t* yv_flow_seq(yv_t* v) {
  my_conf_node_t* arr = my_conf_new_array(v->allocator);
  if (v->p->flow_depth >= MY_CONF_YAML_MAX_DEPTH) {
    y_fail(v->p, v->lineno, 0, "YAML flow nesting depth exceeds resource budget");
    my_conf_destroy(arr);
    return NULL;
  }
  v->p->flow_depth++;
  if (arr == NULL) {
    v->p->flow_depth--;
    return NULL;
  }
  v->pos++; /* '[' */
  yv_ws(v);
  if (yv_peek(v) == ']') {
    v->pos++;
    v->p->flow_depth--;
    return arr;
  }
  for (;;) {
    my_conf_node_t* item;
    yv_ws(v);
    item = yv_value(v);
    if (item == NULL) {
      goto fail;
    }
    if (my_conf_child_count(arr) >= MY_CONF_YAML_MAX_CHILDREN) {
      my_conf_destroy(item);
      y_fail(v->p, v->lineno, 0, "YAML flow sequence exceeds resource budget");
      goto fail;
    }
    if (my_conf_array_push(arr, item) != MY_RET_OK) {
      my_conf_destroy(item);
      goto fail;
    }
    yv_ws(v);
    if (yv_peek(v) == ',') {
      v->pos++;
      continue;
    }
    if (yv_peek(v) == ']') {
      v->pos++;
      v->p->flow_depth--;
      return arr;
    }
    y_fail(v->p, v->lineno, 0, "expected ',' or ']' in flow sequence");
    goto fail;
  }
fail:
  v->p->flow_depth--;
  my_conf_destroy(arr);
  return NULL;
}

/** @brief Flow map {k: v, ...} over the slice. */
static my_conf_node_t* yv_flow_map(yv_t* v) {
  my_conf_node_t* obj = my_conf_new_object(v->allocator);
  if (v->p->flow_depth >= MY_CONF_YAML_MAX_DEPTH) {
    y_fail(v->p, v->lineno, 0, "YAML flow nesting depth exceeds resource budget");
    my_conf_destroy(obj);
    return NULL;
  }
  v->p->flow_depth++;
  if (obj == NULL) {
    v->p->flow_depth--;
    return NULL;
  }
  v->pos++; /* '{' */
  yv_ws(v);
  if (yv_peek(v) == '}') {
    v->pos++;
    v->p->flow_depth--;
    return obj;
  }
  for (;;) {
    size_t ks, ke;
    char* key;
    my_conf_node_t* val;
    yv_ws(v);
    ks = v->pos;
    /* key: plain until ':' (quoted keys supported too) */
    if (yv_peek(v) == '"' || yv_peek(v) == '\'') {
      int q = yv_peek(v);
      v->pos++;
      ks = v->pos;
      while (v->pos < v->len && v->s[v->pos] != q) {
        v->pos++;
      }
      if (v->pos >= v->len) {
        y_fail(v->p, v->lineno, 0, "unterminated quoted key in flow map");
        goto fail;
      }
      ke = v->pos;
      v->pos++;
    } else {
      while (v->pos < v->len && v->s[v->pos] != ':' && v->s[v->pos] != ',' &&
             v->s[v->pos] != '}') {
        v->pos++;
      }
      ke = v->pos;
      while (ke > ks && v->s[ke - 1] == ' ') {
        ke--;
      }
    }
    if (yv_peek(v) != ':') {
      y_fail(v->p, v->lineno, 0, "expected ':' in flow map");
      goto fail;
    }
    if (ke - ks > MY_CONF_YAML_MAX_SCALAR_BYTES) {
      y_fail(v->p, v->lineno, 0,
             "YAML flow map key exceeds resource budget");
      goto fail;
    }
    v->pos++;
    key = (char*)my_mem_alloc(v->allocator, ke - ks + 1);
    if (key == NULL) {
      goto fail;
    }
    memcpy(key, v->s + ks, ke - ks);
    key[ke - ks] = '\0';
    yv_ws(v);
    val = yv_value(v);
    if (val == NULL) {
      my_mem_free(v->allocator, key);
      goto fail;
    }
    if (my_conf_child_count(obj) >= MY_CONF_YAML_MAX_CHILDREN) {
      my_mem_free(v->allocator, key);
      my_conf_destroy(val);
      y_fail(v->p, v->lineno, 0, "YAML flow map exceeds resource budget");
      goto fail;
    }
    {
      size_t k;
      for (k = 0; k < my_conf_child_count(obj); k++) {
        my_conf_node_t* child = my_conf_child(obj, k);
        if (my_conf_key(child) != NULL &&
            strcmp(my_conf_key(child), key) == 0) {
          my_mem_free(v->allocator, key);
          my_conf_destroy(val);
          y_fail(v->p, v->lineno, 0, "duplicate key");
          goto fail;
        }
      }
    }
    if (my_conf_object_set(obj, key, val) != MY_RET_OK) {
      my_mem_free(v->allocator, key);
      my_conf_destroy(val);
      goto fail;
    }
    my_mem_free(v->allocator, key);
    yv_ws(v);
    if (yv_peek(v) == ',') {
      v->pos++;
      continue;
    }
    if (yv_peek(v) == '}') {
      v->pos++;
      v->p->flow_depth--;
      return obj;
    }
    y_fail(v->p, v->lineno, 0, "expected ',' or '}' in flow map");
    goto fail;
  }
fail:
  v->p->flow_depth--;
  my_conf_destroy(obj);
  return NULL;
}

/** @brief One flow/block-inline value over the slice. */
static my_conf_node_t* yv_value(yv_t* v) {
  int c;
  yv_ws(v);
  c = yv_peek(v);
  if (c < 0 || c == '#') {
    return my_conf_new_null(v->allocator);
  }
  if (c == '[') {
    return yv_flow_seq(v);
  }
  if (c == '{') {
    return yv_flow_map(v);
  }
  if (c == '"') {
    char* s = yv_dq(v);
    my_conf_node_t* n;
    if (s == NULL) {
      return NULL;
    }
    n = my_conf_new_str(v->allocator, s);
    my_mem_free(v->allocator, s);
    return n;
  }
  if (c == '\'') {
    char* s = yv_sq(v);
    my_conf_node_t* n;
    if (s == NULL) {
      return NULL;
    }
    n = my_conf_new_str(v->allocator, s);
    my_mem_free(v->allocator, s);
    return n;
  }
  if (c == '&' || c == '!') {
    y_fail(v->p, v->lineno, 0, "anchors/tags not supported");
    return NULL;
  }
  if (c == '>' || c == '|') {
    y_fail(v->p, v->lineno, 0, "folded/literal scalars not supported");
    return NULL;
  }
  /* plain scalar: to the end of the slice (flow callers bound it) */
  {
    size_t start = v->pos;
    while (v->pos < v->len && v->s[v->pos] != ',' && v->s[v->pos] != ']' &&
           v->s[v->pos] != '}') {
      v->pos++;
    }
    return yv_plain(v, v->s + start, v->pos - start);
  }
}

/** @brief Value of a block-level "key: value" rest slice. */
static my_conf_node_t* y_block_value(yaml_p_t* p, const char* s, size_t len,
                                     int32_t lineno) {
  yv_t v;
  my_conf_node_t* n;
  memset(&v, 0, sizeof(v));
  v.allocator = p->allocator;
  v.s = s;
  v.len = len;
  v.p = p;
  v.lineno = lineno;
  n = yv_value(&v);
  if (n == NULL) {
    return NULL;
  }
  return n;
}

/* ---------------- block parser ---------------- */

static my_conf_node_t* y_block(yaml_p_t* p, int32_t indent);
static my_conf_node_t* y_block_impl(yaml_p_t* p, int32_t indent);

/** @brief Does the slice look like "key:" / "key: value"? The colon
 * must be followed by a space or the end (URLs etc. stay plain). */
static bool y_is_pair(const char* s, size_t len, size_t* colon_at) {
  size_t k;
  if (len > 0 && (s[0] == '"' || s[0] == '\'')) {
    /* quoted key: find the closing quote, then ':' */
    char q = s[0];
    for (k = 1; k < len; k++) {
      if (s[k] == q) {
        if (k + 1 < len && s[k + 1] == ':') {
          *colon_at = k + 1;
          return true;
        }
        return false;
      }
    }
    return false;
  }
  for (k = 0; k < len; k++) {
    if (s[k] == ':' && (k + 1 == len || s[k + 1] == ' ')) {
      *colon_at = k;
      return true;
    }
    if (s[k] == '#') {
      return false;
    }
  }
  return false;
}

/** @brief Parse one pair's key (strip quotes) from the slice. */
static char* y_pair_key(yaml_p_t* p, const char* s, size_t len,
                        size_t colon_at, int32_t lineno) {
  size_t ks = 0, ke = colon_at;
  char* out;
  (void)len;
  if (s[0] == '"' || s[0] == '\'') {
    ks = 1;
    ke = colon_at - 1; /* closing quote */
  }
  while (ke > ks && s[ke - 1] == ' ') {
    ke--;
  }
  if (ke == ks) {
    y_fail(p, lineno, 0, "empty key");
    return NULL;
  }
  if (ke - ks > MY_CONF_YAML_MAX_SCALAR_BYTES) {
    y_fail(p, lineno, 0, "YAML mapping key exceeds resource budget");
    return NULL;
  }
  out = (char*)my_mem_alloc(p->allocator, ke - ks + 1);
  if (out == NULL) {
    return NULL;
  }
  memcpy(out, s + ks, ke - ks);
  out[ke - ks] = '\0';
  return out;
}

/** @brief Mapping block at `indent`. */
static my_conf_node_t* y_map(yaml_p_t* p, int32_t indent) {
  my_conf_node_t* obj = my_conf_new_object(p->allocator);
  if (obj == NULL) {
    return NULL;
  }
  for (;;) {
    size_t ci = y_next_content(p, p->i);
    yline_t* l;
    const char* text;
    size_t tlen;
    size_t colon = 0;
    char* key;
    my_conf_node_t* val;
    size_t vstart, vlen;
    if (ci >= p->n_lines) {
      break;
    }
    l = &p->lines[ci];
    if (l->indent < indent) {
      break; /* belongs to an outer level */
    }
    if (l->indent > indent) {
      y_fail(p, l->lineno, l->indent + 1, "inconsistent indentation");
      goto fail;
    }
    text = p->s + l->start + l->indent;
    tlen = l->len - (size_t)l->indent;
    if (tlen > 0 && text[0] == '-') {
      break; /* a sequence starts at this level: caller handles */
    }
    if (!y_is_pair(text, tlen, &colon)) {
      y_fail(p, l->lineno, l->indent + 1, "expected 'key:' pair");
      goto fail;
    }
    key = y_pair_key(p, text, tlen, colon, l->lineno);
    if (key == NULL) {
      goto fail;
    }
    vstart = colon + 1;
    while (vstart < tlen && text[vstart] == ' ') {
      vstart++;
    }
    vlen = tlen - vstart;
    p->i = ci + 1;
    if (vlen == 0) {
      /* nested block or NULL */
      size_t ni = y_next_content(p, p->i);
      if (ni < p->n_lines && p->lines[ni].indent > indent) {
        val = y_block(p, p->lines[ni].indent);
        if (val == NULL) {
          my_mem_free(p->allocator, key);
          goto fail;
        }
      } else {
        val = my_conf_new_null(p->allocator);
        if (val == NULL) {
          my_mem_free(p->allocator, key);
          goto fail;
        }
      }
    } else {
      val = y_block_value(p, text + vstart, vlen, l->lineno);
      if (val == NULL) {
        my_mem_free(p->allocator, key);
        goto fail;
      }
    }
    /* duplicate key check */
    {
      size_t k, n = my_conf_child_count(obj);
      bool dup = false;
      for (k = 0; k < n; k++) {
        my_conf_node_t* cc = my_conf_child(obj, k);
        if (my_conf_key(cc) != NULL && strcmp(my_conf_key(cc), key) == 0) {
          dup = true;
          break;
        }
      }
      if (dup) {
        y_fail(p, l->lineno, l->indent + 1, "duplicate key");
        my_mem_free(p->allocator, key);
        my_conf_destroy(val);
        goto fail;
      }
    }
    if (my_conf_child_count(obj) >= MY_CONF_YAML_MAX_CHILDREN) {
      y_fail(p, l->lineno, l->indent + 1,
             "YAML mapping size exceeds resource budget");
      my_mem_free(p->allocator, key);
      my_conf_destroy(val);
      goto fail;
    }
    if (my_conf_object_set(obj, key, val) != MY_RET_OK) {
      my_mem_free(p->allocator, key);
      my_conf_destroy(val);
      goto fail;
    }
    my_mem_free(p->allocator, key);
  }
  return obj;
fail:
  my_conf_destroy(obj);
  return NULL;
}

/** @brief Sequence block at `indent` ("- item" lines). */
static my_conf_node_t* y_seq(yaml_p_t* p, int32_t indent) {
  my_conf_node_t* arr = my_conf_new_array(p->allocator);
  if (arr == NULL) {
    return NULL;
  }
  for (;;) {
    size_t ci = y_next_content(p, p->i);
    yline_t* l;
    const char* text;
    size_t tlen;
    my_conf_node_t* val = NULL;
    size_t rstart, rlen;
    if (ci >= p->n_lines) {
      break;
    }
    l = &p->lines[ci];
    if (l->indent < indent) {
      break;
    }
    if (l->indent > indent) {
      y_fail(p, l->lineno, l->indent + 1, "inconsistent indentation");
      goto fail;
    }
    text = p->s + l->start + l->indent;
    tlen = l->len - (size_t)l->indent;
    if (!(tlen >= 1 && text[0] == '-' &&
          (tlen == 1 || text[1] == ' '))) {
      break; /* not a sequence item at this level */
    }
    rstart = tlen > 1 ? 2 : 1;
    rlen = tlen - rstart;
    while (rlen > 0 && text[rstart] == ' ') {
      rstart++;
      rlen--;
    }
    p->i = ci + 1;
    if (rlen == 0) {
      /* nested block or null item */
      size_t ni = y_next_content(p, p->i);
      if (ni < p->n_lines && p->lines[ni].indent > indent) {
        val = y_block(p, p->lines[ni].indent);
      } else {
        val = my_conf_new_null(p->allocator);
      }
      if (val == NULL) {
        goto fail;
      }
    } else {
      /* "- key: value" starts an inline map; more pairs follow at
       * indent+2 */
      size_t colon = 0;
      if (y_is_pair(text + rstart, rlen, &colon) &&
          text[rstart] != '[' && text[rstart] != '{') {
        int32_t map_indent = indent + 2;
        my_conf_node_t* m = my_conf_new_object(p->allocator);
        char* key;
        my_conf_node_t* mv;
        size_t vstart, vlen;
        if (m == NULL) {
          goto fail;
        }
        /* first pair inline */
        key = y_pair_key(p, text + rstart, rlen, colon, l->lineno);
        if (key == NULL) {
          my_conf_destroy(m);
          goto fail;
        }
        vstart = rstart + colon + 1;
        while (vstart < tlen && text[vstart] == ' ') {
          vstart++;
        }
        vlen = tlen - vstart;
        if (vlen == 0) {
          size_t ni = y_next_content(p, p->i);
          if (ni < p->n_lines && p->lines[ni].indent > map_indent - 2) {
            mv = y_block(p, p->lines[ni].indent);
          } else {
            mv = my_conf_new_null(p->allocator);
          }
        } else {
          mv = y_block_value(p, text + vstart, vlen, l->lineno);
        }
        if (mv == NULL) {
          my_mem_free(p->allocator, key);
          if (mv != NULL) {
            my_conf_destroy(mv);
          }
          my_conf_destroy(m);
          goto fail;
        }
        if (my_conf_child_count(m) >= MY_CONF_YAML_MAX_CHILDREN) {
          y_fail(p, l->lineno, l->indent + 1,
                 "YAML inline mapping size exceeds resource budget");
          my_mem_free(p->allocator, key);
          my_conf_destroy(mv);
          my_conf_destroy(m);
          goto fail;
        }
        {
          size_t k;
          for (k = 0; k < my_conf_child_count(m); k++) {
            my_conf_node_t* child = my_conf_child(m, k);
            if (my_conf_key(child) != NULL &&
                strcmp(my_conf_key(child), key) == 0) {
              y_fail(p, l->lineno, l->indent + 1, "duplicate key");
              my_mem_free(p->allocator, key);
              my_conf_destroy(mv);
              my_conf_destroy(m);
              goto fail;
            }
          }
        }
        if (my_conf_object_set(m, key, mv) != MY_RET_OK) {
          my_mem_free(p->allocator, key);
          my_conf_destroy(mv);
          my_conf_destroy(m);
          goto fail;
        }
        my_mem_free(p->allocator, key);
        /* following pairs at map_indent belong to the same map */
        for (;;) {
          size_t pi = y_next_content(p, p->i);
          yline_t* pl;
          const char* pt;
          size_t ptlen;
          size_t pc = 0;
          if (pi >= p->n_lines) {
            break;
          }
          pl = &p->lines[pi];
          if (pl->indent != map_indent) {
            if (pl->indent > map_indent) {
              y_fail(p, pl->lineno, pl->indent + 1,
                     "inconsistent indentation");
              my_conf_destroy(m);
              goto fail;
            }
            break;
          }
          pt = p->s + pl->start + pl->indent;
          ptlen = pl->len - (size_t)pl->indent;
          if (ptlen > 0 && pt[0] == '-') {
            break;
          }
          if (!y_is_pair(pt, ptlen, &pc)) {
            y_fail(p, pl->lineno, pl->indent + 1, "expected 'key:' pair");
            my_conf_destroy(m);
            goto fail;
          }
          key = y_pair_key(p, pt, ptlen, pc, pl->lineno);
          if (key == NULL) {
            my_conf_destroy(m);
            goto fail;
          }
          {
            size_t vs = pc + 1;
            size_t vl;
            while (vs < ptlen && pt[vs] == ' ') {
              vs++;
            }
            vl = ptlen - vs;
            p->i = pi + 1;
            if (vl == 0) {
              size_t ni = y_next_content(p, p->i);
              if (ni < p->n_lines && p->lines[ni].indent > map_indent) {
                mv = y_block(p, p->lines[ni].indent);
              } else {
                mv = my_conf_new_null(p->allocator);
              }
            } else {
              mv = y_block_value(p, pt + vs, vl, pl->lineno);
            }
          }
          if (mv == NULL) {
            my_mem_free(p->allocator, key);
            if (mv != NULL) {
              my_conf_destroy(mv);
            }
            my_conf_destroy(m);
            goto fail;
          }
          if (my_conf_child_count(m) >= MY_CONF_YAML_MAX_CHILDREN) {
            y_fail(p, pl->lineno, pl->indent + 1,
                   "YAML inline mapping size exceeds resource budget");
            my_mem_free(p->allocator, key);
            my_conf_destroy(mv);
            my_conf_destroy(m);
            goto fail;
          }
          {
            size_t k;
            for (k = 0; k < my_conf_child_count(m); k++) {
              my_conf_node_t* child = my_conf_child(m, k);
              if (my_conf_key(child) != NULL &&
                  strcmp(my_conf_key(child), key) == 0) {
                y_fail(p, pl->lineno, pl->indent + 1, "duplicate key");
                my_mem_free(p->allocator, key);
                my_conf_destroy(mv);
                my_conf_destroy(m);
                goto fail;
              }
            }
          }
          if (my_conf_object_set(m, key, mv) != MY_RET_OK) {
            my_mem_free(p->allocator, key);
            my_conf_destroy(mv);
            my_conf_destroy(m);
            goto fail;
          }
          my_mem_free(p->allocator, key);
        }
        val = m;
      } else {
        val = y_block_value(p, text + rstart, rlen, l->lineno);
        if (val == NULL) {
          goto fail;
        }
      }
    }
    if (my_conf_child_count(arr) >= MY_CONF_YAML_MAX_CHILDREN) {
      y_fail(p, l->lineno, l->indent + 1,
             "YAML sequence size exceeds resource budget");
      my_conf_destroy(val);
      goto fail;
    }
    if (my_conf_array_push(arr, val) != MY_RET_OK) {
      my_conf_destroy(val);
      goto fail;
    }
  }
  return arr;
fail:
  my_conf_destroy(arr);
  return NULL;
}

/** @brief Block dispatcher: sequence vs mapping vs error. */
static my_conf_node_t* y_block_impl(yaml_p_t* p, int32_t indent) {
  size_t ci = y_next_content(p, p->i);
  yline_t* l;
  const char* text;
  size_t tlen;
  if (ci >= p->n_lines) {
    return NULL; /* caller treats as missing */
  }
  l = &p->lines[ci];
  text = p->s + l->start + l->indent;
  tlen = l->len - (size_t)l->indent;
  if (tlen >= 1 && text[0] == '-' && (tlen == 1 || text[1] == ' ')) {
    return y_seq(p, indent);
  }
  return y_map(p, indent);
}

static my_conf_node_t* y_block(yaml_p_t* p, int32_t indent) {
  my_conf_node_t* result;
  if (p->block_depth >= MY_CONF_YAML_MAX_DEPTH) {
    y_fail(p, p->i < p->n_lines ? p->lines[p->i].lineno : 1, indent + 1,
           "YAML nesting depth exceeds resource budget");
    return NULL;
  }
  p->block_depth++;
  result = y_block_impl(p, indent);
  p->block_depth--;
  return result;
}

my_conf_node_t* my_conf_parse_yaml(const my_allocator_t* allocator,
                                   const char* data, size_t len,
                                   my_conf_error_t* err) {
  yaml_p_t p;
  my_conf_node_t* root = NULL;
  size_t first;
  if (err != NULL) {
    memset(err, 0, sizeof(*err));
  }
  if (data == NULL) {
    return NULL;
  }
  memset(&p, 0, sizeof(p));
  p.allocator = allocator;
  p.s = data;
  p.len = len;
  p.err = err;
  if (!y_split(&p)) {
    my_mem_free(allocator, p.lines);
    return NULL;
  }
  /* multi-document marker: hard error (documented) */
  first = y_next_content(&p, 0);
  if (first < p.n_lines) {
    const char* t = p.s + p.lines[first].start + p.lines[first].indent;
    size_t tl = p.lines[first].len - (size_t)p.lines[first].indent;
    if (tl >= 3 && strncmp(t, "---", 3) == 0) {
      y_fail(&p, p.lines[first].lineno, 1,
             "multi-document (---) not supported");
    }
  }
  if (!y_failed(&p)) {
    p.i = 0;
    first = y_next_content(&p, 0);
    if (first < p.n_lines) {
      root = y_block(&p, p.lines[first].indent);
    } else {
      root = my_conf_new_null(allocator); /* empty doc */
    }
    /* trailing content must not remain */
    if (root != NULL && y_next_content(&p, p.i) < p.n_lines && !y_failed(&p)) {
      yline_t* l = &p.lines[y_next_content(&p, p.i)];
      y_fail(&p, l->lineno, l->indent + 1, "trailing content");
      my_conf_destroy(root);
      root = NULL;
    }
  }
  if (y_failed(&p)) {
    my_conf_destroy(root);
    root = NULL;
  }
  my_mem_free(allocator, p.lines);
  return root;
}
