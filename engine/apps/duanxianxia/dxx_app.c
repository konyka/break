/**
 * @file dxx_app.c
 * @brief Duanxianxia application composition for the Break RHI backend.
 */
#include "dxx_app.h"

#include <stdlib.h>
#include <string.h>

#include "dxx_theme.h"
#include "myui/widgets/my_scroll_bar.h"
#include "myui/widgets/my_scroll_view.h"
#include "views/auth.h"
#include "views/placeholder.h"
#include "views/views.h"

#define DXX_TOPBAR_H 50

struct dxx_app_t {
  my_window_manager_t *wm;
  my_window_t *win;
  my_scroll_view_t *page_sv;
  my_widget_t *scroll_bar;
  my_widget_t *placeholder;
  dxx_topbar_t topbar;
};

static void app_show_home(dxx_app_t *app) {
  my_widget_set_visible(app->placeholder, false);
  my_widget_set_visible((my_widget_t *)app->page_sv, true);
  my_widget_set_visible(app->scroll_bar, true);
  dxx_topbar_set_active(&app->topbar, "涨停表现");
  my_widget_invalidate(my_window_widget(app->win), NULL);
}

static void app_on_back(void *ctx) {
  app_show_home((dxx_app_t *)ctx);
}

static void app_on_nav(void *ctx, const char *name) {
  dxx_app_navigate((dxx_app_t *)ctx, name);
}

void dxx_app_navigate(dxx_app_t *app, const char *name) {
  if (app == NULL || name == NULL) {
    return;
  }
  if (strcmp(name, "注册") == 0) {
    dxx_show_auth_dialog(app->wm, true);
    return;
  }
  if (strcmp(name, "登录") == 0) {
    dxx_show_auth_dialog(app->wm, false);
    return;
  }
  if (strcmp(name, "首页") == 0 || strcmp(name, "涨停表现") == 0) {
    app_show_home(app);
    return;
  }
  dxx_placeholder_set_title(app->placeholder, name);
  my_widget_set_visible((my_widget_t *)app->page_sv, false);
  my_widget_set_visible(app->scroll_bar, false);
  my_widget_set_visible(app->placeholder, true);
  my_widget_invalidate(my_window_widget(app->win), NULL);
}

dxx_app_t *dxx_app_create(my_window_manager_t *wm, my_window_t *win,
                          my_font_t *font, u32 width, u32 height) {
  dxx_app_t *app;
  my_widget_t *page;
  my_widget_t *strip;
  my_widget_t *ztpool;
  my_widget_t *footer;
  int32_t y;
  if (win == NULL || width == 0 || height == 0) {
    return NULL;
  }
  app = (dxx_app_t *)calloc(1, sizeof(dxx_app_t));
  if (app == NULL) {
    return NULL;
  }
  app->wm = wm;
  app->win = win;
  my_window_set_theme(win, dxx_theme_create(NULL), true);
  if (font != NULL) {
    my_window_set_font(win, font, 16);
  }

  app->page_sv = my_scroll_view_create(NULL);
  if (app->page_sv == NULL) {
    free(app);
    return NULL;
  }
  my_widget_set_rect((my_widget_t *)app->page_sv,
                     &(my_rect_t){0, 0, (int32_t)width - 14, (int32_t)height});
  page = my_widget_create(NULL, "dxx_page");
  my_scroll_view_set_content(app->page_sv, page);
  my_widget_unref(page);
  my_widget_add_child(my_window_widget(win), (my_widget_t *)app->page_sv);
  my_widget_unref((my_widget_t *)app->page_sv);

  app->scroll_bar = my_scroll_bar_create(NULL);
  my_widget_set_rect(app->scroll_bar,
                     &(my_rect_t){(int32_t)width - 14, 0, 14, (int32_t)height});
  my_widget_add_child(my_window_widget(win), app->scroll_bar);
  my_widget_unref(app->scroll_bar);
  my_scroll_view_set_scroll_bar(app->page_sv, app->scroll_bar);

  dxx_build_topbar(win, page, &app->topbar);
  dxx_topbar_set_nav_handler(&app->topbar, app_on_nav, app);
  strip = dxx_build_index_strip(page);
  my_widget_set_rect(strip, &(my_rect_t){10, DXX_TOPBAR_H + 8, 1300, 64});
  y = DXX_TOPBAR_H + 8 + 64 + 12;
  y += dxx_build_live_area(page, 10, y, 1300) + 12;
  ztpool = dxx_build_ztpool(wm, page, 1300);
  my_widget_set_rect(ztpool, &(my_rect_t){10, y, 1300, ztpool->rect.h});
  y += ztpool->rect.h + 12;
  footer = dxx_build_footer(page);
  my_widget_set_rect(footer, &(my_rect_t){10, y, 1300, 48});
  y += 48 + 8;
  my_scroll_view_set_content_height(app->page_sv, y);

  app->placeholder = dxx_placeholder_create(NULL, app_on_back, app);
  my_widget_set_rect(app->placeholder,
                     &(my_rect_t){0, DXX_TOPBAR_H, (int32_t)width,
                                  (int32_t)height - DXX_TOPBAR_H});
  my_widget_set_visible(app->placeholder, false);
  my_widget_add_child(my_window_widget(win), app->placeholder);
  my_widget_unref(app->placeholder);
  dxx_topbar_set_active(&app->topbar, "涨停表现");
  my_widget_invalidate(my_window_widget(win), NULL);
  return app;
}

void dxx_app_destroy(dxx_app_t *app) {
  if (app == NULL) {
    return;
  }
  dxx_topbar_destroy(&app->topbar);
  free(app);
}

my_widget_t *dxx_app_page(dxx_app_t *app) {
  return app != NULL ? (my_widget_t *)app->page_sv : NULL;
}
