/* Internal registry coordination shared by the loader and class registry. */
#ifndef MY_WIDGET_REGISTRY_INTERNAL_H
#define MY_WIDGET_REGISTRY_INTERNAL_H

#include <stdbool.h>

typedef struct my_widget_t my_widget_t;

bool my_widget_registry_callback_active(void);
void my_widget_registry_callback_enter(void);
void my_widget_registry_callback_leave(void);
bool my_widget_class_is_builtin_type(const char* type);
void my_widget_class_unbind_instance(my_widget_t* widget);

#endif /* MY_WIDGET_REGISTRY_INTERNAL_H */
