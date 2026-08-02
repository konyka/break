/* ==========================================================================
 *  test_ibl.c — Logic-level tests for the IBL precomputation chain (R434).
 *
 *  Drives ibl_capture_env_sky / ibl_generate through a lightweight fake RHI
 *  backend and asserts:
 *    - with a usable command handle (VK-like, and GL after the R434 sentinel
 *      fix) all three bake stages actually dispatch — no `if (!cmd) break;`
 *      early-out;
 *    - with a NULL command handle (the old GL behaviour) the degradation is
 *      explicit: a warning is logged and ibl_generate does not report ready,
 *      instead of silently leaving the environment maps black.
 *
 *  No real GL/VK context is required; every RHI entry point used by ibl.c is
 *  stubbed locally with call counters.
 * ========================================================================== */

#include "test_framework.h"
#include <renderer/ibl.h>
#include <core/log.h>
#include <core/shader_io.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

/* ---- Fake backend state ------------------------------------------------- */

static int  g_frame_begin_returns_null; /* 1 mimics the pre-R434 GL backend */
static int  g_cmd_sentinel;             /* non-NULL handle, GL ignores it   */

static unsigned g_frame_begin_calls;
static unsigned g_dispatch_calls;
static unsigned g_cube_transition_calls;
static unsigned g_tex_transition_calls;

static unsigned g_warn_count;
static char     g_last_warn[256];

static void fake_reset(void) {
    g_frame_begin_returns_null = 0;
    g_frame_begin_calls        = 0;
    g_dispatch_calls           = 0;
    g_cube_transition_calls    = 0;
    g_tex_transition_calls     = 0;
    g_warn_count               = 0;
    g_last_warn[0]             = '\0';
}

/* ---- log capture (replaces core/log.c) ---------------------------------- */

void log_set_level(LogLevel level) { (void)level; }

void log_write(LogLevel level, const char *file, int line, const char *fmt, ...) {
    (void)file; (void)line;
    if (level == LOG_WARN) {
        va_list ap;
        va_start(ap, fmt);
        vsnprintf(g_last_warn, sizeof(g_last_warn), fmt, ap);
        va_end(ap);
        g_warn_count++;
    }
}

/* ---- shader_io stub ----------------------------------------------------- */

char *shader_read_file(const char *path, usize *out_len) {
    (void)path;
    static const char src[] = "/* fake compute shader */";
    char *copy = (char *)malloc(sizeof(src));
    if (copy) memcpy(copy, src, sizeof(src));
    if (out_len) *out_len = sizeof(src) - 1u;
    return copy;
}

/* ---- RHI stubs ---------------------------------------------------------- */

static RHIHandle fake_handle(void) {
    RHIHandle h = { 0u, 1u }; /* generation != 0 -> rhi_handle_valid */
    return h;
}

RHIShader rhi_shader_create_compute(RHIDevice *d, const char *src, usize len) {
    (void)d; (void)src; (void)len; return fake_handle();
}
void rhi_shader_destroy(RHIDevice *d, RHIShader s) { (void)d; (void)s; }

RHIPipeline rhi_pipeline_create(RHIDevice *d, const RHIPipelineDesc *desc) {
    (void)d; (void)desc; return fake_handle();
}
void rhi_pipeline_destroy(RHIDevice *d, RHIPipeline p) { (void)d; (void)p; }
i32  rhi_pipeline_get_uniform_location(RHIDevice *d, RHIPipeline p, const char *n) {
    (void)d; (void)p; (void)n; return 0; /* valid: exercise the set_uniform paths */
}

RHITexture rhi_texture_create(RHIDevice *d, const RHITextureDesc *desc) {
    (void)d; (void)desc; return fake_handle();
}
void rhi_texture_destroy(RHIDevice *d, RHITexture t) { (void)d; (void)t; }

RHICubemap rhi_cubemap_create(RHIDevice *d, const RHICubemapDesc *desc) {
    (void)d; (void)desc; return fake_handle();
}
void rhi_cubemap_destroy(RHIDevice *d, RHICubemap cm) { (void)d; (void)cm; }

RHISampler rhi_sampler_create(RHIDevice *d, const RHISamplerDesc *desc) {
    (void)d; (void)desc; return fake_handle();
}
void rhi_sampler_destroy(RHIDevice *d, RHISampler s) { (void)d; (void)s; }

RHICmdBuffer *rhi_frame_begin(RHIDevice *dev) {
    (void)dev;
    g_frame_begin_calls++;
    return g_frame_begin_returns_null ? NULL : (RHICmdBuffer *)&g_cmd_sentinel;
}
void rhi_frame_end(RHIDevice *dev) { (void)dev; }
void rhi_present(RHIDevice *dev)  { (void)dev; }

void rhi_cubemap_transition_to_read(RHIDevice *d, RHICubemap cm) {
    (void)d; (void)cm; g_cube_transition_calls++;
}
void rhi_texture_transition_to_read(RHIDevice *d, RHITexture t) {
    (void)d; (void)t; g_tex_transition_calls++;
}

