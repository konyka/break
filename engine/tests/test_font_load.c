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

TEST_MAIN_BEGIN()
    RUN_TEST(font_init_rejects_missing_file);
    RUN_TEST(font_init_rejects_empty_file);
    RUN_TEST(font_init_rejects_file_below_offset_table);
    RUN_TEST(font_init_rejects_non_font_file);
    RUN_TEST(font_init_rejects_oversized_file);
TEST_MAIN_END()
