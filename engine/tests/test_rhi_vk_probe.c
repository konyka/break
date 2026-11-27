#include "test_framework.h"
#include "rhi/rhi_vk_probe.h"

TEST(adapter_score_orders_discrete_over_integrated_over_software) {
    VkProbeAdapterInfo d = { VK_PROBE_DEVICE_TYPE_DISCRETE, 0u, true };
    VkProbeAdapterInfo i = { VK_PROBE_DEVICE_TYPE_INTEGRATED, 0u, true };
    VkProbeAdapterInfo c = { VK_PROBE_DEVICE_TYPE_CPU, 0u, true };
    VkProbeAdapterInfo o = { VK_PROBE_DEVICE_TYPE_OTHER, 0u, true };
    ASSERT_TRUE(vk_probe_adapter_score(&d) > vk_probe_adapter_score(&i));
    ASSERT_TRUE(vk_probe_adapter_score(&i) > vk_probe_adapter_score(&c));
    ASSERT_TRUE(vk_probe_adapter_score(&c) > vk_probe_adapter_score(&o));
}

TEST(adapter_unsuitable_scores_negative_and_never_selected) {
    VkProbeAdapterInfo bad = { VK_PROBE_DEVICE_TYPE_DISCRETE, 0u, false };
    VkProbeAdapterInfo ok  = { VK_PROBE_DEVICE_TYPE_CPU, 0u, true };
    VkProbeAdapterInfo set[2] = { bad, ok };
    ASSERT_EQ(vk_probe_adapter_score(&bad), -1);
    ASSERT_EQ(vk_probe_select_adapter(set, 2u), 1);
    ASSERT_EQ(vk_probe_select_adapter(&bad, 1u), -1);
    ASSERT_EQ(vk_probe_select_adapter(NULL, 0u), -1);
}

TEST(adapter_tie_breaks_on_api_version_then_lowest_index) {
    VkProbeAdapterInfo set[3] = {
        { VK_PROBE_DEVICE_TYPE_DISCRETE, 0x00401000u, true },
        { VK_PROBE_DEVICE_TYPE_DISCRETE, 0x00403000u, true },
        { VK_PROBE_DEVICE_TYPE_DISCRETE, 0x00403000u, true },
    };
    ASSERT_EQ(vk_probe_select_adapter(set, 3u), 1);
    set[1].api_version = set[0].api_version;
    set[2].api_version = set[0].api_version;
    ASSERT_EQ(vk_probe_select_adapter(set, 3u), 0);
}

TEST(queue_families_prefer_combined_graphics_present) {
    u32 flags[3] = { VK_PROBE_QUEUE_GRAPHICS_BIT, 0u,
                     VK_PROBE_QUEUE_GRAPHICS_BIT };
    bool present[3] = { false, true, true };
    u32 g = 99u, p = 99u;
    ASSERT_TRUE(vk_probe_choose_queue_families(flags, present, 3u, &g, &p));
    ASSERT_EQ(g, 2u); /* combined 优先：家族 2 双支持 */
    ASSERT_EQ(p, 2u);
}

TEST(queue_families_split_when_no_combined) {
    u32 flags[2] = { VK_PROBE_QUEUE_GRAPHICS_BIT, 0u };
    bool present[2] = { false, true };
    u32 g = 99u, p = 99u;
    ASSERT_TRUE(vk_probe_choose_queue_families(flags, present, 2u, &g, &p));
    ASSERT_EQ(g, 0u);
    ASSERT_EQ(p, 1u);
    ASSERT_FALSE(vk_probe_choose_queue_families(flags, present, 1u, &g, &p));
}

TEST(present_mode_vsync_prefers_mailbox_then_relaxed_then_fifo) {
    u32 all[4] = { VK_PROBE_PRESENT_MODE_FIFO, VK_PROBE_PRESENT_MODE_IMMEDIATE,
                   VK_PROBE_PRESENT_MODE_FIFO_RELAXED, VK_PROBE_PRESENT_MODE_MAILBOX };
    u32 no_mailbox[3] = { VK_PROBE_PRESENT_MODE_FIFO, VK_PROBE_PRESENT_MODE_IMMEDIATE,
                          VK_PROBE_PRESENT_MODE_FIFO_RELAXED };
    u32 fifo_only[1] = { VK_PROBE_PRESENT_MODE_FIFO };
    ASSERT_EQ(vk_probe_choose_present_mode(all, 4u, true), VK_PROBE_PRESENT_MODE_MAILBOX);
    ASSERT_EQ(vk_probe_choose_present_mode(no_mailbox, 3u, true),
              VK_PROBE_PRESENT_MODE_FIFO_RELAXED);
    ASSERT_EQ(vk_probe_choose_present_mode(fifo_only, 1u, true),
              VK_PROBE_PRESENT_MODE_FIFO);
}

