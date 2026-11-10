#include <animation/anim_compression.h>
#include <game/break_flow.h>
#include <math/math.h>
#include <platform/platform_fs.h>
#include <scene/scene_serial.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define GAME_LEVEL_ENTITIES 7u
#define GAME_LEVEL_MATERIALS 7u
#define GAME_CUBE_VERTICES 24u
#define GAME_CUBE_INDICES 36u
#define GAME_WAV_SAMPLES 4410u
#define GAME_WAV_BYTES (44u + GAME_WAV_SAMPLES * 2u)

static const char *const k_class_names[GAME_LEVEL_ENTITIES] = {
    "Ground", "Player", "Enemy", "DynamicWall", "Vehicle",
    "VisibleColor", "HiddenColor"
};

static void put16(u8 *p, u16 value) {
    p[0] = (u8)value;
    p[1] = (u8)(value >> 8);
}

static void put32(u8 *p, u32 value) {
    p[0] = (u8)value;
    p[1] = (u8)(value >> 8);
    p[2] = (u8)(value >> 16);
    p[3] = (u8)(value >> 24);
}

static bool output_path(char out[PLATFORM_FS_PATH_CAPACITY], const char *output,
                        const char *name) {
    int written = snprintf(out, PLATFORM_FS_PATH_CAPACITY, "%s/%s", output, name);
    return written > 0 && (usize)written < PLATFORM_FS_PATH_CAPACITY;
}

static bool atomic_write(const char *path, const void *data, usize size) {
    PlatformAtomicWriter *writer = platform_atomic_writer_open(path);
    if (!writer) return false;
    if (!platform_atomic_writer_write(writer, data, size)) {
        platform_atomic_writer_abort(writer);
        return false;
    }
    return platform_atomic_writer_commit(writer);
}

static bool atomic_write_named(const char *output, const char *name,
                               const void *data, usize size) {
    char path[PLATFORM_FS_PATH_CAPACITY];
    return output_path(path, output, name) && atomic_write(path, data, size);
}

static bool commit_scene_file(const char *temporary, const char *final_path) {
    u64 size = 0;
    bool ok = scene_probe_binary(temporary) && platform_file_size(temporary, &size) &&
              size > 0u && size <= (u64)BSCN_MAX_FILE_BYTES;
    u8 *bytes = NULL;
    if (ok) {
        bytes = (u8 *)malloc((usize)size);
        ok = bytes != NULL;
    }
    if (ok) {
        FILE *fp = fopen(temporary, "rb");
        if (!fp) {
            ok = false;
        } else {
            usize got = fread(bytes, 1, (usize)size, fp);
            int extra = fgetc(fp);
            ok = got == (usize)size && extra == EOF;
            if (fclose(fp) != 0) ok = false;
        }
    }
    if (ok) ok = atomic_write(final_path, bytes, (usize)size);
    free(bytes);
    if (remove(temporary) != 0) ok = false;
    return ok;
}

static bool read_cpu_geometry(void *user, const Mesh *mesh, u32 mesh_index,
                              void *dst_vertices, usize vertex_bytes,
                              void *dst_indices, usize index_bytes) {
    const Scene *scene = (const Scene *)user;
    if (!scene || !mesh || mesh_index >= scene->mesh_geometry_count) return false;
    const SceneMeshGeometry *geometry = &scene->mesh_geometry[mesh_index];
    if (geometry->mesh_index != mesh_index || geometry->vertex_count != mesh->vertex_count ||
        geometry->index_count != mesh->index_count ||
        vertex_bytes != (usize)mesh->vertex_count * BSCN_MESH_VERTEX_STRIDE ||
        index_bytes != (usize)mesh->index_count * sizeof(u32) ||
        (vertex_bytes > 0u && !dst_vertices) || (index_bytes > 0u && !dst_indices))
        return false;
    if (vertex_bytes > 0u) memcpy(dst_vertices, geometry->vertices, vertex_bytes);
    if (index_bytes > 0u) memcpy(dst_indices, geometry->indices, index_bytes);
    return true;
}

