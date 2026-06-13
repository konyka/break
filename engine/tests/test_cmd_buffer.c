/* test_cmd_buffer.c — Unit tests for the parallel render command buffer.
 *
 * Tests the CPU-side recording logic (no GPU/RHI needed).
 * The submit/replay path is excluded since it calls into RHI.
 */

#include "test_framework.h"
#include <renderer/cmd_buffer.h>
#include <string.h>

/* Helper: create a dummy RHI handle */
static RHIPipeline dummy_pipe(u32 id) { return (RHIPipeline){id, 1}; }
static RHIBuffer   dummy_buf(u32 id)  { return (RHIBuffer){id, 1}; }
static RHITexture  dummy_tex(u32 id)  { return (RHITexture){id, 1}; }

/* ParallelRenderer is ~9MB — must be heap-allocated to avoid stack overflow */
static ParallelRenderer *alloc_pr(void) {
    ParallelRenderer *pr = (ParallelRenderer *)calloc(1, sizeof(ParallelRenderer));
    return pr;
}
static void free_pr(ParallelRenderer *pr) { free(pr); }

/* ---- Lifecycle ---- */

TEST(cmd_lifecycle) {
    ParallelRenderer *pr = alloc_pr();
    ASSERT_NOT_NULL(pr);
    parallel_renderer_init(pr, 4);
    ASSERT_EQ(pr->thread_count, 4u);
    ASSERT_FALSE(pr->recording);

    parallel_renderer_begin_frame(pr);
    ASSERT_TRUE(pr->recording);

    parallel_renderer_end_frame(pr);
    ASSERT_FALSE(pr->recording);

    parallel_renderer_shutdown(pr);
    free_pr(pr);
}

TEST(cmd_init_clamps_thread_count) {
    ParallelRenderer *pr = alloc_pr();
    ASSERT_NOT_NULL(pr);
    parallel_renderer_init(pr, 0);
    ASSERT_EQ(pr->thread_count, 1u);

    parallel_renderer_init(pr, 999);
    ASSERT_EQ(pr->thread_count, (u32)CMD_BUFFER_MAX_THREADS);

    parallel_renderer_shutdown(pr);
    free_pr(pr);
}

TEST(cmd_null_safety) {
    /* All lifecycle functions should tolerate NULL */
    parallel_renderer_init(NULL, 4);
    parallel_renderer_begin_frame(NULL);
    parallel_renderer_end_frame(NULL);
    parallel_renderer_shutdown(NULL);
    ASSERT_EQ(parallel_renderer_total_commands(NULL), 0u);

    /* get_buffer with NULL should return NULL */
    RenderCmdBuffer *buf = parallel_renderer_get_buffer(NULL, 0);
    ASSERT_TRUE(buf == NULL);
}

/* ---- Thread buffer access ---- */

TEST(cmd_get_buffer_valid) {
    ParallelRenderer *pr = alloc_pr();
    ASSERT_NOT_NULL(pr);
    parallel_renderer_init(pr, 4);
    parallel_renderer_begin_frame(pr);

    RenderCmdBuffer *buf0 = parallel_renderer_get_buffer(pr, 0);
    ASSERT_NOT_NULL(buf0);
    ASSERT_EQ(buf0->count, 0u);

    RenderCmdBuffer *buf3 = parallel_renderer_get_buffer(pr, 3);
    ASSERT_NOT_NULL(buf3);

    /* Different thread IDs should return different buffers */
    ASSERT_TRUE(buf0 != buf3);

    parallel_renderer_end_frame(pr);
    parallel_renderer_shutdown(pr);
    free_pr(pr);
}

TEST(cmd_get_buffer_out_of_range) {
    ParallelRenderer *pr = alloc_pr();
    ASSERT_NOT_NULL(pr);
    parallel_renderer_init(pr, 2);
    parallel_renderer_begin_frame(pr);

    RenderCmdBuffer *bad = parallel_renderer_get_buffer(pr, 2);
    ASSERT_TRUE(bad == NULL);

    bad = parallel_renderer_get_buffer(pr, 100);
    ASSERT_TRUE(bad == NULL);

    parallel_renderer_end_frame(pr);
    parallel_renderer_shutdown(pr);
    free_pr(pr);
}

/* ---- Command recording ---- */

