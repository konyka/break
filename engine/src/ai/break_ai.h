#pragma once
/*
 * Navigation, sight, and a small behavior tree.
 * Formal optional library: not linked into engine, engine_demo, or dxx_break.
 * The baker takes a plain heightfield. It does not include the renderer.
 */
#include <core/types.h>
#include <ecs/ecs.h>
#include <math/math.h>

#ifdef __cplusplus
extern "C" {
#endif


#define BREAK_NAV_MAX_POINTS 256u
#define BREAK_SIGHT_MAX_TARGETS 8u
#define BREAK_STEER_MAX_NEIGHBORS 16u
#define BREAK_NAV_TILE_METERS 32.0f

typedef struct BreakNavHeightfield {
    const f32 *heights; /* row-major, index = z * width + x */
    u32 width;
    u32 depth;
    f32 origin_x;
    f32 origin_z;
    f32 cell;
    f32 height_scale;
} BreakNavHeightfield;

typedef struct BreakNavMesh BreakNavMesh;

BreakNavMesh *break_nav_bake_heightfield(const BreakNavHeightfield *field,
                                         f32 walkable_slope_deg,
                                         f32 agent_radius);
void          break_nav_mesh_destroy(BreakNavMesh *mesh);
bool          break_nav_same_component(const BreakNavMesh *mesh, Vec3 a, Vec3 b);

typedef struct BreakNavPath {
    Vec3 points[BREAK_NAV_MAX_POINTS];
    u32 count;
} BreakNavPath;

typedef enum BreakNavError {
    BREAK_NAV_OK = 0,
    BREAK_NAV_INVALID,
    BREAK_NAV_OVERLOAD,
    BREAK_NAV_FAILED,
    BREAK_NAV_STALE,
    BREAK_NAV_REJECTED
} BreakNavError;

#define BREAK_AI_MAX_OBSTACLES 4096u
#define BREAK_AI_MAX_AGENTS 1024u
#define BREAK_AI_MAX_CACHED_PATHS 256u
#define BREAK_AI_MAX_SMART_OBJECTS 1024u
#define BREAK_AI_MAX_FORMATIONS 256u
#define BREAK_AI_MAX_FORMATION_MEMBERS 32u

typedef struct BreakAiRuntime BreakAiRuntime;

typedef struct BreakAiRuntimeDesc {
    u32 max_obstacles;
    u32 max_agents;
    u32 max_cached_paths;
    u32 max_smart_objects;
    u32 max_formations;
} BreakAiRuntimeDesc;

typedef struct BreakAiObstacleHandle {
    u32 index;
    u32 generation;
} BreakAiObstacleHandle;

typedef struct BreakAiObstacleDesc {
    f32 min_x;
    f32 min_z;
    f32 max_x;
    f32 max_z;
} BreakAiObstacleDesc;

typedef struct BreakAiPath {
    BreakNavPath path;
    u32 nav_version;
} BreakAiPath;

BreakAiRuntime *break_ai_runtime_create(BreakNavMesh *mesh, const BreakAiRuntimeDesc *desc);
void break_ai_runtime_destroy(BreakAiRuntime *runtime);
BreakNavError break_ai_obstacle_add(BreakAiRuntime *runtime, const BreakAiObstacleDesc *desc,
                                    BreakAiObstacleHandle *out);
BreakNavError break_ai_obstacle_update(BreakAiRuntime *runtime, BreakAiObstacleHandle handle,
                                       const BreakAiObstacleDesc *desc);
BreakNavError break_ai_obstacle_remove(BreakAiRuntime *runtime, BreakAiObstacleHandle handle);
u32 break_ai_nav_version(const BreakAiRuntime *runtime);
BreakNavError break_ai_find_path(BreakAiRuntime *runtime, Vec3 start, Vec3 end,
                                 u32 expected_version, BreakAiPath *out);
bool break_ai_path_is_current(const BreakAiRuntime *runtime, const BreakAiPath *path);

BreakNavError break_nav_find_path(const BreakNavMesh *mesh, Vec3 start, Vec3 end,
                                  BreakNavPath *out);

typedef struct BreakNavFollower {
    BreakNavPath path;
    u32 cursor;
    f32 arrive_radius;
} BreakNavFollower;

void break_nav_follow_reset(BreakNavFollower *follower, const BreakNavPath *path, f32 arrive_radius);
Vec3 break_nav_follow_wish(BreakNavFollower *follower, Vec3 position, f32 speed, f32 dt);
bool break_nav_follow_arrived(const BreakNavFollower *follower);

typedef struct BreakSight {
    Vec3 eye;
    Vec3 forward; /* must be approximately unit length */
    f32 distance;
    f32 half_angle_rad;
} BreakSight;

typedef struct BreakSightTarget {
    Entity entity;
    Vec3 point;
} BreakSightTarget;

typedef bool (*BreakSightRayFn)(void *user, Vec3 from, Vec3 to);

BreakNavError break_sight_query(const BreakSight *sight,
                                const BreakSightTarget *targets, u32 target_count,
                                BreakSightRayFn ray_clear, void *user,
                                Entity *out_visible, u32 cap, u32 *out_count);

typedef struct BreakBlackboard {
    Entity target;
    Vec3 last_seen;
    bool seen;
    bool attack;
} BreakBlackboard;

typedef enum BreakNodeKind {
    BREAK_NODE_SELECTOR = 1,
    BREAK_NODE_SEQUENCE,
    BREAK_NODE_LEAF
} BreakNodeKind;

typedef enum BreakLeafKind {
    BREAK_LEAF_IDLE = 1,
    BREAK_LEAF_CHASE,
    BREAK_LEAF_ATTACK
} BreakLeafKind;

typedef struct BreakNode {
    BreakNodeKind kind;
    BreakLeafKind leaf;
    u16 child_begin;
    u16 child_count;
} BreakNode;

typedef enum BreakBehaveStatus {
    BREAK_BEHAVE_SUCCESS = 1,
    BREAK_BEHAVE_FAILURE,
    BREAK_BEHAVE_RUNNING
} BreakBehaveStatus;

typedef struct BreakBehaveResult {
    BreakBehaveStatus status;
    Vec3 wish;
    bool attack;
} BreakBehaveResult;

BreakBehaveStatus break_behavior_tick(const BreakNode *nodes, u32 node_count, u32 root,
                                      BreakBlackboard *board,
                                      BreakNavFollower *follower,
                                      Vec3 self_position, f32 dt,
                                      BreakBehaveResult *out);

typedef struct BreakSteerNeighbor {
    Vec3 position;
    f32 radius;
} BreakSteerNeighbor;

Vec3 break_steer_avoid(Vec3 self, f32 self_radius, Vec3 wish,
                       const BreakSteerNeighbor *neighbors, u32 count);

typedef struct BreakSteerAgent {
    Vec3 position;
    Vec3 velocity;
    f32 radius;
} BreakSteerAgent;

typedef struct BreakAiAgentDesc {
    Vec3 position;
    Vec3 velocity;
    f32 radius;
    f32 max_speed;
} BreakAiAgentDesc;

BreakNavError break_steer_avoid_velocity(Vec3 self, Vec3 self_velocity,
                                         f32 self_radius, f32 max_speed,
                                         Vec3 desired_velocity,
                                         const BreakSteerAgent *neighbors,
                                         u32 count, f32 horizon, Vec3 *out_velocity);
BreakNavError break_ai_agent_add(BreakAiRuntime *runtime, Entity entity,
                                 const BreakAiAgentDesc *desc);
BreakNavError break_ai_agent_update(BreakAiRuntime *runtime, Entity entity,
                                    const BreakAiAgentDesc *desc);
BreakNavError break_ai_agent_remove(BreakAiRuntime *runtime, Entity entity);
BreakNavError break_ai_agent_avoid(BreakAiRuntime *runtime, Entity self,
                                   Vec3 desired_velocity, f32 horizon,
                                   Vec3 *out_velocity);

typedef struct BreakAiFormationHandle {
    u32 index;
    u32 generation;
} BreakAiFormationHandle;

BreakNavError break_ai_formation_create(BreakAiRuntime *runtime, const Entity *members,
                                        u32 member_count, f32 spacing,
                                        BreakAiFormationHandle *out);
BreakNavError break_ai_formation_destroy(BreakAiRuntime *runtime,
                                         BreakAiFormationHandle handle);
BreakNavError break_ai_formation_slots(BreakAiRuntime *runtime,
                                       BreakAiFormationHandle handle,
                                       Vec3 leader_position, Vec3 leader_forward,
                                       Vec3 *out_slots, u32 cap, u32 *out_count);
BreakNavError break_ai_formation_tick(BreakAiRuntime *runtime,
                                      BreakAiFormationHandle handle, f32 dt,
                                      Vec3 *out_velocities, u32 cap, u32 *out_count);

typedef struct BreakAiSmartObjectHandle {
    u32 index;
    u32 generation;
} BreakAiSmartObjectHandle;

BreakNavError break_ai_smart_object_add(BreakAiRuntime *runtime, Vec3 position,
                                        BreakAiSmartObjectHandle *out);
BreakNavError break_ai_smart_object_remove(BreakAiRuntime *runtime,
                                           BreakAiSmartObjectHandle handle);
BreakNavError break_ai_smart_object_reserve(BreakAiRuntime *runtime,
                                            BreakAiSmartObjectHandle handle,
                                            Entity agent);
BreakNavError break_ai_smart_object_release(BreakAiRuntime *runtime,
                                            BreakAiSmartObjectHandle handle,
                                            Entity agent);
BreakNavError break_ai_smart_object_owner(BreakAiRuntime *runtime,
                                          BreakAiSmartObjectHandle handle,
                                          Entity *out_owner);

#ifdef __cplusplus
} /* extern "C" */
#endif
