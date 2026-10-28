#include "editor_image_preview.h"

#include <asset/vfs.h>
#include <editor/editor_i18n.h>
#include <editor/editor_image.h>
#include <platform/filewatch.h>
#include <runtime/runtime_reload.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define IMAGE_PREVIEW_SHUTDOWN_TIMEOUT_MS 2000u
#define IMAGE_PREVIEW_COMMITS_PER_TICK 2u

struct BreakEditorImagePreview {
    RHIDevice *device; /* borrowed */
    BreakEditorImagePreviewLog log;
    void *log_user;

    char path[BREAK_EDITOR_IMAGE_PREVIEW_PATH_CAPACITY]; /* "" = none */
    const char *logical; /* points into path: the file name in the VFS */
    VFS *vfs;            /* mounted on the file's directory; NULL = none */
    BreakRuntimeReload *reload;
    FileWatcher watcher;
    bool watcher_live;
    bool watching;
    bool stopped;
    bool stuck;

    bool pending;
    BreakRuntimeReloadRequest request; /* 0 = no attempt active */
    BreakEditorImage staging;          /* decoded by the commit hook */
    bool commit_failed;

    BreakEditorImage current; /* the image the preview shows */
    RHITexture texture;       /* of `current` on `device`; may be null */
    bool upload_pending;      /* current has no texture yet */

    u32 shutdown_timeout_ms;
    BreakEditorImagePreviewStats stats;
};

static void preview_log(BreakEditorImagePreview *p, const char *line) {
    if (p->log != NULL) {
        p->log(p->log_user, line);
    }
}

/* Worker thread: header only (bounded, no owner state). */
static BreakRuntimeError preview_validate(const char *path, const void *bytes,
                                          usize size, void *user) {
    u32 w = 0u, h = 0u;
    (void)path;
    (void)user;
    return break_editor_image_probe(bytes, size, &w, &h) ? BREAK_RUNTIME_OK
                                                          : BREAK_RUNTIME_FAILED;
}

/* Owner thread (inside commit_owner): decode the borrowed bytes into owned
 * staging pixels. The probe bound keeps this decode bounded. */
static BreakRuntimeError preview_commit(const char *path, const void *bytes,
                                        usize size, void *user) {
    BreakEditorImagePreview *p = (BreakEditorImagePreview *)user;
    (void)path;
    if (p == NULL || p->staging.rgba != NULL) {
        if (p != NULL) p->commit_failed = true;
        return BREAK_RUNTIME_FAILED;
    }
    if (!break_editor_image_decode(bytes, size, &p->staging)) {
        p->commit_failed = true;
        return BREAK_RUNTIME_FAILED;
    }
    return BREAK_RUNTIME_OK;
}

static void preview_on_file_changed(const char *path, void *user) {
    BreakEditorImagePreview *p = (BreakEditorImagePreview *)user;
    (void)path;
    p->pending = true;
    p->stats.events++;
}

static void preview_destroy_texture(BreakEditorImagePreview *p) {
    if (rhi_handle_valid(p->texture) && p->device != NULL) {
        rhi_texture_destroy(p->device, p->texture);
    }
    p->texture = RHI_HANDLE_NULL;
}

static bool preview_create_texture(BreakEditorImagePreview *p,
                                   const BreakEditorImage *img,
                                   RHITexture *out) {
    RHITextureDesc desc;
    memset(&desc, 0, sizeof(desc));
    desc.width = img->width;
    desc.height = img->height;
    desc.format = RHI_FORMAT_R8G8B8A8_UNORM;
    desc.mip_levels = 1u;
    desc.data = img->rgba;
    *out = rhi_texture_create(p->device, &desc);
    return rhi_handle_valid(*out);
}

/* Stops the live request (if any) and the per-file machinery. Returns false
 * when the coordinator did not stop in time (everything is kept). */
