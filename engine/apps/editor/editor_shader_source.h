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
/* #include expansion. A line whose first non-blank text is
 * `#include "name"` is replaced by the contents of shaders/<name>, taken from
 * the first root that has it (same priority as the stage files). name is
 * relative, made of [A-Za-z0-9_.-/], with no "..", no leading '/' and no
 * empty segment. Includes nest up to BREAK_EDITOR_SHADER_MAX_INCLUDE_DEPTH;
 * a cycle, a missing or unsafe file, `#include <...>`, an unterminated name
 * or output above SHADER_MAX_FILE_BYTES fails. On success *out is a
 * malloc'd NUL-terminated copy (caller frees). deps receives the logical
 * paths ("shaders/<name>") of every include met, once each, in first-seen
 * order (also filled as far as it got on failure, so a missing file can be
 * watched); at most BREAK_EDITOR_SHADER_MAX_DEPS are kept. On failure *out
 * is NULL. */
#define BREAK_EDITOR_SHADER_MAX_INCLUDE_DEPTH 4u
#define BREAK_EDITOR_SHADER_MAX_DEPS 16u
bool break_editor_shader_source_expand(
    const BreakEditorShaderSource *s, const char *text, usize len,
    char **out, usize *out_len, char deps[][96], u32 *dep_count);
const char *break_editor_shader_source_path(
    const BreakEditorShaderSource *s, BreakEditorShaderStage stage);
