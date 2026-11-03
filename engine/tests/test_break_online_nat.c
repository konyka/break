#include "test_framework.h"
#include <network/break_online_inbox.h>
#include <network/break_online_nat.h>
#include <core/platform_thread.h>
#include <platform/time.h>

#include <stdatomic.h>
#include <stdint.h>
#include <string.h>

typedef struct AuthDirectory {
    u64 sessions[4];
    u64 identities[4];
    usize count;
} AuthDirectory;

static bool directory_auth(void *user, u64 session, BreakOnlineIdentity *out)
{
    AuthDirectory *directory = (AuthDirectory *)user;
    usize i;
    for (i = 0u; i < directory->count; ++i) {
        if (directory->sessions[i] == session) {
            out->session_id = directory->identities[i];
            out->player_id = directory->identities[i];
            return true;
        }
    }
    return false;
}

static u64 fake_clock(void *user)
{
    return *(const u64 *)user;
}

static NetAddress loopback_address(NetSocket *socket)
{
    NetAddress address;
    memset(&address, 0, sizeof(address));
    if (!net_socket_get_local_address(socket, &address)) return address;
    if (strcmp(address.host, "0.0.0.0") == 0) {
        strcpy(address.host, "127.0.0.1");
    }
    return address;
}

TEST(inbox_is_bounded_fifo_and_counts_rejections)
{
    BreakOnlineInbox *inbox = NULL;
    BreakOnlineDatagram datagram;
    BreakOnlineInboxStats stats;
    NetAddress source;
    bool ready = false;
    u8 first = 1u;
    u8 second = 2u;
    u8 third = 3u;
    memset(&source, 0, sizeof(source));
    strcpy(source.host, "127.0.0.1");
    source.port = 9u;
    ASSERT_EQ(break_online_inbox_create(2u, &inbox), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_online_inbox_push(inbox, &source, &first, 1u), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_online_inbox_push(inbox, &source, &second, 1u), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_online_inbox_push(inbox, &source, &third, 1u), BREAK_RUNTIME_OVERLOAD);
    ASSERT_EQ(break_online_inbox_push(inbox, &source, NULL, 0u), BREAK_RUNTIME_INVALID);
    memset(&datagram, 0, sizeof(datagram));
    ASSERT_EQ(break_online_inbox_poll(inbox, &datagram, &ready), BREAK_RUNTIME_OK);
    ASSERT_TRUE(ready);
    ASSERT_EQ(datagram.size, 1u);
    ASSERT_EQ(datagram.bytes[0], 1u);
    ASSERT_EQ(datagram.source.port, 9u);
    ASSERT_EQ(break_online_inbox_poll(inbox, &datagram, &ready), BREAK_RUNTIME_OK);
    ASSERT_EQ(datagram.bytes[0], 2u);
    break_online_inbox_close(inbox);
    ASSERT_EQ(break_online_inbox_push(inbox, &source, &third, 1u), BREAK_RUNTIME_CLOSED);
    ASSERT_EQ(break_online_inbox_poll(inbox, &datagram, &ready), BREAK_RUNTIME_CLOSED);
    ASSERT_EQ(break_online_inbox_stats(inbox, &stats), BREAK_RUNTIME_OK);
    ASSERT_EQ(stats.accepted, 2u);
    ASSERT_EQ(stats.polled, 2u);
    ASSERT_EQ(stats.overload_rejects, 1u);
    ASSERT_EQ(stats.invalid_rejects, 1u);
    ASSERT_EQ(stats.closed_rejects, 1u);
    ASSERT_EQ(stats.high_water, 2u);
    break_online_inbox_destroy(inbox);
}

typedef struct InboxProducer {
    BreakOnlineInbox *inbox;
    NetAddress source;
    u32 start;
    u32 count;
    u32 accepted;
    atomic_bool done;
} InboxProducer;

