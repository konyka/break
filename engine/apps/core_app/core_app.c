#include "core_app.h"

#include "core_app_audio.h"
#include "core_app_checkpoint.h"
#include "core_app_gpu.h"
#include "core_app_render.h"
#include "core_app_simulation.h"

#include <ai/break_ai.h>
#include <animation/anim_compression.h>
#include <animation/animation.h>
#include <animation/facial.h>
#include <renderer/lod_skin.h>
#include <asset/vfs.h>
#include <game/break_flow.h>
#include <game/break_game_internal.h>
#include <game/break_game_lua.h>
#include <physics/physics.h>
#include <physics/ragdoll.h>
#include <physics/vehicle.h>
#include <platform/platform_fs.h>
#include <runtime/runtime_coordinator.h>
#include <runtime/runtime_io.h>
#include <scene/scene_serial.h>
#include <script/break_lua.h>

#include <inttypes.h>
#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CORE_APP_TEXT_FILE_MAX_BYTES (1u << 20)
#define CORE_APP_IO_TIMEOUT_MS 5000u
#define CORE_APP_USER_ENTITY_INDEX 2u
#define CORE_APP_CHASER_ENTITY_INDEX 3u
#define CORE_APP_VEHICLE_NODE_INDEX 4u
#define CORE_APP_VEHICLE_REACH 3.0f
#define CORE_APP_VEHICLE_SETTLE_STEPS 120u
#define CORE_APP_CHAIN_JOINTS 3u
#define CORE_APP_KEY_RAGDOLL 'r'
#define CORE_APP_WORLD_OBJECTS 8u
#define CORE_APP_STREAM_OBJECT_ID 100u
#define CORE_APP_VEGETATION_CAPACITY 4u
#define CORE_APP_DAY_SECONDS 2.0f
#define CORE_APP_SKINNED_OBJECTS 2u
#define CORE_APP_IO_LATENCY_TICKS 2u
#define CORE_APP_IO_QUEUE 8u
#define CORE_APP_RUNTIME_STATE_VERSION 2u
#define CORE_APP_RUNTIME_HEADER_BYTES 16u
#define CORE_APP_RUNTIME_BODY_BYTES 68u
#define CORE_APP_RUNTIME_FILE_BYTES (CORE_APP_RUNTIME_HEADER_BYTES + CORE_APP_RUNTIME_BODY_BYTES)
#define CORE_APP_RUNTIME_FLAG_WALL_ADDED 1u
#define CORE_APP_RUNTIME_FLAG_WALL_REMOVED 2u
#define CORE_APP_RUNTIME_FLAG_TARGET_IN_SIGHT 4u
#define CORE_APP_RUNTIME_FLAG_SEEN 8u
#define CORE_APP_RUNTIME_FLAGS 15u
#define CORE_APP_AREA_FLOW_EVENT 1001u
#define CORE_APP_FLOW_ITEM 1u
#define CORE_APP_MAX_PENDING_AREA_ENTERS 8u
#define CORE_APP_HAPTIC_PAD 0u
#define CORE_APP_HAPTIC_STRENGTH 0.6f
#define CORE_APP_HAPTIC_DURATION_MS 120u

typedef struct CoreLevel {
    World *world;
    Scene scene;
    BreakGame *actor_runtime;
    BreakFlowGraph *flow_graph;
    BreakFlowRuntime *flow;
    BreakLuaRuntime *lua;
    BreakGameLuaAdapter *adapter;
    PhysicsWorld *physics;
    BreakNavMesh *nav_mesh;
    BreakAiRuntime *ai;
    AnimClip animation;
    CoreAppRenderLevel render;
    BreakRuntimeIoRequest *request;
    PhysicsBodyHandle ground_body;
    CoreAppSimulation *simulation;
    Entity user;
    Entity chaser;
    u32 user_items;
    u32 trigger_area;
    u32 pending_area_enters;
    u32 dropped_area_enters;
    f32 nav_heights[64];
    Vec3 chaser_position;
    BreakAiPath chase_path;
    BreakNavFollower follower;
    BreakBlackboard board;
    BreakAiObstacleHandle wall;
    CharacterController chaser_character;
    PhysicsBodyHandle wall_body;
    bool wall_added;
    bool wall_removed;
    u32 chase_nav_version;
    u32 sight_area;
    bool target_in_sight;
    AnimBlendState locomotion;
    AnimLoco1D loco;
    Vec3 previous_user_position;
    bool previous_user_position_valid;
    AnimFacialLibrary facial;
    AnimMorphSet face_morphs;
    Vec3 face_delta;
    u8 face_bind[64];
    u8 face_morphed[64];
    f32 face_skinned[3];
    Vehicle vehicle;
    bool vehicle_live;
    bool interact_was_down;
    Skeleton chain;
    IKSystem ik;
    Ragdoll ragdoll;
    Vec3 chain_position[CORE_APP_CHAIN_JOINTS];
    Quat chain_rotation[CORE_APP_CHAIN_JOINTS];
    Vec3 chain_scale[CORE_APP_CHAIN_JOINTS];
    Mat4 chain_world[CORE_APP_CHAIN_JOINTS];
    WorldObject world_objects[CORE_APP_WORLD_OBJECTS];
    u32 world_object_count;
    /* Device handles exist only when the GPU lane is live; record mode leaves
     * them zeroed and never calls into the RHI. */
    MeshGpu gpu_meshes[CORE_APP_WORLD_OBJECTS];
    bool gpu_meshes_live;
    MeshGpu vegetation_prototype_gpu;
    MeshDrawDesc vegetation_prototype_draw;
    bool vegetation_prototype_gpu_live;
    RHIDevice *mesh_device;
    u32 visible_ids[CORE_APP_WORLD_OBJECTS];
    u32 visible_count;
    MeshBuffer stream_mesh;
    VegetationInstance vegetation_instances[CORE_APP_VEGETATION_CAPACITY];
    VegetationBuild vegetation;
    WorldVegetationPrototype vegetation_prototype;
    u8 lod_levels[CORE_APP_VEGETATION_CAPACITY];
    u32 lod_tags[CORE_APP_VEGETATION_CAPACITY];
    LodInstanceState lod_state;
    WorldFrameSnapshot world_snapshots[2];
    u32 skin_slot[CORE_APP_SKINNED_OBJECTS];
    u8 *scene_bytes;
    usize scene_size;
    u8 *flow_bytes;
    usize flow_size;
    u8 *actor_bytes;
    usize actor_size;
    u64 generation;
    bool actor_level_open;
} CoreLevel;

typedef struct CoreAppRuntimeState {
    Vec3 user_position;
    Vec3 user_velocity;
    Vec3 chaser_position;
    Vec3 chaser_velocity;
    Vec3 last_seen;
    u32 flags;
    u32 items;
} CoreAppRuntimeState;

typedef struct CoreAppLevelSource {
    const char *asset_root;
    const char *scene_root;
    const char *scene_name;
    const char *flow_root;
    const char *flow_name;
    const char *actor_root;
    const char *actor_name;
} CoreAppLevelSource;

typedef struct CoreAppIoCompletion {
    bool used;
    u32 due_tick;
    u32 slot;
    u64 request;
    u64 generation;
    u32 byte_count;
    u8 bytes[CORE_APP_RESOURCE_MAX_BYTES];
} CoreAppIoCompletion;

struct CoreApp {
    CoreAppConfig config;
    CoreAppScenario scenario;
    CoreAppInput *input;
    BreakRuntimeCoordinator *coordinator;
    VFS *vfs;
    CoreLevel *level;
    CoreLevel *retired_level;
    FILE *trace;
    CoreAppRender render;
    CoreAppAudio audio;
    CoreAppResourceTable resources;
    CoreAppIoCompletion io[CORE_APP_IO_QUEUE];
    /* Only --render=vulkan|opengl with a real device creates this; the record
     * lane never touches it, which keeps a headless host a valid record host. */
    CoreAppGpu gpu;
    WorldFrameSnapshot gpu_snapshot;
    const char *screenshot_path;
    bool screenshot_next;
    u32 tick;
    const char *level_asset_root;
    u64 save_generation;
    u64 next_generation;
    bool io_running;
    bool render_live;
    bool audio_live;
};

static BreakRuntimeError app_request_skins(CoreApp *app, CoreLevel *level);

static const u8 k_runtime_magic[8] = {'C', 'O', 'R', 'E', 'R', 'U', 'N', '1'};

static void app_put32(u8 *p, u32 value) {
    p[0] = (u8)value;
    p[1] = (u8)(value >> 8);
    p[2] = (u8)(value >> 16);
    p[3] = (u8)(value >> 24);
}

static u32 app_get32(const u8 *p) {
    return (u32)p[0] | ((u32)p[1] << 8) | ((u32)p[2] << 16) | ((u32)p[3] << 24);
}

static void app_put_vec3(u8 *p, Vec3 value) {
    for (u32 i = 0u; i < 3u; ++i) {
        u32 bits;
        memcpy(&bits, &value.e[i], sizeof(bits));
        app_put32(p + i * 4u, bits);
    }
}

static bool app_get_vec3(const u8 *p, Vec3 *out) {
    for (u32 i = 0u; i < 3u; ++i) {
        u32 bits = app_get32(p + i * 4u);
        memcpy(&out->e[i], &bits, sizeof(bits));
        if (!isfinite(out->e[i])) return false;
    }
    return true;
}

static void app_runtime_encode_body(const CoreAppRuntimeState *state,
                                    u8 body[CORE_APP_RUNTIME_BODY_BYTES]) {
    memset(body, 0, CORE_APP_RUNTIME_BODY_BYTES);
    app_put_vec3(body + 0u, state->user_position);
    app_put_vec3(body + 12u, state->user_velocity);
    app_put_vec3(body + 24u, state->chaser_position);
    app_put_vec3(body + 36u, state->chaser_velocity);
    app_put_vec3(body + 48u, state->last_seen);
    app_put32(body + 60u, state->flags);
    app_put32(body + 64u, state->items);
}

static u64 app_fnv1a64(const u8 *bytes, usize size) {
    u64 hash = 14695981039346656037ULL;
    for (usize i = 0u; i < size; ++i) {
        hash ^= bytes[i];
        hash *= 1099511628211ULL;
    }
    return hash;
}

static BreakRuntimeError app_runtime_decode(const u8 *bytes, usize size,
                                            CoreAppRuntimeState *out) {
    if (!bytes || !out || size != CORE_APP_RUNTIME_FILE_BYTES ||
        memcmp(bytes, k_runtime_magic, sizeof(k_runtime_magic)) != 0 ||
        app_get32(bytes + 8u) != CORE_APP_RUNTIME_STATE_VERSION ||
        app_get32(bytes + 12u) != CORE_APP_RUNTIME_BODY_BYTES) {
        return BREAK_RUNTIME_INVALID;
    }
    const u8 *body = bytes + CORE_APP_RUNTIME_HEADER_BYTES;
    CoreAppRuntimeState state;
    memset(&state, 0, sizeof(state));
    if (!app_get_vec3(body + 0u, &state.user_position) ||
        !app_get_vec3(body + 12u, &state.user_velocity) ||
        !app_get_vec3(body + 24u, &state.chaser_position) ||
        !app_get_vec3(body + 36u, &state.chaser_velocity) ||
        !app_get_vec3(body + 48u, &state.last_seen)) {
        return BREAK_RUNTIME_INVALID;
    }
    state.flags = app_get32(body + 60u);
    state.items = app_get32(body + 64u);
    if ((state.flags & ~CORE_APP_RUNTIME_FLAGS) != 0u ||
        ((state.flags & CORE_APP_RUNTIME_FLAG_WALL_REMOVED) != 0u &&
         (state.flags & CORE_APP_RUNTIME_FLAG_WALL_ADDED) == 0u)) {
        return BREAK_RUNTIME_INVALID;
    }
    *out = state;
    return BREAK_RUNTIME_OK;
}

static BreakRuntimeError app_audio_drain(CoreApp *app, u32 budget);

static BreakRuntimeError app_trace(CoreApp *app, const char *format, ...) {
    if (!app || !app->trace || !format) return BREAK_RUNTIME_INVALID;
    va_list args;
    va_start(args, format);
    int written = vfprintf(app->trace, format, args);
    va_end(args);
    if (written < 0 || fflush(app->trace) != 0) return BREAK_RUNTIME_FAILED;
    return BREAK_RUNTIME_OK;
}

static BreakRuntimeError app_trace_flow_discard(CoreApp *app, const CoreLevel *level) {
    u32 pending = break_flow_runtime_pending_count(level->flow);
    if (pending == 0u) return BREAK_RUNTIME_OK;
    return app_trace(app,
        "COREAPPTRACE version=1 event=flow kind=discarded generation=%" PRIu64
        " pending=%u\n", level->generation, pending);
}

static bool app_path(char out[PLATFORM_FS_PATH_CAPACITY], const char *root,
                      const char *name) {
    if (!root || !name) return false;
    int written = snprintf(out, PLATFORM_FS_PATH_CAPACITY, "%s/%s", root, name);
    return written > 0 && (usize)written < PLATFORM_FS_PATH_CAPACITY;
}

static bool app_read_file(const char *path, usize maximum, u8 **out_bytes,
                           usize *out_size) {
    if (!path || !out_bytes || !out_size || maximum == 0u) return false;
    *out_bytes = NULL;
    *out_size = 0u;
    FILE *file = fopen(path, "rb");
    if (!file) return false;
    if (fseek(file, 0, SEEK_END) != 0) {
        fclose(file);
        return false;
    }
    long end = ftell(file);
    if (end <= 0 || (u64)end > (u64)maximum || fseek(file, 0, SEEK_SET) != 0) {
        fclose(file);
        return false;
    }
    usize size = (usize)end;
    u8 *bytes = (u8 *)malloc(size + 1u);
    if (!bytes) {
        fclose(file);
        return false;
    }
    usize got = fread(bytes, 1, size, file);
    int extra = fgetc(file);
    int close_result = fclose(file);
    bool ok = got == size && extra == EOF && close_result == 0;
    if (!ok) {
        free(bytes);
        return false;
    }
    bytes[size] = 0u;
    *out_bytes = bytes;
    *out_size = size;
    return true;
}

static bool app_read_asset(const char *root, const char *name, usize maximum,
                            u8 **out_bytes, usize *out_size) {
    char path[PLATFORM_FS_PATH_CAPACITY];
    return app_path(path, root, name) &&
           app_read_file(path, maximum, out_bytes, out_size);
}

