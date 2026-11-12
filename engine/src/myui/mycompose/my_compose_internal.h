#ifndef MY_COMPOSE_INTERNAL_H
#define MY_COMPOSE_INTERNAL_H

#include <myui/mycompose/my_compose_remember.h>
#include <myui/mycompose/my_compose_tree.h>

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define MY_COMPOSE_NO_INDEX UINT32_MAX

typedef enum MyComposeMatch {
    MY_COMPOSE_MATCH_NONE = 0,
    MY_COMPOSE_MATCH_NODE,
    MY_COMPOSE_MATCH_REPLACE
} MyComposeMatch;

typedef enum MyComposeBuildState {
    MY_COMPOSE_BUILD_IDLE = 0,
    MY_COMPOSE_BUILD_NODES,
    MY_COMPOSE_BUILD_ENDED
} MyComposeBuildState;

typedef struct MyComposeNodeRecord {
    MyComposeNodeHandle handle;
    uint32_t parent;
    uint32_t previous;
    MyComposeMatch match;
    uint32_t key_offset;
    uint32_t type_offset;
    uint32_t depth;
    uint32_t child_index;
    uint32_t first_child;
    uint32_t last_child;
    uint32_t child_count;
    uint32_t first_property;
    uint32_t last_property;
    uint32_t property_count;
    uint32_t first_event;
    uint32_t last_event;
    uint32_t event_count;
} MyComposeNodeRecord;

typedef struct MyComposeChildLink {
    uint32_t node;
    uint32_t next;
} MyComposeChildLink;

typedef struct MyComposePropertyRecord {
    uint32_t name_offset;
    MyComposeValue value;
    uint32_t next;
} MyComposePropertyRecord;

typedef struct MyComposeEventRecord {
    uint32_t name_offset;
    uint32_t type;
    uint32_t payload_size;
    uint32_t result;
    uint8_t payload[MY_COMPOSE_MESSAGE_BYTES];
    uint32_t next;
} MyComposeEventRecord;

typedef struct MyComposeTree {
    MyComposeNodeRecord nodes[MY_COMPOSE_MAX_NODES];
    MyComposeChildLink child_links[MY_COMPOSE_MAX_CHILD_LINKS];
    MyComposePropertyRecord properties[MY_COMPOSE_MAX_PROPERTIES];
    MyComposeEventRecord events[MY_COMPOSE_MAX_EVENTS];
    char strings[MY_COMPOSE_STRING_BYTES];
    uint32_t node_count;
    uint32_t child_link_count;
    uint32_t property_count;
    uint32_t event_count;
    uint32_t string_used;
} MyComposeTree;

typedef struct MyComposeSlot {
    uint32_t generation;
    uint32_t next_generation;
    bool in_use;
    bool retired;
    bool reserved;
} MyComposeSlot;

typedef enum MyComposeRememberState {
    MY_COMPOSE_REMEMBER_FREE = 0,
    MY_COMPOSE_REMEMBER_CURRENT,
    MY_COMPOSE_REMEMBER_CANDIDATE
} MyComposeRememberState;

typedef union MyComposeRememberStorage {
    max_align_t alignment;
    uint8_t bytes[MY_COMPOSE_REMEMBER_BYTES];
} MyComposeRememberStorage;

typedef struct MyComposeRememberSlot {
    MyComposeRememberStorage storage;
    MyComposeRememberOps ops;
    MyComposeNodeHandle owner;
    uint64_t type_tag;
    uint32_t local_slot;
    uint32_t size;
    uint32_t alignment;
    MyComposeRememberState state;
} MyComposeRememberSlot;

struct MyComposeTreeBuilder {
    MyComposeTree storage[2];
    MyComposeTree *current;
    MyComposeTree *next;
    MyComposeSlot slots[MY_COMPOSE_MAX_NODES];
    MyComposeRememberSlot remember_slots[MY_COMPOSE_MAX_REMEMBER_SLOTS];
    MyComposeDiffOp diff_ops[MY_COMPOSE_MAX_DIFF_OPS];
    MyComposeDiff diff;
    MyComposeBuildState state;
};

uint32_t my_compose_tree_internal_find_node(const MyComposeTree *tree,
    MyComposeNodeHandle handle);
bool my_compose_tree_internal_old_node_is_retained(const MyComposeTree *next,
    uint32_t old_index);

void my_compose_remember_abort(MyComposeTreeBuilder *builder);
void my_compose_remember_finalize(MyComposeTreeBuilder *builder);
void my_compose_remember_destroy(MyComposeTreeBuilder *builder);
void my_compose_remember_reseed(MyComposeTreeBuilder *builder,
    MyComposeNodeHandle handle, uint32_t generation);

MyComposeStatus my_compose_tree_builder_internal_seed_generation(
    MyComposeTreeBuilder *builder, MyComposeNodeHandle handle,
    uint32_t generation);

#ifdef __cplusplus
}
#endif

#endif
