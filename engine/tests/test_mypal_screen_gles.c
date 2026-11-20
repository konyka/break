#if defined(MY_SCREEN_GLES_HOST_TEST)
#include "test_framework.h"
#include "../src/myui/mypal/screen/my_pal_screen.c"

static int host_fail_pbuffer;
static int host_gl_width = 64;
static int host_gl_height = 48;
static int host_native_posts;
static bool host_buffer_acquired;
static uint8_t host_screen_pixels[64u * 48u * 4u];

my_ret_t my_screen_gl_resize(my_pal_gl_t* gl, int32_t width, int32_t height) {
  (void)gl;
  if (host_fail_pbuffer != 0) return MY_RET_FAIL;
  host_gl_width = width;
  host_gl_height = height;
  return MY_RET_OK;
}

my_ret_t my_screen_cursor_bounds(const my_screen_cursor_t* cursor, int32_t width,
                                 int32_t height, my_rect_t* out) {
  (void)cursor;
  (void)width;
  (void)height;
  *out = my_rect_init(0, 0, 0, 0);
  return MY_RET_OK;
}

my_ret_t my_screen_cursor_composite(const my_screen_cursor_t* cursor,
                                    uint8_t* pixels, uint32_t stride,
                                    int32_t width, int32_t height,
                                    const my_rect_t* bounds) {
  (void)cursor;
  (void)pixels;
  (void)stride;
  (void)width;
  (void)height;
  (void)bounds;
  return MY_RET_OK;
}

int screen_enqueue_render_buffer(screen_buffer_t buffer) {
  if (buffer == NULL || !host_buffer_acquired) return -1;
  host_buffer_acquired = false;
  return 0;
}

int screen_dequeue_window_render_buffer(screen_buffer_t* buffer,
                                        screen_window_t window, int flags) {
  (void)window;
  (void)flags;
  if (host_buffer_acquired) return -1;
  *buffer = (screen_buffer_t)host_screen_pixels;
  host_buffer_acquired = true;
  return 0;
}

int screen_get_buffer_property_pv(screen_buffer_t buffer, int property,
                                  void** value) {
  (void)buffer;
  if (property != SCREEN_PROPERTY_POINTER) return -1;
  *value = host_screen_pixels;
  return 0;
}

int screen_get_buffer_property_iv(screen_buffer_t buffer, int property,
                                  int* value) {
  (void)buffer;
  if (property != SCREEN_PROPERTY_STRIDE) return -1;
  *value = 64 * 4;
  return 0;
}

int screen_destroy_window_buffers(screen_window_t window) {
  (void)window;
  host_buffer_acquired = false;
  return 0;
}

int screen_set_window_property_iv(screen_window_t window, int property,
                                  const int* value) {
  (void)window;
  (void)property;
  (void)value;
  return 0;
}

int screen_create_window_buffers(screen_window_t window, int count) {
  (void)window;
  (void)count;
  return 0;
}

int screen_flush_context(screen_context_t context, int flags) {
  (void)context;
  (void)flags;
  return 0;
}

int screen_set_session_property_iv(screen_session_t session, int property,
                                   const int* value) {
  (void)session;
  (void)property;
  (void)value;
  return 0;
}

int screen_post_window(screen_window_t window, screen_buffer_t buffer,
                       int count, const int* rects, int flags) {
  (void)window;
  (void)buffer;
  (void)count;
  (void)rects;
  (void)flags;
  host_native_posts++;
  host_buffer_acquired = false;
  return 0;
}

