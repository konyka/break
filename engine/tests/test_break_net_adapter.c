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

/* Server-side transport close: a queued response still reaches the peer,
 * then the peer sees EOF, the reactor emits CONNECTION_CLOSED, and the
 * identity slot is released. Later sends/closes on the key are rejected. */
TEST(break_net_adapter_server_close_flushes_then_closes_peer)
{
    BreakNetReactorConfig config = break_net_test_config(BREAK_NET_DRIVE_STEP);
    BreakNetReactor *reactor = NULL;
    snow_acceptor_t *acceptor = NULL;
    BreakNetEvent event = {0};
    uint64_t connection_key = 0u;
    uint64_t deadline;
    bool saw_close = false;
    bool saw_eof = false;
    unsigned char payload[] = {0x01u, 0x02u, 0x03u};
    unsigned char wire[BREAK_NET_ENVELOPE_MAX_SIZE];
    size_t have = 0u;
    int fd;

    acceptor = break_net_test_acceptor();
    ASSERT_NOT_NULL(acceptor);
    reactor = break_net_reactor_create(&config);
    ASSERT_NOT_NULL(reactor);
    ASSERT_TRUE(break_net_reactor_set_acceptor(reactor, acceptor));
    ASSERT_TRUE(break_net_reactor_start(reactor));
    fd = break_net_test_connect(acceptor);
    ASSERT_TRUE(fd >= 0);

    deadline = break_net_monotonic_us() + UINT64_C(2000000);
    while (break_net_monotonic_us() < deadline && connection_key == 0u) {
        (void)break_net_reactor_step(reactor, 5);
        while (break_net_reactor_poll_event(reactor, &event) == BREAK_NET_EVENT_OK) {
            if (event.type == BREAK_NET_EVENT_CONNECTION_OPENED) {
                connection_key = event.connection_key;
            }
            break_net_event_release(&event);
        }
    }
    ASSERT_TRUE(connection_key != 0u);

    /* invalid arguments */
    ASSERT_FALSE(break_net_reactor_close(NULL, connection_key));
    ASSERT_FALSE(break_net_reactor_close(reactor, 0u));
    ASSERT_FALSE(break_net_reactor_close(reactor, connection_key ^ 0x5555u));

    /* a response queued BEFORE the close must still be delivered */
    ASSERT_EQ(break_net_reactor_send(reactor, connection_key, BREAK_NET_MESSAGE_ID_PING,
                                     BREAK_NET_PROTOCOL_VERSION, payload, sizeof(payload)),
              BREAK_NET_SEND_OK);
    ASSERT_TRUE(break_net_reactor_close(reactor, connection_key));
    /* idempotent while pending; sends after the close are refused */
    ASSERT_TRUE(break_net_reactor_close(reactor, connection_key));
    ASSERT_EQ(break_net_reactor_send(reactor, connection_key, BREAK_NET_MESSAGE_ID_PING,
                                     BREAK_NET_PROTOCOL_VERSION, payload, sizeof(payload)),
              BREAK_NET_SEND_CLOSED);

    deadline = break_net_monotonic_us() + UINT64_C(3000000);
    while (break_net_monotonic_us() < deadline && (!saw_eof || !saw_close)) {
        struct pollfd pfd = {fd, POLLIN, 0};
        (void)break_net_reactor_step(reactor, 2);
        while (break_net_reactor_poll_event(reactor, &event) == BREAK_NET_EVENT_OK) {
            if (event.connection_key == connection_key &&
                (event.type == BREAK_NET_EVENT_CONNECTION_CLOSED ||
                 event.type == BREAK_NET_EVENT_TRANSPORT_ERROR)) {
                saw_close = true;
            }
            break_net_event_release(&event);
        }
        if (!saw_eof && poll(&pfd, 1, 2) > 0) {
            ssize_t n = read(fd, wire + have, sizeof(wire) - have);
            if (n == 0) {
                saw_eof = true;
            } else if (n > 0) {
                have += (size_t)n;
            } else {
                saw_eof = true; /* RST also counts as the server closing */
            }
        }
    }
    ASSERT_TRUE(saw_eof);
    ASSERT_TRUE(saw_close);
    ASSERT_EQ(have, 18u + sizeof(payload));
    {
        BreakNetEnvelope out = {0};
        ASSERT_EQ(break_net_envelope_decode(wire, have, &out), BREAK_NET_ENVELOPE_OK);
        ASSERT_EQ(out.message_id, BREAK_NET_MESSAGE_ID_PING);
        ASSERT_TRUE(memcmp(out.payload, payload, sizeof(payload)) == 0);
    }
    ASSERT_EQ(break_net_reactor_connection_identity_count_for_test(reactor), 0u);
    ASSERT_FALSE(break_net_reactor_close(reactor, connection_key));

    close(fd);
    ASSERT_TRUE(break_net_reactor_stop(reactor, 1000u));
    break_net_reactor_destroy(reactor);
    snow_acceptor_destroy(acceptor);
}

/* Pumps until OPENED for a new key (returned) or the deadline. */
static uint64_t break_net_test_wait_opened(BreakNetReactor *reactor)
{
    BreakNetEvent event = {0};
    uint64_t key = 0u;
    uint64_t deadline = break_net_monotonic_us() + UINT64_C(2000000);
    while (break_net_monotonic_us() < deadline && key == 0u) {
        (void)break_net_reactor_step(reactor, 5);
        while (break_net_reactor_poll_event(reactor, &event) == BREAK_NET_EVENT_OK) {
            if (event.type == BREAK_NET_EVENT_CONNECTION_OPENED && key == 0u) {
                key = event.connection_key;
            }
            break_net_event_release(&event);
        }
    }
    return key;
}

