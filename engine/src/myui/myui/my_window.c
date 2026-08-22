/**
 * @file my_window.c
 * @brief Top-level window implementation.
 */
#include "myui/my_window.h"

#include <string.h>

#include "myc/my_str.h"
#include "myr/my_gl_desktop.h"
#include "myr/my_vgcanvas_gles2.h"
#include "myr/my_vgcanvas_soft.h"
#include "myr/my_vgcanvas_vulkan.h"
#include "myui/my_animator.h"
#include "myui/my_layout.h"
#include "myui/my_window_manager.h"

/* ---------------- widget vtable ---------------- */

static void tip_cancel_timer(my_window_t* win);
static void tip_hide(my_window_t* win);
static void csd_bar_layout(my_widget_t* widget);
static void window_release_gpu_resources(my_window_t* win);
static void window_configure_vgcanvas(const my_window_t* win,
                                      my_vgcanvas_t* vg);

bool my_window_refresh_scale(my_window_t* win) {
  float scale;
  if (win == NULL || win->pal == NULL) {
    return false;
  }
  scale = my_pal_get_scale_factor(win->pal);
  if (!(scale > 0.0f) || scale != scale || scale == win->scale) {
    return false;
  }
  win->scale = scale;
  window_configure_vgcanvas(win, win->vg);
  my_widget_invalidate((my_widget_t*)win, NULL);
  return true;
}

static void window_on_paint(my_widget_t* widget, my_vgcanvas_t* vg) {
  my_window_t* win = (my_window_t*)widget;
  uint32_t bg = my_widget_style_get_color(widget, MY_STATE_NORMAL, MY_STYLE_BG_COLOR,
                                          my_color_to_rgba32(win->bg_color));
  my_vgcanvas_set_fill_color(vg, my_color_from_rgba32(bg));
  my_vgcanvas_fill_rect(vg, &(my_rectf_t){0, 0, (float)widget->rect.w,
                                          (float)widget->rect.h});
}

static const my_widget_vtable_t s_window_vtable = {window_on_paint, NULL, NULL, NULL};

/* ---------------- CSD title bar (M16) ---------------- */

#define CSD_BAR_H 36
#define CSD_BAR_BG 0x3C4043FFu  /**< GNOME-ish dark grey */
#define CSD_CLOSE_HOVER 0xE81123FFu /**< convention red */

typedef struct csd_bar_t {
  my_widget_t base;
  my_window_t* win; /**< weak */
} csd_bar_t;

typedef struct csd_close_t {
  my_widget_t base;
  my_window_t* win; /**< weak */
} csd_close_btn_t;

static void csd_bar_paint(my_widget_t* widget, my_vgcanvas_t* vg) {
  csd_bar_t* bar = (csd_bar_t*)widget;
  my_window_t* win = bar->win;
  int32_t tw = 0, th = 0;
  my_vgcanvas_set_fill_color(vg, my_color_from_rgba32(CSD_BAR_BG));
  my_vgcanvas_fill_rect(vg, &(my_rectf_t){0, 0, (float)widget->rect.w,
                                          (float)widget->rect.h});
  if (win->title != NULL) {
    my_vgcanvas_set_font(vg, NULL, 13);
    if (my_vgcanvas_measure_text(vg, win->title, &tw, &th) != MY_RET_OK) {
      tw = (int32_t)strlen(win->title) * 8;
      th = 13;
    }
    my_vgcanvas_set_fill_color(vg, my_color_from_rgba32(0xFFFFFFFFu));
    my_vgcanvas_draw_text(vg, win->title,
                          ((float)widget->rect.w - (float)tw) / 2.0f,
                          ((float)widget->rect.h - (float)th) / 2.0f);
  }
}

static my_ret_t csd_bar_event(my_widget_t* widget, const my_event_t* event) {
  csd_bar_t* bar = (csd_bar_t*)widget;
  /* only direct hits on the bar body reach here: the close button is a
   * child and eats its own DOWN/UP first */
  if (event->type == MY_EVENT_POINTER_DOWN) {
    my_pal_window_begin_move(bar->win->pal_window);
    return MY_RET_OK;
  }
  return MY_RET_FAIL;
}

static void csd_close_paint(my_widget_t* widget, my_vgcanvas_t* vg) {
  my_vgcanvas_set_fill_color(
      vg, my_color_from_rgba32(widget->hovered ? CSD_CLOSE_HOVER
                                               : CSD_BAR_BG));
  my_vgcanvas_fill_rect(vg, &(my_rectf_t){0, 0, (float)widget->rect.w,
                                          (float)widget->rect.h});
  my_vgcanvas_set_font(vg, NULL, 14);
  my_vgcanvas_set_fill_color(vg, my_color_from_rgba32(0xFFFFFFFFu));
  my_vgcanvas_draw_text(vg, "\xC3\x97" /* × */, 11, 10);
}

