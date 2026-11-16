#include "test_framework.h"

#include <editor/editor_plugin_panels.h>

#include <stdio.h>
#include <string.h>

typedef struct PanelLog {
    u32 calls;
    const BreakEditorDoc *last_doc;
    const char *text; /* NULL: the panel is hidden */
    bool overrun;
} PanelLog;

static bool record_panel(void *user, const BreakEditorDoc *doc, char *out, usize cap)
{
    PanelLog *log = (PanelLog *)user;
    log->calls++;
    log->last_doc = doc;
    if (log->overrun) {
        memset(out, 'x', cap);
        return true;
    }
    if (!log->text) {
        /* a declining panel may still have written text: render clears it */
        (void)snprintf(out, cap, "partial");
        return false;
    }
    (void)snprintf(out, cap, "%s", log->text);
    return true;
}

#define ZH_REPORT "\xe6\x8a\xa5\xe5\x91\x8a"

TEST(panels_create_bounds)
{
    ASSERT_TRUE(break_editor_plugin_panels_create(0u) == NULL);
    ASSERT_TRUE(break_editor_plugin_panels_create(BREAK_EDITOR_PLUGIN_PANELS_MAX + 1u) == NULL);
    BreakEditorPluginPanels *reg = break_editor_plugin_panels_create(BREAK_EDITOR_PLUGIN_PANELS_MAX);
    ASSERT_NOT_NULL(reg);
    ASSERT_EQ(break_editor_plugin_panels_count(reg), 0u);
    break_editor_plugin_panels_destroy(reg);
    break_editor_plugin_panels_destroy(NULL);
    ASSERT_EQ(break_editor_plugin_panels_count(NULL), 0u);
    ASSERT_TRUE(break_editor_plugin_panels_id(NULL, 0u) == NULL);
    ASSERT_TRUE(break_editor_plugin_panels_title(NULL, 0u, BREAK_EDITOR_LANG_EN_US) == NULL);
    ASSERT_EQ(break_editor_plugin_panels_owner(NULL, 0u), 0u);
    ASSERT_EQ(break_editor_plugin_panels_find(NULL, "a"), BREAK_EDITOR_PLUGIN_PANEL_NONE);
    ASSERT_EQ(break_editor_plugin_panels_remove_owner(NULL, 1u), 0u);
}