static void make_cube(SceneMeshGeometry *geometry, f32 vertices[GAME_CUBE_VERTICES * 8u],
                      u32 indices[GAME_CUBE_INDICES]) {
    static const f32 corners[6][4][3] = {
        {{-1, -1,  1}, { 1, -1,  1}, { 1,  1,  1}, {-1,  1,  1}},
        {{ 1, -1, -1}, {-1, -1, -1}, {-1,  1, -1}, { 1,  1, -1}},
        {{-1,  1,  1}, { 1,  1,  1}, { 1,  1, -1}, {-1,  1, -1}},
        {{-1, -1, -1}, { 1, -1, -1}, { 1, -1,  1}, {-1, -1,  1}},
        {{ 1, -1,  1}, { 1, -1, -1}, { 1,  1, -1}, { 1,  1,  1}},
        {{-1, -1, -1}, {-1, -1,  1}, {-1,  1,  1}, {-1,  1, -1}}
    };
    static const f32 normals[6][3] = {
        {0, 0, 1}, {0, 0, -1}, {0, 1, 0},
        {0, -1, 0}, {1, 0, 0}, {-1, 0, 0}
    };
    static const f32 uv[4][2] = {{0, 0}, {1, 0}, {1, 1}, {0, 1}};
    for (u32 face = 0; face < 6u; ++face) {
        for (u32 corner = 0; corner < 4u; ++corner) {
            u32 vertex = face * 4u + corner;
            f32 *dst = vertices + vertex * 8u;
            dst[0] = corners[face][corner][0];
            dst[1] = corners[face][corner][1];
            dst[2] = corners[face][corner][2];
            dst[3] = normals[face][0];
            dst[4] = normals[face][1];
            dst[5] = normals[face][2];
            dst[6] = uv[corner][0];
            dst[7] = uv[corner][1];
        }
        u32 base = face * 4u;
        u32 *dst = indices + face * 6u;
        dst[0] = base;
        dst[1] = base + 1u;
        dst[2] = base + 2u;
        dst[3] = base;
        dst[4] = base + 2u;
        dst[5] = base + 3u;
    }
    geometry->mesh_index = 0u;
    geometry->vertex_count = GAME_CUBE_VERTICES;
    geometry->index_count = GAME_CUBE_INDICES;
    geometry->vertices = (u8 *)vertices;
    geometry->indices = indices;
}

