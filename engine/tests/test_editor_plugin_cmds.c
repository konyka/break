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
    ASSERT_EQ(break_editor_plugin_cmds_filter(reg, "TERRAIN", BREAK_EDITOR_LANG_EN_US, out, 4u), 2u);
    ASSERT_EQ(out[0], 0u);
    ASSERT_EQ(out[1], 2u);
    ASSERT_EQ(break_editor_plugin_cmds_filter(reg, "bake l", BREAK_EDITOR_LANG_EN_US, out, 4u), 1u);
    ASSERT_EQ(out[0], 1u);
    ASSERT_EQ(break_editor_plugin_cmds_filter(reg, "ground", BREAK_EDITOR_LANG_EN_US, out, 4u), 1u);
    ASSERT_EQ(out[0], 2u);
    ASSERT_EQ(break_editor_plugin_cmds_filter(reg, "", BREAK_EDITOR_LANG_EN_US, out, 4u), 3u);
    out[1] = 99u;
    ASSERT_EQ(break_editor_plugin_cmds_filter(reg, "", BREAK_EDITOR_LANG_EN_US, out, 1u), 1u);
    ASSERT_EQ(out[0], 0u);
    ASSERT_EQ(out[1], 99u);
    ASSERT_EQ(break_editor_plugin_cmds_filter(reg, "zzz", BREAK_EDITOR_LANG_EN_US, out, 4u), 0u);
    ASSERT_EQ(break_editor_plugin_cmds_filter(reg, NULL, BREAK_EDITOR_LANG_EN_US, out, 4u), 0u);
    ASSERT_EQ(break_editor_plugin_cmds_filter(reg, "a", BREAK_EDITOR_LANG_EN_US, NULL, 4u), 0u);
    ASSERT_EQ(break_editor_plugin_cmds_filter(NULL, "a", BREAK_EDITOR_LANG_EN_US, out, 4u), 0u);
    break_editor_plugin_cmds_destroy(reg);
}

#define ZH_RAISE "\xe6\x8a\xac\xe9\xab\x98\xe5\x9c\xb0\xe5\xbd\xa2"

/* A translated label shows for its language only; other languages and an
 * out-of-range language keep the add-time label. Only the owner may
 * translate, rejections change nothing, and a slot reused after
 * remove_owner starts untranslated. */
