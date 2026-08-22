/**
 * @file my_pal.h
 * @brief Platform abstraction layer — frozen vtables (M2).
 *
 * A PAL port provides exactly four things:
 *  1. windows (my_pal_window_t): title/resize/show/size + an my_lcd_t to
 *     draw into (drawing is the myr layer's business);
 *  2. a main loop (my_pal_main_loop_t): run/quit/post_event + timers;
 *  3. a monotonic clock (time_now_ms);
 *  4. the platform entry point my_pal_create() (port chosen at compile
 *     time: MYUI_PAL_X11 / MYUI_PAL_DUMMY, CMake option MYUI_PAL).
 *
 * Events (my_event_t) are delivered to the single application handler
 * registered with my_pal_set_event_handler(). Ports: dummy/ (headless,
 * tests) and x11/ (Linux desktop). See docs/porting.md to add a port.
 */
#ifndef MY_PAL_H
#define MY_PAL_H

#include "myc/my_error.h"
#include "myc/my_mem.h"
#include "mypal/my_event.h"
#include "mypal/my_timer.h"
#include "myr/my_lcd.h"

typedef struct my_pal_t my_pal_t;
typedef struct my_pal_window_t my_pal_window_t;
typedef struct my_pal_main_loop_t my_pal_main_loop_t;
typedef struct my_pal_gl_t my_pal_gl_t;

/**
 * @brief Mouse cursor shape over a window (M21a). ARROW is the default
 * baseline; TEXT = I-beam over text inputs; HAND = pointer over
 * clickable widgets (applied by the event dispatcher's hover tracking).
 */
typedef enum my_cursor_t {
  MY_CURSOR_ARROW = 0,
  MY_CURSOR_TEXT,
  MY_CURSOR_HAND
} my_cursor_t;

/**
 * @brief Application event handler. window is the event source, or NULL
 * for window-less events (e.g. posted USER events). Return value is
 * reserved (currently ignored).
 */
typedef my_ret_t (*my_pal_event_handler_t)(void* ctx, my_pal_window_t* window,
                                           const my_event_t* event);

/* ---------------- window ---------------- */

