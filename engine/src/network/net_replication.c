#include "net_replication.h"

#include <platform/time.h>
#include <stdio.h>
#include <string.h>

#if !defined(ENGINE_PLATFORM_WINDOWS)
#  include <dirent.h>
#  include <sys/stat.h>
#endif

static bool net_repl_parse_payload(const PacketBuffer *buf, NetTransformSnapshot *out,
                                   u32 max_count, u32 *out_count);

i32 net_replicator_send_heartbeat_ack(NetReplicator *rep, const NetAddress *dst,
                                      u32 send_time_ms, u32 echo_seq);

static u8 net_repl_type_index(u8 type) {
    return (type > 0u && type < NET_PKT_MAX) ? type : 0u;
}

static NetRepUnreliableChannel *net_unre_ch(NetReplicator *rep, u8 type) {
    return &rep->unreliable[net_repl_type_index(type)];
}

static NetRepOrderedChannel *net_ord_ch(NetReplicator *rep, u8 type) {
    return &rep->ordered[net_repl_type_index(type)];
}

static NetRepPeerStats *net_repl_peer_evict_lru(NetReplicator *rep) {
    if (!rep || rep->peer_count == 0u) return NULL;
    u32 oldest_i = 0u;
    u32 oldest_t = rep->peers[0].last_seen_ms;
    for (u32 i = 1u; i < rep->peer_count; i++) {
        if (rep->peers[i].last_seen_ms < oldest_t) {
            oldest_t = rep->peers[i].last_seen_ms;
            oldest_i = i;
        }
    }
    rep->peer_evicted++;
    return &rep->peers[oldest_i];
}

static NetRepPeerStats *net_repl_peer_find(NetReplicator *rep, const NetAddress *addr,
                                           bool create, u32 now_ms) {
    if (!rep || !addr) return NULL;
    for (u32 i = 0; i < rep->peer_count; i++) {
        if (net_address_equal(&rep->peers[i].addr, addr)) {
            rep->peers[i].last_seen_ms = now_ms;
            return &rep->peers[i];
        }
    }
    if (!create) return NULL;

    NetRepPeerStats *p = NULL;
    if (rep->peer_count >= NET_REP_MAX_PEERS)
        p = net_repl_peer_evict_lru(rep);
    else
        p = &rep->peers[rep->peer_count++];

    memset(p, 0, sizeof(*p));
    p->addr = *addr;
    p->valid = true;
    p->last_seen_ms = now_ms;
    return p;
}

static void net_repl_peer_update_rtt(NetReplicator *rep, const NetAddress *peer,
                                     f32 one_way_ms, f32 roundtrip_ms, u32 now_ms) {
    NetRepPeerStats *p = net_repl_peer_find(rep, peer, true, now_ms);
    if (!p) return;
    if (one_way_ms >= 0.0f) {
        p->last_rtt_ms = one_way_ms;
        p->hb_recv++;
    }
    if (roundtrip_ms >= 0.0f) {
        p->roundtrip_ms = roundtrip_ms;
        p->hb_rt_recv++;
    }
    p->dirty = true;
}

static void net_repl_peer_write_line(FILE *f, const NetRepPeerStats *p) {
    fprintf(f, "peer %s %u %.3f %.3f %u %u %u\n",
            p->addr.host, (u32)p->addr.port,
            (f64)p->last_rtt_ms, (f64)p->roundtrip_ms,
            p->hb_recv, p->hb_rt_recv, p->last_seen_ms);
}

