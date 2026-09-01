/**
 * @file my_event_dispatch.c
 * @brief Dispatch PAL events into a widget tree.
 */
#include "myui/my_event_dispatch.h"

#include "myc/my_str.h"
#include "myui/my_window.h"

/**
 * @brief Cursor shape for a hover target (M21a): nearest ancestor-or-self
 * that is a text input (edit/text_area) -> TEXT; else the nearest
 * focusable -> HAND (buttons, menus, links, focusable canvases); else
 * ARROW. Single walk up the parent chain, first rule hit wins.
 */
static my_cursor_t hover_cursor_of(my_widget_t* target) {
  my_widget_t* w = target;
  while (w != NULL) {
    if (my_str_eq(w->widget_type, "edit") ||
        my_str_eq(w->widget_type, "text_area")) {
      return MY_CURSOR_TEXT;
    }
    if (w->focusable) {
      return MY_CURSOR_HAND;
    }
    w = w->parent;
  }
  return MY_CURSOR_ARROW;
}

/** @brief Apply the hover-driven cursor to the window owning the
 * dispatcher's root (M21a). Silent no-op for window-less trees (unit
 * tests) and for ports without cursor control (NULL vtable slot). */
static void hover_cursor_apply(my_event_dispatcher_t* d,
                               my_widget_t* target) {
  my_widget_t* root = d->root;
  my_window_t* win;
  my_cursor_t cur;
  if (root == NULL || !my_str_eq(root->widget_type, "window")) {
    return;
  }
  win = (my_window_t*)root;
  if (win->pal_window == NULL) {
    return;
  }
  cur = hover_cursor_of(target);
  if (cur != win->cursor) {
    win->cursor = cur;
    my_pal_window_set_cursor(win->pal_window, cur);
  }
}

void my_event_dispatcher_init(my_event_dispatcher_t* dispatcher,
                              my_widget_t* root) {
  if (dispatcher != NULL) {
    dispatcher->root = root;
    dispatcher->grabbed = NULL;
    dispatcher->focused = NULL;
    dispatcher->hovered = NULL;
  }
}

static bool is_self_or_descendant(my_widget_t* w, my_widget_t* ancestor);

static const char* event_name_of(my_event_type_t type) {
  switch (type) {
    case MY_EVENT_POINTER_DOWN:
      return "pointer_down";
    case MY_EVENT_POINTER_MOVE:
      return "pointer_move";
    case MY_EVENT_POINTER_UP:
      return "pointer_up";
    case MY_EVENT_POINTER_WHEEL:
      return "pointer_wheel";
    case MY_EVENT_KEY_DOWN:
      return "key_down";
    case MY_EVENT_KEY_UP:
      return "key_up";
    default:
      return "unknown";
  }
}

/**
 * @brief Deliver to target, then bubble to parents until consumed.
 *
 * A handler may remove or destroy the target widget (e.g. a menu dismisses
 * itself on pointer events). We hold a temporary ref so the widget stays
 * addressable for the generic emitter call, but only emit if the widget is
 * still attached to the dispatcher's tree.
 */
static bool deliver(my_event_dispatcher_t* d, my_widget_t* target,
                    const my_event_t* event) {
  bool consumed = false;
  my_widget_t* w = my_widget_ref(target);
  while (w != NULL) {
    my_widget_t* parent = w->parent != NULL ? my_widget_ref(w->parent) : NULL;
    if (w->enable) {
      if (w->vtable != NULL && w->vtable->on_event != NULL &&
          w->vtable->on_event(w, event) == MY_RET_OK) {
        consumed = true;
      }
      /* A consumed handler may have removed or destroyed the widget (e.g. a
       * menu dismisses itself). Don't try to emit on a detached widget; just
       * drop our temporary refs and stop propagation. */
      if (consumed) {
        my_widget_unref(w);
        my_widget_unref(parent);
        return true;
      }
      /* A handler that detached itself must not continue bubbling through
       * an otherwise still-attached parent. */
      if (!is_self_or_descendant(w, d->root)) {
        my_widget_unref(w);
        my_widget_unref(parent);
        return false;
      }
      /* Not consumed: the widget is expected to remain in the tree. Emit the
       * convenience event mirroring the PAL event type. */
      my_emitter_emit(w->emitter, event_name_of(event->type), (void*)event);
    }
    my_widget_unref(w);
    if (parent == NULL || !is_self_or_descendant(parent, d->root)) {
      my_widget_unref(parent);
      return false;
    }
    w = parent;
  }
  return false;
}

