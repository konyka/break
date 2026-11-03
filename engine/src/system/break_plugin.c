#include <system/break_plugin.h>

#include <platform/platform_dynamic.h>

#include <stdlib.h>
#include <string.h>

typedef struct BreakPluginSlot {
    bool used;
    bool retired;
    PlatformDynamicLibrary *library;
    BreakPluginUnregisterFn unregister_fn;
    char name[BREAK_PLUGIN_NAME_CAPACITY];
    char build_id[BREAK_PLUGIN_BUILD_ID_CAPACITY];
    char path[BREAK_PLUGIN_PATH_CAPACITY];
    u32 generation;
    u32 references;
} BreakPluginSlot;

struct BreakPluginManager {
    u32 capacity;
    u32 order_count;
    BreakPluginSlot *slots;
    u32 *load_order;
    void *plugin_user;
    bool busy;
};

static usize plugin_bounded_length(const char *text, usize capacity) {
    usize length = 0u;
    if (!text) return SIZE_MAX;
    while (length < capacity && text[length]) length++;
    return length == capacity ? SIZE_MAX : length;
}

static bool plugin_token_valid(const char *text, usize capacity) {
    usize length = plugin_bounded_length(text, capacity);
    if (length == SIZE_MAX || length == 0u) return false;
    for (usize i = 0u; i < length; i++) {
        u8 c = (u8)text[i];
        if (c < 0x21u || c > 0x7eu) return false;
    }
    return true;
}

static void plugin_slot_clear(BreakPluginSlot *slot) {
    slot->used = false;
    slot->library = NULL;
    slot->unregister_fn = NULL;
    slot->name[0] = '\0';
    slot->build_id[0] = '\0';
    slot->path[0] = '\0';
    slot->references = 0u;
}

static BreakPluginSlot *plugin_slot_for_handle(BreakPluginManager *manager,
                                               BreakPluginHandle handle) {
    BreakPluginSlot *slot;
    if (!manager || handle.index >= manager->capacity) return NULL;
    slot = &manager->slots[handle.index];
    if (!slot->used || slot->generation != handle.generation) return NULL;
    return slot;
}

static void plugin_next_generation(BreakPluginSlot *slot) {
    if (slot->generation == UINT32_MAX)
        slot->retired = true;
    else
        slot->generation++;
}

#if defined(BREAK_SYSTEM_TESTING)
void break_plugin_test_set_generation(BreakPluginManager *manager,
                                      u32 index, u32 generation) {
    if (manager && index < manager->capacity && manager->slots[index].used)
        manager->slots[index].generation = generation;
}
#endif

BreakPluginManager *break_plugin_create(u32 capacity, void *plugin_user) {
    BreakPluginManager *manager;
    if (capacity == 0u || capacity > BREAK_PLUGIN_HARD_MAX) return NULL;
    manager = (BreakPluginManager *)calloc(1u, sizeof(*manager));
    if (!manager) return NULL;
    manager->slots = (BreakPluginSlot *)calloc(capacity, sizeof(BreakPluginSlot));
    manager->load_order = (u32 *)calloc(capacity, sizeof(u32));
    if (!manager->slots || !manager->load_order) {
        free(manager->load_order);
        free(manager->slots);
        free(manager);
        return NULL;
    }
    manager->capacity = capacity;
    manager->plugin_user = plugin_user;
    for (u32 i = 0u; i < capacity; i++) manager->slots[i].generation = 1u;
    return manager;
}

