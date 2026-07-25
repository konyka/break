/* Mutation fuzzer for the replication receive path.
 *
 * Builds valid TRANSFORM_SNAPSHOT / HEARTBEAT / HEARTBEAT_ACK datagrams, then
 * feeds randomly mutated copies through net_replicator_feed under ASan+UBSan.
 * This is remote attacker-controlled input, so the receiver must tolerate
 * anything: it may reject, but it must not crash, read or write out of bounds,
 * or wedge itself.
 *
 * Two deliberate design choices, both aimed at catching what a stack array in a
 * hand-written test would hide:
 *
 *  - The caller's snapshot array is heap-allocated at *exactly* max_count
 *    entries, so any write past the declared bound is an immediate ASan report
 *    rather than silent scribbling into unused stack slack.
 *  - The replicator is kept alive across many packets before being reset, so
 *    reorder-buffer, sequence-dedup and peer state accumulate the way they do
 *    against a real peer. Bugs in the ordered path need that history. */

#include <network/net_replication.h>
#include <network/packet.h>
#include <core/log.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static unsigned long rng_state = 0xC0FFEEu;
static unsigned rnd(void) {
    rng_state = rng_state * 6364136223846793005ULL + 1442695040888963407ULL;
    return (unsigned)(rng_state >> 33);
}

/* Boundary values for the u32/u16 header fields. Byte flips alone essentially
 * never produce these; the R388 PAK overflow needed exactly this. */
static const u32 interesting_u32[] = {
    0u, 1u, 2u, 3u,
    0x7FFFFFFFu, 0x80000000u, 0x80000001u,
    0xFFFFFFFDu, 0xFFFFFFFEu, 0xFFFFFFFFu,
    0x0000FFFFu, 0x00010000u, 0x00000020u, /* 32 == NET_REORDER_SLOTS */
};

static u32 build_snap_wire(u8 *out, u32 seq, u32 ack, u8 flags, u8 type, u16 count) {
    PacketBuffer buf;
    packet_begin(&buf, type, flags);
    packet_write_u16(&buf, count);
    for (u16 i = 0; i < count; i++) {
        packet_write_u32(&buf, 1000u + i);
        packet_write_f32(&buf, (f32)i);
        packet_write_f32(&buf, (f32)i * 2.0f);
        packet_write_f32(&buf, (f32)i * 3.0f);
    }
    u32 len = packet_finish(&buf, seq, ack);
    memcpy(out, buf.data, len);
    return len;
}

static u32 build_heartbeat_wire(u8 *out, u32 seq, u32 ack, u8 type, u8 flags) {
    PacketBuffer buf;
    packet_begin(&buf, type, flags);
    packet_write_u32(&buf, 12345u);
    packet_write_u32(&buf, seq);
    u32 len = packet_finish(&buf, seq, ack);
    memcpy(out, buf.data, len);
    return len;
}

/* Produce a fresh, structurally valid datagram; the caller then mutates it. */
static u32 build_seed(u8 *out, u32 seq) {
    u8 flags = 0u;
    switch (rnd() % 4) {
    case 0: flags = (u8)PACKET_UNRELIABLE; break;
    case 1: flags = (u8)PACKET_ORDERED; break;
    case 2: flags = (u8)PACKET_RELIABLE; break;
    default: flags = (u8)(PACKET_ORDERED | PACKET_RELIABLE); break;
    }
    switch (rnd() % 3) {
    case 0:
        return build_heartbeat_wire(out, seq, rnd(), (u8)NET_PKT_HEARTBEAT, flags);
    case 1:
        return build_heartbeat_wire(out, seq, rnd(), (u8)NET_PKT_HEARTBEAT_ACK, flags);
    default:
        return build_snap_wire(out, seq, rnd(), flags,
                               (u8)NET_PKT_TRANSFORM_SNAPSHOT,
                               (u16)(rnd() % 40u));
    }
}

