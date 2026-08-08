#include "scene_state.h"
#include <core/log.h>
#include <math/math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    Camera  camera;
    f32     sun_azimuth;
    f32     sun_elevation;
    f32     exposure;
    f32     render_scale;
    i32     render_scale_idx;
    bool    have_render_scale_idx;
    f32     water_y;
    bool    water_enabled;
    bool    bvh_dirty;
    RigidBody *bodies;
    u32     body_count;
} SceneStateBackup;

static bool scene_state_backup(const SceneStateCtx *ctx, SceneStateBackup *bk) {
    bk->camera = *ctx->camera;
    bk->sun_azimuth = *ctx->sun_azimuth;
    bk->sun_elevation = *ctx->sun_elevation;
    bk->exposure = *ctx->exposure;
    bk->render_scale = *ctx->render_scale;
    bk->have_render_scale_idx = ctx->render_scale_idx != NULL;
    if (bk->have_render_scale_idx)
        bk->render_scale_idx = *ctx->render_scale_idx;
    bk->water_y = *ctx->water_y;
    bk->water_enabled = *ctx->water_enabled;
    bk->bvh_dirty = ctx->physics->bvh_dirty;
    bk->body_count = ctx->physics->count;
    bk->bodies = NULL;
    if (bk->body_count > 0u) {
        bk->bodies = (RigidBody *)malloc((usize)bk->body_count * sizeof(RigidBody));
        if (!bk->bodies) return false;
        memcpy(bk->bodies, ctx->physics->bodies,
               (usize)bk->body_count * sizeof(RigidBody));
    }
    return true;
}

static void scene_state_backup_free(SceneStateBackup *bk) {
    free(bk->bodies);
    bk->bodies = NULL;
    bk->body_count = 0u;
}

static void scene_state_restore(const SceneStateCtx *ctx, const SceneStateBackup *bk) {
    *ctx->camera = bk->camera;
    *ctx->sun_azimuth = bk->sun_azimuth;
    *ctx->sun_elevation = bk->sun_elevation;
    *ctx->exposure = bk->exposure;
    *ctx->render_scale = bk->render_scale;
    if (bk->have_render_scale_idx)
        *ctx->render_scale_idx = bk->render_scale_idx;
    *ctx->water_y = bk->water_y;
    *ctx->water_enabled = bk->water_enabled;
    if (bk->body_count > 0u)
        memcpy(ctx->physics->bodies, bk->bodies,
               (usize)bk->body_count * sizeof(RigidBody));
    ctx->physics->bvh_dirty = bk->bvh_dirty;
}

static usize scene_state_record_bytes(bool v2, bool v3) {
    usize n = sizeof(Vec3) * 2u;
    if (v2) n += sizeof(f32) + sizeof(u8);
    if (v3) n += sizeof(Vec3) + sizeof(f32);
    return n;
}

static bool scene_state_vec3_finite(Vec3 v) {
    return isfinite(v.e[0]) && isfinite(v.e[1]) && isfinite(v.e[2]);
}

static bool scene_state_camera_finite(const Camera *camera) {
    if (!scene_state_vec3_finite(camera->position) ||
        !isfinite(camera->yaw) || !isfinite(camera->pitch) ||
        !isfinite(camera->fov) || !isfinite(camera->aspect) ||
        !isfinite(camera->near_plane) || !isfinite(camera->far_plane) ||
        !isfinite(camera->move_speed) || !isfinite(camera->mouse_sensitivity) ||
        !isfinite(camera->_cy) || !isfinite(camera->_sy) ||
        !isfinite(camera->_cp) || !isfinite(camera->_sp) ||
        !isfinite(camera->_proj_fov) || !isfinite(camera->_proj_aspect) ||
        !isfinite(camera->_proj_near) || !isfinite(camera->_proj_far))
        return false;
    for (u32 col = 0; col < 4u; col++) {
        for (u32 row = 0; row < 4u; row++) {
            if (!isfinite(camera->_proj.e[col][row])) return false;
        }
    }
    return true;
}

static bool scene_state_measure_file(FILE *f, long *out_size) {
    if (fseek(f, 0, SEEK_END) != 0) return false;
    long sz = ftell(f);
    if (sz < 0) return false;
    if (fseek(f, 0, SEEK_SET) != 0) return false;
    *out_size = sz;
    return true;
}

