/**
 * @file my_edit.c
 * @brief Single-line text input widget.
 */
#include "myui/widgets/my_edit.h"

#include <string.h>

#include "myc/my_str.h"
#include "myr/my_text_layout.h"
#include "myui/my_undo_manager.h"
#include "myui/my_undo_stack.h"
#include "myui/my_window.h"

#define EDIT_PAD_X 4
#define EDIT_PAD_Y 2
#define EDIT_CELL_W 8 /* fallback cell width when no font is set */

/* ---------------- text helpers ---------------- */

static size_t edit_len_bytes(my_edit_t* e) {
  return e->text != NULL ? strlen(e->text) : 0;
}

static size_t utf8_cp_count(const char* s) {
  return my_str_utf8_strlen(s);
}

/** @brief Byte offset one codepoint to the left of pos (0 if at start). */
static size_t cp_prev(const char* s, size_t pos) {
  if (s == NULL) {
    return 0;
  }
  while (pos > 0) {
    pos--;
    if ((s[pos] & 0xC0) != 0x80) {
      return pos;
    }
  }
  return 0;
}

/** @brief Byte offset one codepoint to the right of pos. */
static size_t cp_next(const char* s, size_t pos) {
  size_t len;
  if (s == NULL) {
    return 0;
  }
  len = strlen(s);
  if (pos >= len) {
    return len;
  }
  pos += my_str_utf8_char_len(s + pos);
  return pos > len ? len : pos;
}

static void emit_changed(my_edit_t* e) {
  my_emitter_emit(((my_widget_t*)e)->emitter, "changed",
                  e->text != NULL ? e->text : "");
}

static my_ret_t rebuild_masked(my_edit_t* e) {
  size_t n, i;
  my_mem_free(e->allocator, e->masked);
  e->masked = NULL;
  if (!e->password) {
    return MY_RET_OK;
  }
  n = e->text != NULL ? utf8_cp_count(e->text) : 0;
  e->masked = (char*)my_mem_alloc(e->allocator, n + 1);
  if (e->masked == NULL) {
    return MY_RET_OOM;
  }
  for (i = 0; i < n; i++) {
    e->masked[i] = '*';
  }
  e->masked[n] = '\0';
  return MY_RET_OK;
}

static void edit_set_text_internal(my_edit_t* e, const char* text, bool notify) {
  char* copy = my_strdup(e->allocator, text != NULL ? text : "");
  if (copy == NULL) {
    return;
  }
  /* programmatic replacement: not undoable; the document diverged. In
   * shared mode only THIS widget's entries are dropped (M11b). */
  if (e->undo_shared != NULL) {
    my_undo_manager_clear_widget(e->undo_shared, e);
  } else if (e->undo != NULL) {
    my_undo_stack_clear(e->undo);
  }
  my_mem_free(e->allocator, e->text);
  e->text = copy;
  e->cursor = strlen(copy);
  e->anchor = e->cursor;
  rebuild_masked(e);
  if (notify) {
    emit_changed(e);
  }
  my_widget_invalidate((my_widget_t*)e, NULL);
}

/** @brief Delete [start, end) bytes. */
static void edit_delete_range(my_edit_t* e, size_t start, size_t end) {
  size_t len = edit_len_bytes(e);
  if (start >= end || end > len || e->text == NULL) {
    return;
  }
  memmove(e->text + start, e->text + end, len - end + 1);
  e->cursor = start;
  e->anchor = start;
  rebuild_masked(e);
}

static void edit_insert(my_edit_t* e, const char* bytes, size_t n) {
  size_t len = edit_len_bytes(e);
  size_t cur_count;
  char* p;
  if (e->readonly || n == 0) {
    return;
  }
  cur_count = e->text != NULL ? utf8_cp_count(e->text) : 0;
  if (e->max_len > 0 && cur_count + 1 > e->max_len) {
    return; /* at the limit: drop the input */
  }
  p = (char*)my_mem_alloc(e->allocator, len + n + 1);
  if (p == NULL) {
    return;
  }
  if (e->text != NULL) {
    memcpy(p, e->text, e->cursor);
    memcpy(p + e->cursor + n, e->text + e->cursor, len - e->cursor + 1);
  } else {
    p[n] = '\0';
  }
  memcpy(p + e->cursor, bytes, n);
  my_mem_free(e->allocator, e->text);
  e->text = p;
  e->cursor += n;
  e->anchor = e->cursor;
  rebuild_masked(e);
}

static bool has_selection(my_edit_t* e) {
  return e->cursor != e->anchor;
}

static void edit_after_edit(my_edit_t* e); /* fwd: IME section (M13a) */
static my_ret_t edit_paste_tick(void* ctx);

static void delete_selection(my_edit_t* e) {
  size_t a = e->cursor < e->anchor ? e->cursor : e->anchor;
  size_t b = e->cursor < e->anchor ? e->anchor : e->cursor;
  edit_delete_range(e, a, b);
}

