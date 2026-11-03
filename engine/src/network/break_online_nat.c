#include <network/break_online_nat.h>

#include <network/break_online_inbox.h>
#include <core/platform_thread.h>

#include <stdlib.h>
#include <string.h>

#define NAT_HELLO_SIZE 16u
#define NAT_WELCOME_SIZE 24u
#define NAT_PUNCH_SIZE 50u
#define NAT_PING_SIZE 24u
#define NAT_ACK_SIZE 24u
#define NAT_HOST_SIZE 16u

typedef enum NatMessageKind {
    NAT_HELLO = 1,
    NAT_WELCOME = 2,
    NAT_PUNCH = 3,
    NAT_PING = 4,
    NAT_ACK = 5
} NatMessageKind;

typedef struct NatPeer {
    bool used;
    bool paired;
    u32 generation;
    u64 session;
    BreakOnlineIdentity identity;
    NetAddress observed;
} NatPeer;

typedef struct NatPair {
    bool used;
    u32 generation;
    u32 a;
    u32 b;
    u64 nonce;
    u64 expires_at;
    u32 ack_mask;
} NatPair;

struct BreakNatCoordinator {
    PlatformThreadId owner;
    NetSocket *socket;
    BreakOnlineAuthSource auth;
    BreakNatClockMsFn clock;
    void *clock_user;
    BreakOnlineInbox *inbox;
    NatPeer *peers;
    NatPair *pairs;
    u32 max_peers;
    u32 max_pairs;
    u32 peer_count;
    u32 pair_count;
    u64 invalid_messages;
};

struct BreakNatEndpoint {
    PlatformThreadId owner;
    NetSocket *socket;
    NetAddress coordinator;
    u64 session;
    BreakNatClockMsFn clock;
    void *clock_user;
    BreakOnlineInbox *inbox;
    bool registered;
    BreakOnlineHandle peer;
    bool active;
    bool connected;
    bool ping_sent;
    BreakOnlineHandle pair;
    NetAddress peer_address;
    u64 nonce;
    u64 expires_at;
};

static bool coordinator_owner(const BreakNatCoordinator *coordinator)
{
    return coordinator && platform_thread_id_equal(coordinator->owner,
                                                    platform_thread_current_id());
}

static bool endpoint_owner(const BreakNatEndpoint *endpoint)
{
    return endpoint && platform_thread_id_equal(endpoint->owner,
                                                 platform_thread_current_id());
}

static u32 initial_generation(u32 generation)
{
    return generation == 0u ? 1u : generation;
}

static u32 retire_generation(u32 generation)
{
    return generation == UINT32_MAX ? generation : generation + 1u;
}

static void put_u16(u8 *out, u16 value)
{
    out[0] = (u8)value;
    out[1] = (u8)(value >> 8u);
}

static void put_u32(u8 *out, u32 value)
{
    u32 i;
    for (i = 0u; i < 4u; ++i) out[i] = (u8)(value >> (i * 8u));
}

static void put_u64(u8 *out, u64 value)
{
    u32 i;
    for (i = 0u; i < 8u; ++i) out[i] = (u8)(value >> (i * 8u));
}

static u16 get_u16(const u8 *in)
{
    return (u16)((u16)in[0] | ((u16)in[1] << 8u));
}

static u32 get_u32(const u8 *in)
{
    u32 value = 0u;
    u32 i;
    for (i = 0u; i < 4u; ++i) value |= (u32)in[i] << (i * 8u);
    return value;
}

static u64 get_u64(const u8 *in)
{
    u64 value = 0u;
    u32 i;
    for (i = 0u; i < 8u; ++i) value |= (u64)in[i] << (i * 8u);
    return value;
}

static void put_handle(u8 *out, BreakOnlineHandle handle)
{
    put_u32(out, handle.index);
    put_u32(out + 4u, handle.generation);
}

static BreakOnlineHandle get_handle(const u8 *in)
{
    BreakOnlineHandle handle;
    handle.index = get_u32(in);
    handle.generation = get_u32(in + 4u);
    return handle;
}

static void make_header(u8 *out, NatMessageKind kind)
{
    memcpy(out, "BRN1", 4u);
    out[4] = (u8)kind;
    out[5] = 0u;
    out[6] = 0u;
    out[7] = 0u;
}

