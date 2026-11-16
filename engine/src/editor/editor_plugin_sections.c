#include <editor/editor_plugin_sections.h>

#include <stdlib.h>
#include <string.h>

typedef struct PluginSection {
    u32 owner;
    char id[BREAK_EDITOR_PLUGIN_SECTION_ID_CAPACITY];
    char title[BREAK_EDITOR_PLUGIN_SECTION_TITLE_CAPACITY];
    /* "" when the language has no translation */
    char title_lang[BREAK_EDITOR_LANG_COUNT][BREAK_EDITOR_PLUGIN_SECTION_TITLE_CAPACITY];
    BreakEditorPluginSectionFn fn;
    void *user;
} PluginSection;

struct BreakEditorPluginSections {
    u32 capacity;
    u32 count;
    PluginSection sections[];
};

BreakEditorPluginSections *break_editor_plugin_sections_create(u32 capacity)
{
    if (capacity == 0u || capacity > BREAK_EDITOR_PLUGIN_SECTIONS_MAX) {
        return NULL;
    }
    BreakEditorPluginSections *reg =
        calloc(1u, sizeof(*reg) + (usize)capacity * sizeof(PluginSection));
    if (reg) {
        reg->capacity = capacity;
    }
    return reg;
}

void break_editor_plugin_sections_destroy(BreakEditorPluginSections *reg)
{
    free(reg);
}

static bool valid_id(const char *id)
{
    if (!id) {
        return false;
    }
    usize n = strlen(id);
    if (n == 0u || n >= BREAK_EDITOR_PLUGIN_SECTION_ID_CAPACITY) {
        return false;
    }
    for (usize i = 0; i < n; i++) {
        char c = id[i];
        if (!((c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_' || c == '.')) {
            return false;
        }
    }
    return true;
}

static bool valid_title(const char *title)
{
    if (!title) {
        return false;
    }
    usize n = strlen(title);
    if (n == 0u || n >= BREAK_EDITOR_PLUGIN_SECTION_TITLE_CAPACITY) {
        return false;
    }
    for (usize i = 0; i < n; i++) {
        unsigned char c = (unsigned char)title[i];
        if (c < 0x20u || c == 0x7fu) {
            return false;
        }
    }
    return true;
}

BreakEditorPluginSectionStatus break_editor_plugin_sections_add(BreakEditorPluginSections *reg,
                                                                u32 owner, const char *id,
                                                                const char *title,
                                                                BreakEditorPluginSectionFn fn,
                                                                void *user)
{
    if (!reg || owner == 0u || !fn) {
        return BREAK_EDITOR_PLUGIN_SECTION_INVALID;
    }
    if (!valid_id(id)) {
        return BREAK_EDITOR_PLUGIN_SECTION_BAD_ID;
    }
    if (!valid_title(title)) {
        return BREAK_EDITOR_PLUGIN_SECTION_BAD_TITLE;
    }
    if (break_editor_plugin_sections_find(reg, id) != BREAK_EDITOR_PLUGIN_SECTION_NONE) {
        return BREAK_EDITOR_PLUGIN_SECTION_DUPLICATE;
    }
    if (reg->count == reg->capacity) {
        return BREAK_EDITOR_PLUGIN_SECTION_FULL;
    }
    PluginSection *section = &reg->sections[reg->count];
    section->owner = owner;
    memcpy(section->id, id, strlen(id) + 1u);
    memcpy(section->title, title, strlen(title) + 1u);
    memset(section->title_lang, 0, sizeof(section->title_lang));
    section->fn = fn;
    section->user = user;
    reg->count++;
    return BREAK_EDITOR_PLUGIN_SECTION_OK;
}

u32 break_editor_plugin_sections_remove_owner(BreakEditorPluginSections *reg, u32 owner)
{
    if (!reg) {
        return 0u;
    }
    u32 kept = 0u;
    for (u32 i = 0; i < reg->count; i++) {
        if (reg->sections[i].owner != owner) {
            if (kept != i) {
                reg->sections[kept] = reg->sections[i];
            }
            kept++;
        }
    }
    u32 removed = reg->count - kept;
    reg->count = kept;
    return removed;
}

u32 break_editor_plugin_sections_count(const BreakEditorPluginSections *reg)
{
    return reg ? reg->count : 0u;
}

const char *break_editor_plugin_sections_id(const BreakEditorPluginSections *reg, u32 index)
{
    return (reg && index < reg->count) ? reg->sections[index].id : NULL;
}

const char *break_editor_plugin_sections_title(const BreakEditorPluginSections *reg, u32 index)
{
    return (reg && index < reg->count) ? reg->sections[index].title : NULL;
}

u32 break_editor_plugin_sections_owner(const BreakEditorPluginSections *reg, u32 index)
{
    return (reg && index < reg->count) ? reg->sections[index].owner : 0u;
}

static bool lang_valid(BreakEditorLang lang)
{
    /* one unsigned compare also rejects negative values of a signed enum */
    return (u32)lang < (u32)BREAK_EDITOR_LANG_COUNT;
}

BreakEditorPluginSectionStatus break_editor_plugin_sections_set_title(
    BreakEditorPluginSections *reg, u32 owner, const char *id, BreakEditorLang lang,
    const char *title)
{
    if (!reg || owner == 0u) {
        return BREAK_EDITOR_PLUGIN_SECTION_INVALID;
    }
    if (!lang_valid(lang)) {
        return BREAK_EDITOR_PLUGIN_SECTION_BAD_LANG;
    }
    if (!valid_title(title)) {
        return BREAK_EDITOR_PLUGIN_SECTION_BAD_TITLE;
    }
    u32 index = break_editor_plugin_sections_find(reg, id);
    if (index == BREAK_EDITOR_PLUGIN_SECTION_NONE || reg->sections[index].owner != owner) {
        return BREAK_EDITOR_PLUGIN_SECTION_NOT_FOUND;
    }
    memcpy(reg->sections[index].title_lang[lang], title, strlen(title) + 1u);
    return BREAK_EDITOR_PLUGIN_SECTION_OK;
}

const char *break_editor_plugin_sections_title_lang(const BreakEditorPluginSections *reg,
                                                    u32 index, BreakEditorLang lang)
{
    if (!reg || index >= reg->count) {
        return NULL;
    }
    const PluginSection *section = &reg->sections[index];
    if (lang_valid(lang) && section->title_lang[lang][0] != '\0') {
        return section->title_lang[lang];
    }
    return section->title;
}

u32 break_editor_plugin_sections_find(const BreakEditorPluginSections *reg, const char *id)
{
    if (!reg || !id) {
        return BREAK_EDITOR_PLUGIN_SECTION_NONE;
    }
    for (u32 i = 0; i < reg->count; i++) {
        if (strcmp(reg->sections[i].id, id) == 0) {
            return i;
        }
    }
    return BREAK_EDITOR_PLUGIN_SECTION_NONE;
}

bool break_editor_plugin_sections_describe(const BreakEditorPluginSections *reg, u32 index,
                                           const BreakEditorDoc *doc,
                                           BreakEditorEntityId entity, char *out, usize cap)
{
    if (!out || cap == 0u) {
        return false;
    }
    out[0] = '\0';
    if (!reg || index >= reg->count) {
        return false;
    }
    const PluginSection *section = &reg->sections[index];
    bool shown = section->fn(section->user, doc, entity, out, cap);
    out[cap - 1u] = '\0';
    if (!shown) {
        out[0] = '\0';
    }
    return shown;
}
