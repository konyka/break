#pragma once

#include <core/types.h>
#include <physics/physics.h>
#include <renderer/camera.h>

#define SCENE_STATE_MAGIC_V1 0x534E4547u /* GENE: pos/vel */
#define SCENE_STATE_MAGIC_V2 0x32454E47u /* GEN2: +mass/is_static */
#define SCENE_STATE_MAGIC_V3 0x33454E47u /* GEN3: +half_extent/restitution */

#define SCENE_STATE_BODY_LIVE_MAX 256u
/* R393: pc is file-controlled. Saves only ever write physics->count (<= capacity),
 * but load must skip pc records to reach the water tail. Cap pc so a crafted file
 * cannot force millions of freads; forward-compat files with pc > capacity bulk-
 * skip the excess in one fseek. */
#define SCENE_STATE_MAX_PC 65536u
/* R401: reject absurd file sizes before streaming parse (pc cap alone allows
 * multi-MiB files with valid pc but junk that still burns CPU on freads). */
#define SCENE_STATE_MAX_FILE_BYTES (4u << 20)  /* 4 MiB */

typedef struct {
    Camera        *camera;
    f32           *sun_azimuth;
    f32           *sun_elevation;
    f32           *exposure;
    f32           *render_scale;
    i32           *render_scale_idx;
    const f32     *render_scale_options; /* 4 entries */
    PhysicsWorld  *physics;
    u32            frame_count;
    const bool    *body_live; /* SCENE_STATE_BODY_LIVE_MAX entries */
    f32           *water_y;
    bool          *water_enabled;
    bool           water_pipeline_valid;
} SceneStateCtx;

bool scene_state_save(const char *path, const SceneStateCtx *ctx);
bool scene_state_load(const char *path, SceneStateCtx *ctx);
