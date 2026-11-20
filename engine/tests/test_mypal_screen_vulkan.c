#include "test_framework.h"

#include "mypal/dummy/my_pal_dummy.h"
#include "mypal/screen/my_pal_screen.h"
#include "myr/my_vgcanvas_vulkan.h"
#include "myui/my_window.h"

#include <errno.h>
#include <platform/time.h>
#include <screen/screen.h>

#if defined(MYUI_HAS_VULKAN)
static const uint8_t colors_a[4][4] = {
    {241u, 18u, 56u, 255u},
    {17u, 203u, 91u, 255u},
    {29u, 77u, 219u, 255u},
    {230u, 171u, 24u, 255u},
};
static const uint8_t colors_b[4][4] = {
    {201u, 31u, 143u, 255u},
    {13u, 181u, 194u, 255u},
    {244u, 108u, 17u, 255u},
    {83u, 49u, 188u, 255u},
};
#endif

static int native_context_creates;
static int native_context_destroys;
static int native_window_creates;
static int native_window_destroys;
static int native_post_attempts;
static int fail_dequeue_once;
static int fail_post_once;

int __real_screen_create_context(screen_context_t* context, int type);
int __real_screen_destroy_context(screen_context_t context);
int __real_screen_create_window(screen_window_t* window,
                                screen_context_t context);
int __real_screen_destroy_window(screen_window_t window);
int __real_screen_dequeue_window_render_buffer(screen_buffer_t* buffer,
                                               screen_window_t window,
                                               int flags);
int __real_screen_post_window(screen_window_t window, screen_buffer_t buffer,
                              int count, const int* rects, int flags);

int __wrap_screen_create_context(screen_context_t* context, int type) {
  int result = __real_screen_create_context(context, type);
  if (result == 0) native_context_creates++;
  return result;
}

int __wrap_screen_destroy_context(screen_context_t context) {
  int result = __real_screen_destroy_context(context);
  if (result == 0) native_context_destroys++;
  return result;
}

int __wrap_screen_create_window(screen_window_t* window,
                                screen_context_t context) {
  int result = __real_screen_create_window(window, context);
  if (result == 0) native_window_creates++;
  return result;
}

int __wrap_screen_destroy_window(screen_window_t window) {
  int result = __real_screen_destroy_window(window);
  if (result == 0) native_window_destroys++;
  return result;
}

int __wrap_screen_dequeue_window_render_buffer(screen_buffer_t* buffer,
                                               screen_window_t window,
                                               int flags) {
  if (fail_dequeue_once != 0) {
    fail_dequeue_once = 0;
    errno = EWOULDBLOCK;
    return -1;
  }
  return __real_screen_dequeue_window_render_buffer(buffer, window, flags);
}

int __wrap_screen_post_window(screen_window_t window, screen_buffer_t buffer,
                              int count, const int* rects, int flags) {
  native_post_attempts++;
  if (fail_post_once != 0) {
    fail_post_once = 0;
    errno = EWOULDBLOCK;
    return -1;
  }
  return __real_screen_post_window(window, buffer, count, rects, flags);
}

#if defined(MYUI_HAS_VULKAN)
typedef struct window_fixture_t {
  my_allocator_t* debug;
  my_pal_t* pal;
  my_window_t* window;
  int32_t width;
  int32_t height;
} window_fixture_t;

static void fixture_destroy(window_fixture_t* fixture) {
  if (fixture->window != NULL) {
    my_widget_unref((my_widget_t*)fixture->window);
    fixture->window = NULL;
  }
  if (fixture->pal != NULL) {
    my_pal_destroy(fixture->pal);
    fixture->pal = NULL;
  }
  if (fixture->debug != NULL) {
    ASSERT_EQ(my_allocator_debug_leak_count(fixture->debug), 0);
    my_allocator_debug_destroy(fixture->debug);
    fixture->debug = NULL;
  }
}

