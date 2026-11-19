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
 * selects from the cursor to the pressed frame (both included), and a drag
 * selects the frames it passes over; it ends on any release, on a press
 * elsewhere taking the dispatcher's grab, and on an attachment change.
 * Trim/Cut run the document's undoable edits on the selection,
 * and an attachment change clears it. Fade (10 ms) and Normalize (-1 dBFS)
 * act on the selection, or on the whole clip without one. A ruler strip
 * above the waveform draws time ticks from editor_panel_audio_ticks. The
 * Loop checkbox makes playback start the played range again at its end.
 *
 * Bounds: 2 x 4096 i16 columns + a 128-byte info line; the preview allocates
 * its copy buffer once at create. Threading: shell thread only. */

#include "editor_shell_internal.h"

#include <editor/editor_audio.h>
#include <editor/editor_i18n.h>

#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "editor_audio_preview.h"
#include "editor_theme.h"
#include "myui/my_layout.h"
#include "myui/my_window.h"
#include "myui/widgets/my_button.h"
#include "myui/widgets/my_checkbox.h"
#include "myui/widgets/my_label.h"
#include "myui/widgets/my_scroll_bar.h"

#define EDITOR_AUDIO_INFO_BYTES 128u
#define EDITOR_AUDIO_LANES_MAX 2u /* the document accepts mono and stereo */
/* dB grid: these levels, mirrored around each lane's centre. A line closer
 * than EDITOR_AUDIO_GRID_MIN_PX to the centre, or outside the lane, is
 * dropped so a short lane or a high gain is not a solid block. */
#define EDITOR_AUDIO_GRID_MIN_PX 4.0f
#define EDITOR_AUDIO_GRID_MAX 16u /* 4 levels x 2 halves x 2 lanes */
/* a label needs this much room above its line to stay inside the lane */
#define EDITOR_AUDIO_GRID_TEXT_PX 11.0f
static const double k_audio_grid_db[] = {-6.0, -12.0, -18.0, -24.0};
#define EDITOR_BOTTOM_TAB_AUDIO 4u /* index in editor_panels.c k_tab_pages[0] */
#define EDITOR_AUDIO_LIGHT_MID_LINE 0xD3D5DBFFu
#define EDITOR_AUDIO_LIGHT_CURSOR 0x1F1F1FFFu

struct EditorPanelAudio {
    BreakEditorShell *shell;  /* borrowed */
    my_widget_t *info;        /* weak (owned by the window tree) */
    my_widget_t *waveform;    /* weak */
    my_widget_t *ruler;       /* weak */
    my_widget_t *play;        /* weak */
    my_widget_t *trim;        /* weak */
    my_widget_t *cut;         /* weak */
    my_widget_t *fade;        /* weak */
    my_widget_t *normalize;   /* weak */
    my_widget_t *loop;        /* weak */
    my_widget_t *zoom_in;     /* weak */
    my_widget_t *zoom_out;    /* weak */
    my_widget_t *scroll_left; /* weak */
    my_widget_t *scroll_right; /* weak */
    my_widget_t *follow;      /* weak */
    my_widget_t *scrollbar;   /* weak */
    my_widget_t *gain_up;     /* weak */
    my_widget_t *gain_down;   /* weak */
    my_widget_t *solo;        /* weak */
    my_widget_t *mute;        /* weak */
    my_widget_t *levels;      /* weak: the peak/RMS readout */
    u32 gain[EDITOR_AUDIO_LANES_MAX]; /* display-only, one per lane */
    bool following;           /* the view chases the playing position */
    u32 view_begin, view_end; /* visible [begin, end) frames; empty = whole clip */
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
    u32 seen_view_begin, seen_view_end;
    char info_text[EDITOR_AUDIO_INFO_BYTES];
    u32 lanes; /* one per channel, 0 without an attachment */
    u32 grid_count;                      /* lines the last paint drew */
    double grid_db[EDITOR_AUDIO_GRID_MAX];
    i32 grid_y[EDITOR_AUDIO_GRID_MAX];
    u32 grid_lane[EDITOR_AUDIO_GRID_MAX];      /* which lane each line belongs to */
    char grid_label[EDITOR_AUDIO_GRID_MAX][8]; /* "" when unlabelled */
    i16 min[EDITOR_AUDIO_LANES_MAX][BREAK_EDITOR_AUDIO_WAVEFORM_MAX_COLUMNS];
    i16 max[EDITOR_AUDIO_LANES_MAX][BREAK_EDITOR_AUDIO_WAVEFORM_MAX_COLUMNS];
};

static void audio_panel_label_solo(EditorPanelAudio *panel);
static bool audio_panel_levels(const EditorPanelAudio *panel, double *out_peak,
                               double *out_rms);

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
        {
            /* one factor when the lanes agree, "<a>x/<b>x" when they do not,
             * so a per-lane setting is visible */
            const u32 lanes = panel->lanes != 0u ? panel->lanes : 1u;
            const bool uniform = lanes < 2u || panel->gain[0] == panel->gain[1];
            const bool shown = uniform ? panel->gain[0] > 1u
                                       : (panel->gain[0] > 1u || panel->gain[1] > 1u);
            const usize len = strlen(panel->info_text);
            if (shown && len < sizeof(panel->info_text)) {
                if (uniform) {
                    (void)snprintf(panel->info_text + len,
                                   sizeof(panel->info_text) - len, " | %ux",
                                   (unsigned)panel->gain[0]);
                } else {
                    (void)snprintf(panel->info_text + len,
                                   sizeof(panel->info_text) - len, " | %ux/%ux",
                                   (unsigned)panel->gain[0], (unsigned)panel->gain[1]);
                }
            }
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
    if (panel->loop != NULL) {
        (void)my_checkbox_set_text(panel->loop, break_editor_tr(BREAK_EDITOR_TR_AUDIO_LOOP));
    }
    if (panel->follow != NULL) {
        (void)my_checkbox_set_text(panel->follow, break_editor_tr(BREAK_EDITOR_TR_AUDIO_FOLLOW));
    }
    audio_panel_label_solo(panel);
    if (panel->levels != NULL) {
        /* the level readout lives on its own label, so the info line stays
         * exactly what the format string says */
        double peak_db, rms_db;
        char text[64];
        if (audio_panel_levels(panel, &peak_db, &rms_db)) {
            (void)snprintf(text, sizeof(text), "peak %.1f dB  rms %.1f dB", peak_db,
                           rms_db);
        } else {
            text[0] = '\0';
        }
        (void)my_label_set_text(panel->levels, text);
    }
}

/* The visible range. A zero-length stored view (a fresh panel, or one whose
 * attachment changed) means the whole clip. */
static u32 audio_view_begin(const EditorPanelAudio *panel) {
    return panel->view_begin < panel->view_end ? panel->view_begin : 0u;
}

static u32 audio_view_end(const EditorPanelAudio *panel) {
    return panel->view_begin < panel->view_end
               ? panel->view_end
               : break_editor_doc_audio_frames(break_editor_shell_doc(panel->shell));
}

static u32 audio_view_len(const EditorPanelAudio *panel) {
    return audio_view_end(panel) - audio_view_begin(panel);
}

/* Mirror the view on the scroll bar: the thumb covers the visible fraction
 * and sits at the view's position in the scrollable range. set_value does
 * not emit "changed", so this cannot feed back into the handler. */
