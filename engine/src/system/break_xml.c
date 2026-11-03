#include <system/break_xml.h>
#include <system/break_system_internal.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct BreakXmlAttribute {
    u32 name;
    u32 value;
} BreakXmlAttribute;

typedef struct BreakXmlNode {
    BreakXmlNodeKind kind;
    u32 name;
    u32 text;
    u32 parent;
    u32 first_child;
    u32 last_child;
    u32 next_sibling;
    u32 first_attribute;
    u32 attribute_count;
    u32 depth;
} BreakXmlNode;

typedef struct BreakXmlStorage {
    BreakXmlNode *nodes;
    BreakXmlAttribute *attributes;
    char *text;
    u32 node_count;
    u32 attribute_count;
    usize text_used;
    u32 root;
    u32 current;
} BreakXmlStorage;

struct BreakXmlDocument {
    BreakXmlLimits limits;
    BreakXmlStorage *active;
    BreakXmlStorage *scratch;
};

typedef struct BreakXmlParser {
    BreakXmlStorage *storage;
    const BreakXmlLimits *limits;
    const u8 *cursor;
    const u8 *end;
} BreakXmlParser;

typedef struct BreakXmlWriter {
    char *out;
    usize capacity;
    usize size;
    BreakXmlStatus status;
} BreakXmlWriter;

static void xml_storage_destroy(BreakXmlStorage *storage) {
    if (!storage) return;
    free(storage->text);
    free(storage->attributes);
    free(storage->nodes);
    free(storage);
}

static BreakXmlStorage *xml_storage_create(const BreakXmlLimits *limits) {
    BreakXmlStorage *storage = (BreakXmlStorage *)calloc(1u, sizeof(*storage));
    if (!storage) return NULL;
    storage->nodes = (BreakXmlNode *)calloc(limits->max_nodes, sizeof(BreakXmlNode));
    storage->attributes = (BreakXmlAttribute *)calloc(limits->max_attributes,
                                                       sizeof(BreakXmlAttribute));
    storage->text = (char *)malloc(limits->max_text_bytes);
    if (!storage->nodes || !storage->attributes || !storage->text) {
        xml_storage_destroy(storage);
        return NULL;
    }
    storage->root = BREAK_XML_NONE;
    storage->current = BREAK_XML_NONE;
    return storage;
}

static bool xml_limits_valid(const BreakXmlLimits *limits) {
    return limits && limits->max_input_bytes > 0u &&
           limits->max_input_bytes <= BREAK_XML_HARD_MAX_INPUT_BYTES &&
           limits->max_nodes > 0u && limits->max_nodes <= BREAK_XML_HARD_MAX_NODES &&
           limits->max_attributes > 0u &&
           limits->max_attributes <= BREAK_XML_HARD_MAX_ATTRIBUTES &&
           limits->max_depth > 0u && limits->max_depth <= BREAK_XML_HARD_MAX_DEPTH &&
           limits->max_text_bytes > 0u &&
           limits->max_text_bytes <= BREAK_XML_HARD_MAX_TEXT_BYTES;
}

BreakXmlDocument *break_xml_create(const BreakXmlLimits *limits) {
    BreakXmlDocument *document;
    if (!xml_limits_valid(limits)) return NULL;
    document = (BreakXmlDocument *)calloc(1u, sizeof(*document));
    if (!document) return NULL;
    document->limits = *limits;
    document->active = xml_storage_create(limits);
    document->scratch = xml_storage_create(limits);
    if (!document->active || !document->scratch) {
        break_xml_destroy(document);
        return NULL;
    }
    return document;
}

void break_xml_destroy(BreakXmlDocument *document) {
    if (!document) return;
    xml_storage_destroy(document->scratch);
    xml_storage_destroy(document->active);
    free(document);
}

