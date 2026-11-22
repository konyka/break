#ifndef BREAK_CELL_BALANCE_H
#define BREAK_CELL_BALANCE_H

#include "../core/types.h"
#include "break_cell_partition.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Load-based assignment of cells to servers (design:
 * docs/design/cell_handoff.md "按负载分配"). Cells are ordered along a
 * Hilbert curve, so a contiguous run of that order is a spatially compact
 * region, and the order is cut into one contiguous run per server so that
 * the largest per-server load is as small as any such cut allows (binary
 * search over the limit with a greedy packing check). Moving a cell to
 * another server is then a BreakCell handoff of every entity in it, which
 * this planner does not perform. Plain functions; no global state. */

#define BREAK_CELL_BALANCE_MAX_SERVERS 64u
#define BREAK_CELL_BALANCE_MAX_CELLS 4096u

/* Writes every cell id in Hilbert order (on the smallest power-of-two
 * square holding the grid). On a power-of-two square grid consecutive ids
 * are edge neighbours. Returns the cell count, or 0 for a NULL argument or
 * when capacity is smaller than the cell count. */
u32 break_cell_hilbert_order(const BreakCellPartition *p, u32 *out_order, u32 capacity);

/* load[cell] is the cost of each cell (entity count, CPU time, ...).
 * out_assign[cell] receives a server index below `servers`; servers that
 * are not needed get no cells. *out_max_load (optional) receives the
 * largest per-server load. False for NULL arguments, zero servers, more than
 * BREAK_CELL_BALANCE_MAX_SERVERS servers or BREAK_CELL_BALANCE_MAX_CELLS
 * cells, or an allocation failure. */
bool break_cell_balance(const BreakCellPartition *p, const u32 *load, u32 servers, u32 *out_assign,
                        u64 *out_max_load);

/* True when the busiest server under `assign` carries more than `ratio`
 * times the best achievable maximum, or when `assign` names a server at or
 * above `servers`. False for an idle world, invalid arguments (including a
 * ratio below 1 or not finite), or when the best maximum cannot be
 * computed. */
bool break_cell_balance_needed(const BreakCellPartition *p, const u32 *load, const u32 *assign,
                               u32 servers, f32 ratio);

#ifdef __cplusplus
}
#endif

#endif
