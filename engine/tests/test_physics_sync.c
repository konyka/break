#include "test_framework.h"
#include <physics/physics_sync.h>
#include <stdlib.h>
#include <string.h>

static PhysicsWorld *sync_scene(PhysicsBodyHandle *out_box)
{
    PhysicsWorld *pw = physics_world_create(8);
    (void)physics_body_create(pw, vec3(0, -1, 0), vec3(10, 1, 10), 0.0f, true, 0);
    *out_box = physics_body_create(pw, vec3(0, 2, 0), vec3(0.5f, 0.5f, 0.5f), 1.0f, false, 0);
    return pw;
}

TEST(sync_report_round_trip_and_rejection)
{
    u8 buf[PHYSICS_SYNC_REPORT_BYTES + 1u];
    u32 tick = 0;
    u64 hash = 0;
    ASSERT_FALSE(physics_sync_encode_report(7u, 0x1122334455667788ull, buf,
                                            PHYSICS_SYNC_REPORT_BYTES - 1u));
    ASSERT_FALSE(physics_sync_encode_report(7u, 1u, NULL, PHYSICS_SYNC_REPORT_BYTES));
    ASSERT_TRUE(physics_sync_encode_report(7u, 0x1122334455667788ull, buf,
                                           PHYSICS_SYNC_REPORT_BYTES));
    ASSERT_EQ(buf[0], 'P');
    ASSERT_EQ(buf[3], 'N');
    ASSERT_EQ(buf[4], 7u);
    ASSERT_EQ(buf[8], 0x88u);
    ASSERT_EQ(buf[15], 0x11u);
    ASSERT_TRUE(physics_sync_decode_report(buf, PHYSICS_SYNC_REPORT_BYTES, &tick, &hash));
    ASSERT_EQ(tick, 7u);
    ASSERT_TRUE(hash == 0x1122334455667788ull);

    ASSERT_FALSE(physics_sync_decode_report(buf, PHYSICS_SYNC_REPORT_BYTES - 1u, &tick, &hash));
    ASSERT_FALSE(physics_sync_decode_report(buf, PHYSICS_SYNC_REPORT_BYTES + 1u, &tick, &hash));
    ASSERT_FALSE(physics_sync_decode_report(NULL, PHYSICS_SYNC_REPORT_BYTES, &tick, &hash));
    buf[2] ^= 1u;
    tick = 99u;
    ASSERT_FALSE(physics_sync_decode_report(buf, PHYSICS_SYNC_REPORT_BYTES, &tick, &hash));
    ASSERT_EQ(tick, 99u);
}

TEST(sync_lockstep_worlds_match)
{
    PhysicsBodyHandle box_a, box_b;
    PhysicsWorld *a = sync_scene(&box_a);
    PhysicsWorld *b = sync_scene(&box_b);
    PhysicsSyncTracker tracker;
    physics_sync_init(&tracker);
    for (u32 tick = 1; tick <= 30u; tick++) {
        physics_step(a, 1.0f / 60.0f);
        physics_step(b, 1.0f / 60.0f);
        ASSERT_TRUE(physics_sync_record(&tracker, tick, physics_state_hash(a)));
        ASSERT_EQ(physics_sync_check(&tracker, tick, physics_state_hash(b)), PHYSICS_SYNC_MATCH);
    }
    ASSERT_FALSE(physics_sync_desynced(&tracker, NULL));
    physics_world_destroy(a);
    physics_world_destroy(b);
}

TEST(sync_impulse_on_one_world_is_detected_and_latched)
{
    PhysicsBodyHandle box_a, box_b;
    PhysicsWorld *a = sync_scene(&box_a);
    PhysicsWorld *b = sync_scene(&box_b);
    PhysicsSyncTracker tracker;
    u32 first = 0;
    physics_sync_init(&tracker);
    for (u32 tick = 1; tick <= 20u; tick++) {
        if (tick == 12u) {
            physics_body_apply_impulse(b, box_b, vec3(0.0f, 2.0f, 0.0f));
        }
        physics_step(a, 1.0f / 60.0f);
        physics_step(b, 1.0f / 60.0f);
        ASSERT_TRUE(physics_sync_record(&tracker, tick, physics_state_hash(a)));
        PhysicsSyncVerdict v = physics_sync_check(&tracker, tick, physics_state_hash(b));
        ASSERT_EQ(v, tick < 12u ? PHYSICS_SYNC_MATCH : PHYSICS_SYNC_DESYNC);
    }
    ASSERT_TRUE(physics_sync_desynced(&tracker, &first));
    ASSERT_EQ(first, 12u);
    ASSERT_EQ(physics_sync_check(&tracker, 5u, 0u), PHYSICS_SYNC_DESYNC);
    ASSERT_TRUE(physics_sync_desynced(&tracker, &first));
    ASSERT_EQ(first, 5u);
    ASSERT_EQ(physics_sync_check(&tracker, 15u, 0u), PHYSICS_SYNC_DESYNC);
    ASSERT_TRUE(physics_sync_desynced(&tracker, &first));
    ASSERT_EQ(first, 5u);
    physics_sync_init(&tracker);
    ASSERT_FALSE(physics_sync_desynced(&tracker, &first));
    ASSERT_EQ(first, 5u);
    physics_world_destroy(a);
    physics_world_destroy(b);
}

