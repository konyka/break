#pragma once
#include <ai/break_ai.h>

typedef struct BreakNavPoly {
    Vec3 center;
    u32 neighbors[4];
    u32 neighbor_count;
    u32 component;
    u32 cell_x;
    u32 cell_z;
} BreakNavPoly;

struct BreakNavMesh {
    u32 width;
    u32 depth;
    f32 origin_x;
    f32 origin_z;
    f32 cell;
    u32 *cell_poly; /* UINT32_MAX when the cell is not walkable */
    BreakNavPoly *polys;
    u32 poly_count;
};

bool break_nav_locate(const BreakNavMesh *mesh, Vec3 point, u32 *out_poly);
