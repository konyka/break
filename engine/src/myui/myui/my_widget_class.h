/**
 * @file my_widget_class.h
 * @brief Widget class registry: declarative tag -> create + property
 * descriptors (M24a).
 *
 * One table drives all three former hand-written mappings: the YAML UI
 * loader (my_ui_loader.c), the ui2c code generator (tools/ui2c.c) and the
 * MVVM property router (mymvvm_myui/my_widget_target.c). Built-in classes
 * are registered lazily on the first my_widget_class_find() under the
 * registry's initialization lock; applications
 * may register custom classes (an existing type name is overridden). Class
 * descriptors are copied into immutable registry snapshots, so input tables
 * only need to remain valid for the registration call. Startup registration
 * is followed by freeze for the lock-free read path; after freeze, the
 * explicit runtime register/unregister APIs publish immutable table snapshots
 * for cold-path hot replacement.
 *
 * Property lookup order of my_widget_set_prop()/my_widget_get_prop():
 * base-class common properties first ("visible", "enable", "x", "y",
 * "w", "h" — handled for every widget without consulting the table),
 * then the property descriptors of the widget's class (matched by
 * widget->widget_type). Unknown names return MY_RET_NOT_SUPPORTED.
 */
#ifndef MY_WIDGET_CLASS_H
#define MY_WIDGET_CLASS_H

#include "core/platform_thread.h"
#include "myc/my_value.h"
#include "myui/my_widget.h"

/** @brief Type of a widget property (drives string conversions). */
typedef enum my_prop_type_t {
  MY_PROP_STRING,
  MY_PROP_INT,
  MY_PROP_FLOAT,
  MY_PROP_BOOL,
  MY_PROP_COLOR
} my_prop_type_t;

/** @brief One property of a widget class (NULL set/get = read/write-only). */
typedef struct my_prop_desc_t {
  const char* name;   /**< "text" "value" ... */
  my_prop_type_t type;
  my_ret_t (*set)(my_widget_t*, const my_value_t*);  /**< NULL = read-only */
  my_ret_t (*get)(const my_widget_t*, my_value_t*);  /**< NULL = write-only */
} my_prop_desc_t;

/** @brief A widget class: YAML type + factory + property table. */
typedef struct my_widget_class_t {
  const char* type;                      /**< "button" ... */
  my_widget_t* (*create)(const my_allocator_t*);
  const my_prop_desc_t* props;           /**< name==NULL terminated */
  const char* const* events;             /**< {"click", NULL}, documentary */
  /** @brief Optional identity check before property callbacks. */
  bool (*is_instance)(const my_widget_t*);
} my_widget_class_t;

/** @brief Ownership state for callbacks supplied by one loadable module. */
typedef struct my_widget_class_module_t my_widget_class_module_t;

/** @brief Thread-affine lease for invoking a class callback safely. */
typedef struct my_widget_class_lease_t {
  const my_widget_class_t* class_descriptor;
  void* snapshot_token;
  PlatformThreadId owner_thread;
  const void* owner_cookie;
} my_widget_class_lease_t;

#define MY_WIDGET_SCHEMA_MAX_NAME_BYTES 64u
#define MY_WIDGET_SCHEMA_MAX_PROPERTIES 64u
#define MY_WIDGET_SCHEMA_MAX_EVENTS 32u

bool my_widget_schema_name_valid(const char* name);
bool my_widget_schema_property_type_valid(my_prop_type_t type);
bool my_widget_schema_properties_valid(const my_prop_desc_t* properties,
                                       size_t* count);
bool my_widget_schema_events_valid(const char* const* events, size_t* count);
bool my_widget_schema_properties_n_valid(const my_prop_desc_t* properties,
                                         size_t count);
bool my_widget_schema_events_n_valid(const char* const* events, size_t count);

/**
 * @brief Register a custom widget class (an existing type name is
 * overridden). The descriptor and bounded name tables are copied before the
 * active snapshot changes; callers may release or mutate them after return.
 * Type and
 * descriptor names must be non-empty, NUL-terminated within 64 bytes;
 * descriptors cannot duplicate names or use loader-reserved fields, and
 * registration is rejected atomically when any table entry is invalid.
 */
my_ret_t my_widget_class_register(const my_widget_class_t* cls);

/**
 * @brief Atomically replace or add a class in a frozen registry.
 *
 * The active immutable table is published with release semantics. Existing
 * lookup results remain valid for the process lifetime, so readers never
 * observe a partially copied descriptor table. This is a cold-path operation
 * and is rejected before the registry is frozen or from registry callbacks.
 */
my_ret_t my_widget_class_runtime_register(const my_widget_class_t* cls);

/**
 * @brief Create a callback ownership token for a loadable module.
 *
 * Registry accounting is internally synchronized. The creator owns one
 * reference; other owners must call retain() before using the token and
 * release() when finished. The address remains valid after destroy until
 * process shutdown, and calls made after destroy fail closed.
 */
my_widget_class_module_t* my_widget_class_module_create(
    const my_allocator_t* allocator);

/**
 * @brief Retain a module token for use by another owner or thread.
 *
 * The token remains address-stable after destroy and is reclaimed at process
 * shutdown. Retain must happen before the owner starts destruction.
 */
my_ret_t my_widget_class_module_retain(my_widget_class_module_t* module);

