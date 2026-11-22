/* Cross-process transport for BreakCell: an authenticated wire format and a
 * UDP link that drives a real handoff between two cells over loopback,
 * rejecting forged, replayed, misaddressed and malformed datagrams. */
#include "test_framework.h"
#include <network/break_cell_link.h>
#include <crypto/break_crypto.h>
#include <platform/time.h>
#include <string.h>

static const u8 kKey[32] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16,
                            17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32};

static BreakCellMsg sample(u32 type, u32 state_size) {
    BreakCellMsg m;
    memset(&m, 0, sizeof m);
    m.type = type;
    m.from_cell = 7u;
    m.to_cell = 9u;
    m.state_size = state_size;
    m.entity = 0x1122334455667788ull;
    m.epoch = 42u;
    m.txn = 0xa1a2a3a4a5a6a7a8ull;
    m.nonce = 0xfeedfacecafebeefull;
    for (u32 i = 0; i < state_size; i++) m.state[i] = (u8)(i * 7u + 3u);
    return m;
}

static bool same_msg(const BreakCellMsg *a, const BreakCellMsg *b) {
    return a->type == b->type && a->from_cell == b->from_cell && a->to_cell == b->to_cell &&
           a->state_size == b->state_size && a->entity == b->entity && a->epoch == b->epoch &&
           a->txn == b->txn && a->nonce == b->nonce &&
           memcmp(a->state, b->state, a->state_size) == 0;
}

TEST(wire_round_trips_every_type_and_state_size) {
    for (u32 type = BREAK_CELL_MSG_OFFER; type <= BREAK_CELL_MSG_ABORT; type++) {
        for (u32 size = 0; size <= BREAK_CELL_STATE_MAX; size++) {
            BreakCellMsg in = sample(type, size), out;
            u8 buf[BREAK_CELL_WIRE_MAX_SIZE];
            u32 n = 0;
            u64 seq = 0;
            ASSERT_EQ(break_cell_wire_encode(kKey, 32u, 1u, 1000u + size, &in, buf, sizeof buf, &n),
                      BREAK_CELL_WIRE_OK);
            ASSERT_EQ(n, BREAK_CELL_WIRE_HEADER_SIZE + size + BREAK_CELL_WIRE_TAG_SIZE);
            memset(&out, 0xcc, sizeof out);
            ASSERT_EQ(break_cell_wire_decode(kKey, 32u, buf, n, &out, &seq, NULL), BREAK_CELL_WIRE_OK);
            ASSERT_TRUE(same_msg(&in, &out));
            ASSERT_EQ(seq, 1000u + size);
        }
    }
    /* the layout is fixed little-endian: magic first, sequence at offset 52 */
    {
        BreakCellMsg in = sample(BREAK_CELL_MSG_COMMIT, 0u);
        u8 buf[BREAK_CELL_WIRE_MAX_SIZE];
        u32 n = 0;
        ASSERT_EQ(break_cell_wire_encode(kKey, 32u, 1u, 0x0102030405060708ull, &in, buf, sizeof buf, &n),
                  BREAK_CELL_WIRE_OK);
        ASSERT_EQ(buf[0], 0x42u);
        ASSERT_EQ(buf[1], 0x52u);
        ASSERT_EQ(buf[2], 0x43u);
        ASSERT_EQ(buf[3], 0x31u);
        ASSERT_EQ(buf[6], (u8)BREAK_CELL_MSG_COMMIT);
        ASSERT_EQ(buf[52], 0x08u);
        ASSERT_EQ(buf[59], 0x01u);
        ASSERT_EQ(buf[60], 0x01u); /* key id */
        ASSERT_EQ(buf[4], 0x02u); /* version */
    }
}

