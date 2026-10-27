/* BreakEditorPanelRender — render debugger panel, a PURE VIEW
 * (docs/design/editor_render_debugger.md). Mirrors editor_panel_network.c:
 * create = CPU state, build = widgets beside the network panel in the shared
 * diagnostics row, destroy = CPU state only, tick = throttled snapshot.
 *
 * SCOPE: the panel never creates, destroys, binds, records, submits or
 * presents anything. It reads the BORROWED device only through the
 * BreakEditorRenderSource table (production: rhi_device_get_info /
 * _get_capabilities / _get_status / rhi_frame_index /
 * rhi_device_resource_usage and the rollout backend/reason) and the
 * viewport's CPU-side last-render/shader-reload stats. Pinned by
 * render_panel_source_is_read_only (source scan of the marked region).
 *
 * Rows (fixed storage, 16 rows x 96 bytes; no RHI/GPU allocation on refresh;
 * the retained UI may allocate bounded row widgets):
 *   device == NULL: exactly one row, "render: no device".
 *   otherwise:
 *     [0] backend: <name> (<reason>) status=<ready|lost|unknown> frame=<n>
 *     [1] gpu: <device name, truncated>
 *     [2] ids: vendor=0x<v> device=0x<d> api=<maj.min.patch> driver=<d>
 *     [3] caps: shader=<glsl|glsl_vk|...> compute=<0|1> indirect=<0|1> push=<bytes>
 *     [4] caps: msaa=0x<color bits> damage=<0|1> buffer_age=<0|1>
 *     [5] resources: <used>/<capacity> slots
 *     [6] viewport: <ready|failed|not-initialised> fbo=<w>x<h>
 *     [7] viewport: proxies=<n> gizmo=<n> draws=<n> skipped=<reason>
 *     [8] shader reload: <watching|manual-only|shutdown-pending>
 *         busy=<0|1> applied=<n> failed=<n>, or "shader reload: unavailable"
 *
 * THROTTLE: at most 4 refreshes per second (250,000 us) from
 * break_editor_shell_tick; the first tick after create and after any device
 * attach/detach always refreshes. Shell thread only. */

#include "editor_shell_internal.h"
#include "editor_viewport3d.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <platform/time.h>
#include <rhi/rhi_rollout.h>

#include "myui/my_layout.h"
#include "myui/widgets/my_label.h"
#include "myui/widgets/my_list_view.h"

#define EDITOR_RENDER_MAX_ROWS 16u
#define EDITOR_RENDER_ROW_BYTES 96u
#define EDITOR_RENDER_REFRESH_US 250000u /* 4 Hz */

typedef struct {
    my_list_adapter_t base;
    BreakEditorPanelRender *panel; /* borrowed */
} EditorRenderAdapter;

struct BreakEditorPanelRender {
    BreakEditorShell *shell;  /* borrowed */
    void *device;             /* borrowed RHIDevice; NULL = no device */
    const BreakEditorRenderSource *source;
    my_widget_t *list;        /* weak (owned by the window tree) */
    EditorRenderAdapter adapter;
    u64 (*clock)(void *user); /* NULL = time_microseconds */
    void *clock_user;
    bool force_refresh;
    u64 last_refresh_us;
    u32 row_count;
    char rows[EDITOR_RENDER_MAX_ROWS][EDITOR_RENDER_ROW_BYTES];
};

/* RENDER_PANEL_READONLY_BEGIN */

/* ---------------- production read-only source ---------------- */

static bool src_info(const void *dev, RHIDeviceInfo *out) {
    return rhi_device_get_info((const RHIDevice *)dev, out);
}
static bool src_caps(const void *dev, RHICapabilities *out) {
    return rhi_device_get_capabilities((const RHIDevice *)dev, out);
}
static RHIDeviceStatus src_status(const void *dev) {
    return rhi_device_get_status((const RHIDevice *)dev);
}
static u32 src_frame(const void *dev) {
    /* rhi_frame_index takes a non-const device but only reads it */
    return rhi_frame_index((RHIDevice *)(uintptr_t)dev);
}
static bool src_usage(const void *dev, u32 *used, u32 *capacity) {
    return rhi_device_resource_usage((const RHIDevice *)dev, used, capacity);
}

static const BreakEditorRenderSource k_rhi_source = {
    src_info, src_caps, src_status, src_frame, src_usage,
    rhi_rollout_compiled_backend, rhi_rollout_compiled_reason};

/* ---------------- snapshot ---------------- */

static const char *status_name(RHIDeviceStatus s) {
    switch (s) {
    case RHI_DEVICE_STATUS_READY: return "ready";
    case RHI_DEVICE_STATUS_LOST: return "lost";
    default: return "unknown";
    }
}

static const char *variant_name(u32 v) {
    switch ((RHIShaderVariant)v) {
    case RHI_SHADER_VARIANT_GLSL: return "glsl";
    case RHI_SHADER_VARIANT_GLSL_VK: return "glsl_vk";
    default: return "other";
    }
}