static bool bake_scene(const char *output) {
    static f32 vertices[GAME_CUBE_VERTICES * 8u];
    static u32 indices[GAME_CUBE_INDICES];
    SceneMeshGeometry geometry;
    memset(&geometry, 0, sizeof(geometry));
    make_cube(&geometry, vertices, indices);

    bool ok = false;
    World *world = world_create();
    Scene scene;
    memset(&scene, 0, sizeof(scene));
    char temporary[PLATFORM_FS_PATH_CAPACITY];
    char final_path[PLATFORM_FS_PATH_CAPACITY];
    temporary[0] = '\0';
    if (!world) goto cleanup;
    scene.meshes = (Mesh *)calloc(1u, sizeof(Mesh));
    scene.materials = (Material *)calloc(GAME_LEVEL_MATERIALS, sizeof(Material));
    scene.nodes = (SceneNode *)calloc(GAME_LEVEL_ENTITIES, sizeof(SceneNode));
    if (!scene.meshes || !scene.materials || !scene.nodes) goto cleanup;
    scene.mesh_count = 1u;
    scene.material_count = GAME_LEVEL_MATERIALS;
    scene.node_count = GAME_LEVEL_ENTITIES;
    scene.mesh_geometry = &geometry;
    scene.mesh_geometry_count = 1u;
    scene.meshes[0].vertex_count = GAME_CUBE_VERTICES;
    scene.meshes[0].index_count = GAME_CUBE_INDICES;
    scene.meshes[0].aabb_min = vec3(-1.0f, -1.0f, -1.0f);
    scene.meshes[0].aabb_max = vec3(1.0f, 1.0f, 1.0f);

    static const f32 colors[GAME_LEVEL_MATERIALS][4] = {
        {0.18f, 0.20f, 0.22f, 1.0f}, {0.10f, 0.50f, 0.90f, 1.0f},
        {0.90f, 0.10f, 0.10f, 1.0f}, {0.50f, 0.50f, 0.50f, 1.0f},
        {0.90f, 0.70f, 0.10f, 1.0f}, {1.00f, 0.25f, 0.05f, 1.0f},
        {0.10f, 0.20f, 0.90f, 1.0f}
    };
    static const f32 positions[GAME_LEVEL_ENTITIES][3] = {
        {0, -0.5f, 0}, {0, 1, 0}, {4, 1, 4}, {0, 1, 6},
        {-4, 0.75f, 2}, {2, 0.5f, -2}, {-2, 0.5f, -2}
    };
    static const f32 scales[GAME_LEVEL_ENTITIES][3] = {
        {16, 0.5f, 16}, {0.4f, 1, 0.4f}, {0.4f, 1, 0.4f},
        {2, 1, 0.25f}, {1.5f, 0.75f, 2.5f},
        {0.5f, 0.5f, 0.5f}, {0.5f, 0.5f, 0.5f}
    };
    world_register_component(world, 1u, sizeof(f32) * 3u);
    world_register_component(world, 3u, sizeof(u32));
    for (u32 i = 0; i < GAME_LEVEL_ENTITIES; ++i) {
        memcpy(scene.materials[i].base_color, colors[i], sizeof(colors[i]));
        scene.materials[i].roughness_factor = 0.8f;
        scene.materials[i].alpha_cutoff = 0.5f;
        scene.materials[i].occlusion_strength = 1.0f;
        scene.materials[i].alpha_mode = ALPHA_OPAQUE;

        SceneNode *node = &scene.nodes[i];
        node->local_transform = mat4_mul(
            mat4_translation(positions[i][0], positions[i][1], positions[i][2]),
            mat4_scaling(scales[i][0], scales[i][1], scales[i][2]));
        node->world_transform = node->local_transform;
        node->parent_index = UINT32_MAX;
        node->mesh_index = 0u;
        node->material_idx = i;
        node->skin_mesh_index = UINT32_MAX;
        node->has_mesh = i != 6u;
        node->skinned = false;

        Entity entity = world_create_entity(world);
        if (!entity_valid(entity) || entity.index != i + 1u) goto cleanup;
        f32 *transform = (f32 *)world_add_component(world, entity, 1u);
        u32 *mesh = (u32 *)world_add_component(world, entity, 3u);
        if (!transform || !mesh) goto cleanup;
        memcpy(transform, positions[i], sizeof(f32) * 3u);
        *mesh = 0u;
    }
    if (!output_path(temporary, output, ".level.bscn.bake-tmp") ||
        !output_path(final_path, output, "level.bscn"))
        goto cleanup;
    SerializeOptions options;
    memset(&options, 0, sizeof(options));
    options.include_resources = true;
    options.read_mesh_geometry = read_cpu_geometry;
    options.read_mesh_geometry_user = &scene;
    if (!scene_save_binary(world, &scene, temporary, &options)) goto cleanup;
    ok = commit_scene_file(temporary, final_path);

cleanup:
    if (temporary[0] != '\0') (void)remove(temporary);
    free(scene.nodes);
    free(scene.materials);
    free(scene.meshes);
    if (world) world_destroy(world);
    return ok;
}

static bool bake_sidecar(const char *output) {
    char text[1024];
    usize offset = 0;
    for (u32 i = 0; i < GAME_LEVEL_ENTITIES; ++i) {
        int written = snprintf(text + offset, sizeof(text) - offset, "%u %s\n",
                               i + 1u, k_class_names[i]);
        if (written < 0 || (usize)written >= sizeof(text) - offset) return false;
        offset += (usize)written;
    }
    return atomic_write_named(output, "actors.sidecar", text, offset);
}

