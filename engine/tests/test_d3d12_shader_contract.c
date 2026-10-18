#include <rhi/rhi.h>
#include "test_framework.h"
#if defined(_WIN32)
#include <rhi/rhi_d3d12.h>
#endif
/* Plan D Task 6: the D3D12 blit pipeline must be creatable from the
 * hand-authored HLSL sidecars (engine/shaders/blit_hlsl.{vert,frag},
 * precompiled to DXIL at build time) and must expose its push-constant
 * range as a byte-offset location, matching the VK convention. */
static RHIDevice *g_dev;

#if defined(_WIN32)
/* Task 1 (D3D12 shader path): the GLSL path -> sidecar name mapping is pure
 * string logic, so it is locked down here as a table instead of only through
 * a device-backed call. No device, no WARP, no sidecar files on disk: an
 * expect == NULL row asserts the refusal. */
typedef struct ShaderSidecarCase {
    const char *path;
    int stage;              /* RHI_D3D12ShaderStage, widened for the table */
    const char *expect;     /* NULL => must be refused */
} ShaderSidecarCase;

static const ShaderSidecarCase k_sidecar_cases[] = {
    /* Primary mapping: a GLSL path becomes its hand-authored sidecar. */
    { "shaders/blit.vert",  RHI_D3D12_SHADER_STAGE_VERTEX,   "blit_hlsl.vert" },
    { "shaders/blit.frag",  RHI_D3D12_SHADER_STAGE_FRAGMENT, "blit_hlsl.frag" },
    { "shaders/blit.comp",  RHI_D3D12_SHADER_STAGE_COMPUTE,  "blit_hlsl.comp" },
    /* Self-resolution: the "_hlsl" suffix is idempotent, never doubled. */
    { "shaders/blit_hlsl.vert", RHI_D3D12_SHADER_STAGE_VERTEX,   "blit_hlsl.vert" },
    { "shaders/blit_hlsl.frag", RHI_D3D12_SHADER_STAGE_FRAGMENT, "blit_hlsl.frag" },
    /* Bare names and backslash separators (paths as Windows callers write them). */
    { "blit",               RHI_D3D12_SHADER_STAGE_VERTEX,   "blit_hlsl.vert" },
    { "shaders\\blit.frag", RHI_D3D12_SHADER_STAGE_FRAGMENT, "blit_hlsl.frag" },
    /* Only the final path component survives. */
    { "a/b/c/probe_vb.frag", RHI_D3D12_SHADER_STAGE_FRAGMENT, "probe_vb_hlsl.frag" },
    /* A dotted base keeps its dots; only the last extension is stripped. */
    { "shaders/my.pirates.vert", RHI_D3D12_SHADER_STAGE_VERTEX, "my.pirates_hlsl.vert" },
    /* An extension that names no stage makes no claim about the stage. */
    { "shaders/blit.glsl",  RHI_D3D12_SHADER_STAGE_FRAGMENT, "blit_hlsl.frag" },
    /* Fail closed: the path's own stage extension must agree with the
     * request. Resolving the vertex sidecar for a ".frag" path would be a
     * silent stage swap, which is what this lock exists to prevent. */
    { "shaders/blit.frag",  RHI_D3D12_SHADER_STAGE_VERTEX,   NULL },
    { "shaders/blit.vert",  RHI_D3D12_SHADER_STAGE_FRAGMENT, NULL },
    { "shaders/blit.vert",  RHI_D3D12_SHADER_STAGE_COMPUTE,  NULL },
    { "shaders/blit.comp",  RHI_D3D12_SHADER_STAGE_FRAGMENT, NULL },
    { "shaders/blit_hlsl.frag", RHI_D3D12_SHADER_STAGE_VERTEX, NULL },
    /* A stage outside the enum has no suffix, so it cannot name a sidecar. */
    { "shaders/blit.vert",  (int)RHI_D3D12_SHADER_STAGE_COMPUTE + 7, NULL },
    /* Degenerate inputs. */
    { NULL,                 RHI_D3D12_SHADER_STAGE_VERTEX,   NULL },
    { "",                   RHI_D3D12_SHADER_STAGE_VERTEX,   NULL },
    { ".vert",              RHI_D3D12_SHADER_STAGE_VERTEX,   NULL },
    { "shaders/",           RHI_D3D12_SHADER_STAGE_VERTEX,   NULL },
};

TEST(shader_path_sidecar_derivation) {
    char name[RHI_D3D12_SHADER_SIDECAR_NAME_CAPACITY];
    usize i;
    int failures = 0;
    for (i = 0u; i < sizeof(k_sidecar_cases) / sizeof(k_sidecar_cases[0]); ++i) {
        const ShaderSidecarCase *c = &k_sidecar_cases[i];
        int ok = rhi_d3d12_shader_sidecar_name(
            c->path, (RHI_D3D12ShaderStage)c->stage, name, (usize)sizeof(name));
        if (c->expect == NULL) {
            if (ok != 0 || name[0] != '\0') {
                printf("  FAIL: path \"%s\" stage %d should be refused "
                       "(ok=%d, out=\"%s\")\n",
                       c->path ? c->path : "(null)", c->stage, ok, name);
                failures++;
            }
        } else if (ok == 0 || strcmp(name, c->expect) != 0) {
            printf("  FAIL: path \"%s\" stage %d -> \"%s\", want \"%s\"\n",
                   c->path, c->stage, name, c->expect);
            failures++;
        }
    }
    /* A name that cannot fit is refused, never truncated into a name that
     * would resolve a different file. Two budgets, two refusals: the whole
     * sidecar name over the buffer, and the base alone over it. */
    {
        char tiny[8];
        char base_tiny[4];
        int ok = rhi_d3d12_shader_sidecar_name("shaders/blit.vert",
                                               RHI_D3D12_SHADER_STAGE_VERTEX,
                                               tiny, (usize)sizeof(tiny));
        if (ok != 0 || tiny[0] != '\0') {
            printf("  FAIL: oversized sidecar name should be refused "
                   "(ok=%d, out=\"%s\")\n", ok, tiny);
            failures++;
        }
        ok = rhi_d3d12_shader_sidecar_name("shaders/blit",
                                           RHI_D3D12_SHADER_STAGE_VERTEX,
                                           base_tiny, (usize)sizeof(base_tiny));
        if (ok != 0 || base_tiny[0] != '\0') {
            printf("  FAIL: oversized base name should be refused "
                   "(ok=%d, out=\"%s\")\n", ok, base_tiny);
            failures++;
        }
    }
    ASSERT_EQ(failures, 0);
}
#endif

