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
 *
 * Windows: opengl32.dll only exports the GL 1.1 entry points and the
 * Windows SDK <GL/gl.h> carries only GL 1.1 declarations, so every
 * GL 1.2+/2.0 symbol used by this backend is resolved once through
 * wglGetProcAddress (rejecting the documented garbage sentinels) and
 * cached in a static pointer table. The name #define map below keeps
 * the shared wrapper bodies identical to the POSIX path, so per-call
 * cost stays a direct function-pointer call on every platform.
 * my_gl_desktop_default() returns NULL until the caller has made a WGL
 * context current and all required entry points resolved — the same
 * "current context" contract the EGL/GLX mounts rely on.
 */
#include "myr/my_gl_desktop.h"
#include "myr/my_gl_desktop_internal.h"

#ifdef _WIN32

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>
#include <GL/gl.h>

/* ---- enums missing from the Windows SDK GL 1.1 header -------------- */

#ifndef GL_CLAMP_TO_EDGE
#define GL_CLAMP_TO_EDGE 0x812F
#endif
#ifndef GL_TEXTURE0
#define GL_TEXTURE0 0x84C0
#endif
#ifndef GL_MULTISAMPLE
#define GL_MULTISAMPLE 0x809D
#endif
#ifndef GL_SAMPLE_BUFFERS
#define GL_SAMPLE_BUFFERS 0x80A8
#endif
#ifndef GL_SAMPLES
#define GL_SAMPLES 0x80A9
#endif
#ifndef GL_VERTEX_SHADER
#define GL_VERTEX_SHADER 0x8B31
#endif
#ifndef GL_FRAGMENT_SHADER
#define GL_FRAGMENT_SHADER 0x8B30
#endif
#ifndef GL_COMPILE_STATUS
#define GL_COMPILE_STATUS 0x8B81
#endif
#ifndef GL_LINK_STATUS
#define GL_LINK_STATUS 0x8B82
#endif

/* ---- one-shot wglGetProcAddress resolution ------------------------- */

typedef GLuint(APIENTRY* my_gl_desktop_pfn_glCreateShader_t)(GLenum type);
typedef void(APIENTRY* my_gl_desktop_pfn_glShaderSource_t)(
    GLuint shader, GLsizei count, const char* const* string,
    const GLint* length);
typedef void(APIENTRY* my_gl_desktop_pfn_glCompileShader_t)(GLuint shader);
typedef void(APIENTRY* my_gl_desktop_pfn_glGetShaderiv_t)(GLuint shader,
                                                          GLenum pname,
                                                          GLint* params);
typedef void(APIENTRY* my_gl_desktop_pfn_glDeleteShader_t)(GLuint shader);
typedef GLuint(APIENTRY* my_gl_desktop_pfn_glCreateProgram_t)(void);
typedef void(APIENTRY* my_gl_desktop_pfn_glAttachShader_t)(GLuint program,
                                                           GLuint shader);
typedef void(APIENTRY* my_gl_desktop_pfn_glLinkProgram_t)(GLuint program);
typedef void(APIENTRY* my_gl_desktop_pfn_glGetProgramiv_t)(GLuint program,
                                                           GLenum pname,
                                                           GLint* params);
typedef void(APIENTRY* my_gl_desktop_pfn_glDeleteProgram_t)(GLuint program);
typedef void(APIENTRY* my_gl_desktop_pfn_glUseProgram_t)(GLuint program);
typedef GLint(APIENTRY* my_gl_desktop_pfn_glGetUniformLocation_t)(
    GLuint program, const char* name);
typedef void(APIENTRY* my_gl_desktop_pfn_glUniform2f_t)(GLint location,
                                                        GLfloat v0, GLfloat v1);
typedef void(APIENTRY* my_gl_desktop_pfn_glUniform4f_t)(GLint location,
                                                        GLfloat v0, GLfloat v1,
                                                        GLfloat v2,
                                                        GLfloat v3);
typedef GLint(APIENTRY* my_gl_desktop_pfn_glGetAttribLocation_t)(
    GLuint program, const char* name);
typedef void(APIENTRY* my_gl_desktop_pfn_glVertexAttribPointer_t)(
    GLuint index, GLint size, GLenum type, GLboolean normalized,
    GLsizei stride, const void* pointer);
