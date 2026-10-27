#include "editor_shader_reload.h"

#include <core/shader_io.h>
#include <platform/filewatch.h>
#include <runtime/runtime_reload.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SHADER_RELOAD_SHUTDOWN_TIMEOUT_MS 2000u
#define SHADER_RELOAD_COMMITS_PER_TICK 2u

typedef struct {
    char *data;
    usize size;
} ShaderReloadStaging;

struct BreakEditorShaderReload {
    const BreakEditorShaderSource *source;
    BreakEditorShaderReloadApply apply;
    void *apply_user;
    BreakEditorShaderReloadLog log;
    void *log_user;

    VFS *vfs;
    BreakRuntimeReload *reload;
    FileWatcher watcher;
    bool watcher_live;
    bool watching;
    bool stopped;
    bool stuck;

    bool pending;
    BreakRuntimeReloadRequest requests[2];
    BreakRuntimeReloadState terminal[2];
    ShaderReloadStaging staging[2];
    bool attempt_failed;
    bool commit_failed;

    u32 shutdown_timeout_ms;
    BreakEditorShaderReloadStats stats;
};

static usize shader_bounded_length(const char *text, usize capacity) {
    usize length = 0u;
    while (length < capacity && text[length] != '\0') {
        length++;
    }
    return length;
}

static bool shader_source_valid(const BreakEditorShaderSource *source) {
    u32 i;
    usize stage;
    if (source == NULL || source->root_count > 5u) {
        return false;
    }
    for (stage = 0u; stage < 2u; stage++) {
        usize length = shader_bounded_length(
            source->logical[stage], sizeof(source->logical[stage]));
        if (length == 0u || length >= sizeof(source->logical[stage]) ||
            length >= (usize)BREAK_RUNTIME_RELOAD_MAX_PATH) {
            return false;
        }
    }
    for (i = 0u; i < source->root_count; i++) {
        usize length = shader_bounded_length(
            source->roots[i], sizeof(source->roots[i]));
        if (length == 0u || length >= sizeof(source->roots[i])) {
            return false;
        }
    }
    return true;
}

static void shader_log(BreakEditorShaderReload *reload, const char *line) {
    if (reload->log != NULL) {
        reload->log(reload->log_user, line);
    }
}

static void shader_clear_staging(BreakEditorShaderReload *reload) {
    usize stage;
    for (stage = 0u; stage < 2u; stage++) {
        free(reload->staging[stage].data);
        reload->staging[stage].data = NULL;
        reload->staging[stage].size = 0u;
    }
}

static bool shader_attempt_active(const BreakEditorShaderReload *reload) {
    return reload->requests[BREAK_EDITOR_SHADER_VERTEX] != 0u ||
           reload->requests[BREAK_EDITOR_SHADER_FRAGMENT] != 0u;
}

static BreakRuntimeError shader_validate(const char *path, const void *bytes,
                                         usize size, void *user) {
    (void)path;
    (void)user;
    return bytes != NULL && size <= (usize)SHADER_MAX_FILE_BYTES
               ? BREAK_RUNTIME_OK
               : BREAK_RUNTIME_FAILED;
}

static BreakRuntimeError shader_commit(const char *path, const void *bytes,
                                       usize size, void *user) {
    BreakEditorShaderReload *reload = (BreakEditorShaderReload *)user;
    BreakEditorShaderStage stage;
    char *copy;
    if (reload == NULL || path == NULL || bytes == NULL ||
        size > (usize)SHADER_MAX_FILE_BYTES) {
        return BREAK_RUNTIME_FAILED;
    }
    if (strcmp(path, reload->source->logical[BREAK_EDITOR_SHADER_VERTEX]) == 0) {
        stage = BREAK_EDITOR_SHADER_VERTEX;
    } else if (strcmp(path,
                      reload->source->logical[BREAK_EDITOR_SHADER_FRAGMENT]) == 0) {
        stage = BREAK_EDITOR_SHADER_FRAGMENT;
    } else {
        reload->commit_failed = true;
        return BREAK_RUNTIME_FAILED;
    }
    if (reload->staging[stage].data != NULL) {
        reload->commit_failed = true;
        return BREAK_RUNTIME_FAILED;
    }
    copy = (char *)malloc(size + 1u);
    if (copy == NULL) {
        reload->commit_failed = true;
        return BREAK_RUNTIME_FAILED;
    }
    if (size > 0u) {
        memcpy(copy, bytes, size);
    }
    copy[size] = '\0';
    reload->staging[stage].data = copy;
    reload->staging[stage].size = size;
    return BREAK_RUNTIME_OK;
}