static bool fixture_create(window_fixture_t* fixture, int32_t width,
                           int32_t height, const char* title) {
  my_ret_t mount_result;
  memset(fixture, 0, sizeof(*fixture));
  fixture->width = width;
  fixture->height = height;
  fixture->debug = my_allocator_debug_create(NULL);
  if (fixture->debug == NULL) return false;
  fixture->pal = my_pal_create(fixture->debug);
  if (fixture->pal == NULL) {
    fixture_destroy(fixture);
    return false;
  }
  fixture->window = my_window_create(fixture->debug, fixture->pal, width, height,
                                     title);
  if (fixture->window == NULL) {
    fixture_destroy(fixture);
    return false;
  }
  mount_result = my_window_enable_gpu(fixture->window, MY_GPU_VULKAN);
  if (mount_result != MY_RET_OK) {
    printf("  Vulkan mount failed: %d\n", mount_result);
    fixture_destroy(fixture);
    return false;
  }
  if (fixture->window->vg == NULL || fixture->window->gl == NULL ||
      fixture->window->gpu_backend != MY_GPU_VULKAN) {
    fixture_destroy(fixture);
    return false;
  }
  return true;
}

typedef struct fallible_allocator_t {
  my_allocator_t base;
  my_allocator_t* debug;
  size_t budget;
} fallible_allocator_t;

static bool fallible_allow(fallible_allocator_t* allocator) {
  if (allocator->budget == 0u) return false;
  if (allocator->budget != SIZE_MAX) allocator->budget--;
  return true;
}

static void* fallible_alloc(void* context, size_t size) {
  fallible_allocator_t* allocator = (fallible_allocator_t*)context;
  return fallible_allow(allocator) ? my_mem_alloc(allocator->debug, size) : NULL;
}

static void* fallible_calloc(void* context, size_t count, size_t size) {
  fallible_allocator_t* allocator = (fallible_allocator_t*)context;
  return fallible_allow(allocator)
             ? my_mem_calloc(allocator->debug, count, size)
             : NULL;
}

static void* fallible_realloc(void* context, void* pointer, size_t size) {
  fallible_allocator_t* allocator = (fallible_allocator_t*)context;
  return fallible_allow(allocator)
             ? my_mem_realloc(allocator->debug, pointer, size)
             : NULL;
}

static void fallible_free(void* context, void* pointer) {
  fallible_allocator_t* allocator = (fallible_allocator_t*)context;
  my_mem_free(allocator->debug, pointer);
}

static bool fallible_init(fallible_allocator_t* allocator) {
  memset(allocator, 0, sizeof(*allocator));
  allocator->debug = my_allocator_debug_create(NULL);
  if (allocator->debug == NULL) return false;
  allocator->base.ctx = allocator;
  allocator->base.alloc = fallible_alloc;
  allocator->base.calloc = fallible_calloc;
  allocator->base.realloc = fallible_realloc;
  allocator->base.free = fallible_free;
  allocator->budget = SIZE_MAX;
  return true;
}

static bool draw_quadrants(my_vgcanvas_t* canvas, int32_t width, int32_t height,
                           const uint8_t colors[4][4]) {
  int part;
  if (my_vgcanvas_set_antialias_level(canvas, 0) != MY_RET_OK ||
      my_vgcanvas_begin_frame(canvas, NULL) != MY_RET_OK) {
    return false;
  }
  for (part = 0; part < 4; ++part) {
    int32_t x = (part & 1) != 0 ? width / 2 : 0;
    int32_t y = (part & 2) != 0 ? height / 2 : 0;
    my_rectf_t rect = {(float)x, (float)y, (float)(width / 2),
                       (float)(height / 2)};
    if (my_vgcanvas_set_fill_color(
            canvas, my_color_rgba(colors[part][0], colors[part][1],
                                  colors[part][2], colors[part][3])) !=
            MY_RET_OK ||
        my_vgcanvas_fill_rect(canvas, &rect) != MY_RET_OK) {
      (void)my_vgcanvas_end_frame(canvas);
      return false;
    }
  }
  return my_vgcanvas_end_frame(canvas) == MY_RET_OK;
}