static PLATFORM_THREAD_RET inbox_produce(PLATFORM_THREAD_ARG arg)
{
    InboxProducer *producer = (InboxProducer *)arg;
    u32 i;
    for (i = 0u; i < producer->count; ++i) {
        u8 value = (u8)(producer->start + i);
        if (break_online_inbox_push(producer->inbox, &producer->source,
                                    &value, 1u) == BREAK_RUNTIME_OK) {
            producer->accepted++;
        }
    }
    atomic_store_explicit(&producer->done, true, memory_order_release);
    return PLATFORM_THREAD_RETURN;
}

TEST(inbox_supports_concurrent_producers_with_owner_consumer)
{
    BreakOnlineInbox *inbox = NULL;
    InboxProducer producers[2];
    PlatformThread threads[2];
    BreakOnlineInboxStats stats;
    u32 received = 0u;
    u32 i;
    u64 deadline;
    ASSERT_EQ(break_online_inbox_create(128u, &inbox), BREAK_RUNTIME_OK);
    memset(producers, 0, sizeof(producers));
    for (i = 0u; i < 2u; ++i) {
        producers[i].inbox = inbox;
        strcpy(producers[i].source.host, "127.0.0.1");
        producers[i].source.port = (u16)(100u + i);
        producers[i].start = (u32)(i * 64u);
        producers[i].count = 64u;
        ASSERT_TRUE(platform_thread_create(&threads[i], inbox_produce, &producers[i]));
    }
    deadline = time_microseconds() + UINT64_C(5000000);
    while (received < 128u && time_microseconds() < deadline) {
        BreakOnlineDatagram datagram;
        bool ready = false;
        BreakRuntimeError result = break_online_inbox_poll(inbox, &datagram, &ready);
        ASSERT_EQ(result, BREAK_RUNTIME_OK);
        if (ready) ++received;
        if (!ready) platform_thread_yield();
    }
    for (i = 0u; i < 2u; ++i) platform_thread_join(threads[i]);
    ASSERT_EQ(received, 128u);
    ASSERT_EQ(producers[0].accepted, 64u);
    ASSERT_EQ(producers[1].accepted, 64u);
    ASSERT_EQ(break_online_inbox_stats(inbox, &stats), BREAK_RUNTIME_OK);
    ASSERT_EQ(stats.polled, 128u);
    ASSERT_EQ(stats.overload_rejects, 0u);
    break_online_inbox_destroy(inbox);
}

typedef struct NatFixture {
    NetSocket *coordinator_socket;
    NetSocket *a_socket;
    NetSocket *b_socket;
    NetSocket *attacker_socket;
    NetAddress coordinator_address;
    NetAddress a_address;
    NetAddress b_address;
    BreakNatCoordinator *coordinator;
    BreakNatEndpoint *a;
    BreakNatEndpoint *b;
    AuthDirectory auth;
    u64 now;
} NatFixture;

