#pragma once

#include <core/types.h>

#define BREAK_PLUGIN_ABI_VERSION 1u
#define BREAK_PLUGIN_ENTRY_SYMBOL "break_plugin_entry"
#define BREAK_PLUGIN_HARD_MAX 64u
#define BREAK_PLUGIN_NAME_CAPACITY 64u
#define BREAK_PLUGIN_BUILD_ID_CAPACITY 64u
#define BREAK_PLUGIN_PATH_CAPACITY 1024u

typedef bool (*BreakPluginRegisterFn)(void *user);
typedef void (*BreakPluginUnregisterFn)(void *user);

typedef struct BreakPluginDescriptor {
    u32 struct_size;
    u32 abi_version;
    const char *name;
    const char *build_id;
    BreakPluginRegisterFn register_fn;
    BreakPluginUnregisterFn unregister_fn;
} BreakPluginDescriptor;

typedef const BreakPluginDescriptor *(*BreakPluginEntryFn)(void);

typedef struct BreakPluginHandle {
    u32 index;
    u32 generation;
} BreakPluginHandle;

typedef enum BreakPluginStatus {
    BREAK_PLUGIN_OK = 0,
    BREAK_PLUGIN_INVALID,
    BREAK_PLUGIN_OVERLOAD,
    BREAK_PLUGIN_OOM,
    BREAK_PLUGIN_STALE,
    BREAK_PLUGIN_REJECTED,
    BREAK_PLUGIN_FAILED
} BreakPluginStatus;

typedef struct BreakPluginManager BreakPluginManager;

BreakPluginManager *break_plugin_create(u32 capacity, void *plugin_user);
BreakPluginStatus break_plugin_destroy(BreakPluginManager *manager);
BreakPluginStatus break_plugin_load(BreakPluginManager *manager,
                                    const char *path, const char *build_id,
                                    const u8 expected_sha256[32],
                                    BreakPluginHandle *out_handle);
BreakPluginStatus break_plugin_acquire(BreakPluginManager *manager,
                                       BreakPluginHandle handle);
BreakPluginStatus break_plugin_release(BreakPluginManager *manager,
                                       BreakPluginHandle handle);
BreakPluginStatus break_plugin_unload(BreakPluginManager *manager,
                                      BreakPluginHandle handle);
BreakPluginStatus break_plugin_unload_all(BreakPluginManager *manager);

#if defined(BREAK_SYSTEM_TESTING)
void break_plugin_test_set_generation(BreakPluginManager *manager,
                                      u32 index, u32 generation);
#endif
