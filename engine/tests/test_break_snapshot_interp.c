/* Snapshot interpolation for remote entities: blending between server
 * snapshots a fixed delay behind, bounded extrapolation, teleport gaps and
 * out-of-order arrival. */
#include "test_framework.h"

#include <network/break_snapshot_interp.h>

#include <math.h>
#include <string.h>

static BreakSnapshotPose pose_at(f32 x, f32 y, f32 z) {
    BreakSnapshotPose p;
    p.position[0] = x;
    p.position[1] = y;
    p.position[2] = z;
    p.rotation[0] = 0.0f;
    p.rotation[1] = 0.0f;
    p.rotation[2] = 0.0f;
    p.rotation[3] = 1.0f;
    return p;
}

/* rotation of `deg` degrees about +y */
static BreakSnapshotPose yaw(f32 deg) {
    BreakSnapshotPose p = pose_at(0.0f, 0.0f, 0.0f);
    f32 h = deg * 3.14159265f / 360.0f;
    p.rotation[1] = sinf(h);
    p.rotation[3] = cosf(h);
    return p;
}

static void init(BreakSnapshotInterp *si, f32 extrapolate, f32 gap) {
    BreakSnapshotInterpConfig cfg;
    cfg.max_extrapolate_ticks = extrapolate;
    cfg.max_gap_ticks = gap;
    (void)break_snapshot_interp_init(si, &cfg);
}

TEST(positions_blend_linearly_between_the_two_surrounding_snapshots) {
    BreakSnapshotInterp si;
    BreakSnapshotPose a = pose_at(0.0f, 0.0f, 0.0f), b = pose_at(10.0f, -4.0f, 2.0f), out;
    init(&si, 0.0f, 8.0f);
    ASSERT_EQ(break_snapshot_interp_push(&si, 100u, &a), BREAK_SNAPSHOT_PUSH_OK);
    ASSERT_EQ(break_snapshot_interp_push(&si, 104u, &b), BREAK_SNAPSHOT_PUSH_OK);
    ASSERT_EQ(break_snapshot_interp_sample(&si, 101.0, &out), BREAK_SNAPSHOT_INTERP_INTERPOLATED);
    ASSERT_FLOAT_EQ(out.position[0], 2.5f, 1e-5f);
    ASSERT_FLOAT_EQ(out.position[1], -1.0f, 1e-5f);
    ASSERT_FLOAT_EQ(out.position[2], 0.5f, 1e-5f);
    ASSERT_EQ(break_snapshot_interp_sample(&si, 100.0, &out), BREAK_SNAPSHOT_INTERP_INTERPOLATED);
    ASSERT_FLOAT_EQ(out.position[0], 0.0f, 1e-6f);
    ASSERT_EQ(break_snapshot_interp_sample(&si, 104.0, &out), BREAK_SNAPSHOT_INTERP_INTERPOLATED);
    ASSERT_FLOAT_EQ(out.position[0], 10.0f, 1e-6f);
}

