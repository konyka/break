#define _POSIX_C_SOURCE 200809L /* setenv/unsetenv/strdup */
#include "test_framework.h"

#include <editor/editor_components.h>
#include <editor/editor_i18n.h>

#include <stdlib.h>
#include <string.h>

/* Strict UTF-8 validation: rejects overlongs, surrogates and > U+10FFFF. */
static bool utf8_valid(const char *s) {
    const unsigned char *p = (const unsigned char *)s;
    while (*p != 0u) {
        unsigned cp;
        int extra;
        if (*p < 0x80u) {
            p++;
            continue;
        }
        if ((*p & 0xE0u) == 0xC0u) {
            cp = *p & 0x1Fu;
            extra = 1;
        } else if ((*p & 0xF0u) == 0xE0u) {
            cp = *p & 0x0Fu;
            extra = 2;
        } else if ((*p & 0xF8u) == 0xF0u) {
            cp = *p & 0x07u;
            extra = 3;
        } else {
            return false;
        }
        p++;
        for (int i = 0; i < extra; i++, p++) {
            if ((*p & 0xC0u) != 0x80u) {
                return false;
            }
            cp = (cp << 6) | (*p & 0x3Fu);
        }
        if ((extra == 1 && cp < 0x80u) || (extra == 2 && cp < 0x800u) ||
            (extra == 3 && cp < 0x10000u) || cp > 0x10FFFFu ||
            (cp >= 0xD800u && cp <= 0xDFFFu)) {
            return false;
        }
    }
    return true;
}

/* The printf conversion sequence of a format ("%s|%u|%.3g" -> "s u g"),
 * ignoring flags/width/precision and "%%". */
static void conversions(const char *fmt, char *out, size_t cap) {
    size_t n = 0u;
    out[0] = '\0';
    for (const char *p = fmt; *p != '\0'; p++) {
        if (*p != '%') {
            continue;
        }
        p++;
        if (*p == '%') {
            continue;
        }
        while (*p != '\0' && strchr("-+ #0123456789.", *p) != NULL) {
            p++;
        }
        while (*p == 'l' || *p == 'h' || *p == 'z') {
            if (n + 1u < cap) out[n++] = *p;
            p++;
        }
        if (*p == '\0') {
            break;
        }
        if (n + 2u < cap) {
            out[n++] = *p;
            out[n++] = ' ';
        }
    }
    out[n] = '\0';
}

TEST(every_language_fills_every_key_with_valid_utf8)
{
    for (int lang = 0; lang < BREAK_EDITOR_LANG_COUNT; lang++) {
        for (int key = 0; key < BREAK_EDITOR_TR_COUNT; key++) {
            const char *s =
                break_editor_tr_lang((BreakEditorLang)lang, (BreakEditorTr)key);
            ASSERT_NOT_NULL(s);
            if (s[0] == '\0' || strcmp(s, "?") == 0 || !utf8_valid(s)) {
                printf("    lang %d key %d: '%s'\n", lang, key, s);
            }
            ASSERT_TRUE(s[0] != '\0');
            ASSERT_TRUE(strcmp(s, "?") != 0);
            ASSERT_TRUE(utf8_valid(s));
        }
    }
}

/* A key whose zh-CN text equals en-US was almost certainly left untranslated. */
TEST(chinese_table_is_actually_translated)
{
    for (int key = 0; key < BREAK_EDITOR_TR_COUNT; key++) {
        const char *en = break_editor_tr_lang(BREAK_EDITOR_LANG_EN_US,
                                              (BreakEditorTr)key);
        const char *zh = break_editor_tr_lang(BREAK_EDITOR_LANG_ZH_CN,
                                              (BreakEditorTr)key);
        if (strcmp(en, zh) == 0) {
            printf("    key %d untranslated: '%s'\n", key, en);
        }
        ASSERT_TRUE(strcmp(en, zh) != 0);
    }
}

TEST(format_keys_keep_identical_conversions_across_languages)
{
    for (int key = 0; key < BREAK_EDITOR_TR_COUNT; key++) {
        char en_conv[64], other_conv[64];
        conversions(break_editor_tr_lang(BREAK_EDITOR_LANG_EN_US,
                                         (BreakEditorTr)key),
                    en_conv, sizeof(en_conv));
        for (int lang = 1; lang < BREAK_EDITOR_LANG_COUNT; lang++) {
            conversions(break_editor_tr_lang((BreakEditorLang)lang,
                                             (BreakEditorTr)key),
                        other_conv, sizeof(other_conv));
            if (strcmp(en_conv, other_conv) != 0) {
                printf("    key %d lang %d: '%s' vs '%s'\n", key, lang,
                       en_conv, other_conv);
            }
            ASSERT_STR_EQ(en_conv, other_conv);
        }
    }
    /* the documented shapes of two format keys */
    {
        char buf[160];
        ASSERT_TRUE(break_editor_i18n_set_lang(BREAK_EDITOR_LANG_ZH_CN));
        (void)snprintf(buf, sizeof(buf),
                       break_editor_tr(BREAK_EDITOR_TR_TOOL_LABEL_FMT),
                       break_editor_tr(BREAK_EDITOR_TR_TOOL_SCALE));
        ASSERT_TRUE(strstr(buf, break_editor_tr(BREAK_EDITOR_TR_TOOL_SCALE)) !=
                    NULL);
        (void)snprintf(buf, sizeof(buf),
                       break_editor_tr(BREAK_EDITOR_TR_STATUS_FMT), 3ull, 1,
                       "add", "-");
        ASSERT_TRUE(strstr(buf, "3") != NULL);
        ASSERT_TRUE(break_editor_i18n_set_lang(BREAK_EDITOR_LANG_EN_US));
    }
}