static void shader_on_file_changed(const char *path, void *user) {
    BreakEditorShaderReload *reload = (BreakEditorShaderReload *)user;
    (void)path;
    reload->pending = true;
    reload->stats.events++;
}

static void shader_watch_candidates(BreakEditorShaderReload *reload) {
    u32 i;
    usize stage;
    filewatch_init(&reload->watcher);
    reload->watcher_live = true;
    for (i = 0u; i < reload->source->root_count; i++) {
        usize root_len = strlen(reload->source->roots[i]);
        for (stage = 0u; stage < 2u; stage++) {
            char path[1024];
            usize logical_len = strlen(reload->source->logical[stage]);
            usize path_len = root_len + 1u + logical_len;
            u32 before;
            if (path_len >= sizeof(path) ||
                path_len >= (usize)FILEWATCH_MAX_PATH) {
                continue;
            }
            memcpy(path, reload->source->roots[i], root_len);
            path[root_len] = '/';
            memcpy(path + root_len + 1u, reload->source->logical[stage],
                   logical_len);
            path[path_len] = '\0';
            before = reload->watcher.count;
            filewatch_add(&reload->watcher, path, shader_on_file_changed,
                          reload);
            if (reload->watcher.count > before) {
                reload->watching = true;
            }
        }
    }
    reload->stats.last_result = reload->watching
                                    ? BREAK_EDITOR_SHADER_RELOAD_IDLE
                                    : BREAK_EDITOR_SHADER_RELOAD_UNAVAILABLE;
}

BreakEditorShaderReload *break_editor_shader_reload_create(
    const BreakEditorShaderSource *source, BreakEditorShaderReloadApply apply,
    void *user) {
    BreakEditorShaderReload *reload;
    BreakRuntimeReloadConfig config;
    u32 i;
    if (!shader_source_valid(source) || apply == NULL) {
        return NULL;
    }
    reload = (BreakEditorShaderReload *)calloc(1u, sizeof(*reload));
    if (reload == NULL) {
        return NULL;
    }
    reload->source = source;
    reload->apply = apply;
    reload->apply_user = user;
    reload->shutdown_timeout_ms = SHADER_RELOAD_SHUTDOWN_TIMEOUT_MS;
    reload->vfs = vfs_create();
    if (reload->vfs == NULL) {
        free(reload);
        return NULL;
    }
    for (i = source->root_count; i > 0u; i--) {
        if (!vfs_mount_dir(reload->vfs, source->roots[i - 1u])) {
            vfs_destroy(reload->vfs);
            free(reload);
            return NULL;
        }
    }
    memset(&config, 0, sizeof(config));
    config.vfs = reload->vfs;
    config.hooks.validate = shader_validate;
    config.hooks.commit = shader_commit;
    config.hooks.user = reload;
    config.worker_count = 1u;
    config.request_capacity = 4u;
    config.event_capacity = 4u;
    config.commit_capacity = 4u;
    if (break_runtime_reload_create(&config, &reload->reload) != BREAK_RUNTIME_OK) {
        reload->reload = NULL;
        vfs_destroy(reload->vfs);
        free(reload);
        return NULL;
    }
    shader_watch_candidates(reload);
    return reload;
}

