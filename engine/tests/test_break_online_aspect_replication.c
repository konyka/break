#include "test_framework.h"
#include <network/break_online_aspect_replication.h>

#include <stdint.h>
#include <string.h>

#define SINK_MAX_RECORDS 64u
#define SINK_MAX_FRAGMENT 512u

typedef struct RecordedFragment {
    u64 connection;
    BreakReplicationFragment meta;
    u8 bytes[SINK_MAX_FRAGMENT];
} RecordedFragment;

typedef struct SendSink {
    RecordedFragment records[SINK_MAX_RECORDS];
    usize count;
    u64 fail_connection;
    u32 failures;
    u32 calls;
    u32 fail_at_call;
} SendSink;

static BreakRuntimeError record_send(void *user, u64 connection,
                                     const BreakReplicationFragment *fragment)
{
    SendSink *sink = (SendSink *)user;
    RecordedFragment *record;
    sink->calls++;
    if (sink->fail_at_call != 0u && sink->calls == sink->fail_at_call) {
        sink->failures++;
        return BREAK_RUNTIME_OVERLOAD;
    }
    if (sink->fail_connection == connection) {
        sink->fail_connection = 0u;
        sink->failures++;
        return BREAK_RUNTIME_OVERLOAD;
    }
    if (sink->count == SINK_MAX_RECORDS || fragment->size > SINK_MAX_FRAGMENT) {
        return BREAK_RUNTIME_OVERLOAD;
    }
    record = &sink->records[sink->count++];
    record->connection = connection;
    record->meta = *fragment;
    record->meta.data = record->bytes;
    memcpy(record->bytes, fragment->data, fragment->size);
    return BREAK_RUNTIME_OK;
}

static void sink_reset(SendSink *sink)
{
    sink->count = 0u;
}

typedef struct ReplFixture {
    BreakAspectStore *store;
    BreakAspectStore *remote_a;
    BreakAspectStore *remote_b;
    BreakSpatialIndex *index;
    BreakAspectReplication *replication;
    SendSink sink;
} ReplFixture;

static bool register_schemas(BreakAspectStore *store)
{
    const BreakAspectSchema health = {2u, 1u, BREAK_ASPECT_U32, 4u};
    const BreakAspectSchema blob = {3u, 1u, BREAK_ASPECT_BYTES, 220u};
    return break_aspect_schema_register(store, &health) == BREAK_RUNTIME_OK &&
           break_aspect_schema_register(store, &blob) == BREAK_RUNTIME_OK;
}

static BreakAspectStore *make_aspect_store(void)
{
    BreakAspectStoreConfig config = {4u, 224u, 512u};
    BreakAspectStore *store = NULL;
    if (break_aspect_store_create(&config, &store) != BREAK_RUNTIME_OK) return NULL;
    if (!register_schemas(store)) {
        break_aspect_store_destroy(store);
        return NULL;
    }
    return store;
}

static bool fixture_init(ReplFixture *fixture)
{
    BreakAspectReplicationConfig config;
    memset(fixture, 0, sizeof(*fixture));
    fixture->store = make_aspect_store();
    fixture->remote_a = make_aspect_store();
    fixture->remote_b = make_aspect_store();
    fixture->index = break_spatial_index_create(10.0f);
    if (!fixture->store || !fixture->remote_a || !fixture->remote_b || !fixture->index) {
        return false;
    }
    memset(&config, 0, sizeof(config));
    config.max_connections = 2u;
    config.max_objects = 4u;
    config.max_packet_bytes = 512u;
    config.max_fragments = 16u;
    config.send = record_send;
    config.send_user = &fixture->sink;
    return break_aspect_replication_create(&config, fixture->store, fixture->index,
                                           &fixture->replication) == BREAK_RUNTIME_OK;
}

static void fixture_dispose(ReplFixture *fixture)
{
    break_aspect_replication_destroy(fixture->replication);
    break_spatial_index_destroy(fixture->index);
    break_aspect_store_destroy(fixture->remote_b);
    break_aspect_store_destroy(fixture->remote_a);
    break_aspect_store_destroy(fixture->store);
}

