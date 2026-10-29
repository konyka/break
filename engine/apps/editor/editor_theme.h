#pragma once

/* Editor look: JetBrains "New UI" dark (CLion 2024+ style), applied as a
 * myui CSS sheet (design docs/superpowers/specs/
 * 2026-10-28-editor-text-and-clion-theme-design.md). Colours approximate the
 * public Int UI dark palette; no JetBrains assets are used. */

#include <core/types.h>

struct my_window_t;

/* Palette (0xRRGGBBAA), shared by the sheet and by widgets that paint
 * themselves (viewport surround, preview area). */
#define BREAK_EDITOR_THEME_BG_WINDOW 0x2B2D30FFu  /* tool windows, toolbar */
#define BREAK_EDITOR_THEME_BG_CONTENT 0x1E1F22FFu /* lists, consoles, inputs */
#define BREAK_EDITOR_THEME_BORDER 0x393B40FFu
#define BREAK_EDITOR_THEME_BORDER_STRONG 0x4E5157FFu
#define BREAK_EDITOR_THEME_TEXT 0xDFE1E5FFu
#define BREAK_EDITOR_THEME_TEXT_SECONDARY 0x9DA0A8FFu
#define BREAK_EDITOR_THEME_ACCENT 0x3574F0FFu
#define BREAK_EDITOR_THEME_ACCENT_HOVER 0x4682FAFFu
#define BREAK_EDITOR_THEME_ACCENT_PRESSED 0x2E5FCCFFu
#define BREAK_EDITOR_THEME_HOVER 0x393B40FFu
#define BREAK_EDITOR_THEME_PRESSED 0x43454AFFu
#define BREAK_EDITOR_THEME_SELECTION 0x2E436EFFu

/* Light palette (JetBrains New UI light). */
#define BREAK_EDITOR_THEME_LIGHT_BG_WINDOW 0xF7F8FAFFu
#define BREAK_EDITOR_THEME_LIGHT_BG_CONTENT 0xFFFFFFFFu
#define BREAK_EDITOR_THEME_LIGHT_TEXT 0x1F1F1FFFu
#define BREAK_EDITOR_THEME_LIGHT_SELECTION 0xD4E2FFFFu

/* The sheet (NUL-terminated, static). */
const char *break_editor_theme_css(void);
/* Applies the sheet to `win` (myui my_window_set_css_style). false when the
 * sheet does not parse (nothing changes). */
bool break_editor_theme_apply(struct my_window_t *win);

/* Applies the dark or light sheet; on success also records the mode used by
 * break_editor_theme_content_bg(). On a parse failure nothing changes. */
bool break_editor_theme_apply_mode(struct my_window_t *win, bool light);
bool break_editor_theme_is_light(void);
/* Content-surface colour of the current mode, for widgets that paint
 * themselves (viewport surround, image preview). */
uint32_t break_editor_theme_content_bg(void);
