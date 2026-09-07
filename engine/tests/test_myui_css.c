#include "test_framework.h"

#include <stdlib.h>
#include <string.h>

#include "myui/my_css.h"
#include "myui/my_theme.h"
#include "myui/my_widget.h"

typedef struct css_alloc_state_t {
  size_t alloc_calls;
  size_t fail_at;
  int live_count;
} css_alloc_state_t;

static void* css_test_alloc(void* context, size_t size)
{
  css_alloc_state_t* state = (css_alloc_state_t*)context;
  state->alloc_calls++;
  if (state->fail_at != 0u && state->alloc_calls == state->fail_at) {
    return NULL;
  }
  void* memory = malloc(size);
  if (memory != NULL) {
    state->live_count++;
  }
  return memory;
}

static void* css_test_calloc(void* context, size_t count, size_t size)
{
  css_alloc_state_t* state = (css_alloc_state_t*)context;
  state->alloc_calls++;
  if (state->fail_at != 0u && state->alloc_calls == state->fail_at) {
    return NULL;
  }
  void* memory = calloc(count, size);
  if (memory != NULL) {
    state->live_count++;
  }
  return memory;
}

static void* css_test_realloc(void* context, void* memory, size_t size)
{
  css_alloc_state_t* state = (css_alloc_state_t*)context;
  state->alloc_calls++;
  if (state->fail_at != 0u && state->alloc_calls == state->fail_at) {
    return NULL;
  }
  void* result = realloc(memory, size);
  if (result != NULL && memory == NULL) {
    state->live_count++;
  }
  return result;
}

static void css_test_free(void* context, void* memory)
{
  css_alloc_state_t* state = (css_alloc_state_t*)context;
  if (memory != NULL) {
    state->live_count--;
  }
  free(memory);
}

typedef struct css_import_entry_t {
  const char* path;
  const char* css;
  size_t css_len;
} css_import_entry_t;

static size_t css_import_release_count;

static void css_test_release_import(void* context, const char* css, size_t len)
{
  (void)context;
  (void)css;
  (void)len;
  css_import_release_count++;
}

static bool css_test_resolve_import(void* context, const char* path,
                                    size_t path_len,
                                    my_css_import_source_t* source)
{
  const css_import_entry_t* entries = (const css_import_entry_t*)context;
  size_t i;
  if (source == NULL || path == NULL) return false;
  memset(source, 0, sizeof(*source));
  for (i = 0; entries[i].path != NULL; ++i) {
    if (strlen(entries[i].path) == path_len &&
        memcmp(entries[i].path, path, path_len) == 0) {
      source->css = entries[i].css;
      source->len = entries[i].css_len;
      source->release = css_test_release_import;
      return true;
    }
  }
  return false;
}

TEST(css_universal_selector_applies_to_any_widget)
{
  const char* css = "* { color: #112233; }";
  my_css_error_t error;
  my_css_sheet_t* sheet = my_css_parse(NULL, css, strlen(css), &error);
  my_theme_t* theme;
  my_widget_t* widget;
  const my_value_t* value;

  ASSERT_NOT_NULL(sheet);
  ASSERT_EQ(my_css_rule_count(sheet), 1u);
  ASSERT_EQ(my_css_selector(sheet != NULL ? my_css_rule(sheet, 0) : NULL, 0)
                ->widget_type[0],
            '\0');
  my_css_sheet_destroy(sheet);

  theme = my_theme_create(NULL);
  widget = my_widget_create(NULL, "any");
  ASSERT_NOT_NULL(theme);
  ASSERT_NOT_NULL(widget);
  ASSERT_EQ(my_theme_load_css(theme, css), MY_RET_OK);
  value = my_theme_get_for_widget(theme, widget, MY_STATE_NORMAL, "fg_color");
  ASSERT_NOT_NULL(value);
  ASSERT_EQ(my_value_get_uint32(value), 0x112233FFu);

  my_widget_unref(widget);
  my_theme_destroy(theme);
}

TEST(widget_local_style_write_invalidates_retained_pixels)
{
  my_widget_t* widget = my_widget_create(NULL, "styled");
  my_value_t value;

  ASSERT_NOT_NULL(widget);
  my_value_init(&value, NULL);
  ASSERT_EQ(my_value_set_uint32(&value, 0x102030FFu), MY_RET_OK);
  widget->dirty = false;
  ASSERT_EQ(my_widget_style_set(widget, MY_STATE_NORMAL, "bg_color", &value),
            MY_RET_OK);
  ASSERT_TRUE(widget->dirty);
  my_value_reset(&value);
  my_widget_unref(widget);
}

TEST(widget_local_style_rejects_invalid_request_without_allocation)
{
  my_widget_t* widget = my_widget_create(NULL, "styled");
  my_value_t value;

  ASSERT_NOT_NULL(widget);
  my_value_init(&value, NULL);
  ASSERT_EQ(my_value_set_uint32(&value, 0x102030FFu), MY_RET_OK);
  ASSERT_EQ(my_widget_style_set(widget, (my_widget_state_t)MY_STATE_COUNT,
                               "bg_color", &value),
            MY_RET_INVALID_PARAMS);
  ASSERT_TRUE(widget->local_style == NULL);
  ASSERT_EQ(my_widget_style_set(widget, MY_STATE_NORMAL,
                               "this-key-is-definitely-too-long-for-style",
                               &value),
            MY_RET_INVALID_PARAMS);
  ASSERT_TRUE(widget->local_style == NULL);
  my_value_reset(&value);
  my_widget_unref(widget);
}

TEST(widget_local_style_oom_does_not_leave_empty_style)
{
  css_alloc_state_t state = {0};
  my_allocator_t allocator = {&state, css_test_alloc, css_test_calloc,
                              css_test_realloc, css_test_free};
  my_widget_t* widget = my_widget_create(&allocator, "styled");
  my_value_t value;
  size_t calls_before_set;

  ASSERT_NOT_NULL(widget);
  my_value_init(&value, NULL);
  ASSERT_EQ(my_value_set_str(&value, "red"), MY_RET_OK);
  calls_before_set = state.alloc_calls;
  state.fail_at = calls_before_set + 2u;
  ASSERT_EQ(my_widget_style_set(widget, MY_STATE_NORMAL, "caption", &value),
            MY_RET_OOM);
  ASSERT_TRUE(widget->local_style == NULL);
  ASSERT_FALSE(widget->dirty);
  state.fail_at = 0u;
  my_value_reset(&value);
  my_widget_unref(widget);
}

TEST(css_multiple_classes_match_as_a_set)
{
  const char* css = ".primary.urgent { color: #223344; }";
  my_css_error_t error;
  my_css_sheet_t* sheet = my_css_parse(NULL, css, strlen(css), &error);
  my_theme_t* theme;
  my_widget_t* widget;
  const my_value_t* value;

  ASSERT_NOT_NULL(sheet);
  my_css_sheet_destroy(sheet);
  theme = my_theme_create(NULL);
  widget = my_widget_create(NULL, "item");
  ASSERT_NOT_NULL(theme);
  ASSERT_NOT_NULL(widget);
  ASSERT_EQ(my_widget_set_style_class(widget, "primary urgent muted"),
            MY_RET_OK);
  ASSERT_EQ(my_theme_load_css(theme, css), MY_RET_OK);
  value = my_theme_get_for_widget(theme, widget, MY_STATE_NORMAL, "fg_color");
  ASSERT_NOT_NULL(value);
  ASSERT_EQ(my_value_get_uint32(value), 0x223344FFu);
  my_widget_unref(widget);
  my_theme_destroy(theme);
}

TEST(css_same_specificity_uses_later_source_rule)
{
  const char* css =
      ".primary { color: #112233; } .urgent { color: #445566; }";
  my_theme_t* theme = my_theme_create(NULL);
  my_widget_t* widget = my_widget_create(NULL, "item");
  const my_value_t* value;

  ASSERT_NOT_NULL(theme);
  ASSERT_NOT_NULL(widget);
  ASSERT_EQ(my_widget_set_style_class(widget, "primary urgent"), MY_RET_OK);
  ASSERT_EQ(my_theme_load_css(theme, css), MY_RET_OK);
  value = my_theme_get_for_widget(theme, widget, MY_STATE_NORMAL, "fg_color");
  ASSERT_NOT_NULL(value);
  ASSERT_EQ(my_value_get_uint32(value), 0x445566FFu);
  my_widget_unref(widget);
  my_theme_destroy(theme);
}

TEST(css_specificity_beats_later_lower_specificity)
{
  const char* css =
      "button.primary { color: #112233; } .primary { color: #445566; }";
  my_theme_t* theme = my_theme_create(NULL);
  my_widget_t* widget = my_widget_create(NULL, "button");
  const my_value_t* value;

  ASSERT_NOT_NULL(theme);
  ASSERT_NOT_NULL(widget);
  widget->widget_type = "button";
  ASSERT_EQ(my_widget_set_style_class(widget, "primary"), MY_RET_OK);
  ASSERT_EQ(my_theme_load_css(theme, css), MY_RET_OK);
  value = my_theme_get_for_widget(theme, widget, MY_STATE_NORMAL,
                                  "fg_color");
  ASSERT_NOT_NULL(value);
  ASSERT_EQ(my_value_get_uint32(value), 0x112233FFu);
  my_widget_unref(widget);
  my_theme_destroy(theme);
}

TEST(css_normal_specificity_survives_state_fallback)
{
  const char* css =
      "button.primary { color: #112233; } * { color: #445566; }";
  my_theme_t* theme = my_theme_create(NULL);
  my_widget_t* widget = my_widget_create(NULL, "button");
  const my_value_t* value;

  ASSERT_NOT_NULL(theme);
  ASSERT_NOT_NULL(widget);
  widget->widget_type = "button";
  ASSERT_EQ(my_widget_set_style_class(widget, "primary"), MY_RET_OK);
  ASSERT_EQ(my_theme_load_css(theme, css), MY_RET_OK);
  value = my_theme_get_for_widget(theme, widget, MY_STATE_HOVER,
                                  "fg_color");
  ASSERT_NOT_NULL(value);
  ASSERT_EQ(my_value_get_uint32(value), 0x112233FFu);
  my_widget_unref(widget);
  my_theme_destroy(theme);
}

TEST(css_numeric_values_are_finite_and_bounded)
{
  const char* css =
      "button { border-width: +; color: rgba(1, 2, 3, -1); "
      "font-size: 2147483648; background: #010203; }";
  my_css_error_t error;
  my_css_sheet_t* sheet = my_css_parse(NULL, css, strlen(css), &error);
  const my_css_rule_t* rule;
  const my_css_decl_t* decl;

  ASSERT_NOT_NULL(sheet);
  rule = my_css_rule(sheet, 0);
  ASSERT_NOT_NULL(rule);
  ASSERT_EQ(my_css_decl_count(rule), 2u);
  decl = my_css_decl(rule, 0);
  ASSERT_NOT_NULL(decl);
  ASSERT_STR_EQ(decl->key, "fg_color");
  ASSERT_EQ(my_value_get_uint32(&decl->value), 0x01020300u);
  decl = my_css_decl(rule, 1);
  ASSERT_NOT_NULL(decl);
  ASSERT_STR_EQ(decl->key, "bg_color");
  my_css_sheet_destroy(sheet);
}

TEST(css_specificity_compares_across_selector_levels)
{
  const char* css =
      "window.primary * { color: #112233; } button { color: #445566; }";
  my_theme_t* theme = my_theme_create(NULL);
  my_widget_t* window = my_widget_create(NULL, "window");
  my_widget_t* button = my_widget_create(NULL, "button");
  const my_value_t* value;

  ASSERT_NOT_NULL(theme);
  ASSERT_NOT_NULL(window);
  ASSERT_NOT_NULL(button);
  window->widget_type = "window";
  button->widget_type = "button";
  ASSERT_EQ(my_widget_set_style_class(window, "primary"), MY_RET_OK);
  ASSERT_EQ(my_widget_add_child(window, button), MY_RET_OK);
  my_widget_unref(button);
  ASSERT_EQ(my_theme_load_css(theme, css), MY_RET_OK);
  value = my_theme_get_for_widget(theme, button, MY_STATE_NORMAL, "fg_color");
  ASSERT_NOT_NULL(value);
  ASSERT_EQ(my_value_get_uint32(value), 0x112233FFu);
  my_widget_unref(window);
  my_theme_destroy(theme);
}

TEST(theme_specificity_is_stored_per_property)
{
  my_theme_t* theme = my_theme_create(NULL);
  my_widget_t* widget = my_widget_create(NULL, "button");
  my_value_t high;
  my_value_t low;
  my_value_t fallback;
  const my_value_t* value;

  ASSERT_NOT_NULL(theme);
  ASSERT_NOT_NULL(widget);
  widget->widget_type = "button";
  ASSERT_EQ(my_widget_set_style_class(widget, "primary"), MY_RET_OK);
  my_value_init(&high, NULL);
  my_value_init(&low, NULL);
  my_value_init(&fallback, NULL);
  my_value_set_uint32(&high, 0x112233FFu);
  my_value_set_uint32(&low, 0x010203FFu);
  my_value_set_uint32(&fallback, 0x445566FFu);
  ASSERT_EQ(my_theme_set_ex3(theme, "button", NULL, "primary", NULL, false,
                             MY_STATE_NORMAL, "fg_color", &high, 101),
            MY_RET_OK);
  ASSERT_EQ(my_theme_set_ex3(theme, "button", NULL, "primary", NULL, false,
                             MY_STATE_NORMAL, "bg_color", &low, 1),
            MY_RET_OK);
  ASSERT_EQ(my_theme_set_ex3(theme, "", NULL, NULL, NULL, false,
                             MY_STATE_NORMAL, "fg_color", &fallback, 2),
            MY_RET_OK);
  value = my_theme_get_for_widget(theme, widget, MY_STATE_NORMAL, "fg_color");
  ASSERT_NOT_NULL(value);
  ASSERT_EQ(my_value_get_uint32(value), 0x112233FFu);
  my_widget_unref(widget);
  my_theme_destroy(theme);
}

TEST(css_class_selector_is_safe_without_widget_classes)
{
  const char* css = ".primary { color: #223344; }";
  my_theme_t* theme = my_theme_create(NULL);
  my_widget_t* widget = my_widget_create(NULL, "item");

  ASSERT_NOT_NULL(theme);
  ASSERT_NOT_NULL(widget);
  ASSERT_EQ(my_theme_load_css(theme, css), MY_RET_OK);
  ASSERT_TRUE(my_theme_get_for_widget(theme, widget, MY_STATE_NORMAL,
                                      "fg_color") == NULL);
  my_widget_unref(widget);
  my_theme_destroy(theme);
}

TEST(css_child_combinator_matches_only_direct_parent)
{
  const char* css = "window > button { color: #334455; }";
  my_theme_t* theme = my_theme_create(NULL);
  my_widget_t* window = my_widget_create(NULL, "window");
  my_widget_t* panel = my_widget_create(NULL, "panel");
  my_widget_t* direct = my_widget_create(NULL, "button");
  my_widget_t* nested = my_widget_create(NULL, "button");
  const my_value_t* value;

  ASSERT_NOT_NULL(theme);
  ASSERT_NOT_NULL(window);
  ASSERT_NOT_NULL(panel);
  ASSERT_NOT_NULL(direct);
  ASSERT_NOT_NULL(nested);
  window->widget_type = "window";
  panel->widget_type = "panel";
  direct->widget_type = "button";
  nested->widget_type = "button";
  ASSERT_EQ(my_widget_add_child(window, direct), MY_RET_OK);
  ASSERT_EQ(my_widget_add_child(window, panel), MY_RET_OK);
  ASSERT_EQ(my_widget_add_child(panel, nested), MY_RET_OK);
  my_widget_unref(direct);
  my_widget_unref(panel);
  my_widget_unref(nested);
  ASSERT_EQ(my_theme_load_css(theme, css), MY_RET_OK);
  value = my_theme_get_for_widget(theme, direct, MY_STATE_NORMAL, "fg_color");
  ASSERT_NOT_NULL(value);
  ASSERT_EQ(my_value_get_uint32(value), 0x334455FFu);
  ASSERT_TRUE(my_theme_get_for_widget(theme, nested, MY_STATE_NORMAL,
                                      "fg_color") == NULL);
  my_widget_unref(window);
  my_theme_destroy(theme);
}

