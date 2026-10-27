#include "mypal/screen/my_pal_screen.h"
#include "myui/my_ui_command_internal.h"
#include "myr/my_lcd_mem.h"
#include "myc/my_str.h"
#include <platform/time.h>
#include <screen/screen.h>
#include <sys/keycodes.h>
#include <errno.h>
#include <limits.h>
#include <stdatomic.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>

#define SCREEN_WAKE_COOKIE 0x51554e58

typedef struct my_screen_window_t my_screen_window_t;

typedef struct my_screen_pal_t {
  my_pal_t base;
  const my_allocator_t* allocator;
  screen_context_t context;
  screen_event_t event;
  screen_event_t wake_event;
  my_pal_event_handler_t handler;
  void* handler_ctx;
  my_screen_window_t* windows;
} my_screen_pal_t;

struct my_screen_window_t {
  my_pal_window_t base;
  my_screen_pal_t* pal;
  screen_window_t native;
  struct my_screen_lcd_t* lcd;
  my_screen_window_t* next;
  int32_t width;
  int32_t height;
  char* title;
  uint32_t native_depth;
  uint32_t buttons;
  int32_t pointer_x;
  int32_t pointer_y;
  bool has_pointer_position;
  bool buffer_replace_failed;
  bool destroy_requested;
};

#define SCREEN_BUFFER_SLOT_COUNT 2u

typedef struct my_screen_buffer_slot_t {
  screen_buffer_t buffer;
  my_lcd_t* mem;
} my_screen_buffer_slot_t;

typedef struct my_screen_lcd_t {
  my_lcd_t base;
  my_screen_window_t* window;
  my_lcd_t* mem;
  screen_buffer_t buffer;
  my_screen_buffer_slot_t slots[SCREEN_BUFFER_SLOT_COUNT];
  uint8_t* shadow;
  uint32_t post_count;
  bool buffer_acquired;
  bool restore_required;
  bool in_frame;
  bool has_dirty;
  my_rect_t dirty;
  bool has_unposted;
  my_rect_t unposted;
} my_screen_lcd_t;

static bool screen_size_supported(int32_t width, int32_t height) {
  return width > 0 && height > 0 && width <= INT32_MAX / 4 &&
         (size_t)(uint32_t)height <=
             SIZE_MAX / ((size_t)(uint32_t)width * 4u);
}

typedef struct my_screen_event_t {
  my_event_t event;
  char* ime_text;
  struct my_screen_event_t* next;
} my_screen_event_t;

typedef struct my_screen_loop_t {
  my_pal_main_loop_t base;
  my_screen_pal_t* pal;
  my_screen_event_t* head;
  my_screen_event_t* tail;
  atomic_flag event_lock;
  bool wake_pending;
  atomic_bool accepting_events;
  atomic_bool quit;
  bool running;
  bool destroy_requested;
  my_timer_manager_t* timers;
} my_screen_loop_t;

static const my_pal_window_vtable_t s_window_vtable;
static const my_pal_main_loop_vtable_t s_loop_vtable;
static const my_pal_vtable_t s_pal_vtable;

static uint64_t screen_now_ms(void* context) {
  (void)context;
  return time_microseconds() / 1000u;
}

static void screen_window_link(my_screen_window_t* w) {
  w->next = w->pal->windows;
  w->pal->windows = w;
}

static void screen_window_unlink(my_screen_window_t* w) {
  my_screen_window_t** it = &w->pal->windows;
  while (*it != NULL) {
    if (*it == w) {
      *it = w->next;
      w->next = NULL;
      return;
    }
    it = &(*it)->next;
  }
}

static my_screen_window_t* screen_window_find(my_screen_pal_t* pal,
                                               screen_window_t native) {
  my_screen_window_t* w;
  for (w = pal->windows; w != NULL; w = w->next) {
    if (w->native == native) return w;
  }
  return NULL;
}

static my_rect_t screen_lcd_bounds(const my_screen_lcd_t* x) {
  return my_rect_init(0, 0, x->window->width, x->window->height);
}

static void screen_copy_rect(uint8_t* dst, uint32_t dst_stride,
                             const uint8_t* src, uint32_t src_stride,
                             const my_rect_t* rect) {
  int32_t row;
  size_t bytes = (size_t)(uint32_t)rect->w * 4u;
  for (row = 0; row < rect->h; ++row) {
    size_t y = (size_t)(uint32_t)rect->y + (size_t)(uint32_t)row;
    size_t x_offset = (size_t)(uint32_t)rect->x * 4u;
    memcpy(dst + y * dst_stride + x_offset,
           src + y * src_stride + x_offset, bytes);
  }
}

static void screen_lcd_release_buffers(my_screen_lcd_t* x) {
  uint32_t i;
  if (x->buffer_acquired) (void)screen_enqueue_render_buffer(x->buffer);
  for (i = 0u; i < SCREEN_BUFFER_SLOT_COUNT; ++i) {
    if (x->slots[i].mem != NULL) my_lcd_destroy(x->slots[i].mem);
  }
  memset(x->slots, 0, sizeof(x->slots));
  my_mem_free(x->window->pal->allocator, x->shadow);
  x->shadow = NULL;
  x->mem = NULL;
  x->buffer = NULL;
  x->buffer_acquired = false;
  x->restore_required = false;
  x->in_frame = false;
  x->has_dirty = false;
  x->has_unposted = false;
}

static void screen_lcd_destroy(my_lcd_t* lcd) {
  my_screen_lcd_t* x = (my_screen_lcd_t*)lcd;
  screen_lcd_release_buffers(x);
  my_mem_free(x->window->pal->allocator, x);
}

static uint32_t screen_lcd_width(my_lcd_t* lcd) {
  my_screen_lcd_t* x = (my_screen_lcd_t*)lcd;
  return x->mem != NULL ? my_lcd_get_width(x->mem) : 0u;
}

static uint32_t screen_lcd_height(my_lcd_t* lcd) {
  my_screen_lcd_t* x = (my_screen_lcd_t*)lcd;
  return x->mem != NULL ? my_lcd_get_height(x->mem) : 0u;
}