TEST(rotation_slerps_along_the_shorter_arc) {
    BreakSnapshotInterp si;
    BreakSnapshotPose a = yaw(0.0f), b = yaw(90.0f), out;
    BreakSnapshotPose flipped;
    init(&si, 0.0f, 8.0f);
    ASSERT_EQ(break_snapshot_interp_push(&si, 1u, &a), BREAK_SNAPSHOT_PUSH_OK);
    ASSERT_EQ(break_snapshot_interp_push(&si, 3u, &b), BREAK_SNAPSHOT_PUSH_OK);
    ASSERT_EQ(break_snapshot_interp_sample(&si, 2.0, &out), BREAK_SNAPSHOT_INTERP_INTERPOLATED);
    /* halfway is 45 degrees: y = sin(22.5), w = cos(22.5) */
    ASSERT_FLOAT_EQ(out.rotation[1], 0.38268343f, 1e-5f);
    ASSERT_FLOAT_EQ(out.rotation[3], 0.92387953f, 1e-5f);
    /* a quarter of the way is 22.5 degrees: the two slerp weights differ */
    ASSERT_EQ(break_snapshot_interp_sample(&si, 1.5, &out), BREAK_SNAPSHOT_INTERP_INTERPOLATED);
    ASSERT_FLOAT_EQ(out.rotation[1], 0.19509032f, 1e-5f);
    ASSERT_FLOAT_EQ(out.rotation[3], 0.98078528f, 1e-5f);
    /* the same 90 degrees given as the negated quaternion takes the same path */
    flipped = b;
    for (int k = 0; k < 4; ++k) flipped.rotation[k] = -flipped.rotation[k];
    init(&si, 0.0f, 8.0f);
    ASSERT_EQ(break_snapshot_interp_push(&si, 1u, &a), BREAK_SNAPSHOT_PUSH_OK);
    ASSERT_EQ(break_snapshot_interp_push(&si, 3u, &flipped), BREAK_SNAPSHOT_PUSH_OK);
    ASSERT_EQ(break_snapshot_interp_sample(&si, 2.0, &out), BREAK_SNAPSHOT_INTERP_INTERPOLATED);
    ASSERT_FLOAT_EQ(fabsf(out.rotation[1]), 0.38268343f, 1e-5f);
    ASSERT_FLOAT_EQ(fabsf(out.rotation[3]), 0.92387953f, 1e-5f);
    ASSERT_TRUE(out.rotation[1] * out.rotation[3] > 0.0f);
    /* nearly identical rotations do not divide by a vanishing sine */
    init(&si, 0.0f, 8.0f);
    a = yaw(10.0f);
    b = yaw(10.0001f);
    ASSERT_EQ(break_snapshot_interp_push(&si, 1u, &a), BREAK_SNAPSHOT_PUSH_OK);
    ASSERT_EQ(break_snapshot_interp_push(&si, 2u, &b), BREAK_SNAPSHOT_PUSH_OK);
    ASSERT_EQ(break_snapshot_interp_sample(&si, 1.5, &out), BREAK_SNAPSHOT_INTERP_INTERPOLATED);
    ASSERT_TRUE(isfinite(out.rotation[1]) && isfinite(out.rotation[3]));
    ASSERT_FLOAT_EQ(out.rotation[1], a.rotation[1], 1e-5f);
}

TEST(incoming_quaternions_are_normalized_and_zero_ones_refused) {
    BreakSnapshotInterp si;
    BreakSnapshotPose p = pose_at(1.0f, 2.0f, 3.0f), out;
    init(&si, 0.0f, 8.0f);
    p.rotation[3] = 4.0f;
    ASSERT_EQ(break_snapshot_interp_push(&si, 1u, &p), BREAK_SNAPSHOT_PUSH_OK);
    ASSERT_EQ(break_snapshot_interp_sample(&si, 1.0, &out), BREAK_SNAPSHOT_INTERP_HELD);
    ASSERT_FLOAT_EQ(out.rotation[3], 1.0f, 1e-6f);
    p.rotation[3] = 0.0f;
    ASSERT_EQ(break_snapshot_interp_push(&si, 2u, &p), BREAK_SNAPSHOT_PUSH_INVALID);
    p = pose_at(NAN, 0.0f, 0.0f);
    ASSERT_EQ(break_snapshot_interp_push(&si, 3u, &p), BREAK_SNAPSHOT_PUSH_INVALID);
    p = pose_at(0.0f, 0.0f, 0.0f);
    p.rotation[0] = INFINITY;
    ASSERT_EQ(break_snapshot_interp_push(&si, 4u, &p), BREAK_SNAPSHOT_PUSH_INVALID);
    ASSERT_EQ(break_snapshot_interp_push(&si, 5u, NULL), BREAK_SNAPSHOT_PUSH_INVALID);
    ASSERT_EQ(break_snapshot_interp_push(NULL, 5u, &p), BREAK_SNAPSHOT_PUSH_INVALID);
    ASSERT_EQ(break_snapshot_interp_count(&si), 1u);
}