TEST(screen_gles2_host_same_resize_retries_after_gl_failure) {
  my_allocator_t* debug = my_allocator_debug_create(NULL);
  my_screen_pal_t pal;
  my_screen_window_t window;
  my_ret_t first;
  my_ret_t second;
  ASSERT_NOT_NULL(debug);
  memset(&pal, 0, sizeof(pal));
  memset(&window, 0, sizeof(window));
  pal.allocator = debug;
  window.pal = &pal;
  window.native = (screen_window_t)1;
  window.width = 64;
  window.height = 48;
  window.gl = (my_pal_gl_t*)1;
  host_fail_pbuffer = 1;
  host_native_posts = 0;
  first = screen_win_resize(&window.base, 32, 24);
  second = screen_win_resize(&window.base, 32, 24);
  ASSERT_NEQ(first, MY_RET_OK);
  ASSERT_NEQ(second, MY_RET_OK);
  ASSERT_EQ(host_gl_width, 64);
  ASSERT_EQ(host_gl_height, 48);
  ASSERT_EQ(host_native_posts, 0);

  host_fail_pbuffer = 0;
  ASSERT_EQ(screen_win_resize(&window.base, 32, 24), MY_RET_OK);
  ASSERT_EQ(host_gl_width, 32);
  ASSERT_EQ(host_gl_height, 24);
  ASSERT_EQ(host_native_posts, 0);
  ASSERT_NOT_NULL(window.lcd);
  ASSERT_EQ(my_lcd_get_width(window.lcd->mem), 32u);
  ASSERT_EQ(my_lcd_get_height(window.lcd->mem), 24u);
  screen_lcd_destroy(window.lcd);
  window.lcd = NULL;
  ASSERT_EQ(my_allocator_debug_leak_count(debug), 0);
  my_allocator_debug_destroy(debug);
}

TEST_MAIN_BEGIN()
  RUN_TEST(screen_gles2_host_same_resize_retries_after_gl_failure);
TEST_MAIN_END()

#else
#include "test_framework.h"
#include "mypal/screen/my_pal_screen.h"
#include "myui/my_window.h"
#include <EGL/egl.h>
#include <GLES2/gl2.h>
#include <errno.h>
#include <screen/screen.h>

static const uint8_t quadrant_colors[4][4] = {
    {255u, 0u, 0u, 255u},
    {0u, 255u, 0u, 255u},
    {0u, 0u, 255u, 255u},
    {255u, 255u, 0u, 255u}
};

static int fail_post;
static int fail_pbuffer;
static int native_posts;

int __real_screen_post_window(screen_window_t window, screen_buffer_t buffer,
                              int count, const int* rects, int flags);
EGLSurface __real_eglCreatePbufferSurface(EGLDisplay display, EGLConfig config,
                                          const EGLint* attributes);

int __wrap_screen_post_window(screen_window_t window, screen_buffer_t buffer,
                              int count, const int* rects, int flags) {
  native_posts++;
  if (fail_post != 0) {
    fail_post = 0;
    errno = EWOULDBLOCK;
    return -1;
  }
  return __real_screen_post_window(window, buffer, count, rects, flags);
}

EGLSurface __wrap_eglCreatePbufferSurface(EGLDisplay display, EGLConfig config,
                                          const EGLint* attributes) {
  if (fail_pbuffer != 0) return EGL_NO_SURFACE;
  return __real_eglCreatePbufferSurface(display, config, attributes);
}

typedef struct gles_fixture_t {
  my_allocator_t* debug;
  my_pal_t* pal;
  my_pal_window_t* window;
  my_pal_gl_t* gl;
  my_lcd_t* lcd;
} gles_fixture_t;

static void fixture_destroy(gles_fixture_t* fixture) {
  if (fixture->window != NULL) my_pal_window_destroy(fixture->window);
  if (fixture->pal != NULL) my_pal_destroy(fixture->pal);
  if (fixture->debug != NULL) {
    ASSERT_EQ(my_allocator_debug_leak_count(fixture->debug), 0);
    my_allocator_debug_destroy(fixture->debug);
  }
  memset(fixture, 0, sizeof(*fixture));
}

static bool fixture_create(gles_fixture_t* fixture) {
  memset(fixture, 0, sizeof(*fixture));
  fixture->debug = my_allocator_debug_create(NULL);
  if (fixture->debug == NULL) return false;
  fixture->pal = my_pal_create(fixture->debug);
  if (fixture->pal == NULL || my_pal_screen_native_context(fixture->pal) == NULL) {
    fixture_destroy(fixture);
    return false;
  }
  fixture->window = my_pal_window_create(fixture->pal, 64, 48, "QNX ES2 pbuffer");
  if (fixture->window == NULL) {
    fixture_destroy(fixture);
    return false;
  }
  fixture->gl = my_pal_window_gl_enable_api(fixture->window, MY_PAL_GL_API_GLES2);
  fixture->lcd = my_pal_window_get_lcd(fixture->window);
  if (fixture->gl == NULL || fixture->lcd == NULL) {
    fixture_destroy(fixture);
    return false;
  }
  return true;
}