static void audio_panel_sync_scrollbar(EditorPanelAudio *panel) {
    u32 frames, len, scrollable;
    if (panel->scrollbar == NULL) {
        return;
    }
    frames = break_editor_doc_audio_frames(break_editor_shell_doc(panel->shell));
    len = audio_view_len(panel);
    if (frames == 0u || len >= frames) {
        (void)my_scroll_bar_set_page_size(panel->scrollbar, 1.0f);
        (void)my_scroll_bar_set_value(panel->scrollbar, 0.0f);
        return;
    }
    scrollable = frames - len;
    (void)my_scroll_bar_set_page_size(panel->scrollbar,
                                      (float)((double)len / (double)frames));
    (void)my_scroll_bar_set_value(
        panel->scrollbar,
        (float)((double)audio_view_begin(panel) / (double)scrollable));
}

static void audio_panel_refresh(EditorPanelAudio *panel) {
    const BreakEditorDoc *doc = break_editor_shell_doc(panel->shell);
    if (panel->seen_revision != break_editor_doc_audio_revision(doc)) {
        /* the cursor, the selection and the view may point past the new end */
        break_editor_audio_preview_reset_cursor(panel->preview);
        panel->sel_begin = panel->sel_end = 0u;
        panel->view_begin = panel->view_end = 0u;
        for (u32 lane = 0u; lane < EDITOR_AUDIO_LANES_MAX; ++lane) panel->gain[lane] = 1u;
        break_editor_audio_preview_set_solo(panel->preview, BREAK_EDITOR_AUDIO_SOLO_NONE);
        break_editor_audio_preview_set_mute(panel->preview, BREAK_EDITOR_AUDIO_MUTE_NONE);
        panel->dragging = false;
    }
    const i32 width = panel->waveform != NULL ? panel->waveform->rect.w : 0;
    u32 columns = width > 0 ? (u32)width : 1u;
    const u32 view_begin = audio_view_begin(panel);
    const u32 view_end = audio_view_end(panel);
    const u32 frames = view_end - view_begin;
    if (columns > frames) columns = frames;
    if (columns > BREAK_EDITOR_AUDIO_WAVEFORM_MAX_COLUMNS) {
        columns = BREAK_EDITOR_AUDIO_WAVEFORM_MAX_COLUMNS;
    }
    /* one lane per channel, each filled from that channel's samples */
    u32 lanes = break_editor_doc_audio_channels(doc);
    if (lanes > EDITOR_AUDIO_LANES_MAX) lanes = EDITOR_AUDIO_LANES_MAX;
    if (columns == 0u || lanes == 0u) {
        columns = lanes = 0u;
    } else {
        for (u32 lane = 0u; lane < lanes; ++lane) {
            if (!break_editor_doc_audio_waveform_channel(doc, lane, view_begin, view_end,
                                                         columns, panel->min[lane],
                                                         panel->max[lane])) {
                columns = lanes = 0u;
                break;
            }
        }
    }
    panel->columns = columns;
    panel->lanes = lanes;
    panel->seen_revision = break_editor_doc_audio_revision(doc);
    panel->seen_width = width;
    panel->seen_view_begin = view_begin;
    panel->seen_view_end = view_end;
    panel->fresh = true;
    audio_panel_format_info(panel);
    audio_panel_sync_scrollbar(panel);
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
    EditorPanelAudio *grid;
    float w, h, mid, scale, lane_h;
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
    /* one lane per channel, stacked: a stereo clip gets half the height each */
    lane_h = h / (float)(panel->lanes != 0u ? panel->lanes : 1u);
    /* the grid model is paint output, so the const view writes it through
     * one alias rather than taking the panel non-const everywhere */
    grid = (EditorPanelAudio *)panel;
    grid->grid_count = 0u;
    mid = lane_h * 0.5f;
    /* the amplitude zoom is display only and per lane: `scale` is set
     * inside the lane loop below */
    scale = 0.0f;
    if (panel->sel_begin < panel->sel_end) {
        const u32 view_begin = audio_view_begin(panel);
        const u32 view_end = audio_view_end(panel);
        /* clipped to the view: a selection may run past either edge */
        const u32 lo = panel->sel_begin > view_begin ? panel->sel_begin : view_begin;
        const u32 hi = panel->sel_end < view_end ? panel->sel_end : view_end;
        if (view_begin < view_end && lo < hi) {
            const double len = (double)(view_end - view_begin);
            const float x0 = (float)((double)(lo - view_begin) * (double)w / len);
            const float x1 = (float)((double)(hi - view_begin) * (double)w / len);
            my_vgcanvas_set_fill_color(vg, my_color_from_rgba32(break_editor_theme_is_light()
                                                                     ? BREAK_EDITOR_THEME_LIGHT_SELECTION
                                                                     : BREAK_EDITOR_THEME_SELECTION));
            (void)my_vgcanvas_fill_rect(vg, &(my_rectf_t){x0, 0.0f, x1 - x0 > 1.0f ? x1 - x0 : 1.0f,
                                                          h});
        }
    }
    for (u32 lane = 0u; lane < panel->lanes; ++lane) {
        const float lane_mid = (float)lane * lane_h + mid;
        const u32 lane_gain = lane < EDITOR_AUDIO_LANES_MAX && panel->gain[lane] != 0u
                                  ? panel->gain[lane]
                                  : 1u;
        scale = (lane_h * 0.5f) * (float)lane_gain / 32768.0f;
        my_vgcanvas_set_fill_color(vg, my_color_from_rgba32(break_editor_theme_is_light()
                                                                 ? EDITOR_AUDIO_LIGHT_MID_LINE
                                                                 : BREAK_EDITOR_THEME_BORDER));
        (void)my_vgcanvas_fill_rect(vg, &(my_rectf_t){0.0f, lane_mid, w, 1.0f});
        /* the dB grid, under the trace: the same scale the columns use, so
         * it follows the amplitude zoom */
        for (usize g = 0u; g < sizeof(k_audio_grid_db) / sizeof(k_audio_grid_db[0]); ++g) {
            const float offset =
                (float)pow(10.0, k_audio_grid_db[g] / 20.0) * 32768.0f * scale;
            if (offset < EDITOR_AUDIO_GRID_MIN_PX || offset > lane_h * 0.5f) {
                continue; /* too close to the centre, or off the lane */
            }
            (void)my_vgcanvas_fill_rect(vg, &(my_rectf_t){0.0f, lane_mid - offset, w, 1.0f});
            (void)my_vgcanvas_fill_rect(vg, &(my_rectf_t){0.0f, lane_mid + offset, w, 1.0f});
            /* the level above the upper line, when it fits inside the lane;
             * the lower line is the same level mirrored, so one is enough */
            char label[8];
            const float top = lane_mid - offset;
            const bool labelled = top - (float)lane * lane_h >= EDITOR_AUDIO_GRID_TEXT_PX;
            (void)snprintf(label, sizeof(label), "%d", (int)k_audio_grid_db[g]);
            if (labelled) {
                my_vgcanvas_set_fill_color(
                    vg, my_color_from_rgba32(break_editor_theme_is_light()
                                                 ? EDITOR_AUDIO_LIGHT_CURSOR
                                                 : BREAK_EDITOR_THEME_TEXT_SECONDARY));
                (void)my_vgcanvas_draw_text(vg, label, 2.0f, top - 1.0f);
                my_vgcanvas_set_fill_color(
                    vg, my_color_from_rgba32(break_editor_theme_is_light()
                                                 ? EDITOR_AUDIO_LIGHT_MID_LINE
                                                 : BREAK_EDITOR_THEME_BORDER));
            }
            if (grid->grid_count + 2u <= EDITOR_AUDIO_GRID_MAX) {
                /* the model the test reads: every lane's two halves */
                grid->grid_db[grid->grid_count] = k_audio_grid_db[g];
                grid->grid_y[grid->grid_count] = (i32)top;
                grid->grid_lane[grid->grid_count] = lane;
                (void)snprintf(grid->grid_label[grid->grid_count],
                               sizeof(grid->grid_label[0]), "%s", labelled ? label : "");
                grid->grid_count++;
                grid->grid_db[grid->grid_count] = k_audio_grid_db[g];
                grid->grid_y[grid->grid_count] = (i32)(lane_mid + offset);
                grid->grid_lane[grid->grid_count] = lane;
                grid->grid_label[grid->grid_count][0] = '\0'; /* mirrored: no label */
                grid->grid_count++;
            }
        }
        my_vgcanvas_set_fill_color(vg, my_color_from_rgba32(BREAK_EDITOR_THEME_ACCENT));
        for (c = 0u; c < panel->columns; c++) {
            const float x0 = (float)c * w / (float)panel->columns;
            const float x1 = (float)(c + 1u) * w / (float)panel->columns;
            /* a zoomed column may reach past the widget; my_widget_paint
             * clips every widget to its own rect, so it cannot reach the
             * ruler (lanes may still overlap each other at high gain) */
            const float top = lane_mid - (float)panel->max[lane][c] * scale;
            const float bottom = lane_mid - (float)panel->min[lane][c] * scale;
            const float bar_w = x1 - x0 > 1.0f ? x1 - x0 : 1.0f;
            const float bar_h = bottom - top > 1.0f ? bottom - top : 1.0f;
            (void)my_vgcanvas_fill_rect(vg, &(my_rectf_t){x0, top, bar_w, bar_h});
        }
    }
    {
        const u32 view_begin = audio_view_begin(panel);
        const u32 view_end = audio_view_end(panel);
        const bool playing = break_editor_audio_preview_playing(panel->preview);
        const u32 at = playing ? break_editor_audio_preview_position_frames(panel->preview)
                               : break_editor_audio_preview_cursor_frames(panel->preview);
        /* only while it is inside the view */
        if (view_begin < view_end && at >= view_begin && at < view_end && (playing || at != 0u)) {
            const float x = (float)((double)(at - view_begin) * (double)w /
                                    (double)(view_end - view_begin));
            my_vgcanvas_set_fill_color(vg, my_color_from_rgba32(break_editor_theme_is_light()
                                                                     ? EDITOR_AUDIO_LIGHT_CURSOR
                                                                     : BREAK_EDITOR_THEME_TEXT));
            (void)my_vgcanvas_fill_rect(vg, &(my_rectf_t){x < w - 1.0f ? x : w - 1.0f, 0.0f,
                                                          1.0f, h});
        }
    }
}

