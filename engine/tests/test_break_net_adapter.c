/* Focused lifecycle tests for the Snowflake-backed Break network adapter. */
#include "test_framework.h"
#include <network/break_net_adapter.h>
#include <network/break_net_envelope.h>
#include <network/break_net_events.h>
#include <network/break_net_message.h>
#include <network/break_net_protocol.h>
#include <snow/acceptor.h>
#include <snow/endpoint.h>
#include <snow/tcp_client.h>
#include <arpa/inet.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <fcntl.h>
#include <poll.h>
#include <sched.h>
#include <sys/socket.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>

extern int clock_gettime(int, struct timespec *);
#ifndef CLOCK_MONOTONIC
#define CLOCK_MONOTONIC 1
#endif
extern int usleep(unsigned int);

static snow_acceptor_t *break_net_test_acceptor(void);
static int break_net_test_connect(snow_acceptor_t *acceptor);

typedef struct BreakNetStepThreadArgs {
    BreakNetReactor *reactor;
    bool result;
} BreakNetStepThreadArgs;

static void *break_net_step_thread_main(void *arg)
{
    BreakNetStepThreadArgs *args = (BreakNetStepThreadArgs *)arg;
    args->result = break_net_reactor_step(args->reactor, 0);
    return NULL;
}

static uint64_t break_net_monotonic_us(void)
{
    struct timespec now;
    clock_gettime(CLOCK_MONOTONIC, &now);
    return (uint64_t)now.tv_sec * UINT64_C(1000000) +
           (uint64_t)now.tv_nsec / UINT64_C(1000);
}

static BreakNetReactorConfig break_net_test_config(BreakNetDriveMode mode)
{
    BreakNetReactorConfig config = {0};
    config.drive_mode = mode;
    config.logical_index = 0;
    config.max_connections = 16u;
    config.empty_connection_timeout_ms = 1000;
    config.watchdog_interval_ms = 1000u;
    config.step_timeout_ms = 10u;
    return config;
}

TEST(break_net_adapter_rejects_null_config)
{
    ASSERT_TRUE(break_net_reactor_create(NULL) == NULL);
}

TEST(break_net_adapter_start_without_acceptor_fails_closed)
{
    BreakNetReactorConfig config = break_net_test_config(BREAK_NET_DRIVE_STEP);
    BreakNetReactor *reactor = break_net_reactor_create(&config);
    unsigned char payload = 1u;
    ASSERT_NOT_NULL(reactor);
    ASSERT_FALSE(break_net_reactor_start(reactor));
    ASSERT_FALSE(break_net_reactor_is_ready(reactor));
    ASSERT_EQ(break_net_reactor_send(reactor, 1u, 12u, 1u, &payload, 1u),
              BREAK_NET_SEND_CLOSED);
    break_net_reactor_destroy(reactor);
}

TEST(break_net_adapter_start_failure_destroys_snow_thread)
{
    static const BreakNetStartFailureForTest failures[] = {
        BREAK_NET_START_FAIL_SETTER,
        BREAK_NET_START_FAIL_REGISTRATION
    };
    size_t i;
    for (i = 0u; i < sizeof(failures) / sizeof(failures[0]); ++i) {
        BreakNetReactorConfig config = break_net_test_config(BREAK_NET_DRIVE_STEP);
        BreakNetReactor *reactor = break_net_reactor_create(&config);
        snow_acceptor_t *acceptor = break_net_test_acceptor();
        ASSERT_NOT_NULL(reactor);
        ASSERT_NOT_NULL(acceptor);
        ASSERT_TRUE(break_net_reactor_set_acceptor(reactor, acceptor));
        ASSERT_FALSE(break_net_reactor_start_failure_for_test(reactor, failures[i]));
        ASSERT_EQ(break_net_reactor_state_for_test(reactor), 5);
        ASSERT_TRUE(break_net_reactor_stop(reactor, 1000u));
        break_net_reactor_destroy(reactor);
        snow_acceptor_destroy(acceptor);
    }
}

TEST(break_net_adapter_thread_loop_exits_after_new_connection_failure)
{
    BreakNetReactorConfig config = break_net_test_config(BREAK_NET_DRIVE_THREAD);
    BreakNetReactor *reactor = break_net_reactor_create(&config);
    snow_acceptor_t *acceptor = break_net_test_acceptor();
    ASSERT_NOT_NULL(reactor);
    ASSERT_NOT_NULL(acceptor);
    ASSERT_TRUE(break_net_reactor_set_acceptor(reactor, acceptor));
    ASSERT_TRUE(break_net_reactor_start(reactor));
    ASSERT_TRUE(break_net_reactor_new_connection_failure_cleanup_for_test(
        reactor, BREAK_NET_NEW_CONNECTION_FAIL_CONTEXT));
    usleep(10000u);
    ASSERT_EQ(break_net_reactor_state_for_test(reactor), 5);
    ASSERT_TRUE(break_net_reactor_stop(reactor, 1000u));
    break_net_reactor_destroy(reactor);
    snow_acceptor_destroy(acceptor);
}

