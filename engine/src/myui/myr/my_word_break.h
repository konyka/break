/**
 * @file my_word_break.h
 * @brief Allocation-free byte-space word boundaries (R662).
 *
 * Bounded subset: three codepoint classes — whitespace (ASCII
 * space/tab/CR/LF), word (A-Za-z0-9_ plus every non-ASCII codepoint), and
 * punctuation (the rest). The jump semantics follow the common editor
 * convention: right lands on the next word start, left on the current or
 * previous word start. Cluster alignment is inherent: combining marks are
 * word-class, so a cluster never straddles a class run.
 */
#ifndef MY_WORD_BREAK_H
#define MY_WORD_BREAK_H

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/** @brief Start of the word at or before `offset` (skipping whitespace
 * backward first). `text` holds `len` bytes of UTF-8 (need not be
 * NUL-terminated); `offset` must sit on a codepoint start (0..len). */
size_t my_word_break_left(const char* text, size_t len, size_t offset);

/** @brief Start of the next word after `offset` (clamped at `len`). */
size_t my_word_break_right(const char* text, size_t len, size_t offset);

#ifdef __cplusplus
}
#endif

#endif /* MY_WORD_BREAK_H */