static bool bake_flow(const char *output) {
    BreakFlowConfig config = {3u, 2u};
    BreakFlowGraph *graph = break_flow_graph_create(&config);
    u8 *bytes = NULL;
    bool ok = false;
    if (!graph) return false;
    BreakFlowNodeDesc desc;
    memset(&desc, 0, sizeof(desc));
    u32 enter = 0, delay = 0, add_item = 0, link = 0;
    desc.type = BREAK_FLOW_NODE_EVENT;
    desc.event_key = 1u;
    strcpy(desc.name, "enter");
    if (break_flow_node_add(graph, &desc, &enter) != BREAK_FLOW_OK) goto cleanup;
    memset(&desc, 0, sizeof(desc));
    desc.type = BREAK_FLOW_NODE_DELAY;
    desc.delay_ticks = 30u;
    strcpy(desc.name, "delay");
    if (break_flow_node_add(graph, &desc, &delay) != BREAK_FLOW_OK) goto cleanup;
    memset(&desc, 0, sizeof(desc));
    desc.type = BREAK_FLOW_NODE_ENTITY_ADD_ITEM;
    desc.entity = (Entity){2u, 1u};
    desc.item_id = 1u;
    strcpy(desc.name, "add-item");
    if (break_flow_node_add(graph, &desc, &add_item) != BREAK_FLOW_OK) goto cleanup;
    BreakFlowLinkDesc edge = {BREAK_FLOW_PORT_EXEC, enter,
                              BREAK_FLOW_EVENT_EXEC_OUT, delay, BREAK_FLOW_EXEC_IN};
    if (break_flow_link_add(graph, &edge, &link) != BREAK_FLOW_OK) goto cleanup;
    edge.source_node = delay;
    edge.source_port = BREAK_FLOW_DELAY_EXEC_OUT;
    edge.target_node = add_item;
    if (break_flow_link_add(graph, &edge, &link) != BREAK_FLOW_OK) goto cleanup;

    usize required = 0;
    if (break_flow_serialized_size(graph, &required) != BREAK_FLOW_OK || required > 4096u)
        goto cleanup;
    bytes = (u8 *)malloc(required);
    if (!bytes) goto cleanup;
    usize written = 0;
    if (break_flow_serialize(graph, bytes, required, &written) != BREAK_FLOW_OK ||
        written != required)
        goto cleanup;
    ok = atomic_write_named(output, "level.fg", bytes, written);

cleanup:
    free(bytes);
    break_flow_graph_destroy(graph);
    return ok;
}

static bool bake_animation(const char *output) {
    static AnimClip clip;
    static u8 encoded[ANIM_CODEC_MAX_BYTES];
    static const f32 times[3] = {0.0f, 0.5f, 1.0f};
    static const f32 translation[3][4] = {
        {0.0f, 0.0f, 0.0f, 0.0f}, {1.0f, 2.0f, 3.0f, 0.0f},
        {2.0f, 0.0f, -1.0f, 0.0f}
    };
    static const f32 rotation[3][4] = {
        {0.0f, 0.0f, 0.0f, 1.0f}, {0.0f, 0.6f, 0.0f, 0.8f},
        {0.0f, 0.0f, 0.0f, 1.0f}
    };
    static const f32 scale[3][4] = {
        {1.0f, 1.0f, 1.0f, 0.0f}, {2.0f, 3.0f, 4.0f, 0.0f},
        {1.0f, 1.0f, 1.0f, 0.0f}
    };
    memset(&clip, 0, sizeof(clip));
    clip.duration = 1.0f;
    clip.loop = true;
    clip.playing = false;
    clip.channel_count = 3u;
    const f32 (*values[3])[4] = {translation, rotation, scale};
    for (u32 c = 0; c < 3u; ++c) {
        AnimChannel *channel = &clip.channels[c];
        channel->joint_index = c;
        channel->path = (AnimPathType)c;
        channel->interp = ANIM_INTERP_LINEAR;
        channel->keyframe_count = 3u;
        memcpy(channel->times, times, sizeof(times));
        memcpy(channel->values, values[c], sizeof(f32) * 12u);
    }
    usize required = 0, written = 0;
    if (anim_codec_encoded_size(&clip, 3u, &required) != ANIM_CODEC_OK ||
        required > sizeof(encoded) ||
        anim_codec_encode(&clip, 3u, encoded, sizeof(encoded), &written) != ANIM_CODEC_OK ||
        written != required)
        return false;
    return atomic_write_named(output, "level.banm", encoded, written);
}

