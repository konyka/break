#include <game/break_flow_internal.h>
#include <core/platform_thread.h>

#include <math.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

typedef struct BreakFlowEvent {
    u32 target_node;
    u32 event_node;
    u64 due_tick;
    u64 sequence;
    Entity entity;
    f32 value;
    bool resume;
} BreakFlowEvent;

struct BreakFlowRuntime {
    BreakFlowGraph *graph;
    BreakGame *game;
    PlatformThreadId owner;
    u32 max_events;
    u32 max_actions;
    u32 node_budget;
    BreakFlowEvent *events;
    BreakFlowEvent *backup;
    u32 event_count;
    BreakGameEntityAction *actions;
    u32 action_count;
    u8 *eval_state;
    u64 next_sequence;
    u64 now_tick;
    u64 graph_revision;
};

static bool is_owner(const BreakFlowRuntime *runtime) {
    return runtime && platform_thread_id_equal(runtime->owner,
                                               platform_thread_current_id());
}

static BreakFlowError consume(BreakFlowRuntime *runtime, u32 *used) {
    if (*used >= runtime->node_budget) return BREAK_FLOW_TIMEOUT;
    (*used)++;
    return BREAK_FLOW_OK;
}

static BreakFlowError enqueue(BreakFlowRuntime *runtime, u32 target, bool resume,
                              u64 due_tick, const BreakFlowEvent *context) {
    if (runtime->event_count >= runtime->max_events ||
        runtime->next_sequence == 0u || runtime->next_sequence == UINT64_MAX) {
        return BREAK_FLOW_OVERLOAD;
    }
    BreakFlowEvent *event = &runtime->events[runtime->event_count++];
    event->target_node = target;
    event->event_node = context ? context->event_node : 0u;
    event->due_tick = due_tick;
    event->sequence = runtime->next_sequence++;
    event->entity = context ? context->entity : ENTITY_NULL;
    event->value = context ? context->value : 0.0f;
    event->resume = resume;
    return BREAK_FLOW_OK;
}

static BreakFlowError eval_node(BreakFlowRuntime *runtime, u32 id,
                                const BreakFlowEvent *context, u32 *used,
                                f32 *out_value);

static BreakFlowError eval_input(BreakFlowRuntime *runtime, u32 target, u32 port,
                                 f32 fallback, const BreakFlowEvent *context,
                                 u32 *used, f32 *out_value) {
    for (u32 i = 1u; i <= runtime->graph->max_links; i++) {
        const BreakFlowLink *link = &runtime->graph->links[i];
        if (link->used && link->desc.kind == BREAK_FLOW_PORT_VALUE &&
            link->desc.target_node == target && link->desc.target_port == port) {
            return eval_node(runtime, link->desc.source_node, context, used, out_value);
        }
    }
    *out_value = fallback;
    return BREAK_FLOW_OK;
}

