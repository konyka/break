#include "test_framework.h"
#include <physics/physics_replay.h>
#include <math.h>
#include <stdint.h>

#define REPLAY_CAP 64u

static PhysicsWorld *replay_scene(PhysicsBodyHandle *out_box)
{
    PhysicsWorld *pw = physics_world_create(8);
    (void)physics_body_create(pw, vec3(0, -1, 0), vec3(10, 1, 10), 0.0f, true, 0);
    *out_box = physics_body_create(pw, vec3(0, 2, 0), vec3(0.5f, 0.5f, 0.5f), 1.0f, false, 0);
    (void)physics_body_create_sphere(pw, vec3(1, 4, 0), 0.5f, 1.0f, false, 0);
    return pw;
}

/* Records 40 steps with impulses, encodes, decodes into a fresh log,
 * restores the snapshot and replays; the state must match. */
static void record_session(PhysicsReplay *log, PhysicsWorld *pw, PhysicsBodyHandle box)
{
    for (u32 i = 0; i < 40u; i++) {
        if (i % 10u == 0u) {
            ASSERT_TRUE(physics_replay_impulse(log, pw, box, vec3(0.5f, 1.0f, -0.25f)));
        }
        ASSERT_TRUE(physics_replay_step(log, pw, 1.0f / 60.0f));
    }
}

TEST(replay_round_trip_reproduces_the_recorded_run)
{
    PhysicsReplayRecord storage[REPLAY_CAP];
    PhysicsReplayRecord decoded_storage[REPLAY_CAP];
    PhysicsReplay log, decoded;
    PhysicsBodyHandle box;
    PhysicsWorld *pw = replay_scene(&box);
    usize snap_size = physics_snapshot_size(pw);
    void *snap = malloc(snap_size);
    ASSERT_NOT_NULL(snap);
    ASSERT_TRUE(physics_snapshot_save(pw, snap, snap_size, NULL));
    ASSERT_TRUE(physics_replay_init(&log, storage, REPLAY_CAP));
    record_session(&log, pw, box);
    ASSERT_EQ(log.count, 44u);
    u64 final_hash = physics_state_hash(pw);

    usize size = 0u;
    ASSERT_FALSE(physics_replay_encode(&log, NULL, 0u, &size));
    ASSERT_EQ(size, (usize)PHYSICS_REPLAY_HEADER_BYTES + 44u * PHYSICS_REPLAY_RECORD_BYTES);
    u8 *wire = (u8 *)malloc(size);
    ASSERT_NOT_NULL(wire);
    ASSERT_TRUE(physics_replay_encode(&log, wire, size, &size));
    ASSERT_EQ(wire[0], 'P');
    ASSERT_EQ(wire[1], 'R');
    ASSERT_EQ(wire[2], 'P');
    ASSERT_EQ(wire[3], 'L');
    ASSERT_EQ(wire[4], 1u);
    ASSERT_EQ(wire[8], 44u);
    ASSERT_EQ(wire[12], PHYSICS_REPLAY_OP_IMPULSE);
    ASSERT_EQ(wire[16], (u8)box.index);

    ASSERT_TRUE(physics_replay_init(&decoded, decoded_storage, REPLAY_CAP));
    ASSERT_TRUE(physics_replay_decode(&decoded, wire, size));
    ASSERT_EQ(decoded.count, log.count);
    for (u32 i = 0; i < log.count; i++) {
        ASSERT_EQ(decoded.records[i].op, log.records[i].op);
        ASSERT_TRUE(physics_body_handle_equal(decoded.records[i].body, log.records[i].body));
        ASSERT_TRUE(memcmp(decoded.records[i].value, log.records[i].value,
                           sizeof(log.records[i].value)) == 0);
        ASSERT_EQ(decoded.records[i].hash_after, log.records[i].hash_after);
    }

    ASSERT_TRUE(physics_snapshot_restore(pw, snap, snap_size));
    u32 divergent = 0u;
    ASSERT_EQ(physics_replay_run(&decoded, pw, &divergent), PHYSICS_REPLAY_OK);
    ASSERT_EQ(divergent, UINT32_MAX);
    ASSERT_EQ(physics_state_hash(pw), final_hash);
    free(wire);
    free(snap);
    physics_world_destroy(pw);
}

TEST(replay_reports_the_first_divergent_step)
{
    PhysicsReplayRecord storage[REPLAY_CAP];
    PhysicsReplay log;
    PhysicsBodyHandle box;
    PhysicsWorld *pw = replay_scene(&box);
    usize snap_size = physics_snapshot_size(pw);
    void *snap = malloc(snap_size);
    ASSERT_NOT_NULL(snap);
    ASSERT_TRUE(physics_snapshot_save(pw, snap, snap_size, NULL));
    ASSERT_TRUE(physics_replay_init(&log, storage, REPLAY_CAP));
    record_session(&log, pw, box);

    /* Record 11 is the impulse before step 10; the step after it is 12. */
    ASSERT_EQ(log.records[11].op, PHYSICS_REPLAY_OP_IMPULSE);
    log.records[11].value[1] += 0.5f;
    ASSERT_TRUE(physics_snapshot_restore(pw, snap, snap_size));
    u32 divergent = 0u;
    ASSERT_EQ(physics_replay_run(&log, pw, &divergent), PHYSICS_REPLAY_DIVERGED);
    ASSERT_EQ(divergent, 12u);
    log.records[11].value[1] -= 0.5f;

    log.records[30].hash_after ^= 1u;
    ASSERT_TRUE(physics_snapshot_restore(pw, snap, snap_size));
    ASSERT_EQ(physics_replay_run(&log, pw, &divergent), PHYSICS_REPLAY_DIVERGED);
    ASSERT_EQ(divergent, 30u);
    log.records[30].hash_after ^= 1u;

    ASSERT_TRUE(physics_snapshot_restore(pw, snap, snap_size));
    ASSERT_EQ(physics_replay_run(&log, pw, &divergent), PHYSICS_REPLAY_OK);
    ASSERT_EQ(physics_replay_run(NULL, pw, &divergent), PHYSICS_REPLAY_INVALID);
    free(snap);
    physics_world_destroy(pw);
}

