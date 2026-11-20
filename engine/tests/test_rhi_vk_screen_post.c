#include "test_framework.h"
#include "rhi/rhi_backend_internal.h"
#include "rhi/rhi_vk_screen_post.h"
#include <screen/screen.h>
#include <string.h>

static bool dequeue_ok;
static bool screenshot_ok;
static bool buffer_acquired;
static bool capture_mismatch;
static int post_result;
static int create_result;
static int set_size_result;
static int create_count;
static int destroy_count;
static int native_width;
static int native_height;
static int enqueue_count;
static int enqueue_success_count;
static int enqueue_failures;
static int dequeue_count;
static int post_count;
static int screenshot_count;
static int capture_create_count;
static int capture_destroy_count;
static int capture_read_count;
static int last_post_flags;
static int last_post_count;
static int last_post_rects[4];
static uint8_t screen_pixels[16u * 32u * 4u];
static uint8_t capture_pixels[16u * 32u * 4u];

int __wrap_screen_create_window_buffers(screen_window_t window, int count) {
  (void)window;
  (void)count;
  if (create_result != 0) return create_result;
  create_count++;
  return 0;
}

int __wrap_screen_destroy_window_buffers(screen_window_t window) {
  (void)window;
  destroy_count++;
  buffer_acquired = false;
  return 0;
}

int __wrap_screen_set_window_property_iv(screen_window_t window, int property,
                                          const int* value) {
  (void)window;
  if (property != SCREEN_PROPERTY_BUFFER_SIZE) return -1;
  if (set_size_result == -2) return 0;
  if (set_size_result != 0) return set_size_result;
  native_width = value[0];
  native_height = value[1];
  return 0;
}

int __wrap_screen_dequeue_window_render_buffer(screen_buffer_t* buffer,
                                                screen_window_t window,
                                                int flags) {
  (void)window;
  (void)flags;
  dequeue_count++;
  if (!dequeue_ok || buffer_acquired) {
    *buffer = NULL;
    return -1;
  }
  *buffer = (screen_buffer_t)screen_pixels;
  buffer_acquired = true;
  return 0;
}

int __wrap_screen_get_buffer_property_pv(screen_buffer_t buffer, int property,
                                          void** value) {
  if (property != SCREEN_PROPERTY_POINTER) return -1;
  *value = buffer == (screen_buffer_t)capture_pixels ? capture_pixels
                                                     : screen_pixels;
  return 0;
}

int __wrap_screen_get_buffer_property_iv(screen_buffer_t buffer, int property,
                                          int* value) {
  (void)buffer;
  if (property == SCREEN_PROPERTY_STRIDE) {
    *value = native_width * 4;
    return 0;
  }
  if (property == SCREEN_PROPERTY_BUFFER_SIZE) {
    value[0] = native_width;
    value[1] = native_height;
    return 0;
  }
  return -1;
}

int __wrap_screen_post_window(screen_window_t window, screen_buffer_t buffer,
                              int count, const int* rects, int flags) {
  (void)window;
  (void)buffer;
  post_count++;
  last_post_flags = flags;
  last_post_count = count;
  if (count > 0 && rects != NULL) {
    memcpy(last_post_rects, rects, sizeof(last_post_rects));
  } else {
    memset(last_post_rects, 0, sizeof(last_post_rects));
  }
  if (post_result != 0) return post_result;
  if ((flags & SCREEN_EXPLICIT_ENQUEUE) == 0) buffer_acquired = false;
  return 0;
}

int __wrap_screen_enqueue_render_buffer(screen_buffer_t buffer) {
  enqueue_count++;
  if (buffer == NULL || enqueue_failures > 0) {
    if (enqueue_failures > 0) enqueue_failures--;
    return -1;
  }
  if (!buffer_acquired) return -1;
  buffer_acquired = false;
  enqueue_success_count++;
  return 0;
}

int __wrap_screen_create_pixmap(screen_pixmap_t* pixmap,
                                screen_context_t context) {
  (void)context;
  *pixmap = (screen_pixmap_t)4;
  capture_create_count++;
  return 0;
}

