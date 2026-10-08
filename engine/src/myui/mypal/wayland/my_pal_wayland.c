/**
 * @file my_pal_wayland.c
 * @brief Wayland PAL port: xdg-shell windows, wl_shm lcd, EGL GLES2.
 */
#define _POSIX_C_SOURCE 200809L
#include "mypal/wayland/my_pal_wayland.h"

#include "myr/my_lcd_mem.h"
#include "mypal/my_timer.h"

#include <wayland-client.h>
#include <wayland-client-protocol.h>
#include <wayland-egl.h>
#include <linux/input-event-codes.h>
#include <sys/mman.h>
#include <poll.h>
#include <fcntl.h>
#include <unistd.h>

#include <EGL/egl.h>
#include <EGL/eglext.h>
#ifndef EGL_PLATFORM_WAYLAND_KHR
#define EGL_PLATFORM_WAYLAND_KHR 0x31D8
#endif

#include <stdatomic.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "xdg-shell-client-protocol.h"

typedef struct wl_pal_t {
  my_pal_t base;
  const my_allocator_t* allocator;
  struct wl_display* display;
  struct wl_registry* registry;
  struct wl_compositor* compositor;
  struct wl_shm* shm;
  struct xdg_wm_base* wm_base;
  struct wl_seat* seat;
  my_pal_event_handler_t handler;
  void* handler_ctx;
  struct wl_window_t* windows[8];
  size_t window_count;
  uint32_t pointer_serial;
  int32_t hot_x;
  int32_t hot_y;
} wl_pal_t;

typedef struct wl_shm_lcd_t {
  my_lcd_t base;
  wl_pal_t* pal;
  my_lcd_t* mem;
  struct wl_surface* surface;
  struct wl_buffer* buffer;
  void* data;
  size_t size;
  int32_t width;
  int32_t height;
} wl_shm_lcd_t;

typedef struct wl_window_t {
  my_pal_window_t base;
  wl_pal_t* pal;
  struct wl_surface* surface;
  struct xdg_surface* xdg_surface;
  struct xdg_toplevel* toplevel;
  wl_shm_lcd_t* lcd;
  struct wl_gl_t* gl;
  int32_t width;
  int32_t height;
  int configured;
  int closed;
} wl_window_t;

typedef struct wl_gl_t {
  my_pal_gl_t base;
  wl_window_t* owner;
  EGLDisplay display;
  EGLSurface surface;
  EGLContext context;
  struct wl_egl_window* egl_window;
} wl_gl_t;

typedef struct queued_event_t {
  my_event_t event;
  struct queued_event_t* next;
} queued_event_t;

typedef struct wl_loop_t {
  my_pal_main_loop_t base;
  wl_pal_t* pal;
  const my_allocator_t* allocator;
  int wake_pipe[2];
  queued_event_t* head;
  queued_event_t* tail;
  my_timer_manager_t* timers;
  atomic_flag lock;
  atomic_bool accepting;
  atomic_bool quit;
} wl_loop_t;

static uint64_t wl_now_ms(void) {
  struct timespec ts;
  (void)clock_gettime(CLOCK_MONOTONIC, &ts);
  return (uint64_t)ts.tv_sec * 1000u + (uint64_t)ts.tv_nsec / 1000000u;
}

static void wl_deliver(wl_pal_t* pal, my_pal_window_t* window,
                       const my_event_t* event) {
  if (pal->handler != NULL) pal->handler(pal->handler_ctx, window, event);
}

/* ---------------- registry + seat ---------------- */

static void registry_global(void* data, struct wl_registry* r, uint32_t name,
                            const char* iface, uint32_t version) {
  wl_pal_t* pal = data;
  (void)version;
  if (strcmp(iface, "wl_compositor") == 0)
    pal->compositor = wl_registry_bind(r, name, &wl_compositor_interface, 1);
  else if (strcmp(iface, "wl_shm") == 0)
    pal->shm = wl_registry_bind(r, name, &wl_shm_interface, 1);
  else if (strcmp(iface, "xdg_wm_base") == 0)
    pal->wm_base = wl_registry_bind(r, name, &xdg_wm_base_interface, 1);
  else if (strcmp(iface, "wl_seat") == 0)
    pal->seat = wl_registry_bind(r, name, &wl_seat_interface, 1);
}

