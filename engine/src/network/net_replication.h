#ifndef NET_REPLICATION_H
#define NET_REPLICATION_H

#include "../core/types.h"
#include "network.h"
#include "packet.h"

#define NET_PKT_TRANSFORM_SNAPSHOT 1u
#define NET_PKT_HEARTBEAT          2u
#define NET_PKT_HEARTBEAT_ACK      3u
#define NET_PKT_MAX                4u
#define NET_REPL_MAX_SNAPSHOTS     64u
#define NET_REORDER_SLOTS          32u
#define NET_REP_MAX_PEERS          8u

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

typedef struct {
    NetSocket                *socket;
    NetRepUnreliableChannel  unreliable[NET_PKT_MAX];
    NetRepOrderedChannel     ordered[NET_PKT_MAX];
    NetRepReliablePending    reliable_pending;
    u32                      last_peer_ack;   /* peer's ack of OUR packets (clears our pending) */
    u32                      ack_to_send;     /* highest reliable seq WE received (echoed as outgoing ack) */
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