static void core_app_level_destroy(CoreLevel *level) {
    if (!level) return;
    /* Device handles die with the level that uploaded them. mesh_device is
     * only set when the GPU lane is live, so record mode never touches the
     * RHI here. */
    if (level->gpu_meshes_live && level->mesh_device) {
        for (u32 i = 0u; i < level->world_object_count; ++i) {
            if (rhi_handle_valid(level->gpu_meshes[i].vertex) ||
                rhi_handle_valid(level->gpu_meshes[i].index)) {
                mesh_gpu_destroy(level->mesh_device, &level->gpu_meshes[i]);
            }
        }
    }
    if (level->vegetation_prototype_gpu_live && level->mesh_device) {
        mesh_gpu_destroy(level->mesh_device, &level->vegetation_prototype_gpu);
    }
    level->vegetation_prototype_gpu_live = false;
    memset(level->gpu_meshes, 0, sizeof(level->gpu_meshes));
    level->gpu_meshes_live = false;
    level->mesh_device = NULL;
    break_runtime_io_request_release(level->request);
    level->request = NULL;
    core_app_simulation_destroy(level->simulation);
    level->simulation = NULL;
    anim_blend_state_destroy(&level->locomotion);
    if (level->ai) break_ai_runtime_destroy(level->ai);
    if (level->nav_mesh) break_nav_mesh_destroy(level->nav_mesh);
    if (level->ragdoll.active && level->physics) ragdoll_deactivate(&level->ragdoll, level->physics);
    if (level->vehicle_live && level->physics) vehicle_destroy(&level->vehicle, level->physics);
    if (level->physics) physics_world_destroy(level->physics);
    if (level->actor_level_open && level->actor_runtime) {
        (void)break_game_level_close(level->actor_runtime);
    }
    if (level->adapter) break_game_lua_destroy(level->adapter);
    if (level->lua) break_lua_runtime_destroy(level->lua);
    if (level->flow) break_flow_runtime_destroy(level->flow);
    if (level->flow_graph) break_flow_graph_destroy(level->flow_graph);
    if (level->actor_runtime) break_game_destroy(level->actor_runtime);
    free(level->scene.materials);
    level->scene.materials = NULL;
    level->scene.material_count = 0u;
    scene_serial_free(&level->scene);
    if (level->world) world_destroy(level->world);
    free(level->scene_bytes);
    free(level->flow_bytes);
    free(level->actor_bytes);
    free(level);
}

static BreakGameError app_level_hook_load(void *user, World *world,
                                           const char *scene_path) {
    CoreLevel *level = (CoreLevel *)user;
    if (!level || level->world != world || !scene_path || scene_path[0] == '\0') {
        return BREAK_GAME_INVALID;
    }
    return level->scene.node_count > 0u ? BREAK_GAME_OK : BREAK_GAME_FAILED;
}

static void app_level_hook_unload(void *user, World *world) {
    (void)user;
    (void)world;
}

static BreakRuntimeError stage_bscn(CoreApp *app, CoreLevel *candidate,
                                         const char *root, const char *name,
                                         bool *runtime_fatal) {
    if (app->vfs->mount_count != 0u) {
        if (app->vfs->mount_count != 1u ||
            app->vfs->mounts[0].type != VFS_MOUNT_DIR) {
            return BREAK_RUNTIME_FAILED;
        }
        app->vfs->mount_count = 0u;
    }
    if (!vfs_mount_dir(app->vfs, root)) return BREAK_RUNTIME_FAILED;
    BreakRuntimeError result = break_runtime_io_submit(&candidate->request,
                                                       name, 0u, 0u);
    if (result != BREAK_RUNTIME_OK) return result;
    BreakRuntimeOwnedMessage *message = NULL;
    result = break_runtime_io_wait_completion(candidate->request,
                                              CORE_APP_IO_TIMEOUT_MS, &message);
    if (result == BREAK_RUNTIME_TIMEOUT) {
        result = break_runtime_io_wait_completion(candidate->request,
                                                  CORE_APP_IO_TIMEOUT_MS, &message);
        if (result != BREAK_RUNTIME_OK || !message) {
            break_runtime_message_release(message);
            *runtime_fatal = true;
            return result != BREAK_RUNTIME_OK ? result : BREAK_RUNTIME_FAILED;
        }
        break_runtime_message_release(message);
        break_runtime_io_request_release(candidate->request);
        candidate->request = NULL;
        result = app_trace(app, "COREAPPTRACE version=1 event=io_quiesced\n");
        if (result != BREAK_RUNTIME_OK) *runtime_fatal = true;
        return result != BREAK_RUNTIME_OK ? result : BREAK_RUNTIME_TIMEOUT;
    }
    if (result != BREAK_RUNTIME_OK || !message) {
        break_runtime_message_release(message);
        return result != BREAK_RUNTIME_OK ? result : BREAK_RUNTIME_FAILED;
    }
    BreakRuntimeIoCompletion completion;
    memset(&completion, 0, sizeof(completion));
    result = break_runtime_io_completion_view(message, &completion);
    if (result != BREAK_RUNTIME_OK ||
        completion.state != BREAK_RUNTIME_IO_COMPLETED ||
        completion.byte_size == 0u || completion.byte_size > BSCN_MAX_FILE_BYTES ||
        !completion.bytes) {
        break_runtime_message_release(message);
        return BREAK_RUNTIME_FAILED;
    }
    candidate->scene_bytes = (u8 *)malloc((usize)completion.byte_size);
    if (!candidate->scene_bytes) {
        break_runtime_message_release(message);
        return BREAK_RUNTIME_OOM;
    }
    memcpy(candidate->scene_bytes, completion.bytes, (usize)completion.byte_size);
    candidate->scene_size = (usize)completion.byte_size;

    candidate->world = world_create();
    if (!candidate->world) {
        break_runtime_message_release(message);
        return BREAK_RUNTIME_OOM;
    }
    world_register_component(candidate->world, BREAK_GAME_POSITION_COMPONENT,
                             sizeof(Vec3));
    world_register_component(candidate->world, 1u, sizeof(f32) * 3u);
    world_register_component(candidate->world, 3u, sizeof(u32));
    bool loaded = scene_load_binary_memory(candidate->world, &candidate->scene,
                                           completion.bytes,
                                           (usize)completion.byte_size);
    break_runtime_message_release(message);
    break_runtime_io_request_release(candidate->request);
    candidate->request = NULL;
    if (!loaded) return BREAK_RUNTIME_FAILED;

    BreakGameConfig config = {16u, 64u};
    candidate->actor_runtime = break_game_create(candidate->world, &config);
    if (!candidate->actor_runtime) return BREAK_RUNTIME_OOM;
    static const char *const class_names[] = {
        "Ground", "User", "Chaser", "DynamicWall", "Vehicle",
        "VisibleColor", "HiddenColor"
    };
    for (u32 i = 0u; i < sizeof(class_names) / sizeof(class_names[0]); ++i) {
        BreakGameClassDesc desc;
        memset(&desc, 0, sizeof(desc));
        desc.name = class_names[i];
        if (i == 1u) desc.lua_module = "user";
        if (i == 2u) desc.lua_module = "chaser";
        u32 class_id = 0u;
        if (break_game_register_class(candidate->actor_runtime, &desc, &class_id) !=
                BREAK_GAME_OK ||
            class_id == 0u) {
            return BREAK_RUNTIME_FAILED;
        }
    }
    BreakGameItemDesc item = {1u, 1000000u};
    if (break_game_item_define(candidate->actor_runtime, &item) != BREAK_GAME_OK) {
        return BREAK_RUNTIME_FAILED;
    }
    return BREAK_RUNTIME_OK;
}

static BreakRuntimeError stage_flow(CoreLevel *candidate, const char *root,
                                    const char *name) {
    u8 *bytes = NULL;
    usize size = 0u;
    if (!app_read_asset(root, name, CORE_APP_TEXT_FILE_MAX_BYTES, &bytes, &size)) {
        return BREAK_RUNTIME_FAILED;
    }
    candidate->flow_bytes = bytes;
    candidate->flow_size = size;
    BreakFlowError flow_result = break_flow_deserialize(bytes, size,
                                                        &candidate->flow_graph);
    if (flow_result != BREAK_FLOW_OK ||
        break_flow_graph_validate(candidate->flow_graph) != BREAK_FLOW_OK) {
        return BREAK_RUNTIME_FAILED;
    }
    u32 node_count = break_flow_graph_node_count(candidate->flow_graph);
    for (u32 ordinal = 0u; ordinal < node_count; ++ordinal) {
        u32 id = 0u;
        BreakFlowNodeDesc desc;
        if (break_flow_node_at(candidate->flow_graph, ordinal, &id, &desc) !=
            BREAK_FLOW_OK) {
            return BREAK_RUNTIME_FAILED;
        }
        if ((desc.type == BREAK_FLOW_NODE_ENTITY_SET_POSITION ||
             desc.type == BREAK_FLOW_NODE_ENTITY_ADD_ITEM) &&
            !world_entity_exists(candidate->world, desc.entity)) {
            return BREAK_RUNTIME_STALE;
        }
        if (desc.type == BREAK_FLOW_NODE_ENTITY_ADD_ITEM && desc.item_id != 1u) {
            return BREAK_RUNTIME_FAILED;
        }
    }
    BreakFlowRuntimeConfig config = {64u, 64u, 256u};
    candidate->flow = break_flow_runtime_create(candidate->flow_graph,
                                                candidate->actor_runtime, &config);
    return candidate->flow ? BREAK_RUNTIME_OK : BREAK_RUNTIME_OOM;
}

static BreakRuntimeError stage_lua(CoreLevel *candidate,
                                        const char *asset_root) {
    BreakLuaRuntimeConfig config;
    memset(&config, 0, sizeof(config));
    config.max_modules = 4u;
    config.instruction_budget = 1000000u;
    config.memory_budget = 8u * 1024u * 1024u;
    candidate->lua = break_lua_runtime_create(&config);
    if (!candidate->lua) return BREAK_RUNTIME_OOM;
    static const char *const modules[] = {"director", "user", "chaser"};
    for (u32 i = 0u; i < sizeof(modules) / sizeof(modules[0]); ++i) {
        char filename[64];
        int written = snprintf(filename, sizeof(filename), "%s.lua", modules[i]);
        if (written < 0 || (usize)written >= sizeof(filename)) {
            return BREAK_RUNTIME_FAILED;
        }
        u8 *source = NULL;
        usize source_size = 0u;
        if (!app_read_asset(asset_root, filename, BREAK_LUA_MAX_MODULE_BYTES,
                             &source, &source_size)) {
            return BREAK_RUNTIME_FAILED;
        }
        BreakLuaError result = break_lua_runtime_load_module(
            candidate->lua, modules[i], source, source_size);
        free(source);
        if (result != BREAK_LUA_OK) return BREAK_RUNTIME_FAILED;
    }
    candidate->adapter = break_game_lua_create(candidate->actor_runtime, candidate->lua);
    return candidate->adapter ? BREAK_RUNTIME_OK : BREAK_RUNTIME_OOM;
}

static BreakRuntimeError stage_actor(CoreLevel *candidate,
                                     const CoreAppLevelSource *source) {
    char scene_path[PLATFORM_FS_PATH_CAPACITY];
    char sidecar_path[PLATFORM_FS_PATH_CAPACITY];
    if (!app_path(scene_path, source->scene_root, source->scene_name) ||
        !app_path(sidecar_path, source->actor_root, source->actor_name)) {
        return BREAK_RUNTIME_INVALID;
    }
    if (!app_read_file(sidecar_path, CORE_APP_TEXT_FILE_MAX_BYTES, &candidate->actor_bytes,
                       &candidate->actor_size)) {
        return BREAK_RUNTIME_FAILED;
    }
    BreakGameLevelHooks hooks;
    memset(&hooks, 0, sizeof(hooks));
    hooks.load = app_level_hook_load;
    hooks.unload = app_level_hook_unload;
    hooks.user = candidate;
    if (break_game_level_open(candidate->actor_runtime, &hooks, scene_path, sidecar_path) !=
        BREAK_GAME_OK) {
        return BREAK_RUNTIME_FAILED;
    }
    candidate->actor_level_open = true;
    return BREAK_RUNTIME_OK;
}

static Vec3 app_node_position(const SceneNode *node) {
    return vec3(node->world_transform.e[3][0], node->world_transform.e[3][1],
                node->world_transform.e[3][2]);
}

static BreakRuntimeError stage_physics(CoreLevel *candidate) {
    if (candidate->scene.node_count < 2u || !candidate->scene.nodes) {
        return BREAK_RUNTIME_FAILED;
    }
    candidate->physics = physics_world_create(32u);
    if (!candidate->physics) return BREAK_RUNTIME_OOM;
    const SceneNode *ground = &candidate->scene.nodes[0];
    Vec3 ground_extent = vec3(fabsf(ground->world_transform.e[0][0]),
                              fabsf(ground->world_transform.e[1][1]),
                              fabsf(ground->world_transform.e[2][2]));
    candidate->ground_body = physics_body_create(candidate->physics,
        app_node_position(ground), ground_extent, 0.0f, true, 0u);
    if (!physics_body_handle_is_valid(candidate->ground_body)) {
        return BREAK_RUNTIME_FAILED;
    }
    if (candidate->scene.node_count <= CORE_APP_VEHICLE_NODE_INDEX) return BREAK_RUNTIME_FAILED;
    Vec3 spawn = app_node_position(&candidate->scene.nodes[CORE_APP_VEHICLE_NODE_INDEX]);
    spawn.e[1] += 0.25f;
    if (!vehicle_create(&candidate->vehicle, candidate->physics, spawn)) {
        return BREAK_RUNTIME_FAILED;
    }
    candidate->vehicle_live = true;
    VehicleInput idle = {0.0f, 0.0f, 0.0f};
    for (u32 step = 0u; step < CORE_APP_VEHICLE_SETTLE_STEPS; ++step) {
        vehicle_step(&candidate->vehicle, candidate->physics, &idle, CORE_APP_FIXED_DT);
        physics_step(candidate->physics, CORE_APP_FIXED_DT);
    }
    static const Vec3 bind_world[CORE_APP_CHAIN_JOINTS] = {
        {{6.0f, 3.0f, -4.0f}}, {{6.0f, 2.0f, -4.0f}}, {{6.0f, 1.0f, -4.0f}}
    };
    const u32 parents[CORE_APP_CHAIN_JOINTS] = {UINT32_MAX, 0u, 1u};
    Mat4 inverse_bind[CORE_APP_CHAIN_JOINTS];
    for (u32 joint = 0u; joint < CORE_APP_CHAIN_JOINTS; ++joint) {
        inverse_bind[joint] = mat4_translation(-bind_world[joint].e[0],
                                               -bind_world[joint].e[1],
                                               -bind_world[joint].e[2]);
    }
    skeleton_init(&candidate->chain, NULL);
    skeleton_set_joints(&candidate->chain, CORE_APP_CHAIN_JOINTS, parents, inverse_bind);
    anim_ik_init(&candidate->ik);
    anim_ik_set_target(&candidate->ik, 0u, 0u, 1u, 2u, vec3(6.6f, 1.6f, -4.0f),
                       vec3(7.0f, 2.0f, -4.0f));
    anim_ik_set_weight(&candidate->ik, 0u, 1.0f);
    return BREAK_RUNTIME_OK;
}

