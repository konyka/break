/* ==========================================================================
 *  test_script.c — Unit tests for the script engine module.
 * ========================================================================== */

#include "test_framework.h"
#include <script/script.h>
#include <math.h>
#include <stdio.h>

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
    char path[64]; /* R444: per-pid path — parallel ctest trees raced on the fixed name */
    test_tmp(path, sizeof path, "test_script.script");
    FILE *f = fopen(path, "w");
    ASSERT_NOT_NULL(f);
    fprintf(f, "var health = 100\n");
    fprintf(f, "var speed = 5.5\n");
    fprintf(f, "func on_start\n");
    fprintf(f, "    set health 50\n");
    fprintf(f, "    add speed 1.0\n");
    fclose(f);

    ScriptEngine se = {0};
    script_engine_init(&se);
    bool ok = script_load(&se, path);
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
    remove(path); /* R444: was never removed; stale mtime made runs order-dependent */
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
    char path[128];
    test_tmp(path, sizeof path, "no_such_script_xyz.script");
    bool ok = script_load(&se, path);
    ASSERT_TRUE(!ok);
    ASSERT_TRUE(!se.loaded);
    script_engine_shutdown(&se);
}

/* R485: a failed replacement must not discard the script currently running. */
TEST(load_failure_preserves_previous_script)
{
    char path[64];
    test_tmp(path, sizeof path, "test_script_preserve.script");
    FILE *f = fopen(path, "w");
    ASSERT_NOT_NULL(f);
    fprintf(f, "var hp = 7\n");
    fprintf(f, "func damage\n");
    fprintf(f, "    add hp -2\n");
    fclose(f);

    ScriptEngine se = {0};
    script_engine_init(&se);
    ASSERT_TRUE(script_load(&se, path));
    char missing[128];
    test_tmp(missing, sizeof missing, "break_missing_replacement.script");
    ASSERT_FALSE(script_load(&se, missing));
    ASSERT_TRUE(se.loaded);
    ASSERT_EQ(se.func_count, 1u);
    script_call(&se, "damage");
    ASSERT_TRUE(fabsf(script_get_global(&se, "hp") - 5.0f) < 0.001f);

    script_engine_shutdown(&se);
    remove(path);
}

/* Script text is untrusted at load time: sscanf accepts nan/inf, which must
 * not replace an executable script or enter its globals and operation args. */
TEST(load_rejects_nonfinite_values_preserves_previous_script)
{
    char good_path[64], bad_path[64];
    test_tmp(good_path, sizeof good_path, "test_script_finite_good.script");
    test_tmp(bad_path, sizeof bad_path, "test_script_finite_bad.script");
    FILE *f = fopen(good_path, "w");
    ASSERT_NOT_NULL(f);
    fprintf(f, "var hp = 7\n");
    fprintf(f, "func damage\n");
    fprintf(f, "    add hp -2\n");
    fclose(f);

    const char *bad_scripts[] = {
        "var value = nan\n",
        "func run\n    set value inf\n",
        "func run\n    add value nan\n",
        "func run\n    spawn 1 inf nan\n",
    };
    ScriptEngine se = {0};
    script_engine_init(&se);
    ASSERT_TRUE(script_load(&se, good_path));

    for (usize i = 0; i < sizeof(bad_scripts) / sizeof(bad_scripts[0]); i++) {
        f = fopen(bad_path, "w");
        ASSERT_NOT_NULL(f);
        fputs(bad_scripts[i], f);
        fclose(f);

        ASSERT_FALSE(script_load(&se, bad_path));
        ASSERT_TRUE(se.loaded);
        ASSERT_EQ(se.func_count, 1u);
        script_call(&se, "damage");
        ASSERT_TRUE(fabsf(script_get_global(&se, "hp") - (5.0f - 2.0f * (f32)i)) < 0.001f);
    }

    script_engine_shutdown(&se);
    remove(good_path);
    remove(bad_path);
}

