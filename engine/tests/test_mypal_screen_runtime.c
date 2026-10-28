#include "test_framework.h"
#include "mypal/screen/my_pal_screen.h"
#include "myui/my_ui_command_internal.h"
#include <errno.h>
#include <screen/screen.h>
#include <sys/keycodes.h>

#define NATIVE_EVENT_LIMIT 16u

static my_pal_t* g_pal;
static my_pal_window_t* g_window;
static my_pal_main_loop_t* g_loop;
static int g_user_events;
static int g_timer_fires;
static int g_command_executes;
static int g_native_count;
static int g_native_overflow;
static int g_bad_window;
static my_event_t g_native_events[NATIVE_EVENT_LIMIT];
static char g_native_text[NATIVE_EVENT_LIMIT][8];

static my_ret_t screen_event_handler(void* context, my_pal_window_t* window,
                                     const my_event_t* event) {
  (void)context;
  if (event->type == MY_EVENT_USER) g_user_events++;
  if (event->type == MY_EVENT_COMMAND) {
    my_ui_command_dispatch((my_ui_command_t*)event->u.command.data);
  }
  if (event->type != MY_EVENT_USER && event->type != MY_EVENT_COMMAND) {
    if (window != g_window) g_bad_window++;
    if ((uint32_t)g_native_count < NATIVE_EVENT_LIMIT) {
      g_native_events[g_native_count] = *event;
      if ((event->type == MY_EVENT_IME_PREEDIT ||
           event->type == MY_EVENT_IME_COMMIT) &&
          event->u.ime.text != NULL) {
        size_t length = strlen(event->u.ime.text);
        if (length >= sizeof(g_native_text[0])) {
          g_native_overflow++;
          length = sizeof(g_native_text[0]) - 1u;
        }
        memcpy(g_native_text[g_native_count], event->u.ime.text, length);
        g_native_text[g_native_count][length] = '\0';
        g_native_events[g_native_count].u.ime.text =
            g_native_text[g_native_count];
      }
    } else {
      g_native_overflow++;
    }
    g_native_count++;
    if (event->type == MY_EVENT_QUIT) {
      (void)my_pal_main_loop_quit(g_loop);
    }
  }
  return MY_RET_OK;
}

static my_ret_t screen_timer_callback(void* context) {
  (void)context;
  g_timer_fires++;
  (void)my_pal_main_loop_quit(g_loop);
  return MY_RET_FAIL;
}

static my_ret_t screen_destroy_timer_callback(void* context) {
  (void)context;
  g_timer_fires++;
  my_pal_main_loop_destroy(g_loop);
  g_loop = NULL;
  return MY_RET_FAIL;
}

static my_ret_t screen_command_execute(void* context) {
  (void)context;
  g_command_executes++;
  (void)my_pal_main_loop_quit(g_loop);
  return MY_RET_OK;
}

static void cleanup_window(void) {
  if (g_window != NULL) {
    my_pal_window_destroy(g_window);
    g_window = NULL;
  }
}

static void cleanup_loop(void) {
  if (g_loop != NULL) {
    my_pal_main_loop_destroy(g_loop);
    g_loop = NULL;
  }
}

static screen_window_t native_window(void) {
  return (screen_window_t)my_pal_screen_native_window(g_window);
}

static void expect_native_size(int width, int height) {
  int size[2] = {0, 0};
  int result;
  errno = 0;
  result = screen_get_window_property_iv(native_window(),
                                         SCREEN_PROPERTY_SIZE, size);
  if (result != 0) {
    printf("\n  Screen SIZE error: %d (%s); local size: ", errno,
           strerror(errno));
    ASSERT_EQ(my_pal_window_get_size(g_window, &size[0], &size[1]), MY_RET_OK);
    printf("%d x %d\n", size[0], size[1]);
  }
  ASSERT_EQ(result, 0);
  ASSERT_EQ(size[0], width);
  ASSERT_EQ(size[1], height);
  size[0] = 0;
  size[1] = 0;
  ASSERT_EQ(screen_get_window_property_iv(
                native_window(), SCREEN_PROPERTY_BUFFER_SIZE, size), 0);
  ASSERT_EQ(size[0], width);
  ASSERT_EQ(size[1], height);
}

static void expect_native_buffer_count(int expected) {
  int count = 0;
  ASSERT_EQ(screen_get_window_property_iv(
                native_window(), SCREEN_PROPERTY_RENDER_BUFFER_COUNT, &count), 0);
  ASSERT_EQ(count, expected);
}

static const uint8_t* g_frame_pixels;
static uint8_t g_frame_pixel_value;
static const uint8_t* g_first_pixels;
static uint8_t g_first_pixel_value;

static void fill_frame(my_lcd_t* lcd, uint8_t value) {
  uint32_t y;
  uint32_t width = my_lcd_get_width(lcd);
  uint32_t height = my_lcd_get_height(lcd);
  uint32_t stride = my_lcd_get_stride(lcd);
  uint8_t* pixels = my_lcd_get_buffer(lcd);
  ASSERT_NOT_NULL(pixels);
  ASSERT_TRUE(stride >= width * 4u);
  for (y = 0; y < height; ++y) memset(pixels + y * stride, value, width * 4u);
  g_frame_pixels = pixels;
  g_frame_pixel_value = pixels[0];
}

