#include "test_framework.h"
#include <network/break_net_adapter.h>
#include <network/break_net_envelope.h>
#include <network/break_net_message_registry.h>
#include <network/break_net_events.h>
#include <network/break_session.h>

#include <stdint.h>
#include <time.h>
#include <string.h>
#include <arpa/inet.h>
#include <poll.h>
#include <sys/socket.h>
#include <unistd.h>
#include <snow/acceptor.h>
#include <snow/endpoint.h>

extern int usleep(unsigned int);
#ifndef CLOCK_MONOTONIC
#define CLOCK_MONOTONIC 1
#endif
extern int clock_gettime(int, struct timespec *);

static uint64_t break_session_monotonic_us(void)
{
    struct timespec now;
    clock_gettime(CLOCK_MONOTONIC, &now);
    return (uint64_t)now.tv_sec * UINT64_C(1000000) +
           (uint64_t)now.tv_nsec / UINT64_C(1000);
}

static const uint8_t k_payload[] = {0x10u, 0x20u, 0x30u, 0x40u};
static size_t g_auth_dispatches;
static bool g_handler_result = true;
static bool break_test_auth_handler(BreakConnectionKey connection,
                                    const BreakNetOwnedMessage *message,
                                    void *user_data)
{
    (void)connection;
    (void)message;
    (void)user_data;
    ++g_auth_dispatches;
    return g_handler_result;
}

static BreakNetEnvelope break_test_envelope(uint16_t version, uint16_t message_id,
                                            uint16_t flags, uint32_t sequence,
                                            const void *payload, size_t payload_size)
{
    BreakNetEnvelope envelope = {0};
    envelope.protocol_version = version;
    envelope.message_id = message_id;
    envelope.flags = flags;
    envelope.sequence = sequence;
    envelope.payload = payload;
    envelope.payload_size = payload_size;
    return envelope;
}

TEST(break_envelope_round_trip_preserves_fields)
{
    uint8_t encoded[BREAK_NET_ENVELOPE_MAX_SIZE];
    BreakNetEnvelope input = break_test_envelope(
        BREAK_NET_PROTOCOL_VERSION, BREAK_NET_MESSAGE_ID_AUTH, 0x0003u,
        0x01020304u, k_payload, sizeof(k_payload));
    BreakNetEnvelope output = {0};
    size_t encoded_size = 0u;

    ASSERT_EQ(break_net_envelope_encode(&input, encoded, sizeof(encoded),
                                        &encoded_size),
              BREAK_NET_ENVELOPE_OK);
    ASSERT_EQ(break_net_envelope_decode(encoded, encoded_size, &output),
              BREAK_NET_ENVELOPE_OK);
    ASSERT_EQ(output.protocol_version, input.protocol_version);
    ASSERT_EQ(output.message_id, input.message_id);
    ASSERT_EQ(output.flags, input.flags);
    ASSERT_EQ(output.sequence, input.sequence);
    ASSERT_EQ(output.payload_size, sizeof(k_payload));
    ASSERT_TRUE(memcmp(output.payload, k_payload, sizeof(k_payload)) == 0);
}

TEST(break_envelope_uses_little_endian_wire_order)
{
    uint8_t encoded[BREAK_NET_ENVELOPE_MAX_SIZE] = {0};
    BreakNetEnvelope input = break_test_envelope(
        BREAK_NET_PROTOCOL_VERSION, BREAK_NET_MESSAGE_ID_PING, 0x0006u,
        0x0708090au, NULL, 0u);
    size_t encoded_size = 0u;

    ASSERT_EQ(break_net_envelope_encode(&input, encoded, sizeof(encoded),
                                        &encoded_size),
              BREAK_NET_ENVELOPE_OK);
    ASSERT_EQ(encoded_size, BREAK_NET_ENVELOPE_HEADER_SIZE);
    ASSERT_EQ(encoded[0], 0x31u);
    ASSERT_EQ(encoded[1], 0x4bu);
    ASSERT_EQ(encoded[2], 0x52u);
    ASSERT_EQ(encoded[3], 0x42u);
    ASSERT_EQ(encoded[4], 0x01u);
    ASSERT_EQ(encoded[5], 0x00u);
    ASSERT_EQ(encoded[6], 0x02u);
    ASSERT_EQ(encoded[7], 0x00u);
    ASSERT_EQ(encoded[8], 0x06u);
    ASSERT_EQ(encoded[9], 0x00u);
    ASSERT_EQ(encoded[10], 0x0au);
    ASSERT_EQ(encoded[11], 0x09u);
    ASSERT_EQ(encoded[12], 0x08u);
    ASSERT_EQ(encoded[13], 0x07u);
    ASSERT_EQ(encoded[14], 0x00u);
    ASSERT_EQ(encoded[15], 0x00u);
    ASSERT_EQ(encoded[16], 0x00u);
    ASSERT_EQ(encoded[17], 0x00u);
}

