#pragma once
/* Bounded registry of commands contributed by editor plugins (plugins are
 * loaded through system/break_plugin.h). The command palette lists and runs
 * these next to its built-in commands.
 *
 * Each command has a non-zero owner key (one per plugin), an id of
 * [a-z0-9_.] (1..63 bytes), a label of 1..95 bytes without control bytes,
 * and a callback. Commands keep registration order; remove_owner drops one
 * plugin's commands before that plugin is unloaded, keeping the order of the
 * rest. Indexes are positions in that order and change after remove_owner.
 *
 * Threading: owned by the editor shell thread, no locking. */

#include <core/types.h>

#include <editor/editor_doc.h>

#define BREAK_EDITOR_PLUGIN_CMDS_MAX 256u
#define BREAK_EDITOR_PLUGIN_CMD_ID_CAPACITY 64u
#define BREAK_EDITOR_PLUGIN_CMD_LABEL_CAPACITY 96u
#define BREAK_EDITOR_PLUGIN_CMD_NONE 0xffffffffu

typedef enum BreakEditorPluginCmdStatus {
    BREAK_EDITOR_PLUGIN_CMD_OK = 0,
    BREAK_EDITOR_PLUGIN_CMD_INVALID,
    BREAK_EDITOR_PLUGIN_CMD_BAD_ID,
    BREAK_EDITOR_PLUGIN_CMD_BAD_LABEL,
    BREAK_EDITOR_PLUGIN_CMD_DUPLICATE,
    BREAK_EDITOR_PLUGIN_CMD_FULL
} BreakEditorPluginCmdStatus;

/* Returns the command's own result; the palette logs a failure. */
typedef bool (*BreakEditorPluginCmdFn)(void *user, BreakEditorDoc *doc);

typedef struct BreakEditorPluginCmds BreakEditorPluginCmds;

/* capacity 0 or above BREAK_EDITOR_PLUGIN_CMDS_MAX gives NULL. */
BreakEditorPluginCmds *break_editor_plugin_cmds_create(u32 capacity);
void break_editor_plugin_cmds_destroy(BreakEditorPluginCmds *reg); /* NULL no-op */

/* INVALID: NULL registry, owner 0 or NULL fn. Any rejection changes nothing. */
BreakEditorPluginCmdStatus break_editor_plugin_cmds_add(BreakEditorPluginCmds *reg, u32 owner,
                                                        const char *id, const char *label,
                                                        BreakEditorPluginCmdFn fn, void *user);
/* Returns the number of commands removed (0 for NULL; owner 0 never has any). */
u32 break_editor_plugin_cmds_remove_owner(BreakEditorPluginCmds *reg, u32 owner);

u32 break_editor_plugin_cmds_count(const BreakEditorPluginCmds *reg);
/* NULL / 0 for an out-of-range index. */
const char *break_editor_plugin_cmds_id(const BreakEditorPluginCmds *reg, u32 index);
const char *break_editor_plugin_cmds_label(const BreakEditorPluginCmds *reg, u32 index);
u32 break_editor_plugin_cmds_owner(const BreakEditorPluginCmds *reg, u32 index);
/* Exact id match; BREAK_EDITOR_PLUGIN_CMD_NONE when absent. */
u32 break_editor_plugin_cmds_find(const BreakEditorPluginCmds *reg, const char *id);
/* Writes up to cap indexes whose label or id contains text (ASCII
 * case-insensitive; "" matches all), in order. Returns the number written. */
u32 break_editor_plugin_cmds_filter(const BreakEditorPluginCmds *reg, const char *text,
                                    u32 *out, u32 cap);
/* Runs the callback; false without a call for an out-of-range index. */
bool break_editor_plugin_cmds_execute(const BreakEditorPluginCmds *reg, u32 index,
                                      BreakEditorDoc *doc);
