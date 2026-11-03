#include <renderer/world_presentation.h>
#include <math.h>
#include <string.h>

_Static_assert(sizeof(WorldInstanceSnapshot) == 64u, "instance texel rows must be four vec4 values");

static bool finite_vec3(Vec3 value) {
    return isfinite(value.e[0]) && isfinite(value.e[1]) && isfinite(value.e[2]);
}

static bool finite_mat4(Mat4 value) {
    for (u32 r = 0; r < 4u; r++)
        for (u32 c = 0; c < 4u; c++)
            if (!isfinite(value.e[r][c])) return false;
    return true;
}

static bool valid_material(const MeshMaterial *material) {
    if (!finite_vec3(material->base_color) || material->base_color.e[0] < 0.0f ||
        material->base_color.e[1] < 0.0f || material->base_color.e[2] < 0.0f ||
        !isfinite(material->roughness) || material->roughness < 0.0f || material->roughness > 1.0f)
        return false;
    return rhi_handle_valid(material->albedo) == rhi_handle_valid(material->sampler);
}

static bool valid_draw(const MeshGpu *gpu, const MeshDrawDesc *draw) {
    if (draw->vertex_count == 0u || draw->stride != (u32)sizeof(MeshVertex) ||
        !rhi_handle_valid(gpu->vertex)) return false;
    return draw->index_count == 0u || rhi_handle_valid(gpu->index);
}

static bool valid_lighting(const TimeOfDayLighting *lighting) {
    if (!finite_vec3(lighting->sun_dir) || !finite_vec3(lighting->sun_color) ||
        !finite_vec3(lighting->ambient) || !isfinite(lighting->fog) || lighting->fog < 0.0f)
        return false;
    for (u32 i = 0; i < 3u; i++)
        if (lighting->sun_color.e[i] < 0.0f || lighting->ambient.e[i] < 0.0f) return false;
    return vec3_dot(lighting->sun_dir, lighting->sun_dir) > 1.0e-12f;
}

bool world_presenter_create(RHIDevice *dev, WorldPresenter *out) {
    if (out) memset(out, 0, sizeof(*out));
    if (!dev || !out) return false;
    if (!mesh_pipeline_create_lit(dev, &out->object_pipeline, false) ||
        !mesh_pipeline_create_lit(dev, &out->vegetation_pipeline, true)) {
        world_presenter_destroy(dev, out);
        return false;
    }
    u8 white_rgba[4] = {255u, 255u, 255u, 255u};
    RHITextureDesc texture_desc = {1u, 1u, RHI_FORMAT_R8G8B8A8_UNORM, 1u, white_rgba};
    out->white = rhi_texture_create(dev, &texture_desc);
    RHISamplerDesc sampler_desc = {RHI_FILTER_NEAREST, RHI_FILTER_NEAREST,
                                   RHI_WRAP_REPEAT, RHI_WRAP_REPEAT, RHI_WRAP_REPEAT};
    out->sampler = rhi_sampler_create(dev, &sampler_desc);
    RHIBufferDesc instance_desc = {RHI_BUFFER_USAGE_TEXEL,
                                   WORLD_PRESENT_MAX_INSTANCES * sizeof(WorldInstanceSnapshot), NULL};
    out->instances = rhi_buffer_create(dev, &instance_desc);
    if (!rhi_handle_valid(out->white) || !rhi_handle_valid(out->sampler) ||
        !rhi_handle_valid(out->instances)) {
        world_presenter_destroy(dev, out);
        return false;
    }
    out->ready = true;
    return true;
}

void world_presenter_destroy(RHIDevice *dev, WorldPresenter *presenter) {
    if (!dev || !presenter) return;
    if (rhi_handle_valid(presenter->instances)) rhi_buffer_destroy(dev, presenter->instances);
    if (rhi_handle_valid(presenter->sampler)) rhi_sampler_destroy(dev, presenter->sampler);
    if (rhi_handle_valid(presenter->white)) rhi_texture_destroy(dev, presenter->white);
    mesh_pipeline_destroy(dev, &presenter->vegetation_pipeline);
    mesh_pipeline_destroy(dev, &presenter->object_pipeline);
    memset(presenter, 0, sizeof(*presenter));
}