static my_pixel_format_t screen_lcd_format(my_lcd_t* lcd) {
  my_screen_lcd_t* x = (my_screen_lcd_t*)lcd;
  return x->mem != NULL ? my_lcd_get_format(x->mem)
                                   : (my_pixel_format_t)-1;
}

static my_ret_t screen_lcd_restore(my_screen_lcd_t* x) {
  my_rect_t bounds = screen_lcd_bounds(x);
  uint8_t* pixels;
  uint32_t stride;
  if (x->mem == NULL || x->shadow == NULL) return MY_RET_FAIL;
  pixels = my_lcd_get_buffer(x->mem);
  stride = my_lcd_get_stride(x->mem);
  if (pixels == NULL || stride < (uint32_t)x->window->width * 4u) {
    return MY_RET_FAIL;
  }
  screen_copy_rect(pixels, stride, x->shadow,
                   (uint32_t)x->window->width * 4u, &bounds);
  return MY_RET_OK;
}

static my_rect_t screen_lcd_frame_damage(const my_screen_lcd_t* x) {
  my_rect_t bounds = screen_lcd_bounds(x);
  my_rect_t damage;
  if (!x->has_dirty ||
      !my_rect_intersect(&x->dirty, &bounds, &damage)) {
    damage = bounds;
  }
  if (x->has_unposted) my_rect_union(&damage, &x->unposted, &damage);
  return damage;
}

static my_ret_t screen_lcd_capture(my_screen_lcd_t* x,
                                   const my_rect_t* damage) {
  my_rect_t bounds = screen_lcd_bounds(x);
  my_rect_t clipped;
  uint8_t* pixels;
  uint32_t stride;
  if (x->mem == NULL || x->shadow == NULL) return MY_RET_FAIL;
  if (!my_rect_intersect(damage, &bounds, &clipped)) return MY_RET_FAIL;
  pixels = my_lcd_get_buffer(x->mem);
  stride = my_lcd_get_stride(x->mem);
  if (pixels == NULL || stride < (uint32_t)x->window->width * 4u) {
    return MY_RET_FAIL;
  }
  screen_copy_rect(x->shadow, (uint32_t)x->window->width * 4u, pixels, stride,
                   &clipped);
  return MY_RET_OK;
}

static my_ret_t screen_lcd_prepare(my_screen_lcd_t* x, screen_buffer_t buffer) {
  my_screen_window_t* w = x->window;
  my_screen_buffer_slot_t* slot = NULL;
  uint8_t* pixels = NULL;
  int stride = 0;
  uint32_t i;
  my_lcd_t* mem;
  if (buffer == NULL) return MY_RET_FAIL;
  if (x->mem != NULL && x->buffer == buffer) return MY_RET_OK;
  for (i = 0u; i < SCREEN_BUFFER_SLOT_COUNT; ++i) {
    if (x->slots[i].mem == NULL) {
      if (slot == NULL) slot = &x->slots[i];
    } else if (x->slots[i].buffer == buffer) {
      slot = &x->slots[i];
      break;
    }
  }
  if (slot == NULL) return MY_RET_FAIL;
  if (x->shadow == NULL) {
    if (!screen_size_supported(w->width, w->height)) {
      return MY_RET_INVALID_PARAMS;
    }
    x->shadow = my_mem_calloc(w->pal->allocator,
                              (size_t)(uint32_t)w->width *
                                  (size_t)(uint32_t)w->height,
                              4u);
    if (x->shadow == NULL) return MY_RET_OOM;
  }
  if (slot->mem != NULL) {
    x->mem = slot->mem;
    x->buffer = buffer;
    return MY_RET_OK;
  }
  if (screen_get_buffer_property_pv(buffer, SCREEN_PROPERTY_POINTER,
                                    (void**)&pixels) != 0 ||
      screen_get_buffer_property_iv(buffer, SCREEN_PROPERTY_STRIDE,
                                    &stride) != 0 ||
      pixels == NULL || stride < w->width * 4) {
    return MY_RET_FAIL;
  }
  mem = my_lcd_mem_create_from_buffer(
      w->pal->allocator, (uint32_t)w->width, (uint32_t)w->height,
      MY_PIXEL_FORMAT_RGBA8888, pixels, (uint32_t)stride);
  if (mem == NULL) return MY_RET_OOM;
  slot->buffer = buffer;
  slot->mem = mem;
  x->mem = mem;
  x->buffer = buffer;
  return MY_RET_OK;
}

static my_ret_t screen_lcd_begin(my_lcd_t* lcd, const my_rect_t* dirty) {
  my_screen_lcd_t* x = (my_screen_lcd_t*)lcd;
  screen_buffer_t available = NULL;
  my_ret_t result;
  if (x->in_frame) return MY_RET_INVALID_PARAMS;
  if (x->window->buffer_replace_failed) return MY_RET_FAIL;
  if (!x->buffer_acquired) {
    if (screen_dequeue_window_render_buffer(&available, x->window->native,
                                            SCREEN_DONT_BLOCK) != 0) {
      return errno == EWOULDBLOCK ? MY_RET_PENDING : MY_RET_FAIL;
    }
    result = screen_lcd_prepare(x, available);
    if (result != MY_RET_OK) {
      (void)screen_enqueue_render_buffer(available);
      return result;
    }
    x->buffer_acquired = true;
    x->restore_required = true;
  }
  if (x->restore_required) {
    result = screen_lcd_restore(x);
    if (result != MY_RET_OK) {
      (void)screen_enqueue_render_buffer(x->buffer);
      x->buffer_acquired = false;
      return result;
    }
    x->restore_required = false;
  }
  result = my_lcd_begin_frame(x->mem, dirty);
  if (result != MY_RET_OK) return result;
  x->in_frame = true;
  x->has_dirty = dirty != NULL && !my_rect_is_empty(dirty);
  if (x->has_dirty) x->dirty = *dirty;
  return MY_RET_OK;
}

