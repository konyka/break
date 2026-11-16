#include "test_framework.h"

#include <editor/editor_plugin_sections.h>

#include <string.h>

typedef struct SectionLog {
    u32 calls;
    const BreakEditorDoc *last_doc;
    BreakEditorEntityId last_entity;
    bool result;
    const char *text;
    bool overrun;
} SectionLog;

static bool record_section(void *user, const BreakEditorDoc *doc, BreakEditorEntityId entity,
                           char *out, usize cap)
{
    SectionLog *log = (SectionLog *)user;
    log->calls++;
    log->last_doc = doc;
    log->last_entity = entity;
    if (log->overrun) {
        memset(out, 'x', cap);
        return true;
    }
    if (log->text) (void)snprintf(out, cap, "%s", log->text);
    return log->result;
}

TEST(sections_create_bounds)
{
    ASSERT_TRUE(break_editor_plugin_sections_create(0u) == NULL);
    ASSERT_TRUE(break_editor_plugin_sections_create(BREAK_EDITOR_PLUGIN_SECTIONS_MAX + 1u) == NULL);
    BreakEditorPluginSections *reg =
        break_editor_plugin_sections_create(BREAK_EDITOR_PLUGIN_SECTIONS_MAX);
    ASSERT_NOT_NULL(reg);
    ASSERT_EQ(break_editor_plugin_sections_count(reg), 0u);
    break_editor_plugin_sections_destroy(reg);
    break_editor_plugin_sections_destroy(NULL);
    ASSERT_EQ(break_editor_plugin_sections_count(NULL), 0u);
}

