#include "test_framework.h"

#include <editor/editor_image.h>

#include <stb_image_write.h>

#include <stdlib.h>
#include <string.h>

typedef struct {
    u8 data[65536];
    usize size;
} MemOut;

static void mem_write(void *context, void *data, int size) {
    MemOut *out = (MemOut *)context;
    if (size == 0) {
        return; /* stb may flush an empty chunk */
    }
    if (size < 0 || out->size + (usize)size > sizeof(out->data)) {
        out->size = sizeof(out->data) + 1u; /* overflow marker */
        return;
    }
    memcpy(out->data + out->size, data, (usize)size);
    out->size += (usize)size;
}

/* w x h RGBA image: pixel (x, y) = (x*20, y*30, 200, 255). */
static void fill_pattern(u8 *px, int w, int h) {
    int x, y;
    for (y = 0; y < h; y++) {
        for (x = 0; x < w; x++) {
            u8 *p = px + ((usize)y * (usize)w + (usize)x) * 4u;
            p[0] = (u8)(x * 20);
            p[1] = (u8)(y * 30);
            p[2] = 200u;
            p[3] = 255u;
        }
    }
}

static void make_png(MemOut *out, int w, int h) {
    u8 px[8 * 6 * 4];
    memset(out, 0, sizeof(*out));
    fill_pattern(px, w, h);
    (void)stbi_write_png_to_func(mem_write, out, w, h, 4, px, w * 4);
}

TEST(decode_png_returns_size_and_pixels) {
    MemOut png;
    BreakEditorImage img;
    u32 w = 0, h = 0;
    make_png(&png, 5, 3);
    ASSERT_TRUE(png.size > 0u && png.size <= sizeof(png.data));
    ASSERT_TRUE(break_editor_image_probe(png.data, png.size, &w, &h));
    ASSERT_EQ(w, 5u);
    ASSERT_EQ(h, 3u);
    ASSERT_TRUE(break_editor_image_decode(png.data, png.size, &img));
    if (img.rgba == NULL) return;
    ASSERT_EQ(img.width, 5u);
    ASSERT_EQ(img.height, 3u);
    ASSERT_NOT_NULL(img.rgba);
    /* pixel (4, 2) */
    ASSERT_EQ(img.rgba[(2u * 5u + 4u) * 4u + 0u], 80u);
    ASSERT_EQ(img.rgba[(2u * 5u + 4u) * 4u + 1u], 60u);
    ASSERT_EQ(img.rgba[(2u * 5u + 4u) * 4u + 2u], 200u);
    ASSERT_EQ(img.rgba[(2u * 5u + 4u) * 4u + 3u], 255u);
    break_editor_image_free(&img);
    ASSERT_TRUE((img.rgba) == NULL);
}

TEST(decode_bmp_without_alpha_is_opaque_rgba) {
    MemOut bmp;
    u8 rgb[4 * 2 * 3];
    BreakEditorImage img;
    usize i;
    memset(&bmp, 0, sizeof(bmp));
    for (i = 0; i < sizeof(rgb); i++) rgb[i] = (u8)(i * 9u);
    ASSERT_TRUE(stbi_write_bmp_to_func(mem_write, &bmp, 4, 2, 3, rgb) != 0);
    ASSERT_TRUE(bmp.size > 0u && bmp.size <= sizeof(bmp.data));
    ASSERT_TRUE(break_editor_image_decode(bmp.data, bmp.size, &img));
    if (img.rgba == NULL) return;
    ASSERT_EQ(img.width, 4u);
    ASSERT_EQ(img.height, 2u);
    ASSERT_EQ(img.rgba[0], rgb[0]);
    ASSERT_EQ(img.rgba[1], rgb[1]);
    ASSERT_EQ(img.rgba[2], rgb[2]);
    ASSERT_EQ(img.rgba[3], 255u);
    break_editor_image_free(&img);
}

TEST(bad_input_fails_and_zeroes_output) {
    static const u8 garbage[16] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
    MemOut png;
    BreakEditorImage img;
    u32 w = 7, h = 7;
    memset(&img, 0xAB, sizeof(img));
    ASSERT_FALSE(break_editor_image_decode(garbage, sizeof(garbage), &img));
    ASSERT_EQ(img.width, 0u);
    ASSERT_TRUE((img.rgba) == NULL);
    ASSERT_FALSE(break_editor_image_probe(garbage, sizeof(garbage), &w, &h));
    ASSERT_FALSE(break_editor_image_decode(NULL, 10u, &img));
    ASSERT_FALSE(break_editor_image_decode(garbage, 0u, &img));
    ASSERT_FALSE(break_editor_image_probe(NULL, 0u, &w, &h));
    make_png(&png, 5, 3);
    /* truncated: header intact, pixel data cut */
    ASSERT_FALSE(break_editor_image_decode(png.data, png.size / 2u, &img));
    ASSERT_TRUE((img.rgba) == NULL);
}