TEST(script_comments_ignored)
{
    char path[64]; /* R444: per-pid path */
    test_tmp(path, sizeof path, "test_comment.script");
    FILE *f = fopen(path, "w");
    ASSERT_NOT_NULL(f);
    fprintf(f, "# This is a comment\n");
    fprintf(f, "var x = 42\n");
    fprintf(f, "# Another comment\n");
    fclose(f);

    ScriptEngine se = {0};
    script_engine_init(&se);
    bool ok = script_load(&se, path);
    ASSERT_TRUE(ok);
    ASSERT_EQ(se.global_count, 1u);
    ASSERT_TRUE(fabsf(script_get_global(&se, "x") - 42.0f) < 0.001f);
    script_engine_shutdown(&se);
    remove(path); /* R444: was never removed */
}

TEST(reload_if_changed_is_per_engine)
{
    /* R309: script_reload_if_changed must track the last-seen mtime PER ENGINE,
     * not in a function-local static shared by all engines. Two fresh engines
     * pointed at the same unchanged file must BOTH load it. Pre-fix the shared
     * static made the first call record the file's mtime, so the second engine
     * saw mt==last_mtime, skipped script_load and stayed permanently empty —
     * exactly the failure a level/engine recreate hits. */
    char path[64]; /* R444: per-pid path */
    test_tmp(path, sizeof path, "test_reload_per_engine.script");
    FILE *f = fopen(path, "w");
    ASSERT_NOT_NULL(f);
    fprintf(f, "var hp = 7\n");
    fprintf(f, "func boot\n");
    fprintf(f, "    set hp 3\n");
    fclose(f);

    ScriptEngine a = {0};
    script_engine_init(&a);
    script_reload_if_changed(&a, path);
    ASSERT_TRUE(a.loaded);
    ASSERT_EQ(a.func_count, 1u);
    script_engine_shutdown(&a);

    /* A distinct, freshly-initialized engine reading the SAME (unchanged) file
     * must also load it. Pre-fix: b stays empty (shared static == file mtime). */
    ScriptEngine b = {0};
    script_engine_init(&b);
    ASSERT_EQ(b.last_mtime, 0u);        /* init must zero the per-engine tracker */
    script_reload_if_changed(&b, path);
    ASSERT_TRUE(b.loaded);              /* pre-fix FAILs here (never reloaded) */
    ASSERT_EQ(b.func_count, 1u);
    ASSERT_TRUE(fabsf(script_get_global(&b, "hp") - 7.0f) < 0.001f);
    script_engine_shutdown(&b);
    remove(path); /* R444: was never removed; stale mtime broke this mtime test */
}

/* ----------------------------------------------------------------------- */
/*  Edge Cases                                                              */
/* ----------------------------------------------------------------------- */

TEST(script_empty_file)
{
    char path[64]; /* R444: per-pid path */
    test_tmp(path, sizeof path, "test_empty.script");
    FILE *f = fopen(path, "w");
    ASSERT_NOT_NULL(f);
    /* Write a single space to avoid format-zero-length warning */
    fputc(' ', f);
    fclose(f);

    ScriptEngine se = {0};
    script_engine_init(&se);
    bool ok = script_load(&se, path);
    /* Empty file should load successfully with zero globals/funcs */
    ASSERT_TRUE(ok);
    ASSERT_EQ(se.global_count, 0u);
    ASSERT_EQ(se.func_count, 0u);
    script_engine_shutdown(&se);
    remove(path); /* R444: was never removed */
}

