#pragma once
/* BreakEditorDoc scene persistence — Stage 4 scene editor Phase 1 Task 2.
 *
 * break_editor_doc_save(doc, path) writes TWO files:
 *   1. `<path>` — the BSCN binary scene via scene_save_binary (entity
 *      generations + component id lists + component payloads; the format
 *      stores NO entity names — see scene_serial.h).
 *   2. `<path>.editor.json` (BREAK_EDITOR_SIDECAR_SUFFIX) — the editor
 *      sidecar carrying the entity display names:
 *        {"version":1,"entities":[{"index":u32,"generation":u32,
 *                                  "name":"..."}, ...]}
 *      Hand-rolled and bounded, matching scene_serial.c's own "freestanding
 *      from third-party JSON libraries" convention (the only other in-repo
 *      JSON is the myui echarts adapter's option parser, which is bound to
 *      the myui object system and not a reusable library). Writer escapes
 *      '"' and '\' with a backslash and bytes < 0x20 as \u00XX; everything
 *      else (including multi-byte UTF-8) passes through raw.
 *
 * Render `Scene` argument: NULL on BOTH paths. Verified tolerated:
 * scene_save_binary's scene chunks all handle NULL (emit empty payloads —
 * scene_serial.c:255-257, 275-277, 366-367) and scene_load_binary treats a
 * NULL Scene as "parse and discard" (scene_serial.c:1596-1598). The editor
 * document owns no render scene. Game-side chunks are still preserved
 * (2026-10-29; previously dropped on re-save): load keeps every chunk the
 * editor does not own (all but ENTITIES/COMPONENTS/HIERARCHY — so
 * SCENE_NODES, RESOURCES, mesh/skin geometry, skeleton, anims and unknown
 * future types) as exact bytes, and save splices them back after its own
 * ENTITIES/COMPONENTS. They describe the game's render graph, not the
 * editor's entities, so they are NOT re-indexed when entities are added or
 * removed; a later phase that edits the render graph must take ownership.
 *
 * INDEX COMPACTION across save/load: the BSCN ENTITIES chunk stores entities
 * densely in ascending-index order WITHOUT the index value, and
 * scene_load_binary re-creates entities via world_create_entity — into the
 * fresh staging world used here that yields dense ascending indices 1..n,
 * while each entity's GENERATION is restored exactly
 * (scene_serial.c:1056-1064). Therefore: when the saved document had no
 * destroyed-entity holes, BreakEditorEntityId round-trips exactly; with
 * holes, indices compact and only {dense-rank, generation} identity
 * survives. The sidecar's "index" field is that DENSE 1-BASED RANK, which
 * always equals the entity's index in the LOADED document — sidecar entries
 * are matched to loaded entities by exact {index, generation}.
 *
 * break_editor_doc_load(doc, path) — REPLACE semantics, all-or-nothing:
 * scene_load_binary does not clear the target world's entities (it
 * appends), so the load stages into a FRESH world and only swaps it into
 * the doc after the whole BSCN parses (the same swap pattern as
 * main.c:4916-4930). On ANY BSCN failure (missing file, bad magic/layout,
 * corrupt chunk, > 64 MiB — the last rejected by scene_serial's own
 * BSCN_MAX_FILE_BYTES gate, scene_file_size_ok) the document is left
 * COMPLETELY unchanged: entities, names, undo history, dirty flag. The
 * doc's registered component set (component id -> size) is re-registered
 * into the staging world before parsing, so registrations made through the
 * borrowed World* survive the swap; payloads for unregistered or
 * size-mismatched ids are skipped by scene_serial itself.
 * WORLD-SWAP HAZARD: because a successful load swaps the internal World,
 * any World* previously borrowed via break_editor_doc_world() DANGLES after
 * break_editor_doc_load returns true — callers MUST re-fetch it
 * (editor_doc.h). A failed load leaves the World untouched.
 *
 * Sidecar handling on load (NEVER fails the load):
 *   - missing / unreadable / > BREAK_EDITOR_SIDECAR_MAX_BYTES / corrupt /
 *     wrong version => ALL entities get generated `entity_<index>_
 *     <generation>` names + one LOG_WARN line.
 *   - structural corruption after a valid prefix keeps the entries already
 *     applied; the remaining entities get generated names.
 *   - a semantically bad entry (name > 127 bytes after unescape, empty name,
 *     index 0 or >= ECS_MAX_ENTITIES, generation 0, duplicate index) is
 *     skipped individually with a warning; parsing continues.
 *   - entries naming entities the BSCN does not contain (stale) are ignored.
 *   - entities with no matching entry get generated names.
 *
 * Dirty flag: save clears it on success (and never touches it on failure).
 * A successful load sets dirty = false IFF every live entity took its name
 * from the sidecar (loaded state == on-disk state); ANY generated-name
 * fallback (missing/corrupt/partial sidecar, skipped entries) sets dirty =
 * true, because the in-memory names then differ from what a re-save would
 * write. Undo/redo across load: a successful load CLEARS the command stack
 * (the recorded commands reference the pre-load world, which no longer
 * exists; undo/redo return false afterwards). A failed load keeps the
 * stack intact.
 *
 * No partial-save corruption: both files are written to `<file>.tmp` first
 * and rename(2)d into place (atomic on POSIX; on Windows rename() cannot
 * replace an existing file, so the destination is removed first —
 * best-effort, documented). The sidecar tmp is written BEFORE the BSCN tmp
 * so a sidecar-cap failure leaves neither file behind; the BSCN is committed
 * first, then the sidecar — if the sidecar commit fails after the BSCN
 * committed, save returns false (dirty stays set) and the on-disk BSCN is
 * the new scene paired with the previous/absent sidecar (next load falls
 * back to generated names for mismatched entries). A failed save never
 * truncates the previously saved files.
 *
 * Bounds: sidecar write aborts (save fails bounded, dirty unchanged) when
 * the exact byte count would exceed BREAK_EDITOR_SIDECAR_MAX_BYTES; the
 * sidecar read rejects files over the cap before allocating; the full path
 * including suffixes must fit BREAK_EDITOR_SCENE_PATH_CAPACITY bytes. Save
 * performs NO editor-owned allocation (streaming stdio); load's only
 * editor-owned allocation is the sidecar read buffer (OOM-injectable under
 * BREAK_EDITOR_TESTING; failure degrades to the generated-name fallback).
 *
 * Threading: same single-owner-thread convention as the document. */

#include <core/types.h>

#include <editor/editor_doc.h>

/* Sidecar file suffix appended to the BSCN path. */
#define BREAK_EDITOR_SIDECAR_SUFFIX ".editor.json"
/* Sidecar size cap for both write (abort) and read (fallback). */
#define BREAK_EDITOR_SIDECAR_MAX_BYTES (4u << 20) /* 4 MiB */
/* Full path byte cap including the sidecar suffix and ".tmp". */
#define BREAK_EDITOR_SCENE_PATH_CAPACITY 1024u

/* <path> BSCN + <path>.editor.json sidecar; clears dirty on success. */
bool break_editor_doc_save(BreakEditorDoc *doc, const char *path);
/* REPLACE semantics; missing/corrupt sidecar => generated names + warning.
 * A successful load swaps the internal World: borrowed
 * break_editor_doc_world() pointers DANGLE — callers must re-fetch. */
bool break_editor_doc_load(BreakEditorDoc *doc, const char *path);
/* Hot-reload entry: parse the supplied BSCN bytes (borrowed for the call)
 * instead of re-reading path. sidecar_path is still read from path at commit. */
bool break_editor_doc_load_bytes(BreakEditorDoc *doc, const char *path,
                                  const void *data, usize size);