TEST(cmd_draw_recording) {
    ParallelRenderer *pr = alloc_pr();
    ASSERT_NOT_NULL(pr);
    parallel_renderer_init(pr, 1);
    parallel_renderer_begin_frame(pr);

    RenderCmdBuffer *buf = parallel_renderer_get_buffer(pr, 0);
    ASSERT_NOT_NULL(buf);

    cmd_draw(buf, 100, 1, 0);
    ASSERT_EQ(buf->count, 1u);
    ASSERT_EQ(buf->commands[0].type, RENDER_CMD_DRAW);
    ASSERT_EQ(buf->commands[0].draw.vertex_count, 100u);
    ASSERT_EQ(buf->commands[0].draw.instance_count, 1u);
    ASSERT_EQ(buf->commands[0].draw.first_vertex, 0u);

    parallel_renderer_end_frame(pr);
    parallel_renderer_shutdown(pr);
    free_pr(pr);
}

TEST(cmd_draw_indexed_recording) {
    RenderCmdBuffer buf = {0};
    cmd_draw_indexed(&buf, 36, 2, 0, -1);
    ASSERT_EQ(buf.count, 1u);
    ASSERT_EQ(buf.commands[0].type, RENDER_CMD_DRAW_INDEXED);
    ASSERT_EQ(buf.commands[0].draw_indexed.index_count, 36u);
    ASSERT_EQ(buf.commands[0].draw_indexed.instance_count, 2u);
    ASSERT_EQ(buf.commands[0].draw_indexed.first_index, 0u);
    ASSERT_EQ(buf.commands[0].draw_indexed.vertex_offset, -1);
}

TEST(cmd_bind_pipeline_recording) {
    RenderCmdBuffer buf = {0};
    RHIPipeline pipe = dummy_pipe(42);
    cmd_bind_pipeline(&buf, pipe);
    ASSERT_EQ(buf.count, 1u);
    ASSERT_EQ(buf.commands[0].type, RENDER_CMD_BIND_PIPELINE);
    ASSERT_EQ(buf.commands[0].bind_pipeline.pipeline.index, 42u);
}

TEST(cmd_bind_buffers) {
    RenderCmdBuffer buf = {0};
    RHIBuffer vbo = dummy_buf(10);
    RHIBuffer ibo = dummy_buf(20);

    cmd_bind_vertex_buffer(&buf, vbo, 64);
    cmd_bind_index_buffer(&buf, ibo, 0, true);

    ASSERT_EQ(buf.count, 2u);
    ASSERT_EQ(buf.commands[0].type, RENDER_CMD_BIND_VERTEX_BUFFER);
    ASSERT_EQ(buf.commands[0].bind_vb.buffer.index, 10u);
    ASSERT_EQ(buf.commands[0].bind_vb.offset, 64u);

    ASSERT_EQ(buf.commands[1].type, RENDER_CMD_BIND_INDEX_BUFFER);
    ASSERT_EQ(buf.commands[1].bind_ib.buffer.index, 20u);
    ASSERT_TRUE(buf.commands[1].bind_ib.is_u32);
}

TEST(cmd_bind_uniform_and_texture) {
    RenderCmdBuffer buf = {0};
    RHIBuffer ubo = dummy_buf(5);
    RHITexture tex = dummy_tex(7);

    cmd_bind_uniform(&buf, 2, ubo, 0, 256);
    cmd_bind_texture(&buf, 0, tex);

    ASSERT_EQ(buf.count, 2u);
    ASSERT_EQ(buf.commands[0].type, RENDER_CMD_BIND_UNIFORM);
    ASSERT_EQ(buf.commands[0].bind_uniform.binding, 2u);
    ASSERT_EQ(buf.commands[0].bind_uniform.buffer.index, 5u);
    ASSERT_EQ(buf.commands[0].bind_uniform.size, 256u);

    ASSERT_EQ(buf.commands[1].type, RENDER_CMD_BIND_TEXTURE);
    ASSERT_EQ(buf.commands[1].bind_texture.slot, 0u);
    ASSERT_EQ(buf.commands[1].bind_texture.texture.index, 7u);
}

