#include "test_framework.h"

#include <system/break_xml.h>

#include <string.h>

static BreakXmlLimits limits(void) {
    BreakXmlLimits value;
    value.max_input_bytes = 4096u;
    value.max_nodes = 64u;
    value.max_attributes = 64u;
    value.max_depth = 8u;
    value.max_text_bytes = 4096u;
    return value;
}

static BreakXmlDocument *create_default(void) {
    BreakXmlLimits value = limits();
    return break_xml_create(&value);
}

TEST(xml_parses_tree_entities_utf8_and_roundtrips) {
    const char *input = "<?xml version=\"1.0\"?><!--before--><root a=\"1 &amp; 2\" quote=\"&quot;&apos;\"><child/>text &lt; \xE4\xB8\xAD &gt;</root>";
    char encoded[2048];
    usize written = 0u;
    BreakXmlDocument *doc = create_default();
    u32 root;
    u32 child;
    u32 text;
    const char *name;
    const char *value;
    ASSERT_NOT_NULL(doc);
    ASSERT_EQ(break_xml_parse(doc, input, strlen(input)), BREAK_XML_OK);
    root = break_xml_root(doc);
    ASSERT_EQ(break_xml_kind(doc, root), BREAK_XML_ELEMENT);
    ASSERT_STR_EQ(break_xml_name(doc, root), "root");
    ASSERT_EQ(break_xml_attribute_count(doc, root), 2u);
    ASSERT_TRUE(break_xml_attribute(doc, root, 0u, &name, &value));
    ASSERT_STR_EQ(name, "a");
    ASSERT_STR_EQ(value, "1 & 2");
    ASSERT_TRUE(break_xml_attribute(doc, root, 1u, &name, &value));
    ASSERT_STR_EQ(value, "\"'");
    child = break_xml_first_child(doc, root);
    ASSERT_STR_EQ(break_xml_name(doc, child), "child");
    text = break_xml_next_sibling(doc, child);
    ASSERT_EQ(break_xml_kind(doc, text), BREAK_XML_TEXT);
    ASSERT_STR_EQ(break_xml_text(doc, text), "text < \xE4\xB8\xAD >");
    ASSERT_EQ(break_xml_next_sibling(doc, text), BREAK_XML_NONE);
    ASSERT_EQ(break_xml_serialize(doc, encoded, sizeof(encoded), &written), BREAK_XML_OK);
    ASSERT_TRUE(written > 0u && written < sizeof(encoded));
    ASSERT_STR_EQ(encoded + written, "");
    ASSERT_EQ(break_xml_parse(doc, encoded, written), BREAK_XML_OK);
    ASSERT_EQ(break_xml_serialize(doc, encoded, sizeof(encoded), &written), BREAK_XML_OK);
    ASSERT_TRUE(strstr(encoded, "&amp;") != NULL);
    ASSERT_TRUE(strstr(encoded, "&lt;") != NULL);
    break_xml_destroy(doc);
}

TEST(xml_rejects_dtd_and_entity_expansion) {
    const char *documents[] = {
        "<!DOCTYPE root [<!ENTITY x \"boom\">]><root>&x;</root>",
        "<root>&unknown;</root>",
        "<root>&#60;</root>",
        "<root><![CDATA[text]]></root>",
        "<!DOCTYPE root><root/>"
    };
    BreakXmlDocument *doc = create_default();
    ASSERT_NOT_NULL(doc);
    for (u32 i = 0u; i < sizeof(documents) / sizeof(documents[0]); i++) {
        ASSERT_EQ(break_xml_parse(doc, documents[i], strlen(documents[i])), BREAK_XML_INVALID);
    }
    break_xml_destroy(doc);
}

TEST(xml_rejects_invalid_utf8_and_forbidden_characters) {
    static const u8 invalid[][8] = {
        { '<', 'r', '>', 0xC0, 0x80, '<', '/', 'r' },
        { '<', 'r', '>', 0xE2, 0x28, 0xA1, '<', '/' },
        { '<', 'r', '>', 0xED, 0xA0, 0x80, '<', '/' },
        { '<', 'r', '>', 0xF4, 0x90, 0x80, 0x80, '<' },
        { '<', 'r', '>', 0xE4, 0xB8, '<', '/', 'r' },
        { '<', 'r', '>', 0x01, '<', '/', 'r', '>' },
        { '<', 'r', '>', 0x00, '<', '/', 'r', '>' }
    };
    const char *valid = "<r>\xF4\x8F\xBF\xBF</r>";
    BreakXmlDocument *doc = create_default();
    ASSERT_NOT_NULL(doc);
    for (u32 i = 0u; i < sizeof(invalid) / sizeof(invalid[0]); i++)
        ASSERT_EQ(break_xml_parse(doc, invalid[i], sizeof(invalid[i])), BREAK_XML_INVALID);
    ASSERT_EQ(break_xml_parse(doc, valid, strlen(valid)), BREAK_XML_OK);
    break_xml_destroy(doc);
}

