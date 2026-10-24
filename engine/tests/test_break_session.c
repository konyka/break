#include "test_framework.h"
#include <network/break_net_adapter.h>
#include <network/break_net_envelope.h>
#include <network/break_net_message_registry.h>
#include <network/break_net_events.h>
#include <network/break_session.h>
#ifdef BREAK_ENABLE_CRYPTO
#include <crypto/break_crypto.h>
#endif

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
    ASSERT_EQ(response.sequence, 1u);
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

TEST(break_session_registry_auth_versions_match_crypto_mode)
{
    const BreakNetMessageRegistry *registry = break_net_message_registry_default();
    const BreakNetMessageDefinition *auth = break_net_message_registry_lookup(
        registry, BREAK_NET_MESSAGE_ID_AUTH);
    const BreakNetMessageDefinition *challenge = break_net_message_registry_lookup(
        registry, BREAK_NET_MESSAGE_ID_CHALLENGE);

    ASSERT_NOT_NULL(auth);
    ASSERT_TRUE(break_net_message_definition_supports_version(auth, 1u));
#ifdef BREAK_ENABLE_CRYPTO
    ASSERT_TRUE(break_net_message_definition_supports_version(auth, 2u));
    ASSERT_NOT_NULL(challenge);
    ASSERT_EQ(challenge->payload_limit, 16u);
    ASSERT_TRUE(break_net_message_definition_supports_version(challenge, 1u));
#else
    ASSERT_FALSE(break_net_message_definition_supports_version(auth, 2u));
    ASSERT_TRUE(challenge == NULL);
#endif
}

#ifdef BREAK_ENABLE_CRYPTO
TEST(break_session_max_age_expires_at_poll)
{
    BreakSessionConfig config = {0};
    BreakSessionManager *manager = break_session_manager_create(&config);
    BreakNetEvent opened = {0};
    BreakNetEvent auth = {0};
    const unsigned char payload = 0x5au;
    BreakNetMessageView view = {BREAK_NET_MESSAGE_ID_AUTH, 1u, 1u,
                                &payload, sizeof(payload)};
    uint64_t deadline;

    ASSERT_NOT_NULL(manager);
    opened.type = BREAK_NET_EVENT_CONNECTION_OPENED;
    opened.connection_key = 0x701u;
    ASSERT_TRUE(break_session_manager_apply_adapter_event(manager, &opened));
    ASSERT_TRUE(break_session_manager_set_message_handler(
        manager, BREAK_NET_MESSAGE_ID_AUTH, break_test_auth_handler, NULL));
    g_handler_result = true;
    auth.type = BREAK_NET_EVENT_MESSAGE_RECEIVED;
    auth.connection_key = 0x701u;
    ASSERT_EQ(break_net_message_copy(&auth.message, &view), BREAK_NET_MESSAGE_OK);
    ASSERT_TRUE(break_session_manager_apply_adapter_event(manager, &auth));
    break_net_event_release(&auth);
    break_session_set_max_age(manager, 1u);
    ASSERT_EQ(break_session_manager_poll(manager, 1u), 0u);
    ASSERT_EQ(break_session_manager_state(manager, 0x701u),
              BREAK_SESSION_AUTHENTICATED);

    deadline = break_session_monotonic_us() + UINT64_C(3000000);
    while (break_session_monotonic_us() < deadline &&
           break_session_manager_state(manager, 0x701u) ==
               BREAK_SESSION_AUTHENTICATED) {
        (void)break_session_manager_poll(manager, 1u);
        usleep(1000u);
    }
    ASSERT_EQ(break_session_manager_state(manager, 0x701u), BREAK_SESSION_CLOSING);
    ASSERT_EQ(break_session_manager_poll(manager, 1u), 1u);
    ASSERT_EQ(break_session_manager_state(manager, 0x701u), BREAK_SESSION_CLOSED);
    break_session_manager_destroy(manager);
}

static const uint8_t break_session_auth_key_id[8] = {
    't', 'e', 's', 't', '-', 'k', '0', '1'
};
static const uint8_t break_session_auth_psk[32] = {
    0x00u, 0x11u, 0x22u, 0x33u, 0x44u, 0x55u, 0x66u, 0x77u,
    0x88u, 0x99u, 0xaau, 0xbbu, 0xccu, 0xddu, 0xeeu, 0xffu,
    0x10u, 0x21u, 0x32u, 0x43u, 0x54u, 0x65u, 0x76u, 0x87u,
    0x98u, 0xa9u, 0xbau, 0xcbu, 0xdcu, 0xedu, 0xfeu, 0x0fu
};

