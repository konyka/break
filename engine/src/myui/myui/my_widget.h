/**
 * @file my_widget.h
 * @brief Widget base class: tree, geometry, painting, event hooks.
 *
 * Subclassing (mirrors my_object conventions):
 *  - embed my_widget_t as the FIRST member;
 *  - in the factory: allocate, then my_widget_init(), then override
 *    base.destroy with your own destructor that frees subclass resources
 *    and finally calls my_widget_destroy() (widget cleanup) followed by
 *    my_object_destroy() (frees name + struct);
 *  - vtable entries on_paint/on_event/on_layout are all optional.
 *
 * Ownership: add_child() takes over ONE reference of the child (the
 * caller keeps its own and should my_widget_unref() it when done);
 * remove_child() releases the tree's reference.
 *
 * Coordinates: widget->rect is in the PARENT's coordinate space; the
 * root's parent space is the window/global space.
 */
#ifndef MY_WIDGET_H
#define MY_WIDGET_H

#include "myc/my_darray.h"
#include "myc/my_emitter.h"
#include "myc/my_object.h"
#include "myui/my_theme.h"
#include "myr/my_dirty_rects.h"
#include "myr/my_vgcanvas.h"
#include "mypal/my_event.h"

typedef struct my_widget_t my_widget_t;

/** @brief Sizing mode of one layout axis. */
typedef enum my_layout_mode_t {
  MY_LAYOUT_AUTO = 0, /**< keep current size */
  MY_LAYOUT_PX,       /**< fixed pixels */
  MY_LAYOUT_PERCENT,  /**< percent of the parent's content size */
  MY_LAYOUT_FLEX      /**< share of remaining space (weight) */
} my_layout_mode_t;

/**
 * @brief Parsed layout params (syntax: "w:100 h:30", "w:50%", "w:1f").
 * Parsed by my_layout_params_parse() (my_layout.h).
 */
typedef struct my_layout_params_t {
  my_layout_mode_t w_mode;
  float w_value;
  my_layout_mode_t h_mode;
  float h_value;
} my_layout_params_t;

/** @brief Widget vtable; every entry is optional (NULL = no-op). */
typedef struct my_widget_vtable_t {
  /** @brief Paint self (children are painted afterwards by the framework). */
  void (*on_paint)(my_widget_t* widget, my_vgcanvas_t* vg);
  /**
   * @brief Handle a dispatched event. Return MY_RET_OK to consume it
   * (stops bubbling), anything else to let it bubble to the parent.
   */
  my_ret_t (*on_event)(my_widget_t* widget, const my_event_t* event);
  /** @brief Optional custom layout hook (layouters usually suffice). */
  void (*on_layout)(my_widget_t* widget);
  /**
   * @brief Optional content-driven measurement (M24c). Called by
   * my_widget_relayout() BEFORE the layouter/on_layout of the same
   * widget, so auto-sizing widgets (node auto-size, scroll_view
   * re-clamp) settle their own rect/state first. NULL = keep as is.
   */
  void (*on_measure)(my_widget_t* widget);
} my_widget_vtable_t;

struct my_layouter_t;

/** @brief Root-only hook: a subtree is about to be removed (M3b). */
typedef void (*my_widget_removed_hook_t)(my_widget_t* root,
                                         my_widget_t* removed);

/** @brief Widget base "class". */
struct my_widget_t {
  my_object_t base;                 /**< ref counting + destroy chain */
  const my_widget_vtable_t* vtable;
  my_widget_t* parent;              /**< weak reference */
  my_darray_t* children;            /**< owned references (my_widget_t*) */
  my_rect_t rect;                   /**< in parent coordinates */
  bool visible;
  bool enable;
  bool focusable;
  bool dirty;                       /**< needs repaint */
  bool hovered;  /**< pointer is over (dispatcher-maintained, M14a);
                  * drives the MY_STATE_HOVER style slot */
  bool need_layout;                 /**< this widget needs layout callbacks */
  bool subtree_need_layout; /**< a descendant has pending layout work */
  bool floating;  /**< overlay/popup child: layouters skip it, rect is
                       * set absolutely by the owner (M13c) */
  const char* widget_type;          /**< static type name for theming */
  my_emitter_t* emitter;            /**< my_widget_on() convenience */
  my_layout_params_t layout_params; /**< parsed "w:.. h:.." spec */
  struct my_layouter_t* layouter;   /**< owned, NULL = absolute */
  my_dirty_rects_t* dirty_sink;     /**< root only: frame dirty collector */
  my_style_t* local_style;          /**< owned local overrides (M3b) */
  my_theme_t* theme;                /**< weak; lookup climbs ancestors */
  void* user_data;  /**< app/owner pointer, unused by the core (M13c) */
  char* tooltip;    /**< owned hover hint text, NULL = none (M13c) */
  char* style_class; /**< owned: space-separated CSS classes (M18a) */
  char* bind_rules;                 /**< owned: MVVM rules (M4b), ";" separated */
  void* anim_mgr;                   /**< root only, weak (my_animator) */
  my_widget_removed_hook_t removed_hook; /**< root only: subtree removed */
};