static bool net_repl_peer_apply_line(NetReplicator *rep, const char *line) {
    if (!rep || !line) return false;
    const char *peer_line = line;
    if (peer_line[0] == '+' && peer_line[1] == ' ') peer_line += 2;
    if (strncmp(peer_line, "peer ", 5) != 0) return false;

    char host[256] = {0};
    u32 port = 0u, hb = 0u, hb_rt = 0u, seen = 0u;
    f32 rtt = 0.0f, rt = 0.0f;
    if (sscanf(peer_line + 5, "%255s %u %f %f %u %u %u",
               host, &port, &rtt, &rt, &hb, &hb_rt, &seen) < 7)
        return false;

    NetAddress addr = {0};
    memcpy(addr.host, host, strlen(host) + 1);
    addr.port = (u16)port;
    NetRepPeerStats *p = net_repl_peer_find(rep, &addr, true,
                                             (u32)(time_microseconds() / 1000ull));
    if (!p) return false;
    p->last_rtt_ms = rtt;
    p->roundtrip_ms = rt;
    p->hb_recv = hb;
    p->hb_rt_recv = hb_rt;
    p->last_seen_ms = seen;
    p->valid = true;
    return true;
}

static bool net_repl_mkdir_p(const char *dir) {
    if (!dir || !dir[0]) return false;
#if !defined(ENGINE_PLATFORM_WINDOWS)
    struct stat st;
    if (stat(dir, &st) == 0) return S_ISDIR(st.st_mode);
    return mkdir(dir, 0755) == 0;
#else
    (void)dir;
    return false;
#endif
}

static i32 net_repl_deliver_unreliable(NetReplicator *rep, u8 type, const u8 *wire, u32 len,
                                       const NetAddress *reply_to,
                                       NetTransformSnapshot *out, u32 max_count, u32 *out_count,
                                       u32 now_ms) {
    PacketHeader hdr;
    if (!packet_parse_header(wire, len, &hdr)) return NET_ERROR;
    if (hdr.type != type) {
        *out_count = 0u;
        return (i32)len;
    }

    NetRepUnreliableChannel *ch = net_unre_ch(rep, type);

    /* R245: wraparound-safe "ack has reached pending.seq" (ack at-or-after seq),
     * matching the seq-dedup convention (delta > 0x80000000u) used below. A naive
     * `ack >= seq` fails once the 32-bit sequence wraps (e.g. seq=0xFFFFFFF0,
     * ack=5), leaving reliable_pending stuck valid → endless retransmit. */
    if ((hdr.ack - rep->reliable_pending.seq) < 0x80000000u)
        rep->reliable_pending.valid = false;
    rep->last_peer_ack = hdr.ack;

    if (rep->seq_dedup && ch->last_recv_seq != 0u) {
        u32 delta = hdr.sequence - ch->last_recv_seq;
        if (delta > 0x80000000u) {
            *out_count = 0u;
            return (i32)len;
        }
    }
    ch->last_recv_seq = hdr.sequence;

    if (type != (u8)NET_PKT_TRANSFORM_SNAPSHOT) {
        if (type == (u8)NET_PKT_HEARTBEAT) {
            PacketBuffer buf;
            packet_read_begin(&buf, wire, len);
            u32 send_ms = packet_read_u32(&buf);
            /* now_ms passed from caller — avoids redundant time_microseconds() division */
            rep->hb_last_rtt_ms = (now_ms >= send_ms) ? (f32)(now_ms - send_ms) : 0.0f;
            rep->hb_recv++;
            if (reply_to)
                net_repl_peer_update_rtt(rep, reply_to, rep->hb_last_rtt_ms, -1.0f, now_ms);
            if (reply_to && rep->hb_echo_reply && rep->socket)
                net_replicator_send_heartbeat_ack(rep, reply_to, send_ms, hdr.sequence);
        } else if (type == (u8)NET_PKT_HEARTBEAT_ACK) {
            PacketBuffer buf;
            packet_read_begin(&buf, wire, len);
            u32 send_ms = packet_read_u32(&buf);
            (void)packet_read_u32(&buf);
            rep->hb_roundtrip_ms = (now_ms >= send_ms) ? (f32)(now_ms - send_ms) : 0.0f;
            rep->hb_roundtrip_recv++;
            if (reply_to)
                net_repl_peer_update_rtt(rep, reply_to, -1.0f, rep->hb_roundtrip_ms, now_ms);
        }
        *out_count = 0u;
        return (i32)len;
    }

    PacketBuffer buf;
    packet_read_begin(&buf, wire, len);
    if (!net_repl_parse_payload(&buf, out, max_count, out_count)) return NET_ERROR;
    return (i32)len;
}

