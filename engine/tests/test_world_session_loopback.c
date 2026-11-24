#include "test_framework.h"

#include <ecs/world_session.h>
#include <network/break_net_envelope.h>
#include <network/break_net_message_registry.h>
#include <network/break_replication_wire.h>
#include <network/break_session.h>
#include <snow/acceptor.h>
#include <snow/endpoint.h>

#include <arpa/inet.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

extern int usleep(unsigned int);

#define TEST_COMPONENT 11u
#define TEST_PROTOCOL 1u
#define TEST_LEVEL 7u

#define LOOPBACK_CHECK(x) do { \
    if (!(x)) { \
        printf("  FAIL: %s:%d: %s\n", __FILE__, __LINE__, #x); \
        g_test_fail++; \
        goto cleanup; \
    } \
} while (0)

typedef struct {
    u32 value;
} Value;

typedef struct {
    BreakComponentSchemaRegistry *schemas;
    World *authoritative;
    World *remote;
    BreakWorldSession *session;
    BreakNetReactor *reactor;
    SnowAcceptor *acceptor;
    BreakSessionManager *manager;
    BreakNetMessageRegistry registry;
    BreakConnectionKey connection;
    u64 now;
    u64 epoch;
    u32 sequence;
    usize auth_calls;
    int client_fd;
} SocketFixture;

static u64 test_clock(void *user)
{
    return *(const u64 *)user;
}

static void put16(u8 *out, u16 value)
{
    out[0] = (u8)value;
    out[1] = (u8)(value >> 8u);
}

static void put32(u8 *out, u32 value)
{
    out[0] = (u8)value;
    out[1] = (u8)(value >> 8u);
    out[2] = (u8)(value >> 16u);
    out[3] = (u8)(value >> 24u);
}

static bool write_all(int fd, const void *data, usize size)
{
    const u8 *bytes = (const u8 *)data;
    usize offset = 0u;
    while (offset < size) {
        ssize_t written = write(fd, bytes + offset, size - offset);
        if (written <= 0) return false;
        offset += (usize)written;
    }
    return true;
}

static bool auth_handler(BreakConnectionKey connection, const BreakNetOwnedMessage *message,
                         void *user_data)
{
    SocketFixture *fixture = (SocketFixture *)user_data;
    if (!message || message->message_id != BREAK_NET_MESSAGE_ID_AUTH) return false;
    fixture->connection = connection;
    fixture->auth_calls++;
    return true;
}

static bool reactor_start(SocketFixture *fixture)
{
    BreakNetReactorConfig config = {BREAK_NET_DRIVE_STEP, 0, 4u, 1000, 1000u, 1u};
    SnowEndpoint *endpoint = NULL;
    if (SnowEndpointCreate(&endpoint) != SNOW_OK ||
        SnowEndpointSetHost(endpoint, "127.0.0.1") != SNOW_OK ||
        SnowEndpointSetPort(endpoint, 0) != SNOW_OK ||
        SnowAcceptorCreate(endpoint, &fixture->acceptor) != SNOW_OK) {
        SnowEndpointDestroy(endpoint);
        return false;
    }
    SnowEndpointDestroy(endpoint);
    if (SnowAcceptorBind(fixture->acceptor, 1) != SNOW_OK) return false;
    fixture->reactor = break_net_reactor_create(&config);
    return fixture->reactor &&
           break_net_reactor_set_acceptor(fixture->reactor, fixture->acceptor) &&
           break_net_reactor_start(fixture->reactor);
}

static bool pump(SocketFixture *fixture)
{
    bool stepped = break_net_reactor_step(fixture->reactor, 1);
    (void)break_session_manager_poll_adapter(fixture->manager, 64u);
    return stepped;
}