TEST(panels_add_validates_and_keeps_order)
{
    PanelLog log = {0u, NULL, "x", false};
    char title[BREAK_EDITOR_PLUGIN_PANEL_TITLE_CAPACITY + 1u];
    char id[BREAK_EDITOR_PLUGIN_PANEL_ID_CAPACITY + 1u];
    BreakEditorPluginPanels *reg = break_editor_plugin_panels_create(2u);
    ASSERT_NOT_NULL(reg);
    ASSERT_EQ(break_editor_plugin_panels_add(NULL, 1u, "a", "A", record_panel, &log),
              BREAK_EDITOR_PLUGIN_PANEL_INVALID);
    ASSERT_EQ(break_editor_plugin_panels_add(reg, 0u, "a", "A", record_panel, &log),
              BREAK_EDITOR_PLUGIN_PANEL_INVALID);
    ASSERT_EQ(break_editor_plugin_panels_add(reg, 1u, "a", "A", NULL, &log),
              BREAK_EDITOR_PLUGIN_PANEL_INVALID);
    ASSERT_EQ(break_editor_plugin_panels_add(reg, 1u, NULL, "A", record_panel, &log),
              BREAK_EDITOR_PLUGIN_PANEL_BAD_ID);
    ASSERT_EQ(break_editor_plugin_panels_add(reg, 1u, "", "A", record_panel, &log),
              BREAK_EDITOR_PLUGIN_PANEL_BAD_ID);
    ASSERT_EQ(break_editor_plugin_panels_add(reg, 1u, "Bad", "A", record_panel, &log),
              BREAK_EDITOR_PLUGIN_PANEL_BAD_ID);
    ASSERT_EQ(break_editor_plugin_panels_add(reg, 1u, "a-b", "A", record_panel, &log),
              BREAK_EDITOR_PLUGIN_PANEL_BAD_ID);
    memset(id, 'i', BREAK_EDITOR_PLUGIN_PANEL_ID_CAPACITY);
    id[BREAK_EDITOR_PLUGIN_PANEL_ID_CAPACITY] = '\0';
    ASSERT_EQ(break_editor_plugin_panels_add(reg, 1u, id, "A", record_panel, &log),
              BREAK_EDITOR_PLUGIN_PANEL_BAD_ID);
    ASSERT_EQ(break_editor_plugin_panels_add(reg, 1u, "a", NULL, record_panel, &log),
              BREAK_EDITOR_PLUGIN_PANEL_BAD_TITLE);
    ASSERT_EQ(break_editor_plugin_panels_add(reg, 1u, "a", "", record_panel, &log),
              BREAK_EDITOR_PLUGIN_PANEL_BAD_TITLE);
    ASSERT_EQ(break_editor_plugin_panels_add(reg, 1u, "a", "A\nB", record_panel, &log),
              BREAK_EDITOR_PLUGIN_PANEL_BAD_TITLE);
    ASSERT_EQ(break_editor_plugin_panels_add(reg, 1u, "a", "A\x7f", record_panel, &log),
              BREAK_EDITOR_PLUGIN_PANEL_BAD_TITLE);
    memset(title, 't', BREAK_EDITOR_PLUGIN_PANEL_TITLE_CAPACITY);
    title[BREAK_EDITOR_PLUGIN_PANEL_TITLE_CAPACITY] = '\0';
    ASSERT_EQ(break_editor_plugin_panels_add(reg, 1u, "a", title, record_panel, &log),
              BREAK_EDITOR_PLUGIN_PANEL_BAD_TITLE);
    ASSERT_EQ(break_editor_plugin_panels_count(reg), 0u);

    /* the longest id and title fit */
    id[BREAK_EDITOR_PLUGIN_PANEL_ID_CAPACITY - 1u] = '\0';
    title[BREAK_EDITOR_PLUGIN_PANEL_TITLE_CAPACITY - 1u] = '\0';
    ASSERT_EQ(break_editor_plugin_panels_add(reg, 1u, id, title, record_panel, &log),
              BREAK_EDITOR_PLUGIN_PANEL_OK);
    ASSERT_EQ(break_editor_plugin_panels_add(reg, 2u, "build.report", "Build " ZH_REPORT,
                                             record_panel, &log),
              BREAK_EDITOR_PLUGIN_PANEL_OK);
    ASSERT_EQ(break_editor_plugin_panels_add(reg, 3u, id, "Again", record_panel, &log),
              BREAK_EDITOR_PLUGIN_PANEL_DUPLICATE);
    ASSERT_EQ(break_editor_plugin_panels_add(reg, 3u, "fresh", "Fresh", record_panel, &log),
              BREAK_EDITOR_PLUGIN_PANEL_FULL);
    ASSERT_EQ(break_editor_plugin_panels_count(reg), 2u);
    ASSERT_STR_EQ(break_editor_plugin_panels_id(reg, 0u), id);
    ASSERT_STR_EQ(break_editor_plugin_panels_title(reg, 0u, BREAK_EDITOR_LANG_EN_US), title);
    ASSERT_STR_EQ(break_editor_plugin_panels_id(reg, 1u), "build.report");
    ASSERT_STR_EQ(break_editor_plugin_panels_title(reg, 1u, BREAK_EDITOR_LANG_ZH_CN),
                  "Build " ZH_REPORT);
    ASSERT_EQ(break_editor_plugin_panels_owner(reg, 1u), 2u);
    ASSERT_EQ(break_editor_plugin_panels_find(reg, "build.report"), 1u);
    ASSERT_EQ(break_editor_plugin_panels_find(reg, "build"), BREAK_EDITOR_PLUGIN_PANEL_NONE);
    ASSERT_EQ(break_editor_plugin_panels_find(reg, NULL), BREAK_EDITOR_PLUGIN_PANEL_NONE);
    ASSERT_TRUE(break_editor_plugin_panels_id(reg, 2u) == NULL);
    ASSERT_TRUE(break_editor_plugin_panels_title(reg, 2u, BREAK_EDITOR_LANG_EN_US) == NULL);
    ASSERT_EQ(break_editor_plugin_panels_owner(reg, 2u), 0u);
    ASSERT_EQ(log.calls, 0u);
    break_editor_plugin_panels_destroy(reg);
}

