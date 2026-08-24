/**
 * @file my_xml.c
 * @brief Minimal XML parser (single pass, small DOM).
 */
#include "myui/my_xml.h"

#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "myc/my_str.h"

typedef struct parser_t {
  const my_allocator_t* allocator;
  const char* p;
  int line;
  const char* line_start;
  my_xml_error_t* err;
} parser_t;

static my_ret_t fail(parser_t* ps, const char* msg) {
  if (ps->err != NULL) {
    ps->err->line = ps->line;
    ps->err->col = (int)(ps->p - ps->line_start) + 1;
    snprintf(ps->err->message, sizeof(ps->err->message), "%s", msg);
  }
  return MY_RET_FAIL;
}

static void advance(parser_t* ps) {
  if (*ps->p == '\n') {
    ps->line++;
    ps->line_start = ps->p + 1;
  }
  ps->p++;
}

static void skip_ws(parser_t* ps) {
  while (*ps->p == ' ' || *ps->p == '\t' || *ps->p == '\n' || *ps->p == '\r') {
    advance(ps);
  }
}

static bool name_start_char(char c) {
  return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c == '_';
}

static bool name_char(char c) {
  return name_start_char(c) || (c >= '0' && c <= '9') || c == '-' ||
         c == '.' || c == ':';
}

static char* parse_name(parser_t* ps) {
  const char* start = ps->p;
  size_t len;
  if (!name_start_char(*ps->p)) {
    return NULL;
  }
  while (name_char(*ps->p)) {
    ps->p++;
  }
  len = (size_t)(ps->p - start);
  if (len > MY_XML_MAX_NAME_BYTES) {
    fail(ps, "XML name exceeds resource budget");
    return NULL;
  }
  return my_strndup(ps->allocator, start, len);
}

static bool starts_with(parser_t* ps, const char* prefix) {
  return strncmp(ps->p, prefix, strlen(prefix)) == 0;
}

/** @brief Append text to a growable owned buffer. */
static my_ret_t text_append(parser_t* ps, char** buf, size_t* used,
                            size_t* capacity, const char* s, size_t len,
                            size_t max_bytes) {
  size_t total;
  size_t needed;
  size_t new_capacity;
  char* p;
  if (*used > max_bytes || len > max_bytes - *used) {
    return fail(ps, "XML text value exceeds resource budget");
  }
  total = *used + len;
  if (total >= SIZE_MAX) {
    return fail(ps, "XML text size overflow");
  }
  needed = total + 1u;
  if (needed > *capacity) {
    new_capacity = *capacity != 0 ? *capacity : 64u;
    while (new_capacity < needed) {
      if (new_capacity > (max_bytes + 1u) / 2u) {
        new_capacity = max_bytes + 1u;
        break;
      }
      new_capacity *= 2u;
    }
    p = (char*)my_mem_realloc(ps->allocator, *buf, new_capacity);
    if (p == NULL) {
      return MY_RET_OOM;
    }
    *buf = p;
    *capacity = new_capacity;
  }
  memcpy(*buf + *used, s, len);
  (*buf)[total] = '\0';
  *used = total;
  return MY_RET_OK;
}

/** @brief Decode one predefined entity at ps->p (points past '&'). */
static my_ret_t parse_entity(parser_t* ps, char* out) {
  static const struct {
    const char* name;
    char ch;
  } ENTS[] = {{"lt;", '<'}, {"gt;", '>'}, {"amp;", '&'},
              {"quot;", '"'}, {"apos;", '\''}};
  size_t i;
  for (i = 0; i < 5; i++) {
    size_t len = strlen(ENTS[i].name);
    if (strncmp(ps->p, ENTS[i].name, len) == 0) {
      ps->p += len;
      *out = ENTS[i].ch;
      return MY_RET_OK;
    }
  }
  return fail(ps, "unknown entity");
}