static void socket_dispose(SocketFixture *fixture)
{
    if (fixture->client_fd >= 0) {
        close(fixture->client_fd);
        fixture->client_fd = -1;
    }
    if (fixture->manager && fixture->reactor && fixture->connection != 0u) {
        for (usize i = 0u; i < 1000u &&
             break_session_manager_state(fixture->manager, fixture->connection) !=
                 BREAK_SESSION_CLOSED; ++i) {
            if (!pump(fixture)) break;
            usleep(1000u);
        }
        (void)break_session_manager_poll(fixture->manager, 64u);
    }
    break_world_session_destroy(fixture->session);
    break_session_manager_destroy(fixture->manager);
    if (fixture->reactor) {
        (void)break_net_reactor_stop(fixture->reactor, 1000u);
        break_net_reactor_destroy(fixture->reactor);
    }
    if (fixture->acceptor) SnowAcceptorDestroy(fixture->acceptor);
    world_destroy(fixture->remote);
    world_destroy(fixture->authoritative);
    break_schema_registry_destroy(fixture->schemas);
    memset(fixture, 0, sizeof(*fixture));
    fixture->client_fd = -1;
}

static bool socket_start(SocketFixture *fixture, bool include_delta)
{
    BreakComponentSchema schema;
    BreakWorldSessionConfig world_config;
    BreakSessionConfig session_config;
    memset(fixture, 0, sizeof(*fixture));
    fixture->client_fd = -1;
    memset(&schema, 0, sizeof(schema));
    schema.component_id = TEST_COMPONENT;
    schema.version = 1u;
    schema.size = sizeof(Value);
    schema.alignment = _Alignof(Value);
    schema.flags = BREAK_SCHEMA_FLAG_DETERMINISTIC_POD | BREAK_SCHEMA_FLAG_RAW_BYTES;
    fixture->schemas = break_schema_registry_create();
    fixture->authoritative = world_create();
    fixture->remote = world_create();
    if (!fixture->schemas || !fixture->authoritative || !fixture->remote ||
        break_schema_register(fixture->schemas, &schema) != BREAK_SCHEMA_OK ||
        !reactor_start(fixture)) {
        return false;
    }
    world_register_component(fixture->authoritative, TEST_COMPONENT, sizeof(Value));
    world_register_component(fixture->remote, TEST_COMPONENT, sizeof(Value));

    fixture->registry = *break_net_message_registry_default();
    if (!include_delta) {
        for (usize i = 0u; i < fixture->registry.count; ++i) {
            if (fixture->registry.definitions[i].message_id ==
                BREAK_NET_MESSAGE_ID_WORLD_DELTA) {
                memmove(&fixture->registry.definitions[i],
                        &fixture->registry.definitions[i + 1u],
                        (fixture->registry.count - i - 1u) *
                            sizeof(fixture->registry.definitions[0]));
                fixture->registry.count--;
                memset(&fixture->registry.definitions[fixture->registry.count], 0,
                       sizeof(fixture->registry.definitions[0]));
                break;
            }
        }
    }
    memset(&session_config, 0, sizeof(session_config));
    session_config.registry = &fixture->registry;
    fixture->manager = break_session_manager_create(&session_config);

    memset(&world_config, 0, sizeof(world_config));
    world_config.schemas = fixture->schemas;
    world_config.protocol_version = TEST_PROTOCOL;
    world_config.level_generation = TEST_LEVEL;
    world_config.bridge.reactor = fixture->reactor;
    world_config.bridge.max_connections = 1u;
    world_config.bridge.stream_capacity = 8u;
    world_config.bridge.max_pending_bytes_per_connection = 8192u;
    world_config.bridge.max_total_pending_bytes = 8192u;
    world_config.bridge.max_fragment_bytes = 64u;
    world_config.bridge.max_fragment_count = 64u;
    world_config.bridge.completion_capacity = 8u;
    world_config.bridge.max_completion_packet_bytes = 8192u;
    world_config.bridge.max_completion_queue_bytes = 16384u;
    world_config.bridge.clock = test_clock;
    world_config.bridge.clock_user = &fixture->now;
    world_config.need_full_tick_interval = 1u;
    fixture->session = break_world_session_create(&world_config);
    fixture->epoch = break_world_session_stream_epoch(
        TEST_PROTOCOL, break_schema_hash(fixture->schemas), TEST_LEVEL);
    if (!fixture->manager || !fixture->session ||
        !break_session_manager_attach_reactor(fixture->manager, fixture->reactor) ||
        !break_session_manager_set_message_handler(
            fixture->manager, BREAK_NET_MESSAGE_ID_AUTH, auth_handler, fixture) ||
        !break_session_manager_set_message_handler(
            fixture->manager, BREAK_NET_MESSAGE_ID_WORLD_CONTROL,
            break_world_session_handle_control, fixture->session)) {
        return false;
    }
    if (include_delta &&
        !break_session_manager_set_message_handler(
            fixture->manager, BREAK_NET_MESSAGE_ID_WORLD_DELTA,
            break_replication_session_handle_message,
            break_world_session_bridge(fixture->session))) {
        return false;
    }
    return true;
}