TEST(css_child_parent_classes_match_as_a_set)
{
  const char* css = "window.primary > button { color: #334455; }";
  my_theme_t* theme = my_theme_create(NULL);
  my_widget_t* window = my_widget_create(NULL, "window");
  my_widget_t* button = my_widget_create(NULL, "button");
  const my_value_t* value;

  ASSERT_NOT_NULL(theme);
  ASSERT_NOT_NULL(window);
  ASSERT_NOT_NULL(button);
  window->widget_type = "window";
  button->widget_type = "button";
  ASSERT_EQ(my_widget_set_style_class(window, "primary urgent"), MY_RET_OK);
  ASSERT_EQ(my_widget_add_child(window, button), MY_RET_OK);
  my_widget_unref(button);
  ASSERT_EQ(my_theme_load_css(theme, css), MY_RET_OK);
  value = my_theme_get_for_widget(theme, button, MY_STATE_NORMAL, "fg_color");
  ASSERT_NOT_NULL(value);
  ASSERT_EQ(my_value_get_uint32(value), 0x334455FFu);
  my_widget_unref(window);
  my_theme_destroy(theme);
}

TEST(css_multilevel_selector_chain_matches)
{
  const char* css =
      "window.primary panel > button#submit { color: #556677; }";
  my_theme_t* theme = my_theme_create(NULL);
  my_widget_t* root = my_widget_create(NULL, "root");
  my_widget_t* window = my_widget_create(NULL, "window");
  my_widget_t* panel = my_widget_create(NULL, "panel");
  my_widget_t* button = my_widget_create(NULL, "submit");
  const my_value_t* value;

  ASSERT_NOT_NULL(theme);
  ASSERT_NOT_NULL(root);
  ASSERT_NOT_NULL(window);
  ASSERT_NOT_NULL(panel);
  ASSERT_NOT_NULL(button);
  root->widget_type = "root";
  window->widget_type = "window";
  panel->widget_type = "panel";
  button->widget_type = "button";
  ASSERT_EQ(my_widget_set_style_class(window, "primary"), MY_RET_OK);
  ASSERT_EQ(my_widget_add_child(root, window), MY_RET_OK);
  ASSERT_EQ(my_widget_add_child(window, panel), MY_RET_OK);
  ASSERT_EQ(my_widget_add_child(panel, button), MY_RET_OK);
  my_widget_unref(window);
  my_widget_unref(panel);
  my_widget_unref(button);
  ASSERT_EQ(my_theme_load_css(theme, css), MY_RET_OK);
  value = my_theme_get_for_widget(theme, button, MY_STATE_NORMAL, "fg_color");
  ASSERT_NOT_NULL(value);
  ASSERT_EQ(my_value_get_uint32(value), 0x556677FFu);
  my_widget_unref(root);
  my_theme_destroy(theme);
}

TEST(css_multilevel_direct_path_rejects_wrong_intermediate)
{
  const char* css = "window > panel > button { color: #556677; }";
  my_theme_t* theme = my_theme_create(NULL);
  my_widget_t* window = my_widget_create(NULL, "window");
  my_widget_t* wrapper = my_widget_create(NULL, "wrapper");
  my_widget_t* panel = my_widget_create(NULL, "panel");
  my_widget_t* button = my_widget_create(NULL, "button");

  ASSERT_NOT_NULL(theme);
  ASSERT_NOT_NULL(window);
  ASSERT_NOT_NULL(wrapper);
  ASSERT_NOT_NULL(panel);
  ASSERT_NOT_NULL(button);
  window->widget_type = "window";
  wrapper->widget_type = "wrapper";
  panel->widget_type = "panel";
  button->widget_type = "button";
  ASSERT_EQ(my_widget_add_child(window, wrapper), MY_RET_OK);
  ASSERT_EQ(my_widget_add_child(wrapper, panel), MY_RET_OK);
  ASSERT_EQ(my_widget_add_child(panel, button), MY_RET_OK);
  my_widget_unref(wrapper);
  my_widget_unref(panel);
  my_widget_unref(button);
  ASSERT_EQ(my_theme_load_css(theme, css), MY_RET_OK);
  ASSERT_TRUE(my_theme_get_for_widget(theme, button, MY_STATE_NORMAL,
                                      "fg_color") == NULL);
  my_widget_unref(window);
  my_theme_destroy(theme);
}

TEST(css_multilevel_ancestor_id_and_class_must_match)
{
  const char* css = "window#main.primary panel button { color: #667788; }";
  my_theme_t* theme = my_theme_create(NULL);
  my_widget_t* window = my_widget_create(NULL, "main");
  my_widget_t* panel = my_widget_create(NULL, "panel");
  my_widget_t* button = my_widget_create(NULL, "button");
  const my_value_t* value;

  ASSERT_NOT_NULL(theme);
  ASSERT_NOT_NULL(window);
  ASSERT_NOT_NULL(panel);
  ASSERT_NOT_NULL(button);
  window->widget_type = "window";
  panel->widget_type = "panel";
  button->widget_type = "button";
  ASSERT_EQ(my_widget_set_style_class(window, "primary"), MY_RET_OK);
  ASSERT_EQ(my_widget_add_child(window, panel), MY_RET_OK);
  ASSERT_EQ(my_widget_add_child(panel, button), MY_RET_OK);
  my_widget_unref(panel);
  my_widget_unref(button);
  ASSERT_EQ(my_theme_load_css(theme, css), MY_RET_OK);
  value = my_theme_get_for_widget(theme, button, MY_STATE_NORMAL, "fg_color");
  ASSERT_NOT_NULL(value);
  ASSERT_EQ(my_value_get_uint32(value), 0x667788FFu);
  ASSERT_EQ(my_widget_set_style_class(window, "secondary"), MY_RET_OK);
  ASSERT_TRUE(my_theme_get_for_widget(theme, button, MY_STATE_NORMAL,
                                      "fg_color") == NULL);
  my_widget_unref(window);
  my_theme_destroy(theme);
}

TEST(css_multilevel_specificity_beats_simple_selector)
{
  const char* css = "button { color: red; }"
                    "window.primary panel > button { color: blue; }";
  my_theme_t* theme = my_theme_create(NULL);
  my_widget_t* window = my_widget_create(NULL, "window");
  my_widget_t* panel = my_widget_create(NULL, "panel");
  my_widget_t* button = my_widget_create(NULL, "button");
  const my_value_t* value;

  ASSERT_NOT_NULL(theme);
  ASSERT_NOT_NULL(window);
  ASSERT_NOT_NULL(panel);
  ASSERT_NOT_NULL(button);
  window->widget_type = "window";
  panel->widget_type = "panel";
  button->widget_type = "button";
  ASSERT_EQ(my_widget_set_style_class(window, "primary"), MY_RET_OK);
  ASSERT_EQ(my_widget_add_child(window, panel), MY_RET_OK);
  ASSERT_EQ(my_widget_add_child(panel, button), MY_RET_OK);
  my_widget_unref(panel);
  my_widget_unref(button);
  ASSERT_EQ(my_theme_load_css(theme, css), MY_RET_OK);
  value = my_theme_get_for_widget(theme, button, MY_STATE_NORMAL, "fg_color");
  ASSERT_NOT_NULL(value);
  ASSERT_EQ(my_value_get_uint32(value), 0x0000FFFFu);
  my_widget_unref(window);
  my_theme_destroy(theme);
}

TEST(css_rejects_selector_paths_over_depth_limit)
{
  const char* css = "a b c d e f { color: red; }";
  my_css_error_t error;

  ASSERT_TRUE(my_css_parse(NULL, css, strlen(css), &error) == NULL);
  ASSERT_TRUE(error.msg[0] != '\0');
}

TEST(css_rejects_dangling_and_repeated_combinators)
{
  const char* dangling = "window > { color: #334455; }";
  const char* repeated = "window > > button { color: #334455; }";
  my_css_error_t error;
  my_css_sheet_t* sheet;

  sheet = my_css_parse(NULL, dangling, strlen(dangling), &error);
  ASSERT_TRUE(sheet == NULL);
  ASSERT_TRUE(error.msg[0] != '\0');
  sheet = my_css_parse(NULL, repeated, strlen(repeated), &error);
  ASSERT_TRUE(sheet == NULL);
  ASSERT_TRUE(error.msg[0] != '\0');
}

TEST(css_rejects_adjacent_selector_tokens_without_combinator)
{
  const char* css = "window* { color: #334455; }";
  my_css_error_t error;
  my_css_sheet_t* sheet = my_css_parse(NULL, css, strlen(css), &error);

  ASSERT_TRUE(sheet == NULL);
  ASSERT_TRUE(error.msg[0] != '\0');
}

TEST(css_comments_preserve_descendant_separator)
{
  const char* css = "window/**/button { color: #334455; }";
  my_css_error_t error;
  my_css_sheet_t* sheet = my_css_parse(NULL, css, strlen(css), &error);
  const my_css_selector_t* selector;

  ASSERT_NOT_NULL(sheet);
  selector = my_css_selector(my_css_rule(sheet, 0), 0);
  ASSERT_NOT_NULL(selector);
  ASSERT_STR_EQ(selector->ancestor_type, "window");
  ASSERT_FALSE(selector->ancestor_direct);
  my_css_sheet_destroy(sheet);
}

TEST(css_unsupported_at_rules_ignore_braces_in_strings_and_comments)
{
  const char* css =
      "@supports (content: \"}\") { /* } */ .ignored { color: red; } }"
      "button { color: #123456; }";
  my_css_error_t error;
  my_css_sheet_t* sheet = my_css_parse(NULL, css, strlen(css), &error);
  const my_css_decl_t* decl;

  ASSERT_NOT_NULL(sheet);
  ASSERT_EQ(my_css_rule_count(sheet), 1u);
  decl = my_css_decl(my_css_rule(sheet, 0), 0);
  ASSERT_NOT_NULL(decl);
  ASSERT_STR_EQ(decl->key, "fg_color");
  ASSERT_EQ(my_value_get_uint32(&decl->value), 0x123456FFu);
  my_css_sheet_destroy(sheet);
}

TEST(css_import_resolver_flattens_sources_in_source_order)
{
  const css_import_entry_t entries[] = {
      {"buttons.css", "button { color: red; }", 22u}, {NULL, NULL, 0u}};
  const char* css =
      "@import \"buttons.css\"; button { color: blue; }";
  my_css_parse_options_t options = {0};
  my_css_error_t error = {0};
  my_css_sheet_t* sheet;

  options.flags = MY_CSS_PARSE_STRICT_AT_RULES;
  options.resolve_import = css_test_resolve_import;
  options.import_context = (void*)entries;
  css_import_release_count = 0u;
  sheet = my_css_parse_with_options(NULL, css, strlen(css), &options, &error);
  ASSERT_NOT_NULL(sheet);
  ASSERT_EQ(my_css_rule_count(sheet), 2u);
  my_css_sheet_destroy(sheet);
  ASSERT_EQ(css_import_release_count, 1u);
}

TEST(css_import_without_resolver_is_rejected_in_strict_mode)
{
  const char* css = "@import \"buttons.css\"; button { color: blue; }";
  my_css_parse_options_t options = {MY_CSS_PARSE_STRICT_AT_RULES, NULL, NULL,
                                    NULL};
  my_css_error_t error = {0};

  ASSERT_TRUE(my_css_parse_with_options(NULL, css, strlen(css), &options,
                                        &error) == NULL);
  ASSERT_EQ(error.code, MY_CSS_ERROR_UNSUPPORTED_FEATURE);
  ASSERT_EQ(error.capability, (uint32_t)MY_CSS_FEATURE_IMPORTS);
}

TEST(css_import_cycle_and_depth_are_bounded)
{
  const css_import_entry_t entries[] = {
      {"a.css", "@import \"a.css\";", 16u}, {NULL, NULL, 0u}};
  const char* css = "@import \"a.css\";";
  my_css_parse_options_t options = {0};
  my_css_error_t error = {0};

  options.flags = MY_CSS_PARSE_STRICT_AT_RULES;
  options.resolve_import = css_test_resolve_import;
  options.import_context = (void*)entries;
  ASSERT_TRUE(my_css_parse_with_options(NULL, css, strlen(css), &options,
                                        &error) == NULL);
  ASSERT_EQ(error.code, MY_CSS_ERROR_IMPORT);
}

TEST(css_import_rejects_absolute_and_traversal_paths)
{
  const css_import_entry_t entries[] = {{"unused", "", 0u},
                                        {NULL, NULL, 0u}};
  const char* paths[] = {"/etc/theme.css", "../theme.css", "a/../../theme.css"};
  my_css_parse_options_t options = {0};
  my_css_error_t error = {0};
  size_t i;

  options.flags = MY_CSS_PARSE_STRICT_AT_RULES;
  options.resolve_import = css_test_resolve_import;
  options.import_context = (void*)entries;
  for (i = 0u; i < sizeof(paths) / sizeof(paths[0]); ++i) {
    char css[MY_CSS_MAX_IMPORT_PATH_BYTES + 32u];
    int written = snprintf(css, sizeof(css), "@import \"%s\";", paths[i]);
    ASSERT_TRUE(written > 0 && (size_t)written < sizeof(css));
    memset(&error, 0, sizeof(error));
    ASSERT_TRUE(my_css_parse_with_options(NULL, css, (size_t)written,
                                          &options, &error) == NULL);
    ASSERT_EQ(error.code, MY_CSS_ERROR_IMPORT);
  }
}

TEST(css_scope_applies_rules_only_inside_root)
{
  const char* css = "@scope panel { button { color: red; } }";
  my_css_error_t error = {0};
  my_css_sheet_t* sheet = my_css_parse_ex(
      NULL, css, strlen(css), MY_CSS_PARSE_STRICT_AT_RULES, &error);
  my_theme_t* theme = my_theme_create(NULL);
  my_widget_t* panel = my_widget_create(NULL, "panel");
  my_widget_t* inside = my_widget_create(NULL, "inside");
  my_widget_t* outside = my_widget_create(NULL, "outside");
  const my_value_t* value;

  ASSERT_NOT_NULL(sheet);
  ASSERT_EQ(my_css_rule_count(sheet), 1u);
  ASSERT_EQ(my_css_selector(my_css_rule(sheet, 0u), 0u)->ancestor_count, 1u);
  my_css_sheet_destroy(sheet);
  ASSERT_NOT_NULL(theme);
  ASSERT_NOT_NULL(panel);
  ASSERT_NOT_NULL(inside);
  ASSERT_NOT_NULL(outside);
  panel->widget_type = "panel";
  inside->widget_type = "button";
  outside->widget_type = "button";
  ASSERT_EQ(my_widget_add_child(panel, inside), MY_RET_OK);
  ASSERT_EQ(my_theme_load_css_ex(theme, css, MY_CSS_PARSE_STRICT_AT_RULES),
            MY_RET_OK);
  value = my_theme_get_for_widget(theme, inside, MY_STATE_NORMAL, "fg_color");
  ASSERT_NOT_NULL(value);
  ASSERT_EQ(my_value_get_uint32(value), 0xFF0000FFu);
  value = my_theme_get_for_widget(theme, outside, MY_STATE_NORMAL, "fg_color");
  ASSERT_TRUE(value == NULL);
  my_widget_unref(outside);
  my_widget_unref(inside);
  my_widget_unref(panel);
  my_theme_destroy(theme);
}

