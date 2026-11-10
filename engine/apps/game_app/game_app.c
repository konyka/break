#include "game_app.h"

#include "game_audio.h"
#include "game_render.h"

#include <ai/break_ai.h>
#include <animation/anim_compression.h>
#include <asset/vfs.h>
#include <game/break_flow.h>
#include <game/break_game_lua.h>
#include <physics/physics.h>
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

#define GAME_SCENARIO_MAX_STEPS 64u
#define GAME_SCENARIO_MAX_BYTES (64u * 1024u)
#define GAME_SCENARIO_ROOT_CAPACITY 1024u
#define GAME_TEXT_FILE_MAX_BYTES (1u << 20)
#define GAME_IO_TIMEOUT_MS 5000u

typedef enum GameScenarioAction {
    GAME_SCENARIO_LOAD = 1,
    GAME_SCENARIO_UNLOAD,
    GAME_SCENARIO_END
} GameScenarioAction;

typedef struct GameScenarioStep {
    u32 frame;
    GameScenarioAction action;
    char asset_root[GAME_SCENARIO_ROOT_CAPACITY];
} GameScenarioStep;

typedef struct GameLevel {
    World *world;
    Scene scene;
    BreakGame *game;
    BreakFlowGraph *flow_graph;
    BreakFlowRuntime *flow;
    BreakLuaRuntime *lua;
    BreakGameLuaAdapter *adapter;
    PhysicsWorld *physics;
    BreakNavMesh *nav_mesh;
    BreakAiRuntime *ai;
    AnimClip animation;
    GameRenderLevel render;
    BreakRuntimeIoRequest *request;
    PhysicsBodyHandle ground_body;
    PhysicsBodyHandle player_body;
    f32 nav_heights[16];
    u64 generation;
    bool actor_level_open;
} GameLevel;

typedef struct GameApp {
    GameAppConfig config;
    GameScenarioStep steps[GAME_SCENARIO_MAX_STEPS];
    BreakRuntimeCoordinator *coordinator;
    BreakRuntimeIoRequest *old_request;
    VFS *vfs;
    GameLevel *level;
    FILE *trace;
    GameRender render;
    GameAudio audio;
    u64 next_generation;
    u32 step_count;
    bool io_running;
    bool render_live;
    bool audio_live;
} GameApp;

static BreakRuntimeError game_trace(GameApp *game, const char *format, ...) {
    if (!game || !game->trace || !format) return BREAK_RUNTIME_INVALID;
    va_list args;
    va_start(args, format);
    int written = vfprintf(game->trace, format, args);
    va_end(args);
    if (written < 0 || fflush(game->trace) != 0) return BREAK_RUNTIME_FAILED;
    return BREAK_RUNTIME_OK;
}

static bool game_path(char out[PLATFORM_FS_PATH_CAPACITY], const char *root,
                      const char *name) {
    if (!root || !name) return false;
    int written = snprintf(out, PLATFORM_FS_PATH_CAPACITY, "%s/%s", root, name);
    return written > 0 && (usize)written < PLATFORM_FS_PATH_CAPACITY;
}

