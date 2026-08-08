/* ==========================================================================
 *  test_net_replication.c — Transform snapshot unreliable UDP broadcast.
 * ========================================================================== */

#include "test_framework.h"
#include <network/net_replication.h>
#include <platform/time.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#if !defined(ENGINE_PLATFORM_WINDOWS)
#include <sys/stat.h>
#endif

/* R444: a fixed UDP TEST_PORT collided across parallel ctest processes
 * (same-tree -j and cross-tree alike) — bind failed and every loopback test
 * fell over. Derive a per-process 16-port block from the pid (tests add
 * +0..+10 offsets on top of TEST_PORT, so the block must be wider than the
 * max offset or consecutive pids overlap each other's ports). Range check:
 * 23000 + 2599*16 = 64584, +10 < 65535. */
#define TEST_PORT ((u16)(23000u + ((u32)getpid() % 2600u) * 16u))

static void feed_ack(NetReplicator *rep, u32 ack);
static void feed_ack_from(NetReplicator *rep, u32 ack, const NetAddress *from);

#if !defined(ENGINE_PLATFORM_WINDOWS)
static bool make_deep_dir(char *dir, usize cap, char *base, usize base_cap,
                          usize target_len) {
    test_tmp(base, base_cap, "r477_netrep_dir");
    if (mkdir(base, 0755) != 0) return false;
    int n = snprintf(dir, cap, "%s", base);
    if (n < 0 || (usize)n >= cap || (usize)n > target_len) return false;
    while ((usize)n < target_len) {
        usize remaining = target_len - (usize)n;
        if (remaining < 2) return false;
        usize part_len = remaining - 1u;
        if (part_len > 80u) part_len = 80u;
        dir[n++] = '/';
        memset(dir + n, 'a', part_len);
        n += (int)part_len;
        dir[n] = '\0';
        if (mkdir(dir, 0755) != 0) return false;
    }
    return true;
}

static void remove_deep_dir(char *dir, const char *base) {
    for (;;) {
        rmdir(dir);
        if (strcmp(dir, base) == 0) break;
        char *slash = strrchr(dir, '/');
        if (!slash) break;
        *slash = '\0';
    }
}
#endif

TEST(replicator_init_shutdown)
{
    ASSERT_TRUE(net_init());
    NetReplicator rep = {0};
    ASSERT_TRUE(net_replicator_init(&rep, 0));
    net_replicator_shutdown(&rep);
    net_shutdown();
}

TEST(transform_snapshot_loopback)
{
    ASSERT_TRUE(net_init());

    NetReplicator recv_rep = {0};
    ASSERT_TRUE(net_replicator_init(&recv_rep, (u16)TEST_PORT));
    net_set_nonblocking(recv_rep.socket, true);

    NetReplicator send_rep = {0};
    ASSERT_TRUE(net_replicator_init(&send_rep, 0));

    NetAddress dst;
    ASSERT_TRUE(net_address_resolve("127.0.0.1", (u16)TEST_PORT, &dst));

    NetTransformSnapshot in[2] = {
        { .entity_id = 42u, .position = { 1.0f, 2.0f, 3.0f } },
        { .entity_id = 99u, .position = { -1.0f, 0.5f, 8.0f } },
    };

    i32 sent = net_replicator_broadcast(&send_rep, in, 2u, &dst);
    ASSERT_TRUE(sent > 0);
    ASSERT_EQ(send_rep.unreliable[NET_PKT_TRANSFORM_SNAPSHOT].send_seq, 2u);

    NetTransformSnapshot out[4] = {0};
    u32 out_count = 0u;
    NetAddress from = {0};
    i32 received = net_replicator_recv(&recv_rep, out, 4u, &out_count, &from);
    ASSERT_TRUE(received > 0);
    ASSERT_EQ(out_count, 2u);
    ASSERT_EQ(out[0].entity_id, 42u);
    ASSERT_FLOAT_EQ(out[0].position[0], 1.0f, 0.001f);
    ASSERT_FLOAT_EQ(out[0].position[1], 2.0f, 0.001f);
    ASSERT_FLOAT_EQ(out[0].position[2], 3.0f, 0.001f);
    ASSERT_EQ(out[1].entity_id, 99u);
    ASSERT_FLOAT_EQ(out[1].position[0], -1.0f, 0.001f);

    net_replicator_shutdown(&send_rep);
    net_replicator_shutdown(&recv_rep);
    net_shutdown();
}

TEST(reliable_retry_pending)
{
    ASSERT_TRUE(net_init());

    NetReplicator send_rep = {0};
    ASSERT_TRUE(net_replicator_init(&send_rep, 0));
    send_rep.reliable_retry = true;

    NetAddress dst;
    ASSERT_TRUE(net_address_resolve("127.0.0.1", (u16)(TEST_PORT + 1u), &dst));

    NetTransformSnapshot snap = { .entity_id = 7u, .position = { 0.0f, 1.0f, 2.0f } };
    ASSERT_TRUE(net_replicator_broadcast(&send_rep, &snap, 1u, &dst) > 0);
    ASSERT_TRUE(send_rep.reliable_window[0].valid);

    ASSERT_TRUE(net_replicator_retry_pending(&send_rep) > 0);
    ASSERT_EQ(send_rep.retry_count, 1u);

    feed_ack(&send_rep, send_rep.reliable_window[0].seq);
    ASSERT_TRUE(net_replicator_retry_pending(&send_rep) == 0);
    ASSERT_FALSE(send_rep.reliable_window[0].valid);

    net_replicator_shutdown(&send_rep);
    net_shutdown();
}

static u32 build_snap_wire(u8 *out, u32 seq, u8 flags, u8 type,
                           u32 entity_id, f32 x, f32 y, f32 z) {
    PacketBuffer buf;
    packet_begin(&buf, type, flags);
    packet_write_u16(&buf, 1);
    packet_write_u32(&buf, entity_id);
    packet_write_f32(&buf, x);
    packet_write_f32(&buf, y);
    packet_write_f32(&buf, z);
    u32 len = packet_finish(&buf, seq, 0);
    memcpy(out, buf.data, len);
    return len;
}

static u32 build_ordered_snap_wire(u8 *out, u32 seq, u32 entity_id, f32 x, f32 y, f32 z) {
    return build_snap_wire(out, seq, (u8)PACKET_ORDERED, (u8)NET_PKT_TRANSFORM_SNAPSHOT,
                           entity_id, x, y, z);
}

static u32 build_ordered_empty_wire(u8 *out, u32 seq) {
    /* An ordered TRANSFORM_SNAPSHOT frame declaring zero snapshots (n = 0). */
    PacketBuffer buf;
    packet_begin(&buf, (u8)NET_PKT_TRANSFORM_SNAPSHOT, (u8)PACKET_ORDERED);
    packet_write_u16(&buf, 0);
    u32 len = packet_finish(&buf, seq, 0);
    memcpy(out, buf.data, len);
    return len;
}

static u32 build_heartbeat_wire(u8 *out, u32 seq, u32 send_time_ms) {
    PacketBuffer buf;
    packet_begin(&buf, (u8)NET_PKT_HEARTBEAT, (u8)PACKET_UNRELIABLE);
    packet_write_u32(&buf, send_time_ms);
    u32 len = packet_finish(&buf, seq, 0);
    memcpy(out, buf.data, len);
    return len;
}

static u32 build_heartbeat_ack_wire(u8 *out, u32 seq, u32 send_time_ms, u32 echo_seq) {
    PacketBuffer buf;
    packet_begin(&buf, (u8)NET_PKT_HEARTBEAT_ACK, (u8)PACKET_UNRELIABLE);
    packet_write_u32(&buf, send_time_ms);
    packet_write_u32(&buf, echo_seq);
    u32 len = packet_finish(&buf, seq, 0);
    memcpy(out, buf.data, len);
    return len;
}

TEST(ordered_reorder_buffer)
{
    NetReplicator rep = {0};
    ASSERT_TRUE(net_replicator_init(&rep, 0));
    rep.ordered_layer = true;

    u8 wire1[PACKET_MAX_SIZE], wire2[PACKET_MAX_SIZE];
    u32 len1 = build_ordered_snap_wire(wire1, 1u, 10u, 1.0f, 2.0f, 3.0f);
    u32 len2 = build_ordered_snap_wire(wire2, 2u, 10u, 4.0f, 5.0f, 6.0f);

    NetTransformSnapshot out[4] = {0};
    u32 out_count = 0u;

    ASSERT_TRUE(net_replicator_feed(&rep, wire2, len2, out, 4u, &out_count) > 0);
    ASSERT_EQ(out_count, 0u);
    ASSERT_EQ(rep.ordered[NET_PKT_TRANSFORM_SNAPSHOT].reorder_pending, 1u);

    ASSERT_TRUE(net_replicator_feed(&rep, wire1, len1, out, 4u, &out_count) > 0);
    ASSERT_TRUE(out_count >= 1u);
    ASSERT_FLOAT_EQ(out[0].position[0], 4.0f, 0.001f);
    ASSERT_FLOAT_EQ(out[0].position[1], 5.0f, 0.001f);
    ASSERT_FLOAT_EQ(out[0].position[2], 6.0f, 0.001f);
    ASSERT_EQ(rep.ordered[NET_PKT_TRANSFORM_SNAPSHOT].reorder_delivered, 1u);
    ASSERT_EQ(rep.ordered[NET_PKT_TRANSFORM_SNAPSHOT].reorder_pending, 0u);

    net_replicator_shutdown(&rep);
}

TEST(ordered_reorder_out_of_window_no_stall)
{
    /* R250: a future packet >= next+NET_REORDER_SLOTS aliases (seq%SLOTS) onto an
     * occupied in-window slot. The old code overwrote it, losing a still-needed
     * packet and stalling the ordered stream.
     * R432: with the head seq lost and the window non-empty, simply dropping
     * the out-of-window packet stalled the channel permanently (the head could
     * never re-arrive once the sender was >=SLOTS ahead). The packet now
     * triggers a resync instead: the buffered window is discarded (never
     * aliased/overwritten as in the pre-R250 bug) and the packet is delivered
     * immediately; the stream continues from the resynced sequence. */
    NetReplicator rep = {0};
    ASSERT_TRUE(net_replicator_init(&rep, 0));
    rep.ordered_layer = true;

    u8 w2[PACKET_MAX_SIZE], w_far[PACKET_MAX_SIZE], w1[PACKET_MAX_SIZE], w_next[PACKET_MAX_SIZE];
    u32 l2   = build_ordered_snap_wire(w2,   2u,               10u, 4.0f, 5.0f, 6.0f);
    /* seq 2 + NET_REORDER_SLOTS aliases the same slot as seq 2 (2 % 32). */
    u32 lfar = build_ordered_snap_wire(w_far, 2u + NET_REORDER_SLOTS, 10u, 9.0f, 9.0f, 9.0f);
    u32 l1   = build_ordered_snap_wire(w1,   1u,               10u, 1.0f, 2.0f, 3.0f);
    u32 lnext = build_ordered_snap_wire(w_next, 2u + NET_REORDER_SLOTS + 1u, 10u, 7.0f, 8.0f, 9.0f);

    NetTransformSnapshot out[4] = {0};
    u32 out_count = 0u;

    /* Buffer seq 2 (waiting for seq 1). */
    ASSERT_TRUE(net_replicator_feed(&rep, w2, l2, out, 4u, &out_count) > 0);
    ASSERT_EQ(out_count, 0u);
    ASSERT_EQ(rep.ordered[NET_PKT_TRANSFORM_SNAPSHOT].reorder_pending, 1u);

    /* R432: the out-of-window seq resyncs (discarding the buffered window —
     * NOT overwriting seq 2's slot via aliasing) and is delivered at once. */
    out_count = 0u;
    ASSERT_TRUE(net_replicator_feed(&rep, w_far, lfar, out, 4u, &out_count) > 0);
    ASSERT_TRUE(out_count >= 1u);
    ASSERT_FLOAT_EQ(out[0].position[0], 9.0f, 0.001f);
    ASSERT_EQ(rep.ordered[NET_PKT_TRANSFORM_SNAPSHOT].next_ordered_seq, 2u + NET_REORDER_SLOTS + 1u);
    ASSERT_EQ(rep.ordered[NET_PKT_TRANSFORM_SNAPSHOT].reorder_pending, 0u);

    /* A belated seq 1 is now stale and must be dropped without disturbing the
     * resynced stream. */
    out_count = 0u;
    ASSERT_TRUE(net_replicator_feed(&rep, w1, l1, out, 4u, &out_count) > 0);
    ASSERT_EQ(out_count, 0u);
    ASSERT_EQ(rep.ordered[NET_PKT_TRANSFORM_SNAPSHOT].next_ordered_seq, 2u + NET_REORDER_SLOTS + 1u);

    /* The stream continues normally from the resynced sequence — no stall. */
    out_count = 0u;
    ASSERT_TRUE(net_replicator_feed(&rep, w_next, lnext, out, 4u, &out_count) > 0);
    ASSERT_TRUE(out_count >= 1u);
    ASSERT_FLOAT_EQ(out[0].position[0], 7.0f, 0.001f);
    ASSERT_FLOAT_EQ(out[0].position[1], 8.0f, 0.001f);
    ASSERT_FLOAT_EQ(out[0].position[2], 9.0f, 0.001f);
    ASSERT_EQ(rep.ordered[NET_PKT_TRANSFORM_SNAPSHOT].next_ordered_seq, 2u + NET_REORDER_SLOTS + 2u);

    net_replicator_shutdown(&rep);
}

