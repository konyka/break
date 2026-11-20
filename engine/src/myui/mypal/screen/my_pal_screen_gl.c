#include "mypal/screen/my_pal_screen_gl.h"

#include <EGL/egl.h>
#include <GLES2/gl2.h>
#include <limits.h>
#include <pthread.h>
#include <stdint.h>
#include <string.h>

typedef struct my_screen_gl_t {
  my_pal_gl_t base;
  my_pal_window_t* owner;
  my_pal_gl_t** owner_link;
  const my_allocator_t* allocator;
  EGLDisplay display;
  EGLConfig config;
  EGLSurface surface;
  EGLContext context;
  uint8_t* readback;
  int32_t width;
  int32_t height;
  bool initialized;
  bool readback_ready;
} my_screen_gl_t;

static pthread_mutex_t my_screen_display_mutex = PTHREAD_MUTEX_INITIALIZER;
static EGLDisplay my_screen_shared_display = EGL_NO_DISPLAY;
static uint32_t my_screen_display_references;

static bool my_screen_gl_display_acquire(my_screen_gl_t* g) {
  bool acquired = false;
  pthread_mutex_lock(&my_screen_display_mutex);
  if (my_screen_display_references == 0u) {
    if (eglInitialize(g->display, NULL, NULL)) {
      my_screen_shared_display = g->display;
      my_screen_display_references = 1u;
      acquired = true;
    }
  } else if (my_screen_shared_display == g->display &&
             my_screen_display_references < UINT32_MAX) {
    my_screen_display_references++;
    acquired = true;
  }
  if (acquired) g->initialized = true;
  pthread_mutex_unlock(&my_screen_display_mutex);
  return acquired;
}

static void my_screen_gl_display_release(my_screen_gl_t* g) {
  if (!g->initialized) return;
  pthread_mutex_lock(&my_screen_display_mutex);
  if (my_screen_shared_display == g->display &&
      my_screen_display_references > 0u) {
    my_screen_display_references--;
    if (my_screen_display_references == 0u) {
      (void)eglTerminate(my_screen_shared_display);
      my_screen_shared_display = EGL_NO_DISPLAY;
    }
    g->initialized = false;
  }
  pthread_mutex_unlock(&my_screen_display_mutex);
}

static bool my_screen_gl_size_bytes(int32_t width, int32_t height,
                                    size_t* bytes) {
  size_t stride;
  if (width <= 0 || height <= 0 || width > INT32_MAX / 4) return false;
  stride = (size_t)(uint32_t)width * 4u;
  if ((size_t)(uint32_t)height > SIZE_MAX / stride) return false;
  *bytes = stride * (size_t)(uint32_t)height;
  return true;
}

static void my_screen_gl_release(my_screen_gl_t* g) {
  if (g->display != EGL_NO_DISPLAY) {
    if (g->context != EGL_NO_CONTEXT && eglGetCurrentContext() == g->context) {
      (void)eglMakeCurrent(g->display, EGL_NO_SURFACE, EGL_NO_SURFACE,
                           EGL_NO_CONTEXT);
    }
    if (g->context != EGL_NO_CONTEXT) {
      (void)eglDestroyContext(g->display, g->context);
    }
    if (g->surface != EGL_NO_SURFACE) {
      (void)eglDestroySurface(g->display, g->surface);
    }
    my_screen_gl_display_release(g);
  }
  my_mem_free(g->allocator, g->readback);
  g->readback = NULL;
}

static my_ret_t my_screen_gl_sync_size(my_screen_gl_t* g) {
  int32_t width = 0;
  int32_t height = 0;
  my_ret_t result = my_pal_window_get_size(g->owner, &width, &height);
  if (result != MY_RET_OK) return result;
  if (width == g->width && height == g->height) return MY_RET_OK;
  return my_screen_gl_resize(&g->base, width, height);
}

static my_ret_t my_screen_gl_make_current(my_pal_gl_t* gl) {
  my_screen_gl_t* g = (my_screen_gl_t*)gl;
  my_ret_t result = my_screen_gl_sync_size(g);
  if (result != MY_RET_OK) return result;
  if (!eglMakeCurrent(g->display, g->surface, g->surface, g->context)) {
    return MY_RET_FAIL;
  }
  g->readback_ready = false;
  return MY_RET_OK;
}