static bool game_read_file(const char *path, usize maximum, u8 **out_bytes,
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

static bool game_read_asset(const char *root, const char *name, usize maximum,
                            u8 **out_bytes, usize *out_size) {
    char path[PLATFORM_FS_PATH_CAPACITY];
    return game_path(path, root, name) &&
           game_read_file(path, maximum, out_bytes, out_size);
}

static void game_app_level_destroy(GameLevel *level) {
    if (!level) return;
    break_runtime_io_request_release(level->request);
    level->request = NULL;
    if (level->ai) break_ai_runtime_destroy(level->ai);
    if (level->nav_mesh) break_nav_mesh_destroy(level->nav_mesh);
    if (level->physics) physics_world_destroy(level->physics);
    if (level->actor_level_open && level->game) {
        (void)break_game_level_close(level->game);
    }
    if (level->adapter) break_game_lua_destroy(level->adapter);
    if (level->lua) break_lua_runtime_destroy(level->lua);
    if (level->flow) break_flow_runtime_destroy(level->flow);
    if (level->flow_graph) break_flow_graph_destroy(level->flow_graph);
    if (level->game) break_game_destroy(level->game);
    scene_serial_free(&level->scene);
    if (level->world) world_destroy(level->world);
    free(level);
}

static BreakGameError game_level_hook_load(void *user, World *world,
                                           const char *scene_path) {
    GameLevel *level = (GameLevel *)user;
    if (!level || level->world != world || !scene_path || scene_path[0] == '\0') {
        return BREAK_GAME_INVALID;
    }
    return level->scene.node_count > 0u ? BREAK_GAME_OK : BREAK_GAME_FAILED;
}

static void game_level_hook_unload(void *user, World *world) {
    (void)user;
    (void)world;
}

static BreakRuntimeError game_stage_bscn(GameApp *game, GameLevel *candidate,
                                         const char *asset_root) {
    if (!vfs_mount_dir(game->vfs, asset_root)) return BREAK_RUNTIME_FAILED;
    BreakRuntimeError result = break_runtime_io_submit(&candidate->request,
                                                       "level.bscn", 0u, 0u);
    if (result != BREAK_RUNTIME_OK) return result;
    BreakRuntimeOwnedMessage *message = NULL;
    result = break_runtime_io_wait_completion(candidate->request,
                                              GAME_IO_TIMEOUT_MS, &message);
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
    candidate->game = break_game_create(candidate->world, &config);
    if (!candidate->game) return BREAK_RUNTIME_OOM;
    static const char *const class_names[] = {
        "Ground", "Player", "Enemy", "DynamicWall", "Vehicle",
        "VisibleColor", "HiddenColor"
    };
    for (u32 i = 0u; i < sizeof(class_names) / sizeof(class_names[0]); ++i) {
        BreakGameClassDesc desc;
        memset(&desc, 0, sizeof(desc));
        desc.name = class_names[i];
        if (i == 1u) desc.lua_module = "player";
        u32 class_id = 0u;
        if (break_game_register_class(candidate->game, &desc, &class_id) !=
                BREAK_GAME_OK ||
            class_id == 0u) {
            return BREAK_RUNTIME_FAILED;
        }
    }
    BreakGameItemDesc item = {1u, 1000000u};
    if (break_game_item_define(candidate->game, &item) != BREAK_GAME_OK) {
        return BREAK_RUNTIME_FAILED;
    }
    return BREAK_RUNTIME_OK;
}

static BreakRuntimeError game_stage_flow(GameLevel *candidate,
                                         const char *asset_root) {
    u8 *bytes = NULL;
    usize size = 0u;
    if (!game_read_asset(asset_root, "level.fg", GAME_TEXT_FILE_MAX_BYTES,
                         &bytes, &size)) {
        return BREAK_RUNTIME_FAILED;
    }
    BreakFlowError flow_result = break_flow_deserialize(bytes, size,
                                                        &candidate->flow_graph);
    free(bytes);
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
                                                candidate->game, &config);
    return candidate->flow ? BREAK_RUNTIME_OK : BREAK_RUNTIME_OOM;
}

static BreakRuntimeError game_stage_lua(GameLevel *candidate,
                                        const char *asset_root) {
    BreakLuaRuntimeConfig config;
    memset(&config, 0, sizeof(config));
    config.max_modules = 4u;
    config.instruction_budget = 1000000u;
    config.memory_budget = 8u * 1024u * 1024u;
    candidate->lua = break_lua_runtime_create(&config);
    if (!candidate->lua) return BREAK_RUNTIME_OOM;
    static const char *const modules[] = {"director", "player"};
    for (u32 i = 0u; i < sizeof(modules) / sizeof(modules[0]); ++i) {
        char filename[64];
        int written = snprintf(filename, sizeof(filename), "%s.lua", modules[i]);
        if (written < 0 || (usize)written >= sizeof(filename)) {
            return BREAK_RUNTIME_FAILED;
        }
        u8 *source = NULL;
        usize source_size = 0u;
        if (!game_read_asset(asset_root, filename, BREAK_LUA_MAX_MODULE_BYTES,
                             &source, &source_size)) {
            return BREAK_RUNTIME_FAILED;
        }
        BreakLuaError result = break_lua_runtime_load_module(
            candidate->lua, modules[i], source, source_size);
        free(source);
        if (result != BREAK_LUA_OK) return BREAK_RUNTIME_FAILED;
    }
    candidate->adapter = break_game_lua_create(candidate->game, candidate->lua);
    return candidate->adapter ? BREAK_RUNTIME_OK : BREAK_RUNTIME_OOM;
}

