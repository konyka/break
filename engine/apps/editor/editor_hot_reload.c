/* BreakEditorHotReload implementation — see editor_hot_reload.h and
 * docs/design/editor_hot_reload.md. */

#include "editor_hot_reload.h"
#include "editor_shell_internal.h"

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <asset/vfs.h>
#include <core/log.h>
#include <editor/editor_cmd.h>
#include <editor/editor_gizmo.h>
#include <editor/editor_i18n.h>
#include <editor/editor_scene.h>
#include <platform/filewatch.h>
#include <runtime/runtime_reload.h>
#include <scene/scene_serial.h>

#define HR_SHUTDOWN_TIMEOUT_MS 2000u
#define HR_COMMITS_PER_TICK 4u

typedef enum HrOutcome {
    HR_OUT_NONE = 0, /* the commit hook has not run for the live request */
    HR_OUT_APPLIED,
    HR_OUT_SKIPPED,  /* hook ran and chose not to apply (counted there) */
    HR_OUT_FAILED    /* hook ran and the load failed (counted there) */
} HrOutcome;

struct BreakEditorHotReload {
    BreakEditorShell *shell; /* borrowed; NULL once the shell is gone */

    VFS *vfs;
    BreakRuntimeReload *reload;
    FileWatcher watcher;
    bool watcher_live;
    bool watching;
    bool stuck; /* a coordinator shutdown timed out; hot reload unavailable */

    char scene_path[BREAK_EDITOR_SCENE_PATH_CAPACITY];
    char name[BREAK_RUNTIME_RELOAD_MAX_PATH]; /* scene file name inside the VFS */

    bool pending; /* the watcher saw a change that has no request yet */
    BreakRuntimeReloadRequest request; /* 0 = none in flight */
    u64 request_epoch;
    HrOutcome outcome;

    u64 local_epoch; /* bumped by every local save/load of the scene */
    bool known_valid;
    u64 known_hash; /* hash of the scene file as last saved/loaded/seen */

    u32 shutdown_timeout_ms;
    BreakEditorHotReloadStats stats;
};

/* ---------------- helpers ---------------- */

static u64 hr_fnv_update(u64 h, const void *data, usize size) {
    const u8 *p = (const u8 *)data;
    usize i;
    for (i = 0u; i < size; i++) {
        h ^= (u64)p[i];
        h *= 1099511628211ULL;
    }
    return h;
}

#define HR_FNV_INIT 14695981039346656037ULL

/* Streams the file through the hash. false when it is missing, unreadable or
 * larger than the scene loader's own cap. */
static bool hr_hash_file(const char *path, u64 *out_hash) {
    FILE *fp = fopen(path, "rb");
    u8 buf[4096];
    u64 h = HR_FNV_INIT;
    u64 total = 0u;
    size_t n;
    if (fp == NULL) {
        return false;
    }
    while ((n = fread(buf, 1u, sizeof(buf), fp)) > 0u) {
        total += (u64)n;
        if (total > (u64)BSCN_MAX_FILE_BYTES) {
            fclose(fp);
            return false;
        }
        h = hr_fnv_update(h, buf, n);
    }
    if (ferror(fp)) {
        fclose(fp);
        return false;
    }
    fclose(fp);
    *out_hash = h;
    return true;
}

static void hr_log(const BreakEditorHotReload *hr, const char *fmt, ...) {
    char line[160];
    va_list ap;
    if (hr == NULL || hr->shell == NULL) {
        return;
    }
    va_start(ap, fmt);
    (void)vsnprintf(line, sizeof(line), fmt, ap);
    va_end(ap);
    editor_shell_log(hr->shell, "%s", line);
}

/* Splits "<dir>/<name>"; a bare name watches the working directory. Returns
 * false when either part does not fit the VFS / coordinator bounds. */
static bool hr_split_path(const char *path, char *dir, usize dir_cap,
                          char *name, usize name_cap) {
    const char *slash = strrchr(path, '/');
    const char *back = strrchr(path, '\\');
    const char *sep = slash;
    usize dir_len;
    usize name_len;
    if (back != NULL && (sep == NULL || back > sep)) {
        sep = back;
    }
    if (sep == NULL) {
        if (dir_cap < 2u) {
            return false;
        }
        dir[0] = '.';
        dir[1] = '\0';
        name_len = strlen(path);
        if (name_len == 0u || name_len + 1u > name_cap) {
            return false;
        }
        memcpy(name, path, name_len + 1u);
        return true;
    }
    dir_len = (usize)(sep - path);
    name_len = strlen(sep + 1);
    if (name_len == 0u || name_len + 1u > name_cap) {
        return false;
    }
    if (dir_len == 0u) { /* "/scene.bscn": the root directory */
        if (dir_cap < 2u) {
            return false;
        }
        dir[0] = '/';
        dir[1] = '\0';
    } else {
        if (dir_len + 1u > dir_cap) {
            return false;
        }
        memcpy(dir, path, dir_len);
        dir[dir_len] = '\0';
    }
    memcpy(name, sep + 1, name_len + 1u);
    return true;
}

