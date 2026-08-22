/**
 * @file my_scroll_view.h
 * @brief Generic vertical scroll container (M14a).
 *
 * Hosts ONE content widget (any subtree, e.g. a flow-laid-out panel);
 * when the content is taller than the view it scrolls vertically via
 * the wheel and an optionally linked scroll_bar (a sibling widget, same
 * pattern as my_list_view_set_scroll_bar). Clipping is automatic: the
 * widget paint path clips children to the parent's rect.
 *
 * Content height: explicit my_scroll_view_set_content_height(), else
 * the flow layouter's measure when the content uses one, else the
 * content's current rect height.
 */
#ifndef MY_SCROLL_VIEW_H
#define MY_SCROLL_VIEW_H

#include "myui/my_widget.h"

/** @brief Scroll view (opaque). */
typedef struct my_scroll_view_t my_scroll_view_t;

my_scroll_view_t* my_scroll_view_create(const my_allocator_t* allocator);

/** @brief Replace the content child (the view takes the tree reference;
 * callers still unref their own). */
my_ret_t my_scroll_view_set_content(my_scroll_view_t* sv,
                                    my_widget_t* content);

/** @brief The content widget (borrowed, NULL when none). */
my_widget_t* my_scroll_view_get_content(my_scroll_view_t* sv);

/** @brief The scroll view AS a widget (M24c uniform accessor; the type
 * is opaque, so this is the sanctioned way to mix it into widget-typed
 * APIs). The internal container is named "scroll_view". */
my_widget_t* my_scroll_view_widget(my_scroll_view_t* sv);

/** @brief Explicit content height in px; 0 = auto (flow measure /
 * content rect height). Triggers relayout. */
void my_scroll_view_set_content_height(my_scroll_view_t* sv, int32_t height);

/** @brief Current scroll offset [0, content_height - view_height]. */
int32_t my_scroll_view_get_offset(my_scroll_view_t* sv);

/** @brief Set the scroll offset (clamped). */
void my_scroll_view_set_offset(my_scroll_view_t* sv, int32_t offset);

/** @brief Link an external scroll_bar (weak ref, sibling widget);
 * value/page_size sync both ways. NULL unlinks. */
my_ret_t my_scroll_view_set_scroll_bar(my_scroll_view_t* sv,
                                       my_widget_t* bar);

#endif /* MY_SCROLL_VIEW_H */
