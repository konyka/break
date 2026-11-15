#include "test_framework.h"

#include <editor/editor_plugin_cmds.h>

#include <string.h>

typedef struct CallLog {
    u32 calls;
    void *last_doc;
    bool result;
} CallLog;

static bool record_call(void *user, BreakEditorDoc *doc)
{
    CallLog *log = (CallLog *)user;
    log->calls++;
    log->last_doc = doc;
    return log->result;
}

TEST(plugin_cmds_create_bounds)
{
    ASSERT_TRUE(break_editor_plugin_cmds_create(0u) == NULL);
    ASSERT_TRUE(break_editor_plugin_cmds_create(BREAK_EDITOR_PLUGIN_CMDS_MAX + 1u) == NULL);
    BreakEditorPluginCmds *reg = break_editor_plugin_cmds_create(BREAK_EDITOR_PLUGIN_CMDS_MAX);
    ASSERT_NOT_NULL(reg);
    ASSERT_EQ(break_editor_plugin_cmds_count(reg), 0u);
    break_editor_plugin_cmds_destroy(reg);
    break_editor_plugin_cmds_destroy(NULL);
    ASSERT_EQ(break_editor_plugin_cmds_count(NULL), 0u);
    ASSERT_TRUE(break_editor_plugin_cmds_label(NULL, 0u) == NULL);
    ASSERT_TRUE(break_editor_plugin_cmds_id(NULL, 0u) == NULL);
    ASSERT_EQ(break_editor_plugin_cmds_find(NULL, "a"), BREAK_EDITOR_PLUGIN_CMD_NONE);
    ASSERT_FALSE(break_editor_plugin_cmds_execute(NULL, 0u, NULL));
    ASSERT_EQ(break_editor_plugin_cmds_remove_owner(NULL, 1u), 0u);
    ASSERT_EQ(break_editor_plugin_cmds_add(NULL, 1u, "a", "A", record_call, NULL),
              BREAK_EDITOR_PLUGIN_CMD_INVALID);
}

TEST(plugin_cmds_add_find_execute)
{
    CallLog log_a = {0u, NULL, true};
    CallLog log_b = {0u, NULL, false};
    int fake_doc = 0;
    BreakEditorDoc *doc = (BreakEditorDoc *)(void *)&fake_doc;
    BreakEditorPluginCmds *reg = break_editor_plugin_cmds_create(4u);
    ASSERT_NOT_NULL(reg);
    ASSERT_EQ(break_editor_plugin_cmds_add(reg, 1u, "terrain.raise", "Raise Terrain",
                                           record_call, &log_a),
              BREAK_EDITOR_PLUGIN_CMD_OK);
    ASSERT_EQ(break_editor_plugin_cmds_add(reg, 2u, "lights_bake2", "Bake Lights",
                                           record_call, &log_b),
              BREAK_EDITOR_PLUGIN_CMD_OK);
    ASSERT_EQ(break_editor_plugin_cmds_count(reg), 2u);
    ASSERT_EQ(break_editor_plugin_cmds_find(reg, "lights_bake2"), 1u);
    ASSERT_EQ(break_editor_plugin_cmds_find(reg, "terrain.raise"), 0u);
    ASSERT_EQ(break_editor_plugin_cmds_find(reg, "terrain"), BREAK_EDITOR_PLUGIN_CMD_NONE);
    ASSERT_EQ(break_editor_plugin_cmds_find(reg, NULL), BREAK_EDITOR_PLUGIN_CMD_NONE);
    ASSERT_STR_EQ(break_editor_plugin_cmds_label(reg, 1u), "Bake Lights");
    ASSERT_STR_EQ(break_editor_plugin_cmds_id(reg, 0u), "terrain.raise");
    ASSERT_TRUE(break_editor_plugin_cmds_label(reg, 2u) == NULL);
    ASSERT_TRUE(break_editor_plugin_cmds_id(reg, 2u) == NULL);
    ASSERT_EQ(break_editor_plugin_cmds_owner(reg, 1u), 2u);
    ASSERT_EQ(break_editor_plugin_cmds_owner(reg, 2u), 0u);

    ASSERT_TRUE(break_editor_plugin_cmds_execute(reg, 0u, doc));
    ASSERT_EQ(log_a.calls, 1u);
    ASSERT_TRUE(log_a.last_doc == (void *)doc);
    ASSERT_FALSE(break_editor_plugin_cmds_execute(reg, 1u, NULL));
    ASSERT_EQ(log_b.calls, 1u);
    ASSERT_TRUE(log_b.last_doc == NULL);
    ASSERT_FALSE(break_editor_plugin_cmds_execute(reg, 2u, doc));
    ASSERT_EQ(log_a.calls + log_b.calls, 2u);
    break_editor_plugin_cmds_destroy(reg);
}

