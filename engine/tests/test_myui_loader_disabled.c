#include "test_framework.h"

#include <string.h>

#include "myui/my_ui_loader.h"

TEST(yaml_loader_disabled_reports_no_yaml_capability)
{
  const my_ui_loader_capabilities_t* capabilities =
      my_ui_loader_capabilities();

  ASSERT_TRUE(capabilities != NULL);
  ASSERT_EQ(capabilities->supported_features, 0u);
  ASSERT_EQ(my_ui_loader_register("disabled_widget", NULL), MY_RET_NOT_SUPPORTED);
}

TEST(yaml_loader_disabled_rejects_load_without_touching_error)
{
  my_ui_error_t error;
  my_widget_t* widget;

  memset(&error, 0, sizeof(error));
  widget = my_ui_load_str(NULL, NULL, "type: button\n", &error);
  ASSERT_TRUE(widget == NULL);
  ASSERT_EQ(error.code, MY_UI_ERROR_NONE);
  ASSERT_EQ(error.message[0], '\0');
}

TEST_MAIN_BEGIN()
  RUN_TEST(yaml_loader_disabled_reports_no_yaml_capability);
  RUN_TEST(yaml_loader_disabled_rejects_load_without_touching_error);
TEST_MAIN_END()
