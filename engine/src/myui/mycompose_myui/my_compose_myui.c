#include <myui/mycompose_myui/my_compose_myui_internal.h>

#include <stdatomic.h>
#include <stdlib.h>
#include <string.h>

#include <myui/mycompose/my_compose_internal.h>
#include <myui/my_layout.h>
#include <myui/my_ui_command.h>
#include <myui/my_widget_class.h>
#include <myui/my_window.h>

#define MYUI_COMPOSE_NO_INDEX UINT32_MAX

typedef struct MyComposeMyuiDefault {
    char name[MY_COMPOSE_NAME_BYTES];
    my_value_t value;
    bool used;
    bool initialized;
} MyComposeMyuiDefault;

typedef struct MyComposeMyuiListener {
    MyComposeMyui *adapter;
    my_widget_t *widget;
    MyComposeNodeHandle owner;
    MyComposeIntent intent;
    uint8_t payload[MY_COMPOSE_MESSAGE_BYTES];
    char name[MY_COMPOSE_NAME_BYTES];
    my_emitter_context_lease_t *lease;
    uint32_t id;
    bool in_use;
} MyComposeMyuiListener;

typedef struct MyComposeMyuiBinding {
    MyComposeNodeHandle handle;
    my_widget_t *widget;
    MyComposeMyuiDefault defaults[MY_COMPOSE_MAX_PROPERTIES_PER_NODE];
    MyComposeMyuiListener *listeners[MY_COMPOSE_MAX_EVENTS_PER_NODE];
    bool used;
    bool owner_registered;
} MyComposeMyuiBinding;

typedef enum MyComposeMyuiPropertyKind {
    MYUI_PROP_COMMON = 0,
    MYUI_PROP_LAYOUT,
    MYUI_PROP_STYLE,
    MYUI_PROP_CLASS
} MyComposeMyuiPropertyKind;

typedef struct MyComposeMyuiProperty {
    my_widget_t *widget;
    const my_prop_desc_t *desc;
    my_widget_class_lease_t lease;
    my_prop_snapshot_t capture;
    my_style_t *style;
    my_layout_params_t layout;
    my_value_t common;
    MyComposeMyuiPropertyKind kind;
    bool lease_held;
    bool skip_restore;
} MyComposeMyuiProperty;

typedef struct MyComposeMyuiListenerChange {
    MyComposeMyuiListener *old_listener;
    MyComposeMyuiListener *new_listener;
} MyComposeMyuiListenerChange;

typedef struct MyComposeMyuiDelete {
    my_widget_t *widget;
    my_widget_t *parent;
    MyComposeNodeHandle handle;
    uint32_t current_index;
    bool top;
    bool detached;
} MyComposeMyuiDelete;

typedef struct MyComposeMyuiOriginalParent {
    my_widget_t *widget;
    size_t offset;
    size_t count;
} MyComposeMyuiOriginalParent;

typedef struct MyComposeMyuiTxnNode {
    my_widget_t *widget;
    MyComposeMyuiDefault defaults[MY_COMPOSE_MAX_PROPERTIES_PER_NODE];
    MyComposeMyuiListener *listeners[MY_COMPOSE_MAX_EVENTS_PER_NODE];
    bool owns_widget;
    bool new_binding;
} MyComposeMyuiTxnNode;

typedef struct MyComposeMyuiTxn {
    const MyComposeTree *next;
    MyComposeMyuiTxnNode nodes[MY_COMPOSE_MAX_NODES];
    MyComposeMyuiProperty properties[MY_COMPOSE_MAX_DIFF_OPS];
    MyComposeMyuiListenerChange listener_changes[MY_COMPOSE_MAX_DIFF_OPS];
    MyComposeMyuiDelete deletes[MY_COMPOSE_MAX_NODES];
    MyComposeMyuiOriginalParent original_parents[MY_COMPOSE_MAX_NODES];
    my_widget_t *original_children[MY_COMPOSE_MAX_CHILD_LINKS];
    uint32_t property_count;
    uint32_t listener_change_count;
    uint32_t delete_count;
    uint32_t original_parent_count;
    uint32_t original_child_count;
    uint32_t factory_attempts;
    uint32_t insert_attempts;
    uint32_t detach_attempts;
    uint32_t listener_bank;
    bool active;
    bool suppress_events;
} MyComposeMyuiTxn;

typedef struct MyComposeMyuiAsync {
    my_pal_main_loop_t *loop;
    my_ui_command_scope_t *scope;
    my_emitter_context_lease_t *lease;
    atomic_uint fail_posts;
} MyComposeMyuiAsync;

typedef struct MyComposeMyuiCommand {
    my_emitter_context_lease_t *lease;
    MyComposeAsyncDeliver deliver;
    MyComposeCompletionContext *completion;
    MyComposeAsyncRelease release;
    uint32_t result;
} MyComposeMyuiCommand;

typedef struct MyComposeMyuiState {
    my_window_t *window;
    my_widget_t *root;
    MyComposeTreeBuilder *builder;
    MyComposeStore *store;
    MyComposeMyuiAsync *async;
    MyComposeMyuiBinding bindings[MY_COMPOSE_MAX_NODES];
    MyComposeMyuiListener listeners[2][MY_COMPOSE_MAX_EVENTS];
    MyComposeMyuiTxn txn;
    uint32_t close_listener;
    uint32_t listener_bank;
    bool window_closed;
} MyComposeMyuiState;

static MyComposeMyuiState *state_of(MyComposeMyui *adapter) {
    return adapter != NULL ? (MyComposeMyuiState *)adapter->state : NULL;
}

static bool handle_equal(MyComposeNodeHandle a, MyComposeNodeHandle b) {
    return a.index == b.index && a.generation == b.generation;
}

static bool handle_valid(MyComposeNodeHandle handle) {
    return handle.index < MY_COMPOSE_MAX_NODES && handle.generation != 0u;
}

static uint32_t next_index(const MyComposeMyuiState *state,
    MyComposeNodeHandle handle) {
    return my_compose_tree_internal_find_node(state->builder->next, handle);
}

static uint32_t current_index(const MyComposeMyuiState *state,
    MyComposeNodeHandle handle) {
    return my_compose_tree_internal_find_node(state->builder->current, handle);
}

static MyComposeMyuiBinding *find_binding(MyComposeMyuiState *state,
    MyComposeNodeHandle handle) {
    MyComposeMyuiBinding *binding;
    if (!handle_valid(handle)) return NULL;
    binding = &state->bindings[handle.index];
    return binding->used && handle_equal(binding->handle, handle) ? binding : NULL;
}

static MyComposeMyuiBinding *binding_for_current(MyComposeMyuiState *state,
    uint32_t index) {
    return find_binding(state, state->builder->current->nodes[index].handle);
}

static size_t child_index(my_widget_t *parent, my_widget_t *child) {
    size_t i;
    for (i = 0u; i < my_widget_child_count(parent); ++i) {
        if (my_widget_get_child(parent, i) == child) return i;
    }
    return SIZE_MAX;
}

static void layout_path(my_widget_t *widget) {
    my_widget_t *ancestor;
    if (widget == NULL) return;
    widget->need_layout = true;
    for (ancestor = widget->parent; ancestor != NULL; ancestor = ancestor->parent) {
        ancestor->subtree_need_layout = true;
    }
}

static void raw_detach(my_widget_t *parent, my_widget_t *child) {
    size_t index = child_index(parent, child);
    if (index == SIZE_MAX) return;
    my_widget_invalidate(parent, NULL);
    (void)my_darray_remove_at(parent->children, index);
    child->parent = NULL;
    my_widget_request_layout(parent);
}

static void raw_insert(my_widget_t *parent, my_widget_t *child, size_t index) {
    size_t count = my_widget_child_count(parent);
    if (index > count) index = count;
    parent->children->items[count] = child;
    parent->children->size++;
    if (index < count) {
        memmove(parent->children->items + index + 1u,
            parent->children->items + index, (count - index) * sizeof(void *));
    }
    parent->children->items[index] = child;
    child->parent = parent;
    my_widget_request_layout(parent);
    layout_path(child);
    my_widget_invalidate(parent, NULL);
}

static my_ret_t stage_insert(MyComposeMyui *adapter, my_widget_t *parent,
    my_widget_t *child) {
    MyComposeMyuiState *state = state_of(adapter);
    uint32_t attempt = ++state->txn.insert_attempts;
    adapter->stats.insert_calls++;
    if (adapter->fault.insert_call != 0u &&
        attempt == adapter->fault.insert_call) {
        return MY_RET_FAIL;
    }
    return my_widget_insert_child(parent, child, my_widget_child_count(parent));
}

static my_ret_t stage_detach(MyComposeMyui *adapter, my_widget_t *parent,
    my_widget_t *child, my_widget_t **detached) {
    MyComposeMyuiState *state = state_of(adapter);
    uint32_t attempt = ++state->txn.detach_attempts;
    adapter->stats.detach_calls++;
    if ((adapter->fault.detach_call != 0u &&
            attempt == adapter->fault.detach_call) ||
        (adapter->fault.fail_after_detach_error && attempt != 0u &&
            adapter->fault.detach_call != 0u &&
            attempt > adapter->fault.detach_call)) {
        return MY_RET_FAIL;
    }
    return my_widget_detach_child(parent, child, detached);
}