TEST(cmd_scissor_viewport) {
    RenderCmdBuffer buf = {0};
    cmd_set_scissor(&buf, 10, 20, 800, 600);
    cmd_set_viewport(&buf, 0.0f, 0.0f, 1920.0f, 1080.0f, 0.0f, 1.0f);

    ASSERT_EQ(buf.count, 2u);
    ASSERT_EQ(buf.commands[0].type, RENDER_CMD_SET_SCISSOR);
    ASSERT_EQ(buf.commands[0].scissor.x, 10);
    ASSERT_EQ(buf.commands[0].scissor.w, 800u);

    ASSERT_EQ(buf.commands[1].type, RENDER_CMD_SET_VIEWPORT);
    ASSERT_FLOAT_EQ(buf.commands[1].viewport.w, 1920.0f, 1e-5f);
    ASSERT_FLOAT_EQ(buf.commands[1].viewport.max_depth, 1.0f, 1e-5f);
}

TEST(cmd_push_constants) {
    RenderCmdBuffer buf = {0};
    f32 data[4] = {1.0f, 2.0f, 3.0f, 4.0f};
    cmd_push_constants(&buf, 0, sizeof(data), data);

    ASSERT_EQ(buf.count, 1u);
    ASSERT_EQ(buf.commands[0].type, RENDER_CMD_PUSH_CONSTANTS);
    ASSERT_EQ(buf.commands[0].push_constants.offset, 0u);
    ASSERT_EQ(buf.commands[0].push_constants.size, (u32)sizeof(data));

    f32 *stored = (f32 *)buf.commands[0].push_constants.data;
    ASSERT_FLOAT_EQ(stored[0], 1.0f, 1e-5f);
    ASSERT_FLOAT_EQ(stored[3], 4.0f, 1e-5f);
}

TEST(cmd_push_constants_null_data) {
    RenderCmdBuffer buf = {0};
    cmd_push_constants(&buf, 16, 32, NULL);
    ASSERT_EQ(buf.count, 1u);
    ASSERT_EQ(buf.commands[0].push_constants.size, 32u);
    /* data should be zeroed (from calloc/zero-init) */
}

TEST(cmd_push_constants_size_clamp) {
    RenderCmdBuffer buf = {0};
    u8 big_data[256];
    memset(big_data, 0xAB, sizeof(big_data));
    /* Size exceeds CMD_BUFFER_PUSH_CONST_MAX (128) — should be clamped */
    cmd_push_constants(&buf, 0, 256, big_data);
    ASSERT_EQ(buf.count, 1u);
    ASSERT_EQ(buf.commands[0].push_constants.size, (u32)CMD_BUFFER_PUSH_CONST_MAX);
}

/* ---- Overflow ---- */

TEST(cmd_overflow_drops_commands) {
    RenderCmdBuffer buf = {0};
    /* Fill buffer to max */
    for (u32 i = 0; i < CMD_BUFFER_MAX_COMMANDS; i++) {
        cmd_draw(&buf, i, 1, 0);
    }
    ASSERT_EQ(buf.count, (u32)CMD_BUFFER_MAX_COMMANDS);

    /* Next command should be silently dropped */
    cmd_draw(&buf, 9999, 1, 0);
    ASSERT_EQ(buf.count, (u32)CMD_BUFFER_MAX_COMMANDS);

    /* Verify first command is intact */
    ASSERT_EQ(buf.commands[0].draw.vertex_count, 0u);
    /* Verify last valid command */
    ASSERT_EQ(buf.commands[CMD_BUFFER_MAX_COMMANDS - 1].draw.vertex_count,
              (u32)(CMD_BUFFER_MAX_COMMANDS - 1));
}

TEST(cmd_null_buffer_drops) {
    /* cmd_draw with NULL buf should not crash */
    cmd_draw(NULL, 100, 1, 0);
    cmd_draw_indexed(NULL, 36, 1, 0, 0);
    cmd_bind_pipeline(NULL, dummy_pipe(1));
    cmd_bind_vertex_buffer(NULL, dummy_buf(1), 0);
    cmd_bind_index_buffer(NULL, dummy_buf(1), 0, false);
    cmd_bind_uniform(NULL, 0, dummy_buf(1), 0, 64);
    cmd_bind_texture(NULL, 0, dummy_tex(1));
    cmd_set_scissor(NULL, 0, 0, 100, 100);
    cmd_set_viewport(NULL, 0, 0, 100, 100, 0, 1);
    cmd_push_constants(NULL, 0, 4, NULL);
    /* If we get here without crashing, the test passes */
    ASSERT_TRUE(true);
}

/* ---- Statistics ---- */