static bool nat_fixture_init(NatFixture *fixture, u32 max_peers, u32 max_pairs)
{
    BreakNatCoordinatorConfig coordinator_config;
    BreakNatEndpointConfig endpoint_config;
    memset(fixture, 0, sizeof(*fixture));
    fixture->coordinator_socket = net_udp_create(0);
    fixture->a_socket = net_udp_create(0);
    fixture->b_socket = net_udp_create(0);
    fixture->attacker_socket = net_udp_create(0);
    if (!fixture->coordinator_socket || !fixture->a_socket ||
        !fixture->b_socket || !fixture->attacker_socket) return false;
    net_set_nonblocking(fixture->coordinator_socket, true);
    net_set_nonblocking(fixture->a_socket, true);
    net_set_nonblocking(fixture->b_socket, true);
    net_set_nonblocking(fixture->attacker_socket, true);
    fixture->coordinator_address = loopback_address(fixture->coordinator_socket);
    fixture->a_address = loopback_address(fixture->a_socket);
    fixture->b_address = loopback_address(fixture->b_socket);
    if (!fixture->coordinator_address.port || !fixture->a_address.port ||
        !fixture->b_address.port) return false;
    fixture->auth.sessions[0] = 11u;
    fixture->auth.sessions[1] = 22u;
    fixture->auth.identities[0] = 1011u;
    fixture->auth.identities[1] = 1022u;
    fixture->auth.count = 2u;
    memset(&coordinator_config, 0, sizeof(coordinator_config));
    coordinator_config.max_peers = max_peers;
    coordinator_config.max_pairs = max_pairs;
    coordinator_config.queue_capacity = 32u;
    coordinator_config.auth.user = &fixture->auth;
    coordinator_config.auth.authenticate = directory_auth;
    coordinator_config.clock = fake_clock;
    coordinator_config.clock_user = &fixture->now;
    if (break_nat_coordinator_create(fixture->coordinator_socket,
                                     &coordinator_config,
                                     &fixture->coordinator) != BREAK_RUNTIME_OK) return false;
    memset(&endpoint_config, 0, sizeof(endpoint_config));
    endpoint_config.queue_capacity = 32u;
    endpoint_config.clock = fake_clock;
    endpoint_config.clock_user = &fixture->now;
    endpoint_config.session = 11u;
    if (break_nat_endpoint_create(fixture->a_socket, &fixture->coordinator_address,
                                  &endpoint_config, &fixture->a) != BREAK_RUNTIME_OK) return false;
    endpoint_config.session = 22u;
    if (break_nat_endpoint_create(fixture->b_socket, &fixture->coordinator_address,
                                  &endpoint_config, &fixture->b) != BREAK_RUNTIME_OK) return false;
    return true;
}

static void nat_fixture_dispose(NatFixture *fixture)
{
    break_nat_endpoint_destroy(fixture->a);
    break_nat_endpoint_destroy(fixture->b);
    break_nat_coordinator_destroy(fixture->coordinator);
    net_close(fixture->coordinator_socket);
    net_close(fixture->a_socket);
    net_close(fixture->b_socket);
    net_close(fixture->attacker_socket);
}

static void nat_pump_once(NatFixture *fixture)
{
    (void)break_nat_coordinator_receive_socket(fixture->coordinator, 32u);
    (void)break_nat_endpoint_receive_socket(fixture->a, 32u);
    (void)break_nat_endpoint_receive_socket(fixture->b, 32u);
    (void)break_nat_coordinator_poll(fixture->coordinator, 32u);
    (void)break_nat_endpoint_poll(fixture->a, 32u);
    (void)break_nat_endpoint_poll(fixture->b, 32u);
}

static bool nat_pump_until_registered(NatFixture *fixture)
{
    u64 deadline = time_microseconds() + UINT64_C(5000000);
    while (time_microseconds() < deadline) {
        nat_pump_once(fixture);
        if (break_nat_coordinator_peer_count(fixture->coordinator) == 2u &&
            break_nat_endpoint_registered(fixture->a) &&
            break_nat_endpoint_registered(fixture->b)) return true;
        platform_thread_yield();
    }
    return false;
}

static bool nat_pump_until_connected(NatFixture *fixture, BreakOnlineHandle pair)
{
    u64 deadline = time_microseconds() + UINT64_C(5000000);
    while (time_microseconds() < deadline) {
        u32 ack_mask = 0u;
        nat_pump_once(fixture);
        if (break_nat_endpoint_connected(fixture->a, pair) &&
            break_nat_endpoint_connected(fixture->b, pair) &&
            break_nat_coordinator_pair_ack_mask(fixture->coordinator, pair,
                                                &ack_mask) == BREAK_RUNTIME_OK &&
            ack_mask == 3u) return true;
        platform_thread_yield();
    }
    return false;
}