/* Mutates in place; may also shrink the reported length to model a truncated
 * datagram, which is an attack dimension independent of the content. */
static u32 mutate(u8 *buf, u32 len, unsigned nmut) {
    for (unsigned m = 0; m < nmut; m++) {
        /* Word-level boundary write into the header + count field. */
        if (len >= 16u && rnd() % 2 == 0) {
            u32 v = interesting_u32[rnd() % (sizeof(interesting_u32) / sizeof(interesting_u32[0]))];
            u32 nwords = (len < 32u ? len : 32u) / 4u;
            memcpy(buf + (size_t)(rnd() % nwords) * 4u, &v, sizeof(v));
            continue;
        }
        u32 pos = (rnd() % 4 != 0) ? (rnd() % (len < 16u ? len : 16u)) : (rnd() % len);
        switch (rnd() % 4) {
        case 0: buf[pos] = (u8)(rnd() & 0xFF); break;
        case 1: buf[pos] ^= (u8)(1u << (rnd() % 8)); break;
        case 2: buf[pos] = 0xFF; break;
        default: buf[pos] = 0x00; break;
        }
    }
    /* Truncate sometimes, including to below PACKET_HEADER_SIZE. */
    if (rnd() % 8 == 0) {
        u32 cut = 1u + rnd() % len;
        return cut;
    }
    return len;
}

int main(int argc, char **argv) {
    unsigned iters = argc > 1 ? (unsigned)atoi(argv[1]) : 20000;
    if (argc > 2) rng_state = (unsigned long)atoi(argv[2]);
    log_set_level(LOG_FATAL);

    NetReplicator rep;
    if (!net_replicator_init(&rep, 0)) {
        fprintf(stderr, "net_replicator_init failed (no UDP socket available)\n");
        return 2;
    }
    rep.ordered_layer = true;
    rep.seq_dedup = true;

    u8 wire[PACKET_MAX_SIZE];
    unsigned accepted = 0, delivered = 0;

    for (unsigned it = 0; it < iters; it++) {
        /* Periodically start over so state builds up and is then torn down;
         * a leak or a wedged reorder buffer shows up either way. */
        if (it % 64u == 0u) {
            net_replicator_shutdown(&rep);
            if (!net_replicator_init(&rep, 0)) {
                fprintf(stderr, "re-init failed at iter %u\n", it);
                return 2;
            }
            rep.ordered_layer = true;
            rep.seq_dedup = true;
        }

        u32 len = build_seed(wire, 1u + (it % 40u));
        len = mutate(wire, len, 1 + rnd() % 5);

        /* Exact-size heap array: any write past max_count traps here. Routed
         * through void* so the size stays opaque to -Walloc-size; max_count of 0
         * deliberately yields a zero-entry region, which is still non-NULL and
         * still fully poisoned past byte 0. */
        u32 max_count = rnd() % 5u; /* includes 0 */
        void *raw = malloc((size_t)max_count * sizeof(NetTransformSnapshot));
        NetTransformSnapshot *out = (NetTransformSnapshot *)raw;
        if (!out) continue;

        u32 out_count = 0xDEADBEEFu;
        i32 r = net_replicator_feed(&rep, wire, len, out, max_count, &out_count);
        if (r > 0) {
            accepted++;
            /* The parser must never report more snapshots than it was allowed to
             * write, otherwise a caller trusting out_count reads uninitialized
             * memory or worse. */
            if (out_count != 0xDEADBEEFu && out_count > max_count) {
                fprintf(stderr,
                        "INVARIANT VIOLATION iter %u: out_count=%u > max_count=%u\n",
                        it, out_count, max_count);
                free(out);
                return 3;
            }
            delivered += (out_count != 0xDEADBEEFu) ? out_count : 0u;
        }
        free(out);
    }

    net_replicator_shutdown(&rep);
    printf("fuzz done: %u iters, accepted %u, snapshots delivered %u\n",
           iters, accepted, delivered);
    return 0;
}
