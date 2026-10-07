/**
 * @file my_pal_cocoa.m
 * @brief macOS PAL port: Cocoa windows, NSBitmapImageRep lcd, NSOpenGL.
 *        Compile-targeted (no macOS host in CI); follows the frozen
 *        my_pal.h contract. NULL slots: clipboard, gl_enable_api,
 *        vk_create_surface, set_cursor, ime, move, begin_move.
 */
#import <Cocoa/Cocoa.h>
#import <OpenGL/OpenGL.h>
#include "mypal/cocoa/my_pal_cocoa.h"

#include "myr/my_lcd_mem.h"
#include "mypal/my_timer.h"

#include <mach/mach_time.h>
#include <stdatomic.h>
#include <stdint.h>
#include <string.h>

typedef struct cocoa_pal_t {
  my_pal_t base;
  const my_allocator_t* allocator;
  my_pal_event_handler_t handler;
  void* handler_ctx;
} cocoa_pal_t;

typedef struct cocoa_lcd_t {
  my_lcd_t base;
  cocoa_pal_t* pal;
  my_lcd_t* mem;
  NSView* view;
  int32_t width;
  int32_t height;
} cocoa_lcd_t;

typedef struct cocoa_window_t {
  my_pal_window_t base;
  cocoa_pal_t* pal;
  NSWindow* window;
  cocoa_lcd_t* lcd;
  struct cocoa_gl_t* gl;
} cocoa_window_t;

typedef struct cocoa_gl_t {
  my_pal_gl_t base;
  cocoa_window_t* owner;
  NSOpenGLContext* ctx;
} cocoa_gl_t;

typedef struct queued_event_t {
  my_event_t event;
  struct queued_event_t* next;
} queued_event_t;

typedef struct cocoa_loop_t {
  my_pal_main_loop_t base;
  cocoa_pal_t* pal;
  const my_allocator_t* allocator;
  queued_event_t* head;
  queued_event_t* tail;
  my_timer_manager_t* timers;
  atomic_flag lock;
  atomic_bool accepting;
  atomic_bool quit;
} cocoa_loop_t;

static void deliver(cocoa_pal_t* pal, my_pal_window_t* window,
                    const my_event_t* event) {
  if (pal->handler != NULL) pal->handler(pal->handler_ctx, window, event);
}

static uint64_t cocoa_now_ms(void) {
  static mach_timebase_info_data_t tb;
  uint64_t t;
  if (tb.denom == 0u) (void)mach_timebase_info(&tb);
  t = mach_absolute_time();
  return t * tb.numer / tb.denom / 1000000u;
}

/* ---------------- view ---------------- */

@interface PalView : NSView {
 @public
  cocoa_window_t* owner;
}
- (void)drawRect:(NSRect)rect;
- (void)mouseMoved:(NSEvent*)ev;
- (void)mouseDragged:(NSEvent*)ev;
- (void)mouseDown:(NSEvent*)ev;
- (void)scrollWheel:(NSEvent*)ev;
- (void)keyDown:(NSEvent*)ev;
@end

@implementation PalView
- (BOOL)isFlipped {
  return YES;
}
- (void)drawRect:(NSRect)rect {
  (void)rect;
  if (owner->gl != NULL || owner->lcd == NULL) return;
  {
    NSBitmapImageRep* rep =
        [[NSBitmapImageRep alloc]
             initWithBitmapDataPlanes:NULL
                          pixelsWide:owner->lcd->width
                          pixelsHigh:owner->lcd->height
                       bitsPerSample:8
                     samplesPerPixel:4
                            hasAlpha:YES
                            isPlanar:NO
                      colorSpaceName:NSDeviceRGBColorSpace
                         bitmapFormat:NSAlphaFirstBitmapFormat
                          bytesPerRow:(int)my_lcd_get_stride(owner->lcd->mem)
                             bitsPerPixel:32];
    memcpy([rep bitmapData], my_lcd_get_buffer(owner->lcd->mem),
           (size_t)owner->lcd->height * my_lcd_get_stride(owner->lcd->mem));
    [rep drawInRect:[self bounds]];
    [rep release];
  }
}
- (void)mouseMoved:(NSEvent*)ev {
  NSPoint p = [self convertPoint:[ev locationInWindow] fromView:nil];
  my_event_t event = my_event_init(MY_EVENT_POINTER_MOVE);
  event.u.pointer.x = (int32_t)p.x;
  event.u.pointer.y = (int32_t)p.y;
  deliver(owner->pal, &owner->base, &event);
}
- (void)mouseDragged:(NSEvent*)ev {
  [self mouseMoved:ev];
}
- (void)mouseDown:(NSEvent*)ev {
  NSPoint p = [self convertPoint:[ev locationInWindow] fromView:nil];
  my_event_t event = my_event_init(MY_EVENT_POINTER_DOWN);
  event.u.pointer.x = (int32_t)p.x;
  event.u.pointer.y = (int32_t)p.y;
  event.u.pointer.button = 1u;
  deliver(owner->pal, &owner->base, &event);
}
- (void)scrollWheel:(NSEvent*)ev {
  my_event_t event = my_event_init(MY_EVENT_POINTER_WHEEL);
  event.u.pointer.delta = [ev deltaY] > 0 ? 1 : -1;
  deliver(owner->pal, &owner->base, &event);
}
- (void)keyDown:(NSEvent*)ev {
  const char* chars = [[ev characters] UTF8String];
  if (chars != NULL && (unsigned char)chars[0] >= ' ' &&
      (unsigned char)chars[0] <= '~') {
    my_event_t event = my_event_init(MY_EVENT_KEY_DOWN);
    event.u.key.key = (uint32_t)(unsigned char)chars[0];
    deliver(owner->pal, &owner->base, &event);
  }
}
@end

