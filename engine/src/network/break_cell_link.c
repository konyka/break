#include "network/break_cell_link.h"

#include <crypto/break_crypto.h>
#include <openssl/crypto.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "network/break_replay_window.h"

#define SEQUENCE_OFFSET 52u
#define KEY_ID_OFFSET 60u

typedef struct {
    u32 id; /* 0 = empty */
    u32 size;
    u8 bytes[BREAK_CELL_LINK_MAX_KEY_SIZE];
} LinkKey;

typedef struct {
    u32 cell_id;
    NetAddress address;
    BreakReplayWindow window;
} LinkPeer;

struct BreakCellLink {
    u32 cell_id;
    NetSocket *socket;
    u16 port;
    LinkKey current;
    LinkKey previous;
    u64 next_sequence;
    LinkPeer peers[BREAK_CELL_LINK_MAX_PEERS];
    u32 peer_count;
    BreakCellLinkStats stats;
    BreakCellLinkRejectFn reject_hook;
    void *reject_user;
};

static void put_u16(u8 *p, u16 v) {
    p[0] = (u8)v;
    p[1] = (u8)(v >> 8);
}

static void put_u32(u8 *p, u32 v) {
    for (u32 i = 0; i < 4u; i++) p[i] = (u8)(v >> (8u * i));
}

static void put_u64(u8 *p, u64 v) {
    for (u32 i = 0; i < 8u; i++) p[i] = (u8)(v >> (8u * i));
}

static u16 get_u16(const u8 *p) { return (u16)(p[0] | (p[1] << 8)); }

static u32 get_u32(const u8 *p) {
    u32 v = 0;
    for (u32 i = 0; i < 4u; i++) v |= (u32)p[i] << (8u * i);
    return v;
}

static u64 get_u64(const u8 *p) {
    u64 v = 0;
    for (u32 i = 0; i < 8u; i++) v |= (u64)p[i] << (8u * i);
    return v;
}

static bool valid_type(u32 type) {
    return type >= BREAK_CELL_MSG_OFFER && type <= BREAK_CELL_MSG_ABORT;
}

BreakCellWireResult break_cell_wire_encode(const u8 *key, u32 key_size, u32 key_id, u64 sequence,
                                           const BreakCellMsg *msg, u8 *out, u32 capacity,
                                           u32 *out_size) {
    u32 body;
    if (key == NULL || key_size == 0u || key_id == 0u || sequence == 0u || msg == NULL || out == NULL ||
        out_size == NULL)
        return BREAK_CELL_WIRE_INVALID_ARGUMENT;
    if (!valid_type(msg->type) || msg->state_size > BREAK_CELL_STATE_MAX)
        return BREAK_CELL_WIRE_BAD_HEADER;
    body = BREAK_CELL_WIRE_HEADER_SIZE + msg->state_size;
    if (capacity < body + BREAK_CELL_WIRE_TAG_SIZE) return BREAK_CELL_WIRE_BUFFER_TOO_SMALL;
    put_u32(out + 0, BREAK_CELL_WIRE_MAGIC);
    put_u16(out + 4, (u16)BREAK_CELL_WIRE_VERSION);
    put_u16(out + 6, (u16)msg->type);
    put_u32(out + 8, msg->from_cell);
    put_u32(out + 12, msg->to_cell);
    put_u32(out + 16, msg->state_size);
    put_u64(out + 20, msg->entity);
    put_u64(out + 28, msg->epoch);
    put_u64(out + 36, msg->txn);
    put_u64(out + 44, msg->nonce);
    put_u64(out + SEQUENCE_OFFSET, sequence);
    put_u32(out + KEY_ID_OFFSET, key_id);
    if (msg->state_size > 0u) memcpy(out + BREAK_CELL_WIRE_HEADER_SIZE, msg->state, msg->state_size);
    if (!break_crypto_hmac_sha256(key, key_size, out, body, out + body))
        return BREAK_CELL_WIRE_INVALID_ARGUMENT;
    *out_size = body + BREAK_CELL_WIRE_TAG_SIZE;
    return BREAK_CELL_WIRE_OK;
}

