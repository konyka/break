/* Editor image decoding — see editor_image.h. */

#include "editor/editor_image.h"

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