TEST(break_envelope_accepts_minimum_zero_and_exact_max_payloads)
{
    uint8_t encoded[BREAK_NET_ENVELOPE_MAX_SIZE + BREAK_NET_ENVELOPE_HEADER_SIZE];
    uint8_t max_payload[BREAK_NET_ENVELOPE_MAX_PAYLOAD_SIZE];
    BreakNetEnvelope envelope;
    size_t encoded_size = 0u;

    memset(max_payload, 0x7fu, sizeof(max_payload));
    envelope = break_test_envelope(BREAK_NET_PROTOCOL_VERSION,
                                   BREAK_NET_MESSAGE_ID_PING, 0u, 1u, NULL, 0u);
    ASSERT_EQ(break_net_envelope_encode(&envelope, encoded, sizeof(encoded),
                                        &encoded_size), BREAK_NET_ENVELOPE_OK);
    ASSERT_EQ(encoded_size, BREAK_NET_ENVELOPE_HEADER_SIZE);

    envelope.payload = max_payload;
    envelope.payload_size = sizeof(max_payload);
    ASSERT_EQ(break_net_envelope_encode(&envelope, encoded, sizeof(encoded),
                                        &encoded_size), BREAK_NET_ENVELOPE_OK);
    ASSERT_EQ(encoded_size, sizeof(max_payload) + BREAK_NET_ENVELOPE_HEADER_SIZE);
}

TEST(break_envelope_rejects_over_limit_unknown_id_and_version)
{
    uint8_t encoded[BREAK_NET_ENVELOPE_MAX_SIZE + BREAK_NET_ENVELOPE_HEADER_SIZE];
    uint8_t over_limit[BREAK_NET_ENVELOPE_MAX_PAYLOAD_SIZE + 1u];
    BreakNetEnvelope envelope;
    size_t encoded_size = 0u;

    envelope = break_test_envelope(BREAK_NET_PROTOCOL_VERSION,
                                   BREAK_NET_MESSAGE_ID_PING, 0u, 1u,
                                   over_limit, sizeof(over_limit));
    ASSERT_EQ(break_net_envelope_encode(&envelope, encoded, sizeof(encoded),
                                        &encoded_size), BREAK_NET_ENVELOPE_OVER_LIMIT);

    envelope = break_test_envelope(BREAK_NET_PROTOCOL_VERSION, 0xffffu, 0u, 1u,
                                   NULL, 0u);
    ASSERT_EQ(break_net_envelope_encode(&envelope, encoded, sizeof(encoded),
                                        &encoded_size), BREAK_NET_ENVELOPE_UNKNOWN_MESSAGE);

    envelope = break_test_envelope(BREAK_NET_PROTOCOL_VERSION + 1u,
                                   BREAK_NET_MESSAGE_ID_PING, 0u, 1u,
                                   NULL, 0u);
    ASSERT_EQ(break_net_envelope_encode(&envelope, encoded, sizeof(encoded),
                                        &encoded_size), BREAK_NET_ENVELOPE_UNSUPPORTED_VERSION);
}

TEST(break_envelope_rejects_malformed_lengths_and_bad_sequence)
{
    uint8_t encoded[BREAK_NET_ENVELOPE_MAX_SIZE] = {0};
    BreakNetEnvelope envelope = break_test_envelope(
        BREAK_NET_PROTOCOL_VERSION, BREAK_NET_MESSAGE_ID_PING, 0u, 10u,
        NULL, 0u);
    BreakNetEnvelope decoded = {0};
    BreakNetEnvelopeContext context = {0};
    size_t encoded_size = 0u;

    ASSERT_EQ(break_net_envelope_encode(&envelope, encoded, sizeof(encoded),
                                        &encoded_size), BREAK_NET_ENVELOPE_OK);
    ASSERT_EQ(break_net_envelope_decode_with_context(&context, encoded,
                                                     encoded_size, &decoded),
              BREAK_NET_ENVELOPE_OK);
    ASSERT_EQ(break_net_envelope_decode_with_context(&context, encoded,
                                                     encoded_size, &decoded),
              BREAK_NET_ENVELOPE_INVALID_SEQUENCE);
    encoded[14u] = 1u;
    ASSERT_EQ(break_net_envelope_decode(encoded, encoded_size, &decoded),
              BREAK_NET_ENVELOPE_INVALID_LENGTH);
}

TEST(break_session_legal_transitions_and_unknown_connection)
{
    BreakSessionConfig config = {0};
    BreakSessionManager *manager = break_session_manager_create(&config);
    const BreakConnectionKey connection = 0x11u;

    ASSERT_NOT_NULL(manager);
    ASSERT_EQ(break_session_manager_state(manager, 0x99u), BREAK_SESSION_UNKNOWN);
    ASSERT_TRUE(break_session_manager_bind(manager, 0x99u));
    ASSERT_EQ(break_session_manager_state(manager, 0x99u), BREAK_SESSION_NEW);
    ASSERT_TRUE(break_session_manager_bind(manager, connection));
    ASSERT_EQ(break_session_manager_state(manager, connection), BREAK_SESSION_NEW);
    ASSERT_TRUE(break_session_manager_begin_auth(manager, connection));
    ASSERT_EQ(break_session_manager_state(manager, connection),
              BREAK_SESSION_AUTHENTICATING);
    ASSERT_TRUE(break_session_manager_auth_succeeded(manager, connection));
    ASSERT_EQ(break_session_manager_state(manager, connection),
              BREAK_SESSION_AUTHENTICATED);
    ASSERT_TRUE(break_session_manager_close(manager, connection, 0u));
    ASSERT_EQ(break_session_manager_state(manager, connection), BREAK_SESSION_CLOSING);
    ASSERT_TRUE(break_session_manager_poll(manager, 16u) >= 0u);
    ASSERT_EQ(break_session_manager_state(manager, connection), BREAK_SESSION_CLOSED);
    ASSERT_EQ(break_session_manager_state(manager, 0xaau), BREAK_SESSION_UNKNOWN);
    break_session_manager_destroy(manager);
}