static void user_delete_range(my_edit_t* e, size_t start, size_t end) {
  if (e->readonly) {
    return;
  }
  if (!e->applying_history) {
    if (e->undo_shared != NULL) {
      my_undo_manager_record_delete(e->undo_shared, e, start, e->text + start,
                                    end - start);
    } else if (e->undo != NULL) {
      my_undo_stack_record_delete(e->undo, start, e->text + start, end - start);
    }
  }
  edit_delete_range(e, start, end);
  emit_changed(e);
  edit_after_edit(e);
  my_widget_invalidate((my_widget_t*)e, NULL);
}

static void user_insert(my_edit_t* e, const char* bytes, size_t n) {
  if (e->readonly) {
    return;
  }
  if (has_selection(e)) {
    delete_selection(e);
  }
  if (!e->applying_history) {
    if (e->undo_shared != NULL) {
      my_undo_manager_record_insert(e->undo_shared, e, e->cursor, bytes, n);
    } else if (e->undo != NULL) {
      my_undo_stack_record_insert(e->undo, e->cursor, bytes, n);
    }
  }
  edit_insert(e, bytes, n);
  emit_changed(e);
  edit_after_edit(e);
  my_widget_invalidate((my_widget_t*)e, NULL);
}

static my_ret_t edit_paste(my_edit_t* e) {
  my_pal_t* pal = my_window_pal_of_widget((my_widget_t*)e);
  char* text = NULL;
  char* filtered;
  const char* input;
  size_t input_length;
  size_t output_length = 0;
  size_t current_count;
  if (pal == NULL || e->readonly) return MY_RET_NOT_FOUND;
  {
    my_ret_t result = my_pal_clipboard_get_text_alloc(pal, e->allocator, &text);
    if (result != MY_RET_OK) return result;
  }
  input_length = strlen(text);
  filtered = (char*)my_mem_alloc(e->allocator, input_length + 1);
  if (filtered == NULL) {
    my_mem_free(e->allocator, text);
    return MY_RET_OOM;
  }
  current_count = e->text != NULL ? utf8_cp_count(e->text) : 0;
  if (has_selection(e) && e->text != NULL) {
    size_t start = e->cursor < e->anchor ? e->cursor : e->anchor;
    size_t end = e->cursor < e->anchor ? e->anchor : e->cursor;
    current_count -= utf8_cp_count(e->text + start) -
                     utf8_cp_count(e->text + end);
  }
  input = text;
  while (*input != '\0') {
    size_t codepoint_length = my_str_utf8_char_len(input);
    if (*input != '\n' && *input != '\r') {
      if (e->max_len > 0 && current_count >= e->max_len) break;
      memcpy(filtered + output_length, input, codepoint_length);
      output_length += codepoint_length;
      current_count++;
    }
    input += codepoint_length;
  }
  if (output_length > 0) user_insert(e, filtered, output_length);
  my_mem_free(e->allocator, filtered);
  my_mem_free(e->allocator, text);
  return MY_RET_OK;
}
/** @brief Apply one undo/redo op (shared-mode apply callback, M11b). */
static void edit_apply_undo_op(void* widget, const my_undo_op_t* op) {
  my_edit_t* e = (my_edit_t*)widget;
  e->applying_history = true;
  edit_delete_range(e, op->offset, op->offset + op->remove_len);
  edit_insert(e, op->bytes, op->bytes_len);
  e->cursor = op->offset + op->bytes_len;
  e->anchor = e->cursor;
  e->applying_history = false;
  emit_changed(e);
  my_widget_invalidate((my_widget_t*)e, NULL);
}

/* ---------------- measuring ---------------- */

static my_font_t* edit_eff_font(my_edit_t* e);
static int32_t edit_eff_font_size(my_edit_t* e);

static int32_t text_px(my_edit_t* e, const char* s, size_t n) {
  char buf[128];
  int32_t w = 0;
  if (edit_eff_font(e) == NULL) {
    size_t i, cps = 0;
    for (i = 0; i < n; i++) {
      if ((s[i] & 0xC0) != 0x80) {
        cps++;
      }
    }
    return (int32_t)cps * EDIT_CELL_W;
  }
  if (n >= sizeof(buf)) {
    n = sizeof(buf) - 1;
  }
  memcpy(buf, s, n);
  buf[n] = '\0';
  my_font_measure(edit_eff_font(e), buf, edit_eff_font_size(e), &w, NULL);
  return w;
}

/* ---------------- RTL cursor/click/selection mapping (M12a) ---------- */

/** @brief Layout of the shown text when it needs bidi, else NULL (the
 * plain-LTR fast path keeps the legacy logic untouched). */
static my_text_layout_t* edit_layout_rtl(my_edit_t* e, const char* shown) {
  if (shown != NULL && *shown != '\0' && my_text_layout_may_need_bidi(shown)) {
    return my_text_layout_process(e->allocator, shown);
  }
  return NULL;
}

