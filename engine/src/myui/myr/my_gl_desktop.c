/**
 * @file my_gl_desktop.c
 * @brief Desktop OpenGL implementation of my_gl_t (M25a, current
 * context). Compiled only when MYUI_HAS_GL_DESKTOP is defined; otherwise
 * a stub my_gl_desktop_default() returning NULL is used.
 *
 * Differences from my_gl_real.c (GLES2): desktop <GL/gl.h> binding,
 * GL_MULTISAMPLE is core (no _EXT), and the shader header seam carries
 * "#version 120" for both stages. GL_LUMINANCE stays (compatibility
 * profile contexts accept it; the EGL mount creates one).
 */
#include "myr/my_gl_desktop.h"

#ifdef MYUI_HAS_GL_DESKTOP

#define GL_GLEXT_PROTOTYPES /* declare the GL 2.0 shader/texture API */
#include <GL/gl.h>
#include <GL/glext.h>

static void gl_viewport(void* ctx, int32_t w, int32_t h) {
  (void)ctx;
  glViewport(0, 0, (GLsizei)w, (GLsizei)h);
}

static void gl_enable_scissor(void* ctx, bool on) {
  (void)ctx;
  if (on) {
    glEnable(GL_SCISSOR_TEST);
  } else {
    glDisable(GL_SCISSOR_TEST);
  }
}

static void gl_scissor(void* ctx, int32_t x, int32_t y, int32_t w, int32_t h) {
  (void)ctx;
  glScissor((GLint)x, (GLint)y, (GLsizei)w, (GLsizei)h);
}

static void gl_clear_color(void* ctx, float r, float g, float b, float a) {
  (void)ctx;
  glClearColor((GLclampf)r, (GLclampf)g, (GLclampf)b, (GLclampf)a);
}

static void gl_clear(void* ctx) {
  (void)ctx;
  glClear(GL_COLOR_BUFFER_BIT);
}

static GLuint compile_one(GLenum type, const char* src) {
  GLuint shader = glCreateShader(type);
  GLint ok = GL_FALSE;
  glShaderSource(shader, 1, &src, NULL);
  glCompileShader(shader);
  glGetShaderiv(shader, GL_COMPILE_STATUS, &ok);
  if (ok != GL_TRUE) {
    glDeleteShader(shader);
    return 0;
  }
  return shader;
}

static uint32_t gl_create_program(void* ctx, const char* vs_src,
                                  const char* fs_src) {
  GLuint vs, fs, prog;
  GLint ok = GL_FALSE;
  (void)ctx;
  vs = compile_one(GL_VERTEX_SHADER, vs_src);
  fs = compile_one(GL_FRAGMENT_SHADER, fs_src);
  if (vs == 0 || fs == 0) {
    if (vs != 0) {
      glDeleteShader(vs);
    }
    if (fs != 0) {
      glDeleteShader(fs);
    }
    return 0;
  }
  prog = glCreateProgram();
  glAttachShader(prog, vs);
  glAttachShader(prog, fs);
  glLinkProgram(prog);
  glGetProgramiv(prog, GL_LINK_STATUS, &ok);
  glDeleteShader(vs);
  glDeleteShader(fs);
  if (ok != GL_TRUE) {
    glDeleteProgram(prog);
    return 0;
  }
  return (uint32_t)prog;
}

static void gl_delete_program(void* ctx, uint32_t program) {
  (void)ctx;
  glDeleteProgram((GLuint)program);
}

static void gl_use_program(void* ctx, uint32_t program) {
  (void)ctx;
  glUseProgram((GLuint)program);
}

static void gl_uniform2f(void* ctx, uint32_t program, const char* name,
                         float a, float b) {
  GLint loc;
  (void)ctx;
  loc = glGetUniformLocation((GLuint)program, name);
  glUniform2f(loc, (GLfloat)a, (GLfloat)b);
}

static void gl_uniform4f(void* ctx, uint32_t program, const char* name,
                         float r, float g, float b, float a) {
  GLint loc;
  (void)ctx;
  loc = glGetUniformLocation((GLuint)program, name);
  glUniform4f(loc, (GLfloat)r, (GLfloat)g, (GLfloat)b, (GLfloat)a);
}

