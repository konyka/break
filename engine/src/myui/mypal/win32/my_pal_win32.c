/**
 * @file my_pal_win32.c
 * @brief Win32 PAL port: message-pump windows, DIB lcd, WGL GLES2.
 *        Compile-targeted (no Windows host in CI); follows the frozen
 *        my_pal.h contract. NULL slots: clipboard, gl_enable_api,
 *        vk_create_surface, set_cursor, ime, begin_move.
 */
#include "mypal/win32/my_pal_win32.h"

#include "myr/my_lcd_mem.h"
#include "mypal/my_timer.h"

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <windowsx.h>
#include <GL/gl.h>

#include <stdatomic.h>
#include <stdint.h>
#include <string.h>

typedef struct win_pal_t {
  my_pal_t base;
  const my_allocator_t* allocator;
  my_pal_event_handler_t handler;
  void* handler_ctx;
} win_pal_t;

typedef struct win_lcd_t {
  my_lcd_t base;
  win_pal_t* pal;
  my_lcd_t* mem;
  HWND hwnd;
  HBITMAP dib;
  HDC dib_dc;
  void* bits;
  int32_t width;
  int32_t height;
} win_lcd_t;

typedef struct win_window_t {
  my_pal_window_t base;
  win_pal_t* pal;
  HWND hwnd;
  win_lcd_t* lcd;
  struct win_gl_t* gl;
  int32_t width;
  int32_t height;
} win_window_t;

typedef struct win_gl_t {
  my_pal_gl_t base;
  win_window_t* owner;
  HDC dc;
  HGLRC ctx;
} win_gl_t;

typedef struct queued_event_t {
  my_event_t event;
  struct queued_event_t* next;
} queued_event_t;

typedef struct win_loop_t {
  my_pal_main_loop_t base;
  win_pal_t* pal;
  const my_allocator_t* allocator;
  queued_event_t* head;
  queued_event_t* tail;
  my_timer_manager_t* timers;
  atomic_flag lock;
  atomic_bool accepting;
  atomic_bool quit;
} win_loop_t;

#define W32_MAX_WINDOWS 16u
static win_window_t* s_windows[W32_MAX_WINDOWS];
static size_t s_window_count;

static win_window_t* find_window(HWND hwnd) {
  size_t i;
  for (i = 0u; i < s_window_count; i++)
    if (s_windows[i]->hwnd == hwnd) return s_windows[i];
  return NULL;
}

static void deliver(win_pal_t* pal, my_pal_window_t* window,
                    const my_event_t* event) {
  if (pal->handler != NULL) pal->handler(pal->handler_ctx, window, event);
}

static uint64_t w32_now_ms(void) {
  return (uint64_t)GetTickCount64();
}

/* ---------------- lcd (DIB section presentation) ---------------- */

static uint32_t wlcd_width(my_lcd_t* lcd) {
  return my_lcd_get_width(((win_lcd_t*)lcd)->mem);
}

static uint32_t wlcd_height(my_lcd_t* lcd) {
  return my_lcd_get_height(((win_lcd_t*)lcd)->mem);
}

static my_pixel_format_t wlcd_format(my_lcd_t* lcd) {
  return my_lcd_get_format(((win_lcd_t*)lcd)->mem);
}

static my_ret_t wlcd_begin(my_lcd_t* lcd, const my_rect_t* dirty) {
  return my_lcd_begin_frame(((win_lcd_t*)lcd)->mem, dirty);
}

static my_ret_t wlcd_end(my_lcd_t* lcd) {
  win_lcd_t* x = (win_lcd_t*)lcd;
  my_ret_t r = my_lcd_end_frame(x->mem);
  HDC window_dc;
  if (r != MY_RET_OK) return r;
  memcpy(x->bits, my_lcd_get_buffer(x->mem),
         (size_t)x->width * (size_t)x->height * 4u);
  window_dc = GetDC(x->hwnd);
  StretchDIBits(window_dc, 0, 0, x->width, x->height, 0, 0, x->width,
                x->height, x->bits, NULL, DIB_RGB_COLORS, SRCCOPY);
  ReleaseDC(x->hwnd, window_dc);
  return MY_RET_OK;
}

