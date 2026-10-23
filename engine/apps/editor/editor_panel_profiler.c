/* EditorPanelProfiler — Stage 4 scene editor Phase 3 Task 3: profiler
 * panel, a PURE VIEW over the core profiler (core/profiler.h).
 *
 * SCOPE: the panel NEVER mutates profiler state — no profiler_set_enabled /
 * begin_frame / push / pop calls live here; it only reads
 * profiler_last_frame() (borrowed, NULL when no frame has been recorded)
 * and renders a snapshot. The producer side (profiler_set_enabled(true) +
 * per-frame begin/push/pop/end) is the editor app's main loop
 * (editor_main.c), not the panel.
 *
 * Rendering: the last frame's regions (up to PROFILER_MAX_REGIONS) are
 * sorted by elapsed time descending and the top N (N <= 16) render as
 * "<name> <ms> ms" label rows in a list_view. The snapshot is copied into
 * fixed panel storage, so the rows never alias the profiler ring (region
 * name pointers are borrowed for the duration of the refresh only — the
 * rendered text is fully copied).
 *
 * THROTTLE (documented plan decision): the snapshot refreshes at most
 * 4 times per second (250,000 us between refreshes, measured with the
 * platform monotonic clock time_microseconds()) from
 * break_editor_shell_tick — the per-frame hook the editor main loop already
 * calls. The FIRST tick after create always refreshes (last refresh
 * timestamp 0), so a freshly opened editor shows data immediately.
 *
 * Bounds: 16 rows x 80 bytes of fixed snapshot storage; refresh allocates
 * nothing. Threading: single-owner-thread convention (the editor records
 * and reads the profiler on the shell thread; the profiler's own R434
 * per-thread recording is unaffected — this panel only ever reads the last
 * completed frame). */

#include "editor_shell_internal.h"

#include <stdio.h>
#include <stdlib.h>

#include <core/profiler.h>
#include <platform/time.h>

#include "myui/my_layout.h"
#include "myui/widgets/my_label.h"
#include "myui/widgets/my_list_view.h"

#define EDITOR_PROFILER_MAX_ROWS 16u
#define EDITOR_PROFILER_ROW_BYTES 80u
#define EDITOR_PROFILER_REFRESH_US 250000u /* 4 Hz */

typedef struct {
    my_list_adapter_t base;
    EditorPanelProfiler *panel; /* borrowed */
} EditorProfilerAdapter;

struct EditorPanelProfiler {
    BreakEditorShell *shell; /* borrowed (unused beyond create symmetry) */
    my_widget_t *list;       /* weak (owned by the window tree) */
    EditorProfilerAdapter adapter;
    u64 last_refresh_us;     /* 0 = never refreshed (next tick refreshes) */
    u32 row_count;
    char rows[EDITOR_PROFILER_MAX_ROWS][EDITOR_PROFILER_ROW_BYTES];
};

/* ---------------- snapshot ---------------- */

/* Re-reads profiler_last_frame into the fixed row snapshot. Pure read: the
 * profiler's frame ring, counts, and enabled flag are untouched. */
static void profiler_panel_refresh(EditorPanelProfiler *panel) {
    const ProfilerFrame *frame;
    u32 order[PROFILER_MAX_REGIONS];
    u32 n, i, j, shown;
    if (panel == NULL) {
        return;
    }
    frame = profiler_last_frame();
    if (frame == NULL) {
        panel->row_count = 0u;
    } else {
        n = frame->region_count;
        if (n > PROFILER_MAX_REGIONS) {
            n = PROFILER_MAX_REGIONS; /* defensive; the core caps at 64 */
        }
        for (i = 0u; i < n; i++) {
            order[i] = i;
        }
        /* insertion sort by elapsed desc, ties keep frame order (stable):
         * deterministic for a fixed frame */
        for (i = 1u; i < n; i++) {
            u32 key = order[i];
            u64 key_us = frame->regions[key].elapsed_us;
            j = i;
            while (j > 0u && frame->regions[order[j - 1u]].elapsed_us <
                                key_us) {
                order[j] = order[j - 1u];
                j--;
            }
            order[j] = key;
        }
        shown = n < EDITOR_PROFILER_MAX_ROWS ? n : EDITOR_PROFILER_MAX_ROWS;
        for (i = 0u; i < shown; i++) {
            const ProfilerRegion *r = &frame->regions[order[i]];
            const char *name = r->name != NULL ? r->name : "?";
            (void)snprintf(panel->rows[i], sizeof(panel->rows[i]),
                           "%.56s %.3f ms", name,
                           (double)r->elapsed_us / 1000.0);
        }
        panel->row_count = shown;
    }
    if (panel->list != NULL) {
        (void)my_list_view_refresh(panel->list);
    }
}

/* ---------------- list adapter ---------------- */