TEST(out_of_order_and_duplicate_snapshots_are_sorted_or_ignored) {
    BreakSnapshotInterp si;
    BreakSnapshotPose a = pose_at(0.0f, 0.0f, 0.0f), b = pose_at(4.0f, 0.0f, 0.0f);
    BreakSnapshotPose c = pose_at(8.0f, 0.0f, 0.0f), out;
    init(&si, 0.0f, 8.0f);
    ASSERT_EQ(break_snapshot_interp_push(&si, 30u, &c), BREAK_SNAPSHOT_PUSH_OK);
    ASSERT_EQ(break_snapshot_interp_push(&si, 10u, &a), BREAK_SNAPSHOT_PUSH_OK);
    ASSERT_EQ(break_snapshot_interp_push(&si, 20u, &b), BREAK_SNAPSHOT_PUSH_OK);
    ASSERT_EQ(break_snapshot_interp_push(&si, 20u, &c), BREAK_SNAPSHOT_PUSH_DUPLICATE);
    ASSERT_EQ(break_snapshot_interp_count(&si), 3u);
    init(&si, 0.0f, 20.0f);
    ASSERT_EQ(break_snapshot_interp_push(&si, 30u, &c), BREAK_SNAPSHOT_PUSH_OK);
    ASSERT_EQ(break_snapshot_interp_push(&si, 10u, &a), BREAK_SNAPSHOT_PUSH_OK);
    ASSERT_EQ(break_snapshot_interp_push(&si, 20u, &b), BREAK_SNAPSHOT_PUSH_OK);
    ASSERT_EQ(break_snapshot_interp_sample(&si, 15.0, &out), BREAK_SNAPSHOT_INTERP_INTERPOLATED);
    ASSERT_FLOAT_EQ(out.position[0], 2.0f, 1e-5f);
    ASSERT_EQ(break_snapshot_interp_sample(&si, 25.0, &out), BREAK_SNAPSHOT_INTERP_INTERPOLATED);
    ASSERT_FLOAT_EQ(out.position[0], 6.0f, 1e-5f);
}

TEST(past_the_newest_snapshot_motion_is_extrapolated_then_held) {
    BreakSnapshotInterp si;
    BreakSnapshotPose a = pose_at(0.0f, 0.0f, 0.0f), b = pose_at(2.0f, 0.0f, 0.0f), out;
    init(&si, 3.0f, 8.0f);
    ASSERT_EQ(break_snapshot_interp_push(&si, 10u, &a), BREAK_SNAPSHOT_PUSH_OK);
    ASSERT_EQ(break_snapshot_interp_push(&si, 12u, &b), BREAK_SNAPSHOT_PUSH_OK);
    /* velocity 1 per tick */
    ASSERT_EQ(break_snapshot_interp_sample(&si, 14.0, &out), BREAK_SNAPSHOT_INTERP_EXTRAPOLATED);
    ASSERT_FLOAT_EQ(out.position[0], 4.0f, 1e-5f);
    ASSERT_EQ(break_snapshot_interp_sample(&si, 15.0, &out), BREAK_SNAPSHOT_INTERP_EXTRAPOLATED);
    ASSERT_FLOAT_EQ(out.position[0], 5.0f, 1e-5f);
    /* beyond 3 ticks it stays where the extrapolation ended */
    ASSERT_EQ(break_snapshot_interp_sample(&si, 40.0, &out), BREAK_SNAPSHOT_INTERP_HELD);
    ASSERT_FLOAT_EQ(out.position[0], 5.0f, 1e-5f);
    /* with extrapolation off it holds the newest snapshot */
    init(&si, 0.0f, 8.0f);
    ASSERT_EQ(break_snapshot_interp_push(&si, 10u, &a), BREAK_SNAPSHOT_PUSH_OK);
    ASSERT_EQ(break_snapshot_interp_push(&si, 12u, &b), BREAK_SNAPSHOT_PUSH_OK);
    ASSERT_EQ(break_snapshot_interp_sample(&si, 13.0, &out), BREAK_SNAPSHOT_INTERP_HELD);
    ASSERT_FLOAT_EQ(out.position[0], 2.0f, 1e-6f);
    /* a single snapshot cannot be extrapolated */
    init(&si, 3.0f, 8.0f);
    ASSERT_EQ(break_snapshot_interp_push(&si, 10u, &a), BREAK_SNAPSHOT_PUSH_OK);
    ASSERT_EQ(break_snapshot_interp_sample(&si, 11.0, &out), BREAK_SNAPSHOT_INTERP_HELD);
}

TEST(extrapolation_does_not_continue_across_a_teleport) {
    BreakSnapshotInterp si;
    BreakSnapshotPose a = pose_at(0.0f, 0.0f, 0.0f), b = pose_at(500.0f, 0.0f, 0.0f), out;
    init(&si, 3.0f, 4.0f);
    ASSERT_EQ(break_snapshot_interp_push(&si, 10u, &a), BREAK_SNAPSHOT_PUSH_OK);
    ASSERT_EQ(break_snapshot_interp_push(&si, 20u, &b), BREAK_SNAPSHOT_PUSH_OK);
    ASSERT_EQ(break_snapshot_interp_sample(&si, 22.0, &out), BREAK_SNAPSHOT_INTERP_HELD);
    ASSERT_FLOAT_EQ(out.position[0], 500.0f, 1e-4f);
}

