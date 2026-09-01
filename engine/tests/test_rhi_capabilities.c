#include "test_framework.h"

#include "rhi/rhi.h"
#include "rhi/rhi_present_history.h"

TEST(sample_count_bits_are_portable_and_bounded)
{
    ASSERT_EQ(rhi_sample_count_bit(0u), 0u);
    ASSERT_EQ(rhi_sample_count_bit(3u), 0u);
    ASSERT_EQ(rhi_sample_count_bit(1u), 1u);
    ASSERT_EQ(rhi_sample_count_bit(2u), 2u);
    ASSERT_EQ(rhi_sample_count_bit(4u), 4u);
    ASSERT_EQ(rhi_sample_count_bit(64u), 64u);
}

TEST(capability_query_rejects_invalid_arguments)
{
    RHICapabilities caps;
    ASSERT_FALSE(rhi_device_get_capabilities(NULL, NULL));
    ASSERT_FALSE(rhi_device_get_capabilities(NULL, &caps));
}

TEST(offscreen_descriptor_requires_safe_supported_values)
{
    RHICapabilities caps = {0};
    caps.color_sample_counts = rhi_sample_count_bit(1u) |
                               rhi_sample_count_bit(2u) |
                               rhi_sample_count_bit(4u);
    caps.depth_sample_counts = rhi_sample_count_bit(1u) |
                               rhi_sample_count_bit(2u) |
                               rhi_sample_count_bit(4u);
    caps.color_resolve_supported = true;
    caps.depth_resolve_supported = true;

    RHIOffscreenFBODesc desc = {64u, 64u, RHI_FORMAT_R8G8B8A8_UNORM, 2u};
    ASSERT_TRUE(rhi_offscreen_fbo_desc_validate(&caps, &desc));
    desc.width = 0u;
    ASSERT_FALSE(rhi_offscreen_fbo_desc_validate(&caps, &desc));
    desc.width = 64u;
    desc.sample_count = 3u;
    ASSERT_FALSE(rhi_offscreen_fbo_desc_validate(&caps, &desc));
    desc.sample_count = 4u;
    caps.depth_resolve_supported = false;
    ASSERT_FALSE(rhi_offscreen_fbo_desc_validate(&caps, &desc));
    caps.depth_resolve_supported = true;
    caps.depth_sample_counts = rhi_sample_count_bit(1u) | rhi_sample_count_bit(2u);
    ASSERT_FALSE(rhi_offscreen_fbo_desc_validate(&caps, &desc));
}

TEST(offscreen_descriptor_defaults_to_single_sample)
{
    RHICapabilities caps = {0};
    caps.color_sample_counts = rhi_sample_count_bit(1u);
    caps.depth_sample_counts = rhi_sample_count_bit(1u);
    RHIOffscreenFBODesc desc = {1u, 1u, RHI_FORMAT_R8G8B8A8_UNORM, 0u};
    ASSERT_TRUE(rhi_offscreen_fbo_desc_validate(&caps, &desc));
    ASSERT_EQ(desc.sample_count, 0u);
}

TEST(present_damage_rects_require_bounded_nonempty_regions)
{
    RHIPresentRect rect = {0, 0, 10u, 10u};

    ASSERT_TRUE(rhi_present_damage_validate(&rect, 1u, 100u, 100u));
    ASSERT_TRUE(rhi_present_damage_validate(NULL, 0u, 100u, 100u));
    ASSERT_FALSE(rhi_present_damage_validate(NULL, 1u, 100u, 100u));
    ASSERT_FALSE(rhi_present_damage_validate(&rect, 1u, 0u, 100u));
    ASSERT_TRUE(rhi_present_damage_validate(&rect, 1u, 100u, 100u));

    rect.x = -1;
    ASSERT_FALSE(rhi_present_damage_validate(&rect, 1u, 100u, 100u));
    rect.x = 95;
    rect.w = 10u;
    ASSERT_FALSE(rhi_present_damage_validate(&rect, 1u, 100u, 100u));
    rect.x = 0;
    rect.w = 0u;
    ASSERT_FALSE(rhi_present_damage_validate(&rect, 1u, 100u, 100u));
}

TEST(present_damage_rects_have_a_fixed_upper_bound)
{
    RHIPresentRect rects[RHI_MAX_PRESENT_DAMAGE_RECTS + 1u] = {{0, 0, 1u, 1u}};
    u32 i;

    for (i = 0u; i < RHI_MAX_PRESENT_DAMAGE_RECTS + 1u; ++i) {
        rects[i] = (RHIPresentRect){(i32)(i % 10u), (i32)(i / 10u), 1u, 1u};
    }

    ASSERT_TRUE(rhi_present_damage_validate(rects, RHI_MAX_PRESENT_DAMAGE_RECTS,
                                             100u, 100u));
    ASSERT_FALSE(rhi_present_damage_validate(rects,
                                              RHI_MAX_PRESENT_DAMAGE_RECTS + 1u,
                                              100u, 100u));
}