static bool write_frame(SocketFixture *fixture, u16 message_id, const void *payload,
                        usize payload_size)
{
    u8 wire[BREAK_NET_ENVELOPE_HEADER_SIZE + 128u];
    if (payload_size > 128u || (payload_size != 0u && !payload)) return false;
    put32(wire, BREAK_NET_ENVELOPE_MAGIC);
    put16(wire + 4u, BREAK_NET_PROTOCOL_VERSION);
    put16(wire + 6u, message_id);
    put16(wire + 8u, 0u);
    put32(wire + 10u, fixture->sequence++);
    put32(wire + 14u, (u32)payload_size);
    if (payload_size != 0u)
        memcpy(wire + BREAK_NET_ENVELOPE_HEADER_SIZE, payload, payload_size);
    return write_all(fixture->client_fd, wire, BREAK_NET_ENVELOPE_HEADER_SIZE + payload_size);
}

static bool connect_authenticate(SocketFixture *fixture)
{
    static const u8 auth_payload[] = {'a', 'u', 't', 'h'};
    const SnowEndpoint *bound = SnowAcceptorEndpoint(fixture->acceptor);
    struct sockaddr_in address = {0};
    fixture->client_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fixture->client_fd < 0) return false;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    address.sin_port = htons((u16)SnowEndpointPort(bound));
    if (connect(fixture->client_fd, (const struct sockaddr *)&address,
                sizeof(address)) != 0) {
        return false;
    }
    fixture->sequence = 1u;
    if (!write_frame(fixture, BREAK_NET_MESSAGE_ID_AUTH,
                     auth_payload, sizeof(auth_payload))) {
        return false;
    }
    for (usize i = 0u; i < 5000u; ++i) {
        if (fixture->auth_calls == 1u && fixture->connection != 0u &&
            break_session_manager_state(fixture->manager, fixture->connection) ==
                BREAK_SESSION_AUTHENTICATED) {
            return break_world_session_open(fixture->session, fixture->connection);
        }
        if (!pump(fixture)) return false;
        usleep(1000u);
    }
    return false;
}

static bool write_fragment(SocketFixture *fixture, const BreakReplicationFragment *fragment)
{
    u8 wire[BREAK_REPLICATION_WIRE_HEADER_SIZE + 64u];
    usize wire_size = 0u;
    if (break_replication_wire_encode(fragment, wire, sizeof(wire), &wire_size) !=
        BREAK_REPLICATION_FRAGMENT_OK) {
        return false;
    }
    return write_frame(fixture, BREAK_NET_MESSAGE_ID_WORLD_DELTA, wire, wire_size);
}

static bool write_shuffled_payload(SocketFixture *fixture, u64 delta_id,
                                   const void *payload, usize payload_size)
{
    BreakReplicationFragment *fragments = NULL;
    usize count = 0u;
    bool ok = true;
    if (break_replication_fragment_payload(delta_id, fixture->epoch, payload, payload_size,
                                           17u, &fragments, &count) !=
            BREAK_REPLICATION_FRAGMENT_OK ||
        count < 2u) {
        break_replication_fragments_free(fragments, count);
        return false;
    }
    for (usize i = count; i-- > 0u && ok;) {
        ok = write_fragment(fixture, &fragments[i]);
        if (ok && i == count - 1u) ok = write_fragment(fixture, &fragments[i]);
    }
    break_replication_fragments_free(fragments, count);
    return ok;
}

static bool wait_completed(SocketFixture *fixture, u64 expected)
{
    for (usize i = 0u; i < 5000u; ++i) {
        BreakWorldSessionStats stats;
        break_world_session_stats(fixture->session, &stats);
        if (stats.bridge.completed_packets >= expected) return true;
        if (break_session_manager_state(fixture->manager, fixture->connection) ==
            BREAK_SESSION_CLOSED) {
            return false;
        }
        if (!pump(fixture)) return false;
        usleep(1000u);
    }
    return false;
}

