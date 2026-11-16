#pragma once
/* Bounded registry of inspector sections contributed by editor plugins.
 * The inspector shows, for the selected entity, one read-only block per
 * section after the built-in component rows.
 *
 * Each section has a non-zero owner key (one per plugin), an id of
 * [a-z0-9_.] (1..63 bytes), a title of 1..95 bytes without control bytes,
 * and a describe callback. describe writes the section text for one entity
 * into a buffer of BREAK_EDITOR_PLUGIN_SECTION_TEXT_CAPACITY bytes and
 * returns false when the section does not apply to that entity. The doc is
 * passed const: a section only reads; edits go through commands.
 *
 * Sections keep registration order; remove_owner drops one plugin's
 * sections before that plugin is unloaded, keeping the order of the rest.
 *
 * Threading: owned by the editor shell thread, no locking. */

#include <core/types.h>

#include <editor/editor_doc.h>

#define BREAK_EDITOR_PLUGIN_SECTIONS_MAX 64u
#define BREAK_EDITOR_PLUGIN_SECTION_ID_CAPACITY 64u
#define BREAK_EDITOR_PLUGIN_SECTION_TITLE_CAPACITY 96u
#define BREAK_EDITOR_PLUGIN_SECTION_TEXT_CAPACITY 256u
#define BREAK_EDITOR_PLUGIN_SECTION_NONE 0xffffffffu

typedef enum BreakEditorPluginSectionStatus {
    BREAK_EDITOR_PLUGIN_SECTION_OK = 0,
    BREAK_EDITOR_PLUGIN_SECTION_INVALID,
    BREAK_EDITOR_PLUGIN_SECTION_BAD_ID,
    BREAK_EDITOR_PLUGIN_SECTION_BAD_TITLE,
    BREAK_EDITOR_PLUGIN_SECTION_DUPLICATE,
    BREAK_EDITOR_PLUGIN_SECTION_FULL
} BreakEditorPluginSectionStatus;

typedef bool (*BreakEditorPluginSectionFn)(void *user, const BreakEditorDoc *doc,
                                           BreakEditorEntityId entity, char *out, usize cap);

typedef struct BreakEditorPluginSections BreakEditorPluginSections;

/* capacity 0 or above BREAK_EDITOR_PLUGIN_SECTIONS_MAX gives NULL. */
BreakEditorPluginSections *break_editor_plugin_sections_create(u32 capacity);
void break_editor_plugin_sections_destroy(BreakEditorPluginSections *reg); /* NULL no-op */

/* INVALID: NULL registry, owner 0 or NULL fn. Any rejection changes nothing. */
BreakEditorPluginSectionStatus break_editor_plugin_sections_add(BreakEditorPluginSections *reg,
                                                                u32 owner, const char *id,
                                                                const char *title,
                                                                BreakEditorPluginSectionFn fn,
                                                                void *user);
/* Returns the number of sections removed (0 for NULL; owner 0 never has any). */
u32 break_editor_plugin_sections_remove_owner(BreakEditorPluginSections *reg, u32 owner);

u32 break_editor_plugin_sections_count(const BreakEditorPluginSections *reg);
/* NULL / 0 for an out-of-range index. */
const char *break_editor_plugin_sections_id(const BreakEditorPluginSections *reg, u32 index);
const char *break_editor_plugin_sections_title(const BreakEditorPluginSections *reg, u32 index);
u32 break_editor_plugin_sections_owner(const BreakEditorPluginSections *reg, u32 index);
/* Exact id match; BREAK_EDITOR_PLUGIN_SECTION_NONE when absent. */
u32 break_editor_plugin_sections_find(const BreakEditorPluginSections *reg, const char *id);

/* Runs section `index` for `entity` into out (cap bytes, at least 1). The
 * text is always NUL-terminated at out[cap - 1] even when the callback
 * overruns its terminator; on false out[0] is '\0'. False without a call for
 * an out-of-range index, NULL out or cap 0. */
bool break_editor_plugin_sections_describe(const BreakEditorPluginSections *reg, u32 index,
                                           const BreakEditorDoc *doc,
                                           BreakEditorEntityId entity, char *out, usize cap);