/** @brief Codepoint index of a byte offset (cursor is at cp boundaries). */
static size_t edit_cp_index_of(const char* s, size_t byte_off) {
  size_t pos = 0, idx = 0;
  while (pos < byte_off && s[pos] != '\0') {
    pos = cp_next(s, pos);
    idx++;
  }
  return idx;
}

/** @brief Effective font: the edit's own, else the window default (M16 —
 * rendering used the vg/window font while measurement used the 8px cell
 * fallback, putting the caret at the wrong x for CJK text). */
static my_font_t* edit_eff_font(my_edit_t* e) {
  if (e->font == NULL) {
    my_font_t* f = NULL;
    my_window_font_of_widget((my_widget_t*)e, &f, NULL);
    return f;
  }
  return e->font;
}
static int32_t edit_eff_font_size(my_edit_t* e) {
  if (e->font == NULL) {
    int32_t fs = 0;
    my_window_font_of_widget((my_widget_t*)e, NULL, &fs);
    if (fs > 0) {
      return fs;
    }
  }
  return e->font_size;
}

/** @brief Byte offset of a codepoint index. */
static size_t edit_byte_of_cp(const char* s, size_t cp_idx) {
  size_t pos = 0;
  while (cp_idx > 0 && s[pos] != '\0') {
    pos = cp_next(s, pos);
    cp_idx--;
  }
  return pos;
}

/** @brief Cursor pixel x: visual mapping for RTL text, prefix width
 * otherwise (bit-identical to the legacy path for LTR). */
static int32_t edit_cursor_px(my_edit_t* e, const char* shown,
                              size_t byte_off) {
  my_text_layout_t* l = edit_layout_rtl(e, shown);
  int32_t x;
  if (l == NULL) {
    return text_px(e, shown, byte_off);
  }
  x = my_text_layout_visual_x(l, edit_eff_font(e), edit_eff_font_size(e),
                              edit_cp_index_of(shown, byte_off));
  my_text_layout_destroy(l);
  return x;
}

/** @brief Cursor byte offset for a click at local x (pixels). */
static size_t locate_cursor(my_edit_t* e, int32_t local_x) {
  const char* s = e->password ? e->masked : e->text;
  size_t pos = 0, len;
  int32_t target = local_x - EDIT_PAD_X + e->scroll_x;
  if (s == NULL || target <= 0) {
    return 0;
  }
  len = strlen(s);
  {
    /* RTL (M12a): hit-test in visual space via the layout mapping */
    my_text_layout_t* l = edit_layout_rtl(e, s);
    if (l != NULL) {
      size_t idx = my_text_layout_logical_at_x(l, edit_eff_font(e), edit_eff_font_size(e),
                                               target);
      my_text_layout_destroy(l);
      return edit_byte_of_cp(s, idx);
    }
  }
  while (pos < len) {
    size_t next = cp_next(s, pos);
    int32_t w0 = text_px(e, s, pos);
    int32_t w1 = text_px(e, s, next);
    if (target < (w0 + w1) / 2) {
      return pos;
    }
    pos = next;
  }
  return len;
}

static void ensure_cursor_visible(my_edit_t* e) {
  const char* s = e->password ? e->masked : e->text;
  my_widget_t* w = (my_widget_t*)e;
  int32_t inner_w = w->rect.w - 2 * EDIT_PAD_X;
  int32_t cx = s != NULL ? edit_cursor_px(e, s, e->cursor) : 0;
  if (inner_w <= 0) {
    return;
  }
  if (cx - e->scroll_x > inner_w) {
    e->scroll_x = cx - inner_w;
  }
  if (cx - e->scroll_x < 0) {
    e->scroll_x = cx;
  }
}

/** @brief Push the cursor's window coordinates to the PAL as the IME
 * candidate anchor (M13a; no-op without a window/IM). */
static void edit_update_ime_spot(my_edit_t* e) {
  my_widget_t* root = (my_widget_t*)e;
  my_window_t* win;
  const char* shown;
  int32_t x, y;
  while (root->parent != NULL) {
    root = root->parent;
  }
  if (!my_str_eq(root->widget_type, "window")) {
    return;
  }
  win = (my_window_t*)root;
  if (win->pal_window == NULL) {
    return;
  }
  shown = e->password ? e->masked : e->text;
  x = EDIT_PAD_X + (shown != NULL ? edit_cursor_px(e, shown, e->cursor) : 0) -
      e->scroll_x;
  y = ((my_widget_t*)e)->rect.h; /* bottom of the line */
  my_widget_local_to_global((my_widget_t*)e, &x, &y);
  my_pal_window_ime_set_spot(win->pal_window, x, y);
  my_pal_window_ime_set_surrounding(
      win->pal_window, e->text != NULL ? e->text : "", (int32_t)e->cursor,
      (int32_t)e->anchor);
}

