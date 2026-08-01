#include <core/string.h>
#include <string.h>

bool str_eq(Str a, Str b) {
    if (a.len != b.len) return false;
    /* R419: memcmp with NULL data is UB even when len==0 — equal-length empty
     * slices are trivially equal (pointer-equal case kept for clarity). */
    if (a.len == 0) return true;
    return a.data == b.data || memcmp(a.data, b.data, a.len) == 0;
}

bool str_eq_c(Str a, const char *b) {
    return str_eq(a, str_from_c(b));
}

Str str_slice(Str s, usize start, usize end) {
    /* R420: s.data + start is pointer arithmetic on NULL (UB) even with
     * start==0 — return the empty slice without touching the pointer. */
    if (!s.data || s.len == 0) return (Str){NULL, 0};
    if (end > s.len) end = s.len;
    if (start > end) start = end;
    return (Str){s.data + start, end - start};
}

i32 str_find_char(Str s, char c) {
    /* R424: memchr(NULL, c, 0) is strict UB — bail on a NULL data pointer. */
    if (!s.data) return -1;
    const void *p = memchr(s.data, c, s.len);
    if (!p) return -1;
    return (i32)((const char *)p - s.data);
}

u64 str_hash(Str s) {
    u64 h = 14695981039346656037ULL;
    for (usize i = 0; i < s.len; i++) {
        h ^= (u64)(u8)s.data[i];
        h *= 1099511628211ULL;
    }
    return h;
}

Str str_copy(Str s, char *buf, usize buf_size) {
    /* R109-1: Guard against buf_size == 0 — unsigned underflow in
     * buf_size - 1 would wrap to SIZE_MAX and bypass the length clamp. */
    if (buf_size == 0) return (Str){buf, 0};
    usize len = s.len < buf_size - 1 ? s.len : buf_size - 1;
    /* R419: memcpy with NULL s.data is UB even when len==0. */
    if (len > 0) memcpy(buf, s.data, len);
    buf[len] = '\0';
    return (Str){buf, len};
}
