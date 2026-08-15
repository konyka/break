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
/* R442: declarations only — font.c carries STB_TRUETYPE_IMPLEMENTATION and
 * this target links against it. Used as the kern-table oracle for the GPOS
 * cross-validation. */
#include <stb_truetype.h>
#include <stdio.h>
#include <string.h>

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

/* R444: per-pid path — parallel ctest trees raced on the fixed name.
 * Function-backed macro keeps every use site unchanged (static buffer). */
static const char *font_tmp_path(void)
{
    static char b[128];
    return test_tmp(b, sizeof b, "test_font_load.bin");
}
#define TMP_FONT font_tmp_path()

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

/* ---- R439: SDF coverage mapping ------------------------------------------
 *
 * The bake switched from coverage bitmaps to stbtt_GetCodepointSDF; the
 * fragment shader maps the sampled distance to alpha with a smoothstep whose
 * transition width comes from fwidth. font_sdf_coverage() is the C mirror of
 * that mapping (font.h keeps them in lockstep) so the semantics are testable
 * headlessly. A plain threshold (step) implementation fails
 * font_sdf_coverage_smooth_transition — that is the regression tripwire for
 * "someone reverted the SDF path to bitmap sampling". */

TEST(font_sdf_coverage_endpoints)
{
    /* far outside / far inside saturate regardless of smoothing width */
    ASSERT_FLOAT_EQ(font_sdf_coverage(0.0f, 0.05f), 0.0f, 1e-6f);
    ASSERT_FLOAT_EQ(font_sdf_coverage(1.0f, 0.05f), 1.0f, 1e-6f);
    /* the on-edge value maps to half coverage */
    ASSERT_FLOAT_EQ(font_sdf_coverage(FONT_SDF_EDGE, 0.05f), 0.5f, 1e-6f);
}

TEST(font_sdf_coverage_smooth_transition)
{
    /* half a smoothing width below the edge a step() gives exactly 0; the SDF
     * mapping must be strictly inside (0, 1) — that is what makes edges
     * antialiased instead of binary. */
    f32 a = font_sdf_coverage(FONT_SDF_EDGE - 0.025f, 0.05f);
    ASSERT_TRUE(a > 0.0f && a < 1.0f);
    /* monotonic across the edge */
    ASSERT_TRUE(font_sdf_coverage(0.48f, 0.05f) < font_sdf_coverage(0.52f, 0.05f));
}

TEST(font_sdf_coverage_zero_smoothing_degenerates_to_step)
{
    /* smoothing == 0 must not divide by zero; it collapses to a hard edge
     * (white patch / constant regions where fwidth is 0 hit this path in the
     * shader, which clamps the width instead). */
    ASSERT_FLOAT_EQ(font_sdf_coverage(0.0f, 0.0f), 0.0f, 1e-6f);
    ASSERT_FLOAT_EQ(font_sdf_coverage(1.0f, 0.0f), 1.0f, 1e-6f);
}

/* ---- R439: shader contract ------------------------------------------------
 *
 * The CPU cannot assert rendered pixels headlessly, but it can assert that
 * both backend font fragment shaders actually implement the SDF sampling
 * path. Reverting either shader to plain alpha sampling (step at 0.5) turns
 * this test red. Shader files are located relative to this source file so
 * the test is independent of the ctest working directory. */

static bool read_shader_source(const char *name, char *buf, usize cap) {
    const char *candidates[3];
    char rel[1024];
    const char *slash = strrchr(__FILE__, '/');
    if (slash) {
        snprintf(rel, sizeof(rel), "%.*s/../shaders/%s",
                 (int)(slash - __FILE__), __FILE__, name);
        candidates[0] = rel;
        candidates[1] = NULL;
    } else {
        candidates[0] = NULL;
    }
    candidates[1] = name; /* last-resort: bare name in cwd */
    candidates[2] = NULL;
    for (usize i = 0; i < 2 && candidates[i]; i++) {
        FILE *f = fopen(candidates[i], "rb");
        if (!f) continue;
        usize n = fread(buf, 1, cap - 1, f);
        fclose(f);
        buf[n] = '\0';
        if (n > 0) return true;
    }
    return false;
}

/* R439: strip block and line comments in place so keyword scans below match
 * code, not prose — the shader's own R439 comment mentions smoothstep/fwidth
 * and defeated a naive strstr during reverse verification. */
