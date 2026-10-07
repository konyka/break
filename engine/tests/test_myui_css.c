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

TEST(css_decl_important_flag_and_cascade)
{
  /* R654: `!important` — a declaration-level flag (public on my_css_decl_t)
   * that lifts the declaration into a flat top cascade tier: important
   * beats every normal declaration regardless of selector specificity or
   * layer; among important declarations the usual order applies. The subset
   * accepts lowercase `important` with optional whitespace after '!'. */
  const char* css =
      "button { color: red !important; font-size: 14px; }"
      "label { color: blue ! important; }";
  const char* malformed[] = {
      "button { color: red !foo; }",
      "button { color: red !IMPORTANT; }",
      "button { color: red !; }"};
  my_css_error_t error = {0};
  my_css_sheet_t* sheet = my_css_parse_ex(
      NULL, css, strlen(css), MY_CSS_PARSE_STRICT_AT_RULES, &error);
  size_t i;

  ASSERT_NOT_NULL(sheet);
  ASSERT_EQ(my_css_rule_count(sheet), 2u);
  ASSERT_EQ(my_css_decl_count(my_css_rule(sheet, 0u)), 2u);
  ASSERT_TRUE(my_css_decl(my_css_rule(sheet, 0u), 0u)->important);
  ASSERT_FALSE(my_css_decl(my_css_rule(sheet, 0u), 1u)->important);
  ASSERT_TRUE(my_css_decl(my_css_rule(sheet, 1u), 0u)->important);
  my_css_sheet_destroy(sheet);

  for (i = 0u; i < sizeof(malformed) / sizeof(malformed[0]); ++i) {
    memset(&error, 0, sizeof(error));
    ASSERT_TRUE(my_css_parse_ex(NULL, malformed[i], strlen(malformed[i]),
                                MY_CSS_PARSE_STRICT_AT_RULES,
                                &error) == NULL);
  }

  /* specificity flip: the multilevel selector would normally win. */
  {
    const char* flip =
        "window.primary panel button { color: blue; }"
        "button { color: red !important; }";
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
    ASSERT_EQ(my_theme_load_css_ex(theme, flip, MY_CSS_PARSE_STRICT_AT_RULES),
              MY_RET_OK);
    value = my_theme_get_for_widget(theme, button, MY_STATE_NORMAL,
                                    "fg_color");
    ASSERT_NOT_NULL(value);
    ASSERT_EQ(my_value_get_uint32(value), 0xFF0000FFu);
    my_widget_unref(window);
    my_theme_destroy(theme);
  }

  /* layer flip: unlayered normal loses to layered important. */
  {
    const char* layered =
        "@layer base { button { color: red !important; } }"
        "button { color: blue; }";
    my_theme_t* theme = my_theme_create(NULL);
    my_widget_t* widget = my_widget_create(NULL, "button");
    const my_value_t* value;

    ASSERT_NOT_NULL(theme);
    ASSERT_NOT_NULL(widget);
    widget->widget_type = "button";
    ASSERT_EQ(my_theme_load_css_ex(theme, layered,
                                   MY_CSS_PARSE_STRICT_AT_RULES),
              MY_RET_OK);
    value = my_theme_get_for_widget(theme, widget, MY_STATE_NORMAL,
                                    "fg_color");
    ASSERT_NOT_NULL(value);
    ASSERT_EQ(my_value_get_uint32(value), 0xFF0000FFu);
    my_widget_unref(widget);
    my_theme_destroy(theme);
  }

  /* among important declarations the usual source order applies. */
  {
    const char* order =
        "button { color: red !important; }"
        "button { color: blue !important; }";
    my_theme_t* theme = my_theme_create(NULL);
    my_widget_t* widget = my_widget_create(NULL, "button");
    const my_value_t* value;

    ASSERT_NOT_NULL(theme);
    ASSERT_NOT_NULL(widget);
    widget->widget_type = "button";
    ASSERT_EQ(my_theme_load_css_ex(theme, order, MY_CSS_PARSE_STRICT_AT_RULES),
              MY_RET_OK);
    value = my_theme_get_for_widget(theme, widget, MY_STATE_NORMAL,
                                    "fg_color");
    ASSERT_NOT_NULL(value);
    ASSERT_EQ(my_value_get_uint32(value), 0x0000FFFFu);
    my_widget_unref(widget);
    my_theme_destroy(theme);
  }
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
                                    NULL, NULL};
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

TEST(css_container_size_queries_evaluate_at_parse_time)
{
  /* R663: @container phase 1 — unnamed size queries evaluate at parse
   * time against the host-injected container context (the @media pattern).
   * Only size features are legal (width/height family, orientation,
   * aspect-ratio, including range forms and boolean logic). */
  const char* hit =
      "@container (min-width: 700px) { button { color: red; } }"
      "@container (width >= 700px) and (height <= 600px) { label { color: blue; } }"
      "@container (orientation: landscape) { edit { color: green; } }"
      "@container (aspect-ratio: 4/3) { slider { color: white; } }"
      "@container (min-width: 900px) or (min-height: 500px) { check { color: black; } }"
      "@container not (min-width: 900px) { radio { color: gray; } }";
  const char* miss = "@container (min-width: 900px) { button { color: red; } }";
  const char* malformed[] = {
      /* named queries need the match layer (R670): with an injected
       * context (parse-time mode) a name still rejects */
      "@container side (min-width: 1px) { button { color: red; } }",
      /* non-size features are invalid in container queries */
      "@container (hover: hover) { button { color: red; } }",
      /* media types belong to @media */
      "@container screen and (min-width: 1px) { button { color: red; } }",
      "@container (min-width: nope) { button { color: red; } }"};
  const char* too_deep =
      "@container (min-width: 1px) { @container (min-width: 1px) {"
      " @container (min-width: 1px) { @container (min-width: 1px) {"
      " @container (min-width: 1px) { button { color: red; } } } } } }";
  my_css_container_context_t container = {800u, 600u};
  my_css_parse_options_t options = {0};
  my_css_error_t error = {0};
  my_css_sheet_t* sheet;
  size_t i;

  options.flags = MY_CSS_PARSE_STRICT_AT_RULES;
  options.container = &container;

  sheet = my_css_parse_with_options(NULL, hit, strlen(hit), &options, &error);
  ASSERT_NOT_NULL(sheet);
  ASSERT_EQ(my_css_rule_count(sheet), 6u);
  ASSERT_STR_EQ(my_css_selector(my_css_rule(sheet, 0u), 0u)->widget_type,
                "button");
  ASSERT_STR_EQ(my_css_selector(my_css_rule(sheet, 5u), 0u)->widget_type,
                "radio");
  my_css_sheet_destroy(sheet);

  memset(&error, 0, sizeof(error));
  sheet = my_css_parse_with_options(NULL, miss, strlen(miss), &options,
                                    &error);
  ASSERT_NOT_NULL(sheet);
  ASSERT_EQ(my_css_rule_count(sheet), 0u);
  my_css_sheet_destroy(sheet);

  for (i = 0u; i < sizeof(malformed) / sizeof(malformed[0]); ++i) {
    memset(&error, 0, sizeof(error));
    ASSERT_TRUE(my_css_parse_with_options(NULL, malformed[i],
                                          strlen(malformed[i]), &options,
                                          &error) == NULL);
  }
  memset(&error, 0, sizeof(error));
  ASSERT_TRUE(my_css_parse_with_options(NULL, too_deep, strlen(too_deep),
                                        &options, &error) == NULL);

  /* no container context (R670 contract change): the query now DEFERS
   * to match time in both modes — the rule carries the condition for
   * the lookup layer instead of rejecting (strict) or skipping. */
  options.container = NULL;
  memset(&error, 0, sizeof(error));
  sheet = my_css_parse_with_options(NULL, miss, strlen(miss), &options,
                                    &error);
  ASSERT_NOT_NULL(sheet);
  ASSERT_EQ(my_css_rule_count(sheet), 1u);
  ASSERT_STR_EQ(my_css_rule(sheet, 0u)->container_query,
                "(min-width: 900px)");
  ASSERT_STR_EQ(my_css_rule(sheet, 0u)->container_name, "");
  my_css_sheet_destroy(sheet);
  options.flags = 0u;
  memset(&error, 0, sizeof(error));
  sheet = my_css_parse_with_options(NULL, miss, strlen(miss), &options,
                                    &error);
  ASSERT_NOT_NULL(sheet);
  ASSERT_EQ(my_css_rule_count(sheet), 1u);
  ASSERT_STR_EQ(my_css_rule(sheet, 0u)->container_query,
                "(min-width: 900px)");
  my_css_sheet_destroy(sheet);
}

TEST(css_container_nested_in_rule_blocks)
{
  /* @container is a conditional group, so CSS Nesting admits it into a
   * declaration block — matching declarations merge in source order. */
  const char* css =
      "button { color: blue; @container (min-width: 700px) { color: red; } }"
      "label { color: green; @container (min-width: 900px) { color: white; } }";
  const char* theme_css =
      "button { color: blue; @container (min-width: 700px) { color: red; } }";
  my_css_container_context_t container = {800u, 600u};
  my_css_parse_options_t options = {0};
  my_css_error_t error = {0};
  my_css_sheet_t* sheet;
  my_theme_t* theme;
  my_widget_t* widget;
  const my_value_t* value;

  options.flags = MY_CSS_PARSE_STRICT_AT_RULES;
  options.container = &container;

  sheet = my_css_parse_with_options(NULL, css, strlen(css), &options, &error);
  ASSERT_NOT_NULL(sheet);
  ASSERT_EQ(my_css_rule_count(sheet), 2u);
  /* the matching group's declaration lands last on the same rule. */
  ASSERT_EQ(my_css_decl_count(my_css_rule(sheet, 0u)), 2u);
  ASSERT_EQ(my_css_decl_count(my_css_rule(sheet, 1u)), 1u);
  my_css_sheet_destroy(sheet);

  theme = my_theme_create(NULL);
  widget = my_widget_create(NULL, "button");
  ASSERT_NOT_NULL(theme);
  ASSERT_NOT_NULL(widget);
  widget->widget_type = "button";
  ASSERT_EQ(my_theme_load_css_with_options(theme, theme_css, &options),
            MY_RET_OK);
  value = my_theme_get_for_widget(theme, widget, MY_STATE_NORMAL, "fg_color");
  ASSERT_NOT_NULL(value);
  ASSERT_EQ(my_value_get_uint32(value), 0xFF0000FFu);
  my_widget_unref(widget);
  my_theme_destroy(theme);
}

TEST(css_custom_properties_store_raw_token_streams)
{
  /* R665: CSS Custom Properties phase 1 — `--*` declarations capture the
   * raw token stream (Custom Properties L1 stores values as specified;
   * var() substitution is a later phase). The capture is quote/depth
   * aware, strips a trailing top-level `!important`, and the decl flows
   * through the existing cascade/theme machinery unchanged. */
  const char* css =
      "button { --gap: 8px; --border: 1px solid red; --empty:; color: blue; }";
  const char* quoted =
      "button { --u: url(\"a;b.png\") 2px; --y: var(--x); }";
  const char* flagged = "button { --x: 8px !important; }";
  const char* bad_bang = "button { --x: 8px !foo; color: red; }";
  const char* unbalanced = "button { --x: (a; color: red; }";
  const char* cascade =
      "button { --brand: #369; } button { --brand: #036; }"
      ".fancy { --brand: #fff; }";
  const char* important_wins =
      "button { --x: a !important; } .fancy { --x: b; }";
  my_css_error_t error = {0};
  my_css_sheet_t* sheet;
  const my_css_rule_t* rule;
  my_theme_t* theme;
  my_widget_t* widget;
  const my_value_t* value;

  /* raw capture: multi-token values survive verbatim (ws-trimmed). */
  sheet = my_css_parse_ex(NULL, css, strlen(css),
                          MY_CSS_PARSE_STRICT_AT_RULES, &error);
  ASSERT_NOT_NULL(sheet);
  rule = my_css_rule(sheet, 0u);
  ASSERT_EQ(my_css_decl_count(rule), 4u);
  ASSERT_STR_EQ(my_css_decl(rule, 0u)->key, "--gap");
  ASSERT_STR_EQ(my_value_get_str(&my_css_decl(rule, 0u)->value), "8px");
  ASSERT_STR_EQ(my_value_get_str(&my_css_decl(rule, 1u)->value),
                "1px solid red");
  ASSERT_STR_EQ(my_value_get_str(&my_css_decl(rule, 2u)->value), "");
  ASSERT_EQ(my_value_type(&my_css_decl(rule, 3u)->value), MY_VALUE_UINT32);
  my_css_sheet_destroy(sheet);

  /* ';' inside quotes does not terminate; var() stays unresolved text. */
  memset(&error, 0, sizeof(error));
  sheet = my_css_parse_ex(NULL, quoted, strlen(quoted),
                          MY_CSS_PARSE_STRICT_AT_RULES, &error);
  ASSERT_NOT_NULL(sheet);
  rule = my_css_rule(sheet, 0u);
  ASSERT_EQ(my_css_decl_count(rule), 2u);
  ASSERT_STR_EQ(my_value_get_str(&my_css_decl(rule, 0u)->value),
                "url(\"a;b.png\") 2px");
  ASSERT_STR_EQ(my_value_get_str(&my_css_decl(rule, 1u)->value), "var(--x)");
  my_css_sheet_destroy(sheet);

  /* trailing top-level `!important` sets the flag and is stripped. */
  memset(&error, 0, sizeof(error));
  sheet = my_css_parse_ex(NULL, flagged, strlen(flagged),
                          MY_CSS_PARSE_STRICT_AT_RULES, &error);
  ASSERT_NOT_NULL(sheet);
  rule = my_css_rule(sheet, 0u);
  ASSERT_EQ(my_css_decl_count(rule), 1u);
  ASSERT_TRUE(my_css_decl(rule, 0u)->important);
  ASSERT_STR_EQ(my_value_get_str(&my_css_decl(rule, 0u)->value), "8px");
  my_css_sheet_destroy(sheet);

  /* a top-level '!' that is not `!important` invalidates just the decl. */
  memset(&error, 0, sizeof(error));
  sheet = my_css_parse_ex(NULL, bad_bang, strlen(bad_bang),
                          MY_CSS_PARSE_STRICT_AT_RULES, &error);
  ASSERT_NOT_NULL(sheet);
  rule = my_css_rule(sheet, 0u);
  ASSERT_EQ(my_css_decl_count(rule), 1u);
  ASSERT_STR_EQ(my_css_decl(rule, 0u)->key, "fg_color");
  my_css_sheet_destroy(sheet);

  /* unbalanced capture swallows the block — truthful parse failure. */
  memset(&error, 0, sizeof(error));
  ASSERT_TRUE(my_css_parse_ex(NULL, unbalanced, strlen(unbalanced),
                              MY_CSS_PARSE_STRICT_AT_RULES,
                              &error) == NULL);

  /* theme cascade: later source order wins; class specificity wins. */
  theme = my_theme_create(NULL);
  widget = my_widget_create(NULL, "button");
  ASSERT_NOT_NULL(theme);
  ASSERT_NOT_NULL(widget);
  widget->widget_type = "button";
  ASSERT_EQ(my_theme_load_css_ex(theme, cascade, MY_CSS_PARSE_STRICT_AT_RULES),
            MY_RET_OK);
  value = my_theme_get_for_widget(theme, widget, MY_STATE_NORMAL, "--brand");
  ASSERT_NOT_NULL(value);
  ASSERT_STR_EQ(my_value_get_str(value), "#036");
  ASSERT_EQ(my_widget_set_style_class(widget, "fancy"), MY_RET_OK);
  value = my_theme_get_for_widget(theme, widget, MY_STATE_NORMAL, "--brand");
  ASSERT_NOT_NULL(value);
  ASSERT_STR_EQ(my_value_get_str(value), "#fff");
  my_widget_unref(widget);
  my_theme_destroy(theme);

  /* !important weighting applies to custom properties too. */
  theme = my_theme_create(NULL);
  widget = my_widget_create(NULL, "button");
  ASSERT_NOT_NULL(theme);
  ASSERT_NOT_NULL(widget);
  widget->widget_type = "button";
  ASSERT_EQ(my_widget_set_style_class(widget, "fancy"), MY_RET_OK);
  ASSERT_EQ(my_theme_load_css_ex(theme, important_wins,
                                 MY_CSS_PARSE_STRICT_AT_RULES),
            MY_RET_OK);
  value = my_theme_get_for_widget(theme, widget, MY_STATE_NORMAL, "--x");
  ASSERT_NOT_NULL(value);
  ASSERT_STR_EQ(my_value_get_str(value), "a");
  my_widget_unref(widget);
  my_theme_destroy(theme);
}

TEST(css_var_substitution_resolves_at_lookup_time)
{
  /* R666: var() phase 2 — a declaration whose value mentions var( is
   * stored as raw text (no more sheet-level failure) and resolved at
   * lookup against the element's custom properties (own cascade first,
   * then DOM inheritance), with fallback chains and cycle detection
   * (invalid at computed-value time → the getter reports unset). */
  const char* basic = "button { --brand: #036; color: var(--brand); }";
  const char* fallback = "button { color: var(--missing, red); }";
  const char* defined_wins = "button { --x: blue; color: var(--x, red); }";
  const char* chained =
      "button { --a: var(--b); --b: #123456; color: var(--a); }";
  const char* nested_fallback = "button { color: var(--x, var(--y, green)); }";
  const char* cyclic =
      "button { --x: var(--y); --y: var(--x); color: var(--x, #010203); }";
  const char* cyclic_unset =
      "button { --x: var(--y); --y: var(--x); color: var(--x); }";
  const char* missing_unset = "button { color: var(--missing); }";
  const char* inherited =
      "window { --brand: #0F1E2D; } button { color: var(--brand); }";
  const char* numeric = "button { --w: 12px; border-width: var(--w); }";
  const char* typed = "button { color: red; }";
  my_css_error_t error = {0};
  my_css_sheet_t* sheet;
  my_theme_t* theme;
  my_widget_t* widget;
  my_widget_t* window;
  my_value_t out;

  my_value_init(&out, NULL);

  /* parse level: var() no longer hard-fails the sheet; stored raw. */
  sheet = my_css_parse_ex(NULL, basic, strlen(basic),
                          MY_CSS_PARSE_STRICT_AT_RULES, &error);
  ASSERT_NOT_NULL(sheet);
  ASSERT_EQ(my_css_decl_count(my_css_rule(sheet, 0u)), 2u);
  ASSERT_STR_EQ(
      my_value_get_str(&my_css_decl(my_css_rule(sheet, 0u), 1u)->value),
      "var(--brand)");
  my_css_sheet_destroy(sheet);

  /* basic substitution. */
  theme = my_theme_create(NULL);
  widget = my_widget_create(NULL, "button");
  ASSERT_NOT_NULL(theme);
  ASSERT_NOT_NULL(widget);
  widget->widget_type = "button";
  ASSERT_EQ(my_theme_load_css_ex(theme, basic, MY_CSS_PARSE_STRICT_AT_RULES),
            MY_RET_OK);
  ASSERT_TRUE(my_theme_get_for_widget_var(theme, widget, MY_STATE_NORMAL,
                                          "fg_color", &out));
  ASSERT_EQ(my_value_get_uint32(&out), 0x003366FFu);
  my_widget_unref(widget);
  my_theme_destroy(theme);

  /* fallback used when the name is missing. */
  theme = my_theme_create(NULL);
  widget = my_widget_create(NULL, "button");
  widget->widget_type = "button";
  ASSERT_EQ(my_theme_load_css_ex(theme, fallback,
                                 MY_CSS_PARSE_STRICT_AT_RULES),
            MY_RET_OK);
  ASSERT_TRUE(my_theme_get_for_widget_var(theme, widget, MY_STATE_NORMAL,
                                          "fg_color", &out));
  ASSERT_EQ(my_value_get_uint32(&out), 0xFF0000FFu);
  my_widget_unref(widget);
  my_theme_destroy(theme);

  /* a defined name wins over the fallback. */
  theme = my_theme_create(NULL);
  widget = my_widget_create(NULL, "button");
  widget->widget_type = "button";
  ASSERT_EQ(my_theme_load_css_ex(theme, defined_wins,
                                 MY_CSS_PARSE_STRICT_AT_RULES),
            MY_RET_OK);
  ASSERT_TRUE(my_theme_get_for_widget_var(theme, widget, MY_STATE_NORMAL,
                                          "fg_color", &out));
  ASSERT_EQ(my_value_get_uint32(&out), 0x0000FFFFu);
  my_widget_unref(widget);
  my_theme_destroy(theme);

  /* custom properties may reference other custom properties. */
  theme = my_theme_create(NULL);
  widget = my_widget_create(NULL, "button");
  widget->widget_type = "button";
  ASSERT_EQ(my_theme_load_css_ex(theme, chained, MY_CSS_PARSE_STRICT_AT_RULES),
            MY_RET_OK);
  ASSERT_TRUE(my_theme_get_for_widget_var(theme, widget, MY_STATE_NORMAL,
                                          "fg_color", &out));
  ASSERT_EQ(my_value_get_uint32(&out), 0x123456FFu);
  my_widget_unref(widget);
  my_theme_destroy(theme);

  /* fallbacks nest. */
  theme = my_theme_create(NULL);
  widget = my_widget_create(NULL, "button");
  widget->widget_type = "button";
  ASSERT_EQ(my_theme_load_css_ex(theme, nested_fallback,
                                 MY_CSS_PARSE_STRICT_AT_RULES),
            MY_RET_OK);
  ASSERT_TRUE(my_theme_get_for_widget_var(theme, widget, MY_STATE_NORMAL,
                                          "fg_color", &out));
  ASSERT_EQ(my_value_get_uint32(&out), 0x008000FFu);
  my_widget_unref(widget);
  my_theme_destroy(theme);

  /* a cycle invalidates the reference — the fallback applies. */
  theme = my_theme_create(NULL);
  widget = my_widget_create(NULL, "button");
  widget->widget_type = "button";
  ASSERT_EQ(my_theme_load_css_ex(theme, cyclic, MY_CSS_PARSE_STRICT_AT_RULES),
            MY_RET_OK);
  ASSERT_TRUE(my_theme_get_for_widget_var(theme, widget, MY_STATE_NORMAL,
                                          "fg_color", &out));
  ASSERT_EQ(my_value_get_uint32(&out), 0x010203FFu);
  my_widget_unref(widget);
  my_theme_destroy(theme);

  /* ... and without a fallback the property is unset. */
  theme = my_theme_create(NULL);
  widget = my_widget_create(NULL, "button");
  widget->widget_type = "button";
  ASSERT_EQ(my_theme_load_css_ex(theme, cyclic_unset,
                                 MY_CSS_PARSE_STRICT_AT_RULES),
            MY_RET_OK);
  ASSERT_TRUE(!my_theme_get_for_widget_var(theme, widget, MY_STATE_NORMAL,
                                           "fg_color", &out));
  my_widget_unref(widget);
  my_theme_destroy(theme);

  theme = my_theme_create(NULL);
  widget = my_widget_create(NULL, "button");
  widget->widget_type = "button";
  ASSERT_EQ(my_theme_load_css_ex(theme, missing_unset,
                                 MY_CSS_PARSE_STRICT_AT_RULES),
            MY_RET_OK);
  ASSERT_TRUE(!my_theme_get_for_widget_var(theme, widget, MY_STATE_NORMAL,
                                           "fg_color", &out));
  my_widget_unref(widget);
  my_theme_destroy(theme);

  /* custom properties inherit down the widget tree. */
  theme = my_theme_create(NULL);
  window = my_widget_create(NULL, "window");
  widget = my_widget_create(NULL, "button");
  ASSERT_NOT_NULL(theme);
  ASSERT_NOT_NULL(window);
  ASSERT_NOT_NULL(widget);
  window->widget_type = "window";
  widget->widget_type = "button";
  ASSERT_EQ(my_widget_add_child(window, widget), MY_RET_OK);
  my_widget_unref(widget);
  ASSERT_EQ(my_theme_load_css_ex(theme, inherited,
                                 MY_CSS_PARSE_STRICT_AT_RULES),
            MY_RET_OK);
  ASSERT_TRUE(my_theme_get_for_widget_var(theme, widget, MY_STATE_NORMAL,
                                          "fg_color", &out));
  ASSERT_EQ(my_value_get_uint32(&out), 0x0F1E2DFFu);
  my_widget_unref(window);
  my_theme_destroy(theme);

  /* numeric substitution through a length-typed property. */
  theme = my_theme_create(NULL);
  widget = my_widget_create(NULL, "button");
  widget->widget_type = "button";
  ASSERT_EQ(my_theme_load_css_ex(theme, numeric, MY_CSS_PARSE_STRICT_AT_RULES),
            MY_RET_OK);
  ASSERT_TRUE(my_theme_get_for_widget_var(theme, widget, MY_STATE_NORMAL,
                                          "border_width", &out));
  ASSERT_EQ(my_value_get_int32(&out), 12);
  my_widget_unref(widget);
  my_theme_destroy(theme);

  /* typed (var-free) values pass through untouched. */
  theme = my_theme_create(NULL);
  widget = my_widget_create(NULL, "button");
  widget->widget_type = "button";
  ASSERT_EQ(my_theme_load_css_ex(theme, typed, MY_CSS_PARSE_STRICT_AT_RULES),
            MY_RET_OK);
  ASSERT_TRUE(my_theme_get_for_widget_var(theme, widget, MY_STATE_NORMAL,
                                          "fg_color", &out));
  ASSERT_EQ(my_value_get_uint32(&out), 0xFF0000FFu);
  my_widget_unref(widget);
  my_theme_destroy(theme);

  my_value_reset(&out);
}

TEST(css_var_flows_through_widget_style_accessors)
{
  /* R667: consumer migration — my_widget_style_get_color/_int resolve
   * var() declarations through the themed-ancestor chain, so theme
   * tokens actually reach the screen. Local-style strings stay literal
   * (the var contract is a theme-CSS feature). */
  const char* css =
      "button { --brand: #036; background-color: var(--brand);"
      " border-width: var(--w, 3px); color: var(--missing); }";
  const char* inherited =
      "window { --brand: #0F1E2D; } button { background-color: var(--brand); }";
  my_theme_t* theme = my_theme_create(NULL);
  my_widget_t* widget = my_widget_create(NULL, "button");
  my_theme_t* theme2;
  my_widget_t* window;
  my_widget_t* child;
  my_value_t local;
  ASSERT_NOT_NULL(theme);
  ASSERT_NOT_NULL(widget);
  widget->widget_type = "button";
  ASSERT_EQ(my_theme_load_css_ex(theme, css, MY_CSS_PARSE_STRICT_AT_RULES),
            MY_RET_OK);
  ASSERT_EQ(my_widget_apply_theme(widget, theme), MY_RET_OK);
  /* color/length tokens resolve through the typed accessors. */
  ASSERT_EQ(my_widget_style_get_color(widget, MY_STATE_NORMAL, "bg_color",
                                      0xDEADBEEFu),
            0x003366FFu);
  ASSERT_EQ(my_widget_style_get_int(widget, MY_STATE_NORMAL, "border_width",
                                    99),
            3);
  /* invalid at computed-value time -> the caller's fallback. */
  ASSERT_EQ(my_widget_style_get_color(widget, MY_STATE_NORMAL, "fg_color",
                                      0xDEADBEEFu),
            0xDEADBEEFu);
  /* local-style strings stay literal — no var resolution off-theme. */
  my_value_init(&local, NULL);
  ASSERT_EQ(my_value_set_str(&local, "var(--brand)"), MY_RET_OK);
  ASSERT_EQ(my_widget_style_set(widget, MY_STATE_NORMAL, "fg_color", &local),
            MY_RET_OK);
  my_value_reset(&local);
  ASSERT_EQ(my_widget_style_get_color(widget, MY_STATE_NORMAL, "fg_color",
                                      0xDEADBEEFu),
            0xDEADBEEFu);
  my_widget_unref(widget);
  my_theme_destroy(theme);

  /* the themed-ancestor chain: a child without a theme resolves through
   * the nearest themed ancestor (and inherits the custom property). */
  theme2 = my_theme_create(NULL);
  window = my_widget_create(NULL, "window");
  child = my_widget_create(NULL, "button");
  ASSERT_NOT_NULL(theme2);
  ASSERT_NOT_NULL(window);
  ASSERT_NOT_NULL(child);
  window->widget_type = "window";
  child->widget_type = "button";
  ASSERT_EQ(my_widget_add_child(window, child), MY_RET_OK);
  my_widget_unref(child);
  ASSERT_EQ(my_theme_load_css_ex(theme2, inherited,
                                 MY_CSS_PARSE_STRICT_AT_RULES),
            MY_RET_OK);
  ASSERT_EQ(my_widget_apply_theme(window, theme2), MY_RET_OK);
  ASSERT_EQ(my_widget_style_get_color(child, MY_STATE_NORMAL, "bg_color",
                                      0xDEADBEEFu),
            0x0F1E2DFFu);
  my_widget_unref(window);
  my_theme_destroy(theme2);
}

TEST(css_container_properties_parse_and_cascade)
{
  /* R669: @container phase 2 slice 1 — container-type / container-name
   * are real style properties (new keys container_type/container_name).
   * container-type validates its keyword set (normal/size/inline-size);
   * container-name stores the raw ident list (`none` only alone). The
   * match-time container resolution they feed is a later slice. */
  const char* css =
      "panel { container-type: inline-size; container-name: sidebar; }";
  const char* multi = "panel { container-name: sidebar main; }";
  const char* bad_type =
      "panel { container-type: bogus; container-name: x; }";
  const char* bad_name = "panel { container-name: none sidebar; color: red; }";
  const char* none_name = "panel { container-name: none; }";
  const char* cascade =
      "panel { container-type: inline-size; } .sized { container-type: size; }";
  my_css_error_t error = {0};
  my_css_sheet_t* sheet;
  const my_css_rule_t* rule;
  my_theme_t* theme;
  my_widget_t* widget;
  const my_value_t* value;

  /* parse + store under the new internal keys. */
  sheet = my_css_parse_ex(NULL, css, strlen(css),
                          MY_CSS_PARSE_STRICT_AT_RULES, &error);
  ASSERT_NOT_NULL(sheet);
  rule = my_css_rule(sheet, 0u);
  ASSERT_EQ(my_css_decl_count(rule), 2u);
  ASSERT_STR_EQ(my_css_decl(rule, 0u)->key, "container_type");
  ASSERT_STR_EQ(my_value_get_str(&my_css_decl(rule, 0u)->value),
                "inline-size");
  ASSERT_STR_EQ(my_css_decl(rule, 1u)->key, "container_name");
  ASSERT_STR_EQ(my_value_get_str(&my_css_decl(rule, 1u)->value), "sidebar");
  my_css_sheet_destroy(sheet);

  /* multi-name lists store raw. */
  memset(&error, 0, sizeof(error));
  sheet = my_css_parse_ex(NULL, multi, strlen(multi),
                          MY_CSS_PARSE_STRICT_AT_RULES, &error);
  ASSERT_NOT_NULL(sheet);
  ASSERT_STR_EQ(
      my_value_get_str(&my_css_decl(my_css_rule(sheet, 0u), 0u)->value),
      "sidebar main");
  my_css_sheet_destroy(sheet);

  /* an unknown container-type keyword drops just the declaration. */
  memset(&error, 0, sizeof(error));
  sheet = my_css_parse_ex(NULL, bad_type, strlen(bad_type),
                          MY_CSS_PARSE_STRICT_AT_RULES, &error);
  ASSERT_NOT_NULL(sheet);
  rule = my_css_rule(sheet, 0u);
  ASSERT_EQ(my_css_decl_count(rule), 1u);
  ASSERT_STR_EQ(my_css_decl(rule, 0u)->key, "container_name");
  my_css_sheet_destroy(sheet);

  /* `none` must stand alone in container-name. */
  memset(&error, 0, sizeof(error));
  sheet = my_css_parse_ex(NULL, bad_name, strlen(bad_name),
                          MY_CSS_PARSE_STRICT_AT_RULES, &error);
  ASSERT_NOT_NULL(sheet);
  rule = my_css_rule(sheet, 0u);
  ASSERT_EQ(my_css_decl_count(rule), 1u);
  ASSERT_STR_EQ(my_css_decl(rule, 0u)->key, "fg_color");
  my_css_sheet_destroy(sheet);

  memset(&error, 0, sizeof(error));
  sheet = my_css_parse_ex(NULL, none_name, strlen(none_name),
                          MY_CSS_PARSE_STRICT_AT_RULES, &error);
  ASSERT_NOT_NULL(sheet);
  ASSERT_STR_EQ(
      my_value_get_str(&my_css_decl(my_css_rule(sheet, 0u), 0u)->value),
      "none");
  my_css_sheet_destroy(sheet);

  /* cascade + lookup: class specificity wins, theme exposes the keys. */
  theme = my_theme_create(NULL);
  widget = my_widget_create(NULL, "panel");
  ASSERT_NOT_NULL(theme);
  ASSERT_NOT_NULL(widget);
  widget->widget_type = "panel";
  ASSERT_EQ(my_theme_load_css_ex(theme, cascade, MY_CSS_PARSE_STRICT_AT_RULES),
            MY_RET_OK);
  value = my_theme_get_for_widget(theme, widget, MY_STATE_NORMAL,
                                  "container_type");
  ASSERT_NOT_NULL(value);
  ASSERT_STR_EQ(my_value_get_str(value), "inline-size");
  ASSERT_EQ(my_widget_set_style_class(widget, "sized"), MY_RET_OK);
  value = my_theme_get_for_widget(theme, widget, MY_STATE_NORMAL,
                                  "container_type");
  ASSERT_NOT_NULL(value);
  ASSERT_STR_EQ(my_value_get_str(value), "size");
  my_widget_unref(widget);
  my_theme_destroy(theme);
}