static my_ret_t stage_set_property(MyComposeMyui *adapter, my_widget_t *widget,
    const char *name, const my_value_t *value) {
    bool targeted = widget == adapter->fault.property_widget &&
        adapter->fault.property_name != NULL &&
        strcmp(name, adapter->fault.property_name) == 0;
    adapter->stats.property_set_calls++;
    if (targeted || (adapter->fault.fail_after_property_error &&
            adapter->fault.property_widget == NULL &&
            adapter->fault.property_name == NULL)) {
        if (targeted) {
            adapter->fault.property_widget = NULL;
            adapter->fault.property_name = NULL;
        }
        return MY_RET_FAIL;
    }
    return my_widget_set_prop(widget, name, value);
}

static bool intrinsic_type(const char *type) {
    return type != NULL && type[0] == '@';
}

static const my_prop_desc_t *class_property(const my_widget_class_t *cls,
    const char *name) {
    const my_prop_desc_t *desc;
    if (cls == NULL || cls->props == NULL) return NULL;
    for (desc = cls->props; desc->name != NULL; ++desc) {
        if (strcmp(desc->name, name) == 0) return desc;
    }
    return NULL;
}

static bool class_event(const my_widget_class_t *cls, const char *name) {
    size_t i;
    if (cls == NULL || cls->events == NULL) return false;
    for (i = 0u; cls->events[i] != NULL; ++i) {
        if (strcmp(cls->events[i], name) == 0) return true;
    }
    return false;
}

static bool common_property(const char *name) {
    return strcmp(name, "visible") == 0 || strcmp(name, "enable") == 0 ||
        (name[0] != '\0' && name[1] == '\0' && strchr("xywh", name[0]) != NULL);
}

static const my_prop_desc_t *common_descriptor(const char *name) {
    static const my_prop_desc_t descriptors[] = {
        {"visible", MY_PROP_BOOL, NULL, NULL, NULL, NULL, NULL},
        {"enable", MY_PROP_BOOL, NULL, NULL, NULL, NULL, NULL},
        {"x", MY_PROP_INT, NULL, NULL, NULL, NULL, NULL},
        {"y", MY_PROP_INT, NULL, NULL, NULL, NULL, NULL},
        {"w", MY_PROP_INT, NULL, NULL, NULL, NULL, NULL},
        {"h", MY_PROP_INT, NULL, NULL, NULL, NULL, NULL}
    };
    size_t i;
    for (i = 0u; i < sizeof(descriptors) / sizeof(descriptors[0]); ++i) {
        if (strcmp(descriptors[i].name, name) == 0) return &descriptors[i];
    }
    return NULL;
}

static bool style_property(const char *name, my_widget_state_t *state,
    const char **key) {
    const char *rest;
    if (strncmp(name, "style:", 6u) != 0) return false;
    rest = name + 6u;
    *state = MY_STATE_NORMAL;
    if (strncmp(rest, "normal:", 7u) == 0) {
        rest += 7u;
    } else if (strncmp(rest, "hover:", 6u) == 0) {
        *state = MY_STATE_HOVER;
        rest += 6u;
    } else if (strncmp(rest, "pressed:", 8u) == 0) {
        *state = MY_STATE_PRESSED;
        rest += 8u;
    } else if (strncmp(rest, "disabled:", 9u) == 0) {
        *state = MY_STATE_DISABLED;
        rest += 9u;
    }
    if (rest[0] == '\0' || strlen(rest) >= MY_STYLE_KEY_LEN) return false;
    *key = rest;
    return true;
}

static MyComposeMyuiPropertyKind property_kind(const char *name,
    my_widget_state_t *style_state, const char **style_key) {
    if (strcmp(name, "layout") == 0) return MYUI_PROP_LAYOUT;
    if (common_property(name)) return MYUI_PROP_COMMON;
    if (strncmp(name, "style:", 6u) == 0) return MYUI_PROP_STYLE;
    (void)style_state;
    (void)style_key;
    return MYUI_PROP_CLASS;
}

static void compose_value_to_my(const MyComposeValue *source, my_value_t *out) {
    my_value_init(out, NULL);
    switch (source->type) {
        case MY_COMPOSE_VALUE_NONE:
            break;
        case MY_COMPOSE_VALUE_BOOL:
            out->type = MY_VALUE_BOOL;
            out->u.b = source->as.bool_value;
            break;
        case MY_COMPOSE_VALUE_INT32:
            out->type = MY_VALUE_INT32;
            out->u.i32 = source->as.int32_value;
            break;
        case MY_COMPOSE_VALUE_UINT32:
            out->type = MY_VALUE_UINT32;
            out->u.u32 = source->as.uint32_value;
            break;
        case MY_COMPOSE_VALUE_INT64:
            out->type = MY_VALUE_INT64;
            out->u.i64 = source->as.int64_value;
            break;
        case MY_COMPOSE_VALUE_FLOAT:
            out->type = MY_VALUE_FLOAT;
            out->u.f32 = source->as.float_value;
            break;
        case MY_COMPOSE_VALUE_DOUBLE:
            out->type = MY_VALUE_DOUBLE;
            out->u.f64 = source->as.double_value;
            break;
        case MY_COMPOSE_VALUE_STRING:
            out->type = MY_VALUE_STR;
            out->u.str = (char *)(source->as.string.data != NULL ?
                source->as.string.data : "");
            break;
        case MY_COMPOSE_VALUE_COLOR:
            out->type = MY_VALUE_UINT32;
            out->u.u32 = source->as.color;
            break;
        default:
            break;
    }
}

static bool property_value_valid(const MyComposeValue *value,
    MyComposeMyuiPropertyKind kind, const my_prop_desc_t *desc,
    const char *name, my_widget_state_t style_state, const char *style_key) {
    if (kind == MYUI_PROP_STYLE) {
        if (!style_property(name, &style_state, &style_key)) return false;
        return value->type != MY_COMPOSE_VALUE_NONE || style_key != NULL;
    }
    if (value->type == MY_COMPOSE_VALUE_NONE) return true;
    if (kind == MYUI_PROP_LAYOUT) return value->type == MY_COMPOSE_VALUE_STRING;
    if (kind == MYUI_PROP_COMMON) {
        if (strcmp(name, "visible") == 0 || strcmp(name, "enable") == 0) {
            return value->type == MY_COMPOSE_VALUE_BOOL;
        }
        return value->type == MY_COMPOSE_VALUE_INT32;
    }
    if (desc == NULL) return false;
    switch (desc->type) {
        case MY_PROP_STRING:
            return value->type == MY_COMPOSE_VALUE_STRING;
        case MY_PROP_INT:
            return value->type == MY_COMPOSE_VALUE_INT32;
        case MY_PROP_FLOAT:
            return value->type == MY_COMPOSE_VALUE_FLOAT ||
                value->type == MY_COMPOSE_VALUE_DOUBLE ||
                value->type == MY_COMPOSE_VALUE_INT32;
        case MY_PROP_BOOL:
            return value->type == MY_COMPOSE_VALUE_BOOL;
        case MY_PROP_COLOR:
            return value->type == MY_COMPOSE_VALUE_COLOR ||
                value->type == MY_COMPOSE_VALUE_UINT32;
        default:
            return false;
    }
}

static MyComposeStatus preflight_property(MyComposeMyuiState *state,
    const MyComposeNodeRecord *node, const char *name,
    const MyComposeValue *value, my_widget_t *current_widget) {
    MyComposeMyuiPropertyKind kind = property_kind(name, NULL, NULL);
    const my_widget_class_t *cls;
    const my_prop_desc_t *desc = NULL;
    my_widget_class_lease_t lease = {0};
    my_widget_state_t style_state = MY_STATE_NORMAL;
    const char *style_key = NULL;
    const char *type = state->builder->next->strings + node->type_offset;
    my_ret_t ret;
    if (kind == MYUI_PROP_STYLE) {
        if (!style_property(name, &style_state, &style_key)) {
            return MY_COMPOSE_INVALID;
        }
    } else if (kind == MYUI_PROP_LAYOUT && value->type != MY_COMPOSE_VALUE_NONE) {
        my_layout_params_t parsed;
        my_value_t converted;
        compose_value_to_my(value, &converted);
        if (converted.type != MY_VALUE_STR ||
            my_layout_params_parse(converted.u.str, &parsed) != MY_RET_OK) {
            return MY_COMPOSE_INVALID;
        }
    } else if (kind == MYUI_PROP_CLASS && !intrinsic_type(type)) {
        ret = my_widget_class_acquire(type, &cls, &lease);
        if (ret != MY_RET_OK) return MY_COMPOSE_NOT_SUPPORTED;
        desc = class_property(cls, name);
        if (current_widget != NULL && cls->is_instance != NULL &&
            !cls->is_instance(current_widget)) {
            my_widget_class_release(&lease);
            return MY_COMPOSE_TYPE_MISMATCH;
        }
        if (desc == NULL || desc->set == NULL || desc->get == NULL ||
            desc->capture == NULL || desc->discard == NULL ||
            desc->restore == NULL) {
            my_widget_class_release(&lease);
            return MY_COMPOSE_NOT_SUPPORTED;
        }
        my_widget_class_release(&lease);
    } else if (kind == MYUI_PROP_CLASS) {
        return MY_COMPOSE_NOT_SUPPORTED;
    }
    if (!property_value_valid(value, kind, desc, name, style_state, style_key)) {
        return MY_COMPOSE_INVALID;
    }
    return MY_COMPOSE_OK;
}

