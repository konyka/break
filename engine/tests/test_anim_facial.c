#include "test_framework.h"
#include <animation/facial.h>

TEST(facial_named_expression_drives_named_morphs) {
    AnimMorphSet morphs;
    ASSERT_TRUE(anim_morph_init(&morphs, 1u));
    const Vec3 delta[1] = {{{1.0f, 0.0f, 0.0f}}};
    ASSERT_TRUE(anim_morph_add_target(&morphs, "smile_l", delta));
    ASSERT_TRUE(anim_morph_add_target(&morphs, "smile_r", delta));
    AnimFacialLibrary library;
    anim_facial_library_init(&library);
    ASSERT_TRUE(anim_facial_add_expression(&library, "smile"));
    const f32 times[2] = {0.0f, 1.0f};
    const f32 values[2] = {0.0f, 1.0f};
    ASSERT_TRUE(anim_facial_add_curve(&library, "smile", "left", "smile_l",
                                      2u, times, values));
    ASSERT_TRUE(anim_facial_add_curve(&library, "smile", "right", "smile_r",
                                      2u, times, values));
    f32 weights[2] = {-1.0f, -1.0f};
    ASSERT_TRUE(anim_facial_evaluate(&library, &morphs, "smile", 0.5f,
                                     weights, 2u));
    ASSERT_FLOAT_EQ(weights[0], 0.5f, 1e-6f);
    ASSERT_FLOAT_EQ(weights[1], 0.5f, 1e-6f);
}

TEST(facial_missing_target_and_nonfinite_time_are_atomic) {
    AnimMorphSet morphs;
    ASSERT_TRUE(anim_morph_init(&morphs, 1u));
    const Vec3 delta[1] = {{{0.0f, 0.0f, 0.0f}}};
    ASSERT_TRUE(anim_morph_add_target(&morphs, "known", delta));
    AnimFacialLibrary library;
    anim_facial_library_init(&library);
    ASSERT_TRUE(anim_facial_add_expression(&library, "expression"));
    const f32 times[1] = {0.0f};
    const f32 values[1] = {1.0f};
    ASSERT_TRUE(anim_facial_add_curve(&library, "expression", "bad", "missing",
                                      1u, times, values));
    f32 weights[1] = {7.0f};
    ASSERT_FALSE(anim_facial_evaluate(&library, &morphs, "expression", 0.0f,
                                      weights, 1u));
    ASSERT_FLOAT_EQ(weights[0], 7.0f, 0.0f);
    ASSERT_FALSE(anim_facial_evaluate(&library, &morphs, "expression", NAN,
                                      weights, 1u));
    ASSERT_FLOAT_EQ(weights[0], 7.0f, 0.0f);
}

TEST(facial_curve_rejects_nonfinite_unsorted_and_out_of_range_keys) {
    AnimFacialLibrary library;
    const f32 good_times[2] = {0.0f, 1.0f};
    const f32 good_values[2] = {0.0f, 1.0f};
    const f32 bad_times[2] = {1.0f, 0.0f};
    const f32 bad_values[2] = {0.0f, 1.1f};
    anim_facial_library_init(&library);
    ASSERT_TRUE(anim_facial_add_expression(&library, "expression"));
    ASSERT_FALSE(anim_facial_add_curve(&library, "expression", "bad", "target",
                                       2u, bad_times, good_values));
    ASSERT_FALSE(anim_facial_add_curve(&library, "expression", "bad", "target",
                                       2u, good_times, bad_values));
    const f32 nan_times[2] = {NAN, 1.0f};
    ASSERT_FALSE(anim_facial_add_curve(&library, "expression", "bad", "target",
                                       2u, nan_times, good_values));
    ASSERT_EQ(library.expressions[0].curve_count, 0u);
}

TEST(facial_rejects_duplicate_expressions_and_curve_bindings) {
    AnimFacialLibrary library;
    anim_facial_library_init(&library);
    ASSERT_TRUE(anim_facial_add_expression(&library, "expression"));
    ASSERT_FALSE(anim_facial_add_expression(&library, "expression"));
    const f32 times[1] = {0.0f};
    const f32 values[1] = {1.0f};
    ASSERT_TRUE(anim_facial_add_curve(&library, "expression", "one", "target",
                                      1u, times, values));
    ASSERT_FALSE(anim_facial_add_curve(&library, "expression", "two", "target",
                                       1u, times, values));
    ASSERT_EQ(library.expression_count, 1u);
    ASSERT_EQ(library.expressions[0].curve_count, 1u);
}

