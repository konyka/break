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

/* R411: cgltf_size counts are file-controlled but the loader stores counts in
 * u32 and allocates count*sizeof(Vertex/Index). Reject extreme declarations
 * before casts or allocations, even if cgltf_validate accepts the JSON shape. */
TEST(gltf_rejects_extreme_accessor_count_before_alloc)
{
    char json[1024];
    snprintf(json, sizeof(json),
             "{\"asset\":{\"version\":\"2.0\"},\"scene\":0,"
             "\"scenes\":[{\"nodes\":[0]}],\"nodes\":[{\"mesh\":0}],"
             "\"meshes\":[{\"primitives\":[{\"attributes\":{\"POSITION\":0}}]}],"
             "\"accessors\":[{\"bufferView\":0,\"componentType\":5126,"
             "\"count\":10000001,\"type\":\"VEC3\"}],"
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

/* A 40-byte buffer: large enough that a 3xVEC3 span still fits after being
 * nudged off alignment, so the misaligned cases below pass cgltf_validate's size
 * checks and reach the actual load. */
static const char *BUF40 =
    "\"buffers\":[{\"byteLength\":40,\"uri\":\"data:application/octet-stream;base64,"
    "AAAAAAAAAAAAAAAAAACAPwAAAAAAAAAAAAAAAAAAgD8AAAAAAAAAAA==\"}]";

/* R391-A: accessor byteOffset of 2 is not a multiple of the 4-byte component
 * size. The span still fits the view, so pre-fix this passed cgltf_validate and
 * the POSITION loop then did a misaligned f32 load (UBSan: "load of misaligned
 * address ... requires 4 byte alignment"). */
TEST(gltf_rejects_misaligned_accessor_offset)
{
    char json[1024];
    snprintf(json, sizeof(json),
             "{\"asset\":{\"version\":\"2.0\"},\"scene\":0,"
             "\"scenes\":[{\"nodes\":[0]}],\"nodes\":[{\"mesh\":0}],"
             "\"meshes\":[{\"primitives\":[{\"attributes\":{\"POSITION\":0}}]}],"
             "\"accessors\":[{\"bufferView\":0,\"byteOffset\":2,\"componentType\":5126,"
             "\"count\":3,\"type\":\"VEC3\"}],"
             "\"bufferViews\":[{\"buffer\":0,\"byteOffset\":0,\"byteLength\":40}],"
             "%s}", BUF40);
    ASSERT_TRUE(write_text(TMP_GLTF, json));

    AssetCtx ctx;
    asset_ctx_init(&ctx, NULL);
    ctx.vfs = NULL;
    Scene scene;
    memset(&scene, 0, sizeof(scene));

    ASSERT_TRUE(!asset_load_gltf(&ctx, TMP_GLTF, &scene));
    remove(TMP_GLTF);
}

/* R391-A: the misalignment can equally come from the bufferView, so the check
 * has to look at the sum rather than the accessor's own offset. */
TEST(gltf_rejects_misaligned_buffer_view_offset)
{
    char json[1024];
    snprintf(json, sizeof(json),
             "{\"asset\":{\"version\":\"2.0\"},\"scene\":0,"
             "\"scenes\":[{\"nodes\":[0]}],\"nodes\":[{\"mesh\":0}],"
             "\"meshes\":[{\"primitives\":[{\"attributes\":{\"POSITION\":0}}]}],"
             "\"accessors\":[{\"bufferView\":0,\"componentType\":5126,"
             "\"count\":3,\"type\":\"VEC3\"}],"
             "\"bufferViews\":[{\"buffer\":0,\"byteOffset\":2,\"byteLength\":38}],"
             "%s}", BUF40);
    ASSERT_TRUE(write_text(TMP_GLTF, json));

    AssetCtx ctx;
    asset_ctx_init(&ctx, NULL);
    ctx.vfs = NULL;
    Scene scene;
    memset(&scene, 0, sizeof(scene));

    ASSERT_TRUE(!asset_load_gltf(&ctx, TMP_GLTF, &scene));
    remove(TMP_GLTF);
}

/* R391-A: an index accessor's misalignment is read by cgltf_calc_index_bound
 * inside cgltf_validate, which is why the alignment check has to run first.
 * Pre-fix this was a misaligned unsigned short load reached from validate. */
TEST(gltf_rejects_misaligned_index_accessor)
{
    char json[1024];
    snprintf(json, sizeof(json),
             "{\"asset\":{\"version\":\"2.0\"},\"scene\":0,"
             "\"scenes\":[{\"nodes\":[0]}],\"nodes\":[{\"mesh\":0}],"
             "\"meshes\":[{\"primitives\":[{\"attributes\":{\"POSITION\":0},"
             "\"indices\":1}]}],"
             "\"accessors\":[{\"bufferView\":0,\"componentType\":5126,"
             "\"count\":3,\"type\":\"VEC3\"},"
             "{\"bufferView\":1,\"byteOffset\":1,\"componentType\":5123,"
             "\"count\":3,\"type\":\"SCALAR\"}],"
             "\"bufferViews\":[{\"buffer\":0,\"byteOffset\":0,\"byteLength\":36},"
             "{\"buffer\":0,\"byteOffset\":0,\"byteLength\":40}],"
             "%s}", BUF40);
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

/* R415: node with a skin and JOINTS_0 but NO WEIGHTS_0, followed by a plain
 * mesh. The old counting pass classified the first primitive as skinned
 * (total_skinned=1, total_meshes=1) while the fill pass took the Mesh branch
 * for it (jnt && wgt required) — the second mesh then wrote meshes[1] past a
 * 1-element allocation (heap overflow). Post-fix both primitives classify as
 * plain meshes and mesh_count fits the allocation exactly. */
TEST(gltf_skinned_node_without_weights_no_overflow)
{
    char b64[113];
    memset(b64, 'A', 112); /* 84 zero bytes -> 112 base64 chars, no padding */
    b64[112] = '\0';
    char json[2048];
    snprintf(json, sizeof(json),
             "{\"asset\":{\"version\":\"2.0\"},\"scene\":0,"
             "\"scenes\":[{\"nodes\":[0,1]}],"
             "\"nodes\":[{\"mesh\":0,\"skin\":0},{\"mesh\":1},{}],"
             "\"skins\":[{\"joints\":[2]}],"
             "\"meshes\":[{\"primitives\":[{\"attributes\":{\"POSITION\":0,\"JOINTS_0\":1}}]},"
             "{\"primitives\":[{\"attributes\":{\"POSITION\":2}}]}],"
             "\"accessors\":["
             "{\"bufferView\":0,\"componentType\":5126,\"count\":3,\"type\":\"VEC3\"},"
             "{\"bufferView\":1,\"componentType\":5121,\"count\":3,\"type\":\"VEC4\"},"
             "{\"bufferView\":2,\"componentType\":5126,\"count\":3,\"type\":\"VEC3\"}],"
             "\"bufferViews\":["
             "{\"buffer\":0,\"byteOffset\":0,\"byteLength\":36},"
             "{\"buffer\":0,\"byteOffset\":36,\"byteLength\":12},"
             "{\"buffer\":0,\"byteOffset\":48,\"byteLength\":36}],"
             "\"buffers\":[{\"byteLength\":84,\"uri\":\"data:application/octet-stream;base64,%s\"}]}",
             b64);
    ASSERT_TRUE(write_text(TMP_GLTF, json));

    AssetCtx ctx;
    asset_ctx_init(&ctx, NULL);
    ctx.vfs = NULL;
    Scene scene;
    memset(&scene, 0, sizeof(scene));

    ASSERT_TRUE(asset_load_gltf(&ctx, TMP_GLTF, &scene));
    ASSERT_EQ(scene.mesh_count, 2u);
    ASSERT_EQ(scene.skinned_mesh_count, 0u);

    asset_scene_free(&ctx, &scene);
    remove(TMP_GLTF);
}

/* R415: cgltf_validate does not check accessor component_type, so a MAT4
 * inverse-bind accessor declared as UNSIGNED_BYTE passed validation and was
 * then memcpy'd as 16 f32 per joint — a 4x over-read of the real bytes.
 * Post-fix the loader converts non-float data through cgltf instead. */
TEST(gltf_non_float_inverse_bind_converted)
{
    char b64[25];
    memset(b64, 'A', 24); /* 18 zero bytes -> 24 base64 chars, no padding */
    b64[24] = '\0';
    char json[1024];
    snprintf(json, sizeof(json),
             "{\"asset\":{\"version\":\"2.0\"},\"scene\":0,"
             "\"scenes\":[{\"nodes\":[0]}],\"nodes\":[{}],"
             "\"skins\":[{\"joints\":[0],\"inverseBindMatrices\":0}],"
             "\"accessors\":[{\"bufferView\":0,\"componentType\":5121,"
             "\"count\":1,\"type\":\"MAT4\"}],"
             "\"bufferViews\":[{\"buffer\":0,\"byteOffset\":0,\"byteLength\":16}],"
             "\"buffers\":[{\"byteLength\":18,\"uri\":\"data:application/octet-stream;base64,%s\"}]}",
             b64);
    ASSERT_TRUE(write_text(TMP_GLTF, json));

    AssetCtx ctx;
    asset_ctx_init(&ctx, NULL);
    ctx.vfs = NULL;
    Scene scene;
    memset(&scene, 0, sizeof(scene));

    ASSERT_TRUE(asset_load_gltf(&ctx, TMP_GLTF, &scene));
    ASSERT_EQ(scene.joint_count, 1u);

    asset_scene_free(&ctx, &scene);
    remove(TMP_GLTF);
}

/* R415: same class of bug in the vertex path — POSITION declared as
 * UNSIGNED_BYTE was memcpy'd as 12 bytes/vertex out of a 3-byte/vertex span.
 * Post-fix it is converted through cgltf_accessor_read_float. */
TEST(gltf_non_float_position_converted)
{
    char b64[17];
    memset(b64, 'A', 16); /* 12 zero bytes -> 16 base64 chars, no padding */
    b64[16] = '\0';
    char json[1024];
    snprintf(json, sizeof(json),
             "{\"asset\":{\"version\":\"2.0\"},\"scene\":0,"
             "\"scenes\":[{\"nodes\":[0]}],\"nodes\":[{\"mesh\":0}],"
             "\"meshes\":[{\"primitives\":[{\"attributes\":{\"POSITION\":0}}]}],"
             "\"accessors\":[{\"bufferView\":0,\"componentType\":5121,"
             "\"count\":3,\"type\":\"VEC3\"}],"
             "\"bufferViews\":[{\"buffer\":0,\"byteOffset\":0,\"byteLength\":9}],"
             "\"buffers\":[{\"byteLength\":12,\"uri\":\"data:application/octet-stream;base64,%s\"}]}",
             b64);
    ASSERT_TRUE(write_text(TMP_GLTF, json));

    AssetCtx ctx;
    asset_ctx_init(&ctx, NULL);
    ctx.vfs = NULL;
    Scene scene;
    memset(&scene, 0, sizeof(scene));

    ASSERT_TRUE(asset_load_gltf(&ctx, TMP_GLTF, &scene));
    ASSERT_EQ(scene.mesh_count, 1u);
    ASSERT_EQ(scene.meshes[0].vertex_count, 3u);

    asset_scene_free(&ctx, &scene);
    remove(TMP_GLTF);
}

/* R415: external buffer URIs went to cgltf_load_buffers unchecked (the R353
 * gltf_uri_safe guard only covered image URIs). A "../" escape must be
 * rejected before any file outside the asset directory is read. */
TEST(gltf_rejects_traversal_buffer_uri)
{
    char json[1024];
    snprintf(json, sizeof(json),
             "{\"asset\":{\"version\":\"2.0\"},\"scene\":0,"
             "\"scenes\":[{\"nodes\":[0]}],\"nodes\":[{\"mesh\":0}],"
             "\"meshes\":[{\"primitives\":[{\"attributes\":{\"POSITION\":0}}]}],"
             "\"accessors\":[{\"bufferView\":0,\"componentType\":5126,"
             "\"count\":3,\"type\":\"VEC3\"}],"
             "\"bufferViews\":[{\"buffer\":0,\"byteOffset\":0,\"byteLength\":36}],"
             "\"buffers\":[{\"byteLength\":36,\"uri\":\"../r415_evil.bin\"}]}");
    ASSERT_TRUE(write_text(TMP_GLTF, json));

    AssetCtx ctx;
    asset_ctx_init(&ctx, NULL);
    ctx.vfs = NULL;
    Scene scene;
    memset(&scene, 0, sizeof(scene));

    ASSERT_TRUE(!asset_load_gltf(&ctx, TMP_GLTF, &scene));
    remove(TMP_GLTF);
}

/* R422: cgltf percent-decodes a buffer uri AFTER combining it with the gltf
 * directory (cgltf_decode_uri in cgltf_load_buffer_file), so a uri with no
 * literal ".." can still traverse: "%2e%2e/" decodes to "../" once the raw-text
 * check has already passed. Percent-encoding is now rejected outright. */
TEST(gltf_rejects_percent_encoded_buffer_uri)
{
    char json[1024];
    snprintf(json, sizeof(json),
             "{\"asset\":{\"version\":\"2.0\"},\"scene\":0,"
             "\"scenes\":[{\"nodes\":[0]}],\"nodes\":[{\"mesh\":0}],"
             "\"meshes\":[{\"primitives\":[{\"attributes\":{\"POSITION\":0}}]}],"
             "\"accessors\":[{\"bufferView\":0,\"componentType\":5126,"
             "\"count\":3,\"type\":\"VEC3\"}],"
             "\"bufferViews\":[{\"buffer\":0,\"byteOffset\":0,\"byteLength\":36}],"
             "\"buffers\":[{\"byteLength\":36,\"uri\":\"%%2e%%2e/%%2e%%2e/etc/passwd\"}]}");
    ASSERT_TRUE(write_text(TMP_GLTF, json));

    AssetCtx ctx;
    asset_ctx_init(&ctx, NULL);
    ctx.vfs = NULL;
    Scene scene;
    memset(&scene, 0, sizeof(scene));

    ASSERT_TRUE(!asset_load_gltf(&ctx, TMP_GLTF, &scene));
    remove(TMP_GLTF);
}

static bool write_bin(const char *path, const void *data, usize n) {
    FILE *f = fopen(path, "wb");
    if (!f) return false;
    bool ok = fwrite(data, 1, n, f) == n;
    fclose(f);
    return ok;
}

static void put_f32(u8 *dst, f32 v) { memcpy(dst, &v, sizeof(v)); }
static void put_u16(u8 *dst, u16 v) { memcpy(dst, &v, sizeof(v)); }
static void put_u8v(u8 *dst, u8 a, u8 b, u8 c, u8 d) {
    dst[0] = a; dst[1] = b; dst[2] = c; dst[3] = d;
}

/* R422: the memcpy fast path in gltf_read_vec3_attr ignored acc->is_sparse —
 * a sparse float VEC3 POSITION read the base data only, silently dropping the
 * sparse overrides. Sparse accessors now take cgltf's conversion path (which
 * applies them), so the mesh AABB must reflect the override, not the base. */
TEST(gltf_sparse_position_applies_overrides)
{
    const char *bin_path = "/tmp/test_r422_sparse.bin";
    /* [0..36)  base POSITION: (1,0,0),(0,1,0),(0,0,1)
     * [36..38) sparse index u16: 0        [38..40) pad
     * [40..52) sparse value VEC3 f32: (9,9,9) */
    u8 buf[52];
    memset(buf, 0, sizeof(buf));
    put_f32(buf + 0, 1.0f);
    put_f32(buf + 16, 1.0f);
    put_f32(buf + 32, 1.0f);
    put_u16(buf + 36, 0u);
    put_f32(buf + 40, 9.0f);
    put_f32(buf + 44, 9.0f);
    put_f32(buf + 48, 9.0f);
    ASSERT_TRUE(write_bin(bin_path, buf, sizeof(buf)));

    char json[1280];
    snprintf(json, sizeof(json),
             "{\"asset\":{\"version\":\"2.0\"},\"scene\":0,"
             "\"scenes\":[{\"nodes\":[0]}],\"nodes\":[{\"mesh\":0}],"
             "\"meshes\":[{\"primitives\":[{\"attributes\":{\"POSITION\":0}}]}],"
             "\"accessors\":[{\"bufferView\":0,\"componentType\":5126,"
             "\"count\":3,\"type\":\"VEC3\",\"sparse\":{\"count\":1,"
             "\"indices\":{\"bufferView\":1,\"componentType\":5123},"
             "\"values\":{\"bufferView\":2}}}],"
             "\"bufferViews\":[{\"buffer\":0,\"byteOffset\":0,\"byteLength\":36},"
             "{\"buffer\":0,\"byteOffset\":36,\"byteLength\":4},"
             "{\"buffer\":0,\"byteOffset\":40,\"byteLength\":12}],"
             "\"buffers\":[{\"byteLength\":52,\"uri\":\"test_r422_sparse.bin\"}]}");
    ASSERT_TRUE(write_text(TMP_GLTF, json));

    AssetCtx ctx;
    asset_ctx_init(&ctx, NULL);
    ctx.vfs = NULL;
    Scene scene;
    memset(&scene, 0, sizeof(scene));

    ASSERT_TRUE(asset_load_gltf(&ctx, TMP_GLTF, &scene));
    ASSERT_EQ(scene.mesh_count, 1u);
    /* Vertex 0 must be the sparse override (9,9,9), not the base (1,0,0). */
    ASSERT_FLOAT_EQ(scene.meshes[0].aabb_max.e[0], 9.0f, 1e-6f);
    ASSERT_FLOAT_EQ(scene.meshes[0].aabb_max.e[1], 9.0f, 1e-6f);
    ASSERT_FLOAT_EQ(scene.meshes[0].aabb_max.e[2], 9.0f, 1e-6f);
    ASSERT_FLOAT_EQ(scene.meshes[0].aabb_min.e[0], 0.0f, 1e-6f);

    asset_scene_free(&ctx, &scene);
    remove(TMP_GLTF);
    remove(bin_path);
}

/* R422: WEIGHTS_0 is legally normalized UNSIGNED_BYTE (glTF skinning). The
 * read must go through cgltf (which honours normalized) and the raw-memcpy
 * fallback must stay guarded to float data — this skinned mesh must load with
 * exactly one skinned mesh and no reinterpretation of the weight bytes. */
TEST(gltf_normalized_u8_weights_load_safely)
{
    const char *bin_path = "/tmp/test_r422_weights.bin";
    /* [0..36)  POSITION 3xVEC3 f32: (1,0,0),(0,1,0),(0,0,1)
     * [36..48) JOINTS_0 3xVEC4 u8: {0,0,0,0} each
     * [48..60) WEIGHTS_0 3xVEC4 u8 normalized: {255,0,0,0} each */
    u8 buf[60];
    memset(buf, 0, sizeof(buf));
    put_f32(buf + 0, 1.0f);
    put_f32(buf + 16, 1.0f);
    put_f32(buf + 32, 1.0f);
    for (u32 v = 0; v < 3; v++) {
        put_u8v(buf + 36 + v * 4, 0u, 0u, 0u, 0u);
        put_u8v(buf + 48 + v * 4, 255u, 0u, 0u, 0u);
    }
    ASSERT_TRUE(write_bin(bin_path, buf, sizeof(buf)));

    char json[1280];
    snprintf(json, sizeof(json),
             "{\"asset\":{\"version\":\"2.0\"},\"scene\":0,"
             "\"scenes\":[{\"nodes\":[0]}],"
             "\"nodes\":[{\"mesh\":0,\"skin\":0},{}],"
             "\"skins\":[{\"joints\":[1]}],"
             "\"meshes\":[{\"primitives\":[{\"attributes\":{"
             "\"POSITION\":0,\"JOINTS_0\":1,\"WEIGHTS_0\":2}}]}],"
             "\"accessors\":["
             "{\"bufferView\":0,\"componentType\":5126,\"count\":3,\"type\":\"VEC3\"},"
             "{\"bufferView\":1,\"componentType\":5121,\"count\":3,\"type\":\"VEC4\"},"
             "{\"bufferView\":2,\"componentType\":5121,\"normalized\":true,"
             "\"count\":3,\"type\":\"VEC4\"}],"
             "\"bufferViews\":[{\"buffer\":0,\"byteOffset\":0,\"byteLength\":36},"
             "{\"buffer\":0,\"byteOffset\":36,\"byteLength\":12},"
             "{\"buffer\":0,\"byteOffset\":48,\"byteLength\":12}],"
             "\"buffers\":[{\"byteLength\":60,\"uri\":\"test_r422_weights.bin\"}]}");
    ASSERT_TRUE(write_text(TMP_GLTF, json));

    AssetCtx ctx;
    asset_ctx_init(&ctx, NULL);
    ctx.vfs = NULL;
    Scene scene;
    memset(&scene, 0, sizeof(scene));

    ASSERT_TRUE(asset_load_gltf(&ctx, TMP_GLTF, &scene));
    ASSERT_EQ(scene.skinned_mesh_count, 1u);
    ASSERT_EQ(scene.mesh_count, 0u);

    asset_scene_free(&ctx, &scene);
    remove(TMP_GLTF);
    remove(bin_path);
}

/* R415: the memoized-DFS rewrite of scene_compute_world_transforms must give
 * the same results as the old iterate-until-stable loop when children precede
 * their parents in nodes[] (glTF does not guarantee parent-first order). */
TEST(scene_world_transforms_child_before_parent)
{
    Scene scene;
    memset(&scene, 0, sizeof(scene));
    SceneNode nodes[3];
    memset(nodes, 0, sizeof(nodes));
    scene.nodes = nodes;
    scene.node_count = 3;
    nodes[0].parent_index = 1; /* grandchild sits at the lowest index */
    nodes[0].local_transform = mat4_translation(1.0f, 0.0f, 0.0f);
    nodes[1].parent_index = 2;
    nodes[1].local_transform = mat4_translation(0.0f, 2.0f, 0.0f);
    nodes[2].parent_index = UINT32_MAX;
    nodes[2].local_transform = mat4_translation(0.0f, 0.0f, 3.0f);

    scene_compute_world_transforms(&scene);

    /* Translations compose additively; translation lives in e[3][0..2]. */
    ASSERT_FLOAT_EQ(nodes[2].world_transform.e[3][0], 0.0f, 1e-6f);
    ASSERT_FLOAT_EQ(nodes[2].world_transform.e[3][1], 0.0f, 1e-6f);
    ASSERT_FLOAT_EQ(nodes[2].world_transform.e[3][2], 3.0f, 1e-6f);
    ASSERT_FLOAT_EQ(nodes[1].world_transform.e[3][0], 0.0f, 1e-6f);
    ASSERT_FLOAT_EQ(nodes[1].world_transform.e[3][1], 2.0f, 1e-6f);
    ASSERT_FLOAT_EQ(nodes[1].world_transform.e[3][2], 3.0f, 1e-6f);
    ASSERT_FLOAT_EQ(nodes[0].world_transform.e[3][0], 1.0f, 1e-6f);
    ASSERT_FLOAT_EQ(nodes[0].world_transform.e[3][1], 2.0f, 1e-6f);
    ASSERT_FLOAT_EQ(nodes[0].world_transform.e[3][2], 3.0f, 1e-6f);
}

/* R415: a parent cycle (malformed scene) must terminate deterministically —
 * the visited-state DFS breaks the cycle by treating the re-entered node as
 * its own root. */
TEST(scene_world_transforms_parent_cycle_terminates)
{
    Scene scene;
    memset(&scene, 0, sizeof(scene));
    SceneNode nodes[2];
    memset(nodes, 0, sizeof(nodes));
    scene.nodes = nodes;
    scene.node_count = 2;
    nodes[0].parent_index = 1;
    nodes[0].local_transform = mat4_translation(1.0f, 0.0f, 0.0f);
    nodes[1].parent_index = 0;
    nodes[1].local_transform = mat4_translation(0.0f, 1.0f, 0.0f);

    scene_compute_world_transforms(&scene); /* must not hang */

    ASSERT_FLOAT_EQ(nodes[0].world_transform.e[3][0], 1.0f, 1e-6f);
    ASSERT_FLOAT_EQ(nodes[0].world_transform.e[3][1], 0.0f, 1e-6f);
    ASSERT_FLOAT_EQ(nodes[1].world_transform.e[3][0], 1.0f, 1e-6f);
    ASSERT_FLOAT_EQ(nodes[1].world_transform.e[3][1], 1.0f, 1e-6f);
}

TEST_MAIN_BEGIN()
    RUN_TEST(gltf_rejects_accessor_count_past_buffer_view);
    RUN_TEST(gltf_rejects_accessor_offset_past_buffer_view);
    RUN_TEST(gltf_rejects_buffer_view_past_buffer);
    RUN_TEST(gltf_rejects_index_count_past_buffer_view);
    RUN_TEST(gltf_rejects_extreme_accessor_count_before_alloc);
    RUN_TEST(gltf_rejects_misaligned_accessor_offset);
    RUN_TEST(gltf_rejects_misaligned_buffer_view_offset);
    RUN_TEST(gltf_rejects_misaligned_index_accessor);
    RUN_TEST(gltf_accepts_well_formed_model);
    RUN_TEST(gltf_skinned_node_without_weights_no_overflow);
    RUN_TEST(gltf_non_float_inverse_bind_converted);
    RUN_TEST(gltf_non_float_position_converted);
    RUN_TEST(gltf_rejects_traversal_buffer_uri);
    RUN_TEST(gltf_rejects_percent_encoded_buffer_uri);
    RUN_TEST(gltf_sparse_position_applies_overrides);
    RUN_TEST(gltf_normalized_u8_weights_load_safely);
    RUN_TEST(scene_world_transforms_child_before_parent);
    RUN_TEST(scene_world_transforms_parent_cycle_terminates);
TEST_MAIN_END()
