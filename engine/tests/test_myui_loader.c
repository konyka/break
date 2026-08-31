#include "test_framework.h"

#include <math.h>
#include <stdlib.h>
#include <string.h>

#include "myc/myconf/my_conf.h"
#include "myui/my_ui_loader.h"
#include "myui/widgets/my_label.h"

typedef struct loader_alloc_state_t {
  size_t alloc_calls;
} loader_alloc_state_t;

static void* loader_test_alloc(void* context, size_t size)
{
  loader_alloc_state_t* state = (loader_alloc_state_t*)context;
  state->alloc_calls++;
  return malloc(size);
}

static void* loader_test_calloc(void* context, size_t count, size_t size)
{
  loader_alloc_state_t* state = (loader_alloc_state_t*)context;
  state->alloc_calls++;
  return calloc(count, size);
}

static void* loader_test_realloc(void* context, void* memory, size_t size)
{
  loader_alloc_state_t* state = (loader_alloc_state_t*)context;
  state->alloc_calls++;
  return realloc(memory, size);
}

static void loader_test_free(void* context, void* memory)
{
  (void)context;
  free(memory);
}

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

TEST(yaml_file_loader_rejects_oversized_file_before_allocation)
{
  char path[256];
  FILE* file;
  loader_alloc_state_t state = {0};
  my_allocator_t allocator = {&state, loader_test_alloc, loader_test_calloc,
                              loader_test_realloc, loader_test_free};
  my_ui_error_t error = {0};
  size_t size = (size_t)MY_UI_MAX_YAML_BYTES + 1u;

  test_tmp(path, sizeof(path), "yaml_oversized_file");
  file = fopen(path, "wb");
  ASSERT_NOT_NULL(file);
  ASSERT_EQ(fseek(file, (long)size, SEEK_SET), 0);
  ASSERT_EQ(fputc('\n', file), '\n');
  ASSERT_EQ(fclose(file), 0);
  ASSERT_TRUE(my_ui_load_file(&allocator, NULL, path, &error) == NULL);
  ASSERT_EQ(state.alloc_calls, 0u);
  ASSERT_TRUE(error.message[0] != '\0');
  remove(path);
}

TEST(yaml_file_loader_rejects_embedded_nul)
{
  char path[256];
  FILE* file;
  my_ui_error_t error = {0};

  test_tmp(path, sizeof(path), "yaml_embedded_nul");
  file = fopen(path, "wb");
  ASSERT_NOT_NULL(file);
  ASSERT_TRUE(fputs("type: label\ntext: safe\n", file) >= 0);
  ASSERT_EQ(fputc('\0', file), '\0');
  ASSERT_TRUE(fputs("type: button\ntext: ignored\n", file) >= 0);
  ASSERT_EQ(fclose(file), 0);
  ASSERT_TRUE(my_ui_load_file(NULL, NULL, path, &error) == NULL);
  ASSERT_TRUE(error.message[0] != '\0');
  remove(path);
}

TEST(json_file_loader_rejects_oversized_file_before_allocation)
{
  char path[256];
  FILE* file;
  loader_alloc_state_t state = {0};
  my_allocator_t allocator = {&state, loader_test_alloc, loader_test_calloc,
                              loader_test_realloc, loader_test_free};
  my_conf_error_t error = {0};
  size_t size = (size_t)MY_CONF_FILE_MAX_BYTES + 1u;

  test_tmp(path, sizeof(path), "json_oversized_file");
  file = fopen(path, "wb");
  ASSERT_NOT_NULL(file);
  ASSERT_EQ(fseek(file, (long)size, SEEK_SET), 0);
  ASSERT_EQ(fputc('}', file), '}');
  ASSERT_EQ(fclose(file), 0);
  ASSERT_TRUE(my_conf_load_file(&allocator, path, &error) == NULL);
  ASSERT_EQ(state.alloc_calls, 0u);
  ASSERT_TRUE(error.msg[0] != '\0');
  remove(path);
}