static const char *init_name(int state) {
    switch (state) {
    case BREAK_EDITOR_VIEWPORT3D_INIT_READY: return "ready";
    case BREAK_EDITOR_VIEWPORT3D_INIT_FAILED: return "failed";
    default: return "not-initialised";
    }
}

static void render_panel_refresh(BreakEditorPanelRender *p,
                                 const BreakEditorViewport3D *vp) {
    const BreakEditorRenderSource *s = p->source != NULL ? p->source : &k_rhi_source;
    RHIDeviceInfo info;
    RHICapabilities caps;
    BreakEditorViewport3DStats st;
    u32 used = 0u, capacity = 0u;
    const char *backend, *reason;
    if (p->device == NULL) {
        (void)snprintf(p->rows[0], EDITOR_RENDER_ROW_BYTES, "render: no device");
        p->row_count = 1u;
    } else {
        memset(&info, 0, sizeof(info));
        memset(&caps, 0, sizeof(caps));
        (void)s->device_info(p->device, &info);
        (void)s->capabilities(p->device, &caps);
        (void)s->resource_usage(p->device, &used, &capacity);
        backend = s->backend_name != NULL ? s->backend_name() : NULL;
        reason = s->selection_reason != NULL ? s->selection_reason() : NULL;
        info.device_name[sizeof(info.device_name) - 1u] = '\0';
        (void)snprintf(p->rows[0], EDITOR_RENDER_ROW_BYTES,
                       "backend: %s (%s) status=%s frame=%u",
                       backend != NULL ? backend : "unknown",
                       reason != NULL ? reason : "unknown",
                       status_name(s->status(p->device)),
                       (unsigned)s->frame_index(p->device));
        (void)snprintf(p->rows[1], EDITOR_RENDER_ROW_BYTES, "gpu: %.88s",
                       info.device_name[0] != '\0' ? info.device_name : "unknown");
        (void)snprintf(p->rows[2], EDITOR_RENDER_ROW_BYTES,
                       "ids: vendor=0x%x device=0x%x api=%u.%u.%u driver=%u",
                       (unsigned)info.vendor_id, (unsigned)info.device_id,
                       (unsigned)((info.api_version >> 22) & 0x7fu),
                       (unsigned)((info.api_version >> 12) & 0x3ffu),
                       (unsigned)(info.api_version & 0xfffu),
                       (unsigned)info.driver_version);
        (void)snprintf(p->rows[3], EDITOR_RENDER_ROW_BYTES,
                       "caps: shader=%s compute=%u indirect=%u push=%u",
                       variant_name(caps.shader_variant),
                       caps.compute_supported ? 1u : 0u,
                       caps.indirect_draw_supported ? 1u : 0u,
                       caps.push_constants_supported
                           ? (unsigned)caps.max_push_constant_size : 0u);
        (void)snprintf(p->rows[4], EDITOR_RENDER_ROW_BYTES,
                       "caps: msaa=0x%x damage=%u buffer_age=%u",
                       (unsigned)caps.color_sample_counts,
                       caps.present_damage_supported ? 1u : 0u,
                       caps.present_buffer_age_supported ? 1u : 0u);
        (void)snprintf(p->rows[5], EDITOR_RENDER_ROW_BYTES,
                       "resources: %u/%u slots", (unsigned)used,
                       (unsigned)capacity);
        if (!break_editor_viewport3d_last_stats(vp, &st)) {
            memset(&st, 0, sizeof(st));
            st.skipped = BREAK_EDITOR_VIEWPORT3D_SKIP_NOT_RENDERED;
        }
        (void)snprintf(p->rows[6], EDITOR_RENDER_ROW_BYTES,
                       "viewport: %s fbo=%ux%u", init_name(st.init_state),
                       (unsigned)st.fbo_w, (unsigned)st.fbo_h);
        (void)snprintf(p->rows[7], EDITOR_RENDER_ROW_BYTES,
                       "viewport: proxies=%u gizmo=%u draws=%u skipped=%s",
                       (unsigned)st.proxies, (unsigned)st.gizmo_handles,
                       (unsigned)st.draws,
                       break_editor_viewport3d_skip_name(st.skipped));
        {
            BreakEditorShaderReloadStats reload;
            if (!break_editor_viewport3d_shader_reload_stats(vp, &reload) ||
                !reload.owner_present) {
                (void)snprintf(p->rows[8], EDITOR_RENDER_ROW_BYTES,
                               "shader reload: unavailable");
            } else {
                const char *state =
                    reload.stopping
                        ? "shutdown-pending"
                        : (reload.watching ? "watching" : "manual-only");
                (void)snprintf(
                    p->rows[8], EDITOR_RENDER_ROW_BYTES,
                    "shader reload: %s busy=%u applied=%llu failed=%llu",
                    state, reload.busy ? 1u : 0u,
                    (unsigned long long)reload.reloads,
                    (unsigned long long)reload.failed);
            }
        }
        p->row_count = 9u;
    }
    if (p->list != NULL) {
        (void)my_list_view_refresh(p->list);
    }
}

