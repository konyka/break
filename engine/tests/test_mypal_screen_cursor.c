#include "test_framework.h"
#include "mypal/screen/my_pal_screen_cursor.h"
#include "mypal/screen/my_pal_screen.h"
#include <limits.h>
#include <stdint.h>

static void fill_bytes(uint8_t* pixels, uint32_t stride, int32_t width,
                       int32_t height, const uint8_t color[4]) {
  int32_t y;
  for (y = 0; y < height; ++y) {
    int32_t x;
    for (x = 0; x < width; ++x) {
      memcpy(pixels + (size_t)y * stride + (size_t)x * 4u, color, 4u);
    }
  }
}

static uint32_t different_pixels(const uint8_t* left, const uint8_t* right,
                                 size_t bytes) {
  uint32_t count = 0u;
  size_t i;
  for (i = 0u; i < bytes; ++i) {
    if (left[i] != right[i]) count++;
  }
  return count;
}

static uint32_t pixel_signature(const uint8_t* pixels, size_t bytes) {
  uint32_t hash = 2166136261u;
  size_t i;
  for (i = 0u; i < bytes; ++i) {
    hash = (hash ^ pixels[i]) * 16777619u;
  }
  return hash;
}

TEST(cursor_visibility_shapes_and_invalid_shape)
{
  my_screen_cursor_t cursor;
  my_rect_t rect;
  my_screen_cursor_init(&cursor);
  ASSERT_EQ(my_screen_cursor_bounds(&cursor, 64, 48, &rect), MY_RET_OK);
  ASSERT_TRUE(my_rect_is_empty(&rect));
  my_screen_cursor_set_enabled(&cursor, true);
  ASSERT_EQ(my_screen_cursor_bounds(&cursor, 64, 48, &rect), MY_RET_OK);
  ASSERT_TRUE(my_rect_is_empty(&rect));
  my_screen_cursor_set_position(&cursor, 4, 5);
  ASSERT_EQ(my_screen_cursor_set_shape(&cursor, MY_CURSOR_ARROW), MY_RET_OK);
  ASSERT_EQ(my_screen_cursor_bounds(&cursor, 64, 48, &rect), MY_RET_OK);
  ASSERT_EQ(rect.x, 4);
  ASSERT_EQ(rect.y, 5);
  ASSERT_EQ(rect.w, 16);
  ASSERT_EQ(rect.h, 16);
  ASSERT_EQ(my_screen_cursor_set_shape(&cursor, MY_CURSOR_TEXT), MY_RET_OK);
  ASSERT_EQ(my_screen_cursor_bounds(&cursor, 64, 48, &rect), MY_RET_OK);
  ASSERT_EQ(rect.x, -3);
  ASSERT_EQ(rect.y, -2);
  ASSERT_EQ(my_screen_cursor_set_shape(&cursor, MY_CURSOR_HAND), MY_RET_OK);
  ASSERT_EQ(my_screen_cursor_bounds(&cursor, 64, 48, &rect), MY_RET_OK);
  ASSERT_EQ(rect.x, 0);
  ASSERT_EQ(rect.y, 5);
  ASSERT_EQ(my_screen_cursor_set_shape(&cursor, (my_cursor_t)99),
            MY_RET_INVALID_PARAMS);
  ASSERT_EQ(cursor.shape, MY_CURSOR_HAND);
  my_screen_cursor_set_enabled(&cursor, false);
  ASSERT_EQ(my_screen_cursor_bounds(&cursor, 64, 48, &rect), MY_RET_OK);
  ASSERT_TRUE(my_rect_is_empty(&rect));
}