TEST(json_parser_rejects_oversized_input_before_allocation)
{
  size_t length = (size_t)MY_CONF_JSON_MAX_BYTES + 1u;
  char* json = (char*)malloc(length);
  loader_alloc_state_t state = {0};
  my_allocator_t allocator = {&state, loader_test_alloc, loader_test_calloc,
                              loader_test_realloc, loader_test_free};
  my_conf_error_t error = {0};

  ASSERT_NOT_NULL(json);
  memset(json, ' ', length);
  json[0] = '{';
  json[1] = '}';
  ASSERT_TRUE(my_conf_parse_json(&allocator, json, length, &error) == NULL);
  ASSERT_EQ(state.alloc_calls, 0u);
  ASSERT_TRUE(error.msg[0] != '\0');
  free(json);
}

TEST(toml_parser_rejects_oversized_input_before_allocation)
{
  size_t length = (size_t)MY_CONF_TOML_MAX_BYTES + 1u;
  char* toml = (char*)malloc(length);
  loader_alloc_state_t state = {0};
  my_allocator_t allocator = {&state, loader_test_alloc, loader_test_calloc,
                              loader_test_realloc, loader_test_free};
  my_conf_error_t error = {0};

  ASSERT_NOT_NULL(toml);
  memset(toml, ' ', length);
  ASSERT_TRUE(my_conf_parse_toml(&allocator, toml, length, &error) == NULL);
  ASSERT_EQ(state.alloc_calls, 0u);
  ASSERT_TRUE(error.msg[0] != '\0');
  free(toml);
}

TEST(bson_parser_rejects_oversized_input_before_allocation)
{
  size_t length = (size_t)MY_CONF_BSON_MAX_BYTES + 1u;
  unsigned char* bson = (unsigned char*)malloc(length);
  loader_alloc_state_t state = {0};
  my_allocator_t allocator = {&state, loader_test_alloc, loader_test_calloc,
                              loader_test_realloc, loader_test_free};
  my_conf_error_t error = {0};

  ASSERT_NOT_NULL(bson);
  memset(bson, 0x20, length);
  bson[0] = 5;
  bson[1] = 0;
  bson[2] = 0;
  bson[3] = 0;
  bson[4] = 0;
  ASSERT_TRUE(my_conf_parse_bson(&allocator, bson, length, &error) == NULL);
  ASSERT_EQ(state.alloc_calls, 0u);
  ASSERT_TRUE(error.msg[0] != '\0');
  free(bson);
}

TEST(bson_writer_rejects_output_above_parser_budget)
{
  size_t text_length = (size_t)MY_CONF_BSON_MAX_BYTES - 1u;
  char* text = (char*)malloc(text_length + 1u);
  my_conf_node_t* root;
  my_conf_node_t* value;
  uint8_t* bson;
  size_t bson_length = 0;

  ASSERT_NOT_NULL(text);
  memset(text, 'x', text_length);
  text[text_length] = '\0';
  root = my_conf_new_object(NULL);
  value = my_conf_new_str(NULL, text);
  ASSERT_NOT_NULL(root);
  ASSERT_NOT_NULL(value);
  ASSERT_EQ(my_conf_object_set(root, "payload", value), MY_RET_OK);
  bson = my_conf_to_bson(NULL, root, &bson_length);
  ASSERT_TRUE(bson == NULL);
  if (bson != NULL) {
    my_mem_free(NULL, bson);
  }
  my_conf_destroy(root);
  free(text);
}

TEST(json_writer_rejects_output_above_parser_budget)
{
  size_t text_length = (size_t)MY_CONF_JSON_MAX_BYTES - 1u;
  char* text = (char*)malloc(text_length + 1u);
  my_conf_node_t* root;
  my_conf_node_t* value;
  char* json;

  ASSERT_NOT_NULL(text);
  memset(text, 'x', text_length);
  text[text_length] = '\0';
  root = my_conf_new_object(NULL);
  value = my_conf_new_str(NULL, text);
  ASSERT_NOT_NULL(root);
  ASSERT_NOT_NULL(value);
  ASSERT_EQ(my_conf_object_set(root, "payload", value), MY_RET_OK);
  json = my_conf_to_json_str(NULL, root, false);
  ASSERT_TRUE(json == NULL);
  if (json != NULL) {
    my_mem_free(NULL, json);
  }
  my_conf_destroy(root);
  free(text);
}

TEST(json_parser_rejects_nonfinite_numbers)
{
  my_conf_node_t* root = my_conf_parse_json(NULL, "1e999", 5u, NULL);

  ASSERT_TRUE(root == NULL);
  my_conf_destroy(root);
}