/** @brief Initialize an already-allocated widget (subclass factories). */
my_ret_t my_widget_init(my_widget_t* widget, const my_allocator_t* allocator,
                        const my_widget_vtable_t* vtable, const char* name);

/**
 * @brief Lightweight anonymous subclassing (M24c): replace the vtable of
 * an already-created widget. Contract: only for subclasses with NO own
 * resources that merely customize paint/event — the destroy chain stays
 * the plain widget one (a subclass needing its own destructor must use
 * the full factory pattern described at the top of this file). Replaces
 * the former ad-hoc `w->vtable = &vt;` overrides.
 */
my_ret_t my_widget_subclass_init(my_widget_t* widget,
                                 const my_widget_vtable_t* vtable);

/** @brief Create a plain container widget. */
my_widget_t* my_widget_create(const my_allocator_t* allocator, const char* name);

/**
 * @brief Widget-level destructor for the destroy chain: frees children,
 * emitter, layout params and layouter. Does NOT free name/struct — call
 * my_object_destroy() after it (subclass destructors chain this way).
 */
void my_widget_destroy(my_widget_t* widget);

static inline my_widget_t* my_widget_ref(my_widget_t* widget) {
  return widget != NULL ? (my_widget_t*)my_object_ref((my_object_t*)widget)
                        : NULL;
}

static inline void my_widget_unref(my_widget_t* widget) {
  if (widget != NULL) {
    my_object_unref((my_object_t*)widget);
  }
}

/**
 * @brief Add a detached child (takes over one reference of child).
 *
 * The parent becomes fully dirty and layout is requested through the root
 * because sibling layout may change. A child already attached elsewhere, or
 * an operation that would create a cycle, is rejected.
 */
my_ret_t my_widget_add_child(my_widget_t* parent, my_widget_t* child);
/**
 * @brief Remove child (releases the tree's reference).
 *
 * The parent is invalidated and layout is requested through the root, so both
 * the old child pixels and the post-layout arrangement are covered by damage.
 */
my_ret_t my_widget_remove_child(my_widget_t* parent, my_widget_t* child);
/** @brief Find a direct child by name (NULL when absent). */
my_widget_t* my_widget_find_child(my_widget_t* parent, const char* name);
/**
 * @brief Find any descendant by name (depth-first, direct children
 * first; the widget itself is not matched). NULL when absent. Plain
 * recursion — the widget tree is acyclic by construction (M24c).
 */
my_widget_t* my_widget_find_descendant(my_widget_t* parent, const char* name);
/** @brief Number of direct children. */
size_t my_widget_child_count(my_widget_t* parent);
/** @brief Get the i-th direct child (borrowed). */
my_widget_t* my_widget_get_child(my_widget_t* parent, size_t index);

/**
 * @brief Set application-owned geometry and schedule a root relayout.
 *
 * A changed rect invalidates both its old and new coverage, which is required
 * for retained shared render targets.
 */
my_ret_t my_widget_set_rect(my_widget_t* widget, const my_rect_t* rect);

/**
 * @brief Apply geometry during a layout callback without scheduling relayout.
 *
 * The old and new coverage are still recorded in the root dirty sink.
 */
my_ret_t my_widget_set_layout_rect(my_widget_t* widget,
                                   const my_rect_t* rect);

/**
 * @brief Request this widget's layout callbacks and mark its ancestor path.
 *
 * The pending frame walker revisits only this widget and dirty descendant
 * paths; use the parent when a child's layout params or geometry affect the
 * parent's layouter.
 */
void my_widget_request_layout(my_widget_t* widget);
my_ret_t my_widget_set_visible(my_widget_t* widget, bool visible);