TEST(present_mode_no_vsync_prefers_immediate) {
    u32 all[4] = { VK_PROBE_PRESENT_MODE_FIFO, VK_PROBE_PRESENT_MODE_IMMEDIATE,
                   VK_PROBE_PRESENT_MODE_FIFO_RELAXED, VK_PROBE_PRESENT_MODE_MAILBOX };
    u32 no_immediate[2] = { VK_PROBE_PRESENT_MODE_FIFO, VK_PROBE_PRESENT_MODE_MAILBOX };
    ASSERT_EQ(vk_probe_choose_present_mode(all, 4u, false),
              VK_PROBE_PRESENT_MODE_IMMEDIATE);
    ASSERT_EQ(vk_probe_choose_present_mode(no_immediate, 2u, false),
              VK_PROBE_PRESENT_MODE_MAILBOX);
    ASSERT_EQ(vk_probe_choose_present_mode(NULL, 0u, false),
              VK_PROBE_PRESENT_MODE_FIFO);
}

/* R646: UNORM first -- the engine's tonemap writes gamma-encoded values
 * itself, so an sRGB swapchain would encode them a second time. */
TEST(surface_format_prefers_bgra_unorm_then_rgba_unorm_then_first) {
    VkProbeSurfaceFormat formats[4] = {
        { VK_PROBE_FORMAT_B8G8R8A8_SRGB, VK_PROBE_COLORSPACE_SRGB_NONLINEAR },
        { VK_PROBE_FORMAT_R8G8B8A8_UNORM, VK_PROBE_COLORSPACE_SRGB_NONLINEAR },
        { VK_PROBE_FORMAT_B8G8R8A8_UNORM, VK_PROBE_COLORSPACE_SRGB_NONLINEAR },
        { VK_PROBE_FORMAT_R8G8B8A8_SRGB, VK_PROBE_COLORSPACE_SRGB_NONLINEAR },
    };
    VkProbeSurfaceFormat picked = { 0xFFFFFFFFu, 0xFFFFFFFFu };
    ASSERT_TRUE(vk_probe_choose_surface_format(formats, 4u, &picked));
    ASSERT_EQ(picked.format, VK_PROBE_FORMAT_B8G8R8A8_UNORM);
    ASSERT_TRUE(vk_probe_choose_surface_format(formats, 2u, &picked));
    ASSERT_EQ(picked.format, VK_PROBE_FORMAT_R8G8B8A8_UNORM);
    ASSERT_TRUE(vk_probe_choose_surface_format(&formats[3], 1u, &picked));
    ASSERT_EQ(picked.format, VK_PROBE_FORMAT_R8G8B8A8_SRGB); /* 无 UNORM 时退回 formats[0] */
    ASSERT_FALSE(vk_probe_choose_surface_format(formats, 0u, &picked));
}

TEST(surface_format_undefined_sentinel_means_any) {
    VkProbeSurfaceFormat any[1] = {
        { VK_PROBE_FORMAT_UNDEFINED, VK_PROBE_COLORSPACE_SRGB_NONLINEAR } };
    VkProbeSurfaceFormat picked = { 0u, 0u };
    ASSERT_TRUE(vk_probe_choose_surface_format(any, 1u, &picked));
    ASSERT_EQ(picked.format, VK_PROBE_FORMAT_B8G8R8A8_UNORM);
    ASSERT_EQ(picked.color_space, VK_PROBE_COLORSPACE_SRGB_NONLINEAR);
}

TEST(feature_bits_compose_rhi_feature_values) {
    ASSERT_EQ(vk_probe_feature_bits(false, false, false), 0u);
    ASSERT_EQ(vk_probe_feature_bits(true, false, false),
              VK_PROBE_FEATURE_ACCELERATION_STRUCTURE);
    ASSERT_EQ(vk_probe_feature_bits(true, true, true),
              VK_PROBE_FEATURE_ACCELERATION_STRUCTURE |
              VK_PROBE_FEATURE_RAY_TRACING_PIPELINE |
              VK_PROBE_FEATURE_RAY_QUERY);
}

TEST(present_regions_pass_through_in_bounds_rects_on_layer_zero) {
    RHIPresentRect damage[2] = { { 0, 0, 10, 20 }, { 30, 40, 5, 6 } };
    VkProbeRectLayer out[2];
    u32 count = 99u;
    ASSERT_TRUE(vk_probe_present_regions(damage, 2u, 100u, 80u, out, 2u, &count));
    ASSERT_EQ(count, 2u);
    ASSERT_EQ(out[0].x, 0); ASSERT_EQ(out[0].y, 0);
    ASSERT_EQ(out[0].w, 10u); ASSERT_EQ(out[0].h, 20u); ASSERT_EQ(out[0].layer, 0u);
    ASSERT_EQ(out[1].x, 30); ASSERT_EQ(out[1].y, 40);
    ASSERT_EQ(out[1].w, 5u); ASSERT_EQ(out[1].h, 6u); ASSERT_EQ(out[1].layer, 0u);
}

