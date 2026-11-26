#include <network/break_snapshot_interp.h>

#include <math.h>
#include <string.h>

/* Below this dot product the two rotations are far enough apart for slerp;
 * above it sin(angle) is too small to divide by and nlerp is used. */
#define SLERP_NLERP_DOT 0.9995f

static bool finite3(const f32 v[3]) { return isfinite(v[0]) && isfinite(v[1]) && isfinite(v[2]); }

static void normalize4(f32 q[4]) {
    f32 n = sqrtf(q[0] * q[0] + q[1] * q[1] + q[2] * q[2] + q[3] * q[3]);
    for (int k = 0; k < 4; ++k) q[k] /= n;
}

bool break_snapshot_interp_init(BreakSnapshotInterp *si, const BreakSnapshotInterpConfig *cfg) {
    if (!si || !cfg) return false;
    if (!isfinite(cfg->max_extrapolate_ticks) || cfg->max_extrapolate_ticks < 0.0f ||
        !isfinite(cfg->max_gap_ticks) || !(cfg->max_gap_ticks > 0.0f))
        return false;
    memset(si, 0, sizeof *si);
    si->cfg = *cfg;
    return true;
}

BreakSnapshotPushResult break_snapshot_interp_push(BreakSnapshotInterp *si, u64 tick,
                                                   const BreakSnapshotPose *pose) {
    BreakSnapshotPose p;
    f32 n2;
    u32 at;
    if (!si || !pose) return BREAK_SNAPSHOT_PUSH_INVALID;
    if (!finite3(pose->position) || !finite3(pose->rotation) || !isfinite(pose->rotation[3]))
        return BREAK_SNAPSHOT_PUSH_INVALID;
    n2 = pose->rotation[0] * pose->rotation[0] + pose->rotation[1] * pose->rotation[1] +
         pose->rotation[2] * pose->rotation[2] + pose->rotation[3] * pose->rotation[3];
    if (!(n2 > 0.0f) || !isfinite(n2)) return BREAK_SNAPSHOT_PUSH_INVALID;
    p = *pose;
    normalize4(p.rotation);
    at = 0u;
    while (at < si->count && si->ticks[at] < tick) ++at;
    if (at < si->count && si->ticks[at] == tick) return BREAK_SNAPSHOT_PUSH_DUPLICATE;
    if (si->count == BREAK_SNAPSHOT_INTERP_CAPACITY) {
        if (at == 0u) return BREAK_SNAPSHOT_PUSH_TOO_OLD;
        /* drop the oldest; the insertion point moves down with it */
        memmove(si->ticks, si->ticks + 1, (si->count - 1u) * sizeof si->ticks[0]);
        memmove(si->poses, si->poses + 1, (si->count - 1u) * sizeof si->poses[0]);
        si->count--;
        at--;
    }
    memmove(si->ticks + at + 1, si->ticks + at, (si->count - at) * sizeof si->ticks[0]);
    memmove(si->poses + at + 1, si->poses + at, (si->count - at) * sizeof si->poses[0]);
    si->ticks[at] = tick;
    si->poses[at] = p;
    si->count++;
    return BREAK_SNAPSHOT_PUSH_OK;
}

void break_snapshot_interp_discard_before(BreakSnapshotInterp *si, f64 tick) {
    u32 keep_from = 0u;
    if (!si || si->count == 0u) return;
    /* The newest snapshot at or before `tick` stays. A NaN `tick` compares
     * false and keeps everything. */
    while (keep_from + 1u < si->count && (f64)si->ticks[keep_from + 1u] <= tick) ++keep_from;
    if (keep_from == 0u) return;
    memmove(si->ticks, si->ticks + keep_from, (si->count - keep_from) * sizeof si->ticks[0]);
    memmove(si->poses, si->poses + keep_from, (si->count - keep_from) * sizeof si->poses[0]);
    si->count -= keep_from;
}

static void blend(const BreakSnapshotPose *a, const BreakSnapshotPose *b, f32 t,
                  BreakSnapshotPose *out) {
    f32 q[4];
    f32 dot = 0.0f;
    for (int k = 0; k < 3; ++k) out->position[k] = a->position[k] + (b->position[k] - a->position[k]) * t;
    for (int k = 0; k < 4; ++k) {
        q[k] = b->rotation[k];
        dot += a->rotation[k] * q[k];
    }
    if (dot < 0.0f) { /* q and -q are the same rotation: take the shorter arc */
        dot = -dot;
        for (int k = 0; k < 4; ++k) q[k] = -q[k];
    }
    if (dot > SLERP_NLERP_DOT) {
        for (int k = 0; k < 4; ++k) out->rotation[k] = a->rotation[k] + (q[k] - a->rotation[k]) * t;
    } else {
        f32 theta = acosf(dot);
        f32 s = sinf(theta);
        f32 wa = sinf((1.0f - t) * theta) / s;
        f32 wb = sinf(t * theta) / s;
        for (int k = 0; k < 4; ++k) out->rotation[k] = a->rotation[k] * wa + q[k] * wb;
    }
    normalize4(out->rotation);
}

BreakSnapshotInterpResult break_snapshot_interp_sample(const BreakSnapshotInterp *si,
                                                       f64 render_tick,
                                                       BreakSnapshotPose *out) {
    u32 hi;
    if (!si || !out || !isfinite(render_tick)) return BREAK_SNAPSHOT_INTERP_INVALID;
    if (si->count == 0u) return BREAK_SNAPSHOT_INTERP_EMPTY;
    if (render_tick < (f64)si->ticks[0]) {
        *out = si->poses[0];
        return BREAK_SNAPSHOT_INTERP_HELD;
    }
    hi = 1u;
    while (hi < si->count && (f64)si->ticks[hi] < render_tick) ++hi;
    if (hi < si->count) {
        const u64 t0 = si->ticks[hi - 1u], t1 = si->ticks[hi];
        f64 span = (f64)(t1 - t0);
        if (span > (f64)si->cfg.max_gap_ticks) {
            /* no blend across a teleport: the older pose until the newer one is due */
            *out = render_tick >= (f64)t1 ? si->poses[hi] : si->poses[hi - 1u];
            return BREAK_SNAPSHOT_INTERP_HELD;
        }
        blend(&si->poses[hi - 1u], &si->poses[hi], (f32)((render_tick - (f64)t0) / span), out);
        return BREAK_SNAPSHOT_INTERP_INTERPOLATED;
    }
    /* past the newest snapshot */
    {
        const u32 last = si->count - 1u;
        f64 ahead = render_tick - (f64)si->ticks[last];
        f64 span;
        *out = si->poses[last];
        if (si->count < 2u || si->cfg.max_extrapolate_ticks <= 0.0f) return BREAK_SNAPSHOT_INTERP_HELD;
        span = (f64)(si->ticks[last] - si->ticks[last - 1u]);
        if (span > (f64)si->cfg.max_gap_ticks) return BREAK_SNAPSHOT_INTERP_HELD;
        {
            bool capped = ahead > (f64)si->cfg.max_extrapolate_ticks;
            f32 k = (f32)((capped ? (f64)si->cfg.max_extrapolate_ticks : ahead) / span);
            for (int i = 0; i < 3; ++i)
                out->position[i] += (si->poses[last].position[i] - si->poses[last - 1u].position[i]) * k;
            return capped ? BREAK_SNAPSHOT_INTERP_HELD : BREAK_SNAPSHOT_INTERP_EXTRAPOLATED;
        }
    }
}

u32 break_snapshot_interp_count(const BreakSnapshotInterp *si) { return si ? si->count : 0u; }