TEST(css_scope_accepts_to_clause_and_rejects_malformed_limit)
{
  const char* to_clause = "@scope panel to dialog { button { color: red; } }";
  const char* malformed_limit =
      "@scope panel to :hover { button { color: red; } }";
  const char* too_deep =
      "@scope a { @scope b { @scope c { @scope d {"
      "@scope e { button { color: red; } } } } } }";
  my_css_error_t error = {0};

  my_css_sheet_t* sheet = my_css_parse_ex(
      NULL, to_clause, strlen(to_clause), MY_CSS_PARSE_STRICT_AT_RULES,
      &error);
  ASSERT_NOT_NULL(sheet);
  ASSERT_EQ(my_css_rule_count(sheet), 1u);
  ASSERT_EQ(my_css_selector(my_css_rule(sheet, 0u), 0u)->scope_limit_count,
            1u);
  ASSERT_STR_EQ(my_css_selector(my_css_rule(sheet, 0u), 0u)
                    ->scope_limits[0]
                    .widget_type,
                "dialog");
  my_css_sheet_destroy(sheet);
  memset(&error, 0, sizeof(error));
  ASSERT_TRUE(my_css_parse_ex(NULL, malformed_limit, strlen(malformed_limit),
                              MY_CSS_PARSE_STRICT_AT_RULES, &error) == NULL);
  ASSERT_EQ(error.code, MY_CSS_ERROR_SYNTAX);
  ASSERT_EQ(error.capability, (uint32_t)MY_CSS_FEATURE_SCOPE);
  memset(&error, 0, sizeof(error));
  ASSERT_TRUE(my_css_parse_ex(NULL, too_deep, strlen(too_deep),
                              MY_CSS_PARSE_STRICT_AT_RULES, &error) == NULL);
  ASSERT_EQ(error.code, MY_CSS_ERROR_UNSUPPORTED_FEATURE);
  ASSERT_EQ(error.capability, (uint32_t)MY_CSS_FEATURE_SCOPE);
}

TEST(css_scope_to_clause_accepts_implicit_root)
{
  const char* css = "@scope to dialog { button { color: red; } }";
  my_css_error_t error = {0};
  my_css_sheet_t* sheet = my_css_parse_ex(
      NULL, css, strlen(css), MY_CSS_PARSE_STRICT_AT_RULES, &error);
  const my_css_selector_t* selector;

  ASSERT_NOT_NULL(sheet);
  ASSERT_EQ(my_css_rule_count(sheet), 1u);
  selector = my_css_selector(my_css_rule(sheet, 0u), 0u);
  ASSERT_NOT_NULL(selector);
  ASSERT_EQ(selector->ancestor_count, 0u);
  ASSERT_EQ(selector->scope_limit_count, 1u);
  ASSERT_EQ(selector->scope_limit_root_index[0], MY_CSS_MAX_ANCESTORS);
  ASSERT_STR_EQ(selector->scope_limits[0].widget_type, "dialog");
  my_css_sheet_destroy(sheet);
}

TEST(css_scope_implicit_root_to_clause_excludes_boundary)
{
  const char* css = "@scope to dialog { button { color: red; } }";
  my_theme_t* theme = my_theme_create(NULL);
  my_widget_t* allowed = my_widget_create(NULL, "allowed");
  my_widget_t* dialog = my_widget_create(NULL, "dialog");
  my_widget_t* blocked = my_widget_create(NULL, "blocked");
  const my_value_t* value;

  ASSERT_NOT_NULL(theme);
  ASSERT_NOT_NULL(allowed);
  ASSERT_NOT_NULL(dialog);
  ASSERT_NOT_NULL(blocked);
  allowed->widget_type = "button";
  dialog->widget_type = "dialog";
  blocked->widget_type = "button";
  ASSERT_EQ(my_widget_add_child(dialog, blocked), MY_RET_OK);
  ASSERT_EQ(my_theme_load_css_ex(theme, css, MY_CSS_PARSE_STRICT_AT_RULES),
            MY_RET_OK);
  value = my_theme_get_for_widget(theme, allowed, MY_STATE_NORMAL,
                                  "fg_color");
  ASSERT_NOT_NULL(value);
  ASSERT_EQ(my_value_get_uint32(value), 0xFF0000FFu);
  value = my_theme_get_for_widget(theme, blocked, MY_STATE_NORMAL,
                                  "fg_color");
  ASSERT_TRUE(value == NULL);
  my_widget_unref(blocked);
  my_widget_unref(dialog);
  my_widget_unref(allowed);
  my_theme_destroy(theme);
}

TEST(css_scope_implicit_root_rejects_malformed_limit)
{
  const char* malformed[] = {
      "@scope to :hover { button { color: red; } }",
      "@scope to { button { color: red; } }",
      "@scope to dialog extra { button { color: red; } }",
      "@scope to dialog, { button { color: red; } }",
      "@scope to a, b, c, d, e { button { color: red; } }"};
  my_css_error_t error = {0};
  size_t i;

  for (i = 0u; i < sizeof(malformed) / sizeof(malformed[0]); ++i) {
    memset(&error, 0, sizeof(error));
    ASSERT_TRUE(my_css_parse_ex(NULL, malformed[i], strlen(malformed[i]),
                                MY_CSS_PARSE_STRICT_AT_RULES,
                                &error) == NULL);
    ASSERT_EQ(error.code, MY_CSS_ERROR_SYNTAX);
    ASSERT_EQ(error.capability, (uint32_t)MY_CSS_FEATURE_SCOPE);
  }
}

TEST(css_scope_rejects_malformed_root_with_scope_capability)
{
  const char* malformed[] = {
      "@scope :hover { button { color: red; } }",
      "@scope panel:hover { button { color: red; } }"};
  my_css_error_t error = {0};
  size_t i;

  for (i = 0u; i < sizeof(malformed) / sizeof(malformed[0]); ++i) {
    memset(&error, 0, sizeof(error));
    ASSERT_TRUE(my_css_parse_ex(NULL, malformed[i], strlen(malformed[i]),
                                MY_CSS_PARSE_STRICT_AT_RULES,
                                &error) == NULL);
    ASSERT_EQ(error.code, MY_CSS_ERROR_SYNTAX);
    ASSERT_EQ(error.capability, (uint32_t)MY_CSS_FEATURE_SCOPE);
  }
}

TEST(css_scope_to_clause_supports_universal_limit)
{
  const char* css = "@scope panel to * { button { color: red; } }";
  my_css_error_t error = {0};
  my_css_sheet_t* sheet = my_css_parse_ex(
      NULL, css, strlen(css), MY_CSS_PARSE_STRICT_AT_RULES, &error);
  const my_css_selector_t* selector;

  ASSERT_NOT_NULL(sheet);
  selector = my_css_selector(my_css_rule(sheet, 0u), 0u);
  ASSERT_NOT_NULL(selector);
  ASSERT_EQ(selector->scope_limit_count, 1u);
  ASSERT_EQ(selector->scope_limits[0].widget_type[0], '\0');
  ASSERT_EQ(selector->scope_limits[0].id[0], '\0');
  ASSERT_EQ(selector->scope_limits[0].style_class[0], '\0');
  my_css_sheet_destroy(sheet);
}

TEST(css_scope_universal_limit_excludes_every_ancestor_boundary)
{
  const char* css = "@scope panel to * { button { color: red; } }";
  my_theme_t* theme = my_theme_create(NULL);
  my_widget_t* panel = my_widget_create(NULL, "panel");
  my_widget_t* button = my_widget_create(NULL, "button");
  const my_value_t* value;

  ASSERT_NOT_NULL(theme);
  ASSERT_NOT_NULL(panel);
  ASSERT_NOT_NULL(button);
  panel->widget_type = "panel";
  button->widget_type = "button";
  ASSERT_EQ(my_widget_add_child(panel, button), MY_RET_OK);
  ASSERT_EQ(my_theme_load_css_ex(theme, css, MY_CSS_PARSE_STRICT_AT_RULES),
            MY_RET_OK);
  value = my_theme_get_for_widget(theme, button, MY_STATE_NORMAL,
                                  "fg_color");
  ASSERT_TRUE(value == NULL);
  my_widget_unref(button);
  my_widget_unref(panel);
  my_theme_destroy(theme);
}

TEST(css_scope_to_clause_supports_compound_limit)
{
  const char* css = "@scope .panel to dialog.stop { button { color: red; } }";
  my_theme_t* theme = my_theme_create(NULL);
  my_widget_t* panel = my_widget_create(NULL, "panel");
  my_widget_t* allowed = my_widget_create(NULL, "allowed");
  my_widget_t* boundary = my_widget_create(NULL, "boundary");
  my_widget_t* blocked = my_widget_create(NULL, "blocked");
  const my_value_t* value;

  ASSERT_NOT_NULL(theme);
  ASSERT_NOT_NULL(panel);
  ASSERT_NOT_NULL(allowed);
  ASSERT_NOT_NULL(boundary);
  ASSERT_NOT_NULL(blocked);
  panel->widget_type = "panel";
  allowed->widget_type = "button";
  boundary->widget_type = "dialog";
  blocked->widget_type = "button";
  ASSERT_EQ(my_widget_set_style_class(panel, "panel"), MY_RET_OK);
  ASSERT_EQ(my_widget_set_style_class(boundary, "stop"), MY_RET_OK);
  ASSERT_EQ(my_widget_add_child(panel, allowed), MY_RET_OK);
  ASSERT_EQ(my_widget_add_child(panel, boundary), MY_RET_OK);
  ASSERT_EQ(my_widget_add_child(boundary, blocked), MY_RET_OK);
  ASSERT_EQ(my_theme_load_css_ex(theme, css, MY_CSS_PARSE_STRICT_AT_RULES),
            MY_RET_OK);
  value = my_theme_get_for_widget(theme, allowed, MY_STATE_NORMAL,
                                  "fg_color");
  ASSERT_NOT_NULL(value);
  value = my_theme_get_for_widget(theme, blocked, MY_STATE_NORMAL,
                                  "fg_color");
  ASSERT_TRUE(value == NULL);
  my_widget_unref(blocked);
  my_widget_unref(boundary);
  my_widget_unref(allowed);
  my_widget_unref(panel);
  my_theme_destroy(theme);
}

TEST(css_scope_to_clause_supports_limit_selector_list)
{
  const char* css =
      "@scope panel to dialog, .stop { button { color: red; } }";
  my_css_error_t error = {0};
  my_css_sheet_t* sheet = my_css_parse_ex(
      NULL, css, strlen(css), MY_CSS_PARSE_STRICT_AT_RULES, &error);
  const my_css_selector_t* selector;

  ASSERT_NOT_NULL(sheet);
  selector = my_css_selector(my_css_rule(sheet, 0u), 0u);
  ASSERT_NOT_NULL(selector);
  ASSERT_EQ(selector->scope_limit_count, 2u);
  ASSERT_STR_EQ(selector->scope_limits[0].widget_type, "dialog");
  ASSERT_STR_EQ(selector->scope_limits[1].style_class, "stop");
  my_css_sheet_destroy(sheet);
}

TEST(css_scope_limit_selector_list_excludes_any_matching_boundary)
{
  const char* css =
      "@scope panel to dialog, .stop { button { color: red; } }";
  my_theme_t* theme = my_theme_create(NULL);
  my_widget_t* panel = my_widget_create(NULL, "panel");
  my_widget_t* allowed = my_widget_create(NULL, "allowed");
  my_widget_t* dialog = my_widget_create(NULL, "dialog");
  my_widget_t* dialog_child = my_widget_create(NULL, "dialog-child");
  my_widget_t* stop = my_widget_create(NULL, "stop");
  my_widget_t* stop_child = my_widget_create(NULL, "stop-child");
  const my_value_t* value;

  ASSERT_NOT_NULL(theme);
  ASSERT_NOT_NULL(panel);
  ASSERT_NOT_NULL(allowed);
  ASSERT_NOT_NULL(dialog);
  ASSERT_NOT_NULL(dialog_child);
  ASSERT_NOT_NULL(stop);
  ASSERT_NOT_NULL(stop_child);
  panel->widget_type = "panel";
  allowed->widget_type = "button";
  dialog->widget_type = "dialog";
  dialog_child->widget_type = "button";
  stop->widget_type = "container";
  stop_child->widget_type = "button";
  ASSERT_EQ(my_widget_set_style_class(stop, "stop"), MY_RET_OK);
  ASSERT_EQ(my_widget_add_child(panel, allowed), MY_RET_OK);
  ASSERT_EQ(my_widget_add_child(panel, dialog), MY_RET_OK);
  ASSERT_EQ(my_widget_add_child(dialog, dialog_child), MY_RET_OK);
  ASSERT_EQ(my_widget_add_child(panel, stop), MY_RET_OK);
  ASSERT_EQ(my_widget_add_child(stop, stop_child), MY_RET_OK);
  ASSERT_EQ(my_theme_load_css_ex(theme, css, MY_CSS_PARSE_STRICT_AT_RULES),
            MY_RET_OK);
  value = my_theme_get_for_widget(theme, allowed, MY_STATE_NORMAL,
                                  "fg_color");
  ASSERT_NOT_NULL(value);
  value = my_theme_get_for_widget(theme, dialog_child, MY_STATE_NORMAL,
                                  "fg_color");
  ASSERT_TRUE(value == NULL);
  value = my_theme_get_for_widget(theme, stop_child, MY_STATE_NORMAL,
                                  "fg_color");
  ASSERT_TRUE(value == NULL);
  my_widget_unref(stop_child);
  my_widget_unref(stop);
  my_widget_unref(dialog_child);
  my_widget_unref(dialog);
  my_widget_unref(allowed);
  my_widget_unref(panel);
  my_theme_destroy(theme);
}

TEST(theme_scope_implicit_root_api_boundary_is_bounded)
{
  my_theme_t* theme = my_theme_create(NULL);
  my_theme_ancestor_t limit = {{0}, {0}, {0}};
  my_value_t value;
  my_widget_t* allowed = my_widget_create(NULL, "allowed");
  my_widget_t* dialog = my_widget_create(NULL, "dialog");
  my_widget_t* blocked = my_widget_create(NULL, "blocked");
  size_t root_index = MY_THEME_SCOPE_ROOT_IMPLICIT;
  size_t invalid_root_index = MY_THEME_SCOPE_ROOT_IMPLICIT + 1u;
  const my_value_t* result;

  ASSERT_NOT_NULL(theme);
  ASSERT_NOT_NULL(allowed);
  ASSERT_NOT_NULL(dialog);
  ASSERT_NOT_NULL(blocked);
  snprintf(limit.widget_type, sizeof(limit.widget_type), "%s", "dialog");
  allowed->widget_type = "button";
  dialog->widget_type = "dialog";
  blocked->widget_type = "button";
  ASSERT_EQ(my_widget_add_child(dialog, blocked), MY_RET_OK);
  my_value_init(&value, NULL);
  ASSERT_EQ(my_value_set_uint32(&value, 0xFF0000FFu), MY_RET_OK);
  ASSERT_EQ(my_theme_set_ex5(theme, "button", NULL, NULL, NULL, 0u, NULL,
                             &limit, 1u, &root_index, MY_STATE_NORMAL,
                             "fg_color", &value, 0), MY_RET_OK);
  ASSERT_EQ(my_theme_set_ex5(theme, "label", NULL, NULL, NULL, 0u, NULL,
                             &limit, 1u, &invalid_root_index, MY_STATE_NORMAL,
                             "fg_color", &value, 0),
            MY_RET_INVALID_PARAMS);
  result = my_theme_get_for_widget(theme, allowed, MY_STATE_NORMAL,
                                   "fg_color");
  ASSERT_NOT_NULL(result);
  result = my_theme_get_for_widget(theme, blocked, MY_STATE_NORMAL,
                                   "fg_color");
  ASSERT_TRUE(result == NULL);
  my_widget_unref(blocked);
  my_widget_unref(dialog);
  my_widget_unref(allowed);
  my_theme_destroy(theme);
}