/** @brief Release a reference acquired with retain(). */
void my_widget_class_module_release(my_widget_class_module_t* module);

/**
 * @brief Publish a class owned by a module.
 *
 * The module must remain alive until its classes are unregistered, all bound
 * instances are destroyed, and my_widget_class_module_try_unload() succeeds.
 */
my_ret_t my_widget_class_runtime_register_module(
    my_widget_class_module_t* module, const my_widget_class_t* cls);

/**
 * @brief Stop new callback leases for a module without blocking.
 *
 * Existing callbacks and instances are allowed to drain; this call is
 * rejected from registry callbacks so callback code cannot deadlock itself.
 */
my_ret_t my_widget_class_module_begin_unload(
    my_widget_class_module_t* module);

/**
 * @brief Check whether a module has no classes, callbacks, or instances left.
 */
my_ret_t my_widget_class_module_try_unload(my_widget_class_module_t* module);

/**
 * @brief Logically destroy a module token after try_unload() succeeds.
 *
 * This consumes the creator's reference and is rejected while retained
 * references exist. The token storage is reclaimed during process shutdown.
 */
my_ret_t my_widget_class_module_destroy(my_widget_class_module_t* module);

/** @brief Retain one registered callback entry owned by a module. */
my_ret_t my_widget_class_module_register_entry(
    my_widget_class_module_t* module);

/** @brief Release one registered callback entry owned by a module. */
void my_widget_class_module_unregister_entry(
    my_widget_class_module_t* module);

/** @brief Retain one in-flight module callback, rejecting quiescing modules. */
my_ret_t my_widget_class_module_callback_acquire(
    my_widget_class_module_t* module);

/** @brief Release one in-flight module callback. */
void my_widget_class_module_callback_release(
    my_widget_class_module_t* module);

/** @brief Bind a widget instance to a module without a class snapshot lease. */
my_ret_t my_widget_class_module_bind_widget(
    my_widget_class_module_t* module, my_widget_t* widget);

/**
 * @brief Remove a non-built-in class from a frozen registry.
 *
 * Existing lookup results remain valid, while new lookups stop finding the
 * removed type. The operation does not unload callback code or widget
 * instances; callers must quiesce those separately before unloading a module.
 */
my_ret_t my_widget_class_runtime_unregister(const char* type);

/**
 * @brief Acquire the active class snapshot for callback invocation.
 *
 * The lease is thread-affine and must surround every direct invocation of
 * create, is_instance, or property callbacks obtained from the descriptor.
 * It also activates the registry callback guard for the lease duration, so
 * registry mutation from callback code fails instead of waiting recursively.
 * Runtime replacement/unregister waits for acquired leases before returning.
 * Only the original lease storage in the acquiring thread may release it;
 * foreign-thread and copied-lease releases are rejected and leave the lease
 * active.
 */
my_ret_t my_widget_class_acquire(const char* type,
                                 const my_widget_class_t** out,
                                 my_widget_class_lease_t* lease);

/**
 * @brief Create a class widget through a leased callback and bind its module.
 *
 * This is the preferred entry point for callers that do not need to inspect
 * the descriptor. It releases the callback lease after creation while the
 * returned widget keeps the module instance count until destruction.
 */
my_widget_t* my_widget_class_create(const char* type,
                                    const my_allocator_t* allocator);

/** @brief Release a lease acquired by my_widget_class_acquire(). */
void my_widget_class_release(my_widget_class_lease_t* lease);

/** @brief Bind a created widget to the callback module held by a lease. */
my_ret_t my_widget_class_bind_instance(
    my_widget_t* widget, const my_widget_class_lease_t* lease);

/**
 * @brief Freeze class registration after application startup.
 *
 * The operation is idempotent. Built-ins are registered before the registry
 * becomes immutable; the startup registration API then returns
 * MY_RET_NOT_SUPPORTED. Before freeze, registration and first lookup are
 * serialized; after freeze, lookup is a lock-free read-only fast path and the
 * runtime APIs are the only way to publish a replacement snapshot.
 */
my_ret_t my_widget_class_freeze(void);

/** @brief Return whether class registration has been frozen. */
bool my_widget_class_is_frozen(void);

/**
 * @brief Find a class by type name (built-ins are registered lazily).
 * NULL when unknown. Use my_widget_class_acquire() before invoking any
 * callback from a dynamically replaceable class descriptor.
 */
const my_widget_class_t* my_widget_class_find(const char* type);

/** @brief Set a property by name (see the lookup order above). */
my_ret_t my_widget_set_prop(my_widget_t* w, const char* name,
                            const my_value_t* v);
/** @brief Get a property by name (see the lookup order above). */
my_ret_t my_widget_get_prop(my_widget_t* w, const char* name, my_value_t* v);

/* typed convenience wrappers (ui2c-generated code and applications) */
my_ret_t my_widget_set_prop_str(my_widget_t* w, const char* name,
                                const char* v);
my_ret_t my_widget_set_prop_int(my_widget_t* w, const char* name, int32_t v);
my_ret_t my_widget_set_prop_float(my_widget_t* w, const char* name, float v);
my_ret_t my_widget_set_prop_bool(my_widget_t* w, const char* name, bool v);

#endif /* MY_WIDGET_CLASS_H */