static void app_chain_bind_pose(CoreLevel *level) {
    level->chain_position[0] = vec3(6.0f, 3.0f, -4.0f);
    level->chain_position[1] = vec3(0.0f, -1.0f, 0.0f);
    level->chain_position[2] = vec3(0.0f, -1.0f, 0.0f);
    for (u32 joint = 0u; joint < CORE_APP_CHAIN_JOINTS; ++joint) {
        level->chain_rotation[joint] = QUAT_IDENTITY;
        level->chain_scale[joint] = vec3(1.0f, 1.0f, 1.0f);
    }
}

static BreakRuntimeError app_tick_ragdoll(CoreApp *app, u32 tick,
                                          const CoreAppInputFrame *frame) {
    CoreLevel *level = app->level;
    BreakRuntimeError result;
    if (input_key_pressed(&frame->state, CORE_APP_KEY_RAGDOLL)) {
        bool ok;
        if (level->ragdoll.active) {
            ragdoll_deactivate(&level->ragdoll, level->physics);
            ok = !level->ragdoll.active;
        } else {
            ok = ragdoll_activate(&level->ragdoll, level->physics, &level->chain, &level->ik);
        }
        result = app_trace(app,
            "COREAPPTRACE version=1 event=ragdoll tick=%u generation=%" PRIu64
            " active=%u ok=%u\n", tick, level->generation,
            level->ragdoll.active ? 1u : 0u, ok ? 1u : 0u);
        if (result != BREAK_RUNTIME_OK) return result;
    }
    bool ragdoll_active = level->ragdoll.active;
    if (ragdoll_active) {
        if (!ragdoll_write_local_trs(&level->ragdoll, level->physics, &level->chain,
                                     level->chain_position, level->chain_rotation,
                                     level->chain_scale)) {
            return BREAK_RUNTIME_FAILED;
        }
    } else {
        app_chain_bind_pose(level);
    }
    skeleton_compute_world_transforms(&level->chain, level->chain_position,
                                      level->chain_rotation, level->chain_scale,
                                      level->chain_world);
    bool solved = anim_ik_solve_unless_ragdoll(&level->ik, level->chain_position,
                                               level->chain_rotation, level->chain_world,
                                               CORE_APP_CHAIN_JOINTS, ragdoll_active);
    skeleton_compute_world_transforms(&level->chain, level->chain_position,
                                      level->chain_rotation, level->chain_scale,
                                      level->chain_world);
    skeleton_apply_local_trs(&level->chain, level->chain_position, level->chain_rotation,
                             level->chain_scale);
    return app_trace(app,
        "COREAPPTRACE version=1 event=ik tick=%u generation=%" PRIu64
        " ragdoll=%u solved=%u owned=%u tip_x=%.9g tip_y=%.9g\n", tick, level->generation,
        ragdoll_active ? 1u : 0u, solved ? 1u : 0u, level->ik.physics_ragdoll_count,
        (double)level->chain_world[2].e[3][0], (double)level->chain_world[2].e[3][1]);
}

static void app_area_event(u32 area_id, Entity entity, BreakGameAreaEvent event,
                           void *user) {
    CoreLevel *level = (CoreLevel *)user;
    if (!level || event != BREAK_GAME_AREA_ENTER ||
        entity.index != level->user.index ||
        entity.generation != level->user.generation) {
        return;
    }
    if (area_id == level->sight_area) {
        level->target_in_sight = true;
        return;
    }
    if (area_id != level->trigger_area) return;
    if (level->pending_area_enters < CORE_APP_MAX_PENDING_AREA_ENTERS) {
        level->pending_area_enters++;
    } else {
        level->dropped_area_enters++;
    }
}

static BreakRuntimeError stage_simulation(CoreLevel *candidate) {
    if (candidate->scene.node_count < 2u ||
        candidate->world->entity_count <= CORE_APP_USER_ENTITY_INDEX) {
        return BREAK_RUNTIME_FAILED;
    }
    Entity user = candidate->world->entities[CORE_APP_USER_ENTITY_INDEX];
    if (!world_entity_exists(candidate->world, user)) return BREAK_RUNTIME_STALE;
    const SceneNode *node = &candidate->scene.nodes[1];
    Vec3 center = app_node_position(node);
    Vec3 feet = vec3(center.e[0], center.e[1] - fabsf(node->world_transform.e[1][1]),
                     center.e[2]);
    Vec3 *position = (Vec3 *)world_add_component(candidate->world, user,
                                                 BREAK_GAME_POSITION_COMPONENT);
    if (!position) return BREAK_RUNTIME_FAILED;
    *position = feet;
    CoreAppSimulationDesc desc;
    memset(&desc, 0, sizeof(desc));
    desc.world = candidate->world;
    desc.actor_runtime = candidate->actor_runtime;
    desc.physics = candidate->physics;
    desc.user = user;
    desc.spawn = feet;
    candidate->simulation = core_app_simulation_create(&desc);
    if (!candidate->simulation) return BREAK_RUNTIME_FAILED;
    candidate->user = user;
    if (candidate->world->entity_count <= CORE_APP_CHASER_ENTITY_INDEX) {
        return BREAK_RUNTIME_FAILED;
    }
    candidate->chaser = candidate->world->entities[CORE_APP_CHASER_ENTITY_INDEX];
    if (!world_entity_exists(candidate->world, candidate->chaser)) return BREAK_RUNTIME_STALE;
    BreakGameAreaDesc area;
    memset(&area, 0, sizeof(area));
    area.center = vec3(feet.e[0], feet.e[1] + 1.0f, feet.e[2] + 3.0f);
    area.half_extent = vec3(1.5f, 2.0f, 0.5f);
    if (break_game_area_add(candidate->actor_runtime, &area,
                            &candidate->trigger_area) != BREAK_GAME_OK) {
        return BREAK_RUNTIME_FAILED;
    }
    break_game_set_area_callback(candidate->actor_runtime, app_area_event, candidate);
    if (candidate->scene.node_count < 3u || !candidate->scene.nodes) {
        return BREAK_RUNTIME_FAILED;
    }
    BreakGameAreaDesc sight;
    memset(&sight, 0, sizeof(sight));
    sight.center = app_node_position(&candidate->scene.nodes[2]);
    sight.half_extent = vec3(6.0f, 3.0f, 6.0f);
    if (break_game_area_add(candidate->actor_runtime, &sight,
                            &candidate->sight_area) != BREAK_GAME_OK) {
        return BREAK_RUNTIME_FAILED;
    }
    AnimLocoSample samples[2] = {{0.0f, 0u}, {4.0f, 1u}};
    if (!anim_loco1d_init(&candidate->loco, 0u, samples, 2u)) return BREAK_RUNTIME_FAILED;
    anim_blend_state_init(&candidate->locomotion, 1u);
    candidate->previous_user_position_valid = false;
    if (!anim_morph_init(&candidate->face_morphs, 1u)) return BREAK_RUNTIME_FAILED;
    candidate->face_delta = vec3(0.0f, 2.0f, 0.0f);
    if (!anim_morph_add_target(&candidate->face_morphs, "lift", &candidate->face_delta)) {
        return BREAK_RUNTIME_FAILED;
    }
    anim_facial_library_init(&candidate->facial);
    if (!anim_facial_add_expression(&candidate->facial, "lift")) return BREAK_RUNTIME_FAILED;
    {
        const f32 times[2] = {0.0f, 1.0f};
        const f32 values[2] = {0.0f, 1.0f};
        if (!anim_facial_add_curve(&candidate->facial, "lift", "up", "lift",
                                   2u, times, values)) {
            return BREAK_RUNTIME_FAILED;
        }
    }
    memset(candidate->face_bind, 0, sizeof(candidate->face_bind));
    {
        f32 weights[4] = {1.0f, 0.0f, 0.0f, 0.0f};
        memcpy(candidate->face_bind + 48, weights, sizeof(weights));
    }
    return BREAK_RUNTIME_OK;
}

static BreakRuntimeError app_tick_vehicle(CoreApp *app, u32 tick,
                                          const CoreAppInputFrame *frame) {
    CoreLevel *level = app->level;
    CoreAppMoveIntent intent;
    BreakRuntimeError result = core_app_simulation_intent(level->simulation, frame, &intent);
    if (result != BREAK_RUNTIME_OK) return result;
    bool pressed = intent.interact && !level->interact_was_down;
    level->interact_was_down = intent.interact;
    RigidBody *chassis = physics_body_resolve(level->physics, level->vehicle.chassis);
    if (!chassis) return BREAK_RUNTIME_STALE;
    if (pressed && !level->vehicle.occupied) {
        Vec3 user_position;
        result = core_app_simulation_user_position(level->simulation, &user_position);
        if (result != BREAK_RUNTIME_OK) return result;
        f32 dx = user_position.e[0] - chassis->position.e[0];
        f32 dz = user_position.e[2] - chassis->position.e[2];
        bool ok = dx * dx + dz * dz <= CORE_APP_VEHICLE_REACH * CORE_APP_VEHICLE_REACH &&
                  vehicle_enter(&level->vehicle);
        result = app_trace(app,
            "COREAPPTRACE version=1 event=vehicle_enter tick=%u generation=%" PRIu64
            " ok=%u\n", tick, level->generation, ok ? 1u : 0u);
        if (result != BREAK_RUNTIME_OK) return result;
    } else if (pressed) {
        Vec3 feet;
        bool ok = vehicle_exit(&level->vehicle, level->physics, &feet);
        if (ok) {
            result = core_app_simulation_place_user(level->simulation, feet);
            if (result != BREAK_RUNTIME_OK) return result;
        }
        result = app_trace(app,
            "COREAPPTRACE version=1 event=vehicle_exit tick=%u generation=%" PRIu64
            " ok=%u\n", tick, level->generation, ok ? 1u : 0u);
        if (result != BREAK_RUNTIME_OK) return result;
    }
    VehicleInput input = {0.0f, 0.0f, 0.0f};
    if (level->vehicle.occupied) {
        input.throttle = intent.forward;
        input.steer = intent.strafe;
    }
    vehicle_step(&level->vehicle, level->physics, &input, CORE_APP_FIXED_DT);
    return BREAK_RUNTIME_OK;
}

static bool app_chaser_sees_user(void *user, Vec3 from, Vec3 to) {
    CoreLevel *level = (CoreLevel *)user;
    Vec3 delta = vec3(to.e[0] - from.e[0], to.e[1] - from.e[1], to.e[2] - from.e[2]);
    f32 distance = sqrtf(delta.e[0] * delta.e[0] + delta.e[1] * delta.e[1] +
                         delta.e[2] * delta.e[2]);
    if (distance <= 1.0e-6f) return true;
    Vec3 dir = vec3(delta.e[0] / distance, delta.e[1] / distance, delta.e[2] / distance);
    PhysicsBodyHandle hit;
    f32 t = 0.0f;
    if (!physics_raycast(level->physics, from, dir, distance, &hit, &t)) return true;
    return hit.index == level->wall_body.index && hit.generation == level->wall_body.generation
               ? false
               : true;
}

static BreakRuntimeError app_tick_chaser(CoreApp *app, u32 tick) {
    CoreLevel *level = app->level;
    Vec3 user_position;
    BreakRuntimeError result = core_app_simulation_user_position(level->simulation,
                                                                   &user_position);
    if (result != BREAK_RUNTIME_OK) return result;
    BreakSight sight;
    memset(&sight, 0, sizeof(sight));
    sight.eye = level->chaser_position;
    sight.forward = vec3(-0.707106781f, 0.0f, -0.707106781f);
    sight.distance = 12.0f;
    sight.half_angle_rad = 1.2f;
    BreakSightTarget target;
    memset(&target, 0, sizeof(target));
    target.entity = level->user;
    target.point = user_position;
    Entity visible;
    u32 visible_count = 0u;
    if (break_sight_query(&sight, &target, 1u, app_chaser_sees_user, level,
                          &visible, 1u, &visible_count) != BREAK_NAV_OK) {
        return BREAK_RUNTIME_FAILED;
    }
    if (visible_count == 1u) {
        level->board.seen = true;
        level->board.last_seen = user_position;
        level->board.target = level->user;
    }
    u32 nav_version = break_ai_nav_version(level->ai);
    bool first_path = level->board.seen && level->chase_path.path.count == 0u;
    if (level->board.seen && (first_path || nav_version != level->chase_nav_version)) {
        Vec3 goal = level->board.last_seen;
        if (goal.e[0] < -0.5f) goal.e[0] = -0.5f;
        if (goal.e[0] > 6.5f) goal.e[0] = 6.5f;
        if (goal.e[2] < -0.5f) goal.e[2] = -0.5f;
        if (goal.e[2] > 6.5f) goal.e[2] = 6.5f;
        BreakAiPath fresh;
        BreakNavError path = break_ai_find_path(level->ai, level->chaser_position, goal,
                                                nav_version, &fresh);
        if (path == BREAK_NAV_OK) {
            level->chase_path = fresh;
            break_nav_follow_reset(&level->follower, &fresh.path, 0.2f);
        } else if (path != BREAK_NAV_FAILED) {
            return BREAK_RUNTIME_FAILED;
        }
        level->chase_nav_version = nav_version;
    }

    if (!level->wall_added && level->target_in_sight) {
        BreakAiObstacleDesc wall = {1.0f, 1.0f, 4.0f, 2.0f};
        if (break_ai_obstacle_add(level->ai, &wall, &level->wall) != BREAK_NAV_OK) {
            return BREAK_RUNTIME_FAILED;
        }
        level->wall_body = physics_body_create(level->physics,
            vec3(2.5f, 1.0f, 1.5f), vec3(1.5f, 1.0f, 0.5f), 0.0f, true, 0u);
        if (!physics_body_handle_is_valid(level->wall_body)) return BREAK_RUNTIME_FAILED;
        level->wall_added = true;
    }
    BreakNode nodes[2];
    memset(nodes, 0, sizeof(nodes));
    nodes[0].kind = BREAK_NODE_SELECTOR;
    nodes[0].child_begin = 1u;
    nodes[0].child_count = 1u;
    nodes[1].kind = BREAK_NODE_LEAF;
    nodes[1].leaf = BREAK_LEAF_CHASE;
    BreakBehaveResult behave;
    memset(&behave, 0, sizeof(behave));
    break_behavior_tick(nodes, 2u, 0u, &level->board, &level->follower,
                        level->chaser_position, CORE_APP_FIXED_DT, &behave);
    Vec3 velocity;
    if (break_steer_avoid_velocity(level->chaser_position, vec3(0, 0, 0), 0.4f, 3.0f,
                                   vec3(behave.wish.e[0] / CORE_APP_FIXED_DT, 0.0f,
                                        behave.wish.e[2] / CORE_APP_FIXED_DT),
                                   NULL, 0u, 1.0f, &velocity) != BREAK_NAV_OK) {
        return BREAK_RUNTIME_FAILED;
    }
    character_update(&level->chaser_character, level->physics, CORE_APP_FIXED_DT,
                     vec3(velocity.e[0] / 6.0f, 0.0f, velocity.e[2] / 6.0f), false);
    level->chaser_position = character_get_position(&level->chaser_character);
    if (level->wall_added && !level->wall_removed && level->board.seen &&
        level->chaser_position.e[2] < 1.5f &&
        level->chaser_position.e[0] < 1.0f) {
        if (break_ai_obstacle_remove(level->ai, level->wall) != BREAK_NAV_OK) {
            return BREAK_RUNTIME_FAILED;
        }
        level->wall_removed = true;
    }
    (void)tick;
    return app_trace(app,
        "COREAPPTRACE version=1 event=sim tick=%u generation=%" PRIu64
        " chaser_x=%.9g chaser_z=%.9g nav_version=%u path_current=%u\n",
        tick, level->generation, (double)level->chaser_position.e[0],
        (double)level->chaser_position.e[2], break_ai_nav_version(level->ai),
        break_ai_path_is_current(level->ai, &level->chase_path) ? 1u : 0u);
}

