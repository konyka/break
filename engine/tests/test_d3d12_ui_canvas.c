/* R667: the myui break-RHI canvas on D3D12, end to end through the public
 * vgcanvas API. R666 made D3D12 honour the caller's RHISampler; this pins the
 * one UI feature that depends on it -- my_vgcanvas_set_scale_filter -- which
 * the canvas advertises (capabilities.scale_filters) and which, before R666,
 * silently stayed bilinear on D3D12.
 *
 * A 2x1 image (black | white) is drawn into a 16x4 target, a 4x magnification
 * per source texel along x. NEAREST must give a hard step: columns 0..7 black,
 * 8..15 white. BILINEAR must ramp across the middle: the target columns whose
 * centres sit between the two texel centres read neither 0 nor 255. The
 * canvas's image sampler is CLAMP, so the outer columns are pure black / white
 * in both modes. */
#include <rhi/rhi.h>
#include <stdio.h>
#include <string.h>
#include "myr/my_vgcanvas.h"
#include "myr/my_vgcanvas_break_rhi.h"
#include "test_framework.h"

static RHIDevice *g_dev;

static int draw_and_read(my_scale_filter_t filter, unsigned char *px) {
    static const uint8_t image[2 * 1 * 4] = { 0, 0, 0, 255, 255, 255, 255, 255 };
    RHIOffscreenFBODesc fd;
    RHIOffscreenFBO fbo;
    my_vgcanvas_t *vg;
    RHICmdBuffer *cmd;
    my_rectf_t dst;
    int ok = 1;
    memset(&fd, 0, sizeof(fd));
    fd.width = 16u; fd.height = 4u;
    fd.color_format = RHI_FORMAT_R8G8B8A8_UNORM;
    fd.sample_count = 1u;
    fbo = rhi_offscreen_fbo_create_desc(g_dev, &fd);
    if (!rhi_handle_valid(fbo.fb)) return 0;
    vg = my_vgcanvas_break_rhi_create(NULL, g_dev, 16u, 4u);
    if (vg == NULL) { rhi_offscreen_fbo_destroy(g_dev, &fbo); return 0; }
    if (my_vgcanvas_set_scale_filter(vg, filter) != MY_RET_OK) ok = 0;
    cmd = rhi_frame_begin(g_dev);
    if (cmd == NULL) ok = 0;
    if (ok) {
        rhi_offscreen_fbo_set_clear_color(g_dev, &fbo, 1.0f, 0.0f, 0.0f, 1.0f);
        rhi_offscreen_fbo_bind(cmd, &fbo);
        my_vgcanvas_break_rhi_set_cmd(vg, cmd);
        if (my_vgcanvas_begin_frame(vg, NULL) != MY_RET_OK) ok = 0;
        dst.x = 0.0f; dst.y = 0.0f; dst.w = 16.0f; dst.h = 4.0f;
        if (ok && my_vgcanvas_draw_image(vg, image, 2, 1, &dst, NULL) != MY_RET_OK) ok = 0;
        if (ok && my_vgcanvas_end_frame(vg) != MY_RET_OK) ok = 0;
        rhi_offscreen_fbo_unbind(cmd, 64u, 64u);
        if (rhi_frame_end_ex(g_dev) != RHI_RESULT_OK) ok = 0;
        memset(px, 0, 16 * 4 * 4);
        if (!rhi_texture_read_pixels(g_dev, fbo.color_tex, px, 16 * 4 * 4)) ok = 0;
        if (rhi_present_ex(g_dev) != RHI_RESULT_OK) ok = 0;
    }
    my_vgcanvas_break_rhi_set_cmd(vg, NULL);
    my_vgcanvas_destroy(vg);
    rhi_offscreen_fbo_destroy(g_dev, &fbo);
    return ok;
}

TEST(canvas_scale_filter_nearest_and_bilinear_reach_the_pixels) {
    static unsigned char near_px[16 * 4 * 4], lin_px[16 * 4 * 4];
    int x, y, mids = 0;
    ASSERT_TRUE(draw_and_read(MY_SCALE_FILTER_NEAREST, near_px));
    ASSERT_TRUE(draw_and_read(MY_SCALE_FILTER_BILINEAR, lin_px));
    for (y = 0; y < 4; ++y) {
        for (x = 0; x < 16; ++x) {
            int n = near_px[(y * 16 + x) * 4 + 1];   /* green: 0 or 255 for the image */
            int l = lin_px[(y * 16 + x) * 4 + 1];
            int want_n = x < 8 ? 0 : 255;
            if (n != want_n)
                printf("  NEAREST px (%d,%d) green %d, want %d\n", x, y, n, want_n);
            ASSERT_EQ(n, want_n);
            /* Outer quarter of each half: past the texel centres, clamped. */
            if (x < 4) ASSERT_TRUE(l <= 2);
            if (x >= 12) ASSERT_TRUE(l >= 253);
            if (l > 10 && l < 245) ++mids;
        }
    }
    /* Bilinear ramps over the 8 columns between the texel centres (u from
     * 0.25 to 0.75): every one of them on every row is a true in-between. */
    if (mids < 24) printf("  BILINEAR in-between pixels: %d (want >= 24)\n", mids);
    ASSERT_TRUE(mids >= 24);
}

int main(void) {
#if defined(_WIN32)
    RHIResult r = RHI_RESULT_OK;
    g_dev = rhi_device_create_ex(RHI_BACKEND_D3D12, (void *)1, NULL, 64, 64, &r);
    if (g_dev == NULL) return 77;
    printf("=== Running Tests ===\n");
    RUN_TEST(canvas_scale_filter_nearest_and_bilinear_reach_the_pixels);
    rhi_device_destroy(g_dev);
    printf("\n=== Results: %d passed, %d failed, %d total ===\n",
           g_test_pass, g_test_fail, g_test_count);
    return g_test_fail > 0 ? 1 : 0;
#else
    return 77;
#endif
}