static const struct wl_registry_listener registry_listener = {
    .global = registry_global, .global_remove = NULL};

static void pointer_enter(void* data, struct wl_pointer* p, uint32_t serial,
                          struct wl_surface* s, wl_fixed_t sx, wl_fixed_t sy) {
  wl_pal_t* pal = data;
  (void)p; (void)s;
  pal->pointer_serial = serial;
  pal->hot_x = wl_fixed_to_int(sx);
  pal->hot_y = wl_fixed_to_int(sy);
}

static void pointer_motion(void* data, struct wl_pointer* p, uint32_t time,
                           wl_fixed_t sx, wl_fixed_t sy) {
  wl_pal_t* pal = data;
  my_event_t event;
  size_t i;
  (void)p; (void)time;
  pal->hot_x = wl_fixed_to_int(sx);
  pal->hot_y = wl_fixed_to_int(sy);
  event = my_event_init(MY_EVENT_POINTER_MOVE);
  event.u.pointer.x = pal->hot_x;
  event.u.pointer.y = pal->hot_y;
  for (i = 0u; i < pal->window_count; i++)
    wl_deliver(pal, &pal->windows[i]->base, &event);
}

static void pointer_button(void* data, struct wl_pointer* p, uint32_t serial,
                           uint32_t time, uint32_t button, uint32_t state) {
  wl_pal_t* pal = data;
  my_event_t event;
  size_t i;
  (void)p; (void)time;
  pal->pointer_serial = serial;
  if (state != WL_POINTER_BUTTON_STATE_PRESSED || button != BTN_LEFT) return;
  event = my_event_init(MY_EVENT_POINTER_DOWN);
  event.u.pointer.x = pal->hot_x;
  event.u.pointer.y = pal->hot_y;
  event.u.pointer.button = 1u;
  for (i = 0u; i < pal->window_count; i++)
    wl_deliver(pal, &pal->windows[i]->base, &event);
}

static void pointer_axis(void* data, struct wl_pointer* p, uint32_t time,
                         uint32_t axis, wl_fixed_t value) {
  wl_pal_t* pal = data;
  my_event_t event;
  size_t i;
  (void)p; (void)time; (void)axis;
  event = my_event_init(MY_EVENT_POINTER_WHEEL);
  event.u.pointer.x = pal->hot_x;
  event.u.pointer.y = pal->hot_y;
  event.u.pointer.delta = wl_fixed_to_int(value) > 0 ? -1 : 1;
  for (i = 0u; i < pal->window_count; i++)
    wl_deliver(pal, &pal->windows[i]->base, &event);
}

static const struct wl_pointer_listener pointer_listener = {
    .enter = pointer_enter, .leave = NULL, .motion = pointer_motion,
    .button = pointer_button, .axis = pointer_axis};

static void keymap(void* data, struct wl_keyboard* k, uint32_t format,
                   int32_t fd, uint32_t size) {
  (void)data; (void)k; (void)format; (void)fd; (void)size;
}

static void kbd_enter(void* data, struct wl_keyboard* k, uint32_t serial,
                      struct wl_surface* surface, struct wl_array* keys) {
  (void)data; (void)k; (void)serial; (void)surface; (void)keys;
}
static void kbd_leave(void* data, struct wl_keyboard* k, uint32_t serial,
                      struct wl_surface* surface) {
  (void)data; (void)k; (void)serial; (void)surface;
}

static void key_event(void* data, struct wl_keyboard* k, uint32_t serial,
                      uint32_t time, uint32_t key_code, uint32_t state) {
  wl_pal_t* pal = data;
  my_event_t event;
  int ch = 0;
  size_t i;
  (void)k; (void)serial; (void)time;
  if (state != WL_KEYBOARD_KEY_STATE_PRESSED) return;
  if (key_code >= KEY_1 && key_code <= KEY_9) ch = '1' + (int)(key_code - KEY_1);
  else if (key_code == KEY_0) ch = '0';
  else if (key_code >= KEY_A && key_code <= KEY_Z)
    ch = 'a' + (int)(key_code - KEY_A);
  else if (key_code == KEY_MINUS) ch = '-';
  else if (key_code == KEY_EQUAL) ch = '=';
  else if (key_code >= KEY_SPACE && key_code <= KEY_SLASH)
    ch = (int)key_code;
  if (ch == 0) return;
  event = my_event_init(MY_EVENT_KEY_DOWN);
  event.u.key.key = (uint32_t)ch;
  for (i = 0u; i < pal->window_count; i++)
    wl_deliver(pal, &pal->windows[i]->base, &event);
}