TEST(css_container_queries_resolve_against_ancestor_at_match_time)
{
  /* R670: @container phase 2 core — with no injected context the query
   * defers to match time: the rule carries the condition (query text +
   * optional name), and the theme lookup evaluates it against the
   * nearest ancestor query container (container-type size/inline-size,
   * name-matching when named), using the ancestor's layout rect. */
  const char* deferred =
      "@container (min-width: 400px) { button { color: red; } }";
  const char* named =
      "@container sidebar (min-width: 400px) { button { color: red; } }";
  const char* themed =
      "panel { container-type: inline-size; }"
      "@container (min-width: 400px) { button { color: red; } }";
  const char* themed_named =
      "panel { container-type: inline-size; container-name: sidebar; }"
      "@container sidebar (min-width: 400px) { button { color: red; } }";
  const char* themed_nameless =
      "panel { container-type: inline-size; }"
      "@container sidebar (min-width: 400px) { button { color: red; } }";
  const char* themed_normal =
      "panel { container-type: normal; }"
      "@container (min-width: 400px) { button { color: red; } }";
  my_css_error_t error = {0};
  my_css_parse_options_t options = {0};
  my_css_sheet_t* sheet;
  my_theme_t* theme;
  my_widget_t* window;
  my_widget_t* panel;
  my_widget_t* button;
  const my_value_t* value;

  /* deferral: strict parse without an injected context stores the
   * condition on the rule (R663's strict reject was the phase-1
   * contract). */
  options.flags = MY_CSS_PARSE_STRICT_AT_RULES;
  sheet = my_css_parse_with_options(NULL, deferred, strlen(deferred),
                                    &options, &error);
  ASSERT_NOT_NULL(sheet);
  ASSERT_EQ(my_css_rule_count(sheet), 1u);
  ASSERT_STR_EQ(my_css_rule(sheet, 0u)->container_query,
                "(min-width: 400px)");
  ASSERT_STR_EQ(my_css_rule(sheet, 0u)->container_name, "");
  my_css_sheet_destroy(sheet);

  /* a named query stores the name. */
  memset(&error, 0, sizeof(error));
  sheet = my_css_parse_with_options(NULL, named, strlen(named), &options,
                                    &error);
  ASSERT_NOT_NULL(sheet);
  ASSERT_STR_EQ(my_css_rule(sheet, 0u)->container_name, "sidebar");
  my_css_sheet_destroy(sheet);

  /* the nearest ancestor query container gates the rule. */
  theme = my_theme_create(NULL);
  window = my_widget_create(NULL, "window");
  panel = my_widget_create(NULL, "panel");
  button = my_widget_create(NULL, "button");
  ASSERT_NOT_NULL(theme);
  ASSERT_NOT_NULL(window);
  ASSERT_NOT_NULL(panel);
  ASSERT_NOT_NULL(button);
  window->widget_type = "window";
  panel->widget_type = "panel";
  button->widget_type = "button";
  ASSERT_EQ(my_widget_add_child(window, panel), MY_RET_OK);
  ASSERT_EQ(my_widget_add_child(panel, button), MY_RET_OK);
  my_widget_unref(panel);
  my_widget_unref(button);
  panel->rect.w = 500;
  panel->rect.h = 600;
  ASSERT_EQ(my_theme_load_css_ex(theme, themed, MY_CSS_PARSE_STRICT_AT_RULES),
            MY_RET_OK);
  value = my_theme_get_for_widget(theme, button, MY_STATE_NORMAL, "fg_color");
  ASSERT_NOT_NULL(value);
  ASSERT_EQ(my_value_get_uint32(value), 0xFF0000FFu);
  /* below the threshold the conditional rule vanishes. */
  panel->rect.w = 300;
  ASSERT_TRUE(my_theme_get_for_widget(theme, button, MY_STATE_NORMAL,
                                      "fg_color") == NULL);
  my_widget_unref(window);
  my_theme_destroy(theme);

  /* named: the container must carry the name... */
  theme = my_theme_create(NULL);
  window = my_widget_create(NULL, "window");
  panel = my_widget_create(NULL, "panel");
  button = my_widget_create(NULL, "button");
  window->widget_type = "window";
  panel->widget_type = "panel";
  button->widget_type = "button";
  ASSERT_EQ(my_widget_add_child(window, panel), MY_RET_OK);
  ASSERT_EQ(my_widget_add_child(panel, button), MY_RET_OK);
  my_widget_unref(panel);
  my_widget_unref(button);
  panel->rect.w = 500;
  panel->rect.h = 600;
  ASSERT_EQ(my_theme_load_css_ex(theme, themed_named,
                                 MY_CSS_PARSE_STRICT_AT_RULES),
            MY_RET_OK);
  value = my_theme_get_for_widget(theme, button, MY_STATE_NORMAL, "fg_color");
  ASSERT_NOT_NULL(value);
  ASSERT_EQ(my_value_get_uint32(value), 0xFF0000FFu);
  my_widget_unref(window);
  my_theme_destroy(theme);

  /* ...a nameless container does not satisfy a named query. */
  theme = my_theme_create(NULL);
  window = my_widget_create(NULL, "window");
  panel = my_widget_create(NULL, "panel");
  button = my_widget_create(NULL, "button");
  window->widget_type = "window";
  panel->widget_type = "panel";
  button->widget_type = "button";
  ASSERT_EQ(my_widget_add_child(window, panel), MY_RET_OK);
  ASSERT_EQ(my_widget_add_child(panel, button), MY_RET_OK);
  my_widget_unref(panel);
  my_widget_unref(button);
  panel->rect.w = 500;
  panel->rect.h = 600;
  ASSERT_EQ(my_theme_load_css_ex(theme, themed_nameless,
                                 MY_CSS_PARSE_STRICT_AT_RULES),
            MY_RET_OK);
  ASSERT_TRUE(my_theme_get_for_widget(theme, button, MY_STATE_NORMAL,
                                      "fg_color") == NULL);
  my_widget_unref(window);
  my_theme_destroy(theme);

  /* container-type: normal is not a query container. */
  theme = my_theme_create(NULL);
  window = my_widget_create(NULL, "window");
  panel = my_widget_create(NULL, "panel");
  button = my_widget_create(NULL, "button");
  window->widget_type = "window";
  panel->widget_type = "panel";
  button->widget_type = "button";
  ASSERT_EQ(my_widget_add_child(window, panel), MY_RET_OK);
  ASSERT_EQ(my_widget_add_child(panel, button), MY_RET_OK);
  my_widget_unref(panel);
  my_widget_unref(button);
  panel->rect.w = 500;
  panel->rect.h = 600;
  ASSERT_EQ(my_theme_load_css_ex(theme, themed_normal,
                                 MY_CSS_PARSE_STRICT_AT_RULES),
            MY_RET_OK);
  ASSERT_TRUE(my_theme_get_for_widget(theme, button, MY_STATE_NORMAL,
                                      "fg_color") == NULL);
  my_widget_unref(window);
  my_theme_destroy(theme);
}

TEST(css_container_style_queries_resolve_at_match_time)
{
  /* R673: style() container queries — `@container [name]
   * style(--prop: value)` defers like a size query but evaluates
   * differently: container-type does not gate style queries (every
   * ancestor is a candidate; a name still filters), and the verdict is
   * a whitespace-normalized raw-text comparison of the custom property
   * value on the nearest qualifying ancestor (inherited through the
   * DOM chain, var()-resolved). Bounded slice: a single
   * `style(--prop: value)` condition — no bare form, no and/or/not
   * mixing, custom properties only. */
  const char* deferred =
      "@container style(--accent: red) { button { color: #010203; } }";
  const char* named =
      "@container card style(--accent: red) { button { color: #010203; } }";
  const char* bare =
      "@container style(--accent) { button { color: #010203; } }";
  const char* mixed =
      "@container style(--accent: red) and (min-width: 400px) {"
      " button { color: #010203; } }";
  const char* non_custom =
      "@container style(color: red) { button { color: #010203; } }";
  const char* hit =
      "panel { --accent: red; }"
      "@container style(--accent: red) { button { color: #010203; } }";
  const char* miss =
      "panel { --accent: blue; }"
      "@container style(--accent: red) { button { color: #010203; } }";
  const char* inherited =
      "window { --accent: red; }"
      "@container style(--accent: red) { button { color: #010203; } }";
  const char* var_hit =
      "panel { --brand: red; --accent: var(--brand); }"
      "@container style(--accent: red) { button { color: #010203; } }";
  const char* named_hit =
      "panel { container-name: card; --accent: red; }"
      "@container card style(--accent: red) { button { color: #010203; } }";
  const char* named_miss =
      "panel { --accent: red; }"
      "@container card style(--accent: red) { button { color: #010203; } }";
  const char* spacious =
      "panel { --accent: red; }"
      "@container style(--accent:   red  ) { button { color: #010203; } }";
  my_css_error_t error = {0};
  my_css_parse_options_t options = {0};
  my_css_sheet_t* sheet;
  my_theme_t* theme;
  my_widget_t* window;
  my_widget_t* panel;
  my_widget_t* button;
  const my_value_t* value;

  /* deferral: strict parse without an injected context stamps the
   * style query on the rule. */
  options.flags = MY_CSS_PARSE_STRICT_AT_RULES;
  sheet = my_css_parse_with_options(NULL, deferred, strlen(deferred),
                                    &options, &error);
  ASSERT_NOT_NULL(sheet);
  ASSERT_EQ(my_css_rule_count(sheet), 1u);
  ASSERT_STR_EQ(my_css_rule(sheet, 0u)->container_query,
                "style(--accent: red)");
  ASSERT_STR_EQ(my_css_rule(sheet, 0u)->container_name, "");
  my_css_sheet_destroy(sheet);

  /* a named style query stores the name. */
  memset(&error, 0, sizeof(error));
  sheet = my_css_parse_with_options(NULL, named, strlen(named), &options,
                                    &error);
  ASSERT_NOT_NULL(sheet);
  ASSERT_STR_EQ(my_css_rule(sheet, 0u)->container_query,
                "style(--accent: red)");
  ASSERT_STR_EQ(my_css_rule(sheet, 0u)->container_name, "card");
  my_css_sheet_destroy(sheet);

  /* bounded slice: the bare form, and/or mixing, and non-custom
   * properties all reject in strict mode. */
  memset(&error, 0, sizeof(error));
  ASSERT_TRUE(my_css_parse_with_options(NULL, bare, strlen(bare), &options,
                                        &error) == NULL);
  memset(&error, 0, sizeof(error));
  ASSERT_TRUE(my_css_parse_with_options(NULL, mixed, strlen(mixed), &options,
                                        &error) == NULL);
  memset(&error, 0, sizeof(error));
  ASSERT_TRUE(my_css_parse_with_options(NULL, non_custom, strlen(non_custom),
                                        &options, &error) == NULL);

  /* hit: the nearest ancestor carries the value — no container-type
   * is required for style queries. */
  theme = my_theme_create(NULL);
  window = my_widget_create(NULL, "window");
  panel = my_widget_create(NULL, "panel");
  button = my_widget_create(NULL, "button");
  window->widget_type = "window";
  panel->widget_type = "panel";
  button->widget_type = "button";
  ASSERT_EQ(my_widget_add_child(window, panel), MY_RET_OK);
  ASSERT_EQ(my_widget_add_child(panel, button), MY_RET_OK);
  my_widget_unref(panel);
  my_widget_unref(button);
  ASSERT_EQ(my_theme_load_css_ex(theme, hit, MY_CSS_PARSE_STRICT_AT_RULES),
            MY_RET_OK);
  value = my_theme_get_for_widget(theme, button, MY_STATE_NORMAL, "fg_color");
  ASSERT_NOT_NULL(value);
  ASSERT_EQ(my_value_get_uint32(value), 0x010203FFu);
  my_widget_unref(window);
  my_theme_destroy(theme);

  /* a different value does not match. */
  theme = my_theme_create(NULL);
  window = my_widget_create(NULL, "window");
  panel = my_widget_create(NULL, "panel");
  button = my_widget_create(NULL, "button");
  window->widget_type = "window";
  panel->widget_type = "panel";
  button->widget_type = "button";
  ASSERT_EQ(my_widget_add_child(window, panel), MY_RET_OK);
  ASSERT_EQ(my_widget_add_child(panel, button), MY_RET_OK);
  my_widget_unref(panel);
  my_widget_unref(button);
  ASSERT_EQ(my_theme_load_css_ex(theme, miss, MY_CSS_PARSE_STRICT_AT_RULES),
            MY_RET_OK);
  ASSERT_TRUE(my_theme_get_for_widget(theme, button, MY_STATE_NORMAL,
                                      "fg_color") == NULL);
  my_widget_unref(window);
  my_theme_destroy(theme);

  /* the custom property inherits: window sets it, the nearest ancestor
   * (panel) is the container and reads the inherited value. */
  theme = my_theme_create(NULL);
  window = my_widget_create(NULL, "window");
  panel = my_widget_create(NULL, "panel");
  button = my_widget_create(NULL, "button");
  window->widget_type = "window";
  panel->widget_type = "panel";
  button->widget_type = "button";
  ASSERT_EQ(my_widget_add_child(window, panel), MY_RET_OK);
  ASSERT_EQ(my_widget_add_child(panel, button), MY_RET_OK);
  my_widget_unref(panel);
  my_widget_unref(button);
  ASSERT_EQ(my_theme_load_css_ex(theme, inherited,
                                 MY_CSS_PARSE_STRICT_AT_RULES),
            MY_RET_OK);
  value = my_theme_get_for_widget(theme, button, MY_STATE_NORMAL, "fg_color");
  ASSERT_NOT_NULL(value);
  ASSERT_EQ(my_value_get_uint32(value), 0x010203FFu);
  my_widget_unref(window);
  my_theme_destroy(theme);

  /* a var()-laden stored value resolves before the comparison. */
  theme = my_theme_create(NULL);
  window = my_widget_create(NULL, "window");
  panel = my_widget_create(NULL, "panel");
  button = my_widget_create(NULL, "button");
  window->widget_type = "window";
  panel->widget_type = "panel";
  button->widget_type = "button";
  ASSERT_EQ(my_widget_add_child(window, panel), MY_RET_OK);
  ASSERT_EQ(my_widget_add_child(panel, button), MY_RET_OK);
  my_widget_unref(panel);
  my_widget_unref(button);
  ASSERT_EQ(my_theme_load_css_ex(theme, var_hit, MY_CSS_PARSE_STRICT_AT_RULES),
            MY_RET_OK);
  value = my_theme_get_for_widget(theme, button, MY_STATE_NORMAL, "fg_color");
  ASSERT_NOT_NULL(value);
  ASSERT_EQ(my_value_get_uint32(value), 0x010203FFu);
  my_widget_unref(window);
  my_theme_destroy(theme);

  /* named: the container must carry the name... */
  theme = my_theme_create(NULL);
  window = my_widget_create(NULL, "window");
  panel = my_widget_create(NULL, "panel");
  button = my_widget_create(NULL, "button");
  window->widget_type = "window";
  panel->widget_type = "panel";
  button->widget_type = "button";
  ASSERT_EQ(my_widget_add_child(window, panel), MY_RET_OK);
  ASSERT_EQ(my_widget_add_child(panel, button), MY_RET_OK);
  my_widget_unref(panel);
  my_widget_unref(button);
  ASSERT_EQ(my_theme_load_css_ex(theme, named_hit,
                                 MY_CSS_PARSE_STRICT_AT_RULES),
            MY_RET_OK);
  value = my_theme_get_for_widget(theme, button, MY_STATE_NORMAL, "fg_color");
  ASSERT_NOT_NULL(value);
  ASSERT_EQ(my_value_get_uint32(value), 0x010203FFu);
  my_widget_unref(window);
  my_theme_destroy(theme);

  /* ...a nameless ancestor does not satisfy a named style query. */
  theme = my_theme_create(NULL);
  window = my_widget_create(NULL, "window");
  panel = my_widget_create(NULL, "panel");
  button = my_widget_create(NULL, "button");
  window->widget_type = "window";
  panel->widget_type = "panel";
  button->widget_type = "button";
  ASSERT_EQ(my_widget_add_child(window, panel), MY_RET_OK);
  ASSERT_EQ(my_widget_add_child(panel, button), MY_RET_OK);
  my_widget_unref(panel);
  my_widget_unref(button);
  ASSERT_EQ(my_theme_load_css_ex(theme, named_miss,
                                 MY_CSS_PARSE_STRICT_AT_RULES),
            MY_RET_OK);
  ASSERT_TRUE(my_theme_get_for_widget(theme, button, MY_STATE_NORMAL,
                                      "fg_color") == NULL);
  my_widget_unref(window);
  my_theme_destroy(theme);

  /* whitespace around the compared value normalizes away. */
  theme = my_theme_create(NULL);
  window = my_widget_create(NULL, "window");
  panel = my_widget_create(NULL, "panel");
  button = my_widget_create(NULL, "button");
  window->widget_type = "window";
  panel->widget_type = "panel";
  button->widget_type = "button";
  ASSERT_EQ(my_widget_add_child(window, panel), MY_RET_OK);
  ASSERT_EQ(my_widget_add_child(panel, button), MY_RET_OK);
  my_widget_unref(panel);
  my_widget_unref(button);
  ASSERT_EQ(my_theme_load_css_ex(theme, spacious,
                                 MY_CSS_PARSE_STRICT_AT_RULES),
            MY_RET_OK);
  value = my_theme_get_for_widget(theme, button, MY_STATE_NORMAL, "fg_color");
  ASSERT_NOT_NULL(value);
  ASSERT_EQ(my_value_get_uint32(value), 0x010203FFu);
  my_widget_unref(window);
  my_theme_destroy(theme);
}

TEST(css_container_style_query_registered_computed_comparison)
{
  /* R677: a style() query against a REGISTERED custom property
   * compares computed values — both sides parse as one full value of
   * the registered primitive's type and compare typed (color bits,
   * numeric INT32/DOUBLE cross-type equality, quoted strings compare
   * by content). An unregistered property keeps the
   * whitespace-normalized raw-text comparison: red vs #f00 stay
   * distinct there. */
  const char* color_hit =
      "@property --accent { syntax: \"<color>\"; inherits: true;"
      " initial-value: blue; }"
      "panel { --accent: #f00; }"
      "@container style(--accent: red) { button { color: #010203; } }";
  const char* color_miss =
      "@property --accent { syntax: \"<color>\"; inherits: true;"
      " initial-value: blue; }"
      "panel { --accent: #f00; }"
      "@container style(--accent: blue) { button { color: #010203; } }";
  const char* number_cross_type =
      "@property --n { syntax: \"<number>\"; inherits: true;"
      " initial-value: 0; }"
      "panel { --n: 1.0; }"
      "@container style(--n: 1) { button { color: #010203; } }";
  const char* malformed_query =
      "@property --accent { syntax: \"<color>\"; inherits: true;"
      " initial-value: red; }"
      "panel { --accent: red; }"
      "@container style(--accent: bogus) { button { color: #010203; } }";
  const char* string_quote_forms =
      "@property --s { syntax: \"<string>\"; inherits: true;"
      " initial-value: \"none\"; }"
      "panel { --s: 'hi'; }"
      "@container style(--s: \"hi\") { button { color: #010203; } }";
  const char* unregistered_raw =
      "panel { --plain: red; }"
      "@container style(--plain: #f00) { button { color: #010203; } }";
  const char* initial_typed =
      "@property --accent { syntax: \"<color>\"; inherits: true;"
      " initial-value: #f00; }"
      "@container style(--accent: red) { button { color: #010203; } }";
  my_theme_t* theme;
  my_widget_t* window;
  my_widget_t* panel;
  my_widget_t* button;
  const my_value_t* value;

  /* registered <color>: stored #f00 and queried red are the same
   * computed color. */
  theme = my_theme_create(NULL);
  window = my_widget_create(NULL, "window");
  panel = my_widget_create(NULL, "panel");
  button = my_widget_create(NULL, "button");
  window->widget_type = "window";
  panel->widget_type = "panel";
  button->widget_type = "button";
  ASSERT_EQ(my_widget_add_child(window, panel), MY_RET_OK);
  ASSERT_EQ(my_widget_add_child(panel, button), MY_RET_OK);
  my_widget_unref(panel);
  my_widget_unref(button);
  ASSERT_EQ(my_theme_load_css_ex(theme, color_hit,
                                 MY_CSS_PARSE_STRICT_AT_RULES),
            MY_RET_OK);
  value = my_theme_get_for_widget(theme, button, MY_STATE_NORMAL, "fg_color");
  ASSERT_NOT_NULL(value);
  ASSERT_EQ(my_value_get_uint32(value), 0x010203FFu);
  my_widget_unref(window);
  my_theme_destroy(theme);

  /* a different computed color still misses. */
  theme = my_theme_create(NULL);
  window = my_widget_create(NULL, "window");
  panel = my_widget_create(NULL, "panel");
  button = my_widget_create(NULL, "button");
  window->widget_type = "window";
  panel->widget_type = "panel";
  button->widget_type = "button";
  ASSERT_EQ(my_widget_add_child(window, panel), MY_RET_OK);
  ASSERT_EQ(my_widget_add_child(panel, button), MY_RET_OK);
  my_widget_unref(panel);
  my_widget_unref(button);
  ASSERT_EQ(my_theme_load_css_ex(theme, color_miss,
                                 MY_CSS_PARSE_STRICT_AT_RULES),
            MY_RET_OK);
  ASSERT_TRUE(my_theme_get_for_widget(theme, button, MY_STATE_NORMAL,
                                      "fg_color") == NULL);
  my_widget_unref(window);
  my_theme_destroy(theme);

  /* registered <number>: 1.0 and 1 compare numerically across
   * INT32/DOUBLE. */
  theme = my_theme_create(NULL);
  window = my_widget_create(NULL, "window");
  panel = my_widget_create(NULL, "panel");
  button = my_widget_create(NULL, "button");
  window->widget_type = "window";
  panel->widget_type = "panel";
  button->widget_type = "button";
  ASSERT_EQ(my_widget_add_child(window, panel), MY_RET_OK);
  ASSERT_EQ(my_widget_add_child(panel, button), MY_RET_OK);
  my_widget_unref(panel);
  my_widget_unref(button);
  ASSERT_EQ(my_theme_load_css_ex(theme, number_cross_type,
                                 MY_CSS_PARSE_STRICT_AT_RULES),
            MY_RET_OK);
  value = my_theme_get_for_widget(theme, button, MY_STATE_NORMAL, "fg_color");
  ASSERT_NOT_NULL(value);
  ASSERT_EQ(my_value_get_uint32(value), 0x010203FFu);
  my_widget_unref(window);
  my_theme_destroy(theme);

  /* a value that does not parse as the registered type never matches. */
  theme = my_theme_create(NULL);
  window = my_widget_create(NULL, "window");
  panel = my_widget_create(NULL, "panel");
  button = my_widget_create(NULL, "button");
  window->widget_type = "window";
  panel->widget_type = "panel";
  button->widget_type = "button";
  ASSERT_EQ(my_widget_add_child(window, panel), MY_RET_OK);
  ASSERT_EQ(my_widget_add_child(panel, button), MY_RET_OK);
  my_widget_unref(panel);
  my_widget_unref(button);
  ASSERT_EQ(my_theme_load_css_ex(theme, malformed_query,
                                 MY_CSS_PARSE_STRICT_AT_RULES),
            MY_RET_OK);
  ASSERT_TRUE(my_theme_get_for_widget(theme, button, MY_STATE_NORMAL,
                                      "fg_color") == NULL);
  my_widget_unref(window);
  my_theme_destroy(theme);

  /* registered <string>: single- and double-quoted forms hold the
   * same computed string. */
  theme = my_theme_create(NULL);
  window = my_widget_create(NULL, "window");
  panel = my_widget_create(NULL, "panel");
  button = my_widget_create(NULL, "button");
  window->widget_type = "window";
  panel->widget_type = "panel";
  button->widget_type = "button";
  ASSERT_EQ(my_widget_add_child(window, panel), MY_RET_OK);
  ASSERT_EQ(my_widget_add_child(panel, button), MY_RET_OK);
  my_widget_unref(panel);
  my_widget_unref(button);
  ASSERT_EQ(my_theme_load_css_ex(theme, string_quote_forms,
                                 MY_CSS_PARSE_STRICT_AT_RULES),
            MY_RET_OK);
  value = my_theme_get_for_widget(theme, button, MY_STATE_NORMAL, "fg_color");
  ASSERT_NOT_NULL(value);
  ASSERT_EQ(my_value_get_uint32(value), 0x010203FFu);
  my_widget_unref(window);
  my_theme_destroy(theme);

  /* unregistered: raw-text comparison — red vs #f00 stay distinct. */
  theme = my_theme_create(NULL);
  window = my_widget_create(NULL, "window");
  panel = my_widget_create(NULL, "panel");
  button = my_widget_create(NULL, "button");
  window->widget_type = "window";
  panel->widget_type = "panel";
  button->widget_type = "button";
  ASSERT_EQ(my_widget_add_child(window, panel), MY_RET_OK);
  ASSERT_EQ(my_widget_add_child(panel, button), MY_RET_OK);
  my_widget_unref(panel);
  my_widget_unref(button);
  ASSERT_EQ(my_theme_load_css_ex(theme, unregistered_raw,
                                 MY_CSS_PARSE_STRICT_AT_RULES),
            MY_RET_OK);
  ASSERT_TRUE(my_theme_get_for_widget(theme, button, MY_STATE_NORMAL,
                                      "fg_color") == NULL);
  my_widget_unref(window);
  my_theme_destroy(theme);

  /* an unset registered property falls to its initial value, which
   * participates in the typed comparison (#f00 == red). */
  theme = my_theme_create(NULL);
  window = my_widget_create(NULL, "window");
  panel = my_widget_create(NULL, "panel");
  button = my_widget_create(NULL, "button");
  window->widget_type = "window";
  panel->widget_type = "panel";
  button->widget_type = "button";
  ASSERT_EQ(my_widget_add_child(window, panel), MY_RET_OK);
  ASSERT_EQ(my_widget_add_child(panel, button), MY_RET_OK);
  my_widget_unref(panel);
  my_widget_unref(button);
  ASSERT_EQ(my_theme_load_css_ex(theme, initial_typed,
                                 MY_CSS_PARSE_STRICT_AT_RULES),
            MY_RET_OK);
  value = my_theme_get_for_widget(theme, button, MY_STATE_NORMAL, "fg_color");
  ASSERT_NOT_NULL(value);
  ASSERT_EQ(my_value_get_uint32(value), 0x010203FFu);
  my_widget_unref(window);
  my_theme_destroy(theme);
}

TEST(css_property_syntax_multi_choice_alternatives)
{
  /* R678: `a | b` syntax combinations — the value matches when any
   * trimmed alternative accepts it: ident alternatives compare
   * byte-exact after trimming, primitive alternatives reuse the
   * R672/R676 gates. A combination holding an unrecognized component
   * (unknown primitive, empty alternative) stays unenforced — the
   * R672 unknown-string deferral. */
  const char* ident_valid =
      "@property --size { syntax: \"small | large | medium\";"
      " inherits: false; initial-value: small; } button { color: blue; }";
  const char* ident_bad_initial =
      "@property --size { syntax: \"small | large | medium\";"
      " inherits: false; initial-value: huge; } button { color: blue; }";
  const char* ident_case =
      "@property --size { syntax: \"small | large | medium\";"
      " inherits: false; initial-value: Large; } button { color: blue; }";
  const char* primitive_valid =
      "@property --x { syntax: \"<length> | <percentage>\";"
      " inherits: false; initial-value: 12.5%; } button { color: blue; }";
  const char* primitive_bad_initial =
      "@property --x { syntax: \"<length> | <percentage>\";"
      " inherits: false; initial-value: abc; } button { color: blue; }";
  const char* tight_spacing =
      "@property --size { syntax: \"small|large\"; inherits: false;"
      " initial-value: large; } button { color: blue; }";
  const char* unknown_alt =
      "@property --t { syntax: \"<transform-function> | small\";"
      " inherits: false; initial-value: junk; } button { color: blue; }";
  const char* empty_alt =
      "@property --size { syntax: \"small | | large\"; inherits: false;"
      " initial-value: huge; } button { color: blue; }";
  const char* ident_pass =
      "@property --size { syntax: \"small | large\"; inherits: true; }"
      "button { --size: large; color: var(--size, red); }";
  const char* ident_fail =
      "@property --size { syntax: \"small | large\"; inherits: true; }"
      "button { --size: big; color: var(--size, red); }";
  const char* primitive_pass =
      "@property --x { syntax: \"<length> | <percentage>\";"
      " inherits: true; }"
      "button { --x: 50%; color: var(--x, red); }";
  const char* primitive_fail =
      "@property --x { syntax: \"<length> | <percentage>\";"
      " inherits: true; }"
      "button { --x: abc; color: var(--x, red); }";
  const char* unknown_alt_raw =
      "@property --t { syntax: \"<transform-function> | small\";"
      " inherits: true; }"
      "button { --t: junk2; color: var(--t, red); }";
  my_css_error_t error = {0};
  my_css_sheet_t* sheet;
  my_theme_t* theme;
  my_widget_t* widget;
  my_value_t out;

  my_value_init(&out, NULL);

  /* a conforming ident initial registers. */
  sheet = my_css_parse_ex(NULL, ident_valid, strlen(ident_valid),
                          MY_CSS_PARSE_STRICT_AT_RULES, &error);
  ASSERT_NOT_NULL(sheet);
  ASSERT_EQ(my_css_property_def_count(sheet), 1u);
  my_css_sheet_destroy(sheet);

  /* an initial matching no alternative drops the whole @property. */
  memset(&error, 0, sizeof(error));
  sheet = my_css_parse_ex(NULL, ident_bad_initial,
                          strlen(ident_bad_initial),
                          MY_CSS_PARSE_STRICT_AT_RULES, &error);
  ASSERT_NOT_NULL(sheet);
  ASSERT_EQ(my_css_property_def_count(sheet), 0u);
  my_css_sheet_destroy(sheet);

  /* idents compare byte-exact: Large != large. */
  memset(&error, 0, sizeof(error));
  sheet = my_css_parse_ex(NULL, ident_case, strlen(ident_case),
                          MY_CSS_PARSE_STRICT_AT_RULES, &error);
  ASSERT_NOT_NULL(sheet);
  ASSERT_EQ(my_css_property_def_count(sheet), 0u);
  my_css_sheet_destroy(sheet);

  /* primitive alternatives accept a conforming initial... */
  memset(&error, 0, sizeof(error));
  sheet = my_css_parse_ex(NULL, primitive_valid, strlen(primitive_valid),
                          MY_CSS_PARSE_STRICT_AT_RULES, &error);
  ASSERT_NOT_NULL(sheet);
  ASSERT_EQ(my_css_property_def_count(sheet), 1u);
  my_css_sheet_destroy(sheet);

  /* ...and drop a non-matching one. */
  memset(&error, 0, sizeof(error));
  sheet = my_css_parse_ex(NULL, primitive_bad_initial,
                          strlen(primitive_bad_initial),
                          MY_CSS_PARSE_STRICT_AT_RULES, &error);
  ASSERT_NOT_NULL(sheet);
  ASSERT_EQ(my_css_property_def_count(sheet), 0u);
  my_css_sheet_destroy(sheet);

  /* whitespace around '|' is not required. */
  memset(&error, 0, sizeof(error));
  sheet = my_css_parse_ex(NULL, tight_spacing, strlen(tight_spacing),
                          MY_CSS_PARSE_STRICT_AT_RULES, &error);
  ASSERT_NOT_NULL(sheet);
  ASSERT_EQ(my_css_property_def_count(sheet), 1u);
  my_css_sheet_destroy(sheet);

  /* an unrecognized alternative leaves the combination unenforced. */
  memset(&error, 0, sizeof(error));
  sheet = my_css_parse_ex(NULL, unknown_alt, strlen(unknown_alt),
                          MY_CSS_PARSE_STRICT_AT_RULES, &error);
  ASSERT_NOT_NULL(sheet);
  ASSERT_EQ(my_css_property_def_count(sheet), 1u);
  my_css_sheet_destroy(sheet);

  /* an empty alternative is malformed and likewise unenforced. */
  memset(&error, 0, sizeof(error));
  sheet = my_css_parse_ex(NULL, empty_alt, strlen(empty_alt),
                          MY_CSS_PARSE_STRICT_AT_RULES, &error);
  ASSERT_NOT_NULL(sheet);
  ASSERT_EQ(my_css_property_def_count(sheet), 1u);
  my_css_sheet_destroy(sheet);

  /* computed-value time: a matching ident passes the gate raw — the
   * substituted STR "large" comes through verbatim. */
  theme = my_theme_create(NULL);
  widget = my_widget_create(NULL, "button");
  widget->widget_type = "button";
  ASSERT_EQ(my_theme_load_css_ex(theme, ident_pass,
                                 MY_CSS_PARSE_STRICT_AT_RULES),
            MY_RET_OK);
  ASSERT_TRUE(my_theme_get_for_widget_var(theme, widget, MY_STATE_NORMAL,
                                          "fg_color", &out));
  ASSERT_EQ(my_value_type(&out), MY_VALUE_STR);
  ASSERT_STR_EQ(my_value_get_str(&out), "large");
  my_widget_unref(widget);
  my_theme_destroy(theme);

  /* a value matching no alternative is guaranteed-invalid -> the
   * var() fallback applies. */
  theme = my_theme_create(NULL);
  widget = my_widget_create(NULL, "button");
  widget->widget_type = "button";
  ASSERT_EQ(my_theme_load_css_ex(theme, ident_fail,
                                 MY_CSS_PARSE_STRICT_AT_RULES),
            MY_RET_OK);
  ASSERT_TRUE(my_theme_get_for_widget_var(theme, widget, MY_STATE_NORMAL,
                                          "fg_color", &out));
  ASSERT_EQ(my_value_get_uint32(&out), 0xFF0000FFu);
  my_widget_unref(widget);
  my_theme_destroy(theme);

  /* primitives gate the same way at computed-value time. */
  theme = my_theme_create(NULL);
  widget = my_widget_create(NULL, "button");
  widget->widget_type = "button";
  ASSERT_EQ(my_theme_load_css_ex(theme, primitive_pass,
                                 MY_CSS_PARSE_STRICT_AT_RULES),
            MY_RET_OK);
  ASSERT_TRUE(!my_theme_get_for_widget_var(theme, widget, MY_STATE_NORMAL,
                                           "fg_color", &out));
  my_widget_unref(widget);
  my_theme_destroy(theme);

  theme = my_theme_create(NULL);
  widget = my_widget_create(NULL, "button");
  widget->widget_type = "button";
  ASSERT_EQ(my_theme_load_css_ex(theme, primitive_fail,
                                 MY_CSS_PARSE_STRICT_AT_RULES),
            MY_RET_OK);
  ASSERT_TRUE(my_theme_get_for_widget_var(theme, widget, MY_STATE_NORMAL,
                                          "fg_color", &out));
  ASSERT_EQ(my_value_get_uint32(&out), 0xFF0000FFu);
  my_widget_unref(widget);
  my_theme_destroy(theme);

  /* an unenforced combination substitutes raw values through. */
  theme = my_theme_create(NULL);
  widget = my_widget_create(NULL, "button");
  widget->widget_type = "button";
  ASSERT_EQ(my_theme_load_css_ex(theme, unknown_alt_raw,
                                 MY_CSS_PARSE_STRICT_AT_RULES),
            MY_RET_OK);
  ASSERT_TRUE(my_theme_get_for_widget_var(theme, widget, MY_STATE_NORMAL,
                                          "fg_color", &out));
  ASSERT_EQ(my_value_type(&out), MY_VALUE_STR);
  ASSERT_STR_EQ(my_value_get_str(&out), "junk2");
  my_widget_unref(widget);
  my_theme_destroy(theme);

  my_value_reset(&out);
}

