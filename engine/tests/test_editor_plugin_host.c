#include "test_framework.h"

#include <editor/editor_plugin_host.h>

#include <stddef.h>
#include <stdio.h>

static bool host_cmd_ok(void *user, BreakEditorDoc *doc)
{
    (void)user;
    (void)doc;
    return true;
}

TEST(plugin_host_null_handling)
{
    ASSERT_TRUE(break_editor_plugin_host_create(NULL) == NULL);
    ASSERT_TRUE(break_editor_plugin_host_api(NULL) == NULL);
    ASSERT_EQ(break_editor_plugin_host_begin_load(NULL), 0u);
    ASSERT_FALSE(break_editor_plugin_host_end_load(NULL, true));
    ASSERT_EQ(break_editor_plugin_host_release(NULL, 1u), 0u);
    break_editor_plugin_host_destroy(NULL);
}

TEST(plugin_host_api_and_window_rules)
{
    BreakEditorPluginCmds *cmds = break_editor_plugin_cmds_create(8u);
    ASSERT_NOT_NULL(cmds);
    BreakEditorPluginHost *host = break_editor_plugin_host_create(cmds);
    ASSERT_NOT_NULL(host);
    const BreakEditorPluginApi *api = break_editor_plugin_host_api(host);
    ASSERT_NOT_NULL(api);
    ASSERT_EQ(api->struct_size, (u32)sizeof(BreakEditorPluginApi));
    ASSERT_EQ(api->api_version, BREAK_EDITOR_PLUGIN_API_VERSION);
    ASSERT_TRUE(api->host == (void *)host);
    ASSERT_NOT_NULL(api->add_command);

    ASSERT_EQ(api->add_command(api->host, "early", "Early", host_cmd_ok, NULL),
              BREAK_EDITOR_PLUGIN_CMD_INVALID);
    ASSERT_EQ(api->add_command(NULL, "early", "Early", host_cmd_ok, NULL),
              BREAK_EDITOR_PLUGIN_CMD_INVALID);
    ASSERT_FALSE(break_editor_plugin_host_end_load(host, true));

    u32 first = break_editor_plugin_host_begin_load(host);
    ASSERT_TRUE(first != 0u);
    ASSERT_EQ(break_editor_plugin_host_begin_load(host), 0u);
    ASSERT_EQ(api->add_command(api->host, "a.one", "One", host_cmd_ok, NULL),
              BREAK_EDITOR_PLUGIN_CMD_OK);
    ASSERT_EQ(api->add_command(api->host, "a.two", "Two", host_cmd_ok, NULL),
              BREAK_EDITOR_PLUGIN_CMD_OK);
    ASSERT_EQ(api->add_command(api->host, "a.one", "Again", host_cmd_ok, NULL),
              BREAK_EDITOR_PLUGIN_CMD_DUPLICATE);
    ASSERT_EQ(api->add_command(NULL, "a.three", "Three", host_cmd_ok, NULL),
              BREAK_EDITOR_PLUGIN_CMD_INVALID);
    ASSERT_TRUE(break_editor_plugin_host_end_load(host, true));
    ASSERT_FALSE(break_editor_plugin_host_end_load(host, true));
    ASSERT_EQ(break_editor_plugin_cmds_count(cmds), 2u);
    ASSERT_EQ(break_editor_plugin_cmds_owner(cmds, 0u), first);
    ASSERT_EQ(break_editor_plugin_cmds_owner(cmds, 1u), first);
    ASSERT_EQ(api->add_command(api->host, "late", "Late", host_cmd_ok, NULL),
              BREAK_EDITOR_PLUGIN_CMD_INVALID);

    u32 second = break_editor_plugin_host_begin_load(host);
    ASSERT_TRUE(second != 0u);
    ASSERT_TRUE(second != first);
    ASSERT_EQ(api->add_command(api->host, "b.one", "B One", host_cmd_ok, NULL),
              BREAK_EDITOR_PLUGIN_CMD_OK);
    ASSERT_EQ(break_editor_plugin_cmds_owner(cmds, 2u), second);
    ASSERT_TRUE(break_editor_plugin_host_end_load(host, false));
    ASSERT_EQ(break_editor_plugin_cmds_count(cmds), 2u);
    ASSERT_EQ(break_editor_plugin_cmds_find(cmds, "b.one"), BREAK_EDITOR_PLUGIN_CMD_NONE);

    u32 third = break_editor_plugin_host_begin_load(host);
    ASSERT_TRUE(third != 0u && third != first && third != second);
    ASSERT_EQ(api->add_command(api->host, "c.one", "C One", host_cmd_ok, NULL),
              BREAK_EDITOR_PLUGIN_CMD_OK);
    ASSERT_TRUE(break_editor_plugin_host_end_load(host, true));

    ASSERT_EQ(break_editor_plugin_host_release(host, first), 2u);
    ASSERT_EQ(break_editor_plugin_host_release(host, first), 0u);
    ASSERT_EQ(break_editor_plugin_cmds_count(cmds), 1u);
    ASSERT_STR_EQ(break_editor_plugin_cmds_id(cmds, 0u), "c.one");
    break_editor_plugin_host_destroy(host);
    ASSERT_EQ(break_editor_plugin_cmds_count(cmds), 1u);
    break_editor_plugin_cmds_destroy(cmds);
}