static void strip_glsl_comments(char *s) {
    for (char *p = s; *p;) {
        if (p[0] == '/' && p[1] == '/') {
            while (*p && *p != '\n') *p++ = ' ';
        } else if (p[0] == '/' && p[1] == '*') {
            *p++ = ' '; *p++ = ' ';
            while (*p && !(p[0] == '*' && p[1] == '/')) *p++ = ' ';
            if (*p) { *p++ = ' '; *p++ = ' '; }
        } else {
            p++;
        }
    }
}

TEST(font_shaders_use_sdf_sampling)
{
    const char *frags[] = { "font.frag", "font_vk.frag" };
    for (usize i = 0; i < sizeof(frags) / sizeof(frags[0]); i++) {
        char src[4096];
        ASSERT_TRUE(read_shader_source(frags[i], src, sizeof(src)));
        strip_glsl_comments(src);
        /* smoothstep( = antialiased threshold call; fwidth( = screen-space
         * transition width. Plain bitmap sampling calls neither. */
        ASSERT_NOT_NULL(strstr(src, "smoothstep("));
        ASSERT_NOT_NULL(strstr(src, "fwidth("));
    }
}

/* ---- R442: GPOS kerning ----------------------------------------------------
 *
 * stb_truetype only reads the legacy 'kern' table (format 0); GPOS-only fonts
 * bake an empty pair table. font_gpos_kern_extract() is the pure byte-level
 * GPOS PairPos extractor that closes that gap. LiberationSans carries BOTH a
 * kern table and a GPOS table, and recon (R442) showed the two agree exactly
 * on all 908 kern-table pairs — so the shipped font is its own oracle: the
 * GPOS parse is cross-validated pair-by-pair against stbtt's kern-table
 * results below. Both values are unscaled font units, so equality is exact
 * (no tolerance); if a future font swap breaks exact agreement the tolerance
 * debate can happen then, with data.
 *
 * The ttf is located relative to this source file, like the R439 shader
 * contract test, so ctest working directory does not matter. */

static u8 *read_asset_ttf(usize *out_size) {
    const char *candidates[3];
    char rel[1024];
    const char *slash = strrchr(__FILE__, '/');
    if (slash) {
        snprintf(rel, sizeof(rel), "%.*s/../assets/LiberationSans-Regular.ttf",
                 (int)(slash - __FILE__), __FILE__);
        candidates[0] = rel;
        candidates[1] = NULL;
    } else {
        candidates[0] = NULL;
    }
    candidates[1] = "assets/LiberationSans-Regular.ttf"; /* cwd = engine/ */
    candidates[2] = NULL;
    for (usize i = 0; i < 2 && candidates[i]; i++) {
        FILE *f = fopen(candidates[i], "rb");
        if (!f) continue;
        if (fseek(f, 0, SEEK_END) != 0) { fclose(f); continue; }
        long sz = ftell(f);
        if (sz <= 0 || fseek(f, 0, SEEK_SET) != 0) { fclose(f); continue; }
        u8 *buf = malloc((usize)sz);
        if (!buf) { fclose(f); continue; }
        bool ok = fread(buf, 1, (usize)sz, f) == (usize)sz;
        fclose(f);
        if (!ok) { free(buf); continue; }
        *out_size = (usize)sz;
        return buf;
    }
    return NULL;
}

/* GPOS table location within a well-formed sfnt directory (test-local copy of
 * the directory walk; the parser under test does its own). */
static bool find_gpos_table(const u8 *d, usize n, usize *off, usize *len) {
    if (n < 12) return false;
    u32 num = ((u32)d[4] << 8) | d[5];
    if (12 + (usize)num * 16 > n) return false;
    for (u32 i = 0; i < num; i++) {
        const u8 *r = d + 12 + (usize)i * 16;
        if (r[0] == 'G' && r[1] == 'P' && r[2] == 'O' && r[3] == 'S') {
            *off = ((usize)r[8] << 24) | ((usize)r[9] << 16) | ((usize)r[10] << 8) | r[11];
            *len = ((usize)r[12] << 24) | ((usize)r[13] << 16) | ((usize)r[14] << 8) | r[15];
            return *off <= n && *len <= n - *off;
        }
    }
    return false;
}

#define TEST_GPOS_CAP 4096