static u32 xml_utf8_codepoint(const u8 *data, usize *out_length) {
    if (data[0] < 0x80u) {
        *out_length = 1u;
        return data[0];
    }
    if (data[0] < 0xE0u) {
        *out_length = 2u;
        return ((u32)(data[0] & 0x1Fu) << 6u) | (u32)(data[1] & 0x3Fu);
    }
    if (data[0] < 0xF0u) {
        *out_length = 3u;
        return ((u32)(data[0] & 0x0Fu) << 12u) |
               ((u32)(data[1] & 0x3Fu) << 6u) | (u32)(data[2] & 0x3Fu);
    }
    *out_length = 4u;
    return ((u32)(data[0] & 0x07u) << 18u) |
           ((u32)(data[1] & 0x3Fu) << 12u) |
           ((u32)(data[2] & 0x3Fu) << 6u) | (u32)(data[3] & 0x3Fu);
}

static bool xml_input_characters_valid(const u8 *data, usize size) {
    usize offset = 0u;
    if (!break_system_utf8_valid((const char *)data, size)) return false;
    while (offset < size) {
        usize length;
        u32 codepoint = xml_utf8_codepoint(data + offset, &length);
        if (!((codepoint >= 0x20u && codepoint <= 0xD7FFu) ||
              (codepoint >= 0xE000u && codepoint <= 0xFFFDu) ||
              (codepoint >= 0x10000u && codepoint <= 0x10FFFFu) ||
              codepoint == 0x09u || codepoint == 0x0Au || codepoint == 0x0Du))
            return false;
        offset += length;
    }
    return true;
}

static bool xml_starts(const BreakXmlParser *parser, const char *token, usize length) {
    return (usize)(parser->end - parser->cursor) >= length &&
           memcmp(parser->cursor, token, length) == 0;
}

static bool xml_space(u8 c) {
    return c == ' ' || c == '\t' || c == '\r' || c == '\n';
}

static bool xml_skip_space(BreakXmlParser *parser) {
    const u8 *start = parser->cursor;
    while (parser->cursor < parser->end && xml_space(*parser->cursor)) parser->cursor++;
    return parser->cursor != start;
}

static bool xml_name_start(u8 c) {
    return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c == '_' || c == ':';
}

static bool xml_name_character(u8 c) {
    return xml_name_start(c) || (c >= '0' && c <= '9') || c == '.' || c == '-';
}

static const u8 *xml_name_end(const u8 *cursor, const u8 *end) {
    const u8 *p = cursor;
    if (p >= end || !xml_name_start(*p)) return NULL;
    p++;
    while (p < end && xml_name_character(*p)) p++;
    return p;
}

static BreakXmlStatus xml_reserve_text(BreakXmlStorage *storage,
                                       const BreakXmlLimits *limits,
                                       usize raw_length, u32 *out_offset,
                                       char **out_text) {
    usize remaining;
    if (storage->text_used >= limits->max_text_bytes) return BREAK_XML_OVERLOAD;
    remaining = limits->max_text_bytes - storage->text_used;
    if (raw_length >= remaining) return BREAK_XML_OVERLOAD;
    *out_offset = (u32)storage->text_used;
    *out_text = storage->text + storage->text_used;
    storage->text_used += raw_length + 1u;
    return BREAK_XML_OK;
}

static BreakXmlStatus xml_store_raw(BreakXmlStorage *storage,
                                    const BreakXmlLimits *limits,
                                    const u8 *data, usize length, u32 *out_offset) {
    char *text;
    BreakXmlStatus status = xml_reserve_text(storage, limits, length, out_offset, &text);
    if (status != BREAK_XML_OK) return status;
    if (length) memcpy(text, data, length);
    text[length] = '\0';
    return BREAK_XML_OK;
}

