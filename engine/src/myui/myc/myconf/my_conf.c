/**
 * @file my_conf.c
 * @brief Configuration document tree (M17a): nodes, building, dot-path
 * queries, JSON file io.
 */
#include "myc/myconf/my_conf.h"

#include <stdio.h>
#include <string.h>

#include "myc/my_darray.h"
#include "myc/my_str.h"

struct my_conf_node_t {
  const my_allocator_t* allocator;
  my_conf_type_t type;
  char* key;      /**< owned: key inside the parent object */
  int64_t i;      /**< INT64 */
  double d;       /**< DOUBLE */
  bool b;         /**< BOOL */
  char* str;      /**< owned: STR */
  my_darray_t* children; /**< OBJECT/ARRAY: my_conf_node_t* (owned) */
};

static my_conf_node_t* node_new(const my_allocator_t* allocator,
                                my_conf_type_t type) {
  my_conf_node_t* n =
      (my_conf_node_t*)my_mem_calloc(allocator, 1, sizeof(my_conf_node_t));
  if (n == NULL) {
    return NULL;
  }
  n->allocator = allocator;
  n->type = type;
  return n;
}

my_conf_node_t* my_conf_new_null(const my_allocator_t* allocator) {
  return node_new(allocator, MY_CONF_NULL);
}

my_conf_node_t* my_conf_new_object(const my_allocator_t* allocator) {
  my_conf_node_t* n = node_new(allocator, MY_CONF_OBJECT);
  if (n != NULL) {
    n->children = my_darray_create(allocator, 0);
    if (n->children == NULL) {
      my_mem_free(allocator, n);
      return NULL;
    }
  }
  return n;
}

my_conf_node_t* my_conf_new_array(const my_allocator_t* allocator) {
  my_conf_node_t* n = node_new(allocator, MY_CONF_ARRAY);
  if (n != NULL) {
    n->children = my_darray_create(allocator, 0);
    if (n->children == NULL) {
      my_mem_free(allocator, n);
      return NULL;
    }
  }
  return n;
}

my_conf_node_t* my_conf_new_int64(const my_allocator_t* allocator,
                                  int64_t v) {
  my_conf_node_t* n = node_new(allocator, MY_CONF_INT64);
  if (n != NULL) {
    n->i = v;
  }
  return n;
}

my_conf_node_t* my_conf_new_double(const my_allocator_t* allocator,
                                   double v) {
  my_conf_node_t* n = node_new(allocator, MY_CONF_DOUBLE);
  if (n != NULL) {
    n->d = v;
  }
  return n;
}

my_conf_node_t* my_conf_new_bool(const my_allocator_t* allocator, bool v) {
  my_conf_node_t* n = node_new(allocator, MY_CONF_BOOL);
  if (n != NULL) {
    n->b = v;
  }
  return n;
}

my_conf_node_t* my_conf_new_str(const my_allocator_t* allocator,
                                const char* v) {
  my_conf_node_t* n = node_new(allocator, MY_CONF_STR);
  if (n != NULL) {
    n->str = my_strdup(allocator, v);
    if (v != NULL && n->str == NULL) {
      my_mem_free(allocator, n);
      return NULL;
    }
  }
  return n;
}

void my_conf_destroy(my_conf_node_t* node) {
  size_t i, n;
  if (node == NULL) {
    return;
  }
  if (node->children != NULL) {
    n = my_darray_size(node->children);
    for (i = 0; i < n; i++) {
      my_conf_destroy((my_conf_node_t*)my_darray_get(node->children, i));
    }
    my_darray_destroy(node->children);
  }
  my_mem_free(node->allocator, node->key);
  my_mem_free(node->allocator, node->str);
  my_mem_free(node->allocator, node);
}

/* ---------------- structure ---------------- */