TEST(sync_window_and_ordering_rules)
{
    PhysicsSyncTracker tracker;
    physics_sync_init(&tracker);
    ASSERT_EQ(physics_sync_check(&tracker, 1u, 1u), PHYSICS_SYNC_UNKNOWN);
    ASSERT_EQ(physics_sync_check(&tracker, 0u, 0u), PHYSICS_SYNC_UNKNOWN);
    for (u32 tick = 1; tick <= PHYSICS_SYNC_HISTORY + 10u; tick++) {
        ASSERT_TRUE(physics_sync_record(&tracker, tick, (u64)tick * 31u));
    }
    ASSERT_FALSE(physics_sync_record(&tracker, PHYSICS_SYNC_HISTORY + 10u, 1u));
    ASSERT_FALSE(physics_sync_record(&tracker, 3u, 1u));
    PhysicsSyncTracker fresh;
    physics_sync_init(&fresh);
    ASSERT_TRUE(physics_sync_record(&fresh, 1u, 9u));
    ASSERT_EQ(physics_sync_check(&fresh, 0u, 0u), PHYSICS_SYNC_UNKNOWN);
    ASSERT_EQ(physics_sync_check(&fresh, 65u, 0u), PHYSICS_SYNC_UNKNOWN);
    ASSERT_EQ(physics_sync_check(&tracker, 10u, 310u), PHYSICS_SYNC_UNKNOWN);
    ASSERT_EQ(physics_sync_check(&tracker, 11u, 341u), PHYSICS_SYNC_MATCH);
    ASSERT_EQ(physics_sync_check(&tracker, PHYSICS_SYNC_HISTORY + 10u,
                                 (u64)(PHYSICS_SYNC_HISTORY + 10u) * 31u),
              PHYSICS_SYNC_MATCH);
    ASSERT_EQ(physics_sync_check(&tracker, PHYSICS_SYNC_HISTORY + 11u, 0u),
              PHYSICS_SYNC_UNKNOWN);
    ASSERT_FALSE(physics_sync_desynced(&tracker, NULL));
    ASSERT_TRUE(physics_sync_record(&tracker, PHYSICS_SYNC_HISTORY + 20u, 5u));
    ASSERT_EQ(physics_sync_check(&tracker, PHYSICS_SYNC_HISTORY + 20u, 5u), PHYSICS_SYNC_MATCH);
    ASSERT_EQ(physics_sync_check(&tracker, PHYSICS_SYNC_HISTORY + 15u, 5u), PHYSICS_SYNC_UNKNOWN);
}

static void step_both(PhysicsWorld *a, PhysicsWorld *b)
{
    physics_step(a, 1.0f / 60.0f);
    physics_step(b, 1.0f / 60.0f);
}

TEST(sync_correction_restores_the_diverged_peer)
{
    PhysicsBodyHandle box_a, box_b;
    PhysicsWorld *a = sync_scene(&box_a);
    PhysicsWorld *b = sync_scene(&box_b);
    PhysicsSyncTracker tracker;
    u32 first = 0;
    u32 applied_tick = 0;
    physics_sync_init(&tracker);
    for (u32 tick = 1; tick <= 10u; tick++) {
        if (tick == 4u) {
            physics_body_apply_impulse(b, box_b, vec3(1.0f, 2.0f, 0.0f));
        }
        step_both(a, b);
        ASSERT_TRUE(physics_sync_record(&tracker, tick, physics_state_hash(b)));
        (void)physics_sync_check(&tracker, tick, physics_state_hash(a));
    }
    ASSERT_TRUE(physics_sync_desynced(&tracker, &first));
    ASSERT_EQ(first, 4u);

    usize need = physics_sync_correction_size(a);
    ASSERT_EQ(need, PHYSICS_SYNC_CORRECTION_HEADER_BYTES + physics_snapshot_size(a));
    u8 *packet = malloc(need);
    usize written = 0;
    ASSERT_NOT_NULL(packet);
    ASSERT_FALSE(physics_sync_encode_correction(a, 10u, packet, need - 1u, &written));
    ASSERT_EQ(written, need);
    written = 0;
    ASSERT_TRUE(physics_sync_encode_correction(a, 10u, packet, need, &written));
    ASSERT_EQ(written, need);
    ASSERT_EQ(packet[0], 'P');
    ASSERT_EQ(packet[1], 'S');
    ASSERT_EQ(packet[2], 'N');
    ASSERT_EQ(packet[3], 'P');
    ASSERT_EQ(packet[4], 10u);

    ASSERT_TRUE(physics_sync_apply_correction(&tracker, b, packet, need, &applied_tick));
    ASSERT_EQ(applied_tick, 10u);
    ASSERT_FALSE(physics_sync_desynced(&tracker, NULL));
    ASSERT_TRUE(physics_state_hash(b) == physics_state_hash(a));
    ASSERT_EQ(physics_sync_check(&tracker, 10u, physics_state_hash(a)), PHYSICS_SYNC_MATCH);
    ASSERT_FALSE(physics_sync_record(&tracker, 10u, 0u));
    for (u32 tick = 11; tick <= 30u; tick++) {
        step_both(a, b);
        ASSERT_TRUE(physics_sync_record(&tracker, tick, physics_state_hash(b)));
        ASSERT_EQ(physics_sync_check(&tracker, tick, physics_state_hash(a)), PHYSICS_SYNC_MATCH);
    }
    free(packet);
    physics_world_destroy(a);
    physics_world_destroy(b);
}

