#pragma once

#include <platform/platform.h>

/* Select the output owning the largest window area. If a window is between
 * outputs while moving, use the closest output to keep DPI stable. */
static inline i32 platform_monitor_select(const MonitorInfo *monitors,
                                          u32 monitor_count, i32 window_x,
                                          i32 window_y, u32 window_width,
                                          u32 window_height) {
    i32 best = -1;
    u64 best_overlap = 0;
    u64 best_distance = UINT64_MAX;
    i64 window_left = window_x;
    i64 window_top = window_y;
    i64 window_right = window_left + window_width;
    i64 window_bottom = window_top + window_height;
    i64 center_x2 = window_left * 2 + window_width;
    i64 center_y2 = window_top * 2 + window_height;

    if (monitors == NULL || monitor_count == 0) return -1;
    for (u32 i = 0; i < monitor_count; i++) {
        const MonitorInfo *monitor = &monitors[i];
        i64 monitor_left = monitor->x;
        i64 monitor_top = monitor->y;
        i64 monitor_right = monitor_left + monitor->width;
        i64 monitor_bottom = monitor_top + monitor->height;
        i64 overlap_left = window_left > monitor_left ? window_left : monitor_left;
        i64 overlap_top = window_top > monitor_top ? window_top : monitor_top;
        i64 overlap_right = window_right < monitor_right ? window_right : monitor_right;
        i64 overlap_bottom = window_bottom < monitor_bottom ? window_bottom : monitor_bottom;
        u64 overlap = overlap_right > overlap_left && overlap_bottom > overlap_top
                          ? (u64)(overlap_right - overlap_left) *
                                (u64)(overlap_bottom - overlap_top)
                          : 0;
        i64 left2 = monitor_left * 2;
        i64 top2 = monitor_top * 2;
        i64 right2 = monitor_right * 2;
        i64 bottom2 = monitor_bottom * 2;
        i64 dx = center_x2 < left2 ? left2 - center_x2
                 : center_x2 > right2 ? center_x2 - right2 : 0;
        i64 dy = center_y2 < top2 ? top2 - center_y2
                 : center_y2 > bottom2 ? center_y2 - bottom2 : 0;
        u64 distance = (u64)dx + (u64)dy;

        if (best < 0 || overlap > best_overlap ||
            (overlap == best_overlap && overlap > 0 && monitor->primary &&
             !monitors[best].primary) ||
            (best_overlap == 0 && overlap == 0 && distance < best_distance) ||
            (best_overlap == 0 && overlap == 0 && distance == best_distance &&
             monitor->primary && !monitors[best].primary)) {
            best = (i32)i;
            best_overlap = overlap;
            best_distance = distance;
        }
    }
    return best;
}
