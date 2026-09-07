/**
 * @file my_mvvm.h
 * @brief MVVM convenience layer for myui: item template registry,
 * one-call window binding, and a window-manager navigator.
 */
#ifndef MY_MVVM_H
#define MY_MVVM_H

#include "mymvvm/my_binding_context.h"
#include "mymvvm/my_navigator.h"
#include "myc/my_emitter.h"
#include "mypal/my_pal.h"
#include "myui/my_window_manager.h"

#include <stdatomic.h>

/* ---------------- item templates ---------------- */

/** @brief Builds one item-row widget for rebuild_items. */
typedef my_widget_t* (*my_item_builder_fn_t)(my_widget_t* parent, size_t index,
                                             my_item_props_fn_t props,
                                             void* props_ctx, void* builder_ctx);
typedef void (*my_item_context_destroy_fn_t)(void* ctx);

/** @brief Template registry entry. */
typedef struct my_item_template_t {
  char name[32];
  my_item_builder_fn_t build;
  void* ctx;
} my_item_template_t;

/** @brief Register an item template (max 16; replaces same-name). */
my_ret_t my_mvvm_register_template(const char* name, my_item_builder_fn_t fn,
                                   void* ctx);

/**
 * @brief Register a template and transfer its builder context ownership.
 *
 * On success, destroy_ctx is called exactly once when the entry is replaced
 * or unregistered. On failure, ownership remains with the caller.
 */
my_ret_t my_mvvm_register_template_owned(
    const char* name, my_item_builder_fn_t fn, void* ctx,
    my_item_context_destroy_fn_t destroy_ctx);

/** @brief Unregister a template and release its owned context, if any. */
my_ret_t my_mvvm_unregister_template(const char* name);

/** @brief Find a template (NULL when unregistered). */
const my_item_template_t* my_mvvm_find_template(const char* name);

/* ---------------- one-call binding ---------------- */

/** @brief Binding session: context + owned widget targets. */
typedef struct my_mvvm_context_t {
  const my_allocator_t* allocator;
  my_binding_context_t* ctx;     /**< owned */
  my_darray_t* targets;          /**< owned my_widget_target_t* */
  my_darray_t* close_listeners;  /**< owned listener records */
  my_window_manager_t* wm;       /**< weak, for CloseWindow */
  my_window_t* win;              /**< owned context-lifetime reference */
  uint32_t wm_destroy_listener_id; /**< listener holds one context reference */
  struct my_ui_command_scope_t* command_scope; /**< owned async lifetime */
  void* async_state; /**< private bounded async submission state */
  my_pal_main_loop_t* loop; /**< immutable async destination, borrowed */
  atomic_uint ref_count; /**< context lifetime references */
  atomic_bool closing; /**< final release has started */
} my_mvvm_context_t;

/**
 * @brief Bind a window to a view model: walks the widget tree, wraps each
 * widget carrying bind_rules (my_widget_set_bind_rules) as a target and
 * applies every rule. Command rules with CloseWindow=true close win via
 * wm after the command.
 */
my_mvvm_context_t* my_mvvm_bind(my_window_manager_t* wm, my_window_t* win,
                                my_view_model_t* vm);

/** @brief Retain a binding context for use by an asynchronous producer. */
my_mvvm_context_t* my_mvvm_context_ref(my_mvvm_context_t* ctx);

/**
 * @brief Release a binding context reference; NULL-safe.
 *
 * When the last reference is released off the UI loop, final destruction is
 * deferred to the bound loop so widgets and binding listeners remain
 * thread-affine. The loop must outlive all context references.
 */
void my_mvvm_context_unref(my_mvvm_context_t* ctx);

/**
 * @brief Queue a copied view-model notification on the bound window loop.
 *
 * All binding listeners and UI target writes run on the window loop. The
 * caller must synchronize any model storage mutation before calling this
 * compatibility API; use my_mvvm_context_set_property_async() when the
 * worker needs the model write itself to be serialized.
 */
my_ret_t my_mvvm_context_notify_change_async(my_mvvm_context_t* ctx,
                                             const char* name);

/**
 * @brief Copy and queue a view-model property write on the window loop.
 *
 * Scalar and string values are copied before returning. Pointer values are
 * rejected because my_value_t only borrows their pointee. The model setter,
 * its notification, and all UI target writes execute on the window loop.
 */
my_ret_t my_mvvm_context_set_property_async(my_mvvm_context_t* ctx,
                                            const char* name,
                                            const my_value_t* value);

/** @brief Release the creator reference (equivalent to unref). */
void my_mvvm_context_destroy(my_mvvm_context_t* ctx);

/* ---------------- navigator ---------------- */

/** @brief Page factory: build a window for a TO request. */
typedef my_window_t* (*my_page_factory_fn_t)(my_pal_t* pal, const char* args,
                                             void* ctx);
typedef void (*my_page_context_destroy_fn_t)(void* ctx);

/** @brief Navigator backed by the window manager. */
typedef struct my_navigator_wm_t {
  my_navigator_t base;
  const my_allocator_t* allocator;
  my_window_manager_t* wm; /**< weak */
  my_pal_t* pal;           /**< weak */
  uint32_t wm_destroy_listener_id;
  my_darray_t* pages;      /**< page_entry_t* */
  struct my_ui_command_scope_t* command_scope; /**< owned async lifetime */
  bool destroying;
  bool destroy_requested;
  unsigned callback_depth;
} my_navigator_wm_t;

/** @brief Create a window-manager navigator (does NOT set it as default). */
my_navigator_wm_t* my_navigator_wm_create(const my_allocator_t* allocator,
                                          my_window_manager_t* wm,
                                          my_pal_t* pal);

void my_navigator_wm_destroy(my_navigator_wm_t* nav);

/** @brief Register a page factory by name. */
my_ret_t my_navigator_wm_add_page(my_navigator_wm_t* nav, const char* name,
                                  my_page_factory_fn_t factory, void* ctx);

/**
 * @brief Register a page and transfer its context ownership to the navigator.
 *
 * On success, destroy_ctx is called exactly once when the page registration is
 * released. On failure, ownership remains with the caller.
 */
my_ret_t my_navigator_wm_add_page_owned(
    my_navigator_wm_t* nav, const char* name, my_page_factory_fn_t factory,
    void* ctx, my_page_context_destroy_fn_t destroy_ctx);

/** @brief Register a page factory guarded by an invalidatable context lease. */
my_ret_t my_navigator_wm_add_page_lease(
    my_navigator_wm_t* nav, const char* name, my_page_factory_fn_t factory,
    my_emitter_context_lease_t* lease);

/**
 * @brief Queue an owned navigation request on the navigator's loop.
 *
 * The request is copied before this function returns. It executes on the
 * target loop thread and is cancelled when the navigator is destroyed.
 * The loop must outlive all producers and queued requests.
 */
my_ret_t my_navigator_wm_request_async(
    my_navigator_wm_t* nav, my_pal_main_loop_t* loop,
    const my_navigator_request_t* request);

#endif /* MY_MVVM_H */