static void shader_finish_attempt(BreakEditorShaderReload *reload) {
    bool ok = !reload->attempt_failed && !reload->commit_failed;
    usize stage;
    for (stage = 0u; stage < 2u; stage++) {
        if (reload->terminal[stage] != BREAK_RUNTIME_RELOAD_COMMITTED ||
            reload->staging[stage].data == NULL) {
            ok = false;
        }
    }
    if (ok) {
        ok = reload->apply(
            reload->apply_user,
            reload->staging[BREAK_EDITOR_SHADER_VERTEX].data,
            reload->staging[BREAK_EDITOR_SHADER_VERTEX].size,
            reload->staging[BREAK_EDITOR_SHADER_FRAGMENT].data,
            reload->staging[BREAK_EDITOR_SHADER_FRAGMENT].size);
    }
    if (ok) {
        reload->stats.reloads++;
        reload->stats.last_result = BREAK_EDITOR_SHADER_RELOAD_APPLIED;
        shader_log(reload, "shader reload: applied shader pair");
    } else {
        reload->stats.failed++;
        reload->stats.last_result = BREAK_EDITOR_SHADER_RELOAD_FAILED_KEEP_OLD;
        shader_log(reload, "shader reload: failed; keeping current shaders");
    }
    shader_clear_staging(reload);
    reload->attempt_failed = false;
    reload->commit_failed = false;
}

static void shader_consume(BreakEditorShaderReload *reload,
                           BreakEditorShaderStage stage) {
    BreakRuntimeReloadState state = BREAK_RUNTIME_RELOAD_LOADING;
    BreakRuntimeError error;
    if (reload->requests[stage] == 0u) {
        return;
    }
    error = break_runtime_reload_poll(reload->reload, reload->requests[stage],
                                      &state);
    if (error != BREAK_RUNTIME_OK) {
        reload->requests[stage] = 0u;
        reload->attempt_failed = true;
        return;
    }
    if (state != BREAK_RUNTIME_RELOAD_LOADING &&
        state != BREAK_RUNTIME_RELOAD_VALIDATING) {
        reload->requests[stage] = 0u;
        reload->terminal[stage] = state;
        if (state != BREAK_RUNTIME_RELOAD_COMMITTED) {
            reload->attempt_failed = true;
        }
    }
}

static void shader_cancel_and_consume(BreakEditorShaderReload *reload,
                                      BreakEditorShaderStage stage) {
    BreakRuntimeReloadState state = BREAK_RUNTIME_RELOAD_LOADING;
    if (reload->requests[stage] == 0u) {
        return;
    }
    (void)break_runtime_reload_cancel(reload->reload, reload->requests[stage]);
    if (break_runtime_reload_poll(reload->reload, reload->requests[stage],
                                  &state) == BREAK_RUNTIME_OK &&
        state != BREAK_RUNTIME_RELOAD_LOADING &&
        state != BREAK_RUNTIME_RELOAD_VALIDATING) {
        reload->requests[stage] = 0u;
        reload->terminal[stage] = state;
    }
}

static void shader_start_attempt(BreakEditorShaderReload *reload) {
    usize stage;
    reload->pending = false;
    shader_clear_staging(reload);
    reload->attempt_failed = false;
    reload->commit_failed = false;
    for (stage = 0u; stage < 2u; stage++) {
        reload->requests[stage] = 0u;
        reload->terminal[stage] = BREAK_RUNTIME_RELOAD_LOADING;
    }
    reload->stats.attempts++;
    reload->stats.last_result = BREAK_EDITOR_SHADER_RELOAD_BUSY;
    if (break_runtime_reload_request(
            reload->reload,
            reload->source->logical[BREAK_EDITOR_SHADER_VERTEX],
            &reload->requests[BREAK_EDITOR_SHADER_VERTEX]) != BREAK_RUNTIME_OK) {
        reload->attempt_failed = true;
    } else if (break_runtime_reload_request(
                   reload->reload,
                   reload->source->logical[BREAK_EDITOR_SHADER_FRAGMENT],
                   &reload->requests[BREAK_EDITOR_SHADER_FRAGMENT]) !=
               BREAK_RUNTIME_OK) {
        reload->attempt_failed = true;
        shader_cancel_and_consume(reload, BREAK_EDITOR_SHADER_VERTEX);
    }
    if (!shader_attempt_active(reload)) {
        shader_finish_attempt(reload);
    }
}

