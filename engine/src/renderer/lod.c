#include "lod.h"
#include <string.h>

/* ---- Hysteresis to prevent LOD thrashing ---- */
#define LOD_HYSTERESIS 0.1f

/* Precomputed 1/(2^i) for i=0..15 — eliminates runtime division by powers of 2. */
static const f32 lod_inv_pow2[16] = {
    1.0f, 0.5f, 0.25f, 0.125f, 0.0625f, 0.03125f, 0.015625f, 0.0078125f,
    0.00390625f, 0.001953125f, 0.0009765625f, 0.00048828125f,
    0.000244140625f, 0.0001220703125f, 6.103515625e-05f, 3.0517578125e-05f,
};

/* ---- Internal helpers ---- */

static f32 lod_distance_sq(Vec3 a, Vec3 b) {
    f32 dx = a.e[0] - b.e[0];
    f32 dy = a.e[1] - b.e[1];
    f32 dz = a.e[2] - b.e[2];
    return dx * dx + dy * dy + dz * dz;
}

/*
 * Compute approximate screen-space fraction using dist² ratio.
 * Avoids sqrtf + atanf: screen_fraction ≈ (radius²) / dist² when dist >> radius.
 */
static f32 lod_compute_screen_fraction(Vec3 obj_pos, f32 radius,
                                       Vec3 cam_pos, f32 fov) {
    (void)fov;  /* absorbed into thresholds via squared approximation */
    f32 dist_sq = lod_distance_sq(obj_pos, cam_pos);
    if (dist_sq < 0.000001f) return 1.0f;

    /* Approximate angular diameter ratio: (2*atan(r/d)) / fov ≈ (r²/d²) * (2/fov)
     * For LOD selection, the constant factor is absorbed into thresholds. */
    f32 r_sq = radius * radius;
    f32 screen_fraction = r_sq / dist_sq;
    return screen_fraction;
}

/*
 * Select LOD level using squared-distance strategy with hysteresis.
 * Avoids sqrtf by comparing dist² against pre-squared thresholds.
 */
static u32 lod_select_by_distance_sq(const LODGroup *group, u32 current_level,
                                      f32 dist_sq, f32 bias) {
    /* Apply global bias in squared domain */
    f32 bias_factor = (1.0f + bias);
    f32 effective_dist_sq = dist_sq * (bias_factor * bias_factor);

    /* Pre-compute squared hysteresis factors */
    f32 hyst_lo = (1.0f - LOD_HYSTERESIS);
    f32 hyst_hi = (1.0f + LOD_HYSTERESIS);
    f32 hyst_lo_sq = hyst_lo * hyst_lo;
    f32 hyst_hi_sq = hyst_hi * hyst_hi;

    /* Find raw target level */
    u32 target = group->level_count - 1; /* default: coarsest */
    for (u32 i = 0; i < group->level_count - 1; i++) {
        if (effective_dist_sq < group->thresholds_sq[i]) {
            target = i;
            break;
        }
    }

    /* Apply hysteresis to prevent rapid switching */
    if (current_level != target) {
        if (target < current_level) {
            /* Upgrading quality: require being closer than threshold minus buffer */
            f32 threshold_sq = group->thresholds_sq[target];
            if (effective_dist_sq > threshold_sq * hyst_lo_sq) {
                return current_level; /* stay at current */
            }
        } else {
            /* Downgrading quality: require being farther than threshold plus buffer */
            f32 threshold_sq = group->thresholds_sq[current_level];
            if (effective_dist_sq < threshold_sq * hyst_hi_sq) {
                return current_level; /* stay at current */
            }
        }
    }

    return target;
}

/*
 * Select LOD level using screen-fraction strategy with hysteresis.
 * Smaller screen fraction -> higher LOD level (coarser).
 */
