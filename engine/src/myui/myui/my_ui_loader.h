/**
 * @file my_ui_loader.h
 * @brief XML UI loader: builds widget trees from XML documents.
 *
 * Element tags map to widget factories (registry; window/button/label/
 * edit/checkbox/slider/progress_bar built in). Common attributes handled
 * by the loader: name, x/y/w/h, visible/enable, lp (layout params),
 * layout ("linear:h:8" / "linear:v:8" / "default"). All v:* attributes
 * are joined into the widget's bind_rules (';' separated) for
 * my_mvvm_bind(). A <style> element's text is fed to my_theme_load_str
 * onto the window's theme. Widget-specific attributes (text/hint/value/
 * min/max/step/checked/password/...) are parsed by each factory.
 *
 * The root element should be <window> (needs pal); anything else builds
 * a plain widget tree.
 *
 * Compile-time switch: MYUI_UI_XML (default ON; OFF for size-trimmed
 * builds — load functions return NULL).
 */
#ifndef MY_UI_LOADER_H
#define MY_UI_LOADER_H

#include "myui/my_window.h"
#include "myui/my_xml.h"

/** @brief Widget factory for one XML tag. */
typedef my_widget_t* (*my_ui_factory_fn_t)(const my_allocator_t* allocator,
                                           const my_xml_node_t* node);

/** @brief Register (or replace) a tag factory. Max 32 tags. */
my_ret_t my_ui_loader_register(const char* tag, my_ui_factory_fn_t factory);

/** @brief Loader error (element line from the XML source). */
typedef struct my_ui_error_t {
  int line;
  char message[96];
} my_ui_error_t;

/**
 * @brief Load a widget tree from an XML string. A <window> root requires
 * pal (non-NULL) and returns a my_window_t*. NULL on error (see err).
 */
my_widget_t* my_ui_load_str(const my_allocator_t* allocator, my_pal_t* pal,
                            const char* xml_str, my_ui_error_t* err);

/** @brief Load from a file path (NULL on error). */
my_widget_t* my_ui_load_file(const my_allocator_t* allocator, my_pal_t* pal,
                             const char* path, my_ui_error_t* err);

#endif /* MY_UI_LOADER_H */