static void kbd_modifiers(void* data, struct wl_keyboard* k, uint32_t serial,
                          uint32_t depressed, uint32_t latched,
                          uint32_t locked, uint32_t group) {
  (void)data; (void)k; (void)serial; (void)depressed; (void)latched;
  (void)locked; (void)group;
}

static void kbd_repeat(void* data, struct wl_keyboard* k, int32_t rate,
                       int32_t delay) {
  (void)data; (void)k; (void)rate; (void)delay;
}

static const struct wl_keyboard_listener keyboard_listener = {
    .keymap = keymap, .enter = kbd_enter, .leave = kbd_leave, .key = key_event,
    .modifiers = kbd_modifiers, .repeat_info = kbd_repeat};

static void seat_capabilities(void* data, struct wl_seat* seat,
                              uint32_t caps) {
  wl_pal_t* pal = data;
  if ((caps & WL_SEAT_CAPABILITY_POINTER) != 0u) {
    struct wl_pointer* p = wl_seat_get_pointer(seat);
    wl_pointer_add_listener(p, &pointer_listener, pal);
  }
  if ((caps & WL_SEAT_CAPABILITY_KEYBOARD) != 0u) {
    struct wl_keyboard* kb = wl_seat_get_keyboard(seat);
    wl_keyboard_add_listener(kb, &keyboard_listener, pal);
  }
}

static const struct wl_seat_listener seat_listener = {
    .capabilities = seat_capabilities};

static void wm_base_ping(void* data, struct xdg_wm_base* base,
                         uint32_t serial) {
  (void)data;
  xdg_wm_base_pong(base, serial);
}

static const struct xdg_wm_base_listener wm_base_listener = {
    .ping = wm_base_ping};

/* ---------------- lcd (wl_shm presentation) ---------------- */

static uint32_t wlcd_width(my_lcd_t* lcd) {
  return my_lcd_get_width(((wl_shm_lcd_t*)lcd)->mem);
}

static uint32_t wlcd_height(my_lcd_t* lcd) {
  return my_lcd_get_height(((wl_shm_lcd_t*)lcd)->mem);
}

static my_pixel_format_t wlcd_format(my_lcd_t* lcd) {
  return my_lcd_get_format(((wl_shm_lcd_t*)lcd)->mem);
}

static my_ret_t wlcd_begin(my_lcd_t* lcd, const my_rect_t* dirty) {
  return my_lcd_begin_frame(((wl_shm_lcd_t*)lcd)->mem, dirty);
}

static my_ret_t wlcd_end(my_lcd_t* lcd) {
  wl_shm_lcd_t* x = (wl_shm_lcd_t*)lcd;
  my_ret_t r = my_lcd_end_frame(x->mem);
  if (r != MY_RET_OK) return r;
  if (x->buffer == NULL) return MY_RET_FAIL;
  memcpy(x->data, my_lcd_get_buffer(x->mem), x->size);
  wl_surface_attach(x->surface, x->buffer, 0, 0);
  wl_surface_damage(x->surface, 0, 0, x->width, x->height);
  wl_surface_commit(x->surface);
  return MY_RET_OK;
}

static my_ret_t wlcd_draw_pixels(my_lcd_t* lcd, const void* pixels,
                                 int32_t px, int32_t py, uint32_t w,
                                 uint32_t h) {
  return my_lcd_draw_pixels(((wl_shm_lcd_t*)lcd)->mem, pixels, px, py, w, h);
}

static my_ret_t wlcd_fill_rect(my_lcd_t* lcd, const my_rect_t* rect,
                               my_color_t color) {
  return my_lcd_fill_rect(((wl_shm_lcd_t*)lcd)->mem, rect, color);
}

static my_ret_t wlcd_blend_span(my_lcd_t* lcd, int32_t x, int32_t y,
                                const uint8_t* alpha, int32_t n,
                                my_color_t color) {
  return my_lcd_blend_span(((wl_shm_lcd_t*)lcd)->mem, x, y, alpha, n, color);
}