/** @brief Depth-first traversal: next focusable (visible+enable) after w,
 * wrapping around the tree. direction: +1 forward, -1 backward. */
static my_widget_t* focus_step(my_widget_t* root, my_widget_t* current,
                               int direction) {
  my_widget_t* found = NULL;
  my_widget_t* first = NULL;
  my_widget_t* prev = NULL;
  if (root == NULL) {
    return NULL;
  }
  /* collect-walk: preorder via recursion-free loop using child index state
   * kept on the stack of parent pointers (trees are small) */
  {
    /* simple recursive walk implemented iteratively with an explicit
     * state: we walk using parent/child links only */
    size_t i;
    my_widget_t* order[256]; /* cap: first 256 focusables (documented) */
    size_t count = 0;
    /* stack-based preorder */
    my_widget_t* stack[256];
    size_t sp = 0;
    stack[sp++] = root;
    while (sp > 0 && count < 256) {
      my_widget_t* n = stack[--sp];
      size_t c = my_widget_child_count(n);
      if (n->visible && n->enable && n->focusable) {
        order[count++] = n;
      }
      /* push children in reverse so pop order matches tree order */
      i = c;
      while (i > 0 && sp < 256) {
        stack[sp++] = my_widget_get_child(n, i - 1);
        i--;
      }
    }
    for (i = 0; i < count; i++) {
      if (first == NULL) {
        first = order[i];
      }
      if (order[i] == current) {
        if (direction > 0) {
          found = i + 1 < count ? order[i + 1] : NULL;
        } else {
          found = prev;
        }
        break;
      }
      prev = order[i];
    }
    if (found == NULL) {
      /* wrap: forward -> first, backward -> last */
      if (count > 0) {
        found = direction > 0 ? first : order[count - 1];
      }
    }
  }
  return found;
}

/** @brief Nearest focusable widget at or above w (NULL when none). */
static my_widget_t* nearest_focusable(my_widget_t* w) {
  while (w != NULL && !w->focusable) {
    w = w->parent;
  }
  return w;
}

/** @brief Switch the hover target (M14a): clears the old widget's
 * `hovered` flag (emitting "hover_leave"), sets the new one (emitting
 * "hover_enter"), invalidating both so the MY_STATE_HOVER style slot
 * takes effect. While a grab is active the grabbed widget keeps hover. */
static void hover_update(my_event_dispatcher_t* d, my_widget_t* target) {
  my_widget_t* old = d->hovered;
  if (old == target) {
    return;
  }
  /* Keep both widgets alive across the emits: a hover_leave/hover_enter
   * listener may destroy either widget (deliver() uses the same pattern). */
  my_widget_ref(target);
  if (old != NULL) {
    my_widget_ref(old);
    old->hovered = false;
    my_widget_invalidate(old, NULL);
    my_emitter_emit(old->emitter, "hover_leave", NULL);
    my_widget_unref(old);
  }
  d->hovered = target;
  if (target != NULL) {
    target->hovered = true;
    my_widget_invalidate(target, NULL);
    my_emitter_emit(target->emitter, "hover_enter", NULL);
  }
  hover_cursor_apply(d, target); /* M21a: cursor follows the hover class */
  my_widget_unref(target);
}

/** @brief Switch key focus, emitting "blur"/"focus" on the widgets. */
static void set_focus(my_event_dispatcher_t* d, my_widget_t* widget) {
  my_widget_t* old = d->focused;
  if (old == widget) {
    return;
  }
  if (old != NULL) {
    my_widget_ref(old); /* a blur listener may destroy the old widget */
    my_emitter_emit(old->emitter, "blur", NULL);
    my_widget_unref(old);
    if (d->focused != old && d->focused != NULL) {
      return; /* the blur handler moved focus elsewhere: keep its choice */
    }
    /* d->focused == NULL also covers old leaving the tree mid-emit
     * (forget() cleared it): the caller's choice still applies. */
  }
  d->focused = widget;
  if (widget != NULL) {
    my_widget_ref(widget); /* a focus listener may destroy the widget */
    my_emitter_emit(widget->emitter, "focus", NULL);
    my_widget_unref(widget);
  }
}

void my_event_dispatcher_set_focus(my_event_dispatcher_t* dispatcher,
                                   my_widget_t* widget) {
  if (dispatcher != NULL) {
    set_focus(dispatcher, nearest_focusable(widget));
  }
}