static void expect_last_frame(uint32_t count, uint8_t expected) {
  ASSERT_EQ(my_pal_screen_test_post_count(g_window), count);
  ASSERT_NOT_NULL(g_frame_pixels);
  if (count == 1u) {
    g_first_pixels = g_frame_pixels;
    g_first_pixel_value = g_frame_pixel_value;
  } else if (count == 2u) {
    ASSERT_TRUE(g_frame_pixels != g_first_pixels);
    ASSERT_EQ(g_first_pixel_value, 0x40u);
  }
  ASSERT_EQ(g_frame_pixel_value, expected);
}

static my_ret_t native_event_begin(int type, screen_event_t* event) {
  screen_window_t window = native_window();
  *event = NULL;
  if (screen_create_event(event) != 0 ||
      screen_set_event_property_iv(*event, SCREEN_PROPERTY_TYPE, &type) != 0 ||
      screen_set_event_property_pv(*event, SCREEN_PROPERTY_WINDOW,
                                   (void**)&window) != 0) {
    if (*event != NULL) (void)screen_destroy_event(*event);
    *event = NULL;
    return MY_RET_FAIL;
  }
  return MY_RET_OK;
}

static my_ret_t native_event_send(screen_event_t event) {
  screen_context_t context =
      (screen_context_t)my_pal_screen_native_context(g_pal);
  int result = screen_send_event(context, event, getpid());
  int error = errno;
  (void)screen_destroy_event(event);
  errno = error;
  return result == 0 ? MY_RET_OK : MY_RET_FAIL;
}

static my_ret_t native_send_pointer(int x, int y, int buttons, int wheel,
                                    int modifiers) {
  screen_event_t event;
  int position[2] = {x, y};
  int flags = SCREEN_FLAG_POSITION_VALID;
  if (native_event_begin(SCREEN_EVENT_POINTER, &event) != MY_RET_OK) {
    return MY_RET_FAIL;
  }
  if (screen_set_event_property_iv(event, SCREEN_PROPERTY_POSITION, position) !=
          0 ||
      screen_set_event_property_iv(event, SCREEN_PROPERTY_BUTTONS, &buttons) !=
          0 ||
      screen_set_event_property_iv(event, SCREEN_PROPERTY_MOUSE_WHEEL, &wheel) !=
          0 ||
      screen_set_event_property_iv(event, SCREEN_PROPERTY_MODIFIERS,
                                   &modifiers) != 0 ||
      screen_set_event_property_iv(event, SCREEN_PROPERTY_FLAGS, &flags) != 0) {
    (void)screen_destroy_event(event);
    return MY_RET_FAIL;
  }
  return native_event_send(event);
}

static my_ret_t native_send_displacement(int dx, int dy, int buttons,
                                         int wheel) {
  screen_event_t event;
  int displacement[2] = {dx, dy};
  int flags = SCREEN_FLAG_DISPLACEMENT_VALID;
  int modifiers = 0;
  if (native_event_begin(SCREEN_EVENT_POINTER, &event) != MY_RET_OK) {
    return MY_RET_FAIL;
  }
  if (screen_set_event_property_iv(event, SCREEN_PROPERTY_DISPLACEMENT,
                                   displacement) != 0 ||
      screen_set_event_property_iv(event, SCREEN_PROPERTY_BUTTONS, &buttons) !=
          0 ||
      screen_set_event_property_iv(event, SCREEN_PROPERTY_MOUSE_WHEEL, &wheel) !=
          0 ||
      screen_set_event_property_iv(event, SCREEN_PROPERTY_MODIFIERS,
                                   &modifiers) != 0 ||
      screen_set_event_property_iv(event, SCREEN_PROPERTY_FLAGS, &flags) != 0) {
    (void)screen_destroy_event(event);
    return MY_RET_FAIL;
  }
  return native_event_send(event);
}

static my_ret_t native_send_key_cap(int symbol, int cap, int flags,
                                    int modifiers) {
  screen_event_t event;
  if (native_event_begin(SCREEN_EVENT_KEYBOARD, &event) != MY_RET_OK) {
    return MY_RET_FAIL;
  }
  if (screen_set_event_property_iv(event, SCREEN_PROPERTY_SYM, &symbol) != 0 ||
      screen_set_event_property_iv(event, SCREEN_PROPERTY_KEY_CAP, &cap) != 0 ||
      screen_set_event_property_iv(event, SCREEN_PROPERTY_FLAGS, &flags) != 0 ||
      screen_set_event_property_iv(event, SCREEN_PROPERTY_MODIFIERS,
                                   &modifiers) != 0) {
    (void)screen_destroy_event(event);
    return MY_RET_FAIL;
  }
  return native_event_send(event);
}

static my_ret_t native_send_key(int symbol, int flags, int modifiers) {
  return native_send_key_cap(symbol, 0, flags, modifiers);
}

static my_ret_t native_resize(int width, int height) {
  int size[2] = {width, height};
  screen_context_t context =
      (screen_context_t)my_pal_screen_native_context(g_pal);
  if (screen_set_window_property_iv(native_window(), SCREEN_PROPERTY_SIZE,
                                    size) != 0 ||
      screen_flush_context(context, 0) != 0) {
    return MY_RET_FAIL;
  }
  return MY_RET_OK;
}

static my_ret_t native_send_property(int property) {
  screen_event_t event;
  if (native_event_begin(SCREEN_EVENT_PROPERTY, &event) != MY_RET_OK) {
    return MY_RET_FAIL;
  }
  if (screen_set_event_property_iv(event, SCREEN_PROPERTY_NAME, &property) != 0) {
    (void)screen_destroy_event(event);
    return MY_RET_FAIL;
  }
  return native_event_send(event);
}

