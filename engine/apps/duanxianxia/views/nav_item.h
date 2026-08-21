/**
 * @file nav_item.h
 * @brief duanxianxia clone: topbar text item (M14b) — colored text with
 * hover background and a "click" emitter event (press+release inside).
 */
#ifndef DXX_NAV_ITEM_H
#define DXX_NAV_ITEM_H

#include "myui/my_widget.h"

/**
 * @brief Create a nav item: text drawn in rgba_color at font_size,
 * vertically centered with 8px horizontal padding; while hovered a
 * hover_bg background is painted (0 alpha = none). Bold = fake bold
 * (1px double-draw). Emits "click".
 */
my_widget_t* dxx_nav_item_create(const my_allocator_t* allocator,
                                 const char* text, uint32_t rgba_color,
                                 bool bold, int32_t font_size,
                                 uint32_t hover_bg);

/** @brief Recolor the item text (navigation active highlight, M14d). */
void dxx_nav_item_set_color(my_widget_t* item, uint32_t rgba_color);

/**
 * @brief Estimated pixel width of text at font_size: CJK chars count
 * font_size, ASCII count font_size/2. For layout before a paint pass.
 */
int32_t dxx_text_estimate(const char* utf8, int32_t font_size);

#endif /* DXX_NAV_ITEM_H */
