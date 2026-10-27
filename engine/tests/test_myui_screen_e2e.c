#include "test_framework.h"

#include "mypal/screen/my_pal_screen.h"
#include "myr/my_font.h"
#include "myui/my_window_manager.h"
#include "myui/widgets/my_button.h"
#include "myui/widgets/my_edit.h"
#include "myui/widgets/my_progress_bar.h"
#include "myui/widgets/my_slider.h"

#include <errno.h>
#include <limits.h>
#include <screen/screen.h>
#include <stdbool.h>
#include <stdint.h>
#include <sys/keycodes.h>
#include <unistd.h>

#define E2E_PHASE_MS 80u
#define E2E_WATCHDOG_MS 5000u

typedef struct screen_e2e_state_t {
  my_pal_t* pal;
  my_pal_main_loop_t* loop;
  my_window_manager_t* wm;
  my_window_t* win;
  my_font_t* font;
  my_widget_t* button;
  my_widget_t* progress;
  my_widget_t* edit;
  my_widget_t* slider;
  uint32_t phase_timer_id;
  uint32_t watchdog_timer_id;
  uint32_t posts_before;
  int phase;
  int failures;
  int button_clicks;
  bool button_click_pointer_up;
  int edit_changes;
  int edit_focuses;
  int edit_blurs;
  int edit_key_ups;
  int slider_changes;
  float slider_values[2];
  int close_count;
  int watchdog_fires;
  bool close_sent;
} screen_e2e_state_t;

static my_pal_t* g_pal;

static bool e2e_check(screen_e2e_state_t* state, bool condition,
                      const char* message) {
  if (!condition) {
    state->failures++;
    printf("  FAIL: Screen E2E: %s\n", message);
  }
  return condition;
}

