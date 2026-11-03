#include "editor_shell_internal.h"

#include <editor/editor_cmd.h>
#include <editor/editor_flow.h>
#include <editor/editor_i18n.h>

#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "myui/my_layout.h"
#include "myui/widgets/my_button.h"
#include "myui/widgets/my_edit.h"
#include "myui/widgets/my_list_view.h"

#define FLOW_ROW_CAP BREAK_FLOW_HARD_MAX_NODES
#define FLOW_ROW_TEXT 96u
#define FLOW_ROW_CONTEXT_CAP 32u

typedef struct EditorPanelFlow EditorPanelFlow;

typedef struct {
    my_list_adapter_t base;
    EditorPanelFlow *panel;
} FlowAdapter;

typedef struct {
    EditorPanelFlow *panel;
    my_widget_t *row;
    usize index;
} FlowRowContext;

struct EditorPanelFlow {
    BreakEditorShell *shell;
    my_widget_t *list;
    my_widget_t *name;
    my_widget_t *key;
    my_widget_t *delay;
    my_widget_t *a;
    my_widget_t *b;
    my_widget_t *c;
    my_widget_t *entity;
    my_widget_t *source_node;
    my_widget_t *source_port;
    my_widget_t *target_node;
    my_widget_t *target_port;
    my_widget_t *kind;
    my_widget_t *disconnect_id;
    FlowAdapter adapter;
    FlowRowContext contexts[FLOW_ROW_CONTEXT_CAP];
    u32 context_count;
    u32 selected_id;
    u32 row_count;
    u32 row_ids[FLOW_ROW_CAP];
    char rows[FLOW_ROW_CAP][FLOW_ROW_TEXT];
    u64 observed_revision;
    BreakFlowGraph *observed_graph;
};

static const char *flow_type_name(BreakFlowNodeType type) {
    static const char *const names[] = {
        "event", "add", "subtract", "multiply", "divide", "less", "equal",
        "greater", "set_position", "add_item", "delay", "sequence", "branch"};
    return type >= BREAK_FLOW_NODE_EVENT && type <= BREAK_FLOW_NODE_BRANCH
               ? names[(u32)type - 1u] : "invalid";
}

static bool parse_u32(const char *text, u32 *out) {
    if (!text || !*text || !out) return false;
    for (const char *p = text; *p; p++) {
        if (*p < '0' || *p > '9') return false;
    }
    errno = 0;
    char *end = NULL;
    unsigned long value = strtoul(text, &end, 10);
    if (errno == ERANGE || !end || *end != '\0' || value > UINT32_MAX) return false;
    *out = (u32)value;
    return true;
}

static bool parse_f32(const char *text, f32 *out) {
    if (!text || !*text || !out) return false;
    errno = 0;
    char *end = NULL;
    f32 value = strtof(text, &end);
    if (errno == ERANGE || !end || *end != '\0' || !isfinite(value)) return false;
    *out = value;
    return true;
}

static bool parse_entity(const char *text, Entity *out) {
    const char *colon = text ? strchr(text, ':') : NULL;
    if (!colon || colon == text || !colon[1] || strchr(colon + 1, ':')) return false;
    usize n = (usize)(colon - text);
    if (n >= 32u) return false;
    char left[32];
    memcpy(left, text, n);
    left[n] = '\0';
    u32 index = 0u;
    u32 generation = 0u;
    if (!parse_u32(left, &index) || !parse_u32(colon + 1, &generation) ||
        index == 0u || index >= ECS_MAX_ENTITIES || generation == 0u) return false;
    out->index = index;
    out->generation = generation;
    return true;
}

static BreakFlowGraph *flow_graph(EditorPanelFlow *panel) {
    return break_editor_doc_flow_graph(break_editor_shell_doc(panel->shell));
}

static void set_edit(my_widget_t *edit, const char *text) {
    if (edit) (void)my_edit_set_text(edit, text);
}

