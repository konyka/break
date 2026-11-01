#include "test_framework.h"
#include <animation/animation.h>

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

TEST_MAIN_BEGIN()
    RUN_TEST(loco_blends_walk_and_run);
TEST_MAIN_END()
