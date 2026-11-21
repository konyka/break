#ifndef BREAK_CELL_PARTITION_H
#define BREAK_CELL_PARTITION_H

#include "../core/types.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Uniform grid partition of the XZ plane into cells (design:
 * docs/design/cell_handoff.md "分区"). Cell ids are row-major: id =
 * row * columns + column, where column grows with x and row with z. Each
 * cell covers [min + i * size, min + (i + 1) * size) on both axes; positions
 * outside the grid belong to the nearest edge cell, so every position has
 * exactly one cell and the outer edge never migrates anything out.
 *
 * migrate_target adds hysteresis: an entity owned by `current` stays there
 * until it is MORE than `hysteresis` (Euclidean distance) outside the
 * current cell's rectangle, so motion along a boundary does not hand the
 * entity back and forth. The caller then starts a BreakCell handoff to the
 * returned cell. Plain value type; no allocation; thread-safe for readers. */

typedef struct {
    f32 min_x;
    f32 min_z;
    f32 cell_size;
    u32 columns;
    u32 rows;
} BreakCellPartition;

/* False for a NULL output, a non-finite origin, a cell size that is not a
 * positive finite number, zero columns or rows, or more than UINT32_MAX
 * cells. */
bool break_cell_partition_init(BreakCellPartition *p, f32 min_x, f32 min_z, f32 cell_size,
                               u32 columns, u32 rows);
u32 break_cell_partition_cell_count(const BreakCellPartition *p);
/* The cell holding (x, z), clamped to the grid; a non-finite coordinate
 * maps to column/row 0. */
u32 break_cell_partition_locate(const BreakCellPartition *p, f32 x, f32 z);
/* False for an unknown cell or a NULL output. */
bool break_cell_partition_bounds(const BreakCellPartition *p, u32 cell, f32 *min_x, f32 *min_z,
                                 f32 *max_x, f32 *max_z);
/* The cell an entity owned by `current` at (x, z) should move to; returns
 * `current` while it is within `hysteresis` of the current cell or when the
 * position is not finite. An unknown current cell or a negative or
 * non-finite hysteresis falls back to locate(). */
u32 break_cell_partition_migrate_target(const BreakCellPartition *p, u32 current, f32 x, f32 z,
                                        f32 hysteresis);

#ifdef __cplusplus
}
#endif

#endif
