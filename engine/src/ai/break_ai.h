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
    BREAK_NAV_FAILED
} BreakNavError;

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
#ifdef __cplusplus
} /* extern "C" */
#endif

