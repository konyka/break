/**
 * @file dxx_theme.c
 * @brief Site theme (M18b): CSS-driven via my_theme_load_css (default
 * theme underneath keeps every widget's built-in fallbacks). The rules
 * below are the site's palette expressed with type/class selectors;
 * widget-specific colors that are not theme-keyed (charts, badges, feed
 * keyword colors) stay inline in the views (noted).
 */
#include "dxx_theme.h"

#include "myui/my_css.h"

my_theme_t* dxx_theme_create(const my_allocator_t* allocator) {
  my_theme_t* t = my_theme_default_create(allocator);
  if (t == NULL) {
    return NULL;
  }
  my_theme_load_css(t,
                    /* white page, dark text */
                    "window { background-color: white } "
                    "label { background-color: white; color: #333333 } "
                    /* footer grey (class demo) */
                    "label.muted { color: #999999 } "
                    /* danger buttons (the share button carries
                     * class="danger"): site #D9534F, hover #C9302C */
                    ".danger { background-color: #D9534F; color: white } "
                    ".danger:hover { background-color: #C9302C }");
  return t;
}