static int gpos_kern_cmp(const void *pa, const void *pb) {
    const FontGposKern *a = pa, *b = pb;
    u32 ka = ((u32)a->glyph_a << 16) | a->glyph_b;
    u32 kb = ((u32)b->glyph_a << 16) | b->glyph_b;
    return ka < kb ? -1 : ka > kb ? 1 : 0;
}

/* x_advance for (ga, gb) in a sorted extract result, 0 when absent. */
static i32 gpos_lookup(const FontGposKern *pairs, u32 count, u16 ga, u16 gb) {
    FontGposKern key = { ga, gb, 0 };
    const FontGposKern *hit = bsearch(&key, pairs, count, sizeof(*pairs), gpos_kern_cmp);
    return hit ? hit->x_advance : 0;
}

TEST(font_gpos_extract_finds_known_pair)
{
    usize sz = 0;
    u8 *ttf = read_asset_ttf(&sz);
    ASSERT_NOT_NULL(ttf);

    FontGposKern *pairs = malloc(sizeof(FontGposKern) * TEST_GPOS_CAP);
    ASSERT_NOT_NULL(pairs);
    u32 count = font_gpos_kern_extract(ttf, sz, pairs, TEST_GPOS_CAP, NULL);
    /* R442 recon: 2015 non-zero GPOS pairs total (908 Latin + 1107 Hebrew). */
    ASSERT_TRUE(count > 0);
    ASSERT_TRUE(count <= TEST_GPOS_CAP);

    /* Known value: R436 measured A->V = -152 font units in the kern table;
     * recon showed GPOS carries the identical value. */
    stbtt_fontinfo fi;
    ASSERT_TRUE(stbtt_InitFont(&fi, ttf, stbtt_GetFontOffsetForIndex(ttf, 0)) != 0);
    u16 ga = (u16)stbtt_FindGlyphIndex(&fi, 'A');
    u16 gv = (u16)stbtt_FindGlyphIndex(&fi, 'V');
    qsort(pairs, count, sizeof(*pairs), gpos_kern_cmp);
    ASSERT_EQ(gpos_lookup(pairs, count, ga, gv), -152);

    free(pairs);
    free(ttf);
}

TEST(font_gpos_cross_validates_kern_table)
{
    usize sz = 0;
    u8 *ttf = read_asset_ttf(&sz);
    ASSERT_NOT_NULL(ttf);
    stbtt_fontinfo fi;
    ASSERT_TRUE(stbtt_InitFont(&fi, ttf, stbtt_GetFontOffsetForIndex(ttf, 0)) != 0);

    FontGposKern *pairs = malloc(sizeof(FontGposKern) * TEST_GPOS_CAP);
    ASSERT_NOT_NULL(pairs);
    u32 count = font_gpos_kern_extract(ttf, sz, pairs, TEST_GPOS_CAP, NULL);
    ASSERT_TRUE(count > 0);
    qsort(pairs, count, sizeof(*pairs), gpos_kern_cmp);

    /* Every baked-range codepoint pair: the kern-table value (via stbtt) and
     * the GPOS value must agree exactly — both are unscaled font units and
     * LiberationSans ships the same kerning in both tables (R442 recon:
     * 908/908 match, 0 mismatch, the 1107 GPOS-only pairs are Hebrew glyphs
     * outside these ranges). */
    const u32 ranges[2][2] = { { 0x20, 0x7E }, { 0xA0, 0xFF } };
    u32 compared = 0;
    for (u32 ri = 0; ri < 2; ri++) {
        for (u32 a = ranges[ri][0]; a <= ranges[ri][1]; a++) {
            int ga = stbtt_FindGlyphIndex(&fi, (int)a);
            if (ga <= 0) continue;
            for (u32 b = ranges[ri][0]; b <= ranges[ri][1]; b++) {
                int gb = stbtt_FindGlyphIndex(&fi, (int)b);
                if (gb <= 0) continue;
                i32 k = stbtt_GetCodepointKernAdvance(&fi, (int)a, (int)b);
                i32 g = gpos_lookup(pairs, count, (u16)ga, (u16)gb);
                if (k != g) {
                    printf("  FAIL: %s:%d: pair U+%04X/U+%04X kern=%d gpos=%d\n",
                           __FILE__, __LINE__, a, b, (int)k, (int)g);
                    g_test_fail++;
                    free(pairs); free(ttf);
                    return;
                }
                if (k != 0) compared++;
            }
        }
    }
    /* Sanity: the cross-check must actually exercise a meaningful number of
     * pairs, not vacuously pass on an empty intersection (96 in baked ranges
     * per R436; leave margin for font updates). */
    ASSERT_TRUE(compared >= 64);

    free(pairs);
    free(ttf);
}