static my_ret_t my_screen_gl_swap(my_pal_gl_t* gl) {
  my_screen_gl_t* g = (my_screen_gl_t*)gl;
  my_lcd_t* lcd;
  my_ret_t result;
  uint8_t* pixels;
  uint32_t lcd_stride;
  size_t rgb_stride;
  int32_t row;
  result = my_screen_gl_sync_size(g);
  if (result != MY_RET_OK) return result;
  if (!g->readback_ready) {
    if (!eglMakeCurrent(g->display, g->surface, g->surface, g->context)) {
      return MY_RET_FAIL;
    }
    rgb_stride = (size_t)(uint32_t)g->width * 4u;
    glReadPixels(0, 0, g->width, g->height, GL_RGBA, GL_UNSIGNED_BYTE,
                 g->readback);
    if (glGetError() != GL_NO_ERROR) return MY_RET_FAIL;
    g->readback_ready = true;
  }
  rgb_stride = (size_t)(uint32_t)g->width * 4u;
  lcd = my_pal_window_get_lcd(g->owner);
  if (lcd == NULL || my_lcd_get_width(lcd) != (uint32_t)g->width ||
      my_lcd_get_height(lcd) != (uint32_t)g->height ||
      my_lcd_get_format(lcd) != MY_PIXEL_FORMAT_RGBA8888) {
    return MY_RET_FAIL;
  }
  result = my_lcd_begin_frame(lcd, NULL);
  if (result != MY_RET_OK) return result;
  pixels = my_lcd_get_buffer(lcd);
  lcd_stride = my_lcd_get_stride(lcd);
  if (pixels == NULL || lcd_stride < rgb_stride) {
    (void)my_lcd_end_frame(lcd);
    return MY_RET_FAIL;
  }
  for (row = 0; row < g->height; ++row) {
    const uint8_t* source =
        g->readback + (size_t)(uint32_t)(g->height - row - 1) * rgb_stride;
    memcpy(pixels + (size_t)(uint32_t)row * lcd_stride, source, rgb_stride);
  }
  result = my_lcd_end_frame(lcd);
  if (result == MY_RET_OK) g->readback_ready = false;
  return result;
}

static my_ret_t my_screen_gl_get_size(my_pal_gl_t* gl, int32_t* width,
                                      int32_t* height) {
  my_screen_gl_t* g = (my_screen_gl_t*)gl;
  if (width != NULL) *width = g->width;
  if (height != NULL) *height = g->height;
  return MY_RET_OK;
}

static bool my_screen_gl_has_multisample(my_pal_gl_t* gl) {
  (void)gl;
  return false;
}

static const my_pal_gl_vtable_t s_screen_gl_vtable = {
    my_screen_gl_make_current, my_screen_gl_swap, my_screen_gl_get_size,
    my_screen_gl_has_multisample, my_screen_gl_destroy};

my_ret_t my_screen_gl_resize(my_pal_gl_t* gl, int32_t width, int32_t height) {
  my_screen_gl_t* g = (my_screen_gl_t*)gl;
  EGLSurface surface;
  EGLint attributes[5];
  uint8_t* readback;
  uint8_t* old_readback;
  EGLSurface old_surface;
  size_t bytes;
  bool was_current;
  if (g == NULL || !my_screen_gl_size_bytes(width, height, &bytes)) {
    return MY_RET_INVALID_PARAMS;
  }
  if (width == g->width && height == g->height) return MY_RET_OK;
  readback = my_mem_alloc(g->allocator, bytes);
  if (readback == NULL) return MY_RET_OOM;
  attributes[0] = EGL_WIDTH;
  attributes[1] = width;
  attributes[2] = EGL_HEIGHT;
  attributes[3] = height;
  attributes[4] = EGL_NONE;
  surface = eglCreatePbufferSurface(g->display, g->config, attributes);
  if (surface == EGL_NO_SURFACE) {
    my_mem_free(g->allocator, readback);
    return MY_RET_FAIL;
  }
  was_current = eglGetCurrentContext() == g->context;
  if (was_current &&
      !eglMakeCurrent(g->display, surface, surface, g->context)) {
    (void)eglDestroySurface(g->display, surface);
    my_mem_free(g->allocator, readback);
    return MY_RET_FAIL;
  }
  old_surface = g->surface;
  old_readback = g->readback;
  g->surface = surface;
  g->readback = readback;
  g->width = width;
  g->height = height;
  g->readback_ready = false;
  if (old_surface != EGL_NO_SURFACE) {
    (void)eglDestroySurface(g->display, old_surface);
  }
  my_mem_free(g->allocator, old_readback);
  return MY_RET_OK;
}

