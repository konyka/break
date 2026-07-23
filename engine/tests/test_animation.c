/* ==========================================================================
 *  test_animation.c — Unit tests for animation blend state + IK + clip.
 * ========================================================================== */

#include "test_framework.h"
#include <animation/animation.h>
#include <animation/skeleton.h>
#include <math.h>

/* RHI stubs for skeleton.c linkage */
RHIBuffer rhi_buffer_create(RHIDevice *dev, const RHIBufferDesc *desc) {
    (void)dev; (void)desc;
    RHIBuffer b = {.index = 1, .generation = 1};
    return b;
}
void rhi_buffer_destroy(RHIDevice *dev, RHIBuffer buf) { (void)dev; (void)buf; }
void rhi_buffer_update(RHIDevice *dev, RHIBuffer buf, const void *data, usize size) {
    (void)dev; (void)buf; (void)data; (void)size;
}
u32 rhi_frame_index(RHIDevice *dev) { (void)dev; return 0u; }

/* ---- Helpers to build simple AnimClips ---- */

/* AnimClip is ~328KB, must be static to avoid stack overflow */
static AnimClip g_clips[3];

static void init_translation_clip(AnimClip *clip, u32 joint, f32 dur,
                                 f32 x0, f32 y0, f32 z0,
                                 f32 x1, f32 y1, f32 z1)
{
    anim_clip_init(clip, dur, false);
    f32 times[2] = {0.0f, dur};
    f32 values[2][4] = {{x0, y0, z0, 0.0f}, {x1, y1, z1, 0.0f}};
    anim_clip_add_channel(clip, joint, ANIM_PATH_TRANSLATION, 2,
                          times, (const f32 *)values);
}

/* ----------------------------------------------------------------------- */
/*  Blend state lifecycle                                                    */
/* ----------------------------------------------------------------------- */

TEST(blend_state_init)
{
    AnimBlendState st;
    anim_blend_state_init(&st, 10);
    ASSERT_EQ(st.bone_count, 10u);
    ASSERT_EQ(st.layer_count, 0u);
    /* Bind pose: identity rotations */
    ASSERT_TRUE(fabsf(st.local_rotations[0].e[3] - 1.0f) < 0.001f);
    /* Bind pose: zero translations */
    ASSERT_TRUE(fabsf(st.local_positions[0].e[0]) < 0.001f);
    anim_blend_state_destroy(&st);
}

/* ----------------------------------------------------------------------- */
/*  Layer operations                                                         */
/* ----------------------------------------------------------------------- */

TEST(layer_play_sets_active)
{
    AnimBlendState st;
    anim_blend_state_init(&st, 4);
    anim_layer_play(&st, 0, 0, 1.0f, true);
    ASSERT_TRUE(st.layers[0].active);
    ASSERT_TRUE(fabsf(st.layers[0].speed - 1.0f) < 0.001f);
    ASSERT_TRUE(st.layers[0].looping);
    ASSERT_EQ(st.layer_count, 1u);
    anim_blend_state_destroy(&st);
}

TEST(layer_weight_clamped)
{
    AnimBlendState st;
    anim_blend_state_init(&st, 4);
    anim_layer_set_weight(&st, 0, 1.5f);
    ASSERT_TRUE(fabsf(st.layers[0].weight - 1.0f) < 0.001f);
    anim_layer_set_weight(&st, 0, -0.5f);
    ASSERT_TRUE(fabsf(st.layers[0].weight) < 0.001f);
    anim_blend_state_destroy(&st);
}

TEST(layer_stop)
{
    AnimBlendState st;
    anim_blend_state_init(&st, 4);
    anim_layer_play(&st, 0, 0, 1.0f, true);
    ASSERT_TRUE(st.layers[0].active);
    anim_layer_stop(&st, 0);
    ASSERT_TRUE(!st.layers[0].active);
    ASSERT_TRUE(fabsf(st.layers[0].weight) < 0.001f);
    anim_blend_state_destroy(&st);
}