/* ---------------- coordinator hooks ---------------- */

/* Worker thread: a pure check over the staged bytes. */
static BreakRuntimeError hr_validate(const char *path, const void *bytes,
                                     usize size, void *user) {
    const u8 *b = (const u8 *)bytes;
    u32 magic;
    (void)path;
    (void)user;
    if (b == NULL || size < 8u) {
        return BREAK_RUNTIME_FAILED;
    }
    magic = (u32)b[0] | ((u32)b[1] << 8) | ((u32)b[2] << 16) |
            ((u32)b[3] << 24);
    return magic == BSCN_MAGIC ? BREAK_RUNTIME_OK : BREAK_RUNTIME_FAILED;
}

/* Shell thread (inside break_runtime_reload_commit_owner). Order matters:
 * stale, then same-as-known, then dirty, then apply. */
static BreakRuntimeError hr_commit(const char *path, const void *bytes,
                                   usize size, void *user) {
    BreakEditorHotReload *hr = (BreakEditorHotReload *)user;
    BreakEditorShell *shell = hr->shell;
    BreakEditorDoc *doc;
    u64 h;
    (void)path;
    if (shell == NULL) {
        hr->outcome = HR_OUT_SKIPPED;
        return BREAK_RUNTIME_FAILED;
    }
    if (hr->request_epoch != hr->local_epoch) {
        hr->stats.skipped_stale++;
        hr->outcome = HR_OUT_SKIPPED;
        hr_log(hr, break_editor_tr(BREAK_EDITOR_TR_LOG_HR_STALE_FMT),
               hr->name);
        return BREAK_RUNTIME_FAILED;
    }
    h = hr_fnv_update(HR_FNV_INIT, bytes, size);
    if (hr->known_valid && h == hr->known_hash) {
        hr->stats.skipped_same++;
        hr->outcome = HR_OUT_SKIPPED;
        return BREAK_RUNTIME_FAILED;
    }
    /* an open gizmo drag is closed first (same policy as external undo) */
    break_editor_gizmo_end_drag(break_editor_shell_gizmo(shell));
    doc = break_editor_shell_doc(shell);
    /* "Local edits" = unsaved AND user-made: the document is dirty and has
     * command history. Dirty alone is not enough (a scene loaded without a
     * sidecar is dirty only for its generated names), and history alone is
     * not enough (after Ctrl+S the document matches the file and the undo
     * history is kept). Undoing back to the saved state stays dirty, which
     * errs on the side of keeping the user's session. */
    if (break_editor_doc_is_dirty(doc) &&
        break_editor_cmd_stack_size(break_editor_doc_stack(doc)) > 0u) {
        hr->stats.skipped_dirty++;
        hr->outcome = HR_OUT_SKIPPED;
        hr_log(hr, break_editor_tr(BREAK_EDITOR_TR_LOG_HR_SKIPPED_DIRTY_FMT),
               hr->name);
        return BREAK_RUNTIME_FAILED;
    }
    if (!break_editor_doc_load_bytes(doc, hr->scene_path, bytes, size)) {
        hr->stats.failed++;
        hr->outcome = HR_OUT_FAILED;
        hr_log(hr, break_editor_tr(BREAK_EDITOR_TR_LOG_HR_NOT_SCENE_FMT), hr->name);
        return BREAK_RUNTIME_FAILED;
    }
    hr->known_valid = true;
    hr->known_hash = h;
    hr->stats.reloads++;
    hr->outcome = HR_OUT_APPLIED;
    editor_shell_refresh_all(shell);
    hr_log(hr, break_editor_tr(BREAK_EDITOR_TR_LOG_HR_RELOADED_FMT), hr->name,
           (unsigned)break_editor_doc_entity_count(doc));
    return BREAK_RUNTIME_OK;
}

static void hr_on_file_changed(const char *path, void *user) {
    BreakEditorHotReload *hr = (BreakEditorHotReload *)user;
    (void)path;
    hr->pending = true;
    hr->stats.events++;
}

/* ---------------- lifecycle ---------------- */

