/**
 * @file my_pal_x11.c
 * @brief X11 PAL port: XPending pump, XImage lcd presentation, EGL GLES2.
 */
#define _POSIX_C_SOURCE 200809L
#include "mypal/x11/my_pal_x11.h"

#include "myr/my_lcd_mem.h"
#include "mypal/my_timer.h"

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/keysym.h>
#include <X11/cursorfont.h>

#include <EGL/egl.h>
#include <EGL/eglext.h>
#ifndef EGL_PLATFORM_X11_KHR
#define EGL_PLATFORM_X11_KHR 0x31D5
#endif

#include <poll.h>
#include <stdatomic.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct x11_pal_t {
  my_pal_t base;
  const my_allocator_t* allocator;
  Display* display;
  Atom wm_delete;
  Atom wake;
  Window wake_window;
  my_pal_event_handler_t handler;
  void* handler_ctx;
} x11_pal_t;

typedef struct x11_lcd_t {
  my_lcd_t base;
  x11_pal_t* pal;
  my_lcd_t* mem;
  Window window;
  GC gc;
  XImage* image;
  int32_t width;
  int32_t height;
} x11_lcd_t;

typedef struct x11_window_t {
  my_pal_window_t base;
  x11_pal_t* pal;
  Window window;
  x11_lcd_t* lcd;
  struct x11_gl_t* gl;
  int32_t width;
  int32_t height;
  char* title;
} x11_window_t;

typedef struct x11_gl_t {
  my_pal_gl_t base;
  x11_window_t* owner;
  EGLDisplay display;
  EGLSurface surface;
  EGLContext context;
} x11_gl_t;

typedef struct queued_event_t {
  my_event_t event;
  struct queued_event_t* next;
} queued_event_t;

typedef struct x11_loop_t {
  my_pal_main_loop_t base;
  x11_pal_t* pal;
  const my_allocator_t* allocator;
  queued_event_t* head;
  queued_event_t* tail;
  my_timer_manager_t* timers;
  atomic_flag lock;
  atomic_bool accepting;
  atomic_bool quit;
} x11_loop_t;

static uint64_t x11_now_ms(void) {
  struct timespec ts;
  (void)clock_gettime(CLOCK_MONOTONIC, &ts);
  return (uint64_t)ts.tv_sec * 1000u + (uint64_t)ts.tv_nsec / 1000000u;
}

static x11_window_t* window_of(Display* dpy, Window target,
                               x11_pal_t* pal);
static void registry_remove(x11_window_t* w);

static void x11_deliver(x11_pal_t* pal, my_pal_window_t* window,
                        const my_event_t* event) {
  if (pal->handler != NULL) pal->handler(pal->handler_ctx, window, event);
}

/* ---------------- lcd wrapper ---------------- */

static uint32_t xlcd_width(my_lcd_t* lcd) {
  return my_lcd_get_width(((x11_lcd_t*)lcd)->mem);
}

static uint32_t xlcd_height(my_lcd_t* lcd) {
  return my_lcd_get_height(((x11_lcd_t*)lcd)->mem);
}

static my_pixel_format_t xlcd_format(my_lcd_t* lcd) {
  return my_lcd_get_format(((x11_lcd_t*)lcd)->mem);
}

static my_ret_t xlcd_begin(my_lcd_t* lcd, const my_rect_t* dirty) {
  return my_lcd_begin_frame(((x11_lcd_t*)lcd)->mem, dirty);
}

static my_ret_t xlcd_end(my_lcd_t* lcd) {
  x11_lcd_t* x = (x11_lcd_t*)lcd;
  my_ret_t r = my_lcd_end_frame(x->mem);
  if (r != MY_RET_OK) return r;
  if (x->image != NULL) {
    /* data is borrowed from the lcd buffer: free the struct only */
    XFree((char*)x->image);
    x->image = NULL;
  }
  x->image = XCreateImage(x->pal->display, NULL, 24, ZPixmap, 0,
                          (char*)my_lcd_get_buffer(x->mem), (unsigned)x->width,
                          (unsigned)x->height, 32,
                          (int)my_lcd_get_stride(x->mem));
  if (x->image == NULL) return MY_RET_FAIL;
  XPutImage(x->pal->display, x->window, x->gc, x->image, 0, 0, 0, 0,
            (unsigned)x->width, (unsigned)x->height);
  XFlush(x->pal->display);
  return MY_RET_OK;
}

