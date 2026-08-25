#include "re_internal.h"
#include <string.h>

#define RE_RETE_MAX_CONDITIONS 8u

static int condition_matches(const re_rete_condition_t *condition,
                             const re_fact_entry_t *entry) {
    re_value_t left = entry->value;
    return entry->active && condition->fact_name.size == entry->name_size &&
           memcmp(condition->fact_name.data, entry->name, entry->name_size) == 0 &&
           re_value_compare(&left, &condition->value, condition->compare) != 0;
}

static int collect_conditions(const re_expr_t *expr,
                              re_rete_condition_t *conditions, size_t *count) {
    if (expr == NULL) return 0;
    if (expr->kind == RE_EXPR_AND)
        return collect_conditions(expr->first, conditions, count) &&
               collect_conditions(expr->second, conditions, count);
    if (expr->kind != RE_EXPR_COMPARE || *count >= RE_RETE_MAX_CONDITIONS ||
        expr->left.kind != RE_OPERAND_FACT || expr->right.kind != RE_OPERAND_LITERAL)
        return 0;
    conditions[*count].fact_name.data = expr->left.fact_name;
    conditions[*count].fact_name.size = expr->left.fact_name_size;
    conditions[*count].compare = expr->compare;
    conditions[*count].value = expr->right.value;
    ++*count;
    return 1;
}

static re_status_t create_rule_conditions(re_facts_t *facts, const re_rule_t *rule,
                                          const re_allocator_t *allocator,
                                          re_rete_network_t **out_network) {
    re_rete_condition_t conditions[RE_RETE_MAX_CONDITIONS];
    size_t count = 0u;
    size_t i;
    if (rule == NULL || !collect_conditions(rule->condition, conditions, &count) || count < 2u)
        return RE_STATUS_NOT_SUPPORTED;
    for (i = 0u; i < count; ++i) {
        size_t fact_index;
        int exact = 0;
        for (fact_index = 0u; fact_index < facts->count; ++fact_index)
            if (facts->entries[fact_index].active && facts->entries[fact_index].name_size == conditions[i].fact_name.size &&
                memcmp(facts->entries[fact_index].name, conditions[i].fact_name.data, conditions[i].fact_name.size) == 0) exact = 1;
        if (!exact) return RE_STATUS_NOT_SUPPORTED;
    }
    return re_rete_network_create_conditions(facts, conditions, count, allocator, out_network);
}

int re_rete_conditions_from_rule(const re_rule_t *rule,
                                 re_rete_condition_t conditions[2]) {
    size_t count = 0u;
    if (rule == NULL || conditions == NULL || !collect_conditions(rule->condition, conditions, &count)) return 0;
    return count == 2u;
}

static re_status_t reserve(re_rete_network_t *network, size_t needed) {
    size_t capacity = network->activation_capacity;
    re_rete_activation_t *grown;
    if (needed <= capacity) return RE_STATUS_OK;
    if (capacity == 0u) capacity = 8u;
    while (capacity < needed) {
        if (capacity > (size_t)-1 / 2u) return RE_STATUS_LIMIT;
        capacity *= 2u;
    }
    if (capacity > (size_t)-1 / sizeof(*grown)) return RE_STATUS_LIMIT;
    grown = re_realloc(&network->allocator, network->activations, capacity * sizeof(*grown));
    if (grown == NULL) return RE_STATUS_OUT_OF_MEMORY;
    network->activations = grown;
    network->activation_capacity = capacity;
    return RE_STATUS_OK;
}

static re_status_t rebuild_walk(re_rete_network_t *network, size_t depth,
                                size_t *slots, size_t *needed) {
    size_t index;
    if (depth == network->condition_count) {
        if (*needed == (size_t)-1) return RE_STATUS_LIMIT;
        ++*needed;
        return RE_STATUS_OK;
    }
    for (index = 0u; index < network->facts->count; ++index) {
        size_t prior;
        int duplicate = 0;
        for (prior = 0u; prior < depth; ++prior) if (slots[prior] == index) duplicate = 1;
        if (duplicate || !condition_matches(&network->conditions[depth], &network->facts->entries[index])) continue;
        slots[depth] = index;
        if (rebuild_walk(network, depth + 1u, slots, needed) != RE_STATUS_OK) return RE_STATUS_LIMIT;
    }
    return RE_STATUS_OK;
}