static void gl_draw_arrays(void* ctx, uint32_t program, const float* xy,
                           int32_t count) {
  GLint loc;
  (void)ctx;
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  loc = glGetAttribLocation((GLuint)program, "a_pos");
  glVertexAttribPointer((GLuint)loc, 2, GL_FLOAT, GL_FALSE, 0, xy);
  glEnableVertexAttribArray((GLuint)loc);
  glDrawArrays(GL_TRIANGLES, 0, (GLsizei)count);
  glDisableVertexAttribArray((GLuint)loc);
}

static uint32_t gl_create_texture(void* ctx, const uint8_t* alpha, int32_t w,
                                  int32_t h) {
  GLuint tex;
  (void)ctx;
  glGenTextures(1, &tex);
  glBindTexture(GL_TEXTURE_2D, tex);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_LUMINANCE, (GLsizei)w, (GLsizei)h, 0,
               GL_LUMINANCE, GL_UNSIGNED_BYTE, alpha);
  return (uint32_t)tex;
}

static uint32_t gl_create_texture_rgba_filtered(void* ctx, const uint8_t* rgba,
                                                int32_t w, int32_t h,
                                                bool linear) {
  GLuint tex;
  (void)ctx;
  glGenTextures(1, &tex);
  glBindTexture(GL_TEXTURE_2D, tex);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                  linear ? GL_LINEAR : GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
                  linear ? GL_LINEAR : GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, (GLsizei)w, (GLsizei)h, 0, GL_RGBA,
               GL_UNSIGNED_BYTE, rgba);
  return (uint32_t)tex;
}

static uint32_t gl_create_texture_rgba(void* ctx, const uint8_t* rgba,
                                       int32_t w, int32_t h) {
  return gl_create_texture_rgba_filtered(ctx, rgba, w, h, true);
}

static void gl_delete_texture(void* ctx, uint32_t texture) {
  GLuint tex = (GLuint)texture;
  (void)ctx;
  glDeleteTextures(1, &tex);
}

static void gl_draw_textured(void* ctx, uint32_t program, uint32_t texture,
                             const float* xyuv, int32_t count) {
  GLint pos_loc, uv_loc;
  (void)ctx;
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, (GLuint)texture);
  pos_loc = glGetAttribLocation((GLuint)program, "a_pos");
  uv_loc = glGetAttribLocation((GLuint)program, "a_uv");
  glVertexAttribPointer((GLuint)pos_loc, 2, GL_FLOAT, GL_FALSE,
                        4 * (GLsizei)sizeof(float), xyuv);
  glEnableVertexAttribArray((GLuint)pos_loc);
  glVertexAttribPointer((GLuint)uv_loc, 2, GL_FLOAT, GL_FALSE,
                        4 * (GLsizei)sizeof(float), xyuv + 2);
  glEnableVertexAttribArray((GLuint)uv_loc);
  glDrawArrays(GL_TRIANGLES, 0, (GLsizei)count);
  glDisableVertexAttribArray((GLuint)pos_loc);
  glDisableVertexAttribArray((GLuint)uv_loc);
}

static void gl_set_multisample(void* ctx, bool on) {
  (void)ctx;
  /* GL_MULTISAMPLE is core on desktop GL (same 0x809D value as the ES2
   * EXT); effective only on surfaces created with samples */
  if (on) {
    glEnable(GL_MULTISAMPLE);
  } else {
    glDisable(GL_MULTISAMPLE);
  }
  (void)glGetError();
}

const my_gl_t* my_gl_desktop_default(void) {
  static const my_gl_t real = {gl_viewport,      gl_enable_scissor,
                               gl_scissor,       gl_clear_color,
                               gl_clear,         gl_create_program,
                               gl_delete_program, gl_use_program,
                               gl_uniform2f,     gl_uniform4f,
                               gl_draw_arrays,   gl_create_texture,
                               gl_create_texture_rgba, gl_delete_texture,
                               gl_draw_textured, gl_set_multisample,
                               NULL,
                               "#version 120\n", /* shader_header_vs */
                               "#version 120\n", /* shader_header_fs */
                               gl_create_texture_rgba_filtered};
  return &real;
}

#else

const my_gl_t* my_gl_desktop_default(void) {
  return NULL;
}

#endif /* MYUI_HAS_GL_DESKTOP */
