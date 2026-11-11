#include "test_framework.h"
#include <network/break_online_inbox.h>
#include <network/break_online_nat.h>
#include <core/platform_thread.h>
#include <platform/time.h>
#include <crypto/break_crypto.h>

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

static bool directory_key(void *user, u64 session, u8 out_key[32])
{
    AuthDirectory *directory = (AuthDirectory *)user;
    usize i;
    for (i = 0u; i < directory->count; ++i) {
        if (directory->sessions[i] == session) {
            u32 j;
            for (j = 0u; j < 32u; ++j) out_key[j] = (u8)(session * 17u + j);
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

TEST(inbox_concurrent_overload_accounting_is_exact)
{
    BreakOnlineInbox *inbox = NULL;
    InboxProducer producers[2];
    PlatformThread threads[2];
    BreakOnlineInboxStats stats;
    BreakOnlineDatagram datagram;
    u32 received = 0u;
    u32 i;
    ASSERT_EQ(break_online_inbox_create(64u, &inbox), BREAK_RUNTIME_OK);
    memset(producers, 0, sizeof(producers));
    for (i = 0u; i < 2u; ++i) {
        producers[i].inbox = inbox;
        strcpy(producers[i].source.host, "127.0.0.1");
        producers[i].source.port = (u16)(200u + i);
        producers[i].start = (u32)(i * 64u);
        producers[i].count = 64u;
        ASSERT_TRUE(platform_thread_create(&threads[i], inbox_produce, &producers[i]));
    }
    for (i = 0u; i < 2u; ++i) platform_thread_join(threads[i]);
    ASSERT_EQ(producers[0].accepted + producers[1].accepted, 64u);
    ASSERT_EQ(break_online_inbox_stats(inbox, &stats), BREAK_RUNTIME_OK);
    ASSERT_EQ(stats.accepted, 64u);
    ASSERT_EQ(stats.overload_rejects, 64u);
    ASSERT_EQ(stats.high_water, 64u);
    while (true) {
        bool ready = false;
        ASSERT_EQ(break_online_inbox_poll(inbox, &datagram, &ready), BREAK_RUNTIME_OK);
        if (!ready) break;
        ++received;
    }
    ASSERT_EQ(received, 64u);
    break_online_inbox_destroy(inbox);
}

typedef struct NatFixture {
    NetSocket *coordinator_socket;
    NetSocket *a_socket;
    NetSocket *b_socket;
    NetSocket *c_socket;
    NetSocket *d_socket;
    NetSocket *attacker_socket;
    NetAddress coordinator_address;
    NetAddress a_address;
    NetAddress b_address;
    NetAddress c_address;
    NetAddress d_address;
    BreakNatCoordinator *coordinator;
    BreakNatEndpoint *a;
    BreakNatEndpoint *b;
    BreakNatEndpoint *c;
    BreakNatEndpoint *d;
    AuthDirectory auth;
    u64 now;
    u64 a_now;
    u64 b_now;
    u64 c_now;
    u64 d_now;
} NatFixture;

static bool nat_fixture_init(NatFixture *fixture, u32 max_peers, u32 max_pairs)
{
    BreakNatCoordinatorConfig coordinator_config;
    BreakNatEndpointConfig endpoint_config;
    u32 i;
    memset(fixture, 0, sizeof(*fixture));
    fixture->coordinator_socket = net_udp_create(0);
    fixture->a_socket = net_udp_create(0);
    fixture->b_socket = net_udp_create(0);
    fixture->c_socket = net_udp_create(0);
    fixture->d_socket = net_udp_create(0);
    fixture->attacker_socket = net_udp_create(0);
    if (!fixture->coordinator_socket || !fixture->a_socket ||
        !fixture->b_socket || !fixture->c_socket || !fixture->d_socket ||
        !fixture->attacker_socket) return false;
    net_set_nonblocking(fixture->coordinator_socket, true);
    net_set_nonblocking(fixture->a_socket, true);
    net_set_nonblocking(fixture->b_socket, true);
    net_set_nonblocking(fixture->c_socket, true);
    net_set_nonblocking(fixture->d_socket, true);
    net_set_nonblocking(fixture->attacker_socket, true);
    fixture->coordinator_address = loopback_address(fixture->coordinator_socket);
    fixture->a_address = loopback_address(fixture->a_socket);
    fixture->b_address = loopback_address(fixture->b_socket);
    fixture->c_address = loopback_address(fixture->c_socket);
    fixture->d_address = loopback_address(fixture->d_socket);
    if (!fixture->coordinator_address.port || !fixture->a_address.port ||
        !fixture->b_address.port || !fixture->c_address.port ||
        !fixture->d_address.port) return false;
    fixture->auth.sessions[0] = 11u;
    fixture->auth.sessions[1] = 22u;
    fixture->auth.sessions[2] = 33u;
    fixture->auth.sessions[3] = 44u;
    fixture->auth.identities[0] = 1011u;
    fixture->auth.identities[1] = 1022u;
    fixture->auth.identities[2] = 1033u;
    fixture->auth.identities[3] = 1044u;
    fixture->auth.count = 4u;
    memset(&coordinator_config, 0, sizeof(coordinator_config));
    for (i = 0u; i < 32u; ++i) coordinator_config.challenge_key[i] = (u8)(i * 7u + 3u);
    coordinator_config.max_peers = max_peers;
    coordinator_config.max_pairs = max_pairs;
    coordinator_config.queue_capacity = 32u;
    coordinator_config.auth.user = &fixture->auth;
    coordinator_config.auth.authenticate = directory_auth;
    coordinator_config.auth.session_key = directory_key;
    coordinator_config.clock = fake_clock;
    coordinator_config.clock_user = &fixture->now;
    if (break_nat_coordinator_create(fixture->coordinator_socket,
                                     &coordinator_config,
                                     &fixture->coordinator) != BREAK_RUNTIME_OK) return false;
    memset(&endpoint_config, 0, sizeof(endpoint_config));
    endpoint_config.queue_capacity = 32u;
    endpoint_config.session_key = directory_key;
    endpoint_config.session_key_user = &fixture->auth;
    endpoint_config.clock = fake_clock;
    endpoint_config.clock_user = &fixture->a_now;
    endpoint_config.session = 11u;
    if (break_nat_endpoint_create(fixture->a_socket, &fixture->coordinator_address,
                                  &endpoint_config, &fixture->a) != BREAK_RUNTIME_OK) return false;
    endpoint_config.session = 22u;
    endpoint_config.clock_user = &fixture->b_now;
    if (break_nat_endpoint_create(fixture->b_socket, &fixture->coordinator_address,
                                  &endpoint_config, &fixture->b) != BREAK_RUNTIME_OK) return false;
    endpoint_config.session = 33u;
    endpoint_config.clock_user = &fixture->c_now;
    if (break_nat_endpoint_create(fixture->c_socket, &fixture->coordinator_address,
                                  &endpoint_config, &fixture->c) != BREAK_RUNTIME_OK) return false;
    endpoint_config.session = 44u;
    endpoint_config.clock_user = &fixture->d_now;
    if (break_nat_endpoint_create(fixture->d_socket, &fixture->coordinator_address,
                                  &endpoint_config, &fixture->d) != BREAK_RUNTIME_OK) return false;
    return true;
}

static void nat_fixture_dispose(NatFixture *fixture)
{
    break_nat_endpoint_destroy(fixture->a);
    break_nat_endpoint_destroy(fixture->b);
    break_nat_endpoint_destroy(fixture->c);
    break_nat_endpoint_destroy(fixture->d);
    break_nat_coordinator_destroy(fixture->coordinator);
    net_close(fixture->coordinator_socket);
    net_close(fixture->a_socket);
    net_close(fixture->b_socket);
    net_close(fixture->c_socket);
    net_close(fixture->d_socket);
    net_close(fixture->attacker_socket);
}

static BreakRuntimeError nat_pump_once(NatFixture *fixture)
{
    BreakRuntimeError result;
    result = break_nat_coordinator_receive_socket(fixture->coordinator, 32u);
    if (result != BREAK_RUNTIME_OK) return result;
    result = break_nat_endpoint_receive_socket(fixture->a, 32u);
    if (result != BREAK_RUNTIME_OK) return result;
    result = break_nat_endpoint_receive_socket(fixture->b, 32u);
    if (result != BREAK_RUNTIME_OK) return result;
    result = break_nat_endpoint_receive_socket(fixture->c, 32u);
    if (result != BREAK_RUNTIME_OK) return result;
    result = break_nat_endpoint_receive_socket(fixture->d, 32u);
    if (result != BREAK_RUNTIME_OK) return result;
    result = break_nat_coordinator_poll(fixture->coordinator, 32u);
    if (result != BREAK_RUNTIME_OK) return result;
    result = break_nat_endpoint_poll(fixture->a, 32u);
    if (result != BREAK_RUNTIME_OK) return result;
    result = break_nat_endpoint_poll(fixture->b, 32u);
    if (result != BREAK_RUNTIME_OK) return result;
    result = break_nat_endpoint_poll(fixture->c, 32u);
    if (result != BREAK_RUNTIME_OK) return result;
    result = break_nat_endpoint_poll(fixture->d, 32u);
    return result;
}

static bool nat_pump_until_registered(NatFixture *fixture)
{
    u64 deadline = time_microseconds() + UINT64_C(5000000);
    while (time_microseconds() < deadline) {
        (void)nat_pump_once(fixture);
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
        (void)nat_pump_once(fixture);
        if (break_nat_endpoint_connected(fixture->a, pair) &&
            break_nat_endpoint_connected(fixture->b, pair) &&
            break_nat_coordinator_pair_ack_mask(fixture->coordinator, pair,
                                                &ack_mask) == BREAK_RUNTIME_OK &&
            ack_mask == 3u) return true;
        platform_thread_yield();
    }
    return false;
}

static BreakRuntimeError nat_pump_until_closed(NatFixture *fixture, BreakOnlineHandle pair)
{
    u64 deadline = time_microseconds() + UINT64_C(5000000);
    while (time_microseconds() < deadline) {
        BreakRuntimeError result = nat_pump_once(fixture);
        if (result != BREAK_RUNTIME_OK) return result;
        if (!break_nat_endpoint_connected(fixture->a, pair) &&
            !break_nat_endpoint_connected(fixture->b, pair) &&
            !break_nat_endpoint_armed(fixture->a, pair) &&
            !break_nat_endpoint_armed(fixture->b, pair)) return BREAK_RUNTIME_OK;
        platform_thread_yield();
    }
    return BREAK_RUNTIME_OVERLOAD;
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
    (void)nat_pump_once(&fixture);
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

TEST(nat_rejects_unknown_pair_and_nonce_from_expected_peer)
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
    packet[16] = 0x98u;
    ASSERT_EQ(net_sendto(fixture.b_socket, packet, sizeof(packet),
                         &fixture.a_address), (i32)sizeof(packet));
    packet[16] = 0x99u;
    packet[12] = (u8)(pair.generation + 1u);
    ASSERT_EQ(net_sendto(fixture.b_socket, packet, sizeof(packet),
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
    fixture.a_now = 11u;
    fixture.b_now = 11u;
    ASSERT_EQ(break_nat_coordinator_poll(fixture.coordinator, 1u), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_nat_coordinator_pair_ack_mask(fixture.coordinator, pair, &ack_mask),
              BREAK_RUNTIME_STALE);
    (void)nat_pump_once(&fixture);
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
    {
        u64 deadline = time_microseconds() + UINT64_C(5000000);
        while (break_nat_coordinator_invalid_messages(fixture.coordinator) < 3u &&
               time_microseconds() < deadline) {
            ASSERT_EQ(break_nat_coordinator_receive_socket(fixture.coordinator, 32u),
                      BREAK_RUNTIME_OK);
            ASSERT_EQ(break_nat_coordinator_poll(fixture.coordinator, 32u),
                      BREAK_RUNTIME_OK);
            platform_thread_yield();
        }
    }
    ASSERT_EQ(break_nat_coordinator_invalid_messages(fixture.coordinator), 3u);
    ASSERT_EQ(break_nat_coordinator_peer_count(fixture.coordinator), 0u);
    ASSERT_EQ(break_nat_peer_hello(fixture.a), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_nat_peer_hello(fixture.b), BREAK_RUNTIME_OK);
    {
        u64 deadline = time_microseconds() + UINT64_C(5000000);
        while (!break_nat_endpoint_registered(fixture.a) && time_microseconds() < deadline) {
            (void)nat_pump_once(&fixture);
            platform_thread_yield();
        }
    }
    ASSERT_TRUE(break_nat_endpoint_registered(fixture.a));
    ASSERT_FALSE(break_nat_endpoint_registered(fixture.b));
    ASSERT_EQ(break_nat_coordinator_peer_count(fixture.coordinator), 1u);
    nat_fixture_dispose(&fixture);
}

static void put_test_u16(u8 *out, u16 value)
{
    out[0] = (u8)value;
    out[1] = (u8)(value >> 8u);
}

static void put_test_u32(u8 *out, u32 value)
{
    u32 i;
    for (i = 0u; i < 4u; ++i) out[i] = (u8)(value >> (i * 8u));
}

static void put_test_u64(u8 *out, u64 value)
{
    u32 i;
    for (i = 0u; i < 8u; ++i) out[i] = (u8)(value >> (i * 8u));
}

static void put_test_handle(u8 *out, BreakOnlineHandle handle)
{
    put_test_u32(out, handle.index);
    put_test_u32(out + 4u, handle.generation);
}

static void send_test_punch(NatFixture *fixture, BreakOnlineHandle pair,
                            u64 nonce, u64 deadline_or_ttl, u64 sequence)
{
    u8 packet[106] = {0};
    BreakOnlineHandle recipient = {0u, 1u};
    u8 key[32];
    (void)break_nat_coordinator_peer_for_session(fixture->coordinator, 11u, &recipient);
    memcpy(packet, "BRN1", 4u);
    packet[4] = 3u;
    put_test_handle(packet + 8u, pair);
    put_test_handle(packet + 16u, recipient);
    put_test_u64(packet + 24u, 11u);
    put_test_u64(packet + 32u, nonce);
    put_test_u64(packet + 40u, deadline_or_ttl);
    put_test_u64(packet + 48u, sequence);
    memcpy(packet + 56u, fixture->b_address.host, strlen(fixture->b_address.host));
    put_test_u16(packet + 72u, fixture->b_address.port);
    ASSERT_TRUE(directory_key(&fixture->auth, 11u, key));
    ASSERT_TRUE(break_crypto_hmac_sha256(key, sizeof(key), packet, 74u, packet + 74u));
    ASSERT_EQ(net_sendto(fixture->coordinator_socket, packet, sizeof(packet),
                         &fixture->a_address), (i32)sizeof(packet));
}

static void send_test_close(NatFixture *fixture, BreakOnlineHandle pair, u64 sequence)
{
    u8 packet[72] = {0};
    BreakOnlineHandle recipient = {0u, 1u};
    u8 key[32];
    (void)break_nat_coordinator_peer_for_session(fixture->coordinator, 11u, &recipient);
    memcpy(packet, "BRN1", 4u);
    packet[4] = 8u;
    put_test_handle(packet + 8u, pair);
    put_test_handle(packet + 16u, recipient);
    put_test_u64(packet + 24u, 11u);
    put_test_u64(packet + 32u, sequence);
    ASSERT_TRUE(directory_key(&fixture->auth, 11u, key));
    ASSERT_TRUE(break_crypto_hmac_sha256(key, sizeof(key), packet, 40u, packet + 40u));
    ASSERT_EQ(net_sendto(fixture->coordinator_socket, packet, sizeof(packet),
                         &fixture->a_address), (i32)sizeof(packet));
}

TEST(nat_pre_pair_cross_socket_hello_replay_cannot_move_observed)
{
    NatFixture fixture;
    BreakOnlineHandle a_peer;
    NetAddress observed;
    u8 hello[16] = {0};
    ASSERT_TRUE(nat_fixture_init(&fixture, 2u, 1u));
    ASSERT_EQ(break_nat_peer_hello(fixture.a), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_nat_peer_hello(fixture.b), BREAK_RUNTIME_OK);
    ASSERT_TRUE(nat_pump_until_registered(&fixture));
    ASSERT_EQ(break_nat_coordinator_peer_for_session(fixture.coordinator, 11u, &a_peer),
              BREAK_RUNTIME_OK);
    memcpy(hello, "BRN1", 4u);
    hello[4] = 1u;
    put_test_u64(hello + 8u, 11u);
    ASSERT_EQ(net_sendto(fixture.attacker_socket, hello, sizeof(hello),
                         &fixture.coordinator_address), (i32)sizeof(hello));
    (void)break_nat_coordinator_receive_socket(fixture.coordinator, 1u);
    (void)break_nat_coordinator_poll(fixture.coordinator, 1u);
    ASSERT_EQ(break_nat_coordinator_peer_observed(fixture.coordinator, a_peer, &observed),
              BREAK_RUNTIME_OK);
    ASSERT_TRUE(net_address_equal(&observed, &fixture.a_address));
    nat_fixture_dispose(&fixture);
}

TEST(nat_pre_registration_punch_is_rejected)
{
    NatFixture fixture;
    BreakOnlineHandle pair = {0u, 1u};
    ASSERT_TRUE(nat_fixture_init(&fixture, 2u, 1u));
    send_test_punch(&fixture, pair, 55u, 1000u, 1u);
    (void)break_nat_endpoint_receive_socket(fixture.a, 1u);
    (void)break_nat_endpoint_poll(fixture.a, 1u);
    ASSERT_FALSE(break_nat_endpoint_armed(fixture.a, pair));
    nat_fixture_dispose(&fixture);
}

TEST(nat_duplicate_punch_does_not_reset_connected)
{
    NatFixture fixture;
    BreakOnlineHandle pair;
    ASSERT_TRUE(nat_fixture_init(&fixture, 2u, 1u));
    ASSERT_TRUE(register_and_pair(&fixture, &pair, 55u, 1000u));
    ASSERT_TRUE(nat_pump_until_connected(&fixture, pair));
    send_test_punch(&fixture, pair, 55u, 1000u, 1u);
    (void)break_nat_endpoint_receive_socket(fixture.a, 1u);
    (void)break_nat_endpoint_poll(fixture.a, 1u);
    ASSERT_TRUE(break_nat_endpoint_connected(fixture.a, pair));
    nat_fixture_dispose(&fixture);
}

TEST(nat_conflicting_punch_does_not_replace_connected)
{
    NatFixture fixture;
    BreakOnlineHandle pair;
    ASSERT_TRUE(nat_fixture_init(&fixture, 2u, 1u));
    ASSERT_TRUE(register_and_pair(&fixture, &pair, 55u, 1000u));
    ASSERT_TRUE(nat_pump_until_connected(&fixture, pair));
    send_test_punch(&fixture, pair, 56u, 1000u, 1u);
    (void)break_nat_endpoint_receive_socket(fixture.a, 1u);
    (void)break_nat_endpoint_poll(fixture.a, 1u);
    ASSERT_TRUE(break_nat_endpoint_connected(fixture.a, pair));
    send_test_punch(&fixture, pair, 55u, 1001u, 1u);
    (void)break_nat_endpoint_receive_socket(fixture.a, 1u);
    (void)break_nat_endpoint_poll(fixture.a, 1u);
    ASSERT_TRUE(break_nat_endpoint_connected(fixture.a, pair));
    send_test_punch(&fixture, pair, 55u, 1000u, 2u);
    (void)break_nat_endpoint_receive_socket(fixture.a, 1u);
    (void)break_nat_endpoint_poll(fixture.a, 1u);
    ASSERT_TRUE(break_nat_endpoint_connected(fixture.a, pair));
    nat_fixture_dispose(&fixture);
}

TEST(nat_tampered_punch_mac_is_rejected)
{
    NatFixture fixture;
    BreakOnlineHandle pair = {0u, 1u};
    BreakOnlineHandle recipient;
    u8 packet[106] = {0};
    u8 key[32];
    ASSERT_TRUE(nat_fixture_init(&fixture, 2u, 1u));
    ASSERT_EQ(break_nat_peer_hello(fixture.a), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_nat_peer_hello(fixture.b), BREAK_RUNTIME_OK);
    ASSERT_TRUE(nat_pump_until_registered(&fixture));
    ASSERT_EQ(break_nat_coordinator_peer_for_session(fixture.coordinator, 11u, &recipient),
              BREAK_RUNTIME_OK);
    memcpy(packet, "BRN1", 4u);
    packet[4] = 3u;
    put_test_handle(packet + 8u, pair);
    put_test_handle(packet + 16u, recipient);
    put_test_u64(packet + 24u, 11u);
    put_test_u64(packet + 32u, 77u);
    put_test_u64(packet + 40u, 1000u);
    put_test_u64(packet + 48u, 1u);
    memcpy(packet + 56u, fixture.b_address.host, strlen(fixture.b_address.host));
    put_test_u16(packet + 72u, fixture.b_address.port);
    ASSERT_TRUE(directory_key(&fixture.auth, 11u, key));
    ASSERT_TRUE(break_crypto_hmac_sha256(key, sizeof(key), packet, 74u, packet + 74u));
    packet[74] ^= 1u;
    ASSERT_EQ(net_sendto(fixture.coordinator_socket, packet, sizeof(packet),
                         &fixture.a_address), (i32)sizeof(packet));
    (void)break_nat_endpoint_receive_socket(fixture.a, 1u);
    (void)break_nat_endpoint_poll(fixture.a, 1u);
    ASSERT_FALSE(break_nat_endpoint_armed(fixture.a, pair));
    nat_fixture_dispose(&fixture);
}

TEST(nat_captured_valid_hello_replay_from_other_socket_is_rejected)
{
    NatFixture fixture;
    BreakOnlineHandle a_peer;
    NetAddress observed;
    NetAddress source;
    u8 discover[16] = {0};
    u8 challenge[32];
    u8 hello[72] = {0};
    u8 key[32];
    i32 size;
    ASSERT_TRUE(nat_fixture_init(&fixture, 2u, 1u));
    memcpy(discover, "BRN1", 4u);
    discover[4] = 6u;
    put_test_u64(discover + 8u, 11u);
    ASSERT_EQ(net_sendto(fixture.a_socket, discover, sizeof(discover),
                         &fixture.coordinator_address), (i32)sizeof(discover));
    size = NET_WOULD_BLOCK;
    {
        u64 deadline = time_microseconds() + UINT64_C(5000000);
        while (size == NET_WOULD_BLOCK && time_microseconds() < deadline) {
            ASSERT_EQ(break_nat_coordinator_receive_socket(fixture.coordinator, 1u),
                      BREAK_RUNTIME_OK);
            ASSERT_EQ(break_nat_coordinator_poll(fixture.coordinator, 1u),
                      BREAK_RUNTIME_OK);
            size = net_recvfrom(fixture.a_socket, challenge, sizeof(challenge), &source);
            if (size == NET_WOULD_BLOCK) platform_thread_yield();
        }
    }
    ASSERT_EQ(size, (i32)sizeof(challenge));
    ASSERT_TRUE(memcmp(challenge, "BRN1", 4u) == 0);
    ASSERT_EQ(challenge[4], 7u);
    memcpy(hello, "BRN1", 4u);
    hello[4] = 1u;
    put_test_u64(hello + 8u, 11u);
    memcpy(hello + 16u, challenge + 16u, 16u);
    put_test_u64(hello + 32u, 1u);
    ASSERT_TRUE(directory_key(&fixture.auth, 11u, key));
    ASSERT_TRUE(break_crypto_hmac_sha256(key, sizeof(key), hello, 40u, hello + 40u));
    ASSERT_EQ(net_sendto(fixture.a_socket, hello, sizeof(hello),
                         &fixture.coordinator_address), (i32)sizeof(hello));
    {
        u64 deadline = time_microseconds() + UINT64_C(5000000);
        while (break_nat_coordinator_peer_for_session(fixture.coordinator, 11u, &a_peer) !=
                   BREAK_RUNTIME_OK && time_microseconds() < deadline) {
            ASSERT_EQ(break_nat_coordinator_receive_socket(fixture.coordinator, 1u),
                      BREAK_RUNTIME_OK);
            ASSERT_EQ(break_nat_coordinator_poll(fixture.coordinator, 1u),
                      BREAK_RUNTIME_OK);
            platform_thread_yield();
        }
    }
    ASSERT_EQ(break_nat_coordinator_peer_for_session(fixture.coordinator, 11u, &a_peer),
              BREAK_RUNTIME_OK);
    ASSERT_EQ(net_sendto(fixture.attacker_socket, hello, sizeof(hello),
                         &fixture.coordinator_address), (i32)sizeof(hello));
    {
        u64 deadline = time_microseconds() + UINT64_C(5000000);
        while (break_nat_coordinator_invalid_messages(fixture.coordinator) == 0u &&
               time_microseconds() < deadline) {
            ASSERT_EQ(break_nat_coordinator_receive_socket(fixture.coordinator, 1u),
                      BREAK_RUNTIME_OK);
            ASSERT_EQ(break_nat_coordinator_poll(fixture.coordinator, 1u),
                      BREAK_RUNTIME_OK);
            platform_thread_yield();
        }
    }
    ASSERT_EQ(break_nat_coordinator_invalid_messages(fixture.coordinator), 1u);
    ASSERT_EQ(break_nat_coordinator_peer_observed(fixture.coordinator, a_peer, &observed),
              BREAK_RUNTIME_OK);
    ASSERT_TRUE(net_address_equal(&observed, &fixture.a_address));
    ASSERT_EQ(break_nat_coordinator_peer_count(fixture.coordinator), 1u);
    nat_fixture_dispose(&fixture);
}

TEST(nat_pair_close_resets_connected_and_allows_repair)
{
    NatFixture fixture;
    BreakOnlineHandle pair;
    BreakOnlineHandle replacement;
    ASSERT_TRUE(nat_fixture_init(&fixture, 2u, 1u));
    ASSERT_TRUE(register_and_pair(&fixture, &pair, 55u, 1000u));
    ASSERT_TRUE(nat_pump_until_connected(&fixture, pair));
    ASSERT_EQ(break_nat_coordinator_pair_close(fixture.coordinator, pair), BREAK_RUNTIME_OK);
    ASSERT_EQ(nat_pump_until_closed(&fixture, pair), BREAK_RUNTIME_OK);
    ASSERT_FALSE(break_nat_endpoint_connected(fixture.a, pair));
    ASSERT_FALSE(break_nat_endpoint_connected(fixture.b, pair));
    ASSERT_FALSE(break_nat_endpoint_armed(fixture.a, pair));
    ASSERT_FALSE(break_nat_endpoint_armed(fixture.b, pair));
    send_test_punch(&fixture, pair, 55u, 1000u, 1u);
    (void)break_nat_endpoint_receive_socket(fixture.a, 1u);
    (void)break_nat_endpoint_poll(fixture.a, 1u);
    ASSERT_FALSE(break_nat_endpoint_armed(fixture.a, pair));
    ASSERT_TRUE(register_and_pair(&fixture, &replacement, 66u, 1000u));
    ASSERT_NEQ(replacement.generation, pair.generation);
    ASSERT_TRUE(nat_pump_until_connected(&fixture, replacement));
    nat_fixture_dispose(&fixture);
}

TEST(nat_close_before_punch_blocks_late_punch)
{
    NatFixture fixture;
    BreakOnlineHandle pair;
    u32 i;
    ASSERT_TRUE(nat_fixture_init(&fixture, 2u, 1u));
    ASSERT_TRUE(register_and_pair(&fixture, &pair, 77u, 1000u));
    ASSERT_EQ(break_nat_coordinator_pair_close(fixture.coordinator, pair), BREAK_RUNTIME_OK);
    for (i = 0u; i < 8u; ++i) (void)nat_pump_once(&fixture);
    ASSERT_FALSE(break_nat_endpoint_armed(fixture.a, pair));
    ASSERT_FALSE(break_nat_endpoint_armed(fixture.b, pair));
    send_test_punch(&fixture, pair, 77u, 1000u, 1u);
    (void)break_nat_endpoint_receive_socket(fixture.a, 1u);
    (void)break_nat_endpoint_poll(fixture.a, 1u);
    ASSERT_FALSE(break_nat_endpoint_armed(fixture.a, pair));
    nat_fixture_dispose(&fixture);
}

TEST(nat_punch_ttl_uses_each_endpoint_local_clock)
{
    NatFixture fixture;
    BreakOnlineHandle pair;
    ASSERT_TRUE(nat_fixture_init(&fixture, 2u, 1u));
    fixture.now = 10u;
    fixture.a_now = 100000u;
    fixture.b_now = 100020u;
    ASSERT_TRUE(register_and_pair(&fixture, &pair, 88u, 1000u));
    ASSERT_TRUE(nat_pump_until_connected(&fixture, pair));
    nat_fixture_dispose(&fixture);
}

TEST(nat_pair_capacity_and_stale_peer_are_rejected)
{
    NatFixture fixture;
    BreakOnlineHandle peers[4];
    BreakOnlineHandle pair;
    BreakOnlineHandle stale;
    u64 deadline;
    ASSERT_TRUE(nat_fixture_init(&fixture, 4u, 1u));
    ASSERT_EQ(break_nat_peer_hello(fixture.a), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_nat_peer_hello(fixture.b), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_nat_peer_hello(fixture.c), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_nat_peer_hello(fixture.d), BREAK_RUNTIME_OK);
    deadline = time_microseconds() + UINT64_C(5000000);
    while (time_microseconds() < deadline) {
        (void)nat_pump_once(&fixture);
        if (break_nat_coordinator_peer_count(fixture.coordinator) == 4u &&
            break_nat_endpoint_registered(fixture.a) &&
            break_nat_endpoint_registered(fixture.b) &&
            break_nat_endpoint_registered(fixture.c) &&
            break_nat_endpoint_registered(fixture.d)) break;
        platform_thread_yield();
    }
    ASSERT_EQ(break_nat_coordinator_peer_count(fixture.coordinator), 4u);
    ASSERT_EQ(break_nat_coordinator_peer_for_session(fixture.coordinator, 11u, &peers[0]), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_nat_coordinator_peer_for_session(fixture.coordinator, 22u, &peers[1]), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_nat_coordinator_peer_for_session(fixture.coordinator, 33u, &peers[2]), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_nat_coordinator_peer_for_session(fixture.coordinator, 44u, &peers[3]), BREAK_RUNTIME_OK);
    stale = peers[0];
    stale.generation++;
    ASSERT_EQ(break_nat_coordinator_pair(fixture.coordinator, stale, peers[1],
                                         10u, 1000u, &pair), BREAK_RUNTIME_STALE);
    ASSERT_EQ(break_nat_coordinator_pair(fixture.coordinator, peers[0], peers[1],
                                         11u, 1000u, &pair), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_nat_coordinator_pair(fixture.coordinator, peers[2], peers[3],
                                         12u, 1000u, &pair), BREAK_RUNTIME_OVERLOAD);
    nat_fixture_dispose(&fixture);
}

TEST(nat_captured_punch_after_local_expiry_cannot_rearm)
{
    NatFixture fixture;
    BreakOnlineHandle pair;
    u64 deadline;
    ASSERT_TRUE(nat_fixture_init(&fixture, 2u, 1u));
    ASSERT_TRUE(register_and_pair(&fixture, &pair, 55u, 10u));
    deadline = time_microseconds() + UINT64_C(5000000);
    while (!break_nat_endpoint_armed(fixture.a, pair) && time_microseconds() < deadline) {
        (void)break_nat_endpoint_receive_socket(fixture.a, 32u);
        (void)break_nat_endpoint_poll(fixture.a, 32u);
        platform_thread_yield();
    }
    ASSERT_TRUE(break_nat_endpoint_armed(fixture.a, pair));
    fixture.a_now = 11u;
    (void)break_nat_endpoint_poll(fixture.a, 1u);
    ASSERT_FALSE(break_nat_endpoint_armed(fixture.a, pair));
    send_test_punch(&fixture, pair, 55u, 10u, 1u);
    (void)break_nat_endpoint_receive_socket(fixture.a, 1u);
    (void)break_nat_endpoint_poll(fixture.a, 1u);
    ASSERT_FALSE(break_nat_endpoint_armed(fixture.a, pair));
    nat_fixture_dispose(&fixture);
}

TEST(nat_two_close_cycles_reject_oldest_punch)
{
    NatFixture fixture;
    BreakOnlineHandle first;
    BreakOnlineHandle second;
    u32 i;
    ASSERT_TRUE(nat_fixture_init(&fixture, 2u, 1u));
    ASSERT_TRUE(register_and_pair(&fixture, &first, 55u, 1000u));
    ASSERT_TRUE(nat_pump_until_connected(&fixture, first));
    ASSERT_EQ(break_nat_coordinator_pair_close(fixture.coordinator, first), BREAK_RUNTIME_OK);
    ASSERT_TRUE(register_and_pair(&fixture, &second, 66u, 1000u));
    ASSERT_TRUE(nat_pump_until_connected(&fixture, second));
    ASSERT_EQ(break_nat_coordinator_pair_close(fixture.coordinator, second), BREAK_RUNTIME_OK);
    for (i = 0u; i < 8u; ++i) (void)nat_pump_once(&fixture);
    send_test_punch(&fixture, first, 55u, 1000u, 1u);
    (void)break_nat_endpoint_receive_socket(fixture.a, 1u);
    (void)break_nat_endpoint_poll(fixture.a, 1u);
    ASSERT_FALSE(break_nat_endpoint_armed(fixture.a, first));
    nat_fixture_dispose(&fixture);
}

TEST(nat_older_close_cannot_rollback_high_water)
{
    NatFixture fixture;
    BreakOnlineHandle first;
    BreakOnlineHandle second;
    u32 i;
    ASSERT_TRUE(nat_fixture_init(&fixture, 2u, 1u));
    ASSERT_TRUE(register_and_pair(&fixture, &first, 55u, 1000u));
    ASSERT_TRUE(nat_pump_until_connected(&fixture, first));
    ASSERT_EQ(break_nat_coordinator_pair_close(fixture.coordinator, first), BREAK_RUNTIME_OK);
    ASSERT_TRUE(register_and_pair(&fixture, &second, 66u, 1000u));
    ASSERT_TRUE(nat_pump_until_connected(&fixture, second));
    ASSERT_EQ(break_nat_coordinator_pair_close(fixture.coordinator, second), BREAK_RUNTIME_OK);
    for (i = 0u; i < 8u; ++i) (void)nat_pump_once(&fixture);
    send_test_close(&fixture, first, 2u);
    (void)break_nat_endpoint_receive_socket(fixture.a, 1u);
    (void)break_nat_endpoint_poll(fixture.a, 1u);
    send_test_punch(&fixture, second, 66u, 1000u, 3u);
    (void)break_nat_endpoint_receive_socket(fixture.a, 1u);
    (void)break_nat_endpoint_poll(fixture.a, 1u);
    ASSERT_FALSE(break_nat_endpoint_armed(fixture.a, second));
    nat_fixture_dispose(&fixture);
}

TEST(nat_forged_discover_flood_does_not_block_legitimate_registration)
{
    NatFixture fixture;
    u8 discover[16] = {0};
    u32 i;
    ASSERT_TRUE(nat_fixture_init(&fixture, 2u, 1u));
    memcpy(discover, "BRN1", 4u);
    discover[4] = 6u;
    for (i = 0u; i < 8u; ++i) {
        put_test_u64(discover + 8u, 1000u + i);
        ASSERT_EQ(net_sendto(fixture.attacker_socket, discover, sizeof(discover),
                             &fixture.coordinator_address), (i32)sizeof(discover));
    }
    (void)break_nat_coordinator_receive_socket(fixture.coordinator, 32u);
    (void)break_nat_coordinator_poll(fixture.coordinator, 32u);
    ASSERT_EQ(break_nat_peer_hello(fixture.a), BREAK_RUNTIME_OK);
    ASSERT_EQ(break_nat_peer_hello(fixture.b), BREAK_RUNTIME_OK);
    ASSERT_TRUE(nat_pump_until_registered(&fixture));
    ASSERT_EQ(break_nat_coordinator_peer_count(fixture.coordinator), 2u);
    nat_fixture_dispose(&fixture);
}

TEST(network_subsystem_initializes)
{
    ASSERT_TRUE(net_init());
}

TEST_MAIN_BEGIN()
    RUN_TEST(inbox_is_bounded_fifo_and_counts_rejections);
    RUN_TEST(inbox_supports_concurrent_producers_with_owner_consumer);
    RUN_TEST(inbox_concurrent_overload_accounting_is_exact);
    RUN_TEST(network_subsystem_initializes);
    RUN_TEST(nat_real_udp_loopback_registers_punches_and_acknowledges);
    RUN_TEST(nat_rejects_ping_from_unexpected_source);
    RUN_TEST(nat_rejects_unknown_pair_and_nonce_from_expected_peer);
    RUN_TEST(nat_expires_unconfirmed_pair_and_late_punch);
    RUN_TEST(nat_rejects_malformed_datagrams_and_beyond_peer_capacity);
    RUN_TEST(nat_pre_pair_cross_socket_hello_replay_cannot_move_observed);
    RUN_TEST(nat_pre_registration_punch_is_rejected);
    RUN_TEST(nat_duplicate_punch_does_not_reset_connected);
    RUN_TEST(nat_conflicting_punch_does_not_replace_connected);
    RUN_TEST(nat_tampered_punch_mac_is_rejected);
    RUN_TEST(nat_captured_valid_hello_replay_from_other_socket_is_rejected);
    RUN_TEST(nat_pair_close_resets_connected_and_allows_repair);
    RUN_TEST(nat_close_before_punch_blocks_late_punch);
    RUN_TEST(nat_punch_ttl_uses_each_endpoint_local_clock);
    RUN_TEST(nat_pair_capacity_and_stale_peer_are_rejected);
    RUN_TEST(nat_captured_punch_after_local_expiry_cannot_rearm);
    RUN_TEST(nat_two_close_cycles_reject_oldest_punch);
    RUN_TEST(nat_older_close_cannot_rollback_high_water);
    RUN_TEST(nat_forged_discover_flood_does_not_block_legitimate_registration);
    net_shutdown();
TEST_MAIN_END()