TEST(bone_mask_filters)
{
    AnimBlendState st;
    anim_blend_state_init(&st, 4);
    /* Mask: only bone 0 */
    anim_layer_set_bone_mask(&st, 0, 1ULL << 0);
    ASSERT_EQ(st.layers[0].bone_mask, 1ULL);
    /* Mask 0 = no filtering */
    anim_layer_set_bone_mask(&st, 0, 0);
    ASSERT_EQ(st.layers[0].bone_mask, 0ULL);
    anim_blend_state_destroy(&st);
}

/* ----------------------------------------------------------------------- */
/*  Blend evaluation with translation clip                                 */
/* ----------------------------------------------------------------------- */

TEST(blend_evaluate_translation)
{
    AnimBlendState st;
    anim_blend_state_init(&st, 4);

    init_translation_clip(&g_clips[0], 0, 1.0f, 0, 0, 0, 10, 0, 0);

    anim_layer_play(&st, 0, 0, 1.0f, false);
    /* Evaluate at t=0 → position should be near (0,0,0) */
    anim_blend_evaluate(&st, 0.0f, g_clips, 1);
    ASSERT_TRUE(fabsf(st.local_positions[0].e[0]) < 0.1f);

    /* Evaluate at dt=0.5 → position should be near (5,0,0) */
    anim_blend_evaluate(&st, 0.5f, g_clips, 1);
    ASSERT_TRUE(fabsf(st.local_positions[0].e[0] - 5.0f) < 0.5f);

    /* Evaluate at dt=0.5 more → position near (10,0,0) */
    anim_blend_evaluate(&st, 0.5f, g_clips, 1);
    ASSERT_TRUE(fabsf(st.local_positions[0].e[0] - 10.0f) < 0.5f);

    anim_blend_state_destroy(&st);
}

TEST(blend_evaluate_two_layers)
{
    AnimBlendState st;
    anim_blend_state_init(&st, 4);

    init_translation_clip(&g_clips[0], 0, 1.0f, 0, 0, 0, 10, 0, 0);
    init_translation_clip(&g_clips[1], 1, 1.0f, 0, 0, 0, 0, 20, 0);

    anim_layer_play(&st, 0, 0, 1.0f, false);
    anim_layer_set_bone_mask(&st, 0, 1ULL << 0);  /* only bone 0 */
    anim_layer_play(&st, 1, 1, 1.0f, false);
    anim_layer_set_bone_mask(&st, 1, 1ULL << 1);  /* only bone 1 */
    anim_blend_evaluate(&st, 0.5f, g_clips, 2);
    /* Bone 0.x should be > 0 (animated by layer 0) */
    ASSERT_TRUE(st.local_positions[0].e[0] > 0.5f);
    /* Bone 1.y should be > 0 (animated by layer 1) */
    ASSERT_TRUE(st.local_positions[1].e[1] > 0.5f);

    anim_blend_state_destroy(&st);
}

TEST(additive_layer_leaves_unaddressed_bones_untouched)
{
    /* R305: an additive layer must only affect the bones its clip animates.
     * Bones the additive clip does NOT address must keep the value produced by
     * the layers below it. The old code seeded the scratch buffer from the
     * running output for additive layers too, so an unaddressed bone had
     *   pos += pos*w  (=> doubled at w=1), rot *= frac(rot), scale rescaled,
     * corrupting every bone outside the additive clip's channels. */
    AnimBlendState st;
    anim_blend_state_init(&st, 4);

    /* Base (OVERRIDE) layer places bone 1 at x=6 and leaves bone 0 at bind. */
    init_translation_clip(&g_clips[0], 1, 1.0f, 6, 0, 0, 6, 0, 0);
    /* Additive layer animates ONLY bone 0 (delta +2 on x); never touches bone 1. */
    init_translation_clip(&g_clips[1], 0, 1.0f, 2, 0, 0, 2, 0, 0);

    anim_layer_play(&st, 0, 0, 1.0f, false);
    anim_layer_play(&st, 1, 1, 1.0f, false);
    anim_layer_set_mode(&st, 1, ANIM_BLEND_ADDITIVE);
    anim_layer_set_weight(&st, 1, 1.0f);

    anim_blend_evaluate(&st, 0.0f, g_clips, 2);

    /* Bone 0: additive delta applied on top of bind (0) → x ≈ 2. */
    ASSERT_TRUE(fabsf(st.local_positions[0].e[0] - 2.0f) < 0.01f);
    /* Bone 1: NOT animated by the additive clip → must stay at the base x=6.
     * Pre-fix it became 6 + 6*1 = 12 (its own transform added back onto itself). */
    ASSERT_TRUE(fabsf(st.local_positions[1].e[0] - 6.0f) < 0.01f);

    anim_blend_state_destroy(&st);
}