static my_ret_t csd_close_event(my_widget_t* widget, const my_event_t* event) {
  csd_close_btn_t* btn = (csd_close_btn_t*)widget;
  if (event->type == MY_EVENT_POINTER_DOWN) {
    return MY_RET_OK;
  }
  if (event->type == MY_EVENT_POINTER_UP) {
    my_window_t* win = btn->win;
    if (win->wm == NULL || win->loop == NULL) {
      /* not under a window manager: nothing to route a close through
       * (the QUIT path lives in the wm) — no-op by design */
      return MY_RET_OK;
    }
    (void)my_window_manager_close(win->wm, win);
    return MY_RET_OK;
  }
  return MY_RET_FAIL;
}

static const my_widget_vtable_t s_csd_bar_vtable = {csd_bar_paint,
                                                    csd_bar_event,
                                                    csd_bar_layout, NULL};
static const my_widget_vtable_t s_csd_close_vtable = {csd_close_paint,
                                                      csd_close_event, NULL, NULL};

/** @brief Keep the close button glued to the bar's right edge. */
static void csd_bar_layout(my_widget_t* widget) {
  size_t n = my_widget_child_count(widget);
  if (n > 0) {
    my_widget_t* close_btn = my_widget_get_child(widget, n - 1);
    (void)my_widget_set_layout_rect(
        close_btn, &(my_rect_t){widget->rect.w - 32, 0, 32, widget->rect.h});
  }
}

/** @brief Build the CSD title bar + content container under the root
 * (vertical linear: bar h:36 + content h:1f). */
static void window_setup_csd(my_window_t* win) {
  my_widget_t* root = (my_widget_t*)win;
  csd_bar_t* bar;
  csd_close_btn_t* close_btn;
  my_widget_t* content;
  my_widget_set_layouter(root, my_layouter_linear_create(win->allocator,
                                                         false, 0));
  bar = (csd_bar_t*)my_mem_calloc(win->allocator, 1, sizeof(csd_bar_t));
  content = my_widget_create(win->allocator, "csd_content");
  if (bar == NULL || content == NULL ||
      my_widget_init((my_widget_t*)bar, win->allocator, &s_csd_bar_vtable,
                     "csd_bar") != MY_RET_OK) {
    my_mem_free(win->allocator, bar);
    if (content != NULL) {
      my_widget_unref(content);
    }
    return; /* out of memory: stay undecorated rather than broken */
  }
  bar->win = win;
  my_widget_set_layout_params((my_widget_t*)bar, "h:36");
  close_btn =
      (csd_close_btn_t*)my_mem_calloc(win->allocator, 1, sizeof(csd_close_btn_t));
  if (close_btn != NULL &&
      my_widget_init((my_widget_t*)close_btn, win->allocator,
                     &s_csd_close_vtable, "csd_close") == MY_RET_OK) {
    close_btn->win = win;
    ((my_widget_t*)close_btn)->rect =
        my_rect_init(0, 0, 32, CSD_BAR_H); /* x set in csd_bar_layout */
    my_widget_add_child((my_widget_t*)bar, (my_widget_t*)close_btn);
    my_widget_unref((my_widget_t*)close_btn);
  } else {
    my_mem_free(win->allocator, close_btn);
  }
  my_widget_set_layout_params(content, "h:1f");
  my_widget_add_child(root, (my_widget_t*)bar);
  my_widget_unref((my_widget_t*)bar);
  my_widget_add_child(root, content);
  my_widget_unref(content);
  /* The root owns the content reference. my_window_widget() exposes this
   * node as a borrowed access point, matching the non-CSD root accessor. */
  win->csd_content = content;
  win->csd = true;
}

/* ---------------- lifecycle ---------------- */

/** @brief Root hook: a subtree is being removed -> drop dispatcher refs
 * and cancel its animations. */
static void window_on_subtree_removed(my_widget_t* root, my_widget_t* removed) {
  my_window_t* win = (my_window_t*)root;
  my_widget_t* w;
  my_event_dispatcher_forget(&win->dispatcher, removed);
  if (root->anim_mgr != NULL) {
    my_animator_stop_widget((my_animator_manager_t*)root->anim_mgr, removed);
  }
  /* tooltip (M13c): drop hover state pointing into the removed subtree */
  for (w = win->tip_target; w != NULL; w = w->parent) {
    if (w == removed) {
      win->tip_target = NULL;
      tip_cancel_timer(win);
      if (win->tip_widget != NULL) {
        tip_hide(win); /* safe: tip is never inside `removed` */
      }
      break;
    }
  }
}

static void window_destroy_chain(my_object_t* obj) {
  my_window_t* win = (my_window_t*)obj;
  tip_cancel_timer(win);
  tip_hide(win); /* we hold one ref; the tree holds the other */
  win->tip_target = NULL;
  if (((my_widget_t*)win)->anim_mgr != NULL) {
    my_animator_stop_widget((my_animator_manager_t*)((my_widget_t*)win)->anim_mgr,
                            (my_widget_t*)win);
  }
  window_release_gpu_resources(win);
  if (win->theme_owned) {
    my_theme_destroy(win->theme);
  }
  win->theme = NULL;
  my_mem_free(win->allocator, win->title);
  win->title = NULL;
  my_pal_window_destroy(win->pal_window);
  win->pal_window = NULL;
  my_widget_destroy((my_widget_t*)win);
  my_object_destroy(obj);
}