TEST(wire_encode_rejects_bad_arguments) {
    BreakCellMsg m = sample(BREAK_CELL_MSG_OFFER, 8u);
    u8 buf[BREAK_CELL_WIRE_MAX_SIZE];
    u32 n = 0;
    ASSERT_EQ(break_cell_wire_encode(kKey, 32u, 1u, 0u, &m, buf, sizeof buf, &n),
              BREAK_CELL_WIRE_INVALID_ARGUMENT);
    ASSERT_EQ(break_cell_wire_encode(NULL, 32u, 1u, 1u, &m, buf, sizeof buf, &n),
              BREAK_CELL_WIRE_INVALID_ARGUMENT);
    ASSERT_EQ(break_cell_wire_encode(kKey, 0u, 1u, 1u, &m, buf, sizeof buf, &n),
              BREAK_CELL_WIRE_INVALID_ARGUMENT);
    ASSERT_EQ(break_cell_wire_encode(kKey, 32u, 1u, 1u, NULL, buf, sizeof buf, &n),
              BREAK_CELL_WIRE_INVALID_ARGUMENT);
    ASSERT_EQ(break_cell_wire_encode(kKey, 32u, 1u, 1u, &m, NULL, sizeof buf, &n),
              BREAK_CELL_WIRE_INVALID_ARGUMENT);
    ASSERT_EQ(break_cell_wire_encode(kKey, 32u, 1u, 1u, &m, buf, sizeof buf, NULL),
              BREAK_CELL_WIRE_INVALID_ARGUMENT);
    ASSERT_EQ(break_cell_wire_encode(kKey, 32u, 1u, 1u, &m, buf,
                                     BREAK_CELL_WIRE_HEADER_SIZE + 8u + BREAK_CELL_WIRE_TAG_SIZE - 1u,
                                     &n),
              BREAK_CELL_WIRE_BUFFER_TOO_SMALL);
    m.state_size = BREAK_CELL_STATE_MAX + 1u;
    ASSERT_EQ(break_cell_wire_encode(kKey, 32u, 1u, 1u, &m, buf, sizeof buf, &n),
              BREAK_CELL_WIRE_BAD_HEADER);
    m = sample(0u, 0u);
    ASSERT_EQ(break_cell_wire_encode(kKey, 32u, 1u, 1u, &m, buf, sizeof buf, &n),
              BREAK_CELL_WIRE_BAD_HEADER);
    m = sample(BREAK_CELL_MSG_ABORT + 1u, 0u);
    ASSERT_EQ(break_cell_wire_encode(kKey, 32u, 1u, 1u, &m, buf, sizeof buf, &n),
              BREAK_CELL_WIRE_BAD_HEADER);
}

