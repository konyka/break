#include "re_internal.h"
#include <string.h>

static int same_name(re_string_t name, const re_fact_entry_t *entry) {
    return name.size == entry->name_size && memcmp(name.data, entry->name, name.size) == 0;
}

re_facts_t *re_facts_create(const re_allocator_t *allocator, const re_limits_t *limits) {
    re_allocator_impl_t selected;
    re_facts_t *facts;
    re_allocator_init(&selected, allocator);
    if (selected.api.alloc == NULL || selected.api.realloc == NULL || selected.api.free == NULL) return NULL;
    facts = re_alloc(&selected, sizeof(*facts));
    if (facts == NULL) return NULL;
    facts->allocator = selected; facts->limits = limits != NULL ? *limits : re_default_limits();
    facts->entries = NULL; facts->count = 0u; facts->capacity = 0u;
    facts->running = 0; facts->destroy_requested = 0;
    return facts;
}

void re_facts_destroy(re_facts_t *facts) {
    size_t index;
    if (facts == NULL) return;
    if (facts->running) { facts->destroy_requested = 1; return; }
    for (index = 0u; index < facts->count; ++index) {
        re_free(&facts->allocator, facts->entries[index].name);
        re_free(&facts->allocator, facts->entries[index].string_data);
    }
    re_free(&facts->allocator, facts->entries);
    re_free(&facts->allocator, facts);
}

re_status_t re_facts_set(re_facts_t *facts, re_string_t name, const re_value_t *value) {
    size_t index; re_fact_entry_t replacement; char *name_copy = NULL; char *string_copy = NULL;
    if (facts == NULL || value == NULL || name.data == NULL || name.size == 0u) return RE_STATUS_INVALID_ARGUMENT;
    if (facts->limits.max_facts != 0u && facts->count >= facts->limits.max_facts) {
        for (index = 0u; index < facts->count; ++index) if (same_name(name, &facts->entries[index])) break;
        if (index == facts->count) return RE_STATUS_LIMIT;
    }
    if (value->type == RE_VALUE_STRING) {
        re_status_t status = re_copy_string(&facts->allocator, value->as.string, &string_copy);
        if (status != RE_STATUS_OK) return status;
    } else if (value->type < RE_VALUE_NONE || value->type > RE_VALUE_STRING) return RE_STATUS_INVALID_ARGUMENT;
    for (index = 0u; index < facts->count; ++index) if (same_name(name, &facts->entries[index])) break;
    if (index == facts->count) {
        if (facts->count == facts->capacity) {
            size_t capacity;
            if (facts->capacity != 0u && facts->capacity > (size_t)-1 / 2u) {
                re_free(&facts->allocator, string_copy);
                return RE_STATUS_LIMIT;
            }
            capacity = facts->capacity == 0u ? 8u : facts->capacity * 2u;
            if (capacity > (size_t)-1 / sizeof(*facts->entries)) {
                re_free(&facts->allocator, string_copy); return RE_STATUS_LIMIT;
            }
            re_fact_entry_t *grown = re_realloc(&facts->allocator, facts->entries, capacity * sizeof(*grown));
            if (grown == NULL) { re_free(&facts->allocator, string_copy); return RE_STATUS_OUT_OF_MEMORY; }
            facts->entries = grown; facts->capacity = capacity;
        }
        { re_status_t status = re_copy_string(&facts->allocator, name, &name_copy);
          if (status != RE_STATUS_OK) { re_free(&facts->allocator, string_copy); return status; } }
        facts->entries[index].name = name_copy; facts->entries[index].name_size = name.size; facts->count++;
    } else re_free(&facts->allocator, facts->entries[index].string_data);
    replacement.value = *value; replacement.string_data = string_copy;
    if (replacement.value.type == RE_VALUE_BOOL)
        replacement.value.as.boolean = replacement.value.as.boolean != 0;
    if (value->type == RE_VALUE_STRING) {
        replacement.value.as.string.data = string_copy;
        replacement.value.as.string.size = value->as.string.size;
    }
    replacement.name = facts->entries[index].name; replacement.name_size = facts->entries[index].name_size;
    facts->entries[index] = replacement;
    return RE_STATUS_OK;
}

re_status_t re_facts_resolve(const re_facts_t *facts, re_string_t name, re_value_t *out) {
    size_t index; const char *dot;
    if (facts == NULL || out == NULL || name.data == NULL) return RE_STATUS_INVALID_ARGUMENT;
    for (index = 0u; index < facts->count; ++index) if (same_name(name, &facts->entries[index])) { *out = facts->entries[index].value; return RE_STATUS_OK; }
    dot = memchr(name.data, '.', name.size);
    if (dot != NULL) {
        re_string_t prefix = {name.data, (size_t)(dot - name.data)};
        for (index = 0u; index < facts->count; ++index) if (same_name(prefix, &facts->entries[index])) return RE_STATUS_NOT_FOUND;
    }
    return RE_STATUS_NOT_FOUND;
}

re_status_t re_facts_get(const re_facts_t *facts, re_string_t name, re_value_t *out_value) {
    return re_facts_resolve(facts, name, out_value);
}