static bool current_snapshot_matches(MyComposeMyuiState *state) {
    const MyComposeTree *current = state->builder->current;
    uint32_t i;
    if (current->node_count == 0u) {
        for (i = 0u; i < MY_COMPOSE_MAX_NODES; ++i) {
            if (state->bindings[i].used) return false;
        }
        return my_widget_child_count(state->root) == 0u;
    }
    for (i = 0u; i < current->node_count; ++i) {
        const MyComposeNodeRecord *node = &current->nodes[i];
        MyComposeMyuiBinding *binding = binding_for_current(state, i);
        my_widget_t *parent = state->root;
        uint32_t j;
        if (binding == NULL || binding->widget == NULL) return false;
        if (node->parent != MY_COMPOSE_NO_INDEX) {
            MyComposeMyuiBinding *parent_binding = binding_for_current(state,
                node->parent);
            if (parent_binding == NULL) return false;
            parent = parent_binding->widget;
        }
        if (node->parent == MY_COMPOSE_NO_INDEX) {
            if (binding->widget != state->root) return false;
        } else if (binding->widget->parent != parent) {
            return false;
        }
        if (my_widget_child_count(binding->widget) != node->child_count) {
            return false;
        }
        if (node->parent != MY_COMPOSE_NO_INDEX &&
            child_index(parent, binding->widget) != node->child_index) {
            return false;
        }
        if (binding->owner_registered) {
            const MyComposeOwner *owner = &state->store->owners[node->handle.index];
            if (!owner->active || owner->retired ||
                owner->generation != node->handle.generation) {
                return false;
            }
        }
        for (j = 0u; j < MY_COMPOSE_MAX_EVENTS_PER_NODE; ++j) {
            MyComposeMyuiListener *listener = binding->listeners[j];
            if (listener != NULL &&
                (!listener->in_use || listener->widget != binding->widget ||
                    !handle_equal(listener->owner, node->handle))) {
                return false;
            }
        }
    }
    return true;
}

static MyComposeStatus preflight_diff(MyComposeMyui *adapter,
    const MyComposeDiff *diff) {
    MyComposeMyuiState *state = state_of(adapter);
    const MyComposeTree *next = state->builder->next;
    uint32_t i;
    uint32_t j;
    if (state->builder->state != MY_COMPOSE_BUILD_ENDED || diff == NULL) {
        return MY_COMPOSE_INVALID;
    }
    if (state->window_closed || state->store->closed) return MY_COMPOSE_CANCELLED;
    if (diff->count > MY_COMPOSE_MAX_DIFF_OPS) return MY_COMPOSE_OVERLOAD;
    if (diff->count != 0u && diff->ops == NULL) return MY_COMPOSE_INVALID;
    for (i = 0u; i < next->node_count; ++i) {
        const MyComposeNodeRecord *a = &next->nodes[i];
        if (a->key_offset == MY_COMPOSE_NO_INDEX) continue;
        for (j = i + 1u; j < next->node_count; ++j) {
            const MyComposeNodeRecord *b = &next->nodes[j];
            if (a->parent == b->parent && b->key_offset != MY_COMPOSE_NO_INDEX &&
                strcmp(next->strings + a->key_offset,
                    next->strings + b->key_offset) == 0) {
                return MY_COMPOSE_DUPLICATE_KEY;
            }
        }
    }
    for (i = 0u; i < diff->count; ++i) {
        if (diff->ops[i].type != MY_COMPOSE_DIFF_CREATE) continue;
        for (j = i + 1u; j < diff->count; ++j) {
            if (diff->ops[j].type == MY_COMPOSE_DIFF_CREATE &&
                handle_equal(diff->ops[i].node, diff->ops[j].node)) {
                return MY_COMPOSE_DUPLICATE_KEY;
            }
        }
    }
    if (diff->count != state->builder->diff.count) return MY_COMPOSE_CONFLICT;
    for (i = 0u; i < diff->count; ++i) {
        const MyComposeDiffOp *a = &diff->ops[i];
        const MyComposeDiffOp *b = &state->builder->diff.ops[i];
        if (a->type != b->type || !handle_equal(a->node, b->node) ||
            !handle_equal(a->parent, b->parent) ||
            a->from_index != b->from_index || a->to_index != b->to_index ||
            a->on_event != b->on_event ||
            ((a->name == NULL) != (b->name == NULL)) ||
            (a->name != NULL && b->name != NULL && strcmp(a->name, b->name) != 0)) {
            return MY_COMPOSE_CONFLICT;
        }
    }
    {
        uint32_t property_operations = 0u;
        uint32_t listener_operations = 0u;
        for (i = 0u; i < next->node_count; ++i) {
            if (next->nodes[i].match != MY_COMPOSE_MATCH_NODE) {
                property_operations += next->nodes[i].property_count;
                listener_operations += next->nodes[i].event_count;
            }
        }
        for (i = 0u; i < diff->count; ++i) {
            if (diff->ops[i].type != MY_COMPOSE_DIFF_UPDATE) continue;
            if (diff->ops[i].on_event) {
                listener_operations++;
            } else {
                property_operations++;
            }
        }
        if (property_operations > MY_COMPOSE_MAX_DIFF_OPS ||
            listener_operations > MY_COMPOSE_MAX_DIFF_OPS) {
            return MY_COMPOSE_OVERLOAD;
        }
    }
    if (!current_snapshot_matches(state)) return MY_COMPOSE_CONFLICT;
    for (i = 0u; i < next->node_count; ++i) {
        const MyComposeNodeRecord *node = &next->nodes[i];
        const MyComposeSlot *slot;
        my_widget_t *widget = NULL;
        uint32_t property;
        uint32_t event;
        if (!handle_valid(node->handle)) return MY_COMPOSE_INVALID;
        slot = &state->builder->slots[node->handle.index];
        if (slot->retired || node->handle.generation == UINT32_MAX) {
            return MY_COMPOSE_OVERLOAD;
        }
        if (node->match == MY_COMPOSE_MATCH_NODE) {
            MyComposeMyuiBinding *binding = find_binding(state, node->handle);
            if (strcmp(next->strings + node->type_offset, "@root") == 0) {
                widget = state->root;
            } else if (binding == NULL) {
                return MY_COMPOSE_CONFLICT;
            } else {
                widget = binding->widget;
            }
        }
        property = node->first_property;
        while (property != MY_COMPOSE_NO_INDEX) {
            const MyComposePropertyRecord *record = &next->properties[property];
            MyComposeStatus status = preflight_property(state, node,
                next->strings + record->name_offset, &record->value, widget);
            if (status != MY_COMPOSE_OK) return status;
            property = record->next;
        }
        event = node->first_event;
        while (event != MY_COMPOSE_NO_INDEX) {
            const MyComposeEventRecord *record = &next->events[event];
            const char *name = next->strings + record->name_offset;
            const char *type = next->strings + node->type_offset;
            const MyComposeOwner *owner = &state->store->owners[node->handle.index];
            if (record->payload_size > MY_COMPOSE_MESSAGE_BYTES) {
                return MY_COMPOSE_OVERLOAD;
            }
            if (intrinsic_type(type)) return MY_COMPOSE_NOT_SUPPORTED;
            {
                const my_widget_class_t *cls;
                my_widget_class_lease_t lease = {0};
                if (my_widget_class_acquire(type, &cls, &lease) != MY_RET_OK) {
                    return MY_COMPOSE_NOT_SUPPORTED;
                }
                if (!class_event(cls, name)) {
                    my_widget_class_release(&lease);
                    return MY_COMPOSE_NOT_SUPPORTED;
                }
                my_widget_class_release(&lease);
            }
            if (owner->retired || state->store->generation == UINT32_MAX ||
                node->handle.generation == UINT32_MAX) {
                return MY_COMPOSE_OVERLOAD;
            }
            if (owner->active && owner->generation > node->handle.generation) {
                return MY_COMPOSE_STALE;
            }
            event = record->next;
        }
    }
    for (i = 0u; i < diff->count; ++i) {
        if (diff->ops[i].type == MY_COMPOSE_DIFF_DELETE) {
            MyComposeMyuiBinding *binding = find_binding(state, diff->ops[i].node);
            if (binding == NULL) return MY_COMPOSE_CONFLICT;
            if (diff->ops[i].node.generation >= UINT32_MAX - 1u) {
                return MY_COMPOSE_OVERLOAD;
            }
        }
    }
    return MY_COMPOSE_OK;
}

static bool style_has_key(const my_widget_t *widget, my_widget_state_t state,
    const char *key) {
    size_t i;
    if (widget == NULL || widget->local_style == NULL) return false;
    for (i = 0u; i < widget->local_style->counts[state]; ++i) {
        if (strcmp(widget->local_style->props[state][i].key, key) == 0) return true;
    }
    return false;
}