/* Defense: a well-formed sfnt directory without a GPOS table yields 0 pairs. */
TEST(font_gpos_no_gpos_table_returns_zero)
{
    u8 fake[12 + 16];
    memset(fake, 0, sizeof(fake));
    fake[0] = 0x00; fake[1] = 0x01; fake[2] = 0x00; fake[3] = 0x00; /* sfnt v1 */
    fake[5] = 1;                                                    /* 1 table */
    memcpy(fake + 12, "cmap", 4);
    FontGposKern out[4];
    ASSERT_EQ(font_gpos_kern_extract(fake, sizeof(fake), out, 4, NULL), 0u);
}

/* Defense: corrupted directory fields must degrade to 0, never to a wild
 * read. (a) numTables far beyond the buffer; (b) GPOS length far beyond EOF. */
TEST(font_gpos_corrupt_directory_returns_zero)
{
    usize sz = 0;
    u8 *ttf = read_asset_ttf(&sz);
    ASSERT_NOT_NULL(ttf);

    ttf[5] = 0xFF; /* numTables = 255+ with a ~400KB file: 12+255*16 < sz,
                    * so also push it to the u16 max to blow past EOF */
    ttf[4] = 0xFF;
    FontGposKern out[4];
    ASSERT_EQ(font_gpos_kern_extract(ttf, sz, out, 4, NULL), 0u);
    free(ttf);

    ttf = read_asset_ttf(&sz);
    ASSERT_NOT_NULL(ttf);
    usize goff = 0, glen = 0;
    ASSERT_TRUE(find_gpos_table(ttf, sz, &goff, &glen));
    /* rewrite the GPOS directory length to 0xFFFFFFFF */
    u32 num = ((u32)ttf[4] << 8) | ttf[5];
    for (u32 i = 0; i < num; i++) {
        u8 *r = ttf + 12 + (usize)i * 16;
        if (memcmp(r, "GPOS", 4) == 0) { r[12] = r[13] = r[14] = r[15] = 0xFF; }
    }
    ASSERT_EQ(font_gpos_kern_extract(ttf, sz, out, 4, NULL), 0u);
    free(ttf);
}

/* Defense: truncating the real font at any point — inside the directory,
 * inside the GPOS header, mid-PairSet — must never read out of bounds.
 * The assertion is trivially weak on purpose; ASan is the real judge. */
TEST(font_gpos_truncated_never_crashes)
{
    usize sz = 0;
    u8 *ttf = read_asset_ttf(&sz);
    ASSERT_NOT_NULL(ttf);
    usize goff = 0, glen = 0;
    ASSERT_TRUE(find_gpos_table(ttf, sz, &goff, &glen));

    FontGposKern out[64];
    const usize cuts[] = {
        0, 1, 11, 12, 13, 64, 256, 4096,
        334020,              /* GPOS table start (dir entry stays) */
        334020 + 10,         /* just past the GPOS header */
        334020 + 300,        /* inside ScriptList/FeatureList */
        334020 + 2000,       /* inside lookup/pairset data */
        334036, 335020, 340020,
        410663,              /* GPOS end - 1 (mid-pair data) */
    };
    for (usize i = 0; i < sizeof(cuts) / sizeof(cuts[0]); i++) {
        usize n = cuts[i] < sz ? cuts[i] : sz;
        (void)font_gpos_kern_extract(ttf, n, out, 64, NULL);
    }
    ASSERT_TRUE(true);
    free(ttf);
}

/* Defense: GPOS payload turned into garbage (counts and offsets all 0xFF)
 * with the directory intact — every internal offset is now maximal. */
TEST(font_gpos_garbage_payload_never_crashes)
{
    usize sz = 0;
    u8 *ttf = read_asset_ttf(&sz);
    ASSERT_NOT_NULL(ttf);
    usize goff = 0, glen = 0;
    ASSERT_TRUE(find_gpos_table(ttf, sz, &goff, &glen));
    memset(ttf + goff, 0xFF, glen);

    FontGposKern out[64];
    u32 n = font_gpos_kern_extract(ttf, sz, out, 64, NULL);
    ASSERT_TRUE(n <= 64); /* capacity respected; value otherwise arbitrary */
    free(ttf);
}