TEST(sync_correction_rejects_malformed_packets)
{
    PhysicsBodyHandle box_a, box_b;
    PhysicsWorld *a = sync_scene(&box_a);
    PhysicsWorld *b = sync_scene(&box_b);
    PhysicsSyncTracker tracker;
    u32 first = 0;
    u32 applied_tick = 77u;
    physics_sync_init(&tracker);
    physics_body_apply_impulse(b, box_b, vec3(0.0f, 3.0f, 0.0f));
    step_both(a, b);
    ASSERT_TRUE(physics_sync_record(&tracker, 1u, physics_state_hash(b)));
    ASSERT_EQ(physics_sync_check(&tracker, 1u, physics_state_hash(a)), PHYSICS_SYNC_DESYNC);
    u64 before = physics_state_hash(b);

    usize need = physics_sync_correction_size(a);
    u8 *packet = malloc(need + 1u);
    ASSERT_NOT_NULL(packet);
    ASSERT_FALSE(physics_sync_encode_correction(a, 1u, NULL, need, NULL));
    ASSERT_TRUE(physics_sync_encode_correction(a, 1u, packet, need, NULL));

    ASSERT_FALSE(physics_sync_apply_correction(&tracker, b, NULL, need, &applied_tick));
    ASSERT_FALSE(physics_sync_apply_correction(&tracker, b, packet, need - 1u, &applied_tick));
    packet[need] = 0u;
    ASSERT_FALSE(physics_sync_apply_correction(&tracker, b, packet, need + 1u, &applied_tick));
    ASSERT_FALSE(physics_sync_apply_correction(&tracker, b, packet,
                                               PHYSICS_SYNC_CORRECTION_HEADER_BYTES - 1u,
                                               &applied_tick));
    packet[1] ^= 1u;
    ASSERT_FALSE(physics_sync_apply_correction(&tracker, b, packet, need, &applied_tick));
    packet[1] ^= 1u;
    packet[8] ^= 1u;
    ASSERT_FALSE(physics_sync_apply_correction(&tracker, b, packet, need, &applied_tick));
    packet[8] ^= 1u;
    packet[PHYSICS_SYNC_CORRECTION_HEADER_BYTES] ^= 1u;
    ASSERT_FALSE(physics_sync_apply_correction(&tracker, b, packet, need, &applied_tick));
    packet[PHYSICS_SYNC_CORRECTION_HEADER_BYTES] ^= 1u;
    packet[need - 1u] ^= 1u;
    ASSERT_FALSE(physics_sync_apply_correction(&tracker, b, packet, need, &applied_tick));
    packet[need - 1u] ^= 1u;
    packet[12] ^= 1u;
    ASSERT_FALSE(physics_sync_apply_correction(&tracker, b, packet, need, &applied_tick));
    packet[12] ^= 1u;
    packet[need - 1u] ^= 1u;
    packet[need - 2u] ^= 1u;
    ASSERT_FALSE(physics_sync_apply_correction(&tracker, b, packet, need, &applied_tick));
    packet[need - 1u] ^= 1u;
    packet[need - 2u] ^= 1u;

    PhysicsWorld *small = physics_world_create(1);
    PhysicsSyncTracker small_tracker;
    physics_sync_init(&small_tracker);
    ASSERT_TRUE(physics_sync_record(&small_tracker, 3u, 5u));
    ASSERT_FALSE(physics_sync_apply_correction(&small_tracker, small, packet, need, &applied_tick));
    ASSERT_EQ(physics_sync_check(&small_tracker, 3u, 5u), PHYSICS_SYNC_MATCH);
    ASSERT_EQ(small->count, 0u);
    physics_world_destroy(small);

    ASSERT_EQ(applied_tick, 77u);
    ASSERT_TRUE(physics_state_hash(b) == before);
    ASSERT_TRUE(physics_sync_desynced(&tracker, &first));
    ASSERT_EQ(first, 1u);

    ASSERT_TRUE(physics_sync_apply_correction(&tracker, b, packet, need, NULL));
    ASSERT_TRUE(physics_state_hash(b) == physics_state_hash(a));
    free(packet);
    physics_world_destroy(a);
    physics_world_destroy(b);
}

static u32 rd32(const u8 *p)
{
    return (u32)p[0] | ((u32)p[1] << 8) | ((u32)p[2] << 16) | ((u32)p[3] << 24);
}

static void wr32(u8 *p, u32 v)
{
    p[0] = (u8)v;
    p[1] = (u8)(v >> 8);
    p[2] = (u8)(v >> 16);
    p[3] = (u8)(v >> 24);
}

TEST(sync_delta_encodes_only_changed_runs)
{
    u8 base[64];
    u8 target[64];
    u8 packet[256];
    usize size = 0;
    for (u32 i = 0; i < 64u; i++) {
        base[i] = (u8)(i * 7u + 1u);
    }
    memcpy(target, base, sizeof(target));

    ASSERT_TRUE(physics_sync_encode_delta(9u, 4u, base, 64u, target, 64u, packet,
                                          sizeof(packet), &size));
    ASSERT_EQ(size, PHYSICS_SYNC_DELTA_HEADER_BYTES);
    ASSERT_EQ(packet[0], 'P');
    ASSERT_EQ(packet[1], 'S');
    ASSERT_EQ(packet[2], 'N');
    ASSERT_EQ(packet[3], 'D');
    ASSERT_EQ(rd32(packet + 4), 9u);
    ASSERT_EQ(rd32(packet + 8), 4u);
    ASSERT_EQ(rd32(packet + 12), 64u);
    ASSERT_EQ(rd32(packet + 20), 64u);
    ASSERT_TRUE(rd32(packet + 16) == rd32(packet + 24));

    target[10] ^= 0xffu;
    target[14] ^= 0xffu;
    target[40] ^= 0xffu;
    ASSERT_TRUE(physics_sync_encode_delta(9u, 4u, base, 64u, target, 64u, packet,
                                          sizeof(packet), &size));
    ASSERT_EQ(size, PHYSICS_SYNC_DELTA_HEADER_BYTES + 8u + 5u + 8u + 1u);
    const u8 *run = packet + PHYSICS_SYNC_DELTA_HEADER_BYTES;
    ASSERT_EQ(rd32(run), 10u);
    ASSERT_EQ(rd32(run + 4), 5u);
    ASSERT_EQ(memcmp(run + 8, target + 10, 5u), 0);
    run += 8u + 5u;
    ASSERT_EQ(rd32(run), 40u);
    ASSERT_EQ(rd32(run + 4), 1u);
    ASSERT_EQ(run[8], target[40]);
    ASSERT_FALSE(rd32(packet + 16) == rd32(packet + 24));

    target[49] ^= 0xffu;
    ASSERT_TRUE(physics_sync_encode_delta(9u, 4u, base, 64u, target, 64u, packet,
                                          sizeof(packet), &size));
    ASSERT_EQ(size, PHYSICS_SYNC_DELTA_HEADER_BYTES + 8u + 5u + 8u + 10u);
    run = packet + PHYSICS_SYNC_DELTA_HEADER_BYTES + 8u + 5u;
    ASSERT_EQ(rd32(run), 40u);
    ASSERT_EQ(rd32(run + 4), 10u);

    target[49] ^= 0xffu;
    target[50] ^= 0xffu;
    ASSERT_TRUE(physics_sync_encode_delta(9u, 4u, base, 64u, target, 64u, packet,
                                          sizeof(packet), &size));
    ASSERT_EQ(size, PHYSICS_SYNC_DELTA_HEADER_BYTES + 8u + 5u + 8u + 1u + 8u + 1u);
    run = packet + PHYSICS_SYNC_DELTA_HEADER_BYTES + 8u + 5u + 8u + 1u;
    ASSERT_EQ(rd32(run), 50u);
    ASSERT_EQ(rd32(run + 4), 1u);

    memset(packet, 0xaa, sizeof(packet));
    usize need = size;
    size = 0;
    ASSERT_FALSE(physics_sync_encode_delta(9u, 4u, base, 64u, target, 64u, packet, need - 1u,
                                           &size));
    ASSERT_EQ(size, need);
    ASSERT_EQ(packet[0], 0xaau);
    ASSERT_FALSE(physics_sync_encode_delta(9u, 4u, base, 64u, target, 64u, NULL, need, NULL));
    ASSERT_FALSE(physics_sync_encode_delta(9u, 4u, NULL, 64u, target, 64u, packet, need, NULL));
    ASSERT_FALSE(physics_sync_encode_delta(9u, 4u, base, 64u, NULL, 64u, packet, need, NULL));
    ASSERT_TRUE(physics_sync_encode_delta(9u, 4u, NULL, 0u, target, 64u, packet,
                                          sizeof(packet), &size));
}

