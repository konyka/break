#pragma once
#include <ai/break_ai.h>
#include <stdatomic.h>

typedef struct BreakNavPoly {
    Vec3 center;
    u32 neighbors[4];
    u32 neighbor_count;
    u32 component;
    u32 cell_x;
    u32 cell_z;
} BreakNavPoly;

typedef struct BreakNavWorkspace {
    u32 poly_count;
    f32 *gscore;
    f32 *fscore;
    u32 *came;
    u8 *closed;
    u32 *heap;
    u32 *chain;
} BreakNavWorkspace;

#define BREAK_NAV_QUERY_POOL_CAPACITY 4u

typedef struct BreakNavWorkspacePool BreakNavWorkspacePool;

struct BreakNavMesh {
    u32 width;
    u32 depth;
    f32 origin_x;
    f32 origin_z;
    f32 cell;
    u32 *cell_poly; /* UINT32_MAX when the cell is not walkable */
    BreakNavPoly *polys;
    u32 poly_count;
    BreakNavWorkspacePool *workspace_pool;
};

BreakNavWorkspace *break_nav_workspace_create(u32 poly_count);
void break_nav_workspace_destroy(BreakNavWorkspace *workspace);
BreakNavWorkspacePool *break_nav_workspace_pool_create(u32 poly_count);
void break_nav_workspace_pool_destroy(BreakNavWorkspacePool *pool);
BreakNavWorkspace *break_nav_workspace_pool_acquire(const BreakNavMesh *mesh, u32 *out_slot);
void break_nav_workspace_pool_release(const BreakNavMesh *mesh, u32 slot);
bool break_nav_locate(const BreakNavMesh *mesh, Vec3 point, u32 *out_poly);
BreakNavError break_nav_find_path_workspace(const BreakNavMesh *mesh,
                                            BreakNavWorkspace *workspace,
                                            const u32 *blocked_counts,
                                            Vec3 start, Vec3 end,
                                            BreakNavPath *out);