static my_ret_t xlcd_draw_pixels(my_lcd_t* lcd, const void* pixels,
                                 int32_t px, int32_t py, uint32_t w,
                                 uint32_t h) {
  return my_lcd_draw_pixels(((x11_lcd_t*)lcd)->mem, pixels, px, py, w, h);
}

static my_ret_t xlcd_fill_rect(my_lcd_t* lcd, const my_rect_t* rect,
                               my_color_t color) {
  return my_lcd_fill_rect(((x11_lcd_t*)lcd)->mem, rect, color);
}

static my_ret_t xlcd_blend_span(my_lcd_t* lcd, int32_t x, int32_t y,
                                const uint8_t* alpha, int32_t n,
                                my_color_t color) {
  return my_lcd_blend_span(((x11_lcd_t*)lcd)->mem, x, y, alpha, n, color);
}

static uint8_t* xlcd_buffer(my_lcd_t* lcd) {
  return my_lcd_get_buffer(((x11_lcd_t*)lcd)->mem);
}

static uint32_t xlcd_stride(my_lcd_t* lcd) {
  return my_lcd_get_stride(((x11_lcd_t*)lcd)->mem);
}

static void xlcd_destroy(my_lcd_t* lcd) {
  x11_lcd_t* x = (x11_lcd_t*)lcd;
  if (x->image != NULL) XFree((char*)x->image);
  my_lcd_destroy(x->mem);
  my_mem_free(x->pal->allocator, x);
}

static const my_lcd_vtable_t s_xlcd_vtable = {
    xlcd_width,  xlcd_height, xlcd_format,  xlcd_begin,
    xlcd_end,    xlcd_draw_pixels, xlcd_fill_rect, xlcd_blend_span,
    xlcd_destroy, xlcd_buffer, xlcd_stride};

static x11_lcd_t* xlcd_create(x11_pal_t* pal, Window window, GC gc,
                              int32_t w, int32_t h) {
  x11_lcd_t* x = (x11_lcd_t*)my_mem_calloc(pal->allocator, 1u, sizeof(*x));
  if (x == NULL) return NULL;
  x->base.vtable = &s_xlcd_vtable;
  x->pal = pal;
  x->window = window;
  x->gc = gc;
  x->width = w;
  x->height = h;
  x->mem = my_lcd_mem_create(pal->allocator, (uint32_t)w, (uint32_t)h,
                             MY_PIXEL_FORMAT_BGRA8888);
  if (x->mem == NULL) {
    my_mem_free(pal->allocator, x);
    return NULL;
  }
  return x;
}

/* ---------------- window ---------------- */



static my_ret_t xwin_set_title(my_pal_window_t* win, const char* title) {
  x11_window_t* w = (x11_window_t*)win;
  char* copy = NULL;
  if (title != NULL) {
    copy = (char*)my_mem_alloc(w->pal->allocator, strlen(title) + 1u);
    if (copy == NULL) return MY_RET_OOM;
    memcpy(copy, title, strlen(title) + 1u);
  }
  XStoreName(w->pal->display, w->window, title != NULL ? title : "");
  my_mem_free(w->pal->allocator, w->title);
  w->title = copy;
  return MY_RET_OK;
}

static void xwin_realloc_lcd(x11_window_t* w, int32_t width, int32_t height) {
  x11_lcd_t* lcd = xlcd_create(w->pal, w->window,
                               XCreateGC(w->pal->display, w->window, 0, NULL),
                               width, height);
  if (lcd == NULL) return;
  if (w->lcd != NULL) my_lcd_destroy(&w->lcd->base);
  w->lcd = lcd;
  w->width = width;
  w->height = height;
}

static my_ret_t xwin_resize(my_pal_window_t* win, int32_t w, int32_t h) {
  x11_window_t* x = (x11_window_t*)win;
  if (w <= 0 || h <= 0) return MY_RET_INVALID_PARAMS;
  XResizeWindow(x->pal->display, x->window, (unsigned)w, (unsigned)h);
  xwin_realloc_lcd(x, w, h);
  return MY_RET_OK;
}

static my_ret_t xwin_show(my_pal_window_t* win) {
  x11_window_t* x = (x11_window_t*)win;
  XMapRaised(x->pal->display, x->window);
  XFlush(x->pal->display);
  return MY_RET_OK;
}