/* ---- R443: GPOS PairPos Format 2 (class-based) -----------------------------
 *
 * No shipped/real font at hand kerns exclusively through class-based PairPos
 * (LiberationSans is all Format 1), so the Format-2 oracle is synthetic: a
 * minimal but spec-shaped sfnt + GPOS table is assembled byte-by-byte below.
 * Every builder field is annotated with its OpenType-spec meaning. Layout:
 *
 *   sfnt offset table (1 table) -> TableRecord 'GPOS'
 *   GPOS header v1.0 -> ScriptList(DFLT -> default LangSys -> feature 0)
 *                    -> FeatureList('kern' -> lookup 0)
 *                    -> LookupList(lookup 0, type 2 PairPos, N subtables)
 *   PairPos Format 2 subtable: coverage {glyph 10},
 *     classDef1 (format 1): glyph 10 -> class 1
 *     classDef2 (format 2): glyphs 20..21 -> class 1
 *     class1Count = class2Count = 2, matrix[1][1].XAdvance = -80
 *   Optionally a leading Format 1 subtable: coverage {glyph 5},
 *     pair set (5,6) -> XAdvance -40 (mixed-format coexistence test). */

typedef struct {
    u8    data[2048];
    usize len;
    usize off_gpos; /* GPOS table start (absolute)              */
    usize off_fmt2; /* PairPos Format 2 subtable start (absolute) */
    usize off_cd1;  /* classDef1 table start (absolute)           */
} SynthFont;

static void sf_put(SynthFont *b, u8 v) { b->data[b->len++] = v; }
static void sf_u16(SynthFont *b, u16 v) { /* big-endian, like the sfnt spec */
    sf_put(b, (u8)(v >> 8)); sf_put(b, (u8)v);
}
static void sf_u32(SynthFont *b, u32 v) { sf_u16(b, (u16)(v >> 16)); sf_u16(b, (u16)v); }
static void sf_tag(SynthFont *b, const char t[4]) {
    for (int i = 0; i < 4; i++) sf_put(b, (u8)t[i]);
}
static void sf_patch_u16(SynthFont *b, usize at, u16 v) {
    b->data[at] = (u8)(v >> 8); b->data[at + 1] = (u8)v;
}
static void sf_patch_u32(SynthFont *b, usize at, u32 v) {
    sf_patch_u16(b, at, (u16)(v >> 16)); sf_patch_u16(b, at + 2, (u16)v);
}

/* m10: XAdvance of matrix cell [class 1][class 0] (the class-0 column is only
 * enumerable through the glyph filter — see the filter test). */
