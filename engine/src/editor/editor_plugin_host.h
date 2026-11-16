#pragma once
/* Bridge between system/break_plugin.h plugins and the editor plugin command
 * registry. This file never calls break_plugin_*: the code that owns the
 * plugin manager wraps every load and unload:
 *
 *   manager = break_plugin_create(n, (void *)break_editor_plugin_host_api(host));
 *   owner = break_editor_plugin_host_begin_load(host);
 *   status = break_plugin_load(manager, ...);
 *   break_editor_plugin_host_end_load(host, status == BREAK_PLUGIN_OK);
 *   ...
 *   break_editor_plugin_host_release(host, owner);   before unload
 *   break_plugin_unload(manager, handle);
 *
 * A plugin's register_fn receives the BreakEditorPluginApi pointer, checks
 * struct_size and api_version, and calls add_command. add_command works only
 * inside a begin/end window; the commands it adds belong to that window's
 * owner key. Threading: editor shell thread only. */

#include <editor/editor_components.h>
#include <editor/editor_plugin_cmds.h>
#include <editor/editor_plugin_sections.h>

#define BREAK_EDITOR_PLUGIN_API_VERSION 1u

typedef BreakEditorPluginCmdStatus (*BreakEditorPluginAddCommandFn)(
    void *host, const char *id, const char *label, BreakEditorPluginCmdFn fn, void *user);

typedef BreakEditorPluginSectionStatus (*BreakEditorPluginAddSectionFn)(
    void *host, const char *id, const char *title, BreakEditorPluginSectionFn fn, void *user);

typedef BreakEditorPluginCmdStatus (*BreakEditorPluginSetCommandLabelFn)(
    void *host, const char *id, const char *lang_tag, const char *label);

typedef BreakEditorPluginSectionStatus (*BreakEditorPluginSetSectionTitleFn)(
    void *host, const char *id, const char *lang_tag, const char *title);

typedef const char *(*BreakEditorPluginLangTagFn)(void *host);

typedef BreakEditorComponentRegStatus (*BreakEditorPluginAddComponentFn)(
    void *host, const BreakEditorComponentDesc *desc);

/* Fields are only ever appended. A plugin checks api_version and that
 * struct_size covers the last field it uses. */
typedef struct BreakEditorPluginApi {
    u32 struct_size;
    u32 api_version;
    void *host;
    BreakEditorPluginAddCommandFn add_command;
    /* Adds a read-only inspector section (editor_plugin_sections.h). Same
     * load-window rule as add_command; INVALID when the host has no section
     * registry attached. */
    BreakEditorPluginAddSectionFn add_section;
    /* Label of one of this plugin's commands in an editor language, given as
     * a tag ("zh-CN", "zh_CN.UTF-8", "en"; see break_editor_i18n_parse_lang).
     * Same load-window rule as add_command, checked before the tag: INVALID
     * outside a window, BAD_LANG for a tag the editor does not support,
     * NOT_FOUND for an id this plugin did not add. */
    BreakEditorPluginSetCommandLabelFn set_command_label;
    /* Section title in an editor language; same rules as set_command_label,
     * and INVALID without a section registry. */
    BreakEditorPluginSetSectionTitleFn set_section_title;
    /* Current editor language tag ("en-US", "zh-CN"); never NULL, callable
     * at any time, for example inside a section callback. */
    BreakEditorPluginLangTagFn lang_tag;
    /* Registers an editable component type in the attached doc
     * (break_editor_doc_register_component). Same load-window rule as
     * add_command; INVALID without an attached doc. The registry copies the
     * name, fields and default bytes, so the type stays usable for the
     * editor session after the plugin unloads; a failed load drops the
     * types it registered. */
    BreakEditorPluginAddComponentFn add_component;
} BreakEditorPluginApi;

typedef struct BreakEditorPluginHost BreakEditorPluginHost;

/* Borrows cmds, which must outlive the host. NULL cmds gives NULL. */
BreakEditorPluginHost *break_editor_plugin_host_create(BreakEditorPluginCmds *cmds);
/* Attaches the inspector section registry (borrowed, may be NULL to detach;
 * it must outlive the host). Sections follow the same owner keys as
 * commands. NULL host is a no-op. */
void break_editor_plugin_host_set_sections(BreakEditorPluginHost *host,
                                           BreakEditorPluginSections *sections);
/* Attaches the doc that add_component registers types in (borrowed, may be
 * NULL to detach; it must outlive the host). NULL host is a no-op, and so is
 * a call while a load window is open. */
void break_editor_plugin_host_set_doc(BreakEditorPluginHost *host, BreakEditorDoc *doc);
/* Leaves the registered commands in place. NULL no-op. */
void break_editor_plugin_host_destroy(BreakEditorPluginHost *host);
const BreakEditorPluginApi *break_editor_plugin_host_api(BreakEditorPluginHost *host);
/* Fresh non-zero owner key; 0 for NULL or while a window is open. */
u32 break_editor_plugin_host_begin_load(BreakEditorPluginHost *host);
/* Closes the window; loaded == false removes the owner's commands and
 * sections and the component types registered in the window. False when no
 * window was open. */
bool break_editor_plugin_host_end_load(BreakEditorPluginHost *host, bool loaded);
/* Removes the owner's commands and sections; returns how many in total.
 * Component types stay: entities and undo history may still use them. */
u32 break_editor_plugin_host_release(BreakEditorPluginHost *host, u32 owner);
