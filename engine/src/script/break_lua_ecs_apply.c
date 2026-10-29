#include "script/break_lua_ecs_apply.h"

#include <float.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

static const BreakLuaEcsField *find_field(const BreakLuaEcsField *schema,
                                          usize schema_count,
                                          const BreakLuaEcsRecord *rec)
{
    usize i;
    if (schema == NULL) {
        return NULL;
    }
    for (i = 0u; i < schema_count; i++) {
        if (schema[i].component != NULL && schema[i].field != NULL &&
            strncmp(schema[i].component, rec->component,
                    BREAK_LUA_ECS_NAME_CAPACITY) == 0 &&
            strncmp(schema[i].field, rec->field,
                    BREAK_LUA_ECS_NAME_CAPACITY) == 0) {
            return &schema[i];
        }
    }
    return NULL;
}

static bool to_f32(const BreakLuaEcsRecord *rec, f32 *out)
{
    f64 v;
    switch ((BreakLuaEcsValueKind)rec->value_type) {
    case BREAK_LUA_ECS_VALUE_NUMBER:
        v = rec->value.n;
        break;
    case BREAK_LUA_ECS_VALUE_BOOL:
        *out = rec->value.b ? 1.0f : 0.0f;
        return true;
    case BREAK_LUA_ECS_VALUE_STRING: {
        char buf[BREAK_LUA_ECS_VALUE_STRING_CAPACITY];
        char *end = NULL;
        usize len = rec->value.s.len;
        if (len == 0u || len >= sizeof(buf)) {
            return false;
        }
        memcpy(buf, rec->value.s.data, len);
        buf[len] = '\0';
        v = strtod(buf, &end);
        if (end == NULL || *end != '\0') {
            return false;
        }
        break;
    }
    default:
        return false;
    }
    if (!isfinite(v) || v > (f64)FLT_MAX || v < -(f64)FLT_MAX) {
        return false;
    }
    *out = (f32)v;
    return true;
}

bool break_lua_ecs_apply(World *world, const BreakLuaEcsField *schema,
                         usize schema_count, const BreakLuaEcsRecord *records,
                         usize count, BreakLuaEcsApplyReport *report)
{
    Entity target = ENTITY_NULL;
    usize i;
    if (report == NULL) {
        return false;
    }
    memset(report, 0, sizeof(*report));
    report->last_spawned = ENTITY_NULL;
    if (world == NULL || (records == NULL && count > 0u)) {
        return false;
    }
    for (i = 0u; i < count; i++) {
        const BreakLuaEcsRecord *rec = &records[i];
        if (rec->kind == BREAK_LUA_ECS_RECORD_SPAWN) {
            Entity e = world_create_entity(world);
            if (!entity_valid(e)) {
                report->rejected++;
                target = ENTITY_NULL;
                continue;
            }
            target = e;
            report->last_spawned = e;
            report->spawned++;
        } else if (rec->kind == BREAK_LUA_ECS_RECORD_SET) {
            const BreakLuaEcsField *f = find_field(schema, schema_count, rec);
            f32 value;
            u8 *comp;
            u32 size;
            if (!entity_valid(target) || f == NULL ||
                f->component_id >= ECS_MAX_COMPONENTS || !to_f32(rec, &value)) {
                report->rejected++;
                continue;
            }
            size = world->component_sizes[f->component_id];
            if (size < sizeof(f32) || f->offset > size - (u32)sizeof(f32)) {
                report->rejected++;
                continue;
            }
            comp = (u8 *)world_get_component(world, target, f->component_id);
            if (comp == NULL) {
                comp = (u8 *)world_add_component(world, target, f->component_id);
                if (comp == NULL) {
                    report->rejected++;
                    continue;
                }
                memset(comp, 0, size);
            }
            memcpy(comp + f->offset, &value, sizeof(value));
            report->set++;
        } else {
            report->rejected++;
        }
    }
    return true;
}
