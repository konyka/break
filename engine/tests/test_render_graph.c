/* ==========================================================================
 *  test_render_graph.c — Unit tests for the declarative render-graph module.
 *
 *  Tests cover: creation, pass/resource declaration, dependency derivation,
 *  dead-pass culling, topological sort, execute callbacks, and reset.
 * ========================================================================== */

#include "test_framework.h"
#include <renderer/render_graph.h>
#include <string.h>

/* ---- Stub RHI functions for unit-test (no real GPU backend) ---- */
RHITexture rhi_texture_create(RHIDevice *dev, const RHITextureDesc *desc) {
    (void)dev; (void)desc;
    RHITexture t = {.index = 1, .generation = 1};
    return t;
}
void rhi_texture_destroy(RHIDevice *dev, RHITexture tex) {
    (void)dev; (void)tex;
}
RHIBuffer rhi_buffer_create(RHIDevice *dev, const RHIBufferDesc *desc) {
    (void)dev; (void)desc;
    RHIBuffer b = {.index = 1, .generation = 1};
    return b;
}

/* -----------------------------------------------------------------------
 *  Execute callback helpers
 * ----------------------------------------------------------------------- */

static int g_exec_order[32];
static int g_exec_idx = 0;

static void exec_pass_a(void *ctx, RGPass *pass)
{
    (void)pass;
    g_exec_order[g_exec_idx++] = 0;
    (*(int *)ctx)++;
}
static void exec_pass_b(void *ctx, RGPass *pass)
{
    (void)pass;
    g_exec_order[g_exec_idx++] = 1;
    (*(int *)ctx)++;
}
static void exec_pass_c(void *ctx, RGPass *pass)
{
    (void)pass;
    g_exec_order[g_exec_idx++] = 2;
    (*(int *)ctx)++;
}
static void exec_pass_dead(void *ctx, RGPass *pass)
{
    (void)pass;
    /* Should never be called if dead-pass culling works. */
    (*(int *)ctx) += 100;
}

/* -----------------------------------------------------------------------
 *  Tests
 * ----------------------------------------------------------------------- */

TEST(create_destroy)
{
    RenderGraph *rg = rg_create();
    ASSERT_NOT_NULL(rg);
    ASSERT_EQ(rg_pass_count(rg), 0u);
    ASSERT_EQ(rg_resource_count(rg), 0u);
    rg_destroy(rg);
}

TEST(add_passes)
{
    RenderGraph *rg = rg_create();
    RGPass *p1 = rg_add_pass(rg, "shadow", RG_PASS_GRAPHICS);
    RGPass *p2 = rg_add_pass(rg, "forward", RG_PASS_GRAPHICS);
    RGPass *p3 = rg_add_pass(rg, "tonemap", RG_PASS_COMPUTE);

    ASSERT_NOT_NULL(p1);
    ASSERT_NOT_NULL(p2);
    ASSERT_NOT_NULL(p3);
    ASSERT_EQ(rg_pass_count(rg), 3u);
    rg_destroy(rg);
}

TEST(create_resources)
{
    RenderGraph *rg = rg_create();

    RGTextureDesc td = { .width = 1920, .height = 1080, .format = 1,
                          .mip_levels = 1, .is_depth = false, .name = "color" };
    RGResource color = rg_create_texture(rg, "color", &td);
    ASSERT_NEQ(color, RG_INVALID_RESOURCE);

    RGBufferDesc bd = { .size = 4096, .name = "ssbo" };
    RGResource buf = rg_create_buffer(rg, "ssbo", &bd);
    ASSERT_NEQ(buf, RG_INVALID_RESOURCE);

    ASSERT_EQ(rg_resource_count(rg), 2u);
    rg_destroy(rg);
}

TEST(import_external)
{
    RenderGraph *rg = rg_create();

    /* Use a dummy non-null handle (1) to simulate an imported texture. */
    RHITexture dummy = {.index = 1, .generation = 1};
    RGResource imported = rg_import_texture(rg, "backbuffer", dummy);
    ASSERT_NEQ(imported, RG_INVALID_RESOURCE);
    ASSERT_EQ(rg_resource_count(rg), 1u);

    rg_destroy(rg);
}