TEST(break_net_adapter_send_rejects_created_and_stopped)
{
    BreakNetReactorConfig config = break_net_test_config(BREAK_NET_DRIVE_STEP);
    BreakNetReactor *reactor = break_net_reactor_create(&config);
    unsigned char payload = 2u;
    ASSERT_NOT_NULL(reactor);
    ASSERT_EQ(break_net_reactor_send(reactor, 1u, 12u, 1u, &payload, 1u),
              BREAK_NET_SEND_CLOSED);
    ASSERT_TRUE(break_net_reactor_stop(reactor, 1000u));
    ASSERT_EQ(break_net_reactor_send(reactor, 1u, 12u, 1u, &payload, 1u),
              BREAK_NET_SEND_CLOSED);
    break_net_reactor_destroy(reactor);
}

TEST(break_net_adapter_rejects_identity_capacity_overflow)
{
    BreakNetReactorConfig config = break_net_test_config(BREAK_NET_DRIVE_STEP);
    config.max_connections = BREAK_NET_CONNECTION_IDENTITY_CAPACITY + 1u;
    ASSERT_TRUE(break_net_reactor_create(&config) == NULL);
}

TEST(break_net_adapter_acceptor_setter_is_created_only)
{
    BreakNetReactorConfig config = break_net_test_config(BREAK_NET_DRIVE_STEP);
    BreakNetReactor *reactor = break_net_reactor_create(&config);
    snow_acceptor_t *acceptor = break_net_test_acceptor();
    ASSERT_NOT_NULL(reactor);
    ASSERT_NOT_NULL(acceptor);
    ASSERT_TRUE(break_net_reactor_set_acceptor(reactor, acceptor));
    ASSERT_TRUE(break_net_reactor_start(reactor));
    ASSERT_FALSE(break_net_reactor_set_acceptor(reactor, acceptor));
    ASSERT_TRUE(break_net_reactor_stop(reactor, 1000u));
    break_net_reactor_destroy(reactor);
    snow_acceptor_destroy(acceptor);
}

static snow_acceptor_t *break_net_test_acceptor(void)
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

static int break_net_test_connect(snow_acceptor_t *acceptor)
{
    const snow_endpoint_t *endpoint = snow_acceptor_endpoint(acceptor);
    struct sockaddr_in address = {0};
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd < 0) return -1;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    address.sin_port = htons((uint16_t)snow_endpoint_port(endpoint));
    if (connect(fd, (const struct sockaddr *)&address, sizeof(address)) != 0) {
        close(fd);
        return -1;
    }
    return fd;
}

TEST(break_net_adapter_step_lifecycle)
{
    BreakNetReactorConfig config = break_net_test_config(BREAK_NET_DRIVE_STEP);
    BreakNetReactor *reactor = break_net_reactor_create(&config);
    snow_acceptor_t *acceptor = break_net_test_acceptor();
    ASSERT_NOT_NULL(reactor);
    ASSERT_TRUE(break_net_reactor_set_acceptor(reactor, acceptor));
    ASSERT_FALSE(break_net_reactor_is_ready(reactor));
    ASSERT_TRUE(break_net_reactor_start(reactor));
    ASSERT_TRUE(break_net_reactor_is_ready(reactor));
    ASSERT_TRUE(break_net_reactor_step(reactor, 0));
    ASSERT_TRUE(break_net_reactor_stop(reactor, 1000u));
    break_net_reactor_destroy(reactor);
    snow_acceptor_destroy(acceptor);
}

TEST(break_net_adapter_rejects_duplicate_start)
{
    BreakNetReactorConfig config =
        break_net_test_config(BREAK_NET_DRIVE_STEP);
    BreakNetReactor *reactor = break_net_reactor_create(&config);
    snow_acceptor_t *acceptor = break_net_test_acceptor();
    ASSERT_NOT_NULL(reactor);
    ASSERT_NOT_NULL(acceptor);
    ASSERT_TRUE(break_net_reactor_set_acceptor(reactor, acceptor));
    ASSERT_TRUE(break_net_reactor_start(reactor));
    ASSERT_FALSE(break_net_reactor_start(reactor));
    ASSERT_TRUE(break_net_reactor_stop(reactor, 1000u));
    break_net_reactor_destroy(reactor);
    snow_acceptor_destroy(acceptor);
}

TEST(break_net_adapter_stop_is_idempotent)
{
    BreakNetReactorConfig config =
        break_net_test_config(BREAK_NET_DRIVE_STEP);
    BreakNetReactor *reactor = break_net_reactor_create(&config);
    snow_acceptor_t *acceptor = break_net_test_acceptor();
    ASSERT_NOT_NULL(reactor);
    ASSERT_NOT_NULL(acceptor);
    ASSERT_TRUE(break_net_reactor_set_acceptor(reactor, acceptor));
    ASSERT_TRUE(break_net_reactor_start(reactor));
    ASSERT_TRUE(break_net_reactor_stop(reactor, 1000u));
    ASSERT_TRUE(break_net_reactor_stop(reactor, 1000u));
    break_net_reactor_destroy(reactor);
    snow_acceptor_destroy(acceptor);
}

TEST(break_net_adapter_thread_lifecycle)
{
    BreakNetReactorConfig config =
        break_net_test_config(BREAK_NET_DRIVE_THREAD);
    BreakNetReactor *reactor = break_net_reactor_create(&config);
    snow_acceptor_t *acceptor = break_net_test_acceptor();

    ASSERT_NOT_NULL(reactor);
    ASSERT_NOT_NULL(acceptor);
    ASSERT_TRUE(break_net_reactor_set_acceptor(reactor, acceptor));
    ASSERT_FALSE(break_net_reactor_is_ready(reactor));
    ASSERT_TRUE(break_net_reactor_start(reactor));
    ASSERT_TRUE(break_net_reactor_is_ready(reactor));
    ASSERT_TRUE(break_net_reactor_stop(reactor, 1000u));
    ASSERT_TRUE(break_net_reactor_stop(reactor, 1000u));
    break_net_reactor_destroy(reactor);
    snow_acceptor_destroy(acceptor);
}

