/**
 * @file views.h
 * @brief duanxianxia clone: section builders (M14b).
 */
#ifndef DXX_VIEWS_H
#define DXX_VIEWS_H

#include "../dxx_data.h"
#include "myui/my_window_manager.h"
#include "myui/widgets/my_menu.h"
#include "myui/widgets/my_scroll_view.h"

#define DXX_MENU_COUNT 4
#define DXX_TOPBAR_H 50

/** @brief Navigation callback (M14d): name = menu item / flat item /
 * "首页" (logo); the app decides what to show. */
typedef void (*dxx_nav_cb)(void* ctx, const char* name);

/** @brief Topbar handle: the bar widget + the dropdown menu models
 * (owned by the caller; destroy with dxx_topbar_destroy). The struct
 * must outlive the bar (trigger callbacks reference it). */
typedef struct dxx_topbar_t {
  my_widget_t* bar;
  my_menu_t* menus[DXX_MENU_COUNT];
  dxx_nav_cb nav_cb;   /**< NULL = log only */
  void* nav_ctx;
  struct dxx_trigger_t {
    my_window_t* win;
    struct dxx_topbar_t* tb;
    int menu_index;      /**< >= 0: dropdown; -1: flat item */
    my_widget_t* anchor; /**< weak: popup position */
    const char* log_name;
    uint32_t base_color; /**< text color when inactive */
  } triggers[16];
} dxx_topbar_t;

/** @brief Build the 50px #444 topbar into parent (full parent width). */
void dxx_build_topbar(my_window_t* win, my_widget_t* parent,
                      dxx_topbar_t* out);

/** @brief Destroy the dropdown menu models (not the bar widget). */
void dxx_topbar_destroy(dxx_topbar_t* tb);

/** @brief Set the navigation handler (M14d). */
void dxx_topbar_set_nav_handler(dxx_topbar_t* tb, dxx_nav_cb cb, void* ctx);

/** @brief Highlight the trigger owning `name` (menu item or flat item)
 * in the primary color; all others revert to their base color. */
void dxx_topbar_set_active(dxx_topbar_t* tb, const char* name);

/** @brief Build the 12-column index strip into parent (strip rect set
 * by the caller after attaching; columns reflow on layout). */
my_widget_t* dxx_build_index_strip(my_widget_t* parent);

/** @brief Build the two-line footer into parent (rect by the caller). */
my_widget_t* dxx_build_footer(my_widget_t* parent);

/** @brief Build the two-column live area into parent at (x, y), total
 * width w (750 left + 20 gap + 530 right). @return the area height. */
int32_t dxx_build_live_area(my_widget_t* parent, int32_t x, int32_t y,
                            int32_t w);

/** @brief Build the 涨停股票池 table into parent with width w; the
 * table's own rect height is set to the measured content height. */
my_widget_t* dxx_build_ztpool(my_window_manager_t* wm, my_widget_t* parent,
                              int32_t w);

/** @brief Override the share-image PNG path (default ztpool_share.png). */
void dxx_ztpool_set_share_path(my_widget_t* table, const char* path);

/** @brief Feed list (time + keyword-colored rows) in a scroll_view
 * (M15; shared by the live cards and the emotion card). */
my_scroll_view_t* dxx_feed_list_create(const dxx_live_item_t* items,
                                       int count, int32_t w);

/** @brief Emotion-live card with stats grid + charts above the feed
 * (M15). */
my_widget_t* dxx_build_emotion_card(my_widget_t* parent, int32_t x, int32_t y,
                                    int32_t w, int32_t h);

#endif /* DXX_VIEWS_H */
