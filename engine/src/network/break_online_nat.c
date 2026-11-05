#include <network/break_online_nat.h>

#include <network/break_online_inbox.h>
#include <network/break_replay_window.h>
#include <core/platform_thread.h>
#ifdef BREAK_ENABLE_CRYPTO
#include <crypto/break_crypto.h>
#endif

#include <stdlib.h>
#include <string.h>

#define NAT_DISCOVER_SIZE 16u
#define NAT_CHALLENGE_SIZE 32u
#define NAT_HELLO_SIZE 72u
#define NAT_WELCOME_SIZE 56u
#define NAT_PUNCH_SIZE 106u
#define NAT_PING_SIZE 24u
#define NAT_ACK_SIZE 72u
#define NAT_HOST_SIZE 16u
#define NAT_CHALLENGE_TTL_MS 10000u

typedef enum NatMessageKind {
    NAT_HELLO = 1,
    NAT_WELCOME = 2,
    NAT_PUNCH = 3,
    NAT_PING = 4,
    NAT_ACK = 5,
    NAT_DISCOVER = 6,
    NAT_CHALLENGE = 7,
    NAT_CLOSE = 8
} NatMessageKind;

typedef struct NatPeer {
    bool used;
    bool paired;
    u32 generation;
    u64 session;
    BreakOnlineIdentity identity;
    NetAddress observed;
    BreakReplayWindow hello_window;
    u64 hello_challenge;
    u64 hello_sequence;
    u8 hello_tag[32];
    NetAddress hello_source;
    u64 next_control_sequence;
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
    u8 challenge_key[32];
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
    BreakOnlineSessionKeyFn session_key;
    void *session_key_user;
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
    u64 punch_ttl;
    u64 punch_sequence;
    bool closed_pair_valid;
    BreakOnlineHandle closed_pair;
    u64 closed_sequence;
    u64 control_high_water;
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

static void nat_wipe(void *data, usize size)
{
    volatile u8 *bytes = (volatile u8 *)data;
    while (size-- != 0u) *bytes++ = 0u;
}

static bool nat_mac(BreakOnlineSessionKeyFn key_fn, void *key_user, u64 session,
                    const u8 *data, usize size, u8 out[32])
{
#ifdef BREAK_ENABLE_CRYPTO
    u8 key[32];
    bool ok;
    if (!key_fn) return false;
    ok = key_fn(key_user, session, key) &&
         break_crypto_hmac_sha256(key, sizeof(key), data, size, out);
    nat_wipe(key, sizeof(key));
    return ok;
#else
    (void)key_fn; (void)key_user; (void)session; (void)data; (void)size; (void)out;
    return false;
#endif
}

static bool nat_mac_key(const u8 key[32], const u8 *data, usize size, u8 out[32])
{
#ifdef BREAK_ENABLE_CRYPTO
    return break_crypto_hmac_sha256(key, 32u, data, size, out);
#else
    (void)key; (void)data; (void)size; (void)out;
    return false;
#endif
}

static bool nat_challenge_nonce(const BreakNatCoordinator *coordinator,
                                u64 session, const NetAddress *source,
                                u64 expires_at, u8 out[8])
{
    u8 material[34];
    u8 tag[32];
    usize host_size = strlen(source->host);
    bool ok;
    if (!host_size || host_size >= NAT_HOST_SIZE || !source->port) return false;
    memset(material, 0, sizeof(material));
    put_u64(material, session);
    memcpy(material + 8u, source->host, host_size);
    put_u16(material + 24u, source->port);
    put_u64(material + 26u, expires_at);
    ok = nat_mac_key(coordinator->challenge_key, material, sizeof(material), tag);
    if (ok) memcpy(out, tag, 8u);
    nat_wipe(tag, sizeof(tag));
    return ok && get_u64(out) != 0u;
}

static bool nat_tag_equal(const u8 left[32], const u8 right[32])
{
    u8 difference = 0u;
    u32 i;
    for (i = 0u; i < 32u; ++i) difference |= (u8)(left[i] ^ right[i]);
    return difference == 0u;
}

static bool nat_verify(BreakOnlineSessionKeyFn key_fn, void *key_user, u64 session,
                       const u8 *packet, usize tag_offset)
{
    u8 expected[32];
    bool ok = nat_mac(key_fn, key_user, session, packet, tag_offset, expected) &&
              nat_tag_equal(expected, packet + tag_offset);
    nat_wipe(expected, sizeof(expected));
    return ok;
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
    if (!nat_mac(coordinator->auth.session_key, coordinator->auth.user, session,
                 packet, 24u, packet + 24u)) return BREAK_RUNTIME_FAILED;
    return send_datagram(coordinator->socket, to, packet, sizeof(packet));
}

static BreakRuntimeError coordinator_discover(BreakNatCoordinator *coordinator,
                                              const BreakOnlineDatagram *datagram)
{
    u64 session = get_u64(datagram->bytes + 8u);
    u64 now;
    u64 expires_at;
    u64 nonce;
    u8 packet[NAT_CHALLENGE_SIZE];
    if (!session) return BREAK_RUNTIME_REJECTED;
    now = coordinator->clock(coordinator->clock_user);
    if (now > UINT64_MAX - NAT_CHALLENGE_TTL_MS) return BREAK_RUNTIME_FAILED;
    expires_at = (now / NAT_CHALLENGE_TTL_MS) * NAT_CHALLENGE_TTL_MS +
                 NAT_CHALLENGE_TTL_MS;
    if (!nat_challenge_nonce(coordinator, session, &datagram->source,
                             expires_at, (u8 *)&nonce)) return BREAK_RUNTIME_FAILED;
    make_header(packet, NAT_CHALLENGE);
    put_u64(packet + 8u, session);
    put_u64(packet + 16u, nonce);
    put_u64(packet + 24u, expires_at);
    return send_datagram(coordinator->socket, &datagram->source,
                         packet, sizeof(packet));
}

static bool exact_hello_duplicate(const NatPeer *peer,
                                  const BreakOnlineDatagram *datagram,
                                  u64 challenge, u64 sequence)
{
    return peer->hello_challenge == challenge && peer->hello_sequence == sequence &&
           net_address_equal(&peer->hello_source, &datagram->source) &&
           memcmp(peer->hello_tag, datagram->bytes + 40u, 32u) == 0;
}

static BreakRuntimeError coordinator_hello(BreakNatCoordinator *coordinator,
                                           const BreakOnlineDatagram *datagram)
{
    u64 session = get_u64(datagram->bytes + 8u);
    u64 challenge_nonce = get_u64(datagram->bytes + 16u);
    u64 expires_at = get_u64(datagram->bytes + 24u);
    u64 sequence = get_u64(datagram->bytes + 32u);
    BreakOnlineIdentity identity;
    NatPeer *peer = NULL;
    BreakReplayWindow window;
    u8 expected_nonce[8];
    u32 i;
    bool new_challenge;
    if (!session || !challenge_nonce || !expires_at || !sequence ||
        coordinator->clock(coordinator->clock_user) >= expires_at ||
        !nat_challenge_nonce(coordinator, session, &datagram->source,
                             expires_at, expected_nonce) ||
        memcmp(expected_nonce, &challenge_nonce, sizeof(expected_nonce)) != 0 ||
        !coordinator->auth.authenticate(coordinator->auth.user, session, &identity) ||
        !identity.session_id || !identity.player_id ||
        !nat_verify(coordinator->auth.session_key, coordinator->auth.user, session,
                    datagram->bytes, 40u)) {
        return BREAK_RUNTIME_REJECTED;
    }
    for (i = 0u; i < coordinator->max_peers; ++i) {
        if (coordinator->peers[i].used && coordinator->peers[i].session == session) {
            peer = &coordinator->peers[i];
            break;
        }
    }
    if (peer && exact_hello_duplicate(peer, datagram, challenge_nonce, sequence)) {
        BreakOnlineHandle handle = {i, peer->generation};
        return send_welcome(coordinator, &datagram->source, session, handle);
    }
    if (peer && peer->paired && !net_address_equal(&peer->observed, &datagram->source)) {
        return BREAK_RUNTIME_REJECTED;
    }
    new_challenge = !peer || peer->hello_challenge != challenge_nonce;
    if (new_challenge) {
        break_replay_window_init(&window);
    } else {
        window = peer->hello_window;
    }
    if (break_replay_window_check(&window, sequence) != BREAK_REPLAY_OK) {
        return BREAK_RUNTIME_REJECTED;
    }
    if (!peer) {
        if (coordinator->peer_count == coordinator->max_peers) return BREAK_RUNTIME_OVERLOAD;
        for (i = 0u; i < coordinator->max_peers; ++i) {
            if (!coordinator->peers[i].used && coordinator->peers[i].generation != UINT32_MAX) {
                peer = &coordinator->peers[i];
                break;
            }
        }
        if (!peer) return BREAK_RUNTIME_OVERLOAD;
    }
    {
        BreakOnlineHandle handle = {
            (u32)(peer - coordinator->peers), initial_generation(peer->generation)};
        BreakRuntimeError result = send_welcome(coordinator, &datagram->source,
                                                session, handle);
        if (result != BREAK_RUNTIME_OK) return result;
        if (break_replay_window_check_and_mark(&window, sequence) != BREAK_REPLAY_OK) {
            return BREAK_RUNTIME_REJECTED;
        }
        if (peer->used) {
            peer->observed = datagram->source;
        } else {
            memset(peer, 0, sizeof(*peer));
            peer->used = true;
            peer->generation = handle.generation;
            peer->session = session;
            peer->identity = identity;
            peer->observed = datagram->source;
            peer->next_control_sequence = 1u;
            coordinator->peer_count++;
        }
        peer->hello_window = window;
        peer->hello_challenge = challenge_nonce;
        peer->hello_sequence = sequence;
        peer->hello_source = datagram->source;
        memcpy(peer->hello_tag, datagram->bytes + 40u, 32u);
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
    u64 session = get_u64(datagram->bytes + 16u);
    NatPair *pair;
    BreakRuntimeError result = find_pair(coordinator, handle, &pair);
    u32 peer_index;
    if (result != BREAK_RUNTIME_OK) return BREAK_RUNTIME_REJECTED;
    peer_index = coordinator->peers[pair->a].session == session ? pair->a : pair->b;
    if (coordinator->peers[peer_index].session != session ||
        !nat_verify(coordinator->auth.session_key, coordinator->auth.user, session,
                    datagram->bytes, 40u)) {
        return BREAK_RUNTIME_REJECTED;
    }
    if (net_address_equal(&datagram->source, &coordinator->peers[pair->a].observed) &&
        pair->a == peer_index) {
        pair->ack_mask |= 1u;
    } else if (net_address_equal(&datagram->source, &coordinator->peers[pair->b].observed) &&
               pair->b == peer_index) {
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
    u32 i;
    bool key_nonzero = false;
    if (!out) return BREAK_RUNTIME_INVALID;
    *out = NULL;
    if (!socket || !config || !config->max_peers || !config->max_pairs ||
        config->max_peers > BREAK_NAT_HARD_MAX_PEERS ||
        config->max_pairs > BREAK_NAT_HARD_MAX_PAIRS ||
        !config->auth.authenticate || !config->auth.session_key || !config->clock) {
        return BREAK_RUNTIME_INVALID;
    }
    for (i = 0u; i < 32u; ++i) {
        if (config->challenge_key[i] != 0u) key_nonzero = true;
    }
    if (!key_nonzero) return BREAK_RUNTIME_INVALID;
#ifndef BREAK_ENABLE_CRYPTO
    return BREAK_RUNTIME_REJECTED;
#else
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
    memcpy(coordinator->challenge_key, config->challenge_key,
           sizeof(coordinator->challenge_key));
    *out = coordinator;
    return BREAK_RUNTIME_OK;
#endif
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

static BreakRuntimeError send_close(BreakNatCoordinator *coordinator,
                                    NatPeer *recipient, BreakOnlineHandle pair);

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
            BreakRuntimeError close_result = send_close(
                coordinator, &coordinator->peers[pair->a],
                (BreakOnlineHandle){i, pair->generation});
            if (close_result != BREAK_RUNTIME_OK) return close_result;
            close_result = send_close(coordinator, &coordinator->peers[pair->b],
                (BreakOnlineHandle){i, pair->generation});
            if (close_result != BREAK_RUNTIME_OK) return close_result;
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
        if (valid_header(&datagram, NAT_DISCOVER, NAT_DISCOVER_SIZE)) {
            result = coordinator_discover(coordinator, &datagram);
        } else if (valid_header(&datagram, NAT_HELLO, NAT_HELLO_SIZE)) {
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
                                    NatPeer *recipient, const NetAddress *to,
                                    BreakOnlineHandle pair, u64 nonce, u64 ttl_ms,
                                    const NetAddress *peer_address)
{
    u8 packet[NAT_PUNCH_SIZE];
    usize host_size = strlen(peer_address->host);
    BreakRuntimeError result;
    if (!host_size || host_size >= NAT_HOST_SIZE || !peer_address->port ||
        !recipient->next_control_sequence) return BREAK_RUNTIME_INVALID;
    memset(packet, 0, sizeof(packet));
    make_header(packet, NAT_PUNCH);
    put_handle(packet + 8u, pair);
    {
        BreakOnlineHandle recipient_handle = {
            (u32)(recipient - coordinator->peers), recipient->generation};
        put_handle(packet + 16u, recipient_handle);
    }
    put_u64(packet + 24u, recipient->session);
    put_u64(packet + 32u, nonce);
    put_u64(packet + 40u, ttl_ms);
    put_u64(packet + 48u, recipient->next_control_sequence);
    memcpy(packet + 56u, peer_address->host, host_size);
    put_u16(packet + 72u, peer_address->port);
    if (!nat_mac(coordinator->auth.session_key, coordinator->auth.user,
                 recipient->session, packet, 74u, packet + 74u)) {
        return BREAK_RUNTIME_FAILED;
    }
    result = send_datagram(coordinator->socket, to, packet, sizeof(packet));
    if (result == BREAK_RUNTIME_OK) recipient->next_control_sequence++;
    return result;
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
    result = send_punch(coordinator, a_peer, &a_peer->observed, handle, nonce, (u64)ttl_ms,
                        &b_peer->observed);
    if (result != BREAK_RUNTIME_OK) return result;
    result = send_punch(coordinator, b_peer, &b_peer->observed, handle, nonce, (u64)ttl_ms,
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

static BreakRuntimeError send_close(BreakNatCoordinator *coordinator,
                                    NatPeer *recipient, BreakOnlineHandle pair)
{
    u8 packet[NAT_ACK_SIZE];
    BreakRuntimeError result;
    if (!recipient->next_control_sequence) return BREAK_RUNTIME_INVALID;
    make_header(packet, NAT_CLOSE);
    put_handle(packet + 8u, pair);
    {
        BreakOnlineHandle recipient_handle = {
            (u32)(recipient - coordinator->peers), recipient->generation};
        put_handle(packet + 16u, recipient_handle);
    }
    put_u64(packet + 24u, recipient->session);
    put_u64(packet + 32u, recipient->next_control_sequence);
    if (!nat_mac(coordinator->auth.session_key, coordinator->auth.user,
                 recipient->session, packet, 40u, packet + 40u)) {
        return BREAK_RUNTIME_FAILED;
    }
    result = send_datagram(coordinator->socket, &recipient->observed,
                           packet, sizeof(packet));
    if (result == BREAK_RUNTIME_OK) recipient->next_control_sequence++;
    return result;
}

BreakRuntimeError break_nat_coordinator_pair_close(
    BreakNatCoordinator *coordinator, BreakOnlineHandle handle)
{
    NatPair *pair;
    BreakRuntimeError result;
    if (!coordinator_owner(coordinator)) return BREAK_RUNTIME_REJECTED;
    result = find_pair(coordinator, handle, &pair);
    if (result != BREAK_RUNTIME_OK) return result;
    result = send_close(coordinator, &coordinator->peers[pair->a], handle);
    if (result != BREAK_RUNTIME_OK) return result;
    result = send_close(coordinator, &coordinator->peers[pair->b], handle);
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
        !config->session || !config->session_key || !config->clock) {
        return BREAK_RUNTIME_INVALID;
    }
#ifndef BREAK_ENABLE_CRYPTO
    return BREAK_RUNTIME_REJECTED;
#else
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
    endpoint->session_key = config->session_key;
    endpoint->session_key_user = config->session_key_user;
    endpoint->clock = config->clock;
    endpoint->clock_user = config->clock_user;
    *out = endpoint;
    return BREAK_RUNTIME_OK;
#endif
}

void break_nat_endpoint_destroy(BreakNatEndpoint *endpoint)
{
    if (!endpoint_owner(endpoint)) return;
    break_online_inbox_destroy(endpoint->inbox);
    free(endpoint);
}

BreakRuntimeError break_nat_peer_hello(BreakNatEndpoint *endpoint)
{
    u8 packet[NAT_DISCOVER_SIZE];
    if (!endpoint_owner(endpoint)) return BREAK_RUNTIME_REJECTED;
    if (endpoint->registered) return BREAK_RUNTIME_OK;
    make_header(packet, NAT_DISCOVER);
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

static BreakRuntimeError endpoint_challenge(BreakNatEndpoint *endpoint,
                                            const BreakOnlineDatagram *datagram)
{
    u8 packet[NAT_HELLO_SIZE];
    BreakRuntimeError result;
    u64 expires_at = get_u64(datagram->bytes + 24u);
    if (endpoint->registered ||
        !net_address_equal(&datagram->source, &endpoint->coordinator) ||
        get_u64(datagram->bytes + 8u) != endpoint->session || !expires_at) {
        return BREAK_RUNTIME_REJECTED;
    }
    make_header(packet, NAT_HELLO);
    put_u64(packet + 8u, endpoint->session);
    memcpy(packet + 16u, datagram->bytes + 16u, 16u);
    put_u64(packet + 32u, 1u);
    if (!nat_mac(endpoint->session_key, endpoint->session_key_user, endpoint->session,
                 packet, 40u, packet + 40u)) return BREAK_RUNTIME_FAILED;
    result = send_datagram(endpoint->socket, &endpoint->coordinator,
                           packet, sizeof(packet));
    return result;
}

static BreakRuntimeError endpoint_welcome(BreakNatEndpoint *endpoint,
                                          const BreakOnlineDatagram *datagram)
{
    BreakOnlineHandle peer = get_handle(datagram->bytes + 16u);
    if (!net_address_equal(&datagram->source, &endpoint->coordinator) ||
        get_u64(datagram->bytes + 8u) != endpoint->session ||
        !break_online_handle_valid(peer) ||
        !nat_verify(endpoint->session_key, endpoint->session_key_user,
                    endpoint->session, datagram->bytes, 24u)) {
        return BREAK_RUNTIME_REJECTED;
    }
    if (endpoint->registered) {
        if (endpoint->peer.index == peer.index && endpoint->peer.generation == peer.generation) {
            return BREAK_RUNTIME_OK;
        }
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
    BreakOnlineHandle recipient = get_handle(datagram->bytes + 16u);
    u64 session = get_u64(datagram->bytes + 24u);
    u64 nonce = get_u64(datagram->bytes + 32u);
    u64 ttl_ms = get_u64(datagram->bytes + 40u);
    u64 sequence = get_u64(datagram->bytes + 48u);
    NetAddress peer_address;
    BreakRuntimeError result;
    u64 now = endpoint->clock(endpoint->clock_user);
    if (!endpoint->registered || session != endpoint->session ||
        recipient.index != endpoint->peer.index ||
        recipient.generation != endpoint->peer.generation ||
        !net_address_equal(&datagram->source, &endpoint->coordinator) ||
        !break_online_handle_valid(pair) || !nonce || !sequence || !ttl_ms ||
        now > UINT64_MAX - ttl_ms ||
        !decode_address(datagram->bytes + 56u, &peer_address) ||
        !nat_verify(endpoint->session_key, endpoint->session_key_user,
                    endpoint->session, datagram->bytes, 74u)) {
        return BREAK_RUNTIME_REJECTED;
    }
    if (endpoint->active && endpoint->pair.index == pair.index &&
        endpoint->pair.generation == pair.generation) {
        if (endpoint->nonce == nonce && endpoint->punch_ttl == ttl_ms &&
            endpoint->punch_sequence == sequence &&
            net_address_equal(&endpoint->peer_address, &peer_address)) {
            return BREAK_RUNTIME_OK;
        }
        return BREAK_RUNTIME_REJECTED;
    }
    if (endpoint->active) return BREAK_RUNTIME_REJECTED;
    if (sequence <= endpoint->control_high_water) return BREAK_RUNTIME_REJECTED;
    if (endpoint->closed_pair_valid && endpoint->closed_pair.index == pair.index &&
        endpoint->closed_pair.generation == pair.generation &&
        sequence <= endpoint->closed_sequence) {
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
    endpoint->closed_pair_valid = false;
    endpoint->active = true;
    endpoint->connected = false;
    endpoint->ping_sent = true;
    endpoint->pair = pair;
    endpoint->peer_address = peer_address;
    endpoint->nonce = nonce;
    endpoint->punch_ttl = ttl_ms;
    endpoint->expires_at = now + ttl_ms;
    endpoint->punch_sequence = sequence;
    endpoint->control_high_water = sequence;
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
    put_u64(ack + 16u, endpoint->session);
    put_u64(ack + 24u, 1u);
    memset(ack + 32u, 0, 8u);
    if (!nat_mac(endpoint->session_key, endpoint->session_key_user, endpoint->session,
                 ack, 40u, ack + 40u)) return BREAK_RUNTIME_FAILED;
    result = send_datagram(endpoint->socket, &endpoint->coordinator, ack, sizeof(ack));
    if (result != BREAK_RUNTIME_OK) return result;
    endpoint->connected = true;
    return BREAK_RUNTIME_OK;
}

static BreakRuntimeError endpoint_close(BreakNatEndpoint *endpoint,
                                        const BreakOnlineDatagram *datagram)
{
    BreakOnlineHandle pair = get_handle(datagram->bytes + 8u);
    BreakOnlineHandle recipient = get_handle(datagram->bytes + 16u);
    u64 session = get_u64(datagram->bytes + 24u);
    u64 sequence = get_u64(datagram->bytes + 32u);
    if (!endpoint->registered || session != endpoint->session ||
        recipient.index != endpoint->peer.index ||
        recipient.generation != endpoint->peer.generation ||
        !net_address_equal(&datagram->source, &endpoint->coordinator) ||
        !break_online_handle_valid(pair) || !sequence ||
        !nat_verify(endpoint->session_key, endpoint->session_key_user,
                    endpoint->session, datagram->bytes, 40u)) {
        return BREAK_RUNTIME_REJECTED;
    }
    if (endpoint->closed_pair_valid && endpoint->closed_pair.index == pair.index &&
        endpoint->closed_pair.generation == pair.generation &&
        sequence == endpoint->closed_sequence) {
        return BREAK_RUNTIME_OK;
    }
    if (sequence <= endpoint->control_high_water) return BREAK_RUNTIME_REJECTED;
    if (endpoint->active &&
        (endpoint->pair.index != pair.index || endpoint->pair.generation != pair.generation)) {
        return BREAK_RUNTIME_REJECTED;
    }
    if (endpoint->active && sequence <= endpoint->punch_sequence) {
        return BREAK_RUNTIME_REJECTED;
    }
    endpoint->active = false;
    endpoint->connected = false;
    endpoint->ping_sent = false;
    endpoint->nonce = 0u;
    endpoint->expires_at = 0u;
    endpoint->punch_ttl = 0u;
    endpoint->punch_sequence = 0u;
    memset(&endpoint->peer_address, 0, sizeof(endpoint->peer_address));
    endpoint->closed_pair_valid = true;
    endpoint->closed_pair = pair;
    endpoint->closed_sequence = sequence;
    endpoint->control_high_water = sequence;
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
        if (valid_header(&datagram, NAT_CHALLENGE, NAT_CHALLENGE_SIZE)) {
            result = endpoint_challenge(endpoint, &datagram);
        } else if (valid_header(&datagram, NAT_WELCOME, NAT_WELCOME_SIZE)) {
            result = endpoint_welcome(endpoint, &datagram);
        } else if (valid_header(&datagram, NAT_PUNCH, NAT_PUNCH_SIZE)) {
            result = endpoint_punch(endpoint, &datagram);
        } else if (valid_header(&datagram, NAT_CLOSE, NAT_ACK_SIZE)) {
            result = endpoint_close(endpoint, &datagram);
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