/** @brief Window vtable. */
typedef struct my_pal_window_vtable_t {
  my_ret_t (*set_title)(my_pal_window_t* win, const char* title);
  my_ret_t (*resize)(my_pal_window_t* win, int32_t w, int32_t h);
  my_ret_t (*show)(my_pal_window_t* win);
  /** @brief Current client size in logical pixels; w/h may be NULL
   * individually. GPU drawable sizes are queried from my_pal_gl_t and may be
   * logical_size * display_scale. */
  my_ret_t (*get_size)(my_pal_window_t* win, int32_t* w, int32_t* h);
  /**
   * @brief The lcd to draw this window's frame into (owned by the
   * window, do NOT destroy). Frame ends (my_lcd_end_frame) present it.
   */
  my_lcd_t* (*get_lcd)(my_pal_window_t* win);
  void (*destroy)(my_pal_window_t* win);
  /**
   * @brief Enable GLES rendering on this window (M10c, optional port
   * feature). Returns a GL context handle (create on first call, same
   * handle afterwards), or NULL when the port/build has no GL support.
   * The handle is owned by the window (freed with it); my_pal_gl_destroy
   * is for early teardown only and is double-destroy safe (the window
   * forgets the handle). The software lcd path keeps working regardless.
  */
  my_pal_gl_t* (*gl_enable)(my_pal_window_t* win);
  /** @brief Enable or disable text input for the focused widget. */
  void (*ime_set_enabled)(my_pal_window_t* win, bool enabled);
  /** @brief Update the UTF-8 document context used by platform IMEs. */
  void (*ime_set_surrounding)(my_pal_window_t* win, const char* utf8,
                              int32_t cursor, int32_t anchor);
  /**
   * @brief Move the IME candidate window anchor (M13a): x/y are the text
   * cursor's LOGICAL window coordinates (ports convert). No-op on ports
   * without IME integration.
   */
  void (*ime_set_spot)(my_pal_window_t* win, int32_t x, int32_t y);
  /**
   * @brief Move the window to (x, y) in LOGICAL screen coords (M13c;
   * used for dialog centering). No-op / NOT_SUPPORTED where the
   * compositor owns placement (wayland).
   */
  my_ret_t (*move)(my_pal_window_t* win, int32_t x, int32_t y);
  /**
   * @brief Ask the compositor/window manager to start an interactive
   * move (M16 CSD: the client-drawn title bar calls this on pointer
   * down). No-op on ports where the WM owns moving (x11) or that have
   * no concept of it (dummy/linux_fb).
   */
  my_ret_t (*begin_move)(my_pal_window_t* win);
  /**
   * @brief Set the mouse cursor shape over this window (M21a). Optional
   * slot: NULL = the port has no cursor control (linux_fb); the inline
   * wrapper then returns MY_RET_NOT_SUPPORTED. The port re-asserts the
   * shape itself where the windowing system resets it (wayland: on every
   * wl_pointer enter, with that enter's serial).
   */
  my_ret_t (*set_cursor)(my_pal_window_t* win, my_cursor_t cursor);
  /**
   * @brief Enable GL rendering with an explicit API (M25a): api is one
   * of MY_PAL_GL_API_*. Same ownership rules as gl_enable. NULL slot =
   * the port cannot select APIs; the inline wrapper then falls back to
   * gl_enable for MY_PAL_GL_API_GLES2 and fails (NULL) otherwise.
   */
  my_pal_gl_t* (*gl_enable_api)(my_pal_window_t* win, int api);
  /**
   * @brief Create a Vulkan surface for this window (M25b). vk_instance
   * is a VkInstance and the return a VkSurfaceKHR — both as void* so
   * this header stays free of Vulkan types. NULL slot or NULL return =
   * the port has no Vulkan support (dummy, linux_fb).
   */
  void* (*vk_create_surface)(my_pal_window_t* win, void* vk_instance);
} my_pal_window_vtable_t;

/** @brief GL APIs selectable through the gl_enable_api slot (M25a). */
#define MY_PAL_GL_API_GLES2 0
#define MY_PAL_GL_API_OPENGL 1

/** @brief Window base "class". */
struct my_pal_window_t {
  const my_pal_window_vtable_t* vtable;
};

static inline my_ret_t my_pal_window_set_title(my_pal_window_t* win,
                                               const char* title) {
  return win->vtable->set_title(win, title);
}

static inline my_ret_t my_pal_window_resize(my_pal_window_t* win, int32_t w,
                                            int32_t h) {
  return win->vtable->resize(win, w, h);
}

static inline my_ret_t my_pal_window_show(my_pal_window_t* win) {
  return win->vtable->show(win);
}

static inline my_ret_t my_pal_window_get_size(my_pal_window_t* win, int32_t* w,
                                              int32_t* h) {
  return win->vtable->get_size(win, w, h);
}

static inline my_lcd_t* my_pal_window_get_lcd(my_pal_window_t* win) {
  return win->vtable->get_lcd(win);
}

static inline void my_pal_window_destroy(my_pal_window_t* win) {
  if (win != NULL) {
    win->vtable->destroy(win);
  }
}

/* ---------------- GL context (M10c) ---------------- */

/** @brief GL context vtable: the raw window-system GL mount a vgcanvas
 * GLES backend can render through. */
