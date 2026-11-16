#include "test_framework.h"

#include <editor/editor_plugin_host.h>

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

TEST_MAIN_BEGIN()
    RUN_TEST(plugin_host_null_handling);
    RUN_TEST(plugin_host_api_and_window_rules);
    RUN_TEST(plugin_host_sections_follow_owner_keys);
TEST_MAIN_END()
