#pragma once
#include <core/types.h>

/* Runtime LOD generation (phase 1): simplified index buffers that reference
 * the LOD0 vertices (meshopt_c simplifier), plus the bake-table validator
 * for the mega buffer's node x level command layout. */

#define LOD_GEN_MAX_LEVELS     3u     /* LOD0 + 2 simplified levels */
#define LOD_GEN_MIN_TRIANGLES  512u   /* smaller meshes keep LOD0 only */
#define LOD_GEN_STOP_RATIO     0.85f  /* a level above 85% of the previous one stops the chain */

typedef struct {
    u32  level_count;                        /* 1..LOD_GEN_MAX_LEVELS; 1 = LOD0 only */
    u32 *indices[LOD_GEN_MAX_LEVELS];        /* [0] unused (LOD0 = source); [l] owned, into LOD0 vertices */
    u32  index_count[LOD_GEN_MAX_LEVELS];    /* [0] = source index count */
    f32  rel_error[LOD_GEN_MAX_LEVELS];      /* meshopt result_error vs LOD0, relative to mesh extent; [0] = 0 */
    f32  scale;                              /* meshopt_simplifyScale(positions): rel -> local units */
    bool authored;                           /* R705: levels reference authored meshes, not simplifier output */
} LodMeshLevels;

/* vertices: vertex_stride bytes per vertex, pos3 at offset 0, nrm3 at 12,
 * uv2 at 24 (the engine's 32-byte Vertex). Simplifies in the mesh's local
 * space; every level is produced from LOD0 so rel_error is always measured
 * against LOD0. Never fails hard: invalid input or allocation failure leaves
 * fewer levels (level_count 1 at worst). */
void lod_generate_levels(const f32 *vertices, u32 vertex_count, u32 vertex_stride,
                         const u32 *indices, u32 index_count, u32 max_levels,
                         LodMeshLevels *out);
void lod_mesh_levels_free(LodMeshLevels *levels);

/* R705: geometric deviation of an authored (glTF MSFT_lod) level vs LOD0, in
 * local units: symmetric Hausdorff estimate = max over sampled vertices of one
 * mesh of the distance to the nearest triangle of the other, both directions.
 * Vertex samples per direction are capped so samples x triangles stays near
 * LOD_AUTHORED_ERROR_BUDGET point-triangle tests (min 64 samples). Indices
 * must be < their vertex counts. Returns a negative value on invalid input. */
#define LOD_AUTHORED_ERROR_BUDGET (1u << 24)
f32 lod_authored_error(const f32 *base_v, u32 base_vc, const u32 *base_i, u32 base_ic,
                       const f32 *alt_v, u32 alt_vc, const u32 *alt_i, u32 alt_ic,
                       u32 vertex_stride);

/* Bake-table consistency check. cmds: cmd_count DrawIndexedIndirect commands
 * of 5 u32 words each (index_count, instance_count, first_index,
 * vertex_offset, first_instance). Nodes are dense mega-node indices; node b
 * owns commands [node_cmd_base[b], node_cmd_base[b] + node_level_count[b])
 * and vertices [node_vbase[b], node_vbase[b] + node_vcount[b]). Returns false
 * with a message in err on the first violation. */
bool lod_bake_validate(const u32 *cmds, u32 cmd_count,
                       const u32 *indices, u32 index_total, u32 vertex_total,
                       const u32 *node_cmd_base, const u8 *node_level_count,
                       const u32 *node_vbase, const u32 *node_vcount, u32 node_count,
                       const u32 *cmd_node, const u8 *cmd_level,
                       char *err, usize err_len);
/* Optional per-command vertex ranges for authored LODs with their own vertices.
 * NULL ranges preserve the original shared-LOD0 validation. */
bool lod_bake_validate_ex(const u32 *cmds, u32 cmd_count,
                          const u32 *indices, u32 index_total, u32 vertex_total,
                          const u32 *node_cmd_base, const u8 *node_level_count,
                          const u32 *node_vbase, const u32 *node_vcount, u32 node_count,
                          const u32 *cmd_node, const u8 *cmd_level,
                          const u32 *cmd_vbase, const u32 *cmd_vcount,
                          char *err, usize err_len);
