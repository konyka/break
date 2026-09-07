/**
 * @file my_widget_class.c
 * @brief Widget class registry: lookup + generic property access (M24a).
 *
 * Loader-independent on purpose: this file must stay usable in
 * MYUI_UI_YAML=OFF builds (generated code relies on it).
 */
#include "myui/my_widget_class.h"

#include <stdatomic.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>

#include "core/platform_thread.h"
#include "myc/my_str.h"
#include "myui/my_widget_registry_internal.h"

#define MY_WIDGET_CLASS_MAX 64

static const my_widget_class_t* g_classes[MY_WIDGET_CLASS_MAX];
static size_t g_class_count = 0;
static bool g_builtins_done = false;
static atomic_bool g_classes_frozen;
static PlatformMutex g_class_mutex;
static PlatformCond g_class_cond;
static atomic_int g_class_sync_state;
static _Thread_local unsigned g_registry_callback_depth;
static _Thread_local unsigned g_class_lease_depth;

struct my_widget_class_module_t {
  const my_allocator_t* allocator;
  size_t references;
  size_t registered_classes;
  size_t callback_leases;
  size_t instances;
  bool unloading;
  bool destroyed;
  struct my_widget_class_module_t* next;
};

static my_widget_class_module_t* g_modules;

static bool module_is_known_locked(const my_widget_class_module_t* module) {
  const my_widget_class_module_t* current;
  for (current = g_modules; current != NULL; current = current->next) {
    if (current == module) return true;
  }
  return false;
}

typedef struct my_widget_class_instance_binding_t {
  my_widget_t* widget;
  my_widget_class_module_t* module;
  const my_allocator_t* allocator;
  struct my_widget_class_instance_binding_t* next;
} my_widget_class_instance_binding_t;

static my_widget_class_instance_binding_t* g_instance_bindings;

bool my_widget_registry_callback_active(void) {
  return g_registry_callback_depth != 0u;
}

void my_widget_registry_callback_enter(void) {
  if (g_registry_callback_depth != UINT_MAX) {
    g_registry_callback_depth++;
  }
}

void my_widget_registry_callback_leave(void) {
  if (g_registry_callback_depth != 0u) {
    g_registry_callback_depth--;
  }
}

typedef struct my_widget_class_snapshot_t {
  my_widget_class_t cls;
  bool builtin;
  char* type;
  my_prop_desc_t* properties;
  char** property_names;
  const char** events;
  char** event_names;
  size_t callback_leases;
  my_widget_class_module_t* module;
  bool retired;
  struct my_widget_class_snapshot_t* next;
} my_widget_class_snapshot_t;

static my_widget_class_snapshot_t* g_class_snapshots;

typedef struct my_widget_class_table_t {
  size_t count;
  const my_widget_class_t* classes[MY_WIDGET_CLASS_MAX];
  struct my_widget_class_table_t* next;
} my_widget_class_table_t;

static _Atomic(my_widget_class_table_t*) g_active_table;
static my_widget_class_table_t* g_class_tables;

static void class_snapshot_destroy(my_widget_class_snapshot_t* snapshot) {
  size_t i;
  if (snapshot == NULL) return;
  if (snapshot->property_names != NULL) {
    for (i = 0; snapshot->property_names[i] != NULL; i++) {
      my_mem_free(NULL, snapshot->property_names[i]);
    }
  }
  if (snapshot->event_names != NULL) {
    for (i = 0; snapshot->event_names[i] != NULL; i++) {
      my_mem_free(NULL, snapshot->event_names[i]);
    }
  }
  my_mem_free(NULL, snapshot->property_names);
  my_mem_free(NULL, snapshot->event_names);
  my_mem_free(NULL, snapshot->properties);
  my_mem_free(NULL, snapshot->events);
  my_mem_free(NULL, snapshot->type);
  my_mem_free(NULL, snapshot);
}

static void class_snapshot_cleanup(void) {
  my_widget_class_snapshot_t* snapshot = g_class_snapshots;
  while (snapshot != NULL) {
    my_widget_class_snapshot_t* next = snapshot->next;
    class_snapshot_destroy(snapshot);
    snapshot = next;
  }
  g_class_snapshots = NULL;
  while (g_class_tables != NULL) {
    my_widget_class_table_t* next = g_class_tables->next;
    my_mem_free(NULL, g_class_tables);
    g_class_tables = next;
  }
  while (g_modules != NULL) {
    my_widget_class_module_t* next = g_modules->next;
    my_mem_free(g_modules->allocator, g_modules);
    g_modules = next;
  }
}

static void class_snapshot_rollback(
    my_widget_class_snapshot_t* checkpoint, size_t class_count,
    const my_widget_class_t* const* classes) {
  my_widget_class_snapshot_t* snapshot;
  while (g_class_snapshots != checkpoint) {
    snapshot = g_class_snapshots;
    g_class_snapshots = snapshot->next;
    class_snapshot_destroy(snapshot);
  }
  memcpy(g_classes, classes, sizeof(g_classes));
  g_class_count = class_count;
}

