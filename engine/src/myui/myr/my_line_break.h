/**
 * @file my_line_break.h
 * @brief Simplified line-break classes for word wrap (M12d, a UAX#14
 * practical subset).
 *
 * Classes (data: my_line_break_data.h, generated from UCD LineBreak via
 * awtk's libunibreak table):
 *  - MY_LB_AL: letters/digits/marks -- no break inside a run;
 *  - MY_LB_SP: ASCII space -- a break consumes it (space semantics of
 *    M10b: no visual line starts with whitespace);
 *  - MY_LB_HY: hyphen / soft hyphen -- break AFTER it;
 *  - MY_LB_ID: ideographic and everything else -- break allowed between
 *    chars (CJK word wrap);
 *  - MY_LB_NS: no-start (，。！？；：、）」』 etc.) -- a visual line may
 *    NOT start with it (break before it is forbidden);
 *  - MY_LB_OP: open bracket （「『 etc.) -- a visual line may NOT end
 *    with it (break after it is forbidden);
 *  - MY_LB_BK: hard breaks (\n etc.) -- handled by the physical-line
 *    logic, never reached by the table in practice.
 *
 * This is a SUBSET: dictionary breaking for SA and the full set of
 * locale-specific tailoring remain out of scope. The contextual helper
 * below covers combining marks, numeric punctuation, Hebrew quotes, regional
 * indicators, Unicode glue and emoji/joiner extensions so callers do not need
 * to duplicate those safety rules.
 */
#ifndef MY_LINE_BREAK_H
#define MY_LINE_BREAK_H

#include <stdbool.h>
#include <stdint.h>

typedef enum my_line_break_class_t {
  MY_LB_AL = 0, /**< letter/number run: no break inside */
  MY_LB_SP,     /**< space: break here, consumed */
  MY_LB_HY,     /**< hyphen: break after */
  MY_LB_ID,     /**< ideographic / default: break allowed */
  MY_LB_NS,     /**< no-start punctuation: line must not start with it */
  MY_LB_OP,     /**< open bracket: line must not end with it */
  MY_LB_BK      /**< hard break (physical line, outside the table) */
} my_line_break_class_t;

/** @brief Simplified line-break class of a codepoint (binary search,
 * default MY_LB_ID for gaps in the table). */
my_line_break_class_t my_line_break_class(uint32_t cp);

/** @brief Whether a line break is allowed between adjacent codepoints. */
bool my_line_break_allowed(uint32_t prev_cp, uint32_t cur_cp);

#endif /* MY_LINE_BREAK_H */