TEST(sync_delta_handles_grown_and_shrunk_targets)
{
    u8 base[16];
    u8 grown[32];
    u8 packet[128];
    u8 out[64];
    usize size = 0;
    usize out_size = 0;
    u32 tick = 0;
    for (u32 i = 0; i < 16u; i++) {
        base[i] = (u8)(i + 1u);
    }
    memcpy(grown, base, 16u);
    memset(grown + 16, 0, 16u);
    grown[30] = 5u;
    ASSERT_TRUE(physics_sync_encode_delta(2u, 1u, base, 16u, grown, 32u, packet,
                                          sizeof(packet), &size));
    ASSERT_EQ(size, PHYSICS_SYNC_DELTA_HEADER_BYTES + 8u + 1u);
    ASSERT_EQ(rd32(packet + PHYSICS_SYNC_DELTA_HEADER_BYTES), 30u);
    ASSERT_TRUE(physics_sync_decode_delta(base, 16u, packet, size, out, sizeof(out), &out_size,
                                          &tick));
    ASSERT_EQ(out_size, 32u);
    ASSERT_EQ(tick, 2u);
    ASSERT_EQ(memcmp(out, grown, 32u), 0);

    ASSERT_TRUE(physics_sync_encode_delta(3u, 2u, grown, 32u, base, 16u, packet,
                                          sizeof(packet), &size));
    ASSERT_EQ(size, PHYSICS_SYNC_DELTA_HEADER_BYTES);
    memset(out, 0xee, sizeof(out));
    ASSERT_TRUE(physics_sync_decode_delta(grown, 32u, packet, size, out, sizeof(out), &out_size,
                                          &tick));
    ASSERT_EQ(out_size, 16u);
    ASSERT_EQ(tick, 3u);
    ASSERT_EQ(memcmp(out, base, 16u), 0);
    ASSERT_EQ(out[16], 0xeeu);

    u32 t = 0;
    u32 bt = 0;
    ASSERT_TRUE(physics_sync_delta_ticks(packet, size, &t, &bt));
    ASSERT_EQ(t, 3u);
    ASSERT_EQ(bt, 2u);
    t = 77u;
    ASSERT_FALSE(physics_sync_delta_ticks(packet, PHYSICS_SYNC_DELTA_HEADER_BYTES - 1u, &t, &bt));
    ASSERT_FALSE(physics_sync_delta_ticks(NULL, size, &t, &bt));
    packet[3] ^= 1u;
    ASSERT_FALSE(physics_sync_delta_ticks(packet, size, &t, &bt));
    ASSERT_EQ(t, 77u);
    ASSERT_TRUE(physics_sync_delta_ticks(packet, 0u, NULL, NULL) == false);
}

static u32 fnv32(const u8 *data, usize size)
{
    u32 h = 2166136261u;
    for (usize i = 0; i < size; i++) {
        h ^= data[i];
        h *= 16777619u;
    }
    return h;
}

/* Rewrites the target checksum to match a naive replay of the runs, so a
 * crafted packet fails only on the structural rule under test. */
static void seal_delta(u8 *packet, usize size, const u8 *base, usize base_size)
{
    u8 rebuilt[256];
    u32 target_size = rd32(packet + 20);
    memset(rebuilt, 0, sizeof(rebuilt));
    memcpy(rebuilt, base, base_size < target_size ? base_size : target_size);
    usize at = PHYSICS_SYNC_DELTA_HEADER_BYTES;
    while (at + 8u <= size) {
        u32 off = rd32(packet + at);
        u32 len = rd32(packet + at + 4);
        at += 8u;
        if (at + len > size) {
            break;
        }
        if ((u64)off + len <= sizeof(rebuilt)) {
            memcpy(rebuilt + off, packet + at, len);
        }
        at += len;
    }
    wr32(packet + 24, fnv32(rebuilt, target_size));
}

static usize put_run(u8 *p, u32 off, u32 len, u8 fill)
{
    wr32(p, off);
    wr32(p + 4, len);
    memset(p + 8, fill, len);
    return 8u + len;
}