static my_widget_class_snapshot_t* class_snapshot_copy(
    const my_widget_class_t* cls, bool builtin,
    my_widget_class_module_t* module) {
  my_widget_class_snapshot_t* snapshot;
  size_t property_count = 0u;
  size_t event_count = 0u;
  size_t i;

  if (cls == NULL || !my_widget_schema_properties_valid(cls->props,
                                                         &property_count) ||
      !my_widget_schema_events_valid(cls->events, &event_count)) {
    return NULL;
  }
  snapshot = (my_widget_class_snapshot_t*)my_mem_calloc(
      NULL, 1u, sizeof(*snapshot));
  if (snapshot == NULL) return NULL;
  snapshot->type = my_strdup(NULL, cls->type);
  if (snapshot->type == NULL) goto fail;
  if (property_count != 0u) {
    snapshot->properties = (my_prop_desc_t*)my_mem_calloc(
        NULL, property_count + 1u, sizeof(*snapshot->properties));
    snapshot->property_names = (char**)my_mem_calloc(
        NULL, property_count + 1u, sizeof(*snapshot->property_names));
    if (snapshot->properties == NULL || snapshot->property_names == NULL) {
      goto fail;
    }
    for (i = 0u; i < property_count; i++) {
      snapshot->property_names[i] = my_strdup(NULL, cls->props[i].name);
      if (snapshot->property_names[i] == NULL) goto fail;
      snapshot->properties[i] = cls->props[i];
      snapshot->properties[i].name = snapshot->property_names[i];
    }
  }
  if (event_count != 0u) {
    snapshot->events = (const char**)my_mem_calloc(
        NULL, event_count + 1u, sizeof(*snapshot->events));
    snapshot->event_names = (char**)my_mem_calloc(
        NULL, event_count + 1u, sizeof(*snapshot->event_names));
    if (snapshot->events == NULL || snapshot->event_names == NULL) goto fail;
    for (i = 0u; i < event_count; i++) {
      snapshot->event_names[i] = my_strdup(NULL, cls->events[i]);
      if (snapshot->event_names[i] == NULL) goto fail;
      snapshot->events[i] = snapshot->event_names[i];
    }
  }
  snapshot->cls = *cls;
  snapshot->builtin = builtin;
  snapshot->module = module;
  snapshot->cls.type = snapshot->type;
  snapshot->cls.props = snapshot->properties;
  snapshot->cls.events = snapshot->events;
  snapshot->next = g_class_snapshots;
  g_class_snapshots = snapshot;
  return snapshot;

fail:
  class_snapshot_destroy(snapshot);
  return NULL;
}

/* defined in my_widget_class_builtin.c */
my_ret_t my_widget_class_register_builtins(void);
my_ret_t my_widget_class_register_builtin_entry(const my_widget_class_t* cls);

static void class_sync_init(void) {
  int expected = 0;
  if (atomic_compare_exchange_strong_explicit(
          &g_class_sync_state, &expected, 1, memory_order_acq_rel,
          memory_order_acquire)) {
    platform_mutex_init(&g_class_mutex);
    platform_cond_init(&g_class_cond);
    (void)atexit(class_snapshot_cleanup);
    atomic_store_explicit(&g_class_sync_state, 2, memory_order_release);
  } else {
    while (atomic_load_explicit(&g_class_sync_state, memory_order_acquire) !=
           2) {
    }
  }
}

bool my_widget_schema_name_valid(const char* name) {
  size_t i;
  if (name == NULL || name[0] == '\0') {
    return false;
  }
  for (i = 0; i < MY_WIDGET_SCHEMA_MAX_NAME_BYTES; i++) {
    if (name[i] == '\0') {
      return true;
    }
  }
  return false;
}

bool my_widget_schema_property_type_valid(my_prop_type_t type) {
  return type >= MY_PROP_STRING && type <= MY_PROP_COLOR;
}

static bool class_reserved_property(const char* name) {
  static const char* const reserved[] = {
      "type",     "name",    "tooltip", "class",    "x",       "y",
      "w",        "h",       "visible", "enable",   "lp",      "layout",
      "version",  "children", "bindings", "title",    "style"};
  size_t i;
  for (i = 0; i < sizeof(reserved) / sizeof(reserved[0]); i++) {
    if (my_str_eq(reserved[i], name)) {
      return true;
    }
  }
  return false;
}

bool my_widget_schema_properties_valid(const my_prop_desc_t* properties,
                                       size_t* count) {
  size_t i, j;
  if (properties == NULL) {
    if (count != NULL) {
      *count = 0u;
    }
    return true;
  }
  for (i = 0; i < MY_WIDGET_SCHEMA_MAX_PROPERTIES; i++) {
    if (properties[i].name == NULL) {
      if (count != NULL) {
        *count = i;
      }
      return true;
    }
    if (!my_widget_schema_name_valid(properties[i].name) ||
        !my_widget_schema_property_type_valid(properties[i].type) ||
        class_reserved_property(properties[i].name)) {
      return false;
    }
    for (j = 0; j < i; j++) {
      if (my_str_eq(properties[j].name, properties[i].name)) {
        return false;
      }
    }
  }
  return false;
}

bool my_widget_schema_properties_n_valid(const my_prop_desc_t* properties,
                                         size_t count) {
  size_t i, j;
  if (count == 0u) {
    return true;
  }
  if (properties == NULL || count > MY_WIDGET_SCHEMA_MAX_PROPERTIES) {
    return false;
  }
  for (i = 0; i < count; i++) {
    if (properties[i].name == NULL ||
        !my_widget_schema_name_valid(properties[i].name) ||
        !my_widget_schema_property_type_valid(properties[i].type) ||
        class_reserved_property(properties[i].name)) {
      return false;
    }
    for (j = 0; j < i; j++) {
      if (my_str_eq(properties[j].name, properties[i].name)) {
        return false;
      }
    }
  }
  return true;
}

