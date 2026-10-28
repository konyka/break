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