static BreakXmlStatus xml_store_decoded(BreakXmlStorage *storage,
                                        const BreakXmlLimits *limits,
                                        const u8 *data, usize length,
                                        u32 *out_offset) {
    char *text;
    usize source = 0u;
    usize written = 0u;
    BreakXmlStatus status = xml_reserve_text(storage, limits, length, out_offset, &text);
    if (status != BREAK_XML_OK) return status;
    while (source < length) {
        if (data[source] != '&') {
            text[written++] = (char)data[source++];
            continue;
        }
        if (source + 5u <= length && memcmp(data + source, "&amp;", 5u) == 0) {
            text[written++] = '&';
            source += 5u;
        } else if (source + 4u <= length && memcmp(data + source, "&lt;", 4u) == 0) {
            text[written++] = '<';
            source += 4u;
        } else if (source + 4u <= length && memcmp(data + source, "&gt;", 4u) == 0) {
            text[written++] = '>';
            source += 4u;
        } else if (source + 6u <= length && memcmp(data + source, "&quot;", 6u) == 0) {
            text[written++] = '"';
            source += 6u;
        } else if (source + 6u <= length && memcmp(data + source, "&apos;", 6u) == 0) {
            text[written++] = '\'';
            source += 6u;
        } else {
            return BREAK_XML_INVALID;
        }
    }
    text[written] = '\0';
    storage->text_used -= length - written;
    return BREAK_XML_OK;
}

static BreakXmlStatus xml_add_node(BreakXmlParser *parser, BreakXmlNodeKind kind,
                                   u32 name, u32 text, u32 *out_index) {
    BreakXmlStorage *storage = parser->storage;
    BreakXmlNode *node;
    u32 parent = storage->current;
    u32 index;
    u32 depth = 1u;
    if (storage->node_count == parser->limits->max_nodes) return BREAK_XML_OVERLOAD;
    if (kind == BREAK_XML_ELEMENT && parent != BREAK_XML_NONE)
        depth = storage->nodes[parent].depth + 1u;
    if (kind == BREAK_XML_ELEMENT && depth > parser->limits->max_depth)
        return BREAK_XML_OVERLOAD;
    if (parent == BREAK_XML_NONE) {
        if (kind != BREAK_XML_ELEMENT || storage->root != BREAK_XML_NONE)
            return BREAK_XML_INVALID;
    }
    index = storage->node_count++;
    node = &storage->nodes[index];
    memset(node, 0, sizeof(*node));
    node->kind = kind;
    node->name = name;
    node->text = text;
    node->parent = parent;
    node->first_child = BREAK_XML_NONE;
    node->last_child = BREAK_XML_NONE;
    node->next_sibling = BREAK_XML_NONE;
    node->first_attribute = storage->attribute_count;
    node->depth = depth;
    if (parent == BREAK_XML_NONE) {
        storage->root = index;
    } else {
        BreakXmlNode *parent_node = &storage->nodes[parent];
        if (parent_node->last_child == BREAK_XML_NONE)
            parent_node->first_child = index;
        else
            storage->nodes[parent_node->last_child].next_sibling = index;
        parent_node->last_child = index;
    }
    *out_index = index;
    return BREAK_XML_OK;
}

static BreakXmlStatus xml_parse_comment(BreakXmlParser *parser) {
    parser->cursor += 4u;
    while (parser->cursor < parser->end) {
        if (xml_starts(parser, "-->", 3u)) {
            parser->cursor += 3u;
            return BREAK_XML_OK;
        }
        if (xml_starts(parser, "--", 2u)) return BREAK_XML_INVALID;
        parser->cursor++;
    }
    return BREAK_XML_INVALID;
}

static BreakXmlStatus xml_parse_instruction(BreakXmlParser *parser) {
    parser->cursor += 2u;
    while (parser->cursor < parser->end) {
        if (xml_starts(parser, "?>", 2u)) {
            parser->cursor += 2u;
            return BREAK_XML_OK;
        }
        parser->cursor++;
    }
    return BREAK_XML_INVALID;
}

static BreakXmlStatus xml_parse_close(BreakXmlParser *parser) {
    const u8 *name_start;
    const u8 *name_end;
    BreakXmlNode *current;
    usize length;
    if (parser->storage->current == BREAK_XML_NONE) return BREAK_XML_INVALID;
    parser->cursor += 2u;
    name_start = parser->cursor;
    name_end = xml_name_end(name_start, parser->end);
    if (!name_end) return BREAK_XML_INVALID;
    parser->cursor = name_end;
    xml_skip_space(parser);
    if (parser->cursor >= parser->end || *parser->cursor != '>') return BREAK_XML_INVALID;
    parser->cursor++;
    current = &parser->storage->nodes[parser->storage->current];
    length = (usize)(name_end - name_start);
    if (strlen(parser->storage->text + current->name) != length ||
        memcmp(parser->storage->text + current->name, name_start, length) != 0)
        return BREAK_XML_INVALID;
    parser->storage->current = current->parent;
    return BREAK_XML_OK;
}

