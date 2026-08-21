/**
 * @file my_widget_target.h
 * @brief myui adapter: wraps a widget as an MVVM binding target.
 *
 * Property mapping (set_prop/get_prop):
 *  - "text": button/label text (by widget_type);
 *  - "visible"/"enable": bool;
 *  - "x"/"y"/"w"/"h": int32 geometry;
 *  - "value": generic slot stored on the target itself.
 * Events map to the widget emitter ("click", "changed", ...).
 * rebuild_items: non-list containers rebuild their children from the named
 * ItemTemplate; list_view updates its virtualized adapter in place.
 */
#ifndef MY_WIDGET_TARGET_H
#define MY_WIDGET_TARGET_H

#include "mymvvm/my_binding_target.h"
#include "myui/my_widget.h"

/** @brief Widget binding target (created by my_widget_target_create). */
typedef struct my_widget_target_t {
  my_binding_target_t base;
  const my_allocator_t* allocator;
  my_widget_t* widget; /**< weak */
  my_value_t value;    /**< generic "value" property slot */
  void* items_adapter; /**< owned when widget is a list_view (M8b) */
} my_widget_target_t;

/** @brief Wrap a widget (weak ref) as a binding target. */
my_widget_target_t* my_widget_target_create(const my_allocator_t* allocator,
                                            my_widget_t* widget);

void my_widget_target_destroy(my_widget_target_t* target);

#endif /* MY_WIDGET_TARGET_H */
