#include <ai/break_ai_internal.h>
#include <math.h>

static bool formation_vec_ok(Vec3 value) {
    return isfinite(value.e[0]) && isfinite(value.e[1]) && isfinite(value.e[2]);
}

static bool formation_entity_equal(Entity a, Entity b) {
    return a.index == b.index && a.generation == b.generation;
}

static BreakNavError formation_slot_at(const BreakAiRuntime *runtime,
                                       BreakAiFormationHandle handle, u32 *out_index) {
    if (handle.index >= runtime->max_formations ||
        !runtime->formations[handle.index].live ||
        runtime->formations[handle.index].generation != handle.generation ||
        handle.generation == 0) {
        return BREAK_NAV_STALE;
    }
    *out_index = handle.index;
    return BREAK_NAV_OK;
}

static void formation_compute_slots(const BreakAiFormationSlot *formation,
                                    Vec3 leader_position, Vec3 leader_forward,
                                    Vec3 *out_slots) {
    f32 length_sq = leader_forward.e[0] * leader_forward.e[0] +
                    leader_forward.e[2] * leader_forward.e[2];
    Vec3 forward = vec3(1, 0, 0);
    if (length_sq > 1.0e-12f) {
        f32 inverse_length = 1.0f / sqrtf(length_sq);
        forward.e[0] = leader_forward.e[0] * inverse_length;
        forward.e[2] = leader_forward.e[2] * inverse_length;
    }
    Vec3 right = vec3(-forward.e[2], 0.0f, forward.e[0]);
    out_slots[0] = leader_position;
    for (u32 i = 1; i < formation->member_count; i++) {
        f32 row = (f32)((i + 1u) / 2u);
        f32 side = (i & 1u) ? -1.0f : 1.0f;
        f32 behind = -row * formation->spacing;
        f32 lateral = side * row * formation->spacing;
        out_slots[i] = vec3(leader_position.e[0] + forward.e[0] * behind + right.e[0] * lateral,
                            leader_position.e[1],
                            leader_position.e[2] + forward.e[2] * behind + right.e[2] * lateral);
    }
}

BreakNavError break_ai_formation_create(BreakAiRuntime *runtime, const Entity *members,
                                        u32 member_count, f32 spacing,
                                        BreakAiFormationHandle *out) {
    if (!runtime || !members || !out) {
        return BREAK_NAV_INVALID;
    }
    if (!break_ai_is_owner(runtime)) {
        return BREAK_NAV_REJECTED;
    }
    if (member_count > BREAK_AI_MAX_FORMATION_MEMBERS) {
        return BREAK_NAV_OVERLOAD;
    }
    if (member_count == 0 || !isfinite(spacing) || spacing <= 0.0f) {
        return BREAK_NAV_INVALID;
    }
    for (u32 i = 0; i < member_count; i++) {
        if (!entity_valid(members[i])) {
            return BREAK_NAV_INVALID;
        }
        if (break_ai_agent_index(runtime, members[i]) == UINT32_MAX) {
            return BREAK_NAV_STALE;
        }
        for (u32 n = 0; n < i; n++) {
            if (formation_entity_equal(members[i], members[n])) {
                return BREAK_NAV_INVALID;
            }
        }
    }
    u32 free_index = runtime->max_formations;
    for (u32 i = 0; i < runtime->max_formations; i++) {
        if (!runtime->formations[i].live) {
            free_index = i;
            break;
        }
    }
    if (free_index == runtime->max_formations) {
        return BREAK_NAV_OVERLOAD;
    }
    BreakAiFormationSlot *formation = &runtime->formations[free_index];
    u32 generation = formation->generation == UINT32_MAX ? 1u : formation->generation + 1u;
    for (u32 i = 0; i < member_count; i++) {
        formation->members[i] = members[i];
    }
    formation->member_count = member_count;
    formation->spacing = spacing;
    formation->generation = generation;
    formation->live = true;
    out->index = free_index;
    out->generation = generation;
    return BREAK_NAV_OK;
}