TEST(break_session_rejects_backward_transition_and_duplicate_auth)
{
    BreakSessionConfig config = {0};
    BreakSessionManager *manager = break_session_manager_create(&config);
    const BreakConnectionKey connection = 0x22u;

    ASSERT_NOT_NULL(manager);
    ASSERT_TRUE(break_session_manager_bind(manager, connection));
    ASSERT_TRUE(break_session_manager_begin_auth(manager, connection));
    ASSERT_TRUE(break_session_manager_auth_succeeded(manager, connection));
    ASSERT_FALSE(break_session_manager_begin_auth(manager, connection));
    ASSERT_FALSE(break_session_manager_transition(manager, connection,
                                                   BREAK_SESSION_NEW));
    break_session_manager_destroy(manager);
}

TEST(break_session_rejects_stale_event_after_close)
{
    BreakSessionConfig config = {0};
    BreakSessionManager *manager = break_session_manager_create(&config);
    const BreakConnectionKey connection = 0x33u;

    ASSERT_NOT_NULL(manager);
    ASSERT_TRUE(break_session_manager_bind(manager, connection));
    ASSERT_TRUE(break_session_manager_close(manager, connection, 7u));
    ASSERT_FALSE(break_session_manager_apply_event(
        manager, connection, BREAK_SESSION_EVENT_AUTHENTICATED));
    ASSERT_TRUE(break_session_manager_poll(manager, 16u) >= 0u);
    ASSERT_EQ(break_session_manager_state(manager, connection), BREAK_SESSION_CLOSED);
    break_session_manager_destroy(manager);
}

TEST(break_session_enforces_capacity_duplicate_bind_and_closed_rebind_policy)
{
    BreakSessionConfig config = {2u, 100u, NULL};
    BreakSessionManager *manager = break_session_manager_create(&config);
    const BreakConnectionKey first = 0x44u;
    const BreakConnectionKey second = 0x55u;
    const BreakConnectionKey third = 0x66u;

    ASSERT_NOT_NULL(manager);
    ASSERT_TRUE(break_session_manager_bind(manager, first));
    ASSERT_TRUE(break_session_manager_bind(manager, second));
    ASSERT_FALSE(break_session_manager_bind(manager, first));
    ASSERT_FALSE(break_session_manager_bind(manager, third));
    ASSERT_TRUE(break_session_manager_close(manager, first, 0u));
    ASSERT_TRUE(break_session_manager_close(manager, second, 0u));
    ASSERT_EQ(break_session_manager_poll(manager, 1u), 1u);
    ASSERT_EQ(break_session_manager_state(manager, first), BREAK_SESSION_CLOSED);
    ASSERT_EQ(break_session_manager_state(manager, second), BREAK_SESSION_CLOSING);
    ASSERT_EQ(break_session_manager_poll(manager, 1u), 1u);
    ASSERT_EQ(break_session_manager_state(manager, second), BREAK_SESSION_CLOSED);
    ASSERT_FALSE(break_session_manager_bind(manager, first));
    ASSERT_FALSE(break_session_manager_bind(manager, third));
    break_session_manager_destroy(manager);
}

TEST(break_session_rejects_session_id_overflow)
{
    BreakSessionConfig config = {2u, UINT64_MAX, NULL};
    BreakSessionManager *manager = break_session_manager_create(&config);

    ASSERT_NOT_NULL(manager);
    ASSERT_TRUE(break_session_manager_bind(manager, 0x66u));
    ASSERT_EQ(break_session_manager_session_id(manager, 0x66u), UINT64_MAX);
    ASSERT_FALSE(break_session_manager_bind(manager, 0x77u));
    break_session_manager_destroy(manager);
}

TEST(break_session_applies_adapter_lifecycle_without_taking_payload_ownership)
{
    BreakSessionConfig config = {0};
    BreakSessionManager *manager = break_session_manager_create(&config);
    BreakNetEvent opened = {0};
    BreakNetEvent message = {0};
    BreakNetEvent closed = {0};
    unsigned char payload = 0x5au;
    BreakNetMessageView view = {BREAK_NET_MESSAGE_ID_PING, 1u, 1u, &payload, 1u};

    ASSERT_NOT_NULL(manager);
    opened.type = BREAK_NET_EVENT_CONNECTION_OPENED;
    opened.connection_key = 0x88u;
    ASSERT_TRUE(break_session_manager_apply_adapter_event(manager, &opened));
    ASSERT_EQ(break_session_manager_state(manager, 0x88u), BREAK_SESSION_NEW);
    ASSERT_FALSE(break_session_manager_apply_adapter_event(manager, &opened));
    ASSERT_EQ(break_session_manager_last_result(manager), BREAK_SESSION_APPLY_DUPLICATE);

    message.type = BREAK_NET_EVENT_MESSAGE_RECEIVED;
    message.connection_key = 0x88u;
    ASSERT_EQ(break_net_message_copy(&message.message, &view), BREAK_NET_MESSAGE_OK);
    ASSERT_FALSE(break_session_manager_apply_adapter_event(manager, &message));
    ASSERT_NOT_NULL(message.message.data);
    break_net_event_release(&message);

    closed.type = BREAK_NET_EVENT_CONNECTION_CLOSED;
    closed.connection_key = 0x88u;
    closed.reason = 9u;
    ASSERT_TRUE(break_session_manager_apply_adapter_event(manager, &closed));
    ASSERT_EQ(break_session_manager_state(manager, 0x88u), BREAK_SESSION_CLOSING);
    ASSERT_TRUE(break_session_manager_poll(manager, 1u) == 1u);
    ASSERT_EQ(break_session_manager_state(manager, 0x88u), BREAK_SESSION_CLOSED);
    ASSERT_FALSE(break_session_manager_apply_adapter_event(manager, &message));
    ASSERT_FALSE(break_session_manager_apply_adapter_event(manager, &closed));
    ASSERT_FALSE(break_session_manager_apply_adapter_event(manager, &(BreakNetEvent){
        BREAK_NET_EVENT_MESSAGE_RECEIVED, 0x99u, 0u, {0}
    }));

    break_net_event_release(&opened);
    break_net_event_release(&closed);
    break_session_manager_destroy(manager);
}