TEST(wire_decode_rejects_every_truncation_and_every_flipped_bit) {
    BreakCellMsg in = sample(BREAK_CELL_MSG_COMMIT, 16u), out;
    u8 buf[BREAK_CELL_WIRE_MAX_SIZE];
    u32 n = 0;
    u64 seq = 0;
    ASSERT_EQ(break_cell_wire_encode(kKey, 32u, 1u, 77u, &in, buf, sizeof buf, &n), BREAK_CELL_WIRE_OK);
    for (u32 len = 0; len < n; len++)
        ASSERT_TRUE(break_cell_wire_decode(kKey, 32u, buf, len, &out, &seq, NULL) != BREAK_CELL_WIRE_OK);
    {
        u8 longer[BREAK_CELL_WIRE_MAX_SIZE + 1u];
        memcpy(longer, buf, n);
        longer[n] = 0u;
        ASSERT_EQ(break_cell_wire_decode(kKey, 32u, longer, n + 1u, &out, &seq, NULL),
                  BREAK_CELL_WIRE_BAD_LENGTH);
    }
    for (u32 byte = 0; byte < n; byte++) {
        for (u32 bit = 0; bit < 8u; bit++) {
            buf[byte] ^= (u8)(1u << bit);
            ASSERT_TRUE(break_cell_wire_decode(kKey, 32u, buf, n, &out, &seq, NULL) != BREAK_CELL_WIRE_OK);
            buf[byte] ^= (u8)(1u << bit);
        }
    }
    ASSERT_EQ(break_cell_wire_decode(kKey, 32u, buf, n, &out, &seq, NULL), BREAK_CELL_WIRE_OK);
    {
        u8 other[32];
        memcpy(other, kKey, 32u);
        other[31] ^= 1u;
        ASSERT_EQ(break_cell_wire_decode(other, 32u, buf, n, &out, &seq, NULL), BREAK_CELL_WIRE_BAD_TAG);
        ASSERT_EQ(break_cell_wire_decode(kKey, 31u, buf, n, &out, &seq, NULL), BREAK_CELL_WIRE_BAD_TAG);
    }
    ASSERT_EQ(break_cell_wire_decode(kKey, 32u, NULL, n, &out, &seq, NULL), BREAK_CELL_WIRE_INVALID_ARGUMENT);
    ASSERT_EQ(break_cell_wire_decode(kKey, 32u, buf, n, NULL, &seq, NULL), BREAK_CELL_WIRE_INVALID_ARGUMENT);
    ASSERT_EQ(break_cell_wire_decode(kKey, 32u, buf, n, &out, NULL, NULL), BREAK_CELL_WIRE_INVALID_ARGUMENT);
    ASSERT_EQ(break_cell_wire_decode(NULL, 32u, buf, n, &out, &seq, NULL), BREAK_CELL_WIRE_INVALID_ARGUMENT);
    /* the key id is reported and covered by the tag */
    {
        u32 key_id = 0;
        u8 tagged[BREAK_CELL_WIRE_MAX_SIZE];
        u32 tn = 0;
        ASSERT_EQ(break_cell_wire_encode(kKey, 32u, 0xa0b0c0d0u, 9u, &in, tagged, sizeof tagged, &tn),
                  BREAK_CELL_WIRE_OK);
        ASSERT_EQ(break_cell_wire_key_id(tagged, tn, &key_id), true);
        ASSERT_EQ(key_id, 0xa0b0c0d0u);
        key_id = 0;
        ASSERT_EQ(break_cell_wire_decode(kKey, 32u, tagged, tn, &out, &seq, &key_id), BREAK_CELL_WIRE_OK);
        ASSERT_EQ(key_id, 0xa0b0c0d0u);
        ASSERT_FALSE(break_cell_wire_key_id(tagged, BREAK_CELL_WIRE_HEADER_SIZE - 1u, &key_id));
        ASSERT_FALSE(break_cell_wire_key_id(NULL, tn, &key_id));
        ASSERT_FALSE(break_cell_wire_key_id(tagged, tn, NULL));
    }
    /* a zero sequence is never valid, even with a correct tag */
    memset(buf + 52, 0, 8u);
    ASSERT_TRUE(break_crypto_hmac_sha256(kKey, 32u, buf, n - BREAK_CELL_WIRE_TAG_SIZE,
                                         buf + n - BREAK_CELL_WIRE_TAG_SIZE));
    ASSERT_EQ(break_cell_wire_decode(kKey, 32u, buf, n, &out, &seq, NULL), BREAK_CELL_WIRE_BAD_HEADER);
    /* nor is key id 0 */
    ASSERT_EQ(break_cell_wire_encode(kKey, 32u, 1u, 77u, &in, buf, sizeof buf, &n), BREAK_CELL_WIRE_OK);
    memset(buf + 60, 0, 4u);
    ASSERT_TRUE(break_crypto_hmac_sha256(kKey, 32u, buf, n - BREAK_CELL_WIRE_TAG_SIZE,
                                         buf + n - BREAK_CELL_WIRE_TAG_SIZE));
    ASSERT_EQ(break_cell_wire_decode(kKey, 32u, buf, n, &out, &seq, NULL), BREAK_CELL_WIRE_BAD_HEADER);
    /* and the encoder refuses key id 0 */
    ASSERT_EQ(break_cell_wire_encode(kKey, 32u, 0u, 77u, &in, buf, sizeof buf, &n),
              BREAK_CELL_WIRE_INVALID_ARGUMENT);
}

static BreakCellLinkConfig link_config(u32 self, const BreakCellPeer *peers, u32 count) {
    BreakCellLinkConfig c;
    memset(&c, 0, sizeof c);
    c.cell_id = self;
    c.key = kKey;
    c.key_size = 32u;
    c.key_id = 1u;
    c.peers = peers;
    c.peer_count = count;
    return c;
}

static BreakCellPeer peer(u32 id, u16 port) {
    BreakCellPeer p;
    memset(&p, 0, sizeof p);
    p.cell_id = id;
    if (!net_address_resolve("127.0.0.1", port, &p.address)) p.address.port = 0u;
    return p;
}

