/* test_font_load.c — font_renderer_init input validation (R389)
 *
 * font.c had no test coverage at all, which is how R386 (init-failure resource
 * leaks) and R389 (two out-of-bounds reads on malformed font files) both landed
 * there unnoticed. The TTF is read and parsed before the first rhi_* call, so
 * every rejection path can be exercised headlessly with dev = NULL; the RHI
 * symbols below exist only to satisfy the linker and are never reached by these
 * tests. If font.c starts calling a new rhi_* function this target fails to
 * link, which is the intended signal to look at it.
 *
 * Covered:
 *   - missing file
 *   - zero-byte file        (R389-A: 1-byte OOB read in stbtt__isfont)
 *   - file below the sfnt offset table size
 *   - well-formed but non-font file (R389-B: -1 offset became 0xFFFFFFFF and
 *     stbtt__find_table read a wild pointer — hard SEGV)
 */

#include "test_framework.h"
#include <ui/font.h>
#include <rhi/rhi.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

/* ---- RHI stubs (link-only; the tests below never reach a draw path) ---- */

RHIDevice *g_current_device = NULL;

static RHIBuffer   s_null_buffer   = {0};
static RHIShader   s_null_shader   = {0};
static RHIPipeline s_null_pipeline = {0};
static RHITexture  s_null_texture  = {0};
static RHISampler  s_null_sampler  = {0};

u32 rhi_frame_index(RHIDevice *dev) { (void)dev; return 0u; }

RHIBuffer rhi_buffer_create(RHIDevice *dev, const RHIBufferDesc *desc) {
    (void)dev; (void)desc; return s_null_buffer;
}
void rhi_buffer_destroy(RHIDevice *dev, RHIBuffer buf) { (void)dev; (void)buf; }
void rhi_buffer_update(RHIDevice *dev, RHIBuffer buf, const void *data, usize size) {
    (void)dev; (void)buf; (void)data; (void)size;
}

RHIShader rhi_shader_create(RHIDevice *dev, const char *source, usize len, bool is_fragment) {
    (void)dev; (void)source; (void)len; (void)is_fragment; return s_null_shader;
}
void rhi_shader_destroy(RHIDevice *dev, RHIShader shader) { (void)dev; (void)shader; }

RHIPipeline rhi_pipeline_create(RHIDevice *dev, const RHIPipelineDesc *desc) {
    (void)dev; (void)desc; return s_null_pipeline;
}
void rhi_pipeline_destroy(RHIDevice *dev, RHIPipeline pipe) { (void)dev; (void)pipe; }

RHITexture rhi_texture_create(RHIDevice *dev, const RHITextureDesc *desc) {
    (void)dev; (void)desc; return s_null_texture;
}
void rhi_texture_destroy(RHIDevice *dev, RHITexture tex) { (void)dev; (void)tex; }

RHISampler rhi_sampler_create(RHIDevice *dev, const RHISamplerDesc *desc) {
    (void)dev; (void)desc; return s_null_sampler;
}
void rhi_sampler_destroy(RHIDevice *dev, RHISampler sampler) { (void)dev; (void)sampler; }

void rhi_cmd_bind_pipeline(RHICmdBuffer *cmd, RHIPipeline pipe) { (void)cmd; (void)pipe; }
void rhi_cmd_bind_vertex_buffer(RHICmdBuffer *cmd, RHIBuffer buf, usize offset) {
    (void)cmd; (void)buf; (void)offset;
}
void rhi_cmd_draw(RHICmdBuffer *cmd, u32 vertex_count, u32 instance_count) {
    (void)cmd; (void)vertex_count; (void)instance_count;
}
void rhi_cmd_bind_texture(RHICmdBuffer *cmd, RHITexture tex, RHISampler sampler, u32 unit) {
    (void)cmd; (void)tex; (void)sampler; (void)unit;
}
void rhi_cmd_set_uniform_vec4(RHICmdBuffer *cmd, i32 location, f32 x, f32 y, f32 z, f32 w) {
    (void)cmd; (void)location; (void)x; (void)y; (void)z; (void)w;
}

/* ---- helpers ---- */

static const char *TMP_FONT = "/tmp/test_font_load.bin";

static bool write_bytes(const char *path, const void *data, usize n) {
    FILE *f = fopen(path, "wb");
    if (!f) return false;
    bool ok = (n == 0) || (fwrite(data, 1, n, f) == n);
    fclose(f);
    return ok;
}

/* ---- tests ---- */

TEST(font_init_rejects_missing_file)
{
    FontRenderer fr;
    ASSERT_TRUE(!font_renderer_init(&fr, NULL, "/tmp/no_such_font_xyz.ttf", 16.0f));
}