TEST(break_net_adapter_thread_stop_timeout_preserves_reactor)
{
    BreakNetReactorConfig config = break_net_test_config(BREAK_NET_DRIVE_THREAD);
    BreakNetReactor *reactor = break_net_reactor_create(&config);
    snow_acceptor_t *acceptor = break_net_test_acceptor();
    uint64_t started_us;
    uint64_t elapsed_us;
    bool stopped;

    ASSERT_NOT_NULL(reactor);
    ASSERT_NOT_NULL(acceptor);
    ASSERT_TRUE(break_net_reactor_set_acceptor(reactor, acceptor));
    ASSERT_TRUE(break_net_reactor_start(reactor));
    started_us = break_net_monotonic_us();
    stopped = break_net_reactor_stop(reactor, 1u);
    elapsed_us = break_net_monotonic_us() - started_us;
    ASSERT_TRUE(stopped || elapsed_us < 100000u);
    if (!stopped) {
        ASSERT_TRUE(break_net_reactor_stop_pending_for_test(reactor));
        break_net_reactor_destroy(reactor);
        ASSERT_TRUE(break_net_reactor_stop_pending_for_test(reactor));
        ASSERT_TRUE(break_net_reactor_stop(reactor, 5000u));
    }
    break_net_reactor_destroy(reactor);
    snow_acceptor_destroy(acceptor);
}

TEST(break_net_adapter_step_stop_timeout_waits_for_active_step)
{
    BreakNetReactorConfig config = break_net_test_config(BREAK_NET_DRIVE_STEP);
    BreakNetReactor *reactor = break_net_reactor_create(&config);
    snow_acceptor_t *acceptor = break_net_test_acceptor();
    BreakNetStepThreadArgs args = {0};
    pthread_t step_thread;
    uint64_t started_us;
    uint64_t elapsed_us;

    ASSERT_NOT_NULL(reactor);
    ASSERT_NOT_NULL(acceptor);
    ASSERT_TRUE(break_net_reactor_set_acceptor(reactor, acceptor));
    ASSERT_TRUE(break_net_reactor_start(reactor));
    ASSERT_TRUE(break_net_reactor_step_delay_for_test(reactor, 100u));
    args.reactor = reactor;
    ASSERT_EQ(pthread_create(&step_thread, NULL, break_net_step_thread_main, &args), 0);
    usleep(10000u);
    started_us = break_net_monotonic_us();
    ASSERT_FALSE(break_net_reactor_stop(reactor, 1u));
    elapsed_us = break_net_monotonic_us() - started_us;
    ASSERT_TRUE(elapsed_us < 100000u);
    ASSERT_TRUE(break_net_reactor_stop_pending_for_test(reactor));
    ASSERT_EQ(pthread_join(step_thread, NULL), 0);
    ASSERT_TRUE(args.result);
    ASSERT_TRUE(break_net_reactor_stop(reactor, 1000u));
    break_net_reactor_destroy(reactor);
    snow_acceptor_destroy(acceptor);
}

TEST(break_net_adapter_thread_mode_drains_queued_command_before_step)
{
    BreakNetReactorConfig config = break_net_test_config(BREAK_NET_DRIVE_THREAD);
    BreakNetReactor *reactor = break_net_reactor_create(&config);
    snow_acceptor_t *acceptor = break_net_test_acceptor();
    unsigned char payload = 0x5au;
    int client_fd;
    uint64_t connection_key;
    BreakNetEvent event = {0};

    ASSERT_NOT_NULL(reactor);
    ASSERT_NOT_NULL(acceptor);
    client_fd = break_net_test_connect(acceptor);
    ASSERT_TRUE(client_fd >= 0);
    ASSERT_TRUE(break_net_reactor_set_acceptor(reactor, acceptor));
    ASSERT_TRUE(break_net_reactor_start(reactor));
    ASSERT_EQ(break_net_reactor_poll_event(reactor, &event), BREAK_NET_EVENT_OK);
    connection_key = event.connection_key;
    break_net_event_release(&event);
    ASSERT_EQ(break_net_reactor_send(reactor, connection_key, 12u, 1u, &payload, 1u),
              BREAK_NET_SEND_OK);
    while (break_net_reactor_outbound_attempts_for_test(reactor) == 0u) sched_yield();
    ASSERT_TRUE(break_net_reactor_outbound_attempts_for_test(reactor) > 0u);
    ASSERT_TRUE(break_net_reactor_outbound_count(reactor) <= 1u);
    ASSERT_TRUE(break_net_reactor_stop(reactor, 1000u));
    close(client_fd);
    break_net_reactor_destroy(reactor);
    snow_acceptor_destroy(acceptor);
}

TEST(break_net_adapter_malformed_packet_callback_releases_recv_context)
{
    BreakNetReactorConfig config = break_net_test_config(BREAK_NET_DRIVE_STEP);
    BreakNetReactor *reactor = break_net_reactor_create(&config);
    ASSERT_NOT_NULL(reactor);
    ASSERT_TRUE(break_net_reactor_malformed_packet_cleanup_for_test(reactor));
    break_net_reactor_destroy(reactor);
}

