/**
 * @file my_window.h
 * @brief Top-level window: a root widget bound to a PAL window.
 *
 * A window owns its PAL window and a vgcanvas (software backend over the
 * PAL window's lcd by default; injectable for tests). Dirty rects from
 * my_widget_invalidate() collect here (the root's dirty_sink); painting
 * redraws only the dirty regions.
 */
#ifndef MY_WINDOW_H
#define MY_WINDOW_H

#include "mypal/my_pal.h"
#include "myui/my_event_dispatch.h"

struct my_window_manager_t;

/** @brief GPU backends selectable through my_window_enable_gpu (M25a). */
typedef enum my_gpu_backend_t {
  MY_GPU_AUTO = 0, /**< try GLES2 -> OPENGL -> VULKAN, else stay soft */
  MY_GPU_SOFT,     /**< CPU rasterizer (always available) */
  MY_GPU_GLES2,    /**< OpenGL ES 2.0 (most mature GL path) */
  MY_GPU_OPENGL,   /**< desktop OpenGL (compat profile, GLSL 1.20) */
  MY_GPU_VULKAN    /**< Vulkan WSI canvas (requires PAL + Vulkan build) */
} my_gpu_backend_t;

/** @brief Top-level window (IS-A widget: embed as first member). */
typedef struct my_window_t {
  my_widget_t base;                  /**< root widget of the window */
  const my_allocator_t* allocator;
  my_pal_t* pal;                     /**< borrowed */
  my_pal_main_loop_t* loop;          /**< borrowed; set by wm open (M8c) */
  my_pal_window_t* pal_window;       /**< owned */
  my_vgcanvas_t* vg;                 /**< soft backend, or injected (tests) */
  bool vg_owned;
  my_pal_gl_t* gl;                   /**< GL mount when GL enabled (M10c) */
  bool gl_owned;
  void* undo_manager;      /**< borrowed my_undo_manager_t (M11b) */
  float scale;             /**< cached display scale (M12c HiDPI) */
  my_color_t bg_color;
  my_theme_t* theme;                 /**< active theme */
  bool theme_owned;
  my_font_t* font;                   /**< borrowed default font */
  int32_t font_size;
  my_dirty_rects_t dirty;            /**< frame dirty collector (sink) */
  my_event_dispatcher_t dispatcher;
  bool modal;
  bool scrim; /**< paint a translucent veil (modal dialog above, M13c) */
  my_widget_t* tip_target;  /**< weak: hovered widget owning a tooltip */
  my_widget_t* tip_widget;  /**< ours while shown (floating tip, M13c) */
  uint32_t tip_timer;       /**< pending hover timer id, 0 = none */
  int32_t tip_x;            /**< cursor pos at hover start (window space) */
  int32_t tip_y;
  my_cursor_t cursor; /**< last shape applied via the pal (M21a; the
                       * dispatcher's hover tracking drives it) */
  char* title;       /**< owned copy (M16: CSD bar text) */
  struct my_window_manager_t* wm; /**< weak: set by wm open (M16) */
  bool csd;                 /**< client-side decoration active (M16) */
  my_widget_t* csd_content; /**< CSD content container (weak; the root
                             * holds the tree ref) */
  my_gpu_backend_t gpu_backend; /**< active backend (M25a/b; SOFT init) */
} my_window_t;

/** @brief Create a window (hidden) of w x h with the given title. */
my_window_t* my_window_create(const my_allocator_t* allocator, my_pal_t* pal,
                              int32_t w, int32_t h, const char* title);

/**
 * @brief The widget apps add children to. In CSD mode (M16: the port's
 * compositor provides no decoration) this is the borrowed content container
 * BELOW the built-in title bar; otherwise the window root itself.
 * Window internals (paint/hit/dispatch) always operate on the root. Callers
 * must not unref the returned widget.
 */
static inline my_widget_t* my_window_widget(my_window_t* win) {
  return win->csd && win->csd_content != NULL ? win->csd_content
                                              : (my_widget_t*)win;
}

/**
 * @brief Paint if dirty: relayout when needed, then for each dirty rect
 * clip and repaint the tree; commits dirty consumption only after the canvas
 * frame succeeds. No-op when clean.
 */
void my_window_paint(my_window_t* win);

/**
 * @brief Synchronize the canvas with the PAL's current content scale.
 *
 * A scale change preserves logical layout coordinates, reapplies the canvas
 * configuration, and invalidates the full logical window. The caller owns
 * resizing any injected drawable target before the next paint.
 * @return true only when the effective scale changed.
 */
