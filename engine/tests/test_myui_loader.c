#include "test_framework.h"

#include <stdlib.h>
#include <string.h>

#include "myui/my_ui_loader.h"
#include "myui/widgets/my_label.h"

TEST(yaml_loader_builds_typed_widget)
{
  const char* yaml =
      "type: label\n"
      "text: Hello YAML\n"
      "x: 7\n"
      "visible: false\n";
  my_ui_error_t error = {0};
  my_widget_t* widget = my_ui_load_str(NULL, NULL, yaml, &error);
  my_label_t* label;

  ASSERT_NOT_NULL(widget);
  label = (my_label_t*)widget;
  ASSERT_STR_EQ(label->text, "Hello YAML");
  ASSERT_EQ(widget->rect.x, 7);
  ASSERT_FALSE(widget->visible);
  my_widget_unref(widget);
}

TEST(yaml_loader_builds_nested_children)
{
  const char* yaml =
      "type: widget\n"
      "children:\n"
      "  - type: label\n"
      "    text: First\n"
      "  - type: button\n"
      "    text: Second\n";
  my_ui_error_t error = {0};
  my_widget_t* root = my_ui_load_str(NULL, NULL, yaml, &error);

  ASSERT_NOT_NULL(root);
  ASSERT_EQ(my_widget_child_count(root), 2u);
  ASSERT_STR_EQ(my_widget_get_child(root, 0)->widget_type, "label");
  ASSERT_STR_EQ(my_widget_get_child(root, 1)->widget_type, "button");
  my_widget_unref(root);
}

TEST(yaml_loader_rejects_xml_input)
{
  const char* xml = "<label text=\"not yaml\"/>";
  my_ui_error_t error = {0};
  my_widget_t* widget = my_ui_load_str(NULL, NULL, xml, &error);

  ASSERT_TRUE(widget == NULL);
  ASSERT_TRUE(error.message[0] != '\0');
}

TEST(yaml_loader_rejects_invalid_shapes)
{
  const char* invalid_type = "type: label\nvisible: yes\n";
  const char* invalid_children = "type: widget\nchildren: label\n";
  my_ui_error_t error = {0};

  ASSERT_TRUE(my_ui_load_str(NULL, NULL, invalid_type, &error) == NULL);
  ASSERT_TRUE(error.message[0] != '\0');
  memset(&error, 0, sizeof(error));
  ASSERT_TRUE(my_ui_load_str(NULL, NULL, invalid_children, &error) == NULL);
  ASSERT_TRUE(error.message[0] != '\0');
}

TEST(yaml_loader_applies_bindings_map)
{
  const char* yaml =
      "type: label\n"
      "bindings:\n"
      "  text: title\n";
  my_ui_error_t error = {0};
  my_widget_t* widget = my_ui_load_str(NULL, NULL, yaml, &error);

  ASSERT_NOT_NULL(widget);
  ASSERT_STR_EQ(widget->bind_rules, "v:text=title;");
  my_widget_unref(widget);
}

TEST(yaml_loader_rejects_oversized_input)
{
  char* yaml = (char*)malloc(MY_UI_MAX_YAML_BYTES + 2u);
  my_ui_error_t error = {0};

  ASSERT_NOT_NULL(yaml);
  memset(yaml, 'x', MY_UI_MAX_YAML_BYTES + 1u);
  yaml[MY_UI_MAX_YAML_BYTES + 1u] = '\0';
  ASSERT_TRUE(my_ui_load_str(NULL, NULL, yaml, &error) == NULL);
  ASSERT_TRUE(error.message[0] != '\0');
  free(yaml);
}

TEST_MAIN_BEGIN()
    RUN_TEST(yaml_loader_builds_typed_widget);
    RUN_TEST(yaml_loader_builds_nested_children);
    RUN_TEST(yaml_loader_rejects_xml_input);
    RUN_TEST(yaml_loader_rejects_invalid_shapes);
    RUN_TEST(yaml_loader_applies_bindings_map);
    RUN_TEST(yaml_loader_rejects_oversized_input);
TEST_MAIN_END()
