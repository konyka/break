#include "test_framework.h"
#include <rhi/rhi.h>

/* Plan C Task 3: real-device contract for the native Metal backend. Runs on
 * macOS with ENGINE_RHI_BACKEND_METAL; everywhere else it exits 77 (SKIP).
 * The CAMetalLayer is created offscreen (explicit drawableSize, no window —
 * CAMetalLayer can acquire drawables without being attached to a view). */
#if defined(ENGINE_RHI_BACKEND_METAL) && defined(ENGINE_PLATFORM_MACOS)

/* CAMetalLayer creation needs Objective-C; metal_test_layer.m wraps it so
 * this TU stays C11. */
void *metal_test_layer_create(u32 w, u32 h);
void metal_test_layer_destroy(void *layer);

static RHIDevice *g_dev;
static void *g_layer;
static RHIResult g_create_result = RHI_RESULT_OK;

TEST(create_ex_reports_ok) {
    ASSERT_NOT_NULL(g_dev);
    ASSERT_EQ(g_create_result, RHI_RESULT_OK);
    ASSERT_EQ(rhi_device_get_status(g_dev), RHI_DEVICE_STATUS_READY);
}

TEST(zero_width_is_invalid_argument) {
    RHIResult r = RHI_RESULT_OK;
    RHIDevice *dev = rhi_device_create_ex(RHI_BACKEND_METAL, g_layer, NULL,
                                          0u, 64u, &r);
    ASSERT_TRUE(dev == NULL);
    ASSERT_EQ(r, RHI_RESULT_INVALID_ARGUMENT);
}

TEST(null_layer_is_invalid_argument) {
    RHIResult r = RHI_RESULT_OK;
    RHIDevice *dev = rhi_device_create_ex(RHI_BACKEND_METAL, NULL, NULL,
                                          64u, 64u, &r);
    ASSERT_TRUE(dev == NULL);
    ASSERT_EQ(r, RHI_RESULT_INVALID_ARGUMENT);
}

TEST(capabilities_match_metal_contract) {
    RHICapabilities caps;
    ASSERT_TRUE(rhi_device_get_capabilities(g_dev, &caps));
    ASSERT_EQ(caps.backend, RHI_BACKEND_METAL);
    ASSERT_TRUE((caps.color_sample_counts & rhi_sample_count_bit(1u)) != 0u);
    ASSERT_TRUE((caps.depth_sample_counts & rhi_sample_count_bit(1u)) != 0u);
    /* CAMetalLayer drawables cannot be multisampled (MSAA only via offscreen
     * resolve), so the surface itself is 1x. */
    ASSERT_EQ(caps.surface_sample_count, 1u);
    ASSERT_TRUE(caps.color_resolve_supported);
    ASSERT_FALSE(caps.depth_resolve_supported);
    ASSERT_TRUE(caps.scissor_supported);
    ASSERT_FALSE(caps.present_target_preserved);
    ASSERT_FALSE(caps.present_damage_supported);
    ASSERT_FALSE(caps.present_buffer_age_supported);
    /* Metal's intersection-function model has no raygen-pipeline equivalent;
     * this bit must never be set (fail-closed). */
    ASSERT_EQ(caps.feature_bits & RHI_FEATURE_RAY_TRACING_PIPELINE, 0u);
}

TEST(device_info_reports_hardware) {
    RHIDeviceInfo info;
    ASSERT_TRUE(rhi_device_get_info(g_dev, &info));
    ASSERT_EQ(info.backend, RHI_BACKEND_METAL);
    ASSERT_TRUE(info.device_name[0] != '\0');
    ASSERT_EQ(info.api_version, (3u << 22));  /* Metal 3 baseline */
    ASSERT_EQ(info.feature_bits & RHI_FEATURE_RAY_TRACING_PIPELINE, 0u);
}

int main(void) {
    g_layer = metal_test_layer_create(64u, 64u);
    if (g_layer == NULL) return 77;
    g_dev = rhi_device_create_ex(RHI_BACKEND_METAL, g_layer, NULL, 64u, 64u,
                                 &g_create_result);
    if (g_dev == NULL) {
        /* No Metal device on this host (GPU-less CI runner): a clean
         * UNAVAILABLE/ERROR is a skip, never a fabricated success. */
        metal_test_layer_destroy(g_layer);
        if (g_create_result == RHI_RESULT_UNAVAILABLE ||
            g_create_result == RHI_RESULT_ERROR) return 77;
        return 1;
    }
    printf("=== Running Tests ===\n");
    RUN_TEST(create_ex_reports_ok);
    RUN_TEST(zero_width_is_invalid_argument);
    RUN_TEST(null_layer_is_invalid_argument);
    RUN_TEST(capabilities_match_metal_contract);
    RUN_TEST(device_info_reports_hardware);
    rhi_device_destroy(g_dev);
    metal_test_layer_destroy(g_layer);
    printf("\n=== Results: %d passed, %d failed, %d total ===\n",
           g_test_pass, g_test_fail, g_test_count);
    return g_test_fail > 0 ? 1 : 0;
}
#else
int main(void) { return 77; }
#endif