TEST(additive_crossfade_leaves_unaddressed_bones_untouched)
{
    /* R350: crossfade TO-clip seed must use bind pose for ADDITIVE layers
     * (same contract as the main sample path / R305). Seeding from local_*
     * made unaddressed bones lerp toward the running pose then add that delta. */
    AnimBlendState st;
    anim_blend_state_init(&st, 4);

    init_translation_clip(&g_clips[0], 1, 1.0f, 6, 0, 0, 6, 0, 0); /* base bone1 */
    init_translation_clip(&g_clips[1], 0, 1.0f, 2, 0, 0, 2, 0, 0); /* add from bone0 */
    init_translation_clip(&g_clips[2], 0, 1.0f, 4, 0, 0, 4, 0, 0); /* add to bone0 */

    anim_layer_play(&st, 0, 0, 1.0f, false);
    anim_layer_play(&st, 1, 1, 1.0f, false);
    anim_layer_set_mode(&st, 1, ANIM_BLEND_ADDITIVE);
    anim_layer_set_weight(&st, 1, 1.0f);
    anim_crossfade(&st, 1, 2, 1.0f);

    anim_blend_evaluate(&st, 0.5f, g_clips, 3);
    ASSERT_TRUE(st.crossfade.active);
    /* Bone 1 must remain the base OVERRIDE value; pre-fix drifted toward ~9. */
    ASSERT_TRUE(fabsf(st.local_positions[1].e[0] - 6.0f) < 0.01f);

    anim_blend_state_destroy(&st);
}

/* ----------------------------------------------------------------------- */
/*  Crossfade                                                                */
/* ----------------------------------------------------------------------- */

TEST(crossfade_instant)
{
    AnimBlendState st;
    anim_blend_state_init(&st, 4);

    anim_layer_play(&st, 0, 0, 1.0f, false);
    /* Instant crossfade (duration=0) */
    anim_crossfade(&st, 0, 1, 0.0f);
    ASSERT_EQ(st.layers[0].clip_index, 1u);
    ASSERT_TRUE(!st.crossfade.active);
    anim_blend_state_destroy(&st);
}

TEST(crossfade_gradual)
{
    AnimBlendState st;
    anim_blend_state_init(&st, 4);
    init_translation_clip(&g_clips[0], 0, 1.0f, 0, 0, 0, 10, 0, 0);
    init_translation_clip(&g_clips[1], 0, 1.0f, 0, 0, 0, 20, 0, 0);

    anim_layer_play(&st, 0, 0, 1.0f, false);
    anim_crossfade(&st, 0, 1, 1.0f);
    ASSERT_TRUE(st.crossfade.active);

    /* Evaluate halfway through crossfade */
    anim_blend_evaluate(&st, 0.5f, g_clips, 2);
    /* R269: at t=0.5, fade_t=0.5, from-clip x=10*0.5=5, to-clip x=20*0.5=10,
     * so the blended x must be lerp(5,10,0.5)=7.5 — the to-clip MUST contribute.
     * The pre-fix code never sampled the to-clip and produced x=5 (from only),
     * which still passed the old loose 1<x<19 bound. */
    f32 x = st.local_positions[0].e[0];
    ASSERT_TRUE(x > 1.0f && x < 19.0f);
    ASSERT_FLOAT_EQ(x, 7.5f, 0.01f);

    /* Complete the crossfade */
    anim_blend_evaluate(&st, 0.6f, g_clips, 2);
    ASSERT_TRUE(!st.crossfade.active);
    ASSERT_EQ(st.layers[0].clip_index, 1u);

    anim_blend_state_destroy(&st);
}