int __wrap_screen_destroy_pixmap(screen_pixmap_t pixmap) {
  (void)pixmap;
  capture_destroy_count++;
  return 0;
}

int __wrap_screen_set_pixmap_property_iv(screen_pixmap_t pixmap, int property,
                                         const int* value) {
  (void)pixmap;
  (void)property;
  (void)value;
  return 0;
}

int __wrap_screen_create_pixmap_buffer(screen_pixmap_t pixmap) {
  (void)pixmap;
  return 0;
}

int __wrap_screen_get_pixmap_property_pv(screen_pixmap_t pixmap, int property,
                                         void** value) {
  (void)pixmap;
  if (property != SCREEN_PROPERTY_RENDER_BUFFERS) return -1;
  *value = capture_pixels;
  return 0;
}

int __wrap_screen_read_window(screen_window_t window, screen_buffer_t buffer,
                              int count, const int* rects, int flags) {
  size_t bytes;
  (void)window;
  (void)count;
  (void)rects;
  (void)flags;
  if (buffer != (screen_buffer_t)capture_pixels) return -1;
  bytes = (size_t)native_width * (size_t)native_height * 4u;
  memcpy(capture_pixels, screen_pixels, bytes);
  if (capture_mismatch && bytes > 0u) capture_pixels[0] ^= 0xffu;
  capture_read_count++;
  return 0;
}

bool rhi_screenshot(RHIDevice* dev, u32 x, u32 y, u32 w, u32 h, u8* pixels,
                    usize pixel_bytes) {
  (void)dev;
  (void)x;
  (void)y;
  (void)w;
  (void)h;
  screenshot_count++;
  if (screenshot_ok) memset(pixels, 0x2a, pixel_bytes);
  return screenshot_ok;
}

static void fixture_with_post_count(VKQnxScreenPost* post, RHIDevice* dev,
                                    u64 initial_post_count) {
  memset(dev, 0, sizeof(*dev));
  dev->width = 16u;
  dev->height = 16u;
  dequeue_ok = true;
  screenshot_ok = true;
  buffer_acquired = false;
  capture_mismatch = false;
  post_result = 0;
  create_result = 0;
  set_size_result = 0;
  create_count = 0;
  destroy_count = 0;
  native_width = 16;
  native_height = 16;
  enqueue_count = 0;
  enqueue_success_count = 0;
  enqueue_failures = 0;
  dequeue_count = 0;
  post_count = 0;
  screenshot_count = 0;
  capture_create_count = 0;
  capture_destroy_count = 0;
  capture_read_count = 0;
  last_post_flags = 0;
  last_post_count = -1;
  memset(last_post_rects, 0, sizeof(last_post_rects));
  memset(screen_pixels, 0, sizeof(screen_pixels));
  memset(capture_pixels, 0, sizeof(capture_pixels));
  ASSERT_TRUE(vk_qnx_screen_post_init(post, (void*)1, (void*)1));
  post->post_count = initial_post_count;
}

static void fixture(VKQnxScreenPost* post, RHIDevice* dev) {
  fixture_with_post_count(post, dev, 1u);
}

static void first_frame_fixture(VKQnxScreenPost* post, RHIDevice* dev) {
  fixture_with_post_count(post, dev, 0u);
}

TEST(screen_post_dequeue_failure_never_enqueues_null) {
  VKQnxScreenPost post;
  RHIDevice dev;
  fixture(&post, &dev);
  dequeue_ok = false;
  ASSERT_FALSE(vk_qnx_screen_post_present(&post, &dev));
  ASSERT_EQ(enqueue_count, 0);
  ASSERT_EQ(screenshot_count, 0);
}

TEST(screen_post_screenshot_failure_releases_acquired_buffer) {
  VKQnxScreenPost post;
  RHIDevice dev;
  fixture(&post, &dev);
  screenshot_ok = false;
  ASSERT_FALSE(vk_qnx_screen_post_present(&post, &dev));
  ASSERT_EQ(screenshot_count, 1);
  ASSERT_EQ(enqueue_count, 1);
}

