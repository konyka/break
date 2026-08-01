#include <asset/asset.h>
#include <asset/async_loader.h>
#include <asset/vfs.h>
#include <core/log.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define STB_IMAGE_IMPLEMENTATION
#define STBI_NO_FAILURE_STRINGS
#include <stb_image.h>

#define CGLTF_IMPLEMENTATION
#define CGLTF_NO_STRTOD
#include <cgltf.h>

void asset_ctx_init(AssetCtx *ctx, RHIDevice *dev) {
    ctx->device = dev;
}

RHITexture asset_load_texture(AssetCtx *ctx, const char *path) {
    int w, h, channels;
    u8 *data;

    if (ctx->vfs) {
        usize sz = 0;
        u8 *raw = vfs_read_all(ctx->vfs, path, &sz);
        if (!raw) {
            LOG_ERROR("VFS: texture not found: %s", path);
            return RHI_HANDLE_NULL;
        }
        if (sz > (usize)INT32_MAX) {
            /* R144: stbi_load_from_memory takes int len — reject >2GB to prevent truncation */
            LOG_ERROR("Texture too large (>%d bytes): %s", INT32_MAX, path);
            free(raw);
            return RHI_HANDLE_NULL;
        }
        data = stbi_load_from_memory(raw, (int)sz, &w, &h, &channels, 4);
        free(raw);
    } else {
        data = stbi_load(path, &w, &h, &channels, 4);
    }

    if (!data) {
        LOG_ERROR("Failed to load texture: %s", path);
        return RHI_HANDLE_NULL;
    }

    RHITextureDesc desc = {
        .width      = (u32)w,
        .height     = (u32)h,
        .format     = RHI_FORMAT_R8G8B8A8_UNORM,
        .mip_levels = 1,
        .data       = data,
    };
    RHITexture tex = rhi_texture_create(ctx->device, &desc);
    stbi_image_free(data);

    if (!rhi_handle_valid(tex)) {
        LOG_ERROR("Failed to create GPU texture: %s", path);
    }
    return tex;
}

void asset_texture_free(AssetCtx *ctx, RHITexture tex) {
    if (rhi_handle_valid(tex)) rhi_texture_destroy(ctx->device, tex);
}

typedef struct {
    f32 pos[3];
    f32 normal[3];
    f32 uv[2];
} Vertex;

typedef struct {
    f32 pos[3];
    f32 normal[3];
    f32 uv[2];
    u32 joints[4];
    f32 weights[4];
} SkinnedVertex;

#define GLTF_MAX_SCENE_ITEMS     100000u
#define GLTF_MAX_VERTEX_COUNT    10000000u
#define GLTF_MAX_INDEX_COUNT     30000000u
#define GLTF_MAX_KEYFRAME_COUNT  1000000u

static bool gltf_count_fits_u32(cgltf_size count) {
    return count <= (cgltf_size)UINT32_MAX;
}

static bool gltf_count_fits_size(cgltf_size count, usize elem_size) {
    if (elem_size == 0) return false;
    return (usize)count <= SIZE_MAX / elem_size;
}

static bool gltf_count_bounded(cgltf_size count, u32 max_count, usize elem_size) {
    return gltf_count_fits_u32(count) &&
           count <= (cgltf_size)max_count &&
           gltf_count_fits_size(count, elem_size);
}

static bool cgltf_accessor_is_type(cgltf_accessor *acc, cgltf_type type) {
    return acc && acc->type == type;
}

static bool gltf_uri_safe(const char *uri) {
    if (!uri || !*uri) return false;
    if (uri[0] == '/' || uri[0] == '\\') return false;
    const char *p = uri;
    for (;;) {
        if (p[0] == '.' && p[1] == '.' &&
            (p[2] == '/' || p[2] == '\\' || p[2] == '\0'))
            return false;
        const char *slash = strpbrk(p, "/\\");
        if (!slash) break;
        p = slash + 1;
    }
    return true;
}

/* R415: external buffer URIs went straight to cgltf_load_buffers with no path
 * check — the R353 gltf_uri_safe guard only covered image URIs, so a file
 * could point a buffer at "../../etc/..." and have cgltf read it. NULL (GLB
 * binary chunk) and data: URIs are loaded inline and need no check. */
static bool gltf_buffer_uris_safe(const cgltf_data *data, const char *path) {
    for (cgltf_size bi = 0; bi < data->buffers_count; bi++) {
        const char *uri = data->buffers[bi].uri;
        if (!uri || strncmp(uri, "data:", 5) == 0) continue;
        if (!gltf_uri_safe(uri)) {
            LOG_ERROR("glTF: rejecting unsafe buffer uri '%s': %s", uri, path);
            return false;
        }
    }
    return true;
}

static RHITexture load_gltf_texture(AssetCtx *ctx, const char *gltf_path, cgltf_texture *tex) {
    if (!tex || !tex->image || !tex->image->uri) return RHI_HANDLE_NULL;
    /* R353: reject path escape in image.uri (pairs with vfs_rel_path_safe). */
    if (!gltf_uri_safe(tex->image->uri)) {
        LOG_WARN("glTF: rejecting unsafe texture uri '%s'", tex->image->uri);
        return RHI_HANDLE_NULL;
    }
    char tex_path[512];
    const char *last_slash = strrchr(gltf_path, '/');
    if (last_slash) {
        usize dir_len = (usize)(last_slash - gltf_path + 1);
        /* R109-3: Clamp dir_len to prevent stack buffer overflow when
         * gltf_path exceeds tex_path capacity. */
        if (dir_len >= sizeof(tex_path)) dir_len = sizeof(tex_path) - 1;
        memcpy(tex_path, gltf_path, dir_len);
        strncpy(tex_path + dir_len, tex->image->uri, sizeof(tex_path) - dir_len - 1);
        tex_path[sizeof(tex_path) - 1] = '\0';
    } else {
        strncpy(tex_path, tex->image->uri, sizeof(tex_path) - 1);
        tex_path[sizeof(tex_path) - 1] = '\0';
    }
    return asset_load_texture(ctx, tex_path);
}

static const u8 *cgltf_buffer_data(cgltf_accessor *acc) {
    if (!acc || !acc->buffer_view) return NULL;
    cgltf_buffer_view *bv = acc->buffer_view;
    /* R109-2: Validate buffer and buffer->data to prevent NULL + offset
     * from producing a non-NULL dangling pointer that callers won't detect. */
    if (!bv->buffer || !bv->buffer->data) return NULL;
    return (const u8 *)bv->buffer->data + bv->offset + acc->offset;
}

