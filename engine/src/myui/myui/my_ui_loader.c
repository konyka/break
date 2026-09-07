/**
 * @file my_ui_loader.c
 * @brief YAML UI loader.
 */
#include "myui/my_ui_loader.h"
#include "myui/my_widget_registry_internal.h"

const my_ui_loader_capabilities_t* my_ui_loader_capabilities(void) {
  static const my_ui_loader_capabilities_t capabilities = {
#ifdef MYUI_UI_YAML
      (uint32_t)(MY_UI_FEATURE_YAML_SCHEMA | MY_UI_FEATURE_CHILDREN |
                 MY_UI_FEATURE_BINDINGS | MY_UI_FEATURE_CSS_STYLE |
                 MY_UI_FEATURE_TYPE_QUERY | MY_UI_FEATURE_SCHEMA_MIGRATION |
                 MY_UI_FEATURE_DYNAMIC_SCHEMA),
#else
      0u,
#endif
      MY_UI_MAX_YAML_BYTES, MY_UI_MAX_FACTORIES, MY_UI_MAX_BIND_RULE_BYTES,
      (uint32_t)MY_UI_LOAD_STRICT_SCHEMA};
  return &capabilities;
}

#ifdef MYUI_UI_YAML

#include <errno.h>
#include <float.h>
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdatomic.h>
#include <string.h>

#include "core/platform_thread.h"
#include "myc/my_str.h"
#include "myui/my_css.h"
#include "myui/my_layout.h"
#include "myui/my_widget_class.h"

static const my_prop_desc_t UI_COMMON_PROPERTIES[] = {
    {"name", MY_PROP_STRING, NULL, NULL},
    {"tooltip", MY_PROP_STRING, NULL, NULL},
    {"class", MY_PROP_STRING, NULL, NULL},
    {"x", MY_PROP_INT, NULL, NULL},
    {"y", MY_PROP_INT, NULL, NULL},
    {"w", MY_PROP_INT, NULL, NULL},
    {"h", MY_PROP_INT, NULL, NULL},
    {"visible", MY_PROP_BOOL, NULL, NULL},
    {"enable", MY_PROP_BOOL, NULL, NULL},
    {"lp", MY_PROP_STRING, NULL, NULL},
    {"layout", MY_PROP_STRING, NULL, NULL},
    {"version", MY_PROP_INT, NULL, NULL},
    {NULL, MY_PROP_STRING, NULL, NULL}};

static const my_prop_desc_t UI_WINDOW_PROPERTIES[] = {
    {"title", MY_PROP_STRING, NULL, NULL},
    {"style", MY_PROP_STRING, NULL, NULL},
    {NULL, MY_PROP_STRING, NULL, NULL}};

static bool ui_is_common_key(const char* key) {
  static const char* const keys[] = {
      "type", "name", "tooltip", "class", "x", "y", "w", "h",
      "visible", "enable", "lp", "layout", "version", "children",
      "bindings"};
  size_t i;
  for (i = 0; i < sizeof(keys) / sizeof(keys[0]); i++) {
    if (my_str_eq(keys[i], key)) {
      return true;
    }
  }
  return false;
}

static bool ui_property_value_valid(my_prop_type_t type,
                                    const my_conf_node_t* value) {
  int64_t integer;
  double number;
  if (value == NULL) {
    return false;
  }
  if (type == MY_PROP_STRING) {
    return my_conf_type(value) == MY_CONF_STR;
  }
  if (type == MY_PROP_INT) {
    if (my_conf_type(value) != MY_CONF_INT64) {
      return false;
    }
    integer = my_conf_as_int64(value, 0);
    return integer >= INT32_MIN && integer <= INT32_MAX;
  }
  if (type == MY_PROP_FLOAT) {
    if (my_conf_type(value) == MY_CONF_INT64) {
      number = (double)my_conf_as_int64(value, 0);
    } else if (my_conf_type(value) == MY_CONF_DOUBLE) {
      number = my_conf_as_double(value, 0.0);
    } else {
      return false;
    }
    return isfinite(number) && number >= -FLT_MAX && number <= FLT_MAX;
  }
  if (type == MY_PROP_BOOL) {
    return my_conf_type(value) == MY_CONF_BOOL;
  }
  if (type == MY_PROP_COLOR) {
    if (my_conf_type(value) != MY_CONF_INT64) {
      return false;
    }
    integer = my_conf_as_int64(value, 0);
    return integer >= 0 && integer <= UINT32_MAX;
  }
  return false;
}

static bool ui_bounded_cstr_len(const char* text, size_t* length) {
  size_t i;
  for (i = 0; i < MY_UI_MAX_YAML_BYTES; i++) {
    if (text[i] == '\0') {
      *length = i;
      return true;
    }
  }
  return false;
}

typedef struct ui_factory_entry_t {
  char type[24];
  my_ui_factory_fn_t factory;
  const my_prop_desc_t* properties;
  const char* const* events;
  uint32_t schema_version;
  my_ui_schema_migrate_fn_t migrate;
  const my_ui_schema_migration_t* migrations;
  size_t migration_count;
  struct ui_owned_schema_t* owned_schema;
  my_widget_class_module_t* module;
} ui_factory_entry_t;

typedef struct ui_owned_schema_t {
  const my_allocator_t* allocator;
  my_prop_desc_t* properties;
  char** property_names;
  char** events;
  char** event_names;
} ui_owned_schema_t;

static void ui_owned_schema_destroy(ui_owned_schema_t* schema) {
  size_t i;
  if (schema == NULL) {
    return;
  }
  if (schema->property_names != NULL) {
    for (i = 0; i < MY_WIDGET_SCHEMA_MAX_PROPERTIES; i++) {
      if (schema->property_names[i] == NULL) {
        break;
      }
      my_mem_free(schema->allocator, schema->property_names[i]);
    }
  }
  if (schema->event_names != NULL) {
    for (i = 0; i < MY_WIDGET_SCHEMA_MAX_EVENTS; i++) {
      if (schema->event_names[i] == NULL) {
        break;
      }
      my_mem_free(schema->allocator, schema->event_names[i]);
    }
  }
  my_mem_free(schema->allocator, schema->property_names);
  my_mem_free(schema->allocator, schema->event_names);
  my_mem_free(schema->allocator, schema->properties);
  my_mem_free(schema->allocator, schema->events);
  my_mem_free(schema->allocator, schema);
}

static ui_owned_schema_t* ui_owned_schema_copy(
    const my_allocator_t* allocator, const my_ui_dynamic_schema_t* input) {
  ui_owned_schema_t* schema;
  size_t i;
  if (input == NULL || input->property_count > MY_WIDGET_SCHEMA_MAX_PROPERTIES ||
      input->event_count > MY_WIDGET_SCHEMA_MAX_EVENTS ||
      (input->property_count != 0u && input->properties == NULL) ||
      (input->event_count != 0u && input->events == NULL) ||
      !my_widget_schema_properties_n_valid(input->properties,
                                           input->property_count) ||
      !my_widget_schema_events_n_valid(input->events, input->event_count)) {
    return NULL;
  }
  schema = (ui_owned_schema_t*)my_mem_calloc(allocator, 1u, sizeof(*schema));
  if (schema == NULL) {
    return NULL;
  }
  schema->allocator = allocator;
  schema->properties = (my_prop_desc_t*)my_mem_calloc(
      allocator, input->property_count + 1u, sizeof(*schema->properties));
  schema->property_names = (char**)my_mem_calloc(
      allocator, input->property_count + 1u, sizeof(*schema->property_names));
  schema->events = (char**)my_mem_calloc(
      allocator, input->event_count + 1u, sizeof(*schema->events));
  schema->event_names = (char**)my_mem_calloc(
      allocator, input->event_count + 1u, sizeof(*schema->event_names));
  if (schema->properties == NULL || schema->property_names == NULL ||
      schema->events == NULL || schema->event_names == NULL) {
    ui_owned_schema_destroy(schema);
    return NULL;
  }
  for (i = 0; i < input->property_count; i++) {
    schema->property_names[i] =
        my_strdup(allocator, input->properties[i].name);
    if (schema->property_names[i] == NULL) {
      ui_owned_schema_destroy(schema);
      return NULL;
    }
    schema->properties[i] = input->properties[i];
    schema->properties[i].name = schema->property_names[i];
  }
  for (i = 0; i < input->event_count; i++) {
    schema->event_names[i] = my_strdup(allocator, input->events[i]);
    if (schema->event_names[i] == NULL) {
      ui_owned_schema_destroy(schema);
      return NULL;
    }
    schema->events[i] = schema->event_names[i];
  }
  return schema;
}

static ui_factory_entry_t g_factories[MY_UI_MAX_FACTORIES];
static size_t g_factory_count;
static bool g_factories_frozen;
static PlatformMutex g_registry_mutex;
static PlatformCond g_registry_cond;
static atomic_int g_registry_sync_state;
static size_t g_registry_readers;
static bool g_registry_writer;
static size_t g_registry_writers_waiting;
static _Thread_local unsigned g_registry_read_depth;
static bool ui_registry_callback_active(void) {
  return my_widget_registry_callback_active();
}

static void ui_registry_callback_enter(void) {
  my_widget_registry_callback_enter();
}

static void ui_registry_callback_leave(void) {
  my_widget_registry_callback_leave();
}

static my_ret_t ui_module_callback_enter(
    my_widget_class_module_t* module) {
  return my_widget_class_module_callback_acquire(module);
}

static void ui_module_callback_leave(my_widget_class_module_t* module) {
  my_widget_class_module_callback_release(module);
}

static void ui_registry_sync_init(void) {
  int expected = 0;
  if (atomic_compare_exchange_strong_explicit(&g_registry_sync_state,
                                              &expected, 1,
                                              memory_order_acq_rel,
          memory_order_acquire)) {
    platform_mutex_init(&g_registry_mutex);
    platform_cond_init(&g_registry_cond);
    /* Complete the class registry's lazy built-in setup before parallel reads. */
    (void)my_widget_class_find("widget");
    atomic_store_explicit(&g_registry_sync_state, 2, memory_order_release);
  } else {
    while (atomic_load_explicit(&g_registry_sync_state,
                                memory_order_acquire) != 2) {}
  }
}

static void ui_registry_read_lock(void) {
  if (g_registry_read_depth != 0u) {
    g_registry_read_depth++;
    return;
  }
  ui_registry_sync_init();
  platform_mutex_lock(&g_registry_mutex);
  while (g_registry_writer || g_registry_writers_waiting != 0u) {
    platform_cond_wait(&g_registry_cond, &g_registry_mutex);
  }
  g_registry_readers++;
  g_registry_read_depth = 1u;
  platform_mutex_unlock(&g_registry_mutex);
}