static my_ret_t xwin_get_size(my_pal_window_t* win, int32_t* w, int32_t* h) {
  x11_window_t* x = (x11_window_t*)win;
  if (w != NULL) *w = x->width;
  if (h != NULL) *h = x->height;
  return MY_RET_OK;
}

static my_lcd_t* xwin_get_lcd(my_pal_window_t* win) {
  return &((x11_window_t*)win)->lcd->base;
}

static void xgl_destroy_owned(x11_window_t* w) {
  if (w->gl == NULL) return;
  eglMakeCurrent(w->gl->display, EGL_NO_SURFACE, EGL_NO_SURFACE,
                 EGL_NO_CONTEXT);
  eglDestroyContext(w->gl->display, w->gl->context);
  eglDestroySurface(w->gl->display, w->gl->surface);
  my_mem_free(w->pal->allocator, w->gl);
  w->gl = NULL;
}

static void xwin_destroy(my_pal_window_t* win) {
  x11_window_t* w = (x11_window_t*)win;
  registry_remove(w);
  xgl_destroy_owned(w);
  my_lcd_destroy(&w->lcd->base);
  XDestroyWindow(w->pal->display, w->window);
  XFlush(w->pal->display);
  my_mem_free(w->pal->allocator, w->title);
  my_mem_free(w->pal->allocator, w);
}

static my_ret_t xgl_make_current(my_pal_gl_t* gl) {
  x11_gl_t* g = (x11_gl_t*)gl;
  return eglMakeCurrent(g->display, g->surface, g->surface, g->context)
             ? MY_RET_OK
             : MY_RET_FAIL;
}

static my_ret_t xgl_swap(my_pal_gl_t* gl) {
  x11_gl_t* g = (x11_gl_t*)gl;
  return eglSwapBuffers(g->display, g->surface) ? MY_RET_OK : MY_RET_FAIL;
}

static my_ret_t xgl_size(my_pal_gl_t* gl, int32_t* w, int32_t* h) {
  x11_gl_t* g = (x11_gl_t*)gl;
  return eglQuerySurface(g->display, g->surface, EGL_WIDTH, w) &&
                 eglQuerySurface(g->display, g->surface, EGL_HEIGHT, h)
             ? MY_RET_OK
             : MY_RET_FAIL;
}

static bool xgl_multisample(my_pal_gl_t* gl) {
  x11_gl_t* g = (x11_gl_t*)gl;
  EGLint samples = 0;
  (void)eglQueryContext(g->display, g->context, EGL_SAMPLES, &samples);
  return samples > 0;
}

static void xgl_destroy(my_pal_gl_t* gl) {
  xgl_destroy_owned(((x11_gl_t*)gl)->owner);
}

static const my_pal_gl_vtable_t s_xgl_vtable = {
    xgl_make_current, xgl_swap, xgl_size, xgl_multisample, xgl_destroy};

