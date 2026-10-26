/* BreakEditorPanelNetwork — Stage 4 scene editor Phase 4 Task 3: network
 * diagnostics panel, a PURE VIEW over the host-attached remote session
 * (editor_remote.h). Mirrors editor_panel_profiler.c's lifecycle exactly:
 * create = CPU state, build = widgets into the diagnostics column, destroy =
 * CPU state only, tick = throttled snapshot.
 *
 * SCOPE: the panel NEVER mutates network/session state. It reaches the
 * network ONLY through the read-only editor_remote.h accessors
 * (is_running / is_tls / outbound_count / admission_denied /
 * session_stats / connection_count / connections_snapshot) and includes no
 * transport or session header — no step, drain, send, close, or session
 * transition can originate here (source-scan + behavior pins in
 * test_editor_shell.c). Driving the remote stays the shell tick's job.
 *
 * Remote lifetime: the remote is BORROWED and may be attached/detached at
 * any time; break_editor_shell_set_remote forwards every attach/detach
 * (including break_editor_remote_destroy's detach) to
 * editor_panel_network_set_remote, so the panel never reads a destroyed
 * remote. Any attach/detach forces a refresh on the next tick.
 *
 * Rows (fixed storage, 16 rows x 96 bytes; refresh allocates nothing):
 *   remote == NULL: exactly one row, "remote: off".
 *   otherwise:
 *     [0]  reactor: running=<0|1> tls=<0|1> outbound=<n> denied=<n>
 *     [1]  session: applied=<n> unknown=<n> stale=<n>
 *     [2]  session: invalid=<n> phase_rejected=<n>
 *     [3]  session: duplicate=<n> handler_failed=<n>
 *     [4]  connections: <count>
 *     [5+] conn: key=<connection_key> state=<SESSION_STATE>
 *          (up to 11 rows; the header row carries the full count)
 *   The session counters are break_session_manager_apply_stats verbatim.
 *
 * THROTTLE: at most 4 refreshes per second (250,000 us between refreshes)
 * from break_editor_shell_tick, measured with time_microseconds() unless a
 * test clock is injected (editor_panel_network_set_clock). The first tick
 * after create — and after any remote attach/detach — always refreshes.
 *
 * Threading: single-owner-thread convention (shell thread), same as the
 * remote it reads. */

#include "editor_shell_internal.h"
#include "editor_remote.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <platform/time.h>

#include "myui/my_layout.h"
#include "myui/widgets/my_label.h"
#include "myui/widgets/my_list_view.h"

#define EDITOR_NETWORK_MAX_ROWS 16u
#define EDITOR_NETWORK_ROW_BYTES 96u
#define EDITOR_NETWORK_FIXED_ROWS 5u
#define EDITOR_NETWORK_MAX_CONN_ROWS \
    (EDITOR_NETWORK_MAX_ROWS - EDITOR_NETWORK_FIXED_ROWS)
#define EDITOR_NETWORK_REFRESH_US 250000u /* 4 Hz */

typedef struct {
    my_list_adapter_t base;
    BreakEditorPanelNetwork *panel; /* borrowed */
} EditorNetworkAdapter;

struct BreakEditorPanelNetwork {
    BreakEditorShell *shell;   /* borrowed (unused beyond create symmetry) */
    BreakEditorRemote *remote; /* borrowed; NULL = remote off */
    my_widget_t *list;         /* weak (owned by the window tree) */
    EditorNetworkAdapter adapter;
    u64 (*clock)(void *user);  /* NULL = time_microseconds */
    void *clock_user;
    bool force_refresh;        /* next tick refreshes regardless of clock */
    u64 last_refresh_us;
    u32 row_count;
    char rows[EDITOR_NETWORK_MAX_ROWS][EDITOR_NETWORK_ROW_BYTES];
};

/* ---------------- snapshot ---------------- */

/* Re-reads the remote's diagnostics into the fixed row snapshot. Pure read:
 * only const accessors of the borrowed remote are called. */
