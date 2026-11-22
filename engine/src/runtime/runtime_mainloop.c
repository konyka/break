#include <runtime/runtime_mainloop.h>

#include <runtime/runtime_bus.h>

#include <math.h>
#include <stdlib.h>
#include <string.h>

struct BreakRuntimeMainLoop {
    BreakRuntimeBus *bus;
    bool seen;
    bool close_requested;
    u32 width;
    u32 height;
    u32 wsi_state;
    u32 scale_milli;
    BreakRuntimeMainLoopStats stats;
};

static const BreakRuntimeBusKind k_mainloop_kind = {
    BREAK_RUNTIME_MAINLOOP_NOTICE_KIND, BREAK_RUNTIME_MAINLOOP_NOTICE_VERSION,
    BREAK_RUNTIME_MAINLOOP_NOTICE_SIZE, "runtime.mainloop.notice", true, 0u};

static void ml_put(u8 *p, u64 v, u32 bytes) {
    for (u32 i = 0u; i < bytes; ++i) p[i] = (u8)(v >> (8u * i));
}

static u64 ml_get(const u8 *p, u32 bytes) {
    u64 v = 0u;
    for (u32 i = 0u; i < bytes; ++i) v |= (u64)p[i] << (8u * i);
    return v;
}

BreakRuntimeError break_runtime_mainloop_register_kind(BreakRuntimeBus *bus) {
    BreakRuntimeError r;
    if (!bus) return BREAK_RUNTIME_INVALID;
    r = break_runtime_bus_register_kind(bus, &k_mainloop_kind);
    if (r == BREAK_RUNTIME_INVALID) {
        return break_runtime_bus_kind_matches(bus, &k_mainloop_kind) == BREAK_RUNTIME_OK
                   ? BREAK_RUNTIME_OK
                   : BREAK_RUNTIME_REJECTED;
    }
    return r;
}

BreakRuntimeError break_runtime_mainloop_create(BreakRuntimeBus *bus,
                                                BreakRuntimeMainLoop **out_mainloop) {
    BreakRuntimeMainLoop *ml;
    BreakRuntimeError r;
    if (!bus || !out_mainloop) return BREAK_RUNTIME_INVALID;
    *out_mainloop = NULL;
    r = break_runtime_mainloop_register_kind(bus);
    if (r != BREAK_RUNTIME_OK) return r;
    ml = (BreakRuntimeMainLoop *)calloc(1u, sizeof(*ml));
    if (!ml) return BREAK_RUNTIME_OOM;
    ml->bus = bus;
    *out_mainloop = ml;
    return BREAK_RUNTIME_OK;
}

void break_runtime_mainloop_destroy(BreakRuntimeMainLoop *mainloop) {
    free(mainloop);
}

static void ml_publish(BreakRuntimeMainLoop *ml, BreakRuntimeMainLoopNoticeType type, u32 a,
                       u32 b, u64 frame) {
    u8 payload[BREAK_RUNTIME_MAINLOOP_NOTICE_SIZE] = {0};
    BreakRuntimeMessageView view;
    u32 delivered = 0u;
    ml_put(payload, (u64)type, 4u);
    ml_put(payload + 4, a, 4u);
    ml_put(payload + 8, b, 4u);
    ml_put(payload + 16, frame, 8u);
    memset(&view, 0, sizeof(view));
    view.kind = BREAK_RUNTIME_MAINLOOP_NOTICE_KIND;
    view.version = BREAK_RUNTIME_MAINLOOP_NOTICE_VERSION;
    view.sequence = frame;
    view.data = payload;
    view.size = sizeof(payload);
    (void)break_runtime_bus_publish(ml->bus, &view, &delivered);
    if (delivered > 0u) {
        ml->stats.published++;
    } else {
        ml->stats.dropped++;
    }
}

BreakRuntimeError break_runtime_mainloop_observe(BreakRuntimeMainLoop *ml,
                                                 const BreakRuntimeMainLoopFacts *f) {
    u32 scale_milli;
    if (!ml || !f || !isfinite(f->content_scale) || f->content_scale < 0.0f ||
        f->content_scale > 1000.0f) {
        return BREAK_RUNTIME_INVALID;
    }
    scale_milli = (u32)lroundf(f->content_scale * 1000.0f);
    ml->stats.observed++;
    if (f->close_requested && !ml->close_requested) {
        ml_publish(ml, BREAK_RUNTIME_MAINLOOP_CLOSE_REQUESTED, 0u, 0u, f->frame);
    }
    ml->close_requested = f->close_requested;
    if (!ml->seen || f->drawable_width != ml->width || f->drawable_height != ml->height) {
        ml_publish(ml, BREAK_RUNTIME_MAINLOOP_RESIZED, f->drawable_width, f->drawable_height,
                   f->frame);
        ml->width = f->drawable_width;
        ml->height = f->drawable_height;
    }
    if (!ml->seen || f->wsi_state != ml->wsi_state) {
        ml_publish(ml, BREAK_RUNTIME_MAINLOOP_WSI_CHANGED, f->wsi_state,
                   ml->seen ? ml->wsi_state : 0u, f->frame);
        ml->wsi_state = f->wsi_state;
    }
    if (!ml->seen || scale_milli != ml->scale_milli) {
        ml_publish(ml, BREAK_RUNTIME_MAINLOOP_SCALE_CHANGED, scale_milli, 0u, f->frame);
        ml->scale_milli = scale_milli;
    }
    ml->seen = true;
    return BREAK_RUNTIME_OK;
}

BreakRuntimeError break_runtime_mainloop_stats(const BreakRuntimeMainLoop *ml,
                                               BreakRuntimeMainLoopStats *out) {
    if (!ml || !out) return BREAK_RUNTIME_INVALID;
    *out = ml->stats;
    return BREAK_RUNTIME_OK;
}

BreakRuntimeError break_runtime_mainloop_notice_view(const BreakRuntimeOwnedMessage *message,
                                                     BreakRuntimeMainLoopNotice *out) {
    BreakRuntimeMessageView view;
    const u8 *p;
    u32 type;
    if (!message || !out || break_runtime_message_view(message, &view) != BREAK_RUNTIME_OK ||
        view.kind != BREAK_RUNTIME_MAINLOOP_NOTICE_KIND ||
        view.version != BREAK_RUNTIME_MAINLOOP_NOTICE_VERSION ||
        view.size != BREAK_RUNTIME_MAINLOOP_NOTICE_SIZE || !view.data) {
        return BREAK_RUNTIME_INVALID;
    }
    p = (const u8 *)view.data;
    type = (u32)ml_get(p, 4u);
    if (type < (u32)BREAK_RUNTIME_MAINLOOP_CLOSE_REQUESTED ||
        type > (u32)BREAK_RUNTIME_MAINLOOP_SCALE_CHANGED) {
        return BREAK_RUNTIME_INVALID;
    }
    out->type = type;
    out->a = (u32)ml_get(p + 4, 4u);
    out->b = (u32)ml_get(p + 8, 4u);
    out->frame = ml_get(p + 16, 8u);
    return BREAK_RUNTIME_OK;
}
