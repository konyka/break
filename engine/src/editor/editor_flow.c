#include <editor/editor_flow.h>

#include <editor/editor_internal.h>
#include <editor/editor_test_hooks.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FLOW_COMMAND_BYTES 45104u

typedef struct {
    BreakEditorCmd base;
    usize before_len;
    usize after_len;
    u32 result_id;
    u8 before[FLOW_COMMAND_BYTES];
    u8 after[FLOW_COMMAND_BYTES];
} BreakEditorFlowCmd;

typedef enum {
    FLOW_EDIT_ADD_NODE = 1,
    FLOW_EDIT_REMOVE_NODE,
    FLOW_EDIT_SET_NODE,
    FLOW_EDIT_CONNECT,
    FLOW_EDIT_DISCONNECT
} FlowEditKind;

typedef struct {
    FlowEditKind kind;
    u32 id;
    BreakFlowNodeDesc node;
    BreakFlowLinkDesc link;
} FlowEdit;

static BreakFlowError replace_graph(BreakEditorDoc *doc, const u8 *bytes, usize len) {
    BreakFlowGraph *fresh = NULL;
    BreakFlowError err = break_flow_deserialize(bytes, len, &fresh);
    if (err != BREAK_FLOW_OK) return err;
    BreakFlowGraph *old = doc->flow_graph;
    doc->flow_graph = fresh;
    break_flow_graph_destroy(old);
    return BREAK_FLOW_OK;
}

static bool flow_apply_after(BreakEditorCmd *self, BreakEditorDoc *doc) {
    BreakEditorFlowCmd *cmd = (BreakEditorFlowCmd *)self;
    return replace_graph(doc, cmd->after, cmd->after_len) == BREAK_FLOW_OK;
}

static bool flow_apply_before(BreakEditorCmd *self, BreakEditorDoc *doc) {
    BreakEditorFlowCmd *cmd = (BreakEditorFlowCmd *)self;
    return replace_graph(doc, cmd->before, cmd->before_len) == BREAK_FLOW_OK;
}

static void flow_destroy(BreakEditorCmd *self) {
    free(self);
}

static void flow_describe(const BreakEditorCmd *self, char buf[128]) {
    snprintf(buf, 128, "flow: %.100s", self->name);
}

static BreakFlowError mutate_clone(BreakFlowGraph *graph, FlowEdit *edit,
                                   u32 *out_id) {
    switch (edit->kind) {
        case FLOW_EDIT_ADD_NODE:
            return break_flow_node_add(graph, &edit->node, out_id);
        case FLOW_EDIT_REMOVE_NODE:
            return break_flow_node_remove(graph, edit->id);
        case FLOW_EDIT_SET_NODE:
            return break_flow_node_set(graph, edit->id, &edit->node);
        case FLOW_EDIT_CONNECT:
            return break_flow_link_add(graph, &edit->link, out_id);
        case FLOW_EDIT_DISCONNECT:
            return break_flow_link_remove(graph, edit->id);
        default:
            return BREAK_FLOW_INVALID;
    }
}

static BreakFlowError flow_execute(BreakEditorDoc *doc, FlowEdit *edit,
                                   const char *label, u32 *out_id) {
    if (!doc || !doc->flow_graph || !edit) return BREAK_FLOW_INVALID;
    BreakEditorFlowCmd *cmd = break_editor_test_calloc(sizeof(*cmd));
    if (!cmd) return BREAK_FLOW_OOM;
    cmd->base.apply = flow_apply_after;
    cmd->base.revert = flow_apply_before;
    cmd->base.destroy = flow_destroy;
    cmd->base.describe = flow_describe;
    cmd->base.kind = BREAK_EDITOR_CMD_KIND_FLOW_GRAPH;
    break_editor_name_copy(cmd->base.name, label);
    BreakFlowError err = break_flow_serialize(doc->flow_graph, cmd->before,
                                              sizeof(cmd->before), &cmd->before_len);
    if (err != BREAK_FLOW_OK) {
        flow_destroy(&cmd->base);
        return err;
    }
    BreakFlowGraph *clone = NULL;
    err = break_flow_deserialize(cmd->before, cmd->before_len, &clone);
    if (err != BREAK_FLOW_OK) {
        flow_destroy(&cmd->base);
        return err;
    }
    u32 result_id = 0u;
    err = mutate_clone(clone, edit, &result_id);
    if (err == BREAK_FLOW_OK) {
        err = break_flow_serialize(clone, cmd->after, sizeof(cmd->after),
                                   &cmd->after_len);
    }
    break_flow_graph_destroy(clone);
    if (err != BREAK_FLOW_OK) {
        flow_destroy(&cmd->base);
        return err;
    }
    cmd->result_id = result_id;
    if (!flow_apply_after(&cmd->base, doc)) {
        flow_destroy(&cmd->base);
        return BREAK_FLOW_OOM;
    }
    break_editor_cmd_stack_push_applied(doc, &cmd->base);
    doc->dirty = true;
    if (out_id) *out_id = result_id;
    return BREAK_FLOW_OK;
}

BreakFlowGraph *break_editor_doc_flow_graph(BreakEditorDoc *doc) {
    return doc ? doc->flow_graph : NULL;
}

BreakFlowError break_editor_flow_add_node(BreakEditorDoc *doc,
                                          const BreakFlowNodeDesc *desc,
                                          u32 *out_id) {
    if (!desc) return BREAK_FLOW_INVALID;
    FlowEdit edit;
    memset(&edit, 0, sizeof(edit));
    edit.kind = FLOW_EDIT_ADD_NODE;
    edit.node = *desc;
    return flow_execute(doc, &edit, "add node", out_id);
}

BreakFlowError break_editor_flow_remove_node(BreakEditorDoc *doc, u32 node_id) {
    FlowEdit edit;
    memset(&edit, 0, sizeof(edit));
    edit.kind = FLOW_EDIT_REMOVE_NODE;
    edit.id = node_id;
    return flow_execute(doc, &edit, "remove node", NULL);
}

BreakFlowError break_editor_flow_set_node(BreakEditorDoc *doc, u32 node_id,
                                          const BreakFlowNodeDesc *desc) {
    if (!desc) return BREAK_FLOW_INVALID;
    FlowEdit edit;
    memset(&edit, 0, sizeof(edit));
    edit.kind = FLOW_EDIT_SET_NODE;
    edit.id = node_id;
    edit.node = *desc;
    return flow_execute(doc, &edit, "edit node", NULL);
}

BreakFlowError break_editor_flow_connect(BreakEditorDoc *doc,
                                         const BreakFlowLinkDesc *desc,
                                         u32 *out_id) {
    if (!desc) return BREAK_FLOW_INVALID;
    FlowEdit edit;
    memset(&edit, 0, sizeof(edit));
    edit.kind = FLOW_EDIT_CONNECT;
    edit.link = *desc;
    return flow_execute(doc, &edit, "connect ports", out_id);
}

BreakFlowError break_editor_flow_disconnect(BreakEditorDoc *doc, u32 link_id) {
    FlowEdit edit;
    memset(&edit, 0, sizeof(edit));
    edit.kind = FLOW_EDIT_DISCONNECT;
    edit.id = link_id;
    return flow_execute(doc, &edit, "disconnect ports", NULL);
}