static my_ret_t wlcd_draw_pixels(my_lcd_t* lcd, const void* pixels,
                                 int32_t px, int32_t py, uint32_t w,
                                 uint32_t h) {
  return my_lcd_draw_pixels(((win_lcd_t*)lcd)->mem, pixels, px, py, w, h);
}

static my_ret_t wlcd_fill_rect(my_lcd_t* lcd, const my_rect_t* rect,
                               my_color_t color) {
  return my_lcd_fill_rect(((win_lcd_t*)lcd)->mem, rect, color);
}

static my_ret_t wlcd_blend_span(my_lcd_t* lcd, int32_t x, int32_t y,
                                const uint8_t* alpha, int32_t n,
                                my_color_t color) {
  return my_lcd_blend_span(((win_lcd_t*)lcd)->mem, x, y, alpha, n, color);
}

static uint8_t* wlcd_buffer(my_lcd_t* lcd) {
  return my_lcd_get_buffer(((win_lcd_t*)lcd)->mem);
}

static uint32_t wlcd_stride(my_lcd_t* lcd) {
  return my_lcd_get_stride(((win_lcd_t*)lcd)->mem);
}

static void wlcd_destroy(my_lcd_t* lcd) {
  win_lcd_t* x = (win_lcd_t*)lcd;
  if (x->dib != NULL) DeleteObject(x->dib);
  if (x->dib_dc != NULL) DeleteDC(x->dib_dc);
  my_lcd_destroy(x->mem);
  my_mem_free(x->pal->allocator, x);
}

static const my_lcd_vtable_t s_wlcd_vtable = {
    wlcd_width, wlcd_height, wlcd_format, wlcd_begin,
    wlcd_end, wlcd_draw_pixels, wlcd_fill_rect, wlcd_blend_span,
    wlcd_destroy, wlcd_buffer, wlcd_stride};

static win_lcd_t* wlcd_create(win_pal_t* pal, HWND hwnd, int32_t w,
                              int32_t h) {
  win_lcd_t* x = (win_lcd_t*)my_mem_calloc(pal->allocator, 1u, sizeof(*x));
  BITMAPINFO bi;
  if (x == NULL) return NULL;
  x->base.vtable = &s_wlcd_vtable;
  x->pal = pal;
  x->hwnd = hwnd;
  x->width = w;
  x->height = h;
  x->mem = my_lcd_mem_create(pal->allocator, (uint32_t)w, (uint32_t)h,
                             MY_PIXEL_FORMAT_BGRA8888);
  if (x->mem == NULL) {
    my_mem_free(pal->allocator, x);
    return NULL;
  }
  ZeroMemory(&bi, sizeof(bi));
  bi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
  bi.bmiHeader.biWidth = w;
  bi.bmiHeader.biHeight = -h;
  bi.bmiHeader.biPlanes = 1;
  bi.bmiHeader.biBitCount = 32;
  bi.bmiHeader.biCompression = BI_RGB;
  x->dib_dc = CreateCompatibleDC(NULL);
  x->dib = CreateDIBSection(x->dib_dc, &bi, DIB_RGB_COLORS, &x->bits, NULL,
                            0u);
  if (x->dib == NULL || x->dib_dc == NULL) {
    wlcd_destroy(&x->base);
    return NULL;
  }
  return x;
}

/* ---------------- window ---------------- */

static void realloc_lcd(win_window_t* w, int32_t width, int32_t height) {
  win_lcd_t* lcd = wlcd_create(w->pal, w->hwnd, width, height);
  if (lcd == NULL) return;
  if (w->lcd != NULL) my_lcd_destroy(&w->lcd->base);
  w->lcd = lcd;
  w->width = width;
  w->height = height;
}

static my_ret_t wwin_set_title(my_pal_window_t* win, const char* title) {
  wchar_t wide[128];
  MultiByteToWideChar(CP_UTF8, 0, title != NULL ? title : "", -1, wide,
                      128);
  SetWindowTextW(((win_window_t*)win)->hwnd, wide);
  return MY_RET_OK;
}

