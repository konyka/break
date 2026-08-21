/**
 * @file my_gl_real.c
 * @brief Real GLES2 implementation of my_gl_t (current context).
 * Compiled only when MYUI_HAS_GLES2 is defined; otherwise a stub
 * my_gl_real_default() returning NULL is used.
 */
#include "myr/my_gl.h"

#ifdef MYUI_HAS_GLES2

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h> /* GL_MULTISAMPLE_EXT (ES2 core has no toggle) */

static void real_viewport(void* ctx, int32_t w, int32_t h) {
  (void)ctx;
  glViewport(0, 0, (GLsizei)w, (GLsizei)h);
}

static void real_enable_scissor(void* ctx, bool on) {
  (void)ctx;
  if (on) {
    glEnable(GL_SCISSOR_TEST);
  } else {
    glDisable(GL_SCISSOR_TEST);
  }
}

static void real_scissor(void* ctx, int32_t x, int32_t y, int32_t w, int32_t h) {
  (void)ctx;
  glScissor((GLint)x, (GLint)y, (GLsizei)w, (GLsizei)h);
}

static void real_clear_color(void* ctx, float r, float g, float b, float a) {
  (void)ctx;
  glClearColor((GLclampf)r, (GLclampf)g, (GLclampf)b, (GLclampf)a);
}

static void real_clear(void* ctx) {
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

static uint32_t real_create_program(void* ctx, const char* vs_src,
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

static void real_delete_program(void* ctx, uint32_t program) {
  (void)ctx;
  glDeleteProgram((GLuint)program);
}

static void real_use_program(void* ctx, uint32_t program) {
  (void)ctx;
  glUseProgram((GLuint)program);
}

static void real_uniform2f(void* ctx, uint32_t program, const char* name,
                           float a, float b) {
  GLint loc;
  (void)ctx;
  loc = glGetUniformLocation((GLuint)program, name);
  glUniform2f(loc, (GLfloat)a, (GLfloat)b);
}

static void real_uniform4f(void* ctx, uint32_t program, const char* name,
                           float r, float g, float b, float a) {
  GLint loc;
  (void)ctx;
  loc = glGetUniformLocation((GLuint)program, name);
  glUniform4f(loc, (GLfloat)r, (GLfloat)g, (GLfloat)b, (GLfloat)a);
}

static void real_draw_arrays(void* ctx, uint32_t program, const float* xy,
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

static uint32_t real_create_texture(void* ctx, const uint8_t* alpha, int32_t w,
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

static uint32_t real_create_texture_rgba(void* ctx, const uint8_t* rgba,
                                         int32_t w, int32_t h) {
  GLuint tex;
  (void)ctx;
  glGenTextures(1, &tex);
  glBindTexture(GL_TEXTURE_2D, tex);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, (GLsizei)w, (GLsizei)h, 0, GL_RGBA,
               GL_UNSIGNED_BYTE, rgba);
  return (uint32_t)tex;
}

static void real_delete_texture(void* ctx, uint32_t texture) {
  GLuint tex = (GLuint)texture;
  (void)ctx;
  glDeleteTextures(1, &tex);
}

static void real_draw_textured(void* ctx, uint32_t program, uint32_t texture,
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

static void real_set_multisample(void* ctx, bool on) {
  (void)ctx;
  /* ES2 core has no GL_MULTISAMPLE toggle; the EXT constant shares the
   * desktop value (0x809D). Drivers without the EXT flag
   * GL_INVALID_ENUM -- swallow it: AA state stays surface-driven (the
   * EGL config decides, see M11c config negotiation). */
  if (on) {
    glEnable(GL_MULTISAMPLE_EXT);
  } else {
    glDisable(GL_MULTISAMPLE_EXT);
  }
  (void)glGetError();
}

const my_gl_t* my_gl_real_default(void) {
  static const my_gl_t real = {real_viewport,      real_enable_scissor,
                               real_scissor,       real_clear_color,
                               real_clear,         real_create_program,
                               real_delete_program, real_use_program,
                               real_uniform2f,     real_uniform4f,
                               real_draw_arrays,   real_create_texture,
                               real_create_texture_rgba, real_delete_texture,
                               real_draw_textured, real_set_multisample,
                               NULL,
                               NULL, /* shader_header_vs: ES2 needs none */
                               "precision mediump float;\n"};
  return &real;
}

#else

const my_gl_t* my_gl_real_default(void) {
  return NULL;
}

#endif /* MYUI_HAS_GLES2 */
