/* Editor UI preferences — see editor_settings.h. */

#include "editor_settings.h"

#include <platform/platform_fs.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SETTINGS_MAX_BYTES 4096u

void break_editor_settings_defaults(BreakEditorSettings *s) {
    if (s == NULL) {
        return;
    }
    memset(s, 0, sizeof(*s));
    s->lang = BREAK_EDITOR_LANG_EN_US;
}

static void trim(const char **b, const char **e) {
    while (*b < *e && (**b == ' ' || **b == '\t')) (*b)++;
    while (*e > *b && ((*e)[-1] == ' ' || (*e)[-1] == '\t' || (*e)[-1] == '\r'))
        (*e)--;
}

static bool span_eq(const char *b, const char *e, const char *lit) {
    usize n = strlen(lit);
    return (usize)(e - b) == n && memcmp(b, lit, n) == 0;
}

/* single decimal digit < limit */
static bool parse_small(const char *b, const char *e, u32 limit, u32 *out) {
    if (e - b != 1 || *b < '0' || *b > '9' || (u32)(*b - '0') >= limit) {
        return false;
    }
    *out = (u32)(*b - '0');
    return true;
}

static void apply_line(BreakEditorSettings *s, const char *b, const char *e) {
    const char *eq = memchr(b, '=', (usize)(e - b));
    const char *kb = b, *ke, *vb, *ve;
    if (eq == NULL) {
        return;
    }
    ke = eq;
    vb = eq + 1;
    ve = e;
    trim(&kb, &ke);
    trim(&vb, &ve);
    if (kb == ke || kb[0] == '#') {
        return;
    }
    if (span_eq(kb, ke, "theme")) {
        if (span_eq(vb, ve, "light")) s->light_theme = true;
        else if (span_eq(vb, ve, "dark")) s->light_theme = false;
    } else if (span_eq(kb, ke, "lang")) {
        char tag[32];
        BreakEditorLang lang;
        usize n = (usize)(ve - vb);
        if (n > 0u && n < sizeof(tag)) {
            memcpy(tag, vb, n);
            tag[n] = '\0';
            if (break_editor_i18n_parse_lang(tag, &lang)) {
                s->lang = lang;
                s->has_lang = true;
            }
        }
    } else if (span_eq(kb, ke, "bottom_tab")) {
        (void)parse_small(vb, ve, 2u, &s->bottom_tab);
    } else if (span_eq(kb, ke, "diag_tab")) {
        (void)parse_small(vb, ve, 3u, &s->diag_tab);
    }
}

bool break_editor_settings_parse(BreakEditorSettings *s, const char *text,
                                 usize len) {
    const char *p, *end;
    if (s == NULL || text == NULL) {
        return false;
    }
    p = text;
    end = text + len;
    while (p < end) {
        const char *nl = memchr(p, '\n', (usize)(end - p));
        const char *le = nl != NULL ? nl : end;
        if (le > p && p[0] != '#') {
            apply_line(s, p, le);
        }
        p = nl != NULL ? nl + 1 : end;
    }
    return true;
}

usize break_editor_settings_serialize(const BreakEditorSettings *s, char *out,
                                      usize cap) {
    int n;
    if (s == NULL || out == NULL || cap == 0u) {
        return 0u;
    }
    n = snprintf(out, cap,
                 "# Break editor UI settings (written by the editor)\n"
                 "theme=%s\n"
                 "%s%s%s"
                 "bottom_tab=%u\n"
                 "diag_tab=%u\n",
                 s->light_theme ? "light" : "dark",
                 s->has_lang ? "lang=" : "",
                 s->has_lang ? break_editor_i18n_lang_tag(s->lang) : "",
                 s->has_lang ? "\n" : "",
                 (unsigned)(s->bottom_tab < 2u ? s->bottom_tab : 0u),
                 (unsigned)(s->diag_tab < 3u ? s->diag_tab : 0u));
    if (n < 0 || (usize)n >= cap) {
        out[0] = '\0';
        return 0u;
    }
    return (usize)n;
}

static bool join3(char *out, usize cap, const char *a, const char *b) {
    int n = snprintf(out, cap, "%s%s", a, b);
    return n > 0 && (usize)n < cap;
}

bool break_editor_settings_default_path(char *out, usize cap) {
    const char *env;
    if (out == NULL || cap == 0u) {
        return false;
    }
    out[0] = '\0';
    env = getenv("BREAK_EDITOR_SETTINGS");
    if (env != NULL && env[0] != '\0') {
        return join3(out, cap, env, "");
    }
#if defined(_WIN32)
    env = getenv("APPDATA");
    if (env != NULL && env[0] != '\0') {
        return join3(out, cap, env, "/break/editor.ini");
    }
    return false;
#else
    env = getenv("XDG_CONFIG_HOME");
    if (env != NULL && env[0] != '\0') {
        return join3(out, cap, env, "/break/editor.ini");
    }
    env = getenv("HOME");
    if (env != NULL && env[0] != '\0') {
        return join3(out, cap, env, "/.config/break/editor.ini");
    }
    return false;
#endif
}

bool break_editor_settings_load(BreakEditorSettings *s, const char *path) {
    FILE *f;
    char buf[SETTINGS_MAX_BYTES];
    usize n;
    if (s == NULL || path == NULL) {
        return false;
    }
    f = fopen(path, "rb");
    if (f == NULL) {
        return true; /* first run: defaults */
    }
    n = fread(buf, 1u, sizeof(buf), f);
    fclose(f);
    return break_editor_settings_parse(s, buf, n);
}

/* mkdir -p for every parent of `path` (PAL mkdir is single level). Failures
 * of intermediate components are ignored on purpose: a drive prefix such as
 * "C:" or a protected existing directory cannot be created but is not an
 * error; if the leaf directory is really missing the file open fails. */
static bool make_parents(const char *path) {
    char dir[1024];
    usize n = strlen(path), i;
    if (n >= sizeof(dir)) {
        return false;
    }
    memcpy(dir, path, n + 1u);
    for (i = 1u; i < n; i++) {
        if (dir[i] == '/' || dir[i] == '\\') {
            char c = dir[i];
            dir[i] = '\0';
            (void)platform_mkdir(dir);
            dir[i] = c;
        }
    }
    return true;
}

bool break_editor_settings_save(const BreakEditorSettings *s, const char *path) {
    char buf[512];
    usize n;
    PlatformAtomicWriter *w;
    if (s == NULL || path == NULL) {
        return false;
    }
    n = break_editor_settings_serialize(s, buf, sizeof(buf));
    if (n == 0u || !make_parents(path)) {
        return false;
    }
    w = platform_atomic_writer_open(path);
    if (w == NULL) {
        return false;
    }
    if (!platform_atomic_writer_write(w, buf, n)) {
        platform_atomic_writer_abort(w);
        return false;
    }
    return platform_atomic_writer_commit(w);
}
