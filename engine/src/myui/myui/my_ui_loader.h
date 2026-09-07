/**
 * @file my_ui_loader.h
 * @brief YAML UI loader: builds widget trees from YAML documents.
 *
 * YAML type names map to widget factories (registry; window/button/label/
 * edit/checkbox/slider/progress_bar built in). Common attributes handled
 * by the loader: name, x/y/w/h, visible/enable, lp (layout params),
 * version (schema version),
 * layout ("linear:h:8" / "linear:v:8" / "default"). Bindings in the
 * `bindings` map are joined into the widget's bind_rules (';' separated) for
 * my_mvvm_bind(). A root `style` string without braces is fed to
 * my_theme_load_str; a CSS style string is loaded with the strict CSS policy
 * onto the window's theme. Widget-specific properties (text/hint/value/
 * min/max/step/checked/password/...) are parsed by each factory. YAML uses
 * a `type` key and a `children` sequence; common and widget properties are
 * direct keys. Bindings live in a `bindings` map and style is a scalar key.
 *
 * The root type can be `window` (needs pal); anything else builds
 * a plain widget tree.
 *
 * Compile-time switch: MYUI_UI_YAML (default ON; OFF for size-trimmed
 * builds — load functions return NULL).
 */
#ifndef MY_UI_LOADER_H
#define MY_UI_LOADER_H

#include "myc/myconf/my_conf.h"
#include "myui/my_window.h"
#include "myui/my_widget_class.h"

#define MY_UI_MAX_YAML_BYTES (4u * 1024u * 1024u)
#define MY_UI_MAX_FACTORIES 32u
#define MY_UI_MAX_BIND_RULE_BYTES 512u
#define MY_UI_MAX_TYPE_PROPERTIES MY_WIDGET_SCHEMA_MAX_PROPERTIES
#define MY_UI_MAX_TYPE_EVENTS MY_WIDGET_SCHEMA_MAX_EVENTS
#define MY_UI_MAX_SCHEMA_MIGRATIONS 16u
#define MY_UI_MAX_SCHEMA_NAME_BYTES MY_WIDGET_SCHEMA_MAX_NAME_BYTES
#define MY_UI_ERROR_PATH_LEN 128u

/** @brief Optional load policy flags. */
typedef enum my_ui_load_flags_t {
  MY_UI_LOAD_DEFAULT = 0u,
  MY_UI_LOAD_STRICT_SCHEMA = 1u << 0
} my_ui_load_flags_t;

/** @brief Features exposed by the YAML UI loader. */
typedef enum my_ui_feature_t {
  MY_UI_FEATURE_YAML_SCHEMA = 1u << 0,
  MY_UI_FEATURE_CHILDREN = 1u << 1,
  MY_UI_FEATURE_BINDINGS = 1u << 2,
  MY_UI_FEATURE_CSS_STYLE = 1u << 3,
  MY_UI_FEATURE_TYPE_QUERY = 1u << 4,
  MY_UI_FEATURE_SCHEMA_MIGRATION = 1u << 5,
  MY_UI_FEATURE_DYNAMIC_SCHEMA = 1u << 6
} my_ui_feature_t;

/** @brief Stable machine-readable loader failure category. */
typedef enum my_ui_error_code_t {
  MY_UI_ERROR_NONE = 0,
  MY_UI_ERROR_INVALID_PARAMS,
  MY_UI_ERROR_INPUT_LIMIT,
  MY_UI_ERROR_UNKNOWN_POLICY,
  MY_UI_ERROR_YAML_SYNTAX,
  MY_UI_ERROR_SCHEMA,
  MY_UI_ERROR_UNKNOWN_WIDGET,
  MY_UI_ERROR_RESOURCE,
  MY_UI_ERROR_STYLE
} my_ui_error_code_t;

/** @brief Immutable YAML loader capability registry. */
typedef struct my_ui_loader_capabilities_t {
  uint32_t supported_features;
  size_t max_yaml_bytes;
  size_t max_factories;
  size_t max_bind_rule_bytes;
  uint32_t supported_load_flags;
} my_ui_loader_capabilities_t;

/** @brief Return the process-wide immutable YAML loader capabilities. */
const my_ui_loader_capabilities_t* my_ui_loader_capabilities(void);