/* Review finding: a peer that resets while a send is in flight leaves the
 * old identity `closing` with a pending send snow never reports drained. The
 * next connection reuses the snow slot, hence the same key; the stale entry
 * must neither shadow the new connection (sends, server close) nor leak its
 * identity slot. */
TEST(break_net_adapter_reset_with_pending_send_then_reconnect_same_key)
{
    BreakNetReactorConfig config = break_net_test_config(BREAK_NET_DRIVE_STEP);
    BreakNetReactor *reactor = NULL;
    snow_acceptor_t *acceptor = NULL;
    BreakNetEvent event = {0};
    uint64_t key_a, key_b;
    uint64_t deadline;
    bool closed_a = false, saw_eof = false;
    unsigned char payload[] = {0x42u, 0x43u};
    unsigned char wire[64];
    size_t have = 0u;
    int fd_a, fd_b;
    struct linger hard = {1, 0};

    config.max_connections = 1u;
    acceptor = break_net_test_acceptor();
    ASSERT_NOT_NULL(acceptor);
    reactor = break_net_reactor_create(&config);
    ASSERT_NOT_NULL(reactor);
    ASSERT_TRUE(break_net_reactor_set_acceptor(reactor, acceptor));
    ASSERT_TRUE(break_net_reactor_start(reactor));

    fd_a = break_net_test_connect(acceptor);
    ASSERT_TRUE(fd_a >= 0);
    key_a = break_net_test_wait_opened(reactor);
    ASSERT_TRUE(key_a != 0u);
    /* send queued, then the peer resets before the reactor steps again */
    ASSERT_EQ(break_net_reactor_send(reactor, key_a, BREAK_NET_MESSAGE_ID_PING,
                                     BREAK_NET_PROTOCOL_VERSION, payload, sizeof(payload)),
              BREAK_NET_SEND_OK);
    ASSERT_EQ(setsockopt(fd_a, SOL_SOCKET, SO_LINGER, &hard, sizeof(hard)), 0);
    close(fd_a);
    deadline = break_net_monotonic_us() + UINT64_C(2000000);
    while (break_net_monotonic_us() < deadline && !closed_a) {
        (void)break_net_reactor_step(reactor, 5);
        while (break_net_reactor_poll_event(reactor, &event) == BREAK_NET_EVENT_OK) {
            if (event.connection_key == key_a &&
                (event.type == BREAK_NET_EVENT_CONNECTION_CLOSED ||
                 event.type == BREAK_NET_EVENT_TRANSPORT_ERROR)) {
                closed_a = true;
            }
            break_net_event_release(&event);
        }
    }
    ASSERT_TRUE(closed_a);
    /* let snow reap the old connection so its slot (and uid) is reused */
    {
        int i;
        for (i = 0; i < 20; i++) (void)break_net_reactor_step(reactor, 2);
    }

    fd_b = break_net_test_connect(acceptor);
    ASSERT_TRUE(fd_b >= 0);
    key_b = break_net_test_wait_opened(reactor);
    ASSERT_TRUE(key_b != 0u);
    {
        int i;
        for (i = 0; i < 5; i++) (void)break_net_reactor_step(reactor, 2);
    }
    /* exactly one identity: the stale one was retired */
    ASSERT_EQ(break_net_reactor_connection_identity_count_for_test(reactor), 1u);

    /* the new connection is fully usable: a send arrives, then a server
     * close delivers EOF */
    ASSERT_EQ(break_net_reactor_send(reactor, key_b, BREAK_NET_MESSAGE_ID_PING,
                                     BREAK_NET_PROTOCOL_VERSION, payload, sizeof(payload)),
              BREAK_NET_SEND_OK);
    ASSERT_TRUE(break_net_reactor_close(reactor, key_b));
    deadline = break_net_monotonic_us() + UINT64_C(3000000);
    while (break_net_monotonic_us() < deadline && !saw_eof) {
        struct pollfd pfd = {fd_b, POLLIN, 0};
        (void)break_net_reactor_step(reactor, 2);
        while (break_net_reactor_poll_event(reactor, &event) == BREAK_NET_EVENT_OK) {
            break_net_event_release(&event);
        }
        if (poll(&pfd, 1, 2) > 0) {
            ssize_t n = read(fd_b, wire + have, sizeof(wire) - have);
            if (n <= 0) saw_eof = true;
            else have += (size_t)n;
        }
    }
    ASSERT_EQ(have, 18u + sizeof(payload));
    ASSERT_TRUE(saw_eof);

    close(fd_b);
    ASSERT_TRUE(break_net_reactor_stop(reactor, 1000u));
    break_net_reactor_destroy(reactor);
    snow_acceptor_destroy(acceptor);
}

