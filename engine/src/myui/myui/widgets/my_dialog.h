/**
 * @file my_dialog.h
 * @brief Modal dialog window (M13c).
 *
 * A dialog wraps a real my_window with a content area (flex) plus a
 * button strip. Open it through the window manager: the dialog becomes
 * the top window marked modal -- while a modal window is on top, the wm
 * routes POINTER/KEY/IME events only to it (lower windows are blocked)
 * and the window below is painted with a translucent scrim. Clicking a
 * button (or ESC, result MY_DIALOG_CANCEL) closes the dialog and
 * reports the result code through the callback (one-shot).
 */
#ifndef MY_DIALOG_H
#define MY_DIALOG_H

#include "myui/my_window_manager.h"

#define MY_DIALOG_CANCEL (-1)

typedef void (*my_dialog_result_cb)(void* ctx, int32_t result);

/** @brief Modal dialog (composition over my_window). */
typedef struct my_dialog_t {
  const my_allocator_t* allocator;
  my_window_t* win;      /**< owned */
  my_widget_t* content;  /**< inside win's tree; add children here */
  my_widget_t* btn_row;  /**< inside win's tree */
  my_window_manager_t* wm; /**< borrowed (set by my_dialog_open) */
  my_dialog_result_cb on_result;
  void* cb_ctx;
  bool closing;
} my_dialog_t;

/** @brief Create a dialog window (hidden) of logical w x h. */
my_dialog_t* my_dialog_create(const my_allocator_t* allocator, my_pal_t* pal,
                              const char* title, int32_t w, int32_t h);

/** @brief Content container (vertical linear): add app widgets here. */
my_widget_t* my_dialog_content(my_dialog_t* dlg);

/**
 * @brief The dialog's root widget (M24c uniform accessor). The named
 * slots inside it: "dialog_content" (content area) and "dialog_buttons"
 * (button row) — reach them with my_widget_find_descendant().
 */
my_widget_t* my_dialog_widget(my_dialog_t* dlg);

/** @brief Append a button reporting `result` when clicked. */
my_ret_t my_dialog_add_button(my_dialog_t* dlg, const char* text,
                              int32_t result);

/** @brief Open modally over the wm's current top window (centered over
 * it where the port supports window moves; that window gets the scrim).
 * ESC reports MY_DIALOG_CANCEL. */
my_ret_t my_dialog_open(my_dialog_t* dlg, my_window_manager_t* wm,
                        my_dialog_result_cb cb, void* ctx);

/** @brief Close programmatically (reports `result`). */
void my_dialog_close(my_dialog_t* dlg, int32_t result);

/** @brief Destroy a CLOSED dialog (safe right after create for unused
 * dialogs; an open dialog is destroyed via my_dialog_close). */
void my_dialog_destroy(my_dialog_t* dlg);

#endif /* MY_DIALOG_H */
