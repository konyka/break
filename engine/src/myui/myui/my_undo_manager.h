/**
 * @file my_undo_manager.h
 * @brief Window-level shared undo manager (M11b).
 *
 * edit/text_area normally keep a PRIVATE undo stack. A widget switched
 * to shared mode (my_edit_set_undo_shared / my_text_area_set_undo_shared)
 * records its user-edit patches into this manager's single chronological
 * stack instead -- entries are tagged with their owner widget, so undo
 * order is correct across widgets (type in A, type in B, undo twice:
 * B's edit is reverted first, then A's).
 *
 * Routed undo/redo semantics (documented boundary): undo applies the top
 * entry to ITS OWNER widget and switches key focus to that widget first
 * (via the window's dispatcher; no focus change when the widget is not
 * under a my_window root). A tag change breaks the open batch naturally;
 * blur still breaks batches via my_undo_manager_break_batch.
 *
 * Ownership: the manager is created/destroyed by the app; widgets and
 * the window hold BORROWED pointers. Attach to a window with
 * my_window_set_undo_manager so widgets can find it via
 * my_window_undo_manager_of_widget (convenience; widgets are switched to
 * shared mode explicitly).
 */
#ifndef MY_UNDO_MANAGER_H
#define MY_UNDO_MANAGER_H

#include "myui/my_undo_stack.h"

/** @brief Apply one undo/redo op to a widget (edit/text_area impl). */
typedef void (*my_undo_apply_fn)(void* widget, const my_undo_op_t* op);

typedef struct my_undo_manager_t my_undo_manager_t;

my_undo_manager_t* my_undo_manager_create(const my_allocator_t* allocator,
                                          size_t capacity);
void my_undo_manager_destroy(my_undo_manager_t* mgr);

/** @brief Register a shared-mode widget (borrowed refs; called by
 * my_edit_set_undo_shared etc., rarely needed directly). */
my_ret_t my_undo_manager_register(my_undo_manager_t* mgr, void* widget,
                                  my_undo_apply_fn apply);
void my_undo_manager_unregister(my_undo_manager_t* mgr, const void* widget);

/** @brief Record user edits on behalf of a shared-mode widget. */
my_ret_t my_undo_manager_record_insert(my_undo_manager_t* mgr, void* widget,
                                       size_t offset, const char* bytes,
                                       size_t len);
my_ret_t my_undo_manager_record_delete(my_undo_manager_t* mgr, void* widget,
                                       size_t offset, const char* bytes,
                                       size_t len);

/** @brief Close the open batch (widget blur, cursor jumps). */
void my_undo_manager_break_batch(my_undo_manager_t* mgr);

/** @brief Drop ALL entries (whole-window document reset). */
void my_undo_manager_clear(my_undo_manager_t* mgr);

/** @brief Drop only the entries owned by `widget` (its set_text). */
void my_undo_manager_clear_widget(my_undo_manager_t* mgr, const void* widget);

bool my_undo_manager_can_undo(my_undo_manager_t* mgr);
bool my_undo_manager_can_redo(my_undo_manager_t* mgr);

/**
 * @brief Routed undo/redo: pop the top entry, focus its owner (when the
 * owner is under a window root), apply the op to the owner. @return
 * MY_RET_OK, MY_RET_NOT_FOUND when empty, or MY_RET_FAIL when the owner
 * is no longer registered.
 */
my_ret_t my_undo_manager_undo(my_undo_manager_t* mgr);
my_ret_t my_undo_manager_redo(my_undo_manager_t* mgr);

#endif /* MY_UNDO_MANAGER_H */