/** @brief Read-only schema and factory information for one YAML type. */
typedef struct my_ui_type_info_t {
  const char* type;
  bool schema_known;
  bool factory_registered;
  const my_prop_desc_t* common_properties;
  size_t common_property_count;
  const my_prop_desc_t* properties;
  size_t property_count;
  const char* const* events;
  size_t event_count;
  uint32_t schema_version;
  bool migration_supported;
  /* Query results own bounded descriptor storage. */
  char type_storage[24];
  my_prop_desc_t property_storage[MY_UI_MAX_TYPE_PROPERTIES];
  char property_name_storage[MY_UI_MAX_TYPE_PROPERTIES]
                            [MY_UI_MAX_SCHEMA_NAME_BYTES];
  const char* event_storage[MY_UI_MAX_TYPE_EVENTS];
  char event_name_storage[MY_UI_MAX_TYPE_EVENTS]
                         [MY_UI_MAX_SCHEMA_NAME_BYTES];
} my_ui_type_info_t;

/**
 * @brief Query a type without allocation or dangling borrowed results.
 *
 * Descriptor names and the type name are copied into info's bounded storage;
 * the returned pointers remain valid until info is overwritten or destroyed.
 */
my_ret_t my_ui_loader_query_type(const char* type, my_ui_type_info_t* info);

/** @brief Widget factory for one YAML widget object. */
typedef my_widget_t* (*my_ui_factory_fn_t)(const my_allocator_t* allocator,
                                           const my_conf_node_t* node);

/**
 * @brief Register (or replace) a YAML type factory. Max 32 types.
 *
 * Registration is serialized against active loads and queries. Registration
 * remains a startup operation after freeze; it must not be called recursively
 * from a factory or migration callback.
 */
my_ret_t my_ui_loader_register(const char* type, my_ui_factory_fn_t factory);

/**
 * @brief Register or replace a factory after loader freeze.
 *
 * Descriptor names are copied into loader-owned storage before publication;
 * the factory callback remains borrowed and must stay loaded until callers
 * quiesce instances and readers that may invoke it. Runtime registration is
 * a cold-path operation and cannot shadow a built-in widget class.
 */
my_ret_t my_ui_loader_runtime_register_schema(
    const char* type, my_ui_factory_fn_t factory,
    const my_prop_desc_t* properties, const char* const* events);

/**
 * @brief Register a runtime factory owned by a module lifecycle token.
 *
 * The module must remain alive until the factory is unregistered, all
 * instances are destroyed, and my_widget_class_module_try_unload() succeeds.
 */
my_ret_t my_ui_loader_runtime_register_schema_module(
    my_widget_class_module_t* module, const char* type,
    my_ui_factory_fn_t factory, const my_prop_desc_t* properties,
    const char* const* events);

/** @brief Remove a non-built-in runtime factory after loader freeze. */
my_ret_t my_ui_loader_runtime_unregister(const char* type);

/**
 * @brief Freeze factory registration after application startup.
 *
 * The operation is idempotent. Runtime queries and loading remain available;
 * later registration attempts return
 * MY_RET_NOT_SUPPORTED.
 */
my_ret_t my_ui_loader_freeze(void);

/** @brief Return whether YAML factory registration has been frozen. */
bool my_ui_loader_is_frozen(void);

/**
 * @brief Register a YAML type factory with static property/event schema.
 * The schema tables must outlive the loader registry. NULL tables are valid.
 */
my_ret_t my_ui_loader_register_schema(const char* type,
                                      my_ui_factory_fn_t factory,
                                      const my_prop_desc_t* properties,
                                      const char* const* events);

/**
 * @brief Migrate one private YAML node from an older schema version.
 *
 * The callback must preserve the node type and is invoked before validation or
 * factory creation. Its allocator and node are valid only for the call.
 */
typedef my_ret_t (*my_ui_schema_migrate_fn_t)(
    const my_allocator_t* allocator, my_conf_node_t* node,
    uint32_t from_version, uint32_t to_version);

/** @brief Explicit-count schema input copied by dynamic registration. */
typedef struct my_ui_dynamic_schema_t {
  const my_prop_desc_t* properties;
  size_t property_count;
  const char* const* events;
  size_t event_count;
} my_ui_dynamic_schema_t;

/**
 * @brief Register a schema whose descriptor arrays are copied and owned.
 *
 * The input arrays and names need only remain valid for this call. Counts are
 * explicit and bounded; copy failure leaves an existing entry unchanged. The
 * allocator and its context must remain valid until this type is replaced or
 * the process exits. Static schema registration remains borrowed. Registration
 * is only valid before loader freeze. A replacement waits for active loads and
 * queries before releasing the previous owned schema.
 */
my_ret_t my_ui_loader_register_dynamic_schema(
    const my_allocator_t* allocator, const char* type,
    my_ui_factory_fn_t factory,
    const my_ui_dynamic_schema_t* schema, uint32_t schema_version,
    my_ui_schema_migrate_fn_t migrate);