TEST(sync_delta_decode_rejects_malformed_packets)
{
    u8 base[32];
    u8 target[32];
    u8 packet[256];
    u8 out[64];
    usize size = 0;
    usize out_size = 5u;
    u32 tick = 66u;
    for (u32 i = 0; i < 32u; i++) {
        base[i] = (u8)(i * 3u + 2u);
    }
    memcpy(target, base, 32u);
    target[4] = 0u;
    target[20] = 9u;
    ASSERT_TRUE(physics_sync_encode_delta(8u, 7u, base, 32u, target, 32u, packet,
                                          sizeof(packet), &size));
    ASSERT_TRUE(physics_sync_decode_delta(base, 32u, packet, size, out, 32u, &out_size, &tick));
    ASSERT_EQ(out_size, 32u);
    ASSERT_EQ(memcmp(out, target, 32u), 0);
    out_size = 5u;
    tick = 66u;

    ASSERT_FALSE(physics_sync_decode_delta(base, 32u, NULL, size, out, 32u, &out_size, &tick));
    ASSERT_FALSE(physics_sync_decode_delta(base, 32u, packet, size, NULL, 32u, &out_size, &tick));
    ASSERT_FALSE(physics_sync_decode_delta(NULL, 32u, packet, size, out, 32u, &out_size, &tick));
    ASSERT_FALSE(physics_sync_decode_delta(base, 32u, packet, PHYSICS_SYNC_DELTA_HEADER_BYTES - 1u,
                                           out, 32u, &out_size, &tick));
    ASSERT_FALSE(physics_sync_decode_delta(base, 32u, packet, size, out, 31u, &out_size, &tick));
    ASSERT_FALSE(physics_sync_decode_delta(base, 31u, packet, size, out, 32u, &out_size, &tick));
    packet[0] ^= 1u;
    ASSERT_FALSE(physics_sync_decode_delta(base, 32u, packet, size, out, 32u, &out_size, &tick));
    packet[0] ^= 1u;
    base[31] ^= 1u;
    ASSERT_FALSE(physics_sync_decode_delta(base, 32u, packet, size, out, 32u, &out_size, &tick));
    base[31] ^= 1u;
    base[4] ^= 1u;
    ASSERT_FALSE(physics_sync_decode_delta(base, 32u, packet, size, out, 32u, &out_size, &tick));
    base[4] ^= 1u;
    packet[size - 1u] ^= 1u;
    ASSERT_FALSE(physics_sync_decode_delta(base, 32u, packet, size, out, 32u, &out_size, &tick));
    packet[size - 1u] ^= 1u;
    ASSERT_FALSE(physics_sync_decode_delta(base, 32u, packet, size - 1u, out, 32u, &out_size,
                                           &tick));
    ASSERT_FALSE(physics_sync_decode_delta(base, 32u, packet, size - 2u, out, 32u, &out_size,
                                           &tick));
    ASSERT_EQ(out_size, 5u);
    ASSERT_EQ(tick, 66u);

    usize h = PHYSICS_SYNC_DELTA_HEADER_BYTES;
    usize n = h + put_run(packet + h, 4u, 2u, 1u);
    n += put_run(packet + n, 5u, 2u, 2u);
    seal_delta(packet, n, base, 32u);
    ASSERT_FALSE(physics_sync_decode_delta(base, 32u, packet, n, out, 32u, &out_size, &tick));
    n = h + put_run(packet + h, 4u, 2u, 1u);
    n += put_run(packet + n, 6u, 2u, 2u);
    seal_delta(packet, n, base, 32u);
    ASSERT_TRUE(physics_sync_decode_delta(base, 32u, packet, n, out, 32u, &out_size, &tick));
    out_size = 5u;
    tick = 66u;
    n = h + put_run(packet + h, 10u, 2u, 1u);
    n += put_run(packet + n, 4u, 2u, 2u);
    seal_delta(packet, n, base, 32u);
    ASSERT_FALSE(physics_sync_decode_delta(base, 32u, packet, n, out, 32u, &out_size, &tick));
    n = h + put_run(packet + h, 10u, 0u, 1u);
    seal_delta(packet, n, base, 32u);
    ASSERT_FALSE(physics_sync_decode_delta(base, 32u, packet, n, out, 32u, &out_size, &tick));
    n = h + put_run(packet + h, 30u, 3u, 1u);
    seal_delta(packet, n, base, 32u);
    ASSERT_FALSE(physics_sync_decode_delta(base, 32u, packet, n, out, 64u, &out_size, &tick));
    n = h + put_run(packet + h, 29u, 3u, 1u);
    seal_delta(packet, n, base, 32u);
    ASSERT_TRUE(physics_sync_decode_delta(base, 32u, packet, n, out, 32u, &out_size, &tick));
    out_size = 5u;
    tick = 66u;
    n = h + put_run(packet + h, 2u, 2u, 1u);
    wr32(packet + n, 0xfffffffeu);
    wr32(packet + n + 4, 4u);
    memset(packet + n + 8, 3u, 4u);
    n += 12u;
    seal_delta(packet, n, base, 32u);
    ASSERT_FALSE(physics_sync_decode_delta(base, 32u, packet, n, out, 32u, &out_size, &tick));
    n = h + put_run(packet + h, 2u, 2u, 1u);
    wr32(packet + n, 3u);
    n += 4u;
    seal_delta(packet, n, base, 32u);
    ASSERT_FALSE(physics_sync_decode_delta(base, 32u, packet, n, out, 32u, &out_size, &tick));
    ASSERT_EQ(out_size, 5u);
    ASSERT_EQ(tick, 66u);
}

