#pragma once
#include <core/types.h>

/* ---- String Slice (non-zero-terminated) ---- */

typedef struct {
    const char *data;
    usize       len;
} Str;

/* Constructors */
#define STR(literal) ((Str){literal, sizeof(literal) - 1})

static inline Str str_from_c(const char *s) {
    usize len = 0;
    while (s[len]) len++;
    return (Str){s, len};
}

/* Comparison */
bool str_eq(Str a, Str b);
bool str_eq_c(Str a, const char *b);

/* Search */
Str  str_slice(Str s, usize start, usize end);
i32  str_find_char(Str s, char c);
u64  str_hash(Str s);

/* Copy (caller provides buffer) */
Str  str_copy(Str s, char *buf, usize buf_size);

/* strtod/strtof that always use '.' as the decimal point, whatever
 * LC_NUMERIC the host set. The number-shaped prefix of text (at most 255
 * bytes; leading whitespace allowed) is parsed; *end, when non-NULL, points
 * into text after the consumed characters. A locale ',' is never accepted. */
double break_strtod_c(const char *text, char **end);
float  break_strtof_c(const char *text, char **end);

/* Rewrites the locale decimal point that snprintf("%f"/"%g") wrote into the
 * NUL-terminated buf back to '.', in place (every occurrence). */
void break_c_decimal(char *buf);