static void edit_set_ime_enabled(my_edit_t* e, bool enabled) {
  my_widget_t* root = (my_widget_t*)e;
  while (root->parent != NULL) {
    root = root->parent;
  }
  if (my_str_eq(root->widget_type, "window")) {
    my_window_t* win = (my_window_t*)root;
    if (win->pal_window != NULL) {
      my_pal_window_ime_set_enabled(win->pal_window, enabled);
    }
  }
}

/* ---------------- IME events (M13a) ---------------- */

/** @brief Forward declaration-free spot refresh after cursor-affecting
 * operations. */
static void edit_after_edit(my_edit_t* e) {
  ensure_cursor_visible(e);
  edit_update_ime_spot(e);
}

static my_ret_t edit_on_ime_preedit(my_edit_t* e, const my_event_t* ev) {
  char* copy = my_strdup(e->allocator, ev->u.ime.text != NULL
                                             ? ev->u.ime.text
                                             : "");
  if (copy == NULL) {
    return MY_RET_OOM;
  }
  my_mem_free(e->allocator, e->ime_preedit);
  e->ime_preedit = *copy != '\0' ? copy : NULL;
  if (e->ime_preedit == NULL) {
    my_mem_free(e->allocator, copy);
  }
  e->ime_caret = ev->u.ime.cursor;
  my_widget_invalidate((my_widget_t*)e, NULL);
  return MY_RET_OK;
}

static my_ret_t edit_on_ime_commit(my_edit_t* e, const my_event_t* ev) {
  const char* text = ev->u.ime.text;
  my_mem_free(e->allocator, e->ime_preedit);
  e->ime_preedit = NULL;
  if (!e->readonly && text != NULL && *text != '\0') {
    /* a real edit: undo stack + "changed" + MVVM, like typed text */
    user_insert(e, text, strlen(text));
  }
  my_widget_invalidate((my_widget_t*)e, NULL);
  return MY_RET_OK;
}

static my_ret_t edit_on_ime_delete_surrounding(my_edit_t* e,
                                                const my_event_t* ev) {
  size_t before = ev->u.ime.before > 0 ? (size_t)ev->u.ime.before : 0;
  size_t after = ev->u.ime.after > 0 ? (size_t)ev->u.ime.after : 0;
  size_t length = edit_len_bytes(e);
  size_t start = before < e->cursor ? e->cursor - before : 0;
  size_t end = after < length - e->cursor ? e->cursor + after : length;
  if (!e->readonly && start < end) {
    user_delete_range(e, start, end);
  }
  return MY_RET_OK;
}

/* ---------------- events ---------------- */