static my_pal_gl_t* xwin_gl_enable(my_pal_window_t* win) {
  static const EGLint cfg_attribs[] = {EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
                                       EGL_RENDERABLE_TYPE,
                                       EGL_OPENGL_ES2_BIT, EGL_NONE};
  static const EGLint ctx_attribs[] = {EGL_CONTEXT_CLIENT_VERSION, 2,
                                       EGL_NONE};
  x11_window_t* w = (x11_window_t*)win;
  EGLDisplay display;
  EGLConfig config;
  EGLint count = 0;
  EGLint visual_id = 0;
  XVisualInfo vi;
  if (w->gl != NULL) return &w->gl->base;
  display = eglGetPlatformDisplay(EGL_PLATFORM_X11_KHR,
                                  (void*)w->pal->display, NULL);
  if (display == EGL_NO_DISPLAY || !eglInitialize(display, NULL, NULL) ||
      !eglBindAPI(EGL_OPENGL_ES_API) ||
      !eglChooseConfig(display, cfg_attribs, &config, 1, &count) || count < 1)
    return NULL;
  if (eglGetConfigAttrib(display, config, EGL_NATIVE_VISUAL_ID,
                         &visual_id) &&
      XMatchVisualInfo(w->pal->display,
                       DefaultScreen(w->pal->display), (int)visual_id,
                       TrueColor, &vi)) {
    XSetWindowAttributes swa;
    Window replacement;
    swa.colormap = XCreateColormap(
        w->pal->display,
        RootWindow(w->pal->display, DefaultScreen(w->pal->display)),
        vi.visual, AllocNone);
    swa.border_pixel = 0;
    swa.event_mask =
        ExposureMask | PointerMotionMask | ButtonPressMask |
        KeyPressMask | StructureNotifyMask;
    replacement = XCreateWindow(
        w->pal->display,
        RootWindow(w->pal->display, DefaultScreen(w->pal->display)), 0,
        0, (unsigned)w->width, (unsigned)w->height, 0, vi.depth,
        InputOutput, vi.visual, CWColormap | CWBorderPixel | CWEventMask,
        &swa);
    if (replacement != None) {
      XSetWMProtocols(w->pal->display, replacement, &w->pal->wm_delete, 1);
      XDestroyWindow(w->pal->display, w->window);
      w->window = replacement;
      xwin_realloc_lcd(w, w->width, w->height);
      (void)XMapRaised(w->pal->display, w->window);
      XFlush(w->pal->display);
    }
  }
  w->gl = (x11_gl_t*)my_mem_calloc(w->pal->allocator, 1u, sizeof(*w->gl));
  if (w->gl == NULL) return NULL;
  w->gl->base.vtable = &s_xgl_vtable;
  w->gl->owner = w;
  w->gl->display = display;
  w->gl->surface = eglCreateWindowSurface(display, config,
                                          (EGLNativeWindowType)w->window,
                                          NULL);
  w->gl->context = eglCreateContext(display, config, EGL_NO_CONTEXT,
                                    ctx_attribs);
  if (w->gl->surface == EGL_NO_SURFACE ||
      w->gl->context == EGL_NO_CONTEXT) {
    xgl_destroy_owned(w);
    return NULL;
  }
  return &w->gl->base;
}

static my_ret_t xwin_move(my_pal_window_t* win, int32_t x, int32_t y) {
  x11_window_t* w = (x11_window_t*)win;
  XMoveWindow(w->pal->display, w->window, x, y);
  return MY_RET_OK;
}

static void xwin_noop_bool(my_pal_window_t* win, bool on) {
  (void)win; (void)on;
}

static void xwin_noop_ime(my_pal_window_t* win, const char* utf8,
                          int32_t cursor, int32_t anchor) {
  (void)win; (void)utf8; (void)cursor; (void)anchor;
}

static void xwin_noop_spot(my_pal_window_t* win, int32_t x, int32_t y) {
  (void)win; (void)x; (void)y;
}

static my_ret_t xwin_set_cursor(my_pal_window_t* win, my_cursor_t cursor) {
  static const unsigned int shapes[3] = {XC_left_ptr, XC_xterm,
                                         XC_hand2};
  x11_window_t* w = (x11_window_t*)win;
  Cursor c;
  if ((unsigned)cursor > 2u) return MY_RET_INVALID_PARAMS;
  c = XCreateFontCursor(w->pal->display, shapes[cursor]);
  if (c == None) return MY_RET_FAIL;
  XDefineCursor(w->pal->display, w->window, c);
  XFreeCursor(w->pal->display, c);
  return MY_RET_OK;
}

static const my_pal_window_vtable_t s_xwin_vtable = {
    .set_title = xwin_set_title,
    .resize = xwin_resize,
    .show = xwin_show,
    .get_size = xwin_get_size,
    .get_lcd = xwin_get_lcd,
    .destroy = xwin_destroy,
    .gl_enable = xwin_gl_enable,
    .ime_set_enabled = xwin_noop_bool,
    .ime_set_surrounding = xwin_noop_ime,
    .ime_set_spot = xwin_noop_spot,
    .move = xwin_move,
    .set_cursor = xwin_set_cursor};

/* ---------------- events + main loop ---------------- */

