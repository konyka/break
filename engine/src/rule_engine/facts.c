#include "re_internal.h"
#include <string.h>

static int same_name(re_string_t name, const re_fact_entry_t *entry) {
    return entry->active && name.size == entry->name_size &&
        memcmp(name.data, entry->name, name.size) == 0;
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
    facts->mutation_serial = 0u;
    facts->running = 0; facts->mutation_allowed = 0; facts->read_allowed = 0; facts->destroy_requested = 0; facts->notifying = 0; facts->run_transaction_allowed = 0;
    facts->subscriptions = NULL;
    facts->retired_subscriptions = NULL;
    facts->transaction = NULL;
    facts->retired_transaction = NULL; facts->rete_network = NULL;
    facts->tms = NULL;
    return facts;
}

void re_facts_destroy(re_facts_t *facts) {
    size_t index;
    if (facts == NULL) return;
    if (facts->running || facts->notifying) { facts->destroy_requested = 1; return; }
    if (facts->transaction != NULL) {
        re_fact_txn_t *transaction = facts->transaction;
        re_facts_rollback(transaction);
        transaction->facts = NULL;
    }
    if (facts->rete_network != NULL) {
        if (facts->rete_network->engine_owned) re_rete_network_destroy_internal(facts->rete_network);
        else re_rete_network_detach_facts(facts->rete_network);
        facts->rete_network = NULL;
    }
    {
        re_fact_txn_t *transaction = facts->retired_transaction;
        while (transaction != NULL) {
            /* Retired handles remain valid tombstones after their store dies. */
            transaction->inactive = 1;
            transaction->facts = NULL;
            transaction = transaction->next_retired;
        }
    }
    while (facts->subscriptions != NULL) {
        re_subscription_t *subscription = facts->subscriptions;
        facts->subscriptions = subscription->next;
        subscription->facts = NULL;
        re_free(&facts->allocator, subscription);
    }
    while (facts->retired_subscriptions != NULL) {
        re_subscription_t *subscription = facts->retired_subscriptions;
        facts->retired_subscriptions = subscription->next;
        subscription->facts = NULL;
        re_free(&facts->allocator, subscription);
    }
    for (index = 0u; index < facts->count; ++index) {
        re_free(&facts->allocator, facts->entries[index].name);
        re_free(&facts->allocator, facts->entries[index].string_data);
        re_value_destroy(facts->entries[index].structured);
    }
    re_free(&facts->allocator, facts->entries);
    re_tms_destroy(facts->tms);
    /* Retired transaction records intentionally outlive facts so stale opaque
     * handles remain safe to query as inactive tombstones. */
    re_free(&facts->allocator, facts);
}

/* Wholesale working-memory reset: drops every fact entry and all TMS
 * justifications without per-fact notifications. An attached rete network is
 * torn down exactly like in re_facts_destroy so no stale fact ids survive;
 * user subscriptions stay registered and observe later asserts. */
re_status_t re_facts_clear_all(re_facts_t *facts) {
    size_t index;
    if (facts == NULL) return RE_STATUS_INVALID_ARGUMENT;
    if (facts->running || facts->notifying || facts->transaction != NULL) return RE_STATUS_BUSY;
    if (facts->rete_network != NULL) {
        if (facts->rete_network->engine_owned) re_rete_network_destroy_internal(facts->rete_network);
        else re_rete_network_detach_facts(facts->rete_network);
        facts->rete_network = NULL;
    }
    for (index = 0u; index < facts->count; ++index) {
        re_free(&facts->allocator, facts->entries[index].name);
        re_free(&facts->allocator, facts->entries[index].string_data);
        re_value_destroy(facts->entries[index].structured);
    }
    re_free(&facts->allocator, facts->entries);
    facts->entries = NULL;
    facts->count = 0u;
    facts->capacity = 0u;
    re_tms_destroy(facts->tms);
    facts->tms = NULL;
    ++facts->mutation_serial;
    return RE_STATUS_OK;
}

