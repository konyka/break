#include "re_internal.h"
#include <stdio.h>
#include <string.h>

#define RE_VALUE_MAX_DEPTH 64u

static size_t value_depth(const re_value_handle_t *value) {
    size_t depth = 0u;
    while (value != NULL) {
        ++depth;
        if (depth > RE_VALUE_MAX_DEPTH) return depth;
        value = value->count == 0u ? NULL : value->members[0].child;
    }
    return depth;
}

static re_value_handle_t *value_new(const re_allocator_impl_t *allocator, int kind) {
    re_value_handle_t *value = re_alloc(allocator, sizeof(*value));
    if (value == NULL) return NULL;
    value->allocator = *allocator;
    value->kind = kind;
    value->members = NULL;
    value->count = 0u;
    value->capacity = 0u;
    return value;
}

static void value_free(const re_allocator_impl_t *allocator, re_value_handle_t *value) {
    size_t i;
    if (value == NULL) return;
    for (i = 0u; i < value->count; ++i) {
        re_free(allocator, value->members[i].key);
        value_free(allocator, value->members[i].child);
    }
    re_free(allocator, value->members);
    re_free(allocator, value);
}

static re_status_t value_copy(const re_allocator_impl_t *allocator,
                              const re_value_handle_t *source,
                              re_value_handle_t **out) {
    size_t i;
    re_value_handle_t *copy;
    if (source == NULL || out == NULL) return RE_STATUS_INVALID_ARGUMENT;
    copy = value_new(allocator, source->kind);
    if (copy == NULL) return RE_STATUS_OUT_OF_MEMORY;
    for (i = 0u; i < source->count; ++i) {
        re_value_member_t *member;
        if (copy->count == copy->capacity) {
            size_t capacity = copy->capacity == 0u ? 4u : copy->capacity * 2u;
            member = re_realloc(allocator, copy->members, capacity * sizeof(*member));
            if (member == NULL) { value_free(allocator, copy); return RE_STATUS_OUT_OF_MEMORY; }
            copy->members = member;
            copy->capacity = capacity;
        }
        member = &copy->members[copy->count++];
        memset(member, 0, sizeof(*member));
        if (re_copy_string(allocator, (re_string_t){source->members[i].key,
                                                    source->members[i].key_size}, &member->key) != RE_STATUS_OK) {
            value_free(allocator, copy); return RE_STATUS_OUT_OF_MEMORY;
        }
        member->key_size = source->members[i].key_size;
        member->scalar = source->members[i].scalar;
        if (source->members[i].child != NULL &&
            value_copy(allocator, source->members[i].child, &member->child) != RE_STATUS_OK) {
            value_free(allocator, copy); return RE_STATUS_OUT_OF_MEMORY;
        }
    }
    *out = copy;
    return RE_STATUS_OK;
}

static re_status_t value_add(re_value_handle_t *value, re_string_t key,
                             const re_value_t *scalar, const re_value_handle_t *child) {
    re_value_member_t *member;
    if (value == NULL || key.data == NULL || key.size == 0u ||
        (scalar == NULL && child == NULL) || (scalar != NULL && child != NULL))
        return RE_STATUS_INVALID_ARGUMENT;
    if (key.size > 256u || value->count >= 1024u) return RE_STATUS_LIMIT;
    if (child != NULL && value_depth(child) > RE_VALUE_MAX_DEPTH) return RE_STATUS_LIMIT;
    if (value->count == value->capacity) {
        size_t capacity = value->capacity == 0u ? 4u : value->capacity * 2u;
        member = re_realloc(&value->allocator, value->members, capacity * sizeof(*member));
        if (member == NULL) return RE_STATUS_OUT_OF_MEMORY;
        value->members = member; value->capacity = capacity;
    }
    member = &value->members[value->count++];
    memset(member, 0, sizeof(*member));
    if (re_copy_string(&value->allocator, key, &member->key) != RE_STATUS_OK) {
        --value->count; return RE_STATUS_OUT_OF_MEMORY;
    }
    member->key_size = key.size;
    if (scalar != NULL) member->scalar = *scalar;
    else if (value_copy(&value->allocator, child, &member->child) != RE_STATUS_OK) {
        re_free(&value->allocator, member->key); --value->count; return RE_STATUS_OUT_OF_MEMORY;
    }
    return RE_STATUS_OK;
}