/* THREAD drive mode: the host thread runs the same close path. */
TEST(break_net_adapter_server_close_thread_mode)
{
    BreakNetReactorConfig config = break_net_test_config(BREAK_NET_DRIVE_THREAD);
    BreakNetReactor *reactor = NULL;
    snow_acceptor_t *acceptor = NULL;
    BreakNetEvent event = {0};
    uint64_t key = 0u;
    uint64_t deadline;
    bool saw_close = false, saw_eof = false;
    unsigned char payload[] = {0x11u, 0x22u, 0x33u, 0x44u};
    unsigned char wire[64];
    size_t have = 0u;
    int fd;

    acceptor = break_net_test_acceptor();
    ASSERT_NOT_NULL(acceptor);
    reactor = break_net_reactor_create(&config);
    ASSERT_NOT_NULL(reactor);
    ASSERT_TRUE(break_net_reactor_set_acceptor(reactor, acceptor));
    ASSERT_TRUE(break_net_reactor_start(reactor));
    fd = break_net_test_connect(acceptor);
    ASSERT_TRUE(fd >= 0);
    deadline = break_net_monotonic_us() + UINT64_C(2000000);
    while (break_net_monotonic_us() < deadline && key == 0u) {
        if (break_net_reactor_poll_event(reactor, &event) == BREAK_NET_EVENT_OK) {
            if (event.type == BREAK_NET_EVENT_CONNECTION_OPENED) key = event.connection_key;
            break_net_event_release(&event);
        } else {
            usleep(1000u);
        }
    }
    ASSERT_TRUE(key != 0u);
    ASSERT_EQ(break_net_reactor_send(reactor, key, BREAK_NET_MESSAGE_ID_PING,
                                     BREAK_NET_PROTOCOL_VERSION, payload, sizeof(payload)),
              BREAK_NET_SEND_OK);
    ASSERT_TRUE(break_net_reactor_close(reactor, key));
    deadline = break_net_monotonic_us() + UINT64_C(3000000);
    while (break_net_monotonic_us() < deadline && (!saw_eof || !saw_close)) {
        struct pollfd pfd = {fd, POLLIN, 0};
        while (break_net_reactor_poll_event(reactor, &event) == BREAK_NET_EVENT_OK) {
            if (event.connection_key == key &&
                (event.type == BREAK_NET_EVENT_CONNECTION_CLOSED ||
                 event.type == BREAK_NET_EVENT_TRANSPORT_ERROR)) {
                saw_close = true;
            }
            break_net_event_release(&event);
        }
        if (!saw_eof && poll(&pfd, 1, 5) > 0) {
            ssize_t n = read(fd, wire + have, sizeof(wire) - have);
            if (n <= 0) saw_eof = true;
            else have += (size_t)n;
        }
    }
    ASSERT_TRUE(saw_eof);
    ASSERT_TRUE(saw_close);
    ASSERT_EQ(have, 18u + sizeof(payload));
    /* the host thread releases the identity on its own schedule (the
     * CLOSED event is pushed before the release); wait for it */
    deadline = break_net_monotonic_us() + UINT64_C(2000000);
    while (break_net_monotonic_us() < deadline &&
           break_net_reactor_connection_identity_count_for_test(reactor) != 0u) {
        usleep(1000u);
    }
    ASSERT_EQ(break_net_reactor_connection_identity_count_for_test(reactor), 0u);
    close(fd);
    ASSERT_TRUE(break_net_reactor_stop(reactor, 1000u));
    break_net_reactor_destroy(reactor);
    snow_acceptor_destroy(acceptor);
}

/* A close on one connection never disturbs another. */
TEST(break_net_adapter_server_close_is_per_connection)
{
    BreakNetReactorConfig config = break_net_test_config(BREAK_NET_DRIVE_STEP);
    BreakNetReactor *reactor = NULL;
    snow_acceptor_t *acceptor = NULL;
    BreakNetEvent event = {0};
    uint64_t keys[2] = {0u, 0u};
    unsigned key_count = 0u;
    uint64_t deadline;
    bool closed_a = false, closed_b = false, eof_a = false;
    unsigned char payload[] = {0x7au};
    unsigned char wire[64];
    size_t have_b = 0u;
    int fds[2];

    acceptor = break_net_test_acceptor();
    ASSERT_NOT_NULL(acceptor);
    reactor = break_net_reactor_create(&config);
    ASSERT_NOT_NULL(reactor);
    ASSERT_TRUE(break_net_reactor_set_acceptor(reactor, acceptor));
    ASSERT_TRUE(break_net_reactor_start(reactor));
    fds[0] = break_net_test_connect(acceptor);
    ASSERT_TRUE(fds[0] >= 0);
    deadline = break_net_monotonic_us() + UINT64_C(2000000);
    while (break_net_monotonic_us() < deadline && key_count < 1u) {
        (void)break_net_reactor_step(reactor, 5);
        while (break_net_reactor_poll_event(reactor, &event) == BREAK_NET_EVENT_OK) {
            if (event.type == BREAK_NET_EVENT_CONNECTION_OPENED && key_count < 2u) {
                keys[key_count++] = event.connection_key;
            }
            break_net_event_release(&event);
        }
    }
    fds[1] = break_net_test_connect(acceptor);
    ASSERT_TRUE(fds[1] >= 0);
    while (break_net_monotonic_us() < deadline && key_count < 2u) {
        (void)break_net_reactor_step(reactor, 5);
        while (break_net_reactor_poll_event(reactor, &event) == BREAK_NET_EVENT_OK) {
            if (event.type == BREAK_NET_EVENT_CONNECTION_OPENED && key_count < 2u) {
                keys[key_count++] = event.connection_key;
            }
            break_net_event_release(&event);
        }
    }
    ASSERT_EQ(key_count, 2u);

    ASSERT_TRUE(break_net_reactor_close(reactor, keys[0]));
    ASSERT_EQ(break_net_reactor_send(reactor, keys[1], BREAK_NET_MESSAGE_ID_PING,
                                     BREAK_NET_PROTOCOL_VERSION, payload, sizeof(payload)),
              BREAK_NET_SEND_OK);
    deadline = break_net_monotonic_us() + UINT64_C(3000000);
    while (break_net_monotonic_us() < deadline &&
           (!closed_a || !eof_a || have_b < 18u + sizeof(payload))) {
        struct pollfd pfd[2] = {{fds[0], POLLIN, 0}, {fds[1], POLLIN, 0}};
        (void)break_net_reactor_step(reactor, 2);
        while (break_net_reactor_poll_event(reactor, &event) == BREAK_NET_EVENT_OK) {
            if (event.type == BREAK_NET_EVENT_CONNECTION_CLOSED ||
                event.type == BREAK_NET_EVENT_TRANSPORT_ERROR) {
                if (event.connection_key == keys[0]) closed_a = true;
                if (event.connection_key == keys[1]) closed_b = true;
            }
            break_net_event_release(&event);
        }
        if (poll(pfd, 2, 2) > 0) {
            if (!eof_a && (pfd[0].revents & (POLLIN | POLLHUP | POLLERR)) != 0) {
                unsigned char sink[16];
                if (read(fds[0], sink, sizeof(sink)) <= 0) eof_a = true;
            }
            if ((pfd[1].revents & POLLIN) != 0) {
                ssize_t n = read(fds[1], wire + have_b, sizeof(wire) - have_b);
                if (n > 0) have_b += (size_t)n;
            }
        }
    }
    ASSERT_TRUE(closed_a);
    ASSERT_TRUE(eof_a);
    ASSERT_FALSE(closed_b);
    ASSERT_EQ(have_b, 18u + sizeof(payload));
    ASSERT_EQ(break_net_reactor_connection_identity_count_for_test(reactor), 1u);

    close(fds[0]);
    close(fds[1]);
    ASSERT_TRUE(break_net_reactor_stop(reactor, 1000u));
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
    ASSERT_EQ(outgoing.sequence, 1u);
    ASSERT_EQ(outgoing.payload_size, sizeof(incoming_payload));
    ASSERT_TRUE(memcmp(outgoing.payload, incoming_payload, sizeof(incoming_payload)) == 0);

    ASSERT_EQ(snow_tcp_client_close(client), SNOW_OK);
    ASSERT_TRUE(break_net_reactor_stop(reactor, 1000u));
    snow_tcp_client_destroy(client);
    snow_endpoint_destroy(endpoint);
    break_net_reactor_destroy(reactor);
    snow_acceptor_destroy(acceptor);
}