/** @brief Parse text until '<' or end; decodes entities; CDATA appended raw. */
static my_ret_t parse_text_into(parser_t* ps, char** text, size_t* text_len,
                                size_t* text_capacity) {
  for (;;) {
    const char* start = ps->p;
    while (*ps->p != '\0' && *ps->p != '<' && *ps->p != '&') {
      advance(ps);
    }
    if (ps->p > start) {
      my_ret_t ret = text_append(ps, text, text_len, text_capacity, start,
                                 (size_t)(ps->p - start),
                                 MY_XML_MAX_TEXT_BYTES);
      if (ret != MY_RET_OK) {
        return ret;
      }
    }
    if (*ps->p == '&') {
      char ch;
      ps->p++;
      if (parse_entity(ps, &ch) != MY_RET_OK) {
        return MY_RET_FAIL;
      }
      {
        my_ret_t ret = text_append(ps, text, text_len, text_capacity, &ch, 1,
                                   MY_XML_MAX_TEXT_BYTES);
        if (ret != MY_RET_OK) {
          return ret;
        }
      }
      continue;
    }
    if (starts_with(ps, "<![CDATA[")) {
      const char* end;
      ps->p += 9;
      start = ps->p;
      end = strstr(ps->p, "]]>");
      if (end == NULL) {
        return fail(ps, "unclosed CDATA");
      }
      while (ps->p < end) {
        advance(ps); /* keep line numbers */
      }
      {
        my_ret_t ret = text_append(ps, text, text_len, text_capacity, start,
                                   (size_t)(end - start),
                                   MY_XML_MAX_TEXT_BYTES);
        if (ret != MY_RET_OK) {
          return ret;
        }
      }
      ps->p = end + 3;
      continue;
    }
    return MY_RET_OK; /* '<' or NUL */
  }
}

static my_ret_t parse_attr_value(parser_t* ps, char** out) {
  char quote = *ps->p;
  char* buf = NULL;
  size_t value_len = 0;
  size_t value_capacity = 0;
  if (quote != '"' && quote != '\'') {
    return fail(ps, "attribute value must be quoted");
  }
  ps->p++;
  for (;;) {
    const char* start = ps->p;
    while (*ps->p != '\0' && *ps->p != quote && *ps->p != '&' &&
           *ps->p != '<') {
      advance(ps);
    }
    {
      my_ret_t ret = text_append(ps, &buf, &value_len, &value_capacity, start,
                                 (size_t)(ps->p - start),
                                 MY_XML_MAX_ATTRIBUTE_VALUE_BYTES);
      if (ret != MY_RET_OK) {
        my_mem_free(ps->allocator, buf);
        return ret;
      }
    }
    if (*ps->p == quote) {
      ps->p++;
      break;
    }
    if (*ps->p == '<' || *ps->p == '\0') {
      my_mem_free(ps->allocator, buf);
      return fail(ps, "unclosed attribute value");
    }
    {
      char ch;
      ps->p++;
      if (parse_entity(ps, &ch) != MY_RET_OK) {
        my_mem_free(ps->allocator, buf);
        return MY_RET_FAIL;
      }
      {
        my_ret_t ret = text_append(ps, &buf, &value_len, &value_capacity, &ch,
                                   1, MY_XML_MAX_ATTRIBUTE_VALUE_BYTES);
        if (ret != MY_RET_OK) {
          my_mem_free(ps->allocator, buf);
          return ret;
        }
      }
    }
  }
  *out = buf;
  return MY_RET_OK;
}

static my_ret_t node_add_child(parser_t* ps, my_xml_node_t* parent,
                               my_xml_node_t* child) {
  size_t bytes;
  if (parent->child_count >= MY_XML_MAX_CHILDREN_PER_ELEMENT ||
      parent->child_count > (SIZE_MAX / sizeof(my_xml_node_t*)) - 1u) {
    return fail(ps, "XML child count exceeds resource budget");
  }
  bytes = (parent->child_count + 1u) * sizeof(my_xml_node_t*);
  my_xml_node_t** arr = (my_xml_node_t**)my_mem_realloc(
      ps->allocator, parent->children, bytes);
  if (arr == NULL) {
    return MY_RET_OOM;
  }
  parent->children = arr;
  parent->children[parent->child_count++] = child;
  return MY_RET_OK;
}

static my_ret_t node_add_attr(parser_t* ps, my_xml_node_t* node, char* name,
                              char* value) {
  size_t bytes;
  if (node->attr_count >= MY_XML_MAX_ATTRIBUTES_PER_ELEMENT ||
      node->attr_count > (SIZE_MAX / sizeof(my_xml_attr_t)) - 1u) {
    return fail(ps, "XML attribute count exceeds resource budget");
  }
  bytes = (node->attr_count + 1u) * sizeof(my_xml_attr_t);
  my_xml_attr_t* arr = (my_xml_attr_t*)my_mem_realloc(
      ps->allocator, node->attrs, bytes);
  if (arr == NULL) {
    return MY_RET_OOM;
  }
  node->attrs = arr;
  node->attrs[node->attr_count].name = name;
  node->attrs[node->attr_count].value = value;
  node->attr_count++;
  return MY_RET_OK;
}

static bool node_has_attr(const my_xml_node_t* node, const char* name) {
  size_t i;
  for (i = 0; i < node->attr_count; i++) {
    if (my_str_eq(node->attrs[i].name, name)) {
      return true;
    }
  }
  return false;
}

static my_xml_node_t* parse_element(parser_t* ps, my_ret_t* out_err,
                                    size_t depth);