TEST(break_session_polls_adapter_and_dispatches_auth_phase)
{
    BreakSessionConfig config = {0};
    BreakNetReactorConfig reactor_config = {BREAK_NET_DRIVE_STEP, 0, 4u, 0, 0u, 0u};
    BreakSessionManager *manager = break_session_manager_create(&config);
    BreakNetReactor *reactor = break_net_reactor_create(&reactor_config);
    const unsigned char auth_payload = 0x01u;

    ASSERT_NOT_NULL(manager);
    ASSERT_NOT_NULL(reactor);
    ASSERT_TRUE(break_session_manager_attach_reactor(manager, reactor));
    ASSERT_TRUE(break_session_manager_set_message_handler(
        manager, BREAK_NET_MESSAGE_ID_AUTH, break_test_auth_handler, NULL));
    ASSERT_TRUE(break_net_reactor_enqueue_opened_for_test(reactor, 0x101u));
    ASSERT_TRUE(break_net_reactor_enqueue_message_for_test(
        reactor, 0x101u, BREAK_NET_MESSAGE_ID_AUTH, BREAK_NET_PROTOCOL_VERSION,
        &auth_payload, sizeof(auth_payload)));
    ASSERT_EQ(break_session_manager_poll_adapter(manager, 8u), 2u);
    ASSERT_EQ(break_session_manager_state(manager, 0x101u),
              BREAK_SESSION_AUTHENTICATED);
    ASSERT_EQ(g_auth_dispatches, 1u);
    ASSERT_EQ(break_session_manager_poll_adapter(manager, 8u), 0u);

    break_session_manager_destroy(manager);
    break_net_reactor_destroy(reactor);
}

TEST(break_session_stale_close_watermark_rejects_queued_message)
{
    BreakSessionConfig config = {0};
    BreakNetReactorConfig reactor_config = {BREAK_NET_DRIVE_STEP, 0, 4u, 0, 0u, 0u};
    BreakSessionManager *manager = break_session_manager_create(&config);
    BreakNetReactor *reactor = break_net_reactor_create(&reactor_config);
    const unsigned char auth_payload = 0x02u;
    BreakSessionApplyStats stats = {0};

    ASSERT_NOT_NULL(manager);
    ASSERT_NOT_NULL(reactor);
    ASSERT_TRUE(break_session_manager_attach_reactor(manager, reactor));
    ASSERT_TRUE(break_net_reactor_enqueue_opened_for_test(reactor, 0x202u));
    ASSERT_TRUE(break_session_manager_poll_adapter(manager, 1u) == 1u);
    ASSERT_TRUE(break_session_manager_begin_auth(manager, 0x202u));
    ASSERT_TRUE(break_session_manager_close(manager, 0x202u, 9u));
    ASSERT_TRUE(break_net_reactor_enqueue_message_for_test(
        reactor, 0x202u, BREAK_NET_MESSAGE_ID_AUTH, BREAK_NET_PROTOCOL_VERSION,
        &auth_payload, sizeof(auth_payload)));
    ASSERT_TRUE(break_net_reactor_enqueue_opened_for_test(reactor, 0x202u));
    ASSERT_EQ(break_session_manager_poll_adapter(manager, 1u), 1u);
    ASSERT_EQ(break_session_manager_state(manager, 0x202u), BREAK_SESSION_CLOSING);
    ASSERT_EQ(break_session_manager_last_result(manager), BREAK_SESSION_APPLY_STALE);
    ASSERT_EQ(break_session_manager_poll_adapter(manager, 1u), 1u);
    ASSERT_EQ(break_session_manager_state(manager, 0x202u), BREAK_SESSION_CLOSED);
    ASSERT_EQ(break_session_manager_last_result(manager), BREAK_SESSION_APPLY_STALE);
    break_session_manager_apply_stats(manager, &stats);
    ASSERT_EQ(stats.stale, 2u);
    ASSERT_EQ(stats.duplicate, 0u);

    break_session_manager_destroy(manager);
    break_net_reactor_destroy(reactor);
}

