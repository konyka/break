#include <renderer/world_presentation.h>
#include <math.h>
#include <string.h>

static bool finite_float(f32 value) {
    return isfinite(value) != 0;
}

static bool finite_vec3(Vec3 value) {
    return finite_float(value.e[0]) && finite_float(value.e[1]) && finite_float(value.e[2]);
}

static bool nonnegative_vec3(Vec3 value) {
    return finite_vec3(value) && value.e[0] >= 0.0f && value.e[1] >= 0.0f && value.e[2] >= 0.0f;
}

static bool finite_mat4(Mat4 value) {
    for (u32 r = 0; r < 4u; r++)
        for (u32 c = 0; c < 4u; c++)
            if (!finite_float(value.e[r][c])) return false;
    return true;
}

static bool valid_material(const MeshMaterial *material) {
    if (!material || !nonnegative_vec3(material->base_color) ||
        !finite_float(material->roughness) || material->roughness < 0.0f ||
        material->roughness > 1.0f) return false;
    bool texture = rhi_handle_valid(material->albedo);
    bool sampler = rhi_handle_valid(material->sampler);
    return texture == sampler;
}

static bool valid_draw(const MeshGpu *gpu, const MeshDrawDesc *draw) {
    if (!gpu || !draw || draw->vertex_count == 0u ||
        draw->stride != (u32)sizeof(MeshVertex) || !rhi_handle_valid(gpu->vertex)) return false;
    return draw->index_count == 0u || rhi_handle_valid(gpu->index);
}

static bool valid_lighting(const TimeOfDayLighting *lighting) {
    if (!lighting || !finite_vec3(lighting->sun_dir) ||
        !nonnegative_vec3(lighting->sun_color) || !nonnegative_vec3(lighting->ambient) ||
        !finite_float(lighting->fog) || lighting->fog < 0.0f) return false;
    f32 length_sq = vec3_dot(lighting->sun_dir, lighting->sun_dir);
    return finite_float(length_sq) && length_sq > 1.0e-12f;
}

static bool visible_id(u32 id, const u32 *ids, u32 count) {
    for (u32 i = 0; i < count; i++)
        if (ids[i] == id) return true;
    return false;
}

