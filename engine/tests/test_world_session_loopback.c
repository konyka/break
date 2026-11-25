#include "test_framework.h"

#include <core/platform_thread.h>
#include <ecs/world_session.h>
#include <ecs/world_snapshot_publication.h>
#include <network/break_net_envelope.h>
#include <network/break_net_message_registry.h>
#include <network/break_replication_wire.h>
#include <network/break_session.h>
#include <runtime/runtime_world_session.h>
#include <snow/acceptor.h>
#include <snow/endpoint.h>

#include <arpa/inet.h>
#include <errno.h>
#include <poll.h>
#include <stdatomic.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

extern int usleep(unsigned int);

#define TEST_COMPONENT 11u
#define TEST_PROTOCOL 1u
#define TEST_LEVEL 7u
#define TEST_DUAL_OUTBOUND_SHARE (BREAK_NET_OUTBOUND_QUEUE_CAPACITY / 2u)

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
    u16 message_id;
    u16 protocol_version;
    u16 flags;
    u32 sequence;
    u64 correlation_id;
    usize payload_size;
    u8 payload[128u];
} SocketFrame;

typedef struct {
    u64 delta_id;
    BreakWorldDeltaWireKind kind;
    u64 base_snapshot_id;
    u64 target_snapshot_id;
    u64 target_tick;
    u64 level_generation;
    usize fragment_count;
} SocketAttempt;

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
    BreakConnectionKey inactive_connection;
    World *remote_secondary;
    u64 now;
    u64 epoch;
    u32 sequence;
    u32 inactive_sequence;
    usize auth_calls;
    int client_fd;
    int inactive_client_fd;
    bool active_secondary;
    bool fair_outbound_admission;
    BreakRuntimeBus *bus;                   /* owned; NULL for adapter-free tests */
    BreakRuntimeWorldSession *adapter;      /* owned; NULL for adapter-free tests */
    BreakWorldSnapshotPublication *publication; /* owned; NULL disables */
    u64 adapter_epoch;                      /* active connection adapter epoch */
    u64 inactive_adapter_epoch;             /* inactive connection adapter epoch */
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

static void put64(u8 *out, u64 value)
{
    for (u32 i = 0u; i < 8u; ++i) out[i] = (u8)(value >> (i * 8u));
}

static u16 get16(const u8 *bytes)
{
    return (u16)bytes[0] | ((u16)bytes[1] << 8u);
}

static u32 get32(const u8 *bytes)
{
    return (u32)bytes[0] | ((u32)bytes[1] << 8u) |
           ((u32)bytes[2] << 16u) | ((u32)bytes[3] << 24u);
}