static my_ret_t screen_lcd_end(my_lcd_t* lcd) {
  my_screen_lcd_t* x = (my_screen_lcd_t*)lcd;
  my_ret_t result;
  my_rect_t damage;
  int dirty[4];
  int count = 0;
  const int* rects = NULL;
  int post_result;
  if (!x->in_frame) return MY_RET_INVALID_PARAMS;
  result = my_lcd_end_frame(x->mem);
  if (result != MY_RET_OK) {
    x->unposted = screen_lcd_frame_damage(x);
    x->has_unposted = true;
    x->in_frame = false;
    return result;
  }
  damage = screen_lcd_frame_damage(x);
  result = screen_lcd_capture(x, &damage);
  if (result != MY_RET_OK) {
    x->in_frame = false;
    return result;
  }
  if (x->has_unposted) {
    dirty[0] = damage.x;
    dirty[1] = damage.y;
    dirty[2] = damage.w;
    dirty[3] = damage.h;
    count = 1;
    rects = dirty;
  } else if (x->has_dirty) {
    dirty[0] = x->dirty.x;
    dirty[1] = x->dirty.y;
    dirty[2] = x->dirty.w;
    dirty[3] = x->dirty.h;
    count = 1;
    rects = dirty;
  }
  post_result = screen_post_window(x->window->native, x->buffer, count, rects,
                                   SCREEN_DONT_BLOCK);
  if (post_result == 0) {
    x->has_unposted = false;
    x->post_count++;
    x->buffer_acquired = false;
    x->in_frame = false;
    return MY_RET_OK;
  }
  {
    int error = errno;
    x->unposted = damage;
    x->has_unposted = true;
    x->in_frame = false;
    return error == EWOULDBLOCK ? MY_RET_PENDING : MY_RET_FAIL;
  }
}

static my_ret_t screen_lcd_draw_pixels(my_lcd_t* lcd, const void* pixels,
                                       int32_t x, int32_t y, uint32_t w,
                                       uint32_t h) {
  return my_lcd_draw_pixels(((my_screen_lcd_t*)lcd)->mem, pixels, x, y, w, h);
}

static my_ret_t screen_lcd_fill_rect(my_lcd_t* lcd, const my_rect_t* rect,
                                     my_color_t color) {
  return my_lcd_fill_rect(((my_screen_lcd_t*)lcd)->mem, rect, color);
}

static my_ret_t screen_lcd_blend_span(my_lcd_t* lcd, int32_t x, int32_t y,
                                      const uint8_t* alpha, int32_t n,
                                      my_color_t color) {
  return my_lcd_blend_span(((my_screen_lcd_t*)lcd)->mem, x, y, alpha, n,
                           color);
}

static uint8_t* screen_lcd_buffer(my_lcd_t* lcd) {
  my_screen_lcd_t* x = (my_screen_lcd_t*)lcd;
  return x->mem != NULL ? my_lcd_get_buffer(x->mem) : NULL;
}

static uint32_t screen_lcd_stride(my_lcd_t* lcd) {
  my_screen_lcd_t* x = (my_screen_lcd_t*)lcd;
  return x->mem != NULL ? my_lcd_get_stride(x->mem) : 0u;
}

static const my_lcd_vtable_t s_lcd_vtable = {
    screen_lcd_width, screen_lcd_height, screen_lcd_format, screen_lcd_begin,
    screen_lcd_end, screen_lcd_draw_pixels, screen_lcd_fill_rect,
    screen_lcd_blend_span, screen_lcd_destroy, screen_lcd_buffer,
    screen_lcd_stride};

static my_ret_t screen_lcd_prime(my_screen_lcd_t* x) {
  screen_buffer_t available = NULL;
  my_ret_t result;
  if (screen_dequeue_window_render_buffer(&available, x->window->native,
                                          SCREEN_DONT_BLOCK) != 0) {
    return MY_RET_FAIL;
  }
  result = screen_lcd_prepare(x, available);
  if (result != MY_RET_OK) {
    (void)screen_enqueue_render_buffer(available);
    return result;
  }
  x->buffer_acquired = true;
  x->restore_required = true;
  return MY_RET_OK;
}

static my_screen_lcd_t* screen_lcd_create(my_screen_window_t* window) {
  my_screen_pal_t* pal = window->pal;
  my_screen_lcd_t* x = my_mem_calloc(pal->allocator, 1, sizeof(*x));
  if (x == NULL) return NULL;
  x->base.vtable = &s_lcd_vtable;
  x->window = window;
  if (screen_lcd_prime(x) != MY_RET_OK) {
    screen_lcd_release_buffers(x);
    my_mem_free(pal->allocator, x);
    return NULL;
  }
  return x;
}

static my_ret_t screen_win_set_name(my_screen_window_t* w, const char* title) {
  size_t length = strlen(title) + 1u;
  if (length > INT_MAX) return MY_RET_INVALID_PARAMS;
  return screen_set_window_property_cv(w->native, SCREEN_PROPERTY_ID_STRING,
                                       (int)length, title) == 0
             ? MY_RET_OK
             : MY_RET_FAIL;
}

static my_ret_t screen_win_set_title(my_pal_window_t* win, const char* title) {
  my_screen_window_t* w = (my_screen_window_t*)win;
  char* copy = my_strdup(w->pal->allocator, title != NULL ? title : "");
  my_ret_t result;
  if (copy == NULL) return MY_RET_OOM;
  result = screen_win_set_name(w, copy);
  if (result != MY_RET_OK || screen_flush_context(w->pal->context, 0) != 0) {
    my_mem_free(w->pal->allocator, copy);
    return result == MY_RET_OK ? MY_RET_FAIL : result;
  }
  my_mem_free(w->pal->allocator, w->title);
  w->title = copy;
  return MY_RET_OK;
}

