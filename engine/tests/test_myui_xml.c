#include "test_framework.h"

#include <string.h>

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

TEST_MAIN_BEGIN()
    RUN_TEST(xml_rejects_duplicate_attributes);
    RUN_TEST(xml_accepts_entities_and_cdata_without_confusing_markup);
    RUN_TEST(xml_rejects_unquoted_attribute_and_trailing_root);
TEST_MAIN_END()
