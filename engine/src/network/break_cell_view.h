#ifndef BREAK_CELL_VIEW_H
#define BREAK_CELL_VIEW_H

#include "../core/types.h"

#ifdef __cplusplus
extern "C" {
#endif

/* What one client sees of a world split into cells, and where its input
 * goes (design: docs/design/cell_handoff.md "可见性与连接随交接迁移").
 *
 * BreakCellView merges per-cell visibility for one client connection. Every
 * cell near the client reports the full set of its entities the client can
 * see (its AoI result); the client is sent enter and leave events for the
 * union of the latest reports, so an entity handed from one cell to another
 * stays visible without a leave/enter pair. Because the source gives up an
 * entity before the target takes it, there is a moment when no cell reports
 * it; an entity therefore leaves only after no cell has reported it for
 * more than grace_ticks ticks.
 *
 * BreakCellRoute tells the connection gateway which cell is authoritative
 * for each entity, so input for the client's own entity follows it across
 * handoffs. Cells announce (entity, cell, epoch) for the entities they own;
 * since every commit raises the epoch, the announcement with the highest
 * epoch names the current owner, and late or reordered announcements with
 * a lower epoch are ignored.
 *
 * Plain single-threaded objects; no locking. */

#define BREAK_CELL_VIEW_MAX_CELLS 32u

typedef struct BreakCellView BreakCellView;

/* NULL for zero capacity or OOM. capacity bounds the entities tracked at
 * once (visible ones plus ones still within the grace period). */
BreakCellView *break_cell_view_create(u32 capacity, u32 grace_ticks);
void break_cell_view_destroy(BreakCellView *view);

/* Replaces what `cell` reports as visible. An empty report (count 0) means
 * the cell sees nothing, as after the cell went away. False, with no
 * change, for NULL arguments, a duplicate id in the report, a 33rd distinct
 * cell, or when the new entities would exceed the capacity. */
bool break_cell_view_report(BreakCellView *view, u32 cell, const u64 *ids, u32 count);

/* Advances one tick and writes the entities that became visible and the
 * ones that stopped being visible, each in ascending id order. Both arrays
 * need room for the view's capacity. False for NULL arguments. */
bool break_cell_view_tick(BreakCellView *view, u64 *out_enter, u32 *out_enter_count,
                          u64 *out_leave, u32 *out_leave_count);

bool break_cell_view_is_visible(const BreakCellView *view, u64 entity);
u32 break_cell_view_visible_count(const BreakCellView *view);

typedef struct BreakCellRoute BreakCellRoute;

typedef enum {
    BREAK_CELL_ROUTE_UPDATED = 0, /* new entity or higher epoch */
    BREAK_CELL_ROUTE_SAME,        /* the current owner at the current epoch */
    BREAK_CELL_ROUTE_STALE,       /* lower epoch: ignored */
    BREAK_CELL_ROUTE_CONFLICT,    /* same epoch, another cell: ignored */
    BREAK_CELL_ROUTE_FULL,        /* new entity and no room */
    BREAK_CELL_ROUTE_INVALID      /* NULL route or epoch 0 */
} BreakCellRouteResult;

BreakCellRoute *break_cell_route_create(u32 capacity);
void break_cell_route_destroy(BreakCellRoute *route);
BreakCellRouteResult break_cell_route_observe(BreakCellRoute *route, u64 entity, u32 cell,
                                              u64 epoch);
/* False when the entity is unknown. Either output may be NULL. */
bool break_cell_route_lookup(const BreakCellRoute *route, u64 entity, u32 *out_cell,
                             u64 *out_epoch);
/* Forgets an entity (despawned). False when it was unknown. */
bool break_cell_route_forget(BreakCellRoute *route, u64 entity);

#ifdef __cplusplus
}
#endif

#endif