static my_ret_t wwin_resize(my_pal_window_t* win, int32_t w, int32_t h) {
  win_window_t* x = (win_window_t*)win;
  RECT r = {0, 0, w, h};
  AdjustWindowRect(&r, WS_OVERLAPPEDWINDOW, FALSE);
  SetWindowPos(x->hwnd, NULL, 0, 0, r.right - r.left, r.bottom - r.top,
               SWP_NOMOVE | SWP_NOZORDER);
  realloc_lcd(x, w, h);
  return MY_RET_OK;
}

static my_ret_t wwin_show(my_pal_window_t* win) {
  ShowWindow(((win_window_t*)win)->hwnd, SW_SHOWNORMAL);
  return MY_RET_OK;
}

static my_ret_t wwin_get_size(my_pal_window_t* win, int32_t* w, int32_t* h) {
  win_window_t* x = (win_window_t*)win;
  if (w != NULL) *w = x->width;
  if (h != NULL) *h = x->height;
  return MY_RET_OK;
}

static my_lcd_t* wwin_get_lcd(my_pal_window_t* win) {
  return &((win_window_t*)win)->lcd->base;
}

static void wgl_destroy_owned(win_window_t* w) {
  if (w->gl == NULL) return;
  wglMakeCurrent(NULL, NULL);
  wglDeleteContext(w->gl->ctx);
  my_mem_free(w->pal->allocator, w->gl);
  w->gl = NULL;
}

static void wwin_destroy(my_pal_window_t* win) {
  win_window_t* w = (win_window_t*)win;
  size_t i;
  wgl_destroy_owned(w);
  my_lcd_destroy(&w->lcd->base);
  DestroyWindow(w->hwnd);
  for (i = 0u; i < s_window_count; i++)
    if (s_windows[i] == w) {
      s_windows[i] = s_windows[s_window_count - 1u];
      s_window_count--;
      break;
    }
  my_mem_free(w->pal->allocator, w);
}

static my_ret_t wgl_make_current(my_pal_gl_t* gl) {
  win_gl_t* g = (win_gl_t*)gl;
  return wglMakeCurrent(g->dc, g->ctx) ? MY_RET_OK : MY_RET_FAIL;
}

static my_ret_t wgl_swap(my_pal_gl_t* gl) {
  win_gl_t* g = (win_gl_t*)gl;
  SwapBuffers(g->dc);
  return MY_RET_OK;
}

static my_ret_t wgl_size(my_pal_gl_t* gl, int32_t* w, int32_t* h) {
  win_gl_t* g = (win_gl_t*)gl;
  RECT r;
  GetClientRect(g->owner->hwnd, &r);
  if (w != NULL) *w = (int32_t)(r.right - r.left);
  if (h != NULL) *h = (int32_t)(r.bottom - r.top);
  return MY_RET_OK;
}

static bool wgl_multisample(my_pal_gl_t* gl) {
  (void)gl;
  return false;
}

static void wgl_destroy(my_pal_gl_t* gl) {
  wgl_destroy_owned(((win_gl_t*)gl)->owner);
}

static const my_pal_gl_vtable_t s_wgl_vtable = {
    wgl_make_current, wgl_swap, wgl_size, wgl_multisample, wgl_destroy};