static usize cgltf_accessor_stride(cgltf_accessor *acc) {
    /* R249: honor the accessor byte stride. cgltf's fixup sets acc->stride to the
     * bufferView's byteStride, or the compact element size when byteStride==0
     * (see cgltf_fixup_pointers). The previous compact-only computation ignored
     * interleaved buffers (byteStride > element size), so pos/normal/uv/joints/
     * weights were read from wrong offsets and meshes came out mangled. For
     * compact (non-interleaved) accessors acc->stride already equals the element
     * size, so this is byte-identical there. */
    if (acc->stride) return (usize)acc->stride;
    cgltf_size component_size = cgltf_component_size(acc->component_type);
    return component_size * cgltf_num_components(acc->type);
}

/* R391: glTF 2.0 §3.6.2.4 requires an accessor's offset into its buffer
 * (bufferView.byteOffset + accessor.byteOffset) and its byteStride to both be
 * multiples of the component size. cgltf_validate checks sizes, not alignment.
 *
 * Nothing enforced it, and every reader dereferences a typed pointer built from
 * those file-controlled offsets — ours in the attribute and animation loops, and
 * cgltf's own cgltf_component_read_float (*(const float *)in) and
 * cgltf_calc_index_bound (((unsigned short *)data)[i]). A non-conforming file
 * therefore produces misaligned loads (UBSan: "load of misaligned address ...
 * which requires 4 byte alignment", found by fuzz_asset_gltf). That is UB in C
 * and a SIGBUS on strict-alignment targets such as ARM.
 *
 * Checked against the resolved pointer rather than the offset sum alone, because
 * buffer->data for a GLB points into the binary chunk: a file whose JSON chunk
 * length is not the spec-mandated multiple of 4 lands the chunk itself at an odd
 * address, and then a perfectly conforming offset is still misaligned.
 *
 * Runs before cgltf_validate, not after: validate calls cgltf_calc_index_bound,
 * so by the time it returns the misaligned read has already happened. Only
 * integer arithmetic on uintptr_t is used, never a computed pointer, since an
 * out-of-range offset would make forming one UB in its own right. */
static bool gltf_span_aligned(const cgltf_buffer_view *view, cgltf_size offset,
                              cgltf_size stride, cgltf_size cs) {
    if (!view || !view->buffer || cs == 0) return true;
    uintptr_t base = (uintptr_t)view->buffer->data + (uintptr_t)view->offset + (uintptr_t)offset;
    return (base % (uintptr_t)cs) == 0 && (stride % cs) == 0;
}

static bool gltf_accessors_aligned(const cgltf_data *data, const char *path) {
    for (cgltf_size i = 0; i < data->accessors_count; i++) {
        const cgltf_accessor *acc = &data->accessors[i];
        cgltf_size cs = cgltf_component_size(acc->component_type);

        if (!gltf_span_aligned(acc->buffer_view, acc->offset, acc->stride, cs)) {
            LOG_ERROR("glTF accessor %u misaligned (component size %u): %s",
                      (u32)i, (u32)cs, path);
            return false;
        }
        /* Sparse indices and values carry their own views, offsets and component
         * type, and are read by the same unaligned-unsafe helpers. */
        if (acc->is_sparse) {
            cgltf_size ics = cgltf_component_size(acc->sparse.indices_component_type);
            if (!gltf_span_aligned(acc->sparse.indices_buffer_view,
                                   acc->sparse.indices_byte_offset, ics, ics) ||
                !gltf_span_aligned(acc->sparse.values_buffer_view,
                                   acc->sparse.values_byte_offset, cs, cs)) {
                LOG_ERROR("glTF accessor %u sparse data misaligned: %s", (u32)i, path);
                return false;
            }
        }
    }
    return true;
}

static bool gltf_counts_bounded(const cgltf_data *data, const char *path) {
    if (!gltf_count_bounded(data->nodes_count, GLTF_MAX_SCENE_ITEMS, sizeof(SceneNode)) ||
        !gltf_count_bounded(data->meshes_count, GLTF_MAX_SCENE_ITEMS, sizeof(Mesh)) ||
        !gltf_count_bounded(data->materials_count, GLTF_MAX_SCENE_ITEMS, sizeof(Material))) {
        LOG_ERROR("glTF scene count exceeds loader limits: %s", path);
        return false;
    }

    for (cgltf_size i = 0; i < data->accessors_count; i++) {
        const cgltf_accessor *acc = &data->accessors[i];
        usize elem_size = cgltf_component_size(acc->component_type) * cgltf_num_components(acc->type);
        u32 max_count = acc->type == cgltf_type_scalar ? GLTF_MAX_INDEX_COUNT : GLTF_MAX_VERTEX_COUNT;
        if (!gltf_count_bounded(acc->count, max_count, elem_size ? elem_size : 1u)) {
            LOG_ERROR("glTF accessor %u count exceeds loader limits: %s", (u32)i, path);
            return false;
        }
    }

    for (cgltf_size i = 0; i < data->skins_count; i++) {
        if (!gltf_count_bounded(data->skins[i].joints_count, GLTF_MAX_SCENE_ITEMS, sizeof(Mat4))) {
            LOG_ERROR("glTF skin %u joint count exceeds loader limits: %s", (u32)i, path);
            return false;
        }
    }

    for (cgltf_size ai = 0; ai < data->animations_count; ai++) {
        const cgltf_animation *anim = &data->animations[ai];
        if (!gltf_count_bounded(anim->channels_count, GLTF_MAX_SCENE_ITEMS, sizeof(cgltf_animation_channel)) ||
            !gltf_count_bounded(anim->samplers_count, GLTF_MAX_SCENE_ITEMS, sizeof(cgltf_animation_sampler))) {
            LOG_ERROR("glTF animation %u count exceeds loader limits: %s", (u32)ai, path);
            return false;
        }
        for (cgltf_size si = 0; si < anim->samplers_count; si++) {
            const cgltf_animation_sampler *samp = &anim->samplers[si];
            if (samp->input && !gltf_count_bounded(samp->input->count, GLTF_MAX_KEYFRAME_COUNT, sizeof(f32))) {
                LOG_ERROR("glTF animation %u sampler %u has too many keyframes: %s", (u32)ai, (u32)si, path);
                return false;
            }
        }
    }

    return true;
}