TEST(css_container_nested_queries_and_at_match_time)
{
  /* R675: nested deferred @container is a conjunction — the rule must
   * carry BOTH conditions (inner pair first, outer pair second) and the
   * cascade gates on both. R670's "inner stamps first and wins" silently
   * dropped the outer condition. Bounded slice: depth ≥ 3 keeps the
   * innermost two conditions (documented approximation). */
  const char* nested =
      "panel { container-type: inline-size; }"
      "@container (min-width: 400px) {"
      " @container (min-height: 500px) {"
      "  button { color: #010203; } } }";
  const char* nested_named =
      "panel { container-type: inline-size; container-name: card; }"
      "@container card (min-width: 400px) {"
      " @container (min-height: 500px) {"
      "  button { color: #010203; } } }";
  const char* nested_named_miss =
      "panel { container-type: inline-size; }"
      "@container card (min-width: 400px) {"
      " @container (min-height: 500px) {"
      "  button { color: #010203; } } }";
  const char* deep =
      "panel { container-type: inline-size; }"
      "@container (min-width: 900px) {"      /* dropped (outermost) */
      " @container (min-width: 400px) {"     /* kept */
      "  @container (min-height: 500px) {"   /* kept (innermost) */
      "   button { color: #010203; } } } }";
  my_css_error_t error = {0};
  my_css_parse_options_t options = {0};
  my_css_sheet_t* sheet;
  my_theme_t* theme;
  my_widget_t* window;
  my_widget_t* panel;
  my_widget_t* button;
  const my_value_t* value;

  /* stamping: the inner condition lands in pair1, the outer in pair2. */
  options.flags = MY_CSS_PARSE_STRICT_AT_RULES;
  sheet = my_css_parse_with_options(NULL, nested + 38, strlen(nested + 38),
                                    &options, &error);
  ASSERT_NOT_NULL(sheet);
  ASSERT_EQ(my_css_rule_count(sheet), 1u);
  ASSERT_STR_EQ(my_css_rule(sheet, 0u)->container_query,
                "(min-height: 500px)");
  ASSERT_STR_EQ(my_css_rule(sheet, 0u)->container_name, "");
  ASSERT_STR_EQ(my_css_rule(sheet, 0u)->container_query2,
                "(min-width: 400px)");
  ASSERT_STR_EQ(my_css_rule(sheet, 0u)->container_name2, "");
  my_css_sheet_destroy(sheet);

  /* both conditions true: the rule applies. */
  theme = my_theme_create(NULL);
  window = my_widget_create(NULL, "window");
  panel = my_widget_create(NULL, "panel");
  button = my_widget_create(NULL, "button");
  window->widget_type = "window";
  panel->widget_type = "panel";
  button->widget_type = "button";
  ASSERT_EQ(my_widget_add_child(window, panel), MY_RET_OK);
  ASSERT_EQ(my_widget_add_child(panel, button), MY_RET_OK);
  my_widget_unref(panel);
  my_widget_unref(button);
  panel->rect.w = 500;
  panel->rect.h = 600;
  ASSERT_EQ(my_theme_load_css_ex(theme, nested, MY_CSS_PARSE_STRICT_AT_RULES),
            MY_RET_OK);
  value = my_theme_get_for_widget(theme, button, MY_STATE_NORMAL, "fg_color");
  ASSERT_NOT_NULL(value);
  ASSERT_EQ(my_value_get_uint32(value), 0x010203FFu);

  /* outer false (width 300) + inner true: the conjunction must hold the
   * rule back — R670's inner-only stamp let it through. */
  panel->rect.w = 300;
  ASSERT_TRUE(my_theme_get_for_widget(theme, button, MY_STATE_NORMAL,
                                      "fg_color") == NULL);
  /* inner false (height 400) + outer true: held back too. */
  panel->rect.w = 500;
  panel->rect.h = 400;
  ASSERT_TRUE(my_theme_get_for_widget(theme, button, MY_STATE_NORMAL,
                                      "fg_color") == NULL);
  my_widget_unref(window);
  my_theme_destroy(theme);

  /* named outer + unnamed inner: the name binds to its own condition. */
  theme = my_theme_create(NULL);
  window = my_widget_create(NULL, "window");
  panel = my_widget_create(NULL, "panel");
  button = my_widget_create(NULL, "button");
  window->widget_type = "window";
  panel->widget_type = "panel";
  button->widget_type = "button";
  ASSERT_EQ(my_widget_add_child(window, panel), MY_RET_OK);
  ASSERT_EQ(my_widget_add_child(panel, button), MY_RET_OK);
  my_widget_unref(panel);
  my_widget_unref(button);
  panel->rect.w = 500;
  panel->rect.h = 600;
  ASSERT_EQ(my_theme_load_css_ex(theme, nested_named,
                                 MY_CSS_PARSE_STRICT_AT_RULES),
            MY_RET_OK);
  value = my_theme_get_for_widget(theme, button, MY_STATE_NORMAL, "fg_color");
  ASSERT_NOT_NULL(value);
  ASSERT_EQ(my_value_get_uint32(value), 0x010203FFu);
  my_widget_unref(window);
  my_theme_destroy(theme);

  /* ...a nameless container does not satisfy the named outer leg. */
  theme = my_theme_create(NULL);
  window = my_widget_create(NULL, "window");
  panel = my_widget_create(NULL, "panel");
  button = my_widget_create(NULL, "button");
  window->widget_type = "window";
  panel->widget_type = "panel";
  button->widget_type = "button";
  ASSERT_EQ(my_widget_add_child(window, panel), MY_RET_OK);
  ASSERT_EQ(my_widget_add_child(panel, button), MY_RET_OK);
  my_widget_unref(panel);
  my_widget_unref(button);
  panel->rect.w = 500;
  panel->rect.h = 600;
  ASSERT_EQ(my_theme_load_css_ex(theme, nested_named_miss,
                                 MY_CSS_PARSE_STRICT_AT_RULES),
            MY_RET_OK);
  ASSERT_TRUE(my_theme_get_for_widget(theme, button, MY_STATE_NORMAL,
                                      "fg_color") == NULL);
  my_widget_unref(window);
  my_theme_destroy(theme);

  /* depth 3: the innermost two conditions are kept, the outermost is
   * dropped — panel 500x600 fails min-width 900 but the documented
   * approximation still applies the rule. */
  theme = my_theme_create(NULL);
  window = my_widget_create(NULL, "window");
  panel = my_widget_create(NULL, "panel");
  button = my_widget_create(NULL, "button");
  window->widget_type = "window";
  panel->widget_type = "panel";
  button->widget_type = "button";
  ASSERT_EQ(my_widget_add_child(window, panel), MY_RET_OK);
  ASSERT_EQ(my_widget_add_child(panel, button), MY_RET_OK);
  my_widget_unref(panel);
  my_widget_unref(button);
  panel->rect.w = 500;
  panel->rect.h = 600;
  ASSERT_EQ(my_theme_load_css_ex(theme, deep, MY_CSS_PARSE_STRICT_AT_RULES),
            MY_RET_OK);
  value = my_theme_get_for_widget(theme, button, MY_STATE_NORMAL, "fg_color");
  ASSERT_NOT_NULL(value);
  ASSERT_EQ(my_value_get_uint32(value), 0x010203FFu);
  my_widget_unref(window);
  my_theme_destroy(theme);
}

TEST(css_property_rule_registers_custom_properties)
{
  /* R671: @property slice 1 — the rule parses into the theme registry
   * (syntax text stored, inherits flag, optional initial-value raw
   * text) and the var() resolver honors it: inherits:false stops the
   * DOM inheritance walk, initial-value fills an unset registered
   * property. Syntax enforcement itself is a later slice. */
  const char* defd =
      "@property --brand { syntax: \"<color>\"; inherits: false;"
      " initial-value: #036; }";
  const char* dropped =
      "@property --x { initial-value: red; } button { color: blue; }";
  const char* no_inherits =
      "@property --x { syntax: \"*\"; inherits: false; }"
      "window { --x: red; } button { color: var(--x, blue); }";
  const char* yes_inherits =
      "@property --x { syntax: \"*\"; inherits: true; }"
      "window { --x: red; } button { color: var(--x, blue); }";
  const char* initial =
      "@property --brand { syntax: \"<color>\"; inherits: true;"
      " initial-value: #036; }"
      "button { color: var(--brand); }";
  my_css_error_t error = {0};
  my_css_sheet_t* sheet;
  const my_theme_property_def_t* def;
  my_theme_t* theme;
  my_widget_t* window;
  my_widget_t* button;
  my_value_t out;

  my_value_init(&out, NULL);

  /* parse + register: descriptors land on the sheet. */
  sheet = my_css_parse_ex(NULL, defd, strlen(defd),
                          MY_CSS_PARSE_STRICT_AT_RULES, &error);
  ASSERT_NOT_NULL(sheet);
  ASSERT_EQ(my_css_property_def_count(sheet), 1u);
  def = my_css_property_def(sheet, 0u);
  ASSERT_NOT_NULL(def);
  ASSERT_STR_EQ(def->name, "--brand");
  ASSERT_STR_EQ(def->syntax, "<color>");
  ASSERT_TRUE(!def->inherits);
  ASSERT_TRUE(def->has_initial);
  ASSERT_STR_EQ(def->initial, "#036");
  my_css_sheet_destroy(sheet);

  /* missing required descriptors (syntax/inherits) drops just the rule. */
  memset(&error, 0, sizeof(error));
  sheet = my_css_parse_ex(NULL, dropped, strlen(dropped),
                          MY_CSS_PARSE_STRICT_AT_RULES, &error);
  ASSERT_NOT_NULL(sheet);
  ASSERT_EQ(my_css_property_def_count(sheet), 0u);
  ASSERT_EQ(my_css_rule_count(sheet), 1u);
  my_css_sheet_destroy(sheet);

  /* inherits:false — the custom property does not cross the DOM edge. */
  theme = my_theme_create(NULL);
  window = my_widget_create(NULL, "window");
  button = my_widget_create(NULL, "button");
  ASSERT_NOT_NULL(theme);
  ASSERT_NOT_NULL(window);
  ASSERT_NOT_NULL(button);
  window->widget_type = "window";
  button->widget_type = "button";
  ASSERT_EQ(my_widget_add_child(window, button), MY_RET_OK);
  my_widget_unref(button);
  ASSERT_EQ(my_theme_load_css_ex(theme, no_inherits,
                                 MY_CSS_PARSE_STRICT_AT_RULES),
            MY_RET_OK);
  ASSERT_TRUE(my_theme_get_for_widget_var(theme, button, MY_STATE_NORMAL,
                                          "fg_color", &out));
  ASSERT_EQ(my_value_get_uint32(&out), 0x0000FFFFu);
  my_widget_unref(window);
  my_theme_destroy(theme);

  /* inherits:true — the walk proceeds (unregistered behavior). */
  theme = my_theme_create(NULL);
  window = my_widget_create(NULL, "window");
  button = my_widget_create(NULL, "button");
  window->widget_type = "window";
  button->widget_type = "button";
  ASSERT_EQ(my_widget_add_child(window, button), MY_RET_OK);
  my_widget_unref(button);
  ASSERT_EQ(my_theme_load_css_ex(theme, yes_inherits,
                                 MY_CSS_PARSE_STRICT_AT_RULES),
            MY_RET_OK);
  ASSERT_TRUE(my_theme_get_for_widget_var(theme, button, MY_STATE_NORMAL,
                                          "fg_color", &out));
  ASSERT_EQ(my_value_get_uint32(&out), 0xFF0000FFu);
  my_widget_unref(window);
  my_theme_destroy(theme);

  /* initial-value fills an unset registered property. */
  theme = my_theme_create(NULL);
  button = my_widget_create(NULL, "button");
  button->widget_type = "button";
  ASSERT_EQ(my_theme_load_css_ex(theme, initial,
                                 MY_CSS_PARSE_STRICT_AT_RULES),
            MY_RET_OK);
  ASSERT_TRUE(my_theme_get_for_widget_var(theme, button, MY_STATE_NORMAL,
                                          "fg_color", &out));
  ASSERT_EQ(my_value_get_uint32(&out), 0x003366FFu);
  my_widget_unref(button);
  my_theme_destroy(theme);

  my_value_reset(&out);
}

TEST(css_property_syntax_is_enforced_at_computed_value_time)
{
  /* R672: @property slice 2 — a registered property's value must parse
   * as its syntax at computed-value time (bounded primitives:
   * <color>/<length>/<number>/<integer>/<string> and *). An invalid
   * value makes the property guaranteed-invalid: the initial value or
   * the var() fallback applies. An invalid initial (when checkable)
   * invalidates the @property rule itself. */
  const char* good_color =
      "@property --c { syntax: \"<color>\"; inherits: true; }"
      "button { --c: #036; color: var(--c, red); }";
  const char* bad_color_initial =
      "@property --c { syntax: \"<color>\"; inherits: true;"
      " initial-value: blue; }"
      "button { --c: 12px; color: var(--c, red); }";
  const char* bad_color_unset =
      "@property --c { syntax: \"<color>\"; inherits: true; }"
      "button { --c: 12px; color: var(--c, red); }";
  const char* good_length =
      "@property --w { syntax: \"<length>\"; inherits: true; }"
      "button { --w: 12px; border-width: var(--w); }";
  const char* bad_length =
      "@property --w { syntax: \"<length>\"; inherits: true; }"
      "button { --w: red; border-width: var(--w); }";
  const char* bad_initial =
      "@property --w { syntax: \"<length>\"; inherits: true;"
      " initial-value: red; } button { color: blue; }";
  const char* var_initial =
      "@property --c { syntax: \"<color>\"; inherits: true;"
      " initial-value: var(--other); } button { color: blue; }";
  my_css_error_t error = {0};
  my_css_sheet_t* sheet;
  my_theme_t* theme;
  my_widget_t* widget;
  my_value_t out;

  my_value_init(&out, NULL);

  /* a conforming value passes. */
  theme = my_theme_create(NULL);
  widget = my_widget_create(NULL, "button");
  ASSERT_NOT_NULL(theme);
  ASSERT_NOT_NULL(widget);
  widget->widget_type = "button";
  ASSERT_EQ(my_theme_load_css_ex(theme, good_color,
                                 MY_CSS_PARSE_STRICT_AT_RULES),
            MY_RET_OK);
  ASSERT_TRUE(my_theme_get_for_widget_var(theme, widget, MY_STATE_NORMAL,
                                          "fg_color", &out));
  ASSERT_EQ(my_value_get_uint32(&out), 0x003366FFu);
  my_widget_unref(widget);
  my_theme_destroy(theme);

  /* an invalid value falls to the registered initial value. */
  theme = my_theme_create(NULL);
  widget = my_widget_create(NULL, "button");
  widget->widget_type = "button";
  ASSERT_EQ(my_theme_load_css_ex(theme, bad_color_initial,
                                 MY_CSS_PARSE_STRICT_AT_RULES),
            MY_RET_OK);
  ASSERT_TRUE(my_theme_get_for_widget_var(theme, widget, MY_STATE_NORMAL,
                                          "fg_color", &out));
  ASSERT_EQ(my_value_get_uint32(&out), 0x0000FFFFu);
  my_widget_unref(widget);
  my_theme_destroy(theme);

  /* ... and without an initial, to the var() fallback. */
  theme = my_theme_create(NULL);
  widget = my_widget_create(NULL, "button");
  widget->widget_type = "button";
  ASSERT_EQ(my_theme_load_css_ex(theme, bad_color_unset,
                                 MY_CSS_PARSE_STRICT_AT_RULES),
            MY_RET_OK);
  ASSERT_TRUE(my_theme_get_for_widget_var(theme, widget, MY_STATE_NORMAL,
                                          "fg_color", &out));
  ASSERT_EQ(my_value_get_uint32(&out), 0xFF0000FFu);
  my_widget_unref(widget);
  my_theme_destroy(theme);

  /* <length> takes engine numbers; a color word is guaranteed-invalid
   * (no initial, no fallback -> unset). */
  theme = my_theme_create(NULL);
  widget = my_widget_create(NULL, "button");
  widget->widget_type = "button";
  ASSERT_EQ(my_theme_load_css_ex(theme, good_length,
                                 MY_CSS_PARSE_STRICT_AT_RULES),
            MY_RET_OK);
  ASSERT_TRUE(my_theme_get_for_widget_var(theme, widget, MY_STATE_NORMAL,
                                          "border_width", &out));
  ASSERT_EQ(my_value_get_int32(&out), 12);
  my_widget_unref(widget);
  my_theme_destroy(theme);

  theme = my_theme_create(NULL);
  widget = my_widget_create(NULL, "button");
  widget->widget_type = "button";
  ASSERT_EQ(my_theme_load_css_ex(theme, bad_length,
                                 MY_CSS_PARSE_STRICT_AT_RULES),
            MY_RET_OK);
  ASSERT_TRUE(!my_theme_get_for_widget_var(theme, widget, MY_STATE_NORMAL,
                                           "border_width", &out));
  my_widget_unref(widget);
  my_theme_destroy(theme);

  /* an invalid initial invalidates the @property rule itself. */
  sheet = my_css_parse_ex(NULL, bad_initial, strlen(bad_initial),
                          MY_CSS_PARSE_STRICT_AT_RULES, &error);
  ASSERT_NOT_NULL(sheet);
  ASSERT_EQ(my_css_property_def_count(sheet), 0u);
  ASSERT_EQ(my_css_rule_count(sheet), 1u);
  my_css_sheet_destroy(sheet);

  /* ... unless the initial mentions var() — validation defers to
   * computed-value time. */
  memset(&error, 0, sizeof(error));
  sheet = my_css_parse_ex(NULL, var_initial, strlen(var_initial),
                          MY_CSS_PARSE_STRICT_AT_RULES, &error);
  ASSERT_NOT_NULL(sheet);
  ASSERT_EQ(my_css_property_def_count(sheet), 1u);
  my_css_sheet_destroy(sheet);

  my_value_reset(&out);
}

TEST(css_property_syntax_percentage_primitive)
{
  /* R676: @property syntax primitive <percentage> — a number immediately
   * followed by '%' (no intervening whitespace, no other unit). The
   * initial is checked at registration; the cascaded value is gated at
   * computed-value time (guaranteed-invalid falls to the initial, then
   * the var() fallback). */
  const char* good_initial =
      "@property --p { syntax: \"<percentage>\"; inherits: false;"
      " initial-value: 50%; } button { color: blue; }";
  const char* decimal_initial =
      "@property --p { syntax: \"<percentage>\"; inherits: false;"
      " initial-value: 12.5%; } button { color: blue; }";
  const char* bare_number_initial =
      "@property --p { syntax: \"<percentage>\"; inherits: false;"
      " initial-value: 50; } button { color: blue; }";
  const char* px_initial =
      "@property --p { syntax: \"<percentage>\"; inherits: false;"
      " initial-value: 50px; } button { color: blue; }";
  const char* spaced_initial =
      "@property --p { syntax: \"<percentage>\"; inherits: false;"
      " initial-value: 50 %; } button { color: blue; }";
  const char* word_initial =
      "@property --p { syntax: \"<percentage>\"; inherits: false;"
      " initial-value: abc; } button { color: blue; }";
  const char* good_value =
      "@property --p { syntax: \"<percentage>\"; inherits: true; }"
      "button { --p: 50%; color: var(--p, red); }";
  const char* bad_value =
      "@property --p { syntax: \"<percentage>\"; inherits: true; }"
      "button { --p: abc; color: var(--p, red); }";
  const char* bare_number_value =
      "@property --p { syntax: \"<percentage>\"; inherits: true; }"
      "button { --p: 50; color: var(--p, red); }";
  my_css_error_t error = {0};
  my_css_sheet_t* sheet;
  my_theme_t* theme;
  my_widget_t* widget;
  my_value_t out;

  my_value_init(&out, NULL);

  /* conforming initials register. */
  sheet = my_css_parse_ex(NULL, good_initial, strlen(good_initial),
                          MY_CSS_PARSE_STRICT_AT_RULES, &error);
  ASSERT_NOT_NULL(sheet);
  ASSERT_EQ(my_css_property_def_count(sheet), 1u);
  my_css_sheet_destroy(sheet);

  memset(&error, 0, sizeof(error));
  sheet = my_css_parse_ex(NULL, decimal_initial, strlen(decimal_initial),
                          MY_CSS_PARSE_STRICT_AT_RULES, &error);
  ASSERT_NOT_NULL(sheet);
  ASSERT_EQ(my_css_property_def_count(sheet), 1u);
  my_css_sheet_destroy(sheet);

  /* a bare number, a px length, a spaced percent and a word are not
   * percentages — the rule is invalidated. */
  memset(&error, 0, sizeof(error));
  sheet = my_css_parse_ex(NULL, bare_number_initial,
                          strlen(bare_number_initial),
                          MY_CSS_PARSE_STRICT_AT_RULES, &error);
  ASSERT_NOT_NULL(sheet);
  ASSERT_EQ(my_css_property_def_count(sheet), 0u);
  my_css_sheet_destroy(sheet);

  memset(&error, 0, sizeof(error));
  sheet = my_css_parse_ex(NULL, px_initial, strlen(px_initial),
                          MY_CSS_PARSE_STRICT_AT_RULES, &error);
  ASSERT_NOT_NULL(sheet);
  ASSERT_EQ(my_css_property_def_count(sheet), 0u);
  my_css_sheet_destroy(sheet);

  memset(&error, 0, sizeof(error));
  sheet = my_css_parse_ex(NULL, spaced_initial, strlen(spaced_initial),
                          MY_CSS_PARSE_STRICT_AT_RULES, &error);
  ASSERT_NOT_NULL(sheet);
  ASSERT_EQ(my_css_property_def_count(sheet), 0u);
  my_css_sheet_destroy(sheet);

  memset(&error, 0, sizeof(error));
  sheet = my_css_parse_ex(NULL, word_initial, strlen(word_initial),
                          MY_CSS_PARSE_STRICT_AT_RULES, &error);
  ASSERT_NOT_NULL(sheet);
  ASSERT_EQ(my_css_property_def_count(sheet), 0u);
  my_css_sheet_destroy(sheet);

  /* a conforming cascaded value passes the gate and substitutes raw —
   * "50%" cannot parse as a color, so the declaration drops. */
  theme = my_theme_create(NULL);
  widget = my_widget_create(NULL, "button");
  widget->widget_type = "button";
  ASSERT_EQ(my_theme_load_css_ex(theme, good_value,
                                 MY_CSS_PARSE_STRICT_AT_RULES),
            MY_RET_OK);
  ASSERT_TRUE(!my_theme_get_for_widget_var(theme, widget, MY_STATE_NORMAL,
                                           "fg_color", &out));
  my_widget_unref(widget);
  my_theme_destroy(theme);

  /* a word value is guaranteed-invalid -> var() fallback. */
  theme = my_theme_create(NULL);
  widget = my_widget_create(NULL, "button");
  widget->widget_type = "button";
  ASSERT_EQ(my_theme_load_css_ex(theme, bad_value,
                                 MY_CSS_PARSE_STRICT_AT_RULES),
            MY_RET_OK);
  ASSERT_TRUE(my_theme_get_for_widget_var(theme, widget, MY_STATE_NORMAL,
                                          "fg_color", &out));
  ASSERT_EQ(my_value_get_uint32(&out), 0xFF0000FFu);
  my_widget_unref(widget);
  my_theme_destroy(theme);

  /* a bare number likewise. */
  theme = my_theme_create(NULL);
  widget = my_widget_create(NULL, "button");
  widget->widget_type = "button";
  ASSERT_EQ(my_theme_load_css_ex(theme, bare_number_value,
                                 MY_CSS_PARSE_STRICT_AT_RULES),
            MY_RET_OK);
  ASSERT_TRUE(my_theme_get_for_widget_var(theme, widget, MY_STATE_NORMAL,
                                          "fg_color", &out));
  ASSERT_EQ(my_value_get_uint32(&out), 0xFF0000FFu);
  my_widget_unref(widget);
  my_theme_destroy(theme);

  my_value_reset(&out);
}

TEST(css_import_position_and_charset_conformance)
{
  /* R656: import-position and @charset conformance — @import is valid only
   * at top level before any style rule or conditional at-rule (@charset
   * and @layer may precede); nested @import is invalid. @charset is valid
   * only as the very first statement, with a (case-insensitive) utf-8
   * label — the engine decodes UTF-8 only. */
  const css_import_entry_t entries[] = {
      {"x.css", "label { color: red; }", 21u}, {NULL, NULL, 0u}};
  const char* after_rule = "button { color: blue; } @import \"x.css\";";
  const char* after_media =
      "@media all { label { color: green; } } @import \"x.css\";";
  const char* nested = "@media all { @import \"x.css\"; }";
  const char* good_order =
      "@charset \"utf-8\"; @import \"x.css\"; @layer base;"
      " button { color: blue; }";
  const char* charset_first = "@charset \"UTF-8\"; button { color: blue; }";
  const char* charset_late = "button { color: blue; } @charset \"utf-8\";";
  const char* charset_nested = "@media all { @charset \"utf-8\"; }";
  const char* charset_unquoted = "@charset utf-8; button { color: blue; }";
  const char* charset_other = "@charset \"latin1\"; button { color: blue; }";
  my_css_parse_options_t options = {0};
  my_css_error_t error = {0};
  my_css_sheet_t* sheet;

  options.flags = MY_CSS_PARSE_STRICT_AT_RULES;
  options.resolve_import = css_test_resolve_import;
  options.import_context = (void*)entries;

  /* conforming order: charset -> import -> layer statement -> rules. */
  css_import_release_count = 0u;
  sheet = my_css_parse_with_options(NULL, good_order, strlen(good_order),
                                    &options, &error);
  ASSERT_NOT_NULL(sheet);
  ASSERT_EQ(my_css_rule_count(sheet), 2u);
  ASSERT_STR_EQ(my_css_selector(my_css_rule(sheet, 0u), 0u)->widget_type,
                "label");
  my_css_sheet_destroy(sheet);
  ASSERT_EQ(css_import_release_count, 1u);

  /* @charset as the first statement (case-insensitive label). */
  memset(&error, 0, sizeof(error));
  sheet = my_css_parse_with_options(NULL, charset_first,
                                    strlen(charset_first), &options, &error);
  ASSERT_NOT_NULL(sheet);
  ASSERT_EQ(my_css_rule_count(sheet), 1u);
  my_css_sheet_destroy(sheet);

  /* misplaced imports: strict rejects. */
  memset(&error, 0, sizeof(error));
  ASSERT_TRUE(my_css_parse_with_options(NULL, after_rule,
                                        strlen(after_rule), &options,
                                        &error) == NULL);
  ASSERT_EQ(error.code, MY_CSS_ERROR_UNSUPPORTED_FEATURE);
  ASSERT_EQ(error.capability, (uint32_t)MY_CSS_FEATURE_IMPORTS);

  memset(&error, 0, sizeof(error));
  ASSERT_TRUE(my_css_parse_with_options(NULL, after_media,
                                        strlen(after_media), &options,
                                        &error) == NULL);

  memset(&error, 0, sizeof(error));
  ASSERT_TRUE(my_css_parse_with_options(NULL, nested, strlen(nested),
                                        &options, &error) == NULL);

  /* compatibility mode: a misplaced import is skipped, not fatal. */
  options.flags = 0u;
  css_import_release_count = 0u;
  memset(&error, 0, sizeof(error));
  sheet = my_css_parse_with_options(NULL, after_rule, strlen(after_rule),
                                    &options, &error);
  ASSERT_NOT_NULL(sheet);
  ASSERT_EQ(my_css_rule_count(sheet), 1u);
  ASSERT_STR_EQ(my_css_selector(my_css_rule(sheet, 0u), 0u)->widget_type,
                "button");
  my_css_sheet_destroy(sheet);
  ASSERT_EQ(css_import_release_count, 0u);
  options.flags = MY_CSS_PARSE_STRICT_AT_RULES;

  /* @charset violations: strict rejects. */
  memset(&error, 0, sizeof(error));
  ASSERT_TRUE(my_css_parse_with_options(NULL, charset_late,
                                        strlen(charset_late), &options,
                                        &error) == NULL);
  memset(&error, 0, sizeof(error));
  ASSERT_TRUE(my_css_parse_with_options(NULL, charset_nested,
                                        strlen(charset_nested), &options,
                                        &error) == NULL);
  memset(&error, 0, sizeof(error));
  ASSERT_TRUE(my_css_parse_with_options(NULL, charset_unquoted,
                                        strlen(charset_unquoted), &options,
                                        &error) == NULL);
  memset(&error, 0, sizeof(error));
  ASSERT_TRUE(my_css_parse_with_options(NULL, charset_other,
                                        strlen(charset_other), &options,
                                        &error) == NULL);
}

TEST(css_import_media_qualifier_gates_resolution)
{
  /* R651: standard media-qualified imports — the query after the path is
   * evaluated with the full media-condition machinery (R650): a matching
   * import resolves inline, a non-matching one is skipped silently, a
   * conditional import without a media context follows the @media
   * convention (strict rejects, compatibility skips). */
  const css_import_entry_t entries[] = {
      {"wide.css", "label { color: red; }", 21u}, {NULL, NULL, 0u}};
  const char* matching =
      "@import \"wide.css\" screen and (min-width: 800px);"
      " button { color: blue; }";
  const char* non_matching =
      "@import \"wide.css\" screen and (min-width: 2000px);"
      " button { color: blue; }";
  const char* type_miss =
      "@import \"wide.css\" screen; button { color: blue; }";
  const char* mq4_or =
      "@import \"wide.css\" (min-width: 2000px) or (orientation: landscape);"
      " button { color: blue; }";
  const char* malformed =
      "@import \"wide.css\" screen and (bogus); button { color: blue; }";
  const char* unterminated =
      "@import \"wide.css\" screen and (min-width: 1px)";
  my_css_media_context_ex_t media = {
      {1024u, 768u, true, false, false, 0u}, MY_CSS_MEDIA_KNOWN_ALL};
  my_css_media_context_ex_t off_screen = {
      {1024u, 768u, false, false, false, 0u}, MY_CSS_MEDIA_KNOWN_ALL};
  my_css_parse_options_t options = {0};
  my_css_error_t error = {0};
  my_css_sheet_t* sheet;

  options.flags = MY_CSS_PARSE_STRICT_AT_RULES;
  options.media = &media;
  options.resolve_import = css_test_resolve_import;
  options.import_context = (void*)entries;

  /* matching query: imported rule flattens in source order. */
  css_import_release_count = 0u;
  sheet = my_css_parse_with_options(NULL, matching, strlen(matching),
                                    &options, &error);
  ASSERT_NOT_NULL(sheet);
  ASSERT_EQ(my_css_rule_count(sheet), 2u);
  ASSERT_STR_EQ(my_css_selector(my_css_rule(sheet, 0u), 0u)->widget_type,
                "label");
  my_css_sheet_destroy(sheet);
  ASSERT_EQ(css_import_release_count, 1u);

  /* non-matching query: the import is skipped without resolving. */
  css_import_release_count = 0u;
  memset(&error, 0, sizeof(error));
  sheet = my_css_parse_with_options(NULL, non_matching,
                                    strlen(non_matching), &options, &error);
  ASSERT_NOT_NULL(sheet);
  ASSERT_EQ(my_css_rule_count(sheet), 1u);
  ASSERT_STR_EQ(my_css_selector(my_css_rule(sheet, 0u), 0u)->widget_type,
                "button");
  my_css_sheet_destroy(sheet);
  ASSERT_EQ(css_import_release_count, 0u);

  /* type mismatch skips the same way. */
  css_import_release_count = 0u;
  memset(&error, 0, sizeof(error));
  options.media = &off_screen;
  sheet = my_css_parse_with_options(NULL, type_miss, strlen(type_miss),
                                    &options, &error);
  ASSERT_NOT_NULL(sheet);
  ASSERT_EQ(my_css_rule_count(sheet), 1u);
  my_css_sheet_destroy(sheet);
  ASSERT_EQ(css_import_release_count, 0u);
  options.media = &media;

  /* MQ4 or-chain in the qualifier (R650 machinery). */
  css_import_release_count = 0u;
  memset(&error, 0, sizeof(error));
  sheet = my_css_parse_with_options(NULL, mq4_or, strlen(mq4_or), &options,
                                    &error);
  ASSERT_NOT_NULL(sheet);
  ASSERT_EQ(my_css_rule_count(sheet), 2u);
  my_css_sheet_destroy(sheet);
  ASSERT_EQ(css_import_release_count, 1u);

  /* malformed qualifier: strict rejects. */
  memset(&error, 0, sizeof(error));
  ASSERT_TRUE(my_css_parse_with_options(NULL, malformed, strlen(malformed),
                                        &options, &error) == NULL);

  /* qualifier without the terminating ';': strict rejects. */
  memset(&error, 0, sizeof(error));
  ASSERT_TRUE(my_css_parse_with_options(NULL, unterminated,
                                        strlen(unterminated), &options,
                                        &error) == NULL);

  /* conditional qualifier without a media context: strict rejects. */
  memset(&error, 0, sizeof(error));
  options.media = NULL;
  ASSERT_TRUE(my_css_parse_with_options(NULL, matching, strlen(matching),
                                        &options, &error) == NULL);

  /* compatibility mode: the qualified import is skipped, not fatal. */
  memset(&error, 0, sizeof(error));
  options.flags = 0u;
  css_import_release_count = 0u;
  sheet = my_css_parse_with_options(NULL, matching, strlen(matching),
                                    &options, &error);
  ASSERT_NOT_NULL(sheet);
  ASSERT_EQ(my_css_rule_count(sheet), 1u);
  my_css_sheet_destroy(sheet);
  ASSERT_EQ(css_import_release_count, 0u);
}

TEST(css_import_supports_qualifier_gates_resolution)
{
  /* R652: the `supports(...)` import condition (same family as the media
   * qualifier) — evaluated with the @supports expression machinery before
   * the optional media query. A false condition skips the import; a
   * malformed one follows the qualifier convention (strict rejects,
   * compatibility skips). */
  const css_import_entry_t entries[] = {
      {"wide.css", "label { color: red; }", 21u}, {NULL, NULL, 0u}};
  const char* sup_hit =
      "@import \"wide.css\" supports (color: red); button { color: blue; }";
  const char* sup_miss =
      "@import \"wide.css\" supports (not (color: red));"
      " button { color: blue; }";
  const char* combined_hit =
      "@import \"wide.css\" supports (color: red) screen and"
      " (min-width: 800px); button { color: blue; }";
  const char* combined_media_miss =
      "@import \"wide.css\" supports (color: red) screen and"
      " (min-width: 2000px); button { color: blue; }";
  const char* unknown_decl =
      "@import \"wide.css\" supports (display: grid);"
      " button { color: blue; }";
  const char* unbalanced =
      "@import \"wide.css\" supports (color: red;"
      " button { color: blue; }";
  my_css_media_context_ex_t media = {
      {1024u, 768u, true, false, false, 0u}, MY_CSS_MEDIA_KNOWN_ALL};
  my_css_parse_options_t options = {0};
  my_css_error_t error = {0};
  my_css_sheet_t* sheet;

  options.flags = MY_CSS_PARSE_STRICT_AT_RULES;
  options.media = &media;
  options.resolve_import = css_test_resolve_import;
  options.import_context = (void*)entries;

  /* supported declaration: the import resolves. */
  css_import_release_count = 0u;
  sheet = my_css_parse_with_options(NULL, sup_hit, strlen(sup_hit),
                                    &options, &error);
  ASSERT_NOT_NULL(sheet);
  ASSERT_EQ(my_css_rule_count(sheet), 2u);
  my_css_sheet_destroy(sheet);
  ASSERT_EQ(css_import_release_count, 1u);

  /* legal false condition: skipped without resolving. */
  css_import_release_count = 0u;
  memset(&error, 0, sizeof(error));
  sheet = my_css_parse_with_options(NULL, sup_miss, strlen(sup_miss),
                                    &options, &error);
  ASSERT_NOT_NULL(sheet);
  ASSERT_EQ(my_css_rule_count(sheet), 1u);
  my_css_sheet_destroy(sheet);
  ASSERT_EQ(css_import_release_count, 0u);

  /* combined supports + media: both gates apply. */
  css_import_release_count = 0u;
  memset(&error, 0, sizeof(error));
  sheet = my_css_parse_with_options(NULL, combined_hit,
                                    strlen(combined_hit), &options, &error);
  ASSERT_NOT_NULL(sheet);
  ASSERT_EQ(my_css_rule_count(sheet), 2u);
  my_css_sheet_destroy(sheet);
  ASSERT_EQ(css_import_release_count, 1u);

  css_import_release_count = 0u;
  memset(&error, 0, sizeof(error));
  sheet = my_css_parse_with_options(NULL, combined_media_miss,
                                    strlen(combined_media_miss), &options,
                                    &error);
  ASSERT_NOT_NULL(sheet);
  ASSERT_EQ(my_css_rule_count(sheet), 1u);
  my_css_sheet_destroy(sheet);
  ASSERT_EQ(css_import_release_count, 0u);

  /* unknown declaration: strict rejects (the @supports contract). */
  memset(&error, 0, sizeof(error));
  ASSERT_TRUE(my_css_parse_with_options(NULL, unknown_decl,
                                        strlen(unknown_decl), &options,
                                        &error) == NULL);

  /* unbalanced supports group: strict rejects. */
  memset(&error, 0, sizeof(error));
  ASSERT_TRUE(my_css_parse_with_options(NULL, unbalanced,
                                        strlen(unbalanced), &options,
                                        &error) == NULL);

  /* compatibility mode: malformed supports skips just the import. */
  memset(&error, 0, sizeof(error));
  options.flags = 0u;
  css_import_release_count = 0u;
  sheet = my_css_parse_with_options(NULL, unknown_decl,
                                    strlen(unknown_decl), &options, &error);
  ASSERT_NOT_NULL(sheet);
  ASSERT_EQ(my_css_rule_count(sheet), 1u);
  my_css_sheet_destroy(sheet);
  ASSERT_EQ(css_import_release_count, 0u);
}

