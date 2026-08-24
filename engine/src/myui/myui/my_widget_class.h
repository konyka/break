/**
 * @file my_widget_class.h
 * @brief Widget class registry: declarative tag -> create + property
 * descriptors (M24a).
 *
 * One table drives all three former hand-written mappings: the YAML UI
 * loader (my_ui_loader.c), the ui2c code generator (tools/ui2c.c) and the
 * MVVM property router (mymvvm_myui/my_widget_target.c). Built-in classes
 * are registered lazily on the first my_widget_class_find(); applications
 * may register custom classes (an existing type name is overridden).
 *
 * Property lookup order of my_widget_set_prop()/my_widget_get_prop():
 * base-class common properties first ("visible", "enable", "x", "y",
 * "w", "h" — handled for every widget without consulting the table),
 * then the property descriptors of the widget's class (matched by
 * widget->widget_type). Unknown names return MY_RET_NOT_SUPPORTED.
 */
#ifndef MY_WIDGET_CLASS_H
#define MY_WIDGET_CLASS_H

#include "myc/my_value.h"
#include "myui/my_widget.h"

/** @brief Type of a widget property (drives string conversions). */
typedef enum my_prop_type_t {
  MY_PROP_STRING,
  MY_PROP_INT,
  MY_PROP_FLOAT,
  MY_PROP_BOOL,
  MY_PROP_COLOR
} my_prop_type_t;

/** @brief One property of a widget class (NULL set/get = read/write-only). */
typedef struct my_prop_desc_t {
  const char* name;   /**< "text" "value" ... */
  my_prop_type_t type;
  my_ret_t (*set)(my_widget_t*, const my_value_t*);  /**< NULL = read-only */
  my_ret_t (*get)(const my_widget_t*, my_value_t*);  /**< NULL = write-only */
} my_prop_desc_t;

/** @brief A widget class: YAML type + factory + property table. */
typedef struct my_widget_class_t {
  const char* type;                      /**< "button" ... */
  my_widget_t* (*create)(const my_allocator_t*);
  const my_prop_desc_t* props;           /**< name==NULL terminated */
  const char* const* events;             /**< {"click", NULL}, documentary */
} my_widget_class_t;

/**
 * @brief Register a custom widget class (an existing type name is
 * overridden). cls must outlive the registry (static storage).
 */
my_ret_t my_widget_class_register(const my_widget_class_t* cls);

/**
 * @brief Find a class by type name (built-ins are registered lazily).
 * NULL when unknown.
 */
const my_widget_class_t* my_widget_class_find(const char* type);

/** @brief Set a property by name (see the lookup order above). */
my_ret_t my_widget_set_prop(my_widget_t* w, const char* name,
                            const my_value_t* v);
/** @brief Get a property by name (see the lookup order above). */
my_ret_t my_widget_get_prop(my_widget_t* w, const char* name, my_value_t* v);

/* typed convenience wrappers (ui2c-generated code and applications) */
my_ret_t my_widget_set_prop_str(my_widget_t* w, const char* name,
                                const char* v);
my_ret_t my_widget_set_prop_int(my_widget_t* w, const char* name, int32_t v);
my_ret_t my_widget_set_prop_float(my_widget_t* w, const char* name, float v);
my_ret_t my_widget_set_prop_bool(my_widget_t* w, const char* name, bool v);

#endif /* MY_WIDGET_CLASS_H */