static void free_node(parser_t* ps, my_xml_node_t* node);

/** @brief Parse the content of an element until its close tag. */
static my_ret_t parse_content(parser_t* ps, my_xml_node_t* node,
                              size_t depth) {
  size_t text_len = node->text != NULL ? strlen(node->text) : 0;
  size_t text_capacity = node->text != NULL ? text_len + 1u : 0;
  for (;;) {
    skip_ws(ps);
    if (*ps->p == '\0') {
      return fail(ps, "unexpected end of document (unclosed element)");
    }
    if (starts_with(ps, "</")) {
      const char* name_start;
      size_t len;
      ps->p += 2;
      name_start = ps->p;
      while (name_char(*ps->p)) {
        ps->p++;
      }
      len = (size_t)(ps->p - name_start);
      if (len > MY_XML_MAX_NAME_BYTES) {
        return fail(ps, "XML name exceeds resource budget");
      }
      if (len != strlen(node->name) ||
          strncmp(name_start, node->name, len) != 0) {
        return fail(ps, "mismatched close tag");
      }
      skip_ws(ps);
      if (*ps->p != '>') {
        return fail(ps, "expected '>' in close tag");
      }
      ps->p++;
      return MY_RET_OK;
    }
    if (starts_with(ps, "<!--")) {
      const char* end;
      ps->p += 4;
      end = strstr(ps->p, "-->");
      if (end == NULL) {
        return fail(ps, "unclosed comment");
      }
      while (ps->p < end) {
        advance(ps);
      }
      ps->p = end + 3;
      continue;
    }
    if (*ps->p == '<' && !starts_with(ps, "<![CDATA[")) {
      my_xml_node_t* child;
      my_ret_t err = MY_RET_OK;
      ps->p++;
      child = parse_element(ps, &err, depth + 1);
      if (err != MY_RET_OK || child == NULL) {
        free_node(ps, child);
        return err != MY_RET_OK ? err : MY_RET_FAIL;
      }
      {
        my_ret_t ret = node_add_child(ps, node, child);
        if (ret != MY_RET_OK) {
          free_node(ps, child);
          return ret;
        }
      }
      continue;
    }
    {
      my_ret_t ret = parse_text_into(ps, &node->text, &text_len,
                                     &text_capacity);
      if (ret != MY_RET_OK) {
        return ret;
      }
    }
  }
}

/** @brief Parse one element (current char is just past '<'). */
static my_xml_node_t* parse_element(parser_t* ps, my_ret_t* out_err,
                                    size_t depth) {
  my_xml_node_t* node;
  if (depth == 0 || depth > MY_XML_MAX_DEPTH) {
    *out_err = fail(ps, "maximum element depth exceeded");
    return NULL;
  }
  node = (my_xml_node_t*)my_mem_calloc(ps->allocator, 1,
                                       sizeof(my_xml_node_t));
  if (node == NULL) {
    *out_err = MY_RET_OOM;
    return NULL;
  }
  node->line = ps->line;
  node->name = parse_name(ps);
  if (node->name == NULL) {
    *out_err = fail(ps, "expected element name");
    my_mem_free(ps->allocator, node);
    return NULL;
  }
  for (;;) {
    skip_ws(ps);
    if (*ps->p == '/' && ps->p[1] == '>') {
      ps->p += 2; /* self-closing */
      *out_err = MY_RET_OK;
      return node;
    }
    if (*ps->p == '>') {
      ps->p++;
      *out_err = parse_content(ps, node, depth);
      if (*out_err != MY_RET_OK) {
        /* caller destroys via doc root */
        return node;
      }
      *out_err = MY_RET_OK;
      return node;
    }
    {
      char* name = parse_name(ps);
      char* value = NULL;
      if (name == NULL) {
        *out_err = fail(ps, "expected attribute name");
        return node; /* freed by caller */
      }
      skip_ws(ps);
      if (*ps->p != '=') {
        my_mem_free(ps->allocator, name);
        *out_err = fail(ps, "expected '=' after attribute name");
        return node;
      }
      ps->p++;
      skip_ws(ps);
      if (parse_attr_value(ps, &value) != MY_RET_OK) {
        my_mem_free(ps->allocator, name);
        *out_err = MY_RET_FAIL;
        return node;
      }
      if (node_has_attr(node, name)) {
        my_mem_free(ps->allocator, name);
        my_mem_free(ps->allocator, value);
        *out_err = fail(ps, "duplicate attribute");
        return node;
      }
      {
        my_ret_t ret = node_add_attr(ps, node, name, value);
        if (ret != MY_RET_OK) {
          my_mem_free(ps->allocator, name);
          my_mem_free(ps->allocator, value);
          *out_err = ret;
          return node;
        }
      }
    }
  }
}

