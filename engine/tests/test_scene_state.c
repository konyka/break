#include "test_framework.h"
#include <scene/scene_state.h>
#include <physics/physics.h>
#include <renderer/camera.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

#define TMP_STATE "/tmp/test_scene_state.bin"

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

TEST_MAIN_BEGIN()
    RUN_TEST(scene_state_roundtrip);
    RUN_TEST(scene_state_rejects_excessive_pc);
    RUN_TEST(scene_state_rejects_pc_past_eof);
    RUN_TEST(scene_state_load_failure_preserves_runtime);
    RUN_TEST(scene_state_rejects_oversized_file);
TEST_MAIN_END()