/* ------------------------------------------------------------------ */
/* Review-round-2 regression scaffolding (outbound ring + FIFO)        */
/* ------------------------------------------------------------------ */

/* STEP-mode accept driver: step until CONNECTION_OPENED or deadline. */
static uint64_t break_net_test_step_until_opened(BreakNetReactor *reactor,
                                                 uint64_t deadline_us)
{
    while (break_net_monotonic_us() < deadline_us) {
        BreakNetEvent event = {0};
        if (!break_net_reactor_step(reactor, 5)) return 0u;
        while (break_net_reactor_poll_event(reactor, &event) == BREAK_NET_EVENT_OK) {
            uint64_t key = event.type == BREAK_NET_EVENT_CONNECTION_OPENED
                               ? event.connection_key
                               : 0u;
            break_net_event_release(&event);
            if (key != 0u) return key;
        }
    }
    return 0u;
}

/* Poll (deadline-bounded) then recv what is readable; 0 on timeout/EOF. */
static size_t break_net_test_recv_available(int fd, unsigned char *buf, size_t cap,
                                            uint64_t deadline_us)
{
    struct pollfd pfd;
    uint64_t now = break_net_monotonic_us();
    int ms;
    int ready;
    ssize_t got;
    if (cap == 0u) return 0u;
    pfd.fd = fd;
    pfd.events = POLLIN;
    pfd.revents = 0;
    ms = now >= deadline_us ? 1 : (int)((deadline_us - now) / UINT64_C(1000));
    if (ms <= 0) ms = 1;
    ready = poll(&pfd, 1, ms);
    if (ready <= 0 || (pfd.revents & (POLLIN | POLLERR | POLLHUP)) == 0) return 0u;
    got = recv(fd, buf, cap, 0);
    return got > 0 ? (size_t)got : 0u;
}

/* Decode as many complete PING frames as the buffer holds; each frame must
 * carry a 4-byte LE payload equal to its 0-based ordinal. */
static size_t break_net_test_scan_ping_frames(const unsigned char *buf,
                                              size_t received, bool *order_ok)
{
    size_t frames = 0u;
    *order_ok = true;
    while ((frames + 1u) * 22u <= received) {
        const unsigned char *frame = buf + frames * 22u;
        BreakNetEnvelope env = {0};
        uint32_t word;
        const unsigned char *env_payload;
        if (break_net_envelope_decode(frame, 22u, &env) != BREAK_NET_ENVELOPE_OK ||
            env.message_id != BREAK_NET_MESSAGE_ID_PING || env.payload_size != 4u) {
            *order_ok = false;
            return frames;
        }
        env_payload = (const unsigned char *)env.payload;
        word = (uint32_t)env_payload[0] | ((uint32_t)env_payload[1] << 8u) |
               ((uint32_t)env_payload[2] << 16u) | ((uint32_t)env_payload[3] << 24u);
        if (word != (uint32_t)frames) *order_ok = false;
        frames++;
    }
    return frames;
}

/* Review N1: a full (256-entry, wrapped) ring must survive head removal
 * without losing the tail command or leaking its payload. */
