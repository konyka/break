#pragma once
#include <renderer/cull.h>

/*
 * Frustum culling batch API.
 *
 * Builds on the existing Frustum type from cull.h (Vec4 planes[6]).
 * Adds AABB structure and batch culling for efficient CPU-side visibility
 * determination before GPU occlusion culling.
 */

typedef struct {
    Vec3 min;
    Vec3 max;
} CullAABB;

/* Extract frustum planes from view-projection matrix (pointer variant) */
void frustum_extract(Frustum *f, const Mat4 *vp);

/* Batch cull: returns visible object count, visible_indices stores indices */
u32 frustum_cull_batch(const Frustum *f, const CullAABB *aabbs, u32 count,
                       u32 *visible_indices);