TEST(current_language_switches_and_rejects_out_of_range)
{
    ASSERT_TRUE(break_editor_i18n_set_lang(BREAK_EDITOR_LANG_EN_US));
    ASSERT_EQ(break_editor_i18n_lang(), BREAK_EDITOR_LANG_EN_US);
    ASSERT_STR_EQ(break_editor_tr(BREAK_EDITOR_TR_ADD), "Add");
    ASSERT_TRUE(break_editor_i18n_set_lang(BREAK_EDITOR_LANG_ZH_CN));
    ASSERT_EQ(break_editor_i18n_lang(), BREAK_EDITOR_LANG_ZH_CN);
    ASSERT_STR_EQ(break_editor_tr(BREAK_EDITOR_TR_ADD), "添加");
    ASSERT_FALSE(break_editor_i18n_set_lang(BREAK_EDITOR_LANG_COUNT));
    ASSERT_FALSE(break_editor_i18n_set_lang((BreakEditorLang)-1));
    ASSERT_EQ(break_editor_i18n_lang(), BREAK_EDITOR_LANG_ZH_CN);
    ASSERT_STR_EQ(break_editor_tr(BREAK_EDITOR_TR_COUNT), "?");
    ASSERT_STR_EQ(break_editor_tr((BreakEditorTr)-3), "?");
    ASSERT_STR_EQ(break_editor_tr_lang(BREAK_EDITOR_LANG_COUNT,
                                       BREAK_EDITOR_TR_ADD),
                  "Add"); /* unknown language -> en-US */
    ASSERT_TRUE(break_editor_i18n_set_lang(BREAK_EDITOR_LANG_EN_US));
}

TEST(language_tags_and_names)
{
    ASSERT_STR_EQ(break_editor_i18n_lang_tag(BREAK_EDITOR_LANG_EN_US), "en-US");
    ASSERT_STR_EQ(break_editor_i18n_lang_tag(BREAK_EDITOR_LANG_ZH_CN), "zh-CN");
    ASSERT_STR_EQ(break_editor_i18n_lang_tag(BREAK_EDITOR_LANG_COUNT), "?");
    ASSERT_STR_EQ(break_editor_i18n_lang_name(BREAK_EDITOR_LANG_EN_US),
                  "English");
    ASSERT_STR_EQ(break_editor_i18n_lang_name(BREAK_EDITOR_LANG_ZH_CN), "中文");
    ASSERT_STR_EQ(break_editor_i18n_lang_name(BREAK_EDITOR_LANG_COUNT), "?");
}

TEST(parse_lang_accepts_bcp47_and_posix_tags)
{
    static const struct {
        const char *tag;
        BreakEditorLang lang;
    } ok[] = {
        {"zh-CN", BREAK_EDITOR_LANG_ZH_CN},   {"zh_CN.UTF-8", BREAK_EDITOR_LANG_ZH_CN},
        {"ZH", BREAK_EDITOR_LANG_ZH_CN},      {"zh-Hans", BREAK_EDITOR_LANG_ZH_CN},
        {"zh_CN@pinyin", BREAK_EDITOR_LANG_ZH_CN},
        {"en", BREAK_EDITOR_LANG_EN_US},      {"en_US.utf8", BREAK_EDITOR_LANG_EN_US},
        {"EN-gb", BREAK_EDITOR_LANG_EN_US},   {"C", BREAK_EDITOR_LANG_EN_US},
        {"C.UTF-8", BREAK_EDITOR_LANG_EN_US}, {"POSIX", BREAK_EDITOR_LANG_EN_US},
    };
    static const char *const bad[] = {"", "fr", "fr_FR.UTF-8", "zhx", "e",
                                      "-", "_CN", "chinese"};
    for (size_t i = 0u; i < sizeof(ok) / sizeof(ok[0]); i++) {
        BreakEditorLang lang = BREAK_EDITOR_LANG_COUNT;
        if (!break_editor_i18n_parse_lang(ok[i].tag, &lang)) {
            printf("    rejected '%s'\n", ok[i].tag);
        }
        ASSERT_TRUE(break_editor_i18n_parse_lang(ok[i].tag, &lang));
        ASSERT_EQ(lang, ok[i].lang);
    }
    for (size_t i = 0u; i < sizeof(bad) / sizeof(bad[0]); i++) {
        BreakEditorLang lang = BREAK_EDITOR_LANG_ZH_CN;
        if (break_editor_i18n_parse_lang(bad[i], &lang)) {
            printf("    accepted '%s'\n", bad[i]);
        }
        ASSERT_FALSE(break_editor_i18n_parse_lang(bad[i], &lang));
        ASSERT_EQ(lang, BREAK_EDITOR_LANG_ZH_CN); /* untouched */
    }
    {
        BreakEditorLang lang;
        ASSERT_FALSE(break_editor_i18n_parse_lang(NULL, &lang));
        ASSERT_FALSE(break_editor_i18n_parse_lang("zh", NULL));
    }
}