static size_t profiler_adapter_count(my_list_adapter_t *adapter) {
    EditorProfilerAdapter *a =
        (EditorProfilerAdapter *)((char *)adapter -
                                  offsetof(EditorProfilerAdapter, base));
    return (size_t)a->panel->row_count;
}

static my_widget_t *profiler_adapter_create_row(my_list_adapter_t *adapter) {
    my_widget_t *row = my_label_create(NULL, "");
    (void)adapter;
    if (row == NULL) {
        return NULL;
    }
    (void)my_widget_set_name(row, "editor-profiler-row");
    return row;
}

static void profiler_adapter_bind_row(my_list_adapter_t *adapter,
                                      my_widget_t *row, size_t index) {
    EditorProfilerAdapter *a =
        (EditorProfilerAdapter *)((char *)adapter -
                                  offsetof(EditorProfilerAdapter, base));
    if (index < a->panel->row_count) {
        (void)my_label_set_text(row, a->panel->rows[index]);
    } else {
        (void)my_label_set_text(row, "<stale>");
    }
}

static const my_list_adapter_vtable_t k_profiler_adapter_vtable = {
    profiler_adapter_count, profiler_adapter_create_row,
    profiler_adapter_bind_row, NULL};

/* ---------------- lifecycle ---------------- */

EditorPanelProfiler *editor_panel_profiler_create(BreakEditorShell *shell) {
    EditorPanelProfiler *panel;
    if (shell == NULL) {
        return NULL;
    }
    panel = (EditorPanelProfiler *)calloc(1u, sizeof(EditorPanelProfiler));
    if (panel == NULL) {
        return NULL;
    }
    panel->shell = shell;
    return panel;
}

void editor_panel_profiler_destroy(EditorPanelProfiler *panel) {
    /* no CPU-side sub-objects; the widgets belong to the window tree */
    free(panel);
}

bool editor_panel_profiler_build(EditorPanelProfiler *panel,
                                 my_widget_t *parent) {
    my_widget_t *section;
    my_widget_t *label;
    if (panel == NULL || parent == NULL) {
        return false;
    }
    section = my_widget_create(NULL, "editor-profiler-panel");
    if (section == NULL) {
        return false;
    }
    (void)my_widget_set_layouter(section,
                                 my_layouter_linear_create(NULL, false, 2));
    label = my_label_create(NULL, "Profiler (top 16, 4 Hz)");
    if (label == NULL) {
        my_widget_unref(section);
        return false;
    }
    (void)my_widget_set_name(label, "editor-profiler-label");
    (void)my_widget_set_layout_params(label, "w:100% h:22");
    if (my_widget_add_child(section, label) == MY_RET_OK) {
        my_widget_unref(label); /* tree holds its own reference */
    } else {
        my_widget_unref(label);
        my_widget_unref(section);
        return false;
    }
    panel->list = my_list_view_create(NULL);
    if (panel->list == NULL) {
        my_widget_unref(section);
        return false;
    }
    (void)my_widget_set_name(panel->list, "editor-profiler-list");
    panel->adapter.base.vtable = &k_profiler_adapter_vtable;
    panel->adapter.panel = panel;
    if (my_list_view_set_adapter(panel->list, &panel->adapter.base) !=
        MY_RET_OK) {
        my_widget_unref(panel->list);
        my_widget_unref(section);
        return false;
    }
    (void)my_widget_set_layout_params(panel->list, "w:100% h:1f");
    if (my_widget_add_child(section, panel->list) == MY_RET_OK) {
        my_widget_unref(panel->list); /* tree holds its own reference */
    } else {
        my_widget_unref(panel->list);
        my_widget_unref(section);
        return false;
    }
    /* under the inspector: 30% of the right column height */
    (void)my_widget_set_layout_params(section, "w:100% h:30%");
    if (my_widget_add_child(parent, section) == MY_RET_OK) {
        my_widget_unref(section); /* tree holds its own reference */
    } else {
        my_widget_unref(section);
        return false;
    }
    return true;
}

void editor_panel_profiler_tick(EditorPanelProfiler *panel) {
    u64 now;
    if (panel == NULL) {
        return;
    }
    now = time_microseconds();
    /* first tick after create always refreshes; afterwards <= 4 Hz */
    if (panel->last_refresh_us == 0u ||
        now - panel->last_refresh_us >= EDITOR_PROFILER_REFRESH_US) {
        panel->last_refresh_us = now;
        profiler_panel_refresh(panel);
    }
}

usize editor_panel_profiler_row_count(const EditorPanelProfiler *panel) {
    return panel != NULL ? (usize)panel->row_count : 0u;
}

const char *editor_panel_profiler_row_text(const EditorPanelProfiler *panel,
                                           usize i) {
    if (panel == NULL || i >= panel->row_count) {
        return NULL;
    }
    return panel->rows[i];
}