BreakPluginStatus break_plugin_load(BreakPluginManager *manager,
                                    const char *path, const char *build_id,
                                    const u8 expected_sha256[32],
                                    BreakPluginHandle *out_handle) {
    BreakPluginStatus status = BREAK_PLUGIN_FAILED;
    BreakPluginSlot *slot = NULL;
    PlatformDynamicLibrary *library = NULL;
    PlatformDynamicOpenStatus open_status;
    void *symbol;
    BreakPluginEntryFn entry = NULL;
    const BreakPluginDescriptor *descriptor;
    bool committed = false;
    usize path_length;
    usize build_length;
    usize name_length;
    if (out_handle) {
        out_handle->index = 0u;
        out_handle->generation = 0u;
    }
    if (!manager || !out_handle || !expected_sha256 ||
        !plugin_token_valid(build_id, BREAK_PLUGIN_BUILD_ID_CAPACITY))
        return BREAK_PLUGIN_INVALID;
    path_length = plugin_bounded_length(path, BREAK_PLUGIN_PATH_CAPACITY);
    if (path_length == SIZE_MAX || path_length == 0u) return BREAK_PLUGIN_INVALID;
    if (manager->busy) return BREAK_PLUGIN_REJECTED;
    manager->busy = true;
    for (u32 i = 0u; i < manager->capacity; i++) {
        if (manager->slots[i].used && strcmp(manager->slots[i].path, path) == 0) {
            status = BREAK_PLUGIN_REJECTED;
            goto done;
        }
    }
    for (u32 i = 0u; i < manager->capacity; i++) {
        if (!manager->slots[i].used && !manager->slots[i].retired) {
            slot = &manager->slots[i];
            break;
        }
    }
    if (!slot) {
        status = BREAK_PLUGIN_OVERLOAD;
        goto done;
    }
    open_status = platform_dynamic_open_verified(path, expected_sha256, &library);
    if (open_status == PLATFORM_DYNAMIC_OPEN_OVERLOAD) {
        status = BREAK_PLUGIN_OVERLOAD;
        goto done;
    }
    if (open_status == PLATFORM_DYNAMIC_OPEN_MISMATCH) {
        status = BREAK_PLUGIN_REJECTED;
        goto done;
    }
    if (open_status != PLATFORM_DYNAMIC_OPEN_OK) {
        status = BREAK_PLUGIN_FAILED;
        goto done;
    }
    symbol = platform_dynamic_symbol(library, BREAK_PLUGIN_ENTRY_SYMBOL);
    if (!symbol || sizeof(symbol) != sizeof(entry)) {
        status = BREAK_PLUGIN_FAILED;
        goto done;
    }
    memcpy(&entry, &symbol, sizeof(entry));
    descriptor = entry();
    if (!descriptor || descriptor->struct_size != sizeof(BreakPluginDescriptor) ||
        descriptor->abi_version != BREAK_PLUGIN_ABI_VERSION) {
        status = BREAK_PLUGIN_REJECTED;
        goto done;
    }
    build_length = plugin_bounded_length(descriptor->build_id,
                                         BREAK_PLUGIN_BUILD_ID_CAPACITY);
    name_length = plugin_bounded_length(descriptor->name, BREAK_PLUGIN_NAME_CAPACITY);
    if (build_length == SIZE_MAX || build_length == 0u ||
        !plugin_token_valid(descriptor->build_id, BREAK_PLUGIN_BUILD_ID_CAPACITY) ||
        !plugin_token_valid(descriptor->name, BREAK_PLUGIN_NAME_CAPACITY) ||
        strcmp(descriptor->build_id, build_id) != 0) {
        status = BREAK_PLUGIN_REJECTED;
        goto done;
    }
    for (u32 i = 0u; i < manager->capacity; i++) {
        if (manager->slots[i].used &&
            strcmp(manager->slots[i].name, descriptor->name) == 0) {
            status = BREAK_PLUGIN_REJECTED;
            goto done;
        }
    }
    memcpy(slot->name, descriptor->name, name_length + 1u);
    memcpy(slot->build_id, descriptor->build_id, build_length + 1u);
    memcpy(slot->path, path, path_length + 1u);
    slot->library = library;
    slot->unregister_fn = descriptor->unregister_fn;
    if (descriptor->register_fn && !descriptor->register_fn(manager->plugin_user)) {
        status = BREAK_PLUGIN_FAILED;
        goto done;
    }
    slot->used = true;
    manager->load_order[manager->order_count++] = (u32)(slot - manager->slots);
    out_handle->index = (u32)(slot - manager->slots);
    out_handle->generation = slot->generation;
    committed = true;
    status = BREAK_PLUGIN_OK;

done:
    if (!committed) {
        if (slot) plugin_slot_clear(slot);
        if (library) platform_dynamic_close(library);
    }
    manager->busy = false;
    return status;
}