TEST(css_import_layer_qualifier_assigns_layer_order)
{
  /* R653: `layer(name)` import condition — the imported rules carry the
   * named layer's order (unlayered local rules still outrank them); it
   * composes with the supports/media conditions after it. Anonymous
   * `layer` follows the engine-wide subset: rejected everywhere. */
  const css_import_entry_t entries[] = {
      {"themed.css", "label { color: red; }", 21u},
      {"btn.css", "button { color: red; }", 22u},
      {NULL, NULL, 0u}};
  const char* layered =
      "@import \"themed.css\" layer(base); button { color: blue; }";
  const char* layered_media =
      "@import \"themed.css\" layer(base) screen and (min-width: 800px);"
      " button { color: blue; }";
  const char* layered_media_miss =
      "@import \"themed.css\" layer(base) screen and (min-width: 2000px);"
      " button { color: blue; }";
  const char* layered_supports =
      "@import \"themed.css\" layer(base) supports (color: red);"
      " button { color: blue; }";
  const char* bad_name = "@import \"themed.css\" layer(..x..);";
  const char* unbalanced = "@import \"themed.css\" layer(base;";
  const char* cascade =
      "@import \"btn.css\" layer(base); button { color: blue; }";
  my_css_media_context_ex_t media = {
      {1024u, 768u, true, false, false, 0u}, MY_CSS_MEDIA_KNOWN_ALL};
  my_css_parse_options_t options = {0};
  my_css_error_t error = {0};
  my_css_sheet_t* sheet;
  my_theme_t* theme;
  my_widget_t* widget;
  const my_value_t* value;

  options.flags = MY_CSS_PARSE_STRICT_AT_RULES;
  options.media = &media;
  options.resolve_import = css_test_resolve_import;
  options.import_context = (void*)entries;

  /* the imported rule carries the first registered layer; the local rule
   * stays unlayered. */
  css_import_release_count = 0u;
  sheet = my_css_parse_with_options(NULL, layered, strlen(layered),
                                    &options, &error);
  ASSERT_NOT_NULL(sheet);
  ASSERT_EQ(my_css_rule_count(sheet), 2u);
  ASSERT_EQ(my_css_rule(sheet, 0u)->layer_order, 0u);
  ASSERT_EQ(my_css_rule(sheet, 1u)->layer_order, MY_CSS_UNLAYERED_ORDER);
  my_css_sheet_destroy(sheet);
  ASSERT_EQ(css_import_release_count, 1u);

  /* layer + media, both gates live. */
  memset(&error, 0, sizeof(error));
  sheet = my_css_parse_with_options(NULL, layered_media,
                                    strlen(layered_media), &options, &error);
  ASSERT_NOT_NULL(sheet);
  ASSERT_EQ(my_css_rule_count(sheet), 2u);
  ASSERT_EQ(my_css_rule(sheet, 0u)->layer_order, 0u);
  my_css_sheet_destroy(sheet);

  css_import_release_count = 0u;
  memset(&error, 0, sizeof(error));
  sheet = my_css_parse_with_options(NULL, layered_media_miss,
                                    strlen(layered_media_miss), &options,
                                    &error);
  ASSERT_NOT_NULL(sheet);
  ASSERT_EQ(my_css_rule_count(sheet), 1u);
  my_css_sheet_destroy(sheet);
  ASSERT_EQ(css_import_release_count, 0u);

  /* layer + supports. */
  memset(&error, 0, sizeof(error));
  sheet = my_css_parse_with_options(NULL, layered_supports,
                                    strlen(layered_supports), &options,
                                    &error);
  ASSERT_NOT_NULL(sheet);
  ASSERT_EQ(my_css_rule_count(sheet), 2u);
  ASSERT_EQ(my_css_rule(sheet, 0u)->layer_order, 0u);
  my_css_sheet_destroy(sheet);

  /* cascade: the unlayered local rule outranks the layered import. */
  theme = my_theme_create(NULL);
  widget = my_widget_create(NULL, "button");
  ASSERT_NOT_NULL(theme);
  ASSERT_NOT_NULL(widget);
  widget->widget_type = "button";
  ASSERT_EQ(my_theme_load_css_with_options(theme, cascade, &options),
            MY_RET_OK);
  value = my_theme_get_for_widget(theme, widget, MY_STATE_NORMAL, "fg_color");
  ASSERT_NOT_NULL(value);
  ASSERT_EQ(my_value_get_uint32(value), 0x0000FFFFu);
  my_widget_unref(widget);
  my_theme_destroy(theme);

  /* malformed layer conditions: strict rejects. (The bare-`layer` case was
   * an R653 subset rejection; R655 turned it into the anonymous import
   * layer, pinned in css_anonymous_layers_get_unique_orders.) */
  memset(&error, 0, sizeof(error));
  ASSERT_TRUE(my_css_parse_with_options(NULL, bad_name, strlen(bad_name),
                                        &options, &error) == NULL);
  memset(&error, 0, sizeof(error));
  ASSERT_TRUE(my_css_parse_with_options(NULL, unbalanced,
                                        strlen(unbalanced), &options,
                                        &error) == NULL);
}

static void css_test_stack_spray_ident(void) {
  /* spray the deep stack with an identifier byte so a keyword-boundary
   * read past a buffer's logical length misfires deterministically. */
  volatile char pad[32768];
  size_t i;
  for (i = 0u; i < sizeof(pad); ++i) pad[i] = 'A';
}