static BreakFlowError eval_node(BreakFlowRuntime *runtime, u32 id,
                                const BreakFlowEvent *context, u32 *used,
                                f32 *out_value) {
    if (id == 0u || id > runtime->graph->max_nodes ||
        !runtime->graph->nodes[id].used) {
        return BREAK_FLOW_STALE;
    }
    const BreakFlowNodeDesc *node = &runtime->graph->nodes[id].desc;
    if (node->type == BREAK_FLOW_NODE_EVENT) {
        if (!context || context->event_node != id) return BREAK_FLOW_FAILED;
        *out_value = context->value;
        return BREAK_FLOW_OK;
    }
    if (node->type < BREAK_FLOW_NODE_MATH_ADD ||
        node->type > BREAK_FLOW_NODE_COMPARE_GREATER) {
        return BREAK_FLOW_FAILED;
    }
    BreakFlowError err = consume(runtime, used);
    if (err != BREAK_FLOW_OK) return err;
    if (runtime->eval_state[id] != 0u) return BREAK_FLOW_FAILED;
    runtime->eval_state[id] = 1u;
    f32 a = 0.0f;
    f32 b = 0.0f;
    err = eval_input(runtime, id, BREAK_FLOW_MATH_INPUT_A, node->a,
                     context, used, &a);
    if (err == BREAK_FLOW_OK) {
        err = eval_input(runtime, id, BREAK_FLOW_MATH_INPUT_B, node->b,
                         context, used, &b);
    }
    f32 value = 0.0f;
    if (err == BREAK_FLOW_OK) {
        switch (node->type) {
            case BREAK_FLOW_NODE_MATH_ADD: value = a + b; break;
            case BREAK_FLOW_NODE_MATH_SUBTRACT: value = a - b; break;
            case BREAK_FLOW_NODE_MATH_MULTIPLY: value = a * b; break;
            case BREAK_FLOW_NODE_MATH_DIVIDE:
                if (b == 0.0f) err = BREAK_FLOW_FAILED;
                else value = a / b;
                break;
            case BREAK_FLOW_NODE_COMPARE_LESS: value = a < b ? 1.0f : 0.0f; break;
            case BREAK_FLOW_NODE_COMPARE_EQUAL: value = a == b ? 1.0f : 0.0f; break;
            case BREAK_FLOW_NODE_COMPARE_GREATER: value = a > b ? 1.0f : 0.0f; break;
            default: err = BREAK_FLOW_FAILED; break;
        }
    }
    runtime->eval_state[id] = 0u;
    if (err == BREAK_FLOW_OK && !isfinite(value)) err = BREAK_FLOW_FAILED;
    if (err == BREAK_FLOW_OK) *out_value = value;
    return err;
}

static BreakFlowError fire(BreakFlowRuntime *runtime, u32 source, u32 port,
                           const BreakFlowEvent *context) {
    for (u32 i = 1u; i <= runtime->graph->max_links; i++) {
        const BreakFlowLink *link = &runtime->graph->links[i];
        if (link->used && link->desc.kind == BREAK_FLOW_PORT_EXEC &&
            link->desc.source_node == source && link->desc.source_port == port) {
            return enqueue(runtime, link->desc.target_node, false,
                           runtime->now_tick, context);
        }
    }
    return BREAK_FLOW_OK;
}

static BreakFlowError stage_action(BreakFlowRuntime *runtime,
                                   const BreakGameEntityAction *action) {
    if (runtime->action_count >= runtime->max_actions) return BREAK_FLOW_OVERLOAD;
    runtime->actions[runtime->action_count++] = *action;
    return BREAK_FLOW_OK;
}