static void ui_registry_read_unlock(void) {
  if (g_registry_read_depth > 1u) {
    g_registry_read_depth--;
    return;
  }
  if (g_registry_read_depth == 0u) return;
  g_registry_read_depth = 0u;
  platform_mutex_lock(&g_registry_mutex);
  g_registry_readers--;
  if (g_registry_readers == 0u) {
    platform_cond_broadcast(&g_registry_cond);
  }
  platform_mutex_unlock(&g_registry_mutex);
}

static void ui_registry_write_lock(void) {
  ui_registry_sync_init();
  platform_mutex_lock(&g_registry_mutex);
  g_registry_writers_waiting++;
  while (g_registry_writer || g_registry_readers != 0u) {
    platform_cond_wait(&g_registry_cond, &g_registry_mutex);
  }
  g_registry_writers_waiting--;
  g_registry_writer = true;
  platform_mutex_unlock(&g_registry_mutex);
}

static void ui_registry_write_unlock(void) {
  platform_mutex_lock(&g_registry_mutex);
  g_registry_writer = false;
  platform_cond_broadcast(&g_registry_cond);
  platform_mutex_unlock(&g_registry_mutex);
}

static bool ui_type_name_len(const char* type, size_t* length) {
  size_t i;
  if (type == NULL || type[0] == '\0') {
    return false;
  }
  for (i = 0; i < sizeof(g_factories[0].type); i++) {
    if (type[i] == '\0') {
      *length = i;
      return true;
    }
  }
  return false;
}

static const ui_factory_entry_t* find_factory_entry(const char* type) {
  size_t i;
  for (i = 0; i < g_factory_count; i++) {
    if (my_str_eq(g_factories[i].type, type)) {
      return &g_factories[i];
    }
  }
  return NULL;
}

static bool ui_loader_builtin_type(const char* type) {
  return my_str_eq(type, "window") || my_widget_class_is_builtin_type(type);
}

static bool ui_migration_table_valid(
    const my_ui_schema_migration_t* migrations, size_t migration_count,
    uint32_t schema_version) {
  size_t i;
  if (migration_count > MY_UI_MAX_SCHEMA_MIGRATIONS ||
      (migration_count != 0u && migrations == NULL)) {
    return false;
  }
  for (i = 0; i < migration_count; i++) {
    const my_ui_schema_migration_t* step = &migrations[i];
    if (step->migrate == NULL || step->from_version >= step->to_version ||
        step->to_version > schema_version ||
        step->from_version == UINT32_MAX ||
        step->to_version != step->from_version + 1u ||
        (i > 0u && migrations[i - 1u].to_version != step->from_version)) {
      return false;
    }
  }
  return true;
}

static my_ui_error_code_t ui_error_code_for(const char* message) {
  if (strcmp(message, "unknown YAML load flags") == 0) {
    return MY_UI_ERROR_UNKNOWN_POLICY;
  }
  if (strncmp(message, "YAML input exceeds", 18) == 0) {
    return MY_UI_ERROR_INPUT_LIMIT;
  }
  if (strncmp(message, "invalid YAML", 12) == 0 ||
      strncmp(message, "invalid YAML file", 17) == 0) {
    return MY_UI_ERROR_INVALID_PARAMS;
  }
  if (strncmp(message, "yaml:", 5) == 0) {
    return MY_UI_ERROR_YAML_SYNTAX;
  }
  if (strcmp(message, "unknown widget type") == 0) {
    return MY_UI_ERROR_UNKNOWN_WIDGET;
  }
  if (strstr(message, "style") != NULL) {
    return MY_UI_ERROR_STYLE;
  }
  if (strstr(message, "memory") != NULL ||
      strncmp(message, "failed to", 9) == 0 ||
      strncmp(message, "cannot ", 7) == 0) {
    return MY_UI_ERROR_RESOURCE;
  }
  return MY_UI_ERROR_SCHEMA;
}

static uint32_t ui_error_capability_for(const char* message) {
  if (strstr(message, "children") != NULL) {
    return (uint32_t)MY_UI_FEATURE_CHILDREN;
  }
  if (strstr(message, "binding") != NULL ||
      strstr(message, "bind rules") != NULL) {
    return (uint32_t)MY_UI_FEATURE_BINDINGS;
  }
  if (strstr(message, "style") != NULL) {
    return (uint32_t)MY_UI_FEATURE_CSS_STYLE;
  }
  if (strcmp(message, "unknown widget type") == 0) {
    return (uint32_t)MY_UI_FEATURE_YAML_SCHEMA;
  }
  return 0u;
}

static void ui_fail(my_ui_error_t* err, const char* message) {
  if (err != NULL && err->message[0] == '\0') {
    err->code = ui_error_code_for(message);
    err->capability = ui_error_capability_for(message);
    snprintf(err->message, sizeof(err->message), "%s", message);
  }
}

static void ui_fail_field(my_ui_error_t* err, const char* message,
                          const char* field) {
  ui_fail(err, message);
  if (err != NULL && err->field[0] == '\0' && field != NULL) {
    snprintf(err->field, sizeof(err->field), "%s", field);
  }
  if (err != NULL && err->path[0] == '\0' && field != NULL) {
    snprintf(err->path, sizeof(err->path), "%s", field);
  }
}

static void ui_fail_field_path(my_ui_error_t* err, const char* message,
                               const char* field, const char* node_path) {
  ui_fail(err, message);
  if (err != NULL && err->field[0] == '\0' && field != NULL) {
    snprintf(err->field, sizeof(err->field), "%s", field);
  }
  if (err != NULL && err->path[0] == '\0' && field != NULL) {
    if (node_path == NULL || node_path[0] == '\0') {
      snprintf(err->path, sizeof(err->path), "%s", field);
    } else if (my_str_eq(node_path, "<path-truncated>")) {
      snprintf(err->path, sizeof(err->path), "%s", node_path);
    } else {
      snprintf(err->path, sizeof(err->path), "%s.%s", node_path, field);
    }
  }
}

static void ui_child_path(char* output, size_t capacity, const char* parent,
                          size_t index) {
  int written;
  if (parent != NULL && my_str_eq(parent, "<path-truncated>")) {
    snprintf(output, capacity, "%s", parent);
    return;
  }
  if (parent == NULL || parent[0] == '\0') {
    written = snprintf(output, capacity, "children[%zu]", index);
  } else {
    written = snprintf(output, capacity, "%s.children[%zu]", parent, index);
  }
  if (written < 0 || (size_t)written >= capacity) {
    snprintf(output, capacity, "<path-truncated>");
  }
}

static bool parse_linear_layout(const char* text, bool* horizontal,
                                int32_t* spacing);

static const my_conf_node_t* object_value(const my_conf_node_t* object,
                                          const char* key);

static const my_prop_desc_t* ui_find_property(const my_prop_desc_t* properties,
                                              const char* key) {
  const my_prop_desc_t* property;
  if (properties == NULL || key == NULL) {
    return NULL;
  }
  for (property = properties; property->name != NULL; property++) {
    if (my_str_eq(property->name, key)) {
      return property;
    }
  }
  return NULL;
}

static bool ui_common_value_valid(const char* key,
                                  const my_conf_node_t* value) {
  const my_prop_desc_t* property;
  size_t i;
  if (key == NULL || value == NULL) {
    return false;
  }
  if (my_str_eq(key, "type")) {
    return my_conf_type(value) == MY_CONF_STR;
  }
  if (my_str_eq(key, "version")) {
    int64_t version;
    if (my_conf_type(value) != MY_CONF_INT64) return false;
    version = my_conf_as_int64(value, -1);
    return version >= 0 && (uint64_t)version <= UINT32_MAX;
  }
  if (my_str_eq(key, "name") || my_str_eq(key, "tooltip") ||
      my_str_eq(key, "class") || my_str_eq(key, "lp")) {
    property = ui_find_property(UI_COMMON_PROPERTIES, key);
    return property != NULL && ui_property_value_valid(property->type, value);
  }
  if (my_str_eq(key, "x") || my_str_eq(key, "y") || my_str_eq(key, "w") ||
      my_str_eq(key, "h")) {
    return ui_property_value_valid(MY_PROP_INT, value);
  }
  if (my_str_eq(key, "visible") || my_str_eq(key, "enable")) {
    return ui_property_value_valid(MY_PROP_BOOL, value);
  }
  if (my_str_eq(key, "children")) {
    return my_conf_type(value) == MY_CONF_ARRAY;
  }
  if (my_str_eq(key, "bindings")) {
    if (my_conf_type(value) != MY_CONF_OBJECT) {
      return false;
    }
    for (i = 0; i < my_conf_child_count(value); i++) {
      const my_conf_node_t* binding = my_conf_child(value, i);
      if (my_conf_key(binding) == NULL ||
          my_conf_type(binding) != MY_CONF_STR) {
        return false;
      }
    }
    return true;
  }
  if (my_str_eq(key, "layout")) {
    bool horizontal;
    int32_t spacing;
    if (my_conf_type(value) != MY_CONF_STR) {
      return false;
    }
    return my_str_eq(my_conf_as_str(value, NULL), "default") ||
           parse_linear_layout(my_conf_as_str(value, NULL), &horizontal,
                               &spacing);
  }
  return true;
}

static bool ui_node_schema_valid(const my_conf_node_t* node,
                                 const my_prop_desc_t* properties, bool root,
                                 uint32_t flags, const char* node_path,
                                 my_ui_error_t* err) {
  size_t i;
  if ((flags & ~(uint32_t)MY_UI_LOAD_STRICT_SCHEMA) != 0u) {
    return false;
  }
  if ((flags & MY_UI_LOAD_STRICT_SCHEMA) == 0u) {
    return true;
  }
  if (my_conf_type(node) != MY_CONF_OBJECT) {
    ui_fail_field_path(err, "widget must be a map", "widget", node_path);
    return false;
  }
  for (i = 0; i < my_conf_child_count(node); i++) {
    const my_conf_node_t* child = my_conf_child(node, i);
    const char* key = my_conf_key(child);
    const my_prop_desc_t* prop;
    bool known = ui_is_common_key(key);
    if (known && !ui_common_value_valid(key, child)) {
      if (my_str_eq(key, "type")) {
        ui_fail_field_path(err, "widget requires a string type", key,
                           node_path);
      } else if (my_str_eq(key, "children")) {
        ui_fail_field_path(err, "children must be a sequence", key,
                           node_path);
      } else if (my_str_eq(key, "bindings") &&
                 my_conf_type(child) != MY_CONF_OBJECT) {
        ui_fail_field_path(err, "bindings must be a map", key, node_path);
      } else if (my_str_eq(key, "bindings")) {
        ui_fail_field_path(err, "binding values must be strings", key,
                           node_path);
      } else if (my_str_eq(key, "layout") &&
                 my_conf_type(child) == MY_CONF_STR) {
        ui_fail_field_path(err, "invalid layout syntax", key, node_path);
      } else {
        ui_fail_field_path(err, "invalid common widget property", key,
                           node_path);
      }
      return false;
    }
    if (root && (my_str_eq(key, "title") || my_str_eq(key, "style"))) {
      known = true;
      prop = ui_find_property(UI_WINDOW_PROPERTIES, key);
      if (!ui_property_value_valid(prop->type, child)) {
        ui_fail_field_path(err,
                           my_str_eq(key, "title") ? "title must be a string"
                                                    : "style must be a string",
                           key, node_path);
        return false;
      }
    }
    if (!known) {
      prop = ui_find_property(properties, key);
      if (prop != NULL) {
        known = true;
        if (!ui_property_value_valid(prop->type, child)) {
          ui_fail_field_path(err, "invalid typed widget property", key,
                             node_path);
          return false;
        }
      }
    }
    if (!known && properties != NULL) {
      ui_fail_field_path(err, "unknown YAML field", key, node_path);
      return false;
    }
  }
  return true;
}