static BreakRuntimeError stage_ai(CoreLevel *candidate) {
    if (candidate->scene.node_count < 3u || candidate->world->entity_count <= 3u) {
        return BREAK_RUNTIME_FAILED;
    }
    BreakNavHeightfield field;
    memset(&field, 0, sizeof(field));
    field.heights = candidate->nav_heights;
    field.width = 8u;
    field.depth = 8u;
    field.cell = 1.0f;
    field.origin_x = -1.0f;
    field.origin_z = -1.0f;
    field.height_scale = 1.0f;
    candidate->nav_mesh = break_nav_bake_heightfield(&field, 45.0f, 0.0f);
    if (!candidate->nav_mesh) return BREAK_RUNTIME_OOM;
    BreakAiRuntimeDesc desc;
    memset(&desc, 0, sizeof(desc));
    desc.max_obstacles = 8u;
    desc.max_agents = 8u;
    desc.max_cached_paths = 8u;
    desc.max_smart_objects = 4u;
    desc.max_formations = 2u;
    candidate->ai = break_ai_runtime_create(candidate->nav_mesh, &desc);
    if (!candidate->ai) return BREAK_RUNTIME_OOM;
    BreakAiAgentDesc agent;
    memset(&agent, 0, sizeof(agent));
    agent.position = app_node_position(&candidate->scene.nodes[2]);
    agent.radius = 0.4f;
    agent.max_speed = 3.0f;
    Entity chaser = candidate->world->entities[3];
    if (break_ai_agent_add(candidate->ai, chaser, &agent) != BREAK_NAV_OK) {
        return BREAK_RUNTIME_FAILED;
    }
    candidate->chaser_position = agent.position;
    candidate->chaser_character = character_create(agent.position, 0.4f, 1.0f);
    candidate->chase_nav_version = break_ai_nav_version(candidate->ai);
    return BREAK_RUNTIME_OK;
}

static BreakRuntimeError stage_animation(CoreLevel *candidate,
                                              const char *asset_root) {
    u8 *bytes = NULL;
    usize size = 0u;
    if (!app_read_asset(asset_root, "level.banm", ANIM_CODEC_MAX_BYTES,
                         &bytes, &size)) {
        return BREAK_RUNTIME_FAILED;
    }
    AnimCodecResult result = anim_codec_decode(bytes, size, &candidate->animation);
    free(bytes);
    return result == ANIM_CODEC_OK ? BREAK_RUNTIME_OK : BREAK_RUNTIME_FAILED;
}

static RHIBuffer app_record_handle(u32 id, u64 generation) {
    RHIBuffer handle = {id, (u32)generation};
    return handle;
}

static BreakRuntimeError stage_presentation(CoreLevel *candidate) {
    if (!scene_rebuild_materials_from_manifest(&candidate->scene)) return BREAK_RUNTIME_FAILED;
    const Scene *scene = &candidate->scene;
    if (!scene->nodes || !scene->mesh_geometry || !scene->materials ||
        scene->node_count + 1u > CORE_APP_WORLD_OBJECTS || (u32)candidate->generation == 0u) {
        return BREAK_RUNTIME_FAILED;
    }
    candidate->world_object_count = 0u;
    candidate->visible_count = 0u;
    for (u32 i = 0u; i < scene->node_count; ++i) {
        const SceneNode *node = &scene->nodes[i];
        if (node->mesh_index >= scene->mesh_geometry_count ||
            node->material_idx >= scene->material_count) {
            return BREAK_RUNTIME_FAILED;
        }
        const SceneMeshGeometry *mesh = &scene->mesh_geometry[node->mesh_index];
        const Material *material = &scene->materials[node->material_idx];
        WorldObject *object = &candidate->world_objects[candidate->world_object_count++];
        memset(object, 0, sizeof(*object));
        object->id = i + 1u;
        object->gpu.vertex = app_record_handle(object->id, candidate->generation);
        object->gpu.index = app_record_handle(object->id, candidate->generation);
        object->draw.vertex_count = mesh->vertex_count;
        object->draw.stride = (u32)sizeof(MeshVertex);
        object->draw.index_count = mesh->index_count;
        object->material.base_color = vec3(material->base_color[0], material->base_color[1],
                                           material->base_color[2]);
        f32 roughness = material->roughness_factor;
        object->material.roughness = roughness < 0.0f ? 0.0f : (roughness > 1.0f ? 1.0f : roughness);
        if (node->has_mesh) candidate->visible_ids[candidate->visible_count++] = object->id;
    }
    StreamTileData tile;
    memset(&tile, 0, sizeof(tile));
    tile.vertex_count = 4u;
    static const f32 corners[4][2] = {{0.0f, 0.0f}, {1.0f, 0.0f}, {1.0f, 1.0f}, {0.0f, 1.0f}};
    for (u32 v = 0u; v < 4u; ++v) {
        tile.verts[v].px = corners[v][0];
        tile.verts[v].pz = corners[v][1];
        tile.verts[v].ny = 1.0f;
    }
    if (!world_presentation_stream_mesh(&tile, vec3(6.0f, 0.0f, -6.0f),
                                        &candidate->stream_mesh)) {
        return BREAK_RUNTIME_FAILED;
    }
    WorldObject *stream = &candidate->world_objects[candidate->world_object_count++];
    memset(stream, 0, sizeof(*stream));
    stream->id = CORE_APP_STREAM_OBJECT_ID;
    stream->gpu.vertex = app_record_handle(stream->id, candidate->generation);
    stream->gpu.index = app_record_handle(stream->id, candidate->generation);
    stream->draw.vertex_count = candidate->stream_mesh.count;
    stream->draw.stride = (u32)sizeof(MeshVertex);
    stream->draw.index_count = candidate->stream_mesh.index_count;
    stream->material.base_color = vec3(0.4f, 0.4f, 0.4f);
    stream->material.roughness = 1.0f;
    stream->stream = true;
    candidate->visible_ids[candidate->visible_count++] = stream->id;

    static const u8 density[4] = {1u, 1u, 1u, 0u};
    static const f32 heights[4] = {0.0f, 0.0f, 0.0f, 0.0f};
    VegetationDesc vegetation;
    memset(&vegetation, 0, sizeof(vegetation));
    vegetation.density = density;
    vegetation.width = 2u;
    vegetation.depth = 2u;
    vegetation.cell = 1.0f;
    vegetation.prototype_count = 1u;
    candidate->vegetation.instances = candidate->vegetation_instances;
    candidate->vegetation.capacity = CORE_APP_VEGETATION_CAPACITY;
    if (!vegetation_build(&vegetation, heights, 1.0f, &candidate->vegetation)) {
        return BREAK_RUNTIME_FAILED;
    }
    WorldVegetationPrototype *prototype = &candidate->vegetation_prototype;
    memset(prototype, 0, sizeof(*prototype));
    prototype->lod_count = 1u;
    prototype->gpu[0].vertex = app_record_handle(200u, candidate->generation);
    prototype->gpu[0].index = app_record_handle(200u, candidate->generation);
    prototype->draws[0].vertex_count = scene->mesh_geometry[0].vertex_count;
    prototype->draws[0].stride = (u32)sizeof(MeshVertex);
    prototype->draws[0].index_count = scene->mesh_geometry[0].index_count;
    prototype->bounding_radius = 0.5f;
    prototype->material.base_color = vec3(0.2f, 0.7f, 0.2f);
    prototype->material.roughness = 1.0f;
    candidate->lod_state.level = candidate->lod_levels;
    candidate->lod_state.tag = candidate->lod_tags;
    candidate->lod_state.capacity = CORE_APP_VEGETATION_CAPACITY;
    return BREAK_RUNTIME_OK;
}

static BreakRuntimeError app_publish_world(CoreApp *app, u32 tick) {
    CoreLevel *level = app->level;
    Vec3 user;
    BreakRuntimeError result = core_app_simulation_user_position(level->simulation, &user);
    if (result != BREAK_RUNTIME_OK) return result;
    Vec3 eye = vec3(user.e[0], user.e[1] + 6.0f, user.e[2] - 10.0f);
    Vec3 forward = vec3_normalize(vec3_sub(user, eye));
    VisQuery visibility;
    memset(&visibility, 0, sizeof(visibility));
    visibility.camera = eye;
    visibility.camera_forward = forward;
    visibility.outdoor_ids = level->visible_ids;
    visibility.outdoor_count = level->visible_count;
    WorldPresentationInput input;
    memset(&input, 0, sizeof(input));
    input.frame_id = tick;
    input.view = mat4_lookat(eye, user, vec3(0.0f, 1.0f, 0.0f));
    input.projection = mat4_perspective(1.0f, 16.0f / 9.0f, 0.1f, 200.0f);
    input.camera = eye;
    input.fov = 1.0f;
    input.screen_height = 720.0f;
    input.pixel_error = 1.0f;
    time_of_day_eval((f32)tick * CORE_APP_FIXED_DT, CORE_APP_DAY_SECONDS, &input.lighting);
    input.objects = level->world_objects;
    input.object_count = level->world_object_count;
    input.visibility = &visibility;
    input.vegetation = &level->vegetation;
    input.prototypes = &level->vegetation_prototype;
    input.prototype_count = 1u;
    input.lod_state = &level->lod_state;
    WorldFrameSnapshot *slot = &level->world_snapshots[tick & 1u];
    if (world_presentation_snapshot(&input, slot) != WORLD_PRESENTATION_OK) {
        return BREAK_RUNTIME_FAILED;
    }
    /* In the GPU lane the snapshot carries real device handles, so the
     * record-only handle validation (generation == level generation) does not
     * apply; the real device trace is the evidence instead. Record mode keeps
     * the validation. */
    if (app->gpu.live) return BREAK_RUNTIME_OK;
    return core_app_render_record_world(&app->render, level->generation, slot);
}

static BreakRuntimeError stage_render(CoreLevel *candidate) {
    if (candidate->scene.resource_count > CORE_APP_RENDER_RESOURCE_CAPACITY ||
        (candidate->scene.resource_count > 0u && !candidate->scene.resources)) {
        return BREAK_RUNTIME_OVERLOAD;
    }
    CoreAppRenderResource resources[CORE_APP_RENDER_RESOURCE_CAPACITY];
    memset(resources, 0, sizeof(resources));
    for (u32 i = 0u; i < candidate->scene.resource_count; ++i) {
        resources[i].id = candidate->scene.resources[i].guid;
        resources[i].generation = candidate->generation;
        resources[i].kind = candidate->scene.resources[i].type;
        resources[i].ref_index = candidate->scene.resources[i].ref_index;
    }
    return core_app_render_stage_level(resources, candidate->scene.resource_count,
                                   candidate->generation, &candidate->render);
}

static const SceneResource *app_find_resource(const CoreLevel *candidate,
                                               BscnResourceType type, u32 ref_index) {
    for (u32 i = 0u; i < candidate->scene.resource_count; ++i) {
        const SceneResource *resource = &candidate->scene.resources[i];
        if (resource->type == (u32)type && resource->ref_index == ref_index) {
            return resource;
        }
    }
    return NULL;
}

static bool app_find_geometry(const CoreLevel *candidate, u32 mesh_index) {
    for (u32 i = 0u; i < candidate->scene.mesh_geometry_count; ++i) {
        if (candidate->scene.mesh_geometry[i].mesh_index == mesh_index) return true;
    }
    return false;
}

static BreakRuntimeError app_validate_crossrefs(const CoreLevel *candidate) {
    if (!candidate->world || !candidate->actor_runtime || !candidate->flow ||
        !candidate->lua || !candidate->adapter || !candidate->actor_level_open ||
        !candidate->physics || !candidate->simulation || !candidate->ai ||
        !candidate->nav_mesh ||
        candidate->generation == 0u || candidate->animation.channel_count == 0u ||
        candidate->scene.node_count == 0u ||
        candidate->world->entity_count != candidate->scene.node_count + 1u ||
        candidate->render.resource_count != candidate->scene.resource_count) {
        return BREAK_RUNTIME_FAILED;
    }
    for (u32 i = 0u; i < candidate->scene.node_count; ++i) {
        const SceneNode *node = &candidate->scene.nodes[i];
        if (!app_find_resource(candidate, BSCN_RES_MESH, node->mesh_index) ||
            !app_find_resource(candidate, BSCN_RES_MATERIAL, node->material_idx) ||
            (node->has_mesh && !app_find_geometry(candidate, node->mesh_index))) {
            return BREAK_RUNTIME_FAILED;
        }
    }
    for (u32 i = 0u; i < candidate->scene.resource_count; ++i) {
        if (candidate->scene.resources[i].guid != candidate->render.resources[i].id ||
            candidate->render.resources[i].generation != candidate->generation) {
            return BREAK_RUNTIME_STALE;
        }
    }
    return BREAK_RUNTIME_OK;
}

