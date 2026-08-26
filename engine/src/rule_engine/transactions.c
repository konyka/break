#include "re_internal.h"
#include <string.h>

static int structured_equal(const re_value_handle_t *left, const re_value_handle_t *right) {
    size_t index;
    if (left == NULL || right == NULL) return left == right;
    if (left->kind != right->kind || left->count != right->count) return 0;
    for (index = 0u; index < left->count; ++index) {
        const re_value_member_t *a = &left->members[index];
        const re_value_member_t *b = &right->members[index];
        if (a->key_size != b->key_size || memcmp(a->key, b->key, a->key_size) != 0) return 0;
        if (a->child != NULL || b->child != NULL) {
            if (!structured_equal(a->child, b->child)) return 0;
        } else if (a->scalar.type != b->scalar.type ||
                   (a->scalar.type == RE_VALUE_INT64 && a->scalar.as.int64_value != b->scalar.as.int64_value) ||
                   (a->scalar.type == RE_VALUE_BOOL && a->scalar.as.boolean != b->scalar.as.boolean) ||
                   (a->scalar.type == RE_VALUE_DOUBLE && a->scalar.as.double_value != b->scalar.as.double_value) ||
                   (a->scalar.type == RE_VALUE_STRING &&
                    (a->scalar.as.string.size != b->scalar.as.string.size ||
                     memcmp(a->scalar.as.string.data, b->scalar.as.string.data, a->scalar.as.string.size) != 0))) return 0;
    }
    return 1;
}

static re_status_t clone_facts(const re_facts_t *source, re_facts_t **out) {
    size_t index;
    re_facts_t *copy = re_facts_create(&source->allocator.api, &source->limits);
    if (copy == NULL) return RE_STATUS_OUT_OF_MEMORY;
    for (index = 0u; index < source->count; ++index) {
        const re_fact_entry_t *entry = &source->entries[index];
        re_status_t status = re_facts_set(copy,
            (re_string_t){entry->name, entry->name_size}, &entry->value);
        if (status != RE_STATUS_OK) { re_facts_destroy(copy); return status; }
        if (entry->structured != NULL) {
            status = re_facts_set_value(copy,
                (re_string_t){entry->name, entry->name_size}, entry->structured);
            if (status != RE_STATUS_OK) { re_facts_destroy(copy); return status; }
        }
        copy->entries[index].generation = entry->generation;
        copy->entries[index].active = entry->active;
    }
    *out = copy;
    copy->mutation_serial = source->mutation_serial;
    return RE_STATUS_OK;
}

static int scalar_changed(const re_fact_entry_t *left, const re_fact_entry_t *right) {
    if (left->value.type != right->value.type) return 1;
    switch (left->value.type) {
    case RE_VALUE_BOOL: return left->value.as.boolean != right->value.as.boolean;
    case RE_VALUE_INT64: return left->value.as.int64_value != right->value.as.int64_value;
    case RE_VALUE_DOUBLE: return left->value.as.double_value != right->value.as.double_value;
    case RE_VALUE_STRING:
        return left->value.as.string.size != right->value.as.string.size ||
            memcmp(left->value.as.string.data, right->value.as.string.data,
                   left->value.as.string.size) != 0;
    default: return 0;
    }
}

static int entry_changed(const re_fact_entry_t *left, const re_fact_entry_t *right) {
    return left->generation != right->generation || scalar_changed(left, right) ||
           !structured_equal(left->structured, right->structured);
}

static void dispatch(re_facts_t *facts, const re_fact_entry_t *entry,
                     size_t index, re_fact_change_kind_t kind) {
    size_t count = 0u, cursor = 0u;
    re_subscription_t *subscription;
    re_subscription_t **snapshot;
    char *name_copy = NULL;
    char *value_copy = NULL;
    re_fact_event_t event;
    for (subscription = facts->subscriptions; subscription != NULL; subscription = subscription->next)
        if (subscription->active) ++count;
    snapshot = count == 0u ? NULL : re_alloc(&facts->allocator, count * sizeof(*snapshot));
    if (count != 0u && snapshot == NULL) return;
    if (entry->name != NULL && re_copy_string(&facts->allocator,
            (re_string_t){entry->name, entry->name_size}, &name_copy) != RE_STATUS_OK) goto cleanup;
    if (entry->value.type == RE_VALUE_STRING && re_copy_string(&facts->allocator,
            entry->value.as.string, &value_copy) != RE_STATUS_OK) goto cleanup;
    event = (re_fact_event_t){sizeof(event), kind, {(uint64_t)index, entry->generation},
        {name_copy, entry->name_size}, entry->value};
    if (value_copy != NULL) event.value.as.string.data = value_copy;
    for (subscription = facts->subscriptions; subscription != NULL; subscription = subscription->next)
        if (subscription->active) snapshot[cursor++] = subscription;
    facts->notifying = 1;
    for (cursor = 0u; cursor < count; ++cursor) {
        if (snapshot[cursor]->active)
            snapshot[cursor]->callback(facts, &event, snapshot[cursor]->context);
    }
    facts->notifying = 0;
cleanup:
    re_free(&facts->allocator, value_copy);
    re_free(&facts->allocator, name_copy);
    re_free(&facts->allocator, snapshot);
}