my_window_t* my_window_create(const my_allocator_t* allocator, my_pal_t* pal,
                              int32_t w, int32_t h, const char* title) {
  my_window_t* win;
  if (pal == NULL || w <= 0 || h <= 0) {
    return NULL;
  }
  win = (my_window_t*)my_mem_calloc(allocator, 1, sizeof(my_window_t));
  if (win == NULL) {
    return NULL;
  }
  if (my_widget_init((my_widget_t*)win, allocator, &s_window_vtable, "window") !=
      MY_RET_OK) {
    my_mem_free(allocator, win);
    return NULL;
  }
  ((my_object_t*)win)->destroy = window_destroy_chain;
  win->allocator = allocator;
  win->pal = pal;
  win->pal_window = my_pal_window_create(pal, w, h, title);
  if (win->pal_window == NULL) {
    my_object_unref((my_object_t*)win);
    return NULL;
  }
  win->bg_color = my_color_rgb(32, 32, 32);
  win->title = my_strdup(allocator, title); /* M16: CSD bar text */
  win->scale = my_pal_get_scale_factor(pal); /* HiDPI (M12c): applied to
                                                the vgcanvas in ensure/GL */
  if (win->scale <= 0.0f) {
    win->scale = 1.0f;
  }
  win->vg = NULL;
  win->vg_owned = false;
  win->gpu_backend = MY_GPU_SOFT;
  win->modal = false;
  win->theme = my_theme_default_create(allocator);
  win->theme_owned = win->theme != NULL;
  ((my_widget_t*)win)->rect = my_rect_init(0, 0, w, h);
  ((my_widget_t*)win)->widget_type = "window";
  ((my_widget_t*)win)->dirty_sink = &win->dirty;
  ((my_widget_t*)win)->theme = win->theme;
  ((my_widget_t*)win)->removed_hook = window_on_subtree_removed;
  my_dirty_rects_init(&win->dirty);
  my_event_dispatcher_init(&win->dispatcher, (my_widget_t*)win);
  if (my_pal_needs_client_decoration(pal)) {
    window_setup_csd(win); /* M16: compositor gives no SSD (mutter/wl) */
  }
  return win;
}

static void window_configure_vgcanvas(const my_window_t* win,
                                      my_vgcanvas_t* vg) {
  if (win == NULL || vg == NULL) {
    return;
  }
  (void)my_vgcanvas_set_scale(vg, win->scale);
  if (win->font != NULL) {
    (void)my_vgcanvas_set_font(vg, win->font, win->font_size);
  }
}

static void window_release_gpu_resources(my_window_t* win) {
  if (win == NULL) {
    return;
  }
  if (win->vg_owned) {
    if (win->gl != NULL && win->gpu_backend != MY_GPU_VULKAN) {
      (void)my_pal_gl_make_current(win->gl);
    }
    my_vgcanvas_destroy(win->vg);
    win->vg = NULL;
    win->vg_owned = false;
  }
  if (win->gl_owned) {
    my_pal_gl_destroy(win->gl);
  }
  win->gl = NULL;
  win->gl_owned = false;
  win->gpu_backend = MY_GPU_SOFT;
}

static void window_release_gpu_resources_except(my_window_t* win,
                                                my_pal_gl_t* keep_gl) {
  if (win == NULL) {
    return;
  }
  if (win->vg_owned) {
    if (win->gl != NULL && win->gpu_backend != MY_GPU_VULKAN) {
      (void)my_pal_gl_make_current(win->gl);
    }
    my_vgcanvas_destroy(win->vg);
  }
  if (win->gl_owned && win->gl != NULL && win->gl != keep_gl) {
    my_pal_gl_destroy(win->gl);
  }
  win->vg = NULL;
  win->vg_owned = false;
  win->gl = keep_gl;
  win->gl_owned = keep_gl != NULL;
  win->gpu_backend = MY_GPU_SOFT;
}

void my_window_set_vgcanvas(my_window_t* win, my_vgcanvas_t* vg) {
  if (win == NULL) {
    return;
  }
  if (win->vg == vg) {
    window_configure_vgcanvas(win, vg);
    return;
  }
  window_release_gpu_resources(win);
  win->vg = vg;
  win->vg_owned = false;
  window_configure_vgcanvas(win, vg);
}

/** @brief Shared GLES2/OPENGL enable path (M25a): mount the PAL GL
 * context for `api` and switch the vgcanvas to the gles2 backend driven
 * by `gl_table` (NULL table = the backend was stubbed at build time). */