static void network_panel_refresh(BreakEditorPanelNetwork *panel) {
    const BreakEditorRemote *remote;
    BreakEditorRemoteSessionStats st;
    uint64_t keys[EDITOR_NETWORK_MAX_CONN_ROWS];
    uint32_t states[EDITOR_NETWORK_MAX_CONN_ROWS];
    u32 n, i;
    if (panel == NULL) {
        return;
    }
    remote = panel->remote;
    if (remote == NULL) {
        (void)snprintf(panel->rows[0], sizeof(panel->rows[0]), "remote: off");
        panel->row_count = 1u;
    } else {
        (void)break_editor_remote_session_stats(remote, &st);
        (void)snprintf(panel->rows[0], sizeof(panel->rows[0]),
                       "reactor: running=%u tls=%u outbound=%llu denied=%llu",
                       break_editor_remote_is_running(remote) ? 1u : 0u,
                       break_editor_remote_is_tls(remote) ? 1u : 0u,
                       (unsigned long long)break_editor_remote_outbound_count(
                           remote),
                       (unsigned long long)
                           break_editor_remote_admission_denied(remote));
        (void)snprintf(panel->rows[1], sizeof(panel->rows[1]),
                       "session: applied=%llu unknown=%llu stale=%llu",
                       (unsigned long long)st.applied,
                       (unsigned long long)st.unknown,
                       (unsigned long long)st.stale);
        (void)snprintf(panel->rows[2], sizeof(panel->rows[2]),
                       "session: invalid=%llu phase_rejected=%llu",
                       (unsigned long long)st.invalid,
                       (unsigned long long)st.phase_rejected);
        (void)snprintf(panel->rows[3], sizeof(panel->rows[3]),
                       "session: duplicate=%llu handler_failed=%llu",
                       (unsigned long long)st.duplicate,
                       (unsigned long long)st.handler_failed);
        (void)snprintf(panel->rows[4], sizeof(panel->rows[4]),
                       "connections: %u",
                       (unsigned)break_editor_remote_connection_count(remote));
        n = break_editor_remote_connections_snapshot(
            remote, keys, states, EDITOR_NETWORK_MAX_CONN_ROWS);
        if (n > EDITOR_NETWORK_MAX_CONN_ROWS) {
            n = EDITOR_NETWORK_MAX_CONN_ROWS; /* defensive; capacity-bounded */
        }
        for (i = 0u; i < n; i++) {
            (void)snprintf(panel->rows[EDITOR_NETWORK_FIXED_ROWS + i],
                           EDITOR_NETWORK_ROW_BYTES,
                           "conn: key=%llu state=%s",
                           (unsigned long long)keys[i],
                           break_editor_remote_state_name(states[i]));
        }
        panel->row_count = EDITOR_NETWORK_FIXED_ROWS + n;
    }
    if (panel->list != NULL) {
        (void)my_list_view_refresh(panel->list);
    }
}

/* ---------------- list adapter ---------------- */

static size_t network_adapter_count(my_list_adapter_t *adapter) {
    EditorNetworkAdapter *a =
        (EditorNetworkAdapter *)((char *)adapter -
                                 offsetof(EditorNetworkAdapter, base));
    return (size_t)a->panel->row_count;
}

static my_widget_t *network_adapter_create_row(my_list_adapter_t *adapter) {
    my_widget_t *row = my_label_create(NULL, "");
    (void)adapter;
    if (row == NULL) {
        return NULL;
    }
    (void)my_widget_set_name(row, "editor-network-row");
    return row;
}

static void network_adapter_bind_row(my_list_adapter_t *adapter,
                                     my_widget_t *row, size_t index) {
    EditorNetworkAdapter *a =
        (EditorNetworkAdapter *)((char *)adapter -
                                 offsetof(EditorNetworkAdapter, base));
    if (index < a->panel->row_count) {
        (void)my_label_set_text(row, a->panel->rows[index]);
    } else {
        (void)my_label_set_text(row, "<stale>");
    }
}

static const my_list_adapter_vtable_t k_network_adapter_vtable = {
    network_adapter_count, network_adapter_create_row,
    network_adapter_bind_row, NULL};

/* ---------------- lifecycle ---------------- */