static BreakRuntimeError game_stage_actor(GameLevel *candidate,
                                          const char *asset_root) {
    char scene_path[PLATFORM_FS_PATH_CAPACITY];
    char sidecar_path[PLATFORM_FS_PATH_CAPACITY];
    if (!game_path(scene_path, asset_root, "level.bscn") ||
        !game_path(sidecar_path, asset_root, "actors.sidecar")) {
        return BREAK_RUNTIME_INVALID;
    }
    BreakGameLevelHooks hooks;
    memset(&hooks, 0, sizeof(hooks));
    hooks.load = game_level_hook_load;
    hooks.unload = game_level_hook_unload;
    hooks.user = candidate;
    if (break_game_level_open(candidate->game, &hooks, scene_path, sidecar_path) !=
        BREAK_GAME_OK) {
        return BREAK_RUNTIME_FAILED;
    }
    candidate->actor_level_open = true;
    return BREAK_RUNTIME_OK;
}

static Vec3 game_node_position(const SceneNode *node) {
    return vec3(node->world_transform.e[3][0], node->world_transform.e[3][1],
                node->world_transform.e[3][2]);
}

static BreakRuntimeError game_stage_physics(GameLevel *candidate) {
    if (candidate->scene.node_count < 2u || !candidate->scene.nodes) {
        return BREAK_RUNTIME_FAILED;
    }
    candidate->physics = physics_world_create(16u);
    if (!candidate->physics) return BREAK_RUNTIME_OOM;
    const SceneNode *ground = &candidate->scene.nodes[0];
    Vec3 ground_extent = vec3(fabsf(ground->world_transform.e[0][0]),
                              fabsf(ground->world_transform.e[1][1]),
                              fabsf(ground->world_transform.e[2][2]));
    candidate->ground_body = physics_body_create(candidate->physics,
        game_node_position(ground), ground_extent, 0.0f, true, 0u);
    const SceneNode *player = &candidate->scene.nodes[1];
    candidate->player_body = physics_body_create(candidate->physics,
        game_node_position(player), vec3(0.4f, 1.0f, 0.4f), 70.0f, false, 0u);
    if (!physics_body_handle_is_valid(candidate->ground_body) ||
        !physics_body_handle_is_valid(candidate->player_body)) {
        return BREAK_RUNTIME_FAILED;
    }
    return BREAK_RUNTIME_OK;
}

static BreakRuntimeError game_stage_ai(GameLevel *candidate) {
    if (candidate->scene.node_count < 3u || candidate->world->entity_count <= 3u) {
        return BREAK_RUNTIME_FAILED;
    }
    BreakNavHeightfield field;
    memset(&field, 0, sizeof(field));
    field.heights = candidate->nav_heights;
    field.width = 4u;
    field.depth = 4u;
    field.cell = 1.0f;
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
    agent.position = game_node_position(&candidate->scene.nodes[2]);
    agent.radius = 0.4f;
    agent.max_speed = 3.0f;
    Entity enemy = candidate->world->entities[3];
    if (break_ai_agent_add(candidate->ai, enemy, &agent) != BREAK_NAV_OK) {
        return BREAK_RUNTIME_FAILED;
    }
    return BREAK_RUNTIME_OK;
}

static BreakRuntimeError game_stage_animation(GameLevel *candidate,
                                              const char *asset_root) {
    u8 *bytes = NULL;
    usize size = 0u;
    if (!game_read_asset(asset_root, "level.banm", ANIM_CODEC_MAX_BYTES,
                         &bytes, &size)) {
        return BREAK_RUNTIME_FAILED;
    }
    AnimCodecResult result = anim_codec_decode(bytes, size, &candidate->animation);
    free(bytes);
    return result == ANIM_CODEC_OK ? BREAK_RUNTIME_OK : BREAK_RUNTIME_FAILED;
}