TEST(screenshot_region_requires_bounded_rgba8_storage)
{
    ASSERT_TRUE(rhi_screenshot_region_validate(2u, 3u, 4u, 5u,
                                                16u, 16u, 80u));
    ASSERT_TRUE(rhi_screenshot_region_validate(2u, 3u, 4u, 5u,
                                                16u, 16u, 81u));
    ASSERT_FALSE(rhi_screenshot_region_validate(2u, 3u, 4u, 5u,
                                                 16u, 16u, 79u));
    ASSERT_FALSE(rhi_screenshot_region_validate(16u, 0u, 1u, 1u,
                                                 16u, 16u, 4u));
    ASSERT_FALSE(rhi_screenshot_region_validate(0u, 0u, 0u, 1u,
                                                 16u, 16u, 0u));
    ASSERT_FALSE(rhi_screenshot_region_validate(0u, 15u, 2u, 2u,
                                                 16u, 16u, 16u));
    ASSERT_FALSE(rhi_screenshot_region_validate(0u, 0u, 8192u, 8192u,
                                                 8192u, 8192u,
                                                 (usize)RHI_MAX_SCREENSHOT_BYTES));
}

TEST(screenshot_region_rejects_size_overflow)
{
    ASSERT_FALSE(rhi_screenshot_region_validate(UINT32_MAX, UINT32_MAX,
                                                 UINT32_MAX, UINT32_MAX,
                                                 UINT32_MAX, UINT32_MAX,
                                                 SIZE_MAX));
}

TEST(present_history_forces_full_on_first_image_use)
{
    RHIPresentHistory history;
    RHIPresentRect current = {10, 20, 30u, 40u};
    RHIPresentRect output[RHI_MAX_PRESENT_DAMAGE_RECTS];
    u32 output_count = 0u;
    bool full = false;

    ASSERT_TRUE(rhi_present_history_init(&history, 2u, 100u, 100u));
    ASSERT_TRUE(rhi_present_history_prepare(&history, 0u, &current, 1u,
                                             output, RHI_MAX_PRESENT_DAMAGE_RECTS,
                                             &output_count, &full));
    ASSERT_TRUE(full);
    ASSERT_EQ(output_count, 1u);
    ASSERT_EQ(output[0].w, 100u);
    ASSERT_EQ(output[0].h, 100u);
}

TEST(present_history_merges_damage_since_image_was_used)
{
    RHIPresentHistory history;
    RHIPresentRect first = {0, 0, 10u, 10u};
    RHIPresentRect second = {80, 80, 10u, 10u};
    RHIPresentRect current = {40, 40, 10u, 10u};
    RHIPresentRect output[RHI_MAX_PRESENT_DAMAGE_RECTS];
    u32 output_count = 0u;
    bool full = false;

    ASSERT_TRUE(rhi_present_history_init(&history, 2u, 100u, 100u));
    ASSERT_TRUE(rhi_present_history_commit(&history, 0u, &first, 1u));
    ASSERT_TRUE(rhi_present_history_prepare(&history, 1u, &second, 1u,
                                             output, RHI_MAX_PRESENT_DAMAGE_RECTS,
                                             &output_count, &full));
    ASSERT_TRUE(full);
    ASSERT_TRUE(rhi_present_history_commit(&history, 1u, &second, 1u));
    ASSERT_TRUE(rhi_present_history_prepare(&history, 0u, &current, 1u,
                                             output, RHI_MAX_PRESENT_DAMAGE_RECTS,
                                             &output_count, &full));
    ASSERT_FALSE(full);
    ASSERT_EQ(output_count, 2u);
    ASSERT_EQ(output[0].x, 80);
    ASSERT_EQ(output[1].x, 40);
}

TEST(present_history_reset_invalidates_every_swapchain_image)
{
    RHIPresentHistory history;
    RHIPresentRect damage = {1, 2, 3u, 4u};
    RHIPresentRect output[RHI_MAX_PRESENT_DAMAGE_RECTS];
    u32 output_count = 0u;
    bool full = false;

    ASSERT_TRUE(rhi_present_history_init(&history, 2u, 20u, 20u));
    ASSERT_TRUE(rhi_present_history_commit(&history, 0u, &damage, 1u));
    ASSERT_TRUE(rhi_present_history_reset(&history));
    ASSERT_TRUE(rhi_present_history_prepare(&history, 0u, &damage, 1u,
                                             output, RHI_MAX_PRESENT_DAMAGE_RECTS,
                                             &output_count, &full));
    ASSERT_TRUE(full);
    ASSERT_TRUE(rhi_present_history_prepare(&history, 1u, &damage, 1u,
                                             output, RHI_MAX_PRESENT_DAMAGE_RECTS,
                                             &output_count, &full));
    ASSERT_TRUE(full);
}