static void flow_refresh(EditorPanelFlow *panel, bool force) {
    if (!panel || !panel->shell) return;
    BreakEditorDoc *doc = break_editor_shell_doc(panel->shell);
    u64 revision = break_editor_cmd_stack_revision(break_editor_doc_stack(doc));
    BreakFlowGraph *graph = break_editor_doc_flow_graph(doc);
    if (!force && revision == panel->observed_revision &&
        graph == panel->observed_graph) return;
    panel->observed_revision = revision;
    panel->observed_graph = graph;
    panel->row_count = graph ? break_flow_graph_node_count(graph) : 0u;
    if (panel->row_count > FLOW_ROW_CAP) panel->row_count = FLOW_ROW_CAP;
    bool selected_live = false;
    for (u32 i = 0u; i < panel->row_count; i++) {
        BreakFlowNodeDesc d;
        if (break_flow_node_at(graph, i, &panel->row_ids[i], &d) != BREAK_FLOW_OK) {
            panel->row_count = i;
            break;
        }
        snprintf(panel->rows[i], sizeof(panel->rows[i]), "#%u %s %s",
                 panel->row_ids[i], flow_type_name(d.type), d.name);
        if (panel->row_ids[i] == panel->selected_id) selected_live = true;
    }
    if (!selected_live) panel->selected_id = 0u;
    if (panel->list) (void)my_list_view_refresh(panel->list);
    BreakFlowNodeDesc d;
    memset(&d, 0, sizeof(d));
    if (panel->selected_id && graph &&
        break_flow_node_get(graph, panel->selected_id, &d) != BREAK_FLOW_OK) {
        panel->selected_id = 0u;
    }
    char text[96];
    set_edit(panel->name, d.name);
    if (d.type == BREAK_FLOW_NODE_EVENT) snprintf(text, sizeof(text), "%u", d.event_key);
    else if (d.type == BREAK_FLOW_NODE_ENTITY_ADD_ITEM) snprintf(text, sizeof(text), "%u", d.item_id);
    else snprintf(text, sizeof(text), "0");
    set_edit(panel->key, text);
    snprintf(text, sizeof(text), "%u", d.delay_ticks);
    set_edit(panel->delay, text);
    snprintf(text, sizeof(text), "%.9g", (double)d.a);
    set_edit(panel->a, text);
    snprintf(text, sizeof(text), "%.9g", (double)d.b);
    set_edit(panel->b, text);
    snprintf(text, sizeof(text), "%.9g", (double)d.c);
    set_edit(panel->c, text);
    snprintf(text, sizeof(text), "%u:%u", d.entity.index, d.entity.generation);
    set_edit(panel->entity, text);
}

static void flow_result(EditorPanelFlow *panel, BreakFlowError error) {
    if (error != BREAK_FLOW_OK) {
        editor_shell_log(panel->shell, "flow| edit rejected (%d)", (int)error);
        return;
    }
    flow_refresh(panel, true);
    editor_shell_refresh_all(panel->shell);
}

static void flow_add(EditorPanelFlow *panel, BreakFlowNodeType type) {
    BreakFlowNodeDesc d;
    memset(&d, 0, sizeof(d));
    d.type = type;
    if (type == BREAK_FLOW_NODE_EVENT) {
        BreakFlowGraph *graph = flow_graph(panel);
        u32 key = 1u;
        bool used = true;
        while (used && key != UINT32_MAX) {
            used = false;
            for (u32 i = 0u; i < break_flow_graph_node_count(graph); i++) {
                BreakFlowNodeDesc other;
                u32 id = 0u;
                if (break_flow_node_at(graph, i, &id, &other) != BREAK_FLOW_OK) break;
                if (other.type == BREAK_FLOW_NODE_EVENT && other.event_key == key) used = true;
            }
            if (used) key++;
        }
        d.event_key = key;
    }
    u32 id = 0u;
    BreakFlowError error = break_editor_flow_add_node(
        break_editor_shell_doc(panel->shell), &d, &id);
    if (error == BREAK_FLOW_OK) panel->selected_id = id;
    flow_result(panel, error);
}

