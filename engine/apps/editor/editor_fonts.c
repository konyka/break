/* Editor UI font discovery — see editor_fonts.h. */

#include "editor_fonts.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if defined(__linux__)
#include <unistd.h>
/* The engine compiles with _POSIX_C_SOURCE=199309L, where unistd.h does not
 * declare readlink(2) (it needs >= 200112L). Declare it here. */
extern ssize_t readlink(const char *path, char *buf, size_t bufsiz);
#endif
#if defined(__APPLE__)
#include <mach-o/dyld.h>
#endif
#if defined(_WIN32)
#include <windows.h>
#endif

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

#define BREAK_EDITOR_BUNDLED_FONT_REL "assets/fonts/JetBrainsMono-Regular.ttf"
#define BREAK_EDITOR_BUNDLED_CJK_REL "assets/fonts/NotoSansSC-VF.ttf"

/* Writes dir + '/' + rel into out; false when it does not fit. */
static bool path_join(char *out, usize cap, const char *dir, usize dir_len,
                      const char *rel) {
    usize rel_len = strlen(rel);
    if (dir_len == 0u || dir_len + 1u + rel_len >= cap) {
        return false;
    }
    memcpy(out, dir, dir_len);
    out[dir_len] = '/';
    memcpy(out + dir_len + 1u, rel, rel_len + 1u);
    return true;
}

/* Directory part of an absolute executable path, "" when unavailable. */
static usize exe_dir(char *out, usize cap) {
    usize n = 0u;
#if defined(__linux__)
    ssize_t r = readlink("/proc/self/exe", out, cap - 1u);
    if (r <= 0 || (usize)r >= cap) {
        return 0u;
    }
    n = (usize)r;
#elif defined(__APPLE__)
    uint32_t need = (uint32_t)cap;
    if (_NSGetExecutablePath(out, &need) != 0) {
        return 0u;
    }
    n = strlen(out);
#elif defined(_WIN32)
    DWORD r = GetModuleFileNameA(NULL, out, (DWORD)cap);
    if (r == 0 || r >= (DWORD)cap) {
        return 0u;
    }
    n = (usize)r;
    for (usize i = 0u; i < n; i++) {
        if (out[i] == '\\') out[i] = '/';
    }
#else
    (void)cap;
#endif
    out[n] = '\0';
    while (n > 0u && out[n - 1u] != '/') {
        n--;
    }
    return n > 0u ? n - 1u : 0u;
}

/* Build-tree layouts: the exe sits in the build dir, assets live in
 * <source>/engine; the editor's asset root is the cwd, so "engine/assets"
 * and "assets" (cwd = source root or engine/) cover source runs. */
static bool bundled_path(const char *rel, usize index, char *out, usize cap) {
    const char *env;
    char dir[BREAK_EDITOR_FONT_PATH_MAX];
    usize n;
    if (out == NULL || cap == 0u) {
        return false;
    }
    out[0] = '\0';
    if (index == 0u) {
        env = getenv("BREAK_ASSET_DIR");
        if (env == NULL || env[0] == '\0') {
            return false;
        }
        return path_join(out, cap, env, strlen(env),
                         rel);
    }
    if (index == 1u) {
        n = exe_dir(dir, sizeof(dir));
        if (n == 0u) {
            return false;
        }
        /* <exe dir>/assets (installed, or engine/ as cwd of the exe dir) */
        return path_join(out, cap, dir, n, rel);
    }
    if (index == 2u) {
        /* repo layout: exe in <build>, assets in <repo>/engine */
        n = exe_dir(dir, sizeof(dir));
        if (n == 0u) {
            return false;
        }
        /* strip the build dir: exe dir is <repo>/<build> or <repo> */
        while (n > 0u && dir[n - 1u] != '/') {
            n--;
        }
        if (n == 0u) {
            return false;
        }
        {
            char full[BREAK_EDITOR_FONT_PATH_MAX];
            if (snprintf(full, sizeof(full), "engine/%s", rel) >=
                (int)sizeof(full)) {
                return false;
            }
            return path_join(out, cap, dir, n - 1u, full);
        }
    }
    if (index == 3u) {
        return path_join(out, cap, ".", 1u, rel);
    }
    if (index == 4u) {
        {
            char full[BREAK_EDITOR_FONT_PATH_MAX];
            if (snprintf(full, sizeof(full), "engine/%s", rel) >=
                (int)sizeof(full)) {
                return false;
            }
            return path_join(out, cap, ".", 1u, full);
        }
    }
    return false;
}

bool break_editor_bundled_font_path(usize index, char *out, usize cap) {
    return bundled_path(BREAK_EDITOR_BUNDLED_FONT_REL, index, out, cap);
}

bool break_editor_bundled_cjk_font_path(usize index, char *out, usize cap) {
    return bundled_path(BREAK_EDITOR_BUNDLED_CJK_REL, index, out, cap);
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
    /* Bundled CLion face first (JetBrains Mono Regular, OFL; Latin and
     * punctuation only — CJK still comes from the system chain below).
     * Skipped when `root` is set: that form emulates a whole system tree
     * for the table tests. */
    if (root == NULL) {
        for (usize i = 0u; i < BREAK_EDITOR_BUNDLED_FONT_PATHS; i++) {
            char path[BREAK_EDITOR_FONT_PATH_MAX];
            if (break_editor_bundled_font_path(i, path, sizeof(path))) {
                chain_add(out, NULL, path, 0, false);
            }
        }
        /* Bundled Chinese face (Noto Sans SC, the CLion Chinese language
         * pack's family): second, so Latin keeps JetBrains Mono and CJK no
         * longer depends on the host having any Chinese font installed. */
        for (usize i = 0u; i < BREAK_EDITOR_BUNDLED_FONT_PATHS; i++) {
            char path[BREAK_EDITOR_FONT_PATH_MAX];
            if (break_editor_bundled_cjk_font_path(i, path, sizeof(path))) {
                chain_add(out, NULL, path, 0, true);
            }
        }
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