TEST(break_session_auth_handler_failure_closes_without_authenticating)
{
    BreakSessionConfig config = {0};
    BreakSessionManager *manager = break_session_manager_create(&config);
    BreakNetEvent opened = {0};
    BreakNetEvent message = {0};
    const unsigned char payload = 0x03u;
    BreakNetMessageView view = {BREAK_NET_MESSAGE_ID_AUTH, 1u, 1u,
                                &payload, sizeof(payload)};

    ASSERT_NOT_NULL(manager);
    opened.type = BREAK_NET_EVENT_CONNECTION_OPENED;
    opened.connection_key = 0x303u;
    ASSERT_TRUE(break_session_manager_apply_adapter_event(manager, &opened));
    ASSERT_TRUE(break_session_manager_set_message_handler(
        manager, BREAK_NET_MESSAGE_ID_AUTH, break_test_auth_handler, NULL));
    g_handler_result = false;
    ASSERT_EQ(break_net_message_copy(&message.message, &view), BREAK_NET_MESSAGE_OK);
    message.type = BREAK_NET_EVENT_MESSAGE_RECEIVED;
    message.connection_key = 0x303u;
    ASSERT_FALSE(break_session_manager_apply_adapter_event(manager, &message));
    ASSERT_EQ(break_session_manager_state(manager, 0x303u), BREAK_SESSION_CLOSING);
    ASSERT_EQ(break_session_manager_last_result(manager), BREAK_SESSION_APPLY_HANDLER_FAILED);
    {
        BreakSessionApplyStats stats = {0};
        break_session_manager_apply_stats(manager, &stats);
        ASSERT_EQ(stats.applied, 1u);
        ASSERT_EQ(stats.handler_failed, 1u);
    }
    g_handler_result = true;
    break_net_event_release(&message);
    break_session_manager_destroy(manager);
}

TEST(break_session_ping_duplicate_is_idempotent_and_observable)
{
    BreakSessionConfig config = {0};
    BreakSessionManager *manager = break_session_manager_create(&config);
    BreakNetEvent opened = {0};
    BreakNetEvent first = {0};
    BreakNetEvent duplicate = {0};
    const unsigned char payload = 0x04u;
    BreakNetMessageView view = {BREAK_NET_MESSAGE_ID_PING, 1u, 77u,
                                &payload, sizeof(payload)};
    BreakSessionApplyStats stats = {0};

    ASSERT_NOT_NULL(manager);
    opened.type = BREAK_NET_EVENT_CONNECTION_OPENED;
    opened.connection_key = 0x404u;
    ASSERT_TRUE(break_session_manager_apply_adapter_event(manager, &opened));
    ASSERT_TRUE(break_session_manager_set_message_handler(
        manager, BREAK_NET_MESSAGE_ID_PING, break_test_auth_handler, NULL));
    g_auth_dispatches = 0u;
    ASSERT_EQ(break_net_message_copy(&first.message, &view), BREAK_NET_MESSAGE_OK);
    ASSERT_EQ(break_net_message_copy(&duplicate.message, &view), BREAK_NET_MESSAGE_OK);
    first.type = duplicate.type = BREAK_NET_EVENT_MESSAGE_RECEIVED;
    first.connection_key = duplicate.connection_key = 0x404u;
    ASSERT_TRUE(break_session_manager_apply_adapter_event(manager, &first));
    ASSERT_TRUE(break_session_manager_apply_adapter_event(manager, &duplicate));
    ASSERT_EQ(break_session_manager_last_result(manager), BREAK_SESSION_APPLY_OK);
    break_session_manager_apply_stats(manager, &stats);
    ASSERT_EQ(stats.duplicate, 0u);
    ASSERT_EQ(g_auth_dispatches, 1u);
    break_net_event_release(&first);
    break_net_event_release(&duplicate);
    break_session_manager_destroy(manager);
}

TEST(break_session_uses_attached_registry_phase_and_duplicate_policy)
{
    BreakNetMessageRegistry registry;
    BreakSessionConfig config = {0};
    BreakSessionManager *manager;
    BreakNetEvent opened = {0};
    BreakNetEvent first = {0};
    BreakNetEvent duplicate = {0};
    const unsigned char payload = 0x05u;
    BreakNetMessageDefinition definition = {
        77u, 1u, 1u, BREAK_NET_MAX_PAYLOAD_SIZE,
        BREAK_NET_MESSAGE_PHASE_AUTHENTICATING,
        BREAK_NET_DUPLICATE_IDEMPOTENT
    };
    BreakNetMessageView view = {77u, 1u, 9u, &payload, sizeof(payload)};

    break_net_message_registry_init(&registry);
    ASSERT_TRUE(break_net_message_registry_register(&registry, &definition));
    config.registry = &registry;
    g_auth_dispatches = 0u;
    manager = break_session_manager_create(&config);
    ASSERT_NOT_NULL(manager);
    opened.type = BREAK_NET_EVENT_CONNECTION_OPENED;
    opened.connection_key = 0x505u;
    ASSERT_TRUE(break_session_manager_apply_adapter_event(manager, &opened));
    ASSERT_EQ(break_net_message_copy(&first.message, &view), BREAK_NET_MESSAGE_OK);
    ASSERT_EQ(break_net_message_copy(&duplicate.message, &view), BREAK_NET_MESSAGE_OK);
    first.type = duplicate.type = BREAK_NET_EVENT_MESSAGE_RECEIVED;
    first.connection_key = duplicate.connection_key = 0x505u;
    ASSERT_EQ(break_session_manager_apply_adapter_event(manager, &first), false);
    ASSERT_EQ(break_session_manager_last_result(manager), BREAK_SESSION_APPLY_PHASE_REJECTED);
    ASSERT_TRUE(break_session_manager_begin_auth(manager, 0x505u));
    ASSERT_TRUE(break_session_manager_set_message_handler(manager, 77u,
                                                           break_test_auth_handler,
                                                           NULL));
    ASSERT_TRUE(break_session_manager_apply_adapter_event(manager, &first));
    ASSERT_TRUE(break_session_manager_apply_adapter_event(manager, &duplicate));
    ASSERT_EQ(break_session_manager_last_result(manager), BREAK_SESSION_APPLY_OK);
    ASSERT_EQ(g_auth_dispatches, 1u);
    break_net_event_release(&first);
    break_net_event_release(&duplicate);
    break_session_manager_destroy(manager);
}