static bool valid_header(const BreakOnlineDatagram *datagram, NatMessageKind kind,
                         u32 size)
{
    return datagram->size == size && memcmp(datagram->bytes, "BRN1", 4u) == 0 &&
           datagram->bytes[4] == (u8)kind && datagram->bytes[5] == 0u &&
           datagram->bytes[6] == 0u && datagram->bytes[7] == 0u;
}

static BreakRuntimeError send_datagram(NetSocket *socket, const NetAddress *to,
                                       const u8 *data, u32 size)
{
    i32 result = net_sendto(socket, data, size, to);
    if (result == (i32)size) return BREAK_RUNTIME_OK;
    if (result == NET_WOULD_BLOCK) return BREAK_RUNTIME_OVERLOAD;
    return BREAK_RUNTIME_FAILED;
}

static BreakRuntimeError receive_datagrams(NetSocket *socket, BreakOnlineInbox *inbox,
                                           u32 max_datagrams)
{
    u32 i;
    if (!socket || !inbox || !max_datagrams) return BREAK_RUNTIME_INVALID;
    for (i = 0u; i < max_datagrams; ++i) {
        u8 bytes[BREAK_ONLINE_MAX_DATAGRAM];
        NetAddress source;
        i32 size = net_recvfrom(socket, bytes, sizeof(bytes), &source);
        BreakRuntimeError result;
        if (size == NET_WOULD_BLOCK) return BREAK_RUNTIME_OK;
        if (size <= 0) return BREAK_RUNTIME_FAILED;
        result = break_online_inbox_push(inbox, &source, bytes, (u32)size);
        if (result != BREAK_RUNTIME_OK) return result;
    }
    return BREAK_RUNTIME_OK;
}

static BreakRuntimeError find_peer(const BreakNatCoordinator *coordinator,
                                   BreakOnlineHandle handle, NatPeer **out)
{
    NatPeer *peer;
    if (!break_online_handle_valid(handle) || handle.index >= coordinator->max_peers) {
        return BREAK_RUNTIME_INVALID;
    }
    peer = &coordinator->peers[handle.index];
    if (!peer->used || peer->generation != handle.generation) return BREAK_RUNTIME_STALE;
    *out = peer;
    return BREAK_RUNTIME_OK;
}

static BreakRuntimeError find_pair(const BreakNatCoordinator *coordinator,
                                   BreakOnlineHandle handle, NatPair **out)
{
    NatPair *pair;
    if (!break_online_handle_valid(handle) || handle.index >= coordinator->max_pairs) {
        return BREAK_RUNTIME_INVALID;
    }
    pair = &coordinator->pairs[handle.index];
    if (!pair->used || pair->generation != handle.generation) return BREAK_RUNTIME_STALE;
    *out = pair;
    return BREAK_RUNTIME_OK;
}

static BreakRuntimeError send_welcome(BreakNatCoordinator *coordinator,
                                      const NetAddress *to, u64 session,
                                      BreakOnlineHandle peer)
{
    u8 packet[NAT_WELCOME_SIZE];
    make_header(packet, NAT_WELCOME);
    put_u64(packet + 8u, session);
    put_handle(packet + 16u, peer);
    return send_datagram(coordinator->socket, to, packet, sizeof(packet));
}