re_status_t re_facts_set_impl(re_facts_t *facts, re_string_t name,
                              const re_value_t *value, int emit_event) {
    size_t index; re_fact_entry_t replacement; char *name_copy = NULL; char *string_copy = NULL;
    int was_existing;
    if (facts == NULL || value == NULL || name.data == NULL || name.size == 0u) return RE_STATUS_INVALID_ARGUMENT;
    if (facts->notifying) return RE_STATUS_BUSY;
    if (facts->transaction != NULL)
        return re_facts_set_impl(facts->transaction->staged, name, value, emit_event);
    if (facts->limits.max_facts != 0u && facts->count >= facts->limits.max_facts) {
        for (index = 0u; index < facts->count; ++index) if (same_name(name, &facts->entries[index])) break;
        if (index == facts->count) return RE_STATUS_LIMIT;
    }
    if (value->type == RE_VALUE_STRING) {
        re_status_t status = re_copy_string(&facts->allocator, value->as.string, &string_copy);
        if (status != RE_STATUS_OK) return status;
    } else if (value->type < RE_VALUE_NONE || value->type > RE_VALUE_UNKNOWN) return RE_STATUS_INVALID_ARGUMENT;
    for (index = 0u; index < facts->count; ++index) if (same_name(name, &facts->entries[index])) break;
    was_existing = index < facts->count;
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
        facts->entries[index].name = name_copy; facts->entries[index].name_size = name.size;
        facts->entries[index].generation = 0u;
        facts->entries[index].active = 1;
        facts->entries[index].logical = 0;
        facts->entries[index].structured = NULL;
        facts->entries[index].string_data = NULL;
        facts->count++;
    } else {
        re_free(&facts->allocator, facts->entries[index].string_data);
        re_value_destroy(facts->entries[index].structured);
        facts->entries[index].structured = NULL;
    }
    replacement.value = *value; replacement.string_data = string_copy;
    if (replacement.value.type == RE_VALUE_BOOL)
        replacement.value.as.boolean = replacement.value.as.boolean != 0;
    if (value->type == RE_VALUE_STRING) {
        replacement.value.as.string.data = string_copy;
        replacement.value.as.string.size = value->as.string.size;
    }
    replacement.name = facts->entries[index].name; replacement.name_size = facts->entries[index].name_size;
    replacement.structured = NULL;
    replacement.generation = facts->entries[index].generation;
    replacement.active = facts->entries[index].active;
    replacement.logical = facts->entries[index].logical;
    facts->entries[index] = replacement;
    facts->mutation_serial++;
    if (emit_event && was_existing) return re_facts_notify(facts, RE_FACT_UPDATE, index);
    return RE_STATUS_OK;
}

re_status_t re_facts_set(re_facts_t *facts, re_string_t name, const re_value_t *value) {
    return re_facts_set_impl(facts, name, value, 1);
}

