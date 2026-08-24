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

static bool is_non_break_extension(uint32_t cp) {
  return (cp >= 0xFE00u && cp <= 0xFE0Fu) ||
         (cp >= 0xE0100u && cp <= 0xE01EFu) ||
         (cp >= 0x1F3FBu && cp <= 0x1F3FFu) ||
         (cp >= 0xE0020u && cp <= 0xE007Fu) || cp == 0x200Du;
}

static bool is_non_break_glue(uint32_t cp) {
  return cp == 0x00A0u || cp == 0x2007u || cp == 0x202Fu ||
         cp == 0x2060u;
}

static bool is_regional_indicator(uint32_t cp) {
  return cp >= 0x1F1E6u && cp <= 0x1F1FFu;
}

static bool is_decimal_digit(uint32_t cp) {
  return (cp >= '0' && cp <= '9') ||
         (cp >= 0x0660u && cp <= 0x0669u) ||
         (cp >= 0x06F0u && cp <= 0x06F9u) ||
         (cp >= 0xFF10u && cp <= 0xFF19u);
}

static bool is_decimal_separator(uint32_t cp) {
  return cp == '.' || cp == ',' || cp == 0x066Bu || cp == 0x066Cu ||
         cp == 0xFF0Eu || cp == 0xFF0Cu;
}

static bool is_hebrew_letter(uint32_t cp) {
  return (cp >= 0x05D0u && cp <= 0x05EAu) ||
         (cp >= 0x05F0u && cp <= 0x05F2u);
}

static bool is_hebrew_quote(uint32_t cp) {
  return cp == '\'' || cp == '"' || cp == 0x05F3u || cp == 0x05F4u;
}

bool my_line_break_allowed(uint32_t prev_cp, uint32_t cur_cp) {
  my_line_break_class_t prev = my_line_break_class(prev_cp);
  my_line_break_class_t cur = my_line_break_class(cur_cp);

  if (is_combining_mark(cur_cp)) {
    return false;
  }
  if (is_non_break_extension(prev_cp) || is_non_break_extension(cur_cp)) {
    return false;
  }
  if (is_non_break_glue(prev_cp) || is_non_break_glue(cur_cp)) {
    return false;
  }
  if ((is_hebrew_letter(prev_cp) && is_hebrew_quote(cur_cp)) ||
      (is_hebrew_quote(prev_cp) && is_hebrew_letter(cur_cp))) {
    return false;
  }
  if (is_decimal_separator(cur_cp) && is_decimal_digit(prev_cp)) {
    return false;
  }
  if (is_decimal_separator(prev_cp) && is_decimal_digit(cur_cp)) {
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
