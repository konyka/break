#pragma once
#include <ai/break_nav_internal.h>
#include <core/platform_thread.h>

typedef struct BreakAiObstacleSlot {
    BreakAiObstacleDesc desc;
    u32 generation;
    bool live;
} BreakAiObstacleSlot;

typedef struct BreakAiCacheEntry {
    Vec3 start;
    Vec3 end;
    BreakAiPath result;
    u32 nav_version;
    bool valid;
} BreakAiCacheEntry;

typedef struct BreakAiAgentSlot {
    Entity entity;
    BreakAiAgentDesc desc;
    bool live;
} BreakAiAgentSlot;

struct BreakAiRuntime {
    BreakNavMesh *mesh;
    PlatformThreadId owner;
    BreakNavWorkspace *workspace;
    u32 nav_version;
    BreakAiObstacleSlot *obstacles;
    u32 max_obstacles;
    u32 *blocked_counts;
    BreakAiCacheEntry *cache;
    u32 max_cached_paths;
    u32 cache_next;
    BreakAiAgentSlot *agents;
    u32 max_agents;
};

bool break_ai_is_owner(const BreakAiRuntime *runtime);
u32 break_ai_agent_index(const BreakAiRuntime *runtime, Entity entity);
