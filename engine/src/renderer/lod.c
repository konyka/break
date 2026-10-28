#include "lod.h"
#include <math.h>
#include <stdlib.h>
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
    if (group->level_count == 0) return;  /* prevent u32 underflow in lod_select_* */

    u32 idx = sys->count;
    sys->groups[idx] = *group;
    sys->groups[idx].entity_id = entity;
    /* R161-B: Clamp level_count to LOD_MAX_LEVELS to prevent out-of-bounds reads
     * in thresholds_sq[] and meshes[] arrays during lod_select and lod_get_mesh.
     * Without this, a caller setting level_count > 4 would cause OOB reads. */
    if (sys->groups[idx].level_count > LOD_MAX_LEVELS) {
        sys->groups[idx].level_count = LOD_MAX_LEVELS;
    }
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
    /* R344 (CORRECTNESS): same group-0 aliasing hole as R260 on select/get_mesh.
     * Unregistered entities keep entity_to_group[]==0; once any group exists,
     * idx=0 passes "idx >= count" and swap-removes the real occupant of slot 0. */
    if (idx >= sys->count || sys->groups[idx].entity_id != entity) return;

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
    /* R260 (CORRECTNESS): entity_to_group[] is zero-initialised (lod_init) and
     * lod_unregister resets removed entries to 0, so an entity that was never
     * registered maps to group_idx 0. The old "group_idx >= count" guard passes
     * for group_idx 0 once any group exists, aliasing this entity onto group 0's
     * LODGroup and even writing current_levels[entity] below. Verify the resolved
     * group actually belongs to this entity — entity_id is kept accurate across
     * the swap-remove in lod_unregister. */
    if (group_idx >= sys->count || sys->groups[group_idx].entity_id != entity) return 0;

    LODGroup *group = &sys->groups[group_idx];
    u32 current = sys->current_levels[entity];
    u32 selected;

    if (sys->use_screen_size) {
        f32 fraction = lod_compute_screen_fraction(
            object_pos, group->bounding_radius, camera_pos, fov);
        /* R162-A: Compute inv_bias = 1/(1+bias) to match lod_update_all.
         * Previously sys->bias was passed directly as inv_bias, causing
         * effective_fraction = fraction * bias (instead of fraction / (1+bias)).
         * With default bias=0 this zeroed effective_fraction, always selecting
         * the coarsest LOD level. */
        f32 inv_bias = 1.0f / (1.0f + sys->bias);
        selected = lod_select_by_screen_size(
            group, current, fraction, sys->screen_threshold, inv_bias);
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
            /* R293 (CORRECTNESS): current_levels[] is indexed by ENTITY id (see
             * lod.h + lod_register/lod_select/lod_get_level/lod_get_mesh), not by
             * the dense group slot i. Reading/writing current_levels[i] here made
             * lod_update_all update the wrong slot whenever an entity id differed
             * from its registration index, so lod_get_level/lod_get_mesh(entity)
             * kept returning the stale initial level 0. Index by entity_id. */
            u32 entity = group->entity_id;
            u32 current = sys->current_levels[entity];

            f32 fraction = lod_compute_screen_fraction(
                positions[i], group->bounding_radius, camera_pos, fov);

            u32 selected = lod_select_by_screen_size(
                group, current, fraction, sys->screen_threshold, inv_bias);

            if (selected != current) {
                sys->lod_transitions_this_frame++;
                sys->current_levels[entity] = selected;
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
            /* R293 (CORRECTNESS): index current_levels[] by entity id, not slot i
             * (see the screen-size branch above). */
            u32 entity = group->entity_id;
            u32 current = sys->current_levels[entity];

            f32 dist_sq = lod_distance_sq(positions[i], camera_pos);

            u32 selected = lod_select_by_distance_sq(
                group, current, dist_sq, sys->bias);

            if (selected != current) {
                sys->lod_transitions_this_frame++;
                sys->current_levels[entity] = selected;
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

    /* R260: reject unregistered entities that alias group 0 (see lod_select). */
    if (group_idx >= sys->count || sys->groups[group_idx].entity_id != entity) {
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

f32 lod_screen_proj_factor(f32 fov, f32 screen_h) {
    f32 t = tanf(fov * 0.5f);
    if (!(t > 1e-6f)) t = 1e-6f;
    return screen_h / (2.0f * t);
}

u32 lod_select_by_screen_error(const f32 *errors, u32 count, f32 dist,
                               f32 proj_factor, f32 pixel_err, u32 current_level) {
    if (!errors || count <= 1u || !(pixel_err > 0.0f)) return 0u;
    u32 cur = current_level < count ? current_level : count - 1u;
    if (!(dist > LOD_SCREEN_MIN_DIST)) dist = LOD_SCREEN_MIN_DIST;
    f32 px_per_unit = proj_factor / dist;
    f32 hi = pixel_err * (1.0f + LOD_SCREEN_HYSTERESIS);
    f32 lo = pixel_err * (1.0f - LOD_SCREEN_HYSTERESIS);

    if (errors[cur] * px_per_unit > hi) {
        /* Refine: coarsest level at or below cur within the plain threshold
         * (errors are non-decreasing, so scan down from cur). */
        u32 l = cur;
        while (l > 0u && errors[l] * px_per_unit > pixel_err) l--;
        return l;
    }
    /* Coarsen only past the lower edge of the band. */
    u32 l = cur;
    while (l + 1u < count && errors[l + 1u] * px_per_unit <= lo) l++;
    return l;
}

u32 lod_select_screen_error(const f32 *errors, u32 count, Vec3 center, f32 radius,
                            Vec3 cam_pos, f32 fov, f32 screen_h, f32 pixel_err,
                            u32 current_level) {
    f32 d = sqrtf(lod_distance_sq(center, cam_pos)) - (radius > 0.0f ? radius : 0.0f);
    return lod_select_by_screen_error(errors, count, d,
                                      lod_screen_proj_factor(fov, screen_h),
                                      pixel_err, current_level);
}

u32 lod_bucket_instances(const u32 *inst_mesh, const u8 *inst_level, u32 count,
                         u32 mesh_count, u32 levels, u32 *offsets, u32 *order) {
    if (!inst_mesh || !offsets || !order || mesh_count == 0u || levels == 0u) return 0u;
    if (mesh_count > UINT32_MAX / levels - 1u) return 0u;
    u32 k_total = mesh_count * levels;
    memset(offsets, 0, ((usize)k_total + 1u) * sizeof(u32));
    for (u32 i = 0; i < count; i++) {
        if (inst_mesh[i] >= mesh_count) continue;
        u32 l = inst_level ? inst_level[i] : 0u;
        if (l >= levels) l = levels - 1u;
        offsets[inst_mesh[i] * levels + l + 1u]++;
    }
    for (u32 k = 1; k <= k_total; k++) offsets[k] += offsets[k - 1u];
    for (u32 i = 0; i < count; i++) {
        if (inst_mesh[i] >= mesh_count) continue;
        u32 l = inst_level ? inst_level[i] : 0u;
        if (l >= levels) l = levels - 1u;
        order[offsets[inst_mesh[i] * levels + l]++] = i;
    }
    /* offsets[k] now holds the end of bucket k; shift back to starts. */
    for (u32 k = k_total; k >= 1u; k--) offsets[k] = offsets[k - 1u];
    offsets[0] = 0u;
    return offsets[k_total];
}

u32 lod_instance_select(LodInstanceState *st, u32 slot, u32 tag,
                        const f32 *errors, u32 count, f32 dist, f32 proj_factor,
                        f32 pixel_err, bool *changed) {
    if (changed) *changed = false;
    bool tracked = st && st->level && st->tag && slot < st->capacity && tag != 0u;
    u32 cur = (tracked && st->tag[slot] == tag) ? st->level[slot] : 0u;
    u32 lvl = lod_select_by_screen_error(errors, count, dist, proj_factor, pixel_err, cur);
    if (tracked) {
        if (changed && st->tag[slot] == tag && lvl != cur) *changed = true;
        st->tag[slot] = tag;
        st->level[slot] = (u8)lvl;
    }
    return lvl;
}

u32 lod_instance_level(const LodInstanceState *st, u32 slot, u32 tag) {
    if (!st || !st->level || !st->tag || slot >= st->capacity || tag == 0u) return 0u;
    return st->tag[slot] == tag ? st->level[slot] : 0u;
}

f32 lod_fade_seconds(void) {
    static int cached = 0;
    static f32 v = 0.25f;
    if (!cached) {
        cached = 1;
        const char *l = getenv("BREAK_LOD");
        const char *e = getenv("BREAK_LOD_FADE_MS");
        if (e && e[0]) { int ms = atoi(e); v = ms > 0 ? (f32)ms / 1000.0f : 0.0f; }
        if (l && l[0] && !atoi(l)) v = 0.0f;
    }
    return v;
}

void lod_fade_reset(LodFade *f, u32 level) {
    if (!f) return;
    f->level = (u8)level;
    f->from = (u8)level;
    f->start = 0.0;
}

static f32 lod_fade_progress(const LodFade *f, f64 now, f32 fade_s) {
    if (!(fade_s > 0.0f)) return 1.0f;
    f64 t = (now - f->start) / (f64)fade_s;
    if (t < 0.0) t = 0.0;
    if (t > 1.0) t = 1.0;
    return (f32)t;
}

bool lod_fade_update(LodFade *f, u32 new_level, f64 now, f32 fade_s) {
    if (!f) return false;
    if (!(fade_s > 0.0f)) {
        bool ch = f->level != new_level;
        lod_fade_reset(f, new_level);
        return ch;
    }
    if (f->from != f->level && now - f->start >= (f64)fade_s) f->from = f->level;
    if (new_level == f->level) return false;
    if (f->from == f->level) {
        f->level = (u8)new_level;
        f->start = now;
    } else {
        f32 t = lod_fade_progress(f, now, fade_s);
        if (new_level == f->from) {
            /* Reverse: the outgoing level becomes the incoming one at the
             * complementary progress, so the finer share stays put. */
            f->from = f->level;
            f->level = (u8)new_level;
            f->start = now - (f64)(1.0f - t) * (f64)fade_s;
        } else {
            f->from = t >= 0.5f ? f->level : f->from;
            f->level = (u8)new_level;
            f->start = now;
        }
    }
    return true;
}

u32 lod_fade_split(const LodFade *f, f64 now, f32 fade_s, u32 *finer, u32 *coarser) {
    u32 a = f ? f->level : 0u, b = f ? f->from : 0u;
    f32 t = (f && a != b) ? lod_fade_progress(f, now, fade_s) : 1.0f;
    if (!f || a == b || t >= 1.0f) {
        if (finer) *finer = a;
        if (coarser) *coarser = a;
        return LOD_FADE_STEPS;
    }
    bool incoming_finer = a < b;
    f32 phi = incoming_finer ? t : 1.0f - t;   /* finer level's share */
    u32 k = (u32)(phi * (f32)LOD_FADE_STEPS);
    if (k > LOD_FADE_STEPS) k = LOD_FADE_STEPS;
    if (finer) *finer = incoming_finer ? a : b;
    if (coarser) *coarser = incoming_finer ? b : a;
    return k;
}

u32 lod_bayer4(u32 x, u32 y) {
    static const u8 m[16] = { 0, 8, 2, 10, 12, 4, 14, 6, 3, 11, 1, 9, 15, 7, 13, 5 };
    return m[(y & 3u) * 4u + (x & 3u)];
}

bool lod_fade_keep(u32 bayer, f32 value) {
    if (value == 0.0f) return true;
    f32 b = (f32)bayer + 0.5f;
    return value > 0.0f ? !(b > value) : !(b < -value);
}

u32 lod_fade_write_commands(const LodFade *f, f64 now, f32 fade_s,
                            u32 level_count, u32 *selected, i8 *dither) {
    if (!selected || !dither || level_count == 0u) return 0u;
    u32 fi = 0u, co = 0u;
    u32 k = lod_fade_split(f, now, fade_s, &fi, &co);
    if (fi >= level_count) fi = level_count - 1u;
    if (co >= level_count) co = level_count - 1u;
    for (u32 l = 0; l < level_count; l++) {
        selected[l] = 0u;
        dither[l] = 0;
    }
    if (fi == co || k >= LOD_FADE_STEPS) {
        selected[fi] = 1u;
    } else if (k == 0u) {
        selected[co] = 1u;
    } else {
        selected[fi] = selected[co] = 1u;
        dither[fi] = (i8)k;
        dither[co] = -(i8)k;
        return 2u;
    }
    return 1u;
}

u32 lod_fade_pack_first_instance(u32 first_instance, i32 dither) {
    u32 layer = first_instance & 0xFFFFu;
    if (dither == 0) return layer;
    if (dither < -15) dither = -15;
    if (dither > 15) dither = 15;
    return layer | ((u32)(dither + 16) << 16);
}

void lod_group_set_auto_thresholds(LODGroup *group, f32 base_distance) {
    /* Default: each level doubles the distance */
    for (u32 i = 0; i < group->level_count && i < LOD_MAX_LEVELS; i++) {
        f32 t = base_distance * (f32)(1u << i);
        group->thresholds[i] = t;
        group->thresholds_sq[i] = t * t;
    }
}