typedef struct BreakSessionAuthKeys {
    bool allow_default;
} BreakSessionAuthKeys;

static bool break_session_auth_key(void *user, const u8 key_id[8], u8 out_psk[32])
{
    BreakSessionAuthKeys *keys = (BreakSessionAuthKeys *)user;
    static const u8 zero_id[8] = {0u};
    if (keys == NULL || key_id == NULL || out_psk == NULL) return false;
    if (memcmp(key_id, break_session_auth_key_id, 8u) != 0 &&
        !(keys->allow_default && memcmp(key_id, zero_id, 8u) == 0)) {
        return false;
    }
    memcpy(out_psk, break_session_auth_psk, 32u);
    return true;
}

typedef struct BreakSessionAuthFixture {
    BreakNetReactor *reactor;
    BreakSessionManager *manager;
    snow_acceptor_t *acceptor;
    int fd;
    uint64_t key;
    uint8_t server_nonce[16];
} BreakSessionAuthFixture;

static snow_acceptor_t *break_session_auth_acceptor(void)
{
    snow_endpoint_t *endpoint = NULL;
    snow_acceptor_t *acceptor = NULL;
    if (snow_endpoint_create(&endpoint) != SNOW_OK ||
        snow_endpoint_set_host(endpoint, "127.0.0.1") != SNOW_OK ||
        snow_endpoint_set_port(endpoint, 0) != SNOW_OK ||
        snow_acceptor_create(endpoint, &acceptor) != SNOW_OK) {
        snow_endpoint_destroy(endpoint);
        return NULL;
    }
    snow_endpoint_destroy(endpoint);
    if (snow_acceptor_bind(acceptor, 1) != SNOW_OK) {
        snow_acceptor_destroy(acceptor);
        return NULL;
    }
    return acceptor;
}

static int break_session_auth_connect(snow_acceptor_t *acceptor)
{
    const snow_endpoint_t *bound = snow_acceptor_endpoint(acceptor);
    struct sockaddr_in address = {0};
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd < 0) return -1;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    address.sin_port = htons((uint16_t)snow_endpoint_port(bound));
    if (connect(fd, (const struct sockaddr *)&address, sizeof(address)) != 0) {
        close(fd);
        return -1;
    }
    return fd;
}

static void break_session_auth_pump(BreakSessionAuthFixture *fixture)
{
    BreakNetEvent event = {0};
    (void)break_net_reactor_step(fixture->reactor, 1);
    while (break_net_reactor_poll_event(fixture->reactor, &event) == BREAK_NET_EVENT_OK) {
        if (event.type == BREAK_NET_EVENT_CONNECTION_OPENED && fixture->key == 0u) {
            fixture->key = event.connection_key;
        }
        (void)break_session_manager_apply_adapter_event(fixture->manager, &event);
        break_net_event_release(&event);
    }
}

static bool break_session_auth_read(BreakSessionAuthFixture *fixture,
                                    uint8_t *wire, size_t size, uint64_t deadline)
{
    size_t received = 0u;
    while (received < size && break_session_monotonic_us() < deadline) {
        struct pollfd descriptor = {fixture->fd, POLLIN, 0};
        break_session_auth_pump(fixture);
        if (poll(&descriptor, 1u, 0) > 0 &&
            (descriptor.revents & (POLLIN | POLLERR | POLLHUP)) != 0) {
            ssize_t chunk = read(fixture->fd, wire + received, size - received);
            if (chunk <= 0) break;
            received += (size_t)chunk;
        }
    }
    return received == size;
}

static void break_session_auth_fixture_close(BreakSessionAuthFixture *fixture)
{
    if (fixture->fd >= 0) {
        close(fixture->fd);
        fixture->fd = -1;
    }
    if (fixture->reactor != NULL && fixture->manager != NULL) {
        uint64_t deadline = break_session_monotonic_us() + UINT64_C(2000000);
        while (break_session_monotonic_us() < deadline &&
               break_net_reactor_connection_identity_count_for_test(
                   fixture->reactor) != 0u) {
            break_session_auth_pump(fixture);
        }
        (void)break_session_manager_poll(fixture->manager, 64u);
    }
    if (fixture->reactor != NULL) {
        (void)break_net_reactor_stop(fixture->reactor, 1000u);
    }
    break_session_manager_destroy(fixture->manager);
    break_net_reactor_destroy(fixture->reactor);
    if (fixture->acceptor != NULL) snow_acceptor_destroy(fixture->acceptor);
    memset(fixture, 0, sizeof(*fixture));
    fixture->fd = -1;
}