/* Does the dispatcher still deliver moves and releases to this widget?
 * It hands the grab to whatever is pressed next and drops it on any
 * release, neither of which the widget is told about. */
static bool audio_has_grab(const EditorPanelAudio *panel, const my_widget_t *widget) {
    const my_window_t *window = break_editor_shell_window(panel->shell);
    return window != NULL && window->dispatcher.grabbed == widget;
}

static bool audio_view_set(EditorPanelAudio *panel, u32 begin, u32 end);

/* View keys, only while the waveform holds the focus (the dispatcher routes
 * key events there): +/= zoom in, - zooms out, the arrows scroll, Home shows
 * the whole clip. A handled key is consumed so it does not also reach the
 * shell's global shortcuts. */
static bool audio_waveform_on_key(EditorPanelAudio *panel, const my_event_t *event) {
    if (panel == NULL) {
        return false;
    }
    audio_panel_catch_up(panel);
    if (break_editor_doc_audio_frames(break_editor_shell_doc(panel->shell)) == 0u) {
        return false; /* nothing to look at: leave the keys to the shell */
    }
    switch (event->u.key.key) {
    case '+':
    case '=':
        (void)editor_panel_audio_zoom(panel, true);
        return true;
    case '-':
        (void)editor_panel_audio_zoom(panel, false);
        return true;
    case MY_KEY_LEFT:
        (void)editor_panel_audio_scroll(panel, false);
        return true;
    case MY_KEY_RIGHT:
        (void)editor_panel_audio_scroll(panel, true);
        return true;
    case MY_KEY_HOME:
        (void)audio_view_set(panel, 0u,
                             break_editor_doc_audio_frames(
                                 break_editor_shell_doc(panel->shell)));
        return true;
    default:
        return false;
    }
}

/* The frame under the pointer, through the view. */
static u32 audio_frame_at_pointer(const EditorPanelAudio *panel, const my_widget_t *widget,
                                  const my_event_t *event) {
    int32_t gx = event->u.pointer.x;
    int32_t gy = event->u.pointer.y;
    my_widget_global_to_local((my_widget_t *)widget, &gx, &gy);
    if (gx < 0) gx = 0;
    if (gx >= widget->rect.w) gx = widget->rect.w - 1;
    return audio_view_begin(panel) +
           (u32)((u64)(u32)gx * audio_view_len(panel) / (u32)widget->rect.w);
}

/* The wheel zooms around the frame under the pointer, one step per row; with
 * Shift it scrolls the view instead, forward on a scroll down. */
