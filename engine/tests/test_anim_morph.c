#include "test_framework.h"
#include <animation/morph.h>
#include <renderer/lod_skin.h>

typedef struct {
    f32 pos[3];
    f32 normal[3];
    f32 uv[2];
    u32 joints[4];
    f32 weights[4];
} TestSkinVertex;

_Static_assert(sizeof(TestSkinVertex) == ANIM_MORPH_SKIN_VERTEX_BYTES,
               "morph adapter must use the real skinned vertex layout");
_Static_assert(ANIM_MORPH_SKIN_VERTEX_BYTES == LOD_SKIN_VERTEX_STRIDE,
               "morph adapter and real skinner must share their byte stride");

TEST(morph_evaluates_bounded_weight_sum) {
    AnimMorphSet set;
    ASSERT_TRUE(anim_morph_init(&set, 1u));
    const Vec3 delta[1] = {{{2.0f, 4.0f, -2.0f}}};
    ASSERT_TRUE(anim_morph_add_target(&set, "smile", delta));
    const f32 base[3] = {1.0f, 2.0f, 3.0f};
    const f32 weights[1] = {0.25f};
    f32 out[3] = {0.0f, 0.0f, 0.0f};
    ASSERT_TRUE(anim_morph_evaluate(&set, base, weights, 1u, out));
    ASSERT_FLOAT_EQ(out[0], 1.5f, 1e-6f);
    ASSERT_FLOAT_EQ(out[1], 3.0f, 1e-6f);
    ASSERT_FLOAT_EQ(out[2], 2.5f, 1e-6f);
}

TEST(morph_empty_set_copies_base) {
    AnimMorphSet set;
    ASSERT_TRUE(anim_morph_init(&set, 2u));
    const f32 base[6] = {1.0f, 2.0f, 3.0f, -4.0f, 5.0f, -6.0f};
    f32 out[6] = {0.0f};
    ASSERT_TRUE(anim_morph_evaluate(&set, base, NULL, 0u, out));
    ASSERT_EQ(memcmp(base, out, sizeof(base)), 0);
}

TEST(morph_rejects_invalid_weights_without_touching_output) {
    AnimMorphSet set;
    ASSERT_TRUE(anim_morph_init(&set, 1u));
    const Vec3 delta[1] = {{{2.0f, 4.0f, -2.0f}}};
    ASSERT_TRUE(anim_morph_add_target(&set, "smile", delta));
    const f32 base[3] = {1.0f, 2.0f, 3.0f};
    const f32 invalid[4] = {NAN, INFINITY, -0.01f, 1.01f};
    for (u32 i = 0; i < 4u; ++i) {
        f32 out[3] = {7.0f, 7.0f, 7.0f};
        const f32 expected[3] = {7.0f, 7.0f, 7.0f};
        ASSERT_FALSE(anim_morph_evaluate(&set, base, &invalid[i], 1u, out));
        ASSERT_EQ(memcmp(out, expected, sizeof(out)), 0);
    }
}

TEST(morph_rejects_nonfinite_or_overflowing_results_atomically) {
    AnimMorphSet set;
    ASSERT_TRUE(anim_morph_init(&set, 1u));
    const Vec3 delta[1] = {{{3.402823466e38F, 0.0f, 0.0f}}};
    ASSERT_TRUE(anim_morph_add_target(&set, "large", delta));
    const f32 weight[1] = {1.0f};
    const f32 bad_base[2][3] = {
        {NAN, 0.0f, 0.0f},
        {3.402823466e38F, 0.0f, 0.0f}
    };
    for (u32 i = 0; i < 2u; ++i) {
        f32 out[3] = {7.0f, 7.0f, 7.0f};
        const f32 expected[3] = {7.0f, 7.0f, 7.0f};
        ASSERT_FALSE(anim_morph_evaluate(&set, bad_base[i], weight, 1u, out));
        ASSERT_EQ(memcmp(out, expected, sizeof(out)), 0);
    }
}

TEST(morph_init_enforces_vertex_capacity) {
    AnimMorphSet set;
    ASSERT_FALSE(anim_morph_init(NULL, 1u));
    ASSERT_FALSE(anim_morph_init(&set, 0u));
    ASSERT_FALSE(anim_morph_init(&set, ANIM_MORPH_MAX_VERTICES + 1u));
    ASSERT_TRUE(anim_morph_init(&set, ANIM_MORPH_MAX_VERTICES));
    ASSERT_EQ(set.vertex_count, ANIM_MORPH_MAX_VERTICES);
}