TEST(break_net_adapter_outbound_full_ring_remove_preserves_tail)
{
    BreakNetReactorConfig config = break_net_test_config(BREAK_NET_DRIVE_STEP);
    BreakNetReactor *reactor = break_net_reactor_create(&config);
    snow_acceptor_t *acceptor = break_net_test_acceptor();
    int client_fd;
    uint64_t key;
    uint64_t deadline;
    unsigned char payload[4] = {0u, 0u, 0u, 0u};
    unsigned char buf[8192];
    size_t received = 0u;
    size_t frames;
    size_t i;
    bool order_ok = false;

    ASSERT_NOT_NULL(reactor);
    ASSERT_NOT_NULL(acceptor);
    client_fd = break_net_test_connect(acceptor);
    ASSERT_TRUE(client_fd >= 0);
    ASSERT_TRUE(break_net_reactor_set_acceptor(reactor, acceptor));
    ASSERT_TRUE(break_net_reactor_start(reactor));
    deadline = break_net_monotonic_us() + UINT64_C(5000000);
    key = break_net_test_step_until_opened(reactor, deadline);
    ASSERT_TRUE(key != 0u);

    /* Advance the ring head off slot 0 (stale-key commands are dropped by the
     * next step's drain), so the full ring below wraps around slot 255->0. */
    for (i = 0u; i < 60u; ++i) {
        ASSERT_EQ(break_net_reactor_send(reactor, UINT64_C(0xEEEE),
                                         BREAK_NET_MESSAGE_ID_PING,
                                         BREAK_NET_PROTOCOL_VERSION, payload,
                                         sizeof(payload)), BREAK_NET_SEND_OK);
    }
    ASSERT_TRUE(break_net_reactor_step(reactor, 5));
    ASSERT_EQ(break_net_reactor_outbound_count(reactor), 0u);

    for (i = 0u; i < BREAK_NET_OUTBOUND_QUEUE_CAPACITY; ++i) {
        payload[0] = (unsigned char)i;
        payload[1] = (unsigned char)(i >> 8u);
        ASSERT_EQ(break_net_reactor_send(reactor, key, BREAK_NET_MESSAGE_ID_PING,
                                         BREAK_NET_PROTOCOL_VERSION, payload,
                                         sizeof(payload)), BREAK_NET_SEND_OK);
    }
    ASSERT_EQ(break_net_reactor_outbound_count(reactor),
              (size_t)BREAK_NET_OUTBOUND_QUEUE_CAPACITY);

    while (received < (size_t)BREAK_NET_OUTBOUND_QUEUE_CAPACITY * 22u &&
           break_net_monotonic_us() < deadline) {
        ASSERT_TRUE(break_net_reactor_step(reactor, 5));
        received += break_net_test_recv_available(client_fd, buf + received,
                                                  sizeof(buf) - received, deadline);
    }
    ASSERT_EQ(received, (size_t)BREAK_NET_OUTBOUND_QUEUE_CAPACITY * 22u);
    frames = break_net_test_scan_ping_frames(buf, received, &order_ok);
    ASSERT_EQ(frames, (size_t)BREAK_NET_OUTBOUND_QUEUE_CAPACITY);
    ASSERT_TRUE(order_ok);

    close(client_fd);
    while (break_net_monotonic_us() < deadline &&
           break_net_reactor_connection_identity_count_for_test(reactor) != 0u) {
        ASSERT_TRUE(break_net_reactor_step(reactor, 5));
    }
    ASSERT_EQ(break_net_reactor_connection_identity_count_for_test(reactor), 0u);
    ASSERT_TRUE(break_net_reactor_stop(reactor, 1000u));
    break_net_reactor_destroy(reactor);
    snow_acceptor_destroy(acceptor);
}

/* Review N1 boundary guard: non-full head drops, wrap-around removal order,
 * and tail removal all preserve the surviving commands byte-for-byte. */
TEST(break_net_adapter_outbound_wrap_and_tail_boundaries)
{
    BreakNetReactorConfig config = break_net_test_config(BREAK_NET_DRIVE_STEP);
    BreakNetReactor *reactor = break_net_reactor_create(&config);
    snow_acceptor_t *acceptor = break_net_test_acceptor();
    int client_fd;
    uint64_t key;
    uint64_t deadline;
    unsigned char payload[4] = {0u, 0u, 0u, 0u};
    unsigned char buf[4096];
    size_t received = 0u;
    size_t frames;
    size_t i;
    bool order_ok = false;

    ASSERT_NOT_NULL(reactor);
    ASSERT_NOT_NULL(acceptor);
    client_fd = break_net_test_connect(acceptor);
    ASSERT_TRUE(client_fd >= 0);
    ASSERT_TRUE(break_net_reactor_set_acceptor(reactor, acceptor));
    ASSERT_TRUE(break_net_reactor_start(reactor));
    deadline = break_net_monotonic_us() + UINT64_C(5000000);
    key = break_net_test_step_until_opened(reactor, deadline);
    ASSERT_TRUE(key != 0u);

    /* 200 stale-key commands dropped one by one at the head (non-full head
     * removal x200), moving the head to slot 200. */
    for (i = 0u; i < 200u; ++i) {
        ASSERT_EQ(break_net_reactor_send(reactor, UINT64_C(0xEEEE),
                                         BREAK_NET_MESSAGE_ID_PING,
                                         BREAK_NET_PROTOCOL_VERSION, payload,
                                         sizeof(payload)), BREAK_NET_SEND_OK);
    }
    ASSERT_TRUE(break_net_reactor_step(reactor, 5));
    ASSERT_EQ(break_net_reactor_outbound_count(reactor), 0u);

    /* 100 good commands occupy slots 200..255,0..43 (wrapped); one trailing
     * stale-key command lands at the tail (slot 44) and is dropped last. */
    for (i = 0u; i < 100u; ++i) {
        payload[0] = (unsigned char)i;
        ASSERT_EQ(break_net_reactor_send(reactor, key, BREAK_NET_MESSAGE_ID_PING,
                                         BREAK_NET_PROTOCOL_VERSION, payload,
                                         sizeof(payload)), BREAK_NET_SEND_OK);
    }
    ASSERT_EQ(break_net_reactor_send(reactor, UINT64_C(0xEEEE),
                                     BREAK_NET_MESSAGE_ID_PING,
                                     BREAK_NET_PROTOCOL_VERSION, payload,
                                     sizeof(payload)), BREAK_NET_SEND_OK);
    ASSERT_EQ(break_net_reactor_outbound_count(reactor), 101u);

    while (received < 100u * 22u && break_net_monotonic_us() < deadline) {
        ASSERT_TRUE(break_net_reactor_step(reactor, 5));
        received += break_net_test_recv_available(client_fd, buf + received,
                                                  sizeof(buf) - received, deadline);
    }
    ASSERT_EQ(received, 100u * 22u);
    frames = break_net_test_scan_ping_frames(buf, received, &order_ok);
    ASSERT_EQ(frames, 100u);
    ASSERT_TRUE(order_ok);
    while (break_net_monotonic_us() < deadline &&
           break_net_reactor_outbound_count(reactor) != 0u) {
        ASSERT_TRUE(break_net_reactor_step(reactor, 5));
    }
    ASSERT_EQ(break_net_reactor_outbound_count(reactor), 0u);

    close(client_fd);
    ASSERT_TRUE(break_net_reactor_stop(reactor, 1000u));
    break_net_reactor_destroy(reactor);
    snow_acceptor_destroy(acceptor);
}

