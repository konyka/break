#pragma once
/* Bounded registry of tool-window panels contributed by editor plugins. The
 * shell shows them on the "Plugins" page of the bottom tool window: one
 * title and one block of read-only text per panel, refreshed while the page
 * is visible.
 *
 * Each panel has a non-zero owner key (one per plugin), an id of
 * [a-z0-9_.] (1..63 bytes), a title of 1..95 bytes without control bytes
 * (plus an optional title per editor language) and a text callback. The
 * callback writes the panel text into a buffer of
 * BREAK_EDITOR_PLUGIN_PANEL_TEXT_CAPACITY bytes and returns false to hide
 * the panel. The doc is passed const: a panel only reads; edits go through
 * commands.
 *
 * Panels keep registration order; remove_owner drops one plugin's panels
 * before that plugin is unloaded, keeping the order of the rest.
 *
 * Threading: owned by the editor shell thread, no locking. */

#include <core/types.h>

#include <editor/editor_doc.h>
#include <editor/editor_i18n.h>

#define BREAK_EDITOR_PLUGIN_PANELS_MAX 16u
#define BREAK_EDITOR_PLUGIN_PANEL_ID_CAPACITY 64u
#define BREAK_EDITOR_PLUGIN_PANEL_TITLE_CAPACITY 96u
#define BREAK_EDITOR_PLUGIN_PANEL_TEXT_CAPACITY 1024u
#define BREAK_EDITOR_PLUGIN_PANEL_NONE 0xffffffffu

typedef enum BreakEditorPluginPanelStatus {
    BREAK_EDITOR_PLUGIN_PANEL_OK = 0,
    BREAK_EDITOR_PLUGIN_PANEL_INVALID,
    BREAK_EDITOR_PLUGIN_PANEL_BAD_ID,
    BREAK_EDITOR_PLUGIN_PANEL_BAD_TITLE,
    BREAK_EDITOR_PLUGIN_PANEL_DUPLICATE,
    BREAK_EDITOR_PLUGIN_PANEL_FULL,
    BREAK_EDITOR_PLUGIN_PANEL_NOT_FOUND,
    BREAK_EDITOR_PLUGIN_PANEL_BAD_LANG
} BreakEditorPluginPanelStatus;

typedef bool (*BreakEditorPluginPanelFn)(void *user, const BreakEditorDoc *doc, char *out,
                                         usize cap);

typedef struct BreakEditorPluginPanels BreakEditorPluginPanels;

/* capacity 0 or above BREAK_EDITOR_PLUGIN_PANELS_MAX gives NULL. */
BreakEditorPluginPanels *break_editor_plugin_panels_create(u32 capacity);
void break_editor_plugin_panels_destroy(BreakEditorPluginPanels *reg); /* NULL no-op */

/* INVALID: NULL registry, owner 0 or NULL fn. Any rejection changes nothing. */
BreakEditorPluginPanelStatus break_editor_plugin_panels_add(BreakEditorPluginPanels *reg,
                                                            u32 owner, const char *id,
                                                            const char *title,
                                                            BreakEditorPluginPanelFn fn,
                                                            void *user);
/* Adds or replaces the title shown for panel `id` in `lang`. Checks in
 * order: INVALID (NULL registry, owner 0), BAD_LANG, BAD_TITLE, NOT_FOUND
 * (no panel `id` owned by `owner`). Any rejection changes nothing. */
BreakEditorPluginPanelStatus break_editor_plugin_panels_set_title(BreakEditorPluginPanels *reg,
                                                                  u32 owner, const char *id,
                                                                  BreakEditorLang lang,
                                                                  const char *title);
/* Returns the number of panels removed (0 for NULL; owner 0 never has any). */
u32 break_editor_plugin_panels_remove_owner(BreakEditorPluginPanels *reg, u32 owner);

u32 break_editor_plugin_panels_count(const BreakEditorPluginPanels *reg);
/* NULL / 0 for an out-of-range index. */
const char *break_editor_plugin_panels_id(const BreakEditorPluginPanels *reg, u32 index);
/* The title for `lang`, or the add-time title when `lang` has none or is out
 * of range. */
const char *break_editor_plugin_panels_title(const BreakEditorPluginPanels *reg, u32 index,
                                             BreakEditorLang lang);
u32 break_editor_plugin_panels_owner(const BreakEditorPluginPanels *reg, u32 index);
/* Exact id match; BREAK_EDITOR_PLUGIN_PANEL_NONE when absent. */
u32 break_editor_plugin_panels_find(const BreakEditorPluginPanels *reg, const char *id);

/* Runs panel `index` into out (cap bytes, at least 1). The text is always
 * NUL-terminated at out[cap - 1] even when the callback overruns its
 * terminator; on false out[0] is '\0'. False without a call for an
 * out-of-range index, NULL out or cap 0. */
bool break_editor_plugin_panels_render(const BreakEditorPluginPanels *reg, u32 index,
                                       const BreakEditorDoc *doc, char *out, usize cap);