TEST(present_regions_clip_to_swapchain_extent) {
    RHIPresentRect damage[2] = { { 90, 70, 20, 30 }, { -5, -3, 10, 10 } };
    VkProbeRectLayer out[2];
    u32 count = 0u;
    ASSERT_TRUE(vk_probe_present_regions(damage, 2u, 100u, 80u, out, 2u, &count));
    ASSERT_EQ(count, 2u);
    ASSERT_EQ(out[0].x, 90); ASSERT_EQ(out[0].y, 70);
    ASSERT_EQ(out[0].w, 10u); ASSERT_EQ(out[0].h, 10u);
    ASSERT_EQ(out[1].x, 0); ASSERT_EQ(out[1].y, 0);
    ASSERT_EQ(out[1].w, 5u); ASSERT_EQ(out[1].h, 7u);
}

TEST(present_regions_drop_empty_and_outside_rects) {
    RHIPresentRect damage[4] = { { 100, 0, 5, 5 }, { 0, 80, 5, 5 },
                                 { 3, 4, 0, 5 }, { 7, 8, 2, 3 } };
    VkProbeRectLayer out[4];
    u32 count = 0u;
    ASSERT_TRUE(vk_probe_present_regions(damage, 4u, 100u, 80u, out, 4u, &count));
    ASSERT_EQ(count, 1u);
    ASSERT_EQ(out[0].x, 7); ASSERT_EQ(out[0].y, 8);
    ASSERT_EQ(out[0].w, 2u); ASSERT_EQ(out[0].h, 3u);
}

TEST(present_regions_fall_back_to_full_present_when_nothing_usable) {
    RHIPresentRect outside[2] = { { 200, 0, 5, 5 }, { -10, 0, 10, 5 } };
    RHIPresentRect one[1] = { { 0, 0, 4, 4 } };
    VkProbeRectLayer out[2];
    u32 count = 7u;
    ASSERT_FALSE(vk_probe_present_regions(outside, 2u, 100u, 80u, out, 2u, &count));
    ASSERT_EQ(count, 0u);
    count = 7u;
    ASSERT_FALSE(vk_probe_present_regions(one, 0u, 100u, 80u, out, 2u, &count));
    ASSERT_EQ(count, 0u);
    ASSERT_FALSE(vk_probe_present_regions(NULL, 1u, 100u, 80u, out, 2u, &count));
    ASSERT_FALSE(vk_probe_present_regions(one, 1u, 0u, 80u, out, 2u, &count));
    ASSERT_FALSE(vk_probe_present_regions(one, 1u, 100u, 0u, out, 2u, &count));
    ASSERT_FALSE(vk_probe_present_regions(one, 1u, 100u, 80u, NULL, 2u, &count));
    ASSERT_FALSE(vk_probe_present_regions(one, 1u, 100u, 80u, out, 2u, NULL));
}

TEST(present_regions_reject_more_rects_than_capacity) {
    RHIPresentRect damage[3] = { { 0, 0, 1, 1 }, { 2, 2, 1, 1 }, { 4, 4, 1, 1 } };
    VkProbeRectLayer out[3];
    u32 count = 7u;
    ASSERT_FALSE(vk_probe_present_regions(damage, 3u, 100u, 80u, out, 2u, &count));
    ASSERT_EQ(count, 0u);
    ASSERT_TRUE(vk_probe_present_regions(damage, 3u, 100u, 80u, out, 3u, &count));
    ASSERT_EQ(count, 3u);
}

TEST(present_regions_clip_huge_extents_without_overflow) {
    RHIPresentRect damage[1] = { { 2147483000, 0, 4000000000u, 10 } };
    RHIPresentRect wide[1] = { { 10, 0, 4294967295u, 10 } };
    VkProbeRectLayer out[1];
    u32 count = 0u;
    ASSERT_FALSE(vk_probe_present_regions(damage, 1u, 100u, 80u, out, 1u, &count));
    ASSERT_TRUE(vk_probe_present_regions(wide, 1u, 100u, 80u, out, 1u, &count));
    ASSERT_EQ(count, 1u);
    ASSERT_EQ(out[0].x, 10); ASSERT_EQ(out[0].w, 90u);
}

TEST_MAIN_BEGIN()
    RUN_TEST(adapter_score_orders_discrete_over_integrated_over_software);
    RUN_TEST(adapter_unsuitable_scores_negative_and_never_selected);
    RUN_TEST(adapter_tie_breaks_on_api_version_then_lowest_index);
    RUN_TEST(queue_families_prefer_combined_graphics_present);
    RUN_TEST(queue_families_split_when_no_combined);
    RUN_TEST(present_mode_vsync_prefers_mailbox_then_relaxed_then_fifo);
    RUN_TEST(present_mode_no_vsync_prefers_immediate);
    RUN_TEST(surface_format_prefers_bgra_unorm_then_rgba_unorm_then_first);
    RUN_TEST(surface_format_undefined_sentinel_means_any);
    RUN_TEST(feature_bits_compose_rhi_feature_values);
    RUN_TEST(present_regions_pass_through_in_bounds_rects_on_layer_zero);
    RUN_TEST(present_regions_clip_to_swapchain_extent);
    RUN_TEST(present_regions_drop_empty_and_outside_rects);
    RUN_TEST(present_regions_fall_back_to_full_present_when_nothing_usable);
    RUN_TEST(present_regions_reject_more_rects_than_capacity);
    RUN_TEST(present_regions_clip_huge_extents_without_overflow);
TEST_MAIN_END()
