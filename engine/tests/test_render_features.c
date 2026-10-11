#include "test_framework.h"

#include <renderer/render_features.h>

TEST(dlss_requires_all_vendor_prerequisites)
{
    RenderFeatureCapabilities capabilities = {true, true, false, true};
    RenderFeatureSelection selection = render_features_select(
        &capabilities, true, RENDER_UPSCALER_DLSS);

    ASSERT_EQ(selection.path, RENDER_PATH_RAY_TRACING);
    ASSERT_EQ(selection.upscaler, RENDER_UPSCALER_DIRECT);
    ASSERT_EQ(selection.fallback, RENDER_FALLBACK_DLSS_RUNTIME_UNAVAILABLE);
}

TEST(dlss_is_not_selected_on_an_unsupported_api)
{
    RenderFeatureCapabilities capabilities = {true, true, true, false};
    RenderFeatureSelection selection = render_features_select(
        &capabilities, true, RENDER_UPSCALER_DLSS);

    ASSERT_EQ(selection.upscaler, RENDER_UPSCALER_DIRECT);
    ASSERT_EQ(selection.fallback, RENDER_FALLBACK_DLSS_API_UNSUPPORTED);
}

TEST(ray_tracing_falls_back_without_disabling_tsr)
{
    RenderFeatureCapabilities capabilities = {false, false, false, false};
    RenderFeatureSelection selection = render_features_select(
        &capabilities, true, RENDER_UPSCALER_TSR);

    ASSERT_EQ(selection.path, RENDER_PATH_RASTER);
    ASSERT_EQ(selection.upscaler, RENDER_UPSCALER_TSR);
    ASSERT_EQ(selection.fallback, RENDER_FALLBACK_RAY_TRACING_UNSUPPORTED);
}

TEST(null_capabilities_use_safe_defaults)
{
    RenderFeatureSelection selection = render_features_select(
        NULL, true, RENDER_UPSCALER_DLSS);

    ASSERT_EQ(selection.path, RENDER_PATH_RASTER);
    ASSERT_EQ(selection.upscaler, RENDER_UPSCALER_DIRECT);
    ASSERT_EQ(selection.fallback, RENDER_FALLBACK_NONE);
}

TEST_MAIN_BEGIN()
    RUN_TEST(dlss_requires_all_vendor_prerequisites);
    RUN_TEST(dlss_is_not_selected_on_an_unsupported_api);
    RUN_TEST(ray_tracing_falls_back_without_disabling_tsr);
    RUN_TEST(null_capabilities_use_safe_defaults);
TEST_MAIN_END()