TEST(ordered_reorder_zero_snapshot_no_stall)
{
    /* R299: a buffered ordered packet carrying 0 snapshots must not halt the
     * drain of subsequent consecutive buffered packets. The old drain loop broke
     * on `late_count == 0`, so an empty frame in the middle of the reorder buffer
     * left later packets stuck (reorder_pending never reaching 0) and the ordered
     * stream stalled forever. A foreign/forged peer can send such a frame. */
    NetReplicator rep = {0};
    ASSERT_TRUE(net_replicator_init(&rep, 0));
    rep.ordered_layer = true;

    u8 w_empty[PACKET_MAX_SIZE], w3[PACKET_MAX_SIZE], w1[PACKET_MAX_SIZE];
    u32 le = build_ordered_empty_wire(w_empty, 2u);                 /* seq 2, 0 snapshots */
    u32 l3 = build_ordered_snap_wire(w3, 3u, 30u, 7.0f, 8.0f, 9.0f);
    u32 l1 = build_ordered_snap_wire(w1, 1u, 10u, 1.0f, 2.0f, 3.0f);

    NetTransformSnapshot out[4] = {0};
    u32 out_count = 0u;

    /* Buffer seq 2 (empty) and seq 3 while waiting for the gap at seq 1. */
    ASSERT_TRUE(net_replicator_feed(&rep, w_empty, le, out, 4u, &out_count) > 0);
    ASSERT_TRUE(net_replicator_feed(&rep, w3, l3, out, 4u, &out_count) > 0);
    ASSERT_EQ(rep.ordered[NET_PKT_TRANSFORM_SNAPSHOT].reorder_pending, 2u);

    /* seq 1 arrives → deliver 1, then drain seq 2 (empty) AND seq 3. The empty
     * frame must not stop the drain: the buffer fully empties and seq 3's payload
     * reaches the caller. Before the fix reorder_pending stuck at 1 and seq 3 was
     * never delivered. */
    out_count = 0u;
    ASSERT_TRUE(net_replicator_feed(&rep, w1, l1, out, 4u, &out_count) > 0);
    ASSERT_EQ(rep.ordered[NET_PKT_TRANSFORM_SNAPSHOT].reorder_pending, 0u);
    ASSERT_EQ(rep.ordered[NET_PKT_TRANSFORM_SNAPSHOT].reorder_delivered, 2u);
    ASSERT_TRUE(out_count >= 1u);
    ASSERT_FLOAT_EQ(out[0].position[0], 7.0f, 0.001f);
    ASSERT_FLOAT_EQ(out[0].position[1], 8.0f, 0.001f);
    ASSERT_FLOAT_EQ(out[0].position[2], 9.0f, 0.001f);

    net_replicator_shutdown(&rep);
}

TEST(ordered_resync_after_large_seq_jump)
{
    /* R427: a >= NET_REORDER_SLOTS forward jump with an empty reorder window
     * must resync next_ordered_seq and deliver, not drop — otherwise the
     * channel stalled permanently (next_ordered_seq only advances on exact-seq
     * delivery). Trigger: a >=32-packet loss burst, or an R423 peer-channel
     * eviction resetting an active peer's channel mid-stream. */
    NetReplicator rep = {0};
    ASSERT_TRUE(net_replicator_init(&rep, 0));
    rep.ordered_layer = true;

    u8 w_far[PACKET_MAX_SIZE], w_next[PACKET_MAX_SIZE];
    u32 seq_far = 1u + NET_REORDER_SLOTS + 5u;
    u32 lfar  = build_ordered_snap_wire(w_far,  seq_far,      10u, 1.0f, 2.0f, 3.0f);
    u32 lnext = build_ordered_snap_wire(w_next, seq_far + 1u, 10u, 4.0f, 5.0f, 6.0f);

    NetTransformSnapshot out[4] = {0};
    u32 out_count = 0u;

    /* The jump packet is delivered immediately and resyncs the channel. */
    ASSERT_TRUE(net_replicator_feed(&rep, w_far, lfar, out, 4u, &out_count) > 0);
    ASSERT_TRUE(out_count >= 1u);
    ASSERT_FLOAT_EQ(out[0].position[0], 1.0f, 0.001f);
    ASSERT_EQ(rep.ordered[NET_PKT_TRANSFORM_SNAPSHOT].next_ordered_seq, seq_far + 1u);

    /* The stream continues normally from the resynced sequence — no stall. */
    out_count = 0u;
    ASSERT_TRUE(net_replicator_feed(&rep, w_next, lnext, out, 4u, &out_count) > 0);
    ASSERT_TRUE(out_count >= 1u);
    ASSERT_FLOAT_EQ(out[0].position[0], 4.0f, 0.001f);
    ASSERT_EQ(rep.ordered[NET_PKT_TRANSFORM_SNAPSHOT].next_ordered_seq, seq_far + 2u);

    net_replicator_shutdown(&rep);
}

TEST(ordered_resync_nonempty_window_head_loss)
{
    /* R432: the R427 resync only fired on a completely empty window. If the
     * head seq (next_ordered_seq) is lost while later packets stay buffered
     * and the sender keeps sending, every subsequent packet lands >= SLOTS
     * ahead and was dropped as stale — the head never re-arrives, so the
     * channel stalled permanently. The >=SLOTS packet must now resync
     * (accepting loss of the buffered window) and be delivered. */
    NetReplicator rep = {0};
    ASSERT_TRUE(net_replicator_init(&rep, 0));
    rep.ordered_layer = true;

    u8 w2[PACKET_MAX_SIZE], w3[PACKET_MAX_SIZE], w_far[PACKET_MAX_SIZE], w_next[PACKET_MAX_SIZE];
    u32 l2 = build_ordered_snap_wire(w2, 2u, 10u, 7.0f, 8.0f, 9.0f);
    u32 l3 = build_ordered_snap_wire(w3, 3u, 10u, 7.0f, 8.0f, 9.0f);
    u32 seq_far = 1u + NET_REORDER_SLOTS + 5u;
    u32 lfar  = build_ordered_snap_wire(w_far,  seq_far,      10u, 1.0f, 2.0f, 3.0f);
    u32 lnext = build_ordered_snap_wire(w_next, seq_far + 1u, 10u, 4.0f, 5.0f, 6.0f);

    NetTransformSnapshot out[4] = {0};
    u32 out_count = 0u;

    /* Buffer seqs 2 and 3; the head seq 1 is lost and never arrives. */
    ASSERT_TRUE(net_replicator_feed(&rep, w2, l2, out, 4u, &out_count) > 0);
    ASSERT_TRUE(net_replicator_feed(&rep, w3, l3, out, 4u, &out_count) > 0);
    ASSERT_EQ(rep.ordered[NET_PKT_TRANSFORM_SNAPSHOT].reorder_pending, 2u);

    /* The sender is now >= SLOTS ahead: must resync and deliver, not drop. */
    out_count = 0u;
    ASSERT_TRUE(net_replicator_feed(&rep, w_far, lfar, out, 4u, &out_count) > 0);
    ASSERT_TRUE(out_count >= 1u);
    ASSERT_FLOAT_EQ(out[0].position[0], 1.0f, 0.001f);
    ASSERT_EQ(rep.ordered[NET_PKT_TRANSFORM_SNAPSHOT].next_ordered_seq, seq_far + 1u);
    /* The stale buffered window was discarded by the resync. */
    ASSERT_EQ(rep.ordered[NET_PKT_TRANSFORM_SNAPSHOT].reorder_pending, 0u);

    /* The stream continues normally from the resynced sequence — no stall. */
    out_count = 0u;
    ASSERT_TRUE(net_replicator_feed(&rep, w_next, lnext, out, 4u, &out_count) > 0);
    ASSERT_TRUE(out_count >= 1u);
    ASSERT_FLOAT_EQ(out[0].position[0], 4.0f, 0.001f);
    ASSERT_EQ(rep.ordered[NET_PKT_TRANSFORM_SNAPSHOT].next_ordered_seq, seq_far + 2u);

    net_replicator_shutdown(&rep);
}

TEST(reliable_ordered_combined)
{
    ASSERT_TRUE(net_init());

    NetReplicator send_rep = {0};
    ASSERT_TRUE(net_replicator_init(&send_rep, 0));
    send_rep.reliable_retry = true;
    send_rep.ordered_layer = true;

    NetAddress dst;
    ASSERT_TRUE(net_address_resolve("127.0.0.1", (u16)(TEST_PORT + 2u), &dst));

    NetTransformSnapshot snap = { .entity_id = 3u, .position = { 9.0f, 8.0f, 7.0f } };
    ASSERT_TRUE(net_replicator_broadcast(&send_rep, &snap, 1u, &dst) > 0);
    ASSERT_TRUE(send_rep.reliable_window[0].valid);
    ASSERT_EQ(send_rep.reliable_window[0].data[11], (u8)(PACKET_RELIABLE | PACKET_ORDERED));
    ASSERT_EQ(send_rep.ordered[NET_PKT_TRANSFORM_SNAPSHOT].send_seq, 2u);

    NetReplicator recv_rep = {0};
    ASSERT_TRUE(net_replicator_init(&recv_rep, 0));
    recv_rep.ordered_layer = true;

    u8 wire2[PACKET_MAX_SIZE], wire1[PACKET_MAX_SIZE];
    u8 ro_flags = (u8)(PACKET_ORDERED | PACKET_RELIABLE);
    u32 len2 = build_snap_wire(wire2, 2u, ro_flags, (u8)NET_PKT_TRANSFORM_SNAPSHOT,
                               3u, 2.0f, 2.0f, 2.0f);
    u32 len1 = build_snap_wire(wire1, 1u, ro_flags, (u8)NET_PKT_TRANSFORM_SNAPSHOT,
                               3u, 1.0f, 1.0f, 1.0f);

    NetTransformSnapshot out[4] = {0};
    u32 out_count = 0u;

    ASSERT_TRUE(net_replicator_feed(&recv_rep, wire2, len2, out, 4u, &out_count) > 0);
    ASSERT_EQ(out_count, 0u);

    ASSERT_TRUE(net_replicator_feed(&recv_rep, wire1, len1, out, 4u, &out_count) > 0);
    ASSERT_TRUE(out_count >= 1u);
    ASSERT_FLOAT_EQ(out[0].position[0], 2.0f, 0.001f);

    ASSERT_TRUE(net_replicator_feed(&recv_rep, wire1, len1, out, 4u, &out_count) > 0);
    ASSERT_EQ(out_count, 0u);
    ASSERT_TRUE(recv_rep.ordered[NET_PKT_TRANSFORM_SNAPSHOT].reorder_duplicate >= 1u);

    net_replicator_shutdown(&send_rep);
    net_replicator_shutdown(&recv_rep);
    net_shutdown();
}

