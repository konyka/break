#include <network/break_online_aspect_replication.h>

#include <network/break_net_message.h>
#include <core/platform_thread.h>

#include <stdlib.h>
#include <string.h>

#define ASPECT_REPLICATION_HARD_MAX_CONNECTIONS 64u
#define ASPECT_REPLICATION_HARD_MAX_OBJECTS 1024u
#define ASPECT_REPLICATION_HARD_MAX_FRAGMENTS 2048u

typedef struct AspectReal {
    bool used;
    BreakOnlineHandle handle;
    BreakReplicationObject object;
    u64 record_epoch;
} AspectReal;

typedef struct AspectConnection {
    bool used;
    u64 id;
    usize default_budget;
    usize fragment_size;
} AspectConnection;

typedef struct AspectGhost {
    bool in_scope;
    bool baseline_sent;
    u64 sent_revision;
    u64 dirty_mask;
    u8 pending_leave;
} AspectGhost;

struct BreakAspectReplication {
    PlatformThreadId owner;
    BreakAspectStore *store;
    BreakSpatialIndex *index;
    BreakAspectSendFn send;
    void *send_user;
    u32 max_connections;
    u32 max_objects;
    u32 connection_count;
    usize packet_capacity;
    u32 max_fragments;
    AspectReal *objects;
    AspectConnection *connections;
    AspectGhost *ghosts;
    u8 *packet;
    BreakReplicationFragment *fragments;
    u64 next_delta_id;
};

static bool replication_owner(const BreakAspectReplication *replication)
{
    return replication && platform_thread_id_equal(replication->owner,
                                                    platform_thread_current_id());
}

static AspectGhost *ghost_at(BreakAspectReplication *replication,
                             u32 connection_index, u32 object_index)
{
    return &replication->ghosts[(usize)connection_index * replication->max_objects +
                                object_index];
}

static BreakRuntimeError find_real(BreakAspectReplication *replication,
                                   BreakOnlineHandle handle, AspectReal **out)
{
    AspectReal *real;
    if (!break_online_handle_valid(handle) || handle.index >= replication->max_objects) {
        return BREAK_RUNTIME_INVALID;
    }
    real = &replication->objects[handle.index];
    if (!real->used || real->handle.generation != handle.generation) {
        return BREAK_RUNTIME_STALE;
    }
    *out = real;
    return BREAK_RUNTIME_OK;
}

static AspectReal *find_real_id(BreakAspectReplication *replication,
                                BreakAoIEntityId id, u32 *out_index)
{
    u32 i;
    for (i = 0u; i < replication->max_objects; ++i) {
        if (replication->objects[i].used &&
            replication->objects[i].object.entity_id == id) {
            *out_index = i;
            return &replication->objects[i];
        }
    }
    return NULL;
}

static BreakRuntimeError find_connection(BreakAspectReplication *replication,
                                         u64 id, u32 *out_index,
                                         AspectConnection **out)
{
    u32 i;
    if (!id) return BREAK_RUNTIME_INVALID;
    for (i = 0u; i < replication->max_connections; ++i) {
        if (replication->connections[i].used && replication->connections[i].id == id) {
            if (out_index) *out_index = i;
            if (out) *out = &replication->connections[i];
            return BREAK_RUNTIME_OK;
        }
    }
    return BREAK_RUNTIME_STALE;
}

