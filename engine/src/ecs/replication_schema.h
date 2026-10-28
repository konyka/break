#pragma once

#include <core/types.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct BreakComponentSchemaRegistry BreakComponentSchemaRegistry;

typedef bool (*BreakComponentEncodeFn)(const void *value, usize value_size,
                                       void *out, usize out_capacity,
                                       usize *out_size);
typedef bool (*BreakComponentDecodeFn)(const void *data, usize data_size,
                                       void *value, usize value_capacity);

typedef struct {
    u32 component_id;
    u32 version;
    usize size;
    usize alignment;
    u32 flags;
    BreakComponentEncodeFn encode;
    BreakComponentDecodeFn decode;
} BreakComponentSchema;

enum {
    BREAK_SCHEMA_FLAG_DETERMINISTIC_POD = 1u << 0,
    BREAK_SCHEMA_FLAG_RAW_BYTES          = 1u << 1,
    BREAK_SCHEMA_FLAG_POINTER_CONTAINING = 1u << 2,
    BREAK_SCHEMA_FLAG_RESOURCE_REFERENCE = 1u << 3,
    BREAK_SCHEMA_FLAG_DERIVED_CACHE      = 1u << 4
};

typedef enum {
    BREAK_SCHEMA_OK = 0,
    BREAK_SCHEMA_INVALID_ARGUMENT,
    BREAK_SCHEMA_OUT_OF_MEMORY,
    BREAK_SCHEMA_DUPLICATE,
    BREAK_SCHEMA_INVALID_SIZE,
    BREAK_SCHEMA_INVALID_ALIGNMENT,
    BREAK_SCHEMA_UNSUPPORTED_POLICY
} BreakSchemaResult;

BreakComponentSchemaRegistry *break_schema_registry_create(void);
void break_schema_registry_destroy(BreakComponentSchemaRegistry *registry);
BreakSchemaResult break_schema_register(BreakComponentSchemaRegistry *registry,
                                        const BreakComponentSchema *schema);
const BreakComponentSchema *break_schema_lookup(
    const BreakComponentSchemaRegistry *registry, u32 component_id);
u64 break_schema_hash(const BreakComponentSchemaRegistry *registry);

#ifdef __cplusplus
}
#endif