static bool check_rgba_quadrants(const uint8_t* pixels, uint32_t stride,
                                 int32_t width, int32_t height,
                                 const uint8_t colors[4][4]) {
  int part;
  for (part = 0; part < 4; ++part) {
    int32_t x = (part & 1) != 0 ? width - 3 : 2;
    int32_t y = (part & 2) != 0 ? height - 3 : 2;
    const uint8_t* actual = pixels + (size_t)y * stride + (size_t)x * 4u;
    if (memcmp(actual, colors[part], 4u) != 0) {
      printf("  quadrant %d at (%d,%d): got %u,%u,%u,%u expected "
             "%u,%u,%u,%u\n",
             part, x, y, actual[0], actual[1], actual[2], actual[3],
             colors[part][0], colors[part][1], colors[part][2],
             colors[part][3]);
      return false;
    }
  }
  return true;
}

static bool check_window_quadrants(my_window_t* window,
                                   const uint8_t colors[4][4]) {
  my_lcd_t* lcd = my_pal_window_get_lcd(window->pal_window);
  int32_t width;
  int32_t height;
  my_ret_t begin_result = MY_RET_FAIL;
  my_ret_t end_result;
  const uint8_t* pixels;
  uint32_t stride;
  bool matches;
  int attempt;
  if (lcd == NULL) return false;
  width = (int32_t)my_lcd_get_width(lcd);
  height = (int32_t)my_lcd_get_height(lcd);
  for (attempt = 0; attempt < 200; ++attempt) {
    begin_result = my_lcd_begin_frame(lcd, NULL);
    if (begin_result != MY_RET_PENDING) break;
    time_sleep_us(100u);
  }
  if (begin_result != MY_RET_OK) {
    printf("  LCD begin for pixel assertion failed: %d\n", begin_result);
    return false;
  }
  pixels = my_lcd_get_buffer(lcd);
  stride = my_lcd_get_stride(lcd);
  matches = pixels != NULL && width >= 6 && height >= 6 &&
            check_rgba_quadrants(pixels, stride, width, height, colors);
  end_result = my_lcd_end_frame(lcd);
  if (end_result != MY_RET_OK) {
    printf("  LCD end after pixel assertion failed: %d\n", end_result);
    return false;
  }
  return matches;
}
#endif

TEST(screen_vulkan_provider_is_explicitly_surfaceless) {
  my_pal_t* pal = my_pal_create(NULL);
  my_pal_window_t* window;
  my_pal_vulkan_instance_extensions_t extensions;
  ASSERT_NOT_NULL(pal);
  window = my_pal_window_create(pal, 32, 24, "Vulkan provider");
  ASSERT_NOT_NULL(window);
  ASSERT_EQ(my_pal_get_vulkan_instance_extensions(pal, window, &extensions),
            MY_RET_OK);
  ASSERT_EQ(extensions.count, 2u);
  ASSERT_STR_EQ(extensions.names[0], "VK_KHR_surface");
  ASSERT_STR_EQ(extensions.names[1], "VK_EXT_headless_surface");
  ASSERT_TRUE(my_pal_window_vk_create_surface(window, (void*)1) == NULL);
  my_pal_window_destroy(window);
  my_pal_destroy(pal);
  ASSERT_EQ(my_pal_get_vulkan_instance_extensions(pal, NULL, &extensions),
            MY_RET_NOT_SUPPORTED);
}

TEST(dummy_without_vulkan_provider_does_not_mount_lcd) {
  my_allocator_t* debug = my_allocator_debug_create(NULL);
  my_pal_t* pal;
  my_window_t* window;
  my_pal_vulkan_instance_extensions_t extensions;
  ASSERT_NOT_NULL(debug);
  pal = my_pal_dummy_create(debug);
  ASSERT_NOT_NULL(pal);
  window = my_window_create(debug, pal, 32, 24, "Dummy Vulkan rejection");
  ASSERT_NOT_NULL(window);
  ASSERT_EQ(my_pal_get_vulkan_instance_extensions(pal, window->pal_window,
                                                  &extensions),
            MY_RET_NOT_SUPPORTED);
  ASSERT_EQ(my_window_enable_gpu(window, MY_GPU_VULKAN), MY_RET_NOT_SUPPORTED);
  ASSERT_EQ(window->gpu_backend, MY_GPU_SOFT);
  ASSERT_TRUE(window->gl == NULL);
  ASSERT_TRUE(window->vg == NULL);
  my_widget_unref((my_widget_t*)window);
  my_pal_destroy(pal);
  ASSERT_EQ(my_allocator_debug_leak_count(debug), 0);
  my_allocator_debug_destroy(debug);
}

