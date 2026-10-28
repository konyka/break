#pragma once
/* BreakEditorAssets — Stage 4 scene editor Phase 3 Task 1 asset browser
 * model (pure CPU view model; the editor document is NOT involved — loading
 * a .bscn through the browser is Task 3's panel wiring).
 *
 * The model lists DIR-mounted filesystem trees only; VFS pak enumeration is
 * explicitly NOT in scope (plan Global Constraints). One instance = one
 * configured root directory + a current relative directory + a cached
 * one-level listing + an extension filter set. The listing is a snapshot
 * taken at create/enter/up time; set_filter re-filters the cache in memory
 * and never touches the disk.
 *
 * Bounds (plan): absolute/relative paths < BREAK_EDITOR_ASSETS_PATH_CAPACITY
 * (1024) bytes INCLUDING the NUL; at most BREAK_EDITOR_ASSETS_MAX_ENTRIES
 * (4096) entries cached per directory level (a fuller directory is
 * truncated to the first 4096 in OS enumeration order — the platform layer
 * reports the total, the model keeps the bounded prefix); entry names <
 * BREAK_EDITOR_ASSETS_NAME_CAPACITY (256) bytes including NUL; relative
 * depth <= BREAK_EDITOR_ASSETS_MAX_DEPTH (8) segments.
 *
 * Path safety: break_editor_assets_enter accepts a SINGLE relative path
 * segment — ".." (parent, clamped at the root) or the exact byte-wise name
 * of a subdirectory present in the current listing. Absolute subdirs,
 * names containing '/', ".", empty strings, unknown names, regular files,
 * symlinked directories (the listing classifies via lstat, so a symlink
 * never has is_dir set), and moves beyond the depth/path caps are all
 * rejected with false and leave the model unchanged. Escaping the root is
 * therefore impossible: the current relative path is only ever mutated by
 * appending a validated single segment or popping one.
 *
 * Sorting: directories first, then byte-wise (strcmp) name order —
 * deterministic for a fixed directory content. Names are handled
 * byte-wise; no NFC/encoding re-normalization is performed (documented
 * plan decision).
 *
 * Filter: break_editor_assets_set_filter parses a CSV of extensions
 * ("bscn,json,lua"); a file passes when its extension — the bytes after
 * the LAST '.', with no extension when that '.' is the first or last
 * character — matches a token byte-wise (case-sensitive). Directories
 * always pass (navigation must stay possible). NULL/"" disables the
 * filter. Tokens >= BREAK_EDITOR_ASSETS_EXT_CAPACITY bytes or beyond
 * BREAK_EDITOR_ASSETS_FILTER_MAX_EXTS tokens are dropped (bounded; the
 * void return cannot report it — documented).
 *
 * Allocation: create performs exactly 3 editor-owned allocations (the
 * struct, the entry cache, the visible-index array); enter/up/set_filter
 * allocate nothing. All go through break_editor_test_calloc, so the
 * BREAK_EDITOR_TESTING budget hook covers them (test_editor_assets.c
 * OOM sweep).
 *
 * Borrowed pointers: the name returned by break_editor_assets_entry_at
 * points into the entry cache and is valid until the next enter/up/destroy
 * (which re-read and re-sort the cache); set_filter only rewrites the
 * visible-index array and does NOT invalidate borrowed names. The same
 * rule covers break_editor_assets_current_rel.
 *
 * Threading: single-owner-thread convention (the editor shell thread owns
 * the model; no mutex), same as BreakEditorDoc. */

#include <core/types.h>

#define BREAK_EDITOR_ASSETS_PATH_CAPACITY 1024u
#define BREAK_EDITOR_ASSETS_MAX_ENTRIES 4096u
#define BREAK_EDITOR_ASSETS_NAME_CAPACITY 256u
#define BREAK_EDITOR_ASSETS_MAX_DEPTH 8u
#define BREAK_EDITOR_ASSETS_FILTER_MAX_EXTS 16u
#define BREAK_EDITOR_ASSETS_EXT_CAPACITY 32u

typedef struct BreakEditorAssets BreakEditorAssets;
BreakEditorAssets *break_editor_assets_create(const char *root_path);   /* root must exist + be a dir */
void break_editor_assets_destroy(BreakEditorAssets *assets);
bool break_editor_assets_enter(BreakEditorAssets *assets, const char *rel_subdir);  /* ".." allowed, clamped at root */
bool break_editor_assets_up(BreakEditorAssets *assets);
usize break_editor_assets_count(const BreakEditorAssets *assets);       /* after filter */
bool break_editor_assets_entry_at(const BreakEditorAssets *assets, usize i, const char **out_name, bool *out_is_dir); /* borrowed */
void break_editor_assets_set_filter(BreakEditorAssets *assets, const char *extensions_csv); /* e.g. "bscn,json,lua"; NULL/"" = all */
const char *break_editor_assets_current_rel(const BreakEditorAssets *assets); /* borrowed, "" = root */
bool break_editor_assets_abs_path(const BreakEditorAssets *assets, usize i, char *out, usize cap); /* bounded */
/* Re-reads the CURRENT directory (hot reload / filesystem events). Keeps the
 * filter and the relative position; allocates nothing. *out_changed (may be
 * NULL) is set when the visible listing, the current directory, or the
 * truncation flag differs from before, so a caller can skip repainting an
 * unchanged panel. If the current directory vanished the model walks up to
 * the nearest ancestor that still lists (out_changed == true, returns true);
 * if even the root cannot be listed the model becomes a coherent empty
 * listing at the root and this returns false (out_changed == true).
 * Borrowed names from entry_at are invalidated when out_changed is true. */
bool break_editor_assets_refresh(BreakEditorAssets *assets, bool *out_changed);