static MyComposeStatus preflight_style_capacity(MyComposeMyuiState *state,
    const MyComposeDiff *diff) {
    size_t counts[MY_COMPOSE_MAX_NODES][MY_STATE_COUNT];
    const MyComposeTree *next = state->builder->next;
    uint32_t i;
    memset(counts, 0, sizeof(counts));
    for (i = 0u; i < next->node_count; ++i) {
        const MyComposeNodeRecord *node = &next->nodes[i];
        if (node->match == MY_COMPOSE_MATCH_NODE) {
            MyComposeMyuiBinding *binding = find_binding(state, node->handle);
            my_widget_t *widget = strcmp(next->strings + node->type_offset,
                "@root") == 0 ? state->root : binding->widget;
            if (widget->local_style != NULL) {
                memcpy(counts[i], widget->local_style->counts,
                    sizeof(counts[i]));
            }
        }
    }
    for (i = 0u; i < next->node_count; ++i) {
        const MyComposeNodeRecord *node = &next->nodes[i];
        uint32_t property = node->first_property;
        if (node->match == MY_COMPOSE_MATCH_NODE) continue;
        while (property != MY_COMPOSE_NO_INDEX) {
            const MyComposePropertyRecord *record = &next->properties[property];
            const char *name = next->strings + record->name_offset;
            my_widget_state_t style_state;
            const char *key;
            if (property_kind(name, NULL, NULL) == MYUI_PROP_STYLE &&
                style_property(name, &style_state, &key) &&
                record->value.type != MY_COMPOSE_VALUE_NONE) {
                if (counts[i][style_state] >= MY_STYLE_MAX_PROPS) {
                    return MY_COMPOSE_OVERLOAD;
                }
                counts[i][style_state]++;
            }
            property = record->next;
        }
    }
    for (i = 0u; i < diff->count; ++i) {
        const MyComposeDiffOp *op = &diff->ops[i];
        uint32_t node_index;
        uint32_t property = MY_COMPOSE_NO_INDEX;
        const MyComposeValue *value = NULL;
        const MyComposeNodeRecord *node;
        MyComposeMyuiBinding *binding;
        my_widget_t *widget;
        my_widget_state_t style_state;
        const char *key;
        bool present;
        if (op->type != MY_COMPOSE_DIFF_UPDATE || op->on_event ||
            property_kind(op->name, NULL, NULL) != MYUI_PROP_STYLE ||
            !style_property(op->name, &style_state, &key)) {
            continue;
        }
        node_index = next_index(state, op->node);
        if (node_index == MY_COMPOSE_NO_INDEX) return MY_COMPOSE_CONFLICT;
        node = &next->nodes[node_index];
        property = node->first_property;
        while (property != MY_COMPOSE_NO_INDEX) {
            const MyComposePropertyRecord *record = &next->properties[property];
            if (strcmp(next->strings + record->name_offset, op->name) == 0) {
                value = &record->value;
                break;
            }
            property = record->next;
        }
        binding = find_binding(state, op->node);
        widget = binding != NULL ? binding->widget : state->root;
        present = style_has_key(widget, style_state, key);
        if ((value == NULL || value->type == MY_COMPOSE_VALUE_NONE)) {
            if (present && counts[node_index][style_state] != 0u) {
                counts[node_index][style_state]--;
            }
        } else if (!present) {
            if (counts[node_index][style_state] >= MY_STYLE_MAX_PROPS) {
                return MY_COMPOSE_OVERLOAD;
            }
            counts[node_index][style_state]++;
        }
    }
    return MY_COMPOSE_OK;
}

static MyComposeStatus capture_original(MyComposeMyuiState *state) {
    MyComposeMyuiTxn *txn = &state->txn;
    const MyComposeTree *current = state->builder->current;
    uint32_t i;
    if (current->node_count == 0u) {
        MyComposeMyuiOriginalParent *parent = &txn->original_parents[0];
        parent->widget = state->root;
        parent->offset = 0u;
        parent->count = my_widget_child_count(state->root);
        if (parent->count > MY_COMPOSE_MAX_CHILD_LINKS) return MY_COMPOSE_OVERLOAD;
        for (i = 0u; i < parent->count; ++i) {
            txn->original_children[i] = my_widget_get_child(state->root, i);
        }
        txn->original_parent_count = 1u;
        txn->original_child_count = (uint32_t)parent->count;
        return MY_COMPOSE_OK;
    }
    for (i = 0u; i < current->node_count; ++i) {
        MyComposeMyuiBinding *binding = binding_for_current(state, i);
        MyComposeMyuiOriginalParent *parent =
            &txn->original_parents[txn->original_parent_count];
        size_t j;
        parent->widget = binding->widget;
        parent->offset = txn->original_child_count;
        parent->count = my_widget_child_count(binding->widget);
        if (parent->count > MY_COMPOSE_MAX_CHILD_LINKS -
            txn->original_child_count) {
            return MY_COMPOSE_OVERLOAD;
        }
        for (j = 0u; j < parent->count; ++j) {
            txn->original_children[txn->original_child_count++] =
                my_widget_get_child(binding->widget, j);
        }
        txn->original_parent_count++;
    }
    return MY_COMPOSE_OK;
}

static MyComposeMyuiDefault *default_slot(MyComposeMyuiState *state,
    uint32_t node_index, const char *name, bool create) {
    MyComposeMyuiTxnNode *node = &state->txn.nodes[node_index];
    MyComposeMyuiDefault *defaults;
    uint32_t i;
    if (!node->new_binding) {
        MyComposeMyuiBinding *binding = find_binding(state,
            state->builder->next->nodes[node_index].handle);
        defaults = binding->defaults;
    } else {
        defaults = node->defaults;
    }
    for (i = 0u; i < MY_COMPOSE_MAX_PROPERTIES_PER_NODE; ++i) {
        if (defaults[i].used && strcmp(defaults[i].name, name) == 0) {
            return &defaults[i];
        }
    }
    if (!create) return NULL;
    for (i = 0u; i < MY_COMPOSE_MAX_PROPERTIES_PER_NODE; ++i) {
        if (!defaults[i].used) {
            defaults[i].used = true;
            snprintf(defaults[i].name, sizeof(defaults[i].name), "%s", name);
            my_value_init(&defaults[i].value, NULL);
            return &defaults[i];
        }
    }
    return NULL;
}

static MyComposeStatus ensure_default(MyComposeMyuiState *state,
    uint32_t node_index, const char *name, my_widget_t *widget,
    MyComposeMyuiDefault **out) {
    MyComposeMyuiDefault *value = default_slot(state, node_index, name, true);
    my_ret_t ret;
    if (value == NULL) return MY_COMPOSE_OVERLOAD;
    if (value->initialized) {
        *out = value;
        return MY_COMPOSE_OK;
    }
    my_value_init(&value->value, ((my_object_t *)widget)->allocator);
    if (strcmp(name, "layout") == 0) {
        ret = my_value_set_str(&value->value, "");
    } else {
        ret = my_widget_get_prop(widget, name, &value->value);
    }
    if (ret != MY_RET_OK) return MY_COMPOSE_NOT_SUPPORTED;
    value->initialized = true;
    *out = value;
    return MY_COMPOSE_OK;
}

static void discard_property(MyComposeMyuiProperty *property, bool restore) {
    if (property->kind == MYUI_PROP_CLASS) {
        if (restore) property->desc->restore(property->widget, &property->capture);
        property->desc->discard(property->widget, &property->capture);
        if (property->lease_held) {
            my_widget_class_release(&property->lease);
            property->lease_held = false;
        }
    } else if (property->kind == MYUI_PROP_STYLE) {
        if (restore) {
            my_style_t *saved = property->style;
            property->style = property->widget->local_style;
            property->widget->local_style = saved;
            my_widget_invalidate(property->widget, NULL);
        }
        if (property->style != NULL) {
            my_style_reset(property->style);
            my_mem_free(((my_object_t *)property->widget)->allocator,
                property->style);
            property->style = NULL;
        }
    } else if (property->kind == MYUI_PROP_LAYOUT) {
        if (restore) {
            property->widget->layout_params = property->layout;
            my_widget_request_layout(property->widget->parent != NULL ?
                property->widget->parent : property->widget);
            my_widget_invalidate(property->widget, NULL);
        }
    } else if (restore) {
        const char *name = property->desc->name;
        my_widget_t *widget = property->widget;
        if (strcmp(name, "visible") == 0) {
            widget->visible = my_value_get_bool(&property->common);
        } else if (strcmp(name, "enable") == 0) {
            widget->enable = my_value_get_bool(&property->common);
        } else {
            my_rect_t rect = widget->rect;
            int32_t value = my_value_get_int32(&property->common);
            if (name[0] == 'x') rect.x = value;
            if (name[0] == 'y') rect.y = value;
            if (name[0] == 'w') rect.w = value;
            if (name[0] == 'h') rect.h = value;
            widget->rect = rect;
            my_widget_request_layout(widget->parent != NULL ? widget->parent : widget);
        }
        my_widget_invalidate(widget, NULL);
    }
    my_value_reset(&property->common);
    property->desc = NULL;
}

