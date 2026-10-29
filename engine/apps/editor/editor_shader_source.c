#include "editor_shader_source.h"

#include <core/shader_io.h>

#include <stdlib.h>
#include <string.h>

static bool editor_shader_stage_valid(BreakEditorShaderStage stage) {
    return stage == BREAK_EDITOR_SHADER_VERTEX ||
           stage == BREAK_EDITOR_SHADER_FRAGMENT;
}

static usize editor_shader_bounded_length(const char *text, usize capacity) {
    usize length = 0u;
    while (length < capacity && text[length] != '\0') {
        length++;
    }
    return length;
}

static void editor_shader_source_add_root(BreakEditorShaderSource *s,
                                          const char *root) {
    usize root_len = editor_shader_bounded_length(root, VFS_MAX_PATH);
    usize stage;
    if (root_len == 0u || root_len >= sizeof(s->roots[0]) ||
        s->root_count >= 5u) {
        s->skipped_roots++;
        return;
    }
    for (stage = 0u; stage < 2u; stage++) {
        usize logical_len = editor_shader_bounded_length(
            s->logical[stage], sizeof(s->logical[stage]));
        if (root_len + 1u + logical_len >= 1024u) {
            s->skipped_roots++;
            return;
        }
    }
    memcpy(s->roots[s->root_count], root, root_len + 1u);
    s->root_count++;
}

bool break_editor_shader_source_configure(BreakEditorShaderSource *s,
                                          RHIShaderVariant variant) {
    static const char *const roots[] = {
        ".", "engine", "../engine", "../../engine"
    };
    const char *env;
    usize i;
    if (s == NULL) {
        return false;
    }
    memset(s, 0, sizeof(*s));
    if (shader_variant_path("shaders/editor_color.vert", variant,
                            s->logical[BREAK_EDITOR_SHADER_VERTEX],
                            sizeof(s->logical[BREAK_EDITOR_SHADER_VERTEX])) == NULL ||
        shader_variant_path("shaders/editor_color.frag", variant,
                            s->logical[BREAK_EDITOR_SHADER_FRAGMENT],
                            sizeof(s->logical[BREAK_EDITOR_SHADER_FRAGMENT])) == NULL) {
        memset(s, 0, sizeof(*s));
        return false;
    }
    env = getenv("BREAK_SHADER_DIR");
    if (env != NULL && env[0] != '\0') {
        editor_shader_source_add_root(s, env);
    }
    for (i = 0u; i < sizeof(roots) / sizeof(roots[0]); i++) {
        editor_shader_source_add_root(s, roots[i]);
    }
    return true;
}

void break_editor_shader_source_destroy_bytes(BreakEditorShaderBytes *bytes) {
    if (bytes == NULL) {
        return;
    }
    free(bytes->data);
    memset(bytes, 0, sizeof(*bytes));
}

bool break_editor_shader_source_read(const BreakEditorShaderSource *s,
                                     BreakEditorShaderStage stage,
                                     BreakEditorShaderBytes *out) {
    u32 i;
    if (s == NULL || out == NULL || !editor_shader_stage_valid(stage)) {
        return false;
    }
    for (i = 0u; i < s->root_count && i < 5u; i++) {
        char path[1024];
        usize root_len = editor_shader_bounded_length(
            s->roots[i], sizeof(s->roots[i]));
        usize logical_len = editor_shader_bounded_length(
            s->logical[stage], sizeof(s->logical[stage]));
        usize path_len;
        char *data;
        usize size = 0u;
        if (root_len == 0u || root_len >= sizeof(s->roots[i]) ||
            logical_len >= sizeof(s->logical[stage]) ||
            root_len + 1u + logical_len >= sizeof(path)) {
            continue;
        }
        memcpy(path, s->roots[i], root_len);
        path[root_len] = '/';
        memcpy(path + root_len + 1u, s->logical[stage], logical_len);
        path_len = root_len + 1u + logical_len;
        path[path_len] = '\0';
        data = shader_read_file(path, &size);
        if (data != NULL) {
            out->data = data;
            out->size = size;
            memcpy(out->path, path, path_len + 1u);
            return true;
        }
    }
    return false;
}

const char *break_editor_shader_source_path(
    const BreakEditorShaderSource *s, BreakEditorShaderStage stage) {
    if (s == NULL || !editor_shader_stage_valid(stage)) {
        return NULL;
    }
    return s->logical[stage];
}

typedef struct {
    const BreakEditorShaderSource *s;
    char *buf;
    usize len, cap;
    char (*deps)[96];
    u32 dep_count;
    const char *stack[BREAK_EDITOR_SHADER_MAX_INCLUDE_DEPTH + 1u];
    u32 depth;
} ShaderExpand;