TEST(screen_post_native_failure_releases_acquired_buffer) {
  VKQnxScreenPost post;
  RHIDevice dev;
  fixture(&post, &dev);
  post_result = -1;
  ASSERT_FALSE(vk_qnx_screen_post_present(&post, &dev));
  ASSERT_EQ(screenshot_count, 1);
  ASSERT_EQ(enqueue_count, 1);
}

TEST(screen_post_rejects_invalid_arguments_without_native_calls) {
  VKQnxScreenPost post;
  RHIDevice dev;
  fixture(&post, &dev);
  ASSERT_FALSE(vk_qnx_screen_post_present(NULL, &dev));
  ASSERT_FALSE(vk_qnx_screen_post_present(&post, NULL));
  create_result = -1;
  post.buffers_created = false;
  ASSERT_FALSE(vk_qnx_screen_post_present(&post, &dev));
  dev.width = 0u;
  ASSERT_FALSE(vk_qnx_screen_post_present(&post, &dev));
  ASSERT_EQ(enqueue_count, 0);
  ASSERT_EQ(screenshot_count, 0);
}

TEST(screen_post_init_defers_buffer_creation_to_present) {
  VKQnxScreenPost post;
  RHIDevice dev;
  fixture(&post, &dev);
  ASSERT_EQ(create_count, 0);
  ASSERT_TRUE(vk_qnx_screen_post_present(&post, &dev));
  ASSERT_EQ(create_count, 1);
  ASSERT_EQ(native_width, 16);
  ASSERT_EQ(native_height, 16);
  ASSERT_TRUE(post.buffers_created);
  ASSERT_EQ(post.post_count, 2u);
}

TEST(screen_post_resize_recreates_exact_size_buffers) {
  VKQnxScreenPost post;
  RHIDevice dev;
  fixture(&post, &dev);
  ASSERT_TRUE(vk_qnx_screen_post_present(&post, &dev));
  dev.width = 8u;
  dev.height = 8u;
  ASSERT_TRUE(vk_qnx_screen_post_present(&post, &dev));
  ASSERT_EQ(create_count, 2);
  ASSERT_EQ(destroy_count, 1);
  ASSERT_EQ(native_width, 8);
  ASSERT_EQ(native_height, 8);
  ASSERT_EQ(enqueue_count, 0);
  ASSERT_EQ(screenshot_count, 2);
}

TEST(screen_post_rejects_mismatched_buffer_dimensions) {
  VKQnxScreenPost post;
  RHIDevice dev;
  fixture(&post, &dev);
  set_size_result = -2;
  dev.height = 32u;
  ASSERT_FALSE(vk_qnx_screen_post_present(&post, &dev));
  ASSERT_EQ(screenshot_count, 0);
  ASSERT_EQ(enqueue_count, 1);
}

TEST(screen_post_first_frame_capture_verifies_and_enqueues) {
  VKQnxScreenPost post;
  RHIDevice dev;
  first_frame_fixture(&post, &dev);
  ASSERT_TRUE(vk_qnx_screen_post_present(&post, &dev));
  ASSERT_EQ(post_count, 1);
  ASSERT_EQ(last_post_count, 0);
  ASSERT_EQ(last_post_flags & SCREEN_EXPLICIT_ENQUEUE,
            SCREEN_EXPLICIT_ENQUEUE);
  ASSERT_EQ(capture_create_count, 1);
  ASSERT_EQ(capture_read_count, 1);
  ASSERT_EQ(enqueue_count, 1);
  ASSERT_EQ(enqueue_success_count, 1);
  ASSERT_FALSE(buffer_acquired);
  ASSERT_EQ(post.post_count, 1u);
  vk_qnx_screen_post_shutdown(&post);
  ASSERT_EQ(capture_destroy_count, 1);
}

TEST(screen_post_first_frame_capture_mismatch_fails) {
  VKQnxScreenPost post;
  RHIDevice dev;
  first_frame_fixture(&post, &dev);
  capture_mismatch = true;
  ASSERT_FALSE(vk_qnx_screen_post_present(&post, &dev));
  ASSERT_EQ(post_count, 1);
  ASSERT_EQ(capture_read_count, 1);
  ASSERT_EQ(enqueue_count, 1);
  ASSERT_EQ(enqueue_success_count, 1);
  ASSERT_FALSE(buffer_acquired);
  ASSERT_EQ(post.post_count, 0u);
  vk_qnx_screen_post_shutdown(&post);
  ASSERT_EQ(capture_destroy_count, 1);
}