typedef struct my_pal_gl_vtable_t {
  /** @brief Make this context (and its window surface) current. */
  my_ret_t (*make_current)(my_pal_gl_t* gl);
  /** @brief Present the back buffer (eglSwapBuffers; vsync-throttled). */
  my_ret_t (*swap_buffers)(my_pal_gl_t* gl);
  /** @brief Current drawable size in physical pixels; w/h may be NULL.
   * This is the size required by GPU viewport, scissor and swapchain code,
   * not the logical widget size. */
  my_ret_t (*get_size)(my_pal_gl_t* gl, int32_t* w, int32_t* h);
  /** @brief True when the surface carries multisamples (M11c; the port
   * preferred EGL_SAMPLES=4 and got it, false = fell back to no AA). */
  bool (*has_multisample)(my_pal_gl_t* gl);
  void (*destroy)(my_pal_gl_t* gl);
} my_pal_gl_vtable_t;

/** @brief GL context base "class". */
struct my_pal_gl_t {
  const my_pal_gl_vtable_t* vtable;
};

static inline my_ret_t my_pal_gl_make_current(my_pal_gl_t* gl) {
  return gl->vtable->make_current(gl);
}

static inline my_ret_t my_pal_gl_swap_buffers(my_pal_gl_t* gl) {
  return gl->vtable->swap_buffers(gl);
}

static inline my_ret_t my_pal_gl_get_size(my_pal_gl_t* gl, int32_t* w,
                                          int32_t* h) {
  return gl->vtable->get_size(gl, w, h);
}

static inline bool my_pal_gl_has_multisample(my_pal_gl_t* gl) {
  return gl->vtable->has_multisample(gl);
}

static inline void my_pal_gl_destroy(my_pal_gl_t* gl) {
  if (gl != NULL) {
    gl->vtable->destroy(gl);
  }
}

static inline my_pal_gl_t* my_pal_window_gl_enable(my_pal_window_t* win) {
  return win->vtable->gl_enable(win);
}

/**
 * @brief Enable GL with an explicit API (M25a). Ports without the
 * gl_enable_api slot can only do the legacy GLES2 mount.
 */
static inline my_pal_gl_t* my_pal_window_gl_enable_api(my_pal_window_t* win,
                                                       int api) {
  if (win->vtable->gl_enable_api != NULL) {
    return win->vtable->gl_enable_api(win, api);
  }
  return api == MY_PAL_GL_API_GLES2 ? win->vtable->gl_enable(win) : NULL;
}

/**
 * @brief Create a Vulkan surface (VkSurfaceKHR as void*) for this window
 * on the given instance (VkInstance as void*), NULL when unsupported
 * (M25b; ownership passes to the caller).
 */
static inline void* my_pal_window_vk_create_surface(my_pal_window_t* win,
                                                    void* vk_instance) {
  return win->vtable->vk_create_surface != NULL
             ? win->vtable->vk_create_surface(win, vk_instance)
             : NULL;
}

static inline void my_pal_window_ime_set_enabled(my_pal_window_t* win,
                                                 bool enabled) {
  if (win->vtable->ime_set_enabled != NULL) {
    win->vtable->ime_set_enabled(win, enabled);
  }
}

static inline void my_pal_window_ime_set_surrounding(my_pal_window_t* win,
                                                      const char* utf8,
                                                      int32_t cursor,
                                                      int32_t anchor) {
  if (win->vtable->ime_set_surrounding != NULL) {
    win->vtable->ime_set_surrounding(win, utf8, cursor, anchor);
  }
}

static inline void my_pal_window_ime_set_spot(my_pal_window_t* win, int32_t x,
                                              int32_t y) {
  if (win->vtable->ime_set_spot != NULL) {
    win->vtable->ime_set_spot(win, x, y);
  }
}

static inline my_ret_t my_pal_window_move(my_pal_window_t* win, int32_t x,
                                          int32_t y) {
  return win->vtable->move(win, x, y);
}

/** @brief Start an interactive move (M16 CSD). NOT_SUPPORTED/no-op when
 * the port has no such concept. */
static inline my_ret_t my_pal_window_begin_move(my_pal_window_t* win) {
  if (win->vtable->begin_move == NULL) {
    return MY_RET_NOT_SUPPORTED;
  }
  return win->vtable->begin_move(win);
}