/* R323: a packet's `ack` field acknowledges the SENDER's sequence. On receiving a
 * reliable packet the replicator must record the peer's SEQUENCE as the value it
 * will echo back (ack_to_send) — NOT the peer's ack field. The old code echoed
 * last_peer_ack (= the peer's ack of us), so a reliable packet was never actually
 * acknowledged and retry_pending retransmitted forever. */
TEST(reliable_ack_echoes_received_sequence)
{
    ASSERT_TRUE(net_init());
    NetReplicator rep = {0};
    ASSERT_TRUE(net_replicator_init(&rep, 0));

    /* Peer's reliable snapshot: header sequence=7, ack=99. */
    PacketBuffer buf;
    packet_begin(&buf, (u8)NET_PKT_TRANSFORM_SNAPSHOT, (u8)PACKET_RELIABLE);
    packet_write_u16(&buf, 1);
    packet_write_u32(&buf, 5u);
    packet_write_f32(&buf, 0.0f);
    packet_write_f32(&buf, 0.0f);
    packet_write_f32(&buf, 0.0f);
    u32 len = packet_finish(&buf, 7u, 99u);

    NetTransformSnapshot out[4] = {0};
    u32 oc = 0u;
    ASSERT_TRUE(net_replicator_feed(&rep, buf.data, len, out, 4u, &oc) > 0);

    /* We must acknowledge the peer's sequence (7), not echo its ack (99). */
    ASSERT_EQ(rep.ack_to_send, 7u);
    /* last_peer_ack still records the peer's ack of us (99) for retry self-check. */
    ASSERT_EQ(rep.last_peer_ack, 99u);

    net_replicator_shutdown(&rep);
    net_shutdown();
}

TEST(reliable_ack_is_scoped_to_destination)
{
    /* R454: receiving a reliable frame from A must not put A's sequence into
     * a later packet sent to B. A cumulative ack is meaningful only to the
     * peer whose sequence space it acknowledges. */
    ASSERT_TRUE(net_init());

    NetReplicator rep = {0}, receiver_a = {0}, receiver_b = {0};
    ASSERT_TRUE(net_replicator_init(&rep, 0));
    ASSERT_TRUE(net_replicator_init(&receiver_a, (u16)(TEST_PORT + 12u)));
    ASSERT_TRUE(net_replicator_init(&receiver_b, (u16)(TEST_PORT + 13u)));

    NetAddress peer_a, peer_b;
    ASSERT_TRUE(net_address_resolve("127.0.0.1", (u16)(TEST_PORT + 12u), &peer_a));
    ASSERT_TRUE(net_address_resolve("127.0.0.1", (u16)(TEST_PORT + 13u), &peer_b));

    u8 reliable_from_a[PACKET_MAX_SIZE];
    u32 reliable_len = build_snap_wire(reliable_from_a, 1u, (u8)PACKET_RELIABLE,
                                       (u8)NET_PKT_TRANSFORM_SNAPSHOT,
                                       1u, 0.0f, 0.0f, 0.0f);
    NetTransformSnapshot out[1] = {0};
    u32 out_count = 0u;
    ASSERT_TRUE(net_replicator_feed_from(&rep, reliable_from_a, reliable_len, &peer_a,
                                         out, 1u, &out_count) > 0);

    NetTransformSnapshot snap = { .entity_id = 2u, .position = {0} };
    ASSERT_TRUE(net_replicator_broadcast(&rep, &snap, 1u, &peer_b) > 0);

    u8 sent[PACKET_MAX_SIZE];
    NetAddress from = {0};
    i32 sent_len = net_recvfrom(receiver_b.socket, sent, sizeof(sent), &from);
    ASSERT_TRUE(sent_len > 0);
    PacketHeader header;
    ASSERT_TRUE(packet_parse_header(sent, (u32)sent_len, &header));
    ASSERT_EQ(header.ack, 0u); /* B has not sent us a reliable sequence. */

    ASSERT_TRUE(net_replicator_broadcast(&rep, &snap, 1u, &peer_a) > 0);
    sent_len = net_recvfrom(receiver_a.socket, sent, sizeof(sent), &from);
    ASSERT_TRUE(sent_len > 0);
    ASSERT_TRUE(packet_parse_header(sent, (u32)sent_len, &header));
    ASSERT_EQ(header.ack, 1u); /* The reliable sequence is echoed only to A. */

    net_replicator_shutdown(&receiver_b);
    net_replicator_shutdown(&receiver_a);
    net_replicator_shutdown(&rep);
    net_shutdown();
}

TEST(reliable_ack_waits_for_contiguous_sequence)
{
    /* R455: header ACK is cumulative. After seq 1, seeing reliable seq 3
     * before seq 2 cannot acknowledge 3, otherwise a lost seq 2 is silently
     * retired by the sender and never retried. */
    ASSERT_TRUE(net_init());

    NetReplicator rep = {0}, receiver = {0};
    ASSERT_TRUE(net_replicator_init(&rep, 0));
    ASSERT_TRUE(net_replicator_init(&receiver, (u16)(TEST_PORT + 12u)));

    NetAddress peer_a;
    ASSERT_TRUE(net_address_resolve("127.0.0.1", (u16)(TEST_PORT + 12u), &peer_a));

    u8 seq1[PACKET_MAX_SIZE], seq2[PACKET_MAX_SIZE], seq3[PACKET_MAX_SIZE];
    u32 len1 = build_snap_wire(seq1, 1u, (u8)PACKET_RELIABLE,
                               (u8)NET_PKT_TRANSFORM_SNAPSHOT,
                               1u, 0.0f, 0.0f, 0.0f);
    u32 len2 = build_snap_wire(seq2, 2u, (u8)PACKET_RELIABLE,
                               (u8)NET_PKT_TRANSFORM_SNAPSHOT,
                               2u, 0.0f, 0.0f, 0.0f);
    u32 len3 = build_snap_wire(seq3, 3u, (u8)PACKET_RELIABLE,
                               (u8)NET_PKT_TRANSFORM_SNAPSHOT,
                               3u, 0.0f, 0.0f, 0.0f);
    NetTransformSnapshot out[1] = {0};
    u32 out_count = 0u;
    ASSERT_TRUE(net_replicator_feed_from(&rep, seq1, len1, &peer_a,
                                         out, 1u, &out_count) > 0);
    ASSERT_TRUE(net_replicator_feed_from(&rep, seq3, len3, &peer_a,
                                         out, 1u, &out_count) > 0);

    NetTransformSnapshot snap = { .entity_id = 3u, .position = {0} };
    ASSERT_TRUE(net_replicator_broadcast(&rep, &snap, 1u, &peer_a) > 0);

    u8 sent[PACKET_MAX_SIZE];
    NetAddress from = {0};
    i32 sent_len = net_recvfrom(receiver.socket, sent, sizeof(sent), &from);
    ASSERT_TRUE(sent_len > 0);
    PacketHeader header;
    ASSERT_TRUE(packet_parse_header(sent, (u32)sent_len, &header));
    ASSERT_EQ(header.ack, 1u); /* seq 2 is still missing. */

    ASSERT_TRUE(net_replicator_feed_from(&rep, seq2, len2, &peer_a,
                                         out, 1u, &out_count) > 0);
    ASSERT_TRUE(net_replicator_broadcast(&rep, &snap, 1u, &peer_a) > 0);
    sent_len = net_recvfrom(receiver.socket, sent, sizeof(sent), &from);
    ASSERT_TRUE(sent_len > 0);
    ASSERT_TRUE(packet_parse_header(sent, (u32)sent_len, &header));
    ASSERT_EQ(header.ack, 3u); /* Now seqs 1 through 3 are contiguous. */

    net_replicator_shutdown(&receiver);
    net_replicator_shutdown(&rep);
    net_shutdown();
}

TEST(reliable_send_sequence_survives_receive_peer_eviction)
{
    /* R456: outgoing reliable sequence state must outlive the independently
     * evictable receive-channel slot for the same address. Otherwise a spoofed
     * sender flood can make the next packet to A restart at seq 1. */
    ASSERT_TRUE(net_init());

    NetReplicator rep = {0}, receiver = {0};
    ASSERT_TRUE(net_replicator_init(&rep, 0));
    ASSERT_TRUE(net_replicator_init(&receiver, (u16)(TEST_PORT + 15u)));
    rep.reliable_retry = true;

    NetAddress peer_a;
    ASSERT_TRUE(net_address_resolve("127.0.0.1", (u16)(TEST_PORT + 15u), &peer_a));
    NetTransformSnapshot snap = { .entity_id = 4u, .position = {0} };
    ASSERT_TRUE(net_replicator_broadcast(&rep, &snap, 1u, &peer_a) > 0);

    u8 sent[PACKET_MAX_SIZE];
    NetAddress from = {0};
    i32 sent_len = net_recvfrom(receiver.socket, sent, sizeof(sent), &from);
    ASSERT_TRUE(sent_len > 0);
    PacketHeader header;
    ASSERT_TRUE(packet_parse_header(sent, (u32)sent_len, &header));
    ASSERT_EQ(header.sequence, 1u);

    u8 heartbeat[PACKET_MAX_SIZE];
    u32 heartbeat_len = build_heartbeat_wire(heartbeat, 1u, 0u);
    NetTransformSnapshot out[1] = {0};
    u32 out_count = 0u;
    for (u32 i = 0u; i < NET_REP_MAX_PEERS; i++) {
        NetAddress forged = {0};
        strncpy(forged.host, "127.0.0.1", sizeof(forged.host) - 1u);
        forged.port = (u16)(22000u + i);
        ASSERT_TRUE(net_replicator_feed_from(&rep, heartbeat, heartbeat_len, &forged,
                                             out, 1u, &out_count) > 0);
    }

    ASSERT_TRUE(net_replicator_broadcast(&rep, &snap, 1u, &peer_a) > 0);
    sent_len = net_recvfrom(receiver.socket, sent, sizeof(sent), &from);
    ASSERT_TRUE(sent_len > 0);
    ASSERT_TRUE(packet_parse_header(sent, (u32)sent_len, &header));
    ASSERT_EQ(header.sequence, 2u);

    net_replicator_shutdown(&receiver);
    net_replicator_shutdown(&rep);
    net_shutdown();
}