static bool preview_close_file(BreakEditorImagePreview *p) {
    if (p->watcher_live) {
        filewatch_shutdown(&p->watcher);
        p->watcher_live = false;
    }
    p->watching = false;
    p->pending = false;
    if (p->reload != NULL) {
        if (break_runtime_reload_shutdown(p->reload, p->shutdown_timeout_ms) !=
            BREAK_RUNTIME_OK) {
            return false;
        }
        break_runtime_reload_destroy(p->reload);
        p->reload = NULL;
    }
    if (p->vfs != NULL) {
        vfs_destroy(p->vfs);
        p->vfs = NULL;
    }
    p->request = 0u;
    break_editor_image_free(&p->staging);
    p->commit_failed = false;
    return true;
}

static void preview_watch_current(BreakEditorImagePreview *p);

static bool preview_open_file(BreakEditorImagePreview *p) {
    BreakRuntimeReloadConfig config;
    char dir[BREAK_EDITOR_IMAGE_PREVIEW_PATH_CAPACITY];
    usize dir_len = (usize)(p->logical - p->path) - 1u; /* without the '/' */
    if (dir_len == 0u) {
        dir[0] = '/'; /* a file directly under the root */
        dir[1] = '\0';
    } else {
        memcpy(dir, p->path, dir_len);
        dir[dir_len] = '\0';
    }
    p->vfs = vfs_create();
    if (p->vfs == NULL || !vfs_mount_dir(p->vfs, dir)) {
        return false;
    }
    memset(&config, 0, sizeof(config));
    config.vfs = p->vfs;
    config.hooks.validate = preview_validate;
    config.hooks.commit = preview_commit;
    config.hooks.user = p;
    config.worker_count = 1u;
    config.request_capacity = 4u;
    config.event_capacity = 4u;
    config.commit_capacity = 4u;
    if (break_runtime_reload_create(&config, &p->reload) != BREAK_RUNTIME_OK) {
        p->reload = NULL;
        return false;
    }
    preview_watch_current(p);
    return true;
}

BreakEditorImagePreview *break_editor_image_preview_create(void) {
    BreakEditorImagePreview *p =
        (BreakEditorImagePreview *)calloc(1u, sizeof(*p));
    if (p == NULL) {
        return NULL;
    }
    p->shutdown_timeout_ms = IMAGE_PREVIEW_SHUTDOWN_TIMEOUT_MS;
    p->stats.last_result = BREAK_EDITOR_IMAGE_PREVIEW_EMPTY;
    return p;
}

void break_editor_image_preview_set_device(BreakEditorImagePreview *p,
                                           RHIDevice *device) {
    if (p == NULL || p->device == device) {
        return;
    }
    preview_destroy_texture(p);
    p->device = device;
    p->upload_pending = p->current.rgba != NULL && device != NULL;
}

void break_editor_image_preview_set_logger(BreakEditorImagePreview *p,
                                           BreakEditorImagePreviewLog log,
                                           void *user) {
    if (p != NULL) {
        p->log = log;
        p->log_user = user;
    }
}

static void preview_drop_current(BreakEditorImagePreview *p) {
    preview_destroy_texture(p);
    break_editor_image_free(&p->current);
    p->upload_pending = false;
    p->stats.has_image = false;
    p->stats.width = 0u;
    p->stats.height = 0u;
}

static void preview_watch_current(BreakEditorImagePreview *p) {
    filewatch_init(&p->watcher);
    p->watcher_live = true;
    p->watching = false;
    if (strlen(p->path) < (usize)FILEWATCH_MAX_PATH) {
        u32 before = p->watcher.count;
        filewatch_add_with_missing(&p->watcher, p->path,
                                   preview_on_file_changed, p);
        p->watching = p->watcher.count > before;
    }
}

static bool preview_retarget_same_dir(BreakEditorImagePreview *p,
                                      const char *path, usize len,
                                      const char *slash) {
    if (p->request != 0u) {
        BreakRuntimeReloadState state = BREAK_RUNTIME_RELOAD_LOADING;
        (void)break_runtime_reload_cancel(p->reload, p->request);
        /* consume a terminal state now; a request that is mid-commit
         * finishes on the owner thread later and is dropped below */
        (void)break_runtime_reload_poll(p->reload, p->request, &state);
        p->request = 0u;
    }
    break_editor_image_free(&p->staging);
    p->commit_failed = false;
    if (p->watcher_live) {
        filewatch_shutdown(&p->watcher);
        p->watcher_live = false;
    }
    preview_drop_current(p);
    memcpy(p->path, path, len + 1u);
    p->logical = p->path + (slash - path) + 1;
    preview_watch_current(p);
    p->pending = true;
    p->stats.last_result = BREAK_EDITOR_IMAGE_PREVIEW_BUSY;
    return true;
}