bool my_widget_schema_events_valid(const char* const* events, size_t* count) {
  size_t i, j;
  if (events == NULL) {
    if (count != NULL) {
      *count = 0u;
    }
    return true;
  }
  for (i = 0; i < MY_WIDGET_SCHEMA_MAX_EVENTS; i++) {
    if (events[i] == NULL) {
      if (count != NULL) {
        *count = i;
      }
      return true;
    }
    if (!my_widget_schema_name_valid(events[i])) {
      return false;
    }
    for (j = 0; j < i; j++) {
      if (my_str_eq(events[j], events[i])) {
        return false;
      }
    }
  }
  return false;
}

bool my_widget_schema_events_n_valid(const char* const* events, size_t count) {
  size_t i, j;
  if (count == 0u) {
    return true;
  }
  if (events == NULL || count > MY_WIDGET_SCHEMA_MAX_EVENTS) {
    return false;
  }
  for (i = 0; i < count; i++) {
    if (events[i] == NULL || !my_widget_schema_name_valid(events[i])) {
      return false;
    }
    for (j = 0; j < i; j++) {
      if (my_str_eq(events[j], events[i])) {
        return false;
      }
    }
  }
  return true;
}

static my_ret_t class_register_locked(const my_widget_class_t* cls,
                                      bool builtin) {
  my_widget_class_snapshot_t* snapshot;
  size_t i;
  if (my_widget_registry_callback_active()) return MY_RET_NOT_SUPPORTED;
  if (atomic_load_explicit(&g_classes_frozen, memory_order_relaxed)) {
    return MY_RET_NOT_SUPPORTED;
  }
  if (cls == NULL || !my_widget_schema_name_valid(cls->type) ||
      cls->create == NULL ||
      !my_widget_schema_properties_valid(cls->props, NULL) ||
      !my_widget_schema_events_valid(cls->events, NULL)) {
    return MY_RET_INVALID_PARAMS;
  }
  snapshot = class_snapshot_copy(cls, builtin, NULL);
  if (snapshot == NULL) return MY_RET_OOM;
  for (i = 0; i < g_class_count; i++) {
    if (my_str_eq(g_classes[i]->type, cls->type)) {
      g_classes[i] = &snapshot->cls;
      return MY_RET_OK;
    }
  }
  if (g_class_count >= MY_WIDGET_CLASS_MAX) {
    g_class_snapshots = snapshot->next;
    class_snapshot_destroy(snapshot);
    return MY_RET_OOM;
  }
  g_classes[g_class_count] = &snapshot->cls;
  g_class_count++;
  return MY_RET_OK;
}

my_ret_t my_widget_class_register_builtin_entry(const my_widget_class_t* cls) {
  return class_register_locked(cls, true);
}

my_ret_t my_widget_class_register(const my_widget_class_t* cls) {
  my_ret_t ret;
  class_sync_init();
  platform_mutex_lock(&g_class_mutex);
  ret = class_register_locked(cls, false);
  platform_mutex_unlock(&g_class_mutex);
  return ret;
}

my_ret_t my_widget_class_freeze(void) {
  const my_widget_class_t* class_checkpoint[MY_WIDGET_CLASS_MAX];
  my_widget_class_snapshot_t* snapshot_checkpoint;
  size_t class_count_checkpoint;
  if (my_widget_registry_callback_active()) return MY_RET_NOT_SUPPORTED;
  class_sync_init();
  platform_mutex_lock(&g_class_mutex);
  if (atomic_load_explicit(&g_classes_frozen, memory_order_acquire)) {
    platform_mutex_unlock(&g_class_mutex);
    return MY_RET_OK;
  }
  if (!g_builtins_done) {
    memcpy(class_checkpoint, g_classes, sizeof(g_classes));
    class_count_checkpoint = g_class_count;
    snapshot_checkpoint = g_class_snapshots;
    my_ret_t ret = my_widget_class_register_builtins();
    if (ret != MY_RET_OK) {
      class_snapshot_rollback(snapshot_checkpoint, class_count_checkpoint,
                              class_checkpoint);
      platform_mutex_unlock(&g_class_mutex);
      return ret;
    }
    g_builtins_done = true;
  }
  {
    my_widget_class_table_t* table = (my_widget_class_table_t*)my_mem_calloc(
        NULL, 1u, sizeof(*table));
    if (table == NULL) {
      platform_mutex_unlock(&g_class_mutex);
      return MY_RET_OOM;
    }
    table->count = g_class_count;
    memcpy(table->classes, g_classes, sizeof(g_classes));
    table->next = g_class_tables;
    g_class_tables = table;
    atomic_store_explicit(&g_active_table, table, memory_order_release);
  }
  atomic_store_explicit(&g_classes_frozen, true, memory_order_release);
  platform_mutex_unlock(&g_class_mutex);
  return MY_RET_OK;
}

static my_widget_class_snapshot_t* class_snapshot_from_class(
    const my_widget_class_t* cls) {
  return cls != NULL ? (my_widget_class_snapshot_t*)cls : NULL;
}

static const my_widget_class_t* class_current_locked(const char* type) {
  size_t i;
  if (atomic_load_explicit(&g_classes_frozen, memory_order_acquire)) {
    my_widget_class_table_t* table = atomic_load_explicit(
        &g_active_table, memory_order_acquire);
    if (table == NULL) return NULL;
    for (i = 0u; i < table->count; i++) {
      if (my_str_eq(table->classes[i]->type, type)) {
        return table->classes[i];
      }
    }
    return NULL;
  }
  for (i = 0u; i < g_class_count; i++) {
    if (my_str_eq(g_classes[i]->type, type)) return g_classes[i];
  }
  return NULL;
}

