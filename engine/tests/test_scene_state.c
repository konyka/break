#include "test_framework.h"
#include <scene/scene_state.h>
#include <physics/physics.h>
#include <renderer/camera.h>
#include <math.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

/* R444: per-pid path — parallel ctest trees raced on the fixed name. */
static const char *scene_state_tmp_path(void)
{
    static char b[128];
    return test_tmp(b, sizeof b, "test_scene_state.bin");
}
#define TMP_STATE scene_state_tmp_path()

static SceneStateCtx make_ctx(Camera *cam, PhysicsWorld *pw, f32 *sun_a, f32 *sun_e,
                              f32 *exp, f32 *scale, f32 *wy, bool *wen) {
    SceneStateCtx ctx = {0};
    ctx.camera = cam;
    ctx.sun_azimuth = sun_a;
    ctx.sun_elevation = sun_e;
    ctx.exposure = exp;
    ctx.render_scale = scale;
    ctx.physics = pw;
    ctx.water_y = wy;
    ctx.water_enabled = wen;
    return ctx;
}

TEST(scene_state_roundtrip)
{
    Camera cam = {0};
    cam.position = vec3(1, 2, 3);
    f32 sun_a = 0.5f, sun_e = 0.25f, exp = 1.5f, scale = 1.0f;
    f32 wy = -2.0f;
    bool wen = true;

    PhysicsWorld *pw = physics_world_create(8);
    ASSERT_NOT_NULL(pw);
    pw->count = 2;
    pw->bodies[0].position = vec3(0, 1, 0);
    pw->bodies[0].velocity = vec3(0, 0, 0);
    pw->bodies[0].mass = 1.0f;
    pw->bodies[1].position = vec3(3, 4, 5);
    pw->bodies[1].velocity = vec3(1, 0, 0);
    pw->bodies[1].mass = 2.0f;

    SceneStateCtx sctx = make_ctx(&cam, pw, &sun_a, &sun_e, &exp, &scale, &wy, &wen);
    ASSERT_TRUE(scene_state_save(TMP_STATE, &sctx));

    cam.position = vec3(0, 0, 0);
    sun_a = 0.0f;
    wy = 0.0f;
    bool live[SCENE_STATE_BODY_LIVE_MAX] = {0};
    live[1] = true;

    SceneStateCtx lctx = make_ctx(&cam, pw, &sun_a, &sun_e, &exp, &scale, &wy, &wen);
    lctx.body_live = live;
    lctx.frame_count = 42u;
    lctx.water_pipeline_valid = true;
    ASSERT_TRUE(scene_state_load(TMP_STATE, &lctx));

    ASSERT_TRUE(fabsf(cam.position.e[0] - 1.0f) < 1e-4f);
    ASSERT_TRUE(fabsf(sun_a - 0.5f) < 1e-4f);
    ASSERT_TRUE(fabsf(wy - (-2.0f)) < 1e-4f);
    ASSERT_TRUE(wen);
    ASSERT_TRUE(fabsf(pw->bodies[1].position.e[0] - 3.0f) < 1e-4f);

    physics_world_destroy(pw);
    remove(TMP_STATE);
}

/* R484: stdio may report state-save write errors only during fclose. */
TEST(scene_state_save_reports_close_failure)
{
#if defined(ENGINE_PLATFORM_WINDOWS)
    /* /dev/full is a POSIX error-injection facility. */
#else
    Camera cam = {0};
    f32 sun_a = 0, sun_e = 0, exp = 1, scale = 1, wy = 0;
    bool wen = false;
    PhysicsWorld *pw = physics_world_create(1);
    ASSERT_NOT_NULL(pw);

    SceneStateCtx ctx = make_ctx(&cam, pw, &sun_a, &sun_e, &exp, &scale, &wy, &wen);
    ASSERT_FALSE(scene_state_save("/dev/full", &ctx));

    physics_world_destroy(pw);
#endif
}

/* R393: pc had no cap — UINT32_MAX against a padded file could loop forever on
 * skip-record freads (DoS). */