TEST(break_net_adapter_close_with_pending_send_defers_recv_context_cleanup)
{
    BreakNetReactorConfig config = break_net_test_config(BREAK_NET_DRIVE_STEP);
    BreakNetReactor *reactor = break_net_reactor_create(&config);
    ASSERT_NOT_NULL(reactor);
    ASSERT_TRUE(break_net_reactor_pending_send_close_contract_for_test(reactor));
    break_net_reactor_destroy(reactor);
}

TEST(break_net_adapter_new_connection_failure_releases_identity_slot)
{
    BreakNetReactorConfig config = break_net_test_config(BREAK_NET_DRIVE_STEP);
    BreakNetReactor *reactor = break_net_reactor_create(&config);
    ASSERT_NOT_NULL(reactor);
    ASSERT_TRUE(break_net_reactor_new_connection_failure_cleanup_for_test(
        reactor, BREAK_NET_NEW_CONNECTION_FAIL_ADDRESS));
    ASSERT_TRUE(break_net_reactor_new_connection_failure_cleanup_for_test(
        reactor, BREAK_NET_NEW_CONNECTION_FAIL_RECV_CONTEXT));
    break_net_reactor_destroy(reactor);
}

TEST(break_net_adapter_event_queue_fifo_and_payload_ownership)
{
    BreakNetReactorConfig config = break_net_test_config(BREAK_NET_DRIVE_STEP);
    BreakNetReactor *reactor = break_net_reactor_create(&config);
    BreakNetEvent event = {0};
    unsigned char payload[] = {4u, 5u, 6u};

    ASSERT_NOT_NULL(reactor);
    ASSERT_TRUE(break_net_reactor_enqueue_opened_for_test(reactor, 7u));
    ASSERT_TRUE(break_net_reactor_enqueue_message_for_test(reactor, 7u, 11u,
                                                            1u, payload,
                                                            sizeof(payload)));
    payload[0] = 99u;
    ASSERT_EQ(break_net_reactor_poll_event(reactor, &event), BREAK_NET_EVENT_OK);
    ASSERT_EQ(event.type, BREAK_NET_EVENT_CONNECTION_OPENED);
    break_net_event_release(&event);
    ASSERT_EQ(break_net_reactor_poll_event(reactor, &event), BREAK_NET_EVENT_OK);
    ASSERT_EQ(event.type, BREAK_NET_EVENT_MESSAGE_RECEIVED);
    ASSERT_EQ(event.connection_key, 7u);
    ASSERT_EQ(event.message.size, sizeof(payload));
    ASSERT_EQ(((const unsigned char *)event.message.data)[0], 4u);
    break_net_event_release(&event);
    break_net_reactor_destroy(reactor);
}

TEST(break_net_adapter_event_queue_full_releases_owned_packet)
{
    BreakNetReactorConfig config = break_net_test_config(BREAK_NET_DRIVE_STEP);
    BreakNetReactor *reactor = break_net_reactor_create(&config);
    unsigned char payload[] = {0xa1u, 0xb2u, 0xc3u};
    BreakNetEvent event = {0};
    size_t i;

    ASSERT_NOT_NULL(reactor);
    for (i = 0u; i < BREAK_NET_EVENT_QUEUE_CAPACITY; ++i)
        ASSERT_TRUE(break_net_reactor_enqueue_opened_for_test(reactor, (uint64_t)i));
    ASSERT_FALSE(break_net_reactor_enqueue_message_for_test(
        reactor, 7u, 11u, 1u, payload, sizeof(payload)));
    ASSERT_EQ(break_net_reactor_poll_event(reactor, &event), BREAK_NET_EVENT_OK);
    ASSERT_EQ(event.type, BREAK_NET_EVENT_CONNECTION_OPENED);
    break_net_event_release(&event);
    ASSERT_EQ(break_net_reactor_poll_event(reactor, &event), BREAK_NET_EVENT_OK);
    break_net_event_release(&event);
    break_net_reactor_destroy(reactor);
}

TEST(break_net_adapter_outbound_drain_drops_stale_uid)
{
    BreakNetReactorConfig config = break_net_test_config(BREAK_NET_DRIVE_STEP);
    BreakNetReactor *reactor = break_net_reactor_create(&config);
    snow_acceptor_t *acceptor = break_net_test_acceptor();
    unsigned char payload = 0x42u;

    ASSERT_NOT_NULL(reactor);
    ASSERT_NOT_NULL(acceptor);
    ASSERT_TRUE(break_net_reactor_set_acceptor(reactor, acceptor));
    ASSERT_TRUE(break_net_reactor_start(reactor));
    ASSERT_EQ(break_net_reactor_send(reactor, 9u, 12u, 1u, &payload, 1u),
              BREAK_NET_SEND_OK);
    ASSERT_TRUE(break_net_reactor_step(reactor, 0));
    ASSERT_EQ(break_net_reactor_outbound_count(reactor), 0u);
    ASSERT_TRUE(break_net_reactor_stop(reactor, 1000u));
    break_net_reactor_destroy(reactor);
    snow_acceptor_destroy(acceptor);
}