static bool add_value(World *world, Entity entity, u32 value)
{
    Value *component = (Value *)world_add_component(world, entity, TEST_COMPONENT);
    if (!component) return false;
    component->value = value;
    return true;
}

static bool encode_message(BreakWorldDeltaWire *message, u8 **out_wire, usize *out_size)
{
    usize size = 0u;
    u8 *wire;
    bool ok;
    if (break_world_delta_wire_encoded_size(message, &size) != BREAK_WORLD_DELTA_WIRE_OK) {
        free(message->records);
        return false;
    }
    wire = (u8 *)malloc(size);
    if (!wire) {
        free(message->records);
        return false;
    }
    ok = break_world_delta_wire_encode(message, wire, size, &size) ==
         BREAK_WORLD_DELTA_WIRE_OK;
    free(message->records);
    if (!ok) {
        free(wire);
        return false;
    }
    *out_wire = wire;
    *out_size = size;
    return true;
}

static bool encode_full(const BreakWorldSnapshot *snapshot, u8 **out_wire, usize *out_size)
{
    BreakWorldDeltaWire message;
    usize entity_count = break_world_snapshot_entity_count(snapshot);
    usize count = 0u;
    usize slot = 0u;
    memset(&message, 0, sizeof(message));
    for (usize i = 0u; i < entity_count; ++i) {
        Entity entity = break_world_snapshot_entity_at(snapshot, i);
        ++count;
        for (u32 component = 0u; component < ECS_MAX_COMPONENTS; ++component) {
            const void *bytes = NULL;
            usize size = 0u;
            if (break_world_snapshot_component_bytes(snapshot, entity, component,
                                                      &bytes, &size)) {
                ++count;
            }
        }
    }
    if (count > UINT32_MAX) return false;
    message.kind = BREAK_WORLD_DELTA_WIRE_FULL;
    message.schema_hash = break_world_snapshot_schema_hash(snapshot);
    message.level_generation = TEST_LEVEL;
    message.target_snapshot_id = break_world_snapshot_id(snapshot);
    message.target_tick = break_world_snapshot_tick(snapshot);
    message.record_count = (u32)count;
    if (count != 0u) {
        message.records = (BreakWorldDeltaRecord *)calloc(count, sizeof(*message.records));
        if (!message.records) return false;
    }
    for (usize i = 0u; i < entity_count; ++i) {
        Entity entity = break_world_snapshot_entity_at(snapshot, i);
        message.records[slot].kind = BREAK_DELTA_ENTITY_CREATE;
        message.records[slot].entity = entity;
        ++slot;
        for (u32 component = 0u; component < ECS_MAX_COMPONENTS; ++component) {
            const void *bytes = NULL;
            usize size = 0u;
            if (break_world_snapshot_component_bytes(snapshot, entity, component,
                                                      &bytes, &size)) {
                message.records[slot].kind = BREAK_DELTA_COMPONENT_ADD;
                message.records[slot].entity = entity;
                message.records[slot].component = component;
                message.records[slot].bytes = bytes;
                message.records[slot].size = size;
                ++slot;
            }
        }
    }
    return encode_message(&message, out_wire, out_size);
}

static bool encode_delta(const BreakWorldSnapshot *base, const BreakWorldSnapshot *target,
                         u8 **out_wire, usize *out_size)
{
    BreakWorldDelta *delta = break_world_delta_diff(base, target);
    BreakWorldDeltaWire message;
    usize count;
    bool ok;
    if (!delta) return false;
    count = break_world_delta_record_count(delta);
    if (count > UINT32_MAX) {
        break_world_delta_release(delta);
        return false;
    }
    memset(&message, 0, sizeof(message));
    message.kind = BREAK_WORLD_DELTA_WIRE_DELTA;
    message.schema_hash = break_world_delta_target_schema_hash(delta);
    message.level_generation = TEST_LEVEL;
    message.base_snapshot_id = break_world_delta_base_id(delta);
    message.target_snapshot_id = break_world_delta_target_id(delta);
    message.base_tick = break_world_delta_base_tick(delta);
    message.target_tick = break_world_delta_target_tick(delta);
    message.record_count = (u32)count;
    if (count != 0u) {
        message.records = (BreakWorldDeltaRecord *)calloc(count, sizeof(*message.records));
        if (!message.records) {
            break_world_delta_release(delta);
            return false;
        }
        for (usize i = 0u; i < count; ++i) {
            if (!break_world_delta_record_at(delta, i, &message.records[i])) {
                free(message.records);
                break_world_delta_release(delta);
                return false;
            }
        }
    }
    ok = encode_message(&message, out_wire, out_size);
    break_world_delta_release(delta);
    return ok;
}