TEST(panels_remove_owner_keeps_the_rest_in_order)
{
    PanelLog log = {0u, NULL, "x", false};
    BreakEditorPluginPanels *reg = break_editor_plugin_panels_create(8u);
    ASSERT_NOT_NULL(reg);
    ASSERT_EQ(break_editor_plugin_panels_add(reg, 1u, "a", "A", record_panel, &log), 0);
    ASSERT_EQ(break_editor_plugin_panels_add(reg, 2u, "b", "B", record_panel, &log), 0);
    ASSERT_EQ(break_editor_plugin_panels_add(reg, 1u, "c", "C", record_panel, &log), 0);
    ASSERT_EQ(break_editor_plugin_panels_add(reg, 3u, "d", "D", record_panel, &log), 0);
    ASSERT_EQ(break_editor_plugin_panels_set_title(reg, 3u, "d", BREAK_EDITOR_LANG_ZH_CN, "zh d"),
              BREAK_EDITOR_PLUGIN_PANEL_OK);
    ASSERT_EQ(break_editor_plugin_panels_remove_owner(reg, 0u), 0u);
    ASSERT_EQ(break_editor_plugin_panels_remove_owner(reg, 9u), 0u);
    ASSERT_EQ(break_editor_plugin_panels_remove_owner(reg, 1u), 2u);
    ASSERT_EQ(break_editor_plugin_panels_count(reg), 2u);
    ASSERT_STR_EQ(break_editor_plugin_panels_id(reg, 0u), "b");
    ASSERT_STR_EQ(break_editor_plugin_panels_id(reg, 1u), "d");
    /* translations move with their panel */
    ASSERT_STR_EQ(break_editor_plugin_panels_title(reg, 1u, BREAK_EDITOR_LANG_ZH_CN), "zh d");
    ASSERT_EQ(break_editor_plugin_panels_owner(reg, 1u), 3u);
    ASSERT_EQ(break_editor_plugin_panels_remove_owner(reg, 1u), 0u);
    /* a slot reused after removal starts untranslated */
    ASSERT_EQ(break_editor_plugin_panels_remove_owner(reg, 3u), 1u);
    ASSERT_EQ(break_editor_plugin_panels_add(reg, 4u, "e", "E", record_panel, &log), 0);
    ASSERT_STR_EQ(break_editor_plugin_panels_id(reg, 1u), "e");
    ASSERT_STR_EQ(break_editor_plugin_panels_title(reg, 1u, BREAK_EDITOR_LANG_ZH_CN), "E");
    break_editor_plugin_panels_destroy(reg);
}

TEST(panels_translated_titles)
{
    PanelLog log = {0u, NULL, "x", false};
    char long_title[BREAK_EDITOR_PLUGIN_PANEL_TITLE_CAPACITY + 1u];
    memset(long_title, 't', sizeof(long_title) - 1u);
    long_title[sizeof(long_title) - 1u] = '\0';
    BreakEditorPluginPanels *reg = break_editor_plugin_panels_create(4u);
    ASSERT_NOT_NULL(reg);
    ASSERT_EQ(break_editor_plugin_panels_add(reg, 1u, "build.report", "Report", record_panel,
                                             &log),
              BREAK_EDITOR_PLUGIN_PANEL_OK);
    ASSERT_EQ(break_editor_plugin_panels_add(reg, 2u, "other", "Other", record_panel, &log),
              BREAK_EDITOR_PLUGIN_PANEL_OK);
    ASSERT_EQ(break_editor_plugin_panels_set_title(NULL, 1u, "build.report",
                                                   BREAK_EDITOR_LANG_ZH_CN, ZH_REPORT),
              BREAK_EDITOR_PLUGIN_PANEL_INVALID);
    ASSERT_EQ(break_editor_plugin_panels_set_title(reg, 0u, "build.report",
                                                   BREAK_EDITOR_LANG_ZH_CN, ZH_REPORT),
              BREAK_EDITOR_PLUGIN_PANEL_INVALID);
    ASSERT_EQ(break_editor_plugin_panels_set_title(reg, 1u, "build.report",
                                                   BREAK_EDITOR_LANG_COUNT, ZH_REPORT),
              BREAK_EDITOR_PLUGIN_PANEL_BAD_LANG);
    ASSERT_EQ(break_editor_plugin_panels_set_title(reg, 1u, "build.report",
                                                   (BreakEditorLang)-1, ZH_REPORT),
              BREAK_EDITOR_PLUGIN_PANEL_BAD_LANG);
    ASSERT_EQ(break_editor_plugin_panels_set_title(reg, 1u, "build.report",
                                                   BREAK_EDITOR_LANG_ZH_CN, ""),
              BREAK_EDITOR_PLUGIN_PANEL_BAD_TITLE);
    ASSERT_EQ(break_editor_plugin_panels_set_title(reg, 1u, "build.report",
                                                   BREAK_EDITOR_LANG_ZH_CN, long_title),
              BREAK_EDITOR_PLUGIN_PANEL_BAD_TITLE);
    ASSERT_EQ(break_editor_plugin_panels_set_title(reg, 1u, "build.report",
                                                   BREAK_EDITOR_LANG_ZH_CN, "A\x1f"),
              BREAK_EDITOR_PLUGIN_PANEL_BAD_TITLE);
    ASSERT_EQ(break_editor_plugin_panels_set_title(reg, 1u, "other", BREAK_EDITOR_LANG_ZH_CN,
                                                   ZH_REPORT),
              BREAK_EDITOR_PLUGIN_PANEL_NOT_FOUND);
    ASSERT_EQ(break_editor_plugin_panels_set_title(reg, 1u, "missing", BREAK_EDITOR_LANG_ZH_CN,
                                                   ZH_REPORT),
              BREAK_EDITOR_PLUGIN_PANEL_NOT_FOUND);
    ASSERT_STR_EQ(break_editor_plugin_panels_title(reg, 0u, BREAK_EDITOR_LANG_ZH_CN), "Report");

    ASSERT_EQ(break_editor_plugin_panels_set_title(reg, 1u, "build.report",
                                                   BREAK_EDITOR_LANG_ZH_CN, "first"),
              BREAK_EDITOR_PLUGIN_PANEL_OK);
    ASSERT_EQ(break_editor_plugin_panels_set_title(reg, 1u, "build.report",
                                                   BREAK_EDITOR_LANG_ZH_CN, ZH_REPORT),
              BREAK_EDITOR_PLUGIN_PANEL_OK);
    ASSERT_STR_EQ(break_editor_plugin_panels_title(reg, 0u, BREAK_EDITOR_LANG_ZH_CN), ZH_REPORT);
    ASSERT_STR_EQ(break_editor_plugin_panels_title(reg, 0u, BREAK_EDITOR_LANG_EN_US), "Report");
    ASSERT_STR_EQ(break_editor_plugin_panels_title(reg, 0u, BREAK_EDITOR_LANG_COUNT), "Report");
    ASSERT_STR_EQ(break_editor_plugin_panels_title(reg, 0u, (BreakEditorLang)-1), "Report");
    ASSERT_EQ(break_editor_plugin_panels_set_title(reg, 2u, "other", BREAK_EDITOR_LANG_EN_US,
                                                   "Other Panel"),
              BREAK_EDITOR_PLUGIN_PANEL_OK);
    ASSERT_STR_EQ(break_editor_plugin_panels_title(reg, 1u, BREAK_EDITOR_LANG_EN_US),
                  "Other Panel");
    ASSERT_STR_EQ(break_editor_plugin_panels_title(reg, 1u, BREAK_EDITOR_LANG_ZH_CN), "Other");
    ASSERT_EQ(log.calls, 0u);
    break_editor_plugin_panels_destroy(reg);
}

