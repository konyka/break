/**
 * @file my_arabic_shape.h
 * @brief Arabic letter joining (shaping) to presentation forms (M11a).
 *
 * SheenBidi 3.0.0 has no shaping module, so myui implements the joining
 * rules itself: each Arabic letter is replaced by its isolated / final /
 * initial / medial presentation form (Arabic Presentation Forms-A/B)
 * based on the joining class of its logical neighbours (transparent
 * marks are skipped). Lam-Alef ligatures are formed in place when the
 * mandatory pair is present. Full OpenType GSUB remains outside this
 * module.
 * Data: my_arabic_shape_data.h (generated from the UCD).
 */
#ifndef MY_ARABIC_SHAPE_H
#define MY_ARABIC_SHAPE_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "myr/my_arabic_shape_data.h"

/** @brief Joining class of a codepoint (MY_ARABIC_JOIN_NONE outside the
 * Arabic blocks / for non-joining chars). */
my_arabic_join_t my_arabic_join_class(uint32_t cp);

/** @brief Presentation form for base given the join context, or base
 * itself when no such form exists. */
uint32_t my_arabic_form_for(uint32_t base, bool join_prev, bool join_next);

/** @brief Shape a logical-order codepoint array in place. Returns the visual
 * item count; Lam-Alef may compact two source codepoints into one item. */
size_t my_arabic_shape(uint32_t* cps, size_t len);

/** @brief Shape in place and preserve source coverage for every output item.
 * `logical_start` and `logical_span` are optional arrays with at least `len`
 * entries. On success, each output item covers the source range
 * [logical_start[i], logical_start[i] + logical_span[i]). */
size_t my_arabic_shape_with_map(uint32_t* cps, size_t len,
                                uint32_t* logical_start,
                                uint32_t* logical_span);

#endif /* MY_ARABIC_SHAPE_H */