/**
 * @brief Register an owned schema after loader freeze.
 *
 * This is the runtime counterpart of my_ui_loader_register_dynamic_schema();
 * descriptor storage is copied transactionally and callback code remains
 * borrowed until the caller has quiesced all users.
 */
my_ret_t my_ui_loader_runtime_register_dynamic_schema(
    const my_allocator_t* allocator, const char* type,
    my_ui_factory_fn_t factory, const my_ui_dynamic_schema_t* schema,
    uint32_t schema_version, my_ui_schema_migrate_fn_t migrate);

/** @brief Runtime dynamic-schema registration with module ownership. */
my_ret_t my_ui_loader_runtime_register_dynamic_schema_module(
    const my_allocator_t* allocator, my_widget_class_module_t* module,
    const char* type, my_ui_factory_fn_t factory,
    const my_ui_dynamic_schema_t* schema, uint32_t schema_version,
    my_ui_schema_migrate_fn_t migrate);

/** @brief One adjacent step in a borrowed schema migration chain. */
typedef struct my_ui_schema_migration_t {
  uint32_t from_version;
  uint32_t to_version;
  my_ui_schema_migrate_fn_t migrate;
} my_ui_schema_migration_t;

/** @brief Runtime versioned schema registration with module ownership. */
my_ret_t my_ui_loader_runtime_register_schema_ex_module(
    my_widget_class_module_t* module, const char* type,
    my_ui_factory_fn_t factory, const my_prop_desc_t* properties,
    const char* const* events, uint32_t schema_version,
    my_ui_schema_migrate_fn_t migrate);

/** @brief Runtime migration-chain registration with module ownership. */
my_ret_t my_ui_loader_runtime_register_schema_chain_module(
    my_widget_class_module_t* module, const char* type,
    my_ui_factory_fn_t factory, const my_prop_desc_t* properties,
    const char* const* events, uint32_t schema_version,
    const my_ui_schema_migration_t* migrations, size_t migration_count);

/**
 * @brief Register a factory with a versioned schema and optional migration.
 * The schema and callback remain borrowed and must outlive the registry.
 * Explicit YAML versions older than schema_version require migrate; absent
 * version keys retain the current-version compatibility behavior. Use the
 * chain API for bounded adjacent migration steps.
 */
my_ret_t my_ui_loader_register_schema_ex(
    const char* type, my_ui_factory_fn_t factory,
    const my_prop_desc_t* properties, const char* const* events,
    uint32_t schema_version, my_ui_schema_migrate_fn_t migrate);

/**
 * @brief Register a factory with a bounded adjacent-step migration chain.
 *
 * The table remains borrowed and must outlive the loader registry. Steps must
 * be ordered, contiguous, and advance exactly one version; a partial chain is
 * valid and rejects source versions not covered by the table.
 */
my_ret_t my_ui_loader_register_schema_chain(
    const char* type, my_ui_factory_fn_t factory,
    const my_prop_desc_t* properties, const char* const* events,
    uint32_t schema_version, const my_ui_schema_migration_t* migrations,
    size_t migration_count);

/** @brief Loader error (source line for YAML syntax failures). */
typedef struct my_ui_error_t {
  int line;
  char message[96];
  my_ui_error_code_t code;
  uint32_t capability; /**< Relevant my_ui_feature_t bit. */
  char field[32]; /**< First YAML key responsible for the failure, if known. */
  char path[MY_UI_ERROR_PATH_LEN]; /**< Bounded path to the failing YAML key. */
} my_ui_error_t;

/**
 * @brief Load a widget tree from a YAML string. A `window` root requires
 * pal (non-NULL) and returns a my_window_t*. NULL on error (see err).
 */
my_widget_t* my_ui_load_str(const my_allocator_t* allocator, my_pal_t* pal,
                            const char* yaml_str, my_ui_error_t* err);

/** @brief Load a YAML widget tree with explicit validation policy. */
my_widget_t* my_ui_load_str_ex(const my_allocator_t* allocator, my_pal_t* pal,
                               const char* yaml_str, uint32_t flags,
                               my_ui_error_t* err);

/** @brief Load from a file path (NULL on error). */
my_widget_t* my_ui_load_file(const my_allocator_t* allocator, my_pal_t* pal,
                             const char* path, my_ui_error_t* err);

/** @brief Load a YAML file with explicit validation policy. */
my_widget_t* my_ui_load_file_ex(const my_allocator_t* allocator, my_pal_t* pal,
                               const char* path, uint32_t flags,
                               my_ui_error_t* err);

#endif /* MY_UI_LOADER_H */
