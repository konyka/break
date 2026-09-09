#include "test_framework.h"

#include <stdlib.h>
#include <string.h>
#include <limits.h>

#include "mypal/dummy/my_pal_dummy.h"
#include "myc/my_ref_count.h"
#include "myc/my_emitter.h"
#include "mypal/my_event.h"
#include "mypal/my_timer.h"
#include "myr/my_font.h"
#include "myr/my_lcd_mem.h"
#include "myr/my_text_layout.h"
#include "myr/my_ui_metrics.h"
#include "myr/my_vgcanvas_soft.h"
#include "myui/my_layout.h"
#include "myui/my_ui_command.h"
#include "myui/my_window_manager.h"
#include "myui/my_undo_manager.h"
#include "myui/my_undo_stack.h"
#include "myui/widgets/my_dialog.h"
#include "myui/widgets/my_button.h"
#include "myui/widgets/my_checkbox.h"
#include "myui/widgets/my_label.h"
#include "myui/widgets/my_image.h"
#include "myui/widgets/my_menu.h"
#include "myui/widgets/my_node_view.h"
#include "myui/widgets/my_edit.h"
#include "myui/widgets/my_text_area.h"
#include "myui/widgets/my_list_view.h"
#include "myui/widgets/my_progress_bar.h"
#include "myui/widgets/my_rich_label.h"
#include "myui/widgets/my_scroll_bar.h"
#include "myui/widgets/my_scroll_view.h"
#include "myui/widgets/my_slider.h"

static int g_open_count;
static my_window_manager_t* g_hook_wm;
static my_window_t* g_hook_win;
static void* g_hook_ctx;

typedef struct command_lifecycle_test_t {
  my_window_manager_t* wm;
  my_window_t* win;
  int execute_count;
  int destroy_count;
} command_lifecycle_test_t;

static my_ret_t command_lifecycle_execute(void* context) {
  command_lifecycle_test_t* state = (command_lifecycle_test_t*)context;
  state->execute_count++;
  if (state->wm != NULL && state->win != NULL) {
    (void)my_window_manager_close(state->wm, state->win);
  }
  return MY_RET_OK;
}

static void command_lifecycle_destroy(void* context) {
  command_lifecycle_test_t* state = (command_lifecycle_test_t*)context;
  state->destroy_count++;
}

typedef struct list_guard_adapter_t {
  my_list_adapter_t base;
  const my_allocator_t* allocator;
  size_t count;
  int32_t height;
} list_guard_adapter_t;

static size_t list_guard_count(my_list_adapter_t* adapter) {
  return ((list_guard_adapter_t*)adapter)->count;
}

static my_widget_t* list_guard_create_row(my_list_adapter_t* adapter) {
  return my_widget_create(((list_guard_adapter_t*)adapter)->allocator,
                          "guard-row");
}

static void list_guard_bind_row(my_list_adapter_t* adapter, my_widget_t* row,
                                size_t index) {
  (void)adapter;
  (void)row;
  (void)index;
}

static int32_t list_guard_height(my_list_adapter_t* adapter, size_t index) {
  (void)index;
  return ((list_guard_adapter_t*)adapter)->height;
}

static const my_list_adapter_vtable_t list_guard_vtable = {
    list_guard_count, list_guard_create_row, list_guard_bind_row,
    list_guard_height};

typedef struct list_reentrant_adapter_t {
  my_list_adapter_t base;
  my_widget_t* list;
  my_ret_t result;
  int calls;
} list_reentrant_adapter_t;

typedef struct animator_reentrant_test_t {
  my_animator_manager_t* manager;
  int update_calls;
} animator_reentrant_test_t;

static void animator_stop_all_from_update(my_widget_t* widget, void* ctx) {
  animator_reentrant_test_t* state = (animator_reentrant_test_t*)ctx;
  state->update_calls++;
  my_animator_stop_widget(state->manager, widget);
}

typedef struct animator_destroy_test_t {
  my_animator_manager_t* manager;
  int update_calls;
} animator_destroy_test_t;

static void animator_destroy_from_update(my_widget_t* widget, void* ctx) {
  animator_destroy_test_t* state = (animator_destroy_test_t*)ctx;
  (void)widget;
  state->update_calls++;
  my_animator_manager_destroy(state->manager);
}

static size_t list_reentrant_count(my_list_adapter_t* adapter) {
  list_reentrant_adapter_t* state = (list_reentrant_adapter_t*)adapter;
  state->calls++;
  state->result = my_list_view_set_scroll_offset(state->list, 12);
  return 1u;
}

static my_widget_t* list_reentrant_create_row(my_list_adapter_t* adapter) {
  (void)adapter;
  return my_widget_create(NULL, "reentrant-row");
}

static void list_reentrant_bind_row(my_list_adapter_t* adapter,
                                    my_widget_t* row, size_t index) {
  (void)row;
  (void)index;
  (void)list_reentrant_count(adapter);
}

static const my_list_adapter_vtable_t list_reentrant_vtable = {
    list_reentrant_count, list_reentrant_create_row, list_reentrant_bind_row,
    NULL};

typedef struct leased_list_adapter_t {
  my_list_adapter_t base;
  size_t count;
  int* destroy_count;
} leased_list_adapter_t;

static size_t leased_list_count(my_list_adapter_t* adapter) {
  return ((leased_list_adapter_t*)adapter)->count;
}

static my_widget_t* leased_list_create_row(my_list_adapter_t* adapter) {
  (void)adapter;
  return my_widget_create(NULL, "leased-row");
}

static void leased_list_bind_row(my_list_adapter_t* adapter,
                                 my_widget_t* row, size_t index) {
  (void)adapter;
  (void)row;
  (void)index;
}

static const my_list_adapter_vtable_t leased_list_vtable = {
    leased_list_count, leased_list_create_row, leased_list_bind_row, NULL};

static void leased_list_destroy(my_list_adapter_t* adapter, void* context) {
  leased_list_adapter_t* state = (leased_list_adapter_t*)adapter;
  (void)context;
  (*state->destroy_count)++;
  free(state);
}

typedef struct image_test_loader_t {
  my_image_loader_t base;
  uint8_t rgba[4];
  int load_count;
  int free_count;
  bool return_invalid_data;
  int lease_release_count;
} image_test_loader_t;

static my_image_data_t* image_test_load(my_image_loader_t* loader,
                                        const char* path) {
  image_test_loader_t* test_loader = (image_test_loader_t*)loader;
  my_image_data_t* data;
  (void)path;
  data = (my_image_data_t*)calloc(1, sizeof(*data));
  if (data == NULL) {
    return NULL;
  }
  data->pixels = (uint8_t*)malloc(4u);
  if (data->pixels == NULL) {
    free(data);
    return NULL;
  }
  memcpy(data->pixels, test_loader->rgba, 4u);
  if (test_loader->return_invalid_data) {
    free(data->pixels);
    data->pixels = NULL;
  }
  data->w = 1;
  data->h = 1;
  test_loader->load_count++;
  return data;
}

static void image_test_free_data(my_image_loader_t* loader,
                                 my_image_data_t* data) {
  image_test_loader_t* test_loader = (image_test_loader_t*)loader;
  if (data != NULL) {
    test_loader->free_count++;
    free(data->pixels);
    free(data);
  }
}

static void image_test_destroy(my_image_loader_t* loader) {
  (void)loader;
}

static void image_test_release(my_image_loader_t* loader, void* context) {
  image_test_loader_t* test_loader = (image_test_loader_t*)loader;
  (void)context;
  test_loader->lease_release_count++;
}

static const my_image_loader_vtable_t image_test_loader_vtable = {
    image_test_load, image_test_free_data, image_test_destroy};
static void on_open_cb(my_window_manager_t* wm, my_window_t* win, void* ctx) {
  g_open_count++;
  g_hook_wm = wm;
  g_hook_win = win;
  g_hook_ctx = ctx;
}

typedef struct on_open_owned_reentry_context_t {
  int destroy_count;
  int callback_count;
  int set_result;
  bool replace_once;
  bool* callback_active;
  bool* destroyed_during_callback;
  void* replacement_context;
} on_open_owned_reentry_context_t;

static void on_open_owned_reentry_destroy(void* context) {
  on_open_owned_reentry_context_t* state =
      (on_open_owned_reentry_context_t*)context;
  state->destroy_count++;
  if (state->callback_active != NULL && *state->callback_active &&
      state->destroyed_during_callback != NULL) {
    *state->destroyed_during_callback = true;
  }
}

static void on_open_owned_reentry_callback(my_window_manager_t* wm,
                                            my_window_t* win, void* context) {
  on_open_owned_reentry_context_t* state =
      (on_open_owned_reentry_context_t*)context;
  (void)win;
  state->callback_count++;
  if (!state->replace_once) {
    state->replace_once = true;
    if (state->callback_active != NULL) {
      *state->callback_active = true;
    }
    state->set_result = my_window_manager_set_on_open_owned(
        wm, on_open_owned_reentry_callback, state->replacement_context,
        on_open_owned_reentry_destroy);
    if (state->callback_active != NULL) {
      *state->callback_active = false;
    }
  }
}


typedef struct manager_destroy_reentry_t {
  my_window_manager_t* manager;
  int calls;
  uint32_t rejected_id;
} manager_destroy_reentry_t;

static void manager_destroy_reentry_cb(void* ctx) {
  manager_destroy_reentry_t* state = (manager_destroy_reentry_t*)ctx;
  state->calls++;
  state->rejected_id = my_window_manager_add_destroy_listener(
      state->manager, manager_destroy_reentry_cb, state);
  my_window_manager_destroy(state->manager);
}

typedef struct text_area_fail_alloc_t {
  bool fail;
  bool fail_realloc;
} text_area_fail_alloc_t;

typedef struct text_area_count_alloc_t {
  size_t alloc_calls;
} text_area_count_alloc_t;

typedef struct timer_free_guard_t {
  void* freed[32];
  size_t freed_count;
  bool duplicate_free;
} timer_free_guard_t;

static void* timer_free_guard_alloc(void* ctx, size_t size) {
  (void)ctx;
  return malloc(size);
}

static void* timer_free_guard_calloc(void* ctx, size_t count, size_t size) {
  (void)ctx;
  return calloc(count, size);
}

static void* timer_free_guard_realloc(void* ctx, void* ptr, size_t size) {
  (void)ctx;
  return realloc(ptr, size);
}

static void timer_free_guard_free(void* ctx, void* ptr) {
  timer_free_guard_t* state = (timer_free_guard_t*)ctx;
  size_t i;
  if (ptr == NULL) return;
  for (i = 0u; i < state->freed_count; ++i) {
    if (state->freed[i] == ptr) {
      state->duplicate_free = true;
      return;
    }
  }
  if (state->freed_count < sizeof(state->freed) / sizeof(state->freed[0])) {
    state->freed[state->freed_count++] = ptr;
  }
  free(ptr);
}

typedef struct undo_guard_alloc_t {
  bool bad_size_request;
} undo_guard_alloc_t;

static void* undo_guard_alloc(void* ctx, size_t size) {
  undo_guard_alloc_t* state = (undo_guard_alloc_t*)ctx;
  if (size == 0 || size > 1024u) {
    state->bad_size_request = true;
    return NULL;
  }
  return malloc(size);
}

static void* undo_guard_calloc(void* ctx, size_t count, size_t size) {
  undo_guard_alloc_t* state = (undo_guard_alloc_t*)ctx;
  if (count != 0 && size > SIZE_MAX / count) {
    state->bad_size_request = true;
    return NULL;
  }
  if (count != 0 && size > 1024u / count) {
    state->bad_size_request = true;
    return NULL;
  }
  return calloc(count, size);
}

static void* undo_guard_realloc(void* ctx, void* ptr, size_t size) {
  undo_guard_alloc_t* state = (undo_guard_alloc_t*)ctx;
  if (size == 0 || size > 1024u) {
    state->bad_size_request = true;
    return NULL;
  }
  return realloc(ptr, size);
}

static void undo_guard_free(void* ctx, void* ptr) {
  (void)ctx;
  free(ptr);
}

static void* text_area_count_alloc(void* ctx, size_t size) {
  text_area_count_alloc_t* state = (text_area_count_alloc_t*)ctx;
  void* ptr = malloc(size);
  if (ptr != NULL) state->alloc_calls++;
  return ptr;
}

static void* text_area_count_calloc(void* ctx, size_t count, size_t size) {
  text_area_count_alloc_t* state = (text_area_count_alloc_t*)ctx;
  void* ptr = calloc(count, size);
  if (ptr != NULL) state->alloc_calls++;
  return ptr;
}

static void* text_area_count_realloc(void* ctx, void* ptr, size_t size) {
  text_area_count_alloc_t* state = (text_area_count_alloc_t*)ctx;
  void* grown = realloc(ptr, size);
  if (grown != NULL && grown != ptr) state->alloc_calls++;
  return grown;
}

static void text_area_count_free(void* ctx, void* ptr) {
  (void)ctx;
  free(ptr);
}

static void* text_area_fail_alloc(void* ctx, size_t size) {
  text_area_fail_alloc_t* state = (text_area_fail_alloc_t*)ctx;
  return state->fail ? NULL : malloc(size);
}

static void* text_area_fail_calloc(void* ctx, size_t count, size_t size) {
  text_area_fail_alloc_t* state = (text_area_fail_alloc_t*)ctx;
  return state->fail ? NULL : calloc(count, size);
}

static void* text_area_fail_realloc(void* ctx, void* ptr, size_t size) {
  text_area_fail_alloc_t* state = (text_area_fail_alloc_t*)ctx;
  return state->fail || state->fail_realloc ? NULL : realloc(ptr, size);
}

static void text_area_fail_free(void* ctx, void* ptr) {
  (void)ctx;
  free(ptr);
}

static void count_edit_changed(void* ctx, const char* event, void* data) {
  int* count = (int*)ctx;
  (void)event;
  (void)data;
  (*count)++;
}

typedef struct paste_self_remove_t {
  my_widget_t* parent;
  my_widget_t* widget;
  bool called;
} paste_self_remove_t;

static void remove_paste_widget_on_changed(void* ctx, const char* event,
                                           void* data) {
  paste_self_remove_t* state = (paste_self_remove_t*)ctx;
  (void)event;
  (void)data;
  state->called = true;
  if (state->widget != NULL) {
    (void)my_widget_remove_child(state->parent, state->widget);
    my_widget_unref(state->widget);
    state->widget = NULL;
  }
}

typedef struct text_area_variable_font_t {
  my_font_t base;
  size_t glyph_calls;
  size_t measure_calls;
} text_area_variable_font_t;

static my_ret_t text_area_variable_font_measure(my_font_t* font,
                                                const char* text, int32_t size,
                                                int32_t* width, int32_t* height) {
  const char* p = text;
  int32_t total = 0;
  text_area_variable_font_t* variable_font = (text_area_variable_font_t*)font;
  variable_font->measure_calls++;
  if (text == NULL || size <= 0 || width == NULL) return MY_RET_INVALID_PARAMS;
  while (*p != '\0') {
    total += *p == 'A' ? 5 : 20;
    p++;
  }
  *width = total;
  if (height != NULL) *height = size;
  return MY_RET_OK;
}

static my_ret_t text_area_variable_font_glyph(my_font_t* font,
                                              uint32_t codepoint, int32_t size,
                                              my_glyph_t* glyph) {
  text_area_variable_font_t* variable_font =
      (text_area_variable_font_t*)font;
  variable_font->glyph_calls++;
  if (glyph == NULL || size <= 0) return MY_RET_INVALID_PARAMS;
  memset(glyph, 0, sizeof(*glyph));
  glyph->advance = codepoint == 'A' ? 5 : 20;
  return MY_RET_OK;
}

static int32_t text_area_variable_font_ascent(my_font_t* font, int32_t size) {
  (void)font;
  return size;
}

static int32_t text_area_variable_font_descent(my_font_t* font, int32_t size) {
  (void)font;
  (void)size;
  return 0;
}

static int32_t text_area_variable_font_line_height(my_font_t* font,
                                                   int32_t size) {
  (void)font;
  return size + 8;
}

static void text_area_variable_font_destroy(my_font_t* font) { (void)font; }

static bool text_area_variable_font_has_glyph(my_font_t* font,
                                              uint32_t codepoint) {
  (void)font;
  return codepoint == 'A' || codepoint == 'B';
}

static const my_font_vtable_t text_area_variable_font_vtable = {
    text_area_variable_font_measure,
    text_area_variable_font_glyph,
    text_area_variable_font_ascent,
    text_area_variable_font_descent,
    text_area_variable_font_line_height,
    text_area_variable_font_destroy,
    text_area_variable_font_has_glyph,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL};

typedef struct text_area_huge_font_t {
  my_font_t base;
} text_area_huge_font_t;

static my_ret_t text_area_huge_font_measure(my_font_t* font,
                                            const char* text, int32_t size,
                                            int32_t* width, int32_t* height) {
  (void)font;
  (void)text;
  if (size <= 0 || width == NULL) return MY_RET_INVALID_PARAMS;
  *width = INT32_MAX;
  if (height != NULL) *height = size;
  return MY_RET_OK;
}

static my_ret_t text_area_huge_font_glyph(my_font_t* font, uint32_t codepoint,
                                          int32_t size, my_glyph_t* glyph) {
  (void)font;
  (void)codepoint;
  if (size <= 0 || glyph == NULL) return MY_RET_INVALID_PARAMS;
  memset(glyph, 0, sizeof(*glyph));
  glyph->advance = INT32_MAX;
  return MY_RET_OK;
}

static int32_t text_area_huge_font_ascent(my_font_t* font, int32_t size) {
  (void)font;
  return size;
}

static int32_t text_area_huge_font_descent(my_font_t* font, int32_t size) {
  (void)font;
  (void)size;
  return 0;
}

static int32_t text_area_huge_font_line_height(my_font_t* font, int32_t size) {
  (void)font;
  (void)size;
  return 16;
}

static void text_area_huge_font_destroy(my_font_t* font) { (void)font; }

static const my_font_vtable_t text_area_huge_font_vtable = {
    text_area_huge_font_measure,
    text_area_huge_font_glyph,
    text_area_huge_font_ascent,
    text_area_huge_font_descent,
    text_area_huge_font_line_height,
    text_area_huge_font_destroy,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL};

static my_ret_t text_area_ligature_shape(my_font_t* font, const char* text,
                                         int32_t size, bool rtl,
                                         const my_allocator_t* allocator,
                                         my_font_shape_result_t* result) {
  const char* hebrew = "\xD7\x90\xD7\x91";
  size_t i;
  if (font == NULL || text == NULL || size <= 0 || result == NULL) {
    return MY_RET_INVALID_PARAMS;
  }
  if (strcmp(text, "fi") != 0 && strcmp(text, hebrew) != 0) {
    return MY_RET_FAIL;
  }
  result->allocator = allocator;
  result->glyphs = (my_font_shape_glyph_t*)my_mem_calloc(
      allocator, strcmp(text, "fi") == 0 ? 1u : 2u, sizeof(*result->glyphs));
  if (result->glyphs == NULL) return MY_RET_OOM;
  if (strcmp(text, "fi") == 0) {
    result->count = 1;
    result->glyphs[0].font = font;
    result->glyphs[0].glyph_id = 1;
    result->glyphs[0].cluster = 0;
    result->glyphs[0].advance_x_26_6 = 10 * 64;
    return MY_RET_OK;
  }
  result->count = 2;
  for (i = 0; i < result->count; i++) {
    size_t source = rtl ? result->count - i - 1u : i;
    result->glyphs[i].font = font;
    result->glyphs[i].glyph_id = 1;
    result->glyphs[i].cluster = (uint32_t)(source * 2u);
    result->glyphs[i].advance_x_26_6 = 8 * 64;
  }
  return MY_RET_OK;
}

static const my_font_vtable_t text_area_ligature_vtable = {
    .shape = text_area_ligature_shape};

static int g_result = -999;
static int g_main_clicks;
static int g_dialog_clicks;
static int g_owned_callback_destroy_count;
static int g_owned_callback_calls;
static int g_user_events;
static uint64_t g_timer_test_now;
static int g_timer_test_fires;
static my_window_manager_t* g_paint_destroy_wm;
static bool g_paint_destroy_called;
static int g_paint_destroy_paint_count;
static my_window_manager_t* g_event_destroy_wm;
static bool g_event_destroy_called;
static my_window_manager_t* g_close_listener_destroy_wm;
static bool g_close_listener_destroy_called;

typedef struct lifecycle_context_test_t {
  int callback_count;
  int destroy_count;
  my_window_t* window_owner;
  my_window_manager_t* manager_owner;
} lifecycle_context_test_t;

static void lifecycle_listener_callback(void* context) {
  lifecycle_context_test_t* state = (lifecycle_context_test_t*)context;
  state->callback_count++;
}

static void lifecycle_context_destroy(void* context) {
  lifecycle_context_test_t* state = (lifecycle_context_test_t*)context;
  state->destroy_count++;
}

static void lifecycle_context_destroy_window_owner(void* context) {
  lifecycle_context_test_t* state = (lifecycle_context_test_t*)context;
  state->destroy_count++;
  if (state->window_owner != NULL) {
    my_widget_unref((my_widget_t*)state->window_owner);
    state->window_owner = NULL;
  }
}

static void lifecycle_context_destroy_manager_owner(void* context) {
  lifecycle_context_test_t* state = (lifecycle_context_test_t*)context;
  state->destroy_count++;
  if (state->manager_owner != NULL) {
    my_window_manager_destroy(state->manager_owner);
    state->manager_owner = NULL;
  }
}

static void destroy_manager_from_paint(my_widget_t* widget,
                                       my_vgcanvas_t* canvas) {
  my_window_manager_t* wm = g_paint_destroy_wm;
  (void)widget;
  (void)canvas;
  g_paint_destroy_paint_count++;
  if (g_paint_destroy_called) {
    return;
  }
  g_paint_destroy_called = true;
  g_paint_destroy_wm = NULL;
  if (wm != NULL) {
    my_window_manager_destroy(wm);
  }
}

static const my_widget_vtable_t paint_destroy_vtable = {
    destroy_manager_from_paint, NULL, NULL, NULL};

static my_ret_t destroy_manager_from_event(my_widget_t* widget,
                                           const my_event_t* event) {
  (void)widget;
  if (event != NULL && event->type == MY_EVENT_POINTER_UP) {
    g_event_destroy_called = true;
    if (g_event_destroy_wm != NULL) {
      my_window_manager_destroy(g_event_destroy_wm);
      g_event_destroy_wm = NULL;
    }
  }
  return MY_RET_OK;
}

static const my_widget_vtable_t event_destroy_vtable = {
    NULL, destroy_manager_from_event, NULL, NULL};

static void destroy_manager_from_window_close(void* context) {
  my_window_manager_t* wm = (my_window_manager_t*)context;
  g_close_listener_destroy_called = true;
  if (wm == g_close_listener_destroy_wm) {
    g_close_listener_destroy_wm = NULL;
    my_window_manager_destroy(wm);
  }
}

static void destroy_manager_from_open(my_window_manager_t* wm,
                                      my_window_t* win, void* context) {
  bool* called = (bool*)context;
  (void)win;
  *called = true;
  my_window_manager_destroy(wm);
}

static uint64_t timer_test_now(void* context) {
  (void)context;
  return g_timer_test_now;
}

typedef struct timer_manager_layout_test_t {
  const my_allocator_t* allocator;
  my_timer_now_fn_t now_fn;
  void* now_ctx;
  void* timers;
  void* pending;
  uint32_t next_id;
  bool id_wrapped;
} timer_manager_layout_test_t;

static void timer_test_set_next_id(my_timer_manager_t* manager,
                                   uint32_t next_id) {
  ((timer_manager_layout_test_t*)manager)->next_id = next_id;
}

static my_ret_t timer_test_callback(void* context) {
  (void)context;
  g_timer_test_fires++;
  return MY_RET_FAIL;
}

static my_ret_t timer_repeat_callback(void* context) {
  int* fires = (int*)context;
  (*fires)++;
  return MY_RET_OK;
}

typedef struct timer_pending_oom_test_t {
  my_timer_manager_t* manager;
  text_area_fail_alloc_t* allocation;
  int pending_fires;
  int fires;
  bool add_failed;
} timer_pending_oom_test_t;

static my_ret_t timer_pending_fire_callback(void* context) {
  int* fires = (int*)context;
  (*fires)++;
  return MY_RET_FAIL;
}

static my_ret_t timer_add_during_callback(void* context) {
  timer_pending_oom_test_t* state = (timer_pending_oom_test_t*)context;
  size_t i;
  state->fires++;
  if (state->fires == 1) {
    /* Fill pending's initial capacity before forcing heap growth to fail. */
    for (i = 0u; i < 8u; ++i) {
      if (my_timer_add(state->manager, timer_pending_fire_callback,
                       &state->pending_fires, 1u) == 0u) {
        state->add_failed = true;
      }
    }
    state->allocation->fail_realloc = true;
  }
  return MY_RET_FAIL;
}

typedef struct timer_mutation_test_t {
  my_timer_manager_t* manager;
  uint32_t remove_id;
  uint32_t added_id;
  my_ret_t remove_result;
  int fires;
} timer_mutation_test_t;

static my_ret_t timer_mutation_callback(void* context) {
  timer_mutation_test_t* state = (timer_mutation_test_t*)context;
  state->fires++;
  if (state->fires == 1) {
    state->remove_result =
        my_timer_remove(state->manager, state->remove_id);
    state->added_id = my_timer_add(state->manager, timer_test_callback, NULL,
                                   1u);
  }
  return MY_RET_FAIL;
}

typedef struct timer_cancel_test_t {
  my_timer_manager_t* manager;
  uint32_t cancel_id;
} timer_cancel_test_t;

typedef struct timer_nested_fire_test_t {
  my_timer_manager_t* manager;
  uint32_t outer_id;
  int outer_fires;
  int inner_fires;
  uint32_t nested_fired;
  my_ret_t remove_outer_result;
} timer_nested_fire_test_t;

typedef struct timer_destroy_reentrant_test_t {
  my_timer_manager_t* manager;
  int fires;
} timer_destroy_reentrant_test_t;

typedef struct timer_lease_test_t {
  my_emitter_context_lease_t* lease;
  my_timer_manager_t* manager;
  int callback_count;
  int destroy_count;
  bool invalidate_in_callback;
  bool destroy_manager_in_destructor;
  bool api_reentry_rejected;
  bool probe_api_reentry;
  int sibling_callback_count;
} timer_lease_test_t;

typedef struct emitter_destroy_reentrant_test_t {
  my_emitter_t* emitter;
  int destroy_callback_count;
  int trailing_callback_count;
  int context_destroy_count;
} emitter_destroy_reentrant_test_t;

typedef struct emitter_context_lease_test_t {
  my_emitter_context_lease_t* lease;
  int callback_count;
  int destroy_count;
} emitter_context_lease_test_t;

static my_ret_t timer_lease_callback(void* context);

static my_ret_t timer_lease_sibling_callback(void* context) {
  timer_lease_test_t* state = (timer_lease_test_t*)context;
  state->sibling_callback_count++;
  return MY_RET_FAIL;
}

/* Test-only view of the opaque emitter to exercise the uint32 wrap boundary. */
typedef struct emitter_layout_test_t {
  const my_allocator_t* allocator;
  void* listeners;
  uint32_t next_id;
  int emitting;
  bool destroy_requested;
  bool sweeping;
  bool disposing;
} emitter_layout_test_t;

static void emitter_test_set_next_id(my_emitter_t* emitter, uint32_t next_id) {
  ((emitter_layout_test_t*)emitter)->next_id = next_id;
}

static void emitter_destroy_reentrant_callback(void* context, const char* event,
                                               void* event_data) {
  emitter_destroy_reentrant_test_t* state =
      (emitter_destroy_reentrant_test_t*)context;
  (void)event;
  (void)event_data;
  state->destroy_callback_count++;
  my_emitter_destroy(state->emitter);
}

static void emitter_trailing_callback(void* context, const char* event,
                                      void* event_data) {
  emitter_destroy_reentrant_test_t* state =
      (emitter_destroy_reentrant_test_t*)context;
  (void)event;
  (void)event_data;
  state->trailing_callback_count++;
}

static void emitter_owned_context_destroy(void* context) {
  emitter_destroy_reentrant_test_t* state =
      (emitter_destroy_reentrant_test_t*)context;
  state->context_destroy_count++;
  my_emitter_destroy(state->emitter);
}

static void emitter_owned_context_destroy_plain(void* context) {
  emitter_destroy_reentrant_test_t* state =
      (emitter_destroy_reentrant_test_t*)context;
  state->context_destroy_count++;
}

static void emitter_context_lease_destroy(void* context) {
  emitter_context_lease_test_t* state =
      (emitter_context_lease_test_t*)context;
  state->destroy_count++;
}

static void emitter_context_lease_callback(void* context, const char* event,
                                           void* event_data) {
  emitter_context_lease_test_t* state =
      (emitter_context_lease_test_t*)context;
  (void)event;
  (void)event_data;
  state->callback_count++;
  my_emitter_context_lease_invalidate(state->lease);
}

static void emitter_context_lease_lifecycle_callback(void* context) {
  emitter_context_lease_test_t* state =
      (emitter_context_lease_test_t*)context;
  state->callback_count++;
  my_emitter_context_lease_invalidate(state->lease);
}

static my_ret_t timer_cancel_callback(void* context) {
  timer_cancel_test_t* state = (timer_cancel_test_t*)context;
  (void)my_timer_remove(state->manager, state->cancel_id);
  return MY_RET_FAIL;
}

static my_ret_t timer_nested_inner_callback(void* context) {
  timer_nested_fire_test_t* state = (timer_nested_fire_test_t*)context;
  state->inner_fires++;
  state->remove_outer_result =
      my_timer_remove(state->manager, state->outer_id);
  return MY_RET_FAIL;
}

static my_ret_t timer_nested_outer_callback(void* context) {
  timer_nested_fire_test_t* state = (timer_nested_fire_test_t*)context;
  state->outer_fires++;
  if (state->outer_fires == 1) {
    state->nested_fired = my_timer_manager_fire(state->manager);
  }
  return MY_RET_FAIL;
}

static my_ret_t timer_destroy_reentrant_callback(void* context) {
  timer_destroy_reentrant_test_t* state =
      (timer_destroy_reentrant_test_t*)context;
  state->fires++;
  my_timer_manager_destroy(state->manager);
  return MY_RET_OK;
}

static void timer_lease_destroy(void* context) {
  timer_lease_test_t* state = (timer_lease_test_t*)context;
  state->destroy_count++;
  if (state->probe_api_reentry) {
    state->api_reentry_rejected =
        my_timer_add(state->manager, timer_lease_callback, state, 1u) == 0u &&
        my_timer_remove(state->manager, 1u) == MY_RET_INVALID_PARAMS &&
        my_timer_manager_due_in_ms(state->manager) == UINT32_MAX &&
        my_timer_manager_fire(state->manager) == 0u;
  }
  if (state->destroy_manager_in_destructor) {
    my_timer_manager_destroy(state->manager);
  }
}

static my_ret_t timer_lease_callback(void* context) {
  timer_lease_test_t* state = (timer_lease_test_t*)context;
  state->callback_count++;
  if (state->invalidate_in_callback) {
    my_emitter_context_lease_invalidate(state->lease);
  }
  return MY_RET_OK;
}

TEST(emitter_destroy_from_callback_defers_free_and_stops_emit)
{
  my_emitter_t* emitter = my_emitter_create(NULL);
  emitter_destroy_reentrant_test_t state = {0};

  ASSERT_NOT_NULL(emitter);
  state.emitter = emitter;
  ASSERT_TRUE(my_emitter_on(emitter, "changed",
                            emitter_destroy_reentrant_callback, &state) != 0u);
  ASSERT_TRUE(my_emitter_on(emitter, "changed", emitter_trailing_callback,
                            &state) != 0u);
  ASSERT_EQ(my_emitter_emit(emitter, "changed", NULL), MY_RET_OK);
  ASSERT_EQ(state.destroy_callback_count, 1);
  ASSERT_EQ(state.trailing_callback_count, 0);
}

TEST(emitter_owned_context_releases_once_on_off_and_destroy)
{
  my_emitter_t* emitter = my_emitter_create(NULL);
  emitter_destroy_reentrant_test_t state = {0};
  emitter_destroy_reentrant_test_t reentrant_state = {0};
  uint32_t id;

  ASSERT_NOT_NULL(emitter);
  state.emitter = emitter;
  id = my_emitter_on_owned(emitter, "changed", emitter_trailing_callback,
                           &state, emitter_owned_context_destroy_plain);
  ASSERT_TRUE(id != 0u);
  ASSERT_EQ(my_emitter_off(emitter, id), MY_RET_OK);
  ASSERT_EQ(state.context_destroy_count, 1);
  ASSERT_EQ(my_emitter_off(emitter, id), MY_RET_NOT_FOUND);
  reentrant_state.emitter = emitter;
  id = my_emitter_on_owned(emitter, "changed", emitter_trailing_callback,
                           &reentrant_state, emitter_owned_context_destroy);
  ASSERT_TRUE(id != 0u);
  my_emitter_destroy(emitter);
  ASSERT_EQ(state.context_destroy_count, 1);
  ASSERT_EQ(reentrant_state.context_destroy_count, 1);
}

TEST(emitter_owned_context_off_allows_reentrant_destroy)
{
  my_emitter_t* emitter = my_emitter_create(NULL);
  emitter_destroy_reentrant_test_t state = {0};
  uint32_t id;

  ASSERT_NOT_NULL(emitter);
  state.emitter = emitter;
  id = my_emitter_on_owned(emitter, "changed", emitter_trailing_callback,
                           &state, emitter_owned_context_destroy);
  ASSERT_TRUE(id != 0u);
  ASSERT_EQ(my_emitter_off(emitter, id), MY_RET_OK);
  ASSERT_EQ(state.context_destroy_count, 1);
}

TEST(emitter_context_lease_invalidates_borrowed_callback_safely)
{
  my_emitter_t* emitter = my_emitter_create(NULL);
  emitter_context_lease_test_t state = {0};
  uint32_t id;

  ASSERT_NOT_NULL(emitter);
  state.lease = my_emitter_context_lease_create(
      NULL, &state, emitter_context_lease_destroy);
  ASSERT_NOT_NULL(state.lease);
  id = my_emitter_on_lease(emitter, "changed", emitter_context_lease_callback,
                           state.lease);
  ASSERT_TRUE(id != 0u);
  ASSERT_TRUE(my_emitter_context_lease_is_valid(state.lease));
  my_emitter_context_lease_unref(state.lease);
  ASSERT_EQ(my_emitter_emit(emitter, "changed", NULL), MY_RET_OK);
  ASSERT_EQ(state.callback_count, 1);
  ASSERT_TRUE(!my_emitter_context_lease_is_valid(state.lease));
  ASSERT_EQ(my_emitter_emit(emitter, "changed", NULL), MY_RET_OK);
  ASSERT_EQ(state.callback_count, 1);
  ASSERT_EQ(state.destroy_count, 0);
  ASSERT_EQ(my_emitter_off(emitter, id), MY_RET_OK);
  ASSERT_EQ(state.destroy_count, 1);
  my_emitter_destroy(emitter);
}

TEST(emitter_context_lease_rejects_invalid_registration_without_transfer)
{
  my_emitter_t* emitter = my_emitter_create(NULL);
  emitter_context_lease_test_t state = {0};

  ASSERT_NOT_NULL(emitter);
  state.lease = my_emitter_context_lease_create(
      NULL, &state, emitter_context_lease_destroy);
  ASSERT_NOT_NULL(state.lease);
  my_emitter_context_lease_invalidate(state.lease);
  ASSERT_EQ(my_emitter_on_lease(emitter, "changed", emitter_context_lease_callback,
                                state.lease), 0u);
  ASSERT_EQ(state.destroy_count, 0);
  my_emitter_context_lease_unref(state.lease);
  ASSERT_EQ(state.destroy_count, 1);
  my_emitter_destroy(emitter);
}

TEST(widget_context_lease_forwards_to_widget_emitter)
{
  my_widget_t* widget = my_widget_create(NULL, "lease-widget");
  emitter_context_lease_test_t state = {0};
  uint32_t id;

  ASSERT_NOT_NULL(widget);
  state.lease = my_emitter_context_lease_create(
      NULL, &state, emitter_context_lease_destroy);
  ASSERT_NOT_NULL(state.lease);
  id = my_widget_on_lease(widget, "changed", emitter_context_lease_callback,
                          state.lease);
  ASSERT_TRUE(id != 0u);
  my_emitter_context_lease_unref(state.lease);
  ASSERT_EQ(my_emitter_emit(widget->emitter, "changed", NULL), MY_RET_OK);
  ASSERT_EQ(state.callback_count, 1);
  ASSERT_EQ(my_widget_off(widget, id), MY_RET_OK);
  ASSERT_EQ(state.destroy_count, 1);
  my_widget_unref(widget);
}

TEST(window_close_context_lease_invalidates_before_context_teardown)
{
  my_pal_t* pal = my_pal_dummy_create(NULL);
  my_pal_main_loop_t* loop = my_pal_main_loop_create(pal);
  my_window_manager_t* wm = my_window_manager_create(NULL, pal, loop);
  my_window_t* win = my_window_create(NULL, pal, 100, 80, "lease-close");
  emitter_context_lease_test_t state = {0};
  uint32_t id;

  ASSERT_NOT_NULL(wm);
  ASSERT_NOT_NULL(win);
  state.lease = my_emitter_context_lease_create(
      NULL, &state, emitter_context_lease_destroy);
  ASSERT_NOT_NULL(state.lease);
  id = my_window_add_close_listener_lease(
      win, emitter_context_lease_lifecycle_callback, state.lease);
  ASSERT_TRUE(id != 0u);
  my_emitter_context_lease_unref(state.lease);
  ASSERT_EQ(my_window_manager_open(wm, win), MY_RET_OK);
  ASSERT_EQ(my_window_manager_close(wm, win), MY_RET_OK);
  ASSERT_EQ(state.callback_count, 1);
  ASSERT_EQ(state.destroy_count, 1);
  ASSERT_EQ(my_window_manager_count(wm), 0u);
  my_widget_unref((my_widget_t*)win);
  my_window_manager_destroy(wm);
  my_pal_main_loop_destroy(loop);
  my_pal_destroy(pal);
}

TEST(window_manager_destroy_context_lease_skips_after_invalidation)
{
  my_pal_t* pal = my_pal_dummy_create(NULL);
  my_pal_main_loop_t* loop = my_pal_main_loop_create(pal);
  my_window_manager_t* wm = my_window_manager_create(NULL, pal, loop);
  emitter_context_lease_test_t state = {0};
  emitter_context_lease_test_t active = {0};
  uint32_t id;

  ASSERT_NOT_NULL(wm);
  state.lease = my_emitter_context_lease_create(
      NULL, &state, emitter_context_lease_destroy);
  ASSERT_NOT_NULL(state.lease);
  id = my_window_manager_add_destroy_listener_lease(
      wm, emitter_context_lease_lifecycle_callback, state.lease);
  ASSERT_TRUE(id != 0u);
  active.lease = my_emitter_context_lease_create(
      NULL, &active, emitter_context_lease_destroy);
  ASSERT_NOT_NULL(active.lease);
  id = my_window_manager_add_destroy_listener_lease(
      wm, emitter_context_lease_lifecycle_callback, active.lease);
  ASSERT_TRUE(id != 0u);
  my_emitter_context_lease_invalidate(state.lease);
  my_window_manager_destroy(wm);
  ASSERT_EQ(state.callback_count, 0);
  ASSERT_EQ(active.callback_count, 1);
  ASSERT_EQ(state.destroy_count, 0);
  ASSERT_EQ(active.destroy_count, 0);
  my_emitter_context_lease_unref(state.lease);
  my_emitter_context_lease_unref(active.lease);
  ASSERT_EQ(state.destroy_count, 1);
  ASSERT_EQ(active.destroy_count, 1);
  my_pal_main_loop_destroy(loop);
  my_pal_destroy(pal);
}

TEST(emitter_listener_id_wrap_skips_zero_and_live_ids)
{
  my_emitter_t* emitter = my_emitter_create(NULL);
  uint32_t first;
  uint32_t maximum;
  uint32_t after_wrap;

  ASSERT_NOT_NULL(emitter);
  first = my_emitter_on(emitter, "changed", emitter_trailing_callback, NULL);
  ASSERT_EQ(first, 1u);
  emitter_test_set_next_id(emitter, UINT32_MAX);
  maximum =
      my_emitter_on(emitter, "changed", emitter_trailing_callback, NULL);
  ASSERT_EQ(maximum, UINT32_MAX);
  after_wrap =
      my_emitter_on(emitter, "changed", emitter_trailing_callback, NULL);
  ASSERT_TRUE(after_wrap != 0u);
  ASSERT_TRUE(after_wrap != first);
  ASSERT_TRUE(after_wrap != maximum);
  ASSERT_EQ(my_emitter_off(emitter, first), MY_RET_OK);
  ASSERT_EQ(my_emitter_off(emitter, maximum), MY_RET_OK);
  ASSERT_EQ(my_emitter_off(emitter, after_wrap), MY_RET_OK);
  my_emitter_destroy(emitter);
}
static void on_result(void* ctx, int32_t result) {
  (void)ctx;
  g_result = result;
}

static void owned_callback_destroy(void* ctx) {
  (void)ctx;
  g_owned_callback_destroy_count++;
}

typedef struct menu_reentrant_destroy_context_t {
  my_menu_t* menu;
  my_window_t* window;
  int destroy_count;
} menu_reentrant_destroy_context_t;

static void menu_reentrant_destroy_context(void* ctx) {
  menu_reentrant_destroy_context_t* state =
      (menu_reentrant_destroy_context_t*)ctx;
  state->destroy_count++;
  if (state->menu != NULL) {
    my_menu_destroy(state->menu);
    state->menu = NULL;
  }
  if (state->window != NULL) {
    my_widget_unref((my_widget_t*)state->window);
    state->window = NULL;
  }
}

static void owned_menu_callback(void* ctx, int32_t id) {
  (void)ctx;
  (void)id;
  g_owned_callback_calls++;
}

static void owned_dialog_callback(void* ctx, int32_t result) {
  (void)ctx;
  (void)result;
  g_owned_callback_calls++;
}

typedef struct callback_lease_test_t {
  my_emitter_context_lease_t* lease;
  int callback_count;
  int destroy_count;
  bool invalidate_in_callback;
} callback_lease_test_t;

static void callback_lease_destroy(void* ctx) {
  callback_lease_test_t* state = (callback_lease_test_t*)ctx;
  state->destroy_count++;
}

static void menu_callback_lease_select(void* ctx, int32_t id) {
  callback_lease_test_t* state = (callback_lease_test_t*)ctx;
  (void)id;
  state->callback_count++;
  if (state->invalidate_in_callback) {
    my_emitter_context_lease_invalidate(state->lease);
  }
}

static void dialog_callback_lease_result(void* ctx, int32_t result) {
  callback_lease_test_t* state = (callback_lease_test_t*)ctx;
  (void)result;
  state->callback_count++;
  if (state->invalidate_in_callback) {
    my_emitter_context_lease_invalidate(state->lease);
  }
}

static void on_open_lease_callback(my_window_manager_t* wm, my_window_t* win,
                                    void* ctx) {
  callback_lease_test_t* state = (callback_lease_test_t*)ctx;
  (void)wm;
  (void)win;
  state->callback_count++;
  if (state->invalidate_in_callback) {
    my_emitter_context_lease_invalidate(state->lease);
  }
}

static void count_click(void* ctx, const char* event, void* data) {
  int* count = (int*)ctx;
  (void)event;
  (void)data;
  (*count)++;
}

static void dispatch_button_click(my_window_manager_t* wm, int32_t x,
                                  int32_t y) {
  my_event_t event = my_event_init(MY_EVENT_POINTER_DOWN);
  event.u.pointer.x = x;
  event.u.pointer.y = y;
  event.u.pointer.button = 1;
  (void)my_window_manager_dispatch_surface_event(wm, &event);
  event.type = MY_EVENT_POINTER_UP;
  (void)my_window_manager_dispatch_surface_event(wm, &event);
}

TEST(timer_deadline_saturates_at_clock_limit)
{
  my_timer_manager_t* timers;
  uint32_t id;

  g_timer_test_now = UINT64_MAX - 2u;
  g_timer_test_fires = 0;
  timers = my_timer_manager_create(NULL, timer_test_now, NULL);
  ASSERT_NOT_NULL(timers);
  id = my_timer_add(timers, timer_test_callback, NULL, 10u);
  ASSERT_TRUE(id != 0u);
  ASSERT_EQ(my_timer_manager_due_in_ms(timers), 2u);
  ASSERT_EQ(my_timer_manager_fire(timers), 0u);
  ASSERT_EQ(g_timer_test_fires, 0);
  g_timer_test_now = UINT64_MAX;
  ASSERT_EQ(my_timer_manager_due_in_ms(timers), 0u);
  ASSERT_EQ(my_timer_manager_fire(timers), 1u);
  ASSERT_EQ(g_timer_test_fires, 1);
  ASSERT_EQ(my_timer_manager_due_in_ms(timers), UINT32_MAX);
  my_timer_manager_destroy(timers);
}

TEST(timer_periodic_deadline_at_clock_limit_does_not_busy_loop)
{
  my_timer_manager_t* timers;
  uint32_t id;
  int fires = 0;

  g_timer_test_now = UINT64_MAX - 2u;
  timers = my_timer_manager_create(NULL, timer_test_now, NULL);
  ASSERT_NOT_NULL(timers);
  id = my_timer_add(timers, timer_repeat_callback, &fires, 10u);
  ASSERT_TRUE(id != 0u);
  g_timer_test_now = UINT64_MAX;
  ASSERT_EQ(my_timer_manager_fire(timers), 1u);
  ASSERT_EQ(fires, 1);
  ASSERT_EQ(my_timer_manager_fire(timers), 0u);
  ASSERT_EQ(fires, 1);
  ASSERT_EQ(my_timer_manager_due_in_ms(timers), UINT32_MAX);
  ASSERT_EQ(my_timer_remove(timers, id), MY_RET_OK);
  my_timer_manager_destroy(timers);
}

TEST(timer_rejects_zero_interval)
{
  my_timer_manager_t* timers;

  g_timer_test_now = 100u;
  g_timer_test_fires = 0;
  timers = my_timer_manager_create(NULL, timer_test_now, NULL);
  ASSERT_NOT_NULL(timers);
  ASSERT_EQ(my_timer_add(timers, timer_test_callback, NULL, 0u), 0u);
  ASSERT_EQ(my_timer_manager_due_in_ms(timers), UINT32_MAX);
  ASSERT_EQ(my_timer_manager_fire(timers), 0u);
  ASSERT_EQ(g_timer_test_fires, 0);
  my_timer_manager_destroy(timers);
}

TEST(timer_due_in_saturates_after_clock_rollback)
{
  my_timer_manager_t* timers;
  uint32_t id;

  g_timer_test_now = UINT64_MAX - 100u;
  g_timer_test_fires = 0;
  timers = my_timer_manager_create(NULL, timer_test_now, NULL);
  ASSERT_NOT_NULL(timers);
  id = my_timer_add(timers, timer_test_callback, NULL, 50u);
  ASSERT_TRUE(id != 0u);
  g_timer_test_now = 0u;
  ASSERT_EQ(my_timer_manager_due_in_ms(timers), UINT32_MAX);
  ASSERT_EQ(my_timer_manager_fire(timers), 0u);
  ASSERT_EQ(g_timer_test_fires, 0);
  g_timer_test_now = UINT64_MAX - 50u;
  ASSERT_EQ(my_timer_manager_due_in_ms(timers), 0u);
  ASSERT_EQ(my_timer_manager_fire(timers), 1u);
  ASSERT_EQ(g_timer_test_fires, 1);
  my_timer_manager_destroy(timers);
}

TEST(timer_heap_preserves_safe_callback_mutation)
{
  my_timer_manager_t* timers;
  timer_mutation_test_t state = {0};
  uint32_t first_id;

  g_timer_test_now = 100u;
  g_timer_test_fires = 0;
  timers = my_timer_manager_create(NULL, timer_test_now, NULL);
  ASSERT_NOT_NULL(timers);
  state.manager = timers;
  first_id = my_timer_add(timers, timer_mutation_callback, &state, 10u);
  state.remove_id = my_timer_add(timers, timer_test_callback, NULL, 10u);
  ASSERT_TRUE(first_id != 0u);
  ASSERT_TRUE(state.remove_id != 0u);
  g_timer_test_now = 110u;
  ASSERT_EQ(my_timer_manager_fire(timers), 1u);
  ASSERT_EQ(state.fires, 1);
  ASSERT_EQ(state.remove_result, MY_RET_OK);
  ASSERT_EQ(g_timer_test_fires, 0);
  ASSERT_TRUE(state.added_id != 0u);
  g_timer_test_now = 111u;
  ASSERT_EQ(my_timer_manager_fire(timers), 1u);
  ASSERT_EQ(g_timer_test_fires, 1);
  my_timer_manager_destroy(timers);
}

TEST(timer_heap_removes_inactive_non_root_without_losing_order)
{
  my_timer_manager_t* timers;
  timer_cancel_test_t state = {0};
  uint32_t first_id;
  uint32_t cancel_id;

  g_timer_test_now = 100u;
  g_timer_test_fires = 0;
  timers = my_timer_manager_create(NULL, timer_test_now, NULL);
  ASSERT_NOT_NULL(timers);
  state.manager = timers;
  first_id = my_timer_add(timers, timer_cancel_callback, &state, 10u);
  cancel_id = my_timer_add(timers, timer_test_callback, NULL, 20u);
  state.cancel_id = cancel_id;
  ASSERT_TRUE(first_id != 0u);
  ASSERT_TRUE(cancel_id != 0u);
  ASSERT_TRUE(my_timer_add(timers, timer_test_callback, NULL, 30u) != 0u);
  g_timer_test_now = 110u;
  ASSERT_EQ(my_timer_manager_fire(timers), 1u);
  ASSERT_EQ(g_timer_test_fires, 0);
  g_timer_test_now = 120u;
  ASSERT_EQ(my_timer_manager_fire(timers), 0u);
  g_timer_test_now = 130u;
  ASSERT_EQ(my_timer_manager_fire(timers), 1u);
  ASSERT_EQ(g_timer_test_fires, 1);
  my_timer_manager_destroy(timers);
}

TEST(timer_remove_releases_each_entry_once)
{
  timer_free_guard_t guard = {0};
  my_allocator_t allocator = {&guard, timer_free_guard_alloc,
                              timer_free_guard_calloc, timer_free_guard_realloc,
                              timer_free_guard_free};
  my_timer_manager_t* timers;
  uint32_t first_id;
  uint32_t second_id;

  g_timer_test_now = 100u;
  timers = my_timer_manager_create(&allocator, timer_test_now, NULL);
  ASSERT_NOT_NULL(timers);
  first_id = my_timer_add(timers, timer_test_callback, NULL, 10u);
  second_id = my_timer_add(timers, timer_test_callback, NULL, 20u);
  ASSERT_TRUE(first_id != 0u);
  ASSERT_TRUE(second_id != 0u);
  ASSERT_EQ(my_timer_remove(timers, second_id), MY_RET_OK);
  ASSERT_FALSE(guard.duplicate_free);
  my_timer_manager_destroy(timers);
  ASSERT_FALSE(guard.duplicate_free);
}

TEST(timer_nested_fire_can_remove_outer_current_timer)
{
  my_timer_manager_t* timers;
  timer_nested_fire_test_t state = {0};

  g_timer_test_now = 100u;
  timers = my_timer_manager_create(NULL, timer_test_now, NULL);
  ASSERT_NOT_NULL(timers);
  state.manager = timers;
  state.outer_id = my_timer_add(timers, timer_nested_outer_callback, &state, 10u);
  ASSERT_TRUE(state.outer_id != 0u);
  ASSERT_TRUE(my_timer_add(timers, timer_nested_inner_callback, &state, 10u) !=
              0u);
  g_timer_test_now = 110u;
  ASSERT_EQ(my_timer_manager_fire(timers), 1u);
  ASSERT_EQ(state.outer_fires, 1);
  ASSERT_EQ(state.nested_fired, 1u);
  ASSERT_EQ(state.inner_fires, 1);
  ASSERT_EQ(state.remove_outer_result, MY_RET_OK);
  ASSERT_EQ(my_timer_manager_fire(timers), 0u);
  my_timer_manager_destroy(timers);
}

TEST(timer_manager_destroy_from_callback_defers_free_and_stops_fire)
{
  my_timer_manager_t* timers;
  timer_destroy_reentrant_test_t state = {0};
  g_timer_test_now = 100u;
  timers = my_timer_manager_create(NULL, timer_test_now, NULL);
  ASSERT_NOT_NULL(timers);
  state.manager = timers;
  ASSERT_TRUE(my_timer_add(timers, timer_destroy_reentrant_callback, &state,
                           10u) != 0u);
  ASSERT_TRUE(my_timer_add(timers, timer_test_callback, NULL, 10u) != 0u);
  g_timer_test_now = 110u;
  ASSERT_EQ(my_timer_manager_fire(timers), 1u);
  ASSERT_EQ(state.fires, 1);
}

TEST(timer_lease_skips_invalidated_context_and_releases_once)
{
  my_timer_manager_t* timers;
  timer_lease_test_t state = {0};
  uint32_t id;

  g_timer_test_now = 0u;
  timers = my_timer_manager_create(NULL, timer_test_now, NULL);
  ASSERT_NOT_NULL(timers);
  state.manager = timers;
  state.probe_api_reentry = true;
  state.lease = my_emitter_context_lease_create(NULL, &state,
                                                timer_lease_destroy);
  ASSERT_NOT_NULL(state.lease);
  id = my_timer_add_lease(timers, timer_lease_callback, state.lease, 10u);
  ASSERT_TRUE(id != 0u);
  my_emitter_context_lease_invalidate(state.lease);
  my_emitter_context_lease_unref(state.lease);
  state.lease = NULL;
  g_timer_test_now = 10u;
  ASSERT_EQ(my_timer_manager_due_in_ms(timers), UINT32_MAX);
  ASSERT_EQ(my_timer_manager_fire(timers), 0u);
  ASSERT_EQ(state.callback_count, 0);
  ASSERT_EQ(state.destroy_count, 1);
  ASSERT_TRUE(state.api_reentry_rejected);
  my_timer_manager_destroy(timers);
}

TEST(timer_lease_callback_can_invalidate_and_keep_running)
{
  my_timer_manager_t* timers;
  timer_lease_test_t state = {0};
  uint32_t id;

  g_timer_test_now = 0u;
  timers = my_timer_manager_create(NULL, timer_test_now, NULL);
  ASSERT_NOT_NULL(timers);
  state.invalidate_in_callback = true;
  state.lease = my_emitter_context_lease_create(NULL, &state,
                                                timer_lease_destroy);
  ASSERT_NOT_NULL(state.lease);
  id = my_timer_add_lease(timers, timer_lease_callback, state.lease, 10u);
  ASSERT_TRUE(id != 0u);
  g_timer_test_now = 10u;
  ASSERT_EQ(my_timer_manager_fire(timers), 1u);
  ASSERT_EQ(state.callback_count, 1);
  my_emitter_context_lease_unref(state.lease);
  state.lease = NULL;
  my_timer_manager_destroy(timers);
  ASSERT_EQ(state.destroy_count, 1);
}

TEST(timer_lease_context_destroy_cannot_reenter_manager_dispose)
{
  my_timer_manager_t* timers;
  timer_lease_test_t state = {0};

  g_timer_test_now = 0u;
  timers = my_timer_manager_create(NULL, timer_test_now, NULL);
  ASSERT_NOT_NULL(timers);
  state.manager = timers;
  state.destroy_manager_in_destructor = true;
  state.probe_api_reentry = true;
  state.lease = my_emitter_context_lease_create(NULL, &state,
                                                timer_lease_destroy);
  ASSERT_NOT_NULL(state.lease);
  ASSERT_TRUE(my_timer_add_lease(timers, timer_lease_callback, state.lease,
                                 10u) != 0u);
  ASSERT_TRUE(my_timer_add(timers, timer_lease_sibling_callback, &state,
                           10u) != 0u);
  my_emitter_context_lease_unref(state.lease);
  state.lease = NULL;
  my_timer_manager_destroy(timers);
  ASSERT_EQ(state.destroy_count, 1);
  ASSERT_TRUE(state.api_reentry_rejected);
  ASSERT_EQ(state.sibling_callback_count, 0);
}

TEST(timer_lease_cleanup_destroy_stops_sibling_timers)
{
  my_timer_manager_t* timers;
  timer_lease_test_t state = {0};

  g_timer_test_now = 0u;
  timers = my_timer_manager_create(NULL, timer_test_now, NULL);
  ASSERT_NOT_NULL(timers);
  state.manager = timers;
  state.destroy_manager_in_destructor = true;
  state.lease = my_emitter_context_lease_create(NULL, &state,
                                                timer_lease_destroy);
  ASSERT_NOT_NULL(state.lease);
  ASSERT_TRUE(my_timer_add_lease(timers, timer_lease_callback, state.lease,
                                 10u) != 0u);
  ASSERT_TRUE(my_timer_add(timers, timer_lease_sibling_callback, &state,
                           10u) != 0u);
  my_emitter_context_lease_invalidate(state.lease);
  my_emitter_context_lease_unref(state.lease);
  state.lease = NULL;
  g_timer_test_now = 10u;
  ASSERT_EQ(my_timer_manager_fire(timers), 0u);
  ASSERT_EQ(state.callback_count, 0);
  ASSERT_EQ(state.sibling_callback_count, 0);
  ASSERT_EQ(state.destroy_count, 1);
}

TEST(timer_fire_does_not_allocate_deferred_storage)
{
  text_area_count_alloc_t allocation = {0};
  my_allocator_t allocator = {&allocation, text_area_count_alloc,
                              text_area_count_calloc, text_area_count_realloc,
                              text_area_count_free};
  my_timer_manager_t* timers;
  size_t allocations_before_fire;

  g_timer_test_now = 100u;
  timers = my_timer_manager_create(&allocator, timer_test_now, NULL);
  ASSERT_NOT_NULL(timers);
  ASSERT_TRUE(my_timer_add(timers, timer_test_callback, NULL, 10u) != 0u);
  allocations_before_fire = allocation.alloc_calls;
  g_timer_test_now = 110u;
  ASSERT_EQ(my_timer_manager_fire(timers), 1u);
  ASSERT_EQ(allocation.alloc_calls, allocations_before_fire);
  my_timer_manager_destroy(timers);
}

TEST(timer_pending_heap_oom_preserves_added_timer)
{
  text_area_fail_alloc_t allocation = {false, false};
  my_allocator_t allocator = {&allocation, text_area_fail_alloc,
                              text_area_fail_calloc, text_area_fail_realloc,
                              text_area_fail_free};
  my_timer_manager_t* timers;
  timer_pending_oom_test_t state = {0};
  uint32_t ids[8];
  size_t i;

  g_timer_test_now = 100u;
  timers = my_timer_manager_create(&allocator, timer_test_now, NULL);
  ASSERT_NOT_NULL(timers);
  state.manager = timers;
  state.allocation = &allocation;
  ids[0] = my_timer_add(timers, timer_add_during_callback, &state, 10u);
  ASSERT_TRUE(ids[0] != 0u);
  for (i = 1u; i < sizeof(ids) / sizeof(ids[0]); ++i) {
    ids[i] = my_timer_add(timers, timer_test_callback, NULL, 1000u);
    ASSERT_TRUE(ids[i] != 0u);
  }
  g_timer_test_now = 110u;
  ASSERT_EQ(my_timer_manager_fire(timers), 1u);
  ASSERT_FALSE(state.add_failed);
  ASSERT_EQ(state.pending_fires, 0);
  for (i = 1u; i < sizeof(ids) / sizeof(ids[0]); ++i) {
    ASSERT_EQ(my_timer_remove(timers, ids[i]), MY_RET_OK);
  }
  allocation.fail_realloc = false;
  g_timer_test_now = 111u;
  ASSERT_EQ(my_timer_manager_fire(timers), 1u);
  ASSERT_EQ(state.pending_fires, 1);
  g_timer_test_now = 112u;
  ASSERT_EQ(my_timer_manager_fire(timers), 7u);
  ASSERT_EQ(state.pending_fires, 8);
  for (i = 0u; i < sizeof(ids) / sizeof(ids[0]); ++i) {
    (void)my_timer_remove(timers, ids[i]);
  }
  my_timer_manager_destroy(timers);
}

TEST(timer_index_keeps_pending_removal_and_heap_order)
{
  my_timer_manager_t* timers;
  timer_mutation_test_t state = {0};
  uint32_t ids[3];

  g_timer_test_now = 100u;
  timers = my_timer_manager_create(NULL, timer_test_now, NULL);
  ASSERT_NOT_NULL(timers);
  state.manager = timers;
  ids[0] = my_timer_add(timers, timer_mutation_callback, &state, 10u);
  ids[1] = my_timer_add(timers, timer_test_callback, NULL, 10u);
  ids[2] = my_timer_add(timers, timer_test_callback, NULL, 20u);
  ASSERT_TRUE(ids[0] != 0u && ids[1] != 0u && ids[2] != 0u);
  state.remove_id = ids[1];

  g_timer_test_now = 110u;
  ASSERT_EQ(my_timer_manager_fire(timers), 1u);
  ASSERT_TRUE(state.added_id != 0u);
  ASSERT_EQ(my_timer_remove(timers, state.added_id), MY_RET_OK);
  ASSERT_EQ(my_timer_remove(timers, ids[2]), MY_RET_OK);
  ASSERT_EQ(my_timer_manager_due_in_ms(timers), UINT32_MAX);
  ASSERT_EQ(my_timer_manager_fire(timers), 0u);

  my_timer_manager_destroy(timers);
}

TEST(timer_index_skips_active_ids_after_wrap)
{
  my_timer_manager_t* timers;
  uint32_t first_id;
  uint32_t max_id;
  uint32_t wrapped_id;

  g_timer_test_now = 100u;
  timers = my_timer_manager_create(NULL, timer_test_now, NULL);
  ASSERT_NOT_NULL(timers);
  first_id = my_timer_add(timers, timer_test_callback, NULL, 1000u);
  ASSERT_EQ(first_id, 1u);
  timer_test_set_next_id(timers, UINT32_MAX);
  max_id = my_timer_add(timers, timer_test_callback, NULL, 1000u);
  ASSERT_EQ(max_id, UINT32_MAX);
  wrapped_id = my_timer_add(timers, timer_test_callback, NULL, 1000u);
  ASSERT_EQ(wrapped_id, 2u);
  ASSERT_EQ(my_timer_remove(timers, first_id), MY_RET_OK);
  ASSERT_EQ(my_timer_remove(timers, max_id), MY_RET_OK);
  ASSERT_EQ(my_timer_remove(timers, wrapped_id), MY_RET_OK);
  my_timer_manager_destroy(timers);
}

TEST(animator_delay_saturates_without_early_completion)
{
  my_pal_t* pal = my_pal_dummy_create(NULL);
  my_pal_main_loop_t* loop;
  my_window_manager_t* wm;
  my_widget_t* widget;
  my_rect_t rect;
  uint32_t id;

  ASSERT_NOT_NULL(pal);
  my_pal_dummy_set_now_ms(pal, UINT64_MAX - 100u);
  loop = my_pal_main_loop_create(pal);
  wm = my_window_manager_create(NULL, pal, loop);
  widget = my_widget_create(NULL, "anim-boundary");
  ASSERT_NOT_NULL(loop);
  ASSERT_NOT_NULL(wm);
  ASSERT_NOT_NULL(widget);
  rect = my_rect_init(0, 0, 20, 20);
  ASSERT_EQ(my_widget_set_rect(widget, &rect), MY_RET_OK);
  id = my_animator_animate(wm->anim_mgr, widget, "x", 100.0f, 0.0f,
                           1000u, UINT32_MAX, NULL, 0, false, NULL, NULL,
                           NULL);
  ASSERT_TRUE(id != 0u);

  my_pal_dummy_set_now_ms(pal, UINT64_MAX);
  my_widget_unref(widget);
  widget = NULL;
  (void)my_pal_main_loop_run(loop);
  ASSERT_EQ(my_animator_manager_active_count(wm->anim_mgr), 1u);

  my_window_manager_destroy(wm);
  my_pal_main_loop_destroy(loop);
  my_pal_destroy(pal);
}

TEST(animator_reentrant_stop_defers_record_sweep)
{
  my_pal_t* pal = my_pal_dummy_create(NULL);
  my_pal_main_loop_t* loop;
  my_window_manager_t* wm;
  my_widget_t* widget;
  animator_reentrant_test_t state = {0};
  my_rect_t rect = my_rect_init(0, 0, 20, 20);

  ASSERT_NOT_NULL(pal);
  loop = my_pal_main_loop_create(pal);
  wm = my_window_manager_create(NULL, pal, loop);
  widget = my_widget_create(NULL, "anim-reentrant");
  ASSERT_NOT_NULL(loop);
  ASSERT_NOT_NULL(wm);
  ASSERT_NOT_NULL(widget);
  ASSERT_EQ(my_widget_set_rect(widget, &rect), MY_RET_OK);
  state.manager = wm->anim_mgr;
  ASSERT_TRUE(my_animator_animate(wm->anim_mgr, widget, "x", 100.0f, 0.0f,
                                  100u, 0u, NULL, 0, false,
                                  animator_stop_all_from_update, NULL, &state) !=
              0u);
  ASSERT_TRUE(my_animator_animate(wm->anim_mgr, widget, "y", 100.0f, 0.0f,
                                  100u, 0u, NULL, 0, false,
                                  NULL, NULL, NULL) != 0u);
  my_pal_dummy_set_now_ms(pal, 33u);
  ASSERT_EQ(my_pal_main_loop_run(loop), MY_RET_OK);
  ASSERT_EQ(state.update_calls, 1);
  ASSERT_EQ(my_animator_manager_active_count(wm->anim_mgr), 0u);

  my_widget_unref(widget);
  my_window_manager_destroy(wm);
  my_pal_main_loop_destroy(loop);
  my_pal_destroy(pal);
}

TEST(animator_manager_destroy_from_callback_is_deferred)
{
  my_pal_t* pal = my_pal_dummy_create(NULL);
  my_pal_main_loop_t* loop;
  my_animator_manager_t* manager;
  my_widget_t* widget;
  animator_destroy_test_t state = {0};
  my_rect_t rect = my_rect_init(0, 0, 20, 20);

  ASSERT_NOT_NULL(pal);
  loop = my_pal_main_loop_create(pal);
  manager = my_animator_manager_create(NULL, pal, loop);
  widget = my_widget_create(NULL, "anim-destroy-reentrant");
  ASSERT_NOT_NULL(loop);
  ASSERT_NOT_NULL(manager);
  ASSERT_NOT_NULL(widget);
  ASSERT_EQ(my_widget_set_rect(widget, &rect), MY_RET_OK);
  state.manager = manager;
  ASSERT_TRUE(my_animator_animate(manager, widget, "x", 100.0f, 0.0f, 100u,
                                  0u, NULL, 0, false,
                                  animator_destroy_from_update, NULL, &state) !=
              0u);
  my_pal_dummy_set_now_ms(pal, 33u);
  ASSERT_EQ(my_pal_main_loop_run(loop), MY_RET_OK);
  ASSERT_EQ(state.update_calls, 1);

  my_widget_unref(widget);
  my_pal_main_loop_destroy(loop);
  my_pal_destroy(pal);
}

TEST(undo_manager_destroy_keeps_shared_edit_safe)
{
  my_undo_manager_t* manager = my_undo_manager_create(NULL, 8u);
  my_widget_t* edit = my_edit_create(NULL);
  my_widget_t* area = my_text_area_create(NULL);

  ASSERT_NOT_NULL(manager);
  ASSERT_NOT_NULL(edit);
  ASSERT_NOT_NULL(area);
  ASSERT_EQ(my_edit_set_undo_shared(edit, manager), MY_RET_OK);
  ASSERT_EQ(my_text_area_set_undo_shared(area, manager), MY_RET_OK);
  my_undo_manager_destroy(manager);
  my_undo_manager_destroy(manager);
  ASSERT_EQ(my_undo_manager_record_insert(manager, edit, 0u, "x", 1u),
            MY_RET_INVALID_PARAMS);
  ASSERT_FALSE(my_undo_manager_can_undo(manager));
  ASSERT_EQ(my_edit_set_undo_shared(edit, NULL), MY_RET_OK);
  ASSERT_EQ(my_text_area_set_undo_shared(area, NULL), MY_RET_OK);
  my_widget_unref(edit);
  my_widget_unref(area);
}

TEST(undo_manager_window_reference_survives_owner_destroy)
{
  my_pal_t* pal = my_pal_dummy_create(NULL);
  my_pal_main_loop_t* loop;
  my_window_manager_t* wm;
  my_window_t* win;
  my_undo_manager_t* manager;
  my_widget_t* edit;

  ASSERT_NOT_NULL(pal);
  loop = my_pal_main_loop_create(pal);
  wm = my_window_manager_create(NULL, pal, loop);
  win = my_window_create(NULL, pal, 160, 100, "undo-window");
  manager = my_undo_manager_create(NULL, 8u);
  edit = my_edit_create(NULL);
  ASSERT_NOT_NULL(loop);
  ASSERT_NOT_NULL(wm);
  ASSERT_NOT_NULL(win);
  ASSERT_NOT_NULL(manager);
  ASSERT_NOT_NULL(edit);
  my_window_set_undo_manager(win, manager);
  ASSERT_EQ(my_edit_set_undo_shared(edit, manager), MY_RET_OK);
  ASSERT_EQ(my_widget_add_child(my_window_widget(win), edit), MY_RET_OK);
  my_undo_manager_destroy(manager);
  my_widget_unref(edit);
  my_widget_unref((my_widget_t*)win);
  my_window_manager_destroy(wm);
  my_pal_main_loop_destroy(loop);
  my_pal_destroy(pal);
}

TEST(edit_blink_timer_does_not_keep_dangling_widget_context)
{
  my_pal_t* pal = my_pal_dummy_create(NULL);
  my_pal_main_loop_t* loop;
  my_window_manager_t* wm;
  my_window_t* win;
  my_widget_t* edit;

  ASSERT_NOT_NULL(pal);
  loop = my_pal_main_loop_create(pal);
  wm = my_window_manager_create(NULL, pal, loop);
  win = my_window_create(NULL, pal, 160, 100, "edit-timer");
  edit = my_edit_create(NULL);
  ASSERT_NOT_NULL(loop);
  ASSERT_NOT_NULL(wm);
  ASSERT_NOT_NULL(win);
  ASSERT_NOT_NULL(edit);
  ASSERT_EQ(my_widget_add_child(my_window_widget(win), edit), MY_RET_OK);
  ASSERT_EQ(my_window_manager_open(wm, win), MY_RET_OK);
  ASSERT_TRUE(my_emitter_emit(edit->emitter, "focus", NULL) == MY_RET_OK);
  ASSERT_TRUE(((my_edit_t*)edit)->blink_timer_id != 0u);
  ASSERT_EQ(my_widget_remove_child(my_window_widget(win), edit), MY_RET_OK);
  my_widget_unref(edit);
  my_pal_dummy_set_now_ms(pal, 500u);
  ASSERT_EQ(my_pal_main_loop_run(loop), MY_RET_OK);

  ASSERT_EQ(my_window_manager_close(wm, win), MY_RET_OK);
  my_widget_unref((my_widget_t*)win);
  my_window_manager_destroy(wm);
  my_pal_main_loop_destroy(loop);
  my_pal_destroy(pal);
}

TEST(window_manager_destroy_from_paint_is_deferred)
{
  my_pal_t* pal = my_pal_dummy_create(NULL);
  my_pal_main_loop_t* loop = my_pal_main_loop_create(pal);
  my_window_manager_t* wm = my_window_manager_create(NULL, pal, loop);
  my_window_t* win = my_window_create(NULL, pal, 160, 100, "paint-destroy");
  my_window_t* second = my_window_create(NULL, pal, 160, 100, "paint-destroy-2");
  my_widget_t* child = my_widget_create(NULL, "paint-destroy-child");

  ASSERT_NOT_NULL(pal);
  ASSERT_NOT_NULL(loop);
  ASSERT_NOT_NULL(wm);
  ASSERT_NOT_NULL(win);
  ASSERT_NOT_NULL(second);
  ASSERT_NOT_NULL(child);
  ASSERT_EQ(my_widget_subclass_init(child, &paint_destroy_vtable), MY_RET_OK);
  ASSERT_EQ(my_widget_add_child(my_window_widget(win), child), MY_RET_OK);
  my_widget_unref(child);
  child = my_widget_create(NULL, "paint-destroy-child-2");
  ASSERT_NOT_NULL(child);
  ASSERT_EQ(my_widget_subclass_init(child, &paint_destroy_vtable), MY_RET_OK);
  ASSERT_EQ(my_widget_add_child(my_window_widget(second), child), MY_RET_OK);
  my_widget_unref(child);
  ASSERT_EQ(my_window_manager_open(wm, win), MY_RET_OK);
  ASSERT_EQ(my_window_manager_open(wm, second), MY_RET_OK);
  g_paint_destroy_wm = wm;
  g_paint_destroy_called = false;
  g_paint_destroy_paint_count = 0;
  my_widget_invalidate(my_window_widget(win), NULL);
  my_pal_dummy_set_now_ms(pal, 33u);
  ASSERT_EQ(my_pal_main_loop_run(loop), MY_RET_OK);
  ASSERT_TRUE(g_paint_destroy_called);
  ASSERT_TRUE(g_paint_destroy_wm == NULL);
  ASSERT_EQ(g_paint_destroy_paint_count, 1);

  my_pal_main_loop_destroy(loop);
  my_widget_unref((my_widget_t*)win);
  my_widget_unref((my_widget_t*)second);
  my_pal_destroy(pal);
}

TEST(window_manager_destroy_from_event_is_deferred)
{
  my_pal_t* pal = my_pal_dummy_create(NULL);
  my_pal_main_loop_t* loop = my_pal_main_loop_create(pal);
  my_window_manager_t* wm = my_window_manager_create(NULL, pal, loop);
  my_window_t* win = my_window_create(NULL, pal, 160, 100, "event-destroy");
  my_widget_t* child = my_widget_create(NULL, "event-destroy-child");
  my_event_t event = my_event_init(MY_EVENT_POINTER_UP);

  ASSERT_NOT_NULL(pal);
  ASSERT_NOT_NULL(loop);
  ASSERT_NOT_NULL(wm);
  ASSERT_NOT_NULL(win);
  ASSERT_NOT_NULL(child);
  ASSERT_EQ(my_widget_subclass_init(child, &event_destroy_vtable), MY_RET_OK);
  ASSERT_EQ(my_widget_set_rect(child, &(my_rect_t){0, 0, 80, 40}), MY_RET_OK);
  ASSERT_EQ(my_widget_add_child(my_window_widget(win), child), MY_RET_OK);
  my_widget_unref(child);
  ASSERT_EQ(my_window_manager_open(wm, win), MY_RET_OK);
  g_event_destroy_wm = wm;
  g_event_destroy_called = false;
  event.u.pointer.x = 10;
  event.u.pointer.y = 10;
  ASSERT_EQ(my_window_manager_dispatch_surface_event(wm, &event), MY_RET_OK);
  ASSERT_TRUE(g_event_destroy_called);
  ASSERT_TRUE(g_event_destroy_wm == NULL);

  my_pal_main_loop_destroy(loop);
  my_widget_unref((my_widget_t*)win);
  my_pal_destroy(pal);
}

TEST(window_manager_destroy_from_close_listener_is_deferred)
{
  my_pal_t* pal = my_pal_dummy_create(NULL);
  my_pal_main_loop_t* loop = my_pal_main_loop_create(pal);
  my_window_manager_t* wm = my_window_manager_create(NULL, pal, loop);
  my_window_t* win = my_window_create(NULL, pal, 160, 100, "close-destroy");

  ASSERT_NOT_NULL(pal);
  ASSERT_NOT_NULL(loop);
  ASSERT_NOT_NULL(wm);
  ASSERT_NOT_NULL(win);
  ASSERT_EQ(my_window_add_close_listener(
                win, destroy_manager_from_window_close, wm),
            1u);
  ASSERT_EQ(my_window_manager_open(wm, win), MY_RET_OK);
  g_close_listener_destroy_wm = wm;
  g_close_listener_destroy_called = false;
  ASSERT_EQ(my_window_manager_close(wm, win), MY_RET_OK);
  ASSERT_TRUE(g_close_listener_destroy_called);
  ASSERT_TRUE(g_close_listener_destroy_wm == NULL);

  my_pal_main_loop_destroy(loop);
  my_widget_unref((my_widget_t*)win);
  my_pal_destroy(pal);
}

TEST(window_close_owned_listener_releases_once_on_remove_and_close)
{
  my_pal_t* pal = my_pal_dummy_create(NULL);
  my_pal_main_loop_t* loop = my_pal_main_loop_create(pal);
  my_window_manager_t* wm = my_window_manager_create(NULL, pal, loop);
  my_window_t* win = my_window_create(NULL, pal, 160, 100, "owned-close");
  lifecycle_context_test_t removed = {0};
  lifecycle_context_test_t closed = {0};
  uint32_t id;

  ASSERT_NOT_NULL(pal);
  ASSERT_NOT_NULL(loop);
  ASSERT_NOT_NULL(wm);
  ASSERT_NOT_NULL(win);
  id = my_window_add_close_listener_owned(
      win, lifecycle_listener_callback, &removed, lifecycle_context_destroy);
  ASSERT_TRUE(id != 0u);
  ASSERT_EQ(my_window_remove_close_listener(win, id), MY_RET_OK);
  ASSERT_EQ(removed.destroy_count, 1);
  ASSERT_EQ(my_window_add_close_listener_owned(
                win, lifecycle_listener_callback, &closed,
                lifecycle_context_destroy),
            2u);
  ASSERT_EQ(my_window_manager_open(wm, win), MY_RET_OK);
  ASSERT_EQ(my_window_manager_close(wm, win), MY_RET_OK);
  ASSERT_EQ(closed.callback_count, 1);
  ASSERT_EQ(closed.destroy_count, 1);

  my_window_manager_destroy(wm);
  my_pal_main_loop_destroy(loop);
  my_widget_unref((my_widget_t*)win);
  my_pal_destroy(pal);
}

TEST(window_manager_owned_destroy_listener_releases_once)
{
  my_pal_t* pal = my_pal_dummy_create(NULL);
  my_pal_main_loop_t* loop = my_pal_main_loop_create(pal);
  my_window_manager_t* wm = my_window_manager_create(NULL, pal, loop);
  lifecycle_context_test_t removed = {0};
  lifecycle_context_test_t destroyed = {0};
  uint32_t id;

  ASSERT_NOT_NULL(pal);
  ASSERT_NOT_NULL(loop);
  ASSERT_NOT_NULL(wm);
  id = my_window_manager_add_destroy_listener_owned(
      wm, lifecycle_listener_callback, &removed, lifecycle_context_destroy);
  ASSERT_TRUE(id != 0u);
  ASSERT_EQ(my_window_manager_remove_destroy_listener(wm, id), MY_RET_OK);
  ASSERT_EQ(removed.destroy_count, 1);
  ASSERT_EQ(my_window_manager_add_destroy_listener_owned(
                wm, lifecycle_listener_callback, &destroyed,
                lifecycle_context_destroy),
            2u);
  my_window_manager_destroy(wm);
  ASSERT_EQ(destroyed.callback_count, 1);
  ASSERT_EQ(destroyed.destroy_count, 1);
  my_pal_main_loop_destroy(loop);
  my_pal_destroy(pal);
}

TEST(owned_listener_destructor_can_destroy_owner_during_remove)
{
  my_pal_t* pal = my_pal_dummy_create(NULL);
  my_pal_main_loop_t* loop = my_pal_main_loop_create(pal);
  my_window_manager_t* wm = my_window_manager_create(NULL, pal, loop);
  my_window_t* win = my_window_create(NULL, pal, 160, 100, "owner-remove");
  lifecycle_context_test_t window_state = {0};
  lifecycle_context_test_t manager_state = {0};
  uint32_t window_id;
  uint32_t manager_id;

  ASSERT_NOT_NULL(pal);
  ASSERT_NOT_NULL(loop);
  ASSERT_NOT_NULL(wm);
  ASSERT_NOT_NULL(win);
  window_state.window_owner = win;
  window_id = my_window_add_close_listener_owned(
      win, lifecycle_listener_callback, &window_state,
      lifecycle_context_destroy_window_owner);
  ASSERT_TRUE(window_id != 0u);
  ASSERT_EQ(my_window_remove_close_listener(win, window_id), MY_RET_OK);
  ASSERT_EQ(window_state.destroy_count, 1);
  manager_state.manager_owner = wm;
  manager_id = my_window_manager_add_destroy_listener_owned(
      wm, lifecycle_listener_callback, &manager_state,
      lifecycle_context_destroy_manager_owner);
  ASSERT_TRUE(manager_id != 0u);
  ASSERT_EQ(my_window_manager_remove_destroy_listener(wm, manager_id),
            MY_RET_OK);
  ASSERT_EQ(manager_state.destroy_count, 1);
  my_pal_main_loop_destroy(loop);
  my_pal_destroy(pal);
}

TEST(window_manager_destroy_from_open_callback_is_deferred)
{
  my_pal_t* pal = my_pal_dummy_create(NULL);
  my_pal_main_loop_t* loop = my_pal_main_loop_create(pal);
  my_window_manager_t* wm = my_window_manager_create(NULL, pal, loop);
  my_window_t* win = my_window_create(NULL, pal, 160, 100, "open-destroy");
  bool called = false;

  ASSERT_NOT_NULL(pal);
  ASSERT_NOT_NULL(loop);
  ASSERT_NOT_NULL(wm);
  ASSERT_NOT_NULL(win);
  my_window_manager_set_on_open(wm, destroy_manager_from_open, &called);
  ASSERT_EQ(my_window_manager_open(wm, win), MY_RET_OK);
  ASSERT_TRUE(called);

  my_pal_main_loop_destroy(loop);
  my_widget_unref((my_widget_t*)win);
  my_pal_destroy(pal);
}

TEST(edit_async_paste_changed_listener_can_remove_self)
{
  my_pal_t* pal = my_pal_dummy_create(NULL);
  my_pal_main_loop_t* loop = my_pal_main_loop_create(pal);
  my_window_manager_t* wm = my_window_manager_create(NULL, pal, loop);
  my_window_t* win = my_window_create(NULL, pal, 160, 100, "edit-paste");
  my_widget_t* edit = my_edit_create(NULL);
  paste_self_remove_t state = {my_window_widget(win), edit, false};
  my_event_t event = my_event_init(MY_EVENT_KEY_DOWN);

  ASSERT_NOT_NULL(pal);
  ASSERT_NOT_NULL(loop);
  ASSERT_NOT_NULL(wm);
  ASSERT_NOT_NULL(win);
  ASSERT_NOT_NULL(edit);
  ASSERT_EQ(my_widget_add_child(my_window_widget(win), edit), MY_RET_OK);
  ASSERT_TRUE(my_widget_on(edit, "changed", remove_paste_widget_on_changed,
                           &state) != 0u);
  ASSERT_EQ(my_window_manager_open(wm, win), MY_RET_OK);
  ASSERT_EQ(my_pal_clipboard_set_text(pal, "async"), MY_RET_OK);
  my_pal_dummy_set_clipboard_pending_reads(pal, 1u);
  event.u.key.key = 'v';
  event.u.key.modifiers = MY_KEYMOD_CTRL;
  my_event_dispatcher_set_focus(&win->dispatcher, edit);
  ASSERT_EQ(my_window_manager_dispatch_surface_event(wm, &event), MY_RET_OK);
  ASSERT_TRUE(((my_edit_t*)edit)->paste_timer_id != 0u);
  my_pal_dummy_set_now_ms(pal, 10u);
  ASSERT_EQ(my_pal_main_loop_run(loop), MY_RET_OK);
  ASSERT_TRUE(state.called);
  ASSERT_TRUE(state.widget == NULL);

  my_window_manager_destroy(wm);
  my_pal_main_loop_destroy(loop);
  my_widget_unref((my_widget_t*)win);
  my_pal_destroy(pal);
}

TEST(text_area_async_paste_changed_listener_can_remove_self)
{
  my_pal_t* pal = my_pal_dummy_create(NULL);
  my_pal_main_loop_t* loop = my_pal_main_loop_create(pal);
  my_window_manager_t* wm = my_window_manager_create(NULL, pal, loop);
  my_window_t* win = my_window_create(NULL, pal, 160, 100, "text-area-paste");
  my_widget_t* area = my_text_area_create(NULL);
  paste_self_remove_t state = {my_window_widget(win), area, false};
  my_event_t event = my_event_init(MY_EVENT_KEY_DOWN);

  ASSERT_NOT_NULL(pal);
  ASSERT_NOT_NULL(loop);
  ASSERT_NOT_NULL(wm);
  ASSERT_NOT_NULL(win);
  ASSERT_NOT_NULL(area);
  ASSERT_EQ(my_widget_add_child(my_window_widget(win), area), MY_RET_OK);
  ASSERT_TRUE(my_widget_on(area, "changed", remove_paste_widget_on_changed,
                           &state) != 0u);
  ASSERT_EQ(my_window_manager_open(wm, win), MY_RET_OK);
  ASSERT_EQ(my_pal_clipboard_set_text(pal, "async"), MY_RET_OK);
  my_pal_dummy_set_clipboard_pending_reads(pal, 1u);
  event.u.key.key = 'v';
  event.u.key.modifiers = MY_KEYMOD_CTRL;
  my_event_dispatcher_set_focus(&win->dispatcher, area);
  ASSERT_EQ(my_window_manager_dispatch_surface_event(wm, &event), MY_RET_OK);
  ASSERT_TRUE(((my_text_area_t*)area)->paste_timer_id != 0u);
  my_pal_dummy_set_now_ms(pal, 10u);
  ASSERT_EQ(my_pal_main_loop_run(loop), MY_RET_OK);
  ASSERT_TRUE(state.called);
  ASSERT_TRUE(state.widget == NULL);

  my_window_manager_destroy(wm);
  my_pal_main_loop_destroy(loop);
  my_widget_unref((my_widget_t*)win);
  my_pal_destroy(pal);
}

TEST(edit_typed_changed_listener_can_remove_self)
{
  my_widget_t* parent = my_widget_create(NULL, "edit-parent");
  my_widget_t* edit = my_edit_create(NULL);
  my_edit_t* edit_state = (my_edit_t*)edit;
  my_event_t event = my_event_init(MY_EVENT_KEY_DOWN);
  paste_self_remove_t state = {parent, edit, false};

  ASSERT_NOT_NULL(parent);
  ASSERT_NOT_NULL(edit);
  ASSERT_EQ(my_widget_add_child(parent, edit), MY_RET_OK);
  ASSERT_TRUE(my_widget_on(edit, "changed", remove_paste_widget_on_changed,
                           &state) != 0u);
  edit_state->focused = true;
  event.u.key.key = 'x';
  ASSERT_EQ(edit->vtable->on_event(edit, &event), MY_RET_OK);
  ASSERT_TRUE(state.called);
  ASSERT_TRUE(state.widget == NULL);

  my_widget_unref(parent);
}

TEST(text_area_typed_changed_listener_can_remove_self)
{
  my_widget_t* parent = my_widget_create(NULL, "text-area-parent");
  my_widget_t* area = my_text_area_create(NULL);
  my_text_area_t* area_state = (my_text_area_t*)area;
  my_event_t event = my_event_init(MY_EVENT_KEY_DOWN);
  paste_self_remove_t state = {parent, area, false};

  ASSERT_NOT_NULL(parent);
  ASSERT_NOT_NULL(area);
  ASSERT_EQ(my_widget_add_child(parent, area), MY_RET_OK);
  ASSERT_TRUE(my_widget_on(area, "changed", remove_paste_widget_on_changed,
                           &state) != 0u);
  area_state->focused = true;
  event.u.key.key = 'x';
  ASSERT_EQ(area->vtable->on_event(area, &event), MY_RET_OK);
  ASSERT_TRUE(state.called);
  ASSERT_TRUE(state.widget == NULL);

  my_widget_unref(parent);
}

TEST(button_click_listener_can_remove_self_before_post_emit_invalidate)
{
  my_widget_t* parent = my_widget_create(NULL, "button-parent");
  my_widget_t* button = my_button_create(NULL, "button");
  my_event_t event = my_event_init(MY_EVENT_KEY_DOWN);
  paste_self_remove_t state = {parent, button, false};

  ASSERT_NOT_NULL(parent);
  ASSERT_NOT_NULL(button);
  ASSERT_EQ(my_widget_add_child(parent, button), MY_RET_OK);
  ASSERT_TRUE(my_widget_on(button, "click", remove_paste_widget_on_changed,
                           &state) != 0u);
  event.u.key.key = MY_KEY_RETURN;
  ASSERT_EQ(button->vtable->on_event(button, &event), MY_RET_OK);
  event.type = MY_EVENT_KEY_UP;
  ASSERT_EQ(button->vtable->on_event(button, &event), MY_RET_OK);
  ASSERT_TRUE(state.called);
  ASSERT_TRUE(state.widget == NULL);

  my_widget_unref(parent);
}

TEST(node_view_changed_listener_can_remove_self)
{
  my_widget_t* parent = my_widget_create(NULL, "node-parent");
  my_widget_t* view = my_node_view_create(NULL);
  my_widget_t* out_node;
  my_widget_t* in_node;
  paste_self_remove_t state = {parent, view, false};

  ASSERT_NOT_NULL(parent);
  ASSERT_NOT_NULL(view);
  ASSERT_EQ(my_widget_add_child(parent, view), MY_RET_OK);
  out_node = my_node_view_add_node(view, "out", "Out", NULL, 0, 0,
                                   80, 60);
  in_node = my_node_view_add_node(view, "in", "In", NULL, 100, 0, 80, 60);
  ASSERT_NOT_NULL(out_node);
  ASSERT_NOT_NULL(in_node);
  ASSERT_EQ(my_node_add_socket(out_node, MY_SOCKET_OUT, "out", 0u),
            MY_RET_OK);
  ASSERT_EQ(my_node_add_socket(in_node, MY_SOCKET_IN, "in", 0u), MY_RET_OK);
  ASSERT_TRUE(my_widget_on(view, "changed", remove_paste_widget_on_changed,
                           &state) != 0u);
  ASSERT_EQ(my_node_view_connect(view, out_node, 0u, in_node, 0u), MY_RET_OK);
  ASSERT_TRUE(state.called);
  ASSERT_TRUE(state.widget == NULL);

  my_widget_unref(parent);
}

TEST(checkbox_changed_listener_can_remove_self)
{
  my_widget_t* parent = my_widget_create(NULL, "checkbox-parent");
  my_widget_t* checkbox = my_checkbox_create(NULL, "check");
  my_event_t event = my_event_init(MY_EVENT_POINTER_DOWN);
  paste_self_remove_t state = {parent, checkbox, false};

  ASSERT_NOT_NULL(parent);
  ASSERT_NOT_NULL(checkbox);
  ASSERT_EQ(my_widget_add_child(parent, checkbox), MY_RET_OK);
  ASSERT_TRUE(my_widget_on(checkbox, "changed", remove_paste_widget_on_changed,
                           &state) != 0u);
  ASSERT_EQ(checkbox->vtable->on_event(checkbox, &event), MY_RET_OK);
  event.type = MY_EVENT_POINTER_UP;
  ASSERT_EQ(checkbox->vtable->on_event(checkbox, &event), MY_RET_OK);
  ASSERT_TRUE(state.called);
  ASSERT_TRUE(state.widget == NULL);

  my_widget_unref(parent);
}

TEST(slider_changed_listener_can_remove_self)
{
  my_widget_t* parent = my_widget_create(NULL, "slider-parent");
  my_widget_t* slider = my_slider_create(NULL);
  my_event_t event = my_event_init(MY_EVENT_POINTER_DOWN);
  paste_self_remove_t state = {parent, slider, false};

  ASSERT_NOT_NULL(parent);
  ASSERT_NOT_NULL(slider);
  ASSERT_EQ(my_widget_set_rect(slider, &(my_rect_t){0, 0, 100, 20}),
            MY_RET_OK);
  ASSERT_EQ(my_widget_add_child(parent, slider), MY_RET_OK);
  ASSERT_TRUE(my_widget_on(slider, "changed", remove_paste_widget_on_changed,
                           &state) != 0u);
  event.u.pointer.x = 80;
  ASSERT_EQ(slider->vtable->on_event(slider, &event), MY_RET_OK);
  ASSERT_TRUE(state.called);
  ASSERT_TRUE(state.widget == NULL);

  my_widget_unref(parent);
}

TEST(scroll_bar_changed_listener_can_remove_self)
{
  my_widget_t* parent = my_widget_create(NULL, "scroll-parent");
  my_widget_t* bar = my_scroll_bar_create(NULL);
  my_event_t event = my_event_init(MY_EVENT_POINTER_DOWN);
  paste_self_remove_t state = {parent, bar, false};

  ASSERT_NOT_NULL(parent);
  ASSERT_NOT_NULL(bar);
  ASSERT_EQ(my_widget_set_rect(bar, &(my_rect_t){0, 0, 20, 100}), MY_RET_OK);
  ASSERT_EQ(my_widget_add_child(parent, bar), MY_RET_OK);
  ASSERT_TRUE(my_widget_on(bar, "changed", remove_paste_widget_on_changed,
                           &state) != 0u);
  event.u.pointer.y = 90;
  ASSERT_EQ(bar->vtable->on_event(bar, &event), MY_RET_OK);
  ASSERT_TRUE(state.called);
  ASSERT_TRUE(state.widget == NULL);

  my_widget_unref(parent);
}

static void count_user(void* ctx, const char* event, void* data) {
  int* marker = (int*)data;
  (void)event;
  ASSERT_TRUE(marker == &g_user_events);
  (*(int*)ctx)++;
}

static void close_window_from_user_event(void* ctx, const char* event,
                                         void* data) {
  my_window_manager_t* wm = (my_window_manager_t*)ctx;
  (void)event;
  (void)data;
  (void)my_window_manager_close(wm, my_window_manager_top(wm));
}

static void pump(my_pal_t* pal, my_pal_main_loop_t* loop) {
  my_pal_dummy_set_now_ms(pal, 10000);
  (void)my_pal_main_loop_run(loop);
}

typedef struct bubbling_mutation_ctx_t {
  my_widget_t *root;
  my_widget_t *removed_parent;
  my_widget_t *removed_leaf;
  int parent_events;
} bubbling_mutation_ctx_t;

static my_ret_t mutation_leaf_event(my_widget_t *widget,
                                    const my_event_t *event) {
  bubbling_mutation_ctx_t *ctx =
      (bubbling_mutation_ctx_t *)my_widget_get_user_data(widget);
  (void)event;
  (void)my_widget_remove_child(ctx->root, ctx->removed_parent);
  return MY_RET_FAIL;
}

static my_ret_t detached_parent_event(my_widget_t *widget,
                                      const my_event_t *event) {
  bubbling_mutation_ctx_t *ctx =
      (bubbling_mutation_ctx_t *)my_widget_get_user_data(widget);
  (void)event;
  ctx->parent_events++;
  return MY_RET_OK;
}

static my_ret_t self_removing_leaf_event(my_widget_t *widget,
                                         const my_event_t *event) {
  (void)event;
  (void)my_widget_remove_child(widget->parent, widget);
  return MY_RET_FAIL;
}

static const my_widget_vtable_t s_mutation_leaf_vtable = {
    NULL, mutation_leaf_event, NULL, NULL};
static const my_widget_vtable_t s_self_removing_leaf_vtable = {
    NULL, self_removing_leaf_event, NULL, NULL};
static const my_widget_vtable_t s_detached_parent_vtable = {
    NULL, detached_parent_event, NULL, NULL};

typedef struct surface_focus_ctx_t {
  int key_down;
} surface_focus_ctx_t;

static my_ret_t surface_focus_event(my_widget_t *widget,
                                    const my_event_t *event) {
  surface_focus_ctx_t *ctx =
      (surface_focus_ctx_t *)my_widget_get_user_data(widget);
  if (event->type == MY_EVENT_KEY_DOWN) {
    ctx->key_down++;
    return MY_RET_OK;
  }
  return MY_RET_FAIL;
}

static const my_widget_vtable_t s_surface_focus_vtable = {
    NULL, surface_focus_event, NULL, NULL};

typedef struct paint_stack_mutation_ctx_t {
  my_window_manager_t *wm;
  my_window_t *window;
  int paint_count;
} paint_stack_mutation_ctx_t;

static void close_window_on_paint(my_widget_t *widget, my_vgcanvas_t *vg) {
  paint_stack_mutation_ctx_t *ctx =
      (paint_stack_mutation_ctx_t *)my_widget_get_user_data(widget);
  (void)vg;
  ctx->paint_count++;
  (void)my_window_manager_close(ctx->wm, ctx->window);
}

static void count_paint(my_widget_t *widget, my_vgcanvas_t *vg) {
  paint_stack_mutation_ctx_t *ctx =
      (paint_stack_mutation_ctx_t *)my_widget_get_user_data(widget);
  (void)vg;
  ctx->paint_count++;
}

static const my_widget_vtable_t s_close_window_on_paint_vtable = {
    close_window_on_paint, NULL, NULL, NULL};
static const my_widget_vtable_t s_count_paint_vtable = {count_paint, NULL,
                                                         NULL, NULL};

TEST(injected_canvas_inherits_window_scale)
{
  my_pal_t* pal = my_pal_dummy_create(NULL);
  my_window_t* win;
  my_vgcanvas_t* canvas;
  my_lcd_t* lcd;
  uint8_t* pixels;
  uint32_t stride;

  ASSERT_NOT_NULL(pal);
  my_pal_dummy_set_scale_factor(pal, 2.0f);
  win = my_window_create(NULL, pal, 100, 50, "hidpi");
  ASSERT_NOT_NULL(win);
  lcd = my_pal_window_get_lcd(win->pal_window);
  ASSERT_NOT_NULL(lcd);
  canvas = my_vgcanvas_soft_create(NULL, lcd);
  ASSERT_NOT_NULL(canvas);

  my_window_set_vgcanvas(win, canvas);
  ASSERT_EQ(my_vgcanvas_begin_frame(canvas, NULL), MY_RET_OK);
  ASSERT_EQ(my_vgcanvas_set_fill_color(canvas, my_color_rgb(255, 0, 0)),
            MY_RET_OK);
  ASSERT_EQ(my_vgcanvas_fill_rect(canvas, &(my_rectf_t){0, 0, 10, 10}),
            MY_RET_OK);
  ASSERT_EQ(my_vgcanvas_end_frame(canvas), MY_RET_OK);
  pixels = my_lcd_mem_get_buffer(lcd);
  stride = my_lcd_mem_get_stride(lcd);
  ASSERT_NOT_NULL(pixels);
  ASSERT_EQ(pixels[(size_t)15 * stride + (size_t)15 * 4 + 2], 255);

  my_vgcanvas_destroy(canvas);
  my_object_unref((my_object_t*)win);
  my_pal_destroy(pal);
}

TEST(dynamic_scale_reconfigures_injected_canvas_without_resize)
{
  my_pal_t* pal = my_pal_dummy_create(NULL);
  my_window_t* win;
  my_vgcanvas_t* canvas;
  my_lcd_t* lcd;
  uint8_t* pixels;
  uint32_t stride;

  ASSERT_NOT_NULL(pal);
  win = my_window_create(NULL, pal, 100, 50, "dynamic-scale");
  ASSERT_NOT_NULL(win);
  /* The injected target deliberately has headroom for the new backing scale. */
  lcd = my_lcd_mem_create(NULL, 200, 100, MY_PIXEL_FORMAT_BGRA8888);
  ASSERT_NOT_NULL(lcd);
  canvas = my_vgcanvas_soft_create(NULL, lcd);
  ASSERT_NOT_NULL(canvas);
  my_window_set_vgcanvas(win, canvas);
  ASSERT_EQ(my_vgcanvas_begin_frame(canvas, NULL), MY_RET_OK);
  ASSERT_EQ(my_vgcanvas_set_fill_color(canvas, my_color_rgb(255, 0, 0)),
            MY_RET_OK);
  ASSERT_EQ(my_vgcanvas_fill_rect(canvas, &(my_rectf_t){0, 0, 10, 10}),
            MY_RET_OK);
  ASSERT_EQ(my_vgcanvas_end_frame(canvas), MY_RET_OK);
  pixels = my_lcd_mem_get_buffer(lcd);
  stride = my_lcd_mem_get_stride(lcd);
  ASSERT_NOT_NULL(pixels);
  ASSERT_EQ(pixels[(size_t)15 * stride + (size_t)15 * 4 + 2], 0);

  my_dirty_rects_clear(&win->dirty);
  my_pal_dummy_set_scale_factor(pal, 2.0f);
  ASSERT_TRUE(my_window_refresh_scale(win));
  ASSERT_EQ(win->scale, 2.0f);
  ASSERT_EQ(((my_widget_t*)win)->rect.w, 100);
  ASSERT_EQ(((my_widget_t*)win)->rect.h, 50);
  ASSERT_TRUE(my_dirty_rects_count(&win->dirty) > 0);
  ASSERT_TRUE(!my_window_refresh_scale(win));

  ASSERT_EQ(my_vgcanvas_begin_frame(canvas, NULL), MY_RET_OK);
  ASSERT_EQ(my_vgcanvas_fill_rect(canvas, &(my_rectf_t){0, 0, 10, 10}),
            MY_RET_OK);
  ASSERT_EQ(my_vgcanvas_end_frame(canvas), MY_RET_OK);
  ASSERT_EQ(pixels[(size_t)15 * stride + (size_t)15 * 4 + 2], 255);

  my_vgcanvas_destroy(canvas);
  my_lcd_destroy(lcd);
  my_object_unref((my_object_t*)win);
  my_pal_destroy(pal);
}

TEST(window_record_dirty_reports_damage_in_owner_frame)
{
  my_pal_t* pal = my_pal_dummy_create(NULL);
  my_window_t* win;
  my_vgcanvas_t* canvas;
  my_lcd_t* lcd;
  my_ui_frame_metrics_sample_t sample;

  ASSERT_NOT_NULL(pal);
  win = my_window_create(NULL, pal, 40, 30, "metrics-window");
  ASSERT_NOT_NULL(win);
  lcd = my_pal_window_get_lcd(win->pal_window);
  ASSERT_NOT_NULL(lcd);
  canvas = my_vgcanvas_soft_create(NULL, lcd);
  ASSERT_NOT_NULL(canvas);
  my_window_set_vgcanvas(win, canvas);
  my_dirty_rects_clear(&win->dirty);
  my_widget_invalidate(my_window_widget(win), NULL);
  ASSERT_TRUE(my_dirty_rects_count(&win->dirty) > 0);

  memset(&g_myui_metrics, 0, sizeof(g_myui_metrics));
  my_ui_metrics_set_enabled(true);
  ASSERT_EQ(my_vgcanvas_begin_frame(canvas, NULL), MY_RET_OK);
  ASSERT_EQ(my_window_record_dirty(win), MY_RET_OK);
  ASSERT_EQ(my_vgcanvas_end_frame(canvas), MY_RET_OK);
  ASSERT_TRUE(my_ui_metrics_get_last(&sample));
  ASSERT_TRUE(sample.damage_rects > 0u);
  ASSERT_TRUE(sample.damage_area_pixels > 0u);

  my_vgcanvas_destroy(canvas);
  my_object_unref((my_object_t*)win);
  my_pal_destroy(pal);
}

TEST(floating_plain_widget_does_not_crash_hit_test)
{
  my_widget_t* root = my_widget_create(NULL, "root");
  my_widget_t* overlay = my_widget_create(NULL, "overlay");

  ASSERT_NOT_NULL(root);
  ASSERT_NOT_NULL(overlay);
  ASSERT_EQ(my_widget_set_rect(root, &(my_rect_t){0, 0, 100, 100}),
            MY_RET_OK);
  ASSERT_EQ(my_widget_set_rect(overlay, &(my_rect_t){10, 10, 40, 40}),
            MY_RET_OK);
  overlay->floating = true;
  ASSERT_EQ(my_widget_add_child(root, overlay), MY_RET_OK);
  ASSERT_TRUE(my_widget_hit_test(root, 20, 20) == root);

  my_widget_unref(overlay);
  my_widget_unref(root);
}

TEST(text_area_grows_capacity_exponentially)
{
  my_widget_t* area = my_text_area_create(NULL);
  char text[257];
  size_t length;
  size_t previous_capacity;

  ASSERT_NOT_NULL(area);
  previous_capacity = ((my_text_area_t*)area)->text_cap;
  memset(text, 'x', sizeof(text) - 1);
  text[sizeof(text) - 1] = '\0';
  for (length = 1; length < sizeof(text); length++) {
    text[length - 1] = 'x';
    text[length] = '\0';
    ASSERT_EQ(my_text_area_set_text(area, text), MY_RET_OK);
    ASSERT_TRUE(((my_text_area_t*)area)->text_cap >= length + 1);
    ASSERT_TRUE(((my_text_area_t*)area)->text_cap >= previous_capacity);
    previous_capacity = ((my_text_area_t*)area)->text_cap;
  }
  ASSERT_TRUE(((my_text_area_t*)area)->text_cap > strlen(text) + 1);
  my_widget_unref(area);
}

TEST(text_area_wrap_rebuilds_after_edit)
{
  my_widget_t* area = my_text_area_create(NULL);
  ASSERT_NOT_NULL(area);
  ASSERT_EQ(my_widget_set_rect(area, &(my_rect_t){0, 0, 20, 80}), MY_RET_OK);
  ASSERT_EQ(my_text_area_set_wrap(area, true), MY_RET_OK);
  ASSERT_EQ(my_text_area_set_text(area, "ab"), MY_RET_OK);
  ASSERT_EQ(my_text_area_visual_line_count(area), 2u);
  ASSERT_EQ(my_text_area_set_text(area, "a"), MY_RET_OK);
  ASSERT_EQ(my_text_area_visual_line_count(area), 1u);
  ASSERT_EQ(my_text_area_set_text(area, "abc\ndef"), MY_RET_OK);
  ASSERT_EQ(my_text_area_visual_line_count(area), 6u);
  my_widget_unref(area);
}

TEST(text_area_visual_lines_cache_byte_ranges)
{
  my_widget_t* area = my_text_area_create(NULL);
  const my_visual_line_t* line;

  ASSERT_NOT_NULL(area);
  ASSERT_EQ(my_widget_set_rect(area, &(my_rect_t){0, 0, 28, 80}), MY_RET_OK);
  ASSERT_EQ(my_text_area_set_wrap(area, true), MY_RET_OK);
  ASSERT_EQ(my_text_area_set_text(area, "abcdefghij"), MY_RET_OK);
  ASSERT_EQ(my_text_area_visual_line_count(area), 5u);
  line = my_text_area_visual_line_at(area, 2);
  ASSERT_NOT_NULL(line);
  ASSERT_EQ(line->start_byte, 4u);
  ASSERT_EQ(line->len_bytes, 2u);
  my_widget_unref(area);
}

TEST(text_area_visual_line_index_cache_tracks_folds_and_edits)
{
  my_widget_t* area = my_text_area_create(NULL);
  my_text_area_t* ta;
  size_t col_in = 0;
  size_t visual;

  ASSERT_NOT_NULL(area);
  ta = (my_text_area_t*)area;
  ASSERT_EQ(my_widget_set_rect(area, &(my_rect_t){0, 0, 28, 80}), MY_RET_OK);
  ASSERT_EQ(my_text_area_set_wrap(area, true), MY_RET_OK);
  ASSERT_EQ(my_text_area_set_text(area, "abcd\nefgh\nijkl"), MY_RET_OK);
  visual = my_text_area_visual_line_of_pos(area, 1, 2, &col_in);
  ASSERT_TRUE(visual < my_text_area_visual_line_count(area));
  ASSERT_NOT_NULL(ta->vline_first_by_phys);
  ASSERT_NOT_NULL(ta->vline_last_by_phys);
  ASSERT_EQ(ta->vline_first_by_phys[1], 2u);
  ASSERT_EQ(ta->vline_last_by_phys[1], 3u);
  ASSERT_EQ(col_in, 0u);
  ASSERT_EQ(my_text_area_set_folded_range(area, 0, 1, true), MY_RET_OK);
  ASSERT_EQ(my_text_area_visual_line_count(area), 4u);
  ASSERT_EQ(my_text_area_visual_line_of_pos(area, 2, 1, &col_in), 2u);
  ASSERT_EQ(ta->vline_first_by_phys[1], SIZE_MAX);
  ASSERT_EQ(ta->vline_first_by_phys[2], 2u);
  ASSERT_EQ(ta->vline_last_by_phys[2], 3u);
  ASSERT_EQ(my_text_area_set_text(area, "xy\nzzzz"), MY_RET_OK);
  ASSERT_EQ(my_text_area_visual_line_count(area), 3u);
  ASSERT_EQ(my_text_area_visual_line_of_pos(area, 1, 2, &col_in), 2u);
  ASSERT_EQ(ta->vline_first_by_phys[1], 1u);
  ASSERT_EQ(ta->vline_last_by_phys[1], 2u);
  my_widget_unref(area);
}

TEST(text_area_visual_line_index_cache_oom_falls_back)
{
  text_area_fail_alloc_t state = {false, false};
  my_allocator_t allocator = {&state, text_area_fail_alloc,
                              text_area_fail_calloc, text_area_fail_realloc,
                              text_area_fail_free};
  my_widget_t* area = my_text_area_create(&allocator);
  my_text_area_t* ta;
  size_t col_in = 0;

  ASSERT_NOT_NULL(area);
  ta = (my_text_area_t*)area;
  ASSERT_EQ(my_widget_set_rect(area, &(my_rect_t){0, 0, 28, 80}), MY_RET_OK);
  ASSERT_EQ(my_text_area_set_wrap(area, true), MY_RET_OK);
  ASSERT_EQ(my_text_area_set_text(area, "abcdefgh"), MY_RET_OK);
  ASSERT_EQ(my_text_area_visual_line_count(area), 4u);
  state.fail = true;
  ASSERT_EQ(my_text_area_visual_line_of_pos(area, 0, 5, &col_in), 2u);
  ASSERT_EQ(col_in, 1u);
  ASSERT_TRUE(ta->vline_first_by_phys == NULL);
  state.fail = false;
  my_widget_unref(area);
}

TEST(text_area_geometry_cache_reuses_glyph_advances)
{
  text_area_variable_font_t font = {{&text_area_variable_font_vtable}, 0, 0};
  my_widget_t* area = my_text_area_create(NULL);
  my_text_area_t* text_area = (my_text_area_t*)area;
  my_lcd_t* lcd = my_lcd_mem_create(NULL, 160, 80, MY_PIXEL_FORMAT_BGRA8888);
  my_vgcanvas_t* canvas = my_vgcanvas_soft_create(NULL, lcd);
  size_t first_frame;
  size_t second_frame;

  ASSERT_NOT_NULL(area);
  ASSERT_NOT_NULL(lcd);
  ASSERT_NOT_NULL(canvas);
  ASSERT_EQ(my_widget_set_rect(area, &(my_rect_t){0, 0, 80, 54}), MY_RET_OK);
  my_text_area_set_font(area, (my_font_t*)&font, 16);
  ASSERT_EQ(my_text_area_set_text(area, "ABBA"), MY_RET_OK);
  text_area->focused = true;
  text_area->cursor_visible = true;
  ASSERT_EQ(my_vgcanvas_begin_frame(canvas, NULL), MY_RET_OK);
  area->vtable->on_paint(area, canvas);
  ASSERT_EQ(my_vgcanvas_end_frame(canvas), MY_RET_OK);
  first_frame = font.glyph_calls;
  ASSERT_TRUE(first_frame > 0);
  ASSERT_EQ(my_vgcanvas_begin_frame(canvas, NULL), MY_RET_OK);
  area->vtable->on_paint(area, canvas);
  ASSERT_EQ(my_vgcanvas_end_frame(canvas), MY_RET_OK);
  second_frame = font.glyph_calls - first_frame;
  ASSERT_EQ(second_frame, 0u);
  ASSERT_EQ(my_text_area_set_text(area, "BABA"), MY_RET_OK);
  first_frame = font.glyph_calls;
  ASSERT_EQ(my_vgcanvas_begin_frame(canvas, NULL), MY_RET_OK);
  area->vtable->on_paint(area, canvas);
  ASSERT_EQ(my_vgcanvas_end_frame(canvas), MY_RET_OK);
  ASSERT_TRUE(font.glyph_calls > first_frame);
  my_text_area_set_font(area, (my_font_t*)&font, 18);
  first_frame = font.glyph_calls;
  ASSERT_EQ(my_vgcanvas_begin_frame(canvas, NULL), MY_RET_OK);
  area->vtable->on_paint(area, canvas);
  ASSERT_EQ(my_vgcanvas_end_frame(canvas), MY_RET_OK);
  ASSERT_TRUE(font.glyph_calls > first_frame);
  my_widget_unref(area);
  my_vgcanvas_destroy(canvas);
  my_lcd_destroy(lcd);
}

TEST(text_area_geometry_saturates_huge_glyph_advances)
{
  text_area_huge_font_t font = {{&text_area_huge_font_vtable}};
  my_widget_t* area = my_text_area_create(NULL);
  my_text_area_t* text_area = (my_text_area_t*)area;
  my_lcd_t* lcd = my_lcd_mem_create(NULL, 160, 80, MY_PIXEL_FORMAT_BGRA8888);
  my_vgcanvas_t* canvas = my_vgcanvas_soft_create(NULL, lcd);

  ASSERT_NOT_NULL(area);
  ASSERT_NOT_NULL(lcd);
  ASSERT_NOT_NULL(canvas);
  ASSERT_EQ(my_widget_set_rect(area, &(my_rect_t){0, 0, 80, 54}), MY_RET_OK);
  my_text_area_set_font(area, (my_font_t*)&font, 16);
  ASSERT_EQ(my_text_area_set_text(area, "AB"), MY_RET_OK);
  text_area->focused = true;
  text_area->cursor_visible = true;
  ASSERT_EQ(my_vgcanvas_begin_frame(canvas, NULL), MY_RET_OK);
  area->vtable->on_paint(area, canvas);
  ASSERT_EQ(my_vgcanvas_end_frame(canvas), MY_RET_OK);
  ASSERT_EQ(text_area->geometry_count, 2u);
  ASSERT_EQ(text_area->geometry_boundaries[0], 0);
  ASSERT_EQ(text_area->geometry_boundaries[1], INT32_MAX);
  ASSERT_EQ(text_area->geometry_boundaries[2], INT32_MAX);
  text_area->scroll_x = INT32_MAX;
  text_area->scroll_y = INT32_MAX;
  ASSERT_EQ(my_vgcanvas_begin_frame(canvas, NULL), MY_RET_OK);
  area->vtable->on_paint(area, canvas);
  ASSERT_EQ(my_vgcanvas_end_frame(canvas), MY_RET_OK);
  my_vgcanvas_destroy(canvas);
  my_lcd_destroy(lcd);
  my_widget_unref(area);
}

TEST(edit_insert_oom_is_transactional)
{
  text_area_fail_alloc_t state = {false, false};
  my_allocator_t allocator = {&state, text_area_fail_alloc,
                              text_area_fail_calloc, text_area_fail_realloc,
                              text_area_fail_free};
  my_widget_t* edit = my_edit_create(&allocator);
  my_edit_t* edit_state;
  my_event_t event = my_event_init(MY_EVENT_KEY_DOWN);
  int changed = 0;

  ASSERT_NOT_NULL(edit);
  edit_state = (my_edit_t*)edit;
  ASSERT_EQ(my_edit_set_text(edit, "before"), MY_RET_OK);
  ASSERT_NEQ(my_widget_on(edit, "changed", count_edit_changed, &changed), 0u);
  state.fail = true;
  event.u.key.key = 'x';
  event.u.key.modifiers = 0;
  edit_state->focused = true;
  ASSERT_EQ(edit->vtable->on_event(edit, &event), MY_RET_OK);
  ASSERT_STR_EQ(my_edit_get_text(edit), "before");
  ASSERT_EQ(edit_state->cursor, strlen("before"));
  ASSERT_EQ(edit_state->anchor, strlen("before"));
  ASSERT_EQ(my_undo_stack_size(edit_state->undo), 0u);
  ASSERT_EQ(changed, 0);
  my_widget_unref(edit);
}

TEST(edit_paint_uses_measurement_font)
{
  text_area_variable_font_t measure_font = {{&text_area_variable_font_vtable}, 0, 0};
  text_area_variable_font_t canvas_font = {{&text_area_variable_font_vtable}, 0, 0};
  my_widget_t* edit = my_edit_create(NULL);
  my_lcd_t* lcd = my_lcd_mem_create(NULL, 160, 40, MY_PIXEL_FORMAT_BGRA8888);
  my_vgcanvas_t* canvas = my_vgcanvas_soft_create(NULL, lcd);

  ASSERT_NOT_NULL(edit);
  ASSERT_NOT_NULL(lcd);
  ASSERT_NOT_NULL(canvas);
  ASSERT_EQ(my_widget_set_rect(edit, &(my_rect_t){0, 0, 120, 30}), MY_RET_OK);
  ASSERT_EQ(my_edit_set_text(edit, "AB"), MY_RET_OK);
  my_edit_set_font(edit, (my_font_t*)&measure_font, 16);
  ASSERT_EQ(my_vgcanvas_set_font(canvas, (my_font_t*)&canvas_font, 16),
            MY_RET_OK);
  ASSERT_EQ(my_vgcanvas_begin_frame(canvas, NULL), MY_RET_OK);
  edit->vtable->on_paint(edit, canvas);
  ASSERT_EQ(my_vgcanvas_end_frame(canvas), MY_RET_OK);
  ASSERT_TRUE(measure_font.glyph_calls > 0 || measure_font.measure_calls > 0);
  ASSERT_EQ(canvas_font.glyph_calls, 0u);
  ASSERT_EQ(canvas_font.measure_calls, 0u);
  my_vgcanvas_destroy(canvas);
  my_lcd_destroy(lcd);
  my_widget_unref(edit);
}

TEST(edit_geometry_saturates_huge_font)
{
  text_area_huge_font_t font = {{&text_area_huge_font_vtable}};
  my_widget_t* edit = my_edit_create(NULL);
  my_edit_t* edit_state;
  my_event_t event = my_event_init(MY_EVENT_POINTER_DOWN);
  my_lcd_t* lcd = my_lcd_mem_create(NULL, 160, 40, MY_PIXEL_FORMAT_BGRA8888);
  my_vgcanvas_t* canvas = my_vgcanvas_soft_create(NULL, lcd);

  ASSERT_NOT_NULL(edit);
  ASSERT_NOT_NULL(lcd);
  ASSERT_NOT_NULL(canvas);
  edit_state = (my_edit_t*)edit;
  ASSERT_EQ(my_widget_set_rect(edit, &(my_rect_t){0, 0, 120, 30}), MY_RET_OK);
  my_edit_set_font(edit, (my_font_t*)&font, 16);
  ASSERT_EQ(my_edit_set_text(edit, "AB"), MY_RET_OK);
  edit_state->focused = true;
  event.u.pointer.x = INT32_MAX;
  event.u.pointer.y = 5;
  ASSERT_EQ(edit->vtable->on_event(edit, &event), MY_RET_OK);
  ASSERT_TRUE(edit_state->cursor <= strlen("AB"));
  ASSERT_TRUE(edit_state->cursor == 0u || edit_state->cursor == 1u ||
              edit_state->cursor == 2u);
  ASSERT_TRUE(edit_state->scroll_x >= 0);
  ASSERT_EQ(my_vgcanvas_begin_frame(canvas, NULL), MY_RET_OK);
  edit->vtable->on_paint(edit, canvas);
  ASSERT_EQ(my_vgcanvas_end_frame(canvas), MY_RET_OK);
  my_vgcanvas_destroy(canvas);
  my_lcd_destroy(lcd);
  my_widget_unref(edit);
}

TEST(edit_password_oom_preserves_previous_mask)
{
  text_area_fail_alloc_t state = {false, false};
  my_allocator_t allocator = {&state, text_area_fail_alloc,
                              text_area_fail_calloc, text_area_fail_realloc,
                              text_area_fail_free};
  my_widget_t* edit = my_edit_create(&allocator);
  my_edit_t* edit_state;

  ASSERT_NOT_NULL(edit);
  edit_state = (my_edit_t*)edit;
  ASSERT_EQ(my_edit_set_text(edit, "secret"), MY_RET_OK);
  ASSERT_EQ(my_edit_set_password(edit, true), MY_RET_OK);
  ASSERT_STR_EQ(edit_state->masked, "******");
  state.fail = true;
  ASSERT_EQ(my_edit_set_text(edit, "changed"), MY_RET_OOM);
  ASSERT_STR_EQ(my_edit_get_text(edit), "secret");
  ASSERT_STR_EQ(edit_state->masked, "******");
  my_widget_unref(edit);
}

TEST(edit_password_delete_oom_is_transactional)
{
  text_area_fail_alloc_t state = {false, false};
  my_allocator_t allocator = {&state, text_area_fail_alloc,
                              text_area_fail_calloc, text_area_fail_realloc,
                              text_area_fail_free};
  my_widget_t* edit = my_edit_create(&allocator);
  my_edit_t* edit_state;
  my_event_t event = my_event_init(MY_EVENT_KEY_DOWN);

  ASSERT_NOT_NULL(edit);
  edit_state = (my_edit_t*)edit;
  ASSERT_EQ(my_edit_set_text(edit, "secret"), MY_RET_OK);
  ASSERT_EQ(my_edit_set_password(edit, true), MY_RET_OK);
  edit_state->focused = true;
  state.fail = true;
  event.u.key.key = MY_KEY_BACKSPACE;
  ASSERT_EQ(edit->vtable->on_event(edit, &event), MY_RET_OK);
  ASSERT_STR_EQ(my_edit_get_text(edit), "secret");
  ASSERT_STR_EQ(edit_state->masked, "******");
  ASSERT_EQ(edit_state->cursor, strlen("secret"));
  my_widget_unref(edit);
}

TEST(edit_password_toggle_oom_preserves_state)
{
  text_area_fail_alloc_t state = {false, false};
  my_allocator_t allocator = {&state, text_area_fail_alloc,
                              text_area_fail_calloc, text_area_fail_realloc,
                              text_area_fail_free};
  my_widget_t* edit = my_edit_create(&allocator);
  my_edit_t* edit_state;

  ASSERT_NOT_NULL(edit);
  edit_state = (my_edit_t*)edit;
  ASSERT_EQ(my_edit_set_text(edit, "secret"), MY_RET_OK);
  state.fail = true;
  ASSERT_EQ(my_edit_set_password(edit, true), MY_RET_OOM);
  ASSERT_FALSE(edit_state->password);
  ASSERT_TRUE(edit_state->masked == NULL);
  my_widget_unref(edit);
}

TEST(edit_delete_oom_does_not_record_history)
{
  text_area_fail_alloc_t state = {false, false};
  my_allocator_t allocator = {&state, text_area_fail_alloc,
                              text_area_fail_calloc, text_area_fail_realloc,
                              text_area_fail_free};
  my_widget_t* edit = my_edit_create(&allocator);
  my_edit_t* edit_state;
  my_event_t event = my_event_init(MY_EVENT_KEY_DOWN);

  ASSERT_NOT_NULL(edit);
  edit_state = (my_edit_t*)edit;
  ASSERT_EQ(my_edit_set_text(edit, "secret"), MY_RET_OK);
  edit_state->focused = true;
  state.fail = true;
  event.u.key.key = MY_KEY_BACKSPACE;
  ASSERT_EQ(edit->vtable->on_event(edit, &event), MY_RET_OK);
  ASSERT_STR_EQ(my_edit_get_text(edit), "secret");
  ASSERT_EQ(my_undo_stack_size(edit_state->undo), 0u);
  my_widget_unref(edit);
}

TEST(edit_selection_replace_undo_restores_deleted_text)
{
  my_widget_t* edit = my_edit_create(NULL);
  my_edit_t* edit_state;
  my_event_t event = my_event_init(MY_EVENT_KEY_DOWN);

  ASSERT_NOT_NULL(edit);
  edit_state = (my_edit_t*)edit;
  ASSERT_EQ(my_edit_set_text(edit, "abc"), MY_RET_OK);
  edit_state->cursor = 1;
  edit_state->anchor = 2;
  edit_state->focused = true;
  event.u.key.key = 'X';
  ASSERT_EQ(edit->vtable->on_event(edit, &event), MY_RET_OK);
  ASSERT_STR_EQ(my_edit_get_text(edit), "aXc");
  ASSERT_EQ(my_undo_stack_size(edit_state->undo), 1u);
  event.u.key.key = 'z';
  event.u.key.modifiers = MY_KEYMOD_CTRL;
  ASSERT_EQ(edit->vtable->on_event(edit, &event), MY_RET_OK);
  ASSERT_STR_EQ(my_edit_get_text(edit), "abc");
  event.u.key.key = 'y';
  ASSERT_EQ(edit->vtable->on_event(edit, &event), MY_RET_OK);
  ASSERT_STR_EQ(my_edit_get_text(edit), "aXc");
  my_widget_unref(edit);
}

TEST(undo_stack_rejects_size_overflow_and_terminates_delete_batches)
{
  undo_guard_alloc_t state = {false};
  my_allocator_t allocator = {&state, undo_guard_alloc, undo_guard_calloc,
                              undo_guard_realloc, undo_guard_free};
  my_undo_stack_t* stack = my_undo_stack_create(&allocator, 8);
  my_undo_op_t op;

  ASSERT_NOT_NULL(stack);
  ASSERT_EQ(my_undo_stack_record_insert(stack, 0, "x", SIZE_MAX), MY_RET_OOM);
  ASSERT_EQ(my_undo_stack_record_delete(stack, 1, "a", 1), MY_RET_OK);
  ASSERT_EQ(my_undo_stack_record_delete(stack, 0, "b", 1), MY_RET_OK);
  ASSERT_FALSE(state.bad_size_request);
  ASSERT_EQ(my_undo_stack_undo(stack, &op), MY_RET_OK);
  ASSERT_EQ(op.offset, 0u);
  ASSERT_EQ(op.remove_len, 0u);
  ASSERT_EQ(op.bytes_len, 2u);
  ASSERT_STR_EQ(op.bytes, "ba");
  ASSERT_EQ(my_undo_stack_record_replace(stack, 0, "x", SIZE_MAX, "y", 1),
            MY_RET_OOM);
  ASSERT_FALSE(state.bad_size_request);
  my_undo_stack_destroy(stack);
}

TEST(undo_stack_record_oom_preserves_redo_branch)
{
  text_area_fail_alloc_t state = {false, false};
  my_allocator_t allocator = {&state, text_area_fail_alloc,
                              text_area_fail_calloc, text_area_fail_realloc,
                              text_area_fail_free};
  my_undo_stack_t* stack = my_undo_stack_create(&allocator, 8);
  my_undo_op_t op;

  ASSERT_NOT_NULL(stack);
  ASSERT_EQ(my_undo_stack_record_insert(stack, 0, "a", 1), MY_RET_OK);
  ASSERT_EQ(my_undo_stack_undo(stack, &op), MY_RET_OK);
  ASSERT_TRUE(my_undo_stack_can_redo(stack));
  state.fail = true;
  ASSERT_EQ(my_undo_stack_record_insert(stack, 0, "b", 1), MY_RET_OOM);
  ASSERT_TRUE(my_undo_stack_can_redo(stack));
  ASSERT_EQ(my_undo_stack_redo(stack, &op), MY_RET_OK);
  ASSERT_EQ(op.offset, 0u);
  ASSERT_EQ(op.bytes_len, 1u);
  ASSERT_EQ(op.bytes[0], 'a');
  my_undo_stack_destroy(stack);
}

TEST(undo_stack_capacity_oom_preserves_oldest_entry)
{
  text_area_fail_alloc_t state = {false, false};
  my_allocator_t allocator = {&state, text_area_fail_alloc,
                              text_area_fail_calloc, text_area_fail_realloc,
                              text_area_fail_free};
  my_undo_stack_t* stack = my_undo_stack_create(&allocator, 1);
  my_undo_op_t op;

  ASSERT_NOT_NULL(stack);
  ASSERT_EQ(my_undo_stack_record_insert(stack, 0, "a", 1), MY_RET_OK);
  state.fail = true;
  ASSERT_EQ(my_undo_stack_record_insert(stack, 1, "b", 1), MY_RET_OOM);
  ASSERT_EQ(my_undo_stack_size(stack), 1u);
  ASSERT_EQ(my_undo_stack_undo(stack, &op), MY_RET_OK);
  ASSERT_EQ(op.offset, 0u);
  ASSERT_EQ(op.bytes_len, 0u);
  ASSERT_EQ(op.remove_len, 1u);
  my_undo_stack_destroy(stack);
}

TEST(undo_stack_peek_commit_is_transactional)
{
  my_undo_stack_t* stack = my_undo_stack_create(NULL, 8);
  my_undo_op_t op;

  ASSERT_NOT_NULL(stack);
  ASSERT_EQ(my_undo_stack_record_insert(stack, 0, "a", 1), MY_RET_OK);
  ASSERT_EQ(my_undo_stack_undo_peek_tagged(stack, &op, NULL), MY_RET_OK);
  ASSERT_EQ(op.remove_len, 1u);
  ASSERT_EQ(op.bytes_len, 0u);
  ASSERT_TRUE(my_undo_stack_can_undo(stack));
  ASSERT_FALSE(my_undo_stack_can_redo(stack));
  ASSERT_EQ(my_undo_stack_commit_undo(stack), MY_RET_OK);
  ASSERT_FALSE(my_undo_stack_can_undo(stack));
  ASSERT_TRUE(my_undo_stack_can_redo(stack));
  ASSERT_EQ(my_undo_stack_redo_peek_tagged(stack, &op, NULL), MY_RET_OK);
  ASSERT_EQ(op.bytes_len, 1u);
  ASSERT_EQ(op.bytes[0], 'a');
  ASSERT_TRUE(my_undo_stack_can_redo(stack));
  ASSERT_EQ(my_undo_stack_commit_redo(stack), MY_RET_OK);
  ASSERT_TRUE(my_undo_stack_can_undo(stack));
  my_undo_stack_destroy(stack);
}

TEST(shared_undo_registration_oom_keeps_widgets_private)
{
  text_area_fail_alloc_t state = {false, false};
  my_allocator_t allocator = {&state, text_area_fail_alloc,
                              text_area_fail_calloc, text_area_fail_realloc,
                              text_area_fail_free};
  my_undo_manager_t* manager = my_undo_manager_create(&allocator, 8);
  my_widget_t* edit = my_edit_create(NULL);
  my_widget_t* area = my_text_area_create(NULL);

  ASSERT_NOT_NULL(manager);
  ASSERT_NOT_NULL(edit);
  ASSERT_NOT_NULL(area);
  state.fail = true;
  ASSERT_EQ(my_edit_set_undo_shared(edit, manager), MY_RET_OOM);
  ASSERT_EQ(my_text_area_set_undo_shared(area, manager), MY_RET_OOM);
  ASSERT_TRUE(((my_edit_t*)edit)->undo_shared == NULL);
  ASSERT_TRUE(((my_text_area_t*)area)->undo_shared == NULL);
  my_widget_unref(edit);
  my_widget_unref(area);
  my_undo_manager_destroy(manager);
}

TEST(text_area_selection_replace_undo_restores_deleted_text)
{
  my_widget_t* area = my_text_area_create(NULL);
  my_text_area_t* text_area;
  my_event_t event = my_event_init(MY_EVENT_KEY_DOWN);

  ASSERT_NOT_NULL(area);
  text_area = (my_text_area_t*)area;
  ASSERT_EQ(my_text_area_set_text(area, "abc"), MY_RET_OK);
  text_area->focused = true;
  text_area->cursor_row = 0;
  text_area->cursor_col = 1;
  text_area->anchor_row = 0;
  text_area->anchor_col = 2;
  event.u.key.key = 'X';
  ASSERT_EQ(area->vtable->on_event(area, &event), MY_RET_OK);
  ASSERT_STR_EQ(my_text_area_get_text(area), "aXc");
  ASSERT_EQ(my_undo_stack_size(text_area->undo), 1u);
  event.u.key.key = 'z';
  event.u.key.modifiers = MY_KEYMOD_CTRL;
  ASSERT_EQ(area->vtable->on_event(area, &event), MY_RET_OK);
  ASSERT_STR_EQ(my_text_area_get_text(area), "abc");
  my_widget_unref(area);
}

TEST(text_area_selection_replace_over_max_len_preserves_document)
{
  my_widget_t* area = my_text_area_create(NULL);
  my_text_area_t* text_area;
  my_event_t event = my_event_init(MY_EVENT_KEY_DOWN);

  ASSERT_NOT_NULL(area);
  text_area = (my_text_area_t*)area;
  ASSERT_EQ(my_text_area_set_text(area, "abcd"), MY_RET_OK);
  text_area->focused = true;
  ASSERT_EQ(my_text_area_set_max_len(area, 2), MY_RET_OK);
  text_area->cursor_row = 0;
  text_area->cursor_col = 1;
  text_area->anchor_row = 0;
  text_area->anchor_col = 3;
  event.u.key.key = 'W';
  ASSERT_EQ(area->vtable->on_event(area, &event), MY_RET_OK);
  ASSERT_STR_EQ(my_text_area_get_text(area), "abcd");
  ASSERT_EQ(my_undo_stack_size(text_area->undo), 0u);
  my_widget_unref(area);
}

TEST(text_area_insert_reserve_oom_does_not_record_history)
{
  text_area_fail_alloc_t state = {false, false};
  my_allocator_t allocator = {&state, text_area_fail_alloc,
                              text_area_fail_calloc, text_area_fail_realloc,
                              text_area_fail_free};
  my_widget_t* area = my_text_area_create(&allocator);
  my_text_area_t* text_area;
  my_event_t event = my_event_init(MY_EVENT_KEY_DOWN);

  ASSERT_NOT_NULL(area);
  text_area = (my_text_area_t*)area;
  ASSERT_EQ(my_text_area_set_text(area, "a"), MY_RET_OK);
  text_area->focused = true;
  state.fail_realloc = true;
  event.u.key.key = 'b';
  ASSERT_EQ(area->vtable->on_event(area, &event), MY_RET_OK);
  ASSERT_STR_EQ(my_text_area_get_text(area), "a");
  ASSERT_EQ(my_undo_stack_size(text_area->undo), 0u);
  my_widget_unref(area);
}

TEST(text_area_selection_replace_reserve_oom_is_transactional)
{
  text_area_fail_alloc_t state = {false, false};
  my_allocator_t allocator = {&state, text_area_fail_alloc,
                              text_area_fail_calloc, text_area_fail_realloc,
                              text_area_fail_free};
  my_widget_t* area = my_text_area_create(&allocator);
  my_text_area_t* text_area;
  my_event_t event = my_event_init(MY_EVENT_IME_COMMIT);

  ASSERT_NOT_NULL(area);
  text_area = (my_text_area_t*)area;
  ASSERT_EQ(my_text_area_set_text(area, "abc"), MY_RET_OK);
  text_area->focused = true;
  text_area->cursor_row = 0;
  text_area->cursor_col = 1;
  text_area->anchor_row = 0;
  text_area->anchor_col = 2;
  state.fail_realloc = true;
  event.u.ime.text = "WX";
  ASSERT_EQ(area->vtable->on_event(area, &event), MY_RET_OK);
  ASSERT_STR_EQ(my_text_area_get_text(area), "abc");
  ASSERT_EQ(my_undo_stack_size(text_area->undo), 0u);
  ASSERT_EQ(text_area->cursor_col, 1u);
  ASSERT_EQ(text_area->anchor_col, 2u);
  my_widget_unref(area);
}

TEST(text_area_delete_history_oom_preserves_document)
{
  text_area_fail_alloc_t state = {false, false};
  my_allocator_t allocator = {&state, text_area_fail_alloc,
                              text_area_fail_calloc, text_area_fail_realloc,
                              text_area_fail_free};
  my_widget_t* area = my_text_area_create(&allocator);
  my_text_area_t* text_area;
  my_event_t event = my_event_init(MY_EVENT_KEY_DOWN);

  ASSERT_NOT_NULL(area);
  text_area = (my_text_area_t*)area;
  ASSERT_EQ(my_text_area_set_text(area, "ab"), MY_RET_OK);
  text_area->focused = true;
  state.fail = true;
  event.u.key.key = MY_KEY_BACKSPACE;
  ASSERT_EQ(area->vtable->on_event(area, &event), MY_RET_OK);
  ASSERT_STR_EQ(my_text_area_get_text(area), "ab");
  ASSERT_EQ(my_undo_stack_size(text_area->undo), 0u);
  my_widget_unref(area);
}

TEST(text_area_set_text_oom_preserves_history)
{
  text_area_fail_alloc_t state = {false, false};
  my_allocator_t allocator = {&state, text_area_fail_alloc,
                              text_area_fail_calloc, text_area_fail_realloc,
                              text_area_fail_free};
  my_widget_t* area = my_text_area_create(&allocator);
  my_text_area_t* text_area;
  my_event_t event = my_event_init(MY_EVENT_KEY_DOWN);

  ASSERT_NOT_NULL(area);
  text_area = (my_text_area_t*)area;
  ASSERT_EQ(my_text_area_set_text(area, "a"), MY_RET_OK);
  text_area->focused = true;
  event.u.key.key = 'b';
  ASSERT_EQ(area->vtable->on_event(area, &event), MY_RET_OK);
  ASSERT_EQ(my_undo_stack_size(text_area->undo), 1u);
  state.fail_realloc = true;
  ASSERT_EQ(my_text_area_set_text(area, "a longer replacement"), MY_RET_OOM);
  ASSERT_STR_EQ(my_text_area_get_text(area), "ab");
  ASSERT_EQ(my_undo_stack_size(text_area->undo), 1u);
  my_widget_unref(area);
}

TEST(text_area_line_cache_handles_unicode_hard_breaks)
{
  my_widget_t* area = my_text_area_create(NULL);

  ASSERT_NOT_NULL(area);
  ASSERT_EQ(my_text_area_set_text(area, "a\r\nb"), MY_RET_OK);
  ASSERT_EQ(my_text_area_line_count(area), 2u);
  ASSERT_EQ(my_text_area_set_text(area, "a\xC2\x85" "b"), MY_RET_OK);
  ASSERT_EQ(my_text_area_line_count(area), 2u);
  ASSERT_EQ(my_text_area_set_text(area, "a\vb"), MY_RET_OK);
  ASSERT_EQ(my_text_area_line_count(area), 2u);
  ASSERT_EQ(my_text_area_set_text(area, "a\fb"), MY_RET_OK);
  ASSERT_EQ(my_text_area_line_count(area), 2u);
  my_widget_unref(area);
}


TEST(text_area_rejects_corrupt_visual_line_slice)
{
  my_widget_t* area = my_text_area_create(NULL);
  my_lcd_t* lcd = my_lcd_mem_create(NULL, 160, 80, MY_PIXEL_FORMAT_BGRA8888);
  my_vgcanvas_t* canvas = my_vgcanvas_soft_create(NULL, lcd);
  const my_visual_line_t* line;

  ASSERT_NOT_NULL(area);
  ASSERT_NOT_NULL(lcd);
  ASSERT_NOT_NULL(canvas);
  ASSERT_EQ(my_widget_set_rect(area, &(my_rect_t){0, 0, 80, 54}), MY_RET_OK);
  ASSERT_EQ(my_text_area_set_wrap(area, true), MY_RET_OK);
  ASSERT_EQ(my_text_area_set_text(area, "abc"), MY_RET_OK);
  line = my_text_area_visual_line_at(area, 0);
  ASSERT_NOT_NULL(line);
  ((my_visual_line_t*)line)->start_byte = SIZE_MAX - 1u;
  ((my_visual_line_t*)line)->len_bytes = 4u;
  ASSERT_EQ(my_text_area_visual_line_at(area, 0), line);
  ASSERT_EQ(my_vgcanvas_begin_frame(canvas, NULL), MY_RET_OK);
  area->vtable->on_paint(area, canvas);
  ASSERT_EQ(my_vgcanvas_end_frame(canvas), MY_RET_OK);
  my_vgcanvas_destroy(canvas);
  my_lcd_destroy(lcd);
  my_widget_unref(area);
}

TEST(text_area_visual_line_query_rejects_out_of_range_index)
{
  my_widget_t* area = my_text_area_create(NULL);

  ASSERT_NOT_NULL(area);
  ASSERT_EQ(my_text_area_set_text(area, "one\ntwo"), MY_RET_OK);
  ASSERT_NOT_NULL(my_text_area_visual_line_at(area, 0));
  ASSERT_NOT_NULL(my_text_area_visual_line_at(area, 1));
  ASSERT_TRUE(my_text_area_visual_line_at(area, 2) == NULL);
  ASSERT_TRUE(my_text_area_visual_line_at(area, SIZE_MAX) == NULL);
  ASSERT_TRUE(my_text_area_visual_line_of_pos(area, SIZE_MAX, 0, NULL) < 2u);
  my_widget_unref(area);
}

TEST(text_area_shaping_params_are_owned_and_validated)
{
  my_widget_t* area = my_text_area_create(NULL);
  my_text_area_t* text_area = (my_text_area_t*)area;
  char language[] = "ar";
  char features[] = "liga=0";
  char invalid_language[MY_FONT_SHAPE_MAX_LANGUAGE_BYTES + 2];
  my_font_shape_params_t params = {true, MY_FONT_SCRIPT_ARAB, language,
                                   features};

  ASSERT_NOT_NULL(area);
  ASSERT_EQ(my_text_area_set_shaping_params(area, &params), MY_RET_OK);
  language[0] = 'x';
  features[0] = 'x';
  ASSERT_TRUE(text_area->shaping_params.rtl);
  ASSERT_EQ(text_area->shaping_params.script, MY_FONT_SCRIPT_ARAB);
  ASSERT_STR_EQ(text_area->shaping_params.language, "ar");
  ASSERT_STR_EQ(text_area->shaping_params.features, "liga=0");

  memset(invalid_language, 'a', sizeof(invalid_language));
  invalid_language[sizeof(invalid_language) - 1] = '\0';
  params.language = invalid_language;
  ASSERT_EQ(my_text_area_set_shaping_params(area, &params),
            MY_RET_INVALID_PARAMS);
  ASSERT_STR_EQ(text_area->shaping_params.language, "ar");
  ASSERT_STR_EQ(text_area->shaping_params.features, "liga=0");
  params.language = language;
  params.features = "liga=0,,kern=1";
  ASSERT_EQ(my_text_area_set_shaping_params(area, &params),
            MY_RET_INVALID_PARAMS);
  ASSERT_STR_EQ(text_area->shaping_params.language, "ar");
  ASSERT_STR_EQ(text_area->shaping_params.features, "liga=0");
  ASSERT_EQ(my_text_area_set_shaping_params(area, NULL), MY_RET_OK);
  ASSERT_FALSE(text_area->shaping_params.rtl);
  ASSERT_EQ(text_area->shaping_params.script, 0u);
  ASSERT_TRUE(text_area->shaping_params.language == NULL);
  ASSERT_TRUE(text_area->shaping_params.features == NULL);
  my_widget_unref(area);
}

TEST(text_area_shaping_params_normalize_without_revision_churn)
{
  my_widget_t* area = my_text_area_create(NULL);
  my_text_area_t* text_area = (my_text_area_t*)area;
  my_font_shape_params_t first = {false, MY_FONT_SCRIPT_LATN, "en",
                                  "liga=0,kern=1"};
  my_font_shape_params_t equivalent = {false, MY_FONT_SCRIPT_LATN, "en",
                                       " kern = 1 , liga = 0 "};
  uint64_t revision;

  ASSERT_NOT_NULL(area);
  ASSERT_EQ(my_text_area_set_shaping_params(area, &first), MY_RET_OK);
  revision = text_area->shaping_revision;
  ASSERT_EQ(my_text_area_set_shaping_params(area, &equivalent), MY_RET_OK);
  ASSERT_EQ(text_area->shaping_revision, revision);
  ASSERT_STR_EQ(text_area->shaping_params.features, "kern=1,liga=0");
  my_widget_unref(area);
}

TEST(text_area_rtl_paint_reuses_layout)
{
  text_area_count_alloc_t state = {0};
  my_allocator_t allocator = {&state, text_area_count_alloc,
                              text_area_count_calloc, text_area_count_realloc,
                              text_area_count_free};
  my_widget_t* area = my_text_area_create(&allocator);
  my_text_area_t* text_area = (my_text_area_t*)area;
  my_lcd_t* lcd = my_lcd_mem_create(NULL, 160, 80, MY_PIXEL_FORMAT_BGRA8888);
  my_vgcanvas_t* canvas = my_vgcanvas_soft_create(NULL, lcd);
  size_t before;
  size_t second_frame;
  my_text_layout_t* painted_layout;
  my_event_t event = my_event_init(MY_EVENT_POINTER_DOWN);

  ASSERT_NOT_NULL(area);
  ASSERT_NOT_NULL(lcd);
  ASSERT_NOT_NULL(canvas);
  ASSERT_EQ(my_widget_set_rect(area, &(my_rect_t){0, 0, 80, 54}), MY_RET_OK);
  ASSERT_EQ(my_text_area_set_text(area, "\xD7\x90\xD7\x91\xD7\x92"),
            MY_RET_OK);
  text_area->focused = true;
  text_area->cursor_visible = true;
  before = state.alloc_calls;
  ASSERT_EQ(my_vgcanvas_begin_frame(canvas, NULL), MY_RET_OK);
  area->vtable->on_paint(area, canvas);
  ASSERT_EQ(my_vgcanvas_end_frame(canvas), MY_RET_OK);
  painted_layout = text_area->rtl_layout;
  ASSERT_NOT_NULL(painted_layout);
  event.u.pointer.x = 20;
  event.u.pointer.y = 5;
  event.u.pointer.button = 1;
  ASSERT_EQ(area->vtable->on_event(area, &event), MY_RET_OK);
  ASSERT_TRUE(text_area->rtl_layout == painted_layout);
  before = state.alloc_calls;
  ASSERT_EQ(my_vgcanvas_begin_frame(canvas, NULL), MY_RET_OK);
  area->vtable->on_paint(area, canvas);
  ASSERT_EQ(my_vgcanvas_end_frame(canvas), MY_RET_OK);
  second_frame = state.alloc_calls - before;
  ASSERT_EQ(second_frame, 0u);
  ASSERT_EQ(my_text_area_set_text(area, "\xD7\x93\xD7\x94\xD7\x95"),
            MY_RET_OK);
  before = state.alloc_calls;
  ASSERT_EQ(my_vgcanvas_begin_frame(canvas, NULL), MY_RET_OK);
  area->vtable->on_paint(area, canvas);
  ASSERT_EQ(my_vgcanvas_end_frame(canvas), MY_RET_OK);
  ASSERT_TRUE(state.alloc_calls > before);
  my_vgcanvas_destroy(canvas);
  my_lcd_destroy(lcd);
  my_widget_unref(area);
}

TEST(text_area_rtl_hit_test_reuses_layout)
{
  text_area_count_alloc_t state = {0};
  my_allocator_t allocator = {&state, text_area_count_alloc,
                              text_area_count_calloc, text_area_count_realloc,
                              text_area_count_free};
  my_widget_t* area = my_text_area_create(&allocator);
  my_event_t event = my_event_init(MY_EVENT_POINTER_DOWN);
  size_t before;

  ASSERT_NOT_NULL(area);
  ASSERT_EQ(my_widget_set_rect(area, &(my_rect_t){0, 0, 80, 54}), MY_RET_OK);
  ASSERT_EQ(my_text_area_set_text(area, "\xD7\x90\xD7\x91\xD7\x92"),
            MY_RET_OK);
  event.u.pointer.x = 20;
  event.u.pointer.y = 5;
  event.u.pointer.button = 1;
  before = state.alloc_calls;
  ASSERT_EQ(area->vtable->on_event(area, &event), MY_RET_OK);
  ASSERT_TRUE(state.alloc_calls > before);
  before = state.alloc_calls;
  ASSERT_EQ(area->vtable->on_event(area, &event), MY_RET_OK);
  ASSERT_EQ(state.alloc_calls - before, 0u);
  my_widget_unref(area);
}

TEST(text_area_rtl_paint_caches_multiple_visual_lines)
{
  text_area_count_alloc_t state = {0};
  my_allocator_t allocator = {&state, text_area_count_alloc,
                              text_area_count_calloc, text_area_count_realloc,
                              text_area_count_free};
  my_widget_t* area = my_text_area_create(&allocator);
  my_lcd_t* lcd = my_lcd_mem_create(NULL, 160, 120, MY_PIXEL_FORMAT_BGRA8888);
  my_vgcanvas_t* canvas = my_vgcanvas_soft_create(NULL, lcd);
  size_t before;
  size_t second_frame;

  ASSERT_NOT_NULL(area);
  ASSERT_NOT_NULL(lcd);
  ASSERT_NOT_NULL(canvas);
  ASSERT_EQ(my_widget_set_rect(area, &(my_rect_t){0, 0, 160, 100}), MY_RET_OK);
  ASSERT_EQ(my_text_area_set_text(
                area,
                "\xD7\x90\xD7\x91\n\xD7\x92\xD7\x93\n\xD7\x94\xD7\x95\n\xD7\x96\xD7\x97"),
            MY_RET_OK);
  ASSERT_EQ(my_vgcanvas_begin_frame(canvas, NULL), MY_RET_OK);
  area->vtable->on_paint(area, canvas);
  ASSERT_EQ(my_vgcanvas_end_frame(canvas), MY_RET_OK);

  before = state.alloc_calls;
  ASSERT_EQ(my_vgcanvas_begin_frame(canvas, NULL), MY_RET_OK);
  area->vtable->on_paint(area, canvas);
  ASSERT_EQ(my_vgcanvas_end_frame(canvas), MY_RET_OK);
  second_frame = state.alloc_calls - before;
  ASSERT_EQ(second_frame, 0u);

  my_vgcanvas_destroy(canvas);
  my_lcd_destroy(lcd);
  my_widget_unref(area);
}

TEST(text_area_rtl_syntax_colors_tokens)
{
  my_widget_t* plain = my_text_area_create(NULL);
  my_widget_t* highlighted = my_text_area_create(NULL);
  my_font_t* font = my_font_bitmap_create(NULL);
  my_lcd_t* plain_lcd = my_lcd_mem_create(NULL, 160, 80, MY_PIXEL_FORMAT_BGRA8888);
  my_lcd_t* highlighted_lcd =
      my_lcd_mem_create(NULL, 160, 80, MY_PIXEL_FORMAT_BGRA8888);
  my_vgcanvas_t* plain_canvas = my_vgcanvas_soft_create(NULL, plain_lcd);
  my_vgcanvas_t* highlighted_canvas =
      my_vgcanvas_soft_create(NULL, highlighted_lcd);
  uint8_t* plain_pixels;
  uint8_t* highlighted_pixels;
  uint32_t plain_stride;
  uint32_t highlighted_stride;
  size_t bytes;

  ASSERT_NOT_NULL(plain);
  ASSERT_NOT_NULL(highlighted);
  ASSERT_NOT_NULL(font);
  ASSERT_NOT_NULL(plain_lcd);
  ASSERT_NOT_NULL(highlighted_lcd);
  ASSERT_NOT_NULL(plain_canvas);
  ASSERT_NOT_NULL(highlighted_canvas);
  ASSERT_EQ(my_widget_set_rect(plain, &(my_rect_t){0, 0, 80, 54}), MY_RET_OK);
  ASSERT_EQ(my_widget_set_rect(highlighted, &(my_rect_t){0, 0, 80, 54}),
            MY_RET_OK);
  my_text_area_set_font(plain, font, 16);
  my_text_area_set_font(highlighted, font, 16);
  ASSERT_EQ(my_vgcanvas_set_font(plain_canvas, font, 16), MY_RET_OK);
  ASSERT_EQ(my_vgcanvas_set_font(highlighted_canvas, font, 16), MY_RET_OK);
  ASSERT_EQ(my_text_area_set_text(plain, "true \xD7\x90"), MY_RET_OK);
  ASSERT_EQ(my_text_area_set_text(highlighted, "true \xD7\x90"), MY_RET_OK);
  ASSERT_EQ(my_text_area_set_syntax_enabled(highlighted, true), MY_RET_OK);
  ASSERT_EQ(my_text_area_set_syntax_language(highlighted, MY_SYNTAX_YAML),
            MY_RET_OK);
  ASSERT_EQ(my_vgcanvas_begin_frame(plain_canvas, NULL), MY_RET_OK);
  plain->vtable->on_paint(plain, plain_canvas);
  ASSERT_EQ(my_vgcanvas_end_frame(plain_canvas), MY_RET_OK);
  ASSERT_EQ(my_vgcanvas_begin_frame(highlighted_canvas, NULL), MY_RET_OK);
  highlighted->vtable->on_paint(highlighted, highlighted_canvas);
  ASSERT_EQ(my_vgcanvas_end_frame(highlighted_canvas), MY_RET_OK);
  plain_pixels = my_lcd_mem_get_buffer(plain_lcd);
  highlighted_pixels = my_lcd_mem_get_buffer(highlighted_lcd);
  plain_stride = my_lcd_mem_get_stride(plain_lcd);
  highlighted_stride = my_lcd_mem_get_stride(highlighted_lcd);
  ASSERT_EQ(plain_stride, highlighted_stride);
  bytes = (size_t)plain_stride * 80u;
  ASSERT_TRUE(memcmp(plain_pixels, highlighted_pixels, bytes) != 0);
  my_vgcanvas_destroy(plain_canvas);
  my_vgcanvas_destroy(highlighted_canvas);
  my_lcd_destroy(plain_lcd);
  my_lcd_destroy(highlighted_lcd);
  my_font_destroy(font);
  my_widget_unref(plain);
  my_widget_unref(highlighted);
}

TEST(text_area_wrap_reuses_unchanged_prefix_after_edit)
{
  my_widget_t* area = my_text_area_create(NULL);
  const my_visual_line_t* prefix;
  my_event_t event = my_event_init(MY_EVENT_KEY_DOWN);

  ASSERT_NOT_NULL(area);
  ASSERT_EQ(my_widget_set_rect(area, &(my_rect_t){0, 0, 20, 80}), MY_RET_OK);
  ASSERT_EQ(my_text_area_set_wrap(area, true), MY_RET_OK);
  ASSERT_EQ(my_text_area_set_text(area, "aa\nbb\ncc"), MY_RET_OK);
  prefix = my_text_area_visual_line_at(area, 0);
  ASSERT_NOT_NULL(prefix);
  ((my_text_area_t*)area)->cursor_row = 1;
  ((my_text_area_t*)area)->cursor_col = 1;
  ((my_text_area_t*)area)->anchor_row = 1;
  ((my_text_area_t*)area)->anchor_col = 1;
  ((my_text_area_t*)area)->focused = true;
  event.u.key.key = 'x';
  ASSERT_EQ(area->vtable->on_event(area, &event), MY_RET_OK);
  ASSERT_STR_EQ(my_text_area_get_text(area), "aa\nbxb\ncc");
  ASSERT_TRUE(my_text_area_visual_line_at(area, 0) == prefix);
  my_widget_unref(area);
}

TEST(text_area_wrap_reuses_unchanged_suffix_after_single_line_edit)
{
  my_widget_t* area = my_text_area_create(NULL);
  const my_visual_line_t* suffix = NULL;
  my_event_t event = my_event_init(MY_EVENT_KEY_DOWN);
  size_t i;

  ASSERT_NOT_NULL(area);
  ASSERT_EQ(my_widget_set_rect(area, &(my_rect_t){0, 0, 28, 100}), MY_RET_OK);
  ASSERT_EQ(my_text_area_set_wrap(area, true), MY_RET_OK);
  ASSERT_EQ(my_text_area_set_text(area, "aaaa\nbbbb\ncccc\ndddd"),
            MY_RET_OK);
  for (i = 0u; i < my_text_area_visual_line_count(area); i++) {
    const my_visual_line_t* line = my_text_area_visual_line_at(area, i);
    if (line != NULL && line->phys == 3u) {
      suffix = line;
      break;
    }
  }
  ASSERT_NOT_NULL(suffix);
  ((my_text_area_t*)area)->cursor_row = 1u;
  ((my_text_area_t*)area)->cursor_col = 1u;
  ((my_text_area_t*)area)->anchor_row = 1u;
  ((my_text_area_t*)area)->anchor_col = 1u;
  ((my_text_area_t*)area)->focused = true;
  event.u.key.key = 'x';
  ASSERT_EQ(area->vtable->on_event(area, &event), MY_RET_OK);
  ASSERT_STR_EQ(my_text_area_get_text(area), "aaaa\nbxbbb\ncccc\ndddd");
  {
    bool found_suffix = false;
    for (i = 0u; i < my_text_area_visual_line_count(area); i++) {
      const my_visual_line_t* line = my_text_area_visual_line_at(area, i);
      if (line != NULL && line->phys == 3u) {
        found_suffix = line == suffix;
        break;
      }
    }
    ASSERT_TRUE(found_suffix);
  }
  my_widget_unref(area);
}

TEST(text_area_wrap_reuses_suffix_after_newline_edit)
{
  my_widget_t* area = my_text_area_create(NULL);
  my_text_area_t* text_area = (my_text_area_t*)area;
  my_event_t event = my_event_init(MY_EVENT_KEY_DOWN);
  const my_visual_line_t* suffix = NULL;
  size_t i;

  ASSERT_NOT_NULL(area);
  ASSERT_EQ(my_widget_set_rect(area, &(my_rect_t){0, 0, 100, 120}), MY_RET_OK);
  ASSERT_EQ(my_text_area_set_wrap(area, true), MY_RET_OK);
  ASSERT_EQ(my_text_area_set_text(area, "aaaa\nbbbb\ncccc\ndddd"),
            MY_RET_OK);
  ASSERT_EQ(my_text_area_visual_line_count(area), 4u);
  suffix = my_text_area_visual_line_at(area, 2u);
  ASSERT_NOT_NULL(suffix);
  ASSERT_EQ(suffix->phys, 2u);

  text_area->cursor_row = 1u;
  text_area->cursor_col = 2u;
  text_area->anchor_row = 1u;
  text_area->anchor_col = 2u;
  text_area->focused = true;
  event.u.key.key = MY_KEY_RETURN;
  ASSERT_EQ(area->vtable->on_event(area, &event), MY_RET_OK);
  ASSERT_STR_EQ(my_text_area_get_text(area), "aaaa\nbb\nbb\ncccc\ndddd");
  ASSERT_EQ(my_text_area_visual_line_count(area), 5u);
  for (i = 0u; i < my_text_area_visual_line_count(area); ++i) {
    const my_visual_line_t* line = my_text_area_visual_line_at(area, i);
    if (line != NULL && line->phys == 3u) {
      ASSERT_TRUE(line == suffix);
      break;
    }
  }
  ASSERT_EQ(i < my_text_area_visual_line_count(area), true);
  my_widget_unref(area);
}

TEST(text_area_wrap_reuses_suffix_after_newline_delete)
{
  my_widget_t* area = my_text_area_create(NULL);
  my_text_area_t* text_area = (my_text_area_t*)area;
  my_event_t event = my_event_init(MY_EVENT_KEY_DOWN);
  const my_visual_line_t* suffix;
  size_t i;

  ASSERT_NOT_NULL(area);
  ASSERT_EQ(my_widget_set_rect(area, &(my_rect_t){0, 0, 100, 120}), MY_RET_OK);
  ASSERT_EQ(my_text_area_set_wrap(area, true), MY_RET_OK);
  ASSERT_EQ(my_text_area_set_text(area, "aaaa\nbbbb\ncccc\ndddd"),
            MY_RET_OK);
  ASSERT_EQ(my_text_area_visual_line_count(area), 4u);
  suffix = my_text_area_visual_line_at(area, 3u);
  ASSERT_NOT_NULL(suffix);
  ASSERT_EQ(suffix->phys, 3u);

  text_area->cursor_row = 2u;
  text_area->cursor_col = 0u;
  text_area->anchor_row = 2u;
  text_area->anchor_col = 0u;
  text_area->focused = true;
  event.u.key.key = MY_KEY_BACKSPACE;
  ASSERT_EQ(area->vtable->on_event(area, &event), MY_RET_OK);
  ASSERT_STR_EQ(my_text_area_get_text(area), "aaaa\nbbbbcccc\ndddd");
  ASSERT_EQ(my_text_area_visual_line_count(area), 3u);
  for (i = 0u; i < my_text_area_visual_line_count(area); ++i) {
    const my_visual_line_t* line = my_text_area_visual_line_at(area, i);
    if (line != NULL && line->phys == 2u) {
      ASSERT_TRUE(line == suffix);
      break;
    }
  }
  ASSERT_EQ(i < my_text_area_visual_line_count(area), true);
  my_widget_unref(area);
}

TEST(text_area_wrap_reuses_suffix_after_multibyte_edit)
{
  my_widget_t* area = my_text_area_create(NULL);
  my_text_area_t* text_area = (my_text_area_t*)area;
  my_event_t event = my_event_init(MY_EVENT_IME_COMMIT);
  const my_visual_line_t* suffix;
  size_t i;

  ASSERT_NOT_NULL(area);
  ASSERT_EQ(my_widget_set_rect(area, &(my_rect_t){0, 0, 100, 120}), MY_RET_OK);
  ASSERT_EQ(my_text_area_set_wrap(area, true), MY_RET_OK);
  ASSERT_EQ(my_text_area_set_text(area, "aaaa\nbbbb\ncccc"), MY_RET_OK);
  suffix = my_text_area_visual_line_at(area, 2u);
  ASSERT_NOT_NULL(suffix);
  text_area->cursor_row = 1u;
  text_area->cursor_col = 1u;
  text_area->anchor_row = 1u;
  text_area->anchor_col = 1u;
  text_area->focused = true;
  event.u.ime.text = "\xE7\x95\x8C";
  ASSERT_EQ(area->vtable->on_event(area, &event), MY_RET_OK);
  ASSERT_STR_EQ(my_text_area_get_text(area),
                "aaaa\nb\xE7\x95\x8C" "bbb\ncccc");
  for (i = 0u; i < my_text_area_visual_line_count(area); ++i) {
    const my_visual_line_t* line = my_text_area_visual_line_at(area, i);
    if (line != NULL && line->phys == 2u) {
      ASSERT_TRUE(line == suffix);
      ASSERT_EQ(line->start_byte, 0u);
      ASSERT_EQ(line->len_bytes, 4u);
      ASSERT_EQ(line->start_cp, 0u);
      ASSERT_EQ(line->len_cp, 4u);
      break;
    }
  }
  ASSERT_EQ(i < my_text_area_visual_line_count(area), true);
  my_widget_unref(area);
}

TEST(text_area_wrap_dirty_cache_disables_suffix_reuse)
{
  my_widget_t* area = my_text_area_create(NULL);
  my_text_area_t* text_area = (my_text_area_t*)area;
  my_event_t event = my_event_init(MY_EVENT_KEY_DOWN);
  const my_visual_line_t* old_suffix;
  const my_visual_line_t* new_suffix = NULL;
  size_t i;

  ASSERT_NOT_NULL(area);
  ASSERT_EQ(my_widget_set_rect(area, &(my_rect_t){0, 0, 40, 120}), MY_RET_OK);
  ASSERT_EQ(my_text_area_set_wrap(area, true), MY_RET_OK);
  ASSERT_EQ(my_text_area_set_text(area, "aaaa\nbbbb\ncccc"), MY_RET_OK);
  old_suffix = my_text_area_visual_line_at(area, 2u);
  ASSERT_NOT_NULL(old_suffix);
  text_area->vlines_dirty = true;
  text_area->vlines_dirty_from = 0u;
  text_area->cursor_row = 1u;
  text_area->cursor_col = 1u;
  text_area->anchor_row = 1u;
  text_area->anchor_col = 1u;
  text_area->focused = true;
  event.u.key.key = MY_KEY_RETURN;
  ASSERT_EQ(area->vtable->on_event(area, &event), MY_RET_OK);
  for (i = 0u; i < my_text_area_visual_line_count(area); ++i) {
    const my_visual_line_t* line = my_text_area_visual_line_at(area, i);
    if (line != NULL && line->phys == 2u) {
      new_suffix = line;
      break;
    }
  }
  ASSERT_NOT_NULL(new_suffix);
  ASSERT_TRUE(new_suffix != old_suffix);
  my_widget_unref(area);
}

TEST(text_area_wrap_suffix_reuse_oom_preserves_old_objects)
{
  text_area_fail_alloc_t state = {false, false};
  my_allocator_t base = {&state, text_area_fail_alloc,
                         text_area_fail_calloc, text_area_fail_realloc,
                         text_area_fail_free};
  my_allocator_t* allocator = my_allocator_debug_create(&base);
  my_widget_t* area;
  my_text_area_t* text_area;
  my_event_t event = my_event_init(MY_EVENT_KEY_DOWN);
  const my_visual_line_t* suffix;
  int live_before;

  ASSERT_NOT_NULL(allocator);
  area = my_text_area_create(allocator);
  ASSERT_NOT_NULL(area);
  text_area = (my_text_area_t*)area;
  ASSERT_EQ(my_widget_set_rect(area, &(my_rect_t){0, 0, 100, 120}), MY_RET_OK);
  ASSERT_EQ(my_text_area_set_wrap(area, true), MY_RET_OK);
  ASSERT_EQ(my_text_area_set_text(area, "aaaa\nbbbb\ncccc\ndddd"),
            MY_RET_OK);
  suffix = my_text_area_visual_line_at(area, 2u);
  ASSERT_NOT_NULL(suffix);
  text_area->cursor_row = 1u;
  text_area->cursor_col = 2u;
  text_area->anchor_row = 1u;
  text_area->anchor_col = 2u;
  text_area->focused = true;
  event.u.key.key = MY_KEY_RETURN;
  ASSERT_EQ(area->vtable->on_event(area, &event), MY_RET_OK);
  live_before = my_allocator_debug_leak_count(allocator);
  state.fail_realloc = true;
  ASSERT_EQ(my_text_area_visual_line_count(area), 4u);
  ASSERT_TRUE(my_text_area_visual_line_at(area, 2u) == suffix);
  ASSERT_EQ(my_allocator_debug_leak_count(allocator), live_before);
  state.fail_realloc = false;
  ASSERT_EQ(my_text_area_visual_line_count(area), 5u);
  ASSERT_TRUE(my_text_area_visual_line_at(area, 3u) == suffix);
  my_widget_unref(area);
  ASSERT_EQ(my_allocator_debug_leak_count(allocator), 0);
  my_allocator_debug_destroy(allocator);
}

TEST(text_area_wrap_single_line_edit_shapes_only_changed_row)
{
  text_area_variable_font_t font = {{&text_area_variable_font_vtable}, 0, 0};
  my_widget_t* area = my_text_area_create(NULL);
  my_text_area_t* text_area = (my_text_area_t*)area;
  my_event_t event = my_event_init(MY_EVENT_KEY_DOWN);
  size_t before;

  ASSERT_NOT_NULL(area);
  ASSERT_EQ(my_widget_set_rect(area, &(my_rect_t){0, 0, 28, 100}), MY_RET_OK);
  my_text_area_set_font(area, (my_font_t*)&font, 16);
  ASSERT_EQ(my_text_area_set_wrap(area, true), MY_RET_OK);
  ASSERT_EQ(my_text_area_set_text(area, "BBBB\nBBBB\nBBBB\nBBBB"),
            MY_RET_OK);
  ASSERT_EQ(my_text_area_visual_line_count(area), 16u);
  text_area->cursor_row = 1u;
  text_area->cursor_col = 1u;
  text_area->anchor_row = 1u;
  text_area->anchor_col = 1u;
  text_area->focused = true;
  before = font.glyph_calls;
  event.u.key.key = 'B';
  ASSERT_EQ(area->vtable->on_event(area, &event), MY_RET_OK);
  ASSERT_EQ(my_text_area_visual_line_count(area), 17u);
  ASSERT_EQ(font.glyph_calls - before, 5u);
  my_widget_unref(area);
}

TEST(text_area_wrap_preserves_trailing_empty_line_on_single_line_edit)
{
  my_widget_t* area = my_text_area_create(NULL);
  my_text_area_t* text_area = (my_text_area_t*)area;
  my_event_t event = my_event_init(MY_EVENT_KEY_DOWN);
  const my_visual_line_t* trailing;

  ASSERT_NOT_NULL(area);
  ASSERT_EQ(my_widget_set_rect(area, &(my_rect_t){0, 0, 40, 80}), MY_RET_OK);
  ASSERT_EQ(my_text_area_set_wrap(area, true), MY_RET_OK);
  ASSERT_EQ(my_text_area_set_text(area, "aa\n"), MY_RET_OK);
  ASSERT_EQ(my_text_area_line_count(area), 2u);
  ASSERT_EQ(my_text_area_visual_line_count(area), 2u);
  trailing = my_text_area_visual_line_at(area, 1u);
  ASSERT_NOT_NULL(trailing);
  ASSERT_EQ(trailing->phys, 1u);
  ASSERT_EQ(trailing->len_cp, 0u);

  text_area->cursor_row = 0u;
  text_area->cursor_col = 1u;
  text_area->anchor_row = 0u;
  text_area->anchor_col = 1u;
  text_area->focused = true;
  event.u.key.key = 'b';
  ASSERT_EQ(area->vtable->on_event(area, &event), MY_RET_OK);
  ASSERT_STR_EQ(my_text_area_get_text(area), "aba\n");
  ASSERT_EQ(my_text_area_line_count(area), 2u);
  ASSERT_EQ(my_text_area_visual_line_count(area), 2u);
  ASSERT_TRUE(my_text_area_visual_line_at(area, 1u) == trailing);
  ASSERT_EQ(my_text_area_visual_line_at(area, 1u)->len_cp, 0u);
  my_widget_unref(area);
}

TEST(text_area_wrap_represents_empty_document_as_empty_visual_line)
{
  my_widget_t* area = my_text_area_create(NULL);
  const my_visual_line_t* line;

  ASSERT_NOT_NULL(area);
  ASSERT_EQ(my_widget_set_rect(area, &(my_rect_t){0, 0, 40, 80}), MY_RET_OK);
  ASSERT_EQ(my_text_area_set_wrap(area, true), MY_RET_OK);
  ASSERT_EQ(my_text_area_set_text(area, ""), MY_RET_OK);
  ASSERT_EQ(my_text_area_line_count(area), 1u);
  ASSERT_EQ(my_text_area_visual_line_count(area), 1u);
  line = my_text_area_visual_line_at(area, 0u);
  ASSERT_NOT_NULL(line);
  ASSERT_EQ(line->phys, 0u);
  ASSERT_EQ(line->len_cp, 0u);
  ASSERT_EQ(line->len_bytes, 0u);
  my_widget_unref(area);
}

TEST(text_area_wrap_keeps_all_consecutive_empty_physical_lines)
{
  my_widget_t* area = my_text_area_create(NULL);
  const my_visual_line_t* first_empty;
  const my_visual_line_t* second_empty;

  ASSERT_NOT_NULL(area);
  ASSERT_EQ(my_widget_set_rect(area, &(my_rect_t){0, 0, 28, 80}), MY_RET_OK);
  ASSERT_EQ(my_text_area_set_wrap(area, true), MY_RET_OK);
  ASSERT_EQ(my_text_area_set_text(area, "a\n\n\nb"), MY_RET_OK);
  ASSERT_EQ(my_text_area_line_count(area), 4u);
  ASSERT_EQ(my_text_area_visual_line_count(area), 4u);
  first_empty = my_text_area_visual_line_at(area, 1u);
  second_empty = my_text_area_visual_line_at(area, 2u);
  ASSERT_NOT_NULL(first_empty);
  ASSERT_NOT_NULL(second_empty);
  ASSERT_EQ(first_empty->phys, 1u);
  ASSERT_EQ(second_empty->phys, 2u);
  ASSERT_EQ(first_empty->len_cp, 0u);
  ASSERT_EQ(second_empty->len_cp, 0u);
  ASSERT_EQ(my_text_area_visual_line_at(area, 3u)->phys, 3u);
  my_widget_unref(area);
}

TEST(text_area_wrap_last_line_edit_does_not_retain_stale_visual_lines)
{
  my_widget_t* area = my_text_area_create(NULL);
  my_text_area_t* text_area = (my_text_area_t*)area;
  my_event_t event = my_event_init(MY_EVENT_KEY_DOWN);

  ASSERT_NOT_NULL(area);
  ASSERT_EQ(my_widget_set_rect(area, &(my_rect_t){0, 0, 40, 80}), MY_RET_OK);
  ASSERT_EQ(my_text_area_set_wrap(area, true), MY_RET_OK);
  ASSERT_EQ(my_text_area_set_text(area, "aa\nbb"), MY_RET_OK);
  ASSERT_EQ(my_text_area_visual_line_count(area), 2u);
  text_area->cursor_row = 1u;
  text_area->cursor_col = 1u;
  text_area->anchor_row = 1u;
  text_area->anchor_col = 1u;
  text_area->focused = true;
  event.u.key.key = 'c';
  ASSERT_EQ(area->vtable->on_event(area, &event), MY_RET_OK);
  ASSERT_STR_EQ(my_text_area_get_text(area), "aa\nbcb");
  ASSERT_EQ(my_text_area_line_count(area), 2u);
  ASSERT_EQ(my_text_area_visual_line_count(area), 2u);
  ASSERT_EQ(my_text_area_visual_line_at(area, 0u)->phys, 0u);
  ASSERT_EQ(my_text_area_visual_line_at(area, 1u)->phys, 1u);
  my_widget_unref(area);
}

TEST(text_area_wrap_cross_line_delete_rebuilds_physical_rows)
{
  my_widget_t* area = my_text_area_create(NULL);
  my_text_area_t* text_area = (my_text_area_t*)area;
  my_event_t event = my_event_init(MY_EVENT_KEY_DOWN);

  ASSERT_NOT_NULL(area);
  ASSERT_EQ(my_widget_set_rect(area, &(my_rect_t){0, 0, 28, 80}), MY_RET_OK);
  ASSERT_EQ(my_text_area_set_wrap(area, true), MY_RET_OK);
  ASSERT_EQ(my_text_area_set_text(area, "aa\nbb\ncc"), MY_RET_OK);
  ASSERT_EQ(my_text_area_visual_line_count(area), 3u);
  text_area->cursor_row = 1u;
  text_area->cursor_col = 0u;
  text_area->anchor_row = 1u;
  text_area->anchor_col = 0u;
  text_area->focused = true;
  event.u.key.key = MY_KEY_BACKSPACE;
  ASSERT_EQ(area->vtable->on_event(area, &event), MY_RET_OK);
  ASSERT_STR_EQ(my_text_area_get_text(area), "aabb\ncc");
  ASSERT_EQ(my_text_area_line_count(area), 2u);
  ASSERT_EQ(my_text_area_visual_line_count(area), 3u);
  ASSERT_EQ(my_text_area_visual_line_at(area, 0u)->phys, 0u);
  ASSERT_EQ(my_text_area_visual_line_at(area, 1u)->phys, 0u);
  ASSERT_EQ(my_text_area_visual_line_at(area, 2u)->phys, 1u);
  my_widget_unref(area);
}

TEST(text_area_wrap_rebuilds_dirty_suffix_as_one_paragraph)
{
  text_area_count_alloc_t state = {0};
  my_allocator_t allocator = {&state, text_area_count_alloc,
                              text_area_count_calloc, text_area_count_realloc,
                              text_area_count_free};
  my_widget_t* area = my_text_area_create(&allocator);
  my_text_area_t* text_area = (my_text_area_t*)area;
  my_event_t event = my_event_init(MY_EVENT_KEY_DOWN);
  size_t before;
  size_t rebuild_allocs;

  ASSERT_NOT_NULL(area);
  ASSERT_EQ(my_widget_set_rect(area, &(my_rect_t){0, 0, 28, 80}), MY_RET_OK);
  ASSERT_EQ(my_text_area_set_wrap(area, true), MY_RET_OK);
  ASSERT_EQ(my_text_area_set_text(area, "aaaa\nbbbb\ncccc"), MY_RET_OK);
  ASSERT_EQ(my_text_area_visual_line_count(area), 6u);
  text_area->cursor_row = 1u;
  text_area->cursor_col = 1u;
  text_area->anchor_row = 1u;
  text_area->anchor_col = 1u;
  text_area->focused = true;
  event.u.key.key = 'x';
  ASSERT_EQ(area->vtable->on_event(area, &event), MY_RET_OK);
  before = state.alloc_calls;
  ASSERT_EQ(my_text_area_visual_line_count(area), 7u);
  rebuild_allocs = state.alloc_calls - before;
  ASSERT_TRUE(rebuild_allocs <= 24u);
  ASSERT_EQ(my_text_area_visual_line_at(area, 0)->phys, 0u);
  ASSERT_EQ(my_text_area_visual_line_at(area, 2)->phys, 1u);
  ASSERT_EQ(my_text_area_visual_line_at(area, 5)->phys, 2u);
  my_widget_unref(area);
}

TEST(text_area_wrap_suffix_oom_releases_candidate_lines)
{
  text_area_fail_alloc_t state = {false, false};
  my_allocator_t base = {&state, text_area_fail_alloc,
                         text_area_fail_calloc, text_area_fail_realloc,
                         text_area_fail_free};
  my_allocator_t* allocator = my_allocator_debug_create(&base);
  my_widget_t* area;
  int live_before;
  my_event_t event = my_event_init(MY_EVENT_KEY_DOWN);

  ASSERT_NOT_NULL(allocator);
  area = my_text_area_create(allocator);
  ASSERT_NOT_NULL(area);
  ASSERT_EQ(my_widget_set_rect(area, &(my_rect_t){0, 0, 28, 80}), MY_RET_OK);
  ASSERT_EQ(my_text_area_set_wrap(area, true), MY_RET_OK);
  ASSERT_EQ(my_text_area_set_text(area, "aaaa\nbbbb\ncccczzzz"), MY_RET_OK);
  ASSERT_EQ(my_text_area_visual_line_count(area), 8u);
  ((my_text_area_t*)area)->cursor_row = 1u;
  ((my_text_area_t*)area)->cursor_col = 1u;
  ((my_text_area_t*)area)->anchor_row = 1u;
  ((my_text_area_t*)area)->anchor_col = 1u;
  ((my_text_area_t*)area)->focused = true;
  event.u.key.key = 'x';
  ASSERT_EQ(area->vtable->on_event(area, &event), MY_RET_OK);
  live_before = my_allocator_debug_leak_count(allocator);
  state.fail_realloc = true;
  ASSERT_EQ(my_text_area_visual_line_count(area), 8u);
  ASSERT_EQ(my_allocator_debug_leak_count(allocator), live_before);
  state.fail_realloc = false;
  ASSERT_EQ(my_text_area_visual_line_count(area), 9u);
  my_widget_unref(area);
  ASSERT_EQ(my_allocator_debug_leak_count(allocator), 0);
  my_allocator_debug_destroy(allocator);
}

TEST(text_area_line_number_gutter_has_bounded_width)
{
  my_widget_t* area = my_text_area_create(NULL);

  ASSERT_NOT_NULL(area);
  ASSERT_FALSE(my_text_area_line_numbers_enabled(area));
  ASSERT_EQ(my_text_area_content_left(area), 4);
  ASSERT_EQ(my_text_area_set_line_numbers(area, true), MY_RET_OK);
  ASSERT_TRUE(my_text_area_line_numbers_enabled(area));
  ASSERT_TRUE(my_text_area_content_left(area) > 4);
  ASSERT_EQ(my_text_area_set_text(area, "a\nb\nc\nd\ne\nf\ng\nh\ni\nj\n"),
            MY_RET_OK);
  ASSERT_TRUE(my_text_area_content_left(area) >= 20);
  ASSERT_EQ(my_text_area_set_line_numbers(area, false), MY_RET_OK);
  ASSERT_EQ(my_text_area_content_left(area), 4);
  my_widget_unref(area);
}

TEST(text_area_line_numbers_reduce_wrap_width)
{
  my_widget_t* area = my_text_area_create(NULL);

  ASSERT_NOT_NULL(area);
  ASSERT_EQ(my_widget_set_rect(area, &(my_rect_t){0, 0, 28, 80}), MY_RET_OK);
  ASSERT_EQ(my_text_area_set_wrap(area, true), MY_RET_OK);
  ASSERT_EQ(my_text_area_set_text(area, "abcd"), MY_RET_OK);
  ASSERT_EQ(my_text_area_visual_line_count(area), 2u);
  ASSERT_EQ(my_text_area_set_line_numbers(area, true), MY_RET_OK);
  ASSERT_EQ(my_text_area_visual_line_count(area), 4u);
  my_widget_unref(area);
}

TEST(text_area_folded_range_hides_only_inner_physical_lines)
{
  my_widget_t* area = my_text_area_create(NULL);
  const my_visual_line_t* line;

  ASSERT_NOT_NULL(area);
  ASSERT_EQ(my_text_area_set_text(area, "a\nbb\nccc\ndddd"), MY_RET_OK);
  ASSERT_EQ(my_text_area_visual_line_count(area), 4u);
  ASSERT_EQ(my_text_area_set_folded_range(area, 1, 2, true), MY_RET_OK);
  ASSERT_TRUE(my_text_area_is_folded(area, 1));
  ASSERT_EQ(my_text_area_visual_line_count(area), 3u);
  line = my_text_area_visual_line_at(area, 1);
  ASSERT_NOT_NULL(line);
  ASSERT_EQ(line->phys, 1u);
  line = my_text_area_visual_line_at(area, 2);
  ASSERT_NOT_NULL(line);
  ASSERT_EQ(line->phys, 3u);
  ASSERT_EQ(line->len_cp, 4u);
  ASSERT_EQ(my_text_area_set_folded_range(area, 1, 2, false), MY_RET_OK);
  ASSERT_FALSE(my_text_area_is_folded(area, 1));
  ASSERT_EQ(my_text_area_visual_line_count(area), 4u);
  my_widget_unref(area);
}

TEST(text_area_folded_range_rejects_invalid_or_overlapping_ranges)
{
  my_widget_t* area = my_text_area_create(NULL);

  ASSERT_NOT_NULL(area);
  ASSERT_EQ(my_text_area_set_text(area, "a\nb\nc\nd\ne"), MY_RET_OK);
  ASSERT_EQ(my_text_area_set_folded_range(area, 2, 2, true),
            MY_RET_INVALID_PARAMS);
  ASSERT_EQ(my_text_area_set_folded_range(area, 3, 9, true),
            MY_RET_INVALID_PARAMS);
  ASSERT_EQ(my_text_area_set_folded_range(area, 1, 3, true), MY_RET_OK);
  ASSERT_EQ(my_text_area_set_folded_range(area, 2, 4, true),
            MY_RET_INVALID_PARAMS);
  ASSERT_EQ(my_text_area_set_folded_range(area, 1, 4, false),
            MY_RET_INVALID_PARAMS);
  my_widget_unref(area);
}

TEST(text_area_nested_fold_ranges_preserve_containment)
{
  my_widget_t* area = my_text_area_create(NULL);
  const my_visual_line_t* line;
  ASSERT_NOT_NULL(area);
  ASSERT_EQ(my_text_area_set_text(area, "a\nb\nc\nd\ne\nf"), MY_RET_OK);
  ASSERT_EQ(my_text_area_set_folded_range(area, 0, 5, true), MY_RET_OK);
  ASSERT_EQ(my_text_area_set_folded_range(area, 1, 3, true), MY_RET_OK);
  ASSERT_TRUE(my_text_area_is_folded(area, 0));
  ASSERT_TRUE(my_text_area_is_folded(area, 1));
  ASSERT_EQ(my_text_area_visual_line_count(area), 1u);
  ASSERT_EQ(my_text_area_set_folded_range(area, 0, 5, false), MY_RET_OK);
  ASSERT_EQ(my_text_area_visual_line_count(area), 4u);
  line = my_text_area_visual_line_at(area, 1);
  ASSERT_NOT_NULL(line);
  ASSERT_EQ(line->phys, 1u);
  ASSERT_EQ(my_text_area_set_folded_range(area, 1, 3, false), MY_RET_OK);
  ASSERT_EQ(my_text_area_visual_line_count(area), 6u);
  my_widget_unref(area);
}

TEST(text_area_fold_state_yaml_roundtrip_and_transaction)
{
  my_widget_t* area = my_text_area_create(NULL);
  char* yaml = NULL;
  ASSERT_NOT_NULL(area);
  ASSERT_EQ(my_text_area_set_text(area, "a\nb\nc\nd\ne\nf"), MY_RET_OK);
  ASSERT_EQ(my_text_area_set_folded_range(area, 0, 5, true), MY_RET_OK);
  ASSERT_EQ(my_text_area_set_folded_range(area, 1, 3, true), MY_RET_OK);
  ASSERT_EQ(my_text_area_folds_to_yaml(area, NULL, &yaml), MY_RET_OK);
  ASSERT_NOT_NULL(yaml);
  ASSERT_STR_EQ(yaml, "version: 1\nfolds:\n  - start: 0\n    end: 5\n  - start: 1\n    end: 3\n");
  ASSERT_EQ(my_text_area_set_folded_range(area, 0, 5, false), MY_RET_OK);
  ASSERT_EQ(my_text_area_set_folded_range(area, 1, 3, false), MY_RET_OK);
  ASSERT_EQ(my_text_area_folds_from_yaml(area, yaml), MY_RET_OK);
  ASSERT_TRUE(my_text_area_is_folded(area, 0));
  ASSERT_TRUE(my_text_area_is_folded(area, 1));
  ASSERT_EQ(my_text_area_visual_line_count(area), 1u);
  ASSERT_EQ(my_text_area_folds_from_yaml(area,
                                         "folds:\n  - start: 0\n    end: 5\n  - start: 1\n    end: 3\n"),
            MY_RET_OK);
  ASSERT_TRUE(my_text_area_is_folded(area, 0));
  ASSERT_TRUE(my_text_area_is_folded(area, 1));
  ASSERT_EQ(my_text_area_folds_from_yaml(area,
                                         "version: 0\nfolds:\n  - start: 0\n    end: 5\n  - start: 1\n    end: 3\n"),
            MY_RET_OK);
  ASSERT_TRUE(my_text_area_is_folded(area, 0));
  ASSERT_TRUE(my_text_area_is_folded(area, 1));
  my_mem_free(NULL, yaml);
  yaml = NULL;
  ASSERT_EQ(my_text_area_folds_to_yaml(area, NULL, &yaml), MY_RET_OK);
  ASSERT_STR_EQ(yaml, "version: 1\nfolds:\n  - start: 0\n    end: 5\n  - start: 1\n    end: 3\n");
  my_mem_free(NULL, yaml);
  yaml = NULL;
  ASSERT_EQ(my_text_area_folds_from_yaml(area, "version: 2\nfolds:\n"),
            MY_RET_INVALID_PARAMS);
  ASSERT_TRUE(my_text_area_is_folded(area, 0));
  ASSERT_EQ(my_text_area_folds_from_yaml(area,
                                         "folds:\n  - start: 0\n    end: 99\n"),
            MY_RET_INVALID_PARAMS);
  ASSERT_TRUE(my_text_area_is_folded(area, 0));
  ASSERT_TRUE(my_text_area_is_folded(area, 1));
  ASSERT_EQ(my_text_area_folds_from_yaml(area,
                                         "folds:\n  - start: 0\n    end: 3\n    extra: 1\n"),
            MY_RET_INVALID_PARAMS);
  ASSERT_EQ(my_text_area_folds_from_yaml(area,
                                         "folds:\n  - start: 0\n    end: 3\n\nextra: 1\n"),
            MY_RET_INVALID_PARAMS);
  ASSERT_TRUE(my_text_area_is_folded(area, 0));
  ASSERT_TRUE(my_text_area_is_folded(area, 1));
  ASSERT_EQ(my_text_area_set_folded_range(area, 0, 5, false), MY_RET_OK);
  ASSERT_EQ(my_text_area_set_folded_range(area, 1, 3, false), MY_RET_OK);
  my_mem_free(NULL, yaml);
  yaml = NULL;
  ASSERT_EQ(my_text_area_folds_to_yaml(area, NULL, &yaml), MY_RET_OK);
  ASSERT_STR_EQ(yaml, "version: 1\nfolds:\n");
  my_mem_free(NULL, yaml);
  my_widget_unref(area);
}

TEST(text_area_many_nested_folds_build_visible_rows_once)
{
  my_widget_t* area = my_text_area_create(NULL);
  char* text;
  size_t line_count = 512;
  size_t i;
  ASSERT_NOT_NULL(area);
  text = (char*)malloc(line_count * 2u + 1u);
  ASSERT_NOT_NULL(text);
  for (i = 0; i < line_count; i++) {
    text[i * 2u] = 'x';
    text[i * 2u + 1u] = '\n';
  }
  text[line_count * 2u] = '\0';
  ASSERT_EQ(my_text_area_set_text(area, text), MY_RET_OK);
  free(text);
  for (i = 0; i < 128; i++) {
    ASSERT_EQ(my_text_area_set_folded_range(area, i, line_count - i,
                                            true),
              MY_RET_OK);
  }
  ASSERT_EQ(my_text_area_visual_line_count(area), 1u);
  ASSERT_TRUE(my_text_area_is_folded(area, 0));
  ASSERT_TRUE(my_text_area_is_folded(area, 127));
  my_widget_unref(area);
}

TEST(text_area_folded_range_rebuilds_wrapped_visual_lines)
{
  my_widget_t* area = my_text_area_create(NULL);
  const my_visual_line_t* line;

  ASSERT_NOT_NULL(area);
  ASSERT_EQ(my_widget_set_rect(area, &(my_rect_t){0, 0, 28, 80}), MY_RET_OK);
  ASSERT_EQ(my_text_area_set_wrap(area, true), MY_RET_OK);
  ASSERT_EQ(my_text_area_set_text(area, "abcd\nefgh\nijkl"), MY_RET_OK);
  ASSERT_EQ(my_text_area_visual_line_count(area), 6u);
  ASSERT_EQ(my_text_area_set_folded_range(area, 0, 1, true), MY_RET_OK);
  ASSERT_EQ(my_text_area_visual_line_count(area), 4u);
  line = my_text_area_visual_line_at(area, 2);
  ASSERT_NOT_NULL(line);
  ASSERT_EQ(line->phys, 2u);
  my_widget_unref(area);
}

TEST(text_area_wrap_oom_keeps_previous_cache)
{
  text_area_fail_alloc_t state = {false, false};
  my_allocator_t allocator = {&state, text_area_fail_alloc,
                              text_area_fail_calloc, text_area_fail_realloc,
                              text_area_fail_free};
  my_widget_t* area = my_text_area_create(&allocator);
  ASSERT_NOT_NULL(area);
  ASSERT_EQ(my_widget_set_rect(area, &(my_rect_t){0, 0, 20, 80}), MY_RET_OK);
  ASSERT_EQ(my_text_area_set_text(area, "abcd"), MY_RET_OK);
  ASSERT_EQ(my_text_area_set_wrap(area, true), MY_RET_OK);
  ASSERT_EQ(my_text_area_visual_line_count(area), 4u);
  state.fail = true;
  ASSERT_EQ(my_text_area_set_wrap(area, false), MY_RET_OK);
  ASSERT_EQ(my_text_area_set_wrap(area, true), MY_RET_OK);
  ASSERT_EQ(my_text_area_visual_line_count(area), 4u);
  state.fail = false;
  ASSERT_EQ(my_text_area_visual_line_count(area), 4u);
  my_widget_unref(area);
}

TEST(text_area_folded_rows_remain_hidden_when_visible_cache_ooms)
{
  text_area_fail_alloc_t state = {false, false};
  my_allocator_t allocator = {&state, text_area_fail_alloc,
                              text_area_fail_calloc, text_area_fail_realloc,
                              text_area_fail_free};
  my_widget_t* area = my_text_area_create(&allocator);
  const my_visual_line_t* line;

  ASSERT_NOT_NULL(area);
  ASSERT_EQ(my_text_area_set_text(area, "a\nb\nc\nd"), MY_RET_OK);
  ASSERT_EQ(my_text_area_set_folded_range(area, 1, 2, true), MY_RET_OK);
  state.fail = true;
  ASSERT_EQ(my_text_area_visual_line_count(area), 3u);
  line = my_text_area_visual_line_at(area, 1);
  ASSERT_NOT_NULL(line);
  ASSERT_EQ(line->phys, 1u);
  line = my_text_area_visual_line_at(area, 2);
  ASSERT_NOT_NULL(line);
  ASSERT_EQ(line->phys, 3u);
  my_widget_unref(area);
}

TEST(text_area_justify_cursor_tracks_stretched_space)
{
  my_widget_t* area = my_text_area_create(NULL);
  my_text_area_t* text_area = (my_text_area_t*)area;
  my_lcd_t* lcd = my_lcd_mem_create(NULL, 100, 80, MY_PIXEL_FORMAT_BGRA8888);
  my_vgcanvas_t* canvas = my_vgcanvas_soft_create(NULL, lcd);
  uint8_t* pixels;
  uint32_t stride;
  size_t y;

  ASSERT_NOT_NULL(area);
  ASSERT_NOT_NULL(lcd);
  ASSERT_NOT_NULL(canvas);
  ASSERT_EQ(my_widget_set_rect(area, &(my_rect_t){0, 0, 54, 80}), MY_RET_OK);
  ASSERT_EQ(my_text_area_set_wrap(area, true), MY_RET_OK);
  ASSERT_EQ(my_text_area_set_align(area, MY_TEXT_ALIGN_JUSTIFY), MY_RET_OK);
  ASSERT_EQ(my_text_area_set_text(area, "aa bb cc"), MY_RET_OK);
  text_area->cursor_row = 0;
  text_area->cursor_col = 3;
  text_area->focused = true;
  text_area->cursor_visible = true;
  ASSERT_EQ(my_vgcanvas_begin_frame(canvas, NULL), MY_RET_OK);
  area->vtable->on_paint(area, canvas);
  ASSERT_EQ(my_vgcanvas_end_frame(canvas), MY_RET_OK);
  pixels = my_lcd_mem_get_buffer(lcd);
  stride = my_lcd_mem_get_stride(lcd);
  ASSERT_NOT_NULL(pixels);
  for (y = 3; y < 19; y++) {
    ASSERT_EQ(pixels[y * stride + 34u * 4u], 33u);
  }
  my_vgcanvas_destroy(canvas);
  my_lcd_destroy(lcd);
  my_widget_unref(area);
}

TEST(text_area_justify_cursor_tracks_unicode_breaking_space)
{
  my_pal_t* pal = my_pal_dummy_create(NULL);
  my_pal_main_loop_t* loop = my_pal_main_loop_create(pal);
  my_window_manager_t* wm = my_window_manager_create(NULL, pal, loop);
  my_window_t* win = my_window_create(NULL, pal, 200, 100, "main");
  my_widget_t* area = my_text_area_create(NULL);
  my_text_area_t* text_area = (my_text_area_t*)area;
  int32_t ime_x = 0;
  int32_t ime_y = 0;

  ASSERT_NOT_NULL(pal);
  ASSERT_NOT_NULL(loop);
  ASSERT_NOT_NULL(wm);
  ASSERT_NOT_NULL(win);
  ASSERT_NOT_NULL(area);
  ASSERT_EQ(my_widget_set_rect(area, &(my_rect_t){10, 20, 54, 60}),
            MY_RET_OK);
  ASSERT_EQ(my_text_area_set_wrap(area, true), MY_RET_OK);
  ASSERT_EQ(my_text_area_set_align(area, MY_TEXT_ALIGN_JUSTIFY), MY_RET_OK);
  ASSERT_EQ(my_text_area_set_text(area, "aa\xE2\x80\x83" "bb cc"), MY_RET_OK);
  text_area->cursor_row = 0;
  text_area->cursor_col = 3;
  ASSERT_EQ(my_widget_add_child(my_window_widget(win), area), MY_RET_OK);
  my_widget_unref(area);
  ASSERT_EQ(my_window_manager_open(wm, win), MY_RET_OK);
  my_widget_unref((my_widget_t*)win);
  my_event_dispatcher_set_focus(&win->dispatcher, area);
  my_pal_dummy_get_ime_spot(win->pal_window, &ime_x, &ime_y);
  ASSERT_EQ(ime_x, 44);
  ASSERT_EQ(ime_y, 39);
  my_event_dispatcher_set_focus(&win->dispatcher, NULL);

  my_window_manager_destroy(wm);
  my_pal_main_loop_destroy(loop);
  my_pal_destroy(pal);
}

TEST(text_area_syntax_is_lazy_and_budgeted)
{
  my_widget_t* area = my_text_area_create(NULL);
  my_lcd_t* lcd = my_lcd_mem_create(NULL, 160, 80, MY_PIXEL_FORMAT_BGRA8888);
  my_vgcanvas_t* canvas = my_vgcanvas_soft_create(NULL, lcd);
  my_text_area_t* text_area = (my_text_area_t*)area;

  ASSERT_NOT_NULL(area);
  ASSERT_NOT_NULL(lcd);
  ASSERT_NOT_NULL(canvas);
  ASSERT_EQ(my_text_area_set_text(area, "int first;\nint second;\n"),
            MY_RET_OK);
  ASSERT_FALSE(my_text_area_syntax_enabled(area));
  ASSERT_TRUE(text_area->syntax_cache == NULL);
  ASSERT_EQ(my_text_area_set_syntax_language(area, MY_SYNTAX_C_LIKE),
            MY_RET_OK);
  ASSERT_EQ(my_text_area_set_syntax_line_budget(area, 1), MY_RET_OK);
  ASSERT_EQ(my_text_area_set_syntax_enabled(area, true), MY_RET_OK);
  ASSERT_TRUE(my_text_area_syntax_enabled(area));
  ASSERT_FALSE(my_text_area_syntax_line_ready(area, 0));
  ASSERT_FALSE(my_text_area_syntax_line_ready(area, 1));

  ASSERT_EQ(my_vgcanvas_begin_frame(canvas, NULL), MY_RET_OK);
  area->vtable->on_paint(area, canvas);
  ASSERT_EQ(my_vgcanvas_end_frame(canvas), MY_RET_OK);
  ASSERT_TRUE(my_text_area_syntax_line_ready(area, 0));
  ASSERT_FALSE(my_text_area_syntax_line_ready(area, 1));

  ASSERT_EQ(my_vgcanvas_begin_frame(canvas, NULL), MY_RET_OK);
  area->vtable->on_paint(area, canvas);
  ASSERT_EQ(my_vgcanvas_end_frame(canvas), MY_RET_OK);
  ASSERT_TRUE(my_text_area_syntax_line_ready(area, 1));

  my_vgcanvas_destroy(canvas);
  my_lcd_destroy(lcd);
  my_widget_unref(area);
}

TEST(text_area_syntax_replacement_invalidates_tokens)
{
  my_widget_t* area = my_text_area_create(NULL);
  my_text_area_t* text_area = (my_text_area_t*)area;
  ASSERT_NOT_NULL(area);
  ASSERT_EQ(my_text_area_set_text(area, "int first;\nint second;\n"),
            MY_RET_OK);
  ASSERT_EQ(my_text_area_set_syntax_language(area, MY_SYNTAX_C_LIKE),
            MY_RET_OK);
  ASSERT_EQ(my_text_area_set_syntax_line_budget(area, 8), MY_RET_OK);
  ASSERT_EQ(my_text_area_set_syntax_enabled(area, true), MY_RET_OK);
  ASSERT_EQ(my_syntax_cache_ensure(text_area->syntax_cache, 8), MY_RET_OK);
  ASSERT_TRUE(my_text_area_syntax_line_ready(area, 0));
  ASSERT_TRUE(my_text_area_syntax_line_ready(area, 1));
  text_area->cursor_row = 0;
  text_area->cursor_col = 0;
  text_area->anchor_row = 0;
  text_area->anchor_col = 0;
  text_area->goal_col = 0;
  ASSERT_EQ(my_text_area_set_text(area, "int changed;\nint second;\n"),
            MY_RET_OK);
  ASSERT_FALSE(my_text_area_syntax_line_ready(area, 0));
  ASSERT_FALSE(my_text_area_syntax_line_ready(area, 1));
  my_widget_unref(area);
}

TEST(text_area_syntax_key_edit_invalidates_suffix)
{
  my_widget_t* area = my_text_area_create(NULL);
  my_text_area_t* text_area = (my_text_area_t*)area;
  my_event_t event = my_event_init(MY_EVENT_KEY_DOWN);
  ASSERT_NOT_NULL(area);
  ASSERT_EQ(my_text_area_set_text(area, "int first;\nint second;\n"), MY_RET_OK);
  ASSERT_EQ(my_text_area_set_syntax_language(area, MY_SYNTAX_C_LIKE), MY_RET_OK);
  ASSERT_EQ(my_text_area_set_syntax_enabled(area, true), MY_RET_OK);
  ASSERT_EQ(my_syntax_cache_ensure(text_area->syntax_cache, 8), MY_RET_OK);
  text_area->cursor_row = 0;
  text_area->cursor_col = 0;
  text_area->anchor_row = 0;
  text_area->anchor_col = 0;
  text_area->focused = true;
  event.u.key.key = 'x';
  ASSERT_EQ(area->vtable->on_event(area, &event), MY_RET_OK);
  ASSERT_FALSE(my_text_area_syntax_line_ready(area, 0));
  ASSERT_TRUE(my_text_area_syntax_line_ready(area, 1));
  my_widget_unref(area);
}

TEST(window_manager_refreshes_all_window_scales)
{
  my_pal_t* pal = my_pal_dummy_create(NULL);
  my_pal_main_loop_t* loop;
  my_window_manager_t* wm;
  my_window_t* root;
  my_window_t* dialog;

  ASSERT_NOT_NULL(pal);
  loop = my_pal_main_loop_create(pal);
  wm = my_window_manager_create(NULL, pal, loop);
  root = my_window_create(NULL, pal, 200, 120, "root-scale");
  dialog = my_window_create(NULL, pal, 80, 40, "dialog-scale");
  ASSERT_NOT_NULL(loop);
  ASSERT_NOT_NULL(wm);
  ASSERT_NOT_NULL(root);
  ASSERT_NOT_NULL(dialog);
  ASSERT_EQ(my_window_manager_open(wm, root), MY_RET_OK);
  ASSERT_EQ(my_window_manager_open(wm, dialog), MY_RET_OK);
  my_widget_unref((my_widget_t *)root);
  my_widget_unref((my_widget_t *)dialog);
  my_dirty_rects_clear(&root->dirty);
  my_dirty_rects_clear(&dialog->dirty);

  my_pal_dummy_set_scale_factor(pal, 1.5f);
  ASSERT_TRUE(my_window_manager_refresh_scales(wm));
  ASSERT_EQ(root->scale, 1.5f);
  ASSERT_EQ(dialog->scale, 1.5f);
  ASSERT_TRUE(my_dirty_rects_count(&root->dirty) > 0);
  ASSERT_TRUE(my_dirty_rects_count(&dialog->dirty) > 0);
  ASSERT_TRUE(!my_window_manager_refresh_scales(wm));

  my_window_manager_destroy(wm);
  my_pal_main_loop_destroy(loop);
  my_pal_destroy(pal);
}

TEST(gpu_backend_request_reports_actual_state)
{
  my_pal_t* pal = my_pal_dummy_create(NULL);
  my_window_t* win;

  ASSERT_NOT_NULL(pal);
  win = my_window_create(NULL, pal, 80, 40, "backend");
  ASSERT_NOT_NULL(win);
  ASSERT_EQ(win->gpu_backend, MY_GPU_SOFT);
  ASSERT_EQ(my_window_enable_gpu(win, MY_GPU_GLES2), MY_RET_NOT_SUPPORTED);
  ASSERT_EQ(win->gpu_backend, MY_GPU_SOFT);
  ASSERT_EQ(my_window_enable_gpu(win, MY_GPU_VULKAN), MY_RET_NOT_SUPPORTED);
  ASSERT_EQ(win->gpu_backend, MY_GPU_SOFT);
  ASSERT_EQ(my_window_enable_gpu(win, MY_GPU_SOFT), MY_RET_OK);
  ASSERT_EQ(win->gpu_backend, MY_GPU_SOFT);
  ASSERT_EQ(my_window_enable_gpu(win, (my_gpu_backend_t)99),
            MY_RET_INVALID_PARAMS);
  ASSERT_EQ(win->gpu_backend, MY_GPU_SOFT);

  my_object_unref((my_object_t*)win);
  my_pal_destroy(pal);
}

TEST(software_canvas_recreates_after_surface_resize)
{
  my_pal_t* pal = my_pal_dummy_create(NULL);
  my_pal_main_loop_t* loop;
  my_window_manager_t* wm;
  my_window_t* win;
  my_lcd_t* old_lcd;
  my_lcd_t* resized_lcd;

  ASSERT_NOT_NULL(pal);
  my_pal_dummy_set_scale_factor(pal, 2.0f);
  loop = my_pal_main_loop_create(pal);
  ASSERT_NOT_NULL(loop);
  wm = my_window_manager_create(NULL, pal, loop);
  ASSERT_NOT_NULL(wm);
  win = my_window_create(NULL, pal, 80, 40, "resize");
  ASSERT_NOT_NULL(win);
  ASSERT_EQ(my_window_manager_open(wm, win), MY_RET_OK);
  my_widget_unref((my_widget_t *)win);
  my_widget_invalidate(my_window_widget(win), NULL);
  my_window_paint(win);
  ASSERT_NOT_NULL(win->vg);
  old_lcd = my_pal_window_get_lcd(win->pal_window);
  ASSERT_NOT_NULL(old_lcd);
  ASSERT_EQ(my_lcd_get_width(old_lcd), 160);
  ASSERT_EQ(my_lcd_get_height(old_lcd), 80);

  ASSERT_EQ(my_window_manager_resize_surface(wm, 160, 90), MY_RET_OK);
  ASSERT_TRUE(win->vg == NULL);
  resized_lcd = my_pal_window_get_lcd(win->pal_window);
  ASSERT_NOT_NULL(resized_lcd);
  ASSERT_TRUE(resized_lcd != old_lcd);
  ASSERT_EQ(my_lcd_get_width(resized_lcd), 320);
  ASSERT_EQ(my_lcd_get_height(resized_lcd), 180);
  my_window_paint(win);
  ASSERT_NOT_NULL(win->vg);

  my_window_manager_destroy(wm);
  my_pal_main_loop_destroy(loop);
  my_pal_destroy(pal);
}

TEST(window_css_media_reloads_on_logical_resize)
{
  const char* css =
      "button { color: blue; }"
      "@media (min-width: 150px) { button { color: red; } }";
  my_pal_t* pal = my_pal_dummy_create(NULL);
  my_pal_main_loop_t* loop;
  my_window_manager_t* wm;
  my_window_t* win;
  my_widget_t* button;

  ASSERT_NOT_NULL(pal);
  loop = my_pal_main_loop_create(pal);
  ASSERT_NOT_NULL(loop);
  wm = my_window_manager_create(NULL, pal, loop);
  ASSERT_NOT_NULL(wm);
  win = my_window_create(NULL, pal, 100, 80, "responsive");
  ASSERT_NOT_NULL(win);
  button = my_button_create(NULL, "button");
  ASSERT_NOT_NULL(button);
  ASSERT_EQ(my_widget_add_child(my_window_widget(win), button), MY_RET_OK);
  ASSERT_EQ(my_window_set_css_style(win, css), MY_RET_OK);
  ASSERT_EQ(my_widget_style_get_color(button, MY_STATE_NORMAL,
                                      MY_STYLE_FG_COLOR, 0u),
            0x0000FFFFu);
  ASSERT_EQ(my_window_manager_open(wm, win), MY_RET_OK);
  ASSERT_EQ(my_window_manager_resize_surface(wm, 200, 80), MY_RET_OK);
  ASSERT_EQ(my_widget_style_get_color(button, MY_STATE_NORMAL,
                                      MY_STYLE_FG_COLOR, 0u),
            0xFF0000FFu);
  ASSERT_EQ(my_window_manager_resize_surface(wm, 100, 80), MY_RET_OK);
  ASSERT_EQ(my_widget_style_get_color(button, MY_STATE_NORMAL,
                                      MY_STYLE_FG_COLOR, 0u),
            0x0000FFFFu);

  my_widget_unref(button);
  my_widget_unref((my_widget_t*)win);
  my_window_manager_destroy(wm);
  my_pal_main_loop_destroy(loop);
  my_pal_destroy(pal);
}

TEST(window_css_style_failure_preserves_active_theme)
{
  const char* valid =
      "button { color: blue; }"
      "@media (min-width: 150px) { button { color: red; } }";
  const char* invalid = "@media (min-width: nope) { button { color: red; } }";
  my_pal_t* pal = my_pal_dummy_create(NULL);
  my_window_t* win;
  my_widget_t* button;

  ASSERT_NOT_NULL(pal);
  win = my_window_create(NULL, pal, 100, 80, "transaction");
  ASSERT_NOT_NULL(win);
  button = my_button_create(NULL, "button");
  ASSERT_NOT_NULL(button);
  ASSERT_EQ(my_widget_add_child(my_window_widget(win), button), MY_RET_OK);
  ASSERT_EQ(my_window_set_css_style(win, valid), MY_RET_OK);
  ASSERT_EQ(my_widget_style_get_color(button, MY_STATE_NORMAL,
                                      MY_STYLE_FG_COLOR, 0u),
            0x0000FFFFu);
  ASSERT_EQ(my_window_set_css_style(win, invalid), MY_RET_FAIL);
  ASSERT_EQ(my_widget_style_get_color(button, MY_STATE_NORMAL,
                                      MY_STYLE_FG_COLOR, 0u),
            0x0000FFFFu);
  {
    my_event_t resize = my_event_init(MY_EVENT_RESIZE);
    resize.u.resize.w = 200;
    resize.u.resize.h = 80;
    ASSERT_EQ(my_pal_window_resize(win->pal_window, 200, 80), MY_RET_OK);
    ASSERT_EQ(my_window_on_pal_event(win, &resize), MY_RET_OK);
    ASSERT_EQ(my_widget_style_get_color(button, MY_STATE_NORMAL,
                                        MY_STYLE_FG_COLOR, 0u),
              0xFF0000FFu);
  }

  my_widget_unref(button);
  my_widget_unref((my_widget_t*)win);
  my_pal_destroy(pal);
}

TEST(window_css_media_refreshes_only_after_platform_fact_change)
{
  const char* css =
      "button { color: blue; }"
      "@media (prefers-color-scheme: dark) { button { color: red; } }";
  my_pal_t* pal = my_pal_dummy_create(NULL);
  my_window_manager_t* wm;
  my_pal_main_loop_t* loop;
  my_window_t* win;
  my_widget_t* button;
  my_pal_media_context_ex_t media = {
      {true, false, false, MY_PAL_MEDIA_CAP_COLOR_SRGB},
      MY_PAL_MEDIA_KNOWN_COLOR_SCHEME | MY_PAL_MEDIA_KNOWN_COLOR_GAMUT};

  ASSERT_NOT_NULL(pal);
  my_pal_dummy_set_media_context_ex(pal, &media);
  loop = my_pal_main_loop_create(pal);
  ASSERT_NOT_NULL(loop);
  wm = my_window_manager_create(NULL, pal, loop);
  ASSERT_NOT_NULL(wm);
  win = my_window_create(NULL, pal, 100, 80, "media-refresh");
  ASSERT_NOT_NULL(win);
  button = my_button_create(NULL, "button");
  ASSERT_NOT_NULL(button);
  ASSERT_EQ(my_widget_add_child(my_window_widget(win), button), MY_RET_OK);
  ASSERT_EQ(my_window_set_css_style(win, css), MY_RET_OK);
  ASSERT_EQ(my_window_manager_open(wm, win), MY_RET_OK);
  ASSERT_EQ(my_widget_style_get_color(button, MY_STATE_NORMAL,
                                      MY_STYLE_FG_COLOR, 0u),
            0x0000FFFFu);
  ASSERT_EQ(my_window_refresh_media_style(win), MY_RET_NOT_FOUND);

  media.base.prefers_dark = true;
  my_pal_dummy_set_media_context_ex(pal, &media);
  ASSERT_TRUE(my_window_manager_refresh_media(wm));
  ASSERT_EQ(my_widget_style_get_color(button, MY_STATE_NORMAL,
                                      MY_STYLE_FG_COLOR, 0u),
            0xFF0000FFu);
  ASSERT_EQ(my_window_refresh_media_style(win), MY_RET_NOT_FOUND);

  media.base.prefers_dark = false;
  my_pal_dummy_set_media_context_ex(pal, &media);
  ASSERT_EQ(my_window_manager_count(wm), 1u);
  ASSERT_TRUE(my_window_manager_refresh_media(wm));
  ASSERT_EQ(my_widget_style_get_color(button, MY_STATE_NORMAL,
                                      MY_STYLE_FG_COLOR, 0u),
            0x0000FFFFu);
  ASSERT_TRUE(!my_window_manager_refresh_media(wm));

  my_widget_unref(button);
  my_widget_unref((my_widget_t*)win);
  my_window_manager_destroy(wm);
  my_pal_main_loop_destroy(loop);
  my_pal_destroy(pal);
}

TEST(window_css_media_refresh_failure_is_retryable)
{
  const char* css =
      "button { color: blue; }"
      "@media (prefers-color-scheme: dark) { button { color: red; } }";
  text_area_fail_alloc_t state = {false, false};
  my_allocator_t allocator = {&state, text_area_fail_alloc,
                              text_area_fail_calloc, text_area_fail_realloc,
                              text_area_fail_free};
  my_pal_t* pal = my_pal_dummy_create(NULL);
  my_pal_main_loop_t* loop;
  my_window_manager_t* wm;
  my_window_t* win;
  my_widget_t* button;
  my_pal_media_context_ex_t media = {
      {true, false, false, MY_PAL_MEDIA_CAP_COLOR_SRGB},
      MY_PAL_MEDIA_KNOWN_COLOR_SCHEME | MY_PAL_MEDIA_KNOWN_COLOR_GAMUT};
  bool changed = true;

  ASSERT_NOT_NULL(pal);
  my_pal_dummy_set_media_context_ex(pal, &media);
  loop = my_pal_main_loop_create(pal);
  ASSERT_NOT_NULL(loop);
  wm = my_window_manager_create(NULL, pal, loop);
  ASSERT_NOT_NULL(wm);
  win = my_window_create(&allocator, pal, 100, 80, "media-retry");
  ASSERT_NOT_NULL(win);
  button = my_button_create(&allocator, "button");
  ASSERT_NOT_NULL(button);
  ASSERT_EQ(my_widget_add_child(my_window_widget(win), button), MY_RET_OK);
  ASSERT_EQ(my_window_set_css_style(win, css), MY_RET_OK);
  ASSERT_EQ(my_window_manager_open(wm, win), MY_RET_OK);

  media.base.prefers_dark = true;
  my_pal_dummy_set_media_context_ex(pal, &media);
  state.fail = true;
  ASSERT_EQ(my_window_manager_refresh_media_ex(wm, &changed), MY_RET_OOM);
  ASSERT_FALSE(changed);
  ASSERT_EQ(my_widget_style_get_color(button, MY_STATE_NORMAL,
                                      MY_STYLE_FG_COLOR, 0u),
            0x0000FFFFu);

  state.fail = false;
  ASSERT_EQ(my_window_manager_refresh_media_ex(wm, &changed), MY_RET_OK);
  ASSERT_TRUE(changed);
  ASSERT_EQ(my_widget_style_get_color(button, MY_STATE_NORMAL,
                                      MY_STYLE_FG_COLOR, 0u),
            0xFF0000FFu);
  ASSERT_EQ(my_window_manager_refresh_media_ex(wm, &changed), MY_RET_OK);
  ASSERT_FALSE(changed);

  my_widget_unref(button);
  my_widget_unref((my_widget_t*)win);
  my_window_manager_destroy(wm);
  my_pal_main_loop_destroy(loop);
  my_pal_destroy(pal);
}

TEST(window_snapshot_keeps_removed_window_alive)
{
  my_pal_t *pal = my_pal_dummy_create(NULL);
  my_pal_main_loop_t *loop = my_pal_main_loop_create(pal);
  my_window_manager_t *wm = my_window_manager_create(NULL, pal, loop);
  my_window_t *win = my_window_create(NULL, pal, 100, 80, "snapshot");
  my_window_t **snapshot = NULL;
  size_t count = 0;

  ASSERT_NOT_NULL(pal);
  ASSERT_NOT_NULL(loop);
  ASSERT_NOT_NULL(wm);
  ASSERT_NOT_NULL(win);
  ASSERT_EQ(my_window_manager_open(wm, win), MY_RET_OK);
  ASSERT_EQ(my_window_manager_snapshot_windows(wm, &snapshot, &count),
            MY_RET_OK);
  ASSERT_EQ(count, 1u);
  ASSERT_TRUE(snapshot[0] == win);

  my_widget_unref((my_widget_t *)win);
  ASSERT_EQ(my_window_manager_close(wm, snapshot[0]), MY_RET_OK);
  ASSERT_EQ(my_window_manager_count(wm), 0u);
  ASSERT_TRUE(snapshot[0]->pal_window != NULL);

  my_window_manager_release_snapshot(wm, snapshot, count);
  my_window_manager_destroy(wm);
  my_pal_main_loop_destroy(loop);
  my_pal_destroy(pal);
}

TEST(closed_window_detaches_manager_borrowed_state)
{
  my_pal_t* pal = my_pal_dummy_create(NULL);
  my_pal_main_loop_t* loop = my_pal_main_loop_create(pal);
  my_window_manager_t* wm = my_window_manager_create(NULL, pal, loop);
  my_window_t* win = my_window_create(NULL, pal, 100, 80, "closed");

  ASSERT_NOT_NULL(wm);
  ASSERT_NOT_NULL(win);
  ASSERT_EQ(my_window_manager_open(wm, win), MY_RET_OK);
  ASSERT_EQ(my_window_manager_close(wm, win), MY_RET_OK);
  ASSERT_TRUE(win->wm == NULL);
  ASSERT_TRUE(win->loop == NULL);
  ASSERT_TRUE(win->base.anim_mgr == NULL);

  my_window_manager_destroy(wm);
  my_widget_unref((my_widget_t*)win);
  my_pal_main_loop_destroy(loop);
  my_pal_destroy(pal);
}

TEST(paint_stack_mutation_stops_current_frame)
{
  my_pal_t *pal = my_pal_dummy_create(NULL);
  my_pal_main_loop_t *loop = my_pal_main_loop_create(pal);
  my_window_manager_t *wm = my_window_manager_create(NULL, pal, loop);
  my_window_t *closing = my_window_create(NULL, pal, 100, 80, "closing");
  my_window_t *remaining = my_window_create(NULL, pal, 100, 80, "remaining");
  my_widget_t *closing_child = my_widget_create(NULL, "close-on-paint");
  my_widget_t *remaining_child = my_widget_create(NULL, "count-paint");
  paint_stack_mutation_ctx_t closing_ctx = {wm, closing, 0};
  paint_stack_mutation_ctx_t remaining_ctx = {wm, remaining, 0};

  ASSERT_NOT_NULL(pal);
  ASSERT_NOT_NULL(loop);
  ASSERT_NOT_NULL(wm);
  ASSERT_NOT_NULL(closing);
  ASSERT_NOT_NULL(remaining);
  ASSERT_NOT_NULL(closing_child);
  ASSERT_NOT_NULL(remaining_child);
  ASSERT_EQ(my_widget_subclass_init(closing_child,
                                    &s_close_window_on_paint_vtable),
            MY_RET_OK);
  ASSERT_EQ(my_widget_subclass_init(remaining_child, &s_count_paint_vtable),
            MY_RET_OK);
  ASSERT_EQ(my_widget_set_user_data(closing_child, &closing_ctx), MY_RET_OK);
  ASSERT_EQ(my_widget_set_user_data(remaining_child, &remaining_ctx),
            MY_RET_OK);
  ASSERT_EQ(my_widget_set_rect(closing_child, &(my_rect_t){0, 0, 20, 20}),
            MY_RET_OK);
  ASSERT_EQ(my_widget_set_rect(remaining_child, &(my_rect_t){0, 0, 20, 20}),
            MY_RET_OK);
  ASSERT_EQ(my_widget_add_child(my_window_widget(closing), closing_child),
            MY_RET_OK);
  ASSERT_EQ(my_widget_add_child(my_window_widget(remaining), remaining_child),
            MY_RET_OK);
  my_widget_unref(closing_child);
  my_widget_unref(remaining_child);
  ASSERT_EQ(my_window_manager_open(wm, closing), MY_RET_OK);
  ASSERT_EQ(my_window_manager_open(wm, remaining), MY_RET_OK);
  my_widget_unref((my_widget_t *)closing);
  my_widget_unref((my_widget_t *)remaining);

  my_pal_dummy_set_now_ms(pal, 10000);
  ASSERT_EQ(my_pal_main_loop_run(loop), MY_RET_OK);
  ASSERT_EQ(closing_ctx.paint_count, 1);
  ASSERT_EQ(remaining_ctx.paint_count, 0);
  ASSERT_EQ(my_window_manager_count(wm), 1u);
  ASSERT_TRUE(my_dirty_rects_count(&remaining->dirty) > 0);

  my_window_manager_destroy(wm);
  my_pal_main_loop_destroy(loop);
  my_pal_destroy(pal);
}

TEST(on_open_hook_fires_once_per_open)
{
  my_pal_t *pal = my_pal_dummy_create(NULL);
  my_pal_main_loop_t *loop = my_pal_main_loop_create(pal);
  my_window_manager_t *wm = my_window_manager_create(NULL, pal, loop);
  my_window_t *win = my_window_create(NULL, pal, 100, 80, "test");
  int marker = 42;

  my_window_manager_set_on_open(wm, on_open_cb, &marker);
  g_open_count = 0;
  my_window_manager_open(wm, win);
  ASSERT_EQ(g_open_count, 1);
  ASSERT_TRUE(g_hook_wm == wm);
  ASSERT_TRUE(g_hook_win == win);
  ASSERT_TRUE(g_hook_ctx == &marker);

  my_object_unref((my_object_t *)win);
  my_window_manager_destroy(wm);
  my_pal_main_loop_destroy(loop);
  my_pal_destroy(pal);
}

TEST(on_open_lease_skips_invalidated_context_and_releases_on_destroy)
{
  my_pal_t* pal = my_pal_dummy_create(NULL);
  my_pal_main_loop_t* loop = my_pal_main_loop_create(pal);
  my_window_manager_t* wm = my_window_manager_create(NULL, pal, loop);
  my_window_t* win = my_window_create(NULL, pal, 160, 100, "open-lease");
  callback_lease_test_t state = {0};

  ASSERT_NOT_NULL(wm);
  ASSERT_NOT_NULL(win);
  state.lease = my_emitter_context_lease_create(
      NULL, &state, callback_lease_destroy);
  ASSERT_NOT_NULL(state.lease);
  ASSERT_EQ(my_window_manager_set_on_open_lease(
                wm, on_open_lease_callback, state.lease), MY_RET_OK);
  my_emitter_context_lease_invalidate(state.lease);
  my_emitter_context_lease_unref(state.lease);
  ASSERT_EQ(my_window_manager_open(wm, win), MY_RET_OK);
  ASSERT_EQ(state.callback_count, 0);
  ASSERT_EQ(state.destroy_count, 0);

  my_window_manager_destroy(wm);
  ASSERT_EQ(state.destroy_count, 1);
  my_widget_unref((my_widget_t*)win);
  my_pal_main_loop_destroy(loop);
  my_pal_destroy(pal);
}

TEST(on_open_lease_replacement_releases_old_context_once)
{
  my_pal_t* pal = my_pal_dummy_create(NULL);
  my_pal_main_loop_t* loop = my_pal_main_loop_create(pal);
  my_window_manager_t* wm = my_window_manager_create(NULL, pal, loop);
  callback_lease_test_t first = {0};
  callback_lease_test_t second = {0};

  ASSERT_NOT_NULL(wm);
  first.lease = my_emitter_context_lease_create(
      NULL, &first, callback_lease_destroy);
  second.lease = my_emitter_context_lease_create(
      NULL, &second, callback_lease_destroy);
  ASSERT_NOT_NULL(first.lease);
  ASSERT_NOT_NULL(second.lease);
  ASSERT_EQ(my_window_manager_set_on_open_lease(
                wm, on_open_lease_callback, first.lease), MY_RET_OK);
  my_emitter_context_lease_unref(first.lease);
  ASSERT_EQ(my_window_manager_set_on_open_lease(
                wm, on_open_lease_callback, second.lease), MY_RET_OK);
  my_emitter_context_lease_unref(second.lease);
  ASSERT_EQ(first.destroy_count, 1);
  ASSERT_EQ(second.destroy_count, 0);

  my_window_manager_destroy(wm);
  ASSERT_EQ(second.destroy_count, 1);
  my_pal_main_loop_destroy(loop);
  my_pal_destroy(pal);
}

TEST(on_open_owned_context_releases_on_replacement_and_destroy)
{
  my_pal_t* pal = my_pal_dummy_create(NULL);
  my_pal_main_loop_t* loop = my_pal_main_loop_create(pal);
  my_window_manager_t* wm = my_window_manager_create(NULL, pal, loop);
  callback_lease_test_t state = {0};

  ASSERT_NOT_NULL(wm);
  ASSERT_EQ(my_window_manager_set_on_open_owned(
                wm, on_open_cb, &state, callback_lease_destroy), MY_RET_OK);
  ASSERT_EQ(state.destroy_count, 0);
  my_window_manager_set_on_open(wm, NULL, NULL);
  ASSERT_EQ(state.destroy_count, 1);
  ASSERT_EQ(my_window_manager_set_on_open_owned(
                wm, on_open_cb, &state, callback_lease_destroy), MY_RET_OK);
  my_window_manager_destroy(wm);
  ASSERT_EQ(state.destroy_count, 2);

  my_pal_main_loop_destroy(loop);
  my_pal_destroy(pal);
}

TEST(on_open_owned_context_replacement_defers_destroy_until_callback_returns)
{
  my_pal_t* pal = my_pal_dummy_create(NULL);
  my_pal_main_loop_t* loop = my_pal_main_loop_create(pal);
  my_window_manager_t* wm = my_window_manager_create(NULL, pal, loop);
  my_window_t* win = my_window_create(NULL, pal, 160, 100, "open-reentry");
  bool callback_active = false;
  bool destroyed_during_callback = false;
  on_open_owned_reentry_context_t first = {0};
  on_open_owned_reentry_context_t second = {0};

  ASSERT_NOT_NULL(pal);
  ASSERT_NOT_NULL(loop);
  ASSERT_NOT_NULL(wm);
  ASSERT_NOT_NULL(win);
  first.callback_active = &callback_active;
  first.destroyed_during_callback = &destroyed_during_callback;
  first.replacement_context = &second;
  ASSERT_EQ(my_window_manager_set_on_open_owned(
                wm, on_open_owned_reentry_callback, &first,
                on_open_owned_reentry_destroy), MY_RET_OK);
  ASSERT_EQ(my_window_manager_open(wm, win), MY_RET_OK);
  ASSERT_EQ(first.callback_count, 1);
  ASSERT_EQ(first.set_result, MY_RET_OK);
  ASSERT_EQ(first.destroy_count, 1);
  ASSERT_TRUE(!destroyed_during_callback);
  my_window_manager_destroy(wm);
  ASSERT_EQ(second.destroy_count, 1);
  my_widget_unref((my_widget_t*)win);
  my_pal_main_loop_destroy(loop);
  my_pal_destroy(pal);
}

static void on_open_owned_destroy_manager_callback(my_window_manager_t* wm,
                                                    my_window_t* win,
                                                    void* context) {
  on_open_owned_reentry_context_t* state =
      (on_open_owned_reentry_context_t*)context;
  (void)win;
  state->callback_count++;
  if (state->callback_active != NULL) {
    *state->callback_active = true;
  }
  my_window_manager_destroy(wm);
  if (state->callback_active != NULL) {
    *state->callback_active = false;
  }
}

TEST(on_open_owned_context_destroy_defers_manager_teardown)
{
  my_pal_t* pal = my_pal_dummy_create(NULL);
  my_pal_main_loop_t* loop = my_pal_main_loop_create(pal);
  my_window_manager_t* wm = my_window_manager_create(NULL, pal, loop);
  my_window_t* win = my_window_create(NULL, pal, 160, 100, "open-destroy-owned");
  bool callback_active = false;
  bool destroyed_during_callback = false;
  on_open_owned_reentry_context_t state = {0};

  ASSERT_NOT_NULL(pal);
  ASSERT_NOT_NULL(loop);
  ASSERT_NOT_NULL(wm);
  ASSERT_NOT_NULL(win);
  state.callback_active = &callback_active;
  state.destroyed_during_callback = &destroyed_during_callback;
  ASSERT_EQ(my_window_manager_set_on_open_owned(
                wm, on_open_owned_destroy_manager_callback, &state,
                on_open_owned_reentry_destroy), MY_RET_OK);
  ASSERT_EQ(my_window_manager_open(wm, win), MY_RET_OK);
  ASSERT_EQ(state.callback_count, 1);
  ASSERT_EQ(state.destroy_count, 1);
  ASSERT_TRUE(!destroyed_during_callback);
  my_widget_unref((my_widget_t*)win);
  my_pal_main_loop_destroy(loop);
  my_pal_destroy(pal);
}

TEST(dialog_lifecycle_and_modal_blocking)
{
  my_pal_t *pal = my_pal_dummy_create(NULL);
  my_pal_main_loop_t *loop = my_pal_main_loop_create(pal);
  my_window_manager_t *wm = my_window_manager_create(NULL, pal, loop);
  my_window_t *main_win = my_window_create(NULL, pal, 400, 300, "main");
  my_widget_t *btn = my_button_create(NULL, "ok");
  my_dialog_t *dlg;
  my_event_t e;

  my_widget_set_rect(btn, &(my_rect_t){10, 10, 80, 32});
  my_widget_add_child(my_window_widget(main_win), btn);
  my_widget_unref(btn);

  my_window_manager_open(wm, main_win);
  my_widget_unref((my_widget_t *)main_win);

  dlg = my_dialog_create(NULL, pal, "confirm", 200, 120);
  my_dialog_add_button(dlg, "Yes", 1);
  my_dialog_open(dlg, wm, on_result, NULL);
  ASSERT_EQ(my_window_manager_count(wm), 2);
  ASSERT_TRUE(my_window_manager_top(wm) == dlg->win);
  ASSERT_TRUE(main_win->scrim);

  my_widget_invalidate(my_window_widget(dlg->win), NULL);
  my_window_paint(dlg->win);

  e = my_event_init(MY_EVENT_POINTER_DOWN);
  e.u.pointer.x = 20; e.u.pointer.y = 20; e.u.pointer.button = 1;
  my_pal_dummy_inject_event(pal, main_win->pal_window, &e);
  e = my_event_init(MY_EVENT_POINTER_UP);
  e.u.pointer.x = 20; e.u.pointer.y = 20; e.u.pointer.button = 1;
  my_pal_dummy_inject_event(pal, main_win->pal_window, &e);

  g_result = -999;
  e = my_event_init(MY_EVENT_KEY_DOWN);
  e.u.key.key = MY_KEY_ESCAPE;
  my_pal_dummy_inject_event(pal, dlg->win->pal_window, &e);
  pump(pal, loop);
  ASSERT_EQ(g_result, MY_DIALOG_CANCEL);
  ASSERT_EQ(my_window_manager_count(wm), 1);
  ASSERT_TRUE(!main_win->scrim);

  my_dialog_destroy(dlg);
  my_window_manager_destroy(wm);
  my_pal_main_loop_destroy(loop);
  my_pal_destroy(pal);
}

TEST(window_manager_rejects_duplicate_window_open)
{
  my_pal_t* pal = my_pal_dummy_create(NULL);
  my_pal_main_loop_t* loop = my_pal_main_loop_create(pal);
  my_window_manager_t* wm = my_window_manager_create(NULL, pal, loop);
  my_window_t* win = my_window_create(NULL, pal, 100, 80, "duplicate");

  ASSERT_NOT_NULL(pal);
  ASSERT_NOT_NULL(loop);
  ASSERT_NOT_NULL(wm);
  ASSERT_NOT_NULL(win);
  ASSERT_EQ(my_window_manager_open(wm, win), MY_RET_OK);
  ASSERT_EQ(my_window_manager_open(wm, win), MY_RET_INVALID_PARAMS);
  ASSERT_EQ(my_window_manager_count(wm), 1u);

  my_widget_unref((my_widget_t*)win);
  my_window_manager_destroy(wm);
  my_pal_main_loop_destroy(loop);
  my_pal_destroy(pal);
}

TEST(window_manager_destroy_listener_reentry_is_guarded)
{
  my_pal_t* pal = my_pal_dummy_create(NULL);
  my_pal_main_loop_t* loop;
  my_window_manager_t* wm;
  manager_destroy_reentry_t state;
  uint32_t id;

  ASSERT_NOT_NULL(pal);
  loop = my_pal_main_loop_create(pal);
  wm = my_window_manager_create(NULL, pal, loop);
  ASSERT_NOT_NULL(loop);
  ASSERT_NOT_NULL(wm);
  state.manager = wm;
  state.calls = 0;
  state.rejected_id = 0u;
  id = my_window_manager_add_destroy_listener(wm,
                                               manager_destroy_reentry_cb,
                                               &state);
  ASSERT_TRUE(id != 0u);
  my_window_manager_destroy(wm);
  ASSERT_EQ(state.calls, 1);
  ASSERT_EQ(state.rejected_id, 0u);
  my_pal_main_loop_destroy(loop);
  my_pal_destroy(pal);
}

TEST(dialog_rejects_duplicate_open_without_state_corruption)
{
  my_pal_t* pal = my_pal_dummy_create(NULL);
  my_pal_main_loop_t* loop = my_pal_main_loop_create(pal);
  my_window_manager_t* wm = my_window_manager_create(NULL, pal, loop);
  my_window_t* base = my_window_create(NULL, pal, 120, 80, "base");
  my_dialog_t* dlg = my_dialog_create(NULL, pal, "dialog", 80, 60);

  ASSERT_NOT_NULL(wm);
  ASSERT_NOT_NULL(base);
  ASSERT_NOT_NULL(dlg);
  ASSERT_EQ(my_window_manager_open(wm, base), MY_RET_OK);
  ASSERT_EQ(my_dialog_open(dlg, wm, NULL, NULL), MY_RET_OK);
  ASSERT_EQ(my_dialog_open(dlg, wm, NULL, NULL), MY_RET_INVALID_PARAMS);
  ASSERT_EQ(my_window_manager_count(wm), 2u);
  ASSERT_TRUE(dlg->wm == wm);
  ASSERT_TRUE(dlg->win->modal);

  my_dialog_close(dlg, MY_DIALOG_CANCEL);
  my_dialog_destroy(dlg);
  my_widget_unref((my_widget_t*)base);
  my_window_manager_destroy(wm);
  my_pal_main_loop_destroy(loop);
  my_pal_destroy(pal);
}

TEST(dialog_detaches_when_window_manager_is_destroyed_first)
{
  my_pal_t* pal = my_pal_dummy_create(NULL);
  my_pal_main_loop_t* loop = my_pal_main_loop_create(pal);
  my_window_manager_t* wm = my_window_manager_create(NULL, pal, loop);
  my_dialog_t* dlg = my_dialog_create(NULL, pal, "dialog", 80, 60);

  ASSERT_NOT_NULL(wm);
  ASSERT_NOT_NULL(dlg);
  ASSERT_EQ(my_dialog_open(dlg, wm, NULL, NULL), MY_RET_OK);
  ASSERT_TRUE(dlg->wm == wm);
  my_window_manager_destroy(wm);
  ASSERT_TRUE(dlg->wm == NULL);
  ASSERT_EQ(dlg->wm_destroy_listener_id, 0u);

  my_dialog_close(dlg, 7);
  my_dialog_destroy(dlg);
  my_pal_main_loop_destroy(loop);
  my_pal_destroy(pal);
}

TEST(dialog_detaches_when_window_is_closed_directly)
{
  my_pal_t* pal = my_pal_dummy_create(NULL);
  my_pal_main_loop_t* loop = my_pal_main_loop_create(pal);
  my_window_manager_t* wm = my_window_manager_create(NULL, pal, loop);
  my_window_t* base = my_window_create(NULL, pal, 160, 100, "base");
  my_dialog_t* dlg = my_dialog_create(NULL, pal, "dialog", 80, 60);

  ASSERT_NOT_NULL(wm);
  ASSERT_NOT_NULL(base);
  ASSERT_NOT_NULL(dlg);
  ASSERT_EQ(my_window_manager_open(wm, base), MY_RET_OK);
  ASSERT_EQ(my_dialog_open(dlg, wm, NULL, NULL), MY_RET_OK);
  ASSERT_TRUE(dlg->wm == wm);
  ASSERT_TRUE(dlg->window_close_listener_id != 0u);

  ASSERT_EQ(my_window_manager_close(wm, dlg->win), MY_RET_OK);
  ASSERT_TRUE(dlg->wm == NULL);
  ASSERT_EQ(dlg->wm_destroy_listener_id, 0u);
  ASSERT_EQ(dlg->window_close_listener_id, 0u);
  ASSERT_FALSE(dlg->win->modal);

  my_dialog_destroy(dlg);
  my_widget_unref((my_widget_t*)base);
  my_window_manager_destroy(wm);
  my_pal_main_loop_destroy(loop);
  my_pal_destroy(pal);
}

TEST(shared_surface_routes_input_to_modal)
{
  my_pal_t *pal = my_pal_dummy_create(NULL);
  my_pal_main_loop_t *loop = my_pal_main_loop_create(pal);
  my_window_manager_t *wm = my_window_manager_create(NULL, pal, loop);
  my_window_t *main_win = my_window_create(NULL, pal, 400, 300, "main");
  my_widget_t *main_btn = my_button_create(NULL, "main");
  my_dialog_t *dlg;
  my_widget_t *dialog_btn;
  my_event_t e;

  g_main_clicks = 0;
  g_dialog_clicks = 0;
  my_widget_set_rect(main_btn, &(my_rect_t){10, 10, 80, 32});
  my_widget_on(main_btn, "click", count_click, &g_main_clicks);
  my_widget_add_child(my_window_widget(main_win), main_btn);
  my_widget_unref(main_btn);
  ASSERT_EQ(my_window_manager_open(wm, main_win), MY_RET_OK);
  my_widget_unref((my_widget_t *)main_win);

  dlg = my_dialog_create(NULL, pal, "confirm", 200, 120);
  ASSERT_EQ(my_dialog_add_button(dlg, "Yes", 1), MY_RET_OK);
  ASSERT_EQ(my_dialog_open(dlg, wm, on_result, NULL), MY_RET_OK);
  ((my_widget_t*)dlg->win)->rect.x = 100;
  ((my_widget_t*)dlg->win)->rect.y = 90;
  my_widget_relayout((my_widget_t*)dlg->win);
  dialog_btn = my_widget_get_child(dlg->btn_row, 0);
  my_widget_on(dialog_btn, "click", count_click, &g_dialog_clicks);

  e = my_event_init(MY_EVENT_POINTER_DOWN);
  e.u.pointer.x = 110;
  e.u.pointer.y = 100;
  e.u.pointer.button = 1;
  ASSERT_EQ(my_window_manager_dispatch_surface_event(wm, &e), MY_RET_OK);
  e = my_event_init(MY_EVENT_POINTER_UP);
  e.u.pointer.x = 110;
  e.u.pointer.y = 100;
  e.u.pointer.button = 1;
  ASSERT_EQ(my_window_manager_dispatch_surface_event(wm, &e), MY_RET_OK);
  ASSERT_EQ(g_main_clicks, 0);

  e = my_event_init(MY_EVENT_POINTER_DOWN);
  e.u.pointer.x = ((my_widget_t*)dlg->win)->rect.x + dialog_btn->rect.x + 4;
  e.u.pointer.y = ((my_widget_t*)dlg->win)->rect.y +
                  dlg->btn_row->rect.y + dialog_btn->rect.y + 4;
  e.u.pointer.button = 1;
  ASSERT_EQ(my_window_manager_dispatch_surface_event(wm, &e), MY_RET_OK);
  e.type = MY_EVENT_POINTER_UP;
  ASSERT_EQ(my_window_manager_dispatch_surface_event(wm, &e), MY_RET_OK);
  ASSERT_EQ(g_dialog_clicks, 1);

  pump(pal, loop);
  my_dialog_destroy(dlg);
  my_window_manager_destroy(wm);
  my_pal_main_loop_destroy(loop);
  my_pal_destroy(pal);
}

TEST(shared_surface_routes_keyboard_to_pointer_window)
{
  my_pal_t *pal = my_pal_dummy_create(NULL);
  my_pal_main_loop_t *loop = my_pal_main_loop_create(pal);
  my_window_manager_t *wm = my_window_manager_create(NULL, pal, loop);
  my_window_t *bottom = my_window_create(NULL, pal, 400, 300, "bottom");
  my_window_t *top = my_window_create(NULL, pal, 400, 300, "top");
  my_widget_t *bottom_input = my_widget_create(NULL, "bottom_input");
  my_widget_t *top_input = my_widget_create(NULL, "top_input");
  surface_focus_ctx_t bottom_ctx = {0};
  surface_focus_ctx_t top_ctx = {0};
  my_event_t event;

  ASSERT_NOT_NULL(pal);
  ASSERT_NOT_NULL(loop);
  ASSERT_NOT_NULL(wm);
  ASSERT_NOT_NULL(bottom);
  ASSERT_NOT_NULL(top);
  ASSERT_NOT_NULL(bottom_input);
  ASSERT_NOT_NULL(top_input);
  ASSERT_EQ(my_widget_subclass_init(bottom_input, &s_surface_focus_vtable),
            MY_RET_OK);
  ASSERT_EQ(my_widget_subclass_init(top_input, &s_surface_focus_vtable),
            MY_RET_OK);
  bottom_input->focusable = true;
  top_input->focusable = true;
  ASSERT_EQ(my_widget_set_user_data(bottom_input, &bottom_ctx), MY_RET_OK);
  ASSERT_EQ(my_widget_set_user_data(top_input, &top_ctx), MY_RET_OK);
  ASSERT_EQ(my_widget_set_rect(bottom_input, &(my_rect_t){10, 10, 80, 32}),
            MY_RET_OK);
  ASSERT_EQ(my_widget_set_rect(top_input, &(my_rect_t){10, 10, 80, 32}),
            MY_RET_OK);
  ASSERT_EQ(my_widget_add_child(my_window_widget(bottom), bottom_input),
            MY_RET_OK);
  ASSERT_EQ(my_widget_add_child(my_window_widget(top), top_input), MY_RET_OK);
  my_widget_unref(bottom_input);
  my_widget_unref(top_input);
  ASSERT_EQ(my_window_manager_open(wm, bottom), MY_RET_OK);
  my_widget_unref((my_widget_t *)bottom);
  ASSERT_EQ(my_window_manager_open(wm, top), MY_RET_OK);
  my_widget_unref((my_widget_t *)top);
  ASSERT_EQ(my_widget_set_rect(my_window_widget(top),
                               &(my_rect_t){220, 0, 180, 140}),
            MY_RET_OK);
  my_event_dispatcher_set_focus(&top->dispatcher, top_input);

  event = my_event_init(MY_EVENT_KEY_DOWN);
  event.u.key.key = MY_KEY_RETURN;
  ASSERT_EQ(my_window_manager_dispatch_surface_event(wm, &event), MY_RET_OK);
  ASSERT_EQ(top_ctx.key_down, 1);
  ASSERT_EQ(bottom_ctx.key_down, 0);

  event = my_event_init(MY_EVENT_POINTER_DOWN);
  event.u.pointer.x = 230;
  event.u.pointer.y = 10;
  ASSERT_EQ(my_window_manager_dispatch_surface_event(wm, &event), MY_RET_OK);
  event = my_event_init(MY_EVENT_POINTER_UP);
  event.u.pointer.x = 230;
  event.u.pointer.y = 10;
  ASSERT_EQ(my_window_manager_dispatch_surface_event(wm, &event), MY_RET_OK);

  event = my_event_init(MY_EVENT_POINTER_DOWN);
  event.u.pointer.x = 20;
  event.u.pointer.y = 20;
  ASSERT_EQ(my_window_manager_dispatch_surface_event(wm, &event), MY_RET_OK);
  event = my_event_init(MY_EVENT_KEY_DOWN);
  event.u.key.key = MY_KEY_RETURN;
  ASSERT_EQ(my_window_manager_dispatch_surface_event(wm, &event), MY_RET_OK);
  ASSERT_EQ(bottom_ctx.key_down, 1);
  ASSERT_EQ(top_ctx.key_down, 1);

  ASSERT_EQ(my_window_manager_close(wm, bottom), MY_RET_OK);
  ASSERT_EQ(my_window_manager_dispatch_surface_event(wm, &event), MY_RET_OK);
  ASSERT_EQ(top_ctx.key_down, 2);

  my_window_manager_destroy(wm);
  my_pal_main_loop_destroy(loop);
  my_pal_destroy(pal);
}

TEST(button_cooldown_blocks_reentry_and_exposes_progress)
{
  my_pal_t *pal = my_pal_dummy_create(NULL);
  my_pal_main_loop_t *loop = my_pal_main_loop_create(pal);
  my_window_manager_t *wm = my_window_manager_create(NULL, pal, loop);
  my_window_t *win = my_window_create(NULL, pal, 160, 100, "cooldown");
  my_widget_t *button = my_button_create(NULL, "send");
  int clicks = 0;

  ASSERT_NOT_NULL(pal);
  ASSERT_NOT_NULL(loop);
  ASSERT_NOT_NULL(wm);
  ASSERT_NOT_NULL(win);
  ASSERT_NOT_NULL(button);
  ASSERT_EQ(my_button_set_cooldown(button, 1000), MY_RET_OK);
  ASSERT_FALSE(my_button_is_cooling_down(button));
  ASSERT_EQ(my_button_cooldown_remaining_ms(button), 0u);
  ASSERT_FLOAT_EQ(my_button_cooldown_progress(button), 0.0f, 0.0001f);
  ASSERT_EQ(my_widget_set_rect(button, &(my_rect_t){10, 10, 80, 32}), MY_RET_OK);
  ASSERT_NEQ(my_widget_on(button, "click", count_click, &clicks), 0u);
  ASSERT_EQ(my_widget_add_child(my_window_widget(win), button), MY_RET_OK);
  my_widget_unref(button);
  ASSERT_EQ(my_window_manager_open(wm, win), MY_RET_OK);
  my_widget_unref((my_widget_t *)win);

  my_pal_dummy_set_now_ms(pal, 1000);
  dispatch_button_click(wm, 20, 20);
  ASSERT_EQ(clicks, 1);
  ASSERT_TRUE(my_button_is_cooling_down(my_widget_get_child(my_window_widget(win), 0)));
  ASSERT_EQ(my_button_cooldown_remaining_ms(my_widget_get_child(my_window_widget(win), 0)),
            1000u);
  ASSERT_FLOAT_EQ(my_button_cooldown_progress(
                      my_widget_get_child(my_window_widget(win), 0)),
                  1.0f, 0.0001f);

  my_pal_dummy_set_now_ms(pal, 1500);
  ASSERT_EQ(my_button_set_cooldown(my_widget_get_child(my_window_widget(win), 0),
                                   2000),
            MY_RET_OK);
  dispatch_button_click(wm, 20, 20);
  ASSERT_EQ(clicks, 1);
  ASSERT_EQ(my_button_cooldown_remaining_ms(my_widget_get_child(my_window_widget(win), 0)),
            500u);
  ASSERT_TRUE(my_button_cooldown_progress(
                  my_widget_get_child(my_window_widget(win), 0)) < 1.0f);

  my_pal_dummy_set_now_ms(pal, 2000);
  ASSERT_FALSE(my_button_is_cooling_down(my_widget_get_child(my_window_widget(win), 0)));
  ASSERT_EQ(my_button_cooldown_remaining_ms(my_widget_get_child(my_window_widget(win), 0)),
            0u);
  ASSERT_FLOAT_EQ(my_button_cooldown_progress(
                      my_widget_get_child(my_window_widget(win), 0)),
                  0.0f, 0.0001f);
  dispatch_button_click(wm, 20, 20);
  ASSERT_EQ(clicks, 2);

  my_window_manager_destroy(wm);
  my_pal_main_loop_destroy(loop);
  my_pal_destroy(pal);
}

TEST(scroll_containers_unlink_scroll_bar_before_destroy)
{
  my_widget_t* bar = my_scroll_bar_create(NULL);
  my_scroll_view_t* scroll_view = my_scroll_view_create(NULL);
  my_widget_t* list_view = my_list_view_create(NULL);
  my_widget_t* text_area = my_text_area_create(NULL);

  ASSERT_NOT_NULL(bar);
  ASSERT_NOT_NULL(scroll_view);
  ASSERT_NOT_NULL(list_view);
  ASSERT_NOT_NULL(text_area);
  ASSERT_EQ(my_scroll_view_set_scroll_bar(scroll_view, bar), MY_RET_OK);
  ASSERT_EQ(my_scroll_view_set_scroll_bar(scroll_view, bar), MY_RET_OK);
  ASSERT_EQ(my_list_view_set_scroll_bar(list_view, bar), MY_RET_OK);
  ASSERT_EQ(my_list_view_set_scroll_bar(list_view, bar), MY_RET_OK);
  ASSERT_EQ(my_text_area_set_scroll_bar(text_area, bar), MY_RET_OK);
  ASSERT_EQ(my_text_area_set_scroll_bar(text_area, bar), MY_RET_OK);

  my_widget_unref((my_widget_t*)scroll_view);
  my_widget_unref(list_view);
  my_widget_unref(text_area);
  ASSERT_EQ(my_emitter_emit(bar->emitter, "changed", NULL), MY_RET_OK);
  my_widget_unref(bar);
}

TEST(scroll_containers_reject_non_scroll_bar_without_rebinding)
{
  my_widget_t* bar = my_scroll_bar_create(NULL);
  my_widget_t* invalid = my_widget_create(NULL, "not-a-scroll-bar");
  my_scroll_view_t* scroll_view = my_scroll_view_create(NULL);
  my_widget_t* list_view = my_list_view_create(NULL);
  my_widget_t* text_area = my_text_area_create(NULL);

  ASSERT_NOT_NULL(bar);
  ASSERT_NOT_NULL(invalid);
  ASSERT_NOT_NULL(scroll_view);
  ASSERT_NOT_NULL(list_view);
  ASSERT_NOT_NULL(text_area);
  ASSERT_EQ(my_scroll_bar_set_value(invalid, 0.5f), MY_RET_INVALID_PARAMS);
  ASSERT_EQ(my_scroll_bar_set_page_size(invalid, 0.5f), MY_RET_INVALID_PARAMS);
  ASSERT_FLOAT_EQ(my_scroll_bar_get_value(invalid), 0.0f, 0.0001f);
  ASSERT_FLOAT_EQ(my_scroll_bar_get_page_size(invalid), 0.0f, 0.0001f);
  ASSERT_EQ(my_scroll_view_set_scroll_bar(scroll_view, bar), MY_RET_OK);
  ASSERT_EQ(my_list_view_set_scroll_bar(list_view, bar), MY_RET_OK);
  ASSERT_EQ(my_text_area_set_scroll_bar(text_area, bar), MY_RET_OK);

  ASSERT_EQ(my_scroll_view_set_scroll_bar(scroll_view, invalid),
            MY_RET_INVALID_PARAMS);
  ASSERT_EQ(my_list_view_set_scroll_bar(list_view, invalid),
            MY_RET_INVALID_PARAMS);
  ASSERT_EQ(my_text_area_set_scroll_bar(text_area, invalid),
            MY_RET_INVALID_PARAMS);

  ASSERT_EQ(my_scroll_view_set_scroll_bar(scroll_view, NULL), MY_RET_OK);
  ASSERT_EQ(my_list_view_set_scroll_bar(list_view, NULL), MY_RET_OK);
  ASSERT_EQ(my_text_area_set_scroll_bar(text_area, NULL), MY_RET_OK);
  my_widget_unref((my_widget_t*)scroll_view);
  my_widget_unref(list_view);
  my_widget_unref(text_area);
  my_widget_unref(invalid);
  my_widget_unref(bar);
}

TEST(scroll_containers_keep_linked_scroll_bar_alive)
{
  my_widget_t* bar = my_scroll_bar_create(NULL);
  my_scroll_view_t* scroll_view = my_scroll_view_create(NULL);
  my_widget_t* list_view = my_list_view_create(NULL);
  my_widget_t* text_area = my_text_area_create(NULL);

  ASSERT_NOT_NULL(bar);
  ASSERT_NOT_NULL(scroll_view);
  ASSERT_NOT_NULL(list_view);
  ASSERT_NOT_NULL(text_area);
  ASSERT_EQ(my_scroll_view_set_scroll_bar(scroll_view, bar), MY_RET_OK);
  ASSERT_EQ(my_list_view_set_scroll_bar(list_view, bar), MY_RET_OK);
  ASSERT_EQ(my_text_area_set_scroll_bar(text_area, bar), MY_RET_OK);

  my_widget_unref(bar);
  ASSERT_EQ(my_scroll_bar_set_value(bar, 0.5f), MY_RET_OK);
  ASSERT_EQ(my_emitter_emit(bar->emitter, "changed", NULL), MY_RET_OK);
  my_widget_unref((my_widget_t*)scroll_view);
  my_widget_unref(list_view);
  my_widget_unref(text_area);
}

TEST(widget_specific_setters_reject_plain_widget)
{
  my_widget_t* plain = my_widget_create(NULL, "plain");
  my_widget_t* button = my_button_create(NULL, "button");
  my_widget_t* checkbox = my_checkbox_create(NULL, "checkbox");
  my_widget_t* edit = my_edit_create(NULL);
  my_widget_t* image = my_image_create(NULL);
  my_widget_t* label = my_label_create(NULL, "label");
  my_widget_t* list = my_list_view_create(NULL);
  my_widget_t* progress = my_progress_bar_create(NULL);
  my_widget_t* scrollbar = my_scroll_bar_create(NULL);
  my_widget_t* slider = my_slider_create(NULL);
  my_widget_t* area = my_text_area_create(NULL);

  ASSERT_NOT_NULL(plain);
  ASSERT_NOT_NULL(button);
  ASSERT_NOT_NULL(checkbox);
  ASSERT_NOT_NULL(edit);
  ASSERT_NOT_NULL(image);
  ASSERT_NOT_NULL(label);
  ASSERT_NOT_NULL(list);
  ASSERT_NOT_NULL(progress);
  ASSERT_NOT_NULL(scrollbar);
  ASSERT_NOT_NULL(slider);
  ASSERT_NOT_NULL(area);
  ASSERT_EQ(my_button_set_text(plain, "x"), MY_RET_INVALID_PARAMS);
  ASSERT_EQ(my_checkbox_set_text(plain, "x"), MY_RET_INVALID_PARAMS);
  ASSERT_EQ(my_edit_set_text(plain, "x"), MY_RET_INVALID_PARAMS);
  ASSERT_EQ(my_image_set_image(plain, "x"), MY_RET_INVALID_PARAMS);
  ASSERT_EQ(my_label_set_text(plain, "x"), MY_RET_INVALID_PARAMS);
  ASSERT_EQ(my_list_view_set_row_height(plain, 20), MY_RET_INVALID_PARAMS);
  ASSERT_EQ(my_list_view_set_scroll_offset(plain, 20), MY_RET_INVALID_PARAMS);
  ASSERT_EQ(my_progress_bar_set_value(plain, 1.0f), MY_RET_INVALID_PARAMS);
  ASSERT_FLOAT_EQ(my_progress_bar_get_value(plain), 0.0f, 0.0001f);
  ASSERT_EQ(my_scroll_bar_set_value(plain, 0.5f), MY_RET_INVALID_PARAMS);
  ASSERT_EQ(my_slider_set_value(plain, 0.5f), MY_RET_INVALID_PARAMS);
  ASSERT_EQ(my_text_area_set_text(plain, "x"), MY_RET_INVALID_PARAMS);
  ASSERT_EQ(my_text_area_set_wrap(plain, true), MY_RET_INVALID_PARAMS);
  ASSERT_EQ(my_rich_label_add_segment(plain, "x", 0, false),
            MY_RET_INVALID_PARAMS);
  ASSERT_FALSE(my_rich_label_is_instance(plain));
  ASSERT_EQ(my_rich_label_content_width(plain), 0);
  my_rich_label_clear(plain);

  my_widget_unref(plain);
  my_widget_unref(button);
  my_widget_unref(checkbox);
  my_widget_unref(edit);
  my_widget_unref(image);
  my_widget_unref(label);
  my_widget_unref(list);
  my_widget_unref(progress);
  my_widget_unref(scrollbar);
  my_widget_unref(slider);
  my_widget_unref(area);
}

TEST(image_cache_is_loader_scoped_and_respects_loader_ownership)
{
  image_test_loader_t first = {{&image_test_loader_vtable}, {255, 0, 0, 255},
                               0, 0, false, 0};
  image_test_loader_t second = {{&image_test_loader_vtable},
                                {0, 255, 0, 255}, 0, 0, false, 0};
  my_widget_t* first_image = my_image_create(NULL);
  my_widget_t* second_image = my_image_create(NULL);
  my_lcd_t* lcd = my_lcd_mem_create(NULL, 4, 4, MY_PIXEL_FORMAT_BGRA8888);
  my_vgcanvas_t* canvas;
  my_image_loader_lease_t* first_lease;
  my_image_loader_lease_t* second_lease;

  ASSERT_NOT_NULL(first_image);
  ASSERT_NOT_NULL(second_image);
  ASSERT_NOT_NULL(lcd);
  canvas = my_vgcanvas_soft_create(NULL, lcd);
  ASSERT_NOT_NULL(canvas);
  first_lease = my_image_loader_lease_create(NULL, &first.base, NULL,
                                             image_test_release);
  second_lease = my_image_loader_lease_create(NULL, &second.base, NULL,
                                              image_test_release);
  ASSERT_NOT_NULL(first_lease);
  ASSERT_NOT_NULL(second_lease);
  ASSERT_EQ(my_image_set_loader_lease(first_image, first_lease), MY_RET_OK);
  ASSERT_EQ(my_image_set_loader_lease(second_image, second_lease), MY_RET_OK);
  my_image_loader_lease_unref(first_lease);
  my_image_loader_lease_unref(second_lease);
  ASSERT_EQ(my_image_set_image(first_image, "same-image-key"), MY_RET_OK);
  ASSERT_EQ(my_image_set_image(second_image, "same-image-key"), MY_RET_OK);
  ASSERT_EQ(my_widget_set_rect(first_image, &(my_rect_t){0, 0, 1, 1}),
            MY_RET_OK);
  ASSERT_EQ(my_widget_set_rect(second_image, &(my_rect_t){0, 0, 1, 1}),
            MY_RET_OK);
  ASSERT_EQ(my_vgcanvas_begin_frame(canvas, NULL), MY_RET_OK);
  my_widget_paint(first_image, canvas);
  my_widget_paint(first_image, canvas);
  my_widget_paint(second_image, canvas);
  ASSERT_EQ(my_vgcanvas_end_frame(canvas), MY_RET_OK);
  ASSERT_EQ(first.load_count, 1);
  ASSERT_EQ(second.load_count, 1);
  ASSERT_EQ(first.free_count, 1);
  ASSERT_EQ(second.free_count, 1);
  ASSERT_EQ(first.lease_release_count, 0);
  ASSERT_EQ(second.lease_release_count, 0);

  my_vgcanvas_destroy(canvas);
  my_lcd_destroy(lcd);
  my_widget_unref(first_image);
  my_widget_unref(second_image);
  my_image_cache_clear();
}

TEST(image_loader_with_invalid_vtable_or_data_fails_safely)
{
  image_test_loader_t loader = {{&image_test_loader_vtable},
                                {1, 2, 3, 255}, 0, 0, true, 0};
  my_image_loader_t invalid = {NULL};
  my_widget_t* image = my_image_create(NULL);
  my_lcd_t* lcd = my_lcd_mem_create(NULL, 2, 2, MY_PIXEL_FORMAT_BGRA8888);
  my_vgcanvas_t* canvas;

  ASSERT_NOT_NULL(image);
  ASSERT_NOT_NULL(lcd);
  canvas = my_vgcanvas_soft_create(NULL, lcd);
  ASSERT_NOT_NULL(canvas);
  ASSERT_EQ(my_image_set_loader(image, &invalid), MY_RET_INVALID_PARAMS);
  ASSERT_EQ(my_image_loader_load(&invalid, "invalid-loader"), NULL);
  my_image_loader_free_data(&invalid, (my_image_data_t*)1);
  my_image_loader_destroy(&invalid);
  ASSERT_EQ(my_image_set_image(image, "invalid-loader"), MY_RET_OK);
  ASSERT_EQ(my_vgcanvas_begin_frame(canvas, NULL), MY_RET_OK);
  my_widget_paint(image, canvas);
  ASSERT_EQ(my_vgcanvas_end_frame(canvas), MY_RET_OK);
  ASSERT_EQ(my_image_set_loader(image, &loader.base), MY_RET_OK);
  ASSERT_EQ(my_vgcanvas_begin_frame(canvas, NULL), MY_RET_OK);
  my_widget_paint(image, canvas);
  ASSERT_EQ(my_vgcanvas_end_frame(canvas), MY_RET_OK);
  ASSERT_EQ(loader.load_count, 1);
  ASSERT_EQ(loader.free_count, 1);

  my_vgcanvas_destroy(canvas);
  my_lcd_destroy(lcd);
  my_widget_unref(image);
  my_image_cache_clear();
}

TEST(image_loader_lease_releases_once_when_widget_and_cache_drop_references)
{
  image_test_loader_t loader = {{&image_test_loader_vtable},
                                {5, 6, 7, 255}, 0, 0, false, 0};
  my_image_loader_lease_t* lease = my_image_loader_lease_create(
      NULL, &loader.base, NULL, image_test_release);
  my_widget_t* image = my_image_create(NULL);
  my_lcd_t* lcd = my_lcd_mem_create(NULL, 2, 2, MY_PIXEL_FORMAT_BGRA8888);
  my_vgcanvas_t* canvas;
  char path[32];
  size_t index;

  ASSERT_NOT_NULL(lease);
  ASSERT_NOT_NULL(image);
  ASSERT_NOT_NULL(lcd);
  canvas = my_vgcanvas_soft_create(NULL, lcd);
  ASSERT_NOT_NULL(canvas);
  ASSERT_EQ(my_image_set_loader_lease(image, lease), MY_RET_OK);
  my_image_loader_lease_unref(lease);
  for (index = 0; index < 9u; index++) {
    (void)snprintf(path, sizeof(path), "lease-only-%zu", index);
    ASSERT_EQ(my_image_set_image(image, path), MY_RET_OK);
    ASSERT_EQ(my_vgcanvas_begin_frame(canvas, NULL), MY_RET_OK);
    my_widget_paint(image, canvas);
    ASSERT_EQ(my_vgcanvas_end_frame(canvas), MY_RET_OK);
  }
  my_widget_unref(image);
  ASSERT_EQ(loader.lease_release_count, 0);

  image = my_image_create(NULL);
  ASSERT_NOT_NULL(image);
  ASSERT_EQ(my_image_set_loader(image, &loader.base), MY_RET_OK);
  for (index = 0; index < 9u; index++) {
    (void)snprintf(path, sizeof(path), "flush-%zu", index);
    ASSERT_EQ(my_image_set_image(image, path), MY_RET_OK);
    ASSERT_EQ(my_vgcanvas_begin_frame(canvas, NULL), MY_RET_OK);
    my_widget_paint(image, canvas);
    ASSERT_EQ(my_vgcanvas_end_frame(canvas), MY_RET_OK);
  }
  ASSERT_EQ(loader.lease_release_count, 0);
  my_widget_unref(image);
  my_vgcanvas_destroy(canvas);
  my_lcd_destroy(lcd);
  my_image_cache_clear();
  ASSERT_EQ(loader.lease_release_count, 1);
}

TEST(myui_ref_count_rejects_overflow_without_wrapping)
{
  atomic_uint count;

  atomic_init(&count, UINT_MAX);
  ASSERT_FALSE(my_ref_count_try_ref(&count));
  ASSERT_EQ(atomic_load_explicit(&count, memory_order_relaxed), UINT_MAX);

  atomic_store_explicit(&count, UINT_MAX - 1u, memory_order_relaxed);
  ASSERT_TRUE(my_ref_count_try_ref(&count));
  ASSERT_EQ(atomic_load_explicit(&count, memory_order_relaxed), UINT_MAX);
  ASSERT_FALSE(my_ref_count_try_ref(&count));
  ASSERT_FALSE(my_ref_count_release(&count));
  ASSERT_EQ(atomic_load_explicit(&count, memory_order_relaxed), UINT_MAX);

  atomic_store_explicit(&count, 0u, memory_order_relaxed);
  ASSERT_FALSE(my_ref_count_try_ref(&count));
  ASSERT_EQ(atomic_load_explicit(&count, memory_order_relaxed), 0u);
}

TEST(image_borrowed_loader_uses_transient_data_without_cache_retention)
{
  image_test_loader_t loader = {{&image_test_loader_vtable},
                                {9, 8, 7, 255}, 0, 0, false, 0};
  my_widget_t* image = my_image_create(NULL);
  my_lcd_t* lcd = my_lcd_mem_create(NULL, 2, 2, MY_PIXEL_FORMAT_BGRA8888);
  my_vgcanvas_t* canvas;

  ASSERT_NOT_NULL(image);
  ASSERT_NOT_NULL(lcd);
  canvas = my_vgcanvas_soft_create(NULL, lcd);
  ASSERT_NOT_NULL(canvas);
  ASSERT_EQ(my_image_set_loader(image, &loader.base), MY_RET_OK);
  ASSERT_EQ(my_image_set_image(image, "borrowed-image"), MY_RET_OK);
  ASSERT_EQ(my_vgcanvas_begin_frame(canvas, NULL), MY_RET_OK);
  my_widget_paint(image, canvas);
  ASSERT_EQ(my_vgcanvas_end_frame(canvas), MY_RET_OK);
  ASSERT_EQ(loader.load_count, 1);
  ASSERT_EQ(loader.free_count, 1);
  ASSERT_EQ(my_vgcanvas_begin_frame(canvas, NULL), MY_RET_OK);
  my_widget_paint(image, canvas);
  ASSERT_EQ(my_vgcanvas_end_frame(canvas), MY_RET_OK);
  ASSERT_EQ(loader.load_count, 2);
  ASSERT_EQ(loader.free_count, 2);

  my_vgcanvas_destroy(canvas);
  my_lcd_destroy(lcd);
  my_widget_unref(image);
  my_image_cache_clear();
}

TEST(widget_specific_queries_reject_plain_widget)
{
  my_widget_t* plain = my_widget_create(NULL, "plain");
  my_widget_t* node_view = my_node_view_create(NULL);
  int32_t x = 11, y = 13;
  float cx = 17.0f, cy = 19.0f;
  char* yaml = (char*)1;

  ASSERT_NOT_NULL(plain);
  ASSERT_NOT_NULL(node_view);
  ASSERT_FALSE(my_checkbox_get_checked(plain));
  ASSERT_FLOAT_EQ(my_slider_get_value(plain), 0.0f, 0.0001f);
  ASSERT_EQ(my_edit_get_text(plain)[0], '\0');
  ASSERT_EQ(my_text_area_get_text(plain)[0], '\0');
  ASSERT_EQ(my_text_area_content_left(plain), 0);
  ASSERT_EQ(my_text_area_line_count(plain), 0u);
  ASSERT_EQ(my_text_area_visual_line_count(plain), 0u);
  ASSERT_EQ(my_text_area_visual_line_at(plain, 0), NULL);
  ASSERT_EQ(my_text_area_visual_line_of_pos(plain, 0, 0, NULL), 0u);
  ASSERT_FALSE(my_text_area_line_numbers_enabled(plain));
  ASSERT_FALSE(my_text_area_syntax_enabled(plain));
  ASSERT_FALSE(my_text_area_syntax_line_ready(plain, 0));
  ASSERT_FALSE(my_text_area_is_folded(plain, 0));
  ASSERT_EQ(my_text_area_folds_to_yaml(plain, NULL, &yaml),
            MY_RET_INVALID_PARAMS);
  ASSERT_EQ(yaml, (char*)1);
  ASSERT_FALSE(my_node_is_instance(plain));
  ASSERT_EQ(my_node_socket_count(plain, MY_SOCKET_IN), 0u);
  ASSERT_FALSE(my_node_socket_center(plain, MY_SOCKET_IN, 0, &x, &y));
  ASSERT_EQ(my_node_socket_type_color(plain, MY_SOCKET_IN, 0), 0u);
  ASSERT_EQ(my_node_add_socket(plain, MY_SOCKET_IN, "x", 0),
            MY_RET_INVALID_PARAMS);
  ASSERT_FALSE(my_node_view_is_instance(plain));
  ASSERT_EQ(my_node_view_link_count(plain), 0u);
  ASSERT_EQ(my_node_view_get_selected(plain), -1);
  ASSERT_FALSE(my_node_view_is_selected(node_view, plain));
  ASSERT_FALSE(my_node_view_get_link(plain, 0, NULL, NULL, NULL, NULL));
  ASSERT_EQ(my_node_view_connect(plain, plain, 0, plain, 0),
            MY_RET_INVALID_PARAMS);
  ASSERT_EQ(my_node_view_disconnect_in(plain, plain, 0),
            MY_RET_INVALID_PARAMS);
  ASSERT_EQ(my_node_view_remove_node(plain, "x"), MY_RET_INVALID_PARAMS);
  ASSERT_EQ(my_node_view_find_link_at(plain, 0, 0), -1);
  ASSERT_FLOAT_EQ(my_node_view_get_zoom(plain), 1.0f, 0.0001f);
  ASSERT_FLOAT_EQ(my_node_view_flow_offset(plain), 0.0f, 0.0001f);
  my_node_view_screen_to_canvas(plain, 1, 2, &cx, &cy);
  ASSERT_FLOAT_EQ(cx, 17.0f, 0.0001f);
  ASSERT_FLOAT_EQ(cy, 19.0f, 0.0001f);
  ASSERT_EQ(my_node_view_selected_count(plain), 0u);
  ASSERT_EQ(my_node_view_selected_at(plain, 0), NULL);

  my_widget_unref(plain);
  my_widget_unref(node_view);
}

TEST(scroll_view_opaque_api_rejects_plain_widget)
{
  my_widget_t* plain = my_widget_create(NULL, "plain");
  my_scroll_view_t* view = my_scroll_view_create(NULL);
  my_widget_t* content = my_widget_create(NULL, "content");

  ASSERT_NOT_NULL(plain);
  ASSERT_NOT_NULL(view);
  ASSERT_NOT_NULL(content);
  ASSERT_FALSE(my_scroll_view_is_instance((my_scroll_view_t*)plain));
  ASSERT_EQ(my_scroll_view_get_offset((my_scroll_view_t*)plain), 0);
  ASSERT_EQ(my_scroll_view_get_content((my_scroll_view_t*)plain), NULL);
  ASSERT_EQ(my_scroll_view_set_content((my_scroll_view_t*)plain, content),
            MY_RET_INVALID_PARAMS);
  ASSERT_EQ(my_scroll_view_set_scroll_bar((my_scroll_view_t*)plain, NULL),
            MY_RET_INVALID_PARAMS);
  my_scroll_view_set_offset((my_scroll_view_t*)plain, 10);
  my_scroll_view_set_content_height((my_scroll_view_t*)plain, 10);
  ASSERT_EQ(my_scroll_view_widget((my_scroll_view_t*)plain), NULL);

  my_widget_unref(plain);
  my_widget_unref(content);
  my_widget_unref((my_widget_t*)view);
}

TEST(scroll_view_set_content_failure_preserves_previous_content)
{
  my_scroll_view_t* view = my_scroll_view_create(NULL);
  my_widget_t* previous = my_widget_create(NULL, "previous");
  my_widget_t* owner = my_widget_create(NULL, "owner");
  my_widget_t* candidate = my_widget_create(NULL, "candidate");

  ASSERT_NOT_NULL(view);
  ASSERT_NOT_NULL(previous);
  ASSERT_NOT_NULL(owner);
  ASSERT_NOT_NULL(candidate);
  ASSERT_EQ(my_scroll_view_set_content(view, previous), MY_RET_OK);
  ASSERT_EQ(my_widget_add_child(owner, candidate), MY_RET_OK);
  ASSERT_EQ(my_scroll_view_set_content(view, candidate), MY_RET_INVALID_PARAMS);
  ASSERT_EQ(my_scroll_view_get_content(view), previous);
  ASSERT_EQ(previous->parent, (my_widget_t*)view);
  ASSERT_EQ(candidate->parent, owner);

  my_widget_unref((my_widget_t*)view);
  my_widget_unref(previous);
  my_widget_unref(owner);
  my_widget_unref(candidate);
}

TEST(scroll_view_direct_content_removal_clears_borrowed_state)
{
  my_scroll_view_t* view = my_scroll_view_create(NULL);
  my_widget_t* content = my_widget_create(NULL, "content");
  my_widget_t* widget;

  ASSERT_NOT_NULL(view);
  ASSERT_NOT_NULL(content);
  widget = my_scroll_view_widget(view);
  ASSERT_NOT_NULL(widget);
  ASSERT_EQ(my_scroll_view_set_content(view, content), MY_RET_OK);
  ASSERT_EQ(my_widget_remove_child(widget, content), MY_RET_OK);
  ASSERT_EQ(my_scroll_view_get_content(view), NULL);
  my_scroll_view_set_content_height(view, 100);
  my_scroll_view_set_offset(view, 20);
  ASSERT_EQ(my_scroll_view_get_offset(view), 20);

  my_widget_unref(content);
  my_widget_unref(widget);
}

TEST(list_view_rejects_invalid_adapter_and_saturates_extreme_heights)
{
  my_widget_t* list = my_list_view_create(NULL);
  list_guard_adapter_t adapter = {{&list_guard_vtable}, NULL, 3u, INT32_MAX};
  my_list_adapter_t invalid = {NULL};
  int32_t old_offset;

  ASSERT_NOT_NULL(list);
  ASSERT_EQ(my_widget_set_rect(list, &(my_rect_t){0, 0, 100, 50}), MY_RET_OK);
  ASSERT_EQ(my_list_view_set_adapter(list, &invalid), MY_RET_INVALID_PARAMS);
  ASSERT_EQ(my_list_view_set_adapter(list, &adapter.base), MY_RET_OK);
  ASSERT_EQ(my_list_view_set_scroll_offset(list, INT32_MAX), MY_RET_OK);
  old_offset = my_list_view_get_scroll_offset(list);
  ASSERT_TRUE(old_offset >= 0);
  ASSERT_EQ(my_list_view_refresh(list), MY_RET_OK);
  ASSERT_TRUE(my_list_view_rows_created_total(list) <= 3u);

  my_widget_unref(list);
}

TEST(list_view_pool_oom_releases_recycle_reference)
{
  text_area_fail_alloc_t state = {false, false};
  my_allocator_t base = {&state, text_area_fail_alloc,
                         text_area_fail_calloc, text_area_fail_realloc,
                         text_area_fail_free};
  my_allocator_t* allocator = my_allocator_debug_create(&base);
  my_list_view_t* list;
  list_guard_adapter_t adapter;

  ASSERT_NOT_NULL(allocator);
  list = (my_list_view_t*)my_list_view_create(allocator);
  ASSERT_NOT_NULL(list);
  ASSERT_EQ(my_widget_set_rect((my_widget_t*)list,
                               &(my_rect_t){0, 0, 100, 50}), MY_RET_OK);
  adapter.base.vtable = &list_guard_vtable;
  adapter.allocator = allocator;
  adapter.count = 4u;
  adapter.height = 24;
  ASSERT_EQ(my_list_view_set_adapter((my_widget_t*)list, &adapter.base),
            MY_RET_OK);
  state.fail = true;
  ASSERT_EQ(my_list_view_refresh((my_widget_t*)list), MY_RET_OK);
  state.fail = false;
  my_widget_unref((my_widget_t*)list);
  ASSERT_EQ(my_allocator_debug_leak_count(allocator), 0);
  my_allocator_debug_destroy(allocator);
}

TEST(list_view_rejects_adapter_reentry_during_sync)
{
  my_widget_t* list = my_list_view_create(NULL);
  list_reentrant_adapter_t adapter = {{&list_reentrant_vtable}, list, 0, 0};

  ASSERT_NOT_NULL(list);
  ASSERT_EQ(my_widget_set_rect(list, &(my_rect_t){0, 0, 100, 50}), MY_RET_OK);
  ASSERT_EQ(my_list_view_set_adapter(list, &adapter.base), MY_RET_OK);
  ASSERT_TRUE(adapter.calls > 0);
  ASSERT_EQ(adapter.result, MY_RET_PENDING);
  ASSERT_EQ(my_list_view_get_scroll_offset(list), 0);
  my_widget_unref(list);
}

TEST(list_view_adapter_lease_preserves_lifetime_and_failed_install)
{
  my_widget_t* list = my_list_view_create(NULL);
  my_list_adapter_t invalid = {NULL};
  leased_list_adapter_t* first =
      (leased_list_adapter_t*)calloc(1, sizeof(*first));
  leased_list_adapter_t* second =
      (leased_list_adapter_t*)calloc(1, sizeof(*second));
  my_list_adapter_lease_t* first_lease;
  my_list_adapter_lease_t* second_lease;
  my_list_adapter_lease_t* invalid_lease;
  int first_destroyed = 0;
  int second_destroyed = 0;

  ASSERT_NOT_NULL(list);
  ASSERT_NOT_NULL(first);
  ASSERT_NOT_NULL(second);
  first->base.vtable = &leased_list_vtable;
  first->count = 3u;
  first->destroy_count = &first_destroyed;
  second->base.vtable = &leased_list_vtable;
  second->count = 2u;
  second->destroy_count = &second_destroyed;
  first_lease = my_list_adapter_lease_create(NULL, &first->base, NULL,
                                             leased_list_destroy);
  second_lease = my_list_adapter_lease_create(NULL, &second->base, NULL,
                                              leased_list_destroy);
  ASSERT_NOT_NULL(first_lease);
  ASSERT_NOT_NULL(second_lease);
  ASSERT_EQ(my_widget_set_rect(list, &(my_rect_t){0, 0, 100, 50}), MY_RET_OK);
  ASSERT_EQ(my_list_view_set_adapter_lease(list, first_lease), MY_RET_OK);
  my_list_adapter_lease_unref(first_lease);
  ASSERT_EQ(first_destroyed, 0);
  ASSERT_EQ(my_list_view_set_adapter(list, &invalid), MY_RET_INVALID_PARAMS);
  invalid_lease = my_list_adapter_lease_create(NULL, &invalid, NULL, NULL);
  ASSERT_NOT_NULL(invalid_lease);
  ASSERT_EQ(my_list_view_set_adapter_lease(list, invalid_lease),
            MY_RET_INVALID_PARAMS);
  my_list_adapter_lease_unref(invalid_lease);
  ASSERT_EQ(first_destroyed, 0);
  ASSERT_EQ(my_list_view_set_adapter_lease(list, second_lease), MY_RET_OK);
  ASSERT_EQ(first_destroyed, 1);
  my_list_adapter_lease_unref(second_lease);
  ASSERT_EQ(second_destroyed, 0);
  my_widget_unref(list);
  ASSERT_EQ(second_destroyed, 1);
}

TEST(node_view_rejects_foreign_nodes_and_invalid_sockets)
{
  my_widget_t* first = my_node_view_create(NULL);
  my_widget_t* second = my_node_view_create(NULL);
  my_widget_t* out_node;
  my_widget_t* in_node;

  ASSERT_NOT_NULL(first);
  ASSERT_NOT_NULL(second);
  out_node = my_node_view_add_node(first, "out", "Out", NULL, 0, 0, 80, 60);
  in_node = my_node_view_add_node(second, "in", "In", NULL, 100, 0, 80, 60);
  ASSERT_NOT_NULL(out_node);
  ASSERT_NOT_NULL(in_node);
  ASSERT_EQ(my_node_add_socket(out_node, MY_SOCKET_OUT, "value", 0),
            MY_RET_OK);
  ASSERT_EQ(my_node_add_socket(in_node, MY_SOCKET_IN, "value", 0),
            MY_RET_OK);
  ASSERT_EQ(my_node_view_connect(first, out_node, 0, in_node, 0),
            MY_RET_INVALID_PARAMS);
  ASSERT_EQ(my_node_view_connect(first, out_node, 1, out_node, 0),
            MY_RET_INVALID_PARAMS);
  ASSERT_EQ(my_node_view_connect(first, out_node, 0, out_node, 0),
            MY_RET_INVALID_PARAMS);
  ASSERT_EQ(my_node_view_disconnect_in(first, in_node, 0),
            MY_RET_INVALID_PARAMS);
  ASSERT_EQ(my_node_add_socket(out_node, (my_socket_dir_t)99, "bad", 0),
            MY_RET_INVALID_PARAMS);

  my_widget_unref(first);
  my_widget_unref(second);
}

TEST(button_cooldown_zero_disables_without_timer)
{
  my_widget_t *button = my_button_create(NULL, "send");

  ASSERT_EQ(my_button_set_cooldown(NULL, 250), MY_RET_INVALID_PARAMS);
  ASSERT_FALSE(my_button_is_cooling_down(NULL));
  ASSERT_EQ(my_button_cooldown_remaining_ms(NULL), 0u);
  ASSERT_FLOAT_EQ(my_button_cooldown_progress(NULL), 0.0f, 0.0001f);
  ASSERT_NOT_NULL(button);
  ASSERT_EQ(my_button_set_cooldown(button, 0), MY_RET_OK);
  ASSERT_FALSE(my_button_is_cooling_down(button));
  ASSERT_EQ(my_button_cooldown_remaining_ms(button), 0u);
  ASSERT_FLOAT_EQ(my_button_cooldown_progress(button), 0.0f, 0.0001f);
  ASSERT_EQ(my_button_set_cooldown(button, 250), MY_RET_OK);
  ASSERT_EQ(my_button_set_cooldown(button, 0), MY_RET_OK);
  ASSERT_FALSE(my_button_is_cooling_down(button));
  my_widget_unref(button);
}

TEST(button_keyboard_activation_is_single_shot_and_cooldown_safe)
{
  my_pal_t* pal = my_pal_dummy_create(NULL);
  my_pal_main_loop_t* loop = my_pal_main_loop_create(pal);
  my_window_manager_t* wm = my_window_manager_create(NULL, pal, loop);
  my_window_t* win = my_window_create(NULL, pal, 160, 100, "keyboard-button");
  my_widget_t* button = my_button_create(NULL, "send");
  my_widget_t* attached;
  my_event_t event;
  int clicks = 0;

  ASSERT_NOT_NULL(pal);
  ASSERT_NOT_NULL(loop);
  ASSERT_NOT_NULL(wm);
  ASSERT_NOT_NULL(win);
  ASSERT_NOT_NULL(button);
  ASSERT_EQ(my_button_set_cooldown(button, 100u), MY_RET_OK);
  ASSERT_EQ(my_widget_set_rect(button, &(my_rect_t){10, 10, 80, 32}),
            MY_RET_OK);
  ASSERT_NEQ(my_widget_on(button, "click", count_click, &clicks), 0u);
  ASSERT_EQ(my_widget_add_child(my_window_widget(win), button), MY_RET_OK);
  my_widget_unref(button);
  ASSERT_EQ(my_window_manager_open(wm, win), MY_RET_OK);
  my_widget_unref((my_widget_t*)win);
  attached = my_widget_get_child(my_window_widget(win), 0);
  my_event_dispatcher_set_focus(&win->dispatcher, attached);

  my_pal_dummy_set_now_ms(pal, 1000u);
  event = my_event_init(MY_EVENT_KEY_DOWN);
  event.u.key.key = MY_KEY_RETURN;
  ASSERT_EQ(my_window_manager_dispatch_surface_event(wm, &event), MY_RET_OK);
  ASSERT_EQ(clicks, 0);
  ASSERT_TRUE(((my_button_t*)attached)->pressed);
  ASSERT_EQ(my_window_manager_dispatch_surface_event(wm, &event), MY_RET_OK);
  ASSERT_EQ(clicks, 0);

  event.type = MY_EVENT_KEY_UP;
  ASSERT_EQ(my_window_manager_dispatch_surface_event(wm, &event), MY_RET_OK);
  ASSERT_EQ(clicks, 1);
  ASSERT_TRUE(my_button_is_cooling_down(attached));
  ASSERT_FALSE(((my_button_t*)attached)->pressed);

  event.type = MY_EVENT_KEY_DOWN;
  event.u.key.key = ' ';
  ASSERT_EQ(my_window_manager_dispatch_surface_event(wm, &event), MY_RET_OK);
  event.type = MY_EVENT_KEY_UP;
  ASSERT_EQ(my_window_manager_dispatch_surface_event(wm, &event), MY_RET_OK);
  ASSERT_EQ(clicks, 1);

  my_pal_dummy_set_now_ms(pal, 1100u);
  event.type = MY_EVENT_KEY_DOWN;
  ASSERT_EQ(my_window_manager_dispatch_surface_event(wm, &event), MY_RET_OK);
  event.type = MY_EVENT_KEY_UP;
  ASSERT_EQ(my_window_manager_dispatch_surface_event(wm, &event), MY_RET_OK);
  ASSERT_EQ(clicks, 2);

  my_pal_dummy_set_now_ms(pal, 1200u);
  event = my_event_init(MY_EVENT_POINTER_DOWN);
  event.u.pointer.x = 20;
  event.u.pointer.y = 20;
  event.u.pointer.button = 1;
  ASSERT_EQ(my_window_manager_dispatch_surface_event(wm, &event), MY_RET_OK);
  event.type = MY_EVENT_POINTER_UP;
  ASSERT_EQ(my_window_manager_dispatch_surface_event(wm, &event), MY_RET_OK);
  ASSERT_EQ(clicks, 3);

  my_pal_dummy_set_now_ms(pal, 1300u);
  event = my_event_init(MY_EVENT_KEY_DOWN);
  event.u.key.key = MY_KEY_RETURN;
  ASSERT_EQ(my_window_manager_dispatch_surface_event(wm, &event), MY_RET_OK);
  event.type = MY_EVENT_KEY_UP;
  ASSERT_EQ(my_window_manager_dispatch_surface_event(wm, &event), MY_RET_OK);
  ASSERT_EQ(clicks, 4);

  my_window_manager_destroy(wm);
  my_pal_main_loop_destroy(loop);
  my_pal_destroy(pal);
}

TEST(button_keyboard_activation_clears_on_focus_loss)
{
  my_pal_t* pal = my_pal_dummy_create(NULL);
  my_pal_main_loop_t* loop = my_pal_main_loop_create(pal);
  my_window_manager_t* wm = my_window_manager_create(NULL, pal, loop);
  my_window_t* win = my_window_create(NULL, pal, 200, 100, "keyboard-focus");
  my_widget_t* first = my_button_create(NULL, "first");
  my_widget_t* second = my_button_create(NULL, "second");
  my_button_t* first_state;
  my_button_t* second_state;
  my_event_t event;
  int clicks = 0;

  ASSERT_NOT_NULL(pal);
  ASSERT_NOT_NULL(loop);
  ASSERT_NOT_NULL(wm);
  ASSERT_NOT_NULL(win);
  ASSERT_NOT_NULL(first);
  ASSERT_NOT_NULL(second);
  ASSERT_EQ(my_widget_set_rect(first, &(my_rect_t){10, 10, 80, 32}),
            MY_RET_OK);
  ASSERT_EQ(my_widget_set_rect(second, &(my_rect_t){100, 10, 80, 32}),
            MY_RET_OK);
  ASSERT_NEQ(my_widget_on(first, "click", count_click, &clicks), 0u);
  ASSERT_NEQ(my_widget_on(second, "click", count_click, &clicks), 0u);
  ASSERT_EQ(my_widget_add_child(my_window_widget(win), first), MY_RET_OK);
  ASSERT_EQ(my_widget_add_child(my_window_widget(win), second), MY_RET_OK);
  my_widget_unref(first);
  my_widget_unref(second);
  ASSERT_EQ(my_window_manager_open(wm, win), MY_RET_OK);
  my_widget_unref((my_widget_t*)win);
  first_state = (my_button_t*)my_widget_get_child(my_window_widget(win), 0);
  second_state = (my_button_t*)my_widget_get_child(my_window_widget(win), 1);

  my_event_dispatcher_set_focus(&win->dispatcher, (my_widget_t*)first_state);
  event = my_event_init(MY_EVENT_KEY_DOWN);
  event.u.key.key = MY_KEY_RETURN;
  ASSERT_EQ(my_window_manager_dispatch_surface_event(wm, &event), MY_RET_OK);
  ASSERT_TRUE(first_state->pressed);

  my_event_dispatcher_set_focus(&win->dispatcher, (my_widget_t*)second_state);
  ASSERT_FALSE(first_state->pressed);
  ASSERT_FALSE(first_state->keyboard_pressed);
  event.type = MY_EVENT_KEY_UP;
  ASSERT_EQ(my_window_manager_dispatch_surface_event(wm, &event), MY_RET_OK);
  ASSERT_EQ(clicks, 0);

  event.type = MY_EVENT_KEY_DOWN;
  ASSERT_EQ(my_window_manager_dispatch_surface_event(wm, &event), MY_RET_OK);
  event.type = MY_EVENT_KEY_UP;
  ASSERT_EQ(my_window_manager_dispatch_surface_event(wm, &event), MY_RET_OK);
  ASSERT_EQ(clicks, 1);

  my_window_manager_destroy(wm);
  my_pal_main_loop_destroy(loop);
  my_pal_destroy(pal);
}

TEST(button_api_rejects_non_button_widgets)
{
  my_widget_t* label = my_label_create(NULL, "not a button");
  my_label_t* state;

  ASSERT_NOT_NULL(label);
  state = (my_label_t*)label;
  label->widget_type = "button";
  ASSERT_EQ(my_button_set_text(label, "still not a button"),
            MY_RET_INVALID_PARAMS);
  ASSERT_EQ(my_button_set_cooldown(label, 250u), MY_RET_INVALID_PARAMS);
  ASSERT_FALSE(my_button_is_cooling_down(label));
  ASSERT_EQ(my_button_cooldown_remaining_ms(label), 0u);
  ASSERT_FLOAT_EQ(my_button_cooldown_progress(label), 0.0f, 0.0001f);
  ASSERT_STR_EQ(state->text, "not a button");
  my_widget_unref(label);
}

TEST(button_cooldown_timer_tracks_deadline_and_stops)
{
  my_pal_t *pal = my_pal_dummy_create(NULL);
  my_pal_main_loop_t *loop = my_pal_main_loop_create(pal);
  my_window_manager_t *wm = my_window_manager_create(NULL, pal, loop);
  my_window_t *win = my_window_create(NULL, pal, 160, 100, "cooldown-timer");
  my_widget_t *button = my_button_create(NULL, "send");
  my_button_t *state;

  ASSERT_NOT_NULL(pal);
  ASSERT_NOT_NULL(loop);
  ASSERT_NOT_NULL(wm);
  ASSERT_NOT_NULL(win);
  ASSERT_NOT_NULL(button);
  ASSERT_EQ(my_button_set_cooldown(button, 100), MY_RET_OK);
  ASSERT_EQ(my_widget_set_rect(button, &(my_rect_t){10, 10, 80, 32}), MY_RET_OK);
  ASSERT_EQ(my_widget_add_child(my_window_widget(win), button), MY_RET_OK);
  my_widget_unref(button);
  ASSERT_EQ(my_window_manager_open(wm, win), MY_RET_OK);
  my_widget_unref((my_widget_t *)win);
  state = (my_button_t *)my_widget_get_child(my_window_widget(win), 0);

  my_pal_dummy_set_now_ms(pal, 1000);
  dispatch_button_click(wm, 20, 20);
  ASSERT_TRUE(state->cooldown_timer != 0);
  ASSERT_TRUE(state->cooldown_loop == loop);

  my_pal_dummy_set_now_ms(pal, 1016);
  ASSERT_EQ(my_pal_main_loop_run(loop), MY_RET_OK);
  ASSERT_TRUE(state->cooldown_timer != 0);
  ASSERT_TRUE(my_button_is_cooling_down((my_widget_t *)state));

  my_pal_dummy_set_now_ms(pal, 1100);
  ASSERT_EQ(my_pal_main_loop_run(loop), MY_RET_OK);
  ASSERT_EQ(state->cooldown_timer, 0u);
  ASSERT_TRUE(state->cooldown_loop == NULL);
  ASSERT_FALSE(my_button_is_cooling_down((my_widget_t *)state));

  my_window_manager_destroy(wm);
  my_pal_main_loop_destroy(loop);
  my_pal_destroy(pal);
}

TEST(button_cooldown_respects_reduced_motion_uses_completion_timer)
{
  my_pal_t *pal = my_pal_dummy_create(NULL);
  my_pal_main_loop_t *loop = my_pal_main_loop_create(pal);
  my_window_manager_t *wm = my_window_manager_create(NULL, pal, loop);
  my_window_t *win = my_window_create(NULL, pal, 160, 100, "reduced-motion");
  my_widget_t *button = my_button_create(NULL, "send");
  my_pal_media_context_ex_t media = {
      {true, false, true, MY_PAL_MEDIA_CAP_COLOR_SRGB},
      MY_PAL_MEDIA_KNOWN_REDUCED_MOTION};
  my_button_t *state;

  ASSERT_NOT_NULL(pal);
  ASSERT_NOT_NULL(loop);
  ASSERT_NOT_NULL(wm);
  ASSERT_NOT_NULL(win);
  ASSERT_NOT_NULL(button);
  my_pal_dummy_set_media_context_ex(pal, &media);
  ASSERT_EQ(my_button_set_cooldown(button, 1000u), MY_RET_OK);
  ASSERT_EQ(my_widget_set_rect(button, &(my_rect_t){10, 10, 80, 32}), MY_RET_OK);
  ASSERT_EQ(my_widget_add_child(my_window_widget(win), button), MY_RET_OK);
  my_widget_unref(button);
  ASSERT_EQ(my_window_manager_open(wm, win), MY_RET_OK);
  my_widget_unref((my_widget_t *)win);
  state = (my_button_t *)my_widget_get_child(my_window_widget(win), 0);

  my_pal_dummy_set_now_ms(pal, 1000u);
  dispatch_button_click(wm, 20, 20);
  ASSERT_TRUE(my_button_is_cooling_down((my_widget_t *)state));
  ASSERT_TRUE(state->cooldown_timer != 0u);
  ASSERT_EQ(my_button_cooldown_remaining_ms((my_widget_t *)state), 1000u);

  my_pal_dummy_set_now_ms(pal, 1016u);
  ASSERT_EQ(my_pal_main_loop_run(loop), MY_RET_OK);
  ASSERT_TRUE(state->cooldown_timer != 0u);
  ASSERT_TRUE(my_button_is_cooling_down((my_widget_t *)state));

  my_pal_dummy_set_now_ms(pal, 2000u);
  ASSERT_EQ(my_pal_main_loop_run(loop), MY_RET_OK);
  ASSERT_EQ(state->cooldown_timer, 0u);
  ASSERT_FALSE(my_button_is_cooling_down((my_widget_t *)state));

  my_window_manager_destroy(wm);
  my_pal_main_loop_destroy(loop);
  my_pal_destroy(pal);
}

TEST(button_cooldown_remaining_samples_clock_once)
{
  my_pal_t* pal = my_pal_dummy_create(NULL);
  my_pal_main_loop_t* loop = my_pal_main_loop_create(pal);
  my_window_manager_t* wm = my_window_manager_create(NULL, pal, loop);
  my_window_t* win = my_window_create(NULL, pal, 160, 100, "cooldown-clock");
  my_widget_t* button = my_button_create(NULL, "send");

  ASSERT_NOT_NULL(pal);
  ASSERT_NOT_NULL(loop);
  ASSERT_NOT_NULL(wm);
  ASSERT_NOT_NULL(win);
  ASSERT_NOT_NULL(button);
  ASSERT_EQ(my_button_set_cooldown(button, 1000u), MY_RET_OK);
  ASSERT_EQ(my_widget_set_rect(button, &(my_rect_t){10, 10, 80, 32}), MY_RET_OK);
  ASSERT_EQ(my_widget_add_child(my_window_widget(win), button), MY_RET_OK);
  my_widget_unref(button);
  ASSERT_EQ(my_window_manager_open(wm, win), MY_RET_OK);
  my_widget_unref((my_widget_t*)win);

  my_pal_dummy_set_now_ms(pal, 1000u);
  dispatch_button_click(wm, 20, 20);
  my_pal_dummy_set_now_ms(pal, 1999u);
  my_pal_dummy_set_time_step_ms(pal, 2u);
  ASSERT_EQ(my_button_cooldown_remaining_ms(
                my_widget_get_child(my_window_widget(win), 0)),
            1u);
  my_pal_dummy_set_now_ms(pal, 1999u);
  ASSERT_FLOAT_EQ(my_button_cooldown_progress(
                      my_widget_get_child(my_window_widget(win), 0)),
                  0.001f, 0.0001f);

  my_window_manager_destroy(wm);
  my_pal_main_loop_destroy(loop);
  my_pal_destroy(pal);
}

TEST(button_cooldown_paint_samples_clock_once)
{
  my_pal_t* pal = my_pal_dummy_create(NULL);
  my_pal_main_loop_t* loop = my_pal_main_loop_create(pal);
  my_window_manager_t* wm = my_window_manager_create(NULL, pal, loop);
  my_window_t* win = my_window_create(NULL, pal, 160, 100, "cooldown-paint");
  my_widget_t* button = my_button_create(NULL, "send");
  my_lcd_t* lcd = my_lcd_mem_create(NULL, 160, 100, MY_PIXEL_FORMAT_BGRA8888);
  my_vgcanvas_t* canvas = my_vgcanvas_soft_create(NULL, lcd);
  my_widget_t* attached;

  ASSERT_NOT_NULL(pal);
  ASSERT_NOT_NULL(loop);
  ASSERT_NOT_NULL(wm);
  ASSERT_NOT_NULL(win);
  ASSERT_NOT_NULL(button);
  ASSERT_NOT_NULL(lcd);
  ASSERT_NOT_NULL(canvas);
  ASSERT_EQ(my_button_set_cooldown(button, 1000u), MY_RET_OK);
  ASSERT_EQ(my_widget_set_rect(button, &(my_rect_t){10, 10, 80, 32}), MY_RET_OK);
  ASSERT_EQ(my_widget_add_child(my_window_widget(win), button), MY_RET_OK);
  my_widget_unref(button);
  ASSERT_EQ(my_window_manager_open(wm, win), MY_RET_OK);
  my_widget_unref((my_widget_t*)win);
  attached = my_widget_get_child(my_window_widget(win), 0);
  my_pal_dummy_set_now_ms(pal, 1000u);
  dispatch_button_click(wm, 20, 20);
  my_pal_dummy_reset_time_query_count(pal);
  ASSERT_EQ(my_vgcanvas_begin_frame(canvas, NULL), MY_RET_OK);
  attached->vtable->on_paint(attached, canvas);
  ASSERT_EQ(my_vgcanvas_end_frame(canvas), MY_RET_OK);
  ASSERT_EQ(my_pal_dummy_time_query_count(pal), 1u);

  my_window_manager_destroy(wm);
  my_pal_main_loop_destroy(loop);
  my_vgcanvas_destroy(canvas);
  my_lcd_destroy(lcd);
  my_pal_destroy(pal);
}

TEST(button_release_preserves_minimum_press_after_clock_rollback)
{
  my_pal_t* pal = my_pal_dummy_create(NULL);
  my_pal_main_loop_t* loop = my_pal_main_loop_create(pal);
  my_window_manager_t* wm = my_window_manager_create(NULL, pal, loop);
  my_window_t* win = my_window_create(NULL, pal, 160, 100, "clock-rollback");
  my_widget_t* button = my_button_create(NULL, "send");
  my_button_t* state;
  my_event_t event = my_event_init(MY_EVENT_POINTER_DOWN);

  ASSERT_NOT_NULL(pal);
  ASSERT_NOT_NULL(loop);
  ASSERT_NOT_NULL(wm);
  ASSERT_NOT_NULL(win);
  ASSERT_NOT_NULL(button);
  ASSERT_EQ(my_widget_set_rect(button, &(my_rect_t){10, 10, 80, 32}),
            MY_RET_OK);
  ASSERT_EQ(my_widget_add_child(my_window_widget(win), button), MY_RET_OK);
  my_widget_unref(button);
  ASSERT_EQ(my_window_manager_open(wm, win), MY_RET_OK);
  my_widget_unref((my_widget_t*)win);
  state = (my_button_t*)my_widget_get_child(my_window_widget(win), 0);

  my_pal_dummy_set_now_ms(pal, 1000u);
  event.u.pointer.x = 20;
  event.u.pointer.y = 20;
  event.u.pointer.button = 1;
  ASSERT_EQ(my_window_manager_dispatch_surface_event(wm, &event), MY_RET_OK);

  my_pal_dummy_set_now_ms(pal, 900u);
  event.type = MY_EVENT_POINTER_UP;
  ASSERT_EQ(my_window_manager_dispatch_surface_event(wm, &event), MY_RET_OK);
  ASSERT_TRUE(state->pressed);
  ASSERT_TRUE(state->release_timer != 0u);

  my_pal_dummy_set_now_ms(pal, 1019u);
  ASSERT_EQ(my_pal_main_loop_run(loop), MY_RET_OK);
  ASSERT_TRUE(state->pressed);
  my_pal_dummy_set_now_ms(pal, 1020u);
  ASSERT_EQ(my_pal_main_loop_run(loop), MY_RET_OK);
  ASSERT_FALSE(state->pressed);
  ASSERT_EQ(state->release_timer, 0u);

  my_window_manager_destroy(wm);
  my_pal_main_loop_destroy(loop);
  my_pal_destroy(pal);
}

TEST(button_cooldown_remains_active_at_clock_upper_bound)
{
  my_pal_t* pal = my_pal_dummy_create(NULL);
  my_pal_main_loop_t* loop = my_pal_main_loop_create(pal);
  my_window_manager_t* wm = my_window_manager_create(NULL, pal, loop);
  my_window_t* win = my_window_create(NULL, pal, 160, 100, "clock-limit");
  my_widget_t* button = my_button_create(NULL, "send");
  my_button_t* state;

  ASSERT_NOT_NULL(pal);
  ASSERT_NOT_NULL(loop);
  ASSERT_NOT_NULL(wm);
  ASSERT_NOT_NULL(win);
  ASSERT_NOT_NULL(button);
  ASSERT_EQ(my_button_set_cooldown(button, 100u), MY_RET_OK);
  ASSERT_EQ(my_widget_set_rect(button, &(my_rect_t){10, 10, 80, 32}),
            MY_RET_OK);
  ASSERT_EQ(my_widget_add_child(my_window_widget(win), button), MY_RET_OK);
  my_widget_unref(button);
  ASSERT_EQ(my_window_manager_open(wm, win), MY_RET_OK);
  my_widget_unref((my_widget_t*)win);
  state = (my_button_t*)my_widget_get_child(my_window_widget(win), 0);

  my_pal_dummy_set_now_ms(pal, UINT64_MAX);
  dispatch_button_click(wm, 20, 20);
  ASSERT_TRUE(my_button_is_cooling_down((my_widget_t*)state));
  ASSERT_EQ(my_button_cooldown_remaining_ms((my_widget_t*)state), 100u);
  ASSERT_FLOAT_EQ(my_button_cooldown_progress((my_widget_t*)state), 1.0f,
                  0.0001f);
  ASSERT_EQ(state->cooldown_timer, 0u);

  my_window_manager_destroy(wm);
  my_pal_main_loop_destroy(loop);
  my_pal_destroy(pal);
}

TEST(button_release_timer_failure_does_not_stick_pressed_state)
{
  text_area_fail_alloc_t allocation = {false};
  my_allocator_t allocator = {&allocation, text_area_fail_alloc,
                              text_area_fail_calloc, text_area_fail_realloc,
                              text_area_fail_free};
  my_pal_t *pal = my_pal_dummy_create(&allocator);
  my_pal_main_loop_t *loop = my_pal_main_loop_create(pal);
  my_window_manager_t *wm = my_window_manager_create(NULL, pal, loop);
  my_window_t *win = my_window_create(NULL, pal, 160, 100, "cooldown-oom");
  my_widget_t *button = my_button_create(NULL, "send");
  my_button_t *state;

  ASSERT_NOT_NULL(pal);
  ASSERT_NOT_NULL(loop);
  ASSERT_NOT_NULL(wm);
  ASSERT_NOT_NULL(win);
  ASSERT_NOT_NULL(button);
  ASSERT_EQ(my_button_set_cooldown(button, 500), MY_RET_OK);
  ASSERT_EQ(my_widget_set_rect(button, &(my_rect_t){10, 10, 80, 32}), MY_RET_OK);
  ASSERT_EQ(my_widget_add_child(my_window_widget(win), button), MY_RET_OK);
  my_widget_unref(button);
  ASSERT_EQ(my_window_manager_open(wm, win), MY_RET_OK);
  my_widget_unref((my_widget_t *)win);
  state = (my_button_t *)my_widget_get_child(my_window_widget(win), 0);

  my_pal_dummy_set_now_ms(pal, 1000);
  {
    my_event_t event = my_event_init(MY_EVENT_POINTER_DOWN);
    event.u.pointer.x = 20;
    event.u.pointer.y = 20;
    ASSERT_EQ(my_window_manager_dispatch_surface_event(wm, &event), MY_RET_OK);
  }
  allocation.fail = true;
  my_pal_dummy_set_now_ms(pal, 1000);
  {
    my_event_t event = my_event_init(MY_EVENT_POINTER_UP);
    event.u.pointer.x = 20;
    event.u.pointer.y = 20;
    ASSERT_EQ(my_window_manager_dispatch_surface_event(wm, &event), MY_RET_OK);
  }
  ASSERT_FALSE(state->pressed);
  ASSERT_TRUE(my_button_is_cooling_down((my_widget_t *)state));
  ASSERT_EQ(state->cooldown_timer, 0u);
  allocation.fail = false;

  my_window_manager_destroy(wm);
  my_pal_main_loop_destroy(loop);
  my_pal_destroy(pal);
}

TEST(surface_resize_preserves_and_recenters_dialog)
{
  my_pal_t *pal = my_pal_dummy_create(NULL);
  my_pal_main_loop_t *loop = my_pal_main_loop_create(pal);
  my_window_manager_t *wm = my_window_manager_create(NULL, pal, loop);
  my_window_t *main_win = my_window_create(NULL, pal, 400, 300, "main");
  my_dialog_t *dlg;

  ASSERT_EQ(my_window_manager_open(wm, main_win), MY_RET_OK);
  my_widget_unref((my_widget_t *)main_win);
  dlg = my_dialog_create(NULL, pal, "confirm", 200, 120);
  ASSERT_EQ(my_dialog_open(dlg, wm, NULL, NULL), MY_RET_OK);

  ASSERT_EQ(my_window_manager_resize_surface(wm, 800, 600), MY_RET_OK);
  ASSERT_EQ(((my_widget_t*)main_win)->rect.w, 800);
  ASSERT_EQ(((my_widget_t*)main_win)->rect.h, 600);
  ASSERT_EQ(((my_widget_t*)dlg->win)->rect.w, 200);
  ASSERT_EQ(((my_widget_t*)dlg->win)->rect.h, 120);
  ASSERT_EQ(((my_widget_t*)dlg->win)->rect.x, 300);
  ASSERT_EQ(((my_widget_t*)dlg->win)->rect.y, 240);

  my_dialog_close(dlg, MY_DIALOG_CANCEL);
  pump(pal, loop);
  my_dialog_destroy(dlg);
  my_window_manager_destroy(wm);
  my_pal_main_loop_destroy(loop);
  my_pal_destroy(pal);
}

TEST(back_to_home_clears_window_links_and_scrim)
{
  my_pal_t *pal = my_pal_dummy_create(NULL);
  my_pal_main_loop_t *loop = my_pal_main_loop_create(pal);
  my_window_manager_t *wm;
  my_window_t *home;
  my_window_t *page;

  my_pal_dummy_set_needs_csd(pal, true);
  wm = my_window_manager_create(NULL, pal, loop);
  home = my_window_create(NULL, pal, 400, 300, "home");
  page = my_window_create(NULL, pal, 200, 100, "page");
  ASSERT_EQ(my_window_manager_open(wm, home), MY_RET_OK);
  my_widget_unref((my_widget_t *)home);
  ASSERT_EQ(my_window_manager_open(wm, page), MY_RET_OK);
  my_widget_unref((my_widget_t *)page);
  home->scrim = true;

  ASSERT_EQ(my_window_manager_back_to_home(wm), MY_RET_OK);
  ASSERT_EQ(my_window_manager_count(wm), 1);
  ASSERT_TRUE(!home->scrim);

  my_window_manager_destroy(wm);
  my_pal_main_loop_destroy(loop);
  my_pal_destroy(pal);
}

TEST(auto_paint_toggle_removes_timer)
{
  my_pal_t *pal = my_pal_dummy_create(NULL);
  my_pal_main_loop_t *loop = my_pal_main_loop_create(pal);
  my_window_manager_t *wm = my_window_manager_create(NULL, pal, loop);

  ASSERT_TRUE(wm->paint_timer_id > 0);
  my_window_manager_set_auto_paint(wm, false);
  ASSERT_EQ(wm->paint_timer_id, 0u);
  my_window_manager_set_auto_paint(wm, true);
  ASSERT_TRUE(wm->paint_timer_id > 0);

  my_window_manager_destroy(wm);
  my_pal_main_loop_destroy(loop);
  my_pal_destroy(pal);
}

TEST(ui_command_runs_on_manager_loop_and_survives_window_close)
{
  my_pal_t* pal = my_pal_dummy_create(NULL);
  my_pal_main_loop_t* loop = my_pal_main_loop_create(pal);
  my_window_manager_t* wm = my_window_manager_create(NULL, pal, loop);
  my_window_t* win = my_window_create(NULL, pal, 200, 100, "command");
  command_lifecycle_test_t state = {wm, win, 0, 0};
  my_ui_command_t* command = my_ui_command_create(
      NULL, command_lifecycle_execute, &state, command_lifecycle_destroy);

  ASSERT_EQ(my_window_manager_open(wm, win), MY_RET_OK);
  ASSERT_EQ(my_ui_command_submit(loop, command), MY_RET_OK);
  my_ui_command_unref(command);
  my_widget_unref((my_widget_t*)win);
  ASSERT_EQ(my_pal_main_loop_pump_n(loop, 1u), 1u);
  ASSERT_EQ(state.execute_count, 1);
  ASSERT_EQ(state.destroy_count, 1);
  ASSERT_EQ(my_window_manager_count(wm), 0u);

  my_window_manager_destroy(wm);
  my_pal_main_loop_destroy(loop);
  my_pal_destroy(pal);
}

TEST(ui_command_destroyed_with_manager_does_not_execute)
{
  my_pal_t* pal = my_pal_dummy_create(NULL);
  my_pal_main_loop_t* loop = my_pal_main_loop_create(pal);
  my_window_manager_t* wm = my_window_manager_create(NULL, pal, loop);
  command_lifecycle_test_t state = {wm, NULL, 0, 0};
  my_ui_command_t* command = my_ui_command_create(
      NULL, command_lifecycle_execute, &state, command_lifecycle_destroy);

  ASSERT_EQ(my_ui_command_submit(loop, command), MY_RET_OK);
  my_ui_command_unref(command);
  my_window_manager_destroy(wm);
  ASSERT_EQ(state.execute_count, 0);
  ASSERT_EQ(state.destroy_count, 0);
  my_pal_main_loop_destroy(loop);
  ASSERT_EQ(state.execute_count, 0);
  ASSERT_EQ(state.destroy_count, 1);
  my_pal_destroy(pal);
}

TEST(ui_command_does_not_require_an_open_window)
{
  my_pal_t* pal = my_pal_dummy_create(NULL);
  my_pal_main_loop_t* loop = my_pal_main_loop_create(pal);
  my_window_manager_t* wm = my_window_manager_create(NULL, pal, loop);
  command_lifecycle_test_t state = {wm, NULL, 0, 0};
  my_ui_command_t* command = my_ui_command_create(
      NULL, command_lifecycle_execute, &state, command_lifecycle_destroy);

  ASSERT_EQ(my_ui_command_submit(loop, command), MY_RET_OK);
  my_ui_command_unref(command);
  ASSERT_EQ(my_pal_main_loop_pump_n(loop, 1u), 1u);
  ASSERT_EQ(state.execute_count, 1);
  ASSERT_EQ(state.destroy_count, 1);

  my_window_manager_destroy(wm);
  my_pal_main_loop_destroy(loop);
  my_pal_destroy(pal);
}

TEST(ui_command_scope_closes_with_window)
{
  my_pal_t* pal = my_pal_dummy_create(NULL);
  my_pal_main_loop_t* loop = my_pal_main_loop_create(pal);
  my_window_manager_t* wm = my_window_manager_create(NULL, pal, loop);
  my_window_t* win = my_window_create(NULL, pal, 200, 100, "scope");
  command_lifecycle_test_t state = {wm, win, 0, 0};
  my_ui_command_t* command = my_ui_command_create(
      NULL, command_lifecycle_execute, &state, command_lifecycle_destroy);
  struct my_ui_command_scope_t* scope = my_window_command_scope_ref(win);

  ASSERT_EQ(my_window_manager_open(wm, win), MY_RET_OK);
  ASSERT_EQ(my_ui_command_submit_scoped(loop, scope, command), MY_RET_OK);
  ASSERT_EQ(my_window_manager_close(wm, win), MY_RET_OK);
  ASSERT_TRUE(my_ui_command_scope_is_closed(scope));
  my_ui_command_unref(command);
  ASSERT_EQ(my_pal_main_loop_pump_n(loop, 1u), 1u);
  ASSERT_EQ(state.execute_count, 0);
  ASSERT_EQ(state.destroy_count, 1);
  my_ui_command_scope_unref(scope);
  my_widget_unref((my_widget_t*)win);
  my_window_manager_destroy(wm);
  my_pal_main_loop_destroy(loop);
  my_pal_destroy(pal);
}

TEST(ui_command_scope_reopens_with_window)
{
  my_pal_t* pal = my_pal_dummy_create(NULL);
  my_pal_main_loop_t* loop = my_pal_main_loop_create(pal);
  my_window_manager_t* wm = my_window_manager_create(NULL, pal, loop);
  my_window_t* win = my_window_create(NULL, pal, 200, 100, "scope-reopen");
  command_lifecycle_test_t state = {wm, NULL, 0, 0};
  my_ui_command_t* command = my_ui_command_create(
      NULL, command_lifecycle_execute, &state, command_lifecycle_destroy);
  struct my_ui_command_scope_t* scope = my_window_command_scope_ref(win);

  ASSERT_EQ(my_window_manager_open(wm, win), MY_RET_OK);
  ASSERT_EQ(my_window_manager_close(wm, win), MY_RET_OK);
  ASSERT_TRUE(my_ui_command_scope_is_closed(scope));
  ASSERT_EQ(my_window_manager_open(wm, win), MY_RET_OK);
  ASSERT_FALSE(my_ui_command_scope_is_closed(scope));
  ASSERT_EQ(my_ui_command_submit_scoped(loop, scope, command), MY_RET_OK);
  my_ui_command_unref(command);
  ASSERT_EQ(my_pal_main_loop_pump_n(loop, 1u), 1u);
  ASSERT_EQ(state.execute_count, 1);
  ASSERT_EQ(state.destroy_count, 1);
  my_ui_command_scope_unref(scope);
  my_widget_unref((my_widget_t*)win);
  my_window_manager_destroy(wm);
  my_pal_main_loop_destroy(loop);
  my_pal_destroy(pal);
}

TEST(ui_command_scope_closes_with_manager)
{
  my_pal_t* pal = my_pal_dummy_create(NULL);
  my_pal_main_loop_t* loop = my_pal_main_loop_create(pal);
  my_window_manager_t* wm = my_window_manager_create(NULL, pal, loop);
  command_lifecycle_test_t state = {wm, NULL, 0, 0};
  my_ui_command_t* command = my_ui_command_create(
      NULL, command_lifecycle_execute, &state, command_lifecycle_destroy);
  struct my_ui_command_scope_t* scope =
      my_window_manager_command_scope_ref(wm);

  ASSERT_EQ(my_ui_command_submit_scoped(loop, scope, command), MY_RET_OK);
  my_window_manager_destroy(wm);
  ASSERT_TRUE(my_ui_command_scope_is_closed(scope));
  my_ui_command_scope_unref(scope);
  my_ui_command_unref(command);
  ASSERT_EQ(my_pal_main_loop_pump_n(loop, 1u), 1u);
  ASSERT_EQ(state.execute_count, 0);
  ASSERT_EQ(state.destroy_count, 1);
  my_pal_main_loop_destroy(loop);
  my_pal_destroy(pal);
}

TEST(ui_command_scope_keeps_sibling_commands_alive)
{
  my_pal_t* pal = my_pal_dummy_create(NULL);
  my_pal_main_loop_t* loop = my_pal_main_loop_create(pal);
  my_window_manager_t* wm = my_window_manager_create(NULL, pal, loop);
  command_lifecycle_test_t state = {wm, NULL, 0, 0};
  my_ui_command_t* first = my_ui_command_create(
      NULL, command_lifecycle_execute, &state, command_lifecycle_destroy);
  my_ui_command_t* second = my_ui_command_create(
      NULL, command_lifecycle_execute, &state, command_lifecycle_destroy);
  struct my_ui_command_scope_t* scope =
      my_window_manager_command_scope_ref(wm);

  ASSERT_EQ(my_ui_command_submit_scoped(loop, scope, first), MY_RET_OK);
  ASSERT_EQ(my_ui_command_submit_scoped(loop, scope, second), MY_RET_OK);
  my_ui_command_unref(first);
  my_ui_command_unref(second);
  ASSERT_EQ(my_pal_main_loop_pump_n(loop, 2u), 2u);
  ASSERT_EQ(state.execute_count, 2);
  ASSERT_EQ(state.destroy_count, 2);
  ASSERT_FALSE(my_ui_command_scope_is_closed(scope));

  my_ui_command_scope_unref(scope);
  my_window_manager_destroy(wm);
  my_pal_main_loop_destroy(loop);
  my_pal_destroy(pal);
}

TEST(posted_user_event_reaches_top_window)
{
  my_pal_t *pal = my_pal_dummy_create(NULL);
  my_pal_main_loop_t *loop = my_pal_main_loop_create(pal);
  my_window_manager_t *wm = my_window_manager_create(NULL, pal, loop);
  my_window_t *win = my_window_create(NULL, pal, 200, 100, "main");
  my_event_t event = my_event_init(MY_EVENT_USER);

  g_user_events = 0;
  event.u.user.data = &g_user_events;
  my_widget_on(my_window_widget(win), "user", count_user, &g_user_events);
  ASSERT_EQ(my_window_manager_open(wm, win), MY_RET_OK);
  my_widget_unref((my_widget_t *)win);
  ASSERT_EQ(my_pal_main_loop_post_event(loop, &event), MY_RET_OK);
  ASSERT_EQ(my_pal_main_loop_pump_n(loop, 1), 1u);
  ASSERT_EQ(g_user_events, 1);

  my_window_manager_destroy(wm);
  my_pal_main_loop_destroy(loop);
  my_pal_destroy(pal);
}

TEST(user_event_can_close_window_during_dispatch)
{
  my_pal_t *pal = my_pal_dummy_create(NULL);
  my_pal_main_loop_t *loop = my_pal_main_loop_create(pal);
  my_window_manager_t *wm = my_window_manager_create(NULL, pal, loop);
  my_window_t *win = my_window_create(NULL, pal, 200, 100, "main");
  my_event_t event = my_event_init(MY_EVENT_USER);

  ASSERT_NOT_NULL(pal);
  ASSERT_NOT_NULL(loop);
  ASSERT_NOT_NULL(wm);
  ASSERT_NOT_NULL(win);
  my_widget_on(my_window_widget(win), "user", close_window_from_user_event,
               wm);
  ASSERT_EQ(my_window_manager_open(wm, win), MY_RET_OK);
  my_widget_unref((my_widget_t *)win);
  ASSERT_EQ(my_pal_main_loop_post_event(loop, &event), MY_RET_OK);
  ASSERT_EQ(my_pal_main_loop_pump_n(loop, 1), 1u);
  ASSERT_EQ(my_window_manager_count(wm), 0u);
  ASSERT_TRUE(wm->quit_requested);

  my_window_manager_destroy(wm);
  my_pal_main_loop_destroy(loop);
  my_pal_destroy(pal);
}

TEST(text_widgets_toggle_platform_ime_with_focus)
{
  my_pal_t *pal = my_pal_dummy_create(NULL);
  my_pal_main_loop_t *loop = my_pal_main_loop_create(pal);
  my_window_manager_t *wm = my_window_manager_create(NULL, pal, loop);
  my_window_t *win = my_window_create(NULL, pal, 400, 300, "main");
  my_widget_t *edit = my_edit_create(NULL);
  my_widget_t *text_area = my_text_area_create(NULL);
  my_widget_t *button = my_button_create(NULL, "done");
  char surrounding[32];
  int32_t cursor;
  int32_t anchor;

  ASSERT_EQ(my_widget_add_child(my_window_widget(win), edit), MY_RET_OK);
  ASSERT_EQ(my_widget_add_child(my_window_widget(win), text_area), MY_RET_OK);
  ASSERT_EQ(my_widget_add_child(my_window_widget(win), button), MY_RET_OK);
  my_widget_unref(edit);
  my_widget_unref(text_area);
  my_widget_unref(button);
  ASSERT_EQ(my_window_manager_open(wm, win), MY_RET_OK);
  my_widget_unref((my_widget_t *)win);

  ASSERT_TRUE(!my_pal_dummy_get_ime_enabled(win->pal_window));
  ASSERT_EQ(my_edit_set_text(edit, "a\xE4\xB8\xAD"), MY_RET_OK);
  my_event_dispatcher_set_focus(&win->dispatcher, edit);
  ASSERT_TRUE(my_pal_dummy_get_ime_enabled(win->pal_window));
  my_pal_dummy_get_ime_surrounding(win->pal_window, surrounding,
                                   sizeof(surrounding), &cursor, &anchor);
  ASSERT_EQ(strcmp(surrounding, "a\xE4\xB8\xAD"), 0);
  ASSERT_EQ(cursor, 4);
  ASSERT_EQ(anchor, 4);
  my_event_dispatcher_set_focus(&win->dispatcher, button);
  ASSERT_TRUE(!my_pal_dummy_get_ime_enabled(win->pal_window));
  my_event_dispatcher_set_focus(&win->dispatcher, text_area);
  ASSERT_TRUE(my_pal_dummy_get_ime_enabled(win->pal_window));
  my_event_dispatcher_set_focus(&win->dispatcher, NULL);
  ASSERT_TRUE(!my_pal_dummy_get_ime_enabled(win->pal_window));

  my_window_manager_destroy(wm);
  my_pal_main_loop_destroy(loop);
  my_pal_destroy(pal);
}

TEST(text_area_variable_font_keeps_nonwrap_coordinates_consistent)
{
  text_area_variable_font_t font = {{&text_area_variable_font_vtable}, 0, 0};
  my_widget_t* area = my_text_area_create(NULL);
  my_text_area_t* text_area = (my_text_area_t*)area;
  my_event_t event = my_event_init(MY_EVENT_POINTER_DOWN);

  ASSERT_NOT_NULL(area);
  ASSERT_EQ(my_widget_set_rect(area, &(my_rect_t){0, 0, 80, 40}), MY_RET_OK);
  my_text_area_set_font(area, (my_font_t*)&font, 16);
  ASSERT_EQ(my_text_area_set_text(area, "AB"), MY_RET_OK);
  event.u.pointer.x = 7;
  event.u.pointer.y = 5;
  ASSERT_EQ(area->vtable->on_event(area, &event), MY_RET_OK);
  ASSERT_EQ(text_area->cursor_col, 1u);
  my_widget_unref(area);
}

TEST(text_area_nonwrap_hit_test_uses_shaping_clusters)
{
  my_font_t font = {&text_area_ligature_vtable};
  my_widget_t* area = my_text_area_create(NULL);
  my_text_area_t* text_area = (my_text_area_t*)area;
  my_event_t event = my_event_init(MY_EVENT_POINTER_DOWN);

  ASSERT_NOT_NULL(area);
  ASSERT_EQ(my_widget_set_rect(area, &(my_rect_t){0, 0, 80, 40}), MY_RET_OK);
  my_text_area_set_font(area, &font, 16);
  ASSERT_EQ(my_text_area_set_text(area, "fi"), MY_RET_OK);
  event.u.pointer.x = 15;
  event.u.pointer.y = 5;
  ASSERT_EQ(area->vtable->on_event(area, &event), MY_RET_OK);
  ASSERT_EQ(text_area->cursor_col, 2u);
  my_widget_unref(area);
}

TEST(text_area_pointer_hit_test_clamps_vertical_bounds)
{
  my_widget_t* area = my_text_area_create(NULL);
  my_text_area_t* text_area = (my_text_area_t*)area;
  my_event_t event = my_event_init(MY_EVENT_POINTER_DOWN);

  ASSERT_NOT_NULL(area);
  ASSERT_EQ(my_widget_set_rect(area, &(my_rect_t){0, 0, 80, 60}), MY_RET_OK);
  ASSERT_EQ(my_text_area_set_text(area, "first\nsecond\nthird"), MY_RET_OK);
  event.u.pointer.x = 5;
  event.u.pointer.y = -30;
  ASSERT_EQ(area->vtable->on_event(area, &event), MY_RET_OK);
  ASSERT_EQ(text_area->cursor_row, 0u);
  event.u.pointer.y = 100;
  ASSERT_EQ(area->vtable->on_event(area, &event), MY_RET_OK);
  ASSERT_EQ(text_area->cursor_row, 2u);
  my_widget_unref(area);
}

TEST(text_area_pointer_hit_test_uses_font_line_height)
{
  text_area_variable_font_t font = {{&text_area_variable_font_vtable}, 0, 0};
  my_widget_t* area = my_text_area_create(NULL);
  my_text_area_t* text_area = (my_text_area_t*)area;
  my_event_t event = my_event_init(MY_EVENT_POINTER_DOWN);

  ASSERT_NOT_NULL(area);
  ASSERT_EQ(my_widget_set_rect(area, &(my_rect_t){0, 0, 80, 80}), MY_RET_OK);
  my_text_area_set_font(area, (my_font_t*)&font, 16);
  ASSERT_EQ(my_text_area_set_text(area, "a\nb\nc"), MY_RET_OK);
  event.u.pointer.x = 5;
  event.u.pointer.y = 22;
  ASSERT_EQ(area->vtable->on_event(area, &event), MY_RET_OK);
  ASSERT_EQ(text_area->cursor_row, 0u);
  my_widget_unref(area);
}

TEST(text_area_page_down_moves_by_wrapped_visual_lines)
{
  my_widget_t* area = my_text_area_create(NULL);
  my_text_area_t* text_area = (my_text_area_t*)area;
  my_event_t event = my_event_init(MY_EVENT_KEY_DOWN);

  ASSERT_NOT_NULL(area);
  ASSERT_EQ(my_widget_set_rect(area, &(my_rect_t){0, 0, 28, 54}), MY_RET_OK);
  ASSERT_EQ(my_text_area_set_wrap(area, true), MY_RET_OK);
  ASSERT_EQ(my_text_area_set_text(area, "abcdefghij"), MY_RET_OK);
  ASSERT_EQ(my_text_area_visual_line_count(area), 5u);
  text_area->cursor_row = 0;
  text_area->cursor_col = 0;
  text_area->anchor_row = 0;
  text_area->anchor_col = 0;
  text_area->goal_col = 0;
  text_area->focused = true;
  event.u.key.key = MY_KEY_PAGE_DOWN;
  ASSERT_EQ(area->vtable->on_event(area, &event), MY_RET_OK);
  ASSERT_EQ(text_area->cursor_row, 0u);
  ASSERT_EQ(text_area->cursor_col, 6u);
  my_widget_unref(area);
}

TEST(text_area_page_up_moves_by_wrapped_visual_lines)
{
  my_widget_t* area = my_text_area_create(NULL);
  my_text_area_t* text_area = (my_text_area_t*)area;
  my_event_t event = my_event_init(MY_EVENT_KEY_DOWN);

  ASSERT_NOT_NULL(area);
  ASSERT_EQ(my_widget_set_rect(area, &(my_rect_t){0, 0, 28, 54}), MY_RET_OK);
  ASSERT_EQ(my_text_area_set_wrap(area, true), MY_RET_OK);
  ASSERT_EQ(my_text_area_set_text(area, "abcdef\nabcdefghij"), MY_RET_OK);
  ASSERT_EQ(my_text_area_visual_line_count(area), 8u);
  text_area->cursor_row = 1;
  text_area->cursor_col = 2;
  text_area->anchor_row = 1;
  text_area->anchor_col = 2;
  text_area->goal_col = 0;
  text_area->focused = true;
  event.u.key.key = MY_KEY_PAGE_UP;
  ASSERT_EQ(area->vtable->on_event(area, &event), MY_RET_OK);
  ASSERT_EQ(text_area->cursor_row, 0u);
  ASSERT_EQ(text_area->cursor_col, 2u);
  my_widget_unref(area);
}

TEST(text_area_paint_reuses_line_buffer)
{
  text_area_count_alloc_t state = {0};
  my_allocator_t allocator = {&state, text_area_count_alloc,
                              text_area_count_calloc, text_area_count_realloc,
                              text_area_count_free};
  my_widget_t* area = my_text_area_create(&allocator);
  my_text_area_t* text_area = (my_text_area_t*)area;
  my_lcd_t* lcd = my_lcd_mem_create(NULL, 160, 80, MY_PIXEL_FORMAT_BGRA8888);
  my_vgcanvas_t* canvas = my_vgcanvas_soft_create(NULL, lcd);
  size_t before;

  ASSERT_NOT_NULL(area);
  ASSERT_NOT_NULL(lcd);
  ASSERT_NOT_NULL(canvas);
  ASSERT_EQ(my_widget_set_rect(area, &(my_rect_t){0, 0, 28, 54}), MY_RET_OK);
  ASSERT_EQ(my_text_area_set_wrap(area, true), MY_RET_OK);
  ASSERT_EQ(my_text_area_set_text(area, "abcdefghij"), MY_RET_OK);
  text_area->focused = true;
  text_area->cursor_visible = true;
  ASSERT_EQ(my_vgcanvas_begin_frame(canvas, NULL), MY_RET_OK);
  area->vtable->on_paint(area, canvas);
  ASSERT_EQ(my_vgcanvas_end_frame(canvas), MY_RET_OK);
  before = state.alloc_calls;
  ASSERT_EQ(my_vgcanvas_begin_frame(canvas, NULL), MY_RET_OK);
  area->vtable->on_paint(area, canvas);
  ASSERT_EQ(my_vgcanvas_end_frame(canvas), MY_RET_OK);
  ASSERT_EQ(state.alloc_calls, before);
  my_vgcanvas_destroy(canvas);
  my_lcd_destroy(lcd);
  my_widget_unref(area);
}

TEST(text_area_justify_paint_reuses_line_buffer)
{
  text_area_count_alloc_t state = {0};
  my_allocator_t allocator = {&state, text_area_count_alloc,
                              text_area_count_calloc, text_area_count_realloc,
                              text_area_count_free};
  my_widget_t* area = my_text_area_create(&allocator);
  my_lcd_t* lcd = my_lcd_mem_create(NULL, 160, 80, MY_PIXEL_FORMAT_BGRA8888);
  my_vgcanvas_t* canvas = my_vgcanvas_soft_create(NULL, lcd);
  size_t before;

  ASSERT_NOT_NULL(area);
  ASSERT_NOT_NULL(lcd);
  ASSERT_NOT_NULL(canvas);
  ASSERT_EQ(my_widget_set_rect(area, &(my_rect_t){0, 0, 54, 80}), MY_RET_OK);
  ASSERT_EQ(my_text_area_set_wrap(area, true), MY_RET_OK);
  ASSERT_EQ(my_text_area_set_align(area, MY_TEXT_ALIGN_JUSTIFY), MY_RET_OK);
  ASSERT_EQ(my_text_area_set_text(area, "aa bb cc dd"), MY_RET_OK);
  ASSERT_EQ(my_vgcanvas_begin_frame(canvas, NULL), MY_RET_OK);
  area->vtable->on_paint(area, canvas);
  ASSERT_EQ(my_vgcanvas_end_frame(canvas), MY_RET_OK);
  before = state.alloc_calls;
  ASSERT_EQ(my_vgcanvas_begin_frame(canvas, NULL), MY_RET_OK);
  area->vtable->on_paint(area, canvas);
  ASSERT_EQ(my_vgcanvas_end_frame(canvas), MY_RET_OK);
  ASSERT_EQ(state.alloc_calls, before);
  my_vgcanvas_destroy(canvas);
  my_lcd_destroy(lcd);
  my_widget_unref(area);
}

TEST(text_area_ime_spot_tracks_wrapped_justify_cursor)
{
  my_pal_t* pal = my_pal_dummy_create(NULL);
  my_pal_main_loop_t* loop = my_pal_main_loop_create(pal);
  my_window_manager_t* wm = my_window_manager_create(NULL, pal, loop);
  my_window_t* win = my_window_create(NULL, pal, 200, 100, "main");
  my_widget_t* area = my_text_area_create(NULL);
  my_text_area_t* text_area = (my_text_area_t*)area;
  int32_t ime_x = 0;
  int32_t ime_y = 0;

  ASSERT_NOT_NULL(pal);
  ASSERT_NOT_NULL(loop);
  ASSERT_NOT_NULL(wm);
  ASSERT_NOT_NULL(win);
  ASSERT_NOT_NULL(area);
  ASSERT_EQ(my_widget_set_rect(area, &(my_rect_t){10, 20, 54, 60}),
            MY_RET_OK);
  ASSERT_EQ(my_text_area_set_wrap(area, true), MY_RET_OK);
  ASSERT_EQ(my_text_area_set_align(area, MY_TEXT_ALIGN_JUSTIFY), MY_RET_OK);
  ASSERT_EQ(my_text_area_set_text(area, "aa bb cc"), MY_RET_OK);
  text_area->cursor_row = 0;
  text_area->cursor_col = 3;
  ASSERT_EQ(my_widget_add_child(my_window_widget(win), area), MY_RET_OK);
  my_widget_unref(area);
  ASSERT_EQ(my_window_manager_open(wm, win), MY_RET_OK);
  my_widget_unref((my_widget_t*)win);
  my_event_dispatcher_set_focus(&win->dispatcher, area);
  my_pal_dummy_get_ime_spot(win->pal_window, &ime_x, &ime_y);
  ASSERT_EQ(ime_x, 44);
  ASSERT_EQ(ime_y, 39);
  my_event_dispatcher_set_focus(&win->dispatcher, NULL);
  text_area->cursor_col = 6;
  my_event_dispatcher_set_focus(&win->dispatcher, area);
  my_pal_dummy_get_ime_spot(win->pal_window, &ime_x, &ime_y);
  ASSERT_EQ(ime_x, 14);
  ASSERT_EQ(ime_y, 55);

  my_window_manager_destroy(wm);
  my_pal_main_loop_destroy(loop);
  my_pal_destroy(pal);
}

#ifdef MYUI_BIDI
TEST(text_area_wrap_rtl_horizontal_crosses_visual_lines)
{
  my_widget_t* area = my_text_area_create(NULL);
  my_text_area_t* text_area = (my_text_area_t*)area;
  my_font_t* font = my_font_bitmap_create(NULL);
  my_event_t event = my_event_init(MY_EVENT_KEY_DOWN);

  ASSERT_NOT_NULL(area);
  ASSERT_NOT_NULL(font);
  ASSERT_EQ(my_widget_set_rect(area, &(my_rect_t){0, 0, 52, 80}), MY_RET_OK);
  my_text_area_set_font(area, font, 16);
  ASSERT_EQ(my_text_area_set_wrap(area, true), MY_RET_OK);
  ASSERT_EQ(my_text_area_set_text(area, "\xD7\x90\xD7\x91\xD7\x92\xD7\x93"),
            MY_RET_OK);
  ASSERT_EQ(my_text_area_visual_line_count(area), 2u);
  ASSERT_EQ(my_text_area_visual_line_at(area, 0u)->phys, 0u);
  ASSERT_EQ(my_text_area_visual_line_at(area, 1u)->phys, 0u);

  text_area->focused = true;
  text_area->cursor_row = 0u;
  text_area->cursor_col = 0u;
  text_area->anchor_row = 0u;
  text_area->anchor_col = 0u;
  event.u.key.key = MY_KEY_RIGHT;
  ASSERT_EQ(area->vtable->on_event(area, &event), MY_RET_OK);
  ASSERT_EQ(text_area->cursor_row, 0u);
  ASSERT_EQ(text_area->cursor_col, 4u);

  event.u.key.key = MY_KEY_LEFT;
  ASSERT_EQ(area->vtable->on_event(area, &event), MY_RET_OK);
  ASSERT_EQ(text_area->cursor_row, 0u);
  ASSERT_EQ(text_area->cursor_col, 0u);

  text_area->cursor_col = 0u;
  text_area->anchor_col = 0u;
  event.u.key.modifiers = MY_KEYMOD_SHIFT;
  event.u.key.key = MY_KEY_RIGHT;
  ASSERT_EQ(area->vtable->on_event(area, &event), MY_RET_OK);
  ASSERT_EQ(text_area->anchor_col, 0u);
  ASSERT_EQ(text_area->cursor_col, 4u);
  event.u.key.key = MY_KEY_LEFT;
  ASSERT_EQ(area->vtable->on_event(area, &event), MY_RET_OK);
  ASSERT_EQ(text_area->anchor_col, 0u);
  ASSERT_EQ(text_area->cursor_col, 0u);

  my_widget_unref(area);
  my_font_destroy(font);
}

TEST(text_area_wrap_rtl_horizontal_crosses_physical_lines)
{
  my_widget_t* area = my_text_area_create(NULL);
  my_text_area_t* text_area = (my_text_area_t*)area;
  my_font_t* font = my_font_bitmap_create(NULL);
  my_event_t event = my_event_init(MY_EVENT_KEY_DOWN);

  ASSERT_NOT_NULL(area);
  ASSERT_NOT_NULL(font);
  ASSERT_EQ(my_widget_set_rect(area, &(my_rect_t){0, 0, 52, 100}), MY_RET_OK);
  my_text_area_set_font(area, font, 16);
  ASSERT_EQ(my_text_area_set_wrap(area, true), MY_RET_OK);
  ASSERT_EQ(my_text_area_set_text(area,
                                  "\xD7\x90\xD7\x91\xD7\x92\xD7\x93\n"
                                  "\xD7\x94\xD7\x95\xD7\x96\xD7\x97"),
            MY_RET_OK);
  ASSERT_EQ(my_text_area_visual_line_count(area), 4u);
  ASSERT_EQ(my_text_area_visual_line_at(area, 0u)->phys, 0u);
  ASSERT_EQ(my_text_area_visual_line_at(area, 1u)->phys, 0u);
  ASSERT_EQ(my_text_area_visual_line_at(area, 2u)->phys, 1u);
  ASSERT_EQ(my_text_area_visual_line_at(area, 3u)->phys, 1u);
  text_area->focused = true;
  text_area->cursor_row = 0u;
  text_area->cursor_col = 0u;
  text_area->anchor_row = 0u;
  text_area->anchor_col = 0u;
  event.u.key.key = MY_KEY_RIGHT;
  ASSERT_EQ(area->vtable->on_event(area, &event), MY_RET_OK);
  ASSERT_EQ(text_area->cursor_row, 0u);
  ASSERT_EQ(text_area->cursor_col, 4u);
  ASSERT_EQ(area->vtable->on_event(area, &event), MY_RET_OK);
  ASSERT_EQ(text_area->cursor_row, 0u);
  ASSERT_EQ(text_area->cursor_col, 3u);
  ASSERT_EQ(area->vtable->on_event(area, &event), MY_RET_OK);
  ASSERT_EQ(text_area->cursor_row, 0u);
  ASSERT_EQ(text_area->cursor_col, 2u);
  ASSERT_EQ(area->vtable->on_event(area, &event), MY_RET_OK);
  ASSERT_EQ(text_area->cursor_row, 1u);
  ASSERT_EQ(text_area->cursor_col,
            my_text_area_visual_line_at(area, 2u)->start_cp +
                my_text_area_visual_line_at(area, 2u)->len_cp);

  event.u.key.key = MY_KEY_LEFT;
  ASSERT_EQ(area->vtable->on_event(area, &event), MY_RET_OK);
  ASSERT_EQ(text_area->cursor_row, 0u);
  ASSERT_EQ(text_area->cursor_col, 2u);

  text_area->cursor_row = 0u;
  text_area->cursor_col = 0u;
  text_area->anchor_row = 0u;
  text_area->anchor_col = 0u;
  event.u.key.modifiers = MY_KEYMOD_SHIFT;
  event.u.key.key = MY_KEY_RIGHT;
  ASSERT_EQ(area->vtable->on_event(area, &event), MY_RET_OK);
  ASSERT_EQ(area->vtable->on_event(area, &event), MY_RET_OK);
  ASSERT_EQ(area->vtable->on_event(area, &event), MY_RET_OK);
  ASSERT_EQ(area->vtable->on_event(area, &event), MY_RET_OK);
  ASSERT_EQ(text_area->anchor_row, 0u);
  ASSERT_EQ(text_area->anchor_col, 0u);
  ASSERT_EQ(text_area->cursor_row, 1u);
  ASSERT_EQ(text_area->cursor_col,
            my_text_area_visual_line_at(area, 2u)->start_cp +
                my_text_area_visual_line_at(area, 2u)->len_cp);

  my_widget_unref(area);
  my_font_destroy(font);
}

TEST(text_area_rtl_navigation_state_invalidates_after_text_replace)
{
  my_widget_t* area = my_text_area_create(NULL);
  my_text_area_t* text_area = (my_text_area_t*)area;
  my_font_t* font = my_font_bitmap_create(NULL);
  my_event_t event = my_event_init(MY_EVENT_KEY_DOWN);

  ASSERT_NOT_NULL(area);
  ASSERT_NOT_NULL(font);
  ASSERT_EQ(my_widget_set_rect(area, &(my_rect_t){0, 0, 52, 100}), MY_RET_OK);
  my_text_area_set_font(area, font, 16);
  ASSERT_EQ(my_text_area_set_wrap(area, true), MY_RET_OK);
  ASSERT_EQ(my_text_area_set_text(area,
                                  "\xD7\x90\xD7\x91\xD7\x92\xD7\x93\n"
                                  "\xD7\x94\xD7\x95\xD7\x96\xD7\x97"),
            MY_RET_OK);
  ASSERT_EQ(my_text_area_visual_line_count(area), 4u);

  text_area->focused = true;
  text_area->cursor_row = 0u;
  text_area->cursor_col = 0u;
  text_area->anchor_row = 0u;
  text_area->anchor_col = 0u;
  event.u.key.key = MY_KEY_RIGHT;
  ASSERT_EQ(area->vtable->on_event(area, &event), MY_RET_OK);
  ASSERT_TRUE(text_area->navigation_valid);

  ASSERT_EQ(my_text_area_set_text(area, "\xD7\x90\xD7\x91"), MY_RET_OK);
  ASSERT_FALSE(text_area->navigation_valid);
  ASSERT_EQ(my_text_area_visual_line_count(area), 1u);
  text_area->focused = true;
  text_area->cursor_row = 0u;
  text_area->cursor_col = 0u;
  text_area->anchor_row = 0u;
  text_area->anchor_col = 0u;
  ASSERT_EQ(area->vtable->on_event(area, &event), MY_RET_OK);
  ASSERT_EQ(text_area->cursor_row, 0u);
  ASSERT_NOT_NULL(text_area->rtl_layout);
  ASSERT_EQ(text_area->cursor_col,
            my_text_layout_boundary_right(text_area->rtl_layout, 0u));

  my_widget_unref(area);
  my_font_destroy(font);
}

TEST(text_area_nonwrap_rtl_ime_spot_uses_visual_boundary)
{
  my_pal_t* pal = my_pal_dummy_create(NULL);
  my_pal_main_loop_t* loop = my_pal_main_loop_create(pal);
  my_window_manager_t* wm = my_window_manager_create(NULL, pal, loop);
  my_window_t* win = my_window_create(NULL, pal, 200, 100, "main");
  my_widget_t* area = my_text_area_create(NULL);
  my_font_t* font = my_font_bitmap_create(NULL);
  my_text_layout_t* layout;
  int32_t ime_x = 0;
  int32_t ime_y = 0;

  ASSERT_NOT_NULL(pal);
  ASSERT_NOT_NULL(loop);
  ASSERT_NOT_NULL(wm);
  ASSERT_NOT_NULL(win);
  ASSERT_NOT_NULL(area);
  ASSERT_NOT_NULL(font);
  ASSERT_EQ(my_widget_set_rect(area, &(my_rect_t){10, 20, 100, 40}),
            MY_RET_OK);
  my_text_area_set_font(area, font, 16);
  ASSERT_EQ(my_text_area_set_text(area, "\xD7\x90\xD7\x91\xD7\x92"),
            MY_RET_OK);
  ((my_text_area_t*)area)->cursor_row = 0;
  ((my_text_area_t*)area)->cursor_col = 0;
  ASSERT_EQ(my_widget_add_child(my_window_widget(win), area), MY_RET_OK);
  my_widget_unref(area);
  ASSERT_EQ(my_window_manager_open(wm, win), MY_RET_OK);
  my_widget_unref((my_widget_t*)win);
  my_event_dispatcher_set_focus(&win->dispatcher, area);
  my_pal_dummy_get_ime_spot(win->pal_window, &ime_x, &ime_y);
  layout = my_text_layout_process(NULL, "\xD7\x90\xD7\x91\xD7\x92");
  ASSERT_NOT_NULL(layout);
  ASSERT_EQ(ime_x, 10 + 4 + (100 - 4 - 4 - 48) +
                       my_text_layout_visual_x(layout, font, 16, 0));
  my_text_layout_destroy(layout);

  my_event_dispatcher_set_focus(&win->dispatcher, NULL);
  my_window_manager_destroy(wm);
  my_pal_main_loop_destroy(loop);
  my_pal_destroy(pal);
  my_font_destroy(font);
}

TEST(text_area_wrap_rtl_ime_spot_uses_visual_boundary)
{
  my_pal_t* pal = my_pal_dummy_create(NULL);
  my_pal_main_loop_t* loop = my_pal_main_loop_create(pal);
  my_window_manager_t* wm = my_window_manager_create(NULL, pal, loop);
  my_window_t* win = my_window_create(NULL, pal, 200, 100, "main");
  my_widget_t* area = my_text_area_create(NULL);
  my_font_t* font = my_font_bitmap_create(NULL);
  my_text_layout_t* layout;
  int32_t ime_x = 0;
  int32_t ime_y = 0;

  ASSERT_NOT_NULL(pal);
  ASSERT_NOT_NULL(loop);
  ASSERT_NOT_NULL(wm);
  ASSERT_NOT_NULL(win);
  ASSERT_NOT_NULL(area);
  ASSERT_NOT_NULL(font);
  ASSERT_EQ(my_widget_set_rect(area, &(my_rect_t){10, 20, 100, 40}),
            MY_RET_OK);
  my_text_area_set_font(area, font, 16);
  ASSERT_EQ(my_text_area_set_wrap(area, true), MY_RET_OK);
  ASSERT_EQ(my_text_area_set_text(area, "\xD7\x90\xD7\x91\xD7\x92"),
            MY_RET_OK);
  ((my_text_area_t*)area)->cursor_row = 0;
  ((my_text_area_t*)area)->cursor_col = 0;
  ASSERT_EQ(my_widget_add_child(my_window_widget(win), area), MY_RET_OK);
  my_widget_unref(area);
  ASSERT_EQ(my_window_manager_open(wm, win), MY_RET_OK);
  my_widget_unref((my_widget_t*)win);
  my_event_dispatcher_set_focus(&win->dispatcher, area);
  my_pal_dummy_get_ime_spot(win->pal_window, &ime_x, &ime_y);
  layout = my_text_layout_process(NULL, "\xD7\x90\xD7\x91\xD7\x92");
  ASSERT_NOT_NULL(layout);
  ASSERT_EQ(ime_x, 10 + 4 + (100 - 4 - 4 - 48) +
                       my_text_layout_visual_x(layout, font, 16, 0));
  my_text_layout_destroy(layout);

  my_event_dispatcher_set_focus(&win->dispatcher, NULL);
  my_window_manager_destroy(wm);
  my_pal_main_loop_destroy(loop);
  my_pal_destroy(pal);
  my_font_destroy(font);
}

TEST(text_area_wrap_rtl_justify_cursor_tracks_stretched_space)
{
  my_pal_t* pal = my_pal_dummy_create(NULL);
  my_pal_main_loop_t* loop = my_pal_main_loop_create(pal);
  my_window_manager_t* wm = my_window_manager_create(NULL, pal, loop);
  my_window_t* win = my_window_create(NULL, pal, 200, 100, "main");
  my_widget_t* area = my_text_area_create(NULL);
  my_text_area_t* text_area = (my_text_area_t*)area;
  my_font_t* font = my_font_bitmap_create(NULL);
  const my_visual_line_t* visual_line;
  my_text_layout_t* layout;
  int32_t ime_x = 0;
  int32_t ime_y = 0;

  ASSERT_NOT_NULL(pal);
  ASSERT_NOT_NULL(loop);
  ASSERT_NOT_NULL(wm);
  ASSERT_NOT_NULL(win);
  ASSERT_NOT_NULL(area);
  ASSERT_NOT_NULL(font);
  ASSERT_EQ(my_widget_set_rect(area, &(my_rect_t){10, 20, 98, 60}),
            MY_RET_OK);
  my_text_area_set_font(area, font, 16);
  ASSERT_EQ(my_text_area_set_wrap(area, true), MY_RET_OK);
  ASSERT_EQ(my_text_area_set_align(area, MY_TEXT_ALIGN_JUSTIFY), MY_RET_OK);
  ASSERT_EQ(my_text_area_set_text(
                area, "\xD7\x90\xD7\x91 \xD7\x92\xD7\x93 \xD7\x94\xD7\x95"),
            MY_RET_OK);
  ASSERT_EQ(my_text_area_visual_line_count(area), 2u);
  visual_line = my_text_area_visual_line_at(area, 0u);
  ASSERT_NOT_NULL(visual_line);
  ASSERT_EQ(visual_line->len_cp, 5u);
  text_area->cursor_row = 0u;
  text_area->cursor_col = 1u;
  ASSERT_EQ(my_widget_add_child(my_window_widget(win), area), MY_RET_OK);
  my_widget_unref(area);
  ASSERT_EQ(my_window_manager_open(wm, win), MY_RET_OK);
  my_widget_unref((my_widget_t*)win);
  my_event_dispatcher_set_focus(&win->dispatcher, area);
  my_pal_dummy_get_ime_spot(win->pal_window, &ime_x, &ime_y);

  layout = my_text_layout_process(NULL, "\xD7\x90\xD7\x91 \xD7\x92\xD7\x93");
  ASSERT_NOT_NULL(layout);
  ASSERT_EQ(ime_x, 10 + 4 +
                       my_text_layout_visual_x(layout, font, 16, 1u) + 10);
  my_text_layout_destroy(layout);
  my_event_dispatcher_set_focus(&win->dispatcher, NULL);
  my_window_manager_destroy(wm);
  my_pal_main_loop_destroy(loop);
  my_pal_destroy(pal);
  my_font_destroy(font);
}

TEST(text_area_rtl_justify_selection_uses_stretched_visual_rect)
{
  my_widget_t* area = my_text_area_create(NULL);
  my_text_area_t* text_area = (my_text_area_t*)area;
  my_font_t* font = my_font_bitmap_create(NULL);
  my_lcd_t* lcd = my_lcd_mem_create(NULL, 120, 80, MY_PIXEL_FORMAT_BGRA8888);
  my_vgcanvas_t* canvas = my_vgcanvas_soft_create(NULL, lcd);
  uint8_t* pixels;
  uint32_t stride;

  ASSERT_NOT_NULL(area);
  ASSERT_NOT_NULL(font);
  ASSERT_NOT_NULL(lcd);
  ASSERT_NOT_NULL(canvas);
  ASSERT_EQ(my_widget_set_rect(area, &(my_rect_t){0, 0, 98, 60}),
            MY_RET_OK);
  my_text_area_set_font(area, font, 16);
  ASSERT_EQ(my_text_area_set_wrap(area, true), MY_RET_OK);
  ASSERT_EQ(my_text_area_set_align(area, MY_TEXT_ALIGN_JUSTIFY), MY_RET_OK);
  ASSERT_EQ(my_text_area_set_text(
                area, "\xD7\x90\xD7\x91 \xD7\x92\xD7\x93 \xD7\x94\xD7\x95"),
            MY_RET_OK);
  text_area->anchor_row = 0u;
  text_area->anchor_col = 0u;
  text_area->cursor_row = 0u;
  text_area->cursor_col = 1u;
  ASSERT_EQ(my_vgcanvas_begin_frame(canvas, NULL), MY_RET_OK);
  area->vtable->on_paint(area, canvas);
  ASSERT_EQ(my_vgcanvas_end_frame(canvas), MY_RET_OK);
  pixels = my_lcd_mem_get_buffer(lcd);
  stride = my_lcd_mem_get_stride(lcd);
  ASSERT_NOT_NULL(pixels);
  ASSERT_EQ(pixels[18u * stride + 80u * 4u], 230u);
  ASSERT_EQ(pixels[18u * stride + 80u * 4u + 1u], 170u);
  ASSERT_EQ(pixels[18u * stride + 80u * 4u + 2u], 130u);
  my_vgcanvas_destroy(canvas);
  my_lcd_destroy(lcd);
  my_widget_unref(area);
  my_font_destroy(font);
}

TEST(text_area_nonwrap_rtl_geometry_keeps_logical_boundaries)
{
  my_font_t font = {&text_area_ligature_vtable};
  my_widget_t* area = my_text_area_create(NULL);
  my_text_area_t* text_area = (my_text_area_t*)area;
  my_event_t event = my_event_init(MY_EVENT_POINTER_DOWN);

  ASSERT_NOT_NULL(area);
  ASSERT_EQ(my_widget_set_rect(area, &(my_rect_t){0, 0, 100, 40}), MY_RET_OK);
  my_text_area_set_font(area, &font, 16);
  ASSERT_EQ(my_text_area_set_text(area, "\xD7\x90\xD7\x91"), MY_RET_OK);
  event.u.pointer.x = 15;
  event.u.pointer.y = 5;
  ASSERT_EQ(area->vtable->on_event(area, &event), MY_RET_OK);
  ASSERT_EQ(text_area->geometry_boundaries[0], 16);
  ASSERT_EQ(text_area->geometry_boundaries[1], 8);
  ASSERT_EQ(text_area->geometry_boundaries[2], 0);
  my_widget_unref(area);
}

TEST(text_area_nonwrap_rtl_geometry_works_without_shaping)
{
  my_font_t* font = my_font_bitmap_create(NULL);
  my_widget_t* area = my_text_area_create(NULL);
  my_text_area_t* text_area = (my_text_area_t*)area;
  my_event_t event = my_event_init(MY_EVENT_POINTER_DOWN);

  ASSERT_NOT_NULL(font);
  ASSERT_NOT_NULL(area);
  ASSERT_EQ(my_widget_set_rect(area, &(my_rect_t){0, 0, 100, 40}), MY_RET_OK);
  my_text_area_set_font(area, font, 16);
  ASSERT_EQ(my_text_area_set_text(area, "\xD7\x90\xD7\x91"), MY_RET_OK);
  event.u.pointer.x = 15;
  event.u.pointer.y = 5;
  ASSERT_EQ(area->vtable->on_event(area, &event), MY_RET_OK);
  ASSERT_EQ(text_area->geometry_boundaries[0], 32);
  ASSERT_EQ(text_area->geometry_boundaries[1], 16);
  ASSERT_EQ(text_area->geometry_boundaries[2], 0);
  my_font_destroy(font);
  my_widget_unref(area);
}
#endif

TEST(removing_focused_widget_blurs_and_disables_ime)
{
  my_pal_t *pal = my_pal_dummy_create(NULL);
  my_pal_main_loop_t *loop = my_pal_main_loop_create(pal);
  my_window_manager_t *wm = my_window_manager_create(NULL, pal, loop);
  my_window_t *win = my_window_create(NULL, pal, 400, 300, "main");
  my_widget_t *edit = my_edit_create(NULL);

  ASSERT_NOT_NULL(pal);
  ASSERT_NOT_NULL(loop);
  ASSERT_NOT_NULL(wm);
  ASSERT_NOT_NULL(win);
  ASSERT_NOT_NULL(edit);
  ASSERT_EQ(my_widget_add_child(my_window_widget(win), edit), MY_RET_OK);
  ASSERT_EQ(my_window_manager_open(wm, win), MY_RET_OK);
  my_widget_unref((my_widget_t *)win);
  my_event_dispatcher_set_focus(&win->dispatcher, edit);
  ASSERT_TRUE(((my_edit_t *)edit)->focused);
  ASSERT_TRUE(my_pal_dummy_get_ime_enabled(win->pal_window));

  ASSERT_EQ(my_widget_remove_child(my_window_widget(win), edit), MY_RET_OK);
  ASSERT_TRUE(win->dispatcher.focused == NULL);
  ASSERT_FALSE(((my_edit_t *)edit)->focused);
  ASSERT_FALSE(my_pal_dummy_get_ime_enabled(win->pal_window));

  my_widget_unref(edit);
  my_window_manager_destroy(wm);
  my_pal_main_loop_destroy(loop);
  my_pal_destroy(pal);
}

TEST(removing_hovered_grabbed_widget_resets_dispatch_state)
{
  my_pal_t *pal = my_pal_dummy_create(NULL);
  my_pal_main_loop_t *loop = my_pal_main_loop_create(pal);
  my_window_manager_t *wm = my_window_manager_create(NULL, pal, loop);
  my_window_t *win = my_window_create(NULL, pal, 400, 300, "main");
  my_widget_t *button = my_button_create(NULL, "drag");
  my_event_t event = my_event_init(MY_EVENT_POINTER_MOVE);

  ASSERT_NOT_NULL(pal);
  ASSERT_NOT_NULL(loop);
  ASSERT_NOT_NULL(wm);
  ASSERT_NOT_NULL(win);
  ASSERT_NOT_NULL(button);
  ASSERT_EQ(my_widget_set_rect(button, &(my_rect_t){10, 10, 80, 32}),
            MY_RET_OK);
  ASSERT_EQ(my_widget_add_child(my_window_widget(win), button), MY_RET_OK);
  ASSERT_EQ(my_window_manager_open(wm, win), MY_RET_OK);
  my_widget_unref((my_widget_t *)win);

  event.u.pointer.x = 20;
  event.u.pointer.y = 20;
  ASSERT_EQ(my_window_manager_dispatch_surface_event(wm, &event), MY_RET_OK);
  ASSERT_TRUE(win->dispatcher.hovered == button);
  ASSERT_EQ(my_pal_dummy_get_cursor(win->pal_window), MY_CURSOR_HAND);

  event.type = MY_EVENT_POINTER_DOWN;
  ASSERT_EQ(my_window_manager_dispatch_surface_event(wm, &event), MY_RET_OK);
  ASSERT_TRUE(win->dispatcher.grabbed == button);
  ASSERT_EQ(my_widget_remove_child(my_window_widget(win), button), MY_RET_OK);
  ASSERT_TRUE(win->dispatcher.grabbed == NULL);
  ASSERT_TRUE(win->dispatcher.hovered == NULL);
  ASSERT_FALSE(button->hovered);
  ASSERT_EQ(my_pal_dummy_get_cursor(win->pal_window), MY_CURSOR_ARROW);

  event.type = MY_EVENT_POINTER_MOVE;
  ASSERT_EQ(my_window_manager_dispatch_surface_event(wm, &event), MY_RET_OK);
  event.type = MY_EVENT_POINTER_UP;
  ASSERT_EQ(my_window_manager_dispatch_surface_event(wm, &event), MY_RET_OK);

  my_widget_unref(button);
  my_window_manager_destroy(wm);
  my_pal_main_loop_destroy(loop);
  my_pal_destroy(pal);
}

TEST(event_bubbling_stops_at_removed_ancestor)
{
  my_pal_t *pal = my_pal_dummy_create(NULL);
  my_window_t *win = my_window_create(NULL, pal, 100, 80, "main");
  my_widget_t *parent = my_widget_create(NULL, "parent");
  my_widget_t *leaf = my_widget_create(NULL, "leaf");
  bubbling_mutation_ctx_t ctx = {(my_widget_t *)win, parent, NULL, 0};
  my_event_t event = my_event_init(MY_EVENT_POINTER_DOWN);

  ASSERT_NOT_NULL(pal);
  ASSERT_NOT_NULL(win);
  ASSERT_NOT_NULL(parent);
  ASSERT_NOT_NULL(leaf);
  ASSERT_EQ(my_widget_subclass_init(parent, &s_detached_parent_vtable),
            MY_RET_OK);
  ASSERT_EQ(my_widget_subclass_init(leaf, &s_mutation_leaf_vtable),
            MY_RET_OK);
  ASSERT_EQ(my_widget_set_user_data(parent, &ctx), MY_RET_OK);
  ASSERT_EQ(my_widget_set_user_data(leaf, &ctx), MY_RET_OK);
  ASSERT_EQ(my_widget_set_rect(parent, &(my_rect_t){0, 0, 80, 60}),
            MY_RET_OK);
  ASSERT_EQ(my_widget_set_rect(leaf, &(my_rect_t){0, 0, 20, 20}),
            MY_RET_OK);
  ASSERT_EQ(my_widget_add_child((my_widget_t *)win, parent), MY_RET_OK);
  ASSERT_EQ(my_widget_add_child(parent, leaf), MY_RET_OK);

  event.u.pointer.x = 5;
  event.u.pointer.y = 5;
  ASSERT_FALSE(my_event_dispatch(&win->dispatcher, &event));
  ASSERT_EQ(ctx.parent_events, 0);
  ASSERT_TRUE(parent->parent == NULL);
  ASSERT_TRUE(win->dispatcher.grabbed == NULL);

  my_widget_unref(leaf);
  my_widget_unref(parent);
  my_object_unref((my_object_t *)win);
  my_pal_destroy(pal);
}

TEST(event_bubbling_stops_at_self_removed_leaf)
{
  my_pal_t *pal = my_pal_dummy_create(NULL);
  my_window_t *win = my_window_create(NULL, pal, 100, 80, "main");
  my_widget_t *parent = my_widget_create(NULL, "parent");
  my_widget_t *leaf = my_widget_create(NULL, "leaf");
  bubbling_mutation_ctx_t ctx = {(my_widget_t *)win, NULL, leaf, 0};
  my_event_t event = my_event_init(MY_EVENT_POINTER_DOWN);

  ASSERT_NOT_NULL(pal);
  ASSERT_NOT_NULL(win);
  ASSERT_NOT_NULL(parent);
  ASSERT_NOT_NULL(leaf);
  ASSERT_EQ(my_widget_subclass_init(parent, &s_detached_parent_vtable),
            MY_RET_OK);
  ASSERT_EQ(my_widget_subclass_init(leaf, &s_self_removing_leaf_vtable),
            MY_RET_OK);
  ASSERT_EQ(my_widget_set_user_data(parent, &ctx), MY_RET_OK);
  ASSERT_EQ(my_widget_set_user_data(leaf, &ctx), MY_RET_OK);
  ASSERT_EQ(my_widget_set_rect(parent, &(my_rect_t){0, 0, 80, 60}),
            MY_RET_OK);
  ASSERT_EQ(my_widget_set_rect(leaf, &(my_rect_t){0, 0, 20, 20}),
            MY_RET_OK);
  ASSERT_EQ(my_widget_add_child((my_widget_t *)win, parent), MY_RET_OK);
  ASSERT_EQ(my_widget_add_child(parent, leaf), MY_RET_OK);

  event.u.pointer.x = 5;
  event.u.pointer.y = 5;
  ASSERT_FALSE(my_event_dispatch(&win->dispatcher, &event));
  ASSERT_EQ(ctx.parent_events, 0);
  ASSERT_TRUE(leaf->parent == NULL);
  ASSERT_TRUE(parent->parent == (my_widget_t *)win);
  ASSERT_TRUE(win->dispatcher.grabbed == NULL);

  my_widget_unref(leaf);
  my_widget_unref(parent);
  my_object_unref((my_object_t *)win);
  my_pal_destroy(pal);
}

TEST(text_widgets_apply_ime_delete_surrounding)
{
  my_pal_t *pal = my_pal_dummy_create(NULL);
  my_pal_main_loop_t *loop = my_pal_main_loop_create(pal);
  my_window_manager_t *wm = my_window_manager_create(NULL, pal, loop);
  my_window_t *win = my_window_create(NULL, pal, 400, 300, "main");
  my_widget_t *edit = my_edit_create(NULL);
  my_widget_t *text_area = my_text_area_create(NULL);
  my_event_t event = my_event_init(MY_EVENT_IME_DELETE_SURROUNDING);

  ASSERT_EQ(my_widget_add_child(my_window_widget(win), edit), MY_RET_OK);
  ASSERT_EQ(my_widget_add_child(my_window_widget(win), text_area), MY_RET_OK);
  my_widget_unref(edit);
  my_widget_unref(text_area);
  ASSERT_EQ(my_window_manager_open(wm, win), MY_RET_OK);
  my_widget_unref((my_widget_t *)win);

  ASSERT_EQ(my_edit_set_text(edit, "ab\xE4\xB8\xAD" "cd"), MY_RET_OK);
  ((my_edit_t *)edit)->cursor = 5;
  ((my_edit_t *)edit)->anchor = 5;
  my_event_dispatcher_set_focus(&win->dispatcher, edit);
  event.u.ime.before = 3;
  event.u.ime.after = 1;
  ASSERT_EQ(my_window_manager_dispatch_surface_event(wm, &event), MY_RET_OK);
  ASSERT_EQ(strcmp(my_edit_get_text(edit), "abd"), 0);

  ASSERT_EQ(my_text_area_set_text(text_area, "ab\xE4\xB8\xAD" "cd"),
            MY_RET_OK);
  ((my_text_area_t *)text_area)->cursor_row = 0;
  ((my_text_area_t *)text_area)->cursor_col = 3;
  ((my_text_area_t *)text_area)->anchor_row = 0;
  ((my_text_area_t *)text_area)->anchor_col = 3;
  my_event_dispatcher_set_focus(&win->dispatcher, text_area);
  ASSERT_EQ(my_window_manager_dispatch_surface_event(wm, &event), MY_RET_OK);
  ASSERT_EQ(strcmp(my_text_area_get_text(text_area), "abd"), 0);

  my_window_manager_destroy(wm);
  my_pal_main_loop_destroy(loop);
  my_pal_destroy(pal);
}

TEST(text_widgets_paste_full_clipboard_without_fixed_buffer_limit)
{
  enum { text_length = 8192 };
  my_pal_t *pal = my_pal_dummy_create(NULL);
  my_pal_main_loop_t *loop = my_pal_main_loop_create(pal);
  my_window_manager_t *wm = my_window_manager_create(NULL, pal, loop);
  my_window_t *win = my_window_create(NULL, pal, 400, 300, "main");
  my_widget_t *edit = my_edit_create(NULL);
  my_widget_t *text_area = my_text_area_create(NULL);
  my_event_t event = my_event_init(MY_EVENT_KEY_DOWN);
  char text[text_length + 1];

  memset(text, 'x', text_length);
  text[text_length] = '\0';
  ASSERT_EQ(my_widget_add_child(my_window_widget(win), edit), MY_RET_OK);
  ASSERT_EQ(my_widget_add_child(my_window_widget(win), text_area), MY_RET_OK);
  my_widget_unref(edit);
  my_widget_unref(text_area);
  ASSERT_EQ(my_window_manager_open(wm, win), MY_RET_OK);
  my_widget_unref((my_widget_t *)win);
  ASSERT_EQ(my_pal_clipboard_set_text(pal, text), MY_RET_OK);

  event.u.key.key = 'v';
  event.u.key.modifiers = MY_KEYMOD_CTRL;
  my_event_dispatcher_set_focus(&win->dispatcher, edit);
  ASSERT_EQ(my_window_manager_dispatch_surface_event(wm, &event), MY_RET_OK);
  ASSERT_EQ(strlen(my_edit_get_text(edit)), (size_t)text_length);

  my_event_dispatcher_set_focus(&win->dispatcher, text_area);
  ASSERT_EQ(my_window_manager_dispatch_surface_event(wm, &event), MY_RET_OK);
  ASSERT_EQ(strlen(my_text_area_get_text(text_area)), (size_t)text_length);

  my_window_manager_destroy(wm);
  my_pal_main_loop_destroy(loop);
  my_pal_destroy(pal);
}

TEST(window_close_cancels_node_view_flow_timer)
{
  my_pal_t *pal = my_pal_dummy_create(NULL);
  my_pal_main_loop_t *loop = my_pal_main_loop_create(pal);
  my_window_manager_t *wm = my_window_manager_create(NULL, pal, loop);
  my_window_t *win = my_window_create(NULL, pal, 400, 300, "main");
  my_widget_t *view = my_node_view_create(NULL);
  my_widget_t *na = NULL;
  my_widget_t *nb = NULL;

  ASSERT_NOT_NULL(pal);
  ASSERT_NOT_NULL(loop);
  ASSERT_NOT_NULL(wm);
  ASSERT_NOT_NULL(win);
  ASSERT_NOT_NULL(view);
  my_window_manager_set_auto_paint(wm, false); /* isolate the flow tick */
  ASSERT_EQ(my_widget_add_child(my_window_widget(win), view), MY_RET_OK);
  my_widget_unref(view);
  na = my_node_view_add_node(view, "a", "A", "cat", 20, 20, 120, 60);
  nb = my_node_view_add_node(view, "b", "B", "cat", 240, 20, 120, 60);
  ASSERT_NOT_NULL(na);
  ASSERT_NOT_NULL(nb);
  ASSERT_EQ(my_window_manager_open(wm, win), MY_RET_OK);
  my_widget_unref((my_widget_t *)win);
  my_node_view_set_flow_enabled(view, true); /* arms the 33ms flow timer */

  my_pal_dummy_set_now_ms(pal, 10000);
  ASSERT_EQ(my_pal_main_loop_run(loop), MY_RET_OK);
  ASSERT_TRUE(my_node_view_flow_offset(view) > 0.0f); /* timer really ran */

  /* Close with the flow timer live: the destroy chain must cancel it via
   * the still-valid win->loop. Pre-fix wm_release_window_at nulled
   * loop/anim_mgr first, so the shared loop kept a timer that ticked the
   * freed view 33ms later (heap UAF, ASAN-catchable). */
  ASSERT_EQ(my_window_manager_close(wm, win), MY_RET_OK);
  ASSERT_EQ(my_window_manager_count(wm), 0u);
  my_pal_dummy_set_now_ms(pal, 20000);
  ASSERT_EQ(my_pal_main_loop_run(loop), MY_RET_OK);

  my_window_manager_destroy(wm);
  my_pal_main_loop_destroy(loop);
  my_pal_destroy(pal);
}

TEST(node_view_remove_node_cancels_magnet_preview)
{
  my_widget_t *view = my_node_view_create(NULL);
  my_widget_t *na = NULL;
  my_widget_t *nb = NULL;
  int32_t ax = 0, ay = 0, bx = 0, by = 0;
  my_event_t ev;

  ASSERT_NOT_NULL(view);
  ASSERT_EQ(my_widget_set_rect(view, &(my_rect_t){0, 0, 400, 300}),
            MY_RET_OK);
  na = my_node_view_add_node(view, "a", "A", "cat", 20, 20, 120, 60);
  nb = my_node_view_add_node(view, "b", "B", "cat", 240, 20, 120, 60);
  ASSERT_NOT_NULL(na);
  ASSERT_NOT_NULL(nb);
  ASSERT_EQ(my_node_add_socket(na, MY_SOCKET_OUT, "out", 0u), MY_RET_OK);
  ASSERT_EQ(my_node_add_socket(nb, MY_SOCKET_IN, "in", 0u), MY_RET_OK);
  ASSERT_TRUE(my_node_socket_center(na, MY_SOCKET_OUT, 0, &ax, &ay));
  ASSERT_TRUE(my_node_socket_center(nb, MY_SOCKET_IN, 0, &bx, &by));

  /* drag a link out of a's output socket: preview activates */
  ev = my_event_init(MY_EVENT_POINTER_DOWN);
  ev.u.pointer.x = ax;
  ev.u.pointer.y = ay;
  ev.u.pointer.button = 1;
  ASSERT_EQ(view->vtable->on_event(view, &ev), MY_RET_OK);
  /* hover b's input socket: the magnet snaps to b */
  ev = my_event_init(MY_EVENT_POINTER_MOVE);
  ev.u.pointer.x = bx;
  ev.u.pointer.y = by;
  ASSERT_EQ(view->vtable->on_event(view, &ev), MY_RET_OK);

  /* Delete the magnet TARGET: the preview must be cancelled, not left
   * pointing at the freed node (pre-fix POINTER_UP connected to it). */
  ASSERT_EQ(my_node_view_remove_node(view, "b"), MY_RET_OK);
  ev = my_event_init(MY_EVENT_POINTER_UP);
  ev.u.pointer.x = bx;
  ev.u.pointer.y = by;
  ev.u.pointer.button = 1;
  (void)view->vtable->on_event(view, &ev);
  ASSERT_EQ(my_node_view_link_count(view), 0u);

  my_widget_unref(view);
}

TEST(node_view_remove_node_clears_embedded_child_grab)
{
  my_widget_t *view = my_node_view_create(NULL);
  my_widget_t *nc = NULL;
  my_widget_t *btn = NULL;
  my_event_t ev;

  ASSERT_NOT_NULL(view);
  ASSERT_EQ(my_widget_set_rect(view, &(my_rect_t){0, 0, 400, 300}),
            MY_RET_OK);
  nc = my_node_view_add_node(view, "c", "C", "cat", 20, 20, 120, 80);
  ASSERT_NOT_NULL(nc);
  btn = my_button_create(NULL, "x");
  ASSERT_NOT_NULL(btn);
  ASSERT_EQ(my_widget_set_rect(btn, &(my_rect_t){10, 30, 40, 20}), MY_RET_OK);
  ASSERT_EQ(my_widget_add_child(nc, btn), MY_RET_OK);
  my_widget_unref(btn);

  /* press the embedded button: the view grabs it (M23c) */
  ev = my_event_init(MY_EVENT_POINTER_DOWN);
  ev.u.pointer.x = 35; /* node (20,20) + button (10,30) + (5,5) */
  ev.u.pointer.y = 55;
  ev.u.pointer.button = 1;
  ASSERT_EQ(view->vtable->on_event(view, &ev), MY_RET_OK);
  /* moves are forwarded to the grabbed child while it lives */
  ev = my_event_init(MY_EVENT_POINTER_MOVE);
  ev.u.pointer.x = 36;
  ev.u.pointer.y = 56;
  ASSERT_EQ(view->vtable->on_event(view, &ev), MY_RET_OK);

  /* deleting the node kills the grabbed child with it */
  ASSERT_EQ(my_node_view_remove_node(view, "c"), MY_RET_OK);
  /* pre-fix the next move dereferenced the freed child's vtable and
   * returned OK; the grab must be cleared instead */
  ASSERT_EQ(view->vtable->on_event(view, &ev), MY_RET_FAIL);

  my_widget_unref(view);
}

TEST(node_view_generic_child_removal_clears_weak_state)
{
  my_widget_t *view = my_node_view_create(NULL);
  my_widget_t *out_node = NULL;
  my_widget_t *in_node = NULL;
  my_widget_t *held_node = NULL;
  int32_t x = 0, y = 0;
  my_event_t ev;

  ASSERT_NOT_NULL(view);
  ASSERT_EQ(my_widget_set_rect(view, &(my_rect_t){0, 0, 400, 300}),
            MY_RET_OK);
  out_node = my_node_view_add_node(view, "out", "Out", "cat", 20, 20,
                                   120, 60);
  in_node = my_node_view_add_node(view, "in", "In", "cat", 240, 20,
                                  120, 60);
  ASSERT_NOT_NULL(out_node);
  ASSERT_NOT_NULL(in_node);
  ASSERT_EQ(my_node_add_socket(out_node, MY_SOCKET_OUT, "out", 0u),
            MY_RET_OK);
  ASSERT_EQ(my_node_add_socket(in_node, MY_SOCKET_IN, "in", 0u), MY_RET_OK);
  ASSERT_EQ(my_node_view_connect(view, out_node, 0, in_node, 0), MY_RET_OK);

  /* Retain the node so generic tree removal does not destroy it. */
  held_node = my_widget_ref(out_node);
  ev = my_event_init(MY_EVENT_POINTER_DOWN);
  ev.u.pointer.x = out_node->rect.x + 20;
  ev.u.pointer.y = out_node->rect.y + 10;
  ev.u.pointer.button = 1;
  ASSERT_EQ(view->vtable->on_event(view, &ev), MY_RET_OK);
  ASSERT_TRUE(my_node_view_is_selected(view, out_node));

  ASSERT_EQ(my_widget_remove_child(view, out_node), MY_RET_OK);
  ASSERT_EQ(my_node_view_link_count(view), 0u);
  ASSERT_EQ(my_node_view_selected_count(view), 0u);
  ASSERT_EQ(my_node_view_get_selected(view), -1);
  ASSERT_EQ(my_node_view_find_link_at(view, x, y), -1);
  ASSERT_TRUE(my_node_get_id(held_node) != NULL);
  my_widget_unref(held_node);
  my_widget_unref(view);
}

TEST(node_view_destroy_detaches_externally_held_nodes)
{
  my_widget_t *view = my_node_view_create(NULL);
  my_widget_t *node;
  my_lcd_t *lcd = NULL;
  my_vgcanvas_t *canvas = NULL;

  ASSERT_NOT_NULL(view);
  node = my_node_view_add_node(view, "held", "Held", "cat", 20, 20,
                               120, 60);
  ASSERT_NOT_NULL(node);
  my_widget_ref(node);
  my_widget_unref(view);
  ASSERT_TRUE(my_node_get_id(node) != NULL);
  lcd = my_lcd_mem_create(NULL, 160, 80, MY_PIXEL_FORMAT_BGRA8888);
  canvas = my_vgcanvas_soft_create(NULL, lcd);
  ASSERT_NOT_NULL(lcd);
  ASSERT_NOT_NULL(canvas);
  ASSERT_EQ(my_vgcanvas_begin_frame(canvas, NULL), MY_RET_OK);
  node->vtable->on_paint(node, canvas);
  ASSERT_EQ(my_vgcanvas_end_frame(canvas), MY_RET_OK);
  my_vgcanvas_destroy(canvas);
  my_lcd_destroy(lcd);
  my_widget_unref(node);
}

typedef struct focus_move_ctx_t {
  my_event_dispatcher_t *dispatcher;
  my_widget_t *target;
  int done;
} focus_move_ctx_t;

static void blur_moves_focus_cb(void *ctx, const char *event,
                                void *event_data) {
  focus_move_ctx_t *c = (focus_move_ctx_t *)ctx;
  (void)event;
  (void)event_data;
  if (!c->done) {
    c->done = 1; /* reentrant blurs must not recurse */
    my_event_dispatcher_set_focus(c->dispatcher, c->target);
  }
}

TEST(blur_handler_can_move_focus_to_another_widget)
{
  my_pal_t *pal = my_pal_dummy_create(NULL);
  my_window_t *win = my_window_create(NULL, pal, 200, 100, "main");
  my_widget_t *a = my_button_create(NULL, "a");
  my_widget_t *b = my_button_create(NULL, "b");
  focus_move_ctx_t ctx;

  ASSERT_NOT_NULL(pal);
  ASSERT_NOT_NULL(win);
  ASSERT_NOT_NULL(a);
  ASSERT_NOT_NULL(b);
  ctx.dispatcher = &win->dispatcher;
  ctx.target = b;
  ctx.done = 0;
  ASSERT_EQ(my_widget_add_child(my_window_widget(win), a), MY_RET_OK);
  ASSERT_EQ(my_widget_add_child(my_window_widget(win), b), MY_RET_OK);
  my_widget_unref(a);
  my_widget_unref(b);
  ASSERT_TRUE(my_widget_on(a, "blur", blur_moves_focus_cb, &ctx) != 0u);

  my_event_dispatcher_set_focus(&win->dispatcher, a);
  ASSERT_TRUE(win->dispatcher.focused == a);
  /* blurring a lets its handler move focus to b; the outer set_focus(NULL)
   * must not clobber that choice */
  my_event_dispatcher_set_focus(&win->dispatcher, NULL);
  ASSERT_TRUE(win->dispatcher.focused == b);

  my_object_unref((my_object_t *)win);
  my_pal_destroy(pal);
}

typedef struct blur_destroy_ctx_t {
  my_widget_t *root;
  my_widget_t *widget; /* owned ref, dropped from the blur handler */
  int done;
} blur_destroy_ctx_t;

static void blur_destroys_widget_cb(void *ctx, const char *event,
                                    void *event_data) {
  blur_destroy_ctx_t *c = (blur_destroy_ctx_t *)ctx;
  (void)event;
  (void)event_data;
  if (!c->done) {
    c->done = 1; /* the removal re-emits blur via forget(): no recursion */
    my_widget_remove_child(c->root, c->widget);
    my_widget_unref(c->widget); /* drop our ref: widget dies mid-emit */
    c->widget = NULL;
  }
}

TEST(blur_handler_can_destroy_the_old_focused_widget)
{
  my_pal_t *pal = my_pal_dummy_create(NULL);
  my_window_t *win = my_window_create(NULL, pal, 200, 100, "main");
  my_widget_t *a = my_button_create(NULL, "a");
  my_widget_t *b = my_button_create(NULL, "b");
  blur_destroy_ctx_t ctx;

  ASSERT_NOT_NULL(pal);
  ASSERT_NOT_NULL(win);
  ASSERT_NOT_NULL(a);
  ASSERT_NOT_NULL(b);
  ctx.root = my_window_widget(win);
  ctx.widget = a; /* we keep the create ref; the handler drops it */
  ctx.done = 0;
  ASSERT_EQ(my_widget_add_child(my_window_widget(win), a), MY_RET_OK);
  ASSERT_EQ(my_widget_add_child(my_window_widget(win), b), MY_RET_OK);
  my_widget_unref(b);
  ASSERT_TRUE(my_widget_on(a, "blur", blur_destroys_widget_cb, &ctx) != 0u);

  my_event_dispatcher_set_focus(&win->dispatcher, a);
  ASSERT_TRUE(win->dispatcher.focused == a);
  /* the blur handler destroys a (emitter freed) while the blur emit is
   * still unwinding on it — the dispatcher must hold a ref across the
   * emit (pre-fix heap UAF, ASAN-catchable) — and the caller's focus
   * target must still win afterwards */
  my_event_dispatcher_set_focus(&win->dispatcher, b);
  ASSERT_TRUE(ctx.widget == NULL);
  ASSERT_TRUE(win->dispatcher.focused == b);

  my_object_unref((my_object_t *)win);
  my_pal_destroy(pal);
}

TEST(window_close_invalidates_open_menu)
{
  my_pal_t *pal = my_pal_dummy_create(NULL);
  my_pal_main_loop_t *loop = my_pal_main_loop_create(pal);
  my_window_manager_t *wm = my_window_manager_create(NULL, pal, loop);
  my_window_t *win = my_window_create(NULL, pal, 400, 300, "main");
  my_menu_t *menu = my_menu_create(NULL);
  my_menu_t *sub = NULL;
  my_widget_t *overlay = NULL;
  my_widget_t *box = NULL;
  my_widget_t *item = NULL;
  my_event_t ev;

  ASSERT_NOT_NULL(pal);
  ASSERT_NOT_NULL(loop);
  ASSERT_NOT_NULL(wm);
  ASSERT_NOT_NULL(win);
  ASSERT_NOT_NULL(menu);
  ASSERT_EQ(my_menu_add_item(menu, "leaf", 1), MY_RET_OK);
  sub = my_menu_add_submenu(menu, "more");
  ASSERT_NOT_NULL(sub);
  ASSERT_EQ(my_menu_add_item(sub, "child", 2), MY_RET_OK);
  ASSERT_EQ(my_window_manager_open(wm, win), MY_RET_OK);
  my_widget_unref((my_widget_t *)win);
  ASSERT_EQ(my_menu_popup(win, menu, 10, 10, NULL, NULL), MY_RET_OK);
  ASSERT_TRUE(my_menu_widget(menu) != NULL);

  /* arm the 120ms submenu hover timer by hovering the "more" item */
  overlay = my_menu_widget(menu);
  box = my_widget_get_child(overlay, 0);
  ASSERT_NOT_NULL(box);
  item = my_widget_get_child(box, 1); /* 0 = leaf, 1 = more */
  ASSERT_NOT_NULL(item);
  ev = my_event_init(MY_EVENT_POINTER_MOVE);
  ASSERT_EQ(item->vtable->on_event(item, &ev), MY_RET_OK);

  /* closing the window destroys the overlay in place: the model must be
   * invalidated and the hover timer cancelled, not left dangling on the
   * freed window (pre-fix my_menu_dismiss/destroy dereferenced it) */
  ASSERT_EQ(my_window_manager_close(wm, win), MY_RET_OK);
  ASSERT_TRUE(my_menu_widget(menu) == NULL);

  my_pal_dummy_set_now_ms(pal, 10000);
  ASSERT_EQ(my_pal_main_loop_run(loop), MY_RET_OK); /* stale timer fires here pre-fix */
  my_menu_destroy(menu);
  my_window_manager_destroy(wm);
  my_pal_main_loop_destroy(loop);
  my_pal_destroy(pal);
}

TEST(window_close_invalidates_menu_with_external_window_ref)
{
  my_pal_t* pal = my_pal_dummy_create(NULL);
  my_pal_main_loop_t* loop = my_pal_main_loop_create(pal);
  my_window_manager_t* wm = my_window_manager_create(NULL, pal, loop);
  my_window_t* win = my_window_create(NULL, pal, 400, 300, "main");
  my_menu_t* menu = my_menu_create(NULL);
  my_menu_t* sub = NULL;
  my_widget_t* overlay = NULL;
  my_widget_t* box = NULL;
  my_widget_t* item = NULL;
  my_event_t ev;

  ASSERT_NOT_NULL(pal);
  ASSERT_NOT_NULL(loop);
  ASSERT_NOT_NULL(wm);
  ASSERT_NOT_NULL(win);
  ASSERT_NOT_NULL(menu);
  ASSERT_EQ(my_menu_add_item(menu, "leaf", 1), MY_RET_OK);
  sub = my_menu_add_submenu(menu, "more");
  ASSERT_NOT_NULL(sub);
  ASSERT_EQ(my_menu_add_item(sub, "child", 2), MY_RET_OK);
  ASSERT_EQ(my_window_manager_open(wm, win), MY_RET_OK);
  ASSERT_EQ(my_menu_popup(win, menu, 10, 10, NULL, NULL), MY_RET_OK);

  overlay = my_menu_widget(menu);
  box = my_widget_get_child(overlay, 0);
  item = my_widget_get_child(box, 1);
  ASSERT_NOT_NULL(item);
  ev = my_event_init(MY_EVENT_POINTER_MOVE);
  ASSERT_EQ(item->vtable->on_event(item, &ev), MY_RET_OK);

  ASSERT_EQ(my_window_manager_close(wm, win), MY_RET_OK);
  ASSERT_TRUE(my_menu_widget(menu) == NULL);
  ASSERT_TRUE(win->wm == NULL);
  ASSERT_TRUE(win->loop == NULL);

  ASSERT_EQ(my_window_manager_open(wm, win), MY_RET_OK);
  ASSERT_EQ(my_menu_popup(win, menu, 10, 10, NULL, NULL), MY_RET_OK);
  ASSERT_NOT_NULL(my_menu_widget(menu));
  ASSERT_EQ(my_window_manager_close(wm, win), MY_RET_OK);
  ASSERT_TRUE(my_menu_widget(menu) == NULL);

  my_pal_dummy_set_now_ms(pal, 10000);
  ASSERT_EQ(my_pal_main_loop_run(loop), MY_RET_OK);
  my_menu_destroy(menu);
  my_widget_unref((my_widget_t*)win);
  my_window_manager_destroy(wm);
  my_pal_main_loop_destroy(loop);
  my_pal_destroy(pal);
}

TEST(menu_detaches_when_window_manager_is_destroyed_first)
{
  my_pal_t* pal = my_pal_dummy_create(NULL);
  my_pal_main_loop_t* loop = my_pal_main_loop_create(pal);
  my_window_manager_t* wm = my_window_manager_create(NULL, pal, loop);
  my_window_t* win = my_window_create(NULL, pal, 160, 100, "main");
  my_menu_t* menu = my_menu_create(NULL);

  ASSERT_NOT_NULL(wm);
  ASSERT_NOT_NULL(win);
  ASSERT_NOT_NULL(menu);
  ASSERT_EQ(my_menu_add_item(menu, "item", 1), MY_RET_OK);
  ASSERT_EQ(my_window_manager_open(wm, win), MY_RET_OK);
  ASSERT_EQ(my_menu_popup(win, menu, 4, 4, NULL, NULL), MY_RET_OK);
  ASSERT_NOT_NULL(my_menu_widget(menu));

  my_window_manager_destroy(wm);
  ASSERT_TRUE(my_menu_widget(menu) == NULL);
  my_menu_dismiss(menu);
  my_menu_destroy(menu);
  my_widget_unref((my_widget_t*)win);
  my_pal_main_loop_destroy(loop);
  my_pal_destroy(pal);
}

TEST(menu_owned_callback_context_releases_once)
{
  my_pal_t* pal = my_pal_dummy_create(NULL);
  my_pal_main_loop_t* loop = my_pal_main_loop_create(pal);
  my_window_manager_t* wm = my_window_manager_create(NULL, pal, loop);
  my_window_t* win = my_window_create(NULL, pal, 160, 100, "menu-owned");
  my_menu_t* menu = my_menu_create(NULL);
  int context = 7;

  ASSERT_NOT_NULL(wm);
  ASSERT_NOT_NULL(win);
  ASSERT_NOT_NULL(menu);
  ASSERT_EQ(my_menu_add_item(menu, "item", 1), MY_RET_OK);
  ASSERT_EQ(my_window_manager_open(wm, win), MY_RET_OK);
  ASSERT_EQ(my_menu_popup_owned(win, menu, 4, 4, owned_menu_callback,
                                &context, owned_callback_destroy), MY_RET_OK);
  g_owned_callback_calls = 0;
  g_owned_callback_destroy_count = 0;
  my_menu_dismiss(menu);
  ASSERT_EQ(g_owned_callback_calls, 0);
  ASSERT_EQ(g_owned_callback_destroy_count, 1);
  my_menu_dismiss(menu);
  ASSERT_EQ(g_owned_callback_destroy_count, 1);

  my_menu_destroy(menu);
  my_widget_unref((my_widget_t*)win);
  my_window_manager_destroy(wm);
  my_pal_main_loop_destroy(loop);
  my_pal_destroy(pal);
}

TEST(menu_owned_callback_context_releases_after_manager_destroy)
{
  my_pal_t* pal = my_pal_dummy_create(NULL);
  my_pal_main_loop_t* loop = my_pal_main_loop_create(pal);
  my_window_manager_t* wm = my_window_manager_create(NULL, pal, loop);
  my_window_t* win = my_window_create(NULL, pal, 160, 100, "menu-owned-wm");
  my_menu_t* menu = my_menu_create(NULL);
  int context = 9;

  ASSERT_EQ(my_menu_add_item(menu, "item", 1), MY_RET_OK);
  ASSERT_EQ(my_window_manager_open(wm, win), MY_RET_OK);
  g_owned_callback_destroy_count = 0;
  ASSERT_EQ(my_menu_popup_owned(win, menu, 4, 4, owned_menu_callback,
                                &context, owned_callback_destroy), MY_RET_OK);
  my_window_manager_destroy(wm);
  ASSERT_EQ(g_owned_callback_destroy_count, 1);
  my_menu_destroy(menu);
  my_widget_unref((my_widget_t*)win);
  my_pal_main_loop_destroy(loop);
  my_pal_destroy(pal);
}

TEST(menu_owned_context_destroy_may_destroy_menu_and_window)
{
  my_pal_t* pal = my_pal_dummy_create(NULL);
  my_pal_main_loop_t* loop = my_pal_main_loop_create(pal);
  my_window_manager_t* wm = my_window_manager_create(NULL, pal, loop);
  my_window_t* win = my_window_create(NULL, pal, 160, 100, "menu-reentrant");
  my_menu_t* menu = my_menu_create(NULL);
  menu_reentrant_destroy_context_t context;

  ASSERT_NOT_NULL(wm);
  ASSERT_NOT_NULL(win);
  ASSERT_NOT_NULL(menu);
  context.menu = menu;
  context.window = win;
  context.destroy_count = 0;
  ASSERT_EQ(my_menu_add_item(menu, "item", 1), MY_RET_OK);
  ASSERT_EQ(my_window_manager_open(wm, win), MY_RET_OK);
  ASSERT_EQ(my_menu_popup_owned(win, menu, 4, 4, owned_menu_callback, &context,
                                menu_reentrant_destroy_context), MY_RET_OK);

  my_menu_dismiss(menu);
  ASSERT_EQ(context.destroy_count, 1);
  ASSERT_TRUE(context.menu == NULL);
  ASSERT_TRUE(context.window == NULL);

  my_window_manager_destroy(wm);
  my_pal_main_loop_destroy(loop);
  my_pal_destroy(pal);
}

TEST(dialog_owned_callback_context_releases_once)
{
  my_pal_t* pal = my_pal_dummy_create(NULL);
  my_pal_main_loop_t* loop = my_pal_main_loop_create(pal);
  my_window_manager_t* wm = my_window_manager_create(NULL, pal, loop);
  my_dialog_t* dialog = my_dialog_create(NULL, pal, "owned", 80, 60);
  int context = 11;

  ASSERT_NOT_NULL(dialog);
  g_owned_callback_calls = 0;
  g_owned_callback_destroy_count = 0;
  ASSERT_EQ(my_dialog_open_owned(dialog, wm, owned_dialog_callback, &context,
                                 owned_callback_destroy), MY_RET_OK);
  my_dialog_close(dialog, 1);
  ASSERT_EQ(g_owned_callback_calls, 1);
  ASSERT_EQ(g_owned_callback_destroy_count, 1);
  my_dialog_close(dialog, 2);
  ASSERT_EQ(g_owned_callback_destroy_count, 1);
  my_dialog_destroy(dialog);
  my_window_manager_destroy(wm);
  my_pal_main_loop_destroy(loop);
  my_pal_destroy(pal);
}

TEST(dialog_owned_callback_context_releases_on_manager_destroy)
{
  my_pal_t* pal = my_pal_dummy_create(NULL);
  my_pal_main_loop_t* loop = my_pal_main_loop_create(pal);
  my_window_manager_t* wm = my_window_manager_create(NULL, pal, loop);
  my_dialog_t* dialog = my_dialog_create(NULL, pal, "owned-wm", 80, 60);
  int context = 13;

  ASSERT_EQ(my_dialog_open_owned(dialog, wm, owned_dialog_callback, &context,
                                 owned_callback_destroy), MY_RET_OK);
  g_owned_callback_calls = 0;
  g_owned_callback_destroy_count = 0;
  my_window_manager_destroy(wm);
  ASSERT_EQ(g_owned_callback_calls, 0);
  ASSERT_EQ(g_owned_callback_destroy_count, 1);
  my_dialog_destroy(dialog);
  my_pal_main_loop_destroy(loop);
  my_pal_destroy(pal);
}

TEST(menu_callback_lease_rejects_invalid_registration)
{
  my_pal_t* pal = my_pal_dummy_create(NULL);
  my_window_t* win = my_window_create(NULL, pal, 160, 100, "menu-lease");
  my_menu_t* menu = my_menu_create(NULL);
  callback_lease_test_t state = {0};

  ASSERT_NOT_NULL(pal);
  ASSERT_NOT_NULL(win);
  ASSERT_NOT_NULL(menu);
  ASSERT_EQ(my_menu_add_item(menu, "item", 1), MY_RET_OK);
  state.lease = my_emitter_context_lease_create(
      NULL, &state, callback_lease_destroy);
  ASSERT_NOT_NULL(state.lease);
  my_emitter_context_lease_invalidate(state.lease);
  ASSERT_EQ(my_menu_popup_lease(win, menu, 4, 4,
                                menu_callback_lease_select, state.lease),
            MY_RET_INVALID_PARAMS);
  ASSERT_EQ(state.destroy_count, 0);
  my_emitter_context_lease_unref(state.lease);
  ASSERT_EQ(state.destroy_count, 1);

  my_menu_destroy(menu);
  my_widget_unref((my_widget_t*)win);
  my_pal_destroy(pal);
}

TEST(menu_callback_lease_skips_after_invalidation)
{
  my_pal_t* pal = my_pal_dummy_create(NULL);
  my_pal_main_loop_t* loop = my_pal_main_loop_create(pal);
  my_window_manager_t* wm = my_window_manager_create(NULL, pal, loop);
  my_window_t* win = my_window_create(NULL, pal, 160, 100, "menu-lease");
  my_menu_t* menu = my_menu_create(NULL);
  callback_lease_test_t state = {0};
  my_widget_t* overlay;
  my_widget_t* box;
  my_widget_t* item;
  my_event_t event;

  ASSERT_NOT_NULL(wm);
  ASSERT_NOT_NULL(win);
  ASSERT_NOT_NULL(menu);
  ASSERT_EQ(my_menu_add_item(menu, "item", 1), MY_RET_OK);
  state.lease = my_emitter_context_lease_create(
      NULL, &state, callback_lease_destroy);
  ASSERT_NOT_NULL(state.lease);
  ASSERT_EQ(my_window_manager_open(wm, win), MY_RET_OK);
  my_widget_unref((my_widget_t*)win);
  ASSERT_EQ(my_menu_popup_lease(win, menu, 4, 4,
                                menu_callback_lease_select, state.lease),
            MY_RET_OK);
  my_emitter_context_lease_invalidate(state.lease);
  my_emitter_context_lease_unref(state.lease);
  overlay = my_menu_widget(menu);
  box = my_widget_get_child(overlay, 0);
  item = my_widget_get_child(box, 0);
  event = my_event_init(MY_EVENT_POINTER_UP);
  ASSERT_EQ(item->vtable->on_event(item, &event), MY_RET_OK);
  ASSERT_EQ(state.callback_count, 0);
  ASSERT_EQ(state.destroy_count, 1);

  my_menu_destroy(menu);
  ASSERT_EQ(state.destroy_count, 1);
  my_window_manager_destroy(wm);
  my_pal_main_loop_destroy(loop);
  my_pal_destroy(pal);
}

TEST(menu_callback_lease_invalidates_during_callback)
{
  my_pal_t* pal = my_pal_dummy_create(NULL);
  my_pal_main_loop_t* loop = my_pal_main_loop_create(pal);
  my_window_manager_t* wm = my_window_manager_create(NULL, pal, loop);
  my_window_t* win = my_window_create(NULL, pal, 160, 100, "menu-lease");
  my_menu_t* menu = my_menu_create(NULL);
  callback_lease_test_t state = {0};
  my_widget_t* overlay;
  my_widget_t* box;
  my_widget_t* item;
  my_event_t event;

  ASSERT_NOT_NULL(wm);
  ASSERT_NOT_NULL(win);
  ASSERT_NOT_NULL(menu);
  ASSERT_EQ(my_menu_add_item(menu, "item", 1), MY_RET_OK);
  state.invalidate_in_callback = true;
  state.lease = my_emitter_context_lease_create(
      NULL, &state, callback_lease_destroy);
  ASSERT_NOT_NULL(state.lease);
  ASSERT_EQ(my_window_manager_open(wm, win), MY_RET_OK);
  my_widget_unref((my_widget_t*)win);
  ASSERT_EQ(my_menu_popup_lease(win, menu, 4, 4,
                                menu_callback_lease_select, state.lease),
            MY_RET_OK);
  my_emitter_context_lease_unref(state.lease);
  overlay = my_menu_widget(menu);
  box = my_widget_get_child(overlay, 0);
  item = my_widget_get_child(box, 0);
  event = my_event_init(MY_EVENT_POINTER_UP);
  ASSERT_EQ(item->vtable->on_event(item, &event), MY_RET_OK);
  ASSERT_EQ(state.callback_count, 1);
  ASSERT_EQ(state.destroy_count, 1);

  my_menu_destroy(menu);
  my_window_manager_destroy(wm);
  my_pal_main_loop_destroy(loop);
  my_pal_destroy(pal);
}

TEST(menu_callback_lease_releases_on_window_close)
{
  my_pal_t* pal = my_pal_dummy_create(NULL);
  my_pal_main_loop_t* loop = my_pal_main_loop_create(pal);
  my_window_manager_t* wm = my_window_manager_create(NULL, pal, loop);
  my_window_t* win = my_window_create(NULL, pal, 160, 100, "menu-lease");
  my_menu_t* menu = my_menu_create(NULL);
  callback_lease_test_t state = {0};

  ASSERT_NOT_NULL(wm);
  ASSERT_NOT_NULL(win);
  ASSERT_NOT_NULL(menu);
  ASSERT_EQ(my_menu_add_item(menu, "item", 1), MY_RET_OK);
  state.lease = my_emitter_context_lease_create(
      NULL, &state, callback_lease_destroy);
  ASSERT_NOT_NULL(state.lease);
  ASSERT_EQ(my_window_manager_open(wm, win), MY_RET_OK);
  my_widget_unref((my_widget_t*)win);
  ASSERT_EQ(my_menu_popup_lease(win, menu, 4, 4,
                                menu_callback_lease_select, state.lease),
            MY_RET_OK);
  my_emitter_context_lease_unref(state.lease);
  ASSERT_EQ(my_window_manager_close(wm, win), MY_RET_OK);
  ASSERT_EQ(state.callback_count, 0);
  ASSERT_EQ(state.destroy_count, 1);

  my_menu_destroy(menu);
  my_window_manager_destroy(wm);
  my_pal_main_loop_destroy(loop);
  my_pal_destroy(pal);
}

TEST(dialog_callback_lease_skips_after_invalidation)
{
  my_pal_t* pal = my_pal_dummy_create(NULL);
  my_pal_main_loop_t* loop = my_pal_main_loop_create(pal);
  my_window_manager_t* wm = my_window_manager_create(NULL, pal, loop);
  my_dialog_t* dialog = my_dialog_create(NULL, pal, "dialog-lease", 80, 60);
  callback_lease_test_t state = {0};

  ASSERT_NOT_NULL(dialog);
  state.lease = my_emitter_context_lease_create(
      NULL, &state, callback_lease_destroy);
  ASSERT_NOT_NULL(state.lease);
  ASSERT_EQ(my_dialog_open_lease(dialog, wm, dialog_callback_lease_result,
                                 state.lease), MY_RET_OK);
  my_emitter_context_lease_invalidate(state.lease);
  my_emitter_context_lease_unref(state.lease);
  my_dialog_close(dialog, 7);
  ASSERT_EQ(state.callback_count, 0);
  ASSERT_EQ(state.destroy_count, 1);

  my_dialog_destroy(dialog);
  ASSERT_EQ(state.destroy_count, 1);
  my_window_manager_destroy(wm);
  my_pal_main_loop_destroy(loop);
  my_pal_destroy(pal);
}

TEST(dialog_callback_lease_invalidates_during_callback)
{
  my_pal_t* pal = my_pal_dummy_create(NULL);
  my_pal_main_loop_t* loop = my_pal_main_loop_create(pal);
  my_window_manager_t* wm = my_window_manager_create(NULL, pal, loop);
  my_dialog_t* dialog = my_dialog_create(NULL, pal, "dialog-lease", 80, 60);
  callback_lease_test_t state = {0};

  ASSERT_NOT_NULL(dialog);
  state.invalidate_in_callback = true;
  state.lease = my_emitter_context_lease_create(
      NULL, &state, callback_lease_destroy);
  ASSERT_NOT_NULL(state.lease);
  ASSERT_EQ(my_dialog_open_lease(dialog, wm, dialog_callback_lease_result,
                                 state.lease), MY_RET_OK);
  my_emitter_context_lease_unref(state.lease);
  my_dialog_close(dialog, 8);
  ASSERT_EQ(state.callback_count, 1);
  ASSERT_EQ(state.destroy_count, 1);

  my_dialog_destroy(dialog);
  my_window_manager_destroy(wm);
  my_pal_main_loop_destroy(loop);
  my_pal_destroy(pal);
}

TEST(dialog_callback_lease_releases_on_manager_destroy)
{
  my_pal_t* pal = my_pal_dummy_create(NULL);
  my_pal_main_loop_t* loop = my_pal_main_loop_create(pal);
  my_window_manager_t* wm = my_window_manager_create(NULL, pal, loop);
  my_dialog_t* dialog = my_dialog_create(NULL, pal, "dialog-lease", 80, 60);
  callback_lease_test_t state = {0};

  ASSERT_NOT_NULL(dialog);
  state.lease = my_emitter_context_lease_create(
      NULL, &state, callback_lease_destroy);
  ASSERT_NOT_NULL(state.lease);
  ASSERT_EQ(my_dialog_open_lease(dialog, wm, dialog_callback_lease_result,
                                 state.lease), MY_RET_OK);
  my_emitter_context_lease_unref(state.lease);
  my_window_manager_destroy(wm);
  ASSERT_EQ(state.callback_count, 0);
  ASSERT_EQ(state.destroy_count, 1);

  my_dialog_destroy(dialog);
  my_pal_main_loop_destroy(loop);
  my_pal_destroy(pal);
}

TEST(menu_popup_clamps_extreme_coordinates)
{
  my_pal_t *pal = my_pal_dummy_create(NULL);
  my_pal_main_loop_t *loop = my_pal_main_loop_create(pal);
  my_window_manager_t *wm = my_window_manager_create(NULL, pal, loop);
  my_window_t *win = my_window_create(NULL, pal, 400, 300, "main");
  my_menu_t *menu = my_menu_create(NULL);
  my_widget_t *overlay;
  my_widget_t *box;

  ASSERT_EQ(my_menu_add_item(menu, "item", 1), MY_RET_OK);
  ASSERT_EQ(my_window_manager_open(wm, win), MY_RET_OK);
  my_widget_unref((my_widget_t *)win);
  ASSERT_EQ(my_menu_popup(win, menu, INT32_MAX, INT32_MAX, NULL, NULL),
            MY_RET_OK);
  overlay = my_menu_widget(menu);
  ASSERT_NOT_NULL(overlay);
  box = my_widget_get_child(overlay, 0);
  ASSERT_NOT_NULL(box);
  ASSERT_TRUE(box->rect.x >= 0 && box->rect.x < 400);
  ASSERT_TRUE(box->rect.y >= 0 && box->rect.y < 300);

  my_menu_dismiss(menu);
  my_menu_destroy(menu);
  my_window_manager_destroy(wm);
  my_pal_main_loop_destroy(loop);
  my_pal_destroy(pal);
}

TEST(menu_destroyed_submenu_detaches_from_parent)
{
  my_menu_t* menu = my_menu_create(NULL);
  my_menu_t* sub;

  ASSERT_NOT_NULL(menu);
  sub = my_menu_add_submenu(menu, "more");
  ASSERT_NOT_NULL(sub);
  ASSERT_EQ(my_menu_add_item(sub, "child", 2), MY_RET_OK);

  /* The public child handle may be released independently. The parent must
   * not retain a freed submenu when it is later used or destroyed. */
  my_menu_destroy(sub);
  ASSERT_EQ(my_menu_max_depth(menu), 3);
  my_menu_destroy(menu);
}

TEST(menu_destroyed_open_submenu_invalidates_parent_popup)
{
  my_pal_t* pal = my_pal_dummy_create(NULL);
  my_pal_main_loop_t* loop = my_pal_main_loop_create(pal);
  my_window_manager_t* wm = my_window_manager_create(NULL, pal, loop);
  my_window_t* win = my_window_create(NULL, pal, 160, 100, "main");
  my_menu_t* menu = my_menu_create(NULL);
  my_menu_t* sub;

  ASSERT_NOT_NULL(wm);
  ASSERT_NOT_NULL(win);
  ASSERT_NOT_NULL(menu);
  sub = my_menu_add_submenu(menu, "more");
  ASSERT_NOT_NULL(sub);
  ASSERT_EQ(my_menu_add_item(sub, "child", 2), MY_RET_OK);
  ASSERT_EQ(my_window_manager_open(wm, win), MY_RET_OK);
  my_widget_unref((my_widget_t*)win);
  ASSERT_EQ(my_menu_popup(win, menu, 4, 4, NULL, NULL), MY_RET_OK);
  ASSERT_NOT_NULL(my_menu_widget(menu));

  my_menu_destroy(sub);
  ASSERT_TRUE(my_menu_widget(menu) == NULL);
  ASSERT_EQ(my_menu_popup(win, menu, 4, 4, NULL, NULL), MY_RET_FAIL);

  my_menu_destroy(menu);
  my_window_manager_destroy(wm);
  my_pal_main_loop_destroy(loop);
  my_pal_destroy(pal);
}

TEST(window_destroy_with_open_menu_submenu_detaches_parent_chain)
{
  my_pal_t* pal = my_pal_dummy_create(NULL);
  my_pal_main_loop_t* loop = my_pal_main_loop_create(pal);
  my_window_manager_t* wm = my_window_manager_create(NULL, pal, loop);
  my_window_t* win = my_window_create(NULL, pal, 240, 140, "menu-cascade");
  my_menu_t* menu = my_menu_create(NULL);
  my_menu_t* sub = NULL;
  my_widget_t* overlay = NULL;
  my_widget_t* box = NULL;
  my_widget_t* item = NULL;
  my_event_t event;

  ASSERT_NOT_NULL(wm);
  ASSERT_NOT_NULL(win);
  ASSERT_NOT_NULL(menu);
  ASSERT_EQ(my_menu_add_item(menu, "leaf", 1), MY_RET_OK);
  sub = my_menu_add_submenu(menu, "more");
  ASSERT_NOT_NULL(sub);
  ASSERT_EQ(my_menu_add_item(sub, "child", 2), MY_RET_OK);
  ASSERT_EQ(my_window_manager_open(wm, win), MY_RET_OK);
  ASSERT_EQ(my_menu_popup(win, menu, 4, 4, NULL, NULL), MY_RET_OK);

  overlay = my_menu_widget(menu);
  box = my_widget_get_child(overlay, 0);
  item = my_widget_get_child(box, 1);
  ASSERT_NOT_NULL(item);
  event = my_event_init(MY_EVENT_POINTER_UP);
  ASSERT_EQ(item->vtable->on_event(item, &event), MY_RET_OK);
  ASSERT_NOT_NULL(my_menu_widget(sub));

  ASSERT_EQ(my_window_manager_close(wm, win), MY_RET_OK);
  ASSERT_TRUE(my_menu_widget(menu) == NULL);
  ASSERT_TRUE(my_menu_widget(sub) == NULL);

  my_menu_destroy(menu);
  my_window_manager_destroy(wm);
  my_widget_unref((my_widget_t*)win);
  my_pal_main_loop_destroy(loop);
  my_pal_destroy(pal);
}

TEST(node_auto_size_saturates_extreme_child_extent)
{
  my_widget_t *node = my_node_create(NULL, NULL, "node", "node", "cat");
  my_widget_t *child = my_label_create(NULL, "child");

  ASSERT_NOT_NULL(node);
  ASSERT_NOT_NULL(child);
  ASSERT_EQ(my_widget_set_rect(child,
                               &(my_rect_t){INT32_MAX - 4, 0, 10, 10}),
            MY_RET_OK);
  ASSERT_EQ(my_widget_add_child(node, child), MY_RET_OK);
  my_widget_unref(child);
  my_node_set_auto_size(node, true, false);
  my_node_auto_size(node);
  ASSERT_EQ(node->rect.w, INT32_MAX);

  my_widget_unref(node);
}

TEST(node_socket_center_does_not_wrap_extreme_rect)
{
  my_widget_t *node = my_node_create(NULL, NULL, "node", "node", "cat");
  int32_t x = 0;
  int32_t y = 0;

  ASSERT_NOT_NULL(node);
  ASSERT_EQ(my_widget_set_rect(node,
                               &(my_rect_t){INT32_MAX - 2, INT32_MAX - 2,
                                            10, 10}),
            MY_RET_OK);
  ASSERT_EQ(my_node_add_socket(node, MY_SOCKET_OUT, "out", 0u), MY_RET_OK);
  ASSERT_TRUE(my_node_socket_center(node, MY_SOCKET_OUT, 0, &x, &y));
  ASSERT_EQ(x, INT32_MAX);
  ASSERT_EQ(y, INT32_MAX);
  my_widget_unref(node);
}

TEST(node_socket_hit_distance_does_not_wrap)
{
  my_widget_t *view = my_node_view_create(NULL);
  my_widget_t *node;
  my_event_t event;

  ASSERT_NOT_NULL(view);
  ASSERT_EQ(my_widget_set_rect(view, &(my_rect_t){0, 0, 100, 100}),
            MY_RET_OK);
  node = my_node_view_add_node(view, "edge", "edge", "cat",
                               INT32_MIN, INT32_MIN, 40, 40);
  ASSERT_NOT_NULL(node);
  ASSERT_EQ(my_node_add_socket(node, MY_SOCKET_IN, "in", 0u), MY_RET_OK);
  event = my_event_init(MY_EVENT_POINTER_DOWN);
  event.u.pointer.x = INT32_MIN;
  event.u.pointer.y = INT32_MIN + MY_NODE_HEADER_H + MY_NODE_ROW_H / 2;
  event.u.pointer.button = 1;
  ASSERT_EQ(view->vtable->on_event(view, &event), MY_RET_OK);
  my_widget_unref(view);
}

TEST_MAIN_BEGIN()
    RUN_TEST(ui_command_runs_on_manager_loop_and_survives_window_close);
    RUN_TEST(ui_command_destroyed_with_manager_does_not_execute);
    RUN_TEST(ui_command_does_not_require_an_open_window);
    RUN_TEST(ui_command_scope_closes_with_window);
    RUN_TEST(ui_command_scope_reopens_with_window);
    RUN_TEST(ui_command_scope_closes_with_manager);
    RUN_TEST(ui_command_scope_keeps_sibling_commands_alive);
    RUN_TEST(injected_canvas_inherits_window_scale);
    RUN_TEST(window_record_dirty_reports_damage_in_owner_frame);
    RUN_TEST(dynamic_scale_reconfigures_injected_canvas_without_resize);
    RUN_TEST(floating_plain_widget_does_not_crash_hit_test);
    RUN_TEST(text_area_grows_capacity_exponentially);
    RUN_TEST(text_area_wrap_rebuilds_after_edit);
    RUN_TEST(text_area_visual_lines_cache_byte_ranges);
    RUN_TEST(text_area_visual_line_index_cache_tracks_folds_and_edits);
    RUN_TEST(text_area_visual_line_index_cache_oom_falls_back);
    RUN_TEST(text_area_geometry_cache_reuses_glyph_advances);
    RUN_TEST(text_area_geometry_saturates_huge_glyph_advances);
    RUN_TEST(edit_insert_oom_is_transactional);
    RUN_TEST(edit_paint_uses_measurement_font);
    RUN_TEST(edit_geometry_saturates_huge_font);
    RUN_TEST(edit_password_oom_preserves_previous_mask);
    RUN_TEST(edit_password_delete_oom_is_transactional);
    RUN_TEST(edit_password_toggle_oom_preserves_state);
    RUN_TEST(edit_delete_oom_does_not_record_history);
    RUN_TEST(edit_selection_replace_undo_restores_deleted_text);
    RUN_TEST(undo_stack_rejects_size_overflow_and_terminates_delete_batches);
    RUN_TEST(undo_stack_record_oom_preserves_redo_branch);
    RUN_TEST(undo_stack_capacity_oom_preserves_oldest_entry);
    RUN_TEST(undo_stack_peek_commit_is_transactional);
    RUN_TEST(shared_undo_registration_oom_keeps_widgets_private);
    RUN_TEST(text_area_selection_replace_undo_restores_deleted_text);
    RUN_TEST(text_area_selection_replace_over_max_len_preserves_document);
    RUN_TEST(text_area_insert_reserve_oom_does_not_record_history);
    RUN_TEST(text_area_selection_replace_reserve_oom_is_transactional);
    RUN_TEST(text_area_delete_history_oom_preserves_document);
    RUN_TEST(text_area_set_text_oom_preserves_history);
    RUN_TEST(text_area_line_cache_handles_unicode_hard_breaks);
    RUN_TEST(text_area_rejects_corrupt_visual_line_slice);
    RUN_TEST(text_area_visual_line_query_rejects_out_of_range_index);
    RUN_TEST(text_area_shaping_params_are_owned_and_validated);
    RUN_TEST(text_area_shaping_params_normalize_without_revision_churn);
    RUN_TEST(text_area_rtl_paint_reuses_layout);
    RUN_TEST(text_area_rtl_hit_test_reuses_layout);
    RUN_TEST(text_area_rtl_paint_caches_multiple_visual_lines);
    RUN_TEST(text_area_rtl_syntax_colors_tokens);
    RUN_TEST(text_area_wrap_reuses_unchanged_prefix_after_edit);
    RUN_TEST(text_area_wrap_reuses_unchanged_suffix_after_single_line_edit);
    RUN_TEST(text_area_wrap_reuses_suffix_after_newline_edit);
    RUN_TEST(text_area_wrap_reuses_suffix_after_newline_delete);
    RUN_TEST(text_area_wrap_reuses_suffix_after_multibyte_edit);
    RUN_TEST(text_area_wrap_dirty_cache_disables_suffix_reuse);
    RUN_TEST(text_area_wrap_suffix_reuse_oom_preserves_old_objects);
    RUN_TEST(text_area_wrap_single_line_edit_shapes_only_changed_row);
    RUN_TEST(text_area_wrap_preserves_trailing_empty_line_on_single_line_edit);
    RUN_TEST(text_area_wrap_represents_empty_document_as_empty_visual_line);
    RUN_TEST(text_area_wrap_keeps_all_consecutive_empty_physical_lines);
    RUN_TEST(text_area_wrap_last_line_edit_does_not_retain_stale_visual_lines);
    RUN_TEST(text_area_wrap_cross_line_delete_rebuilds_physical_rows);
    RUN_TEST(text_area_wrap_rebuilds_dirty_suffix_as_one_paragraph);
    RUN_TEST(text_area_wrap_suffix_oom_releases_candidate_lines);
    RUN_TEST(text_area_line_number_gutter_has_bounded_width);
    RUN_TEST(text_area_line_numbers_reduce_wrap_width);
    RUN_TEST(text_area_folded_range_hides_only_inner_physical_lines);
    RUN_TEST(text_area_folded_range_rejects_invalid_or_overlapping_ranges);
    RUN_TEST(text_area_nested_fold_ranges_preserve_containment);
    RUN_TEST(text_area_fold_state_yaml_roundtrip_and_transaction);
    RUN_TEST(text_area_many_nested_folds_build_visible_rows_once);
    RUN_TEST(text_area_folded_range_rebuilds_wrapped_visual_lines);
    RUN_TEST(text_area_wrap_oom_keeps_previous_cache);
    RUN_TEST(text_area_folded_rows_remain_hidden_when_visible_cache_ooms);
    RUN_TEST(text_area_justify_cursor_tracks_stretched_space);
    RUN_TEST(text_area_justify_cursor_tracks_unicode_breaking_space);
    RUN_TEST(text_area_syntax_is_lazy_and_budgeted);
    RUN_TEST(text_area_syntax_replacement_invalidates_tokens);
    RUN_TEST(text_area_syntax_key_edit_invalidates_suffix);
    RUN_TEST(window_manager_refreshes_all_window_scales);
    RUN_TEST(gpu_backend_request_reports_actual_state);
    RUN_TEST(software_canvas_recreates_after_surface_resize);
    RUN_TEST(window_css_media_reloads_on_logical_resize);
    RUN_TEST(window_css_style_failure_preserves_active_theme);
    RUN_TEST(window_css_media_refreshes_only_after_platform_fact_change);
    RUN_TEST(window_css_media_refresh_failure_is_retryable);
    RUN_TEST(window_snapshot_keeps_removed_window_alive);
    RUN_TEST(closed_window_detaches_manager_borrowed_state);
    RUN_TEST(paint_stack_mutation_stops_current_frame);
    RUN_TEST(on_open_hook_fires_once_per_open);
    RUN_TEST(on_open_lease_skips_invalidated_context_and_releases_on_destroy);
    RUN_TEST(on_open_lease_replacement_releases_old_context_once);
    RUN_TEST(on_open_owned_context_releases_on_replacement_and_destroy);
    RUN_TEST(on_open_owned_context_replacement_defers_destroy_until_callback_returns);
    RUN_TEST(on_open_owned_context_destroy_defers_manager_teardown);
    RUN_TEST(dialog_lifecycle_and_modal_blocking);
    RUN_TEST(window_manager_rejects_duplicate_window_open);
    RUN_TEST(window_manager_destroy_listener_reentry_is_guarded);
    RUN_TEST(dialog_rejects_duplicate_open_without_state_corruption);
    RUN_TEST(dialog_detaches_when_window_manager_is_destroyed_first);
    RUN_TEST(dialog_detaches_when_window_is_closed_directly);
    RUN_TEST(dialog_owned_callback_context_releases_once);
    RUN_TEST(dialog_owned_callback_context_releases_on_manager_destroy);
    RUN_TEST(dialog_callback_lease_skips_after_invalidation);
    RUN_TEST(dialog_callback_lease_invalidates_during_callback);
    RUN_TEST(dialog_callback_lease_releases_on_manager_destroy);
    RUN_TEST(shared_surface_routes_input_to_modal);
    RUN_TEST(shared_surface_routes_keyboard_to_pointer_window);
    RUN_TEST(timer_deadline_saturates_at_clock_limit);
    RUN_TEST(timer_periodic_deadline_at_clock_limit_does_not_busy_loop);
    RUN_TEST(timer_rejects_zero_interval);
    RUN_TEST(timer_due_in_saturates_after_clock_rollback);
    RUN_TEST(timer_heap_preserves_safe_callback_mutation);
    RUN_TEST(timer_heap_removes_inactive_non_root_without_losing_order);
    RUN_TEST(timer_remove_releases_each_entry_once);
    RUN_TEST(timer_nested_fire_can_remove_outer_current_timer);
    RUN_TEST(timer_manager_destroy_from_callback_defers_free_and_stops_fire);
    RUN_TEST(timer_lease_skips_invalidated_context_and_releases_once);
    RUN_TEST(timer_lease_callback_can_invalidate_and_keep_running);
    RUN_TEST(timer_lease_context_destroy_cannot_reenter_manager_dispose);
    RUN_TEST(timer_lease_cleanup_destroy_stops_sibling_timers);
    RUN_TEST(emitter_destroy_from_callback_defers_free_and_stops_emit);
    RUN_TEST(emitter_owned_context_releases_once_on_off_and_destroy);
    RUN_TEST(emitter_owned_context_off_allows_reentrant_destroy);
    RUN_TEST(emitter_context_lease_invalidates_borrowed_callback_safely);
    RUN_TEST(emitter_context_lease_rejects_invalid_registration_without_transfer);
    RUN_TEST(widget_context_lease_forwards_to_widget_emitter);
    RUN_TEST(window_close_context_lease_invalidates_before_context_teardown);
    RUN_TEST(window_manager_destroy_context_lease_skips_after_invalidation);
    RUN_TEST(emitter_listener_id_wrap_skips_zero_and_live_ids);
    RUN_TEST(timer_fire_does_not_allocate_deferred_storage);
    RUN_TEST(timer_pending_heap_oom_preserves_added_timer);
    RUN_TEST(timer_index_keeps_pending_removal_and_heap_order);
    RUN_TEST(timer_index_skips_active_ids_after_wrap);
    RUN_TEST(animator_delay_saturates_without_early_completion);
    RUN_TEST(animator_reentrant_stop_defers_record_sweep);
    RUN_TEST(animator_manager_destroy_from_callback_is_deferred);
    RUN_TEST(undo_manager_destroy_keeps_shared_edit_safe);
    RUN_TEST(undo_manager_window_reference_survives_owner_destroy);
    RUN_TEST(edit_blink_timer_does_not_keep_dangling_widget_context);
    RUN_TEST(window_manager_destroy_from_paint_is_deferred);
    RUN_TEST(window_manager_destroy_from_event_is_deferred);
    RUN_TEST(window_manager_destroy_from_close_listener_is_deferred);
    RUN_TEST(window_close_owned_listener_releases_once_on_remove_and_close);
    RUN_TEST(window_manager_owned_destroy_listener_releases_once);
    RUN_TEST(owned_listener_destructor_can_destroy_owner_during_remove);
    RUN_TEST(window_manager_destroy_from_open_callback_is_deferred);
    RUN_TEST(edit_async_paste_changed_listener_can_remove_self);
    RUN_TEST(text_area_async_paste_changed_listener_can_remove_self);
    RUN_TEST(edit_typed_changed_listener_can_remove_self);
    RUN_TEST(text_area_typed_changed_listener_can_remove_self);
    RUN_TEST(button_click_listener_can_remove_self_before_post_emit_invalidate);
    RUN_TEST(node_view_changed_listener_can_remove_self);
    RUN_TEST(checkbox_changed_listener_can_remove_self);
    RUN_TEST(slider_changed_listener_can_remove_self);
    RUN_TEST(scroll_bar_changed_listener_can_remove_self);
    RUN_TEST(button_cooldown_blocks_reentry_and_exposes_progress);
    RUN_TEST(scroll_containers_unlink_scroll_bar_before_destroy);
    RUN_TEST(scroll_containers_reject_non_scroll_bar_without_rebinding);
    RUN_TEST(scroll_containers_keep_linked_scroll_bar_alive);
    RUN_TEST(widget_specific_setters_reject_plain_widget);
    RUN_TEST(image_cache_is_loader_scoped_and_respects_loader_ownership);
    RUN_TEST(image_loader_with_invalid_vtable_or_data_fails_safely);
    RUN_TEST(image_loader_lease_releases_once_when_widget_and_cache_drop_references);
    RUN_TEST(myui_ref_count_rejects_overflow_without_wrapping);
    RUN_TEST(image_borrowed_loader_uses_transient_data_without_cache_retention);
    RUN_TEST(widget_specific_queries_reject_plain_widget);
    RUN_TEST(scroll_view_opaque_api_rejects_plain_widget);
    RUN_TEST(scroll_view_set_content_failure_preserves_previous_content);
    RUN_TEST(scroll_view_direct_content_removal_clears_borrowed_state);
    RUN_TEST(list_view_rejects_invalid_adapter_and_saturates_extreme_heights);
    RUN_TEST(list_view_pool_oom_releases_recycle_reference);
    RUN_TEST(list_view_rejects_adapter_reentry_during_sync);
    RUN_TEST(list_view_adapter_lease_preserves_lifetime_and_failed_install);
    RUN_TEST(node_view_rejects_foreign_nodes_and_invalid_sockets);
    RUN_TEST(button_cooldown_zero_disables_without_timer);
    RUN_TEST(button_keyboard_activation_is_single_shot_and_cooldown_safe);
    RUN_TEST(button_keyboard_activation_clears_on_focus_loss);
    RUN_TEST(button_api_rejects_non_button_widgets);
    RUN_TEST(button_cooldown_timer_tracks_deadline_and_stops);
    RUN_TEST(button_cooldown_respects_reduced_motion_uses_completion_timer);
    RUN_TEST(button_cooldown_remaining_samples_clock_once);
    RUN_TEST(button_cooldown_paint_samples_clock_once);
    RUN_TEST(button_release_preserves_minimum_press_after_clock_rollback);
    RUN_TEST(button_cooldown_remains_active_at_clock_upper_bound);
    RUN_TEST(button_release_timer_failure_does_not_stick_pressed_state);
    RUN_TEST(surface_resize_preserves_and_recenters_dialog);
    RUN_TEST(back_to_home_clears_window_links_and_scrim);
    RUN_TEST(auto_paint_toggle_removes_timer);
    RUN_TEST(posted_user_event_reaches_top_window);
    RUN_TEST(user_event_can_close_window_during_dispatch);
    RUN_TEST(text_widgets_toggle_platform_ime_with_focus);
    RUN_TEST(text_area_variable_font_keeps_nonwrap_coordinates_consistent);
    RUN_TEST(text_area_nonwrap_hit_test_uses_shaping_clusters);
    RUN_TEST(text_area_pointer_hit_test_clamps_vertical_bounds);
    RUN_TEST(text_area_pointer_hit_test_uses_font_line_height);
    RUN_TEST(text_area_page_down_moves_by_wrapped_visual_lines);
    RUN_TEST(text_area_page_up_moves_by_wrapped_visual_lines);
    RUN_TEST(text_area_paint_reuses_line_buffer);
    RUN_TEST(text_area_justify_paint_reuses_line_buffer);
    RUN_TEST(text_area_ime_spot_tracks_wrapped_justify_cursor);
#ifdef MYUI_BIDI
    RUN_TEST(text_area_wrap_rtl_horizontal_crosses_visual_lines);
    RUN_TEST(text_area_wrap_rtl_horizontal_crosses_physical_lines);
    RUN_TEST(text_area_rtl_navigation_state_invalidates_after_text_replace);
    RUN_TEST(text_area_nonwrap_rtl_ime_spot_uses_visual_boundary);
    RUN_TEST(text_area_wrap_rtl_ime_spot_uses_visual_boundary);
    RUN_TEST(text_area_wrap_rtl_justify_cursor_tracks_stretched_space);
    RUN_TEST(text_area_rtl_justify_selection_uses_stretched_visual_rect);
    RUN_TEST(text_area_nonwrap_rtl_geometry_keeps_logical_boundaries);
    RUN_TEST(text_area_nonwrap_rtl_geometry_works_without_shaping);
#endif
    RUN_TEST(removing_focused_widget_blurs_and_disables_ime);
    RUN_TEST(removing_hovered_grabbed_widget_resets_dispatch_state);
    RUN_TEST(event_bubbling_stops_at_removed_ancestor);
    RUN_TEST(event_bubbling_stops_at_self_removed_leaf);
    RUN_TEST(text_widgets_apply_ime_delete_surrounding);
    RUN_TEST(text_widgets_paste_full_clipboard_without_fixed_buffer_limit);
    RUN_TEST(window_close_cancels_node_view_flow_timer);
    RUN_TEST(node_view_remove_node_cancels_magnet_preview);
    RUN_TEST(node_view_remove_node_clears_embedded_child_grab);
    RUN_TEST(node_view_generic_child_removal_clears_weak_state);
    RUN_TEST(node_view_destroy_detaches_externally_held_nodes);
    RUN_TEST(blur_handler_can_move_focus_to_another_widget);
    RUN_TEST(blur_handler_can_destroy_the_old_focused_widget);
    RUN_TEST(window_close_invalidates_open_menu);
    RUN_TEST(window_close_invalidates_menu_with_external_window_ref);
    RUN_TEST(menu_detaches_when_window_manager_is_destroyed_first);
    RUN_TEST(menu_owned_callback_context_releases_once);
    RUN_TEST(menu_owned_callback_context_releases_after_manager_destroy);
    RUN_TEST(menu_owned_context_destroy_may_destroy_menu_and_window);
    RUN_TEST(menu_callback_lease_rejects_invalid_registration);
    RUN_TEST(menu_callback_lease_skips_after_invalidation);
    RUN_TEST(menu_callback_lease_invalidates_during_callback);
    RUN_TEST(menu_callback_lease_releases_on_window_close);
    RUN_TEST(menu_popup_clamps_extreme_coordinates);
    RUN_TEST(menu_destroyed_submenu_detaches_from_parent);
    RUN_TEST(menu_destroyed_open_submenu_invalidates_parent_popup);
    RUN_TEST(window_destroy_with_open_menu_submenu_detaches_parent_chain);
    RUN_TEST(node_auto_size_saturates_extreme_child_extent);
    RUN_TEST(node_socket_center_does_not_wrap_extreme_rect);
    RUN_TEST(node_socket_hit_distance_does_not_wrap);
TEST_MAIN_END()