/* ---------------- lcd ---------------- */

static uint32_t clcd_width(my_lcd_t* lcd) {
  return my_lcd_get_width(((cocoa_lcd_t*)lcd)->mem);
}

static uint32_t clcd_height(my_lcd_t* lcd) {
  return my_lcd_get_height(((cocoa_lcd_t*)lcd)->mem);
}

static my_pixel_format_t clcd_format(my_lcd_t* lcd) {
  return my_lcd_get_format(((cocoa_lcd_t*)lcd)->mem);
}

static my_ret_t clcd_begin(my_lcd_t* lcd, const my_rect_t* dirty) {
  return my_lcd_begin_frame(((cocoa_lcd_t*)lcd)->mem, dirty);
}

static my_ret_t clcd_end(my_lcd_t* lcd) {
  cocoa_lcd_t* x = (cocoa_lcd_t*)lcd;
  my_ret_t r = my_lcd_end_frame(x->mem);
  if (r != MY_RET_OK) return r;
  [x->view setNeedsDisplay:YES];
  return MY_RET_OK;
}

static my_ret_t clcd_draw_pixels(my_lcd_t* lcd, const void* pixels,
                                 int32_t px, int32_t py, uint32_t w,
                                 uint32_t h) {
  return my_lcd_draw_pixels(((cocoa_lcd_t*)lcd)->mem, pixels, px, py, w, h);
}

static my_ret_t clcd_fill_rect(my_lcd_t* lcd, const my_rect_t* rect,
                               my_color_t color) {
  return my_lcd_fill_rect(((cocoa_lcd_t*)lcd)->mem, rect, color);
}

static my_ret_t clcd_blend_span(my_lcd_t* lcd, int32_t x, int32_t y,
                                const uint8_t* alpha, int32_t n,
                                my_color_t color) {
  return my_lcd_blend_span(((cocoa_lcd_t*)lcd)->mem, x, y, alpha, n, color);
}

static uint8_t* clcd_buffer(my_lcd_t* lcd) {
  return my_lcd_get_buffer(((cocoa_lcd_t*)lcd)->mem);
}

static uint32_t clcd_stride(my_lcd_t* lcd) {
  return my_lcd_get_stride(((cocoa_lcd_t*)lcd)->mem);
}

static void clcd_destroy(my_lcd_t* lcd) {
  cocoa_lcd_t* x = (cocoa_lcd_t*)lcd;
  my_lcd_destroy(x->mem);
  my_mem_free(x->pal->allocator, x);
}

static const my_lcd_vtable_t s_clcd_vtable = {
    clcd_width, clcd_height, clcd_format, clcd_begin,
    clcd_end, clcd_draw_pixels, clcd_fill_rect, clcd_blend_span,
    clcd_destroy, clcd_buffer, clcd_stride};