typedef void(APIENTRY* my_gl_desktop_pfn_glEnableVertexAttribArray_t)(
    GLuint index);
typedef void(APIENTRY* my_gl_desktop_pfn_glDisableVertexAttribArray_t)(
    GLuint index);
typedef void(APIENTRY* my_gl_desktop_pfn_glActiveTexture_t)(GLenum texture);

static struct {
  my_gl_desktop_pfn_glCreateShader_t glCreateShader;
  my_gl_desktop_pfn_glShaderSource_t glShaderSource;
  my_gl_desktop_pfn_glCompileShader_t glCompileShader;
  my_gl_desktop_pfn_glGetShaderiv_t glGetShaderiv;
  my_gl_desktop_pfn_glDeleteShader_t glDeleteShader;
  my_gl_desktop_pfn_glCreateProgram_t glCreateProgram;
  my_gl_desktop_pfn_glAttachShader_t glAttachShader;
  my_gl_desktop_pfn_glLinkProgram_t glLinkProgram;
  my_gl_desktop_pfn_glGetProgramiv_t glGetProgramiv;
  my_gl_desktop_pfn_glDeleteProgram_t glDeleteProgram;
  my_gl_desktop_pfn_glUseProgram_t glUseProgram;
  my_gl_desktop_pfn_glGetUniformLocation_t glGetUniformLocation;
  my_gl_desktop_pfn_glUniform2f_t glUniform2f;
  my_gl_desktop_pfn_glUniform4f_t glUniform4f;
  my_gl_desktop_pfn_glGetAttribLocation_t glGetAttribLocation;
  my_gl_desktop_pfn_glVertexAttribPointer_t glVertexAttribPointer;
  my_gl_desktop_pfn_glEnableVertexAttribArray_t glEnableVertexAttribArray;
  my_gl_desktop_pfn_glDisableVertexAttribArray_t
      glDisableVertexAttribArray;
  my_gl_desktop_pfn_glActiveTexture_t glActiveTexture;
} s_wgl;

/* 0 = unresolved, 1 = resolved, -1 = resolution failed once. */
static int s_wgl_state = 0;

/* ---- pedantic-clean proc/address conversions (test seam) ----------- */

my_gl_desktop_proc_t my_gl_desktop_proc_from_address(uintptr_t address) {
  union {
    my_gl_desktop_proc_t fn;
    uintptr_t addr;
  } conv;
  conv.addr = address;
  return conv.fn;
}

uintptr_t my_gl_desktop_proc_to_address(my_gl_desktop_proc_t proc) {
  union {
    my_gl_desktop_proc_t fn;
    uintptr_t addr;
  } conv;
  conv.fn = proc;
  return conv.addr;
}

bool my_gl_desktop_wgl_proc_usable(my_gl_desktop_proc_t proc) {
  uintptr_t address = my_gl_desktop_proc_to_address(proc);
  /* wglGetProcAddress documents (and drivers in the wild return) these
   * sentinels for unavailable entry points; anything else is a real
   * address (W documents 0; SGI/3Dfx lineage returned 1/2/3; -1 shows
   * up on some 64-bit drivers). */
  return address > 3u && address != (uintptr_t)-1;
}

