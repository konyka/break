#ifndef BREAK_EDITOR_IMAGE_H
#define BREAK_EDITOR_IMAGE_H

/* Editor image decoding for the asset-browser preview: pure CPU, no RHI.
 *
 * probe reads only the header (cheap; safe on a worker thread) and decode
 * produces tightly packed RGBA8 rows, top row first. Both reject a zero or
 * a > BREAK_EDITOR_IMAGE_MAX_DIM side, so the largest decode is bounded
 * (4096 * 4096 * 4 = 64 MiB). Formats are whatever stb_image recognises;
 * is_supported_name lists the extensions the browser offers to preview. */

#include <core/types.h>

#define BREAK_EDITOR_IMAGE_MAX_DIM 4096u

typedef struct BreakEditorImage {
    u32 width;
    u32 height;
    u8 *rgba; /* owned; width * height * 4 bytes */
} BreakEditorImage;

bool break_editor_image_probe(const void *bytes, usize size, u32 *out_width,
                              u32 *out_height);
/* On success *out owns the pixels (free with break_editor_image_free); on
 * failure *out is zeroed. */
bool break_editor_image_decode(const void *bytes, usize size,
                               BreakEditorImage *out);
void break_editor_image_free(BreakEditorImage *image);
/* Mip chain for an RGBA8 image: levels halve each side (rounding down,
 * never below 1) to 1x1. mip_count(w, h) = floor(log2(max(w, h))) + 1, 0
 * for a zero side. build_mips box-filters each level from the previous one
 * (2x2 average, the footprint clamped at odd edges); level 0 borrows the
 * image pixels, levels 1.. are owned and released by free_mips. On failure
 * (NULL / empty image, OOM) *out is zeroed. */
#define BREAK_EDITOR_IMAGE_MAX_MIPS 13u /* 4096 -> 1 */
typedef struct BreakEditorImageMips {
    u32 count;
    u32 width[BREAK_EDITOR_IMAGE_MAX_MIPS];
    u32 height[BREAK_EDITOR_IMAGE_MAX_MIPS];
    u8 *level[BREAK_EDITOR_IMAGE_MAX_MIPS];
} BreakEditorImageMips;
u32 break_editor_image_mip_count(u32 width, u32 height);
bool break_editor_image_build_mips(const BreakEditorImage *image,
                                   BreakEditorImageMips *out);
void break_editor_image_free_mips(BreakEditorImageMips *mips);
/* Case-insensitive: .png .jpg .jpeg .bmp .tga. NULL -> false. */
bool break_editor_image_is_supported_name(const char *name);

#endif /* BREAK_EDITOR_IMAGE_H */