TEST(cursor_composite_distinguishes_all_shapes)
{
  enum { WIDTH = 40, HEIGHT = 30, STRIDE = WIDTH * 4 };
  const uint8_t background[4] = {10u, 20u, 30u, 255u};
  uint8_t pixels[STRIDE * HEIGHT];
  uint8_t original[STRIDE * HEIGHT];
  uint8_t arrow[STRIDE * HEIGHT];
  uint8_t text[STRIDE * HEIGHT];
  my_screen_cursor_t cursor;
  my_rect_t rect;
  uint32_t changed;
  my_screen_cursor_init(&cursor);
  my_screen_cursor_set_enabled(&cursor, true);
  my_screen_cursor_set_position(&cursor, 8, 8);
  fill_bytes(pixels, STRIDE, WIDTH, HEIGHT, background);
  memcpy(original, pixels, sizeof(pixels));
  ASSERT_EQ(my_screen_cursor_composite(&cursor, pixels, STRIDE, WIDTH, HEIGHT,
                                       &rect), MY_RET_OK);
  changed = different_pixels(pixels, original, sizeof(pixels));
  ASSERT_TRUE(changed > 0u);
  ASSERT_TRUE(changed <= MY_SCREEN_CURSOR_MAX_PIXELS * 4u);
  memcpy(arrow, pixels, sizeof(arrow));
  memcpy(pixels, original, sizeof(pixels));
  ASSERT_EQ(my_screen_cursor_set_shape(&cursor, MY_CURSOR_TEXT), MY_RET_OK);
  ASSERT_EQ(my_screen_cursor_composite(&cursor, pixels, STRIDE, WIDTH, HEIGHT,
                                       &rect), MY_RET_OK);
  memcpy(text, pixels, sizeof(text));
  ASSERT_NEQ(pixel_signature(arrow, sizeof(arrow)),
             pixel_signature(text, sizeof(text)));
  memcpy(pixels, original, sizeof(pixels));
  ASSERT_EQ(my_screen_cursor_set_shape(&cursor, MY_CURSOR_HAND), MY_RET_OK);
  ASSERT_EQ(my_screen_cursor_composite(&cursor, pixels, STRIDE, WIDTH, HEIGHT,
                                       &rect), MY_RET_OK);
  ASSERT_NEQ(pixel_signature(arrow, sizeof(arrow)),
             pixel_signature(pixels, sizeof(pixels)));
  ASSERT_NEQ(pixel_signature(text, sizeof(text)),
             pixel_signature(pixels, sizeof(pixels)));
  memcpy(pixels, original, sizeof(pixels));
  my_screen_cursor_set_enabled(&cursor, false);
  ASSERT_EQ(my_screen_cursor_composite(&cursor, pixels, STRIDE, WIDTH, HEIGHT,
                                       &rect), MY_RET_OK);
  ASSERT_TRUE(my_rect_is_empty(&rect));
  ASSERT_EQ(different_pixels(pixels, original, sizeof(pixels)), 0u);
}