static bool host_section_ok(void *user, const BreakEditorDoc *doc, BreakEditorEntityId entity,
                            char *out, usize cap)
{
    (void)user;
    (void)doc;
    (void)entity;
    (void)snprintf(out, cap, "ok");
    return true;
}

TEST(plugin_host_sections_follow_owner_keys)
{
    BreakEditorPluginCmds *cmds = break_editor_plugin_cmds_create(8u);
    BreakEditorPluginSections *sections = break_editor_plugin_sections_create(8u);
    BreakEditorPluginHost *host = break_editor_plugin_host_create(cmds);
    ASSERT_NOT_NULL(host);
    ASSERT_NOT_NULL(sections);
    const BreakEditorPluginApi *api = break_editor_plugin_host_api(host);
    ASSERT_NOT_NULL(api->add_section);

    /* no registry attached: refused even inside a window */
    ASSERT_TRUE(break_editor_plugin_host_begin_load(host) != 0u);
    ASSERT_EQ(api->add_section(api->host, "a.stats", "Stats", host_section_ok, NULL),
              BREAK_EDITOR_PLUGIN_SECTION_INVALID);
    ASSERT_TRUE(break_editor_plugin_host_end_load(host, true));

    break_editor_plugin_host_set_sections(NULL, sections);
    break_editor_plugin_host_set_sections(host, sections);
    ASSERT_EQ(api->add_section(api->host, "early", "Early", host_section_ok, NULL),
              BREAK_EDITOR_PLUGIN_SECTION_INVALID);
    ASSERT_EQ(api->add_section(NULL, "early", "Early", host_section_ok, NULL),
              BREAK_EDITOR_PLUGIN_SECTION_INVALID);

    u32 first = break_editor_plugin_host_begin_load(host);
    ASSERT_EQ(api->add_command(api->host, "a.cmd", "Cmd", host_cmd_ok, NULL),
              BREAK_EDITOR_PLUGIN_CMD_OK);
    ASSERT_EQ(api->add_section(api->host, "a.stats", "Stats", host_section_ok, NULL),
              BREAK_EDITOR_PLUGIN_SECTION_OK);
    ASSERT_EQ(api->add_section(api->host, "a.stats", "Again", host_section_ok, NULL),
              BREAK_EDITOR_PLUGIN_SECTION_DUPLICATE);
    ASSERT_TRUE(break_editor_plugin_host_end_load(host, true));
    ASSERT_EQ(break_editor_plugin_sections_owner(sections, 0u), first);

    /* a failed load drops its sections with its commands */
    ASSERT_TRUE(break_editor_plugin_host_begin_load(host) != 0u);
    ASSERT_EQ(api->add_section(api->host, "b.stats", "B", host_section_ok, NULL),
              BREAK_EDITOR_PLUGIN_SECTION_OK);
    ASSERT_TRUE(break_editor_plugin_host_end_load(host, false));
    ASSERT_EQ(break_editor_plugin_sections_count(sections), 1u);
    ASSERT_EQ(break_editor_plugin_sections_find(sections, "b.stats"),
              BREAK_EDITOR_PLUGIN_SECTION_NONE);

    ASSERT_EQ(break_editor_plugin_host_release(host, first), 2u);
    ASSERT_EQ(break_editor_plugin_sections_count(sections), 0u);
    ASSERT_EQ(break_editor_plugin_cmds_count(cmds), 0u);

    /* detached again: sections are refused, release still counts commands */
    break_editor_plugin_host_set_sections(host, NULL);
    u32 third = break_editor_plugin_host_begin_load(host);
    ASSERT_EQ(api->add_section(api->host, "c.stats", "C", host_section_ok, NULL),
              BREAK_EDITOR_PLUGIN_SECTION_INVALID);
    ASSERT_EQ(api->add_command(api->host, "c.cmd", "C", host_cmd_ok, NULL),
              BREAK_EDITOR_PLUGIN_CMD_OK);
    ASSERT_TRUE(break_editor_plugin_host_end_load(host, true));
    ASSERT_EQ(break_editor_plugin_host_release(host, third), 1u);

    break_editor_plugin_host_destroy(host);
    break_editor_plugin_sections_destroy(sections);
    break_editor_plugin_cmds_destroy(cmds);
}

