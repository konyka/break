/**
 * @file my_conf_bson.c
 * @brief BSON codec (M17a): strict little-endian document parser
 * (lengths validated, no out-of-bounds reads, nesting capped) and a
 * writer for the full tree (object/array/string/int64/double/bool/
 * null; INT64 in int32 range written as 0x10, else 0x12).
 *
 * Read type mapping: 0x01 double, 0x02 utf8, 0x03 object, 0x04 array
 * (element keys ignored — order is positional), 0x07 objectId (24 hex
 * chars STR), 0x08 bool, 0x09 datetime (INT64 milliseconds), 0x0A null,
 * 0x10 int32 -> INT64, 0x12 int64 -> INT64. Any other element type is
 * an ERROR (data integrity over leniency).
 */
#include "myc/myconf/my_conf.h"

#include <string.h>

#define BSON_MAX_DEPTH 64

/* ---------------- reader ---------------- */

typedef struct bson_r_t {
  const my_allocator_t* allocator;
  const uint8_t* data;
  size_t len;
  size_t pos;
  int depth;
  my_conf_error_t* err;
} bson_r_t;

static void bson_fail(bson_r_t* r, const char* msg) {
  if (r->err != NULL && r->err->msg[0] == '\0') {
    r->err->line = 0;
    r->err->col = 0;
    r->err->offset = (int64_t)r->pos;
    snprintf(r->err->msg, sizeof(r->err->msg), "%s", msg);
  }
}

/** @brief Read n raw bytes (bounds-checked). */
static const uint8_t* bson_take(bson_r_t* r, size_t n, const char* msg) {
  const uint8_t* p;
  if (r->pos + n > r->len) {
    bson_fail(r, msg);
    return NULL;
  }
  p = r->data + r->pos;
  r->pos += n;
  return p;
}

static int32_t bson_i32(const uint8_t* p) {
  return (int32_t)((uint32_t)p[0] | ((uint32_t)p[1] << 8) |
                   ((uint32_t)p[2] << 16) | ((uint32_t)p[3] << 24));
}

static int64_t bson_i64(const uint8_t* p) {
  uint64_t lo = (uint32_t)bson_i32(p);
  uint64_t hi = (uint32_t)bson_i32(p + 4);
  return (int64_t)(lo | (hi << 32));
}

static double bson_f64(const uint8_t* p) {
  uint64_t u = (uint64_t)bson_i64(p);
  double d;
  memcpy(&d, &u, 8);
  return d;
}

/** @brief element name: NUL-terminated, bounds-checked. */
static const char* bson_cstr(bson_r_t* r, size_t* out_len) {
  size_t start = r->pos;
  while (r->pos < r->len && r->data[r->pos] != 0) {
    r->pos++;
  }
  if (r->pos >= r->len) {
    bson_fail(r, "unterminated cstring");
    return NULL;
  }
  *out_len = r->pos - start;
  r->pos++; /* the NUL */
  return (const char*)r->data + start;
}

static my_conf_node_t* bson_document(bson_r_t* r, bool as_array);

/** @brief objectId -> 24 lowercase hex chars (owned). */
static char* bson_oid_hex(bson_r_t* r, const uint8_t* p) {
  static const char HEX[] = "0123456789abcdef";
  char* s = (char*)my_mem_alloc(r->allocator, 25);
  int i;
  if (s == NULL) {
    bson_fail(r, "oom");
    return NULL;
  }
  for (i = 0; i < 12; i++) {
    s[i * 2] = HEX[p[i] >> 4];
    s[i * 2 + 1] = HEX[p[i] & 0xF];
  }
  s[24] = '\0';
  return s;
}

