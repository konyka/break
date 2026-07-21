/* ==========================================================================
 *  test_script.c — Unit tests for the script engine module.
 * ========================================================================== */

#include "test_framework.h"
#include <script/script.h>
#include <math.h>

/* ----------------------------------------------------------------------- */

TEST(init_shutdown)
{
    ScriptEngine se = {0};
    script_engine_init(&se);
    ASSERT_EQ(se.func_count, 0u);
    ASSERT_EQ(se.global_count, 0u);
    ASSERT_TRUE(!se.loaded);
    script_engine_shutdown(&se);
}

TEST(set_get_global)
{
    ScriptEngine se = {0};
    script_engine_init(&se);
    script_set_global(&se, "speed", 5.0f);
    f32 v = script_get_global(&se, "speed");
    ASSERT_TRUE(fabsf(v - 5.0f) < 0.001f);
    script_engine_shutdown(&se);
}

TEST(set_global_overwrite)
{
    ScriptEngine se = {0};
    script_engine_init(&se);
    script_set_global(&se, "x", 1.0f);
    script_set_global(&se, "x", 99.0f);
    ASSERT_TRUE(fabsf(script_get_global(&se, "x") - 99.0f) < 0.001f);
    ASSERT_EQ(se.global_count, 1u);
    script_engine_shutdown(&se);
}

TEST(get_global_missing)
{
    ScriptEngine se = {0};
    script_engine_init(&se);
    f32 v = script_get_global(&se, "nonexistent");
    ASSERT_TRUE(fabsf(v) < 0.001f);
    script_engine_shutdown(&se);
}

TEST(multiple_globals)
{
    ScriptEngine se = {0};
    script_engine_init(&se);
    script_set_global(&se, "a", 1.0f);
    script_set_global(&se, "b", 2.0f);
    script_set_global(&se, "c", 3.0f);
    ASSERT_EQ(se.global_count, 3u);
    ASSERT_TRUE(fabsf(script_get_global(&se, "b") - 2.0f) < 0.001f);
    script_engine_shutdown(&se);
}

TEST(load_from_file)
{
    /* Write a temp script file */
    FILE *f = fopen("/tmp/test_script.script", "w");
    ASSERT_NOT_NULL(f);
    fprintf(f, "var health = 100\n");
    fprintf(f, "var speed = 5.5\n");
    fprintf(f, "func on_start\n");
    fprintf(f, "    set health 50\n");
    fprintf(f, "    add speed 1.0\n");
    fclose(f);

    ScriptEngine se = {0};
    script_engine_init(&se);
    bool ok = script_load(&se, "/tmp/test_script.script");
    ASSERT_TRUE(ok);
    ASSERT_TRUE(se.loaded);
    ASSERT_EQ(se.global_count, 2u);
    ASSERT_EQ(se.func_count, 1u);

    /* Check initial values */
    ASSERT_TRUE(fabsf(script_get_global(&se, "health") - 100.0f) < 0.001f);
    ASSERT_TRUE(fabsf(script_get_global(&se, "speed") - 5.5f) < 0.001f);

    /* Call function: should set health=50, add 1.0 to speed */
    script_call(&se, "on_start");
    ASSERT_TRUE(fabsf(script_get_global(&se, "health") - 50.0f) < 0.001f);
    ASSERT_TRUE(fabsf(script_get_global(&se, "speed") - 6.5f) < 0.001f);

    script_engine_shutdown(&se);
}

TEST(call_nonexistent_func)
{
    ScriptEngine se = {0};
    script_engine_init(&se);
    /* Should not crash */
    script_call(&se, "no_such_func");
    script_engine_shutdown(&se);
}

TEST(load_nonexistent_file)
{
    ScriptEngine se = {0};
    script_engine_init(&se);
    bool ok = script_load(&se, "/tmp/nonexistent_script_xyz.script");
    ASSERT_TRUE(!ok);
    ASSERT_TRUE(!se.loaded);
    script_engine_shutdown(&se);
}

TEST(script_comments_ignored)
{
    FILE *f = fopen("/tmp/test_comment.script", "w");
    ASSERT_NOT_NULL(f);
    fprintf(f, "# This is a comment\n");
    fprintf(f, "var x = 42\n");
    fprintf(f, "# Another comment\n");
    fclose(f);

    ScriptEngine se = {0};
    script_engine_init(&se);
    bool ok = script_load(&se, "/tmp/test_comment.script");
    ASSERT_TRUE(ok);
    ASSERT_EQ(se.global_count, 1u);
    ASSERT_TRUE(fabsf(script_get_global(&se, "x") - 42.0f) < 0.001f);
    script_engine_shutdown(&se);
}

