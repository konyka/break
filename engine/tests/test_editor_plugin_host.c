#include "test_framework.h"

#include <editor/editor_plugin_host.h>

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

TEST_MAIN_BEGIN()
    RUN_TEST(plugin_host_null_handling);
    RUN_TEST(plugin_host_api_and_window_rules);
TEST_MAIN_END()