static bool draw_quadrants(my_pal_gl_t* gl) {
  int32_t width = 0;
  int32_t height = 0;
  int32_t part;
  if (my_pal_gl_make_current(gl) != MY_RET_OK ||
      my_pal_gl_get_size(gl, &width, &height) != MY_RET_OK || width < 2 ||
      height < 2) {
    return false;
  }
  glViewport(0, 0, width, height);
  glDisable(GL_SCISSOR_TEST);
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
  glEnable(GL_SCISSOR_TEST);
  for (part = 0; part < 4; ++part) {
    int32_t right = part & 1;
    int32_t bottom = part >> 1;
    glClearColor(quadrant_colors[part][0] / 255.0f,
                 quadrant_colors[part][1] / 255.0f,
                 quadrant_colors[part][2] / 255.0f, 1.0f);
    glScissor(right * (width / 2), (1 - bottom) * (height / 2), width / 2,
              height / 2);
    glClear(GL_COLOR_BUFFER_BIT);
  }
  glFinish();
  return glGetError() == GL_NO_ERROR;
}

static bool verify_quadrants(gles_fixture_t* fixture) {
  int32_t width = (int32_t)my_lcd_get_width(fixture->lcd);
  int32_t height = (int32_t)my_lcd_get_height(fixture->lcd);
  uint32_t stride = my_lcd_get_stride(fixture->lcd);
  const uint8_t* pixels = my_lcd_get_buffer(fixture->lcd);
  int32_t part;
  if (pixels == NULL || width < 2 || height < 2) return false;
  if (my_lcd_begin_frame(fixture->lcd, NULL) != MY_RET_OK) return false;
  pixels = my_lcd_get_buffer(fixture->lcd);
  for (part = 0; part < 4; ++part) {
    int32_t x = (part & 1) ? width - 3 : 2;
    int32_t y = (part >> 1) ? height - 3 : 2;
    const uint8_t* actual = pixels + (size_t)y * stride + (size_t)x * 4u;
    if (memcmp(actual, quadrant_colors[part], 4u) != 0) {
      printf("  pixel %d at (%d,%d): got %u,%u,%u,%u expected %u,%u,%u,%u\n",
             part, x, y, actual[0], actual[1], actual[2], actual[3],
             quadrant_colors[part][0], quadrant_colors[part][1],
             quadrant_colors[part][2], quadrant_colors[part][3]);
      (void)my_lcd_end_frame(fixture->lcd);
      return false;
    }
  }
  return my_lcd_end_frame(fixture->lcd) == MY_RET_OK;
}

TEST(screen_gles2_mount_pixels_resize_and_window_isolation) {
  gles_fixture_t fixture;
  gles_fixture_t other;
  GLuint texture = 0;
  ASSERT_TRUE(fixture_create(&fixture));
  ASSERT_NOT_NULL(fixture.gl);
  ASSERT_EQ(my_pal_window_gl_enable_api(fixture.window, MY_PAL_GL_API_GLES2),
            fixture.gl);
  ASSERT_EQ(my_pal_window_gl_enable(fixture.window), fixture.gl);
  ASSERT_TRUE(my_pal_window_gl_enable_api(fixture.window, MY_PAL_GL_API_OPENGL) ==
              NULL);
  ASSERT_TRUE(draw_quadrants(fixture.gl));
  ASSERT_EQ(my_pal_gl_swap_buffers(fixture.gl), MY_RET_OK);
  ASSERT_TRUE(verify_quadrants(&fixture));
  glGenTextures(1, &texture);
  ASSERT_TRUE(texture != 0u);
  glBindTexture(GL_TEXTURE_2D, texture);
  ASSERT_EQ(glGetError(), GL_NO_ERROR);
  ASSERT_EQ(my_pal_window_resize(fixture.window, 32, 24), MY_RET_OK);
  ASSERT_TRUE(draw_quadrants(fixture.gl));
  ASSERT_TRUE(glIsTexture(texture) == GL_TRUE);
  ASSERT_EQ(my_pal_gl_swap_buffers(fixture.gl), MY_RET_OK);
  ASSERT_TRUE(verify_quadrants(&fixture));

  memset(&other, 0, sizeof(other));
  other.debug = my_allocator_debug_create(NULL);
  ASSERT_NOT_NULL(other.debug);
  other.pal = my_pal_create(other.debug);
  ASSERT_NOT_NULL(other.pal);
  other.window = my_pal_window_create(other.pal, 64, 48, "QNX ES2 second");
  ASSERT_NOT_NULL(other.window);
  other.gl = my_pal_window_gl_enable_api(other.window, MY_PAL_GL_API_GLES2);
  other.lcd = my_pal_window_get_lcd(other.window);
  ASSERT_NOT_NULL(other.gl);
  ASSERT_NOT_NULL(other.lcd);
  ASSERT_TRUE(other.gl != fixture.gl);
  ASSERT_TRUE(draw_quadrants(other.gl));
  ASSERT_EQ(my_pal_gl_swap_buffers(other.gl), MY_RET_OK);
  ASSERT_TRUE(verify_quadrants(&other));
  ASSERT_TRUE(verify_quadrants(&fixture));
  my_pal_gl_destroy(other.gl);
  other.gl = NULL;
  fixture_destroy(&other);
  ASSERT_EQ(my_pal_gl_make_current(fixture.gl), MY_RET_OK);
  glDeleteTextures(1, &texture);
  my_pal_gl_destroy(fixture.gl);
  fixture.gl = NULL;
  fixture_destroy(&fixture);
}