my_ret_t my_widget_class_acquire(const char* type,
                                 const my_widget_class_t** out,
                                 my_widget_class_lease_t* lease) {
  const my_widget_class_t* found;
  my_widget_class_snapshot_t* snapshot;
  if (out == NULL || lease == NULL || !my_widget_schema_name_valid(type)) {
    return MY_RET_INVALID_PARAMS;
  }
  *out = NULL;
  lease->class_descriptor = NULL;
  lease->snapshot_token = NULL;
  lease->owner_cookie = NULL;
  lease->owner_thread = platform_thread_current_id();
  if (my_widget_class_find(type) == NULL) return MY_RET_NOT_FOUND;
  class_sync_init();
  platform_mutex_lock(&g_class_mutex);
  found = class_current_locked(type);
  snapshot = class_snapshot_from_class(found);
  if (found == NULL || snapshot == NULL || snapshot->retired) {
    platform_mutex_unlock(&g_class_mutex);
    return MY_RET_NOT_FOUND;
  }
  if (snapshot->module != NULL && snapshot->module->unloading) {
    platform_mutex_unlock(&g_class_mutex);
    return MY_RET_NOT_SUPPORTED;
  }
  if (snapshot->callback_leases == SIZE_MAX) {
    platform_mutex_unlock(&g_class_mutex);
    return MY_RET_FAIL;
  }
  snapshot->callback_leases++;
  if (snapshot->module != NULL) snapshot->module->callback_leases++;
  lease->class_descriptor = found;
  lease->snapshot_token = snapshot;
  lease->owner_cookie = lease;
  g_class_lease_depth++;
  my_widget_registry_callback_enter();
  *out = found;
  platform_mutex_unlock(&g_class_mutex);
  return MY_RET_OK;
}

void my_widget_class_release(my_widget_class_lease_t* lease) {
  my_widget_class_snapshot_t* snapshot;
  if (lease == NULL || lease->snapshot_token == NULL) return;
  if (!platform_thread_id_equal(lease->owner_thread,
                                platform_thread_current_id()) ||
      lease->owner_cookie != lease) {
    return;
  }
  snapshot = (my_widget_class_snapshot_t*)lease->snapshot_token;
  class_sync_init();
  platform_mutex_lock(&g_class_mutex);
  if (snapshot->callback_leases != 0u) {
    snapshot->callback_leases--;
    if (snapshot->callback_leases == 0u) {
      platform_cond_broadcast(&g_class_cond);
    }
  }
  if (snapshot->module != NULL && snapshot->module->callback_leases != 0u) {
    snapshot->module->callback_leases--;
  }
  platform_mutex_unlock(&g_class_mutex);
  if (g_class_lease_depth != 0u) g_class_lease_depth--;
  my_widget_registry_callback_leave();
  lease->class_descriptor = NULL;
  lease->snapshot_token = NULL;
  lease->owner_cookie = NULL;
}

my_widget_class_module_t* my_widget_class_module_create(
    const my_allocator_t* allocator) {
  my_widget_class_module_t* module = (my_widget_class_module_t*)my_mem_calloc(
      allocator, 1u, sizeof(*module));
  if (module != NULL) {
    module->allocator = allocator;
    module->references = 1u;
    class_sync_init();
    platform_mutex_lock(&g_class_mutex);
    module->next = g_modules;
    g_modules = module;
    platform_mutex_unlock(&g_class_mutex);
  }
  return module;
}

my_ret_t my_widget_class_module_retain(my_widget_class_module_t* module) {
  if (module == NULL) return MY_RET_INVALID_PARAMS;
  class_sync_init();
  platform_mutex_lock(&g_class_mutex);
  if (!module_is_known_locked(module) || module->destroyed ||
      module->references == SIZE_MAX) {
    platform_mutex_unlock(&g_class_mutex);
    return MY_RET_NOT_SUPPORTED;
  }
  module->references++;
  platform_mutex_unlock(&g_class_mutex);
  return MY_RET_OK;
}

void my_widget_class_module_release(my_widget_class_module_t* module) {
  if (module == NULL) return;
  class_sync_init();
  platform_mutex_lock(&g_class_mutex);
  if (module_is_known_locked(module) && module->references > 1u) {
    module->references--;
  }
  platform_mutex_unlock(&g_class_mutex);
}

my_ret_t my_widget_class_module_register_entry(
    my_widget_class_module_t* module) {
  if (module == NULL) return MY_RET_INVALID_PARAMS;
  class_sync_init();
  platform_mutex_lock(&g_class_mutex);
  if (!module_is_known_locked(module) || module->destroyed ||
      module->unloading ||
      module->registered_classes == SIZE_MAX) {
    platform_mutex_unlock(&g_class_mutex);
    return MY_RET_NOT_SUPPORTED;
  }
  module->registered_classes++;
  platform_mutex_unlock(&g_class_mutex);
  return MY_RET_OK;
}

void my_widget_class_module_unregister_entry(
    my_widget_class_module_t* module) {
  if (module == NULL) return;
  class_sync_init();
  platform_mutex_lock(&g_class_mutex);
  if (module_is_known_locked(module) && module->registered_classes != 0u) {
    module->registered_classes--;
  }
  platform_mutex_unlock(&g_class_mutex);
}