TEST(present_history_aborts_to_safe_full_frame)
{
    RHIPresentHistory history;
    RHIPresentRect damage = {1, 2, 3u, 4u};
    RHIPresentRect output[RHI_MAX_PRESENT_DAMAGE_RECTS];
    u32 output_count = 0u;
    bool full = false;

    ASSERT_TRUE(rhi_present_history_init(&history, 1u, 20u, 20u));
    ASSERT_TRUE(rhi_present_history_commit(&history, 0u, &damage, 1u));
    rhi_present_history_abort(&history);
    ASSERT_TRUE(rhi_present_history_prepare(&history, 0u, &damage, 1u,
                                             output, RHI_MAX_PRESENT_DAMAGE_RECTS,
                                             &output_count, &full));
    ASSERT_TRUE(full);
}

TEST(present_history_rejects_invalid_damage_without_state_change)
{
    RHIPresentHistory history;
    RHIPresentRect valid = {1, 2, 3u, 4u};
    RHIPresentRect invalid = {-1, 2, 3u, 4u};

    ASSERT_TRUE(rhi_present_history_init(&history, 1u, 20u, 20u));
    ASSERT_TRUE(rhi_present_history_commit(&history, 0u, &valid, 1u));
    ASSERT_FALSE(rhi_present_history_commit(&history, 0u, &invalid, 1u));
    ASSERT_EQ(rhi_present_history_generation(&history), 1u);
    ASSERT_TRUE(rhi_present_history_image_generation(&history, 0u) == 1u);
}

TEST(present_history_overflow_invalidates_other_images)
{
    RHIPresentHistory history;
    RHIPresentRect damage = {1, 2, 3u, 4u};
    RHIPresentRect output[RHI_MAX_PRESENT_DAMAGE_RECTS];
    u32 output_count = 0u;
    bool full = false;
    u32 i;

    ASSERT_TRUE(rhi_present_history_init(&history, 2u, 20u, 20u));
    ASSERT_TRUE(rhi_present_history_commit(&history, 0u, &damage, 1u));
    for (i = 1u; i < RHI_PRESENT_HISTORY_CAPACITY; ++i) {
        ASSERT_TRUE(rhi_present_history_commit(&history, 1u, &damage, 1u));
    }
    ASSERT_TRUE(rhi_present_history_prepare(&history, 0u, &damage, 1u,
                                             output, RHI_MAX_PRESENT_DAMAGE_RECTS,
                                             &output_count, &full));
    ASSERT_TRUE(full);
    ASSERT_EQ(rhi_present_history_generation(&history),
              RHI_PRESENT_HISTORY_CAPACITY);
    ASSERT_TRUE(rhi_present_history_commit(&history, 0u, &damage, 1u));
    ASSERT_TRUE(rhi_present_history_prepare(&history, 1u, &damage, 1u,
                                             output, RHI_MAX_PRESENT_DAMAGE_RECTS,
                                             &output_count, &full));
    ASSERT_TRUE(full);
}

TEST(present_damage_history_requires_full_for_unknown_age)
{
    RHIPresentDamageHistory history;
    RHIPresentRect current = {2, 3, 4u, 5u};
    RHIPresentRect output[RHI_MAX_PRESENT_DAMAGE_RECTS];
    u32 output_count = 0u;
    bool full = false;

    ASSERT_TRUE(rhi_present_damage_history_init(&history, 100u, 80u));
    ASSERT_TRUE(rhi_present_damage_history_prepare_age(
        &history, 0u, &current, 1u, output, RHI_MAX_PRESENT_DAMAGE_RECTS,
        &output_count, &full));
    ASSERT_TRUE(full);
    ASSERT_EQ(output_count, 1u);
    ASSERT_EQ(output[0].w, 100u);
    ASSERT_EQ(output[0].h, 80u);
}

TEST(present_damage_history_requires_history_for_age_one)
{
    RHIPresentDamageHistory history;
    RHIPresentRect current = {2, 3, 4u, 5u};
    RHIPresentRect output[RHI_MAX_PRESENT_DAMAGE_RECTS];
    u32 output_count = 0u;
    bool full = false;

    ASSERT_TRUE(rhi_present_damage_history_init(&history, 100u, 80u));
    ASSERT_TRUE(rhi_present_damage_history_prepare_age(
        &history, 1u, &current, 1u, output, RHI_MAX_PRESENT_DAMAGE_RECTS,
        &output_count, &full));
    ASSERT_TRUE(full);
    ASSERT_EQ(output_count, 1u);
}