static bool ui_validate_tree(const my_conf_node_t* node, bool root,
                             uint32_t flags, const char* node_path,
                             my_ui_error_t* err) {
  const my_conf_node_t* type_node;
  const my_conf_node_t* children;
  const ui_factory_entry_t* factory_entry;
  const my_widget_class_t* cls;
  const my_prop_desc_t* properties;
  const char* type;
  char child_path[MY_UI_ERROR_PATH_LEN];
  bool window_root;
  size_t i;
  if ((flags & MY_UI_LOAD_STRICT_SCHEMA) == 0u) {
    return true;
  }
  if (my_conf_type(node) != MY_CONF_OBJECT) {
    ui_fail_field_path(err, "widget must be a map", "widget", node_path);
    return false;
  }
  type_node = object_value(node, "type");
  if (type_node == NULL || my_conf_type(type_node) != MY_CONF_STR) {
    ui_fail_field_path(err, "widget requires a string type", "type",
                       node_path);
    return false;
  }
  type = my_conf_as_str(type_node, NULL);
  window_root = root && my_str_eq(type, "window");
  if (!root && my_str_eq(type, "window")) {
    ui_fail_field_path(err, "window is only allowed as root", "type",
                       node_path);
    return false;
  }
  factory_entry = find_factory_entry(type);
  cls = factory_entry == NULL ? my_widget_class_find(type) : NULL;
  if (window_root) {
    properties = UI_WINDOW_PROPERTIES;
  } else {
    properties = factory_entry != NULL
                     ? factory_entry->properties
                     : cls != NULL ? cls->props : NULL;
    if (factory_entry == NULL && cls == NULL) {
      ui_fail_field_path(err, "unknown widget type", "type", node_path);
      return false;
    }
  }
  if (!ui_node_schema_valid(node, properties, window_root, flags, node_path,
                            err)) {
    return false;
  }
  children = object_value(node, "children");
  if (children == NULL) {
    return true;
  }
  for (i = 0; i < my_conf_child_count(children); i++) {
    ui_child_path(child_path, sizeof(child_path), node_path, i);
    if (!ui_validate_tree(my_conf_child(children, i), false, flags,
                          child_path, err)) {
      return false;
    }
  }
  return true;
}

static my_ret_t ui_factory_register_locked(
    const char* type, my_ui_factory_fn_t factory,
    const my_prop_desc_t* properties, const char* const* events,
    uint32_t schema_version, my_ui_schema_migrate_fn_t migrate,
    const my_ui_schema_migration_t* migrations, size_t migration_count,
    ui_owned_schema_t* owned_schema, my_widget_class_module_t* module,
    bool allow_frozen) {
  size_t i;
  size_t type_len;
  size_t table_count;
  if (g_factories_frozen && !allow_frozen) return MY_RET_NOT_SUPPORTED;
  if (type == NULL || factory == NULL ||
      schema_version == 0u ||
      (migrate != NULL && migration_count != 0u) ||
      (migrate == NULL && migration_count == 0u && schema_version > 1u) ||
      !ui_type_name_len(type, &type_len) ||
      type_len >= sizeof(g_factories[0].type) ||
      !my_widget_schema_properties_valid(properties, &table_count) ||
      !my_widget_schema_events_valid(events, &table_count) ||
      !ui_migration_table_valid(migrations, migration_count,
                                schema_version)) {
    return MY_RET_INVALID_PARAMS;
  }
  for (i = 0; i < g_factory_count; i++) {
    if (my_str_eq(g_factories[i].type, type)) {
      ui_owned_schema_t* old_owned_schema = g_factories[i].owned_schema;
      my_widget_class_module_t* old_module = g_factories[i].module;
      if (module != old_module && module != NULL &&
          my_widget_class_module_register_entry(module) != MY_RET_OK) {
        return MY_RET_NOT_SUPPORTED;
      }
      g_factories[i].factory = factory;
      g_factories[i].properties = properties;
      g_factories[i].events = events;
      g_factories[i].schema_version = schema_version;
      g_factories[i].migrate = migrate;
      g_factories[i].migrations = migrations;
      g_factories[i].migration_count = migration_count;
      g_factories[i].owned_schema = owned_schema;
      g_factories[i].module = module;
      ui_owned_schema_destroy(old_owned_schema);
      if (old_module != NULL && old_module != module) {
        my_widget_class_module_unregister_entry(old_module);
      }
      return MY_RET_OK;
    }
  }
  if (g_factory_count >= MY_UI_MAX_FACTORIES) {
    return MY_RET_OOM;
  }
  if (module != NULL &&
      my_widget_class_module_register_entry(module) != MY_RET_OK) {
    return MY_RET_NOT_SUPPORTED;
  }
  snprintf(g_factories[g_factory_count].type, sizeof(g_factories[0].type), "%s", type);
  g_factories[g_factory_count].factory = factory;
  g_factories[g_factory_count].properties = properties;
  g_factories[g_factory_count].events = events;
  g_factories[g_factory_count].schema_version = schema_version;
  g_factories[g_factory_count].migrate = migrate;
  g_factories[g_factory_count].migrations = migrations;
  g_factories[g_factory_count].migration_count = migration_count;
  g_factories[g_factory_count].owned_schema = owned_schema;
  g_factories[g_factory_count].module = module;
  g_factory_count++;
  return MY_RET_OK;
}

static my_ret_t ui_factory_register(
    const char* type, my_ui_factory_fn_t factory,
    const my_prop_desc_t* properties, const char* const* events,
    uint32_t schema_version, my_ui_schema_migrate_fn_t migrate,
    const my_ui_schema_migration_t* migrations, size_t migration_count,
    ui_owned_schema_t* owned_schema) {
  my_ret_t ret;
  if (ui_registry_callback_active()) return MY_RET_NOT_SUPPORTED;
  ui_registry_write_lock();
  ret = ui_factory_register_locked(type, factory, properties, events,
                                   schema_version, migrate, migrations,
                                   migration_count, owned_schema, NULL, false);
  ui_registry_write_unlock();
  return ret;
}

my_ret_t my_ui_loader_freeze(void) {
  if (ui_registry_callback_active()) return MY_RET_NOT_SUPPORTED;
  ui_registry_write_lock();
  g_factories_frozen = true;
  ui_registry_write_unlock();
  return MY_RET_OK;
}

bool my_ui_loader_is_frozen(void) {
  bool frozen;
  ui_registry_read_lock();
  frozen = g_factories_frozen;
  ui_registry_read_unlock();
  return frozen;
}

my_ret_t my_ui_loader_register(const char* type, my_ui_factory_fn_t factory) {
  return ui_factory_register(type, factory, NULL, NULL, 1u, NULL, NULL, 0u,
                             NULL);
}

my_ret_t my_ui_loader_runtime_register_schema(
    const char* type, my_ui_factory_fn_t factory,
    const my_prop_desc_t* properties, const char* const* events) {
  my_ui_dynamic_schema_t input;
  ui_owned_schema_t* owned;
  size_t property_count;
  size_t event_count;
  my_ret_t ret;
  if (ui_registry_callback_active()) return MY_RET_NOT_SUPPORTED;
  if (!my_widget_schema_properties_valid(properties, &property_count) ||
      !my_widget_schema_events_valid(events, &event_count)) {
    return MY_RET_INVALID_PARAMS;
  }
  if (type == NULL || factory == NULL ||
      !ui_type_name_len(type, &(size_t){0})) {
    return MY_RET_INVALID_PARAMS;
  }
  ui_registry_write_lock();
  if (!g_factories_frozen) {
    ui_registry_write_unlock();
    return MY_RET_NOT_SUPPORTED;
  }
  if (ui_loader_builtin_type(type)) {
    ui_registry_write_unlock();
    return MY_RET_NOT_SUPPORTED;
  }
  input = (my_ui_dynamic_schema_t){properties, property_count, events,
                                  event_count};
  owned = ui_owned_schema_copy(NULL, &input);
  if (owned == NULL) {
    ui_registry_write_unlock();
    return MY_RET_OOM;
  }
  ret = ui_factory_register_locked(
      type, factory, owned->properties, (const char* const*)owned->events, 1u,
      NULL, NULL, 0u, owned, NULL, true);
  if (ret != MY_RET_OK) ui_owned_schema_destroy(owned);
  ui_registry_write_unlock();
  return ret;
}

my_ret_t my_ui_loader_runtime_register_schema_module(
    my_widget_class_module_t* module, const char* type,
    my_ui_factory_fn_t factory, const my_prop_desc_t* properties,
    const char* const* events) {
  my_ui_dynamic_schema_t input;
  ui_owned_schema_t* owned;
  size_t property_count;
  size_t event_count;
  my_ret_t ret;
  if (module == NULL || ui_registry_callback_active()) {
    return module == NULL ? MY_RET_INVALID_PARAMS : MY_RET_NOT_SUPPORTED;
  }
  if (type == NULL || factory == NULL ||
      !ui_type_name_len(type, &(size_t){0})) {
    return MY_RET_INVALID_PARAMS;
  }
  if (!my_widget_schema_properties_valid(properties, &property_count) ||
      !my_widget_schema_events_valid(events, &event_count)) {
    return MY_RET_INVALID_PARAMS;
  }
  ui_registry_write_lock();
  if (!g_factories_frozen || ui_loader_builtin_type(type)) {
    ui_registry_write_unlock();
    return MY_RET_NOT_SUPPORTED;
  }
  input = (my_ui_dynamic_schema_t){properties, property_count, events,
                                  event_count};
  owned = ui_owned_schema_copy(NULL, &input);
  if (owned == NULL) {
    ui_registry_write_unlock();
    return MY_RET_OOM;
  }
  ret = ui_factory_register_locked(
      type, factory, owned->properties, (const char* const*)owned->events, 1u,
      NULL, NULL, 0u, owned, module, true);
  if (ret != MY_RET_OK) ui_owned_schema_destroy(owned);
  ui_registry_write_unlock();
  return ret;
}

