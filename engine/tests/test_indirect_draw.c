/* ==========================================================================
 *  test_indirect_draw.c — CPU-side validation tests for indirect_draw uploads.
 *
 *  R482 regression gate: indirect_draw_upload_grouped must REJECT a
 *  group-size prefix sum exceeding max_draws. The old code clamped only the
 *  total while storing UNCLAMPED per-group sizes in group_cpu_cap[] /
 *  group_cpu_base[], so the compact shader scattered past visible_draws_buf
 *  (GPU OOB write) and indirect_draw_execute_group read past the buffer.
 *
 *  Runs headless: the system struct is hand-built (no device init) and the
 *  RHI buffer uploads are no-op stubs, so only the CPU-side bookkeeping is
 *  exercised — exactly where the validation lives.
 * ========================================================================== */

#include "test_framework.h"
#include <renderer/indirect_draw.h>
#include <string.h>

/* rhi_stubs.c covers every RHI entry indirect_draw.c references except this
 * one (only indirect_draw_execute_group calls it, and no stub-linked suite
 * pulled in indirect_draw.c before). Keep the fake local — same pattern as
 * test_ibl.c's in-file backend — and record the args so the tests can assert
 * the per-group execute intervals stay inside [0, max_draws). */
static u32 g_exec_calls = 0;
static u32 g_exec_last_cmd_offset = 0;
static u32 g_exec_last_max_draws = 0;
void rhi_cmd_draw_indexed_indirect_count(RHIDevice *dev, RHIBuffer cmd_buf, u32 cmd_offset,
                                         RHIBuffer count_buf, u32 count_offset,
                                         u32 max_draws, u32 stride) {
    (void)dev; (void)cmd_buf; (void)count_buf; (void)count_offset; (void)stride;
    g_exec_calls++;
    g_exec_last_cmd_offset = cmd_offset;
    g_exec_last_max_draws  = max_draws;
}

/* Mirror the CPU-side state indirect_draw_init_grouped leaves behind
 * (buffers stay null handles — the stub uploads ignore them). */
static void make_sys(IndirectDrawSystem *sys, u32 max_draws, u32 group_count) {
    memset(sys, 0, sizeof(*sys));
    sys->ready = true;
    sys->max_draws = max_draws;
    sys->group_count = group_count;
    sys->group_cpu_cap[0] = max_draws; /* implicit group until first upload */
}

/* ----------------------------------------------------------------------- */
/*  R482: prefix-sum validation                                             */
/* ----------------------------------------------------------------------- */

TEST(upload_grouped_rejects_overflow_sum)
{
    IndirectDrawSystem sys;
    make_sys(&sys, 4, 2);
    DrawIndexedIndirectCmd cmds[6] = {{0}};
    const u32 sizes[2] = {3u, 3u}; /* sum 6 > max_draws 4 */

    indirect_draw_upload_grouped(&sys, NULL, cmds, sizes, 2);

    /* Rejected: nothing uploaded, CPU intervals untouched. */
    ASSERT_EQ(sys.current_draw_count, 0u);
    ASSERT_EQ(sys.group_cpu_cap[0], 4u);
    ASSERT_EQ(sys.group_cpu_base[0], 0u);
    ASSERT_EQ(sys.group_cpu_cap[1], 0u);
    ASSERT_EQ(sys.group_cpu_base[1], 0u);
}

TEST(upload_grouped_rejects_wrapped_sum)
{
    /* u32 accumulator wrap: 0xFFFFFFFF + 2 == 1 (mod 2^32), which the old
     * u32 sum accepted — with group_cpu_cap[0] = 0xFFFFFFFF. The u64
     * accumulator must see through the wrap and reject. */
    IndirectDrawSystem sys;
    make_sys(&sys, 4, 2);
    DrawIndexedIndirectCmd cmds[2] = {{0}};
    const u32 sizes[2] = {0xFFFFFFFFu, 2u};

    indirect_draw_upload_grouped(&sys, NULL, cmds, sizes, 2);

    ASSERT_EQ(sys.current_draw_count, 0u);
    ASSERT_EQ(sys.group_cpu_cap[0], 4u);
    ASSERT_EQ(sys.group_cpu_cap[1], 0u);
}

TEST(upload_grouped_accepts_exact_fit)
{
    IndirectDrawSystem sys;
    make_sys(&sys, 4, 2);
    DrawIndexedIndirectCmd cmds[4] = {{0}};
    const u32 sizes[2] = {3u, 1u}; /* sum 4 == max_draws 4 */

    indirect_draw_upload_grouped(&sys, NULL, cmds, sizes, 2);

    ASSERT_EQ(sys.current_draw_count, 4u);
    ASSERT_EQ(sys.group_cpu_base[0], 0u);
    ASSERT_EQ(sys.group_cpu_cap[0], 3u);
    ASSERT_EQ(sys.group_cpu_base[1], 3u);
    ASSERT_EQ(sys.group_cpu_cap[1], 1u);
}

TEST(upload_grouped_accepts_under_capacity)
{
    IndirectDrawSystem sys;
    make_sys(&sys, 4, 2);
    DrawIndexedIndirectCmd cmds[3] = {{0}};
    const u32 sizes[2] = {2u, 1u}; /* sum 3 < max_draws 4 */

    indirect_draw_upload_grouped(&sys, NULL, cmds, sizes, 2);

    ASSERT_EQ(sys.current_draw_count, 3u);
    ASSERT_EQ(sys.group_cpu_base[0], 0u);
    ASSERT_EQ(sys.group_cpu_cap[0], 2u);
    ASSERT_EQ(sys.group_cpu_base[1], 2u);
    ASSERT_EQ(sys.group_cpu_cap[1], 1u);
}