TEST(panels_render_bounds_and_terminates)
{
    PanelLog shown = {0u, NULL, "entities: 3", false};
    PanelLog hidden = {0u, NULL, NULL, false};
    PanelLog overrun = {0u, NULL, NULL, true};
    char out[BREAK_EDITOR_PLUGIN_PANEL_TEXT_CAPACITY];
    int fake_doc = 0;
    const BreakEditorDoc *doc = (const BreakEditorDoc *)(const void *)&fake_doc;
    BreakEditorPluginPanels *reg = break_editor_plugin_panels_create(4u);
    ASSERT_NOT_NULL(reg);
    ASSERT_EQ(break_editor_plugin_panels_add(reg, 1u, "shown", "S", record_panel, &shown), 0);
    ASSERT_EQ(break_editor_plugin_panels_add(reg, 1u, "hidden", "H", record_panel, &hidden), 0);
    ASSERT_EQ(break_editor_plugin_panels_add(reg, 1u, "overrun", "O", record_panel, &overrun),
              0);

    ASSERT_TRUE(break_editor_plugin_panels_render(reg, 0u, doc, out, sizeof(out)));
    ASSERT_STR_EQ(out, "entities: 3");
    ASSERT_EQ(shown.calls, 1u);
    ASSERT_TRUE(shown.last_doc == doc);

    memcpy(out, "stale", 6u);
    ASSERT_FALSE(break_editor_plugin_panels_render(reg, 1u, doc, out, sizeof(out)));
    ASSERT_EQ(out[0], '\0');
    ASSERT_EQ(hidden.calls, 1u);

    ASSERT_TRUE(break_editor_plugin_panels_render(reg, 2u, NULL, out, sizeof(out)));
    ASSERT_EQ(strlen(out), sizeof(out) - 1u);
    ASSERT_TRUE(overrun.last_doc == NULL);

    /* bounds: no callback */
    memcpy(out, "stale", 6u);
    ASSERT_FALSE(break_editor_plugin_panels_render(reg, 3u, doc, out, sizeof(out)));
    ASSERT_EQ(out[0], '\0');
    ASSERT_FALSE(break_editor_plugin_panels_render(NULL, 0u, doc, out, sizeof(out)));
    ASSERT_FALSE(break_editor_plugin_panels_render(reg, 0u, doc, NULL, sizeof(out)));
    ASSERT_FALSE(break_editor_plugin_panels_render(reg, 0u, doc, out, 0u));
    ASSERT_EQ(shown.calls, 1u);
    /* a one-byte buffer: the callback runs and the text is empty */
    ASSERT_TRUE(break_editor_plugin_panels_render(reg, 0u, doc, out, 1u));
    ASSERT_EQ(out[0], '\0');
    ASSERT_EQ(shown.calls, 2u);
    break_editor_plugin_panels_destroy(reg);
}

typedef struct ButtonLog {
    u32 calls;
    BreakEditorDoc *last_doc;
    bool result;
} ButtonLog;

static bool record_button(void *user, BreakEditorDoc *doc)
{
    ButtonLog *log = (ButtonLog *)user;
    log->calls++;
    log->last_doc = doc;
    return log->result;
}

#define ZH_RUN "\xe8\xbf\x90\xe8\xa1\x8c"

/* add_button checks in the documented order, keeps add order, and rejects
 * without a change. */