BreakRuntimeError break_aspect_replication_create(
    const BreakAspectReplicationConfig *config, BreakAspectStore *store,
    BreakSpatialIndex *index, BreakAspectReplication **out)
{
    BreakAspectReplication *replication;
    usize ghost_count;
    if (!out) return BREAK_RUNTIME_INVALID;
    *out = NULL;
    if (!config || !store || !index || !config->send || !config->max_connections ||
        !config->max_objects || !config->max_fragments ||
        config->max_connections > ASPECT_REPLICATION_HARD_MAX_CONNECTIONS ||
        config->max_objects > ASPECT_REPLICATION_HARD_MAX_OBJECTS ||
        config->max_fragments > ASPECT_REPLICATION_HARD_MAX_FRAGMENTS ||
        config->max_packet_bytes < 25u ||
        config->max_packet_bytes > BREAK_ASPECT_HARD_MAX_PACKET_BYTES) {
        return BREAK_RUNTIME_INVALID;
    }
    ghost_count = (usize)config->max_connections * config->max_objects;
    if (ghost_count > SIZE_MAX / sizeof(AspectGhost)) return BREAK_RUNTIME_INVALID;
    replication = (BreakAspectReplication *)calloc(1u, sizeof(*replication));
    if (!replication) return BREAK_RUNTIME_OOM;
    replication->objects = (AspectReal *)calloc(config->max_objects,
                                                sizeof(*replication->objects));
    replication->connections = (AspectConnection *)calloc(config->max_connections,
                                                          sizeof(*replication->connections));
    replication->ghosts = (AspectGhost *)calloc(ghost_count, sizeof(*replication->ghosts));
    replication->packet = (u8 *)malloc(config->max_packet_bytes);
    replication->fragments = (BreakReplicationFragment *)calloc(
        config->max_fragments, sizeof(*replication->fragments));
    if (!replication->objects || !replication->connections || !replication->ghosts ||
        !replication->packet || !replication->fragments) {
        free(replication->fragments);
        free(replication->packet);
        free(replication->ghosts);
        free(replication->connections);
        free(replication->objects);
        free(replication);
        return BREAK_RUNTIME_OOM;
    }
    replication->owner = platform_thread_current_id();
    replication->store = store;
    replication->index = index;
    replication->send = config->send;
    replication->send_user = config->send_user;
    replication->max_connections = config->max_connections;
    replication->max_objects = config->max_objects;
    replication->packet_capacity = config->max_packet_bytes;
    replication->max_fragments = config->max_fragments;
    *out = replication;
    return BREAK_RUNTIME_OK;
}

void break_aspect_replication_destroy(BreakAspectReplication *replication)
{
    if (!replication_owner(replication)) return;
    free(replication->fragments);
    free(replication->packet);
    free(replication->ghosts);
    free(replication->connections);
    free(replication->objects);
    free(replication);
}

BreakRuntimeError break_aspect_object_register(
    BreakAspectReplication *replication, const BreakReplicationObject *desc,
    BreakOnlineHandle *out)
{
    BreakOnlineHandle handle;
    BreakReplicationObject object;
    BreakRuntimeError result;
    if (!replication_owner(replication)) return BREAK_RUNTIME_REJECTED;
    if (!desc || !out) return BREAK_RUNTIME_INVALID;
    result = break_aspect_object_create(replication->store, &handle);
    if (result != BREAK_RUNTIME_OK) return result;
    if (handle.index >= replication->max_objects ||
        replication->objects[handle.index].used) {
        (void)break_aspect_object_destroy(replication->store, handle);
        return BREAK_RUNTIME_OVERLOAD;
    }
    object = *desc;
    object.entity_id = break_aspect_aoi_id(handle);
    if (!break_spatial_index_insert(replication->index, &object)) {
        (void)break_aspect_object_destroy(replication->store, handle);
        return BREAK_RUNTIME_FAILED;
    }
    replication->objects[handle.index].used = true;
    replication->objects[handle.index].handle = handle;
    replication->objects[handle.index].object = object;
    replication->objects[handle.index].record_epoch =
        break_aspect_object_revision(replication->store, handle);
    *out = handle;
    return BREAK_RUNTIME_OK;
}

BreakRuntimeError break_aspect_connection_open(
    BreakAspectReplication *replication, u64 connection_id,
    usize bandwidth_budget, usize fragment_size)
{
    u32 i;
    if (!replication_owner(replication)) return BREAK_RUNTIME_REJECTED;
    if (!connection_id || !fragment_size ||
        fragment_size > BREAK_NET_MAX_PAYLOAD_SIZE) return BREAK_RUNTIME_INVALID;
    if (find_connection(replication, connection_id, NULL, NULL) == BREAK_RUNTIME_OK) {
        return BREAK_RUNTIME_REJECTED;
    }
    if (replication->connection_count == replication->max_connections) {
        return BREAK_RUNTIME_OVERLOAD;
    }
    for (i = 0u; i < replication->max_connections; ++i) {
        if (!replication->connections[i].used) {
            AspectConnection *connection = &replication->connections[i];
            memset(ghost_at(replication, i, 0u), 0,
                   replication->max_objects * sizeof(AspectGhost));
            connection->used = true;
            connection->id = connection_id;
            connection->default_budget = bandwidth_budget;
            connection->fragment_size = fragment_size;
            replication->connection_count++;
            return BREAK_RUNTIME_OK;
        }
    }
    return BREAK_RUNTIME_OVERLOAD;
}

