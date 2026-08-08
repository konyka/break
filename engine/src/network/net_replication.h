#ifndef NET_REPLICATION_H
#define NET_REPLICATION_H

#include "../core/types.h"
#include "network.h"
#include "packet.h"

#include <stddef.h>

#define NET_PKT_TRANSFORM_SNAPSHOT 1u
#define NET_PKT_HEARTBEAT          2u
#define NET_PKT_HEARTBEAT_ACK      3u
#define NET_PKT_MAX                4u
#define NET_REPL_MAX_SNAPSHOTS     64u
#define NET_REORDER_SLOTS          32u
#define NET_REP_MAX_PEERS          8u
/* R434: max reliable packets in flight per replicator (sliding window). */
#define NET_RELIABLE_WINDOW        8u
/* R435: delta.log rotation threshold (bytes); compile-time overridable. */
#ifndef NETREP_DELTA_MAX_BYTES
#define NETREP_DELTA_MAX_BYTES (1024u * 1024u)
#endif
/* R435: live rotation threshold, starts at NETREP_DELTA_MAX_BYTES. Exposed so
 * tests can lower it (save/restore around the test); not a stable API. */
extern size_t netrep_delta_max_bytes;

typedef struct {
    u32 entity_id;
    f32 position[3];
} NetTransformSnapshot;

typedef struct {
    NetAddress addr;
    f32        last_rtt_ms;
    f32        roundtrip_ms;
    u32        hb_recv;
    u32        hb_rt_recv;
    u32        last_seen_ms;
    bool       valid;
    bool       dirty;
} NetRepPeerStats;

typedef struct {
    u32  seq;
    u32  wire_len;
    u8   wire[PACKET_MAX_SIZE];
    bool valid;
} NetReorderSlot;

typedef struct {
    u32  seq;
    u32  len;
    u8   data[PACKET_MAX_SIZE];
    NetAddress dst;
    bool valid;
} NetRepReliablePending;

typedef struct {
    u32 send_seq;
    u32 last_recv_seq;
} NetRepUnreliableChannel;

typedef struct {
    u32 send_seq;
    u32 last_recv_seq;
    u32 next_ordered_seq;
    u32 reorder_pending;
    u32 reorder_delivered;
    u32 reorder_stale;
    u32 reorder_duplicate;
    NetReorderSlot slots[NET_REORDER_SLOTS];
} NetRepOrderedChannel;

/* R418: receive-side channel state keyed per peer address. Without it, all
 * senders shared rep->unreliable[]/rep->ordered[], so two peers' ordered /
 * seq-deduped packets collided in one sequence space and were dropped as
 * stale. Only the receive fields are used here; outgoing send_seq stays in
 * the shared channels below. Heap-allocated in net_replicator_init (one block
 * of NET_REP_MAX_PEERS slots) so NetReplicator doesn't grow by ~1.4MB inline. */
typedef struct {
    NetAddress               addr;
    bool                     valid;
    u32                      last_seen_ms;  /* R423: activity stamp for LRU eviction */
    u32                      ack_to_send;   /* highest contiguous reliable sequence from this peer */
    u32                      ack_next_seq;  /* next sequence needed to advance cumulative ACK */
    u8                       ack_pending;   /* R455: received bits for [ack_next_seq, +8) */
    bool                     ack_initialized;
    NetRepUnreliableChannel  unreliable[NET_PKT_MAX];
    NetRepOrderedChannel     ordered[NET_PKT_MAX];
} NetRepPeerChannel;

/* R456: outgoing sequence state cannot share the evictable receive/reorder
 * table above: a receive-side LRU replacement must never restart an active
 * reliable destination's sequence space. */
typedef struct {
    NetAddress               addr;
    bool                     valid;
    u32                      last_seen_ms;
    u32                      unreliable_send_seq[NET_PKT_MAX];
    u32                      ordered_send_seq[NET_PKT_MAX];
} NetRepPeerSendState;

typedef struct {
    NetSocket                *socket;
    NetRepUnreliableChannel  unreliable[NET_PKT_MAX];
    NetRepOrderedChannel     ordered[NET_PKT_MAX];
    NetRepPeerChannel        *peer_channels;  /* R418: per-sender recv state (calloc'd in init) */
    NetRepPeerSendState      send_peers[NET_REP_MAX_PEERS]; /* R456: bounded per-destination wire sequences */
    NetRepReliablePending    reliable_window[NET_RELIABLE_WINDOW]; /* R434: in-flight reliable slots */
    u32                      reliable_dropped;  /* R434: reliable sends rejected (window full) */
    u32                      last_peer_ack;   /* peer's ack of OUR packets (clears our pending) */
    u32                      ack_to_send;     /* legacy address-less feed() cumulative ACK */
    u32                      ack_next_seq;
    u8                       ack_pending;
    bool                     ack_initialized;
    bool                     seq_dedup;
    bool                     reliable_retry;
    bool                     ordered_layer;
    bool                     owns_socket;
    u32                      retry_count;
    u32                      hb_sent;
    u32                      hb_recv;
    u32                      hb_echo_sent;
    u32                      hb_roundtrip_recv;
    f32                      hb_last_rtt_ms;
    f32                      hb_roundtrip_ms;
    bool                     hb_echo_reply;
    NetRepPeerStats          peers[NET_REP_MAX_PEERS];
    u32                      peer_count;
    u32                      peer_evict_ms;
    u32                      peer_evicted;
} NetReplicator;

bool net_replicator_init(NetReplicator *rep, u16 bind_port);
void net_replicator_shutdown(NetReplicator *rep);

i32 net_replicator_broadcast(NetReplicator *rep,
                             const NetTransformSnapshot *snapshots, u32 count,
                             const NetAddress *dst);

i32 net_replicator_send_heartbeat(NetReplicator *rep, const NetAddress *dst, u32 send_time_ms);
i32 net_replicator_send_heartbeat_ack(NetReplicator *rep, const NetAddress *dst,
                                      u32 send_time_ms, u32 echo_seq);

i32 net_replicator_retry_pending(NetReplicator *rep);

i32 net_replicator_recv(NetReplicator *rep,
                        NetTransformSnapshot *out, u32 max_count, u32 *out_count,
                        NetAddress *from);

i32 net_replicator_feed(NetReplicator *rep, const u8 *wire, u32 len,
                        NetTransformSnapshot *out, u32 max_count, u32 *out_count);

i32 net_replicator_feed_from(NetReplicator *rep, const u8 *wire, u32 len,
                             const NetAddress *reply_to,
                             NetTransformSnapshot *out, u32 max_count, u32 *out_count);

u32 net_replicator_peer_count(const NetReplicator *rep);
const NetRepPeerStats *net_replicator_peer_at(const NetReplicator *rep, u32 index);
void net_replicator_peer_evict_stale(NetReplicator *rep, u32 now_ms);
bool net_replicator_peer_save(const NetReplicator *rep, const char *path);
bool net_replicator_peer_load(NetReplicator *rep, const char *path);
bool net_replicator_peer_save_dir(const NetReplicator *rep, const char *dir);
bool net_replicator_peer_load_dir(NetReplicator *rep, const char *dir);
bool net_replicator_peer_save_delta(NetReplicator *rep, const char *path);
bool net_replicator_peer_load_delta(NetReplicator *rep, const char *path);

#endif /* NET_REPLICATION_H */