static bool expand_put(ShaderExpand *x, const char *p, usize n) {
    if (n > (usize)SHADER_MAX_FILE_BYTES - x->len) {
        return false;
    }
    if (x->len + n + 1u > x->cap) {
        usize cap = x->cap ? x->cap : 256u;
        char *grown;
        while (cap < x->len + n + 1u) cap *= 2u;
        grown = (char *)realloc(x->buf, cap);
        if (grown == NULL) return false;
        x->buf = grown;
        x->cap = cap;
    }
    memcpy(x->buf + x->len, p, n);
    x->len += n;
    x->buf[x->len] = '\0';
    return true;
}

static bool include_name_safe(const char *name, usize n) {
    usize i, seg = 0u;
    if (n == 0u || name[0] == '/') return false;
    for (i = 0u; i < n; i++) {
        char c = name[i];
        bool ok = (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') ||
                  (c >= '0' && c <= '9') || c == '_' || c == '.' ||
                  c == '-' || c == '/';
        if (!ok) return false;
        if (c == '/') {
            if (seg == 0u) return false;
            seg = 0u;
        } else {
            seg++;
        }
        if (c == '.' && i + 1u < n && name[i + 1u] == '.') return false;
    }
    return seg > 0u;
}

static bool expand_text(ShaderExpand *x, const char *text, usize len);

static bool expand_include(ShaderExpand *x, const char *name, usize n) {
    char logical[96];
    u32 i;
    if (!include_name_safe(name, n) || n + 8u >= sizeof(logical)) {
        return false;
    }
    memcpy(logical, "shaders/", 8u);
    memcpy(logical + 8u, name, n);
    logical[8u + n] = '\0';
    {
        bool seen = false;
        for (i = 0u; i < x->dep_count; i++) {
            if (strcmp(x->deps[i], logical) == 0) seen = true;
        }
        if (!seen && x->dep_count < BREAK_EDITOR_SHADER_MAX_DEPS) {
            memcpy(x->deps[x->dep_count++], logical, 8u + n + 1u);
        }
    }
    for (i = 0u; i < x->depth; i++) {
        if (strcmp(x->stack[i], logical) == 0) return false; /* cycle */
    }
    if (x->depth >= BREAK_EDITOR_SHADER_MAX_INCLUDE_DEPTH) {
        return false;
    }
    for (i = 0u; i < x->s->root_count && i < 5u; i++) {
        char path[1024];
        usize root_len = editor_shader_bounded_length(
            x->s->roots[i], sizeof(x->s->roots[i]));
        usize size = 0u;
        char *data;
        bool ok;
        if (root_len == 0u || root_len + 1u + 8u + n >= sizeof(path)) {
            continue;
        }
        memcpy(path, x->s->roots[i], root_len);
        path[root_len] = '/';
        memcpy(path + root_len + 1u, logical, 8u + n + 1u);
        data = shader_read_file(path, &size);
        if (data == NULL) {
            continue;
        }
        x->stack[x->depth++] = logical;
        ok = expand_text(x, data, size);
        x->depth--;
        free(data);
        return ok;
    }
    return false;
}

static bool expand_text(ShaderExpand *x, const char *text, usize len) {
    usize p = 0u;
    while (p < len) {
        usize e = p, q;
        while (e < len && text[e] != '\n') e++;
        q = p;
        while (q < e && (text[q] == ' ' || text[q] == '\t')) q++;
        if (e - q >= 8u && memcmp(text + q, "#include", 8u) == 0) {
            usize a = q + 8u, b;
            while (a < e && (text[a] == ' ' || text[a] == '\t')) a++;
            if (a >= e || text[a] != '"') return false;
            a++;
            b = a;
            while (b < e && text[b] != '"') b++;
            if (b >= e) return false;
            if (!expand_include(x, text + a, b - a)) return false;
            if (x->len > 0u && x->buf[x->len - 1u] != '\n' &&
                !expand_put(x, "\n", 1u)) {
                return false;
            }
        } else if (!expand_put(x, text + p, e - p + (e < len ? 1u : 0u))) {
            return false;
        }
        p = e < len ? e + 1u : len;
    }
    return true;
}

bool break_editor_shader_source_expand(
    const BreakEditorShaderSource *s, const char *text, usize len,
    char **out, usize *out_len, char deps[][96], u32 *dep_count) {
    ShaderExpand x;
    if (out != NULL) *out = NULL;
    if (dep_count != NULL) *dep_count = 0u;
    if (s == NULL || (text == NULL && len > 0u) || out == NULL ||
        out_len == NULL || deps == NULL || dep_count == NULL) {
        return false;
    }
    memset(&x, 0, sizeof(x));
    x.s = s;
    x.deps = deps;
    if (!expand_put(&x, "", 0u) || !expand_text(&x, text, len)) {
        *dep_count = x.dep_count;
        free(x.buf);
        return false;
    }
    *dep_count = x.dep_count;
    *out = x.buf;
    *out_len = x.len;
    return true;
}