TEST(blit_pipeline_push_location) {
    /* The blit pipeline must exist and expose its push range as a
     * byte-offset location, matching the VK convention. */
    RHIShader vs = rhi_shader_create(g_dev, "blit_hlsl.vert", 0, false);
    RHIShader fs = rhi_shader_create(g_dev, "blit_hlsl.frag", 0, true);
    ASSERT_TRUE(rhi_handle_valid(vs));
    ASSERT_TRUE(rhi_handle_valid(fs));
    RHIPipelineDesc desc;
    memset(&desc, 0, sizeof(desc));
    desc.vert = vs; desc.frag = fs; desc.no_vertex_input = true;
    desc.color_format = RHI_FORMAT_B8G8R8A8_UNORM;
    RHIPipeline pipe = rhi_pipeline_create(g_dev, &desc);
    ASSERT_TRUE(rhi_handle_valid(pipe));
    i32 loc = rhi_pipeline_get_uniform_location(g_dev, pipe, "u_transform");
    ASSERT_TRUE(loc >= 0);           /* byte offset into the root constants */
    rhi_pipeline_destroy(g_dev, pipe);
    rhi_shader_destroy(g_dev, vs);
    rhi_shader_destroy(g_dev, fs);
}

/* The reflection-driven bindings API is the one main.c prefers over the
 * legacy per-name lookup; it must resolve to the same byte offset. */
TEST(pipeline_bindings_resolve_matches_legacy_lookup) {
    RHIShader vs = rhi_shader_create(g_dev, "blit_hlsl.vert", 0, false);
    RHIShader fs = rhi_shader_create(g_dev, "blit_hlsl.frag", 0, true);
    RHIPipelineDesc desc;
    RHIPipeline pipe;
    RHIPipelineBindings *b;
    i32 legacy, resolved;
    ASSERT_TRUE(rhi_handle_valid(vs));
    ASSERT_TRUE(rhi_handle_valid(fs));
    memset(&desc, 0, sizeof(desc));
    desc.vert = vs; desc.frag = fs; desc.no_vertex_input = true;
    desc.color_format = RHI_FORMAT_B8G8R8A8_UNORM;
    pipe = rhi_pipeline_create(g_dev, &desc);
    ASSERT_TRUE(rhi_handle_valid(pipe));

    legacy = rhi_pipeline_get_uniform_location(g_dev, pipe, "u_transform");
    ASSERT_TRUE(legacy >= 0);

    b = rhi_pipeline_bindings_create(g_dev, pipe);
    ASSERT_TRUE(b != NULL);            /* was a NULL-returning stub */
    resolved = rhi_pipeline_bindings_resolve(b, "u_transform");
    ASSERT_EQ(resolved, legacy);       /* same authority, both paths */
    ASSERT_EQ(rhi_pipeline_bindings_resolve(b, "u_does_not_exist"), -1);
    ASSERT_EQ(rhi_pipeline_bindings_resolve(NULL, "u_transform"), -1);
    rhi_pipeline_bindings_destroy(g_dev, b);

    rhi_pipeline_destroy(g_dev, pipe);
    rhi_shader_destroy(g_dev, vs);
    rhi_shader_destroy(g_dev, fs);
}

int main(void) {
#if defined(_WIN32)
    RHIResult r = RHI_RESULT_OK;
    /* Device-free first: this locks the path -> sidecar-name mapping on hosts
     * with no D3D12 adapter, where everything below has to skip. */
    printf("=== Running Tests ===\n");
    RUN_TEST(shader_path_sidecar_derivation);
    /* The sentinel HWND needs the explicit test-only fallback-window opt-in
     * (Task 4 review gate: the fallback is fail-closed by default). */
    _putenv("BREAK_D3D12_TEST_FALLBACK_HWND=1");
    g_dev = rhi_device_create_ex(RHI_BACKEND_D3D12, (void *)1, NULL, 64, 64, &r);
    if (g_dev == NULL) {
        /* No adapter: the device-backed cases below cannot run, but the
         * device-free derivation lock already did. Report Skipped only when
         * that coverage passed — a regression there must still turn ctest
         * red rather than disappear behind a skip. */
        printf("\n=== Results: %d passed, %d failed, %d total ===\n",
               g_test_pass, g_test_fail, g_test_count);
        return g_test_fail > 0 ? 1 : 77;
    }
    RUN_TEST(blit_pipeline_push_location);
    RUN_TEST(pipeline_bindings_resolve_matches_legacy_lookup);
    rhi_device_destroy(g_dev);
    printf("\n=== Results: %d passed, %d failed, %d total ===\n",
           g_test_pass, g_test_fail, g_test_count);
    return g_test_fail > 0 ? 1 : 0;
#else
    return 77;
#endif
}
