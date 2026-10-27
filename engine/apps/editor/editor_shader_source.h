#pragma once

#include <core/types.h>
#include <asset/vfs.h>
#include <rhi/rhi.h>

typedef enum { BREAK_EDITOR_SHADER_VERTEX = 0,
               BREAK_EDITOR_SHADER_FRAGMENT = 1 } BreakEditorShaderStage;

typedef struct {
    char roots[5][VFS_MAX_PATH]; /* highest priority first */
    u32 root_count;
    char logical[2][96];
    u32 skipped_roots;
} BreakEditorShaderSource;

typedef struct {
    char *data;       /* owned; data[size] == '\0' */
    usize size;
    char path[1024];  /* actual successful path, not a guessed prefix */
} BreakEditorShaderBytes;

bool break_editor_shader_source_configure(BreakEditorShaderSource *s,
                                          RHIShaderVariant variant);
void break_editor_shader_source_destroy_bytes(BreakEditorShaderBytes *bytes);
bool break_editor_shader_source_read(const BreakEditorShaderSource *s,
                                     BreakEditorShaderStage stage,
                                     BreakEditorShaderBytes *out);
const char *break_editor_shader_source_path(
    const BreakEditorShaderSource *s, BreakEditorShaderStage stage);