static my_ret_t native_send_close(void) {
  screen_context_t context = NULL;
  screen_event_t event;
  int subtype = MY_PAL_SCREEN_MANAGER_CLOSE;
  int result;
  int error;
  if (screen_create_context(&context, SCREEN_WINDOW_MANAGER_CONTEXT) != 0 ||
      native_event_begin(SCREEN_EVENT_MANAGER, &event) != MY_RET_OK) {
    printf("\n  Screen manager context error: %d (%s)\n", errno,
           strerror(errno));
    if (context != NULL) (void)screen_destroy_context(context);
    return MY_RET_FAIL;
  }
  if (screen_set_event_property_iv(event, SCREEN_PROPERTY_SUBTYPE, &subtype) !=
      0) {
    (void)screen_destroy_event(event);
    (void)screen_destroy_context(context);
    return MY_RET_FAIL;
  }
  result = screen_send_event(context, event, getpid());
  error = errno;
  if (result != 0) {
    printf("\n  Screen close injection error: %d (%s)\n", error,
           strerror(error));
  }
  (void)screen_destroy_event(event);
  (void)screen_destroy_context(context);
  errno = error;
  return result == 0 ? MY_RET_OK : MY_RET_FAIL;
}

static void reset_native_events(void) {
  g_native_count = 0;
  g_native_overflow = 0;
  g_bad_window = 0;
  g_timer_fires = 0;
}

TEST(screen_window_lifecycle_and_double_buffer)
{
  my_lcd_t* lcd;
  int32_t width = 0;
  int32_t height = 0;
  int format = 0;
  int usage = 0;

  g_window = my_pal_window_create(g_pal, 320, 180, "myui Screen TDD");
  ASSERT_NOT_NULL(g_window);
  ASSERT_NOT_NULL(native_window());
  expect_native_size(320, 180);
  expect_native_buffer_count(2);
  ASSERT_EQ(screen_get_window_property_iv(native_window(),
                                          SCREEN_PROPERTY_FORMAT, &format), 0);
  ASSERT_EQ(format, SCREEN_FORMAT_RGBA8888);
  ASSERT_EQ(screen_get_window_property_iv(native_window(),
                                          SCREEN_PROPERTY_USAGE, &usage), 0);
  ASSERT_EQ(usage & (SCREEN_USAGE_READ | SCREEN_USAGE_WRITE),
            SCREEN_USAGE_READ | SCREEN_USAGE_WRITE);

  errno = 0;
  {
    my_ret_t title_result = my_pal_window_set_title(g_window, "renamed");
    if (title_result != MY_RET_OK) {
      printf("\n  Screen title error: %d (%s), result=%d\n", errno,
             strerror(errno), title_result);
    }
    ASSERT_EQ(title_result, MY_RET_OK);
  }
  ASSERT_EQ(my_pal_window_show(g_window), MY_RET_OK);
  ASSERT_EQ(my_pal_window_get_size(g_window, &width, &height), MY_RET_OK);
  ASSERT_EQ(width, 320);
  ASSERT_EQ(height, 180);
  lcd = my_pal_window_get_lcd(g_window);
  ASSERT_NOT_NULL(lcd);
  ASSERT_EQ(my_lcd_get_width(lcd), 320u);
  ASSERT_EQ(my_lcd_get_height(lcd), 180u);
  ASSERT_EQ(my_lcd_get_format(lcd), MY_PIXEL_FORMAT_RGBA8888);

  ASSERT_EQ(my_lcd_begin_frame(lcd, NULL), MY_RET_OK);
  fill_frame(lcd, 0x40u);
  ASSERT_EQ(my_lcd_end_frame(lcd), MY_RET_OK);
  expect_last_frame(1u, 0x40u);

  ASSERT_EQ(my_lcd_begin_frame(lcd, NULL), MY_RET_OK);
  fill_frame(lcd, 0x80u);
  ASSERT_EQ(my_lcd_end_frame(lcd), MY_RET_OK);
  expect_last_frame(2u, 0x80u);

  ASSERT_EQ(my_pal_window_resize(g_window, 160, 120), MY_RET_OK);
  expect_native_size(160, 120);
  expect_native_buffer_count(2);
  ASSERT_EQ(my_pal_window_get_size(g_window, &width, &height), MY_RET_OK);
  ASSERT_EQ(width, 160);
  ASSERT_EQ(height, 120);
  lcd = my_pal_window_get_lcd(g_window);
  ASSERT_NOT_NULL(lcd);
  ASSERT_EQ(my_lcd_get_width(lcd), 160u);
  ASSERT_EQ(my_lcd_get_height(lcd), 120u);
  ASSERT_EQ(my_lcd_begin_frame(lcd, NULL), MY_RET_OK);
  fill_frame(lcd, 0x20u);
  ASSERT_EQ(my_lcd_end_frame(lcd), MY_RET_OK);
  expect_last_frame(3u, 0x20u);
  ASSERT_TRUE(my_pal_time_now_ms(g_pal) > 0u);
}

TEST(screen_external_size_rebuilds_lcd)
{
  my_lcd_t* lcd;
  int32_t width = 0;
  int32_t height = 0;
  g_window = my_pal_window_create(g_pal, 320, 180, "myui external resize");
  ASSERT_NOT_NULL(g_window);
  ASSERT_EQ(native_resize(160, 120), MY_RET_OK);
  ASSERT_EQ(my_pal_window_get_size(g_window, &width, &height), MY_RET_OK);
  ASSERT_EQ(width, 160);
  ASSERT_EQ(height, 120);
  lcd = my_pal_window_get_lcd(g_window);
  ASSERT_NOT_NULL(lcd);
  ASSERT_EQ(my_lcd_get_width(lcd), 160u);
  ASSERT_EQ(my_lcd_get_height(lcd), 120u);
  expect_native_buffer_count(2);
  ASSERT_EQ(my_lcd_begin_frame(lcd, NULL), MY_RET_OK);
  fill_frame(lcd, 0x30u);
  ASSERT_EQ(my_lcd_end_frame(lcd), MY_RET_OK);
  expect_last_frame(1u, 0x30u);
}

