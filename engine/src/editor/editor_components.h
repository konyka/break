#pragma once
/* Editor component registry + inspector data model — Stage 4 scene editor
 * Phase 1 Task 3.
 *
 * The doc holds a BOUNDED registry of editable component types (cap
 * BREAK_EDITOR_COMPONENT_REGISTRY_CAPACITY = 16). Each entry names an ECS
 * component id and describes up to 9 fields ({name[32], offset, type},
 * type 0 = f32) so the inspector can enumerate and edit components without
 * knowing their concrete C types. Phase 1 registers exactly ONE type at doc
 * create: the editor's own transform:
 *
 *   EditorTransform { f32 pos[3]; f32 rot[3]; f32 scale[3]; }  (36 bytes)
 *   component id BREAK_EDITOR_COMPONENT_TRANSFORM = 64
 *
 * Id choice (documented free id): the engine demo registers ids 1..3
 * (main.c:168-170), in-repo tests use small ids (1..42); 64 is free, well
 * under the ECS component cap of 128 (ecs.h:5, World.component_sizes[128]).
 * NOTE: ids >= 64 cannot participate in ecs_query_exclude/optional masks
 * (u64 masks, ecs.h:135-137) — the editor registry never uses those query
 * builders, so the restriction does not apply here. A public registration
 * API for further editable types is deferred until a second type exists;
 * the registry cap leaves room.
 *
 * Registration into the doc's World happens at break_editor_doc_create via
 * world_register_component (ecs.h:124), which is also what makes the
 * component survive save/load: scene_serial's BSCN COMPONENTS chunk stores
 * raw bytes per registered type, and break_editor_doc_load re-registers the
 * doc's component set into the staging world before parsing
 * (editor_scene.c:477-480), so the payload round-trips byte-exact. The
 * registry itself is per-doc and rebuilt identically by every doc create,
 * so a fresh doc can inspect a freshly loaded scene immediately.
 *
 * Query semantics: every API below is registry-gated — a component id that
 * is NOT in the editor registry (even if registered in the World through
 * the borrowed World* escape hatch) yields bounded false. This is the
 * inspector's enumeration model: it only ever asks about registered
 * editable types.
 *
 * Mutation semantics (all undoable commands, all fail bounded leaving the
 * document unchanged):
 *   - set_field_f32: writes 4 bytes at the field offset through a command
 *     that stores the OLD 4 bytes; revert restores them byte-exact (NaN
 *     payloads and -0.0 survive). A bitwise-identical write is a no-op:
 *     returns true WITHOUT recording a command or setting dirty.
 *   - add_component: adds the component with all bytes ZEROED (the ECS
 *     reuses chunk rows, so world_add_component alone can return stale
 *     bytes) and snapshots the post-add bytes into the command; revert
 *     removes; redo re-adds and restores the snapshot. Adding a component
 *     the entity already has is a bounded false.
 *   - remove_component: snapshots the current component bytes into the
 *     command (<= component size, hard cap
 *     BREAK_EDITOR_COMPONENT_SNAPSHOT_CAPACITY = 256 bytes; EditorTransform
 *     is 36 bytes), then removes; revert re-adds and restores the snapshot
 *     byte-exact; redo removes again. Removing an absent component is a
 *     bounded false.
 *
 * remove_entity snapshots every registered component the entity has at
 * construction; undo restores them byte-exact with the id and name
 * (2026-10-29; previously id + name only).
 *
 * break_editor_parse_f32 — strict string->f32 for inspector edit fields.
 * Grammar (whole input must match; no leading/trailing whitespace):
 *     [+-]? ( digits ('.' digits?)? | '.' digits ) ( [eE] [+-]? digits )?
 * Rejects: NULL, empty, whitespace anywhere, missing mantissa digits,
 * exponent without digits, "inf"/"nan"/hex floats, comma separators, any
 * trailing garbage, inputs without a NUL within the first
 * BREAK_EDITOR_PARSE_F32_MAX_BYTES (64) bytes, and OVERFLOW (magnitude
 * larger than FLT_MAX after evaluation; the double-compare boundary means
 * values that would reach FLT_MAX only through f32 rounding are also
 * rejected). Underflow flushes to +/-0.0f (accepted). The conversion is
 * digit-by-digit in double with a bounded power-of-ten loop — strtod/
 * strtof are NOT used, so the parser is LOCALE-INDEPENDENT: '.' is the
 * only decimal separator regardless of the process locale. On failure
 * *out is left untouched.
 *
 * Threading: same single-owner-thread convention as the document. */