#if defined(MYUI_HAS_VULKAN)
TEST(vulkan_offscreen_readback_orientation_resize_and_invalid_arguments) {
  uint8_t pixels[64u * 48u * 4u];
  my_vgcanvas_t* canvas;
  ASSERT_TRUE(my_vgcanvas_vulkan_create_offscreen(NULL, 0, 24) == NULL);
  canvas = my_vgcanvas_vulkan_create_offscreen(NULL, 64, 48);
  ASSERT_NOT_NULL(canvas);
  ASSERT_EQ(my_vgcanvas_vulkan_readback(NULL, pixels, 64, 48),
            MY_RET_INVALID_PARAMS);
  ASSERT_EQ(my_vgcanvas_vulkan_readback(canvas, NULL, 64, 48),
            MY_RET_INVALID_PARAMS);
  ASSERT_EQ(my_vgcanvas_vulkan_readback(canvas, pixels, 63, 48),
            MY_RET_INVALID_PARAMS);
  ASSERT_EQ(my_vgcanvas_vulkan_resize(canvas, 0, 48), MY_RET_INVALID_PARAMS);
  ASSERT_EQ(my_vgcanvas_vulkan_resize(canvas, 32, -1), MY_RET_INVALID_PARAMS);
  ASSERT_TRUE(draw_quadrants(canvas, 64, 48, colors_a));
  ASSERT_EQ(my_vgcanvas_vulkan_readback(canvas, pixels, 64, 48), MY_RET_OK);
  ASSERT_TRUE(check_rgba_quadrants(pixels, 64u * 4u, 64, 48, colors_a));
  ASSERT_EQ(my_vgcanvas_vulkan_present(canvas), MY_RET_INVALID_PARAMS);
  ASSERT_EQ(my_vgcanvas_vulkan_resize(canvas, 37, 29), MY_RET_OK);
  ASSERT_TRUE(draw_quadrants(canvas, 37, 29, colors_b));
  ASSERT_EQ(my_vgcanvas_vulkan_readback(canvas, pixels, 37, 29), MY_RET_OK);
  ASSERT_TRUE(check_rgba_quadrants(pixels, 37u * 4u, 37, 29, colors_b));
  my_vgcanvas_destroy(canvas);
}

TEST(screen_vulkan_mount_presents_real_quadrants) {
  window_fixture_t fixture;
  ASSERT_TRUE(fixture_create(&fixture, 64, 48, "Vulkan LCD quadrants"));
  ASSERT_TRUE(my_pal_window_vk_create_surface(fixture.window->pal_window,
                                               (void*)1) == NULL);
  ASSERT_TRUE(draw_quadrants(fixture.window->vg, 64, 48, colors_a));
  ASSERT_EQ(my_pal_gl_swap_buffers(fixture.window->gl), MY_RET_OK);
  ASSERT_TRUE(check_window_quadrants(fixture.window, colors_a));
  fixture_destroy(&fixture);
}

static bool check_mount_allocation_failure(size_t budget,
                                           my_ret_t expected) {
  fallible_allocator_t allocator;
  my_pal_t* pal;
  my_window_t* window;
  my_ret_t result;
  bool matches;
  if (!fallible_init(&allocator)) return false;
  pal = my_pal_create(&allocator.base);
  if (pal == NULL) {
    my_allocator_debug_destroy(allocator.debug);
    return false;
  }
  window = my_window_create(&allocator.base, pal, 32, 24,
                            "Vulkan allocation failure");
  if (window == NULL) {
    my_pal_destroy(pal);
    my_allocator_debug_destroy(allocator.debug);
    return false;
  }
  allocator.budget = budget;
  result = my_window_enable_gpu(window, MY_GPU_VULKAN);
  matches = result == expected && window->gpu_backend == MY_GPU_SOFT &&
            window->vg == NULL && window->gl == NULL;
  my_widget_unref((my_widget_t*)window);
  my_pal_destroy(pal);
  if (my_allocator_debug_leak_count(allocator.debug) != 0) matches = false;
  my_allocator_debug_destroy(allocator.debug);
  return matches;
}