TEST(link_create_validates_configuration) {
    BreakCellPeer peers[2] = {peer(2u, 9u), peer(3u, 9u)};
    BreakCellLinkConfig c = link_config(1u, peers, 2u);
    BreakCellLink *ok = break_cell_link_create(&c);
    ASSERT_NOT_NULL(ok);
    ASSERT_TRUE(break_cell_link_port(ok) != 0u);
    break_cell_link_destroy(ok);
    ASSERT_TRUE(break_cell_link_create(NULL) == NULL);
    c = link_config(1u, peers, 0u);
    ASSERT_TRUE(break_cell_link_create(&c) == NULL);
    c = link_config(1u, NULL, 2u);
    ASSERT_TRUE(break_cell_link_create(&c) == NULL);
    c = link_config(1u, peers, BREAK_CELL_LINK_MAX_PEERS + 1u);
    ASSERT_TRUE(break_cell_link_create(&c) == NULL);
    c = link_config(2u, peers, 2u); /* a peer has the local id */
    ASSERT_TRUE(break_cell_link_create(&c) == NULL);
    peers[1].cell_id = 2u; /* duplicate peer ids */
    c = link_config(1u, peers, 2u);
    ASSERT_TRUE(break_cell_link_create(&c) == NULL);
    peers[1].cell_id = 3u;
    c = link_config(1u, peers, 2u);
    c.key_size = BREAK_CELL_LINK_MIN_KEY_SIZE - 1u;
    ASSERT_TRUE(break_cell_link_create(&c) == NULL);
    c.key_size = BREAK_CELL_LINK_MAX_KEY_SIZE + 1u;
    ASSERT_TRUE(break_cell_link_create(&c) == NULL);
    c.key_size = 32u;
    c.key = NULL;
    ASSERT_TRUE(break_cell_link_create(&c) == NULL);
    c.key = kKey;
    c.key_id = 0u; /* key id 0 is reserved */
    ASSERT_TRUE(break_cell_link_create(&c) == NULL);
    /* the config's key buffer may be reused once the link exists */
    {
        u8 key[32];
        memcpy(key, kKey, 32u);
        c = link_config(1u, peers, 2u);
        c.key = key;
        ok = break_cell_link_create(&c);
        ASSERT_NOT_NULL(ok);
        memset(key, 0, sizeof key);
        break_cell_link_destroy(ok);
    }
    break_cell_link_destroy(NULL);
    ASSERT_EQ(break_cell_link_port(NULL), 0u);
    ASSERT_EQ(break_cell_link_poll(NULL, NULL, 4u), 0u);
    ASSERT_FALSE(break_cell_link_stats(NULL, NULL));
}

/* Two cells, each with its own link on a loopback port. */
typedef struct {
    BreakCellLink *link[2];
    BreakCell *cell[2];
} Pair;

static bool pair_open(Pair *p, u32 retransmit_ticks) {
    BreakCellPeer pa, pb;
    BreakCellLinkConfig ca, cb;
    BreakCellConfig cfg;
    memset(p, 0, sizeof *p);
    pa = peer(2u, 1u); /* port fixed up below once B is bound */
    ca = link_config(1u, &pa, 1u);
    pb = peer(1u, 1u);
    cb = link_config(2u, &pb, 1u);
    p->link[1] = break_cell_link_create(&cb);
    if (p->link[1] == NULL) return false;
    pa = peer(2u, break_cell_link_port(p->link[1]));
    p->link[0] = break_cell_link_create(&ca);
    if (p->link[0] == NULL) return false;
    break_cell_link_destroy(p->link[1]);
    pb = peer(1u, break_cell_link_port(p->link[0]));
    cb = link_config(2u, &pb, 1u);
    cb.bind_port = pa.address.port;
    p->link[1] = break_cell_link_create(&cb);
    if (p->link[1] == NULL) return false;
    for (u32 i = 0; i < 2u; i++) {
        memset(&cfg, 0, sizeof cfg);
        cfg.cell_id = i + 1u;
        cfg.capacity = 16u;
        cfg.retransmit_ticks = retransmit_ticks;
        cfg.send = break_cell_link_send;
        cfg.user = p->link[i];
        p->cell[i] = break_cell_create(&cfg);
        if (p->cell[i] == NULL) return false;
    }
    return true;
}

static void pair_close(Pair *p) {
    for (u32 i = 0; i < 2u; i++) {
        break_cell_destroy(p->cell[i]);
        break_cell_link_destroy(p->link[i]);
    }
}

static void pair_step(Pair *p) {
    for (u32 i = 0; i < 2u; i++) {
        (void)break_cell_link_poll(p->link[i], p->cell[i], 64u);
        break_cell_tick(p->cell[i]);
    }
    time_sleep_us(1000u);
}