static bool break_session_auth_fixture_open(BreakSessionAuthFixture *fixture)
{
    BreakNetReactorConfig reactor_config = {BREAK_NET_DRIVE_STEP, 0, 4u,
                                             1000, 1000u, 1u};
    BreakSessionConfig session_config = {0};
    uint8_t challenge_wire[BREAK_NET_ENVELOPE_HEADER_SIZE + 16u];
    BreakNetEnvelope challenge = {0};
    uint64_t deadline;
    bool ok = false;

    memset(fixture, 0, sizeof(*fixture));
    fixture->fd = -1;
    fixture->acceptor = break_session_auth_acceptor();
    if (fixture->acceptor == NULL) goto cleanup;
    fixture->fd = break_session_auth_connect(fixture->acceptor);
    if (fixture->fd < 0) goto cleanup;
    fixture->reactor = break_net_reactor_create(&reactor_config);
    fixture->manager = break_session_manager_create(&session_config);
    if (fixture->reactor == NULL || fixture->manager == NULL) goto cleanup;
    if (!break_session_manager_attach_reactor(fixture->manager, fixture->reactor) ||
        !break_net_reactor_set_acceptor(fixture->reactor, fixture->acceptor) ||
        !break_net_reactor_start(fixture->reactor)) goto cleanup;
    deadline = break_session_monotonic_us() + UINT64_C(5000000);
    while (fixture->key == 0u && break_session_monotonic_us() < deadline) {
        break_session_auth_pump(fixture);
    }
    if (fixture->key == 0u ||
        !break_session_auth_read(fixture, challenge_wire, sizeof(challenge_wire),
                                 deadline) ||
        break_net_envelope_decode(challenge_wire, sizeof(challenge_wire),
                                  &challenge) != BREAK_NET_ENVELOPE_OK ||
        challenge.message_id != BREAK_NET_MESSAGE_ID_CHALLENGE ||
        challenge.protocol_version != 1u || challenge.sequence != 1u ||
        challenge.payload_size != 16u) goto cleanup;
    memcpy(fixture->server_nonce, challenge.payload, 16u);
    if (break_session_manager_state(fixture->manager, fixture->key) !=
        BREAK_SESSION_NEW) goto cleanup;
    ok = true;
cleanup:
    if (!ok) break_session_auth_fixture_close(fixture);
    return ok;
}

static bool break_session_auth_make_v2(const BreakSessionAuthFixture *fixture,
                                       const uint8_t key_id[8],
                                       const uint8_t client_nonce[16],
                                       uint8_t *wire, size_t *wire_size)
{
    uint8_t payload[56];
    uint8_t context[40];
    BreakNetEnvelope auth;
    memcpy(payload, key_id, 8u);
    memcpy(payload + 8u, client_nonce, 16u);
    memcpy(context, "BRKAUTH2", 8u);
    memcpy(context + 8u, fixture->server_nonce, 16u);
    memcpy(context + 24u, client_nonce, 16u);
    if (!break_crypto_hmac_sha256(break_session_auth_psk, 32u,
                                  context, sizeof(context), payload + 24u)) {
        return false;
    }
    auth = break_test_envelope(2u, BREAK_NET_MESSAGE_ID_AUTH, 0u, 1u,
                               payload, sizeof(payload));
    return break_net_envelope_encode(&auth, wire,
                                     BREAK_NET_ENVELOPE_HEADER_SIZE + sizeof(payload),
                                     wire_size) == BREAK_NET_ENVELOPE_OK;
}

static bool break_session_auth_wait_terminal(BreakSessionAuthFixture *fixture)
{
    uint64_t deadline = break_session_monotonic_us() + UINT64_C(5000000);
    while (break_session_monotonic_us() < deadline) {
        BreakSessionState state = break_session_manager_state(fixture->manager,
                                                               fixture->key);
        if (state == BREAK_SESSION_AUTHENTICATED || state == BREAK_SESSION_CLOSING ||
            state == BREAK_SESSION_CLOSED) return true;
        break_session_auth_pump(fixture);
    }
    return false;
}

