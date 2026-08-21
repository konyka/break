/**
 * @file my_arabic_shape.h
 * @brief Arabic letter joining (shaping) to presentation forms (M11a).
 *
 * SheenBidi 3.0.0 has no shaping module, so myui implements the joining
 * rules itself: each Arabic letter is replaced by its isolated / final /
 * initial / medial presentation form (Arabic Presentation Forms-A/B)
 * based on the joining class of its logical neighbours (transparent
 * marks are skipped). The mapping is 1:1 and done in place. Lam-Alef
 * ligatures are NOT formed (TODO; fonts normally ligate via GSUB).
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

/** @brief Shape a logical-order codepoint array in place (1:1 mapping).
 * Returns len. */
size_t my_arabic_shape(uint32_t* cps, size_t len);

#endif /* MY_ARABIC_SHAPE_H */