/* R415: read a VEC3 float attribute (POSITION/NORMAL) into a strided
 * destination. The raw memcpy fast path is only valid when the accessor is
 * actually float VEC3 — cgltf_validate does not check component types, so a
 * file declaring e.g. POSITION as UNSIGNED_BYTE was reinterpreted as f32 and
 * over-read (12 bytes/vertex out of a 3-byte/vertex span). Convert through
 * cgltf in that case, mirroring the R278/R279 weights/UV handling. */
static void gltf_read_vec3_attr(cgltf_accessor *acc, u32 count, u8 *dst, usize dst_stride) {
    if (acc->component_type == cgltf_component_type_r_32f &&
        cgltf_accessor_is_type(acc, cgltf_type_vec3)) {
        const u8 *d = cgltf_buffer_data(acc);
        usize s = cgltf_accessor_stride(acc);
        for (u32 vi = 0; d && vi < count; vi++) {
            memcpy(dst + vi * dst_stride, d + vi * s, sizeof(f32) * 3);
        }
    } else {
        for (u32 vi = 0; vi < count; vi++) {
            cgltf_accessor_read_float(acc, vi, (f32 *)(dst + vi * dst_stride), 3);
        }
    }
}

bool asset_load_gltf(AssetCtx *ctx, const char *path, Scene *out_scene) {
    cgltf_options opts = {0};
    cgltf_data *data = NULL;
    cgltf_result result;

    if (ctx->vfs) {
        usize sz = 0;
        u8 *raw = vfs_read_all(ctx->vfs, path, &sz);
        if (!raw) {
            LOG_ERROR("VFS: glTF not found: %s", path);
            return false;
        }
        result = cgltf_parse(&opts, raw, sz, &data);
        free(raw);
        if (result != cgltf_result_success) {
            LOG_ERROR("cgltf parse failed (%d): %s", result, path);
            return false;
        }
        if (!gltf_buffer_uris_safe(data, path)) {
            cgltf_free(data);
            return false;
        }
        result = cgltf_load_buffers(&opts, data, path);
    } else {
        result = cgltf_parse_file(&opts, path, &data);
        if (result != cgltf_result_success) {
            LOG_ERROR("cgltf parse failed (%d): %s", result, path);
            return false;
        }
        if (!gltf_buffer_uris_safe(data, path)) {
            cgltf_free(data);
            return false;
        }
        result = cgltf_load_buffers(&opts, data, path);
    }

    if (result != cgltf_result_success) {
        LOG_ERROR("cgltf buffer load failed (%d): %s", result, path);
        cgltf_free(data);
        return false;
    }

    /* R390: neither cgltf_parse nor cgltf_load_buffers bounds check the data —
     * that is what cgltf_validate is for, and it was never called. The two
     * invariants it establishes are exactly the ones every read below assumes:
     * an accessor's span (offset + stride * (count - 1) + element_size) fits in
     * its bufferView, and a bufferView (offset + size) fits in its buffer.
     *
     * Without it, cgltf_buffer_data returns buffer->data + view->offset +
     * accessor->offset and the attribute loops walk accessor->count elements
     * from there, all four values straight from the file. A model declaring
     * count = 200000 against a 36-byte bufferView read 2.4 MB past a 36-byte
     * heap block (ASan: READ of size 12 after a 36-byte region) — a crash, or
     * adjacent heap contents copied into vertex buffers. */
    /* R391: must precede cgltf_validate — see gltf_accessors_aligned. */
    if (!gltf_accessors_aligned(data, path)) {
        cgltf_free(data);
        return false;
    }

    if (!gltf_counts_bounded(data, path)) {
        cgltf_free(data);
        return false;
    }

    result = cgltf_validate(data);
    if (result != cgltf_result_success) {
        LOG_ERROR("cgltf validation failed (%d): %s", result, path);
        cgltf_free(data);
        return false;
    }

    u32 total_meshes = 0;
    u32 total_skinned = 0;

    out_scene->nodes = calloc(data->nodes_count > 0 ? data->nodes_count : 1, sizeof(SceneNode));
    out_scene->node_count = 0;
    /* R384: the node loop below writes nodes[ni] unconditionally — mirror the
     * skin path (below) and bail on OOM instead of faulting. */
    if (!out_scene->nodes) {
        LOG_ERROR("glTF: node allocation failed");
        cgltf_free(data);
        asset_scene_free(ctx, out_scene);
        return false;
    }

    for (u32 ni = 0; ni < data->nodes_count; ni++) {
        cgltf_node *node = &data->nodes[ni];
        if (!node->mesh) continue;
        for (u32 pi = 0; pi < node->mesh->primitives_count; pi++) {
            cgltf_primitive *prim = &node->mesh->primitives[pi];
            /* R415: this predicate MUST be identical to the fill passes below
             * (node->skin && JOINTS_0 && WEIGHTS_0). The old version counted a
             * primitive as skinned when node->skin was set OR any JOINTS
             * attribute existed, while the fill pass only took the skinned
             * branch when both JOINTS_0 and WEIGHTS_0 were present — such a
             * primitive was counted as skinned but written into
             * meshes[mesh_count++] with no room allocated (heap overflow). */
            bool has_skin = false;
            if (node->skin) {
                bool has_joints = false, has_weights = false;
                for (u32 ai = 0; ai < prim->attributes_count; ai++) {
                    cgltf_attribute *attr = &prim->attributes[ai];
                    if (attr->type == cgltf_attribute_type_joints  && attr->index == 0) has_joints = true;
                    if (attr->type == cgltf_attribute_type_weights && attr->index == 0) has_weights = true;
                }
                has_skin = has_joints && has_weights;
            }
            if (has_skin) {
                if (total_skinned == GLTF_MAX_SCENE_ITEMS) {
                    LOG_ERROR("glTF: too many skinned mesh primitives: %s", path);
                    cgltf_free(data);
                    asset_scene_free(ctx, out_scene);
                    return false;
                }
                total_skinned++;
            } else {
                if (total_meshes == GLTF_MAX_SCENE_ITEMS) {
                    LOG_ERROR("glTF: too many mesh primitives: %s", path);
                    cgltf_free(data);
                    asset_scene_free(ctx, out_scene);
                    return false;
                }
                total_meshes++;
            }
        }
    }

    out_scene->meshes = calloc(total_meshes > 0 ? total_meshes : 1, sizeof(Mesh));
    out_scene->skinned_meshes = calloc(total_skinned > 0 ? total_skinned : 1, sizeof(SkinnedMesh));
    out_scene->mesh_count = 0;
    out_scene->skinned_mesh_count = 0;
    if (!out_scene->meshes || !out_scene->skinned_meshes) {
        LOG_ERROR("glTF: mesh allocation failed");
        cgltf_free(data);
        asset_scene_free(ctx, out_scene);
        return false;
    }

    /* Pre-build materials from cgltf data for O(1) lookup by pointer diff */
    if (data->materials_count > 0) {
        out_scene->materials = calloc(data->materials_count, sizeof(Material));
        if (!out_scene->materials) {
            LOG_ERROR("glTF: material allocation failed");
            cgltf_free(data);
            asset_scene_free(ctx, out_scene);
            return false;
        }
        out_scene->material_count = (u32)data->materials_count;
        for (u32 mi = 0; mi < data->materials_count; mi++) {
            cgltf_material *cm = &data->materials[mi];
            Material *mat = &out_scene->materials[mi];
            memset(mat, 0, sizeof(Material));
            mat->_material_ptr = (void *)cm;
            { static const f32 white4[4] = {1.0f, 1.0f, 1.0f, 1.0f};
              memcpy(mat->base_color, white4, sizeof(white4)); }
            mat->metallic_factor = cm->pbr_metallic_roughness.metallic_factor;
            mat->roughness_factor = cm->pbr_metallic_roughness.roughness_factor;
            mat->emissive_strength = cm->has_emissive_strength ?
                cm->emissive_strength.emissive_strength : 1.0f;
            if (cm->alpha_mode == cgltf_alpha_mode_opaque) mat->alpha_mode = ALPHA_OPAQUE;
            else if (cm->alpha_mode == cgltf_alpha_mode_mask) mat->alpha_mode = ALPHA_MASK;
            else mat->alpha_mode = ALPHA_BLEND;
            mat->alpha_cutoff = cm->alpha_cutoff;

            mat->albedo = load_gltf_texture(ctx, path,
                cm->pbr_metallic_roughness.base_color_texture.texture);
            mat->metallic_roughness = load_gltf_texture(ctx, path,
                cm->pbr_metallic_roughness.metallic_roughness_texture.texture);
            mat->normal_map = load_gltf_texture(ctx, path,
                cm->normal_texture.texture);
            mat->emissive = load_gltf_texture(ctx, path,
                cm->emissive_texture.texture);
        }
    }

    for (u32 ni = 0; ni < data->nodes_count; ni++) {
        cgltf_node *node = &data->nodes[ni];
        SceneNode *sn = &out_scene->nodes[ni];
        sn->parent_index = UINT32_MAX;
        sn->mesh_index = UINT32_MAX;
        sn->skin_mesh_index = UINT32_MAX;
        sn->material_idx = 0;
        sn->has_mesh = false;
        sn->skinned = false;

        if (node->parent) {
            /* O(1): cgltf nodes are a contiguous array, pointer diff = index */
            sn->parent_index = (u32)(node->parent - data->nodes);
        }

        cgltf_float node_matrix[16];
        cgltf_node_transform_local(node, node_matrix);
        memcpy(sn->local_transform.e, node_matrix, sizeof(f32) * 16);

        if (!node->mesh) continue;

        sn->has_mesh = true;

        for (u32 pi = 0; pi < node->mesh->primitives_count; pi++) {
            cgltf_primitive *prim = &node->mesh->primitives[pi];

            cgltf_accessor *pos_acc = NULL;
            cgltf_accessor *nrm_acc = NULL;
            cgltf_accessor *uv_acc  = NULL;
            cgltf_accessor *jnt_acc = NULL;
            cgltf_accessor *wgt_acc = NULL;
            cgltf_accessor *idx_acc = prim->indices;

            for (u32 ai = 0; ai < prim->attributes_count; ai++) {
                cgltf_attribute *attr = &prim->attributes[ai];
                if (attr->type == cgltf_attribute_type_position) pos_acc = attr->data;
                if (attr->type == cgltf_attribute_type_normal)   nrm_acc = attr->data;
                /* R252: pick set 0 explicitly. glTF allows multiple TEXCOORD_n /
                 * JOINTS_n / WEIGHTS_n; the previous unconditional assignment kept
                 * whichever set appeared LAST in the attribute list. When TEXCOORD_1
                 * (lightmap/detail UV) followed TEXCOORD_0, the mesh got bound to the
                 * secondary UV set while materials default to texCoord 0 → visibly
                 * wrong/stretched texturing. The engine consumes a single UV set and
                 * a single 4-influence skin set, so bind index 0 for all three. */
                if (attr->type == cgltf_attribute_type_texcoord && attr->index == 0) uv_acc  = attr->data;
                if (attr->type == cgltf_attribute_type_joints   && attr->index == 0) jnt_acc = attr->data;
                if (attr->type == cgltf_attribute_type_weights  && attr->index == 0) wgt_acc = attr->data;
            }

            if (!pos_acc) continue;

            u32 mat_idx = 0;
            if (prim->material) {
                /* O(1): cgltf materials are a contiguous array, pointer diff = index */
                mat_idx = (u32)(prim->material - data->materials);
            }

            u32 vert_count = (u32)pos_acc->count;
            u32 idx_count = 0;
            RHIBuffer ibuf = {0};

            if (idx_acc) {
                idx_count = (u32)idx_acc->count;
                /* R115-2/R115-3: Validate calloc and cgltf_buffer_data to prevent
                 * NULL dereference on malformed glTF files with missing buffers. */
                u32 *indices = calloc(idx_count, sizeof(u32));
                const u8 *idx_data = cgltf_buffer_data(idx_acc);
                if (indices && idx_data) {
                    if (idx_acc->component_type == cgltf_component_type_r_16u) {
                        const u16 *src = (const u16 *)idx_data;
                        for (u32 ii = 0; ii < idx_count; ii++) indices[ii] = (u32)src[ii];
                    } else if (idx_acc->component_type == cgltf_component_type_r_32u) {
                        memcpy(indices, idx_data, idx_count * sizeof(u32));
                    } else {
                        const u8 *src = idx_data;
                        for (u32 ii = 0; ii < idx_count; ii++) indices[ii] = (u32)src[ii];
                    }
                    RHIBufferDesc ibdesc = { .usage = RHI_BUFFER_USAGE_INDEX, .size = idx_count * sizeof(u32), .initial_data = indices };
                    ibuf = rhi_buffer_create(ctx->device, &ibdesc);
                }
                free(indices);
            }

            /* R415: identical to the counting-pass predicate (node->skin &&
             * JOINTS_0 && WEIGHTS_0) so the allocated totals always match. */
            if (node->skin && jnt_acc && wgt_acc) {
                /* R415: defensive clamp — never write past the allocated
                 * skinned_meshes array even if the predicates ever diverge. */
                if (out_scene->skinned_mesh_count >= total_skinned) {
                    if (rhi_handle_valid(ibuf)) rhi_buffer_destroy(ctx->device, ibuf);
                    continue;
                }
                sn->skinned = true;
                SkinnedVertex *sverts = calloc(vert_count, sizeof(SkinnedVertex));
                /* R115-2/R115-3: Skip primitive if allocation or buffer data fails. */
                if (!sverts) continue;
                const u8 *pd = cgltf_buffer_data(pos_acc);
                if (!pd) { free(sverts); continue; }
                /* R415: validated component type inside (raw f32 memcpy only
                 * for actual float VEC3 data; converted otherwise). */
                gltf_read_vec3_attr(pos_acc, vert_count, (u8 *)&sverts[0].pos, sizeof(SkinnedVertex));
                if (nrm_acc) {
                    gltf_read_vec3_attr(nrm_acc, vert_count, (u8 *)&sverts[0].normal, sizeof(SkinnedVertex));
                }
                if (uv_acc && cgltf_accessor_is_type(uv_acc, cgltf_type_vec2)) {
                    const u8 *ud = cgltf_buffer_data(uv_acc);
                    usize us = cgltf_accessor_stride(uv_acc);
                    for (u32 vi = 0; ud && vi < vert_count; vi++) {
                        /* R279 (CORRECTNESS): TEXCOORD_0 may be normalized
                         * UNSIGNED_BYTE/UNSIGNED_SHORT (glTF permits it for UV
                         * compression), not just FLOAT. A raw memcpy-as-float
                         * reinterprets those bytes and corrupts texture coords.
                         * cgltf_accessor_read_float honours component_type +
                         * normalized + stride; FLOAT UVs are unchanged. */
                        if (!cgltf_accessor_read_float(uv_acc, vi, sverts[vi].uv, 2) &&
                            uv_acc->component_type == cgltf_component_type_r_32f)
                            /* R415: fallback memcpy only when the accessor is
                             * actually float — never reinterpret other types. */
                            memcpy(sverts[vi].uv, ud + vi * us, sizeof(f32) * 2);
                    }
                }

                usize jnt_stride = cgltf_accessor_stride(jnt_acc);
                const u8 *jd = cgltf_buffer_data(jnt_acc);
                usize wgt_stride = cgltf_accessor_stride(wgt_acc);
                const u8 *wd = cgltf_buffer_data(wgt_acc);
                for (u32 vi = 0; jd && wd && vi < vert_count; vi++) {
                    if (jnt_acc->component_type == cgltf_component_type_r_8u) {
                        const u8 *j = jd + vi * jnt_stride;
                        for (u32 k = 0; k < 4; k++) sverts[vi].joints[k] = (u32)j[k];
                    } else if (jnt_acc->component_type == cgltf_component_type_r_16u) {
                        const u16 *j = (const u16 *)(jd + vi * jnt_stride);
                        for (u32 k = 0; k < 4; k++) sverts[vi].joints[k] = (u32)j[k];
                    } else if (jnt_acc->component_type == cgltf_component_type_r_32u) {
                        /* R249: glTF 2.0 permits UNSIGNED_INT JOINTS_0 (e.g. skins
                         * with >255 joints). Without this branch joints stayed 0,
                         * collapsing all skinned verts onto joint 0. */
                        const u32 *j = (const u32 *)(jd + vi * jnt_stride);
                        for (u32 k = 0; k < 4; k++) sverts[vi].joints[k] = j[k];
                    }
                    /* R253: the skinning shaders index texelFetch(u_joints, j*4+..)
                     * and the joint buffer holds exactly SKELETON_MAX_JOINTS matrices
                     * (skeleton_set_joints clamps joint_count to it and uploads only
                     * that many). R249 enabled u32 JOINTS_0, so an index >= the limit
                     * now reads out of bounds (UB) on both GL and VK. Clamp to the
                     * last valid joint so the fetch stays in-bounds (oversized skins
                     * are warned about below; deformation is degraded but not UB). */
                    for (u32 k = 0; k < 4; k++) {
                        if (sverts[vi].joints[k] >= (u32)SKELETON_MAX_JOINTS)
                            sverts[vi].joints[k] = (u32)SKELETON_MAX_JOINTS - 1u;
                    }
                    /* R278 (CORRECTNESS): WEIGHTS_0 is commonly exported as
                     * normalized UNSIGNED_BYTE/UNSIGNED_SHORT (e.g. Blender), not
                     * FLOAT. The previous raw 16-byte memcpy reinterpreted those
                     * 4/8 bytes as IEEE754 floats, producing garbage weights
                     * (0xFF00_0000 -> ~1.4e-45) and breaking skinning. Use cgltf's
                     * accessor reader, which honours component_type + normalized +
                     * stride + sparse (mirrors the integer JOINTS branch above).
                     * FLOAT weights are unchanged. */
                    if (!cgltf_accessor_read_float(wgt_acc, vi, sverts[vi].weights, 4)) {
                        memcpy(sverts[vi].weights, wd + vi * wgt_stride, sizeof(f32) * 4);
                    }
                    f32 wsum = sverts[vi].weights[0] + sverts[vi].weights[1] + sverts[vi].weights[2] + sverts[vi].weights[3];
                    if (wsum > 0.0f) {
                        f32 inv = 1.0f / wsum;
                        sverts[vi].weights[0] *= inv;
                        sverts[vi].weights[1] *= inv;
                        sverts[vi].weights[2] *= inv;
                        sverts[vi].weights[3] *= inv;
                    }
                }

                RHIBufferDesc vbdesc = { .usage = RHI_BUFFER_USAGE_VERTEX, .size = vert_count * sizeof(SkinnedVertex), .initial_data = sverts };
                RHIBuffer vbuf = rhi_buffer_create(ctx->device, &vbdesc);
                free(sverts);

                SkinnedMesh *sm = &out_scene->skinned_meshes[out_scene->skinned_mesh_count++];
                sm->vertex_buf = vbuf;
                sm->index_buf = ibuf;
                sm->index_count = idx_count;
                sm->material_idx = mat_idx;
                sm->skinned = true;
                if (!sn->has_mesh || sn->skin_mesh_index == UINT32_MAX) {
                    sn->skin_mesh_index = out_scene->skinned_mesh_count - 1;
                    sn->material_idx = mat_idx;
                }
            } else {
                /* R415: defensive clamp — never write past the allocated
                 * meshes array even if the predicates ever diverge. */
                if (out_scene->mesh_count >= total_meshes) {
                    if (rhi_handle_valid(ibuf)) rhi_buffer_destroy(ctx->device, ibuf);
                    continue;
                }
                Vertex *verts = calloc(vert_count, sizeof(Vertex));
                /* R115-2/R115-3: Skip primitive if allocation or buffer data fails. */
                if (!verts) continue;
                const u8 *pd = cgltf_buffer_data(pos_acc);
                if (!pd) { free(verts); continue; }
                /* R415: validated component type inside (raw f32 memcpy only
                 * for actual float VEC3 data; converted otherwise). */
                gltf_read_vec3_attr(pos_acc, vert_count, (u8 *)&verts[0].pos, sizeof(Vertex));
                if (nrm_acc) {
                    gltf_read_vec3_attr(nrm_acc, vert_count, (u8 *)&verts[0].normal, sizeof(Vertex));
                }
                if (uv_acc && cgltf_accessor_is_type(uv_acc, cgltf_type_vec2)) {
                    const u8 *ud = cgltf_buffer_data(uv_acc);
                    usize us = cgltf_accessor_stride(uv_acc);
                    for (u32 vi = 0; ud && vi < vert_count; vi++) {
                        /* R279 (CORRECTNESS): TEXCOORD_0 may be normalized
                         * UNSIGNED_BYTE/UNSIGNED_SHORT (glTF permits it for UV
                         * compression), not just FLOAT. A raw memcpy-as-float
                         * reinterprets those bytes and corrupts texture coords.
                         * cgltf_accessor_read_float honours component_type +
                         * normalized + stride; FLOAT UVs are unchanged. */
                        if (!cgltf_accessor_read_float(uv_acc, vi, verts[vi].uv, 2) &&
                            uv_acc->component_type == cgltf_component_type_r_32f)
                            /* R415: fallback memcpy only when the accessor is
                             * actually float — never reinterpret other types. */
                            memcpy(verts[vi].uv, ud + vi * us, sizeof(f32) * 2);
                    }
                }

                RHIBufferDesc vbdesc = { .usage = RHI_BUFFER_USAGE_VERTEX, .size = vert_count * sizeof(Vertex), .initial_data = verts };
                RHIBuffer vbuf = rhi_buffer_create(ctx->device, &vbdesc);

                Mesh *m = &out_scene->meshes[out_scene->mesh_count++];
                m->vertex_buf = vbuf;
                m->index_buf = ibuf;
                m->index_count = idx_count;
                m->vertex_count = vert_count;
                m->material_idx = mat_idx;
                m->aabb_min = vec3(1e30f, 1e30f, 1e30f);
                m->aabb_max = vec3(-1e30f, -1e30f, -1e30f);
                {
                f32 *mn = m->aabb_min.e, *mx = m->aabb_max.e;
                for (u32 vi = 0; vi < vert_count; vi++) {
                    const f32 *p = verts[vi].pos;
                    if (p[0] < mn[0]) mn[0] = p[0];
                    if (p[0] > mx[0]) mx[0] = p[0];
                    if (p[1] < mn[1]) mn[1] = p[1];
                    if (p[1] > mx[1]) mx[1] = p[1];
                    if (p[2] < mn[2]) mn[2] = p[2];
                    if (p[2] > mx[2]) mx[2] = p[2];
                }
                }
                free(verts);
                if (sn->mesh_index == UINT32_MAX) {
                    sn->mesh_index = out_scene->mesh_count - 1;
                    sn->material_idx = mat_idx;
                }
            }
        }
    }

    out_scene->node_count = (u32)data->nodes_count;

    /* R415: node_index → joint_index map. Previously built and freed inside
     * the skin block, then the animation loop linearly rescanned skin->joints
     * per channel (O(channels × joints)). Kept alive through animation
     * parsing now and freed just before cgltf_free. */
    u32 *node_to_joint = NULL;

    if (data->skins_count > 0) {
        cgltf_skin *skin = &data->skins[0];
        /* R253: skeleton_set_joints clamps to SKELETON_MAX_JOINTS and the GPU joint
         * buffer/skinning shaders only address that many matrices. A larger rig
         * can't be skinned correctly (vertex joint indices are clamped above to
         * avoid an out-of-bounds texelFetch); warn so the truncation is visible. */
        if (skin->joints_count > (cgltf_size)SKELETON_MAX_JOINTS) {
            LOG_WARN("glTF skin has %u joints but engine supports %d; extra joints are "
                     "dropped and affected vertices clamped (skinning will be incorrect)",
                     (u32)skin->joints_count, SKELETON_MAX_JOINTS);
        }
        out_scene->joint_count = (u32)skin->joints_count;
        /* Single alloc: joint_parents (u32[]) + inverse_bind (Mat4[]) */
        usize jp_bytes = skin->joints_count * sizeof(u32);
        usize ib_off   = (jp_bytes + 15u) & ~(usize)15u;
        u8 *skin_buf    = (u8 *)calloc(1, ib_off + skin->joints_count * sizeof(Mat4));
        if (!skin_buf) {
            LOG_ERROR("glTF: skin allocation failed");
            cgltf_free(data);
            /* R353: meshes/materials may already be on out_scene. */
            asset_scene_free(ctx, out_scene);
            return false;
        }
        out_scene->joint_parents = (u32 *)skin_buf;
        out_scene->inverse_bind  = (Mat4 *)(skin_buf + ib_off);

        /* Build node_index → joint_index mapping for O(1) parent lookup */
        node_to_joint = (u32 *)malloc(data->nodes_count * sizeof(u32));
        if (!node_to_joint) {
            LOG_ERROR("glTF: node_to_joint allocation failed");
            cgltf_free(data);
            /* R353: joint_parents already owned by out_scene — free via scene. */
            asset_scene_free(ctx, out_scene);
            return false;
        }
        for (u32 ni2 = 0; ni2 < data->nodes_count; ni2++) node_to_joint[ni2] = UINT32_MAX;
        for (u32 jj = 0; jj < skin->joints_count; jj++) {
            node_to_joint[(u32)(skin->joints[jj] - data->nodes)] = jj;
        }

        for (u32 ji = 0; ji < skin->joints_count; ji++) {
            cgltf_node *joint = skin->joints[ji];
            if (joint->parent) {
                u32 parent_node_idx = (u32)(joint->parent - data->nodes);
                out_scene->joint_parents[ji] = node_to_joint[parent_node_idx];
            } else {
                out_scene->joint_parents[ji] = UINT32_MAX;
            }
        }
        /* R415: node_to_joint NOT freed here — reused by the animation loop. */

        if (skin->inverse_bind_matrices) {
            cgltf_accessor *ibm = skin->inverse_bind_matrices;
            /* R415: the raw f32 cast below requires float MAT4 data, but
             * cgltf_validate does not check component_type — a file declaring
             * MAT4/UNSIGNED_BYTE passed validation and was then read as f32
             * (4× over-read of the accessor's real bytes). Convert through
             * cgltf for anything that is not actually float MAT4. */
            if (ibm->component_type == cgltf_component_type_r_32f &&
                cgltf_accessor_is_type(ibm, cgltf_type_mat4)) {
                const f32 *ibm_data = (const f32 *)cgltf_buffer_data(ibm);
                usize ibm_count = (usize)ibm->count;
                /* R115-3: Check ibm_data for NULL (cgltf_buffer_data may return NULL). */
                for (u32 ji = 0; ibm_data && ji < ibm_count && ji < skin->joints_count; ji++) {
                    memcpy(out_scene->inverse_bind[ji].e, ibm_data + ji * 16, sizeof(f32) * 16);
                }
            } else {
                for (u32 ji = 0; ji < ibm->count && ji < skin->joints_count; ji++) {
                    cgltf_accessor_read_float(ibm, ji, &out_scene->inverse_bind[ji].e[0][0], 16);
                }
            }
        } else {
            for (u32 ji = 0; ji < skin->joints_count; ji++) {
                out_scene->inverse_bind[ji] = mat4_identity();
            }
        }
    }

    if (data->animations_count > 0) {
        cgltf_animation *anim = &data->animations[0];
        out_scene->anim_clip_count = 1;
        out_scene->anim_clips = calloc(1, sizeof(AnimClip));
        AnimClip *clip = &out_scene->anim_clips[0];

        f32 max_time = 0;
        for (u32 ci = 0; ci < anim->channels_count; ci++) {
            cgltf_animation_channel *ch = &anim->channels[ci];
            if (!ch->sampler || !ch->sampler->input) continue;
            /* R415: times are read as raw f32 below. The spec mandates float
             * scalar sampler input, but cgltf_validate does not enforce it —
             * skip non-float inputs instead of reinterpreting them. */
            if (ch->sampler->input->component_type != cgltf_component_type_r_32f ||
                ch->sampler->input->type != cgltf_type_scalar) continue;
            f32 *times_data = (f32 *)cgltf_buffer_data(ch->sampler->input);
            usize time_count = (usize)ch->sampler->input->count;
            if (time_count > 0 && times_data) {
                f32 last = times_data[time_count - 1];
                if (last > max_time) max_time = last;
            }
        }
        anim_clip_init(clip, max_time > 0 ? max_time : 1.0f, true);

        for (u32 ci = 0; ci < anim->channels_count; ci++) {
            cgltf_animation_channel *ch = &anim->channels[ci];
            if (!ch->target_node || !ch->sampler) continue;

            /* R415: O(1) lookup via the node→joint map (kept alive from the
             * skin block) instead of a linear scan over skin->joints for every
             * channel — was O(channels × joints). */
            u32 joint_idx = UINT32_MAX;
            if (node_to_joint) {
                joint_idx = node_to_joint[(u32)(ch->target_node - data->nodes)];
            }
            if (joint_idx == UINT32_MAX) continue;

            AnimPathType path;
            if (ch->target_path == cgltf_animation_path_type_translation) path = ANIM_PATH_TRANSLATION;
            else if (ch->target_path == cgltf_animation_path_type_rotation) path = ANIM_PATH_ROTATION;
            else if (ch->target_path == cgltf_animation_path_type_scale) path = ANIM_PATH_SCALE;
            else continue;

            cgltf_animation_sampler *samp = ch->sampler;
            /* R415: times are read as raw f32 below — require the spec-mandated
             * float scalar input (cgltf_validate does not check this). */
            if (!samp->input || !samp->output ||
                samp->input->component_type != cgltf_component_type_r_32f ||
                samp->input->type != cgltf_type_scalar) continue;
            f32 *times = (f32 *)cgltf_buffer_data(samp->input);
            f32 *values = (f32 *)cgltf_buffer_data(samp->output);
            usize kf_count = (usize)samp->input->count;
            if (!times || !values || kf_count == 0) continue;

            u32 n = (u32)kf_count;
            if (n > SKELETON_MAX_KEYFRAMES) n = SKELETON_MAX_KEYFRAMES;

            f32 packed_values[SKELETON_MAX_KEYFRAMES][4];
            usize comp = cgltf_num_components(samp->output->type);
            memset(packed_values, 0, sizeof(packed_values));
            /* R415: sampler output may legally be normalized BYTE/SHORT
             * (quantized animation) — reading it as raw f32 reinterpreted and
             * over-read the data. Convert per-key through cgltf unless the
             * accessor is actually float. */
            bool output_float = samp->output->component_type == cgltf_component_type_r_32f;
            for (u32 k = 0; k < n; k++) {
                if (output_float) {
                    for (usize c = 0; c < comp && c < 4; c++) {
                        packed_values[k][c] = values[k * comp + c];
                    }
                } else {
                    cgltf_accessor_read_float(samp->output, k, packed_values[k],
                                              comp < 4 ? comp : 4);
                }
                if (path == ANIM_PATH_ROTATION && comp == 4) {
                    f32 len = 0;
                    for (usize c = 0; c < 4; c++) len += packed_values[k][c] * packed_values[k][c];
                    if (len > 0) { f32 inv = 1.0f / sqrtf(len); for (usize c = 0; c < 4; c++) packed_values[k][c] *= inv; }
                }
            }

            anim_clip_add_channel(clip, joint_idx, path, n, times, &packed_values[0][0]);
            /* R251 (CORRECTNESS): honor the sampler interpolation mode. cgltf exposes
             * samp->interpolation; the loader previously ignored it, so STEP samplers
             * (stepped/hard-cut animations, a common export default for mechanical
             * motion) were interpolated linearly — producing in-between poses that
             * never exist in the source. clip_sample holds the keyframe for STEP.
             * (CUBICSPLINE would need 3x-tangent output parsing; treated as LINEAR
             * here, matching the prior behavior.) */
            if (samp->interpolation == cgltf_interpolation_type_step &&
                clip->channel_count > 0) {
                clip->channels[clip->channel_count - 1].interp = ANIM_INTERP_STEP;
            }
        }
    }

    free(node_to_joint); /* R415: kept alive through animation parsing */
    cgltf_free(data);
    LOG_INFO("Loaded glTF: %s (%u meshes, %u skinned, %u nodes, %u joints, %u anims)", path,
        out_scene->mesh_count, out_scene->skinned_mesh_count,
        out_scene->node_count, out_scene->joint_count, out_scene->anim_clip_count);
    return true;
}

