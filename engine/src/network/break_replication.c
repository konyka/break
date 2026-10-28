#include "network/break_replication.h"
#include "network/break_net_protocol.h"

#include <stdlib.h>
#include <string.h>

#define REPL_KIND_SIZE 1u
#define REPL_ID_SIZE 8u
#define REPL_VERSION_SIZE 8u
#define REPL_HEADER_SIZE (REPL_KIND_SIZE + REPL_ID_SIZE + REPL_VERSION_SIZE)

static bool size_add_checked(size_t left, size_t right, size_t *out)
{
    if (!out || right > (size_t)-1 - left) return false;
    *out = left + right;
    return true;
}

static bool size_mul_checked(size_t left, size_t right, size_t *out)
{
    if (!out || (left && right > (size_t)-1 / left)) return false;
    *out = left * right;
    return true;
}

typedef struct {
    BreakReplicationObject object;
    uint8_t *payload;
    size_t payload_size;
    uint64_t version;
} RepObject;

typedef struct {
    BreakAoIEntityId entity_id;
    bool baseline_sent;
    uint64_t sent_version;
} RepGhost;

typedef struct {
    uint64_t key;
    size_t budget;
    RepGhost *ghosts;
    size_t ghost_count;
} RepConnection;

struct BreakReplication {
    BreakNetReactor *reactor;
    uint16_t message_ids[4];
    RepObject *objects;
    size_t object_count;
    RepConnection *connections;
    size_t connection_count;
};

static void put_u64(uint8_t *out, uint64_t value)
{
    size_t i;
    for (i = 0u; i < 8u; ++i) out[i] = (uint8_t)(value >> (i * 8u));
}

static RepObject *find_object(BreakReplication *replication, BreakAoIEntityId id)
{
    size_t i;
    for (i = 0u; i < replication->object_count; ++i)
        if (replication->objects[i].object.entity_id == id) return &replication->objects[i];
    return NULL;
}

static const RepObject *find_object_const(const BreakReplication *replication, BreakAoIEntityId id)
{
    size_t i;
    for (i = 0u; i < replication->object_count; ++i)
        if (replication->objects[i].object.entity_id == id) return &replication->objects[i];
    return NULL;
}

static RepConnection *find_connection(BreakReplication *replication, uint64_t key)
{
    size_t i;
    for (i = 0u; i < replication->connection_count; ++i)
        if (replication->connections[i].key == key) return &replication->connections[i];
    return NULL;
}

static RepGhost *find_ghost(RepConnection *connection, BreakAoIEntityId id)
{
    size_t i;
    for (i = 0u; i < connection->ghost_count; ++i)
        if (connection->ghosts[i].entity_id == id) return &connection->ghosts[i];
    return NULL;
}

static void sort_ids(const BreakReplication *replication,
                     BreakAoIEntityId *ids, size_t count)
{
    size_t i;
    for (i = 0u; i < count; ++i) {
        size_t best = i;
        size_t j;
        for (j = i + 1u; j < count; ++j) {
            const RepObject *left = find_object_const(replication, ids[best]);
            const RepObject *right = find_object_const(replication, ids[j]);
            if (right && (!left || right->object.priority > left->object.priority ||
                (right->object.priority == left->object.priority && ids[j] < ids[best]))) best = j;
        }
        if (best != i) {
            BreakAoIEntityId id = ids[i];
            ids[i] = ids[best];
            ids[best] = id;
        }
    }
}

static bool append_payload(uint8_t **out, size_t *out_size, uint8_t kind,
                           BreakAoIEntityId id, uint64_t version,
                           const void *payload, size_t payload_size)
{
    uint8_t *memory;
    if (payload_size > BREAK_NET_MAX_PAYLOAD_SIZE - REPL_HEADER_SIZE) return false;
    memory = (uint8_t *)malloc(REPL_HEADER_SIZE + payload_size);
    if (!memory) return false;
    memory[0] = kind;
    put_u64(memory + 1u, id);
    put_u64(memory + 9u, version);
    if (payload_size) memcpy(memory + REPL_HEADER_SIZE, payload, payload_size);
    *out = memory;
    *out_size = REPL_HEADER_SIZE + payload_size;
    return true;
}