TEST(break_session_default_registry_allows_auth_in_new_and_ping_pre_auth)
{
    BreakSessionConfig config = {0};
    BreakSessionManager *manager = break_session_manager_create(&config);
    BreakNetEvent opened = {0};
    BreakNetEvent auth = {0};
    BreakNetEvent ping = {0};
    const unsigned char payload = 0x06u;
    BreakNetMessageView auth_view = {BREAK_NET_MESSAGE_ID_AUTH, 1u, 1u,
                                     &payload, sizeof(payload)};
    BreakNetMessageView ping_view = {BREAK_NET_MESSAGE_ID_PING, 1u, 2u,
                                     &payload, sizeof(payload)};

    ASSERT_NOT_NULL(manager);
    opened.type = BREAK_NET_EVENT_CONNECTION_OPENED;
    opened.connection_key = 0x606u;
    ASSERT_TRUE(break_session_manager_apply_adapter_event(manager, &opened));
    ASSERT_EQ(break_session_manager_state(manager, 0x606u), BREAK_SESSION_NEW);
    ASSERT_EQ(break_net_message_copy(&auth.message, &auth_view), BREAK_NET_MESSAGE_OK);
    auth.type = BREAK_NET_EVENT_MESSAGE_RECEIVED;
    auth.connection_key = 0x606u;
    ASSERT_TRUE(break_session_manager_set_message_handler(
        manager, BREAK_NET_MESSAGE_ID_AUTH, break_test_auth_handler, NULL));
    ASSERT_TRUE(break_session_manager_apply_adapter_event(manager, &auth));
    ASSERT_EQ(break_session_manager_state(manager, 0x606u),
              BREAK_SESSION_AUTHENTICATED);
    break_net_event_release(&auth);

    opened.connection_key = 0x607u;
    ASSERT_TRUE(break_session_manager_apply_adapter_event(manager, &opened));
    ASSERT_EQ(break_net_message_copy(&ping.message, &ping_view), BREAK_NET_MESSAGE_OK);
    ping.type = BREAK_NET_EVENT_MESSAGE_RECEIVED;
    ping.connection_key = 0x607u;
    ASSERT_TRUE(break_session_manager_set_message_handler(
        manager, BREAK_NET_MESSAGE_ID_PING, break_test_auth_handler, NULL));
    ASSERT_TRUE(break_session_manager_apply_adapter_event(manager, &ping));
    ASSERT_EQ(break_session_manager_state(manager, 0x607u), BREAK_SESSION_NEW);

    break_net_event_release(&ping);
    break_session_manager_destroy(manager);
}

TEST(break_session_rejects_public_registry_count_out_of_bounds)
{
    BreakNetMessageRegistry registry = {0};
    BreakSessionConfig config = {0};

    registry.count = BREAK_NET_REGISTRY_MAX_MESSAGES + 1u;
    config.registry = &registry;
    ASSERT_EQ(break_session_manager_create(&config), NULL);
}

TEST(break_session_poll_is_low_level_close_finalization)
{
    BreakSessionConfig config = {0};
    BreakNetReactorConfig reactor_config = {BREAK_NET_DRIVE_STEP, 0, 4u, 0, 0u, 0u};
    BreakSessionManager *manager = break_session_manager_create(&config);
    BreakNetReactor *reactor = break_net_reactor_create(&reactor_config);

    ASSERT_NOT_NULL(manager);
    ASSERT_NOT_NULL(reactor);
    ASSERT_TRUE(break_session_manager_attach_reactor(manager, reactor));
    ASSERT_TRUE(break_net_reactor_enqueue_opened_for_test(reactor, 0x608u));
    ASSERT_EQ(break_session_manager_poll(manager, 1u), 0u);
    ASSERT_EQ(break_session_manager_state(manager, 0x608u), BREAK_SESSION_UNKNOWN);
    ASSERT_EQ(break_session_manager_poll_adapter(manager, 1u), 1u);
    ASSERT_EQ(break_session_manager_state(manager, 0x608u), BREAK_SESSION_NEW);

    break_session_manager_destroy(manager);
    break_net_reactor_destroy(reactor);
}