re_status_t re_value_create_struct(re_facts_t *facts, re_value_handle_t **out_value) {
    return re_value_create_object(facts, out_value);
}
re_status_t re_value_create_object(re_facts_t *facts, re_value_handle_t **out_value) {
    if (facts == NULL || out_value == NULL) return RE_STATUS_INVALID_ARGUMENT;
    *out_value = value_new(&facts->allocator, 1);
    return *out_value == NULL ? RE_STATUS_OUT_OF_MEMORY : RE_STATUS_OK;
}
re_status_t re_value_create_array(re_facts_t *facts, re_value_handle_t **out_value) {
    if (facts == NULL || out_value == NULL) return RE_STATUS_INVALID_ARGUMENT;
    *out_value = value_new(&facts->allocator, 2);
    return *out_value == NULL ? RE_STATUS_OUT_OF_MEMORY : RE_STATUS_OK;
}
re_status_t re_value_object_set(re_value_handle_t *object, re_string_t key, const re_value_t *value) {
    return object == NULL || object->kind != 1 ? RE_STATUS_INVALID_ARGUMENT : value_add(object, key, value, NULL);
}
re_status_t re_value_object_set_value(re_value_handle_t *object, re_string_t key, const re_value_handle_t *value) {
    return object == NULL || object->kind != 1 ? RE_STATUS_INVALID_ARGUMENT : value_add(object, key, NULL, value);
}
re_status_t re_value_array_append(re_value_handle_t *array, const re_value_t *value) {
    char key[24];
    int size;
    if (array == NULL || array->kind != 2) return RE_STATUS_INVALID_ARGUMENT;
    size = sprintf(key, "%lu", (unsigned long)array->count);
    return value_add(array, (re_string_t){key, (size_t)size}, value, NULL);
}
re_status_t re_value_array_append_value(re_value_handle_t *array, const re_value_handle_t *value) {
    char key[24];
    int size;
    if (array == NULL || array->kind != 2) return RE_STATUS_INVALID_ARGUMENT;
    size = sprintf(key, "%lu", (unsigned long)array->count);
    return value_add(array, (re_string_t){key, (size_t)size}, NULL, value);
}
void re_value_destroy(re_value_handle_t *value) {
    if (value != NULL) value_free(&value->allocator, value);
}

re_status_t re_facts_set_value(re_facts_t *facts, re_string_t name, const re_value_handle_t *value) {
    size_t index;
    int was_existing;
    re_value_handle_t *copy = NULL;
    re_status_t status;
    if (facts == NULL || value == NULL) return RE_STATUS_INVALID_ARGUMENT;
    if (facts->transaction != NULL)
        return re_facts_set_value(facts->transaction->staged, name, value);
    for (index = 0u; index < facts->count; ++index)
        if (facts->entries[index].active && facts->entries[index].name_size == name.size &&
            memcmp(facts->entries[index].name, name.data, name.size) == 0) break;
    was_existing = index < facts->count;
    status = value_copy(&facts->allocator, value, &copy);
    if (status != RE_STATUS_OK) return status;
    status = re_facts_set_impl(facts, name, &(re_value_t){RE_VALUE_NONE, {0}}, 0);
    if (status != RE_STATUS_OK) { value_free(&facts->allocator, copy); return status; }
    for (index = 0u; index < facts->count; ++index)
        if (facts->entries[index].name_size == name.size && memcmp(facts->entries[index].name, name.data, name.size) == 0) break;
    value_free(&facts->allocator, facts->entries[index].structured);
    facts->entries[index].structured = copy;
    return re_facts_notify(facts, was_existing ? RE_FACT_UPDATE : RE_FACT_INSERT, index);
}

re_status_t re_facts_append_value(re_facts_t *facts, re_string_t name, const re_value_t *value) {
    size_t index;
    re_value_handle_t *array = NULL;
    re_status_t status;
    if (facts == NULL || value == NULL) return RE_STATUS_INVALID_ARGUMENT;
    if (facts->transaction != NULL) return re_facts_append_value(facts->transaction->staged, name, value);
    for (index = 0u; index < facts->count; ++index)
        if (facts->entries[index].active && facts->entries[index].name_size == name.size &&
            memcmp(facts->entries[index].name, name.data, name.size) == 0) break;
    if (index == facts->count || facts->entries[index].structured == NULL) {
        status = re_value_create_array(facts, &array);
        if (status != RE_STATUS_OK) return status;
    } else {
        status = value_copy(&facts->allocator, facts->entries[index].structured, &array);
        if (status != RE_STATUS_OK) return status;
    }
    status = re_value_array_append(array, value);
    if (status == RE_STATUS_OK) status = re_facts_set_value(facts, name, array);
    re_value_destroy(array);
    return status;
}