/** @brief Set the mouse cursor shape over this window (M21a).
 * NOT_SUPPORTED when the port has no cursor control (NULL slot). */
static inline my_ret_t my_pal_window_set_cursor(my_pal_window_t* win,
                                                my_cursor_t cursor) {
  if (win->vtable->set_cursor == NULL) {
    return MY_RET_NOT_SUPPORTED;
  }
  return win->vtable->set_cursor(win, cursor);
}

/* ---------------- main loop ---------------- */

/** @brief Main loop vtable. */
typedef struct my_pal_main_loop_vtable_t {
  /** @brief Run until quit(); returns when the loop exits. */
  my_ret_t (*run)(my_pal_main_loop_t* loop);
  /** @brief Ask run() to return (safe from any thread). */
  my_ret_t (*quit)(my_pal_main_loop_t* loop);
  /**
   * @brief Enqueue a (copied) event for dispatch on the loop thread;
   * wakes the loop. Safe from any thread.
   */
  my_ret_t (*post_event)(my_pal_main_loop_t* loop, const my_event_t* event);
  /** @brief Add a timer driven by this loop (see my_timer.h). */
  uint32_t (*add_timer)(my_pal_main_loop_t* loop, my_timer_callback_t callback,
                        void* ctx, uint32_t interval_ms);
  my_ret_t (*remove_timer)(my_pal_main_loop_t* loop, uint32_t id);
  void (*destroy)(my_pal_main_loop_t* loop);
} my_pal_main_loop_vtable_t;

/** @brief Main loop base "class". */
struct my_pal_main_loop_t {
  const my_pal_main_loop_vtable_t* vtable;
};

static inline my_ret_t my_pal_main_loop_run(my_pal_main_loop_t* loop) {
  return loop->vtable->run(loop);
}

static inline my_ret_t my_pal_main_loop_quit(my_pal_main_loop_t* loop) {
  return loop->vtable->quit(loop);
}

static inline my_ret_t my_pal_main_loop_post_event(my_pal_main_loop_t* loop,
                                                   const my_event_t* event) {
  return loop->vtable->post_event(loop, event);
}

static inline uint32_t my_pal_main_loop_add_timer(my_pal_main_loop_t* loop,
                                                  my_timer_callback_t callback,
                                                  void* ctx,
                                                  uint32_t interval_ms) {
  return loop->vtable->add_timer(loop, callback, ctx, interval_ms);
}

static inline my_ret_t my_pal_main_loop_remove_timer(my_pal_main_loop_t* loop,
                                                     uint32_t id) {
  return loop->vtable->remove_timer(loop, id);
}

static inline void my_pal_main_loop_destroy(my_pal_main_loop_t* loop) {
  if (loop != NULL) {
    loop->vtable->destroy(loop);
  }
}

/* ---------------- platform ---------------- */