TEST(plugin_cmds_rejections_change_nothing)
{
    char long_id[BREAK_EDITOR_PLUGIN_CMD_ID_CAPACITY + 1u];
    char long_label[BREAK_EDITOR_PLUGIN_CMD_LABEL_CAPACITY + 1u];
    char max_id[BREAK_EDITOR_PLUGIN_CMD_ID_CAPACITY];
    char max_label[BREAK_EDITOR_PLUGIN_CMD_LABEL_CAPACITY];
    memset(long_id, 'a', sizeof(long_id) - 1u);
    long_id[sizeof(long_id) - 1u] = '\0';
    memset(long_label, 'L', sizeof(long_label) - 1u);
    long_label[sizeof(long_label) - 1u] = '\0';
    memset(max_id, 'b', sizeof(max_id) - 1u);
    max_id[sizeof(max_id) - 1u] = '\0';
    memset(max_label, 'M', sizeof(max_label) - 1u);
    max_label[sizeof(max_label) - 1u] = '\0';

    BreakEditorPluginCmds *reg = break_editor_plugin_cmds_create(2u);
    ASSERT_NOT_NULL(reg);
    ASSERT_EQ(break_editor_plugin_cmds_add(reg, 0u, "x", "X", record_call, NULL),
              BREAK_EDITOR_PLUGIN_CMD_INVALID);
    ASSERT_EQ(break_editor_plugin_cmds_add(reg, 1u, "x", "X", NULL, NULL),
              BREAK_EDITOR_PLUGIN_CMD_INVALID);
    ASSERT_EQ(break_editor_plugin_cmds_add(reg, 1u, NULL, "X", record_call, NULL),
              BREAK_EDITOR_PLUGIN_CMD_BAD_ID);
    ASSERT_EQ(break_editor_plugin_cmds_add(reg, 1u, "", "X", record_call, NULL),
              BREAK_EDITOR_PLUGIN_CMD_BAD_ID);
    ASSERT_EQ(break_editor_plugin_cmds_add(reg, 1u, "Upper", "X", record_call, NULL),
              BREAK_EDITOR_PLUGIN_CMD_BAD_ID);
    ASSERT_EQ(break_editor_plugin_cmds_add(reg, 1u, "a-b", "X", record_call, NULL),
              BREAK_EDITOR_PLUGIN_CMD_BAD_ID);
    ASSERT_EQ(break_editor_plugin_cmds_add(reg, 1u, "a b", "X", record_call, NULL),
              BREAK_EDITOR_PLUGIN_CMD_BAD_ID);
    ASSERT_EQ(break_editor_plugin_cmds_add(reg, 1u, long_id, "X", record_call, NULL),
              BREAK_EDITOR_PLUGIN_CMD_BAD_ID);
    ASSERT_EQ(break_editor_plugin_cmds_add(reg, 1u, "x", NULL, record_call, NULL),
              BREAK_EDITOR_PLUGIN_CMD_BAD_LABEL);
    ASSERT_EQ(break_editor_plugin_cmds_add(reg, 1u, "x", "", record_call, NULL),
              BREAK_EDITOR_PLUGIN_CMD_BAD_LABEL);
    ASSERT_EQ(break_editor_plugin_cmds_add(reg, 1u, "x", "A\nB", record_call, NULL),
              BREAK_EDITOR_PLUGIN_CMD_BAD_LABEL);
    ASSERT_EQ(break_editor_plugin_cmds_add(reg, 1u, "x", "A\x7f", record_call, NULL),
              BREAK_EDITOR_PLUGIN_CMD_BAD_LABEL);
    ASSERT_EQ(break_editor_plugin_cmds_add(reg, 1u, "x", long_label, record_call, NULL),
              BREAK_EDITOR_PLUGIN_CMD_BAD_LABEL);
    ASSERT_EQ(break_editor_plugin_cmds_count(reg), 0u);

    ASSERT_EQ(break_editor_plugin_cmds_add(reg, 1u, max_id, max_label, record_call, NULL),
              BREAK_EDITOR_PLUGIN_CMD_OK);
    ASSERT_STR_EQ(break_editor_plugin_cmds_label(reg, 0u), max_label);
    ASSERT_EQ(break_editor_plugin_cmds_add(reg, 2u, "z9_.", "\xe5\x9c\xb0\xe5\xbd\xa2 Z",
                                           record_call, NULL),
              BREAK_EDITOR_PLUGIN_CMD_OK);
    ASSERT_EQ(break_editor_plugin_cmds_add(reg, 3u, max_id, "Other", record_call, NULL),
              BREAK_EDITOR_PLUGIN_CMD_DUPLICATE);
    ASSERT_EQ(break_editor_plugin_cmds_add(reg, 3u, "fresh", "Other", record_call, NULL),
              BREAK_EDITOR_PLUGIN_CMD_FULL);
    ASSERT_EQ(break_editor_plugin_cmds_count(reg), 2u);
    break_editor_plugin_cmds_destroy(reg);
}

