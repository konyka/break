#include "rhi_vk_screen_post.h"

#if defined(ENGINE_PLATFORM_QNX) && defined(ENGINE_QNX_SCREEN)

#include <core/log.h>
#include <errno.h>
#include <limits.h>
#include <rhi/rhi_backend_internal.h>
#include <screen/screen.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool vk_qnx_screen_post_init(VKQnxScreenPost *post, void *window, void *context) {
    if (post == NULL || window == NULL || context == NULL) return false;
    memset(post, 0, sizeof(*post));
    post->window = window;
    post->context = context;
    post->enabled = true;
    return true;
}

static bool vk_qnx_screen_post_prepare(VKQnxScreenPost *post, u32 width, u32 height) {
    int size[2] = { (int)width, (int)height };
    if (post->buffers_created && post->width == width && post->height == height) {
        return true;
    }
    if (post->buffers_created) {
        if (screen_destroy_window_buffers((screen_window_t)post->window) != 0) return false;
        post->buffers_created = false;
    }
    if (screen_set_window_property_iv((screen_window_t)post->window,
                                      SCREEN_PROPERTY_BUFFER_SIZE, size) != 0) {
        return false;
    }
    if (screen_create_window_buffers((screen_window_t)post->window, 1) != 0) {
        (void)screen_destroy_window_buffers((screen_window_t)post->window);
        return false;
    }
    post->buffers_created = true;
    post->width = width;
    post->height = height;
    return true;
}

static void vk_qnx_screen_post_capture_destroy(VKQnxScreenPost *post) {
    if (post->capture_pixmap != NULL) {
        (void)screen_destroy_pixmap((screen_pixmap_t)post->capture_pixmap);
    }
    post->capture_pixmap = NULL;
    post->capture_buffer = NULL;
    post->capture_pixels = NULL;
    post->capture_stride = 0;
    post->capture_width = 0;
    post->capture_height = 0;
}

static bool vk_qnx_screen_post_capture_prepare(VKQnxScreenPost *post,
                                                u32 width, u32 height) {
    if (post->capture_pixmap != NULL && post->capture_width == width &&
        post->capture_height == height) {
        return true;
    }
    vk_qnx_screen_post_capture_destroy(post);
    screen_pixmap_t pixmap = NULL;
    if (screen_create_pixmap(&pixmap, (screen_context_t)post->context) != 0) return false;
    int size[2] = { (int)width, (int)height };
    int format = SCREEN_FORMAT_RGBA8888;
    int usage = SCREEN_USAGE_READ | SCREEN_USAGE_WRITE | SCREEN_USAGE_NATIVE;
    post->capture_pixmap = pixmap;
    if (screen_set_pixmap_property_iv(pixmap, SCREEN_PROPERTY_BUFFER_SIZE, size) != 0 ||
        screen_set_pixmap_property_iv(pixmap, SCREEN_PROPERTY_FORMAT, &format) != 0 ||
        screen_set_pixmap_property_iv(pixmap, SCREEN_PROPERTY_USAGE, &usage) != 0 ||
        screen_create_pixmap_buffer(pixmap) != 0 ||
        screen_get_pixmap_property_pv(pixmap, SCREEN_PROPERTY_RENDER_BUFFERS,
                                      &post->capture_buffer) != 0 ||
        screen_get_buffer_property_pv((screen_buffer_t)post->capture_buffer,
                                      SCREEN_PROPERTY_POINTER,
                                      (void **)&post->capture_pixels) != 0 ||
        screen_get_buffer_property_iv((screen_buffer_t)post->capture_buffer,
                                      SCREEN_PROPERTY_STRIDE,
                                      &post->capture_stride) != 0 ||
        post->capture_pixels == NULL || post->capture_stride < (int)(width * 4u)) {
        vk_qnx_screen_post_capture_destroy(post);
        return false;
    }
    post->capture_width = width;
    post->capture_height = height;
    return true;
}

void vk_qnx_screen_post_shutdown(VKQnxScreenPost *post) {
    if (post == NULL) return;
    vk_qnx_screen_post_capture_destroy(post);
    if (post->buffers_created) {
        (void)screen_destroy_window_buffers((screen_window_t)post->window);
    }
    memset(post, 0, sizeof(*post));
}