TEST(reliable_send_state_is_not_recycled_after_ack)
{
    /* R457: even an ACKed destination cannot have its sequence slot recycled:
     * the remote receiver can still retain its old sequence state. At fixed
     * capacity the ninth destination must fail, while A remains seq 2. */
    ASSERT_TRUE(net_init());

    NetReplicator rep = {0}, receiver = {0};
    ASSERT_TRUE(net_replicator_init(&rep, 0));
    ASSERT_TRUE(net_replicator_init(&receiver, (u16)(TEST_PORT + 15u)));
    rep.reliable_retry = true;

    NetAddress peer_a;
    ASSERT_TRUE(net_address_resolve("127.0.0.1", (u16)(TEST_PORT + 15u), &peer_a));
    NetTransformSnapshot snap = { .entity_id = 5u, .position = {0} };
    ASSERT_TRUE(net_replicator_broadcast(&rep, &snap, 1u, &peer_a) > 0);
    u8 sent[PACKET_MAX_SIZE];
    NetAddress from = {0};
    ASSERT_TRUE(net_recvfrom(receiver.socket, sent, sizeof(sent), &from) > 0);
    feed_ack_from(&rep, 1u, &peer_a);

    for (u32 i = 1u; i < NET_REP_MAX_PEERS; i++) {
        NetAddress peer = {0};
        strncpy(peer.host, "127.0.0.1", sizeof(peer.host) - 1u);
        peer.port = (u16)(22100u + i);
        ASSERT_TRUE(net_replicator_send_heartbeat(&rep, &peer, 0u) > 0);
    }

    NetAddress ninth = {0};
    strncpy(ninth.host, "127.0.0.1", sizeof(ninth.host) - 1u);
    ninth.port = 22200u;
    ASSERT_EQ(net_replicator_send_heartbeat(&rep, &ninth, 0u), NET_ERROR);

    ASSERT_TRUE(net_replicator_broadcast(&rep, &snap, 1u, &peer_a) > 0);
    i32 sent_len = net_recvfrom(receiver.socket, sent, sizeof(sent), &from);
    ASSERT_TRUE(sent_len > 0);
    PacketHeader header;
    ASSERT_TRUE(packet_parse_header(sent, (u32)sent_len, &header));
    ASSERT_EQ(header.sequence, 2u);

    net_replicator_shutdown(&receiver);
    net_replicator_shutdown(&rep);
    net_shutdown();
}

/* R323 end-to-end: the ack a receiver produces (from the sequence it received)
 * must clear the original sender's reliable_pending. Pre-R323 the receiver echoed
 * its own last_peer_ack (0 here), so this round-trip never cleared the pending. */
TEST(reliable_pending_cleared_via_peer_ack)
{
    ASSERT_TRUE(net_init());

    /* Receiver B gets A's reliable packet with sequence=5. */
    NetReplicator B = {0};
    ASSERT_TRUE(net_replicator_init(&B, 0));
    PacketBuffer bf;
    packet_begin(&bf, (u8)NET_PKT_TRANSFORM_SNAPSHOT, (u8)PACKET_RELIABLE);
    packet_write_u16(&bf, 1);
    packet_write_u32(&bf, 3u);
    packet_write_f32(&bf, 1.0f);
    packet_write_f32(&bf, 1.0f);
    packet_write_f32(&bf, 1.0f);
    u32 blen = packet_finish(&bf, 5u, 0u);
    NetTransformSnapshot bout[4] = {0};
    u32 boc = 0u;
    ASSERT_TRUE(net_replicator_feed(&B, bf.data, blen, bout, 4u, &boc) > 0);
    ASSERT_EQ(B.ack_to_send, 5u);

    /* Sender A has an outstanding reliable packet with sequence=5. */
    NetReplicator A = {0};
    ASSERT_TRUE(net_replicator_init(&A, 0));
    A.reliable_retry = true;
    A.reliable_window[0].valid = true;
    A.reliable_window[0].seq = 5u;

    /* B replies with a packet carrying ack = B.ack_to_send (=5). Feeding it to A
     * must clear A's pending — the acknowledgment round-trip fixed in R323. */
    PacketBuffer af;
    packet_begin(&af, (u8)NET_PKT_HEARTBEAT, (u8)PACKET_UNRELIABLE);
    packet_write_u32(&af, 0u);
    u32 alen = packet_finish(&af, 0u, B.ack_to_send);
    NetTransformSnapshot aout[4] = {0};
    u32 aoc = 0u;
    net_replicator_feed(&A, af.data, alen, aout, 4u, &aoc);
    ASSERT_FALSE(A.reliable_window[0].valid);

    net_replicator_shutdown(&A);
    net_replicator_shutdown(&B);
    net_shutdown();
}

TEST(dual_channel_sequences)
{
    ASSERT_TRUE(net_init());

    NetReplicator send_rep = {0};
    ASSERT_TRUE(net_replicator_init(&send_rep, 0));

    NetAddress dst;
    ASSERT_TRUE(net_address_resolve("127.0.0.1", (u16)(TEST_PORT + 3u), &dst));

    NetTransformSnapshot snap = { .entity_id = 5u, .position = { 1.0f, 0.0f, 0.0f } };
    ASSERT_TRUE(net_replicator_broadcast(&send_rep, &snap, 1u, &dst) > 0);
    ASSERT_EQ(send_rep.unreliable[NET_PKT_TRANSFORM_SNAPSHOT].send_seq, 2u);

    send_rep.ordered_layer = true;
    ASSERT_TRUE(net_replicator_broadcast(&send_rep, &snap, 1u, &dst) > 0);
    ASSERT_EQ(send_rep.ordered[NET_PKT_TRANSFORM_SNAPSHOT].send_seq, 2u);
    ASSERT_EQ(send_rep.unreliable[NET_PKT_TRANSFORM_SNAPSHOT].send_seq, 2u);

    NetReplicator recv_rep = {0};
    ASSERT_TRUE(net_replicator_init(&recv_rep, 0));
    recv_rep.ordered_layer = true;

    u8 wire_u[PACKET_MAX_SIZE], wire_o[PACKET_MAX_SIZE];
    u32 len_u = build_snap_wire(wire_u, 1u, 0, (u8)NET_PKT_TRANSFORM_SNAPSHOT,
                                5u, 3.0f, 0.0f, 0.0f);
    u32 len_o = build_ordered_snap_wire(wire_o, 1u, 5u, 4.0f, 0.0f, 0.0f);

    NetTransformSnapshot out[4] = {0};
    u32 out_count = 0u;

    ASSERT_TRUE(net_replicator_feed(&recv_rep, wire_u, len_u, out, 4u, &out_count) > 0);
    ASSERT_EQ(out_count, 1u);
    ASSERT_FLOAT_EQ(out[0].position[0], 3.0f, 0.001f);

    out_count = 0u;
    ASSERT_TRUE(net_replicator_feed(&recv_rep, wire_o, len_o, out, 4u, &out_count) > 0);
    ASSERT_EQ(out_count, 1u);
    ASSERT_FLOAT_EQ(out[0].position[0], 4.0f, 0.001f);

    net_replicator_shutdown(&send_rep);
    net_replicator_shutdown(&recv_rep);
    net_shutdown();
}

TEST(multitype_independent_sequences)
{
    ASSERT_TRUE(net_init());

    NetReplicator send_rep = {0};
    ASSERT_TRUE(net_replicator_init(&send_rep, 0));

    NetAddress dst;
    ASSERT_TRUE(net_address_resolve("127.0.0.1", (u16)(TEST_PORT + 4u), &dst));

    NetTransformSnapshot snap = { .entity_id = 8u, .position = { 2.0f, 0.0f, 0.0f } };
    ASSERT_TRUE(net_replicator_broadcast(&send_rep, &snap, 1u, &dst) > 0);
    ASSERT_TRUE(net_replicator_send_heartbeat(&send_rep, &dst, 1000u) > 0);
    ASSERT_EQ(send_rep.unreliable[NET_PKT_TRANSFORM_SNAPSHOT].send_seq, 2u);
    ASSERT_EQ(send_rep.unreliable[NET_PKT_HEARTBEAT].send_seq, 2u);

    NetReplicator recv_rep = {0};
    ASSERT_TRUE(net_replicator_init(&recv_rep, 0));

    u8 wire_h[PACKET_MAX_SIZE], wire_t[PACKET_MAX_SIZE];
    u32 len_h = build_heartbeat_wire(wire_h, 1u, 1000u);
    u32 len_t = build_snap_wire(wire_t, 1u, 0, (u8)NET_PKT_TRANSFORM_SNAPSHOT,
                                8u, 2.0f, 0.0f, 0.0f);

    NetTransformSnapshot out[4] = {0};
    u32 out_count = 0u;

    ASSERT_TRUE(net_replicator_feed(&recv_rep, wire_h, len_h, out, 4u, &out_count) > 0);
    ASSERT_EQ(out_count, 0u);
    ASSERT_EQ(recv_rep.unreliable[NET_PKT_HEARTBEAT].last_recv_seq, 1u);
    ASSERT_EQ(recv_rep.unreliable[NET_PKT_TRANSFORM_SNAPSHOT].last_recv_seq, 0u);

    ASSERT_TRUE(net_replicator_feed(&recv_rep, wire_t, len_t, out, 4u, &out_count) > 0);
    ASSERT_EQ(out_count, 1u);
    ASSERT_EQ(recv_rep.unreliable[NET_PKT_TRANSFORM_SNAPSHOT].last_recv_seq, 1u);

    out_count = 0u;
    ASSERT_TRUE(net_replicator_feed(&recv_rep, wire_h, len_h, out, 4u, &out_count) > 0);
    ASSERT_EQ(out_count, 0u);

    net_replicator_shutdown(&send_rep);
    net_replicator_shutdown(&recv_rep);
    net_shutdown();
}

TEST(heartbeat_rtt)
{
    time_init();
    NetReplicator rep = {0};
    ASSERT_TRUE(net_replicator_init(&rep, 0));

    u8 wire[PACKET_MAX_SIZE];
    u32 now_ms = (u32)(time_microseconds() / 1000ull);
    u32 len = build_heartbeat_wire(wire, 1u, now_ms > 10u ? now_ms - 10u : 0u);

    NetTransformSnapshot out[1] = {0};
    u32 out_count = 0u;
    ASSERT_TRUE(net_replicator_feed(&rep, wire, len, out, 1u, &out_count) > 0);
    ASSERT_EQ(out_count, 0u);
    ASSERT_EQ(rep.hb_recv, 1u);
    ASSERT_TRUE(rep.hb_last_rtt_ms >= 9.0f);

    net_replicator_shutdown(&rep);
}

TEST(heartbeat_roundtrip_echo)
{
    time_init();
    ASSERT_TRUE(net_init());

    NetReplicator rep = {0};
    ASSERT_TRUE(net_replicator_init(&rep, (u16)(TEST_PORT + 5u)));
    net_set_nonblocking(rep.socket, false);
    rep.hb_echo_reply = true;

    NetAddress dst;
    ASSERT_TRUE(net_address_resolve("127.0.0.1", (u16)(TEST_PORT + 5u), &dst));

    u32 t0 = (u32)(time_microseconds() / 1000ull);
    if (t0 > 20u) t0 -= 20u;
    ASSERT_TRUE(net_replicator_send_heartbeat(&rep, &dst, t0) > 0);

    NetTransformSnapshot out[1] = {0};
    u32 out_count = 0u;
    NetAddress from = {0};

    ASSERT_TRUE(net_replicator_recv(&rep, out, 1u, &out_count, &from) > 0);
    ASSERT_EQ(rep.hb_recv, 1u);
    ASSERT_EQ(rep.hb_echo_sent, 1u);

    out_count = 0u;
    for (int i = 0; i < 8; i++) {
        i32 n = net_replicator_recv(&rep, out, 1u, &out_count, &from);
        if (n > 0 && rep.hb_roundtrip_recv > 0u) break;
    }
    ASSERT_EQ(rep.hb_roundtrip_recv, 1u);
    ASSERT_TRUE(rep.hb_roundtrip_ms >= 19.0f);

    net_replicator_shutdown(&rep);
    net_shutdown();
}

TEST(heartbeat_ack_feed)
{
    time_init();
    NetReplicator rep = {0};
    ASSERT_TRUE(net_replicator_init(&rep, 0));

    u8 wire[PACKET_MAX_SIZE];
    u32 now_ms = (u32)(time_microseconds() / 1000ull);
    u32 send_ms = now_ms > 12u ? now_ms - 12u : 0u;
    u32 len = build_heartbeat_ack_wire(wire, 1u, send_ms, 7u);

    NetTransformSnapshot out[1] = {0};
    u32 out_count = 0u;
    NetAddress peer = {0};
    strncpy(peer.host, "127.0.0.1", sizeof(peer.host) - 1u);
    peer.port = 20001u;
    ASSERT_TRUE(net_replicator_feed_from(&rep, wire, len, &peer, out, 1u, &out_count) > 0);
    ASSERT_EQ(out_count, 0u);
    ASSERT_EQ(rep.hb_roundtrip_recv, 1u);
    ASSERT_TRUE(rep.hb_roundtrip_ms >= 11.0f);
    ASSERT_EQ(net_replicator_peer_count(&rep), 1u);
    const NetRepPeerStats *ps = net_replicator_peer_at(&rep, 0u);
    ASSERT_TRUE(ps != NULL);
    ASSERT_TRUE(net_address_equal(&ps->addr, &peer));
    ASSERT_EQ(ps->hb_rt_recv, 1u);

    net_replicator_shutdown(&rep);
}