my_ret_t my_conf_object_set(my_conf_node_t* node, const char* key,
                            my_conf_node_t* child) {
  size_t i, n;
  char* copy;
  if (node == NULL || key == NULL || child == NULL ||
      node->type != MY_CONF_OBJECT) {
    return MY_RET_INVALID_PARAMS;
  }
  copy = my_strdup(node->allocator, key);
  if (copy == NULL) {
    return MY_RET_OOM;
  }
  n = my_darray_size(node->children);
  for (i = 0; i < n; i++) {
    my_conf_node_t* c = (my_conf_node_t*)my_darray_get(node->children, i);
    if (my_str_eq(c->key, key)) {
      /* same key: replace in place (insertion order preserved); the
       * darray struct is public, a direct slot write is the in-place
       * replace */
      my_conf_destroy(c);
      my_mem_free(child->allocator, child->key);
      child->key = copy;
      node->children->items[i] = child;
      return MY_RET_OK;
    }
  }
  my_mem_free(child->allocator, child->key);
  child->key = copy;
  if (my_darray_push(node->children, child) != MY_RET_OK) {
    return MY_RET_OOM;
  }
  return MY_RET_OK;
}

my_ret_t my_conf_array_push(my_conf_node_t* node, my_conf_node_t* child) {
  if (node == NULL || child == NULL || node->type != MY_CONF_ARRAY) {
    return MY_RET_INVALID_PARAMS;
  }
  return my_darray_push(node->children, child);
}

size_t my_conf_child_count(const my_conf_node_t* node) {
  if (node == NULL || node->children == NULL) {
    return 0;
  }
  return my_darray_size(node->children);
}

my_conf_node_t* my_conf_child(const my_conf_node_t* node, size_t index) {
  if (node == NULL || node->children == NULL ||
      index >= my_darray_size(node->children)) {
    return NULL;
  }
  return (my_conf_node_t*)my_darray_get(node->children, index);
}

const char* my_conf_key(const my_conf_node_t* node) {
  return node != NULL ? node->key : NULL;
}

/* ---------------- scalar access ---------------- */

my_conf_type_t my_conf_type(const my_conf_node_t* node) {
  return node != NULL ? node->type : MY_CONF_NULL;
}

int64_t my_conf_as_int64(const my_conf_node_t* node, int64_t dflt) {
  return node != NULL && node->type == MY_CONF_INT64 ? node->i : dflt;
}

double my_conf_as_double(const my_conf_node_t* node, double dflt) {
  return node != NULL && node->type == MY_CONF_DOUBLE ? node->d : dflt;
}

bool my_conf_as_bool(const my_conf_node_t* node, bool dflt) {
  return node != NULL && node->type == MY_CONF_BOOL ? node->b : dflt;
}

const char* my_conf_as_str(const my_conf_node_t* node, const char* dflt) {
  return node != NULL && node->type == MY_CONF_STR ? node->str : dflt;
}

/* ---------------- dot paths ---------------- */

/** @brief Select one path segment: object key, or array index when the
 * node is an array and the segment is all digits. */
static my_conf_node_t* path_step(my_conf_node_t* node, const char* seg,
                                 size_t len) {
  size_t i, n;
  if (node == NULL || node->children == NULL) {
    return NULL;
  }
  n = my_darray_size(node->children);
  if (node->type == MY_CONF_ARRAY) {
    size_t idx = 0;
    size_t k;
    if (len == 0) {
      return NULL;
    }
    for (k = 0; k < len; k++) {
      if (seg[k] < '0' || seg[k] > '9') {
        return NULL; /* arrays need all-digit segments */
      }
      idx = idx * 10 + (size_t)(seg[k] - '0');
    }
    return idx < n ? (my_conf_node_t*)my_darray_get(node->children, idx)
                   : NULL;
  }
  if (node->type == MY_CONF_OBJECT) {
    for (i = 0; i < n; i++) {
      my_conf_node_t* c = (my_conf_node_t*)my_darray_get(node->children, i);
      if (c->key != NULL && strlen(c->key) == len &&
          strncmp(c->key, seg, len) == 0) {
        return c;
      }
    }
  }
  return NULL;
}

