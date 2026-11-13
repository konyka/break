#include "core_app.h"

#include "core_app_audio.h"
#include "core_app_render.h"
#include "core_app_simulation.h"

#include <ai/break_ai.h>
#include <animation/anim_compression.h>
#include <animation/animation.h>
#include <asset/vfs.h>
#include <game/break_flow.h>
#include <game/break_game_internal.h>
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

#define CORE_APP_TEXT_FILE_MAX_BYTES (1u << 20)
#define CORE_APP_IO_TIMEOUT_MS 5000u
#define CORE_APP_USER_ENTITY_INDEX 2u
#define CORE_APP_CHASER_ENTITY_INDEX 3u
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
    u64 generation;
    bool actor_level_open;
} CoreLevel;

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
    u64 next_generation;
    bool io_running;
    bool render_live;
    bool audio_live;
};

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
    break_runtime_io_request_release(level->request);
    level->request = NULL;
    core_app_simulation_destroy(level->simulation);
    level->simulation = NULL;
    anim_blend_state_destroy(&level->locomotion);
    if (level->ai) break_ai_runtime_destroy(level->ai);
    if (level->nav_mesh) break_nav_mesh_destroy(level->nav_mesh);
    if (level->physics) physics_world_destroy(level->physics);
    if (level->actor_level_open && level->actor_runtime) {
        (void)break_game_level_close(level->actor_runtime);
    }
    if (level->adapter) break_game_lua_destroy(level->adapter);
    if (level->lua) break_lua_runtime_destroy(level->lua);
    if (level->flow) break_flow_runtime_destroy(level->flow);
    if (level->flow_graph) break_flow_graph_destroy(level->flow_graph);
    if (level->actor_runtime) break_game_destroy(level->actor_runtime);
    scene_serial_free(&level->scene);
    if (level->world) world_destroy(level->world);
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
                                         const char *asset_root,
                                         bool *runtime_fatal) {
    if (app->vfs->mount_count != 0u) {
        if (app->vfs->mount_count != 1u ||
            app->vfs->mounts[0].type != VFS_MOUNT_DIR) {
            return BREAK_RUNTIME_FAILED;
        }
        app->vfs->mount_count = 0u;
    }
    if (!vfs_mount_dir(app->vfs, asset_root)) return BREAK_RUNTIME_FAILED;
    BreakRuntimeError result = break_runtime_io_submit(&candidate->request,
                                                       "level.bscn", 0u, 0u);
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

static BreakRuntimeError stage_flow(CoreLevel *candidate,
                                         const char *asset_root) {
    u8 *bytes = NULL;
    usize size = 0u;
    if (!app_read_asset(asset_root, "level.fg", CORE_APP_TEXT_FILE_MAX_BYTES,
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
                                          const char *asset_root) {
    char scene_path[PLATFORM_FS_PATH_CAPACITY];
    char sidecar_path[PLATFORM_FS_PATH_CAPACITY];
    if (!app_path(scene_path, asset_root, "level.bscn") ||
        !app_path(sidecar_path, asset_root, "actors.sidecar")) {
        return BREAK_RUNTIME_INVALID;
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
    candidate->physics = physics_world_create(16u);
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
    return BREAK_RUNTIME_OK;
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

static BreakRuntimeError core_app_level_load(CoreApp *app, const char *asset_root,
                                             const char **failed_stage,
                                             bool *out_committed,
                                             bool *out_runtime_fatal) {
    *failed_stage = "bscn";
    *out_committed = false;
    *out_runtime_fatal = false;
    if (!app->io_running || app->next_generation == 0u) {
        return BREAK_RUNTIME_REJECTED;
    }
    CoreLevel *candidate = (CoreLevel *)calloc(1u, sizeof(*candidate));
    if (!candidate) return BREAK_RUNTIME_OOM;
    candidate->generation = app->next_generation;
    BreakRuntimeError result = stage_bscn(app, candidate, asset_root,
                                               out_runtime_fatal);
    if (result != BREAK_RUNTIME_OK) goto reject;

    *failed_stage = "flow";
    result = stage_flow(candidate, asset_root);
    if (result != BREAK_RUNTIME_OK) goto reject;

    *failed_stage = "lua";
    result = stage_lua(candidate, asset_root);
    if (result != BREAK_RUNTIME_OK) goto reject;

    *failed_stage = "actor";
    result = stage_actor(candidate, asset_root);
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
    result = stage_animation(candidate, asset_root);
    if (result != BREAK_RUNTIME_OK) goto reject;

    *failed_stage = "render";
    result = stage_render(candidate);
    if (result != BREAK_RUNTIME_OK) goto reject;

    *failed_stage = "crossref";
    result = app_validate_crossrefs(candidate);
    if (result != BREAK_RUNTIME_OK) goto reject;

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
        if (result == BREAK_RUNTIME_OK) result = core_app_audio_drain_record(&app->audio, 1u);
        if (result != BREAK_RUNTIME_OK) return result;
        result = app_trace_flow_discard(app, previous);
        if (result != BREAK_RUNTIME_OK) return result;
        result = app_trace(app,
            "COREAPPTRACE version=1 event=level_unloaded generation=%" PRIu64 "\n",
            previous_generation);
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
    return core_app_render_level_committed(&app->render, &candidate->render);

reject:
    core_app_level_destroy(candidate);
    return result;
}

static BreakRuntimeError core_app_unload_level(CoreApp *app, bool with_audio) {
    CoreLevel *level = app->level;
    if (!level) return BREAK_RUNTIME_OK;
    BreakRuntimeError result = BREAK_RUNTIME_OK;
    if (with_audio) {
        result = core_app_audio_enqueue(&app->audio, CORE_APP_AUDIO_STOP, level->generation);
        if (result == BREAK_RUNTIME_OK) result = core_app_audio_drain_record(&app->audio, 1u);
    }
    if (result != BREAK_RUNTIME_OK) return result;
    result = app_trace_flow_discard(app, level);
    if (result != BREAK_RUNTIME_OK) return result;
    app->level = NULL;
    u64 generation = level->generation;
    core_app_level_destroy(level);
    result = app_trace(app,
        "COREAPPTRACE version=1 event=level_unloaded generation=%" PRIu64 "\n",
        generation);
    BreakRuntimeError destroyed_result = app_trace(app,
        "COREAPPTRACE version=1 event=level_destroyed generation=%" PRIu64 "\n",
        generation);
    return result != BREAK_RUNTIME_OK ? result : destroyed_result;
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
    return core_app_audio_drain_record(&((CoreApp *)user)->audio,
                                   CORE_APP_AUDIO_QUEUE_CAPACITY);
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

static bool app_scenario_supported(const CoreAppScenario *scenario) {
    if (scenario->fixed_dt_ns != CORE_APP_FIXED_DT_NS) return false;
    for (u32 i = 0u; i < scenario->event_count; ++i) {
        switch (scenario->events[i].kind) {
        case CORE_APP_SCENARIO_KEY:
        case CORE_APP_SCENARIO_TOUCH:
        case CORE_APP_SCENARIO_PAD:
        case CORE_APP_SCENARIO_LEVEL:
        case CORE_APP_SCENARIO_UNLOAD:
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
    result = core_app_simulation_tick(level->simulation, frame);
    if (result != BREAK_RUNTIME_OK) return result;
    result = app_tick_chaser(app, tick);
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
        f32 dy = position.e[1] - level->previous_user_position.e[1];
        f32 dz = position.e[2] - level->previous_user_position.e[2];
        speed = sqrtf(dx * dx + dy * dy + dz * dz) / CORE_APP_FIXED_DT;
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
        (void)core_app_audio_drain_record(&app->audio, CORE_APP_AUDIO_QUEUE_CAPACITY);
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
    if (config->render_mode != CORE_APP_RENDER_RECORD ||
        config->audio_mode != CORE_APP_AUDIO_RECORD || !config->fixed_step ||
        config->require_device || config->network || !config->asset_root ||
        !config->scenario_path || !config->trace_path || config->checkpoint_dir ||
        config->screenshot_path) {
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
        !app_scenario_supported(&app->scenario)) {
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
    stage = "audio_start";
    result = core_app_audio_start(&app->audio, app->trace);
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
        if (app->level) {
            CoreAppInputFrame input_frame;
            stage = "simulation";
            result = core_app_input_frame(app->input, &input_frame);
            if (result == BREAK_RUNTIME_OK) result = app_tick_level(app, tick, &input_frame);
            if (result != BREAK_RUNTIME_OK) goto finished;
            CoreAppRenderFrame frame = {tick, app->level->generation,
                                        app->level->render.resource_count};
            result = core_app_render_record_frame(&app->render, &frame);
            if (result == BREAK_RUNTIME_OK) {
                result = core_app_audio_enqueue(&app->audio, CORE_APP_AUDIO_LISTENER,
                                                app->level->generation);
            }
            if (result == BREAK_RUNTIME_OK) result = core_app_audio_drain_record(&app->audio, 1u);
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
        result = BREAK_RUNTIME_FAILED;
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