TEST(scene_state_rejects_excessive_pc)
{
    Camera cam = {0};
    f32 sun_a = 0, sun_e = 0, exp = 1, scale = 1, wy = 0;
    bool wen = false;
    PhysicsWorld *pw = physics_world_create(4);
    ASSERT_NOT_NULL(pw);

    SceneStateCtx sctx = make_ctx(&cam, pw, &sun_a, &sun_e, &exp, &scale, &wy, &wen);
    pw->count = 0;
    ASSERT_TRUE(scene_state_save(TMP_STATE, &sctx));

    FILE *f = fopen(TMP_STATE, "r+b");
    ASSERT_NOT_NULL(f);
    u32 pc = SCENE_STATE_MAX_PC + 1u;
    fseek(f, (long)(4 + sizeof(Camera) + 4 * sizeof(f32)), SEEK_SET);
    fwrite(&pc, sizeof(pc), 1, f);
    fclose(f);

    SceneStateCtx lctx = make_ctx(&cam, pw, &sun_a, &sun_e, &exp, &scale, &wy, &wen);
    ASSERT_TRUE(!scene_state_load(TMP_STATE, &lctx));

    physics_world_destroy(pw);
    remove(TMP_STATE);
}

/* R393: pc claiming more records than bytes following must fail before the loop. */
TEST(scene_state_rejects_pc_past_eof)
{
    Camera cam = {0};
    f32 sun_a = 0, sun_e = 0, exp = 1, scale = 1, wy = 0;
    bool wen = false;
    PhysicsWorld *pw = physics_world_create(4);
    ASSERT_NOT_NULL(pw);

    SceneStateCtx sctx = make_ctx(&cam, pw, &sun_a, &sun_e, &exp, &scale, &wy, &wen);
    pw->count = 1;
    ASSERT_TRUE(scene_state_save(TMP_STATE, &sctx));

    /* Bump pc in the saved file without adding body bytes. */
    FILE *f = fopen(TMP_STATE, "r+b");
    ASSERT_NOT_NULL(f);
    u32 pc = 500u;
    fseek(f, (long)(4 + sizeof(Camera) + 4 * sizeof(f32)), SEEK_SET);
    fwrite(&pc, sizeof(pc), 1, f);
    fclose(f);

    SceneStateCtx lctx = make_ctx(&cam, pw, &sun_a, &sun_e, &exp, &scale, &wy, &wen);
    ASSERT_TRUE(!scene_state_load(TMP_STATE, &lctx));

    physics_world_destroy(pw);
    remove(TMP_STATE);
}

/* R404: partial load must not leave camera/physics mutated on failure. */
TEST(scene_state_load_failure_preserves_runtime)
{
    Camera cam = {0};
    cam.position = vec3(9, 9, 9);
    f32 sun_a = 1.0f, sun_e = 2.0f, exp = 3.0f, scale = 4.0f;
    f32 wy = 5.0f;
    bool wen = true;

    PhysicsWorld *pw = physics_world_create(4);
    ASSERT_NOT_NULL(pw);
    pw->count = 1;
    pw->bodies[0].position = vec3(10, 11, 12);
    pw->bodies[0].velocity = vec3(0, 0, 0);

    SceneStateCtx sctx = make_ctx(&cam, pw, &sun_a, &sun_e, &exp, &scale, &wy, &wen);
    cam.position = vec3(1, 2, 3);
    sun_a = 0.5f;
    wy = -1.0f;
    ASSERT_TRUE(scene_state_save(TMP_STATE, &sctx));

    cam.position = vec3(9, 9, 9);
    sun_a = 1.0f;
    sun_e = 2.0f;
    exp = 3.0f;
    scale = 4.0f;
    wy = 5.0f;
    wen = true;

    FILE *f = fopen(TMP_STATE, "r+b");
    ASSERT_NOT_NULL(f);
    u32 pc = SCENE_STATE_MAX_PC + 1u;
    fseek(f, (long)(4 + sizeof(Camera) + 4 * sizeof(f32)), SEEK_SET);
    fwrite(&pc, sizeof(pc), 1, f);
    fclose(f);

    SceneStateCtx lctx = make_ctx(&cam, pw, &sun_a, &sun_e, &exp, &scale, &wy, &wen);
    ASSERT_TRUE(!scene_state_load(TMP_STATE, &lctx));

    ASSERT_TRUE(fabsf(cam.position.e[0] - 9.0f) < 1e-4f);
    ASSERT_TRUE(fabsf(cam.position.e[1] - 9.0f) < 1e-4f);
    ASSERT_TRUE(fabsf(cam.position.e[2] - 9.0f) < 1e-4f);
    ASSERT_TRUE(fabsf(sun_a - 1.0f) < 1e-4f);
    ASSERT_TRUE(fabsf(wy - 5.0f) < 1e-4f);
    ASSERT_TRUE(wen);
    ASSERT_TRUE(fabsf(pw->bodies[0].position.e[0] - 10.0f) < 1e-4f);

    physics_world_destroy(pw);
    remove(TMP_STATE);
}