TEST(screen_vulkan_mount_allocation_errors_are_distinct) {
  ASSERT_TRUE(check_mount_allocation_failure(0u, MY_RET_OOM));
  ASSERT_TRUE(check_mount_allocation_failure(1u, MY_RET_OOM));
  ASSERT_TRUE(check_mount_allocation_failure(2u, MY_RET_FAIL));
}

TEST(screen_vulkan_resize_oom_preserves_canvas_and_retries) {
  fallible_allocator_t allocator;
  my_pal_t* pal = NULL;
  my_window_t* window = NULL;
  my_vgcanvas_t* old_canvas;
  my_pal_gl_t* old_adapter;
  my_event_t resize;
  bool matches = false;
  ASSERT_TRUE(fallible_init(&allocator));
  pal = my_pal_create(&allocator.base);
  ASSERT_NOT_NULL(pal);
  window = my_window_create(&allocator.base, pal, 40, 32,
                            "Vulkan resize allocation failure");
  ASSERT_NOT_NULL(window);
  ASSERT_EQ(my_window_enable_gpu(window, MY_GPU_VULKAN), MY_RET_OK);
  old_canvas = window->vg;
  old_adapter = window->gl;
  ASSERT_EQ(my_pal_window_resize(window->pal_window, 52, 36), MY_RET_OK);
  resize = my_event_init(MY_EVENT_RESIZE);
  resize.u.resize.w = 52;
  resize.u.resize.h = 36;
  allocator.budget = 0u;
  ASSERT_EQ(my_window_on_pal_event(window, &resize), MY_RET_OOM);
  ASSERT_TRUE(window->vg == old_canvas);
  ASSERT_TRUE(window->gl == old_adapter);
  allocator.budget = SIZE_MAX;
  ASSERT_EQ(my_window_on_pal_event(window, &resize), MY_RET_OK);
  ASSERT_TRUE(window->vg == old_canvas);
  ASSERT_TRUE(window->gl == old_adapter);
  ASSERT_TRUE(draw_quadrants(window->vg, 52, 36, colors_b));
  ASSERT_EQ(my_pal_gl_swap_buffers(window->gl), MY_RET_OK);
  matches = check_window_quadrants(window, colors_b);
  my_widget_unref((my_widget_t*)window);
  my_pal_destroy(pal);
  ASSERT_EQ(my_allocator_debug_leak_count(allocator.debug), 0);
  my_allocator_debug_destroy(allocator.debug);
  ASSERT_TRUE(matches);
}

