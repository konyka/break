#pragma once
/* Editor UI translations (design: docs/design/editor_i18n.md).
 *
 * Every user-visible editor string is a BreakEditorTr key looked up in the
 * current language's table. Keys are an enum, not free strings, so a typo is
 * a compile error and a test can check that every language fills every key.
 * Format keys (`*_FMT`) carry printf conversions; all languages use the same
 * conversions in the same order, so callers keep using bounded snprintf.
 *
 * The current language is one process-wide value owned by the editor UI
 * (shell) thread. It is not synchronized; set it only on that thread.
 *
 * Not translated: engine LOG_* output, remote protocol text, entity and file
 * names, and console lines already written. */

#include <core/types.h>

typedef enum {
    BREAK_EDITOR_LANG_EN_US = 0,
    BREAK_EDITOR_LANG_ZH_CN,
    BREAK_EDITOR_LANG_COUNT
} BreakEditorLang;

typedef enum {
    /* toolbar / panels */
    BREAK_EDITOR_TR_ADD = 0,
    BREAK_EDITOR_TR_REMOVE,
    BREAK_EDITOR_TR_OUTLINER,
    BREAK_EDITOR_TR_NO_SELECTION,
    BREAK_EDITOR_TR_NAME,
    BREAK_EDITOR_TR_ENTITY_NAME_HINT,
    BREAK_EDITOR_TR_COMMAND_HINT,
    BREAK_EDITOR_TR_STALE_ROW,
    BREAK_EDITOR_TR_ASSETS_PREFIX,
    BREAK_EDITOR_TR_ASSETS_FILTER_HINT,
    BREAK_EDITOR_TR_ASSETS_UNAVAILABLE,
    BREAK_EDITOR_TR_ASSETS_PATH_FMT,  /* %s relative path */
    BREAK_EDITOR_TR_LUA_TITLE,
    BREAK_EDITOR_TR_LUA_HINT,
    BREAK_EDITOR_TR_NETWORK_TITLE,
    BREAK_EDITOR_TR_PROFILER_TITLE,
    BREAK_EDITOR_TR_RENDER_TITLE,
    /* tools */
    BREAK_EDITOR_TR_TOOL_SELECT,
    BREAK_EDITOR_TR_TOOL_TRANSLATE,
    BREAK_EDITOR_TR_TOOL_ROTATE,
    BREAK_EDITOR_TR_TOOL_SCALE,
    BREAK_EDITOR_TR_TOOL_LABEL_FMT,   /* %s tool name */
    BREAK_EDITOR_TR_STATUS_FMT,       /* %llu %d %.100s %.100s */
    /* command palette */
    BREAK_EDITOR_TR_CMD_ADD_ENTITY,
    BREAK_EDITOR_TR_CMD_REMOVE_SELECTED,
    BREAK_EDITOR_TR_CMD_RENAME_SELECTED,
    BREAK_EDITOR_TR_CMD_SAVE_SCENE,
    BREAK_EDITOR_TR_CMD_UNDO,
    BREAK_EDITOR_TR_CMD_REDO,
    BREAK_EDITOR_TR_CMD_DUPLICATE_SELECTED,
    BREAK_EDITOR_TR_CMD_TOGGLE_SNAP,
    BREAK_EDITOR_TR_SNAP_SUFFIX,
    BREAK_EDITOR_TR_CMD_TOGGLE_STATS,
    BREAK_EDITOR_TR_CMD_TOGGLE_GRID,
    BREAK_EDITOR_TR_CMD_RESET_VIEW,
    BREAK_EDITOR_TR_VIEWPORT_STATS_FMT, /* %u entities %u selected %u draws %u x %u */
    BREAK_EDITOR_TR_CMD_TOOL_FMT,     /* %s tool name */
    BREAK_EDITOR_TR_CMD_LANG_EN,
    BREAK_EDITOR_TR_CMD_LANG_ZH,
    BREAK_EDITOR_TR_CMD_THEME_LIGHT,
    BREAK_EDITOR_TR_CMD_THEME_DARK,
    /* tool-window tabs */
    BREAK_EDITOR_TR_TAB_CONSOLE,
    BREAK_EDITOR_TR_TAB_LUA,
    BREAK_EDITOR_TR_TAB_PROFILER,
    BREAK_EDITOR_TR_TAB_NETWORK,
    BREAK_EDITOR_TR_TAB_RENDER,
    /* console lines */
    BREAK_EDITOR_TR_LOG_READY,
    BREAK_EDITOR_TR_LOG_PALETTE_FMT,          /* %s */
    BREAK_EDITOR_TR_LOG_LANGUAGE_FMT,         /* %s */
    BREAK_EDITOR_TR_LOG_ADD_ENTITY_FMT,       /* %s */
    BREAK_EDITOR_TR_LOG_ADD_ENTITY_FAILED,
    BREAK_EDITOR_TR_LOG_DUPLICATE_FMT,        /* %s */
    BREAK_EDITOR_TR_LOG_DUPLICATE_FAILED,
    BREAK_EDITOR_TR_LOG_CLOSE_UNSAVED,
    BREAK_EDITOR_TR_LOG_REMOVE_NO_SELECTION,
    BREAK_EDITOR_TR_LOG_REMOVE_ENTITY_FMT,    /* %s */
    BREAK_EDITOR_TR_LOG_REMOVE_MANY_FMT,      /* %u */
    BREAK_EDITOR_TR_LOG_DUPLICATE_MANY_FMT,   /* %u */
    BREAK_EDITOR_TR_LOG_HIDE_FMT,             /* %u */
    BREAK_EDITOR_TR_UNTITLED,
    BREAK_EDITOR_TR_LOG_LOAD_UNSAVED,
    BREAK_EDITOR_TR_CMD_SAVE_AS_FMT,          /* %s path */
    BREAK_EDITOR_TR_WINDOW_TITLE_FMT,         /* %s dirty mark, %s name */
    BREAK_EDITOR_TR_LOG_SHOW_ALL_FMT,         /* %u */
    BREAK_EDITOR_TR_LOG_REMOVE_ENTITY_FAILED,
    BREAK_EDITOR_TR_LOG_SAVE_NO_PATH,
    BREAK_EDITOR_TR_LOG_SAVED_FMT,            /* %s */
    BREAK_EDITOR_TR_LOG_SAVE_FAILED_FMT,      /* %s */
    BREAK_EDITOR_TR_LOG_UNDO_OK_FMT,          /* %s */
    BREAK_EDITOR_TR_LOG_UNDO_NOTHING,
    BREAK_EDITOR_TR_LOG_REDO_OK_FMT,          /* %s */
    BREAK_EDITOR_TR_LOG_REDO_NOTHING,
    BREAK_EDITOR_TR_LOG_TOOL_FMT,             /* %s */
    BREAK_EDITOR_TR_NOTE_FOCUS_FMT,           /* %s */
    BREAK_EDITOR_TR_LOG_FOCUS_FMT,            /* %s %.3g %.3g %.3g */
    BREAK_EDITOR_TR_LOG_FOCUS_NO_SELECTION,
    BREAK_EDITOR_TR_NOTE_FOCUS_SCENE,
    BREAK_EDITOR_TR_LOG_FOCUS_SCENE_FMT,      /* %u %.3g %.3g %.3g */
    BREAK_EDITOR_TR_LOG_RENAME_HINT,
    BREAK_EDITOR_TR_LOG_RENAME_NO_SELECTION,
    BREAK_EDITOR_TR_LOG_RENAME_FMT,           /* %s */
    BREAK_EDITOR_TR_LOG_RENAME_FAILED_FMT,    /* %u */
    BREAK_EDITOR_TR_LOG_INVALID_F32_FMT,      /* %s */
    BREAK_EDITOR_TR_LOG_SET_FIELD_FMT,        /* %s %u %g */
    BREAK_EDITOR_TR_LOG_SET_FIELD_FAILED,
    BREAK_EDITOR_TR_LOG_ADD_COMPONENT_FMT,    /* %u */
    BREAK_EDITOR_TR_LOG_ADD_COMPONENT_FAILED_FMT,    /* %u */
    BREAK_EDITOR_TR_LOG_REMOVE_COMPONENT_FMT,        /* %u */
    BREAK_EDITOR_TR_LOG_REMOVE_COMPONENT_FAILED_FMT, /* %u */
    BREAK_EDITOR_TR_LOG_LOAD_FMT,             /* %s */
    BREAK_EDITOR_TR_LOG_LOAD_FAILED_FMT,      /* %s */
    BREAK_EDITOR_TR_LOG_ASSET_NOT_SCENE_FMT,  /* %s */
    BREAK_EDITOR_TR_LOG_LUA_UNAVAILABLE,
    BREAK_EDITOR_TR_LOG_HR_STALE_FMT,
    BREAK_EDITOR_TR_LOG_HR_SKIPPED_DIRTY_FMT,
    BREAK_EDITOR_TR_LOG_HR_NOT_SCENE_FMT,
    BREAK_EDITOR_TR_LOG_HR_RELOADED_FMT,
    BREAK_EDITOR_TR_LOG_HR_DISABLED_STUCK,
    BREAK_EDITOR_TR_LOG_HR_DISABLED_PATH,
    BREAK_EDITOR_TR_LOG_HR_DISABLED_MOUNT,
    BREAK_EDITOR_TR_LOG_HR_DISABLED_COORD,
    BREAK_EDITOR_TR_LOG_HR_DISABLED_WATCH,
    BREAK_EDITOR_TR_LOG_HR_UNREADABLE_FMT,
    BREAK_EDITOR_TR_LOG_HR_START_FAILED_FMT,
    BREAK_EDITOR_TR_LOG_SR_APPLIED,
    BREAK_EDITOR_TR_LOG_SR_FAILED,
    BREAK_EDITOR_TR_LOG_SR_UNAVAILABLE,
    BREAK_EDITOR_TR_LOG_SR_STUCK,
    BREAK_EDITOR_TR_LOG_SR_MANUAL_ONLY,
    BREAK_EDITOR_TR_LOG_SR_SHUTDOWN_TIMEOUT,
    BREAK_EDITOR_TR_LOG_SR_ROW_UNAVAILABLE,
    BREAK_EDITOR_TR_LOG_SR_ROW_FMT,
    BREAK_EDITOR_TR_LOG_SR_STATE_WATCHING,
    BREAK_EDITOR_TR_LOG_SR_STATE_MANUAL_ONLY,
    BREAK_EDITOR_TR_LOG_SR_STATE_SHUTDOWN_PENDING,
    BREAK_EDITOR_TR_LOG_IMG_APPLIED_FMT,
    BREAK_EDITOR_TR_LOG_IMG_FAILED,
    BREAK_EDITOR_TR_LOG_IMG_SHUTDOWN_TIMEOUT,
    BREAK_EDITOR_TR_PREVIEW_EMPTY,
    BREAK_EDITOR_TR_PREVIEW_LOADING,
    BREAK_EDITOR_TR_PREVIEW_FAILED,
    BREAK_EDITOR_TR_COUNT
} BreakEditorTr;

