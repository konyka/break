#include "test_framework.h"

#include "editor_settings.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

/* parse: known keys, unknown keys ignored, bad values keep defaults */
TEST(parse_reads_known_keys_and_ignores_the_rest)
{
    BreakEditorSettings s;
    const char *text =
        "# editor settings\n"
        "theme=light\n"
        "lang=zh-CN\n"
        "bottom_tab=1\n"
        "diag_tab=2\n"
        "future_key=whatever\n";
    break_editor_settings_defaults(&s);
    ASSERT_TRUE(break_editor_settings_parse(&s, text, strlen(text)));
    ASSERT_TRUE(s.light_theme);
    ASSERT_TRUE(s.has_lang);
    ASSERT_EQ(s.lang, BREAK_EDITOR_LANG_ZH_CN);
    ASSERT_EQ(s.bottom_tab, 1u);
    ASSERT_EQ(s.diag_tab, 2u);
}

TEST(parse_bad_values_keep_defaults)
{
    BreakEditorSettings s;
    const char *text = "theme=purple\nlang=xx-YY\nbottom_tab=9\ndiag_tab=-1\n"
                       "no_equals_line\n=\n";
    break_editor_settings_defaults(&s);
    ASSERT_TRUE(break_editor_settings_parse(&s, text, strlen(text)));
    ASSERT_FALSE(s.light_theme);
    ASSERT_FALSE(s.has_lang);
    ASSERT_EQ(s.bottom_tab, 0u);
    ASSERT_EQ(s.diag_tab, 0u);
    /* CRLF and spaces around '=' are tolerated */
    {
        const char *crlf = "theme = light\r\ndiag_tab= 1 \r\n";
        break_editor_settings_defaults(&s);
        ASSERT_TRUE(break_editor_settings_parse(&s, crlf, strlen(crlf)));
        ASSERT_TRUE(s.light_theme);
        ASSERT_EQ(s.diag_tab, 1u);
    }
    ASSERT_FALSE(break_editor_settings_parse(NULL, "x", 1u));
    ASSERT_FALSE(break_editor_settings_parse(&s, NULL, 1u));
}

TEST(serialize_round_trips)
{
    BreakEditorSettings a, b;
    char buf[256];
    usize n;
    break_editor_settings_defaults(&a);
    a.light_theme = true;
    a.has_lang = true;
    a.lang = BREAK_EDITOR_LANG_ZH_CN;
    a.bottom_tab = 1u;
    a.diag_tab = 2u;
    n = break_editor_settings_serialize(&a, buf, sizeof(buf));
    ASSERT_TRUE(n > 0u && n < sizeof(buf));
    break_editor_settings_defaults(&b);
    ASSERT_TRUE(break_editor_settings_parse(&b, buf, n));
    ASSERT_TRUE(b.light_theme);
    ASSERT_TRUE(b.has_lang && b.lang == BREAK_EDITOR_LANG_ZH_CN);
    ASSERT_EQ(b.bottom_tab, 1u);
    ASSERT_EQ(b.diag_tab, 2u);
    /* too-small buffer: nothing written, 0 returned */
    ASSERT_EQ(break_editor_settings_serialize(&a, buf, 8u), 0u);
}

/* default path: $XDG_CONFIG_HOME/break/editor.ini, else ~/.config/...;
 * on Windows %APPDATA%/break/editor.ini (and nothing without APPDATA) */
TEST(default_path_follows_xdg_then_home)
{
    char path[512];
    /* the override must not leak in from the caller's environment */
    ASSERT_EQ(TEST_UNSETENV("BREAK_EDITOR_SETTINGS"), 0);
#if defined(_WIN32)
    ASSERT_EQ(TEST_SETENV("APPDATA", "C:/appdata-test"), 0);
    ASSERT_TRUE(break_editor_settings_default_path(path, sizeof(path)));
    ASSERT_STR_EQ(path, "C:/appdata-test/break/editor.ini");
    ASSERT_FALSE(break_editor_settings_default_path(path, 8u));
    ASSERT_EQ(TEST_UNSETENV("APPDATA"), 0);
    ASSERT_FALSE(break_editor_settings_default_path(path, sizeof(path)));
#else
    ASSERT_EQ(TEST_SETENV("XDG_CONFIG_HOME", "/tmp/xdg-test"), 0);
    ASSERT_TRUE(break_editor_settings_default_path(path, sizeof(path)));
    ASSERT_STR_EQ(path, "/tmp/xdg-test/break/editor.ini");
    ASSERT_EQ(TEST_UNSETENV("XDG_CONFIG_HOME"), 0);
    ASSERT_EQ(TEST_SETENV("HOME", "/tmp/home-test"), 0);
    ASSERT_TRUE(break_editor_settings_default_path(path, sizeof(path)));
    ASSERT_STR_EQ(path, "/tmp/home-test/.config/break/editor.ini");
    ASSERT_FALSE(break_editor_settings_default_path(path, 8u));
#endif
    /* BREAK_EDITOR_SETTINGS overrides everything (tests, portable installs) */
    ASSERT_EQ(TEST_SETENV("BREAK_EDITOR_SETTINGS", "/tmp/x/editor.ini"), 0);
    ASSERT_TRUE(break_editor_settings_default_path(path, sizeof(path)));
    ASSERT_STR_EQ(path, "/tmp/x/editor.ini");
    ASSERT_EQ(TEST_UNSETENV("BREAK_EDITOR_SETTINGS"), 0);
}

/* save creates the parent directory and writes atomically; load reads it
 * back; a missing file loads defaults (not an error) */
TEST(save_then_load_through_the_file_system)
{
    char dir[256], path[320];
    BreakEditorSettings a, b;
    test_tmp(dir, sizeof(dir), "editor_settings");
    snprintf(path, sizeof(path), "%s/sub/editor.ini", dir);
    remove(path);
    break_editor_settings_defaults(&b);
    ASSERT_TRUE(break_editor_settings_load(&b, path)); /* missing = defaults */
    ASSERT_FALSE(b.light_theme);
    break_editor_settings_defaults(&a);
    a.light_theme = true;
    a.diag_tab = 1u;
    ASSERT_TRUE(break_editor_settings_save(&a, path));
    break_editor_settings_defaults(&b);
    ASSERT_TRUE(break_editor_settings_load(&b, path));
    ASSERT_TRUE(b.light_theme);
    ASSERT_EQ(b.diag_tab, 1u);
    ASSERT_FALSE(b.has_lang);
    remove(path);
    {
        char sub[300];
        snprintf(sub, sizeof(sub), "%s/sub", dir);
        TEST_RMDIR(sub);
        TEST_RMDIR(dir);
    }
    ASSERT_FALSE(break_editor_settings_save(NULL, path));
    ASSERT_FALSE(break_editor_settings_load(&b, NULL));
}

TEST_MAIN_BEGIN()
    RUN_TEST(parse_reads_known_keys_and_ignores_the_rest);
    RUN_TEST(parse_bad_values_keep_defaults);
    RUN_TEST(serialize_round_trips);
    RUN_TEST(default_path_follows_xdg_then_home);
    RUN_TEST(save_then_load_through_the_file_system);
TEST_MAIN_END()