bool break_editor_image_preview_set_path(BreakEditorImagePreview *p,
                                         const char *path) {
    usize len;
    const char *slash;
    if (p == NULL || p->stopped || p->stuck || path == NULL) {
        return false;
    }
    len = strlen(path);
    if (len == 0u || len >= sizeof(p->path) ||
        len >= (usize)BREAK_RUNTIME_RELOAD_MAX_PATH) {
        return false;
    }
    slash = strrchr(path, '/');
    if (slash == NULL || slash[1] == '\0') {
        return false; /* needs a directory and a file name */
    }
    if (p->reload != NULL && p->logical != NULL &&
        (usize)(p->logical - p->path) == (usize)(slash - path) + 1u &&
        memcmp(p->path, path, (usize)(slash - path)) == 0) {
        /* same directory: keep the coordinator and VFS, cancel the live
         * request (a late result goes stale with its handle) and re-target
         * the watcher */
        return preview_retarget_same_dir(p, path, len, slash);
    }
    if (!preview_close_file(p)) {
        p->stuck = true;
        p->stats.last_result = BREAK_EDITOR_IMAGE_PREVIEW_UNAVAILABLE;
        preview_log(p, break_editor_tr(BREAK_EDITOR_TR_LOG_IMG_SHUTDOWN_TIMEOUT));
        return false;
    }
    /* a new directory: drop the old image */
    preview_drop_current(p);
    memcpy(p->path, path, len + 1u);
    p->logical = p->path + (slash - path) + 1;
    if (!preview_open_file(p)) {
        (void)preview_close_file(p);
        p->path[0] = '\0';
        p->logical = NULL;
        p->stats.last_result = BREAK_EDITOR_IMAGE_PREVIEW_UNAVAILABLE;
        return false;
    }
    p->pending = true;
    p->stats.last_result = BREAK_EDITOR_IMAGE_PREVIEW_BUSY;
    return true;
}

bool break_editor_image_preview_request(BreakEditorImagePreview *p) {
    if (p == NULL || p->stopped || p->stuck || p->reload == NULL) {
        return false;
    }
    p->pending = true;
    return true;
}

static void preview_finish_attempt(BreakEditorImagePreview *p,
                                   BreakRuntimeReloadState terminal) {
    bool ok = terminal == BREAK_RUNTIME_RELOAD_COMMITTED && !p->commit_failed &&
              p->staging.rgba != NULL;
    RHITexture fresh = RHI_HANDLE_NULL;
    if (ok && p->device != NULL) {
        ok = preview_create_texture(p, &p->staging, &fresh);
    }
    if (ok) {
        char line[96];
        preview_destroy_texture(p);
        break_editor_image_free(&p->current);
        p->current = p->staging;
        memset(&p->staging, 0, sizeof(p->staging));
        p->texture = fresh;
        p->upload_pending = false;
        p->stats.has_image = true;
        p->stats.width = p->current.width;
        p->stats.height = p->current.height;
        p->stats.reloads++;
        p->stats.last_result = BREAK_EDITOR_IMAGE_PREVIEW_APPLIED;
        snprintf(line, sizeof(line),
                 break_editor_tr(BREAK_EDITOR_TR_LOG_IMG_APPLIED_FMT),
                 (unsigned)p->current.width, (unsigned)p->current.height);
        preview_log(p, line);
    } else {
        p->stats.failed++;
        p->stats.last_result = BREAK_EDITOR_IMAGE_PREVIEW_FAILED_KEEP_OLD;
        preview_log(p, break_editor_tr(BREAK_EDITOR_TR_LOG_IMG_FAILED));
    }
    break_editor_image_free(&p->staging);
    p->commit_failed = false;
    p->request = 0u;
}

