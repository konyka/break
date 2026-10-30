#pragma once
/* Editor UI preferences persisted across runs: theme, language and the
 * active tool-window tabs. A tiny "key=value" text file (one per line, '#'
 * comments, unknown keys ignored so newer files load in older builds).
 *
 * Location: $BREAK_EDITOR_SETTINGS if set, else
 * $XDG_CONFIG_HOME/break/editor.ini, else $HOME/.config/break/editor.ini
 * (Windows: %APPDATA%\break\editor.ini). A missing or unreadable file means
 * defaults; a bad value keeps that field's default. Saving creates the
 * parent directory and replaces the file atomically. Nothing here is
 * trusted for anything but UI state. */

#include <core/types.h>

#include <editor/editor_i18n.h>

#define BREAK_EDITOR_SETTINGS_RECENT_MAX 5u
#define BREAK_EDITOR_SETTINGS_RECENT_PATH 400u

typedef struct {
    bool light_theme;
    bool has_lang; /* false: language comes from --lang / the environment */
    BreakEditorLang lang;
    u32 bottom_tab; /* 0 Console, 1 Lua */
    u32 diag_tab;   /* 0 Profiler, 1 Network, 2 Render */
    bool snap;      /* gizmo snapping on (default steps) */
    bool stats;     /* viewport stats overlay (default on) */
    bool grid;      /* viewport ground grid (default on) */
    bool wireframe; /* viewport wireframe proxies (default off) */
    /* recently opened/saved scenes, newest first (recent=<path> lines) */
    u32 recent_count;
    char recent[BREAK_EDITOR_SETTINGS_RECENT_MAX][BREAK_EDITOR_SETTINGS_RECENT_PATH];
} BreakEditorSettings;

void break_editor_settings_defaults(BreakEditorSettings *s);
/* false only for NULL arguments; malformed lines are skipped */
bool break_editor_settings_parse(BreakEditorSettings *s, const char *text,
                                 usize len);
/* bytes written (no NUL counted), 0 when it does not fit */
usize break_editor_settings_serialize(const BreakEditorSettings *s, char *out,
                                      usize cap);
bool break_editor_settings_default_path(char *out, usize cap);
/* Moves `path` to the front of the recent list (dropping an older copy and
 * the oldest entry beyond the cap). NULL, empty or too-long paths (no room
 * for the NUL in RECENT_PATH) are ignored. */
void break_editor_settings_note_recent(BreakEditorSettings *s, const char *path);
/* load: true for a missing file (defaults kept); false only for NULL args */
bool break_editor_settings_load(BreakEditorSettings *s, const char *path);
bool break_editor_settings_save(const BreakEditorSettings *s, const char *path);
