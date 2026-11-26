#include <ecs/world_merge.h>

#include <stdlib.h>
#include <string.h>

typedef struct {
    BreakNetEntityId id;
    BreakWorldMergeConnection owner;
} Owned;

/* One accepted value waiting for the batch to finish validating. */
typedef struct {
    void *destination;
    u32 offset; /* into the staging buffer */
    u32 size;
} Pending;

struct BreakWorldMerge {
    World *authoritative;
    const BreakNetEntityMap *ids;
    u32 authoritative_key;
    BreakWorldMergeComponent components[BREAK_WORLD_MERGE_MAX_COMPONENTS];
    u32 component_count;
    u32 max_owned;
    Owned *owned;
    u32 owned_count;
    /* staging for one batch: every owned entity times every component */
    Pending *pending;
    u8 *staging;
    u8 scratch[BREAK_WORLD_MERGE_MAX_VALUE_BYTES];
    BreakWorldMergeStats stats;
};

static u32 component_size(const World *world, ComponentType component) {
    return world->component_sizes[component];
}

BreakWorldMergeResult break_world_merge_create(const BreakWorldMergeConfig *config,
                                               BreakWorldMerge **out) {
    BreakWorldMerge *merge;
    usize staging_bytes = 0u;
    if (out) *out = NULL;
    if (!config || !out || !config->authoritative || !config->ids || !config->components ||
        config->component_count == 0u ||
        config->component_count > BREAK_WORLD_MERGE_MAX_COMPONENTS || config->max_owned == 0u ||
        config->max_owned > BREAK_WORLD_MERGE_MAX_OWNED) {
        return BREAK_WORLD_MERGE_INVALID;
    }
    for (u32 i = 0u; i < config->component_count; ++i) {
        const BreakWorldMergeComponent *c = &config->components[i];
        u32 size;
        if (!c->validate || c->component >= ECS_MAX_COMPONENTS) return BREAK_WORLD_MERGE_INVALID;
        size = component_size(config->authoritative, c->component);
        if (size == 0u || size > BREAK_WORLD_MERGE_MAX_VALUE_BYTES) return BREAK_WORLD_MERGE_INVALID;
        for (u32 j = 0u; j < i; ++j) {
            if (config->components[j].component == c->component) return BREAK_WORLD_MERGE_INVALID;
        }
        staging_bytes += size;
    }
    merge = (BreakWorldMerge *)calloc(1u, sizeof(*merge));
    if (!merge) return BREAK_WORLD_MERGE_INVALID;
    merge->owned = (Owned *)calloc(config->max_owned, sizeof(*merge->owned));
    merge->pending = (Pending *)calloc((usize)config->max_owned * config->component_count,
                                       sizeof(*merge->pending));
    merge->staging = (u8 *)malloc(staging_bytes * config->max_owned);
    if (!merge->owned || !merge->pending || !merge->staging) {
        break_world_merge_destroy(merge);
        return BREAK_WORLD_MERGE_INVALID;
    }
    merge->authoritative = config->authoritative;
    merge->ids = config->ids;
    merge->authoritative_key = config->authoritative_key;
    memcpy(merge->components, config->components,
           config->component_count * sizeof(*config->components));
    merge->component_count = config->component_count;
    merge->max_owned = config->max_owned;
    *out = merge;
    return BREAK_WORLD_MERGE_OK;
}

void break_world_merge_destroy(BreakWorldMerge *merge) {
    if (!merge) return;
    free(merge->owned);
    free(merge->pending);
    free(merge->staging);
    free(merge);
}

static Owned *find_owned(const BreakWorldMerge *merge, BreakNetEntityId id) {
    for (u32 i = 0u; i < merge->owned_count; ++i) {
        if (merge->owned[i].id == id) return &merge->owned[i];
    }
    return NULL;
}

BreakWorldMergeResult break_world_merge_grant(BreakWorldMerge *merge,
                                              BreakWorldMergeConnection connection,
                                              BreakNetEntityId id) {
    Owned *existing;
    if (!merge || connection == 0u || id == 0u) return BREAK_WORLD_MERGE_INVALID;
    existing = find_owned(merge, id);
    if (existing) {
        return existing->owner == connection ? BREAK_WORLD_MERGE_OK : BREAK_WORLD_MERGE_CONFLICT;
    }
    if (merge->owned_count == merge->max_owned) return BREAK_WORLD_MERGE_OVERLOAD;
    merge->owned[merge->owned_count].id = id;
    merge->owned[merge->owned_count].owner = connection;
    merge->owned_count++;
    return BREAK_WORLD_MERGE_OK;
}

static void remove_at(BreakWorldMerge *merge, u32 index) {
    merge->owned[index] = merge->owned[merge->owned_count - 1u];
    merge->owned_count--;
}