static my_ret_t screen_win_replace_buffers(my_screen_window_t* w, int32_t width,
                                           int32_t height) {
  int size[2] = {width, height};
  my_ret_t result = MY_RET_OK;
  if (!screen_size_supported(width, height)) {
    return MY_RET_INVALID_PARAMS;
  }
  if (w->lcd != NULL && w->lcd->in_frame) return MY_RET_PENDING;
  if (w->lcd != NULL) screen_lcd_release_buffers(w->lcd);
  if (screen_destroy_window_buffers(w->native) != 0 ||
      screen_set_window_property_iv(w->native, SCREEN_PROPERTY_BUFFER_SIZE,
                                    size) != 0) {
    goto fail;
  }
  w->width = width;
  w->height = height;
  if (screen_create_window_buffers(w->native, SCREEN_BUFFER_SLOT_COUNT) != 0 ||
      screen_flush_context(w->pal->context, 0) != 0) {
    goto fail;
  }
  if (w->lcd != NULL) {
    result = screen_lcd_prime(w->lcd);
  } else {
    w->lcd = screen_lcd_create(w);
    result = w->lcd != NULL ? MY_RET_OK : MY_RET_FAIL;
  }
  if (result != MY_RET_OK) goto fail;
  w->buffer_replace_failed = false;
  return MY_RET_OK;

fail:
  w->buffer_replace_failed = true;
  return result == MY_RET_OK ? MY_RET_FAIL : result;
}

static my_ret_t screen_win_sync_size(my_screen_window_t* w) {
  int size[2];
  if (screen_get_window_property_iv(w->native, SCREEN_PROPERTY_SIZE, size) != 0 ||
      size[0] <= 0 || size[1] <= 0) {
    return MY_RET_FAIL;
  }
  if (w->lcd != NULL && !w->buffer_replace_failed &&
      size[0] == w->width && size[1] == w->height) {
    return MY_RET_OK;
  }
  return screen_win_replace_buffers(w, size[0], size[1]);
}

static my_ret_t screen_win_resize(my_pal_window_t* win, int32_t width,
                                  int32_t height) {
  my_screen_window_t* w = (my_screen_window_t*)win;
  int size[2];
  if (!screen_size_supported(width, height)) return MY_RET_INVALID_PARAMS;
  if (w->lcd != NULL && w->lcd->in_frame) return MY_RET_PENDING;
  if (w->lcd != NULL && !w->buffer_replace_failed && width == w->width &&
      height == w->height) {
    return MY_RET_OK;
  }
  size[0] = width;
  size[1] = height;
  if (screen_set_window_property_iv(w->native, SCREEN_PROPERTY_SIZE, size) != 0) {
    return MY_RET_FAIL;
  }
  return screen_win_replace_buffers(w, width, height);
}

static my_ret_t screen_win_show(my_pal_window_t* win) {
  my_screen_window_t* w = (my_screen_window_t*)win;
  int visible = 1;
  if (screen_set_window_property_iv(w->native, SCREEN_PROPERTY_VISIBLE,
                                    &visible) != 0 ||
      screen_flush_context(w->pal->context, 0) != 0) {
    return MY_RET_FAIL;
  }
  return MY_RET_OK;
}

static my_ret_t screen_win_get_size(my_pal_window_t* win, int32_t* width,
                                    int32_t* height) {
  my_screen_window_t* w = (my_screen_window_t*)win;
  my_ret_t result = screen_win_sync_size(w);
  if (result != MY_RET_OK) return result;
  if (width != NULL) *width = w->width;
  if (height != NULL) *height = w->height;
  return MY_RET_OK;
}

static my_lcd_t* screen_win_get_lcd(my_pal_window_t* win) {
  my_screen_window_t* w = (my_screen_window_t*)win;
  if (w->buffer_replace_failed || screen_win_sync_size(w) != MY_RET_OK) {
    return NULL;
  }
  return w->lcd != NULL ? &w->lcd->base : NULL;
}

static void screen_win_free(my_screen_window_t* w) {
  if (w->lcd != NULL) my_lcd_destroy(&w->lcd->base);
  (void)screen_destroy_window_buffers(w->native);
  (void)screen_destroy_window(w->native);
  my_mem_free(w->pal->allocator, w->title);
  my_mem_free(w->pal->allocator, w);
}

static void screen_win_native_release(my_screen_window_t* w) {
  if (w->native_depth > 0u) w->native_depth--;
  if (w->native_depth == 0u && w->destroy_requested) screen_win_free(w);
}

static void screen_win_destroy(my_pal_window_t* win) {
  my_screen_window_t* w = (my_screen_window_t*)win;
  if (w == NULL || w->destroy_requested) return;
  screen_window_unlink(w);
  if (w->native_depth != 0u) {
    w->destroy_requested = true;
    return;
  }
  screen_win_free(w);
}

static const my_pal_window_vtable_t s_window_vtable = {
    .set_title = screen_win_set_title,
    .resize = screen_win_resize,
    .show = screen_win_show,
    .get_size = screen_win_get_size,
    .get_lcd = screen_win_get_lcd,
    .destroy = screen_win_destroy};

static my_pal_window_t* screen_pal_window_create(my_pal_t* pal, int32_t width,
                                                 int32_t height,
                                                 const char* title) {
  my_screen_pal_t* p = (my_screen_pal_t*)pal;
  my_screen_window_t* w;
  int size[2];
  int format = SCREEN_FORMAT_RGBA8888;
  int usage = SCREEN_USAGE_READ | SCREEN_USAGE_WRITE;
  int visible = 0;
  if (p == NULL || !screen_size_supported(width, height)) return NULL;
  w = my_mem_calloc(p->allocator, 1, sizeof(*w));
  if (w == NULL) return NULL;
  w->base.vtable = &s_window_vtable;
  w->pal = p;
  w->width = width;
  w->height = height;
  size[0] = width;
  size[1] = height;
  if (screen_create_window(&w->native, p->context) != 0 ||
      screen_set_window_property_iv(w->native, SCREEN_PROPERTY_SIZE, size) != 0 ||
      screen_set_window_property_iv(w->native, SCREEN_PROPERTY_FORMAT,
                                    &format) != 0 ||
      screen_set_window_property_iv(w->native, SCREEN_PROPERTY_USAGE,
                                    &usage) != 0 ||
      screen_set_window_property_iv(w->native, SCREEN_PROPERTY_VISIBLE,
                                    &visible) != 0 ||
      screen_flush_context(p->context, 0) != 0 ||
      screen_create_window_buffers(w->native, SCREEN_BUFFER_SLOT_COUNT) != 0) {
    if (w->native != NULL) {
      (void)screen_destroy_window_buffers(w->native);
      (void)screen_destroy_window(w->native);
    }
    my_mem_free(p->allocator, w);
    return NULL;
  }
  w->lcd = screen_lcd_create(w);
  if (w->lcd == NULL) {
    (void)screen_destroy_window_buffers(w->native);
    (void)screen_destroy_window(w->native);
    my_mem_free(p->allocator, w);
    return NULL;
  }
  w->title = my_strdup(p->allocator, title != NULL ? title : "");
  if (w->title == NULL) {
    my_lcd_destroy(&w->lcd->base);
    (void)screen_destroy_window_buffers(w->native);
    (void)screen_destroy_window(w->native);
    my_mem_free(p->allocator, w);
    return NULL;
  }
  if (screen_win_set_name(w, w->title) != MY_RET_OK) {
    screen_win_destroy(&w->base);
    return NULL;
  }
  screen_window_link(w);
  return &w->base;
}