TEST(screen_native_property_resize_event)
{
  my_lcd_t* lcd;
  g_window = my_pal_window_create(g_pal, 320, 180, "myui resize event");
  ASSERT_NOT_NULL(g_window);
  ASSERT_EQ(my_pal_window_show(g_window), MY_RET_OK);
  g_loop = my_pal_main_loop_create(g_pal);
  ASSERT_NOT_NULL(g_loop);
  reset_native_events();
  ASSERT_EQ(native_resize(200, 150), MY_RET_OK);
  ASSERT_EQ(native_send_property(SCREEN_PROPERTY_SIZE), MY_RET_OK);
  ASSERT_NEQ(my_pal_main_loop_add_timer(g_loop, screen_timer_callback, NULL,
                                        1000u), 0u);
  ASSERT_EQ(my_pal_main_loop_run(g_loop), MY_RET_OK);
  ASSERT_EQ(g_native_count, 1);
  ASSERT_EQ(g_bad_window, 0);
  ASSERT_EQ(g_timer_fires, 1);
  ASSERT_EQ(g_native_events[0].type, MY_EVENT_RESIZE);
  ASSERT_EQ(g_native_events[0].u.resize.w, 200);
  ASSERT_EQ(g_native_events[0].u.resize.h, 150);
  lcd = my_pal_window_get_lcd(g_window);
  ASSERT_NOT_NULL(lcd);
  ASSERT_EQ(my_lcd_get_width(lcd), 200u);
  ASSERT_EQ(my_lcd_get_height(lcd), 150u);
  expect_native_buffer_count(2);
  ASSERT_EQ(my_lcd_begin_frame(lcd, NULL), MY_RET_OK);
  fill_frame(lcd, 0x50u);
  ASSERT_EQ(my_lcd_end_frame(lcd), MY_RET_OK);
  expect_last_frame(1u, 0x50u);
}

TEST(screen_user_event_and_quit)
{
  my_event_t user = my_event_init(MY_EVENT_USER);
  g_loop = my_pal_main_loop_create(g_pal);
  ASSERT_NOT_NULL(g_loop);
  g_user_events = 0;
  ASSERT_EQ(my_pal_main_loop_post_event(g_loop, &user), MY_RET_OK);
  ASSERT_EQ(my_pal_main_loop_quit(g_loop), MY_RET_OK);
  ASSERT_EQ(my_pal_main_loop_run(g_loop), MY_RET_OK);
  ASSERT_EQ(g_user_events, 1);
}

TEST(screen_one_shot_timer_wakes_loop)
{
  g_loop = my_pal_main_loop_create(g_pal);
  ASSERT_NOT_NULL(g_loop);
  g_timer_fires = 0;
  ASSERT_NEQ(my_pal_main_loop_add_timer(g_loop, screen_timer_callback,
                                        g_loop, 1u), 0u);
  ASSERT_EQ(my_pal_main_loop_run(g_loop), MY_RET_OK);
  ASSERT_EQ(g_timer_fires, 1);
}

TEST(screen_timer_callback_destroys_loop)
{
  my_pal_main_loop_t* loop;
  g_loop = my_pal_main_loop_create(g_pal);
  ASSERT_NOT_NULL(g_loop);
  loop = g_loop;
  g_timer_fires = 0;
  ASSERT_NEQ(my_pal_main_loop_add_timer(g_loop, screen_destroy_timer_callback,
                                        NULL, 1u), 0u);
  ASSERT_EQ(my_pal_main_loop_run(loop), MY_RET_OK);
  ASSERT_EQ(g_timer_fires, 1);
  ASSERT_TRUE(g_loop == NULL);
}

TEST(screen_command_dispatches_in_loop_context)
{
  my_ui_command_t* command;
  g_loop = my_pal_main_loop_create(g_pal);
  ASSERT_NOT_NULL(g_loop);
  g_command_executes = 0;
  command = my_ui_command_create(NULL, screen_command_execute, NULL, NULL);
  ASSERT_NOT_NULL(command);
  ASSERT_EQ(my_ui_command_submit(g_loop, command), MY_RET_OK);
  my_ui_command_unref(command);
  ASSERT_EQ(my_pal_main_loop_quit(g_loop), MY_RET_OK);
  ASSERT_EQ(my_pal_main_loop_run(g_loop), MY_RET_OK);
  ASSERT_EQ(g_command_executes, 1);
}