#define ZH_CMD "\xe5\x91\xbd\xe4\xbb\xa4"
#define ZH_STATS "\xe7\xbb\x9f\xe8\xae\xa1"

/* Translations through the plugin API: the load-window rule comes first,
 * then the tag, then the owner; tags accept the forms parse_lang accepts.
 * lang_tag reports the current editor language at any time. */
TEST(plugin_host_translations_need_the_owner_window)
{
    BreakEditorPluginCmds *cmds = break_editor_plugin_cmds_create(8u);
    BreakEditorPluginSections *sections = break_editor_plugin_sections_create(8u);
    BreakEditorPluginHost *host = break_editor_plugin_host_create(cmds);
    ASSERT_NOT_NULL(host);
    ASSERT_NOT_NULL(sections);
    const BreakEditorPluginApi *api = break_editor_plugin_host_api(host);
    ASSERT_NOT_NULL(api->set_command_label);
    ASSERT_NOT_NULL(api->set_section_title);
    ASSERT_NOT_NULL(api->lang_tag);
    ASSERT_TRUE(api->struct_size >= (u32)(offsetof(BreakEditorPluginApi, lang_tag) +
                                          sizeof(api->lang_tag)));

    /* lang_tag works outside a window and follows the editor language */
    ASSERT_TRUE(break_editor_i18n_set_lang(BREAK_EDITOR_LANG_EN_US));
    ASSERT_STR_EQ(api->lang_tag(api->host), "en-US");
    ASSERT_TRUE(break_editor_i18n_set_lang(BREAK_EDITOR_LANG_ZH_CN));
    ASSERT_STR_EQ(api->lang_tag(api->host), "zh-CN");
    ASSERT_STR_EQ(api->lang_tag(NULL), "zh-CN");
    ASSERT_TRUE(break_editor_i18n_set_lang(BREAK_EDITOR_LANG_EN_US));

    /* no section registry: titles are refused even inside a window */
    u32 first = break_editor_plugin_host_begin_load(host);
    ASSERT_TRUE(first != 0u);
    ASSERT_EQ(api->add_command(api->host, "a.cmd", "Cmd", host_cmd_ok, NULL),
              BREAK_EDITOR_PLUGIN_CMD_OK);
    ASSERT_EQ(api->set_section_title(api->host, "a.stats", "zh-CN", ZH_STATS),
              BREAK_EDITOR_PLUGIN_SECTION_INVALID);
    /* the missing registry is reported before the tag is looked at */
    ASSERT_EQ(api->set_section_title(api->host, "a.stats", "xx", ZH_STATS),
              BREAK_EDITOR_PLUGIN_SECTION_INVALID);
    ASSERT_TRUE(break_editor_plugin_host_end_load(host, true));

    /* outside a window: INVALID even for a bad tag */
    break_editor_plugin_host_set_sections(host, sections);
    ASSERT_EQ(api->set_command_label(api->host, "a.cmd", "zh-CN", ZH_CMD),
              BREAK_EDITOR_PLUGIN_CMD_INVALID);
    ASSERT_EQ(api->set_command_label(api->host, "a.cmd", "xx", ZH_CMD),
              BREAK_EDITOR_PLUGIN_CMD_INVALID);
    ASSERT_EQ(api->set_section_title(api->host, "a.stats", "xx", ZH_STATS),
              BREAK_EDITOR_PLUGIN_SECTION_INVALID);
    ASSERT_EQ(api->set_command_label(NULL, "a.cmd", "zh-CN", ZH_CMD),
              BREAK_EDITOR_PLUGIN_CMD_INVALID);
    ASSERT_EQ(api->set_section_title(NULL, "a.stats", "zh-CN", ZH_STATS),
              BREAK_EDITOR_PLUGIN_SECTION_INVALID);

    /* a second plugin may not translate the first plugin's command */
    u32 second = break_editor_plugin_host_begin_load(host);
    ASSERT_TRUE(second != 0u && second != first);
    ASSERT_EQ(api->set_command_label(api->host, "a.cmd", "zh-CN", ZH_CMD),
              BREAK_EDITOR_PLUGIN_CMD_NOT_FOUND);
    ASSERT_EQ(api->add_command(api->host, "b.cmd", "B Cmd", host_cmd_ok, NULL),
              BREAK_EDITOR_PLUGIN_CMD_OK);
    ASSERT_EQ(api->add_section(api->host, "b.stats", "B Stats", host_section_ok, NULL),
              BREAK_EDITOR_PLUGIN_SECTION_OK);
    ASSERT_EQ(api->set_command_label(api->host, "b.cmd", NULL, ZH_CMD),
              BREAK_EDITOR_PLUGIN_CMD_BAD_LANG);
    ASSERT_EQ(api->set_command_label(api->host, "b.cmd", "fr-FR", ZH_CMD),
              BREAK_EDITOR_PLUGIN_CMD_BAD_LANG);
    ASSERT_EQ(api->set_section_title(api->host, "b.stats", "", ZH_STATS),
              BREAK_EDITOR_PLUGIN_SECTION_BAD_LANG);
    ASSERT_EQ(api->set_command_label(api->host, "b.cmd", "zh_CN.UTF-8", ZH_CMD),
              BREAK_EDITOR_PLUGIN_CMD_OK);
    ASSERT_EQ(api->set_command_label(api->host, "b.cmd", "en", "B Command"),
              BREAK_EDITOR_PLUGIN_CMD_OK);
    ASSERT_EQ(api->set_section_title(api->host, "b.stats", "zh-Hans", ZH_STATS),
              BREAK_EDITOR_PLUGIN_SECTION_OK);
    ASSERT_EQ(api->set_section_title(api->host, "b.stats", "zh-CN", ""),
              BREAK_EDITOR_PLUGIN_SECTION_BAD_TITLE);
    ASSERT_EQ(api->set_section_title(api->host, "missing", "zh-CN", ZH_STATS),
              BREAK_EDITOR_PLUGIN_SECTION_NOT_FOUND);
    ASSERT_TRUE(break_editor_plugin_host_end_load(host, true));

    u32 cmd = break_editor_plugin_cmds_find(cmds, "b.cmd");
    ASSERT_EQ(cmd, 1u);
    ASSERT_STR_EQ(break_editor_plugin_cmds_label_lang(cmds, cmd, BREAK_EDITOR_LANG_ZH_CN),
                  ZH_CMD);
    ASSERT_STR_EQ(break_editor_plugin_cmds_label_lang(cmds, cmd, BREAK_EDITOR_LANG_EN_US),
                  "B Command");
    ASSERT_STR_EQ(break_editor_plugin_cmds_label_lang(cmds, 0u, BREAK_EDITOR_LANG_ZH_CN),
                  "Cmd");
    ASSERT_STR_EQ(break_editor_plugin_sections_title_lang(sections, 0u, BREAK_EDITOR_LANG_ZH_CN),
                  ZH_STATS);
    ASSERT_STR_EQ(break_editor_plugin_sections_title_lang(sections, 0u, BREAK_EDITOR_LANG_EN_US),
                  "B Stats");

    break_editor_plugin_host_destroy(host);
    break_editor_plugin_sections_destroy(sections);
    break_editor_plugin_cmds_destroy(cmds);
}

