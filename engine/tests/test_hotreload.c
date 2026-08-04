#include "test_framework.h"
#include <asset/hotreload.h>
#include <core/shader_io.h>
#include <stdio.h>
#include <string.h>

static RHIShader  s_shader  = {1, 1};
static RHIPipeline s_pipe   = {1, 1};
static RHITexture s_tex     = {1, 1};

RHIShader rhi_shader_create(RHIDevice *dev, const char *src, usize len, bool is_frag) {
    (void)dev; (void)src; (void)len; (void)is_frag;
    return s_shader;
}
void rhi_shader_destroy(RHIDevice *dev, RHIShader sh) { (void)dev; (void)sh; }
RHIPipeline rhi_pipeline_create(RHIDevice *dev, const RHIPipelineDesc *desc) {
    (void)dev; (void)desc;
    return s_pipe;
}
void rhi_pipeline_destroy(RHIDevice *dev, RHIPipeline p) { (void)dev; (void)p; }
RHITexture rhi_texture_create(RHIDevice *dev, const RHITextureDesc *desc) {
    (void)dev; (void)desc;
    return s_tex;
}
void rhi_texture_destroy(RHIDevice *dev, RHITexture t) { (void)dev; (void)t; }

static bool write_file(const char *path, long size, char fill) {
    FILE *f = fopen(path, "wb");
    if (!f) return false;
    for (long i = 0; i < size; i++) fputc(fill, f);
    fclose(f);
    return true;
}

/* R393: read_file had no size cap — multi-GB shader path could malloc before compile. */
TEST(hotreload_rejects_oversized_shader)
{
    /* R444: per-pid paths — parallel ctest trees raced on the fixed names. */
    char TMP_VERT[64], TMP_FRAG[64];
    test_tmp(TMP_VERT, sizeof TMP_VERT, "test_hotreload.vert");
    test_tmp(TMP_FRAG, sizeof TMP_FRAG, "test_hotreload.frag");

    ASSERT_TRUE(write_file(TMP_VERT, (long)SHADER_MAX_FILE_BYTES + 1, 'x'));
    ASSERT_TRUE(write_file(TMP_FRAG, 16, '#'));

    HotReloadPipeline hr;
    ASSERT_TRUE(!hotreload_pipeline_init(&hr, NULL, TMP_VERT, TMP_FRAG, NULL));
    remove(TMP_VERT);
    remove(TMP_FRAG);
}

TEST_MAIN_BEGIN()
    RUN_TEST(hotreload_rejects_oversized_shader);
TEST_MAIN_END()