static uint8_t* wlcd_buffer(my_lcd_t* lcd) {
  return my_lcd_get_buffer(((wl_shm_lcd_t*)lcd)->mem);
}

static uint32_t wlcd_stride(my_lcd_t* lcd) {
  return my_lcd_get_stride(((wl_shm_lcd_t*)lcd)->mem);
}

static void wlcd_destroy(my_lcd_t* lcd) {
  wl_shm_lcd_t* x = (wl_shm_lcd_t*)lcd;
  if (x->buffer != NULL) wl_buffer_destroy(x->buffer);
  if (x->data != MAP_FAILED && x->data != NULL) munmap(x->data, x->size);
  my_lcd_destroy(x->mem);
  my_mem_free(x->pal->allocator, x);
}

static const my_lcd_vtable_t s_wlcd_vtable = {
    wlcd_width, wlcd_height, wlcd_format, wlcd_begin,
    wlcd_end, wlcd_draw_pixels, wlcd_fill_rect, wlcd_blend_span,
    wlcd_destroy, wlcd_buffer, wlcd_stride};

static wl_shm_lcd_t* wlcd_create(wl_pal_t* pal, struct wl_surface* surface,
                                 int32_t w, int32_t h) {
  wl_shm_lcd_t* x;
  int fd;
  char name[] = "/tmp/myui-pal-wl-XXXXXX";
  struct wl_shm_pool* pool;
  x = (wl_shm_lcd_t*)my_mem_calloc(pal->allocator, 1u, sizeof(*x));
  if (x == NULL) return NULL;
  x->base.vtable = &s_wlcd_vtable;
  x->pal = pal;
  x->surface = surface;
  x->width = w;
  x->height = h;
  x->size = (size_t)w * (size_t)h * 4u;
  x->mem = my_lcd_mem_create(pal->allocator, (uint32_t)w, (uint32_t)h,
                             MY_PIXEL_FORMAT_BGRA8888);
  if (x->mem == NULL) goto fail;
  fd = mkstemp(name);
  if (fd < 0) goto fail;
  (void)unlink(name);
  if (ftruncate(fd, (off_t)x->size) != 0) {
    close(fd);
    goto fail;
  }
  x->data = mmap(NULL, x->size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
  if (x->data == MAP_FAILED) {
    close(fd);
    goto fail;
  }
  pool = wl_shm_create_pool(pal->shm, fd, (int32_t)x->size);
  x->buffer = wl_shm_pool_create_buffer(pool, 0, w, h, w * 4,
                                        WL_SHM_FORMAT_XRGB8888);
  wl_shm_pool_destroy(pool);
  close(fd);
  return x;
fail:
  my_lcd_destroy(x->mem);
  my_mem_free(pal->allocator, x);
  return NULL;
}

/* ---------------- window ---------------- */

static void xdg_configure(void* data, struct xdg_surface* surf,
                          uint32_t serial) {
  wl_window_t* w = data;
  (void)surf;
  xdg_surface_ack_configure(w->xdg_surface, serial);
  w->configured = 1;
}

static const struct xdg_surface_listener xdg_surface_listener = {
    .configure = xdg_configure};

static void toplevel_configure(void* data, struct xdg_toplevel* t,
                               int32_t width, int32_t height,
                               struct wl_array* states) {
  wl_window_t* w = data;
  (void)t; (void)states;
  if (width > 0 && height > 0 &&
      (width != w->width || height != w->height)) {
    wl_shm_lcd_t* lcd = wlcd_create(w->pal, w->surface, width, height);
    if (lcd != NULL) {
      if (w->lcd != NULL) my_lcd_destroy(&w->lcd->base);
      w->lcd = lcd;
      w->width = width;
      w->height = height;
    }
  }
}

static void toplevel_close(void* data, struct xdg_toplevel* t) {
  wl_window_t* w = data;
  my_event_t event;
  (void)t;
  w->closed = 1;
  event = my_event_init(MY_EVENT_QUIT);
  wl_deliver(w->pal, &w->base, &event);
}

static const struct xdg_toplevel_listener toplevel_listener = {
    .configure = toplevel_configure, .close = toplevel_close};

static my_ret_t wwin_set_title(my_pal_window_t* win, const char* title) {
  xdg_toplevel_set_title(((wl_window_t*)win)->toplevel,
                         title != NULL ? title : "");
  return MY_RET_OK;
}

static my_ret_t wwin_resize(my_pal_window_t* win, int32_t w, int32_t h) {
  (void)win; (void)w; (void)h;
  return MY_RET_NOT_SUPPORTED;
}

static my_ret_t wwin_show(my_pal_window_t* win) {
  wl_window_t* x = (wl_window_t*)win;
  wl_surface_commit(x->surface);
  while (!x->configured)
    if (wl_display_dispatch(x->pal->display) < 0) return MY_RET_FAIL;
  return MY_RET_OK;
}

static my_ret_t wwin_get_size(my_pal_window_t* win, int32_t* w, int32_t* h) {
  wl_window_t* x = (wl_window_t*)win;
  if (w != NULL) *w = x->width;
  if (h != NULL) *h = x->height;
  return MY_RET_OK;
}

static my_lcd_t* wwin_get_lcd(my_pal_window_t* win) {
  return &((wl_window_t*)win)->lcd->base;
}

static void wgl_destroy_owned(wl_window_t* w) {
  if (w->gl == NULL) return;
  eglMakeCurrent(w->gl->display, EGL_NO_SURFACE, EGL_NO_SURFACE,
                 EGL_NO_CONTEXT);
  eglDestroyContext(w->gl->display, w->gl->context);
  eglDestroySurface(w->gl->display, w->gl->surface);
  eglTerminate(w->gl->display);
  wl_egl_window_destroy(w->gl->egl_window);
  my_mem_free(w->pal->allocator, w->gl);
  w->gl = NULL;
}

static void wwin_destroy(my_pal_window_t* win) {
  wl_window_t* w = (wl_window_t*)win;
  wl_pal_t* pal = w->pal;
  size_t i;
  wgl_destroy_owned(w);
  my_lcd_destroy(&w->lcd->base);
  xdg_toplevel_destroy(w->toplevel);
  xdg_surface_destroy(w->xdg_surface);
  wl_surface_destroy(w->surface);
  for (i = 0u; i < pal->window_count; i++)
    if (pal->windows[i] == w) {
      pal->windows[i] = pal->windows[pal->window_count - 1u];
      pal->window_count--;
      break;
    }
  my_mem_free(pal->allocator, w);
}

static my_ret_t wgl_make_current(my_pal_gl_t* gl) {
  wl_gl_t* g = (wl_gl_t*)gl;
  return eglMakeCurrent(g->display, g->surface, g->surface, g->context)
             ? MY_RET_OK
             : MY_RET_FAIL;
}

static my_ret_t wgl_swap(my_pal_gl_t* gl) {
  wl_gl_t* g = (wl_gl_t*)gl;
  return eglSwapBuffers(g->display, g->surface) ? MY_RET_OK : MY_RET_FAIL;
}

static my_ret_t wgl_size(my_pal_gl_t* gl, int32_t* w, int32_t* h) {
  wl_gl_t* g = (wl_gl_t*)gl;
  return eglQuerySurface(g->display, g->surface, EGL_WIDTH, w) &&
                 eglQuerySurface(g->display, g->surface, EGL_HEIGHT, h)
             ? MY_RET_OK
             : MY_RET_FAIL;
}

static bool wgl_multisample(my_pal_gl_t* gl) {
  wl_gl_t* g = (wl_gl_t*)gl;
  EGLint samples = 0;
  (void)eglQueryContext(g->display, g->context, EGL_SAMPLES, &samples);
  return samples > 0;
}

static void wgl_destroy(my_pal_gl_t* gl) {
  wgl_destroy_owned(((wl_gl_t*)gl)->owner);
}

static const my_pal_gl_vtable_t s_wgl_vtable = {
    wgl_make_current, wgl_swap, wgl_size, wgl_multisample, wgl_destroy};

static my_pal_gl_t* wwin_gl_enable(my_pal_window_t* win) {
  static const EGLint cfg_attribs[] = {EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
                                       EGL_RENDERABLE_TYPE,
                                       EGL_OPENGL_ES2_BIT, EGL_NONE};
  static const EGLint ctx_attribs[] = {EGL_CONTEXT_CLIENT_VERSION, 2,
                                       EGL_NONE};
  wl_window_t* w = (wl_window_t*)win;
  EGLDisplay display;
  EGLConfig config;
  EGLint count = 0;
  if (w->gl != NULL) return &w->gl->base;
  display = eglGetPlatformDisplay(EGL_PLATFORM_WAYLAND_KHR,
                                  (void*)w->pal->display, NULL);
  if (display == EGL_NO_DISPLAY || !eglInitialize(display, NULL, NULL) ||
      !eglBindAPI(EGL_OPENGL_ES_API) ||
      !eglChooseConfig(display, cfg_attribs, &config, 1, &count) || count < 1)
    return NULL;
  w->gl = (wl_gl_t*)my_mem_calloc(w->pal->allocator, 1u, sizeof(*w->gl));
  if (w->gl == NULL) return NULL;
  w->gl->base.vtable = &s_wgl_vtable;
  w->gl->owner = w;
  w->gl->display = display;
  w->gl->egl_window = wl_egl_window_create(w->surface, w->width, w->height);
  w->gl->surface = eglCreatePlatformWindowSurface(
      display, config, (void*)w->gl->egl_window, NULL);
  w->gl->context = eglCreateContext(display, config, EGL_NO_CONTEXT,
                                    ctx_attribs);
  if (w->gl->egl_window == NULL || w->gl->surface == EGL_NO_SURFACE ||
      w->gl->context == EGL_NO_CONTEXT) {
    wgl_destroy_owned(w);
    return NULL;
  }
  return &w->gl->base;
}

static void wwin_noop_bool(my_pal_window_t* win, bool on) {
  (void)win; (void)on;
}

static void wwin_noop_ime(my_pal_window_t* win, const char* utf8,
                          int32_t cursor, int32_t anchor) {
  (void)win; (void)utf8; (void)cursor; (void)anchor;
}

static void wwin_noop_spot(my_pal_window_t* win, int32_t x, int32_t y) {
  (void)win; (void)x; (void)y;
}

static my_ret_t wwin_begin_move(my_pal_window_t* win) {
  wl_window_t* w = (wl_window_t*)win;
  xdg_toplevel_move(w->toplevel, w->pal->seat, w->pal->pointer_serial);
  return MY_RET_OK;
}

static const my_pal_window_vtable_t s_wwin_vtable = {
    .set_title = wwin_set_title,
    .resize = wwin_resize,
    .show = wwin_show,
    .get_size = wwin_get_size,
    .get_lcd = wwin_get_lcd,
    .destroy = wwin_destroy,
    .gl_enable = wwin_gl_enable,
    .ime_set_enabled = wwin_noop_bool,
    .ime_set_surrounding = wwin_noop_ime,
    .ime_set_spot = wwin_noop_spot,
    .begin_move = wwin_begin_move};

/* ---------------- main loop + pal ---------------- */

static void loop_flush_queue(wl_loop_t* l) {
  queued_event_t* qe;
  while (atomic_flag_test_and_set_explicit(&l->lock, memory_order_acquire)) {
  }
  qe = l->head;
  l->head = NULL;
  l->tail = NULL;
  atomic_flag_clear_explicit(&l->lock, memory_order_release);
  while (qe != NULL) {
    queued_event_t* next = qe->next;
    if (atomic_load_explicit(&l->accepting, memory_order_relaxed) &&
        l->pal->handler != NULL)
      l->pal->handler(l->pal->handler_ctx, NULL, &qe->event);
    my_mem_free(l->allocator, qe);
    qe = next;
  }
}

static void loop_wake(wl_loop_t* l) {
  char byte = 1;
  ssize_t n = write(l->wake_pipe[1], &byte, 1u);
  (void)n;
}

static uint64_t wloop_timer_now(void* ctx) {
  (void)ctx;
  return wl_now_ms();
}

static my_ret_t wloop_run(my_pal_main_loop_t* loop) {
  wl_loop_t* l = (wl_loop_t*)loop;
  struct pollfd fds[2];
  atomic_store_explicit(&l->accepting, true, memory_order_relaxed);
  while (!atomic_load_explicit(&l->quit, memory_order_relaxed)) {
    int timeout;
    loop_flush_queue(l);
    wl_display_dispatch_pending(l->pal->display);
    wl_display_flush(l->pal->display);
    (void)my_timer_manager_fire(l->timers);
    timeout = (int)my_timer_manager_due_in_ms(l->timers);
    fds[0].fd = wl_display_get_fd(l->pal->display);
    fds[0].events = POLLIN;
    fds[1].fd = l->wake_pipe[0];
    fds[1].events = POLLIN;
    (void)poll(fds, 2u, timeout > 0 ? timeout : 8);
    if ((fds[1].revents & POLLIN) != 0) {
      char sink[16];
      ssize_t n = read(l->wake_pipe[0], sink, sizeof(sink));
      (void)n;
    }
  }
  loop_flush_queue(l);
  atomic_store_explicit(&l->accepting, false, memory_order_relaxed);
  return MY_RET_OK;
}

static my_ret_t wloop_quit(my_pal_main_loop_t* loop) {
  wl_loop_t* l = (wl_loop_t*)loop;
  atomic_store_explicit(&l->quit, true, memory_order_relaxed);
  loop_wake(l);
  return MY_RET_OK;
}

static my_ret_t wloop_post_event(my_pal_main_loop_t* loop,
                                 const my_event_t* event) {
  wl_loop_t* l = (wl_loop_t*)loop;
  queued_event_t* qe;
  if (event == NULL) return MY_RET_INVALID_PARAMS;
  qe = (queued_event_t*)my_mem_calloc(l->allocator, 1u, sizeof(*qe));
  if (qe == NULL) return MY_RET_OOM;
  qe->event = *event;
  while (atomic_flag_test_and_set_explicit(&l->lock, memory_order_acquire)) {
  }
  if (l->tail != NULL) l->tail->next = qe;
  if (l->head == NULL) l->head = qe;
  l->tail = qe;
  atomic_flag_clear_explicit(&l->lock, memory_order_release);
  loop_wake(l);
  return MY_RET_OK;
}

static uint32_t wloop_add_timer(my_pal_main_loop_t* loop,
                                my_timer_callback_t callback, void* ctx,
                                uint32_t interval_ms) {
  return my_timer_add(((wl_loop_t*)loop)->timers, callback, ctx,
                      interval_ms);
}

static my_ret_t wloop_remove_timer(my_pal_main_loop_t* loop, uint32_t id) {
  return my_timer_remove(((wl_loop_t*)loop)->timers, id);
}

static void wloop_destroy(my_pal_main_loop_t* loop) {
  wl_loop_t* l = (wl_loop_t*)loop;
  queued_event_t* qe = l->head;
  while (qe != NULL) {
    queued_event_t* next = qe->next;
    my_mem_free(l->allocator, qe);
    qe = next;
  }
  my_timer_manager_destroy(l->timers);
  close(l->wake_pipe[0]);
  close(l->wake_pipe[1]);
  my_mem_free(l->allocator, l);
}

static const my_pal_main_loop_vtable_t s_wloop_vtable = {
    .run = wloop_run,
    .quit = wloop_quit,
    .post_event = wloop_post_event,
    .add_timer = wloop_add_timer,
    .remove_timer = wloop_remove_timer,
    .destroy = wloop_destroy};

static my_pal_window_t* wpal_window_create(my_pal_t* pal, int32_t w,
                                           int32_t h, const char* title) {
  wl_pal_t* p = (wl_pal_t*)pal;
  wl_window_t* win;
  if (w <= 0 || h <= 0 || p->window_count >= 8u) return NULL;
  win = (wl_window_t*)my_mem_calloc(p->allocator, 1u, sizeof(*win));
  if (win == NULL) return NULL;
  win->base.vtable = &s_wwin_vtable;
  win->pal = p;
  win->width = w;
  win->height = h;
  win->surface = wl_compositor_create_surface(p->compositor);
  win->lcd = wlcd_create(p, win->surface, w, h);
  if (win->lcd == NULL) {
    wl_surface_destroy(win->surface);
    my_mem_free(p->allocator, win);
    return NULL;
  }
  win->xdg_surface = xdg_wm_base_get_xdg_surface(p->wm_base, win->surface);
  xdg_surface_add_listener(win->xdg_surface, &xdg_surface_listener, win);
  win->toplevel = xdg_surface_get_toplevel(win->xdg_surface);
  xdg_toplevel_add_listener(win->toplevel, &toplevel_listener, win);
  (void)wwin_set_title(&win->base, title != NULL ? title : "");
  p->windows[p->window_count++] = win;
  return &win->base;
}

static my_pal_main_loop_t* wpal_loop_create(my_pal_t* pal) {
  wl_pal_t* p = (wl_pal_t*)pal;
  wl_loop_t* l = (wl_loop_t*)my_mem_calloc(p->allocator, 1u, sizeof(*l));
  if (l == NULL) return NULL;
  l->base.vtable = &s_wloop_vtable;
  l->pal = p;
  l->allocator = p->allocator;
  if (pipe(l->wake_pipe) != 0) {
    my_mem_free(p->allocator, l);
    return NULL;
  }
  atomic_flag_clear_explicit(&l->lock, memory_order_release);
  l->timers = my_timer_manager_create(p->allocator, wloop_timer_now, l);
  if (l->timers == NULL) {
    close(l->wake_pipe[0]);
    close(l->wake_pipe[1]);
    my_mem_free(p->allocator, l);
    return NULL;
  }
  return &l->base;
}

static uint64_t wpal_time_ms(my_pal_t* pal) {
  (void)pal;
  return wl_now_ms();
}

static my_ret_t wpal_set_handler(my_pal_t* pal,
                                 my_pal_event_handler_t handler,
                                 void* ctx) {
  wl_pal_t* p = (wl_pal_t*)pal;
  p->handler = handler;
  p->handler_ctx = ctx;
  return MY_RET_OK;
}

static my_ret_t wpal_clipboard_set(my_pal_t* pal, const char* text) {
  (void)pal; (void)text;
  return MY_RET_NOT_SUPPORTED;
}

static my_ret_t wpal_clipboard_get(my_pal_t* pal, char* buf, size_t size) {
  (void)pal; (void)buf; (void)size;
  return MY_RET_NOT_SUPPORTED;
}

static float wpal_scale(my_pal_t* pal) {
  (void)pal;
  return 1.0f;
}

static void wpal_destroy(my_pal_t* pal) {
  wl_pal_t* p = (wl_pal_t*)pal;
  while (p->window_count > 0u)
    wwin_destroy(&p->windows[0]->base);
  if (p->seat != NULL) wl_seat_destroy(p->seat);
  if (p->wm_base != NULL) xdg_wm_base_destroy(p->wm_base);
  if (p->shm != NULL) wl_shm_destroy(p->shm);
  if (p->compositor != NULL) wl_compositor_destroy(p->compositor);
  wl_registry_destroy(p->registry);
  wl_display_disconnect(p->display);
  my_mem_free(p->allocator, p);
}

static bool wpal_needs_csd(my_pal_t* pal) {
  (void)pal;
  return true;
}

static const my_pal_vtable_t s_wpal_vtable = {
    .window_create = wpal_window_create,
    .main_loop_create = wpal_loop_create,
    .time_now_ms = wpal_time_ms,
    .set_event_handler = wpal_set_handler,
    .clipboard_set_text = wpal_clipboard_set,
    .clipboard_get_text = wpal_clipboard_get,
    .get_scale_factor = wpal_scale,
    .destroy = wpal_destroy,
    .needs_client_decoration = wpal_needs_csd};

my_pal_t* my_pal_wayland_create(const my_allocator_t* allocator) {
  wl_pal_t* p;
  struct wl_display* display = wl_display_connect(NULL);
  if (display == NULL) return NULL;
  p = (wl_pal_t*)my_mem_calloc(allocator, 1u, sizeof(*p));
  if (p == NULL) {
    wl_display_disconnect(display);
    return NULL;
  }
  p->base.vtable = &s_wpal_vtable;
  p->allocator = allocator;
  p->display = display;
  p->registry = wl_display_get_registry(display);
  wl_registry_add_listener(p->registry, &registry_listener, p);
  wl_display_roundtrip(display);
  if (p->compositor == NULL || p->shm == NULL || p->wm_base == NULL) {
    wpal_destroy(&p->base);
    return NULL;
  }
  xdg_wm_base_add_listener(p->wm_base, &wm_base_listener, p);
  if (p->seat != NULL)
    wl_seat_add_listener(p->seat, &seat_listener, p);
  return &p->base;
}