static const BreakEditorField k_host_fields[1] = {
    {"level", 0u, BREAK_EDITOR_FIELD_F32},
};

static BreakEditorComponentDesc host_desc(u32 id, const char *name)
{
    BreakEditorComponentDesc d;
    d.component_id = id;
    d.display_name = name;
    d.size = 4u;
    d.fields = k_host_fields;
    d.field_count = 1u;
    d.default_bytes = NULL;
    return d;
}

/* add_component follows the load window and needs an attached doc; a failed
 * load drops the types it registered; release keeps them. */
TEST(plugin_host_components_follow_the_window)
{
    BreakEditorPluginCmds *cmds = break_editor_plugin_cmds_create(8u);
    BreakEditorPluginHost *host = break_editor_plugin_host_create(cmds);
    BreakEditorDoc *doc = break_editor_doc_create();
    ASSERT_NOT_NULL(host);
    ASSERT_NOT_NULL(doc);
    const BreakEditorPluginApi *api = break_editor_plugin_host_api(host);
    ASSERT_NOT_NULL(api->add_component);
    BreakEditorComponentDesc a = host_desc(80u, "Alpha");
    BreakEditorComponentDesc b = host_desc(81u, "Beta");
    BreakEditorComponentDesc c = host_desc(82u, "Gamma");

    /* no doc attached: refused inside a window */
    u32 first = break_editor_plugin_host_begin_load(host);
    ASSERT_TRUE(first != 0u);
    ASSERT_EQ(api->add_component(api->host, &a), BREAK_EDITOR_COMPONENT_REG_INVALID);
    ASSERT_TRUE(break_editor_plugin_host_end_load(host, true));

    break_editor_plugin_host_set_doc(NULL, doc);
    break_editor_plugin_host_set_doc(host, doc);
    /* outside a window */
    ASSERT_EQ(api->add_component(api->host, &a), BREAK_EDITOR_COMPONENT_REG_INVALID);
    ASSERT_EQ(api->add_component(NULL, &a), BREAK_EDITOR_COMPONENT_REG_INVALID);
    ASSERT_EQ(break_editor_doc_component_count(doc), 2u);

    u32 second = break_editor_plugin_host_begin_load(host);
    ASSERT_EQ(api->add_component(api->host, NULL), BREAK_EDITOR_COMPONENT_REG_INVALID);
    ASSERT_EQ(api->add_component(api->host, &a), BREAK_EDITOR_COMPONENT_REG_OK);
    ASSERT_EQ(api->add_component(api->host, &a), BREAK_EDITOR_COMPONENT_REG_DUPLICATE);
    /* attaching another doc inside a window is ignored */
    break_editor_plugin_host_set_doc(host, NULL);
    ASSERT_EQ(api->add_component(api->host, &b), BREAK_EDITOR_COMPONENT_REG_OK);
    ASSERT_TRUE(break_editor_plugin_host_end_load(host, true));
    ASSERT_EQ(break_editor_doc_component_count(doc), 4u);

    /* a failed load drops only its own types */
    ASSERT_TRUE(break_editor_plugin_host_begin_load(host) != 0u);
    ASSERT_EQ(api->add_component(api->host, &c), BREAK_EDITOR_COMPONENT_REG_OK);
    ASSERT_EQ(break_editor_doc_component_count(doc), 5u);
    ASSERT_TRUE(break_editor_plugin_host_end_load(host, false));
    ASSERT_EQ(break_editor_doc_component_count(doc), 4u);
    {
        BreakEditorComponentInfo info;
        ASSERT_TRUE(break_editor_doc_component_info(doc, 3u, &info));
        ASSERT_EQ(info.component_id, 81u);
    }

    /* release keeps component types (entities may use them) */
    ASSERT_EQ(break_editor_plugin_host_release(host, second), 0u);
    ASSERT_EQ(break_editor_doc_component_count(doc), 4u);

    /* detach outside a window: refused again */
    break_editor_plugin_host_set_doc(host, NULL);
    ASSERT_TRUE(break_editor_plugin_host_begin_load(host) != 0u);
    ASSERT_EQ(api->add_component(api->host, &c), BREAK_EDITOR_COMPONENT_REG_INVALID);
    ASSERT_TRUE(break_editor_plugin_host_end_load(host, false));
    ASSERT_EQ(break_editor_doc_component_count(doc), 4u);

    break_editor_plugin_host_destroy(host);
    break_editor_doc_destroy(doc);
    break_editor_plugin_cmds_destroy(cmds);
}