static void build_synth_gpos_fmt2(SynthFont *b, bool with_fmt1, i16 m10) {
    memset(b, 0, sizeof(*b));
    /* sfnt offset table (spec: "Offset Table") */
    sf_u32(b, 0x00010000);      /* sfntVersion = TrueType outlines */
    sf_u16(b, 1);               /* numTables */
    sf_u16(b, 16);              /* searchRange */
    sf_u16(b, 0);               /* entrySelector */
    sf_u16(b, 0);               /* rangeShift */
    /* single TableRecord */
    sf_tag(b, "GPOS");
    sf_u32(b, 0);               /* checksum (parser ignores it) */
    usize dir_off = b->len; sf_u32(b, 0);  /* table offset -> patched below */
    usize dir_len = b->len; sf_u32(b, 0);  /* table length -> patched below */
    b->off_gpos = b->len;
    const usize gpos = b->off_gpos;
    sf_patch_u32(b, dir_off, (u32)gpos);

    /* GPOS header v1.0: version, scriptList/featureList/lookupList offsets
     * (all offsets from here on are relative to the GPOS table start). */
    sf_u32(b, 0x00010000);
    usize off_script  = b->len; sf_u16(b, 0);
    usize off_feature = b->len; sf_u16(b, 0);
    usize off_lookup  = b->len; sf_u16(b, 0);

    /* ScriptList: one 'DFLT' script whose default LangSys references feature
     * index 0. (The extractor gathers 'kern' features from the FeatureList
     * directly and never walks this, but a spec-shaped ScriptList keeps the
     * oracle honest for any future script-aware parsing.) */
    sf_patch_u16(b, off_script, (u16)(b->len - gpos));
    sf_u16(b, 1);               /* scriptCount */
    sf_tag(b, "DFLT");
    sf_u16(b, 8);               /* Script offset: past count + one 6-byte record */
    /* Script table */
    sf_u16(b, 4);               /* defaultLangSysOffset: past this field + langSysCount */
    sf_u16(b, 0);               /* langSysCount */
    /* LangSys table */
    sf_u16(b, 0);               /* lookupOrder offset (NULL) */
    sf_u16(b, 0xFFFF);          /* reqFeatureIndex (none required) */
    sf_u16(b, 1);               /* featureIndexCount */
    sf_u16(b, 0);               /* featureIndex[0] -> FeatureList[0] ('kern') */

    /* FeatureList: one 'kern' feature referencing lookup 0. */
    sf_patch_u16(b, off_feature, (u16)(b->len - gpos));
    sf_u16(b, 1);               /* featureCount */
    sf_tag(b, "kern");
    sf_u16(b, 8);               /* Feature offset: past count + one 6-byte record */
    /* Feature table */
    sf_u16(b, 0);               /* featureParams (NULL) */
    sf_u16(b, 1);               /* lookupIndexCount */
    sf_u16(b, 0);               /* lookupListIndex[0] */

    /* LookupList: one lookup, type 2 = Pair Adjustment Positioning. */
    sf_patch_u16(b, off_lookup, (u16)(b->len - gpos));
    const usize ll = b->len;
    sf_u16(b, 1);               /* lookupCount */
    sf_u16(b, 4);               /* lookupOffset[0]: past count + one offset */
    const usize lookup = ll + 4;
    /* Lookup table (subtable offsets are relative to `lookup`) */
    sf_u16(b, 2);               /* lookupType = PairPos */
    sf_u16(b, 0);               /* lookupFlag */
    sf_u16(b, with_fmt1 ? 2 : 1); /* subTableCount */
    usize sub_off0 = b->len; sf_u16(b, 0);
    usize sub_off1 = 0;
    if (with_fmt1) { sub_off1 = b->len; sf_u16(b, 0); }

    if (with_fmt1) {
        /* PairPos Format 1: coverage {glyph 5}, one pair (5, 6) -> -40. */
        sf_patch_u16(b, sub_off0, (u16)(b->len - lookup));
        const usize st1 = b->len;
        sf_u16(b, 1);           /* posFormat = 1 */
        usize c1o = b->len; sf_u16(b, 0);   /* coverageOffset */
        sf_u16(b, 0x0004);      /* valueFormat1 = XAdvance */
        sf_u16(b, 0);           /* valueFormat2 */
        sf_u16(b, 1);           /* pairSetCount */
        usize pso = b->len; sf_u16(b, 0);   /* pairSetOffset[0] */
        sf_patch_u16(b, c1o, (u16)(b->len - st1));
        sf_u16(b, 1);           /* coverage format 1 (glyph array) */
        sf_u16(b, 1);           /* glyphCount */
        sf_u16(b, 5);           /* glyph 5 */
        sf_patch_u16(b, pso, (u16)(b->len - st1));
        sf_u16(b, 1);           /* pairValueCount */
        sf_u16(b, 6);           /* secondGlyph */
        sf_u16(b, (u16)-40);    /* valueRecord1.XAdvance */
    }

    /* PairPos Format 2 (spec: "Pair Adjustment Positioning Format 2:
     * Class Pair Adjustment"). valueFormat1 = XAdvance only, so each
     * Class2Record is exactly one 2-byte valueRecord1. */
    sf_patch_u16(b, with_fmt1 ? sub_off1 : sub_off0, (u16)(b->len - lookup));
    b->off_fmt2 = b->len;
    const usize st2 = b->off_fmt2;
    sf_u16(b, 2);               /* posFormat = 2 */
    usize cov  = b->len; sf_u16(b, 0);  /* coverageOffset */
    sf_u16(b, 0x0004);          /* valueFormat1 = XAdvance */
    sf_u16(b, 0);               /* valueFormat2 */
    usize cd1o = b->len; sf_u16(b, 0);  /* classDef1Offset */
    usize cd2o = b->len; sf_u16(b, 0);  /* classDef2Offset */
    sf_u16(b, 2);               /* class1Count */
    sf_u16(b, 2);               /* class2Count */
    /* class1Record matrix [class1][class2], one u16 XAdvance per cell */
    sf_u16(b, 0);               /* [0][0] */
    sf_u16(b, 0);               /* [0][1] */
    sf_u16(b, (u16)m10);        /* [1][0] — class-0 column of classDef2 */
    sf_u16(b, (u16)-80);        /* [1][1] — the pair under test */
    /* Coverage: glyph 10 (the only first glyph getting adjusted). */
    sf_patch_u16(b, cov, (u16)(b->len - st2));
    sf_u16(b, 1);               /* coverage format 1 */
    sf_u16(b, 1);               /* glyphCount */
    sf_u16(b, 10);
    /* ClassDef1 format 1: glyph 10 -> class 1. */
    sf_patch_u16(b, cd1o, (u16)(b->len - st2));
    b->off_cd1 = b->len;
    sf_u16(b, 1);               /* classDef format 1 (startGlyph + array) */
    sf_u16(b, 10);              /* startGlyphID */
    sf_u16(b, 1);               /* glyphCount */
    sf_u16(b, 1);               /* classValueArray[0] */
    /* ClassDef2 format 2: glyphs 20..21 -> class 1. */
    sf_patch_u16(b, cd2o, (u16)(b->len - st2));
    sf_u16(b, 2);               /* classDef format 2 (range records) */
    sf_u16(b, 1);               /* classRangeCount */
    sf_u16(b, 20);              /* range[0].startGlyphID */
    sf_u16(b, 21);              /* range[0].endGlyphID */
    sf_u16(b, 1);               /* range[0].class */

    sf_patch_u32(b, dir_len, (u32)(b->len - gpos));
}