static void on_add_event(void *ctx, const char *event, void *data) {
    (void)event; (void)data; flow_add((EditorPanelFlow *)ctx, BREAK_FLOW_NODE_EVENT);
}

static void on_add_sequence(void *ctx, const char *event, void *data) {
    (void)event; (void)data; flow_add((EditorPanelFlow *)ctx, BREAK_FLOW_NODE_SEQUENCE);
}

static void on_delete(void *ctx, const char *event, void *data) {
    EditorPanelFlow *panel = (EditorPanelFlow *)ctx;
    (void)event; (void)data;
    if (!panel->selected_id) return;
    BreakFlowError error = break_editor_flow_remove_node(
        break_editor_shell_doc(panel->shell), panel->selected_id);
    if (error == BREAK_FLOW_OK) panel->selected_id = 0u;
    flow_result(panel, error);
}

static void on_property(void *ctx, const char *event, void *data) {
    (void)ctx;
    (void)event;
    (void)data;
}

static void on_name(void *ctx, const char *event, void *data) {
    EditorPanelFlow *panel = (EditorPanelFlow *)ctx;
    const char *text = (const char *)data;
    (void)event;
    if (!panel->selected_id || !text) return;
    BreakFlowNodeDesc d;
    if (break_flow_node_get(flow_graph(panel), panel->selected_id, &d) != BREAK_FLOW_OK) return;
    usize len = strlen(text);
    if (len >= sizeof(d.name)) return;
    memcpy(d.name, text, len + 1u);
    flow_result(panel, break_editor_flow_set_node(
        break_editor_shell_doc(panel->shell), panel->selected_id, &d));
}

static void on_key(void *ctx, const char *event, void *data) {
    EditorPanelFlow *panel = (EditorPanelFlow *)ctx;
    (void)event;
    u32 value = 0u;
    if (!panel->selected_id || !parse_u32((const char *)data, &value)) return;
    BreakFlowNodeDesc d;
    if (break_flow_node_get(flow_graph(panel), panel->selected_id, &d) != BREAK_FLOW_OK) return;
    if (d.type == BREAK_FLOW_NODE_EVENT) d.event_key = value;
    else if (d.type == BREAK_FLOW_NODE_ENTITY_ADD_ITEM) d.item_id = value;
    else return;
    flow_result(panel, break_editor_flow_set_node(
        break_editor_shell_doc(panel->shell), panel->selected_id, &d));
}

static void on_delay(void *ctx, const char *event, void *data) {
    EditorPanelFlow *panel = (EditorPanelFlow *)ctx;
    (void)event;
    u32 value = 0u;
    if (!panel->selected_id || !parse_u32((const char *)data, &value)) return;
    BreakFlowNodeDesc d;
    if (break_flow_node_get(flow_graph(panel), panel->selected_id, &d) != BREAK_FLOW_OK) return;
    d.delay_ticks = value;
    flow_result(panel, break_editor_flow_set_node(
        break_editor_shell_doc(panel->shell), panel->selected_id, &d));
}

static void on_a(void *ctx, const char *event, void *data) {
    EditorPanelFlow *panel = (EditorPanelFlow *)ctx;
    f32 value = 0.0f;
    (void)event;
    if (!panel->selected_id || !parse_f32((const char *)data, &value)) return;
    BreakFlowNodeDesc d;
    if (break_flow_node_get(flow_graph(panel), panel->selected_id, &d) != BREAK_FLOW_OK) return;
    d.a = value;
    flow_result(panel, break_editor_flow_set_node(break_editor_shell_doc(panel->shell), panel->selected_id, &d));
}

static void on_b(void *ctx, const char *event, void *data) {
    EditorPanelFlow *panel = (EditorPanelFlow *)ctx;
    f32 value = 0.0f;
    (void)event;
    if (!panel->selected_id || !parse_f32((const char *)data, &value)) return;
    BreakFlowNodeDesc d;
    if (break_flow_node_get(flow_graph(panel), panel->selected_id, &d) != BREAK_FLOW_OK) return;
    d.b = value;
    flow_result(panel, break_editor_flow_set_node(break_editor_shell_doc(panel->shell), panel->selected_id, &d));
}