TEST(heartbeat_header_only_rejected)
{
    /* R427: a header-only (12-byte) HEARTBEAT has no send_time_ms payload —
     * packet_read_u32 then yields 0 and hb_last_rtt_ms becomes `now_ms`
     * garbage, poisoning the peer RTT stats. It must be rejected entirely. */
    time_init();
    NetReplicator rep = {0};
    ASSERT_TRUE(net_replicator_init(&rep, 0));

    u8 wire[PACKET_MAX_SIZE];
    PacketBuffer buf;
    packet_begin(&buf, (u8)NET_PKT_HEARTBEAT, (u8)PACKET_UNRELIABLE);
    u32 len = packet_finish(&buf, 1u, 0);   /* header only, no payload */
    ASSERT_EQ(len, (u32)PACKET_HEADER_SIZE);
    memcpy(wire, buf.data, len);

    NetTransformSnapshot out[1] = {0};
    u32 out_count = 0u;
    NetAddress peer = {0};
    strncpy(peer.host, "127.0.0.1", sizeof(peer.host) - 1u);
    peer.port = 20002u;
    ASSERT_TRUE(net_replicator_feed_from(&rep, wire, len, &peer, out, 1u, &out_count) > 0);
    ASSERT_EQ(out_count, 0u);
    /* RTT stats untouched: no hb count, no peer registered, no rtt written. */
    ASSERT_EQ(rep.hb_recv, 0u);
    ASSERT_EQ(rep.hb_last_rtt_ms, 0.0f);
    ASSERT_EQ(net_replicator_peer_count(&rep), 0u);

    net_replicator_shutdown(&rep);
}

TEST(peer_rtt_table)
{
    time_init();
    NetReplicator rep = {0};
    ASSERT_TRUE(net_replicator_init(&rep, 0));

    NetAddress peer_a = {0}, peer_b = {0};
    strncpy(peer_a.host, "127.0.0.1", sizeof(peer_a.host) - 1u);
    peer_a.port = 20010u;
    strncpy(peer_b.host, "127.0.0.1", sizeof(peer_b.host) - 1u);
    peer_b.port = 20011u;

    u8 wire_a[PACKET_MAX_SIZE], wire_b[PACKET_MAX_SIZE];
    u32 now_ms = (u32)(time_microseconds() / 1000ull);
    u32 len_a = build_heartbeat_wire(wire_a, 1u, now_ms > 8u ? now_ms - 8u : 0u);
    u32 len_b = build_heartbeat_wire(wire_b, 2u, now_ms > 16u ? now_ms - 16u : 0u);

    NetTransformSnapshot out[1] = {0};
    u32 out_count = 0u;
    ASSERT_TRUE(net_replicator_feed_from(&rep, wire_a, len_a, &peer_a, out, 1u, &out_count) > 0);
    ASSERT_TRUE(net_replicator_feed_from(&rep, wire_b, len_b, &peer_b, out, 1u, &out_count) > 0);
    ASSERT_EQ(net_replicator_peer_count(&rep), 2u);

    const NetRepPeerStats *pa = net_replicator_peer_at(&rep, 0u);
    const NetRepPeerStats *pb = net_replicator_peer_at(&rep, 1u);
    ASSERT_TRUE(pa && pb);
    ASSERT_TRUE(net_address_equal(&pa->addr, &peer_a) || net_address_equal(&pa->addr, &peer_b));
    ASSERT_FALSE(net_address_equal(&pa->addr, &pb->addr));
    ASSERT_TRUE(pa->last_rtt_ms >= 7.0f || pb->last_rtt_ms >= 7.0f);

    net_replicator_shutdown(&rep);
}

TEST(peer_evict_stale)
{
    time_init();
    NetReplicator rep = {0};
    ASSERT_TRUE(net_replicator_init(&rep, 0));
    rep.peer_evict_ms = 1000u;

    NetAddress peer = {0};
    strncpy(peer.host, "127.0.0.1", sizeof(peer.host) - 1u);
    peer.port = 20100u;

    u8 wire[PACKET_MAX_SIZE];
    u32 len = build_heartbeat_wire(wire, 1u, (u32)(time_microseconds() / 1000ull));
    NetTransformSnapshot out[1] = {0};
    u32 out_count = 0u;
    ASSERT_TRUE(net_replicator_feed_from(&rep, wire, len, &peer, out, 1u, &out_count) > 0);
    ASSERT_EQ(net_replicator_peer_count(&rep), 1u);

    rep.peers[0].last_seen_ms = 0u;
    net_replicator_peer_evict_stale(&rep, 5000u);
    ASSERT_EQ(net_replicator_peer_count(&rep), 0u);
    ASSERT_EQ(rep.peer_evicted, 1u);

    net_replicator_shutdown(&rep);
}

TEST(peer_lru_full)
{
    time_init();
    NetReplicator rep = {0};
    ASSERT_TRUE(net_replicator_init(&rep, 0));
    rep.peer_evict_ms = 0u;

    NetTransformSnapshot out[1] = {0};
    u32 out_count = 0u;
    u8 wire[PACKET_MAX_SIZE];
    u32 base = (u32)(time_microseconds() / 1000ull);

    for (u32 i = 0u; i < NET_REP_MAX_PEERS; i++) {
        NetAddress p = {0};
        strncpy(p.host, "127.0.0.1", sizeof(p.host) - 1u);
        p.port = (u16)(20200u + i);
        u32 len = build_heartbeat_wire(wire, i + 1u, base);
        ASSERT_TRUE(net_replicator_feed_from(&rep, wire, len, &p, out, 1u, &out_count) > 0);
    }
    ASSERT_EQ(net_replicator_peer_count(&rep), NET_REP_MAX_PEERS);
    rep.peers[0].last_seen_ms = 1u;

    NetAddress extra = {0};
    strncpy(extra.host, "127.0.0.1", sizeof(extra.host) - 1u);
    extra.port = 20300u;
    u32 len = build_heartbeat_wire(wire, 99u, base);
    ASSERT_TRUE(net_replicator_feed_from(&rep, wire, len, &extra, out, 1u, &out_count) > 0);

    ASSERT_EQ(net_replicator_peer_count(&rep), NET_REP_MAX_PEERS);
    ASSERT_TRUE(rep.peer_evicted >= 1u);

    bool found_extra = false, found_first = false;
    NetAddress first = {0};
    strncpy(first.host, "127.0.0.1", sizeof(first.host) - 1u);
    first.port = 20200u;
    for (u32 i = 0u; i < rep.peer_count; i++) {
        if (net_address_equal(&rep.peers[i].addr, &extra)) found_extra = true;
        if (net_address_equal(&rep.peers[i].addr, &first)) found_first = true;
    }
    ASSERT_TRUE(found_extra);
    ASSERT_FALSE(found_first);

    net_replicator_shutdown(&rep);
}

TEST(peer_save_load)
{
    time_init();
    NetReplicator rep = {0};
    ASSERT_TRUE(net_replicator_init(&rep, 0));

    NetAddress peer = {0};
    strncpy(peer.host, "127.0.0.1", sizeof(peer.host) - 1u);
    peer.port = 20400u;

    u8 wire[PACKET_MAX_SIZE];
    u32 len = build_heartbeat_wire(wire, 1u, (u32)(time_microseconds() / 1000ull));
    NetTransformSnapshot out[1] = {0};
    u32 out_count = 0u;
    ASSERT_TRUE(net_replicator_feed_from(&rep, wire, len, &peer, out, 1u, &out_count) > 0);
    ASSERT_EQ(net_replicator_peer_count(&rep), 1u);
    rep.peers[0].roundtrip_ms = 9.5f;
    rep.peers[0].hb_rt_recv = 2u;

    char path[64]; test_tmp(path, sizeof path, "test_netrep_peers.txt"); /* R444: per-pid path — same-tree parallel ctest shared the cwd-relative file */
    ASSERT_TRUE(net_replicator_peer_save(&rep, path));

    NetReplicator loaded = {0};
    ASSERT_TRUE(net_replicator_init(&loaded, 0));
    ASSERT_TRUE(net_replicator_peer_load(&loaded, path));
    ASSERT_EQ(net_replicator_peer_count(&loaded), 1u);
    const NetRepPeerStats *ps = net_replicator_peer_at(&loaded, 0u);
    ASSERT_TRUE(ps != NULL);
    ASSERT_TRUE(net_address_equal(&ps->addr, &peer));
    ASSERT_FLOAT_EQ(ps->last_rtt_ms, rep.peers[0].last_rtt_ms, 0.01f);
    ASSERT_FLOAT_EQ(ps->roundtrip_ms, 9.5f, 0.01f);
    ASSERT_EQ(ps->hb_rt_recv, 2u);

    remove(path);
    net_replicator_shutdown(&rep);
    net_replicator_shutdown(&loaded);
}

TEST(peer_save_dir)
{
#if defined(ENGINE_PLATFORM_WINDOWS)
    /* load_dir uses opendir — Linux-only for now */
#else
    time_init();
    NetReplicator rep = {0};
    ASSERT_TRUE(net_replicator_init(&rep, 0));

    NetAddress a = {0}, b = {0};
    strncpy(a.host, "127.0.0.1", sizeof(a.host) - 1u);
    a.port = 20500u;
    strncpy(b.host, "127.0.0.1", sizeof(b.host) - 1u);
    b.port = 20501u;

    u8 wire[PACKET_MAX_SIZE];
    NetTransformSnapshot out[1] = {0};
    u32 out_count = 0u;
    u32 t = (u32)(time_microseconds() / 1000ull);
    ASSERT_TRUE(net_replicator_feed_from(&rep, wire, build_heartbeat_wire(wire, 1u, t),
                                        &a, out, 1u, &out_count) > 0);
    ASSERT_TRUE(net_replicator_feed_from(&rep, wire, build_heartbeat_wire(wire, 2u, t),
                                        &b, out, 1u, &out_count) > 0);
    ASSERT_EQ(net_replicator_peer_count(&rep), 2u);

    char dir[64];
    snprintf(dir, sizeof(dir), "/tmp/netrep_dir_%d", (int)getpid());
    ASSERT_TRUE(net_replicator_peer_save_dir(&rep, dir));

    NetReplicator loaded = {0};
    ASSERT_TRUE(net_replicator_init(&loaded, 0));
    ASSERT_TRUE(net_replicator_peer_load_dir(&loaded, dir));
    ASSERT_EQ(net_replicator_peer_count(&loaded), 2u);

    net_replicator_shutdown(&rep);
    net_replicator_shutdown(&loaded);
#endif
}

/* R477: peer_save_dir formats each output filename in path[512]. A directory
 * that leaves no room must not silently save a peer under a truncated name. */
TEST(peer_save_dir_rejects_path_truncation)
{
#if defined(ENGINE_PLATFORM_WINDOWS)
    /* peer directory persistence uses POSIX mkdir/opendir in this build. */
#else
    NetReplicator rep = {0};
    NetRepPeerStats peer = {0};
    strncpy(peer.addr.host, "127.0.0.1", sizeof(peer.addr.host) - 1u);
    peer.addr.port = 20900u;
    peer.valid = true;
    rep.peers[0] = peer;
    rep.peer_count = 1u;

    char base[128], dir[512];
    ASSERT_TRUE(make_deep_dir(dir, sizeof(dir), base, sizeof(base), 500u));
    ASSERT_FALSE(net_replicator_peer_save_dir(&rep, dir));
    remove_deep_dir(dir, base);
#endif
}