static bool register_and_pair(NatFixture *fixture, BreakOnlineHandle *out_pair,
                              u64 nonce, u32 ttl_ms)
{
    BreakOnlineHandle a_peer;
    BreakOnlineHandle b_peer;
    if (break_nat_peer_hello(fixture->a) != BREAK_RUNTIME_OK ||
        break_nat_peer_hello(fixture->b) != BREAK_RUNTIME_OK ||
        !nat_pump_until_registered(fixture)) return false;
    if (break_nat_coordinator_peer_for_session(fixture->coordinator, 11u,
                                               &a_peer) != BREAK_RUNTIME_OK ||
        break_nat_coordinator_peer_for_session(fixture->coordinator, 22u,
                                               &b_peer) != BREAK_RUNTIME_OK) return false;
    return break_nat_coordinator_pair(fixture->coordinator, a_peer, b_peer,
                                      nonce, ttl_ms, out_pair) == BREAK_RUNTIME_OK;
}

TEST(nat_real_udp_loopback_registers_punches_and_acknowledges)
{
    NatFixture fixture;
    BreakOnlineHandle pair;
    BreakOnlineHandle a_peer;
    NetAddress observed;
    ASSERT_TRUE(nat_fixture_init(&fixture, 2u, 1u));
    ASSERT_TRUE(register_and_pair(&fixture, &pair, UINT64_C(0x12345678), 1000u));
    ASSERT_TRUE(nat_pump_until_connected(&fixture, pair));
    ASSERT_EQ(break_nat_coordinator_peer_for_session(fixture.coordinator, 11u, &a_peer),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(break_nat_coordinator_peer_observed(fixture.coordinator, a_peer, &observed),
              BREAK_RUNTIME_OK);
    ASSERT_TRUE(net_address_equal(&observed, &fixture.a_address));
    ASSERT_EQ(break_nat_peer_hello(fixture.a), BREAK_RUNTIME_OK);
    nat_pump_once(&fixture);
    ASSERT_EQ(break_nat_coordinator_peer_count(fixture.coordinator), 2u);
    ASSERT_EQ(break_nat_coordinator_pair_close(fixture.coordinator, pair), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_nat_coordinator_pair_close(fixture.coordinator, pair), BREAK_RUNTIME_STALE);
    nat_fixture_dispose(&fixture);
}

TEST(nat_rejects_ping_from_unexpected_source)
{
    NatFixture fixture;
    BreakOnlineHandle pair;
    u8 packet[24] = {0};
    u64 deadline;
    ASSERT_TRUE(nat_fixture_init(&fixture, 2u, 1u));
    ASSERT_TRUE(register_and_pair(&fixture, &pair, UINT64_C(0x99), 1000u));
    deadline = time_microseconds() + UINT64_C(5000000);
    while (!break_nat_endpoint_armed(fixture.a, pair) && time_microseconds() < deadline) {
        (void)break_nat_endpoint_receive_socket(fixture.a, 32u);
        (void)break_nat_endpoint_poll(fixture.a, 32u);
        platform_thread_yield();
    }
    ASSERT_TRUE(break_nat_endpoint_armed(fixture.a, pair));
    memcpy(packet, "BRN1", 4u);
    packet[4] = 4u;
    packet[8] = (u8)pair.index;
    packet[9] = (u8)(pair.index >> 8u);
    packet[10] = (u8)(pair.index >> 16u);
    packet[11] = (u8)(pair.index >> 24u);
    packet[12] = (u8)pair.generation;
    packet[13] = (u8)(pair.generation >> 8u);
    packet[14] = (u8)(pair.generation >> 16u);
    packet[15] = (u8)(pair.generation >> 24u);
    packet[16] = 0x99u;
    ASSERT_EQ(net_sendto(fixture.attacker_socket, packet, sizeof(packet),
                         &fixture.a_address), (i32)sizeof(packet));
    (void)break_nat_endpoint_receive_socket(fixture.a, 32u);
    (void)break_nat_endpoint_poll(fixture.a, 32u);
    ASSERT_FALSE(break_nat_endpoint_connected(fixture.a, pair));
    ASSERT_TRUE(nat_pump_until_connected(&fixture, pair));
    nat_fixture_dispose(&fixture);
}

TEST(nat_expires_unconfirmed_pair_and_late_punch)
{
    NatFixture fixture;
    BreakOnlineHandle pair;
    u32 ack_mask = 99u;
    ASSERT_TRUE(nat_fixture_init(&fixture, 2u, 1u));
    ASSERT_TRUE(register_and_pair(&fixture, &pair, UINT64_C(0x55), 10u));
    fixture.now = 11u;
    ASSERT_EQ(break_nat_coordinator_poll(fixture.coordinator, 1u), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_nat_coordinator_pair_ack_mask(fixture.coordinator, pair, &ack_mask),
              BREAK_RUNTIME_STALE);
    nat_pump_once(&fixture);
    ASSERT_FALSE(break_nat_endpoint_connected(fixture.a, pair));
    ASSERT_FALSE(break_nat_endpoint_connected(fixture.b, pair));
    nat_fixture_dispose(&fixture);
}

TEST(nat_rejects_malformed_datagrams_and_beyond_peer_capacity)
{
    NatFixture fixture;
    u8 bad[16] = {0};
    ASSERT_TRUE(nat_fixture_init(&fixture, 1u, 1u));
    ASSERT_EQ(net_sendto(fixture.attacker_socket, bad, sizeof(bad),
                         &fixture.coordinator_address), (i32)sizeof(bad));
    memcpy(bad, "BRN1", 4u);
    bad[4] = 99u;
    ASSERT_EQ(net_sendto(fixture.attacker_socket, bad, sizeof(bad),
                         &fixture.coordinator_address), (i32)sizeof(bad));
    bad[4] = 1u;
    ASSERT_EQ(net_sendto(fixture.attacker_socket, bad, 15u,
                         &fixture.coordinator_address), 15);
    (void)break_nat_coordinator_receive_socket(fixture.coordinator, 32u);
    (void)break_nat_coordinator_poll(fixture.coordinator, 32u);
    ASSERT_EQ(break_nat_coordinator_invalid_messages(fixture.coordinator), 3u);
    ASSERT_EQ(break_nat_coordinator_peer_count(fixture.coordinator), 0u);
    ASSERT_EQ(break_nat_peer_hello(fixture.a), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_nat_peer_hello(fixture.b), BREAK_RUNTIME_OK);
    {
        u64 deadline = time_microseconds() + UINT64_C(5000000);
        while (!break_nat_endpoint_registered(fixture.a) && time_microseconds() < deadline) {
            nat_pump_once(&fixture);
            platform_thread_yield();
        }
    }
    ASSERT_TRUE(break_nat_endpoint_registered(fixture.a));
    ASSERT_FALSE(break_nat_endpoint_registered(fixture.b));
    ASSERT_EQ(break_nat_coordinator_peer_count(fixture.coordinator), 1u);
    nat_fixture_dispose(&fixture);
}

TEST(network_subsystem_initializes)
{
    ASSERT_TRUE(net_init());
}

TEST_MAIN_BEGIN()
    RUN_TEST(inbox_is_bounded_fifo_and_counts_rejections);
    RUN_TEST(inbox_supports_concurrent_producers_with_owner_consumer);
    RUN_TEST(network_subsystem_initializes);
    RUN_TEST(nat_real_udp_loopback_registers_punches_and_acknowledges);
    RUN_TEST(nat_rejects_ping_from_unexpected_source);
    RUN_TEST(nat_expires_unconfirmed_pair_and_late_punch);
    RUN_TEST(nat_rejects_malformed_datagrams_and_beyond_peer_capacity);
    net_shutdown();
TEST_MAIN_END()