TEST(a_gap_wider_than_the_limit_is_not_blended) {
    BreakSnapshotInterp si;
    BreakSnapshotPose a = pose_at(0.0f, 0.0f, 0.0f), b = pose_at(100.0f, 0.0f, 0.0f), out;
    init(&si, 0.0f, 4.0f);
    ASSERT_EQ(break_snapshot_interp_push(&si, 10u, &a), BREAK_SNAPSHOT_PUSH_OK);
    ASSERT_EQ(break_snapshot_interp_push(&si, 15u, &b), BREAK_SNAPSHOT_PUSH_OK);
    ASSERT_EQ(break_snapshot_interp_sample(&si, 12.0, &out), BREAK_SNAPSHOT_INTERP_HELD);
    ASSERT_FLOAT_EQ(out.position[0], 0.0f, 1e-6f);
    ASSERT_EQ(break_snapshot_interp_sample(&si, 15.0, &out), BREAK_SNAPSHOT_INTERP_HELD);
    ASSERT_FLOAT_EQ(out.position[0], 100.0f, 1e-6f);
    /* exactly the limit is still blended */
    init(&si, 0.0f, 5.0f);
    ASSERT_EQ(break_snapshot_interp_push(&si, 10u, &a), BREAK_SNAPSHOT_PUSH_OK);
    ASSERT_EQ(break_snapshot_interp_push(&si, 15u, &b), BREAK_SNAPSHOT_PUSH_OK);
    ASSERT_EQ(break_snapshot_interp_sample(&si, 12.0, &out), BREAK_SNAPSHOT_INTERP_INTERPOLATED);
    ASSERT_FLOAT_EQ(out.position[0], 40.0f, 1e-4f);
}

TEST(before_the_oldest_snapshot_the_oldest_is_held) {
    BreakSnapshotInterp si;
    BreakSnapshotPose a = pose_at(3.0f, 0.0f, 0.0f), b = pose_at(5.0f, 0.0f, 0.0f), out;
    init(&si, 2.0f, 8.0f);
    ASSERT_EQ(break_snapshot_interp_sample(&si, 1.0, &out), BREAK_SNAPSHOT_INTERP_EMPTY);
    ASSERT_EQ(break_snapshot_interp_push(&si, 10u, &a), BREAK_SNAPSHOT_PUSH_OK);
    ASSERT_EQ(break_snapshot_interp_push(&si, 11u, &b), BREAK_SNAPSHOT_PUSH_OK);
    ASSERT_EQ(break_snapshot_interp_sample(&si, 2.0, &out), BREAK_SNAPSHOT_INTERP_HELD);
    ASSERT_FLOAT_EQ(out.position[0], 3.0f, 1e-6f);
}

TEST(a_full_buffer_drops_the_oldest_and_refuses_older) {
    BreakSnapshotInterp si;
    BreakSnapshotPose out;
    init(&si, 0.0f, 100.0f);
    for (u32 i = 0u; i < BREAK_SNAPSHOT_INTERP_CAPACITY; ++i) {
        BreakSnapshotPose p = pose_at((f32)i, 0.0f, 0.0f);
        ASSERT_EQ(break_snapshot_interp_push(&si, 100u + i, &p), BREAK_SNAPSHOT_PUSH_OK);
    }
    {
        BreakSnapshotPose old = pose_at(-1.0f, 0.0f, 0.0f);
        BreakSnapshotPose newer = pose_at(99.0f, 0.0f, 0.0f);
        ASSERT_EQ(break_snapshot_interp_push(&si, 99u, &old), BREAK_SNAPSHOT_PUSH_TOO_OLD);
        ASSERT_EQ(break_snapshot_interp_push(&si, 200u, &newer), BREAK_SNAPSHOT_PUSH_OK);
    }
    ASSERT_EQ(break_snapshot_interp_count(&si), BREAK_SNAPSHOT_INTERP_CAPACITY);
    /* tick 100 was dropped; 101 is now the oldest */
    ASSERT_EQ(break_snapshot_interp_sample(&si, 100.0, &out), BREAK_SNAPSHOT_INTERP_HELD);
    ASSERT_FLOAT_EQ(out.position[0], 1.0f, 1e-6f);
    /* an out-of-order one between the kept ticks still fits after the drop */
    {
        BreakSnapshotPose mid = pose_at(50.0f, 0.0f, 0.0f);
        ASSERT_EQ(break_snapshot_interp_push(&si, 150u, &mid), BREAK_SNAPSHOT_PUSH_OK);
        ASSERT_EQ(break_snapshot_interp_sample(&si, 150.0, &out),
                  BREAK_SNAPSHOT_INTERP_INTERPOLATED);
        ASSERT_FLOAT_EQ(out.position[0], 50.0f, 1e-6f);
    }
}

