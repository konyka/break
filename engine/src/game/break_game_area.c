#include <game/break_game_internal.h>
#include <math.h>

static bool finite_vec(Vec3 v) {
    return isfinite(v.e[0]) && isfinite(v.e[1]) && isfinite(v.e[2]);
}

static bool desc_ok(const BreakGameAreaDesc *desc, bool *aabb) {
    if (!desc || !finite_vec(desc->center) || !finite_vec(desc->half_extent) || !isfinite(desc->radius)) {
        return false;
    }
    bool any = false;
    for (int i = 0; i < 3; i++) {
        if (desc->half_extent.e[i] < 0.0f) {
            return false;
        }
        if (desc->half_extent.e[i] > 0.0f) {
            any = true;
        }
    }
    if (!any && !(desc->radius > 0.0f)) {
        return false;
    }
    *aabb = any;
    return true;
}

static bool contains_aabb(Vec3 center, Vec3 half, Vec3 point) {
    return fabsf(point.e[0] - center.e[0]) <= half.e[0] &&
           fabsf(point.e[1] - center.e[1]) <= half.e[1] &&
           fabsf(point.e[2] - center.e[2]) <= half.e[2];
}

static bool contains_sphere(Vec3 center, f32 radius, Vec3 point) {
    f32 dx = point.e[0] - center.e[0];
    f32 dy = point.e[1] - center.e[1];
    f32 dz = point.e[2] - center.e[2];
    return dx * dx + dy * dy + dz * dz <= radius * radius;
}

static bool area_contains(const BreakGameArea *area, Vec3 point, bool expanded) {
    if (area->aabb) {
        Vec3 half = area->desc.half_extent;
        if (expanded) {
            half.e[0] += BREAK_GAME_AREA_HYSTERESIS;
            half.e[1] += BREAK_GAME_AREA_HYSTERESIS;
            half.e[2] += BREAK_GAME_AREA_HYSTERESIS;
        }
        return contains_aabb(area->desc.center, half, point);
    }
    f32 radius = area->desc.radius + (expanded ? BREAK_GAME_AREA_HYSTERESIS : 0.0f);
    return contains_sphere(area->desc.center, radius, point);
}

static u8 *inside_at(BreakGame *game, u32 area, u32 slot) {
    return &game->inside[(size_t)area * (size_t)game->max_actors + slot];
}

static bool actor_position(const BreakGame *game, u32 slot, Vec3 *out) {
    if (game->world->component_sizes[BREAK_GAME_POSITION_COMPONENT] < sizeof(Vec3)) {
        return false;
    }
    void *pos = world_get_component(game->world, game->actors[slot].entity, BREAK_GAME_POSITION_COMPONENT);
    if (!pos) {
        return false;
    }
    memcpy(out, pos, sizeof(Vec3));
    return true;
}

void break_game_area_on_despawn(BreakGame *game, u32 slot, Entity entity) {
    for (u32 area = 0; area < game->area_count; area++) {
        u8 *bit = inside_at(game, area, slot);
        if (*bit) {
            *bit = 0;
            if (game->area_fn) {
                game->area_fn(area, entity, BREAK_GAME_AREA_LEAVE, game->area_user);
            }
        }
    }
}

BreakGameError break_game_area_add(BreakGame *game, const BreakGameAreaDesc *desc, u32 *out_id) {
    if (!game || !out_id) {
        return BREAK_GAME_INVALID;
    }
    if (!break_game_is_owner(game)) {
        return BREAK_GAME_REJECTED;
    }
    bool aabb = false;
    if (!desc_ok(desc, &aabb)) {
        return BREAK_GAME_INVALID;
    }
    if (game->area_count >= BREAK_GAME_HARD_MAX_AREAS) {
        return BREAK_GAME_OVERLOAD;
    }
    u32 id = game->area_count++;
    game->areas[id].desc = *desc;
    game->areas[id].aabb = aabb;
    game->areas[id].used = true;
    *out_id = id;
    return BREAK_GAME_OK;
}

void break_game_set_area_callback(BreakGame *game, BreakGameAreaFn fn, void *user) {
    if (!game || !break_game_is_owner(game)) {
        return;
    }
    game->area_fn = fn;
    game->area_user = user;
}

BreakGameError break_game_area_tick(BreakGame *game) {
    if (!game) {
        return BREAK_GAME_INVALID;
    }
    if (!break_game_is_owner(game)) {
        return BREAK_GAME_REJECTED;
    }
    bool deferred = false;
    for (u32 area = 0; area < game->area_count; area++) {
        u32 emitted = 0;
        for (u32 slot = 0; slot < game->max_actors; slot++) {
            if (!game->actors[slot].alive) {
                continue;
            }
            Vec3 point;
            bool have = actor_position(game, slot, &point);
            u8 *bit = inside_at(game, area, slot);
            bool was = *bit != 0;
            bool now_in = have && area_contains(&game->areas[area], point, false);
            bool now_out = !have || !area_contains(&game->areas[area], point, true);
            bool enter = !was && now_in;
            bool leave = was && now_out;
            if (!enter && !leave) {
                continue;
            }
            if (emitted >= BREAK_GAME_AREA_EVENT_CAP) {
                deferred = true;
                continue;
            }
            *bit = enter ? 1 : 0;
            if (game->area_fn) {
                game->area_fn(area, game->actors[slot].entity,
                              enter ? BREAK_GAME_AREA_ENTER : BREAK_GAME_AREA_LEAVE,
                              game->area_user);
            }
            emitted++;
        }
    }
    return deferred ? BREAK_GAME_OVERLOAD : BREAK_GAME_OK;
}
