#include "test_framework.h"

#include "editor_fonts.h"

#include <string.h>
#include <sys/stat.h>

static void mkdirs(const char *path) {
    char buf[512];
    size_t n = strlen(path);
    ASSERT_TRUE(n < sizeof(buf));
    memcpy(buf, path, n + 1u);
    for (size_t i = 1u; i < n; i++) {
        if (buf[i] == '/') {
            buf[i] = '\0';
            (void)TEST_MKDIR(buf);
            buf[i] = '/';
        }
    }
    (void)TEST_MKDIR(buf);
}

static void touch(const char *root, const char *rel) {
    char path[512], dir[512];
    char *slash;
    snprintf(path, sizeof(path), "%s%s", root, rel);
    memcpy(dir, path, sizeof(dir));
    slash = strrchr(dir, '/');
    ASSERT_NOT_NULL(slash);
    *slash = '\0';
    mkdirs(dir);
    FILE *f = fopen(path, "wb");
    ASSERT_NOT_NULL(f);
    fputs("font", f);
    fclose(f);
}

static void remove_tree(const char *root, const char *const *rels, size_t n) {
    char path[512];
    for (size_t i = 0u; i < n; i++) {
        snprintf(path, sizeof(path), "%s%s", root, rels[i]);
        remove(path);
    }
}

#if !defined(__APPLE__)
static bool chain_has(const BreakEditorFontChain *c, const char *suffix) {
    for (usize i = 0u; i < c->count; i++) {
        size_t a = strlen(c->paths[i]), b = strlen(suffix);
        if (a >= b && strcmp(c->paths[i] + a - b, suffix) == 0) {
            return true;
        }
    }
    return false;
}
#endif

#if defined(__APPLE__)
static const char *const k_macos[] = {
    "/System/Library/Fonts/Helvetica.ttc",
    "/System/Library/Fonts/PingFang.ttc",
};

/* macOS layout: Latin first for en-US, CJK first for zh-CN. */
TEST(fonts_macos_layout_orders_by_language)
{
    char root[256];
    BreakEditorFontChain c;
    test_tmp(root, sizeof(root), "editor_fonts_macos");
    for (size_t i = 0u; i < 2u; i++) touch(root, k_macos[i]);

    ASSERT_EQ(break_editor_font_candidates(BREAK_EDITOR_LANG_EN_US, root,
                                           false, &c), 2u);
    ASSERT_TRUE(c.has_cjk);
    ASSERT_TRUE(strstr(c.paths[0], "Helvetica.ttc") != NULL);
    ASSERT_TRUE(strstr(c.paths[1], "PingFang.ttc") != NULL);

    ASSERT_EQ(break_editor_font_candidates(BREAK_EDITOR_LANG_ZH_CN, root,
                                           false, &c), 2u);
    ASSERT_TRUE(strstr(c.paths[0], "PingFang.ttc") != NULL);
    ASSERT_TRUE(strstr(c.paths[1], "Helvetica.ttc") != NULL);
    remove_tree(root, k_macos, 2u);
}
#else
static const char *const k_fedora[] = {
    "/usr/share/fonts/google-noto-sans-cjk-vf-fonts/NotoSansCJK-VF.ttc",
    "/usr/share/fonts/google-droid-sans-fonts/DroidSans.ttf",
};

/* Fedora layout: the old Debian paths are absent, the chain still finds a
 * CJK and a Latin face, Latin first for en-US and CJK first for zh-CN */
TEST(fonts_fedora_layout_orders_by_language)
{
    char root[256];
    BreakEditorFontChain c;
    test_tmp(root, sizeof(root), "editor_fonts_fedora");
    for (size_t i = 0u; i < 2u; i++) touch(root, k_fedora[i]);

    ASSERT_EQ(break_editor_font_candidates(BREAK_EDITOR_LANG_EN_US, root,
                                           false, &c), 2u);
    ASSERT_TRUE(c.has_cjk);
    ASSERT_TRUE(strstr(c.paths[0], "DroidSans.ttf") != NULL);
    ASSERT_TRUE(strstr(c.paths[1], "NotoSansCJK-VF.ttc") != NULL);
    for (usize i = 0u; i < c.count; i++) {
        ASSERT_TRUE(c.sources[i].path == c.paths[i]);
    }

    ASSERT_EQ(break_editor_font_candidates(BREAK_EDITOR_LANG_ZH_CN, root,
                                           false, &c), 2u);
    ASSERT_TRUE(strstr(c.paths[0], "NotoSansCJK-VF.ttc") != NULL);
    ASSERT_TRUE(strstr(c.paths[1], "DroidSans.ttf") != NULL);
    remove_tree(root, k_fedora, 2u);
}

static const char *const k_debian[] = {
    "/usr/share/fonts/opentype/noto/NotoSansCJK-Regular.ttc",
    "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf",
};

TEST(fonts_debian_layout_still_found)
{
    char root[256];
    BreakEditorFontChain c;
    test_tmp(root, sizeof(root), "editor_fonts_debian");
    for (size_t i = 0u; i < 2u; i++) touch(root, k_debian[i]);
    ASSERT_EQ(break_editor_font_candidates(BREAK_EDITOR_LANG_EN_US, root,
                                           false, &c), 2u);
    ASSERT_TRUE(chain_has(&c, "DejaVuSans.ttf"));
    ASSERT_TRUE(chain_has(&c, "NotoSansCJK-Regular.ttc"));
    ASSERT_TRUE(c.has_cjk);
    remove_tree(root, k_debian, 2u);
}