void break_editor_shader_reload_tick(BreakEditorShaderReload *reload) {
    u32 done = 0u;
    if (reload == NULL || reload->stopped || reload->stuck) {
        return;
    }
    if (reload->watcher_live) {
        filewatch_poll(&reload->watcher);
    }
    if (shader_attempt_active(reload)) {
        if (break_runtime_reload_commit_owner(
                reload->reload, SHADER_RELOAD_COMMITS_PER_TICK, &done) !=
            BREAK_RUNTIME_OK) {
            reload->attempt_failed = true;
        }
        shader_consume(reload, BREAK_EDITOR_SHADER_VERTEX);
        shader_consume(reload, BREAK_EDITOR_SHADER_FRAGMENT);
        if (!shader_attempt_active(reload)) {
            shader_finish_attempt(reload);
        }
    }
    if (!shader_attempt_active(reload) && reload->pending) {
        shader_start_attempt(reload);
    }
}

bool break_editor_shader_reload_request(BreakEditorShaderReload *reload) {
    if (reload == NULL || reload->stopped || reload->stuck ||
        reload->reload == NULL) {
        return false;
    }
    reload->pending = true;
    return true;
}

bool break_editor_shader_reload_stats(
    const BreakEditorShaderReload *reload, BreakEditorShaderReloadStats *out) {
    if (reload == NULL || out == NULL) {
        return false;
    }
    *out = reload->stats;
    out->watching = reload->watching && !reload->stopped && !reload->stuck;
    out->busy = !reload->stopped && !reload->stuck &&
                (reload->pending || shader_attempt_active(reload));
    if (reload->stopped || reload->stuck) {
        out->last_result = BREAK_EDITOR_SHADER_RELOAD_UNAVAILABLE;
    }
    return true;
}

void break_editor_shader_reload_set_logger(
    BreakEditorShaderReload *reload, BreakEditorShaderReloadLog log, void *user) {
    if (reload == NULL) {
        return;
    }
    reload->log = log;
    reload->log_user = user;
    if (log != NULL && !reload->watching && !reload->stopped) {
        shader_log(reload,
                   "shader reload: watch unavailable; manual reload remains available");
    }
}

bool break_editor_shader_reload_shutdown(BreakEditorShaderReload *reload) {
    BreakRuntimeError error;
    bool was_stuck;
    if (reload == NULL) {
        return false;
    }
    if (reload->stopped) {
        return true;
    }
    was_stuck = reload->stuck;
    if (reload->watcher_live) {
        filewatch_shutdown(&reload->watcher);
        reload->watcher_live = false;
    }
    reload->watching = false;
    reload->pending = false;
    if (reload->reload != NULL) {
        error = break_runtime_reload_shutdown(reload->reload,
                                              reload->shutdown_timeout_ms);
        if (error != BREAK_RUNTIME_OK) {
            reload->stuck = true;
            reload->stats.last_result = BREAK_EDITOR_SHADER_RELOAD_UNAVAILABLE;
            if (!was_stuck) {
                shader_log(reload,
                           "shader reload: worker shutdown timed out; owner retained");
            }
            return false;
        }
        break_runtime_reload_destroy(reload->reload);
        reload->reload = NULL;
    }
    if (reload->vfs != NULL) {
        vfs_destroy(reload->vfs);
        reload->vfs = NULL;
    }
    reload->requests[BREAK_EDITOR_SHADER_VERTEX] = 0u;
    reload->requests[BREAK_EDITOR_SHADER_FRAGMENT] = 0u;
    shader_clear_staging(reload);
    reload->attempt_failed = false;
    reload->commit_failed = false;
    reload->stopped = true;
    reload->stuck = false;
    reload->stats.last_result = BREAK_EDITOR_SHADER_RELOAD_UNAVAILABLE;
    return true;
}

void break_editor_shader_reload_destroy(BreakEditorShaderReload *reload) {
    if (reload == NULL) {
        return;
    }
    if (!break_editor_shader_reload_shutdown(reload)) {
        return;
    }
    free(reload);
}

#ifdef BREAK_EDITOR_SHELL_TESTING
void break_editor_shader_reload_set_shutdown_timeout_for_test(
    BreakEditorShaderReload *reload, u32 timeout_ms) {
    if (reload != NULL) {
        reload->shutdown_timeout_ms = timeout_ms;
    }
}
#endif