TEST(a_handoff_completes_over_udp_and_carries_the_latest_state) {
    Pair p;
    u8 state[4] = {1, 2, 3, 4}, got[8];
    u32 got_size = 0;
    u64 epoch = 0;
    BreakCellLinkStats sa, sb;
    ASSERT_TRUE(pair_open(&p, 5u));
    ASSERT_TRUE(break_cell_spawn(p.cell[0], 100u, state, 4u));
    ASSERT_TRUE(break_cell_begin_handoff(p.cell[0], 100u, 2u));
    state[0] = 9u; /* written while the offer is in flight */
    ASSERT_TRUE(break_cell_write(p.cell[0], 100u, state, 4u));
    for (u32 i = 0; i < 2000u && break_cell_entity_state(p.cell[0], 100u) != BREAK_CELL_ENTITY_NONE; i++) {
        ASSERT_FALSE(break_cell_is_authoritative(p.cell[0], 100u) &&
                     break_cell_is_authoritative(p.cell[1], 100u));
        pair_step(&p);
    }
    ASSERT_EQ(break_cell_entity_state(p.cell[0], 100u), BREAK_CELL_ENTITY_NONE);
    ASSERT_TRUE(break_cell_is_authoritative(p.cell[1], 100u));
    ASSERT_TRUE(break_cell_read(p.cell[1], 100u, got, sizeof got, &got_size, &epoch));
    ASSERT_EQ(got_size, 4u);
    ASSERT_EQ(got[0], 9u);
    ASSERT_EQ(epoch, 2u);
    ASSERT_TRUE(break_cell_link_stats(p.link[0], &sa));
    ASSERT_TRUE(break_cell_link_stats(p.link[1], &sb));
    ASSERT_TRUE(sa.sent >= 2u);
    ASSERT_TRUE(sb.received >= 2u);
    ASSERT_EQ(sa.bad_tag + sb.bad_tag + sa.replayed + sb.replayed, 0u);
    pair_close(&p);
}

/* Sends raw bytes to a link from a separate socket. */
static void inject(NetSocket *s, const BreakCellLink *to, const u8 *data, u32 size) {
    NetAddress a;
    ASSERT_TRUE(net_address_resolve("127.0.0.1", break_cell_link_port(to), &a));
    ASSERT_EQ(net_sendto(s, data, size, &a), (i32)size);
}

static void drain(Pair *p, u32 which) {
    for (u32 i = 0; i < 50u; i++) {
        (void)break_cell_link_poll(p->link[which], p->cell[which], 64u);
        time_sleep_us(1000u);
    }
}