void editor_panel_render_tick(BreakEditorPanelRender *p,
                              const BreakEditorViewport3D *vp) {
    u64 now;
    if (p == NULL) {
        return;
    }
    now = p->clock != NULL ? p->clock(p->clock_user) : time_microseconds();
    if (p->force_refresh || now - p->last_refresh_us >= EDITOR_RENDER_REFRESH_US) {
        p->force_refresh = false;
        p->last_refresh_us = now;
        render_panel_refresh(p, vp);
    }
}

/* RENDER_PANEL_READONLY_END */

/* ---------------- list adapter ---------------- */

static size_t render_adapter_count(my_list_adapter_t *adapter) {
    EditorRenderAdapter *a =
        (EditorRenderAdapter *)((char *)adapter - offsetof(EditorRenderAdapter, base));
    return (size_t)a->panel->row_count;
}

static my_widget_t *render_adapter_create_row(my_list_adapter_t *adapter) {
    my_widget_t *row = my_label_create(NULL, "");
    (void)adapter;
    if (row == NULL) {
        return NULL;
    }
    (void)my_widget_set_name(row, "editor-render-row");
    return row;
}

static void render_adapter_bind_row(my_list_adapter_t *adapter,
                                    my_widget_t *row, size_t index) {
    EditorRenderAdapter *a =
        (EditorRenderAdapter *)((char *)adapter - offsetof(EditorRenderAdapter, base));
    (void)my_label_set_text(row, index < a->panel->row_count
                                     ? a->panel->rows[index] : "<stale>");
}

static const my_list_adapter_vtable_t k_render_adapter_vtable = {
    render_adapter_count, render_adapter_create_row, render_adapter_bind_row,
    NULL};

/* ---------------- lifecycle ---------------- */

BreakEditorPanelRender *editor_panel_render_create(BreakEditorShell *shell) {
    BreakEditorPanelRender *p;
    if (shell == NULL) {
        return NULL;
    }
    p = (BreakEditorPanelRender *)calloc(1u, sizeof(*p));
    if (p == NULL) {
        return NULL;
    }
    p->shell = shell;
    p->force_refresh = true;
    return p;
}

void editor_panel_render_destroy(BreakEditorPanelRender *p) {
    free(p); /* widgets belong to the window tree; the device is borrowed */
}

void editor_panel_render_build(BreakEditorPanelRender *p, my_widget_t *parent) {
    my_widget_t *section, *label;
    if (p == NULL || parent == NULL) {
        return;
    }
    section = my_widget_create(NULL, "editor-render-panel");
    if (section == NULL) {
        return;
    }
    (void)my_widget_set_layouter(section, my_layouter_linear_create(NULL, false, 2));
    label = my_label_create(NULL, "Render (4 Hz)");
    if (label == NULL) {
        my_widget_unref(section);
        return;
    }
    (void)my_widget_set_name(label, "editor-render-label");
    (void)my_widget_set_layout_params(label, "w:100% h:22");
    if (my_widget_add_child(section, label) != MY_RET_OK) {
        my_widget_unref(label);
        my_widget_unref(section);
        return;
    }
    my_widget_unref(label); /* tree holds its own reference */
    p->list = my_list_view_create(NULL);
    if (p->list == NULL) {
        my_widget_unref(section);
        return;
    }
    (void)my_widget_set_name(p->list, "editor-render-list");
    p->adapter.base.vtable = &k_render_adapter_vtable;
    p->adapter.panel = p;
    if (my_list_view_set_adapter(p->list, &p->adapter.base) != MY_RET_OK) {
        my_widget_unref(p->list);
        p->list = NULL;
        my_widget_unref(section);
        return;
    }
    (void)my_widget_set_layout_params(p->list, "w:100% h:1f");
    if (my_widget_add_child(section, p->list) != MY_RET_OK) {
        my_widget_unref(p->list);
        p->list = NULL;
        my_widget_unref(section);
        return;
    }
    my_widget_unref(p->list); /* tree holds its own reference */
    /* diagnostics row (the shell's h:20% editor-diag-row): right of the
     * network panel, takes the rest */
    (void)my_widget_set_layout_params(section, "w:1f h:100%");
    if (my_widget_add_child(parent, section) == MY_RET_OK) {
        my_widget_unref(section);
    } else {
        p->list = NULL; /* died with the section */
        my_widget_unref(section);
    }
}

void editor_panel_render_set_device(BreakEditorPanelRender *p, void *device) {
    if (p == NULL) {
        return;
    }
    p->device = device;
    p->force_refresh = true;
}

void editor_panel_render_set_source(BreakEditorPanelRender *p,
                                    const BreakEditorRenderSource *source) {
    if (p == NULL) {
        return;
    }
    p->source = source;
    p->force_refresh = true;
}

void editor_panel_render_set_clock(BreakEditorPanelRender *p,
                                   u64 (*clock)(void *user), void *user) {
    if (p == NULL) {
        return;
    }
    p->clock = clock;
    p->clock_user = user;
}

uint32_t editor_panel_render_row_count(const BreakEditorPanelRender *p) {
    return p != NULL ? p->row_count : 0u;
}

const char *editor_panel_render_row_text(const BreakEditorPanelRender *p,
                                         uint32_t index) {
    if (p == NULL || index >= p->row_count) {
        return NULL;
    }
    return p->rows[index];
}