/* R389-A: a zero-byte file passed the `sz < 0` guard, so malloc(0) returned a
 * minimal block and stbtt read the sfnt tag out of bounds. */
TEST(font_init_rejects_empty_file)
{
    ASSERT_TRUE(write_bytes(TMP_FONT, "", 0));

    FontRenderer fr;
    ASSERT_TRUE(!font_renderer_init(&fr, NULL, TMP_FONT, 16.0f));
    remove(TMP_FONT);
}

/* R389-A: anything below the 12-byte sfnt offset table cannot be a font. */
TEST(font_init_rejects_file_below_offset_table)
{
    const unsigned char tiny[8] = { 0x00, 0x01, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x80 };
    ASSERT_TRUE(write_bytes(TMP_FONT, tiny, sizeof(tiny)));

    FontRenderer fr;
    ASSERT_TRUE(!font_renderer_init(&fr, NULL, TMP_FONT, 16.0f));
    remove(TMP_FONT);
}

/* R389-B: large enough to clear any size floor, but not a font — stbtt returns
 * offset -1, which as a stbtt_uint32 became 0xFFFFFFFF and sent
 * stbtt__find_table off to `data + 0xFFFFFFFF + 4`. Pre-fix this is a SEGV, so
 * the assertion below never got a chance to run. */
TEST(font_init_rejects_non_font_file)
{
    unsigned char junk[64];
    for (usize i = 0; i < sizeof(junk); i++) junk[i] = (unsigned char)('A' + (i % 26));
    ASSERT_TRUE(write_bytes(TMP_FONT, junk, sizeof(junk)));

    FontRenderer fr;
    ASSERT_TRUE(!font_renderer_init(&fr, NULL, TMP_FONT, 16.0f));
    remove(TMP_FONT);
}

/* R400: TTF read had min-bytes floor (R389) but no max — sparse multi-GB OOM. */
TEST(font_init_rejects_oversized_file)
{
    FILE *f = fopen(TMP_FONT, "wb");
    ASSERT_NOT_NULL(f);
#if defined(_POSIX_C_SOURCE) && _POSIX_C_SOURCE >= 200112L
    ASSERT_TRUE(ftruncate(fileno(f), (off_t)FONT_TTF_MAX_BYTES + 1) == 0);
#else
    if (fseek(f, (long)FONT_TTF_MAX_BYTES, SEEK_SET) == 0) fputc('x', f);
#endif
    fclose(f);

    FontRenderer fr;
    ASSERT_TRUE(!font_renderer_init(&fr, NULL, TMP_FONT, 16.0f));
    remove(TMP_FONT);
}

/* ---- R436: kerning -------------------------------------------------------
 *
 * The RHI-less init paths above can never reach a baked pair table (init
 * bails at texture creation with dev = NULL), so the kerning logic is
 * exercised against a synthetic FontRenderer instead: two glyphs 'A' and 'V'
 * with 10px advances, one kern pair A->V of -2px. Pure lookup plus both
 * layout paths (text_width, draw) are covered; draw emits into quad_data
 * without touching the RHI, so it runs headlessly too. */

static void make_kern_fr(FontRenderer *fr) {
    memset(fr, 0, sizeof(*fr));
    for (u32 i = 0; i < FONT_CPMAP_SIZE; i++) fr->cp_map[i] = -1;
    fr->glyphs[0].codepoint = 'A';
    fr->glyphs[0].advance   = 10.0f;
    fr->glyphs[0].width     = 8.0f;
    fr->glyphs[0].height    = 8.0f;
    fr->cp_map['A'] = 0;
    fr->glyphs[1].codepoint = 'V';
    fr->glyphs[1].advance   = 10.0f;
    fr->glyphs[1].width     = 8.0f;
    fr->glyphs[1].height    = 8.0f;
    fr->cp_map['V'] = 1;
    fr->glyph_count = 2;
    /* -2.0 px in the fixed-point 1/64px storage used by the pair table. */
    fr->kern_pairs[0] = (FontKernPair){ 0, 1, -128 };
    fr->kern_count = 1;
}

TEST(font_kern_lookup_hit)
{
    FontRenderer fr;
    make_kern_fr(&fr);
    ASSERT_FLOAT_EQ(font_kern_advance(&fr, 'A', 'V'), -2.0f, 1e-4f);
}