TEST(css_scope_nested_implicit_and_explicit_boundaries)
{
  const char* css =
      "@scope to outer-stop {"
      "@scope inner to inner-stop { button { color: red; } } }";
  my_theme_t* theme = my_theme_create(NULL);
  my_widget_t* inner = my_widget_create(NULL, "inner");
  my_widget_t* allowed = my_widget_create(NULL, "allowed");
  my_widget_t* inner_stop = my_widget_create(NULL, "inner-stop");
  my_widget_t* blocked_inner = my_widget_create(NULL, "blocked-inner");
  my_widget_t* outer_stop = my_widget_create(NULL, "outer-stop");
  my_widget_t* blocked_outer = my_widget_create(NULL, "blocked-outer");
  const my_value_t* value;

  ASSERT_NOT_NULL(theme);
  ASSERT_NOT_NULL(inner);
  ASSERT_NOT_NULL(allowed);
  ASSERT_NOT_NULL(inner_stop);
  ASSERT_NOT_NULL(blocked_inner);
  ASSERT_NOT_NULL(outer_stop);
  ASSERT_NOT_NULL(blocked_outer);
  inner->widget_type = "inner";
  allowed->widget_type = "button";
  inner_stop->widget_type = "inner-stop";
  blocked_inner->widget_type = "button";
  outer_stop->widget_type = "outer-stop";
  blocked_outer->widget_type = "button";
  ASSERT_EQ(my_widget_add_child(inner, allowed), MY_RET_OK);
  ASSERT_EQ(my_widget_add_child(inner, inner_stop), MY_RET_OK);
  ASSERT_EQ(my_widget_add_child(inner_stop, blocked_inner), MY_RET_OK);
  ASSERT_EQ(my_widget_add_child(outer_stop, blocked_outer), MY_RET_OK);
  ASSERT_EQ(my_theme_load_css_ex(theme, css, MY_CSS_PARSE_STRICT_AT_RULES),
            MY_RET_OK);
  value = my_theme_get_for_widget(theme, allowed, MY_STATE_NORMAL,
                                  "fg_color");
  ASSERT_NOT_NULL(value);
  value = my_theme_get_for_widget(theme, blocked_inner, MY_STATE_NORMAL,
                                  "fg_color");
  ASSERT_TRUE(value == NULL);
  value = my_theme_get_for_widget(theme, blocked_outer, MY_STATE_NORMAL,
                                  "fg_color");
  ASSERT_TRUE(value == NULL);
  my_widget_unref(blocked_outer);
  my_widget_unref(outer_stop);
  my_widget_unref(blocked_inner);
  my_widget_unref(inner_stop);
  my_widget_unref(allowed);
  my_widget_unref(inner);
  my_theme_destroy(theme);
}

TEST(css_scope_accepts_class_id_universal_and_implicit_roots)
{
  const char* css =
      "@scope .panel-root { button { color: red; } }"
      "@scope #application { label { color: blue; } }"
      "@scope * { edit { color: green; } }"
      "@scope { slider { color: white; } }";
  my_css_error_t error = {0};
  my_css_sheet_t* sheet = my_css_parse_ex(
      NULL, css, strlen(css), MY_CSS_PARSE_STRICT_AT_RULES, &error);

  ASSERT_NOT_NULL(sheet);
  ASSERT_EQ(my_css_rule_count(sheet), 4u);
  ASSERT_EQ(my_css_selector(my_css_rule(sheet, 0u), 0u)->ancestor_count, 1u);
  ASSERT_STR_EQ(my_css_selector(my_css_rule(sheet, 0u), 0u)
                    ->ancestors[0]
                    .style_class,
                "panel-root");
  ASSERT_STR_EQ(my_css_selector(my_css_rule(sheet, 1u), 0u)->ancestors[0].id,
                "application");
  ASSERT_EQ(my_css_selector(my_css_rule(sheet, 2u), 0u)->ancestor_count, 1u);
  ASSERT_EQ(my_css_selector(my_css_rule(sheet, 3u), 0u)->ancestor_count, 0u);
  my_css_sheet_destroy(sheet);
}

TEST(css_scope_class_and_id_roots_match_theme_ancestors)
{
  const char* css =
      "@scope .panel-root { button { color: red; } }"
      "@scope #application { label { color: blue; } }";
  my_theme_t* theme = my_theme_create(NULL);
  my_widget_t* root = my_widget_create(NULL, "application");
  my_widget_t* panel = my_widget_create(NULL, "panel");
  my_widget_t* button = my_widget_create(NULL, "button");
  my_widget_t* label = my_widget_create(NULL, "label");
  const my_value_t* value;

  ASSERT_NOT_NULL(theme);
  ASSERT_NOT_NULL(root);
  ASSERT_NOT_NULL(panel);
  ASSERT_NOT_NULL(button);
  ASSERT_NOT_NULL(label);
  root->widget_type = "window";
  panel->widget_type = "panel";
  button->widget_type = "button";
  label->widget_type = "label";
  ASSERT_EQ(my_widget_set_style_class(panel, "panel-root"), MY_RET_OK);
  ASSERT_EQ(my_widget_add_child(root, panel), MY_RET_OK);
  ASSERT_EQ(my_widget_add_child(panel, button), MY_RET_OK);
  ASSERT_EQ(my_widget_add_child(root, label), MY_RET_OK);
  ASSERT_EQ(my_theme_load_css_ex(theme, css, MY_CSS_PARSE_STRICT_AT_RULES),
            MY_RET_OK);

  value = my_theme_get_for_widget(theme, button, MY_STATE_NORMAL, "fg_color");
  ASSERT_NOT_NULL(value);
  ASSERT_EQ(my_value_get_uint32(value), 0xFF0000FFu);
  value = my_theme_get_for_widget(theme, label, MY_STATE_NORMAL, "fg_color");
  ASSERT_NOT_NULL(value);
  ASSERT_EQ(my_value_get_uint32(value), 0x0000FFFFu);
  my_widget_unref(label);
  my_widget_unref(button);
  my_widget_unref(panel);
  my_widget_unref(root);
  my_theme_destroy(theme);
}

TEST(css_scope_universal_root_matches_theme_ancestors)
{
  const char* css = "@scope * { button { color: red; } }";
  my_theme_t* theme = my_theme_create(NULL);
  my_widget_t* root = my_widget_create(NULL, "root");
  my_widget_t* button = my_widget_create(NULL, "button");
  const my_value_t* value;

  ASSERT_NOT_NULL(theme);
  ASSERT_NOT_NULL(root);
  ASSERT_NOT_NULL(button);
  root->widget_type = "window";
  button->widget_type = "button";
  ASSERT_EQ(my_widget_add_child(root, button), MY_RET_OK);
  ASSERT_EQ(my_theme_load_css_ex(theme, css, MY_CSS_PARSE_STRICT_AT_RULES),
            MY_RET_OK);
  value = my_theme_get_for_widget(theme, button, MY_STATE_NORMAL,
                                  "fg_color");
  ASSERT_NOT_NULL(value);
  ASSERT_EQ(my_value_get_uint32(value), 0xFF0000FFu);
  my_widget_unref(button);
  my_widget_unref(root);
  my_theme_destroy(theme);
}

TEST(css_scope_composes_with_media_supports_and_layer)
{
  const char* css =
      "@layer components { @media screen and (min-width: 800px) {"
      "@supports (color: red) { @scope .panel { button { color: red; } } }"
      "} }";
  my_css_media_context_t media = {1024u, 768u, true, false, false, 0u};
  my_css_error_t error = {0};
  my_css_sheet_t* sheet = my_css_parse_media_ex(
      NULL, css, strlen(css), MY_CSS_PARSE_STRICT_AT_RULES, &media, &error);
  const my_css_selector_t* selector;

  ASSERT_NOT_NULL(sheet);
  ASSERT_EQ(my_css_rule_count(sheet), 1u);
  selector = my_css_selector(my_css_rule(sheet, 0u), 0u);
  ASSERT_NOT_NULL(selector);
  ASSERT_EQ(selector->ancestor_count, 1u);
  ASSERT_STR_EQ(selector->ancestors[0].style_class, "panel");
  ASSERT_EQ(my_css_rule(sheet, 0u)->layer_order, 0u);
  my_css_sheet_destroy(sheet);
}

TEST(css_scope_to_clause_excludes_nested_boundary)
{
  const char* css = "@scope panel to dialog { button { color: red; } }";
  my_theme_t* theme = my_theme_create(NULL);
  my_widget_t* panel = my_widget_create(NULL, "panel");
  my_widget_t* allowed = my_widget_create(NULL, "allowed");
  my_widget_t* dialog = my_widget_create(NULL, "dialog");
  my_widget_t* blocked = my_widget_create(NULL, "blocked");
  const my_value_t* value;

  ASSERT_NOT_NULL(theme);
  ASSERT_NOT_NULL(panel);
  ASSERT_NOT_NULL(allowed);
  ASSERT_NOT_NULL(dialog);
  ASSERT_NOT_NULL(blocked);
  panel->widget_type = "panel";
  allowed->widget_type = "button";
  dialog->widget_type = "dialog";
  blocked->widget_type = "button";
  ASSERT_EQ(my_widget_add_child(panel, allowed), MY_RET_OK);
  ASSERT_EQ(my_widget_add_child(panel, dialog), MY_RET_OK);
  ASSERT_EQ(my_widget_add_child(dialog, blocked), MY_RET_OK);
  ASSERT_EQ(my_theme_load_css_ex(theme, css, MY_CSS_PARSE_STRICT_AT_RULES),
            MY_RET_OK);

  value = my_theme_get_for_widget(theme, allowed, MY_STATE_NORMAL,
                                  "fg_color");
  ASSERT_NOT_NULL(value);
  ASSERT_EQ(my_value_get_uint32(value), 0xFF0000FFu);
  value = my_theme_get_for_widget(theme, blocked, MY_STATE_NORMAL,
                                  "fg_color");
  ASSERT_TRUE(value == NULL);
  my_widget_unref(blocked);
  my_widget_unref(dialog);
  my_widget_unref(allowed);
  my_widget_unref(panel);
  my_theme_destroy(theme);
}

TEST(css_scope_to_clause_excludes_boundary_element_itself)
{
  const char* css = "@scope panel to .stop { button { color: red; } }";
  my_theme_t* theme = my_theme_create(NULL);
  my_widget_t* panel = my_widget_create(NULL, "panel");
  my_widget_t* boundary = my_widget_create(NULL, "boundary");
  my_widget_t* child = my_widget_create(NULL, "child");
  const my_value_t* value;

  ASSERT_NOT_NULL(theme);
  ASSERT_NOT_NULL(panel);
  ASSERT_NOT_NULL(boundary);
  ASSERT_NOT_NULL(child);
  panel->widget_type = "panel";
  boundary->widget_type = "button";
  child->widget_type = "button";
  ASSERT_EQ(my_widget_set_style_class(boundary, "stop"), MY_RET_OK);
  ASSERT_EQ(my_widget_add_child(panel, boundary), MY_RET_OK);
  ASSERT_EQ(my_widget_add_child(boundary, child), MY_RET_OK);
  ASSERT_EQ(my_theme_load_css_ex(theme, css, MY_CSS_PARSE_STRICT_AT_RULES),
            MY_RET_OK);

  value = my_theme_get_for_widget(theme, boundary, MY_STATE_NORMAL,
                                  "fg_color");
  ASSERT_TRUE(value == NULL);
  value = my_theme_get_for_widget(theme, child, MY_STATE_NORMAL,
                                  "fg_color");
  ASSERT_TRUE(value == NULL);
  my_widget_unref(child);
  my_widget_unref(boundary);
  my_widget_unref(panel);
  my_theme_destroy(theme);
}

TEST(css_scope_to_clause_excludes_root_when_limit_matches_root)
{
  const char* css = "@scope panel to panel { button { color: red; } }";
  my_theme_t* theme = my_theme_create(NULL);
  my_widget_t* panel = my_widget_create(NULL, "panel");
  my_widget_t* button = my_widget_create(NULL, "button");
  const my_value_t* value;

  ASSERT_NOT_NULL(theme);
  ASSERT_NOT_NULL(panel);
  ASSERT_NOT_NULL(button);
  panel->widget_type = "panel";
  button->widget_type = "button";
  ASSERT_EQ(my_widget_add_child(panel, button), MY_RET_OK);
  ASSERT_EQ(my_theme_load_css_ex(theme, css, MY_CSS_PARSE_STRICT_AT_RULES),
            MY_RET_OK);
  value = my_theme_get_for_widget(theme, button, MY_STATE_NORMAL,
                                  "fg_color");
  ASSERT_TRUE(value == NULL);
  my_widget_unref(button);
  my_widget_unref(panel);
  my_theme_destroy(theme);
}

TEST(css_scope_to_clause_survives_theme_clone)
{
  const char* css = "@scope panel to dialog { button { color: red; } }";
  my_theme_t* theme = my_theme_create(NULL);
  my_theme_t* clone;
  my_widget_t* panel = my_widget_create(NULL, "panel");
  my_widget_t* dialog = my_widget_create(NULL, "dialog");
  my_widget_t* blocked = my_widget_create(NULL, "blocked");
  const my_value_t* value;

  ASSERT_NOT_NULL(theme);
  ASSERT_NOT_NULL(panel);
  ASSERT_NOT_NULL(dialog);
  ASSERT_NOT_NULL(blocked);
  panel->widget_type = "panel";
  dialog->widget_type = "dialog";
  blocked->widget_type = "button";
  ASSERT_EQ(my_widget_add_child(panel, dialog), MY_RET_OK);
  ASSERT_EQ(my_widget_add_child(dialog, blocked), MY_RET_OK);
  ASSERT_EQ(my_theme_load_css_ex(theme, css, MY_CSS_PARSE_STRICT_AT_RULES),
            MY_RET_OK);
  clone = my_theme_clone(theme);
  ASSERT_NOT_NULL(clone);
  value = my_theme_get_for_widget(theme, blocked, MY_STATE_NORMAL,
                                  "fg_color");
  ASSERT_TRUE(value == NULL);
  value = my_theme_get_for_widget(clone, blocked, MY_STATE_NORMAL,
                                  "fg_color");
  ASSERT_TRUE(value == NULL);
  my_theme_destroy(clone);
  my_widget_unref(blocked);
  my_widget_unref(dialog);
  my_widget_unref(panel);
  my_theme_destroy(theme);
}

TEST(css_scope_to_clause_supports_class_and_id_limits)
{
  const char* css =
      "@scope .panel to .stop { button { color: red; } }"
      "@scope #application to #halt { label { color: blue; } }";
  my_css_error_t error = {0};
  my_css_sheet_t* sheet = my_css_parse_ex(
      NULL, css, strlen(css), MY_CSS_PARSE_STRICT_AT_RULES, &error);

  ASSERT_NOT_NULL(sheet);
  ASSERT_EQ(my_css_rule_count(sheet), 2u);
  ASSERT_STR_EQ(my_css_selector(my_css_rule(sheet, 0u), 0u)
                    ->scope_limits[0]
                    .style_class,
                "stop");
  ASSERT_STR_EQ(my_css_selector(my_css_rule(sheet, 1u), 0u)
                    ->scope_limits[0]
                    .id,
                "halt");
  my_css_sheet_destroy(sheet);
}