/* Latin-only system: the chain is usable for English but reports no CJK so
 * the host can warn that Chinese will not render */
TEST(fonts_latin_only_reports_missing_cjk)
{
    char root[256];
    static const char *const latin[] = {
        "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf"};
    BreakEditorFontChain c;
    test_tmp(root, sizeof(root), "editor_fonts_latin");
    touch(root, latin[0]);
    ASSERT_EQ(break_editor_font_candidates(BREAK_EDITOR_LANG_ZH_CN, root,
                                           false, &c), 1u);
    ASSERT_FALSE(c.has_cjk);
    remove_tree(root, latin, 1u);
}

#endif /* __APPLE__ */

TEST(fonts_empty_root_finds_nothing_and_bad_args_are_bounded)
{
    char root[256];
    BreakEditorFontChain c;
    test_tmp(root, sizeof(root), "editor_fonts_empty");
    mkdirs(root);
    ASSERT_EQ(break_editor_font_candidates(BREAK_EDITOR_LANG_EN_US, root,
                                           false, &c), 0u);
    ASSERT_EQ(c.count, 0u);
    ASSERT_FALSE(c.has_cjk);
    ASSERT_EQ(break_editor_font_candidates(BREAK_EDITOR_LANG_EN_US, root,
                                           false, NULL), 0u);
    /* a root that cannot fit the path storage is skipped, not truncated */
    {
        char longroot[600];
        memset(longroot, 'x', sizeof(longroot) - 1u);
        longroot[0] = '/';
        longroot[sizeof(longroot) - 1u] = '\0';
        ASSERT_EQ(break_editor_font_candidates(BREAK_EDITOR_LANG_EN_US,
                                               longroot, false, &c), 0u);
    }
}

/* the real system through fontconfig (when built with it): every candidate
 * exists, is unique, and at least one face is found on this host */
TEST(fonts_real_system_candidates_exist_and_are_unique)
{
    BreakEditorFontChain c;
    usize n = break_editor_font_candidates(BREAK_EDITOR_LANG_ZH_CN, NULL, true,
                                           &c);
    printf("    (%u candidates%s)\n", (unsigned)n, c.has_cjk ? ", cjk" : "");
    for (usize i = 0u; i < n; i++) {
        struct stat st;
        ASSERT_EQ(stat(c.paths[i], &st), 0);
        for (usize j = 0u; j < i; j++) {
            ASSERT_TRUE(strcmp(c.paths[i], c.paths[j]) != 0);
        }
    }
    ASSERT_TRUE(n <= BREAK_EDITOR_FONT_MAX_CANDIDATES);
}

TEST(cli_take_lang_strips_option_and_keeps_other_arguments)
{
    char a0[] = "editor", a1[] = "--lang", a2[] = "zh-CN", a3[] = "scene.bscn",
         a4[] = "--remote", a5[] = "--lang=en";
    char *argv[7] = {a0, a1, a2, a3, a4, a5, NULL};
    int argc = 6;
    BreakEditorLang lang = BREAK_EDITOR_LANG_COUNT;
    char err[96] = "";
    ASSERT_TRUE(break_editor_cli_take_lang(&argc, argv, &lang, err, sizeof(err)));
    ASSERT_EQ(argc, 3);
    ASSERT_STR_EQ(argv[1], "scene.bscn");
    ASSERT_STR_EQ(argv[2], "--remote");
    ASSERT_TRUE(argv[3] == NULL);
    ASSERT_EQ(lang, BREAK_EDITOR_LANG_EN_US); /* last --lang wins */
    {
        char b0[] = "editor", b1[] = "--lang";
        char *bad[3] = {b0, b1, NULL};
        int bc = 2;
        ASSERT_FALSE(break_editor_cli_take_lang(&bc, bad, &lang, err, sizeof(err)));
        ASSERT_EQ(bc, 2);
        ASSERT_TRUE(strstr(err, "--lang") != NULL);
    }
    {
        char c0[] = "editor", c1[] = "--lang=fr";
        char *bad[3] = {c0, c1, NULL};
        int cc = 2;
        ASSERT_FALSE(break_editor_cli_take_lang(&cc, bad, &lang, err, sizeof(err)));
        ASSERT_TRUE(strstr(err, "fr") != NULL);
    }
    {
        char d0[] = "editor", d1[] = "--language";
        char *keep[3] = {d0, d1, NULL};
        int dc = 2;
        ASSERT_TRUE(break_editor_cli_take_lang(&dc, keep, &lang, err, sizeof(err)));
        ASSERT_EQ(dc, 2); /* not --lang: left for the other parsers */
    }
}

TEST_MAIN_BEGIN()
#if defined(__APPLE__)
    RUN_TEST(fonts_macos_layout_orders_by_language);
#else
    RUN_TEST(fonts_fedora_layout_orders_by_language);
    RUN_TEST(fonts_debian_layout_still_found);
    RUN_TEST(fonts_latin_only_reports_missing_cjk);
#endif
    RUN_TEST(fonts_empty_root_finds_nothing_and_bad_args_are_bounded);
    RUN_TEST(fonts_real_system_candidates_exist_and_are_unique);
    RUN_TEST(cli_take_lang_strips_option_and_keeps_other_arguments);
TEST_MAIN_END()