TEST(plugin_cmds_translated_labels)
{
    char long_label[BREAK_EDITOR_PLUGIN_CMD_LABEL_CAPACITY + 1u];
    memset(long_label, 'L', sizeof(long_label) - 1u);
    long_label[sizeof(long_label) - 1u] = '\0';
    BreakEditorPluginCmds *reg = break_editor_plugin_cmds_create(4u);
    ASSERT_NOT_NULL(reg);
    ASSERT_EQ(break_editor_plugin_cmds_add(reg, 1u, "terrain.raise", "Raise Terrain",
                                           record_call, NULL), 0);
    ASSERT_EQ(break_editor_plugin_cmds_add(reg, 2u, "lights.bake", "Bake Lights",
                                           record_call, NULL), 0);
    ASSERT_STR_EQ(break_editor_plugin_cmds_label_lang(reg, 0u, BREAK_EDITOR_LANG_ZH_CN),
                  "Raise Terrain");

    ASSERT_EQ(break_editor_plugin_cmds_set_label(NULL, 1u, "terrain.raise",
                                                 BREAK_EDITOR_LANG_ZH_CN, ZH_RAISE),
              BREAK_EDITOR_PLUGIN_CMD_INVALID);
    ASSERT_EQ(break_editor_plugin_cmds_set_label(reg, 0u, "terrain.raise",
                                                 BREAK_EDITOR_LANG_ZH_CN, ZH_RAISE),
              BREAK_EDITOR_PLUGIN_CMD_INVALID);
    ASSERT_EQ(break_editor_plugin_cmds_set_label(reg, 1u, "terrain.raise",
                                                 BREAK_EDITOR_LANG_COUNT, ZH_RAISE),
              BREAK_EDITOR_PLUGIN_CMD_BAD_LANG);
    ASSERT_EQ(break_editor_plugin_cmds_set_label(reg, 1u, "terrain.raise",
                                                 (BreakEditorLang)-1, ZH_RAISE),
              BREAK_EDITOR_PLUGIN_CMD_BAD_LANG);
    ASSERT_EQ(break_editor_plugin_cmds_set_label(reg, 1u, "terrain.raise",
                                                 BREAK_EDITOR_LANG_ZH_CN, NULL),
              BREAK_EDITOR_PLUGIN_CMD_BAD_LABEL);
    ASSERT_EQ(break_editor_plugin_cmds_set_label(reg, 1u, "terrain.raise",
                                                 BREAK_EDITOR_LANG_ZH_CN, ""),
              BREAK_EDITOR_PLUGIN_CMD_BAD_LABEL);
    ASSERT_EQ(break_editor_plugin_cmds_set_label(reg, 1u, "terrain.raise",
                                                 BREAK_EDITOR_LANG_ZH_CN, "A\tB"),
              BREAK_EDITOR_PLUGIN_CMD_BAD_LABEL);
    ASSERT_EQ(break_editor_plugin_cmds_set_label(reg, 1u, "terrain.raise",
                                                 BREAK_EDITOR_LANG_ZH_CN, long_label),
              BREAK_EDITOR_PLUGIN_CMD_BAD_LABEL);
    ASSERT_EQ(break_editor_plugin_cmds_set_label(reg, 1u, "lights.bake",
                                                 BREAK_EDITOR_LANG_ZH_CN, ZH_RAISE),
              BREAK_EDITOR_PLUGIN_CMD_NOT_FOUND);
    ASSERT_EQ(break_editor_plugin_cmds_set_label(reg, 1u, "missing",
                                                 BREAK_EDITOR_LANG_ZH_CN, ZH_RAISE),
              BREAK_EDITOR_PLUGIN_CMD_NOT_FOUND);
    ASSERT_EQ(break_editor_plugin_cmds_set_label(reg, 1u, NULL,
                                                 BREAK_EDITOR_LANG_ZH_CN, ZH_RAISE),
              BREAK_EDITOR_PLUGIN_CMD_NOT_FOUND);
    ASSERT_STR_EQ(break_editor_plugin_cmds_label_lang(reg, 0u, BREAK_EDITOR_LANG_ZH_CN),
                  "Raise Terrain");
    ASSERT_STR_EQ(break_editor_plugin_cmds_label_lang(reg, 1u, BREAK_EDITOR_LANG_ZH_CN),
                  "Bake Lights");

    ASSERT_EQ(break_editor_plugin_cmds_set_label(reg, 1u, "terrain.raise",
                                                 BREAK_EDITOR_LANG_ZH_CN, "first"),
              BREAK_EDITOR_PLUGIN_CMD_OK);
    ASSERT_EQ(break_editor_plugin_cmds_set_label(reg, 1u, "terrain.raise",
                                                 BREAK_EDITOR_LANG_ZH_CN, ZH_RAISE),
              BREAK_EDITOR_PLUGIN_CMD_OK);
    ASSERT_STR_EQ(break_editor_plugin_cmds_label_lang(reg, 0u, BREAK_EDITOR_LANG_ZH_CN),
                  ZH_RAISE);
    ASSERT_STR_EQ(break_editor_plugin_cmds_label_lang(reg, 0u, BREAK_EDITOR_LANG_EN_US),
                  "Raise Terrain");
    ASSERT_STR_EQ(break_editor_plugin_cmds_label_lang(reg, 0u, BREAK_EDITOR_LANG_COUNT),
                  "Raise Terrain");
    ASSERT_STR_EQ(break_editor_plugin_cmds_label_lang(reg, 0u, (BreakEditorLang)-1),
                  "Raise Terrain");
    ASSERT_STR_EQ(break_editor_plugin_cmds_label(reg, 0u), "Raise Terrain");
    ASSERT_TRUE(break_editor_plugin_cmds_label_lang(reg, 2u, BREAK_EDITOR_LANG_ZH_CN) == NULL);
    ASSERT_TRUE(break_editor_plugin_cmds_label_lang(NULL, 0u, BREAK_EDITOR_LANG_ZH_CN) == NULL);
    /* the en-US slot can carry its own text too */
    ASSERT_EQ(break_editor_plugin_cmds_set_label(reg, 2u, "lights.bake",
                                                 BREAK_EDITOR_LANG_EN_US, "Bake All Lights"),
              BREAK_EDITOR_PLUGIN_CMD_OK);
    ASSERT_STR_EQ(break_editor_plugin_cmds_label_lang(reg, 1u, BREAK_EDITOR_LANG_EN_US),
                  "Bake All Lights");
    ASSERT_STR_EQ(break_editor_plugin_cmds_label_lang(reg, 1u, BREAK_EDITOR_LANG_ZH_CN),
                  "Bake Lights");

    /* compaction keeps translations with their command */
    ASSERT_EQ(break_editor_plugin_cmds_add(reg, 3u, "after", "After", record_call, NULL), 0);
    ASSERT_EQ(break_editor_plugin_cmds_set_label(reg, 3u, "after", BREAK_EDITOR_LANG_ZH_CN,
                                                 "zh after"),
              BREAK_EDITOR_PLUGIN_CMD_OK);
    ASSERT_EQ(break_editor_plugin_cmds_remove_owner(reg, 1u), 1u);
    ASSERT_STR_EQ(break_editor_plugin_cmds_id(reg, 1u), "after");
    ASSERT_STR_EQ(break_editor_plugin_cmds_label_lang(reg, 1u, BREAK_EDITOR_LANG_ZH_CN),
                  "zh after");
    ASSERT_STR_EQ(break_editor_plugin_cmds_label_lang(reg, 0u, BREAK_EDITOR_LANG_EN_US),
                  "Bake All Lights");

    /* a reused slot starts untranslated */
    ASSERT_EQ(break_editor_plugin_cmds_remove_owner(reg, 3u), 1u);
    ASSERT_EQ(break_editor_plugin_cmds_add(reg, 4u, "fresh", "Fresh", record_call, NULL), 0);
    ASSERT_STR_EQ(break_editor_plugin_cmds_id(reg, 1u), "fresh");
    ASSERT_STR_EQ(break_editor_plugin_cmds_label_lang(reg, 1u, BREAK_EDITOR_LANG_ZH_CN),
                  "Fresh");
    ASSERT_STR_EQ(break_editor_plugin_cmds_label_lang(reg, 1u, BREAK_EDITOR_LANG_EN_US),
                  "Fresh");
    break_editor_plugin_cmds_destroy(reg);
}

