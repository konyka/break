/* EditorPanelAudio: the Audio page of the bottom tool window, a read-only
 * view of the document's PCM attachment (editor_audio.h).
 *
 * Layout: an info label ("No audio..." or "<rate> Hz, <ch> ch, <s> s") over a
 * self-painted waveform widget. The tick compares the attachment revision and
 * the widget width with the last refresh; on a change it recomputes
 * min(width, frames, BREAK_EDITOR_AUDIO_WAVEFORM_MAX_COLUMNS) min/max columns
 * (at least 1) into fixed panel storage and invalidates the widget. The paint
 * draws one bar per column from min to max around the centre line.
 *
 * Opening: editor_shell_open_audio (asset browser .wav rows) attaches a file
 * only while the document has no attachment; replacing one would leave audio
 * snapshot commands in the history that belong to the old buffer. Opening
 * keeps the document's dirty flag as it was (a clean scene stays clean); the
 * page itself refreshes on the next tick.
 *
 * Bounds: 2 x 4096 i16 columns + a 96-byte info line, no allocation after
 * create. Threading: shell thread only. */

#include "editor_shell_internal.h"

#include <editor/editor_audio.h>
#include <editor/editor_i18n.h>

#include <stdio.h>
#include <stdlib.h>

#include "editor_theme.h"
#include "myui/my_layout.h"
#include "myui/widgets/my_label.h"

#define EDITOR_AUDIO_INFO_BYTES 96u
#define EDITOR_BOTTOM_TAB_AUDIO 4u /* index in editor_panels.c k_tab_pages[0] */
#define EDITOR_AUDIO_LIGHT_MID_LINE 0xD3D5DBFFu

struct EditorPanelAudio {
    BreakEditorShell *shell;  /* borrowed */
    my_widget_t *info;        /* weak (owned by the window tree) */
    my_widget_t *waveform;    /* weak */
    bool fresh;               /* false = next tick refreshes */
    u64 seen_revision;
    i32 seen_width;
    u32 columns;
    char info_text[EDITOR_AUDIO_INFO_BYTES];
    i16 min[BREAK_EDITOR_AUDIO_WAVEFORM_MAX_COLUMNS];
    i16 max[BREAK_EDITOR_AUDIO_WAVEFORM_MAX_COLUMNS];
};

static void audio_panel_format_info(EditorPanelAudio *panel) {
    const BreakEditorDoc *doc = break_editor_shell_doc(panel->shell);
    if (!break_editor_doc_audio_attached(doc)) {
        (void)snprintf(panel->info_text, sizeof(panel->info_text), "%s",
                       break_editor_tr(BREAK_EDITOR_TR_AUDIO_EMPTY));
    } else {
        const u32 rate = break_editor_doc_audio_sample_rate(doc);
        (void)snprintf(panel->info_text, sizeof(panel->info_text),
                       break_editor_tr(BREAK_EDITOR_TR_AUDIO_INFO_FMT), (unsigned)rate,
                       (unsigned)break_editor_doc_audio_channels(doc),
                       (double)break_editor_doc_audio_frames(doc) / (double)rate);
    }
    if (panel->info != NULL) {
        (void)my_label_set_text(panel->info, panel->info_text);
    }
}

static void audio_panel_refresh(EditorPanelAudio *panel) {
    const BreakEditorDoc *doc = break_editor_shell_doc(panel->shell);
    const i32 width = panel->waveform != NULL ? panel->waveform->rect.w : 0;
    u32 columns = width > 0 ? (u32)width : 1u;
    const u32 frames = break_editor_doc_audio_frames(doc);
    if (columns > frames) columns = frames;
    if (columns > BREAK_EDITOR_AUDIO_WAVEFORM_MAX_COLUMNS) {
        columns = BREAK_EDITOR_AUDIO_WAVEFORM_MAX_COLUMNS;
    }
    if (columns == 0u ||
        !break_editor_doc_audio_waveform(doc, columns, panel->min, panel->max)) {
        columns = 0u;
    }
    panel->columns = columns;
    panel->seen_revision = break_editor_doc_audio_revision(doc);
    panel->seen_width = width;
    panel->fresh = true;
    audio_panel_format_info(panel);
    if (panel->waveform != NULL) {
        my_widget_invalidate(panel->waveform, NULL);
    }
}

static void audio_waveform_on_paint(my_widget_t *widget, my_vgcanvas_t *vg) {
    const EditorPanelAudio *panel;
    float w, h, mid, scale;
    u32 c;
    if (widget == NULL || vg == NULL) {
        return;
    }
    w = (float)widget->rect.w;
    h = (float)widget->rect.h;
    my_vgcanvas_set_fill_color(vg, my_color_from_rgba32(break_editor_theme_content_bg()));
    (void)my_vgcanvas_fill_rect(vg, &(my_rectf_t){0.0f, 0.0f, w, h});
    panel = (const EditorPanelAudio *)my_widget_get_user_data(widget);
    if (panel == NULL || panel->columns == 0u || w <= 0.0f || h <= 0.0f) {
        return;
    }
    mid = h * 0.5f;
    scale = (h * 0.5f) / 32768.0f;
    my_vgcanvas_set_fill_color(vg, my_color_from_rgba32(break_editor_theme_is_light()
                                                             ? EDITOR_AUDIO_LIGHT_MID_LINE
                                                             : BREAK_EDITOR_THEME_BORDER));
    (void)my_vgcanvas_fill_rect(vg, &(my_rectf_t){0.0f, mid, w, 1.0f});
    my_vgcanvas_set_fill_color(vg, my_color_from_rgba32(BREAK_EDITOR_THEME_ACCENT));
    for (c = 0u; c < panel->columns; c++) {
        const float x0 = (float)c * w / (float)panel->columns;
        const float x1 = (float)(c + 1u) * w / (float)panel->columns;
        const float top = mid - (float)panel->max[c] * scale;
        const float bottom = mid - (float)panel->min[c] * scale;
        const float bar_w = x1 - x0 > 1.0f ? x1 - x0 : 1.0f;
        const float bar_h = bottom - top > 1.0f ? bottom - top : 1.0f;
        (void)my_vgcanvas_fill_rect(vg, &(my_rectf_t){x0, top, bar_w, bar_h});
    }
}