TEST(break_session_auth_v2_loopback_authenticates)
{
    BreakSessionAuthKeys keys = {0};
    BreakSessionAuthFixture fixture;
    uint8_t client_nonce[16];
    uint8_t wire[BREAK_NET_ENVELOPE_HEADER_SIZE + 56u];
    size_t wire_size = 0u;
    size_t i;

    ASSERT_TRUE(break_session_set_auth(break_session_auth_key, &keys));
    ASSERT_TRUE(break_session_auth_fixture_open(&fixture));
    for (i = 0u; i < sizeof(client_nonce); ++i) client_nonce[i] = (uint8_t)(i + 1u);
    ASSERT_TRUE(break_session_auth_make_v2(&fixture, break_session_auth_key_id,
                                           client_nonce, wire, &wire_size));
    ASSERT_EQ(wire_size, sizeof(wire));
    ASSERT_EQ(break_session_wire_write_all(fixture.fd, wire, wire_size),
              (ssize_t)wire_size);
    ASSERT_TRUE(break_session_auth_wait_terminal(&fixture));
    ASSERT_EQ(break_session_manager_state(fixture.manager, fixture.key),
              BREAK_SESSION_AUTHENTICATED);
    break_session_auth_fixture_close(&fixture);
    ASSERT_TRUE(break_session_set_auth(NULL, NULL));
}

TEST(break_session_auth_v2_tampered_tag_closes)
{
    BreakSessionAuthKeys keys = {0};
    BreakSessionAuthFixture fixture;
    uint8_t client_nonce[16] = {0x31u};
    uint8_t wire[BREAK_NET_ENVELOPE_HEADER_SIZE + 56u];
    size_t wire_size = 0u;

    ASSERT_TRUE(break_session_set_auth(break_session_auth_key, &keys));
    ASSERT_TRUE(break_session_auth_fixture_open(&fixture));
    ASSERT_TRUE(break_session_auth_make_v2(&fixture, break_session_auth_key_id,
                                           client_nonce, wire, &wire_size));
    wire[BREAK_NET_ENVELOPE_HEADER_SIZE + 24u] ^= 0x80u;
    ASSERT_EQ(break_session_wire_write_all(fixture.fd, wire, wire_size),
              (ssize_t)wire_size);
    ASSERT_TRUE(break_session_auth_wait_terminal(&fixture));
    ASSERT_EQ(break_session_manager_state(fixture.manager, fixture.key),
              BREAK_SESSION_CLOSING);
    ASSERT_EQ(break_session_manager_poll(fixture.manager, 1u), 1u);
    ASSERT_EQ(break_session_manager_state(fixture.manager, fixture.key),
              BREAK_SESSION_CLOSED);
    break_session_auth_fixture_close(&fixture);
    ASSERT_TRUE(break_session_set_auth(NULL, NULL));
}

TEST(break_session_auth_v2_unknown_key_closes)
{
    static const uint8_t unknown_id[8] = {'n', 'o', 's', 'u', 'c', 'h', 'k', 'e'};
    BreakSessionAuthKeys keys = {0};
    BreakSessionAuthFixture fixture;
    uint8_t client_nonce[16] = {0x42u};
    uint8_t wire[BREAK_NET_ENVELOPE_HEADER_SIZE + 56u];
    size_t wire_size = 0u;

    ASSERT_TRUE(break_session_set_auth(break_session_auth_key, &keys));
    ASSERT_TRUE(break_session_auth_fixture_open(&fixture));
    ASSERT_TRUE(break_session_auth_make_v2(&fixture, unknown_id, client_nonce,
                                           wire, &wire_size));
    ASSERT_EQ(break_session_wire_write_all(fixture.fd, wire, wire_size),
              (ssize_t)wire_size);
    ASSERT_TRUE(break_session_auth_wait_terminal(&fixture));
    ASSERT_EQ(break_session_manager_state(fixture.manager, fixture.key),
              BREAK_SESSION_CLOSING);
    break_session_auth_fixture_close(&fixture);
    ASSERT_TRUE(break_session_set_auth(NULL, NULL));
}

TEST(break_session_auth_configured_rejects_v1)
{
    BreakSessionAuthKeys keys = {0};
    BreakSessionAuthFixture fixture;
    BreakNetEnvelope auth = break_test_envelope(1u, BREAK_NET_MESSAGE_ID_AUTH,
                                                0u, 1u, "plain", 5u);
    uint8_t wire[BREAK_NET_ENVELOPE_HEADER_SIZE + 5u];
    size_t wire_size = 0u;

    ASSERT_TRUE(break_session_set_auth(break_session_auth_key, &keys));
    ASSERT_TRUE(break_session_auth_fixture_open(&fixture));
    g_handler_result = true;
    g_auth_dispatches = 0u;
    ASSERT_TRUE(break_session_manager_set_message_handler(
        fixture.manager, BREAK_NET_MESSAGE_ID_AUTH, break_test_auth_handler, NULL));
    ASSERT_EQ(break_net_envelope_encode(&auth, wire, sizeof(wire), &wire_size),
              BREAK_NET_ENVELOPE_OK);
    ASSERT_EQ(break_session_wire_write_all(fixture.fd, wire, wire_size),
              (ssize_t)wire_size);
    ASSERT_TRUE(break_session_auth_wait_terminal(&fixture));
    ASSERT_EQ(break_session_manager_state(fixture.manager, fixture.key),
              BREAK_SESSION_CLOSING);
    ASSERT_EQ(g_auth_dispatches, 0u);
    break_session_auth_fixture_close(&fixture);
    ASSERT_TRUE(break_session_set_auth(NULL, NULL));
}