TEST(discarding_keeps_the_snapshot_still_needed_for_blending) {
    BreakSnapshotInterp si;
    BreakSnapshotPose out;
    init(&si, 0.0f, 8.0f);
    for (u32 i = 0u; i < 6u; ++i) {
        BreakSnapshotPose p = pose_at((f32)(i * 2u), 0.0f, 0.0f);
        ASSERT_EQ(break_snapshot_interp_push(&si, 10u + i, &p), BREAK_SNAPSHOT_PUSH_OK);
    }
    break_snapshot_interp_discard_before(&si, 12.5);
    ASSERT_EQ(break_snapshot_interp_count(&si), 4u); /* 12, 13, 14, 15 */
    ASSERT_EQ(break_snapshot_interp_sample(&si, 12.5, &out), BREAK_SNAPSHOT_INTERP_INTERPOLATED);
    ASSERT_FLOAT_EQ(out.position[0], 5.0f, 1e-5f);
    /* a cut exactly on a tick keeps that tick and drops the one before */
    break_snapshot_interp_discard_before(&si, 13.0);
    ASSERT_EQ(break_snapshot_interp_count(&si), 3u); /* 13, 14, 15 */
    ASSERT_EQ(break_snapshot_interp_sample(&si, 12.5, &out), BREAK_SNAPSHOT_INTERP_HELD);
    ASSERT_FLOAT_EQ(out.position[0], 6.0f, 1e-6f);
    break_snapshot_interp_discard_before(&si, NAN);
    ASSERT_EQ(break_snapshot_interp_count(&si), 3u);
    break_snapshot_interp_discard_before(&si, 100.0);
    ASSERT_EQ(break_snapshot_interp_count(&si), 1u);
    ASSERT_EQ(break_snapshot_interp_sample(&si, 100.0, &out), BREAK_SNAPSHOT_INTERP_HELD);
    ASSERT_FLOAT_EQ(out.position[0], 10.0f, 1e-6f);
    break_snapshot_interp_discard_before(&si, 1.0); /* nothing older: no change */
    ASSERT_EQ(break_snapshot_interp_count(&si), 1u);
    break_snapshot_interp_discard_before(NULL, 1.0);
}

TEST(config_and_sample_arguments_are_validated) {
    BreakSnapshotInterp si;
    BreakSnapshotInterpConfig cfg = {1.0f, 4.0f};
    BreakSnapshotPose p = pose_at(0.0f, 0.0f, 0.0f), out;
    ASSERT_TRUE(break_snapshot_interp_init(&si, &cfg));
    ASSERT_FALSE(break_snapshot_interp_init(NULL, &cfg));
    ASSERT_FALSE(break_snapshot_interp_init(&si, NULL));
    cfg.max_extrapolate_ticks = -0.5f;
    ASSERT_FALSE(break_snapshot_interp_init(&si, &cfg));
    cfg.max_extrapolate_ticks = NAN;
    ASSERT_FALSE(break_snapshot_interp_init(&si, &cfg));
    cfg.max_extrapolate_ticks = 1.0f;
    cfg.max_gap_ticks = 0.0f;
    ASSERT_FALSE(break_snapshot_interp_init(&si, &cfg));
    cfg.max_gap_ticks = INFINITY;
    ASSERT_FALSE(break_snapshot_interp_init(&si, &cfg));
    cfg.max_gap_ticks = 4.0f;
    ASSERT_TRUE(break_snapshot_interp_init(&si, &cfg));
    ASSERT_EQ(break_snapshot_interp_push(&si, 1u, &p), BREAK_SNAPSHOT_PUSH_OK);
    ASSERT_EQ(break_snapshot_interp_sample(&si, NAN, &out), BREAK_SNAPSHOT_INTERP_INVALID);
    ASSERT_EQ(break_snapshot_interp_sample(&si, 1.0, NULL), BREAK_SNAPSHOT_INTERP_INVALID);
    ASSERT_EQ(break_snapshot_interp_sample(NULL, 1.0, &out), BREAK_SNAPSHOT_INTERP_INVALID);
    ASSERT_EQ(break_snapshot_interp_count(NULL), 0u);
}