static bool remote_matches(SocketFixture *fixture, u64 tick, u64 expected_id)
{
    BreakWorldSnapshot *snapshot = break_world_snapshot_build(
        fixture->remote, fixture->schemas, tick);
    bool matches;
    if (!snapshot) return false;
    matches = break_world_snapshot_id(snapshot) == expected_id;
    break_world_snapshot_release(snapshot);
    return matches;
}

TEST(world_session_real_socket_reorders_duplicates_and_recovers_with_full)
{
    SocketFixture fixture;
    BreakWorldSnapshot *base = NULL;
    BreakWorldSnapshot *target = NULL;
    BreakWorldSnapshot *recovered = NULL;
    BreakWorldSessionControl control;
    BreakWorldSessionStats stats;
    Value *value;
    Entity entity;
    u8 *wire = NULL;
    usize size = 0u;

    memset(&fixture, 0, sizeof(fixture));
    fixture.client_fd = -1;
    LOOPBACK_CHECK(socket_start(&fixture, true));
    LOOPBACK_CHECK(connect_authenticate(&fixture));
    LOOPBACK_CHECK(fixture.auth_calls == 1u);
    entity = world_create_entity(fixture.authoritative);
    LOOPBACK_CHECK(add_value(fixture.authoritative, entity, 42u));
    base = break_world_snapshot_build(fixture.authoritative, fixture.schemas, 10u);
    LOOPBACK_CHECK(base != NULL);
    LOOPBACK_CHECK(encode_full(base, &wire, &size));
    LOOPBACK_CHECK(write_shuffled_payload(&fixture, 100u, wire, size));
    free(wire);
    wire = NULL;
    LOOPBACK_CHECK(wait_completed(&fixture, 1u));
    LOOPBACK_CHECK(break_world_entity_count(fixture.remote) == 0u);
    break_world_session_stats(fixture.session, &stats);
    LOOPBACK_CHECK(stats.bridge.duplicate_fragments >= 1u);
    LOOPBACK_CHECK(break_world_session_drain(fixture.session, fixture.connection,
                                             fixture.remote, 1u) == 1u);
    LOOPBACK_CHECK(remote_matches(&fixture, 10u, break_world_snapshot_id(base)));
    LOOPBACK_CHECK(break_world_session_poll_control(fixture.session, fixture.connection,
                                                    &control));
    LOOPBACK_CHECK(control.kind == BREAK_WORLD_SESSION_CONTROL_ACK);
    LOOPBACK_CHECK(control.delta_id == 100u);
    LOOPBACK_CHECK(control.target_snapshot_id == break_world_snapshot_id(base));
    LOOPBACK_CHECK(control.target_tick == 10u);

    value = (Value *)world_get_component(fixture.authoritative, entity, TEST_COMPONENT);
    LOOPBACK_CHECK(value != NULL);
    value->value = 43u;
    target = break_world_snapshot_build(fixture.authoritative, fixture.schemas, 20u);
    LOOPBACK_CHECK(target != NULL);
    size = 0u;
    LOOPBACK_CHECK(encode_delta(base, target, &wire, &size));
    wire[24] ^= 1u;
    LOOPBACK_CHECK(write_shuffled_payload(&fixture, 101u, wire, size));
    free(wire);
    wire = NULL;
    LOOPBACK_CHECK(wait_completed(&fixture, 2u));
    LOOPBACK_CHECK(break_world_session_drain(fixture.session, fixture.connection,
                                             fixture.remote, 1u) == 1u);
    LOOPBACK_CHECK(remote_matches(&fixture, 10u, break_world_snapshot_id(base)));
    LOOPBACK_CHECK(break_world_session_poll_control(fixture.session, fixture.connection,
                                                    &control));
    LOOPBACK_CHECK(control.kind == BREAK_WORLD_SESSION_CONTROL_NEED_FULL);
    LOOPBACK_CHECK(control.target_snapshot_id == break_world_snapshot_id(base));
    LOOPBACK_CHECK(control.target_tick == 10u);

    value->value = 44u;
    recovered = break_world_snapshot_build(fixture.authoritative, fixture.schemas, 30u);
    LOOPBACK_CHECK(recovered != NULL);
    size = 0u;
    LOOPBACK_CHECK(encode_full(recovered, &wire, &size));
    LOOPBACK_CHECK(write_shuffled_payload(&fixture, 102u, wire, size));
    free(wire);
    wire = NULL;
    LOOPBACK_CHECK(wait_completed(&fixture, 3u));
    LOOPBACK_CHECK(break_world_session_drain(fixture.session, fixture.connection,
                                             fixture.remote, 1u) == 1u);
    LOOPBACK_CHECK(remote_matches(&fixture, 30u, break_world_snapshot_id(recovered)));
    break_world_session_stats(fixture.session, &stats);
    LOOPBACK_CHECK(stats.applied_packets == 2u);
    LOOPBACK_CHECK(stats.need_full_packets == 1u);
    LOOPBACK_CHECK(stats.rejected_packets == 1u);
    LOOPBACK_CHECK(stats.drained_packets == 3u);

cleanup:
    free(wire);
    break_world_snapshot_release(recovered);
    break_world_snapshot_release(target);
    break_world_snapshot_release(base);
    socket_dispose(&fixture);
}