my_ret_t my_ui_loader_runtime_register_schema_ex_module(
    my_widget_class_module_t* module, const char* type,
    my_ui_factory_fn_t factory, const my_prop_desc_t* properties,
    const char* const* events, uint32_t schema_version,
    my_ui_schema_migrate_fn_t migrate) {
  my_ret_t ret;
  if (module == NULL || ui_registry_callback_active()) {
    return module == NULL ? MY_RET_INVALID_PARAMS : MY_RET_NOT_SUPPORTED;
  }
  if (type == NULL || factory == NULL ||
      !ui_type_name_len(type, &(size_t){0})) {
    return MY_RET_INVALID_PARAMS;
  }
  ui_registry_write_lock();
  if (!g_factories_frozen || ui_loader_builtin_type(type) ||
      schema_version == 0u ||
      (schema_version > 1u && migrate == NULL)) {
    ui_registry_write_unlock();
    return !g_factories_frozen || ui_loader_builtin_type(type)
               ? MY_RET_NOT_SUPPORTED
               : MY_RET_INVALID_PARAMS;
  }
  ret = ui_factory_register_locked(type, factory, properties, events,
                                   schema_version, migrate, NULL, 0u, NULL,
                                   module, true);
  ui_registry_write_unlock();
  return ret;
}

my_ret_t my_ui_loader_runtime_register_schema_chain_module(
    my_widget_class_module_t* module, const char* type,
    my_ui_factory_fn_t factory, const my_prop_desc_t* properties,
    const char* const* events, uint32_t schema_version,
    const my_ui_schema_migration_t* migrations, size_t migration_count) {
  my_ret_t ret;
  if (module == NULL || ui_registry_callback_active()) {
    return module == NULL ? MY_RET_INVALID_PARAMS : MY_RET_NOT_SUPPORTED;
  }
  if (type == NULL || factory == NULL ||
      !ui_type_name_len(type, &(size_t){0})) {
    return MY_RET_INVALID_PARAMS;
  }
  ui_registry_write_lock();
  if (!g_factories_frozen || ui_loader_builtin_type(type) ||
      schema_version == 0u ||
      (schema_version > 1u && migration_count == 0u)) {
    ui_registry_write_unlock();
    return !g_factories_frozen || ui_loader_builtin_type(type)
               ? MY_RET_NOT_SUPPORTED
               : MY_RET_INVALID_PARAMS;
  }
  ret = ui_factory_register_locked(type, factory, properties, events,
                                   schema_version, NULL, migrations,
                                   migration_count, NULL, module, true);
  ui_registry_write_unlock();
  return ret;
}

my_ret_t my_ui_loader_runtime_register_dynamic_schema(
    const my_allocator_t* allocator, const char* type,
    my_ui_factory_fn_t factory, const my_ui_dynamic_schema_t* schema,
    uint32_t schema_version, my_ui_schema_migrate_fn_t migrate) {
  ui_owned_schema_t* owned;
  my_ret_t ret;
  if (ui_registry_callback_active()) return MY_RET_NOT_SUPPORTED;
  ui_registry_write_lock();
  if (!g_factories_frozen) {
    ui_registry_write_unlock();
    return MY_RET_NOT_SUPPORTED;
  }
  if (type == NULL || factory == NULL || schema == NULL ||
      !ui_type_name_len(type, &(size_t){0})) {
    ui_registry_write_unlock();
    return MY_RET_INVALID_PARAMS;
  }
  if (ui_loader_builtin_type(type)) {
    ui_registry_write_unlock();
    return MY_RET_NOT_SUPPORTED;
  }
  if (schema_version == 0u ||
      (schema_version > 1u && migrate == NULL) ||
      !ui_type_name_len(type, &(size_t){0}) ||
      schema->property_count > MY_WIDGET_SCHEMA_MAX_PROPERTIES ||
      schema->event_count > MY_WIDGET_SCHEMA_MAX_EVENTS ||
      (schema->property_count != 0u && schema->properties == NULL) ||
      (schema->event_count != 0u && schema->events == NULL) ||
      !my_widget_schema_properties_n_valid(schema->properties,
                                           schema->property_count) ||
      !my_widget_schema_events_n_valid(schema->events, schema->event_count)) {
    ui_registry_write_unlock();
    return MY_RET_INVALID_PARAMS;
  }
  owned = ui_owned_schema_copy(allocator, schema);
  if (owned == NULL) {
    ui_registry_write_unlock();
    return MY_RET_OOM;
  }
  ret = ui_factory_register_locked(
      type, factory, owned->properties, (const char* const*)owned->events,
      schema_version, migrate, NULL, 0u, owned, NULL, true);
  if (ret != MY_RET_OK) ui_owned_schema_destroy(owned);
  ui_registry_write_unlock();
  return ret;
}

my_ret_t my_ui_loader_runtime_register_dynamic_schema_module(
    const my_allocator_t* allocator, my_widget_class_module_t* module,
    const char* type, my_ui_factory_fn_t factory,
    const my_ui_dynamic_schema_t* schema, uint32_t schema_version,
    my_ui_schema_migrate_fn_t migrate) {
  ui_owned_schema_t* owned;
  my_ret_t ret;
  if (module == NULL || ui_registry_callback_active()) {
    return module == NULL ? MY_RET_INVALID_PARAMS : MY_RET_NOT_SUPPORTED;
  }
  if (type == NULL || factory == NULL || schema == NULL ||
      !ui_type_name_len(type, &(size_t){0})) {
    return MY_RET_INVALID_PARAMS;
  }
  ui_registry_write_lock();
  if (!g_factories_frozen || ui_loader_builtin_type(type)) {
    ui_registry_write_unlock();
    return MY_RET_NOT_SUPPORTED;
  }
  if (schema_version == 0u ||
      (schema_version > 1u && migrate == NULL) ||
      schema->property_count > MY_WIDGET_SCHEMA_MAX_PROPERTIES ||
      schema->event_count > MY_WIDGET_SCHEMA_MAX_EVENTS ||
      (schema->property_count != 0u && schema->properties == NULL) ||
      (schema->event_count != 0u && schema->events == NULL) ||
      !my_widget_schema_properties_n_valid(schema->properties,
                                           schema->property_count) ||
      !my_widget_schema_events_n_valid(schema->events, schema->event_count)) {
    ui_registry_write_unlock();
    return MY_RET_INVALID_PARAMS;
  }
  owned = ui_owned_schema_copy(allocator, schema);
  if (owned == NULL) {
    ui_registry_write_unlock();
    return MY_RET_OOM;
  }
  ret = ui_factory_register_locked(
      type, factory, owned->properties, (const char* const*)owned->events,
      schema_version, migrate, NULL, 0u, owned, module, true);
  if (ret != MY_RET_OK) ui_owned_schema_destroy(owned);
  ui_registry_write_unlock();
  return ret;
}

my_ret_t my_ui_loader_runtime_unregister(const char* type) {
  size_t i;
  ui_owned_schema_t* owned;
  if (ui_registry_callback_active()) return MY_RET_NOT_SUPPORTED;
  if (type == NULL || !ui_type_name_len(type, &(size_t){0})) {
    return MY_RET_INVALID_PARAMS;
  }
  ui_registry_write_lock();
  if (!g_factories_frozen) {
    ui_registry_write_unlock();
    return MY_RET_NOT_SUPPORTED;
  }
  for (i = 0u; i < g_factory_count; ++i) {
    if (my_str_eq(g_factories[i].type, type)) break;
  }
  if (i == g_factory_count) {
    ui_registry_write_unlock();
    return MY_RET_NOT_FOUND;
  }
  if (ui_loader_builtin_type(type)) {
    ui_registry_write_unlock();
    return MY_RET_NOT_SUPPORTED;
  }
  owned = g_factories[i].owned_schema;
  if (g_factories[i].module != NULL) {
    my_widget_class_module_unregister_entry(g_factories[i].module);
  }
  if (i + 1u < g_factory_count) {
    memmove(&g_factories[i], &g_factories[i + 1u],
            (g_factory_count - i - 1u) * sizeof(g_factories[0]));
  }
  g_factory_count--;
  memset(&g_factories[g_factory_count], 0, sizeof(g_factories[0]));
  ui_owned_schema_destroy(owned);
  ui_registry_write_unlock();
  return MY_RET_OK;
}

my_ret_t my_ui_loader_register_dynamic_schema(
    const my_allocator_t* allocator, const char* type,
    my_ui_factory_fn_t factory,
    const my_ui_dynamic_schema_t* schema, uint32_t schema_version,
    my_ui_schema_migrate_fn_t migrate) {
  ui_owned_schema_t* owned;
  my_ret_t ret;
  if (ui_registry_callback_active()) return MY_RET_NOT_SUPPORTED;
  ui_registry_write_lock();
  if (g_factories_frozen) {
    ui_registry_write_unlock();
    return MY_RET_NOT_SUPPORTED;
  }
  if (type == NULL || factory == NULL || schema_version == 0u ||
      (schema_version > 1u && migrate == NULL) ||
      !ui_type_name_len(type, &(size_t){0}) || schema == NULL ||
      schema->property_count > MY_WIDGET_SCHEMA_MAX_PROPERTIES ||
      schema->event_count > MY_WIDGET_SCHEMA_MAX_EVENTS ||
      (schema->property_count != 0u && schema->properties == NULL) ||
      (schema->event_count != 0u && schema->events == NULL) ||
      !my_widget_schema_properties_n_valid(schema->properties,
                                           schema->property_count) ||
      !my_widget_schema_events_n_valid(schema->events, schema->event_count)) {
    ui_registry_write_unlock();
    return MY_RET_INVALID_PARAMS;
  }
  owned = ui_owned_schema_copy(allocator, schema);
  if (owned == NULL) {
    ui_registry_write_unlock();
    return MY_RET_OOM;
  }
  ret = ui_factory_register_locked(type, factory, owned->properties,
                                   (const char* const*)owned->events,
                                   schema_version, migrate, NULL, 0u, owned,
                                   NULL, false);
  if (ret != MY_RET_OK) {
    ui_owned_schema_destroy(owned);
  }
  ui_registry_write_unlock();
  return ret;
}

my_ret_t my_ui_loader_register_schema(const char* type,
                                      my_ui_factory_fn_t factory,
                                      const my_prop_desc_t* properties,
                                      const char* const* events) {
  return ui_factory_register(type, factory, properties, events, 1u, NULL, NULL,
                             0u, NULL);
}