TEST(screen_process_local_clipboard_full_text)
{
  char buf[32];
  char small[5];
  char source[32] = "process local";
  char* allocated = NULL;
  char* long_text;
  my_pal_t* other;
  const size_t long_length = 16384u;
  size_t i;
  ASSERT_TRUE(my_pal_screen_clipboard_is_process_local());
  ASSERT_EQ(my_pal_clipboard_get_text(g_pal, buf, sizeof(buf)),
            MY_RET_NOT_FOUND);
  ASSERT_EQ(my_pal_clipboard_get_text_alloc(g_pal, NULL, &allocated),
            MY_RET_NOT_FOUND);
  ASSERT_TRUE(allocated == NULL);
  ASSERT_EQ(my_pal_clipboard_get_text(g_pal, NULL, 0u), MY_RET_INVALID_PARAMS);
  other = my_pal_create(NULL);
  ASSERT_NOT_NULL(other);
  ASSERT_EQ(my_pal_clipboard_set_text(g_pal, source), MY_RET_OK);
  source[0] = 'X';
  ASSERT_EQ(my_pal_clipboard_get_text(g_pal, buf, sizeof(buf)), MY_RET_OK);
  ASSERT_STR_EQ(buf, "process local");
  ASSERT_EQ(my_pal_clipboard_get_text(g_pal, small, sizeof(small)), MY_RET_OK);
  ASSERT_STR_EQ(small, "proc");
  ASSERT_EQ(my_pal_clipboard_get_text(other, buf, sizeof(buf)),
            MY_RET_NOT_FOUND);
  my_pal_destroy(other);
  ASSERT_EQ(my_pal_clipboard_set_text(g_pal, "\xe6\xb1\x89\xe5\xad\x97\xf0\x9f\x99\x82"),
            MY_RET_OK);
  ASSERT_EQ(my_pal_clipboard_get_text(g_pal, small, 4u), MY_RET_OK);
  ASSERT_STR_EQ(small, "\xe6\xb1\x89");
  ASSERT_EQ(my_pal_clipboard_get_text(g_pal, small, 2u), MY_RET_OK);
  ASSERT_STR_EQ(small, "");
  ASSERT_EQ(my_pal_clipboard_get_text_alloc(g_pal, NULL, &allocated), MY_RET_OK);
  ASSERT_NOT_NULL(allocated);
  ASSERT_STR_EQ(allocated, "\xe6\xb1\x89\xe5\xad\x97\xf0\x9f\x99\x82");
  my_mem_free(NULL, allocated);
  allocated = NULL;
  ASSERT_EQ(my_pal_clipboard_set_text(g_pal, ""), MY_RET_OK);
  buf[0] = 'X';
  ASSERT_EQ(my_pal_clipboard_get_text(g_pal, buf, sizeof(buf)), MY_RET_OK);
  ASSERT_EQ(buf[0], '\0');
  long_text = my_mem_alloc(NULL, long_length + 1u);
  ASSERT_NOT_NULL(long_text);
  for (i = 0u; i < long_length; ++i) long_text[i] = (char)('a' + i % 26u);
  long_text[long_length] = '\0';
  ASSERT_EQ(my_pal_clipboard_set_text(g_pal, long_text), MY_RET_OK);
  long_text[0] = 'X';
  ASSERT_EQ(my_pal_clipboard_get_text_alloc(g_pal, NULL, &allocated), MY_RET_OK);
  ASSERT_NOT_NULL(allocated);
  ASSERT_EQ(strlen(allocated), long_length);
  ASSERT_EQ(allocated[0], 'a');
  ASSERT_EQ(allocated[long_length - 1u], long_text[long_length - 1u]);
  my_mem_free(NULL, allocated);
  my_mem_free(NULL, long_text);
  ASSERT_EQ(my_pal_clipboard_set_text(g_pal, NULL), MY_RET_OK);
  ASSERT_EQ(my_pal_clipboard_get_text(g_pal, buf, sizeof(buf)),
            MY_RET_NOT_FOUND);
}

TEST(screen_ime_state_is_explicitly_non_native)
{
  my_pal_screen_ime_state_t state;
  char surrounding[16] = "before";
  ASSERT_FALSE(my_pal_screen_has_native_ime());
  g_window = my_pal_window_create(g_pal, 160, 120, "myui IME state");
  ASSERT_NOT_NULL(g_window);
  memset(&state, 0, sizeof(state));
  ASSERT_EQ(my_pal_screen_test_ime_state(g_window, &state), MY_RET_OK);
  ASSERT_FALSE(state.enabled);
  ASSERT_TRUE(state.surrounding == NULL);
  my_pal_window_ime_set_enabled(g_window, true);
  my_pal_window_ime_set_surrounding(g_window, surrounding, 3, 1);
  my_pal_window_ime_set_spot(g_window, 17, 29);
  surrounding[0] = 'X';
  ASSERT_EQ(my_pal_screen_test_ime_state(g_window, &state), MY_RET_OK);
  ASSERT_TRUE(state.enabled);
  ASSERT_STR_EQ(state.surrounding, "before");
  ASSERT_EQ(state.cursor, 3);
  ASSERT_EQ(state.anchor, 1);
  ASSERT_EQ(state.spot_x, 17);
  ASSERT_EQ(state.spot_y, 29);
  my_pal_window_ime_set_enabled(g_window, false);
  my_pal_window_ime_set_surrounding(g_window, NULL, 0, 0);
  ASSERT_EQ(my_pal_screen_test_ime_state(g_window, &state), MY_RET_OK);
  ASSERT_FALSE(state.enabled);
  ASSERT_STR_EQ(state.surrounding, "");
}

