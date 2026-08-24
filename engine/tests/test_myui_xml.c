#include "test_framework.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "myui/my_xml.h"

TEST(xml_rejects_duplicate_attributes)
{
  const char* xml = "<button text=\"send\" text=\"override\"/>";
  my_xml_error_t error;
  my_xml_doc_t* doc = my_xml_parse(NULL, xml, &error);

  ASSERT_TRUE(doc == NULL);
  ASSERT_TRUE(error.message[0] != '\0');
}

TEST(xml_accepts_entities_and_cdata_without_confusing_markup)
{
  const char* xml = "<root title=\"a &amp; b\"><![CDATA[x < y }]]></root>";
  my_xml_error_t error;
  my_xml_doc_t* doc = my_xml_parse(NULL, xml, &error);

  ASSERT_NOT_NULL(doc);
  ASSERT_STR_EQ(my_xml_node_attr(doc->root, "title"), "a & b");
  ASSERT_STR_EQ(doc->root->text, "x < y }");
  my_xml_doc_destroy(doc);
}

TEST(xml_rejects_unquoted_attribute_and_trailing_root)
{
  const char* unquoted = "<root value=test/>";
  const char* trailing = "<root/><extra/>";
  my_xml_error_t error;
  my_xml_doc_t* doc;

  doc = my_xml_parse(NULL, unquoted, &error);
  ASSERT_TRUE(doc == NULL);
  ASSERT_TRUE(error.message[0] != '\0');
  doc = my_xml_parse(NULL, trailing, &error);
  ASSERT_TRUE(doc == NULL);
  ASSERT_TRUE(error.message[0] != '\0');
}

TEST(xml_rejects_excessive_nesting_depth)
{
  char xml[4096];
  my_xml_error_t error;
  my_xml_doc_t* doc;
  size_t pos = 0;
  size_t i;

  for (i = 0; i < MY_XML_MAX_DEPTH; i++) {
    memcpy(xml + pos, "<n>", 3);
    pos += 3;
  }
  for (i = 0; i < MY_XML_MAX_DEPTH; i++) {
    memcpy(xml + pos, "</n>", 4);
    pos += 4;
  }
  xml[pos] = '\0';
  doc = my_xml_parse(NULL, xml, &error);
  ASSERT_NOT_NULL(doc);
  my_xml_doc_destroy(doc);

  pos = 0;
  for (i = 0; i < 257; i++) {
    memcpy(xml + pos, "<n>", 3);
    pos += 3;
  }
  for (i = 0; i < 257; i++) {
    memcpy(xml + pos, "</n>", 4);
    pos += 4;
  }
  xml[pos] = '\0';
  doc = my_xml_parse(NULL, xml, &error);
  ASSERT_TRUE(doc == NULL);
  ASSERT_TRUE(error.message[0] != '\0');
}

TEST(xml_rejects_values_over_resource_budget)
{
  char* attr_xml;
  char* text_xml;
  my_xml_error_t error;
  my_xml_doc_t* doc;
  size_t i;
  size_t attr_len = MY_XML_MAX_ATTRIBUTE_VALUE_BYTES + 1u;
  size_t text_len = MY_XML_MAX_TEXT_BYTES + 1u;

  attr_xml = (char*)malloc(attr_len + 32u);
  text_xml = (char*)malloc(text_len + 16u);
  ASSERT_NOT_NULL(attr_xml);
  ASSERT_NOT_NULL(text_xml);
  memcpy(attr_xml, "<root value=\"", 13);
  memset(attr_xml + 13, 'a', attr_len);
  memcpy(attr_xml + 13 + attr_len, "\"/>", 4);
  doc = my_xml_parse(NULL, attr_xml, &error);
  ASSERT_TRUE(doc == NULL);
  ASSERT_TRUE(error.message[0] != '\0');
  memcpy(text_xml, "<root>", 6);
  for (i = 0; i < text_len; i++) {
    text_xml[6 + i] = 'b';
  }
  memcpy(text_xml + 6 + text_len, "</root>", 8);
  doc = my_xml_parse(NULL, text_xml, &error);
  ASSERT_TRUE(doc == NULL);
  ASSERT_TRUE(error.message[0] != '\0');
  free(attr_xml);
  free(text_xml);
}