static void x11_translate(x11_pal_t* pal, x11_window_t* w, XEvent* ev) {
  my_event_t event;
  if (w == NULL) return;
  if (ev->type == MotionNotify) {
    event = my_event_init(MY_EVENT_POINTER_MOVE);
    event.u.pointer.x = ev->xmotion.x;
    event.u.pointer.y = ev->xmotion.y;
    x11_deliver(pal, &w->base, &event);
  } else if (ev->type == ButtonPress) {
    if (ev->xbutton.button == Button4 || ev->xbutton.button == Button5) {
      event = my_event_init(MY_EVENT_POINTER_WHEEL);
      event.u.pointer.x = ev->xbutton.x;
      event.u.pointer.y = ev->xbutton.y;
      event.u.pointer.delta =
          ev->xbutton.button == Button4 ? 1 : -1;
      x11_deliver(pal, &w->base, &event);
    } else {
      event = my_event_init(MY_EVENT_POINTER_DOWN);
      event.u.pointer.x = ev->xbutton.x;
      event.u.pointer.y = ev->xbutton.y;
      event.u.pointer.button = 1u;
      x11_deliver(pal, &w->base, &event);
    }
  } else if (ev->type == KeyPress) {
    KeySym k = XLookupKeysym(&ev->xkey, 0);
    char buf[8];
    int n = XLookupString(&ev->xkey, buf, sizeof(buf), NULL, NULL);
    if (n > 0 && (unsigned char)buf[0] >= ' ' &&
        (unsigned char)buf[0] <= '~') {
      event = my_event_init(MY_EVENT_KEY_DOWN);
      event.u.key.key = (uint32_t)(unsigned char)buf[0];
      x11_deliver(pal, &w->base, &event);
    } else if (k == XK_Left || k == XK_Right || k == XK_Up ||
               k == XK_Down) {
      event = my_event_init(MY_EVENT_KEY_DOWN);
      event.u.key.key =
          k == XK_Left ? MY_KEY_LEFT
                       : k == XK_Right ? MY_KEY_RIGHT
                                       : k == XK_Up ? MY_KEY_UP
                                                    : MY_KEY_DOWN;
      x11_deliver(pal, &w->base, &event);
    }
  } else if (ev->type == ClientMessage &&
             (Atom)ev->xclient.data.l[0] == pal->wm_delete) {
    event = my_event_init(MY_EVENT_QUIT);
    x11_deliver(pal, &w->base, &event);
  } else if (ev->type == Expose || ev->type == ConfigureNotify) {
    if (ev->type == ConfigureNotify &&
        (ev->xconfigure.width != w->width ||
         ev->xconfigure.height != w->height)) {
      xwin_realloc_lcd(w, ev->xconfigure.width, ev->xconfigure.height);
      event = my_event_init(MY_EVENT_RESIZE);
      event.u.resize.w = ev->xconfigure.width;
      event.u.resize.h = ev->xconfigure.height;
      x11_deliver(pal, &w->base, &event);
    } else {
      event = my_event_init(MY_EVENT_PAINT);
      x11_deliver(pal, &w->base, &event);
    }
  }
}

