#include <core/string.h>
#include <string.h>

bool str_eq(Str a, Str b) {
    if (a.len != b.len) return false;
    return a.data == b.data || memcmp(a.data, b.data, a.len) == 0;
}

bool str_eq_c(Str a, const char *b) {
    return str_eq(a, str_from_c(b));
}

Str str_slice(Str s, usize start, usize end) {
    if (end > s.len) end = s.len;
    if (start > end) start = end;
    return (Str){s.data + start, end - start};
}

i32 str_find_char(Str s, char c) {
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
    usize len = s.len < buf_size - 1 ? s.len : buf_size - 1;
    memcpy(buf, s.data, len);
    buf[len] = '\0';
    return (Str){buf, len};
}
