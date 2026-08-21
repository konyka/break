/**
 * @file my_line_break.c
 * @brief Simplified line-break class lookup (M12d).
 */
#include "myr/my_line_break.h"

#include <stddef.h>

#include "myr/my_line_break_data.h"

my_line_break_class_t my_line_break_class(uint32_t cp) {
  size_t lo = 0, hi = sizeof(MY_LINE_BREAKS) / sizeof(MY_LINE_BREAKS[0]);
  while (lo < hi) {
    size_t mid = lo + (hi - lo) / 2;
    const my_lb_entry_t* e = &MY_LINE_BREAKS[mid];
    if (cp < e->lo) {
      hi = mid;
    } else if (cp > e->hi) {
      lo = mid + 1;
    } else {
      return (my_line_break_class_t)e->cls;
    }
  }
  return MY_LB_ID; /* gaps default to ideographic (break allowed) */
}
