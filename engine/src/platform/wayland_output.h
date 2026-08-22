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

typedef enum {
    WAYLAND_OPTIONAL_NONE = 0,
    WAYLAND_OPTIONAL_DATA_DEVICE_MANAGER,
    WAYLAND_OPTIONAL_TEXT_INPUT_MANAGER,
    WAYLAND_OPTIONAL_XDG_OUTPUT_MANAGER,
    WAYLAND_OPTIONAL_RELATIVE_POINTER_MANAGER,
    WAYLAND_OPTIONAL_POINTER_CONSTRAINTS,
    WAYLAND_OPTIONAL_CURSOR_SHAPE_MANAGER,
    WAYLAND_OPTIONAL_FRACTIONAL_SCALE_MANAGER,
    WAYLAND_OPTIONAL_VIEWPORTER,
    WAYLAND_OPTIONAL_COUNT,
} WaylandOptionalGlobal;

typedef struct {
    u32 names[WAYLAND_OPTIONAL_COUNT];
} WaylandOptionalGlobals;

/* Wayland fractional-scale uses a numerator with denominator 120. When a
 * viewporter is available, buffers stay unscaled at the wl_surface level and
 * wp_viewport maps the physical backing store back to logical coordinates. */
typedef struct {
    u32 content_scale_120;
    i32 buffer_scale;
    bool uses_viewport;
} WaylandSurfaceScale;

static inline void wl_out_list_init(WaylandOutputList *l) {
    memset(l, 0, sizeof(*l));
}

static inline void wl_out_optional_globals_init(WaylandOptionalGlobals *globals) {
    memset(globals, 0, sizeof(*globals));
}

static inline void wl_out_optional_global_set(WaylandOptionalGlobals *globals,
                                              WaylandOptionalGlobal global,
                                              u32 name) {
    if (globals == NULL || global <= WAYLAND_OPTIONAL_NONE ||
        global >= WAYLAND_OPTIONAL_COUNT) return;
    globals->names[global] = name;
}

/* Clears and returns the one optional global associated with a withdrawn
 * registry name. A compositor can re-advertise a feature with a new name. */
static inline WaylandOptionalGlobal wl_out_optional_global_take(
    WaylandOptionalGlobals *globals, u32 name) {
    if (globals == NULL || name == 0) return WAYLAND_OPTIONAL_NONE;
    for (u32 i = WAYLAND_OPTIONAL_DATA_DEVICE_MANAGER;
         i < WAYLAND_OPTIONAL_COUNT; i++) {
        if (globals->names[i] == name) {
            globals->names[i] = 0;
            return (WaylandOptionalGlobal)i;
        }
    }
    return WAYLAND_OPTIONAL_NONE;
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

/* A Wayland surface may span several outputs. Its buffer scale must use the
 * highest entered output scale so the compositor never upscales an
 * undersized buffer. Unknown outputs are ignored because they may have been
 * removed before the corresponding leave event is dispatched. */
static inline i32 wl_out_surface_scale(const WaylandOutputList *l,
                                       const u32 *entered_globals,
                                       u32 entered_count) {
    i32 scale = 1;
    if (l == NULL || entered_globals == NULL) return scale;
    for (u32 i = 0; i < entered_count; i++) {
        i32 slot = wl_out_find(l, entered_globals[i]);
        if (slot >= 0 && l->items[slot].scale > scale)
            scale = l->items[slot].scale;
    }
    return scale;
}

static inline WaylandSurfaceScale wl_out_surface_render_scale(
    i32 integer_scale, u32 fractional_scale_120, bool fractional_available) {
    WaylandSurfaceScale result;
    u32 fallback_scale = integer_scale > 0 ? (u32)integer_scale : 1u;
    result.uses_viewport = fractional_available;
    result.content_scale_120 = fractional_available && fractional_scale_120 > 0
                                   ? fractional_scale_120
                                   : fallback_scale > UINT32_MAX / 120u
                                         ? UINT32_MAX
                                         : fallback_scale * 120u;
    result.buffer_scale = fractional_available ? 1 : (i32)fallback_scale;
    return result;
}

/* Toplevel buffer sizes round halfway away from zero, per fractional-scale-v1. */
static inline u32 wl_out_drawable_dimension(u32 logical,
                                            u32 content_scale_120) {
    u64 scale = content_scale_120 > 0 ? content_scale_120 : 120u;
    u64 pixels = (u64)logical * scale;
    pixels = (pixels + 60u) / 120u;
    return pixels > UINT32_MAX ? UINT32_MAX : (u32)pixels;
}

/* Client-side cursor buffers cannot use viewporter, so choose an integer
 * backing scale that never leaves the compositor to enlarge the bitmap. */
static inline i32 wl_out_cursor_buffer_scale(u32 content_scale_120) {
    u32 scale = content_scale_120 > 0 ? content_scale_120 : 120u;
    return (i32)(scale / 120u + (scale % 120u != 0));
}