BreakRuntimeError break_aspect_replication_disconnect(
    BreakAspectReplication *replication, u64 connection_id)
{
    u32 index;
    AspectConnection *connection;
    BreakRuntimeError result;
    if (!replication_owner(replication)) return BREAK_RUNTIME_REJECTED;
    result = find_connection(replication, connection_id, &index, &connection);
    if (result != BREAK_RUNTIME_OK) return result;
    memset(ghost_at(replication, index, 0u), 0,
           replication->max_objects * sizeof(AspectGhost));
    connection->used = false;
    replication->connection_count--;
    return BREAK_RUNTIME_OK;
}

u32 break_aspect_replication_connection_count(
    const BreakAspectReplication *replication)
{
    return replication_owner(replication) ? replication->connection_count : 0u;
}

static BreakRuntimeError mark_dirty(BreakAspectReplication *replication,
                                    BreakOnlineHandle handle, u32 aspect_id,
                                    u64 old_revision)
{
    u64 new_revision = break_aspect_object_revision(replication->store, handle);
    u32 i;
    if (new_revision == old_revision) return BREAK_RUNTIME_OK;
    for (i = 0u; i < replication->max_connections; ++i) {
        if (replication->connections[i].used) {
            ghost_at(replication, i, handle.index)->dirty_mask |=
                UINT64_C(1) << (aspect_id - 1u);
        }
    }
    return BREAK_RUNTIME_OK;
}

BreakRuntimeError break_aspect_replication_set_u32(
    BreakAspectReplication *replication, BreakOnlineHandle handle,
    u32 aspect_id, u32 value)
{
    AspectReal *real;
    BreakRuntimeError result;
    u64 old_revision;
    if (!replication_owner(replication)) return BREAK_RUNTIME_REJECTED;
    result = find_real(replication, handle, &real);
    if (result != BREAK_RUNTIME_OK) return result;
    old_revision = break_aspect_object_revision(replication->store, handle);
    result = break_aspect_set_u32(replication->store, handle, aspect_id, value);
    if (result != BREAK_RUNTIME_OK) return result;
    return mark_dirty(replication, handle, aspect_id, old_revision);
}

BreakRuntimeError break_aspect_replication_set_i32(
    BreakAspectReplication *replication, BreakOnlineHandle handle,
    u32 aspect_id, i32 value)
{
    AspectReal *real;
    BreakRuntimeError result;
    u64 old_revision;
    if (!replication_owner(replication)) return BREAK_RUNTIME_REJECTED;
    result = find_real(replication, handle, &real);
    if (result != BREAK_RUNTIME_OK) return result;
    old_revision = break_aspect_object_revision(replication->store, handle);
    result = break_aspect_set_i32(replication->store, handle, aspect_id, value);
    if (result != BREAK_RUNTIME_OK) return result;
    return mark_dirty(replication, handle, aspect_id, old_revision);
}

BreakRuntimeError break_aspect_replication_set_f32(
    BreakAspectReplication *replication, BreakOnlineHandle handle,
    u32 aspect_id, f32 value)
{
    AspectReal *real;
    BreakRuntimeError result;
    u64 old_revision;
    if (!replication_owner(replication)) return BREAK_RUNTIME_REJECTED;
    result = find_real(replication, handle, &real);
    if (result != BREAK_RUNTIME_OK) return result;
    old_revision = break_aspect_object_revision(replication->store, handle);
    result = break_aspect_set_f32(replication->store, handle, aspect_id, value);
    if (result != BREAK_RUNTIME_OK) return result;
    return mark_dirty(replication, handle, aspect_id, old_revision);
}

BreakRuntimeError break_aspect_replication_set_bytes(
    BreakAspectReplication *replication, BreakOnlineHandle handle,
    u32 aspect_id, const void *data, u32 size)
{
    AspectReal *real;
    BreakRuntimeError result;
    u64 old_revision;
    if (!replication_owner(replication)) return BREAK_RUNTIME_REJECTED;
    result = find_real(replication, handle, &real);
    if (result != BREAK_RUNTIME_OK) return result;
    old_revision = break_aspect_object_revision(replication->store, handle);
    result = break_aspect_set_bytes(replication->store, handle, aspect_id, data, size);
    if (result != BREAK_RUNTIME_OK) return result;
    return mark_dirty(replication, handle, aspect_id, old_revision);
}