static my_ret_t edit_on_key(my_edit_t* e, const my_event_t* event) {
  uint32_t key = event->u.key.key;
  uint8_t mods = event->u.key.modifiers;
  bool shift = (mods & MY_KEYMOD_SHIFT) != 0;
  bool ctrl = (mods & MY_KEYMOD_CTRL) != 0;
  size_t len = edit_len_bytes(e);

  if (ctrl && (key == 'z' || key == 'Z')) {
    /* Ctrl+Z undo / Ctrl+Shift+Z redo (M10a); shared mode routes (M11b) */
    if (e->undo_shared != NULL) {
      if ((mods & MY_KEYMOD_SHIFT) != 0) {
        my_undo_manager_redo(e->undo_shared);
      } else {
        my_undo_manager_undo(e->undo_shared);
      }
      return MY_RET_OK;
    }
    {
      my_undo_op_t op;
      my_ret_t r = ((mods & MY_KEYMOD_SHIFT) != 0)
                       ? my_undo_stack_redo(e->undo, &op)
                       : my_undo_stack_undo(e->undo, &op);
      if (r == MY_RET_OK) {
        edit_apply_undo_op(e, &op);
      }
    }
    return MY_RET_OK;
  }
  if (ctrl && (key == 'y' || key == 'Y')) {
    if (e->undo_shared != NULL) {
      my_undo_manager_redo(e->undo_shared);
      return MY_RET_OK;
    }
    {
      my_undo_op_t op;
      if (my_undo_stack_redo(e->undo, &op) == MY_RET_OK) {
        edit_apply_undo_op(e, &op);
      }
    }
    return MY_RET_OK;
  }
  if (ctrl && (key == 'a' || key == 'A')) {
    e->anchor = 0;
    e->cursor = len;
    my_widget_invalidate((my_widget_t*)e, NULL);
    return MY_RET_OK;
  }
  if (ctrl && (key == 'c' || key == 'C' || key == 'x' || key == 'X')) {
    my_pal_t* pal = my_window_pal_of_widget((my_widget_t*)e);
    if (pal != NULL && has_selection(e)) {
      size_t a = e->cursor < e->anchor ? e->cursor : e->anchor;
      size_t b = e->cursor < e->anchor ? e->anchor : e->cursor;
      size_t n = b - a;
      char* buf = (char*)my_mem_alloc(e->allocator, n + 1);
      if (buf != NULL) {
        memcpy(buf, e->text + a, n);
        buf[n] = '\0';
        my_pal_clipboard_set_text(pal, buf);
        my_mem_free(e->allocator, buf);
      }
      if (key == 'x' || key == 'X') {
        user_delete_range(e, a, b); /* cut */
      }
    }
    return MY_RET_OK;
  }
  if (ctrl && (key == 'v' || key == 'V')) {
    if (edit_paste(e) == MY_RET_PENDING && e->paste_timer_id == 0) {
      my_pal_main_loop_t* loop = my_window_loop_of_widget((my_widget_t*)e);
      if (loop != NULL) {
        e->paste_timer_id = my_pal_main_loop_add_timer(loop, edit_paste_tick,
                                                       e, 10);
        e->paste_loop = e->paste_timer_id > 0 ? loop : NULL;
      }
    }
    return MY_RET_OK;
  }
  switch (key) {
    case MY_KEY_LEFT:
    case MY_KEY_RIGHT: {
      /* RTL (M12a): arrows move VISUALLY via the layout boundary map */
      my_text_layout_t* l = edit_layout_rtl(e, e->text);
      size_t next;
      if (l != NULL) {
        size_t idx = edit_cp_index_of(e->text, e->cursor);
        idx = key == MY_KEY_LEFT ? my_text_layout_boundary_left(l, idx)
                                 : my_text_layout_boundary_right(l, idx);
        next = edit_byte_of_cp(e->text, idx);
        my_text_layout_destroy(l);
      } else {
        next = key == MY_KEY_LEFT ? cp_prev(e->text, e->cursor)
                                  : cp_next(e->text, e->cursor);
      }
      e->cursor = next;
      if (!shift) {
        e->anchor = next;
      }
      edit_after_edit(e);
      my_widget_invalidate((my_widget_t*)e, NULL);
      return MY_RET_OK;
    }
    case MY_KEY_HOME: {
      my_text_layout_t* l = edit_layout_rtl(e, e->text);
      e->cursor = 0;
      if (l != NULL) {
        e->cursor =
            edit_byte_of_cp(e->text, my_text_layout_boundary_home(l));
        my_text_layout_destroy(l);
      }
      if (!shift) {
        e->anchor = e->cursor;
      }
      my_widget_invalidate((my_widget_t*)e, NULL);
      return MY_RET_OK;
    }
    case MY_KEY_END: {
      my_text_layout_t* l = edit_layout_rtl(e, e->text);
      e->cursor = len;
      if (l != NULL) {
        e->cursor = edit_byte_of_cp(e->text, my_text_layout_boundary_end(l));
        my_text_layout_destroy(l);
      }
      if (!shift) {
        e->anchor = e->cursor;
      }
      edit_after_edit(e);
      my_widget_invalidate((my_widget_t*)e, NULL);
      return MY_RET_OK;
    }
    case MY_KEY_BACKSPACE:
      if (has_selection(e)) {
        user_delete_range(e, e->cursor < e->anchor ? e->cursor : e->anchor,
                          e->cursor < e->anchor ? e->anchor : e->cursor);
      } else if (e->cursor > 0) {
        user_delete_range(e, cp_prev(e->text, e->cursor), e->cursor);
      }
      return MY_RET_OK;
    case MY_KEY_DELETE:
      if (has_selection(e)) {
        user_delete_range(e, e->cursor < e->anchor ? e->cursor : e->anchor,
                          e->cursor < e->anchor ? e->anchor : e->cursor);
      } else if (e->cursor < len) {
        user_delete_range(e, e->cursor, cp_next(e->text, e->cursor));
      }
      return MY_RET_OK;
    case MY_KEY_RETURN:
      my_emitter_emit(((my_widget_t*)e)->emitter, "activate",
                      e->text != NULL ? e->text : "");
      return MY_RET_OK;
    default:
      break;
  }
  if (key >= 32 && key <= 126 && !ctrl) {
    char ch = (char)key;
    user_insert(e, &ch, 1);
    ensure_cursor_visible(e);
    return MY_RET_OK;
  }
  return MY_RET_FAIL;
}

static my_ret_t edit_on_event(my_widget_t* widget, const my_event_t* event) {
  my_edit_t* e = (my_edit_t*)widget;
  int32_t lx, ly;
  switch (event->type) {
    case MY_EVENT_POINTER_DOWN:
      lx = event->u.pointer.x;
      ly = event->u.pointer.y;
      my_widget_global_to_local(widget, &lx, &ly);
      e->cursor = locate_cursor(e, lx);
      e->anchor = e->cursor;
      ensure_cursor_visible(e);
      edit_update_ime_spot(e);
      my_widget_invalidate(widget, NULL);
      return MY_RET_OK;
    case MY_EVENT_KEY_DOWN:
      if (!e->focused) {
        return MY_RET_FAIL;
      }
      return edit_on_key(e, event);
    case MY_EVENT_IME_PREEDIT:
      return edit_on_ime_preedit(e, event);
    case MY_EVENT_IME_COMMIT:
      return edit_on_ime_commit(e, event);
    case MY_EVENT_IME_DELETE_SURROUNDING:
      return edit_on_ime_delete_surrounding(e, event);
    default:
      return MY_RET_FAIL;
  }
}