my_ret_t my_ui_loader_register_schema_ex(
    const char* type, my_ui_factory_fn_t factory,
    const my_prop_desc_t* properties, const char* const* events,
    uint32_t schema_version, my_ui_schema_migrate_fn_t migrate) {
  my_ret_t ret;
  if (ui_registry_callback_active()) return MY_RET_NOT_SUPPORTED;
  ui_registry_write_lock();
  if (g_factories_frozen) {
    ui_registry_write_unlock();
    return MY_RET_NOT_SUPPORTED;
  }
  if (schema_version == 0u || (schema_version > 1u && migrate == NULL)) {
    ui_registry_write_unlock();
    return MY_RET_INVALID_PARAMS;
  }
  ret = ui_factory_register_locked(type, factory, properties, events,
                                   schema_version, migrate, NULL, 0u, NULL,
                                   NULL, false);
  ui_registry_write_unlock();
  return ret;
}

my_ret_t my_ui_loader_register_schema_chain(
    const char* type, my_ui_factory_fn_t factory,
    const my_prop_desc_t* properties, const char* const* events,
    uint32_t schema_version, const my_ui_schema_migration_t* migrations,
    size_t migration_count) {
  my_ret_t ret;
  if (ui_registry_callback_active()) return MY_RET_NOT_SUPPORTED;
  ui_registry_write_lock();
  if (g_factories_frozen) {
    ui_registry_write_unlock();
    return MY_RET_NOT_SUPPORTED;
  }
  if (schema_version == 0u ||
      (schema_version > 1u && migration_count == 0u)) {
    ui_registry_write_unlock();
    return MY_RET_INVALID_PARAMS;
  }
  ret = ui_factory_register_locked(type, factory, properties, events,
                                   schema_version, NULL, migrations,
                                   migration_count, NULL, NULL, false);
  ui_registry_write_unlock();
  return ret;
}

my_ret_t my_ui_loader_query_type(const char* type, my_ui_type_info_t* info) {
  const ui_factory_entry_t* factory;
  const my_widget_class_t* cls;
  const my_prop_desc_t* prop;
  size_t type_len;
  size_t table_count;
  if (info == NULL || type == NULL) {
    return MY_RET_INVALID_PARAMS;
  }
  memset(info, 0, sizeof(*info));
  ui_registry_read_lock();
  if (!ui_type_name_len(type, &type_len) ||
      type_len >= sizeof(g_factories[0].type)) {
    ui_registry_read_unlock();
    return MY_RET_INVALID_PARAMS;
  }
  factory = find_factory_entry(type);
  if (factory != NULL &&
      (!my_widget_schema_properties_valid(factory->properties, &table_count) ||
       !my_widget_schema_events_valid(factory->events, &table_count))) {
    ui_registry_read_unlock();
    return MY_RET_FAIL;
  }
  cls = my_widget_class_find(type);
  if (factory == NULL && cls == NULL && !my_str_eq(type, "window")) {
    ui_registry_read_unlock();
    return MY_RET_NOT_SUPPORTED;
  }
  info->type = factory != NULL ? factory->type
                               : cls != NULL ? cls->type : "window";
  info->factory_registered = factory != NULL;
  info->schema_version = factory != NULL ? factory->schema_version : 1u;
  info->migration_supported =
      factory != NULL &&
      (factory->migrate != NULL || factory->migration_count != 0u);
  info->common_properties = UI_COMMON_PROPERTIES;
  info->common_property_count =
      sizeof(UI_COMMON_PROPERTIES) / sizeof(UI_COMMON_PROPERTIES[0]) - 1u;
  info->schema_known = (cls != NULL || my_str_eq(type, "window") ||
                        (factory != NULL && factory->properties != NULL)) &&
                       (factory == NULL || factory->properties != NULL);
  if (!info->schema_known) {
    snprintf(info->type_storage, sizeof(info->type_storage), "%s", info->type);
    info->type = info->type_storage;
    ui_registry_read_unlock();
    return MY_RET_OK;
  }
  {
    const my_prop_desc_t* source_properties = my_str_eq(type, "window")
                                                   ? UI_WINDOW_PROPERTIES
                                                   : factory != NULL
                                                         ? factory->properties
                                                         : cls->props;
    for (prop = source_properties; prop != NULL && prop->name != NULL &&
                                  info->property_count < MY_UI_MAX_TYPE_PROPERTIES;
         prop++) {
      info->property_storage[info->property_count] = *prop;
      snprintf(info->property_name_storage[info->property_count],
               sizeof(info->property_name_storage[0]), "%s", prop->name);
      info->property_storage[info->property_count].name =
          info->property_name_storage[info->property_count];
      info->property_count++;
    }
  }
  info->properties = info->property_storage;
  info->events = NULL;
  {
    const char* const* source_events =
        factory != NULL ? factory->events : cls != NULL ? cls->events : NULL;
    while (source_events != NULL && source_events[info->event_count] != NULL &&
           info->event_count < MY_UI_MAX_TYPE_EVENTS) {
      snprintf(info->event_name_storage[info->event_count],
               sizeof(info->event_name_storage[0]), "%s",
               source_events[info->event_count]);
      info->event_storage[info->event_count] =
          info->event_name_storage[info->event_count];
      info->event_count++;
    }
    if (info->event_count != 0u) info->events = info->event_storage;
  }
  snprintf(info->type_storage, sizeof(info->type_storage), "%s", info->type);
  info->type = info->type_storage;
  ui_registry_read_unlock();
  return MY_RET_OK;
}

static const my_conf_node_t* object_value(const my_conf_node_t* object,
                                          const char* key) {
  size_t i;
  if (my_conf_type(object) != MY_CONF_OBJECT) {
    return NULL;
  }
  for (i = 0; i < my_conf_child_count(object); i++) {
    my_conf_node_t* child = my_conf_child(object, i);
    if (my_str_eq(my_conf_key(child), key)) {
      return child;
    }
  }
  return NULL;
}

static bool ui_migration_contract_valid(const my_conf_node_t* node,
                                        const char* type,
                                        uint32_t expected_version,
                                        const char* node_path,
                                        my_ui_error_t* err) {
  const my_conf_node_t* type_node = object_value(node, "type");
  const my_conf_node_t* version_node = object_value(node, "version");
  if (type_node == NULL || my_conf_type(type_node) != MY_CONF_STR ||
      !my_str_eq(my_conf_as_str(type_node, NULL), type)) {
    ui_fail_field_path(err, "schema migration changed widget type", "type",
                       node_path);
    return false;
  }
  if (version_node != NULL) {
    int64_t version;
    if (my_conf_type(version_node) != MY_CONF_INT64) {
      ui_fail_field_path(err, "invalid schema version", "version", node_path);
      return false;
    }
    version = my_conf_as_int64(version_node, -1);
    if (version < 0 || (uint64_t)version > UINT32_MAX ||
        (uint32_t)version != expected_version) {
      ui_fail_field_path(err, "schema version is newer than supported",
                         "version", node_path);
      return false;
    }
  }
  return true;
}

static my_ret_t ui_migration_commit_version(const my_allocator_t* allocator,
                                            my_conf_node_t* node,
                                            uint32_t version,
                                            const char* node_path,
                                            my_ui_error_t* err) {
  my_conf_node_t* version_node = my_conf_new_int64(allocator, version);
  if (version_node == NULL) {
    ui_fail_field_path(err, "failed to commit schema version", "version",
                       node_path);
    return MY_RET_OOM;
  }
  if (my_conf_object_set(node, "version", version_node) != MY_RET_OK) {
    my_conf_destroy(version_node);
    ui_fail_field_path(err, "failed to commit schema version", "version",
                       node_path);
    return MY_RET_FAIL;
  }
  return MY_RET_OK;
}

static my_ret_t ui_migrate_tree(const my_allocator_t* allocator,
                                my_conf_node_t* node, bool root,
                                const char* node_path, size_t depth,
                                my_ui_error_t* err) {
  const my_conf_node_t* type_node;
  const my_conf_node_t* version_node;
  const my_conf_node_t* children;
  const my_widget_class_t* cls;
  const ui_factory_entry_t* factory_entry;
  my_widget_class_module_t* module;
  const char* type;
  uint32_t from_version;
  uint32_t schema_version;
  char child_path[MY_UI_ERROR_PATH_LEN];
  size_t i;
  my_ret_t ret;

  if (depth >= MY_CONF_YAML_MAX_DEPTH) {
    ui_fail_field_path(err, "widget nesting exceeds resource budget", "widget",
                       node_path);
    return MY_RET_FAIL;
  }
  if (my_conf_type(node) != MY_CONF_OBJECT) {
    ui_fail_field_path(err, "widget must be a map", "widget", node_path);
    return MY_RET_FAIL;
  }
  type_node = object_value(node, "type");
  if (type_node == NULL || my_conf_type(type_node) != MY_CONF_STR) {
    ui_fail_field_path(err, "widget requires a string type", "type",
                       node_path);
    return MY_RET_FAIL;
  }
  type = my_conf_as_str(type_node, NULL);
  if (!root && my_str_eq(type, "window")) {
    ui_fail_field_path(err, "window is only allowed as root", "type",
                       node_path);
    return MY_RET_FAIL;
  }
  factory_entry = find_factory_entry(type);
  module = factory_entry != NULL ? factory_entry->module : NULL;
  cls = factory_entry == NULL ? my_widget_class_find(type) : NULL;
  if (factory_entry == NULL && cls == NULL &&
      !(root && my_str_eq(type, "window"))) {
    ui_fail_field_path(err, "unknown widget type", "type", node_path);
    return MY_RET_FAIL;
  }
  schema_version = factory_entry != NULL ? factory_entry->schema_version : 1u;
  version_node = object_value(node, "version");
  if (version_node == NULL) {
    from_version = schema_version;
  } else {
    int64_t version;
    if (my_conf_type(version_node) != MY_CONF_INT64) {
      ui_fail_field_path(err, "invalid schema version", "version", node_path);
      return MY_RET_FAIL;
    }
    version = my_conf_as_int64(version_node, -1);
    if (version < 0 || (uint64_t)version > UINT32_MAX) {
      ui_fail_field_path(err, "invalid schema version", "version", node_path);
      return MY_RET_FAIL;
    }
    from_version = (uint32_t)version;
  }
  if (from_version > schema_version) {
    ui_fail_field_path(err, "schema version is newer than supported", "version",
                       node_path);
    return MY_RET_FAIL;
  }
  if (from_version < schema_version) {
    if (factory_entry == NULL ||
        (factory_entry->migrate == NULL &&
         factory_entry->migration_count == 0u)) {
      ui_fail_field_path(err, "schema migration is unavailable", "version",
                         node_path);
      return MY_RET_FAIL;
    }
    if (factory_entry->migrate != NULL) {
      if (ui_module_callback_enter(module) != MY_RET_OK) {
        ui_fail_field_path(err, "widget module is quiescing", "version",
                           node_path);
        return MY_RET_NOT_SUPPORTED;
      }
      ui_registry_callback_enter();
      ret = factory_entry->migrate(allocator, node, from_version,
                                   schema_version);
      ui_registry_callback_leave();
      ui_module_callback_leave(module);
      if (ret != MY_RET_OK) {
        ui_fail_field_path(err,
                           ret == MY_RET_OOM ? "schema migration out of memory"
                                             : "schema migration failed",
                           "version", node_path);
        return ret == MY_RET_OOM ? MY_RET_OOM : MY_RET_FAIL;
      }
      if (!ui_migration_contract_valid(node, type, from_version, node_path,
                                       err)) {
        return MY_RET_FAIL;
      }
      ret = ui_migration_commit_version(allocator, node, schema_version,
                                        node_path, err);
      if (ret != MY_RET_OK) {
        return ret;
      }
    } else {
      uint32_t current_version = from_version;
      size_t step_count = 0u;
      while (current_version < schema_version &&
             step_count < MY_UI_MAX_SCHEMA_MIGRATIONS) {
        const my_ui_schema_migration_t* step = NULL;
        size_t step_index;
        for (step_index = 0u; step_index < factory_entry->migration_count;
             step_index++) {
          if (factory_entry->migrations[step_index].from_version ==
              current_version) {
            step = &factory_entry->migrations[step_index];
            break;
          }
        }
        if (step == NULL) {
          ui_fail_field_path(err, "schema migration is unavailable", "version",
                             node_path);
          return MY_RET_FAIL;
        }
        if (ui_module_callback_enter(module) != MY_RET_OK) {
          ui_fail_field_path(err, "widget module is quiescing", "version",
                             node_path);
          return MY_RET_NOT_SUPPORTED;
        }
        ui_registry_callback_enter();
        ret = step->migrate(allocator, node, step->from_version,
                            step->to_version);
        ui_registry_callback_leave();
        ui_module_callback_leave(module);
        if (ret != MY_RET_OK) {
          ui_fail_field_path(
              err, ret == MY_RET_OOM ? "schema migration out of memory"
                                     : "schema migration failed",
              "version", node_path);
          return ret == MY_RET_OOM ? MY_RET_OOM : MY_RET_FAIL;
        }
        if (!ui_migration_contract_valid(node, type, current_version, node_path,
                                         err)) {
          return MY_RET_FAIL;
        }
        ret = ui_migration_commit_version(allocator, node, step->to_version,
                                          node_path, err);
        if (ret != MY_RET_OK) {
          return ret;
        }
        current_version = step->to_version;
        step_count++;
      }
      if (current_version != schema_version) {
        ui_fail_field_path(err, "schema migration is unavailable", "version",
                           node_path);
        return MY_RET_FAIL;
      }
    }
  }
  children = object_value(node, "children");
  if (children == NULL) {
    return MY_RET_OK;
  }
  if (my_conf_type(children) != MY_CONF_ARRAY) {
    return MY_RET_OK;
  }
  for (i = 0; i < my_conf_child_count(children); i++) {
    ui_child_path(child_path, sizeof(child_path), node_path, i);
    ret = ui_migrate_tree(allocator, my_conf_child(children, i), false,
                          child_path, depth + 1u, err);
    if (ret != MY_RET_OK) {
      return ret;
    }
  }
  return MY_RET_OK;
}