/* Stops watching and tears the coordinator down. false when a worker did not
 * stop in time: nothing is freed, the object becomes `stuck`. */
static bool hr_stop(BreakEditorHotReload *hr) {
    if (hr->stuck) {
        return false;
    }
    if (hr->watcher_live) {
        filewatch_shutdown(&hr->watcher);
        hr->watcher_live = false;
    }
    hr->watching = false;
    hr->pending = false;
    hr->request = 0u;
    hr->outcome = HR_OUT_NONE;
    if (hr->reload != NULL) {
        BreakRuntimeError e =
            break_runtime_reload_shutdown(hr->reload, hr->shutdown_timeout_ms);
        if (e != BREAK_RUNTIME_OK) {
            hr->stuck = true;
            return false;
        }
        break_runtime_reload_destroy(hr->reload);
        hr->reload = NULL;
    }
    if (hr->vfs != NULL) {
        vfs_destroy(hr->vfs);
        hr->vfs = NULL;
    }
    return true;
}

BreakEditorHotReload *break_editor_hot_reload_create(BreakEditorShell *shell) {
    BreakEditorHotReload *hr;
    if (shell == NULL) {
        return NULL;
    }
    hr = (BreakEditorHotReload *)calloc(1u, sizeof(*hr));
    if (hr == NULL) {
        return NULL;
    }
    hr->shell = shell;
    hr->shutdown_timeout_ms = HR_SHUTDOWN_TIMEOUT_MS;
    return hr;
}

void break_editor_hot_reload_destroy(BreakEditorHotReload *hr) {
    if (hr == NULL) {
        return;
    }
    if (hr->shell != NULL && break_editor_shell_hot_reload(hr->shell) == hr) {
        break_editor_shell_set_hot_reload(hr->shell, NULL);
    }
    hr->shell = NULL;
    if (hr->stuck) {
        /* a retry after the earlier timeout */
        hr->stuck = false;
    }
    if (!hr_stop(hr)) {
        /* A worker is still running inside the VFS read: freeing the VFS or
         * the coordinator now would be a use-after-free. The leak is bounded
         * (one coordinator + one VFS) and reported. */
        LOG_ERROR("editor hot reload: worker did not stop; leaking the "
                  "coordinator instead of freeing it under a live thread");
        return; /* hr is kept too: the coordinator's hooks hold it */
    }
    free(hr);
}

void editor_hot_reload_shell_destroyed(BreakEditorHotReload *hr,
                                       BreakEditorShell *shell) {
    if (hr != NULL && hr->shell == shell) {
        hr->shell = NULL;
    }
}

void editor_hot_reload_attach(BreakEditorHotReload *hr,
                              BreakEditorShell *shell) {
    if (hr != NULL) {
        hr->shell = shell;
    }
}

static void hr_rebaseline(BreakEditorHotReload *hr) {
    u64 h = 0u;
    hr->known_valid = hr_hash_file(hr->scene_path, &h);
    hr->known_hash = hr->known_valid ? h : 0u;
}

bool break_editor_hot_reload_set_scene(BreakEditorHotReload *hr,
                                       const char *scene_path) {
    char dir[VFS_MAX_PATH];
    BreakRuntimeReloadConfig cfg;
    size_t len;
    if (hr == NULL) {
        return false;
    }
    if (scene_path != NULL && hr->watching &&
        strcmp(scene_path, hr->scene_path) == 0) {
        /* same scene: a local load of it. Whatever is in flight predates the
         * load, and the file on disk is the new baseline. */
        hr->local_epoch++;
        hr_rebaseline(hr);
        return true;
    }
    if (!hr_stop(hr)) {
        hr_log(hr, "%s", break_editor_tr(BREAK_EDITOR_TR_LOG_HR_DISABLED_STUCK));
        return false;
    }
    hr->scene_path[0] = '\0';
    hr->name[0] = '\0';
    hr->local_epoch++;
    if (scene_path == NULL || scene_path[0] == '\0') {
        return true;
    }
    len = strlen(scene_path);
    if (len >= sizeof(hr->scene_path) || len >= (size_t)FILEWATCH_MAX_PATH ||
        !hr_split_path(scene_path, dir, sizeof(dir), hr->name,
                       sizeof(hr->name))) {
        hr->name[0] = '\0';
        hr_log(hr, "%s", break_editor_tr(BREAK_EDITOR_TR_LOG_HR_DISABLED_PATH));
        return false;
    }
    memcpy(hr->scene_path, scene_path, len + 1u);

    hr->vfs = vfs_create();
    if (hr->vfs == NULL || !vfs_mount_dir(hr->vfs, dir)) {
        (void)hr_stop(hr);
        hr_log(hr, "%s", break_editor_tr(BREAK_EDITOR_TR_LOG_HR_DISABLED_MOUNT));
        return false;
    }
    memset(&cfg, 0, sizeof(cfg));
    cfg.vfs = hr->vfs;
    cfg.hooks.validate = hr_validate;
    cfg.hooks.commit = hr_commit;
    cfg.hooks.user = hr;
    cfg.worker_count = 1u;
    cfg.request_capacity = 4u;
    cfg.event_capacity = 4u;
    cfg.commit_capacity = 4u;
    if (break_runtime_reload_create(&cfg, &hr->reload) != BREAK_RUNTIME_OK) {
        hr->reload = NULL;
        (void)hr_stop(hr);
        hr_log(hr, "%s", break_editor_tr(BREAK_EDITOR_TR_LOG_HR_DISABLED_COORD));
        return false;
    }
    hr_rebaseline(hr);
    filewatch_init(&hr->watcher);
    hr->watcher_live = true;
    filewatch_add(&hr->watcher, hr->scene_path, hr_on_file_changed, hr);
    if (hr->watcher.count == 0u) {
        (void)hr_stop(hr);
        hr_log(hr, "%s", break_editor_tr(BREAK_EDITOR_TR_LOG_HR_DISABLED_WATCH));
        return false;
    }
    hr->watching = true;
    return true;
}