static BreakXmlStatus xml_parse_open(BreakXmlParser *parser) {
    const u8 *name_start;
    const u8 *name_end;
    u32 name;
    u32 node_index;
    BreakXmlStatus status;
    parser->cursor++;
    name_start = parser->cursor;
    name_end = xml_name_end(name_start, parser->end);
    if (!name_end) return BREAK_XML_INVALID;
    status = xml_store_raw(parser->storage, parser->limits, name_start,
                           (usize)(name_end - name_start), &name);
    if (status != BREAK_XML_OK) return status;
    status = xml_add_node(parser, BREAK_XML_ELEMENT, name, BREAK_XML_NONE, &node_index);
    if (status != BREAK_XML_OK) return status;
    parser->cursor = name_end;
    for (;;) {
        bool separated = xml_skip_space(parser);
        if (xml_starts(parser, "/>", 2u)) {
            parser->cursor += 2u;
            return BREAK_XML_OK;
        }
        if (parser->cursor < parser->end && *parser->cursor == '>') {
            parser->cursor++;
            parser->storage->current = node_index;
            return BREAK_XML_OK;
        }
        if (!separated) return BREAK_XML_INVALID;
        {
            const u8 *attribute_start = parser->cursor;
            const u8 *attribute_end = xml_name_end(attribute_start, parser->end);
            const u8 *value_start;
            const u8 *value_end;
            u8 quote;
            u32 attribute_name;
            u32 attribute_value;
            BreakXmlAttribute *attribute;
            BreakXmlNode *node = &parser->storage->nodes[node_index];
            if (!attribute_end) return BREAK_XML_INVALID;
            parser->cursor = attribute_end;
            xml_skip_space(parser);
            if (parser->cursor >= parser->end || *parser->cursor != '=')
                return BREAK_XML_INVALID;
            parser->cursor++;
            xml_skip_space(parser);
            if (parser->cursor >= parser->end ||
                (*parser->cursor != '"' && *parser->cursor != '\'')) return BREAK_XML_INVALID;
            quote = *parser->cursor++;
            value_start = parser->cursor;
            while (parser->cursor < parser->end && *parser->cursor != quote) {
                if (*parser->cursor == '<') return BREAK_XML_INVALID;
                parser->cursor++;
            }
            if (parser->cursor >= parser->end) return BREAK_XML_INVALID;
            value_end = parser->cursor++;
            if (parser->storage->attribute_count == parser->limits->max_attributes)
                return BREAK_XML_OVERLOAD;
            status = xml_store_raw(parser->storage, parser->limits, attribute_start,
                                   (usize)(attribute_end - attribute_start), &attribute_name);
            if (status != BREAK_XML_OK) return status;
            for (u32 i = 0u; i < node->attribute_count; i++) {
                u32 previous = parser->storage->attributes[node->first_attribute + i].name;
                if (strcmp(parser->storage->text + previous,
                           parser->storage->text + attribute_name) == 0)
                    return BREAK_XML_INVALID;
            }
            status = xml_store_decoded(parser->storage, parser->limits, value_start,
                                       (usize)(value_end - value_start), &attribute_value);
            if (status != BREAK_XML_OK) return status;
            attribute = &parser->storage->attributes[parser->storage->attribute_count++];
            attribute->name = attribute_name;
            attribute->value = attribute_value;
            node->attribute_count++;
        }
    }
}