TEST(oversized_dimensions_are_rejected_before_decode) {
    /* Minimal 24-bit BMP header claiming 4097 x 1; no pixel data needed:
     * probe must refuse on the header alone, decode must refuse too. */
    u8 bmp[54];
    u32 w = 0, h = 0;
    BreakEditorImage img;
    u32 width = BREAK_EDITOR_IMAGE_MAX_DIM + 1u;
    memset(bmp, 0, sizeof(bmp));
    bmp[0] = 'B';
    bmp[1] = 'M';
    bmp[10] = 54u;           /* pixel data offset */
    bmp[14] = 40u;           /* BITMAPINFOHEADER */
    bmp[18] = (u8)(width & 0xFFu);
    bmp[19] = (u8)((width >> 8) & 0xFFu);
    bmp[22] = 1u;            /* height 1 */
    bmp[26] = 1u;            /* planes */
    bmp[28] = 24u;           /* bpp */
    ASSERT_FALSE(break_editor_image_probe(bmp, sizeof(bmp), &w, &h));
    ASSERT_FALSE(break_editor_image_decode(bmp, sizeof(bmp), &img));
    ASSERT_TRUE((img.rgba) == NULL);
}

TEST(supported_names) {
    ASSERT_TRUE(break_editor_image_is_supported_name("a.png"));
    ASSERT_TRUE(break_editor_image_is_supported_name("A.PNG"));
    ASSERT_TRUE(break_editor_image_is_supported_name("photo.jpeg"));
    ASSERT_TRUE(break_editor_image_is_supported_name("x.jpg"));
    ASSERT_TRUE(break_editor_image_is_supported_name("x.bmp"));
    ASSERT_TRUE(break_editor_image_is_supported_name("x.TGA"));
    ASSERT_FALSE(break_editor_image_is_supported_name("level.bscn"));
    ASSERT_FALSE(break_editor_image_is_supported_name("png"));
    ASSERT_FALSE(break_editor_image_is_supported_name(".png.txt"));
    ASSERT_FALSE(break_editor_image_is_supported_name(""));
    ASSERT_FALSE(break_editor_image_is_supported_name(NULL));
}

TEST(mip_chain_box_filters_down_to_one_pixel) {
    /* 4x2: left half white, right half black */
    u8 px[4 * 2 * 4];
    for (u32 y = 0; y < 2; y++) {
        for (u32 x = 0; x < 4; x++) {
            u8 v = x < 2 ? 255 : 0;
            u8 *p = px + (y * 4 + x) * 4;
            p[0] = p[1] = p[2] = v;
            p[3] = 255;
        }
    }
    BreakEditorImage img = {4, 2, px};
    ASSERT_EQ(break_editor_image_mip_count(4, 2), 3u);
    ASSERT_EQ(break_editor_image_mip_count(1, 1), 1u);
    ASSERT_EQ(break_editor_image_mip_count(4096, 1), 13u);
    ASSERT_EQ(break_editor_image_mip_count(0, 4), 0u);
    BreakEditorImageMips mips;
    ASSERT_TRUE(break_editor_image_build_mips(&img, &mips));
    ASSERT_EQ(mips.count, 3u);
    ASSERT_EQ(mips.width[0], 4u);
    ASSERT_EQ(mips.height[0], 2u);
    ASSERT_TRUE(mips.level[0] == px);          /* level 0 is borrowed */
    ASSERT_EQ(mips.width[1], 2u);
    ASSERT_EQ(mips.height[1], 1u);
    ASSERT_EQ(mips.level[1][0], 255u);         /* left 2x2 block: white */
    ASSERT_EQ(mips.level[1][4], 0u);           /* right block: black */
    ASSERT_EQ(mips.level[1][7], 255u);
    ASSERT_EQ(mips.width[2], 1u);
    ASSERT_EQ(mips.height[2], 1u);
    ASSERT_TRUE(mips.level[2][0] >= 127u && mips.level[2][0] <= 128u);
    ASSERT_EQ(mips.level[2][3], 255u);
    break_editor_image_free_mips(&mips);
    ASSERT_EQ(mips.count, 0u);
    /* odd sizes clamp the 2x2 footprint at the edge */
    {
        u8 odd[3 * 3 * 4];
        memset(odd, 200, sizeof(odd));
        BreakEditorImage o = {3, 3, odd};
        ASSERT_TRUE(break_editor_image_build_mips(&o, &mips));
        ASSERT_EQ(mips.count, 2u);
        ASSERT_EQ(mips.width[1], 1u);
        ASSERT_EQ(mips.level[1][0], 200u);
        break_editor_image_free_mips(&mips);
    }
    ASSERT_FALSE(break_editor_image_build_mips(NULL, &mips));
    {
        BreakEditorImage empty = {0, 0, NULL};
        ASSERT_FALSE(break_editor_image_build_mips(&empty, &mips));
        ASSERT_EQ(mips.count, 0u);
    }
}

int main(void) {
    printf("=== Running Tests ===\n");
    RUN_TEST(decode_png_returns_size_and_pixels);
    RUN_TEST(decode_bmp_without_alpha_is_opaque_rgba);
    RUN_TEST(bad_input_fails_and_zeroes_output);
    RUN_TEST(oversized_dimensions_are_rejected_before_decode);
    RUN_TEST(supported_names);
    RUN_TEST(mip_chain_box_filters_down_to_one_pixel);
    printf("\n=== Results: %d passed, %d failed, %d total ===\n", g_test_pass,
           g_test_fail, g_test_count);
    return g_test_fail > 0 ? 1 : 0;
}