TEST(xml_rejects_malformed_markup) {
    const char *documents[] = {
        "", "text", "<a/><b/>", "<a>", "</a>", "<a></b>", "<a><b></a></b>",
        "<a x=1/>", "<a x=\"1\" x=\"2\"/>", "<a><</a>", "<a>&amp</a>",
        "<a><!-- bad -- comment --></a>", "<a>text</a>junk"
    };
    BreakXmlDocument *doc = create_default();
    ASSERT_NOT_NULL(doc);
    for (u32 i = 0u; i < sizeof(documents) / sizeof(documents[0]); i++)
        ASSERT_EQ(break_xml_parse(doc, documents[i], strlen(documents[i])), BREAK_XML_INVALID);
    break_xml_destroy(doc);
}

TEST(xml_enforces_every_configured_bound) {
    BreakXmlLimits base = limits();
    const char *too_deep = "<a><b><c/></b></a>";
    const char *too_many_nodes = "<a><b/><c/></a>";
    const char *too_many_attributes = "<a x=\"1\" y=\"2\"/>";
    BreakXmlDocument *doc;
    base.max_input_bytes = 4u;
    doc = break_xml_create(&base);
    ASSERT_NOT_NULL(doc);
    ASSERT_EQ(break_xml_parse(doc, "<a></a>", 7u), BREAK_XML_OVERLOAD);
    break_xml_destroy(doc);
    base = limits();
    base.max_depth = 2u;
    doc = break_xml_create(&base);
    ASSERT_NOT_NULL(doc);
    ASSERT_EQ(break_xml_parse(doc, too_deep, strlen(too_deep)), BREAK_XML_OVERLOAD);
    break_xml_destroy(doc);
    base = limits();
    base.max_nodes = 2u;
    doc = break_xml_create(&base);
    ASSERT_NOT_NULL(doc);
    ASSERT_EQ(break_xml_parse(doc, too_many_nodes, strlen(too_many_nodes)), BREAK_XML_OVERLOAD);
    break_xml_destroy(doc);
    base = limits();
    base.max_attributes = 1u;
    doc = break_xml_create(&base);
    ASSERT_NOT_NULL(doc);
    ASSERT_EQ(break_xml_parse(doc, too_many_attributes, strlen(too_many_attributes)), BREAK_XML_OVERLOAD);
    break_xml_destroy(doc);
    base = limits();
    base.max_text_bytes = 4u;
    doc = break_xml_create(&base);
    ASSERT_NOT_NULL(doc);
    ASSERT_EQ(break_xml_parse(doc, "<abcd/>", 7u), BREAK_XML_OVERLOAD);
    break_xml_destroy(doc);
    base.max_input_bytes = 0u;
    ASSERT_TRUE(break_xml_create(&base) == NULL);
    base = limits();
    base.max_depth = BREAK_XML_HARD_MAX_DEPTH + 1u;
    ASSERT_TRUE(break_xml_create(&base) == NULL);
}

TEST(failed_parse_preserves_previous_document) {
    BreakXmlDocument *doc = create_default();
    const char *bad = "<new>";
    const char *old = "<old><kept/></old>";
    ASSERT_NOT_NULL(doc);
    ASSERT_EQ(break_xml_parse(doc, old, strlen(old)), BREAK_XML_OK);
    ASSERT_EQ(break_xml_parse(doc, bad, strlen(bad)), BREAK_XML_INVALID);
    ASSERT_STR_EQ(break_xml_name(doc, break_xml_root(doc)), "old");
    ASSERT_STR_EQ(break_xml_name(doc, break_xml_first_child(doc, break_xml_root(doc))), "kept");
    break_xml_destroy(doc);
}

TEST(serializer_reports_output_capacity_without_length) {
    BreakXmlDocument *doc = create_default();
    char output[4];
    usize written = 99u;
    ASSERT_NOT_NULL(doc);
    ASSERT_EQ(break_xml_parse(doc, "<root/>", 7u), BREAK_XML_OK);
    ASSERT_EQ(break_xml_serialize(doc, output, sizeof(output), &written), BREAK_XML_OVERLOAD);
    ASSERT_EQ(written, 0u);
    break_xml_destroy(doc);
}