static bool value_int32(const my_conf_node_t* node, int32_t fallback,
                        int32_t* out) {
  int64_t value;
  if (node == NULL) {
    *out = fallback;
    return true;
  }
  if (my_conf_type(node) != MY_CONF_INT64) {
    return false;
  }
  value = my_conf_as_int64(node, 0);
  if (value < INT32_MIN || value > INT32_MAX) {
    return false;
  }
  *out = (int32_t)value;
  return true;
}

static bool value_bool(const my_conf_node_t* node, bool fallback, bool* out) {
  if (node == NULL) {
    *out = fallback;
    return true;
  }
  if (my_conf_type(node) != MY_CONF_BOOL) {
    return false;
  }
  *out = my_conf_as_bool(node, fallback);
  return true;
}

static my_ret_t set_typed_property(my_widget_t* widget,
                                   const my_prop_desc_t* prop,
                                   const my_conf_node_t* node,
                                   my_widget_class_module_t* module) {
  my_value_t value;
  my_ret_t ret = MY_RET_FAIL;
  my_value_init(&value, ((my_object_t*)widget)->allocator);
  if (prop->type == MY_PROP_STRING && my_conf_type(node) == MY_CONF_STR) {
    ret = my_value_set_str(&value, my_conf_as_str(node, NULL));
  } else if (prop->type == MY_PROP_INT && my_conf_type(node) == MY_CONF_INT64) {
    int64_t number = my_conf_as_int64(node, 0);
    ret = number >= INT32_MIN && number <= INT32_MAX
              ? my_value_set_int32(&value, (int32_t)number)
              : MY_RET_FAIL;
  } else if (prop->type == MY_PROP_FLOAT &&
             (my_conf_type(node) == MY_CONF_INT64 ||
              my_conf_type(node) == MY_CONF_DOUBLE)) {
    double number = my_conf_type(node) == MY_CONF_INT64
                        ? (double)my_conf_as_int64(node, 0)
                        : my_conf_as_double(node, 0.0);
    ret = isfinite(number) && number >= -FLT_MAX && number <= FLT_MAX
              ? my_value_set_float(&value, (float)number)
              : MY_RET_FAIL;
  } else if (prop->type == MY_PROP_BOOL && my_conf_type(node) == MY_CONF_BOOL) {
    ret = my_value_set_bool(&value, my_conf_as_bool(node, false));
  } else if (prop->type == MY_PROP_COLOR &&
             my_conf_type(node) == MY_CONF_INT64) {
    int64_t color = my_conf_as_int64(node, -1);
    ret = color >= 0 && (uint64_t)color <= UINT32_MAX
              ? my_value_set_uint32(&value, (uint32_t)color)
              : MY_RET_FAIL;
  }
  if (ret == MY_RET_OK) {
    if (ui_module_callback_enter(module) != MY_RET_OK) {
      my_value_reset(&value);
      return MY_RET_NOT_SUPPORTED;
    }
    ui_registry_callback_enter();
    ret = prop->set(widget, &value);
    ui_registry_callback_leave();
    ui_module_callback_leave(module);
  }
  my_value_reset(&value);
  return ret;
}

static my_ret_t apply_schema_props(my_widget_t* widget,
                                  const my_prop_desc_t* properties,
                                  const my_conf_node_t* node,
                                  const char* node_path,
                                  my_ui_error_t* err,
                                  my_widget_class_module_t* module) {
  const my_prop_desc_t* prop;
  if (properties == NULL) {
    return MY_RET_OK;
  }
  for (prop = properties; prop->name != NULL; prop++) {
    const my_conf_node_t* value = object_value(node, prop->name);
    if (value != NULL && prop->set != NULL &&
        set_typed_property(widget, prop, value, module) != MY_RET_OK) {
      ui_fail_field_path(err, "invalid typed widget property", prop->name,
                         node_path);
      return MY_RET_FAIL;
    }
  }
  return MY_RET_OK;
}

static my_ret_t apply_bindings(my_widget_t* widget, const my_conf_node_t* node,
                               const char* node_path, my_ui_error_t* err) {
  const my_conf_node_t* bindings = object_value(node, "bindings");
  char rules[MY_UI_MAX_BIND_RULE_BYTES];
  size_t used = 0;
  size_t i;
  if (bindings == NULL) {
    return MY_RET_OK;
  }
  if (my_conf_type(bindings) != MY_CONF_OBJECT) {
    ui_fail_field_path(err, "bindings must be a map", "bindings", node_path);
    return MY_RET_FAIL;
  }
  for (i = 0; i < my_conf_child_count(bindings); i++) {
    my_conf_node_t* value = my_conf_child(bindings, i);
    const char* key = my_conf_key(value);
    const char* text;
    int wrote;
    if (key == NULL || my_conf_type(value) != MY_CONF_STR) {
      ui_fail_field_path(err, "binding values must be strings", "bindings",
                         node_path);
      return MY_RET_FAIL;
    }
    text = my_conf_as_str(value, NULL);
    wrote = snprintf(rules + used, sizeof(rules) - used, "v:%s=%s;", key, text);
    if (wrote < 0 || (size_t)wrote >= sizeof(rules) - used) {
      ui_fail_field_path(err, "bind rules too long", "bindings", node_path);
      return MY_RET_FAIL;
    }
    used += (size_t)wrote;
  }
  return used == 0 ? MY_RET_OK : my_widget_set_bind_rules(widget, rules);
}

static bool parse_linear_layout(const char* text, bool* horizontal,
                                int32_t* spacing) {
  const char* value;
  char* end;
  long parsed;
  if (text == NULL || strncmp(text, "linear:", 7) != 0) {
    return false;
  }
  if (text[7] == 'h') {
    *horizontal = true;
  } else if (text[7] == 'v') {
    *horizontal = false;
  } else {
    return false;
  }
  value = text + 8;
  if (*value == '\0') {
    *spacing = 0;
    return true;
  }
  if (*value != ':') {
    return false;
  }
  value++;
  if (*value == '\0') {
    return false;
  }
  errno = 0;
  parsed = strtol(value, &end, 10);
  if (errno == ERANGE || *end != '\0' || parsed < INT32_MIN ||
      parsed > INT32_MAX) {
    return false;
  }
  *spacing = (int32_t)parsed;
  return true;
}