static BreakOnlineHandle register_object(ReplFixture *fixture, u32 priority, u32 flags)
{
    BreakReplicationObject desc;
    BreakOnlineHandle handle = {UINT32_MAX, UINT32_MAX};
    memset(&desc, 0, sizeof(desc));
    desc.priority = priority;
    desc.flags = flags;
    if (break_aspect_object_register(fixture->replication, &desc, &handle) != BREAK_RUNTIME_OK) {
        handle.index = UINT32_MAX;
    }
    return handle;
}

static bool adopt_remote(BreakAspectStore *remote, BreakOnlineHandle handle)
{
    return break_aspect_object_adopt(remote, handle) == BREAK_RUNTIME_OK;
}

static bool consume_one_packet(SendSink *sink, u64 connection, usize *offset,
                               BreakAspectStore *remote, u8 *out_kind)
{
    BreakReplicationReassembler *reassembler;
    BreakReplicationReassemblyResult result = BREAK_REPLICATION_REASSEMBLY_INCOMPLETE;
    u64 delta_id;
    u8 *packet = NULL;
    usize packet_size = 0u;
    u8 kind = 0u;
    bool ok = false;
    if (*offset >= sink->count || sink->records[*offset].connection != connection) return false;
    delta_id = sink->records[*offset].meta.delta_id;
    reassembler = break_replication_reassembler_create(sink->records[*offset].meta.base_id);
    if (!reassembler) return false;
    while (*offset < sink->count && sink->records[*offset].connection == connection &&
           sink->records[*offset].meta.delta_id == delta_id) {
        result = break_replication_reassembler_push(reassembler,
            &sink->records[*offset].meta, &packet, &packet_size);
        ++*offset;
        if (result == BREAK_REPLICATION_REASSEMBLY_COMPLETE) break;
        if (result != BREAK_REPLICATION_REASSEMBLY_INCOMPLETE) {
            break_replication_reassembler_destroy(reassembler);
            return false;
        }
    }
    if (result == BREAK_REPLICATION_REASSEMBLY_COMPLETE && packet_size > 22u) {
        usize position = 20u;
        u8 byte;
        do {
            if (position >= packet_size) goto done;
            byte = packet[position++];
        } while (byte & 0x80u);
        if (position >= packet_size) goto done;
        kind = packet[position];
        ok = break_aspect_apply(remote, packet, packet_size) == BREAK_RUNTIME_OK;
        if (out_kind) *out_kind = kind;
    }
done:
    break_replication_reassembly_free(packet);
    break_replication_reassembler_destroy(reassembler);
    return ok;
}

static bool consume_all(SendSink *sink, u64 connection, BreakAspectStore *remote)
{
    usize offset = 0u;
    while (offset < sink->count) {
        if (sink->records[offset].connection != connection) {
            ++offset;
            continue;
        }
        if (!consume_one_packet(sink, connection, &offset, remote, NULL)) return false;
    }
    return true;
}

static bool prepare_pending_leave(ReplFixture *fixture, BreakOnlineHandle *object,
                                  BreakAoIScope *scope, BreakAoIResult *aoi)
{
    BreakWitness witness;
    BreakAoIEntityId id;
    if (!fixture_init(fixture)) return false;
    *object = register_object(fixture, 5u, BREAK_AOI_OBJECT_ALWAYS_RELEVANT);
    if (object->index == UINT32_MAX || !adopt_remote(fixture->remote_a, *object) ||
        break_aspect_replication_set_u32(fixture->replication, *object, 2u, 1u) != BREAK_RUNTIME_OK ||
        break_aspect_connection_open(fixture->replication, 1u, 1024u, 32u) != BREAK_RUNTIME_OK) {
        return false;
    }
    memset(&witness, 0, sizeof(witness));
    witness.radius = 10.0f;
    witness.connection_id = 1u;
    if (!break_aoi_compute(fixture->index, &witness, 1u, NULL, aoi) ||
        break_aspect_replication_sync(fixture->replication, 1u, aoi, 1024u) != BREAK_RUNTIME_OK ||
        !consume_all(&fixture->sink, 1u, fixture->remote_a)) return false;
    sink_reset(&fixture->sink);
    id = break_aspect_aoi_id(*object);
    if (!break_aoi_scope_assign(scope, &id, 1u) ||
        break_aspect_replication_set_flags(fixture->replication, *object,
            BREAK_AOI_OBJECT_ALWAYS_RELEVANT | BREAK_AOI_OBJECT_DORMANT) != BREAK_RUNTIME_OK) {
        return false;
    }
    break_aoi_result_clear(aoi);
    memset(&witness, 0, sizeof(witness));
    witness.radius = 10.0f;
    witness.connection_id = 1u;
    return break_aoi_compute(fixture->index, &witness, 1u, scope, aoi) &&
           aoi->leave_count == 1u;
}

