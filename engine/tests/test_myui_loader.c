#include "test_framework.h"

#include <math.h>
#include <stdatomic.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#if !defined(_WIN32) && !defined(ENGINE_PLATFORM_WINDOWS)
#include <sched.h>
#endif

#include "core/platform_thread.h"
#include "myc/my_mem.h"
#include "myc/my_str.h"
#include "myc/myconf/my_conf.h"
#include "mypal/dummy/my_pal_dummy.h"
#include "myui/my_ui_loader.h"
#include "myui/my_widget_class.h"
#include "myui/widgets/my_button.h"
#include "myui/widgets/my_label.h"

typedef struct loader_alloc_state_t {
  size_t alloc_calls;
  size_t fail_at;
} loader_alloc_state_t;

static size_t loader_factory_calls;

static void* loader_test_alloc(void* context, size_t size)
{
  loader_alloc_state_t* state = (loader_alloc_state_t*)context;
  state->alloc_calls++;
  if (state->fail_at != 0u && state->alloc_calls == state->fail_at) {
    return NULL;
  }
  return malloc(size);
}

static void* loader_test_calloc(void* context, size_t count, size_t size)
{
  loader_alloc_state_t* state = (loader_alloc_state_t*)context;
  state->alloc_calls++;
  if (state->fail_at != 0u && state->alloc_calls == state->fail_at) {
    return NULL;
  }
  return calloc(count, size);
}

static void* loader_test_realloc(void* context, void* memory, size_t size)
{
  loader_alloc_state_t* state = (loader_alloc_state_t*)context;
  state->alloc_calls++;
  if (state->fail_at != 0u && state->alloc_calls == state->fail_at) {
    return NULL;
  }
  return realloc(memory, size);
}

static void loader_test_free(void* context, void* memory)
{
  (void)context;
  free(memory);
}

static my_widget_t* loader_custom_factory(const my_allocator_t* allocator,
                                          const my_conf_node_t* node)
{
  (void)node;
  loader_factory_calls++;
  return my_widget_create(allocator, "custom_loader_widget");
}

static my_widget_class_module_t* module_callback_owner;
static my_ret_t module_callback_unload_result;
static my_widget_class_module_t* loader_module_callback_owner;
static my_ret_t loader_module_callback_unload_result;
static my_widget_class_module_t* loader_migration_module_owner;
static my_ret_t loader_migration_module_unload_result;

static my_widget_t* module_callback_factory(const my_allocator_t* allocator)
{
  module_callback_unload_result =
      my_widget_class_module_begin_unload(module_callback_owner);
  return my_widget_create(allocator, "runtime_module_callback_widget");
}

static my_widget_t* loader_module_factory(const my_allocator_t* allocator,
                                          const my_conf_node_t* node)
{
  (void)node;
  loader_module_callback_unload_result =
      my_widget_class_module_begin_unload(loader_module_callback_owner);
  return my_widget_create(allocator, "runtime_loader_module_widget");
}

static my_ret_t loader_module_migrate(const my_allocator_t* allocator,
                                      my_conf_node_t* node,
                                      uint32_t from_version,
                                      uint32_t to_version)
{
  (void)allocator;
  (void)node;
  (void)from_version;
  (void)to_version;
  loader_migration_module_unload_result =
      my_widget_class_module_begin_unload(loader_migration_module_owner);
  return MY_RET_OK;
}

static my_ret_t loader_property_reenter_result;
static my_ret_t loader_property_failure_reenter_result;

static my_ret_t loader_property_reenter_set(my_widget_t* widget,
                                             const my_value_t* value)
{
  (void)widget;
  (void)value;
  loader_property_reenter_result = my_ui_loader_runtime_register_schema(
      "property_reentry_child", loader_custom_factory, NULL, NULL);
  return MY_RET_OK;
}

static my_ret_t loader_property_failure_set(my_widget_t* widget,
                                             const my_value_t* value)
{
  (void)widget;
  (void)value;
  loader_property_failure_reenter_result = my_ui_loader_runtime_register_schema(
      "property_failure_child", loader_custom_factory, NULL, NULL);
  return MY_RET_FAIL;
}

static my_value_type_t loader_color_value_type;
static uint32_t loader_color_value;

static my_ret_t loader_color_set(my_widget_t* widget,
                                 const my_value_t* value)
{
  (void)widget;
  loader_color_value_type = my_value_type(value);
  loader_color_value = my_value_get_uint32(value);
  return loader_color_value_type == MY_VALUE_UINT32 ? MY_RET_OK : MY_RET_FAIL;
}

static my_ret_t loader_recursive_register_result;
static my_ret_t loader_recursive_class_register_result;
static my_ret_t loader_recursive_freeze_result;
static my_ret_t loader_recursive_runtime_register_result;
static my_ret_t loader_recursive_runtime_unregister_result;
static my_widget_t* class_registry_factory(const my_allocator_t* allocator);

static const my_widget_class_t LOADER_RECURSIVE_CLASS = {
    "recursive_class_widget", class_registry_factory, NULL, NULL, NULL};

static my_widget_t* loader_recursive_register_factory(
    const my_allocator_t* allocator, const my_conf_node_t* node)
{
  static const my_prop_desc_t properties[] = {
      {"runtime_reentry", MY_PROP_STRING, NULL, NULL},
      {NULL, MY_PROP_STRING, NULL, NULL}};
  (void)node;
  loader_recursive_register_result =
      my_ui_loader_register("recursive_child_widget", loader_custom_factory);
  loader_recursive_class_register_result =
      my_widget_class_register(&LOADER_RECURSIVE_CLASS);
  loader_recursive_freeze_result = my_widget_class_freeze();
  loader_recursive_runtime_register_result = my_ui_loader_runtime_register_schema(
      "runtime_reentry_widget", loader_custom_factory, properties, NULL);
  loader_recursive_runtime_unregister_result =
      my_ui_loader_runtime_unregister("runtime_reentry_widget");
  return my_widget_create(allocator, "recursive_loader_widget");
}

static my_widget_t* class_registry_factory(const my_allocator_t* allocator)
{
  return my_widget_create(allocator, "class_registry_widget");
}

static const my_prop_desc_t LOADER_CUSTOM_PROPERTIES[] = {
    {"caption", MY_PROP_STRING, NULL, NULL},
    {"priority", MY_PROP_INT, NULL, NULL},
    {NULL, MY_PROP_STRING, NULL, NULL}};

static const char* const LOADER_CUSTOM_EVENTS[] = {"activate", NULL};

static size_t loader_migration_calls;
static size_t loader_migration_factory_calls;
static int64_t loader_migration_seen_version;
static bool loader_migration_fail;
static bool loader_migration_oom;
static bool loader_migration_write_newer;
static size_t loader_migration_fail_at;
static bool loader_migration_reenter_registry;
static my_ret_t loader_migration_reenter_result;

static my_widget_t* loader_migration_factory(const my_allocator_t* allocator,
                                             const my_conf_node_t* node)
{
  loader_migration_factory_calls++;
  loader_migration_seen_version =
      my_conf_get_int64((my_conf_node_t*)node, "version", -1);
  return my_label_create(allocator,
                         my_conf_get_str((my_conf_node_t*)node, "text", ""));
}

static my_ret_t loader_migrate_caption(const my_allocator_t* allocator,
                                       my_conf_node_t* node,
                                       uint32_t from_version,
                                       uint32_t to_version)
{
  my_conf_node_t* caption;
  (void)allocator;
  loader_migration_calls++;
  if (loader_migration_reenter_registry) {
    loader_migration_reenter_result = my_ui_loader_register(
        "migration_recursive_child_widget", loader_custom_factory);
  }
  if (loader_migration_oom) {
    return MY_RET_OOM;
  }
  if (loader_migration_fail || loader_migration_fail_at == loader_migration_calls ||
      from_version != 0u || to_version != 1u) {
    return MY_RET_FAIL;
  }
  caption = my_conf_object_take(node, "caption");
  if (caption == NULL || my_conf_object_set(node, "text", caption) != MY_RET_OK) {
    my_conf_destroy(caption);
    return MY_RET_FAIL;
  }
  if (loader_migration_write_newer) {
    my_conf_node_t* version = my_conf_new_int64(allocator, 2);
    if (version == NULL ||
        my_conf_object_set(node, "version", version) != MY_RET_OK) {
      my_conf_destroy(version);
      return MY_RET_OOM;
    }
  }
  return MY_RET_OK;
}

static const my_prop_desc_t LOADER_MIGRATED_PROPERTIES[] = {
    {"text", MY_PROP_STRING, NULL, NULL},
    {NULL, MY_PROP_STRING, NULL, NULL}};

static size_t loader_chain_calls;
static int64_t loader_chain_seen_version;

static my_widget_t* loader_chain_factory(const my_allocator_t* allocator,
                                         const my_conf_node_t* node)
{
  loader_chain_seen_version =
      my_conf_get_int64((my_conf_node_t*)node, "version", -1);
  return my_label_create(allocator,
                         my_conf_get_str((my_conf_node_t*)node, "label", ""));
}

static my_ret_t loader_migrate_caption_to_text(
    const my_allocator_t* allocator, my_conf_node_t* node,
    uint32_t from_version, uint32_t to_version)
{
  my_conf_node_t* value;
  (void)allocator;
  loader_chain_calls++;
  if (from_version != 0u || to_version != 1u) return MY_RET_FAIL;
  value = my_conf_object_take(node, "caption");
  if (value == NULL || my_conf_object_set(node, "text", value) != MY_RET_OK) {
    my_conf_destroy(value);
    return MY_RET_FAIL;
  }
  return MY_RET_OK;
}

static my_ret_t loader_migrate_text_to_label(
    const my_allocator_t* allocator, my_conf_node_t* node,
    uint32_t from_version, uint32_t to_version)
{
  my_conf_node_t* value;
  (void)allocator;
  loader_chain_calls++;
  if (from_version != 1u || to_version != 2u) return MY_RET_FAIL;
  value = my_conf_object_take(node, "text");
  if (value == NULL || my_conf_object_set(node, "label", value) != MY_RET_OK) {
    my_conf_destroy(value);
    return MY_RET_FAIL;
  }
  return MY_RET_OK;
}

static const my_prop_desc_t LOADER_CHAIN_PROPERTIES[] = {
    {"label", MY_PROP_STRING, NULL, NULL},
    {NULL, MY_PROP_STRING, NULL, NULL}};

static atomic_bool class_lookup_thread_failed;

static atomic_bool class_runtime_writer_done;
static atomic_bool class_runtime_concurrent_failed;
static atomic_bool class_lease_unregister_started;
static atomic_bool class_lease_unregister_done;
static my_ret_t class_lease_unregister_result;
static atomic_bool class_lease_replace_started;
static atomic_bool class_lease_replace_done;
static my_ret_t class_lease_replace_result;
static my_widget_class_lease_t* class_foreign_release_lease;
static atomic_bool class_foreign_release_done;
static atomic_bool class_subtree_replace_started;
static atomic_bool class_subtree_replace_done;
static my_ret_t class_subtree_replace_result;
static atomic_bool loader_runtime_writer_done;
static atomic_bool loader_runtime_concurrent_failed;

static PLATFORM_THREAD_RET class_lease_unregister_thread(
    PLATFORM_THREAD_ARG argument)
{
  const char* type = argument != NULL ? (const char*)argument
                                      : "runtime_leased_widget";
  atomic_store_explicit(&class_lease_unregister_started, true,
                        memory_order_release);
  class_lease_unregister_result = my_widget_class_runtime_unregister(
      type);
  atomic_store_explicit(&class_lease_unregister_done, true,
                        memory_order_release);
  return PLATFORM_THREAD_RETURN;
}

static PLATFORM_THREAD_RET class_lease_replace_thread(
    PLATFORM_THREAD_ARG argument)
{
  static const my_prop_desc_t properties[] = {
      {"replacement_lease_property", MY_PROP_STRING, NULL, NULL},
      {NULL, MY_PROP_STRING, NULL, NULL}};
  static const my_widget_class_t replacement = {
      "runtime_leased_widget", class_registry_factory, properties, NULL, NULL};
  (void)argument;
  atomic_store_explicit(&class_lease_replace_started, true,
                        memory_order_release);
  class_lease_replace_result = my_widget_class_runtime_register(&replacement);
  atomic_store_explicit(&class_lease_replace_done, true,
                        memory_order_release);
  return PLATFORM_THREAD_RETURN;
}

static PLATFORM_THREAD_RET class_foreign_release_thread(
    PLATFORM_THREAD_ARG argument)
{
  (void)argument;
  my_widget_class_release(class_foreign_release_lease);
  atomic_store_explicit(&class_foreign_release_done, true,
                        memory_order_release);
  return PLATFORM_THREAD_RETURN;
}

static PLATFORM_THREAD_RET class_subtree_replace_thread(
    PLATFORM_THREAD_ARG argument)
{
  static const my_widget_class_t replacement = {
      "runtime_subtree_widget", class_registry_factory, NULL, NULL, NULL};
  (void)argument;
  atomic_store_explicit(&class_subtree_replace_started, true,
                        memory_order_release);
  class_subtree_replace_result =
      my_widget_class_runtime_register(&replacement);
  atomic_store_explicit(&class_subtree_replace_done, true,
                        memory_order_release);
  return PLATFORM_THREAD_RETURN;
}

static PLATFORM_THREAD_RET class_subtree_load_thread(
    PLATFORM_THREAD_ARG argument)
{
  my_ui_error_t error = {0};
  my_widget_t* widget;
  (void)argument;
  widget = my_ui_load_str(
      NULL, NULL,
      "type: runtime_subtree_widget\n"
      "children:\n"
      "  - type: blocking_loader_widget\n",
      &error);
  if (widget != NULL) my_widget_unref(widget);
  return PLATFORM_THREAD_RETURN;
}

static void loader_test_yield(void)
{
#if defined(_WIN32) || defined(ENGINE_PLATFORM_WINDOWS)
  Sleep(0);
#else
  sched_yield();
#endif
}

static PLATFORM_THREAD_RET class_runtime_writer_thread(
    PLATFORM_THREAD_ARG argument)
{
  static const my_prop_desc_t first_properties[] = {
      {"runtime_concurrent_first", MY_PROP_STRING, NULL, NULL},
      {NULL, MY_PROP_STRING, NULL, NULL}};
  static const my_prop_desc_t second_properties[] = {
      {"runtime_concurrent_second", MY_PROP_INT, NULL, NULL},
      {NULL, MY_PROP_STRING, NULL, NULL}};
  const my_widget_class_t first = {
      "runtime_concurrent_widget", class_registry_factory, first_properties,
      NULL, NULL};
  const my_widget_class_t second = {
      "runtime_concurrent_widget", class_registry_factory, second_properties,
      NULL, NULL};
  size_t i;
  (void)argument;
  for (i = 0u; i < 32u; i++) {
    if (my_widget_class_runtime_register(i % 2u == 0u ? &first : &second) !=
        MY_RET_OK) {
      atomic_store_explicit(&class_runtime_concurrent_failed, true,
                            memory_order_release);
      break;
    }
  }
  atomic_store_explicit(&class_runtime_writer_done, true, memory_order_release);
  return PLATFORM_THREAD_RETURN;
}

static PLATFORM_THREAD_RET class_runtime_reader_thread(
    PLATFORM_THREAD_ARG argument)
{
  size_t i;
  (void)argument;
  for (i = 0u; i < 10000u; i++) {
    const my_widget_class_t *cls =
        my_widget_class_find("runtime_concurrent_widget");
    if (cls == NULL || cls->props == NULL || cls->props[0].name == NULL ||
        (!my_str_eq(cls->props[0].name, "runtime_concurrent_first") &&
         !my_str_eq(cls->props[0].name, "runtime_concurrent_second"))) {
      atomic_store_explicit(&class_runtime_concurrent_failed, true,
                            memory_order_release);
      break;
    }
  }
  return PLATFORM_THREAD_RETURN;
}

static PLATFORM_THREAD_RET loader_runtime_writer_thread(
    PLATFORM_THREAD_ARG argument)
{
  static const my_prop_desc_t first_properties[] = {
      {"loader_runtime_first", MY_PROP_STRING, NULL, NULL},
      {NULL, MY_PROP_STRING, NULL, NULL}};
  static const my_prop_desc_t second_properties[] = {
      {"loader_runtime_second", MY_PROP_INT, NULL, NULL},
      {NULL, MY_PROP_STRING, NULL, NULL}};
  (void)argument;
  for (size_t i = 0u; i < 32u; ++i) {
    const my_prop_desc_t* properties =
        i % 2u == 0u ? first_properties : second_properties;
    if (my_ui_loader_runtime_register_schema(
            "custom_loader_widget", loader_custom_factory, properties,
            NULL) != MY_RET_OK) {
      atomic_store_explicit(&loader_runtime_concurrent_failed, true,
                            memory_order_release);
      break;
    }
  }
  atomic_store_explicit(&loader_runtime_writer_done, true,
                        memory_order_release);
  return PLATFORM_THREAD_RETURN;
}

static PLATFORM_THREAD_RET loader_runtime_reader_thread(
    PLATFORM_THREAD_ARG argument)
{
  (void)argument;
  for (size_t i = 0u; i < 10000u; ++i) {
    my_ui_type_info_t info;
    if (my_ui_loader_query_type("custom_loader_widget", &info) !=
            MY_RET_OK ||
        (info.property_count != 1u && info.property_count != 0u) ||
        (info.property_count == 1u && info.properties == NULL)) {
      atomic_store_explicit(&loader_runtime_concurrent_failed, true,
                            memory_order_release);
      break;
    }
  }
  return PLATFORM_THREAD_RETURN;
}

