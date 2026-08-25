/**
 * @file my_text_area.h
 * @brief Multi-line text editing widget.
 *
 * Model: one UTF-8 byte buffer + a line-start offset cache (darray of
 * byte offsets). Edits rebuild offsets only from the edited line onward
 * (O(bytes after edit)); cursor movement is O(1) amortized on huge
 * documents. Cursor is (row, col) in codepoints; vertical moves keep a
 * goal column. Shift+arrows select, Ctrl+A selects all, Ctrl+C/X/V via
 * the PAL clipboard (newlines preserved). Scrolls to keep the cursor
 * visible. Optional word wrap (M10b): a visual-line cache maps each
 * physical line to width-limited segments; shaping-aware greedy wrapping
 * uses the UAX#14 subset and never splits a shaping cluster. Undo/redo is supported
 * through the private or shared undo manager; line numbers are not part of
 * this widget.
 * Emits "changed" (data = full text). No "activate" (Enter splits lines).
 */
#ifndef MY_TEXT_AREA_H
#define MY_TEXT_AREA_H

#include "mypal/my_pal.h"
#include "myui/my_text_align.h"
#include "myui/my_widget.h"

/** @brief One visual line inside a physical line (word wrap, M10b). */
typedef struct my_visual_line_t {
  size_t phys;     /**< physical line index */
  size_t start_cp; /**< start column (codepoints) within the physical line */
  size_t len_cp;   /**< visual line length in codepoints */
} my_visual_line_t;

/** @brief Multi-line text area (IS-A widget). */
typedef struct my_text_area_t {
  my_widget_t base;
  const my_allocator_t* allocator;
  char* text;               /**< owned UTF-8 buffer */
  size_t text_len;          /**< bytes in use */
  size_t text_cap;          /**< allocated bytes, including trailing NUL */
  my_darray_t* line_offsets;/**< size_t per line start (line 0 = 0) */
  bool wrap;                /**< word wrap on (M10b, default off) */
  bool line_numbers;        /**< show a physical-line number gutter */
  my_darray_t* vlines;      /**< my_visual_line_t* (wrap on only) */
  bool vlines_dirty;        /**< vlines need a rebuild */
  size_t vlines_dirty_from; /**< first physical row requiring rebuild */
  size_t cursor_row;
  size_t cursor_col;        /**< codepoints */
  size_t anchor_row;        /**< selection anchor (== cursor = no sel) */
  size_t anchor_col;
  size_t goal_col;          /**< target col for vertical moves */
  int32_t scroll_x;
  int32_t scroll_y;
  struct my_undo_stack_t* undo; /**< user-edit history (M10a) */
  bool applying_history;          /**< suppresses recording during undo/redo */
  struct my_undo_manager_t* undo_shared; /**< borrowed shared stack (M11b;
                                              NULL = private mode) */
  size_t max_len;           /**< codepoints cap, 0 = unlimited */
  bool readonly;
  char* hint;               /**< owned, shown when empty and unfocused */
  my_widget_t* scroll_bar;     /**< weak; linked scroll_bar (M9c) */
  bool focused;
  bool cursor_visible;
  uint32_t blink_timer_id;
  my_pal_main_loop_t* blink_loop; /**< weak while active */
  uint32_t paste_timer_id;
  my_pal_main_loop_t* paste_loop; /**< weak while async paste is pending */
  my_font_t* font;          /**< borrowed */
  int32_t font_size;
  my_text_align_t align;    /**< horizontal alignment (M11d, default LEFT) */
  char* ime_preedit;        /**< owned: composing text (M13a, NULL=none) */
  int32_t ime_caret;        /**< composing caret in codepoints */
} my_text_area_t;

my_widget_t* my_text_area_create(const my_allocator_t* allocator);

/** @brief Replace the whole text (cursor to end, no "changed" emit). */
my_ret_t my_text_area_set_text(my_widget_t* area, const char* text);
const char* my_text_area_get_text(my_widget_t* area);
my_ret_t my_text_area_set_hint(my_widget_t* area, const char* hint);
my_ret_t my_text_area_set_readonly(my_widget_t* area, bool readonly);
my_ret_t my_text_area_set_max_len(my_widget_t* area, size_t max_codepoints);
/**
 * @brief Switch to the shared undo manager (M11b, borrowed) or back to
 * the private stack (mgr = NULL; the widget's shared entries are
 * DISCARDED then, since a routed undo can no longer find their owner).
 * In shared mode user edits record into mgr and Ctrl+Z/Y route through
 * it (undo applies to the entry's owner widget and focuses it).
 */
my_ret_t my_text_area_set_undo_shared(my_widget_t* area, void* mgr);
/** @brief Font for layout/measuring (borrowed). */
void my_text_area_set_font(my_widget_t* area, my_font_t* font, int32_t size);

/** @brief Line count (from the offset cache). */
size_t my_text_area_line_count(my_widget_t* area);

/** @brief Word wrap on/off (rebuilds visual lines, resets h-scroll). */
my_ret_t my_text_area_set_wrap(my_widget_t* area, bool wrap);

/** @brief Enable or disable the physical-line number gutter. */
my_ret_t my_text_area_set_line_numbers(my_widget_t* area, bool enabled);

/** @brief Whether the physical-line number gutter is enabled. */
bool my_text_area_line_numbers_enabled(const my_widget_t* area);

/** @brief Current content x offset including the optional gutter. */
int32_t my_text_area_content_left(const my_widget_t* area);

/**
 * @brief Horizontal alignment (M11d). LEFT/CENTER/RIGHT shift each
 * visual line within the inner width (measured with the font, or the
 * 8px cell fallback). JUSTIFY only applies in wrap mode: visual lines
 * that are NOT the last segment of their physical line get their word
 * spacing stretched to fill the inner width (the last segment and any
 * line without a word-separating space render LEFT). Without wrap,
 * JUSTIFY behaves as LEFT.
 */
my_ret_t my_text_area_set_align(my_widget_t* area, my_text_align_t align);

/** @brief Visual line count (wrap on; 0 when off). */
size_t my_text_area_visual_line_count(my_widget_t* area);

/** @brief Visual line by index (wrap off = physical line view). */
const my_visual_line_t* my_text_area_visual_line_at(my_widget_t* area,
                                                    size_t index);

/** @brief Visual line index containing (row, col); col_in_v may be NULL. */
size_t my_text_area_visual_line_of_pos(my_widget_t* area, size_t row,
                                       size_t col, size_t* col_in_v);

/** @brief Link a scroll_bar (weak): synced with scroll_y/content height. */
my_ret_t my_text_area_set_scroll_bar(my_widget_t* area, my_widget_t* bar);

#endif /* MY_TEXT_AREA_H */