static BreakFlowError execute_node(BreakFlowRuntime *runtime, u32 id, bool resume,
                                   const BreakFlowEvent *context, u32 *used) {
    if (id == 0u || id > runtime->graph->max_nodes ||
        !runtime->graph->nodes[id].used) {
        return BREAK_FLOW_STALE;
    }
    const BreakFlowNodeDesc *node = &runtime->graph->nodes[id].desc;
    BreakFlowError err = consume(runtime, used);
    if (err != BREAK_FLOW_OK) return err;
    if (node->type == BREAK_FLOW_NODE_EVENT) {
        return resume ? BREAK_FLOW_FAILED :
               fire(runtime, id, BREAK_FLOW_EVENT_EXEC_OUT, context);
    }
    if (node->type == BREAK_FLOW_NODE_SEQUENCE) {
        if (resume) return BREAK_FLOW_FAILED;
        err = fire(runtime, id, BREAK_FLOW_SEQUENCE_OUT_0, context);
        if (err != BREAK_FLOW_OK) return err;
        return fire(runtime, id, BREAK_FLOW_SEQUENCE_OUT_1, context);
    }
    if (node->type == BREAK_FLOW_NODE_DELAY) {
        if (resume) return fire(runtime, id, BREAK_FLOW_DELAY_EXEC_OUT, context);
        if (runtime->now_tick > UINT64_MAX - node->delay_ticks) return BREAK_FLOW_OVERLOAD;
        return enqueue(runtime, id, true, runtime->now_tick + node->delay_ticks, context);
    }
    if (node->type == BREAK_FLOW_NODE_BRANCH) {
        if (resume) return BREAK_FLOW_FAILED;
        memset(runtime->eval_state, 0, (size_t)runtime->graph->max_nodes + 1u);
        f32 condition = 0.0f;
        err = eval_input(runtime, id, BREAK_FLOW_BRANCH_CONDITION, node->a,
                         context, used, &condition);
        if (err != BREAK_FLOW_OK) return err;
        return fire(runtime, id, condition != 0.0f ? BREAK_FLOW_BRANCH_TRUE_OUT :
                    BREAK_FLOW_BRANCH_FALSE_OUT, context);
    }
    if (node->type == BREAK_FLOW_NODE_ENTITY_SET_POSITION) {
        if (resume) return BREAK_FLOW_FAILED;
        f32 values[3] = {node->a, node->b, node->c};
        const u32 ports[3] = {BREAK_FLOW_ACTION_INPUT_X, BREAK_FLOW_ACTION_INPUT_Y,
                              BREAK_FLOW_ACTION_INPUT_Z};
        memset(runtime->eval_state, 0, (size_t)runtime->graph->max_nodes + 1u);
        for (u32 i = 0u; i < 3u; i++) {
            err = eval_input(runtime, id, ports[i], values[i], context, used, &values[i]);
            if (err != BREAK_FLOW_OK) return err;
        }
        BreakGameEntityAction action;
        memset(&action, 0, sizeof(action));
        action.type = BREAK_GAME_ENTITY_SET_POSITION;
        action.entity = node->entity;
        action.position = vec3(values[0], values[1], values[2]);
        err = stage_action(runtime, &action);
        if (err != BREAK_FLOW_OK) return err;
        return fire(runtime, id, BREAK_FLOW_ACTION_EXEC_OUT, context);
    }
    if (node->type == BREAK_FLOW_NODE_ENTITY_ADD_ITEM) {
        if (resume) return BREAK_FLOW_FAILED;
        memset(runtime->eval_state, 0, (size_t)runtime->graph->max_nodes + 1u);
        f32 count = 0.0f;
        err = eval_input(runtime, id, BREAK_FLOW_ACTION_INPUT_COUNT, node->a,
                         context, used, &count);
        if (err != BREAK_FLOW_OK) return err;
        if (!isfinite(count) || count <= 0.0f || count > 1000000.0f ||
            floorf(count) != count) {
            return BREAK_FLOW_INVALID;
        }
        BreakGameEntityAction action;
        memset(&action, 0, sizeof(action));
        action.type = BREAK_GAME_ENTITY_INVENTORY_ADD;
        action.entity = node->entity;
        action.item_id = node->item_id;
        action.count = (u32)count;
        err = stage_action(runtime, &action);
        if (err != BREAK_FLOW_OK) return err;
        return fire(runtime, id, BREAK_FLOW_ACTION_EXEC_OUT, context);
    }
    return BREAK_FLOW_FAILED;
}

static BreakFlowError map_game_error(BreakGameError error) {
    switch (error) {
        case BREAK_GAME_OK: return BREAK_FLOW_OK;
        case BREAK_GAME_INVALID: return BREAK_FLOW_INVALID;
        case BREAK_GAME_OVERLOAD: return BREAK_FLOW_OVERLOAD;
        case BREAK_GAME_OOM: return BREAK_FLOW_OOM;
        case BREAK_GAME_TIMEOUT: return BREAK_FLOW_TIMEOUT;
        case BREAK_GAME_STALE: return BREAK_FLOW_STALE;
        case BREAK_GAME_REJECTED: return BREAK_FLOW_REJECTED;
        default: return BREAK_FLOW_FAILED;
    }
}

