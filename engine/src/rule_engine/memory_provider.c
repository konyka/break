#include "re_internal.h"
#include <string.h>

typedef struct memory_entry_t {
    char *key;
    re_value_t value;
    char *string;
    uint64_t expires;
    int active;
} memory_entry_t;

typedef struct memory_state_t {
    re_allocator_impl_t allocator;
    memory_entry_t *entries;
    size_t count;
    size_t max_keys;
    size_t max_key_bytes;
    size_t max_value_bytes;
    re_state_clock_fn_t clock;
    void *clock_context;
} memory_state_t;

static uint64_t memory_now(const memory_state_t *state) {
    return state->clock == NULL ? 0u : state->clock(state->clock_context);
}

static int add_u64(uint64_t left, uint64_t right, uint64_t *out) {
    if (right > UINT64_MAX - left) return 0;
    *out = left + right;
    return 1;
}

static size_t value_bytes(const re_value_t *value) {
    return value->type == RE_VALUE_STRING ? value->as.string.size : sizeof(*value);
}

static int same_key(const memory_entry_t *entry, re_string_t key) {
    return entry->active && entry->key != NULL && strlen(entry->key) == key.size &&
           (key.size == 0u || memcmp(entry->key, key.data, key.size) == 0);
}

static int valid_value_type(re_value_type_t type) {
    return type == RE_VALUE_BOOL || type == RE_VALUE_INT64 || type == RE_VALUE_DOUBLE ||
           type == RE_VALUE_STRING || type == RE_VALUE_NULL || type == RE_VALUE_UNKNOWN;
}

static void clear_entry(memory_state_t *state, memory_entry_t *entry) {
    re_free(&state->allocator, entry->key);
    re_free(&state->allocator, entry->string);
    memset(entry, 0, sizeof(*entry));
}

static memory_entry_t *find_entry(memory_state_t *state, re_string_t key) {
    size_t i;
    for (i = 0u; i < state->count; ++i) {
        if (same_key(&state->entries[i], key)) return &state->entries[i];
    }
    return NULL;
}

static int expired(memory_state_t *state, memory_entry_t *entry) {
    if (!entry->active || entry->expires == 0u || memory_now(state) < entry->expires) return 0;
    clear_entry(state, entry);
    return 1;
}

static re_status_t copy_value(memory_state_t *state, const re_value_t *source,
                              re_value_t *target, char **string) {
    *target = *source;
    *string = NULL;
    if (source->type != RE_VALUE_STRING) return RE_STATUS_OK;
    if (source->as.string.size != 0u && source->as.string.data == NULL) return RE_STATUS_INVALID_ARGUMENT;
    *string = re_alloc(&state->allocator, source->as.string.size + 1u);
    if (*string == NULL) return RE_STATUS_OUT_OF_MEMORY;
    if (source->as.string.size != 0u) memcpy(*string, source->as.string.data, source->as.string.size);
    (*string)[source->as.string.size] = '\0';
    target->as.string.data = *string;
    return RE_STATUS_OK;
}

static re_status_t memory_put(re_state_provider_t *provider, re_string_t key,
                              const re_value_t *value, uint64_t ttl, void *context) {
    memory_state_t *state = context;
    memory_entry_t *entry;
    char *new_key = NULL;
    char *new_string = NULL;
    re_value_t new_value;
    re_status_t status;
    if (key.data == NULL || key.size == 0u || key.size > state->max_key_bytes ||
        value == NULL || value_bytes(value) > state->max_value_bytes) return RE_STATUS_LIMIT;
    entry = find_entry(state, key);
    if (entry != NULL) {
        status = copy_value(state, value, &new_value, &new_string);
        if (status != RE_STATUS_OK) return status;
        {
            uint64_t expires = 0u;
            if (ttl != 0u && !add_u64(memory_now(state), ttl, &expires)) {
                re_free(&state->allocator, new_string);
                return RE_STATUS_LIMIT;
            }
            re_free(&state->allocator, entry->string);
            entry->value = new_value; entry->string = new_string; entry->expires = expires;
        }
        return RE_STATUS_OK;
    }
    entry = NULL;
    {
        size_t index;
        for (index = 0u; index < state->count; ++index) {
            if (!state->entries[index].active) { entry = &state->entries[index]; break; }
        }
    }
    if (entry == NULL && state->count >= state->max_keys) return RE_STATUS_LIMIT;
    new_key = re_alloc(&state->allocator, key.size + 1u);
    if (new_key == NULL) return RE_STATUS_OUT_OF_MEMORY;
    memcpy(new_key, key.data, key.size); new_key[key.size] = '\0';
    status = copy_value(state, value, &new_value, &new_string);
    if (status != RE_STATUS_OK) { re_free(&state->allocator, new_key); return status; }
    if (entry == NULL) entry = &state->entries[state->count++];
    entry->key = new_key; entry->value = new_value; entry->string = new_string;
    if (ttl != 0u && !add_u64(memory_now(state), ttl, &entry->expires)) {
        re_free(&state->allocator, new_key); re_free(&state->allocator, new_string); --state->count;
        return RE_STATUS_LIMIT;
    }
    if (ttl == 0u) entry->expires = 0u;
    entry->active = 1;
    (void)provider;
    return RE_STATUS_OK;
}

