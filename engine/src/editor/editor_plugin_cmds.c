#include <editor/editor_plugin_cmds.h>

#include <stdlib.h>
#include <string.h>

typedef struct PluginCmd {
    u32 owner;
    char id[BREAK_EDITOR_PLUGIN_CMD_ID_CAPACITY];
    char label[BREAK_EDITOR_PLUGIN_CMD_LABEL_CAPACITY];
    BreakEditorPluginCmdFn fn;
    void *user;
} PluginCmd;

struct BreakEditorPluginCmds {
    u32 capacity;
    u32 count;
    PluginCmd cmds[];
};

BreakEditorPluginCmds *break_editor_plugin_cmds_create(u32 capacity)
{
    if (capacity == 0u || capacity > BREAK_EDITOR_PLUGIN_CMDS_MAX) {
        return NULL;
    }
    BreakEditorPluginCmds *reg =
        calloc(1u, sizeof(*reg) + (usize)capacity * sizeof(PluginCmd));
    if (reg) {
        reg->capacity = capacity;
    }
    return reg;
}

void break_editor_plugin_cmds_destroy(BreakEditorPluginCmds *reg)
{
    free(reg);
}

static bool valid_id(const char *id)
{
    if (!id) {
        return false;
    }
    usize n = strlen(id);
    if (n == 0u || n >= BREAK_EDITOR_PLUGIN_CMD_ID_CAPACITY) {
        return false;
    }
    for (usize i = 0; i < n; i++) {
        char c = id[i];
        if (!((c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_' || c == '.')) {
            return false;
        }
    }
    return true;
}

static bool valid_label(const char *label)
{
    if (!label) {
        return false;
    }
    usize n = strlen(label);
    if (n == 0u || n >= BREAK_EDITOR_PLUGIN_CMD_LABEL_CAPACITY) {
        return false;
    }
    for (usize i = 0; i < n; i++) {
        unsigned char c = (unsigned char)label[i];
        if (c < 0x20u || c == 0x7fu) {
            return false;
        }
    }
    return true;
}

BreakEditorPluginCmdStatus break_editor_plugin_cmds_add(BreakEditorPluginCmds *reg, u32 owner,
                                                        const char *id, const char *label,
                                                        BreakEditorPluginCmdFn fn, void *user)
{
    if (!reg || owner == 0u || !fn) {
        return BREAK_EDITOR_PLUGIN_CMD_INVALID;
    }
    if (!valid_id(id)) {
        return BREAK_EDITOR_PLUGIN_CMD_BAD_ID;
    }
    if (!valid_label(label)) {
        return BREAK_EDITOR_PLUGIN_CMD_BAD_LABEL;
    }
    if (break_editor_plugin_cmds_find(reg, id) != BREAK_EDITOR_PLUGIN_CMD_NONE) {
        return BREAK_EDITOR_PLUGIN_CMD_DUPLICATE;
    }
    if (reg->count == reg->capacity) {
        return BREAK_EDITOR_PLUGIN_CMD_FULL;
    }
    PluginCmd *cmd = &reg->cmds[reg->count];
    cmd->owner = owner;
    memcpy(cmd->id, id, strlen(id) + 1u);
    memcpy(cmd->label, label, strlen(label) + 1u);
    cmd->fn = fn;
    cmd->user = user;
    reg->count++;
    return BREAK_EDITOR_PLUGIN_CMD_OK;
}

u32 break_editor_plugin_cmds_remove_owner(BreakEditorPluginCmds *reg, u32 owner)
{
    if (!reg) {
        return 0u;
    }
    u32 kept = 0u;
    for (u32 i = 0; i < reg->count; i++) {
        if (reg->cmds[i].owner != owner) {
            if (kept != i) {
                reg->cmds[kept] = reg->cmds[i];
            }
            kept++;
        }
    }
    u32 removed = reg->count - kept;
    reg->count = kept;
    return removed;
}

u32 break_editor_plugin_cmds_count(const BreakEditorPluginCmds *reg)
{
    return reg ? reg->count : 0u;
}

const char *break_editor_plugin_cmds_id(const BreakEditorPluginCmds *reg, u32 index)
{
    return (reg && index < reg->count) ? reg->cmds[index].id : NULL;
}

const char *break_editor_plugin_cmds_label(const BreakEditorPluginCmds *reg, u32 index)
{
    return (reg && index < reg->count) ? reg->cmds[index].label : NULL;
}

u32 break_editor_plugin_cmds_owner(const BreakEditorPluginCmds *reg, u32 index)
{
    return (reg && index < reg->count) ? reg->cmds[index].owner : 0u;
}

u32 break_editor_plugin_cmds_find(const BreakEditorPluginCmds *reg, const char *id)
{
    if (!reg || !id) {
        return BREAK_EDITOR_PLUGIN_CMD_NONE;
    }
    for (u32 i = 0; i < reg->count; i++) {
        if (strcmp(reg->cmds[i].id, id) == 0) {
            return i;
        }
    }
    return BREAK_EDITOR_PLUGIN_CMD_NONE;
}

static char fold(char c)
{
    return (c >= 'A' && c <= 'Z') ? (char)(c - 'A' + 'a') : c;
}

static bool contains_casefold(const char *haystack, const char *needle)
{
    usize n = strlen(needle);
    for (const char *p = haystack;; p++) {
        usize i = 0;
        while (i < n && fold(p[i]) == fold(needle[i])) {
            i++;
        }
        if (i == n) {
            return true;
        }
        if (*p == '\0') {
            return false;
        }
    }
}

u32 break_editor_plugin_cmds_filter(const BreakEditorPluginCmds *reg, const char *text,
                                    u32 *out, u32 cap)
{
    if (!reg || !text || !out) {
        return 0u;
    }
    u32 written = 0u;
    for (u32 i = 0; i < reg->count && written < cap; i++) {
        if (contains_casefold(reg->cmds[i].label, text) ||
            contains_casefold(reg->cmds[i].id, text)) {
            out[written++] = i;
        }
    }
    return written;
}

bool break_editor_plugin_cmds_execute(const BreakEditorPluginCmds *reg, u32 index,
                                      BreakEditorDoc *doc)
{
    if (!reg || index >= reg->count) {
        return false;
    }
    const PluginCmd *cmd = &reg->cmds[index];
    return cmd->fn(cmd->user, doc);
}