#define MY_GL_RESOLVE(field, name)                                    \
  do {                                                                \
    if (s_wgl.field == NULL) {                                        \
      PROC candidate = wglGetProcAddress(name);                       \
      if (my_gl_desktop_wgl_proc_usable((my_gl_desktop_proc_t)candidate)) { \
        s_wgl.field = (my_gl_desktop_pfn_##field##_t)candidate;       \
      }                                                               \
    }                                                                 \
    ok = ok && s_wgl.field != NULL;                                   \
  } while (0)

/* Resolve every required entry point against the CURRENT WGL context.
 * Callers own the context lifecycle (same contract as the EGL mount);
 * resolution runs once and its result is cached for the process. */
static bool my_gl_desktop_wgl_ready(void) {
  bool ok = true;
  if (s_wgl_state != 0) return s_wgl_state == 1;
  MY_GL_RESOLVE(glCreateShader, "glCreateShader");
  MY_GL_RESOLVE(glShaderSource, "glShaderSource");
  MY_GL_RESOLVE(glCompileShader, "glCompileShader");
  MY_GL_RESOLVE(glGetShaderiv, "glGetShaderiv");
  MY_GL_RESOLVE(glDeleteShader, "glDeleteShader");
  MY_GL_RESOLVE(glCreateProgram, "glCreateProgram");
  MY_GL_RESOLVE(glAttachShader, "glAttachShader");
  MY_GL_RESOLVE(glLinkProgram, "glLinkProgram");
  MY_GL_RESOLVE(glGetProgramiv, "glGetProgramiv");
  MY_GL_RESOLVE(glDeleteProgram, "glDeleteProgram");
  MY_GL_RESOLVE(glUseProgram, "glUseProgram");
  MY_GL_RESOLVE(glGetUniformLocation, "glGetUniformLocation");
  MY_GL_RESOLVE(glUniform2f, "glUniform2f");
  MY_GL_RESOLVE(glUniform4f, "glUniform4f");
  MY_GL_RESOLVE(glGetAttribLocation, "glGetAttribLocation");
  MY_GL_RESOLVE(glVertexAttribPointer, "glVertexAttribPointer");
  MY_GL_RESOLVE(glEnableVertexAttribArray, "glEnableVertexAttribArray");
  MY_GL_RESOLVE(glDisableVertexAttribArray, "glDisableVertexAttribArray");
  MY_GL_RESOLVE(glActiveTexture, "glActiveTexture");
  s_wgl_state = ok ? 1 : -1;
  return ok;
}

/* Map the GL 2.0 names onto the resolved pointer table so the shared
 * wrapper bodies below stay byte-identical with the POSIX path. GL 1.1
 * entry points (glViewport, glBlendFunc, ...) stay direct opengl32
 * exports on both platforms. */
#define glCreateShader s_wgl.glCreateShader
#define glShaderSource s_wgl.glShaderSource
#define glCompileShader s_wgl.glCompileShader
#define glGetShaderiv s_wgl.glGetShaderiv
#define glDeleteShader s_wgl.glDeleteShader
#define glCreateProgram s_wgl.glCreateProgram
#define glAttachShader s_wgl.glAttachShader
#define glLinkProgram s_wgl.glLinkProgram
#define glGetProgramiv s_wgl.glGetProgramiv
#define glDeleteProgram s_wgl.glDeleteProgram
#define glUseProgram s_wgl.glUseProgram
#define glGetUniformLocation s_wgl.glGetUniformLocation
#define glUniform2f s_wgl.glUniform2f
#define glUniform4f s_wgl.glUniform4f
#define glGetAttribLocation s_wgl.glGetAttribLocation
#define glVertexAttribPointer s_wgl.glVertexAttribPointer
#define glEnableVertexAttribArray s_wgl.glEnableVertexAttribArray
#define glDisableVertexAttribArray s_wgl.glDisableVertexAttribArray
#define glActiveTexture s_wgl.glActiveTexture

#endif /* _WIN32 */

#ifdef MYUI_HAS_GL_DESKTOP

#define GL_GLEXT_PROTOTYPES /* declare the GL 2.0 shader/texture API */
#ifndef _WIN32
#include <GL/gl.h>
#include <GL/glext.h>
#endif

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

static bool gl_has_multisample(void* ctx) {
  GLint buffers = 0;
  GLint samples = 0;
  (void)ctx;
  glGetIntegerv(GL_SAMPLE_BUFFERS, &buffers);
  glGetIntegerv(GL_SAMPLES, &samples);
  return buffers > 0 && samples > 0;
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
                               gl_create_texture_rgba_filtered,
                               gl_has_multisample};
#ifdef _WIN32
  /* Unresolved entry points (no current context / GL 1.1-only driver)
   * keep the table unavailable rather than handing out NULL pointers
   * the vgcanvas would call. */
  if (!my_gl_desktop_wgl_ready()) return NULL;
#endif
  return &real;
}

#else

const my_gl_t* my_gl_desktop_default(void) {
  return NULL;
}

#endif /* MYUI_HAS_GL_DESKTOP */