TEST(break_session_auth_v2_replay_on_new_connection_closes)
{
    BreakSessionAuthKeys keys = {0};
    BreakSessionAuthFixture first;
    BreakSessionAuthFixture second;
    uint8_t client_nonce[16] = {0x73u};
    uint8_t first_nonce[16];
    uint8_t replay[BREAK_NET_ENVELOPE_HEADER_SIZE + 56u];
    size_t replay_size = 0u;

    ASSERT_TRUE(break_session_set_auth(break_session_auth_key, &keys));
    ASSERT_TRUE(break_session_auth_fixture_open(&first));
    ASSERT_TRUE(break_session_auth_make_v2(&first, break_session_auth_key_id,
                                           client_nonce, replay, &replay_size));
    ASSERT_EQ(break_session_wire_write_all(first.fd, replay, replay_size),
              (ssize_t)replay_size);
    ASSERT_TRUE(break_session_auth_wait_terminal(&first));
    ASSERT_EQ(break_session_manager_state(first.manager, first.key),
              BREAK_SESSION_AUTHENTICATED);
    memcpy(first_nonce, first.server_nonce, sizeof(first_nonce));
    break_session_auth_fixture_close(&first);

    ASSERT_TRUE(break_session_auth_fixture_open(&second));
    ASSERT_TRUE(memcmp(first_nonce, second.server_nonce, 16u) != 0);
    ASSERT_EQ(break_session_wire_write_all(second.fd, replay, replay_size),
              (ssize_t)replay_size);
    ASSERT_TRUE(break_session_auth_wait_terminal(&second));
    ASSERT_EQ(break_session_manager_state(second.manager, second.key),
              BREAK_SESSION_CLOSING);
    break_session_auth_fixture_close(&second);
    ASSERT_TRUE(break_session_set_auth(NULL, NULL));
}

TEST(break_session_challenge_client_helper_answers_auth_v2)
{
    BreakSessionAuthKeys keys = {true};
    BreakNetReactorConfig reactor_config = {BREAK_NET_DRIVE_STEP, 0, 4u,
                                             1000, 1000u, 1u};
    BreakSessionConfig session_config = {0};
    BreakNetReactor *reactor = NULL;
    BreakSessionManager *manager = NULL;
    snow_acceptor_t *acceptor = NULL;
    BreakNetOwnedMessage reply = {0};
    uint64_t connection = 0x909u;
    uint64_t outbound_connection = 0u;
    uint8_t server_nonce[16];
    uint8_t zero_id[8] = {0u};
    uint8_t context[40];
    uint8_t expected_tag[32];
    size_t i;

    ASSERT_TRUE(break_session_set_auth(break_session_auth_key, &keys));
    acceptor = break_session_auth_acceptor();
    reactor = break_net_reactor_create(&reactor_config);
    manager = break_session_manager_create(&session_config);
    ASSERT_NOT_NULL(acceptor);
    ASSERT_NOT_NULL(reactor);
    ASSERT_NOT_NULL(manager);
    ASSERT_TRUE(break_session_manager_attach_reactor(manager, reactor));
    ASSERT_TRUE(break_net_reactor_set_acceptor(reactor, acceptor));
    ASSERT_TRUE(break_net_reactor_start(reactor));
    ASSERT_TRUE(break_net_reactor_enqueue_opened_for_test(reactor, connection));
    for (i = 0u; i < sizeof(server_nonce); ++i) server_nonce[i] = (uint8_t)(0xa0u + i);
    ASSERT_TRUE(break_net_reactor_enqueue_message_for_test(
        reactor, connection, BREAK_NET_MESSAGE_ID_CHALLENGE, 1u,
        server_nonce, sizeof(server_nonce)));
    ASSERT_EQ(break_session_manager_poll_adapter(manager, 8u), 2u);
    ASSERT_EQ(break_session_manager_state(manager, connection),
              BREAK_SESSION_AUTHENTICATING);
    ASSERT_EQ(break_net_reactor_poll_outbound_for_test(
                  reactor, &outbound_connection, &reply), BREAK_NET_EVENT_OK);
    ASSERT_EQ(outbound_connection, connection);
    ASSERT_EQ(reply.message_id, BREAK_NET_MESSAGE_ID_AUTH);
    ASSERT_EQ(reply.protocol_version, 2u);
    ASSERT_EQ(reply.size, 56u);
    ASSERT_TRUE(memcmp(reply.data, zero_id, sizeof(zero_id)) == 0);
    memcpy(context, "BRKAUTH2", 8u);
    memcpy(context + 8u, server_nonce, 16u);
    memcpy(context + 24u, (const uint8_t *)reply.data + 8u, 16u);
    ASSERT_TRUE(break_crypto_hmac_sha256(break_session_auth_psk, 32u,
                                         context, sizeof(context), expected_tag));
    ASSERT_TRUE(memcmp((const uint8_t *)reply.data + 24u, expected_tag, 32u) == 0);
    break_net_message_release(&reply);
    ASSERT_TRUE(break_net_reactor_stop(reactor, 1000u));
    break_session_manager_destroy(manager);
    break_net_reactor_destroy(reactor);
    snow_acceptor_destroy(acceptor);
    ASSERT_TRUE(break_session_set_auth(NULL, NULL));
}