BreakCellWireResult break_cell_wire_decode(const u8 *key, u32 key_size, const u8 *data,
                                           u32 size, BreakCellMsg *out_msg, u64 *out_sequence,
                                           u32 *out_key_id) {
    u32 state_size, body, type, key_id;
    u64 sequence;
    u8 tag[BREAK_CELL_WIRE_TAG_SIZE];
    if (key == NULL || key_size == 0u || data == NULL || out_msg == NULL || out_sequence == NULL)
        return BREAK_CELL_WIRE_INVALID_ARGUMENT;
    if (size < BREAK_CELL_WIRE_HEADER_SIZE + BREAK_CELL_WIRE_TAG_SIZE || size > BREAK_CELL_WIRE_MAX_SIZE)
        return BREAK_CELL_WIRE_BAD_LENGTH;
    state_size = get_u32(data + 16);
    if (state_size > BREAK_CELL_STATE_MAX) return BREAK_CELL_WIRE_BAD_HEADER;
    body = BREAK_CELL_WIRE_HEADER_SIZE + state_size;
    if (size != body + BREAK_CELL_WIRE_TAG_SIZE) return BREAK_CELL_WIRE_BAD_LENGTH;
    if (!break_crypto_hmac_sha256(key, key_size, data, body, tag) ||
        CRYPTO_memcmp(tag, data + body, BREAK_CELL_WIRE_TAG_SIZE) != 0)
        return BREAK_CELL_WIRE_BAD_TAG;
    type = get_u16(data + 6);
    sequence = get_u64(data + SEQUENCE_OFFSET);
    key_id = get_u32(data + KEY_ID_OFFSET);
    if (get_u32(data) != BREAK_CELL_WIRE_MAGIC || get_u16(data + 4) != BREAK_CELL_WIRE_VERSION ||
        !valid_type(type) || sequence == 0u || key_id == 0u)
        return BREAK_CELL_WIRE_BAD_HEADER;
    memset(out_msg, 0, sizeof *out_msg);
    out_msg->type = type;
    out_msg->from_cell = get_u32(data + 8);
    out_msg->to_cell = get_u32(data + 12);
    out_msg->state_size = state_size;
    out_msg->entity = get_u64(data + 20);
    out_msg->epoch = get_u64(data + 28);
    out_msg->txn = get_u64(data + 36);
    out_msg->nonce = get_u64(data + 44);
    if (state_size > 0u) memcpy(out_msg->state, data + BREAK_CELL_WIRE_HEADER_SIZE, state_size);
    *out_sequence = sequence;
    if (out_key_id != NULL) *out_key_id = key_id;
    return BREAK_CELL_WIRE_OK;
}

bool break_cell_wire_key_id(const u8 *data, u32 size, u32 *out_key_id) {
    if (data == NULL || out_key_id == NULL || size < BREAK_CELL_WIRE_HEADER_SIZE) return false;
    *out_key_id = get_u32(data + KEY_ID_OFFSET);
    return true;
}

static bool valid_key(u32 key_id, const u8 *key, u32 key_size) {
    return key_id != 0u && key != NULL && key_size >= BREAK_CELL_LINK_MIN_KEY_SIZE &&
           key_size <= BREAK_CELL_LINK_MAX_KEY_SIZE;
}

static void set_key(LinkKey *slot, u32 key_id, const u8 *key, u32 key_size) {
    OPENSSL_cleanse(slot->bytes, sizeof slot->bytes);
    slot->id = key_id;
    slot->size = key_size;
    if (key != NULL) memcpy(slot->bytes, key, key_size);
}

#ifdef BREAK_CELL_LINK_TESTING
static bool g_fail_wall_clock;
void break_cell_link_set_clock_failure_for_test(bool fail) { g_fail_wall_clock = fail; }
#endif

