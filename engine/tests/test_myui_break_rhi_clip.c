/* The Break RHI vgcanvas must honour the clip for text and images.
 *
 * The retained UI repaints only damaged rectangles: my_window clips to each
 * dirty rect and repaints the whole widget tree, so everything outside the
 * clip must be discarded. Rects and paths already were; text and images
 * were not, so every partial repaint drew all text and images again on top
 * of the previous frame's (alpha-blended) glyphs. Antialiased edges grew
 * darker frame by frame and the editor's text looked bold and doubled.
 *
 * Real device (Vulkan or OpenGL, whatever the build links), offscreen FBO,
 * readback. Skips (77) without a display or device. */
#include "test_framework.h"

#include <engine.h>
#include <platform/platform.h>
#include <rhi/rhi.h>

#include "myr/my_font.h"
#include "myr/my_vgcanvas.h"
#include "myr/my_vgcanvas_break_rhi.h"

#include <stdlib.h>
#include <string.h>

#define W 64u
#define H 24u

static Platform *g_platform;
static RHIDevice *g_dev;
static my_font_t *g_font;

static const char *k_fonts[] = {
    "/usr/share/fonts/google-noto-vf/NotoSans[wght].ttf",
    "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf",
    "/usr/share/fonts/dejavu-sans-fonts/DejaVuSans.ttf",
    "/usr/share/fonts/TTF/DejaVuSans.ttf",
    "/usr/share/fonts/liberation-sans-fonts/LiberationSans-Regular.ttf",
    "/usr/share/fonts/truetype/liberation/LiberationSans-Regular.ttf",
};

typedef enum { DRAW_TEXT, DRAW_IMAGE } DrawKind;

/* Draws "Add" (or an 8x8 white image) at (4, 2) under `clip` (NULL = none)
 * and returns how many pixels are lit; *lit_outside counts lit pixels
 * outside the clip. */
static int draw_and_count(DrawKind kind, const my_rectf_t *clip,
                          int *lit_outside) {
    static unsigned char px[W * H * 4];
    static u8 white[8 * 8 * 4];
    RHIOffscreenFBODesc fd;
    RHIOffscreenFBO fbo;
    my_vgcanvas_t *vg;
    RHICmdBuffer *cmd;
    int lit = 0;
    u32 x, y;
    memset(&fd, 0, sizeof(fd));
    fd.width = W;
    fd.height = H;
    fd.color_format = RHI_FORMAT_R8G8B8A8_UNORM;
    fd.sample_count = 1u;
    fbo = rhi_offscreen_fbo_create_desc(g_dev, &fd);
    vg = my_vgcanvas_break_rhi_create(NULL, g_dev, W, H);
    if (!rhi_handle_valid(fbo.fb) || vg == NULL) return -1;
    memset(white, 255, sizeof(white));
    cmd = rhi_frame_begin(g_dev);
    if (cmd == NULL) return -1;
    rhi_offscreen_fbo_set_clear_color(g_dev, &fbo, 0.0f, 0.0f, 0.0f, 1.0f);
    rhi_offscreen_fbo_bind(cmd, &fbo);
    my_vgcanvas_break_rhi_set_target(vg, &fbo);
    my_vgcanvas_break_rhi_set_cmd(vg, cmd);
    (void)my_vgcanvas_begin_frame(vg, NULL);
    if (clip != NULL) (void)my_vgcanvas_clip_rect(vg, clip);
    if (kind == DRAW_TEXT) {
        (void)my_vgcanvas_set_font(vg, g_font, 14);
        my_vgcanvas_set_fill_color(vg, my_color_rgba(255, 255, 255, 255));
        (void)my_vgcanvas_draw_text(vg, "Add", 4.0f, 2.0f);
    } else {
        my_rectf_t dst = {4.0f, 2.0f, 16.0f, 16.0f};
        (void)my_vgcanvas_draw_image(vg, white, 8, 8, &dst, NULL);
    }
    (void)my_vgcanvas_end_frame(vg);
    rhi_offscreen_fbo_unbind(cmd, W, H);
    rhi_frame_end(g_dev);
    memset(px, 0, sizeof(px));
    (void)rhi_texture_read_pixels(g_dev, fbo.color_tex, px, sizeof(px));
    rhi_present(g_dev);
    *lit_outside = 0;
    for (y = 0; y < H; y++) {
        for (x = 0; x < W; x++) {
            bool on = px[(y * W + x) * 4u] > 8u;
            bool inside = clip == NULL ||
                          ((float)x >= clip->x && (float)x < clip->x + clip->w &&
                           (float)y >= clip->y && (float)y < clip->y + clip->h);
            if (on) {
                lit++;
                if (!inside) (*lit_outside)++;
            }
        }
    }
    my_vgcanvas_break_rhi_set_cmd(vg, NULL);
    my_vgcanvas_destroy(vg);
    rhi_offscreen_fbo_destroy(g_dev, &fbo);
    return lit;
}

static void check(DrawKind kind) {
    const my_rectf_t outside = {40.0f, 0.0f, 10.0f, 10.0f};
    const my_rectf_t left_half = {0.0f, 0.0f, 12.0f, (float)H};
    int out_all = 0, out_none = 0, out_half = 0;
    int all = draw_and_count(kind, NULL, &out_all);
    int none = draw_and_count(kind, &outside, &out_none);
    int half = draw_and_count(kind, &left_half, &out_half);
    printf("  %s: unclipped=%d clip-outside=%d clip-left-half=%d (outside %d)\n",
           kind == DRAW_TEXT ? "text" : "image", all, none, half, out_half);
    ASSERT_TRUE(all > 20);
    ASSERT_EQ(none, 0);          /* nothing may be drawn outside the clip */
    ASSERT_EQ(out_half, 0);
    ASSERT_TRUE(half > 0 && half < all);
}

TEST(text_respects_the_clip_rect) {
    check(DRAW_TEXT);
}

TEST(image_respects_the_clip_rect) {
    check(DRAW_IMAGE);
}

int main(void) {
    PlatformConfig pc;
    usize i;
    memset(&pc, 0, sizeof(pc));
    pc.width = W;
    pc.height = W;
    pc.title = "myui break rhi clip";
    g_platform = platform_create(&pc);
    if (g_platform == NULL) return 77;
    g_dev = rhi_device_create_compiled(platform_window_native(g_platform),
                                       platform_surface_native(g_platform),
                                       platform_display_native(g_platform), W,
                                       W);
    if (g_dev == NULL) {
        platform_destroy(g_platform);
        return 77;
    }
    for (i = 0; i < sizeof(k_fonts) / sizeof(k_fonts[0]) && g_font == NULL; i++) {
        const char *paths[1] = {k_fonts[i]};
        FILE *f = fopen(k_fonts[i], "rb");
        if (f == NULL) continue;
        fclose(f);
        g_font = my_font_create_chain(NULL, paths, 1, 64);
    }
    printf("=== Running Tests ===\n");
    if (g_font != NULL) {
        RUN_TEST(text_respects_the_clip_rect);
    } else {
        printf("  (no TrueType font found: text case skipped)\n");
    }
    RUN_TEST(image_respects_the_clip_rect);
    if (g_font != NULL) my_font_destroy(g_font);
    rhi_device_destroy(g_dev);
    platform_destroy(g_platform);
    printf("\n=== Results: %d passed, %d failed, %d total ===\n", g_test_pass,
           g_test_fail, g_test_count);
    return g_test_fail > 0 ? 1 : 0;
}