static my_ret_t edit_paste_tick(void* ctx) {
  my_edit_t* e = (my_edit_t*)ctx;
  if (e->focused && edit_paste(e) == MY_RET_PENDING) return MY_RET_OK;
  e->paste_timer_id = 0;
  e->paste_loop = NULL;
  return MY_RET_FAIL;
}

static my_ret_t edit_blink_tick(void* ctx) {
  my_edit_t* e = (my_edit_t*)ctx;
  e->cursor_visible = !e->cursor_visible;
  my_widget_invalidate((my_widget_t*)e, NULL);
  return MY_RET_OK; /* repeat */
}

static void edit_on_focus(void* ctx, const char* event, void* data) {
  my_edit_t* e = (my_edit_t*)ctx;
  my_pal_main_loop_t* loop;
  (void)event;
  (void)data;
  e->focused = true;
  e->cursor_visible = true;
  edit_set_ime_enabled(e, true);
  edit_update_ime_spot(e);
  loop = my_window_loop_of_widget((my_widget_t*)e);
  if (loop != NULL && e->blink_timer_id == 0) {
    e->blink_timer_id = my_pal_main_loop_add_timer(loop, edit_blink_tick, e,
                                                   500);
    e->blink_loop = e->blink_timer_id > 0 ? loop : NULL;
  }
  my_widget_invalidate((my_widget_t*)e, NULL);
}

static void edit_on_blur(void* ctx, const char* event, void* data) {
  my_edit_t* e = (my_edit_t*)ctx;
  (void)event;
  (void)data;
  if (e->undo_shared != NULL) {
    my_undo_manager_break_batch(e->undo_shared);
  } else {
    my_undo_stack_break_batch(e->undo);
  }
  e->focused = false;
  edit_set_ime_enabled(e, false);
  if (e->ime_preedit != NULL) {
    my_mem_free(e->allocator, e->ime_preedit);
    e->ime_preedit = NULL;
  }
  e->cursor_visible = true; /* hidden anyway when unfocused */
  if (e->blink_timer_id > 0 && e->blink_loop != NULL) {
    my_pal_main_loop_remove_timer(e->blink_loop, e->blink_timer_id);
    e->blink_timer_id = 0;
    e->blink_loop = NULL;
  }
  if (e->paste_timer_id > 0 && e->paste_loop != NULL) {
    my_pal_main_loop_remove_timer(e->paste_loop, e->paste_timer_id);
    e->paste_timer_id = 0;
    e->paste_loop = NULL;
  }
  my_widget_invalidate((my_widget_t*)e, NULL);
}

/* ---------------- painting ---------------- */