static bool wall_clock_microseconds(u64 *out) {
    struct timespec ts;
#ifdef BREAK_CELL_LINK_TESTING
    if (g_fail_wall_clock) return false;
#endif
    if (timespec_get(&ts, TIME_UTC) != TIME_UTC || ts.tv_sec < 0) return false;
    *out = (u64)ts.tv_sec * 1000000u + (u64)ts.tv_nsec / 1000u;
    return true;
}

static LinkPeer *find_peer(BreakCellLink *link, u32 cell_id) {
    for (u32 i = 0; i < link->peer_count; i++)
        if (link->peers[i].cell_id == cell_id) return &link->peers[i];
    return NULL;
}

#ifdef BREAK_CELL_LINK_TESTING
bool break_cell_link_set_peer_address_for_test(BreakCellLink *link, u32 cell_id,
                                               const NetAddress *address) {
    LinkPeer *peer;
    if (link == NULL || address == NULL) return false;
    peer = find_peer(link, cell_id);
    if (peer == NULL) return false;
    peer->address = *address;
    return true;
}
#endif

BreakCellLink *break_cell_link_create(const BreakCellLinkConfig *config) {
    BreakCellLink *link;
    NetAddress local;
    u64 sequence;
    if (config == NULL || !valid_key(config->key_id, config->key, config->key_size) ||
        config->peers == NULL ||
        config->peer_count == 0u || config->peer_count > BREAK_CELL_LINK_MAX_PEERS)
        return NULL;
    for (u32 i = 0; i < config->peer_count; i++) {
        if (config->peers[i].cell_id == config->cell_id) return NULL;
        for (u32 j = 0; j < i; j++)
            if (config->peers[j].cell_id == config->peers[i].cell_id) return NULL;
    }
    if (!wall_clock_microseconds(&sequence)) return NULL;
    link = (BreakCellLink *)calloc(1u, sizeof *link);
    if (link == NULL) return NULL;
    link->socket = net_udp_create(config->bind_port);
    if (link->socket == NULL || !net_socket_get_local_address(link->socket, &local)) {
        if (link->socket != NULL) net_close(link->socket);
        free(link);
        return NULL;
    }
    net_set_nonblocking(link->socket, true);
    link->cell_id = config->cell_id;
    link->port = local.port;
    set_key(&link->current, config->key_id, config->key, config->key_size);
    link->next_sequence = sequence != 0u ? sequence : 1u;
    link->peer_count = config->peer_count;
    for (u32 i = 0; i < config->peer_count; i++) {
        link->peers[i].cell_id = config->peers[i].cell_id;
        link->peers[i].address = config->peers[i].address;
        break_replay_window_init(&link->peers[i].window);
    }
    return link;
}

void break_cell_link_destroy(BreakCellLink *link) {
    if (link == NULL) return;
    net_close(link->socket);
    OPENSSL_cleanse(&link->current, sizeof link->current);
    OPENSSL_cleanse(&link->previous, sizeof link->previous);
    free(link);
}

u16 break_cell_link_port(const BreakCellLink *link) { return link != NULL ? link->port : 0u; }

void break_cell_link_send(void *user, const BreakCellMsg *msg) {
    BreakCellLink *link = (BreakCellLink *)user;
    LinkPeer *to;
    u8 buf[BREAK_CELL_WIRE_MAX_SIZE];
    u32 n = 0;
    if (link == NULL || msg == NULL) return;
    to = find_peer(link, msg->to_cell);
    if (to == NULL || msg->from_cell != link->cell_id ||
        break_cell_wire_encode(link->current.bytes, link->current.size, link->current.id,
                               link->next_sequence, msg, buf, sizeof buf, &n) != BREAK_CELL_WIRE_OK) {
        link->stats.send_failed++;
        return;
    }
    link->next_sequence++;
    if (net_sendto(link->socket, buf, n, &to->address) != (i32)n) {
        link->stats.send_failed++;
        return;
    }
    link->stats.sent++;
}

/* The replay window is marked only after the tag verifies, so a forged
 * datagram cannot use up a sequence number. */
static void report(BreakCellLink *link, BreakCellLinkReject reason, u32 from_cell) {
    if (link->reject_hook) link->reject_hook(link->reject_user, reason, from_cell);
}