/* Random arrival order and drops: every sample between two kept snapshots
 * within the gap limit equals the linear blend computed directly, and every
 * rotation stays a unit quaternion. */
TEST(random_arrival_matches_a_direct_blend) {
    enum { k_ticks = 200 };
    BreakSnapshotInterp si;
    BreakSnapshotPose truth[k_ticks];
    bool sent[k_ticks];
    u32 rng = 99u, checked = 0u;
    init(&si, 2.0f, 6.0f);
    for (u32 t = 0u; t < (u32)k_ticks; ++t) {
        rng = rng * 1103515245u + 12345u;
        truth[t] = yaw((f32)((rng >> 8) % 360u));
        truth[t].position[0] = (f32)((rng >> 4) % 100u);
        sent[t] = false;
    }
    for (u32 now = 0u; now < (u32)k_ticks; ++now) {
        /* deliver tick now and, sometimes, a late one from up to 3 back */
        rng = rng * 1103515245u + 12345u;
        if ((rng >> 16) % 4u != 0u && !sent[now]) {
            (void)break_snapshot_interp_push(&si, now, &truth[now]);
            sent[now] = true;
        }
        if (now >= 3u) {
            u32 late = now - (rng >> 20) % 4u;
            if (!sent[late]) {
                (void)break_snapshot_interp_push(&si, late, &truth[late]);
                sent[late] = true;
            }
        }
        if (now >= 8u) {
            f64 rt = (f64)now - 6.0 + (f64)((rng >> 4) % 100u) / 100.0;
            BreakSnapshotPose out;
            BreakSnapshotInterpResult r = break_snapshot_interp_sample(&si, rt, &out);
            u32 lo = (u32)floor(rt), hi = lo + 1u;
            f32 n = 0.0f;
            while (lo > 0u && !sent[lo]) lo--;
            while (hi < now && !sent[hi]) hi++;
            for (int k = 0; k < 4; ++k) n += out.rotation[k] * out.rotation[k];
            ASSERT_FLOAT_EQ(n, 1.0f, 1e-4f);
            if (sent[lo] && sent[hi] && hi <= now && (f64)lo <= rt && rt <= (f64)hi &&
                hi - lo <= 6u && r == BREAK_SNAPSHOT_INTERP_INTERPOLATED) {
                f32 a = (f32)((rt - (f64)lo) / (f64)(hi - lo));
                f32 want = truth[lo].position[0] + (truth[hi].position[0] - truth[lo].position[0]) * a;
                ASSERT_FLOAT_EQ(out.position[0], want, 1e-3f);
                checked++;
            }
            break_snapshot_interp_discard_before(&si, rt - 2.0);
        }
    }
    ASSERT_TRUE(checked > 100u);
}

TEST_MAIN_BEGIN()
    RUN_TEST(positions_blend_linearly_between_the_two_surrounding_snapshots);
    RUN_TEST(rotation_slerps_along_the_shorter_arc);
    RUN_TEST(incoming_quaternions_are_normalized_and_zero_ones_refused);
    RUN_TEST(out_of_order_and_duplicate_snapshots_are_sorted_or_ignored);
    RUN_TEST(past_the_newest_snapshot_motion_is_extrapolated_then_held);
    RUN_TEST(extrapolation_does_not_continue_across_a_teleport);
    RUN_TEST(a_gap_wider_than_the_limit_is_not_blended);
    RUN_TEST(before_the_oldest_snapshot_the_oldest_is_held);
    RUN_TEST(a_full_buffer_drops_the_oldest_and_refuses_older);
    RUN_TEST(discarding_keeps_the_snapshot_still_needed_for_blending);
    RUN_TEST(config_and_sample_arguments_are_validated);
    RUN_TEST(random_arrival_matches_a_direct_blend);
TEST_MAIN_END()