TEST(break_net_adapter_outbound_copies_and_bounds_queue)
{
    BreakNetReactorConfig config = break_net_test_config(BREAK_NET_DRIVE_STEP);
    BreakNetReactor *reactor = break_net_reactor_create(&config);
    snow_acceptor_t *acceptor = break_net_test_acceptor();
    unsigned char payload = 8u;
    BreakNetSendResult result;

    ASSERT_NOT_NULL(reactor);
    ASSERT_NOT_NULL(acceptor);
    ASSERT_TRUE(break_net_reactor_set_acceptor(reactor, acceptor));
    ASSERT_TRUE(break_net_reactor_start(reactor));
    result = break_net_reactor_send(reactor, 9u, 12u, 1u, &payload, 1u);
    ASSERT_EQ(result, BREAK_NET_SEND_OK);
    payload = 77u;
    result = break_net_reactor_send(reactor, 9u, 13u, 1u, &payload, 1u);
    ASSERT_EQ(result, BREAK_NET_SEND_OK);
    ASSERT_EQ(break_net_reactor_outbound_count(reactor), 2u);
    ASSERT_TRUE(break_net_reactor_stop(reactor, 1000u));
    break_net_reactor_destroy(reactor);
    snow_acceptor_destroy(acceptor);
}

TEST(break_net_message_copies_payload_lifetime)
{
    unsigned char payload[] = {1u, 2u, 3u, 4u};
    BreakNetMessageView view = {7u, 1u, 9u, payload, sizeof(payload)};
    BreakNetOwnedMessage owned = {0};

    ASSERT_EQ(break_net_message_copy(&owned, &view), BREAK_NET_MESSAGE_OK);
    payload[0] = 99u;
    ASSERT_NOT_NULL(owned.data);
    ASSERT_EQ(owned.size, sizeof(payload));
    ASSERT_EQ(((const unsigned char *)owned.data)[0], 1u);
    ASSERT_EQ(owned.message_id, view.message_id);
    ASSERT_EQ(owned.protocol_version, view.protocol_version);
    ASSERT_EQ(owned.sequence, view.sequence);
    break_net_message_release(&owned);
    ASSERT_TRUE(owned.data == NULL);
    ASSERT_EQ(owned.size, 0u);
}

TEST(break_net_message_accepts_zero_payload)
{
    BreakNetMessageView view = {0};
    BreakNetOwnedMessage owned = {0};

    ASSERT_EQ(break_net_message_view_init(&view, 0u, 1u, 0u, NULL, 0u),
              BREAK_NET_MESSAGE_OK);
    ASSERT_EQ(break_net_message_copy(&owned, &view), BREAK_NET_MESSAGE_OK);
    ASSERT_TRUE(owned.data == NULL);
    ASSERT_EQ(owned.size, 0u);
    break_net_message_release(&owned);
}

TEST(break_net_message_accepts_max_payload)
{
    unsigned char payload[BREAK_NET_MAX_PAYLOAD_SIZE];
    BreakNetMessageView view = {0u, 1u, 0u, payload, sizeof(payload)};
    BreakNetOwnedMessage owned = {0};

    memset(payload, 0x5a, sizeof(payload));
    ASSERT_EQ(break_net_message_copy(&owned, &view), BREAK_NET_MESSAGE_OK);
    ASSERT_EQ(owned.size, sizeof(payload));
    ASSERT_EQ(((const unsigned char *)owned.data)[sizeof(payload) - 1u], 0x5au);
    break_net_message_release(&owned);
}

TEST(break_net_message_rejects_invalid_input)
{
    unsigned char payload = 1u;
    BreakNetMessageView view = {0u, 1u, 0u, &payload, BREAK_NET_MAX_PAYLOAD_SIZE + 1u};
    BreakNetOwnedMessage owned = {0};

    ASSERT_EQ(break_net_message_view_init(NULL, 0u, 1u, 0u, &payload, 1u),
              BREAK_NET_MESSAGE_INVALID);
    ASSERT_EQ(break_net_message_view_init(&view, 0u, 1u, 0u, NULL, 1u),
              BREAK_NET_MESSAGE_INVALID);
    ASSERT_EQ(break_net_message_view_init(&view, 0u, 1u, 0u, &payload,
                                          BREAK_NET_MAX_PAYLOAD_SIZE + 1u),
              BREAK_NET_MESSAGE_OVER_LIMIT);
    ASSERT_EQ(break_net_message_copy(NULL, &view), BREAK_NET_MESSAGE_INVALID);
    ASSERT_EQ(break_net_message_copy(&owned, NULL), BREAK_NET_MESSAGE_INVALID);
    ASSERT_EQ(break_net_message_copy(&owned, &view), BREAK_NET_MESSAGE_OVER_LIMIT);
    view.size = 1u;
    view.data = NULL;
    ASSERT_EQ(break_net_message_copy(&owned, &view), BREAK_NET_MESSAGE_INVALID);
    break_net_message_release(&owned);
}

TEST(break_net_message_release_is_idempotent)
{
    unsigned char payload = 42u;
    BreakNetMessageView view = {0u, 1u, 0u, &payload, 1u};
    BreakNetOwnedMessage owned = {0};

    ASSERT_EQ(break_net_message_copy(&owned, &view), BREAK_NET_MESSAGE_OK);
    break_net_message_release(&owned);
    break_net_message_release(&owned);
    ASSERT_TRUE(owned.data == NULL);
}

typedef struct BreakNetProtocolCase {
    const char *name;
    size_t buffer_size;
    uint16_t version;
    uint16_t message_id;
    uint32_t sequence;
    size_t payload_size;
    BreakNetValidationResult expected;
} BreakNetProtocolCase;