static MyComposeStatus capture_property(MyComposeMyui *adapter,
    uint32_t node_index, my_widget_t *widget, const char *name,
    const my_prop_desc_t *desc, MyComposeMyuiPropertyKind kind) {
    MyComposeMyuiState *state = state_of(adapter);
    MyComposeMyuiProperty *property;
    if (state->txn.property_count >= MY_COMPOSE_MAX_DIFF_OPS) {
        return MY_COMPOSE_OVERLOAD;
    }
    property = &state->txn.properties[state->txn.property_count];
    memset(property, 0, sizeof(*property));
    property->widget = widget;
    property->kind = kind;
    property->skip_restore = state->txn.nodes[node_index].owns_widget;
    my_value_init(&property->common, ((my_object_t *)widget)->allocator);
    if (kind == MYUI_PROP_CLASS) {
        const my_widget_class_t *cls;
        my_ret_t ret = my_widget_class_acquire(widget->widget_type, &cls,
            &property->lease);
        if (ret != MY_RET_OK) return MY_COMPOSE_NOT_SUPPORTED;
        property->lease_held = true;
        property->desc = class_property(cls, desc->name);
        if (property->desc == NULL) {
            my_widget_class_release(&property->lease);
            property->lease_held = false;
            return MY_COMPOSE_NOT_SUPPORTED;
        }
        ret = property->desc->capture(widget, &property->capture);
        if (ret != MY_RET_OK) {
            property->desc->discard(widget, &property->capture);
            my_widget_class_release(&property->lease);
            property->lease_held = false;
            property->desc = NULL;
            return MY_COMPOSE_FAILED;
        }
    } else if (kind == MYUI_PROP_STYLE) {
        if (widget->local_style != NULL) {
            size_t s;
            size_t i;
            property->style = (my_style_t *)my_mem_calloc(
                ((my_object_t *)widget)->allocator, 1u, sizeof(*property->style));
            if (property->style == NULL) return MY_COMPOSE_FAILED;
            my_style_init(property->style, ((my_object_t *)widget)->allocator);
            for (s = 0u; s < MY_STATE_COUNT; ++s) {
                property->style->counts[s] = widget->local_style->counts[s];
                for (i = 0u; i < widget->local_style->counts[s]; ++i) {
                    const my_style_prop_t *source = &widget->local_style->props[s][i];
                    my_style_prop_t *target = &property->style->props[s][i];
                    snprintf(target->key, sizeof(target->key), "%s", source->key);
                    if (my_value_copy(&target->value, &source->value) != MY_RET_OK) {
                        discard_property(property, false);
                        return MY_COMPOSE_FAILED;
                    }
                }
            }
        }
    } else if (kind == MYUI_PROP_LAYOUT) {
        property->layout = widget->layout_params;
    } else {
        property->desc = desc;
        if (my_widget_get_prop(widget, name, &property->common) != MY_RET_OK) {
            return MY_COMPOSE_NOT_SUPPORTED;
        }
    }
    state->txn.property_count++;
    adapter->stats.property_captures++;
    return MY_COMPOSE_OK;
}

static MyComposeStatus apply_property(MyComposeMyui *adapter,
    uint32_t node_index, const char *name, const MyComposeValue *value) {
    MyComposeMyuiState *state = state_of(adapter);
    MyComposeMyuiTxnNode *node = &state->txn.nodes[node_index];
    const MyComposeNodeRecord *record = &state->builder->next->nodes[node_index];
    const char *type = state->builder->next->strings + record->type_offset;
    MyComposeMyuiPropertyKind kind = property_kind(name, NULL, NULL);
    my_widget_t *widget = node->widget;
    const my_prop_desc_t *desc = NULL;
    MyComposeValue none = {0};
    my_value_t converted;
    my_ret_t ret;
    MyComposeStatus status;
    MyComposeMyuiDefault *default_value = NULL;
    my_widget_state_t style_state = MY_STATE_NORMAL;
    const char *style_key = NULL;
    if (value == NULL) {
        none.type = MY_COMPOSE_VALUE_NONE;
        value = &none;
    }
    if (kind == MYUI_PROP_CLASS) {
        const my_widget_class_t *cls;
        my_widget_class_lease_t lease = {0};
        if (intrinsic_type(type) ||
            my_widget_class_acquire(type, &cls, &lease) != MY_RET_OK) {
            return MY_COMPOSE_NOT_SUPPORTED;
        }
        desc = class_property(cls, name);
        my_widget_class_release(&lease);
        if (desc == NULL) return MY_COMPOSE_NOT_SUPPORTED;
    }
    if (node->owns_widget && value->type == MY_COMPOSE_VALUE_NONE) {
        return MY_COMPOSE_OK;
    }
    if (kind == MYUI_PROP_STYLE && value->type == MY_COMPOSE_VALUE_NONE &&
        style_property(name, &style_state, &style_key) &&
        !style_has_key(widget, style_state, style_key)) {
        return MY_COMPOSE_OK;
    }
    if (kind == MYUI_PROP_COMMON || kind == MYUI_PROP_CLASS) {
        status = ensure_default(state, node_index, name, widget, &default_value);
        if (status != MY_COMPOSE_OK) return status;
    }
    status = capture_property(adapter, node_index, widget, name,
        kind == MYUI_PROP_COMMON ? common_descriptor(name) : desc, kind);
    if (status != MY_COMPOSE_OK) return status;
    if (value->type == MY_COMPOSE_VALUE_NONE) {
        if (kind == MYUI_PROP_LAYOUT) {
            ret = my_widget_set_layout_params(widget, "");
        } else if (kind == MYUI_PROP_STYLE) {
            (void)style_property(name, &style_state, &style_key);
            ret = my_widget_style_unset(widget, style_state, style_key);
            if (ret == MY_RET_NOT_FOUND) ret = MY_RET_OK;
        } else {
            ret = stage_set_property(adapter, widget, name, &default_value->value);
        }
    } else if (kind == MYUI_PROP_LAYOUT) {
        compose_value_to_my(value, &converted);
        ret = my_widget_set_layout_params(widget, converted.u.str);
    } else if (kind == MYUI_PROP_STYLE) {
        (void)style_property(name, &style_state, &style_key);
        compose_value_to_my(value, &converted);
        converted.allocator = ((my_object_t *)widget)->allocator;
        ret = my_widget_style_set(widget, style_state, style_key, &converted);
    } else {
        compose_value_to_my(value, &converted);
        ret = stage_set_property(adapter, widget, name, &converted);
    }
    return ret == MY_RET_OK ? MY_COMPOSE_OK : MY_COMPOSE_FAILED;
}

static void listener_callback(void *context, const char *event, void *data) {
    MyComposeMyuiListener *listener = (MyComposeMyuiListener *)context;
    MyComposeMyuiState *state;
    (void)event;
    (void)data;
    if (listener == NULL || listener->adapter == NULL) return;
    state = state_of(listener->adapter);
    if (state == NULL || state->window_closed || state->txn.suppress_events) return;
    state->store->event_callback_depth++;
    if (listener->adapter->fault.event_pump != NULL) {
        listener->adapter->fault.event_pump_status = my_compose_myui_pump(
            listener->adapter, listener->adapter->fault.event_pump);
    }
    listener->intent.owner = listener->owner;
    listener->intent.payload = listener->payload;
    (void)my_compose_store_dispatch(state->store, &listener->intent);
    state->store->event_callback_depth--;
}

static void listener_destroy(MyComposeMyuiListener *listener, bool window_closed) {
    if (listener == NULL || !listener->in_use) return;
    if (!window_closed && listener->widget != NULL && listener->id != 0u) {
        (void)my_widget_off(listener->widget, listener->id);
    }
    my_emitter_context_lease_invalidate(listener->lease);
    my_emitter_context_lease_unref(listener->lease);
    listener->lease = NULL;
    listener->id = 0u;
    listener->in_use = false;
}

static MyComposeMyuiListener *listener_allocate(MyComposeMyui *adapter,
    MyComposeMyuiState *state, my_widget_t *widget, MyComposeNodeHandle owner,
    const char *name, const MyComposeEventRecord *event) {
    MyComposeMyuiListener *listener = NULL;
    uint32_t i;
    uint32_t bank_offset;
    for (bank_offset = 0u; bank_offset < 2u && listener == NULL; ++bank_offset) {
        uint32_t bank = (state->txn.listener_bank + bank_offset) & 1u;
        for (i = 0u; i < MY_COMPOSE_MAX_EVENTS; ++i) {
            if (!state->listeners[bank][i].in_use) {
                listener = &state->listeners[bank][i];
                break;
            }
        }
    }
    if (listener == NULL) return NULL;
    memset(listener, 0, sizeof(*listener));
    listener->adapter = adapter;
    listener->widget = widget;
    listener->owner = owner;
    listener->intent.type = event->type;
    listener->intent.result = event->result;
    listener->intent.owner = owner;
    listener->intent.payload_size = event->payload_size;
    listener->intent.payload = listener->payload;
    if (event->payload_size != 0u) {
        memcpy(listener->payload, event->payload, event->payload_size);
    }
    snprintf(listener->name, sizeof(listener->name), "%s", name);
    listener->lease = my_emitter_context_lease_create(
        ((my_object_t *)widget)->allocator, listener, NULL);
    if (listener->lease == NULL) return NULL;
    listener->in_use = true;
    listener->id = my_widget_on_lease(widget, name, listener_callback,
        listener->lease);
    if (listener->id == 0u) {
        listener_destroy(listener, state->window_closed);
        return NULL;
    }
    return listener;
}

static int listener_slot(MyComposeMyuiListener *const *listeners,
    const char *name) {
    uint32_t i;
    for (i = 0u; i < MY_COMPOSE_MAX_EVENTS_PER_NODE; ++i) {
        if (listeners[i] != NULL && strcmp(listeners[i]->name, name) == 0) {
            return (int)i;
        }
    }
    for (i = 0u; i < MY_COMPOSE_MAX_EVENTS_PER_NODE; ++i) {
        if (listeners[i] == NULL) return (int)i;
    }
    return -1;
}

static MyComposeStatus stage_listener(MyComposeMyui *adapter,
    uint32_t node_index, const char *name, const MyComposeEventRecord *event) {
    MyComposeMyuiState *state = state_of(adapter);
    MyComposeMyuiTxnNode *node = &state->txn.nodes[node_index];
    MyComposeMyuiListenerChange *change;
    MyComposeMyuiListener *old_listener = NULL;
    MyComposeMyuiListener *new_listener = NULL;
    int slot = listener_slot(node->listeners, name);
    if (slot < 0 || state->txn.listener_change_count >= MY_COMPOSE_MAX_DIFF_OPS) {
        return MY_COMPOSE_OVERLOAD;
    }
    old_listener = node->listeners[slot];
    if (old_listener != NULL && strcmp(old_listener->name, name) != 0) {
        old_listener = NULL;
    }
    if (event != NULL) {
        new_listener = listener_allocate(adapter, state, node->widget,
            state->builder->next->nodes[node_index].handle, name, event);
        if (new_listener == NULL) return MY_COMPOSE_FAILED;
    }
    if (old_listener == NULL && new_listener == NULL) return MY_COMPOSE_OK;
    change = &state->txn.listener_changes[state->txn.listener_change_count++];
    change->old_listener = old_listener;
    change->new_listener = new_listener;
    node->listeners[slot] = new_listener;
    return MY_COMPOSE_OK;
}