TEST(script_only_comments)
{
    char path[64]; /* R444: per-pid path */
    test_tmp(path, sizeof path, "test_only_comments.script");
    FILE *f = fopen(path, "w");
    ASSERT_NOT_NULL(f);
    fprintf(f, "# Comment 1\n");
    fprintf(f, "# Comment 2\n");
    fprintf(f, "# Comment 3\n");
    fclose(f);

    ScriptEngine se = {0};
    script_engine_init(&se);
    bool ok = script_load(&se, path);
    ASSERT_TRUE(ok);
    ASSERT_EQ(se.global_count, 0u);
    ASSERT_EQ(se.func_count, 0u);
    script_engine_shutdown(&se);
    remove(path); /* R444: was never removed */
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

/* R392: op_count had no cap — a million-line `set x 1` file doubled ops forever. */
TEST(script_rejects_excessive_ops)
{
    char path[64]; /* R444: per-pid path */
    test_tmp(path, sizeof path, "test_ops_cap.script");
    FILE *f = fopen(path, "w");
    ASSERT_NOT_NULL(f);
    fprintf(f, "func spam\n");
    for (u32 i = 0; i < SCRIPT_MAX_OPS + 64u; i++)
        fprintf(f, "set x %u\n", i);
    fclose(f);

    ScriptEngine se = {0};
    script_engine_init(&se);
    bool ok = script_load(&se, path);
    ASSERT_TRUE(ok);
    ASSERT_EQ(se.func_count, 1u);
    ASSERT_EQ(se.funcs[0].op_count, SCRIPT_MAX_OPS);

    script_engine_shutdown(&se);
    remove(path);
}

/* R392: file size had no cap — ftell -> malloc(sz+1) on a multi-GB file. */
TEST(script_rejects_oversized_file)
{
    char path[64]; /* R444: per-pid path */
    test_tmp(path, sizeof path, "test_script_huge.script");
    FILE *f = fopen(path, "wb");
    ASSERT_NOT_NULL(f);
    if (fseek(f, 0, SEEK_SET) != 0) { fclose(f); return; }
    /* Sparse extend past SCRIPT_MAX_FILE_BYTES without writing every byte. */
#if defined(_POSIX_C_SOURCE) && _POSIX_C_SOURCE >= 200112L
    if (ftruncate(fileno(f), (off_t)SCRIPT_MAX_FILE_BYTES + 1) != 0) {
        fclose(f);
        return;
    }
#else
    /* Fallback: write a byte at the end position. */
    if (fseek(f, (long)SCRIPT_MAX_FILE_BYTES, SEEK_SET) != 0) { fclose(f); return; }
    fputc('x', f);
#endif
    fclose(f);

    ScriptEngine se = {0};
    script_engine_init(&se);
    ASSERT_TRUE(!script_load(&se, path));
    script_engine_shutdown(&se);
    remove(path);
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

/* Over-cap `func` lines are rejected at SCRIPT_MAX_CALLBACKS; the ops that
 * follow them must be dropped, not appended to the last accepted function. */
TEST(script_over_cap_function_ops_dropped)
{
    char path[64]; /* R444: per-pid path */
    test_tmp(path, sizeof path, "test_func_cap.script");
    FILE *f = fopen(path, "w");
    ASSERT_NOT_NULL(f);
    for (u32 i = 0; i < SCRIPT_MAX_CALLBACKS; i++)
        fprintf(f, "func f%u\n", i);
    fprintf(f, "func overflow\n");
    fprintf(f, "set x 1\n");
    fclose(f);

    ScriptEngine se = {0};
    script_engine_init(&se);
    bool ok = script_load(&se, path);
    ASSERT_TRUE(ok);
    ASSERT_EQ(se.func_count, (u32)SCRIPT_MAX_CALLBACKS);
    /* The rejected function's op must NOT have leaked into the last function. */
    ASSERT_EQ(se.funcs[SCRIPT_MAX_CALLBACKS - 1].op_count, 0u);

    script_engine_shutdown(&se);
    remove(path);
}

TEST_MAIN_BEGIN()
    RUN_TEST(init_shutdown);
    RUN_TEST(set_get_global);
    RUN_TEST(set_global_overwrite);
    RUN_TEST(get_global_missing);
    RUN_TEST(multiple_globals);
    RUN_TEST(load_from_file);
    RUN_TEST(call_nonexistent_func);
    RUN_TEST(load_nonexistent_file);
    RUN_TEST(load_failure_preserves_previous_script);
    RUN_TEST(load_rejects_nonfinite_values_preserves_previous_script);
    RUN_TEST(script_comments_ignored);
    RUN_TEST(reload_if_changed_is_per_engine);
    /* Edge cases */
    RUN_TEST(script_empty_file);
    RUN_TEST(script_only_comments);
    RUN_TEST(script_negative_values);
    RUN_TEST(script_rejects_excessive_ops);
    RUN_TEST(script_over_cap_function_ops_dropped);
    RUN_TEST(script_rejects_oversized_file);
    RUN_TEST(script_large_values);
TEST_MAIN_END()
