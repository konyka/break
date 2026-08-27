#include "re_internal.h"
#include <string.h>

#define RE_RETE_MAX_CONDITIONS 8u

static int matches(const re_rete_condition_t *condition, const re_fact_entry_t *entry) {
    return entry->active && condition->fact_name.size == entry->name_size &&
        memcmp(condition->fact_name.data, entry->name, entry->name_size) == 0 &&
        re_value_compare(&entry->value, &condition->value, condition->compare) != 0;
}

static int collect(const re_expr_t *expr, re_rete_condition_t *out, size_t *count) {
    if (expr == NULL) return 0;
    if (expr->kind == RE_EXPR_AND)
        return collect(expr->first, out, count) && collect(expr->second, out, count);
    if (expr->kind != RE_EXPR_COMPARE || *count >= RE_RETE_MAX_CONDITIONS ||
        expr->left.kind != RE_OPERAND_FACT || expr->right.kind != RE_OPERAND_LITERAL) return 0;
    out[*count].fact_name = (re_string_t){expr->left.fact_name, expr->left.fact_name_size};
    out[*count].compare = expr->compare;
    out[*count].value = expr->right.value;
    ++*count;
    return 1;
}

static re_status_t grow(void **memory, size_t *capacity, size_t needed, size_t item_size,
                        const re_allocator_impl_t *allocator) {
    size_t next = *capacity == 0u ? 8u : *capacity;
    void *grown;
    while (next < needed) {
        if (next > (size_t)-1 / 2u) return RE_STATUS_LIMIT;
        next *= 2u;
    }
    if (next > (size_t)-1 / item_size) return RE_STATUS_LIMIT;
    grown = re_realloc(allocator, *memory, next * item_size);
    if (grown == NULL) return RE_STATUS_OUT_OF_MEMORY;
    *memory = grown;
    *capacity = next;
    return RE_STATUS_OK;
}

static int alpha_has(const re_rete_alpha_memory_t *alpha, re_fact_id_t id) {
    size_t i;
    for (i = 0u; i < alpha->count; ++i)
        if (alpha->facts[i].slot == id.slot && alpha->facts[i].generation == id.generation) return 1;
    return 0;
}

static re_status_t alpha_change(re_rete_network_t *network, size_t index,
                                re_fact_id_t id, int present) {
    re_rete_alpha_memory_t *alpha = &network->alpha_memories[index];
    size_t i;
    if (present) {
        for (i = 0u; i < alpha->count; ++i)
            if (alpha->facts[i].slot == id.slot) {
                alpha->facts[i] = id;
                return RE_STATUS_OK;
            }
        if (alpha_has(alpha, id)) return RE_STATUS_OK;
        if (grow((void **)&alpha->facts, &alpha->capacity, alpha->count + 1u,
                 sizeof(*alpha->facts), &network->allocator) != RE_STATUS_OK) return RE_STATUS_OUT_OF_MEMORY;
        alpha->facts[alpha->count++] = id;
        return RE_STATUS_OK;
    }
    for (i = 0u; i < alpha->count; ++i)
        if (alpha->facts[i].slot == id.slot) {
            alpha->facts[i] = alpha->facts[--alpha->count];
            break;
        }
    return RE_STATUS_OK;
}

static int token_used(const re_rete_network_t *network, size_t depth, re_fact_id_t id) {
    size_t i;
    for (i = 0u; i < depth; ++i)
        if (network->lineage_scratch[i].slot == id.slot) return 1;
    return 0;
}

static uint64_t previous_sequence(const re_rete_network_t *network) {
    size_t i;
    size_t j;
    for (i = 0u; i < network->activation_count; ++i) {
        const re_rete_activation_t *activation = &network->activations[i];
        if (activation->lineage_count != network->condition_count) continue;
        for (j = 0u; j < network->condition_count; ++j)
            if (activation->lineage[j].slot != network->lineage_scratch[j].slot ||
                activation->lineage[j].generation != network->lineage_scratch[j].generation) break;
        if (j == network->condition_count) return activation->sequence;
    }
    return 0u;
}