static WorldPresentationStatus validate_snapshot(const WorldFrameSnapshot *snapshot) {
    if (snapshot->draw_count > WORLD_PRESENT_MAX_OBJECTS ||
        snapshot->instance_count > WORLD_PRESENT_MAX_INSTANCES ||
        snapshot->prototype_count > WORLD_PRESENT_MAX_PROTOTYPES ||
        snapshot->batch_count > WORLD_PRESENT_MAX_BATCHES) return WORLD_PRESENTATION_OVERLOAD;
    if (snapshot->frame_id == 0u || !finite_mat4(snapshot->view) ||
        !finite_mat4(snapshot->projection) || !finite_vec3(snapshot->camera) ||
        !valid_lighting(&snapshot->lighting)) return WORLD_PRESENTATION_INVALID;
    for (u32 i = 0; i < snapshot->draw_count; i++) {
        const WorldDrawSnapshot *draw = &snapshot->draws[i];
        if (!valid_draw(&draw->gpu, &draw->draw) || !valid_material(&draw->material))
            return WORLD_PRESENTATION_INVALID;
    }
    for (u32 p = 0; p < snapshot->prototype_count; p++) {
        const WorldVegetationPrototype *prototype = &snapshot->prototypes[p];
        if (prototype->lod_count == 0u || prototype->lod_count > WORLD_PRESENT_MAX_LODS ||
            !valid_material(&prototype->material)) return WORLD_PRESENTATION_INVALID;
        for (u32 l = 0; l < prototype->lod_count; l++)
            if (!valid_draw(&prototype->gpu[l], &prototype->draws[l])) return WORLD_PRESENTATION_INVALID;
    }
    u32 cursor = 0u;
    for (u32 i = 0; i < snapshot->batch_count; i++) {
        const WorldInstanceBatch *batch = &snapshot->batches[i];
        if (batch->prototype >= snapshot->prototype_count || batch->count == 0u ||
            batch->first != cursor || batch->count > snapshot->instance_count - cursor)
            return WORLD_PRESENTATION_INVALID;
        const WorldVegetationPrototype *prototype = &snapshot->prototypes[batch->prototype];
        if (batch->lod >= prototype->lod_count) return WORLD_PRESENTATION_INVALID;
        cursor += batch->count;
    }
    if (cursor != snapshot->instance_count) return WORLD_PRESENTATION_INVALID;
    for (u32 i = 0; i < snapshot->instance_count; i++)
        if (!finite_mat4(snapshot->instances[i].model)) return WORLD_PRESENTATION_INVALID;
    return WORLD_PRESENTATION_OK;
}

WorldPresentationStatus world_presenter_submit(RHICmdBuffer *cmd,
                                                WorldPresenter *presenter,
                                                const WorldFrameSnapshot *snapshot,
                                                WorldSubmitStats *out_stats) {
    if (!cmd || !presenter || !presenter->ready || !snapshot) return WORLD_PRESENTATION_INVALID;
    WorldPresentationStatus status = validate_snapshot(snapshot);
    if (status != WORLD_PRESENTATION_OK) return status;

    WorldSubmitStats stats = {0};
    if (snapshot->draw_count > 0u) {
        rhi_cmd_bind_pipeline(cmd, presenter->object_pipeline.pipeline);
        mesh_pipeline_bind_frame(cmd, &presenter->object_pipeline, &snapshot->view,
                                 &snapshot->projection, &snapshot->lighting, snapshot->camera);
        for (u32 i = 0; i < snapshot->draw_count; i++) {
            const WorldDrawSnapshot *draw = &snapshot->draws[i];
            mesh_pipeline_bind_material(cmd, &presenter->object_pipeline, &draw->material,
                                        presenter->white, presenter->sampler);
            mesh_gpu_draw_desc(cmd, &draw->gpu, &draw->draw, 1u);
            stats.object_draws++;
            if (draw->stream) stats.stream_draws++;
        }
    }
    if (snapshot->instance_count > 0u) {
        rhi_cmd_update_buffer(cmd, presenter->instances, 0u, snapshot->instances,
                              snapshot->instance_count * sizeof(WorldInstanceSnapshot));
        rhi_cmd_bind_pipeline(cmd, presenter->vegetation_pipeline.pipeline);
        mesh_pipeline_bind_frame(cmd, &presenter->vegetation_pipeline, &snapshot->view,
                                 &snapshot->projection, &snapshot->lighting, snapshot->camera);
        rhi_cmd_bind_texel_buffers(cmd, presenter->instances, RHI_HANDLE_NULL);
        for (u32 i = 0; i < snapshot->batch_count; i++) {
            const WorldInstanceBatch *batch = &snapshot->batches[i];
            const WorldVegetationPrototype *prototype = &snapshot->prototypes[batch->prototype];
            mesh_pipeline_bind_material(cmd, &presenter->vegetation_pipeline, &prototype->material,
                                        presenter->white, presenter->sampler);
            mesh_pipeline_set_instance_offset(cmd, &presenter->vegetation_pipeline, batch->first);
            mesh_gpu_draw_desc(cmd, &prototype->gpu[batch->lod], &prototype->draws[batch->lod],
                               batch->count);
            stats.instance_batches++;
            stats.instance_count += batch->count;
        }
    }
    if (out_stats) *out_stats = stats;
    return WORLD_PRESENTATION_OK;
}