TEST(sections_add_validates_and_keeps_order)
{
    SectionLog log = {0};
    char title[BREAK_EDITOR_PLUGIN_SECTION_TITLE_CAPACITY + 1u];
    char id[BREAK_EDITOR_PLUGIN_SECTION_ID_CAPACITY + 1u];
    BreakEditorPluginSections *reg = break_editor_plugin_sections_create(2u);
    ASSERT_NOT_NULL(reg);
    ASSERT_EQ(break_editor_plugin_sections_add(NULL, 1u, "a", "A", record_section, &log),
              BREAK_EDITOR_PLUGIN_SECTION_INVALID);
    ASSERT_EQ(break_editor_plugin_sections_add(reg, 0u, "a", "A", record_section, &log),
              BREAK_EDITOR_PLUGIN_SECTION_INVALID);
    ASSERT_EQ(break_editor_plugin_sections_add(reg, 1u, "a", "A", NULL, &log),
              BREAK_EDITOR_PLUGIN_SECTION_INVALID);
    ASSERT_EQ(break_editor_plugin_sections_add(reg, 1u, NULL, "A", record_section, &log),
              BREAK_EDITOR_PLUGIN_SECTION_BAD_ID);
    ASSERT_EQ(break_editor_plugin_sections_add(reg, 1u, "", "A", record_section, &log),
              BREAK_EDITOR_PLUGIN_SECTION_BAD_ID);
    ASSERT_EQ(break_editor_plugin_sections_add(reg, 1u, "Bad", "A", record_section, &log),
              BREAK_EDITOR_PLUGIN_SECTION_BAD_ID);
    ASSERT_EQ(break_editor_plugin_sections_add(reg, 1u, "a b", "A", record_section, &log),
              BREAK_EDITOR_PLUGIN_SECTION_BAD_ID);
    memset(id, 'i', BREAK_EDITOR_PLUGIN_SECTION_ID_CAPACITY);
    id[BREAK_EDITOR_PLUGIN_SECTION_ID_CAPACITY] = '\0';
    ASSERT_EQ(break_editor_plugin_sections_add(reg, 1u, id, "A", record_section, &log),
              BREAK_EDITOR_PLUGIN_SECTION_BAD_ID);
    id[BREAK_EDITOR_PLUGIN_SECTION_ID_CAPACITY - 1u] = '\0';
    ASSERT_EQ(break_editor_plugin_sections_add(reg, 1u, "a", NULL, record_section, &log),
              BREAK_EDITOR_PLUGIN_SECTION_BAD_TITLE);
    ASSERT_EQ(break_editor_plugin_sections_add(reg, 1u, "a", "", record_section, &log),
              BREAK_EDITOR_PLUGIN_SECTION_BAD_TITLE);
    ASSERT_EQ(break_editor_plugin_sections_add(reg, 1u, "a", "A\nB", record_section, &log),
              BREAK_EDITOR_PLUGIN_SECTION_BAD_TITLE);
    ASSERT_EQ(break_editor_plugin_sections_add(reg, 1u, "a", "A\x7f", record_section, &log),
              BREAK_EDITOR_PLUGIN_SECTION_BAD_TITLE);
    memset(title, 't', BREAK_EDITOR_PLUGIN_SECTION_TITLE_CAPACITY);
    title[BREAK_EDITOR_PLUGIN_SECTION_TITLE_CAPACITY] = '\0';
    ASSERT_EQ(break_editor_plugin_sections_add(reg, 1u, "a", title, record_section, &log),
              BREAK_EDITOR_PLUGIN_SECTION_BAD_TITLE);
    title[BREAK_EDITOR_PLUGIN_SECTION_TITLE_CAPACITY - 1u] = '\0';
    ASSERT_EQ(break_editor_plugin_sections_count(reg), 0u);

    ASSERT_EQ(break_editor_plugin_sections_add(reg, 1u, id, title, record_section, &log),
              BREAK_EDITOR_PLUGIN_SECTION_OK);
    ASSERT_EQ(break_editor_plugin_sections_add(reg, 2u, "terrain.layers_2", "Terrain \xe5\x9c\xb0",
                                               record_section, &log),
              BREAK_EDITOR_PLUGIN_SECTION_OK);
    ASSERT_EQ(break_editor_plugin_sections_add(reg, 3u, id, "Other", record_section, &log),
              BREAK_EDITOR_PLUGIN_SECTION_DUPLICATE);
    ASSERT_EQ(break_editor_plugin_sections_add(reg, 3u, "c", "C", record_section, &log),
              BREAK_EDITOR_PLUGIN_SECTION_FULL);
    ASSERT_EQ(break_editor_plugin_sections_count(reg), 2u);
    ASSERT_STR_EQ(break_editor_plugin_sections_id(reg, 0u), id);
    ASSERT_STR_EQ(break_editor_plugin_sections_title(reg, 0u), title);
    ASSERT_EQ(break_editor_plugin_sections_owner(reg, 0u), 1u);
    ASSERT_STR_EQ(break_editor_plugin_sections_id(reg, 1u), "terrain.layers_2");
    ASSERT_STR_EQ(break_editor_plugin_sections_title(reg, 1u), "Terrain \xe5\x9c\xb0");
    ASSERT_EQ(break_editor_plugin_sections_owner(reg, 1u), 2u);
    ASSERT_TRUE(break_editor_plugin_sections_id(reg, 2u) == NULL);
    ASSERT_TRUE(break_editor_plugin_sections_title(reg, 2u) == NULL);
    ASSERT_EQ(break_editor_plugin_sections_owner(reg, 2u), 0u);
    ASSERT_TRUE(break_editor_plugin_sections_id(NULL, 0u) == NULL);
    ASSERT_TRUE(break_editor_plugin_sections_title(NULL, 0u) == NULL);
    ASSERT_EQ(break_editor_plugin_sections_owner(NULL, 0u), 0u);
    ASSERT_EQ(break_editor_plugin_sections_find(reg, "terrain.layers_2"), 1u);
    ASSERT_EQ(break_editor_plugin_sections_find(reg, id), 0u);
    ASSERT_EQ(break_editor_plugin_sections_find(reg, "terrain"), BREAK_EDITOR_PLUGIN_SECTION_NONE);
    ASSERT_EQ(break_editor_plugin_sections_find(reg, NULL), BREAK_EDITOR_PLUGIN_SECTION_NONE);
    ASSERT_EQ(break_editor_plugin_sections_find(NULL, "c"), BREAK_EDITOR_PLUGIN_SECTION_NONE);
    break_editor_plugin_sections_destroy(reg);
}