TEST(crossfade_gradual_nonloop_restarts_at_origin)
{
    /* R351: after a gradual crossfade completes on a non-looping layer, time
     * must reset to 0 (like instant crossfade). Leaving the from-clip clock
     * made the next evaluate clamp to to_duration and snap to the end pose. */
    AnimBlendState st;
    anim_blend_state_init(&st, 4);
    init_translation_clip(&g_clips[0], 0, 1.0f, 0, 0, 0, 10, 0, 0);
    init_translation_clip(&g_clips[1], 0, 1.0f, 0, 0, 0, 20, 0, 0);

    anim_layer_play(&st, 0, 0, 1.0f, false);
    anim_crossfade(&st, 0, 1, 1.0f);
    anim_blend_evaluate(&st, 0.5f, g_clips, 2);
    anim_blend_evaluate(&st, 0.6f, g_clips, 2);
    ASSERT_TRUE(!st.crossfade.active);
    ASSERT_EQ(st.layers[0].clip_index, 1u);
    ASSERT_FLOAT_EQ(st.layers[0].time, 0.0f, 1e-5f);

    /* Sample at the restarted origin — to-clip key0 is x=0, not end x=20. */
    anim_blend_evaluate(&st, 0.0f, g_clips, 2);
    ASSERT_FLOAT_EQ(st.local_positions[0].e[0], 0.0f, 0.01f);

    anim_blend_state_destroy(&st);
}

TEST(play_cancels_active_crossfade)
{
    /* R351: play/stop must clear crossfade or fade_done overwrites clip_index. */
    AnimBlendState st;
    anim_blend_state_init(&st, 4);
    init_translation_clip(&g_clips[0], 0, 1.0f, 0, 0, 0, 10, 0, 0);
    init_translation_clip(&g_clips[1], 0, 1.0f, 0, 0, 0, 20, 0, 0);

    anim_layer_play(&st, 0, 0, 1.0f, true);
    anim_crossfade(&st, 0, 1, 1.0f);
    ASSERT_TRUE(st.crossfade.active);
    anim_layer_play(&st, 0, 0, 1.0f, true);
    ASSERT_TRUE(!st.crossfade.active);
    ASSERT_EQ(st.layers[0].clip_index, 0u);

    anim_crossfade(&st, 0, 1, 1.0f);
    ASSERT_TRUE(st.crossfade.active);
    anim_layer_stop(&st, 0);
    ASSERT_TRUE(!st.crossfade.active);

    anim_blend_state_destroy(&st);
}

/* ----------------------------------------------------------------------- */
/*  AnimClip                                                                 */
/* ----------------------------------------------------------------------- */

TEST(anim_clip_init_basic)
{
    AnimClip clip;
    anim_clip_init(&clip, 2.5f, true);
    ASSERT_TRUE(fabsf(clip.duration - 2.5f) < 0.001f);
    ASSERT_TRUE(clip.loop);
    ASSERT_TRUE(clip.playing);
    ASSERT_EQ(clip.channel_count, 0u);
}

TEST(blend_evaluate_step_holds_keyframe)
{
    /* R251: a STEP sampler must hold keyframe k0 across the segment, not lerp.
     * A LINEAR clip 0->10 over 1s reads 5 at t=0.5; STEP must read 0, then jump
     * to 10 only once time reaches the final keyframe. */
    AnimBlendState st;
    anim_blend_state_init(&st, 4);

    init_translation_clip(&g_clips[0], 0, 1.0f, 0, 0, 0, 10, 0, 0);
    g_clips[0].channels[0].interp = ANIM_INTERP_STEP;

    anim_layer_play(&st, 0, 0, 1.0f, false);

    /* t=0.5: held at keyframe 0 (0.0), NOT the linear midpoint (5.0). */
    anim_blend_evaluate(&st, 0.5f, g_clips, 1);
    ASSERT_TRUE(fabsf(st.local_positions[0].e[0]) < 0.001f);

    /* Advance to the end (time -> 1.0, clamped): STEP now yields the last key. */
    anim_blend_evaluate(&st, 0.5f, g_clips, 1);
    ASSERT_TRUE(fabsf(st.local_positions[0].e[0] - 10.0f) < 0.001f);

    anim_blend_state_destroy(&st);
}