void asset_scene_free(AssetCtx *ctx, Scene *scene) {
    for (u32 i = 0; i < scene->mesh_count; i++) {
        Mesh *m = &scene->meshes[i];
        if (rhi_handle_valid(m->vertex_buf)) rhi_buffer_destroy(ctx->device, m->vertex_buf);
        if (rhi_handle_valid(m->index_buf))  rhi_buffer_destroy(ctx->device, m->index_buf);
    }
    free(scene->meshes);
    for (u32 i = 0; i < scene->skinned_mesh_count; i++) {
        SkinnedMesh *sm = &scene->skinned_meshes[i];
        if (rhi_handle_valid(sm->vertex_buf)) rhi_buffer_destroy(ctx->device, sm->vertex_buf);
        if (rhi_handle_valid(sm->index_buf))  rhi_buffer_destroy(ctx->device, sm->index_buf);
    }
    free(scene->skinned_meshes);
    for (u32 i = 0; i < scene->material_count; i++) {
        Material *mat = &scene->materials[i];
        if (rhi_handle_valid(mat->albedo))             asset_texture_free(ctx, mat->albedo);
        if (rhi_handle_valid(mat->metallic_roughness))  asset_texture_free(ctx, mat->metallic_roughness);
        if (rhi_handle_valid(mat->normal_map))          asset_texture_free(ctx, mat->normal_map);
        if (rhi_handle_valid(mat->emissive))            asset_texture_free(ctx, mat->emissive);
    }
    free(scene->materials);
    free(scene->nodes);
    free(scene->joint_parents); /* single alloc: joint_parents + inverse_bind */
    free(scene->anim_clips);
    free(scene->resources);
    memset(scene, 0, sizeof(*scene));
}