TEST(scene_state_rejects_oversized_file)
{
    FILE *f = fopen(TMP_STATE, "wb");
    ASSERT_NOT_NULL(f);
#if defined(_POSIX_C_SOURCE) && _POSIX_C_SOURCE >= 200112L
    ASSERT_TRUE(ftruncate(fileno(f), (off_t)SCENE_STATE_MAX_FILE_BYTES + 1) == 0);
#else
    if (fseek(f, (long)SCENE_STATE_MAX_FILE_BYTES, SEEK_SET) == 0) fputc('x', f);
#endif
    fclose(f);

    Camera cam = {0};
    f32 sun_a = 0, sun_e = 0, exp = 1, scale = 1, wy = 0;
    bool wen = false;
    PhysicsWorld *pw = physics_world_create(4);
    ASSERT_NOT_NULL(pw);

    SceneStateCtx lctx = make_ctx(&cam, pw, &sun_a, &sun_e, &exp, &scale, &wy, &wen);
    ASSERT_TRUE(!scene_state_load(TMP_STATE, &lctx));

    physics_world_destroy(pw);
    remove(TMP_STATE);
}

/* R431: the water tail is optional, but the old `!feof(lf)` guard made it
 * mandatory — feof only sets after a read PAST EOF, so a tail-less file
 * failed the water fread, flipped ld_ok, and triggered a full restore. A
 * file without the tail must load successfully and leave the water state
 * untouched. */
TEST(scene_state_load_without_water_tail)
{
    Camera cam = {0};
    cam.position = vec3(1, 2, 3);
    f32 sun_a = 0.5f, sun_e = 0.25f, exp = 1.5f, scale = 1.0f;
    f32 wy = -2.0f;
    bool wen = true;

    PhysicsWorld *pw = physics_world_create(4);
    ASSERT_NOT_NULL(pw);
    pw->count = 1;
    pw->bodies[0].position = vec3(3, 4, 5);
    pw->bodies[0].velocity = vec3(0, 0, 0);
    pw->bodies[0].mass = 1.0f;

    SceneStateCtx sctx = make_ctx(&cam, pw, &sun_a, &sun_e, &exp, &scale, &wy, &wen);
    ASSERT_TRUE(scene_state_save(TMP_STATE, &sctx));

    /* Rewrite the file without the optional water tail (f32 + u8 flag). */
    FILE *f = fopen(TMP_STATE, "rb");
    ASSERT_NOT_NULL(f);
    u8 bytes[4096];
    usize n = fread(bytes, 1, sizeof(bytes), f);
    fclose(f);
    ASSERT_TRUE(n > sizeof(f32) + sizeof(u8));
    n -= sizeof(f32) + sizeof(u8);
    f = fopen(TMP_STATE, "wb");
    ASSERT_NOT_NULL(f);
    ASSERT_TRUE(fwrite(bytes, 1, n, f) == n);
    fclose(f);

    cam.position = vec3(0, 0, 0);
    wy = 7.0f;
    wen = false;

    SceneStateCtx lctx = make_ctx(&cam, pw, &sun_a, &sun_e, &exp, &scale, &wy, &wen);
    ASSERT_TRUE(scene_state_load(TMP_STATE, &lctx));

    ASSERT_TRUE(fabsf(cam.position.e[0] - 1.0f) < 1e-4f);
    /* No tail was present, so the water state stays as the app left it. */
    ASSERT_TRUE(fabsf(wy - 7.0f) < 1e-4f);
    ASSERT_TRUE(!wen);

    physics_world_destroy(pw);
    remove(TMP_STATE);
}

/* Persisted floating-point data is untrusted: reject NaN in every loaded
 * value family and restore the runtime state rather than propagating it. */