static re_status_t build_tokens(re_rete_network_t *network) {
    size_t choices[RE_RETE_MAX_CONDITIONS] = {0u};
    size_t depth = 0u;
    for (;;) {
        if (depth == network->condition_count) {
            re_rete_token_t *token;
            size_t j;
            if (network->token_count >= network->token_capacity) return RE_STATUS_LIMIT;
            token = &network->tokens[network->token_count++];
            token->lineage_count = network->condition_count;
            token->sequence = previous_sequence(network);
            if (token->sequence == 0u) token->sequence = ++network->next_sequence;
            for (j = 0u; j < token->lineage_count; ++j) token->lineage[j] = network->lineage_scratch[j];
            --depth;
        }
        while (choices[depth] < network->alpha_memories[depth].count) {
            re_fact_id_t id = network->alpha_memories[depth].facts[choices[depth]++];
            if (token_used(network, depth, id)) continue;
            network->lineage_scratch[depth] = id;
            ++depth;
            if (depth < network->condition_count) choices[depth] = 0u;
            break;
        }
        if (depth == 0u && choices[0] == network->alpha_memories[0].count) return RE_STATUS_OK;
        if (depth < network->condition_count && choices[depth] == network->alpha_memories[depth].count) {
            choices[depth] = 0u;
            if (depth == 0u) return RE_STATUS_OK;
            --depth;
        }
    }
}

static re_status_t rebuild_tokens(re_rete_network_t *network) {
    size_t i;
    size_t needed = 1u;
    for (i = 0u; i < network->condition_count; ++i) {
        if (network->alpha_memories[i].count != 0u && needed > (size_t)-1 / network->alpha_memories[i].count) return RE_STATUS_LIMIT;
        needed *= network->alpha_memories[i].count == 0u ? 1u : network->alpha_memories[i].count;
    }
    {
        re_status_t status = grow((void **)&network->tokens, &network->token_capacity, needed,
                                   sizeof(*network->tokens), &network->allocator);
        if (status != RE_STATUS_OK) return status;
    }
    network->token_count = 0u;
    if (network->condition_count != 0u) {
        re_status_t status = build_tokens(network);
        if (status != RE_STATUS_OK) return status;
    }
    {
        re_status_t status = grow((void **)&network->activations, &network->activation_capacity,
                                  network->token_count, sizeof(*network->activations), &network->allocator);
        if (status != RE_STATUS_OK) return status;
    }
    network->activation_count = 0u;
    for (i = 0u; i < network->token_count; ++i) {
        re_rete_activation_t *activation = &network->activations[network->activation_count++];
        size_t j;
        activation->left = network->tokens[i].lineage[0];
        activation->right = network->tokens[i].lineage_count > 1u ? network->tokens[i].lineage[1] : activation->left;
        activation->sequence = network->tokens[i].sequence;
        activation->lineage_count = network->tokens[i].lineage_count;
        activation->producer_rule = network->producer_rule;
        for (j = 0u; j < activation->lineage_count; ++j) activation->lineage[j] = network->tokens[i].lineage[j];
    }
    return RE_STATUS_OK;
}

static re_status_t fact_changed(re_facts_t *facts, const re_fact_event_t *event, void *context) {
    re_rete_network_t *network = (re_rete_network_t *)context;
    size_t i;
    (void)facts;
    if (network->invalid) return RE_STATUS_OUT_OF_MEMORY;
    for (i = 0u; i < network->condition_count; ++i) {
        if (network->conditions[i].fact_name.size != event->name.size ||
            memcmp(network->conditions[i].fact_name.data, event->name.data, event->name.size) != 0) continue;
        if (event->kind == RE_FACT_RETRACT) alpha_change(network, i, event->id, 0);
        else if (alpha_change(network, i, event->id, re_value_compare(&event->value,
            &network->conditions[i].value, network->conditions[i].compare) != 0) != RE_STATUS_OK) {
            network->invalid = 1;
            network->activation_count = 0u;
            return RE_STATUS_OUT_OF_MEMORY;
        }
    }
    {
        re_status_t status = rebuild_tokens(network);
        if (status != RE_STATUS_OK) {
            network->invalid = 1;
            network->activation_count = 0u;
        }
        return status;
    }
}

static re_status_t create_rule_conditions(re_facts_t *facts, const re_rule_t *rule,
                                          const re_allocator_t *allocator,
                                          re_rete_network_t **out) {
    re_rete_condition_t conditions[RE_RETE_MAX_CONDITIONS];
    size_t count = 0u;
    if (rule == NULL || !collect(rule->condition, conditions, &count) || count < 2u) return RE_STATUS_NOT_SUPPORTED;
    return re_rete_network_create_conditions(facts, conditions, count, allocator, out);
}