TEST(panels_buttons_validate_and_keep_order)
{
    PanelLog log = {0u, NULL, "x", false};
    ButtonLog a = {0u, NULL, true};
    ButtonLog b = {0u, NULL, false};
    char label[BREAK_EDITOR_PLUGIN_PANEL_TITLE_CAPACITY + 1u];
    char id[BREAK_EDITOR_PLUGIN_PANEL_ID_CAPACITY + 1u];
    BreakEditorPluginPanels *reg = break_editor_plugin_panels_create(4u);
    ASSERT_NOT_NULL(reg);
    ASSERT_EQ(break_editor_plugin_panels_add(reg, 1u, "build.report", "Report", record_panel,
                                             &log),
              BREAK_EDITOR_PLUGIN_PANEL_OK);
    ASSERT_EQ(break_editor_plugin_panels_add(reg, 2u, "other", "Other", record_panel, &log),
              BREAK_EDITOR_PLUGIN_PANEL_OK);

    ASSERT_EQ(break_editor_plugin_panels_add_button(NULL, 1u, "build.report", "run", "Run",
                                                    record_button, &a),
              BREAK_EDITOR_PLUGIN_PANEL_INVALID);
    ASSERT_EQ(break_editor_plugin_panels_add_button(reg, 0u, "build.report", "run", "Run",
                                                    record_button, &a),
              BREAK_EDITOR_PLUGIN_PANEL_INVALID);
    ASSERT_EQ(break_editor_plugin_panels_add_button(reg, 1u, "build.report", "run", "Run", NULL,
                                                    &a),
              BREAK_EDITOR_PLUGIN_PANEL_INVALID);
    /* INVALID before BAD_ID, BAD_ID before BAD_TITLE, BAD_TITLE before NOT_FOUND */
    ASSERT_EQ(break_editor_plugin_panels_add_button(reg, 0u, "missing", "Bad", "", NULL, &a),
              BREAK_EDITOR_PLUGIN_PANEL_INVALID);
    ASSERT_EQ(break_editor_plugin_panels_add_button(reg, 1u, "missing", "Bad", "", record_button,
                                                    &a),
              BREAK_EDITOR_PLUGIN_PANEL_BAD_ID);
    ASSERT_EQ(break_editor_plugin_panels_add_button(reg, 1u, "build.report", NULL, "Run",
                                                    record_button, &a),
              BREAK_EDITOR_PLUGIN_PANEL_BAD_ID);
    ASSERT_EQ(break_editor_plugin_panels_add_button(reg, 1u, "build.report", "", "Run",
                                                    record_button, &a),
              BREAK_EDITOR_PLUGIN_PANEL_BAD_ID);
    ASSERT_EQ(break_editor_plugin_panels_add_button(reg, 1u, "build.report", "a-b", "Run",
                                                    record_button, &a),
              BREAK_EDITOR_PLUGIN_PANEL_BAD_ID);
    memset(id, 'i', BREAK_EDITOR_PLUGIN_PANEL_ID_CAPACITY);
    id[BREAK_EDITOR_PLUGIN_PANEL_ID_CAPACITY] = '\0';
    ASSERT_EQ(break_editor_plugin_panels_add_button(reg, 1u, "build.report", id, "Run",
                                                    record_button, &a),
              BREAK_EDITOR_PLUGIN_PANEL_BAD_ID);
    ASSERT_EQ(break_editor_plugin_panels_add_button(reg, 1u, "missing", "run", "", record_button,
                                                    &a),
              BREAK_EDITOR_PLUGIN_PANEL_BAD_TITLE);
    ASSERT_EQ(break_editor_plugin_panels_add_button(reg, 1u, "build.report", "run", NULL,
                                                    record_button, &a),
              BREAK_EDITOR_PLUGIN_PANEL_BAD_TITLE);
    ASSERT_EQ(break_editor_plugin_panels_add_button(reg, 1u, "build.report", "run", "R\n",
                                                    record_button, &a),
              BREAK_EDITOR_PLUGIN_PANEL_BAD_TITLE);
    memset(label, 'l', BREAK_EDITOR_PLUGIN_PANEL_TITLE_CAPACITY);
    label[BREAK_EDITOR_PLUGIN_PANEL_TITLE_CAPACITY] = '\0';
    ASSERT_EQ(break_editor_plugin_panels_add_button(reg, 1u, "build.report", "run", label,
                                                    record_button, &a),
              BREAK_EDITOR_PLUGIN_PANEL_BAD_TITLE);
    ASSERT_EQ(break_editor_plugin_panels_add_button(reg, 1u, "missing", "run", "Run",
                                                    record_button, &a),
              BREAK_EDITOR_PLUGIN_PANEL_NOT_FOUND);
    ASSERT_EQ(break_editor_plugin_panels_add_button(reg, 1u, NULL, "run", "Run", record_button,
                                                    &a),
              BREAK_EDITOR_PLUGIN_PANEL_NOT_FOUND);
    /* another plugin's panel */
    ASSERT_EQ(break_editor_plugin_panels_add_button(reg, 1u, "other", "run", "Run",
                                                    record_button, &a),
              BREAK_EDITOR_PLUGIN_PANEL_NOT_FOUND);
    ASSERT_EQ(break_editor_plugin_panels_button_count(reg, 0u), 0u);
    ASSERT_EQ(break_editor_plugin_panels_button_count(reg, 1u), 0u);

    /* the longest id and label fit */
    id[BREAK_EDITOR_PLUGIN_PANEL_ID_CAPACITY - 1u] = '\0';
    label[BREAK_EDITOR_PLUGIN_PANEL_TITLE_CAPACITY - 1u] = '\0';
    ASSERT_EQ(break_editor_plugin_panels_add_button(reg, 1u, "build.report", "run", "Run",
                                                    record_button, &a),
              BREAK_EDITOR_PLUGIN_PANEL_OK);
    ASSERT_EQ(break_editor_plugin_panels_add_button(reg, 1u, "build.report", id, label,
                                                    record_button, &b),
              BREAK_EDITOR_PLUGIN_PANEL_OK);
    ASSERT_EQ(break_editor_plugin_panels_add_button(reg, 1u, "build.report", "run", "Again",
                                                    record_button, &a),
              BREAK_EDITOR_PLUGIN_PANEL_DUPLICATE);
    /* the same button id on another panel is fine */
    ASSERT_EQ(break_editor_plugin_panels_add_button(reg, 2u, "other", "run", "Run other",
                                                    record_button, &b),
              BREAK_EDITOR_PLUGIN_PANEL_OK);
    ASSERT_EQ(break_editor_plugin_panels_add_button(reg, 1u, "build.report", "c", "C",
                                                    record_button, &a),
              BREAK_EDITOR_PLUGIN_PANEL_OK);
    ASSERT_EQ(break_editor_plugin_panels_add_button(reg, 1u, "build.report", "d", "D",
                                                    record_button, &a),
              BREAK_EDITOR_PLUGIN_PANEL_OK);
    ASSERT_EQ(break_editor_plugin_panels_add_button(reg, 1u, "build.report", "e", "E",
                                                    record_button, &a),
              BREAK_EDITOR_PLUGIN_PANEL_FULL);
    /* DUPLICATE is reported before FULL */
    ASSERT_EQ(break_editor_plugin_panels_add_button(reg, 1u, "build.report", "d", "D",
                                                    record_button, &a),
              BREAK_EDITOR_PLUGIN_PANEL_DUPLICATE);

    ASSERT_EQ(break_editor_plugin_panels_button_count(reg, 0u),
              BREAK_EDITOR_PLUGIN_PANEL_BUTTONS_MAX);
    ASSERT_EQ(break_editor_plugin_panels_button_count(reg, 1u), 1u);
    ASSERT_EQ(break_editor_plugin_panels_button_count(reg, 2u), 0u);
    ASSERT_EQ(break_editor_plugin_panels_button_count(NULL, 0u), 0u);
    ASSERT_STR_EQ(break_editor_plugin_panels_button_id(reg, 0u, 0u), "run");
    ASSERT_STR_EQ(break_editor_plugin_panels_button_id(reg, 0u, 1u), id);
    ASSERT_STR_EQ(break_editor_plugin_panels_button_id(reg, 0u, 3u), "d");
    ASSERT_STR_EQ(break_editor_plugin_panels_button_label(reg, 0u, 1u, BREAK_EDITOR_LANG_EN_US),
                  label);
    ASSERT_STR_EQ(break_editor_plugin_panels_button_label(reg, 1u, 0u, BREAK_EDITOR_LANG_ZH_CN),
                  "Run other");
    ASSERT_TRUE(break_editor_plugin_panels_button_id(reg, 0u, 4u) == NULL);
    ASSERT_TRUE(break_editor_plugin_panels_button_id(reg, 2u, 0u) == NULL);
    ASSERT_TRUE(break_editor_plugin_panels_button_id(NULL, 0u, 0u) == NULL);
    ASSERT_TRUE(break_editor_plugin_panels_button_label(reg, 0u, 4u, BREAK_EDITOR_LANG_EN_US) ==
                NULL);
    ASSERT_TRUE(break_editor_plugin_panels_button_label(reg, 2u, 0u, BREAK_EDITOR_LANG_EN_US) ==
                NULL);
    ASSERT_TRUE(break_editor_plugin_panels_button_label(NULL, 0u, 0u, BREAK_EDITOR_LANG_EN_US) ==
                NULL);
    ASSERT_EQ(a.calls + b.calls, 0u);
    break_editor_plugin_panels_destroy(reg);
}

