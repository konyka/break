/* test_asset_gltf.c — glTF loader input validation (R390)
 *
 * asset.c had no test coverage. It called cgltf_parse + cgltf_load_buffers and
 * went straight to reading vertex data, skipping cgltf_validate — the only step
 * that checks an accessor's span against its bufferView and a bufferView against
 * its buffer. Those are exactly the invariants cgltf_buffer_data and the
 * attribute loops assume.
 *
 * The malicious models below are generated at run time rather than committed as
 * binary fixtures, so what each one attacks stays readable. Every attribute loop
 * runs before the first rhi_buffer_create, so the out-of-bounds read reproduces
 * with stub RHI symbols and dev = NULL.
 */

#include "test_framework.h"
#include <asset/asset.h>
#include <asset/async_loader.h>
#include <rhi/rhi.h>
#include <stdio.h>
#include <string.h>

/* ---- RHI stubs (link-only) ---- */

RHIDevice *g_current_device = NULL;

static RHIBuffer  s_null_buffer  = {0};
static RHITexture s_null_texture = {0};

RHIBuffer rhi_buffer_create(RHIDevice *dev, const RHIBufferDesc *desc) {
    (void)dev; (void)desc; return s_null_buffer;
}
void rhi_buffer_destroy(RHIDevice *dev, RHIBuffer buf) { (void)dev; (void)buf; }
void rhi_buffer_update(RHIDevice *dev, RHIBuffer buf, const void *data, usize size) {
    (void)dev; (void)buf; (void)data; (void)size;
}
u32 rhi_frame_index(RHIDevice *dev) { (void)dev; return 0u; }
RHITexture rhi_texture_create(RHIDevice *dev, const RHITextureDesc *desc) {
    (void)dev; (void)desc; return s_null_texture;
}
void rhi_texture_destroy(RHIDevice *dev, RHITexture tex) { (void)dev; (void)tex; }

/* Async loader stubs: asset.c's async entry points are not exercised here, but
 * they must resolve at link time. */
u64 async_loader_request(const char *path, AsyncLoadCallback callback, void *user_data) {
    (void)path; (void)callback; (void)user_data; return 0u;
}
u64 async_loader_request_texture(const char *path, AsyncLoadCallback callback,
                                 void *user_data, i32 priority) {
    (void)path; (void)callback; (void)user_data; (void)priority; return 0u;
}

/* ---- helpers ---- */

static const char *TMP_GLTF = "/tmp/test_asset_gltf.gltf";

static bool write_text(const char *path, const char *text) {
    FILE *f = fopen(path, "wb");
    if (!f) return false;
    usize n = strlen(text);
    bool ok = fwrite(text, 1, n, f) == n;
    fclose(f);
    return ok;
}

/* A 36-byte buffer holds exactly 3 VEC3 floats; every model below declares far
 * more than that so the mismatch is unambiguous. */
static const char *BUF36 =
    "\"buffers\":[{\"byteLength\":36,\"uri\":\"data:application/octet-stream;base64,"
    "AAAAAAAAAAAAAAAAAACAPwAAAAAAAAAAAAAAAAAAgD8AAAAA\"}]";

/* ---- tests ---- */

/* R390: accessor count far beyond its bufferView. Pre-fix the POSITION loop read
 * 200000 * 12 bytes out of a 36-byte heap block (ASan: READ of size 12 after a
 * 36-byte region). */
TEST(gltf_rejects_accessor_count_past_buffer_view)
{
    char json[1024];
    snprintf(json, sizeof(json),
             "{\"asset\":{\"version\":\"2.0\"},\"scene\":0,"
             "\"scenes\":[{\"nodes\":[0]}],\"nodes\":[{\"mesh\":0}],"
             "\"meshes\":[{\"primitives\":[{\"attributes\":{\"POSITION\":0}}]}],"
             "\"accessors\":[{\"bufferView\":0,\"componentType\":5126,"
             "\"count\":200000,\"type\":\"VEC3\"}],"
             "\"bufferViews\":[{\"buffer\":0,\"byteOffset\":0,\"byteLength\":36}],"
             "%s}", BUF36);
    ASSERT_TRUE(write_text(TMP_GLTF, json));

    AssetCtx ctx;
    asset_ctx_init(&ctx, NULL);
    ctx.vfs = NULL;
    Scene scene;
    memset(&scene, 0, sizeof(scene));

    ASSERT_TRUE(!asset_load_gltf(&ctx, TMP_GLTF, &scene));
    remove(TMP_GLTF);
}

/* R390: accessor byteOffset placing an otherwise-small span past the view end. */
TEST(gltf_rejects_accessor_offset_past_buffer_view)
{
    char json[1024];
    snprintf(json, sizeof(json),
             "{\"asset\":{\"version\":\"2.0\"},\"scene\":0,"
             "\"scenes\":[{\"nodes\":[0]}],\"nodes\":[{\"mesh\":0}],"
             "\"meshes\":[{\"primitives\":[{\"attributes\":{\"POSITION\":0}}]}],"
             "\"accessors\":[{\"bufferView\":0,\"byteOffset\":1000000,"
             "\"componentType\":5126,\"count\":3,\"type\":\"VEC3\"}],"
             "\"bufferViews\":[{\"buffer\":0,\"byteOffset\":0,\"byteLength\":36}],"
             "%s}", BUF36);
    ASSERT_TRUE(write_text(TMP_GLTF, json));

    AssetCtx ctx;
    asset_ctx_init(&ctx, NULL);
    ctx.vfs = NULL;
    Scene scene;
    memset(&scene, 0, sizeof(scene));

    ASSERT_TRUE(!asset_load_gltf(&ctx, TMP_GLTF, &scene));
    remove(TMP_GLTF);
}

