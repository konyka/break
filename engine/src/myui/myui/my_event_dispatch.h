/**
 * @file my_event_dispatch.h
 * @brief Dispatch PAL events into a widget tree.
 *
 * Rules:
 *  - POINTER_DOWN: hit_test from the root; the hit widget gets the event
 *    first (vtable on_event, then its "pointer_down" emitter listeners);
 *    returning MY_RET_OK consumes it, otherwise it bubbles to parents.
 *    The hit widget is grabbed (drag semantics) and, if it or an ancestor
 *    is focusable, becomes the key focus.
 *  - POINTER_MOVE/UP: delivered to the grabbed widget while a grab is
 *    active (otherwise to the hit widget); UP releases the grab.
 *  - KEY_DOWN/UP: delivered to the focused widget (bubbles to parents).
 *    If a handler detaches itself or an ancestor, propagation stops before
 *    entering the detached branch; temporary refs keep the active callback
 *    safe during that mutation.
 *  - Hover (M14a): the dispatcher tracks the widget under the pointer
 *    (grab wins while dragging; UP re-hits); on change it flips the
 *    widget->hovered flag and emits "hover_leave"/"hover_enter". The
 *    flag drives the MY_STATE_HOVER style slot.
 *  - Emitter listener names mirror event types: "pointer_down",
 *    "pointer_move", "pointer_up", "key_down", "key_up",
 *    "hover_enter", "hover_leave".
 * grabbed/focused/hovered are weak refs. The window root's removal hook clears
 * any reference into a subtree before remove_child() detaches it; clearing
 * focus emits blur (so IME state is released) and clearing hover restores the
 * default cursor.
 */
#ifndef MY_EVENT_DISPATCH_H
#define MY_EVENT_DISPATCH_H

#include "myui/my_widget.h"

/** @brief Event dispatcher bound to one widget tree (window). */
typedef struct my_event_dispatcher_t {
  my_widget_t* root;    /**< weak */
  my_widget_t* grabbed; /**< weak: pointer grab target */
  my_widget_t* focused; /**< weak: key focus */
  my_widget_t* hovered; /**< weak: hover target (M14a); its widget->hovered
                         * flag is set and hover_enter/leave are emitted */
} my_event_dispatcher_t;

/** @brief Initialize a dispatcher for the given root widget. */
void my_event_dispatcher_init(my_event_dispatcher_t* dispatcher,
                              my_widget_t* root);

/**
 * @brief Dispatch one event. @return true when consumed by some widget.
 * Only POINTER_x and KEY_x events are handled; others return false.
 */
bool my_event_dispatch(my_event_dispatcher_t* dispatcher, const my_event_t* event);

/**
 * @brief Forget all weak references (grab/focus) pointing at widget or
 * any of its descendants. Called when a subtree leaves the tree.
 */
void my_event_dispatcher_forget(my_event_dispatcher_t* dispatcher,
                                my_widget_t* widget);

/**
 * @brief Switch the key focus programmatically (M11b), emitting
 * "blur"/"focus" like a pointer-driven focus change. NULL = blur all.
 */
void my_event_dispatcher_set_focus(my_event_dispatcher_t* dispatcher,
                                   my_widget_t* widget);

#endif /* MY_EVENT_DISPATCH_H */