/** @brief One element -> node (name consumed by the caller). */
static my_conf_node_t* bson_element(bson_r_t* r, uint8_t type) {
  const uint8_t* p;
  switch (type) {
    case 0x01: /* double */
      p = bson_take(r, 8, "truncated double");
      return p != NULL ? my_conf_new_double(r->allocator, bson_f64(p))
                       : NULL;
    case 0x02: { /* utf8 string */
      int32_t slen;
      char* copy;
      p = bson_take(r, 4, "truncated string length");
      if (p == NULL) {
        return NULL;
      }
      slen = bson_i32(p);
      if (slen <= 0 || (size_t)slen > r->len - r->pos) {
        bson_fail(r, "bad string length");
        return NULL;
      }
      p = bson_take(r, (size_t)slen, "truncated string");
      if (p == NULL || p[slen - 1] != 0) {
        bson_fail(r, "string missing NUL");
        return NULL;
      }
      copy = (char*)my_mem_alloc(r->allocator, (size_t)slen);
      if (copy == NULL) {
        bson_fail(r, "oom");
        return NULL;
      }
      memcpy(copy, p, (size_t)slen - 1);
      copy[slen - 1] = '\0';
      {
        my_conf_node_t* n = my_conf_new_str(r->allocator, copy);
        my_mem_free(r->allocator, copy);
        return n;
      }
    }
    case 0x03: /* embedded document */
      return bson_document(r, false);
    case 0x04: /* array (keys are positional; content is the truth) */
      return bson_document(r, true);
    case 0x07: { /* objectId */
      char* hex;
      my_conf_node_t* n;
      p = bson_take(r, 12, "truncated objectId");
      if (p == NULL) {
        return NULL;
      }
      hex = bson_oid_hex(r, p);
      if (hex == NULL) {
        return NULL;
      }
      n = my_conf_new_str(r->allocator, hex);
      my_mem_free(r->allocator, hex);
      return n;
    }
    case 0x08: { /* bool */
      p = bson_take(r, 1, "truncated bool");
      if (p == NULL) {
        return NULL;
      }
      if (p[0] > 1) {
        bson_fail(r, "bad bool value");
        return NULL;
      }
      return my_conf_new_bool(r->allocator, p[0] != 0);
    }
    case 0x09: /* datetime: int64 ms -> INT64 (noted in the header) */
      p = bson_take(r, 8, "truncated datetime");
      return p != NULL ? my_conf_new_int64(r->allocator, bson_i64(p)) : NULL;
    case 0x0A: /* null */
      return my_conf_new_null(r->allocator);
    case 0x10: /* int32 -> INT64 */
      p = bson_take(r, 4, "truncated int32");
      return p != NULL ? my_conf_new_int64(r->allocator, bson_i32(p)) : NULL;
    case 0x12: /* int64 */
      p = bson_take(r, 8, "truncated int64");
      return p != NULL ? my_conf_new_int64(r->allocator, bson_i64(p)) : NULL;
    default:
      bson_fail(r, "unsupported bson element type");
      return NULL;
  }
}

static my_conf_node_t* bson_document(bson_r_t* r, bool as_array) {
  my_conf_node_t* doc;
  int32_t doc_len;
  size_t end;
  const uint8_t* p;
  if (r->depth >= BSON_MAX_DEPTH) {
    bson_fail(r, "nesting too deep");
    return NULL;
  }
  p = bson_take(r, 4, "truncated document length");
  if (p == NULL) {
    return NULL;
  }
  doc_len = bson_i32(p);
  if (doc_len < 5 || r->pos - 4 + (size_t)doc_len > r->len) {
    bson_fail(r, "inconsistent document length");
    return NULL;
  }
  end = r->pos - 4 + (size_t)doc_len - 1; /* position of the terminator */
  doc = as_array ? my_conf_new_array(r->allocator)
                 : my_conf_new_object(r->allocator);
  if (doc == NULL) {
    bson_fail(r, "oom");
    return NULL;
  }
  r->depth++;
  while (r->pos < end) {
    const uint8_t* tp = bson_take(r, 1, "truncated element type");
    const char* name;
    size_t name_len;
    my_conf_node_t* val;
    my_ret_t ret;
    if (tp == NULL) {
      goto fail;
    }
    name = bson_cstr(r, &name_len);
    if (name == NULL) {
      goto fail;
    }
    val = bson_element(r, *tp);
    if (val == NULL) {
      goto fail;
    }
    /* arrays: ignore the "0","1",.. keys (positional order rules) */
    if (as_array) {
      ret = my_conf_array_push(doc, val);
    } else {
      char* key = (char*)my_mem_alloc(r->allocator, name_len + 1);
      if (key == NULL) {
        my_conf_destroy(val);
        bson_fail(r, "oom");
        goto fail;
      }
      memcpy(key, name, name_len);
      key[name_len] = '\0';
      ret = my_conf_object_set(doc, key, val);
      my_mem_free(r->allocator, key);
    }
    if (ret != MY_RET_OK) {
      my_conf_destroy(val);
      bson_fail(r, "oom");
      goto fail;
    }
  }
  r->depth--;
  if (r->pos != end || r->data[r->pos] != 0) {
    bson_fail(r, "document missing terminator");
    goto fail;
  }
  r->pos++; /* the terminator */
  return doc;
fail:
  r->depth--;
  my_conf_destroy(doc);
  return NULL;
}

my_conf_node_t* my_conf_parse_bson(const my_allocator_t* allocator,
                                   const uint8_t* data, size_t len,
                                   my_conf_error_t* err) {
  bson_r_t r;
  my_conf_node_t* root;
  if (err != NULL) {
    memset(err, 0, sizeof(*err));
  }
  if (data == NULL) {
    return NULL;
  }
  memset(&r, 0, sizeof(r));
  r.allocator = allocator;
  r.data = data;
  r.len = len;
  r.err = err;
  root = bson_document(&r, false);
  if (root == NULL) {
    return NULL;
  }
  if (r.pos != len) {
    bson_fail(&r, "trailing garbage");
    my_conf_destroy(root);
    return NULL;
  }
  return root;
}

/* ---------------- writer ---------------- */

typedef struct bson_w_t {
  const my_allocator_t* allocator;
  uint8_t* buf;
  size_t len;
  size_t cap;
  bool oom;
} bson_w_t;