TEST(cursor_clips_edges_extremes_and_stride_padding)
{
  enum { WIDTH = 32, HEIGHT = 24, STRIDE = 40 * 4 };
  const uint8_t background[4] = {12u, 24u, 36u, 255u};
  uint8_t pixels[STRIDE * HEIGHT];
  uint8_t original[STRIDE * HEIGHT];
  my_screen_cursor_t cursor;
  my_rect_t rect;
  int32_t y;
  my_screen_cursor_init(&cursor);
  my_screen_cursor_set_enabled(&cursor, true);
  memset(pixels, 0xa5, sizeof(pixels));
  fill_bytes(pixels, STRIDE, WIDTH, HEIGHT, background);
  memcpy(original, pixels, sizeof(pixels));
  my_screen_cursor_set_position(&cursor, -1, -1);
  ASSERT_EQ(my_screen_cursor_composite(&cursor, pixels, STRIDE, WIDTH, HEIGHT,
                                       &rect), MY_RET_OK);
  ASSERT_EQ(rect.x, -1);
  ASSERT_EQ(rect.y, -1);
  ASSERT_EQ(rect.w, 15);
  ASSERT_EQ(rect.h, 15);
  for (y = 0; y < HEIGHT; ++y) {
    ASSERT_EQ(memcmp(pixels + (size_t)y * STRIDE + WIDTH * 4u,
                     original + (size_t)y * STRIDE + WIDTH * 4u,
                     STRIDE - WIDTH * 4u), 0);
  }
  memcpy(pixels, original, sizeof(pixels));
  my_screen_cursor_set_position(&cursor, 31, 23);
  ASSERT_EQ(my_screen_cursor_composite(&cursor, pixels, STRIDE, WIDTH, HEIGHT,
                                       &rect), MY_RET_OK);
  ASSERT_EQ(rect.x, 31);
  ASSERT_EQ(rect.y, 23);
  ASSERT_EQ(rect.w, 1);
  ASSERT_EQ(rect.h, 1);
  ASSERT_TRUE(different_pixels(pixels, original, sizeof(pixels)) > 0u);
  my_screen_cursor_set_position(&cursor, INT32_MIN, INT32_MIN);
  ASSERT_EQ(my_screen_cursor_composite(&cursor, pixels, STRIDE, WIDTH, HEIGHT,
                                       &rect), MY_RET_OK);
  ASSERT_TRUE(my_rect_is_empty(&rect));
  my_screen_cursor_set_position(&cursor, INT32_MAX, INT32_MAX);
  ASSERT_EQ(my_screen_cursor_composite(&cursor, pixels, STRIDE, WIDTH, HEIGHT,
                                       &rect), MY_RET_OK);
  ASSERT_TRUE(my_rect_is_empty(&rect));
  ASSERT_EQ(my_screen_cursor_composite(&cursor, pixels, WIDTH * 4u - 1u,
                                       WIDTH, HEIGHT, &rect),
            MY_RET_INVALID_PARAMS);
}

TEST(cursor_state_and_pixels_are_window_local)
{
  enum { WIDTH = 24, HEIGHT = 24, STRIDE = WIDTH * 4 };
  const uint8_t background[4] = {7u, 14u, 21u, 255u};
  uint8_t first[STRIDE * HEIGHT];
  uint8_t second[STRIDE * HEIGHT];
  uint8_t original[STRIDE * HEIGHT];
  my_screen_cursor_t left;
  my_screen_cursor_t right;
  my_rect_t rect;
  my_screen_cursor_init(&left);
  my_screen_cursor_init(&right);
  my_screen_cursor_set_enabled(&left, true);
  my_screen_cursor_set_position(&left, 5, 6);
  fill_bytes(first, STRIDE, WIDTH, HEIGHT, background);
  fill_bytes(second, STRIDE, WIDTH, HEIGHT, background);
  memcpy(original, second, sizeof(original));
  ASSERT_EQ(my_screen_cursor_composite(&left, first, STRIDE, WIDTH, HEIGHT,
                                       &rect), MY_RET_OK);
  ASSERT_EQ(my_screen_cursor_composite(&right, second, STRIDE, WIDTH, HEIGHT,
                                       &rect), MY_RET_OK);
  ASSERT_TRUE(different_pixels(first, original, sizeof(first)) > 0u);
  ASSERT_EQ(different_pixels(second, original, sizeof(second)), 0u);
  my_screen_cursor_set_position(&right, 20, 20);
  ASSERT_EQ(my_screen_cursor_bounds(&left, WIDTH, HEIGHT, &rect), MY_RET_OK);
  ASSERT_EQ(rect.x, 5);
  ASSERT_EQ(rect.y, 6);
}

#ifdef MYUI_PAL_SCREEN
#include <platform/time.h>
#include <screen/screen.h>
#include <errno.h>

typedef struct cursor_fixture_t {
  my_pal_t* pal;
  my_pal_window_t* window;
  my_pal_main_loop_t* loop;
  my_lcd_t* lcd;
  my_pal_window_t* last_event_window;
  int pointer_events;
  int move_events;
  int timer_events;
  int user_events;
} cursor_fixture_t;

static int g_fail_post;
static uint32_t g_native_posts;
static int g_last_post_rect[4];

int __real_screen_post_window(screen_window_t window, screen_buffer_t buffer,
                              int count, const int* rects, int flags);