void scene_compute_world_transforms(Scene *scene) {
    /* R415: memoized DFS over parent_index — O(n) instead of the previous
     * iterate-until-stable loop (O(n × depth), O(n²) worst case). Results are
     * identical for valid scenes (the R256 order-independence is preserved:
     * a child at a lower index than its parent still resolves through the
     * parent's world transform). The visited-state array also breaks parent
     * cycles deterministically. R151's guards for malformed/self parent_index
     * are kept. */
    u32 n = scene->node_count;
    if (n == 0 || !scene->nodes) return;

    u8 *state = (u8 *)calloc(n, 1); /* 0 = unseen, 1 = on current chain, 2 = done */
    u32 *stack = (u32 *)malloc(n * sizeof(u32));
    if (!state || !stack) {
        free(state);
        free(stack);
        /* OOM fallback: at least leave valid (root) transforms behind. */
        for (u32 i = 0; i < n; i++) {
            scene->nodes[i].world_transform = scene->nodes[i].local_transform;
        }
        return;
    }

    for (u32 i = 0; i < n; i++) {
        if (state[i] != 0) continue;

        /* Walk up the parent chain, pushing unresolved nodes, until a root,
         * an already-resolved node, or a cycle is reached. */
        u32 top = 0;
        u32 cur = i;
        while (state[cur] == 0) {
            SceneNode *node = &scene->nodes[cur];
            u32 p = node->parent_index;
            /* R151: guard malformed/self parent_index (out-of-bounds read). */
            if (p == UINT32_MAX || p >= n || p == cur) {
                node->world_transform = node->local_transform;
                state[cur] = 2;
                break;
            }
            stack[top++] = cur;
            state[cur] = 1;
            cur = p;
        }
        if (state[cur] == 1) {
            /* Parent cycle: treat the re-entered node as its own root so the
             * chain below it resolves deterministically. */
            scene->nodes[cur].world_transform = scene->nodes[cur].local_transform;
            state[cur] = 2;
        }
        /* Resolve the pushed chain deepest-first; every parent is done. The
         * cycle entry point `cur` is on the stack too — it was already
         * resolved as a root above, so skip it to avoid double composition. */
        while (top > 0) {
            u32 idx = stack[--top];
            if (idx == cur) continue;
            SceneNode *node = &scene->nodes[idx];
            node->world_transform = mat4_mul(scene->nodes[node->parent_index].world_transform,
                                             node->local_transform);
            state[idx] = 2;
        }
    }

    free(state);
    free(stack);
}

