/* Editor image decoding — see editor_image.h. */

#include "editor/editor_image.h"
#include "editor/editor_test_hooks.h"

#include <limits.h>
#include <stb_image.h>
#include <stdlib.h>
#include <string.h>

static bool image_dims_ok(int w, int h) {
    return w > 0 && h > 0 && (u32)w <= BREAK_EDITOR_IMAGE_MAX_DIM &&
           (u32)h <= BREAK_EDITOR_IMAGE_MAX_DIM;
}

bool break_editor_image_probe(const void *bytes, usize size, u32 *out_width,
                              u32 *out_height) {
    int w = 0, h = 0, comp = 0;
    if (bytes == NULL || size == 0u || size > (usize)INT_MAX ||
        out_width == NULL || out_height == NULL) {
        return false;
    }
    if (!stbi_info_from_memory((const stbi_uc *)bytes, (int)size, &w, &h,
                               &comp) ||
        !image_dims_ok(w, h)) {
        return false;
    }
    *out_width = (u32)w;
    *out_height = (u32)h;
    return true;
}

bool break_editor_image_decode(const void *bytes, usize size,
                               BreakEditorImage *out) {
    u32 w = 0, h = 0;
    int dw = 0, dh = 0, comp = 0;
    stbi_uc *pixels;
    if (out == NULL) {
        return false;
    }
    memset(out, 0, sizeof(*out));
    /* the header check runs first so an oversized image is never decoded */
    if (!break_editor_image_probe(bytes, size, &w, &h)) {
        return false;
    }
    pixels = stbi_load_from_memory((const stbi_uc *)bytes, (int)size, &dw,
                                   &dh, &comp, 4);
    if (pixels == NULL) {
        return false;
    }
    if ((u32)dw != w || (u32)dh != h) {
        stbi_image_free(pixels);
        return false;
    }
    out->width = w;
    out->height = h;
    out->rgba = pixels; /* stbi allocates with malloc (no STBI_MALLOC override) */
    return true;
}

void break_editor_image_free(BreakEditorImage *image) {
    if (image == NULL) {
        return;
    }
    stbi_image_free(image->rgba);
    memset(image, 0, sizeof(*image));
}

static bool ends_with_ci(const char *name, usize len, const char *ext) {
    usize el = strlen(ext);
    usize i;
    if (len <= el) {
        return false; /* needs a base name before the extension */
    }
    for (i = 0; i < el; i++) {
        char c = name[len - el + i];
        if (c >= 'A' && c <= 'Z') {
            c = (char)(c - 'A' + 'a');
        }
        if (c != ext[i]) {
            return false;
        }
    }
    return true;
}

bool break_editor_image_is_supported_name(const char *name) {
    static const char *const k_ext[] = {".png", ".jpg", ".jpeg", ".bmp",
                                        ".tga"};
    usize len;
    usize i;
    if (name == NULL) {
        return false;
    }
    len = strlen(name);
    for (i = 0; i < sizeof(k_ext) / sizeof(k_ext[0]); i++) {
        if (ends_with_ci(name, len, k_ext[i])) {
            return true;
        }
    }
    return false;
}

u32 break_editor_image_mip_count(u32 width, u32 height) {
    u32 m = width > height ? width : height, n = 0u;
    if (width == 0u || height == 0u) return 0u;
    while (m > 0u) {
        n++;
        m >>= 1u;
    }
    return n;
}

void break_editor_image_free_mips(BreakEditorImageMips *mips) {
    if (mips == NULL) return;
    for (u32 i = 1u; i < mips->count && i < BREAK_EDITOR_IMAGE_MAX_MIPS; i++) {
        free(mips->level[i]);
    }
    memset(mips, 0, sizeof(*mips));
}

bool break_editor_image_build_mips(const BreakEditorImage *image,
                                   BreakEditorImageMips *out) {
    u32 n;
    if (out == NULL) return false;
    memset(out, 0, sizeof(*out));
    if (image == NULL || image->rgba == NULL) return false;
    n = break_editor_image_mip_count(image->width, image->height);
    if (n == 0u || n > BREAK_EDITOR_IMAGE_MAX_MIPS) return false;
    out->width[0] = image->width;
    out->height[0] = image->height;
    out->level[0] = image->rgba;
    out->count = 1u;
    for (u32 l = 1u; l < n; l++) {
        u32 pw = out->width[l - 1u], ph = out->height[l - 1u];
        u32 w = pw > 1u ? pw / 2u : 1u, h = ph > 1u ? ph / 2u : 1u;
        const u8 *src = out->level[l - 1u];
        u8 *dst = (u8 *)break_editor_test_calloc((usize)w * h * 4u);
        if (dst == NULL) {
            break_editor_image_free_mips(out);
            return false;
        }
        for (u32 y = 0u; y < h; y++) {
            u32 y0 = y * 2u, y1 = y0 + 1u < ph ? y0 + 1u : y0;
            for (u32 x = 0u; x < w; x++) {
                u32 x0 = x * 2u, x1 = x0 + 1u < pw ? x0 + 1u : x0;
                for (u32 c = 0u; c < 4u; c++) {
                    u32 sum = src[(y0 * pw + x0) * 4u + c] +
                              src[(y0 * pw + x1) * 4u + c] +
                              src[(y1 * pw + x0) * 4u + c] +
                              src[(y1 * pw + x1) * 4u + c];
                    dst[(y * w + x) * 4u + c] = (u8)((sum + 2u) / 4u);
                }
            }
        }
        out->width[l] = w;
        out->height[l] = h;
        out->level[l] = dst;
        out->count = l + 1u;
    }
    return true;
}