TEST(scene_state_rejects_nonfinite_values)
{
    Camera cam = {0};
    cam.position = vec3(1, 2, 3);
    cam.yaw = 0.1f;
    cam._proj.e[2][1] = 1.0f;
    f32 sun_a = 0.5f, sun_e = 0.25f, exp = 1.5f, scale = 1.0f;
    f32 wy = -2.0f;
    bool wen = true;
    PhysicsWorld *pw = physics_world_create(2);
    ASSERT_NOT_NULL(pw);
    pw->count = 1;
    pw->bodies[0].position = vec3(3, 4, 5);
    pw->bodies[0].velocity = vec3(6, 7, 8);
    pw->bodies[0].mass = 2.0f;
    pw->bodies[0].half_extent = vec3(0.5f, 0.75f, 1.0f);
    pw->bodies[0].restitution = 0.3f;

    SceneStateCtx sctx = make_ctx(&cam, pw, &sun_a, &sun_e, &exp, &scale, &wy, &wen);
    const long body_off = (long)(4 + sizeof(Camera) + 4 * sizeof(f32) + sizeof(u32));
    const long offsets[] = {
        4 + (long)offsetof(Camera, position) + 2 * (long)sizeof(f32),
        4 + (long)offsetof(Camera, yaw),
        4 + (long)offsetof(Camera, _proj) + 9 * (long)sizeof(f32),
        4 + (long)sizeof(Camera) + (long)sizeof(f32),
        body_off + (long)sizeof(Vec3) - (long)sizeof(f32),
        body_off + (long)sizeof(Vec3) + (long)sizeof(Vec3) - (long)sizeof(f32),
        body_off + 2 * (long)sizeof(Vec3),
        body_off + 2 * (long)sizeof(Vec3) + (long)sizeof(f32) + sizeof(u8) +
            (long)sizeof(Vec3) - (long)sizeof(f32),
        body_off + 3 * (long)sizeof(Vec3) + (long)sizeof(f32) + sizeof(u8),
        body_off + 3 * (long)sizeof(Vec3) + 2 * (long)sizeof(f32) + sizeof(u8),
    };

    bool live[SCENE_STATE_BODY_LIVE_MAX] = {0};
    live[0] = true;
    SceneStateCtx lctx = make_ctx(&cam, pw, &sun_a, &sun_e, &exp, &scale, &wy, &wen);
    lctx.body_live = live;
    lctx.water_pipeline_valid = true;

    for (usize oi = 0; oi < sizeof(offsets) / sizeof(offsets[0]); oi++) {
        ASSERT_TRUE(scene_state_save(TMP_STATE, &sctx));
        FILE *f = fopen(TMP_STATE, "r+b");
        ASSERT_NOT_NULL(f);
        const f32 nonfinite = NAN;
        ASSERT_TRUE(fseek(f, offsets[oi], SEEK_SET) == 0);
        ASSERT_TRUE(fwrite(&nonfinite, sizeof(nonfinite), 1, f) == 1);
        ASSERT_TRUE(fclose(f) == 0);

        cam.position = vec3(9, 9, 9);
        sun_a = 9.0f;
        wy = 9.0f;
        pw->bodies[0].position = vec3(9, 9, 9);

        ASSERT_FALSE(scene_state_load(TMP_STATE, &lctx));
        ASSERT_TRUE(fabsf(cam.position.e[0] - 9.0f) < 1e-4f);
        ASSERT_TRUE(fabsf(sun_a - 9.0f) < 1e-4f);
        ASSERT_TRUE(fabsf(wy - 9.0f) < 1e-4f);
        ASSERT_TRUE(fabsf(pw->bodies[0].position.e[0] - 9.0f) < 1e-4f);
    }

    physics_world_destroy(pw);
    remove(TMP_STATE);
}

/* Saving a value which the loader rejects produces an unusable checkpoint.
 * Validate before opening the destination so a failed save keeps the last
 * recoverable state intact. */