TEST(present_damage_history_merges_age_without_reusing_old_damage)
{
    RHIPresentDamageHistory history;
    RHIPresentRect first = {1, 2, 3u, 4u};
    RHIPresentRect second = {20, 21, 5u, 6u};
    RHIPresentRect current = {40, 41, 7u, 8u};
    RHIPresentRect output[RHI_MAX_PRESENT_DAMAGE_RECTS];
    u32 output_count = 0u;
    bool full = false;

    ASSERT_TRUE(rhi_present_damage_history_init(&history, 100u, 100u));
    ASSERT_TRUE(rhi_present_damage_history_commit(&history, &first, 1u));
    ASSERT_TRUE(rhi_present_damage_history_commit(&history, &second, 1u));
    ASSERT_TRUE(rhi_present_damage_history_prepare_age(
        &history, 2u, &current, 1u, output, RHI_MAX_PRESENT_DAMAGE_RECTS,
        &output_count, &full));
    ASSERT_FALSE(full);
    ASSERT_EQ(output_count, 2u);
    ASSERT_EQ(output[0].x, 20);
    ASSERT_EQ(output[1].x, 40);
}

TEST(present_damage_history_rejects_age_gap_and_preserves_state)
{
    RHIPresentDamageHistory history;
    RHIPresentRect damage = {1, 2, 3u, 4u};
    RHIPresentRect output[RHI_MAX_PRESENT_DAMAGE_RECTS];
    u32 output_count = 0u;
    bool full = false;

    ASSERT_TRUE(rhi_present_damage_history_init(&history, 20u, 20u));
    ASSERT_TRUE(rhi_present_damage_history_commit(&history, &damage, 1u));
    ASSERT_FALSE(rhi_present_damage_history_prepare_age(
        &history, 0u, &(RHIPresentRect){-1, 0, 1u, 1u}, 1u, output,
        RHI_MAX_PRESENT_DAMAGE_RECTS, &output_count, &full));
    ASSERT_TRUE(rhi_present_damage_history_prepare_age(
        &history, 3u, &damage, 1u, output, RHI_MAX_PRESENT_DAMAGE_RECTS,
        &output_count, &full));
    ASSERT_TRUE(full);
    ASSERT_EQ(history.entry_count, 1u);
}

TEST(present_damage_history_overflow_forces_full)
{
    RHIPresentDamageHistory history;
    RHIPresentRect damage = {0, 0, 1u, 1u};
    RHIPresentRect output[RHI_MAX_PRESENT_DAMAGE_RECTS];
    u32 output_count = 0u;
    bool full = false;
    u32 i;

    ASSERT_TRUE(rhi_present_damage_history_init(&history, 20u, 20u));
    for (i = 0u; i < RHI_PRESENT_DAMAGE_HISTORY_CAPACITY; ++i) {
        ASSERT_TRUE(rhi_present_damage_history_commit(&history, &damage, 1u));
    }
    ASSERT_TRUE(rhi_present_damage_history_prepare_age(
        &history, RHI_PRESENT_DAMAGE_HISTORY_CAPACITY + 1u, &damage, 1u,
        output, RHI_MAX_PRESENT_DAMAGE_RECTS, &output_count, &full));
    ASSERT_TRUE(full);
    ASSERT_EQ(output_count, 1u);
}

TEST_MAIN_BEGIN()
    RUN_TEST(sample_count_bits_are_portable_and_bounded);
    RUN_TEST(capability_query_rejects_invalid_arguments);
    RUN_TEST(offscreen_descriptor_requires_safe_supported_values);
    RUN_TEST(offscreen_descriptor_defaults_to_single_sample);
    RUN_TEST(present_damage_rects_require_bounded_nonempty_regions);
    RUN_TEST(present_damage_rects_have_a_fixed_upper_bound);
    RUN_TEST(screenshot_region_requires_bounded_rgba8_storage);
    RUN_TEST(screenshot_region_rejects_size_overflow);
    RUN_TEST(present_history_forces_full_on_first_image_use);
    RUN_TEST(present_history_merges_damage_since_image_was_used);
    RUN_TEST(present_history_reset_invalidates_every_swapchain_image);
    RUN_TEST(present_history_aborts_to_safe_full_frame);
    RUN_TEST(present_history_rejects_invalid_damage_without_state_change);
    RUN_TEST(present_history_overflow_invalidates_other_images);
    RUN_TEST(present_damage_history_requires_full_for_unknown_age);
    RUN_TEST(present_damage_history_requires_history_for_age_one);
    RUN_TEST(present_damage_history_merges_age_without_reusing_old_damage);
    RUN_TEST(present_damage_history_rejects_age_gap_and_preserves_state);
    RUN_TEST(present_damage_history_overflow_forces_full);
TEST_MAIN_END()
