#pragma once
/* R443: pure, wayland-free logic backing wl_output enumeration in
 * window_wayland.c. Kept in a header (static inline) with no Wayland includes
 * so the slot/mode-selection rules are unit-testable headless — the dev/CI
 * machine may run an X11 session where no compositor is available
 * (see tests/test_wayland.c). */

#include <core/types.h>
#include <string.h>

#include <platform/platform.h> /* PLATFORM_MAX_MONITORS */

#define WAYLAND_OUTPUT_MAX PLATFORM_MAX_MONITORS

typedef struct {
    u32  global_name;       /* wl_registry global name; 0 = slot empty */
    char name[64];          /* model, or xdg-output name/description when given */
    i32  x, y;              /* compositor-space position */
    u32  width, height;     /* selected mode, pixels */
    u32  refresh_rate;      /* selected mode, Hz */
    i32  scale;             /* wl_output.scale factor (1, 2, 3...) */
    bool has_current_mode;  /* a mode flagged WL_OUTPUT_MODE_CURRENT arrived */
    bool done;              /* wl_output.done received (info is complete) */
} WaylandOutputInfo;

typedef struct {
    WaylandOutputInfo items[WAYLAND_OUTPUT_MAX];
    u32               count;
} WaylandOutputList;

static inline void wl_out_list_init(WaylandOutputList *l) {
    memset(l, 0, sizeof(*l));
}

/* Slot index for a registry global name, or -1 if not present. */
static inline i32 wl_out_find(const WaylandOutputList *l, u32 global_name) {
    for (u32 i = 0; i < l->count; i++) {
        if (l->items[i].global_name == global_name) return (i32)i;
    }
    return -1;
}

/* Add a slot for a newly advertised wl_output global. Dedups on global_name
 * (the registry may re-announce a name we already bound — e.g. compositor
 * restart of global advertisement); returns the slot index, or -1 when full. */
static inline i32 wl_out_add(WaylandOutputList *l, u32 global_name) {
    i32 existing = wl_out_find(l, global_name);
    if (existing >= 0) return existing;
    if (l->count >= WAYLAND_OUTPUT_MAX) return -1;
    WaylandOutputInfo *o = &l->items[l->count];
    memset(o, 0, sizeof(*o));
    o->global_name = global_name;
    o->scale = 1;
    return (i32)l->count++;
}

/* Remove the slot for a withdrawn registry global (hot-unplug). Compacts the
 * array (tail shifts down by one) rather than leaving a tombstone, so the
 * fixed slot budget never wears out under repeated plug/unplug cycles and the
 * append-dedup semantics of wl_out_add stay consistent. Returns false when
 * the global is not present. */
static inline bool wl_out_remove(WaylandOutputList *l, u32 global_name) {
    i32 slot = wl_out_find(l, global_name);
    if (slot < 0) return false;
    u32 i = (u32)slot;
    if (i + 1 < l->count)
        memmove(&l->items[i], &l->items[i + 1],
                (l->count - i - 1) * sizeof(l->items[0]));
    l->count--;
    return true;
}

/* Fold one wl_output.mode event into the slot's selected mode.
 * Rule: a mode flagged current always wins and sticks; without a current
 * mode keep the largest area, ties broken by higher refresh.
 * refresh_mhz is the raw wl_output value (mHz); stored rounded to Hz. */
static inline void wl_out_accumulate_mode(WaylandOutputInfo *o, bool current,
                                          i32 w, i32 h, i32 refresh_mhz) {
    if (w <= 0 || h <= 0) return;
    u32 hz = (u32)((refresh_mhz + 500) / 1000);
    if (current) {
        o->width = (u32)w;
        o->height = (u32)h;
        o->refresh_rate = hz;
        o->has_current_mode = true;
        return;
    }
    if (o->has_current_mode) return; /* current mode sticks */
    u64 area = (u64)(u32)w * (u64)(u32)h;
    u64 best = (u64)o->width * (u64)o->height;
    if (area > best || (area == best && hz > o->refresh_rate)) {
        o->width = (u32)w;
        o->height = (u32)h;
        o->refresh_rate = hz;
    }
}