static BreakRuntimeError core_app_level_stage(CoreApp *app,
                                              const CoreAppLevelSource *source,
                                              const char **failed_stage,
                                              bool *out_runtime_fatal,
                                              CoreLevel **out_candidate) {
    *failed_stage = "bscn";
    *out_runtime_fatal = false;
    *out_candidate = NULL;
    if (!app->io_running || app->next_generation == 0u) {
        return BREAK_RUNTIME_REJECTED;
    }
    CoreLevel *candidate = (CoreLevel *)calloc(1u, sizeof(*candidate));
    if (!candidate) return BREAK_RUNTIME_OOM;
    candidate->generation = app->next_generation;
    BreakRuntimeError result = stage_bscn(app, candidate, source->scene_root,
                                          source->scene_name, out_runtime_fatal);
    if (result != BREAK_RUNTIME_OK) goto reject;

    *failed_stage = "flow";
    result = stage_flow(candidate, source->flow_root, source->flow_name);
    if (result != BREAK_RUNTIME_OK) goto reject;

    *failed_stage = "lua";
    result = stage_lua(candidate, source->asset_root);
    if (result != BREAK_RUNTIME_OK) goto reject;

    *failed_stage = "actor";
    result = stage_actor(candidate, source);
    if (result != BREAK_RUNTIME_OK) goto reject;

    *failed_stage = "physics";
    result = stage_physics(candidate);
    if (result != BREAK_RUNTIME_OK) goto reject;

    *failed_stage = "simulation";
    result = stage_simulation(candidate);
    if (result != BREAK_RUNTIME_OK) goto reject;

    *failed_stage = "ai";
    result = stage_ai(candidate);
    if (result != BREAK_RUNTIME_OK) goto reject;

    *failed_stage = "animation";
    result = stage_animation(candidate, source->asset_root);
    if (result != BREAK_RUNTIME_OK) goto reject;

    *failed_stage = "render";
    result = stage_render(candidate);
    if (result != BREAK_RUNTIME_OK) goto reject;

    *failed_stage = "crossref";
    result = app_validate_crossrefs(candidate);
    if (result != BREAK_RUNTIME_OK) goto reject;

    *failed_stage = "presentation";
    result = stage_presentation(candidate);
    if (result != BREAK_RUNTIME_OK) goto reject;
    *out_candidate = candidate;
    return BREAK_RUNTIME_OK;

reject:
    core_app_level_destroy(candidate);
    return result;
}

static BreakRuntimeError core_app_level_commit(CoreApp *app, CoreLevel *candidate,
                                               const char **failed_stage,
                                               bool *out_committed) {
    BreakRuntimeError result;
    /* Upload the candidate's visible meshes before it becomes live, so the
     * first frame of a new level already draws real geometry. Record mode has
     * no device and skips this entirely. */
    if (app->gpu.live) {
        for (u32 i = 0u; i < candidate->world_object_count; ++i) {
            WorldObject *object = &candidate->world_objects[i];
            if (object->stream) continue;
            const SceneNode *node = NULL;
            for (u32 n = 0u; n < candidate->scene.node_count; ++n) {
                if (n + 1u == object->id) { node = &candidate->scene.nodes[n]; break; }
            }
            if (!node || node->mesh_index >= candidate->scene.mesh_geometry_count) continue;
            const SceneMeshGeometry *mesh = &candidate->scene.mesh_geometry[node->mesh_index];
            MeshGpu gpu_mesh;
            MeshDrawDesc draw;
            memset(&gpu_mesh, 0, sizeof(gpu_mesh));
            memset(&draw, 0, sizeof(draw));
            result = core_app_gpu_upload_mesh(&app->gpu, mesh->vertices, mesh->vertex_count,
                                              mesh->indices, mesh->index_count, &gpu_mesh,
                                              &draw);
            if (result != BREAK_RUNTIME_OK) {
                *failed_stage = "gpu_upload";
                return result;
            }
            candidate->gpu_meshes[i] = gpu_mesh;
            object->gpu = gpu_mesh;
            object->draw = draw;
        }
        /* The vegetation prototype is also record-mode fake handles in
         * staging; give it a real mesh so instanced draws bind valid buffers. */
        if (candidate->scene.mesh_geometry_count > 0u) {
            const SceneMeshGeometry *proto = &candidate->scene.mesh_geometry[0];
            MeshGpu proto_gpu;
            MeshDrawDesc proto_draw;
            memset(&proto_gpu, 0, sizeof(proto_gpu));
            memset(&proto_draw, 0, sizeof(proto_draw));
            result = core_app_gpu_upload_mesh(&app->gpu, proto->vertices,
                                              proto->vertex_count, proto->indices,
                                              proto->index_count, &proto_gpu, &proto_draw);
            if (result != BREAK_RUNTIME_OK) {
                *failed_stage = "gpu_upload_prototype";
                return result;
            }
            candidate->vegetation_prototype_gpu = proto_gpu;
            candidate->vegetation_prototype_draw = proto_draw;
            candidate->vegetation_prototype.gpu[0] = proto_gpu;
            candidate->vegetation_prototype.draws[0] = proto_draw;
            candidate->vegetation_prototype_gpu_live = true;
        }
        candidate->gpu_meshes_live = true;
        candidate->mesh_device = app->gpu.device;
    }
    CoreLevel *previous = app->level;
    app->retired_level = previous;
    app->level = candidate;
    app->next_generation++;
    *failed_stage = "commit";
    *out_committed = true;
    if (previous) {
        u64 previous_generation = previous->generation;
        result = core_app_audio_enqueue(&app->audio, CORE_APP_AUDIO_STOP,
                                    previous_generation);
        if (result == BREAK_RUNTIME_OK) result = app_audio_drain(app, 1u);
        if (result != BREAK_RUNTIME_OK) return result;
        result = app_trace_flow_discard(app, previous);
        if (result != BREAK_RUNTIME_OK) return result;
        result = app_trace(app,
            "COREAPPTRACE version=1 event=level_unloaded generation=%" PRIu64 "\n",
            previous_generation);
        if (result != BREAK_RUNTIME_OK) return result;
        result = core_app_resource_retire_generation(&app->resources, previous_generation);
        if (result != BREAK_RUNTIME_OK) return result;
        core_app_level_destroy(previous);
        app->retired_level = NULL;
        result = app_trace(app,
            "COREAPPTRACE version=1 event=level_destroyed generation=%" PRIu64 "\n",
            previous_generation);
        if (result != BREAK_RUNTIME_OK) return result;
    }
    result = app_trace(app,
        "COREAPPTRACE version=1 event=level_loaded generation=%" PRIu64 "\n",
        candidate->generation);
    if (result != BREAK_RUNTIME_OK) return result;
    result = app_trace(app,
        "COREAPPTRACE version=1 event=sight generation=%" PRIu64
        " x=%.9g z=%.9g\n",
        candidate->generation,
        (double)candidate->actor_runtime->areas[candidate->sight_area].desc.center.e[0],
        (double)candidate->actor_runtime->areas[candidate->sight_area].desc.center.e[2]);
    if (result != BREAK_RUNTIME_OK) return result;
    result = app_request_skins(app, candidate);
    if (result != BREAK_RUNTIME_OK) return result;
    return core_app_render_level_committed(&app->render, &candidate->render);
}

static BreakRuntimeError core_app_level_load(CoreApp *app, const char *asset_root,
                                             const char **failed_stage,
                                             bool *out_committed,
                                             bool *out_runtime_fatal) {
    *out_committed = false;
    CoreLevel *candidate = NULL;
    CoreAppLevelSource source = {asset_root, asset_root, "level.bscn", asset_root,
                                 "level.fg", asset_root, "actors.sidecar"};
    BreakRuntimeError result = core_app_level_stage(app, &source, failed_stage,
                                                    out_runtime_fatal, &candidate);
    if (result != BREAK_RUNTIME_OK) return result;
    return core_app_level_commit(app, candidate, failed_stage, out_committed);
}

static void app_skin_pose(const CoreLevel *level, u32 object, const void **bytes,
                          u32 *byte_count) {
    if (object == 0u) {
        *bytes = level->face_morphed;
        *byte_count = (u32)sizeof(level->face_morphed);
    } else {
        *bytes = &level->chaser_position;
        *byte_count = (u32)sizeof(level->chaser_position);
    }
}

static BreakRuntimeError app_io_submit(CoreApp *app, u32 slot, u64 request, u64 generation,
                                       const void *bytes, u32 byte_count) {
    if (byte_count > CORE_APP_RESOURCE_MAX_BYTES) return BREAK_RUNTIME_INVALID;
    for (u32 i = 0u; i < CORE_APP_IO_QUEUE; ++i) {
        CoreAppIoCompletion *io = &app->io[i];
        if (io->used) continue;
        io->used = true;
        io->due_tick = app->tick + CORE_APP_IO_LATENCY_TICKS;
        io->slot = slot;
        io->request = request;
        io->generation = generation;
        io->byte_count = byte_count;
        if (byte_count > 0u) memcpy(io->bytes, bytes, byte_count);
        return BREAK_RUNTIME_OK;
    }
    return BREAK_RUNTIME_OVERLOAD;
}

static BreakRuntimeError app_io_drain(CoreApp *app) {
    for (u32 i = 0u; i < CORE_APP_IO_QUEUE; ++i) {
        CoreAppIoCompletion *io = &app->io[i];
        if (!io->used || io->due_tick > app->tick) continue;
        BreakRuntimeError done = core_app_resource_complete(
            &app->resources, io->slot, io->request, io->generation, io->bytes, io->byte_count);
        io->used = false;
        const char *outcome = done == BREAK_RUNTIME_OK ? "ok"
                            : done == BREAK_RUNTIME_STALE ? "stale" : "invalid";
        BreakRuntimeError result = app_trace(app,
            "COREAPPTRACE version=1 event=resource kind=complete tick=%u slot=%u request=%" PRIu64
            " generation=%" PRIu64 " result=%s\n", app->tick, io->slot, io->request,
            io->generation, outcome);
        if (result != BREAK_RUNTIME_OK) return result;
        if (done != BREAK_RUNTIME_OK && done != BREAK_RUNTIME_STALE) return done;
    }
    return BREAK_RUNTIME_OK;
}

static BreakRuntimeError app_request_skins(CoreApp *app, CoreLevel *level) {
    for (u32 object = 0u; object < CORE_APP_SKINNED_OBJECTS; ++object) {
        u64 request = 0u;
        BreakRuntimeError result = core_app_resource_request(
            &app->resources, level->generation, &level->skin_slot[object], &request);
        if (result != BREAK_RUNTIME_OK) return result;
        const void *bytes = NULL;
        u32 byte_count = 0u;
        app_skin_pose(level, object, &bytes, &byte_count);
        result = app_io_submit(app, level->skin_slot[object], request, level->generation,
                               bytes, byte_count);
        if (result != BREAK_RUNTIME_OK) return result;
    }
    return BREAK_RUNTIME_OK;
}

static BreakRuntimeError app_publish_skins(CoreApp *app, u32 tick) {
    CoreLevel *level = app->level;
    for (u32 object = 0u; object < CORE_APP_SKINNED_OBJECTS; ++object) {
        u32 slot = level->skin_slot[object];
        const CoreAppResourceSlot *entry = &app->resources.slots[slot];
        if (entry->state != CORE_APP_RESOURCE_LIVE || entry->generation != level->generation) {
            continue;
        }
        BreakRuntimeError result = core_app_render_record_skinned(
            &app->render, tick, level->generation, object, &app->resources, slot);
        if (result != BREAK_RUNTIME_OK) return result;
        if (entry->reloading) continue;
        const void *bytes = NULL;
        u32 byte_count = 0u;
        app_skin_pose(level, object, &bytes, &byte_count);
        if (byte_count == entry->byte_count && memcmp(bytes, entry->bytes, byte_count) == 0) {
            continue;
        }
        u64 request = 0u;
        result = core_app_resource_reload(&app->resources, slot, level->generation, &request);
        if (result != BREAK_RUNTIME_OK) return result;
        result = app_io_submit(app, slot, request, level->generation, bytes, byte_count);
        if (result != BREAK_RUNTIME_OK) return result;
    }
    return BREAK_RUNTIME_OK;
}

static BreakRuntimeError app_capture_state(const CoreLevel *level, CoreAppRuntimeState *out) {
    memset(out, 0, sizeof(*out));
    BreakRuntimeError result = core_app_simulation_user_position(level->simulation,
                                                                 &out->user_position);
    if (result == BREAK_RUNTIME_OK) {
        result = core_app_simulation_user_velocity(level->simulation, &out->user_velocity);
    }
    if (result != BREAK_RUNTIME_OK) return result;
    out->chaser_position = level->chaser_position;
    out->chaser_velocity = level->chaser_character.velocity;
    out->last_seen = level->board.last_seen;
    if (level->wall_added) out->flags |= CORE_APP_RUNTIME_FLAG_WALL_ADDED;
    if (level->wall_removed) out->flags |= CORE_APP_RUNTIME_FLAG_WALL_REMOVED;
    if (level->target_in_sight) out->flags |= CORE_APP_RUNTIME_FLAG_TARGET_IN_SIGHT;
    if (level->board.seen) out->flags |= CORE_APP_RUNTIME_FLAG_SEEN;
    if (break_game_inventory_count(level->actor_runtime, level->user, CORE_APP_FLOW_ITEM,
                                   &out->items) != BREAK_GAME_OK) {
        return BREAK_RUNTIME_FAILED;
    }
    return BREAK_RUNTIME_OK;
}

static u64 app_state_hash(const CoreAppRuntimeState *state) {
    u8 body[CORE_APP_RUNTIME_BODY_BYTES];
    app_runtime_encode_body(state, body);
    return app_fnv1a64(body, sizeof(body));
}

static BreakRuntimeError app_trace_state(CoreApp *app, const char *event, u32 tick,
                                         const CoreAppRuntimeState *state) {
    return app_trace(app,
        "COREAPPTRACE version=1 event=%s tick=%u generation=%" PRIu64
        " save_generation=%" PRIu64 " result=ok state_hash=%016" PRIx64
        " user_x=%.9g user_z=%.9g chaser_x=%.9g chaser_z=%.9g items=%u\n",
        event, tick, app->level->generation, app->save_generation, app_state_hash(state),
        (double)state->user_position.e[0], (double)state->user_position.e[2],
        (double)state->chaser_position.e[0], (double)state->chaser_position.e[2],
        state->items);
}

#define CORE_APP_CHECKPOINT_PAYLOADS 4u