/* The filter matches the label shown in the requested language (or the id),
 * not the add-time label once a translation replaces it. */
TEST(plugin_cmds_filter_uses_the_shown_label)
{
    u32 out[4];
    BreakEditorPluginCmds *reg = break_editor_plugin_cmds_create(4u);
    ASSERT_NOT_NULL(reg);
    ASSERT_EQ(break_editor_plugin_cmds_add(reg, 1u, "terrain.raise", "Raise Terrain",
                                           record_call, NULL), 0);
    ASSERT_EQ(break_editor_plugin_cmds_add(reg, 1u, "lights.bake", "Bake Lights",
                                           record_call, NULL), 0);
    ASSERT_EQ(break_editor_plugin_cmds_set_label(reg, 1u, "terrain.raise",
                                                 BREAK_EDITOR_LANG_ZH_CN, ZH_RAISE),
              BREAK_EDITOR_PLUGIN_CMD_OK);
    ASSERT_EQ(break_editor_plugin_cmds_filter(reg, ZH_RAISE, BREAK_EDITOR_LANG_ZH_CN, out, 4u),
              1u);
    ASSERT_EQ(out[0], 0u);
    ASSERT_EQ(break_editor_plugin_cmds_filter(reg, ZH_RAISE, BREAK_EDITOR_LANG_EN_US, out, 4u),
              0u);
    ASSERT_EQ(break_editor_plugin_cmds_filter(reg, "raise t", BREAK_EDITOR_LANG_ZH_CN, out,
                                              4u),
              0u);
    ASSERT_EQ(break_editor_plugin_cmds_filter(reg, "raise t", BREAK_EDITOR_LANG_EN_US, out,
                                              4u),
              1u);
    ASSERT_EQ(break_editor_plugin_cmds_filter(reg, "terrain.r", BREAK_EDITOR_LANG_ZH_CN, out,
                                              4u),
              1u);
    ASSERT_EQ(out[0], 0u);
    /* untranslated commands match their add-time label in every language */
    ASSERT_EQ(break_editor_plugin_cmds_filter(reg, "bake l", BREAK_EDITOR_LANG_ZH_CN, out, 4u),
              1u);
    ASSERT_EQ(out[0], 1u);
    break_editor_plugin_cmds_destroy(reg);
}

TEST_MAIN_BEGIN()
    RUN_TEST(plugin_cmds_create_bounds);
    RUN_TEST(plugin_cmds_add_find_execute);
    RUN_TEST(plugin_cmds_rejections_change_nothing);
    RUN_TEST(plugin_cmds_remove_owner_keeps_order);
    RUN_TEST(plugin_cmds_filter);
    RUN_TEST(plugin_cmds_translated_labels);
    RUN_TEST(plugin_cmds_filter_uses_the_shown_label);
TEST_MAIN_END()