BreakFlowRuntime *break_flow_runtime_create(BreakFlowGraph *graph, BreakGame *game,
                                            const BreakFlowRuntimeConfig *config) {
    if (!graph || !game || break_flow_graph_validate(graph) != BREAK_FLOW_OK) return NULL;
    BreakFlowRuntimeConfig effective = {256u, 256u, 256u};
    if (config) effective = *config;
    if (effective.max_events == 0u) effective.max_events = 256u;
    if (effective.max_actions == 0u) effective.max_actions = 256u;
    if (effective.node_budget == 0u) effective.node_budget = 256u;
    if (effective.max_events > BREAK_FLOW_HARD_MAX_EVENTS ||
        effective.max_actions > BREAK_FLOW_HARD_MAX_ACTIONS ||
        effective.max_actions > BREAK_GAME_MAX_ENTITY_ACTIONS ||
        effective.node_budget > BREAK_FLOW_HARD_MAX_BUDGET) {
        return NULL;
    }
    BreakFlowRuntime *runtime = (BreakFlowRuntime *)calloc(1u, sizeof(*runtime));
    if (!runtime) return NULL;
    runtime->graph = graph;
    runtime->game = game;
    runtime->owner = platform_thread_current_id();
    runtime->max_events = effective.max_events;
    runtime->max_actions = effective.max_actions;
    runtime->node_budget = effective.node_budget;
    runtime->next_sequence = 1u;
    runtime->graph_revision = break_flow_graph_revision(graph);
    runtime->events = (BreakFlowEvent *)calloc(effective.max_events, sizeof(*runtime->events));
    runtime->backup = (BreakFlowEvent *)calloc(effective.max_events, sizeof(*runtime->backup));
    runtime->actions = (BreakGameEntityAction *)calloc(effective.max_actions,
                                                        sizeof(*runtime->actions));
    runtime->eval_state = (u8 *)calloc((size_t)graph->max_nodes + 1u, 1u);
    if (!runtime->events || !runtime->backup || !runtime->actions || !runtime->eval_state) {
        break_flow_runtime_destroy(runtime);
        return NULL;
    }
    return runtime;
}

void break_flow_runtime_destroy(BreakFlowRuntime *runtime) {
    if (!runtime || !is_owner(runtime)) return;
    free(runtime->events);
    free(runtime->backup);
    free(runtime->actions);
    free(runtime->eval_state);
    free(runtime);
}

BreakFlowError break_flow_runtime_check_owner(const BreakFlowRuntime *runtime) {
    if (!runtime) return BREAK_FLOW_INVALID;
    return is_owner(runtime) ? BREAK_FLOW_OK : BREAK_FLOW_REJECTED;
}

BreakFlowError break_flow_runtime_reset(BreakFlowRuntime *runtime) {
    BreakFlowError owner = break_flow_runtime_check_owner(runtime);
    if (owner != BREAK_FLOW_OK) return owner;
    BreakFlowError valid = break_flow_graph_validate(runtime->graph);
    if (valid != BREAK_FLOW_OK) return valid;
    runtime->event_count = 0u;
    runtime->action_count = 0u;
    runtime->next_sequence = 1u;
    runtime->now_tick = 0u;
    runtime->graph_revision = break_flow_graph_revision(runtime->graph);
    return BREAK_FLOW_OK;
}

BreakFlowError break_flow_runtime_post(BreakFlowRuntime *runtime, u32 event_key,
                                       Entity entity, f32 value) {
    BreakFlowError owner = break_flow_runtime_check_owner(runtime);
    if (owner != BREAK_FLOW_OK) return owner;
    if (event_key == 0u || !isfinite(value)) return BREAK_FLOW_INVALID;
    if (runtime->graph_revision != break_flow_graph_revision(runtime->graph)) {
        return BREAK_FLOW_REJECTED;
    }
    for (u32 i = 1u; i <= runtime->graph->max_nodes; i++) {
        if (runtime->graph->nodes[i].used &&
            runtime->graph->nodes[i].desc.type == BREAK_FLOW_NODE_EVENT &&
            runtime->graph->nodes[i].desc.event_key == event_key) {
            BreakFlowEvent context;
            memset(&context, 0, sizeof(context));
            context.event_node = i;
            context.entity = entity;
            context.value = value;
            return enqueue(runtime, i, false, runtime->now_tick, &context);
        }
    }
    return BREAK_FLOW_STALE;
}