BreakPluginStatus break_plugin_acquire(BreakPluginManager *manager,
                                       BreakPluginHandle handle) {
    BreakPluginSlot *slot;
    if (!manager) return BREAK_PLUGIN_INVALID;
    if (manager->busy) return BREAK_PLUGIN_REJECTED;
    slot = plugin_slot_for_handle(manager, handle);
    if (!slot) return BREAK_PLUGIN_STALE;
    if (slot->references == UINT32_MAX) return BREAK_PLUGIN_OVERLOAD;
    slot->references++;
    return BREAK_PLUGIN_OK;
}

BreakPluginStatus break_plugin_release(BreakPluginManager *manager,
                                       BreakPluginHandle handle) {
    BreakPluginSlot *slot;
    if (!manager) return BREAK_PLUGIN_INVALID;
    if (manager->busy) return BREAK_PLUGIN_REJECTED;
    slot = plugin_slot_for_handle(manager, handle);
    if (!slot) return BREAK_PLUGIN_STALE;
    if (slot->references == 0u) return BREAK_PLUGIN_REJECTED;
    slot->references--;
    return BREAK_PLUGIN_OK;
}

static void plugin_unload_slot(BreakPluginManager *manager, u32 index) {
    BreakPluginSlot *slot = &manager->slots[index];
    if (slot->unregister_fn) slot->unregister_fn(manager->plugin_user);
    platform_dynamic_close(slot->library);
    plugin_slot_clear(slot);
    plugin_next_generation(slot);
    for (u32 i = 0u; i < manager->order_count; i++) {
        if (manager->load_order[i] == index) {
            if (i + 1u < manager->order_count)
                memmove(manager->load_order + i, manager->load_order + i + 1u,
                        (manager->order_count - i - 1u) * sizeof(u32));
            manager->order_count--;
            break;
        }
    }
}

BreakPluginStatus break_plugin_unload(BreakPluginManager *manager,
                                      BreakPluginHandle handle) {
    BreakPluginSlot *slot;
    if (!manager) return BREAK_PLUGIN_INVALID;
    if (manager->busy) return BREAK_PLUGIN_REJECTED;
    slot = plugin_slot_for_handle(manager, handle);
    if (!slot) return BREAK_PLUGIN_STALE;
    if (slot->references != 0u) return BREAK_PLUGIN_REJECTED;
    manager->busy = true;
    plugin_unload_slot(manager, handle.index);
    manager->busy = false;
    return BREAK_PLUGIN_OK;
}

BreakPluginStatus break_plugin_unload_all(BreakPluginManager *manager) {
    if (!manager) return BREAK_PLUGIN_INVALID;
    if (manager->busy) return BREAK_PLUGIN_REJECTED;
    for (u32 i = 0u; i < manager->capacity; i++) {
        if (manager->slots[i].used && manager->slots[i].references != 0u)
            return BREAK_PLUGIN_REJECTED;
    }
    manager->busy = true;
    while (manager->order_count > 0u)
        plugin_unload_slot(manager, manager->load_order[manager->order_count - 1u]);
    manager->busy = false;
    return BREAK_PLUGIN_OK;
}

BreakPluginStatus break_plugin_destroy(BreakPluginManager *manager) {
    BreakPluginStatus status;
    if (!manager) return BREAK_PLUGIN_INVALID;
    if (manager->busy) return BREAK_PLUGIN_REJECTED;
    for (u32 i = 0u; i < manager->capacity; i++) {
        if (manager->slots[i].used && manager->slots[i].references != 0u)
            return BREAK_PLUGIN_REJECTED;
    }
    status = break_plugin_unload_all(manager);
    if (status != BREAK_PLUGIN_OK) return status;
    free(manager->load_order);
    free(manager->slots);
    free(manager);
    return BREAK_PLUGIN_OK;
}
