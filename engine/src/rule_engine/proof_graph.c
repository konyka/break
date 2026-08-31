#include "re_internal.h"
#include <string.h>

/* Shared proof graph (Tasks 14 + B2). The design notes live with the structs
 * in re_internal.h; the consult/insert glue sits in backward.c because serving
 * a cached result must wire the same invalidation subscription a fresh run
 * gets, and the premise capture is installed by the dispatch wrapper there.
 * The graph never fails a query: allocation failure while caching skips the
 * cache and the caller falls back to an uncached run. */

/* FNV-1a 64 over a byte range; never dereferences a NULL/empty range. */
static uint64_t fingerprint_bytes(uint64_t hash, const void *data, size_t size) {
    const unsigned char *bytes = (const unsigned char *)data;
    size_t index;
    for (index = 0u; index < size; ++index) {
        hash ^= bytes[index];
        hash *= UINT64_C(1099511628211);
    }
    return hash;
}

/* Typed value fingerprint for premise equality (B2). Hashing the observed
 * value instead of a mutation counter keeps cloned transaction stores
 * comparable (the commit swaps entry arrays wholesale) and lets an
 * absent->assert->retract round trip keep a cached entry valid exactly when
 * the derivation would observe the same value again. */
uint64_t re_value_fingerprint(const re_value_t *value) {
    uint64_t hash = UINT64_C(1469598103934665603); /* FNV-1a 64 offset basis */
    uint64_t bits;
    unsigned char type_byte;
    if (value == NULL) return hash;
    type_byte = (unsigned char)value->type;
    hash = fingerprint_bytes(hash, &type_byte, 1u);
    switch (value->type) {
    case RE_VALUE_BOOL: {
        unsigned char flag = (unsigned char)(value->as.boolean != 0);
        return fingerprint_bytes(hash, &flag, 1u);
    }
    case RE_VALUE_INT64:
        bits = (uint64_t)value->as.int64_value;
        return fingerprint_bytes(hash, &bits, sizeof(bits));
    case RE_VALUE_DOUBLE:
        memcpy(&bits, &value->as.double_value, sizeof(bits));
        return fingerprint_bytes(hash, &bits, sizeof(bits));
    case RE_VALUE_STRING:
        return fingerprint_bytes(hash, value->as.string.data, value->as.string.size);
    default:
        return hash;
    }
}

void re_premise_set_destroy(const re_allocator_impl_t *allocator, re_premise_set_t *set) {
    size_t index;
    if (set == NULL) return;
    for (index = 0u; index < set->count; ++index)
        re_free(allocator, set->items[index].path);
    re_free(allocator, set->items);
    memset(set, 0, sizeof(*set));
}

re_status_t re_premise_set_record(const re_allocator_impl_t *allocator, re_premise_set_t *set,
                                  re_string_t path, int present, uint64_t fingerprint) {
    re_proof_graph_premise_t *grown;
    size_t index;
    if (set == NULL || (path.data == NULL && path.size != 0u)) return RE_STATUS_INVALID_ARGUMENT;
    if (set->opaque) return RE_STATUS_OK;
    /* Deduped by path; the first observation of a run wins (facts cannot
     * mutate mid-run, so a second read would observe the same value). */
    for (index = 0u; index < set->count; ++index)
        if (set->items[index].path_size == path.size &&
            (path.size == 0u || memcmp(set->items[index].path, path.data, path.size) == 0))
            return RE_STATUS_OK;
    if (set->count == RE_PROOF_GRAPH_MAX_PREMISES) {
        /* Past the cap the set can no longer prove survival: fall back to
         * the coarse generation check for the resulting entry. */
        set->opaque = 1;
        return RE_STATUS_OK;
    }
    if (set->count + 1u < set->count || set->count + 1u > (size_t)-1 / sizeof(*grown))
        return RE_STATUS_LIMIT;
    grown = re_realloc(allocator, set->items, (set->count + 1u) * sizeof(*grown));
    if (grown == NULL) return RE_STATUS_OUT_OF_MEMORY;
    set->items = grown;
    memset(&set->items[set->count], 0, sizeof(*grown));
    if (re_copy_string(allocator, path, &set->items[set->count].path) != RE_STATUS_OK)
        return RE_STATUS_OUT_OF_MEMORY;
    set->items[set->count].path_size = path.size;
    set->items[set->count].present = present;
    set->items[set->count].fingerprint = fingerprint;
    ++set->count;
    return RE_STATUS_OK;
}

