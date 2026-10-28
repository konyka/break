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

/* The sheet (NUL-terminated, static). */
const char *break_editor_theme_css(void);
/* Applies the sheet to `win` (myui my_window_set_css_style). false when the
 * sheet does not parse (nothing changes). */
bool break_editor_theme_apply(struct my_window_t *win);
