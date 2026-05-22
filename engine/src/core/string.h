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