static u32 lod_select_by_screen_size(const LODGroup *group, u32 current_level,
                                     f32 screen_fraction, f32 base_threshold,
                                     f32 inv_bias) {
    /* Apply bias: precomputed reciprocal avoids per-call division */
    f32 effective_fraction = screen_fraction * inv_bias;

    /* Thresholds: level 0 needs > base_threshold,
     * level 1 needs > base_threshold/2, etc. — use precomputed 1/2^i table. */
    u32 target = group->level_count - 1;
    for (u32 i = 0; i < group->level_count - 1; i++) {
        f32 level_threshold = base_threshold * lod_inv_pow2[i];
        if (effective_fraction >= level_threshold) {
            target = i;
            break;
        }
    }

    /* Hysteresis */
    if (current_level != target) {
        f32 thresh_current = base_threshold * lod_inv_pow2[current_level & 15];
        f32 buffer = thresh_current * LOD_HYSTERESIS;

        if (target < current_level) {
            /* Upgrading: fraction must exceed threshold + buffer */
            f32 thresh_target = base_threshold * lod_inv_pow2[target & 15];
            if (effective_fraction < thresh_target + buffer) {
                return current_level;
            }
        } else {
            /* Downgrading: fraction must be below threshold - buffer */
            if (effective_fraction > thresh_current - buffer) {
                return current_level;
            }
        }
    }

    return target;
}

/* ---- Public API ---- */

void lod_init(LODSystem *sys) {
    memset(sys, 0, sizeof(LODSystem));
    sys->bias = 0.0f;
    sys->use_screen_size = false;
    sys->screen_threshold = 0.02f; /* 2% screen coverage baseline */
}

void lod_shutdown(LODSystem *sys) {
    /* LOD system is purely CPU-side; no GPU resources to free.
     * The caller owns the mesh resources referenced by LODGroups. */
    memset(sys, 0, sizeof(LODSystem));
}

void lod_register(LODSystem *sys, u32 entity, const LODGroup *group) {
    if (sys->count >= LOD_MAX_GROUPS) return;
    if (entity >= LOD_MAX_GROUPS) return;

    u32 idx = sys->count;
    sys->groups[idx] = *group;
    sys->groups[idx].entity_id = entity;
    /* Ensure thresholds_sq is populated (backward compat for callers that
     * only set thresholds without thresholds_sq). */
    for (u32 i = 0; i < group->level_count && i < LOD_MAX_LEVELS; i++) {
        if (sys->groups[idx].thresholds_sq[i] == 0.0f && group->thresholds[i] != 0.0f) {
            sys->groups[idx].thresholds_sq[i] = group->thresholds[i] * group->thresholds[i];
        }
    }
    sys->entity_to_group[entity] = idx;
    sys->current_levels[entity] = 0; /* start at highest quality */
    sys->count++;
}

void lod_unregister(LODSystem *sys, u32 entity) {
    if (entity >= LOD_MAX_GROUPS) return;

    u32 idx = sys->entity_to_group[entity];
    if (idx >= sys->count) return;

    /* Swap-remove: move last group into the removed slot */
    u32 last = sys->count - 1;
    if (idx != last) {
        sys->groups[idx] = sys->groups[last];

        /* O(1): use stored entity_id to update the mapping directly */
        u32 moved_entity = sys->groups[idx].entity_id;
        sys->entity_to_group[moved_entity] = idx;
    }

    sys->entity_to_group[entity] = 0;
    sys->current_levels[entity] = 0;
    sys->count--;
}

