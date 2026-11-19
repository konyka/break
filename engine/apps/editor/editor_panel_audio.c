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
 * Preview: the Play/Stop button plays a copy of the attachment through the
 * shell's sink (editor_audio_preview.h); the tick pumps it, stops it when the
 * attachment revision changes and appends " | <position> / <length> s" to the
 * info line while it plays. A primary press on the waveform seeks: while
 * playing it restarts there, otherwise Play starts there next; a line marks
 * the playing position (or a non-zero cursor). An attachment change resets
 * the cursor. With a selection, Play plays only the selection. Shift+press
 * selects from the cursor to the pressed frame (both
 * included), and a drag selects the frames it passes over; Trim/Cut run the document's undoable edits on the selection,
 * and an attachment change clears it. Fade (10 ms) and Normalize (-1 dBFS)
 * act on the selection, or on the whole clip without one.
 *
 * Bounds: 2 x 4096 i16 columns + a 128-byte info line; the preview allocates
 * its copy buffer once at create. Threading: shell thread only. */

#include "editor_shell_internal.h"

#include <editor/editor_audio.h>
#include <editor/editor_i18n.h>

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "editor_audio_preview.h"
#include "editor_theme.h"
#include "myui/my_layout.h"
#include "myui/widgets/my_button.h"
#include "myui/widgets/my_label.h"

#define EDITOR_AUDIO_INFO_BYTES 128u
#define EDITOR_BOTTOM_TAB_AUDIO 4u /* index in editor_panels.c k_tab_pages[0] */
#define EDITOR_AUDIO_LIGHT_MID_LINE 0xD3D5DBFFu
#define EDITOR_AUDIO_LIGHT_CURSOR 0x1F1F1FFFu

struct EditorPanelAudio {
    BreakEditorShell *shell;  /* borrowed */
    my_widget_t *info;        /* weak (owned by the window tree) */
    my_widget_t *waveform;    /* weak */
    my_widget_t *play;        /* weak */
    my_widget_t *trim;        /* weak */
    my_widget_t *cut;         /* weak */
    my_widget_t *fade;        /* weak */
    my_widget_t *normalize;   /* weak */
    u32 sel_begin, sel_end;   /* [begin, end) frames; empty when equal */
    bool dragging;            /* a primary press is down on the waveform */
    u32 drag_anchor;          /* frame the drag started at */
    BreakEditorAudioPreview *preview; /* owned */
    bool shown_playing;       /* state the button label shows */
    u32 shown_position;       /* preview position the info line shows */
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
    const bool playing = break_editor_audio_preview_playing(panel->preview);
    if (!break_editor_doc_audio_attached(doc)) {
        (void)snprintf(panel->info_text, sizeof(panel->info_text), "%s",
                       break_editor_tr(BREAK_EDITOR_TR_AUDIO_EMPTY));
    } else {
        const u32 rate = break_editor_doc_audio_sample_rate(doc);
        int n = snprintf(panel->info_text, sizeof(panel->info_text),
                         break_editor_tr(BREAK_EDITOR_TR_AUDIO_INFO_FMT), (unsigned)rate,
                         (unsigned)break_editor_doc_audio_channels(doc),
                         (double)break_editor_doc_audio_frames(doc) / (double)rate);
        if (!playing && panel->sel_begin < panel->sel_end && n > 0 &&
            (usize)n < sizeof(panel->info_text)) {
            (void)snprintf(panel->info_text + n, sizeof(panel->info_text) - (usize)n,
                           break_editor_tr(BREAK_EDITOR_TR_AUDIO_SELECTION_FMT),
                           (double)panel->sel_begin / (double)rate,
                           (double)panel->sel_end / (double)rate);
        }
        if (playing && n > 0 && (usize)n < sizeof(panel->info_text)) {
            const double prate = (double)break_editor_audio_preview_sample_rate(panel->preview);
            (void)snprintf(panel->info_text + n, sizeof(panel->info_text) - (usize)n,
                           break_editor_tr(BREAK_EDITOR_TR_AUDIO_POSITION_FMT),
                           (double)break_editor_audio_preview_position_frames(panel->preview) /
                               prate,
                           (double)break_editor_audio_preview_length_frames(panel->preview) /
                               prate);
        }
    }
    {
        const u32 position = break_editor_audio_preview_position_frames(panel->preview);
        /* the waveform draws the playing position: repaint it when that moves */
        if (panel->waveform != NULL &&
            (playing != panel->shown_playing || position != panel->shown_position)) {
            my_widget_invalidate(panel->waveform, NULL);
        }
        panel->shown_playing = playing;
        panel->shown_position = position;
    }
    if (panel->info != NULL) {
        (void)my_label_set_text(panel->info, panel->info_text);
    }
    if (panel->play != NULL) {
        (void)my_button_set_text(panel->play, break_editor_tr(playing ? BREAK_EDITOR_TR_AUDIO_STOP
                                                                      : BREAK_EDITOR_TR_AUDIO_PLAY));
    }
    if (panel->trim != NULL) {
        (void)my_button_set_text(panel->trim, break_editor_tr(BREAK_EDITOR_TR_AUDIO_TRIM));
    }
    if (panel->cut != NULL) {
        (void)my_button_set_text(panel->cut, break_editor_tr(BREAK_EDITOR_TR_AUDIO_CUT));
    }
    if (panel->fade != NULL) {
        (void)my_button_set_text(panel->fade, break_editor_tr(BREAK_EDITOR_TR_AUDIO_FADE));
    }
    if (panel->normalize != NULL) {
        (void)my_button_set_text(panel->normalize, break_editor_tr(BREAK_EDITOR_TR_AUDIO_NORMALIZE));
    }
}