static void net_reorder_store(NetReplicator *rep, u8 type, u32 seq, const u8 *wire, u32 len) {
    NetRepOrderedChannel *ch = net_ord_ch(rep, type);
    /* R250: only buffer packets inside the [next, next+NET_REORDER_SLOTS) window.
     * The slot index is seq % NET_REORDER_SLOTS, so a packet >= next+SLOTS aliases
     * onto a slot that may already hold a distinct, still-needed in-window seq;
     * the previous unconditional write overwrote it, dropping a packet the drain
     * loop still expects and stalling the ordered stream forever (drain waits on
     * next_ordered_seq which will never reappear). Within the window the 32 seqs
     * map bijectively to the 32 slots, so no in-window aliasing can occur. The
     * caller (net_repl_deliver_ordered) has already rejected stale/past seqs, so
     * (seq - next_ordered_seq) is a valid forward distance here. */
    u32 ahead = seq - ch->next_ordered_seq;
    if (ahead >= (u32)NET_REORDER_SLOTS) {
        ch->reorder_stale++;   /* out-of-window: buffer too small, drop (no overwrite) */
        return;
    }
    u32 idx = seq % NET_REORDER_SLOTS;
    NetReorderSlot *slot = &ch->slots[idx];
    if (slot->valid && slot->seq == seq) {
        ch->reorder_duplicate++;
    } else if (!slot->valid) {
        ch->reorder_pending++;
    }
    slot->seq = seq;
    slot->wire_len = len;
    memcpy(slot->wire, wire, len);
    slot->valid = true;
}

static i32 net_reorder_drain(NetReplicator *rep, u8 type, const NetAddress *reply_to,
                             NetTransformSnapshot *out, u32 max_count, u32 *out_count,
                             u32 now_ms) {
    NetRepOrderedChannel *ch = net_ord_ch(rep, type);
    u32 idx = ch->next_ordered_seq % NET_REORDER_SLOTS;
    NetReorderSlot *slot = &ch->slots[idx];
    if (!slot->valid || slot->seq != ch->next_ordered_seq)
        return 0;

    slot->valid = false;
    if (ch->reorder_pending > 0u) ch->reorder_pending--;
    ch->next_ordered_seq++;
    ch->reorder_delivered++;
    return net_repl_deliver_unreliable(rep, type, slot->wire, slot->wire_len, reply_to,
                                       out, max_count, out_count, now_ms);
}

static i32 net_repl_deliver_ordered(NetReplicator *rep, u8 type, const u8 *wire, u32 len,
                                    const NetAddress *reply_to,
                                    NetTransformSnapshot *out, u32 max_count, u32 *out_count,
                                    u32 now_ms) {
    PacketHeader hdr;
    if (!packet_parse_header(wire, len, &hdr)) return NET_ERROR;

    NetRepOrderedChannel *ch = net_ord_ch(rep, type);
    if ((hdr.ack - rep->reliable_pending.seq) < 0x80000000u) /* R245: wraparound-safe ack */
        rep->reliable_pending.valid = false;
    rep->last_peer_ack = hdr.ack;

    if (ch->next_ordered_seq == 0u)
        ch->next_ordered_seq = 1u;

    if (hdr.sequence != ch->next_ordered_seq) {
        u32 delta = hdr.sequence - ch->next_ordered_seq;
        if (delta > 0x80000000u) {
            ch->reorder_stale++;
            if ((hdr.flags & (u8)PACKET_RELIABLE) != 0u)
                ch->reorder_duplicate++;
            return (i32)len;
        }
        net_reorder_store(rep, type, hdr.sequence, wire, len);
        return (i32)len;
    }

    i32 n = net_repl_deliver_unreliable(rep, type, wire, len, reply_to, out, max_count, out_count, now_ms);
    if (n <= 0) return n;

    ch->last_recv_seq = hdr.sequence;
    ch->next_ordered_seq++;
    for (;;) {
        u32 late_count = 0u;
        i32 late = net_reorder_drain(rep, type, reply_to, out, max_count, &late_count, now_ms);
        /* R299 (CORRECTNESS): break only when the next slot isn't ready or the
         * drained packet failed to parse (late <= 0). The old `|| late_count == 0u`
         * also broke on a successfully-drained ordered packet that legitimately
         * carried 0 snapshots — which a foreign/forged peer can send (this
         * engine's broadcast rejects count==0, but the receiver must be robust,
         * same lineage as R254/R298). That premature break left every subsequent
         * consecutive buffered packet stuck (next_ordered_seq had advanced past
         * the empty one but the drain stopped), so reorder_pending never reached
         * 0 and the ordered stream stalled permanently. Only overwrite out_count
         * for a non-empty frame so a trailing empty packet can't clobber the last
         * delivered snapshot set. */
        if (late <= 0) break;
        if (late_count > 0u) *out_count = late_count;
    }
    return n;
}