BreakRuntimeError break_aspect_replication_set_flags(
    BreakAspectReplication *replication, BreakOnlineHandle handle, u32 flags)
{
    AspectReal *real;
    BreakRuntimeError result;
    BreakReplicationObject object;
    if (!replication_owner(replication)) return BREAK_RUNTIME_REJECTED;
    result = find_real(replication, handle, &real);
    if (result != BREAK_RUNTIME_OK) return result;
    object = real->object;
    object.flags = flags;
    if (!break_spatial_index_insert(replication->index, &object)) {
        return BREAK_RUNTIME_FAILED;
    }
    real->object = object;
    return BREAK_RUNTIME_OK;
}

static BreakRuntimeError publish(BreakAspectReplication *replication,
                                 u32 connection_index, AspectConnection *connection,
                                 AspectReal *real, u8 kind, u64 mask,
                                 usize *budget, bool *out_sent)
{
    BreakReplicationFragmentResult fragment_result;
    BreakRuntimeError result;
    usize packet_size = 0u;
    usize fragment_count = 0u;
    usize total_size = 0u;
    usize i;
    u64 delta_id;
    u64 epoch;
    (void)connection_index;
    *out_sent = false;
    if (real->record_epoch == UINT64_MAX) return BREAK_RUNTIME_OVERLOAD;
    epoch = real->record_epoch + 1u;
    result = break_aspect_encode_with_epoch(replication->store, real->handle, mask, kind,
                                 epoch, replication->packet, replication->packet_capacity,
                                 &packet_size);
    if (result != BREAK_RUNTIME_OK) return result;
    if (replication->next_delta_id == UINT64_MAX) return BREAK_RUNTIME_OVERLOAD;
    delta_id = replication->next_delta_id + 1u;
    fragment_result = break_replication_fragment_payload_into(
        delta_id, break_aspect_schema_hash(replication->store),
        replication->packet, packet_size, connection->fragment_size,
        replication->fragments, replication->max_fragments, &fragment_count);
    if (fragment_result == BREAK_REPLICATION_FRAGMENT_OVER_LIMIT) {
        return BREAK_RUNTIME_OVERLOAD;
    }
    if (fragment_result != BREAK_REPLICATION_FRAGMENT_OK) return BREAK_RUNTIME_INVALID;
    for (i = 0u; i < fragment_count; ++i) {
        if (replication->fragments[i].size > SIZE_MAX - total_size) {
            return BREAK_RUNTIME_OVERLOAD;
        }
        total_size += replication->fragments[i].size;
    }
    if (total_size > *budget) return BREAK_RUNTIME_OK;
    replication->next_delta_id = delta_id;
    for (i = 0u; i < fragment_count; ++i) {
        result = replication->send(replication->send_user, connection->id,
                                   &replication->fragments[i]);
        if (result != BREAK_RUNTIME_OK) return result;
    }
    *budget -= total_size;
    real->record_epoch = epoch;
    *out_sent = true;
    return BREAK_RUNTIME_OK;
}

static BreakRuntimeError sync_record(BreakAspectReplication *replication,
                                     u32 connection_index,
                                     AspectConnection *connection,
                                     AspectReal *real, u32 real_index,
                                     AspectGhost *ghost, u8 kind, u64 mask,
                                     usize *budget)
{
    bool sent = false;
    BreakRuntimeError result = publish(replication, connection_index, connection,
                                       real, kind, mask, budget, &sent);
    (void)real_index;
    if (result != BREAK_RUNTIME_OK || !sent) return result;
    if (kind == BREAK_ASPECT_BASELINE) {
        ghost->baseline_sent = true;
        ghost->sent_revision = break_aspect_object_revision(replication->store,
                                                             real->handle);
        ghost->dirty_mask = 0u;
    } else if (kind == BREAK_ASPECT_DIRTY) {
        ghost->sent_revision = break_aspect_object_revision(replication->store,
                                                             real->handle);
        ghost->dirty_mask &= ~mask;
    } else {
        memset(ghost, 0, sizeof(*ghost));
    }
    return BREAK_RUNTIME_OK;
}