TEST(cmd_total_commands) {
    ParallelRenderer *pr = alloc_pr();
    ASSERT_NOT_NULL(pr);
    parallel_renderer_init(pr, 4);
    parallel_renderer_begin_frame(pr);

    RenderCmdBuffer *b0 = parallel_renderer_get_buffer(pr, 0);
    RenderCmdBuffer *b1 = parallel_renderer_get_buffer(pr, 1);

    cmd_draw(b0, 10, 1, 0);
    cmd_draw(b0, 20, 1, 0);
    cmd_draw(b1, 30, 1, 0);

    u32 total = parallel_renderer_total_commands(pr);
    ASSERT_EQ(total, 3u);

    parallel_renderer_end_frame(pr);
    parallel_renderer_shutdown(pr);
    free_pr(pr);
}

/* ---- Frame reset clears counts ---- */

TEST(cmd_frame_reset) {
    ParallelRenderer *pr = alloc_pr();
    ASSERT_NOT_NULL(pr);
    parallel_renderer_init(pr, 2);

    /* Frame 1: record some commands */
    parallel_renderer_begin_frame(pr);
    RenderCmdBuffer *b0 = parallel_renderer_get_buffer(pr, 0);
    cmd_draw(b0, 10, 1, 0);
    cmd_draw(b0, 20, 1, 0);
    ASSERT_EQ(parallel_renderer_total_commands(pr), 2u);
    parallel_renderer_end_frame(pr);

    /* Frame 2: counts should be reset */
    parallel_renderer_begin_frame(pr);
    ASSERT_EQ(parallel_renderer_total_commands(pr), 0u);
    b0 = parallel_renderer_get_buffer(pr, 0);
    ASSERT_EQ(b0->count, 0u);

    parallel_renderer_end_frame(pr);
    parallel_renderer_shutdown(pr);
    free_pr(pr);
}

/* ---- Mixed command types in order ---- */

TEST(cmd_mixed_command_sequence) {
    RenderCmdBuffer buf = {0};

    cmd_bind_pipeline(&buf, dummy_pipe(1));
    cmd_bind_vertex_buffer(&buf, dummy_buf(10), 0);
    cmd_bind_index_buffer(&buf, dummy_buf(20), 0, true);
    cmd_bind_uniform(&buf, 0, dummy_buf(30), 0, 128);
    cmd_bind_texture(&buf, 0, dummy_tex(40));
    cmd_set_viewport(&buf, 0, 0, 1920, 1080, 0, 1);
    cmd_set_scissor(&buf, 0, 0, 1920, 1080);
    cmd_draw_indexed(&buf, 36, 1, 0, 0);

    ASSERT_EQ(buf.count, 8u);
    ASSERT_EQ(buf.commands[0].type, RENDER_CMD_BIND_PIPELINE);
    ASSERT_EQ(buf.commands[1].type, RENDER_CMD_BIND_VERTEX_BUFFER);
    ASSERT_EQ(buf.commands[2].type, RENDER_CMD_BIND_INDEX_BUFFER);
    ASSERT_EQ(buf.commands[3].type, RENDER_CMD_BIND_UNIFORM);
    ASSERT_EQ(buf.commands[4].type, RENDER_CMD_BIND_TEXTURE);
    ASSERT_EQ(buf.commands[5].type, RENDER_CMD_SET_VIEWPORT);
    ASSERT_EQ(buf.commands[6].type, RENDER_CMD_SET_SCISSOR);
    ASSERT_EQ(buf.commands[7].type, RENDER_CMD_DRAW_INDEXED);
}

/* ---- Sort key ordering ---- */

TEST(cmd_sort_key_assignment) {
    ParallelRenderer *pr = alloc_pr();
    ASSERT_NOT_NULL(pr);
    parallel_renderer_init(pr, 3);
    parallel_renderer_begin_frame(pr);

    /* Assign sort keys in reverse order */
    RenderCmdBuffer *b0 = parallel_renderer_get_buffer(pr, 0);
    RenderCmdBuffer *b1 = parallel_renderer_get_buffer(pr, 1);
    RenderCmdBuffer *b2 = parallel_renderer_get_buffer(pr, 2);

    b0->sort_key = 30;
    b1->sort_key = 10;
    b2->sort_key = 20;

    cmd_draw(b0, 100, 1, 0);
    cmd_draw(b1, 200, 1, 0);
    cmd_draw(b2, 300, 1, 0);

    /* Verify all 3 commands recorded */
    ASSERT_EQ(parallel_renderer_total_commands(pr), 3u);

    parallel_renderer_end_frame(pr);
    parallel_renderer_shutdown(pr);
    free_pr(pr);
}