TEST(reload_if_changed_is_per_engine)
{
    /* R309: script_reload_if_changed must track the last-seen mtime PER ENGINE,
     * not in a function-local static shared by all engines. Two fresh engines
     * pointed at the same unchanged file must BOTH load it. Pre-fix the shared
     * static made the first call record the file's mtime, so the second engine
     * saw mt==last_mtime, skipped script_load and stayed permanently empty —
     * exactly the failure a level/engine recreate hits. */
    FILE *f = fopen("/tmp/test_reload_per_engine.script", "w");
    ASSERT_NOT_NULL(f);
    fprintf(f, "var hp = 7\n");
    fprintf(f, "func boot\n");
    fprintf(f, "    set hp 3\n");
    fclose(f);

    ScriptEngine a = {0};
    script_engine_init(&a);
    script_reload_if_changed(&a, "/tmp/test_reload_per_engine.script");
    ASSERT_TRUE(a.loaded);
    ASSERT_EQ(a.func_count, 1u);
    script_engine_shutdown(&a);

    /* A distinct, freshly-initialized engine reading the SAME (unchanged) file
     * must also load it. Pre-fix: b stays empty (shared static == file mtime). */
    ScriptEngine b = {0};
    script_engine_init(&b);
    ASSERT_EQ(b.last_mtime, 0u);        /* init must zero the per-engine tracker */
    script_reload_if_changed(&b, "/tmp/test_reload_per_engine.script");
    ASSERT_TRUE(b.loaded);              /* pre-fix FAILs here (never reloaded) */
    ASSERT_EQ(b.func_count, 1u);
    ASSERT_TRUE(fabsf(script_get_global(&b, "hp") - 7.0f) < 0.001f);
    script_engine_shutdown(&b);
}

/* ----------------------------------------------------------------------- */
/*  Edge Cases                                                              */
/* ----------------------------------------------------------------------- */

TEST(script_empty_file)
{
    FILE *f = fopen("/tmp/test_empty.script", "w");
    ASSERT_NOT_NULL(f);
    /* Write a single space to avoid format-zero-length warning */
    fputc(' ', f);
    fclose(f);

    ScriptEngine se = {0};
    script_engine_init(&se);
    bool ok = script_load(&se, "/tmp/test_empty.script");
    /* Empty file should load successfully with zero globals/funcs */
    ASSERT_TRUE(ok);
    ASSERT_EQ(se.global_count, 0u);
    ASSERT_EQ(se.func_count, 0u);
    script_engine_shutdown(&se);
}

TEST(script_only_comments)
{
    FILE *f = fopen("/tmp/test_only_comments.script", "w");
    ASSERT_NOT_NULL(f);
    fprintf(f, "# Comment 1\n");
    fprintf(f, "# Comment 2\n");
    fprintf(f, "# Comment 3\n");
    fclose(f);

    ScriptEngine se = {0};
    script_engine_init(&se);
    bool ok = script_load(&se, "/tmp/test_only_comments.script");
    ASSERT_TRUE(ok);
    ASSERT_EQ(se.global_count, 0u);
    ASSERT_EQ(se.func_count, 0u);
    script_engine_shutdown(&se);
}

TEST(script_negative_values)
{
    ScriptEngine se = {0};
    script_engine_init(&se);
    script_set_global(&se, "neg", -42.5f);
    f32 v = script_get_global(&se, "neg");
    ASSERT_TRUE(fabsf(v - (-42.5f)) < 0.001f);
    script_engine_shutdown(&se);
}

TEST(script_large_values)
{
    ScriptEngine se = {0};
    script_engine_init(&se);
    script_set_global(&se, "big", 1e10f);
    f32 v = script_get_global(&se, "big");
    ASSERT_TRUE(fabsf(v - 1e10f) < 1e6f);
    script_engine_shutdown(&se);
}

/* ----------------------------------------------------------------------- */

TEST_MAIN_BEGIN()
    RUN_TEST(init_shutdown);
    RUN_TEST(set_get_global);
    RUN_TEST(set_global_overwrite);
    RUN_TEST(get_global_missing);
    RUN_TEST(multiple_globals);
    RUN_TEST(load_from_file);
    RUN_TEST(call_nonexistent_func);
    RUN_TEST(load_nonexistent_file);
    RUN_TEST(script_comments_ignored);
    RUN_TEST(reload_if_changed_is_per_engine);
    /* Edge cases */
    RUN_TEST(script_empty_file);
    RUN_TEST(script_only_comments);
    RUN_TEST(script_negative_values);
    RUN_TEST(script_large_values);
TEST_MAIN_END()