void* my_pal_screen_native_context(my_pal_t* pal) {
  return pal != NULL ? ((my_screen_pal_t*)pal)->context : NULL;
}

void* my_pal_screen_native_window(my_pal_window_t* win) {
  my_screen_window_t* w = (my_screen_window_t*)win;
  return w != NULL && !w->destroy_requested ? w->native : NULL;
}

uint32_t my_pal_screen_test_post_count(my_pal_window_t* win) {
  my_screen_window_t* w = (my_screen_window_t*)win;
  return w != NULL && w->lcd != NULL ? w->lcd->post_count : 0u;
}

static my_ret_t screen_loop_wake_locked(my_screen_loop_t* loop) {
  return screen_send_event(loop->pal->context, loop->pal->wake_event,
                           getpid()) == 0 ? MY_RET_OK : MY_RET_FAIL;
}

static my_ret_t screen_loop_wake(my_screen_loop_t* loop) {
  my_ret_t result;
  while (atomic_flag_test_and_set_explicit(&loop->event_lock,
                                           memory_order_acquire)) {
  }
  result = screen_loop_wake_locked(loop);
  atomic_flag_clear_explicit(&loop->event_lock, memory_order_release);
  return result;
}

static my_ret_t screen_loop_quit(my_pal_main_loop_t* loop) {
  my_screen_loop_t* l = (my_screen_loop_t*)loop;
  atomic_store_explicit(&l->quit, true, memory_order_release);
  return screen_loop_wake(l);
}

static my_ret_t screen_loop_post(my_pal_main_loop_t* loop,
                                 const my_event_t* event) {
  my_screen_loop_t* l = (my_screen_loop_t*)loop;
  my_screen_event_t* item;
  my_ret_t result;
  if (event == NULL) return MY_RET_INVALID_PARAMS;
  item = my_mem_calloc(l->pal->allocator, 1, sizeof(*item));
  if (item == NULL) return MY_RET_OOM;
  item->event = *event;
  if ((event->type == MY_EVENT_IME_PREEDIT ||
       event->type == MY_EVENT_IME_COMMIT) &&
      event->u.ime.text != NULL) {
    item->ime_text = my_strdup(l->pal->allocator, event->u.ime.text);
    if (item->ime_text == NULL) {
      my_mem_free(l->pal->allocator, item);
      return MY_RET_OOM;
    }
    item->event.u.ime.text = item->ime_text;
  }
  while (atomic_flag_test_and_set_explicit(&l->event_lock,
                                           memory_order_acquire)) {
  }
  if (!atomic_load_explicit(&l->accepting_events, memory_order_relaxed)) {
    result = MY_RET_PENDING;
  } else if (l->wake_pending) {
    result = MY_RET_OK;
  } else {
    result = screen_loop_wake_locked(l);
    l->wake_pending = result == MY_RET_OK;
  }
  if (result == MY_RET_OK) {
    if (l->tail != NULL) {
      l->tail->next = item;
    } else {
      l->head = item;
    }
    l->tail = item;
  }
  atomic_flag_clear_explicit(&l->event_lock, memory_order_release);
  if (result != MY_RET_OK) {
    my_mem_free(l->pal->allocator, item->ime_text);
    my_mem_free(l->pal->allocator, item);
  }
  return result;
}

static void screen_loop_deliver(my_screen_loop_t* l, my_pal_window_t* window,
                                const my_event_t* event) {
  if (l->pal->handler != NULL) {
    my_ui_command_dispatch_context_enter((my_pal_main_loop_t*)l);
    l->pal->handler(l->pal->handler_ctx, window, event);
    my_ui_command_dispatch_context_leave((my_pal_main_loop_t*)l);
  }
}

static uint64_t screen_loop_pending_count(my_screen_loop_t* l) {
  my_screen_event_t* item;
  uint64_t count = 0u;
  while (atomic_flag_test_and_set_explicit(&l->event_lock,
                                           memory_order_acquire)) {
  }
  for (item = l->head; item != NULL; item = item->next) count++;
  atomic_flag_clear_explicit(&l->event_lock, memory_order_release);
  return count;
}

static bool screen_loop_has_pending(my_screen_loop_t* l) {
  bool pending;
  while (atomic_flag_test_and_set_explicit(&l->event_lock,
                                           memory_order_acquire)) {
  }
  pending = l->head != NULL;
  if (!pending) l->wake_pending = false;
  atomic_flag_clear_explicit(&l->event_lock, memory_order_release);
  return pending;
}

static bool screen_loop_drain(my_screen_loop_t* l, uint64_t budget) {
  while (budget > 0u) {
    my_screen_event_t* item;
    if (l->destroy_requested) return true;
    while (atomic_flag_test_and_set_explicit(&l->event_lock,
                                             memory_order_acquire)) {
    }
    item = l->head;
    if (item == NULL) {
      l->wake_pending = false;
      atomic_flag_clear_explicit(&l->event_lock, memory_order_release);
      return false;
    }
    l->head = item->next;
    if (l->head == NULL) l->tail = NULL;
    atomic_flag_clear_explicit(&l->event_lock, memory_order_release);
    screen_loop_deliver(l, NULL, &item->event);
    my_event_release_payload(&item->event);
    my_mem_free(l->pal->allocator, item->ime_text);
    my_mem_free(l->pal->allocator, item);
    budget--;
    if (budget == 0u) return screen_loop_has_pending(l);
  }
  return false;
}