static my_ret_t window_enable_gpu_gl(my_window_t* win, int api,
                                     const my_gl_t* gl_table) {
  my_pal_gl_t* gl;
  my_vgcanvas_t* vg;
  my_gpu_backend_t target;
  int32_t w = 0, h = 0;
  target = api == MY_PAL_GL_API_OPENGL ? MY_GPU_OPENGL : MY_GPU_GLES2;
  if (win->gpu_backend == target && win->gl != NULL && win->vg != NULL) {
    return MY_RET_OK;
  }
  if (gl_table == NULL) {
    return MY_RET_NOT_SUPPORTED; /* backend not built in */
  }
  gl = my_pal_window_gl_enable_api(win->pal_window, api);
  if (gl == NULL) {
    return MY_RET_NOT_SUPPORTED;
  }
  if (my_pal_gl_make_current(gl) != MY_RET_OK) {
    if (gl != win->gl) {
      my_pal_gl_destroy(gl);
    }
    return MY_RET_FAIL;
  }
  my_pal_gl_get_size(gl, &w, &h);
  vg = my_vgcanvas_gles2_create_with_gl(win->allocator, w, h, gl_table);
  if (vg == NULL) {
    if (gl != win->gl) {
      my_pal_gl_destroy(gl);
    }
    return MY_RET_FAIL;
  }
  /* PAL owns the surface configuration, so use its negotiated sample state
   * as the final source of truth for the portable canvas contract. */
  if (my_vgcanvas_gles2_set_multisample_available(
          vg, my_pal_gl_has_multisample(gl)) != MY_RET_OK) {
    my_vgcanvas_destroy(vg);
    if (gl != win->gl) {
      my_pal_gl_destroy(gl);
    }
    return MY_RET_FAIL;
  }
  window_release_gpu_resources_except(win, gl);
  win->vg = vg;
  win->vg_owned = true;
  win->gl = gl;
  win->gl_owned = true;
  win->gpu_backend = target;
  window_configure_vgcanvas(win, vg);
  return MY_RET_OK;
}

/** @brief Tear down any GL mount and return to the soft rasterizer. */
static my_ret_t window_enable_gpu_soft(my_window_t* win) {
  if (win->gl != NULL || win->gpu_backend != MY_GPU_SOFT) {
    window_release_gpu_resources(win);
  }
  return MY_RET_OK;
}

/* ---------------- vulkan present adapter (M25b) ----------------
 * Mounts my_vgcanvas_vulkan_present() as the GL-adapter swap_buffers so
 * the window's present protocol (make_current -> paint -> swap) works
 * unchanged. */

typedef struct vk_present_adapter_t {
  my_pal_gl_t base;
  my_vgcanvas_t* vg;    /**< borrowed (owned by the window) */
  my_pal_window_t* win; /**< borrowed (for get_size) */
  my_pal_t* pal;        /**< borrowed (for the current display scale) */
  const my_allocator_t* allocator;
  float scale;
} vk_present_adapter_t;

static my_ret_t vk_adapter_make_current(my_pal_gl_t* gl) {
  (void)gl; /* no-op: the vulkan backend needs no current context */
  return MY_RET_OK;
}

static my_ret_t vk_adapter_swap(my_pal_gl_t* gl) {
  return my_vgcanvas_vulkan_present(((vk_present_adapter_t*)gl)->vg);
}

static my_ret_t vk_adapter_get_size(my_pal_gl_t* gl, int32_t* w, int32_t* h) {
  vk_present_adapter_t* adapter = (vk_present_adapter_t*)gl;
  int32_t logical_w = 0;
  int32_t logical_h = 0;
  float scale = adapter->scale;
  my_ret_t ret = my_pal_window_get_size(adapter->win, &logical_w, &logical_h);
  if (ret != MY_RET_OK) {
    return ret;
  }
  if (adapter->pal != NULL) {
    float current_scale = my_pal_get_scale_factor(adapter->pal);
    if (current_scale > 0.0f) {
      scale = current_scale;
    }
  }
  if (w != NULL) {
    *w = (int32_t)((float)logical_w * scale + 0.5f);
  }
  if (h != NULL) {
    *h = (int32_t)((float)logical_h * scale + 0.5f);
  }
  return MY_RET_OK;
}

static bool vk_adapter_has_multisample(my_pal_gl_t* gl) {
  (void)gl;
  return true; /* the backend prefers MSAA4 with single-sample fallback */
}

static void vk_adapter_destroy(my_pal_gl_t* gl) {
  vk_present_adapter_t* a = (vk_present_adapter_t*)gl;
  if (a != NULL) {
    my_mem_free(a->allocator, a); /* the vgcanvas is NOT ours */
  }
}

static const my_pal_gl_vtable_t VK_ADAPTER_VTABLE = {
    vk_adapter_make_current, vk_adapter_swap, vk_adapter_get_size,
    vk_adapter_has_multisample, vk_adapter_destroy};