TEST(skeleton_evaluate_step_holds_keyframe)
{
    /* R252: skeleton_evaluate (legacy skinning path, used when BREAK_ANIM_BLEND is
     * unset) must honor STEP like clip_sample. LINEAR 0->10 over 1s reads 5 at
     * t=0.5; STEP must hold 0, then reach 10 only at the final keyframe. */
    Skeleton sk;
    skeleton_init(&sk, NULL);
    u32 parents[1] = { UINT32_MAX };          /* single root joint */
    Mat4 inv_bind[1] = { mat4_identity() };
    skeleton_set_joints(&sk, 1, parents, inv_bind);

    init_translation_clip(&g_clips[0], 0, 1.0f, 0, 0, 0, 10, 0, 0);
    g_clips[0].channels[0].interp = ANIM_INTERP_STEP;

    /* Single joint + identity inverse-bind: current_pose[0] == local TRS;
     * translation is the column-major e[3][*] row. */
    g_clips[0].time = 0.5f;
    skeleton_evaluate(&sk, &g_clips[0], 0.0f);
    ASSERT_TRUE(fabsf(sk.current_pose[0].e[3][0]) < 0.001f);   /* held at key 0 */

    g_clips[0].time = 1.0f;
    skeleton_evaluate(&sk, &g_clips[0], 0.0f);
    ASSERT_TRUE(fabsf(sk.current_pose[0].e[3][0] - 10.0f) < 0.001f); /* final key */

    skeleton_shutdown(&sk);
}

TEST(anim_clip_add_channel)
{
    AnimClip clip;
    anim_clip_init(&clip, 1.0f, false);
    f32 times[3] = {0.0f, 0.5f, 1.0f};
    f32 values[3][4] = {{1,0,0,0}, {2,0,0,0}, {3,0,0,0}};
    anim_clip_add_channel(&clip, 0, ANIM_PATH_TRANSLATION, 3,
                          times, (const f32 *)values);
    ASSERT_EQ(clip.channel_count, 1u);
    ASSERT_EQ(clip.channels[0].keyframe_count, 3u);
    ASSERT_EQ(clip.channels[0].joint_index, 0u);
}

/* ----------------------------------------------------------------------- */
/*  IK system                                                                */
/* ----------------------------------------------------------------------- */

TEST(ik_init)
{
    IKSystem ik;
    anim_ik_init(&ik);
    ASSERT_EQ(ik.target_count, 0u);
}

TEST(ik_set_target)
{
    IKSystem ik;
    anim_ik_init(&ik);
    Vec3 target = {{5, 0, 0}};
    Vec3 pole   = {{0, 1, 0}};
    anim_ik_set_target(&ik, 0, 0, 1, 2, target, pole);
    ASSERT_TRUE(ik.targets[0].active);
    ASSERT_EQ(ik.target_count, 1u);
    ASSERT_EQ(ik.targets[0].chain_root, 0u);
    ASSERT_EQ(ik.targets[0].chain_mid, 1u);
    ASSERT_EQ(ik.targets[0].chain_tip, 2u);
}

TEST(ik_weight_clamped)
{
    IKSystem ik;
    anim_ik_init(&ik);
    Vec3 t = {{0,0,0}}, p = {{0,1,0}};
    anim_ik_set_target(&ik, 0, 0, 1, 2, t, p);
    anim_ik_set_weight(&ik, 0, 2.0f);
    ASSERT_TRUE(fabsf(ik.targets[0].weight - 1.0f) < 0.001f);
    anim_ik_set_weight(&ik, 0, -1.0f);
    ASSERT_TRUE(fabsf(ik.targets[0].weight) < 0.001f);
}