static BreakRuntimeError coordinator_hello(BreakNatCoordinator *coordinator,
                                           const BreakOnlineDatagram *datagram)
{
    u64 session = get_u64(datagram->bytes + 8u);
    BreakOnlineIdentity identity;
    u32 i;
    NatPeer *peer = NULL;
    if (!session || !coordinator->auth.authenticate ||
        !coordinator->auth.authenticate(coordinator->auth.user, session, &identity) ||
        !identity.session_id || !identity.player_id) {
        return BREAK_RUNTIME_REJECTED;
    }
    for (i = 0u; i < coordinator->max_peers; ++i) {
        if (coordinator->peers[i].used && coordinator->peers[i].session == session) {
            BreakOnlineHandle handle = {i, coordinator->peers[i].generation};
            BreakRuntimeError result;
            if (coordinator->peers[i].paired &&
                !net_address_equal(&coordinator->peers[i].observed, &datagram->source)) {
                return BREAK_RUNTIME_REJECTED;
            }
            result = send_welcome(coordinator, &datagram->source, session, handle);
            if (result == BREAK_RUNTIME_OK) coordinator->peers[i].observed = datagram->source;
            return result;
        }
    }
    if (coordinator->peer_count == coordinator->max_peers) return BREAK_RUNTIME_OVERLOAD;
    for (i = 0u; i < coordinator->max_peers; ++i) {
        if (!coordinator->peers[i].used && coordinator->peers[i].generation != UINT32_MAX) {
            peer = &coordinator->peers[i];
            break;
        }
    }
    if (!peer) return BREAK_RUNTIME_OVERLOAD;
    {
        BreakOnlineHandle handle = {i, initial_generation(peer->generation)};
        BreakRuntimeError result = send_welcome(coordinator, &datagram->source,
                                                session, handle);
        if (result != BREAK_RUNTIME_OK) return result;
        memset(peer, 0, sizeof(*peer));
        peer->used = true;
        peer->generation = handle.generation;
        peer->session = session;
        peer->identity = identity;
        peer->observed = datagram->source;
        coordinator->peer_count++;
    }
    return BREAK_RUNTIME_OK;
}

static void retire_pair(BreakNatCoordinator *coordinator, NatPair *pair)
{
    coordinator->peers[pair->a].paired = false;
    coordinator->peers[pair->b].paired = false;
    pair->used = false;
    pair->generation = retire_generation(pair->generation);
    coordinator->pair_count--;
}

static BreakRuntimeError coordinator_ack(BreakNatCoordinator *coordinator,
                                         const BreakOnlineDatagram *datagram)
{
    BreakOnlineHandle handle = get_handle(datagram->bytes + 8u);
    u64 nonce = get_u64(datagram->bytes + 16u);
    NatPair *pair;
    BreakRuntimeError result = find_pair(coordinator, handle, &pair);
    if (result != BREAK_RUNTIME_OK || pair->nonce != nonce) return BREAK_RUNTIME_REJECTED;
    if (net_address_equal(&datagram->source, &coordinator->peers[pair->a].observed)) {
        pair->ack_mask |= 1u;
    } else if (net_address_equal(&datagram->source, &coordinator->peers[pair->b].observed)) {
        pair->ack_mask |= 2u;
    } else {
        return BREAK_RUNTIME_REJECTED;
    }
    return BREAK_RUNTIME_OK;
}

BreakRuntimeError break_nat_coordinator_create(
    NetSocket *socket, const BreakNatCoordinatorConfig *config,
    BreakNatCoordinator **out)
{
    BreakNatCoordinator *coordinator;
    BreakRuntimeError result;
    if (!out) return BREAK_RUNTIME_INVALID;
    *out = NULL;
    if (!socket || !config || !config->max_peers || !config->max_pairs ||
        config->max_peers > BREAK_NAT_HARD_MAX_PEERS ||
        config->max_pairs > BREAK_NAT_HARD_MAX_PAIRS ||
        !config->auth.authenticate || !config->clock) return BREAK_RUNTIME_INVALID;
    coordinator = (BreakNatCoordinator *)calloc(1u, sizeof(*coordinator));
    if (!coordinator) return BREAK_RUNTIME_OOM;
    coordinator->peers = (NatPeer *)calloc(config->max_peers, sizeof(*coordinator->peers));
    coordinator->pairs = (NatPair *)calloc(config->max_pairs, sizeof(*coordinator->pairs));
    if (!coordinator->peers || !coordinator->pairs) {
        free(coordinator->pairs);
        free(coordinator->peers);
        free(coordinator);
        return BREAK_RUNTIME_OOM;
    }
    result = break_online_inbox_create(config->queue_capacity, &coordinator->inbox);
    if (result != BREAK_RUNTIME_OK) {
        free(coordinator->pairs);
        free(coordinator->peers);
        free(coordinator);
        return result;
    }
    coordinator->owner = platform_thread_current_id();
    coordinator->socket = socket;
    coordinator->auth = config->auth;
    coordinator->clock = config->clock;
    coordinator->clock_user = config->clock_user;
    coordinator->max_peers = config->max_peers;
    coordinator->max_pairs = config->max_pairs;
    *out = coordinator;
    return BREAK_RUNTIME_OK;
}