static void on_c(void *ctx, const char *event, void *data) {
    EditorPanelFlow *panel = (EditorPanelFlow *)ctx;
    f32 value = 0.0f;
    (void)event;
    if (!panel->selected_id || !parse_f32((const char *)data, &value)) return;
    BreakFlowNodeDesc d;
    if (break_flow_node_get(flow_graph(panel), panel->selected_id, &d) != BREAK_FLOW_OK) return;
    d.c = value;
    flow_result(panel, break_editor_flow_set_node(break_editor_shell_doc(panel->shell), panel->selected_id, &d));
}

static void on_entity(void *ctx, const char *event, void *data) {
    EditorPanelFlow *panel = (EditorPanelFlow *)ctx;
    Entity entity = ENTITY_NULL;
    (void)event;
    if (!panel->selected_id || !parse_entity((const char *)data, &entity)) return;
    BreakFlowNodeDesc d;
    if (break_flow_node_get(flow_graph(panel), panel->selected_id, &d) != BREAK_FLOW_OK ||
        (d.type != BREAK_FLOW_NODE_ENTITY_SET_POSITION && d.type != BREAK_FLOW_NODE_ENTITY_ADD_ITEM)) return;
    d.entity = entity;
    flow_result(panel, break_editor_flow_set_node(break_editor_shell_doc(panel->shell), panel->selected_id, &d));
}

static void on_connect(void *ctx, const char *event, void *data) {
    EditorPanelFlow *panel = (EditorPanelFlow *)ctx;
    (void)event; (void)data;
    BreakFlowLinkDesc d;
    memset(&d, 0, sizeof(d));
    u32 kind = 0u;
    if (!parse_u32(my_edit_get_text(panel->source_node), &d.source_node) ||
        !parse_u32(my_edit_get_text(panel->source_port), &d.source_port) ||
        !parse_u32(my_edit_get_text(panel->target_node), &d.target_node) ||
        !parse_u32(my_edit_get_text(panel->target_port), &d.target_port) ||
        !parse_u32(my_edit_get_text(panel->kind), &kind) ||
        (kind != BREAK_FLOW_PORT_EXEC && kind != BREAK_FLOW_PORT_VALUE)) return;
    d.kind = (BreakFlowPortKind)kind;
    u32 id = 0u;
    flow_result(panel, break_editor_flow_connect(
        break_editor_shell_doc(panel->shell), &d, &id));
}

static void on_disconnect(void *ctx, const char *event, void *data) {
    EditorPanelFlow *panel = (EditorPanelFlow *)ctx;
    (void)event; (void)data;
    u32 id = 0u;
    if (!parse_u32(my_edit_get_text(panel->disconnect_id), &id)) return;
    flow_result(panel, break_editor_flow_disconnect(
        break_editor_shell_doc(panel->shell), id));
}

static void on_row(void *ctx, const char *event, void *data) {
    FlowRowContext *row = (FlowRowContext *)ctx;
    (void)event; (void)data;
    if (!row || !row->panel || row->index >= row->panel->row_count) return;
    row->panel->selected_id = row->panel->row_ids[row->index];
    flow_refresh(row->panel, true);
}

static usize flow_count(my_list_adapter_t *adapter) {
    return ((FlowAdapter *)adapter)->panel->row_count;
}

static my_widget_t *flow_create_row(my_list_adapter_t *adapter) {
    FlowAdapter *a = (FlowAdapter *)adapter;
    my_widget_t *row = my_button_create(NULL, "");
    if (!row) return NULL;
    (void)my_widget_set_name(row, "editor-flow-row");
    if (a->panel->context_count < FLOW_ROW_CONTEXT_CAP) {
        FlowRowContext *ctx = &a->panel->contexts[a->panel->context_count++];
        ctx->panel = a->panel;
        ctx->row = row;
        (void)my_widget_on(row, "click", on_row, ctx);
    }
    return row;
}