my_ret_t my_widget_class_module_callback_acquire(
    my_widget_class_module_t* module) {
  if (module == NULL) return MY_RET_OK;
  class_sync_init();
  platform_mutex_lock(&g_class_mutex);
  if (!module_is_known_locked(module) || module->destroyed ||
      module->unloading ||
      module->callback_leases == SIZE_MAX) {
    platform_mutex_unlock(&g_class_mutex);
    return MY_RET_NOT_SUPPORTED;
  }
  module->callback_leases++;
  platform_mutex_unlock(&g_class_mutex);
  return MY_RET_OK;
}

void my_widget_class_module_callback_release(
    my_widget_class_module_t* module) {
  if (module == NULL) return;
  class_sync_init();
  platform_mutex_lock(&g_class_mutex);
  if (module_is_known_locked(module) && module->callback_leases != 0u) {
    module->callback_leases--;
  }
  platform_mutex_unlock(&g_class_mutex);
}

my_ret_t my_widget_class_module_begin_unload(
    my_widget_class_module_t* module) {
  if (module == NULL) return MY_RET_INVALID_PARAMS;
  if (my_widget_registry_callback_active()) return MY_RET_NOT_SUPPORTED;
  class_sync_init();
  platform_mutex_lock(&g_class_mutex);
  if (!module_is_known_locked(module) || module->destroyed) {
    platform_mutex_unlock(&g_class_mutex);
    return MY_RET_NOT_SUPPORTED;
  }
  module->unloading = true;
  platform_mutex_unlock(&g_class_mutex);
  return MY_RET_OK;
}

my_ret_t my_widget_class_module_try_unload(my_widget_class_module_t* module) {
  my_ret_t ret = MY_RET_OK;
  if (module == NULL) return MY_RET_INVALID_PARAMS;
  if (my_widget_registry_callback_active()) return MY_RET_NOT_SUPPORTED;
  class_sync_init();
  platform_mutex_lock(&g_class_mutex);
  if (!module_is_known_locked(module) || module->destroyed ||
      !module->unloading ||
      module->registered_classes != 0u ||
      module->callback_leases != 0u || module->instances != 0u) {
    ret = MY_RET_NOT_SUPPORTED;
  }
  platform_mutex_unlock(&g_class_mutex);
  return ret;
}

my_ret_t my_widget_class_module_destroy(my_widget_class_module_t* module) {
  my_ret_t ret;
  if (module == NULL) return MY_RET_INVALID_PARAMS;
  if (my_widget_registry_callback_active()) return MY_RET_NOT_SUPPORTED;
  ret = my_widget_class_module_try_unload(module);
  if (ret != MY_RET_OK) return ret;
  class_sync_init();
  platform_mutex_lock(&g_class_mutex);
  if (!module_is_known_locked(module) || module->destroyed ||
      module->references != 1u ||
      module->registered_classes != 0u || module->callback_leases != 0u ||
      module->instances != 0u) {
    platform_mutex_unlock(&g_class_mutex);
    return MY_RET_NOT_SUPPORTED;
  }
  module->destroyed = true;
  module->references = 0u;
  platform_mutex_unlock(&g_class_mutex);
  return MY_RET_OK;
}

my_ret_t my_widget_class_module_bind_widget(
    my_widget_class_module_t* module, my_widget_t* widget) {
  my_widget_class_instance_binding_t* binding;
  my_widget_class_instance_binding_t* current;
  const my_allocator_t* allocator;
  if (widget == NULL || module == NULL) {
    return MY_RET_INVALID_PARAMS;
  }
  allocator = ((my_object_t*)widget)->allocator;
  class_sync_init();
  platform_mutex_lock(&g_class_mutex);
  if (!module_is_known_locked(module) || module->destroyed ||
      module->unloading || module->instances == SIZE_MAX) {
    platform_mutex_unlock(&g_class_mutex);
    return MY_RET_NOT_SUPPORTED;
  }
  for (current = g_instance_bindings; current != NULL; current = current->next) {
    if (current->widget == widget) {
      platform_mutex_unlock(&g_class_mutex);
      return MY_RET_INVALID_PARAMS;
    }
  }
  binding = (my_widget_class_instance_binding_t*)my_mem_calloc(
      allocator, 1u, sizeof(*binding));
  if (binding == NULL) {
    platform_mutex_unlock(&g_class_mutex);
    return MY_RET_OOM;
  }
  binding->widget = widget;
  binding->module = module;
  binding->allocator = allocator;
  binding->next = g_instance_bindings;
  g_instance_bindings = binding;
  module->instances++;
  platform_mutex_unlock(&g_class_mutex);
  return MY_RET_OK;
}

my_ret_t my_widget_class_bind_instance(
    my_widget_t* widget, const my_widget_class_lease_t* lease) {
  my_widget_class_snapshot_t* snapshot;
  if (widget == NULL || lease == NULL || lease->snapshot_token == NULL ||
      lease->owner_cookie != lease ||
      !platform_thread_id_equal(lease->owner_thread,
                                platform_thread_current_id())) {
    return MY_RET_INVALID_PARAMS;
  }
  snapshot = (my_widget_class_snapshot_t*)lease->snapshot_token;
  if (lease->class_descriptor != &snapshot->cls) {
    return MY_RET_NOT_SUPPORTED;
  }
  if (snapshot->module == NULL) return MY_RET_OK;
  return my_widget_class_module_bind_widget(snapshot->module, widget);
}