BreakEditorPanelNetwork *editor_panel_network_create(BreakEditorShell *shell,
                                                     BreakEditorRemote *remote) {
    BreakEditorPanelNetwork *panel;
    if (shell == NULL) {
        return NULL;
    }
    panel = (BreakEditorPanelNetwork *)calloc(1u,
                                              sizeof(BreakEditorPanelNetwork));
    if (panel == NULL) {
        return NULL;
    }
    panel->shell = shell;
    panel->remote = remote;
    panel->force_refresh = true;
    return panel;
}

void editor_panel_network_destroy(BreakEditorPanelNetwork *p) {
    /* no CPU-side sub-objects; the widgets belong to the window tree and
     * the remote is borrowed */
    free(p);
}

void editor_panel_network_build(BreakEditorPanelNetwork *p,
                                my_widget_t *parent) {
    my_widget_t *section;
    my_widget_t *label;
    if (p == NULL || parent == NULL) {
        return;
    }
    section = my_widget_create(NULL, "editor-network-panel");
    if (section == NULL) {
        return;
    }
    (void)my_widget_set_layouter(section,
                                 my_layouter_linear_create(NULL, false, 2));
    label = my_label_create(NULL, "Network (4 Hz)");
    if (label == NULL) {
        my_widget_unref(section);
        return;
    }
    (void)my_widget_set_name(label, "editor-network-label");
    (void)my_widget_set_layout_params(label, "w:100% h:22");
    if (my_widget_add_child(section, label) == MY_RET_OK) {
        my_widget_unref(label); /* tree holds its own reference */
    } else {
        my_widget_unref(label);
        my_widget_unref(section);
        return;
    }
    p->list = my_list_view_create(NULL);
    if (p->list == NULL) {
        my_widget_unref(section);
        return;
    }
    (void)my_widget_set_name(p->list, "editor-network-list");
    p->adapter.base.vtable = &k_network_adapter_vtable;
    p->adapter.panel = p;
    if (my_list_view_set_adapter(p->list, &p->adapter.base) != MY_RET_OK) {
        my_widget_unref(p->list);
        p->list = NULL;
        my_widget_unref(section);
        return;
    }
    (void)my_widget_set_layout_params(p->list, "w:100% h:1f");
    if (my_widget_add_child(section, p->list) == MY_RET_OK) {
        my_widget_unref(p->list); /* tree holds its own reference */
    } else {
        my_widget_unref(p->list);
        p->list = NULL;
        my_widget_unref(section);
        return;
    }
    /* diagnostics row under the profiler (the shell's h:20% editor-diag-row,
     * shared with the render debugger): left half */
    (void)my_widget_set_layout_params(section, "w:50% h:100%");
    if (my_widget_add_child(parent, section) == MY_RET_OK) {
        my_widget_unref(section); /* tree holds its own reference */
    } else {
        p->list = NULL; /* died with the section */
        my_widget_unref(section);
    }
}

void editor_panel_network_tick(BreakEditorPanelNetwork *p) {
    u64 now;
    if (p == NULL) {
        return;
    }
    now = p->clock != NULL ? p->clock(p->clock_user) : time_microseconds();
    /* first tick after create / attach / detach always refreshes;
     * afterwards <= 4 Hz */
    if (p->force_refresh ||
        now - p->last_refresh_us >= EDITOR_NETWORK_REFRESH_US) {
        p->force_refresh = false;
        p->last_refresh_us = now;
        network_panel_refresh(p);
    }
}

void editor_panel_network_set_remote(BreakEditorPanelNetwork *p,
                                     BreakEditorRemote *remote) {
    if (p == NULL) {
        return;
    }
    p->remote = remote;
    p->force_refresh = true;
}

void editor_panel_network_set_clock(BreakEditorPanelNetwork *p,
                                    u64 (*clock)(void *user), void *user) {
    if (p == NULL) {
        return;
    }
    p->clock = clock;
    p->clock_user = user;
}

uint32_t editor_panel_network_row_count(const BreakEditorPanelNetwork *p) {
    return p != NULL ? p->row_count : 0u;
}

const char *editor_panel_network_row_text(const BreakEditorPanelNetwork *p,
                                          uint32_t index) {
    if (p == NULL || index >= p->row_count) {
        return NULL;
    }
    return p->rows[index];
}
