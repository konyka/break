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

TEST_MAIN_BEGIN()
    RUN_TEST(sync_report_round_trip_and_rejection);
    RUN_TEST(sync_lockstep_worlds_match);
    RUN_TEST(sync_impulse_on_one_world_is_detected_and_latched);
    RUN_TEST(sync_window_and_ordering_rules);
    RUN_TEST(sync_correction_restores_the_diverged_peer);
    RUN_TEST(sync_correction_rejects_malformed_packets);
TEST_MAIN_END()