TEST(compile_empty)
{
    RenderGraph *rg = rg_create();
    bool ok = rg_compile(rg);
    ASSERT_TRUE(ok);
    ASSERT_EQ(rg_pass_count(rg), 0u);
    rg_destroy(rg);
}

TEST(dependency_and_order)
{
    /*
     *  Graph:
     *    shadow -> writes depth_tex
     *    forward -> reads depth_tex, writes color_tex
     *    tonemap -> reads color_tex, writes backbuffer (imported)
     *
     *  Expected execution order: shadow, forward, tonemap
     */
    RenderGraph *rg = rg_create();

    RGTextureDesc depth_desc = { .width = 1024, .height = 1024, .format = 2,
                                  .mip_levels = 1, .is_depth = true, .name = "depth" };
    RGResource depth_tex = rg_create_texture(rg, "depth", &depth_desc);

    RGTextureDesc color_desc = { .width = 1920, .height = 1080, .format = 1,
                                  .mip_levels = 1, .is_depth = false, .name = "color" };
    RGResource color_tex = rg_create_texture(rg, "color", &color_desc);

    RHITexture bb_handle = {.index = 42, .generation = 1};
    RGResource backbuffer = rg_import_texture(rg, "backbuffer", bb_handle);

    RGPass *shadow  = rg_add_pass(rg, "shadow",  RG_PASS_GRAPHICS);
    RGPass *forward = rg_add_pass(rg, "forward", RG_PASS_GRAPHICS);
    RGPass *tonemap = rg_add_pass(rg, "tonemap", RG_PASS_GRAPHICS);

    rg_pass_write(shadow,  depth_tex,  RG_USAGE_DEPTH_ATTACHMENT);
    rg_pass_read(forward,  depth_tex,  RG_USAGE_SHADER_READ);
    rg_pass_write(forward, color_tex,  RG_USAGE_COLOR_ATTACHMENT);
    rg_pass_read(tonemap,  color_tex,  RG_USAGE_SHADER_READ);
    rg_pass_write(tonemap, backbuffer, RG_USAGE_PRESENT);

    bool ok = rg_compile(rg);
    ASSERT_TRUE(ok);

    /* shadow must execute before forward, forward before tonemap */
    ASSERT_TRUE(shadow->execution_order < forward->execution_order);
    ASSERT_TRUE(forward->execution_order < tonemap->execution_order);

    /* No dead passes */
    ASSERT_EQ(rg_culled_pass_count(rg), 0u);

    rg_destroy(rg);
}

TEST(dead_pass_culling)
{
    /*
     *  Graph:
     *    pass_live  -> writes backbuffer (imported, PRESENT)
     *    pass_dead  -> writes orphan_tex (never consumed, not imported)
     *
     *  pass_dead should be culled.
     */
    RenderGraph *rg = rg_create();

    RGTextureDesc orphan_desc = { .width = 256, .height = 256, .format = 1,
                                   .mip_levels = 1, .name = "orphan" };
    RGResource orphan = rg_create_texture(rg, "orphan", &orphan_desc);

    RHITexture bb_handle = {.index = 99, .generation = 1};
    RGResource backbuffer = rg_import_texture(rg, "backbuffer", bb_handle);

    RGPass *live = rg_add_pass(rg, "live_pass", RG_PASS_GRAPHICS);
    RGPass *dead = rg_add_pass(rg, "dead_pass", RG_PASS_GRAPHICS);

    rg_pass_write(live, backbuffer, RG_USAGE_PRESENT);
    rg_pass_write(dead, orphan, RG_USAGE_COLOR_ATTACHMENT);

    bool ok = rg_compile(rg);
    ASSERT_TRUE(ok);

    ASSERT_FALSE(live->culled);
    ASSERT_TRUE(dead->culled);
    ASSERT_EQ(rg_culled_pass_count(rg), 1u);

    rg_destroy(rg);
}