bool my_event_dispatch(my_event_dispatcher_t* dispatcher,
                       const my_event_t* event) {
  my_widget_t* target;
  if (dispatcher == NULL || event == NULL || dispatcher->root == NULL) {
    return false;
  }

  switch (event->type) {
    case MY_EVENT_POINTER_DOWN:
      target = my_widget_hit_test(dispatcher->root, event->u.pointer.x,
                                  event->u.pointer.y);
      dispatcher->grabbed = target;
      hover_update(dispatcher, target);
      if (target != NULL) {
        set_focus(dispatcher, nearest_focusable(target));
        return deliver(dispatcher, target, event);
      }
      set_focus(dispatcher, NULL); /* click on empty space: blur */
      return false;
    case MY_EVENT_POINTER_WHEEL:
      target = my_widget_hit_test(dispatcher->root, event->u.pointer.x,
                                  event->u.pointer.y);
      return target != NULL ? deliver(dispatcher, target, event) : false;
    case MY_EVENT_POINTER_MOVE:
      target = dispatcher->grabbed;
      if (target == NULL) {
        target = my_widget_hit_test(dispatcher->root, event->u.pointer.x,
                                    event->u.pointer.y);
      }
      hover_update(dispatcher, target);
      return target != NULL ? deliver(dispatcher, target, event) : false;
    case MY_EVENT_POINTER_UP:
      target = dispatcher->grabbed;
      if (target == NULL) {
        target = my_widget_hit_test(dispatcher->root, event->u.pointer.x,
                                    event->u.pointer.y);
      }
      dispatcher->grabbed = NULL;
      /* the grab kept hover on the pressed widget; re-hit on release */
      hover_update(dispatcher,
                   my_widget_hit_test(dispatcher->root, event->u.pointer.x,
                                      event->u.pointer.y));
      return target != NULL ? deliver(dispatcher, target, event) : false;
    case MY_EVENT_KEY_DOWN:
      if (event->u.key.key == MY_KEY_TAB) {
        bool consumed = dispatcher->focused != NULL
                            ? deliver(dispatcher, dispatcher->focused, event)
                            : false;
        if (!consumed) {
          int dir = (event->u.key.modifiers & MY_KEYMOD_SHIFT) != 0 ? -1 : 1;
          my_widget_t* next = focus_step(dispatcher->root, dispatcher->focused,
                                         dir);
          if (next != NULL) {
            set_focus(dispatcher, next);
            return true;
          }
        }
        return consumed;
      }
      return dispatcher->focused != NULL
                 ? deliver(dispatcher, dispatcher->focused, event)
                 : false;
    case MY_EVENT_KEY_UP:
      return dispatcher->focused != NULL
                 ? deliver(dispatcher, dispatcher->focused, event)
                 : false;
    case MY_EVENT_IME_PREEDIT: /* IME events go to the focus (M13a) */
    case MY_EVENT_IME_COMMIT:
    case MY_EVENT_IME_DELETE_SURROUNDING:
      return dispatcher->focused != NULL
                 ? deliver(dispatcher, dispatcher->focused, event)
                 : false;
    default:
      return false;
  }
}

static bool is_self_or_descendant(my_widget_t* w, my_widget_t* ancestor) {
  my_widget_t* p = w;
  while (p != NULL) {
    if (p == ancestor) {
      return true;
    }
    p = p->parent;
  }
  return false;
}

void my_event_dispatcher_forget(my_event_dispatcher_t* dispatcher,
                                my_widget_t* widget) {
  if (dispatcher == NULL || widget == NULL) {
    return;
  }
  if (dispatcher->grabbed != NULL &&
      is_self_or_descendant(dispatcher->grabbed, widget)) {
    dispatcher->grabbed = NULL;
  }
  if (dispatcher->focused != NULL &&
      is_self_or_descendant(dispatcher->focused, widget)) {
    my_widget_t* old = my_widget_ref(dispatcher->focused);
    my_emitter_emit(old->emitter, "blur", NULL);
    my_widget_unref(old);
    if (dispatcher->focused == old) {
      dispatcher->focused = NULL; /* a blur handler may have moved focus */
    }
  }
  if (dispatcher->hovered != NULL &&
      is_self_or_descendant(dispatcher->hovered, widget)) {
    /* no hover_leave: the widget is leaving the tree */
    dispatcher->hovered->hovered = false;
    dispatcher->hovered = NULL;
    hover_cursor_apply(dispatcher, NULL);
  }
}
