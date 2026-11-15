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

#include <editor/editor_plugin_cmds.h>

#define BREAK_EDITOR_PLUGIN_API_VERSION 1u

typedef BreakEditorPluginCmdStatus (*BreakEditorPluginAddCommandFn)(
    void *host, const char *id, const char *label, BreakEditorPluginCmdFn fn, void *user);

typedef struct BreakEditorPluginApi {
    u32 struct_size;
    u32 api_version;
    void *host;
    BreakEditorPluginAddCommandFn add_command;
} BreakEditorPluginApi;

typedef struct BreakEditorPluginHost BreakEditorPluginHost;

/* Borrows cmds, which must outlive the host. NULL cmds gives NULL. */
BreakEditorPluginHost *break_editor_plugin_host_create(BreakEditorPluginCmds *cmds);
/* Leaves the registered commands in place. NULL no-op. */
void break_editor_plugin_host_destroy(BreakEditorPluginHost *host);
const BreakEditorPluginApi *break_editor_plugin_host_api(BreakEditorPluginHost *host);
/* Fresh non-zero owner key; 0 for NULL or while a window is open. */
u32 break_editor_plugin_host_begin_load(BreakEditorPluginHost *host);
/* Closes the window; loaded == false removes the owner's commands. False
 * when no window was open. */
bool break_editor_plugin_host_end_load(BreakEditorPluginHost *host, bool loaded);
/* Removes the owner's commands and returns how many. */
u32 break_editor_plugin_host_release(BreakEditorPluginHost *host, u32 owner);