/* -----------------------------------------------------------------------
 *  Edge Cases
 * ----------------------------------------------------------------------- */

TEST(cmd_empty_frame) {
    ParallelRenderer *pr = alloc_pr();
    ASSERT_NOT_NULL(pr);
    parallel_renderer_init(pr, 4);
    parallel_renderer_begin_frame(pr);

    /* No commands recorded */
    ASSERT_EQ(parallel_renderer_total_commands(pr), 0u);

    parallel_renderer_end_frame(pr);
    parallel_renderer_shutdown(pr);
    free_pr(pr);
}

TEST(cmd_single_thread) {
    ParallelRenderer *pr = alloc_pr();
    ASSERT_NOT_NULL(pr);
    parallel_renderer_init(pr, 1);
    parallel_renderer_begin_frame(pr);

    RenderCmdBuffer *buf = parallel_renderer_get_buffer(pr, 0);
    ASSERT_NOT_NULL(buf);
    cmd_draw(buf, 50, 1, 0);
    cmd_draw(buf, 100, 2, 0);

    ASSERT_EQ(parallel_renderer_total_commands(pr), 2u);

    parallel_renderer_end_frame(pr);
    parallel_renderer_shutdown(pr);
    free_pr(pr);
}

TEST(cmd_push_constants_zero_size) {
    RenderCmdBuffer buf = {0};
    /* Zero size push constants - should not crash */
    cmd_push_constants(&buf, 0, 0, NULL);
    ASSERT_EQ(buf.count, 1u);
    ASSERT_EQ(buf.commands[0].push_constants.size, 0u);
}

TEST(cmd_draw_zero_vertices) {
    RenderCmdBuffer buf = {0};
    cmd_draw(&buf, 0, 1, 0);
    ASSERT_EQ(buf.count, 1u);
    ASSERT_EQ(buf.commands[0].draw.vertex_count, 0u);
}

TEST(cmd_multiple_frames_reset) {
    ParallelRenderer *pr = alloc_pr();
    ASSERT_NOT_NULL(pr);
    parallel_renderer_init(pr, 1);

    /* Frame 1 */
    parallel_renderer_begin_frame(pr);
    RenderCmdBuffer *buf = parallel_renderer_get_buffer(pr, 0);
    cmd_draw(buf, 10, 1, 0);
    ASSERT_EQ(parallel_renderer_total_commands(pr), 1u);
    parallel_renderer_end_frame(pr);

    /* Frame 2 - should be clean */
    parallel_renderer_begin_frame(pr);
    buf = parallel_renderer_get_buffer(pr, 0);
    ASSERT_EQ(buf->count, 0u);
    ASSERT_EQ(parallel_renderer_total_commands(pr), 0u);
    parallel_renderer_end_frame(pr);

    parallel_renderer_shutdown(pr);
    free_pr(pr);
}

TEST_MAIN_BEGIN()
    RUN_TEST(cmd_lifecycle);
    RUN_TEST(cmd_init_clamps_thread_count);
    RUN_TEST(cmd_null_safety);
    RUN_TEST(cmd_get_buffer_valid);
    RUN_TEST(cmd_get_buffer_out_of_range);
    RUN_TEST(cmd_draw_recording);
    RUN_TEST(cmd_draw_indexed_recording);
    RUN_TEST(cmd_bind_pipeline_recording);
    RUN_TEST(cmd_bind_buffers);
    RUN_TEST(cmd_bind_uniform_and_texture);
    RUN_TEST(cmd_scissor_viewport);
    RUN_TEST(cmd_push_constants);
    RUN_TEST(cmd_push_constants_null_data);
    RUN_TEST(cmd_push_constants_size_clamp);
    RUN_TEST(cmd_overflow_drops_commands);
    RUN_TEST(cmd_null_buffer_drops);
    RUN_TEST(cmd_total_commands);
    RUN_TEST(cmd_frame_reset);
    RUN_TEST(cmd_mixed_command_sequence);
    RUN_TEST(cmd_sort_key_assignment);
    /* Edge cases */
    RUN_TEST(cmd_empty_frame);
    RUN_TEST(cmd_single_thread);
    RUN_TEST(cmd_push_constants_zero_size);
    RUN_TEST(cmd_draw_zero_vertices);
    RUN_TEST(cmd_multiple_frames_reset);
TEST_MAIN_END()
