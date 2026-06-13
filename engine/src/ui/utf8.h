#pragma once
#include <core/types.h>

/* UTF-8 replacement character emitted for malformed input. */
#define UTF8_REPLACEMENT 0xFFFDu

/* Decode a single codepoint from a NUL-terminated UTF-8 string.
 * Writes the codepoint to *out_cp and returns the number of bytes consumed
 * (always >= 1 so callers cannot get stuck). Malformed or truncated
 * sequences consume one byte and yield UTF8_REPLACEMENT. */
u32 utf8_decode(const char *s, u32 *out_cp);

/* Count the number of codepoints in a NUL-terminated UTF-8 string. */
usize utf8_strlen(const char *s);