/* ---------------- per-frame driver ---------------- */

static void hr_finish(BreakEditorHotReload *hr, BreakRuntimeReloadState state) {
    if (hr->outcome == HR_OUT_NONE && state != BREAK_RUNTIME_RELOAD_COMMITTED &&
        state != BREAK_RUNTIME_RELOAD_CANCELLED) {
        /* failed before the commit hook: unreadable file or not a BSCN */
        hr->stats.failed++;
        hr_log(hr, break_editor_tr(BREAK_EDITOR_TR_LOG_HR_UNREADABLE_FMT), hr->name);
    }
    hr->outcome = HR_OUT_NONE;
    hr->request = 0u;
}

void break_editor_hot_reload_tick(BreakEditorHotReload *hr) {
    u32 done = 0u;
    if (hr == NULL || hr->shell == NULL || !hr->watching || hr->stuck) {
        return;
    }
    filewatch_poll(&hr->watcher);

    (void)break_runtime_reload_commit_owner(hr->reload, HR_COMMITS_PER_TICK,
                                            &done);
    if (hr->request != 0u) {
        BreakRuntimeReloadState state = BREAK_RUNTIME_RELOAD_LOADING;
        BreakRuntimeError e =
            break_runtime_reload_poll(hr->reload, hr->request, &state);
        if (e != BREAK_RUNTIME_OK) {
            hr->request = 0u; /* stale handle: nothing left to wait for */
            hr->outcome = HR_OUT_NONE;
        } else if (state != BREAK_RUNTIME_RELOAD_LOADING &&
                   state != BREAK_RUNTIME_RELOAD_VALIDATING) {
            hr_finish(hr, state);
        }
    }
    if (hr->request == 0u && hr->pending) {
        BreakRuntimeReloadRequest req = 0u;
        hr->pending = false;
        if (break_runtime_reload_request(hr->reload, hr->name, &req) ==
            BREAK_RUNTIME_OK) {
            hr->request = req;
            hr->request_epoch = hr->local_epoch;
            hr->outcome = HR_OUT_NONE;
            hr->stats.requests++;
        } else {
            hr->stats.failed++;
            hr_log(hr, break_editor_tr(BREAK_EDITOR_TR_LOG_HR_START_FAILED_FMT), hr->name);
        }
    }
}

void break_editor_hot_reload_note_saved(BreakEditorHotReload *hr) {
    if (hr == NULL || !hr->watching) {
        return;
    }
    hr->local_epoch++;
    hr_rebaseline(hr);
}

bool break_editor_hot_reload_stats(const BreakEditorHotReload *hr,
                                   BreakEditorHotReloadStats *out_stats) {
    if (hr == NULL || out_stats == NULL) {
        return false;
    }
    *out_stats = hr->stats;
    out_stats->watching = hr->watching;
    out_stats->busy = hr->pending || hr->request != 0u;
    return true;
}

#ifdef BREAK_EDITOR_SHELL_TESTING
void break_editor_hot_reload_set_shutdown_timeout_for_test(
    BreakEditorHotReload *hr, u32 timeout_ms) {
    if (hr != NULL) {
        hr->shutdown_timeout_ms = timeout_ms;
    }
}
#endif
