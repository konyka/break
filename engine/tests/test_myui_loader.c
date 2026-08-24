#include "test_framework.h"

#include <stdlib.h>
#include <string.h>

#include "myc/myconf/my_conf.h"
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

TEST(yaml_loader_rejects_non_yaml_markup)
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

TEST(yaml_parser_rejects_excessive_nesting)
{
  size_t capacity = MY_CONF_YAML_MAX_DEPTH * 4u + 32u;
  size_t used = 0;
  size_t i;
  char* yaml = (char*)malloc(capacity);
  my_conf_error_t error;
  my_conf_node_t* root;

  ASSERT_NOT_NULL(yaml);
  for (i = 0; i < MY_CONF_YAML_MAX_DEPTH + 1u; i++) {
    size_t indent = i * 2u;
    while (used + indent + 4u >= capacity) {
      capacity *= 2u;
      yaml = (char*)realloc(yaml, capacity);
      ASSERT_NOT_NULL(yaml);
    }
    memset(yaml + used, ' ', indent);
    used += indent;
    memcpy(yaml + used, "a:\n", 3);
    used += 3;
  }
  memset(yaml + used, ' ', (MY_CONF_YAML_MAX_DEPTH + 1u) * 2u);
  used += (MY_CONF_YAML_MAX_DEPTH + 1u) * 2u;
  memcpy(yaml + used, "x: 1\n", 5);
  used += 5;
  yaml[used] = '\0';
  root = my_conf_parse_yaml(NULL, yaml, used, &error);
  ASSERT_TRUE(root == NULL);
  free(yaml);
}

TEST(yaml_parser_rejects_excessive_sequence_size)
{
  size_t count = MY_CONF_YAML_MAX_CHILDREN + 1u;
  size_t length = count * 4u;
  size_t i;
  char* yaml = (char*)malloc(length + 1u);
  my_conf_error_t error;
  my_conf_node_t* root;

  ASSERT_NOT_NULL(yaml);
  for (i = 0; i < count; i++) {
    memcpy(yaml + i * 4u, "- x\n", 4);
  }
  yaml[length] = '\0';
  root = my_conf_parse_yaml(NULL, yaml, length, &error);
  ASSERT_TRUE(root == NULL);
  free(yaml);
}

TEST(yaml_parser_rejects_invalid_input_without_error_storage)
{
  my_conf_node_t* root = my_conf_parse_yaml(NULL, "type: [\n", 8u, NULL);

  ASSERT_TRUE(root == NULL);
}

TEST(yaml_parser_rejects_excessive_flow_nesting)
{
  size_t depth = MY_CONF_YAML_MAX_DEPTH + 1u;
  size_t length = depth * 2u + 2u;
  size_t i;
  char* yaml = (char*)malloc(length + 1u);
  my_conf_error_t error;
  my_conf_node_t* root;

  ASSERT_NOT_NULL(yaml);
  for (i = 0; i < depth; i++) {
    yaml[i] = '[';
  }
  yaml[depth] = '0';
  for (i = 0; i < depth; i++) {
    yaml[depth + 1u + i] = ']';
  }
  yaml[length] = '\0';
  root = my_conf_parse_yaml(NULL, yaml, length, &error);
  ASSERT_TRUE(root == NULL);
  free(yaml);
}

TEST(yaml_parser_rejects_oversized_quoted_scalar)
{
  size_t length = MY_CONF_YAML_MAX_SCALAR_BYTES + 4u;
  char* yaml = (char*)malloc(length + 1u);
  my_conf_error_t error;
  my_conf_node_t* root;

  ASSERT_NOT_NULL(yaml);
  yaml[0] = '"';
  memset(yaml + 1, 'x', MY_CONF_YAML_MAX_SCALAR_BYTES + 1u);
  yaml[MY_CONF_YAML_MAX_SCALAR_BYTES + 2u] = '"';
  yaml[MY_CONF_YAML_MAX_SCALAR_BYTES + 3u] = '\n';
  yaml[length] = '\0';
  root = my_conf_parse_yaml(NULL, yaml, length, &error);
  ASSERT_TRUE(root == NULL);
  free(yaml);
}

TEST(yaml_parser_rejects_oversized_flow_map_key)
{
  size_t key_length = MY_CONF_YAML_MAX_SCALAR_BYTES + 1u;
  size_t length = key_length + 12u;
  char* yaml = (char*)malloc(length + 1u);
  my_conf_error_t error;
  my_conf_node_t* root;

  ASSERT_NOT_NULL(yaml);
  memcpy(yaml, "value: {", 8u);
  memset(yaml + 8u, 'k', key_length);
  yaml[key_length + 8u] = ':';
  yaml[key_length + 9u] = ' ';
  yaml[key_length + 10u] = '1';
  yaml[key_length + 11u] = '}';
  yaml[length] = '\0';
  root = my_conf_parse_yaml(NULL, yaml, length, &error);
  ASSERT_TRUE(root == NULL);
  free(yaml);
}

TEST(yaml_parser_rejects_duplicate_inline_map_key)
{
  const char* yaml =
      "items:\n"
      "  - name: first\n"
      "    name: second\n";
  my_conf_error_t error;
  my_conf_node_t* root = my_conf_parse_yaml(NULL, yaml, strlen(yaml), &error);

  ASSERT_TRUE(root == NULL);
  ASSERT_TRUE(error.msg[0] != '\0');
}

TEST(yaml_parser_rejects_duplicate_flow_map_key)
{
  const char* yaml = "value: {name: first, name: second}\n";
  my_conf_error_t error;
  my_conf_node_t* root = my_conf_parse_yaml(NULL, yaml, strlen(yaml), &error);

  ASSERT_TRUE(root == NULL);
  ASSERT_TRUE(error.msg[0] != '\0');
}

TEST_MAIN_BEGIN()
    RUN_TEST(yaml_loader_builds_typed_widget);
    RUN_TEST(yaml_loader_builds_nested_children);
    RUN_TEST(yaml_loader_rejects_non_yaml_markup);
    RUN_TEST(yaml_loader_rejects_invalid_shapes);
    RUN_TEST(yaml_loader_applies_bindings_map);
    RUN_TEST(yaml_loader_rejects_oversized_input);
    RUN_TEST(yaml_parser_rejects_excessive_nesting);
    RUN_TEST(yaml_parser_rejects_excessive_sequence_size);
    RUN_TEST(yaml_parser_rejects_invalid_input_without_error_storage);
    RUN_TEST(yaml_parser_rejects_excessive_flow_nesting);
    RUN_TEST(yaml_parser_rejects_oversized_quoted_scalar);
    RUN_TEST(yaml_parser_rejects_oversized_flow_map_key);
    RUN_TEST(yaml_parser_rejects_duplicate_inline_map_key);
    RUN_TEST(yaml_parser_rejects_duplicate_flow_map_key);
TEST_MAIN_END()