static re_status_t emit_walk(re_rete_network_t *network, size_t depth,
                             size_t *slots) {
    size_t index;
    if (depth == network->condition_count) {
        re_rete_activation_t *activation;
        if (network->activation_count >= network->activation_capacity) return RE_STATUS_LIMIT;
        activation = &network->activations[network->activation_count];
        activation->left.slot = (uint64_t)slots[0];
        activation->left.generation = network->facts->entries[slots[0]].generation;
        activation->right.slot = (uint64_t)slots[1];
        activation->right.generation = network->facts->entries[slots[1]].generation;
        activation->sequence = (uint64_t)network->activation_count + 1u;
        ++network->activation_count;
        return RE_STATUS_OK;
    }
    for (index = 0u; index < network->facts->count; ++index) {
        size_t prior;
        int duplicate = 0;
        for (prior = 0u; prior < depth; ++prior) if (slots[prior] == index) duplicate = 1;
        if (duplicate || !condition_matches(&network->conditions[depth], &network->facts->entries[index])) continue;
        slots[depth] = index;
        if (emit_walk(network, depth + 1u, slots) != RE_STATUS_OK) return RE_STATUS_LIMIT;
    }
    return RE_STATUS_OK;
}

static re_status_t rebuild(re_rete_network_t *network) {
    size_t slots[RE_RETE_MAX_CONDITIONS];
    size_t needed = 0u;
    re_status_t status = rebuild_walk(network, 0u, slots, &needed);
    if (status != RE_STATUS_OK) return status;
    status = reserve(network, needed);
    if (status != RE_STATUS_OK) return status;
    network->activation_count = 0u;
    return emit_walk(network, 0u, slots);
}

static re_status_t fact_changed(re_facts_t *facts, const re_fact_event_t *event, void *context) {
    (void)facts; (void)event;
    return rebuild((re_rete_network_t *)context);
}

re_status_t re_rete_network_create_conditions(re_facts_t *facts,
                                              const re_rete_condition_t *conditions,
                                              size_t condition_count,
                                              const re_allocator_t *allocator,
                                              re_rete_network_t **out_network) {
    re_allocator_impl_t selected;
    re_rete_network_t *network;
    re_status_t status;
    if (facts == NULL || conditions == NULL || out_network == NULL || condition_count < 2u || condition_count > RE_RETE_MAX_CONDITIONS) return RE_STATUS_INVALID_ARGUMENT;
    *out_network = NULL;
    re_allocator_init(&selected, allocator);
    network = re_alloc(&selected, sizeof(*network));
    if (network == NULL) return RE_STATUS_OUT_OF_MEMORY;
    memset(network, 0, sizeof(*network));
    network->allocator = selected;
    network->facts = facts;
    network->conditions = re_alloc(&selected, condition_count * sizeof(*network->conditions));
    if (network->conditions == NULL) { re_free(&selected, network); return RE_STATUS_OUT_OF_MEMORY; }
    memcpy(network->conditions, conditions, condition_count * sizeof(*conditions));
    network->condition_count = condition_count;
    status = re_facts_subscribe(facts, fact_changed, network, &network->subscription);
    if (status == RE_STATUS_OK) status = rebuild(network);
    if (status != RE_STATUS_OK) { re_subscription_destroy(network->subscription); re_free(&selected, network->conditions); re_free(&selected, network->activations); re_free(&selected, network); return status; }
    *out_network = network;
    return RE_STATUS_OK;
}

re_status_t re_rete_network_create(re_facts_t *facts, const re_rete_condition_t conditions[2], const re_allocator_t *allocator, re_rete_network_t **out_network) {
    return re_rete_network_create_conditions(facts, conditions, 2u, allocator, out_network);
}

re_status_t re_rete_network_create_rule(re_facts_t *facts, const re_rule_t *rule,
                                         const re_allocator_t *allocator,
                                         re_rete_network_t **out_network) {
    return create_rule_conditions(facts, rule, allocator, out_network);
}

void re_rete_network_destroy_internal(re_rete_network_t *network) {
    if (network == NULL) return;
    re_subscription_destroy(network->subscription);
    re_free(&network->allocator, network->conditions);
    re_free(&network->allocator, network->activations);
    re_free(&network->allocator, network);
}

size_t re_rete_activation_count(const re_rete_network_t *network) { return network == NULL ? 0u : network->activation_count; }
re_status_t re_rete_activation_get(const re_rete_network_t *network, size_t index, re_rete_activation_t *out) {
    if (network == NULL || out == NULL) return RE_STATUS_INVALID_ARGUMENT;
    if (index >= network->activation_count) return RE_STATUS_NOT_FOUND;
    *out = network->activations[index];
    return RE_STATUS_OK;
}
