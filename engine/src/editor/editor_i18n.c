/* Editor UI translations — see editor_i18n.h. */

#include <editor/editor_i18n.h>

#include <stdlib.h>
#include <string.h>

/* defined in editor_i18n_tables.c */
extern const char *const g_break_editor_tr_tables[BREAK_EDITOR_LANG_COUNT]
                                                 [BREAK_EDITOR_TR_COUNT];

static BreakEditorLang s_lang = BREAK_EDITOR_LANG_EN_US;

static bool lang_valid(BreakEditorLang lang) {
    return (int)lang >= 0 && lang < BREAK_EDITOR_LANG_COUNT;
}

const char *break_editor_tr_lang(BreakEditorLang lang, BreakEditorTr key) {
    const char *s;
    if ((int)key < 0 || key >= BREAK_EDITOR_TR_COUNT) {
        return "?";
    }
    if (lang_valid(lang)) {
        s = g_break_editor_tr_tables[lang][key];
        if (s != NULL && s[0] != '\0') {
            return s;
        }
    }
    s = g_break_editor_tr_tables[BREAK_EDITOR_LANG_EN_US][key];
    return s != NULL && s[0] != '\0' ? s : "?";
}

const char *break_editor_tr(BreakEditorTr key) {
    return break_editor_tr_lang(s_lang, key);
}

bool break_editor_i18n_set_lang(BreakEditorLang lang) {
    if (!lang_valid(lang)) {
        return false;
    }
    s_lang = lang;
    return true;
}

BreakEditorLang break_editor_i18n_lang(void) {
    return s_lang;
}

static char ascii_lower(char c) {
    return (c >= 'A' && c <= 'Z') ? (char)(c - 'A' + 'a') : c;
}

/* true when `tag` starts with the language subtag `lang` followed by the end
 * or a separator ('-', '_', '.', '@'). */
static bool tag_has_language(const char *tag, const char *lang) {
    size_t i;
    for (i = 0u; lang[i] != '\0'; i++) {
        if (ascii_lower(tag[i]) != lang[i]) {
            return false;
        }
    }
    return tag[i] == '\0' || tag[i] == '-' || tag[i] == '_' ||
           tag[i] == '.' || tag[i] == '@';
}

bool break_editor_i18n_parse_lang(const char *tag, BreakEditorLang *out) {
    BreakEditorLang lang;
    if (tag == NULL || out == NULL || tag[0] == '\0') {
        return false;
    }
    if (tag_has_language(tag, "zh")) {
        lang = BREAK_EDITOR_LANG_ZH_CN;
    } else if (tag_has_language(tag, "en") || tag_has_language(tag, "c") ||
               tag_has_language(tag, "posix")) {
        lang = BREAK_EDITOR_LANG_EN_US;
    } else {
        return false;
    }
    *out = lang;
    return true;
}

BreakEditorLang break_editor_i18n_lang_from_env(void) {
    static const char *const names[] = {"BREAK_LANG", "LC_ALL", "LC_MESSAGES",
                                        "LANG"};
    size_t i;
    for (i = 0u; i < sizeof(names) / sizeof(names[0]); i++) {
        BreakEditorLang lang;
        if (break_editor_i18n_parse_lang(getenv(names[i]), &lang)) {
            return lang;
        }
    }
    return BREAK_EDITOR_LANG_EN_US;
}

const char *break_editor_i18n_lang_tag(BreakEditorLang lang) {
    static const char *const tags[BREAK_EDITOR_LANG_COUNT] = {"en-US",
                                                              "zh-CN"};
    return lang_valid(lang) ? tags[lang] : "?";
}

const char *break_editor_i18n_lang_name(BreakEditorLang lang) {
    static const char *const names[BREAK_EDITOR_LANG_COUNT] = {"English",
                                                               "中文"};
    return lang_valid(lang) ? names[lang] : "?";
}