my_conf_node_t* my_conf_get(my_conf_node_t* node, const char* path) {
  const char* p = path;
  if (node == NULL || path == NULL) {
    return NULL;
  }
  while (*p != '\0' && node != NULL) {
    const char* dot = strchr(p, '.');
    size_t len = dot != NULL ? (size_t)(dot - p) : strlen(p);
    node = path_step(node, p, len);
    p = dot != NULL ? dot + 1 : p + len;
  }
  return node;
}

int64_t my_conf_get_int64(my_conf_node_t* node, const char* path,
                          int64_t dflt) {
  return my_conf_as_int64(my_conf_get(node, path), dflt);
}

double my_conf_get_double(my_conf_node_t* node, const char* path,
                          double dflt) {
  return my_conf_as_double(my_conf_get(node, path), dflt);
}

bool my_conf_get_bool(my_conf_node_t* node, const char* path, bool dflt) {
  return my_conf_as_bool(my_conf_get(node, path), dflt);
}

const char* my_conf_get_str(my_conf_node_t* node, const char* path,
                            const char* dflt) {
  return my_conf_as_str(my_conf_get(node, path), dflt);
}

/* ---------------- file io ---------------- */

static void conf_file_fail(my_conf_error_t* err, const char* message) {
  if (err != NULL) {
    err->line = 0;
    err->col = 0;
    err->offset = 0;
    snprintf(err->msg, sizeof(err->msg), "%s", message);
  }
}

my_conf_node_t* my_conf_load_file(const my_allocator_t* allocator,
                                  const char* path, my_conf_error_t* err) {
  FILE* f;
  long size;
  char* buf;
  my_conf_node_t* root;
  if (err != NULL) {
    memset(err, 0, sizeof(*err));
  }
  if (path == NULL) {
    conf_file_fail(err, "invalid configuration path");
    return NULL;
  }
  f = fopen(path, "rb");
  if (f == NULL) {
    conf_file_fail(err, "cannot open configuration file");
    return NULL;
  }
  if (fseek(f, 0, SEEK_END) != 0 || (size = ftell(f)) < 0 ||
      fseek(f, 0, SEEK_SET) != 0) {
    fclose(f);
    conf_file_fail(err, "cannot read configuration file");
    return NULL;
  }
  if (size > (long)MY_CONF_FILE_MAX_BYTES) {
    fclose(f);
    conf_file_fail(err, "configuration file exceeds resource budget");
    return NULL;
  }
  buf = (char*)my_mem_alloc(allocator, (size_t)size + 1);
  if (buf == NULL ||
      (size > 0 && fread(buf, 1, (size_t)size, f) != (size_t)size)) {
    fclose(f);
    my_mem_free(allocator, buf);
    conf_file_fail(err, buf == NULL ? "out of memory" :
                                      "cannot read configuration file");
    return NULL;
  }
  fclose(f);
  root = my_conf_parse_json(allocator, buf, (size_t)size, err);
  my_mem_free(allocator, buf);
  return root;
}

my_ret_t my_conf_save_file(my_conf_node_t* node, const char* path) {
  char* s;
  FILE* f;
  size_t len;
  my_ret_t ret = MY_RET_OK;
  if (node == NULL || path == NULL) {
    return MY_RET_INVALID_PARAMS;
  }
  s = my_conf_to_json_str(NULL, node, true);
  if (s == NULL) {
    return MY_RET_OOM;
  }
  f = fopen(path, "wb");
  if (f == NULL) {
    my_mem_free(NULL, s);
    return MY_RET_FAIL;
  }
  len = strlen(s);
  if (fwrite(s, 1, len, f) != len) {
    ret = MY_RET_FAIL;
  }
  fclose(f);
  my_mem_free(NULL, s);
  return ret;
}