TEST(screen_native_cursor_shapes_use_pointer_session)
{
  screen_context_t context =
      (screen_context_t)my_pal_screen_native_context(g_pal);
  screen_session_t session;
  my_ret_t result;
  int baseline = -1;
  int count = -1;
  int shape = -1;
  int size[2] = {0, 0};
  g_window = my_pal_window_create(g_pal, 160, 120, "myui native cursor");
  ASSERT_NOT_NULL(g_window);
  ASSERT_EQ(screen_get_context_property_iv(context, SCREEN_PROPERTY_SESSION_COUNT,
                                           &baseline), 0);
  result = my_pal_window_set_cursor(g_window, MY_CURSOR_ARROW);
  if (result == MY_RET_NOT_SUPPORTED) {
    ASSERT_TRUE(my_pal_screen_test_native_pointer_session(g_window) == NULL);
    ASSERT_EQ(my_pal_window_set_cursor(g_window, (my_cursor_t)99),
              MY_RET_INVALID_PARAMS);
    cleanup_window();
    ASSERT_EQ(screen_flush_context(context, 0), 0);
    ASSERT_EQ(screen_get_context_property_iv(
                  context, SCREEN_PROPERTY_SESSION_COUNT, &count), 0);
    ASSERT_EQ(count, baseline);
    return;
  }
  ASSERT_EQ(result, MY_RET_OK);
  session = (screen_session_t)my_pal_screen_test_native_pointer_session(g_window);
  ASSERT_NOT_NULL(session);
  ASSERT_EQ(screen_get_session_property_iv(session, SCREEN_PROPERTY_CURSOR,
                                           &shape), 0);
  ASSERT_EQ(shape, SCREEN_CURSOR_SHAPE_ARROW);
  ASSERT_EQ(my_pal_window_set_cursor(g_window, MY_CURSOR_TEXT), MY_RET_OK);
  ASSERT_EQ(screen_get_session_property_iv(session, SCREEN_PROPERTY_CURSOR,
                                           &shape), 0);
  ASSERT_EQ(shape, SCREEN_CURSOR_SHAPE_IBEAM);
  ASSERT_EQ(my_pal_window_set_cursor(g_window, MY_CURSOR_HAND), MY_RET_OK);
  ASSERT_EQ(screen_get_session_property_iv(session, SCREEN_PROPERTY_CURSOR,
                                           &shape), 0);
  ASSERT_EQ(shape, SCREEN_CURSOR_SHAPE_HAND);
  ASSERT_EQ(my_pal_window_set_cursor(g_window, (my_cursor_t)99),
            MY_RET_INVALID_PARAMS);
  ASSERT_EQ(screen_get_session_property_iv(session, SCREEN_PROPERTY_CURSOR,
                                           &shape), 0);
  ASSERT_EQ(shape, SCREEN_CURSOR_SHAPE_HAND);
  ASSERT_EQ(native_resize(200, 100), MY_RET_OK);
  ASSERT_EQ(my_pal_window_get_size(g_window, &size[0], &size[1]), MY_RET_OK);
  ASSERT_EQ(screen_get_session_property_iv(session, SCREEN_PROPERTY_SIZE,
                                           size), 0);
  ASSERT_EQ(size[0], 200);
  ASSERT_EQ(size[1], 100);
  cleanup_window();
  ASSERT_EQ(screen_flush_context(context, 0), 0);
  ASSERT_EQ(screen_get_context_property_iv(context, SCREEN_PROPERTY_SESSION_COUNT,
                                           &count), 0);
  ASSERT_EQ(count, baseline);
}

TEST(screen_native_pointer_and_keyboard_events)
{
  g_window = my_pal_window_create(g_pal, 320, 180, "myui native input");
  ASSERT_NOT_NULL(g_window);
  ASSERT_EQ(my_pal_window_show(g_window), MY_RET_OK);
  g_loop = my_pal_main_loop_create(g_pal);
  ASSERT_NOT_NULL(g_loop);
  reset_native_events();
  ASSERT_EQ(native_send_pointer(11, 12, SCREEN_LEFT_MOUSE_BUTTON, 0,
                                KEYMOD_SHIFT | KEYMOD_CTRL), MY_RET_OK);
  ASSERT_EQ(native_send_pointer(30, 40, SCREEN_LEFT_MOUSE_BUTTON, 0,
                                KEYMOD_SHIFT | KEYMOD_CTRL), MY_RET_OK);
  ASSERT_EQ(native_send_pointer(30, 40, SCREEN_LEFT_MOUSE_BUTTON, 3,
                                KEYMOD_SHIFT | KEYMOD_CTRL), MY_RET_OK);
  ASSERT_EQ(native_send_pointer(30, 40, 0, 0,
                                KEYMOD_SHIFT | KEYMOD_CTRL), MY_RET_OK);
  ASSERT_EQ(native_send_key('a', KEY_DOWN | KEY_SYM_VALID, KEYMOD_ALT),
            MY_RET_OK);
  ASSERT_EQ(native_send_key('a', KEY_SYM_VALID, KEYMOD_ALT), MY_RET_OK);
  ASSERT_EQ(native_send_key(KEYCODE_RETURN, KEY_DOWN | KEY_SYM_VALID, 0),
            MY_RET_OK);
  ASSERT_EQ(native_send_key(KEYCODE_RETURN, KEY_SYM_VALID, 0), MY_RET_OK);
  ASSERT_NEQ(my_pal_main_loop_add_timer(g_loop, screen_timer_callback, NULL,
                                        1000u), 0u);
  ASSERT_EQ(my_pal_main_loop_run(g_loop), MY_RET_OK);
  if (g_native_count != 8) printf("\n  native events received=%d\n", g_native_count);
  ASSERT_EQ(g_native_count, 8);
  ASSERT_EQ(g_native_overflow, 0);
  ASSERT_EQ(g_bad_window, 0);
  ASSERT_EQ(g_timer_fires, 1);
  ASSERT_EQ(g_native_events[0].type, MY_EVENT_POINTER_DOWN);
  ASSERT_EQ(g_native_events[0].u.pointer.x, 11);
  ASSERT_EQ(g_native_events[0].u.pointer.y, 12);
  ASSERT_EQ(g_native_events[0].u.pointer.button, 1u);
  ASSERT_EQ(g_native_events[0].u.pointer.modifiers, MY_KEYMOD_SHIFT | MY_KEYMOD_CTRL);
  ASSERT_EQ(g_native_events[1].type, MY_EVENT_POINTER_MOVE);
  ASSERT_EQ(g_native_events[1].u.pointer.x, 30);
  ASSERT_EQ(g_native_events[1].u.pointer.y, 40);
  ASSERT_EQ(g_native_events[2].type, MY_EVENT_POINTER_WHEEL);
  ASSERT_EQ(g_native_events[2].u.pointer.delta, 3);
  ASSERT_EQ(g_native_events[3].type, MY_EVENT_POINTER_UP);
  ASSERT_EQ(g_native_events[3].u.pointer.button, 1u);
  ASSERT_EQ(g_native_events[4].type, MY_EVENT_KEY_DOWN);
  ASSERT_EQ(g_native_events[4].u.key.key, (uint32_t)'a');
  ASSERT_EQ(g_native_events[4].u.key.modifiers, MY_KEYMOD_ALT);
  ASSERT_EQ(g_native_events[5].type, MY_EVENT_KEY_UP);
  ASSERT_EQ(g_native_events[5].u.key.key, (uint32_t)'a');
  ASSERT_EQ(g_native_events[6].type, MY_EVENT_KEY_DOWN);
  ASSERT_EQ(g_native_events[6].u.key.key, MY_KEY_RETURN);
  ASSERT_EQ(g_native_events[7].type, MY_EVENT_KEY_UP);
  ASSERT_EQ(g_native_events[7].u.key.key, MY_KEY_RETURN);
}