TEST(forged_replayed_misaddressed_and_malformed_datagrams_are_dropped) {
    Pair p;
    NetSocket *s = net_udp_create(0u);
    BreakCellLinkStats st;
    BreakCellMsg offer;
    u8 buf[BREAK_CELL_WIRE_MAX_SIZE], forged[BREAK_CELL_WIRE_MAX_SIZE];
    u32 n = 0;
    u8 wrong_key[32];
    ASSERT_NOT_NULL(s);
    ASSERT_TRUE(pair_open(&p, 1000u));
    memset(&offer, 0, sizeof offer);
    offer.type = BREAK_CELL_MSG_OFFER;
    offer.from_cell = 1u;
    offer.to_cell = 2u;
    offer.entity = 500u;
    offer.epoch = 1u;
    offer.txn = 1u;

    /* a valid datagram from cell 1 is delivered once, its replay is not */
    ASSERT_EQ(break_cell_wire_encode(kKey, 32u, 1u, 10u, &offer, buf, sizeof buf, &n), BREAK_CELL_WIRE_OK);
    inject(s, p.link[1], buf, n);
    inject(s, p.link[1], buf, n);
    drain(&p, 1u);
    ASSERT_TRUE(break_cell_link_stats(p.link[1], &st));
    ASSERT_EQ(st.received, 1u);
    ASSERT_EQ(st.replayed, 1u);
    ASSERT_EQ(break_cell_entity_state(p.cell[1], 500u), BREAK_CELL_ENTITY_RECEIVING);

    /* a newer sequence is accepted, one far below the window is too old */
    offer.entity = 501u;
    ASSERT_EQ(break_cell_wire_encode(kKey, 32u, 1u, 200u, &offer, buf, sizeof buf, &n), BREAK_CELL_WIRE_OK);
    inject(s, p.link[1], buf, n);
    offer.entity = 502u;
    ASSERT_EQ(break_cell_wire_encode(kKey, 32u, 1u, 11u, &offer, buf, sizeof buf, &n), BREAK_CELL_WIRE_OK);
    inject(s, p.link[1], buf, n);
    drain(&p, 1u);
    ASSERT_TRUE(break_cell_link_stats(p.link[1], &st));
    ASSERT_EQ(st.received, 2u);
    ASSERT_EQ(st.replayed, 2u);
    ASSERT_EQ(break_cell_entity_state(p.cell[1], 502u), BREAK_CELL_ENTITY_NONE);

    /* a forged replay (bad tag) must not burn the sequence it claims */
    offer.entity = 503u;
    memcpy(wrong_key, kKey, 32u);
    wrong_key[0] ^= 0x80u;
    ASSERT_EQ(break_cell_wire_encode(wrong_key, 32u, 1u, 201u, &offer, forged, sizeof forged, &n),
              BREAK_CELL_WIRE_OK);
    inject(s, p.link[1], forged, n);
    drain(&p, 1u);
    ASSERT_EQ(break_cell_wire_encode(kKey, 32u, 1u, 201u, &offer, buf, sizeof buf, &n), BREAK_CELL_WIRE_OK);
    inject(s, p.link[1], buf, n);
    drain(&p, 1u);
    ASSERT_TRUE(break_cell_link_stats(p.link[1], &st));
    ASSERT_EQ(st.bad_tag, 1u);
    ASSERT_EQ(st.received, 3u);
    ASSERT_EQ(break_cell_entity_state(p.cell[1], 503u), BREAK_CELL_ENTITY_RECEIVING);

    /* an unknown sender, and a message addressed to another cell */
    offer.entity = 504u;
    offer.from_cell = 3u;
    ASSERT_EQ(break_cell_wire_encode(kKey, 32u, 1u, 300u, &offer, buf, sizeof buf, &n), BREAK_CELL_WIRE_OK);
    inject(s, p.link[1], buf, n);
    offer.from_cell = 1u;
    offer.to_cell = 4u;
    ASSERT_EQ(break_cell_wire_encode(kKey, 32u, 1u, 301u, &offer, buf, sizeof buf, &n), BREAK_CELL_WIRE_OK);
    inject(s, p.link[1], buf, n);
    /* a truncated datagram, a valid one cut short by a byte, and garbage
     * whose key id is not held */
    offer.to_cell = 2u;
    ASSERT_EQ(break_cell_wire_encode(kKey, 32u, 1u, 302u, &offer, buf, sizeof buf, &n), BREAK_CELL_WIRE_OK);
    inject(s, p.link[1], buf, 20u);
    inject(s, p.link[1], buf, n - 1u);
    memset(buf, 0x5a, sizeof buf);
    inject(s, p.link[1], buf, BREAK_CELL_WIRE_HEADER_SIZE + BREAK_CELL_WIRE_TAG_SIZE);
    drain(&p, 1u);
    ASSERT_TRUE(break_cell_link_stats(p.link[1], &st));
    ASSERT_EQ(st.unknown_peer, 2u);
    ASSERT_EQ(st.bad_format, 2u);
    ASSERT_EQ(st.unknown_key, 1u);
    ASSERT_EQ(st.received, 3u);
    ASSERT_EQ(break_cell_entity_state(p.cell[1], 504u), BREAK_CELL_ENTITY_NONE);

    /* a message the cell would send to an unconfigured cell is not sent */
    {
        BreakCellMsg stray = offer;
        BreakCellLinkStats sa;
        stray.to_cell = 77u;
        break_cell_link_send(p.link[0], &stray);
        ASSERT_TRUE(break_cell_link_stats(p.link[0], &sa));
        ASSERT_EQ(sa.send_failed, 1u);
        stray.to_cell = 2u;
        stray.from_cell = 5u; /* the link refuses to speak for another cell */
        break_cell_link_send(p.link[0], &stray);
        ASSERT_TRUE(break_cell_link_stats(p.link[0], &sa));
        ASSERT_EQ(sa.send_failed, 2u);
        ASSERT_EQ(sa.sent, 0u);
    }
    net_close(s);
    pair_close(&p);
}