static const struct {
    u32 kind;
    const char *format;
} k_checkpoint_payloads[CORE_APP_CHECKPOINT_PAYLOADS] = {
    {CORE_APP_CHECKPOINT_SCENE, "scene_%" PRIu64 ".bscn"},
    {CORE_APP_CHECKPOINT_FLOW, "flow_%" PRIu64 ".fg"},
    {CORE_APP_CHECKPOINT_ACTORS, "actors_%" PRIu64 ".sidecar"},
    {CORE_APP_CHECKPOINT_RUNTIME, "runtime_%" PRIu64 ".bin"},
};

static bool app_payload_name(u32 index, u64 generation, char out[64]) {
    int written = snprintf(out, 64, k_checkpoint_payloads[index].format, generation);
    return written > 0 && written < 64;
}

static BreakRuntimeError app_write_payload(const char *directory, u32 index, u64 generation,
                                           const u8 *bytes, usize size,
                                           CoreAppCheckpointFile *file) {
    char path[PLATFORM_FS_PATH_CAPACITY];
    memset(file, 0, sizeof(*file));
    if (!bytes || size == 0u || !app_payload_name(index, generation, file->name) ||
        !app_path(path, directory, file->name)) {
        return BREAK_RUNTIME_INVALID;
    }
    PlatformAtomicWriter *writer = platform_atomic_writer_open(path);
    if (!writer) return BREAK_RUNTIME_FAILED;
    if (!platform_atomic_writer_write(writer, bytes, size)) {
        platform_atomic_writer_abort(writer);
        return BREAK_RUNTIME_FAILED;
    }
    if (platform_atomic_writer_commit_status(writer) ==
        PLATFORM_ATOMIC_NOT_COMMITTED_TARGET_UNCHANGED) {
        return BREAK_RUNTIME_FAILED;
    }
    file->kind = k_checkpoint_payloads[index].kind;
    file->size = (u64)size;
    file->hash = app_fnv1a64(bytes, size);
    return BREAK_RUNTIME_OK;
}

static void app_remove_payloads(const char *directory, const CoreAppCheckpointFile *files,
                                u32 count) {
    char path[PLATFORM_FS_PATH_CAPACITY];
    for (u32 i = 0u; i < count; ++i) {
        if (app_path(path, directory, files[i].name)) (void)remove(path);
    }
}

static BreakRuntimeError app_save_checkpoint(CoreApp *app, u32 tick) {
    const char *directory = app->config.checkpoint_dir;
    const CoreLevel *level = app->level;
    CoreAppRuntimeState state;
    BreakRuntimeError result = app_capture_state(level, &state);
    if (result != BREAK_RUNTIME_OK) return result;
    CoreAppCheckpointFile previous;
    u64 committed_generation = 0u;
    bool has_previous = core_app_checkpoint_find(directory, CORE_APP_CHECKPOINT_RUNTIME,
                                                 &previous, &committed_generation) ==
                        BREAK_RUNTIME_OK;
    if (!has_previous) committed_generation = app->save_generation;
    u64 next = committed_generation + 1u;

    u8 runtime[CORE_APP_RUNTIME_FILE_BYTES];
    memcpy(runtime, k_runtime_magic, sizeof(k_runtime_magic));
    app_put32(runtime + 8u, CORE_APP_RUNTIME_STATE_VERSION);
    app_put32(runtime + 12u, CORE_APP_RUNTIME_BODY_BYTES);
    app_runtime_encode_body(&state, runtime + CORE_APP_RUNTIME_HEADER_BYTES);
    const u8 *payloads[CORE_APP_CHECKPOINT_PAYLOADS] = {
        level->scene_bytes, level->flow_bytes, level->actor_bytes, runtime};
    const usize sizes[CORE_APP_CHECKPOINT_PAYLOADS] = {
        level->scene_size, level->flow_size, level->actor_size, sizeof(runtime)};

    CoreAppCheckpointFile files[CORE_APP_CHECKPOINT_PAYLOADS];
    u32 written = 0u;
    bool ok = platform_mkdir(directory);
    for (u32 i = 0u; ok && i < CORE_APP_CHECKPOINT_PAYLOADS; ++i) {
        ok = app_write_payload(directory, i, next, payloads[i], sizes[i], &files[i]) ==
             BREAK_RUNTIME_OK;
        if (ok) written++;
    }
    CoreAppCheckpointCommitResult commit = CORE_APP_CHECKPOINT_COMMIT_NOT_COMMITTED;
    if (ok) {
        ok = core_app_checkpoint_write_manifest_ex(directory, files, written, next, &commit) ==
             BREAK_RUNTIME_OK;
    }
    if (!ok) {
        app_remove_payloads(directory, files, written);
        return app_trace(app,
            "COREAPPTRACE version=1 event=save tick=%u generation=%" PRIu64
            " save_generation=%" PRIu64 " result=failed\n", tick, level->generation,
            app->save_generation);
    }
    app->save_generation = next;
    if (has_previous && committed_generation != next) {
        CoreAppCheckpointFile stale[CORE_APP_CHECKPOINT_PAYLOADS];
        u32 stale_count = 0u;
        for (u32 i = 0u; i < CORE_APP_CHECKPOINT_PAYLOADS; ++i) {
            if (app_payload_name(i, committed_generation, stale[stale_count].name)) {
                stale_count++;
            }
        }
        app_remove_payloads(directory, stale, stale_count);
    }
    return app_trace_state(app, "save", tick, &state);
}

static BreakRuntimeError app_apply_state(CoreLevel *level, const CoreAppRuntimeState *state) {
    bool saved_added = (state->flags & CORE_APP_RUNTIME_FLAG_WALL_ADDED) != 0u;
    bool saved_removed = (state->flags & CORE_APP_RUNTIME_FLAG_WALL_REMOVED) != 0u;
    if ((level->wall_added && !saved_added) || (level->wall_removed && !saved_removed)) {
        return BREAK_RUNTIME_REJECTED;
    }
    u32 items = 0u;
    if (break_game_inventory_count(level->actor_runtime, level->user, CORE_APP_FLOW_ITEM,
                                   &items) != BREAK_GAME_OK) {
        return BREAK_RUNTIME_FAILED;
    }
    if (items > state->items) return BREAK_RUNTIME_REJECTED;
    if (items < state->items &&
        break_game_inventory_add(level->actor_runtime, level->user, CORE_APP_FLOW_ITEM,
                                 state->items - items) != BREAK_GAME_OK) {
        return BREAK_RUNTIME_REJECTED;
    }
    level->user_items = state->items;
    BreakRuntimeError result = core_app_simulation_restore_user(
        level->simulation, state->user_position, state->user_velocity);
    if (result != BREAK_RUNTIME_OK) return result;
    if (saved_added && !level->wall_added) {
        BreakAiObstacleDesc wall = {1.0f, 1.0f, 4.0f, 2.0f};
        if (break_ai_obstacle_add(level->ai, &wall, &level->wall) != BREAK_NAV_OK) {
            return BREAK_RUNTIME_FAILED;
        }
        level->wall_body = physics_body_create(level->physics,
            vec3(2.5f, 1.0f, 1.5f), vec3(1.5f, 1.0f, 0.5f), 0.0f, true, 0u);
        if (!physics_body_handle_is_valid(level->wall_body)) return BREAK_RUNTIME_FAILED;
        level->wall_added = true;
    }
    if (saved_removed && !level->wall_removed) {
        if (break_ai_obstacle_remove(level->ai, level->wall) != BREAK_NAV_OK) {
            return BREAK_RUNTIME_FAILED;
        }
        level->wall_removed = true;
    }
    level->chaser_character = character_create(state->chaser_position, 0.4f, 1.0f);
    level->chaser_character.velocity = state->chaser_velocity;
    level->chaser_position = state->chaser_position;
    BreakAiAgentDesc agent;
    memset(&agent, 0, sizeof(agent));
    agent.position = state->chaser_position;
    agent.velocity = state->chaser_velocity;
    agent.radius = 0.4f;
    agent.max_speed = 3.0f;
    if (break_ai_agent_update(level->ai, level->chaser, &agent) != BREAK_NAV_OK) {
        return BREAK_RUNTIME_FAILED;
    }
    level->target_in_sight = (state->flags & CORE_APP_RUNTIME_FLAG_TARGET_IN_SIGHT) != 0u;
    level->board.seen = (state->flags & CORE_APP_RUNTIME_FLAG_SEEN) != 0u;
    level->board.last_seen = state->last_seen;
    level->board.target = level->board.seen ? level->user : (Entity){0u, 0u};
    memset(&level->chase_path, 0, sizeof(level->chase_path));
    memset(&level->follower, 0, sizeof(level->follower));
    level->chase_nav_version = break_ai_nav_version(level->ai);
    level->previous_user_position = state->user_position;
    level->previous_user_position_valid = true;
    return BREAK_RUNTIME_OK;
}

static BreakRuntimeError app_trace_load_rejected(CoreApp *app, u32 tick, const char *stage) {
    return app_trace(app,
        "COREAPPTRACE version=1 event=load_rejected tick=%u generation=%" PRIu64
        " stage=%s\n", tick, app->level ? app->level->generation : 0u, stage);
}

static BreakRuntimeError app_load_checkpoint(CoreApp *app, u32 tick) {
    CoreAppCheckpointFile file;
    u64 generation = 0u;
    CoreAppRuntimeState state;
    u8 *bytes = NULL;
    usize size = 0u;
    const char *directory = app->config.checkpoint_dir;
    CoreAppCheckpointFile scene;
    CoreAppCheckpointFile flow;
    CoreAppCheckpointFile actors;
    u64 other = 0u;
    BreakRuntimeError result = core_app_checkpoint_find(
        directory, CORE_APP_CHECKPOINT_RUNTIME, &file, &generation);
    if (result == BREAK_RUNTIME_OK) {
        result = core_app_checkpoint_find(directory, CORE_APP_CHECKPOINT_SCENE, &scene, &other);
    }
    if (result == BREAK_RUNTIME_OK) {
        result = core_app_checkpoint_find(directory, CORE_APP_CHECKPOINT_FLOW, &flow, &other);
    }
    if (result == BREAK_RUNTIME_OK) {
        result = core_app_checkpoint_find(directory, CORE_APP_CHECKPOINT_ACTORS, &actors,
                                          &other);
    }
    if (result == BREAK_RUNTIME_OK &&
        !app_read_asset(app->config.checkpoint_dir, file.name, CORE_APP_RUNTIME_FILE_BYTES,
                        &bytes, &size)) {
        result = BREAK_RUNTIME_INVALID;
    }
    if (result == BREAK_RUNTIME_OK &&
        (size != file.size || app_fnv1a64(bytes, size) != file.hash)) {
        result = BREAK_RUNTIME_INVALID;
    }
    if (result == BREAK_RUNTIME_OK) result = app_runtime_decode(bytes, size, &state);
    free(bytes);
    if (result != BREAK_RUNTIME_OK) return app_trace_load_rejected(app, tick, "checkpoint");

    const char *asset_root = app->level_asset_root ? app->level_asset_root
                                                   : app->config.asset_root;
    const char *stage = "bscn";
    bool runtime_fatal = false;
    CoreLevel *candidate = NULL;
    CoreAppLevelSource source = {asset_root, directory, scene.name, directory, flow.name,
                                 directory, actors.name};
    result = core_app_level_stage(app, &source, &stage, &runtime_fatal, &candidate);
    if (result != BREAK_RUNTIME_OK) {
        if (runtime_fatal) return result;
        return app_trace_load_rejected(app, tick, stage);
    }
    result = app_apply_state(candidate, &state);
    if (result != BREAK_RUNTIME_OK) {
        core_app_level_destroy(candidate);
        return app_trace_load_rejected(app, tick, "state");
    }
    bool committed = false;
    result = core_app_level_commit(app, candidate, &stage, &committed);
    if (result != BREAK_RUNTIME_OK) {
        if (!committed) core_app_level_destroy(candidate);
        return result;
    }
    app->level_asset_root = asset_root;
    app->save_generation = generation;
    CoreAppRuntimeState restored;
    result = app_capture_state(app->level, &restored);
    if (result != BREAK_RUNTIME_OK) return result;
    return app_trace_state(app, "load", tick, &restored);
}

static BreakRuntimeError core_app_unload_level(CoreApp *app, bool with_audio) {
    CoreLevel *level = app->level;
    if (!level) return BREAK_RUNTIME_OK;
    BreakRuntimeError result = BREAK_RUNTIME_OK;
    if (with_audio) {
        result = core_app_audio_enqueue(&app->audio, CORE_APP_AUDIO_STOP, level->generation);
        if (result == BREAK_RUNTIME_OK) result = app_audio_drain(app, 1u);
    }
    if (result != BREAK_RUNTIME_OK) return result;
    result = app_trace_flow_discard(app, level);
    if (result != BREAK_RUNTIME_OK) return result;
    app->level = NULL;
    u64 generation = level->generation;
    result = core_app_resource_retire_generation(&app->resources, generation);
    if (result != BREAK_RUNTIME_OK) return result;
    core_app_level_destroy(level);
    result = app_trace(app,
        "COREAPPTRACE version=1 event=level_unloaded generation=%" PRIu64 "\n",
        generation);
    BreakRuntimeError destroyed_result = app_trace(app,
        "COREAPPTRACE version=1 event=level_destroyed generation=%" PRIu64 "\n",
        generation);
    return result != BREAK_RUNTIME_OK ? result : destroyed_result;
}

/* The null backend has no trace sink, so draining dispatches on the started
 * mode instead of always assuming a record trace is present. */
static BreakRuntimeError app_audio_drain(CoreApp *app, u32 budget) {
    if (app->audio.mode == CORE_APP_AUDIO_BACKEND_RECORD) {
        return core_app_audio_drain_record(&app->audio, budget);
    }
    return core_app_audio_drain_null(&app->audio, budget);
}

static BreakRuntimeError core_app_audio_stop_admission_cb(void *user) {
    return core_app_audio_stop_admission(&((CoreApp *)user)->audio);
}

static BreakRuntimeError core_app_audio_stop_producers_cb(void *user) {
    return core_app_audio_stop_producers(&((CoreApp *)user)->audio);
}

static BreakRuntimeError core_app_audio_close_queues_cb(void *user) {
    return core_app_audio_close_queues(&((CoreApp *)user)->audio);
}

static BreakRuntimeError core_app_audio_drain_cb(void *user) {
    return app_audio_drain((CoreApp *)user, CORE_APP_AUDIO_QUEUE_CAPACITY);
}

static BreakRuntimeError core_app_audio_join_cb(void *user) {
    return core_app_audio_join(&((CoreApp *)user)->audio);
}

static BreakRuntimeError core_app_audio_destroy_cb(void *user) {
    CoreApp *app = (CoreApp *)user;
    BreakRuntimeError result = core_app_audio_destroy(&app->audio);
    if (result == BREAK_RUNTIME_OK) app->audio_live = false;
    return result;
}

