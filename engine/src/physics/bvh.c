#include <physics/bvh.h>
#include <math/simd.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <float.h>

#if defined(__SSE2__) || defined(_M_X64) || (defined(_M_IX86_FP) && _M_IX86_FP >= 2)
    #include <immintrin.h>
    #define BVH_SSE2 1
#else
    #define BVH_SSE2 0
#endif

#define BVH_MAX_DEPTH 32
#define BVH_SAH_BINS  8

/* ---- AABB helpers ---- */
static BVHAABB bvhaabb_union(BVHAABB a, BVHAABB b) {
    BVHAABB r;
#if BVH_SSE2
    /* _mm_loadu_ps on min.e is safe: reads 16 bytes covering min[0..2] + max[0],
     * all within the BVHAABB struct.  Position [3] is ignored by _mm_min/_mm_max
     * which only operate on [0..2]. */
    __m128 a_min = _mm_loadu_ps(a.min.e);
    __m128 b_min = _mm_loadu_ps(b.min.e);
    __m128 r_min = _mm_min_ps(a_min, b_min);

    /* For max, use _mm_set_ps to avoid reading past the struct end (max has
     * only 3 floats). */
    __m128 a_max = _mm_set_ps(0.0f, a.max.e[2], a.max.e[1], a.max.e[0]);
    __m128 b_max = _mm_set_ps(0.0f, b.max.e[2], b.max.e[1], b.max.e[0]);
    __m128 r_max = _mm_max_ps(a_max, b_max);

    /* Store strategy: store r_min (16 bytes) starting at r.min.e — writes
     * min[0..2] + max[0] (safe).  Then overwrite r.max[0..2] with r_max
     * components extracted via shuffle + cvtss. */
    _mm_storeu_ps(r.min.e, r_min);
    r.max.e[0] = _mm_cvtss_f32(r_max);
    r.max.e[1] = _mm_cvtss_f32(_mm_shuffle_ps(r_max, r_max, _MM_SHUFFLE(1, 1, 1, 1)));
    r.max.e[2] = _mm_cvtss_f32(_mm_shuffle_ps(r_max, r_max, _MM_SHUFFLE(2, 2, 2, 2)));
#else
    for (int i = 0; i < 3; i++) {
        r.min.e[i] = a.min.e[i] < b.min.e[i] ? a.min.e[i] : b.min.e[i];
        r.max.e[i] = a.max.e[i] > b.max.e[i] ? a.max.e[i] : b.max.e[i];
    }
#endif
    return r;
}

static f32 bvhaabb_surface_area(BVHAABB b) {
    f32 dx = b.max.e[0] - b.min.e[0];
    f32 dy = b.max.e[1] - b.min.e[1];
    f32 dz = b.max.e[2] - b.min.e[2];
    return 2.0f * (dx * dy + dy * dz + dz * dx);
}

static f32 bvhaabb_centroid_axis(BVHAABB b, int axis) {
    return 0.5f * (b.min.e[axis] + b.max.e[axis]);
}

static bool bvhaabb_overlap(BVHAABB a, BVHAABB b) {
#if SIMD_SSE2
    /* Use SIMD-optimized version */
    return simd_aabb_overlap_sse2(
        a.min.e, a.max.e,
        b.min.e, b.max.e) != 0;
#else
    for (int i = 0; i < 3; i++) {
        if (a.max.e[i] < b.min.e[i] || b.max.e[i] < a.min.e[i])
            return false;
    }
    return true;
#endif
}

/* ---- Lifecycle ---- */
void bvh_init(BVH *bvh, u32 initial_capacity) {
    u32 cap = initial_capacity < 4 ? 4 : initial_capacity;
    u32 node_cap = cap * 2;
    bvh->nodes = (BVHNode *)calloc(node_cap, sizeof(BVHNode));
    bvh->capacity = node_cap;
    bvh->node_count = 0;
    bvh->root = BVH_NULL;
    bvh->leaf_map = NULL;
    bvh->object_count = 0;
    bvh->_build_indices = NULL;
    bvh->_build_indices_cap = 0;
}