u32 lod_select(LODSystem *sys, u32 entity, Vec3 object_pos,
               Vec3 camera_pos, f32 fov) {
    if (entity >= LOD_MAX_GROUPS) return 0;

    u32 group_idx = sys->entity_to_group[entity];
    if (group_idx >= sys->count) return 0;

    LODGroup *group = &sys->groups[group_idx];
    u32 current = sys->current_levels[entity];
    u32 selected;

    if (sys->use_screen_size) {
        f32 fraction = lod_compute_screen_fraction(
            object_pos, group->bounding_radius, camera_pos, fov);
        selected = lod_select_by_screen_size(
            group, current, fraction, sys->screen_threshold, sys->bias);
    } else {
        f32 dist_sq = lod_distance_sq(object_pos, camera_pos);
        selected = lod_select_by_distance_sq(group, current, dist_sq, sys->bias);
    }

    if (selected != current) {
        sys->lod_transitions_this_frame++;
    }
    sys->current_levels[entity] = selected;
    return selected;
}

void lod_update_all(LODSystem *sys, Vec3 camera_pos, f32 fov,
                    const Vec3 *positions, u32 count) {
    /* Reset per-frame stats */
    sys->total_triangles_saved = 0;
    sys->lod_transitions_this_frame = 0;

    u32 update_count = count < sys->count ? count : sys->count;

    if (sys->use_screen_size) {
        /* Screen-fraction strategy — precompute bias reciprocal once per frame */
        f32 inv_bias = 1.0f / (1.0f + sys->bias);
        for (u32 i = 0; i < update_count; i++) {
            LODGroup *group = &sys->groups[i];
            u32 current = sys->current_levels[i];

            f32 fraction = lod_compute_screen_fraction(
                positions[i], group->bounding_radius, camera_pos, fov);

            u32 selected = lod_select_by_screen_size(
                group, current, fraction, sys->screen_threshold, inv_bias);

            if (selected != current) {
                sys->lod_transitions_this_frame++;
                sys->current_levels[i] = selected;
            }

            /* Accumulate triangle savings (LOD 0 is baseline) */
            if (selected > 0 && group->vertex_counts[0] > 0) {
                u32 saved = group->vertex_counts[0] - group->vertex_counts[selected];
                sys->total_triangles_saved += saved / 3;
            }
        }
    } else {
        /* Distance strategy — O(n) linear pass */
        for (u32 i = 0; i < update_count; i++) {
            LODGroup *group = &sys->groups[i];
            u32 current = sys->current_levels[i];

            f32 dist_sq = lod_distance_sq(positions[i], camera_pos);

            u32 selected = lod_select_by_distance_sq(
                group, current, dist_sq, sys->bias);

            if (selected != current) {
                sys->lod_transitions_this_frame++;
                sys->current_levels[i] = selected;
            }

            /* Accumulate triangle savings */
            if (selected > 0 && group->vertex_counts[0] > 0) {
                u32 saved = group->vertex_counts[0] - group->vertex_counts[selected];
                sys->total_triangles_saved += saved / 3;
            }
        }
    }
}

LODMesh lod_get_mesh(LODSystem *sys, u32 entity) {
    if (entity >= LOD_MAX_GROUPS) {
        LODMesh empty;
        memset(&empty, 0, sizeof(empty));
        return empty;
    }

    u32 group_idx = sys->entity_to_group[entity];
    u32 level = sys->current_levels[entity];

    if (group_idx >= sys->count) {
        LODMesh empty;
        memset(&empty, 0, sizeof(empty));
        return empty;
    }

    return sys->groups[group_idx].meshes[level];
}

u32 lod_get_level(LODSystem *sys, u32 entity) {
    if (entity >= LOD_MAX_GROUPS) return 0;
    return sys->current_levels[entity];
}

void lod_set_bias(LODSystem *sys, f32 bias) {
    sys->bias = bias;
}

void lod_set_strategy(LODSystem *sys, bool use_screen_size) {
    sys->use_screen_size = use_screen_size;
}

void lod_group_set_auto_thresholds(LODGroup *group, f32 base_distance) {
    /* Default: each level doubles the distance */
    for (u32 i = 0; i < group->level_count && i < LOD_MAX_LEVELS; i++) {
        f32 t = base_distance * (f32)(1u << i);
        group->thresholds[i] = t;
        group->thresholds_sq[i] = t * t;
    }
}
