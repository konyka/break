/**
 * @file my_grapheme.h
 * @brief Allocation-free byte-space grapheme-cluster boundaries (R659).
 *
 * Bounded UAX#29 subset, the same rules the layout cursor boundaries use
 * (R657/R658): GB9 (combining marks and ZWJ attach forward), GB11 bounded
 * (a pictograph right after a ZWJ joins the chain), GB12/13 (regional
 * indicators cluster in pairs). Text widgets whose cursor walk never
 * builds a layout consume this instead of per-codepoint stepping.
 */
#ifndef MY_GRAPHEME_H
#define MY_GRAPHEME_H

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/** @brief Nearest cluster boundary strictly before `offset`.
 * `text` holds `len` bytes of UTF-8 (need not be NUL-terminated);
 * `offset` must sit on a codepoint start (0..len). Returns 0 at the
 * string start. */
size_t my_grapheme_boundary_left(const char* text, size_t len,
                                 size_t offset);

/** @brief Nearest cluster boundary strictly after `offset` (clamped at
 * `len`). */
size_t my_grapheme_boundary_right(const char* text, size_t len,
                                  size_t offset);

#ifdef __cplusplus
}
#endif

#endif /* MY_GRAPHEME_H */