void break_nat_coordinator_destroy(BreakNatCoordinator *coordinator)
{
    if (!coordinator_owner(coordinator)) return;
    break_online_inbox_destroy(coordinator->inbox);
    free(coordinator->pairs);
    free(coordinator->peers);
    free(coordinator);
}

BreakRuntimeError break_nat_coordinator_receive_socket(
    BreakNatCoordinator *coordinator, u32 max_datagrams)
{
    if (!coordinator) return BREAK_RUNTIME_INVALID;
    return receive_datagrams(coordinator->socket, coordinator->inbox, max_datagrams);
}

BreakRuntimeError break_nat_coordinator_poll(BreakNatCoordinator *coordinator,
                                             u32 max_messages)
{
    u32 i;
    u32 processed = 0u;
    if (!coordinator_owner(coordinator)) return BREAK_RUNTIME_REJECTED;
    for (i = 0u; i < coordinator->max_pairs; ++i) {
        NatPair *pair = &coordinator->pairs[i];
        if (pair->used && pair->ack_mask != 3u &&
            coordinator->clock(coordinator->clock_user) >= pair->expires_at) {
            retire_pair(coordinator, pair);
        }
    }
    while (processed < max_messages) {
        BreakOnlineDatagram datagram;
        BreakRuntimeError result;
        bool ready = false;
        result = break_online_inbox_poll(coordinator->inbox, &datagram, &ready);
        if (result != BREAK_RUNTIME_OK) return result;
        if (!ready) break;
        processed++;
        if (valid_header(&datagram, NAT_HELLO, NAT_HELLO_SIZE)) {
            result = coordinator_hello(coordinator, &datagram);
        } else if (valid_header(&datagram, NAT_ACK, NAT_ACK_SIZE)) {
            result = coordinator_ack(coordinator, &datagram);
        } else {
            coordinator->invalid_messages++;
            continue;
        }
        if (result != BREAK_RUNTIME_OK) coordinator->invalid_messages++;
    }
    return BREAK_RUNTIME_OK;
}

u32 break_nat_coordinator_peer_count(const BreakNatCoordinator *coordinator)
{
    return coordinator_owner(coordinator) ? coordinator->peer_count : 0u;
}

u64 break_nat_coordinator_invalid_messages(const BreakNatCoordinator *coordinator)
{
    return coordinator_owner(coordinator) ? coordinator->invalid_messages : 0u;
}

BreakRuntimeError break_nat_coordinator_peer_for_session(
    const BreakNatCoordinator *coordinator, u64 session, BreakOnlineHandle *out)
{
    u32 i;
    if (!coordinator_owner(coordinator)) return BREAK_RUNTIME_REJECTED;
    if (!session || !out) return BREAK_RUNTIME_INVALID;
    for (i = 0u; i < coordinator->max_peers; ++i) {
        if (coordinator->peers[i].used && coordinator->peers[i].session == session) {
            BreakOnlineHandle handle = {i, coordinator->peers[i].generation};
            *out = handle;
            return BREAK_RUNTIME_OK;
        }
    }
    return BREAK_RUNTIME_FAILED;
}

BreakRuntimeError break_nat_coordinator_peer_observed(
    const BreakNatCoordinator *coordinator, BreakOnlineHandle handle, NetAddress *out)
{
    NatPeer *peer;
    BreakRuntimeError result;
    if (!coordinator_owner(coordinator)) return BREAK_RUNTIME_REJECTED;
    if (!out) return BREAK_RUNTIME_INVALID;
    result = find_peer(coordinator, handle, &peer);
    if (result == BREAK_RUNTIME_OK) *out = peer->observed;
    return result;
}

static BreakRuntimeError send_punch(BreakNatCoordinator *coordinator,
                                    const NetAddress *to, BreakOnlineHandle pair,
                                    u64 nonce, u64 expires_at,
                                    const NetAddress *peer_address)
{
    u8 packet[NAT_PUNCH_SIZE];
    usize host_size = strlen(peer_address->host);
    if (!host_size || host_size >= NAT_HOST_SIZE || !peer_address->port) {
        return BREAK_RUNTIME_INVALID;
    }
    memset(packet, 0, sizeof(packet));
    make_header(packet, NAT_PUNCH);
    put_handle(packet + 8u, pair);
    put_u64(packet + 16u, nonce);
    put_u64(packet + 24u, expires_at);
    memcpy(packet + 32u, peer_address->host, host_size);
    put_u16(packet + 48u, peer_address->port);
    return send_datagram(coordinator->socket, to, packet, sizeof(packet));
}