TEST(screen_post_first_frame_enqueue_failure_is_recoverable) {
  VKQnxScreenPost post;
  RHIDevice dev;
  first_frame_fixture(&post, &dev);
  enqueue_failures = 1;
  ASSERT_FALSE(vk_qnx_screen_post_present(&post, &dev));
  ASSERT_EQ(post.post_count, 0u);
  ASSERT_EQ(enqueue_count, 1);
  ASSERT_EQ(enqueue_success_count, 0);
  ASSERT_TRUE(buffer_acquired);
  ASSERT_TRUE(vk_qnx_screen_post_present(&post, &dev));
  ASSERT_EQ(post.post_count, 1u);
  ASSERT_EQ(post_count, 2);
  ASSERT_EQ(dequeue_count, 2);
  ASSERT_EQ(capture_read_count, 2);
  ASSERT_EQ(enqueue_count, 3);
  ASSERT_EQ(enqueue_success_count, 2);
  ASSERT_FALSE(buffer_acquired);
  vk_qnx_screen_post_shutdown(&post);
  ASSERT_EQ(capture_destroy_count, 1);
}

TEST(screen_post_failed_post_enqueue_failure_preserves_damage_for_retry) {
  VKQnxScreenPost post;
  RHIDevice dev;
  fixture(&post, &dev);
  dev.frame_damage_requested = true;
  dev.frame_damage_count = 1u;
  dev.frame_damage[0] = (RHIPresentRect){1, 2, 3u, 4u};
  post_result = -1;
  enqueue_failures = 1;
  ASSERT_FALSE(vk_qnx_screen_post_present(&post, &dev));
  ASSERT_EQ(post.post_count, 1u);
  ASSERT_EQ(enqueue_count, 1);
  ASSERT_EQ(enqueue_success_count, 0);
  ASSERT_TRUE(buffer_acquired);

  post_result = 0;
  dev.frame_damage[0] = (RHIPresentRect){10, 12, 2u, 3u};
  ASSERT_TRUE(vk_qnx_screen_post_present(&post, &dev));
  ASSERT_EQ(post.post_count, 2u);
  ASSERT_EQ(post_count, 2);
  ASSERT_EQ(dequeue_count, 2);
  ASSERT_EQ(enqueue_count, 2);
  ASSERT_EQ(enqueue_success_count, 1);
  ASSERT_EQ(last_post_count, 1);
  ASSERT_EQ(last_post_rects[0], 1);
  ASSERT_EQ(last_post_rects[1], 2);
  ASSERT_EQ(last_post_rects[2], 11);
  ASSERT_EQ(last_post_rects[3], 13);
  ASSERT_FALSE(buffer_acquired);
  vk_qnx_screen_post_shutdown(&post);
}

TEST_MAIN_BEGIN()
  RUN_TEST(screen_post_dequeue_failure_never_enqueues_null);
  RUN_TEST(screen_post_screenshot_failure_releases_acquired_buffer);
  RUN_TEST(screen_post_native_failure_releases_acquired_buffer);
  RUN_TEST(screen_post_rejects_invalid_arguments_without_native_calls);
  RUN_TEST(screen_post_init_defers_buffer_creation_to_present);
  RUN_TEST(screen_post_resize_recreates_exact_size_buffers);
  RUN_TEST(screen_post_rejects_mismatched_buffer_dimensions);
  RUN_TEST(screen_post_first_frame_capture_verifies_and_enqueues);
  RUN_TEST(screen_post_first_frame_capture_mismatch_fails);
  RUN_TEST(screen_post_first_frame_enqueue_failure_is_recoverable);
  RUN_TEST(screen_post_failed_post_enqueue_failure_preserves_damage_for_retry);
TEST_MAIN_END()
