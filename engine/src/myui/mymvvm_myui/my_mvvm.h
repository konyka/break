/**
 * @file my_mvvm.h
 * @brief MVVM convenience layer for myui: item template registry,
 * one-call window binding, and a window-manager navigator.
 */
#ifndef MY_MVVM_H
#define MY_MVVM_H

#include "mymvvm/my_binding_context.h"
#include "mymvvm/my_navigator.h"
#include "myui/my_window_manager.h"

/* ---------------- item templates ---------------- */

/** @brief Builds one item-row widget for rebuild_items. */
typedef my_widget_t* (*my_item_builder_fn_t)(my_widget_t* parent, size_t index,
                                             my_item_props_fn_t props,
                                             void* props_ctx, void* builder_ctx);

/** @brief Template registry entry. */
typedef struct my_item_template_t {
  char name[32];
  my_item_builder_fn_t build;
  void* ctx;
} my_item_template_t;

/** @brief Register an item template (max 16; replaces same-name). */
my_ret_t my_mvvm_register_template(const char* name, my_item_builder_fn_t fn,
                                   void* ctx);

/** @brief Find a template (NULL when unregistered). */
const my_item_template_t* my_mvvm_find_template(const char* name);

/* ---------------- one-call binding ---------------- */

/** @brief Binding session: context + owned widget targets. */
typedef struct my_mvvm_context_t {
  const my_allocator_t* allocator;
  my_binding_context_t* ctx;     /**< owned */
  my_darray_t* targets;          /**< owned my_widget_target_t* */
  my_window_manager_t* wm;       /**< weak, for CloseWindow */
  my_window_t* win;              /**< weak */
} my_mvvm_context_t;

/**
 * @brief Bind a window to a view model: walks the widget tree, wraps each
 * widget carrying bind_rules (my_widget_set_bind_rules) as a target and
 * applies every rule. Command rules with CloseWindow=true close win via
 * wm after the command.
 */
my_mvvm_context_t* my_mvvm_bind(my_window_manager_t* wm, my_window_t* win,
                                my_view_model_t* vm);

void my_mvvm_context_destroy(my_mvvm_context_t* ctx);

/* ---------------- navigator ---------------- */

/** @brief Page factory: build a window for a TO request. */
typedef my_window_t* (*my_page_factory_fn_t)(my_pal_t* pal, const char* args,
                                             void* ctx);

/** @brief Navigator backed by the window manager. */
typedef struct my_navigator_wm_t {
  my_navigator_t base;
  const my_allocator_t* allocator;
  my_window_manager_t* wm; /**< weak */
  my_pal_t* pal;           /**< weak */
  my_darray_t* pages;      /**< page_entry_t* */
} my_navigator_wm_t;

/** @brief Create a window-manager navigator (does NOT set it as default). */
my_navigator_wm_t* my_navigator_wm_create(const my_allocator_t* allocator,
                                          my_window_manager_t* wm,
                                          my_pal_t* pal);

void my_navigator_wm_destroy(my_navigator_wm_t* nav);

/** @brief Register a page factory by name. */
my_ret_t my_navigator_wm_add_page(my_navigator_wm_t* nav, const char* name,
                                  my_page_factory_fn_t factory, void* ctx);

#endif /* MY_MVVM_H */