static void audio_panel_refresh(EditorPanelAudio *panel) {
    const BreakEditorDoc *doc = break_editor_shell_doc(panel->shell);
    if (panel->seen_revision != break_editor_doc_audio_revision(doc)) {
        /* the cursor and the selection may point past the new end */
        break_editor_audio_preview_reset_cursor(panel->preview);
        panel->sel_begin = panel->sel_end = 0u;
        panel->dragging = false;
    }
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

/* An attachment change no tick has seen yet (an undo in the same frame):
 * stop the stale copy and refresh, which clears the selection and resets the
 * cursor before anything reads them. */
static void audio_panel_catch_up(EditorPanelAudio *panel) {
    if (!panel->fresh || panel->seen_revision != break_editor_doc_audio_revision(
                                                     break_editor_shell_doc(panel->shell))) {
        break_editor_audio_preview_stop(panel->preview);
        audio_panel_refresh(panel);
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
    if (panel->sel_begin < panel->sel_end) {
        const u32 frames = break_editor_doc_audio_frames(break_editor_shell_doc(panel->shell));
        if (frames != 0u) {
            const float x0 = (float)((double)panel->sel_begin * (double)w / (double)frames);
            const float x1 = (float)((double)panel->sel_end * (double)w / (double)frames);
            my_vgcanvas_set_fill_color(vg, my_color_from_rgba32(break_editor_theme_is_light()
                                                                     ? BREAK_EDITOR_THEME_LIGHT_SELECTION
                                                                     : BREAK_EDITOR_THEME_SELECTION));
            (void)my_vgcanvas_fill_rect(vg, &(my_rectf_t){x0, 0.0f, x1 - x0 > 1.0f ? x1 - x0 : 1.0f,
                                                          h});
        }
    }
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
    {
        const u32 frames = break_editor_doc_audio_frames(break_editor_shell_doc(panel->shell));
        const bool playing = break_editor_audio_preview_playing(panel->preview);
        const u32 at = playing ? break_editor_audio_preview_position_frames(panel->preview)
                               : break_editor_audio_preview_cursor_frames(panel->preview);
        if (frames != 0u && (playing || at != 0u)) {
            const float x = (float)((double)at * (double)w / (double)frames);
            my_vgcanvas_set_fill_color(vg, my_color_from_rgba32(break_editor_theme_is_light()
                                                                     ? EDITOR_AUDIO_LIGHT_CURSOR
                                                                     : BREAK_EDITOR_THEME_TEXT));
            (void)my_vgcanvas_fill_rect(vg, &(my_rectf_t){x < w - 1.0f ? x : w - 1.0f, 0.0f,
                                                          1.0f, h});
        }
    }
}

/* A primary-button press seeks to the frame under the pointer and clears the
 * selection; dragging from there selects the frames passed over (both ends
 * included), and Shift+press selects from the cursor to that frame. */
static my_ret_t audio_waveform_on_event(my_widget_t *widget, const my_event_t *event) {
    EditorPanelAudio *panel;
    int32_t gx, gy;
    u32 frames, frame;
    const bool press = event != NULL && event->type == MY_EVENT_POINTER_DOWN &&
                       event->u.pointer.button == 1u;
    const bool move = event != NULL && event->type == MY_EVENT_POINTER_MOVE;
    const bool release = event != NULL && event->type == MY_EVENT_POINTER_UP &&
                         event->u.pointer.button == 1u;
    if (widget == NULL || (!press && !move && !release) || widget->rect.w <= 0) {
        return MY_RET_FAIL;
    }
    panel = (EditorPanelAudio *)my_widget_get_user_data(widget);
    if (panel == NULL || (!press && !panel->dragging)) {
        return MY_RET_FAIL; /* a move or release outside a drag is not ours */
    }
    for (const my_widget_t *w = widget; w != NULL; w = w->parent) {
        if (!w->visible) {
            /* the page was hidden mid-drag (a tab switch): the dispatcher
             * keeps the grab, so end the drag and leave the selection */
            panel->dragging = false;
            return MY_RET_FAIL;
        }
    }
    if (press) {
        audio_panel_catch_up(panel); /* the Shift anchor reads the cursor */
    }
    frames = break_editor_doc_audio_frames(break_editor_shell_doc(panel->shell));
    if (frames == 0u) {
        panel->dragging = false;
        return MY_RET_FAIL;
    }
    gx = event->u.pointer.x;
    gy = event->u.pointer.y;
    my_widget_global_to_local(widget, &gx, &gy);
    if (gx < 0) gx = 0;
    if (gx >= widget->rect.w) gx = widget->rect.w - 1;
    frame = (u32)((u64)(u32)gx * frames / (u32)widget->rect.w);
    if (press) {
        if ((event->u.pointer.modifiers & MY_KEYMOD_SHIFT) != 0u) {
            /* from the cursor to the pressed frame, both included */
            const u32 cursor = break_editor_audio_preview_cursor_frames(panel->preview);
            const u32 lo = cursor < frame ? cursor : frame;
            const u32 hi = cursor < frame ? frame : cursor;
            (void)editor_panel_audio_select(panel, lo, hi + 1u);
        } else {
            panel->dragging = true;
            panel->drag_anchor = frame;
            (void)editor_panel_audio_select(panel, 0u, 0u);
            (void)editor_panel_audio_seek(panel, frame);
        }
        return MY_RET_OK;
    }
    /* a move or release while dragging: the range between anchor and pointer,
     * both frames included; staying on the anchor keeps the plain click */
    if (frame != panel->drag_anchor) {
        const u32 lo = panel->drag_anchor < frame ? panel->drag_anchor : frame;
        const u32 hi = panel->drag_anchor < frame ? frame : panel->drag_anchor;
        (void)editor_panel_audio_select(panel, lo, hi + 1u);
    }
    if (release) {
        panel->dragging = false;
    }
    return MY_RET_OK;
}

static const my_widget_vtable_t k_audio_waveform_vtable = {audio_waveform_on_paint,
                                                           audio_waveform_on_event, NULL, NULL};

EditorPanelAudio *editor_panel_audio_create(BreakEditorShell *shell) {
    EditorPanelAudio *panel;
    if (shell == NULL) {
        return NULL;
    }
    panel = (EditorPanelAudio *)calloc(1u, sizeof(EditorPanelAudio));
    if (panel == NULL) {
        return NULL;
    }
    panel->shell = shell;
    panel->preview = break_editor_audio_preview_create();
    if (panel->preview == NULL) {
        free(panel);
        return NULL;
    }
    return panel;
}

void editor_panel_audio_destroy(EditorPanelAudio *panel) {
    /* the widgets belong to the window tree */
    if (panel != NULL) {
        break_editor_audio_preview_destroy(panel->preview);
    }
    free(panel);
}

struct BreakEditorAudioPreview *editor_panel_audio_preview(EditorPanelAudio *panel) {
    return panel != NULL ? panel->preview : NULL;
}

bool editor_panel_audio_toggle(EditorPanelAudio *panel) {
    if (panel == NULL) {
        return false;
    }
    if (break_editor_audio_preview_playing(panel->preview)) {
        break_editor_audio_preview_stop(panel->preview);
    } else if (!break_editor_audio_preview_has_sink(panel->preview)) {
        editor_shell_log(panel->shell, "%s", break_editor_tr(BREAK_EDITOR_TR_LOG_AUDIO_NO_OUTPUT));
    } else {
        /* bring the page up to date first: an edit not seen by a tick yet
         * resets the cursor, and afterwards only a later change stops it */
        if (!panel->fresh || panel->seen_revision != break_editor_doc_audio_revision(
                                                         break_editor_shell_doc(panel->shell))) {
            audio_panel_refresh(panel);
        }
        /* a selection plays on its own; otherwise from the cursor to the end */
        const bool selected = panel->sel_begin < panel->sel_end;
        if (!break_editor_audio_preview_play_range(
                panel->preview, break_editor_shell_doc(panel->shell),
                selected ? panel->sel_begin
                         : break_editor_audio_preview_cursor_frames(panel->preview),
                selected ? panel->sel_end : UINT32_MAX)) {
            editor_shell_log(panel->shell, "%s",
                             break_editor_tr(BREAK_EDITOR_TR_LOG_AUDIO_PLAY_FAILED));
        } else {
            break_editor_audio_preview_pump(panel->preview);
        }
    }
    audio_panel_format_info(panel);
    return break_editor_audio_preview_playing(panel->preview);
}

bool editor_panel_audio_seek(EditorPanelAudio *panel, u32 frame) {
    bool was_playing, playing;
    if (panel == NULL) {
        return false;
    }
    audio_panel_catch_up(panel);
    was_playing = break_editor_audio_preview_playing(panel->preview);
    playing = break_editor_audio_preview_seek(panel->preview, break_editor_shell_doc(panel->shell),
                                              frame);
    if (playing) {
        break_editor_audio_preview_pump(panel->preview);
    } else if (was_playing) {
        editor_shell_log(panel->shell, "%s",
                         break_editor_tr(BREAK_EDITOR_TR_LOG_AUDIO_PLAY_FAILED));
    }
    audio_panel_format_info(panel);
    if (panel->waveform != NULL) {
        my_widget_invalidate(panel->waveform, NULL);
    }
    return playing;
}

bool editor_panel_audio_select(EditorPanelAudio *panel, u32 begin, u32 end) {
    u32 frames;
    if (panel == NULL) {
        return false;
    }
    audio_panel_catch_up(panel);
    frames = break_editor_doc_audio_frames(break_editor_shell_doc(panel->shell));
    if (end > frames) end = frames;
    if (begin >= end) {
        begin = end = 0u;
    }
    panel->sel_begin = begin;
    panel->sel_end = end;
    audio_panel_format_info(panel);
    if (panel->waveform != NULL) {
        my_widget_invalidate(panel->waveform, NULL);
    }
    return begin < end;
}

bool editor_panel_audio_selection(const EditorPanelAudio *panel, u32 *out_begin, u32 *out_end) {
    if (panel == NULL || panel->sel_begin >= panel->sel_end) {
        return false;
    }
    if (out_begin != NULL) *out_begin = panel->sel_begin;
    if (out_end != NULL) *out_end = panel->sel_end;
    return true;
}

bool editor_panel_audio_edit_selection(EditorPanelAudio *panel, bool cut) {
    BreakEditorDoc *doc;
    bool ok;
    if (panel == NULL) {
        return false;
    }
    audio_panel_catch_up(panel);
    doc = break_editor_shell_doc(panel->shell);
    /* a trim of the whole clip would change nothing */
    if (panel->sel_begin >= panel->sel_end ||
        (!cut && panel->sel_begin == 0u &&
         panel->sel_end == break_editor_doc_audio_frames(doc))) {
        editor_shell_log(panel->shell, "%s",
                         break_editor_tr(BREAK_EDITOR_TR_LOG_AUDIO_NO_SELECTION));
        return false;
    }
    ok = cut ? break_editor_doc_audio_cut(doc, panel->sel_begin, panel->sel_end)
             : break_editor_doc_audio_trim(doc, panel->sel_begin, panel->sel_end);
    if (!ok) {
        editor_shell_log(panel->shell, "%s", break_editor_tr(BREAK_EDITOR_TR_LOG_AUDIO_EDIT_FAILED));
        return false;
    }
    /* the revision changed: stops a preview, clears the selection, resets
     * the cursor and recomputes the waveform */
    break_editor_audio_preview_stop(panel->preview);
    audio_panel_refresh(panel);
    editor_shell_refresh_all(panel->shell);
    return true;
}

#define EDITOR_AUDIO_FADE_MS 10.0
#define EDITOR_AUDIO_NORMALIZE_DBFS -1.0

bool editor_panel_audio_effect(EditorPanelAudio *panel, bool normalize) {
    BreakEditorDoc *doc;
    u32 begin, end;
    bool ok;
    if (panel == NULL) {
        return false;
    }
    audio_panel_catch_up(panel);
    doc = break_editor_shell_doc(panel->shell);
    /* the selection, or the whole clip without one */
    begin = panel->sel_begin < panel->sel_end ? panel->sel_begin : 0u;
    end = panel->sel_begin < panel->sel_end ? panel->sel_end : break_editor_doc_audio_frames(doc);
    ok = normalize ? break_editor_doc_audio_normalize_range(doc, begin, end,
                                                            EDITOR_AUDIO_NORMALIZE_DBFS)
                   : break_editor_doc_audio_fade_range(doc, begin, end, EDITOR_AUDIO_FADE_MS,
                                                       EDITOR_AUDIO_FADE_MS);
    if (!ok) {
        editor_shell_log(panel->shell, "%s", break_editor_tr(BREAK_EDITOR_TR_LOG_AUDIO_EDIT_FAILED));
        return false;
    }
    break_editor_audio_preview_stop(panel->preview);
    audio_panel_refresh(panel);
    editor_shell_refresh_all(panel->shell);
    return true;
}

static void on_audio_fade_click(void *ctx, const char *event, void *data) {
    (void)event;
    (void)data;
    (void)editor_panel_audio_effect((EditorPanelAudio *)ctx, false);
}

static void on_audio_normalize_click(void *ctx, const char *event, void *data) {
    (void)event;
    (void)data;
    (void)editor_panel_audio_effect((EditorPanelAudio *)ctx, true);
}

static void on_audio_trim_click(void *ctx, const char *event, void *data) {
    (void)event;
    (void)data;
    (void)editor_panel_audio_edit_selection((EditorPanelAudio *)ctx, false);
}

static void on_audio_cut_click(void *ctx, const char *event, void *data) {
    (void)event;
    (void)data;
    (void)editor_panel_audio_edit_selection((EditorPanelAudio *)ctx, true);
}

static void on_audio_play_click(void *ctx, const char *event, void *data) {
    (void)event;
    (void)data;
    (void)editor_panel_audio_toggle((EditorPanelAudio *)ctx);
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
    my_widget_t *section, *bar, *info, *play, *trim, *cut, *fade, *normalize, *waveform;
    if (panel == NULL || parent == NULL) {
        return false;
    }
    section = my_widget_create(NULL, "editor-audio-panel");
    if (section == NULL) {
        return false;
    }
    (void)my_widget_set_layouter(section, my_layouter_linear_create(NULL, false, 2));
    bar = my_widget_create(NULL, "editor-audio-bar");
    if (bar == NULL) {
        my_widget_unref(section);
        return false;
    }
    (void)my_widget_set_layouter(bar, my_layouter_linear_create(NULL, true, 4));
    if (!audio_panel_add(section, bar, "w:100% h:24")) {
        my_widget_unref(section);
        return false;
    }
    play = my_button_create(NULL, break_editor_tr(BREAK_EDITOR_TR_AUDIO_PLAY));
    if (play == NULL) {
        my_widget_unref(section);
        return false;
    }
    (void)my_widget_set_name(play, "editor-audio-play");
    (void)my_widget_on(play, "click", on_audio_play_click, panel);
    if (!audio_panel_add(bar, play, "w:80 h:100%")) {
        my_widget_unref(section);
        return false;
    }
    trim = my_button_create(NULL, break_editor_tr(BREAK_EDITOR_TR_AUDIO_TRIM));
    if (trim == NULL) {
        my_widget_unref(section);
        return false;
    }
    (void)my_widget_set_name(trim, "editor-audio-trim");
    (void)my_widget_on(trim, "click", on_audio_trim_click, panel);
    if (!audio_panel_add(bar, trim, "w:80 h:100%")) {
        my_widget_unref(section);
        return false;
    }
    cut = my_button_create(NULL, break_editor_tr(BREAK_EDITOR_TR_AUDIO_CUT));
    if (cut == NULL) {
        my_widget_unref(section);
        return false;
    }
    (void)my_widget_set_name(cut, "editor-audio-cut");
    (void)my_widget_on(cut, "click", on_audio_cut_click, panel);
    if (!audio_panel_add(bar, cut, "w:80 h:100%")) {
        my_widget_unref(section);
        return false;
    }
    fade = my_button_create(NULL, break_editor_tr(BREAK_EDITOR_TR_AUDIO_FADE));
    if (fade == NULL) {
        my_widget_unref(section);
        return false;
    }
    (void)my_widget_set_name(fade, "editor-audio-fade");
    (void)my_widget_on(fade, "click", on_audio_fade_click, panel);
    if (!audio_panel_add(bar, fade, "w:90 h:100%")) {
        my_widget_unref(section);
        return false;
    }
    normalize = my_button_create(NULL, break_editor_tr(BREAK_EDITOR_TR_AUDIO_NORMALIZE));
    if (normalize == NULL) {
        my_widget_unref(section);
        return false;
    }
    (void)my_widget_set_name(normalize, "editor-audio-normalize");
    (void)my_widget_on(normalize, "click", on_audio_normalize_click, panel);
    if (!audio_panel_add(bar, normalize, "w:90 h:100%")) {
        my_widget_unref(section);
        return false;
    }
    info = my_label_create(NULL, "");
    if (info == NULL) {
        my_widget_unref(section);
        return false;
    }
    (void)my_widget_set_name(info, "editor-audio-info");
    (void)my_label_set_align(info, MY_TEXT_ALIGN_LEFT);
    if (!audio_panel_add(bar, info, "w:1f h:100%")) {
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
    panel->play = play;
    panel->trim = trim;
    panel->cut = cut;
    panel->fade = fade;
    panel->normalize = normalize;
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
    if (panel->seen_revision != break_editor_doc_audio_revision(doc)) {
        /* the preview plays a copy taken at Play: an edit makes it stale
         * (the refresh below resets the cursor) */
        break_editor_audio_preview_stop(panel->preview);
    }
    break_editor_audio_preview_pump(panel->preview);
    if (!panel->fresh || panel->seen_revision != break_editor_doc_audio_revision(doc) ||
        (panel->waveform != NULL && panel->seen_width != panel->waveform->rect.w)) {
        audio_panel_refresh(panel);
    } else if (panel->shown_playing != break_editor_audio_preview_playing(panel->preview) ||
               panel->shown_position !=
                   break_editor_audio_preview_position_frames(panel->preview)) {
        audio_panel_format_info(panel);
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