static i32 net_replicator_process(NetReplicator *rep, const u8 *wire, u32 len,
                                  const NetAddress *reply_to,
                                  NetTransformSnapshot *out, u32 max_count, u32 *out_count) {
    if (!rep || !wire || len == 0u || !out || !out_count) return NET_ERROR;
    /* R115-1: Clamp len to PACKET_MAX_SIZE to prevent net_reorder_store buffer
     * overflow when callers (net_replicator_feed / net_replicator_feed_from)
     * pass arbitrary len.  The internal recv path already uses a
     * PACKET_MAX_SIZE-sized stack buffer so this only affects the public API. */
    if (len > PACKET_MAX_SIZE) return NET_ERROR;
    *out_count = 0u;

    PacketHeader hdr;
    if (!packet_parse_header(wire, len, &hdr)) return NET_ERROR;
    if (hdr.type != (u8)NET_PKT_TRANSFORM_SNAPSHOT &&
        hdr.type != (u8)NET_PKT_HEARTBEAT &&
        hdr.type != (u8)NET_PKT_HEARTBEAT_ACK) {
        return (i32)len;
    }

    /* Compute timestamp once per packet, pass to all callees (Round 18). */
    u32 now_ms = (u32)(time_microseconds() / 1000ull);

    /* R323 (CORRECTNESS): a packet's header `ack` field means "the sequence I am
     * acknowledging from you" (see packet.h; the sender clears reliable_pending
     * when an incoming ack reaches pending.seq, at deliver_* above). To actually
     * acknowledge a peer's RELIABLE packet, our own outgoing `ack` field must
     * therefore echo the peer's SEQUENCE — not the peer's ack field. The send
     * path previously wrote `last_peer_ack` (which we set to hdr.ack = the peer's
     * ack of US) into the outgoing ack, so we never acknowledged the peer's
     * sequence: both ends bounced their own ack values back and forth, their
     * reliable_pending never cleared via ack, and net_replicator_retry_pending
     * retransmitted the last reliable packet forever. Track the highest reliable
     * sequence we have received (wraparound-safe, same convention as seq-dedup)
     * and echo THAT as our outgoing ack; `last_peer_ack` still records hdr.ack
     * for our own retry self-check. Only RELIABLE packets need acking; heartbeats
     * are always unreliable, so this stays within the transform channel's space. */
    if ((hdr.flags & (u8)PACKET_RELIABLE) != 0u &&
        (hdr.sequence - rep->ack_to_send) < 0x80000000u) {
        rep->ack_to_send = hdr.sequence;
    }

    bool ordered = (hdr.flags & (u8)PACKET_ORDERED) != 0u;
    if (ordered)
        return net_repl_deliver_ordered(rep, hdr.type, wire, len, reply_to,
                                        out, max_count, out_count, now_ms);
    return net_repl_deliver_unreliable(rep, hdr.type, wire, len, reply_to,
                                       out, max_count, out_count, now_ms);
}

