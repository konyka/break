#include <ecs/replication_schema.h>
#include <ecs/ecs.h>

#include <stdlib.h>
#include <stdint.h>

struct BreakComponentSchemaRegistry {
    BreakComponentSchema *schemas;
    usize count;
    usize capacity;
};

static u64 hash_bytes(u64 hash, const void *data, usize size) {
    const u8 *bytes = (const u8 *)data;
    for (usize i = 0u; i < size; ++i) {
        hash ^= bytes[i];
        hash *= UINT64_C(1099511628211);
    }
    return hash;
}

static bool valid_alignment(usize alignment) {
    return alignment != 0u && (alignment & (alignment - 1u)) == 0u;
}

BreakComponentSchemaRegistry *break_schema_registry_create(void) {
    return (BreakComponentSchemaRegistry *)calloc(1u, sizeof(BreakComponentSchemaRegistry));
}

void break_schema_registry_destroy(BreakComponentSchemaRegistry *registry) {
    if (!registry) return;
    free(registry->schemas);
    free(registry);
}

const BreakComponentSchema *break_schema_lookup(
    const BreakComponentSchemaRegistry *registry, u32 component_id) {
    if (!registry) return NULL;
    for (usize i = 0u; i < registry->count; ++i) {
        if (registry->schemas[i].component_id == component_id) {
            return &registry->schemas[i];
        }
    }
    return NULL;
}

BreakSchemaResult break_schema_register(BreakComponentSchemaRegistry *registry,
                                        const BreakComponentSchema *schema) {
    if (!registry || !schema || schema->component_id >= ECS_MAX_COMPONENTS)
        return BREAK_SCHEMA_INVALID_ARGUMENT;
    if (schema->size == 0u) return BREAK_SCHEMA_INVALID_SIZE;
    if (!valid_alignment(schema->alignment)) return BREAK_SCHEMA_INVALID_ALIGNMENT;
    if ((schema->flags & BREAK_SCHEMA_FLAG_RAW_BYTES) != 0u &&
        (schema->flags & BREAK_SCHEMA_FLAG_DETERMINISTIC_POD) == 0u) {
        return BREAK_SCHEMA_UNSUPPORTED_POLICY;
    }
    if ((schema->flags & BREAK_SCHEMA_FLAG_RAW_BYTES) != 0u &&
        (schema->flags & BREAK_SCHEMA_FLAG_POINTER_CONTAINING) != 0u) {
        return BREAK_SCHEMA_UNSUPPORTED_POLICY;
    }
    if (break_schema_lookup(registry, schema->component_id) != NULL) {
        return BREAK_SCHEMA_DUPLICATE;
    }

    if (registry->count == registry->capacity) {
        if (registry->capacity > (usize)-1 / 2u && registry->capacity != 0u) {
            return BREAK_SCHEMA_OUT_OF_MEMORY;
        }
        usize new_capacity = registry->capacity == 0u ? 8u : registry->capacity * 2u;
        if (new_capacity > (usize)-1 / sizeof(BreakComponentSchema)) {
            return BREAK_SCHEMA_OUT_OF_MEMORY;
        }
        BreakComponentSchema *schemas = (BreakComponentSchema *)realloc(
            registry->schemas, new_capacity * sizeof(BreakComponentSchema));
        if (!schemas) return BREAK_SCHEMA_OUT_OF_MEMORY;
        registry->schemas = schemas;
        registry->capacity = new_capacity;
    }
    registry->schemas[registry->count++] = *schema;
    return BREAK_SCHEMA_OK;
}

u64 break_schema_hash(const BreakComponentSchemaRegistry *registry) {
    u64 hash = UINT64_C(1469598103934665603);
    if (!registry) return hash;
    u32 last_component_id = 0u;
    bool have_last = false;
    for (usize ordinal = 0u; ordinal < registry->count; ++ordinal) {
        const BreakComponentSchema *schema = NULL;
        for (usize i = 0u; i < registry->count; ++i) {
            const BreakComponentSchema *candidate = &registry->schemas[i];
            if (have_last && candidate->component_id <= last_component_id) continue;
            if (!schema || candidate->component_id < schema->component_id) schema = candidate;
        }
        if (!schema) break;
        last_component_id = schema->component_id;
        have_last = true;
        hash = hash_bytes(hash, &schema->component_id, sizeof(schema->component_id));
        hash = hash_bytes(hash, &schema->version, sizeof(schema->version));
        hash = hash_bytes(hash, &schema->size, sizeof(schema->size));
        hash = hash_bytes(hash, &schema->alignment, sizeof(schema->alignment));
        hash = hash_bytes(hash, &schema->flags, sizeof(schema->flags));
        hash = hash_bytes(hash, &(u8){schema->encode != NULL}, sizeof(u8));
        hash = hash_bytes(hash, &(u8){schema->decode != NULL}, sizeof(u8));
    }
    return hash;
}
