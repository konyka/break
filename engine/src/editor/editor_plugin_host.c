#include <editor/editor_plugin_host.h>

#include <stdlib.h>

struct BreakEditorPluginHost {
    BreakEditorPluginApi api;
    BreakEditorPluginCmds *cmds;
    u32 next_owner;
    u32 loading_owner;
};

static BreakEditorPluginCmdStatus host_add_command(void *host_ptr, const char *id,
                                                   const char *label,
                                                   BreakEditorPluginCmdFn fn, void *user)
{
    BreakEditorPluginHost *host = (BreakEditorPluginHost *)host_ptr;
    if (!host) {
        return BREAK_EDITOR_PLUGIN_CMD_INVALID;
    }
    /* outside a load window loading_owner is 0, which the registry rejects */
    return break_editor_plugin_cmds_add(host->cmds, host->loading_owner, id, label, fn, user);
}

BreakEditorPluginHost *break_editor_plugin_host_create(BreakEditorPluginCmds *cmds)
{
    if (!cmds) {
        return NULL;
    }
    BreakEditorPluginHost *host = calloc(1u, sizeof(*host));
    if (!host) {
        return NULL;
    }
    host->api.struct_size = (u32)sizeof(BreakEditorPluginApi);
    host->api.api_version = BREAK_EDITOR_PLUGIN_API_VERSION;
    host->api.host = host;
    host->api.add_command = host_add_command;
    host->cmds = cmds;
    return host;
}

void break_editor_plugin_host_destroy(BreakEditorPluginHost *host)
{
    free(host);
}

const BreakEditorPluginApi *break_editor_plugin_host_api(BreakEditorPluginHost *host)
{
    return host ? &host->api : NULL;
}

u32 break_editor_plugin_host_begin_load(BreakEditorPluginHost *host)
{
    if (!host || host->loading_owner != 0u) {
        return 0u;
    }
    host->next_owner++;
    if (host->next_owner == 0u) {
        host->next_owner = 1u;
    }
    host->loading_owner = host->next_owner;
    return host->loading_owner;
}

bool break_editor_plugin_host_end_load(BreakEditorPluginHost *host, bool loaded)
{
    if (!host || host->loading_owner == 0u) {
        return false;
    }
    if (!loaded) {
        (void)break_editor_plugin_cmds_remove_owner(host->cmds, host->loading_owner);
    }
    host->loading_owner = 0u;
    return true;
}

u32 break_editor_plugin_host_release(BreakEditorPluginHost *host, u32 owner)
{
    return host ? break_editor_plugin_cmds_remove_owner(host->cmds, owner) : 0u;
}