BreakRuntimeError break_nat_coordinator_pair(
    BreakNatCoordinator *coordinator, BreakOnlineHandle a, BreakOnlineHandle b,
    u64 nonce, u32 ttl_ms, BreakOnlineHandle *out_pair)
{
    NatPeer *a_peer;
    NatPeer *b_peer;
    NatPair *pair = NULL;
    BreakRuntimeError result;
    BreakOnlineHandle handle;
    u64 now;
    u64 expires_at;
    u32 i;
    if (!coordinator_owner(coordinator)) return BREAK_RUNTIME_REJECTED;
    if (!out_pair || !nonce || !ttl_ms) return BREAK_RUNTIME_INVALID;
    result = find_peer(coordinator, a, &a_peer);
    if (result != BREAK_RUNTIME_OK) return result;
    result = find_peer(coordinator, b, &b_peer);
    if (result != BREAK_RUNTIME_OK) return result;
    if (a.index == b.index || a_peer->paired || b_peer->paired) {
        return BREAK_RUNTIME_REJECTED;
    }
    if (coordinator->pair_count == coordinator->max_pairs) return BREAK_RUNTIME_OVERLOAD;
    for (i = 0u; i < coordinator->max_pairs; ++i) {
        if (!coordinator->pairs[i].used && coordinator->pairs[i].generation != UINT32_MAX) {
            pair = &coordinator->pairs[i];
            break;
        }
    }
    if (!pair) return BREAK_RUNTIME_OVERLOAD;
    now = coordinator->clock(coordinator->clock_user);
    if (now > UINT64_MAX - ttl_ms) return BREAK_RUNTIME_INVALID;
    expires_at = now + ttl_ms;
    handle.index = i;
    handle.generation = initial_generation(pair->generation);
    result = send_punch(coordinator, &a_peer->observed, handle, nonce, expires_at,
                        &b_peer->observed);
    if (result != BREAK_RUNTIME_OK) return result;
    result = send_punch(coordinator, &b_peer->observed, handle, nonce, expires_at,
                        &a_peer->observed);
    if (result != BREAK_RUNTIME_OK) return result;
    memset(pair, 0, sizeof(*pair));
    pair->used = true;
    pair->generation = handle.generation;
    pair->a = a.index;
    pair->b = b.index;
    pair->nonce = nonce;
    pair->expires_at = expires_at;
    a_peer->paired = true;
    b_peer->paired = true;
    coordinator->pair_count++;
    *out_pair = handle;
    return BREAK_RUNTIME_OK;
}

BreakRuntimeError break_nat_coordinator_pair_close(
    BreakNatCoordinator *coordinator, BreakOnlineHandle handle)
{
    NatPair *pair;
    BreakRuntimeError result;
    if (!coordinator_owner(coordinator)) return BREAK_RUNTIME_REJECTED;
    result = find_pair(coordinator, handle, &pair);
    if (result != BREAK_RUNTIME_OK) return result;
    retire_pair(coordinator, pair);
    return BREAK_RUNTIME_OK;
}

BreakRuntimeError break_nat_coordinator_pair_ack_mask(
    const BreakNatCoordinator *coordinator, BreakOnlineHandle handle, u32 *out)
{
    NatPair *pair;
    BreakRuntimeError result;
    if (!coordinator_owner(coordinator)) return BREAK_RUNTIME_REJECTED;
    if (!out) return BREAK_RUNTIME_INVALID;
    result = find_pair(coordinator, handle, &pair);
    if (result == BREAK_RUNTIME_OK) *out = pair->ack_mask;
    return result;
}

