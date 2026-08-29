#include "re_internal.h"
#include <string.h>

/* Shared proof graph (Task 14). The design notes live with the struct in
 * re_internal.h; the consult/insert glue sits in backward.c because serving a
 * cached result must wire the same invalidation subscription a fresh run gets.
 * The graph never fails a query: allocation failure while caching skips the
 * cache and the caller falls back to an uncached run. */

static void entry_reset(re_proof_graph_t *graph, re_proof_graph_entry_t *entry) {
    size_t index;
    re_free(&graph->allocator, entry->goal);
    for (index = 0u; index < entry->proof_count; ++index)
        re_proof_destroy(entry->proofs[index]);
    re_free(&graph->allocator, entry->proofs);
    memset(entry, 0, sizeof(*entry));
}

/* Entries are kept compact, so removal shifts the tail down. */
static void entry_remove(re_proof_graph_t *graph, size_t index) {
    entry_reset(graph, &graph->entries[index]);
    if (index + 1u < graph->count)
        memmove(&graph->entries[index], &graph->entries[index + 1u],
                (graph->count - index - 1u) * sizeof(*graph->entries));
    --graph->count;
    memset(&graph->entries[graph->count], 0, sizeof(*graph->entries));
}

static re_status_t clone_value(const re_allocator_impl_t *allocator, const re_value_t *source,
                               re_value_t *target, char **string_data) {
    *target = *source;
    *string_data = NULL;
    if (source->type != RE_VALUE_STRING) return RE_STATUS_OK;
    if (re_copy_string(allocator, source->as.string, string_data) != RE_STATUS_OK)
        return RE_STATUS_OUT_OF_MEMORY;
    target->as.string.data = *string_data;
    return RE_STATUS_OK;
}

/* Deep copy of the make_proof representation (backward.c): bindings with
 * owned name/string storage, trace name strings, proof nodes, and edges. The
 * clone carries the target allocator so the public re_proof_destroy releases
 * it. Arrays are zeroed up front and counts set before filling, so a partial
 * failure destroys cleanly (re_free is NULL-safe). */
re_status_t re_proof_clone(const re_allocator_impl_t *allocator, const re_proof_t *source,
                           re_proof_t **out) {
    re_proof_t *copy;
    size_t index;
    if (allocator == NULL || source == NULL || out == NULL) return RE_STATUS_INVALID_ARGUMENT;
    *out = NULL;
    copy = re_alloc(allocator, sizeof(*copy));
    if (copy == NULL) return RE_STATUS_OUT_OF_MEMORY;
    memset(copy, 0, sizeof(*copy));
    copy->allocator = *allocator;
    if (source->binding_count != 0u) {
        copy->bindings = re_alloc(allocator, source->binding_count * sizeof(*copy->bindings));
        if (copy->bindings == NULL) { re_proof_destroy(copy); return RE_STATUS_OUT_OF_MEMORY; }
        memset(copy->bindings, 0, source->binding_count * sizeof(*copy->bindings));
    }
    copy->binding_count = source->binding_count;
    for (index = 0u; index < source->binding_count; ++index) {
        const re_query_binding_impl_t *binding = &source->bindings[index];
        copy->bindings[index].name_size = binding->name_size;
        if (re_copy_string(allocator, (re_string_t){binding->name, binding->name_size},
                           &copy->bindings[index].name) != RE_STATUS_OK ||
            clone_value(allocator, &binding->value, &copy->bindings[index].value,
                        &copy->bindings[index].string_data) != RE_STATUS_OK) {
            re_proof_destroy(copy);
            return RE_STATUS_OUT_OF_MEMORY;
        }
    }
    if (source->trace_count != 0u) {
        copy->trace_names = re_alloc(allocator, source->trace_count * sizeof(*copy->trace_names));
        if (copy->trace_names == NULL) { re_proof_destroy(copy); return RE_STATUS_OUT_OF_MEMORY; }
        memset(copy->trace_names, 0, source->trace_count * sizeof(*copy->trace_names));
        copy->nodes = re_alloc(allocator, source->trace_count * sizeof(*copy->nodes));
        if (copy->nodes == NULL) { re_proof_destroy(copy); return RE_STATUS_OUT_OF_MEMORY; }
        memset(copy->nodes, 0, source->trace_count * sizeof(*copy->nodes));
    }
    copy->trace_count = source->trace_count;
    copy->node_count = source->node_count;
    for (index = 0u; index < source->trace_count; ++index) {
        size_t size = strlen(source->trace_names[index]);
        if (re_copy_string(allocator, (re_string_t){source->trace_names[index], size},
                           &copy->trace_names[index]) != RE_STATUS_OK) {
            re_proof_destroy(copy);
            return RE_STATUS_OUT_OF_MEMORY;
        }
    }
    for (index = 0u; index < source->node_count; ++index) {
        copy->nodes[index].rule_name_size = source->nodes[index].rule_name_size;
        if (re_copy_string(allocator,
                           (re_string_t){source->nodes[index].rule_name,
                                         source->nodes[index].rule_name_size},
                           &copy->nodes[index].rule_name) != RE_STATUS_OK) {
            re_proof_destroy(copy);
            return RE_STATUS_OUT_OF_MEMORY;
        }
    }
    if (source->edge_count != 0u) {
        copy->edges = re_alloc(allocator, source->edge_count * sizeof(*copy->edges));
        if (copy->edges == NULL) { re_proof_destroy(copy); return RE_STATUS_OUT_OF_MEMORY; }
        memcpy(copy->edges, source->edges, source->edge_count * sizeof(*copy->edges));
    }
    copy->edge_count = source->edge_count;
    *out = copy;
    return RE_STATUS_OK;
}