TEST(sync_delta_corrects_a_diverged_world)
{
    PhysicsBodyHandle box_a, box_b;
    PhysicsWorld *a = sync_scene(&box_a);
    PhysicsWorld *b = sync_scene(&box_b);
    PhysicsSyncTracker tracker;
    u32 first = 0;
    u32 applied_tick = 55u;
    physics_sync_init(&tracker);
    for (u32 tick = 1; tick <= 5u; tick++) {
        step_both(a, b);
    }
    usize snap = physics_snapshot_size(a);
    u8 *baseline = malloc(snap);
    u8 *target = malloc(snap);
    u8 *scratch = malloc(snap);
    u8 *packet = malloc(PHYSICS_SYNC_DELTA_HEADER_BYTES + 2u * snap);
    ASSERT_NOT_NULL(baseline);
    ASSERT_NOT_NULL(target);
    ASSERT_NOT_NULL(scratch);
    ASSERT_NOT_NULL(packet);
    ASSERT_TRUE(physics_snapshot_save(a, baseline, snap, NULL));

    physics_body_apply_impulse(b, box_b, vec3(0.0f, 3.0f, 1.0f));
    for (u32 tick = 6; tick <= 8u; tick++) {
        step_both(a, b);
        ASSERT_TRUE(physics_sync_record(&tracker, tick, physics_state_hash(b)));
        (void)physics_sync_check(&tracker, tick, physics_state_hash(a));
    }
    ASSERT_TRUE(physics_sync_desynced(&tracker, &first));
    u64 before = physics_state_hash(b);

    ASSERT_TRUE(physics_snapshot_save(a, target, snap, NULL));
    usize size = 0;
    ASSERT_TRUE(physics_sync_encode_delta(8u, 5u, baseline, snap, target, snap, packet,
                                          PHYSICS_SYNC_DELTA_HEADER_BYTES + 2u * snap, &size));
    ASSERT_TRUE(size < physics_sync_correction_size(a));

    ASSERT_FALSE(physics_sync_apply_delta(&tracker, b, baseline, snap, packet, size, scratch,
                                          snap - 1u, &applied_tick));
    baseline[snap / 2u] ^= 1u;
    ASSERT_FALSE(physics_sync_apply_delta(&tracker, b, baseline, snap, packet, size, scratch,
                                          snap, &applied_tick));
    baseline[snap / 2u] ^= 1u;
    PhysicsWorld *small = physics_world_create(1);
    ASSERT_FALSE(physics_sync_apply_delta(&tracker, small, baseline, snap, packet, size, scratch,
                                          snap, &applied_tick));
    ASSERT_EQ(small->count, 0u);
    physics_world_destroy(small);
    ASSERT_EQ(applied_tick, 55u);
    ASSERT_TRUE(physics_state_hash(b) == before);
    ASSERT_TRUE(physics_sync_desynced(&tracker, NULL));

    ASSERT_TRUE(physics_sync_apply_delta(&tracker, b, baseline, snap, packet, size, scratch, snap,
                                         &applied_tick));
    ASSERT_EQ(applied_tick, 8u);
    ASSERT_FALSE(physics_sync_desynced(&tracker, NULL));
    ASSERT_TRUE(physics_state_hash(b) == physics_state_hash(a));
    ASSERT_EQ(physics_sync_check(&tracker, 8u, physics_state_hash(a)), PHYSICS_SYNC_MATCH);
    for (u32 tick = 9; tick <= 20u; tick++) {
        step_both(a, b);
        ASSERT_TRUE(physics_sync_record(&tracker, tick, physics_state_hash(b)));
        ASSERT_EQ(physics_sync_check(&tracker, tick, physics_state_hash(a)), PHYSICS_SYNC_MATCH);
    }
    free(baseline);
    free(target);
    free(scratch);
    free(packet);
    physics_world_destroy(a);
    physics_world_destroy(b);
}

TEST(sync_baseline_selects_delta_only_after_confirmation)
{
    PhysicsBodyHandle box;
    PhysicsWorld *a = sync_scene(&box);
    for (u32 tick = 1; tick <= 5u; tick++) {
        physics_step(a, 1.0f / 60.0f);
    }
    usize snap = physics_snapshot_size(a);
    usize full = PHYSICS_SYNC_CORRECTION_HEADER_BYTES + snap;
    u8 *s0 = malloc(snap);
    u8 *s1 = malloc(snap);
    u8 *packet = malloc(full);
    ASSERT_NOT_NULL(s0);
    ASSERT_NOT_NULL(s1);
    ASSERT_NOT_NULL(packet);
    ASSERT_TRUE(physics_snapshot_save(a, s0, snap, NULL));

    PhysicsSyncBaseline base;
    physics_sync_baseline_init(&base);
    ASSERT_TRUE(base.bytes == NULL);
    usize size = 0;
    bool delta = true;
    ASSERT_TRUE(physics_sync_baseline_encode(&base, 5u, s0, snap, packet, full, &size, &delta));
    ASSERT_FALSE(delta);
    ASSERT_EQ(size, full);
    ASSERT_EQ(rd32(packet), 0x504e5350u);
    ASSERT_EQ(rd32(packet + 4), 5u);
    const u8 *payload = NULL;
    usize payload_size = 0;
    ASSERT_TRUE(physics_sync_correction_payload(packet, size, &payload, &payload_size));
    ASSERT_TRUE(payload == packet + PHYSICS_SYNC_CORRECTION_HEADER_BYTES);
    ASSERT_EQ(payload_size, snap);
    ASSERT_EQ(memcmp(payload, s0, snap), 0);
    physics_sync_baseline_confirm(&base, 5u);
    ASSERT_FALSE(base.confirmed);

    ASSERT_TRUE(physics_sync_baseline_store(&base, 5u, s0, snap));
    ASSERT_NOT_NULL(base.bytes);
    ASSERT_EQ(base.size, snap);
    ASSERT_EQ(base.tick, 5u);
    ASSERT_FALSE(base.confirmed);
    s0[snap - 1u] ^= 1u;
    ASSERT_FALSE(memcmp(base.bytes, s0, snap) == 0);
    s0[snap - 1u] ^= 1u;
    ASSERT_EQ(memcmp(base.bytes, s0, snap), 0);

    for (u32 tick = 6; tick <= 8u; tick++) {
        physics_step(a, 1.0f / 60.0f);
    }
    ASSERT_TRUE(physics_snapshot_save(a, s1, snap, NULL));
    delta = true;
    ASSERT_TRUE(physics_sync_baseline_encode(&base, 8u, s1, snap, packet, full, &size, &delta));
    ASSERT_FALSE(delta);
    ASSERT_EQ(size, full);
    physics_sync_baseline_confirm(&base, 4u);
    ASSERT_FALSE(base.confirmed);
    ASSERT_TRUE(physics_sync_baseline_encode(&base, 8u, s1, snap, packet, full, &size, &delta));
    ASSERT_FALSE(delta);

    physics_sync_baseline_confirm(&base, 5u);
    ASSERT_TRUE(base.confirmed);
    ASSERT_TRUE(physics_sync_baseline_encode(&base, 8u, s1, snap, packet, full, &size, &delta));
    ASSERT_TRUE(delta);
    ASSERT_TRUE(size < full);
    ASSERT_EQ(rd32(packet), 0x444e5350u);
    ASSERT_EQ(rd32(packet + 4), 8u);
    ASSERT_EQ(rd32(packet + 8), 5u);
    usize need = size;
    ASSERT_FALSE(physics_sync_baseline_encode(&base, 8u, s1, snap, packet, need - 1u, &size,
                                              &delta));
    ASSERT_EQ(size, need);
    ASSERT_FALSE(physics_sync_baseline_encode(&base, 8u, s1, snap, NULL, full, &size, &delta));
    ASSERT_FALSE(physics_sync_baseline_encode(&base, 8u, NULL, snap, packet, full, &size, &delta));
    ASSERT_TRUE(physics_sync_baseline_encode(&base, 8u, s0, snap, packet, full, &size, NULL));
    ASSERT_EQ(size, PHYSICS_SYNC_DELTA_HEADER_BYTES);

    ASSERT_TRUE(physics_sync_baseline_store(&base, 8u, s1, snap));
    ASSERT_FALSE(base.confirmed);
    ASSERT_EQ(base.tick, 8u);
    physics_sync_baseline_confirm(&base, 9u);
    ASSERT_TRUE(base.confirmed);
    PhysicsSyncBaseline fresh;
    physics_sync_baseline_init(&fresh);
    memset(packet, 0xaa, full);
    ASSERT_FALSE(physics_sync_baseline_encode(&fresh, 9u, s1, snap, packet, full - 1u, &size,
                                              &delta));
    ASSERT_FALSE(delta);
    ASSERT_EQ(size, full);
    ASSERT_EQ(packet[0], 0xaau);
    ASSERT_EQ(packet[full - 2u], 0xaau);
    ASSERT_TRUE(physics_sync_baseline_encode(&fresh, 9u, s1, snap, packet, full, &size, &delta));
    ASSERT_EQ(memcmp(packet + PHYSICS_SYNC_CORRECTION_HEADER_BYTES, s1, snap), 0);
    ASSERT_FALSE(physics_sync_baseline_store(&base, 9u, NULL, snap));
    ASSERT_TRUE(base.bytes == NULL);
    ASSERT_EQ(base.size, 0u);
    ASSERT_FALSE(base.confirmed);
    physics_sync_baseline_confirm(&base, 9u);
    ASSERT_FALSE(base.confirmed);
    ASSERT_TRUE(physics_sync_baseline_store(&base, 8u, s1, snap));
    physics_sync_baseline_release(&base);
    ASSERT_TRUE(base.bytes == NULL);
    ASSERT_EQ(base.size, 0u);
    ASSERT_FALSE(base.confirmed);

    u8 small_base[24];
    u8 small_target[24];
    u8 small_packet[64];
    memset(small_base, 1, sizeof(small_base));
    memcpy(small_target, small_base, sizeof(small_target));
    memset(small_target + 8, 9, 4u);
    ASSERT_TRUE(physics_sync_baseline_store(&base, 1u, small_base, sizeof(small_base)));
    physics_sync_baseline_confirm(&base, 1u);
    ASSERT_TRUE(physics_sync_baseline_encode(&base, 2u, small_target, sizeof(small_target),
                                             small_packet, sizeof(small_packet), &size, &delta));
    ASSERT_FALSE(delta);
    ASSERT_EQ(size, PHYSICS_SYNC_CORRECTION_HEADER_BYTES + 24u);
    memset(small_target + 8, 1, 1u);
    ASSERT_TRUE(physics_sync_baseline_encode(&base, 2u, small_target, sizeof(small_target),
                                             small_packet, sizeof(small_packet), &size, &delta));
    ASSERT_TRUE(delta);
    ASSERT_EQ(size, PHYSICS_SYNC_DELTA_HEADER_BYTES + 8u + 3u);
    physics_sync_baseline_release(&base);

    free(s0);
    free(s1);
    free(packet);
    physics_world_destroy(a);
}