static BreakXmlStatus xml_parse_text(BreakXmlParser *parser) {
    const u8 *start = parser->cursor;
    const u8 *end;
    u32 text;
    u32 node;
    BreakXmlStatus status;
    while (parser->cursor < parser->end && *parser->cursor != '<') {
        if (xml_starts(parser, "]]>", 3u)) return BREAK_XML_INVALID;
        parser->cursor++;
    }
    end = parser->cursor;
    if (parser->storage->current == BREAK_XML_NONE) {
        for (const u8 *p = start; p < end; p++)
            if (!xml_space(*p)) return BREAK_XML_INVALID;
        return BREAK_XML_OK;
    }
    if (end == start) return BREAK_XML_INVALID;
    status = xml_store_decoded(parser->storage, parser->limits, start,
                               (usize)(end - start), &text);
    if (status != BREAK_XML_OK) return status;
    return xml_add_node(parser, BREAK_XML_TEXT, BREAK_XML_NONE, text, &node);
}

BreakXmlStatus break_xml_parse(BreakXmlDocument *document,
                               const void *data, usize size) {
    BreakXmlParser parser;
    BreakXmlStorage *next;
    BreakXmlStatus status = BREAK_XML_OK;
    if (!document || !data || size == 0u) return BREAK_XML_INVALID;
    if (size > document->limits.max_input_bytes) return BREAK_XML_OVERLOAD;
    if (!xml_input_characters_valid((const u8 *)data, size)) return BREAK_XML_INVALID;
    next = document->scratch;
    next->node_count = 0u;
    next->attribute_count = 0u;
    next->text_used = 0u;
    next->root = BREAK_XML_NONE;
    next->current = BREAK_XML_NONE;
    parser.storage = next;
    parser.limits = &document->limits;
    parser.cursor = (const u8 *)data;
    parser.end = parser.cursor + size;
    while (parser.cursor < parser.end && status == BREAK_XML_OK) {
        if (xml_starts(&parser, "<!--", 4u))
            status = xml_parse_comment(&parser);
        else if (xml_starts(&parser, "<?", 2u))
            status = xml_parse_instruction(&parser);
        else if (xml_starts(&parser, "<!", 2u))
            status = BREAK_XML_INVALID;
        else if (xml_starts(&parser, "</", 2u))
            status = xml_parse_close(&parser);
        else if (*parser.cursor == '<')
            status = xml_parse_open(&parser);
        else
            status = xml_parse_text(&parser);
    }
    if (status == BREAK_XML_OK && (next->root == BREAK_XML_NONE || next->current != BREAK_XML_NONE))
        status = BREAK_XML_INVALID;
    if (status != BREAK_XML_OK) return status;
    document->scratch = document->active;
    document->active = next;
    return BREAK_XML_OK;
}

static const BreakXmlNode *xml_node(const BreakXmlDocument *document, u32 index) {
    if (!document || index >= document->active->node_count) return NULL;
    return &document->active->nodes[index];
}

u32 break_xml_root(const BreakXmlDocument *document) {
    return document ? document->active->root : BREAK_XML_NONE;
}

BreakXmlNodeKind break_xml_kind(const BreakXmlDocument *document, u32 node) {
    const BreakXmlNode *value = xml_node(document, node);
    return value ? value->kind : (BreakXmlNodeKind)0;
}

const char *break_xml_name(const BreakXmlDocument *document, u32 node) {
    const BreakXmlNode *value = xml_node(document, node);
    if (!value || value->kind != BREAK_XML_ELEMENT) return NULL;
    return document->active->text + value->name;
}

const char *break_xml_text(const BreakXmlDocument *document, u32 node) {
    const BreakXmlNode *value = xml_node(document, node);
    if (!value || value->kind != BREAK_XML_TEXT) return NULL;
    return document->active->text + value->text;
}

u32 break_xml_first_child(const BreakXmlDocument *document, u32 node) {
    const BreakXmlNode *value = xml_node(document, node);
    return value ? value->first_child : BREAK_XML_NONE;
}

u32 break_xml_next_sibling(const BreakXmlDocument *document, u32 node) {
    const BreakXmlNode *value = xml_node(document, node);
    return value ? value->next_sibling : BREAK_XML_NONE;
}