TEST(css_nested_scope_to_clauses_preserve_each_boundary)
{
  const char* css =
      "@scope outer to outer-stop {"
      "@scope inner to inner-stop { button { color: red; } } }";
  my_theme_t* theme = my_theme_create(NULL);
  my_widget_t* outer = my_widget_create(NULL, "outer");
  my_widget_t* inner = my_widget_create(NULL, "inner");
  my_widget_t* allowed = my_widget_create(NULL, "allowed");
  my_widget_t* inner_stop = my_widget_create(NULL, "inner-stop");
  my_widget_t* blocked_inner = my_widget_create(NULL, "blocked-inner");
  my_widget_t* outer_stop = my_widget_create(NULL, "outer-stop");
  my_widget_t* blocked_outer = my_widget_create(NULL, "blocked-outer");
  const my_value_t* value;

  ASSERT_NOT_NULL(theme);
  ASSERT_NOT_NULL(outer);
  ASSERT_NOT_NULL(inner);
  ASSERT_NOT_NULL(allowed);
  ASSERT_NOT_NULL(inner_stop);
  ASSERT_NOT_NULL(blocked_inner);
  ASSERT_NOT_NULL(outer_stop);
  ASSERT_NOT_NULL(blocked_outer);
  outer->widget_type = "outer";
  inner->widget_type = "inner";
  allowed->widget_type = "button";
  inner_stop->widget_type = "inner-stop";
  blocked_inner->widget_type = "button";
  outer_stop->widget_type = "outer-stop";
  blocked_outer->widget_type = "button";
  ASSERT_EQ(my_widget_add_child(outer, inner), MY_RET_OK);
  ASSERT_EQ(my_widget_add_child(inner, allowed), MY_RET_OK);
  ASSERT_EQ(my_widget_add_child(inner, inner_stop), MY_RET_OK);
  ASSERT_EQ(my_widget_add_child(inner_stop, blocked_inner), MY_RET_OK);
  ASSERT_EQ(my_widget_add_child(outer, outer_stop), MY_RET_OK);
  ASSERT_EQ(my_widget_add_child(outer_stop, blocked_outer), MY_RET_OK);
  ASSERT_EQ(my_theme_load_css_ex(theme, css, MY_CSS_PARSE_STRICT_AT_RULES),
            MY_RET_OK);
  value = my_theme_get_for_widget(theme, allowed, MY_STATE_NORMAL,
                                  "fg_color");
  ASSERT_NOT_NULL(value);
  value = my_theme_get_for_widget(theme, blocked_inner, MY_STATE_NORMAL,
                                  "fg_color");
  ASSERT_TRUE(value == NULL);
  value = my_theme_get_for_widget(theme, blocked_outer, MY_STATE_NORMAL,
                                  "fg_color");
  ASSERT_TRUE(value == NULL);
  my_widget_unref(blocked_outer);
  my_widget_unref(outer_stop);
  my_widget_unref(blocked_inner);
  my_widget_unref(inner_stop);
  my_widget_unref(allowed);
  my_widget_unref(inner);
  my_widget_unref(outer);
  my_theme_destroy(theme);
}

TEST(css_import_budget_failure_is_transactional)
{
  static char imported[MY_CSS_MAX_BYTES];
  const css_import_entry_t entries[] = {
      {"large.css", imported, sizeof(imported)}, {NULL, NULL, 0u}};
  const char* css = "@import \"large.css\";";
  my_css_parse_options_t options = {0};
  my_css_error_t error = {0};

  memset(imported, ' ', sizeof(imported));
  options.flags = MY_CSS_PARSE_STRICT_AT_RULES;
  options.resolve_import = css_test_resolve_import;
  options.import_context = (void*)entries;
  css_import_release_count = 0u;
  ASSERT_TRUE(my_css_parse_with_options(NULL, css, strlen(css), &options,
                                        &error) == NULL);
  ASSERT_EQ(error.code, MY_CSS_ERROR_INPUT_LIMIT);
  ASSERT_EQ(css_import_release_count, 1u);
}

TEST(theme_css_import_failure_preserves_existing_theme)
{
  const css_import_entry_t entries[] = {
      {"bad.css", "button { color: red;", 20u}, {NULL, NULL, 0u}};
  const char* css = "@import \"bad.css\";";
  my_css_parse_options_t options = {0};
  my_theme_t* theme = my_theme_create(NULL);
  my_widget_t* widget = my_widget_create(NULL, "button");

  ASSERT_NOT_NULL(theme);
  ASSERT_NOT_NULL(widget);
  widget->widget_type = "button";
  ASSERT_EQ(my_theme_load_css(theme, "button { color: blue; }"), MY_RET_OK);
  options.flags = MY_CSS_PARSE_STRICT_AT_RULES;
  options.resolve_import = css_test_resolve_import;
  options.import_context = (void*)entries;
  ASSERT_EQ(my_theme_load_css_with_options(theme, css, &options), MY_RET_FAIL);
  ASSERT_NOT_NULL(my_theme_get(theme, "button", NULL, MY_STATE_NORMAL,
                               "fg_color"));
  ASSERT_EQ(my_value_get_uint32(my_theme_get(
                theme, "button", NULL, MY_STATE_NORMAL, "fg_color")),
            0x0000FFFFu);
  my_widget_unref(widget);
  my_theme_destroy(theme);
}

TEST(theme_css_import_applies_imported_rules)
{
  const css_import_entry_t entries[] = {
      {"colors.css", "button { color: red; }", 22u}, {NULL, NULL, 0u}};
  const char* css = "@import \"colors.css\";";
  my_css_parse_options_t options = {0};
  my_theme_t* theme = my_theme_create(NULL);
  my_widget_t* widget = my_widget_create(NULL, "button");
  const my_value_t* value;

  ASSERT_NOT_NULL(theme);
  ASSERT_NOT_NULL(widget);
  widget->widget_type = "button";
  options.flags = MY_CSS_PARSE_STRICT_AT_RULES;
  options.resolve_import = css_test_resolve_import;
  options.import_context = (void*)entries;
  ASSERT_EQ(my_theme_load_css_with_options(theme, css, &options), MY_RET_OK);
  value = my_theme_get_for_widget(theme, widget, MY_STATE_NORMAL, "fg_color");
  ASSERT_NOT_NULL(value);
  ASSERT_EQ(my_value_get_uint32(value), 0xFF0000FFu);
  my_widget_unref(widget);
  my_theme_destroy(theme);
}

TEST(css_supports_single_declaration_is_evaluated_at_parse_time)
{
  const char* css =
      "@supports (color: red) { button { color: red; } }"
      "@supports (font-size: 14px) { label { color: blue; } }";
  my_css_error_t error = {0};
  my_css_sheet_t* sheet = my_css_parse_ex(
      NULL, css, strlen(css), MY_CSS_PARSE_STRICT_AT_RULES, &error);

  ASSERT_NOT_NULL(sheet);
  ASSERT_EQ(my_css_rule_count(sheet), 2u);
  ASSERT_STR_EQ(my_css_selector(my_css_rule(sheet, 0u), 0u)->widget_type,
                "button");
  my_css_sheet_destroy(sheet);
}

TEST(css_supports_logical_conditions_are_evaluated_at_parse_time)
{
  const char* css =
      "@supports (color: red) and (font-size: 14px) { button { color: red; } }"
      "@supports (color: red) or (font-size: 14px) { label { color: blue; } }"
      "@supports not (color: red) { edit { color: green; } }"
      "@supports ((color: red) and (font-size: 14px)) { slider { color: white; } }";
  my_css_error_t error = {0};
  my_css_sheet_t* sheet = my_css_parse_ex(
      NULL, css, strlen(css), MY_CSS_PARSE_STRICT_AT_RULES, &error);

  ASSERT_NOT_NULL(sheet);
  ASSERT_EQ(my_css_rule_count(sheet), 3u);
  ASSERT_STR_EQ(my_css_selector(my_css_rule(sheet, 0u), 0u)->widget_type,
                "button");
  ASSERT_STR_EQ(my_css_selector(my_css_rule(sheet, 1u), 0u)->widget_type,
                "label");
  ASSERT_STR_EQ(my_css_selector(my_css_rule(sheet, 2u), 0u)->widget_type,
                "slider");
  my_css_sheet_destroy(sheet);
}

TEST(css_supports_logical_conditions_reject_invalid_operator)
{
  const char* css =
      "@supports (color: red) xor (font-size: 14px) { button { color: red; } }";
  my_css_error_t error = {0};
  my_css_sheet_t* sheet = my_css_parse_ex(
      NULL, css, strlen(css), MY_CSS_PARSE_STRICT_AT_RULES, &error);

  ASSERT_TRUE(sheet == NULL);
  ASSERT_EQ(error.code, MY_CSS_ERROR_UNSUPPORTED_FEATURE);
  ASSERT_EQ(error.capability, (uint32_t)MY_CSS_FEATURE_SUPPORTS);
}

TEST(css_supports_logical_conditions_honor_precedence_and_depth_limit)
{
  const char* precedence =
      "@supports (color: red) or not (font-size: 14px) and (color: red) {"
      "button { color: red; } }";
  const char* too_deep =
      "@supports ((((((color: red)))))) { button { color: red; } }";
  my_css_error_t error = {0};
  my_css_sheet_t* sheet = my_css_parse_ex(
      NULL, precedence, strlen(precedence), MY_CSS_PARSE_STRICT_AT_RULES,
      &error);

  ASSERT_NOT_NULL(sheet);
  ASSERT_EQ(my_css_rule_count(sheet), 1u);
  my_css_sheet_destroy(sheet);

  memset(&error, 0, sizeof(error));
  sheet = my_css_parse_ex(NULL, too_deep, strlen(too_deep),
                          MY_CSS_PARSE_STRICT_AT_RULES, &error);
  ASSERT_TRUE(sheet == NULL);
  ASSERT_EQ(error.code, MY_CSS_ERROR_UNSUPPORTED_FEATURE);
  ASSERT_EQ(error.capability, (uint32_t)MY_CSS_FEATURE_SUPPORTS);
}

TEST(css_supports_rejects_complex_conditions_and_unknown_values)
{
  const char* complex =
      "@supports (color: red) xor (font-size: 14px) { button { color: red; } }";
  const char* unknown_value =
      "@supports (color: not-a-color) { button { color: red; } }";
  my_css_error_t error = {0};
  my_css_sheet_t* sheet;

  sheet = my_css_parse_ex(NULL, complex, strlen(complex),
                          MY_CSS_PARSE_STRICT_AT_RULES, &error);
  ASSERT_TRUE(sheet == NULL);
  ASSERT_EQ(error.code, MY_CSS_ERROR_UNSUPPORTED_FEATURE);
  ASSERT_EQ(error.capability, (uint32_t)MY_CSS_FEATURE_SUPPORTS);

  memset(&error, 0, sizeof(error));
  sheet = my_css_parse_ex(NULL, unknown_value, strlen(unknown_value),
                          MY_CSS_PARSE_STRICT_AT_RULES, &error);
  ASSERT_TRUE(sheet == NULL);
  ASSERT_EQ(error.code, MY_CSS_ERROR_UNSUPPORTED_FEATURE);
  ASSERT_EQ(error.capability, (uint32_t)MY_CSS_FEATURE_SUPPORTS);
}

TEST(css_supports_compatibility_mode_skips_unsupported_query)
{
  const char* css =
      "@supports (display: grid) { label { color: blue; } }"
      "button { color: red; }";
  my_css_error_t error = {0};
  my_css_sheet_t* sheet = my_css_parse(NULL, css, strlen(css), &error);

  ASSERT_NOT_NULL(sheet);
  ASSERT_EQ(my_css_rule_count(sheet), 1u);
  ASSERT_STR_EQ(my_css_selector(my_css_rule(sheet, 0u), 0u)->widget_type,
                "button");
  my_css_sheet_destroy(sheet);
}

TEST(css_supports_key_aliases_and_typed_values)
{
  const char* css =
      "@supports (background-color: #123456) { button { color: red; } }"
      "@supports (font-size: 14px) { label { color: blue; } }";
  my_css_error_t error = {0};
  my_css_sheet_t* sheet = my_css_parse_ex(
      NULL, css, strlen(css), MY_CSS_PARSE_STRICT_AT_RULES, &error);

  ASSERT_NOT_NULL(sheet);
  ASSERT_EQ(my_css_rule_count(sheet), 2u);
  my_css_sheet_destroy(sheet);
}

TEST(css_supports_query_budget_and_malformed_query_are_transactional)
{
  char oversized[MY_CSS_MAX_SUPPORTS_QUERY_BYTES + 32u];
  const char* malformed =
      "@supports (color red) { button { color: red; } }"
      "button { color: blue; }";
  my_css_error_t error = {0};
  size_t i;
  my_css_sheet_t* sheet;

  memcpy(oversized, "@supports (color: ", 19u);
  for (i = 19u; i < sizeof(oversized) - 7u; i++) oversized[i] = 'a';
  memcpy(oversized + sizeof(oversized) - 7u, ") { }", 5u);
  sheet = my_css_parse_ex(NULL, oversized, sizeof(oversized) - 2u,
                          MY_CSS_PARSE_STRICT_AT_RULES, &error);
  ASSERT_TRUE(sheet == NULL);
  ASSERT_EQ(error.code, MY_CSS_ERROR_UNSUPPORTED_FEATURE);

  memset(&error, 0, sizeof(error));
  sheet = my_css_parse_ex(NULL, malformed, strlen(malformed),
                          MY_CSS_PARSE_STRICT_AT_RULES, &error);
  ASSERT_TRUE(sheet == NULL);
  ASSERT_EQ(error.code, MY_CSS_ERROR_UNSUPPORTED_FEATURE);
}

TEST(theme_strict_css_accepts_supported_supports)
{
  const char* css =
      "@supports (color: red) { button { color: red; } }";
  my_theme_t* theme = my_theme_create(NULL);
  my_widget_t* button = my_widget_create(NULL, "button");
  const my_value_t* value;

  ASSERT_NOT_NULL(theme);
  ASSERT_NOT_NULL(button);
  button->widget_type = "button";
  ASSERT_EQ(my_theme_load_css_ex(theme, css, MY_CSS_PARSE_STRICT_AT_RULES),
            MY_RET_OK);
  value = my_theme_get_for_widget(theme, button, MY_STATE_NORMAL, "fg_color");
  ASSERT_NOT_NULL(value);
  ASSERT_EQ(my_value_get_uint32(value), 0xFF0000FFu);
  my_widget_unref(button);
  my_theme_destroy(theme);
}

TEST(css_media_all_and_screen_expand_rules)
{
  const char* css =
      "@media all { button { color: #123456; } }"
      "@media screen { label { color: #654321; } }";
  my_css_error_t error = {0};
  my_css_sheet_t* sheet = my_css_parse_ex(
      NULL, css, strlen(css), MY_CSS_PARSE_STRICT_AT_RULES, &error);
  my_theme_t* theme = my_theme_create(NULL);
  my_widget_t* button = my_widget_create(NULL, "button");
  my_widget_t* label = my_widget_create(NULL, "label");
  const my_value_t* value;

  ASSERT_NOT_NULL(sheet);
  ASSERT_EQ(my_css_rule_count(sheet), 2u);
  my_css_sheet_destroy(sheet);
  ASSERT_NOT_NULL(theme);
  ASSERT_NOT_NULL(button);
  button->widget_type = "button";
  ASSERT_NOT_NULL(label);
  button->widget_type = "button";
  label->widget_type = "label";
  ASSERT_EQ(my_theme_load_css_ex(theme, css, MY_CSS_PARSE_STRICT_AT_RULES),
            MY_RET_OK);
  value = my_theme_get_for_widget(theme, button, MY_STATE_NORMAL, "fg_color");
  ASSERT_NOT_NULL(value);
  ASSERT_EQ(my_value_get_uint32(value), 0x123456FFu);
  value = my_theme_get_for_widget(theme, label, MY_STATE_NORMAL, "fg_color");
  ASSERT_NOT_NULL(value);
  ASSERT_EQ(my_value_get_uint32(value), 0x654321FFu);
  my_widget_unref(label);
  my_widget_unref(button);
  my_theme_destroy(theme);
}

TEST(css_media_nested_all_expands_without_query_cost)
{
  const char* css =
      "@media all { @media screen { button { color: red; } } }";
  my_css_error_t error = {0};
  my_css_sheet_t* sheet = my_css_parse_ex(
      NULL, css, strlen(css), MY_CSS_PARSE_STRICT_AT_RULES, &error);
  const my_css_decl_t* decl;

  ASSERT_NOT_NULL(sheet);
  ASSERT_EQ(my_css_rule_count(sheet), 1u);
  decl = my_css_decl(my_css_rule(sheet, 0u), 0u);
  ASSERT_NOT_NULL(decl);
  ASSERT_EQ(my_value_get_uint32(&decl->value), 0xFF0000FFu);
  my_css_sheet_destroy(sheet);
}

