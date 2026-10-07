#include "test_framework.h"

#include "mypal/my_pal.h"
#include "myr/my_lcd_mem.h"

#include <string.h>

static int g_close_events;
static int g_user_events;

static my_ret_t handler(void* ctx, my_pal_window_t* window,
                        const my_event_t* event) {
  (void)ctx;
  (void)window;
  if (event->type == MY_EVENT_QUIT) g_close_events++;
  if (event->type == MY_EVENT_USER) g_user_events++;
  return MY_RET_OK;
}

TEST(mypal_wayland_window_lifecycle) {
  my_pal_t* pal = my_pal_create(NULL);
  my_pal_window_t* win;
  my_lcd_t* lcd;
  int32_t w = 0;
  int32_t h = 0;
  if (pal == NULL) {
    printf("SKIP (no wayland compositor)\n");
    return;
  }
  ASSERT_TRUE(my_pal_set_event_handler(pal, handler, NULL) == MY_RET_OK);
  win = my_pal_window_create(pal, 320, 180, "pal test");
  ASSERT_NOT_NULL(win);
  ASSERT_EQ(my_pal_window_set_title(win, "renamed"), MY_RET_OK);
  ASSERT_EQ(my_pal_window_show(win), MY_RET_OK);
  ASSERT_EQ(my_pal_window_get_size(win, &w, &h), MY_RET_OK);
  ASSERT_EQ(w, 320);
  ASSERT_EQ(h, 180);
  lcd = my_pal_window_get_lcd(win);
  ASSERT_NOT_NULL(lcd);
  ASSERT_EQ(my_lcd_get_width(lcd), 320u);
  ASSERT_EQ(my_lcd_begin_frame(lcd, NULL), MY_RET_OK);
  memset(my_lcd_get_buffer(lcd), 0x40, 320u * 180u * 4u);
  ASSERT_EQ(my_lcd_end_frame(lcd), MY_RET_OK);
  ASSERT_TRUE(my_pal_time_now_ms(pal) > 0u);
  {
    my_pal_main_loop_t* loop = my_pal_main_loop_create(pal);
    my_event_t user = my_event_init(MY_EVENT_USER);
    ASSERT_NOT_NULL(loop);
    ASSERT_EQ(my_pal_main_loop_post_event(loop, &user), MY_RET_OK);
    ASSERT_EQ(my_pal_main_loop_quit(loop), MY_RET_OK);
    ASSERT_EQ(my_pal_main_loop_run(loop), MY_RET_OK);
    ASSERT_EQ(g_user_events, 1);
    my_pal_main_loop_destroy(loop);
  }
  my_pal_window_destroy(win);
  my_pal_destroy(pal);
}

TEST(mypal_wayland_gl_enable) {
  my_pal_t* pal = my_pal_create(NULL);
  my_pal_window_t* win;
  my_pal_gl_t* gl;
  if (pal == NULL) {
    printf("SKIP (no wayland compositor)\n");
    return;
  }
  win = my_pal_window_create(pal, 256, 128, "gl");
  ASSERT_NOT_NULL(win);
  (void)my_pal_window_show(win);
  gl = my_pal_window_gl_enable(win);
  if (gl != NULL) {
    int32_t w = 0;
    int32_t h = 0;
    ASSERT_EQ(my_pal_gl_make_current(gl), MY_RET_OK);
    ASSERT_EQ(my_pal_gl_get_size(gl, &w, &h), MY_RET_OK);
    ASSERT_EQ(w, 256);
    ASSERT_EQ(h, 128);
    ASSERT_EQ(my_pal_gl_swap_buffers(gl), MY_RET_OK);
    ASSERT_TRUE(my_pal_window_gl_enable(win) == gl);
  } else {
    printf("SKIP (EGL unavailable)\n");
  }
  my_pal_window_destroy(win);
  my_pal_destroy(pal);
}

TEST_MAIN_BEGIN()
RUN_TEST(mypal_wayland_window_lifecycle);
RUN_TEST(mypal_wayland_gl_enable);
TEST_MAIN_END()