TEST(screen_vulkan_multiwindow_resize_and_early_destroy) {
  window_fixture_t first;
  window_fixture_t second;
  my_vgcanvas_t* old_canvas;
  my_event_t resize;
  ASSERT_TRUE(fixture_create(&first, 64, 48, "Vulkan LCD first"));
  ASSERT_TRUE(fixture_create(&second, 40, 32, "Vulkan LCD second"));
  ASSERT_TRUE(first.window->vg != second.window->vg);
  ASSERT_TRUE(first.window->gl != second.window->gl);
  ASSERT_TRUE(draw_quadrants(first.window->vg, 64, 48, colors_a));
  ASSERT_EQ(my_pal_gl_swap_buffers(first.window->gl), MY_RET_OK);
  ASSERT_TRUE(draw_quadrants(second.window->vg, 40, 32, colors_b));
  ASSERT_EQ(my_pal_gl_swap_buffers(second.window->gl), MY_RET_OK);
  ASSERT_TRUE(check_window_quadrants(second.window, colors_b));
  ASSERT_TRUE(check_window_quadrants(first.window, colors_a));

  old_canvas = second.window->vg;
  ASSERT_EQ(my_pal_window_resize(second.window->pal_window, 52, 36), MY_RET_OK);
  resize = my_event_init(MY_EVENT_RESIZE);
  resize.u.resize.w = 52;
  resize.u.resize.h = 36;
  ASSERT_EQ(my_window_on_pal_event(second.window, &resize), MY_RET_OK);
  ASSERT_TRUE(second.window->vg == old_canvas);
  ASSERT_TRUE(draw_quadrants(second.window->vg, 52, 36, colors_a));
  ASSERT_EQ(my_pal_gl_swap_buffers(second.window->gl), MY_RET_OK);
  ASSERT_TRUE(check_window_quadrants(second.window, colors_a));
  ASSERT_TRUE(check_window_quadrants(first.window, colors_a));

  fixture_destroy(&first);
  ASSERT_TRUE(draw_quadrants(second.window->vg, 52, 36, colors_b));
  ASSERT_EQ(my_pal_gl_swap_buffers(second.window->gl), MY_RET_OK);
  ASSERT_TRUE(check_window_quadrants(second.window, colors_b));
  fixture_destroy(&second);
}

TEST(screen_vulkan_pending_dequeue_reuses_original_readback) {
  window_fixture_t fixture;
  ASSERT_TRUE(fixture_create(&fixture, 64, 48, "Vulkan LCD dequeue retry"));
  ASSERT_TRUE(draw_quadrants(fixture.window->vg, 64, 48, colors_b));
  ASSERT_EQ(my_pal_gl_swap_buffers(fixture.window->gl), MY_RET_OK);
  ASSERT_TRUE(draw_quadrants(fixture.window->vg, 64, 48, colors_a));
  fail_dequeue_once = 1;
  ASSERT_EQ(my_pal_gl_swap_buffers(fixture.window->gl), MY_RET_PENDING);
  ASSERT_TRUE(draw_quadrants(fixture.window->vg, 64, 48, colors_b));
  ASSERT_EQ(my_pal_gl_swap_buffers(fixture.window->gl), MY_RET_OK);
  ASSERT_TRUE(check_window_quadrants(fixture.window, colors_a));
  fixture_destroy(&fixture);
}

TEST(screen_vulkan_pending_post_reuses_original_readback) {
  window_fixture_t fixture;
  ASSERT_TRUE(fixture_create(&fixture, 64, 48, "Vulkan LCD post retry"));
  ASSERT_TRUE(draw_quadrants(fixture.window->vg, 64, 48, colors_a));
  fail_post_once = 1;
  ASSERT_EQ(my_pal_gl_swap_buffers(fixture.window->gl), MY_RET_PENDING);
  ASSERT_TRUE(draw_quadrants(fixture.window->vg, 64, 48, colors_b));
  ASSERT_EQ(my_pal_gl_swap_buffers(fixture.window->gl), MY_RET_OK);
  ASSERT_TRUE(check_window_quadrants(fixture.window, colors_a));
  fixture_destroy(&fixture);
}

TEST(screen_vulkan_window_paint_pending_restores_dirty) {
  window_fixture_t fixture;
  ASSERT_TRUE(fixture_create(&fixture, 64, 48, "Vulkan LCD dirty retry"));
  my_widget_invalidate((my_widget_t*)fixture.window, NULL);
  fail_post_once = 1;
  native_post_attempts = 0;
  my_window_paint(fixture.window);
  ASSERT_EQ(native_post_attempts, 1);
  ASSERT_TRUE(my_dirty_rects_count(&fixture.window->dirty) > 0u);
  my_window_paint(fixture.window);
  ASSERT_EQ(native_post_attempts, 2);
  ASSERT_EQ(my_dirty_rects_count(&fixture.window->dirty), 0u);
  fixture_destroy(&fixture);
}