typedef struct BreakSessionWireHandlerState {
    BreakNetReactor *reactor;
    BreakConnectionKey connection;
    uint16_t message_id;
    uint16_t protocol_version;
    uint32_t sequence;
    uint8_t payload[4];
    size_t payload_size;
    size_t calls;
    bool send_ok;
} BreakSessionWireHandlerState;

static bool break_session_wire_auth_handler(BreakConnectionKey connection,
                                            const BreakNetOwnedMessage *message,
                                            void *user_data)
{
    BreakSessionWireHandlerState *state = (BreakSessionWireHandlerState *)user_data;
    state->connection = connection;
    state->message_id = message->message_id;
    state->protocol_version = message->protocol_version;
    state->sequence = message->sequence;
    state->payload_size = message->size;
    if (message->size <= sizeof(state->payload) && message->size != 0u) {
        memcpy(state->payload, message->data, message->size);
    }
    ++state->calls;
    state->send_ok = break_net_reactor_send(state->reactor, connection,
                                            BREAK_NET_MESSAGE_ID_PING,
                                            BREAK_NET_PROTOCOL_VERSION,
                                            "pong", 4u) == BREAK_NET_SEND_OK;
    return true;
}

static ssize_t break_session_wire_write_all(int fd, const void *data, size_t size)
{
    const uint8_t *bytes = (const uint8_t *)data;
    size_t offset = 0u;
    while (offset < size) {
        ssize_t written = write(fd, bytes + offset, size - offset);
        if (written <= 0) return -1;
        offset += (size_t)written;
    }
    return (ssize_t)offset;
}

static ssize_t break_session_wire_read_all(int fd, void *data, size_t size)
{
    uint8_t *bytes = (uint8_t *)data;
    size_t offset = 0u;
    while (offset < size) {
        struct pollfd descriptor = {fd, POLLIN, 0};
        int ready = poll(&descriptor, 1u, 1000);
        ssize_t received;
        if (ready <= 0) return -1;
        received = read(fd, bytes + offset, size - offset);
        if (received <= 0) return -1;
        offset += (size_t)received;
    }
    return (ssize_t)offset;
}