TEST(scene_state_save_rejects_nonfinite_values)
{
    Camera cam = {0};
    cam.position = vec3(1, 2, 3);
    cam.yaw = 0.1f;
    cam._proj.e[2][1] = 1.0f;
    f32 sun_a = 0.5f, sun_e = 0.25f, exp = 1.5f, scale = 1.0f;
    f32 wy = -2.0f;
    bool wen = true;
    PhysicsWorld *pw = physics_world_create(1);
    ASSERT_NOT_NULL(pw);
    pw->count = 1;
    pw->bodies[0].position = vec3(3, 4, 5);
    pw->bodies[0].velocity = vec3(6, 7, 8);
    pw->bodies[0].mass = 2.0f;
    pw->bodies[0].half_extent = vec3(0.5f, 0.75f, 1.0f);
    pw->bodies[0].restitution = 0.3f;

    SceneStateCtx ctx = make_ctx(&cam, pw, &sun_a, &sun_e, &exp, &scale, &wy, &wen);
    ASSERT_TRUE(scene_state_save(TMP_STATE, &ctx));

    FILE *f = fopen(TMP_STATE, "rb");
    ASSERT_NOT_NULL(f);
    ASSERT_TRUE(fseek(f, 0, SEEK_END) == 0);
    long saved_size = ftell(f);
    ASSERT_TRUE(saved_size > 0);
    ASSERT_TRUE(fseek(f, 0, SEEK_SET) == 0);
    u8 *saved = (u8 *)malloc((usize)saved_size);
    ASSERT_NOT_NULL(saved);
    ASSERT_EQ(fread(saved, 1, (usize)saved_size, f), (usize)saved_size);
    ASSERT_EQ(fclose(f), 0);

    f32 *values[] = {
        &cam.yaw,
        &sun_e,
        &pw->bodies[0].velocity.e[2],
        &pw->bodies[0].half_extent.e[1],
        &pw->bodies[0].restitution,
        &wy,
    };
    for (usize i = 0; i < sizeof(values) / sizeof(values[0]); i++) {
        *values[i] = NAN;
        ASSERT_FALSE(scene_state_save(TMP_STATE, &ctx));

        f = fopen(TMP_STATE, "rb");
        ASSERT_NOT_NULL(f);
        u8 current[4096];
        ASSERT_TRUE((usize)saved_size <= sizeof(current));
        ASSERT_EQ(fread(current, 1, (usize)saved_size, f), (usize)saved_size);
        ASSERT_EQ(fclose(f), 0);
        ASSERT_TRUE(memcmp(current, saved, (usize)saved_size) == 0);
        *values[i] = 1.0f;
    }

    free(saved);
    physics_world_destroy(pw);
    remove(TMP_STATE);
}

/* The on-disk water flag is a canonical byte, not an arbitrary C bool object
 * representation. Invalid input must fail without changing live state. */
TEST(scene_state_rejects_noncanonical_water_flag)
{
    Camera cam = {0};
    cam.position = vec3(1, 2, 3);
    f32 sun_a = 0.5f, sun_e = 0.25f, exp = 1.5f, scale = 1.0f;
    f32 wy = -2.0f;
    bool wen = true;
    PhysicsWorld *pw = physics_world_create(1);
    ASSERT_NOT_NULL(pw);

    SceneStateCtx sctx = make_ctx(&cam, pw, &sun_a, &sun_e, &exp, &scale, &wy, &wen);
    ASSERT_TRUE(scene_state_save(TMP_STATE, &sctx));

    FILE *f = fopen(TMP_STATE, "r+b");
    ASSERT_NOT_NULL(f);
    ASSERT_TRUE(fseek(f, -1L, SEEK_END) == 0);
    const u8 invalid_flag = 2u;
    ASSERT_EQ(fwrite(&invalid_flag, 1, 1, f), (usize)1);
    ASSERT_EQ(fclose(f), 0);

    wy = 9.0f;
    wen = true;
    SceneStateCtx lctx = make_ctx(&cam, pw, &sun_a, &sun_e, &exp, &scale, &wy, &wen);
    lctx.water_pipeline_valid = true;
    ASSERT_FALSE(scene_state_load(TMP_STATE, &lctx));
    ASSERT_FLOAT_EQ(wy, 9.0f, 1e-6f);
    ASSERT_TRUE(wen);

    physics_world_destroy(pw);
    remove(TMP_STATE);
}

TEST_MAIN_BEGIN()
    RUN_TEST(scene_state_roundtrip);
    RUN_TEST(scene_state_save_reports_close_failure);
    RUN_TEST(scene_state_rejects_excessive_pc);
    RUN_TEST(scene_state_rejects_pc_past_eof);
    RUN_TEST(scene_state_load_failure_preserves_runtime);
    RUN_TEST(scene_state_rejects_oversized_file);
    RUN_TEST(scene_state_load_without_water_tail);
    RUN_TEST(scene_state_rejects_nonfinite_values);
    RUN_TEST(scene_state_save_rejects_nonfinite_values);
    RUN_TEST(scene_state_rejects_noncanonical_water_flag);
TEST_MAIN_END()
