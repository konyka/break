#pragma once

#include <core/types.h>

#define BREAK_XML_NONE UINT32_MAX
#define BREAK_XML_HARD_MAX_INPUT_BYTES (1024u * 1024u)
#define BREAK_XML_HARD_MAX_NODES 1024u
#define BREAK_XML_HARD_MAX_ATTRIBUTES 2048u
#define BREAK_XML_HARD_MAX_DEPTH 64u
#define BREAK_XML_HARD_MAX_TEXT_BYTES (1024u * 1024u)
#define BREAK_SCENE_XML_CLASS_CAPACITY 64u

typedef enum BreakXmlStatus {
    BREAK_XML_OK = 0,
    BREAK_XML_INVALID,
    BREAK_XML_OVERLOAD,
    BREAK_XML_OOM,
    BREAK_XML_FAILED
} BreakXmlStatus;

typedef enum BreakXmlNodeKind {
    BREAK_XML_ELEMENT = 1,
    BREAK_XML_TEXT
} BreakXmlNodeKind;

typedef struct BreakXmlLimits {
    u32 max_input_bytes;
    u32 max_nodes;
    u32 max_attributes;
    u32 max_depth;
    u32 max_text_bytes;
} BreakXmlLimits;

typedef struct BreakXmlDocument BreakXmlDocument;

BreakXmlDocument *break_xml_create(const BreakXmlLimits *limits);
void break_xml_destroy(BreakXmlDocument *document);
BreakXmlStatus break_xml_parse(BreakXmlDocument *document,
                               const void *data, usize size);
BreakXmlStatus break_xml_serialize(const BreakXmlDocument *document,
                                   char *out, usize capacity, usize *out_size);
u32 break_xml_root(const BreakXmlDocument *document);
BreakXmlNodeKind break_xml_kind(const BreakXmlDocument *document, u32 node);
const char *break_xml_name(const BreakXmlDocument *document, u32 node);
const char *break_xml_text(const BreakXmlDocument *document, u32 node);
u32 break_xml_first_child(const BreakXmlDocument *document, u32 node);
u32 break_xml_next_sibling(const BreakXmlDocument *document, u32 node);
u32 break_xml_attribute_count(const BreakXmlDocument *document, u32 node);
bool break_xml_attribute(const BreakXmlDocument *document, u32 node, u32 index,
                         const char **out_name, const char **out_value);

typedef struct BreakSceneXmlEntity {
    u32 index;
    u32 generation;
    char class_name[BREAK_SCENE_XML_CLASS_CAPACITY];
} BreakSceneXmlEntity;

BreakXmlStatus break_scene_xml_read(const BreakXmlDocument *document,
                                    BreakSceneXmlEntity *out, u32 capacity,
                                    u32 *out_count);
BreakXmlStatus break_scene_xml_write(const BreakSceneXmlEntity *entities,
                                     u32 count, char *out, usize capacity,
                                     usize *out_size);