re_status_t re_premise_set_merge(const re_allocator_impl_t *allocator, re_premise_set_t *target,
                                 const re_premise_set_t *source) {
    size_t index;
    if (target == NULL || source == NULL) return RE_STATUS_INVALID_ARGUMENT;
    if (source->opaque) target->opaque = 1;
    if (target->opaque) return RE_STATUS_OK;
    for (index = 0u; index < source->count; ++index) {
        re_status_t status = re_premise_set_record(allocator, target,
            (re_string_t){source->items[index].path, source->items[index].path_size},
            source->items[index].present, source->items[index].fingerprint);
        if (status != RE_STATUS_OK) return status;
    }
    return RE_STATUS_OK;
}

static void entry_reset(re_proof_graph_t *graph, re_proof_graph_entry_t *entry) {
    size_t index;
    re_free(&graph->allocator, entry->goal);
    for (index = 0u; index < entry->proof_count; ++index)
        re_proof_destroy(entry->proofs[index]);
    re_free(&graph->allocator, entry->proofs);
    for (index = 0u; index < entry->node_count; ++index)
        re_free(&graph->allocator, entry->nodes[index].rule_name);
    re_free(&graph->allocator, entry->nodes);
    re_premise_set_destroy(&graph->allocator, &entry->premises);
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

/* B2 per-premise re-validation: one premise holds when the fact resolves
 * exactly as the producing run observed it - same presence, and for present
 * facts the same value fingerprint. An absent-recorded premise holds while
 * the path still resolves to nothing (a retract-after-assert round trip is
 * invisible to the derivation, mirroring upstream's valid justification). */
static int premise_holds(const re_proof_graph_premise_t *premise, const re_facts_t *facts) {
    re_value_t current;
    if (re_facts_resolve(facts, (re_string_t){premise->path, premise->path_size},
                         &current) != RE_STATUS_OK)
        return !premise->present;
    return premise->present != 0 &&
        re_value_fingerprint(&current) == premise->fingerprint;
}

static int entry_premises_hold(const re_proof_graph_entry_t *entry, const re_facts_t *facts) {
    size_t index;
    /* Opaque entries (untracked reads) cannot prove survival. */
    if (entry->premises.opaque) return 0;
    for (index = 0u; index < entry->premises.count; ++index)
        if (!premise_holds(&entry->premises.items[index], facts)) return 0;
    return 1;
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
            /* The facts moved since the entry was stored. B2: re-validate per
             * premise instead of dropping on the serial alone - a mutation of
             * facts the derivation never read (an unrelated insert/update, or
             * a retract/insert round trip restoring the observed value) leaves
             * the entry valid, and its generation refreshes onto the fast
             * path. A premise flip unlinks the node (upstream lookup_by_key
             * filters invalid nodes) and counts an invalidation. */
            if (!entry_premises_hold(entry, facts)) {
                entry_remove(graph, index);
                ++graph->misses;
                ++graph->invalidations;
                return RE_STATUS_NOT_FOUND;
            }
            entry->generation = facts->mutation_serial;
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
                                 re_proof_t *const *proofs, size_t proof_count,
                                 const re_premise_set_t *premises) {
    re_proof_graph_entry_t *entry;
    size_t index;
    if (graph->count == RE_PROOF_GRAPH_CAPACITY) {
        /* Documented clear-all eviction: a full table is flushed rather than
         * picking victims, keeping the replacement policy trivial. */
        graph->evictions += (uint64_t)graph->count;
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
        entry->nodes = re_alloc(&graph->allocator, proof_count * sizeof(*entry->nodes));
        if (entry->nodes == NULL) { entry_reset(graph, entry); return RE_STATUS_OUT_OF_MEMORY; }
        memset(entry->nodes, 0, proof_count * sizeof(*entry->nodes));
    }
    for (index = 0u; index < proof_count; ++index) {
        if (re_proof_clone(&graph->allocator, proofs[index], &entry->proofs[index]) != RE_STATUS_OK) {
            entry_reset(graph, entry);
            return RE_STATUS_OUT_OF_MEMORY;
        }
        entry->proof_count = index + 1u;
        /* The graph node mirrors the derivation: the proof's trace root (the
         * rule/goal/fact name that anchored the derivation) is the node key. */
        {
            re_string_t name = {NULL, 0u};
            if (proofs[index]->node_count != 0u)
                name = (re_string_t){proofs[index]->nodes[0].rule_name,
                                     proofs[index]->nodes[0].rule_name_size};
            else if (proofs[index]->trace_count != 0u)
                name = (re_string_t){proofs[index]->trace_names[0],
                                     strlen(proofs[index]->trace_names[0])};
            if (name.data != NULL && name.size != 0u &&
                re_copy_string(&graph->allocator, name,
                               &entry->nodes[index].rule_name) != RE_STATUS_OK) {
                entry_reset(graph, entry);
                return RE_STATUS_OUT_OF_MEMORY;
            }
            entry->nodes[index].rule_name_size = name.size;
            entry->nodes[index].valid = 1;
            entry->node_count = index + 1u;
        }
    }
    /* The producing run's premise read-set becomes the entry's justification
     * premise keys (a NULL set stores as empty). */
    if (premises != NULL) {
        entry->premises.opaque = premises->opaque;
        for (index = 0u; index < premises->count; ++index) {
            const re_proof_graph_premise_t *premise = &premises->items[index];
            re_proof_graph_premise_t *grown;
            char *path = NULL;
            if (re_copy_string(&graph->allocator,
                               (re_string_t){premise->path, premise->path_size},
                               &path) != RE_STATUS_OK) {
                entry_reset(graph, entry);
                return RE_STATUS_OUT_OF_MEMORY;
            }
            grown = re_realloc(&graph->allocator, entry->premises.items,
                               (index + 1u) * sizeof(*grown));
            if (grown == NULL) {
                re_free(&graph->allocator, path);
                entry_reset(graph, entry);
                return RE_STATUS_OUT_OF_MEMORY;
            }
            entry->premises.items = grown;
            entry->premises.items[index].path = path;
            entry->premises.items[index].path_size = premise->path_size;
            entry->premises.items[index].present = premise->present;
            entry->premises.items[index].fingerprint = premise->fingerprint;
            entry->premises.count = index + 1u;
        }
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
    ++graph->stores;
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

re_status_t re_engine_proof_graph_stats_v2(const re_engine_t *engine,
                                           re_proof_graph_stats_t *out_stats) {
    const re_proof_graph_t *graph;
    if (engine == NULL || out_stats == NULL) return RE_STATUS_INVALID_ARGUMENT;
    if (out_stats->struct_size < (uint32_t)sizeof(*out_stats))
        return RE_STATUS_INVALID_ARGUMENT;
    graph = engine->proof_graph;
    out_stats->hits = graph != NULL ? graph->hits : 0u;
    out_stats->misses = graph != NULL ? graph->misses : 0u;
    out_stats->invalidations = graph != NULL ? graph->invalidations : 0u;
    out_stats->stores = graph != NULL ? graph->stores : 0u;
    out_stats->evictions = graph != NULL ? graph->evictions : 0u;
    return RE_STATUS_OK;
}
