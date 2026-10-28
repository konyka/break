/* Editor UI font discovery — see editor_fonts.h. */

#include "editor_fonts.h"

#include <stdio.h>
#include <string.h>

#if defined(BREAK_EDITOR_FONTCONFIG)
#include <fontconfig/fontconfig.h>
#endif

typedef struct {
    const char *path;
    int face; /* face index inside a .ttc collection */
    bool cjk;
} FontEntry;

/* Well-known install locations, most specific first within each script. */
static const FontEntry k_fonts[] = {
#if defined(_WIN32)
    {"C:/Windows/Fonts/segoeui.ttf", 0, false},
    {"C:/Windows/Fonts/arial.ttf", 0, false},
    {"C:/Windows/Fonts/msyh.ttc", 0, true},
    {"C:/Windows/Fonts/simsun.ttc", 0, true},
#elif defined(__APPLE__)
    {"/System/Library/Fonts/Helvetica.ttc", 0, false},
    {"/System/Library/Fonts/PingFang.ttc", 0, true},
    {"/System/Library/Fonts/STHeiti Light.ttc", 0, true},
    {"/System/Library/Fonts/Hiragino Sans GB.ttc", 0, true},
#else
    /* Latin */
    {"/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf", 0, false},  /* Debian */
    {"/usr/share/fonts/dejavu-sans-fonts/DejaVuSans.ttf", 0, false}, /* Fedora */
    {"/usr/share/fonts/TTF/DejaVuSans.ttf", 0, false},              /* Arch */
    {"/usr/share/fonts/truetype/DejaVuSans.ttf", 0, false},         /* SUSE */
    {"/usr/share/fonts/google-droid-sans-fonts/DroidSans.ttf", 0, false},
    {"/usr/share/fonts/liberation-sans-fonts/LiberationSans-Regular.ttf", 0, false},
    {"/usr/share/fonts/truetype/liberation/LiberationSans-Regular.ttf", 0, false},
    /* CJK (face 2 of the static Noto CJK .ttc is Simplified Chinese; the
     * variable .ttc keeps SC at face 2 as well) */
    {"/usr/share/fonts/google-noto-sans-cjk-vf-fonts/NotoSansCJK-VF.ttc", 2, true},
    {"/usr/share/fonts/google-noto-cjk/NotoSansCJK-Regular.ttc", 2, true},
    {"/usr/share/fonts/opentype/noto/NotoSansCJK-Regular.ttc", 2, true},
    {"/usr/share/fonts/noto-cjk/NotoSansCJK-Regular.ttc", 2, true},
    {"/usr/share/fonts/google-droid-sans-fonts/DroidSansFallbackFull.ttf", 0, true},
    {"/usr/share/fonts/truetype/wqy/wqy-microhei.ttc", 0, true},
    {"/usr/share/fonts/wenquanyi/wqy-microhei/wqy-microhei.ttc", 0, true},
#endif
};

static bool file_exists(const char *path) {
    FILE *f = fopen(path, "rb");
    if (f == NULL) {
        return false;
    }
    fclose(f);
    return true;
}

static void chain_add(BreakEditorFontChain *c, const char *root,
                      const char *path, int face, bool cjk) {
    usize root_len = root != NULL ? strlen(root) : 0u;
    usize path_len;
    char *dst;
#if defined(_WIN32)
    /* A test/sysroot prefix replaces the drive: "<root>/Windows/Fonts/x".
     * Without a root the absolute path is used as is. */
    if (root_len > 0u && path[0] != '\0' && path[1] == ':') {
        path += 2;
    }
#endif
    path_len = strlen(path);
    if (c->count >= BREAK_EDITOR_FONT_MAX_CANDIDATES ||
        root_len + path_len >= BREAK_EDITOR_FONT_PATH_MAX) {
        return; /* full, or too long to store without truncation */
    }
    dst = c->paths[c->count];
    if (root_len > 0u) {
        memcpy(dst, root, root_len);
    }
    memcpy(dst + root_len, path, path_len + 1u);
    for (usize i = 0u; i < c->count; i++) {
        if (strcmp(c->paths[i], dst) == 0) {
            return; /* duplicate (e.g. fontconfig and the table agree) */
        }
    }
    if (!file_exists(dst)) {
        return;
    }
    c->sources[c->count].path = dst;
    c->sources[c->count].face_index = face;
    c->count++;
    if (cjk) {
        c->has_cjk = true;
    }
}

