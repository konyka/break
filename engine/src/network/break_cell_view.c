#include "network/break_cell_view.h"

#include <stdlib.h>
#include <string.h>

typedef struct {
    u64 entity;
    u32 unseen; /* ticks since any cell last reported it */
    bool visible;
} ViewEntry;

typedef struct {
    u32 cell;
    u64 *ids;
    u32 count;
} ViewReport;

struct BreakCellView {
    u32 capacity;
    u32 grace_ticks;
    ViewEntry *entries;
    u32 entry_count;
    ViewReport reports[BREAK_CELL_VIEW_MAX_CELLS];
    u32 report_count;
};

BreakCellView *break_cell_view_create(u32 capacity, u32 grace_ticks) {
    BreakCellView *view;
    if (capacity == 0u) return NULL;
    view = (BreakCellView *)calloc(1u, sizeof *view);
    if (view == NULL) return NULL;
    view->entries = (ViewEntry *)calloc(capacity, sizeof *view->entries);
    if (view->entries == NULL) {
        free(view);
        return NULL;
    }
    view->capacity = capacity;
    view->grace_ticks = grace_ticks;
    return view;
}

void break_cell_view_destroy(BreakCellView *view) {
    if (view == NULL) return;
    for (u32 i = 0; i < view->report_count; i++) free(view->reports[i].ids);
    free(view->entries);
    free(view);
}

static ViewEntry *view_find(const BreakCellView *view, u64 entity) {
    for (u32 i = 0; i < view->entry_count; i++)
        if (view->entries[i].entity == entity) return &view->entries[i];
    return NULL;
}

static bool reported_elsewhere(const BreakCellView *view, u32 skip, u64 entity) {
    for (u32 r = 0; r < view->report_count; r++) {
        if (r == skip) continue;
        for (u32 i = 0; i < view->reports[r].count; i++)
            if (view->reports[r].ids[i] == entity) return true;
    }
    return false;
}

bool break_cell_view_report(BreakCellView *view, u32 cell, const u64 *ids, u32 count) {
    u32 slot, added = 0u;
    u64 *copy = NULL;
    if (view == NULL || (ids == NULL && count > 0u)) return false;
    for (u32 i = 0; i < count; i++)
        for (u32 j = 0; j < i; j++)
            if (ids[i] == ids[j]) return false;
    for (slot = 0; slot < view->report_count; slot++)
        if (view->reports[slot].cell == cell) break;
    if (count == 0u) {
        /* An empty report contributes nothing, so the slot is released and a
         * client that crosses many cells never runs out of slots. */
        if (slot < view->report_count) {
            free(view->reports[slot].ids);
            view->reports[slot] = view->reports[--view->report_count];
            memset(&view->reports[view->report_count], 0, sizeof view->reports[0]);
        }
        return true;
    }
    if (slot == view->report_count && slot == BREAK_CELL_VIEW_MAX_CELLS) return false;
    for (u32 i = 0; i < count; i++)
        if (view_find(view, ids[i]) == NULL) added++;
    if (added > view->capacity - view->entry_count) return false;
    if (count > 0u) {
        copy = (u64 *)malloc((usize)count * sizeof *copy);
        if (copy == NULL) return false;
        memcpy(copy, ids, (usize)count * sizeof *copy);
    }
    for (u32 i = 0; i < count; i++) {
        if (view_find(view, ids[i]) != NULL) continue;
        view->entries[view->entry_count].entity = ids[i];
        view->entries[view->entry_count].unseen = 0u;
        view->entries[view->entry_count].visible = false;
        view->entry_count++;
    }
    if (slot == view->report_count) {
        view->reports[slot].cell = cell;
        view->report_count++;
    } else {
        free(view->reports[slot].ids);
    }
    view->reports[slot].ids = copy;
    view->reports[slot].count = count;
    return true;
}

static int compare_u64(const void *a, const void *b) {
    u64 x = *(const u64 *)a, y = *(const u64 *)b;
    return x < y ? -1 : x > y;
}