TEST(aspect_replication_baselines_and_per_connection_dirty_masks)
{
    ReplFixture fixture;
    BreakOnlineHandle object;
    BreakAoIResult aoi = {0};
    BreakAoIScope scope = {0};
    BreakWitness witness;
    BreakAoIEntityId id;
    usize offset;
    u32 health_a = 0u;
    u32 health_b = 0u;
    ASSERT_TRUE(fixture_init(&fixture));
    object = register_object(&fixture, 5u, BREAK_AOI_OBJECT_ALWAYS_RELEVANT);
    ASSERT_NEQ(object.index, UINT32_MAX);
    ASSERT_TRUE(adopt_remote(fixture.remote_a, object));
    ASSERT_TRUE(adopt_remote(fixture.remote_b, object));
    ASSERT_EQ(break_aspect_replication_set_u32(fixture.replication, object, 2u, 1u),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(break_aspect_connection_open(fixture.replication, 1u, 1024u, 512u),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(break_aspect_connection_open(fixture.replication, 2u, 1024u, 512u),
              BREAK_RUNTIME_OK);
    memset(&witness, 0, sizeof(witness));
    witness.radius = 10.0f;
    witness.connection_id = 1u;
    ASSERT_TRUE(break_aoi_compute(fixture.index, &witness, 1u, NULL, &aoi));
    ASSERT_EQ(aoi.enter_count, 1u);
    ASSERT_EQ(break_aspect_replication_sync(fixture.replication, 1u, &aoi, 1024u),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(break_aspect_replication_sync(fixture.replication, 2u, &aoi, 1024u),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(fixture.sink.count, 2u);
    ASSERT_TRUE(consume_all(&fixture.sink, 1u, fixture.remote_a));
    ASSERT_TRUE(consume_all(&fixture.sink, 2u, fixture.remote_b));
    ASSERT_EQ(break_aspect_get_u32(fixture.remote_a, object, 2u, &health_a), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_aspect_get_u32(fixture.remote_b, object, 2u, &health_b), BREAK_RUNTIME_OK);
    ASSERT_EQ(health_a, 1u);
    ASSERT_EQ(health_b, 1u);
    id = break_aspect_aoi_id(object);
    ASSERT_TRUE(break_aoi_scope_assign(&scope, &id, 1u));
    break_aoi_result_clear(&aoi);
    ASSERT_TRUE(break_aoi_compute(fixture.index, &witness, 1u, &scope, &aoi));
    ASSERT_EQ(aoi.stay_count, 1u);
    ASSERT_EQ(break_aspect_replication_set_u32(fixture.replication, object, 2u, 7u),
              BREAK_RUNTIME_OK);
    sink_reset(&fixture.sink);
    ASSERT_EQ(break_aspect_replication_sync(fixture.replication, 1u, &aoi, 1024u),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(fixture.sink.count, 1u);
    ASSERT_EQ(fixture.sink.records[0].connection, 1u);
    offset = 0u;
    ASSERT_TRUE(consume_one_packet(&fixture.sink, 1u, &offset, fixture.remote_a, NULL));
    ASSERT_EQ(break_aspect_get_u32(fixture.remote_a, object, 2u, &health_a), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_aspect_get_u32(fixture.remote_b, object, 2u, &health_b), BREAK_RUNTIME_OK);
    ASSERT_EQ(health_a, 7u);
    ASSERT_EQ(health_b, 1u);
    ASSERT_EQ(break_aspect_replication_sync(fixture.replication, 2u, &aoi, 1024u),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(fixture.sink.count, 2u);
    ASSERT_EQ(fixture.sink.records[1].connection, 2u);
    offset = 1u;
    ASSERT_TRUE(consume_one_packet(&fixture.sink, 2u, &offset, fixture.remote_b, NULL));
    ASSERT_EQ(break_aspect_get_u32(fixture.remote_b, object, 2u, &health_b), BREAK_RUNTIME_OK);
    ASSERT_EQ(health_b, 7u);
    ASSERT_EQ(break_aspect_replication_sync(fixture.replication, 1u, &aoi, 1024u),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(fixture.sink.count, 2u);
    break_aoi_scope_clear(&scope);
    break_aoi_result_clear(&aoi);
    fixture_dispose(&fixture);
}

TEST(aspect_replication_budget_priority_and_send_failure_retry)
{
    ReplFixture fixture;
    BreakOnlineHandle low;
    BreakOnlineHandle high;
    BreakAoIResult aoi = {0};
    BreakAoIScope scope = {0};
    BreakWitness witness;
    BreakAoIEntityId ids[2];
    ASSERT_TRUE(fixture_init(&fixture));
    low = register_object(&fixture, 1u, BREAK_AOI_OBJECT_ALWAYS_RELEVANT);
    high = register_object(&fixture, 10u, BREAK_AOI_OBJECT_ALWAYS_RELEVANT);
    ASSERT_TRUE(adopt_remote(fixture.remote_a, low));
    ASSERT_TRUE(adopt_remote(fixture.remote_a, high));
    ASSERT_EQ(break_aspect_replication_set_u32(fixture.replication, low, 2u, 1u),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(break_aspect_replication_set_u32(fixture.replication, high, 2u, 2u),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(break_aspect_connection_open(fixture.replication, 1u, 1024u, 512u),
              BREAK_RUNTIME_OK);
    memset(&witness, 0, sizeof(witness));
    witness.radius = 10.0f;
    witness.connection_id = 1u;
    ASSERT_TRUE(break_aoi_compute(fixture.index, &witness, 1u, NULL, &aoi));
    ASSERT_EQ(aoi.enter_count, 2u);
    ASSERT_EQ(aoi.enter[0], break_aspect_aoi_id(high));
    ASSERT_EQ(break_aspect_replication_sync(fixture.replication, 1u, &aoi, 1u),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(fixture.sink.count, 0u);
    ASSERT_EQ(break_aspect_replication_sync(fixture.replication, 1u, &aoi, 25u),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(fixture.sink.count, 1u);
    ASSERT_TRUE(consume_all(&fixture.sink, 1u, fixture.remote_a));
    {
        u32 high_health = 0u;
        u32 low_health = 99u;
        ASSERT_EQ(break_aspect_get_u32(fixture.remote_a, high, 2u, &high_health), BREAK_RUNTIME_OK);
        ASSERT_EQ(high_health, 2u);
        ASSERT_EQ(break_aspect_get_u32(fixture.remote_a, low, 2u, &low_health), BREAK_RUNTIME_FAILED);
        ASSERT_EQ(low_health, 99u);
    }
    sink_reset(&fixture.sink);
    ASSERT_EQ(break_aspect_replication_sync(fixture.replication, 1u, &aoi, 1024u),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(fixture.sink.count, 1u);
    ASSERT_TRUE(consume_all(&fixture.sink, 1u, fixture.remote_a));
    ids[0] = break_aspect_aoi_id(high);
    ids[1] = break_aspect_aoi_id(low);
    ASSERT_TRUE(break_aoi_scope_assign(&scope, ids, 2u));
    break_aoi_result_clear(&aoi);
    ASSERT_TRUE(break_aoi_compute(fixture.index, &witness, 1u, &scope, &aoi));
    ASSERT_EQ(break_aspect_replication_set_u32(fixture.replication, high, 2u, 9u),
              BREAK_RUNTIME_OK);
    sink_reset(&fixture.sink);
    fixture.sink.fail_connection = 1u;
    ASSERT_EQ(break_aspect_replication_sync(fixture.replication, 1u, &aoi, 1024u),
              BREAK_RUNTIME_OVERLOAD);
    ASSERT_EQ(fixture.sink.count, 0u);
    ASSERT_EQ(fixture.sink.failures, 1u);
    ASSERT_EQ(break_aspect_replication_sync(fixture.replication, 1u, &aoi, 1024u),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(fixture.sink.count, 1u);
    ASSERT_TRUE(consume_all(&fixture.sink, 1u, fixture.remote_a));
    {
        u32 high_health = 0u;
        ASSERT_EQ(break_aspect_get_u32(fixture.remote_a, high, 2u, &high_health), BREAK_RUNTIME_OK);
        ASSERT_EQ(high_health, 9u);
    }
    break_aoi_scope_clear(&scope);
    break_aoi_result_clear(&aoi);
    fixture_dispose(&fixture);
}

TEST(aspect_replication_fragments_leave_and_disconnect)
{
    ReplFixture fixture;
    BreakOnlineHandle object;
    BreakAoIResult aoi = {0};
    BreakAoIScope scope = {0};
    BreakWitness witness;
    BreakAoIEntityId id;
    u8 payload[220];
    u8 kind = 0u;
    usize offset;
    u32 i;
    ASSERT_TRUE(fixture_init(&fixture));
    object = register_object(&fixture, 5u, BREAK_AOI_OBJECT_ALWAYS_RELEVANT);
    ASSERT_TRUE(adopt_remote(fixture.remote_a, object));
    for (i = 0u; i < sizeof(payload); ++i) payload[i] = (u8)(i & 0xffu);
    ASSERT_EQ(break_aspect_replication_set_bytes(fixture.replication, object, 3u,
                                                 payload, sizeof(payload)), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_aspect_connection_open(fixture.replication, 1u, 1024u, 32u),
              BREAK_RUNTIME_OK);
    memset(&witness, 0, sizeof(witness));
    witness.radius = 10.0f;
    witness.connection_id = 1u;
    ASSERT_TRUE(break_aoi_compute(fixture.index, &witness, 1u, NULL, &aoi));
    ASSERT_EQ(break_aspect_replication_sync(fixture.replication, 1u, &aoi, 1024u),
              BREAK_RUNTIME_OK);
    ASSERT_TRUE(fixture.sink.count > 2u);
    ASSERT_TRUE(consume_all(&fixture.sink, 1u, fixture.remote_a));
    {
        u8 remote_payload[220];
        u32 remote_size = 0u;
        ASSERT_EQ(break_aspect_get_bytes(fixture.remote_a, object, 3u,
                                         remote_payload, sizeof(remote_payload), &remote_size),
                  BREAK_RUNTIME_OK);
        ASSERT_EQ(remote_size, sizeof(payload));
        ASSERT_TRUE(memcmp(remote_payload, payload, sizeof(payload)) == 0);
    }
    id = break_aspect_aoi_id(object);
    ASSERT_TRUE(break_aoi_scope_assign(&scope, &id, 1u));
    ASSERT_EQ(break_aspect_replication_set_flags(fixture.replication, object,
                                                 BREAK_AOI_OBJECT_ALWAYS_RELEVANT |
                                                 BREAK_AOI_OBJECT_DORMANT), BREAK_RUNTIME_OK);
    break_aoi_result_clear(&aoi);
    ASSERT_TRUE(break_aoi_compute(fixture.index, &witness, 1u, &scope, &aoi));
    ASSERT_EQ(aoi.leave_count, 1u);
    sink_reset(&fixture.sink);
    ASSERT_EQ(break_aspect_replication_sync(fixture.replication, 1u, &aoi, 1024u),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(fixture.sink.count, 1u);
    offset = 0u;
    ASSERT_TRUE(consume_one_packet(&fixture.sink, 1u, &offset, fixture.remote_a, &kind));
    ASSERT_EQ(kind, BREAK_ASPECT_DORMANT);
    ASSERT_EQ(break_aspect_active_mask(fixture.remote_a, object), 0u);
    ASSERT_EQ(break_aspect_replication_disconnect(fixture.replication, 1u), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_aspect_replication_connection_count(fixture.replication), 0u);
    ASSERT_EQ(break_aspect_replication_disconnect(fixture.replication, 1u), BREAK_RUNTIME_STALE);
    break_aoi_scope_clear(&scope);
    break_aoi_result_clear(&aoi);
    fixture_dispose(&fixture);
}

TEST(aspect_replication_second_fragment_failure_completes_persistent_reassembler)
{
    ReplFixture fixture;
    BreakOnlineHandle object;
    BreakAoIResult aoi = {0};
    BreakWitness witness;
    RecordedFragment first;
    BreakReplicationReassembler *reassembler;
    BreakReplicationReassemblyResult result;
    u8 payload[220];
    u8 *packet = NULL;
    usize packet_size = 0u;
    usize i;
    ASSERT_TRUE(fixture_init(&fixture));
    object = register_object(&fixture, 5u, BREAK_AOI_OBJECT_ALWAYS_RELEVANT);
    ASSERT_TRUE(adopt_remote(fixture.remote_a, object));
    for (i = 0u; i < sizeof(payload); ++i) payload[i] = (u8)i;
    ASSERT_EQ(break_aspect_replication_set_bytes(fixture.replication, object, 3u,
                                                 payload, sizeof(payload)), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_aspect_connection_open(fixture.replication, 1u, 1024u, 32u),
              BREAK_RUNTIME_OK);
    memset(&witness, 0, sizeof(witness));
    witness.radius = 10.0f;
    witness.connection_id = 1u;
    ASSERT_TRUE(break_aoi_compute(fixture.index, &witness, 1u, NULL, &aoi));
    fixture.sink.fail_at_call = 2u;
    ASSERT_EQ(break_aspect_replication_sync(fixture.replication, 1u, &aoi, 1024u),
              BREAK_RUNTIME_OVERLOAD);
    ASSERT_EQ(fixture.sink.count, 1u);
    first = fixture.sink.records[0];
    reassembler = break_replication_reassembler_create(first.meta.base_id);
    ASSERT_NOT_NULL(reassembler);
    ASSERT_EQ(break_replication_reassembler_push(reassembler, &first.meta,
                                                 &packet, &packet_size),
              BREAK_REPLICATION_REASSEMBLY_INCOMPLETE);
    sink_reset(&fixture.sink);
    ASSERT_EQ(break_aspect_replication_sync(fixture.replication, 1u, &aoi, 1024u),
              BREAK_RUNTIME_OK);
    ASSERT_TRUE(fixture.sink.count > 0u);
    result = BREAK_REPLICATION_REASSEMBLY_INCOMPLETE;
    for (i = 0u; i < fixture.sink.count; ++i) {
        result = break_replication_reassembler_push(reassembler,
            &fixture.sink.records[i].meta, &packet, &packet_size);
        if (result == BREAK_REPLICATION_REASSEMBLY_COMPLETE) break;
        ASSERT_EQ(result, BREAK_REPLICATION_REASSEMBLY_INCOMPLETE);
    }
    ASSERT_EQ(result, BREAK_REPLICATION_REASSEMBLY_COMPLETE);
    ASSERT_EQ(break_aspect_apply(fixture.remote_a, packet, packet_size), BREAK_RUNTIME_OK);
    {
        u8 remote_payload[220];
        u32 remote_size = 0u;
        ASSERT_EQ(break_aspect_get_bytes(fixture.remote_a, object, 3u,
                                         remote_payload, sizeof(remote_payload), &remote_size),
                  BREAK_RUNTIME_OK);
        ASSERT_EQ(remote_size, sizeof(payload));
        ASSERT_TRUE(memcmp(remote_payload, payload, sizeof(payload)) == 0);
    }
    break_replication_reassembly_free(packet);
    break_replication_reassembler_destroy(reassembler);
    break_aoi_result_clear(&aoi);
    fixture_dispose(&fixture);
}

TEST(aspect_replication_leave_retries_with_empty_aoi_after_budget)
{
    ReplFixture fixture;
    BreakOnlineHandle object;
    BreakAoIScope scope = {0};
    BreakAoIResult aoi = {0};
    usize offset;
    u8 kind = 0u;
    ASSERT_TRUE(prepare_pending_leave(&fixture, &object, &scope, &aoi));
    ASSERT_EQ(break_aspect_replication_sync(fixture.replication, 1u, &aoi, 0u),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(fixture.sink.count, 0u);
    break_aoi_result_clear(&aoi);
    ASSERT_EQ(break_aspect_replication_sync(fixture.replication, 1u, &aoi, 1024u),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(fixture.sink.count, 1u);
    offset = 0u;
    ASSERT_TRUE(consume_one_packet(&fixture.sink, 1u, &offset, fixture.remote_a, &kind));
    ASSERT_EQ(kind, BREAK_ASPECT_DORMANT);
    break_aoi_scope_clear(&scope);
    fixture_dispose(&fixture);
}

TEST(aspect_replication_leave_retries_with_empty_aoi_after_send_failure)
{
    ReplFixture fixture;
    BreakOnlineHandle object;
    BreakAoIScope scope = {0};
    BreakAoIResult aoi = {0};
    usize offset;
    u8 kind = 0u;
    ASSERT_TRUE(prepare_pending_leave(&fixture, &object, &scope, &aoi));
    fixture.sink.fail_connection = 1u;
    ASSERT_EQ(break_aspect_replication_sync(fixture.replication, 1u, &aoi, 1024u),
              BREAK_RUNTIME_OVERLOAD);
    ASSERT_EQ(fixture.sink.count, 0u);
    break_aoi_result_clear(&aoi);
    ASSERT_EQ(break_aspect_replication_sync(fixture.replication, 1u, &aoi, 1024u),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(fixture.sink.count, 1u);
    offset = 0u;
    ASSERT_TRUE(consume_one_packet(&fixture.sink, 1u, &offset, fixture.remote_a, &kind));
    ASSERT_EQ(kind, BREAK_ASPECT_DORMANT);
    break_aoi_scope_clear(&scope);
    fixture_dispose(&fixture);
}

TEST(aspect_replication_leave_reentry_and_out_of_order_control)
{
    ReplFixture fixture;
    BreakOnlineHandle object;
    BreakAoIScope scope = {0};
    BreakAoIResult aoi = {0};
    BreakWitness witness;
    BreakAoIEntityId id;
    usize offset;
    u8 kind = 0u;
    u8 old_control[64];
    usize old_control_size = 0u;
    u32 health = 0u;
    ASSERT_TRUE(fixture_init(&fixture));
    object = register_object(&fixture, 5u, BREAK_AOI_OBJECT_ALWAYS_RELEVANT);
    ASSERT_TRUE(adopt_remote(fixture.remote_a, object));
    ASSERT_EQ(break_aspect_replication_set_u32(fixture.replication, object, 2u, 1u),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(break_aspect_connection_open(fixture.replication, 1u, 1024u, 32u),
              BREAK_RUNTIME_OK);
    memset(&witness, 0, sizeof(witness));
    witness.radius = 10.0f;
    witness.connection_id = 1u;
    ASSERT_TRUE(break_aoi_compute(fixture.index, &witness, 1u, NULL, &aoi));
    ASSERT_EQ(break_aspect_replication_sync(fixture.replication, 1u, &aoi, 1024u),
              BREAK_RUNTIME_OK);
    offset = 0u;
    ASSERT_TRUE(consume_one_packet(&fixture.sink, 1u, &offset, fixture.remote_a, &kind));
    ASSERT_EQ(kind, BREAK_ASPECT_BASELINE);
    id = break_aspect_aoi_id(object);
    ASSERT_TRUE(break_aoi_scope_assign(&scope, &id, 1u));
    ASSERT_EQ(break_aspect_replication_set_flags(fixture.replication, object, 0u),
              BREAK_RUNTIME_OK);
    witness.position[0] = 100.0f;
    witness.radius = 0.0f;
    break_aoi_result_clear(&aoi);
    ASSERT_TRUE(break_aoi_compute(fixture.index, &witness, 1u, &scope, &aoi));
    ASSERT_EQ(aoi.leave_count, 1u);
    witness.position[0] = 0.0f;
    witness.radius = 10.0f;
    sink_reset(&fixture.sink);
    ASSERT_EQ(break_aspect_replication_sync(fixture.replication, 1u, &aoi, 1024u),
              BREAK_RUNTIME_OK);
    offset = 0u;
    ASSERT_TRUE(consume_one_packet(&fixture.sink, 1u, &offset, fixture.remote_a, &kind));
    ASSERT_EQ(kind, BREAK_ASPECT_DESTROY);
    ASSERT_EQ(break_aspect_replication_set_flags(fixture.replication, object,
                                                 BREAK_AOI_OBJECT_ALWAYS_RELEVANT),
              BREAK_RUNTIME_OK);
    break_aoi_result_clear(&aoi);
    ASSERT_TRUE(break_aoi_compute(fixture.index, &witness, 1u, &scope, &aoi));
    sink_reset(&fixture.sink);
    ASSERT_EQ(break_aspect_replication_sync(fixture.replication, 1u, &aoi, 1024u),
              BREAK_RUNTIME_OK);
    offset = 0u;
    ASSERT_TRUE(consume_one_packet(&fixture.sink, 1u, &offset, fixture.remote_a, &kind));
    ASSERT_EQ(kind, BREAK_ASPECT_BASELINE);
    ASSERT_EQ(break_aspect_replication_set_flags(fixture.replication, object,
        BREAK_AOI_OBJECT_ALWAYS_RELEVANT | BREAK_AOI_OBJECT_DORMANT), BREAK_RUNTIME_OK);
    break_aoi_result_clear(&aoi);
    ASSERT_TRUE(break_aoi_compute(fixture.index, &witness, 1u, &scope, &aoi));
    sink_reset(&fixture.sink);
    ASSERT_EQ(break_aspect_replication_sync(fixture.replication, 1u, &aoi, 1024u),
              BREAK_RUNTIME_OK);
    offset = 0u;
    ASSERT_TRUE(consume_one_packet(&fixture.sink, 1u, &offset, fixture.remote_a, &kind));
    ASSERT_EQ(kind, BREAK_ASPECT_DORMANT);
    ASSERT_EQ(break_aspect_replication_set_flags(fixture.replication, object,
                                                 BREAK_AOI_OBJECT_ALWAYS_RELEVANT),
              BREAK_RUNTIME_OK);
    break_aoi_result_clear(&aoi);
    ASSERT_TRUE(break_aoi_compute(fixture.index, &witness, 1u, &scope, &aoi));
    sink_reset(&fixture.sink);
    ASSERT_EQ(break_aspect_replication_sync(fixture.replication, 1u, &aoi, 1024u),
              BREAK_RUNTIME_OK);
    offset = 0u;
    ASSERT_TRUE(consume_one_packet(&fixture.sink, 1u, &offset, fixture.remote_a, &kind));
    ASSERT_EQ(kind, BREAK_ASPECT_BASELINE);
    ASSERT_EQ(break_aspect_get_u32(fixture.remote_a, object, 2u, &health), BREAK_RUNTIME_OK);
    ASSERT_EQ(health, 1u);
    ASSERT_EQ(break_aspect_encode_with_epoch(fixture.store, object, 0u, BREAK_ASPECT_DORMANT,
                                  2u, old_control, sizeof(old_control), &old_control_size),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(break_aspect_apply(fixture.remote_a, old_control, old_control_size),
              BREAK_RUNTIME_STALE);
    break_aoi_scope_clear(&scope);
    break_aoi_result_clear(&aoi);
    fixture_dispose(&fixture);
}

TEST_MAIN_BEGIN()
    RUN_TEST(aspect_replication_baselines_and_per_connection_dirty_masks);
    RUN_TEST(aspect_replication_budget_priority_and_send_failure_retry);
    RUN_TEST(aspect_replication_fragments_leave_and_disconnect);
    RUN_TEST(aspect_replication_second_fragment_failure_completes_persistent_reassembler);
    RUN_TEST(aspect_replication_leave_retries_with_empty_aoi_after_budget);
    RUN_TEST(aspect_replication_leave_retries_with_empty_aoi_after_send_failure);
    RUN_TEST(aspect_replication_leave_reentry_and_out_of_order_control);
TEST_MAIN_END()