TEST(facial_expression_and_curve_capacities_are_bounded) {
    AnimFacialLibrary library;
    anim_facial_library_init(&library);
    char name[ANIM_FACIAL_NAME_CAP];
    for (u32 i = 0; i < ANIM_FACIAL_MAX_EXPRESSIONS; ++i) {
        snprintf(name, sizeof(name), "expression_%u", i);
        ASSERT_TRUE(anim_facial_add_expression(&library, name));
    }
    ASSERT_FALSE(anim_facial_add_expression(&library, "overflow"));
    const f32 times[1] = {0.0f};
    const f32 values[1] = {1.0f};
    for (u32 i = 0; i < ANIM_FACIAL_MAX_CURVES; ++i) {
        snprintf(name, sizeof(name), "curve_%u", i);
        char target[ANIM_FACIAL_NAME_CAP];
        snprintf(target, sizeof(target), "target_%u", i);
        ASSERT_TRUE(anim_facial_add_curve(&library, "expression_0", name, target,
                                          1u, times, values));
    }
    ASSERT_FALSE(anim_facial_add_curve(&library, "expression_0", "overflow", "other",
                                       1u, times, values));
}

TEST(facial_rejects_seventeenth_key_before_insertion) {
    AnimFacialLibrary library;
    anim_facial_library_init(&library);
    ASSERT_TRUE(anim_facial_add_expression(&library, "empty"));
    f32 times[ANIM_FACIAL_MAX_KEYS + 1u];
    f32 values[ANIM_FACIAL_MAX_KEYS + 1u];
    for (u32 i = 0; i <= ANIM_FACIAL_MAX_KEYS; ++i) {
        times[i] = (f32)i;
        values[i] = 0.5f;
    }
    ASSERT_FALSE(anim_facial_add_curve(&library, "empty", "curve", "target",
                                       ANIM_FACIAL_MAX_KEYS + 1u, times, values));
    ASSERT_EQ(library.expressions[0].curve_count, 0u);
}

TEST(facial_repeated_times_select_later_key) {
    AnimMorphSet morphs;
    ASSERT_TRUE(anim_morph_init(&morphs, 1u));
    const Vec3 delta[1] = {{{0.0f, 0.0f, 0.0f}}};
    ASSERT_TRUE(anim_morph_add_target(&morphs, "target", delta));
    AnimFacialLibrary library;
    anim_facial_library_init(&library);
    ASSERT_TRUE(anim_facial_add_expression(&library, "expression"));
    const f32 times[6] = {0.0f, 0.0f, 1.0f, 1.0f, 2.0f, 2.0f};
    const f32 values[6] = {0.1f, 0.2f, 0.3f, 0.4f, 0.5f, 0.6f};
    ASSERT_TRUE(anim_facial_add_curve(&library, "expression", "curve", "target",
                                      6u, times, values));
    const f32 expected[3] = {0.2f, 0.4f, 0.6f};
    for (u32 i = 0; i < 3u; ++i) {
        f32 weight = -1.0f;
        ASSERT_TRUE(anim_facial_evaluate(&library, &morphs, "expression",
                                         (f32)i, &weight, 1u));
        ASSERT_FLOAT_EQ(weight, expected[i], 1e-6f);
    }
}

TEST(facial_extreme_finite_curve_uses_wide_interpolation) {
    AnimMorphSet morphs;
    ASSERT_TRUE(anim_morph_init(&morphs, 1u));
    const Vec3 delta[1] = {{{0.0f, 0.0f, 0.0f}}};
    ASSERT_TRUE(anim_morph_add_target(&morphs, "target", delta));
    AnimFacialLibrary library;
    anim_facial_library_init(&library);
    ASSERT_TRUE(anim_facial_add_expression(&library, "expression"));
    const f32 extreme = 3.402823466e38F;
    const f32 times[2] = {-extreme, extreme};
    const f32 values[2] = {0.0f, 1.0f};
    ASSERT_TRUE(anim_facial_add_curve(&library, "expression", "curve", "target",
                                      2u, times, values));
    f32 weight = 7.0f;
    ASSERT_TRUE(anim_facial_evaluate(&library, &morphs, "expression",
                                     extreme * 0.5f, &weight, 1u));
    ASSERT_TRUE(isfinite(weight));
    ASSERT_FLOAT_EQ(weight, 0.75f, 1e-6f);
}

TEST_MAIN_BEGIN()
    RUN_TEST(facial_named_expression_drives_named_morphs);
    RUN_TEST(facial_missing_target_and_nonfinite_time_are_atomic);
    RUN_TEST(facial_curve_rejects_nonfinite_unsorted_and_out_of_range_keys);
    RUN_TEST(facial_rejects_duplicate_expressions_and_curve_bindings);
    RUN_TEST(facial_expression_and_curve_capacities_are_bounded);
    RUN_TEST(facial_rejects_seventeenth_key_before_insertion);
    RUN_TEST(facial_repeated_times_select_later_key);
    RUN_TEST(facial_extreme_finite_curve_uses_wide_interpolation);
TEST_MAIN_END()