static BreakRuntimeError core_app_render_stop_admission_cb(void *user) {
    return core_app_render_stop_admission(&((CoreApp *)user)->render);
}

static BreakRuntimeError core_app_render_stop_producers_cb(void *user) {
    return core_app_render_stop_producers(&((CoreApp *)user)->render);
}

static BreakRuntimeError core_app_render_idle_cb(void *user) {
    return core_app_render_idle(&((CoreApp *)user)->render);
}

static BreakRuntimeError core_app_render_destroy_cb(void *user) {
    CoreApp *app = (CoreApp *)user;
    BreakRuntimeError result = core_app_render_destroy(&app->render);
    if (result == BREAK_RUNTIME_OK) app->render_live = false;
    return result;
}

static BreakRuntimeError app_level_stop_producers_cb(void *user) {
    (void)user;
    return BREAK_RUNTIME_OK;
}

static BreakRuntimeError app_level_drain_cb(void *user) {
    CoreApp *app = (CoreApp *)user;
    if (app->level && app->level->request) {
        break_runtime_io_request_release(app->level->request);
        app->level->request = NULL;
    }
    return BREAK_RUNTIME_OK;
}

static BreakRuntimeError core_app_stop_io(CoreApp *app) {
    if (!app->io_running) return BREAK_RUNTIME_OK;
    BreakRuntimeError result = break_runtime_io_shutdown(CORE_APP_IO_TIMEOUT_MS);
    if (result != BREAK_RUNTIME_OK) return result;
    app->io_running = false;
    BreakRuntimeIoStats stats;
    memset(&stats, 0, sizeof(stats));
    result = break_runtime_io_stats(&stats);
    if (result != BREAK_RUNTIME_OK || stats.active != 0u) return BREAK_RUNTIME_FAILED;
    return app_trace(app, "COREAPPTRACE version=1 event=io_stopped active=0\n");
}

static BreakRuntimeError app_level_join_cb(void *user) {
    return core_app_stop_io((CoreApp *)user);
}

static BreakRuntimeError app_level_destroy_cb(void *user) {
    CoreApp *app = (CoreApp *)user;
    BreakRuntimeError result = core_app_unload_level(app, false);
    if (app->vfs && !app->io_running) {
        vfs_destroy(app->vfs);
        app->vfs = NULL;
    }
    return result;
}

static BreakRuntimeError app_register_subsystems(CoreApp *app) {
    BreakRuntimeCoordinatorConfig config = {4u};
    BreakRuntimeError result = break_runtime_coordinator_create(&config,
                                                                &app->coordinator);
    if (result != BREAK_RUNTIME_OK) return result;
    BreakRuntimeSubsystem subsystems[4];
    memset(subsystems, 0, sizeof(subsystems));
    subsystems[0].name = "network";
    subsystems[1].name = "audio";
    subsystems[1].user_data = app;
    subsystems[1].stop_admission = core_app_audio_stop_admission_cb;
    subsystems[1].stop_producers = core_app_audio_stop_producers_cb;
    subsystems[1].close_queues = core_app_audio_close_queues_cb;
    subsystems[1].drain = core_app_audio_drain_cb;
    subsystems[1].join = core_app_audio_join_cb;
    subsystems[1].destroy = core_app_audio_destroy_cb;
    subsystems[2].name = "render";
    subsystems[2].user_data = app;
    subsystems[2].stop_admission = core_app_render_stop_admission_cb;
    subsystems[2].stop_producers = core_app_render_stop_producers_cb;
    subsystems[2].join = core_app_render_idle_cb;
    subsystems[2].destroy = core_app_render_destroy_cb;
    subsystems[3].name = "level";
    subsystems[3].user_data = app;
    subsystems[3].stop_producers = app_level_stop_producers_cb;
    subsystems[3].drain = app_level_drain_cb;
    subsystems[3].join = app_level_join_cb;
    subsystems[3].destroy = app_level_destroy_cb;
    for (u32 i = 0u; i < 4u; ++i) {
        result = break_runtime_coordinator_register_subsystem(app->coordinator,
                                                              &subsystems[i]);
        if (result != BREAK_RUNTIME_OK) return result;
    }
    return BREAK_RUNTIME_OK;
}

static bool app_scenario_supported(const CoreAppScenario *scenario, bool has_checkpoint) {
    if (scenario->fixed_dt_ns != CORE_APP_FIXED_DT_NS) return false;
    for (u32 i = 0u; i < scenario->event_count; ++i) {
        switch (scenario->events[i].kind) {
        case CORE_APP_SCENARIO_SAVE:
        case CORE_APP_SCENARIO_LOAD:
            if (!has_checkpoint) return false;
            break;
        case CORE_APP_SCENARIO_KEY:
        case CORE_APP_SCENARIO_TOUCH:
        case CORE_APP_SCENARIO_PAD:
        case CORE_APP_SCENARIO_LEVEL:
        case CORE_APP_SCENARIO_UNLOAD:
        case CORE_APP_SCENARIO_SCREENSHOT:
        case CORE_APP_SCENARIO_QUIT:
            break;
        default:
            return false;
        }
    }
    return true;
}

static const char *app_input_status_name(InputExtResult result) {
    switch (result) {
    case INPUT_EXT_OK: return "ok";
    case INPUT_EXT_INVALID: return "invalid";
    case INPUT_EXT_OVERLOAD: return "overload";
    case INPUT_EXT_STALE: return "stale";
    case INPUT_EXT_DISCONNECTED: return "disconnected";
    case INPUT_EXT_UNSUPPORTED: return "unsupported";
    case INPUT_EXT_PENDING: return "pending";
    case INPUT_EXT_REJECTED: return "rejected";
    default: return "failed";
    }
}

static BreakRuntimeError app_tick_level(CoreApp *app, u32 tick,
                                        const CoreAppInputFrame *frame) {
    CoreLevel *level = app->level;
    BreakRuntimeError result;
    break_game_tick(level->actor_runtime, CORE_APP_FIXED_DT);
    BreakFlowError flow = break_flow_runtime_tick(level->flow);
    if (flow != BREAK_FLOW_OK) {
        result = app_trace(app,
            "COREAPPTRACE version=1 event=flow kind=tick_failed generation=%" PRIu64
            " tick=%u status=%u\n", level->generation, tick, (unsigned)flow);
        if (result != BREAK_RUNTIME_OK) return result;
    }
    u32 items = 0u;
    if (break_game_inventory_count(level->actor_runtime, level->user,
                                   CORE_APP_FLOW_ITEM, &items) != BREAK_GAME_OK) {
        return BREAK_RUNTIME_FAILED;
    }
    if (items != level->user_items) {
        level->user_items = items;
        result = app_trace(app,
            "COREAPPTRACE version=1 event=item generation=%" PRIu64
            " tick=%u entity=%u item=%u count=%u\n", level->generation, tick,
            level->user.index, CORE_APP_FLOW_ITEM, items);
        if (result != BREAK_RUNTIME_OK) return result;
    }
    result = app_tick_vehicle(app, tick, frame);
    if (result != BREAK_RUNTIME_OK) return result;
    if (!level->vehicle.occupied) {
        result = core_app_simulation_tick(level->simulation, frame);
        if (result != BREAK_RUNTIME_OK) return result;
    }
    result = app_tick_chaser(app, tick);
    if (result != BREAK_RUNTIME_OK) return result;
    physics_step(level->physics, CORE_APP_FIXED_DT);
    {
        RigidBody *chassis = physics_body_resolve(level->physics, level->vehicle.chassis);
        if (!chassis) return BREAK_RUNTIME_STALE;
        if (level->vehicle.occupied) {
            result = core_app_simulation_place_user(level->simulation, chassis->position);
            if (result != BREAK_RUNTIME_OK) return result;
        }
        u32 grounded = 0u;
        for (u32 wheel = 0u; wheel < 4u; ++wheel) {
            if (level->vehicle.wheels[wheel].grounded) grounded++;
        }
        result = app_trace(app,
            "COREAPPTRACE version=1 event=vehicle tick=%u generation=%" PRIu64
            " occupied=%u throttle=%.9g grounded=%u x=%.9g z=%.9g\n", tick,
            level->generation, level->vehicle.occupied ? 1u : 0u,
            (double)level->vehicle.control.throttle, grounded,
            (double)chassis->position.e[0], (double)chassis->position.e[2]);
        if (result != BREAK_RUNTIME_OK) return result;
    }
    result = app_tick_ragdoll(app, tick, frame);
    if (result != BREAK_RUNTIME_OK) return result;
    BreakGameError area = break_game_area_tick(level->actor_runtime);
    if (area != BREAK_GAME_OK && area != BREAK_GAME_OVERLOAD) return BREAK_RUNTIME_FAILED;
    Vec3 position;
    result = core_app_simulation_user_position(level->simulation, &position);
    if (result != BREAK_RUNTIME_OK) return result;
    result = app_trace(app,
        "COREAPPTRACE version=1 event=user tick=%u generation=%" PRIu64
        " x=%.9g y=%.9g z=%.9g\n", tick, level->generation,
        (double)position.e[0], (double)position.e[1], (double)position.e[2]);
    if (result != BREAK_RUNTIME_OK) return result;
    f32 speed = 0.0f;
    if (level->previous_user_position_valid) {
        f32 dx = position.e[0] - level->previous_user_position.e[0];
        f32 dz = position.e[2] - level->previous_user_position.e[2];
        speed = sqrtf(dx * dx + dz * dz) / CORE_APP_FIXED_DT;
    }
    level->previous_user_position = position;
    level->previous_user_position_valid = true;
    anim_loco1d_apply(&level->loco, &level->locomotion, speed);
    f32 walk_weight = 0.0f;
    f32 run_weight = 0.0f;
    for (u32 layer = 0u; layer < 2u; layer++) {
        if (level->locomotion.layers[layer].clip_index == 0u) {
            walk_weight = level->locomotion.layers[layer].weight;
        } else if (level->locomotion.layers[layer].clip_index == 1u) {
            run_weight = level->locomotion.layers[layer].weight;
        }
    }
    result = app_trace(app,
        "COREAPPTRACE version=1 event=loco tick=%u generation=%" PRIu64
        " speed=%.9g walk_weight=%.9g run_weight=%.9g\n", tick, level->generation,
        (double)speed, (double)walk_weight, (double)run_weight);
    if (result != BREAK_RUNTIME_OK) return result;
    {
        f32 weights[1] = {0.0f};
        f32 time = (f32)tick * CORE_APP_FIXED_DT;
        if (time > 1.0f) time = 1.0f;
        if (!anim_facial_evaluate(&level->facial, &level->face_morphs, "lift", time,
                                  weights, 1u)) {
            return BREAK_RUNTIME_FAILED;
        }
        if (!anim_morph_evaluate_skinned(&level->face_morphs, level->face_bind, weights, 1u,
                                         level->face_morphed, sizeof(level->face_morphed))) {
            return BREAK_RUNTIME_FAILED;
        }
        Mat4 skin = mat4_identity();
        skin.e[3][0] = 3.0f;
        if (!lod_skin_positions((const f32 *)level->face_morphed, 1u, &skin, 1u,
                                level->face_skinned)) {
            return BREAK_RUNTIME_FAILED;
        }
        result = app_trace(app,
            "COREAPPTRACE version=1 event=facial tick=%u generation=%" PRIu64
            " x=%.9g y=%.9g\n", tick, level->generation,
            (double)level->face_skinned[0], (double)level->face_skinned[1]);
        if (result != BREAK_RUNTIME_OK) return result;
    }
    while (level->pending_area_enters > 0u) {
        level->pending_area_enters--;
        flow = break_flow_runtime_post(level->flow, CORE_APP_AREA_FLOW_EVENT,
                                       level->user, 1.0f);
        if (flow == BREAK_FLOW_OK) {
            result = app_trace(app,
                "COREAPPTRACE version=1 event=flow kind=post key=%u generation=%" PRIu64
                " tick=%u\n", CORE_APP_AREA_FLOW_EVENT, level->generation, tick);
        } else {
            result = app_trace(app,
                "COREAPPTRACE version=1 event=flow kind=post_failed key=%u generation=%" PRIu64
                " tick=%u status=%u\n", CORE_APP_AREA_FLOW_EVENT, level->generation,
                tick, (unsigned)flow);
        }
        if (result != BREAK_RUNTIME_OK) return result;
        BreakRuntimeError request = core_app_input_request_area_haptic(
            app->input, CORE_APP_HAPTIC_PAD, CORE_APP_HAPTIC_STRENGTH,
            CORE_APP_HAPTIC_STRENGTH, CORE_APP_HAPTIC_DURATION_MS);
        if (request == BREAK_RUNTIME_INVALID) return request;
        CoreAppInputFrame after;
        result = core_app_input_frame(app->input, &after);
        if (result != BREAK_RUNTIME_OK) return result;
        result = app_trace(app,
            "COREAPPTRACE version=1 event=haptic area=%u generation=%" PRIu64
            " tick=%u status=%s request=%" PRIu64 "\n", level->trigger_area,
            level->generation, tick, app_input_status_name(after.haptic_status),
            after.haptic_request_id);
        if (result != BREAK_RUNTIME_OK) return result;
    }
    BreakGameLuaActorStats user_stats;
    BreakGameLuaActorStats chaser_stats;
    if (break_game_lua_actor_stats(level->adapter, level->user, &user_stats) !=
            BREAK_LUA_OK ||
        break_game_lua_actor_stats(level->adapter, level->chaser, &chaser_stats) !=
            BREAK_LUA_OK) {
        return BREAK_RUNTIME_FAILED;
    }
    return app_trace(app,
        "COREAPPTRACE version=1 event=actors tick=%u generation=%" PRIu64
        " user_ticks=%" PRIu64 " user_failures=%" PRIu64
        " chaser_ticks=%" PRIu64 " chaser_failures=%" PRIu64
        " items=%u flow_pending=%u\n", tick, level->generation,
        user_stats.ticks, user_stats.failures, chaser_stats.ticks,
        chaser_stats.failures, level->user_items,
        break_flow_runtime_pending_count(level->flow));
}