static PLATFORM_THREAD_RET class_lookup_thread(PLATFORM_THREAD_ARG argument)
{
  size_t i;
  (void)argument;
  for (i = 0u; i < 1000u; i++) {
    if (my_widget_class_find("button") == NULL ||
        my_widget_class_find("label") == NULL) {
      atomic_store_explicit(&class_lookup_thread_failed, true,
                            memory_order_release);
      break;
    }
  }
  return PLATFORM_THREAD_RETURN;
}

static atomic_bool loader_blocking_factory_entered;
static atomic_bool loader_blocking_factory_release;
static atomic_bool loader_replacement_started;
static atomic_bool loader_replacement_done;
static my_ret_t loader_replacement_result;
static my_ret_t loader_runtime_replacement_result;
static my_widget_class_module_t* loader_bind_race_module;
static atomic_bool loader_bind_race_factory_entered;
static atomic_bool loader_bind_race_factory_release;
static atomic_bool loader_bind_race_load_failed;
static my_ret_t loader_bind_race_unload_result;

static my_widget_t* loader_blocking_factory(const my_allocator_t* allocator,
                                            const my_conf_node_t* node)
{
  (void)node;
  atomic_store_explicit(&loader_blocking_factory_entered, true,
                        memory_order_release);
  while (!atomic_load_explicit(&loader_replacement_started,
                               memory_order_acquire) ||
         !atomic_load_explicit(&loader_blocking_factory_release,
                               memory_order_acquire)) {
  }
  return my_widget_create(allocator, "blocking_loader_widget");
}

static PLATFORM_THREAD_RET loader_blocking_load_thread(
    PLATFORM_THREAD_ARG argument)
{
  my_ui_error_t error = {0};
  my_widget_t* widget;
  (void)argument;
  widget = my_ui_load_str_ex(NULL, NULL, "type: blocking_loader_widget\n",
                             MY_UI_LOAD_DEFAULT, &error);
  if (widget != NULL) my_widget_unref(widget);
  return PLATFORM_THREAD_RETURN;
}

static PLATFORM_THREAD_RET loader_replacement_thread(
    PLATFORM_THREAD_ARG argument)
{
  static const my_prop_desc_t properties[] = {
      {"replacement_live", MY_PROP_STRING, NULL, NULL},
      {NULL, MY_PROP_STRING, NULL, NULL}};
  my_ui_dynamic_schema_t schema = {properties, 1u, NULL, 0u};
  (void)argument;
  atomic_store_explicit(&loader_replacement_started, true,
                        memory_order_release);
  loader_replacement_result = my_ui_loader_register_dynamic_schema(
      NULL, "blocking_loader_widget", loader_custom_factory, &schema, 1u,
      NULL);
  atomic_store_explicit(&loader_replacement_done, true, memory_order_release);
  return PLATFORM_THREAD_RETURN;
}

static PLATFORM_THREAD_RET loader_runtime_replacement_thread(
    PLATFORM_THREAD_ARG argument)
{
  static const my_prop_desc_t properties[] = {
      {"runtime_replacement", MY_PROP_STRING, NULL, NULL},
      {NULL, MY_PROP_STRING, NULL, NULL}};
  (void)argument;
  atomic_store_explicit(&loader_replacement_started, true,
                        memory_order_release);
  loader_runtime_replacement_result = my_ui_loader_runtime_register_schema(
      "blocking_loader_widget", loader_custom_factory, properties, NULL);
  atomic_store_explicit(&loader_replacement_done, true, memory_order_release);
  return PLATFORM_THREAD_RETURN;
}

static my_widget_t* loader_bind_race_factory(
    const my_allocator_t* allocator, const my_conf_node_t* node)
{
  (void)node;
  atomic_store_explicit(&loader_bind_race_factory_entered, true,
                        memory_order_release);
  while (!atomic_load_explicit(&loader_bind_race_factory_release,
                               memory_order_acquire)) {
    platform_thread_yield();
  }
  return my_widget_create(allocator, "loader_bind_race_widget");
}

static PLATFORM_THREAD_RET loader_bind_race_unload_thread(
    PLATFORM_THREAD_ARG argument)
{
  (void)argument;
  while (!atomic_load_explicit(&loader_bind_race_factory_entered,
                               memory_order_acquire)) {
    platform_thread_yield();
  }
  loader_bind_race_unload_result =
      my_widget_class_module_begin_unload(loader_bind_race_module);
  atomic_store_explicit(&loader_bind_race_factory_release, true,
                        memory_order_release);
  return PLATFORM_THREAD_RETURN;
}