static BreakRuntimeError game_stage_render(GameLevel *candidate) {
    if (candidate->scene.resource_count > GAME_RENDER_RESOURCE_CAPACITY ||
        (candidate->scene.resource_count > 0u && !candidate->scene.resources)) {
        return BREAK_RUNTIME_OVERLOAD;
    }
    GameRenderResource resources[GAME_RENDER_RESOURCE_CAPACITY];
    memset(resources, 0, sizeof(resources));
    for (u32 i = 0u; i < candidate->scene.resource_count; ++i) {
        resources[i].id = candidate->scene.resources[i].guid;
        resources[i].generation = candidate->generation;
        resources[i].kind = candidate->scene.resources[i].type;
        resources[i].ref_index = candidate->scene.resources[i].ref_index;
    }
    return game_render_stage_level(resources, candidate->scene.resource_count,
                                   candidate->generation, &candidate->render);
}

static const SceneResource *game_find_resource(const GameLevel *candidate,
                                               BscnResourceType type, u32 ref_index) {
    for (u32 i = 0u; i < candidate->scene.resource_count; ++i) {
        const SceneResource *resource = &candidate->scene.resources[i];
        if (resource->type == (u32)type && resource->ref_index == ref_index) {
            return resource;
        }
    }
    return NULL;
}

static bool game_find_geometry(const GameLevel *candidate, u32 mesh_index) {
    for (u32 i = 0u; i < candidate->scene.mesh_geometry_count; ++i) {
        if (candidate->scene.mesh_geometry[i].mesh_index == mesh_index) return true;
    }
    return false;
}