static my_widget_t *create_widget(MyComposeMyui *adapter, const char *type) {
    MyComposeMyuiState *state = state_of(adapter);
    my_widget_t *widget;
    uint32_t attempt = ++state->txn.factory_attempts;
    adapter->stats.factory_calls++;
    if (adapter->fault.factory_call != 0u &&
        attempt == adapter->fault.factory_call) {
        return NULL;
    }
    if (!intrinsic_type(type)) {
        widget = my_widget_class_create(type, NULL);
        if (widget != NULL) {
            (void)my_widget_set_layouter(widget, my_layouter_default());
        }
        return widget;
    }
    if (strcmp(type, "@root") == 0) return my_widget_ref(state->root);
    if (strcmp(type, "@row") != 0 && strcmp(type, "@column") != 0 &&
        strcmp(type, "@stack") != 0) {
        return NULL;
    }
    widget = my_widget_create(NULL, type + 1u);
    if (widget == NULL) return NULL;
    if (strcmp(type, "@row") == 0 || strcmp(type, "@column") == 0) {
        my_layouter_t *layouter = my_layouter_linear_create(NULL,
            strcmp(type, "@row") == 0, 0);
        if (layouter == NULL) {
            my_widget_unref(widget);
            return NULL;
        }
        (void)my_widget_set_layouter(widget, layouter);
    } else {
        (void)my_widget_set_layouter(widget, my_layouter_default());
    }
    return widget;
}

static MyComposeStatus map_nodes(MyComposeMyui *adapter) {
    MyComposeMyuiState *state = state_of(adapter);
    const MyComposeTree *next = state->builder->next;
    uint32_t i;
    for (i = 0u; i < next->node_count; ++i) {
        const MyComposeNodeRecord *record = &next->nodes[i];
        MyComposeMyuiTxnNode *node = &state->txn.nodes[i];
        const char *type = next->strings + record->type_offset;
        if (strcmp(type, "@root") == 0) {
            MyComposeMyuiBinding *binding = find_binding(state, record->handle);
            node->widget = state->root;
            node->new_binding = binding == NULL;
            if (binding != NULL) {
                memcpy(node->listeners, binding->listeners,
                    sizeof(node->listeners));
            }
            continue;
        }
        if (record->match == MY_COMPOSE_MATCH_NODE) {
            MyComposeMyuiBinding *binding = find_binding(state, record->handle);
            if (binding == NULL) return MY_COMPOSE_CONFLICT;
            node->widget = binding->widget;
            memcpy(node->listeners, binding->listeners, sizeof(node->listeners));
            continue;
        }
        node->widget = create_widget(adapter, type);
        if (node->widget == NULL) return MY_COMPOSE_FAILED;
        node->owns_widget = true;
        node->new_binding = true;
    }
    return MY_COMPOSE_OK;
}

static MyComposeStatus stage_properties(MyComposeMyui *adapter,
    const MyComposeDiff *diff) {
    MyComposeMyuiState *state = state_of(adapter);
    const MyComposeTree *next = state->builder->next;
    uint32_t i;
    for (i = 0u; i < next->node_count; ++i) {
        const MyComposeNodeRecord *node = &next->nodes[i];
        uint32_t property;
        if (!state->txn.nodes[i].new_binding) continue;
        property = node->first_property;
        while (property != MY_COMPOSE_NO_INDEX) {
            const MyComposePropertyRecord *record = &next->properties[property];
            MyComposeStatus status = apply_property(adapter, i,
                next->strings + record->name_offset, &record->value);
            if (status != MY_COMPOSE_OK) return status;
            property = record->next;
        }
    }
    for (i = 0u; i < diff->count; ++i) {
        const MyComposeDiffOp *op = &diff->ops[i];
        uint32_t node_index;
        uint32_t property;
        const MyComposeValue *value = NULL;
        if (op->type != MY_COMPOSE_DIFF_UPDATE || op->on_event) continue;
        node_index = next_index(state, op->node);
        if (node_index == MY_COMPOSE_NO_INDEX) return MY_COMPOSE_CONFLICT;
        property = next->nodes[node_index].first_property;
        while (property != MY_COMPOSE_NO_INDEX) {
            const MyComposePropertyRecord *record = &next->properties[property];
            if (strcmp(next->strings + record->name_offset, op->name) == 0) {
                value = &record->value;
                break;
            }
            property = record->next;
        }
        {
            MyComposeStatus status = apply_property(adapter, node_index,
                op->name, value);
            if (status != MY_COMPOSE_OK) return status;
        }
    }
    return MY_COMPOSE_OK;
}

static MyComposeStatus stage_listeners(MyComposeMyui *adapter,
    const MyComposeDiff *diff) {
    MyComposeMyuiState *state = state_of(adapter);
    const MyComposeTree *next = state->builder->next;
    uint32_t i;
    for (i = 0u; i < next->node_count; ++i) {
        const MyComposeNodeRecord *node = &next->nodes[i];
        uint32_t event;
        if (!state->txn.nodes[i].owns_widget) continue;
        event = node->first_event;
        while (event != MY_COMPOSE_NO_INDEX) {
            const MyComposeEventRecord *record = &next->events[event];
            MyComposeStatus status = stage_listener(adapter, i,
                next->strings + record->name_offset, record);
            if (status != MY_COMPOSE_OK) return status;
            event = record->next;
        }
    }
    for (i = 0u; i < diff->count; ++i) {
        const MyComposeDiffOp *op = &diff->ops[i];
        uint32_t node_index;
        uint32_t event;
        const MyComposeEventRecord *record = NULL;
        if (op->type != MY_COMPOSE_DIFF_UPDATE || !op->on_event) continue;
        node_index = next_index(state, op->node);
        if (node_index == MY_COMPOSE_NO_INDEX) return MY_COMPOSE_CONFLICT;
        event = next->nodes[node_index].first_event;
        while (event != MY_COMPOSE_NO_INDEX) {
            const MyComposeEventRecord *candidate = &next->events[event];
            if (strcmp(next->strings + candidate->name_offset, op->name) == 0) {
                record = candidate;
                break;
            }
            event = candidate->next;
        }
        {
            MyComposeStatus status = stage_listener(adapter, node_index,
                op->name, record);
            if (status != MY_COMPOSE_OK) return status;
        }
    }
    return MY_COMPOSE_OK;
}

static MyComposeStatus collect_deletes(MyComposeMyuiState *state,
    const MyComposeDiff *diff) {
    uint32_t i;
    uint32_t j;
    for (i = 0u; i < diff->count; ++i) {
        const MyComposeDiffOp *op = &diff->ops[i];
        MyComposeMyuiDelete *delete;
        MyComposeMyuiBinding *binding;
        uint32_t old_index;
        const MyComposeNodeRecord *old_node;
        if (op->type != MY_COMPOSE_DIFF_DELETE) continue;
        if (state->txn.delete_count >= MY_COMPOSE_MAX_NODES) {
            return MY_COMPOSE_OVERLOAD;
        }
        binding = find_binding(state, op->node);
        old_index = current_index(state, op->node);
        if (binding == NULL || old_index == MY_COMPOSE_NO_INDEX) {
            return MY_COMPOSE_CONFLICT;
        }
        old_node = &state->builder->current->nodes[old_index];
        delete = &state->txn.deletes[state->txn.delete_count++];
        delete->widget = binding->widget;
        delete->handle = op->node;
        delete->current_index = old_index;
        delete->top = true;
        if (old_node->parent != MY_COMPOSE_NO_INDEX) {
            MyComposeMyuiBinding *parent = binding_for_current(state,
                old_node->parent);
            if (parent == NULL) return MY_COMPOSE_CONFLICT;
            delete->parent = parent->widget;
        }
        for (j = 0u; j < diff->count; ++j) {
            if (diff->ops[j].type == MY_COMPOSE_DIFF_DELETE && old_node->parent !=
                MY_COMPOSE_NO_INDEX && handle_equal(diff->ops[j].node,
                    state->builder->current->nodes[old_node->parent].handle)) {
                delete->top = false;
                break;
            }
        }
    }
    return MY_COMPOSE_OK;
}