void bvh_destroy(BVH *bvh) {
    free(bvh->nodes);
    free(bvh->leaf_map);
    free(bvh->_build_indices);
    bvh->nodes = NULL;
    bvh->leaf_map = NULL;
    bvh->_build_indices = NULL;
    bvh->node_count = 0;
    bvh->capacity = 0;
    bvh->root = BVH_NULL;
    bvh->object_count = 0;
}

static u32 bvh_alloc_node(BVH *bvh) {
    if (bvh->node_count >= bvh->capacity) {
        u32 new_cap = bvh->capacity * 2;
        bvh->nodes = (BVHNode *)realloc(bvh->nodes, new_cap * sizeof(BVHNode));
        memset(&bvh->nodes[bvh->capacity], 0, (new_cap - bvh->capacity) * sizeof(BVHNode));
        bvh->capacity = new_cap;
    }
    u32 idx = bvh->node_count++;
    bvh->nodes[idx].left = BVH_NULL;
    bvh->nodes[idx].right = BVH_NULL;
    bvh->nodes[idx].object_index = BVH_NULL;
    bvh->nodes[idx].parent = BVH_NULL;
    return idx;
}

/* ---- SAH Build ---- */
typedef struct {
    BVHAABB bounds;
    u32 count;
} SAHBin;