my_widget_t* my_widget_class_create(const char* type,
                                    const my_allocator_t* allocator) {
  const my_widget_class_t* cls;
  my_widget_class_lease_t lease = {0};
  my_widget_t* widget;
  if (my_widget_class_acquire(type, &cls, &lease) != MY_RET_OK) {
    return NULL;
  }
  widget = cls->create(allocator);
  if (widget != NULL && my_widget_class_bind_instance(widget, &lease) !=
                             MY_RET_OK) {
    my_widget_unref(widget);
    widget = NULL;
  }
  my_widget_class_release(&lease);
  return widget;
}

void my_widget_class_unbind_instance(my_widget_t* widget) {
  my_widget_class_instance_binding_t** link;
  my_widget_class_instance_binding_t* binding;
  if (widget == NULL) return;
  class_sync_init();
  platform_mutex_lock(&g_class_mutex);
  link = &g_instance_bindings;
  while (*link != NULL && (*link)->widget != widget) link = &(*link)->next;
  if (*link == NULL) {
    platform_mutex_unlock(&g_class_mutex);
    return;
  }
  binding = *link;
  *link = binding->next;
  if (binding->module->instances != 0u) binding->module->instances--;
  platform_mutex_unlock(&g_class_mutex);
  my_mem_free(binding->allocator, binding);
}

static void class_snapshot_retire_and_wait_locked(
    my_widget_class_snapshot_t* snapshot) {
  if (snapshot == NULL || snapshot->builtin) return;
  snapshot->retired = true;
  while (snapshot->callback_leases != 0u) {
    platform_cond_wait(&g_class_cond, &g_class_mutex);
  }
}

static my_ret_t class_snapshot_remove_locked(
    my_widget_class_snapshot_t* snapshot) {
  my_widget_class_snapshot_t** link;
  if (snapshot == NULL) return MY_RET_INVALID_PARAMS;
  link = &g_class_snapshots;
  while (*link != NULL && *link != snapshot) link = &(*link)->next;
  if (*link == NULL) return MY_RET_NOT_FOUND;
  *link = snapshot->next;
  class_snapshot_destroy(snapshot);
  return MY_RET_OK;
}

static my_ret_t class_runtime_register_module(
    my_widget_class_module_t* module, const my_widget_class_t* cls) {
  my_widget_class_snapshot_t* snapshot;
  my_widget_class_snapshot_t* replaced_snapshot = NULL;
  my_widget_class_table_t* old_table;
  my_widget_class_table_t* table;
  size_t i;
  bool replaced = false;
  my_ret_t ret;
  if (my_widget_registry_callback_active() || g_class_lease_depth != 0u) {
    return MY_RET_NOT_SUPPORTED;
  }
  class_sync_init();
  if (!my_widget_class_is_frozen()) return MY_RET_NOT_SUPPORTED;
  platform_mutex_lock(&g_class_mutex);
  if (!atomic_load_explicit(&g_classes_frozen, memory_order_acquire)) {
    platform_mutex_unlock(&g_class_mutex);
    return MY_RET_NOT_SUPPORTED;
  }
  if (module != NULL && (!module_is_known_locked(module) ||
                         module->destroyed || module->unloading)) {
    platform_mutex_unlock(&g_class_mutex);
    return MY_RET_NOT_SUPPORTED;
  }
  if (cls == NULL || !my_widget_schema_name_valid(cls->type) ||
      cls->create == NULL ||
      !my_widget_schema_properties_valid(cls->props, NULL) ||
      !my_widget_schema_events_valid(cls->events, NULL)) {
    platform_mutex_unlock(&g_class_mutex);
    return MY_RET_INVALID_PARAMS;
  }
  snapshot = class_snapshot_copy(cls, false, module);
  if (snapshot == NULL) {
    platform_mutex_unlock(&g_class_mutex);
    return MY_RET_OOM;
  }
  old_table = atomic_load_explicit(&g_active_table, memory_order_acquire);
  table = (my_widget_class_table_t*)my_mem_calloc(NULL, 1u, sizeof(*table));
  if (table == NULL) {
    (void)class_snapshot_remove_locked(snapshot);
    platform_mutex_unlock(&g_class_mutex);
    return MY_RET_OOM;
  }
  if (old_table != NULL) {
    table->count = old_table->count;
    memcpy(table->classes, old_table->classes, sizeof(table->classes));
  }
  for (i = 0; i < table->count; i++) {
    if (my_str_eq(table->classes[i]->type, cls->type)) {
      if (class_snapshot_from_class(table->classes[i])->builtin) {
        my_mem_free(NULL, table);
        (void)class_snapshot_remove_locked(snapshot);
        platform_mutex_unlock(&g_class_mutex);
        return MY_RET_NOT_SUPPORTED;
      }
      replaced_snapshot = class_snapshot_from_class(table->classes[i]);
      table->classes[i] = &snapshot->cls;
      replaced = true;
      break;
    }
  }
  if (!replaced) {
    if (table->count >= MY_WIDGET_CLASS_MAX) {
      my_mem_free(NULL, table);
      (void)class_snapshot_remove_locked(snapshot);
      platform_mutex_unlock(&g_class_mutex);
      return MY_RET_OOM;
    }
    table->classes[table->count++] = &snapshot->cls;
  }
  table->next = g_class_tables;
  g_class_tables = table;
  atomic_store_explicit(&g_active_table, table, memory_order_release);
  if (module != NULL &&
      (!replaced || replaced_snapshot == NULL ||
       replaced_snapshot->module != module)) {
    if (module->registered_classes == SIZE_MAX) {
      atomic_store_explicit(&g_active_table, old_table, memory_order_release);
      g_class_tables = table->next;
      my_mem_free(NULL, table);
      (void)class_snapshot_remove_locked(snapshot);
      platform_mutex_unlock(&g_class_mutex);
      return MY_RET_NOT_SUPPORTED;
    }
    module->registered_classes++;
  }
  if (replaced_snapshot != NULL && replaced_snapshot->module != NULL &&
      replaced_snapshot->module != module &&
      replaced_snapshot->module->registered_classes != 0u) {
    replaced_snapshot->module->registered_classes--;
  }
  class_snapshot_retire_and_wait_locked(replaced_snapshot);
  ret = MY_RET_OK;
  platform_mutex_unlock(&g_class_mutex);
  return ret;
}

