/**
 * @file my_gl_desktop.h
 * @brief Desktop OpenGL implementation of my_gl_t (M25a).
 *
 * Same simplified GL surface as my_gl_real_default() (GLES2), but bound
 * to the desktop GL headers and carrying the "#version 120" shader
 * headers (the vgcanvas gles2 backend's shader bodies are valid GLSL
 * 1.20, so one backend serves both APIs). Uses the CURRENT GL context
 * (created via EGL with eglBindAPI(EGL_OPENGL_API), or GLX elsewhere).
 */
#ifndef MY_GL_DESKTOP_H
#define MY_GL_DESKTOP_H

#include "myr/my_gl.h"

/**
 * @brief The desktop OpenGL implementation of the table (only available
 * when built with MYUI_HAS_GL_DESKTOP, otherwise returns NULL).
 */
const my_gl_t* my_gl_desktop_default(void);

#endif /* MY_GL_DESKTOP_H */
