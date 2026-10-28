#pragma once

#include "editor_shader_source.h"

typedef enum { BREAK_EDITOR_SHADER_RELOAD_IDLE = 0,
               BREAK_EDITOR_SHADER_RELOAD_BUSY,
               BREAK_EDITOR_SHADER_RELOAD_APPLIED,
               BREAK_EDITOR_SHADER_RELOAD_FAILED_KEEP_OLD,
               BREAK_EDITOR_SHADER_RELOAD_UNAVAILABLE } BreakEditorShaderReloadResult;

typedef struct {
    bool owner_present; /* a reload owner exists (false: never created) */
    bool stopping;      /* shutdown began; new requests are rejected */
    bool watching;      /* at least one candidate path registered */
    bool busy;
    int last_result;
    u64 events, attempts, reloads, failed;
} BreakEditorShaderReloadStats;

typedef void (*BreakEditorShaderReloadLog)(void *user, const char *line);
typedef bool (*BreakEditorShaderReloadApply)(
    void *user, const void *vert, usize vert_size,
    const void *frag, usize frag_size);

typedef struct BreakEditorShaderReload BreakEditorShaderReload;

/* The source and apply user are borrowed until shutdown/destroy. apply and the
 * logger run only on the thread that calls tick/shutdown; coordinator workers
 * only validate bounded source bytes. */
BreakEditorShaderReload *break_editor_shader_reload_create(
    const BreakEditorShaderSource *source, BreakEditorShaderReloadApply apply,
    void *user);
/* Stops watching, then stops the coordinator with a bounded wait. false keeps
 * the complete object/VFS/coordinator alive for a later retry. */
bool break_editor_shader_reload_shutdown(BreakEditorShaderReload *reload);
/* Retries shutdown. A timeout deliberately leaks one bounded owner rather than
 * freeing state still referenced by a worker. */
void break_editor_shader_reload_destroy(BreakEditorShaderReload *reload);
void break_editor_shader_reload_tick(BreakEditorShaderReload *reload);
bool break_editor_shader_reload_request(BreakEditorShaderReload *reload);
bool break_editor_shader_reload_stats(
    const BreakEditorShaderReload *reload, BreakEditorShaderReloadStats *out);
void break_editor_shader_reload_set_logger(
    BreakEditorShaderReload *reload, BreakEditorShaderReloadLog log, void *user);

#ifdef BREAK_EDITOR_SHELL_TESTING
/* Runs between the vertex and the fragment admission of an attempt, so a
 * test can let the worker get ahead of the owner thread there. */
void break_editor_shader_reload_set_between_requests_for_test(
    BreakEditorShaderReload *reload, void (*fn)(void *user), void *user);
void break_editor_shader_reload_set_shutdown_timeout_for_test(
    BreakEditorShaderReload *reload, u32 timeout_ms);
#endif