my_ret_t my_widget_class_runtime_register(const my_widget_class_t* cls) {
  return class_runtime_register_module(NULL, cls);
}

my_ret_t my_widget_class_runtime_register_module(
    my_widget_class_module_t* module, const my_widget_class_t* cls) {
  if (module == NULL) return MY_RET_INVALID_PARAMS;
  return class_runtime_register_module(module, cls);
}

my_ret_t my_widget_class_runtime_unregister(const char* type) {
  my_widget_class_table_t* old_table;
  my_widget_class_table_t* table;
  size_t i;
  if (my_widget_registry_callback_active() || g_class_lease_depth != 0u) {
    return MY_RET_NOT_SUPPORTED;
  }
  if (!my_widget_schema_name_valid(type)) return MY_RET_INVALID_PARAMS;
  class_sync_init();
  if (!my_widget_class_is_frozen()) return MY_RET_NOT_SUPPORTED;
  platform_mutex_lock(&g_class_mutex);
  if (!atomic_load_explicit(&g_classes_frozen, memory_order_acquire)) {
    platform_mutex_unlock(&g_class_mutex);
    return MY_RET_NOT_SUPPORTED;
  }
  old_table = atomic_load_explicit(&g_active_table, memory_order_acquire);
  if (old_table == NULL) {
    platform_mutex_unlock(&g_class_mutex);
    return MY_RET_NOT_FOUND;
  }
  for (i = 0; i < old_table->count; i++) {
    if (my_str_eq(old_table->classes[i]->type, type)) break;
  }
  if (i == old_table->count) {
    platform_mutex_unlock(&g_class_mutex);
    return MY_RET_NOT_FOUND;
  }
  if (class_snapshot_from_class(old_table->classes[i])->builtin) {
    platform_mutex_unlock(&g_class_mutex);
    return MY_RET_NOT_SUPPORTED;
  }
  table = (my_widget_class_table_t*)my_mem_calloc(NULL, 1u, sizeof(*table));
  if (table == NULL) {
    platform_mutex_unlock(&g_class_mutex);
    return MY_RET_OOM;
  }
  table->count = old_table->count - 1u;
  memcpy(table->classes, old_table->classes, i * sizeof(table->classes[0]));
  memcpy(&table->classes[i], &old_table->classes[i + 1u],
         (old_table->count - i - 1u) * sizeof(table->classes[0]));
  table->next = g_class_tables;
  g_class_tables = table;
  atomic_store_explicit(&g_active_table, table, memory_order_release);
  {
    my_widget_class_snapshot_t* snapshot =
        class_snapshot_from_class(old_table->classes[i]);
    if (snapshot->module != NULL && snapshot->module->registered_classes != 0u) {
      snapshot->module->registered_classes--;
    }
    class_snapshot_retire_and_wait_locked(snapshot);
  }
  platform_mutex_unlock(&g_class_mutex);
  return MY_RET_OK;
}

bool my_widget_class_is_frozen(void) {
  return atomic_load_explicit(&g_classes_frozen, memory_order_acquire);
}

bool my_widget_class_is_builtin_type(const char* type) {
  const my_widget_class_t* cls;
  if (!my_widget_schema_name_valid(type)) return false;
  cls = my_widget_class_find(type);
  return cls != NULL && class_snapshot_from_class(cls)->builtin;
}

const my_widget_class_t* my_widget_class_find(const char* type) {
  const my_widget_class_t* class_checkpoint[MY_WIDGET_CLASS_MAX];
  my_widget_class_snapshot_t* snapshot_checkpoint;
  size_t class_count_checkpoint;
  size_t i;
  const my_widget_class_t* result = NULL;
  if (!my_widget_schema_name_valid(type)) {
    return NULL;
  }
  if (atomic_load_explicit(&g_classes_frozen, memory_order_acquire)) {
    my_widget_class_table_t* table = atomic_load_explicit(
        &g_active_table, memory_order_acquire);
    if (table == NULL) return NULL;
    for (i = 0; i < table->count; i++) {
      if (my_str_eq(table->classes[i]->type, type)) return table->classes[i];
    }
    return NULL;
  }
  class_sync_init();
  platform_mutex_lock(&g_class_mutex);
  if (!g_builtins_done) {
    memcpy(class_checkpoint, g_classes, sizeof(g_classes));
    class_count_checkpoint = g_class_count;
    snapshot_checkpoint = g_class_snapshots;
    if (my_widget_class_register_builtins() != MY_RET_OK) {
      class_snapshot_rollback(snapshot_checkpoint, class_count_checkpoint,
                              class_checkpoint);
      platform_mutex_unlock(&g_class_mutex);
      return NULL;
    }
    g_builtins_done = true;
  }
  for (i = 0; i < g_class_count; i++) {
    if (my_str_eq(g_classes[i]->type, type)) {
      result = g_classes[i];
      break;
    }
  }
  platform_mutex_unlock(&g_class_mutex);
  return result;
}