u32 break_xml_attribute_count(const BreakXmlDocument *document, u32 node) {
    const BreakXmlNode *value = xml_node(document, node);
    return value && value->kind == BREAK_XML_ELEMENT ? value->attribute_count : 0u;
}

bool break_xml_attribute(const BreakXmlDocument *document, u32 node, u32 index,
                         const char **out_name, const char **out_value) {
    const BreakXmlNode *value = xml_node(document, node);
    const BreakXmlAttribute *attribute;
    if (!value || value->kind != BREAK_XML_ELEMENT || index >= value->attribute_count ||
        !out_name || !out_value) return false;
    attribute = &document->active->attributes[value->first_attribute + index];
    *out_name = document->active->text + attribute->name;
    *out_value = document->active->text + attribute->value;
    return true;
}

static void xml_write_bytes(BreakXmlWriter *writer, const char *data, usize length) {
    if (writer->status != BREAK_XML_OK) return;
    if (writer->size > writer->capacity || length > writer->capacity - writer->size) {
        writer->status = BREAK_XML_OVERLOAD;
        return;
    }
    if (length) memcpy(writer->out + writer->size, data, length);
    writer->size += length;
}

static void xml_write_string(BreakXmlWriter *writer, const char *text) {
    xml_write_bytes(writer, text, strlen(text));
}

static void xml_write_escaped(BreakXmlWriter *writer, const char *text) {
    while (*text && writer->status == BREAK_XML_OK) {
        switch (*text) {
        case '&': xml_write_string(writer, "&amp;"); break;
        case '<': xml_write_string(writer, "&lt;"); break;
        case '>': xml_write_string(writer, "&gt;"); break;
        case '"': xml_write_string(writer, "&quot;"); break;
        case '\'': xml_write_string(writer, "&apos;"); break;
        default: xml_write_bytes(writer, text, 1u); break;
        }
        text++;
    }
}

static void xml_serialize_tree(const BreakXmlDocument *document,
                               BreakXmlWriter *writer) {
    u32 current = document->active->root;
    while (current != BREAK_XML_NONE && writer->status == BREAK_XML_OK) {
        const BreakXmlNode *node = xml_node(document, current);
        if (!node) {
            writer->status = BREAK_XML_INVALID;
            return;
        }
        if (node->kind == BREAK_XML_TEXT) {
            xml_write_escaped(writer, document->active->text + node->text);
        } else if (node->kind == BREAK_XML_ELEMENT) {
            xml_write_string(writer, "<");
            xml_write_string(writer, document->active->text + node->name);
            for (u32 i = 0u; i < node->attribute_count; i++) {
                const BreakXmlAttribute *attribute =
                    &document->active->attributes[node->first_attribute + i];
                xml_write_string(writer, " ");
                xml_write_string(writer, document->active->text + attribute->name);
                xml_write_string(writer, "=\"");
                xml_write_escaped(writer, document->active->text + attribute->value);
                xml_write_string(writer, "\"");
            }
            if (node->first_child != BREAK_XML_NONE) {
                xml_write_string(writer, ">");
                current = node->first_child;
                continue;
            }
            xml_write_string(writer, "/>");
        } else {
            writer->status = BREAK_XML_INVALID;
            return;
        }
        for (;;) {
            u32 next = node->next_sibling;
            if (next != BREAK_XML_NONE) {
                current = next;
                break;
            }
            current = node->parent;
            if (current == BREAK_XML_NONE) break;
            node = xml_node(document, current);
            if (!node) {
                writer->status = BREAK_XML_INVALID;
                return;
            }
            xml_write_string(writer, "</");
            xml_write_string(writer, document->active->text + node->name);
            xml_write_string(writer, ">");
        }
    }
}

static BreakXmlStatus xml_writer_finish(BreakXmlWriter *writer, usize *out_size) {
    if (writer->status == BREAK_XML_OK) {
        if (writer->size == writer->capacity)
            writer->status = BREAK_XML_OVERLOAD;
        else
            writer->out[writer->size] = '\0';
    }
    if (writer->status != BREAK_XML_OK) {
        *out_size = 0u;
        return writer->status;
    }
    *out_size = writer->size;
    return BREAK_XML_OK;
}