static uint8_t screen_native_modifiers(screen_event_t native) {
  int value = 0;
  uint8_t result = 0;
  (void)screen_get_event_property_iv(native, SCREEN_PROPERTY_MODIFIERS, &value);
  if ((value & KEYMOD_SHIFT) != 0) result |= MY_KEYMOD_SHIFT;
  if ((value & KEYMOD_CTRL) != 0) result |= MY_KEYMOD_CTRL;
  if ((value & KEYMOD_ALT) != 0) result |= MY_KEYMOD_ALT;
  return result;
}

static uint32_t screen_native_key_symbol(int symbol) {
  if (symbol >= 32 && symbol <= 126) return (uint32_t)symbol;
  switch (symbol) {
    case KEYCODE_RETURN:
    case KEYCODE_KP_ENTER:
      return MY_KEY_RETURN;
    case KEYCODE_ESCAPE:
      return MY_KEY_ESCAPE;
    case KEYCODE_BACKSPACE:
      return MY_KEY_BACKSPACE;
    case KEYCODE_TAB:
    case KEYCODE_BACK_TAB:
      return MY_KEY_TAB;
    case KEYCODE_LEFT:
    case KEYCODE_KP_LEFT:
      return MY_KEY_LEFT;
    case KEYCODE_RIGHT:
    case KEYCODE_KP_RIGHT:
      return MY_KEY_RIGHT;
    case KEYCODE_UP:
    case KEYCODE_KP_UP:
      return MY_KEY_UP;
    case KEYCODE_DOWN:
    case KEYCODE_KP_DOWN:
      return MY_KEY_DOWN;
    case KEYCODE_HOME:
    case KEYCODE_KP_HOME:
      return MY_KEY_HOME;
    case KEYCODE_END:
    case KEYCODE_KP_END:
      return MY_KEY_END;
    case KEYCODE_PG_UP:
    case KEYCODE_KP_PG_UP:
      return MY_KEY_PAGE_UP;
    case KEYCODE_PG_DOWN:
    case KEYCODE_KP_PG_DOWN:
      return MY_KEY_PAGE_DOWN;
    case KEYCODE_INSERT:
    case KEYCODE_KP_INSERT:
      return MY_KEY_INSERT;
    case KEYCODE_DELETE:
    case KEYCODE_KP_DELETE:
      return MY_KEY_DELETE;
    case KEYCODE_F1:
      return MY_KEY_F1;
    case KEYCODE_F2:
      return MY_KEY_F2;
    case KEYCODE_F3:
      return MY_KEY_F3;
    case KEYCODE_F4:
      return MY_KEY_F4;
    case KEYCODE_F5:
      return MY_KEY_F5;
    case KEYCODE_F6:
      return MY_KEY_F6;
    case KEYCODE_F7:
      return MY_KEY_F7;
    case KEYCODE_F8:
      return MY_KEY_F8;
    case KEYCODE_F9:
      return MY_KEY_F9;
    case KEYCODE_F10:
      return MY_KEY_F10;
    case KEYCODE_F11:
      return MY_KEY_F11;
    case KEYCODE_F12:
      return MY_KEY_F12;
    case KEYCODE_KP_PLUS:
      return (uint32_t)'+';
    case KEYCODE_KP_MINUS:
      return (uint32_t)'-';
    case KEYCODE_KP_MULTIPLY:
      return (uint32_t)'*';
    case KEYCODE_KP_DIVIDE:
      return (uint32_t)'/';
    default:
      return MY_KEY_UNKNOWN;
  }
}

static void screen_native_keyboard(my_screen_loop_t* l,
                                   my_screen_window_t* w) {
  screen_event_t native = l->pal->event;
  my_event_t event;
  int symbol;
  int flags;
  if (screen_get_event_property_iv(native, SCREEN_PROPERTY_SYM, &symbol) != 0 ||
      screen_get_event_property_iv(native, SCREEN_PROPERTY_FLAGS, &flags) != 0 ||
      (flags & KEY_SYM_VALID) == 0 || w->destroy_requested ||
      l->destroy_requested) {
    return;
  }
  event = my_event_init((flags & KEY_DOWN) != 0 ? MY_EVENT_KEY_DOWN
                                                : MY_EVENT_KEY_UP);
  event.time_ms = screen_now_ms(l->pal);
  event.u.key.key = screen_native_key_symbol(symbol);
  if (event.u.key.key == MY_KEY_UNKNOWN) return;
  event.u.key.modifiers = screen_native_modifiers(native);
  if (symbol == KEYCODE_BACK_TAB) event.u.key.modifiers |= MY_KEYMOD_SHIFT;
  screen_loop_deliver(l, &w->base, &event);
}

static void screen_native_pointer_event(my_screen_loop_t* l,
                                        my_screen_window_t* w,
                                        my_event_type_t type, int32_t x,
                                        int32_t y, uint8_t button,
                                        uint8_t modifiers, int32_t delta) {
  my_event_t event;
  if (w->destroy_requested || l->destroy_requested) return;
  event = my_event_init(type);
  event.time_ms = screen_now_ms(l->pal);
  event.u.pointer.x = x;
  event.u.pointer.y = y;
  event.u.pointer.button = button;
  event.u.pointer.modifiers = modifiers;
  event.u.pointer.delta = delta;
  screen_loop_deliver(l, &w->base, &event);
}