static void flow_bind_row(my_list_adapter_t *adapter, my_widget_t *row, usize index) {
    FlowAdapter *a = (FlowAdapter *)adapter;
    if (index < a->panel->row_count) (void)my_button_set_text(row, a->panel->rows[index]);
    for (u32 i = 0u; i < a->panel->context_count; i++) {
        if (a->panel->contexts[i].row == row) a->panel->contexts[i].index = index;
    }
}

static const my_list_adapter_vtable_t k_flow_adapter = {
    flow_count, flow_create_row, flow_bind_row, NULL};

static bool add_child(my_widget_t *parent, my_widget_t *child, const char *params) {
    if (!child) return false;
    (void)my_widget_set_layout_params(child, params);
    if (my_widget_add_child(parent, child) == MY_RET_OK) {
        my_widget_unref(child);
        return true;
    }
    my_widget_unref(child);
    return false;
}

static my_widget_t *add_container(my_widget_t *parent, const char *name,
                                  bool horizontal, const char *params) {
    my_widget_t *widget = my_widget_create(NULL, name);
    if (!widget) return NULL;
    (void)my_widget_set_layouter(widget, my_layouter_linear_create(NULL, horizontal, 1));
    if (!add_child(parent, widget, params)) return NULL;
    return widget;
}

static my_widget_t *add_edit(EditorPanelFlow *panel, my_widget_t *parent,
                             const char *name, const char *hint,
                             my_event_callback_t callback, const char *params) {
    my_widget_t *edit = my_edit_create(NULL);
    if (!edit) return NULL;
    (void)my_widget_set_name(edit, name);
    (void)my_edit_set_hint(edit, hint);
    (void)my_edit_set_max_len(edit, 63u);
    (void)my_widget_on(edit, "activate", callback, panel);
    if (!add_child(parent, edit, params)) return NULL;
    return edit;
}

static bool add_button(EditorPanelFlow *panel, my_widget_t *parent,
                       const char *name, const char *text,
                       my_event_callback_t callback, const char *params) {
    my_widget_t *button = my_button_create(NULL, text);
    if (!button) return false;
    (void)my_widget_set_name(button, name);
    (void)my_widget_on(button, "click", callback, panel);
    return add_child(parent, button, params);
}

EditorPanelFlow *editor_panel_flow_create(BreakEditorShell *shell) {
    if (!shell) return NULL;
    EditorPanelFlow *panel = (EditorPanelFlow *)calloc(1u, sizeof(*panel));
    if (!panel) return NULL;
    panel->shell = shell;
    panel->adapter.base.vtable = &k_flow_adapter;
    panel->adapter.panel = panel;
    return panel;
}

void editor_panel_flow_destroy(EditorPanelFlow *panel) {
    free(panel);
}