TEST(font_kern_lookup_miss)
{
    FontRenderer fr;
    make_kern_fr(&fr);
    /* reversed pair not in table */
    ASSERT_FLOAT_EQ(font_kern_advance(&fr, 'V', 'A'), 0.0f, 1e-4f);
    /* codepoint without a baked glyph */
    ASSERT_FLOAT_EQ(font_kern_advance(&fr, 'A', 'Z'), 0.0f, 1e-4f);
    /* codepoint outside the cp_map range */
    ASSERT_FLOAT_EQ(font_kern_advance(&fr, 'A', 0x20ACu), 0.0f, 1e-4f);
    /* no previous glyph (line start) */
    ASSERT_FLOAT_EQ(font_kern_advance(&fr, 0, 'V'), 0.0f, 1e-4f);
}

TEST(font_kern_width_applies_pair)
{
    FontRenderer fr;
    make_kern_fr(&fr);
    f32 w_a  = font_renderer_text_width(&fr, "A");
    f32 w_v  = font_renderer_text_width(&fr, "V");
    f32 w_av = font_renderer_text_width(&fr, "AV");
    ASSERT_TRUE(w_av < w_a + w_v);
    ASSERT_FLOAT_EQ(w_av, w_a + w_v - 2.0f, 1e-4f);
}

TEST(font_kern_width_empty_table_unchanged)
{
    /* Behavior compat: with no kern pairs, width is pure advance accumulation. */
    FontRenderer fr;
    make_kern_fr(&fr);
    fr.kern_count = 0;
    ASSERT_FLOAT_EQ(font_renderer_text_width(&fr, "AV"), 20.0f, 1e-4f);
}

TEST(font_kern_width_not_across_newline)
{
    FontRenderer fr;
    make_kern_fr(&fr);
    /* Add A->A = -3px so a leaked prev across '\n' changes the result:
     * correct  "A\nAA" = max(10, 10 + 10 - 3) = 17
     * leaked   "A\nAA" = max(10, -3 + 10 - 3 + 10) = 14 */
    fr.kern_pairs[1] = (FontKernPair){ 0, 0, -192 };
    fr.kern_count = 2;
    ASSERT_FLOAT_EQ(font_renderer_text_width(&fr, "A\nAA"), 17.0f, 1e-4f);
}

TEST(font_kern_width_unknown_cp_falls_back_for_pair)
{
    FontRenderer fr;
    make_kern_fr(&fr);
    /* '?' must exist for the fallback glyph; give it idx 2, advance 10. */
    fr.glyphs[2] = fr.glyphs[0];
    fr.glyphs[2].codepoint = '?';
    fr.cp_map['?'] = 2;
    fr.glyph_count = 3;
    /* kern A->? = -2px: a codepoint with no glyph (here 'Z') renders as '?',
     * so "AZ" must pick up the A->? pair, not A->Z. */
    fr.kern_pairs[1] = (FontKernPair){ 0, 2, -128 };
    fr.kern_count = 2;
    ASSERT_FLOAT_EQ(font_renderer_text_width(&fr, "AZ"), 18.0f, 1e-4f);
}

TEST(font_kern_draw_offsets_second_glyph)
{
    /* Mirror of font.c's internal FontVertex (32-byte stride, x first). */
    typedef struct { f32 x, y, u, v, r, g, b, a; } TestFontVertex;
    FontRenderer fr;
    make_kern_fr(&fr);
    TestFontVertex quad_buf[6 * 2];
    fr.quad_data = (u8 *)quad_buf;
    fr.quad_capacity = 2;
    fr.quad_count = 0;

    font_renderer_draw(&fr, "AV", 0.0f, 0.0f, 100.0f, 100.0f,
                       1.0f, 1.0f, 1.0f, 1.0f);
    ASSERT_EQ(fr.quad_count, 2u);
    /* Second glyph's left edge (NDC): x_cursor = adv(A) + kern(A,V) + x_off(V)
     * with x_off(V) = 0 -> (10 - 2) * (2/100) - 1 = -0.84 */
    const TestFontVertex *v1 = &quad_buf[6];
    ASSERT_FLOAT_EQ(v1[0].x, -0.84f, 1e-4f);
}

TEST_MAIN_BEGIN()
    RUN_TEST(font_init_rejects_missing_file);
    RUN_TEST(font_init_rejects_empty_file);
    RUN_TEST(font_init_rejects_file_below_offset_table);
    RUN_TEST(font_init_rejects_non_font_file);
    RUN_TEST(font_init_rejects_oversized_file);
    RUN_TEST(font_kern_lookup_hit);
    RUN_TEST(font_kern_lookup_miss);
    RUN_TEST(font_kern_width_applies_pair);
    RUN_TEST(font_kern_width_empty_table_unchanged);
    RUN_TEST(font_kern_width_not_across_newline);
    RUN_TEST(font_kern_width_unknown_cp_falls_back_for_pair);
    RUN_TEST(font_kern_draw_offsets_second_glyph);
TEST_MAIN_END()