BreakXmlStatus break_xml_serialize(const BreakXmlDocument *document,
                                   char *out, usize capacity, usize *out_size) {
    BreakXmlWriter writer;
    if (!out_size) return BREAK_XML_INVALID;
    *out_size = 0u;
    if (!document || !out || break_xml_root(document) == BREAK_XML_NONE)
        return BREAK_XML_INVALID;
    writer.out = out;
    writer.capacity = capacity;
    writer.size = 0u;
    writer.status = BREAK_XML_OK;
    xml_serialize_tree(document, &writer);
    return xml_writer_finish(&writer, out_size);
}

static bool xml_text_whitespace(const char *text) {
    while (*text) {
        if (!xml_space((u8)*text)) return false;
        text++;
    }
    return true;
}

static bool scene_u32(const char *text, u32 *out) {
    u32 value = 0u;
    if (!text[0]) return false;
    for (usize i = 0u; text[i]; i++) {
        u32 digit;
        if (text[i] < '0' || text[i] > '9') return false;
        digit = (u32)(text[i] - '0');
        if (value > (UINT32_MAX - digit) / 10u) return false;
        value = value * 10u + digit;
    }
    if (value == 0u) return false;
    *out = value;
    return true;
}

static bool scene_class_valid(const char *name) {
    usize length = strlen(name);
    if (length == 0u || length >= BREAK_SCENE_XML_CLASS_CAPACITY) return false;
    if (!((name[0] >= 'A' && name[0] <= 'Z') ||
          (name[0] >= 'a' && name[0] <= 'z') || name[0] == '_')) return false;
    for (usize i = 1u; i < length; i++) {
        char c = name[i];
        if (!((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') ||
              (c >= '0' && c <= '9') || c == '_' || c == '.' || c == '-')) return false;
    }
    return true;
}

static bool scene_entity_valid(const BreakXmlDocument *document, u32 index,
                               BreakSceneXmlEntity *out) {
    bool seen_index = false;
    bool seen_generation = false;
    bool seen_class = false;
    BreakSceneXmlEntity value;
    memset(&value, 0, sizeof(value));
    if (break_xml_kind(document, index) != BREAK_XML_ELEMENT ||
        strcmp(break_xml_name(document, index), "entity") != 0 ||
        break_xml_attribute_count(document, index) != 3u) return false;
    for (u32 i = 0u; i < 3u; i++) {
        const char *name;
        const char *text;
        if (!break_xml_attribute(document, index, i, &name, &text)) return false;
        if (strcmp(name, "index") == 0 && !seen_index) {
            seen_index = scene_u32(text, &value.index);
            if (!seen_index) return false;
        } else if (strcmp(name, "generation") == 0 && !seen_generation) {
            seen_generation = scene_u32(text, &value.generation);
            if (!seen_generation) return false;
        } else if (strcmp(name, "class") == 0 && !seen_class && scene_class_valid(text)) {
            seen_class = true;
            memcpy(value.class_name, text, strlen(text) + 1u);
        } else {
            return false;
        }
    }
    if (!seen_index || !seen_generation || !seen_class) return false;
    for (u32 child = break_xml_first_child(document, index); child != BREAK_XML_NONE;
         child = break_xml_next_sibling(document, child)) {
        if (break_xml_kind(document, child) != BREAK_XML_TEXT ||
            !xml_text_whitespace(break_xml_text(document, child))) return false;
    }
    *out = value;
    return true;
}

static bool scene_root_valid(const BreakXmlDocument *document, u32 root) {
    const char *name;
    const char *value;
    return break_xml_kind(document, root) == BREAK_XML_ELEMENT &&
           strcmp(break_xml_name(document, root), "break-scene") == 0 &&
           break_xml_attribute_count(document, root) == 1u &&
           break_xml_attribute(document, root, 0u, &name, &value) &&
           strcmp(name, "version") == 0 && strcmp(value, "1") == 0;
}

BreakXmlStatus break_scene_xml_read(const BreakXmlDocument *document,
                                    BreakSceneXmlEntity *out, u32 capacity,
                                    u32 *out_count) {
    u32 root;
    u32 count = 0u;
    if (!out_count) return BREAK_XML_INVALID;
    *out_count = 0u;
    if (!document || (capacity > 0u && !out)) return BREAK_XML_INVALID;
    root = break_xml_root(document);
    if (root == BREAK_XML_NONE || !scene_root_valid(document, root)) return BREAK_XML_INVALID;
    for (u32 child = break_xml_first_child(document, root); child != BREAK_XML_NONE;
         child = break_xml_next_sibling(document, child)) {
        BreakSceneXmlEntity current;
        if (break_xml_kind(document, child) == BREAK_XML_TEXT) {
            if (!xml_text_whitespace(break_xml_text(document, child))) return BREAK_XML_INVALID;
            continue;
        }
        if (!scene_entity_valid(document, child, &current)) return BREAK_XML_INVALID;
        for (u32 previous = break_xml_first_child(document, root); previous != child;
             previous = break_xml_next_sibling(document, previous)) {
            BreakSceneXmlEntity prior;
            if (break_xml_kind(document, previous) == BREAK_XML_TEXT) continue;
            if (!scene_entity_valid(document, previous, &prior)) return BREAK_XML_INVALID;
            if (prior.index == current.index && prior.generation == current.generation)
                return BREAK_XML_INVALID;
        }
        count++;
    }
    *out_count = count;
    if (count > capacity) return BREAK_XML_OVERLOAD;
    {
        u32 output_index = 0u;
        for (u32 child = break_xml_first_child(document, root); child != BREAK_XML_NONE;
             child = break_xml_next_sibling(document, child)) {
            if (break_xml_kind(document, child) == BREAK_XML_TEXT) continue;
            if (!scene_entity_valid(document, child, &out[output_index])) return BREAK_XML_INVALID;
            output_index++;
        }
    }
    return BREAK_XML_OK;
}

BreakXmlStatus break_scene_xml_write(const BreakSceneXmlEntity *entities,
                                     u32 count, char *out, usize capacity,
                                     usize *out_size) {
    BreakXmlWriter writer;
    if (!out_size) return BREAK_XML_INVALID;
    *out_size = 0u;
    if (!out || (count > 0u && !entities)) return BREAK_XML_INVALID;
    if (count > BREAK_SCENE_XML_HARD_MAX_ENTITIES) return BREAK_XML_OVERLOAD;
    for (u32 i = 0u; i < count; i++) {
        if (entities[i].index == 0u || entities[i].generation == 0u ||
            !scene_class_valid(entities[i].class_name)) return BREAK_XML_INVALID;
        for (u32 j = 0u; j < i; j++)
            if (entities[i].index == entities[j].index &&
                entities[i].generation == entities[j].generation) return BREAK_XML_INVALID;
    }
    writer.out = out;
    writer.capacity = capacity;
    writer.size = 0u;
    writer.status = BREAK_XML_OK;
    xml_write_string(&writer, "<break-scene version=\"1\">");
    for (u32 i = 0u; i < count; i++) {
        char index[16];
        char generation[16];
        int index_length = snprintf(index, sizeof(index), "%u", entities[i].index);
        int generation_length = snprintf(generation, sizeof(generation), "%u",
                                         entities[i].generation);
        if (index_length < 0 || generation_length < 0) return BREAK_XML_FAILED;
        xml_write_string(&writer, "<entity index=\"");
        xml_write_bytes(&writer, index, (usize)index_length);
        xml_write_string(&writer, "\" generation=\"");
        xml_write_bytes(&writer, generation, (usize)generation_length);
        xml_write_string(&writer, "\" class=\"");
        xml_write_string(&writer, entities[i].class_name);
        xml_write_string(&writer, "\"/>");
    }
    xml_write_string(&writer, "</break-scene>");
    return xml_writer_finish(&writer, out_size);
}