TEST(screen_native_keycap_unicode_text_events)
{
  g_window = my_pal_window_create(g_pal, 160, 120, "myui Unicode keycap");
  ASSERT_NOT_NULL(g_window);
  g_loop = my_pal_main_loop_create(g_pal);
  ASSERT_NOT_NULL(g_loop);
  reset_native_events();
  ASSERT_EQ(native_send_key_cap('a', 0xe9,
                                KEY_DOWN | KEY_SYM_VALID | KEY_CAP_VALID, 0),
            MY_RET_OK);
  ASSERT_EQ(native_send_key_cap('a', 0xe9,
                                KEY_SYM_VALID | KEY_CAP_VALID, 0), MY_RET_OK);
  ASSERT_EQ(native_send_key_cap(0x1f642, 0x1f642,
                                KEY_DOWN | KEY_SYM_VALID | KEY_CAP_VALID, 0),
            MY_RET_OK);
  ASSERT_EQ(native_send_key_cap('a', 0xd800,
                                KEY_DOWN | KEY_SYM_VALID | KEY_CAP_VALID, 0),
            MY_RET_OK);
  ASSERT_EQ(native_send_key_cap('a', 0x110000,
                                KEY_DOWN | KEY_SYM_VALID | KEY_CAP_VALID, 0),
            MY_RET_OK);
  ASSERT_EQ(native_send_key_cap(0xe9, 0xe9, KEY_DOWN | KEY_SYM_VALID, 0),
            MY_RET_OK);
  ASSERT_EQ(native_send_key_cap('a', 'a',
                                KEY_DOWN | KEY_SYM_VALID | KEY_CAP_VALID, 0),
            MY_RET_OK);
  ASSERT_NEQ(my_pal_main_loop_add_timer(g_loop, screen_timer_callback, NULL,
                                        1000u), 0u);
  ASSERT_EQ(my_pal_main_loop_run(g_loop), MY_RET_OK);
  ASSERT_EQ(g_native_count, 7);
  ASSERT_EQ(g_native_overflow, 0);
  ASSERT_EQ(g_bad_window, 0);
  ASSERT_EQ(g_native_events[0].type, MY_EVENT_KEY_DOWN);
  ASSERT_EQ(g_native_events[0].u.key.key, (uint32_t)'a');
  ASSERT_EQ(g_native_events[1].type, MY_EVENT_IME_COMMIT);
  ASSERT_STR_EQ(g_native_events[1].u.ime.text, "\xc3\xa9");
  ASSERT_EQ(g_native_events[2].type, MY_EVENT_KEY_UP);
  ASSERT_EQ(g_native_events[2].u.key.key, (uint32_t)'a');
  ASSERT_EQ(g_native_events[3].type, MY_EVENT_IME_COMMIT);
  ASSERT_STR_EQ(g_native_events[3].u.ime.text, "\xf0\x9f\x99\x82");
  ASSERT_EQ(g_native_events[4].type, MY_EVENT_KEY_DOWN);
  ASSERT_EQ(g_native_events[4].u.key.key, (uint32_t)'a');
  ASSERT_EQ(g_native_events[5].type, MY_EVENT_KEY_DOWN);
  ASSERT_EQ(g_native_events[5].u.key.key, (uint32_t)'a');
  ASSERT_EQ(g_native_events[6].type, MY_EVENT_KEY_DOWN);
  ASSERT_EQ(g_native_events[6].u.key.key, (uint32_t)'a');
}