TEST(xml_rejects_excessive_name_length)
{
  char* xml;
  my_xml_error_t error;
  my_xml_doc_t* doc;
  size_t name_len = MY_XML_MAX_NAME_BYTES + 1u;
  size_t length = name_len * 2u + 6u;

  xml = (char*)malloc(length);
  ASSERT_NOT_NULL(xml);
  xml[0] = '<';
  memset(xml + 1, 'n', name_len);
  xml[1 + name_len] = '>';
  xml[2 + name_len] = '<';
  xml[3 + name_len] = '/';
  memset(xml + 4 + name_len, 'n', name_len);
  xml[4 + name_len * 2u] = '>';
  xml[5 + name_len * 2u] = '\0';
  doc = my_xml_parse(NULL, xml, &error);
  ASSERT_TRUE(doc == NULL);
  ASSERT_TRUE(error.message[0] != '\0');
  free(xml);
}

TEST(xml_accepts_dense_entity_text_with_linear_growth)
{
  char* xml;
  my_xml_error_t error;
  my_xml_doc_t* doc;
  size_t entity_count = 4096u;
  size_t length = 6u + entity_count * 5u + 7u + 1u;
  size_t offset = 0;
  size_t i;

  xml = (char*)malloc(length);
  ASSERT_NOT_NULL(xml);
  memcpy(xml + offset, "<root>", 6);
  offset += 6;
  for (i = 0; i < entity_count; i++) {
    memcpy(xml + offset, "&amp;", 5);
    offset += 5;
  }
  memcpy(xml + offset, "</root>\0", 8);
  doc = my_xml_parse(NULL, xml, &error);
  ASSERT_NOT_NULL(doc);
  ASSERT_TRUE(strlen(doc->root->text) == entity_count);
  my_xml_doc_destroy(doc);
  free(xml);
}

TEST(xml_rejects_excessive_attribute_count)
{
  char* xml;
  my_xml_error_t error;
  my_xml_doc_t* doc;
  size_t capacity = 16u;
  size_t used = 0;
  size_t i;

  xml = (char*)malloc(capacity);
  ASSERT_NOT_NULL(xml);
  used += (size_t)snprintf(xml + used, capacity - used, "<root");
  for (i = 0; i < MY_XML_MAX_ATTRIBUTES_PER_ELEMENT + 1u; i++) {
    if (used + 16u >= capacity) {
      capacity *= 2u;
      xml = (char*)realloc(xml, capacity);
      ASSERT_NOT_NULL(xml);
    }
    used += (size_t)snprintf(xml + used, capacity - used, " a%zu=\"v\"", i);
  }
  if (used + 3u >= capacity) {
    capacity = used + 3u;
    xml = (char*)realloc(xml, capacity);
    ASSERT_NOT_NULL(xml);
  }
  memcpy(xml + used, "/>\0", 3);
  doc = my_xml_parse(NULL, xml, &error);
  ASSERT_TRUE(doc == NULL);
  ASSERT_TRUE(error.message[0] != '\0');
  free(xml);
}

TEST(xml_rejects_excessive_child_count)
{
  char* xml;
  my_xml_error_t error;
  my_xml_doc_t* doc;
  size_t child_len = 7u;
  size_t length = 6u + (MY_XML_MAX_CHILDREN_PER_ELEMENT + 1u) * child_len + 7u + 1u;
  size_t offset = 0;
  size_t i;

  xml = (char*)malloc(length);
  ASSERT_NOT_NULL(xml);
  memcpy(xml + offset, "<root>", 6);
  offset += 6;
  for (i = 0; i < MY_XML_MAX_CHILDREN_PER_ELEMENT + 1u; i++) {
    memcpy(xml + offset, "<item/>", child_len);
    offset += child_len;
  }
  memcpy(xml + offset, "</root>\0", 8);
  doc = my_xml_parse(NULL, xml, &error);
  ASSERT_TRUE(doc == NULL);
  ASSERT_TRUE(error.message[0] != '\0');
  free(xml);
}

TEST_MAIN_BEGIN()
    RUN_TEST(xml_rejects_duplicate_attributes);
    RUN_TEST(xml_accepts_entities_and_cdata_without_confusing_markup);
    RUN_TEST(xml_rejects_unquoted_attribute_and_trailing_root);
    RUN_TEST(xml_rejects_excessive_nesting_depth);
    RUN_TEST(xml_rejects_values_over_resource_budget);
    RUN_TEST(xml_rejects_excessive_name_length);
    RUN_TEST(xml_accepts_dense_entity_text_with_linear_growth);
    RUN_TEST(xml_rejects_excessive_attribute_count);
    RUN_TEST(xml_rejects_excessive_child_count);
TEST_MAIN_END()