/* Review N2: a permanently failing command (unregistered message id —
 * accepted by the public send, rejected by envelope encode in the drain)
 * must block only its own connection's FIFO; another connection still
 * sends. */
TEST(break_net_adapter_outbound_failed_command_blocks_same_key_only)
{
    BreakNetReactorConfig config = break_net_test_config(BREAK_NET_DRIVE_STEP);
    BreakNetReactor *reactor = break_net_reactor_create(&config);
    snow_acceptor_t *acceptor = break_net_test_acceptor();
    int fd_a;
    int fd_b;
    uint64_t key_a;
    uint64_t key_b;
    uint64_t deadline;
    uint64_t silent_until;
    unsigned char poison_payload = 0x11u;
    unsigned char good_a = 0xaau;
    unsigned char good_b = 0xbbu;
    unsigned char buf[64];
    size_t received = 0u;
    bool a_silent = true;
    BreakNetEnvelope env = {0};

    ASSERT_NOT_NULL(reactor);
    ASSERT_NOT_NULL(acceptor);
    fd_a = break_net_test_connect(acceptor);
    ASSERT_TRUE(fd_a >= 0);
    ASSERT_TRUE(break_net_reactor_set_acceptor(reactor, acceptor));
    ASSERT_TRUE(break_net_reactor_start(reactor));
    deadline = break_net_monotonic_us() + UINT64_C(5000000);
    key_a = break_net_test_step_until_opened(reactor, deadline);
    ASSERT_TRUE(key_a != 0u);
    fd_b = break_net_test_connect(acceptor);
    ASSERT_TRUE(fd_b >= 0);
    key_b = break_net_test_step_until_opened(reactor, deadline);
    ASSERT_TRUE(key_b != 0u);
    ASSERT_NEQ(key_a, key_b);

    ASSERT_EQ(break_net_reactor_send(reactor, key_a, 0xbeefu,
                                     BREAK_NET_PROTOCOL_VERSION, &poison_payload,
                                     1u), BREAK_NET_SEND_OK);
    ASSERT_EQ(break_net_reactor_send(reactor, key_a, BREAK_NET_MESSAGE_ID_PING,
                                     BREAK_NET_PROTOCOL_VERSION, &good_a,
                                     1u), BREAK_NET_SEND_OK);
    ASSERT_EQ(break_net_reactor_send(reactor, key_b, BREAK_NET_MESSAGE_ID_PING,
                                     BREAK_NET_PROTOCOL_VERSION, &good_b,
                                     1u), BREAK_NET_SEND_OK);

    /* The other connection's frame must be delivered. */
    while (received < 19u && break_net_monotonic_us() < deadline) {
        ASSERT_TRUE(break_net_reactor_step(reactor, 5));
        received += break_net_test_recv_available(fd_b, buf + received,
                                                  sizeof(buf) - received, deadline);
    }
    ASSERT_EQ(received, 19u);
    ASSERT_EQ(break_net_envelope_decode(buf, received, &env), BREAK_NET_ENVELOPE_OK);
    ASSERT_EQ(env.message_id, BREAK_NET_MESSAGE_ID_PING);
    ASSERT_EQ(env.payload_size, 1u);
    ASSERT_EQ(((const unsigned char *)env.payload)[0], good_b);

    /* The blocked connection must receive nothing: its successor command may
     * not overtake the failed head.  Keep stepping to give an overtaking
     * implementation every chance. */
    silent_until = break_net_monotonic_us() + UINT64_C(500000);
    while (break_net_monotonic_us() < silent_until) {
        ASSERT_TRUE(break_net_reactor_step(reactor, 5));
        if (break_net_test_recv_available(fd_a, buf, sizeof(buf),
                                          break_net_monotonic_us()) != 0u) {
            a_silent = false;
        }
    }
    ASSERT_TRUE(a_silent);
    ASSERT_EQ(break_net_reactor_outbound_count(reactor), 2u);

    /* Closing A drops both retained commands through the stale/closing path. */
    close(fd_a);
    while (break_net_monotonic_us() < deadline &&
           break_net_reactor_outbound_count(reactor) != 0u) {
        ASSERT_TRUE(break_net_reactor_step(reactor, 5));
    }
    ASSERT_EQ(break_net_reactor_outbound_count(reactor), 0u);
    close(fd_b);
    ASSERT_TRUE(break_net_reactor_stop(reactor, 1000u));
    break_net_reactor_destroy(reactor);
    snow_acceptor_destroy(acceptor);
}

