#include "test_framework.h"
#include <animation/animation.h>
#include <math.h>

TEST(loco_blends_walk_and_run) {
    AnimLoco1D loco;
    memset(&loco, 0x5a, sizeof(loco));
    AnimLocoSample bad[2] = {{2.0f, 0}, {1.0f, 1}};
    ASSERT_FALSE(anim_loco1d_init(&loco, 0, bad, 2));
    unsigned char *bytes = (unsigned char *)&loco;
    for (u32 i = 0; i < sizeof(loco); i++) {
        ASSERT_EQ(bytes[i], 0x5au);
    }
    AnimLocoSample samples[2] = {{0.0f, 1}, {4.0f, 2}};
    ASSERT_TRUE(anim_loco1d_init(&loco, 0, samples, 2));
    AnimBlendState state;
    anim_blend_state_init(&state, 4);
    anim_loco1d_apply(&loco, &state, 2.0f);
    ASSERT_FLOAT_EQ(state.layers[0].weight, 0.5f, 1e-4);
    ASSERT_FLOAT_EQ(state.layers[1].weight, 0.5f, 1e-4);
    anim_loco1d_apply(&loco, &state, 4.0f);
    ASSERT_EQ(state.layers[0].clip_index, 2u);
    ASSERT_FLOAT_EQ(state.layers[0].weight, 1.0f, 1e-4);
    ASSERT_EQ(state.layers[1].clip_index, 1u);
    ASSERT_FLOAT_EQ(state.layers[1].weight, 0.0f, 1e-4);
    anim_blend_state_destroy(&state);
}

static void init_three(AnimLoco1D *loco, u32 layer) {
    AnimLocoSample samples[3] = {{0.0f, 10}, {2.0f, 20}, {6.0f, 30}};
    ASSERT_TRUE(anim_loco1d_init(loco, layer, samples, 3));
}

/* With three samples the pair that brackets the speed is used: 4.0 lies
 * halfway between 2.0 and 6.0, so clips 20 and 30 share the weight. */
TEST(loco_picks_the_bracketing_pair_of_three_samples) {
    AnimLoco1D loco;
    init_three(&loco, 0);
    AnimBlendState state;
    anim_blend_state_init(&state, 4);
    anim_loco1d_apply(&loco, &state, 4.0f);
    ASSERT_EQ(state.layers[0].clip_index, 20u);
    ASSERT_EQ(state.layers[1].clip_index, 30u);
    ASSERT_FLOAT_EQ(state.layers[0].weight, 0.5f, 1e-5);
    ASSERT_FLOAT_EQ(state.layers[1].weight, 0.5f, 1e-5);
    anim_loco1d_apply(&loco, &state, 5.0f);
    ASSERT_EQ(state.layers[0].clip_index, 30u);
    ASSERT_FLOAT_EQ(state.layers[0].weight, 0.75f, 1e-5);
    ASSERT_EQ(state.layers[1].clip_index, 20u);
    ASSERT_FLOAT_EQ(state.layers[1].weight, 0.25f, 1e-5);
    ASSERT_TRUE(state.layers[0].active && state.layers[1].active);
    anim_blend_state_destroy(&state);
}

/* Below the first sample the first clip has all the weight; the second
 * layer is inactive. */
TEST(loco_clamps_below_the_slowest_sample) {
    AnimLoco1D loco;
    init_three(&loco, 0);
    AnimBlendState state;
    anim_blend_state_init(&state, 4);
    anim_loco1d_apply(&loco, &state, -3.0f);
    ASSERT_EQ(state.layers[0].clip_index, 10u);
    ASSERT_FLOAT_EQ(state.layers[0].weight, 1.0f, 1e-6);
    ASSERT_TRUE(state.layers[0].active);
    ASSERT_FALSE(state.layers[1].active);
    anim_loco1d_apply(&loco, &state, 100.0f);
    ASSERT_EQ(state.layers[0].clip_index, 30u);
    ASSERT_FLOAT_EQ(state.layers[0].weight, 1.0f, 1e-6);
    anim_blend_state_destroy(&state);
}

/* The blend writes its layer pair only, at the configured layer. */
TEST(loco_writes_only_its_layer_pair) {
    AnimLoco1D loco;
    init_three(&loco, 2);
    AnimBlendState state;
    anim_blend_state_init(&state, 4);
    state.layers[0].clip_index = 99u;
    state.layers[0].weight = 0.3f;
    state.layers[4].clip_index = 77u;
    anim_loco1d_apply(&loco, &state, 1.0f);
    ASSERT_EQ(state.layers[2].clip_index, 10u);
    ASSERT_EQ(state.layers[3].clip_index, 20u);
    ASSERT_EQ(state.layers[0].clip_index, 99u);
    ASSERT_FLOAT_EQ(state.layers[0].weight, 0.3f, 1e-6);
    ASSERT_EQ(state.layers[4].clip_index, 77u);
    anim_blend_state_destroy(&state);
}

/* Non-finite speeds leave the state untouched; bad configurations are
 * refused without writing the output. */
TEST(loco_rejects_bad_speeds_and_configurations) {
    AnimLoco1D loco;
    init_three(&loco, 0);
    AnimBlendState state;
    anim_blend_state_init(&state, 4);
    anim_loco1d_apply(&loco, &state, 4.0f);
    AnimationLayer saved[2] = {state.layers[0], state.layers[1]};
    anim_loco1d_apply(&loco, &state, NAN);
    anim_loco1d_apply(&loco, &state, INFINITY);
    ASSERT_EQ(memcmp(saved, state.layers, sizeof(saved)), 0);
    anim_blend_state_destroy(&state);

    AnimLoco1D other;
    memset(&other, 0x33, sizeof(other));
    AnimLocoSample one[1] = {{0.0f, 1}};
    AnimLocoSample equal[2] = {{1.0f, 1}, {1.0f, 2}};
    AnimLocoSample nan[2] = {{0.0f, 1}, {NAN, 2}};
    AnimLocoSample five[5] = {{0, 1}, {1, 2}, {2, 3}, {3, 4}, {4, 5}};
    AnimLocoSample ok[2] = {{0.0f, 1}, {1.0f, 2}};
    ASSERT_FALSE(anim_loco1d_init(&other, 0, one, 1));
    ASSERT_FALSE(anim_loco1d_init(&other, 0, equal, 2));
    ASSERT_FALSE(anim_loco1d_init(&other, 0, nan, 2));
    ASSERT_FALSE(anim_loco1d_init(&other, 0, five, 5));
    ASSERT_FALSE(anim_loco1d_init(&other, ANIM_MAX_LAYERS - 1u, ok, 2));
    ASSERT_FALSE(anim_loco1d_init(&other, 0, NULL, 2));
    unsigned char *bytes = (unsigned char *)&other;
    for (u32 i = 0; i < sizeof(other); i++) ASSERT_EQ(bytes[i], 0x33u);
    ASSERT_TRUE(anim_loco1d_init(&other, ANIM_MAX_LAYERS - 2u, ok, 2));
}

TEST_MAIN_BEGIN()
    RUN_TEST(loco_blends_walk_and_run);
    RUN_TEST(loco_picks_the_bracketing_pair_of_three_samples);
    RUN_TEST(loco_clamps_below_the_slowest_sample);
    RUN_TEST(loco_writes_only_its_layer_pair);
    RUN_TEST(loco_rejects_bad_speeds_and_configurations);
TEST_MAIN_END()