int __wrap_screen_post_window(screen_window_t window, screen_buffer_t buffer,
                              int count, const int* rects, int flags) {
  g_native_posts++;
  memset(g_last_post_rect, 0, sizeof(g_last_post_rect));
  if (count > 0 && rects != NULL) {
    memcpy(g_last_post_rect, rects, (size_t)count * 4u * sizeof(int));
  }
  if (g_fail_post != 0) {
    g_fail_post = 0;
    errno = EWOULDBLOCK;
    return -1;
  }
  return __real_screen_post_window(window, buffer, count, rects, flags);
}

static my_ret_t cursor_event_handler(void* context, my_pal_window_t* window,
                                     const my_event_t* event) {
  cursor_fixture_t* fixture = (cursor_fixture_t*)context;
  if (event->type == MY_EVENT_POINTER_MOVE ||
      event->type == MY_EVENT_POINTER_DOWN ||
      event->type == MY_EVENT_POINTER_UP) {
    fixture->last_event_window = window;
    fixture->pointer_events++;
    if (event->type == MY_EVENT_POINTER_MOVE) fixture->move_events++;
  } else if (event->type == MY_EVENT_USER) {
    fixture->user_events++;
    (void)my_pal_main_loop_quit(fixture->loop);
  }
  return MY_RET_OK;
}

static my_ret_t cursor_quit_timer(void* context) {
  cursor_fixture_t* fixture = (cursor_fixture_t*)context;
  fixture->timer_events++;
  (void)my_pal_main_loop_quit(fixture->loop);
  return MY_RET_FAIL;
}

static bool fixture_create(cursor_fixture_t* fixture,
                           const my_allocator_t* allocator, int32_t width,
                           int32_t height) {
  memset(fixture, 0, sizeof(*fixture));
  g_fail_post = 0;
  g_native_posts = 0u;
  fixture->pal = my_pal_create(allocator);
  if (fixture->pal == NULL) return false;
  fixture->window = my_pal_window_create(fixture->pal, width, height,
                                         "myui software cursor");
  fixture->loop = my_pal_main_loop_create(fixture->pal);
  if (fixture->window == NULL || fixture->loop == NULL) return false;
  fixture->lcd = my_pal_window_get_lcd(fixture->window);
  return fixture->lcd != NULL &&
         my_pal_set_event_handler(fixture->pal, cursor_event_handler,
                                  fixture) == MY_RET_OK;
}

static void fixture_destroy(cursor_fixture_t* fixture) {
  if (fixture->loop != NULL) my_pal_main_loop_destroy(fixture->loop);
  if (fixture->window != NULL) my_pal_window_destroy(fixture->window);
  if (fixture->pal != NULL) my_pal_destroy(fixture->pal);
  memset(fixture, 0, sizeof(*fixture));
}