void re_proof_graph_ensure(re_engine_t *engine) {
    re_proof_graph_t *graph;
    if (engine->proof_graph != NULL) return;
    graph = re_alloc(&engine->allocator, sizeof(*graph));
    if (graph == NULL) return;
    memset(graph, 0, sizeof(*graph));
    graph->allocator = engine->allocator;
    engine->proof_graph = graph;
}

void re_proof_graph_destroy(re_proof_graph_t *graph) {
    size_t index;
    if (graph == NULL) return;
    for (index = 0u; index < graph->count; ++index)
        entry_reset(graph, &graph->entries[index]);
    re_free(&graph->allocator, graph);
}

static int entry_matches(const re_proof_graph_entry_t *entry, const re_facts_t *facts,
                         re_string_t goal, const re_query_options_t *options,
                         uint64_t config_serial) {
    return entry->facts == facts && entry->facts_nonce == facts->nonce &&
           entry->config_serial == config_serial &&
           entry->max_depth == options->max_depth &&
           entry->max_solutions == options->max_solutions &&
           entry->strategy == options->strategy &&
           entry->goal_size == goal.size &&
           (goal.size == 0u || memcmp(entry->goal, goal.data, goal.size) == 0);
}

re_status_t re_proof_graph_lookup(re_proof_graph_t *graph, re_facts_t *facts,
                                  re_string_t goal, const re_query_options_t *options,
                                  uint64_t config_serial,
                                  const re_proof_graph_entry_t **out_entry) {
    size_t index;
    *out_entry = NULL;
    for (index = 0u; index < graph->count; ++index) {
        re_proof_graph_entry_t *entry = &graph->entries[index];
        if (!entry_matches(entry, facts, goal, options, config_serial)) continue;
        if (entry->generation != facts->mutation_serial) {
            /* Stale: the facts moved since the entry was stored. Drop it so
             * the slot is reusable; the mutation counter is the only
             * invalidation signal and covers first-asserts of previously
             * absent facts (re_facts_set_impl bumps it unconditionally). */
            entry_remove(graph, index);
            ++graph->misses;
            return RE_STATUS_NOT_FOUND;
        }
        ++graph->hits;
        *out_entry = entry;
        return RE_STATUS_OK;
    }
    ++graph->misses;
    return RE_STATUS_NOT_FOUND;
}

re_status_t re_proof_graph_store(re_proof_graph_t *graph, re_facts_t *facts,
                                 re_string_t goal, const re_query_options_t *options,
                                 uint64_t config_serial, re_query_result_t result,
                                 re_proof_t *const *proofs, size_t proof_count) {
    re_proof_graph_entry_t *entry;
    size_t index;
    if (graph->count == RE_PROOF_GRAPH_CAPACITY) {
        /* Documented clear-all eviction: a full table is flushed rather than
         * picking victims, keeping the replacement policy trivial. */
        for (index = 0u; index < graph->count; ++index)
            entry_reset(graph, &graph->entries[index]);
        graph->count = 0u;
    }
    entry = &graph->entries[graph->count];
    memset(entry, 0, sizeof(*entry));
    if (re_copy_string(&graph->allocator, goal, &entry->goal) != RE_STATUS_OK)
        return RE_STATUS_OUT_OF_MEMORY;
    if (proof_count != 0u) {
        entry->proofs = re_alloc(&graph->allocator, proof_count * sizeof(*entry->proofs));
        if (entry->proofs == NULL) { entry_reset(graph, entry); return RE_STATUS_OUT_OF_MEMORY; }
        memset(entry->proofs, 0, proof_count * sizeof(*entry->proofs));
    }
    for (index = 0u; index < proof_count; ++index) {
        if (re_proof_clone(&graph->allocator, proofs[index], &entry->proofs[index]) != RE_STATUS_OK) {
            entry_reset(graph, entry);
            return RE_STATUS_OUT_OF_MEMORY;
        }
        entry->proof_count = index + 1u;
    }
    entry->goal_size = goal.size;
    entry->facts = facts;
    entry->facts_nonce = facts->nonce;
    entry->generation = facts->mutation_serial;
    entry->config_serial = config_serial;
    entry->max_depth = options->max_depth;
    entry->max_solutions = options->max_solutions;
    entry->strategy = options->strategy;
    entry->result = result;
    ++graph->count;
    return RE_STATUS_OK;
}

re_status_t re_engine_proof_graph_stats(const re_engine_t *engine, uint64_t *out_hits,
                                        uint64_t *out_misses) {
    if (engine == NULL || out_hits == NULL || out_misses == NULL)
        return RE_STATUS_INVALID_ARGUMENT;
    /* The graph is lazy: no cacheable query yet means zeroes, not an error. */
    *out_hits = engine->proof_graph != NULL ? engine->proof_graph->hits : 0u;
    *out_misses = engine->proof_graph != NULL ? engine->proof_graph->misses : 0u;
    return RE_STATUS_OK;
}