#if defined(BREAK_EDITOR_FONTCONFIG)
/* Best fontconfig match for a language; only real font files are accepted. */
static void chain_add_fontconfig(BreakEditorFontChain *c, const char *lang,
                                 bool cjk) {
    FcPattern *pat;
    FcPattern *match;
    FcResult result = FcResultNoMatch;
    FcChar8 *file = NULL;
    int face = 0;
    FcLangSet *want;
    if (!FcInit()) {
        return;
    }
    pat = FcPatternCreate();
    if (pat == NULL) {
        return;
    }
    (void)FcPatternAddString(pat, FC_FAMILY, (const FcChar8 *)"sans-serif");
    (void)FcPatternAddString(pat, FC_LANG, (const FcChar8 *)lang);
    (void)FcConfigSubstitute(NULL, pat, FcMatchPattern);
    FcDefaultSubstitute(pat);
    match = FcFontMatch(NULL, pat, &result);
    FcPatternDestroy(pat);
    if (match == NULL) {
        return;
    }
    want = FcLangSetCreate();
    if (want != NULL) {
        FcLangSet *have = NULL;
        (void)FcLangSetAdd(want, (const FcChar8 *)lang);
        /* fontconfig always returns *something*; keep it only if it really
         * covers the language */
        if (FcPatternGetLangSet(match, FC_LANG, 0, &have) == FcResultMatch &&
            FcLangSetContains(have, want) &&
            FcPatternGetString(match, FC_FILE, 0, &file) == FcResultMatch &&
            file != NULL) {
            (void)FcPatternGetInteger(match, FC_INDEX, 0, &face);
            chain_add(c, NULL, (const char *)file, face, cjk);
        }
        FcLangSetDestroy(want);
    }
    FcPatternDestroy(match);
}
#endif

static void chain_add_table(BreakEditorFontChain *c, const char *root,
                            bool cjk) {
    for (usize i = 0u; i < sizeof(k_fonts) / sizeof(k_fonts[0]); i++) {
        if (k_fonts[i].cjk == cjk) {
            usize before = c->count;
            chain_add(c, root, k_fonts[i].path, k_fonts[i].face, cjk);
            if (c->count > before) {
                return; /* one face per script is enough for the chain */
            }
        }
    }
}

static void chain_add_script(BreakEditorFontChain *c, const char *root,
                             bool use_fontconfig, bool cjk) {
    usize before = c->count;
#if defined(BREAK_EDITOR_FONTCONFIG)
    if (use_fontconfig && (root == NULL || root[0] == '\0')) {
        chain_add_fontconfig(c, cjk ? "zh-cn" : "en", cjk);
    }
#else
    (void)use_fontconfig;
#endif
    if (c->count == before) {
        chain_add_table(c, root, cjk);
    }
}

usize break_editor_font_candidates(BreakEditorLang lang, const char *root,
                                   bool use_fontconfig,
                                   BreakEditorFontChain *out) {
    bool cjk_first = lang == BREAK_EDITOR_LANG_ZH_CN;
    if (out == NULL) {
        return 0u;
    }
    memset(out, 0, sizeof(*out));
    if (root != NULL && root[0] == '\0') {
        root = NULL;
    }
    chain_add_script(out, root, use_fontconfig, cjk_first);
    chain_add_script(out, root, use_fontconfig, !cjk_first);
    return out->count;
}

bool break_editor_cli_take_lang(int *argc, char **argv,
                                BreakEditorLang *out_lang, char *err,
                                usize err_cap) {
    BreakEditorLang lang = BREAK_EDITOR_LANG_COUNT;
    int n, i, kept = 1;
    if (argc == NULL || argv == NULL || out_lang == NULL || *argc < 1) {
        return false;
    }
    n = *argc;
    for (i = 1; i < n; i++) {
        const char *value = NULL;
        if (argv[i] == NULL || strncmp(argv[i], "--lang", 6u) != 0 ||
            (argv[i][6] != '\0' && argv[i][6] != '=')) {
            continue;
        }
        if (argv[i][6] == '=') {
            value = argv[i] + 7;
        } else if (i + 1 < n) {
            value = argv[i + 1];
        }
        if (value == NULL || !break_editor_i18n_parse_lang(value, &lang)) {
            if (err != NULL && err_cap > 0u) {
                (void)snprintf(err, err_cap,
                               "--lang needs en-US or zh-CN (got '%.40s')",
                               value != NULL ? value : "");
            }
            return false;
        }
        if (argv[i][6] == '\0') {
            i++; /* the value was the next argument */
        }
    }
    for (i = 1; i < n; i++) {
        if (argv[i] != NULL && strncmp(argv[i], "--lang", 6u) == 0 &&
            (argv[i][6] == '\0' || argv[i][6] == '=')) {
            if (argv[i][6] == '\0') {
                i++;
            }
            continue;
        }
        argv[kept++] = argv[i];
    }
    argv[kept] = NULL;
    *argc = kept;
    *out_lang = lang != BREAK_EDITOR_LANG_COUNT
                    ? lang
                    : break_editor_i18n_lang_from_env();
    return true;
}