static bool native_pointer_to(cursor_fixture_t* fixture,
                              my_pal_window_t* window, int x, int y) {
  screen_context_t context =
      (screen_context_t)my_pal_screen_native_context(fixture->pal);
  screen_window_t native = (screen_window_t)my_pal_screen_native_window(window);
  screen_event_t event = NULL;
  int type = SCREEN_EVENT_POINTER;
  int position[2] = {x, y};
  int flags = SCREEN_FLAG_POSITION_VALID;
  int buttons = 0;
  int result;
  if (screen_create_event(&event) != 0 ||
      screen_set_event_property_iv(event, SCREEN_PROPERTY_TYPE, &type) != 0 ||
      screen_set_event_property_pv(event, SCREEN_PROPERTY_WINDOW,
                                   (void**)&native) != 0 ||
      screen_set_event_property_iv(event, SCREEN_PROPERTY_POSITION, position) !=
          0 ||
      screen_set_event_property_iv(event, SCREEN_PROPERTY_FLAGS, &flags) != 0 ||
      screen_set_event_property_iv(event, SCREEN_PROPERTY_BUTTONS, &buttons) !=
          0) {
    if (event != NULL) (void)screen_destroy_event(event);
    return false;
  }
  result = screen_send_event(context, event, getpid());
  (void)screen_destroy_event(event);
  if (result != 0) return false;
  my_pal_main_loop_destroy(fixture->loop);
  fixture->loop = my_pal_main_loop_create(fixture->pal);
  if (fixture->loop == NULL) return false;
  fixture->timer_events = 0;
  fixture->user_events = 0;
  if (my_pal_main_loop_add_timer(fixture->loop, cursor_quit_timer, fixture,
                                 1000u) == 0u) {
    return false;
  }
  event = NULL;
  type = SCREEN_EVENT_USER;
  {
    int data[4] = {0, 0, 0, 0};
    if (screen_create_event(&event) != 0 ||
        screen_set_event_property_iv(event, SCREEN_PROPERTY_TYPE, &type) != 0 ||
        screen_set_event_property_iv(event, SCREEN_PROPERTY_USER_DATA, data) != 0) {
      if (event != NULL) (void)screen_destroy_event(event);
      return false;
    }
  }
  result = screen_send_event(context, event, getpid());
  (void)screen_destroy_event(event);
  if (result != 0) return false;
  return my_pal_main_loop_run(fixture->loop) == MY_RET_OK &&
         fixture->timer_events == 0 && fixture->user_events == 1;
}

static bool native_pointer(cursor_fixture_t* fixture, int x, int y) {
  fixture->timer_events = 0;
  return native_pointer_to(fixture, fixture->window, x, y);
}

static my_ret_t window_frame(my_pal_window_t* window, const my_rect_t* dirty,
                             const uint8_t color[4]) {
  my_lcd_t* lcd = my_pal_window_get_lcd(window);
  my_rect_t full;
  my_ret_t result;
  if (lcd == NULL) return MY_RET_FAIL;
  full = my_rect_init(0, 0, (int32_t)my_lcd_get_width(lcd),
                      (int32_t)my_lcd_get_height(lcd));
  result = my_lcd_begin_frame(lcd, dirty);
  if (result != MY_RET_OK) return result;
  result = my_lcd_fill_rect(lcd, dirty != NULL ? dirty : &full,
                            my_color_rgba(color[0], color[1], color[2], color[3]));
  if (result != MY_RET_OK) return result;
  return my_lcd_end_frame(lcd);
}

static bool pixel_is(my_lcd_t* lcd, int32_t x, int32_t y,
                     const uint8_t color[4]) {
  uint8_t* pixels = my_lcd_get_buffer(lcd);
  uint32_t stride = my_lcd_get_stride(lcd);
  if (pixels == NULL || x < 0 || y < 0 ||
      x >= (int32_t)my_lcd_get_width(lcd) ||
      y >= (int32_t)my_lcd_get_height(lcd)) {
    return false;
  }
  return memcmp(pixels + (size_t)y * stride + (size_t)x * 4u, color, 4u) == 0;
}

TEST(screen_native_negative_and_explicit_software_opt_in)
{
  cursor_fixture_t fixture;
  my_pal_screen_software_cursor_state_t state;
  my_ret_t native_result;
  ASSERT_TRUE(fixture_create(&fixture, NULL, 64, 48));
  native_result = my_pal_window_set_cursor(fixture.window, MY_CURSOR_ARROW);
  printf("\n  screen_cursor_native_initial=%d\n", native_result);
  ASSERT_TRUE(native_result == MY_RET_NOT_SUPPORTED ||
              native_result == MY_RET_OK);
  if (native_result == MY_RET_NOT_SUPPORTED) {
    ASSERT_TRUE(my_pal_screen_test_native_pointer_session(fixture.window) ==
                NULL);
  }
  ASSERT_EQ(my_pal_screen_software_cursor_set_enabled(fixture.window, true),
            MY_RET_OK);
  ASSERT_TRUE(my_pal_screen_test_native_pointer_session(fixture.window) ==
              NULL);
  ASSERT_EQ(my_pal_window_set_cursor(fixture.window, MY_CURSOR_TEXT), MY_RET_OK);
  ASSERT_EQ(my_pal_screen_test_software_cursor_state(fixture.window, &state),
            MY_RET_OK);
  ASSERT_TRUE(state.enabled);
  ASSERT_FALSE(state.has_position);
  ASSERT_FALSE(state.visible);
  ASSERT_EQ(state.shape, MY_CURSOR_TEXT);
  ASSERT_EQ(my_pal_window_set_cursor(fixture.window, (my_cursor_t)99),
            MY_RET_INVALID_PARAMS);
  ASSERT_EQ(my_pal_screen_software_cursor_set_enabled(fixture.window, false),
            MY_RET_OK);
  ASSERT_EQ(my_pal_window_set_cursor(fixture.window, MY_CURSOR_ARROW),
            native_result);
  fixture_destroy(&fixture);
}