BreakRuntimeError break_aspect_replication_sync(
    BreakAspectReplication *replication, u64 connection_id,
    const BreakAoIResult *aoi, usize bandwidth_budget)
{
    u32 connection_index;
    AspectConnection *connection;
    BreakRuntimeError result;
    usize i;
    if (!replication_owner(replication)) return BREAK_RUNTIME_REJECTED;
    if (!aoi || (aoi->enter_count && !aoi->enter) ||
        (aoi->stay_count && !aoi->stay) || (aoi->leave_count && !aoi->leave) ||
        aoi->enter_count > replication->max_objects ||
        aoi->stay_count > replication->max_objects ||
        aoi->leave_count > replication->max_objects) return BREAK_RUNTIME_INVALID;
    result = find_connection(replication, connection_id, &connection_index, &connection);
    if (result != BREAK_RUNTIME_OK) return result;
    for (i = 0u; i < replication->max_objects; ++i) {
        AspectGhost *ghost = ghost_at(replication, connection_index, (u32)i);
        if (ghost->pending_leave) {
            if (!replication->objects[i].used) {
                memset(ghost, 0, sizeof(*ghost));
                continue;
            }
            result = sync_record(replication, connection_index, connection,
                                 &replication->objects[i], (u32)i, ghost,
                                 ghost->pending_leave, 0u, &bandwidth_budget);
            if (result != BREAK_RUNTIME_OK) return result;
        }
    }
    for (i = 0u; i < aoi->enter_count; ++i) {
        u32 real_index;
        AspectReal *real = find_real_id(replication, aoi->enter[i], &real_index);
        AspectGhost *ghost;
        if (!real) continue;
        ghost = ghost_at(replication, connection_index, real_index);
        if (!ghost->baseline_sent) {
            ghost->in_scope = true;
            result = sync_record(replication, connection_index, connection,
                                 real, real_index, ghost, BREAK_ASPECT_BASELINE,
                                 break_aspect_active_mask(replication->store, real->handle),
                                 &bandwidth_budget);
            if (result != BREAK_RUNTIME_OK) return result;
        }
    }
    for (i = 0u; i < aoi->stay_count; ++i) {
        u32 real_index;
        AspectReal *real = find_real_id(replication, aoi->stay[i], &real_index);
        AspectGhost *ghost;
        if (!real) continue;
        ghost = ghost_at(replication, connection_index, real_index);
        if (!ghost->baseline_sent) {
            ghost->in_scope = true;
            result = sync_record(replication, connection_index, connection,
                                 real, real_index, ghost, BREAK_ASPECT_BASELINE,
                                 break_aspect_active_mask(replication->store, real->handle),
                                 &bandwidth_budget);
        } else if (ghost->dirty_mask) {
            result = sync_record(replication, connection_index, connection,
                                 real, real_index, ghost, BREAK_ASPECT_DIRTY,
                                 ghost->dirty_mask, &bandwidth_budget);
        } else {
            result = BREAK_RUNTIME_OK;
        }
        if (result != BREAK_RUNTIME_OK) return result;
    }
    for (i = 0u; i < aoi->leave_count; ++i) {
        u32 real_index;
        AspectReal *real = find_real_id(replication, aoi->leave[i], &real_index);
        AspectGhost *ghost;
        u8 kind;
        if (!real) continue;
        ghost = ghost_at(replication, connection_index, real_index);
        if (!ghost->in_scope) continue;
        if (!ghost->baseline_sent) {
            memset(ghost, 0, sizeof(*ghost));
            continue;
        }
        kind = (real->object.flags & BREAK_AOI_OBJECT_DORMANT)
            ? BREAK_ASPECT_DORMANT : BREAK_ASPECT_DESTROY;
        ghost->pending_leave = kind;
        result = sync_record(replication, connection_index, connection,
                             real, real_index, ghost, kind, 0u, &bandwidth_budget);
        if (result != BREAK_RUNTIME_OK) return result;
    }
    return BREAK_RUNTIME_OK;
}

BreakRuntimeError break_aspect_replication_sync_default(
    BreakAspectReplication *replication, u64 connection_id,
    const BreakAoIResult *aoi)
{
    AspectConnection *connection;
    BreakRuntimeError result;
    if (!replication_owner(replication)) return BREAK_RUNTIME_REJECTED;
    result = find_connection(replication, connection_id, NULL, &connection);
    if (result != BREAK_RUNTIME_OK) return result;
    return break_aspect_replication_sync(replication, connection_id, aoi,
                                         connection->default_budget);
}