TEST(plugin_cmds_remove_owner_keeps_order)
{
    BreakEditorPluginCmds *reg = break_editor_plugin_cmds_create(8u);
    ASSERT_NOT_NULL(reg);
    ASSERT_EQ(break_editor_plugin_cmds_add(reg, 1u, "a", "A", record_call, NULL), 0);
    ASSERT_EQ(break_editor_plugin_cmds_add(reg, 2u, "b", "B", record_call, NULL), 0);
    ASSERT_EQ(break_editor_plugin_cmds_add(reg, 1u, "c", "C", record_call, NULL), 0);
    ASSERT_EQ(break_editor_plugin_cmds_add(reg, 3u, "d", "D", record_call, NULL), 0);
    ASSERT_EQ(break_editor_plugin_cmds_add(reg, 2u, "e", "E", record_call, NULL), 0);
    ASSERT_EQ(break_editor_plugin_cmds_remove_owner(reg, 0u), 0u);
    ASSERT_EQ(break_editor_plugin_cmds_remove_owner(reg, 9u), 0u);
    ASSERT_EQ(break_editor_plugin_cmds_remove_owner(reg, 2u), 2u);
    ASSERT_EQ(break_editor_plugin_cmds_count(reg), 3u);
    ASSERT_STR_EQ(break_editor_plugin_cmds_id(reg, 0u), "a");
    ASSERT_STR_EQ(break_editor_plugin_cmds_id(reg, 1u), "c");
    ASSERT_STR_EQ(break_editor_plugin_cmds_id(reg, 2u), "d");
    ASSERT_STR_EQ(break_editor_plugin_cmds_label(reg, 2u), "D");
    ASSERT_EQ(break_editor_plugin_cmds_owner(reg, 2u), 3u);
    ASSERT_EQ(break_editor_plugin_cmds_owner(reg, 3u), 0u);
    ASSERT_TRUE(break_editor_plugin_cmds_id(reg, 3u) == NULL);
    ASSERT_TRUE(break_editor_plugin_cmds_label(reg, 3u) == NULL);
    ASSERT_FALSE(break_editor_plugin_cmds_execute(reg, 3u, NULL));
    ASSERT_EQ(break_editor_plugin_cmds_find(reg, "b"), BREAK_EDITOR_PLUGIN_CMD_NONE);
    ASSERT_EQ(break_editor_plugin_cmds_add(reg, 2u, "b", "B again", record_call, NULL), 0);
    ASSERT_EQ(break_editor_plugin_cmds_find(reg, "b"), 3u);
    ASSERT_EQ(break_editor_plugin_cmds_remove_owner(reg, 1u), 2u);
    ASSERT_EQ(break_editor_plugin_cmds_remove_owner(reg, 1u), 0u);
    ASSERT_STR_EQ(break_editor_plugin_cmds_id(reg, 0u), "d");
    ASSERT_STR_EQ(break_editor_plugin_cmds_id(reg, 1u), "b");
    ASSERT_EQ(break_editor_plugin_cmds_count(reg), 2u);
    break_editor_plugin_cmds_destroy(reg);
}

TEST(plugin_cmds_filter)
{
    u32 out[4];
    BreakEditorPluginCmds *reg = break_editor_plugin_cmds_create(8u);
    ASSERT_NOT_NULL(reg);
    ASSERT_EQ(break_editor_plugin_cmds_add(reg, 1u, "terrain.raise", "Raise Terrain",
                                           record_call, NULL), 0);
    ASSERT_EQ(break_editor_plugin_cmds_add(reg, 1u, "lights.bake", "Bake Lights",
                                           record_call, NULL), 0);
    ASSERT_EQ(break_editor_plugin_cmds_add(reg, 2u, "terrain.lower", "Lower Ground",
                                           record_call, NULL), 0);
    ASSERT_EQ(break_editor_plugin_cmds_filter(reg, "TERRAIN", out, 4u), 2u);
    ASSERT_EQ(out[0], 0u);
    ASSERT_EQ(out[1], 2u);
    ASSERT_EQ(break_editor_plugin_cmds_filter(reg, "bake l", out, 4u), 1u);
    ASSERT_EQ(out[0], 1u);
    ASSERT_EQ(break_editor_plugin_cmds_filter(reg, "ground", out, 4u), 1u);
    ASSERT_EQ(out[0], 2u);
    ASSERT_EQ(break_editor_plugin_cmds_filter(reg, "", out, 4u), 3u);
    out[1] = 99u;
    ASSERT_EQ(break_editor_plugin_cmds_filter(reg, "", out, 1u), 1u);
    ASSERT_EQ(out[0], 0u);
    ASSERT_EQ(out[1], 99u);
    ASSERT_EQ(break_editor_plugin_cmds_filter(reg, "zzz", out, 4u), 0u);
    ASSERT_EQ(break_editor_plugin_cmds_filter(reg, NULL, out, 4u), 0u);
    ASSERT_EQ(break_editor_plugin_cmds_filter(reg, "a", NULL, 4u), 0u);
    ASSERT_EQ(break_editor_plugin_cmds_filter(NULL, "a", out, 4u), 0u);
    break_editor_plugin_cmds_destroy(reg);
}

TEST_MAIN_BEGIN()
    RUN_TEST(plugin_cmds_create_bounds);
    RUN_TEST(plugin_cmds_add_find_execute);
    RUN_TEST(plugin_cmds_rejections_change_nothing);
    RUN_TEST(plugin_cmds_remove_owner_keeps_order);
    RUN_TEST(plugin_cmds_filter);
TEST_MAIN_END()