TEST(break_net_adapter_outbound_sequences_are_monotonic_per_connection)
{
    BreakNetReactorConfig config = break_net_test_config(BREAK_NET_DRIVE_STEP);
    BreakNetReactor *reactor = break_net_reactor_create(&config);
    snow_acceptor_t *acceptor = break_net_test_acceptor();
    int fd_a;
    int fd_b;
    uint64_t key_a;
    uint64_t key_b;
    uint64_t deadline;
    unsigned char payload[4] = {0u};
    unsigned char wire_a[3u * 22u] = {0u};
    unsigned char wire_b[2u * 22u] = {0u};
    size_t received_a = 0u;
    size_t received_b = 0u;
    size_t i;

    ASSERT_NOT_NULL(reactor);
    ASSERT_NOT_NULL(acceptor);
    fd_a = break_net_test_connect(acceptor);
    ASSERT_TRUE(fd_a >= 0);
    ASSERT_TRUE(break_net_reactor_set_acceptor(reactor, acceptor));
    ASSERT_TRUE(break_net_reactor_start(reactor));
    deadline = break_net_monotonic_us() + UINT64_C(5000000);
    key_a = break_net_test_step_until_opened(reactor, deadline);
    ASSERT_TRUE(key_a != 0u);
    fd_b = break_net_test_connect(acceptor);
    ASSERT_TRUE(fd_b >= 0);
    key_b = break_net_test_step_until_opened(reactor, deadline);
    ASSERT_TRUE(key_b != 0u);
    ASSERT_NEQ(key_a, key_b);

    for (i = 0u; i < 3u; ++i) {
        payload[0] = (unsigned char)i;
        ASSERT_EQ(break_net_reactor_send(reactor, key_a, BREAK_NET_MESSAGE_ID_PING,
                                         BREAK_NET_PROTOCOL_VERSION, payload,
                                         sizeof(payload)), BREAK_NET_SEND_OK);
    }
    for (i = 0u; i < 2u; ++i) {
        payload[0] = (unsigned char)(0x80u + i);
        ASSERT_EQ(break_net_reactor_send(reactor, key_b, BREAK_NET_MESSAGE_ID_PING,
                                         BREAK_NET_PROTOCOL_VERSION, payload,
                                         sizeof(payload)), BREAK_NET_SEND_OK);
    }
    while ((received_a < sizeof(wire_a) || received_b < sizeof(wire_b)) &&
           break_net_monotonic_us() < deadline) {
        ASSERT_TRUE(break_net_reactor_step(reactor, 5));
        if (received_a < sizeof(wire_a)) {
            received_a += break_net_test_recv_available(
                fd_a, wire_a + received_a, sizeof(wire_a) - received_a, deadline);
        }
        if (received_b < sizeof(wire_b)) {
            received_b += break_net_test_recv_available(
                fd_b, wire_b + received_b, sizeof(wire_b) - received_b, deadline);
        }
    }
    ASSERT_EQ(received_a, sizeof(wire_a));
    ASSERT_EQ(received_b, sizeof(wire_b));
    for (i = 0u; i < 3u; ++i) {
        BreakNetEnvelope envelope = {0};
        ASSERT_EQ(break_net_envelope_decode(wire_a + i * 22u, 22u, &envelope),
                  BREAK_NET_ENVELOPE_OK);
        ASSERT_EQ(envelope.sequence, i + 1u);
    }
    for (i = 0u; i < 2u; ++i) {
        BreakNetEnvelope envelope = {0};
        ASSERT_EQ(break_net_envelope_decode(wire_b + i * 22u, 22u, &envelope),
                  BREAK_NET_ENVELOPE_OK);
        ASSERT_EQ(envelope.sequence, i + 1u);
    }

    close(fd_a);
    close(fd_b);
    ASSERT_TRUE(break_net_reactor_stop(reactor, 1000u));
    break_net_reactor_destroy(reactor);
    snow_acceptor_destroy(acceptor);
}

static bool break_net_test_wait_for_connection_count(BreakNetReactor *reactor,
                                                     size_t expected,
                                                     uint64_t deadline_us)
{
    while (break_net_monotonic_us() < deadline_us) {
        if (break_net_reactor_connection_identity_count_for_test(reactor) == expected)
            return true;
        usleep(1000u);
    }
    return false;
}

TEST(break_net_adapter_rate_limit_config_is_created_only)
{
    BreakNetReactorConfig config = break_net_test_config(BREAK_NET_DRIVE_STEP);
    BreakNetReactor *reactor = break_net_reactor_create(&config);
    snow_acceptor_t *acceptor = break_net_test_acceptor();
    BreakNetRateLimitConfig limits = {0};
    limits.global_accept_per_sec = 10u;
    limits.global_burst = 1u;
    ASSERT_NOT_NULL(reactor);
    ASSERT_NOT_NULL(acceptor);
    ASSERT_TRUE(break_net_reactor_set_acceptor(reactor, acceptor));
    ASSERT_TRUE(break_net_reactor_set_rate_limits(reactor, &limits));
    ASSERT_EQ(break_net_reactor_admission_denied(reactor), UINT64_C(0));
    ASSERT_TRUE(break_net_reactor_start(reactor));
    ASSERT_FALSE(break_net_reactor_set_rate_limits(reactor, &limits));
    ASSERT_TRUE(break_net_reactor_stop(reactor, 1000u));
    break_net_reactor_destroy(reactor);
    snow_acceptor_destroy(acceptor);
}

TEST(break_net_adapter_rate_limit_zeros_keep_legacy_behavior)
{
    BreakNetReactorConfig config = break_net_test_config(BREAK_NET_DRIVE_THREAD);
    BreakNetReactor *reactor = break_net_reactor_create(&config);
    snow_acceptor_t *acceptor = break_net_test_acceptor();
    BreakNetRateLimitConfig limits = {0};
    int fds[3] = {-1, -1, -1};
    uint64_t deadline;
    size_t i;
    ASSERT_NOT_NULL(reactor);
    ASSERT_NOT_NULL(acceptor);
    ASSERT_TRUE(break_net_reactor_set_acceptor(reactor, acceptor));
    ASSERT_TRUE(break_net_reactor_set_rate_limits(reactor, &limits));
    ASSERT_TRUE(break_net_reactor_start(reactor));
    deadline = break_net_monotonic_us() + UINT64_C(3000000);
    for (i = 0u; i < 3u; ++i) {
        fds[i] = break_net_test_connect(acceptor);
        ASSERT_TRUE(fds[i] >= 0);
    }
    ASSERT_TRUE(break_net_test_wait_for_connection_count(reactor, 3u, deadline));
    ASSERT_EQ(break_net_reactor_admission_denied(reactor), UINT64_C(0));
    for (i = 0u; i < 3u; ++i) close(fds[i]);
    ASSERT_TRUE(break_net_reactor_stop(reactor, 1000u));
    break_net_reactor_destroy(reactor);
    snow_acceptor_destroy(acceptor);
}