TEST(css_conditional_media_context_filters_rules_at_parse_time)
{
  const char* css =
      "@media screen and (min-width: 800px) and (prefers-color-scheme: dark) {"
      "button { color: red; } }"
      "@media (max-width: 799px), (prefers-color-scheme: light) {"
      "label { color: blue; } }";
  my_css_media_context_t wide_dark = {1024u, 768u, true, true, false, 0u};
  my_css_media_context_t narrow_light = {640u, 480u, true, false, false, 0u};
  my_css_error_t error = {0};
  my_css_sheet_t* sheet;

  sheet = my_css_parse_media_ex(NULL, css, strlen(css),
                                MY_CSS_PARSE_STRICT_AT_RULES, &wide_dark,
                                &error);
  ASSERT_NOT_NULL(sheet);
  ASSERT_EQ(my_css_rule_count(sheet), 1u);
  ASSERT_STR_EQ(my_css_selector(my_css_rule(sheet, 0u), 0u)->widget_type,
                "button");
  my_css_sheet_destroy(sheet);

  memset(&error, 0, sizeof(error));
  sheet = my_css_parse_media_ex(NULL, css, strlen(css),
                                MY_CSS_PARSE_STRICT_AT_RULES, &narrow_light,
                                &error);
  ASSERT_NOT_NULL(sheet);
  ASSERT_EQ(my_css_rule_count(sheet), 1u);
  ASSERT_STR_EQ(my_css_selector(my_css_rule(sheet, 0u), 0u)->widget_type,
                "label");
  my_css_sheet_destroy(sheet);
}

TEST(css_conditional_media_theme_load_is_transactional)
{
  const char* css =
      "button { color: blue; }"
      "@media (min-width: 800px) { button { color: red; } }";
  const char* malformed =
      "button { color: green; }"
      "@media screen and (min-width: nope) { button { color: red; } }";
  my_css_media_context_t media = {1024u, 768u, true, false, false, 0u};
  my_theme_t* theme = my_theme_create(NULL);
  my_widget_t* button = my_widget_create(NULL, "button");
  const my_value_t* value;

  ASSERT_NOT_NULL(theme);
  ASSERT_NOT_NULL(button);
  button->widget_type = "button";
  ASSERT_EQ(my_theme_load_css_media_ex(theme, css,
                                       MY_CSS_PARSE_STRICT_AT_RULES, &media),
            MY_RET_OK);
  value = my_theme_get_for_widget(theme, button, MY_STATE_NORMAL, "fg_color");
  ASSERT_NOT_NULL(value);
  ASSERT_EQ(my_value_get_uint32(value), 0xFF0000FFu);
  ASSERT_EQ(my_theme_load_css_media_ex(theme, malformed,
                                       MY_CSS_PARSE_STRICT_AT_RULES, &media),
            MY_RET_FAIL);
  value = my_theme_get_for_widget(theme, button, MY_STATE_NORMAL, "fg_color");
  ASSERT_NOT_NULL(value);
  ASSERT_EQ(my_value_get_uint32(value), 0xFF0000FFu);
  my_widget_unref(button);
  my_theme_destroy(theme);
}

TEST(css_conditional_media_filters_logical_viewport_width)
{
  const char* css = "@media (min-width: 150px) { button { color: red; } }";
  my_css_media_context_t media = {100u, 80u, true, false, false, 0u};
  my_css_error_t error = {0};
  my_css_sheet_t* sheet = my_css_parse_media_ex(
      NULL, css, strlen(css), MY_CSS_PARSE_STRICT_AT_RULES, &media, &error);

  ASSERT_NOT_NULL(sheet);
  ASSERT_EQ(my_css_rule_count(sheet), 0u);
  my_css_sheet_destroy(sheet);
}

TEST(css_conditional_media_supports_orientation_and_motion_preferences)
{
  const char* css =
      "@media (orientation: portrait) and (prefers-reduced-motion: reduce) "
      "{ button { color: red; } }";
  my_css_media_context_t matching = {640u, 800u, true, false, true, 0u};
  my_css_media_context_t nonmatching = {800u, 640u, true, false, false, 0u};
  my_css_error_t error = {0};
  my_css_sheet_t* sheet;

  sheet = my_css_parse_media_ex(NULL, css, strlen(css),
                                MY_CSS_PARSE_STRICT_AT_RULES, &matching,
                                &error);
  ASSERT_NOT_NULL(sheet);
  ASSERT_EQ(my_css_rule_count(sheet), 1u);
  my_css_sheet_destroy(sheet);

  memset(&error, 0, sizeof(error));
  sheet = my_css_parse_media_ex(NULL, css, strlen(css),
                                MY_CSS_PARSE_STRICT_AT_RULES, &nonmatching,
                                &error);
  ASSERT_NOT_NULL(sheet);
  ASSERT_EQ(my_css_rule_count(sheet), 0u);
  my_css_sheet_destroy(sheet);
}

TEST(css_conditional_media_rejects_oversized_query_and_invalid_units)
{
  char* oversized = (char*)malloc(MY_CSS_MAX_MEDIA_QUERY_BYTES + 32u);
  const char* invalid_unit =
      "@media (min-width: 10em) { button { color: red; } }";
  my_css_media_context_t media = {1024u, 768u, true, false, false, 0u};
  my_css_error_t error = {0};
  my_css_sheet_t* sheet;
  size_t i;

  ASSERT_NOT_NULL(oversized);
  memcpy(oversized, "@media (min-width: ", 19u);
  for (i = 19u; i < MY_CSS_MAX_MEDIA_QUERY_BYTES + 16u; i++) {
    oversized[i] = '1';
  }
  memcpy(oversized + MY_CSS_MAX_MEDIA_QUERY_BYTES + 16u, "px) { }", 7u);
  sheet = my_css_parse_media_ex(
      NULL, oversized, MY_CSS_MAX_MEDIA_QUERY_BYTES + 23u,
      MY_CSS_PARSE_STRICT_AT_RULES, &media, &error);
  ASSERT_TRUE(sheet == NULL);
  ASSERT_EQ(error.code, MY_CSS_ERROR_SYNTAX);
  free(oversized);

  memset(&error, 0, sizeof(error));
  sheet = my_css_parse_media_ex(NULL, invalid_unit, strlen(invalid_unit),
                                MY_CSS_PARSE_STRICT_AT_RULES, &media, &error);
  ASSERT_TRUE(sheet == NULL);
  ASSERT_EQ(error.code, MY_CSS_ERROR_UNSUPPORTED_FEATURE);
}

TEST(css_conditional_media_rejects_missing_and_operator)
{
  const char* css =
      "@media screen (min-width: 800px) { button { color: red; } }";
  my_css_media_context_t media = {1024u, 768u, true, false, false, 0u};
  my_css_error_t error = {0};
  my_css_sheet_t* sheet = my_css_parse_media_ex(
      NULL, css, strlen(css), MY_CSS_PARSE_STRICT_AT_RULES, &media, &error);

  ASSERT_TRUE(sheet == NULL);
  ASSERT_EQ(error.code, MY_CSS_ERROR_UNSUPPORTED_FEATURE);
}

TEST(css_conditional_media_supports_bounded_range_syntax)
{
  const char* css =
      "@media (width >= 800px) { button { color: red; } }"
      "@media (400px <= width < 800px) { label { color: blue; } }";
  my_css_media_context_t wide = {1024u, 768u, true, false, false, 0u};
  my_css_media_context_t middle = {640u, 480u, true, false, false, 0u};
  my_css_media_context_t narrow = {320u, 480u, true, false, false, 0u};
  my_css_error_t error = {0};
  my_css_sheet_t* sheet;

  sheet = my_css_parse_media_ex(NULL, css, strlen(css),
                                MY_CSS_PARSE_STRICT_AT_RULES, &wide, &error);
  ASSERT_NOT_NULL(sheet);
  ASSERT_EQ(my_css_rule_count(sheet), 1u);
  ASSERT_STR_EQ(my_css_selector(my_css_rule(sheet, 0u), 0u)->widget_type,
                "button");
  my_css_sheet_destroy(sheet);

  memset(&error, 0, sizeof(error));
  sheet = my_css_parse_media_ex(NULL, css, strlen(css),
                                MY_CSS_PARSE_STRICT_AT_RULES, &middle, &error);
  ASSERT_NOT_NULL(sheet);
  ASSERT_EQ(my_css_rule_count(sheet), 1u);
  ASSERT_STR_EQ(my_css_selector(my_css_rule(sheet, 0u), 0u)->widget_type,
                "label");
  my_css_sheet_destroy(sheet);

  memset(&error, 0, sizeof(error));
  sheet = my_css_parse_media_ex(NULL, css, strlen(css),
                                MY_CSS_PARSE_STRICT_AT_RULES, &narrow, &error);
  ASSERT_NOT_NULL(sheet);
  ASSERT_EQ(my_css_rule_count(sheet), 0u);
  my_css_sheet_destroy(sheet);
}

TEST(css_conditional_media_supports_device_capabilities)
{
  const char* css =
      "@media (hover: hover) and (pointer: fine) and "
      "(any-pointer: coarse) and (color-gamut: p3) and "
      "(dynamic-range: high) { button { color: red; } }";
  my_css_media_context_t capable = {
      1024u, 768u, true, false, false,
      MY_CSS_MEDIA_CAP_HOVER | MY_CSS_MEDIA_CAP_POINTER_FINE |
          MY_CSS_MEDIA_CAP_ANY_POINTER_COARSE | MY_CSS_MEDIA_CAP_COLOR_P3 |
          MY_CSS_MEDIA_CAP_HDR};
  my_css_media_context_t basic = {1024u, 768u, true, false, false, 0u};
  my_css_error_t error = {0};
  my_css_sheet_t* sheet;

  sheet = my_css_parse_media_ex(NULL, css, strlen(css),
                                MY_CSS_PARSE_STRICT_AT_RULES, &capable, &error);
  ASSERT_NOT_NULL(sheet);
  ASSERT_EQ(my_css_rule_count(sheet), 1u);
  my_css_sheet_destroy(sheet);

  memset(&error, 0, sizeof(error));
  sheet = my_css_parse_media_ex(NULL, css, strlen(css),
                                MY_CSS_PARSE_STRICT_AT_RULES, &basic, &error);
  ASSERT_NOT_NULL(sheet);
  ASSERT_EQ(my_css_rule_count(sheet), 0u);
  my_css_sheet_destroy(sheet);
}

TEST(css_conditional_media_rejects_unknown_device_capability_value)
{
  const char* css = "@media (pointer: wireless) { button { color: red; } }";
  my_css_media_context_t media = {1024u, 768u, true, false, false, 0u};
  my_css_error_t error = {0};
  my_css_sheet_t* sheet = my_css_parse_media_ex(
      NULL, css, strlen(css), MY_CSS_PARSE_STRICT_AT_RULES, &media, &error);

  ASSERT_TRUE(sheet == NULL);
  ASSERT_EQ(error.code, MY_CSS_ERROR_UNSUPPORTED_FEATURE);
}

TEST(css_conditional_media_device_capabilities_follow_level_semantics)
{
  const char* css =
      "@media (color-gamut: srgb) { button { color: red; } }"
      "@media (color-gamut: p3) { label { color: blue; } }"
      "@media (color-gamut: rec2020) { edit { color: green; } }"
      "@media (dynamic-range: standard) { slider { color: white; } }";
  my_css_media_context_t p3 = {1024u, 768u, true, false, false,
                               MY_CSS_MEDIA_CAP_COLOR_P3 |
                                   MY_CSS_MEDIA_CAP_HDR};
  my_css_media_context_t srgb = {1024u, 768u, true, false, false,
                                 MY_CSS_MEDIA_CAP_COLOR_SRGB};
  my_css_error_t error = {0};
  my_css_sheet_t* sheet;

  sheet = my_css_parse_media_ex(NULL, css, strlen(css),
                                MY_CSS_PARSE_STRICT_AT_RULES, &p3, &error);
  ASSERT_NOT_NULL(sheet);
  ASSERT_EQ(my_css_rule_count(sheet), 3u);
  my_css_sheet_destroy(sheet);

  memset(&error, 0, sizeof(error));
  sheet = my_css_parse_media_ex(NULL, css, strlen(css),
                                MY_CSS_PARSE_STRICT_AT_RULES, &srgb, &error);
  ASSERT_NOT_NULL(sheet);
  ASSERT_EQ(my_css_rule_count(sheet), 2u);
  my_css_sheet_destroy(sheet);
}

TEST(css_conditional_media_rejects_unknown_device_capability_bits)
{
  const char* css = "@media (hover: hover) { button { color: red; } }";
  my_css_media_context_t invalid = {1024u, 768u, true, false, false,
                                    MY_CSS_MEDIA_CAP_ALL | (1u << 31)};
  my_css_error_t error = {0};
  my_css_sheet_t* sheet = my_css_parse_media_ex(
      NULL, css, strlen(css), MY_CSS_PARSE_STRICT_AT_RULES, &invalid, &error);

  ASSERT_TRUE(sheet == NULL);
  ASSERT_EQ(error.code, MY_CSS_ERROR_UNSUPPORTED_FEATURE);
}

TEST(css_conditional_media_unknown_facts_do_not_match_negative_queries)
{
  const char* css =
      "@media (hover: none) { button { color: red; } }"
      "@media (pointer: none) { label { color: blue; } }"
      "@media (prefers-color-scheme: light) { edit { color: green; } }"
      "@media (dynamic-range: standard) { slider { color: white; } }";
  my_css_media_context_ex_t unknown = {{1024u, 768u, false, false, false, 0u},
                                       MY_CSS_MEDIA_KNOWN_COLOR_GAMUT};
  my_css_error_t error = {0};
  my_css_sheet_t* sheet = my_css_parse_media_ex2(
      NULL, css, strlen(css), MY_CSS_PARSE_STRICT_AT_RULES, &unknown, &error);

  ASSERT_NOT_NULL(sheet);
  ASSERT_EQ(my_css_rule_count(sheet), 0u);
  my_css_sheet_destroy(sheet);
}

TEST(css_conditional_media_not_preserves_unknown_facts)
{
  const char* css =
      "@media not (prefers-color-scheme: dark) { button { color: red; } }";
  my_css_media_context_ex_t known_dark = {
      {1024u, 768u, true, true, false, 0u},
      MY_CSS_MEDIA_KNOWN_COLOR_SCHEME};
  my_css_media_context_ex_t known_light = {
      {1024u, 768u, true, false, false, 0u},
      MY_CSS_MEDIA_KNOWN_COLOR_SCHEME};
  my_css_media_context_ex_t unknown = {
      {1024u, 768u, true, false, false, 0u},
      MY_CSS_MEDIA_KNOWN_COLOR_GAMUT};
  my_css_error_t error = {0};
  my_css_sheet_t* sheet;

  sheet = my_css_parse_media_ex2(NULL, css, strlen(css),
                                 MY_CSS_PARSE_STRICT_AT_RULES,
                                 &known_dark, &error);
  ASSERT_NOT_NULL(sheet);
  ASSERT_EQ(my_css_rule_count(sheet), 0u);
  my_css_sheet_destroy(sheet);

  sheet = my_css_parse_media_ex2(NULL, css, strlen(css),
                                 MY_CSS_PARSE_STRICT_AT_RULES,
                                 &known_light, &error);
  ASSERT_NOT_NULL(sheet);
  ASSERT_EQ(my_css_rule_count(sheet), 1u);
  my_css_sheet_destroy(sheet);

  sheet = my_css_parse_media_ex2(NULL, css, strlen(css),
                                 MY_CSS_PARSE_STRICT_AT_RULES, &unknown,
                                 &error);
  ASSERT_NOT_NULL(sheet);
  ASSERT_EQ(my_css_rule_count(sheet), 0u);
  my_css_sheet_destroy(sheet);
}