static void edit_on_paint(my_widget_t* widget, my_vgcanvas_t* vg) {
  my_edit_t* e = (my_edit_t*)widget;
  /* M24b: deliberately NOT my_widget_current_state(): the focused edit
   * borrows the HOVER style slot (documented in my_edit.h); pointer hover
   * plays no role here. */
  my_widget_state_t state =
      widget->enable ? (e->focused ? MY_STATE_HOVER : MY_STATE_NORMAL)
                     : MY_STATE_DISABLED;
  uint32_t bg = my_widget_style_get_color(widget, state, MY_STYLE_BG_COLOR,
                                          0xFFFFFFFFu);
  uint32_t border = my_widget_style_get_color(widget, state, MY_STYLE_BORDER_COLOR,
                                              0x9E9E9EFFu);
  uint32_t fg = my_widget_style_get_color(widget, state, MY_STYLE_FG_COLOR,
                                          0x212121FFu);
  const char* shown = e->password ? e->masked : e->text;
  int32_t text_y;

  my_vgcanvas_set_fill_color(vg, my_color_from_rgba32(bg));
  my_vgcanvas_fill_rect(vg, &(my_rectf_t){0, 0, (float)widget->rect.w,
                                          (float)widget->rect.h});
  my_vgcanvas_set_stroke_color(vg, my_color_from_rgba32(border));
  my_vgcanvas_set_line_width(vg, 1);
  my_vgcanvas_stroke_rect(vg, &(my_rectf_t){0, 0, (float)widget->rect.w,
                                            (float)widget->rect.h});

  my_vgcanvas_save(vg);
  my_vgcanvas_clip_rect(vg, &(my_rectf_t){EDIT_PAD_X, 0,
                                          (float)(widget->rect.w - 2 * EDIT_PAD_X),
                                          (float)widget->rect.h});
  text_y = (widget->rect.h - edit_eff_font_size(e)) / 2;

  if (shown == NULL || *shown == '\0') {
    if (e->hint != NULL && !e->focused) {
      my_vgcanvas_set_fill_color(vg, my_color_rgb(150, 150, 150));
      my_vgcanvas_draw_text(vg, e->hint, EDIT_PAD_X, (float)text_y);
    }
  } else {
    /* selection highlight */
    if (has_selection(e)) {
      size_t a = e->cursor < e->anchor ? e->cursor : e->anchor;
      size_t b = e->cursor < e->anchor ? e->anchor : e->cursor;
      my_text_layout_t* l = edit_layout_rtl(e, shown);
      my_vgcanvas_set_fill_color(vg, my_color_rgb(130, 170, 230));
      if (l != NULL) {
        /* RTL (M12a): a contiguous logical selection may show as
         * several visual segments at run boundaries */
        my_rectf_t rects[4];
        size_t n = my_text_layout_visual_rects(
            l, edit_eff_font(e), edit_eff_font_size(e), edit_cp_index_of(shown, a),
            edit_cp_index_of(shown, b), rects, 4);
        size_t k;
        for (k = 0; k < n && k < 4; k++) {
          my_vgcanvas_fill_rect(
              vg, &(my_rectf_t){(float)(EDIT_PAD_X + (int32_t)rects[k].x -
                                        e->scroll_x),
                                EDIT_PAD_Y, rects[k].w,
                                (float)(widget->rect.h - 2 * EDIT_PAD_Y)});
        }
        my_text_layout_destroy(l);
      } else {
        int32_t x0 = text_px(e, shown, a) - e->scroll_x;
        int32_t x1 = text_px(e, shown, b) - e->scroll_x;
        my_vgcanvas_fill_rect(vg, &(my_rectf_t){(float)(EDIT_PAD_X + x0),
                                                EDIT_PAD_Y, (float)(x1 - x0),
                                                (float)(widget->rect.h - 2 * EDIT_PAD_Y)});
      }
    }
    my_vgcanvas_set_fill_color(vg, my_color_from_rgba32(fg));
    my_vgcanvas_draw_text(vg, shown, (float)(EDIT_PAD_X - e->scroll_x),
                          (float)text_y);
    /* IME composing text (M13a): underlined at the cursor, NOT part of
     * the document (no undo, no "changed") */
    if (e->ime_preedit != NULL) {
      int32_t cx = edit_cursor_px(e, shown, e->cursor);
      int32_t pw = 0;
      my_vgcanvas_draw_text(vg, e->ime_preedit,
                            (float)(EDIT_PAD_X + cx - e->scroll_x),
                            (float)text_y);
      if (my_vgcanvas_measure_text(vg, e->ime_preedit, &pw, NULL) ==
              MY_RET_OK &&
          pw > 0) {
        my_vgcanvas_fill_rect(
            vg, &(my_rectf_t){(float)(EDIT_PAD_X + cx - e->scroll_x),
                              (float)(text_y + edit_eff_font_size(e) + 1), (float)pw,
                              1.0f});
      }
    }
  }

  /* cursor (blinks at 500ms when focused); during IME composition it sits
   * at the caret inside the preedit text, not at the document position */
  if (e->focused && e->cursor_visible) {
    int32_t cx = shown != NULL ? edit_cursor_px(e, shown, e->cursor) : 0;
    if (e->ime_preedit != NULL && e->ime_caret > 0) {
      cx += text_px(e, e->ime_preedit,
                    edit_byte_of_cp(e->ime_preedit, (size_t)e->ime_caret));
    }
    my_vgcanvas_set_fill_color(vg, my_color_from_rgba32(fg));
    my_vgcanvas_fill_rect(vg, &(my_rectf_t){(float)(EDIT_PAD_X + cx - e->scroll_x),
                                            EDIT_PAD_Y + 1, 1,
                                            (float)(widget->rect.h - 2 * EDIT_PAD_Y - 2)});
  }
  my_vgcanvas_restore(vg);
}

static const my_widget_vtable_t s_edit_vtable = {edit_on_paint, edit_on_event,
                                                 NULL, NULL};

static void edit_destroy_chain(my_object_t* obj) {
  my_edit_t* e = (my_edit_t*)obj;
  if (e->blink_timer_id > 0 && e->blink_loop != NULL) {
    my_pal_main_loop_remove_timer(e->blink_loop, e->blink_timer_id);
  }
  if (e->paste_timer_id > 0 && e->paste_loop != NULL) {
    my_pal_main_loop_remove_timer(e->paste_loop, e->paste_timer_id);
  }
  if (e->undo_shared != NULL) {
    my_undo_manager_unregister(e->undo_shared, e);
  }
  my_undo_stack_destroy(e->undo);
  my_mem_free(e->allocator, e->ime_preedit);
  my_mem_free(e->allocator, e->text);
  my_mem_free(e->allocator, e->masked);
  my_mem_free(e->allocator, e->hint);
  my_widget_destroy((my_widget_t*)e);
  my_object_destroy(obj);
}

