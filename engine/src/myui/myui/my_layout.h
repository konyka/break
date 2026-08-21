/**
 * @file my_layout.h
 * @brief Layouters: arrange a widget's children.
 *
 * A layouter is attached with my_widget_set_layouter() and runs on
 * my_widget_relayout(). Children declare their sizing via layout_params
 * (my_widget_set_layout_params), syntax per axis:
 *   "w:100"   fixed pixels
 *   "w:50%"   percent of the parent's content size
 *   "w:1f"    flex: share of the remaining space, weighted
 * Missing axis = MY_LAYOUT_AUTO (main axis: keep current size; cross
 * axis: fill the parent's content size).
 * Grid layout: TODO (M3b+).
 */
#ifndef MY_LAYOUT_H
#define MY_LAYOUT_H

#include "myui/my_widget.h"

/**
 * @brief Parse a layout-params string ("w:50% h:1f"). NULL/empty str =
 * both axes AUTO. Returns MY_RET_INVALID_PARAMS on garbage.
 */
my_ret_t my_layout_params_parse(const char* str, my_layout_params_t* out);

/** @brief Set a child's layout params from a string (see syntax above). */
my_ret_t my_widget_set_layout_params(my_widget_t* widget, const char* params);

/** @brief Layouter interface (single-function vtable + destroy). */
typedef struct my_layouter_t {
  /** @brief Arrange parent's direct children (set their rects). */
  void (*layout)(struct my_layouter_t* self, my_widget_t* parent);
  void (*destroy)(struct my_layouter_t* self);
} my_layouter_t;

/**
 * @brief The default layouter: does nothing (absolute positioning).
 * Shared singleton, do NOT destroy.
 */
my_layouter_t* my_layouter_default(void);

/** @brief Linear layouter (NULL allocator = default). */
my_layouter_t* my_layouter_linear_create(const my_allocator_t* allocator,
                                         bool horizontal, int32_t spacing);

/** @brief Flow layouter row alignment (M14a). */
typedef enum my_flow_align_t {
  MY_FLOW_ALIGN_LEFT = 0, /**< rows start at the left edge */
  MY_FLOW_ALIGN_CENTER    /**< rows are centered horizontally */
} my_flow_align_t;

/**
 * @brief Flow layouter (M14a): children are placed left-to-right with
 * h_spacing between them; a child that does not fit the remaining row
 * width wraps to the next row (v_spacing between rows). Row height =
 * tallest child in the row; align controls each row's horizontal
 * alignment. Child sizing: w/h layout_params PX or % (of the parent's
 * width/height); AUTO keeps the current rect size; FLEX is meaningless
 * in flow and treated as AUTO. The layouter only positions children —
 * the parent's height is NOT adjusted; use my_layouter_flow_measure()
 * for the content height (e.g. scroll_view content).
 */
my_layouter_t* my_layouter_flow_create(const my_allocator_t* allocator,
                                       int32_t h_spacing, int32_t v_spacing,
                                       my_flow_align_t align);

/**
 * @brief Total content height the flow layouter would produce for
 * parent's children at the parent's current width (no rects are
 * changed). Returns 0 when parent has no flow layouter attached.
 */
int32_t my_layouter_flow_measure(my_widget_t* parent);

/** @brief Attach a layouter (takes ownership; NULL resets to absolute). */
my_ret_t my_widget_set_layouter(my_widget_t* widget, my_layouter_t* layouter);

/** @brief Force this widget's layouter and recurse through the whole subtree. */
void my_widget_relayout(my_widget_t* widget);

/**
 * @brief Consume only pending layout work in this subtree.
 *
 * Window frame code uses this dirty-path variant to avoid invoking layout
 * callbacks on clean siblings. A callback may enqueue another bounded pass.
 */
void my_widget_relayout_pending(my_widget_t* widget);

#endif /* MY_LAYOUT_H */
