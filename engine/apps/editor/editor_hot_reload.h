#pragma once
/* BreakEditorHotReload — editor asset hot reload (design:
 * docs/design/editor_hot_reload.md). Watches the shell's current .bscn scene
 * file and applies valid external edits to the document.
 *
 * Ownership: the editor host creates and destroys the object; the shell
 * BORROWS it (break_editor_shell_set_hot_reload) and drives it once per
 * break_editor_shell_tick, the same shape as the remote session host. The
 * host detaches (destroy does it) before destroying the shell, or destroys
 * the shell first; both orders are safe.
 *
 * Data flow: the legacy FileWatcher callback (shell thread) only records
 * that the scene changed. The shell tick then asks the Runtime Core reload
 * coordinator (break_runtime_reload_request) to stage the file: a worker
 * thread reads it through a VFS mounted on the scene's directory and checks
 * the BSCN magic. The staged bytes are committed on the shell thread through
 * editor_shell_load_scene_bytes, so the document, widgets, selection and
 * gizmo are only ever touched by the shell thread.
 *
 * Rules:
 *  - an invalid, truncated or unreadable scene keeps the current document,
 *    names and undo history (FAILED_KEEP_OLD);
 *  - a document with unsaved local edits (dirty AND non-empty command
 *    history) is never overwritten; the change is reported and skipped.
 *    Dirty alone is not enough: a scene loaded without a sidecar is dirty
 *    only for its generated names. History alone is not enough either: after
 *    a save the document matches the file;
 *  - the editor's own saves are recognised by content hash and ignored;
 *  - staging that began before a local save is discarded as stale;
 *  - a scene path that does not fit the watcher/VFS bounds disables
 *    watching with a console line; nothing is truncated.
 *
 * The coordinator's pump_events/notify_file_event seam is intentionally not
 * used: requests it starts have no handle the host can poll, so their table
 * slots could never be released.
 *
 * Threading: create/set_scene/tick/note_saved/destroy are shell-thread-only.
 * Workers never see the shell, the document or any widget. */

#include <core/types.h>

#include "editor_panels.h"

typedef struct BreakEditorHotReload BreakEditorHotReload;

typedef struct BreakEditorHotReloadStats {
    bool watching;        /* a scene is being watched */
    bool busy;            /* a change is pending or a reload is in flight */
    u64 events;           /* watcher callbacks (file mtime changed) */
    u64 requests;         /* reload requests issued to the coordinator */
    u64 reloads;          /* external scenes applied to the document */
    u64 failed;           /* invalid/unreadable/failed commits (old doc kept) */
    u64 skipped_dirty;    /* skipped: the document has local edits */
    u64 skipped_same;     /* skipped: bytes equal to what we last saved/loaded */
    u64 skipped_stale;    /* skipped: staging began before a local save */
} BreakEditorHotReloadStats;

/* NULL shell => NULL. Starts no watcher until set_scene (the shell does that
 * when a scene path is configured or a scene is loaded). */
BreakEditorHotReload *break_editor_hot_reload_create(BreakEditorShell *shell);

/* NULL is a no-op. Detaches from a still-attached shell, then stops the
 * watcher and shuts the coordinator down with a bounded wait. */
void break_editor_hot_reload_destroy(BreakEditorHotReload *hr);

/* Switches the watched scene. NULL or "" stops watching. Returns false when
 * watching could not start (path too long, no file name, coordinator
 * failure); the reason is written to the shell console and the previous
 * scene is no longer watched. */
bool break_editor_hot_reload_set_scene(BreakEditorHotReload *hr,
                                       const char *scene_path);

/* Once per frame on the shell thread. Safe after the shell was destroyed
 * (no-op). */
void break_editor_hot_reload_tick(BreakEditorHotReload *hr);

/* The shell calls this after a successful save of the watched scene. */
void break_editor_hot_reload_note_saved(BreakEditorHotReload *hr);

/* false on NULL arguments. */
bool break_editor_hot_reload_stats(const BreakEditorHotReload *hr,
                                   BreakEditorHotReloadStats *out_stats);
