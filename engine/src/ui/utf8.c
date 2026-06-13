#include <ui/utf8.h>

u32 utf8_decode(const char *s, u32 *out_cp) {
    const unsigned char *p = (const unsigned char *)s;
    unsigned char c = p[0];

    /* 1-byte ASCII */
    if (c < 0x80u) {
        *out_cp = c;
        return 1;
    }

    /* 2-byte sequence: 110xxxxx 10xxxxxx */
    if ((c & 0xE0u) == 0xC0u) {
        if ((p[1] & 0xC0u) != 0x80u) { *out_cp = UTF8_REPLACEMENT; return 1; }
        u32 cp = ((u32)(c & 0x1Fu) << 6) | (u32)(p[1] & 0x3Fu);
        if (cp < 0x80u) { *out_cp = UTF8_REPLACEMENT; return 1; } /* overlong */
        *out_cp = cp;
        return 2;
    }

    /* 3-byte sequence: 1110xxxx 10xxxxxx 10xxxxxx */
    if ((c & 0xF0u) == 0xE0u) {
        if ((p[1] & 0xC0u) != 0x80u || (p[2] & 0xC0u) != 0x80u) {
            *out_cp = UTF8_REPLACEMENT; return 1;
        }
        u32 cp = ((u32)(c & 0x0Fu) << 12) |
                 ((u32)(p[1] & 0x3Fu) << 6) |
                 (u32)(p[2] & 0x3Fu);
        if (cp < 0x800u) { *out_cp = UTF8_REPLACEMENT; return 1; } /* overlong */
        /* UTF-16 surrogate halves are not valid scalar values */
        if (cp >= 0xD800u && cp <= 0xDFFFu) { *out_cp = UTF8_REPLACEMENT; return 1; }
        *out_cp = cp;
        return 3;
    }

    /* 4-byte sequence: 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx */
    if ((c & 0xF8u) == 0xF0u) {
        if ((p[1] & 0xC0u) != 0x80u || (p[2] & 0xC0u) != 0x80u || (p[3] & 0xC0u) != 0x80u) {
            *out_cp = UTF8_REPLACEMENT; return 1;
        }
        u32 cp = ((u32)(c & 0x07u) << 18) |
                 ((u32)(p[1] & 0x3Fu) << 12) |
                 ((u32)(p[2] & 0x3Fu) << 6) |
                 (u32)(p[3] & 0x3Fu);
        if (cp < 0x10000u || cp > 0x10FFFFu) { *out_cp = UTF8_REPLACEMENT; return 1; }
        *out_cp = cp;
        return 4;
    }

    /* Lone continuation byte or invalid lead byte */
    *out_cp = UTF8_REPLACEMENT;
    return 1;
}

usize utf8_strlen(const char *s) {
    usize n = 0;
    while (*s) {
        u32 cp;
        s += utf8_decode(s, &cp);
        n++;
    }
    return n;
}