/* press runs the callback with the doc and returns its result; labels
 * follow the language; buttons leave with their panel. */
TEST(panels_buttons_press_labels_and_removal)
{
    PanelLog log = {0u, NULL, "x", false};
    ButtonLog ok = {0u, NULL, true};
    ButtonLog no = {0u, NULL, false};
    ButtonLog kept = {0u, NULL, true};
    int fake_doc = 0;
    BreakEditorDoc *doc = (BreakEditorDoc *)(void *)&fake_doc;
    char long_label[BREAK_EDITOR_PLUGIN_PANEL_TITLE_CAPACITY + 1u];
    memset(long_label, 'l', sizeof(long_label) - 1u);
    long_label[sizeof(long_label) - 1u] = '\0';
    BreakEditorPluginPanels *reg = break_editor_plugin_panels_create(4u);
    ASSERT_NOT_NULL(reg);
    ASSERT_EQ(break_editor_plugin_panels_add(reg, 1u, "a", "A", record_panel, &log), 0);
    ASSERT_EQ(break_editor_plugin_panels_add(reg, 2u, "b", "B", record_panel, &log), 0);
    ASSERT_EQ(break_editor_plugin_panels_add(reg, 1u, "c", "C", record_panel, &log), 0);
    ASSERT_EQ(break_editor_plugin_panels_add_button(reg, 1u, "a", "ok", "OK", record_button, &ok),
              0);
    ASSERT_EQ(break_editor_plugin_panels_add_button(reg, 1u, "a", "no", "No", record_button, &no),
              0);
    ASSERT_EQ(break_editor_plugin_panels_add_button(reg, 2u, "b", "keep", "Keep", record_button,
                                                    &kept),
              0);

    ASSERT_TRUE(break_editor_plugin_panels_press(reg, 0u, 0u, doc));
    ASSERT_EQ(ok.calls, 1u);
    ASSERT_TRUE(ok.last_doc == doc);
    ASSERT_FALSE(break_editor_plugin_panels_press(reg, 0u, 1u, NULL));
    ASSERT_EQ(no.calls, 1u);
    ASSERT_TRUE(no.last_doc == NULL);
    /* bounds: no callback */
    ASSERT_FALSE(break_editor_plugin_panels_press(reg, 0u, 2u, doc));
    ASSERT_FALSE(break_editor_plugin_panels_press(reg, 2u, 0u, doc));
    ASSERT_FALSE(break_editor_plugin_panels_press(reg, 3u, 0u, doc));
    ASSERT_FALSE(break_editor_plugin_panels_press(NULL, 0u, 0u, doc));
    ASSERT_EQ(ok.calls + no.calls + kept.calls, 2u);

    /* labels: rules in order, then the owner and the button */
    ASSERT_EQ(break_editor_plugin_panels_set_button_label(NULL, 1u, "a", "ok",
                                                          BREAK_EDITOR_LANG_ZH_CN, ZH_RUN),
              BREAK_EDITOR_PLUGIN_PANEL_INVALID);
    ASSERT_EQ(break_editor_plugin_panels_set_button_label(reg, 0u, "a", "ok",
                                                          BREAK_EDITOR_LANG_ZH_CN, ZH_RUN),
              BREAK_EDITOR_PLUGIN_PANEL_INVALID);
    ASSERT_EQ(break_editor_plugin_panels_set_button_label(reg, 1u, "a", "ok",
                                                          BREAK_EDITOR_LANG_COUNT, ZH_RUN),
              BREAK_EDITOR_PLUGIN_PANEL_BAD_LANG);
    ASSERT_EQ(break_editor_plugin_panels_set_button_label(reg, 1u, "a", "ok",
                                                          (BreakEditorLang)-1, ZH_RUN),
              BREAK_EDITOR_PLUGIN_PANEL_BAD_LANG);
    ASSERT_EQ(break_editor_plugin_panels_set_button_label(reg, 1u, "missing", "ok",
                                                          BREAK_EDITOR_LANG_COUNT, ""),
              BREAK_EDITOR_PLUGIN_PANEL_BAD_LANG);
    ASSERT_EQ(break_editor_plugin_panels_set_button_label(reg, 1u, "missing", "ok",
                                                          BREAK_EDITOR_LANG_ZH_CN, ""),
              BREAK_EDITOR_PLUGIN_PANEL_BAD_TITLE);
    ASSERT_EQ(break_editor_plugin_panels_set_button_label(reg, 1u, "a", "ok",
                                                          BREAK_EDITOR_LANG_ZH_CN, long_label),
              BREAK_EDITOR_PLUGIN_PANEL_BAD_TITLE);
    ASSERT_EQ(break_editor_plugin_panels_set_button_label(reg, 1u, "a", "ok",
                                                          BREAK_EDITOR_LANG_ZH_CN, "x\x1f"),
              BREAK_EDITOR_PLUGIN_PANEL_BAD_TITLE);
    ASSERT_EQ(break_editor_plugin_panels_set_button_label(reg, 1u, "b", "keep",
                                                          BREAK_EDITOR_LANG_ZH_CN, ZH_RUN),
              BREAK_EDITOR_PLUGIN_PANEL_NOT_FOUND);
    ASSERT_EQ(break_editor_plugin_panels_set_button_label(reg, 1u, "a", "missing",
                                                          BREAK_EDITOR_LANG_ZH_CN, ZH_RUN),
              BREAK_EDITOR_PLUGIN_PANEL_NOT_FOUND);
    ASSERT_EQ(break_editor_plugin_panels_set_button_label(reg, 1u, "a", NULL,
                                                          BREAK_EDITOR_LANG_ZH_CN, ZH_RUN),
              BREAK_EDITOR_PLUGIN_PANEL_NOT_FOUND);
    ASSERT_EQ(break_editor_plugin_panels_set_button_label(reg, 1u, "c", "ok",
                                                          BREAK_EDITOR_LANG_ZH_CN, ZH_RUN),
              BREAK_EDITOR_PLUGIN_PANEL_NOT_FOUND);
    ASSERT_STR_EQ(break_editor_plugin_panels_button_label(reg, 0u, 0u, BREAK_EDITOR_LANG_ZH_CN),
                  "OK");
    ASSERT_EQ(break_editor_plugin_panels_set_button_label(reg, 1u, "a", "ok",
                                                          BREAK_EDITOR_LANG_ZH_CN, "first"),
              BREAK_EDITOR_PLUGIN_PANEL_OK);
    ASSERT_EQ(break_editor_plugin_panels_set_button_label(reg, 1u, "a", "ok",
                                                          BREAK_EDITOR_LANG_ZH_CN, ZH_RUN),
              BREAK_EDITOR_PLUGIN_PANEL_OK);
    ASSERT_EQ(break_editor_plugin_panels_set_button_label(reg, 1u, "a", "no",
                                                          BREAK_EDITOR_LANG_EN_US, "Cancel"),
              BREAK_EDITOR_PLUGIN_PANEL_OK);
    ASSERT_STR_EQ(break_editor_plugin_panels_button_label(reg, 0u, 0u, BREAK_EDITOR_LANG_ZH_CN),
                  ZH_RUN);
    ASSERT_STR_EQ(break_editor_plugin_panels_button_label(reg, 0u, 0u, BREAK_EDITOR_LANG_EN_US),
                  "OK");
    ASSERT_STR_EQ(break_editor_plugin_panels_button_label(reg, 0u, 0u, BREAK_EDITOR_LANG_COUNT),
                  "OK");
    ASSERT_STR_EQ(break_editor_plugin_panels_button_label(reg, 0u, 0u, (BreakEditorLang)-1),
                  "OK");
    ASSERT_STR_EQ(break_editor_plugin_panels_button_label(reg, 0u, 1u, BREAK_EDITOR_LANG_EN_US),
                  "Cancel");
    ASSERT_STR_EQ(break_editor_plugin_panels_button_label(reg, 0u, 1u, BREAK_EDITOR_LANG_ZH_CN),
                  "No");

    /* removing owner 1 moves panel b to index 0 with its button */
    ASSERT_EQ(break_editor_plugin_panels_remove_owner(reg, 1u), 2u);
    ASSERT_EQ(break_editor_plugin_panels_button_count(reg, 0u), 1u);
    ASSERT_STR_EQ(break_editor_plugin_panels_button_id(reg, 0u, 0u), "keep");
    ASSERT_TRUE(break_editor_plugin_panels_press(reg, 0u, 0u, doc));
    ASSERT_EQ(kept.calls, 1u);
    ASSERT_EQ(ok.calls, 1u);
    ASSERT_EQ(break_editor_plugin_panels_button_count(reg, 1u), 0u);
    /* a reused slot starts with no buttons and no translated labels */
    ASSERT_EQ(break_editor_plugin_panels_add(reg, 3u, "d", "D", record_panel, &log), 0);
    ASSERT_EQ(break_editor_plugin_panels_button_count(reg, 1u), 0u);
    ASSERT_EQ(break_editor_plugin_panels_add_button(reg, 3u, "d", "ok", "OK", record_button, &ok),
              0);
    ASSERT_STR_EQ(break_editor_plugin_panels_button_label(reg, 1u, 0u, BREAK_EDITOR_LANG_ZH_CN),
                  "OK");
    ASSERT_EQ(log.calls, 0u);
    break_editor_plugin_panels_destroy(reg);
}

TEST_MAIN_BEGIN()
    RUN_TEST(panels_buttons_validate_and_keep_order);
    RUN_TEST(panels_buttons_press_labels_and_removal);
    RUN_TEST(panels_create_bounds);
    RUN_TEST(panels_add_validates_and_keeps_order);
    RUN_TEST(panels_remove_owner_keeps_the_rest_in_order);
    RUN_TEST(panels_translated_titles);
    RUN_TEST(panels_render_bounds_and_terminates);
TEST_MAIN_END()