#if !defined(_WIN32)
typedef struct {
    char *saved[4];
    bool had[4];
} EnvSnapshot;
static const char *const k_env_names[4] = {"BREAK_LANG", "LC_ALL",
                                           "LC_MESSAGES", "LANG"};

static void env_save(EnvSnapshot *s) {
    for (int i = 0; i < 4; i++) {
        const char *v = getenv(k_env_names[i]);
        s->had[i] = v != NULL;
        s->saved[i] = v != NULL ? strdup(v) : NULL;
        unsetenv(k_env_names[i]);
    }
}

static void env_restore(EnvSnapshot *s) {
    for (int i = 0; i < 4; i++) {
        if (s->had[i]) {
            setenv(k_env_names[i], s->saved[i], 1);
        } else {
            unsetenv(k_env_names[i]);
        }
        free(s->saved[i]);
    }
}
#endif

TEST(lang_from_env_follows_priority_and_skips_unparseable)
{
#if defined(_WIN32)
    return; /* POSIX locale variables; Windows uses the default */
#else
    EnvSnapshot snap;
    env_save(&snap);
    ASSERT_EQ(break_editor_i18n_lang_from_env(), BREAK_EDITOR_LANG_EN_US);
    setenv("LANG", "zh_CN.UTF-8", 1);
    ASSERT_EQ(break_editor_i18n_lang_from_env(), BREAK_EDITOR_LANG_ZH_CN);
    setenv("LC_MESSAGES", "en_US.UTF-8", 1);
    ASSERT_EQ(break_editor_i18n_lang_from_env(), BREAK_EDITOR_LANG_EN_US);
    setenv("LC_ALL", "zh_CN.UTF-8", 1);
    ASSERT_EQ(break_editor_i18n_lang_from_env(), BREAK_EDITOR_LANG_ZH_CN);
    setenv("BREAK_LANG", "en", 1);
    ASSERT_EQ(break_editor_i18n_lang_from_env(), BREAK_EDITOR_LANG_EN_US);
    /* an unsupported higher-priority value does not mask a usable lower one */
    setenv("BREAK_LANG", "fr", 1);
    ASSERT_EQ(break_editor_i18n_lang_from_env(), BREAK_EDITOR_LANG_ZH_CN);
    setenv("BREAK_LANG", "", 1);
    ASSERT_EQ(break_editor_i18n_lang_from_env(), BREAK_EDITOR_LANG_ZH_CN);
    env_restore(&snap);
#endif
}

TEST(component_names_follow_language_and_fall_back_for_unknown_ids)
{
    BreakEditorLang saved = break_editor_i18n_lang();
    ASSERT_TRUE(break_editor_i18n_set_lang(BREAK_EDITOR_LANG_EN_US));
    ASSERT_STR_EQ(break_editor_tr_component(BREAK_EDITOR_COMPONENT_TRANSFORM,
                                            "x"),
                  "Transform");
    ASSERT_STR_EQ(break_editor_tr_component(BREAK_EDITOR_COMPONENT_LIGHT, "x"),
                  "Light");
    ASSERT_TRUE(break_editor_i18n_set_lang(BREAK_EDITOR_LANG_ZH_CN));
    ASSERT_STR_EQ(break_editor_tr_component(BREAK_EDITOR_COMPONENT_TRANSFORM,
                                            "x"),
                  "变换");
    ASSERT_STR_EQ(break_editor_tr_component(BREAK_EDITOR_COMPONENT_LIGHT, "x"),
                  "灯光");
    ASSERT_STR_EQ(break_editor_tr_component(9999u, "Custom"), "Custom");
    ASSERT_STR_EQ(break_editor_tr_component(9999u, NULL), "?");
    ASSERT_TRUE(break_editor_i18n_set_lang(saved));
}

TEST_MAIN_BEGIN()
    RUN_TEST(every_language_fills_every_key_with_valid_utf8);
    RUN_TEST(chinese_table_is_actually_translated);
    RUN_TEST(format_keys_keep_identical_conversions_across_languages);
    RUN_TEST(current_language_switches_and_rejects_out_of_range);
    RUN_TEST(language_tags_and_names);
    RUN_TEST(parse_lang_accepts_bcp47_and_posix_tags);
    RUN_TEST(lang_from_env_follows_priority_and_skips_unparseable);
    RUN_TEST(component_names_follow_language_and_fall_back_for_unknown_ids);
TEST_MAIN_END()