static bool host_panel_ok(void *user, const BreakEditorDoc *doc, char *out, usize cap)
{
    (void)user;
    (void)doc;
    (void)snprintf(out, cap, "panel");
    return true;
}

/* Panels follow the same rules as sections: a registry must be attached,
 * the load window and owner apply, a failed load and release remove them. */
TEST(plugin_host_panels_follow_owner_keys)
{
    BreakEditorPluginCmds *cmds = break_editor_plugin_cmds_create(8u);
    BreakEditorPluginPanels *panels = break_editor_plugin_panels_create(8u);
    BreakEditorPluginHost *host = break_editor_plugin_host_create(cmds);
    ASSERT_NOT_NULL(host);
    ASSERT_NOT_NULL(panels);
    const BreakEditorPluginApi *api = break_editor_plugin_host_api(host);
    ASSERT_NOT_NULL(api->add_panel);
    ASSERT_NOT_NULL(api->set_panel_title);
    ASSERT_TRUE(api->struct_size >= (u32)(offsetof(BreakEditorPluginApi, set_panel_title) +
                                          sizeof(api->set_panel_title)));

    /* no registry attached */
    ASSERT_TRUE(break_editor_plugin_host_begin_load(host) != 0u);
    ASSERT_EQ(api->add_panel(api->host, "a.report", "Report", host_panel_ok, NULL),
              BREAK_EDITOR_PLUGIN_PANEL_INVALID);
    ASSERT_EQ(api->set_panel_title(api->host, "a.report", "xx", "T"),
              BREAK_EDITOR_PLUGIN_PANEL_INVALID);
    ASSERT_TRUE(break_editor_plugin_host_end_load(host, true));

    break_editor_plugin_host_set_panels(NULL, panels);
    break_editor_plugin_host_set_panels(host, panels);
    /* outside a window */
    ASSERT_EQ(api->add_panel(api->host, "a.report", "Report", host_panel_ok, NULL),
              BREAK_EDITOR_PLUGIN_PANEL_INVALID);
    ASSERT_EQ(api->add_panel(NULL, "a.report", "Report", host_panel_ok, NULL),
              BREAK_EDITOR_PLUGIN_PANEL_INVALID);
    ASSERT_EQ(api->set_panel_title(api->host, "a.report", "xx", "T"),
              BREAK_EDITOR_PLUGIN_PANEL_INVALID);
    ASSERT_EQ(api->set_panel_title(NULL, "a.report", "zh-CN", "T"),
              BREAK_EDITOR_PLUGIN_PANEL_INVALID);

    u32 first = break_editor_plugin_host_begin_load(host);
    ASSERT_EQ(api->add_panel(api->host, "a.report", "Report", host_panel_ok, NULL),
              BREAK_EDITOR_PLUGIN_PANEL_OK);
    ASSERT_EQ(api->add_panel(api->host, "a.report", "Again", host_panel_ok, NULL),
              BREAK_EDITOR_PLUGIN_PANEL_DUPLICATE);
    ASSERT_EQ(api->set_panel_title(api->host, "a.report", NULL, "T"),
              BREAK_EDITOR_PLUGIN_PANEL_BAD_LANG);
    ASSERT_EQ(api->set_panel_title(api->host, "a.report", "fr", "T"),
              BREAK_EDITOR_PLUGIN_PANEL_BAD_LANG);
    ASSERT_EQ(api->set_panel_title(api->host, "a.report", "zh_CN.UTF-8", ZH_STATS),
              BREAK_EDITOR_PLUGIN_PANEL_OK);
    ASSERT_EQ(api->set_panel_title(api->host, "a.report", "zh-CN", ""),
              BREAK_EDITOR_PLUGIN_PANEL_BAD_TITLE);
    ASSERT_TRUE(break_editor_plugin_host_end_load(host, true));
    ASSERT_EQ(break_editor_plugin_panels_owner(panels, 0u), first);
    ASSERT_STR_EQ(break_editor_plugin_panels_title(panels, 0u, BREAK_EDITOR_LANG_ZH_CN),
                  ZH_STATS);

    /* another plugin may not retitle it; its failed load drops its panel */
    ASSERT_TRUE(break_editor_plugin_host_begin_load(host) != 0u);
    ASSERT_EQ(api->set_panel_title(api->host, "a.report", "zh-CN", "x"),
              BREAK_EDITOR_PLUGIN_PANEL_NOT_FOUND);
    ASSERT_EQ(api->add_panel(api->host, "b.report", "B", host_panel_ok, NULL),
              BREAK_EDITOR_PLUGIN_PANEL_OK);
    ASSERT_TRUE(break_editor_plugin_host_end_load(host, false));
    ASSERT_EQ(break_editor_plugin_panels_count(panels), 1u);
    ASSERT_EQ(break_editor_plugin_panels_find(panels, "b.report"),
              BREAK_EDITOR_PLUGIN_PANEL_NONE);

    /* release counts the panel with the owner's other entries */
    ASSERT_EQ(break_editor_plugin_host_release(host, first), 1u);
    ASSERT_EQ(break_editor_plugin_panels_count(panels), 0u);

    break_editor_plugin_host_destroy(host);
    break_editor_plugin_panels_destroy(panels);
    break_editor_plugin_cmds_destroy(cmds);
}

TEST_MAIN_BEGIN()
    RUN_TEST(plugin_host_null_handling);
    RUN_TEST(plugin_host_api_and_window_rules);
    RUN_TEST(plugin_host_sections_follow_owner_keys);
    RUN_TEST(plugin_host_translations_need_the_owner_window);
    RUN_TEST(plugin_host_components_follow_the_window);
    RUN_TEST(plugin_host_panels_follow_owner_keys);
TEST_MAIN_END()