bool net_replicator_init(NetReplicator *rep, u16 bind_port) {
    if (!rep) return false;
    memset(rep, 0, sizeof(*rep));
    rep->socket = net_udp_create(bind_port);
    if (!rep->socket) return false;
    rep->owns_socket = true;
    for (u32 i = 1u; i < NET_PKT_MAX; i++) {
        rep->unreliable[i].send_seq = 1u;
        rep->ordered[i].send_seq = 1u;
    }
    rep->peer_evict_ms = 60000u;
    return true;
}

void net_replicator_shutdown(NetReplicator *rep) {
    if (!rep) return;
    if (rep->owns_socket && rep->socket) {
        net_close(rep->socket);
    }
    memset(rep, 0, sizeof(*rep));
}

i32 net_replicator_broadcast(NetReplicator *rep,
                             const NetTransformSnapshot *snapshots, u32 count,
                             const NetAddress *dst) {
    if (!rep || !rep->socket || !snapshots || !dst || count == 0u) return NET_ERROR;

    u16 n = (count > NET_REPL_MAX_SNAPSHOTS) ? (u16)NET_REPL_MAX_SNAPSHOTS : (u16)count;
    u8 pkt = (u8)NET_PKT_TRANSFORM_SNAPSHOT;

    PacketBuffer buf;
    u8 flags = rep->reliable_retry ? (u8)PACKET_RELIABLE : (u8)PACKET_UNRELIABLE;
    if (rep->ordered_layer) flags |= (u8)PACKET_ORDERED;
    packet_begin(&buf, pkt, flags);
    packet_write_u16(&buf, n);
    for (u16 i = 0; i < n; i++) {
        packet_write_u32(&buf, snapshots[i].entity_id);
        packet_write_f32(&buf, snapshots[i].position[0]);
        packet_write_f32(&buf, snapshots[i].position[1]);
        packet_write_f32(&buf, snapshots[i].position[2]);
    }

    u32 seq = rep->ordered_layer ? rep->ordered[pkt].send_seq++ : rep->unreliable[pkt].send_seq++;
    /* R323: echo the highest reliable seq WE received as our ack (see process). */
    u32 plen = packet_finish(&buf, seq, rep->ack_to_send);
    if (rep->reliable_retry) {
        memcpy(rep->reliable_pending.data, buf.data, plen);
        rep->reliable_pending.len = plen;
        rep->reliable_pending.seq = seq;
        rep->reliable_pending.dst = *dst;
        rep->reliable_pending.valid = true;
    }
    return net_sendto(rep->socket, buf.data, plen, dst);
}

i32 net_replicator_send_heartbeat(NetReplicator *rep, const NetAddress *dst, u32 send_time_ms) {
    if (!rep || !rep->socket || !dst) return NET_ERROR;

    u8 pkt = (u8)NET_PKT_HEARTBEAT;
    PacketBuffer buf;
    packet_begin(&buf, pkt, (u8)PACKET_UNRELIABLE);
    packet_write_u32(&buf, send_time_ms);

    u32 seq = rep->unreliable[pkt].send_seq++;
    u32 plen = packet_finish(&buf, seq, rep->ack_to_send); /* R323 */
    rep->hb_sent++;
    return net_sendto(rep->socket, buf.data, plen, dst);
}

i32 net_replicator_send_heartbeat_ack(NetReplicator *rep, const NetAddress *dst,
                                      u32 send_time_ms, u32 echo_seq) {
    if (!rep || !rep->socket || !dst) return NET_ERROR;

    u8 pkt = (u8)NET_PKT_HEARTBEAT_ACK;
    PacketBuffer buf;
    packet_begin(&buf, pkt, (u8)PACKET_UNRELIABLE);
    packet_write_u32(&buf, send_time_ms);
    packet_write_u32(&buf, echo_seq);

    u32 seq = rep->unreliable[pkt].send_seq++;
    u32 plen = packet_finish(&buf, seq, rep->ack_to_send); /* R323 */
    rep->hb_echo_sent++;
    return net_sendto(rep->socket, buf.data, plen, dst);
}