/* R478: directory loading must not parse a prefix file when dir + d_name
 * exceeds its path buffer. The actual .peer entry is deliberately distinct. */
TEST(peer_load_dir_skips_truncated_entry_path)
{
#if defined(ENGINE_PLATFORM_WINDOWS)
    /* peer directory persistence uses POSIX mkdir/opendir in this build. */
#else
    char base[128], dir[512], prefix[1024], peer_file[1024];
    ASSERT_TRUE(make_deep_dir(dir, sizeof(dir), base, sizeof(base), 508u));
    int n = snprintf(prefix, sizeof(prefix), "%s/xx", dir);
    ASSERT_TRUE(n >= 0 && (usize)n < sizeof(prefix));
    n = snprintf(peer_file, sizeof(peer_file), "%s/xxxxx.peer", dir);
    ASSERT_TRUE(n >= 0 && (usize)n < sizeof(peer_file));
    FILE *f = fopen(prefix, "w");
    ASSERT_NOT_NULL(f);
    ASSERT_TRUE(fputs("peer 127.0.0.1 20910 1.000 2.000 3 4 5\n", f) >= 0);
    ASSERT_EQ(fclose(f), 0);
    f = fopen(peer_file, "w");
    ASSERT_NOT_NULL(f);
    ASSERT_TRUE(fputs("# actual peer entry\n", f) >= 0);
    ASSERT_EQ(fclose(f), 0);

    NetReplicator rep = {0};
    ASSERT_TRUE(net_replicator_peer_load_dir(&rep, dir));
    ASSERT_EQ(net_replicator_peer_count(&rep), 0u);

    remove(peer_file);
    remove(prefix);
    remove_deep_dir(dir, base);
#endif
}

TEST(peer_save_delta)
{
#if defined(ENGINE_PLATFORM_WINDOWS)
#else
    time_init();
    NetReplicator rep = {0};
    ASSERT_TRUE(net_replicator_init(&rep, 0));

    NetAddress peer = {0};
    strncpy(peer.host, "127.0.0.1", sizeof(peer.host) - 1u);
    peer.port = 20600u;

    u8 wire[PACKET_MAX_SIZE];
    NetTransformSnapshot out[1] = {0};
    u32 out_count = 0u;
    u32 len = build_heartbeat_wire(wire, 1u, (u32)(time_microseconds() / 1000ull));
    ASSERT_TRUE(net_replicator_feed_from(&rep, wire, len, &peer, out, 1u, &out_count) > 0);

    char dir[64];
    snprintf(dir, sizeof(dir), "/tmp/netrep_delta_%d", (int)getpid());
    ASSERT_TRUE(net_replicator_peer_save_dir(&rep, dir));

    rep.peers[0].roundtrip_ms = 88.0f;
    rep.peers[0].dirty = true;
    char delta[128];
    snprintf(delta, sizeof(delta), "%s/delta.log", dir);
    ASSERT_TRUE(net_replicator_peer_save_delta(&rep, delta));

    NetReplicator loaded = {0};
    ASSERT_TRUE(net_replicator_init(&loaded, 0));
    ASSERT_TRUE(net_replicator_peer_load_dir(&loaded, dir));
    ASSERT_EQ(net_replicator_peer_count(&loaded), 1u);
    const NetRepPeerStats *ps = net_replicator_peer_at(&loaded, 0u);
    ASSERT_TRUE(ps != NULL);
    ASSERT_FLOAT_EQ(ps->roundtrip_ms, 88.0f, 0.01f);

    net_replicator_shutdown(&rep);
    net_replicator_shutdown(&loaded);
#endif
}

/* R479: a failed append must leave dirty state intact so the peer update can
 * be retried; /dev/full makes the write fail without filesystem cleanup. */
TEST(peer_save_delta_keeps_dirty_on_write_failure)
{
#if defined(ENGINE_PLATFORM_WINDOWS)
    /* /dev/full is a POSIX error-injection device. */
#else
    NetReplicator rep = {0};
    NetRepPeerStats peer = {0};
    strncpy(peer.addr.host, "127.0.0.1", sizeof(peer.addr.host) - 1u);
    peer.addr.port = 20930u;
    peer.valid = true;
    peer.dirty = true;
    rep.peers[0] = peer;
    rep.peer_count = 1u;

    ASSERT_FALSE(net_replicator_peer_save_delta(&rep, "/dev/full"));
    ASSERT_TRUE(rep.peers[0].dirty);
#endif
}

TEST(peer_delta_rotate)
{
    /* R435: once delta.log outgrows netrep_delta_max_bytes, peer_save_delta
     * rewrites the full baseline (.peer files) and rebuilds delta.log from
     * just the header; load_dir must still recover the full latest state. */
#if defined(ENGINE_PLATFORM_WINDOWS)
#else
    time_init();
    NetReplicator rep = {0};
    ASSERT_TRUE(net_replicator_init(&rep, 0));

    NetAddress a = {0}, b = {0};
    strncpy(a.host, "127.0.0.1", sizeof(a.host) - 1u);
    a.port = 20800u;
    strncpy(b.host, "127.0.0.1", sizeof(b.host) - 1u);
    b.port = 20801u;

    u8 wire[PACKET_MAX_SIZE];
    NetTransformSnapshot out[1] = {0};
    u32 out_count = 0u;
    u32 t = (u32)(time_microseconds() / 1000ull);
    ASSERT_TRUE(net_replicator_feed_from(&rep, wire, build_heartbeat_wire(wire, 1u, t),
                                        &a, out, 1u, &out_count) > 0);
    ASSERT_TRUE(net_replicator_feed_from(&rep, wire, build_heartbeat_wire(wire, 2u, t),
                                        &b, out, 1u, &out_count) > 0);
    ASSERT_EQ(net_replicator_peer_count(&rep), 2u);

    char dir[64];
    snprintf(dir, sizeof(dir), "/tmp/netrep_rot_%d", (int)getpid());
    ASSERT_TRUE(net_replicator_peer_save_dir(&rep, dir));
    char delta[128];
    snprintf(delta, sizeof(delta), "%s/delta.log", dir);

    size_t old_max = netrep_delta_max_bytes;
    netrep_delta_max_bytes = 96u;   /* ~2 peer lines overflow this */

    for (u32 round = 0u; round < 6u; round++) {
        rep.peers[0].roundtrip_ms = 10.0f + (f32)round;
        rep.peers[1].roundtrip_ms = 20.0f + (f32)round;
        rep.peers[0].dirty = true;
        rep.peers[1].dirty = true;
        ASSERT_TRUE(net_replicator_peer_save_delta(&rep, delta));
    }
    netrep_delta_max_bytes = old_max;

    /* Rotated log: header line intact, size back to header-only. */
    FILE *f = fopen(delta, "r");
    ASSERT_TRUE(f != NULL);
    char line[512];
    ASSERT_TRUE(fgets(line, sizeof(line), f) != NULL);
    ASSERT_TRUE(strncmp(line, "# break netrep delta v1", 23u) == 0);
    fseek(f, 0, SEEK_END);
    long sz = ftell(f);
    fclose(f);
    ASSERT_TRUE(sz < 128);

    /* Baseline was rewritten: load_dir recovers both peers' latest state. */
    NetReplicator loaded = {0};
    ASSERT_TRUE(net_replicator_init(&loaded, 0));
    ASSERT_TRUE(net_replicator_peer_load_dir(&loaded, dir));
    ASSERT_EQ(net_replicator_peer_count(&loaded), 2u);
    bool found_a = false, found_b = false;
    for (u32 i = 0u; i < 2u; i++) {
        const NetRepPeerStats *ps = net_replicator_peer_at(&loaded, i);
        ASSERT_TRUE(ps != NULL);
        if (ps->addr.port == 20800u) {
            ASSERT_FLOAT_EQ(ps->roundtrip_ms, 15.0f, 0.01f);
            found_a = true;
        } else if (ps->addr.port == 20801u) {
            ASSERT_FLOAT_EQ(ps->roundtrip_ms, 25.0f, 0.01f);
            found_b = true;
        }
    }
    ASSERT_TRUE(found_a && found_b);

    char p0[160], p1[160];
    snprintf(p0, sizeof(p0), "%s/peer_000_127.0.0.1_20800.peer", dir);
    snprintf(p1, sizeof(p1), "%s/peer_001_127.0.0.1_20801.peer", dir);
    remove(delta);
    remove(p0);
    remove(p1);
    rmdir(dir);
    net_replicator_shutdown(&rep);
    net_replicator_shutdown(&loaded);
#endif
}

TEST(peer_delta_no_rotate_below_threshold)
{
    /* R435: below the threshold nothing changes — pure append, no rewrite. */
#if defined(ENGINE_PLATFORM_WINDOWS)
#else
    time_init();
    NetReplicator rep = {0};
    ASSERT_TRUE(net_replicator_init(&rep, 0));

    NetAddress peer = {0};
    strncpy(peer.host, "127.0.0.1", sizeof(peer.host) - 1u);
    peer.port = 20810u;

    u8 wire[PACKET_MAX_SIZE];
    NetTransformSnapshot out[1] = {0};
    u32 out_count = 0u;
    u32 len = build_heartbeat_wire(wire, 1u, (u32)(time_microseconds() / 1000ull));
    ASSERT_TRUE(net_replicator_feed_from(&rep, wire, len, &peer, out, 1u, &out_count) > 0);

    char dir[64];
    snprintf(dir, sizeof(dir), "/tmp/netrep_norot_%d", (int)getpid());
    ASSERT_TRUE(net_replicator_peer_save_dir(&rep, dir));
    char delta[128];
    snprintf(delta, sizeof(delta), "%s/delta.log", dir);

    size_t old_max = netrep_delta_max_bytes;
    netrep_delta_max_bytes = 1u << 20;  /* far above anything this test writes */

    for (u32 round = 0u; round < 3u; round++) {
        rep.peers[0].roundtrip_ms = 30.0f + (f32)round;
        rep.peers[0].dirty = true;
        ASSERT_TRUE(net_replicator_peer_save_delta(&rep, delta));
    }
    netrep_delta_max_bytes = old_max;

    /* One header + one "+ peer" line per round, all appended, nothing cut. */
    FILE *f = fopen(delta, "r");
    ASSERT_TRUE(f != NULL);
    char line[512];
    u32 headers = 0u, appends = 0u;
    while (fgets(line, sizeof(line), f)) {
        if (strncmp(line, "# break netrep delta v1", 23u) == 0) headers++;
        else if (strncmp(line, "+ peer", 6u) == 0) appends++;
    }
    fclose(f);
    ASSERT_EQ(headers, 1u);
    ASSERT_EQ(appends, 3u);

    char p0[160];
    snprintf(p0, sizeof(p0), "%s/peer_000_127.0.0.1_20810.peer", dir);
    remove(delta);
    remove(p0);
    rmdir(dir);
    net_replicator_shutdown(&rep);
#endif
}

