/**
 * @file my_xml.h
 * @brief Minimal XML parser (small DOM), zero dependencies.
 *
 * Supported subset: elements, attributes (single/double quotes), text,
 * comments <!-- -->, CDATA, the five predefined entities
 * (&lt; &gt; &amp; &quot; &apos;), self-closing tags, UTF-8 pass-through.
 * NOT supported (error out): DTD, namespaces, unknown entities.
 * Exactly one root element is required. Errors carry line/column.
 */
#ifndef MY_XML_H
#define MY_XML_H

#include "myc/my_error.h"
#include "myc/my_mem.h"

/** @brief One attribute (name/value, both owned). */
typedef struct my_xml_attr_t {
  char* name;
  char* value;
} my_xml_attr_t;

/** @brief DOM node. */
typedef struct my_xml_node_t {
  char* name;                        /**< element name (owned) */
  my_xml_attr_t* attrs;              /**< attribute array (owned) */
  size_t attr_count;
  struct my_xml_node_t** children;   /**< child element array (owned) */
  size_t child_count;
  char* text;                        /**< concatenated direct text (owned) */
  int line;                          /**< line of the opening tag */
} my_xml_node_t;

/** @brief Parse error location. */
typedef struct my_xml_error_t {
  int line;
  int col;
  char message[80];
} my_xml_error_t;

/** @brief Parsed document. */
typedef struct my_xml_doc_t {
  my_xml_node_t* root;
  const my_allocator_t* allocator;
} my_xml_doc_t;

/**
 * @brief Parse an XML string. Returns NULL on error; err (may be NULL)
 * receives line/column/message.
 */
my_xml_doc_t* my_xml_parse(const my_allocator_t* allocator, const char* str,
                           my_xml_error_t* err);

void my_xml_doc_destroy(my_xml_doc_t* doc);

/** @brief Attribute value by name (NULL when absent). */
const char* my_xml_node_attr(const my_xml_node_t* node, const char* name);

/** @brief Child element by index (NULL when out of range). */
my_xml_node_t* my_xml_node_child(const my_xml_node_t* node, size_t index);

/** @brief First child element with the given name (NULL when absent). */
my_xml_node_t* my_xml_node_find(const my_xml_node_t* node, const char* name);

#endif /* MY_XML_H */