re_status_t re_rete_network_create_conditions(re_facts_t *facts, const re_rete_condition_t *conditions,
                                              size_t count, const re_allocator_t *allocator,
                                              re_rete_network_t **out) {
    re_allocator_impl_t selected;
    re_rete_network_t *network;
    size_t i, j;
    if (facts == NULL || conditions == NULL || out == NULL || count < 2u || count > RE_RETE_MAX_CONDITIONS) return RE_STATUS_INVALID_ARGUMENT;
    *out = NULL; re_allocator_init(&selected, allocator);
    network = re_alloc(&selected, sizeof(*network));
    if (network == NULL) return RE_STATUS_OUT_OF_MEMORY;
    memset(network, 0, sizeof(*network)); network->allocator = selected; network->facts = facts;
    network->conditions = re_alloc(&selected, count * sizeof(*conditions));
    network->alpha_memories = re_alloc(&selected, count * sizeof(*network->alpha_memories));
    if (network->conditions == NULL || network->alpha_memories == NULL) { re_free(&selected, network->conditions); re_free(&selected, network->alpha_memories); re_free(&selected, network); return RE_STATUS_OUT_OF_MEMORY; }
    memcpy(network->conditions, conditions, count * sizeof(*conditions)); memset(network->alpha_memories, 0, count * sizeof(*network->alpha_memories)); network->condition_count = count;
    for (i = 0u; i < count; ++i) for (j = 0u; j < facts->count; ++j) if (matches(&conditions[i], &facts->entries[j])) {
        re_fact_id_t id = {(uint64_t)j, facts->entries[j].generation};
        if (alpha_change(network, i, id, 1) != RE_STATUS_OK) { re_rete_network_destroy_internal(network); return RE_STATUS_OUT_OF_MEMORY; }
    }
    {
        re_status_t status = rebuild_tokens(network);
        if (status != RE_STATUS_OK) { re_rete_network_destroy_internal(network); return status; }
    }
    {
        re_status_t status = re_facts_subscribe(facts, fact_changed, network, &network->subscription);
        if (status != RE_STATUS_OK) { re_rete_network_destroy_internal(network); return status; }
    }
    if (facts->rete_network != NULL) {
        re_rete_network_destroy_internal(network);
        return RE_STATUS_BUSY;
    }
    facts->rete_network = network;
    *out = network; return RE_STATUS_OK;
}

re_status_t re_rete_network_create(re_facts_t *facts, const re_rete_condition_t conditions[2], const re_allocator_t *allocator, re_rete_network_t **out) { return re_rete_network_create_conditions(facts, conditions, 2u, allocator, out); }
re_status_t re_rete_network_create_rule(re_facts_t *facts, const re_rule_t *rule, const re_allocator_t *allocator, re_rete_network_t **out) {
    re_status_t status = create_rule_conditions(facts, rule, allocator, out);
    if (status == RE_STATUS_OK) (*out)->producer_rule = (re_string_t){rule->name, rule->name_size};
    return status;
}
int re_rete_conditions_from_rule(const re_rule_t *rule, re_rete_condition_t conditions[2]) { size_t count = 0u; return rule != NULL && conditions != NULL && collect(rule->condition, conditions, &count) && count == 2u; }
void re_rete_network_destroy_internal(re_rete_network_t *network) { size_t i; if (network == NULL) return; if (network->facts != NULL && network->facts->rete_network == network) network->facts->rete_network = NULL; if (network->owner_engine != NULL && network->owner_engine->rete_network == network) network->owner_engine->rete_network = NULL; network->owner_engine = NULL; re_subscription_destroy(network->subscription); for (i = 0u; i < network->condition_count; ++i) re_free(&network->allocator, network->alpha_memories[i].facts); re_free(&network->allocator, network->alpha_memories); re_free(&network->allocator, network->conditions); re_free(&network->allocator, network->tokens); re_free(&network->allocator, network->activations); re_free(&network->allocator, network); }
size_t re_rete_activation_count(const re_rete_network_t *network) { return network == NULL ? 0u : network->activation_count; }
re_status_t re_rete_activation_get(const re_rete_network_t *network, size_t index, re_rete_activation_t *out) { if (network == NULL || out == NULL) return RE_STATUS_INVALID_ARGUMENT; if (index >= network->activation_count) return RE_STATUS_NOT_FOUND; *out = network->activations[index]; return RE_STATUS_OK; }
