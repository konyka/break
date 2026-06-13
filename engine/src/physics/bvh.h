#ifndef BVH_H
#define BVH_H

#include "../core/types.h"
#include "../math/math.h"

#define BVH_NULL 0xFFFFFFFF

typedef struct {
    Vec3 min, max;
} BVHAABB;

typedef struct {
    BVHAABB bounds;
    u32 left;           /* left child index (BVH_NULL = leaf) */
    u32 right;          /* right child index */
    u32 object_index;   /* leaf: object index; internal: BVH_NULL */
    u32 parent;         /* parent node index (for refit) */
} BVHNode;

typedef struct {
    BVHNode *nodes;
    u32 node_count;
    u32 capacity;
    u32 root;
    u32 *leaf_map;      /* object_index -> node_index mapping */
    u32 object_count;
    /* Persistent build buffer (avoids per-build malloc/free) */
    u32 *_build_indices;
    u32  _build_indices_cap;
} BVH;

/* Lifecycle */
void bvh_init(BVH *bvh, u32 initial_capacity);
void bvh_destroy(BVH *bvh);

/* Build (SAH) */
void bvh_build(BVH *bvh, const BVHAABB *aabbs, u32 count);

/* Incremental update */
void bvh_refit(BVH *bvh, u32 object_index, BVHAABB new_bounds);

/* Query */
typedef void (*BVHPairCallback)(u32 a, u32 b, void *ctx);
void bvh_query_pairs(const BVH *bvh, BVHPairCallback callback, void *ctx);

typedef struct {
    u32 object_index;
    f32 t;         /* hit distance */
} BVHRayHit;

bool bvh_raycast(const BVH *bvh, Vec3 origin, Vec3 dir, f32 max_dist, BVHRayHit *hit);

/* Single-object query: find all objects overlapping a given AABB */
u32 bvh_query_aabb(const BVH *bvh, BVHAABB query, u32 *results, u32 max_results);

#endif