/** @brief Free a subtree (parse-error path). */
static void free_node(parser_t* ps, my_xml_node_t* node) {
  size_t i;
  if (node == NULL) {
    return;
  }
  for (i = 0; i < node->attr_count; i++) {
    my_mem_free(ps->allocator, node->attrs[i].name);
    my_mem_free(ps->allocator, node->attrs[i].value);
  }
  my_mem_free(ps->allocator, node->attrs);
  for (i = 0; i < node->child_count; i++) {
    free_node(ps, node->children[i]);
  }
  my_mem_free(ps->allocator, node->children);
  my_mem_free(ps->allocator, node->name);
  my_mem_free(ps->allocator, node->text);
  my_mem_free(ps->allocator, node);
}

static void skip_prolog_and_misc(parser_t* ps) {
  for (;;) {
    skip_ws(ps);
    if (starts_with(ps, "<?")) {
      const char* end = strstr(ps->p, "?>");
      if (end == NULL) {
        return;
      }
      while (ps->p < end) {
        advance(ps);
      }
      ps->p = end + 2;
      continue;
    }
    if (starts_with(ps, "<!--")) {
      const char* end = strstr(ps->p, "-->");
      if (end == NULL) {
        return;
      }
      while (ps->p < end) {
        advance(ps);
      }
      ps->p = end + 3;
      continue;
    }
    return;
  }
}

my_xml_doc_t* my_xml_parse(const my_allocator_t* allocator, const char* str,
                           my_xml_error_t* err) {
  parser_t ps;
  my_xml_doc_t* doc;
  my_ret_t perr = MY_RET_OK;
  if (str == NULL) {
    return NULL;
  }
  ps.allocator = allocator;
  ps.p = str;
  ps.line = 1;
  ps.line_start = str;
  ps.err = err;
  if (err != NULL) {
    err->line = 0;
    err->col = 0;
    err->message[0] = '\0';
  }

  skip_prolog_and_misc(&ps);
  if (*ps.p != '<') {
    fail(&ps, "document has no root element");
    return NULL;
  }
  ps.p++;
  doc = (my_xml_doc_t*)my_mem_calloc(allocator, 1, sizeof(my_xml_doc_t));
  if (doc == NULL) {
    return NULL;
  }
  doc->allocator = allocator;
  doc->root = parse_element(&ps, &perr, 1);
  if (perr != MY_RET_OK || doc->root == NULL) {
    if (perr == MY_RET_OK) {
      fail(&ps, "parse error");
    }
    free_node(&ps, doc->root);
    my_mem_free(allocator, doc);
    return NULL;
  }
  skip_prolog_and_misc(&ps);
  if (*ps.p != '\0') {
    free_node(&ps, doc->root);
    my_mem_free(allocator, doc);
    fail(&ps, "content after root element");
    return NULL;
  }
  return doc;
}

static void node_destroy(const my_allocator_t* alloc, my_xml_node_t* node) {
  size_t i;
  if (node == NULL) {
    return;
  }
  for (i = 0; i < node->attr_count; i++) {
    my_mem_free(alloc, node->attrs[i].name);
    my_mem_free(alloc, node->attrs[i].value);
  }
  my_mem_free(alloc, node->attrs);
  for (i = 0; i < node->child_count; i++) {
    node_destroy(alloc, node->children[i]);
  }
  my_mem_free(alloc, node->children);
  my_mem_free(alloc, node->name);
  my_mem_free(alloc, node->text);
  my_mem_free(alloc, node);
}

void my_xml_doc_destroy(my_xml_doc_t* doc) {
  if (doc != NULL) {
    node_destroy(doc->allocator, doc->root);
    my_mem_free(doc->allocator, doc);
  }
}

const char* my_xml_node_attr(const my_xml_node_t* node, const char* name) {
  size_t i;
  if (node == NULL || name == NULL) {
    return NULL;
  }
  for (i = 0; i < node->attr_count; i++) {
    if (my_str_eq(node->attrs[i].name, name)) {
      return node->attrs[i].value;
    }
  }
  return NULL;
}

my_xml_node_t* my_xml_node_child(const my_xml_node_t* node, size_t index) {
  if (node == NULL || index >= node->child_count) {
    return NULL;
  }
  return node->children[index];
}

my_xml_node_t* my_xml_node_find(const my_xml_node_t* node, const char* name) {
  size_t i;
  if (node == NULL || name == NULL) {
    return NULL;
  }
  for (i = 0; i < node->child_count; i++) {
    if (my_str_eq(node->children[i]->name, name)) {
      return node->children[i];
    }
  }
  return NULL;
}