TEST(a_restarted_sender_is_not_mistaken_for_a_replay) {
    Pair p;
    BreakCellLinkStats st;
    u8 state[2] = {5, 6};
    ASSERT_TRUE(pair_open(&p, 3u));
    ASSERT_TRUE(break_cell_spawn(p.cell[0], 1u, state, 2u));
    ASSERT_TRUE(break_cell_begin_handoff(p.cell[0], 1u, 2u));
    for (u32 i = 0; i < 2000u && !break_cell_is_authoritative(p.cell[1], 1u); i++) pair_step(&p);
    ASSERT_TRUE(break_cell_is_authoritative(p.cell[1], 1u));
    for (u32 i = 0; i < 50u; i++) pair_step(&p);

    /* restart cell 1's link on the same port: its sequence starts over */
    {
        BreakCellPeer pb = peer(2u, break_cell_link_port(p.link[1]));
        BreakCellLinkConfig ca = link_config(1u, &pb, 1u);
        BreakCellConfig cfg;
        ca.bind_port = break_cell_link_port(p.link[0]);
        break_cell_destroy(p.cell[0]);
        break_cell_link_destroy(p.link[0]);
        p.link[0] = break_cell_link_create(&ca);
        ASSERT_NOT_NULL(p.link[0]);
        memset(&cfg, 0, sizeof cfg);
        cfg.cell_id = 1u;
        cfg.capacity = 16u;
        cfg.retransmit_ticks = 3u;
        cfg.send = break_cell_link_send;
        cfg.user = p.link[0];
        p.cell[0] = break_cell_create(&cfg);
        ASSERT_NOT_NULL(p.cell[0]);
    }
    ASSERT_TRUE(break_cell_spawn(p.cell[0], 2u, state, 2u));
    ASSERT_TRUE(break_cell_begin_handoff(p.cell[0], 2u, 2u));
    for (u32 i = 0; i < 2000u && !break_cell_is_authoritative(p.cell[1], 2u); i++) pair_step(&p);
    ASSERT_TRUE(break_cell_is_authoritative(p.cell[1], 2u));
    ASSERT_TRUE(break_cell_link_stats(p.link[1], &st));
    ASSERT_EQ(st.replayed, 0u);
    pair_close(&p);
}

static const u8 kKey2[32] = {201, 202, 203, 204, 205, 206, 207, 208, 209, 210, 211, 212, 213, 214, 215, 216,
                             217, 218, 219, 220, 221, 222, 223, 224, 225, 226, 227, 228, 229, 230, 231, 232};