i32 net_replicator_retry_pending(NetReplicator *rep) {
    if (!rep || !rep->socket || !rep->reliable_retry || !rep->reliable_pending.valid) return 0;
    /* R245: wraparound-safe "last_peer_ack has reached pending.seq" (see deliver). */
    if ((rep->last_peer_ack - rep->reliable_pending.seq) < 0x80000000u) {
        rep->reliable_pending.valid = false;
        return 0;
    }
    rep->retry_count++;
    return net_sendto(rep->socket, rep->reliable_pending.data, rep->reliable_pending.len,
                      &rep->reliable_pending.dst);
}

static bool net_repl_parse_payload(const PacketBuffer *buf, NetTransformSnapshot *out,
                                   u32 max_count, u32 *out_count) {
    if (!buf || !out || !out_count) return false;
    *out_count = 0u;

    u16 n = packet_read_u16((PacketBuffer *)buf);
    if (n == 0u) return true;
    if (n > max_count) n = (u16)max_count;

    /* R254: clamp the declared entry count to the bytes actually present so a
     * truncated/forged length can't fabricate snapshots (each entry is
     * entity_id:u32 + position:3*f32 = 16 bytes). Without this the loop below
     * would read past write_pos — now zeros (see packet_can_read) — yet still
     * report recv_count = n, producing ghost entities at (0,0,0). */
    u32 avail = (buf->write_pos > buf->read_pos)
              ? (buf->write_pos - buf->read_pos) / 16u : 0u;
    if ((u32)n > avail) n = (u16)avail;
    if (n == 0u) return true;

    for (u16 i = 0; i < n; i++) {
        out[i].entity_id = packet_read_u32((PacketBuffer *)buf);
        out[i].position[0] = packet_read_f32((PacketBuffer *)buf);
        out[i].position[1] = packet_read_f32((PacketBuffer *)buf);
        out[i].position[2] = packet_read_f32((PacketBuffer *)buf);
    }
    *out_count = (u32)n;
    return true;
}

i32 net_replicator_recv(NetReplicator *rep,
                        NetTransformSnapshot *out, u32 max_count, u32 *out_count,
                        NetAddress *from) {
    if (!rep || !rep->socket || !out || !out_count) return NET_ERROR;

    u8 wire[PACKET_MAX_SIZE];
    NetAddress src;
    i32 n = net_recvfrom(rep->socket, wire, sizeof(wire), &src);
    if (n <= 0) return n;
    if (from) *from = src;
    return net_replicator_process(rep, wire, (u32)n, &src, out, max_count, out_count);
}

i32 net_replicator_feed(NetReplicator *rep, const u8 *wire, u32 len,
                        NetTransformSnapshot *out, u32 max_count, u32 *out_count) {
    if (!rep || !wire || len == 0u || !out || !out_count) return NET_ERROR;
    return net_replicator_process(rep, wire, len, NULL, out, max_count, out_count);
}

i32 net_replicator_feed_from(NetReplicator *rep, const u8 *wire, u32 len,
                             const NetAddress *reply_to,
                             NetTransformSnapshot *out, u32 max_count, u32 *out_count) {
    if (!rep || !wire || len == 0u || !out || !out_count) return NET_ERROR;
    return net_replicator_process(rep, wire, len, reply_to, out, max_count, out_count);
}

u32 net_replicator_peer_count(const NetReplicator *rep) {
    return rep ? rep->peer_count : 0u;
}

const NetRepPeerStats *net_replicator_peer_at(const NetReplicator *rep, u32 index) {
    if (!rep || index >= rep->peer_count) return NULL;
    return &rep->peers[index];
}

void net_replicator_peer_evict_stale(NetReplicator *rep, u32 now_ms) {
    if (!rep || rep->peer_evict_ms == 0u) return;
    for (u32 i = 0u; i < rep->peer_count; ) {
        if (now_ms - rep->peers[i].last_seen_ms > rep->peer_evict_ms) {
            if (i + 1u < rep->peer_count)
                rep->peers[i] = rep->peers[rep->peer_count - 1u];
            rep->peer_count--;
            rep->peer_evicted++;
        } else {
            i++;
        }
    }
}