TEST(screen_vulkan_early_destroy_is_balanced) {
  window_fixture_t fixture;
  ASSERT_TRUE(fixture_create(&fixture, 32, 24, "Vulkan LCD early destroy"));
  fixture_destroy(&fixture);
  ASSERT_TRUE(fixture_create(&fixture, 32, 24, "Vulkan LCD frame destroy"));
  ASSERT_TRUE(draw_quadrants(fixture.window->vg, 32, 24, colors_a));
  ASSERT_EQ(my_pal_gl_swap_buffers(fixture.window->gl), MY_RET_OK);
  fixture_destroy(&fixture);
}
#else
TEST(screen_vulkan_disabled_build_fails_closed) {
  my_allocator_t* debug = my_allocator_debug_create(NULL);
  my_pal_t* pal;
  my_window_t* window;
  ASSERT_NOT_NULL(debug);
  pal = my_pal_create(debug);
  ASSERT_NOT_NULL(pal);
  window = my_window_create(debug, pal, 32, 24, "Vulkan disabled");
  ASSERT_NOT_NULL(window);
  ASSERT_EQ(my_window_enable_gpu(window, MY_GPU_VULKAN), MY_RET_NOT_SUPPORTED);
  ASSERT_EQ(window->gpu_backend, MY_GPU_SOFT);
  ASSERT_TRUE(window->gl == NULL);
  ASSERT_TRUE(window->vg == NULL);
  my_widget_unref((my_widget_t*)window);
  my_pal_destroy(pal);
  ASSERT_EQ(my_allocator_debug_leak_count(debug), 0);
  my_allocator_debug_destroy(debug);
}
#endif

int main(void) {
  my_pal_t* probe;
  setvbuf(stdout, NULL, _IONBF, 0);
  probe = my_pal_create(NULL);
  if (probe == NULL || my_pal_screen_native_context(probe) == NULL) {
    if (probe != NULL) my_pal_destroy(probe);
    printf("NOT RUN: no usable QNX Screen service\n");
    return getenv("BREAK_QNX_SCREEN_REQUIRED") != NULL ? 1 : 77;
  }
  my_pal_destroy(probe);
#if defined(MYUI_HAS_VULKAN)
  {
    my_vgcanvas_t* canvas = my_vgcanvas_vulkan_create_offscreen(NULL, 4, 4);
    if (canvas == NULL) {
      printf("NOT RUN: no usable Vulkan offscreen device/ICD\n");
      return getenv("BREAK_QNX_VULKAN_REQUIRED") != NULL ? 1 : 77;
    }
    my_vgcanvas_destroy(canvas);
  }
#endif
  printf("=== Running Tests ===\n");
  RUN_TEST(screen_vulkan_provider_is_explicitly_surfaceless);
  RUN_TEST(dummy_without_vulkan_provider_does_not_mount_lcd);
#if defined(MYUI_HAS_VULKAN)
  RUN_TEST(vulkan_offscreen_readback_orientation_resize_and_invalid_arguments);
  RUN_TEST(screen_vulkan_mount_presents_real_quadrants);
  RUN_TEST(screen_vulkan_mount_allocation_errors_are_distinct);
  RUN_TEST(screen_vulkan_resize_oom_preserves_canvas_and_retries);
  RUN_TEST(screen_vulkan_multiwindow_resize_and_early_destroy);
  RUN_TEST(screen_vulkan_pending_dequeue_reuses_original_readback);
  RUN_TEST(screen_vulkan_pending_post_reuses_original_readback);
  RUN_TEST(screen_vulkan_window_paint_pending_restores_dirty);
  RUN_TEST(screen_vulkan_early_destroy_is_balanced);
#else
  RUN_TEST(screen_vulkan_disabled_build_fails_closed);
#endif
  if (native_context_creates != native_context_destroys) {
    printf("  FAIL: native context balance: %d creates, %d destroys\n",
           native_context_creates, native_context_destroys);
    g_test_fail++;
  }
  if (native_window_creates != native_window_destroys) {
    printf("  FAIL: native window balance: %d creates, %d destroys\n",
           native_window_creates, native_window_destroys);
    g_test_fail++;
  }
  printf("\n=== Results: %d passed, %d failed, %d total ===\n",
         g_test_pass, g_test_fail, g_test_count);
  return g_test_fail > 0 ? 1 : 0;
}