my_widget_t* my_edit_create(const my_allocator_t* allocator) {
  my_edit_t* e = (my_edit_t*)my_mem_calloc(allocator, 1, sizeof(my_edit_t));
  if (e == NULL) {
    return NULL;
  }
  if (my_widget_init((my_widget_t*)e, allocator, &s_edit_vtable, "edit") !=
      MY_RET_OK) {
    my_mem_free(allocator, e);
    return NULL;
  }
  ((my_object_t*)e)->destroy = edit_destroy_chain;
  e->allocator = allocator;
  e->font_size = 16;
  e->cursor_visible = true;
  e->undo = my_undo_stack_create(allocator, 0);
  if (e->undo == NULL) {
    my_object_unref((my_object_t*)e);
    return NULL;
  }
  ((my_widget_t*)e)->focusable = true;
  ((my_widget_t*)e)->widget_type = "edit";
  my_widget_on((my_widget_t*)e, "focus", edit_on_focus, e);
  my_widget_on((my_widget_t*)e, "blur", edit_on_blur, e);
  return (my_widget_t*)e;
}

my_ret_t my_edit_set_text(my_widget_t* edit, const char* text) {
  if (edit == NULL) {
    return MY_RET_INVALID_PARAMS;
  }
  edit_set_text_internal((my_edit_t*)edit, text, false);
  return MY_RET_OK;
}

const char* my_edit_get_text(my_widget_t* edit) {
  my_edit_t* e = (my_edit_t*)edit;
  return edit == NULL || e->text == NULL ? "" : e->text;
}

my_ret_t my_edit_set_undo_shared(my_widget_t* edit, void* mgr) {
  my_edit_t* e = (my_edit_t*)edit;
  if (edit == NULL) {
    return MY_RET_INVALID_PARAMS;
  }
  if (e->undo_shared != NULL) {
    /* leaving shared mode discards the widget's shared history
     * (documented): entries whose owner is unregistered cannot be
     * applied by a routed undo */
    my_undo_manager_clear_widget(e->undo_shared, e);
    my_undo_manager_unregister(e->undo_shared, e);
  }
  e->undo_shared = (my_undo_manager_t*)mgr;
  if (e->undo_shared != NULL) {
    return my_undo_manager_register(e->undo_shared, e, edit_apply_undo_op);
  }
  return MY_RET_OK;
}

my_ret_t my_edit_set_hint(my_widget_t* edit, const char* hint) {
  my_edit_t* e = (my_edit_t*)edit;
  char* copy;
  if (edit == NULL) {
    return MY_RET_INVALID_PARAMS;
  }
  copy = my_strdup(e->allocator, hint);
  if (hint != NULL && copy == NULL) {
    return MY_RET_OOM;
  }
  my_mem_free(e->allocator, e->hint);
  e->hint = copy;
  my_widget_invalidate(edit, NULL);
  return MY_RET_OK;
}

my_ret_t my_edit_set_readonly(my_widget_t* edit, bool readonly) {
  if (edit == NULL) {
    return MY_RET_INVALID_PARAMS;
  }
  ((my_edit_t*)edit)->readonly = readonly;
  return MY_RET_OK;
}

my_ret_t my_edit_set_password(my_widget_t* edit, bool password) {
  my_edit_t* e = (my_edit_t*)edit;
  if (edit == NULL) {
    return MY_RET_INVALID_PARAMS;
  }
  e->password = password;
  rebuild_masked(e);
  my_widget_invalidate(edit, NULL);
  return MY_RET_OK;
}

my_ret_t my_edit_set_max_len(my_widget_t* edit, size_t max_codepoints) {
  if (edit == NULL) {
    return MY_RET_INVALID_PARAMS;
  }
  ((my_edit_t*)edit)->max_len = max_codepoints;
  return MY_RET_OK;
}

void my_edit_set_font(my_widget_t* edit, my_font_t* font, int32_t size) {
  my_edit_t* e = (my_edit_t*)edit;
  if (edit != NULL) {
    if (font != NULL) {
      e->font = font;
    }
    if (size > 0) {
      e->font_size = size;
    }
  }
}

void my_edit_get_selection(my_widget_t* edit, size_t* start, size_t* end) {
  my_edit_t* e = (my_edit_t*)edit;
  size_t a, b;
  if (edit == NULL) {
    return;
  }
  a = e->cursor < e->anchor ? e->cursor : e->anchor;
  b = e->cursor < e->anchor ? e->anchor : e->cursor;
  if (start != NULL) {
    *start = a;
  }
  if (end != NULL) {
    *end = b;
  }
}