BreakRuntimeError break_nat_endpoint_create(
    NetSocket *socket, const NetAddress *coordinator,
    const BreakNatEndpointConfig *config, BreakNatEndpoint **out)
{
    BreakNatEndpoint *endpoint;
    BreakRuntimeError result;
    if (!out) return BREAK_RUNTIME_INVALID;
    *out = NULL;
    if (!socket || !coordinator || !coordinator->port || !config ||
        !config->session || !config->clock) return BREAK_RUNTIME_INVALID;
    endpoint = (BreakNatEndpoint *)calloc(1u, sizeof(*endpoint));
    if (!endpoint) return BREAK_RUNTIME_OOM;
    result = break_online_inbox_create(config->queue_capacity, &endpoint->inbox);
    if (result != BREAK_RUNTIME_OK) {
        free(endpoint);
        return result;
    }
    endpoint->owner = platform_thread_current_id();
    endpoint->socket = socket;
    endpoint->coordinator = *coordinator;
    endpoint->session = config->session;
    endpoint->clock = config->clock;
    endpoint->clock_user = config->clock_user;
    *out = endpoint;
    return BREAK_RUNTIME_OK;
}

void break_nat_endpoint_destroy(BreakNatEndpoint *endpoint)
{
    if (!endpoint_owner(endpoint)) return;
    break_online_inbox_destroy(endpoint->inbox);
    free(endpoint);
}

BreakRuntimeError break_nat_peer_hello(BreakNatEndpoint *endpoint)
{
    u8 packet[NAT_HELLO_SIZE];
    if (!endpoint_owner(endpoint)) return BREAK_RUNTIME_REJECTED;
    make_header(packet, NAT_HELLO);
    put_u64(packet + 8u, endpoint->session);
    return send_datagram(endpoint->socket, &endpoint->coordinator,
                         packet, sizeof(packet));
}

BreakRuntimeError break_nat_endpoint_receive_socket(BreakNatEndpoint *endpoint,
                                                    u32 max_datagrams)
{
    if (!endpoint) return BREAK_RUNTIME_INVALID;
    return receive_datagrams(endpoint->socket, endpoint->inbox, max_datagrams);
}

static bool decode_address(const u8 *packet, NetAddress *out)
{
    usize size = 0u;
    usize i;
    while (size < NAT_HOST_SIZE && packet[size]) {
        u8 c = packet[size];
        if ((c < '0' || c > '9') && c != '.') return false;
        ++size;
    }
    if (!size || size == NAT_HOST_SIZE) return false;
    memset(out, 0, sizeof(*out));
    for (i = 0u; i < size; ++i) out->host[i] = (char)packet[i];
    out->port = get_u16(packet + NAT_HOST_SIZE);
    return out->port != 0u;
}

static BreakRuntimeError endpoint_welcome(BreakNatEndpoint *endpoint,
                                          const BreakOnlineDatagram *datagram)
{
    BreakOnlineHandle peer = get_handle(datagram->bytes + 16u);
    if (!net_address_equal(&datagram->source, &endpoint->coordinator) ||
        get_u64(datagram->bytes + 8u) != endpoint->session ||
        !break_online_handle_valid(peer)) return BREAK_RUNTIME_REJECTED;
    if (endpoint->registered &&
        (endpoint->peer.index != peer.index || endpoint->peer.generation != peer.generation)) {
        return BREAK_RUNTIME_REJECTED;
    }
    endpoint->registered = true;
    endpoint->peer = peer;
    return BREAK_RUNTIME_OK;
}

static BreakRuntimeError endpoint_punch(BreakNatEndpoint *endpoint,
                                        const BreakOnlineDatagram *datagram)
{
    BreakOnlineHandle pair = get_handle(datagram->bytes + 8u);
    u64 nonce = get_u64(datagram->bytes + 16u);
    u64 expires_at = get_u64(datagram->bytes + 24u);
    NetAddress peer_address;
    BreakRuntimeError result;
    if (!net_address_equal(&datagram->source, &endpoint->coordinator) ||
        !break_online_handle_valid(pair) || !nonce ||
        endpoint->clock(endpoint->clock_user) >= expires_at ||
        !decode_address(datagram->bytes + 32u, &peer_address)) {
        return BREAK_RUNTIME_REJECTED;
    }
    if (endpoint->active &&
        (endpoint->pair.index != pair.index || endpoint->pair.generation != pair.generation)) {
        return BREAK_RUNTIME_REJECTED;
    }
    {
        u8 packet[NAT_PING_SIZE];
        make_header(packet, NAT_PING);
        put_handle(packet + 8u, pair);
        put_u64(packet + 16u, nonce);
        result = send_datagram(endpoint->socket, &peer_address, packet, sizeof(packet));
    }
    if (result != BREAK_RUNTIME_OK) return result;
    endpoint->active = true;
    endpoint->connected = false;
    endpoint->ping_sent = true;
    endpoint->pair = pair;
    endpoint->peer_address = peer_address;
    endpoint->nonce = nonce;
    endpoint->expires_at = expires_at;
    return BREAK_RUNTIME_OK;
}

