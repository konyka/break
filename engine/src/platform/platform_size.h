#pragma once
#include <core/types.h>
#include <platform/wayland_output.h> /* wl_out_drawable_dimension 的唯一实现源 */

#if defined(__GNUC__) || defined(__clang__)
#define PLATFORM_SIZE_INLINE static inline __attribute__((unused))
#else
#define PLATFORM_SIZE_INLINE static inline
#endif

/* 尺寸语义契约（本文件是这些规则的唯一实现源，window_*.c 只准调用）：
 *  - Win32 / X11：事件坐标（WM_SIZE / ConfigureNotify）即 drawable 物理像素，
 *    drawable == event，即使 scale != 1；logical 由 drawable 反推。
 *  - Wayland / Cocoa：事件坐标是 logical（xdg_toplevel configure 的 w/h、
 *    NSView bounds 的 points），drawable = logical * scale（物理像素）。
 * 两个方向的「谁是输入」不得互换。 */

/* Win32：PMv2 下 WM_SIZE 的 LOWORD/HIWORD 就是物理像素
 *（window_win32.c:302-305 写入 p->width/height；get_drawable :711-714 原样返回）。 */
PLATFORM_SIZE_INLINE void platform_size_win32(u32 event_w, u32 event_h,
                                              f32 content_scale,
                                              u32 *out_logical_w,
                                              u32 *out_logical_h,
                                              u32 *out_drawable_w,
                                              u32 *out_drawable_h) {
    f32 scale = content_scale > 0.0f ? content_scale : 1.0f;
    if (out_drawable_w != NULL) *out_drawable_w = event_w;
    if (out_drawable_h != NULL) *out_drawable_h = event_h;
    if (out_logical_w != NULL) *out_logical_w = (u32)((f32)event_w / scale + 0.5f);
    if (out_logical_h != NULL) *out_logical_h = (u32)((f32)event_h / scale + 0.5f);
}

/* X11：ConfigureNotify 的 width/height 即 drawable（window_x11.c:1094-1098）；
 * logical = ceil(drawable / scale_factor)（既有公式 :1183-1187，逐位保留）。 */
PLATFORM_SIZE_INLINE void platform_size_x11(u32 event_w, u32 event_h,
                                            u32 scale_factor,
                                            u32 *out_logical_w,
                                            u32 *out_logical_h,
                                            u32 *out_drawable_w,
                                            u32 *out_drawable_h) {
    u32 scale = scale_factor > 0u ? scale_factor : 1u;
    if (out_drawable_w != NULL) *out_drawable_w = event_w;
    if (out_drawable_h != NULL) *out_drawable_h = event_h;
    if (out_logical_w != NULL) *out_logical_w = (event_w + scale - 1u) / scale;
    if (out_logical_h != NULL) *out_logical_h = (event_h + scale - 1u) / scale;
}

/* Wayland：xdg_toplevel configure 的 w/h 是 logical（:842-852）；
 * drawable 经 wl_out_drawable_dimension 换算（既有调用 :2033-2037）。 */
PLATFORM_SIZE_INLINE void platform_size_wayland(u32 logical_w, u32 logical_h,
                                                u32 content_scale_120,
                                                u32 *out_logical_w,
                                                u32 *out_logical_h,
                                                u32 *out_drawable_w,
                                                u32 *out_drawable_h) {
    if (out_logical_w != NULL) *out_logical_w = logical_w;
    if (out_logical_h != NULL) *out_logical_h = logical_h;
    if (out_drawable_w != NULL)
        *out_drawable_w = wl_out_drawable_dimension(logical_w, content_scale_120);
    if (out_drawable_h != NULL)
        *out_drawable_h = wl_out_drawable_dimension(logical_h, content_scale_120);
}

/* Cocoa：view bounds 是 logical points（cocoa_update_drawable_size :339-351）；
 * drawable = round(points * backing_scale)。 */
PLATFORM_SIZE_INLINE void platform_size_cocoa(u32 point_w, u32 point_h,
                                              f32 backing_scale,
                                              u32 *out_logical_w,
                                              u32 *out_logical_h,
                                              u32 *out_drawable_w,
                                              u32 *out_drawable_h) {
    f32 scale = backing_scale > 0.0f ? backing_scale : 1.0f;
    if (out_logical_w != NULL) *out_logical_w = point_w;
    if (out_logical_h != NULL) *out_logical_h = point_h;
    if (out_drawable_w != NULL)
        *out_drawable_w = (u32)((f32)point_w * scale + 0.5f);
    if (out_drawable_h != NULL)
        *out_drawable_h = (u32)((f32)point_h * scale + 0.5f);
}

#undef PLATFORM_SIZE_INLINE