/**
 * @brief Single point of the enable/hover/pressed -> style state
 * derivation (M24b): !enable -> MY_STATE_DISABLED, else pressed ->
 * MY_STATE_PRESSED, else hovered -> MY_STATE_HOVER, else MY_STATE_NORMAL.
 * Each widget keeps owning its `pressed` flag (button press, slider or
 * scroll_bar drag) and passes it in. Widgets whose state derivation
 * deliberately differs (edit/text_area borrow the HOVER slot for the
 * focused border) do NOT use this helper.
 */
my_widget_state_t my_widget_current_state(const my_widget_t* widget,
                                          bool pressed);

/** @brief Rename a widget (name is used by theme [name] selectors). */
my_ret_t my_widget_set_name(my_widget_t* widget, const char* name);

/** @brief Store an app/owner pointer on the widget (not owned, unused by the core). */
my_ret_t my_widget_set_user_data(my_widget_t* widget, void* user_data);

/** @brief Read back the pointer stored with my_widget_set_user_data(). */
void* my_widget_get_user_data(const my_widget_t* widget);

/** @brief Set the hover hint text (copied; NULL clears). Shown by the
 * window after a short hover delay (M13c). */
my_ret_t my_widget_set_tooltip(my_widget_t* widget, const char* text);

/** @brief The tooltip text (NULL when none). */
const char* my_widget_get_tooltip(const my_widget_t* widget);

/** @brief Set the space-separated CSS class list (copied; NULL clears).
 * Drives .class theme rules (M18a). */
my_ret_t my_widget_set_style_class(my_widget_t* widget, const char* cls);

/** @brief The style class string (NULL when none). */
const char* my_widget_get_style_class(const my_widget_t* widget);

/** @brief Attach MVVM binding rules (";"-separated, see docs/mvvm.md). */
my_ret_t my_widget_set_bind_rules(my_widget_t* widget, const char* rules);

/**
 * @brief Mark a local rect (NULL = whole widget) dirty; bubbles the dirty
 * flag up and records the rect (global space) into the root's dirty_sink.
 */
void my_widget_invalidate(my_widget_t* widget, const my_rect_t* rect);

/** @brief Local point -> global (root) coordinates. */
void my_widget_local_to_global(my_widget_t* widget, int32_t* x, int32_t* y);
/** @brief Global (root) point -> local coordinates. */
void my_widget_global_to_local(my_widget_t* widget, int32_t* x, int32_t* y);

/**
 * @brief Deepest visible widget at point (x,y given in widget's PARENT
 * space; for the root this is the global space). Z-order: later children
 * are on top. Returns NULL when the point is outside.
 */
my_widget_t* my_widget_hit_test(my_widget_t* widget, int32_t x, int32_t y);

/**
 * @brief Paint the subtree: invisible -> skip; otherwise
 * save/translate-to-origin/clip-to-rect/on_paint/children/restore.
 */
void my_widget_paint(my_widget_t* widget, my_vgcanvas_t* vg);

/** @brief Register an emitter listener ("click", "pointer_down", ...). */
uint32_t my_widget_on(my_widget_t* widget, const char* event_name,
                      my_event_callback_t callback, void* ctx);
/** @brief Unregister a listener by id. */
my_ret_t my_widget_off(my_widget_t* widget, uint32_t id);

/* layouter-related setters live in my_layout.h */

/* style/theme API (implemented in my_theme.c) */

/** @brief Set a local style override (highest priority). */
my_ret_t my_widget_style_set(my_widget_t* widget, my_widget_state_t state,
                             const char* key, const my_value_t* value);

/** @brief Resolve a style value: local > theme name match > theme type
 * match; state falls back to normal. NULL when unresolved. */
const my_value_t* my_widget_style_get(my_widget_t* widget,
                                      my_widget_state_t state, const char* key);

/** @brief Resolve a color (0xRRGGBBAA), fallback when unresolved. */
uint32_t my_widget_style_get_color(my_widget_t* widget, my_widget_state_t state,
                                   const char* key, uint32_t fallback);

/** @brief Resolve an int, fallback when unresolved. */
int32_t my_widget_style_get_int(my_widget_t* widget, my_widget_state_t state,
                                const char* key, int32_t fallback);

/** @brief Attach a theme at this widget (weak ref); applies to the
 * subtree at query time (climbs ancestors). Invalidates the subtree. */
my_ret_t my_widget_apply_theme(my_widget_t* widget, my_theme_t* theme);

#endif /* MY_WIDGET_H */