static bool audio_waveform_on_wheel(EditorPanelAudio *panel, my_widget_t *widget,
                                    const my_event_t *event) {
    i32 rows = event->u.pointer.delta;
    u32 steps;
    bool changed = false;
    if (panel == NULL || rows == 0) {
        return false;
    }
    audio_panel_catch_up(panel);
    if (break_editor_doc_audio_frames(break_editor_shell_doc(panel->shell)) == 0u) {
        return false;
    }
    steps = (u32)(rows > 0 ? rows : -rows);
    for (u32 i = 0u; i < steps; ++i) {
        if ((event->u.pointer.modifiers & MY_KEYMOD_SHIFT) != 0u) {
            changed = editor_panel_audio_scroll(panel, rows < 0) || changed;
        } else {
            changed = editor_panel_audio_zoom_at(panel, rows > 0,
                                                 audio_frame_at_pointer(panel, widget, event)) ||
                      changed;
        }
    }
    return changed;
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
    /* any release ends the drag: the dispatcher drops the grab on all of
     * them, so a non-primary one would otherwise leave the drag live */
    const bool release = event != NULL && event->type == MY_EVENT_POINTER_UP;
    const bool wheel = event != NULL && event->type == MY_EVENT_POINTER_WHEEL;
    const bool key = event != NULL && event->type == MY_EVENT_KEY_DOWN;
    if (widget == NULL || (!press && !move && !release && !wheel && !key) ||
        widget->rect.w <= 0) {
        return MY_RET_FAIL;
    }
    panel = (EditorPanelAudio *)my_widget_get_user_data(widget);
    if (key) {
        return audio_waveform_on_key(panel, event) ? MY_RET_OK : MY_RET_FAIL;
    }
    if (wheel) {
        return audio_waveform_on_wheel(panel, widget, event) ? MY_RET_OK : MY_RET_FAIL;
    }
    if (panel == NULL || (!press && !panel->dragging)) {
        return MY_RET_FAIL; /* a move or release outside a drag is not ours */
    }
    if (release && event->u.pointer.button != 1u) {
        panel->dragging = false; /* the grab is gone; keep the selection */
        return MY_RET_FAIL;
    }
    if (move && !audio_has_grab(panel, widget)) {
        /* a press elsewhere took the grab: this is a plain hover */
        panel->dragging = false;
        return MY_RET_FAIL;
    }
    for (const my_widget_t *w = widget; w != NULL; w = w->parent) {
        if (!w->visible) {
            /* the page was hidden mid-drag (a tab switch): the dispatcher
             * keeps the grab, so end the drag and leave the selection */
            panel->dragging = false;
            return MY_RET_FAIL;
        }
    }
    /* an edit no tick has seen yet (an undo in the same frame) clears the
     * selection and the drag before the anchor meets the new clip */
    audio_panel_catch_up(panel);
    if (!press && !panel->dragging) {
        return MY_RET_FAIL;
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
    /* through the view, not the whole clip */
    frame = audio_view_begin(panel) +
            (u32)((u64)(u32)gx * audio_view_len(panel) / (u32)widget->rect.w);
    if (frame >= frames) frame = frames - 1u;
    if (press) {
        if ((event->u.pointer.modifiers & MY_KEYMOD_SHIFT) != 0u) {
            /* from the cursor to the pressed frame, both included */
            const u32 cursor = break_editor_audio_preview_cursor_frames(panel->preview);
            const u32 lo = cursor < frame ? cursor : frame;
            const u32 hi = cursor < frame ? frame : cursor;
            panel->dragging = false; /* no drag follows a Shift press */
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
     * both frames included; back on the anchor it is a plain click again */
    if (frame != panel->drag_anchor) {
        const u32 lo = panel->drag_anchor < frame ? panel->drag_anchor : frame;
        const u32 hi = panel->drag_anchor < frame ? frame : panel->drag_anchor;
        (void)editor_panel_audio_select(panel, lo, hi + 1u);
    } else {
        (void)editor_panel_audio_select(panel, 0u, 0u);
    }
    if (release) {
        panel->dragging = false;
    }
    return MY_RET_OK;
}

static void audio_ruler_on_paint(my_widget_t *widget, my_vgcanvas_t *vg) {
    const EditorPanelAudio *panel;
    EditorAudioTicks ticks;
    float h;
    u32 i;
    if (widget == NULL || vg == NULL) {
        return;
    }
    h = (float)widget->rect.h;
    my_vgcanvas_set_fill_color(vg, my_color_from_rgba32(break_editor_theme_content_bg()));
    (void)my_vgcanvas_fill_rect(vg, &(my_rectf_t){0.0f, 0.0f, (float)widget->rect.w, h});
    panel = (const EditorPanelAudio *)my_widget_get_user_data(widget);
    if (!editor_panel_audio_ticks(panel, &ticks)) {
        return;
    }
    my_vgcanvas_set_fill_color(vg, my_color_from_rgba32(break_editor_theme_is_light()
                                                             ? EDITOR_AUDIO_LIGHT_CURSOR
                                                             : BREAK_EDITOR_THEME_TEXT_SECONDARY));
    for (i = 0u; i < ticks.count; ++i) {
        (void)my_vgcanvas_fill_rect(vg, &(my_rectf_t){(float)ticks.x[i], h * 0.5f, 1.0f, h * 0.5f});
        (void)my_vgcanvas_draw_text(vg, ticks.label[i], (float)ticks.x[i] + 3.0f, h * 0.5f);
    }
}

u32 editor_panel_audio_grid_count(const EditorPanelAudio *panel) {
    return panel != NULL ? panel->grid_count : 0u;
}

const char *editor_panel_audio_grid_label(const EditorPanelAudio *panel, u32 i) {
    return panel != NULL && i < panel->grid_count ? panel->grid_label[i] : NULL;
}

bool editor_panel_audio_grid(const EditorPanelAudio *panel, u32 i, double *out_db,
                             i32 *out_y) {
    if (panel == NULL || i >= panel->grid_count) {
        return false;
    }
    if (out_db != NULL) *out_db = panel->grid_db[i];
    if (out_y != NULL) *out_y = panel->grid_y[i];
    return true;
}

u32 editor_panel_audio_grid_lane(const EditorPanelAudio *panel, u32 i) {
    return panel != NULL && i < panel->grid_count ? panel->grid_lane[i] : UINT32_MAX;
}

static const my_widget_vtable_t k_audio_ruler_vtable = {audio_ruler_on_paint, NULL, NULL, NULL};

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
    for (u32 lane = 0u; lane < EDITOR_AUDIO_LANES_MAX; ++lane) panel->gain[lane] = 1u;
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

/* Tick steps in milliseconds, smallest first: the ruler takes the first one
 * that keeps the ticks EDITOR_AUDIO_TICK_MIN_PX apart. */
static const u32 k_audio_tick_steps_ms[] = {1u,     2u,     5u,     10u,    20u,     50u,
                                            100u,   200u,   500u,   1000u,  2000u,   5000u,
                                            10000u, 20000u, 30000u, 60000u, 120000u, 300000u};
#define EDITOR_AUDIO_TICK_MIN_PX 60

/* Zooming in stops here: fewer frames than this across the width makes the
 * columns meaningless (one frame repeated over many pixels). */
#define EDITOR_AUDIO_VIEW_MIN_FRAMES 16u
#define EDITOR_AUDIO_SCROLL_DIVISOR 4u /* one step = a quarter of the view */

/* Replaces the visible range, clamped to the clip; returns whether it moved.
 * A change recomputes the columns and repaints the waveform and the ruler. */
static bool audio_view_set(EditorPanelAudio *panel, u32 begin, u32 end) {
    const u32 frames = break_editor_doc_audio_frames(break_editor_shell_doc(panel->shell));
    if (frames == 0u) {
        return false;
    }
    if (end > frames) end = frames;
    if (begin >= end) {
        return false;
    }
    if (begin == audio_view_begin(panel) && end == audio_view_end(panel)) {
        return false;
    }
    panel->view_begin = begin;
    panel->view_end = end;
    audio_panel_refresh(panel); /* the columns belong to the view */
    if (panel->ruler != NULL) {
        my_widget_invalidate(panel->ruler, NULL);
    }
    return true;
}

bool editor_panel_audio_zoom_at(EditorPanelAudio *panel, bool in, u32 anchor) {
    u32 frames, len, new_len, begin, offset;
    if (panel == NULL) {
        return false;
    }
    audio_panel_catch_up(panel);
    frames = break_editor_doc_audio_frames(break_editor_shell_doc(panel->shell));
    if (frames == 0u) {
        return false;
    }
    len = audio_view_len(panel);
    begin = audio_view_begin(panel);
    if (anchor < begin || anchor >= begin + len) {
        anchor = begin + len / 2u; /* outside the view: fall back to its centre */
    }
    offset = anchor - begin; /* where in the view the anchor sits */
    if (in) {
        new_len = len / 2u;
        if (new_len < EDITOR_AUDIO_VIEW_MIN_FRAMES) {
            new_len = EDITOR_AUDIO_VIEW_MIN_FRAMES;
        }
        if (new_len >= len) {
            return false; /* already at the floor */
        }
    } else {
        new_len = len < frames / 2u ? len * 2u : frames;
    }
    if (new_len >= frames) {
        return audio_view_set(panel, 0u, frames);
    }
    /* keep the anchor at the same fraction of the view, then push the range
     * inside the clip */
    {
        const u32 keep = (u32)((u64)offset * new_len / len);
        begin = anchor > keep ? anchor - keep : 0u;
    }
    if (begin + new_len > frames) {
        begin = frames - new_len;
    }
    return audio_view_set(panel, begin, begin + new_len);
}

bool editor_panel_audio_zoom(EditorPanelAudio *panel, bool in) {
    if (panel == NULL) {
        return false;
    }
    /* the centre of the view: the buttons have no pointer to anchor at */
    return editor_panel_audio_zoom_at(panel, in,
                                      audio_view_begin(panel) + audio_view_len(panel) / 2u);
}

#define EDITOR_AUDIO_GAIN_MAX 32u

u32 editor_panel_audio_set_lane_gain(EditorPanelAudio *panel, u32 lane, u32 gain) {
    u32 snapped = 1u;
    if (panel == NULL || lane >= EDITOR_AUDIO_LANES_MAX) {
        return 0u;
    }
    /* the largest power of two at or below the request, within [1, 32] */
    while (snapped * 2u <= gain && snapped < EDITOR_AUDIO_GAIN_MAX) {
        snapped *= 2u;
    }
    if (snapped != panel->gain[lane]) {
        panel->gain[lane] = snapped;
        audio_panel_format_info(panel); /* the suffix and the repaint */
        if (panel->waveform != NULL) {
            my_widget_invalidate(panel->waveform, NULL);
        }
    }
    return panel->gain[lane];
}

u32 editor_panel_audio_lane_gain(const EditorPanelAudio *panel, u32 lane) {
    return panel != NULL && lane < EDITOR_AUDIO_LANES_MAX ? panel->gain[lane] : 0u;
}

u32 editor_panel_audio_set_gain(EditorPanelAudio *panel, u32 gain) {
    u32 first = 0u;
    if (panel == NULL) {
        return 0u;
    }
    for (u32 lane = 0u; lane < EDITOR_AUDIO_LANES_MAX; ++lane) {
        const u32 applied = editor_panel_audio_set_lane_gain(panel, lane, gain);
        if (lane == 0u) first = applied;
    }
    return first;
}

u32 editor_panel_audio_gain(const EditorPanelAudio *panel) {
    return editor_panel_audio_lane_gain(panel, 0u);
}

/* "<Verb>" with no channel picked, "<Verb> L"/"<Verb> R" for a stereo
 * clip's two channels, "<Verb> <n>" otherwise (mono, or an index beyond R).
 * Shared by the Solo and Mute buttons, which differ only in their keys. */
static void audio_panel_label_channel(EditorPanelAudio *panel, my_widget_t *button,
                                      u32 channel, BreakEditorTr none, BreakEditorTr left,
                                      BreakEditorTr right, BreakEditorTr fmt) {
    char text[32];
    if (button == NULL) {
        return;
    }
    if (channel == UINT32_MAX) {
        (void)my_button_set_text(button, break_editor_tr(none));
        return;
    }
    if (break_editor_doc_audio_channels(break_editor_shell_doc(panel->shell)) == 2u &&
        channel < 2u) {
        (void)my_button_set_text(button, break_editor_tr(channel == 0u ? left : right));
        return;
    }
    (void)snprintf(text, sizeof(text), break_editor_tr(fmt), (unsigned)(channel + 1u));
    (void)my_button_set_text(button, text);
}

static void audio_panel_label_solo(EditorPanelAudio *panel) {
    audio_panel_label_channel(panel, panel->solo,
                              break_editor_audio_preview_solo(panel->preview),
                              BREAK_EDITOR_TR_AUDIO_SOLO, BREAK_EDITOR_TR_AUDIO_SOLO_LEFT,
                              BREAK_EDITOR_TR_AUDIO_SOLO_RIGHT,
                              BREAK_EDITOR_TR_AUDIO_SOLO_FMT);
    audio_panel_label_channel(panel, panel->mute,
                              break_editor_audio_preview_mute(panel->preview),
                              BREAK_EDITOR_TR_AUDIO_MUTE, BREAK_EDITOR_TR_AUDIO_MUTE_LEFT,
                              BREAK_EDITOR_TR_AUDIO_MUTE_RIGHT,
                              BREAK_EDITOR_TR_AUDIO_MUTE_FMT);
}

/* 20*log10(value/32768), floored so digital silence is a number. The zero
 * check is for the FE_DIVBYZERO flag log10(0) would raise; the floor
 * comparison below would catch the resulting -inf by itself. */
static double audio_db_of(double value) {
    if (value <= 0.0) {
        return BREAK_EDITOR_AUDIO_DB_FLOOR;
    }
    const double db = 20.0 * log10(value / 32768.0);
    return db > BREAK_EDITOR_AUDIO_DB_FLOOR ? db : BREAK_EDITOR_AUDIO_DB_FLOOR;
}

/* Peak and RMS of the visible range; false leaves both at the floor. */
static bool audio_panel_levels(const EditorPanelAudio *panel, double *out_peak,
                               double *out_rms) {
    *out_peak = *out_rms = BREAK_EDITOR_AUDIO_DB_FLOOR;
    if (panel == NULL) {
        return false;
    }
    double peak = 0.0, rms = 0.0;
    if (!break_editor_doc_audio_peak_range(break_editor_shell_doc(panel->shell),
                                           audio_view_begin(panel), audio_view_end(panel),
                                           &peak, &rms)) {
        return false;
    }
    *out_peak = audio_db_of(peak);
    *out_rms = audio_db_of(rms);
    return true;
}

double editor_panel_audio_peak_db(const EditorPanelAudio *panel) {
    double peak, rms;
    (void)audio_panel_levels(panel, &peak, &rms);
    return peak;
}

double editor_panel_audio_rms_db(const EditorPanelAudio *panel) {
    double peak, rms;
    (void)audio_panel_levels(panel, &peak, &rms);
    return rms;
}

u32 editor_panel_audio_set_mute(EditorPanelAudio *panel, u32 channel) {
    if (panel == NULL) {
        return BREAK_EDITOR_AUDIO_MUTE_NONE;
    }
    break_editor_audio_preview_set_mute(panel->preview, channel);
    audio_panel_label_solo(panel);
    return break_editor_audio_preview_mute(panel->preview);
}

u32 editor_panel_audio_mute(const EditorPanelAudio *panel) {
    return panel != NULL ? break_editor_audio_preview_mute(panel->preview)
                         : BREAK_EDITOR_AUDIO_MUTE_NONE;
}

/* The next channel in the none -> 0 -> ... -> last -> none cycle. */
static u32 audio_panel_cycle_channel(const EditorPanelAudio *panel, u32 current) {
    const u32 channels =
        break_editor_doc_audio_channels(break_editor_shell_doc(panel->shell));
    if (channels == 0u) {
        return UINT32_MAX;
    }
    if (current == UINT32_MAX) {
        return 0u;
    }
    return current + 1u < channels ? current + 1u : UINT32_MAX;
}

static void on_audio_mute_click(void *ctx, const char *event, void *data) {
    EditorPanelAudio *panel = (EditorPanelAudio *)ctx;
    (void)event;
    (void)data;
    if (panel != NULL) {
        audio_panel_catch_up(panel);
        (void)editor_panel_audio_set_mute(
            panel, audio_panel_cycle_channel(
                       panel, break_editor_audio_preview_mute(panel->preview)));
    }
}

u32 editor_panel_audio_set_solo(EditorPanelAudio *panel, u32 channel) {
    if (panel == NULL) {
        return BREAK_EDITOR_AUDIO_SOLO_NONE;
    }
    break_editor_audio_preview_set_solo(panel->preview, channel);
    audio_panel_label_solo(panel);
    return break_editor_audio_preview_solo(panel->preview);
}

u32 editor_panel_audio_solo(const EditorPanelAudio *panel) {
    return panel != NULL ? break_editor_audio_preview_solo(panel->preview)
                         : BREAK_EDITOR_AUDIO_SOLO_NONE;
}

static void on_audio_solo_click(void *ctx, const char *event, void *data) {
    EditorPanelAudio *panel = (EditorPanelAudio *)ctx;
    (void)event;
    (void)data;
    if (panel != NULL) {
        audio_panel_catch_up(panel);
        (void)editor_panel_audio_set_solo(
            panel, audio_panel_cycle_channel(
                       panel, break_editor_audio_preview_solo(panel->preview)));
    }
}

u32 editor_panel_audio_fit_lane_gain(EditorPanelAudio *panel, u32 lane) {
    u32 peak = 0u, fitted = 1u;
    if (panel == NULL || lane >= EDITOR_AUDIO_LANES_MAX) {
        return 0u;
    }
    audio_panel_catch_up(panel); /* the columns must match the view */
    if (lane >= panel->lanes || panel->columns == 0u) {
        return 0u;
    }
    /* the loudest sample of this lane's visible columns */
    for (u32 c = 0u; c < panel->columns; ++c) {
        const i32 lo = panel->min[lane][c] < 0 ? -(i32)panel->min[lane][c]
                                               : (i32)panel->min[lane][c];
        const i32 hi = panel->max[lane][c] < 0 ? -(i32)panel->max[lane][c]
                                               : (i32)panel->max[lane][c];
        const u32 mag = (u32)(lo > hi ? lo : hi);
        if (mag > peak) peak = mag;
    }
    if (peak == 0u) {
        return panel->gain[lane]; /* a silent lane: nothing to fit */
    }
    while (fitted * 2u <= EDITOR_AUDIO_GAIN_MAX && (fitted * 2u) * peak <= 32768u) {
        fitted *= 2u;
    }
    return editor_panel_audio_set_lane_gain(panel, lane, fitted);
}

/* Each lane to its own peak, which is what makes two channels of very
 * different level comparable in one look. Returns lane 0's factor. */
u32 editor_panel_audio_fit_gain(EditorPanelAudio *panel) {
    u32 first = 0u;
    if (panel == NULL) {
        return 0u;
    }
    audio_panel_catch_up(panel);
    if (panel->lanes == 0u || panel->columns == 0u) {
        return 0u;
    }
    for (u32 lane = 0u; lane < panel->lanes; ++lane) {
        const u32 applied = editor_panel_audio_fit_lane_gain(panel, lane);
        if (lane == 0u) first = applied;
    }
    return first;
}


static void on_audio_gain_fit_click(void *ctx, const char *event, void *data) {
    (void)event;
    (void)data;
    (void)editor_panel_audio_fit_gain((EditorPanelAudio *)ctx);
}

static void on_audio_gain_up_click(void *ctx, const char *event, void *data) {
    EditorPanelAudio *panel = (EditorPanelAudio *)ctx;
    (void)event;
    (void)data;
    if (panel != NULL) {
        (void)editor_panel_audio_set_gain(panel, editor_panel_audio_gain(panel) * 2u);
    }
}

static void on_audio_gain_down_click(void *ctx, const char *event, void *data) {
    EditorPanelAudio *panel = (EditorPanelAudio *)ctx;
    (void)event;
    (void)data;
    if (panel != NULL) {
        (void)editor_panel_audio_set_gain(panel, editor_panel_audio_gain(panel) / 2u);
    }
}

void editor_panel_audio_set_follow(EditorPanelAudio *panel, bool follow) {
    if (panel == NULL) {
        return;
    }
    panel->following = follow;
    if (panel->follow != NULL) {
        (void)my_checkbox_set_checked(panel->follow, follow);
    }
}

bool editor_panel_audio_follow(const EditorPanelAudio *panel) {
    return panel != NULL && panel->following;
}

/* While Follow is on and a preview is playing, keep the playing position
 * inside a view shorter than the clip, a view length at a time. */
static void audio_panel_follow_position(EditorPanelAudio *panel) {
    u32 frames, len, begin, at;
    if (!panel->following || !break_editor_audio_preview_playing(panel->preview)) {
        return;
    }
    frames = break_editor_doc_audio_frames(break_editor_shell_doc(panel->shell));
    len = audio_view_len(panel);
    if (frames == 0u) {
        return;
    }
    at = break_editor_audio_preview_position_frames(panel->preview);
    begin = audio_view_begin(panel);
    /* a view covering the whole clip always holds the position, so the
     * check below also makes it stay put */
    if (at >= begin && at < begin + len) {
        return;
    }
    while (at >= begin + len) {
        begin += len;
    }
    while (at < begin) {
        begin = begin > len ? begin - len : 0u;
    }
    if (begin + len > frames) {
        begin = frames - len;
    }
    (void)audio_view_set(panel, begin, begin + len);
}

bool editor_panel_audio_scroll(EditorPanelAudio *panel, bool forward) {
    u32 frames, len, step, begin;
    if (panel == NULL) {
        return false;
    }
    audio_panel_catch_up(panel);
    frames = break_editor_doc_audio_frames(break_editor_shell_doc(panel->shell));
    if (frames == 0u) {
        return false;
    }
    len = audio_view_len(panel);
    if (len >= frames) {
        return false; /* the whole clip is visible */
    }
    step = len / EDITOR_AUDIO_SCROLL_DIVISOR;
    if (step == 0u) {
        step = 1u;
    }
    begin = audio_view_begin(panel);
    if (forward) {
        begin += step;
        if (begin + len > frames) {
            begin = frames - len;
        }
    } else {
        begin = begin > step ? begin - step : 0u;
    }
    return audio_view_set(panel, begin, begin + len);
}

bool editor_panel_audio_view(const EditorPanelAudio *panel, u32 *out_begin, u32 *out_end) {
    u32 begin, end;
    if (panel == NULL) {
        return false;
    }
    begin = audio_view_begin(panel);
    end = audio_view_end(panel);
    if (begin >= end) {
        return false; /* no attachment */
    }
    if (out_begin != NULL) *out_begin = begin;
    if (out_end != NULL) *out_end = end;
    return true;
}

static void on_audio_zoom_in_click(void *ctx, const char *event, void *data) {
    (void)event;
    (void)data;
    (void)editor_panel_audio_zoom((EditorPanelAudio *)ctx, true);
}

static void on_audio_zoom_out_click(void *ctx, const char *event, void *data) {
    (void)event;
    (void)data;
    (void)editor_panel_audio_zoom((EditorPanelAudio *)ctx, false);
}

static void on_audio_scroll_left_click(void *ctx, const char *event, void *data) {
    (void)event;
    (void)data;
    (void)editor_panel_audio_scroll((EditorPanelAudio *)ctx, false);
}

static void on_audio_scroll_right_click(void *ctx, const char *event, void *data) {
    (void)event;
    (void)data;
    (void)editor_panel_audio_scroll((EditorPanelAudio *)ctx, true);
}

void editor_panel_audio_set_loop(EditorPanelAudio *panel, bool loop) {
    if (panel == NULL) {
        return;
    }
    break_editor_audio_preview_set_loop(panel->preview, loop);
    if (panel->loop != NULL) {
        (void)my_checkbox_set_checked(panel->loop, loop);
    }
}

/* Dragging the bar moves the view, keeping its length. */
static void on_audio_scrollbar_changed(void *ctx, const char *event, void *data) {
    EditorPanelAudio *panel = (EditorPanelAudio *)ctx;
    u32 frames, len, scrollable, begin;
    (void)event;
    (void)data;
    if (panel == NULL || panel->scrollbar == NULL) {
        return;
    }
    audio_panel_catch_up(panel);
    frames = break_editor_doc_audio_frames(break_editor_shell_doc(panel->shell));
    len = audio_view_len(panel);
    if (frames == 0u || len >= frames) {
        return; /* nothing to scroll */
    }
    scrollable = frames - len;
    begin = (u32)((double)my_scroll_bar_get_value(panel->scrollbar) *
                      (double)scrollable +
                  0.5);
    (void)audio_view_set(panel, begin, begin + len);
}

static void on_audio_follow_changed(void *ctx, const char *event, void *data) {
    EditorPanelAudio *panel = (EditorPanelAudio *)ctx;
    (void)event;
    (void)data;
    if (panel != NULL && panel->follow != NULL) {
        panel->following = my_checkbox_get_checked(panel->follow);
    }
}

static void on_audio_loop_changed(void *ctx, const char *event, void *data) {
    EditorPanelAudio *panel = (EditorPanelAudio *)ctx;
    (void)event;
    (void)data;
    if (panel != NULL && panel->loop != NULL) {
        break_editor_audio_preview_set_loop(panel->preview,
                                            my_checkbox_get_checked(panel->loop));
    }
}

bool editor_panel_audio_ticks(const EditorPanelAudio *panel, EditorAudioTicks *out) {
    if (out == NULL) {
        return false;
    }
    out->count = 0u;
    if (panel == NULL || panel->ruler == NULL || panel->ruler->rect.w < 1) {
        return false;
    }
    const u32 rate = break_editor_doc_audio_sample_rate(break_editor_shell_doc(panel->shell));
    const u32 view_begin = audio_view_begin(panel);
    const u32 view_end = audio_view_end(panel);
    const u32 frames = view_end - view_begin; /* the visible span, not the clip */
    const u32 width = (u32)panel->ruler->rect.w;
    if (frames == 0u || rate == 0u) {
        return false;
    }
    u32 step = 0u;
    for (usize i = 0u; i < sizeof(k_audio_tick_steps_ms) / sizeof(k_audio_tick_steps_ms[0]); ++i) {
        const u64 step_frames = (u64)k_audio_tick_steps_ms[i] * rate / 1000u;
        if (step_frames == 0u) {
            continue;
        }
        if (step_frames * width / frames >= (u64)EDITOR_AUDIO_TICK_MIN_PX) {
            step = (u32)step_frames;
            break;
        }
    }
    if (step == 0u) {
        step = frames; /* even the largest step is too narrow: one tick only */
    }
    /* the first multiple of the step at or after the view's start, so the
     * labels stay on round times while the view scrolls */
    for (u32 frame = view_begin - view_begin % step;
         frame < view_end && out->count < EDITOR_AUDIO_TICKS_MAX; frame += step) {
        u32 i;
        double seconds;
        if (frame < view_begin) {
            continue;
        }
        i = out->count++;
        seconds = (double)frame / (double)rate;
        out->frame[i] = frame;
        out->x[i] = (i32)((u64)(frame - view_begin) * width / frames);
        if (seconds < 10.0) {
            (void)snprintf(out->label[i], sizeof(out->label[i]), "%.3f s", seconds);
        } else {
            const u32 total = (u32)(seconds + 0.0005);
            (void)snprintf(out->label[i], sizeof(out->label[i]), "%u:%02u", total / 60u,
                           total % 60u);
        }
    }
    return out->count != 0u;
}

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
    my_widget_t *section, *bar, *info, *play, *trim, *cut, *fade, *normalize, *loop, *ruler,
        *waveform, *view_bar, *zoom_in, *zoom_out, *scroll_left, *scroll_right,
        *follow_box, *scrollbar, *gain_up, *gain_down, *gain_fit, *solo_btn, *mute_btn, *levels_label;
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
    loop = my_checkbox_create(NULL, break_editor_tr(BREAK_EDITOR_TR_AUDIO_LOOP));
    if (loop == NULL) {
        my_widget_unref(section);
        return false;
    }
    (void)my_widget_set_name(loop, "editor-audio-loop");
    (void)my_widget_on(loop, "changed", on_audio_loop_changed, panel);
    if (!audio_panel_add(bar, loop, "w:70 h:100%")) {
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
    /* the view controls sit on their own row so the toolbar keeps room for
     * the info label; their symbols need no translation */
    view_bar = my_widget_create(NULL, "editor-audio-view-bar");
    if (view_bar == NULL) {
        my_widget_unref(section);
        return false;
    }
    (void)my_widget_set_layouter(view_bar, my_layouter_linear_create(NULL, true, 4));
    if (!audio_panel_add(section, view_bar, "w:100% h:20")) {
        my_widget_unref(section);
        return false;
    }
    zoom_in = my_button_create(NULL, "+");
    zoom_out = my_button_create(NULL, "-");
    scroll_left = my_button_create(NULL, "<");
    scroll_right = my_button_create(NULL, ">");
    if (zoom_in == NULL || zoom_out == NULL || scroll_left == NULL || scroll_right == NULL) {
        if (zoom_in != NULL) my_widget_unref(zoom_in);
        if (zoom_out != NULL) my_widget_unref(zoom_out);
        if (scroll_left != NULL) my_widget_unref(scroll_left);
        if (scroll_right != NULL) my_widget_unref(scroll_right);
        my_widget_unref(section);
        return false;
    }
    (void)my_widget_set_name(zoom_out, "editor-audio-zoom-out");
    (void)my_widget_set_name(zoom_in, "editor-audio-zoom-in");
    (void)my_widget_set_name(scroll_left, "editor-audio-scroll-left");
    (void)my_widget_set_name(scroll_right, "editor-audio-scroll-right");
    (void)my_widget_on(zoom_out, "click", on_audio_zoom_out_click, panel);
    (void)my_widget_on(zoom_in, "click", on_audio_zoom_in_click, panel);
    (void)my_widget_on(scroll_left, "click", on_audio_scroll_left_click, panel);
    (void)my_widget_on(scroll_right, "click", on_audio_scroll_right_click, panel);
    if (!audio_panel_add(view_bar, zoom_out, "w:26 h:100%") ||
        !audio_panel_add(view_bar, zoom_in, "w:26 h:100%") ||
        !audio_panel_add(view_bar, scroll_left, "w:26 h:100%") ||
        !audio_panel_add(view_bar, scroll_right, "w:26 h:100%")) {
        my_widget_unref(section);
        return false;
    }
    /* amplitude zoom: display only, so symbols rather than words */
    gain_down = my_button_create(NULL, "v");
    gain_up = my_button_create(NULL, "^");
    if (gain_down == NULL || gain_up == NULL) {
        if (gain_down != NULL) my_widget_unref(gain_down);
        if (gain_up != NULL) my_widget_unref(gain_up);
        my_widget_unref(section);
        return false;
    }
    (void)my_widget_set_name(gain_down, "editor-audio-gain-down");
    (void)my_widget_set_name(gain_up, "editor-audio-gain-up");
    (void)my_widget_on(gain_down, "click", on_audio_gain_down_click, panel);
    (void)my_widget_on(gain_up, "click", on_audio_gain_up_click, panel);
    gain_fit = my_button_create(NULL, "=");
    if (gain_fit == NULL) {
        my_widget_unref(gain_down);
        my_widget_unref(gain_up);
        my_widget_unref(section);
        return false;
    }
    (void)my_widget_set_name(gain_fit, "editor-audio-gain-fit");
    (void)my_widget_on(gain_fit, "click", on_audio_gain_fit_click, panel);
    solo_btn = my_button_create(NULL, break_editor_tr(BREAK_EDITOR_TR_AUDIO_SOLO));
    if (solo_btn == NULL) {
        my_widget_unref(gain_down);
        my_widget_unref(gain_up);
        my_widget_unref(gain_fit);
        my_widget_unref(section);
        return false;
    }
    (void)my_widget_set_name(solo_btn, "editor-audio-solo");
    (void)my_widget_on(solo_btn, "click", on_audio_solo_click, panel);
    mute_btn = my_button_create(NULL, break_editor_tr(BREAK_EDITOR_TR_AUDIO_MUTE));
    if (mute_btn == NULL) {
        my_widget_unref(gain_down);
        my_widget_unref(gain_up);
        my_widget_unref(gain_fit);
        my_widget_unref(solo_btn);
        my_widget_unref(section);
        return false;
    }
    (void)my_widget_set_name(mute_btn, "editor-audio-mute");
    (void)my_widget_on(mute_btn, "click", on_audio_mute_click, panel);
    levels_label = my_label_create(NULL, "");
    if (levels_label == NULL) {
        my_widget_unref(gain_down);
        my_widget_unref(gain_up);
        my_widget_unref(gain_fit);
        my_widget_unref(solo_btn);
        my_widget_unref(mute_btn);
        my_widget_unref(section);
        return false;
    }
    (void)my_widget_set_name(levels_label, "editor-audio-levels");
    (void)my_label_set_align(levels_label, MY_TEXT_ALIGN_LEFT);
    if (!audio_panel_add(view_bar, gain_down, "w:26 h:100%") ||
        !audio_panel_add(view_bar, gain_up, "w:26 h:100%") ||
        !audio_panel_add(view_bar, gain_fit, "w:26 h:100%") ||
        !audio_panel_add(view_bar, solo_btn, "w:70 h:100%") ||
        !audio_panel_add(view_bar, mute_btn, "w:75 h:100%") ||
        !audio_panel_add(view_bar, levels_label, "w:1f h:100%")) {
        my_widget_unref(section);
        return false;
    }
    follow_box = my_checkbox_create(NULL, break_editor_tr(BREAK_EDITOR_TR_AUDIO_FOLLOW));
    if (follow_box == NULL) {
        my_widget_unref(section);
        return false;
    }
    (void)my_widget_set_name(follow_box, "editor-audio-follow");
    (void)my_widget_on(follow_box, "changed", on_audio_follow_changed, panel);
    if (!audio_panel_add(view_bar, follow_box, "w:80 h:100%")) {
        my_widget_unref(section);
        return false;
    }
    ruler = my_widget_create(NULL, "editor-audio-ruler");
    if (ruler == NULL || my_widget_subclass_init(ruler, &k_audio_ruler_vtable) != MY_RET_OK) {
        if (ruler != NULL) {
            my_widget_unref(ruler);
        }
        my_widget_unref(section);
        return false;
    }
    (void)my_widget_set_name(ruler, "editor-audio-ruler");
    (void)my_widget_set_user_data(ruler, panel);
    if (!audio_panel_add(section, ruler, "w:100% h:16")) {
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
    /* a press focuses it, which scopes the view keys to this page */
    waveform->focusable = true;
    if (!audio_panel_add(section, waveform, "w:100% h:1f")) {
        my_widget_unref(section);
        return false;
    }
    scrollbar = my_scroll_bar_create(NULL);
    if (scrollbar == NULL) {
        my_widget_unref(section);
        return false;
    }
    (void)my_widget_set_name(scrollbar, "editor-audio-scrollbar");
    (void)my_scroll_bar_set_horizontal(scrollbar, true);
    (void)my_widget_on(scrollbar, "changed", on_audio_scrollbar_changed, panel);
    if (!audio_panel_add(section, scrollbar, "w:100% h:12")) {
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
    panel->loop = loop;
    panel->zoom_in = zoom_in;
    panel->zoom_out = zoom_out;
    panel->scroll_left = scroll_left;
    panel->scroll_right = scroll_right;
    panel->follow = follow_box;
    panel->scrollbar = scrollbar;
    panel->gain_up = gain_up;
    panel->gain_down = gain_down;
    panel->solo = solo_btn;
    panel->mute = mute_btn;
    panel->levels = levels_label;
    panel->waveform = waveform;
    panel->ruler = ruler;
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
    audio_panel_follow_position(panel);
    if (!panel->fresh || panel->seen_revision != break_editor_doc_audio_revision(doc) ||
        (panel->waveform != NULL && panel->seen_width != panel->waveform->rect.w) ||
        panel->seen_view_begin != audio_view_begin(panel) ||
        panel->seen_view_end != audio_view_end(panel)) {
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

u32 editor_panel_audio_lane_count(const EditorPanelAudio *panel) {
    return panel != NULL ? panel->lanes : 0u;
}

bool editor_panel_audio_lane_column(const EditorPanelAudio *panel, u32 lane, u32 i,
                                    i16 *out_min, i16 *out_max) {
    if (panel == NULL || lane >= panel->lanes || i >= panel->columns || out_min == NULL ||
        out_max == NULL) {
        return false;
    }
    *out_min = panel->min[lane][i];
    *out_max = panel->max[lane][i];
    return true;
}

bool editor_panel_audio_column(const EditorPanelAudio *panel, u32 i,
                               i16 *out_min, i16 *out_max) {
    if (panel == NULL || i >= panel->columns || out_min == NULL || out_max == NULL) {
        return false;
    }
    *out_min = panel->min[0][i];
    *out_max = panel->max[0][i];
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
