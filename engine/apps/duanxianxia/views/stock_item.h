/**
 * @file stock_item.h
 * @brief duanxianxia clone: one stock entry of the zt-pool table (M14c):
 * market badge + name (state color) + [change%] + theme, hover
 * highlight, tooltip, click -> stock card dialog.
 */
#ifndef DXX_STOCK_ITEM_H
#define DXX_STOCK_ITEM_H

#include "../dxx_data.h"
#include "myui/my_window_manager.h"

#define DXX_STOCK_ITEM_HEIGHT 24

/** @brief Estimated item width (for the flow layout; pre-paint). */
int32_t dxx_stock_item_width(const dxx_stock_t* stock);

/** @brief Create a stock item (stock must outlive the widget — the
 * static snapshot table does). wm hosts the click dialog. */
my_widget_t* dxx_stock_item_create(const my_allocator_t* allocator,
                                   const dxx_stock_t* stock,
                                   my_window_manager_t* wm);

#endif /* DXX_STOCK_ITEM_H */