TEST(sync_correction_payload_rejects_malformed_packets)
{
    PhysicsBodyHandle box;
    PhysicsWorld *a = sync_scene(&box);
    usize need = physics_sync_correction_size(a);
    u8 *packet = malloc(need);
    const u8 *payload = (const u8 *)1;
    usize payload_size = 77u;
    ASSERT_NOT_NULL(packet);
    ASSERT_TRUE(physics_sync_encode_correction(a, 3u, packet, need, NULL));
    ASSERT_FALSE(physics_sync_correction_payload(NULL, need, &payload, &payload_size));
    ASSERT_FALSE(physics_sync_correction_payload(packet, PHYSICS_SYNC_CORRECTION_HEADER_BYTES - 1u,
                                                 &payload, &payload_size));
    ASSERT_FALSE(physics_sync_correction_payload(packet, need - 1u, &payload, &payload_size));
    packet[0] ^= 1u;
    ASSERT_FALSE(physics_sync_correction_payload(packet, need, &payload, &payload_size));
    packet[0] ^= 1u;
    packet[need - 1u] ^= 1u;
    ASSERT_FALSE(physics_sync_correction_payload(packet, need, &payload, &payload_size));
    packet[need - 1u] ^= 1u;
    ASSERT_TRUE(payload == (const u8 *)1);
    ASSERT_EQ(payload_size, 77u);
    ASSERT_TRUE(physics_sync_correction_payload(packet, need, &payload, &payload_size));
    ASSERT_EQ(payload_size, need - PHYSICS_SYNC_CORRECTION_HEADER_BYTES);
    free(packet);
    physics_world_destroy(a);
}