static my_ret_t apply_common(my_widget_t* widget, const my_conf_node_t* node,
                             const char* node_path, my_ui_error_t* err) {
  const my_conf_node_t* value;
  const char* text;
  int32_t x, y, w, h;
  bool visible, enable;
  if (my_conf_type(node) != MY_CONF_OBJECT) {
    ui_fail_field_path(err, "invalid common widget property", "widget",
                       node_path);
    return MY_RET_FAIL;
  }
  if (!value_int32(object_value(node, "x"), 0, &x)) {
    ui_fail_field_path(err, "invalid common widget property", "x", node_path);
    return MY_RET_FAIL;
  }
  if (!value_int32(object_value(node, "y"), 0, &y)) {
    ui_fail_field_path(err, "invalid common widget property", "y", node_path);
    return MY_RET_FAIL;
  }
  if (!value_int32(object_value(node, "w"), 0, &w)) {
    ui_fail_field_path(err, "invalid common widget property", "w", node_path);
    return MY_RET_FAIL;
  }
  if (!value_int32(object_value(node, "h"), 0, &h)) {
    ui_fail_field_path(err, "invalid common widget property", "h", node_path);
    return MY_RET_FAIL;
  }
  if (!value_bool(object_value(node, "visible"), true, &visible)) {
    ui_fail_field_path(err, "invalid common widget property", "visible",
                       node_path);
    return MY_RET_FAIL;
  }
  if (!value_bool(object_value(node, "enable"), true, &enable)) {
    ui_fail_field_path(err, "invalid common widget property", "enable",
                       node_path);
    return MY_RET_FAIL;
  }
  value = object_value(node, "name");
  if (value != NULL) {
    if (my_conf_type(value) != MY_CONF_STR) {
      ui_fail_field_path(err, "name must be a string", "name", node_path);
      return MY_RET_FAIL;
    }
    if (my_widget_set_name(widget, my_conf_as_str(value, NULL)) != MY_RET_OK) {
      ui_fail_field_path(err, "failed to set widget name", "name", node_path);
      return MY_RET_FAIL;
    }
  }
  my_widget_set_rect(widget, &(my_rect_t){x, y, w, h});
  my_widget_set_visible(widget, visible);
  widget->enable = enable;
  value = object_value(node, "tooltip");
  if (value != NULL) {
    if (my_conf_type(value) != MY_CONF_STR) {
      ui_fail_field_path(err, "tooltip must be a string", "tooltip", node_path);
      return MY_RET_FAIL;
    }
    if (my_widget_set_tooltip(widget, my_conf_as_str(value, NULL)) !=
        MY_RET_OK) {
      ui_fail_field_path(err, "failed to set widget tooltip", "tooltip",
                         node_path);
      return MY_RET_FAIL;
    }
  }
  value = object_value(node, "class");
  if (value != NULL) {
    if (my_conf_type(value) != MY_CONF_STR) {
      ui_fail_field_path(err, "class must be a string", "class", node_path);
      return MY_RET_FAIL;
    }
    if (my_widget_set_style_class(widget, my_conf_as_str(value, NULL)) !=
        MY_RET_OK) {
      ui_fail_field_path(err, "failed to set widget class", "class", node_path);
      return MY_RET_FAIL;
    }
  }
  value = object_value(node, "lp");
  if (value != NULL && (my_conf_type(value) != MY_CONF_STR ||
                        my_widget_set_layout_params(widget,
                            my_conf_as_str(value, NULL)) != MY_RET_OK)) {
    ui_fail_field_path(err, "invalid lp", "lp", node_path);
    return MY_RET_FAIL;
  }
  value = object_value(node, "layout");
  if (value != NULL) {
    my_layouter_t* layouter;
    bool horizontal;
    int32_t spacing;
    if (my_conf_type(value) != MY_CONF_STR) {
      ui_fail_field_path(err, "layout must be a string", "layout", node_path);
      return MY_RET_FAIL;
    }
    text = my_conf_as_str(value, NULL);
    if (my_str_eq(text, "default")) {
    } else if (!parse_linear_layout(text, &horizontal, &spacing)) {
      ui_fail_field_path(err, "invalid layout syntax", "layout", node_path);
      return MY_RET_FAIL;
    } else {
      layouter = my_layouter_linear_create(
          ((my_object_t*)widget)->allocator, horizontal, spacing);
      if (layouter == NULL) {
        ui_fail_field_path(err, "failed to create layout", "layout", node_path);
        return MY_RET_OOM;
      }
      if (my_widget_set_layouter(widget, layouter) != MY_RET_OK) {
        if (layouter->destroy != NULL) {
          layouter->destroy(layouter);
        }
        ui_fail_field_path(err, "failed to set layout", "layout", node_path);
        return MY_RET_FAIL;
      }
    }
  }
  return apply_bindings(widget, node, node_path, err);
}

static my_widget_t* build_node(const my_allocator_t* allocator, my_pal_t* pal,
                               const my_conf_node_t* node, uint32_t flags,
                               const char* node_path, my_ui_error_t* err);

static my_widget_t* build_children(const my_allocator_t* allocator, my_pal_t* pal,
                                   my_widget_t* parent, const my_conf_node_t* node,
                                   uint32_t flags, const char* node_path,
                                   my_ui_error_t* err) {
  const my_conf_node_t* children = object_value(node, "children");
  char child_path[MY_UI_ERROR_PATH_LEN];
  size_t i;
  if (children == NULL) {
    return parent;
  }
  if (my_conf_type(children) != MY_CONF_ARRAY) {
    ui_fail_field_path(err, "children must be a sequence", "children",
                       node_path);
    return NULL;
  }
  for (i = 0; i < my_conf_child_count(children); i++) {
    ui_child_path(child_path, sizeof(child_path), node_path, i);
    my_widget_t* child = build_node(allocator, pal, my_conf_child(children, i),
                                    flags, child_path, err);
    if (child == NULL) {
      return NULL;
    }
    if (my_widget_add_child(parent, child) != MY_RET_OK) {
      my_widget_unref(child);
      ui_fail_field_path(err, "failed to attach child widget", "children",
                         node_path);
      return NULL;
    }
    my_widget_unref(child);
  }
  return parent;
}

static my_widget_t* build_node(const my_allocator_t* allocator, my_pal_t* pal,
                               const my_conf_node_t* node, uint32_t flags,
                               const char* node_path, my_ui_error_t* err) {
  const my_conf_node_t* type_node;
  const char* type;
  const my_widget_class_t* cls;
  my_ui_factory_fn_t factory;
  const ui_factory_entry_t* factory_entry;
  const my_prop_desc_t* properties;
  my_widget_t* widget;
  my_widget_class_lease_t class_lease = {0};
  bool class_lease_held = false;
  bool module_callback_held = false;
  (void)pal;
  if (my_conf_type(node) != MY_CONF_OBJECT ||
      (type_node = object_value(node, "type")) == NULL ||
      my_conf_type(type_node) != MY_CONF_STR) {
    ui_fail_field_path(err, "widget requires a string type", "type", node_path);
    return NULL;
  }
  type = my_conf_as_str(type_node, NULL);
  if (my_str_eq(type, "window")) {
    ui_fail_field_path(err, "window is only allowed as root", "type", node_path);
    return NULL;
  }
  factory_entry = find_factory_entry(type);
  factory = factory_entry == NULL ? NULL : factory_entry->factory;
  cls = NULL;
  if (factory == NULL &&
      my_widget_class_acquire(type, &cls, &class_lease) == MY_RET_OK) {
    class_lease_held = true;
  }
  properties = factory_entry != NULL ? factory_entry->properties
                                     : cls != NULL ? cls->props : NULL;
  if (factory != NULL) {
    if (factory_entry->module != NULL &&
        ui_module_callback_enter(factory_entry->module) != MY_RET_OK) {
      ui_fail_field_path(err, "widget module is quiescing", "type",
                         node_path);
      return NULL;
    }
    module_callback_held = factory_entry->module != NULL;
    ui_registry_callback_enter();
    widget = factory(allocator, node);
    ui_registry_callback_leave();
  } else if (cls != NULL) {
    widget = cls->create(allocator);
  } else {
    ui_fail_field_path(err, "unknown widget type", "type", node_path);
    return NULL;
  }
  if (widget == NULL) {
    if (module_callback_held) {
      ui_module_callback_leave(factory_entry->module);
    }
    if (class_lease_held) my_widget_class_release(&class_lease);
    return NULL;
  }
  if (module_callback_held &&
      my_widget_class_module_bind_widget(factory_entry->module, widget) !=
          MY_RET_OK) {
    ui_fail_field_path(err, "widget module is quiescing", "type", node_path);
    my_widget_unref(widget);
    ui_module_callback_leave(factory_entry->module);
    return NULL;
  }
  if (module_callback_held) {
    ui_module_callback_leave(factory_entry->module);
    module_callback_held = false;
  }
  if (class_lease_held &&
      my_widget_class_bind_instance(widget, &class_lease) != MY_RET_OK) {
    my_widget_class_release(&class_lease);
    my_widget_unref(widget);
    return NULL;
  }
  if (apply_schema_props(widget, properties, node, node_path, err,
                         factory_entry != NULL ? factory_entry->module : NULL) !=
      MY_RET_OK) {
    if (class_lease_held) my_widget_class_release(&class_lease);
    my_widget_unref(widget);
    return NULL;
  }
  if (class_lease_held) my_widget_class_release(&class_lease);
  if (apply_common(widget, node, node_path, err) != MY_RET_OK ||
      build_children(allocator, pal, widget, node, flags, node_path, err) ==
          NULL) {
    my_widget_unref(widget);
    return NULL;
  }
  return widget;
}

static my_ret_t apply_style(my_window_t* window, const my_conf_node_t* root,
                            my_ui_error_t* err) {
  const my_conf_node_t* style = object_value(root, "style");
  const char* text;
  my_ret_t ret;
  if (style == NULL) {
    return MY_RET_OK;
  }
  if (my_conf_type(style) != MY_CONF_STR || window == NULL ||
      window->theme == NULL) {
    ui_fail_field(err, "style must be a string", "style");
    return MY_RET_FAIL;
  }
  text = my_conf_as_str(style, NULL);
  if (strchr(text, '{') != NULL) {
    ret = my_window_set_css_style(window, text);
  } else {
    ret = my_theme_load_str(window->theme, text);
  }
  if (ret != MY_RET_OK) {
    ui_fail_field(err, "invalid window style", "style");
  }
  return ret;
}

static my_widget_t* ui_load_yaml_bytes(const my_allocator_t* allocator,
                                       my_pal_t* pal, const char* yaml,
                                       size_t yaml_len, bool reject_nul,
                                       uint32_t flags,
                                       my_ui_error_t* err) {
  my_conf_error_t yaml_error;
  my_conf_node_t* root;
  const my_conf_node_t* type_node;
  my_widget_t* result;
  ui_registry_read_lock();
  if (yaml == NULL) {
    ui_fail_field(err, "invalid YAML input", "document");
    ui_registry_read_unlock();
    return NULL;
  }
  if ((flags & ~(uint32_t)MY_UI_LOAD_STRICT_SCHEMA) != 0u) {
    ui_fail_field(err, "unknown YAML load flags", "flags");
    ui_registry_read_unlock();
    return NULL;
  }
  if (yaml_len > MY_UI_MAX_YAML_BYTES) {
    ui_fail_field(err, "YAML input exceeds resource budget", "document");
    ui_registry_read_unlock();
    return NULL;
  }
  if (reject_nul && memchr(yaml, '\0', yaml_len) != NULL) {
    ui_fail_field(err, "YAML input contains NUL byte", "document");
    ui_registry_read_unlock();
    return NULL;
  }
  root = my_conf_parse_yaml(allocator, yaml, yaml_len, &yaml_error);
  if (root == NULL) {
    if (err != NULL) {
      err->line = yaml_error.line;
      err->code = MY_UI_ERROR_YAML_SYNTAX;
      err->capability = 0u;
      snprintf(err->field, sizeof(err->field), "%s", "document");
      snprintf(err->message, sizeof(err->message), "yaml: %.70s (col %d)",
               yaml_error.msg, yaml_error.col);
    }
    ui_registry_read_unlock();
    return NULL;
  }
  if (ui_migrate_tree(allocator, root, true, "", 0u, err) != MY_RET_OK) {
    my_conf_destroy(root);
    ui_registry_read_unlock();
    return NULL;
  }
  if (!ui_validate_tree(root, true, flags, "", err)) {
    my_conf_destroy(root);
    ui_registry_read_unlock();
    return NULL;
  }
  type_node = object_value(root, "type");
  if (type_node != NULL && my_conf_type(type_node) == MY_CONF_STR &&
      my_str_eq(my_conf_as_str(type_node, NULL), "window")) {
    int32_t width, height;
    const my_conf_node_t* title = object_value(root, "title");
    my_window_t* window;
    if (pal == NULL || !value_int32(object_value(root, "w"), 640, &width) ||
        !value_int32(object_value(root, "h"), 480, &height) ||
        (title != NULL && my_conf_type(title) != MY_CONF_STR)) {
      ui_fail_field(err, "window requires pal, integer size, and string title",
                    "window");
      my_conf_destroy(root);
      ui_registry_read_unlock();
      return NULL;
    }
    window = my_window_create(allocator, pal, width, height,
                              title != NULL ? my_conf_as_str(title, NULL) : NULL);
    result = (my_widget_t*)window;
    if (window != NULL &&
               (apply_common(result, root, "", err) != MY_RET_OK ||
                build_children(allocator, pal, result, root, flags, "", err) == NULL)) {
      my_widget_unref(result);
      result = NULL;
    } else if (window != NULL &&
               apply_style(window, root, err) != MY_RET_OK) {
      my_widget_unref(result);
      result = NULL;
    }
  } else {
    result = build_node(allocator, pal, root, flags, "", err);
  }
  my_conf_destroy(root);
  ui_registry_read_unlock();
  return result;
}