/* Oracle: the synthetic Format-2-only font must yield exactly the two class
 * pairs (10,20,-80) and (10,21,-80). */
TEST(font_gpos_fmt2_synthetic_extracts_class_pairs)
{
    SynthFont b;
    build_synth_gpos_fmt2(&b, false, 0);
    FontGposKern out[8];
    u32 count = font_gpos_kern_extract(b.data, b.len, out, 8, NULL);
    ASSERT_EQ(count, 2u);
    qsort(out, count, sizeof(*out), gpos_kern_cmp);
    ASSERT_EQ(gpos_lookup(out, count, 10, 20), -80);
    ASSERT_EQ(gpos_lookup(out, count, 10, 21), -80);
}

/* The glyph filter (bitmap of wanted glyph ids, e.g. the baked set) bounds
 * the class-matrix expansion — and makes classDef2's class 0 enumerable at
 * all: without a filter "every other glyph" is unbounded and stays skipped. */
TEST(font_gpos_fmt2_glyph_filter_limits_expansion)
{
    SynthFont b;
    build_synth_gpos_fmt2(&b, false, -50); /* live class-0 column */
    u8 filter[8192]; /* 65536 glyphs / 8 */
    memset(filter, 0, sizeof(filter));
    /* stand-in baked set: glyphs 10, 21, 30 (20 deliberately absent) */
    filter[10 >> 3] |= (u8)(1u << (10 & 7));
    filter[21 >> 3] |= (u8)(1u << (21 & 7));
    filter[30 >> 3] |= (u8)(1u << (30 & 7));

    FontGposKern out[8];
    u32 count = font_gpos_kern_extract(b.data, b.len, out, 8, filter);
    /* (10,20) filtered out; (10,21) via class 1; (10,10) and (10,30) via the
     * class-0 column because both are filtered-in and classDef2 never
     * mentions them (the filter applies to both sides uniformly). */
    ASSERT_EQ(count, 3u);
    qsort(out, count, sizeof(*out), gpos_kern_cmp);
    ASSERT_EQ(gpos_lookup(out, count, 10, 21), -80);
    ASSERT_EQ(gpos_lookup(out, count, 10, 30), -50);
    ASSERT_EQ(gpos_lookup(out, count, 10, 10), -50);

    /* No filter: class 0 is unenumerable, only the explicit class-1 pairs. */
    count = font_gpos_kern_extract(b.data, b.len, out, 8, NULL);
    ASSERT_EQ(count, 2u);
    qsort(out, count, sizeof(*out), gpos_kern_cmp);
    ASSERT_EQ(gpos_lookup(out, count, 10, 20), -80);
    ASSERT_EQ(gpos_lookup(out, count, 10, 21), -80);
    ASSERT_EQ(gpos_lookup(out, count, 10, 30), 0);
}