/* Text for `key` in the current language; never NULL. An out-of-range key
 * yields "?". */
const char *break_editor_tr(BreakEditorTr key);
/* Text for `key` in `lang`; falls back to en-US, then "?". */
const char *break_editor_tr_lang(BreakEditorLang lang, BreakEditorTr key);

/* false (and no change) for an out-of-range language. */
bool break_editor_i18n_set_lang(BreakEditorLang lang);
BreakEditorLang break_editor_i18n_lang(void);

/* Parses BCP 47 / POSIX locale tags: "zh-CN", "zh_CN.UTF-8", "zh",
 * "zh-Hans", "en", "en_US.utf8" (case-insensitive; region, script, codeset
 * and @modifier are ignored past the language). "C" and "POSIX" mean en-US.
 * false for NULL, empty or unsupported languages; *out is then unchanged. */
bool break_editor_i18n_parse_lang(const char *tag, BreakEditorLang *out);
/* First parseable of BREAK_LANG, LC_ALL, LC_MESSAGES, LANG; en-US when none
 * parses. */
BreakEditorLang break_editor_i18n_lang_from_env(void);

/* "en-US" / "zh-CN"; "?" when out of range. */
const char *break_editor_i18n_lang_tag(BreakEditorLang lang);
/* Native name, "English" / "中文"; "?" when out of range. */
const char *break_editor_i18n_lang_name(BreakEditorLang lang);