my_widget_t* my_ui_load_str(const my_allocator_t* allocator, my_pal_t* pal,
                            const char* yaml_str, my_ui_error_t* err) {
  return my_ui_load_str_ex(allocator, pal, yaml_str, MY_UI_LOAD_DEFAULT, err);
}

my_widget_t* my_ui_load_str_ex(const my_allocator_t* allocator, my_pal_t* pal,
                               const char* yaml_str, uint32_t flags,
                               my_ui_error_t* err) {
  size_t yaml_len;
  if (err != NULL) {
    memset(err, 0, sizeof(*err));
  }
  if (yaml_str != NULL && !ui_bounded_cstr_len(yaml_str, &yaml_len)) {
    ui_fail_field(err, "YAML input exceeds resource budget", "document");
    return NULL;
  }
  return ui_load_yaml_bytes(allocator, pal, yaml_str,
                            yaml_str != NULL ? yaml_len : 0u, false, flags, err);
}

my_widget_t* my_ui_load_file(const my_allocator_t* allocator, my_pal_t* pal,
                             const char* path, my_ui_error_t* err) {
  return my_ui_load_file_ex(allocator, pal, path, MY_UI_LOAD_DEFAULT, err);
}

my_widget_t* my_ui_load_file_ex(const my_allocator_t* allocator, my_pal_t* pal,
                                const char* path, uint32_t flags,
                                my_ui_error_t* err) {
  FILE* file = NULL;
  long size;
  char* buffer;
  my_widget_t* result;
  if (err != NULL) {
    memset(err, 0, sizeof(*err));
  }
  if (path == NULL) {
    ui_fail_field(err, "invalid YAML file path", "path");
    return NULL;
  }
  file = fopen(path, "rb");
  if (file == NULL) {
    ui_fail_field(err, "cannot open YAML file", "path");
    return NULL;
  }
  if (fseek(file, 0, SEEK_END) != 0 || (size = ftell(file)) < 0 ||
      fseek(file, 0, SEEK_SET) != 0) {
    fclose(file);
    ui_fail_field(err, "cannot read YAML file", "path");
    return NULL;
  }
  if (size > (long)MY_UI_MAX_YAML_BYTES) {
    fclose(file);
    ui_fail_field(err, "YAML input exceeds resource budget", "document");
    return NULL;
  }
  buffer = (char*)my_mem_alloc(allocator, (size_t)size + 1u);
  if (buffer == NULL) {
    fclose(file);
    ui_fail_field(err, "out of memory reading YAML file", "document");
    return NULL;
  }
  if (fread(buffer, 1, (size_t)size, file) != (size_t)size) {
    fclose(file);
    my_mem_free(allocator, buffer);
    ui_fail_field(err, "cannot read YAML file", "document");
    return NULL;
  }
  fclose(file);
  buffer[size] = '\0';
  result = ui_load_yaml_bytes(allocator, pal, buffer, (size_t)size, true,
                              flags, err);
  my_mem_free(allocator, buffer);
  return result;
}

#else

my_ret_t my_ui_loader_freeze(void) { return MY_RET_NOT_SUPPORTED; }

bool my_ui_loader_is_frozen(void) { return false; }

my_ret_t my_ui_loader_query_type(const char* type, my_ui_type_info_t* info) {
  (void)type;
  if (info != NULL) {
    *info = (my_ui_type_info_t){0};
  }
  return info == NULL || type == NULL ? MY_RET_INVALID_PARAMS
                                      : MY_RET_NOT_SUPPORTED;
}

my_ret_t my_ui_loader_register(const char* type, my_ui_factory_fn_t factory) {
  (void)type;
  (void)factory;
  return MY_RET_NOT_SUPPORTED;
}

my_ret_t my_ui_loader_runtime_register_schema_ex_module(
    my_widget_class_module_t* module, const char* type,
    my_ui_factory_fn_t factory, const my_prop_desc_t* properties,
    const char* const* events, uint32_t schema_version,
    my_ui_schema_migrate_fn_t migrate) {
  (void)module;
  (void)type;
  (void)factory;
  (void)properties;
  (void)events;
  (void)schema_version;
  (void)migrate;
  return MY_RET_NOT_SUPPORTED;
}

my_ret_t my_ui_loader_runtime_register_schema_chain_module(
    my_widget_class_module_t* module, const char* type,
    my_ui_factory_fn_t factory, const my_prop_desc_t* properties,
    const char* const* events, uint32_t schema_version,
    const my_ui_schema_migration_t* migrations, size_t migration_count) {
  (void)module;
  (void)type;
  (void)factory;
  (void)properties;
  (void)events;
  (void)schema_version;
  (void)migrations;
  (void)migration_count;
  return MY_RET_NOT_SUPPORTED;
}

my_ret_t my_ui_loader_runtime_register_schema_module(
    my_widget_class_module_t* module, const char* type,
    my_ui_factory_fn_t factory, const my_prop_desc_t* properties,
    const char* const* events) {
  (void)module;
  (void)type;
  (void)factory;
  (void)properties;
  (void)events;
  return MY_RET_NOT_SUPPORTED;
}

my_ret_t my_ui_loader_runtime_register_schema(
    const char* type, my_ui_factory_fn_t factory,
    const my_prop_desc_t* properties, const char* const* events) {
  (void)type;
  (void)factory;
  (void)properties;
  (void)events;
  return MY_RET_NOT_SUPPORTED;
}

my_ret_t my_ui_loader_runtime_register_dynamic_schema(
    const my_allocator_t* allocator, const char* type,
    my_ui_factory_fn_t factory, const my_ui_dynamic_schema_t* schema,
    uint32_t schema_version, my_ui_schema_migrate_fn_t migrate) {
  (void)allocator;
  (void)type;
  (void)factory;
  (void)schema;
  (void)schema_version;
  (void)migrate;
  return MY_RET_NOT_SUPPORTED;
}

my_ret_t my_ui_loader_runtime_register_dynamic_schema_module(
    const my_allocator_t* allocator, my_widget_class_module_t* module,
    const char* type, my_ui_factory_fn_t factory,
    const my_ui_dynamic_schema_t* schema, uint32_t schema_version,
    my_ui_schema_migrate_fn_t migrate) {
  (void)allocator;
  (void)module;
  (void)type;
  (void)factory;
  (void)schema;
  (void)schema_version;
  (void)migrate;
  return MY_RET_NOT_SUPPORTED;
}

my_ret_t my_ui_loader_runtime_unregister(const char* type) {
  (void)type;
  return MY_RET_NOT_SUPPORTED;
}

my_ret_t my_ui_loader_register_dynamic_schema(
    const my_allocator_t* allocator, const char* type,
    my_ui_factory_fn_t factory,
    const my_ui_dynamic_schema_t* schema, uint32_t schema_version,
    my_ui_schema_migrate_fn_t migrate) {
  (void)type;
  (void)allocator;
  (void)factory;
  (void)schema;
  (void)schema_version;
  (void)migrate;
  return MY_RET_NOT_SUPPORTED;
}

my_ret_t my_ui_loader_register_schema(const char* type,
                                      my_ui_factory_fn_t factory,
                                      const my_prop_desc_t* properties,
                                      const char* const* events) {
  (void)type;
  (void)factory;
  (void)properties;
  (void)events;
  return MY_RET_NOT_SUPPORTED;
}

my_ret_t my_ui_loader_register_schema_ex(
    const char* type, my_ui_factory_fn_t factory,
    const my_prop_desc_t* properties, const char* const* events,
    uint32_t schema_version, my_ui_schema_migrate_fn_t migrate) {
  (void)type;
  (void)factory;
  (void)properties;
  (void)events;
  (void)schema_version;
  (void)migrate;
  return MY_RET_NOT_SUPPORTED;
}

my_ret_t my_ui_loader_register_schema_chain(
    const char* type, my_ui_factory_fn_t factory,
    const my_prop_desc_t* properties, const char* const* events,
    uint32_t schema_version, const my_ui_schema_migration_t* migrations,
    size_t migration_count) {
  (void)type;
  (void)factory;
  (void)properties;
  (void)events;
  (void)schema_version;
  (void)migrations;
  (void)migration_count;
  return MY_RET_NOT_SUPPORTED;
}

my_widget_t* my_ui_load_str_ex(const my_allocator_t* allocator, my_pal_t* pal,
                               const char* yaml_str, uint32_t flags,
                               my_ui_error_t* err) {
  (void)allocator;
  (void)pal;
  (void)yaml_str;
  (void)flags;
  (void)err;
  return NULL;
}

my_widget_t* my_ui_load_str(const my_allocator_t* allocator, my_pal_t* pal,
                            const char* yaml_str, my_ui_error_t* err) {
  (void)allocator;
  (void)pal;
  (void)yaml_str;
  (void)err;
  return NULL;
}

my_widget_t* my_ui_load_file_ex(const my_allocator_t* allocator, my_pal_t* pal,
                                const char* path, uint32_t flags,
                                my_ui_error_t* err) {
  (void)allocator;
  (void)pal;
  (void)path;
  (void)flags;
  (void)err;
  return NULL;
}

my_widget_t* my_ui_load_file(const my_allocator_t* allocator, my_pal_t* pal,
                             const char* path, my_ui_error_t* err) {
  (void)allocator;
  (void)pal;
  (void)path;
  (void)err;
  return NULL;
}

#endif
