/**
 * @file my_edit.h
 * @brief Single-line text input widget.
 *
 * Features: UTF-8 text (cursor/selection in codepoints), hint
 * placeholder, readonly, max_len (codepoints), password masking,
 * keyboard navigation (Left/Right/Home/End), click-to-locate, selection
 * (Shift+arrows, Ctrl+A), Backspace/Delete, horizontal scrolling.
 * Emits "changed" (event data = new text) and "activate" (Enter).
 * Focused state uses the style's HOVER slot for the border (documented
 * in docs/architecture.md). Cursor blinking: TODO (steady cursor).
 */
#ifndef MY_EDIT_H
#define MY_EDIT_H

#include "mypal/my_pal.h"
#include "myui/my_widget.h"

/** @brief Single-line text edit (IS-A widget). */
typedef struct my_edit_t {
  my_widget_t base;
  const my_allocator_t* allocator;
  char* text;          /**< owned, UTF-8 */
  char* masked;        /**< owned, password cache ("*" x codepoints) */
  char* hint;          /**< owned */
  size_t cursor;       /**< byte offset at a codepoint boundary */
  size_t anchor;       /**< selection anchor (cursor != anchor = selection) */
  int32_t scroll_x;    /**< horizontal scroll offset in pixels */
  size_t max_len;      /**< max codepoints, 0 = unlimited */
  struct my_undo_stack_t* undo; /**< user-edit history (M10a) */
  bool applying_history;          /**< suppresses recording during undo/redo */
  struct my_undo_manager_t* undo_shared; /**< borrowed shared stack (M11b;
                                              NULL = private mode) */
  char* ime_preedit;      /**< owned: composing text (M13a, NULL=none) */
  int32_t ime_caret;      /**< composing caret in codepoints */
  bool readonly;
  bool password;
  bool focused;
  bool cursor_visible; /**< blink state (M8c) */
  uint32_t blink_timer_id;
  my_pal_main_loop_t* blink_loop; /**< weak while timer active */
  uint32_t paste_timer_id;
  my_pal_main_loop_t* paste_loop; /**< weak while async paste is pending */
  my_font_t* font;     /**< borrowed; for click-to-locate measuring */
  int32_t font_size;
} my_edit_t;

my_widget_t* my_edit_create(const my_allocator_t* allocator);

/** @brief Set text (cursor moves to end, selection cleared). No "changed". */
my_ret_t my_edit_set_text(my_widget_t* edit, const char* text);
/** @brief Current text ("" when empty). */
const char* my_edit_get_text(my_widget_t* edit);
my_ret_t my_edit_set_hint(my_widget_t* edit, const char* hint);
my_ret_t my_edit_set_readonly(my_widget_t* edit, bool readonly);
my_ret_t my_edit_set_password(my_widget_t* edit, bool password);
my_ret_t my_edit_set_max_len(my_widget_t* edit, size_t max_codepoints);
/** @brief Font used to measure for click-to-locate (borrowed). */
void my_edit_set_font(my_widget_t* edit, my_font_t* font, int32_t size);

/**
 * @brief Switch to the shared undo manager (M11b, borrowed) or back to
 * the private stack (mgr = NULL; the widget's shared entries are
 * DISCARDED then, since a routed undo can no longer find their owner).
 * In shared mode user edits record into mgr and Ctrl+Z/Y route through
 * it (undo applies to the entry's owner widget and focuses it).
 */
my_ret_t my_edit_set_undo_shared(my_widget_t* edit, void* mgr);

/** @brief Selected range as byte offsets (ordered). No selection: a == b. */
void my_edit_get_selection(my_widget_t* edit, size_t* start, size_t* end);

#endif /* MY_EDIT_H */