TEST(screen_gles2_pending_post_is_reported_and_retried) {
  gles_fixture_t fixture;
  ASSERT_TRUE(fixture_create(&fixture));
  fail_post = 1;
  native_posts = 0;
  ASSERT_TRUE(draw_quadrants(fixture.gl));
  ASSERT_EQ(my_pal_gl_swap_buffers(fixture.gl), MY_RET_PENDING);
  ASSERT_EQ(my_pal_gl_swap_buffers(fixture.gl), MY_RET_OK);
  ASSERT_EQ(native_posts, 2);
  ASSERT_TRUE(verify_quadrants(&fixture));
  my_pal_gl_destroy(fixture.gl);
  fixture.gl = NULL;
  fixture_destroy(&fixture);
}

TEST(screen_gles2_resize_failure_preserves_context) {
  gles_fixture_t fixture;
  GLuint texture = 0;
  int32_t width = 0;
  int32_t height = 0;
  ASSERT_TRUE(fixture_create(&fixture));
  ASSERT_TRUE(draw_quadrants(fixture.gl));
  glGenTextures(1, &texture);
  ASSERT_TRUE(texture != 0u);
  glBindTexture(GL_TEXTURE_2D, texture);
  ASSERT_EQ(glGetError(), GL_NO_ERROR);
  fail_pbuffer = 1;
  ASSERT_NEQ(my_pal_window_resize(fixture.window, 32, 24), MY_RET_OK);
  ASSERT_TRUE(glIsTexture(texture) == GL_TRUE);
  ASSERT_EQ(my_pal_gl_get_size(fixture.gl, &width, &height), MY_RET_OK);
  ASSERT_EQ(width, 64);
  ASSERT_EQ(height, 48);
  fail_pbuffer = 0;
  ASSERT_TRUE(draw_quadrants(fixture.gl));
  ASSERT_TRUE(glIsTexture(texture) == GL_TRUE);
  ASSERT_EQ(my_pal_gl_swap_buffers(fixture.gl), MY_RET_OK);
  ASSERT_TRUE(verify_quadrants(&fixture));
  glDeleteTextures(1, &texture);
  my_pal_gl_destroy(fixture.gl);
  fixture.gl = NULL;
  fixture_destroy(&fixture);
}

TEST(screen_gles2_same_resize_retries_after_pbuffer_failure) {
  gles_fixture_t fixture;
  int32_t width = 0;
  int32_t height = 0;
  ASSERT_TRUE(fixture_create(&fixture));
  native_posts = 0;
  fail_pbuffer = 1;
  ASSERT_NEQ(my_pal_window_resize(fixture.window, 32, 24), MY_RET_OK);
  ASSERT_EQ(my_pal_gl_get_size(fixture.gl, &width, &height), MY_RET_OK);
  ASSERT_EQ(width, 64);
  ASSERT_EQ(height, 48);
  ASSERT_NEQ(my_pal_gl_swap_buffers(fixture.gl), MY_RET_OK);
  ASSERT_EQ(native_posts, 0);
  ASSERT_NEQ(my_pal_window_resize(fixture.window, 32, 24), MY_RET_OK);
  ASSERT_EQ(my_pal_gl_get_size(fixture.gl, &width, &height), MY_RET_OK);
  ASSERT_EQ(width, 64);
  ASSERT_EQ(height, 48);
  ASSERT_EQ(native_posts, 0);

  fail_pbuffer = 0;
  ASSERT_EQ(my_pal_window_resize(fixture.window, 32, 24), MY_RET_OK);
  ASSERT_EQ(my_pal_gl_get_size(fixture.gl, &width, &height), MY_RET_OK);
  ASSERT_EQ(width, 32);
  ASSERT_EQ(height, 24);
  fixture.lcd = my_pal_window_get_lcd(fixture.window);
  ASSERT_NOT_NULL(fixture.lcd);
  ASSERT_TRUE(draw_quadrants(fixture.gl));
  ASSERT_EQ(my_pal_gl_swap_buffers(fixture.gl), MY_RET_OK);
  ASSERT_EQ(native_posts, 1);
  ASSERT_TRUE(verify_quadrants(&fixture));
  my_pal_gl_destroy(fixture.gl);
  fixture.gl = NULL;
  fixture_destroy(&fixture);
}