/* ---- Async loading wrappers ---- */

typedef struct {
    AssetCtx *ctx;
    AssetAsyncCallback user_cb;
    void *user;
} AssetTextureAsyncCtx;

static void asset_texture_async_done(void *user_data, void *data, u32 size) {
    AssetTextureAsyncCtx *actx = (AssetTextureAsyncCtx *)user_data;

    if (actx && actx->user_cb) {
        actx->user_cb(actx->user, data, size);
    } else if (data) {
        free(data);
    }

    free(actx);
}

u64 asset_load_texture_async(AssetCtx *ctx, const char *path,
                             AssetAsyncCallback cb, void *user) {
    if (!ctx || !path || !cb) return 0;

    AssetTextureAsyncCtx *actx = calloc(1, sizeof(*actx));
    if (!actx) return 0;
    actx->ctx = ctx;
    actx->user_cb = cb;
    actx->user = user;

    u64 id = async_loader_request_texture(path, asset_texture_async_done, actx,
                                          ASYNC_PRIORITY_HIGH);
    if (id == 0) free(actx);
    return id;
}

u64 asset_load_file_async(AssetCtx *ctx, const char *path,
                          AssetAsyncCallback cb, void *user) {
    (void)ctx;
    return async_loader_request(path, cb, user);
}