static bool send_record(BreakReplication *replication, RepConnection *connection,
                        uint8_t kind, uint16_t message_id, BreakAoIEntityId id,
                        uint64_t version, const void *payload, size_t payload_size,
                        size_t *budget)
{
    uint8_t *wire = NULL;
    size_t wire_size = 0u;
    BreakNetSendResult result;
    if (!append_payload(&wire, &wire_size, kind, id, version, payload, payload_size)) return false;
    if (wire_size > *budget) {
        free(wire);
        return false;
    }
    result = break_net_reactor_send(replication->reactor, connection->key,
                                    message_id, BREAK_NET_PROTOCOL_VERSION,
                                    wire, wire_size);
    free(wire);
    if (result != BREAK_NET_SEND_OK) return false;
    *budget -= wire_size;
    return true;
}

BreakReplication *break_replication_create(BreakNetReactor *reactor,
                                             uint16_t baseline_message_id,
                                             uint16_t dirty_message_id,
                                             uint16_t destroy_message_id,
                                             uint16_t dormant_message_id)
{
    BreakReplication *replication;
    if (!reactor) return NULL;
    replication = (BreakReplication *)calloc(1u, sizeof(*replication));
    if (!replication) return NULL;
    replication->reactor = reactor;
    replication->message_ids[0] = baseline_message_id;
    replication->message_ids[1] = dirty_message_id;
    replication->message_ids[2] = destroy_message_id;
    replication->message_ids[3] = dormant_message_id;
    return replication;
}

void break_replication_destroy(BreakReplication *replication)
{
    size_t i;
    if (!replication) return;
    for (i = 0u; i < replication->object_count; ++i) free(replication->objects[i].payload);
    for (i = 0u; i < replication->connection_count; ++i) free(replication->connections[i].ghosts);
    free(replication->objects);
    free(replication->connections);
    free(replication);
}

bool break_replication_register(BreakReplication *replication,
                                const BreakReplicationObject *object,
                                const void *payload, size_t payload_size)
{
    RepObject *entry;
    uint8_t *copy = NULL;
    size_t grown_count;
    size_t grown_bytes;
    if (!replication || !object || (payload_size && !payload) ||
        payload_size > BREAK_NET_MAX_PAYLOAD_SIZE - REPL_HEADER_SIZE) return false;
    entry = find_object(replication, object->entity_id);
    if (entry && entry->version == UINT64_MAX) return false;
    if (payload_size) {
        copy = (uint8_t *)malloc(payload_size);
        if (!copy) return false;
        memcpy(copy, payload, payload_size);
    }
    entry = find_object(replication, object->entity_id);
    if (!entry) {
        RepObject *grown;
        if (!size_add_checked(replication->object_count, 1u, &grown_count) ||
            !size_mul_checked(grown_count, sizeof(*grown), &grown_bytes)) {
            free(copy);
            return false;
        }
        grown = (RepObject *)realloc(replication->objects, grown_bytes);
        if (!grown) { free(copy); return false; }
        replication->objects = grown;
        entry = &replication->objects[replication->object_count++];
        memset(entry, 0, sizeof(*entry));
    }
    free(entry->payload);
    entry->payload = copy;
    entry->object = *object;
    entry->payload_size = payload_size;
    entry->version = entry->version ? entry->version + 1u : 1u;
    return true;
}