TEST(replay_recording_rejects_bad_inputs)
{
    PhysicsReplayRecord storage[2];
    PhysicsReplay log;
    PhysicsBodyHandle box;
    PhysicsWorld *pw = replay_scene(&box);
    ASSERT_FALSE(physics_replay_init(NULL, storage, 2u));
    ASSERT_FALSE(physics_replay_init(&log, NULL, 2u));
    ASSERT_TRUE(physics_replay_init(&log, storage, 2u));
    u64 before = physics_state_hash(pw);
    ASSERT_FALSE(physics_replay_impulse(&log, pw, PHYSICS_BODY_HANDLE_INVALID, vec3(1, 0, 0)));
    ASSERT_FALSE(physics_replay_impulse(&log, pw, box, vec3(NAN, 0, 0)));
    ASSERT_FALSE(physics_replay_step(&log, pw, 0.0f));
    ASSERT_FALSE(physics_replay_step(&log, pw, INFINITY));
    ASSERT_EQ(log.count, 0u);
    ASSERT_EQ(physics_state_hash(pw), before);
    ASSERT_TRUE(physics_replay_impulse(&log, pw, box, vec3(1, 0, 0)));
    ASSERT_TRUE(physics_replay_step(&log, pw, 1.0f / 60.0f));
    u64 full = physics_state_hash(pw);
    ASSERT_FALSE(physics_replay_step(&log, pw, 1.0f / 60.0f));
    ASSERT_FALSE(physics_replay_impulse(&log, pw, box, vec3(1, 0, 0)));
    ASSERT_EQ(log.count, 2u);
    ASSERT_EQ(physics_state_hash(pw), full);
    physics_world_destroy(pw);
}

TEST(replay_decode_rejects_malformed_data)
{
    PhysicsReplayRecord storage[4];
    PhysicsReplayRecord small_storage[1];
    PhysicsReplay log, target, small;
    PhysicsBodyHandle box;
    PhysicsWorld *pw = replay_scene(&box);
    ASSERT_TRUE(physics_replay_init(&log, storage, 4u));
    ASSERT_TRUE(physics_replay_impulse(&log, pw, box, vec3(1, 0, 0)));
    ASSERT_TRUE(physics_replay_step(&log, pw, 1.0f / 60.0f));
    u8 wire[PHYSICS_REPLAY_HEADER_BYTES + 2u * PHYSICS_REPLAY_RECORD_BYTES];
    usize size = 0u;
    u8 tiny[4] = {0xab, 0xab, 0xab, 0xab};
    ASSERT_FALSE(physics_replay_encode(&log, tiny, sizeof(tiny), &size));
    ASSERT_EQ(size, sizeof(wire));
    ASSERT_EQ(tiny[0], 0xabu);
    ASSERT_TRUE(physics_replay_encode(&log, wire, sizeof(wire), &size));

    PhysicsReplayRecord target_storage[4];
    ASSERT_TRUE(physics_replay_init(&target, target_storage, 4u));
    ASSERT_FALSE(physics_replay_decode(&target, wire, size - 1u));
    ASSERT_FALSE(physics_replay_decode(&target, NULL, size));
    ASSERT_FALSE(physics_replay_decode(NULL, wire, size));
    struct { usize offset; u8 flip; } cases[] = {
        {0u, 0x01u},                                     /* magic */
        {4u, 0x02u},                                     /* version */
        {8u, 0x01u},                                     /* count vs length */
        {PHYSICS_REPLAY_HEADER_BYTES + 0u, 0x04u},       /* op */
        {PHYSICS_REPLAY_HEADER_BYTES + 15u, 0x7fu},      /* value[0] -> NaN */
        {PHYSICS_REPLAY_HEADER_BYTES + 32u + 15u, 0x7fu} /* step dt -> NaN */
    };
    for (usize c = 0; c < sizeof(cases) / sizeof(cases[0]); c++) {
        if (cases[c].flip == 0x7fu) {
            /* High two bytes of a little-endian f32 -> 0x7fc0xxxx (NaN). */
            wire[cases[c].offset] = 0x7fu;
            wire[cases[c].offset - 1u] = 0xc0u;
        } else {
            wire[cases[c].offset] = (u8)(wire[cases[c].offset] ^ cases[c].flip);
        }
        ASSERT_FALSE(physics_replay_decode(&target, wire, size));
        ASSERT_EQ(target.count, 0u);
        ASSERT_TRUE(physics_replay_encode(&log, wire, sizeof(wire), &size));
    }
    ASSERT_TRUE(physics_replay_init(&small, small_storage, 1u));
    ASSERT_FALSE(physics_replay_decode(&small, wire, size));
    ASSERT_EQ(small.count, 0u);
    ASSERT_TRUE(physics_replay_decode(&target, wire, size));
    ASSERT_EQ(target.count, 2u);
    physics_world_destroy(pw);
}

TEST_MAIN_BEGIN()
    RUN_TEST(replay_round_trip_reproduces_the_recorded_run);
    RUN_TEST(replay_reports_the_first_divergent_step);
    RUN_TEST(replay_recording_rejects_bad_inputs);
    RUN_TEST(replay_decode_rejects_malformed_data);
TEST_MAIN_END()
