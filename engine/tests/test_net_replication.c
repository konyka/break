/* ==========================================================================
 *  test_net_replication.c — Transform snapshot unreliable UDP broadcast.
 * ========================================================================== */

#include "test_framework.h"
#include <network/net_replication.h>
#include <platform/time.h>
#include <string.h>
#include <unistd.h>

#define TEST_PORT 19877u

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
    ASSERT_TRUE(send_rep.reliable_pending.valid);

    ASSERT_TRUE(net_replicator_retry_pending(&send_rep) > 0);
    ASSERT_EQ(send_rep.retry_count, 1u);

    send_rep.last_peer_ack = send_rep.reliable_pending.seq;
    ASSERT_TRUE(net_replicator_retry_pending(&send_rep) == 0);
    ASSERT_FALSE(send_rep.reliable_pending.valid);

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
     * packet and stalling the ordered stream. It must instead be dropped. */
    NetReplicator rep = {0};
    ASSERT_TRUE(net_replicator_init(&rep, 0));
    rep.ordered_layer = true;

    u8 w2[PACKET_MAX_SIZE], w_far[PACKET_MAX_SIZE], w1[PACKET_MAX_SIZE];
    u32 l2   = build_ordered_snap_wire(w2,   2u,               10u, 4.0f, 5.0f, 6.0f);
    /* seq 2 + NET_REORDER_SLOTS aliases the same slot as seq 2 (2 % 32). */
    u32 lfar = build_ordered_snap_wire(w_far, 2u + NET_REORDER_SLOTS, 10u, 9.0f, 9.0f, 9.0f);
    u32 l1   = build_ordered_snap_wire(w1,   1u,               10u, 1.0f, 2.0f, 3.0f);

    NetTransformSnapshot out[4] = {0};
    u32 out_count = 0u;

    /* Buffer seq 2 (waiting for seq 1). */
    ASSERT_TRUE(net_replicator_feed(&rep, w2, l2, out, 4u, &out_count) > 0);
    ASSERT_EQ(out_count, 0u);
    ASSERT_EQ(rep.ordered[NET_PKT_TRANSFORM_SNAPSHOT].reorder_pending, 1u);

    /* Out-of-window seq must be dropped, NOT overwrite the buffered seq 2. */
    out_count = 0u;
    ASSERT_TRUE(net_replicator_feed(&rep, w_far, lfar, out, 4u, &out_count) > 0);
    ASSERT_EQ(out_count, 0u);
    ASSERT_EQ(rep.ordered[NET_PKT_TRANSFORM_SNAPSHOT].reorder_pending, 1u);

    /* seq 1 arrives → delivers 1, then drains the preserved seq 2. The drain
     * reuses out[0] (matching ordered_reorder_buffer), so out[0] ends as seq 2's
     * payload (4,5,6) and the buffer is fully drained (pending 0). Before the fix
     * seq 2 would have been overwritten by the out-of-window packet and the drain
     * would stall with reorder_pending stuck at 1. */
    out_count = 0u;
    ASSERT_TRUE(net_replicator_feed(&rep, w1, l1, out, 4u, &out_count) > 0);
    ASSERT_TRUE(out_count >= 1u);
    ASSERT_FLOAT_EQ(out[0].position[0], 4.0f, 0.001f);
    ASSERT_FLOAT_EQ(out[0].position[1], 5.0f, 0.001f);
    ASSERT_FLOAT_EQ(out[0].position[2], 6.0f, 0.001f);
    ASSERT_EQ(rep.ordered[NET_PKT_TRANSFORM_SNAPSHOT].reorder_delivered, 1u);
    ASSERT_EQ(rep.ordered[NET_PKT_TRANSFORM_SNAPSHOT].reorder_pending, 0u);

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
    ASSERT_TRUE(send_rep.reliable_pending.valid);
    ASSERT_EQ(send_rep.reliable_pending.data[11], (u8)(PACKET_RELIABLE | PACKET_ORDERED));
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

    const char *path = "test_netrep_peers.txt";
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

TEST_MAIN_BEGIN()
    RUN_TEST(replicator_init_shutdown);
    RUN_TEST(transform_snapshot_loopback);
    RUN_TEST(parse_payload_clamps_forged_count);
    RUN_TEST(reliable_retry_pending);
    RUN_TEST(ordered_reorder_buffer);
    RUN_TEST(ordered_reorder_out_of_window_no_stall);
    RUN_TEST(ordered_reorder_zero_snapshot_no_stall);
    RUN_TEST(reliable_ordered_combined);
    RUN_TEST(dual_channel_sequences);
    RUN_TEST(multitype_independent_sequences);
    RUN_TEST(heartbeat_rtt);
    RUN_TEST(heartbeat_roundtrip_echo);
    RUN_TEST(heartbeat_ack_feed);
    RUN_TEST(peer_rtt_table);
    RUN_TEST(peer_evict_stale);
    RUN_TEST(peer_lru_full);
    RUN_TEST(peer_save_load);
    RUN_TEST(peer_save_dir);
    RUN_TEST(peer_save_delta);
TEST_MAIN_END()
