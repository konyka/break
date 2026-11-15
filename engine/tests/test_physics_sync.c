#include "test_framework.h"
#include <physics/physics_sync.h>
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

TEST_MAIN_BEGIN()
    RUN_TEST(sync_report_round_trip_and_rejection);
    RUN_TEST(sync_lockstep_worlds_match);
    RUN_TEST(sync_impulse_on_one_world_is_detected_and_latched);
    RUN_TEST(sync_window_and_ordering_rules);
TEST_MAIN_END()