static re_status_t memory_get(re_state_provider_t *provider, re_string_t key,
                              re_value_t *out, void *context) {
    memory_state_t *state = context;
    memory_entry_t *entry = find_entry(state, key);
    (void)provider;
    if (entry == NULL || expired(state, entry)) return RE_STATUS_NOT_FOUND;
    *out = entry->value;
    return RE_STATUS_OK;
}

static re_status_t memory_set(re_state_provider_t *provider, re_string_t key,
                              const re_value_t *value, void *context) {
    return memory_put(provider, key, value, 0u, context);
}

static re_status_t memory_delete(re_state_provider_t *provider, re_string_t key, void *context) {
    memory_state_t *state = context;
    memory_entry_t *entry = find_entry(state, key);
    (void)provider;
    if (entry == NULL || expired(state, entry)) return RE_STATUS_NOT_FOUND;
    clear_entry(state, entry);
    return RE_STATUS_OK;
}

static re_status_t memory_ttl(re_state_provider_t *provider, re_string_t key,
                              uint64_t *out, void *context) {
    memory_state_t *state = context;
    memory_entry_t *entry = find_entry(state, key);
    uint64_t now;
    (void)provider;
    if (entry == NULL || expired(state, entry)) return RE_STATUS_NOT_FOUND;
    if (entry->expires == 0u) { *out = 0u; return RE_STATUS_OK; }
    now = memory_now(state); *out = entry->expires > now ? entry->expires - now : 0u;
    return RE_STATUS_OK;
}

static void memory_release(void *context) {
    memory_state_t *state = context;
    size_t i;
    for (i = 0u; i < state->count; ++i) clear_entry(state, &state->entries[i]);
    re_free(&state->allocator, state->entries);
    re_free(&state->allocator, state);
}

typedef struct memory_snapshot_context_t { re_allocator_impl_t allocator; } memory_snapshot_context_t;
static void memory_snapshot_release(void *context, const uint8_t *data, size_t size) {
    memory_snapshot_context_t *release_context = context;
    (void)size;
    re_free(&release_context->allocator, (void *)data);
    re_free(&release_context->allocator, release_context);
}

re_status_t re_memory_provider_snapshot(re_state_provider_t *provider, re_snapshot_t *out) {
    memory_state_t *state = provider == NULL ? NULL : provider->implementation;
    size_t i, size = 16u, index = 16u;
    uint8_t *data;
    memory_snapshot_context_t *context;
    if (state == NULL || out == NULL || out->struct_size < sizeof(*out)) return RE_STATUS_INVALID_ARGUMENT;
    for (i = 0u; i < state->count; ++i) if (state->entries[i].active)
        size += 8u + 8u + 8u + 4u + strlen(state->entries[i].key) + value_bytes(&state->entries[i].value);
    data = re_alloc(&state->allocator, size);
    context = data == NULL ? NULL : re_alloc(&state->allocator, sizeof(*context));
    if (data == NULL || context == NULL) { re_free(&state->allocator, data); re_free(&state->allocator, context); return RE_STATUS_OUT_OF_MEMORY; }
    memset(data, 0, 16u); memcpy(data, "REMSNAP1", 8u);
    { uint64_t count = 0u; for (i = 0u; i < state->count; ++i) if (state->entries[i].active) ++count; memcpy(data + 8u, &count, 8u); }
    for (i = 0u; i < state->count; ++i) {
        memory_entry_t *entry = &state->entries[i]; uint64_t key_size, value_size;
        if (!entry->active) continue;
        key_size = strlen(entry->key); value_size = value_bytes(&entry->value);
        memcpy(data + index, &key_size, 8u); index += 8u; memcpy(data + index, &value_size, 8u); index += 8u;
        { uint64_t now = memory_now(state); uint64_t remaining = entry->expires == 0u ? 0u :
              (entry->expires > now ? entry->expires - now : 0u); memcpy(data + index, &remaining, 8u); index += 8u; }
        memcpy(data + index, &entry->value.type, 4u); index += 4u;
        memcpy(data + index, entry->key, key_size); index += key_size;
        if (entry->value.type == RE_VALUE_STRING) memcpy(data + index, entry->value.as.string.data, value_size);
        else memcpy(data + index, &entry->value, value_size);
        index += value_size;
    }
    context->allocator = state->allocator; memset(out, 0, sizeof(*out)); out->struct_size = sizeof(*out);
    out->format_version = 1u; out->data = data; out->size = size; out->release = memory_snapshot_release; out->release_context = context;
    return RE_STATUS_OK;
}