TEST(screen_cursor_moves_clips_and_preserves_frame_history)
{
  const uint8_t first[4] = {10u, 20u, 30u, 255u};
  const uint8_t second[4] = {30u, 20u, 10u, 255u};
  const my_rect_t dirty = {0, 0, 3, 3};
  cursor_fixture_t fixture;
  my_pal_screen_software_cursor_state_t state;
  my_lcd_t* lcd;
  uint32_t posts;
  ASSERT_TRUE(fixture_create(&fixture, NULL, 64, 48));
  lcd = fixture.lcd;
  ASSERT_EQ(my_pal_screen_software_cursor_set_enabled(fixture.window, true),
            MY_RET_OK);
  ASSERT_EQ(my_pal_window_set_cursor(fixture.window, MY_CURSOR_ARROW), MY_RET_OK);
  ASSERT_TRUE(native_pointer(&fixture, 8, 9));
  ASSERT_EQ(fixture.pointer_events, 0);
  ASSERT_EQ(my_pal_screen_test_software_cursor_state(fixture.window, &state),
            MY_RET_OK);
  ASSERT_TRUE(state.visible);
  ASSERT_EQ(state.x, 8);
  ASSERT_EQ(state.y, 9);
  ASSERT_EQ(window_frame(fixture.window, NULL, first), MY_RET_OK);
  ASSERT_FALSE(pixel_is(lcd, 8, 9, first));
  posts = my_pal_screen_test_post_count(fixture.window);
  ASSERT_EQ(posts, 1u);
  ASSERT_EQ(my_lcd_begin_frame(lcd, NULL), MY_RET_OK);
  ASSERT_TRUE(pixel_is(lcd, 8, 9, first));
  {
    const my_rect_t full = {0, 0, 64, 48};
    ASSERT_EQ(my_lcd_fill_rect(
                  lcd, &full,
                  my_color_rgba(second[0], second[1], second[2], 255)),
              MY_RET_OK);
  }
  ASSERT_EQ(my_lcd_end_frame(lcd), MY_RET_OK);
  ASSERT_FALSE(pixel_is(lcd, 8, 9, second));
  posts = my_pal_screen_test_post_count(fixture.window);
  ASSERT_TRUE(native_pointer(&fixture, 30, 20));
  ASSERT_EQ(my_pal_screen_test_post_count(fixture.window), posts);
  ASSERT_EQ(my_lcd_begin_frame(lcd, &dirty), MY_RET_OK);
  ASSERT_TRUE(pixel_is(lcd, 8, 9, second));
  ASSERT_EQ(my_lcd_fill_rect(
                lcd, &dirty,
                my_color_rgba(second[0], second[1], second[2], 255)),
            MY_RET_OK);
  ASSERT_EQ(my_lcd_end_frame(lcd), MY_RET_OK);
  ASSERT_EQ(g_last_post_rect[0], 0);
  ASSERT_EQ(g_last_post_rect[1], 0);
  ASSERT_EQ(g_last_post_rect[2], 46);
  ASSERT_EQ(g_last_post_rect[3], 36);
  ASSERT_TRUE(pixel_is(lcd, 8, 9, second));
  ASSERT_FALSE(pixel_is(lcd, 30, 20, second));
  ASSERT_EQ(my_pal_window_set_cursor(fixture.window, MY_CURSOR_TEXT), MY_RET_OK);
  ASSERT_EQ(window_frame(fixture.window, &dirty, second), MY_RET_OK);
  ASSERT_EQ(my_pal_screen_test_software_cursor_state(fixture.window, &state),
            MY_RET_OK);
  ASSERT_EQ(state.shape, MY_CURSOR_TEXT);
  ASSERT_TRUE(native_pointer(&fixture, 100, 100));
  ASSERT_EQ(my_pal_screen_test_software_cursor_state(fixture.window, &state),
            MY_RET_OK);
  ASSERT_FALSE(state.visible);
  ASSERT_EQ(window_frame(fixture.window, &dirty, second), MY_RET_OK);
  ASSERT_TRUE(pixel_is(lcd, 30, 20, second));
  ASSERT_TRUE(native_pointer(&fixture, 63, 47));
  ASSERT_EQ(my_pal_screen_test_software_cursor_state(fixture.window, &state),
            MY_RET_OK);
  ASSERT_TRUE(state.visible);
  ASSERT_EQ(window_frame(fixture.window, &dirty, second), MY_RET_OK);
  ASSERT_FALSE(pixel_is(lcd, 63, 47, second));
  ASSERT_EQ(my_pal_screen_software_cursor_set_enabled(fixture.window, false),
            MY_RET_OK);
  ASSERT_EQ(window_frame(fixture.window, &dirty, second), MY_RET_OK);
  ASSERT_TRUE(pixel_is(lcd, 63, 47, second));
  fixture_destroy(&fixture);
}