static void check_registry_control(bool include_delta)
{
    SocketFixture fixture;
    BreakWorldSnapshot *target = NULL;
    BreakSessionApplyStats session_stats;
    BreakWorldSessionStats world_stats;
    Entity entity;
    u8 *wire = NULL;
    usize size = 0u;

    memset(&fixture, 0, sizeof(fixture));
    fixture.client_fd = -1;
    LOOPBACK_CHECK(socket_start(&fixture, include_delta));
    LOOPBACK_CHECK(connect_authenticate(&fixture));
    entity = world_create_entity(fixture.authoritative);
    LOOPBACK_CHECK(add_value(fixture.authoritative, entity, 5u));
    target = break_world_snapshot_build(fixture.authoritative, fixture.schemas, 5u);
    LOOPBACK_CHECK(target != NULL);
    LOOPBACK_CHECK(encode_full(target, &wire, &size));
    LOOPBACK_CHECK(write_shuffled_payload(&fixture, 1u, wire, size));
    free(wire);
    wire = NULL;
    if (include_delta) {
        LOOPBACK_CHECK(wait_completed(&fixture, 1u));
        LOOPBACK_CHECK(break_world_session_drain(fixture.session, fixture.connection,
                                                 fixture.remote, 1u) == 1u);
        LOOPBACK_CHECK(remote_matches(&fixture, 5u, break_world_snapshot_id(target)));
    } else {
        for (usize i = 0u; i < 5000u; ++i) {
            break_session_manager_apply_stats(fixture.manager, &session_stats);
            if (session_stats.invalid != 0u) break;
            LOOPBACK_CHECK(pump(&fixture));
            usleep(1000u);
        }
        break_session_manager_apply_stats(fixture.manager, &session_stats);
        LOOPBACK_CHECK(session_stats.invalid == 1u);
        break_world_session_stats(fixture.session, &world_stats);
        LOOPBACK_CHECK(world_stats.bridge.completed_packets == 0u);
        LOOPBACK_CHECK(break_world_entity_count(fixture.remote) == 0u);
    }

cleanup:
    free(wire);
    break_world_snapshot_release(target);
    socket_dispose(&fixture);
}

TEST(world_session_registry_without_delta_fails_then_restores)
{
    check_registry_control(false);
    check_registry_control(true);
}

TEST_MAIN_BEGIN()
    RUN_TEST(world_session_real_socket_reorders_duplicates_and_recovers_with_full);
    RUN_TEST(world_session_registry_without_delta_fails_then_restores);
TEST_MAIN_END()