/* Format 1 and Format 2 subtables under one lookup must both be harvested. */
TEST(font_gpos_fmt1_fmt2_mixed_lookup_coexist)
{
    SynthFont b;
    build_synth_gpos_fmt2(&b, true, 0);
    FontGposKern out[8];
    u32 count = font_gpos_kern_extract(b.data, b.len, out, 8, NULL);
    ASSERT_EQ(count, 3u);
    qsort(out, count, sizeof(*out), gpos_kern_cmp);
    ASSERT_EQ(gpos_lookup(out, count, 5, 6), -40);
    ASSERT_EQ(gpos_lookup(out, count, 10, 20), -80);
    ASSERT_EQ(gpos_lookup(out, count, 10, 21), -80);
}

/* Defense: a classDef offset pointing outside the GPOS table must degrade to
 * 0 pairs, never to a wild read. classDef2Offset lives at fmt2 + 10. */
TEST(font_gpos_fmt2_classdef_out_of_bounds)
{
    SynthFont b;
    build_synth_gpos_fmt2(&b, false, 0);
    sf_patch_u16(&b, b.off_fmt2 + 10, 0x7FF0);
    FontGposKern out[8];
    ASSERT_EQ(font_gpos_kern_extract(b.data, b.len, out, 8, NULL), 0u);
}

/* Defense: an absurd class1Count makes the declared class1Record matrix run
 * past the table end; the size check must reject the subtable wholesale. */
TEST(font_gpos_fmt2_matrix_count_overflow)
{
    SynthFont b;
    build_synth_gpos_fmt2(&b, false, 0);
    sf_patch_u16(&b, b.off_fmt2 + 12, 0xFFFF); /* class1Count */
    FontGposKern out[8];
    ASSERT_EQ(font_gpos_kern_extract(b.data, b.len, out, 8, NULL), 0u);
}

/* Defense: a classDef1 class beyond class1Count has no matrix row; the glyph
 * must be skipped (no out-of-bounds matrix read, 0 pairs). */
TEST(font_gpos_fmt2_class_beyond_matrix_skipped)
{
    SynthFont b;
    build_synth_gpos_fmt2(&b, false, 0);
    sf_patch_u16(&b, b.off_cd1 + 6, 5); /* glyph 10 -> class 5 (matrix has 2) */
    FontGposKern out[8];
    ASSERT_EQ(font_gpos_kern_extract(b.data, b.len, out, 8, NULL), 0u);
}

/* Defense: cutting the synthetic font at EVERY byte length — mid-matrix,
 * mid-classDef, mid-directory — must never read out of bounds. ASan judges. */
TEST(font_gpos_fmt2_truncated_never_crashes)
{
    SynthFont b;
    build_synth_gpos_fmt2(&b, true, -50);
    u8 filter[8192];
    memset(filter, 0xFF, sizeof(filter)); /* worst case: everything wanted */
    FontGposKern out[8];
    for (usize n = 0; n <= b.len; n++) {
        (void)font_gpos_kern_extract(b.data, n, out, 8, NULL);
        (void)font_gpos_kern_extract(b.data, n, out, 8, filter);
    }
    ASSERT_TRUE(true);
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
    RUN_TEST(font_sdf_coverage_endpoints);
    RUN_TEST(font_sdf_coverage_smooth_transition);
    RUN_TEST(font_sdf_coverage_zero_smoothing_degenerates_to_step);
    RUN_TEST(font_shaders_use_sdf_sampling);
    RUN_TEST(font_gpos_extract_finds_known_pair);
    RUN_TEST(font_gpos_cross_validates_kern_table);
    RUN_TEST(font_gpos_no_gpos_table_returns_zero);
    RUN_TEST(font_gpos_corrupt_directory_returns_zero);
    RUN_TEST(font_gpos_truncated_never_crashes);
    RUN_TEST(font_gpos_garbage_payload_never_crashes);
    RUN_TEST(font_gpos_fmt2_synthetic_extracts_class_pairs);
    RUN_TEST(font_gpos_fmt2_glyph_filter_limits_expansion);
    RUN_TEST(font_gpos_fmt1_fmt2_mixed_lookup_coexist);
    RUN_TEST(font_gpos_fmt2_classdef_out_of_bounds);
    RUN_TEST(font_gpos_fmt2_matrix_count_overflow);
    RUN_TEST(font_gpos_fmt2_class_beyond_matrix_skipped);
    RUN_TEST(font_gpos_fmt2_truncated_never_crashes);
TEST_MAIN_END()