TEST(keys_rotate_without_interrupting_a_handoff) {
    Pair p;
    NetSocket *s = net_udp_create(0u);
    BreakCellLinkStats st;
    BreakCellMsg offer;
    u8 buf[BREAK_CELL_WIRE_MAX_SIZE], state[1] = {7};
    u32 n = 0;
    ASSERT_NOT_NULL(s);
    ASSERT_TRUE(pair_open(&p, 3u));

    /* invalid rotations leave the link unchanged */
    ASSERT_FALSE(break_cell_link_rotate_key(p.link[1], 1u, kKey2, 32u)); /* id in use */
    ASSERT_FALSE(break_cell_link_rotate_key(p.link[1], 2u, kKey2, BREAK_CELL_LINK_MIN_KEY_SIZE - 1u));
    ASSERT_FALSE(break_cell_link_rotate_key(p.link[1], 2u, NULL, 32u));
    ASSERT_FALSE(break_cell_link_rotate_key(NULL, 2u, kKey2, 32u));
    ASSERT_FALSE(break_cell_link_retire_previous_key(p.link[1])); /* nothing to retire */

    /* B learns key 2 first; A still sends with key 1 and is accepted */
    ASSERT_TRUE(break_cell_link_rotate_key(p.link[1], 2u, kKey2, 32u));
    ASSERT_TRUE(break_cell_spawn(p.cell[0], 1u, state, 1u));
    ASSERT_TRUE(break_cell_begin_handoff(p.cell[0], 1u, 2u));
    for (u32 i = 0; i < 3u; i++) pair_step(&p);
    /* A switches mid-handoff; B still holds key 1 as the previous key */
    ASSERT_TRUE(break_cell_link_rotate_key(p.link[0], 2u, kKey2, 32u));
    for (u32 i = 0; i < 2000u && break_cell_entity_state(p.cell[0], 1u) != BREAK_CELL_ENTITY_NONE; i++)
        pair_step(&p);
    ASSERT_EQ(break_cell_entity_state(p.cell[0], 1u), BREAK_CELL_ENTITY_NONE);
    ASSERT_TRUE(break_cell_is_authoritative(p.cell[1], 1u));
    ASSERT_TRUE(break_cell_link_stats(p.link[1], &st));
    ASSERT_EQ(st.bad_tag + st.unknown_key, 0u);

    /* after retiring key 1, datagrams under key 1 are refused, key 2 works */
    ASSERT_TRUE(break_cell_link_retire_previous_key(p.link[1]));
    ASSERT_FALSE(break_cell_link_retire_previous_key(p.link[1]));
    memset(&offer, 0, sizeof offer);
    offer.type = BREAK_CELL_MSG_OFFER;
    offer.from_cell = 1u;
    offer.to_cell = 2u;
    offer.entity = 900u;
    offer.epoch = 1u;
    offer.txn = 1u;
    ASSERT_EQ(break_cell_wire_encode(kKey, 32u, 1u, (u64)1 << 62, &offer, buf, sizeof buf, &n),
              BREAK_CELL_WIRE_OK);
    inject(s, p.link[1], buf, n);
    /* a datagram claiming key id 2 but signed with key 1 is a bad tag */
    offer.entity = 901u;
    ASSERT_EQ(break_cell_wire_encode(kKey, 32u, 2u, ((u64)1 << 62) + 1u, &offer, buf, sizeof buf, &n),
              BREAK_CELL_WIRE_OK);
    inject(s, p.link[1], buf, n);
    offer.entity = 902u;
    ASSERT_EQ(break_cell_wire_encode(kKey2, 32u, 2u, ((u64)1 << 62) + 2u, &offer, buf, sizeof buf, &n),
              BREAK_CELL_WIRE_OK);
    inject(s, p.link[1], buf, n);
    drain(&p, 1u);
    ASSERT_TRUE(break_cell_link_stats(p.link[1], &st));
    ASSERT_EQ(st.unknown_key, 1u);
    ASSERT_EQ(st.bad_tag, 1u);
    ASSERT_EQ(break_cell_entity_state(p.cell[1], 900u), BREAK_CELL_ENTITY_NONE);
    ASSERT_EQ(break_cell_entity_state(p.cell[1], 901u), BREAK_CELL_ENTITY_NONE);
    ASSERT_EQ(break_cell_entity_state(p.cell[1], 902u), BREAK_CELL_ENTITY_RECEIVING);

    /* rotating again replaces the previous key: only the two newest remain */
    ASSERT_TRUE(break_cell_link_rotate_key(p.link[1], 3u, kKey, 32u));
    ASSERT_TRUE(break_cell_link_rotate_key(p.link[1], 4u, kKey2, 32u));
    offer.entity = 903u;
    ASSERT_EQ(break_cell_wire_encode(kKey2, 32u, 2u, ((u64)1 << 62) + 3u, &offer, buf, sizeof buf, &n),
              BREAK_CELL_WIRE_OK);
    inject(s, p.link[1], buf, n);
    offer.entity = 904u;
    ASSERT_EQ(break_cell_wire_encode(kKey, 32u, 3u, ((u64)1 << 62) + 4u, &offer, buf, sizeof buf, &n),
              BREAK_CELL_WIRE_OK);
    inject(s, p.link[1], buf, n);
    drain(&p, 1u);
    ASSERT_TRUE(break_cell_link_stats(p.link[1], &st));
    ASSERT_EQ(st.unknown_key, 2u);
    ASSERT_EQ(break_cell_entity_state(p.cell[1], 903u), BREAK_CELL_ENTITY_NONE);
    ASSERT_EQ(break_cell_entity_state(p.cell[1], 904u), BREAK_CELL_ENTITY_RECEIVING);
    net_close(s);
    pair_close(&p);
}

TEST_MAIN_BEGIN()
    if (!net_init()) return 1;
    time_init();
    RUN_TEST(wire_round_trips_every_type_and_state_size);
    RUN_TEST(wire_encode_rejects_bad_arguments);
    RUN_TEST(wire_decode_rejects_every_truncation_and_every_flipped_bit);
    RUN_TEST(link_create_validates_configuration);
    RUN_TEST(a_handoff_completes_over_udp_and_carries_the_latest_state);
    RUN_TEST(forged_replayed_misaddressed_and_malformed_datagrams_are_dropped);
    RUN_TEST(a_restarted_sender_is_not_mistaken_for_a_replay);
    RUN_TEST(keys_rotate_without_interrupting_a_handoff);
    net_shutdown();
TEST_MAIN_END()