re_status_t re_memory_provider_restore(re_state_provider_t *provider, const re_snapshot_t *snapshot) {
    memory_state_t *state = provider == NULL ? NULL : provider->implementation;
    size_t index = 16u, item, count; memory_entry_t *staged; memory_state_t temp; re_state_provider_t temp_provider;
    if (state == NULL || snapshot == NULL || snapshot->format_version != 1u || snapshot->data == NULL ||
        snapshot->size < 16u || memcmp(snapshot->data, "REMSNAP1", 8u) != 0) return RE_STATUS_INVALID_ARGUMENT;
    { uint64_t stored; memcpy(&stored, snapshot->data + 8u, 8u); if (stored > state->max_keys) return RE_STATUS_LIMIT; count = (size_t)stored; }
    staged = re_alloc(&state->allocator, state->max_keys * sizeof(*staged));
    if (staged == NULL) return RE_STATUS_OUT_OF_MEMORY;
    memset(staged, 0, state->max_keys * sizeof(*staged));
    temp = *state; temp.entries = staged; temp.count = 0u; memset(&temp_provider, 0, sizeof(temp_provider));
    temp_provider.implementation = &temp;
    for (item = 0u; item < count; ++item) {
        uint64_t key_size, value_size, expires; re_value_t value; re_string_t key;
        if (snapshot->size - index < 28u) goto invalid;
        memcpy(&key_size, snapshot->data + index, 8u); index += 8u; memcpy(&value_size, snapshot->data + index, 8u); index += 8u;
        memcpy(&expires, snapshot->data + index, 8u); index += 8u; memcpy(&value.type, snapshot->data + index, 4u); index += 4u;
        if (key_size == 0u || key_size > state->max_key_bytes || value_size > state->max_value_bytes || key_size > snapshot->size - index) goto invalid;
        key.data = (const char *)snapshot->data + index; key.size = (size_t)key_size; index += key_size;
        if (value_size > snapshot->size - index || !valid_value_type(value.type)) goto invalid;
        if (value.type == RE_VALUE_STRING) { value.as.string.data = (const char *)snapshot->data + index; value.as.string.size = (size_t)value_size; }
        else { if (value_size != sizeof(value)) goto invalid; memcpy(&value, snapshot->data + index, sizeof(value)); }
        if (memory_put(&temp_provider, key, &value, expires, &temp) != RE_STATUS_OK) goto invalid;
        index += value_size;
    }
    if (index != snapshot->size) goto invalid;
    for (item = 0u; item < state->count; ++item) clear_entry(state, &state->entries[item]);
    re_free(&state->allocator, state->entries); state->entries = staged; state->count = temp.count; return RE_STATUS_OK;
invalid:
    for (item = 0u; item < state->max_keys; ++item) clear_entry(state, &staged[item]);
    re_free(&state->allocator, staged); return RE_STATUS_INVALID_ARGUMENT;
}

re_status_t re_state_provider_create_memory(re_engine_t *engine, const re_memory_provider_options_t *options, re_state_provider_t **out_provider) { return re_memory_provider_init(engine, options, out_provider); }
re_status_t re_state_provider_update(re_state_provider_t *provider, re_string_t key, const re_value_t *value, uint64_t ttl_ms) { return re_state_provider_put(provider, key, value, ttl_ms); }
re_status_t re_state_provider_snapshot(re_state_provider_t *provider, re_snapshot_t *out_snapshot) { return re_memory_provider_snapshot(provider, out_snapshot); }
re_status_t re_state_provider_restore(re_state_provider_t *provider, const re_snapshot_t *snapshot) { return re_memory_provider_restore(provider, snapshot); }

re_status_t re_memory_provider_init(re_engine_t *engine,
                                    const re_memory_provider_options_t *options,
                                    re_state_provider_t **out_provider) {
    memory_state_t *state;
    re_state_provider_t *provider;
    if (engine == NULL || options == NULL || out_provider == NULL ||
        options->struct_size < sizeof(*options) || options->abi_version != 1u ||
        options->max_keys == 0u || options->max_key_bytes == 0u || options->max_value_bytes == 0u) return RE_STATUS_INVALID_ARGUMENT;
    *out_provider = NULL;
    state = re_alloc(&engine->allocator, sizeof(*state));
    provider = state == NULL ? NULL : re_alloc(&engine->allocator, sizeof(*provider));
    if (state == NULL || provider == NULL) { re_free(&engine->allocator, state); re_free(&engine->allocator, provider); return RE_STATUS_OUT_OF_MEMORY; }
    memset(state, 0, sizeof(*state)); state->allocator = engine->allocator;
    state->max_keys = options->max_keys; state->max_key_bytes = options->max_key_bytes;
    state->max_value_bytes = options->max_value_bytes; state->clock = options->clock;
    state->clock_context = options->clock_context;
    state->entries = re_alloc(&state->allocator, state->max_keys * sizeof(*state->entries));
    if (state->entries == NULL) { re_free(&state->allocator, provider); re_free(&state->allocator, state); return RE_STATUS_OUT_OF_MEMORY; }
    memset(state->entries, 0, state->max_keys * sizeof(*state->entries));
    memset(provider, 0, sizeof(*provider)); provider->allocator = engine->allocator;
    provider->implementation = state; provider->descriptor = (re_state_provider_descriptor_t){
        sizeof(provider->descriptor), 1u, memory_get, memory_set, memory_release,
        state, memory_put, memory_delete, memory_ttl};
    *out_provider = provider;
    return RE_STATUS_OK;
}