/* R390: bufferView extending past the end of its buffer. */
TEST(gltf_rejects_buffer_view_past_buffer)
{
    char json[1024];
    snprintf(json, sizeof(json),
             "{\"asset\":{\"version\":\"2.0\"},\"scene\":0,"
             "\"scenes\":[{\"nodes\":[0]}],\"nodes\":[{\"mesh\":0}],"
             "\"meshes\":[{\"primitives\":[{\"attributes\":{\"POSITION\":0}}]}],"
             "\"accessors\":[{\"bufferView\":0,\"componentType\":5126,"
             "\"count\":3,\"type\":\"VEC3\"}],"
             "\"bufferViews\":[{\"buffer\":0,\"byteOffset\":24,\"byteLength\":500000}],"
             "%s}", BUF36);
    ASSERT_TRUE(write_text(TMP_GLTF, json));

    AssetCtx ctx;
    asset_ctx_init(&ctx, NULL);
    ctx.vfs = NULL;
    Scene scene;
    memset(&scene, 0, sizeof(scene));

    ASSERT_TRUE(!asset_load_gltf(&ctx, TMP_GLTF, &scene));
    remove(TMP_GLTF);
}

/* R390: index accessor count past its view — the index loop is separate from the
 * attribute loops, so it needs its own case. */
TEST(gltf_rejects_index_count_past_buffer_view)
{
    char json[1280];
    snprintf(json, sizeof(json),
             "{\"asset\":{\"version\":\"2.0\"},\"scene\":0,"
             "\"scenes\":[{\"nodes\":[0]}],\"nodes\":[{\"mesh\":0}],"
             "\"meshes\":[{\"primitives\":[{\"attributes\":{\"POSITION\":0},"
             "\"indices\":1}]}],"
             "\"accessors\":[{\"bufferView\":0,\"componentType\":5126,"
             "\"count\":3,\"type\":\"VEC3\"},"
             "{\"bufferView\":1,\"componentType\":5125,"
             "\"count\":100000,\"type\":\"SCALAR\"}],"
             "\"bufferViews\":[{\"buffer\":0,\"byteOffset\":0,\"byteLength\":36},"
             "{\"buffer\":0,\"byteOffset\":0,\"byteLength\":12}],"
             "%s}", BUF36);
    ASSERT_TRUE(write_text(TMP_GLTF, json));

    AssetCtx ctx;
    asset_ctx_init(&ctx, NULL);
    ctx.vfs = NULL;
    Scene scene;
    memset(&scene, 0, sizeof(scene));

    ASSERT_TRUE(!asset_load_gltf(&ctx, TMP_GLTF, &scene));
    remove(TMP_GLTF);
}

/* A well-formed model must still load, or the guard above would be a silent
 * regression in model loading — the success branch is otherwise untested. */
TEST(gltf_accepts_well_formed_model)
{
    char json[1024];
    snprintf(json, sizeof(json),
             "{\"asset\":{\"version\":\"2.0\"},\"scene\":0,"
             "\"scenes\":[{\"nodes\":[0]}],\"nodes\":[{\"mesh\":0}],"
             "\"meshes\":[{\"primitives\":[{\"attributes\":{\"POSITION\":0}}]}],"
             "\"accessors\":[{\"bufferView\":0,\"componentType\":5126,"
             "\"count\":3,\"type\":\"VEC3\"}],"
             "\"bufferViews\":[{\"buffer\":0,\"byteOffset\":0,\"byteLength\":36}],"
             "%s}", BUF36);
    ASSERT_TRUE(write_text(TMP_GLTF, json));

    AssetCtx ctx;
    asset_ctx_init(&ctx, NULL);
    ctx.vfs = NULL;
    Scene scene;
    memset(&scene, 0, sizeof(scene));

    bool loaded = asset_load_gltf(&ctx, TMP_GLTF, &scene);
    ASSERT_TRUE(loaded);
    ASSERT_EQ(scene.node_count, 1u);
    ASSERT_EQ(scene.mesh_count, 1u);

    asset_scene_free(&ctx, &scene);
    remove(TMP_GLTF);
}

TEST_MAIN_BEGIN()
    RUN_TEST(gltf_rejects_accessor_count_past_buffer_view);
    RUN_TEST(gltf_rejects_accessor_offset_past_buffer_view);
    RUN_TEST(gltf_rejects_buffer_view_past_buffer);
    RUN_TEST(gltf_rejects_index_count_past_buffer_view);
    RUN_TEST(gltf_accepts_well_formed_model);
TEST_MAIN_END()