WorldPresentationStatus world_presentation_snapshot(const WorldPresentationInput *input,
                                                     WorldFrameSnapshot *out) {
    if (!input || !out || input->frame_id == 0u) return WORLD_PRESENTATION_INVALID;
    if (input->object_count > WORLD_PRESENT_MAX_OBJECTS) return WORLD_PRESENTATION_OVERLOAD;
    if (input->object_count > 0u && !input->objects) return WORLD_PRESENTATION_INVALID;
    if (!finite_mat4(input->view) || !finite_mat4(input->projection) ||
        !finite_vec3(input->camera) || !finite_float(input->fov) || input->fov <= 0.0f ||
        !finite_float(input->screen_height) || input->screen_height <= 0.0f ||
        !finite_float(input->pixel_error) || input->pixel_error <= 0.0f ||
        !valid_lighting(&input->lighting)) return WORLD_PRESENTATION_INVALID;

    for (u32 i = 0; i < input->object_count; i++) {
        const WorldObject *object = &input->objects[i];
        if (!valid_draw(&object->gpu, &object->draw) || !valid_material(&object->material))
            return WORLD_PRESENTATION_INVALID;
        for (u32 j = 0; j < i; j++)
            if (input->objects[j].id == object->id) return WORLD_PRESENTATION_INVALID;
    }

    u32 vegetation_count = input->vegetation ? input->vegetation->count : 0u;
    if (vegetation_count > WORLD_PRESENT_MAX_INSTANCES ||
        input->prototype_count > WORLD_PRESENT_MAX_PROTOTYPES) return WORLD_PRESENTATION_OVERLOAD;
    if (input->prototype_count > 0u && !input->prototypes) return WORLD_PRESENTATION_INVALID;
    if (input->vegetation) {
        const VegetationBuild *build = input->vegetation;
        if (build->count > build->capacity || (build->count > 0u && !build->instances))
            return WORLD_PRESENTATION_INVALID;
        if (build->dropped > 0u) return WORLD_PRESENTATION_OVERLOAD;
    }
    if (vegetation_count > 0u && !input->vegetation) return WORLD_PRESENTATION_INVALID;
    if (input->lod_state && (!input->lod_state->level || !input->lod_state->tag ||
                             input->lod_state->capacity < vegetation_count))
        return WORLD_PRESENTATION_INVALID;

    for (u32 p = 0; p < input->prototype_count; p++) {
        const WorldVegetationPrototype *prototype = &input->prototypes[p];
        if (prototype->lod_count == 0u || prototype->lod_count > WORLD_PRESENT_MAX_LODS ||
            !valid_material(&prototype->material) || !finite_float(prototype->bounding_radius) ||
            prototype->bounding_radius < 0.0f) return WORLD_PRESENTATION_INVALID;
        for (u32 l = 0; l < prototype->lod_count; l++) {
            if (!valid_draw(&prototype->gpu[l], &prototype->draws[l]) ||
                !finite_float(prototype->errors[l]) || prototype->errors[l] < 0.0f ||
                (l > 0u && prototype->errors[l] < prototype->errors[l - 1u]))
                return WORLD_PRESENTATION_INVALID;
        }
    }
    for (u32 i = 0; i < vegetation_count; i++) {
        const VegetationInstance *instance = &input->vegetation->instances[i];
        if (instance->prototype >= input->prototype_count || !finite_vec3(instance->position))
            return WORLD_PRESENTATION_INVALID;
    }

    u32 visible[WORLD_PRESENT_MAX_OBJECTS];
    u32 visible_count = input->object_count;
    if (input->visibility) {
        const VisQuery *query = input->visibility;
        if (query->room_count > VISAREA_MAX_ROOMS ||
            query->outdoor_count > WORLD_PRESENT_MAX_OBJECTS) return WORLD_PRESENTATION_OVERLOAD;
        if ((query->room_count > 0u && !query->rooms) ||
            (query->outdoor_count > 0u && !query->outdoor_ids)) return WORLD_PRESENTATION_INVALID;
        for (u32 i = 0; i < query->room_count; i++) {
            const VisRoom *room = &query->rooms[i];
            if (room->object_count > VISAREA_MAX_OBJECTS || room->portal_count > 8u)
                return WORLD_PRESENTATION_OVERLOAD;
            if (room->object_count > 0u && !room->object_ids) return WORLD_PRESENTATION_INVALID;
        }
        VisRoom empty_room;
        VisQuery safe_query = *query;
        if (safe_query.room_count == 0u && !safe_query.rooms) safe_query.rooms = &empty_room;
        u32 dropped = 0u;
        visible_count = visarea_visible(&safe_query, visible,
                                        WORLD_PRESENT_MAX_OBJECTS, &dropped);
        if (dropped > 0u || visible_count > WORLD_PRESENT_MAX_OBJECTS)
            return WORLD_PRESENTATION_OVERLOAD;
    }

    u32 instance_mesh[WORLD_PRESENT_MAX_INSTANCES];
    u32 instance_order[WORLD_PRESENT_MAX_INSTANCES];
    u32 bucket_offsets[WORLD_PRESENT_MAX_BATCHES + 1u];
    u8 instance_level[WORLD_PRESENT_MAX_INSTANCES];
    f32 projection_factor = lod_screen_proj_factor(input->fov, input->screen_height);
    for (u32 i = 0; i < vegetation_count; i++) {
        const VegetationInstance *instance = &input->vegetation->instances[i];
        const WorldVegetationPrototype *prototype = &input->prototypes[instance->prototype];
        Vec3 delta = vec3_sub(instance->position, input->camera);
        f32 distance = vec3_len(delta) - prototype->bounding_radius;
        instance_mesh[i] = instance->prototype;
        instance_level[i] = (u8)lod_instance_select(input->lod_state, i, instance->prototype + 1u,
                                                    prototype->errors, prototype->lod_count,
                                                    distance, projection_factor,
                                                    input->pixel_error, NULL);
    }
    memset(bucket_offsets, 0, sizeof(bucket_offsets));
    if (vegetation_count > 0u) {
        u32 levels = 0u;
        for (u32 p = 0; p < input->prototype_count; p++)
            if (input->prototypes[p].lod_count > levels) levels = input->prototypes[p].lod_count;
        if (levels == 0u) return WORLD_PRESENTATION_INVALID;
        /* Use the fixed global LOD bucket width so batches can address every
         * prototype's levels without truncating prototypes with fewer levels. */
        u32 kept = lod_bucket_instances(instance_mesh, instance_level, vegetation_count,
                                        input->prototype_count, WORLD_PRESENT_MAX_LODS,
                                        bucket_offsets, instance_order);
        if (kept != vegetation_count) return WORLD_PRESENTATION_INVALID;
    }

    memset(out, 0, sizeof(*out));
    out->frame_id = input->frame_id;
    out->view = input->view;
    out->projection = input->projection;
    out->camera = input->camera;
    out->lighting = input->lighting;
    out->prototype_count = input->prototype_count;
    for (u32 p = 0; p < input->prototype_count; p++) out->prototypes[p] = input->prototypes[p];
    for (u32 i = 0; i < input->object_count; i++) {
        const WorldObject *object = &input->objects[i];
        if (input->visibility && !visible_id(object->id, visible, visible_count)) continue;
        WorldDrawSnapshot *draw = &out->draws[out->draw_count++];
        draw->object_id = object->id;
        draw->gpu = object->gpu;
        draw->draw = object->draw;
        draw->material = object->material;
        draw->stream = object->stream;
    }
    for (u32 p = 0; p < input->prototype_count; p++) {
        for (u32 l = 0; l < WORLD_PRESENT_MAX_LODS; l++) {
            u32 bucket = p * WORLD_PRESENT_MAX_LODS + l;
            u32 first = bucket_offsets[bucket];
            u32 count = bucket_offsets[bucket + 1u] - first;
            if (count == 0u) continue;
            WorldInstanceBatch *batch = &out->batches[out->batch_count++];
            batch->prototype = p;
            batch->lod = l;
            batch->first = out->instance_count;
            batch->count = count;
            for (u32 j = 0; j < count; j++) {
                u32 source = instance_order[first + j];
                out->instances[out->instance_count++].model =
                    mat4_translation(input->vegetation->instances[source].position.e[0],
                                     input->vegetation->instances[source].position.e[1],
                                     input->vegetation->instances[source].position.e[2]);
            }
        }
    }
    return WORLD_PRESENTATION_OK;
}

bool world_presentation_stream_mesh(const StreamTileData *tile, Vec3 translation,
                                    MeshBuffer *out) {
    if (!tile || !out || tile->vertex_count == 0u ||
        tile->vertex_count > STREAM_TILE_MAX_VERTS || !finite_vec3(translation)) return false;
    for (u32 i = 0; i < tile->vertex_count; i++) {
        const MeshStageVertex *vertex = &tile->verts[i];
        if (!finite_float(vertex->px) || !finite_float(vertex->py) || !finite_float(vertex->pz) ||
            !finite_float(vertex->nx) || !finite_float(vertex->ny) || !finite_float(vertex->nz) ||
            !finite_float(vertex->px + translation.e[0]) ||
            !finite_float(vertex->py + translation.e[1]) ||
            !finite_float(vertex->pz + translation.e[2])) return false;
    }
    if (!mesh_buffer_from_legacy(out, tile->verts, tile->vertex_count, NULL)) return false;
    for (u32 i = 0; i < out->count; i++) {
        out->verts[i].px += translation.e[0];
        out->verts[i].py += translation.e[1];
        out->verts[i].pz += translation.e[2];
    }
    return true;
}
