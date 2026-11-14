#include <animation/anim_compression.h>
#include <kernel/break_flow.h>
#include <math/math.h>
#include <platform/platform_fs.h>
#include <scene/scene_serial.h>

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if defined(_WIN32)
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>
#endif

#define CORE_APP_LEVEL_ENTITIES 7u
#define CORE_APP_LEVEL_MATERIALS 7u
#define CORE_APP_CUBE_VERTICES 24u
#define CORE_APP_CUBE_INDICES 36u
#define CORE_APP_WAV_SAMPLES 4410u
#define CORE_APP_WAV_BYTES (44u + CORE_APP_WAV_SAMPLES * 2u)

static const char *const k_class_names[CORE_APP_LEVEL_ENTITIES] = {
    "Ground", "User", "Chaser", "DynamicWall", "Vehicle",
    "VisibleColor", "HiddenColor"
};

typedef struct {
    unsigned long os_error;
    int crt_error;
} CoreAppError;

static CoreAppError core_app_os_error(void) {
    CoreAppError error;
    error.crt_error = errno;
#if defined(_WIN32)
    error.os_error = (unsigned long)GetLastError();
#else
    error.os_error = 0;
#endif
    return error;
}

static CoreAppError core_app_crt_error(void) {
    CoreAppError error = {0, errno};
    return error;
}

static void core_app_report_path(const char *stage, const char *step, const char *path,
                                 i64 raw_result, CoreAppError error) {
    fprintf(stderr,
            "FAIL: CORE_APP_BAKE stage=%s step=%s path=%s raw=%lld "
            "os_error=%lu errno=%d\n",
            stage, step, path, (long long)raw_result, error.os_error, error.crt_error);
}

static void core_app_report_scene(const char *stage, const char *step,
                                  const char *temporary, const char *final_path,
                                  i64 raw_result, CoreAppError error) {
    fprintf(stderr,
            "FAIL: CORE_APP_BAKE stage=%s step=%s temporary=%s final=%s raw=%lld "
            "os_error=%lu errno=%d\n",
            stage, step, temporary, final_path, (long long)raw_result,
            error.os_error, error.crt_error);
}

static void core_app_report_read(const char *step, const char *temporary,
                                 const char *final_path, i64 raw_result,
                                 CoreAppError error, usize got, u64 expected,
                                 int extra, int stream_error) {
    fprintf(stderr,
            "FAIL: CORE_APP_BAKE stage=scene.commit step=%s temporary=%s final=%s "
            "raw=%lld os_error=%lu errno=%d got=%llu expected=%llu extra=%d ferror=%d\n",
            step, temporary, final_path, (long long)raw_result, error.os_error,
            error.crt_error, (unsigned long long)got, (unsigned long long)expected,
            extra, stream_error);
}

static void core_app_report_atomic(const char *stage, const char *temporary,
                                   const char *final_path,
                                   const PlatformAtomicWriterDiagnostic *diagnostic) {
    const char *step = diagnostic->step ? diagnostic->step : "unknown";
    fprintf(stderr,
            "FAIL: CORE_APP_BAKE stage=%s step=%s.atomic.%s temporary=%s final=%s "
            "atomic_temporary=%s raw=%lld os_error=%llu errno=%d",
            stage, stage, step, temporary, final_path, diagnostic->temporary_path,
            (long long)diagnostic->raw_result,
            (unsigned long long)diagnostic->os_error, diagnostic->crt_error);
    if (strcmp(step, "write") == 0 || strcmp(step, "WriteFile") == 0)
        fprintf(stderr, " got=%llu expected=%llu",
                (unsigned long long)diagnostic->got,
                (unsigned long long)diagnostic->expected);
    fputc('\n', stderr);
}

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

static bool atomic_write(const char *stage, const char *temporary, const char *path,
                         const void *data, usize size) {
    PlatformAtomicWriterDiagnostic diagnostic;
    PlatformAtomicWriter *writer = platform_atomic_writer_open_diagnostic(path, &diagnostic);
    if (!writer) {
        core_app_report_atomic(stage, temporary, path, &diagnostic);
        return false;
    }
    if (!platform_atomic_writer_write(writer, data, size)) {
        platform_atomic_writer_abort(writer);
        core_app_report_atomic(stage, temporary, path, &diagnostic);
        return false;
    }
    bool result = platform_atomic_writer_commit(writer);
    if (!result) core_app_report_atomic(stage, temporary, path, &diagnostic);
    return result;
}

static bool atomic_write_named(const char *output, const char *name,
                               const void *data, usize size) {
    char path[PLATFORM_FS_PATH_CAPACITY];
    if (!output_path(path, output, name)) {
        core_app_report_path(name, "asset.output_path", output, 0, core_app_crt_error());
        return false;
    }
    return atomic_write(name, "", path, data, size);
}

