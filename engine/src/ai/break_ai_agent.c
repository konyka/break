#include <ai/break_ai_internal.h>
#include <math.h>

static bool entity_equal(Entity a, Entity b) {
    return a.index == b.index && a.generation == b.generation;
}

static bool agent_vec_ok(Vec3 value) {
    return isfinite(value.e[0]) && isfinite(value.e[1]) && isfinite(value.e[2]);
}

static bool agent_desc_ok(const BreakAiAgentDesc *desc) {
    return desc && agent_vec_ok(desc->position) && agent_vec_ok(desc->velocity) &&
           isfinite(desc->radius) && isfinite(desc->max_speed) &&
           desc->radius > 0.0f && desc->max_speed > 0.0f;
}

u32 break_ai_agent_index(const BreakAiRuntime *runtime, Entity entity) {
    if (!runtime || !entity_valid(entity)) {
        return UINT32_MAX;
    }
    for (u32 i = 0; i < runtime->max_agents; i++) {
        if (runtime->agents[i].live && entity_equal(runtime->agents[i].entity, entity)) {
            return i;
        }
    }
    return UINT32_MAX;
}

BreakNavError break_ai_agent_add(BreakAiRuntime *runtime, Entity entity,
                                 const BreakAiAgentDesc *desc) {
    if (!runtime || !desc) {
        return BREAK_NAV_INVALID;
    }
    if (!break_ai_is_owner(runtime)) {
        return BREAK_NAV_REJECTED;
    }
    if (!entity_valid(entity) || !agent_desc_ok(desc)) {
        return BREAK_NAV_INVALID;
    }
    if (break_ai_agent_index(runtime, entity) != UINT32_MAX) {
        return BREAK_NAV_REJECTED;
    }
    u32 free_index = runtime->max_agents;
    for (u32 i = 0; i < runtime->max_agents; i++) {
        if (!runtime->agents[i].live) {
            free_index = i;
            break;
        }
    }
    if (free_index == runtime->max_agents) {
        return BREAK_NAV_OVERLOAD;
    }
    runtime->agents[free_index].entity = entity;
    runtime->agents[free_index].desc = *desc;
    runtime->agents[free_index].live = true;
    return BREAK_NAV_OK;
}

BreakNavError break_ai_agent_update(BreakAiRuntime *runtime, Entity entity,
                                    const BreakAiAgentDesc *desc) {
    if (!runtime || !desc) {
        return BREAK_NAV_INVALID;
    }
    if (!break_ai_is_owner(runtime)) {
        return BREAK_NAV_REJECTED;
    }
    if (!entity_valid(entity) || !agent_desc_ok(desc)) {
        return BREAK_NAV_INVALID;
    }
    u32 index = break_ai_agent_index(runtime, entity);
    if (index == UINT32_MAX) {
        return BREAK_NAV_STALE;
    }
    runtime->agents[index].desc = *desc;
    return BREAK_NAV_OK;
}

BreakNavError break_ai_agent_remove(BreakAiRuntime *runtime, Entity entity) {
    if (!runtime) {
        return BREAK_NAV_INVALID;
    }
    if (!break_ai_is_owner(runtime)) {
        return BREAK_NAV_REJECTED;
    }
    u32 index = break_ai_agent_index(runtime, entity);
    if (index == UINT32_MAX) {
        return BREAK_NAV_STALE;
    }
    for (u32 i = 0; i < runtime->max_formations; i++) {
        if (!runtime->formations[i].live) {
            continue;
        }
        for (u32 n = 0; n < runtime->formations[i].member_count; n++) {
            if (entity_equal(runtime->formations[i].members[n], entity)) {
                return BREAK_NAV_REJECTED;
            }
        }
    }
    for (u32 i = 0; i < runtime->max_smart_objects; i++) {
        if (runtime->smart_objects[i].live &&
            entity_equal(runtime->smart_objects[i].owner, entity)) {
            return BREAK_NAV_REJECTED;
        }
    }
    runtime->agents[index].live = false;
    return BREAK_NAV_OK;
}

typedef struct BreakAiScoredNeighbor {
    BreakSteerAgent agent;
    Entity entity;
    f32 distance_sq;
} BreakAiScoredNeighbor;

static bool neighbor_before(const BreakAiScoredNeighbor *a, Entity entity, f32 distance_sq) {
    if (distance_sq != a->distance_sq) {
        return distance_sq < a->distance_sq;
    }
    if (entity.index != a->entity.index) {
        return entity.index < a->entity.index;
    }
    return entity.generation < a->entity.generation;
}

BreakNavError break_ai_agent_avoid(BreakAiRuntime *runtime, Entity self,
                                   Vec3 desired_velocity, f32 horizon,
                                   Vec3 *out_velocity) {
    if (!runtime || !out_velocity) {
        return BREAK_NAV_INVALID;
    }
    if (!break_ai_is_owner(runtime)) {
        return BREAK_NAV_REJECTED;
    }
    u32 self_index = break_ai_agent_index(runtime, self);
    if (self_index == UINT32_MAX) {
        return BREAK_NAV_STALE;
    }
    BreakAiScoredNeighbor nearest[BREAK_STEER_MAX_NEIGHBORS];
    u32 count = 0;
    for (u32 i = 0; i < runtime->max_agents; i++) {
        if (i == self_index || !runtime->agents[i].live) {
            continue;
        }
        const BreakAiAgentSlot *slot = &runtime->agents[i];
        f32 dx = slot->desc.position.e[0] - runtime->agents[self_index].desc.position.e[0];
        f32 dz = slot->desc.position.e[2] - runtime->agents[self_index].desc.position.e[2];
        f32 distance_sq = dx * dx + dz * dz;
        u32 insert = count;
        for (u32 n = 0; n < count; n++) {
            if (neighbor_before(&nearest[n], slot->entity, distance_sq)) {
                insert = n;
                break;
            }
        }
        if (insert >= BREAK_STEER_MAX_NEIGHBORS) {
            continue;
        }
        u32 new_count = count < BREAK_STEER_MAX_NEIGHBORS ? count + 1u : count;
        for (u32 n = new_count - 1u; n > insert; n--) {
            nearest[n] = nearest[n - 1u];
        }
        nearest[insert].agent.position = slot->desc.position;
        nearest[insert].agent.velocity = slot->desc.velocity;
        nearest[insert].agent.radius = slot->desc.radius;
        nearest[insert].entity = slot->entity;
        nearest[insert].distance_sq = distance_sq;
        count = new_count;
    }
    BreakSteerAgent neighbors[BREAK_STEER_MAX_NEIGHBORS];
    for (u32 i = 0; i < count; i++) {
        neighbors[i] = nearest[i].agent;
    }
    const BreakAiAgentDesc *desc = &runtime->agents[self_index].desc;
    return break_steer_avoid_velocity(desc->position, desc->velocity, desc->radius,
                                      desc->max_speed, desired_velocity,
                                      neighbors, count, horizon, out_velocity);
}
