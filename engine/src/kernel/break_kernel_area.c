#include <kernel/break_kernel_internal.h>
#include <math.h>

static bool finite_vec(Vec3 v) {
    return isfinite(v.e[0]) && isfinite(v.e[1]) && isfinite(v.e[2]);
}

static bool desc_ok(const BreakKernelAreaDesc *desc, bool *aabb) {
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

static bool area_contains(const BreakKernelArea *area, Vec3 point, bool expanded) {
    if (area->aabb) {
        Vec3 half = area->desc.half_extent;
        if (expanded) {
            half.e[0] += BREAK_KERNEL_AREA_HYSTERESIS;
            half.e[1] += BREAK_KERNEL_AREA_HYSTERESIS;
            half.e[2] += BREAK_KERNEL_AREA_HYSTERESIS;
        }
        return contains_aabb(area->desc.center, half, point);
    }
    f32 radius = area->desc.radius + (expanded ? BREAK_KERNEL_AREA_HYSTERESIS : 0.0f);
    return contains_sphere(area->desc.center, radius, point);
}

static u8 *inside_at(BreakKernel *kernel, u32 area, u32 slot) {
    return &kernel->inside[(size_t)area * (size_t)kernel->max_actors + slot];
}

static bool actor_position(const BreakKernel *kernel, u32 slot, Vec3 *out) {
    if (kernel->world->component_sizes[BREAK_KERNEL_POSITION_COMPONENT] < sizeof(Vec3)) {
        return false;
    }
    void *pos = world_get_component(kernel->world, kernel->actors[slot].entity, BREAK_KERNEL_POSITION_COMPONENT);
    if (!pos) {
        return false;
    }
    memcpy(out, pos, sizeof(Vec3));
    return true;
}

void break_kernel_area_on_despawn(BreakKernel *kernel, u32 slot, Entity entity) {
    for (u32 area = 0; area < kernel->area_count; area++) {
        u8 *bit = inside_at(kernel, area, slot);
        if (*bit) {
            *bit = 0;
            if (kernel->area_fn) {
                kernel->area_fn(area, entity, BREAK_KERNEL_AREA_LEAVE, kernel->area_user);
            }
        }
    }
}

BreakKernelError break_kernel_area_add(BreakKernel *kernel, const BreakKernelAreaDesc *desc, u32 *out_id) {
    if (!kernel || !out_id) {
        return BREAK_KERNEL_INVALID;
    }
    if (!break_kernel_is_owner(kernel)) {
        return BREAK_KERNEL_REJECTED;
    }
    bool aabb = false;
    if (!desc_ok(desc, &aabb)) {
        return BREAK_KERNEL_INVALID;
    }
    if (kernel->area_count >= BREAK_KERNEL_HARD_MAX_AREAS) {
        return BREAK_KERNEL_OVERLOAD;
    }
    u32 id = kernel->area_count++;
    kernel->areas[id].desc = *desc;
    kernel->areas[id].aabb = aabb;
    kernel->areas[id].used = true;
    *out_id = id;
    return BREAK_KERNEL_OK;
}

void break_kernel_set_area_callback(BreakKernel *kernel, BreakKernelAreaFn fn, void *user) {
    if (!kernel || !break_kernel_is_owner(kernel)) {
        return;
    }
    kernel->area_fn = fn;
    kernel->area_user = user;
}

BreakKernelError break_kernel_area_tick(BreakKernel *kernel) {
    if (!kernel) {
        return BREAK_KERNEL_INVALID;
    }
    if (!break_kernel_is_owner(kernel)) {
        return BREAK_KERNEL_REJECTED;
    }
    bool deferred = false;
    for (u32 area = 0; area < kernel->area_count; area++) {
        u32 emitted = 0;
        for (u32 slot = 0; slot < kernel->max_actors; slot++) {
            if (!kernel->actors[slot].alive) {
                continue;
            }
            Vec3 point;
            bool have = actor_position(kernel, slot, &point);
            u8 *bit = inside_at(kernel, area, slot);
            bool was = *bit != 0;
            bool now_in = have && area_contains(&kernel->areas[area], point, false);
            bool now_out = !have || !area_contains(&kernel->areas[area], point, true);
            bool enter = !was && now_in;
            bool leave = was && now_out;
            if (!enter && !leave) {
                continue;
            }
            if (emitted >= BREAK_KERNEL_AREA_EVENT_CAP) {
                deferred = true;
                continue;
            }
            *bit = enter ? 1 : 0;
            if (kernel->area_fn) {
                kernel->area_fn(area, kernel->actors[slot].entity,
                              enter ? BREAK_KERNEL_AREA_ENTER : BREAK_KERNEL_AREA_LEAVE,
                              kernel->area_user);
            }
            emitted++;
        }
    }
    return deferred ? BREAK_KERNEL_OVERLOAD : BREAK_KERNEL_OK;
}
