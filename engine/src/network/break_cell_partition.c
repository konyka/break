#include "break_cell_partition.h"

#include <math.h>

bool break_cell_partition_init(BreakCellPartition *p, f32 min_x, f32 min_z, f32 cell_size,
                               u32 columns, u32 rows) {
    if (!p || !isfinite(min_x) || !isfinite(min_z) || !isfinite(cell_size) || !(cell_size > 0.0f) ||
        columns == 0u || rows == 0u || (u64)columns * (u64)rows > (u64)UINT32_MAX) {
        return false;
    }
    p->min_x = min_x;
    p->min_z = min_z;
    p->cell_size = cell_size;
    p->columns = columns;
    p->rows = rows;
    return true;
}

u32 break_cell_partition_cell_count(const BreakCellPartition *p) {
    return p ? p->columns * p->rows : 0u;
}

static u32 cell_partition_index(f32 v, f32 min, f32 size, u32 count) {
    f64 t;
    if (!isfinite(v)) return 0u;
    t = floor(((f64)v - (f64)min) / (f64)size);
    if (t < 0.0) return 0u;
    if (t >= (f64)count) return count - 1u;
    return (u32)t;
}

u32 break_cell_partition_locate(const BreakCellPartition *p, f32 x, f32 z) {
    u32 col;
    u32 row;
    if (!p || p->columns == 0u || p->rows == 0u) return 0u;
    col = cell_partition_index(x, p->min_x, p->cell_size, p->columns);
    row = cell_partition_index(z, p->min_z, p->cell_size, p->rows);
    return row * p->columns + col;
}

bool break_cell_partition_bounds(const BreakCellPartition *p, u32 cell, f32 *min_x, f32 *min_z,
                                 f32 *max_x, f32 *max_z) {
    u32 col;
    u32 row;
    if (!p || !min_x || !min_z || !max_x || !max_z || cell >= break_cell_partition_cell_count(p)) {
        return false;
    }
    col = cell % p->columns;
    row = cell / p->columns;
    *min_x = p->min_x + (f32)col * p->cell_size;
    *min_z = p->min_z + (f32)row * p->cell_size;
    *max_x = *min_x + p->cell_size;
    *max_z = *min_z + p->cell_size;
    return true;
}

/* Distance from v to [lo, hi] on one axis. Positions beyond the outer edge
 * of the grid measure a gap too, but locate() clamps them back to the edge
 * cell, so they never migrate out of the grid. */
static f64 cell_partition_gap(f32 v, f32 lo, f32 hi) {
    if (v < lo) return (f64)lo - (f64)v;
    if (v > hi) return (f64)v - (f64)hi;
    return 0.0;
}

u32 break_cell_partition_migrate_target(const BreakCellPartition *p, u32 current, f32 x, f32 z,
                                        f32 hysteresis) {
    f32 lo_x;
    f32 lo_z;
    f32 hi_x;
    f32 hi_z;
    f64 dx;
    f64 dz;
    if (!p) return 0u;
    if (!break_cell_partition_bounds(p, current, &lo_x, &lo_z, &hi_x, &hi_z) || !isfinite(hysteresis) ||
        hysteresis < 0.0f) {
        return break_cell_partition_locate(p, x, z);
    }
    if (!isfinite(x) || !isfinite(z)) return current;
    dx = cell_partition_gap(x, lo_x, hi_x);
    dz = cell_partition_gap(z, lo_z, hi_z);
    /* with no band, ownership follows locate() exactly (half-open cells) */
    if (hysteresis == 0.0f) return break_cell_partition_locate(p, x, z);
    if (dx * dx + dz * dz <= (f64)hysteresis * (f64)hysteresis) return current;
    return break_cell_partition_locate(p, x, z);
}
