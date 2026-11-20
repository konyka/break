#pragma once

#include <core/types.h>
#include <rhi/rhi.h>

typedef struct {
    void *window;
    void *context;
    bool enabled;
    bool buffers_created;
    u32 width;
    u32 height;
    u64 post_count;
    void *capture_pixmap;
    void *capture_buffer;
    u8 *capture_pixels;
    int capture_stride;
    u32 capture_width;
    u32 capture_height;
    /* Damage posted to the window but not yet confirmed displayed: kept
     * across failed presents so the next successful post reports the full
     * outstanding region (bounding box, x/y/w/h). */
    i32 saved_damage[4];
    bool has_saved_damage;
    /* A dequeued render buffer that was posted with SCREEN_EXPLICIT_ENQUEUE
     * (or held after a failed post) but not yet accepted back by screen;
     * released via screen_enqueue_render_buffer before the next dequeue. */
    void *outstanding_buffer;
} VKQnxScreenPost;

bool vk_qnx_screen_post_init(VKQnxScreenPost *post, void *window, void *context);
void vk_qnx_screen_post_shutdown(VKQnxScreenPost *post);
bool vk_qnx_screen_post_present(VKQnxScreenPost *post, RHIDevice *dev);