TEST(break_session_auth_configuration_is_new_state_only)
{
    BreakSessionAuthKeys keys = {0};
    BreakSessionConfig config = {0};
    BreakSessionManager *manager = break_session_manager_create(&config);

    ASSERT_NOT_NULL(manager);
    ASSERT_TRUE(break_session_manager_bind(manager, 0x910u));
    ASSERT_TRUE(break_session_set_auth(break_session_auth_key, &keys));
    ASSERT_TRUE(break_session_manager_begin_auth(manager, 0x910u));
    ASSERT_FALSE(break_session_set_auth(NULL, NULL));
    ASSERT_TRUE(break_session_manager_close(manager, 0x910u, 0u));
    ASSERT_EQ(break_session_manager_poll(manager, 1u), 1u);
    break_session_manager_destroy(manager);
    ASSERT_TRUE(break_session_set_auth(NULL, NULL));
}

TEST(break_session_max_age_not_deferred_by_close_budget)
{
    BreakSessionConfig config = {0};
    BreakSessionManager *manager = break_session_manager_create(&config);
    BreakNetEvent opened = {0};
    BreakNetEvent auth = {0};
    const unsigned char payload = 0x6bu;
    BreakNetMessageView view = {BREAK_NET_MESSAGE_ID_AUTH, 1u, 1u,
                                &payload, sizeof(payload)};
    uint64_t authenticated_at;
    uint64_t deadline;
    bool aged = false;
    size_t first_closed;
    size_t second_closed;
    BreakSessionState first_state;
    BreakSessionState second_state;
    BreakSessionState second_final_state;

    ASSERT_NOT_NULL(manager);
    opened.type = BREAK_NET_EVENT_CONNECTION_OPENED;
    opened.connection_key = 0x920u;
    ASSERT_TRUE(break_session_manager_apply_adapter_event(manager, &opened));
    opened.connection_key = 0x921u;
    ASSERT_TRUE(break_session_manager_apply_adapter_event(manager, &opened));
    ASSERT_TRUE(break_session_manager_set_message_handler(
        manager, BREAK_NET_MESSAGE_ID_AUTH, break_test_auth_handler, NULL));
    g_handler_result = true;
    auth.type = BREAK_NET_EVENT_MESSAGE_RECEIVED;
    auth.connection_key = 0x921u;
    ASSERT_EQ(break_net_message_copy(&auth.message, &view), BREAK_NET_MESSAGE_OK);
    ASSERT_TRUE(break_session_manager_apply_adapter_event(manager, &auth));
    break_net_event_release(&auth);
    break_session_set_max_age(manager, 1u);
    ASSERT_TRUE(break_session_manager_close(manager, 0x920u, 0u));

    authenticated_at = break_session_monotonic_us();
    deadline = authenticated_at + UINT64_C(3000000);
    while (break_session_monotonic_us() < deadline && !aged) {
        aged = break_session_monotonic_us() - authenticated_at > UINT64_C(1000000);
        if (!aged) usleep(1000u);
    }
    first_closed = break_session_manager_poll(manager, 1u);
    first_state = break_session_manager_state(manager, 0x920u);
    second_state = break_session_manager_state(manager, 0x921u);
    second_closed = break_session_manager_poll(manager, 1u);
    second_final_state = break_session_manager_state(manager, 0x921u);
    break_session_manager_destroy(manager);

    ASSERT_TRUE(aged);
    ASSERT_EQ(first_closed, 1u);
    ASSERT_EQ(first_state, BREAK_SESSION_CLOSED);
    ASSERT_EQ(second_state, BREAK_SESSION_CLOSING);
    ASSERT_EQ(second_closed, 1u);
    ASSERT_EQ(second_final_state, BREAK_SESSION_CLOSED);
}