bool break_replication_mark_dirty(BreakReplication *replication,
                                  BreakAoIEntityId entity_id,
                                  const void *payload, size_t payload_size)
{
    RepObject *entry;
    uint8_t *copy = NULL;
    if (!replication || (payload_size && !payload) ||
        payload_size > BREAK_NET_MAX_PAYLOAD_SIZE - REPL_HEADER_SIZE) return false;
    entry = find_object(replication, entity_id);
    if (!entry || entry->version == UINT64_MAX) return false;
    if (payload_size) {
        copy = (uint8_t *)malloc(payload_size);
        if (!copy) return false;
        memcpy(copy, payload, payload_size);
    }
    free(entry->payload);
    entry->payload = copy;
    entry->payload_size = payload_size;
    entry->version++;
    return true;
}

bool break_replication_connection_open(BreakReplication *replication,
                                        uint64_t connection_key,
                                        size_t bandwidth_budget)
{
    RepConnection *grown;
    size_t grown_count;
    size_t grown_bytes;
    if (!replication || find_connection(replication, connection_key)) return false;
    if (!size_add_checked(replication->connection_count, 1u, &grown_count) ||
        !size_mul_checked(grown_count, sizeof(*grown), &grown_bytes)) return false;
    grown = (RepConnection *)realloc(replication->connections, grown_bytes);
    if (!grown) return false;
    replication->connections = grown;
    memset(&replication->connections[replication->connection_count], 0, sizeof(*grown));
    replication->connections[replication->connection_count].key = connection_key;
    replication->connections[replication->connection_count].budget = bandwidth_budget;
    replication->connection_count++;
    return true;
}

bool break_replication_disconnect(BreakReplication *replication, uint64_t connection_key)
{
    size_t i;
    if (!replication) return false;
    for (i = 0u; i < replication->connection_count; ++i) {
        if (replication->connections[i].key == connection_key) {
            free(replication->connections[i].ghosts);
            replication->connections[i] = replication->connections[--replication->connection_count];
            return true;
        }
    }
    return false;
}

size_t break_replication_connection_count(const BreakReplication *replication)
{
    return replication ? replication->connection_count : 0u;
}

bool break_replication_sync(BreakReplication *replication, uint64_t connection_key,
                            const BreakAoIResult *aoi)
{
    RepConnection *connection;
    if (!replication || !aoi) return false;
    connection = find_connection(replication, connection_key);
    return connection && break_replication_sync_budget(replication, connection_key, aoi,
                                                        connection->budget);
}