/** @brief Platform vtable. */
typedef struct my_pal_vtable_t {
  /** @brief Create a hidden window of w x h (title may be NULL). Sizes
   * are LOGICAL pixels (M12c): on HiDPI setups the port renders into a
   * physical buffer of logical*scale and reports logical sizes/events
   * back to the app. */
  my_pal_window_t* (*window_create)(my_pal_t* pal, int32_t w, int32_t h,
                                    const char* title);
  my_pal_main_loop_t* (*main_loop_create)(my_pal_t* pal);
  /** @brief Monotonic clock in milliseconds. */
  uint64_t (*time_now_ms)(my_pal_t* pal);
  /** @brief Register the single application event handler. */
  my_ret_t (*set_event_handler)(my_pal_t* pal, my_pal_event_handler_t handler,
                                void* ctx);
  /**
   * @brief Clipboard (M8c). set stores UTF-8 text; get copies into buf
   * (returns MY_RET_NOT_FOUND when empty, MY_RET_PENDING while an external
   * selection transfer is in flight, MY_RET_NOT_SUPPORTED when absent).
   */
  my_ret_t (*clipboard_set_text)(my_pal_t* pal, const char* text);
  my_ret_t (*clipboard_get_text)(my_pal_t* pal, char* buf, size_t size);
  /**
   * @brief Copy the complete clipboard into memory allocated by allocator.
   * The caller owns *out and releases it with my_mem_free(allocator, *out).
   * NULL means the legacy bounded clipboard_get_text implementation is used.
   */
  my_ret_t (*clipboard_get_text_alloc)(my_pal_t* pal,
                                       const my_allocator_t* allocator,
                                       char** out);
  /**
   * @brief Display scale factor (M12c; 1.0 = standard DPI). Physical
   * render buffers are logical*scale; window sizes and event
   * coordinates stay in logical pixels at the PAL boundary.
   */
  float (*get_scale_factor)(my_pal_t* pal);
  void (*destroy)(my_pal_t* pal);
  /**
   * @brief Whether the compositor/WM provides NO server-side decoration
   * for our windows (M16): true => my_window draws its own title bar
   * (CSD). wayland (mutter on plain xdg-shell gives no SSD) = true;
   * x11/dummy/linux_fb = false. Optional slot: NULL means false.
   */
  bool (*needs_client_decoration)(my_pal_t* pal);
} my_pal_vtable_t;

/** @brief Platform base "class". */
struct my_pal_t {
  const my_pal_vtable_t* vtable;
};

static inline my_pal_window_t* my_pal_window_create(my_pal_t* pal, int32_t w,
                                                    int32_t h,
                                                    const char* title) {
  return pal->vtable->window_create(pal, w, h, title);
}

static inline my_pal_main_loop_t* my_pal_main_loop_create(my_pal_t* pal) {
  return pal->vtable->main_loop_create(pal);
}

static inline uint64_t my_pal_time_now_ms(my_pal_t* pal) {
  return pal->vtable->time_now_ms(pal);
}

static inline my_ret_t my_pal_set_event_handler(my_pal_t* pal,
                                                my_pal_event_handler_t handler,
                                                void* ctx) {
  return pal->vtable->set_event_handler(pal, handler, ctx);
}

static inline my_ret_t my_pal_clipboard_set_text(my_pal_t* pal,
                                                 const char* text) {
  return pal->vtable->clipboard_set_text(pal, text);
}

static inline my_ret_t my_pal_clipboard_get_text(my_pal_t* pal, char* buf,
                                                 size_t size) {
  return pal->vtable->clipboard_get_text(pal, buf, size);
}

static inline my_ret_t my_pal_clipboard_get_text_alloc(
    my_pal_t* pal, const my_allocator_t* allocator, char** out) {
  if (out == NULL) {
    return MY_RET_INVALID_PARAMS;
  }
  *out = NULL;
  if (pal->vtable->clipboard_get_text_alloc == NULL) {
    return MY_RET_NOT_SUPPORTED;
  }
  return pal->vtable->clipboard_get_text_alloc(pal, allocator, out);
}

static inline float my_pal_get_scale_factor(my_pal_t* pal) {
  return pal->vtable->get_scale_factor(pal);
}

/** @brief M16: true when the port's compositor gives no SSD and windows
 * must draw their own title bar (NULL slot = false). */
static inline bool my_pal_needs_client_decoration(my_pal_t* pal) {
  return pal->vtable->needs_client_decoration != NULL &&
         pal->vtable->needs_client_decoration(pal);
}

static inline void my_pal_destroy(my_pal_t* pal) {
  if (pal != NULL) {
    pal->vtable->destroy(pal);
  }
}

/**
 * @brief Create the platform object for the compile-time selected port
 * (MYUI_PAL_X11 / MYUI_PAL_DUMMY). NULL allocator = default.
 */
my_pal_t* my_pal_create(const my_allocator_t* allocator);

#endif /* MY_PAL_H */