typedef struct BreakSessionAuthInterleaving {
    BreakNetAuthKeyFn set_fn;
    void *set_user;
    bool called;
    bool setter_result;
} BreakSessionAuthInterleaving;

static void break_session_auth_interleave_setter(void *user)
{
    BreakSessionAuthInterleaving *interleaving = (BreakSessionAuthInterleaving *)user;
    interleaving->called = true;
    interleaving->setter_result = break_session_set_auth(
        interleaving->set_fn, interleaving->set_user);
}

TEST(break_session_auth_set_during_new_v1_snapshot_is_rejected)
{
    BreakSessionAuthKeys keys = {0};
    BreakSessionAuthInterleaving interleaving = {
        break_session_auth_key, &keys, false, false
    };
    BreakSessionConfig config = {0};
    BreakSessionManager *manager = break_session_manager_create(&config);
    BreakNetEvent opened = {0};
    BreakNetEvent auth = {0};
    const unsigned char payload = 0x7cu;
    BreakNetMessageView view = {BREAK_NET_MESSAGE_ID_AUTH, 1u, 1u,
                                &payload, sizeof(payload)};
    bool handled;
    bool cleanup_set;
    BreakSessionState state_after;

    ASSERT_NOT_NULL(manager);
    opened.type = BREAK_NET_EVENT_CONNECTION_OPENED;
    opened.connection_key = 0x930u;
    ASSERT_TRUE(break_session_manager_apply_adapter_event(manager, &opened));
    ASSERT_TRUE(break_session_manager_set_message_handler(
        manager, BREAK_NET_MESSAGE_ID_AUTH, break_test_auth_handler, NULL));
    g_handler_result = true;
    auth.type = BREAK_NET_EVENT_MESSAGE_RECEIVED;
    auth.connection_key = 0x930u;
    ASSERT_EQ(break_net_message_copy(&auth.message, &view), BREAK_NET_MESSAGE_OK);
    break_session_auth_set_test_hook_for_test(
        break_session_auth_interleave_setter, &interleaving);
    handled = break_session_manager_apply_adapter_event(manager, &auth);
    state_after = break_session_manager_state(manager, 0x930u);
    break_net_event_release(&auth);
    break_session_auth_set_test_hook_for_test(NULL, NULL);
    (void)break_session_manager_close(manager, 0x930u, 0u);
    (void)break_session_manager_poll(manager, 1u);
    break_session_manager_destroy(manager);
    cleanup_set = break_session_set_auth(NULL, NULL);

    ASSERT_TRUE(interleaving.called);
    ASSERT_FALSE(interleaving.setter_result);
    ASSERT_TRUE(handled);
    ASSERT_EQ(state_after, BREAK_SESSION_AUTHENTICATED);
    ASSERT_TRUE(cleanup_set);
}

TEST(break_session_auth_clear_during_new_v2_snapshot_is_rejected)
{
    BreakSessionAuthKeys keys = {0};
    BreakSessionAuthInterleaving interleaving = {NULL, NULL, false, false};
    BreakSessionAuthFixture fixture;
    uint8_t client_nonce[16] = {0x8du};
    uint8_t wire[BREAK_NET_ENVELOPE_HEADER_SIZE + 56u];
    size_t wire_size = 0u;
    bool terminated;
    bool cleanup_set;
    BreakSessionState state_after;

    ASSERT_TRUE(break_session_set_auth(break_session_auth_key, &keys));
    ASSERT_TRUE(break_session_auth_fixture_open(&fixture));
    ASSERT_TRUE(break_session_auth_make_v2(&fixture, break_session_auth_key_id,
                                           client_nonce, wire, &wire_size));
    break_session_auth_set_test_hook_for_test(
        break_session_auth_interleave_setter, &interleaving);
    ASSERT_EQ(break_session_wire_write_all(fixture.fd, wire, wire_size),
              (ssize_t)wire_size);
    terminated = break_session_auth_wait_terminal(&fixture);
    state_after = break_session_manager_state(fixture.manager, fixture.key);
    break_session_auth_set_test_hook_for_test(NULL, NULL);
    break_session_auth_fixture_close(&fixture);
    cleanup_set = break_session_set_auth(NULL, NULL);

    ASSERT_TRUE(interleaving.called);
    ASSERT_FALSE(interleaving.setter_result);
    ASSERT_TRUE(terminated);
    ASSERT_EQ(state_after, BREAK_SESSION_AUTHENTICATED);
    ASSERT_TRUE(cleanup_set);
}
#endif

