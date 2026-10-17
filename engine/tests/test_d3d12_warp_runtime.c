#include <rhi/rhi.h>
#include "test_framework.h"
/* Forces WARP via ENGINE_D3D12_WARP=1 (set in CTest ENVIRONMENT) so the
 * windows-d3d12 lane has a deterministic software GPU-runtime floor.
 * Evidence rule: WARP receipts are recorded with gpu=WARP and never
 * upgrade the evidence level past GPU-runtime. */
static RHIDevice *g_dev;

TEST(warp_device_identity_is_honest) {
    RHIDeviceInfo info;
    ASSERT_TRUE(rhi_device_get_info(g_dev, &info));
    ASSERT_EQ(info.backend, RHI_BACKEND_D3D12);
    /* WARP reports Microsoft Basic Render Driver; refuse to masquerade. */
    ASSERT_TRUE(strstr(info.device_name, "Basic Render") != NULL ||
                strstr(info.device_name, "WARP") != NULL);
    ASSERT_EQ(rhi_device_idle_ex(g_dev), RHI_RESULT_OK);
}

/* R715-5: the offscreen FBO path is the next layer the demo needs, and the
 * only honest way to prove it works is pixels, not handle plumbing. Bind
 * clears to a caller-owned colour, unbind restores the swapchain target, and
 * the colour texture is read back and compared. */
TEST(offscreen_fbo_clear_round_trips_pixels) {
    RHIOffscreenFBODesc desc;
    RHIOffscreenFBO fbo;
    RHICmdBuffer *cmd;
    unsigned char px[8 * 8 * 4];
    const int expect[4] = { 64, 128, 191, 255 }; /* 0.25/0.5/0.75/1.0 */
    int c;
    memset(&desc, 0, sizeof(desc));
    desc.width = 8u;
    desc.height = 8u;
    desc.color_format = RHI_FORMAT_R8G8B8A8_UNORM;
    desc.sample_count = 1u;
    fbo = rhi_offscreen_fbo_create_desc(g_dev, &desc);
    ASSERT_TRUE(rhi_handle_valid(fbo.fb));
    ASSERT_TRUE(rhi_handle_valid(fbo.color_tex));
    ASSERT_TRUE(rhi_handle_valid(fbo.depth_tex));
    ASSERT_EQ(fbo.width, 8u);
    ASSERT_EQ(fbo.height, 8u);
    ASSERT_EQ(fbo.sample_count, 1u);

    rhi_offscreen_fbo_set_clear_color(g_dev, &fbo, 0.25f, 0.5f, 0.75f, 1.0f);
    cmd = rhi_frame_begin(g_dev);
    ASSERT_TRUE(cmd != NULL);
    rhi_offscreen_fbo_bind(cmd, &fbo);     /* fresh bind clears */
    rhi_offscreen_fbo_unbind(cmd, 64u, 64u);
    ASSERT_EQ(rhi_frame_end_ex(g_dev), RHI_RESULT_OK);

    memset(px, 0, sizeof(px));
    ASSERT_TRUE(rhi_texture_read_pixels(g_dev, fbo.color_tex, px, sizeof(px)));
    for (c = 0; c < 4; ++c) {
        int diff = (int)px[c] - expect[c];
        if (diff < 0) diff = -diff;
        ASSERT_TRUE(diff <= 2);
    }
    /* The whole 8x8 must be cleared, not just the first pixel. */
    for (c = 4; c < (int)sizeof(px); c += 4) {
        ASSERT_EQ(px[c + 0], px[0]);
        ASSERT_EQ(px[c + 1], px[1]);
        ASSERT_EQ(px[c + 2], px[2]);
    }
    ASSERT_EQ(rhi_present_ex(g_dev), RHI_RESULT_OK);
    rhi_offscreen_fbo_destroy(g_dev, &fbo);
    ASSERT_FALSE(rhi_handle_valid(fbo.fb));
}

int main(void) {
#if defined(_WIN32)
    RHIResult r = RHI_RESULT_OK;
    g_dev = rhi_device_create_ex(RHI_BACKEND_D3D12, (void *)1, NULL, 64, 64, &r);
    if (g_dev == NULL) return 77;
    printf("=== Running Tests ===\n");
    RUN_TEST(warp_device_identity_is_honest);
    RUN_TEST(offscreen_fbo_clear_round_trips_pixels);
    rhi_device_destroy(g_dev);
    printf("\n=== Results: %d passed, %d failed, %d total ===\n",
           g_test_pass, g_test_fail, g_test_count);
    return g_test_fail > 0 ? 1 : 0;
#else
    return 77;
#endif
}
