/**
 * @file my_gl.h
 * @brief Minimal GL function table used by the GLES2 vgcanvas backend.
 *
 * All GL calls of the backend go through this table, so tests can inject
 * a recording mock and ports can supply the real implementation
 * (my_gl_real_default() when built with GLES2). The table is a
 * simplified surface, not a 1:1 GL mapping: create_program takes shader
 * sources, draw_arrays_triangles takes interleaved vec2 positions and
 * draws with the currently set uniforms.
 */
#ifndef MY_GL_H
#define MY_GL_H

#include "myc/my_types.h"

/** @brief GL function table (simplified surface). */
typedef struct my_gl_t {
  void (*viewport)(void* ctx, int32_t w, int32_t h);
  void (*enable_scissor)(void* ctx, bool on);
  void (*scissor)(void* ctx, int32_t x, int32_t y, int32_t w, int32_t h);
  void (*clear_color)(void* ctx, float r, float g, float b, float a);
  void (*clear)(void* ctx);
  /** @brief Compile+link a program; 0 on failure. */
  uint32_t (*create_program)(void* ctx, const char* vs_src, const char* fs_src);
  void (*delete_program)(void* ctx, uint32_t program);
  void (*use_program)(void* ctx, uint32_t program);
  /** @brief "u_resolution": pixel size of the render target. */
  void (*uniform2f)(void* ctx, uint32_t program, const char* name, float a,
                    float b);
  /** @brief "u_color": current draw color. */
  void (*uniform4f)(void* ctx, uint32_t program, const char* name, float r,
                    float g, float b, float a);
  /** @brief Draw GL_TRIANGLES with vec2 xy positions (count = vertices). */
  void (*draw_arrays_triangles)(void* ctx, uint32_t program, const float* xy,
                                int32_t count);
  /** @brief Upload an 8bpp alpha bitmap as a texture; 0 on failure. */
  uint32_t (*create_texture)(void* ctx, const uint8_t* alpha, int32_t w,
                             int32_t h);
  /** @brief Upload an RGBA8888 bitmap as a texture; 0 on failure. */
  uint32_t (*create_texture_rgba)(void* ctx, const uint8_t* rgba, int32_t w,
                                  int32_t h);
  void (*delete_texture)(void* ctx, uint32_t texture);
  /** @brief Draw textured quads (interleaved xy+uv, count = vertices). */
  void (*draw_textured_quads)(void* ctx, uint32_t program, uint32_t texture,
                              const float* xyuv, int32_t count);
  /**
   * @brief Toggle GL_MULTISAMPLE (M11c). Effective only when the current
   * surface was created with samples (EGL_SAMPLES > 0); on plain
   * surfaces this is a no-op state change. May be NULL (mocks).
   */
  void (*set_multisample)(void* ctx, bool on);
  void* ctx;
  /**
   * @brief Shader source prefix for the backend's programs (M25a): when
   * non-NULL the vgcanvas prepends it to the vertex/fragment shader
   * bodies it passes to create_program. ES2: fs = "precision mediump
   * float;\n", vs = NULL; desktop GL: both "#version 120\n".
   */
  const char* shader_header_vs;
  const char* shader_header_fs;
  /** @brief Optional RGBA upload with an explicit sampling filter. */
  uint32_t (*create_texture_rgba_filtered)(void* ctx, const uint8_t* rgba,
                                           int32_t w, int32_t h,
                                           bool linear);
  /** @brief Reports whether the current drawable has multisample storage. */
  bool (*has_multisample)(void* ctx);
} my_gl_t;

/**
 * @brief The real GLES2 implementation of the table (uses the CURRENT GL
 * context; only available when built with MYUI_HAS_GLES2, otherwise
 * returns NULL).
 */
const my_gl_t* my_gl_real_default(void);

#endif /* MY_GL_H */