static my_ret_t window_enable_gpu_vulkan(my_window_t* win) {
  void* inst;
  void* surf;
  my_vgcanvas_t* vg;
  vk_present_adapter_t* ad;
  int32_t w = 0, h = 0;
  if (win->gpu_backend == MY_GPU_VULKAN && win->gl != NULL &&
      win->vg != NULL) {
    return MY_RET_OK;
  }
  inst = my_vgcanvas_vulkan_instance();
  if (inst == NULL) {
    return MY_RET_NOT_SUPPORTED;
  }
  surf = my_pal_window_vk_create_surface(win->pal_window, inst);
  if (surf == NULL) {
    return MY_RET_NOT_SUPPORTED;
  }
  my_pal_window_get_size(win->pal_window, &w, &h);
  w = (int32_t)((float)w * win->scale + 0.5f);
  h = (int32_t)((float)h * win->scale + 0.5f);
  vg = my_vgcanvas_vulkan_create(win->allocator, surf, w > 0 ? w : 1,
                                 h > 0 ? h : 1);
  if (vg == NULL) {
    my_vgcanvas_vulkan_destroy_surface(surf);
    return MY_RET_FAIL;
  }
  ad = (vk_present_adapter_t*)my_mem_calloc(win->allocator, 1,
                                            sizeof(vk_present_adapter_t));
  if (ad == NULL) {
    my_vgcanvas_destroy(vg); /* destroys the surface with it */
    return MY_RET_OOM;
  }
  ad->base.vtable = &VK_ADAPTER_VTABLE;
  ad->vg = vg;
  ad->win = win->pal_window;
  ad->pal = win->pal;
  ad->allocator = win->allocator;
  ad->scale = win->scale;
  window_release_gpu_resources(win);
  win->vg = vg;
  win->vg_owned = true;
  win->gl = (my_pal_gl_t*)ad;
  win->gl_owned = true;
  win->gpu_backend = MY_GPU_VULKAN;
  window_configure_vgcanvas(win, vg);
  return MY_RET_OK;
}

my_ret_t my_window_enable_gpu(my_window_t* win, my_gpu_backend_t backend) {
  if (win == NULL) {
    return MY_RET_INVALID_PARAMS;
  }
  switch (backend) {
    case MY_GPU_SOFT:
      return window_enable_gpu_soft(win);
    case MY_GPU_GLES2:
      return window_enable_gpu_gl(win, MY_PAL_GL_API_GLES2,
                                  my_gl_real_default());
    case MY_GPU_OPENGL:
      return window_enable_gpu_gl(win, MY_PAL_GL_API_OPENGL,
                                  my_gl_desktop_default());
    case MY_GPU_VULKAN:
      return window_enable_gpu_vulkan(win);
    case MY_GPU_AUTO:
      /* priority: GLES2 (most mature) -> OPENGL -> VULKAN; all failed =
       * stay on the soft path, which is always OK (documented) */
      if (my_window_enable_gpu(win, MY_GPU_GLES2) == MY_RET_OK) {
        return MY_RET_OK;
      }
      if (my_window_enable_gpu(win, MY_GPU_OPENGL) == MY_RET_OK) {
        return MY_RET_OK;
      }
      if (my_window_enable_gpu(win, MY_GPU_VULKAN) == MY_RET_OK) {
        return MY_RET_OK;
      }
      return MY_RET_OK;
    default:
      return MY_RET_INVALID_PARAMS;
  }
}

my_ret_t my_window_enable_gl(my_window_t* win) {
  if (win == NULL) {
    return MY_RET_INVALID_PARAMS;
  }
  return my_window_enable_gpu(win, MY_GPU_GLES2);
}

void my_window_set_theme(my_window_t* win, my_theme_t* theme,
                         bool take_ownership) {
  if (win == NULL) {
    return;
  }
  if (win->theme_owned) {
    my_theme_destroy(win->theme);
  }
  win->theme = theme;
  win->theme_owned = take_ownership;
  my_widget_apply_theme((my_widget_t*)win, theme);
}

/* ---------------- painting ---------------- */

static my_vgcanvas_t* window_ensure_vg(my_window_t* win) {
  if (win->vg == NULL) {
    win->vg = my_vgcanvas_soft_create(win->allocator,
                                      my_pal_window_get_lcd(win->pal_window));
    win->vg_owned = win->vg != NULL;
    window_configure_vgcanvas(win, win->vg);
  }
  return win->vg;
}

void my_window_set_font(my_window_t* win, my_font_t* font, int32_t size) {
  if (win == NULL) {
    return;
  }
  win->font = font;
  win->font_size = size > 0 ? size : 16;
  if (win->vg != NULL) {
    my_vgcanvas_set_font(win->vg, font, win->font_size);
  }
}

#define MY_WINDOW_LAYOUT_MAX_PASSES 8

my_ret_t my_window_prepare_layout(my_window_t* win) {
  my_widget_t* root;
  int pass;
  if (win == NULL) {
    return MY_RET_INVALID_PARAMS;
  }
  root = (my_widget_t*)win;
  for (pass = 0;
       pass < MY_WINDOW_LAYOUT_MAX_PASSES &&
       (root->need_layout || root->subtree_need_layout);
       pass++) {
    my_widget_relayout_pending(root);
  }
  return root->need_layout || root->subtree_need_layout ? MY_RET_FAIL
                                                        : MY_RET_OK;
}

