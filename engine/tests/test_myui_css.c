#include "test_framework.h"

#include <string.h>

#include "myui/my_css.h"
#include "myui/my_theme.h"
#include "myui/my_widget.h"

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

TEST_MAIN_BEGIN()
    RUN_TEST(css_universal_selector_applies_to_any_widget);
    RUN_TEST(css_multiple_classes_match_as_a_set);
    RUN_TEST(css_same_specificity_uses_later_source_rule);
    RUN_TEST(css_class_selector_is_safe_without_widget_classes);
    RUN_TEST(css_child_combinator_matches_only_direct_parent);
    RUN_TEST(css_child_parent_classes_match_as_a_set);
    RUN_TEST(css_rejects_dangling_and_repeated_combinators);
    RUN_TEST(css_rejects_adjacent_selector_tokens_without_combinator);
    RUN_TEST(css_comments_preserve_descendant_separator);
TEST_MAIN_END()