TEST(screen_native_displacement_moves_without_fake_wheel)
{
  g_window = my_pal_window_create(g_pal, 160, 120, "myui relative pointer");
  ASSERT_NOT_NULL(g_window);
  g_loop = my_pal_main_loop_create(g_pal);
  ASSERT_NOT_NULL(g_loop);
  reset_native_events();
  ASSERT_EQ(native_send_pointer(10, 20, 0, 0, 0), MY_RET_OK);
  ASSERT_EQ(native_send_displacement(3, -2, 0, 0), MY_RET_OK);
  ASSERT_EQ(native_send_displacement(-4, 5, SCREEN_LEFT_MOUSE_BUTTON, 2),
            MY_RET_OK);
  ASSERT_EQ(native_send_displacement(1, 1, SCREEN_LEFT_MOUSE_BUTTON, 0),
            MY_RET_OK);
  ASSERT_NEQ(my_pal_main_loop_add_timer(g_loop, screen_timer_callback, NULL,
                                        1000u), 0u);
  ASSERT_EQ(my_pal_main_loop_run(g_loop), MY_RET_OK);
  ASSERT_EQ(g_native_count, 5);
  ASSERT_EQ(g_native_overflow, 0);
  ASSERT_EQ(g_bad_window, 0);
  ASSERT_EQ(g_native_events[0].type, MY_EVENT_POINTER_MOVE);
  ASSERT_EQ(g_native_events[0].u.pointer.x, 13);
  ASSERT_EQ(g_native_events[0].u.pointer.y, 18);
  ASSERT_EQ(g_native_events[0].u.pointer.delta, 0);
  ASSERT_EQ(g_native_events[1].type, MY_EVENT_POINTER_MOVE);
  ASSERT_EQ(g_native_events[1].u.pointer.x, 9);
  ASSERT_EQ(g_native_events[1].u.pointer.y, 23);
  ASSERT_EQ(g_native_events[1].u.pointer.delta, 0);
  ASSERT_EQ(g_native_events[2].type, MY_EVENT_POINTER_WHEEL);
  ASSERT_EQ(g_native_events[2].u.pointer.x, 9);
  ASSERT_EQ(g_native_events[2].u.pointer.y, 23);
  ASSERT_EQ(g_native_events[2].u.pointer.delta, 2);
  ASSERT_EQ(g_native_events[3].type, MY_EVENT_POINTER_DOWN);
  ASSERT_EQ(g_native_events[3].u.pointer.x, 9);
  ASSERT_EQ(g_native_events[3].u.pointer.y, 23);
  ASSERT_EQ(g_native_events[4].type, MY_EVENT_POINTER_MOVE);
  ASSERT_EQ(g_native_events[4].u.pointer.x, 10);
  ASSERT_EQ(g_native_events[4].u.pointer.y, 24);
  ASSERT_EQ(g_native_events[4].u.pointer.delta, 0);
}

TEST(screen_native_close_has_source_window)
{
  g_window = my_pal_window_create(g_pal, 160, 120, "myui native close");
  ASSERT_NOT_NULL(g_window);
  ASSERT_EQ(my_pal_window_show(g_window), MY_RET_OK);
  g_loop = my_pal_main_loop_create(g_pal);
  ASSERT_NOT_NULL(g_loop);
  reset_native_events();
  ASSERT_EQ(native_send_close(), MY_RET_OK);
  ASSERT_NEQ(my_pal_main_loop_add_timer(g_loop, screen_timer_callback, NULL,
                                        1000u), 0u);
  ASSERT_EQ(my_pal_main_loop_run(g_loop), MY_RET_OK);
  ASSERT_EQ(g_native_count, 1);
  ASSERT_EQ(g_native_overflow, 0);
  ASSERT_EQ(g_bad_window, 0);
  ASSERT_EQ(g_native_events[0].type, MY_EVENT_QUIT);
  ASSERT_EQ(g_timer_fires, 0);
}

int main(void) {
  setvbuf(stdout, NULL, _IONBF, 0);
  g_pal = my_pal_create(NULL);
  if (g_pal == NULL) {
    printf("SKIP: no usable QNX Screen service\n");
    return getenv("BREAK_QNX_SCREEN_REQUIRED") != NULL ? 1 : 77;
  }
  (void)my_pal_set_event_handler(g_pal, screen_event_handler, NULL);
  printf("=== Running Tests ===\n");
  RUN_TEST(screen_window_lifecycle_and_double_buffer);
  cleanup_window();
  RUN_TEST(screen_external_size_rebuilds_lcd);
  cleanup_window();
  RUN_TEST(screen_native_property_resize_event);
  cleanup_loop();
  cleanup_window();
  RUN_TEST(screen_user_event_and_quit);
  cleanup_loop();
  RUN_TEST(screen_one_shot_timer_wakes_loop);
  cleanup_loop();
  RUN_TEST(screen_timer_callback_destroys_loop);
  cleanup_loop();
  RUN_TEST(screen_command_dispatches_in_loop_context);
  cleanup_loop();
  RUN_TEST(screen_process_local_clipboard_full_text);
  RUN_TEST(screen_ime_state_is_explicitly_non_native);
  cleanup_window();
  RUN_TEST(screen_native_cursor_shapes_use_pointer_session);
  cleanup_window();
  RUN_TEST(screen_native_pointer_and_keyboard_events);
  cleanup_loop();
  cleanup_window();
  RUN_TEST(screen_native_keycap_unicode_text_events);
  cleanup_loop();
  cleanup_window();
  RUN_TEST(screen_native_displacement_moves_without_fake_wheel);
  cleanup_loop();
  cleanup_window();
  RUN_TEST(screen_native_close_has_source_window);
  cleanup_loop();
  cleanup_window();
  my_pal_destroy(g_pal);
  printf("\n=== Results: %d passed, %d failed, %d total ===\n",
         g_test_pass, g_test_fail, g_test_count);
  return g_test_fail > 0 ? 1 : 0;
}
