/**
 * @file dxx_app.h
 * @brief Break-aware duanxianxia application shell.
 *
 * dxx_core owns the view builders; this module owns the navigation state
 * and composes those builders into one scrollable home page. The original
 * dummy-port main.c remains the headless demo entry point.
 */
#ifndef DXX_APP_H
#define DXX_APP_H

#include "core/types.h"
#include "myui/my_window_manager.h"

typedef struct dxx_app_t dxx_app_t;

/** @brief Build the home page on @a win using @a font. */
dxx_app_t *dxx_app_create(my_window_manager_t *wm, my_window_t *win,
                          my_font_t *font, u32 width, u32 height);

/** @brief Tear down navigation state and topbar menus (not the window). */
void dxx_app_destroy(dxx_app_t *app);

/** @brief Topbar navigation callback entry point. */
void dxx_app_navigate(dxx_app_t *app, const char *name);

/** @brief Return the root page content widget (borrowed). */
my_widget_t *dxx_app_page(dxx_app_t *app);

#endif /* DXX_APP_H */