static my_pal_gl_t* wwin_gl_enable(my_pal_window_t* win) {
  win_window_t* w = (win_window_t*)win;
  PIXELFORMATDESCRIPTOR pfd;
  int pf;
  if (w->gl != NULL) return &w->gl->base;
  ZeroMemory(&pfd, sizeof(pfd));
  pfd.nSize = sizeof(pfd);
  pfd.nVersion = 1;
  pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
  pfd.iPixelType = PFD_TYPE_RGBA;
  pfd.cColorBits = 24;
  pf = ChoosePixelFormat(GetDC(w->hwnd), &pfd);
  if (pf == 0 || !SetPixelFormat(GetDC(w->hwnd), pf, &pfd)) return NULL;
  w->gl = (win_gl_t*)my_mem_calloc(w->pal->allocator, 1u, sizeof(*w->gl));
  if (w->gl == NULL) return NULL;
  w->gl->base.vtable = &s_wgl_vtable;
  w->gl->owner = w;
  w->gl->dc = GetDC(w->hwnd);
  w->gl->ctx = wglCreateContext(w->gl->dc);
  if (w->gl->ctx == NULL) {
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

static my_ret_t wwin_move(my_pal_window_t* win, int32_t x, int32_t y) {
  SetWindowPos(((win_window_t*)win)->hwnd, NULL, x, y, 0, 0,
               SWP_NOSIZE | SWP_NOZORDER);
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
    .move = wwin_move};

/* ---------------- events + main loop + pal ---------------- */

static LRESULT CALLBACK wnd_proc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
  win_window_t* w = find_window(hwnd);
  my_event_t event;
  if (w == NULL) return DefWindowProcW(hwnd, msg, wp, lp);
  switch (msg) {
    case WM_MOUSEMOVE:
      event = my_event_init(MY_EVENT_POINTER_MOVE);
      event.u.pointer.x = GET_X_LPARAM(lp);
      event.u.pointer.y = GET_Y_LPARAM(lp);
      deliver(w->pal, &w->base, &event);
      return 0;
    case WM_LBUTTONDOWN:
      event = my_event_init(MY_EVENT_POINTER_DOWN);
      event.u.pointer.x = GET_X_LPARAM(lp);
      event.u.pointer.y = GET_Y_LPARAM(lp);
      event.u.pointer.button = 1u;
      deliver(w->pal, &w->base, &event);
      return 0;
    case WM_MOUSEWHEEL:
      event = my_event_init(MY_EVENT_POINTER_WHEEL);
      event.u.pointer.x = GET_X_LPARAM(lp);
      event.u.pointer.y = GET_Y_LPARAM(lp);
      event.u.pointer.delta = ((short)HIWORD(wp)) > 0 ? 1 : -1;
      deliver(w->pal, &w->base, &event);
      return 0;
    case WM_CHAR:
      if (wp >= ' ' && wp <= '~') {
        event = my_event_init(MY_EVENT_KEY_DOWN);
        event.u.key.key = (uint32_t)wp;
        deliver(w->pal, &w->base, &event);
      }
      return 0;
    case WM_ERASEBKGND:
      return 1;
    case WM_CLOSE:
      event = my_event_init(MY_EVENT_QUIT);
      deliver(w->pal, &w->base, &event);
      return 0;
    case WM_DESTROY:
      return 0;
    default:
      return DefWindowProcW(hwnd, msg, wp, lp);
  }
}

static void loop_flush_queue(win_loop_t* l) {
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

static uint64_t wloop_timer_now(void* ctx) {
  (void)ctx;
  return w32_now_ms();
}

static my_ret_t wloop_run(my_pal_main_loop_t* loop) {
  win_loop_t* l = (win_loop_t*)loop;
  MSG msg;
  atomic_store_explicit(&l->accepting, true, memory_order_relaxed);
  while (!atomic_load_explicit(&l->quit, memory_order_relaxed)) {
    while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
      if (msg.message == WM_QUIT) {
        atomic_store_explicit(&l->quit, true, memory_order_relaxed);
        break;
      }
      TranslateMessage(&msg);
      DispatchMessage(&msg);
    }
    (void)my_timer_manager_fire(l->timers);
    loop_flush_queue(l);
    Sleep(1);
  }
  loop_flush_queue(l);
  atomic_store_explicit(&l->accepting, false, memory_order_relaxed);
  return MY_RET_OK;
}

static my_ret_t wloop_quit(my_pal_main_loop_t* loop) {
  win_loop_t* l = (win_loop_t*)loop;
  atomic_store_explicit(&l->quit, true, memory_order_relaxed);
  PostThreadMessage(GetCurrentThreadId(), WM_QUIT, 0, 0);
  return MY_RET_OK;
}

static my_ret_t wloop_post_event(my_pal_main_loop_t* loop,
                                 const my_event_t* event) {
  win_loop_t* l = (win_loop_t*)loop;
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
  return MY_RET_OK;
}

static uint32_t wloop_add_timer(my_pal_main_loop_t* loop,
                                my_timer_callback_t callback, void* ctx,
                                uint32_t interval_ms) {
  return my_timer_add(((win_loop_t*)loop)->timers, callback, ctx,
                      interval_ms);
}

static my_ret_t wloop_remove_timer(my_pal_main_loop_t* loop, uint32_t id) {
  return my_timer_remove(((win_loop_t*)loop)->timers, id);
}

static void wloop_destroy(my_pal_main_loop_t* loop) {
  win_loop_t* l = (win_loop_t*)loop;
  queued_event_t* qe = l->head;
  while (qe != NULL) {
    queued_event_t* next = qe->next;
    my_mem_free(l->allocator, qe);
    qe = next;
  }
  my_timer_manager_destroy(l->timers);
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
  win_pal_t* p = (win_pal_t*)pal;
  win_window_t* win;
  WNDCLASSW wc;
  RECT r = {0, 0, w, h};
  wchar_t wide[128];
  static int registered;
  if (w <= 0 || h <= 0 || s_window_count >= W32_MAX_WINDOWS) return NULL;
  if (!registered) {
    ZeroMemory(&wc, sizeof(wc));
    wc.style = CS_OWNDC;
    wc.lpfnWndProc = wnd_proc;
    wc.hInstance = GetModuleHandle(NULL);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.lpszClassName = L"MyUIPalWin32";
    RegisterClassW(&wc);
    registered = 1;
  }
  win = (win_window_t*)my_mem_calloc(p->allocator, 1u, sizeof(*win));
  if (win == NULL) return NULL;
  win->base.vtable = &s_wwin_vtable;
  win->pal = p;
  win->width = w;
  win->height = h;
  AdjustWindowRect(&r, WS_OVERLAPPEDWINDOW, FALSE);
  MultiByteToWideChar(CP_UTF8, 0, title != NULL ? title : "", -1, wide,
                      128);
  win->hwnd = CreateWindowW(L"MyUIPalWin32", wide, WS_OVERLAPPEDWINDOW,
                            CW_USEDEFAULT, CW_USEDEFAULT, r.right - r.left,
                            r.bottom - r.top, NULL, NULL,
                            GetModuleHandle(NULL), NULL);
  if (win->hwnd == NULL) {
    my_mem_free(p->allocator, win);
    return NULL;
  }
  realloc_lcd(win, w, h);
  if (win->lcd == NULL) {
    DestroyWindow(win->hwnd);
    my_mem_free(p->allocator, win);
    return NULL;
  }
  s_windows[s_window_count++] = win;
  return &win->base;
}

static my_pal_main_loop_t* wpal_loop_create(my_pal_t* pal) {
  win_pal_t* p = (win_pal_t*)pal;
  win_loop_t* l = (win_loop_t*)my_mem_calloc(p->allocator, 1u, sizeof(*l));
  if (l == NULL) return NULL;
  l->base.vtable = &s_wloop_vtable;
  l->pal = p;
  l->allocator = p->allocator;
  atomic_flag_clear_explicit(&l->lock);
  l->timers = my_timer_manager_create(p->allocator, wloop_timer_now, l);
  if (l->timers == NULL) {
    my_mem_free(p->allocator, l);
    return NULL;
  }
  return &l->base;
}

static uint64_t wpal_time_ms(my_pal_t* pal) {
  (void)pal;
  return w32_now_ms();
}

static my_ret_t wpal_set_handler(my_pal_t* pal,
                                 my_pal_event_handler_t handler,
                                 void* ctx) {
  win_pal_t* p = (win_pal_t*)pal;
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
  win_pal_t* p = (win_pal_t*)pal;
  while (s_window_count > 0u)
    wwin_destroy(&s_windows[0]->base);
  my_mem_free(p->allocator, p);
}

static const my_pal_vtable_t s_wpal_vtable = {
    .window_create = wpal_window_create,
    .main_loop_create = wpal_loop_create,
    .time_now_ms = wpal_time_ms,
    .set_event_handler = wpal_set_handler,
    .clipboard_set_text = wpal_clipboard_set,
    .clipboard_get_text = wpal_clipboard_get,
    .get_scale_factor = wpal_scale,
    .destroy = wpal_destroy};

my_pal_t* my_pal_win32_create(const my_allocator_t* allocator) {
  win_pal_t* p = (win_pal_t*)my_mem_calloc(allocator, 1u, sizeof(*p));
  if (p == NULL) return NULL;
  p->base.vtable = &s_wpal_vtable;
  p->allocator = allocator;
  return &p->base;
}