bool break_cell_view_tick(BreakCellView *view, u64 *out_enter, u32 *out_enter_count,
                          u64 *out_leave, u32 *out_leave_count) {
    u32 enter = 0u, leave = 0u, kept = 0u;
    if (view == NULL || out_enter == NULL || out_enter_count == NULL || out_leave == NULL ||
        out_leave_count == NULL)
        return false;
    for (u32 i = 0; i < view->entry_count; i++) {
        ViewEntry e = view->entries[i];
        if (reported_elsewhere(view, BREAK_CELL_VIEW_MAX_CELLS, e.entity)) {
            e.unseen = 0u;
            if (!e.visible) {
                e.visible = true;
                out_enter[enter++] = e.entity;
            }
        } else if (++e.unseen > view->grace_ticks) {
            if (e.visible) out_leave[leave++] = e.entity;
            continue; /* dropped */
        }
        view->entries[kept++] = e;
    }
    view->entry_count = kept;
    qsort(out_enter, enter, sizeof *out_enter, compare_u64);
    qsort(out_leave, leave, sizeof *out_leave, compare_u64);
    *out_enter_count = enter;
    *out_leave_count = leave;
    return true;
}

bool break_cell_view_is_visible(const BreakCellView *view, u64 entity) {
    const ViewEntry *e = view != NULL ? view_find(view, entity) : NULL;
    return e != NULL && e->visible;
}

u32 break_cell_view_visible_count(const BreakCellView *view) {
    u32 n = 0u;
    if (view == NULL) return 0u;
    for (u32 i = 0; i < view->entry_count; i++)
        if (view->entries[i].visible) n++;
    return n;
}

typedef struct {
    u64 entity;
    u64 epoch;
    u32 cell;
} RouteEntry;

struct BreakCellRoute {
    RouteEntry *entries;
    u32 count;
    u32 capacity;
};

BreakCellRoute *break_cell_route_create(u32 capacity) {
    BreakCellRoute *route;
    if (capacity == 0u) return NULL;
    route = (BreakCellRoute *)calloc(1u, sizeof *route);
    if (route == NULL) return NULL;
    route->entries = (RouteEntry *)calloc(capacity, sizeof *route->entries);
    if (route->entries == NULL) {
        free(route);
        return NULL;
    }
    route->capacity = capacity;
    return route;
}

void break_cell_route_destroy(BreakCellRoute *route) {
    if (route == NULL) return;
    free(route->entries);
    free(route);
}

static RouteEntry *route_find(const BreakCellRoute *route, u64 entity) {
    for (u32 i = 0; i < route->count; i++)
        if (route->entries[i].entity == entity) return &route->entries[i];
    return NULL;
}

BreakCellRouteResult break_cell_route_observe(BreakCellRoute *route, u64 entity, u32 cell,
                                              u64 epoch) {
    RouteEntry *e;
    if (route == NULL || epoch == 0u) return BREAK_CELL_ROUTE_INVALID;
    e = route_find(route, entity);
    if (e == NULL) {
        if (route->count == route->capacity) return BREAK_CELL_ROUTE_FULL;
        e = &route->entries[route->count++];
        e->entity = entity;
        e->epoch = epoch;
        e->cell = cell;
        return BREAK_CELL_ROUTE_UPDATED;
    }
    if (epoch < e->epoch) return BREAK_CELL_ROUTE_STALE;
    if (epoch == e->epoch)
        return e->cell == cell ? BREAK_CELL_ROUTE_SAME : BREAK_CELL_ROUTE_CONFLICT;
    e->epoch = epoch;
    e->cell = cell;
    return BREAK_CELL_ROUTE_UPDATED;
}

bool break_cell_route_lookup(const BreakCellRoute *route, u64 entity, u32 *out_cell,
                             u64 *out_epoch) {
    const RouteEntry *e = route != NULL ? route_find(route, entity) : NULL;
    if (e == NULL) return false;
    if (out_cell != NULL) *out_cell = e->cell;
    if (out_epoch != NULL) *out_epoch = e->epoch;
    return true;
}

bool break_cell_route_forget(BreakCellRoute *route, u64 entity) {
    RouteEntry *e = route != NULL ? route_find(route, entity) : NULL;
    if (e == NULL) return false;
    *e = route->entries[--route->count];
    return true;
}