static PLATFORM_THREAD_RET loader_bind_race_load_thread(
    PLATFORM_THREAD_ARG argument)
{
  my_ui_error_t error = {0};
  my_widget_t* widget;
  (void)argument;
  widget = my_ui_load_str(NULL, NULL, "type: loader_bind_race_widget\n",
                          &error);
  atomic_store_explicit(&loader_bind_race_load_failed, widget == NULL,
                        memory_order_release);
  if (widget != NULL) my_widget_unref(widget);
  return PLATFORM_THREAD_RETURN;
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

TEST(yaml_loader_applies_button_cooldown)
{
  const char* yaml = "type: button\ntext: Send\ncooldown: 1250\n";
  my_ui_error_t error = {0};
  my_ui_type_info_t info = {0};
  my_widget_t* widget;

  ASSERT_EQ(my_ui_loader_query_type("button", &info), MY_RET_OK);
  ASSERT_TRUE(info.property_count >= 2u);
  widget = my_ui_load_str_ex(NULL, NULL, yaml, MY_UI_LOAD_STRICT_SCHEMA,
                             &error);
  ASSERT_NOT_NULL(widget);
  ASSERT_EQ(((my_button_t*)widget)->cooldown_ms, 1250u);
  my_widget_unref(widget);

  memset(&error, 0, sizeof(error));
  widget = my_ui_load_str_ex(NULL, NULL,
                             "type: button\ntext: Send\ncooldown: -1\n",
                             MY_UI_LOAD_STRICT_SCHEMA, &error);
  ASSERT_TRUE(widget == NULL);
  ASSERT_TRUE(error.message[0] != '\0');
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

TEST(yaml_loader_capability_registry_is_static_and_explicit)
{
  const my_ui_loader_capabilities_t* first = my_ui_loader_capabilities();
  const my_ui_loader_capabilities_t* second = my_ui_loader_capabilities();

  ASSERT_NOT_NULL(first);
  ASSERT_TRUE(first == second);
  ASSERT_EQ(first->max_yaml_bytes, (size_t)MY_UI_MAX_YAML_BYTES);
  ASSERT_EQ(first->max_factories, 32u);
  ASSERT_EQ(first->max_bind_rule_bytes, 512u);
  ASSERT_TRUE((first->supported_features & MY_UI_FEATURE_YAML_SCHEMA) != 0u);
  ASSERT_TRUE((first->supported_features & MY_UI_FEATURE_CHILDREN) != 0u);
  ASSERT_TRUE((first->supported_features & MY_UI_FEATURE_TYPE_QUERY) != 0u);
  ASSERT_TRUE((first->supported_features & MY_UI_FEATURE_DYNAMIC_SCHEMA) != 0u);
  ASSERT_EQ(first->supported_features,
            (uint32_t)(MY_UI_FEATURE_YAML_SCHEMA | MY_UI_FEATURE_CHILDREN |
                       MY_UI_FEATURE_BINDINGS | MY_UI_FEATURE_CSS_STYLE |
                       MY_UI_FEATURE_TYPE_QUERY |
                       MY_UI_FEATURE_SCHEMA_MIGRATION |
                       MY_UI_FEATURE_DYNAMIC_SCHEMA));
}

TEST(yaml_loader_schema_migration_is_transactional)
{
  my_ui_type_info_t info;
  my_ui_error_t error = {0};
  my_widget_t* widget;
  my_label_t* label;
  const char* yaml =
      "type: migrating_loader_widget\n"
      "version: 0\n"
      "caption: Migrated\n";

  loader_migration_calls = 0u;
  loader_migration_seen_version = -1;
  loader_migration_fail = false;
  loader_migration_oom = false;
  loader_migration_write_newer = false;
  loader_migration_fail_at = 0u;
  ASSERT_EQ(my_ui_loader_register_schema_ex(
                "migrating_loader_widget", loader_migration_factory,
                LOADER_MIGRATED_PROPERTIES, NULL, 1u,
                loader_migrate_caption),
            MY_RET_OK);
  ASSERT_EQ(my_ui_loader_query_type("migrating_loader_widget", &info),
            MY_RET_OK);
  ASSERT_EQ(info.schema_version, 1u);
  ASSERT_TRUE(info.migration_supported);
  widget = my_ui_load_str_ex(NULL, NULL, yaml, MY_UI_LOAD_STRICT_SCHEMA,
                             &error);
  ASSERT_NOT_NULL(widget);
  ASSERT_EQ(loader_migration_calls, 1u);
  ASSERT_EQ(loader_migration_seen_version, 1);
  label = (my_label_t*)widget;
  ASSERT_STR_EQ(label->text, "Migrated");
  my_widget_unref(widget);

  memset(&error, 0, sizeof(error));
  loader_migration_fail = true;
  loader_migration_oom = false;
  loader_migration_write_newer = false;
  loader_migration_fail_at = 0u;
  ASSERT_TRUE(my_ui_load_str_ex(NULL, NULL, yaml, MY_UI_LOAD_STRICT_SCHEMA,
                                &error) == NULL);
  ASSERT_EQ(loader_migration_calls, 2u);
  ASSERT_EQ(error.code, MY_UI_ERROR_SCHEMA);
  loader_migration_fail = false;
}

TEST(yaml_loader_schema_migration_rejects_newer_version)
{
  my_ui_error_t error = {0};
  const char* yaml =
      "type: migrating_loader_widget\n"
      "version: 2\n";

  loader_migration_calls = 0u;
  ASSERT_TRUE(my_ui_load_str_ex(NULL, NULL, yaml, MY_UI_LOAD_STRICT_SCHEMA,
                                &error) == NULL);
  ASSERT_EQ(loader_migration_calls, 0u);
  ASSERT_EQ(error.code, MY_UI_ERROR_SCHEMA);
  ASSERT_STR_EQ(error.field, "version");
}

TEST(yaml_loader_schema_migrates_nested_nodes_before_any_factory)
{
  const char* yaml =
      "type: migrating_loader_widget\n"
      "version: 0\n"
      "caption: Root\n"
      "children:\n"
      "  - type: migrating_loader_widget\n"
      "    version: 0\n"
      "    caption: Child\n";
  my_ui_error_t error = {0};
  my_widget_t* widget;
  my_widget_t* child;

  loader_migration_calls = 0u;
  loader_migration_factory_calls = 0u;
  loader_migration_seen_version = -1;
  loader_migration_fail = false;
  loader_migration_oom = false;
  loader_migration_write_newer = false;
  loader_migration_fail_at = 0u;
  widget = my_ui_load_str_ex(NULL, NULL, yaml, MY_UI_LOAD_STRICT_SCHEMA,
                             &error);
  ASSERT_NOT_NULL(widget);
  ASSERT_EQ(loader_migration_calls, 2u);
  ASSERT_EQ(loader_migration_factory_calls, 2u);
  ASSERT_EQ(my_widget_child_count(widget), 1u);
  ASSERT_STR_EQ(((my_label_t*)widget)->text, "Root");
  child = (my_widget_t*)my_darray_get(widget->children, 0u);
  ASSERT_NOT_NULL(child);
  ASSERT_STR_EQ(((my_label_t*)child)->text, "Child");
  my_widget_unref(widget);
}

TEST(yaml_loader_nested_migration_failure_is_transactional)
{
  const char* yaml =
      "type: migrating_loader_widget\n"
      "version: 0\n"
      "caption: Root\n"
      "children:\n"
      "  - type: migrating_loader_widget\n"
      "    version: 0\n"
      "    caption: Child\n";
  my_ui_error_t error = {0};

  loader_migration_calls = 0u;
  loader_migration_factory_calls = 0u;
  loader_migration_fail = false;
  loader_migration_oom = false;
  loader_migration_write_newer = false;
  loader_migration_fail_at = 2u;
  ASSERT_TRUE(my_ui_load_str_ex(NULL, NULL, yaml, MY_UI_LOAD_STRICT_SCHEMA,
                                &error) == NULL);
  ASSERT_EQ(loader_migration_calls, 2u);
  ASSERT_EQ(loader_migration_factory_calls, 0u);
  ASSERT_EQ(error.code, MY_UI_ERROR_SCHEMA);
  ASSERT_STR_EQ(error.field, "version");
  ASSERT_STR_EQ(error.path, "children[0].version");
  loader_migration_fail_at = 0u;
}

TEST(yaml_loader_migration_oom_is_transactional)
{
  const char* yaml =
      "type: migrating_loader_widget\n"
      "version: 0\n"
      "caption: OOM\n";
  my_ui_error_t error = {0};

  loader_migration_calls = 0u;
  loader_migration_factory_calls = 0u;
  loader_migration_fail = false;
  loader_migration_oom = true;
  loader_migration_write_newer = false;
  loader_migration_fail_at = 0u;
  ASSERT_TRUE(my_ui_load_str_ex(NULL, NULL, yaml, MY_UI_LOAD_STRICT_SCHEMA,
                                &error) == NULL);
  ASSERT_EQ(loader_migration_calls, 1u);
  ASSERT_EQ(loader_migration_factory_calls, 0u);
  ASSERT_EQ(error.code, MY_UI_ERROR_RESOURCE);
  ASSERT_STR_EQ(error.field, "version");
  loader_migration_oom = false;
}

TEST(yaml_loader_migration_cannot_bypass_version_guard)
{
  const char* yaml =
      "type: migrating_loader_widget\n"
      "version: 0\n"
      "caption: Future\n";
  my_ui_error_t error = {0};

  loader_migration_calls = 0u;
  loader_migration_factory_calls = 0u;
  loader_migration_fail = false;
  loader_migration_oom = false;
  loader_migration_write_newer = true;
  loader_migration_fail_at = 0u;
  ASSERT_TRUE(my_ui_load_str_ex(NULL, NULL, yaml, MY_UI_LOAD_STRICT_SCHEMA,
                                &error) == NULL);
  ASSERT_EQ(loader_migration_calls, 1u);
  ASSERT_EQ(loader_migration_factory_calls, 0u);
  ASSERT_EQ(error.code, MY_UI_ERROR_SCHEMA);
  ASSERT_STR_EQ(error.field, "version");
  loader_migration_write_newer = false;
}

TEST(yaml_loader_runs_bounded_schema_migration_chain)
{
  const my_ui_schema_migration_t migrations[] = {
      {0u, 1u, loader_migrate_caption_to_text},
      {1u, 2u, loader_migrate_text_to_label}};
  const char* yaml =
      "type: chained_loader_widget\n"
      "version: 0\n"
      "caption: Chained\n";
  my_ui_error_t error = {0};
  my_ui_type_info_t info;
  my_widget_t* widget;

  ASSERT_EQ(my_ui_loader_register_schema_chain(
                "chained_loader_widget", loader_chain_factory,
                LOADER_CHAIN_PROPERTIES, NULL, 2u, migrations, 2u),
            MY_RET_OK);
  ASSERT_EQ(my_ui_loader_query_type("chained_loader_widget", &info),
            MY_RET_OK);
  ASSERT_EQ(info.schema_version, 2u);
  ASSERT_TRUE(info.migration_supported);
  loader_chain_calls = 0u;
  loader_chain_seen_version = -1;
  widget = my_ui_load_str_ex(NULL, NULL, yaml, MY_UI_LOAD_STRICT_SCHEMA,
                             &error);
  ASSERT_NOT_NULL(widget);
  ASSERT_EQ(loader_chain_calls, 2u);
  ASSERT_EQ(loader_chain_seen_version, 2);
  ASSERT_STR_EQ(((my_label_t*)widget)->text, "Chained");
  my_widget_unref(widget);
}

TEST(yaml_loader_rejects_unavailable_schema_chain_path)
{
  const my_ui_schema_migration_t migrations[] = {
      {1u, 2u, loader_migrate_text_to_label}};
  const char* yaml =
      "type: partial_chain_widget\n"
      "version: 0\n"
      "caption: Unsupported\n";
  my_ui_error_t error = {0};

  ASSERT_EQ(my_ui_loader_register_schema_chain(
                "partial_chain_widget", loader_chain_factory,
                LOADER_CHAIN_PROPERTIES, NULL, 2u, migrations, 1u),
            MY_RET_OK);
  loader_chain_calls = 0u;
  ASSERT_TRUE(my_ui_load_str_ex(NULL, NULL, yaml, MY_UI_LOAD_STRICT_SCHEMA,
                                &error) == NULL);
  ASSERT_EQ(loader_chain_calls, 0u);
  ASSERT_EQ(error.code, MY_UI_ERROR_SCHEMA);
  ASSERT_STR_EQ(error.field, "version");
}

TEST(yaml_loader_rejects_invalid_schema_migration_chain_registration)
{
  const my_ui_schema_migration_t gap[] = {
      {0u, 2u, loader_migrate_caption_to_text}};
  const my_ui_schema_migration_t missing[] = {
      {1u, 2u, loader_migrate_text_to_label}};

  ASSERT_EQ(my_ui_loader_register_schema_chain(
                "invalid_gap_chain_widget", loader_chain_factory,
                LOADER_CHAIN_PROPERTIES, NULL, 2u, gap, 1u),
            MY_RET_INVALID_PARAMS);
  ASSERT_EQ(my_ui_loader_register_schema_chain(
                "invalid_empty_chain_widget", loader_chain_factory,
                LOADER_CHAIN_PROPERTIES, NULL, 2u, NULL, 0u),
            MY_RET_INVALID_PARAMS);
  ASSERT_EQ(my_ui_loader_register_schema_chain(
                "valid_partial_chain", loader_chain_factory,
                LOADER_CHAIN_PROPERTIES, NULL, 2u, missing, 1u),
            MY_RET_OK);
}

TEST(yaml_loader_type_query_exposes_builtin_schema)
{
  my_ui_type_info_t info;

  memset(&info, 0, sizeof(info));
  ASSERT_EQ(my_ui_loader_query_type("button", &info), MY_RET_OK);
  ASSERT_STR_EQ(info.type, "button");
  ASSERT_TRUE(info.schema_known);
  ASSERT_FALSE(info.factory_registered);
  ASSERT_EQ(info.common_property_count, 12u);
  ASSERT_STR_EQ(info.common_properties[0].name, "name");
  ASSERT_STR_EQ(info.common_properties[3].name, "x");
  ASSERT_STR_EQ(info.common_properties[10].name, "layout");
  ASSERT_EQ(info.property_count, 2u);
  ASSERT_STR_EQ(info.properties[0].name, "text");
  ASSERT_STR_EQ(info.properties[1].name, "cooldown");
  ASSERT_EQ(info.event_count, 1u);
  ASSERT_STR_EQ(info.events[0], "click");
  ASSERT_EQ(my_ui_loader_query_type("not-a-widget", &info),
            MY_RET_NOT_SUPPORTED);
  ASSERT_TRUE(info.type == NULL);
  ASSERT_EQ(info.property_count, 0u);
  ASSERT_EQ(info.common_property_count, 0u);
}

TEST(yaml_loader_type_query_exposes_window_root_schema)
{
  my_ui_type_info_t info;

  memset(&info, 0, sizeof(info));
  ASSERT_EQ(my_ui_loader_query_type("window", &info), MY_RET_OK);
  ASSERT_STR_EQ(info.type, "window");
  ASSERT_TRUE(info.schema_known);
  ASSERT_EQ(info.property_count, 2u);
  ASSERT_STR_EQ(info.properties[0].name, "title");
  ASSERT_STR_EQ(info.properties[1].name, "style");
  ASSERT_EQ(info.event_count, 0u);
}

TEST(yaml_loader_type_query_exposes_custom_factory_without_schema)
{
  my_ui_type_info_t info;

  ASSERT_EQ(my_ui_loader_register("custom_loader_widget",
                                  loader_custom_factory), MY_RET_OK);
  memset(&info, 0, sizeof(info));
  ASSERT_EQ(my_ui_loader_query_type("custom_loader_widget", &info), MY_RET_OK);
  ASSERT_STR_EQ(info.type, "custom_loader_widget");
  ASSERT_TRUE(info.factory_registered);
  ASSERT_FALSE(info.schema_known);
  ASSERT_EQ(info.property_count, 0u);
  ASSERT_EQ(info.event_count, 0u);
}

TEST(yaml_loader_custom_factory_schema_is_queryable_and_strict)
{
  const char* accepted =
      "type: schema_loader_widget\ncaption: Hello\npriority: 3\n";
  const char* rejected = "type: schema_loader_widget\nunknown: true\n";
  my_ui_type_info_t info;
  my_ui_error_t error = {0};
  my_widget_t* widget;

  ASSERT_EQ(my_ui_loader_register_schema("schema_loader_widget",
                                         loader_custom_factory,
                                         LOADER_CUSTOM_PROPERTIES,
                                         LOADER_CUSTOM_EVENTS), MY_RET_OK);
  ASSERT_EQ(my_ui_loader_query_type("schema_loader_widget", &info), MY_RET_OK);
  ASSERT_TRUE(info.factory_registered);
  ASSERT_TRUE(info.schema_known);
  ASSERT_EQ(info.property_count, 2u);
  ASSERT_STR_EQ(info.properties[0].name, "caption");
  ASSERT_EQ(info.event_count, 1u);
  ASSERT_STR_EQ(info.events[0], "activate");
  widget = my_ui_load_str_ex(NULL, NULL, accepted, MY_UI_LOAD_STRICT_SCHEMA,
                             &error);
  ASSERT_NOT_NULL(widget);
  my_widget_unref(widget);
  widget = my_ui_load_str_ex(NULL, NULL, rejected, MY_UI_LOAD_STRICT_SCHEMA,
                             &error);
  ASSERT_TRUE(widget == NULL);
  ASSERT_EQ(error.code, MY_UI_ERROR_SCHEMA);
  ASSERT_STR_EQ(error.field, "unknown");
  memset(&error, 0, sizeof(error));
  widget = my_ui_load_str_ex(NULL, NULL,
                             "type: schema_loader_widget\npriority: bad\n",
                             MY_UI_LOAD_STRICT_SCHEMA, &error);
  ASSERT_TRUE(widget == NULL);
  ASSERT_EQ(error.code, MY_UI_ERROR_SCHEMA);
  ASSERT_STR_EQ(error.field, "priority");
}

TEST(yaml_loader_factory_cannot_reenter_registry_write_path)
{
  my_ui_error_t error = {0};
  my_widget_t* widget;

  loader_recursive_register_result = MY_RET_FAIL;
  loader_recursive_class_register_result = MY_RET_FAIL;
  loader_recursive_freeze_result = MY_RET_FAIL;
  loader_recursive_runtime_register_result = MY_RET_FAIL;
  loader_recursive_runtime_unregister_result = MY_RET_FAIL;
  ASSERT_EQ(my_ui_loader_register("recursive_loader_widget",
                                 loader_recursive_register_factory),
            MY_RET_OK);
  widget = my_ui_load_str(NULL, NULL, "type: recursive_loader_widget\n",
                          &error);
  ASSERT_NOT_NULL(widget);
  ASSERT_EQ(loader_recursive_register_result, MY_RET_NOT_SUPPORTED);
  ASSERT_EQ(loader_recursive_class_register_result, MY_RET_NOT_SUPPORTED);
  ASSERT_EQ(loader_recursive_freeze_result, MY_RET_NOT_SUPPORTED);
  ASSERT_EQ(loader_recursive_runtime_register_result, MY_RET_NOT_SUPPORTED);
  ASSERT_EQ(loader_recursive_runtime_unregister_result, MY_RET_NOT_SUPPORTED);
  my_widget_unref(widget);
}

TEST(yaml_loader_migration_cannot_reenter_registry_write_path)
{
  const char* yaml =
      "type: migrating_loader_widget\n"
      "version: 0\n"
      "caption: Migrated\n";
  my_ui_error_t error = {0};
  my_widget_t* widget;

  loader_migration_calls = 0u;
  loader_migration_factory_calls = 0u;
  loader_migration_seen_version = -1;
  loader_migration_fail = false;
  loader_migration_oom = false;
  loader_migration_write_newer = false;
  loader_migration_fail_at = 0u;
  loader_migration_reenter_registry = true;
  loader_migration_reenter_result = MY_RET_FAIL;
  widget = my_ui_load_str_ex(NULL, NULL, yaml, MY_UI_LOAD_STRICT_SCHEMA,
                             &error);
  loader_migration_reenter_registry = false;
  ASSERT_NOT_NULL(widget);
  ASSERT_EQ(loader_migration_reenter_result, MY_RET_NOT_SUPPORTED);
  ASSERT_EQ(loader_migration_calls, 1u);
  ASSERT_EQ(loader_migration_factory_calls, 1u);
  ASSERT_STR_EQ(((my_label_t*)widget)->text, "Migrated");
  my_widget_unref(widget);
}

TEST(yaml_loader_property_cannot_reenter_registry_write_path)
{
  static const my_prop_desc_t properties[] = {
      {"reenter", MY_PROP_STRING, loader_property_reenter_set, NULL},
      {NULL, MY_PROP_STRING, NULL, NULL}};
  my_ui_error_t error = {0};
  my_widget_t* widget;

  loader_property_reenter_result = MY_RET_FAIL;
  ASSERT_EQ(my_ui_loader_runtime_register_schema(
                "property_reentry_widget", loader_custom_factory, properties,
                NULL),
            MY_RET_OK);
  widget = my_ui_load_str_ex(
      NULL, NULL, "type: property_reentry_widget\nreenter: value\n",
      MY_UI_LOAD_STRICT_SCHEMA, &error);
  ASSERT_NOT_NULL(widget);
  ASSERT_EQ(loader_property_reenter_result, MY_RET_NOT_SUPPORTED);
  my_widget_unref(widget);
  ASSERT_EQ(my_ui_loader_runtime_unregister("property_reentry_widget"),
            MY_RET_OK);
}

TEST(yaml_loader_typed_color_property_preserves_rgba32)
{
  static const my_prop_desc_t properties[] = {
      {"tint", MY_PROP_COLOR, loader_color_set, NULL},
      {NULL, MY_PROP_STRING, NULL, NULL}};
  my_ui_error_t error = {0};
  my_widget_t* widget;

  loader_color_value_type = MY_VALUE_NONE;
  loader_color_value = 0u;
  ASSERT_EQ(my_ui_loader_runtime_register_schema(
                "typed_color_widget", loader_custom_factory, properties,
                NULL),
            MY_RET_OK);
  widget = my_ui_load_str_ex(NULL, NULL,
                             "type: typed_color_widget\ntint: 4278190335\n",
                             MY_UI_LOAD_STRICT_SCHEMA, &error);
  ASSERT_NOT_NULL(widget);
  ASSERT_EQ(loader_color_value_type, MY_VALUE_UINT32);
  ASSERT_EQ(loader_color_value, 0xFF0000FFu);
  my_widget_unref(widget);
  ASSERT_EQ(my_ui_load_str_ex(NULL, NULL,
                               "type: typed_color_widget\ntint: -1\n",
                               MY_UI_LOAD_STRICT_SCHEMA, &error),
            NULL);
  ASSERT_EQ(my_ui_load_str_ex(NULL, NULL,
                               "type: typed_color_widget\ntint: 4294967296\n",
                               MY_UI_LOAD_STRICT_SCHEMA, &error),
            NULL);
  ASSERT_EQ(my_ui_loader_runtime_unregister("typed_color_widget"),
            MY_RET_OK);
}

TEST(widget_class_lease_does_not_cover_child_subtree)
{
  static const my_widget_class_t cls = {
      "runtime_subtree_widget", class_registry_factory, NULL, NULL, NULL};
  static const my_prop_desc_t blocking_properties[] = {
      {"blocking_property", MY_PROP_STRING, NULL, NULL},
      {NULL, MY_PROP_STRING, NULL, NULL}};
  PlatformThread load_thread;
  PlatformThread replacement_thread;
  bool replaced_while_child_blocked = false;

  ASSERT_TRUE(my_widget_class_is_frozen());
  ASSERT_EQ(my_widget_class_runtime_register(&cls), MY_RET_OK);
  ASSERT_EQ(my_ui_loader_runtime_register_schema(
                "blocking_loader_widget", loader_blocking_factory,
                blocking_properties, NULL),
            MY_RET_OK);
  atomic_store_explicit(&loader_blocking_factory_entered, false,
                        memory_order_relaxed);
  atomic_store_explicit(&loader_blocking_factory_release, false,
                        memory_order_relaxed);
  atomic_store_explicit(&loader_replacement_started, false,
                        memory_order_relaxed);
  atomic_store_explicit(&class_subtree_replace_started, false,
                        memory_order_relaxed);
  atomic_store_explicit(&class_subtree_replace_done, false,
                        memory_order_relaxed);
  class_subtree_replace_result = MY_RET_FAIL;

  ASSERT_TRUE(platform_thread_create(&load_thread, class_subtree_load_thread,
                                     NULL));
  while (!atomic_load_explicit(&loader_blocking_factory_entered,
                               memory_order_acquire)) {
  }
  ASSERT_TRUE(platform_thread_create(&replacement_thread,
                                     class_subtree_replace_thread, NULL));
  while (!atomic_load_explicit(&class_subtree_replace_started,
                               memory_order_acquire)) {
  }
  for (size_t i = 0u; i < 100000u; ++i) {
    if (atomic_load_explicit(&class_subtree_replace_done,
                             memory_order_acquire)) {
      replaced_while_child_blocked = true;
      break;
    }
    loader_test_yield();
  }
  atomic_store_explicit(&loader_replacement_started, true,
                        memory_order_release);
  atomic_store_explicit(&loader_blocking_factory_release, true,
                        memory_order_release);
  platform_thread_join(load_thread);
  platform_thread_join(replacement_thread);
  ASSERT_TRUE(replaced_while_child_blocked);
  ASSERT_EQ(class_subtree_replace_result, MY_RET_OK);
  ASSERT_EQ(my_widget_class_runtime_unregister("runtime_subtree_widget"),
            MY_RET_OK);
  ASSERT_EQ(my_ui_loader_runtime_unregister("blocking_loader_widget"),
            MY_RET_OK);
}

TEST(yaml_loader_property_failure_releases_callback_guard)
{
  static const my_prop_desc_t properties[] = {
      {"fail", MY_PROP_STRING, loader_property_failure_set, NULL},
      {NULL, MY_PROP_STRING, NULL, NULL}};
  my_ui_error_t error = {0};
  my_widget_t* widget;

  loader_property_failure_reenter_result = MY_RET_FAIL;
  ASSERT_EQ(my_ui_loader_runtime_register_schema(
                "property_failure_widget", loader_custom_factory, properties,
                NULL),
            MY_RET_OK);
  widget = my_ui_load_str_ex(NULL, NULL,
                             "type: property_failure_widget\nfail: value\n",
                             MY_UI_LOAD_STRICT_SCHEMA, &error);
  ASSERT_TRUE(widget == NULL);
  ASSERT_EQ(loader_property_failure_reenter_result, MY_RET_NOT_SUPPORTED);
  ASSERT_EQ(my_ui_loader_runtime_register_schema(
                "property_failure_after", loader_custom_factory, NULL, NULL),
            MY_RET_OK);
  ASSERT_EQ(my_ui_loader_runtime_unregister("property_failure_after"),
            MY_RET_OK);
  ASSERT_EQ(my_ui_loader_runtime_unregister("property_failure_widget"),
            MY_RET_OK);
}

TEST(yaml_loader_rejects_unterminated_schema_tables)
{
  my_prop_desc_t properties[MY_UI_MAX_TYPE_PROPERTIES];
  const char* events[MY_UI_MAX_TYPE_EVENTS];
  size_t i;

  for (i = 0; i < MY_UI_MAX_TYPE_PROPERTIES; i++) {
    properties[i] = (my_prop_desc_t){"field", MY_PROP_STRING, NULL, NULL};
  }
  for (i = 0; i < MY_UI_MAX_TYPE_EVENTS; i++) {
    events[i] = "event";
  }
  ASSERT_EQ(my_ui_loader_register_schema("bad_property_schema",
                                         loader_custom_factory, properties,
                                         NULL), MY_RET_INVALID_PARAMS);
  ASSERT_EQ(my_ui_loader_register_schema("bad_event_schema",
                                         loader_custom_factory, NULL, events),
            MY_RET_INVALID_PARAMS);
}

TEST(yaml_loader_rejects_conflicting_schema_descriptors)
{
  static const my_prop_desc_t reserved[] = {
      {"version", MY_PROP_INT, NULL, NULL},
      {NULL, MY_PROP_STRING, NULL, NULL}};
  static const my_prop_desc_t duplicate[] = {
      {"caption", MY_PROP_STRING, NULL, NULL},
      {"caption", MY_PROP_STRING, NULL, NULL},
      {NULL, MY_PROP_STRING, NULL, NULL}};
  static const char* const duplicate_events[] = {"activate", "activate", NULL};
  my_ui_type_info_t info;

  ASSERT_EQ(my_ui_loader_register_schema(
                "reserved_schema_widget", loader_custom_factory, reserved,
                NULL),
            MY_RET_INVALID_PARAMS);
  ASSERT_EQ(my_ui_loader_register_schema(
                "duplicate_schema_widget", loader_custom_factory, duplicate,
                NULL),
            MY_RET_INVALID_PARAMS);
  ASSERT_EQ(my_ui_loader_register_schema(
                "duplicate_event_widget", loader_custom_factory, NULL,
                duplicate_events),
            MY_RET_INVALID_PARAMS);
  ASSERT_EQ(my_ui_loader_register_schema(
                "schema_loader_widget", loader_custom_factory, reserved,
                NULL),
            MY_RET_INVALID_PARAMS);
  ASSERT_EQ(my_ui_loader_query_type("schema_loader_widget", &info), MY_RET_OK);
  ASSERT_EQ(info.property_count, 2u);
  ASSERT_STR_EQ(info.properties[0].name, "caption");
}

TEST(yaml_loader_rejects_invalid_schema_descriptor_names)
{
  static const my_prop_desc_t empty_property[] = {
      {"", MY_PROP_STRING, NULL, NULL},
      {NULL, MY_PROP_STRING, NULL, NULL}};
  static const char* const empty_event[] = {"", NULL};
  my_prop_desc_t long_property[2];
  char long_name[MY_UI_MAX_SCHEMA_NAME_BYTES];
  char long_event[MY_UI_MAX_SCHEMA_NAME_BYTES];
  const char* long_events[2];

  memset(long_name, 'p', sizeof(long_name));
  memset(long_event, 'e', sizeof(long_event));
  long_property[0] = (my_prop_desc_t){long_name, MY_PROP_STRING, NULL, NULL};
  long_property[1] = (my_prop_desc_t){NULL, MY_PROP_STRING, NULL, NULL};
  long_events[0] = long_event;
  long_events[1] = NULL;
  ASSERT_EQ(my_ui_loader_register_schema(
                "empty_property_name", loader_custom_factory, empty_property,
                NULL),
            MY_RET_INVALID_PARAMS);
  ASSERT_EQ(my_ui_loader_register_schema(
                "empty_event_name", loader_custom_factory, NULL, empty_event),
            MY_RET_INVALID_PARAMS);
  ASSERT_EQ(my_ui_loader_register_schema(
                "long_property_name", loader_custom_factory, long_property,
                NULL),
            MY_RET_INVALID_PARAMS);
  ASSERT_EQ(my_ui_loader_register_schema(
                "long_event_name", loader_custom_factory, NULL, long_events),
            MY_RET_INVALID_PARAMS);
}

TEST(yaml_loader_rejects_invalid_schema_descriptor_types)
{
  static const my_prop_desc_t invalid_type[] = {
      {"caption", (my_prop_type_t)99, NULL, NULL},
      {NULL, MY_PROP_STRING, NULL, NULL}};

  ASSERT_EQ(my_ui_loader_register_schema(
                "invalid_property_type", loader_custom_factory, invalid_type,
                NULL),
            MY_RET_INVALID_PARAMS);
}

TEST(widget_class_registry_rejects_invalid_descriptors)
{
  static const my_prop_desc_t reserved[] = {
      {"children", MY_PROP_STRING, NULL, NULL},
      {NULL, MY_PROP_STRING, NULL, NULL}};
  static const my_prop_desc_t duplicate[] = {
      {"caption", MY_PROP_STRING, NULL, NULL},
      {"caption", MY_PROP_STRING, NULL, NULL},
      {NULL, MY_PROP_STRING, NULL, NULL}};
  static const my_prop_desc_t invalid_type[] = {
      {"caption", (my_prop_type_t)99, NULL, NULL},
      {NULL, MY_PROP_STRING, NULL, NULL}};
  static const my_prop_desc_t valid[] = {
      {"caption", MY_PROP_STRING, NULL, NULL},
      {NULL, MY_PROP_STRING, NULL, NULL}};
  static const char* const duplicate_events[] = {"activate", "activate",
                                                   NULL};
  static const char* const valid_events[] = {"activate", NULL};
  my_prop_desc_t unterminated_props[64];
  char unterminated_type[64];
  char unterminated_prop_name[64];
  char unterminated_event_name[64];
  const char* unterminated_events[2];
  size_t i;
  static const my_widget_class_t old_class = {
      "class_registry_stable", class_registry_factory, valid, valid_events, NULL};
  static const my_widget_class_t replacement = {
      "class_registry_stable", class_registry_factory, reserved, NULL, NULL};

  memset(unterminated_type, 't', sizeof(unterminated_type));
  memset(unterminated_prop_name, 'p', sizeof(unterminated_prop_name));
  memset(unterminated_event_name, 'e', sizeof(unterminated_event_name));
  for (i = 0; i < sizeof(unterminated_props) / sizeof(unterminated_props[0]);
       i++) {
    unterminated_props[i] =
        (my_prop_desc_t){unterminated_prop_name, MY_PROP_STRING, NULL, NULL};
  }
  unterminated_events[0] = unterminated_event_name;
  unterminated_events[1] = NULL;

  ASSERT_EQ(my_widget_class_register(&old_class), MY_RET_OK);
  ASSERT_EQ(my_widget_class_register(&replacement), MY_RET_INVALID_PARAMS);
  ASSERT_NOT_NULL(my_widget_class_find("class_registry_stable"));
  ASSERT_STR_EQ(my_widget_class_find("class_registry_stable")->type,
                "class_registry_stable");
  ASSERT_EQ(my_widget_class_register(
                &(my_widget_class_t){"class_registry_reserved",
                                     class_registry_factory, reserved, NULL,
                                     NULL}),
            MY_RET_INVALID_PARAMS);
  ASSERT_EQ(my_widget_class_register(
                &(my_widget_class_t){"class_registry_duplicate",
                                     class_registry_factory, duplicate, NULL,
                                     NULL}),
            MY_RET_INVALID_PARAMS);
  ASSERT_EQ(my_widget_class_register(
                &(my_widget_class_t){"class_registry_type",
                                     class_registry_factory, invalid_type, NULL,
                                     NULL}),
            MY_RET_INVALID_PARAMS);
  ASSERT_EQ(my_widget_class_register(
                &(my_widget_class_t){"class_registry_events",
                                     class_registry_factory, NULL,
                                     duplicate_events, NULL}),
            MY_RET_INVALID_PARAMS);
  ASSERT_EQ(my_widget_class_register(
                &(my_widget_class_t){unterminated_type, class_registry_factory,
                                     NULL, NULL, NULL}),
            MY_RET_INVALID_PARAMS);
  ASSERT_EQ(my_widget_class_register(
                &(my_widget_class_t){"class_registry_prop_name",
                                     class_registry_factory, unterminated_props,
                                     NULL, NULL}),
            MY_RET_INVALID_PARAMS);
  ASSERT_EQ(my_widget_class_register(
                &(my_widget_class_t){"class_registry_event_name",
                                     class_registry_factory, NULL,
                                     unterminated_events, NULL}),
            MY_RET_INVALID_PARAMS);
}

TEST(widget_class_registry_owns_descriptor_snapshot)
{
  char type[MY_WIDGET_SCHEMA_MAX_NAME_BYTES] = "owned_snapshot_widget";
  char property_name[MY_WIDGET_SCHEMA_MAX_NAME_BYTES] = "caption";
  char event_name[MY_WIDGET_SCHEMA_MAX_NAME_BYTES] = "activate";
  my_prop_desc_t properties[] = {
      {property_name, MY_PROP_STRING, NULL, NULL},
      {NULL, MY_PROP_STRING, NULL, NULL}};
  const char* events[] = {event_name, NULL};
  my_widget_class_t cls = {type, class_registry_factory, properties, events,
                           NULL};
  const my_widget_class_t* found;

  ASSERT_EQ(my_widget_class_register(&cls), MY_RET_OK);
  strcpy(type, "caller_mutated_type");
  strcpy(property_name, "caller_mutated_property");
  strcpy(event_name, "caller_mutated_event");
  found = my_widget_class_find("owned_snapshot_widget");
  ASSERT_NOT_NULL(found);
  ASSERT_STR_EQ(found->type, "owned_snapshot_widget");
  ASSERT_STR_EQ(found->props[0].name, "caption");
  ASSERT_STR_EQ(found->events[0], "activate");
}

TEST(widget_class_registry_replacement_keeps_previous_snapshot_valid)
{
  static const my_prop_desc_t first_properties[] = {
      {"first", MY_PROP_STRING, NULL, NULL},
      {NULL, MY_PROP_STRING, NULL, NULL}};
  static const my_prop_desc_t second_properties[] = {
      {"second", MY_PROP_INT, NULL, NULL},
      {NULL, MY_PROP_STRING, NULL, NULL}};
  static const my_widget_class_t first = {
      "replacement_snapshot_widget", class_registry_factory, first_properties,
      NULL, NULL};
  static const my_widget_class_t second = {
      "replacement_snapshot_widget", class_registry_factory,
      second_properties, NULL, NULL};
  const my_widget_class_t* old_snapshot;
  const my_widget_class_t* active_snapshot;

  ASSERT_EQ(my_widget_class_register(&first), MY_RET_OK);
  old_snapshot = my_widget_class_find("replacement_snapshot_widget");
  ASSERT_NOT_NULL(old_snapshot);
  ASSERT_STR_EQ(old_snapshot->props[0].name, "first");
  ASSERT_EQ(my_widget_class_register(&second), MY_RET_OK);
  active_snapshot = my_widget_class_find("replacement_snapshot_widget");
  ASSERT_NOT_NULL(active_snapshot);
  ASSERT_STR_EQ(active_snapshot->props[0].name, "second");
  ASSERT_STR_EQ(old_snapshot->props[0].name, "first");
}

TEST(yaml_loader_copies_dynamic_schema_before_freeze)
{
  my_prop_desc_t properties[1] = {
      {"caption", MY_PROP_STRING, NULL, NULL}};
  const char* events[1] = {"activate"};
  my_ui_dynamic_schema_t schema = {properties, 1u, events, 1u};
  my_ui_type_info_t info;
  my_ui_error_t error = {0};
  my_widget_t* widget;

  ASSERT_EQ(my_ui_loader_register_dynamic_schema(
                NULL, "dynamic_schema_widget", loader_custom_factory, &schema,
                1u, NULL),
            MY_RET_OK);
  properties[0].name = "changed";
  events[0] = "changed_event";
  ASSERT_EQ(my_ui_loader_query_type("dynamic_schema_widget", &info), MY_RET_OK);
  ASSERT_TRUE(info.schema_known);
  ASSERT_EQ(info.property_count, 1u);
  ASSERT_STR_EQ(info.properties[0].name, "caption");
  ASSERT_EQ(info.event_count, 1u);
  ASSERT_STR_EQ(info.events[0], "activate");
  widget = my_ui_load_str_ex(NULL, NULL,
                             "type: dynamic_schema_widget\ncaption: hello\n",
                             MY_UI_LOAD_STRICT_SCHEMA, &error);
  ASSERT_NOT_NULL(widget);
  my_widget_unref(widget);
}

TEST(yaml_loader_rejects_invalid_dynamic_schema_transactionally)
{
  static const my_prop_desc_t valid[] = {
      {"caption", MY_PROP_STRING, NULL, NULL},
      {NULL, MY_PROP_STRING, NULL, NULL}};
  static const my_prop_desc_t invalid[] = {
      {"type", MY_PROP_STRING, NULL, NULL}};
  my_ui_dynamic_schema_t schema = {invalid, 1u, NULL, 0u};
  my_ui_type_info_t info;

  ASSERT_EQ(my_ui_loader_register("", loader_custom_factory),
            MY_RET_INVALID_PARAMS);
  ASSERT_EQ(my_ui_loader_register_schema(
                "dynamic_stable_widget", loader_custom_factory, valid, NULL),
            MY_RET_OK);
  ASSERT_EQ(my_ui_loader_register_dynamic_schema(
                NULL, "dynamic_stable_widget", loader_custom_factory, &schema,
                1u, NULL),
            MY_RET_INVALID_PARAMS);
  ASSERT_EQ(my_ui_loader_query_type("dynamic_stable_widget", &info), MY_RET_OK);
  ASSERT_TRUE(info.schema_known);
  ASSERT_EQ(info.property_count, 1u);
  ASSERT_STR_EQ(info.properties[0].name, "caption");
}

TEST(yaml_loader_dynamic_schema_oom_preserves_old_schema)
{
  static const my_prop_desc_t old_properties[] = {
      {"caption", MY_PROP_STRING, NULL, NULL},
      {NULL, MY_PROP_STRING, NULL, NULL}};
  static const my_prop_desc_t new_properties[] = {
      {"replacement", MY_PROP_STRING, NULL, NULL},
      {NULL, MY_PROP_STRING, NULL, NULL}};
  my_ui_dynamic_schema_t schema = {new_properties, 1u, NULL, 0u};
  size_t fail_at;

  ASSERT_EQ(my_ui_loader_register_schema(
                "dynamic_oom_widget", loader_custom_factory, old_properties,
                NULL),
            MY_RET_OK);
  for (fail_at = 1u; fail_at <= 16u; fail_at++) {
    loader_alloc_state_t state = {0u, fail_at};
    my_allocator_t allocator = {&state, loader_test_alloc, loader_test_calloc,
                                loader_test_realloc, loader_test_free};
    my_ui_type_info_t info;
    my_ret_t ret = my_ui_loader_register_dynamic_schema(
        &allocator, "dynamic_oom_widget", loader_custom_factory, &schema, 1u,
        NULL);
    ASSERT_TRUE(ret == MY_RET_OOM || ret == MY_RET_OK);
    ASSERT_EQ(my_ui_loader_query_type("dynamic_oom_widget", &info), MY_RET_OK);
    ASSERT_TRUE(info.schema_known);
    ASSERT_EQ(info.property_count, 1u);
    ASSERT_STR_EQ(info.properties[0].name,
                  ret == MY_RET_OK ? "replacement" : "caption");
    if (ret == MY_RET_OK) {
      ASSERT_EQ(my_ui_loader_register_schema(
                    "dynamic_oom_widget", loader_custom_factory, old_properties,
                    NULL),
                MY_RET_OK);
    }
  }
}

TEST(yaml_loader_dynamic_schema_replacement_keeps_new_schema)
{
  static const my_prop_desc_t first_properties[] = {
      {"first", MY_PROP_STRING, NULL, NULL},
      {NULL, MY_PROP_STRING, NULL, NULL}};
  static const my_prop_desc_t second_properties[] = {
      {"second", MY_PROP_STRING, NULL, NULL},
      {NULL, MY_PROP_STRING, NULL, NULL}};
  my_ui_dynamic_schema_t first = {first_properties, 1u, NULL, 0u};
  my_ui_dynamic_schema_t second = {second_properties, 1u, NULL, 0u};
  my_ui_type_info_t info;
  my_ui_error_t error = {0};
  my_widget_t* widget;

  ASSERT_EQ(my_ui_loader_register_dynamic_schema(
                NULL, "dynamic_replace_widget", loader_custom_factory, &first,
                1u, NULL),
            MY_RET_OK);
  ASSERT_EQ(my_ui_loader_register_dynamic_schema(
                NULL, "dynamic_replace_widget", loader_custom_factory, &second,
                1u, NULL),
            MY_RET_OK);
  ASSERT_EQ(my_ui_loader_query_type("dynamic_replace_widget", &info), MY_RET_OK);
  ASSERT_TRUE(info.schema_known);
  ASSERT_EQ(info.property_count, 1u);
  ASSERT_STR_EQ(info.properties[0].name, "second");
  widget = my_ui_load_str_ex(NULL, NULL,
                             "type: dynamic_replace_widget\nsecond: hello\n",
                             MY_UI_LOAD_STRICT_SCHEMA, &error);
  ASSERT_NOT_NULL(widget);
  my_widget_unref(widget);
}

TEST(yaml_loader_type_query_owns_schema_snapshot)
{
  static const my_prop_desc_t first_properties[] = {
      {"first_snapshot", MY_PROP_STRING, NULL, NULL},
      {NULL, MY_PROP_STRING, NULL, NULL}};
  static const my_prop_desc_t second_properties[] = {
      {"second_snapshot", MY_PROP_INT, NULL, NULL},
      {NULL, MY_PROP_STRING, NULL, NULL}};
  my_ui_dynamic_schema_t first = {first_properties, 1u, NULL, 0u};
  my_ui_dynamic_schema_t second = {second_properties, 1u, NULL, 0u};
  my_ui_type_info_t old_info;
  my_ui_type_info_t new_info;

  ASSERT_EQ(my_ui_loader_register_dynamic_schema(
                NULL, "snapshot_widget", loader_custom_factory, &first, 1u,
                NULL),
            MY_RET_OK);
  ASSERT_EQ(my_ui_loader_query_type("snapshot_widget", &old_info), MY_RET_OK);
  ASSERT_STR_EQ(old_info.type, "snapshot_widget");
  ASSERT_STR_EQ(old_info.properties[0].name, "first_snapshot");
  ASSERT_EQ(my_ui_loader_register_dynamic_schema(
                NULL, "snapshot_widget", loader_custom_factory, &second, 1u,
                NULL),
            MY_RET_OK);
  ASSERT_STR_EQ(old_info.type, "snapshot_widget");
  ASSERT_STR_EQ(old_info.properties[0].name, "first_snapshot");
  ASSERT_EQ(old_info.properties[0].type, MY_PROP_STRING);
  ASSERT_EQ(my_ui_loader_query_type("snapshot_widget", &new_info), MY_RET_OK);
  ASSERT_STR_EQ(new_info.properties[0].name, "second_snapshot");
  ASSERT_EQ(new_info.properties[0].type, MY_PROP_INT);
}

TEST(yaml_loader_replacement_waits_for_active_load)
{
  PlatformThread load_thread;
  PlatformThread replacement_thread;
  static const my_prop_desc_t initial_properties[] = {
      {"initial_live", MY_PROP_STRING, NULL, NULL},
      {NULL, MY_PROP_STRING, NULL, NULL}};

  ASSERT_EQ(my_ui_loader_register_schema("blocking_loader_widget",
                                         loader_blocking_factory,
                                         initial_properties, NULL),
            MY_RET_OK);
  atomic_store_explicit(&loader_blocking_factory_entered, false,
                        memory_order_relaxed);
  atomic_store_explicit(&loader_blocking_factory_release, false,
                        memory_order_relaxed);
  atomic_store_explicit(&loader_replacement_started, false,
                        memory_order_relaxed);
  atomic_store_explicit(&loader_replacement_done, false,
                        memory_order_relaxed);
  loader_replacement_result = MY_RET_FAIL;
  ASSERT_TRUE(platform_thread_create(&load_thread, loader_blocking_load_thread,
                                     NULL));
  while (!atomic_load_explicit(&loader_blocking_factory_entered,
                              memory_order_acquire)) {
  }
  ASSERT_TRUE(platform_thread_create(&replacement_thread,
                                     loader_replacement_thread, NULL));
  while (!atomic_load_explicit(&loader_replacement_started,
                              memory_order_acquire)) {
  }
  ASSERT_FALSE(atomic_load_explicit(&loader_replacement_done,
                                    memory_order_acquire));
  atomic_store_explicit(&loader_blocking_factory_release, true,
                        memory_order_release);
  platform_thread_join(load_thread);
  platform_thread_join(replacement_thread);
  ASSERT_EQ(loader_replacement_result, MY_RET_OK);
}

TEST(yaml_loader_runtime_replacement_waits_for_active_load)
{
  PlatformThread load_thread;
  PlatformThread replacement_thread;
  static const my_prop_desc_t initial_properties[] = {
      {"initial_runtime_live", MY_PROP_STRING, NULL, NULL},
      {NULL, MY_PROP_STRING, NULL, NULL}};

  ASSERT_TRUE(my_ui_loader_is_frozen());
  ASSERT_EQ(my_ui_loader_runtime_register_schema(
                "blocking_loader_widget", loader_blocking_factory,
                initial_properties, NULL),
            MY_RET_OK);
  atomic_store_explicit(&loader_blocking_factory_entered, false,
                        memory_order_relaxed);
  atomic_store_explicit(&loader_blocking_factory_release, false,
                        memory_order_relaxed);
  atomic_store_explicit(&loader_replacement_started, false,
                        memory_order_relaxed);
  atomic_store_explicit(&loader_replacement_done, false,
                        memory_order_relaxed);
  loader_runtime_replacement_result = MY_RET_FAIL;
  ASSERT_TRUE(platform_thread_create(&load_thread, loader_blocking_load_thread,
                                     NULL));
  while (!atomic_load_explicit(&loader_blocking_factory_entered,
                              memory_order_acquire)) {
  }
  ASSERT_TRUE(platform_thread_create(&replacement_thread,
                                     loader_runtime_replacement_thread, NULL));
  while (!atomic_load_explicit(&loader_replacement_started,
                              memory_order_acquire)) {
  }
  ASSERT_FALSE(atomic_load_explicit(&loader_replacement_done,
                                    memory_order_acquire));
  atomic_store_explicit(&loader_blocking_factory_release, true,
                        memory_order_release);
  platform_thread_join(load_thread);
  platform_thread_join(replacement_thread);
  ASSERT_EQ(loader_runtime_replacement_result, MY_RET_OK);
  ASSERT_EQ(my_ui_loader_runtime_unregister("blocking_loader_widget"),
            MY_RET_OK);
}

TEST(widget_class_concurrent_first_lookup_is_stable)
{
  PlatformThread threads[8];
  size_t i;

  atomic_store_explicit(&class_lookup_thread_failed, false,
                        memory_order_relaxed);
  for (i = 0u; i < sizeof(threads) / sizeof(threads[0]); i++) {
    ASSERT_TRUE(platform_thread_create(&threads[i], class_lookup_thread, NULL));
  }
  for (i = 0u; i < sizeof(threads) / sizeof(threads[0]); i++) {
    platform_thread_join(threads[i]);
  }
  ASSERT_FALSE(atomic_load_explicit(&class_lookup_thread_failed,
                                    memory_order_acquire));
  ASSERT_NOT_NULL(my_widget_class_find("button"));
  ASSERT_NOT_NULL(my_widget_class_find("label"));
}

TEST(yaml_loader_dynamic_schema_releases_owned_storage)
{
  static const my_prop_desc_t first_properties[] = {
      {"first", MY_PROP_STRING, NULL, NULL}};
  static const my_prop_desc_t second_properties[] = {
      {"second", MY_PROP_INT, NULL, NULL}};
  static const char* const first_events[] = {"activate"};
  static const char* const second_events[] = {"commit"};
  my_ui_dynamic_schema_t first = {first_properties, 1u, first_events, 1u};
  my_ui_dynamic_schema_t second = {second_properties, 1u, second_events, 1u};
  my_allocator_t* allocator = my_allocator_debug_create(NULL);

  ASSERT_NOT_NULL(allocator);
  ASSERT_EQ(my_ui_loader_register_dynamic_schema(
                allocator, "dynamic_leak_widget", loader_custom_factory,
                &first, 1u, NULL),
            MY_RET_OK);
  ASSERT_TRUE(my_allocator_debug_leak_count(allocator) > 0);
  ASSERT_EQ(my_ui_loader_register_dynamic_schema(
                allocator, "dynamic_leak_widget", loader_custom_factory,
                &second, 1u, NULL),
            MY_RET_OK);
  ASSERT_TRUE(my_allocator_debug_leak_count(allocator) > 0);
  ASSERT_EQ(my_ui_loader_register_schema("dynamic_leak_widget",
                                         loader_custom_factory, NULL, NULL),
            MY_RET_OK);
  ASSERT_EQ(my_allocator_debug_leak_count(allocator), 0);
  my_allocator_debug_destroy(allocator);
}

TEST(my_conf_object_set_oom_preserves_unattached_child)
{
  loader_alloc_state_t state = {0, 0};
  my_allocator_t allocator = {&state, loader_test_alloc, loader_test_calloc,
                              loader_test_realloc, loader_test_free};
  my_conf_node_t* object = my_conf_new_object(&allocator);
  my_conf_node_t* child = my_conf_new_str(&allocator, "value");
  size_t calls_before_set;

  ASSERT_NOT_NULL(object);
  ASSERT_NOT_NULL(child);
  calls_before_set = state.alloc_calls;
  state.fail_at = calls_before_set + 2u;
  ASSERT_EQ(my_conf_object_set(object, "field", child), MY_RET_OOM);
  ASSERT_EQ(my_conf_child_count(object), 0u);
  ASSERT_TRUE(my_conf_key(child) == NULL);
  state.fail_at = 0u;
  ASSERT_EQ(my_conf_object_set(object, "field", child), MY_RET_OK);
  ASSERT_EQ(my_conf_child_count(object), 1u);
  ASSERT_STR_EQ(my_conf_key(my_conf_child(object, 0u)), "field");
  my_conf_destroy(object);
}

TEST(yaml_loader_rejects_unterminated_factory_name)
{
  char type[24];

  memset(type, 'x', sizeof(type));
  ASSERT_EQ(my_ui_loader_register(type, loader_custom_factory),
            MY_RET_INVALID_PARAMS);
}

TEST(yaml_loader_rejects_unterminated_type_query)
{
  char type[24];
  my_ui_type_info_t info;

  memset(type, 'x', sizeof(type));
  ASSERT_EQ(my_ui_loader_query_type(type, &info), MY_RET_INVALID_PARAMS);
  ASSERT_TRUE(info.type == NULL);
}

TEST(yaml_loader_strict_schema_rejects_unknown_field)
{
  const char* yaml = "type: button\ntext: OK\nunknown: 1\n";
  my_ui_error_t error = {0};
  my_widget_t* widget = my_ui_load_str_ex(NULL, NULL, yaml,
                                          MY_UI_LOAD_STRICT_SCHEMA, &error);

  ASSERT_TRUE(widget == NULL);
  ASSERT_EQ(error.code, MY_UI_ERROR_SCHEMA);
  ASSERT_STR_EQ(error.field, "unknown");
  ASSERT_TRUE(error.message[0] != '\0');
}

TEST(yaml_loader_strict_schema_validates_common_fields_before_factory)
{
  static const my_prop_desc_t properties[] = {
      {"caption", MY_PROP_STRING, NULL, NULL},
      {NULL, MY_PROP_STRING, NULL, NULL}};
  const char* invalid_documents[] = {
      "type: strict_common_widget\nvisible: 1\n",
      "type: strict_common_widget\nx: 2147483648\n",
      "type: strict_common_widget\nname: 1\n",
      "type: strict_common_widget\nchildren: {}\n",
      "type: strict_common_widget\nbindings: []\n",
      "type: strict_common_widget\nlayout: linear:x:3\n"};
  size_t i;

  ASSERT_EQ(my_ui_loader_register_schema("strict_common_widget",
                                         loader_custom_factory, properties,
                                         NULL), MY_RET_OK);
  loader_factory_calls = 0u;
  for (i = 0u; i < sizeof(invalid_documents) / sizeof(invalid_documents[0]);
       i++) {
    my_ui_error_t error = {0};
    ASSERT_TRUE(my_ui_load_str_ex(NULL, NULL, invalid_documents[i],
                                  MY_UI_LOAD_STRICT_SCHEMA, &error) == NULL);
    ASSERT_EQ(error.code, MY_UI_ERROR_SCHEMA);
  }
  ASSERT_EQ(loader_factory_calls, 0u);
}

TEST(yaml_loader_strict_schema_rejects_window_fields_on_widget_root)
{
  const char* yaml = "type: button\ntext: OK\ntitle: invalid\n";
  my_ui_error_t error = {0};

  ASSERT_TRUE(my_ui_load_str_ex(NULL, NULL, yaml, MY_UI_LOAD_STRICT_SCHEMA,
                                &error) == NULL);
  ASSERT_EQ(error.code, MY_UI_ERROR_SCHEMA);
  ASSERT_STR_EQ(error.field, "title");
  ASSERT_STR_EQ(error.path, "title");
}

TEST(yaml_file_loader_strict_schema_reports_field_and_path)
{
  char path[256];
  FILE* file;
  my_ui_error_t error = {0};
  my_widget_t* widget;

  test_tmp(path, sizeof(path), "yaml_strict_schema_file");
  file = fopen(path, "wb");
  ASSERT_NOT_NULL(file);
  ASSERT_TRUE(fputs("type: button\ntext: OK\nunknown: 1\n", file) >= 0);
  ASSERT_EQ(fclose(file), 0);
  widget = my_ui_load_file_ex(NULL, NULL, path, MY_UI_LOAD_STRICT_SCHEMA,
                              &error);
  ASSERT_TRUE(widget == NULL);
  ASSERT_EQ(error.code, MY_UI_ERROR_SCHEMA);
  ASSERT_STR_EQ(error.field, "unknown");
  ASSERT_STR_EQ(error.path, "unknown");
  remove(path);
}

TEST(yaml_file_loader_strict_schema_reports_nested_common_path)
{
  char path[256];
  FILE* file;
  my_ui_error_t error = {0};

  test_tmp(path, sizeof(path), "yaml_strict_schema_nested_file");
  file = fopen(path, "wb");
  ASSERT_NOT_NULL(file);
  ASSERT_TRUE(fputs("type: widget\nchildren:\n  - type: label\n    x: bad\n",
                    file) >= 0);
  ASSERT_EQ(fclose(file), 0);
  ASSERT_TRUE(my_ui_load_file_ex(NULL, NULL, path, MY_UI_LOAD_STRICT_SCHEMA,
                                 &error) == NULL);
  ASSERT_EQ(error.code, MY_UI_ERROR_SCHEMA);
  ASSERT_STR_EQ(error.field, "x");
  ASSERT_STR_EQ(error.path, "children[0].x");
  remove(path);
}

TEST(yaml_loader_compat_schema_keeps_unknown_field_behavior)
{
  const char* yaml = "type: button\ntext: OK\nunknown: 1\n";
  my_ui_error_t error = {0};
  my_widget_t* widget = my_ui_load_str(NULL, NULL, yaml, &error);

  ASSERT_NOT_NULL(widget);
  my_widget_unref(widget);
}

TEST(yaml_loader_rejects_unknown_load_policy)
{
  my_ui_error_t error = {0};

  ASSERT_TRUE(my_ui_load_str_ex(NULL, NULL, "type: label\n", 2u, &error) ==
              NULL);
  ASSERT_EQ(error.code, MY_UI_ERROR_UNKNOWN_POLICY);
  ASSERT_STR_EQ(error.field, "flags");
}

TEST(yaml_loader_errors_expose_stable_categories)
{
  char* oversized = (char*)malloc(MY_UI_MAX_YAML_BYTES + 1u);
  my_ui_error_t error = {0};

  ASSERT_NOT_NULL(oversized);
  memset(oversized, ' ', MY_UI_MAX_YAML_BYTES + 1u);
  ASSERT_TRUE(my_ui_load_str(NULL, NULL, oversized, &error) == NULL);
  ASSERT_EQ(error.code, MY_UI_ERROR_INPUT_LIMIT);
  memset(&error, 0, sizeof(error));
  ASSERT_TRUE(my_ui_load_str(NULL, NULL, "type: widget\nchildren: label\n",
                             &error) == NULL);
  ASSERT_EQ(error.code, MY_UI_ERROR_SCHEMA);
  ASSERT_STR_EQ(error.field, "children");
  memset(&error, 0, sizeof(error));
  ASSERT_TRUE(my_ui_load_str(NULL, NULL, "type: label\nvisible: 1\n",
                             &error) == NULL);
  ASSERT_EQ(error.code, MY_UI_ERROR_SCHEMA);
  ASSERT_STR_EQ(error.field, "visible");
  free(oversized);
}

TEST(yaml_loader_reports_bounded_nested_error_path)
{
  const char* yaml =
      "type: widget\n"
      "children:\n"
      "  - type: widget\n"
      "    children:\n"
      "      - type: label\n"
      "        visible: 1\n";
  my_ui_error_t error = {0};

  ASSERT_TRUE(my_ui_load_str(NULL, NULL, yaml, &error) == NULL);
  ASSERT_EQ(error.code, MY_UI_ERROR_SCHEMA);
  ASSERT_STR_EQ(error.field, "visible");
  ASSERT_STR_EQ(error.path, "children[0].children[0].visible");
}

TEST(yaml_loader_truncates_deep_error_path_safely)
{
  char* yaml = (char*)malloc(8192u);
  size_t used = 0u;
  size_t depth;
  my_ui_error_t error = {0};

  ASSERT_NOT_NULL(yaml);
  used += (size_t)snprintf(yaml + used, 8192u - used, "type: widget\n");
  for (depth = 0u; depth < 20u; depth++) {
    size_t indent = depth * 4u;
    used += (size_t)snprintf(yaml + used, 8192u - used, "%*schildren:\n",
                             (int)indent, "");
    used += (size_t)snprintf(yaml + used, 8192u - used, "%*s- type: widget\n",
                             (int)(indent + 2u), "");
  }
  used += (size_t)snprintf(yaml + used, 8192u - used,
                           "%*svisible: 1\n", 80, "");
  ASSERT_TRUE(used < 8192u);
  ASSERT_TRUE(my_ui_load_str(NULL, NULL, yaml, &error) == NULL);
  ASSERT_EQ(error.code, MY_UI_ERROR_SCHEMA);
  ASSERT_STR_EQ(error.field, "visible");
  ASSERT_TRUE(strlen(error.path) < MY_UI_ERROR_PATH_LEN);
  ASSERT_STR_EQ(error.path, "<path-truncated>");
  free(yaml);
}

TEST(yaml_loader_does_not_ignore_name_oom)
{
  const char* yaml = "type: label\nname: named\n";
  size_t fail_at;

  for (fail_at = 1u; fail_at <= 96u; fail_at++) {
    loader_alloc_state_t state = {0, fail_at};
    my_allocator_t allocator = {&state, loader_test_alloc, loader_test_calloc,
                                loader_test_realloc, loader_test_free};
    my_ui_error_t error = {0};
    my_widget_t* widget = my_ui_load_str(&allocator, NULL, yaml, &error);

    if (widget != NULL) {
      my_object_t* object = (my_object_t*)widget;
      ASSERT_NOT_NULL(object->name);
      ASSERT_STR_EQ(object->name, "named");
      my_widget_unref(widget);
    }
  }
}

TEST(yaml_loader_rejects_invalid_layout_syntax)
{
  const char* yaml =
      "type: widget\n"
      "layout: linear:x:8\n";
  my_ui_error_t error = {0};

  ASSERT_TRUE(my_ui_load_str(NULL, NULL, yaml, &error) == NULL);
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

TEST(yaml_loader_rejects_invalid_window_style)
{
  const char* yaml =
      "type: window\n"
      "w: 100\n"
      "h: 80\n"
      "style: \"button { color: red;\"\n";
  my_pal_t* pal = my_pal_dummy_create(NULL);
  my_ui_error_t error = {0};
  my_widget_t* widget;

  ASSERT_NOT_NULL(pal);
  widget = my_ui_load_str(NULL, pal, yaml, &error);
  ASSERT_TRUE(widget == NULL);
  ASSERT_TRUE(error.message[0] != '\0');
  my_pal_destroy(pal);
}

TEST(yaml_loader_applies_css_window_style)
{
  const char* yaml =
      "type: window\n"
      "w: 100\n"
      "h: 80\n"
      "style: \"button { color: red; }\"\n";
  my_pal_t* pal = my_pal_dummy_create(NULL);
  my_ui_error_t error = {0};
  my_window_t* window;
  const my_value_t* color;

  ASSERT_NOT_NULL(pal);
  window = (my_window_t*)my_ui_load_str(NULL, pal, yaml, &error);
  ASSERT_NOT_NULL(window);
  color = my_theme_get(window->theme, "button", NULL, MY_STATE_NORMAL,
                       "fg_color");
  ASSERT_NOT_NULL(color);
  ASSERT_EQ(my_value_get_uint32(color), 0xFF0000FFu);
  my_widget_unref((my_widget_t*)window);
  my_pal_destroy(pal);
}

TEST(yaml_loader_evaluates_media_style_against_window_viewport)
{
  const char* yaml =
      "type: window\n"
      "w: 200\n"
      "h: 80\n"
      "style: \"@media (min-width: 150px) { button { color: red; } }\"\n";
  my_pal_t* pal = my_pal_dummy_create(NULL);
  my_ui_error_t error = {0};
  my_window_t* window;
  const my_value_t* color;

  ASSERT_NOT_NULL(pal);
  window = (my_window_t*)my_ui_load_str(NULL, pal, yaml, &error);
  ASSERT_NOT_NULL(window);
  color = my_theme_get(window->theme, "button", NULL, MY_STATE_NORMAL,
                       "fg_color");
  ASSERT_NOT_NULL(color);
  ASSERT_EQ(my_value_get_uint32(color), 0xFF0000FFu);
  my_widget_unref((my_widget_t*)window);
  my_pal_destroy(pal);
}

TEST(yaml_loader_uses_logical_not_drawable_viewport_for_media)
{
  const char* yaml =
      "type: window\n"
      "w: 100\n"
      "h: 80\n"
      "style: \"@media (min-width: 150px) { button { color: red; } }\"\n";
  my_pal_t* pal = my_pal_dummy_create(NULL);
  my_ui_error_t error = {0};
  my_window_t* window;
  const my_value_t* color;

  ASSERT_NOT_NULL(pal);
  my_pal_dummy_set_scale_factor(pal, 2.0f);
  window = (my_window_t*)my_ui_load_str(NULL, pal, yaml, &error);
  ASSERT_NOT_NULL(window);
  color = my_theme_get(window->theme, "button", NULL, MY_STATE_NORMAL,
                       "fg_color");
  ASSERT_NOT_NULL(color);
  ASSERT_EQ(my_value_get_uint32(color), 0x212121FFu);
  my_widget_unref((my_widget_t*)window);
  my_pal_destroy(pal);
}

TEST(yaml_loader_evaluates_media_style_against_pal_capabilities)
{
  const char* yaml =
      "type: window\n"
      "w: 100\n"
      "h: 80\n"
      "style: \"@media (hover: hover) and (pointer: fine) { button { color: red; } }\"\n";
  my_pal_t* pal = my_pal_dummy_create(NULL);
  my_pal_media_context_ex_t media = {{
      true, false, false,
      MY_PAL_MEDIA_CAP_HOVER | MY_PAL_MEDIA_CAP_POINTER_FINE |
          MY_PAL_MEDIA_CAP_ANY_POINTER_FINE | MY_PAL_MEDIA_CAP_COLOR_SRGB,
      }, MY_PAL_MEDIA_KNOWN_HOVER | MY_PAL_MEDIA_KNOWN_POINTER |
          MY_PAL_MEDIA_KNOWN_ANY_POINTER | MY_PAL_MEDIA_KNOWN_COLOR_GAMUT};
  my_ui_error_t error = {0};
  my_window_t* window;
  const my_value_t* color;

  ASSERT_NOT_NULL(pal);
  my_pal_dummy_set_media_context_ex(pal, &media);
  window = (my_window_t*)my_ui_load_str(NULL, pal, yaml, &error);
  ASSERT_NOT_NULL(window);
  color = my_theme_get(window->theme, "button", NULL, MY_STATE_NORMAL,
                       "fg_color");
  ASSERT_NOT_NULL(color);
  ASSERT_EQ(my_value_get_uint32(color), 0xFF0000FFu);
  my_widget_unref((my_widget_t*)window);
  my_pal_destroy(pal);
}

TEST(yaml_loader_default_dummy_media_is_screen)
{
  const char* yaml =
      "type: window\n"
      "w: 100\n"
      "h: 80\n"
      "style: \"@media screen { button { color: red; } }\"\n";
  my_pal_t* pal = my_pal_dummy_create(NULL);
  my_ui_error_t error = {0};
  my_window_t* window;
  const my_value_t* color;

  ASSERT_NOT_NULL(pal);
  window = (my_window_t*)my_ui_load_str(NULL, pal, yaml, &error);
  ASSERT_NOT_NULL(window);
  color = my_theme_get(window->theme, "button", NULL, MY_STATE_NORMAL,
                       "fg_color");
  ASSERT_NOT_NULL(color);
  ASSERT_EQ(my_value_get_uint32(color), 0xFF0000FFu);
  my_widget_unref((my_widget_t*)window);
  my_pal_destroy(pal);
}

TEST(yaml_loader_honors_pal_screen_media_fact)
{
  const char* yaml =
      "type: window\n"
      "w: 100\n"
      "h: 80\n"
      "style: \"@media screen { button { color: red; } }\"\n";
  my_pal_t* pal = my_pal_dummy_create(NULL);
  my_pal_media_context_ex_t media = {{false, false, false, 0u},
                                     MY_PAL_MEDIA_KNOWN_ALL};
  my_ui_error_t error = {0};
  my_window_t* window;
  const my_value_t* color;

  ASSERT_NOT_NULL(pal);
  my_pal_dummy_set_media_context_ex(pal, &media);
  window = (my_window_t*)my_ui_load_str(NULL, pal, yaml, &error);
  ASSERT_NOT_NULL(window);
  color = my_theme_get(window->theme, "button", NULL, MY_STATE_NORMAL,
                       "fg_color");
  ASSERT_NOT_NULL(color);
  ASSERT_EQ(my_value_get_uint32(color), 0x212121FFu);
  my_widget_unref((my_widget_t*)window);
  my_pal_destroy(pal);
}

TEST(yaml_loader_rejects_unsupported_css_at_rule)
{
  const char* yaml =
      "type: window\n"
      "w: 100\n"
      "h: 80\n"
      "style: \"@media (x) { button { color: red; } }\"\n";
  my_pal_t* pal = my_pal_dummy_create(NULL);
  my_ui_error_t error = {0};

  ASSERT_NOT_NULL(pal);
  ASSERT_TRUE(my_ui_load_str(NULL, pal, yaml, &error) == NULL);
  ASSERT_TRUE(error.message[0] != '\0');
  my_pal_destroy(pal);
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

TEST(yaml_loader_rejects_unterminated_string_with_bounded_scan)
{
  char* yaml = (char*)malloc(MY_UI_MAX_YAML_BYTES);
  my_ui_error_t error = {0};

  ASSERT_NOT_NULL(yaml);
  memset(yaml, ' ', MY_UI_MAX_YAML_BYTES);
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

TEST(yaml_file_loader_reports_buffer_oom)
{
  char path[256];
  FILE* file;
  loader_alloc_state_t state = {0, 1u};
  my_allocator_t allocator = {&state, loader_test_alloc, loader_test_calloc,
                              loader_test_realloc, loader_test_free};
  my_ui_error_t error = {0};

  test_tmp(path, sizeof(path), "yaml_buffer_oom");
  file = fopen(path, "wb");
  ASSERT_NOT_NULL(file);
  ASSERT_TRUE(fputs("type: label\n", file) >= 0);
  ASSERT_EQ(fclose(file), 0);
  ASSERT_TRUE(my_ui_load_file(&allocator, NULL, path, &error) == NULL);
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

TEST(toml_parser_rejects_surrogate_escapes)
{
  const char* hi = "a = \"\\uD800\"\n";
  const char* lo = "a = \"\\uDFFF\"\n";
  my_conf_error_t error;
  my_conf_node_t* root = my_conf_parse_toml(NULL, hi, strlen(hi), &error);

  ASSERT_TRUE(root == NULL);
  root = my_conf_parse_toml(NULL, lo, strlen(lo), &error);
  ASSERT_TRUE(root == NULL);
}

TEST(toml_parser_rejects_out_of_range_unicode_escape)
{
  const char* toml = "a = \"\\U00110000\"\n";
  my_conf_error_t error;
  my_conf_node_t* root = my_conf_parse_toml(NULL, toml, strlen(toml), &error);

  ASSERT_TRUE(root == NULL);
}

TEST(toml_parser_accepts_in_range_unicode_escapes)
{
  const char* toml = "a = \"\\u0041\\U0001F600\"\n";
  my_conf_error_t error;
  my_conf_node_t* root = my_conf_parse_toml(NULL, toml, strlen(toml), &error);

  ASSERT_NOT_NULL(root);
  ASSERT_STR_EQ(my_conf_get_str(root, "a", ""), "A\xF0\x9F\x98\x80");
  my_conf_destroy(root);
}

TEST(registries_freeze_after_startup)
{
  my_widget_class_t class_after_freeze = {
      "class_after_freeze", class_registry_factory, NULL, NULL, NULL};

  ASSERT_FALSE(my_widget_class_is_frozen());
  ASSERT_FALSE(my_ui_loader_is_frozen());
  ASSERT_EQ(my_widget_class_freeze(), MY_RET_OK);
  ASSERT_EQ(my_ui_loader_freeze(), MY_RET_OK);
  ASSERT_TRUE(my_widget_class_is_frozen());
  ASSERT_TRUE(my_ui_loader_is_frozen());
  ASSERT_EQ(my_widget_class_freeze(), MY_RET_OK);
  ASSERT_EQ(my_ui_loader_freeze(), MY_RET_OK);
  ASSERT_EQ(my_widget_class_register(&class_after_freeze),
            MY_RET_NOT_SUPPORTED);
  ASSERT_EQ(my_ui_loader_register("factory_after_freeze", loader_custom_factory),
            MY_RET_NOT_SUPPORTED);
  ASSERT_EQ(my_ui_loader_register(NULL, loader_custom_factory),
            MY_RET_NOT_SUPPORTED);
  ASSERT_EQ(my_ui_loader_register_schema_ex(NULL, loader_custom_factory, NULL,
                                            NULL, 0u, NULL),
            MY_RET_NOT_SUPPORTED);
  ASSERT_NOT_NULL(my_widget_class_find("button"));
  ASSERT_EQ(my_ui_loader_query_type("button", &(my_ui_type_info_t){0}),
            MY_RET_OK);
}

TEST(widget_property_router_rejects_type_spoof)
{
  my_widget_t* label = my_label_create(NULL, "safe label");
  my_value_t value;

  ASSERT_NOT_NULL(label);
  label->widget_type = "list_view";
  my_value_init(&value, NULL);
  ASSERT_EQ(my_widget_get_prop(label, "row_height", &value),
            MY_RET_INVALID_PARAMS);
  my_value_reset(&value);
  my_widget_unref(label);
}

TEST(widget_class_runtime_snapshot_replace_and_remove)
{
  static const my_prop_desc_t first_properties[] = {
      {"runtime_first", MY_PROP_STRING, NULL, NULL},
      {NULL, MY_PROP_STRING, NULL, NULL}};
  static const my_prop_desc_t second_properties[] = {
      {"runtime_second", MY_PROP_INT, NULL, NULL},
      {NULL, MY_PROP_STRING, NULL, NULL}};
  const my_widget_class_t first = {
      "runtime_snapshot_widget", class_registry_factory, first_properties,
      NULL, NULL};
  const my_widget_class_t second = {
      "runtime_snapshot_widget", class_registry_factory, second_properties,
      NULL, NULL};
  const my_widget_class_t *old_snapshot;
  const my_widget_class_t *active_snapshot;

  ASSERT_TRUE(my_widget_class_is_frozen());
  ASSERT_EQ(my_widget_class_runtime_register(&first), MY_RET_OK);
  old_snapshot = my_widget_class_find("runtime_snapshot_widget");
  ASSERT_NOT_NULL(old_snapshot);
  ASSERT_STR_EQ(old_snapshot->props[0].name, "runtime_first");
  ASSERT_EQ(my_widget_class_runtime_register(&second), MY_RET_OK);
  active_snapshot = my_widget_class_find("runtime_snapshot_widget");
  ASSERT_NOT_NULL(active_snapshot);
  ASSERT_STR_EQ(active_snapshot->props[0].name, "runtime_second");
  ASSERT_STR_EQ(old_snapshot->props[0].name, "runtime_first");
  ASSERT_EQ(my_widget_class_runtime_unregister("runtime_snapshot_widget"),
            MY_RET_OK);
  ASSERT_TRUE(my_widget_class_find("runtime_snapshot_widget") == NULL);
  ASSERT_STR_EQ(old_snapshot->props[0].name, "runtime_first");
  ASSERT_STR_EQ(active_snapshot->props[0].name, "runtime_second");
}

TEST(widget_class_runtime_snapshot_protects_builtins)
{
  const my_widget_class_t replacement = {
      "button", class_registry_factory, NULL, NULL, NULL};

  ASSERT_TRUE(my_widget_class_is_frozen());
  ASSERT_EQ(my_widget_class_runtime_register(&replacement),
            MY_RET_NOT_SUPPORTED);
  ASSERT_EQ(my_widget_class_runtime_unregister("button"),
            MY_RET_NOT_SUPPORTED);
}

TEST(widget_class_runtime_unregister_waits_for_callback_lease)
{
  static const my_widget_class_t cls = {
      "runtime_leased_widget", class_registry_factory, NULL, NULL, NULL};
  const my_widget_class_t* found = NULL;
  my_widget_class_lease_t lease = {0};
  PlatformThread unregister_thread;

  ASSERT_EQ(my_widget_class_runtime_register(&cls), MY_RET_OK);
  ASSERT_EQ(my_widget_class_acquire("runtime_leased_widget", &found, &lease),
            MY_RET_OK);
  ASSERT_NOT_NULL(found);
  ASSERT_TRUE(found == lease.class_descriptor);
  ASSERT_EQ(my_widget_class_runtime_register(&cls), MY_RET_NOT_SUPPORTED);
  ASSERT_EQ(my_ui_loader_runtime_register_schema(
                "lease_reentry_loader", loader_custom_factory, NULL, NULL),
            MY_RET_NOT_SUPPORTED);
  atomic_store_explicit(&class_lease_unregister_started, false,
                        memory_order_relaxed);
  atomic_store_explicit(&class_lease_unregister_done, false,
                        memory_order_relaxed);
  class_lease_unregister_result = MY_RET_FAIL;
  ASSERT_TRUE(platform_thread_create(&unregister_thread,
                                     class_lease_unregister_thread,
                                     NULL));
  while (!atomic_load_explicit(&class_lease_unregister_started,
                               memory_order_acquire)) {
  }
  ASSERT_FALSE(atomic_load_explicit(&class_lease_unregister_done,
                                    memory_order_acquire));
  my_widget_class_release(&lease);
  platform_thread_join(unregister_thread);
  ASSERT_TRUE(atomic_load_explicit(&class_lease_unregister_done,
                                   memory_order_acquire));
  ASSERT_EQ(class_lease_unregister_result, MY_RET_OK);
  ASSERT_TRUE(my_widget_class_find("runtime_leased_widget") == NULL);

  ASSERT_EQ(my_widget_class_runtime_register(&cls), MY_RET_OK);
  ASSERT_EQ(my_widget_class_acquire("runtime_leased_widget", &found, &lease),
            MY_RET_OK);
  atomic_store_explicit(&class_lease_replace_started, false,
                        memory_order_relaxed);
  atomic_store_explicit(&class_lease_replace_done, false,
                        memory_order_relaxed);
  class_lease_replace_result = MY_RET_FAIL;
  ASSERT_TRUE(platform_thread_create(&unregister_thread,
                                     class_lease_replace_thread, NULL));
  while (!atomic_load_explicit(&class_lease_replace_started,
                               memory_order_acquire)) {
  }
  ASSERT_FALSE(atomic_load_explicit(&class_lease_replace_done,
                                    memory_order_acquire));
  my_widget_class_release(&lease);
  platform_thread_join(unregister_thread);
  ASSERT_TRUE(atomic_load_explicit(&class_lease_replace_done,
                                   memory_order_acquire));
  ASSERT_EQ(class_lease_replace_result, MY_RET_OK);
  ASSERT_EQ(my_widget_class_runtime_unregister("runtime_leased_widget"),
            MY_RET_OK);
}

TEST(widget_class_lease_rejects_foreign_thread_release)
{
  static const my_widget_class_t cls = {
      "runtime_foreign_release_widget", class_registry_factory, NULL, NULL,
      NULL};
  const my_widget_class_t* found = NULL;
  my_widget_class_lease_t lease = {0};
  PlatformThread release_thread;
  PlatformThread unregister_thread;

  ASSERT_EQ(my_widget_class_runtime_register(&cls), MY_RET_OK);
  ASSERT_EQ(my_widget_class_acquire("runtime_foreign_release_widget", &found,
                                   &lease), MY_RET_OK);
  class_foreign_release_lease = &lease;
  atomic_store_explicit(&class_foreign_release_done, false,
                        memory_order_relaxed);
  ASSERT_TRUE(platform_thread_create(&release_thread,
                                     class_foreign_release_thread, NULL));
  platform_thread_join(release_thread);
  ASSERT_TRUE(atomic_load_explicit(&class_foreign_release_done,
                                   memory_order_acquire));

  atomic_store_explicit(&class_lease_unregister_started, false,
                        memory_order_relaxed);
  atomic_store_explicit(&class_lease_unregister_done, false,
                        memory_order_relaxed);
  class_lease_unregister_result = MY_RET_FAIL;
  ASSERT_TRUE(platform_thread_create(
      &unregister_thread, class_lease_unregister_thread,
      (void*)"runtime_foreign_release_widget"));
  while (!atomic_load_explicit(&class_lease_unregister_started,
                               memory_order_acquire)) {
  }
  /* A foreign release must not allow unregister to pass the active lease. */
  platform_thread_yield();
  ASSERT_FALSE(atomic_load_explicit(&class_lease_unregister_done,
                                   memory_order_acquire));
  my_widget_class_release(&lease);
  platform_thread_join(unregister_thread);
  ASSERT_EQ(class_lease_unregister_result, MY_RET_OK);
  ASSERT_TRUE(my_widget_class_find("runtime_foreign_release_widget") == NULL);
  class_foreign_release_lease = NULL;
}

TEST(widget_class_lease_rejects_copied_release)
{
  static const my_widget_class_t cls = {
      "runtime_copied_release_widget", class_registry_factory, NULL, NULL,
      NULL};
  const my_widget_class_t* found = NULL;
  my_widget_class_lease_t lease = {0};
  my_widget_class_lease_t copied;
  PlatformThread unregister_thread;

  ASSERT_EQ(my_widget_class_runtime_register(&cls), MY_RET_OK);
  ASSERT_EQ(my_widget_class_acquire("runtime_copied_release_widget", &found,
                                   &lease), MY_RET_OK);
  copied = lease;
  my_widget_class_release(&copied);

  atomic_store_explicit(&class_lease_unregister_started, false,
                        memory_order_relaxed);
  atomic_store_explicit(&class_lease_unregister_done, false,
                        memory_order_relaxed);
  class_lease_unregister_result = MY_RET_FAIL;
  ASSERT_TRUE(platform_thread_create(
      &unregister_thread, class_lease_unregister_thread,
      (void*)"runtime_copied_release_widget"));
  while (!atomic_load_explicit(&class_lease_unregister_started,
                               memory_order_acquire)) {
  }
  platform_thread_yield();
  ASSERT_FALSE(atomic_load_explicit(&class_lease_unregister_done,
                                    memory_order_acquire));
  my_widget_class_release(&lease);
  platform_thread_join(unregister_thread);
  ASSERT_EQ(class_lease_unregister_result, MY_RET_OK);
  ASSERT_TRUE(my_widget_class_find("runtime_copied_release_widget") == NULL);
}

TEST(widget_class_module_quiesce_protects_instances)
{
  static const my_widget_class_t cls = {
      "runtime_module_widget", class_registry_factory, NULL, NULL, NULL};
  my_widget_class_module_t* module;
  const my_widget_class_t* found;
  my_widget_class_lease_t lease = {0};
  my_widget_t* widget;

  module = my_widget_class_module_create(NULL);
  ASSERT_TRUE(module != NULL);
  ASSERT_EQ(my_widget_class_runtime_register_module(module, &cls), MY_RET_OK);
  ASSERT_EQ(my_widget_class_acquire("runtime_module_widget", &found, &lease),
            MY_RET_OK);
  widget = found->create(NULL);
  ASSERT_TRUE(widget != NULL);
  ASSERT_EQ(my_widget_class_bind_instance(widget, &lease), MY_RET_OK);
  my_widget_class_release(&lease);

  ASSERT_EQ(my_widget_class_module_begin_unload(module), MY_RET_OK);
  ASSERT_EQ(my_widget_class_acquire("runtime_module_widget", &found, &lease),
            MY_RET_NOT_SUPPORTED);
  ASSERT_EQ(my_widget_class_module_try_unload(module), MY_RET_NOT_SUPPORTED);
  ASSERT_EQ(my_widget_class_runtime_unregister("runtime_module_widget"),
            MY_RET_OK);
  ASSERT_EQ(my_widget_class_module_try_unload(module), MY_RET_NOT_SUPPORTED);
  my_widget_unref(widget);
  ASSERT_EQ(my_widget_class_module_try_unload(module), MY_RET_OK);
  ASSERT_EQ(my_widget_class_module_destroy(module), MY_RET_OK);
}

TEST(widget_class_module_retained_reference_blocks_destroy)
{
  my_widget_class_module_t* module;

  module = my_widget_class_module_create(NULL);
  ASSERT_TRUE(module != NULL);
  ASSERT_EQ(my_widget_class_module_retain(module), MY_RET_OK);
  ASSERT_EQ(my_widget_class_module_begin_unload(module), MY_RET_OK);
  ASSERT_EQ(my_widget_class_module_try_unload(module), MY_RET_OK);
  ASSERT_EQ(my_widget_class_module_destroy(module), MY_RET_NOT_SUPPORTED);
  my_widget_class_module_release(module);
  ASSERT_EQ(my_widget_class_module_try_unload(module), MY_RET_OK);
  ASSERT_EQ(my_widget_class_module_destroy(module), MY_RET_OK);
}

TEST(widget_class_module_destroyed_token_fails_closed)
{
  my_widget_class_module_t* module;

  module = my_widget_class_module_create(NULL);
  ASSERT_TRUE(module != NULL);
  ASSERT_EQ(my_widget_class_module_begin_unload(module), MY_RET_OK);
  ASSERT_EQ(my_widget_class_module_try_unload(module), MY_RET_OK);
  ASSERT_EQ(my_widget_class_module_destroy(module), MY_RET_OK);
  ASSERT_EQ(my_widget_class_module_retain(module), MY_RET_NOT_SUPPORTED);
  ASSERT_EQ(my_widget_class_module_register_entry(module), MY_RET_NOT_SUPPORTED);
  ASSERT_EQ(my_widget_class_module_callback_acquire(module), MY_RET_NOT_SUPPORTED);
  ASSERT_EQ(my_widget_class_module_bind_widget(module, NULL), MY_RET_INVALID_PARAMS);
}

TEST(widget_class_module_rejects_unknown_token_without_dereference)
{
  my_widget_class_module_t* unknown =
      (my_widget_class_module_t*)(uintptr_t)1u;

  ASSERT_EQ(my_widget_class_module_retain(unknown), MY_RET_NOT_SUPPORTED);
  my_widget_class_module_release(unknown);
  ASSERT_EQ(my_widget_class_module_register_entry(unknown),
            MY_RET_NOT_SUPPORTED);
  my_widget_class_module_unregister_entry(unknown);
  ASSERT_EQ(my_widget_class_module_callback_acquire(unknown),
            MY_RET_NOT_SUPPORTED);
  my_widget_class_module_callback_release(unknown);
  ASSERT_EQ(my_widget_class_module_begin_unload(unknown),
            MY_RET_NOT_SUPPORTED);
  ASSERT_EQ(my_widget_class_module_try_unload(unknown), MY_RET_NOT_SUPPORTED);
  ASSERT_EQ(my_widget_class_module_destroy(unknown), MY_RET_NOT_SUPPORTED);
}

TEST(widget_class_module_unload_rejected_from_callback)
{
  static const my_widget_class_t cls = {
      "runtime_module_callback_widget", module_callback_factory, NULL, NULL,
      NULL};
  my_widget_class_module_t* module;
  const my_widget_class_t* found;
  my_widget_class_lease_t lease = {0};
  my_widget_t* widget;

  module = my_widget_class_module_create(NULL);
  ASSERT_TRUE(module != NULL);
  module_callback_owner = module;
  module_callback_unload_result = MY_RET_FAIL;
  ASSERT_EQ(my_widget_class_runtime_register_module(module, &cls), MY_RET_OK);
  ASSERT_EQ(my_widget_class_acquire("runtime_module_callback_widget", &found,
                                   &lease),
            MY_RET_OK);
  widget = found->create(NULL);
  ASSERT_TRUE(widget != NULL);
  my_widget_class_release(&lease);
  ASSERT_EQ(module_callback_unload_result, MY_RET_NOT_SUPPORTED);
  ASSERT_EQ(my_widget_class_module_begin_unload(module), MY_RET_OK);
  ASSERT_EQ(my_widget_class_runtime_unregister("runtime_module_callback_widget"),
            MY_RET_OK);
  ASSERT_EQ(my_widget_class_module_try_unload(module), MY_RET_OK);
  my_widget_unref(widget);
  ASSERT_EQ(my_widget_class_module_destroy(module), MY_RET_OK);
  module_callback_owner = NULL;
}

TEST(widget_class_module_create_binds_until_destroy)
{
  static const my_widget_class_t cls = {
      "runtime_module_create_widget", class_registry_factory, NULL, NULL,
      NULL};
  my_widget_class_module_t* module;
  my_widget_t* widget;

  module = my_widget_class_module_create(NULL);
  ASSERT_TRUE(module != NULL);
  ASSERT_EQ(my_widget_class_runtime_register_module(module, &cls), MY_RET_OK);
  widget = my_widget_class_create("runtime_module_create_widget", NULL);
  ASSERT_TRUE(widget != NULL);
  ASSERT_EQ(my_widget_class_module_begin_unload(module), MY_RET_OK);
  ASSERT_EQ(my_widget_class_runtime_unregister("runtime_module_create_widget"),
            MY_RET_OK);
  ASSERT_EQ(my_widget_class_module_try_unload(module), MY_RET_NOT_SUPPORTED);
  my_widget_unref(widget);
  ASSERT_EQ(my_widget_class_module_try_unload(module), MY_RET_OK);
  ASSERT_EQ(my_widget_class_module_destroy(module), MY_RET_OK);
}

TEST(widget_class_module_same_owner_replace_keeps_entry_count)
{
  static const my_widget_class_t first = {
      "runtime_mod_same_owner", class_registry_factory, NULL, NULL, NULL};
  static const my_widget_class_t second = {
      "runtime_mod_same_owner", class_registry_factory, NULL, NULL, NULL};
  my_widget_class_module_t* module;

  module = my_widget_class_module_create(NULL);
  ASSERT_TRUE(module != NULL);
  ASSERT_EQ(my_widget_class_runtime_register_module(module, &first), MY_RET_OK);
  ASSERT_EQ(my_widget_class_runtime_register_module(module, &second), MY_RET_OK);
  ASSERT_EQ(my_widget_class_module_begin_unload(module), MY_RET_OK);
  ASSERT_EQ(my_widget_class_runtime_unregister("runtime_mod_same_owner"),
            MY_RET_OK);
  ASSERT_EQ(my_widget_class_module_try_unload(module), MY_RET_OK);
  ASSERT_EQ(my_widget_class_module_destroy(module), MY_RET_OK);
}

TEST(yaml_loader_module_factory_quiesce_lifecycle)
{
  my_widget_class_module_t* module;
  my_widget_t* widget;
  my_ui_error_t error = {0};

  module = my_widget_class_module_create(NULL);
  ASSERT_TRUE(module != NULL);
  loader_module_callback_owner = module;
  loader_module_callback_unload_result = MY_RET_FAIL;
  {
    my_ret_t register_result = my_ui_loader_runtime_register_schema_module(
        module, "runtime_ld_mod_widget", loader_module_factory, NULL,
        NULL);
    ASSERT_EQ(register_result, MY_RET_OK);
  }
  widget = my_ui_load_str(NULL, NULL, "type: runtime_ld_mod_widget\n",
                          &error);
  ASSERT_TRUE(widget != NULL);
  ASSERT_EQ(loader_module_callback_unload_result, MY_RET_NOT_SUPPORTED);
  ASSERT_EQ(my_widget_class_module_begin_unload(module), MY_RET_OK);
  ASSERT_EQ(my_ui_load_str(NULL, NULL, "type: runtime_ld_mod_widget\n",
                           &error),
            NULL);
  ASSERT_EQ(my_ui_loader_runtime_unregister("runtime_ld_mod_widget"),
            MY_RET_OK);
  ASSERT_EQ(my_widget_class_module_try_unload(module), MY_RET_NOT_SUPPORTED);
  my_widget_unref(widget);
  ASSERT_EQ(my_widget_class_module_try_unload(module), MY_RET_OK);
  ASSERT_EQ(my_widget_class_module_destroy(module), MY_RET_OK);
  loader_module_callback_owner = NULL;
}

TEST(yaml_loader_module_bind_is_atomic_with_factory_completion)
{
  my_widget_class_module_t* module;
  PlatformThread load_thread;
  PlatformThread unload_thread;

  module = my_widget_class_module_create(NULL);
  ASSERT_TRUE(module != NULL);
  ASSERT_EQ(my_ui_loader_runtime_register_schema_module(
                module, "loader_bind_race_widget", loader_bind_race_factory,
                NULL, NULL),
            MY_RET_OK);
  loader_bind_race_module = module;
  atomic_store_explicit(&loader_bind_race_factory_entered, false,
                        memory_order_relaxed);
  atomic_store_explicit(&loader_bind_race_factory_release, false,
                        memory_order_relaxed);
  atomic_store_explicit(&loader_bind_race_load_failed, false,
                        memory_order_relaxed);
  loader_bind_race_unload_result = MY_RET_FAIL;
  ASSERT_TRUE(platform_thread_create(&load_thread, loader_bind_race_load_thread,
                                     NULL));
  ASSERT_TRUE(platform_thread_create(
      &unload_thread, loader_bind_race_unload_thread, NULL));
  platform_thread_join(unload_thread);
  platform_thread_join(load_thread);
  ASSERT_EQ(loader_bind_race_unload_result, MY_RET_OK);
  ASSERT_TRUE(atomic_load_explicit(&loader_bind_race_load_failed,
                                   memory_order_acquire));
  ASSERT_EQ(my_ui_loader_runtime_unregister("loader_bind_race_widget"),
            MY_RET_OK);
  ASSERT_EQ(my_widget_class_module_try_unload(module), MY_RET_OK);
  ASSERT_EQ(my_widget_class_module_destroy(module), MY_RET_OK);
  loader_bind_race_module = NULL;
}

TEST(yaml_loader_module_replacement_preserves_entry_count)
{
  static const my_prop_desc_t properties[] = {
      {"runtime_module_caption", MY_PROP_STRING, NULL, NULL},
      {NULL, MY_PROP_STRING, NULL, NULL}};
  my_widget_class_module_t* module;

  module = my_widget_class_module_create(NULL);
  ASSERT_TRUE(module != NULL);
  ASSERT_EQ(my_ui_loader_runtime_register_schema_module(
                module, "runtime_ld_replace", loader_custom_factory,
                properties, NULL),
            MY_RET_OK);
  ASSERT_EQ(my_ui_loader_runtime_register_schema_module(
                module, "runtime_ld_replace", loader_custom_factory,
                properties, NULL),
            MY_RET_OK);
  ASSERT_EQ(my_widget_class_module_begin_unload(module), MY_RET_OK);
  ASSERT_EQ(my_ui_loader_runtime_unregister("runtime_ld_replace"), MY_RET_OK);
  ASSERT_EQ(my_widget_class_module_try_unload(module), MY_RET_OK);
  ASSERT_EQ(my_widget_class_module_destroy(module), MY_RET_OK);
}

TEST(yaml_loader_module_migration_lease)
{
  my_widget_class_module_t* module;
  my_widget_t* widget;
  my_ui_error_t error = {0};

  module = my_widget_class_module_create(NULL);
  ASSERT_TRUE(module != NULL);
  loader_migration_module_owner = module;
  loader_migration_module_unload_result = MY_RET_FAIL;
  ASSERT_EQ(my_ui_loader_runtime_register_dynamic_schema_module(
                NULL, module, "runtime_ld_migrate", loader_custom_factory,
                &(my_ui_dynamic_schema_t){NULL, 0u, NULL, 0u}, 2u,
                loader_module_migrate),
            MY_RET_OK);
  widget = my_ui_load_str(NULL, NULL,
                          "type: runtime_ld_migrate\nversion: 1\n", &error);
  ASSERT_TRUE(widget != NULL);
  ASSERT_EQ(loader_migration_module_unload_result, MY_RET_NOT_SUPPORTED);
  ASSERT_EQ(my_widget_class_module_begin_unload(module), MY_RET_OK);
  ASSERT_EQ(my_ui_loader_runtime_unregister("runtime_ld_migrate"), MY_RET_OK);
  ASSERT_EQ(my_widget_class_module_try_unload(module), MY_RET_NOT_SUPPORTED);
  my_widget_unref(widget);
  ASSERT_EQ(my_widget_class_module_try_unload(module), MY_RET_OK);
  ASSERT_EQ(my_widget_class_module_destroy(module), MY_RET_OK);
  loader_migration_module_owner = NULL;
}

TEST(yaml_loader_module_registration_rejects_invalid_without_locking)
{
  my_widget_class_module_t* module = my_widget_class_module_create(NULL);
  ASSERT_TRUE(module != NULL);
  ASSERT_EQ(my_ui_loader_runtime_register_schema_module(
                module, NULL, loader_custom_factory, NULL, NULL),
            MY_RET_INVALID_PARAMS);
  ASSERT_EQ(my_ui_loader_runtime_register_dynamic_schema_module(
                NULL, module, NULL, loader_custom_factory,
                &(my_ui_dynamic_schema_t){NULL, 0u, NULL, 0u}, 1u, NULL),
            MY_RET_INVALID_PARAMS);
  ASSERT_EQ(my_widget_class_module_begin_unload(module), MY_RET_OK);
  ASSERT_EQ(my_widget_class_module_try_unload(module), MY_RET_OK);
  ASSERT_EQ(my_widget_class_module_destroy(module), MY_RET_OK);
}

TEST(yaml_loader_module_schema_variants_share_quiesce)
{
  static const my_prop_desc_t properties[] = {
      {"runtime_variant_caption", MY_PROP_STRING, NULL, NULL},
      {NULL, MY_PROP_STRING, NULL, NULL}};
  static const my_ui_schema_migration_t migrations[] = {
      {1u, 2u, loader_module_migrate}};
  my_widget_class_module_t* module;

  module = my_widget_class_module_create(NULL);
  ASSERT_TRUE(module != NULL);
  ASSERT_EQ(my_ui_loader_runtime_register_schema_ex_module(
                module, "runtime_ld_schema_ex", loader_custom_factory,
                properties, NULL, 2u, loader_module_migrate),
            MY_RET_OK);
  ASSERT_EQ(my_ui_loader_runtime_register_schema_chain_module(
                module, "runtime_ld_schema_chain", loader_custom_factory,
                properties, NULL, 2u, migrations, 1u),
            MY_RET_OK);
  ASSERT_EQ(my_widget_class_module_begin_unload(module), MY_RET_OK);
  ASSERT_EQ(my_ui_loader_runtime_unregister("runtime_ld_schema_ex"),
            MY_RET_OK);
  ASSERT_EQ(my_ui_loader_runtime_unregister("runtime_ld_schema_chain"),
            MY_RET_OK);
  ASSERT_EQ(my_widget_class_module_try_unload(module), MY_RET_OK);
  ASSERT_EQ(my_widget_class_module_destroy(module), MY_RET_OK);
}

TEST(widget_class_runtime_snapshot_concurrent_readers)
{
  static const my_prop_desc_t properties[] = {
      {"runtime_concurrent_first", MY_PROP_STRING, NULL, NULL},
      {NULL, MY_PROP_STRING, NULL, NULL}};
  const my_widget_class_t cls = {
      "runtime_concurrent_widget", class_registry_factory, properties, NULL,
      NULL};
  PlatformThread writer;
  PlatformThread readers[4];
  size_t i;

  ASSERT_EQ(my_widget_class_runtime_register(&cls), MY_RET_OK);
  atomic_store_explicit(&class_runtime_writer_done, false,
                        memory_order_relaxed);
  atomic_store_explicit(&class_runtime_concurrent_failed, false,
                        memory_order_relaxed);
  ASSERT_TRUE(platform_thread_create(&writer, class_runtime_writer_thread, NULL));
  for (i = 0u; i < sizeof(readers) / sizeof(readers[0]); i++) {
    ASSERT_TRUE(platform_thread_create(&readers[i], class_runtime_reader_thread,
                                       NULL));
  }
  platform_thread_join(writer);
  for (i = 0u; i < sizeof(readers) / sizeof(readers[0]); i++) {
    platform_thread_join(readers[i]);
  }
  ASSERT_FALSE(atomic_load_explicit(&class_runtime_concurrent_failed,
                                    memory_order_acquire));
  ASSERT_TRUE(atomic_load_explicit(&class_runtime_writer_done,
                                   memory_order_acquire));
  ASSERT_EQ(my_widget_class_runtime_unregister("runtime_concurrent_widget"),
            MY_RET_OK);
}

TEST(yaml_loader_runtime_factory_register_and_unregister)
{
  static const my_prop_desc_t properties[] = {
      {"runtime_caption", MY_PROP_STRING, NULL, NULL},
      {NULL, MY_PROP_STRING, NULL, NULL}};
  static const char* const events[] = {"activate", NULL};
  my_ui_type_info_t info;
  my_ui_error_t error = {0};
  my_widget_t* widget;

  ASSERT_TRUE(my_ui_loader_is_frozen());
  ASSERT_EQ(my_ui_loader_runtime_register_schema(
                "button", loader_custom_factory, properties, events),
            MY_RET_NOT_SUPPORTED);
  ASSERT_EQ(my_ui_loader_runtime_register_schema(
                "window", loader_custom_factory, properties, events),
            MY_RET_NOT_SUPPORTED);
  ASSERT_EQ(my_ui_loader_runtime_register_schema(
                "runtime_loader_widget", loader_custom_factory, properties,
                events),
            MY_RET_OK);
  ASSERT_EQ(my_ui_loader_query_type("runtime_loader_widget", &info),
            MY_RET_OK);
  ASSERT_TRUE(info.schema_known);
  ASSERT_EQ(info.property_count, 1u);
  ASSERT_STR_EQ(info.properties[0].name, "runtime_caption");
  ASSERT_EQ(info.event_count, 1u);
  widget = my_ui_load_str_ex(NULL, NULL,
                             "type: runtime_loader_widget\n"
                             "runtime_caption: ok\n",
                             MY_UI_LOAD_STRICT_SCHEMA, &error);
  ASSERT_NOT_NULL(widget);
  my_widget_unref(widget);
  ASSERT_EQ(my_ui_loader_runtime_unregister("runtime_loader_widget"),
            MY_RET_OK);
  ASSERT_EQ(my_ui_loader_query_type("runtime_loader_widget", &info),
            MY_RET_NOT_SUPPORTED);
}

TEST(yaml_loader_runtime_dynamic_schema_owns_snapshot)
{
  my_prop_desc_t source_properties[] = {
      {"runtime_dynamic_caption", MY_PROP_STRING, NULL, NULL},
      {NULL, MY_PROP_STRING, NULL, NULL}};
  const char* source_events[] = {"activate", NULL};
  my_ui_dynamic_schema_t schema = {source_properties, 1u,
                                   (const char* const*)source_events, 1u};
  my_ui_type_info_t info;

  ASSERT_TRUE(my_ui_loader_is_frozen());
  ASSERT_EQ(my_ui_loader_runtime_register_dynamic_schema(
                NULL, "runtime_dynamic_widget", loader_custom_factory,
                &schema, 1u, NULL),
            MY_RET_OK);
  source_properties[0].name = "runtime_dynamic_mutated";
  source_events[0] = "mutated";
  ASSERT_EQ(my_ui_loader_query_type("runtime_dynamic_widget", &info),
            MY_RET_OK);
  ASSERT_STR_EQ(info.properties[0].name, "runtime_dynamic_caption");
  ASSERT_EQ(info.event_count, 1u);
  ASSERT_STR_EQ(info.events[0], "activate");
  ASSERT_EQ(my_ui_loader_runtime_unregister("runtime_dynamic_widget"),
            MY_RET_OK);
}

TEST(yaml_loader_runtime_dynamic_schema_oom_preserves_snapshot)
{
  static const my_prop_desc_t old_properties[] = {
      {"runtime_old_caption", MY_PROP_STRING, NULL, NULL},
      {NULL, MY_PROP_STRING, NULL, NULL}};
  static const my_prop_desc_t new_properties[] = {
      {"runtime_new_caption", MY_PROP_STRING, NULL, NULL},
      {NULL, MY_PROP_STRING, NULL, NULL}};
  my_ui_dynamic_schema_t schema = {new_properties, 1u, NULL, 0u};
  size_t fail_at;

  ASSERT_EQ(my_ui_loader_runtime_register_dynamic_schema(
                NULL, "custom_loader_widget", loader_custom_factory,
                &(my_ui_dynamic_schema_t){old_properties, 1u, NULL, 0u}, 1u,
                NULL),
            MY_RET_OK);
  for (fail_at = 1u; fail_at <= 16u; fail_at++) {
    loader_alloc_state_t state = {0u, fail_at};
    my_allocator_t allocator = {&state, loader_test_alloc, loader_test_calloc,
                                loader_test_realloc, loader_test_free};
    my_ui_type_info_t info;
    my_ret_t ret = my_ui_loader_runtime_register_dynamic_schema(
        &allocator, "custom_loader_widget", loader_custom_factory,
        &schema, 1u, NULL);

    ASSERT_TRUE(ret == MY_RET_OOM || ret == MY_RET_OK);
    ASSERT_EQ(my_ui_loader_query_type("custom_loader_widget", &info),
              MY_RET_OK);
    ASSERT_STR_EQ(info.properties[0].name,
                  ret == MY_RET_OK ? "runtime_new_caption"
                                   : "runtime_old_caption");
    if (ret == MY_RET_OK) {
      ASSERT_EQ(my_ui_loader_runtime_register_dynamic_schema(
                    NULL, "custom_loader_widget", loader_custom_factory,
                    &(my_ui_dynamic_schema_t){old_properties, 1u, NULL, 0u},
                    1u, NULL),
                MY_RET_OK);
    }
  }
}

TEST(yaml_loader_runtime_dynamic_schema_rejects_invalid_without_allocating)
{
  static const my_prop_desc_t valid_properties[] = {
      {"runtime_valid_caption", MY_PROP_STRING, NULL, NULL},
      {NULL, MY_PROP_STRING, NULL, NULL}};
  my_ui_dynamic_schema_t valid = {valid_properties, 1u, NULL, 0u};
  my_ui_dynamic_schema_t invalid = {NULL, 1u, NULL, 0u};
  loader_alloc_state_t state = {0u, 0u};
  my_allocator_t allocator = {&state, loader_test_alloc, loader_test_calloc,
                              loader_test_realloc, loader_test_free};

  ASSERT_EQ(my_ui_loader_runtime_register_dynamic_schema(
                &allocator, "runtime_invalid_dynamic_widget",
                loader_custom_factory, NULL, 1u, NULL),
            MY_RET_INVALID_PARAMS);
  ASSERT_EQ(my_ui_loader_runtime_register_dynamic_schema(
                &allocator, "runtime_invalid_dynamic_widget",
                loader_custom_factory, &invalid, 1u, NULL),
            MY_RET_INVALID_PARAMS);
  ASSERT_EQ(my_ui_loader_runtime_register_dynamic_schema(
                &allocator, "runtime_invalid_dynamic_widget",
                loader_custom_factory, &valid, 0u, NULL),
            MY_RET_INVALID_PARAMS);
  ASSERT_EQ(my_ui_loader_runtime_register_dynamic_schema(
                &allocator, "runtime_invalid_dynamic_widget",
                loader_custom_factory, &valid, 2u, NULL),
            MY_RET_INVALID_PARAMS);
  ASSERT_EQ(my_ui_loader_runtime_register_dynamic_schema(
                &allocator, "runtime_invalid_dynamic_widget",
                loader_custom_factory, &invalid, 1u, NULL),
            MY_RET_INVALID_PARAMS);
  ASSERT_EQ(state.alloc_calls, 0u);
}

TEST(yaml_loader_runtime_factory_concurrent_readers)
{
  PlatformThread writer;
  PlatformThread readers[4];
  size_t i;

  ASSERT_TRUE(my_ui_loader_is_frozen());
  ASSERT_EQ(my_ui_loader_runtime_register_schema(
                "custom_loader_widget", loader_custom_factory, NULL,
                NULL),
            MY_RET_OK);
  atomic_store_explicit(&loader_runtime_writer_done, false,
                        memory_order_relaxed);
  atomic_store_explicit(&loader_runtime_concurrent_failed, false,
                        memory_order_relaxed);
  ASSERT_TRUE(platform_thread_create(&writer, loader_runtime_writer_thread,
                                     NULL));
  for (i = 0u; i < sizeof(readers) / sizeof(readers[0]); ++i) {
    ASSERT_TRUE(platform_thread_create(&readers[i],
                                       loader_runtime_reader_thread, NULL));
  }
  platform_thread_join(writer);
  for (i = 0u; i < sizeof(readers) / sizeof(readers[0]); ++i) {
    platform_thread_join(readers[i]);
  }
  ASSERT_TRUE(atomic_load_explicit(&loader_runtime_writer_done,
                                   memory_order_acquire));
  ASSERT_FALSE(atomic_load_explicit(&loader_runtime_concurrent_failed,
                                    memory_order_acquire));
  ASSERT_EQ(my_ui_loader_runtime_unregister("custom_loader_widget"),
            MY_RET_OK);
}

TEST(yaml_loader_runtime_factory_rejects_invalid_and_reentrant_changes)
{
  static const my_prop_desc_t invalid[] = {
      {"version", MY_PROP_INT, NULL, NULL},
      {NULL, MY_PROP_STRING, NULL, NULL}};
  ASSERT_TRUE(my_ui_loader_is_frozen());
  ASSERT_EQ(my_ui_loader_runtime_register_schema(
                "runtime_invalid_loader_widget", loader_custom_factory,
                invalid, NULL),
            MY_RET_INVALID_PARAMS);
  ASSERT_EQ(my_ui_loader_runtime_unregister("runtime_missing_widget"),
            MY_RET_NOT_FOUND);
  ASSERT_EQ(my_ui_loader_runtime_unregister("button"), MY_RET_NOT_FOUND);
}

TEST_MAIN_BEGIN()
    RUN_TEST(yaml_loader_builds_typed_widget);
    RUN_TEST(yaml_loader_builds_nested_children);
    RUN_TEST(yaml_loader_applies_button_cooldown);
    RUN_TEST(yaml_loader_rejects_non_yaml_markup);
    RUN_TEST(yaml_loader_rejects_invalid_shapes);
    RUN_TEST(yaml_loader_capability_registry_is_static_and_explicit);
    RUN_TEST(yaml_loader_schema_migration_is_transactional);
    RUN_TEST(yaml_loader_schema_migration_rejects_newer_version);
    RUN_TEST(yaml_loader_schema_migrates_nested_nodes_before_any_factory);
    RUN_TEST(yaml_loader_nested_migration_failure_is_transactional);
    RUN_TEST(yaml_loader_migration_oom_is_transactional);
    RUN_TEST(yaml_loader_migration_cannot_bypass_version_guard);
    RUN_TEST(yaml_loader_runs_bounded_schema_migration_chain);
    RUN_TEST(yaml_loader_rejects_unavailable_schema_chain_path);
    RUN_TEST(yaml_loader_rejects_invalid_schema_migration_chain_registration);
    RUN_TEST(yaml_loader_type_query_exposes_builtin_schema);
    RUN_TEST(yaml_loader_type_query_exposes_window_root_schema);
    RUN_TEST(yaml_loader_type_query_exposes_custom_factory_without_schema);
    RUN_TEST(yaml_loader_custom_factory_schema_is_queryable_and_strict);
    RUN_TEST(yaml_loader_factory_cannot_reenter_registry_write_path);
    RUN_TEST(yaml_loader_migration_cannot_reenter_registry_write_path);
    RUN_TEST(yaml_loader_rejects_unterminated_schema_tables);
    RUN_TEST(yaml_loader_rejects_conflicting_schema_descriptors);
    RUN_TEST(yaml_loader_rejects_invalid_schema_descriptor_names);
    RUN_TEST(yaml_loader_rejects_invalid_schema_descriptor_types);
    RUN_TEST(widget_class_registry_rejects_invalid_descriptors);
    RUN_TEST(widget_class_registry_owns_descriptor_snapshot);
    RUN_TEST(widget_class_registry_replacement_keeps_previous_snapshot_valid);
    RUN_TEST(yaml_loader_copies_dynamic_schema_before_freeze);
    RUN_TEST(yaml_loader_rejects_invalid_dynamic_schema_transactionally);
    RUN_TEST(yaml_loader_dynamic_schema_oom_preserves_old_schema);
    RUN_TEST(yaml_loader_dynamic_schema_replacement_keeps_new_schema);
    RUN_TEST(yaml_loader_type_query_owns_schema_snapshot);
    RUN_TEST(yaml_loader_replacement_waits_for_active_load);
    RUN_TEST(widget_class_concurrent_first_lookup_is_stable);
    RUN_TEST(yaml_loader_dynamic_schema_releases_owned_storage);
    RUN_TEST(my_conf_object_set_oom_preserves_unattached_child);
    RUN_TEST(yaml_loader_rejects_unterminated_type_query);
    RUN_TEST(yaml_loader_strict_schema_rejects_unknown_field);
    RUN_TEST(yaml_loader_strict_schema_validates_common_fields_before_factory);
    RUN_TEST(yaml_loader_strict_schema_rejects_window_fields_on_widget_root);
    RUN_TEST(yaml_file_loader_strict_schema_reports_field_and_path);
    RUN_TEST(yaml_file_loader_strict_schema_reports_nested_common_path);
    RUN_TEST(yaml_loader_compat_schema_keeps_unknown_field_behavior);
    RUN_TEST(yaml_loader_rejects_unknown_load_policy);
    RUN_TEST(yaml_loader_rejects_unterminated_factory_name);
    RUN_TEST(yaml_loader_errors_expose_stable_categories);
    RUN_TEST(yaml_loader_reports_bounded_nested_error_path);
    RUN_TEST(yaml_loader_truncates_deep_error_path_safely);
    RUN_TEST(yaml_loader_does_not_ignore_name_oom);
    RUN_TEST(yaml_loader_rejects_invalid_layout_syntax);
    RUN_TEST(yaml_loader_applies_bindings_map);
    RUN_TEST(yaml_loader_rejects_invalid_window_style);
    RUN_TEST(yaml_loader_applies_css_window_style);
    RUN_TEST(yaml_loader_evaluates_media_style_against_window_viewport);
    RUN_TEST(yaml_loader_uses_logical_not_drawable_viewport_for_media);
    RUN_TEST(yaml_loader_evaluates_media_style_against_pal_capabilities);
    RUN_TEST(yaml_loader_default_dummy_media_is_screen);
    RUN_TEST(yaml_loader_honors_pal_screen_media_fact);
    RUN_TEST(yaml_loader_rejects_unsupported_css_at_rule);
    RUN_TEST(yaml_loader_rejects_oversized_input);
    RUN_TEST(yaml_loader_rejects_unterminated_string_with_bounded_scan);
    RUN_TEST(yaml_file_loader_rejects_oversized_file_before_allocation);
    RUN_TEST(yaml_file_loader_rejects_embedded_nul);
    RUN_TEST(yaml_file_loader_reports_buffer_oom);
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
    RUN_TEST(toml_parser_rejects_surrogate_escapes);
    RUN_TEST(toml_parser_rejects_out_of_range_unicode_escape);
    RUN_TEST(toml_parser_accepts_in_range_unicode_escapes);
    RUN_TEST(registries_freeze_after_startup);
    RUN_TEST(yaml_loader_property_cannot_reenter_registry_write_path);
    RUN_TEST(yaml_loader_typed_color_property_preserves_rgba32);
    RUN_TEST(widget_class_lease_does_not_cover_child_subtree);
    RUN_TEST(yaml_loader_property_failure_releases_callback_guard);
    RUN_TEST(yaml_loader_runtime_replacement_waits_for_active_load);
    RUN_TEST(widget_property_router_rejects_type_spoof);
    RUN_TEST(widget_class_runtime_snapshot_replace_and_remove);
    RUN_TEST(widget_class_runtime_snapshot_protects_builtins);
    RUN_TEST(widget_class_runtime_unregister_waits_for_callback_lease);
    RUN_TEST(widget_class_lease_rejects_foreign_thread_release);
    RUN_TEST(widget_class_lease_rejects_copied_release);
    RUN_TEST(widget_class_module_quiesce_protects_instances);
    RUN_TEST(widget_class_module_retained_reference_blocks_destroy);
    RUN_TEST(widget_class_module_destroyed_token_fails_closed);
    RUN_TEST(widget_class_module_rejects_unknown_token_without_dereference);
    RUN_TEST(widget_class_module_unload_rejected_from_callback);
    RUN_TEST(widget_class_module_create_binds_until_destroy);
    RUN_TEST(widget_class_module_same_owner_replace_keeps_entry_count);
    RUN_TEST(yaml_loader_module_factory_quiesce_lifecycle);
    RUN_TEST(yaml_loader_module_bind_is_atomic_with_factory_completion);
    RUN_TEST(yaml_loader_module_replacement_preserves_entry_count);
    RUN_TEST(yaml_loader_module_migration_lease);
    RUN_TEST(yaml_loader_module_registration_rejects_invalid_without_locking);
    RUN_TEST(yaml_loader_module_schema_variants_share_quiesce);
    RUN_TEST(widget_class_runtime_snapshot_concurrent_readers);
    RUN_TEST(yaml_loader_runtime_factory_register_and_unregister);
    RUN_TEST(yaml_loader_runtime_dynamic_schema_owns_snapshot);
    RUN_TEST(yaml_loader_runtime_dynamic_schema_oom_preserves_snapshot);
    RUN_TEST(yaml_loader_runtime_dynamic_schema_rejects_invalid_without_allocating);
    RUN_TEST(yaml_loader_runtime_factory_concurrent_readers);
    RUN_TEST(yaml_loader_runtime_factory_rejects_invalid_and_reentrant_changes);
TEST_MAIN_END()