TEST(sync_receiver_applies_full_then_delta_against_its_baseline)
{
    PhysicsBodyHandle box_a, box_b;
    PhysicsWorld *a = sync_scene(&box_a);
    PhysicsWorld *b = sync_scene(&box_b);
    PhysicsSyncTracker tracker;
    PhysicsSyncBaseline sent;
    PhysicsSyncBaseline held;
    u32 applied = 44u;
    physics_sync_init(&tracker);
    physics_sync_baseline_init(&sent);
    physics_sync_baseline_init(&held);
    usize snap = physics_snapshot_size(a);
    usize full = PHYSICS_SYNC_CORRECTION_HEADER_BYTES + snap;
    u8 *s = malloc(snap);
    u8 *packet = malloc(full);
    u8 *delta_packet = malloc(full);
    ASSERT_NOT_NULL(s);
    ASSERT_NOT_NULL(packet);
    ASSERT_NOT_NULL(delta_packet);

    physics_body_apply_impulse(b, box_b, vec3(0.0f, 2.0f, 0.0f));
    for (u32 tick = 1; tick <= 4u; tick++) {
        step_both(a, b);
    }
    ASSERT_TRUE(physics_snapshot_save(a, s, snap, NULL));
    usize size = 0;
    bool delta = true;
    ASSERT_TRUE(physics_sync_baseline_encode(&sent, 4u, s, snap, packet, full, &size, &delta));
    ASSERT_FALSE(delta);
    ASSERT_TRUE(physics_sync_baseline_store(&sent, 4u, s, snap));

    ASSERT_TRUE(physics_sync_apply_received(&tracker, b, &held, packet, size, &applied));
    ASSERT_EQ(applied, 4u);
    ASSERT_TRUE(physics_state_hash(b) == physics_state_hash(a));
    ASSERT_NOT_NULL(held.bytes);
    ASSERT_EQ(held.tick, 4u);
    ASSERT_EQ(held.size, snap);
    ASSERT_EQ(memcmp(held.bytes, s, snap), 0);
    physics_sync_baseline_confirm(&sent, 4u);

    physics_body_apply_impulse(b, box_b, vec3(1.0f, 0.0f, 0.0f));
    for (u32 tick = 5; tick <= 7u; tick++) {
        step_both(a, b);
    }
    ASSERT_TRUE(physics_snapshot_save(a, s, snap, NULL));
    ASSERT_TRUE(physics_sync_baseline_encode(&sent, 7u, s, snap, delta_packet, full, &size,
                                             &delta));
    ASSERT_TRUE(delta);
    usize delta_size = size;

    ASSERT_TRUE(physics_sync_record(&tracker, 5u, 1u));
    ASSERT_EQ(physics_sync_check(&tracker, 5u, 2u), PHYSICS_SYNC_DESYNC);
    u64 before = physics_state_hash(b);
    applied = 44u;
    PhysicsSyncBaseline empty;
    physics_sync_baseline_init(&empty);
    ASSERT_FALSE(physics_sync_apply_received(&tracker, b, &empty, delta_packet, delta_size,
                                             &applied));
    ASSERT_TRUE(empty.bytes == NULL);
    held.bytes[0] ^= 1u;
    ASSERT_FALSE(physics_sync_apply_received(&tracker, b, &held, delta_packet, delta_size,
                                             &applied));
    held.bytes[0] ^= 1u;
    ASSERT_FALSE(physics_sync_apply_received(&tracker, b, &held, delta_packet, delta_size - 1u,
                                             &applied));
    ASSERT_FALSE(physics_sync_apply_received(&tracker, b, &held, packet, full - 1u, &applied));
    ASSERT_FALSE(physics_sync_apply_received(&tracker, b, &held, NULL, delta_size, &applied));
    ASSERT_FALSE(physics_sync_apply_received(&tracker, b, &held, delta_packet, 3u, &applied));
    ASSERT_FALSE(physics_sync_apply_received(&tracker, b, &held, delta_packet,
                                             PHYSICS_SYNC_DELTA_HEADER_BYTES - 1u, &applied));
    u8 huge[PHYSICS_SYNC_DELTA_HEADER_BYTES];
    memcpy(huge, delta_packet, sizeof(huge));
    huge[20] = 0xffu;
    huge[21] = 0xffu;
    huge[22] = 0xffu;
    huge[23] = 0x7fu;
    ASSERT_FALSE(physics_sync_apply_received(&tracker, b, &held, huge, sizeof(huge), &applied));
    PhysicsWorld *tiny = physics_world_create(1);
    PhysicsSyncBaseline tiny_held;
    physics_sync_baseline_init(&tiny_held);
    ASSERT_FALSE(physics_sync_apply_received(&tracker, tiny, &tiny_held, packet, full, &applied));
    ASSERT_TRUE(tiny_held.bytes == NULL);
    ASSERT_EQ(tiny->count, 0u);
    physics_world_destroy(tiny);
    ASSERT_EQ(applied, 44u);
    ASSERT_EQ(held.tick, 4u);
    ASSERT_TRUE(physics_state_hash(b) == before);
    ASSERT_TRUE(physics_sync_desynced(&tracker, NULL));

    ASSERT_TRUE(physics_sync_apply_received(&tracker, b, &held, delta_packet, delta_size,
                                            &applied));
    ASSERT_EQ(applied, 7u);
    ASSERT_FALSE(physics_sync_desynced(&tracker, NULL));
    ASSERT_TRUE(physics_state_hash(b) == physics_state_hash(a));
    ASSERT_EQ(held.tick, 7u);
    ASSERT_EQ(memcmp(held.bytes, s, snap), 0);
    ASSERT_EQ(physics_sync_check(&tracker, 7u, physics_state_hash(a)), PHYSICS_SYNC_MATCH);

    physics_sync_baseline_release(&sent);
    physics_sync_baseline_release(&held);
    free(s);
    free(packet);
    free(delta_packet);
    physics_world_destroy(a);
    physics_world_destroy(b);
}

TEST_MAIN_BEGIN()
    RUN_TEST(sync_report_round_trip_and_rejection);
    RUN_TEST(sync_lockstep_worlds_match);
    RUN_TEST(sync_impulse_on_one_world_is_detected_and_latched);
    RUN_TEST(sync_window_and_ordering_rules);
    RUN_TEST(sync_correction_restores_the_diverged_peer);
    RUN_TEST(sync_correction_rejects_malformed_packets);
    RUN_TEST(sync_delta_encodes_only_changed_runs);
    RUN_TEST(sync_delta_handles_grown_and_shrunk_targets);
    RUN_TEST(sync_delta_decode_rejects_malformed_packets);
    RUN_TEST(sync_delta_corrects_a_diverged_world);
    RUN_TEST(sync_baseline_selects_delta_only_after_confirmation);
    RUN_TEST(sync_correction_payload_rejects_malformed_packets);
    RUN_TEST(sync_receiver_applies_full_then_delta_against_its_baseline);
TEST_MAIN_END()