TEST(yaml_parser_rejects_nonfinite_numbers)
{
  const char* yaml = "value: 1e999";
  my_conf_node_t* root = my_conf_parse_yaml(NULL, yaml, strlen(yaml), NULL);

  ASSERT_TRUE(root == NULL);
  my_conf_destroy(root);
}

TEST(toml_parser_rejects_nonfinite_numbers)
{
  const char* toml = "value = 1e999";
  my_conf_node_t* root = my_conf_parse_toml(NULL, toml, strlen(toml), NULL);

  ASSERT_TRUE(root == NULL);
  my_conf_destroy(root);
}

TEST(toml_parser_preserves_explicit_special_numbers)
{
  const char* toml = "positive = inf\nnegative = -nan\n";
  my_conf_node_t* root = my_conf_parse_toml(NULL, toml, strlen(toml), NULL);
  my_conf_node_t* positive;
  my_conf_node_t* negative;

  ASSERT_NOT_NULL(root);
  positive = my_conf_get(root, "positive");
  negative = my_conf_get(root, "negative");
  ASSERT_NOT_NULL(positive);
  ASSERT_NOT_NULL(negative);
  ASSERT_TRUE(isinf(my_conf_as_double(positive, 0.0)));
  ASSERT_TRUE(isnan(my_conf_as_double(negative, 0.0)));
  my_conf_destroy(root);
}

TEST(json_writer_rejects_nonfinite_numbers)
{
  const double invalid_values[] = {NAN, INFINITY, -INFINITY};
  size_t i;

  for (i = 0; i < sizeof(invalid_values) / sizeof(invalid_values[0]); i++) {
    my_conf_node_t* value = my_conf_new_double(NULL, invalid_values[i]);
    char* json;

    ASSERT_NOT_NULL(value);
    json = my_conf_to_json_str(NULL, value, false);
    ASSERT_TRUE(json == NULL);
    if (json != NULL) {
      my_mem_free(NULL, json);
    }
    my_conf_destroy(value);
  }
}

TEST(json_writer_handles_large_finite_numbers)
{
  my_conf_node_t* value = my_conf_new_double(NULL, 1.0e300);
  char* json;

  ASSERT_NOT_NULL(value);
  json = my_conf_to_json_str(NULL, value, false);
  ASSERT_NOT_NULL(json);
  if (json != NULL) {
    my_mem_free(NULL, json);
  }
  my_conf_destroy(value);
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
    RUN_TEST(yaml_file_loader_rejects_oversized_file_before_allocation);
    RUN_TEST(yaml_file_loader_rejects_embedded_nul);
    RUN_TEST(json_file_loader_rejects_oversized_file_before_allocation);
    RUN_TEST(json_parser_rejects_oversized_input_before_allocation);
    RUN_TEST(toml_parser_rejects_oversized_input_before_allocation);
    RUN_TEST(bson_parser_rejects_oversized_input_before_allocation);
    RUN_TEST(bson_writer_rejects_output_above_parser_budget);
    RUN_TEST(json_writer_rejects_output_above_parser_budget);
    RUN_TEST(json_parser_rejects_nonfinite_numbers);
    RUN_TEST(yaml_parser_rejects_nonfinite_numbers);
    RUN_TEST(toml_parser_rejects_nonfinite_numbers);
    RUN_TEST(toml_parser_preserves_explicit_special_numbers);
    RUN_TEST(json_writer_rejects_nonfinite_numbers);
    RUN_TEST(json_writer_handles_large_finite_numbers);
    RUN_TEST(yaml_parser_rejects_excessive_nesting);
    RUN_TEST(yaml_parser_rejects_excessive_sequence_size);
    RUN_TEST(yaml_parser_rejects_invalid_input_without_error_storage);
    RUN_TEST(yaml_parser_rejects_excessive_flow_nesting);
    RUN_TEST(yaml_parser_rejects_oversized_quoted_scalar);
    RUN_TEST(yaml_parser_rejects_oversized_flow_map_key);
    RUN_TEST(yaml_parser_rejects_duplicate_inline_map_key);
    RUN_TEST(yaml_parser_rejects_duplicate_flow_map_key);
TEST_MAIN_END()