bool scene_state_save(const char *path, const SceneStateCtx *ctx) {
    if (!path || !ctx || !ctx->camera || !ctx->physics ||
        !ctx->sun_azimuth || !ctx->sun_elevation || !ctx->exposure ||
        !ctx->render_scale || !ctx->water_y || !ctx->water_enabled)
        return false;

    FILE *sf = fopen(path, "wb");
    if (!sf) return false;

    bool sv_ok = true;
    u32 magic = SCENE_STATE_MAGIC_V3;
    sv_ok &= fwrite(&magic, 4, 1, sf) == 1;
    sv_ok &= fwrite(&ctx->camera->position, sizeof(Camera), 1, sf) == 1;
    sv_ok &= fwrite(ctx->sun_azimuth, sizeof(f32), 1, sf) == 1;
    sv_ok &= fwrite(ctx->sun_elevation, sizeof(f32), 1, sf) == 1;
    sv_ok &= fwrite(ctx->exposure, sizeof(f32), 1, sf) == 1;
    sv_ok &= fwrite(ctx->render_scale, sizeof(f32), 1, sf) == 1;
    u32 pc = ctx->physics->count;
    sv_ok &= fwrite(&pc, sizeof(u32), 1, sf) == 1;
    for (u32 si = 0; si < pc && sv_ok; si++) {
        RigidBody *sb = &ctx->physics->bodies[si];
        Vec3 pos = sb->position;
        Vec3 vel = sb->velocity;
        Vec3 hext = sb->half_extent;
        f32 mass = sb->mass > 0.0f ? sb->mass : 1.0f;
        f32 rest = sb->restitution;
        u8 is_st = sb->is_static ? 1u : 0u;
        if (physics_body_is_parked(sb)) {
            pos = sb->spawn_pos;
            vel = vec3(0, 0, 0);
            is_st = 0u;
        }
        sv_ok &= fwrite(&pos, sizeof(Vec3), 1, sf) == 1;
        sv_ok &= fwrite(&vel, sizeof(Vec3), 1, sf) == 1;
        sv_ok &= fwrite(&mass, sizeof(f32), 1, sf) == 1;
        sv_ok &= fwrite(&is_st, sizeof(u8), 1, sf) == 1;
        sv_ok &= fwrite(&hext, sizeof(Vec3), 1, sf) == 1;
        sv_ok &= fwrite(&rest, sizeof(f32), 1, sf) == 1;
    }
    sv_ok &= fwrite(ctx->water_y, sizeof(f32), 1, sf) == 1;
    sv_ok &= fwrite(ctx->water_enabled, sizeof(bool), 1, sf) == 1;
    if (ferror(sf)) sv_ok = false;
    if (fclose(sf) != 0) sv_ok = false;
    if (!sv_ok) LOG_WARN("Scene state save: partial write failure");
    return sv_ok;
}