static BreakRuntimeError game_validate_crossrefs(const GameLevel *candidate) {
    if (!candidate->world || !candidate->game || !candidate->flow ||
        !candidate->lua || !candidate->adapter || !candidate->actor_level_open ||
        !candidate->physics || !candidate->ai || !candidate->nav_mesh ||
        candidate->generation == 0u || candidate->animation.channel_count == 0u ||
        candidate->scene.node_count == 0u ||
        candidate->world->entity_count != candidate->scene.node_count + 1u ||
        candidate->render.resource_count != candidate->scene.resource_count) {
        return BREAK_RUNTIME_FAILED;
    }
    for (u32 i = 0u; i < candidate->scene.node_count; ++i) {
        const SceneNode *node = &candidate->scene.nodes[i];
        if (!game_find_resource(candidate, BSCN_RES_MESH, node->mesh_index) ||
            !game_find_resource(candidate, BSCN_RES_MATERIAL, node->material_idx) ||
            (node->has_mesh && !game_find_geometry(candidate, node->mesh_index))) {
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

static BreakRuntimeError game_app_level_load(GameApp *game, const char *asset_root,
                                             const char **failed_stage) {
    *failed_stage = "bscn";
    if (!game->io_running || game->next_generation == 0u) {
        return BREAK_RUNTIME_REJECTED;
    }
    GameLevel *candidate = (GameLevel *)calloc(1u, sizeof(*candidate));
    if (!candidate) return BREAK_RUNTIME_OOM;
    candidate->generation = game->next_generation;
    BreakRuntimeError result = game_stage_bscn(game, candidate, asset_root);
    if (result != BREAK_RUNTIME_OK) goto reject;

    *failed_stage = "flow";
    result = game_stage_flow(candidate, asset_root);
    if (result != BREAK_RUNTIME_OK) goto reject;

    *failed_stage = "lua";
    result = game_stage_lua(candidate, asset_root);
    if (result != BREAK_RUNTIME_OK) goto reject;

    *failed_stage = "actor";
    result = game_stage_actor(candidate, asset_root);
    if (result != BREAK_RUNTIME_OK) goto reject;

    *failed_stage = "physics";
    result = game_stage_physics(candidate);
    if (result != BREAK_RUNTIME_OK) goto reject;

    *failed_stage = "ai";
    result = game_stage_ai(candidate);
    if (result != BREAK_RUNTIME_OK) goto reject;

    *failed_stage = "animation";
    result = game_stage_animation(candidate, asset_root);
    if (result != BREAK_RUNTIME_OK) goto reject;

    *failed_stage = "render";
    result = game_stage_render(candidate);
    if (result != BREAK_RUNTIME_OK) goto reject;

    *failed_stage = "crossref";
    result = game_validate_crossrefs(candidate);
    if (result != BREAK_RUNTIME_OK) goto reject;

    GameLevel *previous = game->level;
    game->level = candidate;
    game->next_generation++;
    if (previous) {
        result = game_audio_enqueue(&game->audio, GAME_AUDIO_STOP,
                                    previous->generation);
        if (result == BREAK_RUNTIME_OK) result = game_audio_drain_record(&game->audio, 1u);
        if (result != BREAK_RUNTIME_OK) return result;
        result = game_trace(game,
            "GAMEAPPTRACE version=1 event=level_unloaded generation=%" PRIu64 "\n",
            previous->generation);
        if (result != BREAK_RUNTIME_OK) return result;
        game_app_level_destroy(previous);
    }
    result = game_trace(game,
        "GAMEAPPTRACE version=1 event=level_loaded generation=%" PRIu64 "\n",
        candidate->generation);
    if (result != BREAK_RUNTIME_OK) return result;
    return game_render_level_committed(&game->render, &candidate->render);

reject:
    game_app_level_destroy(candidate);
    return result;
}

static BreakRuntimeError game_app_unload_level(GameApp *game, bool with_audio) {
    GameLevel *level = game->level;
    if (!level) return BREAK_RUNTIME_OK;
    BreakRuntimeError result = BREAK_RUNTIME_OK;
    if (with_audio) {
        result = game_audio_enqueue(&game->audio, GAME_AUDIO_STOP, level->generation);
        if (result == BREAK_RUNTIME_OK) result = game_audio_drain_record(&game->audio, 1u);
    }
    if (result != BREAK_RUNTIME_OK) return result;
    game->level = NULL;
    u64 generation = level->generation;
    game_app_level_destroy(level);
    return game_trace(game,
        "GAMEAPPTRACE version=1 event=level_unloaded generation=%" PRIu64 "\n",
        generation);
}

static BreakRuntimeError game_audio_stop_admission_cb(void *user) {
    return game_audio_stop_admission(&((GameApp *)user)->audio);
}

static BreakRuntimeError game_audio_stop_producers_cb(void *user) {
    return game_audio_stop_producers(&((GameApp *)user)->audio);
}

static BreakRuntimeError game_audio_close_queues_cb(void *user) {
    return game_audio_close_queues(&((GameApp *)user)->audio);
}

static BreakRuntimeError game_audio_drain_cb(void *user) {
    return game_audio_drain_record(&((GameApp *)user)->audio,
                                   GAME_AUDIO_QUEUE_CAPACITY);
}

static BreakRuntimeError game_audio_join_cb(void *user) {
    return game_audio_join(&((GameApp *)user)->audio);
}

static BreakRuntimeError game_audio_destroy_cb(void *user) {
    GameApp *game = (GameApp *)user;
    BreakRuntimeError result = game_audio_destroy(&game->audio);
    if (result == BREAK_RUNTIME_OK) game->audio_live = false;
    return result;
}

static BreakRuntimeError game_render_stop_admission_cb(void *user) {
    return game_render_stop_admission(&((GameApp *)user)->render);
}

static BreakRuntimeError game_render_stop_producers_cb(void *user) {
    return game_render_stop_producers(&((GameApp *)user)->render);
}

static BreakRuntimeError game_render_idle_cb(void *user) {
    return game_render_idle(&((GameApp *)user)->render);
}

static BreakRuntimeError game_render_destroy_cb(void *user) {
    GameApp *game = (GameApp *)user;
    BreakRuntimeError result = game_render_destroy(&game->render);
    if (result == BREAK_RUNTIME_OK) game->render_live = false;
    return result;
}

static BreakRuntimeError game_level_stop_producers_cb(void *user) {
    (void)user;
    return BREAK_RUNTIME_OK;
}

static BreakRuntimeError game_level_drain_cb(void *user) {
    GameApp *game = (GameApp *)user;
    if (game->level && game->level->request) {
        break_runtime_io_request_release(game->level->request);
        game->level->request = NULL;
    }
    return BREAK_RUNTIME_OK;
}

static BreakRuntimeError game_app_stop_io(GameApp *game) {
    if (!game->io_running) return BREAK_RUNTIME_OK;
    BreakRuntimeError result = break_runtime_io_shutdown(GAME_IO_TIMEOUT_MS);
    if (result != BREAK_RUNTIME_OK) return result;
    game->io_running = false;
    BreakRuntimeIoStats stats;
    memset(&stats, 0, sizeof(stats));
    result = break_runtime_io_stats(&stats);
    if (result != BREAK_RUNTIME_OK || stats.active != 0u) return BREAK_RUNTIME_FAILED;
    return game_trace(game, "GAMEAPPTRACE version=1 event=io_stopped active=0\n");
}

static BreakRuntimeError game_level_join_cb(void *user) {
    return game_app_stop_io((GameApp *)user);
}

static BreakRuntimeError game_level_destroy_cb(void *user) {
    GameApp *game = (GameApp *)user;
    BreakRuntimeError result = game_app_unload_level(game, false);
    if (game->vfs && !game->io_running) {
        vfs_destroy(game->vfs);
        game->vfs = NULL;
    }
    return result;
}

static BreakRuntimeError game_register_subsystems(GameApp *game) {
    BreakRuntimeCoordinatorConfig config = {4u};
    BreakRuntimeError result = break_runtime_coordinator_create(&config,
                                                                &game->coordinator);
    if (result != BREAK_RUNTIME_OK) return result;
    BreakRuntimeSubsystem subsystems[4];
    memset(subsystems, 0, sizeof(subsystems));
    subsystems[0].name = "network";
    subsystems[1].name = "audio";
    subsystems[1].user_data = game;
    subsystems[1].stop_admission = game_audio_stop_admission_cb;
    subsystems[1].stop_producers = game_audio_stop_producers_cb;
    subsystems[1].close_queues = game_audio_close_queues_cb;
    subsystems[1].drain = game_audio_drain_cb;
    subsystems[1].join = game_audio_join_cb;
    subsystems[1].destroy = game_audio_destroy_cb;
    subsystems[2].name = "render";
    subsystems[2].user_data = game;
    subsystems[2].stop_admission = game_render_stop_admission_cb;
    subsystems[2].stop_producers = game_render_stop_producers_cb;
    subsystems[2].join = game_render_idle_cb;
    subsystems[2].destroy = game_render_destroy_cb;
    subsystems[3].name = "level";
    subsystems[3].user_data = game;
    subsystems[3].stop_producers = game_level_stop_producers_cb;
    subsystems[3].drain = game_level_drain_cb;
    subsystems[3].join = game_level_join_cb;
    subsystems[3].destroy = game_level_destroy_cb;
    for (u32 i = 0u; i < 4u; ++i) {
        result = break_runtime_coordinator_register_subsystem(game->coordinator,
                                                              &subsystems[i]);
        if (result != BREAK_RUNTIME_OK) return result;
    }
    return BREAK_RUNTIME_OK;
}

static bool game_parse_scenario(GameApp *game) {
    u8 *bytes = NULL;
    usize size = 0u;
    if (!game_read_file(game->config.scenario_path, GAME_SCENARIO_MAX_BYTES,
                        &bytes, &size) ||
        memchr(bytes, '\0', size) != NULL) {
        free(bytes);
        return false;
    }
    bool ok = false;
    u32 line_number = 0u;
    bool ended = false;
    char *cursor = (char *)bytes;
    while (cursor < (char *)bytes + size) {
        char *line = cursor;
        char *newline = memchr(cursor, '\n', (usize)((char *)bytes + size - cursor));
        if (newline) {
            *newline = '\0';
            cursor = newline + 1;
        } else {
            cursor = (char *)bytes + size;
        }
        line_number++;
        usize length = strlen(line);
        if (length > 0u && line[length - 1u] == '\r') line[length - 1u] = '\0';
        if (line[0] == '\0' || line[0] == '#') continue;
        if (line_number == 1u) {
            if (strcmp(line, "game-app-scenario 1") != 0) goto cleanup;
            continue;
        }
        if (line_number == 2u) {
            unsigned long long seed = 0u;
            char extra = '\0';
            if (sscanf(line, "seed %llu %c", &seed, &extra) != 1) goto cleanup;
            continue;
        }
        if (line_number == 3u) {
            unsigned long long fixed_dt_ns = 0u;
            char extra = '\0';
            if (sscanf(line, "fixed-dt-ns %llu %c", &fixed_dt_ns, &extra) != 1 ||
                fixed_dt_ns == 0u) {
                goto cleanup;
            }
            continue;
        }
        if (ended || game->step_count >= GAME_SCENARIO_MAX_STEPS) goto cleanup;
        char frame_word[16];
        char action[16];
        char root[GAME_SCENARIO_ROOT_CAPACITY];
        char extra[16];
        memset(frame_word, 0, sizeof(frame_word));
        memset(action, 0, sizeof(action));
        memset(root, 0, sizeof(root));
        memset(extra, 0, sizeof(extra));
        u32 frame = 0u;
        int fields = sscanf(line, "%15s %u %15s %1023s %15s", frame_word, &frame,
                            action, root, extra);
        if ((fields != 3 && fields != 4) || strcmp(frame_word, "frame") != 0 ||
            frame != game->step_count + 1u) {
            goto cleanup;
        }
        GameScenarioStep *step = &game->steps[game->step_count];
        memset(step, 0, sizeof(*step));
        step->frame = frame;
        if (strcmp(action, "load") == 0) {
            step->action = GAME_SCENARIO_LOAD;
            if (fields == 4 && snprintf(step->asset_root, sizeof(step->asset_root),
                                        "%s", root) >= (int)sizeof(step->asset_root)) {
                goto cleanup;
            }
        } else if (strcmp(action, "unload") == 0 && fields == 3) {
            step->action = GAME_SCENARIO_UNLOAD;
        } else if (strcmp(action, "end") == 0 && fields == 3) {
            step->action = GAME_SCENARIO_END;
            ended = true;
        } else {
            goto cleanup;
        }
        game->step_count++;
    }
    ok = ended && game->step_count > 0u &&
         game->steps[game->step_count - 1u].action == GAME_SCENARIO_END;

cleanup:
    free(bytes);
    return ok;
}

static void game_rollback(GameApp *game) {
    if (game->coordinator &&
        break_runtime_coordinator_state(game->coordinator) != BREAK_RUNTIME_STOPPED) {
        (void)break_runtime_coordinator_fail(game->coordinator, BREAK_RUNTIME_FAILED);
    }
    if (game->audio_live) {
        (void)game_audio_stop_admission(&game->audio);
        (void)game_audio_stop_producers(&game->audio);
        (void)game_audio_close_queues(&game->audio);
        (void)game_audio_drain_record(&game->audio, GAME_AUDIO_QUEUE_CAPACITY);
        (void)game_audio_join(&game->audio);
        (void)game_audio_destroy(&game->audio);
        game->audio_live = false;
    }
    if (game->render_live) {
        (void)game_render_stop_admission(&game->render);
        (void)game_render_stop_producers(&game->render);
        (void)game_render_idle(&game->render);
        (void)game_render_destroy(&game->render);
        game->render_live = false;
    }
    if (game->level) {
        GameLevel *level = game->level;
        game->level = NULL;
        game_app_level_destroy(level);
    }
    (void)game_app_stop_io(game);
    if (game->vfs && !game->io_running) {
        vfs_destroy(game->vfs);
        game->vfs = NULL;
    }
    (void)game_trace(game, "GAMEAPPTRACE version=1 event=runtime_failed\n");
}

BreakRuntimeError game_app_run(const GameAppConfig *config, int *out_exit_code) {
    if (!out_exit_code) return BREAK_RUNTIME_INVALID;
    *out_exit_code = 2;
    if (!config) return BREAK_RUNTIME_INVALID;
    if (config->render_mode != GAME_RENDER_RECORD ||
        config->audio_mode != GAME_AUDIO_RECORD || !config->fixed_step ||
        config->require_device || config->network || !config->asset_root ||
        !config->scenario_path || !config->trace_path || config->checkpoint_dir ||
        config->screenshot_path) {
        fprintf(stderr, "game_app: stage=config unsupported lifecycle configuration\n");
        return BREAK_RUNTIME_FAILED;
    }
    GameApp *game = (GameApp *)calloc(1u, sizeof(*game));
    if (!game) return BREAK_RUNTIME_OOM;
    game->config = *config;
    game->next_generation = 1u;
    const char *stage = "scenario";
    BreakRuntimeError result = BREAK_RUNTIME_FAILED;

    game->trace = fopen(config->trace_path, "wb");
    if (!game->trace || !game_parse_scenario(game)) goto finished;

    stage = "io";
    game->vfs = vfs_create();
    if (!game->vfs) goto finished;
    BreakRuntimeIoConfig io_config;
    memset(&io_config, 0, sizeof(io_config));
    io_config.vfs = game->vfs;
    io_config.worker_count = 1u;
    io_config.request_capacity = 4u;
    result = break_runtime_io_init(&io_config);
    if (result != BREAK_RUNTIME_OK) goto finished;
    game->io_running = true;

    stage = "render_start";
    result = game_render_start(&game->render, game->trace);
    if (result != BREAK_RUNTIME_OK) goto finished;
    game->render_live = true;
    stage = "audio_start";
    result = game_audio_start(&game->audio, game->trace);
    if (result != BREAK_RUNTIME_OK) goto finished;
    game->audio_live = true;
    stage = "coordinator";
    result = game_register_subsystems(game);
    if (result != BREAK_RUNTIME_OK) goto finished;
    result = break_runtime_coordinator_start(game->coordinator);
    if (result != BREAK_RUNTIME_OK) goto finished;
    result = game_trace(game, "GAMEAPPTRACE version=1 event=runtime_running\n");
    if (result != BREAK_RUNTIME_OK) goto finished;

    bool ended = false;
    for (u32 i = 0u; i < game->step_count; ++i) {
        GameScenarioStep *step = &game->steps[i];
        if (config->max_frames != 0u && step->frame > config->max_frames) {
            ended = true;
            break;
        }
        if (step->action == GAME_SCENARIO_END) {
            ended = true;
            break;
        }
        if (step->action == GAME_SCENARIO_LOAD) {
            const char *asset_root = step->asset_root[0] != '\0'
                ? step->asset_root : config->asset_root;
            bool had_level = game->level != NULL;
            const char *load_stage = "bscn";
            result = game_app_level_load(game, asset_root, &load_stage);
            if (result != BREAK_RUNTIME_OK) {
                u64 generation = game->level ? game->level->generation : 0u;
                (void)game_trace(game,
                    "GAMEAPPTRACE version=1 event=load_rejected generation=%" PRIu64
                    " stage=%s\n", generation, load_stage);
                fprintf(stderr, "game_app: stage=%s level load rejected\n", load_stage);
                if (!had_level || strcmp(load_stage, "crossref") == 0 ||
                    strcmp(load_stage, "render") == 0) {
                    stage = load_stage;
                    goto finished;
                }
            }
        } else if (step->action == GAME_SCENARIO_UNLOAD) {
            result = game_app_unload_level(game, true);
            if (result != BREAK_RUNTIME_OK) {
                stage = "unload";
                goto finished;
            }
        }
        if (game->level) {
            GameRenderFrame frame = {step->frame, game->level->generation,
                                     game->level->render.resource_count};
            result = game_render_record_frame(&game->render, &frame);
            if (result == BREAK_RUNTIME_OK) {
                result = game_audio_enqueue(&game->audio, GAME_AUDIO_LISTENER,
                                            game->level->generation);
            }
            if (result == BREAK_RUNTIME_OK) result = game_audio_drain_record(&game->audio, 1u);
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
    result = break_runtime_coordinator_stop(game->coordinator);
    if (result != BREAK_RUNTIME_OK) {
        stage = "shutdown";
        goto finished;
    }
    result = game_trace(game, "GAMEAPPTRACE version=1 event=runtime_stopped\n");
    if (result != BREAK_RUNTIME_OK) {
        stage = "trace";
        goto finished;
    }
    *out_exit_code = 0;
    stage = NULL;

finished:
    if (*out_exit_code != 0) {
        if (stage) fprintf(stderr, "game_app: stage=%s runtime rollback\n", stage);
        game_rollback(game);
        result = BREAK_RUNTIME_FAILED;
    } else {
        result = BREAK_RUNTIME_OK;
    }
    break_runtime_coordinator_destroy(game->coordinator);
    if (game->trace) fclose(game->trace);
    free(game);
    return result;
}