static void break_net_write_u16(unsigned char *buffer, size_t offset,
                                uint16_t value)
{
    buffer[offset] = (unsigned char)(value >> 8u);
    buffer[offset + 1u] = (unsigned char)value;
}

static void break_net_write_u32(unsigned char *buffer, size_t offset,
                                uint32_t value)
{
    buffer[offset] = (unsigned char)(value >> 24u);
    buffer[offset + 1u] = (unsigned char)(value >> 16u);
    buffer[offset + 2u] = (unsigned char)(value >> 8u);
    buffer[offset + 3u] = (unsigned char)value;
}

static size_t break_net_make_envelope(unsigned char *buffer, uint16_t version,
                                      uint16_t message_id, uint32_t sequence,
                                      size_t payload_size)
{
    size_t i;
    break_net_write_u16(buffer, 0u, version);
    break_net_write_u16(buffer, 2u, message_id);
    break_net_write_u32(buffer, 4u, sequence);
    break_net_write_u32(buffer, 8u, (uint32_t)payload_size);
    for (i = 0u; i < payload_size; ++i) {
        buffer[BREAK_NET_PROTOCOL_HEADER_SIZE + i] = 0xa5u;
    }
    return BREAK_NET_PROTOCOL_HEADER_SIZE + payload_size;
}

TEST(break_net_protocol_table_driven_validation)
{
    static const BreakNetProtocolCase cases[] = {
        {"minimum header", BREAK_NET_PROTOCOL_HEADER_SIZE, 1u, 1u, 1u, 0u,
         BREAK_NET_VALIDATION_OK},
        {"zero payload", BREAK_NET_PROTOCOL_HEADER_SIZE, 1u, 2u, 2u, 0u,
         BREAK_NET_VALIDATION_OK},
        {"exact max", BREAK_NET_PROTOCOL_HEADER_SIZE + BREAK_NET_PROTOCOL_MAX_MESSAGE_SIZE,
         1u, 3u, 3u, BREAK_NET_PROTOCOL_MAX_MESSAGE_SIZE, BREAK_NET_VALIDATION_OK},
        {"one byte over", BREAK_NET_PROTOCOL_HEADER_SIZE + BREAK_NET_PROTOCOL_MAX_MESSAGE_SIZE + 1u,
         1u, 4u, 4u, BREAK_NET_PROTOCOL_MAX_MESSAGE_SIZE + 1u,
         BREAK_NET_VALIDATION_OVER_LIMIT},
        {"unsupported version", BREAK_NET_PROTOCOL_HEADER_SIZE, 2u, 5u, 5u, 0u,
         BREAK_NET_VALIDATION_UNSUPPORTED_VERSION},
        {"unknown id", BREAK_NET_PROTOCOL_HEADER_SIZE, 1u, 0u, 6u, 0u,
         BREAK_NET_VALIDATION_UNKNOWN_MESSAGE},
    };
    unsigned char buffer[BREAK_NET_PROTOCOL_HEADER_SIZE + BREAK_NET_PROTOCOL_MAX_MESSAGE_SIZE + 1u];
    size_t i;

    for (i = 0u; i < sizeof(cases) / sizeof(cases[0]); ++i) {
        BreakNetProtocolContext context;
        BreakNetMessageView view = {0};
        size_t actual_size = break_net_make_envelope(
            buffer, cases[i].version, cases[i].message_id, cases[i].sequence,
            cases[i].payload_size);
        break_net_protocol_context_init(&context, 1024u);
        ASSERT_EQ(actual_size, cases[i].buffer_size);
        ASSERT_EQ(break_net_protocol_validate(&context, buffer, actual_size, &view),
                  cases[i].expected);
        if (cases[i].expected != BREAK_NET_VALIDATION_OK) {
            ASSERT_TRUE(view.data == NULL);
            ASSERT_EQ(view.size, 0u);
        }
    }
}

TEST(break_net_protocol_rejects_bad_sequences_without_queue_view)
{
    unsigned char buffer[BREAK_NET_PROTOCOL_HEADER_SIZE];
    BreakNetProtocolContext context;
    BreakNetMessageView view = {0};

    break_net_protocol_context_init(&context, 4u);
    ASSERT_EQ(break_net_protocol_validate(&context, buffer,
                                          break_net_make_envelope(buffer, 1u, 1u, 10u, 0u),
                                          &view), BREAK_NET_VALIDATION_OK);
    ASSERT_EQ(break_net_protocol_validate(&context, buffer,
                                          break_net_make_envelope(buffer, 1u, 1u, 10u, 0u),
                                          &view), BREAK_NET_VALIDATION_INVALID_SEQUENCE);
    ASSERT_TRUE(view.data == NULL);
    ASSERT_EQ(view.size, 0u);
    ASSERT_EQ(break_net_protocol_validate(&context, buffer,
                                          break_net_make_envelope(buffer, 1u, 1u, 9u, 0u),
                                          &view), BREAK_NET_VALIDATION_INVALID_SEQUENCE);
    ASSERT_EQ(break_net_protocol_validate(&context, buffer,
                                          break_net_make_envelope(buffer, 1u, 1u, 15u, 0u),
                                          &view), BREAK_NET_VALIDATION_INVALID_SEQUENCE);
}