TEST(screen_cursor_pending_resize_destroy_and_window_isolation)
{
  const uint8_t background[4] = {9u, 18u, 27u, 255u};
  const my_rect_t dirty = {1, 1, 2, 2};
  cursor_fixture_t fixture;
  my_pal_window_t* other = NULL;
  my_lcd_t* other_lcd;
  my_allocator_t* debug = my_allocator_debug_create(NULL);
  my_pal_screen_software_cursor_state_t state;
  ASSERT_NOT_NULL(debug);
  ASSERT_TRUE(fixture_create(&fixture, debug, 64, 48));
  ASSERT_EQ(my_pal_screen_software_cursor_set_enabled(fixture.window, true),
            MY_RET_OK);
  ASSERT_EQ(my_pal_window_set_cursor(fixture.window, MY_CURSOR_ARROW), MY_RET_OK);
  ASSERT_TRUE(native_pointer(&fixture, 10, 10));
  g_fail_post = 1;
  ASSERT_EQ(window_frame(fixture.window, NULL, background), MY_RET_PENDING);
  ASSERT_EQ(my_pal_screen_test_post_count(fixture.window), 0u);
  ASSERT_TRUE(native_pointer(&fixture, 30, 10));
  ASSERT_EQ(my_pal_screen_test_post_count(fixture.window), 0u);
  ASSERT_EQ(my_lcd_begin_frame(fixture.lcd, &dirty), MY_RET_OK);
  ASSERT_TRUE(pixel_is(fixture.lcd, 10, 10, background));
  ASSERT_EQ(my_lcd_fill_rect(fixture.lcd, &dirty,
                             my_color_rgba(background[0], background[1],
                                           background[2], 255)), MY_RET_OK);
  ASSERT_EQ(my_lcd_end_frame(fixture.lcd), MY_RET_OK);
  ASSERT_EQ(my_pal_screen_test_post_count(fixture.window), 1u);
  ASSERT_TRUE(pixel_is(fixture.lcd, 10, 10, background));
  ASSERT_FALSE(pixel_is(fixture.lcd, 30, 10, background));
  ASSERT_EQ(my_pal_window_resize(fixture.window, 20, 20), MY_RET_OK);
  fixture.lcd = my_pal_window_get_lcd(fixture.window);
  ASSERT_NOT_NULL(fixture.lcd);
  ASSERT_EQ(my_pal_screen_test_software_cursor_state(fixture.window, &state),
            MY_RET_OK);
  ASSERT_FALSE(state.visible);
  ASSERT_EQ(window_frame(fixture.window, NULL, background), MY_RET_OK);
  ASSERT_TRUE(pixel_is(fixture.lcd, 10, 10, background));
  ASSERT_EQ(my_pal_window_resize(fixture.window, 64, 48), MY_RET_OK);
  fixture.lcd = my_pal_window_get_lcd(fixture.window);
  ASSERT_EQ(window_frame(fixture.window, NULL, background), MY_RET_OK);
  ASSERT_FALSE(pixel_is(fixture.lcd, 30, 10, background));

  other = my_pal_window_create(fixture.pal, 64, 48, "cursor isolation");
  ASSERT_NOT_NULL(other);
  other_lcd = my_pal_window_get_lcd(other);
  ASSERT_NOT_NULL(other_lcd);
  ASSERT_EQ(window_frame(other, NULL, background), MY_RET_OK);
  ASSERT_TRUE(pixel_is(other_lcd, 30, 10, background));
  ASSERT_EQ(my_pal_screen_software_cursor_set_enabled(other, true), MY_RET_OK);
  ASSERT_EQ(my_pal_window_set_cursor(other, MY_CURSOR_HAND), MY_RET_OK);
  fixture.timer_events = 0;
  ASSERT_TRUE(native_pointer_to(&fixture, other, 40, 30));
  ASSERT_EQ(my_pal_screen_test_software_cursor_state(fixture.window, &state),
            MY_RET_OK);
  ASSERT_EQ(state.x, 30);
  ASSERT_EQ(state.y, 10);
  ASSERT_EQ(window_frame(other, &dirty, background), MY_RET_OK);
  ASSERT_FALSE(pixel_is(other_lcd, 40, 30, background));
  ASSERT_EQ(my_pal_screen_test_software_cursor_state(other, &state), MY_RET_OK);
  ASSERT_EQ(state.shape, MY_CURSOR_HAND);
  my_pal_window_destroy(fixture.window);
  fixture.window = NULL;
  ASSERT_EQ(window_frame(other, &dirty, background), MY_RET_OK);
  ASSERT_FALSE(pixel_is(other_lcd, 40, 30, background));
  my_pal_window_destroy(other);
  fixture_destroy(&fixture);
  ASSERT_EQ(my_allocator_debug_leak_count(debug), 0);
  my_allocator_debug_destroy(debug);
}
#endif