TEST(break_session_wire_auth_reaches_handler_and_sends_response)
{
    BreakSessionConfig session_config = {0};
    BreakNetReactorConfig reactor_config = {BREAK_NET_DRIVE_THREAD, 0, 4u,
                                             1000, 1000u, 10u};
    BreakSessionWireHandlerState handler_state = {0};
    BreakNetEnvelope auth = break_test_envelope(
        BREAK_NET_PROTOCOL_VERSION, BREAK_NET_MESSAGE_ID_AUTH, 0u, 1u,
        "auth", 4u);
    BreakNetEnvelope response = {0};
    uint8_t auth_wire[BREAK_NET_ENVELOPE_MAX_SIZE];
    uint8_t response_wire[BREAK_NET_ENVELOPE_MAX_SIZE];
    size_t auth_size = 0u;
    int client_fd = -1;
    snow_endpoint_t *endpoint = NULL;
    snow_acceptor_t *acceptor = NULL;
    BreakNetReactor *reactor = break_net_reactor_create(&reactor_config);
    BreakSessionManager *manager = break_session_manager_create(&session_config);
    size_t i;

    ASSERT_NOT_NULL(reactor);
    ASSERT_NOT_NULL(manager);
    ASSERT_EQ(snow_endpoint_create(&endpoint), SNOW_OK);
    ASSERT_EQ(snow_endpoint_set_host(endpoint, "127.0.0.1"), SNOW_OK);
    ASSERT_EQ(snow_endpoint_set_port(endpoint, 0), SNOW_OK);
    ASSERT_EQ(snow_acceptor_create(endpoint, &acceptor), SNOW_OK);
    snow_endpoint_destroy(endpoint);
    endpoint = NULL;
    ASSERT_EQ(snow_acceptor_bind(acceptor, 1), SNOW_OK);
    {
        const snow_endpoint_t *bound = snow_acceptor_endpoint(acceptor);
        struct sockaddr_in address = {0};
        client_fd = socket(AF_INET, SOCK_STREAM, 0);
        ASSERT_TRUE(client_fd >= 0);
        address.sin_family = AF_INET;
        address.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
        address.sin_port = htons((uint16_t)snow_endpoint_port(bound));
        ASSERT_EQ(connect(client_fd, (const struct sockaddr *)&address,
                          sizeof(address)), 0);
    }
    ASSERT_TRUE(break_net_reactor_set_acceptor(reactor, acceptor));
    ASSERT_TRUE(break_session_manager_attach_reactor(manager, reactor));
    handler_state.reactor = reactor;
    ASSERT_TRUE(break_session_manager_set_message_handler(
        manager, BREAK_NET_MESSAGE_ID_AUTH, break_session_wire_auth_handler,
        &handler_state));
    ASSERT_TRUE(break_net_reactor_start(reactor));
    ASSERT_EQ(break_net_envelope_encode(&auth, auth_wire, sizeof(auth_wire),
                                        &auth_size), BREAK_NET_ENVELOPE_OK);
    ASSERT_EQ(break_session_wire_write_all(client_fd, auth_wire, auth_size),
              (ssize_t)auth_size);

    for (i = 0u; i < 100u && handler_state.calls == 0u; ++i) {
        (void)break_session_manager_poll_adapter(manager, 8u);
        usleep(1000u);
    }
    ASSERT_EQ(handler_state.calls, 1u);
    ASSERT_EQ(handler_state.message_id, BREAK_NET_MESSAGE_ID_AUTH);
    ASSERT_EQ(handler_state.protocol_version, BREAK_NET_PROTOCOL_VERSION);
    ASSERT_EQ(handler_state.sequence, 1u);
    ASSERT_EQ(handler_state.payload_size, 4u);
    ASSERT_TRUE(memcmp(handler_state.payload, "auth", 4u) == 0);
    ASSERT_TRUE(handler_state.send_ok);
    ASSERT_EQ(break_session_manager_state(manager, handler_state.connection),
              BREAK_SESSION_AUTHENTICATED);
    ASSERT_EQ(break_session_wire_read_all(client_fd, response_wire,
                                          BREAK_NET_ENVELOPE_HEADER_SIZE),
              (ssize_t)BREAK_NET_ENVELOPE_HEADER_SIZE);
    {
        uint32_t payload_size = (uint32_t)response_wire[14] |
            ((uint32_t)response_wire[15] << 8u) |
            ((uint32_t)response_wire[16] << 16u) |
            ((uint32_t)response_wire[17] << 24u);
        ASSERT_EQ(payload_size, 4u);
        ASSERT_EQ(break_session_wire_read_all(
                      client_fd, response_wire + BREAK_NET_ENVELOPE_HEADER_SIZE,
                      payload_size), (ssize_t)payload_size);
    }
    ASSERT_EQ(break_net_envelope_decode(response_wire,
                                        BREAK_NET_ENVELOPE_HEADER_SIZE + 4u,
                                        &response), BREAK_NET_ENVELOPE_OK);
    ASSERT_EQ(response.message_id, BREAK_NET_MESSAGE_ID_PING);
    ASSERT_EQ(response.protocol_version, BREAK_NET_PROTOCOL_VERSION);
    ASSERT_EQ(response.sequence, 0u);
    ASSERT_EQ(response.payload_size, 4u);
    ASSERT_TRUE(memcmp(response.payload, "pong", 4u) == 0);

    close(client_fd);
    {
        uint64_t deadline = 0u;
        bool saw_closed = false;
        BreakNetEvent stale_message = {0};
        BreakNetMessageView stale_view = {
            BREAK_NET_MESSAGE_ID_PING, BREAK_NET_PROTOCOL_VERSION, 2u,
            "stale", 5u
        };

        deadline = break_session_monotonic_us() + UINT64_C(2000000);
        while (break_session_monotonic_us() < deadline && !saw_closed) {
            (void)break_session_manager_poll_adapter(manager, 8u);
            saw_closed = break_session_manager_state(
                manager, handler_state.connection) == BREAK_SESSION_CLOSED;
            if (!saw_closed) usleep(1000u);
        }
        ASSERT_TRUE(saw_closed);
        stale_message.type = BREAK_NET_EVENT_MESSAGE_RECEIVED;
        stale_message.connection_key = handler_state.connection;
        ASSERT_EQ(break_net_message_copy(&stale_message.message, &stale_view),
                  BREAK_NET_MESSAGE_OK);
        ASSERT_FALSE(break_session_manager_apply_adapter_event(manager,
                                                                &stale_message));
        ASSERT_EQ(break_session_manager_last_result(manager),
                  BREAK_SESSION_APPLY_STALE);
        break_net_event_release(&stale_message);
    }
    ASSERT_TRUE(break_net_reactor_stop(reactor, 1000u));
    break_session_manager_destroy(manager);
    break_net_reactor_destroy(reactor);
    snow_acceptor_destroy(acceptor);
}

TEST_MAIN_BEGIN()
    RUN_TEST(break_envelope_round_trip_preserves_fields);
    RUN_TEST(break_envelope_uses_little_endian_wire_order);
    RUN_TEST(break_envelope_accepts_minimum_zero_and_exact_max_payloads);
    RUN_TEST(break_envelope_rejects_over_limit_unknown_id_and_version);
    RUN_TEST(break_envelope_rejects_malformed_lengths_and_bad_sequence);
    RUN_TEST(break_session_legal_transitions_and_unknown_connection);
    RUN_TEST(break_session_rejects_backward_transition_and_duplicate_auth);
    RUN_TEST(break_session_rejects_stale_event_after_close);
    RUN_TEST(break_session_enforces_capacity_duplicate_bind_and_closed_rebind_policy);
    RUN_TEST(break_session_rejects_session_id_overflow);
    RUN_TEST(break_session_applies_adapter_lifecycle_without_taking_payload_ownership);
    RUN_TEST(break_session_polls_adapter_and_dispatches_auth_phase);
    RUN_TEST(break_session_stale_close_watermark_rejects_queued_message);
    RUN_TEST(break_session_auth_handler_failure_closes_without_authenticating);
    RUN_TEST(break_session_ping_duplicate_is_idempotent_and_observable);
    RUN_TEST(break_session_uses_attached_registry_phase_and_duplicate_policy);
    RUN_TEST(break_session_default_registry_allows_auth_in_new_and_ping_pre_auth);
    RUN_TEST(break_session_rejects_public_registry_count_out_of_bounds);
    RUN_TEST(break_session_poll_is_low_level_close_finalization);
    RUN_TEST(break_session_wire_auth_reaches_handler_and_sends_response);
TEST_MAIN_END()