TEST(break_net_adapter_loopback_close_emits_event_and_releases_identity)
{
    BreakNetReactorConfig config = break_net_test_config(BREAK_NET_DRIVE_THREAD);
    BreakNetReactor *reactor = NULL;
    snow_acceptor_t *acceptor = NULL;
    snow_endpoint_t *endpoint = NULL;
    snow_tcp_client_t *client = NULL;
    BreakNetEvent event = {0};
    uint64_t connection_key = 0u;
    uint64_t deadline;
    bool saw_close = false;

    acceptor = break_net_test_acceptor();
    ASSERT_NOT_NULL(acceptor);
    ASSERT_EQ(snow_endpoint_create(&endpoint), SNOW_OK);
    ASSERT_EQ(snow_endpoint_set_host(endpoint, "127.0.0.1"), SNOW_OK);
    ASSERT_EQ(snow_endpoint_set_port(endpoint, snow_endpoint_port(
        snow_acceptor_endpoint(acceptor))), SNOW_OK);
    ASSERT_EQ(snow_endpoint_set_timeout(endpoint, 1000), SNOW_OK);
    ASSERT_EQ(snow_tcp_client_create(endpoint, &client), SNOW_OK);
    ASSERT_EQ(snow_tcp_client_connect(client), SNOW_OK);

    reactor = break_net_reactor_create(&config);
    ASSERT_NOT_NULL(reactor);
    ASSERT_TRUE(break_net_reactor_set_acceptor(reactor, acceptor));
    ASSERT_TRUE(break_net_reactor_start(reactor));
    deadline = break_net_monotonic_us() + UINT64_C(2000000);
    while (break_net_monotonic_us() < deadline && connection_key == 0u) {
        if (break_net_reactor_poll_event(reactor, &event) == BREAK_NET_EVENT_OK) {
            if (event.type == BREAK_NET_EVENT_CONNECTION_OPENED) {
                connection_key = event.connection_key;
            }
            break_net_event_release(&event);
        } else {
            usleep(1000u);
        }
    }
    ASSERT_TRUE(connection_key != 0u);
    ASSERT_EQ(break_net_reactor_connection_identity_count_for_test(reactor), 1u);

    ASSERT_EQ(snow_tcp_client_close(client), SNOW_OK);
    deadline = break_net_monotonic_us() + UINT64_C(2000000);
    while (break_net_monotonic_us() < deadline && !saw_close) {
        if (break_net_reactor_poll_event(reactor, &event) == BREAK_NET_EVENT_OK) {
            if (event.connection_key == connection_key &&
                (event.type == BREAK_NET_EVENT_CONNECTION_CLOSED ||
                 event.type == BREAK_NET_EVENT_TRANSPORT_ERROR)) {
                saw_close = true;
            }
            break_net_event_release(&event);
        } else {
            usleep(1000u);
        }
    }
    ASSERT_TRUE(saw_close);
    ASSERT_EQ(break_net_reactor_connection_identity_count_for_test(reactor), 0u);

    ASSERT_TRUE(break_net_reactor_stop(reactor, 1000u));
    snow_tcp_client_destroy(client);
    snow_endpoint_destroy(endpoint);
    break_net_reactor_destroy(reactor);
    snow_acceptor_destroy(acceptor);
}

