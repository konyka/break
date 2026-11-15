#pragma once
/* Plugin manifest: the list of break_plugin libraries the editor loads at
 * startup, and a loader that opens one editor_plugin_host window per entry.
 *
 * Text format, one entry per line; blank lines and lines whose first
 * non-blank byte is '#' are ignored, a trailing '\r' is dropped:
 *
 *   plugin <build_id> <sha256 as 64 hex chars> <path to end of line>
 *
 * build_id is 1..63 bytes in 0x21..0x7e. Trailing blanks after the path are
 * dropped; the path may contain spaces but no other control bytes. A path
 * that does not start with '/', '\' or a drive letter is joined to base_dir.
 * Any bad line fails the whole parse, so a broken manifest loads nothing.
 *
 * This file never calls break_plugin_* (the editor targets do not link
 * break_system): load_all hands each entry to a caller callback, normally a
 * thin wrapper over break_plugin_load. Threading: editor shell thread. */

#include <core/types.h>

#include <editor/editor_plugin_host.h>

#define BREAK_EDITOR_PLUGIN_MANIFEST_MAX 32u
#define BREAK_EDITOR_PLUGIN_MANIFEST_BUILD_ID_CAPACITY 64u
#define BREAK_EDITOR_PLUGIN_MANIFEST_PATH_CAPACITY 1024u

typedef enum BreakEditorPluginManifestStatus {
    BREAK_EDITOR_PLUGIN_MANIFEST_OK = 0,
    BREAK_EDITOR_PLUGIN_MANIFEST_INVALID,
    BREAK_EDITOR_PLUGIN_MANIFEST_SYNTAX,
    BREAK_EDITOR_PLUGIN_MANIFEST_BAD_BUILD_ID,
    BREAK_EDITOR_PLUGIN_MANIFEST_BAD_HASH,
    BREAK_EDITOR_PLUGIN_MANIFEST_BAD_PATH,
    BREAK_EDITOR_PLUGIN_MANIFEST_DUPLICATE,
    BREAK_EDITOR_PLUGIN_MANIFEST_FULL,
    BREAK_EDITOR_PLUGIN_MANIFEST_IO,
    BREAK_EDITOR_PLUGIN_MANIFEST_TOO_LARGE
} BreakEditorPluginManifestStatus;

#define BREAK_EDITOR_PLUGIN_MANIFEST_FILE_MAX (64u * 1024u)

typedef struct BreakEditorPluginManifestEntry {
    char build_id[BREAK_EDITOR_PLUGIN_MANIFEST_BUILD_ID_CAPACITY];
    u8 sha256[32];
    char path[BREAK_EDITOR_PLUGIN_MANIFEST_PATH_CAPACITY];
} BreakEditorPluginManifestEntry;

typedef struct BreakEditorPluginManifest {
    u32 count;
    BreakEditorPluginManifestEntry entries[BREAK_EDITOR_PLUGIN_MANIFEST_MAX];
} BreakEditorPluginManifest;

/* owners[i] is the host owner key of entry i when it loaded, else 0. */
typedef struct BreakEditorPluginManifestReport {
    u32 loaded;
    u32 failed;
    u32 owners[BREAK_EDITOR_PLUGIN_MANIFEST_MAX];
} BreakEditorPluginManifestReport;

/* Returns true when the plugin loaded. Runs inside the entry's host window,
 * so commands the plugin adds belong to that entry. */
typedef bool (*BreakEditorPluginManifestLoadFn)(void *user,
                                                const BreakEditorPluginManifestEntry *entry);

/* text need not be NUL-terminated; a NUL byte inside it is a SYNTAX error.
 * base_dir may be NULL or empty (relative paths are kept as written). On
 * failure out->count is 0. *error_line (optional) gets the 1-based line of
 * the error, 0 on success or INVALID. */
BreakEditorPluginManifestStatus break_editor_plugin_manifest_parse(
    const char *text, usize size, const char *base_dir, BreakEditorPluginManifest *out,
    u32 *error_line);

/* Loads entries in order: begin_load, load_fn, end_load(result). An entry
 * whose window cannot open counts as failed without calling load_fn. False
 * only for NULL arguments. */
bool break_editor_plugin_manifest_load_all(const BreakEditorPluginManifest *manifest,
                                           BreakEditorPluginHost *host,
                                           BreakEditorPluginManifestLoadFn load_fn, void *user,
                                           BreakEditorPluginManifestReport *report);

/* Short lowercase name of a status ("ok", "syntax", ...); "unknown" for
 * values outside the enum. */
const char *break_editor_plugin_manifest_status_name(BreakEditorPluginManifestStatus status);

/* Reads and parses a manifest file. Relative entry paths are joined to the
 * directory part of `path` (kept as written when `path` has none). IO when
 * the file cannot be opened or read, TOO_LARGE above
 * BREAK_EDITOR_PLUGIN_MANIFEST_FILE_MAX bytes; otherwise as _parse. */
BreakEditorPluginManifestStatus break_editor_plugin_manifest_read_file(
    const char *path, BreakEditorPluginManifest *out, u32 *error_line);

/* Removes every "--plugin-manifest <path>" / "--plugin-manifest=<path>"
 * from argv in place and keeps the last path in *out_path (NULL when the
 * option is absent). False with a bounded message in err when an option
 * has an empty or missing value; *argc is then unchanged. */
bool break_editor_plugin_manifest_take_cli(int *argc, char **argv, const char **out_path,
                                           char *err, usize err_cap);