static const my_widget_vtable_t k_audio_waveform_vtable = {audio_waveform_on_paint, NULL,
                                                           NULL, NULL};

EditorPanelAudio *editor_panel_audio_create(BreakEditorShell *shell) {
    EditorPanelAudio *panel;
    if (shell == NULL) {
        return NULL;
    }
    panel = (EditorPanelAudio *)calloc(1u, sizeof(EditorPanelAudio));
    if (panel != NULL) {
        panel->shell = shell;
    }
    return panel;
}

void editor_panel_audio_destroy(EditorPanelAudio *panel) {
    /* the widgets belong to the window tree */
    free(panel);
}

static bool audio_panel_add(my_widget_t *parent, my_widget_t *child, const char *params) {
    (void)my_widget_set_layout_params(child, params);
    if (my_widget_add_child(parent, child) != MY_RET_OK) {
        my_widget_unref(child);
        return false;
    }
    my_widget_unref(child); /* tree holds its own reference */
    return true;
}

bool editor_panel_audio_build(EditorPanelAudio *panel, my_widget_t *parent) {
    my_widget_t *section, *info, *waveform;
    if (panel == NULL || parent == NULL) {
        return false;
    }
    section = my_widget_create(NULL, "editor-audio-panel");
    if (section == NULL) {
        return false;
    }
    (void)my_widget_set_layouter(section, my_layouter_linear_create(NULL, false, 2));
    info = my_label_create(NULL, "");
    if (info == NULL) {
        my_widget_unref(section);
        return false;
    }
    (void)my_widget_set_name(info, "editor-audio-info");
    (void)my_label_set_align(info, MY_TEXT_ALIGN_LEFT);
    if (!audio_panel_add(section, info, "w:100% h:22")) {
        my_widget_unref(section);
        return false;
    }
    waveform = my_widget_create(NULL, "editor-audio-waveform");
    if (waveform == NULL ||
        my_widget_subclass_init(waveform, &k_audio_waveform_vtable) != MY_RET_OK) {
        if (waveform != NULL) {
            my_widget_unref(waveform);
        }
        my_widget_unref(section);
        return false;
    }
    (void)my_widget_set_name(waveform, "editor-audio-waveform");
    (void)my_widget_set_user_data(waveform, panel);
    if (!audio_panel_add(section, waveform, "w:100% h:1f")) {
        my_widget_unref(section);
        return false;
    }
    if (!audio_panel_add(parent, section, "w:100% h:1f")) {
        return false;
    }
    panel->info = info;
    panel->waveform = waveform;
    panel->fresh = false;
    audio_panel_format_info(panel);
    return true;
}

void editor_panel_audio_tick(EditorPanelAudio *panel) {
    const BreakEditorDoc *doc;
    if (panel == NULL) {
        return;
    }
    doc = break_editor_shell_doc(panel->shell);
    if (!panel->fresh || panel->seen_revision != break_editor_doc_audio_revision(doc) ||
        (panel->waveform != NULL && panel->seen_width != panel->waveform->rect.w)) {
        audio_panel_refresh(panel);
    }
}

void editor_panel_audio_retranslate(EditorPanelAudio *panel) {
    if (panel != NULL) {
        audio_panel_format_info(panel);
    }
}

const char *editor_panel_audio_info_text(const EditorPanelAudio *panel) {
    return panel != NULL ? panel->info_text : NULL;
}

u32 editor_panel_audio_column_count(const EditorPanelAudio *panel) {
    return panel != NULL ? panel->columns : 0u;
}

bool editor_panel_audio_column(const EditorPanelAudio *panel, u32 i,
                               i16 *out_min, i16 *out_max) {
    if (panel == NULL || i >= panel->columns || out_min == NULL || out_max == NULL) {
        return false;
    }
    *out_min = panel->min[i];
    *out_max = panel->max[i];
    return true;
}

bool editor_shell_open_audio(BreakEditorShell *shell, const char *path,
                             const char *name) {
    BreakEditorDoc *doc = break_editor_shell_doc(shell);
    if (doc == NULL || path == NULL || name == NULL) {
        return false;
    }
    if (break_editor_doc_audio_attached(doc)) {
        editor_shell_log(shell, break_editor_tr(BREAK_EDITOR_TR_LOG_AUDIO_ALREADY_FMT), name);
        return false;
    }
    /* opening is a view, not an edit: the scene's unsaved state is kept */
    const bool was_dirty = break_editor_doc_is_dirty(doc);
    if (!break_editor_doc_audio_attach_wav(doc, path)) {
        editor_shell_log(shell, break_editor_tr(BREAK_EDITOR_TR_LOG_AUDIO_FAILED_FMT), name);
        return false;
    }
    if (!was_dirty) {
        break_editor_doc_clear_dirty(doc);
    }
    editor_shell_log(shell, break_editor_tr(BREAK_EDITOR_TR_LOG_AUDIO_OPENED_FMT), name);
    (void)break_editor_shell_select_tab(shell, 0u, EDITOR_BOTTOM_TAB_AUDIO);
    editor_shell_refresh_all(shell);
    return true;
}