static void loop_flush_queue(x11_loop_t* l) {
  queued_event_t* qe;
  while (atomic_flag_test_and_set_explicit(&l->lock,
                                            memory_order_acquire)) {
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

static my_ret_t xloop_run(my_pal_main_loop_t* loop) {
  x11_loop_t* l = (x11_loop_t*)loop;
  x11_pal_t* pal = l->pal;
  atomic_store_explicit(&l->accepting, true, memory_order_relaxed);
  while (!atomic_load_explicit(&l->quit, memory_order_relaxed)) {
    XEvent ev;
    loop_flush_queue(l);
    while (XPending(pal->display)) {
      XNextEvent(pal->display, &ev);
      if (ev.type == ClientMessage &&
          ev.xclient.window == pal->wake_window &&
          (Atom)ev.xclient.data.l[0] == pal->wake)
        continue;
      if (ev.xany.window == pal->wake_window) continue;
      {
        x11_window_t* w = window_of(pal->display, ev.xany.window, pal);
        if (w != NULL) x11_translate(pal, w, &ev);
      }
    }
    (void)my_timer_manager_fire(l->timers);
    {
      struct pollfd pfd;
      int timeout = (int)my_timer_manager_due_in_ms(l->timers);
      pfd.fd = ConnectionNumber(pal->display);
      pfd.events = POLLIN;
      (void)poll(&pfd, 1u, timeout > 0 ? timeout : 8);
    }
  }
  loop_flush_queue(l);
  atomic_store_explicit(&l->accepting, false, memory_order_relaxed);
  return MY_RET_OK;
}

static my_ret_t xloop_quit(my_pal_main_loop_t* loop) {
  x11_loop_t* l = (x11_loop_t*)loop;
  XClientMessageEvent wake;
  atomic_store_explicit(&l->quit, true, memory_order_relaxed);
  memset(&wake, 0, sizeof(wake));
  wake.type = ClientMessage;
  wake.display = l->pal->display;
  wake.window = l->pal->wake_window;
  wake.message_type = l->pal->wake;
  wake.format = 32;
  (void)XSendEvent(l->pal->display, l->pal->wake_window, False, 0,
                   (XEvent*)&wake);
  XFlush(l->pal->display);
  return MY_RET_OK;
}

static my_ret_t xloop_post_event(my_pal_main_loop_t* loop,
                                  const my_event_t* event) {
  x11_loop_t* l = (x11_loop_t*)loop;
  queued_event_t* qe;
  if (event == NULL) return MY_RET_INVALID_PARAMS;
  qe = (queued_event_t*)my_mem_calloc(l->allocator, 1u, sizeof(*qe));
  if (qe == NULL) return MY_RET_OOM;
  qe->event = *event;
  while (atomic_flag_test_and_set_explicit(&l->lock,
                                            memory_order_acquire)) {
  }
  if (l->tail != NULL) l->tail->next = qe;
  if (l->head == NULL) l->head = qe;
  l->tail = qe;
  atomic_flag_clear_explicit(&l->lock, memory_order_release);
  xloop_quit(loop);
  return MY_RET_OK;
}

static uint64_t xloop_timer_now(void* ctx) {
  (void)ctx;
  return x11_now_ms();
}

static uint32_t xloop_add_timer(my_pal_main_loop_t* loop,
                                my_timer_callback_t callback, void* ctx,
                                uint32_t interval_ms) {
  return my_timer_add(((x11_loop_t*)loop)->timers, callback, ctx,
                      interval_ms);
}

static my_ret_t xloop_remove_timer(my_pal_main_loop_t* loop, uint32_t id) {
  return my_timer_remove(((x11_loop_t*)loop)->timers, id);
}

static void xloop_destroy(my_pal_main_loop_t* loop) {
  x11_loop_t* l = (x11_loop_t*)loop;
  queued_event_t* qe = l->head;
  while (qe != NULL) {
    queued_event_t* next = qe->next;
    my_mem_free(l->allocator, qe);
    qe = next;
  }
  my_timer_manager_destroy(l->timers);
  my_mem_free(l->allocator, l);
}

static const my_pal_main_loop_vtable_t s_xloop_vtable = {
    .run = xloop_run,
    .quit = xloop_quit,
    .post_event = xloop_post_event,
    .add_timer = xloop_add_timer,
    .remove_timer = xloop_remove_timer,
    .destroy = xloop_destroy};

/* ---------------- pal ---------------- */

#define X11_MAX_WINDOWS 16u

typedef struct x11_registry_t {
  x11_window_t* windows[X11_MAX_WINDOWS];
  size_t count;
} x11_registry_t;

static x11_registry_t s_registry;

static void registry_add(x11_window_t* w) {
  if (s_registry.count < X11_MAX_WINDOWS) {
    s_registry.windows[s_registry.count++] = w;
  }
}

static void registry_remove(x11_window_t* w) {
  size_t i;
  for (i = 0u; i < s_registry.count; i++) {
    if (s_registry.windows[i] == w) {
      s_registry.windows[i] = s_registry.windows[s_registry.count - 1u];
      s_registry.count--;
      return;
    }
  }
}

static x11_window_t* window_of(Display* dpy, Window target,
                               x11_pal_t* pal) {
  size_t i;
  (void)dpy;
  (void)pal;
  for (i = 0u; i < s_registry.count; i++)
    if (s_registry.windows[i]->window == target)
      return s_registry.windows[i];
  return NULL;
}

static my_pal_window_t* xpal_window_create(my_pal_t* pal, int32_t w,
                                           int32_t h, const char* title) {
  x11_pal_t* p = (x11_pal_t*)pal;
  x11_window_t* win;
  int screen;
  if (w <= 0 || h <= 0) return NULL;
  win = (x11_window_t*)my_mem_calloc(p->allocator, 1u, sizeof(*win));
  if (win == NULL) return NULL;
  win->base.vtable = &s_xwin_vtable;
  win->pal = p;
  win->width = w;
  win->height = h;
  screen = DefaultScreen(p->display);
  win->window = XCreateSimpleWindow(
      p->display, RootWindow(p->display, screen), 0, 0, (unsigned)w, (unsigned)h, 0,
      BlackPixel(p->display, screen), WhitePixel(p->display, screen));
  XSelectInput(p->display, win->window,
               ExposureMask | PointerMotionMask | ButtonPressMask |
                   KeyPressMask | StructureNotifyMask);
  XSetWMProtocols(p->display, win->window, &p->wm_delete, 1);
  xwin_realloc_lcd(win, w, h);
  if (win->lcd == NULL) {
    XDestroyWindow(p->display, win->window);
    my_mem_free(p->allocator, win);
    return NULL;
  }
  registry_add(win);
  (void)xwin_set_title(&win->base, title != NULL ? title : "");
  return &win->base;
}

static my_pal_main_loop_t* xpal_loop_create(my_pal_t* pal) {
  x11_pal_t* p = (x11_pal_t*)pal;
  x11_loop_t* l = (x11_loop_t*)my_mem_calloc(p->allocator, 1u, sizeof(*l));
  if (l == NULL) return NULL;
  l->base.vtable = &s_xloop_vtable;
  l->pal = p;
  l->allocator = p->allocator;
  atomic_flag_clear_explicit(&l->lock, memory_order_release);
  l->timers = my_timer_manager_create(p->allocator, xloop_timer_now, l);
  if (l->timers == NULL) {
    my_mem_free(p->allocator, l);
    return NULL;
  }
  return &l->base;
}

static uint64_t xpal_time_ms(my_pal_t* pal) {
  (void)pal;
  return x11_now_ms();
}

static my_ret_t xpal_set_handler(my_pal_t* pal,
                                 my_pal_event_handler_t handler,
                                 void* ctx) {
  x11_pal_t* p = (x11_pal_t*)pal;
  p->handler = handler;
  p->handler_ctx = ctx;
  return MY_RET_OK;
}

static my_ret_t xpal_clipboard_set(my_pal_t* pal, const char* text) {
  (void)pal; (void)text;
  return MY_RET_NOT_SUPPORTED;
}

static my_ret_t xpal_clipboard_get(my_pal_t* pal, char* buf, size_t size) {
  (void)pal; (void)buf; (void)size;
  return MY_RET_NOT_SUPPORTED;
}

static float xpal_scale(my_pal_t* pal) {
  (void)pal;
  return 1.0f;
}

static void xpal_destroy(my_pal_t* pal) {
  x11_pal_t* p = (x11_pal_t*)pal;
  while (s_registry.count > 0u)
    xwin_destroy(&s_registry.windows[0]->base);
  XDestroyWindow(p->display, p->wake_window);
  XCloseDisplay(p->display);
  my_mem_free(p->allocator, p);
}

static const my_pal_vtable_t s_xpal_vtable = {
    .window_create = xpal_window_create,
    .main_loop_create = xpal_loop_create,
    .time_now_ms = xpal_time_ms,
    .set_event_handler = xpal_set_handler,
    .clipboard_set_text = xpal_clipboard_set,
    .clipboard_get_text = xpal_clipboard_get,
    .get_scale_factor = xpal_scale,
    .destroy = xpal_destroy};

my_pal_t* my_pal_x11_create(const my_allocator_t* allocator) {
  x11_pal_t* p;
  Display* display = XOpenDisplay(NULL);
  if (display == NULL) return NULL;
  p = (x11_pal_t*)my_mem_calloc(allocator, 1u, sizeof(*p));
  if (p == NULL) {
    XCloseDisplay(display);
    return NULL;
  }
  p->base.vtable = &s_xpal_vtable;
  p->allocator = allocator;
  p->display = display;
  p->wm_delete = XInternAtom(display, "WM_DELETE_WINDOW", False);
  p->wake = XInternAtom(display, "MYUI_PAL_WAKE", False);
  {
    int screen = DefaultScreen(display);
    p->wake_window = XCreateSimpleWindow(
        display, RootWindow(display, screen), 0, 0, 1, 1, 0, 0, 0);
    XSelectInput(display, p->wake_window, 0);
  }
  return &p->base;
}