static bool vk_qnx_screen_post_write_ppm(const char *path, const u8 *pixels,
                                         int stride, u32 width, u32 height) {
    if (path == NULL) return true;
    FILE *file = fopen(path, "wb");
    if (file == NULL) return false;
    bool ok = fprintf(file, "P6\n%u %u\n255\n", width, height) > 0;
    for (u32 y = 0; ok && y < height; ++y) {
        const u8 *row = pixels + (usize)y * (usize)stride;
        for (u32 x = 0; ok && x < width; ++x) {
            ok = fwrite(row + (usize)x * 4u, 1, 3, file) == 3;
        }
    }
    if (fclose(file) != 0) ok = false;
    return ok;
}

bool vk_qnx_screen_post_present(VKQnxScreenPost *post, RHIDevice *dev) {
    if (post == NULL || dev == NULL || !post->enabled) return false;
    const u32 width = dev->width;
    const u32 height = dev->height;
    if (width == 0 || height == 0 || width > (u32)INT_MAX || height > (u32)INT_MAX ||
        width > SIZE_MAX / 4u / height) return false;
    const usize bytes = (usize)width * height * 4u;

    /* Recover a buffer the previous present could not hand back (its enqueue
     * failed or a verified frame never completed). Releasing it first keeps
     * the next dequeue from blocking on a buffer that is still outstanding. */
    if (post->outstanding_buffer != NULL) {
        if (screen_enqueue_render_buffer((screen_buffer_t)post->outstanding_buffer) == 0) {
            post->outstanding_buffer = NULL;
        }
    }

    /* Merge the damage still pending from earlier failed posts with the
     * damage requested for this frame into one bounding box (x, y, w, h). */
    i32 damage[4] = { 0, 0, 0, 0 };
    bool has_damage = false;
    if (post->has_saved_damage) {
        damage[0] = post->saved_damage[0];
        damage[1] = post->saved_damage[1];
        damage[2] = post->saved_damage[2];
        damage[3] = post->saved_damage[3];
        has_damage = true;
    }
    if (dev->frame_damage_requested) {
        for (u32 i = 0; i < dev->frame_damage_count &&
                        i < (u32)RHI_MAX_PRESENT_DAMAGE_RECTS; ++i) {
            const RHIPresentRect *rect = &dev->frame_damage[i];
            if (rect->w == 0u || rect->h == 0u) continue;
            const i32 x2 = rect->x + (i32)rect->w;
            const i32 y2 = rect->y + (i32)rect->h;
            if (!has_damage) {
                damage[0] = rect->x;
                damage[1] = rect->y;
                damage[2] = (i32)rect->w;
                damage[3] = (i32)rect->h;
                has_damage = true;
            } else {
                const i32 ex2 = damage[0] + damage[2];
                const i32 ey2 = damage[1] + damage[3];
                const i32 nx = damage[0] < rect->x ? damage[0] : rect->x;
                const i32 ny = damage[1] < rect->y ? damage[1] : rect->y;
                const i32 nx2 = ex2 > x2 ? ex2 : x2;
                const i32 ny2 = ey2 > y2 ? ey2 : y2;
                damage[0] = nx;
                damage[1] = ny;
                damage[2] = nx2 - nx;
                damage[3] = ny2 - ny;
            }
        }
    }

    const char *stage = "buffer_prepare";
    bool ok = vk_qnx_screen_post_prepare(post, width, height);

    screen_buffer_t buffer = NULL;
    if (ok) {
        stage = "dequeue_window_render_buffer";
        ok = screen_dequeue_window_render_buffer(&buffer, (screen_window_t)post->window,
                                                 SCREEN_DONT_BLOCK) == 0 && buffer != NULL;
    }
    u8 *screen_pixels = NULL;
    int stride = 0;
    int actual_size[2] = { 0, 0 };
    if (ok) {
        stage = "buffer_pointer_stride";
        ok = screen_get_buffer_property_pv(buffer, SCREEN_PROPERTY_POINTER,
                                           (void **)&screen_pixels) == 0 &&
             screen_get_buffer_property_iv(buffer, SCREEN_PROPERTY_STRIDE, &stride) == 0 &&
             screen_get_buffer_property_iv(buffer, SCREEN_PROPERTY_BUFFER_SIZE,
                                           actual_size) == 0 &&
             screen_pixels != NULL && stride >= (int)(width * 4u) &&
             actual_size[0] == (int)width && actual_size[1] == (int)height;
    }
    if (ok) stage = "readback_allocation";
    u8 *readback = ok ? (u8 *)malloc(bytes) : NULL;
    if (ok && readback == NULL) ok = false;
    if (ok) {
        stage = "rhi_screenshot";
        ok = rhi_screenshot(dev, 0, 0, width, height, readback, bytes);
    }
    if (ok) {
        for (u32 y = 0; y < height; ++y) {
            memcpy(screen_pixels + (usize)y * (usize)stride,
                   readback + (usize)y * width * 4u, (usize)width * 4u);
        }
    }

    const bool verify = ok && post->post_count == 0;
    bool posted = false;
    if (ok) {
        stage = "screen_post_window";
        const int flags = verify ? (SCREEN_EXPLICIT_ENQUEUE | SCREEN_DONT_BLOCK)
                                 : SCREEN_DONT_BLOCK;
        ok = screen_post_window((screen_window_t)post->window, buffer,
                                has_damage ? 1 : 0, has_damage ? damage : NULL,
                                flags) == 0;
        posted = ok;
    }
    if (ok && verify) {
        stage = "capture_pixmap_prepare";
        ok = vk_qnx_screen_post_capture_prepare(post, width, height);
        if (ok) {
            stage = "screen_read_window";
            ok = screen_read_window((screen_window_t)post->window,
                                    (screen_buffer_t)post->capture_buffer,
                                    0, NULL, 0) == 0;
        }
        if (ok) {
            stage = "pixel_compare";
            for (u32 y = 0; ok && y < height; ++y) {
                const u8 *expected = readback + (usize)y * width * 4u;
                const u8 *actual = post->capture_pixels + (usize)y * (usize)post->capture_stride;
                if (memcmp(actual, expected, (usize)width * 4u) != 0) {
                    for (u32 x = 0; x < width * 4u; ++x) {
                        if (actual[x] != expected[x]) {
                            LOG_ERROR("VK: Screen post pixel mismatch at byte %u: %u != %u",
                                      y * width * 4u + x, actual[x], expected[x]);
                            break;
                        }
                    }
                    ok = false;
                }
            }
        }
        if (ok) {
            stage = "ppm_write";
            const char *ppm = getenv("BREAK_VK_SCREEN_POST_PPM");
            ok = vk_qnx_screen_post_write_ppm(ppm, post->capture_pixels,
                                              post->capture_stride, width, height);
            if (ok) {
                LOG_INFO("VK: Screen post verified %ux%u pixels%s%s", width, height,
                         ppm != NULL ? ", PPM=" : "", ppm != NULL ? ppm : "");
            }
        }
        /* The buffer was posted with SCREEN_EXPLICIT_ENQUEUE: hand it back
         * even when the capture verification above failed. A failed enqueue
         * is reported as a present failure and the buffer is remembered so
         * the next present can release it before dequeuing. */
        stage = "screen_enqueue_render_buffer";
        if (screen_enqueue_render_buffer(buffer) != 0) {
            post->outstanding_buffer = buffer;
            ok = false;
        }
    }
    free(readback);
    if (!ok) {
        if (has_damage) {
            post->saved_damage[0] = damage[0];
            post->saved_damage[1] = damage[1];
            post->saved_damage[2] = damage[2];
            post->saved_damage[3] = damage[3];
            post->has_saved_damage = true;
        }
        LOG_ERROR("VK: Screen post stage %s failed (errno=%d)", stage, errno);
        if (!posted && buffer != NULL &&
            screen_enqueue_render_buffer(buffer) != 0) {
            post->outstanding_buffer = buffer;
        }
        return false;
    }
    post->has_saved_damage = false;
    post->post_count++;
    return true;
}

#endif
