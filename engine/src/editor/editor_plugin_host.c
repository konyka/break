#include <editor/editor_plugin_host.h>

#include <stdlib.h>

struct BreakEditorPluginHost {
    BreakEditorPluginApi api;
    BreakEditorPluginCmds *cmds;
    BreakEditorPluginSections *sections;
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

static BreakEditorPluginSectionStatus host_add_section(void *host_ptr, const char *id,
                                                       const char *title,
                                                       BreakEditorPluginSectionFn fn, void *user)
{
    BreakEditorPluginHost *host = (BreakEditorPluginHost *)host_ptr;
    if (!host) {
        return BREAK_EDITOR_PLUGIN_SECTION_INVALID;
    }
    /* NULL registry and loading_owner 0 are both rejected by the registry */
    return break_editor_plugin_sections_add(host->sections, host->loading_owner, id, title, fn,
                                            user);
}

static BreakEditorPluginCmdStatus host_set_command_label(void *host_ptr, const char *id,
                                                         const char *lang_tag,
                                                         const char *label)
{
    BreakEditorPluginHost *host = (BreakEditorPluginHost *)host_ptr;
    BreakEditorLang lang;
    if (!host || host->loading_owner == 0u) {
        return BREAK_EDITOR_PLUGIN_CMD_INVALID;
    }
    if (!break_editor_i18n_parse_lang(lang_tag, &lang)) {
        return BREAK_EDITOR_PLUGIN_CMD_BAD_LANG;
    }
    return break_editor_plugin_cmds_set_label(host->cmds, host->loading_owner, id, lang, label);
}

static BreakEditorPluginSectionStatus host_set_section_title(void *host_ptr, const char *id,
                                                             const char *lang_tag,
                                                             const char *title)
{
    BreakEditorPluginHost *host = (BreakEditorPluginHost *)host_ptr;
    BreakEditorLang lang;
    if (!host || host->loading_owner == 0u || !host->sections) {
        return BREAK_EDITOR_PLUGIN_SECTION_INVALID;
    }
    if (!break_editor_i18n_parse_lang(lang_tag, &lang)) {
        return BREAK_EDITOR_PLUGIN_SECTION_BAD_LANG;
    }
    return break_editor_plugin_sections_set_title(host->sections, host->loading_owner, id, lang,
                                                  title);
}

/* the language is process-wide, so the host pointer is not needed */
static const char *host_lang_tag(void *host_ptr)
{
    (void)host_ptr;
    return break_editor_i18n_lang_tag(break_editor_i18n_lang());
}

void break_editor_plugin_host_set_sections(BreakEditorPluginHost *host,
                                           BreakEditorPluginSections *sections)
{
    if (host) {
        host->sections = sections;
    }
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
    host->api.add_section = host_add_section;
    host->api.set_command_label = host_set_command_label;
    host->api.set_section_title = host_set_section_title;
    host->api.lang_tag = host_lang_tag;
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
        (void)break_editor_plugin_host_release(host, host->loading_owner);
    }
    host->loading_owner = 0u;
    return true;
}

u32 break_editor_plugin_host_release(BreakEditorPluginHost *host, u32 owner)
{
    if (!host) {
        return 0u;
    }
    return break_editor_plugin_cmds_remove_owner(host->cmds, owner) +
           break_editor_plugin_sections_remove_owner(host->sections, owner);
}