static MyComposeStatus stage_structure(MyComposeMyui *adapter,
    const MyComposeDiff *diff) {
    MyComposeMyuiState *state = state_of(adapter);
    const MyComposeTree *next = state->builder->next;
    uint32_t i;
    MyComposeStatus status = collect_deletes(state, diff);
    if (status != MY_COMPOSE_OK) return status;
    for (i = 0u; i < next->node_count; ++i) {
        MyComposeMyuiTxnNode *node = &state->txn.nodes[i];
        my_widget_t *parent;
        if (!node->owns_widget) continue;
        if (next->nodes[i].parent == MY_COMPOSE_NO_INDEX) {
            parent = state->root;
        } else {
            parent = state->txn.nodes[next->nodes[i].parent].widget;
        }
        if (stage_insert(adapter, parent, node->widget) != MY_RET_OK) {
            return MY_COMPOSE_FAILED;
        }
    }
    for (i = 0u; i < next->node_count; ++i) {
        const MyComposeNodeRecord *parent = &next->nodes[i];
        uint32_t link = parent->first_child;
        my_widget_t *previous = NULL;
        while (link != MY_COMPOSE_NO_INDEX) {
            uint32_t child = next->child_links[link].node;
            my_widget_t *current = state->txn.nodes[child].widget;
            my_widget_t *parent_widget = state->txn.nodes[i].widget;
            if (previous != NULL) {
                size_t previous_index = child_index(parent_widget, previous);
                size_t current_position = child_index(parent_widget, current);
                if (previous_index == SIZE_MAX || current_position == SIZE_MAX) {
                    return MY_COMPOSE_CONFLICT;
                }
                if (current_position < previous_index &&
                    my_widget_reorder_child(parent_widget, current,
                        previous_index) != MY_RET_OK) {
                    return MY_COMPOSE_FAILED;
                }
            }
            previous = current;
            link = next->child_links[link].next;
        }
    }
    for (i = 0u; i < state->txn.delete_count; ++i) {
        MyComposeMyuiDelete *delete = &state->txn.deletes[i];
        my_widget_t *detached = NULL;
        if (!delete->top) continue;
        if (stage_detach(adapter, delete->parent, delete->widget,
                &detached) != MY_RET_OK || detached != delete->widget) {
            return MY_COMPOSE_FAILED;
        }
        delete->detached = true;
    }
    return MY_COMPOSE_OK;
}

static void rollback_structure(MyComposeMyuiState *state) {
    MyComposeMyuiTxn *txn = &state->txn;
    const MyComposeTree *next = state->builder->next;
    uint32_t i;
    for (i = next->node_count; i-- != 0u;) {
        MyComposeMyuiTxnNode *node = &txn->nodes[i];
        bool root;
        if (!node->owns_widget) continue;
        root = next->nodes[i].parent == MY_COMPOSE_NO_INDEX ||
            !txn->nodes[next->nodes[i].parent].owns_widget;
        if (root && node->widget != NULL && node->widget->parent != NULL) {
            raw_detach(node->widget->parent, node->widget);
        }
    }
    for (i = 0u; i < txn->delete_count; ++i) {
        MyComposeMyuiDelete *delete = &txn->deletes[i];
        if (delete->detached && delete->widget->parent == NULL) {
            raw_insert(delete->parent, delete->widget,
                my_widget_child_count(delete->parent));
            delete->detached = false;
        }
    }
    for (i = 0u; i < txn->original_parent_count; ++i) {
        MyComposeMyuiOriginalParent *parent = &txn->original_parents[i];
        size_t j;
        if (parent->count != 0u) {
            memcpy(parent->widget->children->items,
                txn->original_children + parent->offset,
                parent->count * sizeof(void *));
        }
        parent->widget->children->size = parent->count;
        for (j = 0u; j < parent->count; ++j) {
            txn->original_children[parent->offset + j]->parent = parent->widget;
        }
        my_widget_request_layout(parent->widget);
        my_widget_invalidate(parent->widget, NULL);
    }
}

static void discard_new_widgets(MyComposeMyuiState *state) {
    const MyComposeTree *next = state->builder->next;
    uint32_t i;
    for (i = next->node_count; i-- != 0u;) {
        MyComposeMyuiTxnNode *node = &state->txn.nodes[i];
        bool root;
        if (!node->owns_widget || node->widget == NULL) continue;
        root = next->nodes[i].parent == MY_COMPOSE_NO_INDEX ||
            !state->txn.nodes[next->nodes[i].parent].owns_widget;
        if (root) {
            if (node->widget->parent != NULL) raw_detach(node->widget->parent,
                node->widget);
            my_widget_unref(node->widget);
            node->widget = NULL;
        }
    }
}

static void discard_defaults(MyComposeMyuiDefault *defaults) {
    uint32_t i;
    for (i = 0u; i < MY_COMPOSE_MAX_PROPERTIES_PER_NODE; ++i) {
        if (defaults[i].used) my_value_reset(&defaults[i].value);
        memset(&defaults[i], 0, sizeof(defaults[i]));
    }
}

static void txn_reset(MyComposeMyuiState *state) {
    memset(&state->txn, 0, sizeof(state->txn));
}

static void rollback_internal(MyComposeMyui *adapter) {
    MyComposeMyuiState *state = state_of(adapter);
    uint32_t i;
    if (state == NULL || !state->txn.active) return;
    rollback_structure(state);
    for (i = state->txn.listener_change_count; i-- != 0u;) {
        listener_destroy(state->txn.listener_changes[i].new_listener,
            state->window_closed);
    }
    for (i = state->txn.property_count; i-- != 0u;) {
        MyComposeMyuiProperty *property = &state->txn.properties[i];
        discard_property(property, !property->skip_restore);
    }
    for (i = 0u; i < state->builder->next->node_count; ++i) {
        if (state->txn.nodes[i].new_binding) {
            discard_defaults(state->txn.nodes[i].defaults);
        }
    }
    discard_new_widgets(state);
    adapter->stats.rollbacks++;
    txn_reset(state);
}

static void clear_binding(MyComposeMyuiState *state,
    MyComposeMyuiBinding *binding) {
    uint32_t i;
    for (i = 0u; i < MY_COMPOSE_MAX_EVENTS_PER_NODE; ++i) {
        listener_destroy(binding->listeners[i], state->window_closed);
    }
    if (binding->owner_registered) {
        (void)my_compose_store_invalidate_owner(state->store, binding->handle);
    }
    discard_defaults(binding->defaults);
    memset(binding, 0, sizeof(*binding));
}

static void move_defaults(MyComposeMyuiDefault *destination,
    MyComposeMyuiDefault *source) {
    memcpy(destination, source, sizeof(MyComposeMyuiDefault) *
        MY_COMPOSE_MAX_PROPERTIES_PER_NODE);
    memset(source, 0, sizeof(MyComposeMyuiDefault) *
        MY_COMPOSE_MAX_PROPERTIES_PER_NODE);
}

static void commit_internal(MyComposeMyui *adapter) {
    MyComposeMyuiState *state = state_of(adapter);
    const MyComposeTree *next = state->txn.next;
    uint32_t i;
    if (!state->txn.active) return;
    for (i = 0u; i < state->txn.listener_change_count; ++i) {
        MyComposeMyuiListenerChange *change = &state->txn.listener_changes[i];
        if (change->old_listener != change->new_listener) {
            listener_destroy(change->old_listener, state->window_closed);
        }
    }
    for (i = 0u; i < state->txn.delete_count; ++i) {
        MyComposeMyuiDelete *delete = &state->txn.deletes[i];
        MyComposeMyuiBinding *binding = find_binding(state, delete->handle);
        if (binding != NULL) clear_binding(state, binding);
    }
    for (i = 0u; i < next->node_count; ++i) {
        const MyComposeNodeRecord *record = &next->nodes[i];
        MyComposeMyuiTxnNode *node = &state->txn.nodes[i];
        MyComposeMyuiBinding *binding = &state->bindings[record->handle.index];
        uint32_t j;
        uint32_t listener_count = 0u;
        if (node->new_binding) {
            if (binding->used) clear_binding(state, binding);
            binding->used = true;
            binding->handle = record->handle;
            binding->widget = node->widget;
            move_defaults(binding->defaults, node->defaults);
        } else if (node->owns_widget) {
            discard_defaults(node->defaults);
        }
        memcpy(binding->listeners, node->listeners, sizeof(binding->listeners));
        for (j = 0u; j < MY_COMPOSE_MAX_EVENTS_PER_NODE; ++j) {
            if (binding->listeners[j] != NULL) listener_count++;
        }
        if (listener_count != 0u && !binding->owner_registered) {
            (void)my_compose_store_register_owner(state->store, record->handle);
            binding->owner_registered = true;
        }
    }
    for (i = 0u; i < state->txn.property_count; ++i) {
        discard_property(&state->txn.properties[i], false);
    }
    for (i = 0u; i < state->txn.delete_count; ++i) {
        MyComposeMyuiDelete *delete = &state->txn.deletes[i];
        if (!delete->top || !delete->detached) continue;
        adapter->stats.notifies++;
        my_widget_notify_child_removed(delete->parent, delete->widget);
        my_widget_unref(delete->widget);
        delete->detached = false;
    }
    state->listener_bank = state->txn.listener_bank;
    adapter->stats.commits++;
    txn_reset(state);
    state->txn.suppress_events = false;
}

static my_ret_t async_command_execute(void *context) {
    MyComposeMyuiCommand *command = context;
    command->deliver(my_emitter_context_lease_context(command->lease),
        command->completion, command->result);
    return MY_RET_OK;
}

static void async_command_destroy(void *context) {
    MyComposeMyuiCommand *command = context;
    command->release(command->completion);
    my_emitter_context_lease_unref(command->lease);
    free(command);
}

