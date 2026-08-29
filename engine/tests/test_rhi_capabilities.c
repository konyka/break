#include "test_framework.h"

#include "rhi/rhi.h"

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

TEST_MAIN_BEGIN()
    RUN_TEST(sample_count_bits_are_portable_and_bounded);
    RUN_TEST(capability_query_rejects_invalid_arguments);
    RUN_TEST(offscreen_descriptor_requires_safe_supported_values);
    RUN_TEST(offscreen_descriptor_defaults_to_single_sample);
    RUN_TEST(present_damage_rects_require_bounded_nonempty_regions);
    RUN_TEST(present_damage_rects_have_a_fixed_upper_bound);
TEST_MAIN_END()