void my_screen_gl_destroy(my_pal_gl_t* gl) {
  my_screen_gl_t* g = (my_screen_gl_t*)gl;
  if (g == NULL) return;
  if (g->owner_link != NULL && *g->owner_link == gl) *g->owner_link = NULL;
  my_screen_gl_release(g);
  my_mem_free(g->allocator, g);
}

my_pal_gl_t* my_screen_gl_create(my_pal_window_t* owner,
                                 const my_allocator_t* allocator,
                                 my_pal_gl_t** owner_link) {
  static const EGLint config_attributes[] = {
      EGL_SURFACE_TYPE, EGL_PBUFFER_BIT, EGL_RENDERABLE_TYPE,
      EGL_OPENGL_ES2_BIT, EGL_RED_SIZE, 8, EGL_GREEN_SIZE, 8, EGL_BLUE_SIZE,
      8, EGL_ALPHA_SIZE, 8, EGL_SAMPLE_BUFFERS, 0, EGL_SAMPLES, 0, EGL_NONE};
  static const EGLint context_attributes[] = {EGL_CONTEXT_CLIENT_VERSION, 2,
                                               EGL_NONE};
  my_screen_gl_t* g;
  EGLint count = 0;
  EGLint surface_attributes[5];
  int32_t width = 0;
  int32_t height = 0;
  size_t bytes;
  if (owner == NULL || owner_link == NULL ||
      my_pal_window_get_size(owner, &width, &height) != MY_RET_OK ||
      !my_screen_gl_size_bytes(width, height, &bytes)) {
    return NULL;
  }
  g = my_mem_calloc(allocator, 1u, sizeof(*g));
  if (g == NULL) return NULL;
  g->base.vtable = &s_screen_gl_vtable;
  g->owner = owner;
  g->owner_link = owner_link;
  g->allocator = allocator;
  g->display = EGL_NO_DISPLAY;
  g->surface = EGL_NO_SURFACE;
  g->context = EGL_NO_CONTEXT;
  g->width = width;
  g->height = height;
  g->readback = my_mem_alloc(allocator, bytes);
  if (g->readback == NULL) goto fail;
  g->display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
  if (g->display == EGL_NO_DISPLAY) goto fail;
  if (!my_screen_gl_display_acquire(g)) goto fail;
  if (!eglBindAPI(EGL_OPENGL_ES_API) ||
      !eglChooseConfig(g->display, config_attributes, &g->config, 1, &count) ||
      count < 1) {
    goto fail;
  }
  surface_attributes[0] = EGL_WIDTH;
  surface_attributes[1] = width;
  surface_attributes[2] = EGL_HEIGHT;
  surface_attributes[3] = height;
  surface_attributes[4] = EGL_NONE;
  g->surface =
      eglCreatePbufferSurface(g->display, g->config, surface_attributes);
  if (g->surface == EGL_NO_SURFACE) goto fail;
  g->context = eglCreateContext(g->display, g->config, EGL_NO_CONTEXT,
                                context_attributes);
  if (g->context == EGL_NO_CONTEXT ||
      !eglMakeCurrent(g->display, g->surface, g->surface, g->context)) {
    goto fail;
  }
  *owner_link = &g->base;
  return &g->base;

fail:
  my_screen_gl_release(g);
  my_mem_free(allocator, g);
  return NULL;
}