TEST(ik_two_bone_solver)
{
    /* Simple 2-bone chain: root(0,0,0) -> mid(0,1,0) -> tip(0,2,0)
     * Target: (1, 1, 0) — should produce non-identity rotations */
    Vec3 root_pos = {{0, 0, 0}};
    Vec3 mid_pos  = {{0, 1, 0}};
    Vec3 tip_pos  = {{0, 2, 0}};
    Vec3 target   = {{1, 1, 0}};
    Vec3 pole     = {{0, 0, 1}};

    Quat root_rot, mid_rot;
    anim_ik_two_bone(root_pos, mid_pos, tip_pos, target, pole,
                     &root_rot, &mid_rot);

    /* Rotations should be non-identity (some rotation applied) */
    f32 root_angle = fabsf(root_rot.e[0]) + fabsf(root_rot.e[1]) +
                     fabsf(root_rot.e[2]);
    f32 mid_angle  = fabsf(mid_rot.e[0]) + fabsf(mid_rot.e[1]) +
                     fabsf(mid_rot.e[2]);
    ASSERT_TRUE(root_angle > 0.01f || mid_angle > 0.01f);
}

TEST(ik_two_bone_zero_length)
{
    /* Degenerate case: zero-length bones → identity */
    Vec3 pos = {{0, 0, 0}};
    Vec3 target = {{1, 0, 0}};
    Vec3 pole   = {{0, 1, 0}};
    Quat r0, r1;
    anim_ik_two_bone(pos, pos, pos, target, pole, &r0, &r1);
    ASSERT_TRUE(fabsf(r0.e[3] - 1.0f) < 0.01f);
    ASSERT_TRUE(fabsf(r1.e[3] - 1.0f) < 0.01f);
}

/* ----------------------------------------------------------------------- */
/*  Edge Cases                                                              */
/* ----------------------------------------------------------------------- */

TEST(blend_evaluate_zero_layers)
{
    AnimBlendState st;
    anim_blend_state_init(&st, 4);
    /* Evaluate with no layers - should not crash and return bind pose */
    anim_blend_evaluate(&st, 1.0f, g_clips, 0);
    /* Bind pose: identity rotations */
    ASSERT_TRUE(fabsf(st.local_rotations[0].e[3] - 1.0f) < 0.001f);
    anim_blend_state_destroy(&st);
}

TEST(layer_zero_weight_no_effect)
{
    AnimBlendState st;
    anim_blend_state_init(&st, 4);

    init_translation_clip(&g_clips[0], 0, 1.0f, 0, 0, 0, 10, 0, 0);

    anim_layer_play(&st, 0, 0, 1.0f, false);
    anim_layer_set_weight(&st, 0, 0.0f);

    anim_blend_evaluate(&st, 0.5f, g_clips, 1);
    /* With zero weight, should stay at bind pose (zero translation) */
    ASSERT_TRUE(fabsf(st.local_positions[0].e[0]) < 0.1f);

    anim_blend_state_destroy(&st);
}

TEST(ik_collinear_bones)
{
    /* Collinear bones: root(0,0,0) -> mid(1,0,0) -> tip(2,0,0)
     * Target on the same line */
    Vec3 root_pos = {{0, 0, 0}};
    Vec3 mid_pos  = {{1, 0, 0}};
    Vec3 tip_pos  = {{2, 0, 0}};
    Vec3 target   = {{3, 0, 0}};
    Vec3 pole     = {{0, 1, 0}};

    Quat root_rot, mid_rot;
    anim_ik_two_bone(root_pos, mid_pos, tip_pos, target, pole,
                     &root_rot, &mid_rot);
    /* Should not crash - result is implementation-defined */
    ASSERT_TRUE(fabsf(root_rot.e[3]) > 0.5f || fabsf(root_rot.e[3]) < 0.5f);
}

