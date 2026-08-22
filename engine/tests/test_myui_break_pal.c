#include "test_framework.h"

#include "mypal/break/my_pal_break.h"

#include <stdint.h>

static int g_events;
static int g_first_marker;
static int g_second_marker;
static my_pal_window_t *g_windows[2];
static my_event_type_t g_types[2];
static void *g_data[2];
static void *g_expected_data[256];
static int g_expected_count;
static bool g_fifo_ok;

static my_ret_t on_event(void *ctx, my_pal_window_t *window,
                         const my_event_t *event) {
  (void)ctx;
  if (g_events < 2) {
    g_windows[g_events] = window;
    g_types[g_events] = event->type;
    g_data[g_events] = event->u.user.data;
  }
  if (g_events >= g_expected_count ||
      event->u.user.data != g_expected_data[g_events]) {
    g_fifo_ok = false;
  }
  g_events += 1;
  return MY_RET_OK;
}

TEST(posted_events_are_fifo_and_dispatched)
{
  my_pal_t *pal = my_pal_break_create(NULL, (Platform *)(uintptr_t)1, NULL);
  my_pal_main_loop_t *loop = my_pal_main_loop_create(pal);
  my_event_t first = my_event_init(MY_EVENT_USER);
  my_event_t second = my_event_init(MY_EVENT_USER);

  g_events = 0;
  g_expected_count = 2;
  g_fifo_ok = true;
  first.u.user.data = &g_first_marker;
  second.u.user.data = &g_second_marker;
  g_expected_data[0] = first.u.user.data;
  g_expected_data[1] = second.u.user.data;
  ASSERT_EQ(my_pal_set_event_handler(pal, on_event, NULL), MY_RET_OK);
  ASSERT_EQ(my_pal_main_loop_post_event(loop, &first), MY_RET_OK);
  ASSERT_EQ(my_pal_main_loop_post_event(loop, &second), MY_RET_OK);
  ASSERT_EQ(my_pal_break_pump(loop), 2u);
  ASSERT_EQ(g_events, 2);
  ASSERT_TRUE(g_fifo_ok);
  ASSERT_TRUE(g_windows[0] == NULL);
  ASSERT_TRUE(g_windows[1] == NULL);
  ASSERT_EQ(g_types[0], MY_EVENT_USER);
  ASSERT_EQ(g_types[1], MY_EVENT_USER);
  ASSERT_TRUE(g_data[0] == &g_first_marker);
  ASSERT_TRUE(g_data[1] == &g_second_marker);

  my_pal_main_loop_destroy(loop);
  my_pal_destroy(pal);
}

TEST(posted_event_burst_preserves_fifo)
{
  enum { event_count = 256 };
  my_pal_t *pal = my_pal_break_create(NULL, (Platform *)(uintptr_t)1, NULL);
  my_pal_main_loop_t *loop = my_pal_main_loop_create(pal);
  my_event_t event = my_event_init(MY_EVENT_USER);
  int markers[event_count];
  int index;

  g_events = 0;
  g_expected_count = event_count;
  g_fifo_ok = true;
  ASSERT_EQ(my_pal_set_event_handler(pal, on_event, NULL), MY_RET_OK);
  for (index = 0; index < event_count; index++) {
    event.u.user.data = &markers[index];
    g_expected_data[index] = event.u.user.data;
    ASSERT_EQ(my_pal_main_loop_post_event(loop, &event), MY_RET_OK);
  }
  ASSERT_EQ(my_pal_break_pump(loop), (uint32_t)event_count);
  ASSERT_EQ(g_events, event_count);
  ASSERT_TRUE(g_fifo_ok);

  my_pal_main_loop_destroy(loop);
  my_pal_destroy(pal);
}

TEST(idle_run_returns_without_blocking)
{
  my_pal_t *pal = my_pal_break_create(NULL, (Platform *)(uintptr_t)1, NULL);
  my_pal_main_loop_t *loop = my_pal_main_loop_create(pal);

  ASSERT_EQ(my_pal_main_loop_run(loop), MY_RET_OK);
  my_pal_main_loop_destroy(loop);
  my_pal_destroy(pal);
}

TEST(embedded_pal_does_not_expose_a_private_vulkan_surface)
{
  my_pal_t *pal = my_pal_break_create(NULL, (Platform *)(uintptr_t)1, NULL);
  my_pal_window_t *window = my_pal_window_create(pal, 100, 100, "test");

  ASSERT_NOT_NULL(window);
  ASSERT_TRUE(my_pal_window_vk_create_surface(window, (void *)(uintptr_t)1) ==
              NULL);
  my_pal_window_destroy(window);
  my_pal_destroy(pal);
}

TEST_MAIN_BEGIN()
    RUN_TEST(posted_events_are_fifo_and_dispatched);
    RUN_TEST(posted_event_burst_preserves_fifo);
    RUN_TEST(idle_run_returns_without_blocking);
    RUN_TEST(embedded_pal_does_not_expose_a_private_vulkan_surface);
TEST_MAIN_END()