static bool bake_wav(const char *output) {
    u8 wav[GAME_WAV_BYTES];
    memset(wav, 0, sizeof(wav));
    memcpy(wav, "RIFF", 4);
    put32(wav + 4, (u32)sizeof(wav) - 8u);
    memcpy(wav + 8, "WAVEfmt ", 8);
    put32(wav + 16, 16u);
    put16(wav + 20, 1u);
    put16(wav + 22, 1u);
    put32(wav + 24, 44100u);
    put32(wav + 28, 88200u);
    put16(wav + 32, 2u);
    put16(wav + 34, 16u);
    memcpy(wav + 36, "data", 4);
    put32(wav + 40, GAME_WAV_SAMPLES * 2u);
    u32 seed = 0xC0FFEE12u;
    for (u32 i = 0; i < GAME_WAV_SAMPLES; ++i) {
        seed ^= seed << 13;
        seed ^= seed >> 17;
        seed ^= seed << 5;
        i32 sample = (i % 100u < 50u) ? 8192 : -8192;
        sample += (i32)(seed & 3u) - 1;
        put16(wav + 44u + i * 2u, (u16)(i16)sample);
    }
    return atomic_write_named(output, "tone.wav", wav, sizeof(wav));
}

static bool bake_text_assets(const char *output) {
    static const struct {
        const char *name;
        const char *text;
    } assets[] = {
        {"director.lua",
         "function on_enter()\n"
         "    return 30, 1\n"
         "end\n"},
        {"player.lua",
         "function on_spawn()\n"
         "    return true\n"
         "end\n"},
        {"broken.lua",
         "function broken(\n"
         "    this is not valid Lua\n"
         "end\n"},
        {"deterministic.scenario",
         "game-app-scenario 1\n"
         "seed 12648430\n"
         "fixed-dt-ns 16666667\n"
         "frame 0 enter 1\n"
         "frame 30 add-item 1\n"
         "frame 60 checkpoint 1\n"
         "frame 120 end\n"},
        {"load_unload.scenario",
         "game-app-scenario 1\n"
         "seed 12648430\n"
         "fixed-dt-ns 16666667\n"
         "frame 1 load\n"
         "frame 2 unload\n"
         "frame 3 load\n"
         "frame 4 unload\n"
         "frame 5 end\n"},
        {"rollback.scenario",
         "game-app-scenario 1\n"
         "seed 12648430\n"
         "fixed-dt-ns 16666667\n"
         "frame 1 checkpoint 7\n"
         "frame 2 add-item 1\n"
         "frame 3 restore 7\n"
         "frame 4 end\n"}
    };
    for (usize i = 0; i < sizeof(assets) / sizeof(assets[0]); ++i) {
        if (!atomic_write_named(output, assets[i].name, assets[i].text,
                                strlen(assets[i].text)))
            return false;
    }
    return true;
}

int main(int argc, char **argv) {
    const char *output = NULL;
    if (argc == 2 && strcmp(argv[1], "--help") == 0) {
        puts("Usage: game_asset_bake --output DIR");
        return 0;
    }
    if (argc == 3 && strcmp(argv[1], "--output") == 0 && argv[2][0] != '\0')
        output = argv[2];
    if (!output) {
        fputs("Usage: game_asset_bake --output DIR\n", stderr);
        return 2;
    }
    if (!platform_mkdir(output)) {
        fputs("game_asset_bake: cannot create output directory\n", stderr);
        return 1;
    }
    if (!bake_scene(output) || !bake_sidecar(output) || !bake_flow(output) ||
        !bake_animation(output) || !bake_wav(output) || !bake_text_assets(output)) {
        fputs("game_asset_bake: asset generation failed\n", stderr);
        return 1;
    }
    return 0;
}