static u32 bvh_build_recursive(BVH *bvh, const BVHAABB *aabbs, u32 *indices,
                                u32 start, u32 end, u32 depth) {
    u32 count = end - start;
    u32 node_idx = bvh_alloc_node(bvh);

    /* Compute bounds for this node */
    BVHAABB node_bounds = aabbs[indices[start]];
    for (u32 i = start + 1; i < end; i++) {
        node_bounds = bvhaabb_union(node_bounds, aabbs[indices[i]]);
    }
    bvh->nodes[node_idx].bounds = node_bounds;

    /* Leaf condition */
    if (count <= 1 || depth >= BVH_MAX_DEPTH) {
        /* Single-object leaf */
        bvh->nodes[node_idx].object_index = indices[start];
        bvh->leaf_map[indices[start]] = node_idx;
        return node_idx;
    }

    /* Find best split using SAH with binning */
    f32 best_cost = FLT_MAX;
    int best_axis = 0;
    u32 best_split = start + count / 2; /* fallback: midpoint */
    u32 best_split_bin = 0;            /* bin index for best split */
    f32 best_axis_min = 0.0f, best_inv_ext = 0.0f;

    f32 parent_sa = bvhaabb_surface_area(node_bounds);
    if (parent_sa < 1e-12f) parent_sa = 1e-12f;

    for (int axis = 0; axis < 3; axis++) {
        f32 axis_min = node_bounds.min.e[axis];
        f32 axis_max = node_bounds.max.e[axis];
        f32 extent = axis_max - axis_min;
        if (extent < 1e-7f) continue;

        SAHBin bins[BVH_SAH_BINS];
        memset(bins, 0, sizeof(bins));
        /* Initialize bins with invalid bounds */
        for (int b = 0; b < BVH_SAH_BINS; b++) {
            bins[b].bounds.min = vec3(FLT_MAX, FLT_MAX, FLT_MAX);
            bins[b].bounds.max = vec3(-FLT_MAX, -FLT_MAX, -FLT_MAX);
            bins[b].count = 0;
        }

        f32 inv_extent = (f32)BVH_SAH_BINS / extent;
        for (u32 i = start; i < end; i++) {
            f32 c = bvhaabb_centroid_axis(aabbs[indices[i]], axis);
            int bin_idx = (int)((c - axis_min) * inv_extent);
            if (bin_idx >= BVH_SAH_BINS) bin_idx = BVH_SAH_BINS - 1;
            if (bin_idx < 0) bin_idx = 0;
            if (bins[bin_idx].count == 0) {
                bins[bin_idx].bounds = aabbs[indices[i]];
            } else {
                bins[bin_idx].bounds = bvhaabb_union(bins[bin_idx].bounds, aabbs[indices[i]]);
            }
            bins[bin_idx].count++;
        }

        /* Sweep from left to compute prefix bounds and counts */
        BVHAABB left_bounds[BVH_SAH_BINS - 1];
        u32 left_counts[BVH_SAH_BINS - 1];
        BVHAABB running = bins[0].bounds;
        u32 running_count = bins[0].count;
        for (int b = 0; b < BVH_SAH_BINS - 1; b++) {
            if (b > 0) {
                if (bins[b].count > 0) {
                    if (running_count == 0) {
                        running = bins[b].bounds;
                    } else {
                        running = bvhaabb_union(running, bins[b].bounds);
                    }
                }
                running_count += bins[b].count;
            }
            left_bounds[b] = running;
            left_counts[b] = running_count;
        }

        /* Sweep from right to evaluate each split */
        BVHAABB right_running = bins[BVH_SAH_BINS - 1].bounds;
        u32 right_count = bins[BVH_SAH_BINS - 1].count;
        for (int b = BVH_SAH_BINS - 2; b >= 0; b--) {
            u32 lc = left_counts[b];
            u32 rc = right_count;
            if (lc == 0 || rc == 0) {
                if (bins[b].count > 0) {
                    if (right_count == 0) {
                        right_running = bins[b].bounds;
                    } else {
                        right_running = bvhaabb_union(right_running, bins[b].bounds);
                    }
                }
                right_count += bins[b].count;
                continue;
            }

            f32 left_sa = bvhaabb_surface_area(left_bounds[b]);
            f32 right_sa = bvhaabb_surface_area(right_running);
            f32 cost = left_sa * (f32)lc + right_sa * (f32)rc;

            if (cost < best_cost) {
                best_cost = cost;
                best_axis = axis;
                best_split = start + lc;
                best_split_bin = (u32)b;
                best_axis_min = axis_min;
                best_inv_ext = inv_extent;
            }

            if (bins[b].count > 0) {
                if (right_count == 0) {
                    right_running = bins[b].bounds;
                } else {
                    right_running = bvhaabb_union(right_running, bins[b].bounds);
                }
            }
            right_count += bins[b].count;
        }
    }

    /* Partition indices by best_axis at best_split position */
    f32 axis_min = node_bounds.min.e[best_axis];
    f32 axis_max = node_bounds.max.e[best_axis];
    f32 extent = axis_max - axis_min;

    if (extent < 1e-7f) {
        /* Degenerate: just split in half */
        best_split = start + count / 2;
    } else {
        /* Use cached split_bin from SAH sweep — no need to re-scan centroids */
        f32 inv_ext = best_inv_ext > 0.0f ? best_inv_ext : (f32)BVH_SAH_BINS / extent;
        f32 a_min = best_inv_ext > 0.0f ? best_axis_min : axis_min;
        u32 split_bin = best_split_bin;

        /* Partition: left = centroids in bins <= split_bin, right = rest */
        u32 lo = start, hi = end - 1;
        while (lo < hi) {
            f32 c = bvhaabb_centroid_axis(aabbs[indices[lo]], best_axis);
            int bi = (int)((c - a_min) * inv_ext);
            if (bi >= BVH_SAH_BINS) bi = BVH_SAH_BINS - 1;
            if (bi < 0) bi = 0;
            if ((u32)bi <= split_bin) {
                lo++;
            } else {
                u32 tmp = indices[lo];
                indices[lo] = indices[hi];
                indices[hi] = tmp;
                hi--;
            }
        }
        best_split = lo;
        /* Ensure non-empty partitions */
        if (best_split <= start) best_split = start + 1;
        if (best_split >= end) best_split = end - 1;
    }

    u32 left = bvh_build_recursive(bvh, aabbs, indices, start, best_split, depth + 1);
    u32 right = bvh_build_recursive(bvh, aabbs, indices, best_split, end, depth + 1);

    bvh->nodes[node_idx].left = left;
    bvh->nodes[node_idx].right = right;
    bvh->nodes[left].parent = node_idx;
    bvh->nodes[right].parent = node_idx;

    return node_idx;
}

