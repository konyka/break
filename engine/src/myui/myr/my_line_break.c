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

static bool is_combining_mark(uint32_t cp) {
  return (cp >= 0x0300u && cp <= 0x036Fu) ||
         (cp >= 0x1AB0u && cp <= 0x1AFFu) ||
         (cp >= 0x1DC0u && cp <= 0x1DFFu) ||
         (cp >= 0x20D0u && cp <= 0x20FFu) ||
         (cp >= 0xFE20u && cp <= 0xFE2Fu);
}

static bool is_regional_indicator(uint32_t cp) {
  return cp >= 0x1F1E6u && cp <= 0x1F1FFu;
}

static bool is_ascii_digit(uint32_t cp) {
  return cp >= '0' && cp <= '9';
}

bool my_line_break_allowed(uint32_t prev_cp, uint32_t cur_cp) {
  my_line_break_class_t prev = my_line_break_class(prev_cp);
  my_line_break_class_t cur = my_line_break_class(cur_cp);

  if (is_combining_mark(cur_cp)) {
    return false;
  }
  if ((cur_cp == '.' || cur_cp == ',') && is_ascii_digit(prev_cp)) {
    return false;
  }
  if ((prev_cp == '.' || prev_cp == ',') && is_ascii_digit(cur_cp)) {
    return false;
  }
  if (is_regional_indicator(prev_cp) && is_regional_indicator(cur_cp)) {
    return false;
  }
  if (cur == MY_LB_SP) {
    return true;
  }
  if (cur == MY_LB_NS) {
    return false;
  }
  if (prev == MY_LB_SP || prev == MY_LB_HY) {
    return true;
  }
  if (cur == MY_LB_HY || prev == MY_LB_OP) {
    return false;
  }
  if (prev == MY_LB_AL && cur == MY_LB_AL) {
    return false;
  }
  return true;
}