static cocoa_lcd_t* clcd_create(cocoa_pal_t* pal, NSView* view, int32_t w,
                                int32_t h) {
  cocoa_lcd_t* x =
      (cocoa_lcd_t*)my_mem_calloc(pal->allocator, 1u, sizeof(*x));
  if (x == NULL) return NULL;
  x->base.vtable = &s_clcd_vtable;
  x->pal = pal;
  x->view = view;
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

static my_ret_t cwin_set_title(my_pal_window_t* win, const char* title) {
  NSString* s = [NSString stringWithUTF8String:title != NULL ? title : ""];
  [((cocoa_window_t*)win)->window setTitle:s];
  return MY_RET_OK;
}

static my_ret_t cwin_resize(my_pal_window_t* win, int32_t w, int32_t h) {
  [((cocoa_window_t*)win)->window
      setContentSize:NSMakeSize((CGFloat)w, (CGFloat)h)];
  return MY_RET_OK;
}

static my_ret_t cwin_show(my_pal_window_t* win) {
  [((cocoa_window_t*)win)->window makeKeyAndOrderFront:nil];
  return MY_RET_OK;
}

static my_ret_t cwin_get_size(my_pal_window_t* win, int32_t* w, int32_t* h) {
  cocoa_window_t* x = (cocoa_window_t*)win;
  if (x->lcd != NULL) {
    if (w != NULL) *w = x->lcd->width;
    if (h != NULL) *h = x->lcd->height;
    return MY_RET_OK;
  }
  return MY_RET_NOT_SUPPORTED;
}

static my_lcd_t* cwin_get_lcd(my_pal_window_t* win) {
  cocoa_window_t* x = (cocoa_window_t*)win;
  return x->lcd != NULL ? &x->lcd->base : NULL;
}

static void cgl_destroy_owned(cocoa_window_t* w) {
  if (w->gl == NULL) return;
  [w->gl->ctx clearDrawable];
  [w->gl->ctx release];
  my_mem_free(w->pal->allocator, w->gl);
  w->gl = NULL;
}

static void cwin_destroy(my_pal_window_t* win) {
  cocoa_window_t* w = (cocoa_window_t*)win;
  cgl_destroy_owned(w);
  if (w->lcd != NULL) my_lcd_destroy(&w->lcd->base);
  [w->window close];
  my_mem_free(w->pal->allocator, w);
}

static my_ret_t cgl_make_current(my_pal_gl_t* gl) {
  [((cocoa_gl_t*)gl)->ctx makeCurrentContext];
  return MY_RET_OK;
}

static my_ret_t cgl_swap(my_pal_gl_t* gl) {
  [((cocoa_gl_t*)gl)->ctx flush];
  return MY_RET_OK;
}

static my_ret_t cgl_size(my_pal_gl_t* gl, int32_t* w, int32_t* h) {
  cocoa_gl_t* g = (cocoa_gl_t*)gl;
  NSRect r = [[g->ctx view] bounds];
  if (w != NULL) *w = (int32_t)r.size.width;
  if (h != NULL) *h = (int32_t)r.size.height;
  return MY_RET_OK;
}

static bool cgl_multisample(my_pal_gl_t* gl) {
  (void)gl;
  return false;
}

static void cgl_destroy(my_pal_gl_t* gl) {
  cgl_destroy_owned(((cocoa_gl_t*)gl)->owner);
}

static const my_pal_gl_vtable_t s_cgl_vtable = {
    cgl_make_current, cgl_swap, cgl_size, cgl_multisample, cgl_destroy};

static my_pal_gl_t* cwin_gl_enable(my_pal_window_t* win) {
  cocoa_window_t* w = (cocoa_window_t*)win;
  NSOpenGLPixelFormatAttribute attrs[] = {NSOpenGLPFAAccelerated,
                                          NSOpenGLPFADoubleBuffer, 0};
  NSOpenGLPixelFormat* pf;
  if (w->gl != NULL) return &w->gl->base;
  pf = [[NSOpenGLPixelFormat alloc] initWithAttributes:attrs];
  if (pf == NULL) return NULL;
  w->gl = (cocoa_gl_t*)my_mem_calloc(w->pal->allocator, 1u, sizeof(*w->gl));
  if (w->gl == NULL) {
    [pf release];
    return NULL;
  }
  w->gl->base.vtable = &s_cgl_vtable;
  w->gl->owner = w;
  w->gl->ctx = [[NSOpenGLContext alloc] initWithFormat:pf shareContext:nil];
  [pf release];
  if (w->gl->ctx == NULL) {
    my_mem_free(w->pal->allocator, w->gl);
    w->gl = NULL;
    return NULL;
  }
  [w->gl->ctx setView:[w->window contentView]];
  [w->gl->ctx makeCurrentContext];
  return &w->gl->base;
}

static void cwin_noop_bool(my_pal_window_t* win, bool on) {
  (void)win; (void)on;
}

static void cwin_noop_ime(my_pal_window_t* win, const char* utf8,
                          int32_t cursor, int32_t anchor) {
  (void)win; (void)utf8; (void)cursor; (void)anchor;
}

static void cwin_noop_spot(my_pal_window_t* win, int32_t x, int32_t y) {
  (void)win; (void)x; (void)y;
}

static const my_pal_window_vtable_t s_cwin_vtable = {
    .set_title = cwin_set_title,
    .resize = cwin_resize,
    .show = cwin_show,
    .get_size = cwin_get_size,
    .get_lcd = cwin_get_lcd,
    .destroy = cwin_destroy,
    .gl_enable = cwin_gl_enable,
    .ime_set_enabled = cwin_noop_bool,
    .ime_set_surrounding = cwin_noop_ime,
    .ime_set_spot = cwin_noop_spot};

/* ---------------- main loop + pal ---------------- */

static void loop_flush_queue(cocoa_loop_t* l) {
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

static uint64_t cloop_timer_now(void* ctx) {
  (void)ctx;
  return cocoa_now_ms();
}

@interface LoopTimerTarget : NSObject
 @property(nonatomic, assign) cocoa_loop_t* loop;
- (void)tick:(NSTimer*)timer;
@end

@implementation LoopTimerTarget
- (void)tick:(NSTimer*)timer {
  (void)timer;
  if (self.loop != NULL) {
    (void)my_timer_manager_fire(self.loop->timers);
    loop_flush_queue(self.loop);
    if (atomic_load_explicit(&self.loop->quit, memory_order_relaxed)) {
      [NSApp stop:nil];
    }
  }
}
@end

@interface PalDelegate : NSObject <NSApplicationDelegate, NSWindowDelegate>
 @property(nonatomic, assign) cocoa_pal_t* pal;
 @property(nonatomic, assign) cocoa_window_t* window;
@end

@implementation PalDelegate
- (void)applicationDidFinishLaunching:(NSNotification*)n {
  (void)n;
}
- (BOOL)applicationShouldTerminateAfterLastWindowClosed:(NSApplication*)a {
  (void)a;
  if (self.pal != NULL && self.pal->handler != NULL) {
    my_event_t event = my_event_init(MY_EVENT_QUIT);
    deliver(self.pal, self.window != NULL ? &self.window->base : NULL,
            &event);
  }
  return NO;
}
- (void)windowWillClose:(NSNotification*)n {
  (void)n;
  if (self.pal != NULL && self.pal->handler != NULL) {
    my_event_t event = my_event_init(MY_EVENT_QUIT);
    deliver(self.pal, self.window != NULL ? &self.window->base : NULL,
            &event);
  }
}
@end

static my_ret_t cloop_run(my_pal_main_loop_t* loop) {
  cocoa_loop_t* l = (cocoa_loop_t*)loop;
  LoopTimerTarget* target = [[LoopTimerTarget alloc] init];
  target.loop = l;
  atomic_store_explicit(&l->accepting, true, memory_order_relaxed);
  [NSTimer scheduledTimerWithTimeInterval:0.008
                                    target:target
                                  selector:@selector(tick:)
                                  userInfo:nil
                                   repeats:YES];
  [NSApp run];
  atomic_store_explicit(&l->accepting, false, memory_order_relaxed);
  loop_flush_queue(l);
  [target release];
  return MY_RET_OK;
}

static my_ret_t cloop_quit(my_pal_main_loop_t* loop) {
  cocoa_loop_t* l = (cocoa_loop_t*)loop;
  atomic_store_explicit(&l->quit, true, memory_order_relaxed);
  return MY_RET_OK;
}

static my_ret_t cloop_post_event(my_pal_main_loop_t* loop,
                                 const my_event_t* event) {
  cocoa_loop_t* l = (cocoa_loop_t*)loop;
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

static uint32_t cloop_add_timer(my_pal_main_loop_t* loop,
                                my_timer_callback_t callback, void* ctx,
                                uint32_t interval_ms) {
  return my_timer_add(((cocoa_loop_t*)loop)->timers, callback, ctx,
                      interval_ms);
}

static my_ret_t cloop_remove_timer(my_pal_main_loop_t* loop, uint32_t id) {
  return my_timer_remove(((cocoa_loop_t*)loop)->timers, id);
}

static void cloop_destroy(my_pal_main_loop_t* loop) {
  cocoa_loop_t* l = (cocoa_loop_t*)loop;
  queued_event_t* qe = l->head;
  while (qe != NULL) {
    queued_event_t* next = qe->next;
    my_mem_free(l->allocator, qe);
    qe = next;
  }
  my_timer_manager_destroy(l->timers);
  my_mem_free(l->allocator, l);
}

static const my_pal_main_loop_vtable_t s_cloop_vtable = {
    .run = cloop_run,
    .quit = cloop_quit,
    .post_event = cloop_post_event,
    .add_timer = cloop_add_timer,
    .remove_timer = cloop_remove_timer,
    .destroy = cloop_destroy};

static my_pal_window_t* cpal_window_create(my_pal_t* pal, int32_t w,
                                           int32_t h, const char* title) {
  cocoa_pal_t* p = (cocoa_pal_t*)pal;
  cocoa_window_t* win;
  PalView* view;
  PalDelegate* delegate;
  if (w <= 0 || h <= 0) return NULL;
  win = (cocoa_window_t*)my_mem_calloc(p->allocator, 1u, sizeof(*win));
  if (win == NULL) return NULL;
  win->base.vtable = &s_cwin_vtable;
  win->pal = p;
  win->window = [[NSWindow alloc]
      initWithContentRect:NSMakeRect(100, 100, w, h)
                styleMask:NSWindowStyleMaskTitled |
                          NSWindowStyleMaskClosable |
                          NSWindowStyleMaskMiniaturizable |
                          NSWindowStyleMaskResizable
                  backing:NSBackingStoreBuffered
                    defer:NO];
  view = [[PalView alloc] initWithFrame:NSMakeRect(0, 0, w, h)];
  view->owner = win;
  [win->window setContentView:view];
  [win->window setAcceptsMouseMovedEvents:YES];
  [win->window setTitle:[NSString
      stringWithUTF8String:title != NULL ? title : ""]];
  delegate = [[PalDelegate alloc] init];
  delegate.pal = p;
  delegate.window = win;
  [win->window setDelegate:delegate];
  win->lcd = clcd_create(p, view, w, h);
  if (win->lcd == NULL) {
    [win->window close];
    my_mem_free(p->allocator, win);
    return NULL;
  }
  return &win->base;
}

static my_pal_main_loop_t* cpal_loop_create(my_pal_t* pal) {
  cocoa_pal_t* p = (cocoa_pal_t*)pal;
  cocoa_loop_t* l =
      (cocoa_loop_t*)my_mem_calloc(p->allocator, 1u, sizeof(*l));
  if (l == NULL) return NULL;
  l->base.vtable = &s_cloop_vtable;
  l->pal = p;
  l->allocator = p->allocator;
  atomic_flag_clear_explicit(&l->lock);
  l->timers = my_timer_manager_create(p->allocator, cloop_timer_now, l);
  if (l->timers == NULL) {
    my_mem_free(p->allocator, l);
    return NULL;
  }
  return &l->base;
}

static uint64_t cpal_time_ms(my_pal_t* pal) {
  (void)pal;
  return cocoa_now_ms();
}

static my_ret_t cpal_set_handler(my_pal_t* pal,
                                 my_pal_event_handler_t handler,
                                 void* ctx) {
  cocoa_pal_t* p = (cocoa_pal_t*)pal;
  p->handler = handler;
  p->handler_ctx = ctx;
  return MY_RET_OK;
}

static my_ret_t cpal_clipboard_set(my_pal_t* pal, const char* text) {
  (void)pal; (void)text;
  return MY_RET_NOT_SUPPORTED;
}

static my_ret_t cpal_clipboard_get(my_pal_t* pal, char* buf, size_t size) {
  (void)pal; (void)buf; (void)size;
  return MY_RET_NOT_SUPPORTED;
}

static float cpal_scale(my_pal_t* pal) {
  (void)pal;
  return 1.0f;
}

static void cpal_destroy(my_pal_t* pal) {
  cocoa_pal_t* p = (cocoa_pal_t*)pal;
  my_mem_free(p->allocator, p);
}

static const my_pal_vtable_t s_cpal_vtable = {
    .window_create = cpal_window_create,
    .main_loop_create = cpal_loop_create,
    .time_now_ms = cpal_time_ms,
    .set_event_handler = cpal_set_handler,
    .clipboard_set_text = cpal_clipboard_set,
    .clipboard_get_text = cpal_clipboard_get,
    .get_scale_factor = cpal_scale,
    .destroy = cpal_destroy};

my_pal_t* my_pal_cocoa_create(const my_allocator_t* allocator) {
  cocoa_pal_t* p;
  if (NSApp == nil) {
    (void)[NSApplication sharedApplication];
    [NSApp setActivationPolicy:NSApplicationActivationPolicyRegular];
    [NSApp activateIgnoringOtherApps:YES];
  }
  p = (cocoa_pal_t*)my_mem_calloc(allocator, 1u, sizeof(*p));
  if (p == NULL) return NULL;
  p->base.vtable = &s_cpal_vtable;
  p->allocator = allocator;
  return &p->base;
}