TEST(morph_target_names_are_nonempty_unique_and_bounded) {
    AnimMorphSet set;
    ASSERT_TRUE(anim_morph_init(&set, 1u));
    const Vec3 delta[1] = {{{0.0f, 0.0f, 0.0f}}};
    ASSERT_FALSE(anim_morph_add_target(&set, "", delta));
    ASSERT_FALSE(anim_morph_add_target(&set, "abcdefghijklmnopqrstuvwxyzabcdefg", delta));
    ASSERT_EQ(set.target_count, 0u);
    ASSERT_TRUE(anim_morph_add_target(&set, "smile", delta));
    ASSERT_FALSE(anim_morph_add_target(&set, "smile", delta));
    ASSERT_EQ(set.target_count, 1u);
}

TEST(morph_target_rejects_nonfinite_delta_atomically) {
    AnimMorphSet set;
    ASSERT_TRUE(anim_morph_init(&set, 2u));
    Vec3 delta[2] = {{{0.0f, 0.0f, 0.0f}}, {{1.0f, INFINITY, 0.0f}}};
    ASSERT_FALSE(anim_morph_add_target(&set, "bad", delta));
    ASSERT_EQ(set.target_count, 0u);
}

TEST(morph_target_capacity_is_hard_bounded) {
    AnimMorphSet set;
    ASSERT_TRUE(anim_morph_init(&set, 1u));
    const Vec3 delta[1] = {{{0.0f, 0.0f, 0.0f}}};
    char name[ANIM_MORPH_NAME_CAP];
    for (u32 i = 0; i < ANIM_MORPH_MAX_TARGETS; ++i) {
        snprintf(name, sizeof(name), "target_%u", i);
        ASSERT_TRUE(anim_morph_add_target(&set, name, delta));
    }
    ASSERT_FALSE(anim_morph_add_target(&set, "overflow", delta));
    ASSERT_EQ(set.target_count, ANIM_MORPH_MAX_TARGETS);
}

TEST(morphed_vertex_is_consumed_by_existing_skinner) {
    AnimMorphSet set;
    ASSERT_TRUE(anim_morph_init(&set, 1u));
    const Vec3 delta[1] = {{{0.0f, 2.0f, 0.0f}}};
    ASSERT_TRUE(anim_morph_add_target(&set, "lift", delta));
    const f32 weight[1] = {0.5f};
    TestSkinVertex base = {
        {1.0f, 0.0f, 0.0f}, {0.0f, 1.0f, 0.0f}, {0.25f, 0.75f},
        {0u, 0u, 0u, 0u}, {1.0f, 0.0f, 0.0f, 0.0f}
    };
    TestSkinVertex morphed;
    memset(&morphed, 0, sizeof(morphed));
    ASSERT_TRUE(anim_morph_evaluate_skinned(&set, &base, weight, 1u,
                                            &morphed, sizeof(morphed)));
    ASSERT_FLOAT_EQ(morphed.pos[0], 1.0f, 1e-6f);
    ASSERT_FLOAT_EQ(morphed.pos[1], 1.0f, 1e-6f);
    ASSERT_FLOAT_EQ(morphed.pos[2], 0.0f, 1e-6f);
    ASSERT_EQ(memcmp(morphed.normal, base.normal,
                     sizeof(base) - sizeof(base.pos)), 0);
    Mat4 skin = mat4_identity();
    skin.e[3][0] = 3.0f;
    f32 skinned_xyz[3] = {0.0f, 0.0f, 0.0f};
    ASSERT_TRUE(lod_skin_positions((const f32 *)&morphed, 1u, &skin, 1u, skinned_xyz));
    ASSERT_FLOAT_EQ(skinned_xyz[0], 4.0f, 1e-6f);
    ASSERT_FLOAT_EQ(skinned_xyz[1], 1.0f, 1e-6f);
    ASSERT_FLOAT_EQ(skinned_xyz[2], 0.0f, 1e-6f);
}

TEST_MAIN_BEGIN()
    RUN_TEST(morph_evaluates_bounded_weight_sum);
    RUN_TEST(morph_empty_set_copies_base);
    RUN_TEST(morph_rejects_invalid_weights_without_touching_output);
    RUN_TEST(morph_rejects_nonfinite_or_overflowing_results_atomically);
    RUN_TEST(morph_init_enforces_vertex_capacity);
    RUN_TEST(morph_target_names_are_nonempty_unique_and_bounded);
    RUN_TEST(morph_target_rejects_nonfinite_delta_atomically);
    RUN_TEST(morph_target_capacity_is_hard_bounded);
    RUN_TEST(morphed_vertex_is_consumed_by_existing_skinner);
TEST_MAIN_END()