BreakWorldMergeResult break_world_merge_revoke(BreakWorldMerge *merge, BreakNetEntityId id) {
    Owned *existing;
    if (!merge) return BREAK_WORLD_MERGE_INVALID;
    existing = find_owned(merge, id);
    if (!existing) return BREAK_WORLD_MERGE_NOT_FOUND;
    remove_at(merge, (u32)(existing - merge->owned));
    return BREAK_WORLD_MERGE_OK;
}

u32 break_world_merge_revoke_connection(BreakWorldMerge *merge,
                                        BreakWorldMergeConnection connection) {
    u32 revoked = 0u;
    if (!merge) return 0u;
    for (u32 i = 0u; i < merge->owned_count;) {
        if (merge->owned[i].owner == connection) {
            remove_at(merge, i);
            revoked++;
        } else {
            ++i;
        }
    }
    return revoked;
}

BreakWorldMergeConnection break_world_merge_owner(const BreakWorldMerge *merge,
                                                  BreakNetEntityId id) {
    const Owned *existing;
    if (!merge) return 0u;
    existing = find_owned(merge, id);
    return existing ? existing->owner : 0u;
}

/* Resolves `id` to an Entity of `world` through `map`, requiring the binding
 * to be in `world_key` and the Entity to be alive. */
static bool resolve(const BreakNetEntityMap *map, World *world, u32 world_key,
                    BreakNetEntityId id, Entity *out) {
    u32 key = 0u;
    if (break_net_entity_map_entity(map, id, &key, out) != BREAK_NET_ENTITY_OK) return false;
    return key == world_key && world_entity_exists(world, *out);
}

BreakWorldMergeResult break_world_merge_connection(BreakWorldMerge *merge,
                                                   BreakWorldMergeConnection connection,
                                                   World *inbound,
                                                   const BreakNetEntityMap *inbound_ids,
                                                   u32 inbound_key,
                                                   BreakWorldMergeReport *report) {
    BreakWorldMergeReport local;
    u32 pending_count = 0u;
    u32 staged = 0u;
    if (report) memset(report, 0, sizeof(*report));
    if (!merge || !inbound || !inbound_ids || connection == 0u ||
        inbound == merge->authoritative) {
        return BREAK_WORLD_MERGE_INVALID;
    }
    for (u32 c = 0u; c < merge->component_count; ++c) {
        ComponentType component = merge->components[c].component;
        if (component_size(inbound, component) != component_size(merge->authoritative, component)) {
            merge->stats.rejected++;
            return BREAK_WORLD_MERGE_REJECTED;
        }
    }
    memset(&local, 0, sizeof(local));
    for (u32 i = 0u; i < merge->owned_count; ++i) {
        const Owned *owned = &merge->owned[i];
        Entity from;
        Entity to;
        if (owned->owner != connection) continue;
        if (!resolve(inbound_ids, inbound, inbound_key, owned->id, &from) ||
            !resolve(merge->ids, merge->authoritative, merge->authoritative_key, owned->id, &to)) {
            local.skipped++;
            continue;
        }
        local.entities++;
        for (u32 c = 0u; c < merge->component_count; ++c) {
            const BreakWorldMergeComponent *spec = &merge->components[c];
            const void *proposed = world_get_component(inbound, from, spec->component);
            void *current = world_get_component(merge->authoritative, to, spec->component);
            u32 size = component_size(merge->authoritative, spec->component);
            BreakWorldMergeVerdict verdict;
            if (!proposed || !current) {
                local.skipped++;
                continue;
            }
            if (memcmp(proposed, current, size) == 0) {
                local.unchanged++;
                continue;
            }
            memcpy(merge->scratch, proposed, size);
            verdict = spec->validate(spec->user, connection, owned->id, spec->component, current,
                                     proposed, merge->scratch, size);
            if (verdict == BREAK_WORLD_MERGE_KEEP) {
                local.kept++;
                continue;
            }
            if (verdict != BREAK_WORLD_MERGE_ACCEPT) {
                merge->stats.rejected++;
                return BREAK_WORLD_MERGE_REJECTED;
            }
            memcpy(merge->staging + staged, merge->scratch, size);
            merge->pending[pending_count].destination = current;
            merge->pending[pending_count].offset = staged;
            merge->pending[pending_count].size = size;
            pending_count++;
            staged += size;
        }
    }
    for (u32 i = 0u; i < pending_count; ++i) {
        const Pending *p = &merge->pending[i];
        memcpy(p->destination, merge->staging + p->offset, p->size);
    }
    local.written = pending_count;
    merge->stats.merges++;
    merge->stats.written += pending_count;
    if (report) *report = local;
    return BREAK_WORLD_MERGE_OK;
}

void break_world_merge_stats(const BreakWorldMerge *merge, BreakWorldMergeStats *out) {
    if (!merge || !out) return;
    *out = merge->stats;
    out->owned = merge->owned_count;
}