TEST(execute_callbacks)
{
    /*
     *  Build a chain: A -> B -> C, all writing to an imported resource.
     *  Execute and verify callback invocation order.
     */
    RenderGraph *rg = rg_create();

    RHITexture bb_handle = {.index = 1, .generation = 1};
    RGResource bb = rg_import_texture(rg, "bb", bb_handle);

    RGTextureDesc td = { .width = 512, .height = 512, .format = 1,
                          .mip_levels = 1, .name = "tmp" };
    RGResource tmp1 = rg_create_texture(rg, "tmp1", &td);
    RGResource tmp2 = rg_create_texture(rg, "tmp2", &td);

    int counter = 0;
    RGPass *pa = rg_add_pass(rg, "A", RG_PASS_GRAPHICS);
    RGPass *pb = rg_add_pass(rg, "B", RG_PASS_GRAPHICS);
    RGPass *pc = rg_add_pass(rg, "C", RG_PASS_GRAPHICS);

    rg_pass_write(pa, tmp1, RG_USAGE_COLOR_ATTACHMENT);
    rg_pass_read(pb,  tmp1, RG_USAGE_SHADER_READ);
    rg_pass_write(pb, tmp2, RG_USAGE_COLOR_ATTACHMENT);
    rg_pass_read(pc,  tmp2, RG_USAGE_SHADER_READ);
    rg_pass_write(pc, bb,   RG_USAGE_PRESENT);

    rg_pass_set_execute(pa, exec_pass_a, &counter);
    rg_pass_set_execute(pb, exec_pass_b, &counter);
    rg_pass_set_execute(pc, exec_pass_c, &counter);

    bool ok = rg_compile(rg);
    ASSERT_TRUE(ok);

    g_exec_idx = 0;
    rg_execute(rg);

    ASSERT_EQ(g_exec_idx, 3);
    ASSERT_EQ(g_exec_order[0], 0);  /* A first */
    ASSERT_EQ(g_exec_order[1], 1);  /* B second */
    ASSERT_EQ(g_exec_order[2], 2);  /* C third */
    ASSERT_EQ(counter, 3);

    rg_destroy(rg);
}

TEST(execute_skips_dead)
{
    RenderGraph *rg = rg_create();

    RHITexture bb_handle = {.index = 1, .generation = 1};
    RGResource bb = rg_import_texture(rg, "bb", bb_handle);

    RGTextureDesc td = { .width = 64, .height = 64, .format = 1,
                          .mip_levels = 1, .name = "unused" };
    RGResource unused = rg_create_texture(rg, "unused", &td);

    int counter = 0;
    RGPass *live = rg_add_pass(rg, "live", RG_PASS_GRAPHICS);
    RGPass *dead = rg_add_pass(rg, "dead", RG_PASS_GRAPHICS);

    rg_pass_write(live, bb,     RG_USAGE_PRESENT);
    rg_pass_write(dead, unused, RG_USAGE_COLOR_ATTACHMENT);

    rg_pass_set_execute(live, exec_pass_a, &counter);
    rg_pass_set_execute(dead, exec_pass_dead, &counter);

    bool ok = rg_compile(rg);
    ASSERT_TRUE(ok);

    g_exec_idx = 0;
    rg_execute(rg);

    /* Only live pass should have executed */
    ASSERT_EQ(g_exec_idx, 1);
    ASSERT_EQ(g_exec_order[0], 0);
    ASSERT_EQ(counter, 1);  /* Dead pass would add 100 */

    rg_destroy(rg);
}

TEST(reset_and_reuse)
{
    RenderGraph *rg = rg_create();

    RHITexture bb_handle = {.index = 1, .generation = 1};
    RGResource bb = rg_import_texture(rg, "bb", bb_handle);

    RGPass *p = rg_add_pass(rg, "frame1", RG_PASS_GRAPHICS);
    rg_pass_write(p, bb, RG_USAGE_PRESENT);
    ASSERT_TRUE(rg_compile(rg));
    ASSERT_EQ(rg_pass_count(rg), 1u);

    /* Reset for next frame */
    rg_reset(rg);
    ASSERT_EQ(rg_pass_count(rg), 0u);
    ASSERT_EQ(rg_resource_count(rg), 0u);

    /* Rebuild for frame 2 */
    RGResource bb2 = rg_import_texture(rg, "bb2", bb_handle);
    RGPass *p2 = rg_add_pass(rg, "frame2", RG_PASS_GRAPHICS);
    rg_pass_write(p2, bb2, RG_USAGE_PRESENT);
    ASSERT_TRUE(rg_compile(rg));
    ASSERT_EQ(rg_pass_count(rg), 1u);

    rg_destroy(rg);
}