bool net_replicator_peer_save(const NetReplicator *rep, const char *path) {
    if (!rep || !path) return false;
    FILE *f = fopen(path, "w");
    if (!f) return false;
    fprintf(f, "# break netrep peers v1\n");
    fprintf(f, "count %u\n", rep->peer_count);
    for (u32 i = 0u; i < rep->peer_count; i++)
        net_repl_peer_write_line(f, &rep->peers[i]);
    fclose(f);
    return true;
}

bool net_replicator_peer_load(NetReplicator *rep, const char *path) {
    if (!rep || !path) return false;
    FILE *f = fopen(path, "r");
    if (!f) return false;

    rep->peer_count = 0u;
    char line[512];
    while (fgets(line, sizeof(line), f)) {
        if (line[0] == '#' || line[0] == '\n') continue;
        net_repl_peer_apply_line(rep, line);
    }
    fclose(f);
    return true;
}

bool net_replicator_peer_save_dir(const NetReplicator *rep, const char *dir) {
    if (!rep || !dir || !dir[0]) return false;
    if (!net_repl_mkdir_p(dir)) return false;

    for (u32 i = 0u; i < rep->peer_count; i++) {
        char path[512];
        const NetRepPeerStats *p = &rep->peers[i];
        snprintf(path, sizeof(path), "%s/peer_%03u_%s_%u.peer",
                 dir, i, p->addr.host, (u32)p->addr.port);
        FILE *f = fopen(path, "w");
        if (!f) return false;
        fprintf(f, "# break netrep peer v1\n");
        net_repl_peer_write_line(f, p);
        fclose(f);
    }
    return true;
}

bool net_replicator_peer_load_dir(NetReplicator *rep, const char *dir) {
    if (!rep || !dir || !dir[0]) return false;
    rep->peer_count = 0u;

#if !defined(ENGINE_PLATFORM_WINDOWS)
    DIR *d = opendir(dir);
    if (!d) return false;
    struct dirent *ent;
    while ((ent = readdir(d)) != NULL) {
        size_t nlen = strlen(ent->d_name);
        if (nlen < 6u || strcmp(ent->d_name + nlen - 5u, ".peer") != 0) continue;
        char path[512];
        snprintf(path, sizeof(path), "%s/%s", dir, ent->d_name);
        FILE *f = fopen(path, "r");
        if (!f) continue;
        char line[512];
        while (fgets(line, sizeof(line), f))
            net_repl_peer_apply_line(rep, line);
        fclose(f);
    }
    closedir(d);

    char delta_path[512];
    snprintf(delta_path, sizeof(delta_path), "%s/delta.log", dir);
    net_replicator_peer_load_delta(rep, delta_path);
    return true;
#else
    (void)rep;
    return false;
#endif
}

bool net_replicator_peer_save_delta(NetReplicator *rep, const char *path) {
    if (!rep || !path) return false;
    FILE *f = fopen(path, "a");
    if (!f) return false;
    if (ftell(f) == 0)
        fprintf(f, "# break netrep delta v1\n");

    u32 wrote = 0u;
    for (u32 i = 0u; i < rep->peer_count; i++) {
        NetRepPeerStats *p = &rep->peers[i];
        if (!p->dirty) continue;
        fprintf(f, "+ ");
        net_repl_peer_write_line(f, p);
        p->dirty = false;
        wrote++;
    }
    fclose(f);
    return wrote > 0u;
}

bool net_replicator_peer_load_delta(NetReplicator *rep, const char *path) {
    if (!rep || !path) return false;
    FILE *f = fopen(path, "r");
    if (!f) return true;

    char line[512];
    while (fgets(line, sizeof(line), f)) {
        if (line[0] == '#' || line[0] == '\n') continue;
        net_repl_peer_apply_line(rep, line);
    }
    fclose(f);
    return true;
}