void bvh_build(BVH *bvh, const BVHAABB *aabbs, u32 count) {
    /* Reset */
    bvh->node_count = 0;
    bvh->object_count = count;
    free(bvh->leaf_map);
    bvh->leaf_map = (u32 *)calloc(count, sizeof(u32));

    if (count == 0) {
        bvh->root = BVH_NULL;
        return;
    }

    /* Ensure capacity */
    u32 max_nodes = count * 2;
    if (bvh->capacity < max_nodes) {
        free(bvh->nodes);
        bvh->nodes = (BVHNode *)calloc(max_nodes, sizeof(BVHNode));
        bvh->capacity = max_nodes;
    }

    /* Build index array (persistent buffer — grow if needed) */
    if (count > bvh->_build_indices_cap) {
        free(bvh->_build_indices);
        bvh->_build_indices = (u32 *)malloc(count * sizeof(u32));
        bvh->_build_indices_cap = count;
    }
    u32 *indices = bvh->_build_indices;
    for (u32 i = 0; i < count; i++) indices[i] = i;

    bvh->root = bvh_build_recursive(bvh, aabbs, indices, 0, count, 0);
    bvh->nodes[bvh->root].parent = BVH_NULL;
}

/* ---- Incremental Refit ---- */
void bvh_refit(BVH *bvh, u32 object_index, BVHAABB new_bounds) {
    if (object_index >= bvh->object_count) return;
    u32 leaf_idx = bvh->leaf_map[object_index];
    bvh->nodes[leaf_idx].bounds = new_bounds;

    /* Walk up to root, updating bounds */
    u32 current = bvh->nodes[leaf_idx].parent;
    while (current != BVH_NULL) {
        BVHNode *node = &bvh->nodes[current];
        BVHAABB left_b = bvh->nodes[node->left].bounds;
        BVHAABB right_b = bvh->nodes[node->right].bounds;
        node->bounds = bvhaabb_union(left_b, right_b);
        current = node->parent;
    }
}

/* ---- Query: AABB overlap ---- */
static void bvh_query_aabb_recursive(const BVH *bvh, u32 node_idx,
                                     BVHAABB query, u32 *results,
                                     u32 max_results, u32 *found) {
    if (node_idx == BVH_NULL || *found >= max_results) return;

    const BVHNode *node = &bvh->nodes[node_idx];
    if (!bvhaabb_overlap(node->bounds, query)) return;

    if (node->object_index != BVH_NULL) {
        /* Leaf node */
        results[*found] = node->object_index;
        (*found)++;
        return;
    }

    bvh_query_aabb_recursive(bvh, node->left, query, results, max_results, found);
    bvh_query_aabb_recursive(bvh, node->right, query, results, max_results, found);
}

u32 bvh_query_aabb(const BVH *bvh, BVHAABB query, u32 *results, u32 max_results) {
    if (bvh->root == BVH_NULL) return 0;
    u32 found = 0;
    bvh_query_aabb_recursive(bvh, bvh->root, query, results, max_results, &found);
    return found;
}

/* ---- Query: collision pairs (dual-traversal O(N log N)) ---- */
static void bvh_query_pairs_dual(const BVH *bvh, u32 nodeA, u32 nodeB,
                                  BVHPairCallback callback, void *ctx) {
    if (nodeA == BVH_NULL || nodeB == BVH_NULL) return;

    const BVHNode *nA = &bvh->nodes[nodeA];
    const BVHNode *nB = &bvh->nodes[nodeB];

    if (!bvhaabb_overlap(nA->bounds, nB->bounds)) return;

    bool leafA = (nA->object_index != BVH_NULL);
    bool leafB = (nB->object_index != BVH_NULL);

    if (leafA && leafB) {
        /* Both leaves: report pair (enforce a < b to avoid duplicates) */
        u32 a = nA->object_index, b = nB->object_index;
        if (a < b) callback(a, b, ctx);
        return;
    }

    if (leafA) {
        /* Descend nodeB */
        bvh_query_pairs_dual(bvh, nodeA, nB->left, callback, ctx);
        bvh_query_pairs_dual(bvh, nodeA, nB->right, callback, ctx);
        return;
    }

    if (leafB) {
        /* Descend nodeA */
        bvh_query_pairs_dual(bvh, nA->left, nodeB, callback, ctx);
        bvh_query_pairs_dual(bvh, nA->right, nodeB, callback, ctx);
        return;
    }

    /* Both internal: cross-descend, handle self-pair case */
    if (nodeA == nodeB) {
        /* Self-pair: avoid double-reporting by only doing LL, RR, LR */
        bvh_query_pairs_dual(bvh, nA->left, nB->left, callback, ctx);
        bvh_query_pairs_dual(bvh, nA->right, nB->right, callback, ctx);
        bvh_query_pairs_dual(bvh, nA->left, nB->right, callback, ctx);
    } else {
        bvh_query_pairs_dual(bvh, nA->left, nB->left, callback, ctx);
        bvh_query_pairs_dual(bvh, nA->left, nB->right, callback, ctx);
        bvh_query_pairs_dual(bvh, nA->right, nB->left, callback, ctx);
        bvh_query_pairs_dual(bvh, nA->right, nB->right, callback, ctx);
    }
}