#include <core/types.h>

#include <editor/editor_doc.h>

/* Registry cap: editable component types per document. */
#define BREAK_EDITOR_COMPONENT_REGISTRY_CAPACITY 16u
/* Hard cap on the component byte snapshot stored in add/remove commands. */
#define BREAK_EDITOR_COMPONENT_SNAPSHOT_CAPACITY 256u
/* parse_f32 input scan bound (a NUL must appear within this many bytes). */
#define BREAK_EDITOR_PARSE_F32_MAX_BYTES 64u

/* Documented free ECS component id for the editor's transform (see the
 * header comment for the choice rationale). */
#define BREAK_EDITOR_COMPONENT_TRANSFORM 64u

typedef struct EditorTransform {
    f32 pos[3];
    f32 rot[3];
    f32 scale[3];
} EditorTransform; /* 36 bytes */

typedef struct BreakEditorField {
    char name[32];
    u32 offset;
    u8 type; /* 0=f32 */
} BreakEditorField;
typedef struct BreakEditorComponentInfo {
    u32 component_id;
    char display_name[32];
    /* DOCUMENTED DEVIATION from the Task 3 brief: the brief's sketch says
     * fields[8], but its own decision requires pos.x..scale.z = 9 f32 fields
     * for EditorTransform — the cap is 9 so the verbatim field set fits.
     * field_count is always <= 9. */
    BreakEditorField fields[9];
    u32 field_count;
} BreakEditorComponentInfo;

/* Number of registered editable component types (1 after doc create). */
usize break_editor_doc_component_count(const BreakEditorDoc *doc);
/* Copies the i-th registry entry; bounded false for i >= count or NULL. */
bool break_editor_doc_component_info(const BreakEditorDoc *doc, usize i,
                                     BreakEditorComponentInfo *out);

/* Registry-gated component presence query (bounded false on unregistered
 * ids, stale entities, NULL doc). */
bool break_editor_doc_has_component(const BreakEditorDoc *doc,
                                    BreakEditorEntityId id, u32 component_id);

/* Reads the 4 bytes at the field's offset as f32 (memcpy, alignment-safe).
 * Bounded false: unregistered id, field_index >= field_count, non-f32 field
 * type, entity without the component, stale id, NULL doc/out. */
bool break_editor_doc_get_field_f32(const BreakEditorDoc *doc,
                                    BreakEditorEntityId id, u32 component_id,
                                    u32 field_index, f32 *out);
/* Undoable command; revert restores the previous 4 bytes byte-exact.
 * Bitwise-identical writes are a no-op true (no command recorded). */
bool break_editor_doc_set_field_f32(BreakEditorDoc *doc,
                                    BreakEditorEntityId id, u32 component_id,
                                    u32 field_index, f32 value);

/* Undoable commands with the component bytes (<= 256) snapshotted into the
 * command. add yields zeroed bytes; remove's revert restores the snapshot
 * byte-exact. */
bool break_editor_doc_add_component(BreakEditorDoc *doc,
                                    BreakEditorEntityId id, u32 component_id);
bool break_editor_doc_remove_component(BreakEditorDoc *doc,
                                       BreakEditorEntityId id,
                                       u32 component_id);

/* Strict, locale-independent string->f32 (see header comment for the
 * grammar, the 64-byte input bound, and the overflow/underflow policy). */
bool break_editor_parse_f32(const char *text, f32 *out);
