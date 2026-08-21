/**
 * @file dxx_theme.h
 * @brief duanxianxia clone: site palette (M14b), values measured from the
 * site's index.css / inline styles (see docs/apps/duanxianxia.md).
 */
#ifndef DXX_THEME_H
#define DXX_THEME_H

#include "myui/my_window.h"

/* rgba32 (site hex + opaque alpha) */
#define DXX_COLOR_TOPBAR 0x444444FFu    /**< header background #444 */
#define DXX_COLOR_PRIMARY 0xE64C62FFu   /**< site accent red #E64C62 */
#define DXX_COLOR_FILTER_BG 0xEAF1FEFFu /**< filter panel bg #EAF1FE */
#define DXX_COLOR_BTN_BLUE 0x347DFAFFu  /**< action button #347DFA */
#define DXX_COLOR_DANGER 0xD9534FFFu    /**< danger button #D9534F */
#define DXX_COLOR_UP 0xFF0000FFu        /**< rise: site "color:red" */
#define DXX_COLOR_DOWN 0x008000FFu      /**< fall: site "color:green" */
#define DXX_COLOR_TEXT 0x333333FFu      /**< body text #333 */
#define DXX_COLOR_MUTED 0x999999FFu     /**< footer grey #999 */
#define DXX_COLOR_NAV_DIV 0x666666FFu   /**< topbar 1px divider */
#define DXX_COLOR_LINE 0xEEEEEEFFu      /**< card edge #eee (shadow fake) */
#define DXX_COLOR_WHITE 0xFFFFFFFFu
#define DXX_COLOR_NAV_HOVER 0x555555FFu /**< topbar item hover bg */

/** @brief Build the site theme (white window bg + widget defaults). */
my_theme_t* dxx_theme_create(const my_allocator_t* allocator);

#endif /* DXX_THEME_H */