static void app_rollback(CoreApp *app) {
    if (app->coordinator &&
        break_runtime_coordinator_state(app->coordinator) != BREAK_RUNTIME_STOPPED) {
        (void)break_runtime_coordinator_fail(app->coordinator, BREAK_RUNTIME_FAILED);
    }
    if (app->audio_live) {
        (void)core_app_audio_stop_admission(&app->audio);
        (void)core_app_audio_stop_producers(&app->audio);
        (void)core_app_audio_close_queues(&app->audio);
        (void)app_audio_drain(app, CORE_APP_AUDIO_QUEUE_CAPACITY);
        (void)core_app_audio_join(&app->audio);
        (void)core_app_audio_destroy(&app->audio);
        app->audio_live = false;
    }
    if (app->render_live) {
        (void)core_app_render_stop_admission(&app->render);
        (void)core_app_render_stop_producers(&app->render);
        (void)core_app_render_idle(&app->render);
        (void)core_app_render_destroy(&app->render);
        app->render_live = false;
    }
    if (app->level) {
        CoreLevel *level = app->level;
        app->level = NULL;
        u64 generation = level->generation;
        core_app_level_destroy(level);
        (void)app_trace(app,
            "COREAPPTRACE version=1 event=level_destroyed generation=%" PRIu64 "\n",
            generation);
    }
    if (app->retired_level) {
        CoreLevel *level = app->retired_level;
        app->retired_level = NULL;
        u64 generation = level->generation;
        core_app_level_destroy(level);
        (void)app_trace(app,
            "COREAPPTRACE version=1 event=level_destroyed generation=%" PRIu64 "\n",
            generation);
    }
    /* Levels release their device meshes, so the device must outlive them. */
    if (app->gpu.live) {
        (void)core_app_gpu_destroy(&app->gpu);
    }
    (void)core_app_stop_io(app);
    if (app->vfs && !app->io_running) {
        vfs_destroy(app->vfs);
        app->vfs = NULL;
    }
    (void)app_trace(app, "COREAPPTRACE version=1 event=runtime_failed\n");
}

BreakRuntimeError core_app_run(const CoreAppConfig *config, int *out_exit_code) {
    if (!out_exit_code) return BREAK_RUNTIME_INVALID;
    *out_exit_code = 2;
    if (!config) return BREAK_RUNTIME_INVALID;
    bool optional_device = config->audio_mode == CORE_APP_AUDIO_DEVICE && !config->require_device;
    bool gpu_lane = config->render_mode == CORE_APP_RENDER_VULKAN ||
                    config->render_mode == CORE_APP_RENDER_OPENGL;
    if ((config->render_mode != CORE_APP_RENDER_RECORD && !gpu_lane) || !config->fixed_step ||
        (config->audio_mode != CORE_APP_AUDIO_RECORD &&
         config->audio_mode != CORE_APP_AUDIO_NULL && !optional_device) ||
        config->network || !config->asset_root ||
        !config->scenario_path || !config->trace_path ||
        (config->screenshot_path && !gpu_lane) ||
        (config->checkpoint_dir && config->checkpoint_dir[0] == '\0')) {
        fprintf(stderr, "core_app: stage=config unsupported lifecycle configuration\n");
        return BREAK_RUNTIME_FAILED;
    }
    CoreApp *app = (CoreApp *)calloc(1u, sizeof(*app));
    if (!app) return BREAK_RUNTIME_OOM;
    app->config = *config;
    app->next_generation = 1u;
    const char *stage = "scenario";
    BreakRuntimeError result = BREAK_RUNTIME_FAILED;

    app->trace = fopen(config->trace_path, "wb");
    if (!app->trace) goto finished;
    if (core_app_scenario_load(config->scenario_path, &app->scenario) !=
            CORE_APP_SCENARIO_OK ||
        !app_scenario_supported(&app->scenario, config->checkpoint_dir != NULL)) {
        result = BREAK_RUNTIME_FAILED;
        goto finished;
    }
    app->input = core_app_input_create();
    if (!app->input) {
        result = BREAK_RUNTIME_OOM;
        goto finished;
    }

    stage = "io";
    app->vfs = vfs_create();
    if (!app->vfs) goto finished;
    BreakRuntimeIoConfig io_config;
    memset(&io_config, 0, sizeof(io_config));
    io_config.vfs = app->vfs;
    io_config.worker_count = 1u;
    io_config.request_capacity = 4u;
    result = break_runtime_io_init(&io_config);
    if (result != BREAK_RUNTIME_OK) goto finished;
    app->io_running = true;

    stage = "render_start";
    result = core_app_render_start(&app->render, app->trace);
    if (result != BREAK_RUNTIME_OK) goto finished;
    app->render_live = true;
    app->screenshot_path = config->screenshot_path;
    if (gpu_lane) {
        CoreAppGpuConfig gpu_config;
        memset(&gpu_config, 0, sizeof(gpu_config));
        gpu_config.backend = config->render_mode == CORE_APP_RENDER_VULKAN
                                 ? CORE_APP_GPU_VULKAN : CORE_APP_GPU_OPENGL;
        gpu_config.width = 640u;
        gpu_config.height = 480u;
        gpu_config.require_device = config->require_device;
        stage = "gpu_start";
        result = core_app_gpu_create(&app->gpu, &gpu_config, app->trace);
        if (result == BREAK_RUNTIME_UNAVAILABLE) {
            (void)app_trace(app,
                "COREAPPTRACE version=1 event=gpu result=unavailable backend=%s\n",
                gpu_config.backend == CORE_APP_GPU_VULKAN ? "vulkan" : "opengl");
            goto finished;
        }
        if (result != BREAK_RUNTIME_OK) goto finished;
        (void)app_trace(app,
            "COREAPPTRACE version=1 event=gpu result=ready backend=%s device=%s"
            " width=%u height=%u\n",
            app->gpu.backend_name, app->gpu.device_name, app->gpu.width, app->gpu.height);
    }
    stage = "audio_start";
    if (config->audio_mode == CORE_APP_AUDIO_NULL) {
        result = core_app_audio_start_null(&app->audio);
    } else if (config->audio_mode == CORE_APP_AUDIO_DEVICE) {
        result = core_app_audio_start_device(&app->audio, app->trace, config->require_device);
        if (result == BREAK_RUNTIME_UNAVAILABLE && !config->require_device) {
            result = BREAK_RUNTIME_OK;
        }
    } else {
        result = core_app_audio_start(&app->audio, app->trace);
    }
    if (result != BREAK_RUNTIME_OK) goto finished;
    app->audio_live = true;
    stage = "coordinator";
    result = app_register_subsystems(app);
    if (result != BREAK_RUNTIME_OK) goto finished;
    result = break_runtime_coordinator_start(app->coordinator);
    if (result != BREAK_RUNTIME_OK) goto finished;
    result = app_trace(app, "COREAPPTRACE version=1 event=runtime_running\n");
    if (result != BREAK_RUNTIME_OK) goto finished;

    bool ended = false;
    u32 event_index = 0u;
    for (u32 tick = 1u; !ended; ++tick) {
        if (config->max_frames != 0u && tick > config->max_frames) {
            ended = true;
            break;
        }
        stage = "input";
        result = core_app_input_begin_tick(app->input, tick,
                                           (u64)tick * CORE_APP_FIXED_DT_NS / 1000000u);
        if (result != BREAK_RUNTIME_OK) goto finished;
        bool quit = false;
        while (event_index < app->scenario.event_count &&
               app->scenario.events[event_index].tick == tick) {
            const CoreAppScenarioEvent *event = &app->scenario.events[event_index++];
            if (event->kind == CORE_APP_SCENARIO_KEY ||
                event->kind == CORE_APP_SCENARIO_TOUCH ||
                event->kind == CORE_APP_SCENARIO_PAD) {
                stage = "input";
                result = core_app_input_apply(app->input, event);
                if (result != BREAK_RUNTIME_OK) goto finished;
            } else if (event->kind == CORE_APP_SCENARIO_LEVEL) {
                const char *asset_root = event->path[0] != '\0'
                    ? event->path : config->asset_root;
                bool had_level = app->level != NULL;
                const char *load_stage = "bscn";
                bool committed = false;
                bool runtime_fatal = false;
                result = core_app_level_load(app, asset_root, &load_stage, &committed,
                                             &runtime_fatal);
                if (result == BREAK_RUNTIME_OK) app->level_asset_root = asset_root;
                if (result != BREAK_RUNTIME_OK) {
                    u64 generation = app->level ? app->level->generation : 0u;
                    if (committed || runtime_fatal) {
                        (void)app_trace(app,
                            "COREAPPTRACE version=1 event=runtime_fault stage=%s generation=%" PRIu64
                            "\n", load_stage, generation);
                        stage = load_stage;
                        goto finished;
                    }
                    (void)app_trace(app,
                        "COREAPPTRACE version=1 event=load_rejected generation=%" PRIu64
                        " stage=%s\n", generation, load_stage);
                    fprintf(stderr, "core_app: stage=%s level load rejected\n", load_stage);
                    if (!had_level) {
                        stage = load_stage;
                        goto finished;
                    }
                }
            } else if (event->kind == CORE_APP_SCENARIO_UNLOAD) {
                result = core_app_unload_level(app, true);
                if (result != BREAK_RUNTIME_OK) {
                    stage = "unload";
                    goto finished;
                }
            } else if (event->kind == CORE_APP_SCENARIO_SAVE ||
                       event->kind == CORE_APP_SCENARIO_LOAD) {
                bool save = event->kind == CORE_APP_SCENARIO_SAVE;
                stage = save ? "save" : "load";
                if (save && !app->level) {
                    result = app_trace(app,
                        "COREAPPTRACE version=1 event=%s_rejected tick=%u generation=0"
                        " stage=level\n", save ? "save" : "load", tick);
                } else {
                    result = save ? app_save_checkpoint(app, tick)
                                  : app_load_checkpoint(app, tick);
                }
                if (result != BREAK_RUNTIME_OK) goto finished;
            } else if (event->kind == CORE_APP_SCENARIO_SCREENSHOT) {
                if (app->gpu.live) {
                    app->screenshot_next = true;
                } else {
                    result = app_trace(app,
                        "COREAPPTRACE version=1 event=screenshot_rejected tick=%u"
                        " stage=device\n", tick);
                    if (result != BREAK_RUNTIME_OK) goto finished;
                }
            } else if (event->kind == CORE_APP_SCENARIO_QUIT) {
                quit = true;
            } else {
                stage = "scenario";
                result = BREAK_RUNTIME_FAILED;
                goto finished;
            }
        }
        if (quit) {
            ended = true;
            break;
        }
        app->tick = tick;
        stage = "resource";
        result = app_io_drain(app);
        if (result != BREAK_RUNTIME_OK) goto finished;
        if (app->level) {
            CoreAppInputFrame input_frame;
            stage = "simulation";
            result = core_app_input_frame(app->input, &input_frame);
            if (result == BREAK_RUNTIME_OK) result = app_tick_level(app, tick, &input_frame);
            if (result != BREAK_RUNTIME_OK) goto finished;
            CoreAppRenderFrame frame = {tick, app->level->generation,
                                        app->level->render.resource_count};
            result = core_app_render_record_frame(&app->render, &frame);
            if (result == BREAK_RUNTIME_OK) result = app_publish_world(app, tick);
            if (result == BREAK_RUNTIME_OK) result = app_publish_skins(app, tick);
            if (result == BREAK_RUNTIME_OK && app->gpu.live) {
                const char *path = app->screenshot_next ? app->screenshot_path : NULL;
                CoreAppGpuFrame gpu_frame = {tick, app->level->generation};
                /* The record snapshot carries record-only fake handles in the
                 * vegetation batches, so the GPU lane submits an object-only
                 * copy: every draw there has a real device mesh. */
                app->gpu_snapshot = app->level->world_snapshots[tick & 1u];
                app->gpu_snapshot.instance_count = 0u;
                app->gpu_snapshot.batch_count = 0u;
                /* The stream object has no device mesh: its geometry is built
                 * host-side and only its record handle is staged. Binding that
                 * fake handle on a real backend would draw garbage, so the GPU
                 * lane drops stream draws instead. */
                u32 kept = 0u;
                for (u32 i = 0u; i < app->gpu_snapshot.draw_count; ++i) {
                    if (app->gpu_snapshot.draws[i].stream) continue;
                    if (kept != i) app->gpu_snapshot.draws[kept] = app->gpu_snapshot.draws[i];
                    kept++;
                }
                app->gpu_snapshot.draw_count = kept;
                stage = "gpu";
                result = core_app_gpu_render(&app->gpu, &app->gpu_snapshot, path, &gpu_frame);
                app->screenshot_next = false;
                if (result != BREAK_RUNTIME_OK) goto finished;
            }
            if (result == BREAK_RUNTIME_OK) {
                result = core_app_audio_enqueue(&app->audio, CORE_APP_AUDIO_LISTENER,
                                                app->level->generation);
            }
            if (result == BREAK_RUNTIME_OK) result = app_audio_drain(app, 1u);
            if (result != BREAK_RUNTIME_OK) {
                stage = "frame";
                goto finished;
            }
        }
    }
    if (!ended) {
        stage = "scenario";
        goto finished;
    }
    result = break_runtime_coordinator_stop(app->coordinator);
    if (result != BREAK_RUNTIME_OK) {
        stage = "shutdown";
        goto finished;
    }
    if (app->gpu.live) {
        /* Levels own device meshes; release them before the device goes. */
        if (app->level) {
            CoreLevel *level = app->level;
            app->level = NULL;
            core_app_level_destroy(level);
        }
        stage = "gpu_stop";
        result = core_app_gpu_destroy(&app->gpu);
        if (result != BREAK_RUNTIME_OK) goto finished;
        (void)app_trace(app,
            "COREAPPTRACE version=1 event=gpu result=stopped frames=%" PRIu64
            " screenshots=%" PRIu64 "\n",
            app->gpu.frames_presented, app->gpu.screenshots_written);
    }
    result = app_trace(app, "COREAPPTRACE version=1 event=runtime_stopped\n");
    if (result != BREAK_RUNTIME_OK) {
        stage = "trace";
        goto finished;
    }
    *out_exit_code = 0;
    stage = NULL;

finished:
    if (*out_exit_code != 0) {
        if (stage) fprintf(stderr, "core_app: stage=%s runtime rollback\n", stage);
        app_rollback(app);
        if (result == BREAK_RUNTIME_UNAVAILABLE) {
            /* Exit 77 mirrors the autotools "skipped" convention: a facility
             * the run required (audio device or GPU device) is absent. That is
             * an environment fact, not a defect in this run, and it must never
             * be reported as a pass either. */
            *out_exit_code = 77;
            result = BREAK_RUNTIME_UNAVAILABLE;
        } else {
            result = BREAK_RUNTIME_FAILED;
        }
    } else {
        result = BREAK_RUNTIME_OK;
    }
    break_runtime_coordinator_destroy(app->coordinator);
    if (app->trace) fclose(app->trace);
    core_app_input_destroy(app->input);
    free(app->scenario.events);
    free(app);
    return result;
}
