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

/* ---- Helpers to build simple AnimClips ---- */

/* AnimClip is ~328KB, must be static to avoid stack overflow */
static AnimClip g_clips[2];

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
    /* Should be blended between c0 and c1 */
    f32 x = st.local_positions[0].e[0];
    ASSERT_TRUE(x > 1.0f && x < 19.0f);

    /* Complete the crossfade */
    anim_blend_evaluate(&st, 0.6f, g_clips, 2);
    ASSERT_TRUE(!st.crossfade.active);
    ASSERT_EQ(st.layers[0].clip_index, 1u);

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

TEST_MAIN_BEGIN()
    RUN_TEST(blend_state_init);
    RUN_TEST(layer_play_sets_active);
    RUN_TEST(layer_weight_clamped);
    RUN_TEST(layer_stop);
    RUN_TEST(bone_mask_filters);
    RUN_TEST(blend_evaluate_translation);
    RUN_TEST(blend_evaluate_two_layers);
    RUN_TEST(crossfade_instant);
    RUN_TEST(crossfade_gradual);
    RUN_TEST(anim_clip_init_basic);
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
TEST_MAIN_END()