BreakFlowError break_flow_runtime_tick(BreakFlowRuntime *runtime) {
    BreakFlowError owner = break_flow_runtime_check_owner(runtime);
    if (owner != BREAK_FLOW_OK) return owner;
    if (runtime->graph_revision != break_flow_graph_revision(runtime->graph)) {
        return BREAK_FLOW_REJECTED;
    }
    if (runtime->now_tick == UINT64_MAX) return BREAK_FLOW_OVERLOAD;
    memcpy(runtime->backup, runtime->events,
           (size_t)runtime->event_count * sizeof(*runtime->events));
    u32 backup_count = runtime->event_count;
    u64 backup_now = runtime->now_tick;
    u64 backup_sequence = runtime->next_sequence;
    runtime->action_count = 0u;
    u32 used = 0u;
    BreakFlowError status = BREAK_FLOW_OK;
    while (runtime->event_count > 0u) {
        u32 best = UINT32_MAX;
        for (u32 i = 0u; i < runtime->event_count; i++) {
            const BreakFlowEvent *candidate = &runtime->events[i];
            if (candidate->due_tick > runtime->now_tick) continue;
            if (best == UINT32_MAX ||
                candidate->due_tick < runtime->events[best].due_tick ||
                (candidate->due_tick == runtime->events[best].due_tick &&
                 candidate->sequence < runtime->events[best].sequence)) {
                best = i;
            }
        }
        if (best == UINT32_MAX) break;
        u32 saved_count = runtime->event_count;
        u32 saved_actions = runtime->action_count;
        BreakFlowEvent current = runtime->events[best];
        runtime->events[best] = runtime->events[saved_count - 1u];
        runtime->event_count--;
        BreakFlowError err = execute_node(runtime, current.target_node,
                                          current.resume, &current, &used);
        if (err == BREAK_FLOW_TIMEOUT) {
            runtime->event_count = saved_count - 1u;
            if (best != saved_count - 1u) {
                runtime->events[saved_count - 1u] = runtime->events[best];
            }
            runtime->events[best] = current;
            runtime->event_count = saved_count;
            runtime->action_count = saved_actions;
            status = BREAK_FLOW_TIMEOUT;
            break;
        }
        if (err != BREAK_FLOW_OK) {
            memcpy(runtime->events, runtime->backup,
                   (size_t)backup_count * sizeof(*runtime->events));
            runtime->event_count = backup_count;
            runtime->next_sequence = backup_sequence;
            runtime->now_tick = backup_now;
            runtime->action_count = 0u;
            return err;
        }
    }
    if (runtime->action_count > 0u) {
        BreakFlowError committed = map_game_error(break_game_entity_actions_apply(
            runtime->game, runtime->actions, runtime->action_count));
        if (committed != BREAK_FLOW_OK) {
            memcpy(runtime->events, runtime->backup,
                   (size_t)backup_count * sizeof(*runtime->events));
            runtime->event_count = backup_count;
            runtime->next_sequence = backup_sequence;
            runtime->now_tick = backup_now;
            runtime->action_count = 0u;
            return committed;
        }
    }
    runtime->action_count = 0u;
    runtime->now_tick++;
    return status;
}

u32 break_flow_runtime_pending_count(const BreakFlowRuntime *runtime) {
    return runtime ? runtime->event_count : 0u;
}

u64 break_flow_runtime_now_tick(const BreakFlowRuntime *runtime) {
    return runtime ? runtime->now_tick : 0u;
}