TEST(resource_lookup)
{
    RenderGraph *rg = rg_create();

    RHITexture ext = {.index = 777, .generation = 1};
    RGResource imp = rg_import_texture(rg, "ext_tex", ext);
    ASSERT_EQ(rg_get_texture(rg, imp).index, ext.index);

    rg_destroy(rg);
}

TEST(stats)
{
    RenderGraph *rg = rg_create();

    RGTextureDesc td = { .width = 128, .height = 128, .format = 1,
                          .mip_levels = 1, .name = "t" };
    RGResource t1 = rg_create_texture(rg, "t1", &td);
    RGResource t2 = rg_create_texture(rg, "t2", &td);
    (void)t2;
    ASSERT_EQ(rg_resource_count(rg), 2u);

    RHITexture bb_handle = {.index = 1, .generation = 1};
    RGResource bb = rg_import_texture(rg, "bb", bb_handle);

    RGPass *p1 = rg_add_pass(rg, "p1", RG_PASS_GRAPHICS);
    RGPass *p2 = rg_add_pass(rg, "p2", RG_PASS_GRAPHICS);
    ASSERT_EQ(rg_pass_count(rg), 2u);

    rg_pass_write(p1, t1, RG_USAGE_COLOR_ATTACHMENT);
    rg_pass_write(p2, bb, RG_USAGE_PRESENT);
    /* p1 writes t1 which is never consumed → should be culled */

    rg_compile(rg);
    ASSERT_EQ(rg_culled_pass_count(rg), 1u);

    rg_destroy(rg);
}

/* -----------------------------------------------------------------------
 *  Edge Cases
 * ----------------------------------------------------------------------- */

TEST(destroy_null)
{
    rg_destroy(NULL);  /* Must not crash */
}

TEST(execute_without_compile)
{
    RenderGraph *rg = rg_create();

    RHITexture bb_handle = {.index = 1, .generation = 1};
    RGResource bb = rg_import_texture(rg, "bb", bb_handle);

    int counter = 0;
    RGPass *p = rg_add_pass(rg, "p", RG_PASS_GRAPHICS);
    rg_pass_write(p, bb, RG_USAGE_PRESENT);
    rg_pass_set_execute(p, exec_pass_a, &counter);

    /* Execute without compile - should not crash */
    g_exec_idx = 0;
    rg_execute(rg);
    /* Behavior is implementation-defined - just verify no crash */

    rg_destroy(rg);
}

TEST(single_pass_no_resources)
{
    RenderGraph *rg = rg_create();

    RGPass *p = rg_add_pass(rg, "solo", RG_PASS_GRAPHICS);
    ASSERT_NOT_NULL(p);
    ASSERT_EQ(rg_pass_count(rg), 1u);

    /* Compile without any resources */
    bool ok = rg_compile(rg);
    /* May succeed or fail - just verify no crash */
    (void)ok;

    rg_destroy(rg);
}

TEST(create_texture_null_desc)
{
    RenderGraph *rg = rg_create();

    /* NULL descriptor should return invalid resource */
    RGResource res = rg_create_texture(rg, "test", NULL);
    /* Behavior is implementation-defined - just verify no crash */
    (void)res;

    rg_destroy(rg);
}

/* -----------------------------------------------------------------------
 *  Main
 * ----------------------------------------------------------------------- */

TEST_MAIN_BEGIN()
    RUN_TEST(create_destroy);
    RUN_TEST(add_passes);
    RUN_TEST(create_resources);
    RUN_TEST(import_external);
    RUN_TEST(compile_empty);
    RUN_TEST(dependency_and_order);
    RUN_TEST(dead_pass_culling);
    RUN_TEST(execute_callbacks);
    RUN_TEST(execute_skips_dead);
    RUN_TEST(reset_and_reuse);
    RUN_TEST(resource_lookup);
    RUN_TEST(stats);
    /* Edge cases */
    RUN_TEST(destroy_null);
    RUN_TEST(execute_without_compile);
    RUN_TEST(single_pass_no_resources);
    RUN_TEST(create_texture_null_desc);
TEST_MAIN_END()