static void screen_native_pointer(my_screen_loop_t* l,
                                  my_screen_window_t* w) {
  screen_event_t native = l->pal->event;
  int flags = 0;
  int position[2];
  int origin[2] = {0, 0};
  int wheel = 0;
  int buttons = (int)w->buttons;
  uint32_t changed;
  uint32_t i;
  int64_t x;
  int64_t y;
  bool moved;
  uint8_t modifiers = screen_native_modifiers(native);
  (void)screen_get_event_property_iv(native, SCREEN_PROPERTY_FLAGS, &flags);
  if ((flags & SCREEN_FLAG_SOURCE_POSITION_VALID) != 0) {
    if (screen_get_event_property_iv(native, SCREEN_PROPERTY_SOURCE_POSITION,
                                     position) != 0) {
      return;
    }
  } else if (screen_get_event_property_iv(native, SCREEN_PROPERTY_POSITION,
                                          position) != 0) {
    return;
  }
  x = position[0];
  y = position[1];
  if ((flags & SCREEN_FLAG_SOURCE_POSITION_VALID) == 0 &&
      (flags & SCREEN_FLAG_POSITION_VALID) != 0 &&
      screen_get_window_property_iv(w->native, SCREEN_PROPERTY_POSITION,
                                    origin) == 0) {
    x -= origin[0];
    y -= origin[1];
  }
  if (x < INT32_MIN || x > INT32_MAX || y < INT32_MIN || y > INT32_MAX) return;
  moved = !w->has_pointer_position || w->pointer_x != x || w->pointer_y != y;
  (void)screen_get_event_property_iv(native, SCREEN_PROPERTY_BUTTONS, &buttons);
  (void)screen_get_event_property_iv(native, SCREEN_PROPERTY_MOUSE_WHEEL, &wheel);
  changed = w->buttons ^ (uint32_t)buttons;
  if (w->has_pointer_position && moved) {
    screen_native_pointer_event(l, w, MY_EVENT_POINTER_MOVE, (int32_t)x,
                                (int32_t)y, 0u, modifiers, 0);
  }
  w->has_pointer_position = true;
  w->pointer_x = (int32_t)x;
  w->pointer_y = (int32_t)y;
  w->buttons = (uint32_t)buttons;
  if (wheel != 0) {
    screen_native_pointer_event(l, w, MY_EVENT_POINTER_WHEEL, (int32_t)x,
                                (int32_t)y, 0u, modifiers, wheel);
  }
  for (i = 0u; i < 3u && !w->destroy_requested && !l->destroy_requested; ++i) {
    uint32_t mask = 1u << i;
    if ((changed & mask) != 0) {
      bool down = ((uint32_t)buttons & mask) != 0;
      screen_native_pointer_event(l, w,
                                  down ? MY_EVENT_POINTER_DOWN
                                       : MY_EVENT_POINTER_UP,
                                  (int32_t)x, (int32_t)y, (uint8_t)(i + 1u),
                                  modifiers, 0);
    }
  }
}

static void screen_loop_native(my_screen_loop_t* l) {
  int type = SCREEN_EVENT_NONE;
  screen_window_t native = NULL;
  my_screen_window_t* w;
  my_event_t event;
  if (screen_get_event_property_iv(l->pal->event, SCREEN_PROPERTY_TYPE,
                                   &type) != 0) {
    return;
  }
  if (type == SCREEN_EVENT_USER) {
    int data[4] = {0, 0, 0, 0};
    if (screen_get_event_property_iv(l->pal->event,
                                     SCREEN_PROPERTY_USER_DATA, data) != 0) {
      return;
    }
    if (data[0] != SCREEN_WAKE_COOKIE) {
      event = my_event_init(MY_EVENT_USER);
      event.time_ms = screen_now_ms(l->pal);
      screen_loop_deliver(l, NULL, &event);
    }
    return;
  }
  if (screen_get_event_property_pv(l->pal->event, SCREEN_PROPERTY_WINDOW,
                                   (void**)&native) != 0) {
    return;
  }
  w = screen_window_find(l->pal, native);
  if (w == NULL) return;
  w->native_depth++;
  if (type == SCREEN_EVENT_MANAGER) {
    int subtype = -1;
    if (screen_get_event_property_iv(l->pal->event, SCREEN_PROPERTY_SUBTYPE,
                                     &subtype) != 0 ||
        subtype != MY_PAL_SCREEN_MANAGER_CLOSE) {
      screen_win_native_release(w);
      return;
    }
  }
  if (type == SCREEN_EVENT_PROPERTY) {
    int property = -1;
    if (screen_get_event_property_iv(l->pal->event, SCREEN_PROPERTY_NAME,
                                     &property) != 0 ||
        property != SCREEN_PROPERTY_SIZE || screen_win_sync_size(w) != MY_RET_OK) {
      screen_win_native_release(w);
      return;
    }
    event = my_event_init(MY_EVENT_RESIZE);
    event.time_ms = screen_now_ms(l->pal);
    event.u.resize.w = w->width;
    event.u.resize.h = w->height;
    screen_loop_deliver(l, &w->base, &event);
  } else if (type == SCREEN_EVENT_CLOSE || type == SCREEN_EVENT_MANAGER) {
    event = my_event_init(MY_EVENT_QUIT);
    event.time_ms = screen_now_ms(l->pal);
    screen_loop_deliver(l, &w->base, &event);
  } else if (type == SCREEN_EVENT_POINTER) {
    screen_native_pointer(l, w);
  } else if (type == SCREEN_EVENT_KEYBOARD) {
    screen_native_keyboard(l, w);
  }
  screen_win_native_release(w);
}

static void screen_loop_free(my_screen_loop_t* l);

static my_ret_t screen_loop_run(my_pal_main_loop_t* loop) {
  my_screen_loop_t* l = (my_screen_loop_t*)loop;
  my_ret_t result = MY_RET_OK;
  if (l->running) return MY_RET_PENDING;
  l->running = true;
  while (!atomic_load_explicit(&l->quit, memory_order_acquire)) {
    uint32_t due;
    uint64_t timeout;
    int rc;
    int type;
    bool pending = screen_loop_drain(l, 64u);
    if (atomic_load_explicit(&l->quit, memory_order_acquire)) break;
    (void)my_timer_manager_fire(l->timers);
    if (atomic_load_explicit(&l->quit, memory_order_acquire)) break;
    due = my_timer_manager_due_in_ms(l->timers);
    timeout = pending ? 0u
                      : due == UINT32_MAX ? UINT64_MAX
                                          : (uint64_t)due * 1000000u;
    rc = screen_get_event(l->pal->context, l->pal->event, timeout);
    if (rc != 0) {
      if (errno == EINTR) continue;
      result = MY_RET_FAIL;
      break;
    }
    type = SCREEN_EVENT_NONE;
    if (screen_get_event_property_iv(l->pal->event, SCREEN_PROPERTY_TYPE,
                                     &type) != 0) {
      result = MY_RET_FAIL;
      break;
    }
    if (type != SCREEN_EVENT_NONE) screen_loop_native(l);
  }
  (void)screen_loop_drain(l, screen_loop_pending_count(l));
  l->running = false;
  if (l->destroy_requested) screen_loop_free(l);
  return result;
}