int main(void) {
  setvbuf(stdout, NULL, _IONBF, 0);
  printf("=== Running Tests ===\n");
  RUN_TEST(cursor_visibility_shapes_and_invalid_shape);
  RUN_TEST(cursor_composite_distinguishes_all_shapes);
  RUN_TEST(cursor_clips_edges_extremes_and_stride_padding);
  RUN_TEST(cursor_state_and_pixels_are_window_local);
#ifdef MYUI_PAL_SCREEN
  time_init();
  {
    my_pal_t* probe = my_pal_create(NULL);
    if (probe == NULL) {
      printf("SKIP: no usable QNX Screen service\n");
      return getenv("BREAK_QNX_SCREEN_REQUIRED") != NULL ? 1 : 77;
    }
    my_pal_destroy(probe);
  }
  RUN_TEST(screen_native_negative_and_explicit_software_opt_in);
  RUN_TEST(screen_cursor_moves_clips_and_preserves_frame_history);
  RUN_TEST(screen_cursor_pending_resize_destroy_and_window_isolation);
#endif
  printf("screen_cursor_bounds,max_pixels=%u,steady_state_allocations=0\n",
         MY_SCREEN_CURSOR_MAX_PIXELS);
  printf("\n=== Results: %d passed, %d failed, %d total ===\n",
         g_test_pass, g_test_fail, g_test_count);
  return g_test_fail > 0 ? 1 : 0;
}