TEST(break_net_adapter_loopback_wire_round_trip)
{
    BreakNetReactorConfig config = break_net_test_config(BREAK_NET_DRIVE_THREAD);
    BreakNetReactor *reactor = NULL;
    snow_acceptor_t *acceptor = NULL;
    snow_endpoint_t *endpoint = NULL;
    snow_tcp_client_t *client = NULL;
    BreakNetEvent event = {0};
    BreakNetEnvelope incoming = {0};
    BreakNetEnvelope outgoing = {0};
    unsigned char incoming_payload[] = {0xdeu, 0xadu, 0xbeu, 0xefu};
    unsigned char incoming_wire[BREAK_NET_ENVELOPE_MAX_SIZE];
    unsigned char outgoing_wire[BREAK_NET_ENVELOPE_MAX_SIZE];
    size_t incoming_size = 0u;
    size_t received = 0u;
    uint64_t connection_key = 0u;
    int attempts;

    acceptor = break_net_test_acceptor();
    ASSERT_NOT_NULL(acceptor);
    ASSERT_EQ(snow_endpoint_create(&endpoint), SNOW_OK);
    ASSERT_EQ(snow_endpoint_set_host(endpoint, "127.0.0.1"), SNOW_OK);
    ASSERT_EQ(snow_endpoint_set_port(endpoint, snow_endpoint_port(
        snow_acceptor_endpoint(acceptor))), SNOW_OK);
    ASSERT_EQ(snow_endpoint_set_timeout(endpoint, 1000), SNOW_OK);
    ASSERT_EQ(snow_tcp_client_create(endpoint, &client), SNOW_OK);
    ASSERT_EQ(snow_tcp_client_connect(client), SNOW_OK);

    reactor = break_net_reactor_create(&config);
    ASSERT_NOT_NULL(reactor);
    ASSERT_TRUE(break_net_reactor_set_acceptor(reactor, acceptor));
    ASSERT_TRUE(break_net_reactor_start(reactor));

    incoming.protocol_version = BREAK_NET_PROTOCOL_VERSION;
    incoming.message_id = BREAK_NET_MESSAGE_ID_AUTH;
    incoming.sequence = 7u;
    incoming.payload = incoming_payload;
    incoming.payload_size = sizeof(incoming_payload);
    ASSERT_EQ(break_net_envelope_encode(&incoming, incoming_wire, sizeof(incoming_wire),
                                        &incoming_size), BREAK_NET_ENVELOPE_OK);
    ASSERT_EQ(incoming_size, 18u + sizeof(incoming_payload));
    ASSERT_EQ(snow_tcp_client_send(client, incoming_wire, incoming_size), SNOW_OK);

    for (attempts = 0; attempts < 100; ++attempts) {
        if (break_net_reactor_poll_event(reactor, &event) == BREAK_NET_EVENT_OK) {
            if (event.type == BREAK_NET_EVENT_MESSAGE_RECEIVED) break;
            break_net_event_release(&event);
        }
        usleep(10000u);
    }
    ASSERT_EQ(event.type, BREAK_NET_EVENT_MESSAGE_RECEIVED);
    connection_key = event.connection_key;
    ASSERT_EQ(event.message.message_id, BREAK_NET_MESSAGE_ID_AUTH);
    ASSERT_EQ(event.message.protocol_version, BREAK_NET_PROTOCOL_VERSION);
    ASSERT_EQ(event.message.sequence, 7u);
    ASSERT_EQ(event.message.size, sizeof(incoming_payload));
    ASSERT_TRUE(memcmp(event.message.data, incoming_payload, sizeof(incoming_payload)) == 0);
    break_net_event_release(&event);

    ASSERT_EQ(break_net_reactor_send(reactor, connection_key, BREAK_NET_MESSAGE_ID_PING,
                                     BREAK_NET_PROTOCOL_VERSION, incoming_payload,
                                     sizeof(incoming_payload)), BREAK_NET_SEND_OK);
    while (received < 18u + sizeof(incoming_payload)) {
        size_t chunk = sizeof(outgoing_wire) - received;
        ASSERT_EQ(snow_tcp_client_recv(client, outgoing_wire + received, &chunk), SNOW_OK);
        ASSERT_TRUE(chunk != 0u);
        received += chunk;
    }
    ASSERT_EQ(received, 18u + sizeof(incoming_payload));
    ASSERT_EQ(break_net_envelope_decode(outgoing_wire, received, &outgoing),
              BREAK_NET_ENVELOPE_OK);
    ASSERT_EQ(outgoing.message_id, BREAK_NET_MESSAGE_ID_PING);
    ASSERT_EQ(outgoing.protocol_version, BREAK_NET_PROTOCOL_VERSION);
    ASSERT_EQ(outgoing.sequence, 0u);
    ASSERT_EQ(outgoing.payload_size, sizeof(incoming_payload));
    ASSERT_TRUE(memcmp(outgoing.payload, incoming_payload, sizeof(incoming_payload)) == 0);

    ASSERT_EQ(snow_tcp_client_close(client), SNOW_OK);
    ASSERT_TRUE(break_net_reactor_stop(reactor, 1000u));
    snow_tcp_client_destroy(client);
    snow_endpoint_destroy(endpoint);
    break_net_reactor_destroy(reactor);
    snow_acceptor_destroy(acceptor);
}

TEST_MAIN_BEGIN()
    RUN_TEST(break_net_adapter_rejects_null_config);
    RUN_TEST(break_net_adapter_start_without_acceptor_fails_closed);
    RUN_TEST(break_net_adapter_start_failure_destroys_snow_thread);
    RUN_TEST(break_net_adapter_thread_loop_exits_after_new_connection_failure);
    RUN_TEST(break_net_adapter_send_rejects_created_and_stopped);
    RUN_TEST(break_net_adapter_rejects_identity_capacity_overflow);
    RUN_TEST(break_net_adapter_acceptor_setter_is_created_only);
    RUN_TEST(break_net_adapter_step_lifecycle);
    RUN_TEST(break_net_adapter_rejects_duplicate_start);
    RUN_TEST(break_net_adapter_stop_is_idempotent);
    RUN_TEST(break_net_adapter_thread_lifecycle);
    RUN_TEST(break_net_adapter_thread_stop_timeout_preserves_reactor);
    RUN_TEST(break_net_adapter_step_stop_timeout_waits_for_active_step);
    RUN_TEST(break_net_adapter_thread_mode_drains_queued_command_before_step);
    RUN_TEST(break_net_adapter_malformed_packet_callback_releases_recv_context);
    RUN_TEST(break_net_adapter_close_with_pending_send_defers_recv_context_cleanup);
    RUN_TEST(break_net_adapter_new_connection_failure_releases_identity_slot);
    RUN_TEST(break_net_adapter_event_queue_fifo_and_payload_ownership);
    RUN_TEST(break_net_adapter_event_queue_full_releases_owned_packet);
    RUN_TEST(break_net_adapter_outbound_drain_drops_stale_uid);
    RUN_TEST(break_net_adapter_outbound_copies_and_bounds_queue);
    RUN_TEST(break_net_message_copies_payload_lifetime);
    RUN_TEST(break_net_message_accepts_zero_payload);
    RUN_TEST(break_net_message_accepts_max_payload);
    RUN_TEST(break_net_message_rejects_invalid_input);
    RUN_TEST(break_net_message_release_is_idempotent);
    RUN_TEST(break_net_protocol_table_driven_validation);
    RUN_TEST(break_net_protocol_rejects_bad_sequences_without_queue_view);
    RUN_TEST(break_net_adapter_loopback_close_emits_event_and_releases_identity);
    RUN_TEST(break_net_adapter_loopback_wire_round_trip);
TEST_MAIN_END()