TEST(ordered_channels_per_peer)
{
    /* R418: channel state is keyed per peer address. Two peers each starting
     * their ordered stream at seq 1 must both be delivered; with the old shared
     * channel the second peer's seq 1 fell behind the shared next_ordered_seq
     * and was dropped as stale. */
    NetReplicator rep = {0};
    ASSERT_TRUE(net_replicator_init(&rep, 0));
    rep.ordered_layer = true;

    NetAddress peer_a = {0}, peer_b = {0};
    strncpy(peer_a.host, "127.0.0.1", sizeof(peer_a.host) - 1u);
    peer_a.port = 20700u;
    strncpy(peer_b.host, "127.0.0.1", sizeof(peer_b.host) - 1u);
    peer_b.port = 20701u;

    u8 wa1[PACKET_MAX_SIZE], wb1[PACKET_MAX_SIZE], wa2[PACKET_MAX_SIZE], wb2[PACKET_MAX_SIZE];
    u32 la1 = build_ordered_snap_wire(wa1, 1u, 10u, 1.0f, 0.0f, 0.0f);
    u32 lb1 = build_ordered_snap_wire(wb1, 1u, 20u, 2.0f, 0.0f, 0.0f);
    u32 la2 = build_ordered_snap_wire(wa2, 2u, 10u, 3.0f, 0.0f, 0.0f);
    u32 lb2 = build_ordered_snap_wire(wb2, 2u, 20u, 4.0f, 0.0f, 0.0f);

    NetTransformSnapshot out[4] = {0};
    u32 out_count = 0u;

    /* Interleave both peers' streams; every packet is in-order for its peer. */
    ASSERT_TRUE(net_replicator_feed_from(&rep, wa1, la1, &peer_a, out, 4u, &out_count) > 0);
    ASSERT_EQ(out_count, 1u);
    ASSERT_EQ(out[0].entity_id, 10u);
    ASSERT_FLOAT_EQ(out[0].position[0], 1.0f, 0.001f);

    out_count = 0u;
    ASSERT_TRUE(net_replicator_feed_from(&rep, wb1, lb1, &peer_b, out, 4u, &out_count) > 0);
    ASSERT_EQ(out_count, 1u);   /* pre-fix: dropped as stale (shared seq space) */
    ASSERT_EQ(out[0].entity_id, 20u);
    ASSERT_FLOAT_EQ(out[0].position[0], 2.0f, 0.001f);

    out_count = 0u;
    ASSERT_TRUE(net_replicator_feed_from(&rep, wa2, la2, &peer_a, out, 4u, &out_count) > 0);
    ASSERT_EQ(out_count, 1u);
    ASSERT_FLOAT_EQ(out[0].position[0], 3.0f, 0.001f);

    out_count = 0u;
    ASSERT_TRUE(net_replicator_feed_from(&rep, wb2, lb2, &peer_b, out, 4u, &out_count) > 0);
    ASSERT_EQ(out_count, 1u);
    ASSERT_FLOAT_EQ(out[0].position[0], 4.0f, 0.001f);

    /* Each peer advanced its own ordered stream; the legacy shared channel was
     * not touched by addressed packets. */
    ASSERT_EQ(rep.ordered[NET_PKT_TRANSFORM_SNAPSHOT].next_ordered_seq, 0u);
    u32 peers_with_channels = 0u;
    for (u32 i = 0u; i < NET_REP_MAX_PEERS; i++) {
        const NetRepPeerChannel *pc = &rep.peer_channels[i];
        if (!pc->valid) continue;
        peers_with_channels++;
        ASSERT_EQ(pc->ordered[NET_PKT_TRANSFORM_SNAPSHOT].next_ordered_seq, 3u);
        ASSERT_EQ(pc->ordered[NET_PKT_TRANSFORM_SNAPSHOT].reorder_stale, 0u);
    }
    ASSERT_EQ(peers_with_channels, 2u);

    net_replicator_shutdown(&rep);
}

TEST(peer_channels_evict_stalest)
{
    /* R423: the per-peer channel table (NET_REP_MAX_PEERS slots) had no
     * eviction — once 8 distinct sender addresses were seen, every further
     * peer fell back to the shared channels FOREVER, reintroducing the
     * cross-peer seq-collision R418 fixed (trivially triggerable: UDP source
     * addresses are spoofable). The table must evict the stalest slot when
     * full so the 9th peer still gets isolated channels. */
    NetReplicator rep = {0};
    ASSERT_TRUE(net_replicator_init(&rep, 0));
    rep.ordered_layer = true;

    NetTransformSnapshot out[4] = {0};
    u32 out_count = 0u;

    NetAddress peers[NET_REP_MAX_PEERS + 1u];
    for (u32 i = 0u; i <= NET_REP_MAX_PEERS; i++) {
        memset(&peers[i], 0, sizeof(peers[i]));
        strncpy(peers[i].host, "127.0.0.1", sizeof(peers[i].host) - 1u);
        peers[i].port = (u16)(20800u + i);
        u8 wire[PACKET_MAX_SIZE];
        u32 len = build_ordered_snap_wire(wire, 1u, 10u + i, (f32)i, 0.0f, 0.0f);
        out_count = 0u;
        ASSERT_TRUE(net_replicator_feed_from(&rep, wire, len, &peers[i],
                                             out, 4u, &out_count) > 0);
        /* Every peer's seq 1 must be delivered — including the 9th, which
         * pre-fix fell back to the shared channel and was dropped as stale. */
        ASSERT_EQ(out_count, 1u);
        ASSERT_EQ(out[0].entity_id, 10u + i);
        ASSERT_FLOAT_EQ(out[0].position[0], (f32)i, 0.001f);
    }

    /* All slots occupied; the newest peer is present, the stalest (first fed)
     * was evicted to make room, and its channel advanced past seq 1. */
    u32 valid = 0u, found_first = 0u, found_last = 0u;
    for (u32 i = 0u; i < NET_REP_MAX_PEERS; i++) {
        const NetRepPeerChannel *pc = &rep.peer_channels[i];
        if (!pc->valid) continue;
        valid++;
        if (net_address_equal(&pc->addr, &peers[0])) found_first = 1u;
        if (net_address_equal(&pc->addr, &peers[NET_REP_MAX_PEERS])) {
            found_last = 1u;
            ASSERT_EQ(pc->ordered[NET_PKT_TRANSFORM_SNAPSHOT].next_ordered_seq, 2u);
            ASSERT_EQ(pc->ordered[NET_PKT_TRANSFORM_SNAPSHOT].reorder_stale, 0u);
        }
    }
    ASSERT_EQ(valid, NET_REP_MAX_PEERS);
    ASSERT_EQ(found_first, 0u);
    ASSERT_EQ(found_last, 1u);

    net_replicator_shutdown(&rep);
}

TEST(peer_load_rejects_port_overflow)
{
    /* R418: a peer line with port > 65535 used to truncate into u16
     * (70000 -> 4464) and register the wrong address; it must be rejected. */
    NetReplicator rep = {0};
    ASSERT_TRUE(net_replicator_init(&rep, 0));

    char path[64]; test_tmp(path, sizeof path, "test_netrep_badport.txt"); /* R444: per-pid path */
    FILE *f = fopen(path, "w");
    ASSERT_NOT_NULL(f);
    fprintf(f, "# break netrep peers v1\n");
    fprintf(f, "peer 127.0.0.1 70000 1.000 2.000 3 4 5\n");
    fprintf(f, "peer 127.0.0.1 20710 1.000 2.000 3 4 5\n");
    fclose(f);

    ASSERT_TRUE(net_replicator_peer_load(&rep, path));
    ASSERT_EQ(net_replicator_peer_count(&rep), 1u);
    const NetRepPeerStats *ps = net_replicator_peer_at(&rep, 0u);
    ASSERT_TRUE(ps != NULL);
    ASSERT_EQ((u32)ps->addr.port, 20710u);

    remove(path);
    net_replicator_shutdown(&rep);
}

TEST(parse_payload_clamps_forged_count)
{
    /* R254: a packet declaring more snapshots than its byte length can hold must
     * not fabricate entries. Build one that claims 5 but carries only 1; the
     * parser must clamp recv_count to the bytes actually present (each entry is
     * u32 + 3*f32 = 16 bytes), not read stale buffer past write_pos. */
    PacketBuffer buf;
    packet_begin(&buf, (u8)NET_PKT_TRANSFORM_SNAPSHOT, (u8)PACKET_UNRELIABLE);
    packet_write_u16(&buf, 5u);          /* forged count */
    packet_write_u32(&buf, 42u);         /* one real entity follows */
    packet_write_f32(&buf, 1.0f);
    packet_write_f32(&buf, 2.0f);
    packet_write_f32(&buf, 3.0f);
    u8 wire[PACKET_MAX_SIZE];
    u32 len = packet_finish(&buf, 1u, 0u);
    memcpy(wire, buf.data, len);

    NetReplicator rep = {0};
    ASSERT_TRUE(net_replicator_init(&rep, 0));

    NetTransformSnapshot out[8] = {0};
    u32 out_count = 99u;
    ASSERT_TRUE(net_replicator_feed(&rep, wire, len, out, 8u, &out_count) > 0);
    ASSERT_EQ(out_count, 1u);            /* clamped — no ghost entities */
    ASSERT_EQ(out[0].entity_id, 42u);
    ASSERT_FLOAT_EQ(out[0].position[0], 1.0f, 0.001f);

    net_replicator_shutdown(&rep);
}

/* R434: reliable sliding-window tests ------------------------------------ */

static u32 reliable_window_valid_count(const NetReplicator *rep) {
    u32 n = 0u;
    for (u32 i = 0u; i < (u32)NET_RELIABLE_WINDOW; i++)
        if (rep->reliable_window[i].valid) n++;
    return n;
}

/* Heartbeat frame carrying a chosen header ack (acks the peer's sequences). */
static u32 build_ack_wire(u8 *out, u32 seq, u32 ack) {
    PacketBuffer buf;
    packet_begin(&buf, (u8)NET_PKT_HEARTBEAT, (u8)PACKET_UNRELIABLE);
    packet_write_u32(&buf, 0u);
    u32 len = packet_finish(&buf, seq, ack);
    memcpy(out, buf.data, len);
    return len;
}

static void feed_ack(NetReplicator *rep, u32 ack) {
    u8 wire[PACKET_MAX_SIZE];
    u32 len = build_ack_wire(wire, 1u, ack);
    NetTransformSnapshot out[1] = {0};
    u32 out_count = 0u;
    ASSERT_TRUE(net_replicator_feed(rep, wire, len, out, 1u, &out_count) > 0);
}

static void feed_ack_from(NetReplicator *rep, u32 ack, const NetAddress *from) {
    u8 wire[PACKET_MAX_SIZE];
    u32 len = build_ack_wire(wire, 1u, ack);
    NetTransformSnapshot out[1] = {0};
    u32 out_count = 0u;
    ASSERT_TRUE(net_replicator_feed_from(rep, wire, len, from, out, 1u, &out_count) > 0);
}

TEST(reliable_window_multiple_inflight)
{
    /* R434: up to NET_RELIABLE_WINDOW reliable packets may be in flight at
     * once; each claims its own slot with its own sequence. */
    ASSERT_TRUE(net_init());

    NetReplicator send_rep = {0};
    ASSERT_TRUE(net_replicator_init(&send_rep, 0));
    send_rep.reliable_retry = true;

    NetAddress dst;
    ASSERT_TRUE(net_address_resolve("127.0.0.1", (u16)(TEST_PORT + 6u), &dst));

    NetTransformSnapshot snap = { .entity_id = 1u, .position = { 0.0f, 0.0f, 0.0f } };
    for (u32 i = 0u; i < (u32)NET_RELIABLE_WINDOW; i++)
        ASSERT_TRUE(net_replicator_broadcast(&send_rep, &snap, 1u, &dst) > 0);

    ASSERT_EQ(reliable_window_valid_count(&send_rep), (u32)NET_RELIABLE_WINDOW);
    /* All slots hold distinct sequences (1..NET_RELIABLE_WINDOW on this channel). */
    for (u32 i = 0u; i < (u32)NET_RELIABLE_WINDOW; i++) {
        ASSERT_TRUE(send_rep.reliable_window[i].valid);
        for (u32 j = i + 1u; j < (u32)NET_RELIABLE_WINDOW; j++)
            ASSERT_NEQ(send_rep.reliable_window[i].seq, send_rep.reliable_window[j].seq);
    }

    net_replicator_shutdown(&send_rep);
    net_shutdown();
}