void rhi_cmd_bind_pipeline(RHICmdBuffer *c, RHIPipeline p) { (void)c; (void)p; }
void rhi_cmd_bind_image_texture(RHICmdBuffer *c, RHITexture t, u32 u, u32 mip, bool wo) {
    (void)c; (void)t; (void)u; (void)mip; (void)wo;
}
void rhi_cmd_bind_image_cubemap_face(RHICmdBuffer *c, RHICubemap cm, u32 f, u32 mip, u32 u, bool wo) {
    (void)c; (void)cm; (void)f; (void)mip; (void)u; (void)wo;
}
void rhi_cmd_bind_cubemap_sampler(RHICmdBuffer *c, RHICubemap cm, RHISampler s, u32 u) {
    (void)c; (void)cm; (void)s; (void)u;
}
void rhi_cmd_set_uniform_i32(RHICmdBuffer *c, i32 loc, i32 v) { (void)c; (void)loc; (void)v; }
void rhi_cmd_set_uniform_f32(RHICmdBuffer *c, i32 loc, f32 v) { (void)c; (void)loc; (void)v; }
void rhi_cmd_set_uniform_vec3(RHICmdBuffer *c, i32 loc, f32 x, f32 y, f32 z) {
    (void)c; (void)loc; (void)x; (void)y; (void)z;
}
void rhi_cmd_memory_barrier(RHICmdBuffer *c) { (void)c; }
void rhi_cmd_dispatch(RHICmdBuffer *c, u32 x, u32 y, u32 z) {
    (void)c; (void)x; (void)y; (void)z; g_dispatch_calls++;
}

/* ---- Tests ----------------------------------------------------------------
 * Expected dispatch counts:
 *   sky capture : 6 faces                       -> 6
 *   BRDF LUT    : 1
 *   irradiance  : 6 faces                       -> 6
 *   prefilter   : 6 faces x 5 mips              -> 30
 *   ibl_generate total                          -> 37
 * ------------------------------------------------------------------------- */

TEST(ibl_capture_env_sky_dispatches_all_faces)
{
    fake_reset();
    IBLSystem sys;
    ibl_init(&sys, (RHIDevice *)&g_cmd_sentinel);

    ibl_capture_env_sky(&sys, (RHIDevice *)&g_cmd_sentinel, NULL, NULL);

    ASSERT_EQ(g_dispatch_calls, 6u);     /* one dispatch per cubemap face */
    ASSERT_EQ(g_frame_begin_calls, 6u);  /* no `if (!cmd) break;` early-out */
    ASSERT_EQ(g_cube_transition_calls, 1u);

    ibl_destroy(&sys, (RHIDevice *)&g_cmd_sentinel);
}

TEST(ibl_generate_runs_all_three_stages)
{
    fake_reset();
    IBLSystem sys;
    RHIDevice *dev = (RHIDevice *)&g_cmd_sentinel;
    ibl_init(&sys, dev);

    ibl_generate(&sys, dev, sys.env_map);

    ASSERT_EQ(g_dispatch_calls, 37u);    /* 1 BRDF + 6 irradiance + 30 prefilter */
    ASSERT_EQ(g_frame_begin_calls, 37u);
    ASSERT_EQ(g_cube_transition_calls, 2u); /* irradiance + prefilter */
    ASSERT_EQ(g_tex_transition_calls, 1u);  /* BRDF LUT */
    ASSERT_TRUE(sys.ready);

    ibl_destroy(&sys, dev);
}

TEST(ibl_generate_brdf_only_without_env)
{
    fake_reset();
    IBLSystem sys;
    RHIDevice *dev = (RHIDevice *)&g_cmd_sentinel;
    ibl_init(&sys, dev);

    ibl_generate(&sys, dev, RHI_HANDLE_NULL);

    ASSERT_EQ(g_dispatch_calls, 1u);     /* BRDF LUT only */
    ASSERT_TRUE(sys.ready);

    ibl_destroy(&sys, dev);
}

/* R434: NULL command handle (old GL frame_begin behaviour) must degrade
 * explicitly — a logged warning and ready=false — not a silent black env. */
TEST(ibl_null_cmd_degrades_explicitly)
{
    fake_reset();
    g_frame_begin_returns_null = 1;
    IBLSystem sys;
    RHIDevice *dev = (RHIDevice *)&g_cmd_sentinel;
    ibl_init(&sys, dev);

    unsigned warns_before = g_warn_count;
    ibl_capture_env_sky(&sys, dev, NULL, NULL);
    ASSERT_EQ(g_dispatch_calls, 0u);
    ASSERT_TRUE(g_warn_count > warns_before); /* explicit, not silent */

    warns_before = g_warn_count;
    ibl_generate(&sys, dev, sys.env_map);
    ASSERT_EQ(g_dispatch_calls, 0u);
    ASSERT_TRUE(g_warn_count > warns_before);
    ASSERT_FALSE(sys.ready); /* must not claim success when nothing ran */

    ibl_destroy(&sys, dev);
}

TEST_MAIN_BEGIN()
    RUN_TEST(ibl_capture_env_sky_dispatches_all_faces);
    RUN_TEST(ibl_generate_runs_all_three_stages);
    RUN_TEST(ibl_generate_brdf_only_without_env);
    RUN_TEST(ibl_null_cmd_degrades_explicitly);
TEST_MAIN_END()