TEST(css_import_bare_layer_qualifier_is_length_bounded)
{
  /* regression: the @import qualifier scanner never terminated its buffer,
   * so the bare `layer` keyword check read one byte past the qualifier —
   * an identifier-looking stack byte there silently turned the layer gate
   * into a media query and failed strict parses of `@import url layer;`.
   * (R663 CI: Linux-only "sheet is NULL" in the anonymous-layers test.) */
  const css_import_entry_t entries[] = {
      {"themed.css", "label { color: red; }", 21u}, {NULL, NULL, 0u}};
  const char* imported =
      "@import \"themed.css\" layer; button { color: blue; }";
  my_css_parse_options_t options = {0};
  my_css_error_t error = {0};
  my_css_sheet_t* sheet;

  css_test_stack_spray_ident();
  options.flags = MY_CSS_PARSE_STRICT_AT_RULES;
  options.resolve_import = css_test_resolve_import;
  options.import_context = (void*)entries;
  sheet = my_css_parse_with_options(NULL, imported, strlen(imported),
                                    &options, &error);
  ASSERT_NOT_NULL(sheet);
  ASSERT_EQ(my_css_rule_count(sheet), 2u);
  ASSERT_EQ(my_css_rule(sheet, 0u)->layer_order, 0u);
  ASSERT_EQ(my_css_rule(sheet, 1u)->layer_order, MY_CSS_UNLAYERED_ORDER);
  my_css_sheet_destroy(sheet);
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
  /* R621 note: "dialog extra" used to be malformed here — descendant limit
   * paths are now a supported feature (covered by
   * css_scope_limit_descendant_combinator). */
  const char* malformed[] = {
      "@scope to :hover { button { color: red; } }",
      "@scope to { button { color: red; } }",
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

TEST(css_scope_root_child_combinator)
{
  const char* css = "@scope panel > box { button { color: red; } }";
  my_css_error_t error = {0};
  my_css_sheet_t* sheet = my_css_parse_ex(
      NULL, css, strlen(css), MY_CSS_PARSE_STRICT_AT_RULES, &error);
  const my_css_selector_t* selector;
  my_theme_t* theme = my_theme_create(NULL);
  my_widget_t* panel = my_widget_create(NULL, "panel");
  my_widget_t* box = my_widget_create(NULL, "box");
  my_widget_t* hit = my_widget_create(NULL, "hit");
  my_widget_t* wrap = my_widget_create(NULL, "wrap");
  my_widget_t* box2 = my_widget_create(NULL, "box2");
  my_widget_t* miss = my_widget_create(NULL, "miss");
  const my_value_t* value;

  ASSERT_NOT_NULL(sheet);
  selector = my_css_selector(my_css_rule(sheet, 0u), 0u);
  ASSERT_NOT_NULL(selector);
  /* root path splices as nearest-first ancestors: box (descendant edge to
   * the rule subject), then panel with the child edge onto box. */
  ASSERT_EQ(selector->ancestor_count, 2u);
  ASSERT_STR_EQ(selector->ancestors[0].widget_type, "box");
  ASSERT_TRUE(selector->ancestor_direct_path[0] == false);
  ASSERT_STR_EQ(selector->ancestors[1].widget_type, "panel");
  ASSERT_TRUE(selector->ancestor_direct_path[1] == true);
  my_css_sheet_destroy(sheet);

  ASSERT_NOT_NULL(theme);
  panel->widget_type = "panel";
  box->widget_type = "box";
  hit->widget_type = "button";
  wrap->widget_type = "wrap";
  box2->widget_type = "box";
  miss->widget_type = "button";
  ASSERT_EQ(my_widget_add_child(panel, box), MY_RET_OK);
  ASSERT_EQ(my_widget_add_child(box, hit), MY_RET_OK);
  ASSERT_EQ(my_widget_add_child(panel, wrap), MY_RET_OK);
  ASSERT_EQ(my_widget_add_child(wrap, box2), MY_RET_OK);
  ASSERT_EQ(my_widget_add_child(box2, miss), MY_RET_OK);
  ASSERT_EQ(my_theme_load_css_ex(theme, css, MY_CSS_PARSE_STRICT_AT_RULES),
            MY_RET_OK);
  /* box IS a direct child of panel: the rule applies. */
  value = my_theme_get_for_widget(theme, hit, MY_STATE_NORMAL, "fg_color");
  ASSERT_NOT_NULL(value);
  ASSERT_EQ(my_value_get_uint32(value), 0xFF0000FFu);
  /* box2 is a DESCENDANT (not direct child) of panel: no match. */
  value = my_theme_get_for_widget(theme, miss, MY_STATE_NORMAL, "fg_color");
  ASSERT_TRUE(value == NULL);
  my_widget_unref(miss);
  my_widget_unref(box2);
  my_widget_unref(wrap);
  my_widget_unref(hit);
  my_widget_unref(box);
  my_widget_unref(panel);
  my_theme_destroy(theme);
}

TEST(css_scope_root_descendant_combinator)
{
  const char* css = "@scope panel box { button { color: red; } }";
  my_css_error_t error = {0};
  my_css_sheet_t* sheet = my_css_parse_ex(
      NULL, css, strlen(css), MY_CSS_PARSE_STRICT_AT_RULES, &error);
  const my_css_selector_t* selector;
  my_theme_t* theme = my_theme_create(NULL);
  my_widget_t* panel = my_widget_create(NULL, "panel");
  my_widget_t* wrap = my_widget_create(NULL, "wrap");
  my_widget_t* box = my_widget_create(NULL, "box");
  my_widget_t* hit = my_widget_create(NULL, "hit");
  my_widget_t* box2 = my_widget_create(NULL, "box2");
  my_widget_t* miss = my_widget_create(NULL, "miss");
  const my_value_t* value;

  ASSERT_NOT_NULL(sheet);
  selector = my_css_selector(my_css_rule(sheet, 0u), 0u);
  ASSERT_NOT_NULL(selector);
  ASSERT_EQ(selector->ancestor_count, 2u);
  ASSERT_STR_EQ(selector->ancestors[0].widget_type, "box");
  ASSERT_TRUE(selector->ancestor_direct_path[0] == false);
  ASSERT_STR_EQ(selector->ancestors[1].widget_type, "panel");
  ASSERT_TRUE(selector->ancestor_direct_path[1] == false);
  my_css_sheet_destroy(sheet);

  ASSERT_NOT_NULL(theme);
  panel->widget_type = "panel";
  wrap->widget_type = "wrap";
  box->widget_type = "box";
  hit->widget_type = "button";
  box2->widget_type = "box";
  miss->widget_type = "button";
  ASSERT_EQ(my_widget_add_child(panel, wrap), MY_RET_OK);
  ASSERT_EQ(my_widget_add_child(wrap, box), MY_RET_OK);
  ASSERT_EQ(my_widget_add_child(box, hit), MY_RET_OK);
  ASSERT_EQ(my_widget_add_child(box2, miss), MY_RET_OK);
  ASSERT_EQ(my_theme_load_css_ex(theme, css, MY_CSS_PARSE_STRICT_AT_RULES),
            MY_RET_OK);
  /* box is a deep descendant of panel: applies. */
  value = my_theme_get_for_widget(theme, hit, MY_STATE_NORMAL, "fg_color");
  ASSERT_NOT_NULL(value);
  ASSERT_EQ(my_value_get_uint32(value), 0xFF0000FFu);
  /* box2 has no panel ancestor at all: no match. */
  value = my_theme_get_for_widget(theme, miss, MY_STATE_NORMAL, "fg_color");
  ASSERT_TRUE(value == NULL);
  my_widget_unref(miss);
  my_widget_unref(box2);
  my_widget_unref(hit);
  my_widget_unref(box);
  my_widget_unref(wrap);
  my_widget_unref(panel);
  my_theme_destroy(theme);
}

TEST(css_scope_root_path_to_limit_boundary)
{
  const char* css = "@scope app > panel to dialog { button { color: red; } }";
  my_css_error_t error = {0};
  my_css_sheet_t* sheet = my_css_parse_ex(
      NULL, css, strlen(css), MY_CSS_PARSE_STRICT_AT_RULES, &error);
  const my_css_selector_t* selector;
  my_theme_t* theme = my_theme_create(NULL);
  my_widget_t* above = my_widget_create(NULL, "above");
  my_widget_t* app = my_widget_create(NULL, "app");
  my_widget_t* panel = my_widget_create(NULL, "panel");
  my_widget_t* hit = my_widget_create(NULL, "hit");
  my_widget_t* dialog = my_widget_create(NULL, "dialog");
  my_widget_t* blocked = my_widget_create(NULL, "blocked");
  const my_value_t* value;

  ASSERT_NOT_NULL(sheet);
  selector = my_css_selector(my_css_rule(sheet, 0u), 0u);
  ASSERT_NOT_NULL(selector);
  ASSERT_EQ(selector->ancestor_count, 2u);
  ASSERT_EQ(selector->scope_limit_count, 1u);
  ASSERT_STR_EQ(selector->scope_limits[0].widget_type, "dialog");
  /* the limit scan is bounded by the root SUBJECT slot (nearest), not by
   * the outermost path compound. */
  ASSERT_EQ(selector->scope_limit_root_index[0], 0u);
  my_css_sheet_destroy(sheet);

  ASSERT_NOT_NULL(theme);
  above->widget_type = "dialog";
  app->widget_type = "app";
  panel->widget_type = "panel";
  hit->widget_type = "button";
  dialog->widget_type = "dialog";
  blocked->widget_type = "button";
  /* dialog sits ABOVE the root path: it is outside the scope and must not
   * exclude the rule. */
  ASSERT_EQ(my_widget_add_child(above, app), MY_RET_OK);
  ASSERT_EQ(my_widget_add_child(app, panel), MY_RET_OK);
  ASSERT_EQ(my_widget_add_child(panel, hit), MY_RET_OK);
  /* a dialog BETWEEN root subject and subject excludes. */
  ASSERT_EQ(my_widget_add_child(panel, dialog), MY_RET_OK);
  ASSERT_EQ(my_widget_add_child(dialog, blocked), MY_RET_OK);
  ASSERT_EQ(my_theme_load_css_ex(theme, css, MY_CSS_PARSE_STRICT_AT_RULES),
            MY_RET_OK);
  value = my_theme_get_for_widget(theme, hit, MY_STATE_NORMAL, "fg_color");
  ASSERT_NOT_NULL(value);
  ASSERT_EQ(my_value_get_uint32(value), 0xFF0000FFu);
  value = my_theme_get_for_widget(theme, blocked, MY_STATE_NORMAL, "fg_color");
  ASSERT_TRUE(value == NULL);
  my_widget_unref(blocked);
  my_widget_unref(dialog);
  my_widget_unref(hit);
  my_widget_unref(panel);
  my_widget_unref(app);
  my_widget_unref(above);
  my_theme_destroy(theme);
}

TEST(css_scope_limit_root_index_pins_subject_slot)
{
  /* limit 'app' also matches the root path's own outer compound; the rule
   * must still apply because the limit scan stops at the root SUBJECT
   * (panel). A splice pointing root_index at the outermost slot would let
   * the limit match that compound and wrongly exclude. */
  const char* css = "@scope app > panel to app { button { color: red; } }";
  my_theme_t* theme = my_theme_create(NULL);
  my_widget_t* app = my_widget_create(NULL, "app");
  my_widget_t* panel = my_widget_create(NULL, "panel");
  my_widget_t* button = my_widget_create(NULL, "button");
  const my_value_t* value;

  ASSERT_NOT_NULL(theme);
  app->widget_type = "app";
  panel->widget_type = "panel";
  button->widget_type = "button";
  ASSERT_EQ(my_widget_add_child(app, panel), MY_RET_OK);
  ASSERT_EQ(my_widget_add_child(panel, button), MY_RET_OK);
  ASSERT_EQ(my_theme_load_css_ex(theme, css, MY_CSS_PARSE_STRICT_AT_RULES),
            MY_RET_OK);
  value = my_theme_get_for_widget(theme, button, MY_STATE_NORMAL, "fg_color");
  ASSERT_NOT_NULL(value);
  ASSERT_EQ(my_value_get_uint32(value), 0xFF0000FFu);
  my_widget_unref(button);
  my_widget_unref(panel);
  my_widget_unref(app);
  my_theme_destroy(theme);
}

TEST(css_scope_root_combinator_rejects_malformed)
{
  const char* malformed[] = {
      "@scope panel > { button { color: red; } }",
      "@scope panel > > box { button { color: red; } }",
      "@scope panel > to box { button { color: red; } }",
      "@scope a > b:hover { button { color: red; } }"};
  /* depth/budget rejections report UNSUPPORTED_FEATURE (same convention as
   * the pre-existing nesting-depth case), syntax rejections SYNTAX; both
   * carry the SCOPE capability. */
  const char* too_deep[] = {
      "@scope a b c d e f { button { color: red; } }",
      "@scope a b c { @scope d e { button { color: red; } } }"};
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
  for (i = 0u; i < sizeof(too_deep) / sizeof(too_deep[0]); ++i) {
    memset(&error, 0, sizeof(error));
    ASSERT_TRUE(my_css_parse_ex(NULL, too_deep[i], strlen(too_deep[i]),
                                MY_CSS_PARSE_STRICT_AT_RULES,
                                &error) == NULL);
    ASSERT_EQ(error.code, MY_CSS_ERROR_UNSUPPORTED_FEATURE);
    ASSERT_EQ(error.capability, (uint32_t)MY_CSS_FEATURE_SCOPE);
  }
}

TEST(css_scope_limit_child_combinator)
{
  const char* css = "@scope panel to dialog > box { button { color: red; } }";
  my_css_error_t error = {0};
  my_css_sheet_t* sheet = my_css_parse_ex(
      NULL, css, strlen(css), MY_CSS_PARSE_STRICT_AT_RULES, &error);
  const my_css_selector_t* selector;
  my_theme_t* theme = my_theme_create(NULL);
  my_widget_t* panel = my_widget_create(NULL, "panel");
  my_widget_t* dialog = my_widget_create(NULL, "dialog");
  my_widget_t* box = my_widget_create(NULL, "box");
  my_widget_t* blocked = my_widget_create(NULL, "blocked");
  my_widget_t* wrap = my_widget_create(NULL, "wrap");
  my_widget_t* box2 = my_widget_create(NULL, "box2");
  my_widget_t* hit = my_widget_create(NULL, "hit");
  const my_value_t* value;

  ASSERT_NOT_NULL(sheet);
  selector = my_css_selector(my_css_rule(sheet, 0u), 0u);
  ASSERT_NOT_NULL(selector);
  /* the limit is a path: subject box + child edge onto dialog. */
  ASSERT_EQ(selector->scope_limit_count, 1u);
  ASSERT_STR_EQ(selector->scope_limits[0].widget_type, "box");
  ASSERT_EQ(selector->scope_limits[0].ancestor_count, 1u);
  ASSERT_STR_EQ(selector->scope_limits[0].ancestors[0].widget_type, "dialog");
  ASSERT_TRUE(selector->scope_limits[0].ancestor_direct_path[0] == true);
  ASSERT_EQ(selector->scope_limit_root_index[0], 0u);
  my_css_sheet_destroy(sheet);

  ASSERT_NOT_NULL(theme);
  panel->widget_type = "panel";
  dialog->widget_type = "dialog";
  box->widget_type = "box";
  blocked->widget_type = "button";
  wrap->widget_type = "wrap";
  box2->widget_type = "box";
  hit->widget_type = "button";
  /* box IS a direct child of dialog: boundary, excludes the subtree. */
  ASSERT_EQ(my_widget_add_child(panel, dialog), MY_RET_OK);
  ASSERT_EQ(my_widget_add_child(dialog, box), MY_RET_OK);
  ASSERT_EQ(my_widget_add_child(box, blocked), MY_RET_OK);
  /* box2's parent is wrap (not dialog): the limit path does not match, the
   * rule applies. */
  ASSERT_EQ(my_widget_add_child(panel, wrap), MY_RET_OK);
  ASSERT_EQ(my_widget_add_child(wrap, box2), MY_RET_OK);
  ASSERT_EQ(my_widget_add_child(box2, hit), MY_RET_OK);
  ASSERT_EQ(my_theme_load_css_ex(theme, css, MY_CSS_PARSE_STRICT_AT_RULES),
            MY_RET_OK);
  value = my_theme_get_for_widget(theme, hit, MY_STATE_NORMAL, "fg_color");
  ASSERT_NOT_NULL(value);
  ASSERT_EQ(my_value_get_uint32(value), 0xFF0000FFu);
  value = my_theme_get_for_widget(theme, blocked, MY_STATE_NORMAL, "fg_color");
  ASSERT_TRUE(value == NULL);
  my_widget_unref(hit);
  my_widget_unref(box2);
  my_widget_unref(wrap);
  my_widget_unref(blocked);
  my_widget_unref(box);
  my_widget_unref(dialog);
  my_widget_unref(panel);
  my_theme_destroy(theme);
}

TEST(css_scope_limit_descendant_combinator)
{
  const char* css = "@scope panel to dialog box { button { color: red; } }";
  my_css_error_t error = {0};
  my_css_sheet_t* sheet = my_css_parse_ex(
      NULL, css, strlen(css), MY_CSS_PARSE_STRICT_AT_RULES, &error);
  const my_css_selector_t* selector;
  my_theme_t* theme = my_theme_create(NULL);
  my_widget_t* panel = my_widget_create(NULL, "panel");
  my_widget_t* dialog = my_widget_create(NULL, "dialog");
  my_widget_t* wrap = my_widget_create(NULL, "wrap");
  my_widget_t* box = my_widget_create(NULL, "box");
  my_widget_t* blocked = my_widget_create(NULL, "blocked");
  my_widget_t* box2 = my_widget_create(NULL, "box2");
  my_widget_t* hit = my_widget_create(NULL, "hit");
  const my_value_t* value;

  ASSERT_NOT_NULL(sheet);
  selector = my_css_selector(my_css_rule(sheet, 0u), 0u);
  ASSERT_NOT_NULL(selector);
  ASSERT_EQ(selector->scope_limit_count, 1u);
  ASSERT_STR_EQ(selector->scope_limits[0].widget_type, "box");
  ASSERT_EQ(selector->scope_limits[0].ancestor_count, 1u);
  ASSERT_STR_EQ(selector->scope_limits[0].ancestors[0].widget_type, "dialog");
  ASSERT_TRUE(selector->scope_limits[0].ancestor_direct_path[0] == false);
  my_css_sheet_destroy(sheet);

  ASSERT_NOT_NULL(theme);
  panel->widget_type = "panel";
  dialog->widget_type = "dialog";
  wrap->widget_type = "wrap";
  box->widget_type = "box";
  blocked->widget_type = "button";
  box2->widget_type = "box";
  hit->widget_type = "button";
  /* box has a dialog ANCESTOR (not necessarily parent): boundary. */
  ASSERT_EQ(my_widget_add_child(panel, dialog), MY_RET_OK);
  ASSERT_EQ(my_widget_add_child(dialog, wrap), MY_RET_OK);
  ASSERT_EQ(my_widget_add_child(wrap, box), MY_RET_OK);
  ASSERT_EQ(my_widget_add_child(box, blocked), MY_RET_OK);
  /* box2 without any dialog ancestor: rule applies. */
  ASSERT_EQ(my_widget_add_child(panel, box2), MY_RET_OK);
  ASSERT_EQ(my_widget_add_child(box2, hit), MY_RET_OK);
  ASSERT_EQ(my_theme_load_css_ex(theme, css, MY_CSS_PARSE_STRICT_AT_RULES),
            MY_RET_OK);
  value = my_theme_get_for_widget(theme, hit, MY_STATE_NORMAL, "fg_color");
  ASSERT_NOT_NULL(value);
  ASSERT_EQ(my_value_get_uint32(value), 0xFF0000FFu);
  value = my_theme_get_for_widget(theme, blocked, MY_STATE_NORMAL, "fg_color");
  ASSERT_TRUE(value == NULL);
  my_widget_unref(hit);
  my_widget_unref(box2);
  my_widget_unref(blocked);
  my_widget_unref(box);
  my_widget_unref(wrap);
  my_widget_unref(dialog);
  my_widget_unref(panel);
  my_theme_destroy(theme);
}

TEST(css_scope_limit_combinator_excludes_boundary_itself)
{
  /* the complex-limit analogue of css_scope_to_clause_excludes_boundary_
   * element_itself: a widget matching the full limit path (subject compound
   * + ancestors) is itself outside the scope. */
  const char* css = "@scope panel to dialog > button { button { color: red; } }";
  my_theme_t* theme = my_theme_create(NULL);
  my_widget_t* panel = my_widget_create(NULL, "panel");
  my_widget_t* dialog = my_widget_create(NULL, "dialog");
  my_widget_t* blocked = my_widget_create(NULL, "blocked");
  my_widget_t* hit = my_widget_create(NULL, "hit");
  const my_value_t* value;

  ASSERT_NOT_NULL(theme);
  panel->widget_type = "panel";
  dialog->widget_type = "dialog";
  blocked->widget_type = "button";
  hit->widget_type = "button";
  ASSERT_EQ(my_widget_add_child(panel, dialog), MY_RET_OK);
  ASSERT_EQ(my_widget_add_child(dialog, blocked), MY_RET_OK);
  ASSERT_EQ(my_widget_add_child(panel, hit), MY_RET_OK);
  ASSERT_EQ(my_theme_load_css_ex(theme, css, MY_CSS_PARSE_STRICT_AT_RULES),
            MY_RET_OK);
  value = my_theme_get_for_widget(theme, hit, MY_STATE_NORMAL, "fg_color");
  ASSERT_NOT_NULL(value);
  ASSERT_EQ(my_value_get_uint32(value), 0xFF0000FFu);
  value = my_theme_get_for_widget(theme, blocked, MY_STATE_NORMAL, "fg_color");
  ASSERT_TRUE(value == NULL);
  my_widget_unref(hit);
  my_widget_unref(blocked);
  my_widget_unref(dialog);
  my_widget_unref(panel);
  my_theme_destroy(theme);
}

TEST(css_scope_limit_selector_list_with_paths)
{
  const char* css = "@scope panel to a > b, c { button { color: red; } }";
  my_css_error_t error = {0};
  my_css_sheet_t* sheet = my_css_parse_ex(
      NULL, css, strlen(css), MY_CSS_PARSE_STRICT_AT_RULES, &error);
  const my_css_selector_t* selector;
  my_theme_t* theme = my_theme_create(NULL);
  my_widget_t* panel = my_widget_create(NULL, "panel");
  my_widget_t* wa = my_widget_create(NULL, "wa");
  my_widget_t* wb = my_widget_create(NULL, "wb");
  my_widget_t* blocked1 = my_widget_create(NULL, "blocked1");
  my_widget_t* wc = my_widget_create(NULL, "wc");
  my_widget_t* blocked2 = my_widget_create(NULL, "blocked2");
  my_widget_t* hit = my_widget_create(NULL, "hit");
  const my_value_t* value;

  ASSERT_NOT_NULL(sheet);
  selector = my_css_selector(my_css_rule(sheet, 0u), 0u);
  ASSERT_NOT_NULL(selector);
  ASSERT_EQ(selector->scope_limit_count, 2u);
  ASSERT_STR_EQ(selector->scope_limits[0].widget_type, "b");
  ASSERT_EQ(selector->scope_limits[0].ancestor_count, 1u);
  ASSERT_STR_EQ(selector->scope_limits[0].ancestors[0].widget_type, "a");
  ASSERT_TRUE(selector->scope_limits[0].ancestor_direct_path[0] == true);
  ASSERT_STR_EQ(selector->scope_limits[1].widget_type, "c");
  ASSERT_EQ(selector->scope_limits[1].ancestor_count, 0u);
  ASSERT_EQ(selector->scope_limit_root_index[0], 0u);
  ASSERT_EQ(selector->scope_limit_root_index[1], 0u);
  my_css_sheet_destroy(sheet);

  ASSERT_NOT_NULL(theme);
  panel->widget_type = "panel";
  wa->widget_type = "a";
  wb->widget_type = "b";
  blocked1->widget_type = "button";
  wc->widget_type = "c";
  blocked2->widget_type = "button";
  hit->widget_type = "button";
  ASSERT_EQ(my_widget_add_child(panel, wa), MY_RET_OK);
  ASSERT_EQ(my_widget_add_child(wa, wb), MY_RET_OK);
  ASSERT_EQ(my_widget_add_child(wb, blocked1), MY_RET_OK);
  ASSERT_EQ(my_widget_add_child(panel, wc), MY_RET_OK);
  ASSERT_EQ(my_widget_add_child(wc, blocked2), MY_RET_OK);
  ASSERT_EQ(my_widget_add_child(panel, hit), MY_RET_OK);
  ASSERT_EQ(my_theme_load_css_ex(theme, css, MY_CSS_PARSE_STRICT_AT_RULES),
            MY_RET_OK);
  value = my_theme_get_for_widget(theme, hit, MY_STATE_NORMAL, "fg_color");
  ASSERT_NOT_NULL(value);
  ASSERT_EQ(my_value_get_uint32(value), 0xFF0000FFu);
  value = my_theme_get_for_widget(theme, blocked1, MY_STATE_NORMAL,
                                  "fg_color");
  ASSERT_TRUE(value == NULL);
  value = my_theme_get_for_widget(theme, blocked2, MY_STATE_NORMAL,
                                  "fg_color");
  ASSERT_TRUE(value == NULL);
  my_widget_unref(hit);
  my_widget_unref(blocked2);
  my_widget_unref(wc);
  my_widget_unref(blocked1);
  my_widget_unref(wb);
  my_widget_unref(wa);
  my_widget_unref(panel);
  my_theme_destroy(theme);
}

TEST(css_scope_limit_combinator_rejects_malformed)
{
  const char* malformed[] = {
      "@scope panel to dialog > { button { color: red; } }",
      "@scope panel to dialog > > box { button { color: red; } }",
      "@scope panel to dialog > , box { button { color: red; } }",
      "@scope panel to a > b:hover { button { color: red; } }"};
  const char* too_deep[] = {
      "@scope panel to a b c d e f { button { color: red; } }"};
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
  for (i = 0u; i < sizeof(too_deep) / sizeof(too_deep[0]); ++i) {
    memset(&error, 0, sizeof(error));
    ASSERT_TRUE(my_css_parse_ex(NULL, too_deep[i], strlen(too_deep[i]),
                                MY_CSS_PARSE_STRICT_AT_RULES,
                                &error) == NULL);
    ASSERT_EQ(error.code, MY_CSS_ERROR_UNSUPPORTED_FEATURE);
    ASSERT_EQ(error.capability, (uint32_t)MY_CSS_FEATURE_SCOPE);
  }
}

TEST(css_scope_root_selector_list)
{
  const char* css = "@scope panel, dialog { button { color: red; } }";
  my_css_error_t error = {0};
  my_css_sheet_t* sheet = my_css_parse_ex(
      NULL, css, strlen(css), MY_CSS_PARSE_STRICT_AT_RULES, &error);
  my_theme_t* theme = my_theme_create(NULL);
  my_widget_t* panel = my_widget_create(NULL, "panel");
  my_widget_t* hit1 = my_widget_create(NULL, "hit1");
  my_widget_t* dialog = my_widget_create(NULL, "dialog");
  my_widget_t* hit2 = my_widget_create(NULL, "hit2");
  my_widget_t* wrap = my_widget_create(NULL, "wrap");
  my_widget_t* miss = my_widget_create(NULL, "miss");
  const my_value_t* value;

  ASSERT_NOT_NULL(sheet);
  /* one rule, TWO selector variants — one per root item. */
  ASSERT_EQ(my_css_rule_count(sheet), 1u);
  ASSERT_EQ(my_css_selector_count(my_css_rule(sheet, 0u)), 2u);
  ASSERT_EQ(my_css_selector(my_css_rule(sheet, 0u), 0u)->ancestor_count, 1u);
  ASSERT_STR_EQ(my_css_selector(my_css_rule(sheet, 0u), 0u)
                    ->ancestors[0]
                    .widget_type,
                "panel");
  ASSERT_STR_EQ(my_css_selector(my_css_rule(sheet, 0u), 1u)
                    ->ancestors[0]
                    .widget_type,
                "dialog");
  my_css_sheet_destroy(sheet);

  ASSERT_NOT_NULL(theme);
  panel->widget_type = "panel";
  hit1->widget_type = "button";
  dialog->widget_type = "dialog";
  hit2->widget_type = "button";
  wrap->widget_type = "wrap";
  miss->widget_type = "button";
  ASSERT_EQ(my_widget_add_child(panel, hit1), MY_RET_OK);
  ASSERT_EQ(my_widget_add_child(dialog, hit2), MY_RET_OK);
  ASSERT_EQ(my_widget_add_child(wrap, miss), MY_RET_OK);
  ASSERT_EQ(my_theme_load_css_ex(theme, css, MY_CSS_PARSE_STRICT_AT_RULES),
            MY_RET_OK);
  value = my_theme_get_for_widget(theme, hit1, MY_STATE_NORMAL, "fg_color");
  ASSERT_NOT_NULL(value);
  ASSERT_EQ(my_value_get_uint32(value), 0xFF0000FFu);
  value = my_theme_get_for_widget(theme, hit2, MY_STATE_NORMAL, "fg_color");
  ASSERT_NOT_NULL(value);
  ASSERT_EQ(my_value_get_uint32(value), 0xFF0000FFu);
  value = my_theme_get_for_widget(theme, miss, MY_STATE_NORMAL, "fg_color");
  ASSERT_TRUE(value == NULL);
  my_widget_unref(miss);
  my_widget_unref(wrap);
  my_widget_unref(hit2);
  my_widget_unref(dialog);
  my_widget_unref(hit1);
  my_widget_unref(panel);
  my_theme_destroy(theme);
}

TEST(css_scope_root_list_with_combinator_items)
{
  const char* css = "@scope app > panel, dialog { button { color: red; } }";
  my_css_error_t error = {0};
  my_css_sheet_t* sheet = my_css_parse_ex(
      NULL, css, strlen(css), MY_CSS_PARSE_STRICT_AT_RULES, &error);
  const my_css_rule_t* rule;
  my_theme_t* theme = my_theme_create(NULL);
  my_widget_t* app = my_widget_create(NULL, "app");
  my_widget_t* panel = my_widget_create(NULL, "panel");
  my_widget_t* hit = my_widget_create(NULL, "hit");
  my_widget_t* wrap = my_widget_create(NULL, "wrap");
  my_widget_t* panel2 = my_widget_create(NULL, "panel2");
  my_widget_t* miss = my_widget_create(NULL, "miss");
  my_widget_t* dialog = my_widget_create(NULL, "dialog");
  my_widget_t* hit2 = my_widget_create(NULL, "hit2");
  const my_value_t* value;

  ASSERT_NOT_NULL(sheet);
  rule = my_css_rule(sheet, 0u);
  ASSERT_EQ(my_css_selector_count(rule), 2u);
  /* variant 0 carries the full path of the first root item. */
  ASSERT_EQ(my_css_selector(rule, 0u)->ancestor_count, 2u);
  ASSERT_STR_EQ(my_css_selector(rule, 0u)->ancestors[0].widget_type, "panel");
  ASSERT_TRUE(my_css_selector(rule, 0u)->ancestor_direct_path[0] == false);
  ASSERT_STR_EQ(my_css_selector(rule, 0u)->ancestors[1].widget_type, "app");
  ASSERT_TRUE(my_css_selector(rule, 0u)->ancestor_direct_path[1] == true);
  ASSERT_EQ(my_css_selector(rule, 1u)->ancestor_count, 1u);
  ASSERT_STR_EQ(my_css_selector(rule, 1u)->ancestors[0].widget_type, "dialog");
  my_css_sheet_destroy(sheet);

  ASSERT_NOT_NULL(theme);
  app->widget_type = "app";
  panel->widget_type = "panel";
  hit->widget_type = "button";
  wrap->widget_type = "wrap";
  panel2->widget_type = "panel";
  miss->widget_type = "button";
  dialog->widget_type = "dialog";
  hit2->widget_type = "button";
  ASSERT_EQ(my_widget_add_child(app, panel), MY_RET_OK);
  ASSERT_EQ(my_widget_add_child(panel, hit), MY_RET_OK);
  /* panel2 is not a DIRECT child of app: the first root item misses. */
  ASSERT_EQ(my_widget_add_child(app, wrap), MY_RET_OK);
  ASSERT_EQ(my_widget_add_child(wrap, panel2), MY_RET_OK);
  ASSERT_EQ(my_widget_add_child(panel2, miss), MY_RET_OK);
  ASSERT_EQ(my_widget_add_child(dialog, hit2), MY_RET_OK);
  ASSERT_EQ(my_theme_load_css_ex(theme, css, MY_CSS_PARSE_STRICT_AT_RULES),
            MY_RET_OK);
  value = my_theme_get_for_widget(theme, hit, MY_STATE_NORMAL, "fg_color");
  ASSERT_NOT_NULL(value);
  ASSERT_EQ(my_value_get_uint32(value), 0xFF0000FFu);
  value = my_theme_get_for_widget(theme, miss, MY_STATE_NORMAL, "fg_color");
  ASSERT_TRUE(value == NULL);
  value = my_theme_get_for_widget(theme, hit2, MY_STATE_NORMAL, "fg_color");
  ASSERT_NOT_NULL(value);
  ASSERT_EQ(my_value_get_uint32(value), 0xFF0000FFu);
  my_widget_unref(hit2);
  my_widget_unref(dialog);
  my_widget_unref(miss);
  my_widget_unref(panel2);
  my_widget_unref(wrap);
  my_widget_unref(hit);
  my_widget_unref(panel);
  my_widget_unref(app);
  my_theme_destroy(theme);
}

TEST(css_scope_root_list_with_limit)
{
  /* limits are shared across root-list variants, each bounded at its own
   * variant's root subject slot. */
  const char* css = "@scope panel, dialog to box { button { color: red; } }";
  my_css_error_t error = {0};
  my_css_sheet_t* sheet = my_css_parse_ex(
      NULL, css, strlen(css), MY_CSS_PARSE_STRICT_AT_RULES, &error);
  const my_css_rule_t* rule;
  my_theme_t* theme = my_theme_create(NULL);
  my_widget_t* panel = my_widget_create(NULL, "panel");
  my_widget_t* box = my_widget_create(NULL, "box");
  my_widget_t* blocked1 = my_widget_create(NULL, "blocked1");
  my_widget_t* dialog = my_widget_create(NULL, "dialog");
  my_widget_t* box2 = my_widget_create(NULL, "box2");
  my_widget_t* blocked2 = my_widget_create(NULL, "blocked2");
  my_widget_t* hit = my_widget_create(NULL, "hit");
  const my_value_t* value;

  ASSERT_NOT_NULL(sheet);
  rule = my_css_rule(sheet, 0u);
  ASSERT_EQ(my_css_selector_count(rule), 2u);
  ASSERT_EQ(my_css_selector(rule, 0u)->scope_limit_count, 1u);
  ASSERT_EQ(my_css_selector(rule, 0u)->scope_limit_root_index[0], 0u);
  ASSERT_EQ(my_css_selector(rule, 1u)->scope_limit_count, 1u);
  ASSERT_EQ(my_css_selector(rule, 1u)->scope_limit_root_index[0], 0u);
  my_css_sheet_destroy(sheet);

  ASSERT_NOT_NULL(theme);
  panel->widget_type = "panel";
  box->widget_type = "box";
  blocked1->widget_type = "button";
  dialog->widget_type = "dialog";
  box2->widget_type = "box";
  blocked2->widget_type = "button";
  hit->widget_type = "button";
  ASSERT_EQ(my_widget_add_child(panel, box), MY_RET_OK);
  ASSERT_EQ(my_widget_add_child(box, blocked1), MY_RET_OK);
  ASSERT_EQ(my_widget_add_child(dialog, box2), MY_RET_OK);
  ASSERT_EQ(my_widget_add_child(box2, blocked2), MY_RET_OK);
  ASSERT_EQ(my_widget_add_child(panel, hit), MY_RET_OK);
  ASSERT_EQ(my_theme_load_css_ex(theme, css, MY_CSS_PARSE_STRICT_AT_RULES),
            MY_RET_OK);
  value = my_theme_get_for_widget(theme, hit, MY_STATE_NORMAL, "fg_color");
  ASSERT_NOT_NULL(value);
  ASSERT_EQ(my_value_get_uint32(value), 0xFF0000FFu);
  value = my_theme_get_for_widget(theme, blocked1, MY_STATE_NORMAL,
                                  "fg_color");
  ASSERT_TRUE(value == NULL);
  value = my_theme_get_for_widget(theme, blocked2, MY_STATE_NORMAL,
                                  "fg_color");
  ASSERT_TRUE(value == NULL);
  my_widget_unref(hit);
  my_widget_unref(blocked2);
  my_widget_unref(box2);
  my_widget_unref(dialog);
  my_widget_unref(blocked1);
  my_widget_unref(box);
  my_widget_unref(panel);
  my_theme_destroy(theme);
}

TEST(css_scope_root_list_expansion_is_bounded)
{
  /* nested root lists multiply: 2 x 2 = 4 variants here. */
  const char* nested =
      "@scope a, b { @scope c, d { button { color: red; } } }";
  /* 4 x 4 x 2 = 32 variants exceeds the expansion budget. */
  const char* over_budget =
      "@scope a, b, c, d { @scope e, f, g, h {"
      " @scope i, j { button { color: red; } } } }";
  /* a single root list is capped at MY_CSS_MAX_SCOPE_NESTING items. */
  const char* too_many =
      "@scope a, b, c, d, e { button { color: red; } }";
  my_css_error_t error = {0};
  my_css_sheet_t* sheet = my_css_parse_ex(
      NULL, nested, strlen(nested), MY_CSS_PARSE_STRICT_AT_RULES, &error);

  ASSERT_NOT_NULL(sheet);
  ASSERT_EQ(my_css_selector_count(my_css_rule(sheet, 0u)), 4u);
  my_css_sheet_destroy(sheet);

  memset(&error, 0, sizeof(error));
  ASSERT_TRUE(my_css_parse_ex(NULL, over_budget, strlen(over_budget),
                              MY_CSS_PARSE_STRICT_AT_RULES, &error) == NULL);
  ASSERT_EQ(error.code, MY_CSS_ERROR_UNSUPPORTED_FEATURE);
  ASSERT_EQ(error.capability, (uint32_t)MY_CSS_FEATURE_SCOPE);

  memset(&error, 0, sizeof(error));
  ASSERT_TRUE(my_css_parse_ex(NULL, too_many, strlen(too_many),
                              MY_CSS_PARSE_STRICT_AT_RULES, &error) == NULL);
  ASSERT_EQ(error.code, MY_CSS_ERROR_SYNTAX);
  ASSERT_EQ(error.capability, (uint32_t)MY_CSS_FEATURE_SCOPE);
}

TEST(css_scope_root_list_rejects_malformed)
{
  const char* malformed[] = {
      "@scope , panel { button { color: red; } }",
      "@scope panel, { button { color: red; } }",
      "@scope panel > , dialog { button { color: red; } }",
      "@scope panel, dialog:hover { button { color: red; } }"};
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

TEST(css_scope_paren_prelude_accepted)
{
  /* CSS's canonical @scope (root) to (limit) form, including combinators
   * and lists inside the parens; bare and parenthesized forms mix. */
  const char* both = "@scope (panel) to (.stop) { button { color: red; } }";
  const char* comb = "@scope (app > panel) { button { color: red; } }";
  const char* list = "@scope (panel, dialog) { button { color: red; } }";
  const char* mixed = "@scope (panel) to .stop { button { color: red; } }";
  my_css_error_t error = {0};
  my_css_sheet_t* sheet;

  sheet = my_css_parse_ex(NULL, both, strlen(both),
                          MY_CSS_PARSE_STRICT_AT_RULES, &error);
  ASSERT_NOT_NULL(sheet);
  ASSERT_EQ(my_css_selector(my_css_rule(sheet, 0u), 0u)->ancestor_count, 1u);
  ASSERT_EQ(my_css_selector(my_css_rule(sheet, 0u), 0u)->scope_limit_count,
            1u);
  my_css_sheet_destroy(sheet);

  sheet = my_css_parse_ex(NULL, comb, strlen(comb),
                          MY_CSS_PARSE_STRICT_AT_RULES, &error);
  ASSERT_NOT_NULL(sheet);
  ASSERT_EQ(my_css_selector(my_css_rule(sheet, 0u), 0u)->ancestor_count, 2u);
  ASSERT_TRUE(my_css_selector(my_css_rule(sheet, 0u), 0u)
                  ->ancestor_direct_path[1] == true);
  my_css_sheet_destroy(sheet);

  sheet = my_css_parse_ex(NULL, list, strlen(list),
                          MY_CSS_PARSE_STRICT_AT_RULES, &error);
  ASSERT_NOT_NULL(sheet);
  ASSERT_EQ(my_css_selector_count(my_css_rule(sheet, 0u)), 2u);
  my_css_sheet_destroy(sheet);

  sheet = my_css_parse_ex(NULL, mixed, strlen(mixed),
                          MY_CSS_PARSE_STRICT_AT_RULES, &error);
  ASSERT_NOT_NULL(sheet);
  ASSERT_EQ(my_css_selector(my_css_rule(sheet, 0u), 0u)->scope_limit_count,
            1u);
  my_css_sheet_destroy(sheet);

  /* theme behavior identical to the bare forms: (panel) to (.stop). */
  my_theme_t* theme = my_theme_create(NULL);
  my_widget_t* panel = my_widget_create(NULL, "panel");
  my_widget_t* hit = my_widget_create(NULL, "hit");
  my_widget_t* stop = my_widget_create(NULL, "stop");
  my_widget_t* blocked = my_widget_create(NULL, "blocked");
  const my_value_t* value;

  ASSERT_NOT_NULL(theme);
  panel->widget_type = "panel";
  hit->widget_type = "button";
  stop->widget_type = "stop";
  blocked->widget_type = "button";
  ASSERT_EQ(my_widget_set_style_class(stop, "stop"), MY_RET_OK);
  ASSERT_EQ(my_widget_add_child(panel, hit), MY_RET_OK);
  ASSERT_EQ(my_widget_add_child(panel, stop), MY_RET_OK);
  ASSERT_EQ(my_widget_add_child(stop, blocked), MY_RET_OK);
  ASSERT_EQ(my_theme_load_css_ex(theme, both, MY_CSS_PARSE_STRICT_AT_RULES),
            MY_RET_OK);
  value = my_theme_get_for_widget(theme, hit, MY_STATE_NORMAL, "fg_color");
  ASSERT_NOT_NULL(value);
  ASSERT_EQ(my_value_get_uint32(value), 0xFF0000FFu);
  value = my_theme_get_for_widget(theme, blocked, MY_STATE_NORMAL, "fg_color");
  ASSERT_TRUE(value == NULL);
  my_widget_unref(blocked);
  my_widget_unref(stop);
  my_widget_unref(hit);
  my_widget_unref(panel);
  my_theme_destroy(theme);

  /* (app > panel): combinator inside parens behaves like the bare form. */
  {
    my_theme_t* theme2 = my_theme_create(NULL);
    my_widget_t* app = my_widget_create(NULL, "app");
    my_widget_t* panel2 = my_widget_create(NULL, "panel2");
    my_widget_t* hit2 = my_widget_create(NULL, "hit2");
    my_widget_t* wrap = my_widget_create(NULL, "wrap");
    my_widget_t* panel3 = my_widget_create(NULL, "panel3");
    my_widget_t* miss = my_widget_create(NULL, "miss");
    ASSERT_NOT_NULL(theme2);
    app->widget_type = "app";
    panel2->widget_type = "panel";
    hit2->widget_type = "button";
    wrap->widget_type = "wrap";
    panel3->widget_type = "panel";
    miss->widget_type = "button";
    ASSERT_EQ(my_widget_add_child(app, panel2), MY_RET_OK);
    ASSERT_EQ(my_widget_add_child(panel2, hit2), MY_RET_OK);
    /* panel3 has an app ANCESTOR but not as its parent: child edge misses. */
    ASSERT_EQ(my_widget_add_child(app, wrap), MY_RET_OK);
    ASSERT_EQ(my_widget_add_child(wrap, panel3), MY_RET_OK);
    ASSERT_EQ(my_widget_add_child(panel3, miss), MY_RET_OK);
    ASSERT_EQ(my_theme_load_css_ex(theme2, comb, MY_CSS_PARSE_STRICT_AT_RULES),
              MY_RET_OK);
    value = my_theme_get_for_widget(theme2, hit2, MY_STATE_NORMAL, "fg_color");
    ASSERT_NOT_NULL(value);
    ASSERT_EQ(my_value_get_uint32(value), 0xFF0000FFu);
    value = my_theme_get_for_widget(theme2, miss, MY_STATE_NORMAL, "fg_color");
    ASSERT_TRUE(value == NULL);
    my_widget_unref(miss);
    my_widget_unref(panel3);
    my_widget_unref(wrap);
    my_widget_unref(hit2);
    my_widget_unref(panel2);
    my_widget_unref(app);
    my_theme_destroy(theme2);
  }
}

TEST(css_scope_paren_prelude_rejects_malformed)
{
  const char* malformed[] = {
      "@scope () { button { color: red; } }",
      "@scope (.panel { button { color: red; } }",
      "@scope (.panel)) { button { color: red; } }",
      "@scope (.panel) extra { button { color: red; } }",
      "@scope (panel to dialog) { button { color: red; } }",
      "@scope to (dialog { button { color: red; } }",
      "@scope to () { button { color: red; } }"};
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

TEST(css_scope_scope_pseudo_styles_root)
{
  /* :scope as the whole subject styles the scoping root element itself. */
  const char* css = "@scope panel { :scope { color: red; } }";
  /* nested: :scope binds the INNERMOST rooted scope. */
  const char* nested =
      "@scope a { @scope b { :scope { color: red; } } }";
  my_css_error_t error = {0};
  my_css_sheet_t* sheet = my_css_parse_ex(
      NULL, css, strlen(css), MY_CSS_PARSE_STRICT_AT_RULES, &error);
  const my_css_selector_t* selector;
  my_theme_t* theme = my_theme_create(NULL);
  my_widget_t* panel = my_widget_create(NULL, "panel");
  my_widget_t* child = my_widget_create(NULL, "child");
  const my_value_t* value;

  ASSERT_NOT_NULL(sheet);
  selector = my_css_selector(my_css_rule(sheet, 0u), 0u);
  ASSERT_NOT_NULL(selector);
  /* desugared: the rule's subject IS the root compound, no ancestors. */
  ASSERT_STR_EQ(selector->widget_type, "panel");
  ASSERT_EQ(selector->ancestor_count, 0u);
  ASSERT_TRUE(selector->scope_ref == false);
  my_css_sheet_destroy(sheet);

  sheet = my_css_parse_ex(NULL, nested, strlen(nested),
                          MY_CSS_PARSE_STRICT_AT_RULES, &error);
  ASSERT_NOT_NULL(sheet);
  selector = my_css_selector(my_css_rule(sheet, 0u), 0u);
  ASSERT_NOT_NULL(selector);
  ASSERT_STR_EQ(selector->widget_type, "b");
  ASSERT_EQ(selector->ancestor_count, 1u);
  ASSERT_STR_EQ(selector->ancestors[0].widget_type, "a");
  my_css_sheet_destroy(sheet);

  ASSERT_NOT_NULL(theme);
  panel->widget_type = "panel";
  child->widget_type = "button";
  ASSERT_EQ(my_widget_add_child(panel, child), MY_RET_OK);
  ASSERT_EQ(my_theme_load_css_ex(theme, css, MY_CSS_PARSE_STRICT_AT_RULES),
            MY_RET_OK);
  value = my_theme_get_for_widget(theme, panel, MY_STATE_NORMAL, "fg_color");
  ASSERT_NOT_NULL(value);
  ASSERT_EQ(my_value_get_uint32(value), 0xFF0000FFu);
  value = my_theme_get_for_widget(theme, child, MY_STATE_NORMAL, "fg_color");
  ASSERT_TRUE(value == NULL);
  my_widget_unref(child);
  my_widget_unref(panel);
  my_theme_destroy(theme);
}

TEST(css_scope_scope_pseudo_as_outermost_ancestor)
{
  /* :scope > button = the root's DIRECT children; :scope button = any
   * descendant. The edge combinator is the parsed one, not forced. */
  const char* direct = "@scope panel { :scope > button { color: red; } }";
  const char* desc = "@scope panel { :scope button { color: red; } }";
  my_css_error_t error = {0};
  my_css_sheet_t* sheet = my_css_parse_ex(
      NULL, direct, strlen(direct), MY_CSS_PARSE_STRICT_AT_RULES, &error);
  const my_css_selector_t* selector;
  my_theme_t* theme = my_theme_create(NULL);
  my_widget_t* panel = my_widget_create(NULL, "panel");
  my_widget_t* hit = my_widget_create(NULL, "hit");
  my_widget_t* mid = my_widget_create(NULL, "mid");
  my_widget_t* deep = my_widget_create(NULL, "deep");
  my_widget_t* outside = my_widget_create(NULL, "outside");
  const my_value_t* value;

  ASSERT_NOT_NULL(sheet);
  selector = my_css_selector(my_css_rule(sheet, 0u), 0u);
  ASSERT_NOT_NULL(selector);
  ASSERT_STR_EQ(selector->widget_type, "button");
  ASSERT_EQ(selector->ancestor_count, 1u);
  ASSERT_STR_EQ(selector->ancestors[0].widget_type, "panel");
  ASSERT_TRUE(selector->ancestor_direct_path[0] == true);
  my_css_sheet_destroy(sheet);

  sheet = my_css_parse_ex(NULL, desc, strlen(desc),
                          MY_CSS_PARSE_STRICT_AT_RULES, &error);
  ASSERT_NOT_NULL(sheet);
  selector = my_css_selector(my_css_rule(sheet, 0u), 0u);
  ASSERT_NOT_NULL(selector);
  ASSERT_EQ(selector->ancestor_count, 1u);
  ASSERT_TRUE(selector->ancestor_direct_path[0] == false);
  my_css_sheet_destroy(sheet);

  ASSERT_NOT_NULL(theme);
  panel->widget_type = "panel";
  hit->widget_type = "button";
  mid->widget_type = "wrap";
  deep->widget_type = "button";
  outside->widget_type = "button";
  ASSERT_EQ(my_widget_add_child(panel, hit), MY_RET_OK);
  ASSERT_EQ(my_widget_add_child(panel, mid), MY_RET_OK);
  ASSERT_EQ(my_widget_add_child(mid, deep), MY_RET_OK);
  ASSERT_EQ(my_theme_load_css_ex(theme, direct, MY_CSS_PARSE_STRICT_AT_RULES),
            MY_RET_OK);
  value = my_theme_get_for_widget(theme, hit, MY_STATE_NORMAL, "fg_color");
  ASSERT_NOT_NULL(value);
  ASSERT_EQ(my_value_get_uint32(value), 0xFF0000FFu);
  value = my_theme_get_for_widget(theme, deep, MY_STATE_NORMAL, "fg_color");
  ASSERT_TRUE(value == NULL); /* not a direct child of the root */
  value = my_theme_get_for_widget(theme, outside, MY_STATE_NORMAL, "fg_color");
  ASSERT_TRUE(value == NULL);
  my_widget_unref(deep);
  my_widget_unref(mid);
  my_widget_unref(hit);
  my_widget_unref(panel);
  my_widget_unref(outside);
  my_theme_destroy(theme);
}

TEST(css_scope_scope_pseudo_with_limit_and_list)
{
  /* root list: one variant per root item, each styling its own root;
   * a limit matching the root element itself still excludes it. */
  const char* css = "@scope panel, dialog to .stop { :scope { color: red; } }";
  my_css_error_t error = {0};
  my_css_sheet_t* sheet = my_css_parse_ex(
      NULL, css, strlen(css), MY_CSS_PARSE_STRICT_AT_RULES, &error);
  const my_css_rule_t* rule;
  my_theme_t* theme = my_theme_create(NULL);
  my_widget_t* panel = my_widget_create(NULL, "panel");
  my_widget_t* dialog = my_widget_create(NULL, "dialog");
  my_widget_t* stopped = my_widget_create(NULL, "stopped");
  my_widget_t* outside = my_widget_create(NULL, "outside");
  const my_value_t* value;

  ASSERT_NOT_NULL(sheet);
  rule = my_css_rule(sheet, 0u);
  ASSERT_EQ(my_css_selector_count(rule), 2u);
  ASSERT_STR_EQ(my_css_selector(rule, 0u)->widget_type, "panel");
  ASSERT_STR_EQ(my_css_selector(rule, 1u)->widget_type, "dialog");
  ASSERT_EQ(my_css_selector(rule, 0u)->scope_limit_count, 1u);
  my_css_sheet_destroy(sheet);

  ASSERT_NOT_NULL(theme);
  panel->widget_type = "panel";
  dialog->widget_type = "dialog";
  stopped->widget_type = "panel";
  outside->widget_type = "box";
  ASSERT_EQ(my_widget_set_style_class(stopped, "stop"), MY_RET_OK);
  ASSERT_EQ(my_theme_load_css_ex(theme, css, MY_CSS_PARSE_STRICT_AT_RULES),
            MY_RET_OK);
  value = my_theme_get_for_widget(theme, panel, MY_STATE_NORMAL, "fg_color");
  ASSERT_NOT_NULL(value);
  ASSERT_EQ(my_value_get_uint32(value), 0xFF0000FFu);
  value = my_theme_get_for_widget(theme, dialog, MY_STATE_NORMAL, "fg_color");
  ASSERT_NOT_NULL(value);
  ASSERT_EQ(my_value_get_uint32(value), 0xFF0000FFu);
  /* the root matching the limit compound is excluded (limit checks the
   * queried widget itself first — the R621 path with an empty path). */
  value = my_theme_get_for_widget(theme, stopped, MY_STATE_NORMAL, "fg_color");
  ASSERT_TRUE(value == NULL);
  value = my_theme_get_for_widget(theme, outside, MY_STATE_NORMAL, "fg_color");
  ASSERT_TRUE(value == NULL);
  my_widget_unref(outside);
  my_widget_unref(stopped);
  my_widget_unref(dialog);
  my_widget_unref(panel);
  my_theme_destroy(theme);
}

TEST(css_scope_scope_pseudo_rejects_misuse)
{
  const char* malformed[] = {
      ":scope { color: red; }",                         /* outside @scope */
      "@scope to dialog { :scope { color: red; } }",    /* implicit root */
      "@scope panel { a :scope b { color: red; } }",    /* mid-path */
      "@scope panel { x:scope { color: red; } }",       /* type-qualified */
      "@scope :scope { button { color: red; } }",       /* in the root */
      "@scope panel to :scope { button { color: red; } }" /* in a limit */};
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

TEST(css_nest_child_path)
{
  /* `.panel { color: blue; & > button { color: red; } }` — the nested rule
   * desugars to `panel > button` at parse time, inheriting the parent's
   * place in source order. */
  const char* css =
      ".panel { color: blue; & > button { color: red; } }";
  my_css_error_t error = {0};
  my_css_sheet_t* sheet = my_css_parse_ex(
      NULL, css, strlen(css), MY_CSS_PARSE_STRICT_AT_RULES, &error);
  const my_css_selector_t* nested;
  my_theme_t* theme = my_theme_create(NULL);
  my_widget_t* panel = my_widget_create(NULL, "panel");
  my_widget_t* hit = my_widget_create(NULL, "hit");
  my_widget_t* wrap = my_widget_create(NULL, "wrap");
  my_widget_t* miss = my_widget_create(NULL, "miss");
  const my_value_t* value;

  ASSERT_NOT_NULL(sheet);
  ASSERT_EQ(my_css_rule_count(sheet), 2u);
  /* rule 0 = the parent's own declarations. */
  ASSERT_STR_EQ(my_css_selector(my_css_rule(sheet, 0u), 0u)->style_class,
                "panel");
  /* rule 1 = the desugared nested rule: button with direct parent panel. */
  nested = my_css_selector(my_css_rule(sheet, 1u), 0u);
  ASSERT_NOT_NULL(nested);
  ASSERT_STR_EQ(nested->widget_type, "button");
  ASSERT_EQ(nested->ancestor_count, 1u);
  ASSERT_STR_EQ(nested->ancestors[0].style_class, "panel");
  ASSERT_TRUE(nested->ancestor_direct_path[0] == true);
  ASSERT_TRUE(nested->nest_ref == false);
  my_css_sheet_destroy(sheet);

  ASSERT_NOT_NULL(theme);
  panel->widget_type = "panel";
  hit->widget_type = "button";
  wrap->widget_type = "wrap";
  miss->widget_type = "button";
  ASSERT_EQ(my_widget_set_style_class(panel, "panel"), MY_RET_OK);
  ASSERT_EQ(my_widget_add_child(panel, hit), MY_RET_OK);
  ASSERT_EQ(my_widget_add_child(wrap, miss), MY_RET_OK);
  ASSERT_EQ(my_theme_load_css_ex(theme, css, MY_CSS_PARSE_STRICT_AT_RULES),
            MY_RET_OK);
  value = my_theme_get_for_widget(theme, hit, MY_STATE_NORMAL, "fg_color");
  ASSERT_NOT_NULL(value);
  ASSERT_EQ(my_value_get_uint32(value), 0xFF0000FFu);
  value = my_theme_get_for_widget(theme, panel, MY_STATE_NORMAL, "fg_color");
  ASSERT_NOT_NULL(value);
  ASSERT_EQ(my_value_get_uint32(value), 0x0000FFFFu);
  value = my_theme_get_for_widget(theme, miss, MY_STATE_NORMAL, "fg_color");
  ASSERT_TRUE(value == NULL);
  my_widget_unref(miss);
  my_widget_unref(wrap);
  my_widget_unref(hit);
  my_widget_unref(panel);
  my_theme_destroy(theme);
}

TEST(css_nest_descendant_and_group)
{
  /* group parent + descendant nested path: `.a, .b { & button {...} }`
   * expands one variant per parent selector (descendant edge). */
  const char* css = ".a, .b { & button { color: red; } }";
  my_css_error_t error = {0};
  my_css_sheet_t* sheet = my_css_parse_ex(
      NULL, css, strlen(css), MY_CSS_PARSE_STRICT_AT_RULES, &error);
  const my_css_rule_t* rule;
  my_theme_t* theme = my_theme_create(NULL);
  my_widget_t* a = my_widget_create(NULL, "a");
  my_widget_t* wrap = my_widget_create(NULL, "wrap");
  my_widget_t* hit1 = my_widget_create(NULL, "hit1");
  my_widget_t* b = my_widget_create(NULL, "b");
  my_widget_t* hit2 = my_widget_create(NULL, "hit2");
  my_widget_t* miss = my_widget_create(NULL, "miss");
  const my_value_t* value;

  ASSERT_NOT_NULL(sheet);
  /* rule 0 = the parent (zero own declarations); rule 1 = the nested
   * rule with one selector variant per parent (source order). */
  ASSERT_EQ(my_css_rule_count(sheet), 2u);
  rule = my_css_rule(sheet, 1u);
  ASSERT_NOT_NULL(rule);
  ASSERT_EQ(my_css_selector_count(rule), 2u);
  ASSERT_STR_EQ(my_css_selector(rule, 0u)->ancestors[0].style_class, "a");
  ASSERT_STR_EQ(my_css_selector(rule, 1u)->ancestors[0].style_class, "b");
  ASSERT_TRUE(my_css_selector(rule, 0u)->ancestor_direct_path[0] == false);
  my_css_sheet_destroy(sheet);

  ASSERT_NOT_NULL(theme);
  a->widget_type = "wrap";
  wrap->widget_type = "wrap";
  hit1->widget_type = "button";
  b->widget_type = "wrap";
  hit2->widget_type = "button";
  miss->widget_type = "button";
  ASSERT_EQ(my_widget_set_style_class(a, "a"), MY_RET_OK);
  ASSERT_EQ(my_widget_set_style_class(b, "b"), MY_RET_OK);
  ASSERT_EQ(my_widget_add_child(a, wrap), MY_RET_OK);
  ASSERT_EQ(my_widget_add_child(wrap, hit1), MY_RET_OK);
  ASSERT_EQ(my_widget_add_child(b, hit2), MY_RET_OK);
  ASSERT_EQ(my_theme_load_css_ex(theme, css, MY_CSS_PARSE_STRICT_AT_RULES),
            MY_RET_OK);
  value = my_theme_get_for_widget(theme, hit1, MY_STATE_NORMAL, "fg_color");
  ASSERT_NOT_NULL(value);
  ASSERT_EQ(my_value_get_uint32(value), 0xFF0000FFu);
  value = my_theme_get_for_widget(theme, hit2, MY_STATE_NORMAL, "fg_color");
  ASSERT_NOT_NULL(value);
  ASSERT_EQ(my_value_get_uint32(value), 0xFF0000FFu);
  value = my_theme_get_for_widget(theme, miss, MY_STATE_NORMAL, "fg_color");
  ASSERT_TRUE(value == NULL);
  my_widget_unref(miss);
  my_widget_unref(hit2);
  my_widget_unref(b);
  my_widget_unref(hit1);
  my_widget_unref(wrap);
  my_widget_unref(a);
  my_theme_destroy(theme);
}

TEST(css_nest_state_merge)
{
  /* `button { color: blue; &:hover { color: red; } }` — subject merge:
   * same subject, the nested pseudo sets the rule's state. */
  const char* css = "button { color: blue; &:hover { color: red; } }";
  my_css_error_t error = {0};
  my_css_sheet_t* sheet = my_css_parse_ex(
      NULL, css, strlen(css), MY_CSS_PARSE_STRICT_AT_RULES, &error);
  const my_css_selector_t* nested;
  my_theme_t* theme = my_theme_create(NULL);
  my_widget_t* btn = my_widget_create(NULL, "btn");
  const my_value_t* value;

  ASSERT_NOT_NULL(sheet);
  ASSERT_EQ(my_css_rule_count(sheet), 2u);
  nested = my_css_selector(my_css_rule(sheet, 1u), 0u);
  ASSERT_NOT_NULL(nested);
  ASSERT_STR_EQ(nested->widget_type, "button");
  ASSERT_EQ(nested->state, (int32_t)MY_STATE_HOVER);
  ASSERT_EQ(nested->ancestor_count, 0u);
  my_css_sheet_destroy(sheet);

  ASSERT_NOT_NULL(theme);
  btn->widget_type = "button";
  ASSERT_EQ(my_theme_load_css_ex(theme, css, MY_CSS_PARSE_STRICT_AT_RULES),
            MY_RET_OK);
  value = my_theme_get_for_widget(theme, btn, MY_STATE_HOVER, "fg_color");
  ASSERT_NOT_NULL(value);
  ASSERT_EQ(my_value_get_uint32(value), 0xFF0000FFu);
  value = my_theme_get_for_widget(theme, btn, MY_STATE_NORMAL, "fg_color");
  ASSERT_NOT_NULL(value);
  ASSERT_EQ(my_value_get_uint32(value), 0x0000FFFFu);
  my_widget_unref(btn);
  my_theme_destroy(theme);
}

TEST(css_nest_rejects_malformed)
{
  const char* malformed[] = {
      "& button { color: red; }",                       /* top-level & */
      "button { & > { color: red; } }",                 /* dangling '>' */
      "button { &#x { color: red; } }",                 /* id merge */
      "button:hover { & .x { color: red; } }",          /* state parent */
      "button { & .x, .y { color: red; } }"};           /* nested group */
  my_css_error_t error = {0};
  size_t i;

  for (i = 0u; i < sizeof(malformed) / sizeof(malformed[0]); ++i) {
    memset(&error, 0, sizeof(error));
    ASSERT_TRUE(my_css_parse_ex(NULL, malformed[i], strlen(malformed[i]),
                                MY_CSS_PARSE_STRICT_AT_RULES,
                                &error) == NULL);
    ASSERT_EQ(error.code, MY_CSS_ERROR_SYNTAX);
    ASSERT_EQ(error.capability, (uint32_t)MY_CSS_FEATURE_NESTING);
  }
}

TEST(css_nest_group_subject_merge)
{
  /* `.panel { &:hover, &:pressed { color: red; } }` — one nested rule with
   * two subject-merge selectors (one per arm). */
  const char* css =
      ".panel { color: blue; &:hover, &:pressed { color: red; } }";
  my_css_error_t error = {0};
  my_css_sheet_t* sheet = my_css_parse_ex(
      NULL, css, strlen(css), MY_CSS_PARSE_STRICT_AT_RULES, &error);
  const my_css_rule_t* rule;
  my_theme_t* theme = my_theme_create(NULL);
  my_widget_t* panel = my_widget_create(NULL, "panel");
  const my_value_t* value;

  ASSERT_NOT_NULL(sheet);
  ASSERT_EQ(my_css_rule_count(sheet), 2u);
  rule = my_css_rule(sheet, 1u);
  ASSERT_NOT_NULL(rule);
  ASSERT_EQ(my_css_selector_count(rule), 2u);
  ASSERT_STR_EQ(my_css_selector(rule, 0u)->style_class, "panel");
  ASSERT_EQ(my_css_selector(rule, 0u)->state, (int32_t)MY_STATE_HOVER);
  ASSERT_STR_EQ(my_css_selector(rule, 1u)->style_class, "panel");
  ASSERT_EQ(my_css_selector(rule, 1u)->state, (int32_t)MY_STATE_PRESSED);
  ASSERT_TRUE(my_css_selector(rule, 0u)->nest_ref == false);
  ASSERT_TRUE(my_css_selector(rule, 1u)->nest_ref == false);
  my_css_sheet_destroy(sheet);

  ASSERT_NOT_NULL(theme);
  panel->widget_type = "panel";
  ASSERT_EQ(my_widget_set_style_class(panel, "panel"), MY_RET_OK);
  ASSERT_EQ(my_theme_load_css_ex(theme, css, MY_CSS_PARSE_STRICT_AT_RULES),
            MY_RET_OK);
  value = my_theme_get_for_widget(theme, panel, MY_STATE_HOVER, "fg_color");
  ASSERT_NOT_NULL(value);
  ASSERT_EQ(my_value_get_uint32(value), 0xFF0000FFu);
  value = my_theme_get_for_widget(theme, panel, MY_STATE_PRESSED,
                                  "fg_color");
  ASSERT_NOT_NULL(value);
  ASSERT_EQ(my_value_get_uint32(value), 0xFF0000FFu);
  value = my_theme_get_for_widget(theme, panel, MY_STATE_NORMAL, "fg_color");
  ASSERT_NOT_NULL(value);
  ASSERT_EQ(my_value_get_uint32(value), 0x0000FFFFu);
  my_widget_unref(panel);
  my_theme_destroy(theme);
}

TEST(css_nest_group_ancestor_forms)
{
  /* `.panel { & > button, & label { color: red; } }` — arms keep their own
   * parsed edge combinators (direct child vs descendant). */
  const char* css = ".panel { & > button, & label { color: red; } }";
  my_css_error_t error = {0};
  my_css_sheet_t* sheet = my_css_parse_ex(
      NULL, css, strlen(css), MY_CSS_PARSE_STRICT_AT_RULES, &error);
  const my_css_rule_t* rule;
  my_theme_t* theme = my_theme_create(NULL);
  my_widget_t* panel = my_widget_create(NULL, "panel");
  my_widget_t* hit = my_widget_create(NULL, "hit");
  my_widget_t* mid = my_widget_create(NULL, "mid");
  my_widget_t* deep = my_widget_create(NULL, "deep");
  my_widget_t* wrap = my_widget_create(NULL, "wrap");
  my_widget_t* miss = my_widget_create(NULL, "miss");
  const my_value_t* value;

  ASSERT_NOT_NULL(sheet);
  ASSERT_EQ(my_css_rule_count(sheet), 2u);
  rule = my_css_rule(sheet, 1u);
  ASSERT_NOT_NULL(rule);
  ASSERT_EQ(my_css_selector_count(rule), 2u);
  ASSERT_STR_EQ(my_css_selector(rule, 0u)->widget_type, "button");
  ASSERT_EQ(my_css_selector(rule, 0u)->ancestor_count, 1u);
  ASSERT_STR_EQ(my_css_selector(rule, 0u)->ancestors[0].style_class,
                "panel");
  ASSERT_TRUE(my_css_selector(rule, 0u)->ancestor_direct_path[0] == true);
  ASSERT_STR_EQ(my_css_selector(rule, 1u)->widget_type, "label");
  ASSERT_EQ(my_css_selector(rule, 1u)->ancestor_count, 1u);
  ASSERT_STR_EQ(my_css_selector(rule, 1u)->ancestors[0].style_class, "panel");
  ASSERT_TRUE(my_css_selector(rule, 1u)->ancestor_direct_path[0] == false);
  my_css_sheet_destroy(sheet);

  ASSERT_NOT_NULL(theme);
  panel->widget_type = "panel";
  hit->widget_type = "button";
  mid->widget_type = "wrap";
  deep->widget_type = "label";
  wrap->widget_type = "wrap";
  miss->widget_type = "button";
  ASSERT_EQ(my_widget_set_style_class(panel, "panel"), MY_RET_OK);
  ASSERT_EQ(my_widget_add_child(panel, hit), MY_RET_OK);
  ASSERT_EQ(my_widget_add_child(panel, mid), MY_RET_OK);
  ASSERT_EQ(my_widget_add_child(mid, deep), MY_RET_OK);
  ASSERT_EQ(my_widget_add_child(wrap, miss), MY_RET_OK);
  ASSERT_EQ(my_theme_load_css_ex(theme, css, MY_CSS_PARSE_STRICT_AT_RULES),
            MY_RET_OK);
  value = my_theme_get_for_widget(theme, hit, MY_STATE_NORMAL, "fg_color");
  ASSERT_NOT_NULL(value);
  ASSERT_EQ(my_value_get_uint32(value), 0xFF0000FFu);
  value = my_theme_get_for_widget(theme, deep, MY_STATE_NORMAL, "fg_color");
  ASSERT_NOT_NULL(value);
  ASSERT_EQ(my_value_get_uint32(value), 0xFF0000FFu);
  value = my_theme_get_for_widget(theme, miss, MY_STATE_NORMAL, "fg_color");
  ASSERT_TRUE(value == NULL);
  my_widget_unref(miss);
  my_widget_unref(wrap);
  my_widget_unref(deep);
  my_widget_unref(mid);
  my_widget_unref(hit);
  my_widget_unref(panel);
  my_theme_destroy(theme);
}

TEST(css_nest_group_cross_product_with_parent_group)
{
  /* `.a, .b { &:hover, &.on { color: red; } }` — arms x parent variants. */
  const char* css = ".a, .b { &:hover, &.on { color: red; } }";
  my_css_error_t error = {0};
  my_css_sheet_t* sheet = my_css_parse_ex(
      NULL, css, strlen(css), MY_CSS_PARSE_STRICT_AT_RULES, &error);
  const my_css_rule_t* rule;
  my_theme_t* theme = my_theme_create(NULL);
  my_widget_t* a = my_widget_create(NULL, "a");
  my_widget_t* b = my_widget_create(NULL, "b");
  const my_value_t* value;

  ASSERT_NOT_NULL(sheet);
  ASSERT_EQ(my_css_rule_count(sheet), 2u);
  rule = my_css_rule(sheet, 1u);
  ASSERT_NOT_NULL(rule);
  /* arm-major order: (&:hover x a,b) then (&.on x a,b). */
  ASSERT_EQ(my_css_selector_count(rule), 4u);
  ASSERT_STR_EQ(my_css_selector(rule, 0u)->style_class, "a");
  ASSERT_EQ(my_css_selector(rule, 0u)->state, (int32_t)MY_STATE_HOVER);
  ASSERT_STR_EQ(my_css_selector(rule, 1u)->style_class, "b");
  ASSERT_EQ(my_css_selector(rule, 1u)->state, (int32_t)MY_STATE_HOVER);
  ASSERT_STR_EQ(my_css_selector(rule, 2u)->style_class, "a on");
  ASSERT_EQ(my_css_selector(rule, 2u)->state, -1);
  ASSERT_STR_EQ(my_css_selector(rule, 3u)->style_class, "b on");
  ASSERT_EQ(my_css_selector(rule, 3u)->state, -1);
  my_css_sheet_destroy(sheet);

  ASSERT_NOT_NULL(theme);
  a->widget_type = "wrap";
  b->widget_type = "wrap";
  ASSERT_EQ(my_widget_set_style_class(a, "a"), MY_RET_OK);
  ASSERT_EQ(my_widget_set_style_class(b, "b on"), MY_RET_OK);
  ASSERT_EQ(my_theme_load_css_ex(theme, css, MY_CSS_PARSE_STRICT_AT_RULES),
            MY_RET_OK);
  value = my_theme_get_for_widget(theme, a, MY_STATE_HOVER, "fg_color");
  ASSERT_NOT_NULL(value);
  ASSERT_EQ(my_value_get_uint32(value), 0xFF0000FFu);
  value = my_theme_get_for_widget(theme, a, MY_STATE_NORMAL, "fg_color");
  ASSERT_TRUE(value == NULL);
  value = my_theme_get_for_widget(theme, b, MY_STATE_NORMAL, "fg_color");
  ASSERT_NOT_NULL(value);
  ASSERT_EQ(my_value_get_uint32(value), 0xFF0000FFu);
  my_widget_unref(b);
  my_widget_unref(a);
  my_theme_destroy(theme);
}

TEST(css_nest_group_rejects_malformed)
{
  const char* malformed[] = {
      "button { &:hover, { color: red; } }",   /* trailing comma: empty arm */
      "button { &:hover,, &:pressed { color: red; } }", /* double comma */
      "button { &:hover, .x { color: red; } }",         /* arm without & */
      "button { &,&,&,&,&,&,&,&,& { color: red; } }"};  /* 9 arms > cap */
  my_css_error_t error = {0};
  size_t i;

  for (i = 0u; i < sizeof(malformed) / sizeof(malformed[0]); ++i) {
    memset(&error, 0, sizeof(error));
    ASSERT_TRUE(my_css_parse_ex(NULL, malformed[i], strlen(malformed[i]),
                                MY_CSS_PARSE_STRICT_AT_RULES,
                                &error) == NULL);
    ASSERT_EQ(error.code, MY_CSS_ERROR_SYNTAX);
    ASSERT_EQ(error.capability, (uint32_t)MY_CSS_FEATURE_NESTING);
  }

  /* a leading comma never reaches the nested-rule parser: the statement
   * starts with ',' and dies as a declaration-syntax error instead. */
  memset(&error, 0, sizeof(error));
  ASSERT_TRUE(my_css_parse_ex(NULL, "button { , &:hover { color: red; } }",
                              strlen("button { , &:hover { color: red; } }"),
                              MY_CSS_PARSE_STRICT_AT_RULES, &error) == NULL);
  ASSERT_EQ(error.code, MY_CSS_ERROR_SYNTAX);
}

TEST(css_nest_second_level_descendant_chain)
{
  /* `.a { color: blue; & .b { color: green; & .c { color: red; } } }` —
   * two nesting levels desugar recursively; the sheet order is parent,
   * outer nested, inner nested (the inner rule sorts after its ancestor
   * nested rule, matching the fully-desugared source order). */
  const char* css =
      ".a { color: blue; & .b { color: green; & .c { color: red; } } }";
  my_css_error_t error = {0};
  my_css_sheet_t* sheet = my_css_parse_ex(
      NULL, css, strlen(css), MY_CSS_PARSE_STRICT_AT_RULES, &error);
  const my_css_selector_t* sel;
  my_theme_t* theme = my_theme_create(NULL);
  my_widget_t* a = my_widget_create(NULL, "a");
  my_widget_t* b = my_widget_create(NULL, "b");
  my_widget_t* hit = my_widget_create(NULL, "hit");
  my_widget_t* miss = my_widget_create(NULL, "miss");
  const my_value_t* value;

  ASSERT_NOT_NULL(sheet);
  ASSERT_EQ(my_css_rule_count(sheet), 3u);
  /* rule 1 = `.a .b`, rule 2 = `.a .b .c` (inner after outer). */
  sel = my_css_selector(my_css_rule(sheet, 1u), 0u);
  ASSERT_NOT_NULL(sel);
  ASSERT_STR_EQ(sel->style_class, "b");
  ASSERT_EQ(sel->ancestor_count, 1u);
  ASSERT_STR_EQ(sel->ancestors[0].style_class, "a");
  sel = my_css_selector(my_css_rule(sheet, 2u), 0u);
  ASSERT_NOT_NULL(sel);
  ASSERT_STR_EQ(sel->style_class, "c");
  ASSERT_EQ(sel->ancestor_count, 2u);
  ASSERT_STR_EQ(sel->ancestors[0].style_class, "b");
  ASSERT_STR_EQ(sel->ancestors[1].style_class, "a");
  ASSERT_TRUE(sel->nest_ref == false);
  my_css_sheet_destroy(sheet);

  ASSERT_NOT_NULL(theme);
  a->widget_type = "panel";
  b->widget_type = "wrap";
  hit->widget_type = "wrap";
  miss->widget_type = "wrap";
  ASSERT_EQ(my_widget_set_style_class(a, "a"), MY_RET_OK);
  ASSERT_EQ(my_widget_set_style_class(b, "b"), MY_RET_OK);
  ASSERT_EQ(my_widget_set_style_class(hit, "c"), MY_RET_OK);
  ASSERT_EQ(my_widget_set_style_class(miss, "c"), MY_RET_OK);
  ASSERT_EQ(my_widget_add_child(a, b), MY_RET_OK);
  ASSERT_EQ(my_widget_add_child(b, hit), MY_RET_OK);
  ASSERT_EQ(my_widget_add_child(a, miss), MY_RET_OK);
  ASSERT_EQ(my_theme_load_css_ex(theme, css, MY_CSS_PARSE_STRICT_AT_RULES),
            MY_RET_OK);
  value = my_theme_get_for_widget(theme, hit, MY_STATE_NORMAL, "fg_color");
  ASSERT_NOT_NULL(value);
  ASSERT_EQ(my_value_get_uint32(value), 0xFF0000FFu);
  value = my_theme_get_for_widget(theme, b, MY_STATE_NORMAL, "fg_color");
  ASSERT_NOT_NULL(value);
  ASSERT_EQ(my_value_get_uint32(value), 0x008000FFu);
  value = my_theme_get_for_widget(theme, a, MY_STATE_NORMAL, "fg_color");
  ASSERT_NOT_NULL(value);
  ASSERT_EQ(my_value_get_uint32(value), 0x0000FFFFu);
  value = my_theme_get_for_widget(theme, miss, MY_STATE_NORMAL, "fg_color");
  ASSERT_TRUE(value == NULL);
  my_widget_unref(miss);
  my_widget_unref(hit);
  my_widget_unref(b);
  my_widget_unref(a);
  my_theme_destroy(theme);
}

TEST(css_nest_second_level_subject_merge)
{
  /* `button { &.on { color: green; &:hover { color: red; } } }` — the
   * second level merges state onto the already-merged first level. */
  const char* css =
      "button { &.on { color: green; &:hover { color: red; } } }";
  my_css_error_t error = {0};
  my_css_sheet_t* sheet = my_css_parse_ex(
      NULL, css, strlen(css), MY_CSS_PARSE_STRICT_AT_RULES, &error);
  const my_css_selector_t* sel;
  my_theme_t* theme = my_theme_create(NULL);
  my_widget_t* btn = my_widget_create(NULL, "btn");
  my_widget_t* plain = my_widget_create(NULL, "plain");
  const my_value_t* value;

  ASSERT_NOT_NULL(sheet);
  ASSERT_EQ(my_css_rule_count(sheet), 3u);
  sel = my_css_selector(my_css_rule(sheet, 1u), 0u);
  ASSERT_NOT_NULL(sel);
  ASSERT_STR_EQ(sel->widget_type, "button");
  ASSERT_STR_EQ(sel->style_class, "on");
  ASSERT_EQ(sel->state, -1);
  sel = my_css_selector(my_css_rule(sheet, 2u), 0u);
  ASSERT_NOT_NULL(sel);
  ASSERT_STR_EQ(sel->widget_type, "button");
  ASSERT_STR_EQ(sel->style_class, "on");
  ASSERT_EQ(sel->state, (int32_t)MY_STATE_HOVER);
  ASSERT_EQ(sel->ancestor_count, 0u);
  my_css_sheet_destroy(sheet);

  ASSERT_NOT_NULL(theme);
  btn->widget_type = "button";
  plain->widget_type = "button";
  ASSERT_EQ(my_widget_set_style_class(btn, "on"), MY_RET_OK);
  ASSERT_EQ(my_theme_load_css_ex(theme, css, MY_CSS_PARSE_STRICT_AT_RULES),
            MY_RET_OK);
  value = my_theme_get_for_widget(theme, btn, MY_STATE_HOVER, "fg_color");
  ASSERT_NOT_NULL(value);
  ASSERT_EQ(my_value_get_uint32(value), 0xFF0000FFu);
  value = my_theme_get_for_widget(theme, btn, MY_STATE_NORMAL, "fg_color");
  ASSERT_NOT_NULL(value);
  ASSERT_EQ(my_value_get_uint32(value), 0x008000FFu);
  value = my_theme_get_for_widget(theme, plain, MY_STATE_HOVER, "fg_color");
  ASSERT_TRUE(value == NULL);
  my_widget_unref(plain);
  my_widget_unref(btn);
  my_theme_destroy(theme);
}

TEST(css_nest_second_level_group_arms)
{
  /* `.a { & .b { &:hover, &:pressed { color: red; } } }` — arm groups work
   * at the second level too, merging each state onto the outer desugared
   * form. */
  const char* css =
      ".a { & .b { &:hover, &:pressed { color: red; } } }";
  my_css_error_t error = {0};
  my_css_sheet_t* sheet = my_css_parse_ex(
      NULL, css, strlen(css), MY_CSS_PARSE_STRICT_AT_RULES, &error);
  const my_css_rule_t* rule;
  my_theme_t* theme = my_theme_create(NULL);
  my_widget_t* a = my_widget_create(NULL, "a");
  my_widget_t* b = my_widget_create(NULL, "b");
  const my_value_t* value;

  ASSERT_NOT_NULL(sheet);
  ASSERT_EQ(my_css_rule_count(sheet), 3u);
  rule = my_css_rule(sheet, 2u);
  ASSERT_NOT_NULL(rule);
  ASSERT_EQ(my_css_selector_count(rule), 2u);
  ASSERT_STR_EQ(my_css_selector(rule, 0u)->style_class, "b");
  ASSERT_EQ(my_css_selector(rule, 0u)->state, (int32_t)MY_STATE_HOVER);
  ASSERT_EQ(my_css_selector(rule, 0u)->ancestor_count, 1u);
  ASSERT_STR_EQ(my_css_selector(rule, 0u)->ancestors[0].style_class, "a");
  ASSERT_STR_EQ(my_css_selector(rule, 1u)->style_class, "b");
  ASSERT_EQ(my_css_selector(rule, 1u)->state, (int32_t)MY_STATE_PRESSED);
  ASSERT_STR_EQ(my_css_selector(rule, 1u)->ancestors[0].style_class, "a");
  my_css_sheet_destroy(sheet);

  ASSERT_NOT_NULL(theme);
  a->widget_type = "panel";
  b->widget_type = "wrap";
  ASSERT_EQ(my_widget_set_style_class(a, "a"), MY_RET_OK);
  ASSERT_EQ(my_widget_set_style_class(b, "b"), MY_RET_OK);
  ASSERT_EQ(my_widget_add_child(a, b), MY_RET_OK);
  ASSERT_EQ(my_theme_load_css_ex(theme, css, MY_CSS_PARSE_STRICT_AT_RULES),
            MY_RET_OK);
  value = my_theme_get_for_widget(theme, b, MY_STATE_HOVER, "fg_color");
  ASSERT_NOT_NULL(value);
  ASSERT_EQ(my_value_get_uint32(value), 0xFF0000FFu);
  value = my_theme_get_for_widget(theme, b, MY_STATE_PRESSED, "fg_color");
  ASSERT_NOT_NULL(value);
  ASSERT_EQ(my_value_get_uint32(value), 0xFF0000FFu);
  value = my_theme_get_for_widget(theme, b, MY_STATE_NORMAL, "fg_color");
  ASSERT_TRUE(value == NULL);
  my_widget_unref(b);
  my_widget_unref(a);
  my_theme_destroy(theme);
}

TEST(css_nest_second_level_sibling_order)
{
  /* `panel { & .a { & .b { color: red; } } & .c { color: green; } }` — a
   * second-level rule and a following first-level sibling: sheet order is
   * panel, panel .a, panel .a .b, panel .c (the inner rule lands before
   * the later sibling but after its own ancestor rule). */
  const char* css =
      "panel { & .a { & .b { color: red; } } & .c { color: green; } }";
  my_css_error_t error = {0};
  my_css_sheet_t* sheet = my_css_parse_ex(
      NULL, css, strlen(css), MY_CSS_PARSE_STRICT_AT_RULES, &error);
  const my_css_selector_t* sel;

  ASSERT_NOT_NULL(sheet);
  ASSERT_EQ(my_css_rule_count(sheet), 4u);
  sel = my_css_selector(my_css_rule(sheet, 1u), 0u);
  ASSERT_NOT_NULL(sel);
  ASSERT_STR_EQ(sel->style_class, "a");
  ASSERT_EQ(sel->ancestor_count, 1u);
  ASSERT_STR_EQ(sel->ancestors[0].widget_type, "panel");
  sel = my_css_selector(my_css_rule(sheet, 2u), 0u);
  ASSERT_NOT_NULL(sel);
  ASSERT_STR_EQ(sel->style_class, "b");
  ASSERT_EQ(sel->ancestor_count, 2u);
  ASSERT_STR_EQ(sel->ancestors[0].style_class, "a");
  ASSERT_STR_EQ(sel->ancestors[1].widget_type, "panel");
  sel = my_css_selector(my_css_rule(sheet, 3u), 0u);
  ASSERT_NOT_NULL(sel);
  ASSERT_STR_EQ(sel->style_class, "c");
  ASSERT_EQ(sel->ancestor_count, 1u);
  ASSERT_STR_EQ(sel->ancestors[0].widget_type, "panel");
  my_css_sheet_destroy(sheet);
}

TEST(css_nest_second_level_rejects_malformed)
{
  const char* malformed[] = {
      /* a state-qualified parent can't become an ancestor */
      "button { &:hover { & .x { color: red; } } }",
      /* a state-qualified marker in ancestor form can't be expressed */
      "button { &.on { &:hover .x { color: red; } } }"};
  my_css_error_t error = {0};
  size_t i;

  for (i = 0u; i < sizeof(malformed) / sizeof(malformed[0]); ++i) {
    memset(&error, 0, sizeof(error));
    ASSERT_TRUE(my_css_parse_ex(NULL, malformed[i], strlen(malformed[i]),
                                MY_CSS_PARSE_STRICT_AT_RULES,
                                &error) == NULL);
    ASSERT_EQ(error.code, MY_CSS_ERROR_SYNTAX);
    ASSERT_EQ(error.capability, (uint32_t)MY_CSS_FEATURE_NESTING);
  }
}

TEST(css_nest_marker_trailing_subject_form)
{
  /* `.card { .theme-dark & { color: red; } }` — the marker may sit at the
   * subject slot with arm compounds before it: the parent subject stays
   * the subject, the arm compounds become its innermost ancestors. This
   * is the canonical "theme ancestor" pattern. */
  const char* css = ".card { .theme-dark & { color: red; } }";
  /* a state-qualified parent stays legal here — it remains the subject. */
  const char* css2 = "button:hover { .a & { color: red; } }";
  my_css_error_t error = {0};
  my_css_sheet_t* sheet = my_css_parse_ex(
      NULL, css, strlen(css), MY_CSS_PARSE_STRICT_AT_RULES, &error);
  const my_css_selector_t* sel;
  my_theme_t* theme = my_theme_create(NULL);
  my_widget_t* dark = my_widget_create(NULL, "dark");
  my_widget_t* card = my_widget_create(NULL, "card");
  my_widget_t* plain = my_widget_create(NULL, "plain");
  my_widget_t* miss = my_widget_create(NULL, "miss");
  const my_value_t* value;

  ASSERT_NOT_NULL(sheet);
  ASSERT_EQ(my_css_rule_count(sheet), 2u);
  sel = my_css_selector(my_css_rule(sheet, 1u), 0u);
  ASSERT_NOT_NULL(sel);
  ASSERT_STR_EQ(sel->style_class, "card");
  ASSERT_EQ(sel->ancestor_count, 1u);
  ASSERT_STR_EQ(sel->ancestors[0].style_class, "theme-dark");
  ASSERT_TRUE(sel->ancestor_direct_path[0] == false);
  ASSERT_TRUE(sel->nest_ref == false);
  my_css_sheet_destroy(sheet);

  sheet = my_css_parse_ex(NULL, css2, strlen(css2),
                          MY_CSS_PARSE_STRICT_AT_RULES, &error);
  ASSERT_NOT_NULL(sheet);
  sel = my_css_selector(my_css_rule(sheet, 1u), 0u);
  ASSERT_NOT_NULL(sel);
  ASSERT_STR_EQ(sel->widget_type, "button");
  ASSERT_EQ(sel->state, (int32_t)MY_STATE_HOVER);
  ASSERT_EQ(sel->ancestor_count, 1u);
  ASSERT_STR_EQ(sel->ancestors[0].style_class, "a");
  my_css_sheet_destroy(sheet);

  ASSERT_NOT_NULL(theme);
  dark->widget_type = "panel";
  card->widget_type = "wrap";
  plain->widget_type = "panel";
  miss->widget_type = "wrap";
  ASSERT_EQ(my_widget_set_style_class(dark, "theme-dark"), MY_RET_OK);
  ASSERT_EQ(my_widget_set_style_class(card, "card"), MY_RET_OK);
  ASSERT_EQ(my_widget_set_style_class(miss, "card"), MY_RET_OK);
  ASSERT_EQ(my_widget_add_child(dark, card), MY_RET_OK);
  ASSERT_EQ(my_widget_add_child(plain, miss), MY_RET_OK);
  ASSERT_EQ(my_theme_load_css_ex(theme, css, MY_CSS_PARSE_STRICT_AT_RULES),
            MY_RET_OK);
  value = my_theme_get_for_widget(theme, card, MY_STATE_NORMAL, "fg_color");
  ASSERT_NOT_NULL(value);
  ASSERT_EQ(my_value_get_uint32(value), 0xFF0000FFu);
  value = my_theme_get_for_widget(theme, miss, MY_STATE_NORMAL, "fg_color");
  ASSERT_TRUE(value == NULL);
  my_widget_unref(miss);
  my_widget_unref(plain);
  my_widget_unref(card);
  my_widget_unref(dark);
  my_theme_destroy(theme);
}

TEST(css_nest_marker_trailing_parent_ancestors_shift)
{
  /* `panel item { .x > & { color: red; } }` — the arm's outward edge binds
   * the parent's OUTERMOST compound: `.x > panel item`. The parent's own
   * ancestors shift outward past the inserted arm compounds. (Top-level
   * ancestors must carry a type, hence `panel item`.) */
  const char* css = "panel item { .x > & { color: red; } }";
  my_css_error_t error = {0};
  my_css_sheet_t* sheet = my_css_parse_ex(
      NULL, css, strlen(css), MY_CSS_PARSE_STRICT_AT_RULES, &error);
  const my_css_selector_t* sel;
  my_theme_t* theme = my_theme_create(NULL);
  my_widget_t* x = my_widget_create(NULL, "x");
  my_widget_t* pa = my_widget_create(NULL, "pa");
  my_widget_t* hit = my_widget_create(NULL, "hit");
  my_widget_t* mid = my_widget_create(NULL, "mid");
  my_widget_t* pa2 = my_widget_create(NULL, "pa2");
  my_widget_t* miss = my_widget_create(NULL, "miss");
  const my_value_t* value;

  ASSERT_NOT_NULL(sheet);
  ASSERT_EQ(my_css_rule_count(sheet), 2u);
  sel = my_css_selector(my_css_rule(sheet, 1u), 0u);
  ASSERT_NOT_NULL(sel);
  ASSERT_STR_EQ(sel->widget_type, "item");
  ASSERT_EQ(sel->ancestor_count, 2u);
  ASSERT_STR_EQ(sel->ancestors[0].widget_type, "panel");
  ASSERT_TRUE(sel->ancestor_direct_path[0] == false);
  ASSERT_STR_EQ(sel->ancestors[1].style_class, "x");
  ASSERT_TRUE(sel->ancestor_direct_path[1] == true);
  my_css_sheet_destroy(sheet);

  ASSERT_NOT_NULL(theme);
  x->widget_type = "wrap";
  pa->widget_type = "panel";
  hit->widget_type = "item";
  mid->widget_type = "wrap";
  pa2->widget_type = "panel";
  miss->widget_type = "item";
  ASSERT_EQ(my_widget_set_style_class(x, "x"), MY_RET_OK);
  ASSERT_EQ(my_widget_add_child(x, pa), MY_RET_OK);
  ASSERT_EQ(my_widget_add_child(pa, hit), MY_RET_OK);
  ASSERT_EQ(my_widget_add_child(x, mid), MY_RET_OK);
  ASSERT_EQ(my_widget_add_child(mid, pa2), MY_RET_OK);
  ASSERT_EQ(my_widget_add_child(pa2, miss), MY_RET_OK);
  ASSERT_EQ(my_theme_load_css_ex(theme, css, MY_CSS_PARSE_STRICT_AT_RULES),
            MY_RET_OK);
  value = my_theme_get_for_widget(theme, hit, MY_STATE_NORMAL, "fg_color");
  ASSERT_NOT_NULL(value);
  ASSERT_EQ(my_value_get_uint32(value), 0xFF0000FFu);
  /* x > mid > pa2 > miss: the direct edge between x and panel is broken. */
  value = my_theme_get_for_widget(theme, miss, MY_STATE_NORMAL, "fg_color");
  ASSERT_TRUE(value == NULL);
  my_widget_unref(miss);
  my_widget_unref(pa2);
  my_widget_unref(mid);
  my_widget_unref(hit);
  my_widget_unref(pa);
  my_widget_unref(x);
  my_theme_destroy(theme);
}

TEST(css_nest_marker_mid_chain)
{
  /* `wrap .a { .x & .y { color: red; } }` — the marker sits mid-chain: the
   * whole parent selector lands in its slot (parent ancestors travel with
   * it, outward of the parent subject but inward of the arm's outward
   * compounds): `.x wrap .a .y`. */
  const char* css = "wrap .a { .x & .y { color: red; } }";
  my_css_error_t error = {0};
  my_css_sheet_t* sheet = my_css_parse_ex(
      NULL, css, strlen(css), MY_CSS_PARSE_STRICT_AT_RULES, &error);
  const my_css_selector_t* sel;
  my_theme_t* theme = my_theme_create(NULL);
  my_widget_t* x = my_widget_create(NULL, "x");
  my_widget_t* w = my_widget_create(NULL, "w");
  my_widget_t* a = my_widget_create(NULL, "a");
  my_widget_t* hit = my_widget_create(NULL, "hit");
  my_widget_t* w2 = my_widget_create(NULL, "w2");
  my_widget_t* a2 = my_widget_create(NULL, "a2");
  my_widget_t* miss = my_widget_create(NULL, "miss");
  const my_value_t* value;

  ASSERT_NOT_NULL(sheet);
  ASSERT_EQ(my_css_rule_count(sheet), 2u);
  sel = my_css_selector(my_css_rule(sheet, 1u), 0u);
  ASSERT_NOT_NULL(sel);
  ASSERT_STR_EQ(sel->style_class, "y");
  ASSERT_EQ(sel->ancestor_count, 3u);
  ASSERT_STR_EQ(sel->ancestors[0].style_class, "a");
  ASSERT_STR_EQ(sel->ancestors[1].widget_type, "wrap");
  ASSERT_STR_EQ(sel->ancestors[2].style_class, "x");
  ASSERT_TRUE(sel->ancestor_direct_path[0] == false);
  ASSERT_TRUE(sel->ancestor_direct_path[2] == false);
  my_css_sheet_destroy(sheet);

  ASSERT_NOT_NULL(theme);
  x->widget_type = "panel";
  w->widget_type = "wrap";
  a->widget_type = "box";
  hit->widget_type = "box";
  w2->widget_type = "wrap";
  a2->widget_type = "box";
  miss->widget_type = "box";
  ASSERT_EQ(my_widget_set_style_class(x, "x"), MY_RET_OK);
  ASSERT_EQ(my_widget_set_style_class(a, "a"), MY_RET_OK);
  ASSERT_EQ(my_widget_set_style_class(hit, "y"), MY_RET_OK);
  ASSERT_EQ(my_widget_set_style_class(a2, "a"), MY_RET_OK);
  ASSERT_EQ(my_widget_set_style_class(miss, "y"), MY_RET_OK);
  ASSERT_EQ(my_widget_add_child(x, w), MY_RET_OK);
  ASSERT_EQ(my_widget_add_child(w, a), MY_RET_OK);
  ASSERT_EQ(my_widget_add_child(a, hit), MY_RET_OK);
  ASSERT_EQ(my_widget_add_child(w2, a2), MY_RET_OK);
  ASSERT_EQ(my_widget_add_child(a2, miss), MY_RET_OK);
  ASSERT_EQ(my_theme_load_css_ex(theme, css, MY_CSS_PARSE_STRICT_AT_RULES),
            MY_RET_OK);
  value = my_theme_get_for_widget(theme, hit, MY_STATE_NORMAL, "fg_color");
  ASSERT_NOT_NULL(value);
  ASSERT_EQ(my_value_get_uint32(value), 0xFF0000FFu);
  /* no .x above the chain: the outward arm compound is required. */
  value = my_theme_get_for_widget(theme, miss, MY_STATE_NORMAL, "fg_color");
  ASSERT_TRUE(value == NULL);
  my_widget_unref(miss);
  my_widget_unref(a2);
  my_widget_unref(w2);
  my_widget_unref(hit);
  my_widget_unref(a);
  my_widget_unref(w);
  my_widget_unref(x);
  my_theme_destroy(theme);
}

TEST(css_nest_marker_mid_chain_direct_edges)
{
  /* `.a { .x > & > .y { color: red; } }` — both parsed edges of the arm
   * are kept: the inward edge lands on the parent-subject slot, the
   * outward edge on the outward arm compound. */
  const char* css = ".a { .x > & > .y { color: red; } }";
  my_css_error_t error = {0};
  my_css_sheet_t* sheet = my_css_parse_ex(
      NULL, css, strlen(css), MY_CSS_PARSE_STRICT_AT_RULES, &error);
  const my_css_selector_t* sel;
  my_theme_t* theme = my_theme_create(NULL);
  my_widget_t* x = my_widget_create(NULL, "x");
  my_widget_t* a = my_widget_create(NULL, "a");
  my_widget_t* hit = my_widget_create(NULL, "hit");
  my_widget_t* mid = my_widget_create(NULL, "mid");
  my_widget_t* a2 = my_widget_create(NULL, "a2");
  my_widget_t* miss = my_widget_create(NULL, "miss");
  const my_value_t* value;

  ASSERT_NOT_NULL(sheet);
  sel = my_css_selector(my_css_rule(sheet, 1u), 0u);
  ASSERT_NOT_NULL(sel);
  ASSERT_STR_EQ(sel->style_class, "y");
  ASSERT_EQ(sel->ancestor_count, 2u);
  ASSERT_STR_EQ(sel->ancestors[0].style_class, "a");
  ASSERT_TRUE(sel->ancestor_direct_path[0] == true);
  ASSERT_STR_EQ(sel->ancestors[1].style_class, "x");
  ASSERT_TRUE(sel->ancestor_direct_path[1] == true);
  my_css_sheet_destroy(sheet);

  ASSERT_NOT_NULL(theme);
  x->widget_type = "panel";
  a->widget_type = "wrap";
  hit->widget_type = "wrap";
  mid->widget_type = "wrap";
  a2->widget_type = "wrap";
  miss->widget_type = "wrap";
  ASSERT_EQ(my_widget_set_style_class(x, "x"), MY_RET_OK);
  ASSERT_EQ(my_widget_set_style_class(a, "a"), MY_RET_OK);
  ASSERT_EQ(my_widget_set_style_class(hit, "y"), MY_RET_OK);
  ASSERT_EQ(my_widget_set_style_class(a2, "a"), MY_RET_OK);
  ASSERT_EQ(my_widget_set_style_class(miss, "y"), MY_RET_OK);
  ASSERT_EQ(my_widget_add_child(x, a), MY_RET_OK);
  ASSERT_EQ(my_widget_add_child(a, hit), MY_RET_OK);
  ASSERT_EQ(my_widget_add_child(x, mid), MY_RET_OK);
  ASSERT_EQ(my_widget_add_child(mid, a2), MY_RET_OK);
  ASSERT_EQ(my_widget_add_child(a2, miss), MY_RET_OK);
  ASSERT_EQ(my_theme_load_css_ex(theme, css, MY_CSS_PARSE_STRICT_AT_RULES),
            MY_RET_OK);
  value = my_theme_get_for_widget(theme, hit, MY_STATE_NORMAL, "fg_color");
  ASSERT_NOT_NULL(value);
  ASSERT_EQ(my_value_get_uint32(value), 0xFF0000FFu);
  /* x > mid > a2 > miss: the direct edge between x and the parent is
   * broken. */
  value = my_theme_get_for_widget(theme, miss, MY_STATE_NORMAL, "fg_color");
  ASSERT_TRUE(value == NULL);
  my_widget_unref(miss);
  my_widget_unref(a2);
  my_widget_unref(mid);
  my_widget_unref(hit);
  my_widget_unref(a);
  my_widget_unref(x);
  my_theme_destroy(theme);
}

TEST(css_nest_marker_position_rejects_malformed)
{
  const char* malformed[] = {
      "button { .a & & { color: red; } }",           /* two markers */
      "button { & .a & { color: red; } }",           /* leading + trailing */
      "button { .a &:hover .x { color: red; } }",    /* state on mid marker */
      "button:hover { .a & .x { color: red; } }"};   /* state parent as
                                                        * mid ancestor */
  my_css_error_t error = {0};
  size_t i;

  for (i = 0u; i < sizeof(malformed) / sizeof(malformed[0]); ++i) {
    memset(&error, 0, sizeof(error));
    ASSERT_TRUE(my_css_parse_ex(NULL, malformed[i], strlen(malformed[i]),
                                MY_CSS_PARSE_STRICT_AT_RULES,
                                &error) == NULL);
    ASSERT_EQ(error.code, MY_CSS_ERROR_SYNTAX);
    ASSERT_EQ(error.capability, (uint32_t)MY_CSS_FEATURE_NESTING);
  }
}

TEST(css_nest_third_level_chains)
{
  /* `.a { & .b { & .c { & .d { color: red; } } } }` — three nesting
   * levels: the pending pre-push order keeps full desugared source order
   * at any depth. */
  const char* css =
      ".a { & .b { & .c { & .d { color: red; } } } }";
  my_css_error_t error = {0};
  my_css_sheet_t* sheet = my_css_parse_ex(
      NULL, css, strlen(css), MY_CSS_PARSE_STRICT_AT_RULES, &error);
  const my_css_selector_t* sel;
  my_theme_t* theme = my_theme_create(NULL);
  my_widget_t* a = my_widget_create(NULL, "a");
  my_widget_t* b = my_widget_create(NULL, "b");
  my_widget_t* c = my_widget_create(NULL, "c");
  my_widget_t* hit = my_widget_create(NULL, "hit");
  my_widget_t* a2 = my_widget_create(NULL, "a2");
  my_widget_t* b2 = my_widget_create(NULL, "b2");
  my_widget_t* miss = my_widget_create(NULL, "miss");
  const my_value_t* value;

  ASSERT_NOT_NULL(sheet);
  ASSERT_EQ(my_css_rule_count(sheet), 4u);
  sel = my_css_selector(my_css_rule(sheet, 1u), 0u);
  ASSERT_NOT_NULL(sel);
  ASSERT_STR_EQ(sel->style_class, "b");
  ASSERT_EQ(sel->ancestor_count, 1u);
  sel = my_css_selector(my_css_rule(sheet, 2u), 0u);
  ASSERT_NOT_NULL(sel);
  ASSERT_STR_EQ(sel->style_class, "c");
  ASSERT_EQ(sel->ancestor_count, 2u);
  sel = my_css_selector(my_css_rule(sheet, 3u), 0u);
  ASSERT_NOT_NULL(sel);
  ASSERT_STR_EQ(sel->style_class, "d");
  ASSERT_EQ(sel->ancestor_count, 3u);
  ASSERT_STR_EQ(sel->ancestors[0].style_class, "c");
  ASSERT_STR_EQ(sel->ancestors[1].style_class, "b");
  ASSERT_STR_EQ(sel->ancestors[2].style_class, "a");
  ASSERT_TRUE(sel->nest_ref == false);
  my_css_sheet_destroy(sheet);

  ASSERT_NOT_NULL(theme);
  a->widget_type = "panel";
  b->widget_type = "wrap";
  c->widget_type = "wrap";
  hit->widget_type = "wrap";
  a2->widget_type = "panel";
  b2->widget_type = "wrap";
  miss->widget_type = "wrap";
  ASSERT_EQ(my_widget_set_style_class(a, "a"), MY_RET_OK);
  ASSERT_EQ(my_widget_set_style_class(b, "b"), MY_RET_OK);
  ASSERT_EQ(my_widget_set_style_class(c, "c"), MY_RET_OK);
  ASSERT_EQ(my_widget_set_style_class(hit, "d"), MY_RET_OK);
  ASSERT_EQ(my_widget_set_style_class(a2, "a"), MY_RET_OK);
  ASSERT_EQ(my_widget_set_style_class(b2, "b"), MY_RET_OK);
  ASSERT_EQ(my_widget_set_style_class(miss, "d"), MY_RET_OK);
  ASSERT_EQ(my_widget_add_child(a, b), MY_RET_OK);
  ASSERT_EQ(my_widget_add_child(b, c), MY_RET_OK);
  ASSERT_EQ(my_widget_add_child(c, hit), MY_RET_OK);
  ASSERT_EQ(my_widget_add_child(a2, b2), MY_RET_OK);
  ASSERT_EQ(my_widget_add_child(b2, miss), MY_RET_OK);
  ASSERT_EQ(my_theme_load_css_ex(theme, css, MY_CSS_PARSE_STRICT_AT_RULES),
            MY_RET_OK);
  value = my_theme_get_for_widget(theme, hit, MY_STATE_NORMAL, "fg_color");
  ASSERT_NOT_NULL(value);
  ASSERT_EQ(my_value_get_uint32(value), 0xFF0000FFu);
  /* a2 > b2 > miss: the .c level is missing from the chain. */
  value = my_theme_get_for_widget(theme, miss, MY_STATE_NORMAL, "fg_color");
  ASSERT_TRUE(value == NULL);
  my_widget_unref(miss);
  my_widget_unref(b2);
  my_widget_unref(a2);
  my_widget_unref(hit);
  my_widget_unref(c);
  my_widget_unref(b);
  my_widget_unref(a);
  my_theme_destroy(theme);
}

TEST(css_nest_third_level_mixed_subject_merges)
{
  /* `button { &.a { color: green; &.b { color: blue; &:hover { color: red;
   * } } } }` — subject merges compose through three levels. */
  const char* css =
      "button { &.a { color: green; &.b { color: blue;"
      " &:hover { color: red; } } } }";
  my_css_error_t error = {0};
  my_css_sheet_t* sheet = my_css_parse_ex(
      NULL, css, strlen(css), MY_CSS_PARSE_STRICT_AT_RULES, &error);
  const my_css_selector_t* sel;
  my_theme_t* theme = my_theme_create(NULL);
  my_widget_t* ab = my_widget_create(NULL, "ab");
  my_widget_t* only_a = my_widget_create(NULL, "only_a");
  const my_value_t* value;

  ASSERT_NOT_NULL(sheet);
  ASSERT_EQ(my_css_rule_count(sheet), 4u);
  sel = my_css_selector(my_css_rule(sheet, 2u), 0u);
  ASSERT_NOT_NULL(sel);
  ASSERT_STR_EQ(sel->widget_type, "button");
  ASSERT_STR_EQ(sel->style_class, "a b");
  ASSERT_EQ(sel->state, -1);
  sel = my_css_selector(my_css_rule(sheet, 3u), 0u);
  ASSERT_NOT_NULL(sel);
  ASSERT_STR_EQ(sel->style_class, "a b");
  ASSERT_EQ(sel->state, (int32_t)MY_STATE_HOVER);
  my_css_sheet_destroy(sheet);

  ASSERT_NOT_NULL(theme);
  ab->widget_type = "button";
  only_a->widget_type = "button";
  ASSERT_EQ(my_widget_set_style_class(ab, "a b"), MY_RET_OK);
  ASSERT_EQ(my_widget_set_style_class(only_a, "a"), MY_RET_OK);
  ASSERT_EQ(my_theme_load_css_ex(theme, css, MY_CSS_PARSE_STRICT_AT_RULES),
            MY_RET_OK);
  value = my_theme_get_for_widget(theme, ab, MY_STATE_HOVER, "fg_color");
  ASSERT_NOT_NULL(value);
  ASSERT_EQ(my_value_get_uint32(value), 0xFF0000FFu);
  value = my_theme_get_for_widget(theme, ab, MY_STATE_NORMAL, "fg_color");
  ASSERT_NOT_NULL(value);
  ASSERT_EQ(my_value_get_uint32(value), 0x0000FFFFu);
  value = my_theme_get_for_widget(theme, only_a, MY_STATE_NORMAL, "fg_color");
  ASSERT_NOT_NULL(value);
  ASSERT_EQ(my_value_get_uint32(value), 0x008000FFu);
  value = my_theme_get_for_widget(theme, only_a, MY_STATE_HOVER, "fg_color");
  /* the hover rule needs class b; only_a falls back to the `&.a` rule. */
  ASSERT_NOT_NULL(value);
  ASSERT_EQ(my_value_get_uint32(value), 0x008000FFu);
  my_widget_unref(only_a);
  my_widget_unref(ab);
  my_theme_destroy(theme);
}

TEST(css_nest_fourth_level_rejects)
{
  const char* css = "a { & b { & c { & d { & e { color: red; } } } } }";
  my_css_error_t error = {0};

  ASSERT_TRUE(my_css_parse_ex(NULL, css, strlen(css),
                              MY_CSS_PARSE_STRICT_AT_RULES, &error) == NULL);
  ASSERT_EQ(error.code, MY_CSS_ERROR_SYNTAX);
  ASSERT_EQ(error.capability, (uint32_t)MY_CSS_FEATURE_NESTING);
}

TEST(css_nest_media_merges_matching_declarations)
{
  /* `button { color: red; @media all { color: blue; } color: green; }` —
   * a conditional group nested in a rule evaluates at parse time; its
   * declarations append to the enclosing rule in source order (identical
   * selector, so within-rule order IS the spec's split-rule cascade). */
  const char* css =
      "button { color: red; @media all { color: blue; } color: green; }";
  my_css_error_t error = {0};
  my_css_sheet_t* sheet = my_css_parse_ex(
      NULL, css, strlen(css), MY_CSS_PARSE_STRICT_AT_RULES, &error);
  const my_css_rule_t* rule;
  my_theme_t* theme = my_theme_create(NULL);
  my_widget_t* btn = my_widget_create(NULL, "btn");
  const my_value_t* value;

  ASSERT_NOT_NULL(sheet);
  ASSERT_EQ(my_css_rule_count(sheet), 1u);
  rule = my_css_rule(sheet, 0u);
  ASSERT_NOT_NULL(rule);
  ASSERT_EQ(my_css_decl_count(rule), 3u);
  ASSERT_EQ(my_value_get_uint32(&my_css_decl(rule, 0u)->value), 0xFF0000FFu);
  ASSERT_EQ(my_value_get_uint32(&my_css_decl(rule, 1u)->value), 0x0000FFFFu);
  ASSERT_EQ(my_value_get_uint32(&my_css_decl(rule, 2u)->value), 0x008000FFu);
  my_css_sheet_destroy(sheet);

  ASSERT_NOT_NULL(theme);
  btn->widget_type = "button";
  ASSERT_EQ(my_theme_load_css_ex(theme, css, MY_CSS_PARSE_STRICT_AT_RULES),
            MY_RET_OK);
  value = my_theme_get_for_widget(theme, btn, MY_STATE_NORMAL, "fg_color");
  ASSERT_NOT_NULL(value);
  ASSERT_EQ(my_value_get_uint32(value), 0x008000FFu);
  my_widget_unref(btn);
  my_theme_destroy(theme);
}

TEST(css_nest_media_skips_non_matching)
{
  /* the same nested group disappears when its query fails: the enclosing
   * rule keeps only its own declarations. */
  const char* css =
      "button { color: red; @media (min-width: 800px) { color: blue; } }";
  my_css_media_context_t narrow = {640u, 480u, true, false, false, 0u};
  my_css_media_context_t wide = {1024u, 768u, true, false, false, 0u};
  my_css_error_t error = {0};
  my_css_sheet_t* sheet;

  sheet = my_css_parse_media_ex(NULL, css, strlen(css),
                                MY_CSS_PARSE_STRICT_AT_RULES, &narrow,
                                &error);
  ASSERT_NOT_NULL(sheet);
  ASSERT_EQ(my_css_rule_count(sheet), 1u);
  ASSERT_EQ(my_css_decl_count(my_css_rule(sheet, 0u)), 1u);
  ASSERT_EQ(my_value_get_uint32(
                &my_css_decl(my_css_rule(sheet, 0u), 0u)->value),
            0xFF0000FFu);
  my_css_sheet_destroy(sheet);

  memset(&error, 0, sizeof(error));
  sheet = my_css_parse_media_ex(NULL, css, strlen(css),
                                MY_CSS_PARSE_STRICT_AT_RULES, &wide, &error);
  ASSERT_NOT_NULL(sheet);
  ASSERT_EQ(my_css_decl_count(my_css_rule(sheet, 0u)), 2u);
  ASSERT_EQ(my_value_get_uint32(
                &my_css_decl(my_css_rule(sheet, 0u), 1u)->value),
            0x0000FFFFu);
  my_css_sheet_destroy(sheet);
}

TEST(css_nest_media_hosts_nested_rules)
{
  /* `&` rules inside a nested conditional desugar against the enclosing
   * rule, and a nested conditional inside a `&` rule's own block appends
   * to that nested rule. */
  const char* css =
      "button { color: green; @media all { &:hover { color: red; } } }";
  const char* css2 =
      "button { &:hover { @media all { color: red; } } }";
  const char* css3 =
      "button { color: green; @media (min-width: 800px) {"
      " &:hover { color: red; } } }";
  my_css_media_context_t narrow = {640u, 480u, true, false, false, 0u};
  my_css_error_t error = {0};
  my_css_sheet_t* sheet = my_css_parse_ex(
      NULL, css, strlen(css), MY_CSS_PARSE_STRICT_AT_RULES, &error);
  my_theme_t* theme = my_theme_create(NULL);
  my_widget_t* btn = my_widget_create(NULL, "btn");
  const my_value_t* value;

  ASSERT_NOT_NULL(sheet);
  ASSERT_EQ(my_css_rule_count(sheet), 2u);
  ASSERT_EQ(my_css_selector(my_css_rule(sheet, 1u), 0u)->state,
            (int32_t)MY_STATE_HOVER);
  my_css_sheet_destroy(sheet);

  sheet = my_css_parse_ex(NULL, css2, strlen(css2),
                          MY_CSS_PARSE_STRICT_AT_RULES, &error);
  ASSERT_NOT_NULL(sheet);
  ASSERT_EQ(my_css_rule_count(sheet), 2u);
  ASSERT_EQ(my_css_decl_count(my_css_rule(sheet, 1u)), 1u);
  my_css_sheet_destroy(sheet);

  sheet = my_css_parse_media_ex(NULL, css3, strlen(css3),
                                MY_CSS_PARSE_STRICT_AT_RULES, &narrow,
                                &error);
  ASSERT_NOT_NULL(sheet);
  ASSERT_EQ(my_css_rule_count(sheet), 1u);
  my_css_sheet_destroy(sheet);

  ASSERT_NOT_NULL(theme);
  btn->widget_type = "button";
  ASSERT_EQ(my_theme_load_css_ex(theme, css, MY_CSS_PARSE_STRICT_AT_RULES),
            MY_RET_OK);
  value = my_theme_get_for_widget(theme, btn, MY_STATE_HOVER, "fg_color");
  ASSERT_NOT_NULL(value);
  ASSERT_EQ(my_value_get_uint32(value), 0xFF0000FFu);
  value = my_theme_get_for_widget(theme, btn, MY_STATE_NORMAL, "fg_color");
  ASSERT_NOT_NULL(value);
  ASSERT_EQ(my_value_get_uint32(value), 0x008000FFu);
  my_widget_unref(btn);
  my_theme_destroy(theme);
}

TEST(css_nest_supports_in_rule)
{
  /* `button { color: green; @supports (color: red) { color: blue; } }` —
   * the condition evaluates against the parser's property registry;
   * unsupported conditions drop their block. */
  const char* css =
      "button { color: green; @supports (color: red) { color: blue; } }";
  const char* css2 =
      "button { color: green; @supports not (color: red) { color: blue; } }";
  const char* css3 =
      "button { @supports (color: red) { &:hover { color: red; } } }";
  my_css_error_t error = {0};
  my_css_sheet_t* sheet = my_css_parse_ex(
      NULL, css, strlen(css), MY_CSS_PARSE_STRICT_AT_RULES, &error);
  my_theme_t* theme = my_theme_create(NULL);
  my_widget_t* btn = my_widget_create(NULL, "btn");
  const my_value_t* value;

  ASSERT_NOT_NULL(sheet);
  ASSERT_EQ(my_css_rule_count(sheet), 1u);
  ASSERT_EQ(my_css_decl_count(my_css_rule(sheet, 0u)), 2u);
  my_css_sheet_destroy(sheet);

  sheet = my_css_parse_ex(NULL, css2, strlen(css2),
                          MY_CSS_PARSE_STRICT_AT_RULES, &error);
  ASSERT_NOT_NULL(sheet);
  ASSERT_EQ(my_css_decl_count(my_css_rule(sheet, 0u)), 1u);
  my_css_sheet_destroy(sheet);

  sheet = my_css_parse_ex(NULL, css3, strlen(css3),
                          MY_CSS_PARSE_STRICT_AT_RULES, &error);
  ASSERT_NOT_NULL(sheet);
  ASSERT_EQ(my_css_rule_count(sheet), 2u);
  ASSERT_EQ(my_css_selector(my_css_rule(sheet, 1u), 0u)->state,
            (int32_t)MY_STATE_HOVER);
  my_css_sheet_destroy(sheet);

  ASSERT_NOT_NULL(theme);
  btn->widget_type = "button";
  ASSERT_EQ(my_theme_load_css_ex(theme, css, MY_CSS_PARSE_STRICT_AT_RULES),
            MY_RET_OK);
  value = my_theme_get_for_widget(theme, btn, MY_STATE_NORMAL, "fg_color");
  ASSERT_NOT_NULL(value);
  ASSERT_EQ(my_value_get_uint32(value), 0x0000FFFFu);
  my_widget_unref(btn);
  my_theme_destroy(theme);
}

TEST(css_nest_conditional_rejects_malformed)
{
  /* the nested form shares the at-rule depth budget: four outer @media
   * plus one inside the rule exceeds MY_CSS_MAX_AT_RULE_NESTING. */
  const char* too_deep =
      "@media all { @media all { @media all { @media all {"
      " button { @media all { color: red; } } } } } }";
  /* strict mode: a malformed nested query rejects (not skip). */
  const char* bad_query = "button { @media (bogus) { color: red; } }";
  /* other @-rules reject with the dedicated nested-at-rule signature. */
  const char* unknown = "button { @layer x { color: red; } }";
  my_css_error_t error = {0};

  ASSERT_TRUE(my_css_parse_ex(NULL, too_deep, strlen(too_deep),
                              MY_CSS_PARSE_STRICT_AT_RULES, &error) == NULL);
  ASSERT_TRUE(error.msg[0] != '\0');

  memset(&error, 0, sizeof(error));
  ASSERT_TRUE(my_css_parse_ex(NULL, bad_query, strlen(bad_query),
                              MY_CSS_PARSE_STRICT_AT_RULES, &error) == NULL);
  ASSERT_EQ(error.code, MY_CSS_ERROR_UNSUPPORTED_FEATURE);

  memset(&error, 0, sizeof(error));
  ASSERT_TRUE(my_css_parse_ex(NULL, unknown, strlen(unknown),
                              MY_CSS_PARSE_STRICT_AT_RULES, &error) == NULL);
  ASSERT_EQ(error.code, MY_CSS_ERROR_UNSUPPORTED_FEATURE);
  ASSERT_EQ(error.capability, (uint32_t)MY_CSS_FEATURE_AT_RULES);
  ASSERT_STR_EQ(error.msg, "unsupported nested @-rule");
}

TEST(css_nest_non_conditional_at_rules_have_dedicated_signature)
{
  /* CSS Nesting admits only style rules and conditional group rules into a
   * declaration block; every other nested @-rule (even ones supported at
   * top level, like @layer/@scope) rejects with one truthful signature
   * instead of the misleading "expected declaration key". (@container was
   * in this list in R645; R663 made it a legal nested conditional group.) */
  const char* cases[] = {
      "button { @layer x { color: red; } }",
      "button { @scope (.x) { color: red; } }",
      "button { @font-face { font-family: x; } }",
      "button { color: blue; @layer x { color: red; } }"};
  my_css_error_t error = {0};
  size_t i;

  for (i = 0u; i < sizeof(cases) / sizeof(cases[0]); ++i) {
    memset(&error, 0, sizeof(error));
    ASSERT_TRUE(my_css_parse_ex(NULL, cases[i], strlen(cases[i]),
                                MY_CSS_PARSE_STRICT_AT_RULES,
                                &error) == NULL);
    ASSERT_EQ(error.code, MY_CSS_ERROR_UNSUPPORTED_FEATURE);
    ASSERT_EQ(error.capability, (uint32_t)MY_CSS_FEATURE_AT_RULES);
    ASSERT_STR_EQ(error.msg, "unsupported nested @-rule");
  }
  /* top-level @layer/@scope remain fully supported (guard). */
  {
    const char* css = "@layer x { button { color: red; } }";
    my_css_sheet_t* sheet;
    memset(&error, 0, sizeof(error));
    sheet = my_css_parse_ex(NULL, css, strlen(css),
                            MY_CSS_PARSE_STRICT_AT_RULES, &error);
    ASSERT_NOT_NULL(sheet);
    ASSERT_EQ(my_css_rule_count(sheet), 1u);
    my_css_sheet_destroy(sheet);
  }
}

TEST(css_scope_subject_state_form_styles_root)
{
  /* `@scope panel { :scope:hover { color: red; } :scope { color: blue; } }`
   * — one state qualifier may stack on `:scope`: the splice substitutes
   * the root subject and keeps the state, styling the root itself when
   * hovered. */
  const char* css =
      "@scope panel { :scope:hover { color: red; } :scope { color: blue; } }";
  my_css_error_t error = {0};
  my_css_sheet_t* sheet = my_css_parse_ex(
      NULL, css, strlen(css), MY_CSS_PARSE_STRICT_AT_RULES, &error);
  const my_css_selector_t* sel;
  my_theme_t* theme = my_theme_create(NULL);
  my_widget_t* panel = my_widget_create(NULL, "panel");
  my_widget_t* child = my_widget_create(NULL, "child");
  const my_value_t* value;

  ASSERT_NOT_NULL(sheet);
  ASSERT_EQ(my_css_rule_count(sheet), 2u);
  sel = my_css_selector(my_css_rule(sheet, 0u), 0u);
  ASSERT_NOT_NULL(sel);
  ASSERT_STR_EQ(sel->widget_type, "panel");
  ASSERT_EQ(sel->state, (int32_t)MY_STATE_HOVER);
  ASSERT_EQ(sel->ancestor_count, 0u);
  ASSERT_TRUE(sel->scope_ref == false);
  sel = my_css_selector(my_css_rule(sheet, 1u), 0u);
  ASSERT_NOT_NULL(sel);
  ASSERT_STR_EQ(sel->widget_type, "panel");
  ASSERT_EQ(sel->state, -1);
  my_css_sheet_destroy(sheet);

  ASSERT_NOT_NULL(theme);
  panel->widget_type = "panel";
  child->widget_type = "button";
  ASSERT_EQ(my_widget_add_child(panel, child), MY_RET_OK);
  ASSERT_EQ(my_theme_load_css_ex(theme, css, MY_CSS_PARSE_STRICT_AT_RULES),
            MY_RET_OK);
  value = my_theme_get_for_widget(theme, panel, MY_STATE_HOVER, "fg_color");
  ASSERT_NOT_NULL(value);
  ASSERT_EQ(my_value_get_uint32(value), 0xFF0000FFu);
  value = my_theme_get_for_widget(theme, panel, MY_STATE_NORMAL, "fg_color");
  ASSERT_NOT_NULL(value);
  ASSERT_EQ(my_value_get_uint32(value), 0x0000FFFFu);
  /* the state sits on the root only — a hovered child matches nothing. */
  value = my_theme_get_for_widget(theme, child, MY_STATE_HOVER, "fg_color");
  ASSERT_TRUE(value == NULL);
  my_widget_unref(child);
  my_widget_unref(panel);
  my_theme_destroy(theme);
}

TEST(css_scope_subject_state_form_root_list)
{
  /* `@scope panel, dialog { :scope:pressed { color: red; } }` — the state
   * qualifier rides along every root variant. */
  const char* css =
      "@scope panel, dialog { :scope:pressed { color: red; } }";
  my_css_error_t error = {0};
  my_css_sheet_t* sheet = my_css_parse_ex(
      NULL, css, strlen(css), MY_CSS_PARSE_STRICT_AT_RULES, &error);
  const my_css_rule_t* rule;
  my_theme_t* theme = my_theme_create(NULL);
  my_widget_t* panel = my_widget_create(NULL, "panel");
  my_widget_t* dialog = my_widget_create(NULL, "dialog");
  const my_value_t* value;

  ASSERT_NOT_NULL(sheet);
  ASSERT_EQ(my_css_rule_count(sheet), 1u);
  rule = my_css_rule(sheet, 0u);
  ASSERT_NOT_NULL(rule);
  ASSERT_EQ(my_css_selector_count(rule), 2u);
  ASSERT_STR_EQ(my_css_selector(rule, 0u)->widget_type, "panel");
  ASSERT_EQ(my_css_selector(rule, 0u)->state, (int32_t)MY_STATE_PRESSED);
  ASSERT_STR_EQ(my_css_selector(rule, 1u)->widget_type, "dialog");
  ASSERT_EQ(my_css_selector(rule, 1u)->state, (int32_t)MY_STATE_PRESSED);
  my_css_sheet_destroy(sheet);

  ASSERT_NOT_NULL(theme);
  panel->widget_type = "panel";
  dialog->widget_type = "dialog";
  ASSERT_EQ(my_theme_load_css_ex(theme, css, MY_CSS_PARSE_STRICT_AT_RULES),
            MY_RET_OK);
  value = my_theme_get_for_widget(theme, dialog, MY_STATE_PRESSED,
                                  "fg_color");
  ASSERT_NOT_NULL(value);
  ASSERT_EQ(my_value_get_uint32(value), 0xFF0000FFu);
  value = my_theme_get_for_widget(theme, panel, MY_STATE_NORMAL, "fg_color");
  ASSERT_TRUE(value == NULL);
  my_widget_unref(dialog);
  my_widget_unref(panel);
  my_theme_destroy(theme);
}

TEST(css_scope_subject_state_rejects_malformed)
{
  const char* malformed[] = {
      /* a state on the ANCESTOR scope marker can't be expressed */
      "@scope panel { :scope:hover button { color: red; } }",
      /* one state qualifier at most */
      "@scope panel { :scope:hover:pressed { color: red; } }",
      /* scope is not a state */
      "@scope panel { :scope:scope { color: red; } }"};
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

TEST(css_scope_subject_class_form_filters_root)
{
  /* `@scope panel { :scope.dark { color: red; } }` — a class qualifier on
   * `:scope` merges into the substituted root subject: the rule styles the
   * root itself, but only when it carries the class. Both qualification
   * orders (`:scope.dark` / `.dark:scope`) mean the same. */
  const char* css = "@scope panel { :scope.dark { color: red; } }";
  const char* css2 = "@scope panel { .dark:scope { color: red; } }";
  my_css_error_t error = {0};
  my_css_sheet_t* sheet = my_css_parse_ex(
      NULL, css, strlen(css), MY_CSS_PARSE_STRICT_AT_RULES, &error);
  const my_css_selector_t* sel;
  my_theme_t* theme = my_theme_create(NULL);
  my_widget_t* dark = my_widget_create(NULL, "dark");
  my_widget_t* plain = my_widget_create(NULL, "plain");
  const my_value_t* value;

  ASSERT_NOT_NULL(sheet);
  ASSERT_EQ(my_css_rule_count(sheet), 1u);
  sel = my_css_selector(my_css_rule(sheet, 0u), 0u);
  ASSERT_NOT_NULL(sel);
  ASSERT_STR_EQ(sel->widget_type, "panel");
  ASSERT_STR_EQ(sel->style_class, "dark");
  ASSERT_EQ(sel->state, -1);
  ASSERT_TRUE(sel->scope_ref == false);
  my_css_sheet_destroy(sheet);

  sheet = my_css_parse_ex(NULL, css2, strlen(css2),
                          MY_CSS_PARSE_STRICT_AT_RULES, &error);
  ASSERT_NOT_NULL(sheet);
  sel = my_css_selector(my_css_rule(sheet, 0u), 0u);
  ASSERT_NOT_NULL(sel);
  ASSERT_STR_EQ(sel->widget_type, "panel");
  ASSERT_STR_EQ(sel->style_class, "dark");
  my_css_sheet_destroy(sheet);

  ASSERT_NOT_NULL(theme);
  dark->widget_type = "panel";
  plain->widget_type = "panel";
  ASSERT_EQ(my_widget_set_style_class(dark, "dark"), MY_RET_OK);
  ASSERT_EQ(my_theme_load_css_ex(theme, css, MY_CSS_PARSE_STRICT_AT_RULES),
            MY_RET_OK);
  value = my_theme_get_for_widget(theme, dark, MY_STATE_NORMAL, "fg_color");
  ASSERT_NOT_NULL(value);
  ASSERT_EQ(my_value_get_uint32(value), 0xFF0000FFu);
  value = my_theme_get_for_widget(theme, plain, MY_STATE_NORMAL, "fg_color");
  ASSERT_TRUE(value == NULL);
  my_widget_unref(plain);
  my_widget_unref(dark);
  my_theme_destroy(theme);
}

TEST(css_scope_subject_class_form_merges_root_classes_and_state)
{
  /* `@scope panel.card { :scope.dark:hover { color: red; } }` — the
   * qualifier classes append to the root's own classes; a state qualifier
   * stacks too. */
  const char* css =
      "@scope panel.card { :scope.dark:hover { color: red; } }";
  my_css_error_t error = {0};
  my_css_sheet_t* sheet = my_css_parse_ex(
      NULL, css, strlen(css), MY_CSS_PARSE_STRICT_AT_RULES, &error);
  const my_css_selector_t* sel;
  my_theme_t* theme = my_theme_create(NULL);
  my_widget_t* full = my_widget_create(NULL, "full");
  my_widget_t* card_only = my_widget_create(NULL, "card_only");
  my_widget_t* dark_only = my_widget_create(NULL, "dark_only");
  const my_value_t* value;

  ASSERT_NOT_NULL(sheet);
  ASSERT_EQ(my_css_rule_count(sheet), 1u);
  sel = my_css_selector(my_css_rule(sheet, 0u), 0u);
  ASSERT_NOT_NULL(sel);
  ASSERT_STR_EQ(sel->widget_type, "panel");
  ASSERT_STR_EQ(sel->style_class, "card dark");
  ASSERT_EQ(sel->state, (int32_t)MY_STATE_HOVER);
  my_css_sheet_destroy(sheet);

  ASSERT_NOT_NULL(theme);
  full->widget_type = "panel";
  card_only->widget_type = "panel";
  dark_only->widget_type = "panel";
  ASSERT_EQ(my_widget_set_style_class(full, "card dark"), MY_RET_OK);
  ASSERT_EQ(my_widget_set_style_class(card_only, "card"), MY_RET_OK);
  ASSERT_EQ(my_widget_set_style_class(dark_only, "dark"), MY_RET_OK);
  ASSERT_EQ(my_theme_load_css_ex(theme, css, MY_CSS_PARSE_STRICT_AT_RULES),
            MY_RET_OK);
  value = my_theme_get_for_widget(theme, full, MY_STATE_HOVER, "fg_color");
  ASSERT_NOT_NULL(value);
  ASSERT_EQ(my_value_get_uint32(value), 0xFF0000FFu);
  /* both class requirements are AND-ed: each partial match misses. */
  value =
      my_theme_get_for_widget(theme, card_only, MY_STATE_HOVER, "fg_color");
  ASSERT_TRUE(value == NULL);
  value =
      my_theme_get_for_widget(theme, dark_only, MY_STATE_HOVER, "fg_color");
  ASSERT_TRUE(value == NULL);
  /* the state qualifier is required too. */
  value = my_theme_get_for_widget(theme, full, MY_STATE_NORMAL, "fg_color");
  ASSERT_TRUE(value == NULL);
  my_widget_unref(dark_only);
  my_widget_unref(card_only);
  my_widget_unref(full);
  my_theme_destroy(theme);
}

TEST(css_scope_subject_qual_rejects_malformed)
{
  const char* malformed[] = {
      /* an id qualifier stays out of the subset */
      "@scope panel { :scope#x { color: red; } }",
      /* class quals on the ANCESTOR scope marker can't be expressed */
      "@scope panel { :scope.dark button { color: red; } }",
      /* one state qualifier at most */
      "@scope panel { :scope.dark:hover:pressed { color: red; } }"};
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

TEST(css_supports_selector_function_evaluates_grammar_support)
{
  /* R649: css-conditional-3 `selector()` — true when the argument parses
   * under the engine's selector grammar (compound chains with descendant
   * and '>' combinators; `&`/`:scope` count as grammar). Context placement
   * (inside a rule / @scope) is not grammar, so those parse as supported.
   * Unknown pseudo-classes, dangling combinators, and junk reject as
   * unsupported (condition false), not as parse errors. */
  const char* css =
      "@supports selector(.x) { button { color: red; } }"
      "@supports selector(panel > .item:hover) { label { color: blue; } }"
      "@supports selector(&) { edit { color: green; } }"
      "@supports selector(:scope) { slider { color: white; } }"
      "@supports not (selector(:bogus)) { check { color: black; } }"
      "@supports (color: red) and (selector(.x)) { radio { color: gray; } }"
      "@supports selector(:bogus) { skipped1 { color: red; } }"
      "@supports selector(div >) { skipped2 { color: red; } }"
      "@supports selector() { skipped3 { color: red; } }";
  const char* malformed =
      "@supports (selector(.x) { button { color: red; } }";
  my_css_error_t error = {0};
  my_css_sheet_t* sheet = my_css_parse_ex(
      NULL, css, strlen(css), MY_CSS_PARSE_STRICT_AT_RULES, &error);

  ASSERT_NOT_NULL(sheet);
  ASSERT_EQ(my_css_rule_count(sheet), 6u);
  ASSERT_STR_EQ(my_css_selector(my_css_rule(sheet, 0u), 0u)->widget_type,
                "button");
  ASSERT_STR_EQ(my_css_selector(my_css_rule(sheet, 1u), 0u)->widget_type,
                "label");
  ASSERT_STR_EQ(my_css_selector(my_css_rule(sheet, 2u), 0u)->widget_type,
                "edit");
  ASSERT_STR_EQ(my_css_selector(my_css_rule(sheet, 3u), 0u)->widget_type,
                "slider");
  ASSERT_STR_EQ(my_css_selector(my_css_rule(sheet, 4u), 0u)->widget_type,
                "check");
  ASSERT_STR_EQ(my_css_selector(my_css_rule(sheet, 5u), 0u)->widget_type,
                "radio");
  my_css_sheet_destroy(sheet);

  memset(&error, 0, sizeof(error));
  sheet = my_css_parse_ex(NULL, malformed, strlen(malformed),
                          MY_CSS_PARSE_STRICT_AT_RULES, &error);
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

TEST(css_conditional_media_supports_aspect_ratio)
{
  /* R646: (aspect-ratio: a/b), min/max forms, and the bare-integer a/1
   * shorthand — evaluated against the logical viewport by exact
   * cross-multiplication (no float). */
  const char* exact = "@media (aspect-ratio: 16/9) { button { color: red; } }";
  const char* bare = "@media (aspect-ratio: 2) { button { color: red; } }";
  const char* at_least =
      "@media (min-aspect-ratio: 1/1) { button { color: red; } }";
  const char* at_most =
      "@media (max-aspect-ratio: 4/3) { button { color: red; } }";
  const char* malformed[] = {
      "@media (aspect-ratio: 16/) { button { color: red; } }",
      "@media (aspect-ratio: x/y) { button { color: red; } }",
      "@media (aspect-ratio: 0/9) { button { color: red; } }",
      "@media (aspect-ratio: 16/0) { button { color: red; } }"};
  my_css_media_context_t wide = {1600u, 900u, true, false, false, 0u};
  my_css_media_context_t four_three = {1024u, 768u, true, false, false, 0u};
  my_css_media_context_t tall = {800u, 1000u, true, false, false, 0u};
  my_css_media_context_t two_one = {1600u, 800u, true, false, false, 0u};
  my_css_error_t error = {0};
  my_css_sheet_t* sheet;
  size_t i;

  sheet = my_css_parse_media_ex(NULL, exact, strlen(exact),
                                MY_CSS_PARSE_STRICT_AT_RULES, &wide, &error);
  ASSERT_NOT_NULL(sheet);
  ASSERT_EQ(my_css_rule_count(sheet), 1u);
  my_css_sheet_destroy(sheet);

  memset(&error, 0, sizeof(error));
  sheet = my_css_parse_media_ex(NULL, exact, strlen(exact),
                                MY_CSS_PARSE_STRICT_AT_RULES, &four_three,
                                &error);
  ASSERT_NOT_NULL(sheet);
  ASSERT_EQ(my_css_rule_count(sheet), 0u);
  my_css_sheet_destroy(sheet);

  /* bare integer means a/1. */
  memset(&error, 0, sizeof(error));
  sheet = my_css_parse_media_ex(NULL, bare, strlen(bare),
                                MY_CSS_PARSE_STRICT_AT_RULES, &two_one,
                                &error);
  ASSERT_NOT_NULL(sheet);
  ASSERT_EQ(my_css_rule_count(sheet), 1u);
  my_css_sheet_destroy(sheet);

  memset(&error, 0, sizeof(error));
  sheet = my_css_parse_media_ex(NULL, bare, strlen(bare),
                                MY_CSS_PARSE_STRICT_AT_RULES, &wide, &error);
  ASSERT_NOT_NULL(sheet);
  ASSERT_EQ(my_css_rule_count(sheet), 0u);
  my_css_sheet_destroy(sheet);

  /* min: viewport ratio >= a/b. */
  memset(&error, 0, sizeof(error));
  sheet = my_css_parse_media_ex(NULL, at_least, strlen(at_least),
                                MY_CSS_PARSE_STRICT_AT_RULES, &wide, &error);
  ASSERT_NOT_NULL(sheet);
  ASSERT_EQ(my_css_rule_count(sheet), 1u);
  my_css_sheet_destroy(sheet);

  memset(&error, 0, sizeof(error));
  sheet = my_css_parse_media_ex(NULL, at_least, strlen(at_least),
                                MY_CSS_PARSE_STRICT_AT_RULES, &tall, &error);
  ASSERT_NOT_NULL(sheet);
  ASSERT_EQ(my_css_rule_count(sheet), 0u);
  my_css_sheet_destroy(sheet);

  /* max: viewport ratio <= a/b; the exact 4/3 viewport matches. */
  memset(&error, 0, sizeof(error));
  sheet = my_css_parse_media_ex(NULL, at_most, strlen(at_most),
                                MY_CSS_PARSE_STRICT_AT_RULES, &four_three,
                                &error);
  ASSERT_NOT_NULL(sheet);
  ASSERT_EQ(my_css_rule_count(sheet), 1u);
  my_css_sheet_destroy(sheet);

  memset(&error, 0, sizeof(error));
  sheet = my_css_parse_media_ex(NULL, at_most, strlen(at_most),
                                MY_CSS_PARSE_STRICT_AT_RULES, &wide, &error);
  ASSERT_NOT_NULL(sheet);
  ASSERT_EQ(my_css_rule_count(sheet), 0u);
  my_css_sheet_destroy(sheet);

  /* malformed ratios reject in strict mode. */
  for (i = 0u; i < sizeof(malformed) / sizeof(malformed[0]); ++i) {
    memset(&error, 0, sizeof(error));
    ASSERT_TRUE(my_css_parse_media_ex(NULL, malformed[i],
                                      strlen(malformed[i]),
                                      MY_CSS_PARSE_STRICT_AT_RULES, &wide,
                                      &error) == NULL);
  }
}

TEST(css_conditional_media_supports_aspect_ratio_range)
{
  /* R647: ratio-domain range syntax — name-first `(aspect-ratio >= 16/9)`,
   * value-first `(1/1 <= aspect-ratio)`, and the chained
   * `(1/1 <= aspect-ratio <= 2/1)`. Domain mismatches (ratio value with a
   * px feature or px value with aspect-ratio) reject. */
  const char* ge = "@media (aspect-ratio >= 16/9) { button { color: red; } }";
  const char* lt = "@media (aspect-ratio < 1/1) { button { color: red; } }";
  const char* eq = "@media (aspect-ratio = 16/9) { button { color: red; } }";
  const char* vfirst =
      "@media (1/1 <= aspect-ratio) { button { color: red; } }";
  const char* chained =
      "@media (1/1 <= aspect-ratio <= 2/1) { button { color: red; } }";
  const char* malformed[] = {
      "@media (aspect-ratio >= 16/) { button { color: red; } }",
      "@media (1/0 <= aspect-ratio) { button { color: red; } }",
      "@media (aspect-ratio > 1/1 <= 2/1) { button { color: red; } }",
      "@media (16/9 <= width) { button { color: red; } }",
      "@media (100px <= aspect-ratio) { button { color: red; } }",
      "@media (aspect-ratio >= 100px) { button { color: red; } }"};
  my_css_media_context_t wide = {1600u, 900u, true, false, false, 0u};
  my_css_media_context_t four_three = {1024u, 768u, true, false, false, 0u};
  my_css_media_context_t tall = {800u, 1000u, true, false, false, 0u};
  my_css_media_context_t extreme = {3000u, 1000u, true, false, false, 0u};
  my_css_error_t error = {0};
  my_css_sheet_t* sheet;
  size_t i;

  /* name-first: >= matches the exact 16:9 viewport, not 4:3. */
  sheet = my_css_parse_media_ex(NULL, ge, strlen(ge),
                                MY_CSS_PARSE_STRICT_AT_RULES, &wide, &error);
  ASSERT_NOT_NULL(sheet);
  ASSERT_EQ(my_css_rule_count(sheet), 1u);
  my_css_sheet_destroy(sheet);

  memset(&error, 0, sizeof(error));
  sheet = my_css_parse_media_ex(NULL, ge, strlen(ge),
                                MY_CSS_PARSE_STRICT_AT_RULES, &four_three,
                                &error);
  ASSERT_NOT_NULL(sheet);
  ASSERT_EQ(my_css_rule_count(sheet), 0u);
  my_css_sheet_destroy(sheet);

  /* name-first: < 1/1 only the tall viewport matches. */
  memset(&error, 0, sizeof(error));
  sheet = my_css_parse_media_ex(NULL, lt, strlen(lt),
                                MY_CSS_PARSE_STRICT_AT_RULES, &tall, &error);
  ASSERT_NOT_NULL(sheet);
  ASSERT_EQ(my_css_rule_count(sheet), 1u);
  my_css_sheet_destroy(sheet);

  memset(&error, 0, sizeof(error));
  sheet = my_css_parse_media_ex(NULL, lt, strlen(lt),
                                MY_CSS_PARSE_STRICT_AT_RULES, &wide, &error);
  ASSERT_NOT_NULL(sheet);
  ASSERT_EQ(my_css_rule_count(sheet), 0u);
  my_css_sheet_destroy(sheet);

  /* name-first: = form. */
  memset(&error, 0, sizeof(error));
  sheet = my_css_parse_media_ex(NULL, eq, strlen(eq),
                                MY_CSS_PARSE_STRICT_AT_RULES, &wide, &error);
  ASSERT_NOT_NULL(sheet);
  ASSERT_EQ(my_css_rule_count(sheet), 1u);
  my_css_sheet_destroy(sheet);

  /* value-first: 1/1 <= aspect-ratio. */
  memset(&error, 0, sizeof(error));
  sheet = my_css_parse_media_ex(NULL, vfirst, strlen(vfirst),
                                MY_CSS_PARSE_STRICT_AT_RULES, &wide, &error);
  ASSERT_NOT_NULL(sheet);
  ASSERT_EQ(my_css_rule_count(sheet), 1u);
  my_css_sheet_destroy(sheet);

  memset(&error, 0, sizeof(error));
  sheet = my_css_parse_media_ex(NULL, vfirst, strlen(vfirst),
                                MY_CSS_PARSE_STRICT_AT_RULES, &tall, &error);
  ASSERT_NOT_NULL(sheet);
  ASSERT_EQ(my_css_rule_count(sheet), 0u);
  my_css_sheet_destroy(sheet);

  /* chained: wide inside, extreme (3/1) and tall outside. */
  memset(&error, 0, sizeof(error));
  sheet = my_css_parse_media_ex(NULL, chained, strlen(chained),
                                MY_CSS_PARSE_STRICT_AT_RULES, &wide, &error);
  ASSERT_NOT_NULL(sheet);
  ASSERT_EQ(my_css_rule_count(sheet), 1u);
  my_css_sheet_destroy(sheet);

  memset(&error, 0, sizeof(error));
  sheet = my_css_parse_media_ex(NULL, chained, strlen(chained),
                                MY_CSS_PARSE_STRICT_AT_RULES, &extreme,
                                &error);
  ASSERT_NOT_NULL(sheet);
  ASSERT_EQ(my_css_rule_count(sheet), 0u);
  my_css_sheet_destroy(sheet);

  memset(&error, 0, sizeof(error));
  sheet = my_css_parse_media_ex(NULL, chained, strlen(chained),
                                MY_CSS_PARSE_STRICT_AT_RULES, &tall, &error);
  ASSERT_NOT_NULL(sheet);
  ASSERT_EQ(my_css_rule_count(sheet), 0u);
  my_css_sheet_destroy(sheet);

  for (i = 0u; i < sizeof(malformed) / sizeof(malformed[0]); ++i) {
    memset(&error, 0, sizeof(error));
    ASSERT_TRUE(my_css_parse_media_ex(NULL, malformed[i],
                                      strlen(malformed[i]),
                                      MY_CSS_PARSE_STRICT_AT_RULES, &wide,
                                      &error) == NULL);
  }
}

TEST(css_conditional_media_supports_only_modifier)
{
  /* R648: the legacy `only` modifier (extremely common in real-world
   * stylesheets) is a no-op synonym for the bare media type:
   * `only screen` ≡ `screen`, `only all` ≡ `all`. It requires a following
   * media type and cannot combine with `not`. */
  const char* only_screen =
      "@media only screen and (min-width: 800px) { button { color: red; } }";
  const char* only_all =
      "@media only all and (min-width: 800px) { button { color: red; } }";
  const char* bare_type = "@media only screen { button { color: red; } }";
  const char* only_malformed[] = {
      "@media only (min-width: 1px) { button { color: red; } }",
      "@media not only screen { button { color: red; } }",
      "@media only not screen { button { color: red; } }",
      "@media onlyonly screen { button { color: red; } }"};
  my_css_media_context_t screen_wide = {1024u, 768u, true, false, false, 0u};
  my_css_media_context_t screen_narrow = {600u, 768u, true, false, false, 0u};
  my_css_media_context_t non_screen = {1024u, 768u, false, false, false, 0u};
  my_css_error_t error = {0};
  my_css_sheet_t* sheet;
  size_t i;

  sheet = my_css_parse_media_ex(NULL, only_screen, strlen(only_screen),
                                MY_CSS_PARSE_STRICT_AT_RULES, &screen_wide,
                                &error);
  ASSERT_NOT_NULL(sheet);
  ASSERT_EQ(my_css_rule_count(sheet), 1u);
  my_css_sheet_destroy(sheet);

  /* feature still gates: narrow viewport misses. */
  memset(&error, 0, sizeof(error));
  sheet = my_css_parse_media_ex(NULL, only_screen, strlen(only_screen),
                                MY_CSS_PARSE_STRICT_AT_RULES, &screen_narrow,
                                &error);
  ASSERT_NOT_NULL(sheet);
  ASSERT_EQ(my_css_rule_count(sheet), 0u);
  my_css_sheet_destroy(sheet);

  /* type still gates: non-screen context misses. */
  memset(&error, 0, sizeof(error));
  sheet = my_css_parse_media_ex(NULL, only_screen, strlen(only_screen),
                                MY_CSS_PARSE_STRICT_AT_RULES, &non_screen,
                                &error);
  ASSERT_NOT_NULL(sheet);
  ASSERT_EQ(my_css_rule_count(sheet), 0u);
  my_css_sheet_destroy(sheet);

  memset(&error, 0, sizeof(error));
  sheet = my_css_parse_media_ex(NULL, only_all, strlen(only_all),
                                MY_CSS_PARSE_STRICT_AT_RULES, &screen_wide,
                                &error);
  ASSERT_NOT_NULL(sheet);
  ASSERT_EQ(my_css_rule_count(sheet), 1u);
  my_css_sheet_destroy(sheet);

  memset(&error, 0, sizeof(error));
  sheet = my_css_parse_media_ex(NULL, bare_type, strlen(bare_type),
                                MY_CSS_PARSE_STRICT_AT_RULES, &screen_wide,
                                &error);
  ASSERT_NOT_NULL(sheet);
  ASSERT_EQ(my_css_rule_count(sheet), 1u);
  my_css_sheet_destroy(sheet);

  for (i = 0u; i < sizeof(only_malformed) / sizeof(only_malformed[0]); ++i) {
    memset(&error, 0, sizeof(error));
    ASSERT_TRUE(my_css_parse_media_ex(NULL, only_malformed[i],
                                      strlen(only_malformed[i]),
                                      MY_CSS_PARSE_STRICT_AT_RULES,
                                      &screen_wide, &error) == NULL);
  }
}

TEST(css_conditional_media_supports_mq4_boolean_logic)
{
  /* R650: MQ4 boolean logic — or-chains (uniform per level), nested
   * conditions in parens, and item-level `not`. Query-level leading `not`
   * keeps its existing contract (single item, no continuation); with a
   * nested group it now expresses MQ3 whole-query negation. */
  const char* or_css =
      "@media (min-width: 800px) or (orientation: portrait) { button { color: red; } }";
  const char* nested_not =
      "@media (min-width: 800px) and (not (orientation: portrait)) { button { color: red; } }";
  const char* group =
      "@media ((min-width: 800px) and (orientation: landscape)) or (orientation: portrait) { button { color: red; } }";
  const char* item_not =
      "@media (min-width: 800px) and not (orientation: portrait) { button { color: red; } }";
  const char* whole_not =
      "@media not ((min-width: 800px) and (orientation: landscape)) { button { color: red; } }";
  const char* malformed[] = {
      /* and/or mixing at one level */
      "@media (min-width: 1px) and (orientation: landscape) or (orientation: portrait) { button { color: red; } }",
      /* type queries take `and` only */
      "@media screen or (min-width: 1px) { button { color: red; } }",
      /* query-level not takes no continuation (existing contract) */
      "@media not (min-width: 1px) and (orientation: landscape) { button { color: red; } }",
      /* unbalanced nesting */
      "@media ((min-width: 1px) or (orientation: portrait) { button { color: red; } }"};
  my_css_media_context_t wide_ls = {1024u, 768u, true, false, false, 0u};
  my_css_media_context_t narrow_pt = {600u, 900u, true, false, false, 0u};
  my_css_media_context_t narrow_ls = {700u, 600u, true, false, false, 0u};
  my_css_media_context_t wide_pt = {1024u, 1200u, true, false, false, 0u};
  my_css_media_context_t mid_ls = {600u, 768u, true, false, false, 0u};
  my_css_error_t error = {0};
  my_css_sheet_t* sheet;
  size_t i;

  /* or-chain: either leg suffices. */
  sheet = my_css_parse_media_ex(NULL, or_css, strlen(or_css),
                                MY_CSS_PARSE_STRICT_AT_RULES, &wide_ls,
                                &error);
  ASSERT_NOT_NULL(sheet);
  ASSERT_EQ(my_css_rule_count(sheet), 1u);
  my_css_sheet_destroy(sheet);

  memset(&error, 0, sizeof(error));
  sheet = my_css_parse_media_ex(NULL, or_css, strlen(or_css),
                                MY_CSS_PARSE_STRICT_AT_RULES, &narrow_pt,
                                &error);
  ASSERT_NOT_NULL(sheet);
  ASSERT_EQ(my_css_rule_count(sheet), 1u);
  my_css_sheet_destroy(sheet);

  memset(&error, 0, sizeof(error));
  sheet = my_css_parse_media_ex(NULL, or_css, strlen(or_css),
                                MY_CSS_PARSE_STRICT_AT_RULES, &narrow_ls,
                                &error);
  ASSERT_NOT_NULL(sheet);
  ASSERT_EQ(my_css_rule_count(sheet), 0u);
  my_css_sheet_destroy(sheet);

  /* nested (not (...)) inside an and-chain. */
  memset(&error, 0, sizeof(error));
  sheet = my_css_parse_media_ex(NULL, nested_not, strlen(nested_not),
                                MY_CSS_PARSE_STRICT_AT_RULES, &wide_ls,
                                &error);
  ASSERT_NOT_NULL(sheet);
  ASSERT_EQ(my_css_rule_count(sheet), 1u);
  my_css_sheet_destroy(sheet);

  memset(&error, 0, sizeof(error));
  sheet = my_css_parse_media_ex(NULL, nested_not, strlen(nested_not),
                                MY_CSS_PARSE_STRICT_AT_RULES, &wide_pt,
                                &error);
  ASSERT_NOT_NULL(sheet);
  ASSERT_EQ(my_css_rule_count(sheet), 0u);
  my_css_sheet_destroy(sheet);

  /* nested group as an or-chain leg. */
  memset(&error, 0, sizeof(error));
  sheet = my_css_parse_media_ex(NULL, group, strlen(group),
                                MY_CSS_PARSE_STRICT_AT_RULES, &wide_ls,
                                &error);
  ASSERT_NOT_NULL(sheet);
  ASSERT_EQ(my_css_rule_count(sheet), 1u);
  my_css_sheet_destroy(sheet);

  memset(&error, 0, sizeof(error));
  sheet = my_css_parse_media_ex(NULL, group, strlen(group),
                                MY_CSS_PARSE_STRICT_AT_RULES, &narrow_pt,
                                &error);
  ASSERT_NOT_NULL(sheet);
  ASSERT_EQ(my_css_rule_count(sheet), 1u);
  my_css_sheet_destroy(sheet);

  memset(&error, 0, sizeof(error));
  sheet = my_css_parse_media_ex(NULL, group, strlen(group),
                                MY_CSS_PARSE_STRICT_AT_RULES, &narrow_ls,
                                &error);
  ASSERT_NOT_NULL(sheet);
  ASSERT_EQ(my_css_rule_count(sheet), 0u);
  my_css_sheet_destroy(sheet);

  /* pragmatic item-level not (browser-compatible form). */
  memset(&error, 0, sizeof(error));
  sheet = my_css_parse_media_ex(NULL, item_not, strlen(item_not),
                                MY_CSS_PARSE_STRICT_AT_RULES, &wide_ls,
                                &error);
  ASSERT_NOT_NULL(sheet);
  ASSERT_EQ(my_css_rule_count(sheet), 1u);
  my_css_sheet_destroy(sheet);

  memset(&error, 0, sizeof(error));
  sheet = my_css_parse_media_ex(NULL, item_not, strlen(item_not),
                                MY_CSS_PARSE_STRICT_AT_RULES, &wide_pt,
                                &error);
  ASSERT_NOT_NULL(sheet);
  ASSERT_EQ(my_css_rule_count(sheet), 0u);
  my_css_sheet_destroy(sheet);

  /* query-level not over a nested group = whole-query negation. */
  memset(&error, 0, sizeof(error));
  sheet = my_css_parse_media_ex(NULL, whole_not, strlen(whole_not),
                                MY_CSS_PARSE_STRICT_AT_RULES, &narrow_ls,
                                &error);
  ASSERT_NOT_NULL(sheet);
  ASSERT_EQ(my_css_rule_count(sheet), 1u);
  my_css_sheet_destroy(sheet);

  memset(&error, 0, sizeof(error));
  sheet = my_css_parse_media_ex(NULL, whole_not, strlen(whole_not),
                                MY_CSS_PARSE_STRICT_AT_RULES, &wide_ls,
                                &error);
  ASSERT_NOT_NULL(sheet);
  ASSERT_EQ(my_css_rule_count(sheet), 0u);
  my_css_sheet_destroy(sheet);

  /* mid-width landscape misses both legs of nested_not's and-chain. */
  memset(&error, 0, sizeof(error));
  sheet = my_css_parse_media_ex(NULL, nested_not, strlen(nested_not),
                                MY_CSS_PARSE_STRICT_AT_RULES, &mid_ls,
                                &error);
  ASSERT_NOT_NULL(sheet);
  ASSERT_EQ(my_css_rule_count(sheet), 0u);
  my_css_sheet_destroy(sheet);

  for (i = 0u; i < sizeof(malformed) / sizeof(malformed[0]); ++i) {
    memset(&error, 0, sizeof(error));
    ASSERT_TRUE(my_css_parse_media_ex(NULL, malformed[i],
                                      strlen(malformed[i]),
                                      MY_CSS_PARSE_STRICT_AT_RULES, &wide_ls,
                                      &error) == NULL);
  }
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

TEST(css_anonymous_layers_get_unique_orders)
{
  /* R655: anonymous layers — `@layer { ... }` without a name and the bare
   * `layer` import condition. Each occurrence registers a fresh layer order
   * (empty registry names can never collide with named lookups); the usual
   * cascade rules apply (later anonymous outranks earlier, unlayered
   * outranks all). */
  const css_import_entry_t entries[] = {
      {"themed.css", "label { color: red; }", 21u}, {NULL, NULL, 0u}};
  const char* css =
      "@layer { button { color: red; } }"
      "@layer { label { color: blue; } }"
      "@layer named { edit { color: green; } }";
  const char* imported = "@import \"themed.css\" layer; button { color: blue; }";
  my_css_error_t error = {0};
  my_css_sheet_t* sheet = my_css_parse_ex(
      NULL, css, strlen(css), MY_CSS_PARSE_STRICT_AT_RULES, &error);
  my_css_parse_options_t options = {0};

  ASSERT_NOT_NULL(sheet);
  ASSERT_EQ(my_css_rule_count(sheet), 3u);
  /* each anonymous occurrence is its own layer, in source order. */
  ASSERT_EQ(my_css_rule(sheet, 0u)->layer_order, 0u);
  ASSERT_EQ(my_css_rule(sheet, 1u)->layer_order, 1u);
  ASSERT_EQ(my_css_rule(sheet, 2u)->layer_order, 2u);
  my_css_sheet_destroy(sheet);

  /* bare `layer` import: the imported rules are anonymous-layered. */
  options.flags = MY_CSS_PARSE_STRICT_AT_RULES;
  options.resolve_import = css_test_resolve_import;
  options.import_context = (void*)entries;
  memset(&error, 0, sizeof(error));
  sheet = my_css_parse_with_options(NULL, imported, strlen(imported),
                                    &options, &error);
  ASSERT_NOT_NULL(sheet);
  ASSERT_EQ(my_css_rule_count(sheet), 2u);
  ASSERT_EQ(my_css_rule(sheet, 0u)->layer_order, 0u);
  ASSERT_EQ(my_css_rule(sheet, 1u)->layer_order, MY_CSS_UNLAYERED_ORDER);
  my_css_sheet_destroy(sheet);

  /* later anonymous layer outranks earlier on the same selector. */
  {
    const char* order =
        "@layer { button { color: red; } }"
        "@layer { button { color: blue; } }";
    my_theme_t* theme = my_theme_create(NULL);
    my_widget_t* widget = my_widget_create(NULL, "button");
    const my_value_t* value;

    ASSERT_NOT_NULL(theme);
    ASSERT_NOT_NULL(widget);
    widget->widget_type = "button";
    ASSERT_EQ(my_theme_load_css_ex(theme, order, MY_CSS_PARSE_STRICT_AT_RULES),
              MY_RET_OK);
    value = my_theme_get_for_widget(theme, widget, MY_STATE_NORMAL,
                                    "fg_color");
    ASSERT_NOT_NULL(value);
    ASSERT_EQ(my_value_get_uint32(value), 0x0000FFFFu);
    my_widget_unref(widget);
    my_theme_destroy(theme);
  }

  /* unlayered still outranks an anonymous layer. */
  {
    const char* unlayered =
        "@layer { button { color: red; } } button { color: blue; }";
    my_theme_t* theme = my_theme_create(NULL);
    my_widget_t* widget = my_widget_create(NULL, "button");
    const my_value_t* value;

    ASSERT_NOT_NULL(theme);
    ASSERT_NOT_NULL(widget);
    widget->widget_type = "button";
    ASSERT_EQ(my_theme_load_css_ex(theme, unlayered,
                                   MY_CSS_PARSE_STRICT_AT_RULES),
              MY_RET_OK);
    value = my_theme_get_for_widget(theme, widget, MY_STATE_NORMAL,
                                    "fg_color");
    ASSERT_NOT_NULL(value);
    ASSERT_EQ(my_value_get_uint32(value), 0x0000FFFFu);
    my_widget_unref(widget);
    my_theme_destroy(theme);
  }
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
    RUN_TEST(css_decl_important_flag_and_cascade);
    RUN_TEST(css_rejects_selector_paths_over_depth_limit);
    RUN_TEST(css_rejects_dangling_and_repeated_combinators);
    RUN_TEST(css_rejects_adjacent_selector_tokens_without_combinator);
    RUN_TEST(css_comments_preserve_descendant_separator);
    RUN_TEST(css_unsupported_at_rules_ignore_braces_in_strings_and_comments);
    RUN_TEST(css_import_resolver_flattens_sources_in_source_order);
    RUN_TEST(css_import_without_resolver_is_rejected_in_strict_mode);
    RUN_TEST(css_import_cycle_and_depth_are_bounded);
    RUN_TEST(css_import_rejects_absolute_and_traversal_paths);
    RUN_TEST(css_import_media_qualifier_gates_resolution);
    RUN_TEST(css_import_position_and_charset_conformance);
    RUN_TEST(css_container_size_queries_evaluate_at_parse_time);
    RUN_TEST(css_container_nested_in_rule_blocks);
    RUN_TEST(css_custom_properties_store_raw_token_streams);
    RUN_TEST(css_var_substitution_resolves_at_lookup_time);
    RUN_TEST(css_var_flows_through_widget_style_accessors);
    RUN_TEST(css_container_properties_parse_and_cascade);
    RUN_TEST(css_container_queries_resolve_against_ancestor_at_match_time);
    RUN_TEST(css_container_style_queries_resolve_at_match_time);
    RUN_TEST(css_container_style_query_registered_computed_comparison);
    RUN_TEST(css_property_syntax_multi_choice_alternatives);
    RUN_TEST(css_container_nested_queries_and_at_match_time);
    RUN_TEST(css_property_rule_registers_custom_properties);
    RUN_TEST(css_property_syntax_is_enforced_at_computed_value_time);
    RUN_TEST(css_property_syntax_percentage_primitive);
    RUN_TEST(css_import_supports_qualifier_gates_resolution);
    RUN_TEST(css_import_layer_qualifier_assigns_layer_order);
    RUN_TEST(css_import_bare_layer_qualifier_is_length_bounded);
    RUN_TEST(css_scope_applies_rules_only_inside_root);
    RUN_TEST(css_scope_accepts_to_clause_and_rejects_malformed_limit);
    RUN_TEST(css_scope_to_clause_accepts_implicit_root);
    RUN_TEST(css_scope_implicit_root_to_clause_excludes_boundary);
    RUN_TEST(css_scope_implicit_root_rejects_malformed_limit);
    RUN_TEST(css_scope_rejects_malformed_root_with_scope_capability);
    RUN_TEST(css_scope_root_child_combinator);
    RUN_TEST(css_scope_root_descendant_combinator);
    RUN_TEST(css_scope_root_path_to_limit_boundary);
    RUN_TEST(css_scope_limit_root_index_pins_subject_slot);
    RUN_TEST(css_scope_root_combinator_rejects_malformed);
    RUN_TEST(css_scope_limit_child_combinator);
    RUN_TEST(css_scope_limit_descendant_combinator);
    RUN_TEST(css_scope_limit_combinator_excludes_boundary_itself);
    RUN_TEST(css_scope_limit_selector_list_with_paths);
    RUN_TEST(css_scope_limit_combinator_rejects_malformed);
    RUN_TEST(css_scope_root_selector_list);
    RUN_TEST(css_scope_root_list_with_combinator_items);
    RUN_TEST(css_scope_root_list_with_limit);
    RUN_TEST(css_scope_root_list_expansion_is_bounded);
    RUN_TEST(css_scope_root_list_rejects_malformed);
    RUN_TEST(css_scope_paren_prelude_accepted);
    RUN_TEST(css_scope_paren_prelude_rejects_malformed);
    RUN_TEST(css_scope_scope_pseudo_styles_root);
    RUN_TEST(css_scope_scope_pseudo_as_outermost_ancestor);
    RUN_TEST(css_scope_scope_pseudo_with_limit_and_list);
    RUN_TEST(css_scope_scope_pseudo_rejects_misuse);
    RUN_TEST(css_nest_child_path);
    RUN_TEST(css_nest_descendant_and_group);
    RUN_TEST(css_nest_state_merge);
    RUN_TEST(css_nest_rejects_malformed);
    RUN_TEST(css_nest_group_subject_merge);
    RUN_TEST(css_nest_group_ancestor_forms);
    RUN_TEST(css_nest_group_cross_product_with_parent_group);
    RUN_TEST(css_nest_group_rejects_malformed);
    RUN_TEST(css_nest_second_level_descendant_chain);
    RUN_TEST(css_nest_second_level_subject_merge);
    RUN_TEST(css_nest_second_level_group_arms);
    RUN_TEST(css_nest_second_level_sibling_order);
    RUN_TEST(css_nest_second_level_rejects_malformed);
    RUN_TEST(css_nest_marker_trailing_subject_form);
    RUN_TEST(css_nest_marker_trailing_parent_ancestors_shift);
    RUN_TEST(css_nest_marker_mid_chain);
    RUN_TEST(css_nest_marker_mid_chain_direct_edges);
    RUN_TEST(css_nest_marker_position_rejects_malformed);
    RUN_TEST(css_nest_third_level_chains);
    RUN_TEST(css_nest_third_level_mixed_subject_merges);
    RUN_TEST(css_nest_fourth_level_rejects);
    RUN_TEST(css_nest_media_merges_matching_declarations);
    RUN_TEST(css_nest_media_skips_non_matching);
    RUN_TEST(css_nest_media_hosts_nested_rules);
    RUN_TEST(css_nest_supports_in_rule);
    RUN_TEST(css_nest_conditional_rejects_malformed);
    RUN_TEST(css_nest_non_conditional_at_rules_have_dedicated_signature);
    RUN_TEST(css_scope_subject_state_form_styles_root);
    RUN_TEST(css_scope_subject_state_form_root_list);
    RUN_TEST(css_scope_subject_state_rejects_malformed);
    RUN_TEST(css_scope_subject_class_form_filters_root);
    RUN_TEST(css_scope_subject_class_form_merges_root_classes_and_state);
    RUN_TEST(css_scope_subject_qual_rejects_malformed);
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
    RUN_TEST(css_supports_selector_function_evaluates_grammar_support);
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
    RUN_TEST(css_conditional_media_supports_aspect_ratio);
    RUN_TEST(css_conditional_media_supports_aspect_ratio_range);
    RUN_TEST(css_conditional_media_supports_only_modifier);
    RUN_TEST(css_conditional_media_supports_mq4_boolean_logic);
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
    RUN_TEST(css_anonymous_layers_get_unique_orders);
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