static void emit_changes(re_fact_txn_t *transaction) {
    size_t index;
    re_facts_t *facts = transaction->facts;
    re_facts_t *old = transaction->original;
    {
        size_t count = facts->count > old->count ? facts->count : old->count;
        for (index = 0u; index < count; ++index) {
            int was_active = index < old->count && old->entries[index].active;
            int is_active = index < facts->count && facts->entries[index].active;
            if (was_active && !is_active) dispatch(facts, &old->entries[index], index, RE_FACT_RETRACT);
            if (!was_active && is_active) dispatch(facts, &facts->entries[index], index, RE_FACT_INSERT);
            if (was_active && is_active && entry_changed(&facts->entries[index], &old->entries[index]))
                dispatch(facts, &facts->entries[index], index, RE_FACT_UPDATE);
        }
    }
}

re_status_t re_facts_begin(re_facts_t *facts, re_fact_txn_t **out_transaction) {
    re_fact_txn_t *transaction;
    re_status_t status;
    if (facts == NULL || out_transaction == NULL) return RE_STATUS_INVALID_ARGUMENT;
    *out_transaction = NULL;
    if (facts->transaction != NULL || facts->running || facts->notifying) return RE_STATUS_BUSY;
    transaction = re_alloc(&facts->allocator, sizeof(*transaction));
    if (transaction == NULL) return RE_STATUS_OUT_OF_MEMORY;
    transaction->facts = facts; transaction->original = NULL; transaction->staged = NULL; transaction->inactive = 0;
    transaction->generation = facts->mutation_serial + 1u;
    transaction->next_retired = NULL;
    status = clone_facts(facts, &transaction->original);
    if (status == RE_STATUS_OK) status = clone_facts(facts, &transaction->staged);
    if (status != RE_STATUS_OK) {
        re_facts_destroy(transaction->original); re_facts_destroy(transaction->staged);
        re_free(&facts->allocator, transaction); return status;
    }
    facts->transaction = transaction; *out_transaction = transaction;
    return RE_STATUS_OK;
}

re_status_t re_facts_txn_set(re_fact_txn_t *txn, re_string_t name, const re_value_t *value) {
    re_status_t status;
    size_t index;
    if (txn == NULL || txn->inactive || txn->facts == NULL || txn->facts->transaction != txn)
        return RE_STATUS_INVALID_ARGUMENT;
    status = re_facts_set(txn->staged, name, value);
    if (status != RE_STATUS_OK) return status;
    for (index = 0u; index < txn->staged->count; ++index)
        if (txn->staged->entries[index].name_size == name.size &&
            memcmp(txn->staged->entries[index].name, name.data, name.size) == 0) break;
    if (index < txn->staged->count) txn->staged->entries[index].active = 1;
    return RE_STATUS_OK;
}
re_status_t re_facts_txn_insert(re_fact_txn_t *txn, re_string_t name,
                                const re_value_t *value, re_fact_id_t *out_id) {
    return txn == NULL || txn->inactive || txn->facts == NULL || txn->facts->transaction != txn ? RE_STATUS_INVALID_ARGUMENT :
        re_facts_insert(txn->staged, name, value, out_id);
}
re_status_t re_facts_txn_update(re_fact_txn_t *txn, re_fact_id_t id, const re_value_t *value) {
    return txn == NULL || txn->inactive || txn->facts == NULL || txn->facts->transaction != txn ? RE_STATUS_INVALID_ARGUMENT :
        re_facts_update(txn->staged, id, value);
}
re_status_t re_facts_txn_retract(re_fact_txn_t *txn, re_fact_id_t id) {
    return txn == NULL || txn->inactive || txn->facts == NULL || txn->facts->transaction != txn ? RE_STATUS_INVALID_ARGUMENT :
        re_facts_retract(txn->staged, id);
}
re_status_t re_facts_txn_get(const re_fact_txn_t *txn, re_string_t name, re_value_t *out) {
    return txn == NULL || txn->inactive || txn->facts == NULL || txn->facts->transaction != txn ? RE_STATUS_INVALID_ARGUMENT :
        re_facts_get(txn->staged, name, out);
}

re_status_t re_facts_commit(re_fact_txn_t *transaction) {
    re_facts_t *facts;
    re_fact_entry_t *entries;
    size_t count, capacity;
    if (transaction == NULL || transaction->inactive || transaction->facts == NULL ||
        transaction->facts->transaction != transaction) return RE_STATUS_INVALID_ARGUMENT;
    facts = transaction->facts;
    entries = facts->entries; count = facts->count; capacity = facts->capacity;
    facts->entries = transaction->staged->entries;
    facts->count = transaction->staged->count; facts->capacity = transaction->staged->capacity;
    if (transaction->staged->mutation_serial > facts->mutation_serial)
        facts->mutation_serial = transaction->staged->mutation_serial;
    transaction->staged->entries = entries;
    transaction->staged->count = count; transaction->staged->capacity = capacity;
    facts->transaction = NULL;
    facts->notifying = 1;
    transaction->inactive = 1;
    emit_changes(transaction);
    facts->notifying = 0;
    re_facts_destroy(transaction->original); re_facts_destroy(transaction->staged);
    transaction->next_retired = facts->retired_transaction;
    facts->retired_transaction = transaction;
    if (facts->destroy_requested) re_facts_destroy(facts);
    return RE_STATUS_OK;
}

void re_facts_rollback(re_fact_txn_t *transaction) {
    re_facts_t *facts;
    if (transaction == NULL || transaction->inactive || transaction->facts == NULL ||
        transaction->facts->transaction != transaction) return;
    facts = transaction->facts; facts->transaction = NULL;
    re_facts_destroy(transaction->original); re_facts_destroy(transaction->staged);
    transaction->inactive = 1;
    transaction->next_retired = facts->retired_transaction;
    facts->retired_transaction = transaction;
}