bool my_window_refresh_scale(my_window_t* win);

/**
 * @brief Settle pending measurement/layout passes before damage collection.
 *
 * Layout callbacks may request one follow-up pass when content-driven geometry
 * changes affect an ancestor. Shared-surface compositors must call this before
 * collecting cross-window damage.
 */
my_ret_t my_window_prepare_layout(my_window_t* win);

/**
 * @brief Record this window's dirty regions into an already-open vgcanvas
 * frame, then clear them. Used by shared-surface compositors to batch a whole
 * logical window stack into one GPU submission. The compositor must call
 * my_window_refresh_scale() and my_window_prepare_layout() before collecting
 * damage when scale or content-driven geometry may have changed. On failure,
 * the window keeps its dirty regions pending.
 */
my_ret_t my_window_record_dirty(my_window_t* win);

/**
 * @brief Merge a previously staged dirty snapshot back into this window.
 *
 * Existing dirty regions are preserved, so invalidation raised while a
 * previous frame was being painted is not lost during compositor rollback.
 */
void my_window_restore_dirty(my_window_t* win,
                             const my_dirty_rects_t* snapshot);

/**
 * @brief Route one PAL event (PAINT/RESIZE/POINTER_x/KEY_x) into the
 * window. Paints immediately when the dispatch left the window dirty.
 */
my_ret_t my_window_on_pal_event(my_window_t* win, const my_event_t* event);

/**
 * @brief The pal of the window at the root of widget's tree (NULL when
 * the widget is not under a my_window root).
 */
my_pal_t* my_window_pal_of_widget(my_widget_t* widget);

/** @brief The main loop of the window at the root (NULL when unknown). */
my_pal_main_loop_t* my_window_loop_of_widget(my_widget_t* widget);

/** @brief The window's default font for a widget (see my_window.c). */
void my_window_font_of_widget(my_widget_t* widget, my_font_t** font,
                              int32_t* font_size);

/**
 * @brief Attach a shared undo manager (M11b, borrowed; the app owns and
 * destroys it). Widgets can then find it via
 * my_window_undo_manager_of_widget.
 */
void my_window_set_undo_manager(my_window_t* win, void* mgr);

/** @brief The undo manager of the window at the root of widget's tree
 * (NULL when none / not under a window). */
void* my_window_undo_manager_of_widget(my_widget_t* widget);

/** @brief Test hook: use this vgcanvas instead of creating a soft one. */
void my_window_set_vgcanvas(my_window_t* win, my_vgcanvas_t* vg);

/**
 * @brief Switch this window to GLES rendering (M10c): enables the PAL
 * window's GL mount and replaces the vgcanvas with the GLES2 backend.
 * Painting then makes the context current and swaps buffers at frame
 * end; resizes update the GL viewport. Returns MY_RET_NOT_SUPPORTED
 * when the port/build has no GL support, MY_RET_FAIL when context or
 * backend creation fails (the window keeps the soft path then).
 */
my_ret_t my_window_enable_gl(my_window_t* win);

/**
 * @brief Unified GPU backend selection (M25a). GLES2/OPENGL mount the
 * PAL window's GL context for that API and switch the vgcanvas to the
 * GLES2 backend (the desktop path adapts the shaders via the my_gl_t
 * header seam). SOFT tears down any GL mount and returns to the CPU
 * rasterizer. AUTO tries GLES2 first (the most mature path), then
 * OPENGL, then VULKAN, and stays soft (returning OK) when all fail.
 * The candidate backend is created and validated before the current backend
 * is replaced, so a creation failure preserves the previous active state.
 * Returns MY_RET_NOT_SUPPORTED when the requested backend is unavailable
 * on this port/build, MY_RET_FAIL when context/backend creation fails.
 * Resize events use logical pixels for widget layout. GPU canvas viewport,
 * swapchain and framebuffer sizes use the PAL-reported drawable pixels.
 */
my_ret_t my_window_enable_gpu(my_window_t* win, my_gpu_backend_t backend);
/**
 * @brief Set the window's default font (borrowed ref; the caller keeps
 * and eventually destroys it). Applied to the window's vgcanvas.
 */
void my_window_set_font(my_window_t* win, my_font_t* font, int32_t size);

/**
 * @brief Switch the window's theme (and apply it to the widget tree).
 * When take_ownership is true the window destroys it on replace/destroy.
 */
void my_window_set_theme(my_window_t* win, my_theme_t* theme,
                         bool take_ownership);

#endif /* MY_WINDOW_H */