static my_ret_t window_record_dirty(my_window_t* win) {
  my_widget_t* root;
  my_vgcanvas_t* vg;
  my_dirty_rects_t frame_dirty;
  size_t i, n;
  if (win == NULL) {
    return MY_RET_INVALID_PARAMS;
  }
  if (my_window_prepare_layout(win) != MY_RET_OK) {
    return MY_RET_FAIL;
  }
  if (my_dirty_rects_count(&win->dirty) == 0) {
    return MY_RET_OK;
  }
  root = (my_widget_t*)win;
  vg = window_ensure_vg(win);
  if (vg == NULL) {
    return MY_RET_FAIL;
  }
  frame_dirty = win->dirty;
  my_dirty_rects_clear(&win->dirty);
  if (win->gl != NULL) {
    my_pal_gl_make_current(win->gl);
  }
  n = my_dirty_rects_count(&frame_dirty);
  for (i = 0; i < n; i++) {
    const my_rect_t* r = my_dirty_rects_get(&frame_dirty, i);
    my_vgcanvas_save(vg);
    my_vgcanvas_clip_rect(vg, &(my_rectf_t){(float)r->x, (float)r->y, (float)r->w,
                                            (float)r->h});
    my_widget_paint(root, vg);
    if (win->scrim) {
      /* modal veil (M13c): darken the blocked window under a dialog */
      my_vgcanvas_set_fill_color(vg, my_color_rgba(0, 0, 0, 96));
      my_vgcanvas_fill_rect(vg, &(my_rectf_t){(float)r->x, (float)r->y,
                                              (float)r->w, (float)r->h});
    }
    my_vgcanvas_restore(vg);
  }
  return MY_RET_OK;
}

my_ret_t my_window_record_dirty(my_window_t* win) {
  my_ret_t ret;
  my_window_t* held_win;
  if (win == NULL) {
    return MY_RET_INVALID_PARAMS;
  }
  held_win = (my_window_t*)my_widget_ref((my_widget_t*)win);
  ret = window_record_dirty(win);
  my_widget_unref((my_widget_t*)held_win);
  return ret;
}

void my_window_restore_dirty(my_window_t* win,
                             const my_dirty_rects_t* snapshot) {
  size_t i;
  if (win == NULL || snapshot == NULL) {
    return;
  }
  for (i = 0; i < my_dirty_rects_count(snapshot); i++) {
    const my_rect_t* rect = my_dirty_rects_get(snapshot, i);
    if (rect != NULL) {
      (void)my_dirty_rects_add(&win->dirty, rect);
    }
  }
  if (my_dirty_rects_count(snapshot) > 0) {
    ((my_widget_t*)win)->dirty = true;
  }
}

void my_window_paint(my_window_t* win) {
  my_vgcanvas_t* vg;
  my_dirty_rects_t frame_dirty;
  my_ret_t ret;
  my_window_t* held_win;
  if (win == NULL) {
    return;
  }
  held_win = (my_window_t*)my_widget_ref((my_widget_t*)win);
  (void)my_window_refresh_scale(win);
  if (my_window_prepare_layout(win) != MY_RET_OK) {
    goto done;
  }
  if (my_dirty_rects_count(&win->dirty) == 0) {
    goto done;
  }
  frame_dirty = win->dirty;
  vg = window_ensure_vg(win);
  if (vg == NULL) {
    goto done;
  }
  if (my_vgcanvas_begin_frame(vg, my_dirty_rects_get(&win->dirty, 0)) !=
      MY_RET_OK) {
    goto done;
  }
  ret = window_record_dirty(win);
  if (ret != MY_RET_OK) {
    my_window_restore_dirty(win, &frame_dirty);
    (void)my_vgcanvas_end_frame(vg);
    goto done;
  }
  if (my_vgcanvas_end_frame(vg) != MY_RET_OK) {
    my_window_restore_dirty(win, &frame_dirty);
    goto done;
  }
  if (win->gl != NULL) {
    my_pal_gl_swap_buffers(win->gl);
  }
done:
  my_widget_unref((my_widget_t*)held_win);
}

/* ---------------- tooltip (M13c) ---------------- */

#define TIP_DELAY_MS 500
#define TIP_DX 12
#define TIP_DY 16

