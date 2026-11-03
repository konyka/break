#pragma once

#include <editor/editor_doc.h>
#include <game/break_flow.h>

/* Borrowed graph. Any successful flow edit, undo/redo or reset replaces it;
 * callers must re-fetch instead of retaining the pointer across mutations. */
BreakFlowGraph *break_editor_doc_flow_graph(BreakEditorDoc *doc);

BreakFlowError break_editor_flow_add_node(BreakEditorDoc *doc,
                                          const BreakFlowNodeDesc *desc,
                                          u32 *out_id);
BreakFlowError break_editor_flow_remove_node(BreakEditorDoc *doc, u32 node_id);
BreakFlowError break_editor_flow_set_node(BreakEditorDoc *doc, u32 node_id,
                                          const BreakFlowNodeDesc *desc);
BreakFlowError break_editor_flow_connect(BreakEditorDoc *doc,
                                         const BreakFlowLinkDesc *desc,
                                         u32 *out_id);
BreakFlowError break_editor_flow_disconnect(BreakEditorDoc *doc, u32 link_id);