TEST(screen_gles2_window_pending_restores_dirty) {
  my_allocator_t* debug = my_allocator_debug_create(NULL);
  my_pal_t* pal;
  my_window_t* window;
  ASSERT_NOT_NULL(debug);
  pal = my_pal_create(debug);
  ASSERT_NOT_NULL(pal);
  window = my_window_create(debug, pal, 64, 48, "QNX ES2 window retry");
  ASSERT_NOT_NULL(window);
  ASSERT_EQ(my_window_enable_gl(window), MY_RET_OK);
  my_widget_invalidate((my_widget_t*)window, NULL);
  fail_post = 1;
  native_posts = 0;
  my_window_paint(window);
  ASSERT_EQ(native_posts, 1);
  ASSERT_TRUE(my_dirty_rects_count(&window->dirty) > 0u);
  my_window_paint(window);
  ASSERT_EQ(native_posts, 2);
  ASSERT_EQ(my_dirty_rects_count(&window->dirty), 0u);
  my_widget_unref((my_widget_t*)window);
  my_pal_destroy(pal);
  ASSERT_EQ(my_allocator_debug_leak_count(debug), 0);
  my_allocator_debug_destroy(debug);
}

TEST(screen_gles2_failed_enable_cleans_up) {
  my_allocator_t* debug = my_allocator_debug_create(NULL);
  my_pal_t* pal;
  my_pal_window_t* window;
  my_pal_gl_t* gl;
  ASSERT_NOT_NULL(debug);
  pal = my_pal_create(debug);
  ASSERT_NOT_NULL(pal);
  window = my_pal_window_create(pal, 64, 48, "QNX ES2 create failure");
  ASSERT_NOT_NULL(window);
  fail_pbuffer = 1;
  gl = my_pal_window_gl_enable_api(window, MY_PAL_GL_API_GLES2);
  fail_pbuffer = 0;
  ASSERT_TRUE(gl == NULL);
  ASSERT_TRUE(my_pal_window_gl_enable_api(window, MY_PAL_GL_API_OPENGL) == NULL);
  my_pal_window_destroy(window);
  my_pal_destroy(pal);
  ASSERT_EQ(my_allocator_debug_leak_count(debug), 0);
  my_allocator_debug_destroy(debug);
}

int main(void) {
  my_pal_t* probe;
  setvbuf(stdout, NULL, _IONBF, 0);
  probe = my_pal_create(NULL);
  if (probe == NULL || my_pal_screen_native_context(probe) == NULL) {
    if (probe != NULL) my_pal_destroy(probe);
    printf("SKIP: no usable QNX Screen service\n");
    return getenv("BREAK_QNX_SCREEN_REQUIRED") != NULL ? 1 : 77;
  }
  my_pal_destroy(probe);
  printf("=== Running Tests ===\n");
  RUN_TEST(screen_gles2_mount_pixels_resize_and_window_isolation);
  RUN_TEST(screen_gles2_pending_post_is_reported_and_retried);
  RUN_TEST(screen_gles2_resize_failure_preserves_context);
  RUN_TEST(screen_gles2_same_resize_retries_after_pbuffer_failure);
  RUN_TEST(screen_gles2_window_pending_restores_dirty);
  RUN_TEST(screen_gles2_failed_enable_cleans_up);
  printf("\n=== Results: %d passed, %d failed, %d total ===\n",
         g_test_pass, g_test_fail, g_test_count);
  return g_test_fail > 0 ? 1 : 0;
}
#endif