bool scene_state_load(const char *path, SceneStateCtx *ctx) {
    if (!path || !ctx || !ctx->camera || !ctx->physics ||
        !ctx->sun_azimuth || !ctx->sun_elevation || !ctx->exposure ||
        !ctx->render_scale || !ctx->water_y || !ctx->water_enabled)
        return false;

    FILE *lf = fopen(path, "rb");
    if (!lf) return false;

    long file_size = 0;
    if (!scene_state_measure_file(lf, &file_size)) {
        fclose(lf);
        return false;
    }
    if ((u64)file_size > (u64)SCENE_STATE_MAX_FILE_BYTES) {
        LOG_WARN("Scene state: file too large (%ld bytes)", file_size);
        fclose(lf);
        return false;
    }

    u32 magic = 0;
    bool ld_ok = fread(&magic, 4, 1, lf) == 1;
    bool v3 = (magic == SCENE_STATE_MAGIC_V3);
    bool v2 = (magic == SCENE_STATE_MAGIC_V2) || v3;
    if (!ld_ok || (magic != SCENE_STATE_MAGIC_V1 && !v2)) {
        fclose(lf);
        return false;
    }

    SceneStateBackup backup;
    memset(&backup, 0, sizeof(backup));
    if (!scene_state_backup(ctx, &backup)) {
        fclose(lf);
        return false;
    }

    ld_ok &= fread(&ctx->camera->position, sizeof(Camera), 1, lf) == 1;
    ld_ok &= fread(ctx->sun_azimuth, sizeof(f32), 1, lf) == 1;
    ld_ok &= fread(ctx->sun_elevation, sizeof(f32), 1, lf) == 1;
    ld_ok &= fread(ctx->exposure, sizeof(f32), 1, lf) == 1;
    ld_ok &= fread(ctx->render_scale, sizeof(f32), 1, lf) == 1;
    if (ld_ok && (!scene_state_camera_finite(ctx->camera) ||
                  !isfinite(*ctx->sun_azimuth) || !isfinite(*ctx->sun_elevation) ||
                  !isfinite(*ctx->exposure) || !isfinite(*ctx->render_scale)))
        ld_ok = false;
    if (ctx->render_scale_idx && ctx->render_scale_options) {
        for (i32 rsi = 0; rsi < 4; rsi++) {
            if (fabsf(*ctx->render_scale - ctx->render_scale_options[rsi]) < 1e-4f) {
                *ctx->render_scale_idx = rsi;
                break;
            }
        }
    }

    u32 pc = 0;
    ld_ok &= fread(&pc, sizeof(u32), 1, lf) == 1;
    long body_start = ftell(lf);
    if (body_start < 0) ld_ok = false;

    usize rec_bytes = scene_state_record_bytes(v2, v3);
    /* R393: reject pc that cannot fit in the file or exceeds SCENE_STATE_MAX_PC.
     * Water tail is optional on short files; require only the body region. */
    if (ld_ok) {
        if (pc > SCENE_STATE_MAX_PC) {
            LOG_WARN("Scene state: body count %u exceeds max %u", pc, SCENE_STATE_MAX_PC);
            ld_ok = false;
        } else if ((u64)pc * (u64)rec_bytes > (u64)(file_size - body_start)) {
            LOG_WARN("Scene state: body table extends past EOF (%u records)", pc);
            ld_ok = false;
        }
    }

    for (u32 si = 0; si < pc && ld_ok; si++) {
        /* R393: once si passes live physics slots, skip the rest in one fseek
         * instead of one fread per record (DoS when pc is large but > capacity). */
        if (si >= ctx->physics->count) {
            u32 remaining = pc - si;
            u64 skip = (u64)remaining * (u64)rec_bytes;
            if (fseek(lf, (long)skip, SEEK_CUR) != 0)
                ld_ok = false;
            break;
        }

        Vec3 pos, vel, hext = vec3(0.5f, 0.5f, 0.5f);
        f32 mass = 1.0f, rest = 0.3f;
        u8 is_st = 0;
        ld_ok &= fread(&pos, sizeof(Vec3), 1, lf) == 1;
        ld_ok &= fread(&vel, sizeof(Vec3), 1, lf) == 1;
        if (v2) {
            ld_ok &= fread(&mass, sizeof(f32), 1, lf) == 1;
            ld_ok &= fread(&is_st, sizeof(u8), 1, lf) == 1;
        }
        if (v3) {
            ld_ok &= fread(&hext, sizeof(Vec3), 1, lf) == 1;
            ld_ok &= fread(&rest, sizeof(f32), 1, lf) == 1;
        }
        if (ld_ok && (!scene_state_vec3_finite(pos) || !scene_state_vec3_finite(vel) ||
                      !isfinite(mass) || !scene_state_vec3_finite(hext) ||
                      !isfinite(rest)))
            ld_ok = false;
        bool live = ctx->body_live && si < SCENE_STATE_BODY_LIVE_MAX && ctx->body_live[si];
        if (ld_ok && live && pos.e[1] > -999.0f) {
            RigidBody *rb = &ctx->physics->bodies[si];
            if (!v2 && rb->mass > 0.0f) mass = rb->mass;
            physics_body_revive(rb, mass, is_st != 0, ctx->frame_count);
            rb->position = pos;
            rb->velocity = vel;
            if (v3) {
                rb->half_extent = hext;
                rb->restitution = rest;
            }
        } else if (ld_ok && !live && si > 0 &&
                   !physics_body_is_parked(&ctx->physics->bodies[si])) {
            physics_body_park(ctx->physics, si);
        }
    }

    if (ld_ok && pc > 0) ctx->physics->bvh_dirty = true;
    /* R431: the R393 "optional tail" guard used !feof(lf), but feof only sets
     * AFTER a read past EOF — a short file never had it set here, so the tail
     * was effectively mandatory (fread failed, ld_ok went false, full restore
     * rejected). Check the remaining bytes instead: read the water tail only
     * when it is actually present. */
    long tail_off = ftell(lf);
    if (ld_ok && tail_off >= 0 &&
        (u64)(file_size - tail_off) >= (u64)(sizeof(f32) + sizeof(bool))) {
        ld_ok &= fread(ctx->water_y, sizeof(f32), 1, lf) == 1;
        ld_ok &= fread(ctx->water_enabled, sizeof(bool), 1, lf) == 1;
        if (ld_ok && !isfinite(*ctx->water_y)) ld_ok = false;
        if (!ctx->water_pipeline_valid)
            *ctx->water_enabled = false;
    }
    if (!ld_ok) LOG_WARN("Scene state load: partial read failure");
    else LOG_INFO("Runtime state restored (%u bodies)", pc);

    if (!ld_ok)
        scene_state_restore(ctx, &backup);
    scene_state_backup_free(&backup);

    fclose(lf);
    return ld_ok;
}