TEST(crossfade_zero_duration)
{
    AnimBlendState st;
    anim_blend_state_init(&st, 4);
    init_translation_clip(&g_clips[0], 0, 1.0f, 0, 0, 0, 10, 0, 0);
    init_translation_clip(&g_clips[1], 0, 1.0f, 0, 0, 0, 20, 0, 0);

    anim_layer_play(&st, 0, 0, 1.0f, false);
    /* Zero duration crossfade should complete immediately */
    anim_crossfade(&st, 0, 1, 0.0f);
    ASSERT_TRUE(!st.crossfade.active);
    ASSERT_EQ(st.layers[0].clip_index, 1u);

    anim_blend_state_destroy(&st);
}

/* ----------------------------------------------------------------------- */
/*  Animation events (R101)                                                 */
/* ----------------------------------------------------------------------- */

static int g_evt_count;
static char g_evt_name[32];
static float g_evt_time;

static void test_event_cb(const char *name, f32 time, void *user_data) {
    (void)user_data;
    g_evt_count++;
    /* Copy name safely */
    usize i = 0;
    for (; i < 31 && name[i] != '\0'; i++) g_evt_name[i] = name[i];
    g_evt_name[i] = '\0';
    g_evt_time = time;
}

TEST(event_fires_when_crossed)
{
    AnimBlendState st;
    anim_blend_state_init(&st, 4);
    init_translation_clip(&g_clips[0], 0, 2.0f, 0, 0, 0, 10, 0, 0);
    anim_clip_add_event(&g_clips[0], 0.5f, "footstep");

    g_evt_count = 0;
    anim_set_event_callback(&st, test_event_cb, NULL);
    anim_layer_play(&st, 0, 0, 1.0f, false);

    /* dt=0.3: time 0 -> 0.3, event at 0.5 not crossed */
    anim_blend_evaluate(&st, 0.3f, g_clips, 1);
    ASSERT_EQ(g_evt_count, 0);

    /* dt=0.3: time 0.3 -> 0.6, event at 0.5 crossed */
    anim_blend_evaluate(&st, 0.3f, g_clips, 1);
    ASSERT_EQ(g_evt_count, 1);
    ASSERT_STR_EQ(g_evt_name, "footstep");
    ASSERT_FLOAT_EQ(g_evt_time, 0.5f, 0.001f);

    /* dt=0.3: time 0.6 -> 0.9, no new event */
    anim_blend_evaluate(&st, 0.3f, g_clips, 1);
    ASSERT_EQ(g_evt_count, 1);

    anim_blend_state_destroy(&st);
}

TEST(event_at_duration_nonlooping_fires)
{
    /* R246: a non-looping clip is clamped to its duration; an event at exactly
     * clip->duration must still fire (half-open [t0,t1) would drop it). */
    AnimBlendState st;
    anim_blend_state_init(&st, 4);
    init_translation_clip(&g_clips[0], 0, 2.0f, 0, 0, 0, 10, 0, 0);
    anim_clip_add_event(&g_clips[0], 2.0f, "clip_end");  /* et == duration */

    g_evt_count = 0;
    anim_set_event_callback(&st, test_event_cb, NULL);
    anim_layer_play(&st, 0, 0, 1.0f, false);  /* non-looping */

    /* Advance past the end: time 0 -> clamped to 2.0; end event must fire once. */
    anim_blend_evaluate(&st, 2.5f, g_clips, 1);
    ASSERT_EQ(g_evt_count, 1);
    ASSERT_STR_EQ(g_evt_name, "clip_end");
    ASSERT_FLOAT_EQ(g_evt_time, 2.0f, 0.001f);

    /* Further frames stay clamped — no duplicate firing. */
    anim_blend_evaluate(&st, 0.5f, g_clips, 1);
    ASSERT_EQ(g_evt_count, 1);

    anim_blend_state_destroy(&st);
}

