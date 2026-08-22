/**
 * @file my_binding_target.h
 * @brief Binding target: the UI-side endpoint of a binding.
 *
 * The binding context never touches widgets directly; it talks to this
 * vtable. M4b implements it for my_widget_t, unit tests implement mocks.
 * Event names follow the widget emitter convention ("changed", "click").
 */
#ifndef MY_BINDING_TARGET_H
#define MY_BINDING_TARGET_H

#include "myc/my_emitter.h"
#include "myc/my_value.h"

typedef struct my_binding_target_t my_binding_target_t;

/**
 * @brief Supplies one property of one item row to the UI side.
 * Fills value (MY_VALUE_NONE when the key is absent). Used by
 * rebuild_items.
 */
typedef void (*my_item_props_fn_t)(void* ctx, size_t index, const char* key,
                                   my_value_t* value);

/** @brief Binding target vtable. */
typedef struct my_binding_target_vtable_t {
  /** @brief Set a target property (e.g. "text", "value"). */
  my_ret_t (*set_prop)(my_binding_target_t* target, const char* name,
                       const my_value_t* value);
  /** @brief Read a target property back (TwoWay bindings). */
  my_ret_t (*get_prop)(my_binding_target_t* target, const char* name,
                       my_value_t* value);
  /** @brief Subscribe to a target event; returns id (> 0), 0 on failure. */
  uint32_t (*on_event)(my_binding_target_t* target, const char* event,
                       my_event_callback_t callback, void* ctx);
  my_ret_t (*off_event)(my_binding_target_t* target, uint32_t id);
  /**
   * @brief Rebuild the item list: count rows of template item_template,
   * row properties via props. Optional (items binding needs it).
   */
  my_ret_t (*rebuild_items)(my_binding_target_t* target,
                            const char* item_template, size_t count,
                            my_item_props_fn_t props, void* props_ctx);
} my_binding_target_vtable_t;

/** @brief Binding target base "class". */
struct my_binding_target_t {
  const my_binding_target_vtable_t* vtable;
};

static inline my_ret_t my_binding_target_set_prop(my_binding_target_t* target,
                                                  const char* name,
                                                  const my_value_t* value) {
  return target->vtable->set_prop(target, name, value);
}

static inline my_ret_t my_binding_target_get_prop(my_binding_target_t* target,
                                                  const char* name,
                                                  my_value_t* value) {
  return target->vtable->get_prop(target, name, value);
}

static inline uint32_t my_binding_target_on_event(my_binding_target_t* target,
                                                  const char* event,
                                                  my_event_callback_t callback,
                                                  void* ctx) {
  return target->vtable->on_event(target, event, callback, ctx);
}

static inline my_ret_t my_binding_target_off_event(my_binding_target_t* target,
                                                   uint32_t id) {
  return target->vtable->off_event(target, id);
}

#endif /* MY_BINDING_TARGET_H */
