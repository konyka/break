#pragma once
/* Applies drained break_lua ECS batch records to a runtime ECS World.
 *
 * break_lua itself never touches a World (its batch is a plain record
 * queue). This helper is the host side: the host describes which
 * component fields scripts may write (a schema of f32 fields by component
 * and field name), drains the batch, and calls break_lua_ecs_apply.
 *
 * Semantics, per call, records applied in order:
 *   SPAWN -> world_create_entity; that entity becomes the SET target.
 *   SET   -> writes one f32 field of the current target. The component is
 *            added (zero-initialized) if the entity does not have it yet.
 *            Value: finite number, bool (1/0) or a string that parses fully
 *            as a finite f32.
 * A record is rejected (counted, nothing written) when: no SPAWN preceded
 * it in this call, the component/field pair is not in the schema, the
 * component is not registered in the World with a size that covers the
 * field, or the value does not convert. Rejections never stop the call.
 * Pure C, no allocation; World access happens on the calling thread. */

#include <ecs/ecs.h>
#include <script/break_lua.h>

typedef struct BreakLuaEcsField {
    const char *component; /* script-visible component name (borrowed) */
    const char *field;     /* script-visible field name (borrowed) */
    ComponentType component_id;
    u32 offset;            /* byte offset of the f32 inside the component */
} BreakLuaEcsField;

typedef struct BreakLuaEcsApplyReport {
    usize spawned;
    usize set;
    usize rejected;
    Entity last_spawned;   /* ENTITY_NULL when nothing was spawned */
} BreakLuaEcsApplyReport;

/* Returns false (report zeroed) for NULL world/report or records == NULL
 * with count > 0; otherwise true, with the counts in *report. */
bool break_lua_ecs_apply(World *world, const BreakLuaEcsField *schema,
                         usize schema_count, const BreakLuaEcsRecord *records,
                         usize count, BreakLuaEcsApplyReport *report);
