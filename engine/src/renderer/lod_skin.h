#pragma once
#include <renderer/lod_gen.h>
#include <renderer/lod_cache.h>
#include <math/math.h>

/* R707a: runtime LOD for skinned meshes (CPU only). vertices are 64-byte
 * SkinnedVertex records: pos3 nrm3 uv2 (f32), joints[4] (u32), weights[4]
 * (f32, normalised by the loader). poses[p * joint_count + j] is joint j's
 * skin matrix (world x inverse_bind, column-major e[col][row]) in pose p.
 *
 * Skinning convention (shared by every function here): position =
 * sum_k weights[k] * (M[joints[k]] * pos). A joint index >= joint_count is
 * clamped to joint_count - 1. A vertex whose weights sum to <= 0 (or are not
 * finite) keeps its bind position. */

#define LOD_SKIN_VERTEX_STRIDE 64u
#define LOD_SKIN_MAX_JOINTS    128u   /* = SKELETON_MAX_JOINTS */
#define LOD_SKIN_MAX_POSES     8u     /* sampled poses fed to the simplifier */

/* Levels share LOD0's vertices (the SkinnedVertex joints/weights are reused
 * as-is). Attributes: normal (0.5) + uv (1.0) + the skinned position in up
 * to LOD_SKIN_MAX_POSES poses (evenly picked when pose_count is larger),
 * divided by the bind-pose meshopt scale (1.0). pose_count 0: bind pose
 * only, plus meshopt vertex locks on vertices whose dominant joint differs
 * from a neighbour's. Same level ratios / error caps / stop ratio /
 * LockBorder as lod_generate_levels. rel_error is measured, not meshopt's:
 * the symmetric deviation of LODn from LOD0 over the bind pose and every
 * sampled pose (LOD0 vertices dropped by LODn against LODn triangles,
 * LODn triangle centroids and edge midpoints against LOD0 triangles, exact
 * nearest triangle via a uniform grid), maximum / scale, non-decreasing. scale is
 * meshopt_simplifyScale of the bind positions. Invalid input (NULL, zero
 * counts, index out of range, joint_count 0 or > LOD_SKIN_MAX_JOINTS, NULL
 * or non-finite poses) yields level_count 1. */
void lod_generate_levels_skinned(const f32 *vertices, u32 vertex_count,
                                 const u32 *indices, u32 index_count,
                                 const Mat4 *poses, u32 pose_count, u32 joint_count,
                                 u32 max_levels, LodMeshLevels *out);

/* Skinned xyz of every vertex under skin_mats[joint_count] (NULL = bind
 * pose) into out_xyz[vertex_count * 3]. Returns false on invalid input. */
bool lod_skin_positions(const f32 *vertices, u32 vertex_count,
                        const Mat4 *skin_mats, u32 joint_count, f32 *out_xyz);

typedef struct { f32 c[3]; f32 r; } LodSphere;   /* r < 0 = empty */

/* Per joint: sphere around the bind positions of vertices that give it a
 * weight > 0 (AABB centre, max distance). Vertices without positive weight
 * sum are not covered (they have no defined skinned position on the GPU). */
void lod_skin_joint_spheres(const f32 *vertices, u32 vertex_count, u32 joint_count,
                            LodSphere *out /* [joint_count] */);

/* Conservative sphere around the mesh under skin_mats: each joint sphere is
 * transformed (centre by the matrix, radius by a bound on the 3x3 part's
 * spectral norm: the max column norm for orthogonal columns, a Gershgorin
 * bound on A^T A otherwise), then all are merged. Exact containment
 * assumes non-negative weights summing to 1. Empty input -> r = -1. */
LodSphere lod_skin_bounds(const LodSphere *joint_spheres, u32 joint_count,
                          const Mat4 *skin_mats);

/* lod_generate_levels_skinned through the R704 disk cache. The key also
 * covers a "skinned" tag, joint_count, pose_count and the pose matrices. */
LodCacheKey lod_skin_cache_key(const f32 *vertices, u32 vertex_count,
                               const u32 *indices, u32 index_count,
                               const Mat4 *poses, u32 pose_count, u32 joint_count,
                               u32 max_levels);
void lod_skin_cache_generate(LodCache *cache, const f32 *vertices, u32 vertex_count,
                             const u32 *indices, u32 index_count,
                             const Mat4 *poses, u32 pose_count, u32 joint_count,
                             u32 max_levels, LodMeshLevels *out);
