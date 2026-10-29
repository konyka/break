#include <core/string.h>
#include <locale.h>
#include <stdlib.h>
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

double break_strtod_c(const char *text, char **end) {
    char buf[256];
    usize map[256];
    char *buf_end = NULL;
    const struct lconv *lc = localeconv();
    const char *point = (lc != NULL && lc->decimal_point != NULL &&
                         lc->decimal_point[0] != '\0') ? lc->decimal_point : ".";
    usize point_len = strlen(point);
    usize i = 0, o = 0;
    double v;
    if (text == NULL) {
        if (end != NULL) *end = NULL;
        return 0.0;
    }
    if (point_len == 1 && point[0] == '.') return strtod(text, end);
    while ((text[i] == ' ' || text[i] == '\t' || text[i] == '\n' || text[i] == '\r' ||
            text[i] == '\f' || text[i] == '\v') && o + 1 < sizeof(buf)) {
        map[o] = i;
        buf[o++] = text[i++];
    }
    while (text[i] != '\0') {
        char ch = text[i];
        bool numeric = (ch >= '0' && ch <= '9') || ch == '.' || ch == '+' || ch == '-' ||
                       (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z');
        usize need = ch == '.' ? point_len : 1;
        if (!numeric || o + need >= sizeof(buf)) break;
        if (ch == '.') {
            memcpy(buf + o, point, point_len);
            for (usize k = 0; k < point_len; k++) map[o + k] = i;
            o += point_len;
        } else {
            map[o] = i;
            buf[o++] = ch;
        }
        i++;
    }
    buf[o] = '\0';
    v = strtod(buf, &buf_end);
    if (end != NULL) {
        usize used = (usize)(buf_end - buf);
        *end = (char *)text + (used < o ? map[used] : i);
    }
    return v;
}

float break_strtof_c(const char *text, char **end) {
    return (float)break_strtod_c(text, end);
}

void break_c_decimal(char *buf) {
    const struct lconv *lc = localeconv();
    const char *point;
    usize point_len;
    char *hit;
    if (buf == NULL || lc == NULL || lc->decimal_point == NULL) return;
    point = lc->decimal_point;
    point_len = strlen(point);
    if (point_len == 0 || (point_len == 1 && point[0] == '.')) return;
    while ((hit = strstr(buf, point)) != NULL) {
        *hit = '.';
        if (point_len > 1) memmove(hit + 1, hit + point_len, strlen(hit + point_len) + 1);
        buf = hit + 1;
    }
}