/** @brief Paint the floating tip (text stored in its own tooltip field). */
static void tip_on_paint(my_widget_t* widget, my_vgcanvas_t* vg) {
  uint32_t bg = my_widget_style_get_color(widget, MY_STATE_NORMAL,
                                          MY_STYLE_BG_COLOR, 0x323232F2u);
  uint32_t fg = my_widget_style_get_color(widget, MY_STATE_NORMAL,
                                          MY_STYLE_FG_COLOR, 0xF5F5F5FFu);
  uint32_t border = my_widget_style_get_color(widget, MY_STATE_NORMAL,
                                              MY_STYLE_BORDER_COLOR, 0x616161FFu);
  my_vgcanvas_set_fill_color(vg, my_color_from_rgba32(bg));
  my_vgcanvas_fill_rect(vg, &(my_rectf_t){0, 0, (float)widget->rect.w,
                                          (float)widget->rect.h});
  my_vgcanvas_set_stroke_color(vg, my_color_from_rgba32(border));
  my_vgcanvas_set_line_width(vg, 1);
  my_vgcanvas_stroke_rect(vg, &(my_rectf_t){0, 0, (float)widget->rect.w,
                                            (float)widget->rect.h});
  if (widget->tooltip != NULL) {
    my_vgcanvas_set_fill_color(vg, my_color_from_rgba32(fg));
    my_vgcanvas_draw_text(vg, widget->tooltip, 6,
                          ((float)widget->rect.h - 8) / 2.0f);
  }
}

static const my_widget_vtable_t s_tip_vtable = {tip_on_paint, NULL, NULL, NULL};

/** @brief Remove the visible tip (reentrancy-safe via early NULL). */
static void tip_hide(my_window_t* win) {
  my_widget_t* tip = win->tip_widget;
  if (tip == NULL) {
    return;
  }
  win->tip_widget = NULL;
  my_widget_remove_child((my_widget_t*)win, tip);
  my_widget_unref(tip);
}

static void tip_cancel_timer(my_window_t* win) {
  if (win->tip_timer != 0 && win->loop != NULL) {
    my_pal_main_loop_remove_timer(win->loop, win->tip_timer);
  }
  win->tip_timer = 0;
}

/** @brief One-shot hover timer fired: pop the tip near the cursor. */
static my_ret_t tip_on_timer(void* ctx) {
  my_window_t* win = (my_window_t*)ctx;
  my_widget_t* root = (my_widget_t*)win;
  my_widget_t* tip;
  const char* text;
  int32_t w, h, x, y;
  win->tip_timer = 0;
  if (win->tip_target == NULL) {
    return MY_RET_FAIL;
  }
  text = win->tip_target->tooltip;
  if (text == NULL || text[0] == '\0') {
    return MY_RET_FAIL;
  }
  w = (int32_t)strlen(text) * 8 + 12;
  h = 22;
  x = win->tip_x + TIP_DX;
  y = win->tip_y + TIP_DY;
  if (x + w > root->rect.w) {
    x = root->rect.w - w;
  }
  if (y + h > root->rect.h) {
    y = win->tip_y - TIP_DY - h; /* flip above the cursor */
  }
  if (x < 0) {
    x = 0;
  }
  if (y < 0) {
    y = 0;
  }
  tip = my_widget_create(win->allocator, "tooltip");
  if (tip == NULL) {
    return MY_RET_FAIL;
  }
  my_widget_subclass_init(tip, &s_tip_vtable);
  tip->floating = true;
  my_widget_set_tooltip(tip, text);
  my_widget_set_rect(tip, &(my_rect_t){x, y, w, h});
  tip_hide(win); /* paranoia: never two tips */
  if (my_widget_add_child(root, tip) != MY_RET_OK) {
    my_widget_unref(tip);
    return MY_RET_FAIL;
  }
  win->tip_widget = tip; /* tree + we hold one ref each */
  my_widget_invalidate(root, NULL);
  return MY_RET_FAIL; /* one-shot */
}

/** @brief Nearest ancestor-or-self with a tooltip (excluding the tip). */
static my_widget_t* tip_hover_target(my_window_t* win, my_widget_t* hit) {
  while (hit != NULL) {
    if (hit != win->tip_widget && hit->tooltip != NULL &&
        hit->tooltip[0] != '\0') {
      return hit;
    }
    hit = hit->parent;
  }
  return NULL;
}

/** @brief Track hover state before the event is dispatched. */
static void tip_track(my_window_t* win, const my_event_t* event) {
  if (event->type == MY_EVENT_POINTER_MOVE) {
    my_widget_t* hit = my_widget_hit_test((my_widget_t*)win, event->u.pointer.x,
                                          event->u.pointer.y);
    my_widget_t* target = tip_hover_target(win, hit);
    if (target == win->tip_target) {
      return; /* still hovering the same widget */
    }
    tip_cancel_timer(win);
    tip_hide(win);
    win->tip_target = target;
    if (target != NULL && win->loop != NULL) {
      win->tip_x = event->u.pointer.x;
      win->tip_y = event->u.pointer.y;
      win->tip_timer =
          my_pal_main_loop_add_timer(win->loop, tip_on_timer, win, TIP_DELAY_MS);
    }
    return;
  }
  if (event->type == MY_EVENT_POINTER_DOWN ||
      event->type == MY_EVENT_KEY_DOWN) {
    tip_cancel_timer(win);
    tip_hide(win);
    win->tip_target = NULL;
  }
}

/* ---------------- event routing ---------------- */

