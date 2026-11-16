#include <editor/editor_plugin_panels.h>

#include <stdlib.h>
#include <string.h>

typedef struct PluginPanel {
    u32 owner;
    char id[BREAK_EDITOR_PLUGIN_PANEL_ID_CAPACITY];
    char title[BREAK_EDITOR_PLUGIN_PANEL_TITLE_CAPACITY];
    /* "" when the language has no translation */
    char title_lang[BREAK_EDITOR_LANG_COUNT][BREAK_EDITOR_PLUGIN_PANEL_TITLE_CAPACITY];
    BreakEditorPluginPanelFn fn;
    void *user;
} PluginPanel;

struct BreakEditorPluginPanels {
    u32 capacity;
    u32 count;
    PluginPanel panels[];
};

BreakEditorPluginPanels *break_editor_plugin_panels_create(u32 capacity)
{
    if (capacity == 0u || capacity > BREAK_EDITOR_PLUGIN_PANELS_MAX) {
        return NULL;
    }
    BreakEditorPluginPanels *reg =
        calloc(1u, sizeof(*reg) + (usize)capacity * sizeof(PluginPanel));
    if (reg) {
        reg->capacity = capacity;
    }
    return reg;
}

void break_editor_plugin_panels_destroy(BreakEditorPluginPanels *reg)
{
    free(reg);
}

static bool valid_id(const char *id)
{
    if (!id) {
        return false;
    }
    usize n = strlen(id);
    if (n == 0u || n >= BREAK_EDITOR_PLUGIN_PANEL_ID_CAPACITY) {
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
    if (n == 0u || n >= BREAK_EDITOR_PLUGIN_PANEL_TITLE_CAPACITY) {
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

/* one unsigned compare also rejects negative values of a signed enum */
static bool lang_valid(BreakEditorLang lang)
{
    return (u32)lang < (u32)BREAK_EDITOR_LANG_COUNT;
}

BreakEditorPluginPanelStatus break_editor_plugin_panels_add(BreakEditorPluginPanels *reg,
                                                            u32 owner, const char *id,
                                                            const char *title,
                                                            BreakEditorPluginPanelFn fn,
                                                            void *user)
{
    if (!reg || owner == 0u || !fn) {
        return BREAK_EDITOR_PLUGIN_PANEL_INVALID;
    }
    if (!valid_id(id)) {
        return BREAK_EDITOR_PLUGIN_PANEL_BAD_ID;
    }
    if (!valid_title(title)) {
        return BREAK_EDITOR_PLUGIN_PANEL_BAD_TITLE;
    }
    if (break_editor_plugin_panels_find(reg, id) != BREAK_EDITOR_PLUGIN_PANEL_NONE) {
        return BREAK_EDITOR_PLUGIN_PANEL_DUPLICATE;
    }
    if (reg->count == reg->capacity) {
        return BREAK_EDITOR_PLUGIN_PANEL_FULL;
    }
    PluginPanel *panel = &reg->panels[reg->count];
    memset(panel, 0, sizeof(*panel));
    panel->owner = owner;
    memcpy(panel->id, id, strlen(id) + 1u);
    memcpy(panel->title, title, strlen(title) + 1u);
    panel->fn = fn;
    panel->user = user;
    reg->count++;
    return BREAK_EDITOR_PLUGIN_PANEL_OK;
}

BreakEditorPluginPanelStatus break_editor_plugin_panels_set_title(BreakEditorPluginPanels *reg,
                                                                  u32 owner, const char *id,
                                                                  BreakEditorLang lang,
                                                                  const char *title)
{
    if (!reg || owner == 0u) {
        return BREAK_EDITOR_PLUGIN_PANEL_INVALID;
    }
    if (!lang_valid(lang)) {
        return BREAK_EDITOR_PLUGIN_PANEL_BAD_LANG;
    }
    if (!valid_title(title)) {
        return BREAK_EDITOR_PLUGIN_PANEL_BAD_TITLE;
    }
    u32 index = break_editor_plugin_panels_find(reg, id);
    if (index == BREAK_EDITOR_PLUGIN_PANEL_NONE || reg->panels[index].owner != owner) {
        return BREAK_EDITOR_PLUGIN_PANEL_NOT_FOUND;
    }
    memcpy(reg->panels[index].title_lang[lang], title, strlen(title) + 1u);
    return BREAK_EDITOR_PLUGIN_PANEL_OK;
}

u32 break_editor_plugin_panels_remove_owner(BreakEditorPluginPanels *reg, u32 owner)
{
    if (!reg) {
        return 0u;
    }
    u32 kept = 0u;
    for (u32 i = 0; i < reg->count; i++) {
        if (reg->panels[i].owner != owner) {
            if (kept != i) {
                reg->panels[kept] = reg->panels[i];
            }
            kept++;
        }
    }
    u32 removed = reg->count - kept;
    reg->count = kept;
    return removed;
}

u32 break_editor_plugin_panels_count(const BreakEditorPluginPanels *reg)
{
    return reg ? reg->count : 0u;
}

const char *break_editor_plugin_panels_id(const BreakEditorPluginPanels *reg, u32 index)
{
    return (reg && index < reg->count) ? reg->panels[index].id : NULL;
}

const char *break_editor_plugin_panels_title(const BreakEditorPluginPanels *reg, u32 index,
                                             BreakEditorLang lang)
{
    if (!reg || index >= reg->count) {
        return NULL;
    }
    const PluginPanel *panel = &reg->panels[index];
    if (lang_valid(lang) && panel->title_lang[lang][0] != '\0') {
        return panel->title_lang[lang];
    }
    return panel->title;
}

u32 break_editor_plugin_panels_owner(const BreakEditorPluginPanels *reg, u32 index)
{
    return (reg && index < reg->count) ? reg->panels[index].owner : 0u;
}

u32 break_editor_plugin_panels_find(const BreakEditorPluginPanels *reg, const char *id)
{
    if (!reg || !id) {
        return BREAK_EDITOR_PLUGIN_PANEL_NONE;
    }
    for (u32 i = 0; i < reg->count; i++) {
        if (strcmp(reg->panels[i].id, id) == 0) {
            return i;
        }
    }
    return BREAK_EDITOR_PLUGIN_PANEL_NONE;
}

bool break_editor_plugin_panels_render(const BreakEditorPluginPanels *reg, u32 index,
                                       const BreakEditorDoc *doc, char *out, usize cap)
{
    if (!out || cap == 0u) {
        return false;
    }
    out[0] = '\0';
    if (!reg || index >= reg->count) {
        return false;
    }
    const PluginPanel *panel = &reg->panels[index];
    bool shown = panel->fn(panel->user, doc, out, cap);
    out[cap - 1u] = '\0';
    if (!shown) {
        out[0] = '\0';
    }
    return shown;
}
