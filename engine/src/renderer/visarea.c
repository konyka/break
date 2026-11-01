#include <renderer/visarea.h>
#include <math.h>
#include <string.h>

static bool point_in_aabb(Vec3 p, Vec3 center, Vec3 half) {
    return fabsf(p.e[0] - center.e[0]) <= half.e[0] &&
           fabsf(p.e[1] - center.e[1]) <= half.e[1] &&
           fabsf(p.e[2] - center.e[2]) <= half.e[2];
}

static bool portal_faces(Vec3 camera, Vec3 forward, const VisPortal *portal) {
    Vec3 to = vec3_sub(portal->center, camera);
    f32 len = vec3_len(to);
    if (len <= 1e-5f) return true;
    Vec3 dir = vec3_scale(to, 1.0f / len);
    if (vec3_dot(dir, forward) <= 0.0f) return false;
    return fabsf(to.e[0]) <= portal->half_extent.e[0] + fabsf(forward.e[0]) * len &&
           fabsf(to.e[1]) <= portal->half_extent.e[1] + fabsf(forward.e[1]) * len &&
           fabsf(to.e[2]) <= portal->half_extent.e[2] + fabsf(forward.e[2]) * len;
}

static u32 append_ids(const u32 *ids, u32 count, u32 *out, u32 cap, u32 *written, u32 *dropped) {
    for (u32 i = 0; i < count; i++) {
        if (*written >= cap) {
            (*dropped)++;
            continue;
        }
        if (out) out[(*written)++] = ids[i];
        else (*dropped)++;
    }
    return *written;
}

u32 visarea_visible(const VisQuery *query, u32 *out_ids, u32 cap, u32 *dropped) {
    if (dropped) *dropped = 0;
    if (!query || !dropped) return 0;
    u32 total = query->outdoor_count;
    for (u32 i = 0; i < query->room_count; i++) total += query->rooms[i].object_count;
    if (!query->rooms || query->room_count > VISAREA_MAX_ROOMS) {
        *dropped = total;
        return 0;
    }
    for (u32 i = 0; i < query->room_count; i++) {
        if (query->rooms[i].object_count > VISAREA_MAX_OBJECTS) {
            *dropped = total;
            return 0;
        }
    }
    u32 written = 0;
    u32 drop = 0;
    if (query->outdoor_ids && query->outdoor_count > 0) {
        append_ids(query->outdoor_ids, query->outdoor_count, out_ids, cap, &written, &drop);
    }
    i32 current = -1;
    for (u32 i = 0; i < query->room_count; i++) {
        if (point_in_aabb(query->camera, query->rooms[i].center, query->rooms[i].half_extent)) {
            current = (i32)i;
            break;
        }
    }
    if (current >= 0) {
        const VisRoom *room = &query->rooms[current];
        if (room->object_ids) {
            append_ids(room->object_ids, room->object_count, out_ids, cap, &written, &drop);
        }
        u8 seen[VISAREA_MAX_ROOMS];
        memset(seen, 0, sizeof(seen));
        seen[current] = 1;
        for (u32 p = 0; p < room->portal_count && p < 8u; p++) {
            const VisPortal *portal = &room->portals[p];
            if (!portal_faces(query->camera, query->camera_forward, portal)) continue;
            if (portal->neighbor_room == UINT32_MAX || portal->neighbor_room >= query->room_count) continue;
            if (seen[portal->neighbor_room]) continue;
            seen[portal->neighbor_room] = 1;
            const VisRoom *next = &query->rooms[portal->neighbor_room];
            if (next->object_ids) {
                append_ids(next->object_ids, next->object_count, out_ids, cap, &written, &drop);
            }
        }
    }
    *dropped = drop;
    return written;
}