TEST(sections_remove_owner_keeps_the_rest_in_order)
{
    SectionLog log = {0};
    BreakEditorPluginSections *reg = break_editor_plugin_sections_create(8u);
    ASSERT_NOT_NULL(reg);
    ASSERT_EQ(break_editor_plugin_sections_add(reg, 1u, "a", "A", record_section, &log),
              BREAK_EDITOR_PLUGIN_SECTION_OK);
    ASSERT_EQ(break_editor_plugin_sections_add(reg, 2u, "b", "B", record_section, &log),
              BREAK_EDITOR_PLUGIN_SECTION_OK);
    ASSERT_EQ(break_editor_plugin_sections_add(reg, 1u, "c", "C", record_section, &log),
              BREAK_EDITOR_PLUGIN_SECTION_OK);
    ASSERT_EQ(break_editor_plugin_sections_add(reg, 3u, "d", "D", record_section, &log),
              BREAK_EDITOR_PLUGIN_SECTION_OK);
    ASSERT_EQ(break_editor_plugin_sections_remove_owner(reg, 1u), 2u);
    ASSERT_EQ(break_editor_plugin_sections_count(reg), 2u);
    ASSERT_STR_EQ(break_editor_plugin_sections_id(reg, 0u), "b");
    ASSERT_STR_EQ(break_editor_plugin_sections_id(reg, 1u), "d");
    ASSERT_EQ(break_editor_plugin_sections_owner(reg, 1u), 3u);
    ASSERT_EQ(break_editor_plugin_sections_remove_owner(reg, 1u), 0u);
    ASSERT_EQ(break_editor_plugin_sections_remove_owner(reg, 0u), 0u);
    ASSERT_EQ(break_editor_plugin_sections_remove_owner(NULL, 2u), 0u);
    ASSERT_EQ(break_editor_plugin_sections_find(reg, "a"), BREAK_EDITOR_PLUGIN_SECTION_NONE);
    /* a removed id can be registered again */
    ASSERT_EQ(break_editor_plugin_sections_add(reg, 4u, "a", "A2", record_section, &log),
              BREAK_EDITOR_PLUGIN_SECTION_OK);
    ASSERT_EQ(break_editor_plugin_sections_find(reg, "a"), 2u);
    break_editor_plugin_sections_destroy(reg);
}

TEST(sections_describe_bounds_and_terminates)
{
    SectionLog ok = {0};
    SectionLog no = {0};
    SectionLog wild = {0};
    char out[16];
    BreakEditorDoc *doc = (BreakEditorDoc *)&ok; /* opaque token, never dereferenced */
    BreakEditorEntityId e = {7u, 3u};
    BreakEditorPluginSections *reg = break_editor_plugin_sections_create(4u);
    ASSERT_NOT_NULL(reg);
    ok.result = true;
    ok.text = "hp=10 armor=2 long tail";
    no.result = false;
    no.text = "ignored";
    wild.overrun = true;
    ASSERT_EQ(break_editor_plugin_sections_add(reg, 1u, "ok", "Ok", record_section, &ok),
              BREAK_EDITOR_PLUGIN_SECTION_OK);
    ASSERT_EQ(break_editor_plugin_sections_add(reg, 1u, "no", "No", record_section, &no),
              BREAK_EDITOR_PLUGIN_SECTION_OK);
    ASSERT_EQ(break_editor_plugin_sections_add(reg, 1u, "wild", "Wild", record_section, &wild),
              BREAK_EDITOR_PLUGIN_SECTION_OK);

    memset(out, 'z', sizeof out);
    ASSERT_TRUE(break_editor_plugin_sections_describe(reg, 0u, doc, e, out, sizeof out));
    ASSERT_STR_EQ(out, "hp=10 armor=2 l");
    ASSERT_EQ(ok.calls, 1u);
    ASSERT_TRUE(ok.last_doc == doc);
    ASSERT_EQ(ok.last_entity.index, 7u);
    ASSERT_EQ(ok.last_entity.generation, 3u);

    memset(out, 'z', sizeof out);
    ASSERT_FALSE(break_editor_plugin_sections_describe(reg, 1u, doc, e, out, sizeof out));
    ASSERT_EQ(out[0], '\0');
    ASSERT_EQ(no.calls, 1u);

    ASSERT_TRUE(break_editor_plugin_sections_describe(reg, 2u, doc, e, out, sizeof out));
    ASSERT_EQ(out[sizeof out - 1u], '\0');
    ASSERT_EQ(strlen(out), sizeof out - 1u);

    out[0] = 'z';
    ASSERT_FALSE(break_editor_plugin_sections_describe(reg, 3u, doc, e, out, sizeof out));
    ASSERT_EQ(out[0], '\0');
    ASSERT_FALSE(break_editor_plugin_sections_describe(NULL, 0u, doc, e, out, sizeof out));
    ASSERT_FALSE(break_editor_plugin_sections_describe(reg, 0u, doc, e, NULL, sizeof out));
    ASSERT_FALSE(break_editor_plugin_sections_describe(reg, 0u, doc, e, out, 0u));
    ASSERT_EQ(ok.calls, 1u);
    break_editor_plugin_sections_destroy(reg);
}

TEST_MAIN_BEGIN()
    RUN_TEST(sections_create_bounds);
    RUN_TEST(sections_add_validates_and_keeps_order);
    RUN_TEST(sections_remove_owner_keeps_the_rest_in_order);
    RUN_TEST(sections_describe_bounds_and_terminates);
TEST_MAIN_END()