TEST(css_conditional_media_not_rejects_bounded_combinations)
{
  const char* css =
      "@media not screen and (min-width: 1px) { button { color: red; } }";
  my_css_media_context_t media = {1024u, 768u, true, false, false, 0u};
  my_css_error_t error = {0};
  my_css_sheet_t* sheet = my_css_parse_media_ex(
      NULL, css, strlen(css), MY_CSS_PARSE_STRICT_AT_RULES, &media, &error);

  ASSERT_TRUE(sheet == NULL);
  ASSERT_EQ(error.code, MY_CSS_ERROR_UNSUPPORTED_FEATURE);
}

TEST(css_extended_media_context_validates_known_mask)
{
  const char* css = "@media (hover: hover) { button { color: red; } }";
  my_css_media_context_ex_t media = {
      {1024u, 768u, true, false, false, MY_CSS_MEDIA_CAP_HOVER},
      MY_CSS_MEDIA_KNOWN_HOVER};
  my_css_media_context_ex_t invalid = media;
  my_css_error_t error = {0};
  my_css_sheet_t* sheet;

  sheet = my_css_parse_media_ex2(NULL, css, strlen(css),
                                 MY_CSS_PARSE_STRICT_AT_RULES, &media,
                                 &error);
  ASSERT_NOT_NULL(sheet);
  ASSERT_EQ(my_css_rule_count(sheet), 1u);
  my_css_sheet_destroy(sheet);
  invalid.known = 1u << 31;
  memset(&error, 0, sizeof(error));
  sheet = my_css_parse_media_ex2(NULL, css, strlen(css),
                                 MY_CSS_PARSE_STRICT_AT_RULES, &invalid,
                                 &error);
  ASSERT_TRUE(sheet == NULL);
  ASSERT_EQ(error.code, MY_CSS_ERROR_UNSUPPORTED_FEATURE);
}

TEST(css_conditional_media_rejects_invalid_range_syntax)
{
  const char* css = "@media (width 800px) { button { color: red; } }";
  my_css_media_context_t media = {1024u, 768u, true, false, false, 0u};
  my_css_error_t error = {0};
  my_css_sheet_t* sheet = my_css_parse_media_ex(
      NULL, css, strlen(css), MY_CSS_PARSE_STRICT_AT_RULES, &media, &error);

  ASSERT_TRUE(sheet == NULL);
  ASSERT_EQ(error.code, MY_CSS_ERROR_UNSUPPORTED_FEATURE);
}

TEST(css_media_nesting_is_bounded)
{
  const char* css =
      "@media all { @media all { @media all { @media all {"
      "@media all { button { color: red; } } } } } }";
  my_css_error_t error = {0};
  my_css_sheet_t* sheet = my_css_parse_ex(
      NULL, css, strlen(css), MY_CSS_PARSE_STRICT_AT_RULES, &error);

  ASSERT_TRUE(sheet == NULL);
  ASSERT_TRUE(error.msg[0] != '\0');
}

TEST(css_strict_mode_rejects_unsupported_at_rules)
{
  const char* css = "@media (min-width: 1px) { button { color: red; } }";
  my_css_error_t error = {0};
  my_css_sheet_t* sheet = my_css_parse_ex(
      NULL, css, strlen(css), MY_CSS_PARSE_STRICT_AT_RULES, &error);

  ASSERT_TRUE(sheet == NULL);
  ASSERT_TRUE(error.msg[0] != '\0');
}

TEST(css_layers_override_specificity_and_unlayered_rules)
{
  const char* css =
      "@layer base { #save { color: red; } }"
      "@layer components { button { color: blue; } }"
      "button { color: green; }";
  my_theme_t* theme = my_theme_create(NULL);
  my_widget_t* widget = my_widget_create(NULL, "button");
  const my_value_t* value;

  ASSERT_NOT_NULL(theme);
  ASSERT_NOT_NULL(widget);
  widget->widget_type = "button";
  ASSERT_EQ(my_widget_set_name(widget, "save"), MY_RET_OK);
  ASSERT_EQ(my_theme_load_css_ex(theme, css, MY_CSS_PARSE_STRICT_AT_RULES),
            MY_RET_OK);
  value = my_theme_get_for_widget(theme, widget, MY_STATE_NORMAL,
                                  "fg_color");
  ASSERT_NOT_NULL(value);
  ASSERT_EQ(my_value_get_uint32(value), 0x008000FFu);
  my_widget_unref(widget);
  my_theme_destroy(theme);
}

TEST(css_layer_order_statement_is_respected)
{
  const char* css =
      "@layer components, base;"
      "@layer base { button { color: red; } }"
      "@layer components { button { color: blue; } }";
  my_theme_t* theme = my_theme_create(NULL);
  my_widget_t* widget = my_widget_create(NULL, "button");
  const my_value_t* value;

  ASSERT_NOT_NULL(theme);
  ASSERT_NOT_NULL(widget);
  widget->widget_type = "button";
  ASSERT_EQ(my_theme_load_css_ex(theme, css, MY_CSS_PARSE_STRICT_AT_RULES),
            MY_RET_OK);
  value = my_theme_get_for_widget(theme, widget, MY_STATE_NORMAL,
                                  "fg_color");
  ASSERT_NOT_NULL(value);
  ASSERT_EQ(my_value_get_uint32(value), 0xFF0000FFu);
  my_widget_unref(widget);
  my_theme_destroy(theme);
}

TEST(css_late_layer_order_statement_reorders_existing_rules)
{
  const char* css =
      "@layer base { button { color: red; } }"
      "@layer components { button { color: blue; } }"
      "@layer components, base;";
  my_theme_t* theme = my_theme_create(NULL);
  my_widget_t* widget = my_widget_create(NULL, "button");
  const my_value_t* value;

  ASSERT_NOT_NULL(theme);
  ASSERT_NOT_NULL(widget);
  widget->widget_type = "button";
  ASSERT_EQ(my_theme_load_css_ex(theme, css, MY_CSS_PARSE_STRICT_AT_RULES),
            MY_RET_OK);
  value = my_theme_get_for_widget(theme, widget, MY_STATE_NORMAL,
                                  "fg_color");
  ASSERT_NOT_NULL(value);
  ASSERT_EQ(my_value_get_uint32(value), 0xFF0000FFu);
  my_widget_unref(widget);
  my_theme_destroy(theme);
}

TEST(css_layer_rejects_empty_duplicate_and_oversized_names)
{
  const char* empty = "@layer ; button { color: red; }";
  const char* duplicate = "@layer a, a; button { color: red; }";
  char oversized[MY_CSS_MAX_LAYER_NAME_BYTES + 32u];
  my_css_error_t error = {0};

  ASSERT_TRUE(my_css_parse_ex(NULL, empty, strlen(empty),
                              MY_CSS_PARSE_STRICT_AT_RULES, &error) == NULL);
  memset(&error, 0, sizeof(error));
  ASSERT_TRUE(my_css_parse_ex(NULL, duplicate, strlen(duplicate),
                              MY_CSS_PARSE_STRICT_AT_RULES, &error) == NULL);
  memset(oversized, 'a', sizeof(oversized));
  memcpy(oversized, "@layer ", 7u);
  oversized[7u + MY_CSS_MAX_LAYER_NAME_BYTES + 1u] = ';';
  oversized[8u + MY_CSS_MAX_LAYER_NAME_BYTES + 1u] = '\0';
  memset(&error, 0, sizeof(error));
  ASSERT_TRUE(my_css_parse_ex(NULL, oversized,
                              strlen(oversized), MY_CSS_PARSE_STRICT_AT_RULES,
                              &error) == NULL);
}

TEST(css_capability_registry_is_static_and_explicit)
{
  const my_css_capabilities_t* first = my_css_capabilities();
  const my_css_capabilities_t* second = my_css_capabilities();

  ASSERT_NOT_NULL(first);
  ASSERT_TRUE(first == second);
  ASSERT_EQ(first->max_bytes, (size_t)MY_CSS_MAX_BYTES);
  ASSERT_EQ(first->max_ancestors, (size_t)MY_CSS_MAX_ANCESTORS);
  ASSERT_TRUE((first->supported_features & MY_CSS_FEATURE_SELECTORS) != 0u);
  ASSERT_TRUE((first->supported_features & MY_CSS_FEATURE_TYPED_VALUES) != 0u);
  ASSERT_TRUE((first->supported_features & MY_CSS_FEATURE_AT_RULES) != 0u);
  ASSERT_TRUE((first->supported_features & MY_CSS_FEATURE_SUPPORTS) != 0u);
  ASSERT_TRUE((first->supported_features & MY_CSS_FEATURE_LAYERS) != 0u);
  ASSERT_TRUE((first->supported_features & MY_CSS_FEATURE_IMPORTS) != 0u);
  ASSERT_TRUE((first->supported_features & MY_CSS_FEATURE_SCOPE) != 0u);
  ASSERT_EQ(first->supported_parse_flags, (uint32_t)MY_CSS_PARSE_STRICT_AT_RULES);
}

TEST(css_strict_error_identifies_missing_capability)
{
  const char* css = "@media (x) { button { color: red; } }";
  my_css_error_t error = {0};
  my_css_sheet_t* sheet = my_css_parse_ex(
      NULL, css, strlen(css), MY_CSS_PARSE_STRICT_AT_RULES, &error);

  ASSERT_TRUE(sheet == NULL);
  ASSERT_EQ(error.code, MY_CSS_ERROR_UNSUPPORTED_FEATURE);
  ASSERT_EQ(error.capability, (uint32_t)MY_CSS_FEATURE_AT_RULES);
  ASSERT_TRUE(error.line > 0);
  ASSERT_TRUE(error.col > 0);
}

TEST(css_error_codes_distinguish_policy_and_budget)
{
  my_css_error_t error = {0};
  char* css = (char*)malloc(MY_CSS_MAX_BYTES + 1u);

  ASSERT_NOT_NULL(css);
  memset(css, ' ', MY_CSS_MAX_BYTES + 1u);
  ASSERT_TRUE(my_css_parse_ex(NULL, "button { color: red; }", 23u, 2u,
                              &error) == NULL);
  ASSERT_EQ(error.code, MY_CSS_ERROR_UNKNOWN_POLICY);
  memset(&error, 0, sizeof(error));
  ASSERT_TRUE(my_css_parse(NULL, css, MY_CSS_MAX_BYTES + 1u, &error) == NULL);
  ASSERT_EQ(error.code, MY_CSS_ERROR_INPUT_LIMIT);
  free(css);
}

TEST(css_parse_rejects_unknown_policy_flags)
{
  my_css_error_t error = {0};
  my_css_sheet_t* sheet =
      my_css_parse_ex(NULL, "button { color: red; }", 23u, 2u, &error);

  ASSERT_TRUE(sheet == NULL);
  ASSERT_TRUE(error.msg[0] != '\0');
}

TEST(theme_strict_css_rejects_at_rule_without_mutation)
{
  my_theme_t* theme = my_theme_create(NULL);
  my_widget_t* widget = my_widget_create(NULL, "button");
  const char* css = "button { color: blue; } @media (x) { button { color: red; } }";

  ASSERT_NOT_NULL(theme);
  ASSERT_NOT_NULL(widget);
  ASSERT_EQ(my_theme_load_css_ex(theme, css, MY_CSS_PARSE_STRICT_AT_RULES),
            MY_RET_FAIL);
  ASSERT_TRUE(my_theme_get_for_widget(theme, widget, MY_STATE_NORMAL,
                                      "fg_color") == NULL);
  my_widget_unref(widget);
  my_theme_destroy(theme);
}

TEST(theme_css_load_preserves_existing_entries)
{
  my_theme_t* theme = my_theme_create(NULL);
  my_widget_t* widget = my_widget_create(NULL, "button");
  const my_value_t* background;
  const my_value_t* foreground;
  my_value_t value;

  ASSERT_NOT_NULL(theme);
  ASSERT_NOT_NULL(widget);
  widget->widget_type = "button";
  my_value_init(&value, NULL);
  ASSERT_EQ(my_value_set_uint32(&value, 0x010203FFu), MY_RET_OK);
  ASSERT_EQ(my_theme_set(theme, "button", NULL, MY_STATE_NORMAL,
                         "bg_color", &value), MY_RET_OK);
  ASSERT_EQ(my_theme_load_css(theme, "button { color: red; }"), MY_RET_OK);
  background = my_theme_get_for_widget(theme, widget, MY_STATE_NORMAL,
                                       "bg_color");
  foreground = my_theme_get_for_widget(theme, widget, MY_STATE_NORMAL,
                                       "fg_color");
  ASSERT_NOT_NULL(background);
  ASSERT_NOT_NULL(foreground);
  ASSERT_EQ(my_value_get_uint32(background), 0x010203FFu);
  ASSERT_EQ(my_value_get_uint32(foreground), 0xFF0000FFu);
  my_value_reset(&value);
  my_widget_unref(widget);
  my_theme_destroy(theme);
}

TEST(theme_css_load_overrides_existing_property)
{
  my_theme_t* theme = my_theme_create(NULL);
  my_widget_t* widget = my_widget_create(NULL, "button");
  my_value_t value;
  const my_value_t* foreground;

  ASSERT_NOT_NULL(theme);
  ASSERT_NOT_NULL(widget);
  widget->widget_type = "button";
  my_value_init(&value, NULL);
  ASSERT_EQ(my_value_set_uint32(&value, 0x010203FFu), MY_RET_OK);
  ASSERT_EQ(my_theme_set(theme, "button", NULL, MY_STATE_NORMAL,
                         "fg_color", &value), MY_RET_OK);
  ASSERT_EQ(my_theme_load_css(theme, "button { color: red; }"), MY_RET_OK);
  foreground = my_theme_get_for_widget(theme, widget, MY_STATE_NORMAL,
                                       "fg_color");
  ASSERT_NOT_NULL(foreground);
  ASSERT_EQ(my_value_get_uint32(foreground), 0xFF0000FFu);
  my_value_reset(&value);
  my_widget_unref(widget);
  my_theme_destroy(theme);
}

TEST(theme_css_load_preserves_existing_specificity)
{
  my_theme_t* theme = my_theme_create(NULL);
  my_widget_t* widget = my_widget_create(NULL, "button");
  my_value_t value;
  const my_value_t* foreground;

  ASSERT_NOT_NULL(theme);
  ASSERT_NOT_NULL(widget);
  widget->widget_type = "button";
  ASSERT_EQ(my_widget_set_style_class(widget, "primary"), MY_RET_OK);
  my_value_init(&value, NULL);
  ASSERT_EQ(my_value_set_uint32(&value, 0x010203FFu), MY_RET_OK);
  ASSERT_EQ(my_theme_set_ex3(theme, "button", NULL, "primary", NULL, false,
                             MY_STATE_NORMAL, "fg_color", &value, 100),
            MY_RET_OK);
  ASSERT_EQ(my_theme_load_css(theme, "button { color: red; }"), MY_RET_OK);
  foreground = my_theme_get_for_widget(theme, widget, MY_STATE_NORMAL,
                                       "fg_color");
  ASSERT_NOT_NULL(foreground);
  ASSERT_EQ(my_value_get_uint32(foreground), 0x010203FFu);
  my_value_reset(&value);
  my_widget_unref(widget);
  my_theme_destroy(theme);
}

TEST(theme_css_load_rolls_back_clone_oom)
{
  size_t failure;
  bool observed_failure = false;

  for (failure = 1u; failure <= 64u; failure++) {
    css_alloc_state_t state = {0};
    my_allocator_t allocator = {&state, css_test_alloc, css_test_calloc,
                                css_test_realloc, css_test_free};
    my_theme_t* theme = my_theme_create(&allocator);
    my_value_t value;
    const my_value_t* background;
    my_ret_t ret;

    ASSERT_NOT_NULL(theme);
    my_value_init(&value, &allocator);
    ASSERT_EQ(my_value_set_str(&value, "original"), MY_RET_OK);
    ASSERT_EQ(my_theme_set(theme, "button", NULL, MY_STATE_NORMAL,
                           "bg_color", &value), MY_RET_OK);
    my_value_reset(&value);
    state.fail_at = state.alloc_calls + failure;
    ret = my_theme_load_css(theme, "button { color: red; }");
    ASSERT_TRUE(ret == MY_RET_OK || ret == MY_RET_OOM || ret == MY_RET_FAIL);
    background = my_theme_get(theme, "button", NULL, MY_STATE_NORMAL,
                               "bg_color");
    ASSERT_NOT_NULL(background);
    ASSERT_STR_EQ(my_value_get_str(background), "original");
    if (ret != MY_RET_OK) {
      observed_failure = true;
    }
    my_theme_destroy(theme);
    ASSERT_EQ(state.live_count, 0);
  }
  ASSERT_TRUE(observed_failure);
}