TEST(reliable_window_ack_per_slot)
{
    /* R434: the header ack is cumulative — every slot whose seq it has
     * reached is cleared, later slots stay in flight; a duplicate ack is a
     * no-op. */
    ASSERT_TRUE(net_init());

    NetReplicator send_rep = {0};
    ASSERT_TRUE(net_replicator_init(&send_rep, 0));
    send_rep.reliable_retry = true;

    NetAddress dst;
    ASSERT_TRUE(net_address_resolve("127.0.0.1", (u16)(TEST_PORT + 7u), &dst));

    NetTransformSnapshot snap = { .entity_id = 1u, .position = { 0.0f, 0.0f, 0.0f } };
    for (u32 i = 0u; i < 5u; i++)   /* seqs 1..5 */
        ASSERT_TRUE(net_replicator_broadcast(&send_rep, &snap, 1u, &dst) > 0);
    ASSERT_EQ(reliable_window_valid_count(&send_rep), 5u);

    feed_ack(&send_rep, 3u);        /* acks seqs 1..3 */
    ASSERT_EQ(reliable_window_valid_count(&send_rep), 2u);
    for (u32 i = 0u; i < (u32)NET_RELIABLE_WINDOW; i++) {
        const NetRepReliablePending *s = &send_rep.reliable_window[i];
        if (s->valid) ASSERT_TRUE(s->seq == 4u || s->seq == 5u);
    }

    feed_ack(&send_rep, 3u);        /* duplicate ack: harmless */
    ASSERT_EQ(reliable_window_valid_count(&send_rep), 2u);

    net_replicator_shutdown(&send_rep);
    net_shutdown();
}

TEST(reliable_window_ack_is_scoped_to_sender)
{
    /* R453: reliable sends to two peers share one fixed window, but each ack
     * only proves delivery to its source peer. An ack from A must never retire
     * an equally-numbered packet sent to B. */
    ASSERT_TRUE(net_init());

    NetReplicator rep = {0};
    ASSERT_TRUE(net_replicator_init(&rep, 0));
    rep.reliable_retry = true;

    NetAddress peer_a, peer_b;
    ASSERT_TRUE(net_address_resolve("127.0.0.1", (u16)(TEST_PORT + 11u), &peer_a));
    ASSERT_TRUE(net_address_resolve("127.0.0.1", (u16)(TEST_PORT + 12u), &peer_b));
    NetTransformSnapshot snap = { .entity_id = 1u, .position = {0} };

    ASSERT_TRUE(net_replicator_broadcast(&rep, &snap, 1u, &peer_a) > 0); /* A seq 1 */
    ASSERT_TRUE(net_replicator_broadcast(&rep, &snap, 1u, &peer_b) > 0); /* B seq 1 */
    ASSERT_EQ(reliable_window_valid_count(&rep), 2u);

    feed_ack_from(&rep, 1u, &peer_a);

    ASSERT_EQ(reliable_window_valid_count(&rep), 1u);
    ASSERT_TRUE(rep.reliable_window[1].valid);
    ASSERT_TRUE(net_address_equal(&rep.reliable_window[1].dst, &peer_b));
    ASSERT_EQ(rep.reliable_window[1].seq, 1u);

    net_replicator_shutdown(&rep);
    net_shutdown();
}

TEST(reliable_window_full_rejected)
{
    /* R434: with every slot occupied a further reliable send is rejected
     * (NET_ERROR, the function's failure convention) and counted, instead of
     * silently overwriting an unacked packet as the single slot did. */
    ASSERT_TRUE(net_init());

    NetReplicator send_rep = {0};
    ASSERT_TRUE(net_replicator_init(&send_rep, 0));
    send_rep.reliable_retry = true;

    NetAddress dst;
    ASSERT_TRUE(net_address_resolve("127.0.0.1", (u16)(TEST_PORT + 8u), &dst));

    NetTransformSnapshot snap = { .entity_id = 1u, .position = { 0.0f, 0.0f, 0.0f } };
    for (u32 i = 0u; i < (u32)NET_RELIABLE_WINDOW; i++)
        ASSERT_TRUE(net_replicator_broadcast(&send_rep, &snap, 1u, &dst) > 0);
    ASSERT_EQ(reliable_window_valid_count(&send_rep), (u32)NET_RELIABLE_WINDOW);

    ASSERT_EQ(net_replicator_broadcast(&send_rep, &snap, 1u, &dst), NET_ERROR);
    ASSERT_EQ(send_rep.reliable_dropped, 1u);
    ASSERT_EQ(reliable_window_valid_count(&send_rep), (u32)NET_RELIABLE_WINDOW);

    /* A freed slot can be claimed again. */
    feed_ack(&send_rep, 1u);
    ASSERT_EQ(reliable_window_valid_count(&send_rep), (u32)NET_RELIABLE_WINDOW - 1u);
    ASSERT_TRUE(net_replicator_broadcast(&send_rep, &snap, 1u, &dst) > 0);
    ASSERT_EQ(reliable_window_valid_count(&send_rep), (u32)NET_RELIABLE_WINDOW);

    net_replicator_shutdown(&send_rep);
    net_shutdown();
}

TEST(reliable_window_seq_wraparound)
{
    /* R434: the per-slot ack compare must stay wraparound-safe (R245 form):
     * slots at seq 0xFFFFFFFE/0xFFFFFFFF/0 are all acked by ack=1 after the
     * 32-bit wrap, while a slot at seq 2 is not. */
    NetReplicator rep = {0};
    ASSERT_TRUE(net_replicator_init(&rep, 0));

    rep.reliable_window[0].valid = true; rep.reliable_window[0].seq = 0xFFFFFFFEu;
    rep.reliable_window[1].valid = true; rep.reliable_window[1].seq = 0xFFFFFFFFu;
    rep.reliable_window[2].valid = true; rep.reliable_window[2].seq = 0u;
    rep.reliable_window[3].valid = true; rep.reliable_window[3].seq = 2u;

    feed_ack(&rep, 1u);
    ASSERT_EQ(reliable_window_valid_count(&rep), 1u);
    ASSERT_TRUE(rep.reliable_window[3].valid);
    ASSERT_EQ(rep.reliable_window[3].seq, 2u);

    net_replicator_shutdown(&rep);
}

TEST(reliable_window_out_of_order_acks)
{
    /* R434: acks arriving out of order (a newer cumulative ack followed by a
     * stale older one) must never resurrect cleared slots or drop newer
     * state. */
    ASSERT_TRUE(net_init());

    NetReplicator send_rep = {0};
    ASSERT_TRUE(net_replicator_init(&send_rep, 0));
    send_rep.reliable_retry = true;

    NetAddress dst;
    ASSERT_TRUE(net_address_resolve("127.0.0.1", (u16)(TEST_PORT + 9u), &dst));

    NetTransformSnapshot snap = { .entity_id = 1u, .position = { 0.0f, 0.0f, 0.0f } };
    for (u32 i = 0u; i < 6u; i++)   /* seqs 1..6 */
        ASSERT_TRUE(net_replicator_broadcast(&send_rep, &snap, 1u, &dst) > 0);
    ASSERT_EQ(reliable_window_valid_count(&send_rep), 6u);

    feed_ack(&send_rep, 4u);        /* clears seqs 1..4 */
    ASSERT_EQ(reliable_window_valid_count(&send_rep), 2u);

    feed_ack(&send_rep, 2u);        /* stale, older ack: no effect on the window */
    ASSERT_EQ(reliable_window_valid_count(&send_rep), 2u);

    feed_ack(&send_rep, 6u);        /* catches up: window empty */
    ASSERT_EQ(reliable_window_valid_count(&send_rep), 0u);

    net_replicator_shutdown(&send_rep);
    net_shutdown();
}

TEST(reliable_window_retry_per_slot)
{
    /* R434: retry retransmits each still-unacked slot independently — acked
     * slots are skipped; a late ack arriving after a retransmit still clears
     * its slot. */
    ASSERT_TRUE(net_init());

    NetReplicator send_rep = {0};
    ASSERT_TRUE(net_replicator_init(&send_rep, 0));
    send_rep.reliable_retry = true;

    NetAddress dst;
    ASSERT_TRUE(net_address_resolve("127.0.0.1", (u16)(TEST_PORT + 10u), &dst));

    NetTransformSnapshot snap = { .entity_id = 1u, .position = { 0.0f, 0.0f, 0.0f } };
    for (u32 i = 0u; i < 4u; i++)   /* seqs 1..4 */
        ASSERT_TRUE(net_replicator_broadcast(&send_rep, &snap, 1u, &dst) > 0);

    feed_ack(&send_rep, 2u);        /* seqs 1..2 acked; 3..4 outstanding */
    ASSERT_EQ(reliable_window_valid_count(&send_rep), 2u);

    ASSERT_TRUE(net_replicator_retry_pending(&send_rep) > 0);
    ASSERT_EQ(send_rep.retry_count, 2u);        /* only the 2 unacked slots resent */
    ASSERT_EQ(reliable_window_valid_count(&send_rep), 2u);

    /* Late ack for a retransmitted packet clears its slot normally. */
    feed_ack(&send_rep, 4u);
    ASSERT_EQ(reliable_window_valid_count(&send_rep), 0u);
    ASSERT_TRUE(net_replicator_retry_pending(&send_rep) == 0);
    ASSERT_EQ(send_rep.retry_count, 2u);        /* nothing left to retransmit */

    net_replicator_shutdown(&send_rep);
    net_shutdown();
}

TEST_MAIN_BEGIN()
    RUN_TEST(replicator_init_shutdown);
    RUN_TEST(transform_snapshot_loopback);
    RUN_TEST(parse_payload_clamps_forged_count);
    RUN_TEST(reliable_retry_pending);
    RUN_TEST(ordered_reorder_buffer);
    RUN_TEST(ordered_reorder_out_of_window_no_stall);
    RUN_TEST(ordered_reorder_zero_snapshot_no_stall);
    RUN_TEST(ordered_resync_after_large_seq_jump);
    RUN_TEST(ordered_resync_nonempty_window_head_loss);
    RUN_TEST(reliable_ordered_combined);
    RUN_TEST(reliable_ack_echoes_received_sequence);
    RUN_TEST(reliable_ack_is_scoped_to_destination);
    RUN_TEST(reliable_ack_waits_for_contiguous_sequence);
    RUN_TEST(reliable_send_sequence_survives_receive_peer_eviction);
    RUN_TEST(reliable_send_state_is_not_recycled_after_ack);
    RUN_TEST(reliable_pending_cleared_via_peer_ack);
    RUN_TEST(dual_channel_sequences);
    RUN_TEST(multitype_independent_sequences);
    RUN_TEST(heartbeat_rtt);
    RUN_TEST(heartbeat_roundtrip_echo);
    RUN_TEST(heartbeat_ack_feed);
    RUN_TEST(heartbeat_header_only_rejected);
    RUN_TEST(peer_rtt_table);
    RUN_TEST(peer_evict_stale);
    RUN_TEST(peer_lru_full);
    RUN_TEST(peer_save_load);
    RUN_TEST(peer_save_dir);
    RUN_TEST(peer_save_dir_rejects_path_truncation);
    RUN_TEST(peer_load_dir_skips_truncated_entry_path);
    RUN_TEST(peer_save_delta);
    RUN_TEST(peer_save_delta_keeps_dirty_on_write_failure);
    RUN_TEST(peer_delta_rotate);
    RUN_TEST(peer_delta_no_rotate_below_threshold);
    RUN_TEST(ordered_channels_per_peer);
    RUN_TEST(peer_channels_evict_stalest);
    RUN_TEST(peer_load_rejects_port_overflow);
    RUN_TEST(reliable_window_multiple_inflight);
    RUN_TEST(reliable_window_ack_per_slot);
    RUN_TEST(reliable_window_ack_is_scoped_to_sender);
    RUN_TEST(reliable_window_full_rejected);
    RUN_TEST(reliable_window_seq_wraparound);
    RUN_TEST(reliable_window_out_of_order_acks);
    RUN_TEST(reliable_window_retry_per_slot);
TEST_MAIN_END()