TEST(event_looping_wrap)
{
    AnimBlendState st;
    anim_blend_state_init(&st, 4);
    init_translation_clip(&g_clips[0], 0, 1.0f, 0, 0, 0, 10, 0, 0);
    anim_clip_add_event(&g_clips[0], 0.5f, "hit");

    g_evt_count = 0;
    anim_set_event_callback(&st, test_event_cb, NULL);
    anim_layer_play(&st, 0, 0, 1.0f, true);  /* looping */

    /* dt=0.6: time 0 -> 0.6, event at 0.5 fires (1st) */
    anim_blend_evaluate(&st, 0.6f, g_clips, 1);
    ASSERT_EQ(g_evt_count, 1);

    /* dt=0.6: time 0.6 -> 0.2 (wrap), no event in [0.6,1.0) or [0,0.2) */
    anim_blend_evaluate(&st, 0.6f, g_clips, 1);
    ASSERT_EQ(g_evt_count, 1);

    /* dt=0.6: time 0.2 -> 0.8, event at 0.5 fires (2nd) */
    anim_blend_evaluate(&st, 0.6f, g_clips, 1);
    ASSERT_EQ(g_evt_count, 2);

    anim_blend_state_destroy(&st);
}

TEST(event_no_callback_safe)
{
    AnimBlendState st;
    anim_blend_state_init(&st, 4);
    init_translation_clip(&g_clips[0], 0, 1.0f, 0, 0, 0, 10, 0, 0);
    anim_clip_add_event(&g_clips[0], 0.5f, "test");

    /* No callback set — should not crash */
    anim_layer_play(&st, 0, 0, 1.0f, false);
    anim_blend_evaluate(&st, 1.0f, g_clips, 1);

    anim_blend_state_destroy(&st);
}

TEST(event_add_max_clamped)
{
    AnimBlendState st;
    anim_blend_state_init(&st, 4);
    anim_clip_init(&g_clips[0], 1.0f, false);

    /* Add SKELETON_MAX_EVENTS events */
    for (u32 i = 0; i < SKELETON_MAX_EVENTS; i++) {
        anim_clip_add_event(&g_clips[0], (f32)i * 0.01f, "evt");
    }
    ASSERT_EQ(g_clips[0].event_count, SKELETON_MAX_EVENTS);

    /* Adding one more should be silently ignored */
    anim_clip_add_event(&g_clips[0], 0.99f, "overflow");
    ASSERT_EQ(g_clips[0].event_count, SKELETON_MAX_EVENTS);

    anim_blend_state_destroy(&st);
}

TEST_MAIN_BEGIN()
    RUN_TEST(blend_state_init);
    RUN_TEST(layer_play_sets_active);
    RUN_TEST(layer_weight_clamped);
    RUN_TEST(layer_stop);
    RUN_TEST(bone_mask_filters);
    RUN_TEST(blend_evaluate_translation);
    RUN_TEST(blend_evaluate_two_layers);
    RUN_TEST(additive_layer_leaves_unaddressed_bones_untouched);
    RUN_TEST(additive_crossfade_leaves_unaddressed_bones_untouched);
    RUN_TEST(crossfade_instant);
    RUN_TEST(crossfade_gradual);
    RUN_TEST(crossfade_gradual_nonloop_restarts_at_origin);
    RUN_TEST(play_cancels_active_crossfade);
    RUN_TEST(anim_clip_init_basic);
    RUN_TEST(blend_evaluate_step_holds_keyframe);
    RUN_TEST(skeleton_evaluate_step_holds_keyframe);
    RUN_TEST(anim_clip_add_channel);
    RUN_TEST(ik_init);
    RUN_TEST(ik_set_target);
    RUN_TEST(ik_weight_clamped);
    RUN_TEST(ik_two_bone_solver);
    RUN_TEST(ik_two_bone_zero_length);
    /* Edge cases */
    RUN_TEST(blend_evaluate_zero_layers);
    RUN_TEST(layer_zero_weight_no_effect);
    RUN_TEST(ik_collinear_bones);
    RUN_TEST(crossfade_zero_duration);
    /* Animation events (R101) */
    RUN_TEST(event_fires_when_crossed);
    RUN_TEST(event_at_duration_nonlooping_fires);
    RUN_TEST(event_looping_wrap);
    RUN_TEST(event_no_callback_safe);
    RUN_TEST(event_add_max_clamped);
TEST_MAIN_END()
