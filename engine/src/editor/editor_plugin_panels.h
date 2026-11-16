#pragma once
/* Bounded registry of tool-window panels contributed by editor plugins. The
 * shell shows them on the "Plugins" page of the bottom tool window: one
 * title, one block of read-only text, up to
 * BREAK_EDITOR_PLUGIN_PANEL_INPUTS_MAX single-line inputs and up to
 * BREAK_EDITOR_PLUGIN_PANEL_BUTTONS_MAX buttons per panel, refreshed while
 * the page is visible.
 *
 * Each panel has a non-zero owner key (one per plugin), an id of
 * [a-z0-9_.] (1..63 bytes), a title of 1..95 bytes without control bytes
 * (plus an optional title per editor language) and a text callback. The
 * callback writes the panel text into a buffer of
 * BREAK_EDITOR_PLUGIN_PANEL_TEXT_CAPACITY bytes and returns false to hide
 * the panel. The doc is passed const: the text only reads. Button and
 * input callbacks get the doc non-const and edit it through doc commands.
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
#define BREAK_EDITOR_PLUGIN_PANEL_BUTTONS_MAX 4u
#define BREAK_EDITOR_PLUGIN_PANEL_INPUTS_MAX 2u
/* draft bytes of one input, terminator included */
#define BREAK_EDITOR_PLUGIN_PANEL_INPUT_CAPACITY 1024u

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

/* Button click: runs on the editor shell thread with the shell doc, which
 * it may edit through doc commands. false reports a failure. */
typedef bool (*BreakEditorPluginPanelButtonFn)(void *user, BreakEditorDoc *doc);

/* Input submit (Enter): runs on the editor shell thread with the shell doc
 * and the input's draft text. false reports a failure. */
typedef bool (*BreakEditorPluginPanelInputFn)(void *user, BreakEditorDoc *doc,
                                              const char *text);

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
/* Adds a button to panel `panel_id`, after its other buttons. Checks in
 * order: INVALID (NULL registry, owner 0, NULL fn), BAD_ID (button id, the
 * panel id rules), BAD_TITLE (label, the title rules), NOT_FOUND (no panel
 * `panel_id` owned by `owner`), DUPLICATE (button id already on the panel),
 * FULL (BREAK_EDITOR_PLUGIN_PANEL_BUTTONS_MAX). Any rejection changes
 * nothing. */
BreakEditorPluginPanelStatus break_editor_plugin_panels_add_button(
    BreakEditorPluginPanels *reg, u32 owner, const char *panel_id, const char *button_id,
    const char *label, BreakEditorPluginPanelButtonFn fn, void *user);
/* Label of a button in `lang`. Checks in order: INVALID (NULL registry,
 * owner 0), BAD_LANG, BAD_TITLE, NOT_FOUND (no such panel owned by `owner`,
 * or no such button on it). Any rejection changes nothing. */
BreakEditorPluginPanelStatus break_editor_plugin_panels_set_button_label(
    BreakEditorPluginPanels *reg, u32 owner, const char *panel_id, const char *button_id,
    BreakEditorLang lang, const char *label);

/* Adds a single-line input to panel `panel_id`, after its other inputs. The
 * hint is shown while the input is empty. Same checks as add_button (BAD_TITLE
 * for the hint, FULL at BREAK_EDITOR_PLUGIN_PANEL_INPUTS_MAX). Input ids are
 * unique among a panel's inputs; a button may use the same id. */
BreakEditorPluginPanelStatus break_editor_plugin_panels_add_input(
    BreakEditorPluginPanels *reg, u32 owner, const char *panel_id, const char *input_id,
    const char *hint, BreakEditorPluginPanelInputFn fn, void *user);
/* Hint of an input in `lang`; same checks as set_button_label. */
BreakEditorPluginPanelStatus break_editor_plugin_panels_set_input_hint(
    BreakEditorPluginPanels *reg, u32 owner, const char *panel_id, const char *input_id,
    BreakEditorLang lang, const char *hint);

/* Returns the number of panels removed (0 for NULL; owner 0 never has any).
 * A panel's buttons and inputs go with it. */
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

/* Buttons of panel `index` in add order; 0 / NULL for an out-of-range
 * panel or button. The label falls back to the add-time label when `lang`
 * has none or is out of range. */
u32 break_editor_plugin_panels_button_count(const BreakEditorPluginPanels *reg, u32 index);
const char *break_editor_plugin_panels_button_id(const BreakEditorPluginPanels *reg, u32 index,
                                                 u32 button);
const char *break_editor_plugin_panels_button_label(const BreakEditorPluginPanels *reg,
                                                    u32 index, u32 button,
                                                    BreakEditorLang lang);
/* Runs the button's callback with `doc` and returns its result; false
 * without a call for an out-of-range panel or button. */
bool break_editor_plugin_panels_press(const BreakEditorPluginPanels *reg, u32 index, u32 button,
                                      BreakEditorDoc *doc);

/* Inputs of panel `index` in add order; 0 / NULL for an out-of-range panel
 * or input. The hint falls back like a button label. The draft text is ""
 * until set. */
u32 break_editor_plugin_panels_input_count(const BreakEditorPluginPanels *reg, u32 index);
const char *break_editor_plugin_panels_input_id(const BreakEditorPluginPanels *reg, u32 index,
                                                u32 input);
const char *break_editor_plugin_panels_input_hint(const BreakEditorPluginPanels *reg, u32 index,
                                                  u32 input, BreakEditorLang lang);
const char *break_editor_plugin_panels_input_text(const BreakEditorPluginPanels *reg, u32 index,
                                                  u32 input);
/* Replaces the draft. False, leaving the draft unchanged, for an
 * out-of-range panel or input, NULL text, text of
 * BREAK_EDITOR_PLUGIN_PANEL_INPUT_CAPACITY bytes or more, or a control byte
 * (below 0x20, or 0x7f). "" clears it. */
bool break_editor_plugin_panels_set_input_text(BreakEditorPluginPanels *reg, u32 index,
                                               u32 input, const char *text);
/* Runs the input's callback with `doc` and the draft and returns its result;
 * false without a call for an out-of-range panel or input. */
bool break_editor_plugin_panels_submit(const BreakEditorPluginPanels *reg, u32 index, u32 input,
                                       BreakEditorDoc *doc);

/* Runs panel `index` into out (cap bytes, at least 1). The text is always
 * NUL-terminated at out[cap - 1] even when the callback overruns its
 * terminator; on false out[0] is '\0'. False without a call for an
 * out-of-range index, NULL out or cap 0. */
bool break_editor_plugin_panels_render(const BreakEditorPluginPanels *reg, u32 index,
                                       const BreakEditorDoc *doc, char *out, usize cap);
