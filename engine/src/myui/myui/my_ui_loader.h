/**
 * @file my_ui_loader.h
 * @brief YAML UI loader: builds widget trees from YAML documents.
 *
 * YAML type names map to widget factories (registry; window/button/label/
 * edit/checkbox/slider/progress_bar built in). Common attributes handled
 * by the loader: name, x/y/w/h, visible/enable, lp (layout params),
 * layout ("linear:h:8" / "linear:v:8" / "default"). Bindings in the
 * `bindings` map are joined into the widget's bind_rules (';' separated) for
 * my_mvvm_bind(). A root `style` string is fed to my_theme_load_str onto
 * the window's theme. Widget-specific properties (text/hint/value/
 * min/max/step/checked/password/...) are parsed by each factory. YAML uses
 * a `type` key and a `children` sequence; common and widget properties are
 * direct keys. Bindings live in a `bindings` map and style is a scalar key.
 *
 * The root type can be `window` (needs pal); anything else builds
 * a plain widget tree.
 *
 * Compile-time switch: MYUI_UI_YAML (default ON; OFF for size-trimmed
 * builds — load functions return NULL).
 */
#ifndef MY_UI_LOADER_H
#define MY_UI_LOADER_H

#include "myc/myconf/my_conf.h"
#include "myui/my_window.h"

#define MY_UI_MAX_YAML_BYTES (4u * 1024u * 1024u)

/** @brief Widget factory for one YAML widget object. */
typedef my_widget_t* (*my_ui_factory_fn_t)(const my_allocator_t* allocator,
                                           const my_conf_node_t* node);

/** @brief Register (or replace) a YAML type factory. Max 32 types. */
my_ret_t my_ui_loader_register(const char* type, my_ui_factory_fn_t factory);

/** @brief Loader error (source line for YAML syntax failures). */
typedef struct my_ui_error_t {
  int line;
  char message[96];
} my_ui_error_t;

/**
 * @brief Load a widget tree from a YAML string. A `window` root requires
 * pal (non-NULL) and returns a my_window_t*. NULL on error (see err).
 */
my_widget_t* my_ui_load_str(const my_allocator_t* allocator, my_pal_t* pal,
                            const char* yaml_str, my_ui_error_t* err);

/** @brief Load from a file path (NULL on error). */
my_widget_t* my_ui_load_file(const my_allocator_t* allocator, my_pal_t* pal,
                             const char* path, my_ui_error_t* err);

#endif /* MY_UI_LOADER_H */