my_pal_t* my_window_pal_of_widget(my_widget_t* widget) {
  my_widget_t* root = widget;
  if (widget == NULL) {
    return NULL;
  }
  while (root->parent != NULL) {
    root = root->parent;
  }
  if (my_str_eq(root->widget_type, "window")) {
    return ((my_window_t*)root)->pal;
  }
  return NULL;
}

/** @brief The window's default font for a widget (NULL/size 0 when unset).
 * Widgets without an explicit font should use this so measurement and
 * rendering stay consistent (caret math bug, M16). */
void my_window_font_of_widget(my_widget_t* widget, my_font_t** font,
                              int32_t* font_size) {
  my_widget_t* root = widget;
  if (font != NULL) {
    *font = NULL;
  }
  if (font_size != NULL) {
    *font_size = 0;
  }
  if (widget == NULL) {
    return;
  }
  while (root->parent != NULL) {
    root = root->parent;
  }
  if (my_str_eq(root->widget_type, "window")) {
    my_window_t* win = (my_window_t*)root;
    if (font != NULL) {
      *font = win->font;
    }
    if (font_size != NULL) {
      *font_size = win->font_size;
    }
  }
}

my_pal_main_loop_t* my_window_loop_of_widget(my_widget_t* widget) {
  my_widget_t* root = widget;
  if (widget == NULL) {
    return NULL;
  }
  while (root->parent != NULL) {
    root = root->parent;
  }
  if (my_str_eq(root->widget_type, "window")) {
    return ((my_window_t*)root)->loop;
  }
  return NULL;
}

void my_window_set_undo_manager(my_window_t* win, void* mgr) {
  if (win != NULL) {
    win->undo_manager = mgr;
  }
}

void* my_window_undo_manager_of_widget(my_widget_t* widget) {
  my_widget_t* root = widget;
  if (widget == NULL) {
    return NULL;
  }
  while (root->parent != NULL) {
    root = root->parent;
  }
  if (my_str_eq(root->widget_type, "window")) {
    return ((my_window_t*)root)->undo_manager;
  }
  return NULL;
}

my_ret_t my_window_on_pal_event(my_window_t* win, const my_event_t* event) {
  my_widget_t* root;
  my_window_t* held_win;
  int32_t drawable_w;
  int32_t drawable_h;
  if (win == NULL || event == NULL) {
    return MY_RET_INVALID_PARAMS;
  }
  held_win = (my_window_t*)my_widget_ref((my_widget_t*)win);
  root = (my_widget_t*)win;
  switch (event->type) {
    case MY_EVENT_PAINT:
      my_window_paint(win);
      break;
    case MY_EVENT_RESIZE:
      (void)my_window_refresh_scale(win);
      (void)my_widget_set_rect(
          root, &(my_rect_t){root->rect.x, root->rect.y, event->u.resize.w,
                             event->u.resize.h});
      if (win->gpu_backend == MY_GPU_SOFT && win->vg_owned &&
          win->vg != NULL) {
        my_vgcanvas_destroy(win->vg);
        win->vg = NULL;
        win->vg_owned = false;
      } else if (win->gl != NULL && win->vg != NULL) {
        drawable_w = (int32_t)((float)event->u.resize.w * win->scale + 0.5f);
        drawable_h = (int32_t)((float)event->u.resize.h * win->scale + 0.5f);
        (void)my_pal_gl_get_size(win->gl, &drawable_w, &drawable_h);
        if (drawable_w <= 0 || drawable_h <= 0) {
          drawable_w = event->u.resize.w;
          drawable_h = event->u.resize.h;
        }
        if (win->gpu_backend == MY_GPU_VULKAN) {
          my_vgcanvas_vulkan_resize(win->vg, drawable_w, drawable_h);
        } else {
          my_pal_gl_make_current(win->gl);
          my_vgcanvas_gles2_resize(win->vg, drawable_w, drawable_h);
        }
      }
      my_widget_invalidate(root, NULL);
      break;
    case MY_EVENT_POINTER_DOWN:
    case MY_EVENT_POINTER_MOVE:
    case MY_EVENT_POINTER_UP:
    case MY_EVENT_POINTER_WHEEL:
    case MY_EVENT_KEY_DOWN:
    case MY_EVENT_KEY_UP:
    case MY_EVENT_IME_PREEDIT:
    case MY_EVENT_IME_COMMIT:
    case MY_EVENT_IME_DELETE_SURROUNDING:
      tip_track(win, event); /* hover tooltip bookkeeping (M13c) */
      my_event_dispatch(&win->dispatcher, event);
      break;
    case MY_EVENT_USER:
      my_emitter_emit(root->emitter, "user", event->u.user.data);
      break;
    default:
      break;
  }
  /* Dirty rects accumulate here and are painted by the window manager's
   * ~33 ms tick (frame coalescing): high-frequency event streams (wheel,
   * pointer motion) then cost at most one repaint per frame instead of one
   * full repaint per event. */
  my_widget_unref((my_widget_t*)held_win);
  return MY_RET_OK;
}