BreakNavError break_ai_formation_destroy(BreakAiRuntime *runtime,
                                         BreakAiFormationHandle handle) {
    if (!runtime) {
        return BREAK_NAV_INVALID;
    }
    if (!break_ai_is_owner(runtime)) {
        return BREAK_NAV_REJECTED;
    }
    u32 index = 0;
    BreakNavError status = formation_slot_at(runtime, handle, &index);
    if (status != BREAK_NAV_OK) {
        return status;
    }
    runtime->formations[index].live = false;
    return BREAK_NAV_OK;
}

BreakNavError break_ai_formation_slots(BreakAiRuntime *runtime,
                                       BreakAiFormationHandle handle,
                                       Vec3 leader_position, Vec3 leader_forward,
                                       Vec3 *out_slots, u32 cap, u32 *out_count) {
    if (!runtime || !out_slots || !out_count) {
        return BREAK_NAV_INVALID;
    }
    if (!break_ai_is_owner(runtime)) {
        return BREAK_NAV_REJECTED;
    }
    u32 index = 0;
    BreakNavError status = formation_slot_at(runtime, handle, &index);
    if (status != BREAK_NAV_OK) {
        return status;
    }
    if (!formation_vec_ok(leader_position) || !formation_vec_ok(leader_forward)) {
        return BREAK_NAV_INVALID;
    }
    const BreakAiFormationSlot *formation = &runtime->formations[index];
    if (cap < formation->member_count) {
        return BREAK_NAV_OVERLOAD;
    }
    Vec3 slots[BREAK_AI_MAX_FORMATION_MEMBERS];
    formation_compute_slots(formation, leader_position, leader_forward, slots);
    for (u32 i = 0; i < formation->member_count; i++) {
        out_slots[i] = slots[i];
    }
    *out_count = formation->member_count;
    return BREAK_NAV_OK;
}

BreakNavError break_ai_formation_tick(BreakAiRuntime *runtime,
                                      BreakAiFormationHandle handle, f32 dt,
                                      Vec3 *out_velocities, u32 cap, u32 *out_count) {
    if (!runtime || !out_velocities || !out_count) {
        return BREAK_NAV_INVALID;
    }
    if (!break_ai_is_owner(runtime)) {
        return BREAK_NAV_REJECTED;
    }
    u32 index = 0;
    BreakNavError status = formation_slot_at(runtime, handle, &index);
    if (status != BREAK_NAV_OK) {
        return status;
    }
    if (!isfinite(dt) || dt <= 0.0f) {
        return BREAK_NAV_INVALID;
    }
    const BreakAiFormationSlot *formation = &runtime->formations[index];
    if (cap < formation->member_count) {
        return BREAK_NAV_OVERLOAD;
    }
    u32 leader_index = break_ai_agent_index(runtime, formation->members[0]);
    if (leader_index == UINT32_MAX) {
        return BREAK_NAV_STALE;
    }
    const BreakAiAgentDesc *leader = &runtime->agents[leader_index].desc;
    Vec3 slots[BREAK_AI_MAX_FORMATION_MEMBERS];
    Vec3 velocities[BREAK_AI_MAX_FORMATION_MEMBERS];
    formation_compute_slots(formation, leader->position, leader->velocity, slots);
    velocities[0] = leader->velocity;
    for (u32 i = 1; i < formation->member_count; i++) {
        u32 agent_index = break_ai_agent_index(runtime, formation->members[i]);
        if (agent_index == UINT32_MAX) {
            return BREAK_NAV_STALE;
        }
        const BreakAiAgentDesc *agent = &runtime->agents[agent_index].desc;
        BreakNavPath path;
        path.count = 2;
        path.points[0] = agent->position;
        path.points[1] = slots[i];
        f32 arrive_radius = formation->spacing * 0.025f;
        if (arrive_radius > 0.05f) {
            arrive_radius = 0.05f;
        }
        BreakNavFollower follower;
        break_nav_follow_reset(&follower, &path, arrive_radius);
        Vec3 displacement = break_nav_follow_wish(&follower, agent->position,
                                                  agent->max_speed, dt);
        velocities[i] = vec3(displacement.e[0] / dt,
                             displacement.e[1] / dt,
                             displacement.e[2] / dt);
    }
    for (u32 i = 0; i < formation->member_count; i++) {
        out_velocities[i] = velocities[i];
    }
    *out_count = formation->member_count;
    return BREAK_NAV_OK;
}