bool editor_panel_flow_build(EditorPanelFlow *panel, my_widget_t *parent) {
    if (!panel || !parent) return false;
    my_widget_t *section = my_widget_create(NULL, "editor-flow-panel");
    if (!section) return false;
    (void)my_widget_set_layouter(section, my_layouter_linear_create(NULL, true, 2));
    panel->list = my_list_view_create(NULL);
    if (!panel->list || my_list_view_set_adapter(panel->list, &panel->adapter.base) != MY_RET_OK ||
        !add_child(section, panel->list, "w:25% h:100%")) {
        my_widget_unref(section);
        return false;
    }
    my_widget_t *properties = add_container(section, "editor-flow-properties", false, "w:35% h:100%");
    my_widget_t *links = add_container(section, "editor-flow-links", false, "w:40% h:100%");
    if (!properties || !links) {
        my_widget_unref(section);
        return false;
    }
    my_widget_t *buttons = add_container(properties, "editor-flow-buttons", true, "w:100% h:24");
    if (!buttons ||
        !add_button(panel, buttons, "editor-flow-add-event", "Add Event", on_add_event, "w:1f h:100%") ||
        !add_button(panel, buttons, "editor-flow-add-sequence", "Add Sequence", on_add_sequence, "w:1f h:100%") ||
        !add_button(panel, buttons, "editor-flow-delete", "Delete", on_delete, "w:1f h:100%")) {
        my_widget_unref(section);
        return false;
    }
    panel->name = add_edit(panel, properties, "editor-flow-name", "name", on_name, "w:100% h:22");
    my_widget_t *key_row = add_container(properties, "editor-flow-key-row", true, "w:100% h:22");
    if (key_row) {
        panel->key = add_edit(panel, key_row, "editor-flow-key", "event key / item id", on_key, "w:1f h:100%");
        panel->delay = add_edit(panel, key_row, "editor-flow-delay", "delay ticks", on_delay, "w:1f h:100%");
    }
    my_widget_t *scalar_row = add_container(properties, "editor-flow-scalar-row", true, "w:100% h:22");
    if (scalar_row) {
        panel->a = add_edit(panel, scalar_row, "editor-flow-a", "a / x / count", on_a, "w:1f h:100%");
        panel->b = add_edit(panel, scalar_row, "editor-flow-b", "b / y", on_b, "w:1f h:100%");
        panel->c = add_edit(panel, scalar_row, "editor-flow-c", "c / z", on_c, "w:1f h:100%");
    }
    panel->entity = add_edit(panel, properties, "editor-flow-entity", "entity index:generation", on_entity, "w:100% h:22");
    my_widget_t *source_row = add_container(links, "editor-flow-source-row", true, "w:100% h:22");
    if (source_row) {
        panel->source_node = add_edit(panel, source_row, "editor-flow-source-node", "source node", on_property, "w:1f h:100%");
        panel->source_port = add_edit(panel, source_row, "editor-flow-source-port", "source port", on_property, "w:1f h:100%");
    }
    my_widget_t *target_row = add_container(links, "editor-flow-target-row", true, "w:100% h:22");
    if (target_row) {
        panel->target_node = add_edit(panel, target_row, "editor-flow-target-node", "target node", on_property, "w:1f h:100%");
        panel->target_port = add_edit(panel, target_row, "editor-flow-target-port", "target port", on_property, "w:1f h:100%");
    }
    my_widget_t *kind_row = add_container(links, "editor-flow-kind-row", true, "w:100% h:22");
    if (kind_row) {
        panel->kind = add_edit(panel, kind_row, "editor-flow-kind", "kind: 1 exec, 2 value", on_property, "w:1f h:100%");
        panel->disconnect_id = add_edit(panel, kind_row, "editor-flow-disconnect-id", "link id", on_property, "w:1f h:100%");
    }
    if (!panel->name || !panel->key || !panel->delay || !panel->a || !panel->b || !panel->c ||
        !panel->entity || !panel->source_node || !panel->source_port || !panel->target_node ||
        !panel->target_port || !panel->kind || !panel->disconnect_id ||
        !add_button(panel, links, "editor-flow-connect", "Connect", on_connect, "w:100% h:22") ||
        !add_button(panel, links, "editor-flow-disconnect", "Disconnect", on_disconnect, "w:100% h:22")) {
        my_widget_unref(section);
        return false;
    }
    if (my_widget_add_child(parent, section) == MY_RET_OK) {
        my_widget_unref(section);
        flow_refresh(panel, true);
        return true;
    }
    my_widget_unref(section);
    return false;
}

void editor_panel_flow_tick(EditorPanelFlow *panel) {
    if (panel) flow_refresh(panel, false);
}

usize editor_panel_flow_row_count(const EditorPanelFlow *panel) {
    return panel ? panel->row_count : 0u;
}

const char *editor_panel_flow_row_text(const EditorPanelFlow *panel, usize i) {
    return panel && i < panel->row_count ? panel->rows[i] : NULL;
}

void editor_panel_flow_retranslate(EditorPanelFlow *panel) {
    (void)panel;
}