static my_ret_t native_event_begin(screen_e2e_state_t* state, int type,
                                   screen_event_t* event) {
  screen_window_t window =
      (screen_window_t)my_pal_screen_native_window(state->win->pal_window);
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

static my_ret_t native_event_send(screen_e2e_state_t* state,
                                  screen_event_t event) {
  screen_context_t context =
      (screen_context_t)my_pal_screen_native_context(state->pal);
  int result;
  int error;
  if (context == NULL) {
    (void)screen_destroy_event(event);
    return MY_RET_FAIL;
  }
  result = screen_send_event(context, event, getpid());
  error = errno;
  (void)screen_destroy_event(event);
  errno = error;
  return result == 0 ? MY_RET_OK : MY_RET_FAIL;
}

static my_ret_t native_send_pointer(screen_e2e_state_t* state, int32_t x,
                                    int32_t y, int buttons) {
  screen_event_t event;
  screen_window_t window =
      (screen_window_t)my_pal_screen_native_window(state->win->pal_window);
  int origin[2] = {0, 0};
  int position[2];
  int flags = SCREEN_FLAG_POSITION_VALID;
  int wheel = 0;
  int modifiers = 0;
  int64_t native_x;
  int64_t native_y;
  if (window == NULL ||
      screen_get_window_property_iv(window, SCREEN_PROPERTY_POSITION, origin) !=
          0) {
    return MY_RET_FAIL;
  }
  native_x = (int64_t)x + origin[0];
  native_y = (int64_t)y + origin[1];
  if (native_x < INT_MIN || native_x > INT_MAX || native_y < INT_MIN ||
      native_y > INT_MAX) {
    return MY_RET_FAIL;
  }
  position[0] = (int)native_x;
  position[1] = (int)native_y;
  if (native_event_begin(state, SCREEN_EVENT_POINTER, &event) != MY_RET_OK) {
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
  return native_event_send(state, event);
}

static my_ret_t native_send_widget_pointer(screen_e2e_state_t* state,
                                           my_widget_t* widget, int32_t x,
                                           int32_t y, int buttons) {
  my_widget_local_to_global(widget, &x, &y);
  return native_send_pointer(state, x, y, buttons);
}

static my_ret_t native_send_key(screen_e2e_state_t* state, int symbol,
                                int flags) {
  screen_event_t event;
  int modifiers = 0;
  if (native_event_begin(state, SCREEN_EVENT_KEYBOARD, &event) != MY_RET_OK) {
    return MY_RET_FAIL;
  }
  if (screen_set_event_property_iv(event, SCREEN_PROPERTY_SYM, &symbol) != 0 ||
      screen_set_event_property_iv(event, SCREEN_PROPERTY_FLAGS, &flags) != 0 ||
      screen_set_event_property_iv(event, SCREEN_PROPERTY_MODIFIERS,
                                   &modifiers) != 0) {
    (void)screen_destroy_event(event);
    return MY_RET_FAIL;
  }
  return native_event_send(state, event);
}

static my_ret_t native_resize(screen_e2e_state_t* state, int width, int height) {
  int size[2] = {width, height};
  screen_context_t context =
      (screen_context_t)my_pal_screen_native_context(state->pal);
  screen_window_t window =
      (screen_window_t)my_pal_screen_native_window(state->win->pal_window);
  if (context == NULL || window == NULL ||
      screen_set_window_property_iv(window, SCREEN_PROPERTY_SIZE, size) != 0 ||
      screen_flush_context(context, 0) != 0) {
    return MY_RET_FAIL;
  }
  return MY_RET_OK;
}

static my_ret_t native_send_property(screen_e2e_state_t* state, int property) {
  screen_event_t event;
  if (native_event_begin(state, SCREEN_EVENT_PROPERTY, &event) != MY_RET_OK) {
    return MY_RET_FAIL;
  }
  if (screen_set_event_property_iv(event, SCREEN_PROPERTY_NAME, &property) != 0) {
    (void)screen_destroy_event(event);
    return MY_RET_FAIL;
  }
  return native_event_send(state, event);
}

static my_ret_t native_send_close(screen_e2e_state_t* state) {
  screen_context_t context = NULL;
  screen_event_t event;
  int subtype = MY_PAL_SCREEN_MANAGER_CLOSE;
  int result;
  int error;
  if (screen_create_context(&context, SCREEN_WINDOW_MANAGER_CONTEXT) != 0 ||
      native_event_begin(state, SCREEN_EVENT_MANAGER, &event) != MY_RET_OK) {
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
  (void)screen_destroy_event(event);
  (void)screen_destroy_context(context);
  errno = error;
  return result == 0 ? MY_RET_OK : MY_RET_FAIL;
}

static void e2e_button_click(void* context, const char* event, void* data) {
  screen_e2e_state_t* state = (screen_e2e_state_t*)context;
  const my_event_t* source = (const my_event_t*)data;
  (void)event;
  state->button_clicks++;
  state->button_click_pointer_up =
      source != NULL && source->type == MY_EVENT_POINTER_UP;
  if (my_progress_bar_set_value(state->progress, 25.0f) != MY_RET_OK) {
    (void)e2e_check(state, false, "button callback could not update progress");
  }
}

static void e2e_edit_changed(void* context, const char* event, void* data) {
  screen_e2e_state_t* state = (screen_e2e_state_t*)context;
  (void)event;
  (void)data;
  state->edit_changes++;
}

static void e2e_edit_focus(void* context, const char* event, void* data) {
  screen_e2e_state_t* state = (screen_e2e_state_t*)context;
  (void)event;
  (void)data;
  state->edit_focuses++;
}

static void e2e_edit_blur(void* context, const char* event, void* data) {
  screen_e2e_state_t* state = (screen_e2e_state_t*)context;
  (void)event;
  (void)data;
  state->edit_blurs++;
}

static void e2e_edit_key_up(void* context, const char* event, void* data) {
  screen_e2e_state_t* state = (screen_e2e_state_t*)context;
  (void)event;
  (void)data;
  state->edit_key_ups++;
}

static void e2e_slider_changed(void* context, const char* event, void* data) {
  screen_e2e_state_t* state = (screen_e2e_state_t*)context;
  (void)event;
  (void)data;
  if (state->slider_changes < 2) {
    state->slider_values[state->slider_changes] =
        my_slider_get_value(state->slider);
  }
  state->slider_changes++;
}

static void e2e_window_closed(void* context) {
  screen_e2e_state_t* state = (screen_e2e_state_t*)context;
  state->close_count++;
}

static my_ret_t e2e_watchdog(void* context) {
  screen_e2e_state_t* state = (screen_e2e_state_t*)context;
  state->watchdog_fires++;
  (void)e2e_check(state, false, "watchdog expired before native close");
  (void)my_pal_main_loop_quit(state->loop);
  return MY_RET_FAIL;
}

static my_ret_t e2e_phase(void* context) {
  screen_e2e_state_t* state = (screen_e2e_state_t*)context;
  int phase = state->phase++;
  uint32_t before;
  switch (phase) {
    case 0:
      (void)e2e_check(state, my_window_manager_count(state->wm) == 1u,
                      "initial window count is not one");
      (void)e2e_check(
          state, my_pal_screen_test_post_count(state->win->pal_window) > 0u,
          "window manager did not automatically post the initial frame");
      state->posts_before =
          my_pal_screen_test_post_count(state->win->pal_window);
      (void)e2e_check(
          state,
          native_send_widget_pointer(state, state->button, 64, 18,
                                     SCREEN_LEFT_MOUSE_BUTTON) == MY_RET_OK,
          "button down injection failed");
      (void)e2e_check(state,
                      native_send_widget_pointer(state, state->button, 64, 18,
                                                 0) == MY_RET_OK,
                      "button up injection failed");
      return MY_RET_OK;
    case 1:
      (void)e2e_check(state, state->button_clicks == 1,
                      "button click listener count is not one");
      (void)e2e_check(state, state->button_click_pointer_up,
                      "button click did not originate from pointer up");
      (void)e2e_check(state,
                      my_progress_bar_get_value(state->progress) == 25.0f,
                      "button callback did not update the progress bar");
      (void)e2e_check(state,
                      !((my_button_t*)state->button)->pointer_pressed,
                      "button remained pointer-pressed after up");
      (void)e2e_check(state, state->win->dispatcher.grabbed == NULL,
                      "button pointer grab survived up");
      (void)e2e_check(
          state,
          my_pal_screen_test_post_count(state->win->pal_window) >
              state->posts_before,
          "button and progress changes were not automatically posted");
      state->posts_before =
          my_pal_screen_test_post_count(state->win->pal_window);
      (void)e2e_check(
          state,
          native_send_widget_pointer(state, state->edit, 80, 16,
                                     SCREEN_LEFT_MOUSE_BUTTON) == MY_RET_OK,
          "edit focus down injection failed");
      (void)e2e_check(state,
                      native_send_widget_pointer(state, state->edit, 80, 16,
                                                 0) == MY_RET_OK,
                      "edit focus up injection failed");
      (void)e2e_check(state,
                      native_send_key(state, 'q',
                                      KEY_DOWN | KEY_SYM_VALID) == MY_RET_OK,
                      "q key down injection failed");
      (void)e2e_check(state,
                      native_send_key(state, 'q', KEY_SYM_VALID) == MY_RET_OK,
                      "q key up injection failed");
      return MY_RET_OK;
    case 2:
      (void)e2e_check(state, state->edit_focuses == 1,
                      "edit focus listener count is not one");
      (void)e2e_check(state, state->edit_blurs == 0,
                      "edit lost focus while typing q");
      (void)e2e_check(state, state->win->dispatcher.focused == state->edit,
                      "dispatcher focus is not the edit");
      (void)e2e_check(state, ((my_edit_t*)state->edit)->focused,
                      "edit focused state is false");
      (void)e2e_check(state, state->edit_changes == 1,
                      "edit changed listener count is not one");
      (void)e2e_check(state, state->edit_key_ups == 1,
                      "edit key up listener count is not one");
      (void)e2e_check(state,
                      strcmp(my_edit_get_text(state->edit), "q") == 0,
                      "native q key did not edit the text");
      (void)e2e_check(state, !((my_button_t*)state->button)->pressed,
                      "button delayed release did not complete");
      (void)e2e_check(
          state,
          my_pal_screen_test_post_count(state->win->pal_window) >
              state->posts_before,
          "edit focus/text changes were not automatically posted");
      state->posts_before =
          my_pal_screen_test_post_count(state->win->pal_window);
      (void)e2e_check(
          state,
          native_send_widget_pointer(state, state->slider, 56, 14,
                                     SCREEN_LEFT_MOUSE_BUTTON) == MY_RET_OK,
          "slider down injection failed");
      (void)e2e_check(
          state,
          native_send_widget_pointer(state, state->slider, 152, 14,
                                     SCREEN_LEFT_MOUSE_BUTTON) == MY_RET_OK,
          "slider move injection failed");
      (void)e2e_check(state,
                      native_send_widget_pointer(state, state->slider, 152, 14,
                                                 0) == MY_RET_OK,
                      "slider up injection failed");
      return MY_RET_OK;
    case 3:
      (void)e2e_check(state, state->slider_changes == 2,
                      "slider changed listener did not fire once per down/move");
      (void)e2e_check(state, state->slider_values[0] == 25.0f,
                      "slider down did not select 25 percent");
      (void)e2e_check(state, state->slider_values[1] == 75.0f,
                      "slider move did not select 75 percent");
      (void)e2e_check(state, my_slider_get_value(state->slider) == 75.0f,
                      "slider final value is not 75 percent");
      (void)e2e_check(state, !((my_slider_t*)state->slider)->dragging,
                      "slider remained dragging after up");
      (void)e2e_check(state, state->win->dispatcher.grabbed == NULL,
                      "slider pointer grab survived up");
      (void)e2e_check(state, state->win->dispatcher.focused == state->slider,
                      "slider did not receive pointer focus");
      (void)e2e_check(state, state->edit_blurs == 1,
                      "edit blur listener count is not one");
      (void)e2e_check(state, !((my_edit_t*)state->edit)->focused,
                      "edit remained focused after slider down");
      (void)e2e_check(
          state,
          my_pal_screen_test_post_count(state->win->pal_window) >
              state->posts_before,
          "slider changes were not automatically posted");
      state->posts_before =
          my_pal_screen_test_post_count(state->win->pal_window);
      (void)e2e_check(state, native_resize(state, 280, 220) == MY_RET_OK,
                      "native window resize failed");
      (void)e2e_check(
          state, native_send_property(state, SCREEN_PROPERTY_SIZE) == MY_RET_OK,
          "native size property event injection failed");
      return MY_RET_OK;
    case 4: {
      int32_t width = 0;
      int32_t height = 0;
      int native_size[2] = {0, 0};
      int native_result;
      int size_error;
      my_ret_t size_result;
      my_widget_t* root = (my_widget_t*)state->win;
      screen_window_t native_window =
          (screen_window_t)my_pal_screen_native_window(state->win->pal_window);
      (void)e2e_check(state, root->rect.w == 280 && root->rect.h == 220,
                      "resize event did not update the root widget to 280x220");
      errno = 0;
      size_result =
          my_pal_window_get_size(state->win->pal_window, &width, &height);
      size_error = errno;
      native_result = screen_get_window_property_iv(
          native_window, SCREEN_PROPERTY_SIZE, native_size);
      (void)e2e_check(state, size_result == MY_RET_OK,
                      "PAL size query failed after native resize");
      (void)e2e_check(state, width == 280 && height == 220,
                      "PAL size is not 280x220 after native resize");
      (void)e2e_check(state, state->win->vg != NULL,
                      "software canvas was not recreated after native resize");
      (void)e2e_check(
          state, my_pal_screen_test_post_count(state->win->pal_window) >
              state->posts_before,
          "resized window was not automatically posted on its rebuilt LCD");
      if (root->rect.w != 280 || root->rect.h != 220 ||
          size_result != MY_RET_OK || width != 280 || height != 220 ||
          native_result != 0 || native_size[0] != 280 ||
          native_size[1] != 220) {
        int native_buffer_size[2] = {0, 0};
        int native_buffer_result = screen_get_window_property_iv(
            native_window, SCREEN_PROPERTY_BUFFER_SIZE, native_buffer_size);
        printf("  resize diagnostic: root=%dx%d result=%d errno=%d (%s) "
               "pal=%dx%d native_result=%d native=%dx%d buffer_result=%d "
               "buffer=%dx%d posts=%u\n",
               root->rect.w, root->rect.h, size_result, size_error,
               strerror(size_error), width, height, native_result,
               native_size[0], native_size[1], native_buffer_result,
               native_buffer_size[0], native_buffer_size[1],
               my_pal_screen_test_post_count(state->win->pal_window));
      }
      (void)e2e_check(state, state->close_count == 0,
                      "window closed before native manager close");
      (void)e2e_check(state, my_window_manager_count(state->wm) == 1u,
                      "window count changed before close");
      (void)e2e_check(state, !state->wm->quit_requested,
                      "window manager quit before close");
      before = my_pal_screen_test_post_count(state->win->pal_window);
      my_widget_invalidate(root, NULL);
      my_window_paint(state->win);
      (void)e2e_check(
          state,
          my_pal_screen_test_post_count(state->win->pal_window) == before + 1u,
          "explicit full dirty resize frame did not commit exactly once");
      if (native_send_close(state) == MY_RET_OK) {
        state->close_sent = true;
      } else {
        (void)e2e_check(state, false, "native manager close injection failed");
      }
      return MY_RET_FAIL;
    }
    default:
      (void)e2e_check(state, false, "unexpected phase timer fire");
      return MY_RET_FAIL;
  }
}

static bool e2e_setup(screen_e2e_state_t* state) {
  my_widget_t* content;
  state->loop = my_pal_main_loop_create(state->pal);
  if (!e2e_check(state, state->loop != NULL, "main loop creation failed")) {
    return false;
  }
  state->wm = my_window_manager_create(NULL, state->pal, state->loop);
  if (!e2e_check(state, state->wm != NULL, "window manager creation failed")) {
    return false;
  }
  state->win = my_window_create(NULL, state->pal, 240, 190, "myui Screen E2E");
  if (!e2e_check(state, state->win != NULL, "window creation failed")) {
    return false;
  }
  state->font = my_font_bitmap_create(NULL);
  if (!e2e_check(state, state->font != NULL, "bitmap font creation failed")) {
    return false;
  }
  my_window_set_font(state->win, state->font, 16);
  state->button = my_button_create(NULL, "Advance");
  state->progress = my_progress_bar_create(NULL);
  state->edit = my_edit_create(NULL);
  state->slider = my_slider_create(NULL);
  if (!e2e_check(state,
                 state->button != NULL && state->progress != NULL &&
                     state->edit != NULL && state->slider != NULL,
                 "control creation failed")) {
    return false;
  }
  if (!e2e_check(
          state,
          my_widget_set_rect(state->button, &(my_rect_t){16, 16, 128, 36}) ==
                  MY_RET_OK &&
              my_widget_set_rect(state->progress,
                                 &(my_rect_t){16, 64, 208, 20}) == MY_RET_OK &&
              my_widget_set_rect(state->edit, &(my_rect_t){16, 96, 208, 32}) ==
                  MY_RET_OK &&
              my_widget_set_rect(state->slider,
                                 &(my_rect_t){16, 144, 208, 28}) == MY_RET_OK,
          "control geometry setup failed")) {
    return false;
  }
  if (!e2e_check(state,
                 my_widget_on(state->button, "click", e2e_button_click, state) !=
                         0u &&
                     my_widget_on(state->edit, "changed", e2e_edit_changed,
                                  state) != 0u &&
                     my_widget_on(state->edit, "focus", e2e_edit_focus, state) !=
                         0u &&
                     my_widget_on(state->edit, "blur", e2e_edit_blur, state) !=
                         0u &&
                     my_widget_on(state->edit, "key_up", e2e_edit_key_up,
                                  state) != 0u &&
                     my_widget_on(state->slider, "changed", e2e_slider_changed,
                                  state) != 0u &&
                     my_window_add_close_listener(state->win, e2e_window_closed,
                                                  state) != 0u,
                 "listener registration failed")) {
    return false;
  }
  content = my_window_widget(state->win);
  if (!e2e_check(state,
                 my_widget_add_child(content, state->button) == MY_RET_OK &&
                     my_widget_add_child(content, state->progress) == MY_RET_OK &&
                     my_widget_add_child(content, state->edit) == MY_RET_OK &&
                     my_widget_add_child(content, state->slider) == MY_RET_OK,
                 "control tree setup failed")) {
    return false;
  }
  if (!e2e_check(state,
                 my_window_manager_open(state->wm, state->win) == MY_RET_OK,
                 "window manager open failed")) {
    return false;
  }
  if (!e2e_check(state,
                 my_pal_screen_native_context(state->pal) != NULL &&
                     my_pal_screen_native_window(state->win->pal_window) != NULL,
                 "native Screen context/window is unavailable")) {
    return false;
  }
  return true;
}

static void e2e_cleanup(screen_e2e_state_t* state) {
  if (state->wm != NULL) {
    my_window_manager_destroy(state->wm);
    state->wm = NULL;
  }
  my_widget_unref(state->button);
  my_widget_unref(state->progress);
  my_widget_unref(state->edit);
  my_widget_unref(state->slider);
  state->button = NULL;
  state->progress = NULL;
  state->edit = NULL;
  state->slider = NULL;
  if (state->win != NULL) {
    my_widget_unref((my_widget_t*)state->win);
    state->win = NULL;
  }
  if (state->font != NULL) {
    my_font_destroy(state->font);
    state->font = NULL;
  }
  if (state->loop != NULL) {
    my_pal_main_loop_destroy(state->loop);
    state->loop = NULL;
  }
}

static void e2e_execute(screen_e2e_state_t* state) {
  bool ran = false;
  int close_count_before_cleanup;
  if (!e2e_setup(state)) goto cleanup;
  state->phase_timer_id = my_pal_main_loop_add_timer(
      state->loop, e2e_phase, state, E2E_PHASE_MS);
  if (!e2e_check(state, state->phase_timer_id != 0u,
                 "phase timer creation failed")) {
    goto cleanup;
  }
  state->watchdog_timer_id = my_pal_main_loop_add_timer(
      state->loop, e2e_watchdog, state, E2E_WATCHDOG_MS);
  if (!e2e_check(state, state->watchdog_timer_id != 0u,
                 "watchdog timer creation failed")) {
    goto cleanup;
  }
  ran = true;
  (void)e2e_check(state, my_pal_main_loop_run(state->loop) == MY_RET_OK,
                  "Screen main loop failed");
  (void)e2e_check(state, state->phase == 5,
                  "not all input/resize/paint phases executed");
  (void)e2e_check(state, state->close_sent,
                  "native manager close was not sent");
  (void)e2e_check(state, state->watchdog_fires == 0,
                  "watchdog was needed to exit the loop");
  (void)e2e_check(state, state->close_count == 1,
                  "window close listener count is not exactly one");
  (void)e2e_check(state, my_window_manager_count(state->wm) == 0u,
                  "window manager count is not zero after close");
  (void)e2e_check(state, state->wm->quit_requested,
                  "window manager did not request quit after last close");
  (void)e2e_check(state, state->win->close_notified,
                  "creator-ref window did not receive close notification");
cleanup:
  close_count_before_cleanup = state->close_count;
  e2e_cleanup(state);
  if (ran && close_count_before_cleanup == 1) {
    (void)e2e_check(state, state->close_count == 1,
                    "window close listener fired again during cleanup");
  }
}

TEST(screen_myui_native_controls_paint_and_close)
{
  screen_e2e_state_t state = {0};
  state.pal = g_pal;
  e2e_execute(&state);
  ASSERT_EQ(state.failures, 0);
}

int main(void) {
  setvbuf(stdout, NULL, _IONBF, 0);
  g_pal = my_pal_create(NULL);
  if (g_pal == NULL) {
    printf("SKIP: no usable QNX Screen service\n");
    return getenv("BREAK_QNX_SCREEN_REQUIRED") != NULL ? 1 : 77;
  }
  printf("=== Running Tests ===\n");
  RUN_TEST(screen_myui_native_controls_paint_and_close);
  my_pal_destroy(g_pal);
  g_pal = NULL;
  printf("\n=== Results: %d passed, %d failed, %d total ===\n", g_test_pass,
         g_test_fail, g_test_count);
  return g_test_fail > 0 ? 1 : 0;
}