static const re_value_member_t *find_member(const re_value_handle_t *value, re_string_t key) {
    size_t i;
    for (i = 0u; i < value->count; ++i)
        if (value->members[i].key_size == key.size && memcmp(value->members[i].key, key.data, key.size) == 0)
            return &value->members[i];
    return NULL;
}
re_status_t re_facts_contains_value(const re_facts_t *facts, re_string_t path,
                                    const re_value_t *needle, int *matched) {
    size_t i;
    const re_value_handle_t *array = NULL;
    if (facts == NULL || needle == NULL || matched == NULL) return RE_STATUS_INVALID_ARGUMENT;
    if (facts->transaction != NULL) facts = facts->transaction->staged;
    for (i = 0u; i < facts->count; ++i)
        if (facts->entries[i].active && facts->entries[i].name_size == path.size &&
            memcmp(facts->entries[i].name, path.data, path.size) == 0) {
            array = facts->entries[i].structured;
            break;
        }
    if (array == NULL || array->kind != 2) return RE_STATUS_INVALID_ARGUMENT;
    *matched = 0;
    for (i = 0u; i < array->count; ++i)
        if (array->members[i].child == NULL && re_value_equal_typed(&array->members[i].scalar, needle)) {
            *matched = 1;
            break;
        }
    return RE_STATUS_OK;
}
re_status_t re_facts_get_path(const re_facts_t *facts, re_string_t path, re_value_t *out) {
    size_t i = 0u, start = 0u, root_size;
    size_t root_index;
    const re_value_handle_t *current;
    const re_value_member_t *member;
    if (facts != NULL && facts->transaction != NULL) facts = facts->transaction->staged;
    if (re_facts_get(facts, path, out) == RE_STATUS_OK) return RE_STATUS_OK;
    while (i < path.size && path.data[i] != '.') ++i;
    if (i == path.size) return RE_STATUS_NOT_FOUND;
    root_size = i;
    if (re_facts_get(facts, (re_string_t){path.data, root_size}, out) != RE_STATUS_OK) return RE_STATUS_NOT_FOUND;
    current = NULL;
    for (root_index = 0u; root_index < facts->count; ++root_index)
        if (facts->entries[root_index].name_size == root_size && memcmp(facts->entries[root_index].name, path.data, root_size) == 0) {
            current = facts->entries[root_index].structured;
            break;
        }
    for (start = root_size + 1u; start <= path.size; ) {
        size_t end = start;
        while (end < path.size && path.data[end] != '.') ++end;
        if (current == NULL) return RE_STATUS_NOT_FOUND;
        member = find_member(current, (re_string_t){path.data + start, end - start});
        if (member == NULL) return RE_STATUS_NOT_FOUND;
        if (end == path.size) { if (member->child != NULL) return RE_STATUS_NOT_FOUND; *out = member->scalar; return RE_STATUS_OK; }
        current = member->child; start = end + 1u;
    }
    return RE_STATUS_NOT_FOUND;
}

re_status_t re_facts_get_structured_path(const re_facts_t *facts, re_string_t path,
                                         const re_value_handle_t **out) {
    size_t i = 0u, start, root_size, root_index;
    const re_value_handle_t *current = NULL;
    const re_value_member_t *member;
    if (facts == NULL || out == NULL || path.data == NULL || path.size == 0u) return RE_STATUS_INVALID_ARGUMENT;
    if (facts->transaction != NULL) facts = facts->transaction->staged;
    for (root_index = 0u; root_index < facts->count; ++root_index)
        if (facts->entries[root_index].active && facts->entries[root_index].name_size == path.size &&
            memcmp(facts->entries[root_index].name, path.data, path.size) == 0) {
            current = facts->entries[root_index].structured;
            if (current == NULL) return RE_STATUS_INVALID_ARGUMENT;
            *out = current;
            return RE_STATUS_OK;
        }
    while (i < path.size && path.data[i] != '.') ++i;
    if (i == path.size) return RE_STATUS_NOT_FOUND;
    root_size = i;
    for (root_index = 0u; root_index < facts->count; ++root_index)
        if (facts->entries[root_index].active && facts->entries[root_index].name_size == root_size &&
            memcmp(facts->entries[root_index].name, path.data, root_size) == 0) {
            current = facts->entries[root_index].structured;
            break;
        }
    if (current == NULL) return RE_STATUS_NOT_FOUND;
    for (start = root_size + 1u; start < path.size; ) {
        size_t end = start;
        while (end < path.size && path.data[end] != '.') ++end;
        member = find_member(current, (re_string_t){path.data + start, end - start});
        if (member == NULL || member->child == NULL) return RE_STATUS_NOT_FOUND;
        current = member->child;
        start = end == path.size ? path.size : end + 1u;
    }
    *out = current;
    return RE_STATUS_OK;
}