bool break_replication_sync_budget(BreakReplication *replication, uint64_t connection_key,
                                   const BreakAoIResult *aoi, size_t bandwidth_budget)
{
    RepConnection *connection;
    BreakAoIEntityId *enter_ids;
    BreakAoIEntityId *stay_ids;
    BreakAoIEntityId *leave_ids;
    size_t i;
    if (!replication || !aoi) return false;
    connection = find_connection(replication, connection_key);
    if (!connection ||
        (aoi->enter_count && !aoi->enter) || (aoi->stay_count && !aoi->stay) ||
        (aoi->leave_count && !aoi->leave)) return false;
    {
        size_t enter_bytes = 0u, stay_bytes = 0u, leave_bytes = 0u;
        if (!size_mul_checked(aoi->enter_count, sizeof(*enter_ids), &enter_bytes) ||
            !size_mul_checked(aoi->stay_count, sizeof(*stay_ids), &stay_bytes) ||
            !size_mul_checked(aoi->leave_count, sizeof(*leave_ids), &leave_bytes)) return false;
        enter_ids = enter_bytes ? (BreakAoIEntityId *)malloc(enter_bytes) : NULL;
        stay_ids = stay_bytes ? (BreakAoIEntityId *)malloc(stay_bytes) : NULL;
        leave_ids = leave_bytes ? (BreakAoIEntityId *)malloc(leave_bytes) : NULL;
    }
    if ((aoi->enter_count && !enter_ids) || (aoi->stay_count && !stay_ids) || (aoi->leave_count && !leave_ids)) {
        free(enter_ids); free(stay_ids); free(leave_ids); return false;
    }
    if (aoi->enter_count) memcpy(enter_ids, aoi->enter, aoi->enter_count * sizeof(*enter_ids));
    if (aoi->stay_count) memcpy(stay_ids, aoi->stay, aoi->stay_count * sizeof(*stay_ids));
    if (aoi->leave_count) memcpy(leave_ids, aoi->leave, aoi->leave_count * sizeof(*leave_ids));
    sort_ids(replication, enter_ids, aoi->enter_count);
    sort_ids(replication, stay_ids, aoi->stay_count);
    sort_ids(replication, leave_ids, aoi->leave_count);
    for (i = 0u; i < aoi->enter_count; ++i) {
        BreakAoIEntityId id = enter_ids[i];
        RepObject *object = find_object(replication, id);
        RepGhost *ghost;
        bool sent;
        if (!object) continue;
        ghost = find_ghost(connection, object->object.entity_id);
        if (!ghost) {
            RepGhost *grown;
            size_t ghost_count;
            size_t ghost_bytes;
            if (!size_add_checked(connection->ghost_count, 1u, &ghost_count) ||
                !size_mul_checked(ghost_count, sizeof(*grown), &ghost_bytes)) {
                free(enter_ids); free(stay_ids); free(leave_ids); return false;
            }
            grown = (RepGhost *)realloc(connection->ghosts, ghost_bytes);
            if (!grown) {
                free(enter_ids); free(stay_ids); free(leave_ids); return false;
            }
            connection->ghosts = grown;
            connection->ghost_count = ghost_count;
            ghost = &connection->ghosts[ghost_count - 1u];
            *ghost = (RepGhost){object->object.entity_id, false, 0u};
        }
        sent = !ghost->baseline_sent &&
               send_record(replication, connection, BREAK_REPLICATION_BASELINE,
                           replication->message_ids[0], object->object.entity_id,
                           object->version, object->payload, object->payload_size,
                           &bandwidth_budget);
        if (sent) { ghost->baseline_sent = true; ghost->sent_version = object->version; }
    }
    for (i = 0u; i < aoi->stay_count; ++i) {
        RepObject *object = find_object(replication, stay_ids[i]);
        RepGhost *ghost = object ? find_ghost(connection, object->object.entity_id) : NULL;
        if (object && ghost && ghost->baseline_sent && object->version > ghost->sent_version &&
            send_record(replication, connection, BREAK_REPLICATION_DIRTY,
                        replication->message_ids[1], object->object.entity_id,
                        object->version, object->payload, object->payload_size,
                        &bandwidth_budget)) ghost->sent_version = object->version;
    }
    for (i = 0u; i < aoi->leave_count; ++i) {
        RepObject *object = find_object(replication, leave_ids[i]);
        RepGhost *ghost = find_ghost(connection, leave_ids[i]);
        if (ghost && send_record(replication, connection,
                                 object && (object->object.flags & BREAK_AOI_OBJECT_DORMANT)
                                     ? BREAK_REPLICATION_DORMANT : BREAK_REPLICATION_DESTROY,
                                 object && (object->object.flags & BREAK_AOI_OBJECT_DORMANT)
                                     ? replication->message_ids[3] : replication->message_ids[2],
                                 leave_ids[i], ghost->sent_version, NULL, 0u,
                                 &bandwidth_budget)) {
            if (--connection->ghost_count != 0u) {
                RepGhost *shrunk;
                size_t ghost_bytes;
                *ghost = connection->ghosts[connection->ghost_count];
                if (size_mul_checked(connection->ghost_count, sizeof(*ghost), &ghost_bytes)) {
                    shrunk = (RepGhost *)realloc(connection->ghosts, ghost_bytes);
                    if (shrunk) connection->ghosts = shrunk;
                }
            }
        }
    }
    free(enter_ids);
    free(stay_ids);
    free(leave_ids);
    return true;
}

bool break_replication_test_set_version(BreakReplication *replication,
                                        BreakAoIEntityId entity_id,
                                        uint64_t version)
{
    RepObject *entry;
    if (!replication) return false;
    entry = find_object(replication, entity_id);
    if (!entry) return false;
    entry->version = version;
    return true;
}