TEST(scene_sidecar_roundtrip_uses_versioned_schema) {
    BreakSceneXmlEntity rows[2] = {{1u, 7u, "Player"}, {8u, 2u, "Enemy.Grunt"}};
    BreakSceneXmlEntity loaded[2];
    BreakXmlDocument *doc = create_default();
    char xml[1024];
    usize written = 0u;
    u32 count = 0u;
    memset(loaded, 0, sizeof(loaded));
    ASSERT_NOT_NULL(doc);
    ASSERT_EQ(break_scene_xml_write(rows, 2u, xml, sizeof(xml), &written), BREAK_XML_OK);
    ASSERT_EQ(break_xml_parse(doc, xml, written), BREAK_XML_OK);
    ASSERT_EQ(break_scene_xml_read(doc, loaded, 2u, &count), BREAK_XML_OK);
    ASSERT_EQ(count, 2u);
    ASSERT_EQ(loaded[0].index, 1u);
    ASSERT_EQ(loaded[0].generation, 7u);
    ASSERT_STR_EQ(loaded[0].class_name, "Player");
    ASSERT_EQ(loaded[1].index, 8u);
    ASSERT_STR_EQ(loaded[1].class_name, "Enemy.Grunt");
    break_xml_destroy(doc);
}

TEST(scene_sidecar_rejects_unknown_or_ambiguous_data) {
    const char *documents[] = {
        "<break-scene version=\"2\"/>",
        "<break-scene version=\"1\"><actor index=\"1\" generation=\"1\" class=\"P\"/></break-scene>",
        "<break-scene version=\"1\"><entity index=\"0\" generation=\"1\" class=\"P\"/></break-scene>",
        "<break-scene version=\"1\"><entity index=\"1\" generation=\"0\" class=\"P\"/></break-scene>",
        "<break-scene version=\"1\"><entity index=\"4294967296\" generation=\"1\" class=\"P\"/></break-scene>",
        "<break-scene version=\"1\"><entity index=\"1\" generation=\"1\" class=\"bad class\"/></break-scene>",
        "<break-scene version=\"1\"><entity index=\"1\" generation=\"1\" class=\"P\" extra=\"x\"/></break-scene>",
        "<break-scene version=\"1\"><entity index=\"1\" generation=\"1\" class=\"P\">text</entity></break-scene>",
        "<break-scene version=\"1\"><entity index=\"1\" generation=\"1\" class=\"P\"/><entity index=\"1\" generation=\"1\" class=\"Q\"/></break-scene>"
    };
    BreakXmlDocument *doc = create_default();
    BreakSceneXmlEntity output[1];
    u32 count = 99u;
    ASSERT_NOT_NULL(doc);
    memset(&output[0], 0x5a, sizeof(output[0]));
    for (u32 i = 0u; i < sizeof(documents) / sizeof(documents[0]); i++) {
        ASSERT_EQ(break_xml_parse(doc, documents[i], strlen(documents[i])), BREAK_XML_OK);
        ASSERT_EQ(break_scene_xml_read(doc, output, 1u, &count), BREAK_XML_INVALID);
        ASSERT_EQ(count, 0u);
        ASSERT_EQ(output[0].index, 0x5a5a5a5au);
    }
    break_xml_destroy(doc);
}

TEST(scene_sidecar_read_capacity_is_transactional) {
    const char *xml = "<break-scene version=\"1\"><entity index=\"1\" generation=\"2\" class=\"P\"/><entity index=\"2\" generation=\"3\" class=\"Q\"/></break-scene>";
    BreakXmlDocument *doc = create_default();
    BreakSceneXmlEntity output[1];
    u32 count = 0u;
    ASSERT_NOT_NULL(doc);
    memset(&output[0], 0x5a, sizeof(output[0]));
    ASSERT_EQ(break_xml_parse(doc, xml, strlen(xml)), BREAK_XML_OK);
    ASSERT_EQ(break_scene_xml_read(doc, output, 1u, &count), BREAK_XML_OVERLOAD);
    ASSERT_EQ(count, 2u);
    ASSERT_EQ(output[0].index, 0x5a5a5a5au);
    break_xml_destroy(doc);
}

TEST_MAIN_BEGIN()
    RUN_TEST(xml_parses_tree_entities_utf8_and_roundtrips);
    RUN_TEST(xml_rejects_dtd_and_entity_expansion);
    RUN_TEST(xml_rejects_invalid_utf8_and_forbidden_characters);
    RUN_TEST(xml_rejects_malformed_markup);
    RUN_TEST(xml_enforces_every_configured_bound);
    RUN_TEST(failed_parse_preserves_previous_document);
    RUN_TEST(serializer_reports_output_capacity_without_length);
    RUN_TEST(scene_sidecar_roundtrip_uses_versioned_schema);
    RUN_TEST(scene_sidecar_rejects_unknown_or_ambiguous_data);
    RUN_TEST(scene_sidecar_read_capacity_is_transactional);
TEST_MAIN_END()