static uint32_t screen_loop_add_timer(my_pal_main_loop_t* loop,
                                      my_timer_callback_t callback, void* ctx,
                                      uint32_t interval_ms) {
  return my_timer_add(((my_screen_loop_t*)loop)->timers, callback, ctx,
                      interval_ms);
}

static my_ret_t screen_loop_remove_timer(my_pal_main_loop_t* loop, uint32_t id) {
  return my_timer_remove(((my_screen_loop_t*)loop)->timers, id);
}

static void screen_loop_free(my_screen_loop_t* l) {
  my_screen_event_t* pending;
  l->destroy_requested = true;
  while (atomic_flag_test_and_set_explicit(&l->event_lock,
                                           memory_order_acquire)) {
  }
  atomic_store_explicit(&l->accepting_events, false, memory_order_release);
  pending = l->head;
  l->head = NULL;
  l->tail = NULL;
  atomic_flag_clear_explicit(&l->event_lock, memory_order_release);
  while (pending != NULL) {
    my_screen_event_t* item = pending;
    pending = item->next;
    my_event_release_payload(&item->event);
    my_mem_free(l->pal->allocator, item->ime_text);
    my_mem_free(l->pal->allocator, item);
  }
  my_timer_manager_destroy(l->timers);
  my_mem_free(l->pal->allocator, l);
}

static void screen_loop_destroy(my_pal_main_loop_t* loop) {
  my_screen_loop_t* l = (my_screen_loop_t*)loop;
  if (l == NULL || l->destroy_requested) return;
  l->destroy_requested = true;
  if (l->running) {
    atomic_store_explicit(&l->quit, true, memory_order_release);
    (void)screen_loop_wake(l);
    return;
  }
  screen_loop_free(l);
}

static const my_pal_main_loop_vtable_t s_loop_vtable = {
    screen_loop_run, screen_loop_quit, screen_loop_post,
    screen_loop_add_timer, screen_loop_remove_timer, screen_loop_destroy};

static my_pal_main_loop_t* screen_pal_loop_create(my_pal_t* pal) {
  my_screen_pal_t* p = (my_screen_pal_t*)pal;
  my_screen_loop_t* l;
  if (p == NULL) return NULL;
  l = my_mem_calloc(p->allocator, 1, sizeof(*l));
  if (l == NULL) return NULL;
  l->base.vtable = &s_loop_vtable;
  l->pal = p;
  atomic_flag_clear(&l->event_lock);
  atomic_init(&l->accepting_events, true);
  atomic_init(&l->quit, false);
  l->timers = my_timer_manager_create(p->allocator, screen_now_ms, p);
  if (l->timers == NULL) {
    screen_loop_destroy(&l->base);
    return NULL;
  }
  return &l->base;
}

static uint64_t screen_pal_time_ms(my_pal_t* pal) {
  (void)pal;
  return time_microseconds() / 1000u;
}

static my_ret_t screen_pal_set_handler(my_pal_t* pal,
                                       my_pal_event_handler_t handler,
                                       void* context) {
  my_screen_pal_t* p = (my_screen_pal_t*)pal;
  if (p == NULL) return MY_RET_INVALID_PARAMS;
  p->handler = handler;
  p->handler_ctx = context;
  return MY_RET_OK;
}

static my_ret_t screen_pal_clipboard_set(my_pal_t* pal, const char* text) {
  (void)pal;
  (void)text;
  return MY_RET_NOT_SUPPORTED;
}

static my_ret_t screen_pal_clipboard_get(my_pal_t* pal, char* buf,
                                         size_t size) {
  (void)pal;
  (void)buf;
  (void)size;
  return MY_RET_NOT_SUPPORTED;
}

static my_ret_t screen_pal_clipboard_alloc(my_pal_t* pal,
                                           const my_allocator_t* allocator,
                                           char** out) {
  (void)pal;
  (void)allocator;
  if (out != NULL) *out = NULL;
  return MY_RET_NOT_SUPPORTED;
}

static float screen_pal_scale(my_pal_t* pal) {
  (void)pal;
  return 1.0f;
}

static void screen_pal_destroy(my_pal_t* pal) {
  my_screen_pal_t* p = (my_screen_pal_t*)pal;
  if (p == NULL) return;
  my_pal_unregister_media_provider(pal);
  if (p->event != NULL) (void)screen_destroy_event(p->event);
  if (p->wake_event != NULL) (void)screen_destroy_event(p->wake_event);
  if (p->context != NULL) (void)screen_destroy_context(p->context);
  my_mem_free(p->allocator, p);
}

static const my_pal_vtable_t s_pal_vtable = {
    screen_pal_window_create, screen_pal_loop_create, screen_pal_time_ms,
    screen_pal_set_handler, screen_pal_clipboard_set, screen_pal_clipboard_get,
    screen_pal_clipboard_alloc, screen_pal_scale, screen_pal_destroy,
    NULL};

my_pal_t* my_pal_screen_create(const my_allocator_t* allocator) {
  my_screen_pal_t* p = my_mem_calloc(allocator, 1, sizeof(*p));
  int type = SCREEN_EVENT_USER;
  int data[4] = {SCREEN_WAKE_COOKIE, 0, 0, 0};
  if (p == NULL) return NULL;
  p->base.vtable = &s_pal_vtable;
  p->allocator = allocator;
  if (screen_create_context(&p->context, SCREEN_APPLICATION_CONTEXT) != 0 ||
      screen_create_event(&p->event) != 0 ||
      screen_create_event(&p->wake_event) != 0 ||
      screen_set_event_property_iv(p->wake_event, SCREEN_PROPERTY_TYPE,
                                   &type) != 0 ||
      screen_set_event_property_iv(p->wake_event, SCREEN_PROPERTY_USER_DATA,
                                   data) != 0) {
    screen_pal_destroy(&p->base);
    return NULL;
  }
  return &p->base;
}