TEST(theme_text_load_rolls_back_malformed_later_line)
{
  my_theme_t* theme = my_theme_create(NULL);
  my_value_t value;
  const my_value_t* background;
  const my_value_t* foreground;

  ASSERT_NOT_NULL(theme);
  my_value_init(&value, NULL);
  ASSERT_EQ(my_value_set_uint32(&value, 0x010203FFu), MY_RET_OK);
  ASSERT_EQ(my_theme_set(theme, "button", NULL, MY_STATE_NORMAL,
                         "bg_color", &value), MY_RET_OK);
  ASSERT_EQ(my_theme_load_str(theme,
                              "button.normal.fg_color=#FF0000\nmalformed"),
            MY_RET_INVALID_PARAMS);
  background = my_theme_get(theme, "button", NULL, MY_STATE_NORMAL,
                            "bg_color");
  foreground = my_theme_get(theme, "button", NULL, MY_STATE_NORMAL,
                            "fg_color");
  ASSERT_NOT_NULL(background);
  ASSERT_TRUE(foreground == NULL);
  ASSERT_EQ(my_value_get_uint32(background), 0x010203FFu);
  my_value_reset(&value);
  my_theme_destroy(theme);
}

TEST(theme_text_rejects_unterminated_input_with_bounded_scan)
{
  char* text = (char*)malloc(MY_THEME_MAX_BYTES);
  css_alloc_state_t state = {0};
  my_allocator_t allocator = {&state, css_test_alloc, css_test_calloc,
                              css_test_realloc, css_test_free};
  my_theme_t* theme;
  size_t calls_before;

  ASSERT_NOT_NULL(text);
  memset(text, ' ', MY_THEME_MAX_BYTES);
  theme = my_theme_create(&allocator);
  ASSERT_NOT_NULL(theme);
  calls_before = state.alloc_calls;
  ASSERT_EQ(my_theme_load_str(theme, text), MY_RET_FAIL);
  ASSERT_EQ(state.alloc_calls, calls_before);
  my_theme_destroy(theme);
  ASSERT_EQ(state.live_count, 0);
  free(text);
}

TEST(theme_set_rolls_back_new_property_value_oom)
{
  css_alloc_state_t state = {0};
  my_allocator_t allocator = {&state, css_test_alloc, css_test_calloc,
                              css_test_realloc, css_test_free};
  my_theme_t* theme = my_theme_create(&allocator);
  my_value_t value;
  const my_value_t* background;
  const my_value_t* foreground;

  ASSERT_NOT_NULL(theme);
  my_value_init(&value, NULL);
  ASSERT_EQ(my_value_set_uint32(&value, 0x010203FFu), MY_RET_OK);
  ASSERT_EQ(my_theme_set(theme, "button", NULL, MY_STATE_NORMAL,
                         "bg_color", &value), MY_RET_OK);
  ASSERT_EQ(my_value_set_str(&value, "oom"), MY_RET_OK);
  state.fail_at = state.alloc_calls + 1u;
  ASSERT_EQ(my_theme_set(theme, "button", NULL, MY_STATE_NORMAL,
                         "fg_color", &value), MY_RET_OOM);
  background = my_theme_get(theme, "button", NULL, MY_STATE_NORMAL,
                            "bg_color");
  foreground = my_theme_get(theme, "button", NULL, MY_STATE_NORMAL,
                            "fg_color");
  ASSERT_NOT_NULL(background);
  ASSERT_TRUE(foreground == NULL);
  ASSERT_EQ(my_value_get_uint32(background), 0x010203FFu);
  my_value_reset(&value);
  my_theme_destroy(theme);
  ASSERT_EQ(state.live_count, 0);
}

TEST(theme_set_rolls_back_new_entry_value_oom)
{
  css_alloc_state_t state = {0};
  my_allocator_t allocator = {&state, css_test_alloc, css_test_calloc,
                              css_test_realloc, css_test_free};
  my_theme_t* theme = my_theme_create(&allocator);
  my_value_t value;

  ASSERT_NOT_NULL(theme);
  my_value_init(&value, NULL);
  ASSERT_EQ(my_value_set_str(&value, "oom"), MY_RET_OK);
  state.fail_at = state.alloc_calls + 2u;
  ASSERT_EQ(my_theme_set(theme, "button", NULL, MY_STATE_NORMAL,
                         "fg_color", &value), MY_RET_OOM);
  ASSERT_EQ(my_darray_size(theme->entries), 0u);
  my_value_reset(&value);
  my_theme_destroy(theme);
  ASSERT_EQ(state.live_count, 0);
}

TEST(default_theme_creation_rolls_back_oom)
{
  size_t fail_at;

  for (fail_at = 1u; fail_at <= 128u; fail_at++) {
    css_alloc_state_t state = {0};
    my_allocator_t allocator = {&state, css_test_alloc, css_test_calloc,
                                css_test_realloc, css_test_free};
    my_theme_t* theme;
    const my_value_t* value;

    state.fail_at = fail_at;
    theme = my_theme_default_create(&allocator);
    if (theme != NULL) {
      value = my_theme_get(theme, "window", NULL, MY_STATE_NORMAL,
                           MY_STYLE_BG_COLOR);
      if (value == NULL) {
        my_theme_destroy(theme);
        ASSERT_TRUE(false);
      }
      value = my_theme_get(theme, "button", NULL, MY_STATE_DISABLED,
                           MY_STYLE_BG_COLOR);
      if (value == NULL) {
        my_theme_destroy(theme);
        ASSERT_TRUE(false);
      }
      value = my_theme_get(theme, "tooltip", NULL, MY_STATE_NORMAL,
                           MY_STYLE_BORDER_COLOR);
      if (value == NULL) {
        my_theme_destroy(theme);
        ASSERT_TRUE(false);
      }
      my_theme_destroy(theme);
    }
    ASSERT_EQ(state.live_count, 0);
  }
}

TEST(css_structural_errors_reject_without_error_storage)
{
  const char* css = "@supports {";
  my_css_sheet_t* sheet = my_css_parse(NULL, css, strlen(css), NULL);

  ASSERT_TRUE(sheet == NULL);
}

TEST(css_parser_rejects_oversized_input_before_allocation)
{
  size_t length = (size_t)MY_CSS_MAX_BYTES + 1u;
  char* css = (char*)malloc(length);
  css_alloc_state_t state = {0};
  my_allocator_t allocator = {&state, css_test_alloc, css_test_calloc,
                              css_test_realloc, css_test_free};
  my_css_error_t error = {0};

  ASSERT_NOT_NULL(css);
  memset(css, ' ', length);
  ASSERT_TRUE(my_css_parse(&allocator, css, length, &error) == NULL);
  ASSERT_EQ(state.alloc_calls, 0u);
  ASSERT_TRUE(error.msg[0] != '\0');
  free(css);
}

TEST(theme_css_rejects_unterminated_input_with_bounded_scan)
{
  char* css = (char*)malloc(MY_CSS_MAX_BYTES);
  css_alloc_state_t state = {0};
  my_allocator_t allocator = {&state, css_test_alloc, css_test_calloc,
                              css_test_realloc, css_test_free};
  my_theme_t* theme;
  size_t calls_before;

  ASSERT_NOT_NULL(css);
  memset(css, ' ', MY_CSS_MAX_BYTES);
  theme = my_theme_create(&allocator);
  ASSERT_NOT_NULL(theme);
  calls_before = state.alloc_calls;
  ASSERT_EQ(my_theme_load_css(theme, css), MY_RET_FAIL);
  ASSERT_EQ(state.alloc_calls, calls_before);
  my_theme_destroy(theme);
  ASSERT_EQ(state.live_count, 0);
  free(css);
}

TEST_MAIN_BEGIN()
    RUN_TEST(css_universal_selector_applies_to_any_widget);
    RUN_TEST(widget_local_style_write_invalidates_retained_pixels);
    RUN_TEST(widget_local_style_rejects_invalid_request_without_allocation);
    RUN_TEST(widget_local_style_oom_does_not_leave_empty_style);
    RUN_TEST(css_multiple_classes_match_as_a_set);
    RUN_TEST(css_same_specificity_uses_later_source_rule);
    RUN_TEST(css_specificity_beats_later_lower_specificity);
    RUN_TEST(css_normal_specificity_survives_state_fallback);
    RUN_TEST(css_numeric_values_are_finite_and_bounded);
    RUN_TEST(css_specificity_compares_across_selector_levels);
    RUN_TEST(theme_specificity_is_stored_per_property);
    RUN_TEST(css_class_selector_is_safe_without_widget_classes);
    RUN_TEST(css_child_combinator_matches_only_direct_parent);
    RUN_TEST(css_child_parent_classes_match_as_a_set);
    RUN_TEST(css_multilevel_selector_chain_matches);
    RUN_TEST(css_multilevel_direct_path_rejects_wrong_intermediate);
    RUN_TEST(css_multilevel_ancestor_id_and_class_must_match);
    RUN_TEST(css_multilevel_specificity_beats_simple_selector);
    RUN_TEST(css_rejects_selector_paths_over_depth_limit);
    RUN_TEST(css_rejects_dangling_and_repeated_combinators);
    RUN_TEST(css_rejects_adjacent_selector_tokens_without_combinator);
    RUN_TEST(css_comments_preserve_descendant_separator);
    RUN_TEST(css_unsupported_at_rules_ignore_braces_in_strings_and_comments);
    RUN_TEST(css_import_resolver_flattens_sources_in_source_order);
    RUN_TEST(css_import_without_resolver_is_rejected_in_strict_mode);
    RUN_TEST(css_import_cycle_and_depth_are_bounded);
    RUN_TEST(css_import_rejects_absolute_and_traversal_paths);
    RUN_TEST(css_scope_applies_rules_only_inside_root);
    RUN_TEST(css_scope_accepts_to_clause_and_rejects_malformed_limit);
    RUN_TEST(css_scope_to_clause_accepts_implicit_root);
    RUN_TEST(css_scope_implicit_root_to_clause_excludes_boundary);
    RUN_TEST(css_scope_implicit_root_rejects_malformed_limit);
    RUN_TEST(css_scope_rejects_malformed_root_with_scope_capability);
    RUN_TEST(css_scope_to_clause_supports_universal_limit);
    RUN_TEST(css_scope_universal_limit_excludes_every_ancestor_boundary);
    RUN_TEST(css_scope_to_clause_supports_compound_limit);
    RUN_TEST(css_scope_to_clause_supports_limit_selector_list);
    RUN_TEST(css_scope_limit_selector_list_excludes_any_matching_boundary);
    RUN_TEST(theme_scope_implicit_root_api_boundary_is_bounded);
    RUN_TEST(css_scope_nested_implicit_and_explicit_boundaries);
    RUN_TEST(css_scope_accepts_class_id_universal_and_implicit_roots);
    RUN_TEST(css_scope_class_and_id_roots_match_theme_ancestors);
    RUN_TEST(css_scope_universal_root_matches_theme_ancestors);
    RUN_TEST(css_scope_composes_with_media_supports_and_layer);
    RUN_TEST(css_scope_to_clause_excludes_nested_boundary);
    RUN_TEST(css_scope_to_clause_excludes_boundary_element_itself);
    RUN_TEST(css_scope_to_clause_excludes_root_when_limit_matches_root);
    RUN_TEST(css_scope_to_clause_survives_theme_clone);
    RUN_TEST(css_scope_to_clause_supports_class_and_id_limits);
    RUN_TEST(css_nested_scope_to_clauses_preserve_each_boundary);
    RUN_TEST(css_import_budget_failure_is_transactional);
    RUN_TEST(theme_css_import_failure_preserves_existing_theme);
    RUN_TEST(theme_css_import_applies_imported_rules);
    RUN_TEST(css_supports_single_declaration_is_evaluated_at_parse_time);
    RUN_TEST(css_supports_logical_conditions_are_evaluated_at_parse_time);
    RUN_TEST(css_supports_logical_conditions_reject_invalid_operator);
    RUN_TEST(css_supports_logical_conditions_honor_precedence_and_depth_limit);
    RUN_TEST(css_supports_rejects_complex_conditions_and_unknown_values);
    RUN_TEST(css_supports_compatibility_mode_skips_unsupported_query);
    RUN_TEST(css_supports_key_aliases_and_typed_values);
    RUN_TEST(css_supports_query_budget_and_malformed_query_are_transactional);
    RUN_TEST(theme_strict_css_accepts_supported_supports);
    RUN_TEST(css_media_all_and_screen_expand_rules);
    RUN_TEST(css_media_nested_all_expands_without_query_cost);
    RUN_TEST(css_conditional_media_context_filters_rules_at_parse_time);
    RUN_TEST(css_conditional_media_theme_load_is_transactional);
    RUN_TEST(css_conditional_media_filters_logical_viewport_width);
    RUN_TEST(css_conditional_media_supports_orientation_and_motion_preferences);
    RUN_TEST(css_conditional_media_rejects_oversized_query_and_invalid_units);
    RUN_TEST(css_conditional_media_rejects_missing_and_operator);
    RUN_TEST(css_conditional_media_supports_bounded_range_syntax);
    RUN_TEST(css_conditional_media_supports_device_capabilities);
    RUN_TEST(css_conditional_media_rejects_unknown_device_capability_value);
    RUN_TEST(css_conditional_media_device_capabilities_follow_level_semantics);
    RUN_TEST(css_conditional_media_rejects_unknown_device_capability_bits);
    RUN_TEST(css_conditional_media_unknown_facts_do_not_match_negative_queries);
    RUN_TEST(css_conditional_media_not_preserves_unknown_facts);
    RUN_TEST(css_conditional_media_not_rejects_bounded_combinations);
    RUN_TEST(css_extended_media_context_validates_known_mask);
    RUN_TEST(css_conditional_media_rejects_invalid_range_syntax);
    RUN_TEST(css_media_nesting_is_bounded);
    RUN_TEST(css_strict_mode_rejects_unsupported_at_rules);
    RUN_TEST(css_layers_override_specificity_and_unlayered_rules);
    RUN_TEST(css_layer_order_statement_is_respected);
    RUN_TEST(css_late_layer_order_statement_reorders_existing_rules);
    RUN_TEST(css_layer_rejects_empty_duplicate_and_oversized_names);
    RUN_TEST(css_capability_registry_is_static_and_explicit);
    RUN_TEST(css_strict_error_identifies_missing_capability);
    RUN_TEST(css_error_codes_distinguish_policy_and_budget);
    RUN_TEST(css_parse_rejects_unknown_policy_flags);
    RUN_TEST(theme_strict_css_rejects_at_rule_without_mutation);
    RUN_TEST(theme_css_load_preserves_existing_entries);
    RUN_TEST(theme_css_load_overrides_existing_property);
    RUN_TEST(theme_css_load_preserves_existing_specificity);
    RUN_TEST(theme_css_load_rolls_back_clone_oom);
    RUN_TEST(theme_text_load_rolls_back_malformed_later_line);
    RUN_TEST(theme_text_rejects_unterminated_input_with_bounded_scan);
    RUN_TEST(theme_set_rolls_back_new_property_value_oom);
    RUN_TEST(theme_set_rolls_back_new_entry_value_oom);
    RUN_TEST(default_theme_creation_rolls_back_oom);
    RUN_TEST(css_structural_errors_reject_without_error_storage);
    RUN_TEST(css_parser_rejects_oversized_input_before_allocation);
    RUN_TEST(theme_css_rejects_unterminated_input_with_bounded_scan);
TEST_MAIN_END()
