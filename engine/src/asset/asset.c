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

static bool cgltf_accessor_is_type(cgltf_accessor *acc, cgltf_type type) {
    return acc && acc->type == type;
}

static RHITexture load_gltf_texture(AssetCtx *ctx, const char *gltf_path, cgltf_texture *tex) {
    if (!tex || !tex->image || !tex->image->uri) return RHI_HANDLE_NULL;
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
        result = cgltf_load_buffers(&opts, data, path);
    } else {
        result = cgltf_parse_file(&opts, path, &data);
        if (result != cgltf_result_success) {
            LOG_ERROR("cgltf parse failed (%d): %s", result, path);
            return false;
        }
        result = cgltf_load_buffers(&opts, data, path);
    }

    if (result != cgltf_result_success) {
        LOG_ERROR("cgltf buffer load failed (%d): %s", result, path);
        cgltf_free(data);
        return false;
    }

    u32 total_meshes = 0;
    u32 total_skinned = 0;

    out_scene->nodes = calloc(data->nodes_count > 0 ? data->nodes_count : 1, sizeof(SceneNode));
    out_scene->node_count = 0;

    for (u32 ni = 0; ni < data->nodes_count; ni++) {
        cgltf_node *node = &data->nodes[ni];
        if (!node->mesh) continue;
        for (u32 pi = 0; pi < node->mesh->primitives_count; pi++) {
            cgltf_primitive *prim = &node->mesh->primitives[pi];
            bool has_skin = node->skin != NULL;
            if (!has_skin) {
                for (u32 ai = 0; ai < prim->attributes_count; ai++) {
                    if (prim->attributes[ai].type == cgltf_attribute_type_joints) has_skin = true;
                }
            }
            if (has_skin) total_skinned++;
            else total_meshes++;
        }
    }

    out_scene->meshes = calloc(total_meshes > 0 ? total_meshes : 1, sizeof(Mesh));
    out_scene->skinned_meshes = calloc(total_skinned > 0 ? total_skinned : 1, sizeof(SkinnedMesh));
    out_scene->mesh_count = 0;
    out_scene->skinned_mesh_count = 0;

    /* Pre-build materials from cgltf data for O(1) lookup by pointer diff */
    if (data->materials_count > 0) {
        out_scene->materials = calloc(data->materials_count, sizeof(Material));
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
                if (attr->type == cgltf_attribute_type_texcoord) uv_acc  = attr->data;
                if (attr->type == cgltf_attribute_type_joints)   jnt_acc = attr->data;
                if (attr->type == cgltf_attribute_type_weights)  wgt_acc = attr->data;
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

            if (jnt_acc && wgt_acc) {
                sn->skinned = true;
                SkinnedVertex *sverts = calloc(vert_count, sizeof(SkinnedVertex));
                /* R115-2/R115-3: Skip primitive if allocation or buffer data fails. */
                if (!sverts) continue;
                const u8 *pd = cgltf_buffer_data(pos_acc);
                if (!pd) { free(sverts); continue; }
                usize ps = cgltf_accessor_stride(pos_acc);
                for (u32 vi = 0; vi < vert_count; vi++) {
                    memcpy(sverts[vi].pos, pd + vi * ps, sizeof(f32) * 3);
                }
                if (nrm_acc) {
                    const u8 *nd = cgltf_buffer_data(nrm_acc);
                    usize ns = cgltf_accessor_stride(nrm_acc);
                    for (u32 vi = 0; nd && vi < vert_count; vi++) {
                        memcpy(sverts[vi].normal, nd + vi * ns, sizeof(f32) * 3);
                    }
                }
                if (uv_acc && cgltf_accessor_is_type(uv_acc, cgltf_type_vec2)) {
                    const u8 *ud = cgltf_buffer_data(uv_acc);
                    usize us = cgltf_accessor_stride(uv_acc);
                    for (u32 vi = 0; ud && vi < vert_count; vi++) {
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
                    memcpy(sverts[vi].weights, wd + vi * wgt_stride, sizeof(f32) * 4);
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
                Vertex *verts = calloc(vert_count, sizeof(Vertex));
                /* R115-2/R115-3: Skip primitive if allocation or buffer data fails. */
                if (!verts) continue;
                const u8 *pd = cgltf_buffer_data(pos_acc);
                if (!pd) { free(verts); continue; }
                usize ps = cgltf_accessor_stride(pos_acc);
                for (u32 vi = 0; vi < vert_count; vi++) {
                    memcpy(verts[vi].pos, pd + vi * ps, sizeof(f32) * 3);
                }
                if (nrm_acc) {
                    const u8 *nd = cgltf_buffer_data(nrm_acc);
                    usize ns = cgltf_accessor_stride(nrm_acc);
                    for (u32 vi = 0; nd && vi < vert_count; vi++) {
                        memcpy(verts[vi].normal, nd + vi * ns, sizeof(f32) * 3);
                    }
                }
                if (uv_acc && cgltf_accessor_is_type(uv_acc, cgltf_type_vec2)) {
                    const u8 *ud = cgltf_buffer_data(uv_acc);
                    usize us = cgltf_accessor_stride(uv_acc);
                    for (u32 vi = 0; ud && vi < vert_count; vi++) {
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

    if (data->skins_count > 0) {
        cgltf_skin *skin = &data->skins[0];
        out_scene->joint_count = (u32)skin->joints_count;
        /* Single alloc: joint_parents (u32[]) + inverse_bind (Mat4[]) */
        usize jp_bytes = skin->joints_count * sizeof(u32);
        usize ib_off   = (jp_bytes + 15u) & ~(usize)15u;
        u8 *skin_buf    = (u8 *)calloc(1, ib_off + skin->joints_count * sizeof(Mat4));
        if (!skin_buf) {
            LOG_ERROR("glTF: skin allocation failed");
            cgltf_free(data);
            return false;
        }
        out_scene->joint_parents = (u32 *)skin_buf;
        out_scene->inverse_bind  = (Mat4 *)(skin_buf + ib_off);

        /* Build node_index → joint_index mapping for O(1) parent lookup */
        u32 *node_to_joint = (u32 *)malloc(data->nodes_count * sizeof(u32));
        if (!node_to_joint) {
            LOG_ERROR("glTF: node_to_joint allocation failed");
            cgltf_free(data);
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
        free(node_to_joint);

        if (skin->inverse_bind_matrices) {
            const f32 *ibm_data = (const f32 *)cgltf_buffer_data(skin->inverse_bind_matrices);
            usize ibm_count = (usize)skin->inverse_bind_matrices->count;
            /* R115-3: Check ibm_data for NULL (cgltf_buffer_data may return NULL). */
            for (u32 ji = 0; ibm_data && ji < ibm_count && ji < skin->joints_count; ji++) {
                memcpy(out_scene->inverse_bind[ji].e, ibm_data + ji * 16, sizeof(f32) * 16);
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

            u32 joint_idx = UINT32_MAX;
            if (data->skins_count > 0) {
                cgltf_skin *skin = &data->skins[0];
                for (u32 ji = 0; ji < skin->joints_count; ji++) {
                    if (skin->joints[ji] == ch->target_node) {
                        joint_idx = ji;
                        break;
                    }
                }
            }
            if (joint_idx == UINT32_MAX) continue;

            AnimPathType path;
            if (ch->target_path == cgltf_animation_path_type_translation) path = ANIM_PATH_TRANSLATION;
            else if (ch->target_path == cgltf_animation_path_type_rotation) path = ANIM_PATH_ROTATION;
            else if (ch->target_path == cgltf_animation_path_type_scale) path = ANIM_PATH_SCALE;
            else continue;

            cgltf_animation_sampler *samp = ch->sampler;
            f32 *times = (f32 *)cgltf_buffer_data(samp->input);
            f32 *values = (f32 *)cgltf_buffer_data(samp->output);
            usize kf_count = (usize)samp->input->count;
            if (!times || !values || kf_count == 0) continue;

            u32 n = (u32)kf_count;
            if (n > SKELETON_MAX_KEYFRAMES) n = SKELETON_MAX_KEYFRAMES;

            f32 packed_values[SKELETON_MAX_KEYFRAMES][4];
            usize comp = cgltf_num_components(samp->output->type);
            memset(packed_values, 0, sizeof(packed_values));
            for (u32 k = 0; k < n; k++) {
                for (usize c = 0; c < comp && c < 4; c++) {
                    packed_values[k][c] = values[k * comp + c];
                }
                if (path == ANIM_PATH_ROTATION && comp == 4) {
                    f32 len = 0;
                    for (usize c = 0; c < 4; c++) len += packed_values[k][c] * packed_values[k][c];
                    if (len > 0) { f32 inv = 1.0f / sqrtf(len); for (usize c = 0; c < 4; c++) packed_values[k][c] *= inv; }
                }
            }

            anim_clip_add_channel(clip, joint_idx, path, n, times, &packed_values[0][0]);
        }
    }

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
    for (u32 i = 0; i < scene->node_count; i++) {
        SceneNode *node = &scene->nodes[i];
        /* R151: Validate parent_index against node_count — a malformed BSCN/JSON
         * file can set parent_index to any u32 value. Without this check,
         * scene->nodes[parent_index] is an out-of-bounds read. Also handles
         * self-references (parent_index == i) which would read uninitialized
         * world_transform. */
        if (node->parent_index == UINT32_MAX || node->parent_index >= scene->node_count
            || node->parent_index == i) {
            node->world_transform = node->local_transform;
        } else {
            SceneNode *parent = &scene->nodes[node->parent_index];
            node->world_transform = mat4_mul(parent->world_transform, node->local_transform);
        }
    }
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