TEST(break_net_adapter_global_burst_then_denies_immediate_accepts)
{
    BreakNetReactorConfig config = break_net_test_config(BREAK_NET_DRIVE_THREAD);
    BreakNetReactor *reactor = break_net_reactor_create(&config);
    snow_acceptor_t *acceptor = break_net_test_acceptor();
    BreakNetRateLimitConfig limits = {0};
    int fd_first = -1;
    int fd_second = -1;
    int fd_later = -1;
    uint64_t deadline;
    uint64_t denied;
    limits.global_accept_per_sec = 1u;
    limits.global_burst = 1u;
    ASSERT_NOT_NULL(reactor);
    ASSERT_NOT_NULL(acceptor);
    ASSERT_TRUE(break_net_reactor_set_acceptor(reactor, acceptor));
    ASSERT_TRUE(break_net_reactor_set_rate_limits(reactor, &limits));
    ASSERT_TRUE(break_net_reactor_start(reactor));
    fd_first = break_net_test_connect(acceptor);
    ASSERT_TRUE(fd_first >= 0);
    deadline = break_net_monotonic_us() + UINT64_C(3000000);
    ASSERT_TRUE(break_net_test_wait_for_connection_count(reactor, 1u, deadline));
    fd_second = break_net_test_connect(acceptor);
    ASSERT_TRUE(fd_second >= 0);
    deadline = break_net_monotonic_us() + UINT64_C(1000000);
    while (break_net_monotonic_us() < deadline &&
           break_net_reactor_admission_denied(reactor) == UINT64_C(0)) {
        usleep(1000u);
    }
    ASSERT_EQ(break_net_reactor_admission_denied(reactor), UINT64_C(1));
    denied = break_net_reactor_admission_denied(reactor);
    usleep(1200000u);
    fd_later = break_net_test_connect(acceptor);
    ASSERT_TRUE(fd_later >= 0);
    deadline = break_net_monotonic_us() + UINT64_C(3000000);
    ASSERT_TRUE(break_net_test_wait_for_connection_count(reactor, 2u, deadline));
    ASSERT_EQ(break_net_reactor_admission_denied(reactor), denied);
    close(fd_first);
    close(fd_second);
    close(fd_later);
    ASSERT_TRUE(break_net_reactor_stop(reactor, 1000u));
    break_net_reactor_destroy(reactor);
    snow_acceptor_destroy(acceptor);
}

TEST(break_net_adapter_per_ip_window_denies_limit_plus_one)
{
    BreakNetReactorConfig config = break_net_test_config(BREAK_NET_DRIVE_THREAD);
    BreakNetReactor *reactor = break_net_reactor_create(&config);
    snow_acceptor_t *acceptor = break_net_test_acceptor();
    BreakNetRateLimitConfig limits = {0};
    int fds[2] = {-1, -1};
    int fd_denied = -1;
    uint64_t deadline;
    limits.per_ip_per_minute = 2u;
    ASSERT_NOT_NULL(reactor);
    ASSERT_NOT_NULL(acceptor);
    ASSERT_TRUE(break_net_reactor_set_acceptor(reactor, acceptor));
    ASSERT_TRUE(break_net_reactor_set_rate_limits(reactor, &limits));
    ASSERT_TRUE(break_net_reactor_start(reactor));
    fds[0] = break_net_test_connect(acceptor);
    fds[1] = break_net_test_connect(acceptor);
    ASSERT_TRUE(fds[0] >= 0);
    ASSERT_TRUE(fds[1] >= 0);
    deadline = break_net_monotonic_us() + UINT64_C(3000000);
    ASSERT_TRUE(break_net_test_wait_for_connection_count(reactor, 2u, deadline));
    fd_denied = break_net_test_connect(acceptor);
    ASSERT_TRUE(fd_denied >= 0);
    deadline = break_net_monotonic_us() + UINT64_C(1000000);
    while (break_net_monotonic_us() < deadline &&
           break_net_reactor_admission_denied(reactor) == UINT64_C(0)) {
        usleep(1000u);
    }
    ASSERT_EQ(break_net_reactor_admission_denied(reactor), UINT64_C(1));
    ASSERT_EQ(break_net_reactor_connection_identity_count_for_test(reactor), 2u);
    close(fds[0]);
    close(fds[1]);
    close(fd_denied);
    ASSERT_TRUE(break_net_reactor_stop(reactor, 1000u));
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
    RUN_TEST(break_net_adapter_server_close_flushes_then_closes_peer);
    RUN_TEST(break_net_adapter_server_close_is_per_connection);
    RUN_TEST(break_net_adapter_server_close_thread_mode);
    RUN_TEST(break_net_adapter_reset_with_pending_send_then_reconnect_same_key);
    RUN_TEST(break_net_adapter_outbound_full_ring_remove_preserves_tail);
    RUN_TEST(break_net_adapter_outbound_wrap_and_tail_boundaries);
    RUN_TEST(break_net_adapter_outbound_failed_command_blocks_same_key_only);
    RUN_TEST(break_net_adapter_outbound_sequences_are_monotonic_per_connection);
    RUN_TEST(break_net_adapter_rate_limit_config_is_created_only);
    RUN_TEST(break_net_adapter_rate_limit_zeros_keep_legacy_behavior);
    RUN_TEST(break_net_adapter_global_burst_then_denies_immediate_accepts);
    RUN_TEST(break_net_adapter_per_ip_window_denies_limit_plus_one);
TEST_MAIN_END()
