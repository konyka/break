#include "test_framework.h"
#include <core/shader_io.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

static bool read_shader_source(const char *name, char *buf, usize cap)
{
    char rel[1024];
    const char *slash = strrchr(__FILE__, '/');
    const char *candidates[3] = { NULL, name, NULL };
    if (slash) {
        snprintf(rel, sizeof(rel), "%.*s/../shaders/%s",
                 (int)(slash - __FILE__), __FILE__, name);
        candidates[0] = rel;
    }
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

/* R444: per-pid path — parallel ctest trees raced on the fixed name. */
static const char *shader_io_tmp_path(void)
{
    static char b[128];
    return test_tmp(b, sizeof b, "test_shader_io.glsl");
}
#define TMP_SHADER shader_io_tmp_path()

TEST(shader_read_rejects_oversized_file)
{
    FILE *f = fopen(TMP_SHADER, "wb");
    ASSERT_NOT_NULL(f);
#if defined(_POSIX_C_SOURCE) && _POSIX_C_SOURCE >= 200112L
    ASSERT_TRUE(ftruncate(fileno(f), (off_t)SHADER_MAX_FILE_BYTES + 1) == 0);
#else
    if (fseek(f, (long)SHADER_MAX_FILE_BYTES, SEEK_SET) == 0) fputc('x', f);
#endif
    fclose(f);

    usize len = 99;
    char *data = shader_read_file(TMP_SHADER, &len);
    ASSERT_TRUE(data == NULL);
    ASSERT_EQ(len, (usize)99);

    remove(TMP_SHADER);
}

TEST(upscale_shaders_guard_first_temporal_frame)
{
    const char *frags[] = { "upscale.frag", "upscale_vk.frag" };
    for (usize i = 0; i < sizeof(frags) / sizeof(frags[0]); i++) {
        char src[16384];
        ASSERT_TRUE(read_shader_source(frags[i], src, sizeof(src)));
        /* Both implementations need the uniform and must gate the only
         * history reprojection path so init/resize cannot sample an invalid
         * previous-frame transform. */
        ASSERT_NOT_NULL(strstr(src, "u_ups_first_frame"));
        ASSERT_NOT_NULL(strstr(src, "u_ups_first_frame < 0.5"));
    }
}

/* R550-A: the five previously dead-end post passes (SSR/SSGI/volumetric/
 * lens flare/contact shadow) self-composite the incoming frame-chain color
 * like god_rays does.  Assert the contract on BOTH backends: each shader
 * must declare the chain-color sampler (SSR reuses u_ssr_color — it already
 * samples the chain) and must blend its effect into it. */
TEST(postfx_passes_composite_chain_color)
{
    struct { const char *file; const char *sampler; const char *blend; } cases[] = {
        { "contact_shadow.frag",    "u_cs_scene",  "scene * shadow" },
        { "contact_shadow_vk.frag", "u_cs_scene",  "scene * shadow" },
        { "volumetric.frag",        "u_vol_scene", "scene * transmittance + accum" },
        { "volumetric_vk.frag",     "u_vol_scene", "scene * transmittance + accum" },
        { "lens_flare.frag",        "u_lf_scene",  "scene + flare" },
        { "lens_flare_vk.frag",     "u_lf_scene",  "scene + flare" },
        { "ssr.frag",               NULL,          "mix(scene, ssr_color, fade)" },
        { "ssr_vk.frag",            NULL,          "mix(scene, ssr_color, fade)" },
        { "ssgi_blur.frag",         "u_ssgi_scene", "scene + result" },
        { "ssgi_blur_vk.frag",      "u_ssgi_scene", "scene + result" },
    };
    for (usize i = 0; i < sizeof(cases) / sizeof(cases[0]); i++) {
        char src[16384];
        ASSERT_TRUE(read_shader_source(cases[i].file, src, sizeof(src)));
        if (cases[i].sampler)
            ASSERT_NOT_NULL(strstr(src, cases[i].sampler));
        ASSERT_NOT_NULL(strstr(src, cases[i].blend));
    }
}

TEST_MAIN_BEGIN()
    RUN_TEST(shader_read_rejects_oversized_file);
    RUN_TEST(upscale_shaders_guard_first_temporal_frame);
    RUN_TEST(postfx_passes_composite_chain_color);
TEST_MAIN_END()