void break_editor_image_preview_tick(BreakEditorImagePreview *p) {
    u32 done = 0u;
    if (p == NULL || p->stopped || p->stuck || p->reload == NULL) {
        return;
    }
    if (p->upload_pending && p->device != NULL && p->current.rgba != NULL) {
        RHITexture t;
        if (preview_create_texture(p, &p->current, &t)) {
            p->texture = t;
        }
        p->upload_pending = false; /* one try per device attach */
    }
    if (p->watcher_live) {
        filewatch_poll(&p->watcher);
    }
    /* pumped every tick: also reclaims commit commands of cancelled
     * requests (see the 2026-10-28 shader reload fix) */
    (void)break_runtime_reload_commit_owner(
        p->reload, IMAGE_PREVIEW_COMMITS_PER_TICK, &done);
    if (p->request != 0u) {
        BreakRuntimeReloadState state = BREAK_RUNTIME_RELOAD_LOADING;
        BreakRuntimeError e =
            break_runtime_reload_poll(p->reload, p->request, &state);
        if (e != BREAK_RUNTIME_OK) {
            preview_finish_attempt(p, BREAK_RUNTIME_RELOAD_FAILED_KEEP_OLD);
        } else if (state != BREAK_RUNTIME_RELOAD_LOADING &&
                   state != BREAK_RUNTIME_RELOAD_VALIDATING) {
            preview_finish_attempt(p, state);
        }
    }
    if (p->request == 0u && p->pending) {
        p->pending = false;
        p->stats.attempts++;
        p->stats.last_result = BREAK_EDITOR_IMAGE_PREVIEW_BUSY;
        break_editor_image_free(&p->staging);
        p->commit_failed = false;
        if (break_runtime_reload_request(p->reload, p->logical, &p->request) !=
            BREAK_RUNTIME_OK) {
            p->request = 0u;
            preview_finish_attempt(p, BREAK_RUNTIME_RELOAD_FAILED_KEEP_OLD);
        }
    }
}

RHITexture break_editor_image_preview_texture(
    const BreakEditorImagePreview *p) {
    return p != NULL ? p->texture : RHI_HANDLE_NULL;
}

const char *break_editor_image_preview_path(const BreakEditorImagePreview *p) {
    return p != NULL ? p->path : "";
}

bool break_editor_image_preview_stats(const BreakEditorImagePreview *p,
                                      BreakEditorImagePreviewStats *out) {
    if (p == NULL || out == NULL) {
        return false;
    }
    *out = p->stats;
    out->watching = p->watching && !p->stopped && !p->stuck;
    out->busy = !p->stopped && !p->stuck && (p->pending || p->request != 0u);
    if (p->stopped || p->stuck) {
        out->last_result = BREAK_EDITOR_IMAGE_PREVIEW_UNAVAILABLE;
    }
    return true;
}

bool break_editor_image_preview_shutdown(BreakEditorImagePreview *p) {
    bool was_stuck;
    if (p == NULL) {
        return false;
    }
    if (p->stopped) {
        return true;
    }
    was_stuck = p->stuck;
    if (!preview_close_file(p)) {
        p->stuck = true;
        if (!was_stuck) {
            preview_log(p,
                        break_editor_tr(BREAK_EDITOR_TR_LOG_IMG_SHUTDOWN_TIMEOUT));
        }
        return false;
    }
    preview_destroy_texture(p);
    break_editor_image_free(&p->current);
    p->stopped = true;
    p->stuck = false;
    return true;
}

void break_editor_image_preview_destroy(BreakEditorImagePreview *p) {
    if (p == NULL) {
        return;
    }
    if (!break_editor_image_preview_shutdown(p)) {
        return;
    }
    free(p);
}

#ifdef BREAK_EDITOR_SHELL_TESTING
void break_editor_image_preview_set_shutdown_timeout_for_test(
    BreakEditorImagePreview *p, u32 timeout_ms) {
    if (p != NULL) {
        p->shutdown_timeout_ms = timeout_ms;
    }
}
#endif