static void handle(BreakCellLink *link, BreakCell *cell, const u8 *data, u32 size, u32 *delivered) {
    BreakCellMsg msg;
    u64 sequence;
    LinkPeer *from;
    BreakCellWireResult r;
    const LinkKey *key = NULL;
    u32 key_id = 0;
    u32 claimed = size >= 12u ? (u32)data[8] | (u32)data[9] << 8 | (u32)data[10] << 16 |
                                    (u32)data[11] << 24
                              : 0u;
    if (size < BREAK_CELL_WIRE_HEADER_SIZE + BREAK_CELL_WIRE_TAG_SIZE ||
        !break_cell_wire_key_id(data, size, &key_id)) {
        link->stats.bad_format++;
        report(link, BREAK_CELL_LINK_REJECT_BAD_FORMAT, claimed);
        return;
    }
    if (key_id != 0u && key_id == link->current.id) key = &link->current;
    else if (key_id != 0u && key_id == link->previous.id) key = &link->previous;
    if (key == NULL) {
        link->stats.unknown_key++;
        report(link, BREAK_CELL_LINK_REJECT_UNKNOWN_KEY, claimed);
        return;
    }
    r = break_cell_wire_decode(key->bytes, key->size, data, size, &msg, &sequence, NULL);
    if (r == BREAK_CELL_WIRE_BAD_TAG) {
        link->stats.bad_tag++;
        report(link, BREAK_CELL_LINK_REJECT_BAD_TAG, claimed);
        return;
    }
    if (r != BREAK_CELL_WIRE_OK) {
        link->stats.bad_format++;
        report(link, BREAK_CELL_LINK_REJECT_BAD_FORMAT, claimed);
        return;
    }
    from = find_peer(link, msg.from_cell);
    if (from == NULL || msg.to_cell != link->cell_id) {
        link->stats.unknown_peer++;
        report(link, BREAK_CELL_LINK_REJECT_UNKNOWN_PEER, msg.from_cell);
        return;
    }
    if (break_replay_window_check_and_mark(&from->window, sequence) != BREAK_REPLAY_OK) {
        link->stats.replayed++;
        report(link, BREAK_CELL_LINK_REJECT_REPLAYED, msg.from_cell);
        return;
    }
    link->stats.received++;
    (*delivered)++;
    break_cell_receive(cell, &msg);
}

u32 break_cell_link_poll(BreakCellLink *link, BreakCell *cell, u32 max_datagrams) {
    u8 buf[BREAK_CELL_WIRE_MAX_SIZE + 1u];
    u32 delivered = 0;
    if (link == NULL || cell == NULL) return 0u;
    for (u32 i = 0; i < max_datagrams; i++) {
        NetAddress from;
        i32 n = net_recvfrom(link->socket, buf, sizeof buf, &from);
        if (n < 0) break;
        handle(link, cell, buf, (u32)n, &delivered);
    }
    return delivered;
}

bool break_cell_link_rotate_key(BreakCellLink *link, u32 key_id, const u8 *key, u32 key_size) {
    if (link == NULL || !valid_key(key_id, key, key_size) || key_id == link->current.id ||
        key_id == link->previous.id)
        return false;
    link->previous = link->current;
    set_key(&link->current, key_id, key, key_size);
    return true;
}

bool break_cell_link_retire_previous_key(BreakCellLink *link) {
    if (link == NULL || link->previous.id == 0u) return false;
    set_key(&link->previous, 0u, NULL, 0u);
    return true;
}

bool break_cell_link_set_reject_hook(BreakCellLink *link, BreakCellLinkRejectFn hook, void *user) {
    if (link == NULL) return false;
    link->reject_hook = hook;
    link->reject_user = hook != NULL ? user : NULL;
    return true;
}

bool break_cell_link_stats(const BreakCellLink *link, BreakCellLinkStats *out_stats) {
    if (link == NULL || out_stats == NULL) return false;
    *out_stats = link->stats;
    return true;
}