static MyComposeStatus async_post(void *context, MyComposeAsyncDeliver deliver,
    MyComposeCompletionContext *completion, uint32_t result,
    MyComposeAsyncRelease release) {
    MyComposeMyuiAsync *async = context;
    MyComposeMyuiCommand *command;
    my_ui_command_t *ui_command;
    my_ret_t ret;
    unsigned int failures = atomic_load_explicit(&async->fail_posts,
        memory_order_acquire);
    while (failures > 0u) {
        if (atomic_compare_exchange_weak_explicit(&async->fail_posts, &failures,
                failures - 1u, memory_order_acq_rel, memory_order_acquire)) {
            release(completion);
            return MY_COMPOSE_OVERLOAD;
        }
    }
    if (my_ui_command_scope_is_closed(async->scope) ||
        !my_emitter_context_lease_is_valid(async->lease)) {
        release(completion);
        return MY_COMPOSE_CANCELLED;
    }
    command = calloc(1u, sizeof(*command));
    if (command == NULL) {
        release(completion);
        return MY_COMPOSE_OVERLOAD;
    }
    command->lease = my_emitter_context_lease_ref(async->lease);
    command->deliver = deliver;
    command->completion = completion;
    command->release = release;
    command->result = result;
    ui_command = my_ui_command_create(NULL, async_command_execute, command,
        async_command_destroy);
    if (ui_command == NULL) {
        async_command_destroy(command);
        return MY_COMPOSE_OVERLOAD;
    }
    ret = my_ui_command_submit_scoped(async->loop, async->scope, ui_command);
    my_ui_command_unref(ui_command);
    if (ret == MY_RET_OK) return MY_COMPOSE_OK;
    if (ret == MY_RET_PENDING && my_ui_command_scope_is_closed(async->scope)) {
        return MY_COMPOSE_CANCELLED;
    }
    return MY_COMPOSE_OVERLOAD;
}

static void async_close(void *context) {
    MyComposeMyuiAsync *async = context;
    my_emitter_context_lease_invalidate(async->lease);
    my_ui_command_scope_close(async->scope);
}

static void async_destroy(void *context) {
    MyComposeMyuiAsync *async = context;
    async_close(async);
    my_emitter_context_lease_unref(async->lease);
    my_ui_command_scope_unref(async->scope);
    free(async);
}

static MyComposeStatus async_create(MyComposeMyuiState *state) {
    MyComposeAsyncBridgeOps ops;
    MyComposeStatus status;
    state->async = calloc(1u, sizeof(*state->async));
    if (state->async == NULL) return MY_COMPOSE_OVERLOAD;
    state->async->loop = state->window->loop;
    state->async->scope = my_ui_command_scope_create(NULL);
    state->async->lease = my_emitter_context_lease_create(NULL, state->store,
        NULL);
    atomic_init(&state->async->fail_posts, 0u);
    if (state->async->loop == NULL || state->async->scope == NULL ||
        state->async->lease == NULL) {
        async_destroy(state->async);
        state->async = NULL;
        return MY_COMPOSE_OVERLOAD;
    }
    memset(&ops, 0, sizeof(ops));
    ops.context = state->async;
    ops.post = async_post;
    ops.close = async_close;
    ops.destroy = async_destroy;
    status = my_compose_store_set_async_bridge(state->store, &ops);
    if (status != MY_COMPOSE_OK) {
        async_destroy(state->async);
        state->async = NULL;
    }
    return status;
}

static void window_closed(void *context) {
    MyComposeMyui *adapter = (MyComposeMyui *)context;
    MyComposeMyuiState *state = state_of(adapter);
    if (state == NULL || state->window_closed) return;
    state->window_closed = true;
    my_compose_store_close(state->store);
    my_compose_store_reap(state->store);
}

MyComposeMyui *my_compose_myui_create(my_window_t *window,
    MyComposeTreeBuilder *builder, MyComposeStore *store) {
    MyComposeMyui *adapter;
    MyComposeMyuiState *state;
    if (window == NULL || builder == NULL || store == NULL) return NULL;
    adapter = (MyComposeMyui *)calloc(1u, sizeof(*adapter));
    if (adapter == NULL) return NULL;
    state = (MyComposeMyuiState *)calloc(1u, sizeof(*state));
    if (state == NULL) {
        free(adapter);
        return NULL;
    }
    adapter->state = state;
    state->window = window;
    state->root = my_window_widget(window);
    state->builder = builder;
    state->store = store;
    state->close_listener = my_window_add_close_listener(window, window_closed,
        adapter);
    if (state->close_listener == 0u || async_create(state) != MY_COMPOSE_OK) {
        if (state->close_listener != 0u) {
            (void)my_window_remove_close_listener(window, state->close_listener);
        }
        free(state);
        free(adapter);
        return NULL;
    }
    return adapter;
}

void my_compose_myui_destroy(MyComposeMyui *adapter) {
    MyComposeMyuiState *state = state_of(adapter);
    uint32_t bank;
    uint32_t i;
    if (state == NULL) {
        free(adapter);
        return;
    }
    rollback_internal(adapter);
    if (!state->window_closed && state->close_listener != 0u) {
        (void)my_window_remove_close_listener(state->window,
            state->close_listener);
    }
    for (bank = 0u; bank < 2u; ++bank) {
        for (i = 0u; i < MY_COMPOSE_MAX_EVENTS; ++i) {
            listener_destroy(&state->listeners[bank][i], state->window_closed);
        }
    }
    for (i = 0u; i < MY_COMPOSE_MAX_NODES; ++i) {
        if (state->bindings[i].used) discard_defaults(state->bindings[i].defaults);
    }
    free(state);
    free(adapter);
}

MyComposeStatus my_compose_myui_stage(MyComposeMyui *adapter,
    const MyComposeDiff *diff) {
    MyComposeMyuiState *state = state_of(adapter);
    MyComposeStatus status;
    if (state == NULL) return MY_COMPOSE_INVALID;
    if (state->txn.active) return MY_COMPOSE_CONFLICT;
    txn_reset(state);
    state->txn.next = state->builder->next;
    state->txn.active = true;
    state->txn.suppress_events = true;
    state->txn.listener_bank = state->listener_bank ^ 1u;
    status = preflight_diff(adapter, diff);
    if (status == MY_COMPOSE_OK) status = preflight_style_capacity(state, diff);
    if (status == MY_COMPOSE_OK) status = capture_original(state);
    if (status == MY_COMPOSE_OK) status = map_nodes(adapter);
    if (status == MY_COMPOSE_OK) status = stage_properties(adapter, diff);
    if (status == MY_COMPOSE_OK) status = stage_listeners(adapter, diff);
    if (status == MY_COMPOSE_OK) status = stage_structure(adapter, diff);
    if (status != MY_COMPOSE_OK) rollback_internal(adapter);
    return status;
}

void my_compose_myui_commit(MyComposeMyui *adapter) {
    MyComposeMyuiState *state = state_of(adapter);
    if (state == NULL || state->builder->state != MY_COMPOSE_BUILD_IDLE) return;
    commit_internal(adapter);
}

void my_compose_myui_rollback(MyComposeMyui *adapter) {
    rollback_internal(adapter);
}

MyComposeStatus my_compose_myui_pump(MyComposeMyui *adapter,
    MyComposeRuntime *runtime) {
    MyComposeMyuiState *state = state_of(adapter);
    if (state == NULL || runtime == NULL) return MY_COMPOSE_INVALID;
    if (!my_compose_runtime_internal_matches(runtime, state->store, adapter)) {
        return MY_COMPOSE_CONFLICT;
    }
    return my_compose_runtime_pump(runtime);
}

static MyComposeStatus sink_stage(void *context, const MyComposeDiff *diff) {
    return my_compose_myui_stage((MyComposeMyui *)context, diff);
}

static void sink_commit(void *context) {
    my_compose_myui_commit((MyComposeMyui *)context);
}

static void sink_rollback(void *context) {
    my_compose_myui_rollback((MyComposeMyui *)context);
}

MyComposeSinkOps my_compose_myui_sink(MyComposeMyui *adapter) {
    MyComposeSinkOps sink;
    MyComposeMyuiState *state = state_of(adapter);
    memset(&sink, 0, sizeof(sink));
    sink.context = adapter;
    sink.store = state != NULL ? state->store : NULL;
    sink.stage = sink_stage;
    sink.commit = sink_commit;
    sink.rollback = sink_rollback;
    return sink;
}

my_widget_t *my_compose_myui_widget(const MyComposeMyui *adapter,
    MyComposeNodeHandle node) {
    MyComposeMyuiState *state = state_of((MyComposeMyui *)adapter);
    MyComposeMyuiBinding *binding;
    if (state == NULL) return NULL;
    binding = find_binding(state, node);
    return binding != NULL ? binding->widget : NULL;
}

void my_compose_myui_internal_fail_async_posts(MyComposeMyui *adapter,
    uint32_t count) {
    MyComposeMyuiState *state = state_of(adapter);
    if (state == NULL || state->async == NULL) return;
    atomic_store_explicit(&state->async->fail_posts, count, memory_order_release);
}

MyComposeStatus my_compose_myui_internal_seed_generation(
    MyComposeMyui *adapter, MyComposeNodeHandle handle, uint32_t generation) {
    MyComposeMyuiState *state = state_of(adapter);
    MyComposeMyuiBinding *binding;
    MyComposeStatus status;
    uint32_t i;
    if (state == NULL || state->txn.active || generation == 0u) {
        return MY_COMPOSE_INVALID;
    }
    binding = find_binding(state, handle);
    if (binding == NULL) return MY_COMPOSE_STALE;
    status = my_compose_tree_builder_internal_seed_generation(state->builder,
        handle, generation);
    if (status != MY_COMPOSE_OK) return status;
    binding->handle.generation = generation;
    for (i = 0u; i < MY_COMPOSE_MAX_EVENTS_PER_NODE; ++i) {
        if (binding->listeners[i] != NULL) {
            binding->listeners[i]->owner.generation = generation;
            binding->listeners[i]->intent.owner.generation = generation;
        }
    }
    if (binding->owner_registered) {
        MyComposeOwner *owner = &state->store->owners[handle.index];
        owner->generation = generation;
        owner->active = true;
        owner->retired = false;
    }
    return MY_COMPOSE_OK;
}