static BreakRuntimeError endpoint_ping(BreakNatEndpoint *endpoint,
                                       const BreakOnlineDatagram *datagram)
{
    BreakOnlineHandle pair = get_handle(datagram->bytes + 8u);
    u64 nonce = get_u64(datagram->bytes + 16u);
    BreakRuntimeError result;
    u8 ack[NAT_ACK_SIZE];
    if (!endpoint->active || endpoint->pair.index != pair.index ||
        endpoint->pair.generation != pair.generation || endpoint->nonce != nonce ||
        !net_address_equal(&datagram->source, &endpoint->peer_address)) {
        return BREAK_RUNTIME_REJECTED;
    }
    if (!endpoint->connected && endpoint->clock(endpoint->clock_user) >= endpoint->expires_at) {
        return BREAK_RUNTIME_REJECTED;
    }
    if (endpoint->connected) return BREAK_RUNTIME_OK;
    if (!endpoint->ping_sent) {
        u8 ping[NAT_PING_SIZE];
        make_header(ping, NAT_PING);
        put_handle(ping + 8u, pair);
        put_u64(ping + 16u, nonce);
        result = send_datagram(endpoint->socket, &endpoint->peer_address,
                               ping, sizeof(ping));
        if (result != BREAK_RUNTIME_OK) return result;
        endpoint->ping_sent = true;
    }
    make_header(ack, NAT_ACK);
    put_handle(ack + 8u, pair);
    put_u64(ack + 16u, nonce);
    result = send_datagram(endpoint->socket, &endpoint->coordinator, ack, sizeof(ack));
    if (result != BREAK_RUNTIME_OK) return result;
    endpoint->connected = true;
    return BREAK_RUNTIME_OK;
}

BreakRuntimeError break_nat_endpoint_poll(BreakNatEndpoint *endpoint,
                                          u32 max_messages)
{
    u32 processed = 0u;
    if (!endpoint_owner(endpoint)) return BREAK_RUNTIME_REJECTED;
    if (endpoint->active && !endpoint->connected &&
        endpoint->clock(endpoint->clock_user) >= endpoint->expires_at) {
        endpoint->active = false;
        endpoint->ping_sent = false;
    }
    while (processed < max_messages) {
        BreakOnlineDatagram datagram;
        bool ready = false;
        BreakRuntimeError result = break_online_inbox_poll(endpoint->inbox,
                                                            &datagram, &ready);
        if (result != BREAK_RUNTIME_OK) return result;
        if (!ready) break;
        processed++;
        if (valid_header(&datagram, NAT_WELCOME, NAT_WELCOME_SIZE)) {
            result = endpoint_welcome(endpoint, &datagram);
        } else if (valid_header(&datagram, NAT_PUNCH, NAT_PUNCH_SIZE)) {
            result = endpoint_punch(endpoint, &datagram);
        } else if (valid_header(&datagram, NAT_PING, NAT_PING_SIZE)) {
            result = endpoint_ping(endpoint, &datagram);
        } else {
            continue;
        }
        if (result != BREAK_RUNTIME_OK && result != BREAK_RUNTIME_REJECTED) return result;
    }
    return BREAK_RUNTIME_OK;
}

bool break_nat_endpoint_registered(const BreakNatEndpoint *endpoint)
{
    return endpoint_owner(endpoint) && endpoint->registered;
}

bool break_nat_endpoint_armed(const BreakNatEndpoint *endpoint,
                              BreakOnlineHandle pair)
{
    return endpoint_owner(endpoint) && endpoint->active &&
           endpoint->pair.index == pair.index &&
           endpoint->pair.generation == pair.generation;
}

bool break_nat_endpoint_connected(const BreakNatEndpoint *endpoint,
                                  BreakOnlineHandle pair)
{
    return endpoint_owner(endpoint) && endpoint->active && endpoint->connected &&
           endpoint->pair.index == pair.index &&
           endpoint->pair.generation == pair.generation;
}