TEST(break_session_public_registry_version_rejection_closes)
{
    BreakSessionConfig config = {0};
    BreakSessionManager *manager = break_session_manager_create(&config);
    BreakNetEvent message = {0};
    unsigned char payload = 0x91u;
    BreakSessionApplyStats stats = {0};
    bool handled;
    BreakSessionState state_after;
    BreakSessionApplyResult result_after;

    ASSERT_NOT_NULL(manager);
    ASSERT_TRUE(break_session_manager_bind(manager, 0x940u));
    message.type = BREAK_NET_EVENT_MESSAGE_RECEIVED;
    message.connection_key = 0x940u;
    message.message.message_id = BREAK_NET_MESSAGE_ID_AUTH;
    message.message.protocol_version = 3u;
    message.message.sequence = 1u;
    message.message.data = &payload;
    message.message.size = 1u;
    handled = break_session_manager_apply_adapter_event(manager, &message);
    state_after = break_session_manager_state(manager, 0x940u);
    result_after = break_session_manager_last_result(manager);
    break_session_manager_apply_stats(manager, &stats);
    break_session_manager_destroy(manager);

    ASSERT_FALSE(handled);
    ASSERT_EQ(state_after, BREAK_SESSION_CLOSING);
    ASSERT_EQ(result_after, BREAK_SESSION_APPLY_INVALID);
    ASSERT_EQ(stats.invalid, 1u);
}

TEST(break_session_public_registry_over_limit_closes_authenticating)
{
    BreakSessionConfig config = {0};
    BreakSessionManager *manager = break_session_manager_create(&config);
    BreakNetEvent message = {0};
    unsigned char payload = 0xa2u;
    BreakSessionApplyStats stats = {0};
    bool handled;
    BreakSessionState state_after;
    BreakSessionApplyResult result_after;

    ASSERT_NOT_NULL(manager);
    ASSERT_TRUE(break_session_manager_bind(manager, 0x950u));
    ASSERT_TRUE(break_session_manager_begin_auth(manager, 0x950u));
    message.type = BREAK_NET_EVENT_MESSAGE_RECEIVED;
    message.connection_key = 0x950u;
    message.message.message_id = BREAK_NET_MESSAGE_ID_AUTH;
    message.message.protocol_version = 1u;
    message.message.sequence = 1u;
    message.message.data = &payload;
    message.message.size = BREAK_NET_MAX_PAYLOAD_SIZE + 1u;
    handled = break_session_manager_apply_adapter_event(manager, &message);
    state_after = break_session_manager_state(manager, 0x950u);
    result_after = break_session_manager_last_result(manager);
    break_session_manager_apply_stats(manager, &stats);
    break_session_manager_destroy(manager);

    ASSERT_FALSE(handled);
    ASSERT_EQ(state_after, BREAK_SESSION_CLOSING);
    ASSERT_EQ(result_after, BREAK_SESSION_APPLY_INVALID);
    ASSERT_EQ(stats.invalid, 1u);
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
    RUN_TEST(break_session_registry_auth_versions_match_crypto_mode);
#ifdef BREAK_ENABLE_CRYPTO
    RUN_TEST(break_session_max_age_expires_at_poll);
    RUN_TEST(break_session_auth_v2_loopback_authenticates);
    RUN_TEST(break_session_auth_v2_tampered_tag_closes);
    RUN_TEST(break_session_auth_v2_unknown_key_closes);
    RUN_TEST(break_session_auth_configured_rejects_v1);
    RUN_TEST(break_session_auth_v2_replay_on_new_connection_closes);
    RUN_TEST(break_session_challenge_client_helper_answers_auth_v2);
    RUN_TEST(break_session_auth_configuration_is_new_state_only);
    RUN_TEST(break_session_max_age_not_deferred_by_close_budget);
    RUN_TEST(break_session_auth_set_during_new_v1_snapshot_is_rejected);
    RUN_TEST(break_session_auth_clear_during_new_v2_snapshot_is_rejected);
#endif
    RUN_TEST(break_session_public_registry_version_rejection_closes);
    RUN_TEST(break_session_public_registry_over_limit_closes_authenticating);
TEST_MAIN_END()