static u64 get64(const u8 *bytes)
{
    u64 value = 0u;
    for (u32 i = 0u; i < 8u; ++i) value |= (u64)bytes[i] << (i * 8u);
    return value;
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
    BreakNetReactorConfig config = {
        BREAK_NET_DRIVE_STEP, 0, 4u, 1000, 1000u, 1u, fixture->fair_outbound_admission
    };
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

static void socket_select_peer(SocketFixture *fixture, bool secondary)
{
    BreakConnectionKey connection;
    u32 sequence;
    int client_fd;
    u64 adapter_epoch;
    if (fixture->active_secondary == secondary) return;
    connection = fixture->connection;
    sequence = fixture->sequence;
    client_fd = fixture->client_fd;
    adapter_epoch = fixture->adapter_epoch;
    fixture->connection = fixture->inactive_connection;
    fixture->sequence = fixture->inactive_sequence;
    fixture->client_fd = fixture->inactive_client_fd;
    fixture->adapter_epoch = fixture->inactive_adapter_epoch;
    fixture->inactive_connection = connection;
    fixture->inactive_sequence = sequence;
    fixture->inactive_client_fd = client_fd;
    fixture->inactive_adapter_epoch = adapter_epoch;
    fixture->active_secondary = secondary;
}

static void socket_dispose(SocketFixture *fixture)
{
    if (fixture->client_fd >= 0) {
        close(fixture->client_fd);
        fixture->client_fd = -1;
    }
    if (fixture->inactive_client_fd >= 0) {
        close(fixture->inactive_client_fd);
        fixture->inactive_client_fd = -1;
    }
    if (fixture->manager && fixture->reactor) {
        for (usize i = 0u; i < 1000u; ++i) {
            bool active_closed = fixture->connection == 0u ||
                break_session_manager_state(fixture->manager, fixture->connection) ==
                    BREAK_SESSION_CLOSED;
            bool inactive_closed = fixture->inactive_connection == 0u ||
                break_session_manager_state(fixture->manager, fixture->inactive_connection) ==
                    BREAK_SESSION_CLOSED;
            if (active_closed && inactive_closed) break;
            if (!pump(fixture)) break;
            usleep(1000u);
        }
        (void)break_session_manager_poll(fixture->manager, 64u);
    }
    if (fixture->adapter) {
        break_runtime_world_session_close(fixture->adapter);
        for (u32 i = 0u; i < 1024u &&
                 break_runtime_world_session_pending(fixture->adapter) != 0u; ++i) {
            usize drained = 0u;
            (void)break_runtime_world_session_drain(fixture->adapter, 256u, &drained);
        }
        (void)break_runtime_world_session_destroy(fixture->adapter);
        fixture->adapter = NULL;
    }
    if (fixture->publication) {
        break_world_snapshot_publication_close(fixture->publication);
        break_world_snapshot_publication_destroy(fixture->publication);
        fixture->publication = NULL;
    }
    if (fixture->bus) {
        break_runtime_bus_destroy(fixture->bus);
        fixture->bus = NULL;
    }
    break_world_session_destroy(fixture->session);
    break_session_manager_destroy(fixture->manager);
    if (fixture->reactor) {
        (void)break_net_reactor_stop(fixture->reactor, 1000u);
        break_net_reactor_destroy(fixture->reactor);
    }
    if (fixture->acceptor) SnowAcceptorDestroy(fixture->acceptor);
    world_destroy(fixture->remote_secondary);
    world_destroy(fixture->remote);
    world_destroy(fixture->authoritative);
    break_schema_registry_destroy(fixture->schemas);
    memset(fixture, 0, sizeof(*fixture));
    fixture->client_fd = -1;
    fixture->inactive_client_fd = -1;
}

static bool socket_start_with_connections(SocketFixture *fixture, bool include_delta,
                                          usize max_connections)
{
    BreakComponentSchema schema;
    BreakWorldSessionConfig world_config;
    BreakSessionConfig session_config;
    bool fair_outbound_admission = fixture->fair_outbound_admission;
    memset(fixture, 0, sizeof(*fixture));
    fixture->fair_outbound_admission = fair_outbound_admission;
    fixture->client_fd = -1;
    fixture->inactive_client_fd = -1;
    memset(&schema, 0, sizeof(schema));
    schema.component_id = TEST_COMPONENT;
    schema.version = 1u;
    schema.size = sizeof(Value);
    schema.alignment = _Alignof(Value);
    schema.flags = BREAK_SCHEMA_FLAG_DETERMINISTIC_POD | BREAK_SCHEMA_FLAG_RAW_BYTES;
    fixture->schemas = break_schema_registry_create();
    fixture->authoritative = world_create();
    fixture->remote = world_create();
    if (max_connections == 2u) fixture->remote_secondary = world_create();
    if (!fixture->schemas || !fixture->authoritative || !fixture->remote ||
        (max_connections == 2u && !fixture->remote_secondary) ||
        break_schema_register(fixture->schemas, &schema) != BREAK_SCHEMA_OK ||
        !reactor_start(fixture)) {
        return false;
    }
    world_register_component(fixture->authoritative, TEST_COMPONENT, sizeof(Value));
    world_register_component(fixture->remote, TEST_COMPONENT, sizeof(Value));
    if (fixture->remote_secondary) {
        world_register_component(fixture->remote_secondary, TEST_COMPONENT, sizeof(Value));
    }

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
    world_config.bridge.max_connections = max_connections;
    world_config.bridge.stream_capacity = 8u;
    world_config.bridge.max_pending_bytes_per_connection = 8192u;
    world_config.bridge.max_total_pending_bytes = 8192u * max_connections;
    world_config.bridge.max_metadata_bytes_per_connection = 8192u;
    world_config.bridge.max_total_metadata_bytes = 8192u * max_connections;
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

static bool socket_start(SocketFixture *fixture, bool include_delta)
{
    return socket_start_with_connections(fixture, include_delta, 1u);
}

static bool socket_attach_runtime_publication(SocketFixture *fixture, u32 budget)
{
    BreakWorldSnapshotPublicationConfig publication_config;
    BreakRuntimeWorldSessionConfig config;
    memset(&publication_config, 0, sizeof(publication_config));
    publication_config.schema_hash = break_schema_hash(fixture->schemas);
    publication_config.level_generation = TEST_LEVEL;
    fixture->publication = break_world_snapshot_publication_create(&publication_config);
    if (!fixture->publication ||
        break_runtime_bus_create(&fixture->bus) != BREAK_RUNTIME_OK) return false;
    memset(&config, 0, sizeof(config));
    config.session = fixture->session;
    config.bus = fixture->bus;
    config.subscriber_name = "world_loopback";
    config.max_connections = 2u;
    config.publication = fixture->publication;
    config.publish_connection_budget = budget;
    fixture->adapter = break_runtime_world_session_create(&config);
    return fixture->adapter != NULL;
}

static BreakRuntimeError socket_submit_current(
    SocketFixture *fixture, u64 level_generation, u64 correlation_id)
{
    BreakRuntimeWorldPublishCurrentNotice notice = {level_generation, 0u};
    return break_runtime_world_session_submit_publish_current(
        fixture->adapter, &notice, correlation_id);
}

static bool socket_publish_snapshot(
    SocketFixture *fixture, BreakWorldSnapshot *snapshot, u64 level_generation)
{
    return break_world_snapshot_publication_publish(fixture->publication, snapshot,
                                                    level_generation);
}

static bool write_frame_version(SocketFixture *fixture, u16 message_id, u16 protocol_version,
                                const void *payload, usize payload_size)
{
    u8 wire[BREAK_NET_ENVELOPE_HEADER_SIZE + 128u];
    if (payload_size > 128u || (payload_size != 0u && !payload)) return false;
    put32(wire, BREAK_NET_ENVELOPE_MAGIC);
    put16(wire + 4u, protocol_version);
    put16(wire + 6u, message_id);
    put16(wire + 8u, 0u);
    put32(wire + 10u, fixture->sequence++);
    put32(wire + 14u, (u32)payload_size);
    if (payload_size != 0u)
        memcpy(wire + BREAK_NET_ENVELOPE_HEADER_SIZE, payload, payload_size);
    return write_all(fixture->client_fd, wire, BREAK_NET_ENVELOPE_HEADER_SIZE + payload_size);
}

static bool write_frame(SocketFixture *fixture, u16 message_id, const void *payload,
                        usize payload_size)
{
    return write_frame_version(fixture, message_id, BREAK_NET_PROTOCOL_VERSION,
                               payload, payload_size);
}

static bool read_exact(SocketFixture *fixture, void *data, usize size)
{
    u8 *bytes = (u8 *)data;
    usize offset = 0u;
    usize attempts = 0u;
    while (offset < size && attempts < 5000u) {
        struct pollfd descriptor;
        ssize_t received;
        int ready;
        memset(&descriptor, 0, sizeof(descriptor));
        descriptor.fd = fixture->client_fd;
        descriptor.events = POLLIN;
        ready = poll(&descriptor, 1, 1);
        if (ready < 0) {
            if (errno == EINTR) continue;
            return false;
        }
        if (ready == 0) {
            ++attempts;
            if (!pump(fixture)) return false;
            continue;
        }
        received = read(fixture->client_fd, bytes + offset, size - offset);
        if (received < 0 && errno == EINTR) continue;
        if (received <= 0) return false;
        offset += (usize)received;
    }
    return offset == size;
}

static bool read_frame(SocketFixture *fixture, SocketFrame *frame)
{
    u8 header[BREAK_NET_ENVELOPE_HEADER_SIZE];
    u8 correlation[BREAK_NET_ENVELOPE_CORRELATION_SIZE];
    u32 body_size;
    memset(frame, 0, sizeof(*frame));
    if (!read_exact(fixture, header, sizeof(header)) ||
        get32(header) != BREAK_NET_ENVELOPE_MAGIC) {
        return false;
    }
    frame->protocol_version = get16(header + 4u);
    frame->message_id = get16(header + 6u);
    frame->flags = get16(header + 8u);
    frame->sequence = get32(header + 10u);
    body_size = get32(header + 14u);
    if ((frame->flags & (u16)~BREAK_NET_ENVELOPE_FLAG_CORRELATED) != 0u) return false;
    if ((frame->flags & BREAK_NET_ENVELOPE_FLAG_CORRELATED) != 0u) {
        if (body_size < BREAK_NET_ENVELOPE_CORRELATION_SIZE ||
            !read_exact(fixture, correlation, sizeof(correlation))) {
            return false;
        }
        frame->correlation_id = get64(correlation);
        if (frame->correlation_id == 0u) return false;
        body_size -= BREAK_NET_ENVELOPE_CORRELATION_SIZE;
    }
    frame->payload_size = body_size;
    return frame->payload_size <= sizeof(frame->payload) &&
           read_exact(fixture, frame->payload, frame->payload_size);
}

static bool write_control(SocketFixture *fixture, u16 version, u64 level_generation,
                          const BreakWorldSessionControl *control)
{
    u8 payload[BREAK_WORLD_SESSION_CONTROL_WIRE_SIZE_V2];
    usize payload_size;
    if (version != 1u && version != 2u) return false;
    payload_size = version == 2u ? BREAK_WORLD_SESSION_CONTROL_WIRE_SIZE_V2
                                 : BREAK_WORLD_SESSION_CONTROL_WIRE_SIZE;
    memset(payload, 0, sizeof(payload));
    memcpy(payload, "BRWC", 4u);
    put16(payload + 4u, version);
    put16(payload + 6u, (u16)control->kind);
    put64(payload + 8u, control->delta_id);
    put64(payload + 16u, control->target_snapshot_id);
    put64(payload + 24u, control->target_tick);
    if (version == 2u) put64(payload + 32u, level_generation);
    return write_frame_version(fixture, BREAK_NET_MESSAGE_ID_WORLD_CONTROL, version,
                               payload, payload_size);
}

static bool write_attempt_ack(SocketFixture *fixture, const SocketAttempt *attempt,
                              u16 version, u64 level_generation)
{
    BreakWorldSessionControl control;
    memset(&control, 0, sizeof(control));
    control.kind = BREAK_WORLD_SESSION_CONTROL_ACK;
    control.delta_id = attempt->delta_id;
    control.target_snapshot_id = attempt->target_snapshot_id;
    control.target_tick = attempt->target_tick;
    return write_control(fixture, version, level_generation, &control);
}

static bool socket_identity(int fd, struct sockaddr_in *local, struct sockaddr_in *peer)
{
    socklen_t local_size = sizeof(*local);
    socklen_t peer_size = sizeof(*peer);
    memset(local, 0, sizeof(*local));
    memset(peer, 0, sizeof(*peer));
    return getsockname(fd, (struct sockaddr *)local, &local_size) == 0 &&
           getpeername(fd, (struct sockaddr *)peer, &peer_size) == 0;
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
        if (fixture->auth_calls != 0u && fixture->connection != 0u &&
            break_session_manager_state(fixture->manager, fixture->connection) ==
                BREAK_SESSION_AUTHENTICATED) {
            BreakRuntimeWorldCommand open;
            usize drained = 0u;
            u64 epoch = 0u;
            if (fixture->adapter == NULL) {
                return break_world_session_open(fixture->session, fixture->connection);
            }
            memset(&open, 0, sizeof(open));
            open.kind = BREAK_RUNTIME_WORLD_COMMAND_OPEN;
            open.connection_key = fixture->connection;
            open.connection_epoch = 0u;
            open.level_generation = TEST_LEVEL;
            if (break_runtime_world_session_submit(fixture->adapter, &open, 0u) !=
                    BREAK_RUNTIME_OK ||
                break_runtime_world_session_drain(fixture->adapter, 1u, &drained) !=
                    BREAK_RUNTIME_OK ||
                drained != 1u ||
                !break_runtime_world_session_connection_epoch(
                    fixture->adapter, fixture->connection, &epoch) ||
                epoch == 0u) {
                return false;
            }
            fixture->adapter_epoch = epoch;
            return true;
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

static bool write_shuffled_payload_with_epoch(SocketFixture *fixture, u64 delta_id, u64 epoch,
                                              const void *payload, usize payload_size)
{
    BreakReplicationFragment *fragments = NULL;
    usize count = 0u;
    bool ok = true;
    if (break_replication_fragment_payload(delta_id, epoch, payload, payload_size,
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

static bool write_shuffled_payload(SocketFixture *fixture, u64 delta_id,
                                   const void *payload, usize payload_size)
{
    return write_shuffled_payload_with_epoch(fixture, delta_id, fixture->epoch,
                                             payload, payload_size);
}

typedef struct {
    BreakReplicationReassembler *reassembler;
    SocketAttempt attempt;
    u8 *payload;
    usize payload_size;
    bool complete;
} SocketReceive;

static bool socket_receive_init(SocketReceive *receive, u64 epoch)
{
    memset(receive, 0, sizeof(*receive));
    receive->reassembler = break_replication_reassembler_create(epoch);
    return receive->reassembler != NULL;
}

static void socket_receive_clear(SocketReceive *receive)
{
    break_replication_reassembly_free(receive->payload);
    break_replication_reassembler_destroy(receive->reassembler);
    memset(receive, 0, sizeof(*receive));
}

static bool socket_receive_push(SocketFixture *fixture, SocketReceive *receive)
{
    SocketFrame frame;
    BreakReplicationFragment fragment;
    BreakReplicationReassemblyResult result;
    BreakWorldDeltaWire decoded;
    if (receive->complete || !read_frame(fixture, &frame) ||
        frame.message_id != BREAK_NET_MESSAGE_ID_WORLD_DELTA ||
        frame.protocol_version != BREAK_REPLICATION_WIRE_VERSION ||
        break_replication_wire_decode(frame.payload, frame.payload_size, &fragment) !=
            BREAK_REPLICATION_FRAGMENT_OK ||
        (receive->attempt.delta_id != 0u &&
         receive->attempt.delta_id != fragment.delta_id)) {
        return false;
    }
    receive->attempt.delta_id = fragment.delta_id;
    receive->attempt.fragment_count++;
    result = break_replication_reassembler_push(receive->reassembler, &fragment,
                                                &receive->payload,
                                                &receive->payload_size);
    if (result == BREAK_REPLICATION_REASSEMBLY_INCOMPLETE) return true;
    if (result != BREAK_REPLICATION_REASSEMBLY_COMPLETE || !receive->payload ||
        break_world_delta_wire_decode(receive->payload, receive->payload_size, &decoded) !=
            BREAK_WORLD_DELTA_WIRE_OK) {
        return false;
    }
    receive->attempt.kind = decoded.kind;
    receive->attempt.base_snapshot_id = decoded.base_snapshot_id;
    receive->attempt.target_snapshot_id = decoded.target_snapshot_id;
    receive->attempt.target_tick = decoded.target_tick;
    receive->attempt.level_generation = decoded.level_generation;
    receive->complete = true;
    break_world_delta_wire_clear(&decoded);
    return true;
}

static bool collect_published_with_payload(SocketFixture *fixture, SocketAttempt *attempt,
                                           u8 **out_payload, usize *out_payload_size)
{
    SocketReceive receive;
    bool ok = socket_receive_init(&receive, fixture->epoch);
    if (out_payload) *out_payload = NULL;
    if (out_payload_size) *out_payload_size = 0u;
    while (ok && !receive.complete) ok = socket_receive_push(fixture, &receive);
    if (ok) {
        *attempt = receive.attempt;
        if (out_payload) {
            *out_payload = receive.payload;
            receive.payload = NULL;
        }
        if (out_payload_size) *out_payload_size = receive.payload_size;
    }
    socket_receive_clear(&receive);
    return ok;
}

static bool collect_published(SocketFixture *fixture, SocketAttempt *attempt)
{
    return collect_published_with_payload(fixture, attempt, NULL, NULL);
}

static bool collect_published_pair_interleaved(SocketFixture *fixture,
                                               SocketAttempt *first,
                                               SocketAttempt *second)
{
    SocketReceive receives[2];
    bool ok;
    usize turn = 0u;
    memset(receives, 0, sizeof(receives));
    ok = socket_receive_init(&receives[0], fixture->epoch) &&
         socket_receive_init(&receives[1], fixture->epoch);
    while (ok && !(receives[0].complete && receives[1].complete) && turn < 128u) {
        usize index = turn & 1u;
        if (receives[index].complete) index ^= 1u;
        socket_select_peer(fixture, index == 1u);
        ok = socket_receive_push(fixture, &receives[index]);
        ++turn;
    }
    ok = ok && receives[0].complete && receives[1].complete;
    if (ok) {
        *first = receives[0].attempt;
        *second = receives[1].attempt;
    }
    socket_receive_clear(&receives[1]);
    socket_receive_clear(&receives[0]);
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

static bool wait_session_dispatched(SocketFixture *fixture, u64 expected)
{
    for (usize i = 0u; i < 5000u; ++i) {
        BreakSessionApplyStats stats;
        break_session_manager_apply_stats(fixture->manager, &stats);
        if (stats.applied + stats.handler_failed >= expected) return true;
        if (!pump(fixture)) return false;
        usleep(1000u);
    }
    return false;
}

static bool wait_sender_confirmed_for_connection(SocketFixture *fixture,
                                                 BreakConnectionKey connection,
                                                 u64 expected_id)
{
    for (usize i = 0u; i < 5000u; ++i) {
        BreakWorldSessionSenderState state;
        if (break_world_session_sender_state(fixture->session, connection, &state) &&
            state.history_count == 0u && state.confirmed_snapshot_id == expected_id) {
            return true;
        }
        if (!pump(fixture)) return false;
        usleep(1000u);
    }
    return false;
}

static bool wait_sender_confirmed(SocketFixture *fixture, u64 expected_id)
{
    return wait_sender_confirmed_for_connection(fixture, fixture->connection, expected_id);
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

static bool encode_full_at_level(const BreakWorldSnapshot *snapshot, u64 level_generation,
                                 u8 **out_wire, usize *out_size)
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
    message.level_generation = level_generation;
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

static bool encode_full(const BreakWorldSnapshot *snapshot, u8 **out_wire, usize *out_size)
{
    return encode_full_at_level(snapshot, TEST_LEVEL, out_wire, out_size);
}

static bool encode_delta_at_level(const BreakWorldSnapshot *base,
                                  const BreakWorldSnapshot *target, u64 level_generation,
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
    message.level_generation = level_generation;
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

static bool encode_delta(const BreakWorldSnapshot *base, const BreakWorldSnapshot *target,
                         u8 **out_wire, usize *out_size)
{
    return encode_delta_at_level(base, target, TEST_LEVEL, out_wire, out_size);
}

static bool world_matches(World *world, BreakComponentSchemaRegistry *schemas,
                          u64 tick, u64 expected_id)
{
    BreakWorldSnapshot *snapshot = break_world_snapshot_build(world, schemas, tick);
    bool matches;
    if (!snapshot) return false;
    matches = break_world_snapshot_id(snapshot) == expected_id;
    break_world_snapshot_release(snapshot);
    return matches;
}

static bool remote_matches(SocketFixture *fixture, u64 tick, u64 expected_id)
{
    return world_matches(fixture->remote, fixture->schemas, tick, expected_id);
}

TEST(world_session_real_socket_control_correlation_preserves_v1_v2_and_sequences)
{
    static const u8 expected_v1[BREAK_WORLD_SESSION_CONTROL_WIRE_SIZE] = {
        0x42, 0x52, 0x57, 0x43, 0x01, 0x00, 0x02, 0x00,
        0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    };
    static const u8 expected_v2[BREAK_WORLD_SESSION_CONTROL_WIRE_SIZE_V2] = {
        0x42, 0x52, 0x57, 0x43, 0x02, 0x00, 0x02, 0x00,
        0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    };
    SocketFixture fixture;
    BreakWorldSessionControl control;
    SocketFrame frame;

    memset(&fixture, 0, sizeof(fixture));
    fixture.client_fd = -1;
    LOOPBACK_CHECK(socket_start(&fixture, true));
    LOOPBACK_CHECK(connect_authenticate(&fixture));
    memset(&control, 0, sizeof(control));
    control.kind = BREAK_WORLD_SESSION_CONTROL_ACK;
    control.delta_id = 1u;
    control.target_snapshot_id = 2u;
    control.target_tick = 3u;

    LOOPBACK_CHECK(break_world_session_send_control(
                       fixture.session, fixture.connection, &control) == BREAK_NET_SEND_OK);
    LOOPBACK_CHECK(read_frame(&fixture, &frame));
    LOOPBACK_CHECK(frame.message_id == 0x400Bu && frame.protocol_version == 1u);
    LOOPBACK_CHECK(frame.flags == 0u && frame.correlation_id == 0u);
    LOOPBACK_CHECK(frame.sequence == 1u);
    LOOPBACK_CHECK(frame.payload_size == sizeof(expected_v1));
    LOOPBACK_CHECK(memcmp(frame.payload, expected_v1, sizeof(expected_v1)) == 0);

    control.level_generation = TEST_LEVEL;
    LOOPBACK_CHECK(break_world_session_send_control_correlated(
                       fixture.session, fixture.connection, &control,
                       UINT64_C(0xF123456789ABCDEF)) == BREAK_NET_SEND_OK);
    LOOPBACK_CHECK(read_frame(&fixture, &frame));
    LOOPBACK_CHECK(frame.message_id == 0x400Bu && frame.protocol_version == 1u);
    LOOPBACK_CHECK(frame.flags == BREAK_NET_ENVELOPE_FLAG_CORRELATED);
    LOOPBACK_CHECK(frame.correlation_id == UINT64_C(0xF123456789ABCDEF));
    LOOPBACK_CHECK(frame.sequence == 2u);
    LOOPBACK_CHECK(frame.payload_size == sizeof(expected_v1));
    LOOPBACK_CHECK(memcmp(frame.payload, expected_v1, sizeof(expected_v1)) == 0);

    LOOPBACK_CHECK(break_world_session_rebaseline(fixture.session, 8u));
    control.level_generation = 8u;
    LOOPBACK_CHECK(break_world_session_send_control_correlated(
                       fixture.session, fixture.connection, &control,
                       UINT64_C(0xE123456789ABCDEF)) == BREAK_NET_SEND_OK);
    LOOPBACK_CHECK(read_frame(&fixture, &frame));
    LOOPBACK_CHECK(frame.message_id == 0x400Bu && frame.protocol_version == 2u);
    LOOPBACK_CHECK(frame.flags == BREAK_NET_ENVELOPE_FLAG_CORRELATED);
    LOOPBACK_CHECK(frame.correlation_id == UINT64_C(0xE123456789ABCDEF));
    LOOPBACK_CHECK(frame.sequence == 3u);
    LOOPBACK_CHECK(frame.payload_size == sizeof(expected_v2));
    LOOPBACK_CHECK(memcmp(frame.payload, expected_v2, sizeof(expected_v2)) == 0);
    LOOPBACK_CHECK(break_world_session_level_generation(fixture.session) == 8u);

cleanup:
    socket_dispose(&fixture);
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

TEST(world_session_same_socket_rebaselines_and_rejects_late_traffic)
{
    SocketFixture fixture;
    BreakWorldSnapshot *base = NULL;
    BreakWorldSnapshot *target = NULL;
    BreakWorldSnapshot *latest = NULL;
    BreakWorldSessionControl control;
    BreakWorldSessionSenderState sender_before;
    BreakWorldSessionSenderState sender_after;
    BreakWorldSessionStats before;
    BreakWorldSessionStats after;
    BreakSessionApplyStats session_stats;
    SocketAttempt old_full;
    SocketAttempt old_delta;
    SocketAttempt new_full;
    SocketAttempt new_delta;
    struct sockaddr_in local_before;
    struct sockaddr_in peer_before;
    struct sockaddr_in local_after;
    struct sockaddr_in peer_after;
    BreakConnectionKey server_key;
    BreakSessionId session_id;
    Value *value;
    Entity entity;
    u64 old_epoch;
    u64 expected_dispatches;
    u64 baseline_id = 99u;
    u64 baseline_tick = 99u;
    u8 *wire = NULL;
    usize size = 0u;

    memset(&fixture, 0, sizeof(fixture));
    fixture.client_fd = -1;
    LOOPBACK_CHECK(socket_start(&fixture, true));
    LOOPBACK_CHECK(connect_authenticate(&fixture));
    LOOPBACK_CHECK(fixture.auth_calls == 1u);
    server_key = fixture.connection;
    session_id = break_session_manager_session_id(fixture.manager, server_key);
    LOOPBACK_CHECK(session_id != 0u);
    LOOPBACK_CHECK(socket_identity(fixture.client_fd, &local_before, &peer_before));
    old_epoch = fixture.epoch;

    entity = world_create_entity(fixture.authoritative);
    LOOPBACK_CHECK(add_value(fixture.authoritative, entity, 42u));
    base = break_world_snapshot_build(fixture.authoritative, fixture.schemas, 10u);
    LOOPBACK_CHECK(base != NULL);
    LOOPBACK_CHECK(break_world_session_publish(fixture.session, server_key,
                                               fixture.authoritative, 10u) == BREAK_NET_SEND_OK);
    LOOPBACK_CHECK(collect_published(&fixture, &old_full));
    LOOPBACK_CHECK(old_full.kind == BREAK_WORLD_DELTA_WIRE_FULL);
    LOOPBACK_CHECK(old_full.delta_id == 1u);
    LOOPBACK_CHECK(old_full.target_snapshot_id == break_world_snapshot_id(base));
    LOOPBACK_CHECK(old_full.target_tick == 10u);
    LOOPBACK_CHECK(old_full.level_generation == TEST_LEVEL);
    LOOPBACK_CHECK(old_full.fragment_count >= 2u);
    LOOPBACK_CHECK(write_attempt_ack(&fixture, &old_full, 1u, 0u));
    LOOPBACK_CHECK(wait_sender_confirmed(&fixture, break_world_snapshot_id(base)));

    value = (Value *)world_get_component(fixture.authoritative, entity, TEST_COMPONENT);
    LOOPBACK_CHECK(value != NULL);
    value->value = 43u;
    target = break_world_snapshot_build(fixture.authoritative, fixture.schemas, 20u);
    LOOPBACK_CHECK(target != NULL);
    LOOPBACK_CHECK(break_world_session_publish(fixture.session, server_key,
                                               fixture.authoritative, 20u) == BREAK_NET_SEND_OK);
    LOOPBACK_CHECK(collect_published(&fixture, &old_delta));
    LOOPBACK_CHECK(old_delta.kind == BREAK_WORLD_DELTA_WIRE_DELTA);
    LOOPBACK_CHECK(old_delta.delta_id == 2u);
    LOOPBACK_CHECK(old_delta.base_snapshot_id == break_world_snapshot_id(base));
    LOOPBACK_CHECK(old_delta.target_snapshot_id == break_world_snapshot_id(target));
    LOOPBACK_CHECK(old_delta.level_generation == TEST_LEVEL);
    LOOPBACK_CHECK(break_world_session_sender_state(fixture.session, server_key, &sender_before));
    LOOPBACK_CHECK(sender_before.history_count == 1u);
    LOOPBACK_CHECK(sender_before.next_delta_id == 3u);

    LOOPBACK_CHECK(encode_full(base, &wire, &size));
    LOOPBACK_CHECK(write_shuffled_payload(&fixture, 100u, wire, size));
    free(wire);
    wire = NULL;
    LOOPBACK_CHECK(wait_completed(&fixture, 1u));
    LOOPBACK_CHECK(break_world_session_drain(fixture.session, server_key,
                                             fixture.remote, 1u) == 1u);
    LOOPBACK_CHECK(remote_matches(&fixture, 10u, break_world_snapshot_id(base)));
    LOOPBACK_CHECK(break_world_session_poll_control(fixture.session, server_key, &control));
    LOOPBACK_CHECK(control.kind == BREAK_WORLD_SESSION_CONTROL_ACK);
    LOOPBACK_CHECK(control.delta_id == 100u);
    LOOPBACK_CHECK(control.level_generation == TEST_LEVEL);

    size = 0u;
    LOOPBACK_CHECK(encode_delta(base, target, &wire, &size));
    LOOPBACK_CHECK(write_shuffled_payload(&fixture, 101u, wire, size));
    free(wire);
    wire = NULL;
    LOOPBACK_CHECK(wait_completed(&fixture, 2u));
    LOOPBACK_CHECK(break_world_session_drain(fixture.session, server_key,
                                             fixture.remote, 1u) == 1u);
    LOOPBACK_CHECK(remote_matches(&fixture, 20u, break_world_snapshot_id(target)));
    LOOPBACK_CHECK(break_world_session_baseline(fixture.session, server_key,
                                                &baseline_id, &baseline_tick));
    LOOPBACK_CHECK(baseline_id == break_world_snapshot_id(target));
    LOOPBACK_CHECK(baseline_tick == 20u);
    LOOPBACK_CHECK(break_world_session_poll_control(fixture.session, server_key, &control));
    LOOPBACK_CHECK(control.kind == BREAK_WORLD_SESSION_CONTROL_ACK);
    LOOPBACK_CHECK(control.delta_id == 101u);
    LOOPBACK_CHECK(control.level_generation == TEST_LEVEL);

    LOOPBACK_CHECK(break_world_session_rebaseline(fixture.session, 8u));
    fixture.epoch = break_world_session_stream_epoch(
        TEST_PROTOCOL, break_schema_hash(fixture.schemas), 8u);
    LOOPBACK_CHECK(fixture.epoch != old_epoch);
    LOOPBACK_CHECK(break_world_session_level_generation(fixture.session) == 8u);
    LOOPBACK_CHECK(fixture.connection == server_key);
    LOOPBACK_CHECK(fixture.auth_calls == 1u);
    LOOPBACK_CHECK(break_world_session_sender_state(fixture.session, server_key, &sender_after));
    LOOPBACK_CHECK(sender_after.history_count == 0u);
    LOOPBACK_CHECK(sender_after.history_bytes == 0u);
    LOOPBACK_CHECK(sender_after.confirmed_snapshot_id == 0u);
    LOOPBACK_CHECK(sender_after.next_delta_id == 1u);
    LOOPBACK_CHECK(!sender_after.attempt_pending);
    LOOPBACK_CHECK(break_world_session_baseline(fixture.session, server_key,
                                                &baseline_id, &baseline_tick));
    LOOPBACK_CHECK(baseline_id == 0u);
    LOOPBACK_CHECK(baseline_tick == 0u);
    LOOPBACK_CHECK(remote_matches(&fixture, 20u, break_world_snapshot_id(target)));
    LOOPBACK_CHECK(!break_world_session_poll_control(fixture.session, server_key, &control));

    value->value = 42u;
    LOOPBACK_CHECK(break_world_session_publish(fixture.session, server_key,
                                               fixture.authoritative, 10u) == BREAK_NET_SEND_OK);
    LOOPBACK_CHECK(collect_published(&fixture, &new_full));
    LOOPBACK_CHECK(new_full.kind == BREAK_WORLD_DELTA_WIRE_FULL);
    LOOPBACK_CHECK(new_full.level_generation == 8u);
    LOOPBACK_CHECK(new_full.delta_id == old_full.delta_id);
    LOOPBACK_CHECK(new_full.target_snapshot_id == old_full.target_snapshot_id);
    LOOPBACK_CHECK(new_full.target_tick == old_full.target_tick);
    LOOPBACK_CHECK(break_world_session_sender_state(fixture.session, server_key, &sender_before));
    LOOPBACK_CHECK(sender_before.history_count == 1u);
    LOOPBACK_CHECK(sender_before.confirmed_snapshot_id == 0u);
    LOOPBACK_CHECK(sender_before.next_delta_id == 2u);
    break_world_session_stats(fixture.session, &before);

    size = 0u;
    LOOPBACK_CHECK(encode_full(base, &wire, &size));
    break_session_manager_apply_stats(fixture.manager, &session_stats);
    expected_dispatches = session_stats.applied + session_stats.handler_failed +
                          (size + 16u) / 17u + 1u + 4u;
    LOOPBACK_CHECK(write_shuffled_payload_with_epoch(&fixture, old_full.delta_id, old_epoch,
                                                     wire, size));
    free(wire);
    wire = NULL;
    memset(&control, 0, sizeof(control));
    control.kind = BREAK_WORLD_SESSION_CONTROL_ACK;
    control.delta_id = old_full.delta_id;
    control.target_snapshot_id = old_full.target_snapshot_id;
    control.target_tick = old_full.target_tick;
    LOOPBACK_CHECK(write_control(&fixture, 1u, 0u, &control));
    LOOPBACK_CHECK(write_control(&fixture, 2u, TEST_LEVEL, &control));
    memset(&control, 0, sizeof(control));
    control.kind = BREAK_WORLD_SESSION_CONTROL_NEED_FULL;
    control.target_snapshot_id = old_full.target_snapshot_id;
    control.target_tick = old_full.target_tick;
    LOOPBACK_CHECK(write_control(&fixture, 1u, 0u, &control));
    LOOPBACK_CHECK(write_control(&fixture, 2u, TEST_LEVEL, &control));
    LOOPBACK_CHECK(wait_session_dispatched(&fixture, expected_dispatches));
    break_world_session_stats(fixture.session, &after);
    LOOPBACK_CHECK(after.bridge.completed_packets == before.bridge.completed_packets);
    LOOPBACK_CHECK(after.applied_packets == before.applied_packets);
    LOOPBACK_CHECK(after.drained_packets == before.drained_packets);
    LOOPBACK_CHECK(after.acknowledged_packets == before.acknowledged_packets);
    LOOPBACK_CHECK(remote_matches(&fixture, 20u, break_world_snapshot_id(target)));
    LOOPBACK_CHECK(break_world_session_baseline(fixture.session, server_key,
                                                &baseline_id, &baseline_tick));
    LOOPBACK_CHECK(baseline_id == 0u && baseline_tick == 0u);
    LOOPBACK_CHECK(break_world_session_sender_state(fixture.session, server_key, &sender_after));
    LOOPBACK_CHECK(memcmp(&sender_before, &sender_after, sizeof(sender_before)) == 0);
    LOOPBACK_CHECK(!break_world_session_poll_control(fixture.session, server_key, &control));

    value->value = 44u;
    latest = break_world_snapshot_build(fixture.authoritative, fixture.schemas, 30u);
    LOOPBACK_CHECK(latest != NULL);
    size = 0u;
    LOOPBACK_CHECK(encode_delta_at_level(target, latest, 8u, &wire, &size));
    LOOPBACK_CHECK(write_shuffled_payload(&fixture, 2u, wire, size));
    free(wire);
    wire = NULL;
    LOOPBACK_CHECK(wait_completed(&fixture, before.bridge.completed_packets + 1u));
    LOOPBACK_CHECK(break_world_session_drain(fixture.session, server_key,
                                             fixture.remote, 1u) == 1u);
    LOOPBACK_CHECK(remote_matches(&fixture, 20u, break_world_snapshot_id(target)));
    LOOPBACK_CHECK(break_world_session_baseline(fixture.session, server_key,
                                                &baseline_id, &baseline_tick));
    LOOPBACK_CHECK(baseline_id == 0u && baseline_tick == 0u);
    LOOPBACK_CHECK(break_world_session_poll_control(fixture.session, server_key, &control));
    LOOPBACK_CHECK(control.kind == BREAK_WORLD_SESSION_CONTROL_NEED_FULL);
    LOOPBACK_CHECK(control.level_generation == 8u);
    LOOPBACK_CHECK(control.target_snapshot_id == 0u);
    LOOPBACK_CHECK(control.target_tick == 0u);

    size = 0u;
    LOOPBACK_CHECK(encode_full_at_level(latest, 8u, &wire, &size));
    LOOPBACK_CHECK(write_shuffled_payload(&fixture, 3u, wire, size));
    free(wire);
    wire = NULL;
    LOOPBACK_CHECK(wait_completed(&fixture, before.bridge.completed_packets + 2u));
    LOOPBACK_CHECK(break_world_session_drain(fixture.session, server_key,
                                             fixture.remote, 1u) == 1u);
    LOOPBACK_CHECK(remote_matches(&fixture, 30u, break_world_snapshot_id(latest)));
    LOOPBACK_CHECK(break_world_session_baseline(fixture.session, server_key,
                                                &baseline_id, &baseline_tick));
    LOOPBACK_CHECK(baseline_id == break_world_snapshot_id(latest));
    LOOPBACK_CHECK(baseline_tick == 30u);
    LOOPBACK_CHECK(break_world_session_poll_control(fixture.session, server_key, &control));
    LOOPBACK_CHECK(control.kind == BREAK_WORLD_SESSION_CONTROL_ACK);
    LOOPBACK_CHECK(control.delta_id == 3u);
    LOOPBACK_CHECK(control.target_snapshot_id == break_world_snapshot_id(latest));
    LOOPBACK_CHECK(control.target_tick == 30u);
    LOOPBACK_CHECK(control.level_generation == 8u);

    LOOPBACK_CHECK(write_attempt_ack(&fixture, &new_full, 2u, 8u));
    LOOPBACK_CHECK(wait_sender_confirmed(&fixture, new_full.target_snapshot_id));
    LOOPBACK_CHECK(break_world_session_sender_state(fixture.session, server_key, &sender_after));
    LOOPBACK_CHECK(sender_after.history_count == 0u);
    LOOPBACK_CHECK(sender_after.confirmed_snapshot_id == new_full.target_snapshot_id);
    LOOPBACK_CHECK(sender_after.confirmed_tick == 10u);
    LOOPBACK_CHECK(sender_after.next_delta_id == 2u);

    value->value = 45u;
    LOOPBACK_CHECK(break_world_session_publish(fixture.session, server_key,
                                               fixture.authoritative, 40u) == BREAK_NET_SEND_OK);
    LOOPBACK_CHECK(collect_published(&fixture, &new_delta));
    LOOPBACK_CHECK(new_delta.kind == BREAK_WORLD_DELTA_WIRE_DELTA);
    LOOPBACK_CHECK(new_delta.delta_id == 2u);
    LOOPBACK_CHECK(new_delta.base_snapshot_id == new_full.target_snapshot_id);
    LOOPBACK_CHECK(new_delta.target_tick == 40u);
    LOOPBACK_CHECK(new_delta.level_generation == 8u);

    break_world_session_stats(fixture.session, &after);
    LOOPBACK_CHECK(after.applied_packets == 3u);
    LOOPBACK_CHECK(after.need_full_packets == 1u);
    LOOPBACK_CHECK(after.rejected_packets == 1u);
    LOOPBACK_CHECK(after.drained_packets == 4u);
    LOOPBACK_CHECK(after.published_full_packets == 2u);
    LOOPBACK_CHECK(after.published_delta_packets == 2u);
    LOOPBACK_CHECK(after.acknowledged_packets == 2u);
    LOOPBACK_CHECK(after.bridge.completed_packets == 4u);
    LOOPBACK_CHECK(fixture.connection == server_key);
    LOOPBACK_CHECK(break_session_manager_session_id(fixture.manager, server_key) == session_id);
    LOOPBACK_CHECK(fixture.auth_calls == 1u);
    LOOPBACK_CHECK(break_session_manager_state(fixture.manager, server_key) ==
                   BREAK_SESSION_AUTHENTICATED);
    LOOPBACK_CHECK(socket_identity(fixture.client_fd, &local_after, &peer_after));
    LOOPBACK_CHECK(memcmp(&local_before, &local_after, sizeof(local_before)) == 0);
    LOOPBACK_CHECK(memcmp(&peer_before, &peer_after, sizeof(peer_before)) == 0);

cleanup:
    free(wire);
    break_world_snapshot_release(latest);
    break_world_snapshot_release(target);
    break_world_snapshot_release(base);
    socket_dispose(&fixture);
}

TEST(world_session_default_outbound_admission_keeps_global_capacity)
{
    SocketFixture fixture;
    BreakWorldSnapshot *first = NULL;
    BreakWorldSessionSenderState state;
    SocketAttempt published;
    BreakConnectionKey a_key;
    BreakConnectionKey b_key;
    Entity entity;

    memset(&fixture, 0, sizeof(fixture));
    fixture.client_fd = -1;
    fixture.inactive_client_fd = -1;
    LOOPBACK_CHECK(socket_start_with_connections(&fixture, true, 2u));
    LOOPBACK_CHECK(connect_authenticate(&fixture));
    a_key = fixture.connection;
    socket_select_peer(&fixture, true);
    LOOPBACK_CHECK(connect_authenticate(&fixture));
    b_key = fixture.connection;
    LOOPBACK_CHECK(fixture.auth_calls == 2u && a_key != b_key);
    entity = world_create_entity(fixture.authoritative);
    LOOPBACK_CHECK(add_value(fixture.authoritative, entity, 42u));
    first = break_world_snapshot_build(fixture.authoritative, fixture.schemas, 10u);
    LOOPBACK_CHECK(first != NULL);

    socket_select_peer(&fixture, false);
    for (usize i = 0u; i < BREAK_NET_OUTBOUND_QUEUE_CAPACITY; ++i) {
        LOOPBACK_CHECK(break_net_reactor_send(fixture.reactor, a_key,
                                             BREAK_NET_MESSAGE_ID_PING, 1u, "x", 1u) ==
                       BREAK_NET_SEND_OK);
    }
    LOOPBACK_CHECK(break_net_reactor_outbound_count(fixture.reactor) ==
                   BREAK_NET_OUTBOUND_QUEUE_CAPACITY);
    LOOPBACK_CHECK(break_world_session_publish_snapshot(fixture.session, b_key, first,
                                                        TEST_LEVEL) ==
                   BREAK_NET_SEND_OVERLOAD);
    LOOPBACK_CHECK(break_world_session_sender_state(fixture.session, b_key, &state));
    LOOPBACK_CHECK(state.attempt_pending && state.history_count == 0u &&
                   state.next_delta_id == 2u);
    for (usize i = 0u; i < BREAK_NET_OUTBOUND_QUEUE_CAPACITY; ++i) {
        SocketFrame frame;
        LOOPBACK_CHECK(read_frame(&fixture, &frame));
        LOOPBACK_CHECK(frame.message_id == BREAK_NET_MESSAGE_ID_PING &&
                       frame.protocol_version == 1u && frame.payload_size == 1u &&
                       frame.payload[0] == (u8)'x');
    }
    LOOPBACK_CHECK(break_net_reactor_outbound_count(fixture.reactor) == 0u);
    LOOPBACK_CHECK(break_world_session_publish_snapshot(fixture.session, b_key, first,
                                                        TEST_LEVEL) == BREAK_NET_SEND_OK);
    socket_select_peer(&fixture, true);
    LOOPBACK_CHECK(collect_published(&fixture, &published));
    LOOPBACK_CHECK(published.kind == BREAK_WORLD_DELTA_WIRE_FULL);
    LOOPBACK_CHECK(published.delta_id == 1u);
    LOOPBACK_CHECK(published.target_snapshot_id == break_world_snapshot_id(first));
    LOOPBACK_CHECK(published.target_tick == 10u && published.level_generation == TEST_LEVEL);
    LOOPBACK_CHECK(break_world_session_sender_state(fixture.session, b_key, &state));
    LOOPBACK_CHECK(!state.attempt_pending && state.history_count == 1u &&
                   state.next_delta_id == 2u);

cleanup:
    break_world_snapshot_release(first);
    socket_dispose(&fixture);
}

TEST(world_session_two_sockets_share_snapshots_with_independent_recovery)
{
    SocketFixture fixture;
    BreakWorldSnapshot *first = NULL;
    BreakWorldSnapshot *second = NULL;
    BreakWorldSnapshot *third = NULL;
    BreakWorldSnapshot *current = NULL;
    SocketAttempt a_first;
    SocketAttempt b_first;
    SocketAttempt a_second;
    SocketAttempt b_second;
    SocketAttempt a_third;
    SocketAttempt b_third;
    SocketAttempt a_current;
    SocketAttempt b_current;
    BreakWorldSessionSenderState a_state;
    BreakWorldSessionSenderState b_state;
    BreakWorldSessionControl control;
    BreakWorldSessionStats stats;
    BreakSessionApplyStats session_stats;
    BreakConnectionKey a_key;
    BreakConnectionKey b_key;
    Entity entity;
    Value *value;
    Value old_value;
    const void *bytes = NULL;
    usize value_size = 0u;
    u64 first_id;
    u64 second_id;
    u64 third_id;
    u64 current_id;
    u64 baseline_id = 99u;
    u64 baseline_tick = 99u;
    u64 expected_dispatches;
    u8 *wire = NULL;
    usize size = 0u;

    memset(&fixture, 0, sizeof(fixture));
    fixture.client_fd = -1;
    fixture.inactive_client_fd = -1;
    fixture.fair_outbound_admission = true;
    LOOPBACK_CHECK(socket_start_with_connections(&fixture, true, 2u));
    LOOPBACK_CHECK(connect_authenticate(&fixture));
    a_key = fixture.connection;
    socket_select_peer(&fixture, true);
    LOOPBACK_CHECK(connect_authenticate(&fixture));
    b_key = fixture.connection;
    LOOPBACK_CHECK(fixture.auth_calls == 2u);
    LOOPBACK_CHECK(a_key != 0u && b_key != 0u && a_key != b_key);
    LOOPBACK_CHECK(break_session_manager_state(fixture.manager, a_key) ==
                   BREAK_SESSION_AUTHENTICATED);
    LOOPBACK_CHECK(break_session_manager_state(fixture.manager, b_key) ==
                   BREAK_SESSION_AUTHENTICATED);

    entity = world_create_entity(fixture.authoritative);
    LOOPBACK_CHECK(add_value(fixture.authoritative, entity, 42u));
    first = break_world_snapshot_build(fixture.authoritative, fixture.schemas, 10u);
    LOOPBACK_CHECK(first != NULL);
    first_id = break_world_snapshot_id(first);

    socket_select_peer(&fixture, false);
    for (usize i = 0u; i < TEST_DUAL_OUTBOUND_SHARE; ++i) {
        LOOPBACK_CHECK(break_net_reactor_send(fixture.reactor, a_key,
                                             BREAK_NET_MESSAGE_ID_PING, 1u, "x", 1u) ==
                       BREAK_NET_SEND_OK);
    }
    LOOPBACK_CHECK(break_world_session_publish_snapshot(fixture.session, a_key, first,
                                                        TEST_LEVEL) ==
                   BREAK_NET_SEND_OVERLOAD);
    LOOPBACK_CHECK(break_world_session_sender_state(fixture.session, a_key, &a_state));
    LOOPBACK_CHECK(break_world_session_sender_state(fixture.session, b_key, &b_state));
    LOOPBACK_CHECK(a_state.attempt_pending && a_state.history_count == 0u &&
                   a_state.next_delta_id == 2u);
    LOOPBACK_CHECK(!b_state.attempt_pending && b_state.history_count == 0u &&
                   b_state.next_delta_id == 1u);
    LOOPBACK_CHECK(break_world_session_publish_snapshot(fixture.session, b_key, first,
                                                        TEST_LEVEL) == BREAK_NET_SEND_OK);
    LOOPBACK_CHECK(break_world_session_sender_state(fixture.session, a_key, &a_state));
    LOOPBACK_CHECK(break_world_session_sender_state(fixture.session, b_key, &b_state));
    LOOPBACK_CHECK(a_state.attempt_pending && a_state.history_count == 0u);
    LOOPBACK_CHECK(!b_state.attempt_pending && b_state.history_count == 1u);
    for (usize i = 0u; i < TEST_DUAL_OUTBOUND_SHARE; ++i) {
        SocketFrame frame;
        LOOPBACK_CHECK(read_frame(&fixture, &frame));
        LOOPBACK_CHECK(frame.message_id == BREAK_NET_MESSAGE_ID_PING &&
                       frame.protocol_version == 1u && frame.payload_size == 1u &&
                       frame.payload[0] == (u8)'x');
    }
    LOOPBACK_CHECK(break_world_session_publish_snapshot(fixture.session, a_key, first,
                                                        TEST_LEVEL) == BREAK_NET_SEND_OK);
    LOOPBACK_CHECK(collect_published_pair_interleaved(&fixture, &a_first, &b_first));
    LOOPBACK_CHECK(a_first.kind == BREAK_WORLD_DELTA_WIRE_FULL &&
                   b_first.kind == BREAK_WORLD_DELTA_WIRE_FULL);
    LOOPBACK_CHECK(a_first.target_snapshot_id == first_id &&
                   b_first.target_snapshot_id == first_id);
    LOOPBACK_CHECK(a_first.target_tick == 10u && b_first.target_tick == 10u);
    LOOPBACK_CHECK(a_first.level_generation == TEST_LEVEL &&
                   b_first.level_generation == TEST_LEVEL);
    LOOPBACK_CHECK(a_first.fragment_count >= 2u && b_first.fragment_count >= 2u);

    LOOPBACK_CHECK(encode_full(first, &wire, &size));
    socket_select_peer(&fixture, false);
    LOOPBACK_CHECK(write_shuffled_payload(&fixture, 100u, wire, size));
    socket_select_peer(&fixture, true);
    LOOPBACK_CHECK(write_shuffled_payload(&fixture, 100u, wire, size));
    free(wire);
    wire = NULL;
    LOOPBACK_CHECK(wait_completed(&fixture, 2u));
    LOOPBACK_CHECK(break_world_entity_count(fixture.remote) == 0u);
    LOOPBACK_CHECK(break_world_entity_count(fixture.remote_secondary) == 0u);
    LOOPBACK_CHECK(break_world_session_baseline(fixture.session, a_key,
                                                &baseline_id, &baseline_tick));
    LOOPBACK_CHECK(baseline_id == 0u && baseline_tick == 0u);
    LOOPBACK_CHECK(break_world_session_baseline(fixture.session, b_key,
                                                &baseline_id, &baseline_tick));
    LOOPBACK_CHECK(baseline_id == 0u && baseline_tick == 0u);
    LOOPBACK_CHECK(break_world_session_drain(fixture.session, a_key,
                                             fixture.remote, 1u) == 1u);
    LOOPBACK_CHECK(remote_matches(&fixture, 10u, first_id));
    LOOPBACK_CHECK(break_world_entity_count(fixture.remote_secondary) == 0u);
    LOOPBACK_CHECK(break_world_session_poll_control(fixture.session, a_key, &control));
    LOOPBACK_CHECK(control.kind == BREAK_WORLD_SESSION_CONTROL_ACK &&
                   control.delta_id == 100u && control.target_snapshot_id == first_id &&
                   control.target_tick == 10u);
    LOOPBACK_CHECK(!break_world_session_poll_control(fixture.session, b_key, &control));
    LOOPBACK_CHECK(break_world_session_drain(fixture.session, b_key,
                                             fixture.remote_secondary, 1u) == 1u);
    LOOPBACK_CHECK(world_matches(fixture.remote_secondary, fixture.schemas, 10u, first_id));
    LOOPBACK_CHECK(break_world_session_poll_control(fixture.session, b_key, &control));
    LOOPBACK_CHECK(control.kind == BREAK_WORLD_SESSION_CONTROL_ACK &&
                   control.delta_id == 100u && control.target_snapshot_id == first_id &&
                   control.target_tick == 10u);

    socket_select_peer(&fixture, true);
    LOOPBACK_CHECK(write_attempt_ack(&fixture, &b_first, 1u, 0u));
    LOOPBACK_CHECK(wait_sender_confirmed_for_connection(&fixture, b_key, first_id));
    LOOPBACK_CHECK(break_world_session_sender_state(fixture.session, a_key, &a_state));
    LOOPBACK_CHECK(a_state.history_count == 1u && a_state.confirmed_snapshot_id == 0u);

    socket_select_peer(&fixture, false);
    break_session_manager_apply_stats(fixture.manager, &session_stats);
    expected_dispatches = session_stats.applied + session_stats.handler_failed + 2u;
    LOOPBACK_CHECK(write_attempt_ack(&fixture, &a_first, 1u, 0u));
    memset(&control, 0, sizeof(control));
    control.kind = BREAK_WORLD_SESSION_CONTROL_NEED_FULL;
    control.target_snapshot_id = first_id;
    control.target_tick = 10u;
    LOOPBACK_CHECK(write_control(&fixture, 1u, 0u, &control));
    LOOPBACK_CHECK(wait_session_dispatched(&fixture, expected_dispatches));
    LOOPBACK_CHECK(wait_sender_confirmed_for_connection(&fixture, a_key, first_id));
    LOOPBACK_CHECK(break_world_session_sender_state(fixture.session, b_key, &b_state));
    LOOPBACK_CHECK(b_state.history_count == 0u && b_state.confirmed_snapshot_id == first_id);

    value = (Value *)world_get_component(fixture.authoritative, entity, TEST_COMPONENT);
    LOOPBACK_CHECK(value != NULL);
    value->value = 43u;
    second = break_world_snapshot_build(fixture.authoritative, fixture.schemas, 20u);
    LOOPBACK_CHECK(second != NULL);
    second_id = break_world_snapshot_id(second);
    LOOPBACK_CHECK(break_world_session_publish_snapshot(fixture.session, a_key, second,
                                                        TEST_LEVEL) == BREAK_NET_SEND_OK);
    LOOPBACK_CHECK(break_world_session_publish_snapshot(fixture.session, b_key, second,
                                                        TEST_LEVEL) == BREAK_NET_SEND_OK);
    LOOPBACK_CHECK(collect_published_pair_interleaved(&fixture, &a_second, &b_second));
    LOOPBACK_CHECK(a_second.kind == BREAK_WORLD_DELTA_WIRE_FULL);
    LOOPBACK_CHECK(a_second.base_snapshot_id == 0u);
    LOOPBACK_CHECK(b_second.kind == BREAK_WORLD_DELTA_WIRE_DELTA);
    LOOPBACK_CHECK(b_second.base_snapshot_id == first_id);
    LOOPBACK_CHECK(a_second.target_snapshot_id == second_id &&
                   b_second.target_snapshot_id == second_id);
    LOOPBACK_CHECK(a_second.target_tick == 20u && b_second.target_tick == 20u);
    LOOPBACK_CHECK(break_world_session_sender_state(fixture.session, a_key, &a_state));
    LOOPBACK_CHECK(break_world_session_sender_state(fixture.session, b_key, &b_state));
    LOOPBACK_CHECK(a_state.history_count == 1u && a_state.confirmed_snapshot_id == 0u);
    LOOPBACK_CHECK(b_state.history_count == 1u && b_state.confirmed_snapshot_id == first_id);

    socket_select_peer(&fixture, false);
    LOOPBACK_CHECK(write_attempt_ack(&fixture, &a_second, 1u, 0u));
    LOOPBACK_CHECK(wait_sender_confirmed_for_connection(&fixture, a_key, second_id));
    LOOPBACK_CHECK(break_world_session_sender_state(fixture.session, b_key, &b_state));
    LOOPBACK_CHECK(b_state.history_count == 1u && b_state.confirmed_snapshot_id == first_id);
    break_world_snapshot_release(second);
    second = NULL;

    value->value = 44u;
    third = break_world_snapshot_build(fixture.authoritative, fixture.schemas, 30u);
    LOOPBACK_CHECK(third != NULL);
    third_id = break_world_snapshot_id(third);
    LOOPBACK_CHECK(break_world_session_publish_snapshot(fixture.session, a_key, third,
                                                        TEST_LEVEL) == BREAK_NET_SEND_OK);
    LOOPBACK_CHECK(break_world_session_publish_snapshot(fixture.session, b_key, third,
                                                        TEST_LEVEL) == BREAK_NET_SEND_OK);
    LOOPBACK_CHECK(collect_published_pair_interleaved(&fixture, &a_third, &b_third));
    LOOPBACK_CHECK(a_third.kind == BREAK_WORLD_DELTA_WIRE_DELTA &&
                   b_third.kind == BREAK_WORLD_DELTA_WIRE_DELTA);
    LOOPBACK_CHECK(a_third.base_snapshot_id == second_id &&
                   b_third.base_snapshot_id == second_id);
    LOOPBACK_CHECK(a_third.target_snapshot_id == third_id &&
                   b_third.target_snapshot_id == third_id);
    LOOPBACK_CHECK(a_third.target_tick == 30u && b_third.target_tick == 30u);
    LOOPBACK_CHECK(break_world_session_sender_state(fixture.session, a_key, &a_state));
    LOOPBACK_CHECK(break_world_session_sender_state(fixture.session, b_key, &b_state));
    LOOPBACK_CHECK(a_state.history_count == 1u &&
                   a_state.confirmed_snapshot_id == second_id);
    LOOPBACK_CHECK(b_state.history_count == 2u &&
                   b_state.confirmed_snapshot_id == first_id);
    break_world_snapshot_release(third);
    third = NULL;

    socket_select_peer(&fixture, true);
    LOOPBACK_CHECK(write_attempt_ack(&fixture, &b_third, 1u, 0u));
    LOOPBACK_CHECK(wait_sender_confirmed_for_connection(&fixture, b_key, third_id));
    LOOPBACK_CHECK(break_world_session_sender_state(fixture.session, a_key, &a_state));
    LOOPBACK_CHECK(a_state.history_count == 1u &&
                   a_state.confirmed_snapshot_id == second_id);

    LOOPBACK_CHECK(break_world_session_rebaseline(fixture.session, 8u));
    fixture.epoch = break_world_session_stream_epoch(
        TEST_PROTOCOL, break_schema_hash(fixture.schemas), 8u);
    LOOPBACK_CHECK(break_world_session_sender_state(fixture.session, a_key, &a_state));
    LOOPBACK_CHECK(break_world_session_sender_state(fixture.session, b_key, &b_state));
    LOOPBACK_CHECK(a_state.history_count == 0u && a_state.confirmed_snapshot_id == 0u &&
                   a_state.next_delta_id == 1u && !a_state.attempt_pending);
    LOOPBACK_CHECK(b_state.history_count == 0u && b_state.confirmed_snapshot_id == 0u &&
                   b_state.next_delta_id == 1u && !b_state.attempt_pending);
    LOOPBACK_CHECK(break_world_snapshot_component_bytes(first, entity, TEST_COMPONENT,
                                                        &bytes, &value_size));
    LOOPBACK_CHECK(value_size == sizeof(old_value));
    memcpy(&old_value, bytes, sizeof(old_value));
    LOOPBACK_CHECK(old_value.value == 42u);
    LOOPBACK_CHECK(break_world_snapshot_id(first) == first_id &&
                   break_world_snapshot_tick(first) == 10u);
    LOOPBACK_CHECK(break_world_session_publish_snapshot(fixture.session, a_key, first,
                                                        TEST_LEVEL) == BREAK_NET_SEND_INVALID);
    LOOPBACK_CHECK(break_world_session_sender_state(fixture.session, a_key, &a_state));
    LOOPBACK_CHECK(break_world_session_sender_state(fixture.session, b_key, &b_state));
    LOOPBACK_CHECK(b_state.history_count == 0u && b_state.confirmed_snapshot_id == 0u &&
                   b_state.next_delta_id == 1u);
    LOOPBACK_CHECK(a_state.history_count == 0u && a_state.confirmed_snapshot_id == 0u &&
                   a_state.next_delta_id == 1u && !a_state.attempt_pending);

    value->value = 45u;
    current = break_world_snapshot_build(fixture.authoritative, fixture.schemas, 5u);
    LOOPBACK_CHECK(current != NULL);
    current_id = break_world_snapshot_id(current);
    LOOPBACK_CHECK(break_world_session_publish_snapshot(fixture.session, a_key, current, 8u) ==
                   BREAK_NET_SEND_OK);
    LOOPBACK_CHECK(break_world_session_publish_snapshot(fixture.session, b_key, current, 8u) ==
                   BREAK_NET_SEND_OK);
    LOOPBACK_CHECK(collect_published_pair_interleaved(&fixture, &a_current, &b_current));
    LOOPBACK_CHECK(a_current.kind == BREAK_WORLD_DELTA_WIRE_FULL &&
                   b_current.kind == BREAK_WORLD_DELTA_WIRE_FULL);
    LOOPBACK_CHECK(a_current.target_snapshot_id == current_id &&
                   b_current.target_snapshot_id == current_id);
    LOOPBACK_CHECK(a_current.target_tick == 5u && b_current.target_tick == 5u);
    LOOPBACK_CHECK(a_current.level_generation == 8u && b_current.level_generation == 8u);
    LOOPBACK_CHECK(a_current.delta_id == 1u && b_current.delta_id == 1u);
    break_world_snapshot_release(current);
    current = NULL;

    socket_select_peer(&fixture, false);
    LOOPBACK_CHECK(write_attempt_ack(&fixture, &a_current, 2u, 8u));
    LOOPBACK_CHECK(wait_sender_confirmed_for_connection(&fixture, a_key, current_id));
    LOOPBACK_CHECK(break_world_session_sender_state(fixture.session, b_key, &b_state));
    LOOPBACK_CHECK(b_state.history_count == 1u && b_state.confirmed_snapshot_id == 0u);
    socket_select_peer(&fixture, true);
    LOOPBACK_CHECK(write_attempt_ack(&fixture, &b_current, 2u, 8u));
    LOOPBACK_CHECK(wait_sender_confirmed_for_connection(&fixture, b_key, current_id));

    break_world_session_stats(fixture.session, &stats);
    LOOPBACK_CHECK(stats.applied_packets == 2u && stats.drained_packets == 2u);
    LOOPBACK_CHECK(stats.published_full_packets == 5u &&
                   stats.published_delta_packets == 3u);
    LOOPBACK_CHECK(stats.acknowledged_packets == 6u);
    LOOPBACK_CHECK(stats.bridge.completed_packets == 2u &&
                   stats.bridge.duplicate_fragments >= 2u);

cleanup:
    free(wire);
    break_world_snapshot_release(current);
    break_world_snapshot_release(third);
    break_world_snapshot_release(second);
    break_world_snapshot_release(first);
    socket_dispose(&fixture);
}

TEST(world_session_pending_snapshot_attempt_outlives_caller_lease)
{
    SocketFixture fixture;
    BreakWorldSnapshot *pending = NULL;
    BreakWorldSnapshot *ignored = NULL;
    SocketAttempt resumed;
    BreakWorldSessionSenderState a_state;
    BreakWorldSessionSenderState b_state;
    BreakConnectionKey a_key;
    BreakConnectionKey b_key;
    Entity entity;
    Value *value;
    u64 pending_id;
    u64 ignored_id;
    u8 *expected_payload = NULL;
    usize expected_payload_size = 0u;
    u8 *actual_payload = NULL;
    usize actual_payload_size = 0u;

    memset(&fixture, 0, sizeof(fixture));
    fixture.client_fd = -1;
    fixture.inactive_client_fd = -1;
    fixture.fair_outbound_admission = true;
    LOOPBACK_CHECK(socket_start_with_connections(&fixture, true, 2u));
    LOOPBACK_CHECK(connect_authenticate(&fixture));
    a_key = fixture.connection;
    socket_select_peer(&fixture, true);
    LOOPBACK_CHECK(connect_authenticate(&fixture));
    b_key = fixture.connection;
    LOOPBACK_CHECK(fixture.auth_calls == 2u && a_key != b_key);

    entity = world_create_entity(fixture.authoritative);
    LOOPBACK_CHECK(add_value(fixture.authoritative, entity, 77u));
    pending = break_world_snapshot_build(fixture.authoritative, fixture.schemas, 20u);
    LOOPBACK_CHECK(pending != NULL);
    pending_id = break_world_snapshot_id(pending);
    LOOPBACK_CHECK(encode_full(pending, &expected_payload, &expected_payload_size));

    socket_select_peer(&fixture, false);
    for (usize i = 0u; i < TEST_DUAL_OUTBOUND_SHARE; ++i) {
        LOOPBACK_CHECK(break_net_reactor_send(fixture.reactor, a_key,
                                             BREAK_NET_MESSAGE_ID_PING, 1u, "x", 1u) ==
                       BREAK_NET_SEND_OK);
    }
    LOOPBACK_CHECK(break_world_session_publish_snapshot(fixture.session, a_key, pending,
                                                        TEST_LEVEL) ==
                   BREAK_NET_SEND_OVERLOAD);
    LOOPBACK_CHECK(break_world_session_sender_state(fixture.session, a_key, &a_state));
    LOOPBACK_CHECK(a_state.attempt_pending && a_state.history_count == 0u &&
                   a_state.next_delta_id == 2u);
    LOOPBACK_CHECK(break_world_session_sender_state(fixture.session, b_key, &b_state));
    LOOPBACK_CHECK(!b_state.attempt_pending && b_state.history_count == 0u &&
                   b_state.confirmed_snapshot_id == 0u && b_state.next_delta_id == 1u);
    break_world_snapshot_release(pending);
    pending = NULL;

    value = (Value *)world_get_component(fixture.authoritative, entity, TEST_COMPONENT);
    LOOPBACK_CHECK(value != NULL);
    value->value = 99u;
    ignored = break_world_snapshot_build(fixture.authoritative, fixture.schemas, 30u);
    LOOPBACK_CHECK(ignored != NULL);
    ignored_id = break_world_snapshot_id(ignored);
    LOOPBACK_CHECK(ignored_id != pending_id);
    LOOPBACK_CHECK(break_world_session_publish_snapshot(fixture.session, a_key, ignored,
                                                        TEST_LEVEL) ==
                   BREAK_NET_SEND_OVERLOAD);
    LOOPBACK_CHECK(break_world_session_sender_state(fixture.session, a_key, &a_state));
    LOOPBACK_CHECK(a_state.attempt_pending && a_state.history_count == 0u &&
                   a_state.next_delta_id == 2u);

    for (usize i = 0u; i < TEST_DUAL_OUTBOUND_SHARE; ++i) {
        SocketFrame frame;
        LOOPBACK_CHECK(read_frame(&fixture, &frame));
        LOOPBACK_CHECK(frame.message_id == BREAK_NET_MESSAGE_ID_PING &&
                       frame.protocol_version == 1u && frame.payload_size == 1u &&
                       frame.payload[0] == (u8)'x');
    }
    LOOPBACK_CHECK(break_world_session_publish_snapshot(fixture.session, a_key, ignored,
                                                        TEST_LEVEL) == BREAK_NET_SEND_OK);
    LOOPBACK_CHECK(collect_published_with_payload(&fixture, &resumed, &actual_payload,
                                                  &actual_payload_size));
    LOOPBACK_CHECK(resumed.kind == BREAK_WORLD_DELTA_WIRE_FULL);
    LOOPBACK_CHECK(resumed.delta_id == 1u);
    LOOPBACK_CHECK(resumed.target_snapshot_id == pending_id);
    LOOPBACK_CHECK(resumed.target_snapshot_id != ignored_id);
    LOOPBACK_CHECK(resumed.target_tick == 20u && resumed.level_generation == TEST_LEVEL);
    LOOPBACK_CHECK(actual_payload_size == expected_payload_size);
    LOOPBACK_CHECK(memcmp(actual_payload, expected_payload, expected_payload_size) == 0);
    LOOPBACK_CHECK(break_world_session_sender_state(fixture.session, a_key, &a_state));
    LOOPBACK_CHECK(break_world_session_sender_state(fixture.session, b_key, &b_state));
    LOOPBACK_CHECK(!a_state.attempt_pending && a_state.history_count == 1u &&
                   a_state.confirmed_snapshot_id == 0u && a_state.next_delta_id == 2u);
    LOOPBACK_CHECK(!b_state.attempt_pending && b_state.history_count == 0u &&
                   b_state.confirmed_snapshot_id == 0u && b_state.next_delta_id == 1u);

    LOOPBACK_CHECK(write_attempt_ack(&fixture, &resumed, 1u, 0u));
    LOOPBACK_CHECK(wait_sender_confirmed_for_connection(&fixture, a_key, pending_id));
    LOOPBACK_CHECK(break_world_session_sender_state(fixture.session, b_key, &b_state));
    LOOPBACK_CHECK(b_state.history_count == 0u && b_state.confirmed_snapshot_id == 0u &&
                   b_state.next_delta_id == 1u);

cleanup:
    break_replication_reassembly_free(actual_payload);
    free(expected_payload);
    break_world_snapshot_release(ignored);
    break_world_snapshot_release(pending);
    socket_dispose(&fixture);
}

TEST(runtime_notice_real_dual_socket_budget_and_independent_ack)
{
    SocketFixture fixture;
    BreakWorldSnapshot *first = NULL;
    BreakWorldSnapshot *second = NULL;
    SocketAttempt a_first;
    SocketAttempt b_first;
    SocketAttempt a_second;
    SocketAttempt b_second;
    BreakWorldSessionSenderState a_before;
    BreakWorldSessionSenderState b_before;
    BreakWorldSessionSenderState a_after;
    BreakWorldSessionSenderState b_after;
    BreakWorldSessionSenderState a_state;
    BreakWorldSessionSenderState b_state;
    BreakConnectionKey a_key;
    BreakConnectionKey b_key;
    Entity entity;
    Value *value;
    u64 first_id;
    u64 second_id;
    usize drained = 0u;
    u8 *wire = NULL;
    usize size = 0u;

    memset(&fixture, 0, sizeof(fixture));
    fixture.client_fd = -1;
    fixture.inactive_client_fd = -1;
    fixture.fair_outbound_admission = true;
    LOOPBACK_CHECK(socket_start_with_connections(&fixture, true, 2u));
    LOOPBACK_CHECK(socket_attach_runtime_publication(&fixture, 1u));
    LOOPBACK_CHECK(connect_authenticate(&fixture));
    a_key = fixture.connection;
    socket_select_peer(&fixture, true);
    LOOPBACK_CHECK(connect_authenticate(&fixture));
    b_key = fixture.connection;
    LOOPBACK_CHECK(fixture.auth_calls == 2u && a_key != 0u && b_key != 0u && a_key != b_key);

    entity = world_create_entity(fixture.authoritative);
    LOOPBACK_CHECK(add_value(fixture.authoritative, entity, 42u));
    first = break_world_snapshot_build(fixture.authoritative, fixture.schemas, 10u);
    LOOPBACK_CHECK(first != NULL);
    first_id = break_world_snapshot_id(first);
    LOOPBACK_CHECK(socket_publish_snapshot(&fixture, first, TEST_LEVEL));

    /* submit 前记录 A/B sender state，submit 后 memcmp 必须相等。 */
    LOOPBACK_CHECK(break_world_session_sender_state(fixture.session, a_key, &a_before));
    LOOPBACK_CHECK(break_world_session_sender_state(fixture.session, b_key, &b_before));
    LOOPBACK_CHECK(socket_submit_current(&fixture, TEST_LEVEL,
                                         UINT64_C(0xF123456789ABCDEF)) == BREAK_RUNTIME_OK);
    LOOPBACK_CHECK(break_world_session_sender_state(fixture.session, a_key, &a_after));
    LOOPBACK_CHECK(break_world_session_sender_state(fixture.session, b_key, &b_after));
    LOOPBACK_CHECK(memcmp(&a_before, &a_after, sizeof(a_before)) == 0);
    LOOPBACK_CHECK(memcmp(&b_before, &b_after, sizeof(b_before)) == 0);

    LOOPBACK_CHECK(break_runtime_world_session_drain(fixture.adapter, 1u, &drained) ==
                   BREAK_RUNTIME_OK);
    LOOPBACK_CHECK(drained == 1u);
    LOOPBACK_CHECK(break_runtime_world_session_pending(fixture.adapter) == 1u);
    socket_select_peer(&fixture, false);
    LOOPBACK_CHECK(collect_published(&fixture, &a_first));
    LOOPBACK_CHECK(a_first.kind == BREAK_WORLD_DELTA_WIRE_FULL);
    LOOPBACK_CHECK(a_first.target_snapshot_id == first_id);
    LOOPBACK_CHECK(a_first.target_tick == 10u);
    LOOPBACK_CHECK(a_first.level_generation == TEST_LEVEL);
    LOOPBACK_CHECK(break_world_session_sender_state(fixture.session, a_key, &a_state));
    LOOPBACK_CHECK(break_world_session_sender_state(fixture.session, b_key, &b_state));
    LOOPBACK_CHECK(a_state.history_count == 1u && b_state.history_count == 0u);

    /* queue 空，第二次 drain 才给 B；A 不重复 full。 */
    LOOPBACK_CHECK(break_runtime_world_session_drain(fixture.adapter, 1u, &drained) ==
                   BREAK_RUNTIME_OK);
    LOOPBACK_CHECK(drained == 0u);
    LOOPBACK_CHECK(break_runtime_world_session_pending(fixture.adapter) == 0u);
    socket_select_peer(&fixture, true);
    LOOPBACK_CHECK(collect_published(&fixture, &b_first));
    LOOPBACK_CHECK(b_first.kind == BREAK_WORLD_DELTA_WIRE_FULL);
    LOOPBACK_CHECK(b_first.target_snapshot_id == a_first.target_snapshot_id);
    LOOPBACK_CHECK(b_first.target_tick == 10u);
    LOOPBACK_CHECK(break_world_session_sender_state(fixture.session, a_key, &a_state));
    LOOPBACK_CHECK(break_world_session_sender_state(fixture.session, b_key, &b_state));
    LOOPBACK_CHECK(a_state.history_count == 1u && b_state.history_count == 1u);

    /* 只 ACK A：B 的 history 不受影响。 */
    socket_select_peer(&fixture, false);
    LOOPBACK_CHECK(write_attempt_ack(&fixture, &a_first, 1u, 0u));
    LOOPBACK_CHECK(wait_sender_confirmed_for_connection(&fixture, a_key, first_id));
    LOOPBACK_CHECK(break_world_session_sender_state(fixture.session, b_key, &b_state));
    LOOPBACK_CHECK(b_state.history_count == 1u && b_state.confirmed_snapshot_id == 0u);

    /* S2/tick20：A 已确认 S1 发 DELTA/base=S1，B 未确认仍 FULL/base=0。 */
    value = (Value *)world_get_component(fixture.authoritative, entity, TEST_COMPONENT);
    LOOPBACK_CHECK(value != NULL);
    value->value = 43u;
    second = break_world_snapshot_build(fixture.authoritative, fixture.schemas, 20u);
    LOOPBACK_CHECK(second != NULL);
    second_id = break_world_snapshot_id(second);
    LOOPBACK_CHECK(socket_publish_snapshot(&fixture, second, TEST_LEVEL));
    LOOPBACK_CHECK(socket_submit_current(&fixture, TEST_LEVEL, 0u) == BREAK_RUNTIME_OK);
    LOOPBACK_CHECK(break_runtime_world_session_drain(fixture.adapter, 1u, &drained) ==
                   BREAK_RUNTIME_OK);
    LOOPBACK_CHECK(drained == 1u);
    LOOPBACK_CHECK(break_runtime_world_session_drain(fixture.adapter, 1u, &drained) ==
                   BREAK_RUNTIME_OK);
    LOOPBACK_CHECK(drained == 0u);
    LOOPBACK_CHECK(break_runtime_world_session_pending(fixture.adapter) == 0u);
    LOOPBACK_CHECK(collect_published_pair_interleaved(&fixture, &a_second, &b_second));
    LOOPBACK_CHECK(a_second.kind == BREAK_WORLD_DELTA_WIRE_DELTA);
    LOOPBACK_CHECK(a_second.base_snapshot_id == first_id);
    LOOPBACK_CHECK(b_second.kind == BREAK_WORLD_DELTA_WIRE_FULL);
    LOOPBACK_CHECK(b_second.base_snapshot_id == 0u);
    LOOPBACK_CHECK(a_second.target_snapshot_id == second_id &&
                   b_second.target_snapshot_id == second_id);
    LOOPBACK_CHECK(a_second.target_tick == 20u && b_second.target_tick == 20u);

    /* 分别 ACK A2/B2，互不裁剪对方 history。 */
    socket_select_peer(&fixture, false);
    LOOPBACK_CHECK(write_attempt_ack(&fixture, &a_second, 1u, 0u));
    LOOPBACK_CHECK(wait_sender_confirmed_for_connection(&fixture, a_key, second_id));
    LOOPBACK_CHECK(break_world_session_sender_state(fixture.session, b_key, &b_state));
    LOOPBACK_CHECK(b_state.history_count == 1u && b_state.confirmed_snapshot_id == 0u);
    socket_select_peer(&fixture, true);
    LOOPBACK_CHECK(write_attempt_ack(&fixture, &b_second, 1u, 0u));
    LOOPBACK_CHECK(wait_sender_confirmed_for_connection(&fixture, b_key, second_id));
    LOOPBACK_CHECK(break_world_session_sender_state(fixture.session, a_key, &a_state));
    LOOPBACK_CHECK(a_state.history_count == 0u && a_state.confirmed_snapshot_id == second_id);

    /* 独立 remote World：两个连接各自入站 S1，不混入同一 World。 */
    LOOPBACK_CHECK(encode_full(first, &wire, &size));
    socket_select_peer(&fixture, false);
    LOOPBACK_CHECK(write_shuffled_payload(&fixture, 100u, wire, size));
    socket_select_peer(&fixture, true);
    LOOPBACK_CHECK(write_shuffled_payload(&fixture, 100u, wire, size));
    free(wire);
    wire = NULL;
    LOOPBACK_CHECK(wait_completed(&fixture, 2u));
    LOOPBACK_CHECK(break_world_session_drain(fixture.session, a_key,
                                             fixture.remote, 1u) == 1u);
    LOOPBACK_CHECK(world_matches(fixture.remote, fixture.schemas, 10u, first_id));
    LOOPBACK_CHECK(break_world_entity_count(fixture.remote_secondary) == 0u);
    LOOPBACK_CHECK(break_world_session_drain(fixture.session, b_key,
                                             fixture.remote_secondary, 1u) == 1u);
    LOOPBACK_CHECK(world_matches(fixture.remote_secondary, fixture.schemas, 10u, first_id));

cleanup:
    free(wire);
    break_world_snapshot_release(second);
    break_world_snapshot_release(first);
    socket_dispose(&fixture);
}

TEST(runtime_notice_real_socket_replaces_lease_and_recovers_e1_e2)
{
    SocketFixture fixture;
    BreakWorldSnapshot *e1 = NULL;
    BreakWorldSnapshot *e2 = NULL;
    BreakWorldSnapshotLease lease;
    SocketAttempt b_e1;
    SocketAttempt resumed;
    SocketAttempt a_e2;
    SocketAttempt b_e2;
    BreakWorldSessionSenderState a_state;
    BreakRuntimeWorldSessionStats stats;
    BreakConnectionKey a_key;
    BreakConnectionKey b_key;
    Entity entity;
    Value *value;
    u64 e1_id;
    u64 e2_id;
    u64 e1_epoch;
    u8 *expected_payload = NULL;
    usize expected_size = 0u;
    u8 *actual_payload = NULL;
    usize actual_size = 0u;
    usize drained = 0u;

    memset(&fixture, 0, sizeof(fixture));
    fixture.client_fd = -1;
    fixture.inactive_client_fd = -1;
    fixture.fair_outbound_admission = true;
    LOOPBACK_CHECK(socket_start_with_connections(&fixture, true, 2u));
    LOOPBACK_CHECK(socket_attach_runtime_publication(&fixture, 1u));
    LOOPBACK_CHECK(connect_authenticate(&fixture));
    a_key = fixture.connection;
    socket_select_peer(&fixture, true);
    LOOPBACK_CHECK(connect_authenticate(&fixture));
    b_key = fixture.connection;
    LOOPBACK_CHECK(fixture.auth_calls == 2u && a_key != b_key);

    entity = world_create_entity(fixture.authoritative);
    LOOPBACK_CHECK(add_value(fixture.authoritative, entity, 77u));
    e1 = break_world_snapshot_build(fixture.authoritative, fixture.schemas, 30u);
    LOOPBACK_CHECK(e1 != NULL);
    e1_id = break_world_snapshot_id(e1);
    LOOPBACK_CHECK(encode_full(e1, &expected_payload, &expected_size));

    /* A 填满自身份额、发布 E1 并 notice。 */
    socket_select_peer(&fixture, false);
    for (usize i = 0u; i < TEST_DUAL_OUTBOUND_SHARE; ++i) {
        LOOPBACK_CHECK(break_net_reactor_send(fixture.reactor, a_key,
                                             BREAK_NET_MESSAGE_ID_PING, 1u, "x", 1u) ==
                       BREAK_NET_SEND_OK);
    }
    LOOPBACK_CHECK(socket_publish_snapshot(&fixture, e1, TEST_LEVEL));
    LOOPBACK_CHECK(socket_submit_current(&fixture, TEST_LEVEL, 0u) == BREAK_RUNTIME_OK);

    /* 第一次 drain：A 饱和返回 OVERLOAD，active attempt==E1。 */
    LOOPBACK_CHECK(break_runtime_world_session_drain(fixture.adapter, 1u, &drained) ==
                   BREAK_RUNTIME_OVERLOAD);
    LOOPBACK_CHECK(drained == 1u);
    LOOPBACK_CHECK(break_world_session_sender_state(fixture.session, a_key, &a_state));
    LOOPBACK_CHECK(a_state.attempt_pending);
    LOOPBACK_CHECK(a_state.attempt_target_snapshot_id == e1_id);
    LOOPBACK_CHECK(a_state.attempt_target_tick == 30u);
    break_runtime_world_session_stats(fixture.adapter, &stats);
    LOOPBACK_CHECK(stats.publish_overloads == 1u);
    LOOPBACK_CHECK(break_runtime_world_session_pending(fixture.adapter) != 0u);

    /* 第二次 drain：显式 fair admission 下 A 饱和不阻断 B，B 收到 E1 full。 */
    LOOPBACK_CHECK(break_runtime_world_session_drain(fixture.adapter, 1u, &drained) ==
                   BREAK_RUNTIME_OK);
    socket_select_peer(&fixture, true);
    LOOPBACK_CHECK(collect_published(&fixture, &b_e1));
    LOOPBACK_CHECK(b_e1.kind == BREAK_WORLD_DELTA_WIRE_FULL);
    LOOPBACK_CHECK(b_e1.target_snapshot_id == e1_id && b_e1.target_tick == 30u);

    /* 逐个读走 A 的全部 PING，不用固定 sleep。 */
    socket_select_peer(&fixture, false);
    for (usize i = 0u; i < TEST_DUAL_OUTBOUND_SHARE; ++i) {
        SocketFrame frame;
        LOOPBACK_CHECK(read_frame(&fixture, &frame));
        LOOPBACK_CHECK(frame.message_id == BREAK_NET_MESSAGE_ID_PING &&
                       frame.payload_size == 1u && frame.payload[0] == (u8)'x');
    }

    /* publication publish 替换 current 为 E2；本地 acquire 得 E2 和新 epoch。 */
    value = (Value *)world_get_component(fixture.authoritative, entity, TEST_COMPONENT);
    LOOPBACK_CHECK(value != NULL);
    value->value = 99u;
    e2 = break_world_snapshot_build(fixture.authoritative, fixture.schemas, 40u);
    LOOPBACK_CHECK(e2 != NULL);
    e2_id = break_world_snapshot_id(e2);
    LOOPBACK_CHECK(e2_id != e1_id);
    LOOPBACK_CHECK(socket_publish_snapshot(&fixture, e2, TEST_LEVEL));
    memset(&lease, 0, sizeof(lease));
    LOOPBACK_CHECK(break_world_snapshot_publication_acquire(fixture.publication, &lease) ==
                   BREAK_WORLD_SNAPSHOT_ACQUIRE_OK);
    LOOPBACK_CHECK(break_world_snapshot_id(lease.snapshot) == e2_id);
    e1_epoch = lease.publication_epoch;
    LOOPBACK_CHECK(e1_epoch != 0u);
    break_world_snapshot_lease_release(&lease);
    LOOPBACK_CHECK(lease.snapshot == NULL && lease.level_generation == 0u &&
                   lease.publication_epoch == 0u);

    /* 释放调用方 E1 引用；Session active attempt 仍拥有它。 */
    break_world_snapshot_release(e1);
    e1 = NULL;

    /* 不提交新 notice；continuation 自行 acquire E2，A 续发旧 E1。 */
    LOOPBACK_CHECK(break_runtime_world_session_drain(fixture.adapter, 1u, &drained) ==
                   BREAK_RUNTIME_OK);
    LOOPBACK_CHECK(collect_published_with_payload(&fixture, &resumed, &actual_payload,
                                                  &actual_size));
    LOOPBACK_CHECK(resumed.kind == BREAK_WORLD_DELTA_WIRE_FULL);
    LOOPBACK_CHECK(resumed.target_snapshot_id == e1_id);
    LOOPBACK_CHECK(resumed.target_snapshot_id != e2_id);
    LOOPBACK_CHECK(resumed.target_tick == 30u);
    LOOPBACK_CHECK(actual_size == expected_size);
    LOOPBACK_CHECK(memcmp(actual_payload, expected_payload, expected_size) == 0);
    LOOPBACK_CHECK(break_runtime_world_session_pending(fixture.adapter) != 0u);

    /* 后续 drain 分别让 B/A 发 E2，最终两个 socket 都收到 E2 target，pending=0。 */
    for (u32 round = 0u;
         round < 8u && break_runtime_world_session_pending(fixture.adapter) != 0u; ++round) {
        LOOPBACK_CHECK(break_runtime_world_session_drain(fixture.adapter, 1u, &drained) ==
                       BREAK_RUNTIME_OK);
    }
    LOOPBACK_CHECK(break_runtime_world_session_pending(fixture.adapter) == 0u);
    socket_select_peer(&fixture, false);
    LOOPBACK_CHECK(collect_published(&fixture, &a_e2));
    LOOPBACK_CHECK(a_e2.target_snapshot_id == e2_id && a_e2.target_tick == 40u);
    socket_select_peer(&fixture, true);
    LOOPBACK_CHECK(collect_published(&fixture, &b_e2));
    LOOPBACK_CHECK(b_e2.target_snapshot_id == e2_id && b_e2.target_tick == 40u);

    /* 再次 acquire current，确认仍是 E2；recovery 不依赖调用方 E1 指针。 */
    memset(&lease, 0, sizeof(lease));
    LOOPBACK_CHECK(break_world_snapshot_publication_acquire(fixture.publication, &lease) ==
                   BREAK_WORLD_SNAPSHOT_ACQUIRE_OK);
    LOOPBACK_CHECK(break_world_snapshot_id(lease.snapshot) == e2_id);
    break_world_snapshot_lease_release(&lease);

cleanup:
    break_replication_reassembly_free(actual_payload);
    free(expected_payload);
    break_world_snapshot_release(e2);
    break_world_snapshot_release(e1);
    socket_dispose(&fixture);
}

#define RUNTIME_SOCKET_RACE_ROUNDS 8u

typedef struct {
    SocketFixture *fixture;
    Entity entity;
    _Atomic u32 ready;
    _Atomic bool go;
    _Atomic bool done;
    _Atomic bool failed;
    u32 accepted;
} RuntimeSocketNoticeRace;

static PLATFORM_THREAD_RET runtime_socket_notice_race_producer(PLATFORM_THREAD_ARG argument)
{
    RuntimeSocketNoticeRace *race = (RuntimeSocketNoticeRace *)argument;
    SocketFixture *fixture = race->fixture;
    atomic_store_explicit(&race->ready, 1u, memory_order_release);
    while (!atomic_load_explicit(&race->go, memory_order_acquire)) {
        platform_thread_yield();
    }
    for (u32 i = 0u; i < RUNTIME_SOCKET_RACE_ROUNDS; ++i) {
        BreakWorldSnapshot *snapshot;
        Value *value = (Value *)world_get_component(fixture->authoritative, race->entity,
                                                    TEST_COMPONENT);
        if (!value) { atomic_store_explicit(&race->failed, true, memory_order_release); break; }
        value->value = 100u + i;
        snapshot = break_world_snapshot_build(fixture->authoritative, fixture->schemas,
                                              (u64)i + 1u);
        if (!snapshot || !socket_publish_snapshot(fixture, snapshot, TEST_LEVEL)) {
            break_world_snapshot_release(snapshot);
            atomic_store_explicit(&race->failed, true, memory_order_release);
            break;
        }
        for (u32 spin = 0u; spin < 1000000u; ++spin) {
            BreakRuntimeError result = socket_submit_current(fixture, TEST_LEVEL,
                                                             UINT64_C(0xD5754) + i);
            if (result == BREAK_RUNTIME_OK) { race->accepted++; break; }
            if (result != BREAK_RUNTIME_OVERLOAD || spin == 999999u) {
                atomic_store_explicit(&race->failed, true, memory_order_release);
                break;
            }
            platform_thread_yield();
        }
        break_world_snapshot_release(snapshot);
        if (atomic_load_explicit(&race->failed, memory_order_relaxed)) break;
    }
    atomic_store_explicit(&race->done, true, memory_order_release);
    return PLATFORM_THREAD_RETURN;
}

static bool race_collect_connection(SocketFixture *fixture, BreakConnectionKey key,
                                    bool secondary, u64 final_id)
{
    BreakWorldSessionSenderState state;
    u64 attempts;
    u64 last_tick = 0u;
    u64 last_id = 0u;
    if (!break_world_session_sender_state(fixture->session, key, &state)) return false;
    if (state.next_delta_id == 0u) return false;
    attempts = state.next_delta_id - 1u;
    if (attempts == 0u) return false;
    socket_select_peer(fixture, secondary);
    for (u64 i = 0u; i < attempts; ++i) {
        SocketAttempt attempt;
        if (!collect_published(fixture, &attempt)) return false;
        if (i != 0u && attempt.target_tick <= last_tick) return false;
        last_tick = attempt.target_tick;
        last_id = attempt.target_snapshot_id;
    }
    return last_id == final_id;
}

TEST(RuntimeSocketNoticeRace)
{
    SocketFixture fixture;
    RuntimeSocketNoticeRace race;
    PlatformThread thread;
    BreakWorldSnapshotLease lease;
    BreakRuntimeWorldSessionStats stats;
    BreakConnectionKey a_key;
    BreakConnectionKey b_key;
    u64 final_id = 0u;
    usize drained = 0u;
    bool ready = false;

    memset(&fixture, 0, sizeof(fixture));
    fixture.client_fd = -1;
    fixture.inactive_client_fd = -1;
    LOOPBACK_CHECK(socket_start_with_connections(&fixture, true, 2u));
    LOOPBACK_CHECK(socket_attach_runtime_publication(&fixture, 2u));
    LOOPBACK_CHECK(connect_authenticate(&fixture));
    a_key = fixture.connection;
    socket_select_peer(&fixture, true);
    LOOPBACK_CHECK(connect_authenticate(&fixture));
    b_key = fixture.connection;
    LOOPBACK_CHECK(fixture.auth_calls == 2u && a_key != b_key);
    socket_select_peer(&fixture, false);

    memset(&race, 0, sizeof(race));
    race.fixture = &fixture;
    race.entity = world_create_entity(fixture.authoritative);
    LOOPBACK_CHECK(add_value(fixture.authoritative, race.entity, 1u));
    atomic_init(&race.ready, 0u);
    atomic_init(&race.go, false);
    atomic_init(&race.done, false);
    atomic_init(&race.failed, false);
    LOOPBACK_CHECK(platform_thread_create(&thread, runtime_socket_notice_race_producer, &race));
    for (u32 spin = 0u; spin < 1000000u && !ready; ++spin) {
        ready = atomic_load_explicit(&race.ready, memory_order_acquire) != 0u;
        if (!ready) platform_thread_yield();
    }
    LOOPBACK_CHECK(ready);
    atomic_store_explicit(&race.go, true, memory_order_release);

    for (u32 spin = 0u;
         spin < 1000000u && !atomic_load_explicit(&race.done, memory_order_acquire); ++spin) {
        (void)break_runtime_world_session_drain(fixture.adapter, 4u, &drained);
        (void)pump(&fixture);
        platform_thread_yield();
    }
    platform_thread_join(thread);
    for (u32 round = 0u;
         round < 1024u && break_runtime_world_session_pending(fixture.adapter) != 0u;
         ++round) {
        (void)break_runtime_world_session_drain(fixture.adapter, 4u, &drained);
        (void)pump(&fixture);
    }

    LOOPBACK_CHECK(!atomic_load_explicit(&race.failed, memory_order_acquire));
    LOOPBACK_CHECK(race.accepted == RUNTIME_SOCKET_RACE_ROUNDS);
    LOOPBACK_CHECK(break_runtime_world_session_pending(fixture.adapter) == 0u);
    break_runtime_world_session_stats(fixture.adapter, &stats);
    LOOPBACK_CHECK(!stats.publish_pending);

    memset(&lease, 0, sizeof(lease));
    LOOPBACK_CHECK(break_world_snapshot_publication_acquire(fixture.publication, &lease) ==
                   BREAK_WORLD_SNAPSHOT_ACQUIRE_OK);
    LOOPBACK_CHECK(break_world_snapshot_tick(lease.snapshot) ==
                   (u64)RUNTIME_SOCKET_RACE_ROUNDS);
    final_id = break_world_snapshot_id(lease.snapshot);
    break_world_snapshot_lease_release(&lease);

    LOOPBACK_CHECK(race_collect_connection(&fixture, a_key, false, final_id));
    LOOPBACK_CHECK(race_collect_connection(&fixture, b_key, true, final_id));

cleanup:
    socket_dispose(&fixture);
}

/* __RUNTIME_SOCKET_TESTS__ */

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
    RUN_TEST(world_session_real_socket_control_correlation_preserves_v1_v2_and_sequences);
    RUN_TEST(world_session_real_socket_reorders_duplicates_and_recovers_with_full);
    RUN_TEST(world_session_same_socket_rebaselines_and_rejects_late_traffic);
    RUN_TEST(world_session_default_outbound_admission_keeps_global_capacity);
    RUN_TEST(world_session_two_sockets_share_snapshots_with_independent_recovery);
    RUN_TEST(world_session_pending_snapshot_attempt_outlives_caller_lease);
    RUN_TEST(runtime_notice_real_dual_socket_budget_and_independent_ack);
    RUN_TEST(runtime_notice_real_socket_replaces_lease_and_recovers_e1_e2);
    RUN_TEST(RuntimeSocketNoticeRace);
    RUN_TEST(world_session_registry_without_delta_fails_then_restores);
TEST_MAIN_END()