TEST(upload_grouped_rejects_excess_group_count)
{
    /* R437 pin (pre-existing guard): more groups than init reserved. */
    IndirectDrawSystem sys;
    make_sys(&sys, 4, 2);
    DrawIndexedIndirectCmd cmds[3] = {{0}};
    const u32 sizes[3] = {1u, 1u, 1u};

    indirect_draw_upload_grouped(&sys, NULL, cmds, sizes, 3);

    ASSERT_EQ(sys.current_draw_count, 0u);
    ASSERT_EQ(sys.group_cpu_cap[0], 4u);
}

TEST(upload_ungrouped_rejects_over_max)
{
    /* R482 behavior change: indirect_draw_upload used to silently clamp
     * count to max_draws; it now rejects through the grouped path. */
    IndirectDrawSystem sys;
    make_sys(&sys, 4, 1);
    DrawIndexedIndirectCmd cmds[5] = {{0}};

    indirect_draw_upload(&sys, NULL, cmds, 5);

    ASSERT_EQ(sys.current_draw_count, 0u);
    ASSERT_EQ(sys.group_cpu_cap[0], 4u);
}

TEST(upload_grouped_guard_clauses)
{
    IndirectDrawSystem sys;
    make_sys(&sys, 4, 2);
    DrawIndexedIndirectCmd cmds[2] = {{0}};
    const u32 sizes[2] = {1u, 1u};

    sys.ready = false; /* destroyed / never-initialized system */
    indirect_draw_upload_grouped(&sys, NULL, cmds, sizes, 2);
    ASSERT_EQ(sys.current_draw_count, 0u);
    sys.ready = true;

    indirect_draw_upload_grouped(&sys, NULL, NULL, sizes, 2);   /* no cmds */
    indirect_draw_upload_grouped(&sys, NULL, cmds, NULL, 2);    /* no sizes */
    indirect_draw_upload_grouped(&sys, NULL, cmds, sizes, 0);   /* no groups */
    indirect_draw_upload_grouped(NULL, NULL, cmds, sizes, 2);   /* no sys */
    ASSERT_EQ(sys.current_draw_count, 0u);

    { /* zero-sum upload is a no-op (pre-existing behavior) */
        const u32 zeros[2] = {0u, 0u};
        indirect_draw_upload_grouped(&sys, NULL, cmds, zeros, 2);
        ASSERT_EQ(sys.current_draw_count, 0u);
    }
}

/* ----------------------------------------------------------------------- */
/*  Execute intervals derive from the validated CPU bookkeeping             */
/* ----------------------------------------------------------------------- */

TEST(execute_group_uses_validated_intervals)
{
    IndirectDrawSystem sys;
    make_sys(&sys, 4, 2);
    DrawIndexedIndirectCmd cmds[4] = {{0}};
    const u32 sizes[2] = {3u, 1u};
    const u32 stride = (u32)sizeof(DrawIndexedIndirectCmd);

    indirect_draw_upload_grouped(&sys, NULL, cmds, sizes, 2);
    ASSERT_EQ(sys.current_draw_count, 4u);

    g_exec_calls = 0;
    indirect_draw_execute_group(&sys, NULL, 0);
    ASSERT_EQ(g_exec_calls, 1u);
    ASSERT_EQ(g_exec_last_cmd_offset, 0u);
    ASSERT_EQ(g_exec_last_max_draws, 3u);
    ASSERT_TRUE(g_exec_last_cmd_offset / stride + g_exec_last_max_draws <= sys.max_draws);

    indirect_draw_execute_group(&sys, NULL, 1);
    ASSERT_EQ(g_exec_calls, 2u);
    ASSERT_EQ(g_exec_last_cmd_offset, 3u * stride);
    ASSERT_EQ(g_exec_last_max_draws, 1u);
    ASSERT_TRUE(g_exec_last_cmd_offset / stride + g_exec_last_max_draws <= sys.max_draws);
}

TEST(execute_group_silent_after_rejected_upload)
{
    /* R482: after a rejected upload current_draw_count stays 0, so neither
     * compact nor execute may issue GPU work for the stale intervals. */
    IndirectDrawSystem sys;
    make_sys(&sys, 4, 2);
    DrawIndexedIndirectCmd cmds[6] = {{0}};
    const u32 sizes[2] = {3u, 3u}; /* rejected: sum 6 > max_draws 4 */

    indirect_draw_upload_grouped(&sys, NULL, cmds, sizes, 2);

    g_exec_calls = 0;
    indirect_draw_execute_group(&sys, NULL, 0);
    indirect_draw_execute_group(&sys, NULL, 1);
    ASSERT_EQ(g_exec_calls, 0u);
}

/* ----------------------------------------------------------------------- */
/*  Main                                                                    */
/* ----------------------------------------------------------------------- */

TEST_MAIN_BEGIN()
    RUN_TEST(upload_grouped_rejects_overflow_sum);
    RUN_TEST(upload_grouped_rejects_wrapped_sum);
    RUN_TEST(upload_grouped_accepts_exact_fit);
    RUN_TEST(upload_grouped_accepts_under_capacity);
    RUN_TEST(upload_grouped_rejects_excess_group_count);
    RUN_TEST(upload_ungrouped_rejects_over_max);
    RUN_TEST(upload_grouped_guard_clauses);
    RUN_TEST(execute_group_uses_validated_intervals);
    RUN_TEST(execute_group_silent_after_rejected_upload);
TEST_MAIN_END()
