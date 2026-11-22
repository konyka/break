#include "break_cell_balance.h"

#include <math.h>
#include <stdlib.h>

/* Hilbert index of (x, y) on an n x n square, n a power of two. */
static u64 cell_balance_hilbert_d(u32 n, u32 x, u32 y) {
    u64 d = 0u;
    for (u32 s = n / 2u; s > 0u; s /= 2u) {
        u32 rx = (x & s) ? 1u : 0u;
        u32 ry = (y & s) ? 1u : 0u;
        d += (u64)s * (u64)s * (u64)((3u * rx) ^ ry);
        if (ry == 0u) {
            if (rx == 1u) {
                x = s - 1u - (x & (s - 1u));
                y = s - 1u - (y & (s - 1u));
            }
            u32 t = x;
            x = y;
            y = t;
        }
        x &= s - 1u;
        y &= s - 1u;
    }
    return d;
}

typedef struct {
    u64 key;
    u32 cell;
} CellBalanceKey;

static int cell_balance_cmp(const void *a, const void *b) {
    const CellBalanceKey *ka = (const CellBalanceKey *)a;
    const CellBalanceKey *kb = (const CellBalanceKey *)b;
    if (ka->key != kb->key) return ka->key < kb->key ? -1 : 1;
    return ka->cell < kb->cell ? -1 : (ka->cell > kb->cell ? 1 : 0);
}

u32 break_cell_hilbert_order(const BreakCellPartition *p, u32 *out_order, u32 capacity) {
    u32 n;
    u32 side = 1u;
    CellBalanceKey *keys;
    if (!p || !out_order || p->columns == 0u || p->rows == 0u) return 0u;
    n = break_cell_partition_cell_count(p);
    if (capacity < n) return 0u;
    while (side < p->columns || side < p->rows) {
        if (side > 0x80000000u) return 0u;
        side *= 2u;
    }
    keys = (CellBalanceKey *)malloc((usize)n * sizeof(CellBalanceKey));
    if (!keys) return 0u;
    for (u32 c = 0; c < n; c++) {
        keys[c].key = cell_balance_hilbert_d(side, c % p->columns, c / p->columns);
        keys[c].cell = c;
    }
    qsort(keys, n, sizeof(CellBalanceKey), cell_balance_cmp);
    for (u32 i = 0; i < n; i++) out_order[i] = keys[i].cell;
    free(keys);
    return n;
}

/* Runs needed to pack `ordered` greedily under `limit`; UINT32_MAX if one
 * cell alone exceeds it. */
static u32 cell_balance_runs(const u64 *ordered, u32 n, u64 limit) {
    u32 runs = 1u;
    u64 cur = 0u;
    for (u32 i = 0; i < n; i++) {
        if (ordered[i] > limit) return UINT32_MAX;
        if (cur + ordered[i] > limit) {
            runs++;
            cur = 0u;
        }
        cur += ordered[i];
    }
    return runs;
}

/* The smallest limit that packs into at most `servers` runs. */
static u64 cell_balance_best(const u64 *ordered, u32 n, u32 servers) {
    u64 lo = 0u;
    u64 hi = 0u;
    for (u32 i = 0; i < n; i++) {
        hi += ordered[i];
        if (ordered[i] > lo) lo = ordered[i];
    }
    while (lo < hi) {
        u64 mid = lo + (hi - lo) / 2u;
        if (cell_balance_runs(ordered, n, mid) <= servers) hi = mid;
        else lo = mid + 1u;
    }
    return lo;
}

static bool cell_balance_args(const BreakCellPartition *p, const u32 *load, u32 servers, u32 *n) {
    if (!p || !load || servers == 0u || servers > BREAK_CELL_BALANCE_MAX_SERVERS) return false;
    *n = break_cell_partition_cell_count(p);
    return *n > 0u && *n <= BREAK_CELL_BALANCE_MAX_CELLS;
}

/* Fills order[] and ordered[] (loads in Hilbert order). */
static bool cell_balance_prepare(const BreakCellPartition *p, const u32 *load, u32 n, u32 *order,
                                 u64 *ordered) {
    if (break_cell_hilbert_order(p, order, n) != n) return false;
    for (u32 i = 0; i < n; i++) ordered[i] = load[order[i]];
    return true;
}

bool break_cell_balance(const BreakCellPartition *p, const u32 *load, u32 servers, u32 *out_assign,
                        u64 *out_max_load) {
    u32 n = 0u;
    u64 *ordered;
    u32 *ord;
    bool ok;
    if (!out_assign || !cell_balance_args(p, load, servers, &n)) return false;
    ordered = (u64 *)malloc((usize)n * sizeof(u64));
    ord = (u32 *)malloc((usize)n * sizeof(u32));
    ok = ordered && ord && cell_balance_prepare(p, load, n, ord, ordered);
    if (ok) {
        u64 limit = cell_balance_best(ordered, n, servers);
        u64 cur = 0u;
        u64 worst = 0u;
        u32 server = 0u;
        for (u32 i = 0; i < n; i++) {
            if (cur + ordered[i] > limit && server + 1u < servers) {
                server++;
                cur = 0u;
            }
            cur += ordered[i];
            if (cur > worst) worst = cur;
            out_assign[ord[i]] = server;
        }
        if (out_max_load) *out_max_load = worst;
    }
    free(ordered);
    free(ord);
    return ok;
}

bool break_cell_balance_needed(const BreakCellPartition *p, const u32 *load, const u32 *assign,
                               u32 servers, f32 ratio) {
    u32 n = 0u;
    u64 per[BREAK_CELL_BALANCE_MAX_SERVERS];
    u64 current = 0u;
    u64 best;
    u64 *ordered;
    u32 *ord;
    bool ok;
    if (!assign || !isfinite(ratio) || ratio < 1.0f || !cell_balance_args(p, load, servers, &n)) {
        return false;
    }
    for (u32 s = 0; s < servers; s++) per[s] = 0u;
    for (u32 c = 0; c < n; c++) {
        if (assign[c] >= servers) return true;
        per[assign[c]] += load[c];
    }
    for (u32 s = 0; s < servers; s++) current = per[s] > current ? per[s] : current;
    if (current == 0u) return false;
    ordered = (u64 *)malloc((usize)n * sizeof(u64));
    ord = (u32 *)malloc((usize)n * sizeof(u32));
    ok = ordered && ord && cell_balance_prepare(p, load, n, ord, ordered);
    best = ok ? cell_balance_best(ordered, n, servers) : 0u;
    free(ordered);
    free(ord);
    if (!ok) return false;
    return (f64)current > (f64)ratio * (f64)best;
}