re_status_t re_facts_resolve(const re_facts_t *facts, re_string_t name, re_value_t *out) {
    size_t index; const char *dot;
    if (facts == NULL || out == NULL || name.data == NULL) return RE_STATUS_INVALID_ARGUMENT;
    for (index = 0u; index < facts->count; ++index) if (facts->entries[index].active && same_name(name, &facts->entries[index])) { *out = facts->entries[index].value; return RE_STATUS_OK; }
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

re_status_t re_facts_notify(re_facts_t *facts, re_fact_change_kind_t kind, size_t index) {
    re_subscription_t *subscription = facts->subscriptions;
    re_fact_event_t event;
    int was_notifying = facts->notifying;
    event.struct_size = sizeof(event);
    event.kind = kind;
    event.id.slot = (uint64_t)index;
    event.id.generation = facts->entries[index].generation;
    event.name.data = facts->entries[index].name;
    event.name.size = facts->entries[index].name_size;
    event.value = facts->entries[index].value;
    facts->notifying = 1;
    while (subscription != NULL) {
        re_subscription_t *next = subscription->next;
        if (subscription->active) {
            re_status_t status = subscription->callback(facts, &event, subscription->context);
            if (status != RE_STATUS_OK) {
                if (facts->rete_network != NULL) {
                    facts->rete_network->invalid = 1;
                    facts->rete_network->activation_count = 0u;
                }
                facts->notifying = was_notifying;
                return status;
            }
        }
        subscription = next;
    }
    facts->notifying = was_notifying;
    return RE_STATUS_OK;
}

re_status_t re_facts_insert(re_facts_t *facts, re_string_t name,
                            const re_value_t *value, re_fact_id_t *out_id) {
    size_t index;
    re_status_t status;
    if (facts == NULL || out_id == NULL) return RE_STATUS_INVALID_ARGUMENT;
    if (facts->notifying) return RE_STATUS_BUSY;
    if (facts->transaction != NULL)
        return re_facts_insert(facts->transaction->staged, name, value, out_id);
    for (index = 0u; index < facts->count; ++index) {
        if (same_name(name, &facts->entries[index])) {
            status = re_facts_set(facts, name, value);
            if (status != RE_STATUS_OK) return status;
            out_id->slot = (uint64_t)index;
            out_id->generation = facts->entries[index].generation;
            return RE_STATUS_OK;
        }
    }
    status = re_facts_set(facts, name, value);
    if (status != RE_STATUS_OK) return status;
    for (index = 0u; index < facts->count; ++index)
        if (same_name(name, &facts->entries[index])) break;
    facts->entries[index].generation += 1u;
    facts->entries[index].active = 1;
    out_id->slot = (uint64_t)index;
    out_id->generation = facts->entries[index].generation;
    return re_facts_notify(facts, RE_FACT_INSERT, index);
}

re_status_t re_facts_update(re_facts_t *facts, re_fact_id_t id, const re_value_t *value) {
    if (facts != NULL && facts->notifying) return RE_STATUS_BUSY;
    if (facts != NULL && facts->transaction != NULL)
        return re_facts_update(facts->transaction->staged, id, value);
    if (facts == NULL || value == NULL || id.slot >= facts->count ||
        !facts->entries[id.slot].active || facts->entries[id.slot].generation != id.generation)
        return RE_STATUS_NOT_FOUND;
    {
        re_status_t status = re_facts_set(facts, (re_string_t){facts->entries[id.slot].name, facts->entries[id.slot].name_size}, value);
        return status;
    }
}

int re_facts_is_logical(const re_facts_t *facts, re_fact_id_t id) {
    return facts != NULL && id.slot < facts->count && facts->entries[id.slot].active &&
        facts->entries[id.slot].generation == id.generation && facts->entries[id.slot].logical;
}

re_status_t re_facts_insert_logical(re_facts_t *facts, re_string_t name, const re_value_t *value,
                                    re_string_t rule, const re_fact_id_t *premises, size_t count,
                                    re_fact_id_t *out_id) {
    re_status_t status;
    size_t index;
    if (facts == NULL || value == NULL || out_id == NULL || rule.data == NULL || rule.size == 0u ||
        (count != 0u && premises == NULL)) return RE_STATUS_INVALID_ARGUMENT;
    if (facts->transaction != NULL)
        return re_facts_insert_logical(facts->transaction->staged, name, value, rule, premises, count, out_id);
    for (index = 0u; index < facts->count; ++index)
        if (facts->entries[index].active && facts->entries[index].name_size == name.size &&
            memcmp(facts->entries[index].name, name.data, name.size) == 0 &&
            !facts->entries[index].logical) {
            status = re_facts_insert(facts, name, value, out_id);
            return status;
        }
    status = re_facts_insert(facts, name, value, out_id);
    if (status != RE_STATUS_OK) return status;
    status = re_facts_justification_add(facts, *out_id, rule, premises, count);
    if (status != RE_STATUS_OK) { re_facts_retract(facts, *out_id); return status; }
    return RE_STATUS_OK;
}

re_status_t re_facts_provenance_get(const re_facts_t *facts, re_fact_id_t id, re_fact_provenance_t *out) {
    size_t i;
    if (facts == NULL || out == NULL || !re_facts_is_logical(facts, id)) return RE_STATUS_NOT_FOUND;
    for (i = 0u; i < facts->tms->count; ++i) if (facts->tms->items[i].derived.slot == id.slot && facts->tms->items[i].derived.generation == id.generation) {
        out->producer_rule.data = facts->tms->items[i].producer_rule;
        out->producer_rule.size = facts->tms->items[i].producer_rule_size;
        out->premises = facts->tms->items[i].premises; out->premise_count = facts->tms->items[i].premise_count;
        return RE_STATUS_OK;
    }
    return RE_STATUS_NOT_FOUND;
}

re_status_t re_facts_retract(re_facts_t *facts, re_fact_id_t id) {
    char *name;
    size_t name_size;
    re_value_t value;
    if (facts != NULL && facts->notifying) return RE_STATUS_BUSY;
    if (facts != NULL && facts->transaction != NULL)
        return re_facts_retract(facts->transaction->staged, id);
    if (facts == NULL || id.slot >= facts->count || !facts->entries[id.slot].active ||
        facts->entries[id.slot].generation != id.generation) return RE_STATUS_NOT_FOUND;
    name = facts->entries[id.slot].name;
    name_size = facts->entries[id.slot].name_size;
    value = facts->entries[id.slot].value;
    facts->entries[id.slot].name = NULL;
    facts->entries[id.slot].name_size = 0u;
    facts->entries[id.slot].string_data = NULL;
    facts->entries[id.slot].structured = NULL;
    facts->entries[id.slot].active = 0;
    facts->entries[id.slot].name = name;
    facts->entries[id.slot].name_size = name_size;
    facts->entries[id.slot].value = value;
    re_tms_remove_derived(facts, id);
    re_tms_remove_premise(facts, id);
    return re_facts_notify(facts, RE_FACT_RETRACT, (size_t)id.slot);
}

re_status_t re_facts_subscribe(re_facts_t *facts, re_fact_event_fn_t callback,
                               void *context, re_subscription_t **out_subscription) {
    re_subscription_t *subscription;
    if (facts == NULL || callback == NULL || out_subscription == NULL) return RE_STATUS_INVALID_ARGUMENT;
    subscription = re_alloc(&facts->allocator, sizeof(*subscription));
    if (subscription == NULL) return RE_STATUS_OUT_OF_MEMORY;
    subscription->facts = facts;
    subscription->callback = callback;
    subscription->context = context;
    subscription->next = facts->subscriptions;
    subscription->active = 1;
    facts->subscriptions = subscription;
    *out_subscription = subscription;
    return RE_STATUS_OK;
}

void re_subscription_destroy(re_subscription_t *subscription) {
    re_subscription_t **link;
    if (subscription == NULL || subscription->facts == NULL) return;
    link = &subscription->facts->subscriptions;
    while (*link != NULL && *link != subscription) link = &(*link)->next;
    if (subscription->facts->notifying) {
        subscription->active = 0;
        if (*link == subscription) {
            *link = subscription->next;
            subscription->next = subscription->facts->retired_subscriptions;
            subscription->facts->retired_subscriptions = subscription;
        }
        return;
    }
    if (*link == subscription) *link = subscription->next;
    re_free(&subscription->facts->allocator, subscription);
}