void bvh_query_pairs(const BVH *bvh, BVHPairCallback callback, void *ctx) {
    if (bvh->root == BVH_NULL || bvh->object_count == 0) return;
    bvh_query_pairs_dual(bvh, bvh->root, bvh->root, callback, ctx);
}

/* ---- Raycast ---- */
static bool ray_aabb_intersect(Vec3 origin, Vec3 inv_dir, BVHAABB box,
                               f32 max_t, f32 *out_t) {
#if SIMD_SSE2
    /* Use SIMD-optimized version */
    return simd_ray_aabb_intersect_sse2(
        origin.e, inv_dir.e,
        box.min.e, box.max.e,
        max_t, out_t) != 0;
#else
    f32 tmin = 0.0f;
    f32 tmax = max_t;

    for (int i = 0; i < 3; i++) {
        f32 t1 = (box.min.e[i] - origin.e[i]) * inv_dir.e[i];
        f32 t2 = (box.max.e[i] - origin.e[i]) * inv_dir.e[i];
        if (t1 > t2) { f32 tmp = t1; t1 = t2; t2 = tmp; }
        if (t1 > tmin) tmin = t1;
        if (t2 < tmax) tmax = t2;
        if (tmin > tmax) return false;
    }
    *out_t = tmin;
    return true;
#endif
}

static void bvh_raycast_recursive(const BVH *bvh, u32 node_idx,
                                   Vec3 origin, Vec3 inv_dir,
                                   f32 *best_t, u32 *best_obj) {
    if (node_idx == BVH_NULL) return;

    const BVHNode *node = &bvh->nodes[node_idx];
    f32 t;
    if (!ray_aabb_intersect(origin, inv_dir, node->bounds, *best_t, &t)) return;

    if (node->object_index != BVH_NULL) {
        /* Leaf node - t is already the intersection distance */
        if (t < *best_t) {
            *best_t = t;
            *best_obj = node->object_index;
        }
        return;
    }

    /* Determine traversal order: visit closer child first */
    f32 t_left = FLT_MAX, t_right = FLT_MAX;
    bool hit_left = ray_aabb_intersect(origin, inv_dir, bvh->nodes[node->left].bounds, *best_t, &t_left);
    bool hit_right = ray_aabb_intersect(origin, inv_dir, bvh->nodes[node->right].bounds, *best_t, &t_right);

    if (hit_left && hit_right) {
        u32 first = node->left, second = node->right;
        if (t_right < t_left) {
            first = node->right;
            second = node->left;
        }
        bvh_raycast_recursive(bvh, first, origin, inv_dir, best_t, best_obj);
        bvh_raycast_recursive(bvh, second, origin, inv_dir, best_t, best_obj);
    } else if (hit_left) {
        bvh_raycast_recursive(bvh, node->left, origin, inv_dir, best_t, best_obj);
    } else if (hit_right) {
        bvh_raycast_recursive(bvh, node->right, origin, inv_dir, best_t, best_obj);
    }
}

bool bvh_raycast(const BVH *bvh, Vec3 origin, Vec3 dir, f32 max_dist, BVHRayHit *hit) {
    if (bvh->root == BVH_NULL) return false;

    Vec3 inv_dir;
    for (int i = 0; i < 3; i++) {
        inv_dir.e[i] = fabsf(dir.e[i]) > 1e-8f ? 1.0f / dir.e[i] : (dir.e[i] >= 0.0f ? 1e8f : -1e8f);
    }

    f32 best_t = max_dist;
    u32 best_obj = BVH_NULL;

    bvh_raycast_recursive(bvh, bvh->root, origin, inv_dir, &best_t, &best_obj);

    if (best_obj != BVH_NULL) {
        hit->object_index = best_obj;
        hit->t = best_t;
        return true;
    }
    return false;
}
