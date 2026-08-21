/**
 * @file placeholder.h
 * @brief duanxianxia clone: placeholder page for navigation targets
 * (M14d): big title + grey subtext + a "back to home" button.
 */
#ifndef DXX_PLACEHOLDER_H
#define DXX_PLACEHOLDER_H

#include "myui/my_widget.h"

/** @brief Create the placeholder panel (full-size; set rect + visible
 * by the caller). on_back(ctx) fires on the back button. */
my_widget_t* dxx_placeholder_create(const my_allocator_t* allocator,
                                    void (*on_back)(void* ctx), void* ctx);

/** @brief Switch the shown page name (16px bold title). */
void dxx_placeholder_set_title(my_widget_t* panel, const char* name);

#endif /* DXX_PLACEHOLDER_H */