static const my_prop_desc_t* find_prop(const my_widget_class_t* cls,
                                       const char* name) {
  const my_prop_desc_t* p;
  if (cls == NULL || cls->props == NULL) {
    return NULL;
  }
  for (p = cls->props; p->name != NULL; p++) {
    if (my_str_eq(p->name, name)) {
      return p;
    }
  }
  return NULL;
}

my_ret_t my_widget_set_prop(my_widget_t* w, const char* name,
                            const my_value_t* v) {
  const my_prop_desc_t* p;
  const my_widget_class_t* cls;
  my_widget_class_lease_t lease = {0};
  if (w == NULL || name == NULL || v == NULL) {
    return MY_RET_INVALID_PARAMS;
  }
  /* base-class common properties (no class table involved) */
  if (strcmp(name, "visible") == 0) {
    return my_widget_set_visible(w, v->type == MY_VALUE_BOOL
                                        ? my_value_get_bool(v)
                                        : true);
  }
  if (strcmp(name, "enable") == 0) {
    if (v->type == MY_VALUE_BOOL) {
      w->enable = my_value_get_bool(v);
      my_widget_invalidate(w, NULL);
    }
    return MY_RET_OK;
  }
  if (strlen(name) == 1 && strchr("xywh", name[0]) != NULL) {
    my_rect_t r;
    int32_t n;
    if (v->type != MY_VALUE_INT32) {
      return MY_RET_NOT_SUPPORTED;
    }
    r = w->rect;
    n = my_value_get_int32(v);
    if (name[0] == 'x') {
      r.x = n;
    } else if (name[0] == 'y') {
      r.y = n;
    } else if (name[0] == 'w') {
      r.w = n;
    } else {
      r.h = n;
    }
    return my_widget_set_rect(w, &r);
  }
  if (my_widget_class_acquire(w->widget_type, &cls, &lease) != MY_RET_OK) {
    return MY_RET_NOT_SUPPORTED;
  }
  p = find_prop(cls, name);
  if (p != NULL) {
    if (cls != NULL && cls->is_instance != NULL && !cls->is_instance(w)) {
      my_widget_class_release(&lease);
      return MY_RET_INVALID_PARAMS;
    }
  }
  if (p == NULL || p->set == NULL) {
    my_widget_class_release(&lease);
    return MY_RET_NOT_SUPPORTED;
  }
  my_ret_t ret = p->set(w, v);
  my_widget_class_release(&lease);
  return ret;
}

my_ret_t my_widget_get_prop(my_widget_t* w, const char* name, my_value_t* v) {
  const my_prop_desc_t* p;
  const my_widget_class_t* cls;
  my_widget_class_lease_t lease = {0};
  if (w == NULL || name == NULL || v == NULL) {
    return MY_RET_INVALID_PARAMS;
  }
  if (strcmp(name, "visible") == 0) {
    return my_value_set_bool(v, w->visible);
  }
  if (strcmp(name, "enable") == 0) {
    return my_value_set_bool(v, w->enable);
  }
  if (strlen(name) == 1 && strchr("xywh", name[0]) != NULL) {
    int32_t n = name[0] == 'x'   ? w->rect.x
                : name[0] == 'y' ? w->rect.y
                : name[0] == 'w' ? w->rect.w
                                 : w->rect.h;
    return my_value_set_int32(v, n);
  }
  if (my_widget_class_acquire(w->widget_type, &cls, &lease) != MY_RET_OK) {
    return MY_RET_NOT_SUPPORTED;
  }
  p = find_prop(cls, name);
  if (p != NULL) {
    if (cls != NULL && cls->is_instance != NULL && !cls->is_instance(w)) {
      my_widget_class_release(&lease);
      return MY_RET_INVALID_PARAMS;
    }
  }
  if (p == NULL || p->get == NULL) {
    my_widget_class_release(&lease);
    return MY_RET_NOT_SUPPORTED;
  }
  my_ret_t ret = p->get(w, v);
  my_widget_class_release(&lease);
  return ret;
}

/* ---------------- typed convenience wrappers ---------------- */

my_ret_t my_widget_set_prop_str(my_widget_t* w, const char* name,
                                const char* v) {
  my_value_t val;
  my_ret_t r;
  my_value_init(&val, NULL);
  my_value_set_str(&val, v);
  r = my_widget_set_prop(w, name, &val);
  my_value_reset(&val);
  return r;
}

my_ret_t my_widget_set_prop_int(my_widget_t* w, const char* name, int32_t v) {
  my_value_t val;
  my_ret_t r;
  my_value_init(&val, NULL);
  my_value_set_int32(&val, v);
  r = my_widget_set_prop(w, name, &val);
  my_value_reset(&val);
  return r;
}

my_ret_t my_widget_set_prop_float(my_widget_t* w, const char* name, float v) {
  my_value_t val;
  my_ret_t r;
  my_value_init(&val, NULL);
  my_value_set_float(&val, v);
  r = my_widget_set_prop(w, name, &val);
  my_value_reset(&val);
  return r;
}

my_ret_t my_widget_set_prop_bool(my_widget_t* w, const char* name, bool v) {
  my_value_t val;
  my_ret_t r;
  my_value_init(&val, NULL);
  my_value_set_bool(&val, v);
  r = my_widget_set_prop(w, name, &val);
  my_value_reset(&val);
  return r;
}