static bool commit_scene_file(const char *temporary, const char *final_path) {
    u64 size = 0;
    bool ok = scene_probe_binary(temporary);
    if (!ok)
        core_app_report_scene("scene.commit", "scene.commit.probe", temporary, final_path,
                              0, core_app_os_error());
    if (ok) {
        bool size_result = platform_file_size(temporary, &size);
        CoreAppError error = core_app_os_error();
        if (!size_result) {
            core_app_report_scene("scene.commit", "scene.commit.file_size", temporary,
                                  final_path, (i64)size_result, error);
            ok = false;
        }
    }
    if (ok && (size == 0u || size > (u64)BSCN_MAX_FILE_BYTES)) {
        core_app_report_scene("scene.commit", "scene.commit.size", temporary, final_path,
                              0, core_app_crt_error());
        ok = false;
    }
    u8 *bytes = NULL;
    if (ok) {
        bytes = (u8 *)malloc((usize)size);
        if (!bytes) {
            core_app_report_scene("scene.commit", "scene.commit.malloc", temporary,
                                  final_path, 0, core_app_crt_error());
            ok = false;
        }
    }
    if (ok) {
        FILE *fp = fopen(temporary, "rb");
        if (!fp) {
            core_app_report_scene("scene.commit", "scene.commit.fopen", temporary,
                                  final_path, 0, core_app_crt_error());
            ok = false;
        } else {
            usize got = fread(bytes, 1, (usize)size, fp);
            int read_errno = errno;
            int read_ferror = ferror(fp);
            int extra = fgetc(fp);
            int extra_errno = errno;
            int extra_ferror = ferror(fp);
            ok = got == (usize)size && extra == EOF;
            if (!ok) {
                bool short_read = got != (usize)size;
                CoreAppError error = {0, short_read ? read_errno : extra_errno};
                core_app_report_read("scene.commit.read", temporary, final_path,
                                     short_read ? (i64)got : (i64)extra, error, got, size,
                                     extra, short_read ? read_ferror : extra_ferror);
            }
            int close_result = fclose(fp);
            int close_errno = errno;
            if (close_result != 0) {
                CoreAppError error = {0, close_errno};
                core_app_report_scene("scene.commit", "scene.commit.close", temporary,
                                      final_path, (i64)close_result, error);
                ok = false;
            }
        }
    }
    if (ok) ok = atomic_write("scene.commit", temporary, final_path, bytes, (usize)size);
    free(bytes);
    int remove_result = remove(temporary);
    int remove_errno = errno;
    if (remove_result != 0) {
        CoreAppError error = {0, remove_errno};
        core_app_report_scene("scene.commit", "scene.commit.remove", temporary, final_path,
                              (i64)remove_result, error);
        ok = false;
    }
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

static void make_cube(SceneMeshGeometry *geometry, f32 vertices[CORE_APP_CUBE_VERTICES * 8u],
                      u32 indices[CORE_APP_CUBE_INDICES]) {
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
    geometry->vertex_count = CORE_APP_CUBE_VERTICES;
    geometry->index_count = CORE_APP_CUBE_INDICES;
    geometry->vertices = (u8 *)vertices;
    geometry->indices = indices;
}

static bool bake_scene(const char *output) {
    static f32 vertices[CORE_APP_CUBE_VERTICES * 8u];
    static u32 indices[CORE_APP_CUBE_INDICES];
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
    scene.materials = (Material *)calloc(CORE_APP_LEVEL_MATERIALS, sizeof(Material));
    scene.nodes = (SceneNode *)calloc(CORE_APP_LEVEL_ENTITIES, sizeof(SceneNode));
    if (!scene.meshes || !scene.materials || !scene.nodes) goto cleanup;
    scene.mesh_count = 1u;
    scene.material_count = CORE_APP_LEVEL_MATERIALS;
    scene.node_count = CORE_APP_LEVEL_ENTITIES;
    scene.mesh_geometry = &geometry;
    scene.mesh_geometry_count = 1u;
    scene.meshes[0].vertex_count = CORE_APP_CUBE_VERTICES;
    scene.meshes[0].index_count = CORE_APP_CUBE_INDICES;
    scene.meshes[0].aabb_min = vec3(-1.0f, -1.0f, -1.0f);
    scene.meshes[0].aabb_max = vec3(1.0f, 1.0f, 1.0f);

    static const f32 colors[CORE_APP_LEVEL_MATERIALS][4] = {
        {0.18f, 0.20f, 0.22f, 1.0f}, {0.10f, 0.50f, 0.90f, 1.0f},
        {0.90f, 0.10f, 0.10f, 1.0f}, {0.50f, 0.50f, 0.50f, 1.0f},
        {0.90f, 0.70f, 0.10f, 1.0f}, {1.00f, 0.25f, 0.05f, 1.0f},
        {0.10f, 0.20f, 0.90f, 1.0f}
    };
    static const f32 positions[CORE_APP_LEVEL_ENTITIES][3] = {
        {0, -0.5f, 0}, {0, 1, 0}, {4, 1, 4}, {0, 1, 6},
        {-4, 0.75f, 2}, {2, 0.5f, -2}, {-2, 0.5f, -2}
    };
    static const f32 scales[CORE_APP_LEVEL_ENTITIES][3] = {
        {16, 0.5f, 16}, {0.4f, 1, 0.4f}, {0.4f, 1, 0.4f},
        {2, 1, 0.25f}, {1.5f, 0.75f, 2.5f},
        {0.5f, 0.5f, 0.5f}, {0.5f, 0.5f, 0.5f}
    };
    world_register_component(world, 1u, sizeof(f32) * 3u);
    world_register_component(world, 3u, sizeof(u32));
    for (u32 i = 0; i < CORE_APP_LEVEL_ENTITIES; ++i) {
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
    if (!output_path(temporary, output, ".level.bscn.bake-tmp")) {
        core_app_report_path("scene", "scene.temporary_path", output, 0,
                             core_app_crt_error());
        goto cleanup;
    }
    if (!output_path(final_path, output, "level.bscn")) {
        core_app_report_path("scene", "scene.final_path", output, 0,
                             core_app_crt_error());
        goto cleanup;
    }
    SerializeOptions options;
    memset(&options, 0, sizeof(options));
    options.include_resources = true;
    options.read_mesh_geometry = read_cpu_geometry;
    options.read_mesh_geometry_user = &scene;
    if (!scene_save_binary(world, &scene, temporary, &options)) {
        core_app_report_scene("scene", "scene.save", temporary, final_path, 0,
                              core_app_os_error());
        goto cleanup;
    }
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
    for (u32 i = 0; i < CORE_APP_LEVEL_ENTITIES; ++i) {
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
    desc.event_key = 1001u;
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
    desc.a = 1.0f;
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
    u8 wav[CORE_APP_WAV_BYTES];
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
    put32(wav + 40, CORE_APP_WAV_SAMPLES * 2u);
    u32 seed = 0xC0FFEE12u;
    for (u32 i = 0; i < CORE_APP_WAV_SAMPLES; ++i) {
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
        {"user.lua",
         "function on_spawn()\n"
         "    return true\n"
         "end\n"
         "function on_actor_tick(actor, dt)\n"
         "    state.ticks = (state.ticks or 0) + 1\n"
         "end\n"},
        {"chaser.lua",
         "function on_actor_tick(actor, dt)\n"
         "    error('faulty actor tick')\n"
         "end\n"},
        {"deterministic.scenario",
         "core-app-scenario 1\n"
         "seed 12648430\n"
         "fixed-dt-ns 16666667\n"
         "1 level\n"
         "1 key w 1\n"
         "181 quit\n"},
        {"load_unload.scenario",
         "core-app-scenario 1\n"
         "seed 12648430\n"
         "fixed-dt-ns 16666667\n"
         "1 level\n"
         "2 unload\n"
         "3 level\n"
         "4 unload\n"
         "5 quit\n"},
        {"rollback.scenario",
         "core-app-scenario 1\n"
         "seed 12648430\n"
         "fixed-dt-ns 16666667\n"
         "1 level\n"
         "30 key w 1\n"
         "120 key w 0\n"
         "121 unload\n"
         "122 level\n"
         "150 quit\n"}
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
        puts("Usage: core_app_asset_bake --output DIR");
        return 0;
    }
    if (argc == 3 && strcmp(argv[1], "--output") == 0 && argv[2][0] != '\0')
        output = argv[2];
    if (!output) {
        fputs("Usage: core_app_asset_bake --output DIR\n", stderr);
        return 2;
    }
    bool mkdir_result = platform_mkdir(output);
    if (!mkdir_result) {
        core_app_report_path("prepare", "prepare.platform_mkdir", output,
                             (i64)mkdir_result, core_app_os_error());
        fputs("core_app_asset_bake: cannot create output directory\n", stderr);
        return 1;
    }
    if (!bake_scene(output) || !bake_sidecar(output) || !bake_flow(output) ||
        !bake_animation(output) || !bake_wav(output) || !bake_text_assets(output)) {
        fputs("core_app_asset_bake: asset generation failed\n", stderr);
        return 1;
    }
    return 0;
}
