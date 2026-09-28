/* Win32 headless contract tests for the myr desktop GL backend's WGL
 * pointer resolution (my_gl_desktop.c / my_gl_desktop_internal.h).
 *
 * These run without any GL context and lock the documented contract:
 *   - wglProcAddress garbage returns (0, 1, 2, 3, (uintptr_t)-1) are
 *     rejected instead of being cached as callable pointers;
 *   - my_gl_desktop_default() is stable across calls, never crashes
 *     without a current context, and a non-NULL table always carries
 *     the slots the vgcanvas backend requires.
 *
 * This test deliberately creates no GL context: on a headless CI host
 * resolution legitimately fails and default() must return NULL; on a
 * machine with a driver that resolves entry points without a context
 * (permitted but not required by the WGL spec) the table must still be
 * internally consistent. The real end-to-end path is covered by
 * test_myui_gl_desktop_runtime (graphics label). */
#include "test_framework.h"

#include "myr/my_gl.h"
#include "myr/my_gl_desktop.h"
#include "myr/my_gl_desktop_internal.h"

#include <stdint.h>

static void required_slots_are_populated(const my_gl_t* gl) {
    ASSERT_NOT_NULL(gl->viewport);
    ASSERT_NOT_NULL(gl->enable_scissor);
    ASSERT_NOT_NULL(gl->scissor);
    ASSERT_NOT_NULL(gl->clear_color);
    ASSERT_NOT_NULL(gl->clear);
    ASSERT_NOT_NULL(gl->create_program);
    ASSERT_NOT_NULL(gl->delete_program);
    ASSERT_NOT_NULL(gl->use_program);
    ASSERT_NOT_NULL(gl->uniform2f);
    ASSERT_NOT_NULL(gl->uniform4f);
    ASSERT_NOT_NULL(gl->draw_arrays_triangles);
    ASSERT_NOT_NULL(gl->create_texture);
    ASSERT_NOT_NULL(gl->create_texture_rgba);
    ASSERT_NOT_NULL(gl->delete_texture);
    ASSERT_NOT_NULL(gl->draw_textured_quads);
    ASSERT_NOT_NULL(gl->shader_header_vs);
    ASSERT_NOT_NULL(gl->shader_header_fs);
}

TEST(wgl_proc_usable_rejects_documented_garbage_addresses)
{
    /* (uintptr_t)-1 covers the 32-bit 0xFFFFFFFF sentinel form. */
    static const uintptr_t garbage[] = {0u, 1u, 2u, 3u, (uintptr_t)-1};
    size_t i;

    for (i = 0; i < sizeof(garbage) / sizeof(garbage[0]); i++) {
        ASSERT_FALSE(my_gl_desktop_wgl_proc_usable(
            my_gl_desktop_proc_from_address(garbage[i])));
    }
}

static void sample_entry_point(void) { /* never called */ }

TEST(wgl_proc_usable_accepts_a_real_function_address)
{
    my_gl_desktop_proc_t proc = my_gl_desktop_proc_from_address(
        my_gl_desktop_proc_to_address(&sample_entry_point));

    ASSERT_TRUE(my_gl_desktop_wgl_proc_usable(proc));
}

TEST(desktop_table_is_stable_without_a_current_context)
{
    const my_gl_t* first = my_gl_desktop_default();
    const my_gl_t* second = my_gl_desktop_default();
    const my_gl_t* third = my_gl_desktop_default();

    /* Resolution is one-shot and cached: every fetch returns the same
     * table (or the same NULL), never a half-resolved mix. */
    ASSERT_EQ(first, second);
    ASSERT_EQ(second, third);
    if (first != NULL) {
        required_slots_are_populated(first);
    }
}

TEST_MAIN_BEGIN()
RUN_TEST(wgl_proc_usable_rejects_documented_garbage_addresses);
RUN_TEST(wgl_proc_usable_accepts_a_real_function_address);
RUN_TEST(desktop_table_is_stable_without_a_current_context);
TEST_MAIN_END()
