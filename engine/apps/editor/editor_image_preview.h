#pragma once

/* Asset-browser image preview with hot reload (design
 * docs/superpowers/specs/2026-10-28-editor-texture-preview-reload-design.md).
 *
 * One owner, one file at a time. A Runtime Core reload coordinator (1 worker)
 * reads the file through a VFS mounted on its directory; the worker only
 * probes the header (break_editor_image_probe). The owner thread decodes in
 * the commit hook and, in tick, creates the new RHITexture and destroys the
 * old one only after the new one exists. Any failure keeps the current
 * texture. Changes during an attempt set one trailing pending flag.
 *
 * Without a device the owner still decodes and counts reloads, and reports
 * the decoded size, but creates no texture (headless shell). Everything runs
 * on the thread that calls set_path/tick/shutdown, except the probe. */

#include <core/types.h>
#include <rhi/rhi.h>

#define BREAK_EDITOR_IMAGE_PREVIEW_PATH_CAPACITY 1024u

typedef enum {
    BREAK_EDITOR_IMAGE_PREVIEW_EMPTY = 0,  /* no file selected */
    BREAK_EDITOR_IMAGE_PREVIEW_BUSY,
    BREAK_EDITOR_IMAGE_PREVIEW_APPLIED,
    BREAK_EDITOR_IMAGE_PREVIEW_FAILED_KEEP_OLD,
    BREAK_EDITOR_IMAGE_PREVIEW_UNAVAILABLE /* stopped or setup failed */
} BreakEditorImagePreviewResult;

typedef struct {
    bool has_image; /* a decoded image is current (texture or headless) */
    bool busy;
    bool watching;
    int last_result;
    u32 width, height; /* of the current image; 0 when none */
    u64 attempts, reloads, failed, events;
} BreakEditorImagePreviewStats;

typedef struct BreakEditorImagePreview BreakEditorImagePreview;
typedef void (*BreakEditorImagePreviewLog)(void *user, const char *line);

BreakEditorImagePreview *break_editor_image_preview_create(void);
/* NULL detaches; the current texture is destroyed on the device it was
 * created on before the switch. Borrowed until detach/destroy. */
void break_editor_image_preview_set_device(BreakEditorImagePreview *preview,
                                           RHIDevice *device);
void break_editor_image_preview_set_logger(BreakEditorImagePreview *preview,
                                           BreakEditorImagePreviewLog log,
                                           void *user);
/* Absolute path of an image file. Rejects NULL/empty/over-long/directory-less
 * paths (false, nothing changes). A new path drops the current image, cancels
 * the live request and queues a load of the new file. */
bool break_editor_image_preview_set_path(BreakEditorImagePreview *preview,
                                         const char *path);
/* Queue a reload of the current file (no-op false without one). */
bool break_editor_image_preview_request(BreakEditorImagePreview *preview);
void break_editor_image_preview_tick(BreakEditorImagePreview *preview);
RHITexture break_editor_image_preview_texture(
    const BreakEditorImagePreview *preview);
const char *break_editor_image_preview_path(
    const BreakEditorImagePreview *preview); /* "" when none */
bool break_editor_image_preview_stats(const BreakEditorImagePreview *preview,
                                      BreakEditorImagePreviewStats *out);
/* Bounded stop; false keeps everything alive for a retry. */
bool break_editor_image_preview_shutdown(BreakEditorImagePreview *preview);
/* Retries shutdown; a timeout leaks the owner rather than freeing state a
 * worker still references. */
void break_editor_image_preview_destroy(BreakEditorImagePreview *preview);

#ifdef BREAK_EDITOR_SHELL_TESTING
void break_editor_image_preview_set_shutdown_timeout_for_test(
    BreakEditorImagePreview *preview, u32 timeout_ms);
#endif
