#ifndef MY_COMPOSE_H
#define MY_COMPOSE_H

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define MY_COMPOSE_MAX_NODES 256u
#define MY_COMPOSE_MAX_CHILD_LINKS 255u
#define MY_COMPOSE_MAX_DEPTH 32u
#define MY_COMPOSE_MAX_PROPERTIES 512u
#define MY_COMPOSE_MAX_PROPERTIES_PER_NODE 64u
#define MY_COMPOSE_MAX_EVENTS 256u
#define MY_COMPOSE_MAX_EVENTS_PER_NODE 32u
#define MY_COMPOSE_MAX_DIFF_OPS 1024u
#define MY_COMPOSE_STRING_BYTES 65536u
#define MY_COMPOSE_STATE_BYTES 16384u
#define MY_COMPOSE_INTENT_CAPACITY 64u
#define MY_COMPOSE_EFFECT_CAPACITY 32u
#define MY_COMPOSE_COMPLETION_CAPACITY 32u
#define MY_COMPOSE_MESSAGE_BYTES 256u
#define MY_COMPOSE_MAX_EFFECTS_PER_INTENT 8u
#define MY_COMPOSE_KEY_BYTES 64u
#define MY_COMPOSE_TYPE_BYTES 64u
#define MY_COMPOSE_NAME_BYTES 64u

typedef struct MyComposeTreeBuilder MyComposeTreeBuilder;

typedef enum MyComposeStatus {
    MY_COMPOSE_OK = 0,
    MY_COMPOSE_INVALID,
    MY_COMPOSE_STALE,
    MY_COMPOSE_OVERLOAD,
    MY_COMPOSE_DUPLICATE_KEY,
    MY_COMPOSE_TYPE_MISMATCH,
    MY_COMPOSE_NOT_SUPPORTED,
    MY_COMPOSE_CONFLICT,
    MY_COMPOSE_PENDING,
    MY_COMPOSE_CANCELLED,
    MY_COMPOSE_FAILED
} MyComposeStatus;

typedef struct MyComposeNodeHandle {
    uint32_t index;
    uint32_t generation;
} MyComposeNodeHandle;

typedef struct MyComposeString {
    const char *data;
    uint32_t size;
} MyComposeString;

typedef enum MyComposeValueType {
    MY_COMPOSE_VALUE_NONE = 0,
    MY_COMPOSE_VALUE_BOOL,
    MY_COMPOSE_VALUE_INT32,
    MY_COMPOSE_VALUE_UINT32,
    MY_COMPOSE_VALUE_INT64,
    MY_COMPOSE_VALUE_FLOAT,
    MY_COMPOSE_VALUE_DOUBLE,
    MY_COMPOSE_VALUE_STRING,
    MY_COMPOSE_VALUE_COLOR
} MyComposeValueType;

typedef struct MyComposeValue {
    MyComposeValueType type;
    union {
        bool bool_value;
        int32_t int32_value;
        uint32_t uint32_value;
        int64_t int64_value;
        float float_value;
        double double_value;
        MyComposeString string;
        uint32_t color;
    } as;
} MyComposeValue;

typedef struct MyComposeIntent {
    uint32_t type;
    uint32_t payload_size;
    const uint8_t *payload;
    MyComposeNodeHandle owner;
    uint32_t result;
} MyComposeIntent;

typedef struct MyComposeNodeDesc {
    MyComposeNodeHandle parent;
    const char *key;
    const char *type;
} MyComposeNodeDesc;

typedef enum MyComposeDiffType {
    MY_COMPOSE_DIFF_CREATE = 0,
    MY_COMPOSE_DIFF_UPDATE,
    MY_COMPOSE_DIFF_MOVE,
    MY_COMPOSE_DIFF_DELETE
} MyComposeDiffType;

typedef struct MyComposeDiffOp {
    MyComposeDiffType type;
    MyComposeNodeHandle node;
    MyComposeNodeHandle parent;
    uint32_t from_index;
    uint32_t to_index;
    const char *name;
    bool on_event;
} MyComposeDiffOp;

typedef struct MyComposeDiff {
    const MyComposeDiffOp *ops;
    uint32_t count;
} MyComposeDiff;

#ifdef __cplusplus
}
#endif

#endif