static void bw_raw(bson_w_t* w, const void* p, size_t n) {
  if (w->oom) {
    return;
  }
  if (w->len + n > w->cap) {
    uint8_t* bigger;
    while (w->len + n > w->cap) {
      w->cap *= 2;
    }
    bigger = (uint8_t*)my_mem_realloc(w->allocator, w->buf, w->cap);
    if (bigger == NULL) {
      w->oom = true;
      return;
    }
    w->buf = bigger;
  }
  memcpy(w->buf + w->len, p, n);
  w->len += n;
}

static void bw_u8(bson_w_t* w, uint8_t v) {
  bw_raw(w, &v, 1);
}

static void bw_i32(bson_w_t* w, int32_t v) {
  uint8_t b[4] = {(uint8_t)v, (uint8_t)(v >> 8), (uint8_t)(v >> 16),
                  (uint8_t)(v >> 24)};
  bw_raw(w, b, 4);
}

static void bw_i64(bson_w_t* w, int64_t v) {
  bw_i32(w, (int32_t)(uint32_t)(uint64_t)v);
  bw_i32(w, (int32_t)(uint32_t)((uint64_t)v >> 32));
}

static void bw_f64(bson_w_t* w, double d) {
  uint64_t u;
  memcpy(&u, &d, 8);
  bw_i64(w, (int64_t)u);
}

/** @brief Write a document; returns its start offset (length patched
 * in afterwards). */
static size_t bw_document(bson_w_t* w, my_conf_node_t* node) {
  size_t start = w->len;
  size_t i, n;
  bool as_array = my_conf_type(node) == MY_CONF_ARRAY;
  bw_i32(w, 0); /* length placeholder */
  n = my_conf_child_count(node);
  for (i = 0; i < n; i++) {
    my_conf_node_t* c = my_conf_child(node, i);
    char idx[24];
    const char* key;
    switch (my_conf_type(c)) {
      case MY_CONF_DOUBLE: bw_u8(w, 0x01); break;
      case MY_CONF_STR: bw_u8(w, 0x02); break;
      case MY_CONF_OBJECT: bw_u8(w, 0x03); break;
      case MY_CONF_ARRAY: bw_u8(w, 0x04); break;
      case MY_CONF_BOOL: bw_u8(w, 0x08); break;
      case MY_CONF_NULL: bw_u8(w, 0x0A); break;
      case MY_CONF_INT64:
        /* int32 range -> 0x10, else 0x12 */
        bw_u8(w, my_conf_as_int64(c, 0) >= INT32_MIN &&
                         my_conf_as_int64(c, 0) <= INT32_MAX
                     ? (uint8_t)0x10
                     : (uint8_t)0x12);
        break;
      default:
        continue;
    }
    /* e-name: object key or the array index as text */
    if (as_array) {
      snprintf(idx, sizeof(idx), "%zu", i);
      key = idx;
    } else {
      key = my_conf_key(c);
      if (key == NULL) {
        key = "";
      }
    }
    bw_raw(w, key, strlen(key) + 1);
    switch (my_conf_type(c)) {
      case MY_CONF_DOUBLE:
        bw_f64(w, my_conf_as_double(c, 0.0));
        break;
      case MY_CONF_STR: {
        const char* s = my_conf_as_str(c, "");
        bw_i32(w, (int32_t)strlen(s) + 1);
        bw_raw(w, s, strlen(s) + 1);
        break;
      }
      case MY_CONF_OBJECT:
      case MY_CONF_ARRAY:
        bw_document(w, c);
        break;
      case MY_CONF_BOOL:
        bw_u8(w, my_conf_as_bool(c, false) ? 1 : 0);
        break;
      case MY_CONF_NULL:
        break;
      case MY_CONF_INT64:
        if (my_conf_as_int64(c, 0) >= INT32_MIN &&
            my_conf_as_int64(c, 0) <= INT32_MAX) {
          bw_i32(w, (int32_t)my_conf_as_int64(c, 0));
        } else {
          bw_i64(w, my_conf_as_int64(c, 0));
        }
        break;
      default:
        break;
    }
  }
  bw_u8(w, 0);
  /* patch the length */
  if (!w->oom) {
    int32_t total = (int32_t)(w->len - start);
    w->buf[start + 0] = (uint8_t)total;
    w->buf[start + 1] = (uint8_t)(total >> 8);
    w->buf[start + 2] = (uint8_t)(total >> 16);
    w->buf[start + 3] = (uint8_t)(total >> 24);
  }
  return start;
}

uint8_t* my_conf_to_bson(const my_allocator_t* allocator,
                         my_conf_node_t* node, size_t* out_len) {
  bson_w_t w;
  if (node == NULL || out_len == NULL ||
      my_conf_type(node) != MY_CONF_OBJECT) {
    return NULL;
  }
  memset(&w, 0, sizeof(w));
  w.allocator = allocator;
  w.cap = 256;
  w.buf = (uint8_t*)my_mem_alloc(allocator, w.cap);
  if (w.buf == NULL) {
    return NULL;
  }
  bw_document(&w, node);
  if (w.oom) {
    my_mem_free(allocator, w.buf);
    return NULL;
  }
  *out_len = w.len;
  return w.buf;
}
