#include <glad.h>

#ifdef ENGINE_PLATFORM_WINDOWS
    #include <windows.h>
    #include <GL/gl.h>
    /* WGL extension function types */
    typedef HGLRC (WINAPI *PFNWGLCREATECONTEXTATTRIBSARBPROC)(HDC, HGLRC, const int*);
    #define WGL_CONTEXT_MAJOR_VERSION_ARB  0x2091
    #define WGL_CONTEXT_MINOR_VERSION_ARB  0x2092
    #define WGL_CONTEXT_PROFILE_MASK_ARB   0x9126
    #define WGL_CONTEXT_CORE_PROFILE_BIT_ARB 0x00000001
#elif defined(ENGINE_PLATFORM_WAYLAND)
    #include <EGL/egl.h>
    #include <EGL/eglext.h>
    #include <wayland-client.h>
    #include <wayland-egl.h>
#else
    #include <GL/glx.h>
    #include <X11/Xlib.h>
#endif

typedef struct {
#ifdef ENGINE_PLATFORM_WINDOWS
    HDC     hdc;
    HWND    hwnd;
    HGLRC   gl_ctx;
#elif defined(ENGINE_PLATFORM_WAYLAND)
    struct wl_display    *wl_display;
    struct wl_egl_window *egl_window;
    EGLDisplay            egl_display;
    EGLContext            egl_context;
    EGLSurface            egl_surface;
    EGLConfig             egl_config;
#else
    Display   *display;
    Window     window;
    GLXContext gl_ctx;
#endif
} GLBackend;

typedef struct {
    GLuint gl_vao;
    GLuint gl_vbo;
    GLuint gl_ibo;
    GLuint gl_program;
    u32    vertex_stride;
    bool   has_index;
    bool   alpha_blend;
    bool   wireframe;
    bool   point_list;   /* R168-C: GL_POINTS + PROGRAM_POINT_SIZE */
} GLPipelineData;

typedef struct {
    GLuint gl_buf;
    GLuint tbo_tex;
    usize  size;
} GLBufferData;

typedef struct {
    GLuint gl_shader;
} GLShaderData;

typedef struct {
    GLuint gl_tex;
    u32    width;
    u32    height;
    GLenum gl_internal_format;  /* GL internal format for image binding */
} GLTextureData;

typedef struct {
    GLuint gl_sampler;
} GLSamplerData;

typedef struct {
    GLuint gl_fbo;
    GLuint color_tex;
    GLuint depth_rb;
} GLFBOData;

typedef struct {
    GLuint gl_fbo;
    GLuint color_tex[RHI_MRT_MAX_ATTACHMENTS];
    GLuint depth_rb;    /* legacy renderbuffer (unused when depth_tex valid) */
    GLuint depth_tex;   /* depth texture (GL_DEPTH_COMPONENT32F)           */
    u32    attachment_count;
} GLMRTFBOData;

typedef struct {
    GLuint gl_fbo;
    GLuint depth_tex;   /* GL_TEXTURE_CUBE_MAP */
} GLCubemapDepthFBOData;

/* Cached vertex stride from the most recently bound pipeline.
 * Avoids the O(4096) linear scan of device slots in bind_vertex_buffer. */
static u32 g_cached_vertex_stride = 32;  /* default: 8 floats * sizeof(f32) */
/* R168-C: Draw mode of the currently bound graphics pipeline. */
static GLenum g_gl_draw_mode = GL_TRIANGLES;
static bool   g_gl_point_size_enabled = false;

/* R76-2: File-scope viewport cache — shared by all viewport-setting paths.
 * Previously g_gl_vp was a static local in gl_cmd_set_viewport, invisible to
 * the 9 FBO/shadow functions that called glViewport directly. This caused
 * ~25 redundant glViewport calls per frame and a cache desync correctness risk. */
static GLint g_gl_vp[4] = {-1, -1, -1, -1};

static void gl_set_viewport_cached(GLint x, GLint y, GLsizei w, GLsizei h) {
    if (g_gl_vp[0] != x || g_gl_vp[1] != y || g_gl_vp[2] != (GLint)w || g_gl_vp[3] != (GLint)h) {
        glViewport(x, y, w, h);
        g_gl_vp[0] = x; g_gl_vp[1] = y; g_gl_vp[2] = (GLint)w; g_gl_vp[3] = (GLint)h;
    }
}

/* R77-1: File-scope texture unit cache — shared by gl_bind_tex_unit,
 * rhi_cmd_bind_texel_buffers, and rhi_cmd_bind_texture_mip. Previously
 * these were static locals in gl_bind_tex_unit, invisible to the two
 * functions that called glActiveTexture + glBindTexture directly. This
 * caused stale cache state — gl_bind_tex_unit would skip glActiveTexture
 * (false cache hit) and bind textures to the wrong unit. */
static GLuint g_tex_cache[16] = {0};
static GLuint g_sam_cache[16] = {0};
static u32    g_active_unit = UINT32_MAX;
/* R106-2: SSBO binding cache promoted to file scope so rhi_buffer_destroy
 * can invalidate entries.  When glDeleteBuffers reverts the binding point
 * to 0, the cache must be cleared or a future buffer that reuses the same
 * GL name would falsely register as already bound. */
static GLuint g_gl_ssbo_cache[8] = {0};

/* R77-2: Indirect/parameter buffer cache — avoids redundant glBindBuffer
 * calls and eliminates trailing unbinds between consecutive indirect draws. */
static GLuint g_gl_indirect_buf = 0;
static GLuint g_gl_param_buf = 0;

/* R79-1: FBO bind cache — avoids redundant glBindFramebuffer calls on every
 * FBO switch. Point shadow rendering binds the same FBO 6× per light (once
 * per cubemap face); without cache, each bind triggers driver-side FBO
 * completeness validation. ~20-30 redundant calls/frame eliminated. */
static GLuint g_gl_bound_fbo = 0;

static void gl_bind_fbo_cached(GLuint fbo) {
    if (g_gl_bound_fbo != fbo) {
        glBindFramebuffer(GL_FRAMEBUFFER, fbo);
        g_gl_bound_fbo = fbo;
    }
}

/* R79-4: GL_SCISSOR_TEST enable cache — avoids redundant glEnable/glDisable
 * calls in shadow pass (4 cascades enable + 2 unbinds disable per frame). */
static bool g_gl_scissor_enabled = false;

/* R80-1: VAO bind cache — promoted from function-local static in
 * gl_cmd_bind_pipeline to file scope so rhi_pipeline_create can update
 * it when it binds VAOs during setup. Prevents cache desync if pipeline
 * creation ever happens during rendering (currently init-only, but
 * defensive against future hot-reload). */
static GLuint g_gl_vao = 0;

/* R86-3: VBO/IBO bind cache — avoids redundant glBindVertexBuffer and
 * glBindBuffer(GL_ELEMENT_ARRAY_BUFFER) calls in draw loops. */
static GLuint g_gl_bound_vbo = 0;
static GLuint g_gl_bound_ibo = 0;

/* R80-2: Depth mask and cull-face enable caches — skybox_render was
 * calling glDepthMask/glDisable(GL_CULL_FACE) directly, bypassing caches.
 * Same class of desync risk as R78-2 (glDepthFunc). */
static bool g_gl_depth_mask = true;    /* GL default after gl_init */
static bool g_gl_cull_enabled = true;  /* GL default after gl_init */

static bool gl_init(RHIDevice *dev, void *window_native, void *display_native, u32 w, u32 h) {
    GLBackend *gl = calloc(1, sizeof(GLBackend));
    if (!gl) return false;

#ifdef ENGINE_PLATFORM_WINDOWS
    (void)display_native;
    gl->hwnd = (HWND)window_native;
    gl->hdc = GetDC(gl->hwnd);

    /* Set pixel format */
    PIXELFORMATDESCRIPTOR pfd = {0};
    pfd.nSize = sizeof(pfd);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 32;
    pfd.cDepthBits = 24;
    pfd.cStencilBits = 8;

    int format = ChoosePixelFormat(gl->hdc, &pfd);
    SetPixelFormat(gl->hdc, format, &pfd);

    /* Create temporary context */
    HGLRC temp_ctx = wglCreateContext(gl->hdc);
    wglMakeCurrent(gl->hdc, temp_ctx);

    /* Get wglCreateContextAttribsARB */
    PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB =
        (PFNWGLCREATECONTEXTATTRIBSARBPROC)wglGetProcAddress("wglCreateContextAttribsARB");

    if (wglCreateContextAttribsARB) {
        /* Create OpenGL 4.5 Core Profile context */
        int attribs[] = {
            WGL_CONTEXT_MAJOR_VERSION_ARB, 4,
            WGL_CONTEXT_MINOR_VERSION_ARB, 5,
            WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
            0
        };
        gl->gl_ctx = wglCreateContextAttribsARB(gl->hdc, NULL, attribs);
        wglMakeCurrent(NULL, NULL);
        wglDeleteContext(temp_ctx);
        wglMakeCurrent(gl->hdc, gl->gl_ctx);
    } else {
        gl->gl_ctx = temp_ctx; /* fallback */
    }

    /* Load OpenGL functions */
    if (!gladLoadGL()) {
        LOG_FATAL("GL: failed to load OpenGL functions");
        wglMakeCurrent(NULL, NULL);
        wglDeleteContext(gl->gl_ctx);
        ReleaseDC(gl->hwnd, gl->hdc);
        free(gl);
        return false;
    }
#elif defined(ENGINE_PLATFORM_WAYLAND)
    gl->wl_display = (struct wl_display *)display_native;
    gl->egl_window = (struct wl_egl_window *)window_native;
    if (!gl->wl_display || !gl->egl_window) {
        LOG_FATAL("GL: null Wayland display or egl_window");
        free(gl);
        return false;
    }

    gl->egl_display = eglGetDisplay((EGLNativeDisplayType)gl->wl_display);
    if (gl->egl_display == EGL_NO_DISPLAY) {
        LOG_FATAL("EGL: failed to get display");
        free(gl);
        return false;
    }

    EGLint egl_major = 0, egl_minor = 0;
    if (!eglInitialize(gl->egl_display, &egl_major, &egl_minor)) {
        LOG_FATAL("EGL: failed to initialize");
        free(gl);
        return false;
    }

    if (!eglBindAPI(EGL_OPENGL_API)) {
        LOG_FATAL("EGL: failed to bind OpenGL API");
        eglTerminate(gl->egl_display);
        free(gl);
        return false;
    }

    EGLint config_attribs[] = {
        EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
        EGL_RENDERABLE_TYPE, EGL_OPENGL_BIT,
        EGL_RED_SIZE, 8,
        EGL_GREEN_SIZE, 8,
        EGL_BLUE_SIZE, 8,
        EGL_ALPHA_SIZE, 8,
        EGL_DEPTH_SIZE, 24,
        EGL_STENCIL_SIZE, 8,
        EGL_NONE
    };

    EGLint num_configs = 0;
    if (!eglChooseConfig(gl->egl_display, config_attribs, &gl->egl_config, 1, &num_configs) || num_configs == 0) {
        LOG_FATAL("EGL: failed to choose config");
        eglTerminate(gl->egl_display);
        free(gl);
        return false;
    }

    EGLint context_attribs[] = {
        EGL_CONTEXT_MAJOR_VERSION, 4,
        EGL_CONTEXT_MINOR_VERSION, 5,
        EGL_CONTEXT_OPENGL_PROFILE_MASK, EGL_CONTEXT_OPENGL_CORE_PROFILE_BIT,
        EGL_NONE
    };

    gl->egl_context = eglCreateContext(gl->egl_display, gl->egl_config, EGL_NO_CONTEXT, context_attribs);
    if (gl->egl_context == EGL_NO_CONTEXT) {
        LOG_FATAL("EGL: failed to create OpenGL 4.5 context");
        eglTerminate(gl->egl_display);
        free(gl);
        return false;
    }

    gl->egl_surface = eglCreateWindowSurface(gl->egl_display, gl->egl_config,
                                              (EGLNativeWindowType)gl->egl_window, NULL);
    if (gl->egl_surface == EGL_NO_SURFACE) {
        LOG_FATAL("EGL: failed to create window surface");
        eglDestroyContext(gl->egl_display, gl->egl_context);
        eglTerminate(gl->egl_display);
        free(gl);
        return false;
    }

    if (!eglMakeCurrent(gl->egl_display, gl->egl_surface, gl->egl_surface, gl->egl_context)) {
        LOG_FATAL("EGL: failed to make context current");
        eglDestroySurface(gl->egl_display, gl->egl_surface);
        eglDestroyContext(gl->egl_display, gl->egl_context);
        eglTerminate(gl->egl_display);
        free(gl);
        return false;
    }

    if (!gladLoadGLLoader((GLADloadproc)eglGetProcAddress)) {
        LOG_FATAL("GL: failed to load OpenGL functions");
        eglMakeCurrent(gl->egl_display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
        eglDestroySurface(gl->egl_display, gl->egl_surface);
        eglDestroyContext(gl->egl_display, gl->egl_context);
        eglTerminate(gl->egl_display);
        free(gl);
        return false;
    }
#else
    Display *dpy = (Display *)display_native;
    if (!dpy) { LOG_FATAL("GL: null display"); free(gl); return false; }

    static int visual_attribs[] = {
        GLX_RENDER_TYPE, GLX_RGBA_BIT,
        GLX_DRAWABLE_TYPE, GLX_WINDOW_BIT,
        GLX_DOUBLEBUFFER, True,
        GLX_RED_SIZE, 8, GLX_GREEN_SIZE, 8, GLX_BLUE_SIZE, 8, GLX_ALPHA_SIZE, 8,
        GLX_DEPTH_SIZE, 24,
        None
    };

    int fb_count = 0;
    GLXFBConfig *fbc = glXChooseFBConfig(dpy, DefaultScreen(dpy), visual_attribs, &fb_count);
    if (!fbc || fb_count == 0) { LOG_FATAL("GL: no framebuffer config"); free(gl); return false; }

    GLXFBConfig best_fbc = fbc[0];
    XFree(fbc);

    gl->gl_ctx = glXCreateNewContext(dpy, best_fbc, GLX_RGBA_TYPE, NULL, True);
    if (!gl->gl_ctx) { LOG_FATAL("GL: failed to create context"); free(gl); return false; }

    Window win = (Window)(uintptr_t)window_native;
    if (!glXMakeCurrent(dpy, win, gl->gl_ctx)) {
        LOG_FATAL("GL: failed to make context current");
        glXDestroyContext(dpy, gl->gl_ctx);
        free(gl);
        return false;
    }

    gl->display = dpy;
    gl->window  = win;

    if (!gladLoadGLLoader((GLADloadproc)glXGetProcAddress)) {
        LOG_FATAL("GL: failed to load OpenGL functions");
        glXMakeCurrent(dpy, None, NULL);
        glXDestroyContext(dpy, gl->gl_ctx);
        free(gl);
        return false;
    }
#endif

    LOG_INFO("OpenGL %s initialized", (const char *)glGetString(GL_VERSION));
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    gl_set_viewport_cached(0, 0, w, h);

    dev->backend_data = gl;
    dev->width  = w;
    dev->height = h;
    return true;
}

static void gl_shutdown(RHIDevice *dev) {
    GLBackend *gl = (GLBackend *)dev->backend_data;
    if (!gl) return;
#ifdef ENGINE_PLATFORM_WINDOWS
    wglMakeCurrent(NULL, NULL);
    wglDeleteContext(gl->gl_ctx);
    ReleaseDC(gl->hwnd, gl->hdc);
#elif defined(ENGINE_PLATFORM_WAYLAND)
    if (gl->egl_display != EGL_NO_DISPLAY) {
        eglMakeCurrent(gl->egl_display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
        if (gl->egl_surface != EGL_NO_SURFACE)
            eglDestroySurface(gl->egl_display, gl->egl_surface);
        if (gl->egl_context != EGL_NO_CONTEXT)
            eglDestroyContext(gl->egl_display, gl->egl_context);
        eglTerminate(gl->egl_display);
    }
#else
    glXMakeCurrent(gl->display, None, NULL);
    glXDestroyContext(gl->display, gl->gl_ctx);
#endif
    free(gl);
    dev->backend_data = NULL;
}

static void gl_resize(RHIDevice *dev, u32 w, u32 h) {
    gl_set_viewport_cached(0, 0, w, h);
    dev->width  = w;
    dev->height = h;
}

static u32 g_gl_frame_index = 0;

static void *gl_frame_begin(RHIDevice *dev) {
    (void)dev;
    return NULL;
}

static void gl_frame_end(RHIDevice *dev) {
    (void)dev;
    /* R178: Advance so dual staging (gpucull/occlusion) can ping-pong. */
    g_gl_frame_index++;
}

static void gl_present(RHIDevice *dev) {
    GLBackend *gl = (GLBackend *)dev->backend_data;
#ifdef ENGINE_PLATFORM_WINDOWS
    SwapBuffers(gl->hdc);
#elif defined(ENGINE_PLATFORM_WAYLAND)
    eglSwapBuffers(gl->egl_display, gl->egl_surface);
#else
    glXSwapBuffers(gl->display, gl->window);
#endif
}

static void gl_set_vsync(RHIDevice *dev, bool enabled) {
    GLBackend *gl = (GLBackend *)dev->backend_data;
#ifdef ENGINE_PLATFORM_WINDOWS
    typedef BOOL (WINAPI *PFNWGLSWAPINTERVALEXTPROC)(int);
    PFNWGLSWAPINTERVALEXTPROC fn = (PFNWGLSWAPINTERVALEXTPROC)wglGetProcAddress("wglSwapIntervalEXT");
    if (fn) {
        fn(enabled ? 1 : 0);
    }
    (void)gl;
#elif defined(ENGINE_PLATFORM_WAYLAND)
    eglSwapInterval(gl->egl_display, enabled ? 1 : 0);
#else
    typedef void (*PFNGLXSWAPINTERVALEXT)(Display *, GLXDrawable, int);
    PFNGLXSWAPINTERVALEXT fn = (PFNGLXSWAPINTERVALEXT)glXGetProcAddress((const GLubyte *)"glXSwapIntervalEXT");
    if (fn) {
        fn(gl->display, gl->window, enabled ? 1 : 0);
    }
#endif
}

void rhi_set_vsync(RHIDevice *dev, bool enabled) {
    gl_set_vsync(dev, enabled);
}

static void gl_cmd_begin_render_pass(void *cmd) {
    (void)cmd;
}

static void gl_cmd_end_render_pass(void *cmd) {
    (void)cmd;
}

static void gl_cmd_bind_pipeline(void *cmd, GLPipelineData *pd) {
    (void)cmd;
    /* Cached GL state: only issue state-change calls when pipeline differs
     * from the last bound pipeline. Eliminates redundant driver validation. */
    static bool g_gl_blend_enabled = false;
    static bool g_gl_wireframe     = false;
    static GLuint g_gl_program     = 0;
    /* R80-1: g_gl_vao moved to file scope — shared with rhi_pipeline_create. */

    if (pd->gl_program != g_gl_program) {
        glUseProgram(pd->gl_program);
        g_gl_program = pd->gl_program;
    }
    if (pd->gl_vao != g_gl_vao) {
        glBindVertexArray(pd->gl_vao);
        g_gl_vao = pd->gl_vao;
        /* R86-3: VAO change invalidates VBO/IBO binding state. */
        g_gl_bound_vbo = 0;
        g_gl_bound_ibo = 0;
    }
    if (pd->alpha_blend != g_gl_blend_enabled) {
        if (pd->alpha_blend) {
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        } else {
            glDisable(GL_BLEND);
        }
        g_gl_blend_enabled = pd->alpha_blend;
    }
    if (pd->wireframe != g_gl_wireframe) {
        glPolygonMode(GL_FRONT_AND_BACK, pd->wireframe ? GL_LINE : GL_FILL);
        g_gl_wireframe = pd->wireframe;
    }
    /* R168-C: Track draw mode + PROGRAM_POINT_SIZE for point sprites. */
    g_gl_draw_mode = pd->point_list ? GL_POINTS : GL_TRIANGLES;
    if (pd->point_list != g_gl_point_size_enabled) {
        if (pd->point_list) glEnable(GL_PROGRAM_POINT_SIZE);
        else                glDisable(GL_PROGRAM_POINT_SIZE);
        g_gl_point_size_enabled = pd->point_list;
    }
    g_cached_vertex_stride = pd->vertex_stride;
}

static void gl_cmd_set_viewport(void *cmd, f32 x, f32 y, f32 w, f32 h) {
    (void)cmd;
    /* R76-2: Uses file-scope g_gl_vp cache via gl_set_viewport_cached. */
    gl_set_viewport_cached((GLint)x, (GLint)y, (GLsizei)w, (GLsizei)h);
}

static void gl_cmd_draw(void *cmd, u32 vertex_count, u32 instance_count) {
    (void)cmd;
    glDrawArraysInstanced(g_gl_draw_mode, 0, (GLsizei)vertex_count, (GLsizei)instance_count);
}

static void gl_cmd_draw_indexed(void *cmd, u32 index_count, u32 instance_count) {
    (void)cmd;
    glDrawElementsInstanced(GL_TRIANGLES, (GLsizei)index_count, GL_UNSIGNED_INT, NULL, (GLsizei)instance_count);
}

static void gl_cmd_clear_color(void *cmd, f32 r, f32 g, f32 b, f32 a) {
    (void)cmd;
    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}


RHIDevice *rhi_device_create(RHIBackend backend, void *window_native, void *display_native, u32 w, u32 h) {
    RHIDevice *dev = calloc(1, sizeof(RHIDevice));
    if (!dev) return NULL;
    rhi_init_freelist(dev);

    switch (backend) {
    case RHI_BACKEND_OPENGL: dev->backend_data = NULL; break;
    default: LOG_FATAL("Unsupported RHI backend %d", backend); free(dev); return NULL;
    }

    if (!gl_init(dev, window_native, display_native, w, h)) {
        free(dev);
        return NULL;
    }
    g_current_device = dev;
    return dev;
}

void rhi_device_destroy(RHIDevice *dev) {
    if (!dev) return;
    for (u32 i = 0; i < RHI_MAX_RESOURCES; i++) {
        if (!dev->slots[i].alive) continue;
        switch (dev->slots[i].type) {
        case RHI_RES_SHADER: {
            GLShaderData *sd = (GLShaderData *)dev->slots[i].ptr;
            if (sd) { glDeleteShader(sd->gl_shader); free(sd); }
            break;
        }
        case RHI_RES_PIPELINE: {
            GLPipelineData *pd = (GLPipelineData *)dev->slots[i].ptr;
            if (pd) {
                glDeleteProgram(pd->gl_program);
                glDeleteVertexArrays(1, &pd->gl_vao);
                if (pd->gl_vbo) glDeleteBuffers(1, &pd->gl_vbo);
                if (pd->gl_ibo) glDeleteBuffers(1, &pd->gl_ibo);
                free(pd);
            }
            break;
        }
        case RHI_RES_BUFFER: {
            GLBufferData *bd = (GLBufferData *)dev->slots[i].ptr;
            if (bd) { glDeleteBuffers(1, &bd->gl_buf); free(bd); }
            break;
        }
        case RHI_RES_TEXTURE: {
            GLTextureData *td = (GLTextureData *)dev->slots[i].ptr;
            if (td) { glDeleteTextures(1, &td->gl_tex); free(td); }
            break;
        }
        case RHI_RES_SAMPLER: {
            GLSamplerData *sd = (GLSamplerData *)dev->slots[i].ptr;
            if (sd) { glDeleteSamplers(1, &sd->gl_sampler); free(sd); }
            break;
        }
        case RHI_RES_FRAMEBUFFER: {
            GLFBOData *fd = (GLFBOData *)dev->slots[i].ptr;
            if (fd) {
                if (fd->gl_fbo) glDeleteFramebuffers(1, &fd->gl_fbo);
                if (fd->color_tex) glDeleteTextures(1, &fd->color_tex);
                if (fd->depth_rb) glDeleteRenderbuffers(1, &fd->depth_rb);
                free(fd);
            }
            break;
        }
        case RHI_RES_CUBEMAP: {
            GLTextureData *td = (GLTextureData *)dev->slots[i].ptr;
            if (td) { glDeleteTextures(1, &td->gl_tex); free(td); }
            break;
        }
        case RHI_RES_MRT_FBO: {
            GLMRTFBOData *md = (GLMRTFBOData *)dev->slots[i].ptr;
            if (md) {
                if (md->gl_fbo) glDeleteFramebuffers(1, &md->gl_fbo);
                for (u32 ai = 0; ai < md->attachment_count; ai++) {
                    if (md->color_tex[ai]) glDeleteTextures(1, &md->color_tex[ai]);
                }
                if (md->depth_tex) glDeleteTextures(1, &md->depth_tex);
                if (md->depth_rb) glDeleteRenderbuffers(1, &md->depth_rb);
                free(md);
            }
            break;
        }
        case RHI_RES_CUBEMAP_DEPTH_FBO: {
            GLCubemapDepthFBOData *cd = (GLCubemapDepthFBOData *)dev->slots[i].ptr;
            if (cd) {
                if (cd->gl_fbo) glDeleteFramebuffers(1, &cd->gl_fbo);
                if (cd->depth_tex) glDeleteTextures(1, &cd->depth_tex);
                free(cd);
            }
            break;
        }
        default:
            LOG_WARN("Unknown resource type %d in slot %u", dev->slots[i].type, i);
            free(dev->slots[i].ptr);
            break;
        }
    }
    gl_shutdown(dev);
    if (g_current_device == dev) g_current_device = NULL;
    free(dev);
}

void rhi_device_resize(RHIDevice *dev, u32 w, u32 h) {
    gl_resize(dev, w, h);
}

RHICmdBuffer *rhi_frame_begin(RHIDevice *dev) {
    g_current_device = dev;
    return (RHICmdBuffer *)gl_frame_begin(dev);
}

void rhi_frame_end(RHIDevice *dev) {
    gl_frame_end(dev);
}

void rhi_present(RHIDevice *dev) {
    gl_present(dev);
}

u32 rhi_frame_index(RHIDevice *dev) {
    (void)dev;
    /* R178: Was hardcoded 0 — dual staging always hit slot 0 and stalled on map. */
    return g_gl_frame_index;
}

static GLuint gl_compile_shader(const char *source, usize len, GLenum type) {
    GLuint sh = glCreateShader(type);
    GLint slen = (GLint)len;
    glShaderSource(sh, 1, &source, &slen);
    glCompileShader(sh);

    GLint ok = 0;
    glGetShaderiv(sh, GL_COMPILE_STATUS, &ok);
    if (!ok) {
        char log[512];
        glGetShaderInfoLog(sh, sizeof(log), NULL, log);
        LOG_FATAL("Shader compile error: %s", log);
        glDeleteShader(sh);
        return 0;
    }
    return sh;
}

RHIShader rhi_shader_create(RHIDevice *dev, const char *source, usize len, bool is_fragment) {
    GLenum type = is_fragment ? GL_FRAGMENT_SHADER : GL_VERTEX_SHADER;
    GLuint gl_sh = gl_compile_shader(source, len, type);
    if (!gl_sh) return RHI_HANDLE_NULL;

    GLShaderData *sd = calloc(1, sizeof(GLShaderData));
    if (!sd) { glDeleteShader(gl_sh); return RHI_HANDLE_NULL; }
    u32 idx = rhi_alloc_slot(dev);
    sd->gl_shader = gl_sh;
    dev->slots[idx].ptr  = sd;
    dev->slots[idx].type = RHI_RES_SHADER;
    return rhi_make_handle(idx, dev->slots[idx].generation);
}

void rhi_shader_destroy(RHIDevice *dev, RHIShader shader) {
    GLShaderData *sd = (GLShaderData *)rhi_get_resource(dev, shader);
    if (!sd) return;
    glDeleteShader(sd->gl_shader);
    free(sd);
    rhi_free_slot(dev, shader);
}

RHIShader rhi_shader_create_compute(RHIDevice *dev, const char *source, usize len) {
    GLuint gl_sh = gl_compile_shader(source, len, GL_COMPUTE_SHADER);
    if (!gl_sh) return RHI_HANDLE_NULL;
    GLShaderData *sd = calloc(1, sizeof(GLShaderData));
    if (!sd) { glDeleteShader(gl_sh); return RHI_HANDLE_NULL; }
    u32 idx = rhi_alloc_slot(dev);
    sd->gl_shader = gl_sh;
    dev->slots[idx].ptr = sd;
    dev->slots[idx].type = RHI_RES_SHADER;
    return rhi_make_handle(idx, dev->slots[idx].generation);
}

RHIPipeline rhi_pipeline_create(RHIDevice *dev, const RHIPipelineDesc *desc) {
    if (desc->is_compute) {
        GLShaderData *cs = (GLShaderData *)rhi_get_resource(dev, desc->frag);
        if (!cs) return RHI_HANDLE_NULL;

        GLuint program = glCreateProgram();
        glAttachShader(program, cs->gl_shader);
        glLinkProgram(program);

        GLint ok = 0;
        glGetProgramiv(program, GL_LINK_STATUS, &ok);
        if (!ok) {
            char log[512];
            glGetProgramInfoLog(program, sizeof(log), NULL, log);
            LOG_FATAL("Compute program link error: %s", log);
            glDeleteProgram(program);
            return RHI_HANDLE_NULL;
        }

        GLPipelineData *pd = calloc(1, sizeof(GLPipelineData));
        if (!pd) { glDeleteProgram(program); return RHI_HANDLE_NULL; }
        u32 idx = rhi_alloc_slot(dev);
        pd->gl_program = program;
        dev->slots[idx].ptr = pd;
        dev->slots[idx].type = RHI_RES_PIPELINE;
        return rhi_make_handle(idx, dev->slots[idx].generation);
    }

    GLShaderData *vs = (GLShaderData *)rhi_get_resource(dev, desc->vert);
    GLShaderData *fs = (GLShaderData *)rhi_get_resource(dev, desc->frag);
    if (!vs || !fs) return RHI_HANDLE_NULL;

    GLuint program = glCreateProgram();
    glAttachShader(program, vs->gl_shader);
    glAttachShader(program, fs->gl_shader);
    glLinkProgram(program);

    GLint ok = 0;
    glGetProgramiv(program, GL_LINK_STATUS, &ok);
    if (!ok) {
        char log[512];
        glGetProgramInfoLog(program, sizeof(log), NULL, log);
        LOG_FATAL("Program link error: %s", log);
        glDeleteProgram(program);
        return RHI_HANDLE_NULL;
    }

    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    g_gl_vao = vao;  /* R80-1: Update cache — VAO is now bound. */
    g_gl_bound_vbo = 0;  /* R86-3: VAO change invalidates VBO/IBO cache. */
    g_gl_bound_ibo = 0;

    u32 stride = desc->vertex_stride;
    if (desc->no_vertex_input) {
        /* Fullscreen triangle via gl_VertexID */
    } else if (desc->font_vertex) {
        stride = 32;
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glEnableVertexAttribArray(2);
        glVertexAttribFormat(0, 2, GL_FLOAT, GL_FALSE, 0);
        glVertexAttribFormat(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(f32));
        glVertexAttribFormat(2, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(f32));
        glVertexAttribBinding(0, 0);
        glVertexAttribBinding(1, 0);
        glVertexAttribBinding(2, 0);
    } else if (desc->skinned_vertex) {
        stride = 64;
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glEnableVertexAttribArray(2);
        glEnableVertexAttribArray(3);
        glEnableVertexAttribArray(4);
        glVertexAttribFormat(0, 3, GL_FLOAT, GL_FALSE, 0);
        glVertexAttribFormat(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(f32));
        glVertexAttribFormat(2, 2, GL_FLOAT, GL_FALSE, 6 * sizeof(f32));
        glVertexAttribIFormat(3, 4, GL_UNSIGNED_INT, 8 * sizeof(f32));
        glVertexAttribFormat(4, 4, GL_FLOAT, GL_FALSE, 8 * sizeof(f32) + 4 * sizeof(u32));
        glVertexAttribBinding(0, 0);
        glVertexAttribBinding(1, 0);
        glVertexAttribBinding(2, 0);
        glVertexAttribBinding(3, 0);
        glVertexAttribBinding(4, 0);
    } else if (stride == 12) {
        glEnableVertexAttribArray(0);
        glVertexAttribFormat(0, 3, GL_FLOAT, GL_FALSE, 0);
        glVertexAttribBinding(0, 0);
    } else {
        stride = stride > 0 ? stride : 32;
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glEnableVertexAttribArray(2);
        glVertexAttribFormat(0, 3, GL_FLOAT, GL_FALSE, 0);
        glVertexAttribFormat(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(f32));
        glVertexAttribFormat(2, 2, GL_FLOAT, GL_FALSE, 6 * sizeof(f32));
        glVertexAttribBinding(0, 0);
        glVertexAttribBinding(1, 0);
        glVertexAttribBinding(2, 0);
    }

    glBindVertexArray(0);
    g_gl_vao = 0;  /* R80-1: Update cache — default VAO is now bound. */
    g_gl_bound_vbo = 0;  /* R86-3: VAO change invalidates VBO/IBO cache. */
    g_gl_bound_ibo = 0;

    GLPipelineData *pd = calloc(1, sizeof(GLPipelineData));
    if (!pd) { glDeleteProgram(program); glDeleteVertexArrays(1, &vao); return RHI_HANDLE_NULL; }
    u32 idx = rhi_alloc_slot(dev);
    pd->gl_program     = program;
    pd->gl_vao         = vao;
    pd->vertex_stride  = stride;
    pd->alpha_blend    = desc->alpha_blend;
    pd->wireframe      = desc->wireframe;
    pd->point_list     = desc->point_list;
    dev->slots[idx].ptr  = pd;
    dev->slots[idx].type = RHI_RES_PIPELINE;
    return rhi_make_handle(idx, dev->slots[idx].generation);
}

void rhi_pipeline_destroy(RHIDevice *dev, RHIPipeline pipe) {
    GLPipelineData *pd = (GLPipelineData *)rhi_get_resource(dev, pipe);
    if (!pd) return;
    glDeleteProgram(pd->gl_program);
    glDeleteVertexArrays(1, &pd->gl_vao);
    if (pd->gl_vbo) glDeleteBuffers(1, &pd->gl_vbo);
    if (pd->gl_ibo) glDeleteBuffers(1, &pd->gl_ibo);
    free(pd);
    rhi_free_slot(dev, pipe);
}

RHIBuffer rhi_buffer_create(RHIDevice *dev, const RHIBufferDesc *desc) {
    GLuint gl_buf = 0;
    glGenBuffers(1, &gl_buf);

    bool is_texel = (desc->usage & RHI_BUFFER_USAGE_TEXEL) != 0;
    bool is_storage = (desc->usage & RHI_BUFFER_USAGE_STORAGE) != 0;
    GLenum target = GL_ARRAY_BUFFER;
    if (desc->usage & RHI_BUFFER_USAGE_INDEX)   target = GL_ELEMENT_ARRAY_BUFFER;
    if (desc->usage & RHI_BUFFER_USAGE_UNIFORM) target = GL_UNIFORM_BUFFER;
    if (is_texel)                                target = GL_TEXTURE_BUFFER;
    if (is_storage)                              target = GL_SHADER_STORAGE_BUFFER;

    glBindBuffer(target, gl_buf);
    GLenum usage = (desc->usage & (RHI_BUFFER_USAGE_UNIFORM | RHI_BUFFER_USAGE_TEXEL)) ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW;
    if (is_storage) usage = GL_DYNAMIC_DRAW;
    glBufferData(target, (GLsizeiptr)desc->size, desc->initial_data, usage);
    glBindBuffer(target, 0);

    GLuint tbo_tex = 0;
    if (is_texel) {
        glGenTextures(1, &tbo_tex);
        glBindTexture(GL_TEXTURE_BUFFER, tbo_tex);
        glTexBuffer(GL_TEXTURE_BUFFER, GL_RGBA32F, gl_buf);
        glBindTexture(GL_TEXTURE_BUFFER, 0);
    }

    GLBufferData *bd = calloc(1, sizeof(GLBufferData));
    if (!bd) { glDeleteBuffers(1, &gl_buf); if (tbo_tex) glDeleteTextures(1, &tbo_tex); return RHI_HANDLE_NULL; }
    u32 idx = rhi_alloc_slot(dev);
    bd->gl_buf  = gl_buf;
    bd->tbo_tex = tbo_tex;
    bd->size    = desc->size;
    dev->slots[idx].ptr  = bd;
    dev->slots[idx].type = RHI_RES_BUFFER;
    return rhi_make_handle(idx, dev->slots[idx].generation);
}

void rhi_buffer_destroy(RHIDevice *dev, RHIBuffer buf) {
    GLBufferData *bd = (GLBufferData *)rhi_get_resource(dev, buf);
    if (!bd) return;
    /* R106-2: Invalidate SSBO cache — glDeleteBuffers reverts all SSBO binding
     * points that referenced this buffer to 0, but the cache still holds the
     * old name.  A future buffer reusing the same GL name would skip the bind. */
    for (u32 i = 0; i < 8; i++) {
        if (g_gl_ssbo_cache[i] == bd->gl_buf) g_gl_ssbo_cache[i] = 0;
    }
    if (bd->tbo_tex) glDeleteTextures(1, &bd->tbo_tex);
    glDeleteBuffers(1, &bd->gl_buf);
    free(bd);
    rhi_free_slot(dev, buf);
}

void rhi_cmd_begin_render_pass(RHICmdBuffer *cmd) { gl_cmd_begin_render_pass(cmd); }
void rhi_cmd_end_render_pass(RHICmdBuffer *cmd) { gl_cmd_end_render_pass(cmd); }

void rhi_cmd_bind_pipeline(RHICmdBuffer *cmd, RHIPipeline pipe) {
    (void)cmd;
    extern RHIDevice *g_current_device;
    GLPipelineData *pd = (GLPipelineData *)rhi_get_resource(g_current_device, pipe);
    if (pd) {
        gl_cmd_bind_pipeline(cmd, pd);
        g_cached_vertex_stride = pd->vertex_stride;
    }
}

void rhi_cmd_bind_vertex_buffer(RHICmdBuffer *cmd, RHIBuffer buf, usize offset) {
    (void)cmd;
    extern RHIDevice *g_current_device;
    GLBufferData *bd = (GLBufferData *)rhi_get_resource(g_current_device, buf);
    if (bd && bd->gl_buf != g_gl_bound_vbo) {
        /* R86-3: Cache VBO binding to avoid redundant glBindVertexBuffer calls. */
        glBindVertexBuffer(0, bd->gl_buf, (GLintptr)offset,
                           (GLsizei)g_cached_vertex_stride);
        g_gl_bound_vbo = bd->gl_buf;
    }
}

void rhi_cmd_bind_index_buffer(RHICmdBuffer *cmd, RHIBuffer buf, usize offset) {
    (void)cmd; (void)offset;
    extern RHIDevice *g_current_device;
    GLBufferData *bd = (GLBufferData *)rhi_get_resource(g_current_device, buf);
    if (bd && bd->gl_buf != g_gl_bound_ibo) {
        /* R86-3: Cache IBO binding to avoid redundant glBindBuffer calls. */
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bd->gl_buf);
        g_gl_bound_ibo = bd->gl_buf;
    }
}

void rhi_cmd_set_viewport(RHICmdBuffer *cmd, f32 x, f32 y, f32 w, f32 h) {
    gl_cmd_set_viewport(cmd, x, y, w, h);
}

void rhi_cmd_set_scissor(RHICmdBuffer *cmd, i32 x, i32 y, u32 w, u32 h) {
    (void)cmd; (void)x; (void)y; (void)w; (void)h;
}

void rhi_cmd_set_shadow_viewport(RHICmdBuffer *cmd, u32 x, u32 y, u32 w, u32 h) {
    (void)cmd;
    /* Restrict rendering (and prevent cross-quadrant bleed) to one cascade
     * quadrant of the shadow atlas. GL uses a native bottom-left origin; the
     * sampling remap in the shaders uses the same quadrant convention. */
    gl_set_viewport_cached((GLint)x, (GLint)y, (GLsizei)w, (GLsizei)h);
    /* R79-4: Cached scissor test enable. */
    if (!g_gl_scissor_enabled) { glEnable(GL_SCISSOR_TEST); g_gl_scissor_enabled = true; }
    glScissor((GLint)x, (GLint)y, (GLsizei)w, (GLsizei)h);
}

void rhi_cmd_draw(RHICmdBuffer *cmd, u32 vertex_count, u32 instance_count) {
    gl_cmd_draw(cmd, vertex_count, instance_count);
}

void rhi_cmd_draw_indexed(RHICmdBuffer *cmd, u32 index_count, u32 instance_count) {
    gl_cmd_draw_indexed(cmd, index_count, instance_count);
}

void rhi_cmd_draw_indirect(RHIDevice *dev, RHIBuffer cmd_buf, u32 offset,
                           u32 draw_count, u32 stride) {
    GLBufferData *bd = (GLBufferData *)rhi_get_resource(dev, cmd_buf);
    if (!bd) return;
    if (g_gl_indirect_buf != bd->gl_buf) {
        glBindBuffer(GL_DRAW_INDIRECT_BUFFER, bd->gl_buf);
        g_gl_indirect_buf = bd->gl_buf;
    }
    /* R168-C: Use bound pipeline's draw mode (POINTS for particles). */
    glMultiDrawArraysIndirect(g_gl_draw_mode,
                              (const void *)(uintptr_t)offset,
                              (GLsizei)draw_count, (GLsizei)stride);
}

void rhi_cmd_draw_indexed_indirect(RHIDevice *dev, RHIBuffer cmd_buf, u32 offset,
                                   u32 draw_count, u32 stride) {
    GLBufferData *bd = (GLBufferData *)rhi_get_resource(dev, cmd_buf);
    if (!bd) return;
    /* R77-2: Cache indirect buffer bind — skip if already bound. */
    if (g_gl_indirect_buf != bd->gl_buf) {
        glBindBuffer(GL_DRAW_INDIRECT_BUFFER, bd->gl_buf);
        g_gl_indirect_buf = bd->gl_buf;
    }
    glMultiDrawElementsIndirect(GL_TRIANGLES, GL_UNSIGNED_INT,
                                (const void *)(uintptr_t)offset,
                                (GLsizei)draw_count, (GLsizei)stride);
}

void rhi_cmd_draw_indexed_indirect_count(RHIDevice *dev, RHIBuffer cmd_buf, u32 cmd_offset,
                                         RHIBuffer count_buf, u32 count_offset,
                                         u32 max_draws, u32 stride) {
    GLBufferData *cmd_bd   = (GLBufferData *)rhi_get_resource(dev, cmd_buf);
    GLBufferData *count_bd = (GLBufferData *)rhi_get_resource(dev, count_buf);
    if (!cmd_bd || !count_bd) return;

    /* Prefer GL_ARB_indirect_parameters (core in 4.6) when available. */
    if (glMultiDrawElementsIndirectCountARB) {
        /* R77-2: Cache binds — skip if already bound. Remove trailing unbinds. */
        if (g_gl_indirect_buf != cmd_bd->gl_buf) {
            glBindBuffer(GL_DRAW_INDIRECT_BUFFER, cmd_bd->gl_buf);
            g_gl_indirect_buf = cmd_bd->gl_buf;
        }
        if (g_gl_param_buf != count_bd->gl_buf) {
            glBindBuffer(0x80EE, count_bd->gl_buf);
            g_gl_param_buf = count_bd->gl_buf;
        }
        glMultiDrawElementsIndirectCountARB(GL_TRIANGLES, GL_UNSIGNED_INT,
                                            (const void *)(uintptr_t)cmd_offset,
                                            (GLintptr)count_offset,
                                            (GLsizei)max_draws,
                                            (GLsizei)stride);
        return;
    }

    /* Fallback: read draw count from the GPU buffer and issue a regular
     * glMultiDrawElementsIndirect with the resolved count. This stalls the
     * pipeline but keeps the API working on GL 4.3-4.5. */
    u32 actual = 0;
    glBindBuffer(GL_COPY_READ_BUFFER, count_bd->gl_buf);
    glGetBufferSubData(GL_COPY_READ_BUFFER, (GLintptr)count_offset,
                       (GLsizeiptr)sizeof(u32), &actual);
    glBindBuffer(GL_COPY_READ_BUFFER, 0);
    if (actual > max_draws) actual = max_draws;
    if (actual == 0) return;

    if (g_gl_indirect_buf != cmd_bd->gl_buf) {
        glBindBuffer(GL_DRAW_INDIRECT_BUFFER, cmd_bd->gl_buf);
        g_gl_indirect_buf = cmd_bd->gl_buf;
    }
    glMultiDrawElementsIndirect(GL_TRIANGLES, GL_UNSIGNED_INT,
                                (const void *)(uintptr_t)cmd_offset,
                                (GLsizei)actual, (GLsizei)stride);
}

void rhi_cmd_clear_color(RHICmdBuffer *cmd, f32 r, f32 g, f32 b, f32 a) {
    gl_cmd_clear_color(cmd, r, g, b, a);
}

static GLenum rhi_format_to_gl_internal(RHIFormat fmt) {
    switch (fmt) {
    case RHI_FORMAT_R8G8B8A8_UNORM: return GL_RGBA8;
    case RHI_FORMAT_B8G8R8A8_UNORM: return GL_RGBA8;
    case RHI_FORMAT_R16G16B16A16_SFLOAT: return GL_RGBA16F;
    case RHI_FORMAT_D32_FLOAT:      return GL_DEPTH_COMPONENT32F;
    default: return GL_RGBA8;
    }
}

static GLenum rhi_format_to_gl_format(RHIFormat fmt) {
    switch (fmt) {
    case RHI_FORMAT_R8G8B8A8_UNORM: return GL_RGBA;
    case RHI_FORMAT_B8G8R8A8_UNORM: return GL_BGRA;
    case RHI_FORMAT_R16G16B16A16_SFLOAT: return GL_RGBA;
    case RHI_FORMAT_D32_FLOAT:      return GL_DEPTH_COMPONENT;
    default: return GL_RGBA;
    }
}

RHITexture rhi_texture_create(RHIDevice *dev, const RHITextureDesc *desc) {
    GLuint gl_tex = 0;
    glGenTextures(1, &gl_tex);
    glBindTexture(GL_TEXTURE_2D, gl_tex);

    glTexImage2D(GL_TEXTURE_2D, 0,
                 rhi_format_to_gl_internal(desc->format),
                 (GLsizei)desc->width, (GLsizei)desc->height, 0,
                 rhi_format_to_gl_format(desc->format),
                  (desc->format == RHI_FORMAT_D32_FLOAT || desc->format == RHI_FORMAT_R16G16B16A16_SFLOAT) ? GL_FLOAT : GL_UNSIGNED_BYTE,
                 desc->data);

    if (desc->mip_levels > 1) {
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    }

    glBindTexture(GL_TEXTURE_2D, 0);

    GLTextureData *td = calloc(1, sizeof(GLTextureData));
    if (!td) { glDeleteTextures(1, &gl_tex); return RHI_HANDLE_NULL; }
    u32 idx = rhi_alloc_slot(dev);
    td->gl_tex            = gl_tex;
    td->width             = desc->width;
    td->height            = desc->height;
    td->gl_internal_format = rhi_format_to_gl_internal(desc->format);
    dev->slots[idx].ptr  = td;
    dev->slots[idx].type = RHI_RES_TEXTURE;
    return rhi_make_handle(idx, dev->slots[idx].generation);
}

void rhi_texture_destroy(RHIDevice *dev, RHITexture tex) {
    GLTextureData *td = (GLTextureData *)rhi_get_resource(dev, tex);
    if (!td) return;
    /* R106-2: Invalidate cache entries — glDeleteTextures reverts all bound
     * units to 0, but the cache still holds the old name.  A future texture
     * that reuses the same GL name would falsely skip the bind. */
    for (u32 i = 0; i < 16; i++) {
        if (g_tex_cache[i] == td->gl_tex) g_tex_cache[i] = 0;
    }
    glDeleteTextures(1, &td->gl_tex);
    free(td);
    rhi_free_slot(dev, tex);
}

void rhi_texture_upload_mip(RHIDevice *dev, RHITexture tex, u32 mip_level,
                            u32 width, u32 height, const void *data, usize size) {
    (void)size;
    GLTextureData *td = (GLTextureData *)rhi_get_resource(dev, tex);
    if (!td || !data) return;
    /* R79-2: Bind for upload — invalidate g_tex_cache afterward since both
     * binds bypass the cache (same class of bug as R77-1/R78-1). */
    glBindTexture(GL_TEXTURE_2D, td->gl_tex);
    /* Define + upload the requested level (mutable storage). RGBA8 streaming. */
    glTexImage2D(GL_TEXTURE_2D, (GLint)mip_level, GL_RGBA8,
                 (GLsizei)width, (GLsizei)height, 0,
                 GL_RGBA, GL_UNSIGNED_BYTE, data);
    glBindTexture(GL_TEXTURE_2D, 0);
    if (g_active_unit < 16) g_tex_cache[g_active_unit] = 0;
}

static GLenum rhi_filter_to_gl(RHIFilter f) {
    return f == RHI_FILTER_LINEAR ? GL_LINEAR : GL_NEAREST;
}

static GLenum rhi_wrap_to_gl(RHIWrapMode w) {
    return w == RHI_WRAP_CLAMP_TO_EDGE ? GL_CLAMP_TO_EDGE : GL_REPEAT;
}

RHISampler rhi_sampler_create(RHIDevice *dev, const RHISamplerDesc *desc) {
    GLuint gl_samp = 0;
    glGenSamplers(1, &gl_samp);
    glSamplerParameteri(gl_samp, GL_TEXTURE_MIN_FILTER, rhi_filter_to_gl(desc->min_filter));
    glSamplerParameteri(gl_samp, GL_TEXTURE_MAG_FILTER, rhi_filter_to_gl(desc->mag_filter));
    glSamplerParameteri(gl_samp, GL_TEXTURE_WRAP_S, rhi_wrap_to_gl(desc->wrap_u));
    glSamplerParameteri(gl_samp, GL_TEXTURE_WRAP_T, rhi_wrap_to_gl(desc->wrap_v));
    glSamplerParameteri(gl_samp, GL_TEXTURE_WRAP_R, rhi_wrap_to_gl(desc->wrap_w));

    GLSamplerData *sd = calloc(1, sizeof(GLSamplerData));
    if (!sd) { glDeleteSamplers(1, &gl_samp); return RHI_HANDLE_NULL; }
    u32 idx = rhi_alloc_slot(dev);
    sd->gl_sampler = gl_samp;
    dev->slots[idx].ptr  = sd;
    dev->slots[idx].type = RHI_RES_SAMPLER;
    return rhi_make_handle(idx, dev->slots[idx].generation);
}

void rhi_sampler_destroy(RHIDevice *dev, RHISampler sampler) {
    GLSamplerData *sd = (GLSamplerData *)rhi_get_resource(dev, sampler);
    if (!sd) return;
    /* R106-2: Invalidate cache entries — glDeleteSamplers detaches the sampler
     * from all units, but the cache still holds the old name. */
    for (u32 i = 0; i < 16; i++) {
        if (g_sam_cache[i] == sd->gl_sampler) g_sam_cache[i] = 0;
    }
    glDeleteSamplers(1, &sd->gl_sampler);
    free(sd);
    rhi_free_slot(dev, sampler);
}

static void gl_bind_tex_unit(u32 unit, RHITexture tex, RHISampler sampler) {
    extern RHIDevice *g_current_device;
    GLTextureData *td = (GLTextureData *)rhi_get_resource(g_current_device, tex);
    GLSamplerData *sd = (GLSamplerData *)rhi_get_resource(g_current_device, sampler);

    /* R77-1: Cache variables promoted to file scope — see definitions above. */

    if (td) {
        /* Choose the GL target from the resource type: cubemaps (including
         * point-shadow depth cubes) must bind to GL_TEXTURE_CUBE_MAP, never
         * GL_TEXTURE_2D, otherwise sampling reads garbage / GL errors. */
        GLenum target = GL_TEXTURE_2D;
        bool depth_cube = false;
        if (tex.index < RHI_MAX_RESOURCES) {
            RHIResourceType t = g_current_device->slots[tex.index].type;
            if (t == RHI_RES_CUBEMAP) {
                target = GL_TEXTURE_CUBE_MAP;
                depth_cube = (td->gl_internal_format == GL_DEPTH_COMPONENT32F ||
                              td->gl_internal_format == GL_DEPTH_COMPONENT24 ||
                              td->gl_internal_format == GL_DEPTH_COMPONENT);
            }
        }
        if (unit < 16 && td->gl_tex == g_tex_cache[unit] && g_active_unit == unit) {
            /* Texture already bound to this unit — only update sampler if needed */
            if (depth_cube) { glBindSampler(unit, 0); return; }
            if (sd && unit < 16 && sd->gl_sampler == g_sam_cache[unit]) return;
        } else {
            if (g_active_unit != unit) {
                glActiveTexture(GL_TEXTURE0 + unit);
                g_active_unit = unit;
            }
            if (unit < 16) g_tex_cache[unit] = td->gl_tex;
            glBindTexture(target, td->gl_tex);
            if (depth_cube) {
                /* samplerCubeShadow relies on the texture's COMPARE_REF_TO_TEXTURE
                 * params; a non-compare sampler object would disable the PCF. */
                glBindSampler(unit, 0);
                if (unit < 16) g_sam_cache[unit] = 0;
                return;
            }
        }
    }
    if (sd) {
        if (unit < 16 && sd->gl_sampler == g_sam_cache[unit]) return;
        glBindSampler(unit, sd->gl_sampler);
        if (unit < 16) g_sam_cache[unit] = sd->gl_sampler;
    }
}

void rhi_cmd_bind_material_textures(RHICmdBuffer *cmd,
    RHITexture albedo, RHITexture mr, RHITexture normal, RHITexture emissive,
    RHITexture shadow, RHITexture ssao, RHISampler sampler) {
    (void)cmd; (void)ssao;
    gl_bind_tex_unit(0, albedo, sampler);
    gl_bind_tex_unit(1, shadow, sampler);
    gl_bind_tex_unit(2, mr, sampler);
    gl_bind_tex_unit(3, normal, sampler);
    gl_bind_tex_unit(4, emissive, sampler);
    gl_bind_tex_unit(5, ssao, sampler);
}

void rhi_cmd_bind_material_textures_ibl(RHICmdBuffer *cmd,
    RHITexture albedo, RHITexture mr, RHITexture normal, RHITexture emissive,
    RHITexture shadow, RHITexture ssao, RHISampler sampler,
    RHITexture brdf_lut, RHICubemap irradiance_map, RHICubemap prefilter_map,
    const RHITexture *point_shadow_cubes, u32 point_shadow_count) {
    (void)cmd;
    gl_bind_tex_unit(0, albedo, sampler);
    gl_bind_tex_unit(1, shadow, sampler);
    gl_bind_tex_unit(2, mr, sampler);
    gl_bind_tex_unit(3, normal, sampler);
    gl_bind_tex_unit(4, emissive, sampler);
    gl_bind_tex_unit(11, ssao, sampler);
    if (point_shadow_cubes && point_shadow_count > 0u) {
        u32 n = point_shadow_count > 4u ? 4u : point_shadow_count;
        for (u32 i = 0u; i < n; i++)
            gl_bind_tex_unit(10u + i, point_shadow_cubes[i], sampler);
    }
    /* IBL textures at units 7/8/9 matching GL shader layout bindings */
    if (rhi_handle_valid(brdf_lut))
        gl_bind_tex_unit(7, brdf_lut, sampler);
    if (rhi_handle_valid(irradiance_map))
        rhi_cmd_bind_cubemap(cmd, irradiance_map, sampler, 8u);
    if (rhi_handle_valid(prefilter_map))
        rhi_cmd_bind_cubemap(cmd, prefilter_map, sampler, 9u);
}

void rhi_cmd_bind_textures_multi(RHICmdBuffer *cmd,
    RHITexture *textures, int count, RHISampler sampler) {
    (void)cmd;
    for (int i = 0; i < count && i < 6; i++) {
        gl_bind_tex_unit(i, textures[i], sampler);
    }
}

void rhi_cmd_bind_texture(RHICmdBuffer *cmd, RHITexture tex, RHISampler sampler, u32 unit) {
    (void)cmd;
    gl_bind_tex_unit(unit, tex, sampler);
}

void rhi_cmd_bind_shadow_texture(RHICmdBuffer *cmd, RHITexture shadow_tex, RHISampler sampler) {
    (void)cmd;
    gl_bind_tex_unit(1, shadow_tex, sampler);
}

void rhi_cmd_bind_uniform_buffer(RHICmdBuffer *cmd, RHIBuffer buf, u32 binding) {
    (void)cmd;
    extern RHIDevice *g_current_device;
    GLBufferData *bd = (GLBufferData *)rhi_get_resource(g_current_device, buf);
    if (bd) glBindBufferBase(GL_UNIFORM_BUFFER, binding, bd->gl_buf);
}

void rhi_cmd_set_uniform_mat4(RHICmdBuffer *cmd, i32 location, const f32 *m) {
    (void)cmd;
    if (location >= 0) glUniformMatrix4fv(location, 1, GL_FALSE, m);
}

void rhi_cmd_set_uniform_vec3(RHICmdBuffer *cmd, i32 location, f32 x, f32 y, f32 z) {
    (void)cmd;
    if (location >= 0) glUniform3f(location, x, y, z);
}

void rhi_cmd_set_uniform_vec2(RHICmdBuffer *cmd, i32 location, f32 x, f32 y) {
    (void)cmd;
    if (location >= 0) glUniform2f(location, x, y);
}

void rhi_cmd_set_uniform_vec4(RHICmdBuffer *cmd, i32 location, f32 x, f32 y, f32 z, f32 w) {
    (void)cmd;
    if (location >= 0) glUniform4f(location, x, y, z, w);
}

void rhi_cmd_set_uniform_f32(RHICmdBuffer *cmd, i32 location, f32 v) {
    (void)cmd;
    if (location >= 0) glUniform1f(location, v);
}

void rhi_cmd_set_uniform_bytes(RHICmdBuffer *cmd, i32 location, const void *data, u32 size) {
    /* GL uses per-uniform locations; raw push blobs are Vulkan-only. */
    (void)cmd; (void)location; (void)data; (void)size;
}

void rhi_cmd_set_uniform_i32(RHICmdBuffer *cmd, i32 location, i32 v) {
    (void)cmd;
    if (location >= 0) glUniform1i(location, v);
}

i32 rhi_pipeline_get_uniform_location(RHIDevice *dev, RHIPipeline pipe, const char *name) {
    GLPipelineData *pd = (GLPipelineData *)rhi_get_resource(dev, pipe);
    if (!pd) return -1;
    return (i32)glGetUniformLocation(pd->gl_program, name);
}

RHIShadowMap rhi_shadow_map_create(RHIDevice *dev, u32 width, u32 height) {
    RHIShadowMap sm = {0};
    sm.width = width;
    sm.height = height;

    RHITextureDesc tdesc = {
        .width  = width,
        .height = height,
        .format = RHI_FORMAT_D32_FLOAT,
        .mip_levels = 1,
        .data   = NULL,
    };
    sm.depth_tex = rhi_texture_create(dev, &tdesc);
    if (!rhi_handle_valid(sm.depth_tex)) return sm;

    GLTextureData *td = (GLTextureData *)rhi_get_resource(dev, sm.depth_tex);
    glBindTexture(GL_TEXTURE_2D, td->gl_tex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    f32 border[] = {1.0f, 1.0f, 1.0f, 1.0f};
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, border);
    glBindTexture(GL_TEXTURE_2D, 0);

    GLuint gl_fbo = 0;
    glGenFramebuffers(1, &gl_fbo);
    gl_bind_fbo_cached(gl_fbo);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, td->gl_tex, 0);
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);
    gl_bind_fbo_cached(0);

    GLFBOData *fd = calloc(1, sizeof(GLFBOData));
    if (!fd) { glDeleteFramebuffers(1, &gl_fbo); sm.fbo = RHI_HANDLE_NULL; return sm; }
    u32 idx = rhi_alloc_slot(dev);
    fd->gl_fbo = gl_fbo;
    dev->slots[idx].ptr  = fd;
    dev->slots[idx].type = RHI_RES_FRAMEBUFFER;
    sm.fbo = rhi_make_handle(idx, dev->slots[idx].generation);

    return sm;
}

void rhi_shadow_map_destroy(RHIDevice *dev, RHIShadowMap *sm) {
    if (!sm) return;
    if (rhi_handle_valid(sm->depth_tex)) rhi_texture_destroy(dev, sm->depth_tex);
    if (rhi_handle_valid(sm->fbo)) {
        GLFBOData *fd = (GLFBOData *)rhi_get_resource(dev, sm->fbo);
        if (fd) { glDeleteFramebuffers(1, &fd->gl_fbo); }
        rhi_free_slot(dev, sm->fbo);
    }
    sm->fbo = RHI_HANDLE_NULL;
    sm->depth_tex = RHI_HANDLE_NULL;
}

void rhi_cmd_bind_shadow_map(RHICmdBuffer *cmd, RHIShadowMap *sm) {
    (void)cmd;
    GLFBOData *fd = (GLFBOData *)rhi_get_resource(g_current_device, sm->fbo);
    if (fd) gl_bind_fbo_cached(fd->gl_fbo);
    /* Clear the whole atlas once with scissor disabled; per-cascade quadrant
     * scissoring is applied afterwards via rhi_cmd_set_shadow_viewport. */
    if (g_gl_scissor_enabled) { glDisable(GL_SCISSOR_TEST); g_gl_scissor_enabled = false; }
    gl_set_viewport_cached(0, 0, sm->width, sm->height);
    glClear(GL_DEPTH_BUFFER_BIT);
}

void rhi_cmd_unbind_shadow_map(RHICmdBuffer *cmd, u32 screen_w, u32 screen_h) {
    (void)cmd;
    if (g_gl_scissor_enabled) { glDisable(GL_SCISSOR_TEST); g_gl_scissor_enabled = false; }
    gl_bind_fbo_cached(0);
    gl_set_viewport_cached(0, 0, (GLsizei)screen_w, (GLsizei)screen_h);
}

void rhi_cmd_clear_depth(RHICmdBuffer *cmd) {
    (void)cmd;
    glClear(GL_DEPTH_BUFFER_BIT);
}

static const GLenum GL_CUBE_FACES[6] = {
    GL_TEXTURE_CUBE_MAP_POSITIVE_X,
    GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
    GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
    GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
    GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
    GL_TEXTURE_CUBE_MAP_NEGATIVE_Z,
};

RHICubemap rhi_cubemap_create(RHIDevice *dev, const RHICubemapDesc *desc) {
    GLuint gl_tex = 0;
    glGenTextures(1, &gl_tex);
    glBindTexture(GL_TEXTURE_CUBE_MAP, gl_tex);

    GLenum internal = rhi_format_to_gl_internal(desc->format);
    GLenum upload_fmt = rhi_format_to_gl_format(desc->format);
    bool hdr = (desc->format == RHI_FORMAT_R16G16B16A16_SFLOAT);
    GLenum upload_type = hdr ? GL_FLOAT : GL_UNSIGNED_BYTE;
    u32 mips = desc->mip_levels ? desc->mip_levels : 1u;

    for (u32 m = 0; m < mips; m++) {
        u32 msz = desc->size >> m; if (msz == 0u) msz = 1u;
        for (u32 i = 0; i < 6; i++) {
            /* Only upload mip 0 face data; higher mips (and HDR float faces with
             * RGBA8 source data) are allocated empty and filled by compute. */
            const void *data = (m == 0u && !hdr) ? desc->faces[i] : NULL;
            glTexImage2D(GL_CUBE_FACES[i], (GLint)m, (GLint)internal,
                         (GLsizei)msz, (GLsizei)msz, 0,
                         upload_fmt, upload_type, data);
        }
    }

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER,
                    mips > 1u ? GL_LINEAR_MIPMAP_LINEAR : GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

    GLTextureData *td = calloc(1, sizeof(GLTextureData));
    if (!td) { glDeleteTextures(1, &gl_tex); return RHI_HANDLE_NULL; }
    u32 idx = rhi_alloc_slot(dev);
    td->gl_tex            = gl_tex;
    td->width             = desc->size;
    td->height            = desc->size;
    td->gl_internal_format = internal;
    dev->slots[idx].ptr   = td;
    dev->slots[idx].type  = RHI_RES_CUBEMAP;
    return rhi_make_handle(idx, dev->slots[idx].generation);
}

void rhi_cubemap_transition_to_read(RHIDevice *dev, RHICubemap cm) {
    /* GL has no explicit image layouts; ensure compute image writes are visible
     * to subsequent texture sampling. */
    (void)dev; (void)cm;
    glMemoryBarrier(GL_TEXTURE_FETCH_BARRIER_BIT | GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);
}

void rhi_texture_transition_to_read(RHIDevice *dev, RHITexture tex) {
    (void)dev; (void)tex;
    glMemoryBarrier(GL_TEXTURE_FETCH_BARRIER_BIT | GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);
}

void rhi_cubemap_destroy(RHIDevice *dev, RHICubemap cm) {
    GLTextureData *td = (GLTextureData *)rhi_get_resource(dev, cm);
    if (!td) return;
    /* R106-2: Invalidate cache entries — same as rhi_texture_destroy. */
    for (u32 i = 0; i < 16; i++) {
        if (g_tex_cache[i] == td->gl_tex) g_tex_cache[i] = 0;
    }
    glDeleteTextures(1, &td->gl_tex);
    free(td);
    rhi_free_slot(dev, cm);
}

void rhi_cmd_bind_cubemap(RHICmdBuffer *cmd, RHICubemap cm, RHISampler sampler, u32 unit) {
    (void)cmd;
    /* R78-1: Route through gl_bind_tex_unit — handles cubemap target detection
     * via RHI_RES_CUBEMAP slot type and updates the file-scope texture cache.
     * Previously called glActiveTexture + glBindTexture + glBindSampler directly,
     * leaving g_active_unit/g_tex_cache/g_sam_cache stale — same class of bug
     * as R77-1 fixed for rhi_cmd_bind_texel_buffers and rhi_cmd_bind_texture_mip.
     * This was a regression: R77-1 made rhi_cmd_bind_texel_buffers trust
     * g_active_unit, but cubemap bypass could leave it stale, causing TBO
     * to bind to the wrong texture unit. */
    gl_bind_tex_unit(unit, cm, sampler);
}

/* Cached GL depth function: skip redundant glDepthFunc calls */
static GLenum g_gl_depth_func = GL_LESS;

void rhi_cmd_set_depth_func_less_or_equal(RHICmdBuffer *cmd) {
    (void)cmd;
    if (g_gl_depth_func != GL_LEQUAL) {
        glDepthFunc(GL_LEQUAL);
        g_gl_depth_func = GL_LEQUAL;
    }
}

void rhi_cmd_set_depth_func_less(RHICmdBuffer *cmd) {
    (void)cmd;
    if (g_gl_depth_func != GL_LESS) {
        glDepthFunc(GL_LESS);
        g_gl_depth_func = GL_LESS;
    }
}

/* R80-2: Cached depth mask and cull-face enable — skybox_render previously
 * called glDepthMask/glEnable/glDisable directly, bypassing caches. */
void rhi_cmd_set_depth_mask(RHICmdBuffer *cmd, bool enabled) {
    (void)cmd;
    if (g_gl_depth_mask != enabled) {
        glDepthMask(enabled ? GL_TRUE : GL_FALSE);
        g_gl_depth_mask = enabled;
    }
}

void rhi_cmd_set_cull_face(RHICmdBuffer *cmd, bool enabled) {
    (void)cmd;
    if (g_gl_cull_enabled != enabled) {
        if (enabled) glEnable(GL_CULL_FACE);
        else glDisable(GL_CULL_FACE);
        g_gl_cull_enabled = enabled;
    }
}

/* Cached GL_ARRAY_BUFFER binding: eliminates redundant glBindBuffer calls
 * when multiple consecutive updates target different buffers. */
static GLuint g_gl_bound_array_buffer = 0;

static inline void gl_bind_array_buffer_cached(GLuint buf) {
    if (buf != g_gl_bound_array_buffer) {
        glBindBuffer(GL_ARRAY_BUFFER, buf);
        g_gl_bound_array_buffer = buf;
    }
}

void rhi_buffer_update(RHIDevice *dev, RHIBuffer buf, const void *data, usize size) {
    GLBufferData *bd = (GLBufferData *)rhi_get_resource(dev, buf);
    if (!bd) return;
    gl_bind_array_buffer_cached(bd->gl_buf);
    glBufferSubData(GL_ARRAY_BUFFER, 0, (GLsizeiptr)size, data);
}

void rhi_buffer_update_region(RHIDevice *dev, RHIBuffer buf, usize offset, const void *data, usize size) {
    GLBufferData *bd = (GLBufferData *)rhi_get_resource(dev, buf);
    if (!bd) return;
    gl_bind_array_buffer_cached(bd->gl_buf);
    glBufferSubData(GL_ARRAY_BUFFER, (GLintptr)offset, (GLsizeiptr)size, data);
}

void* rhi_buffer_map(RHIDevice *dev, RHIBuffer buf) {
    GLBufferData *bd = (GLBufferData *)rhi_get_resource(dev, buf);
    if (!bd) return NULL;
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, bd->gl_buf);
    /* R79-3: Removed trailing unbind — next glBindBuffer/glBindBufferBase
     * will overwrite the generic binding point. Same pattern as R77-2. */
    void *ptr = glMapBufferRange(GL_SHADER_STORAGE_BUFFER, 0, bd->size, GL_MAP_READ_BIT);
    return ptr;
}

void rhi_buffer_unmap(RHIDevice *dev, RHIBuffer buf) {
    GLBufferData *bd = (GLBufferData *)rhi_get_resource(dev, buf);
    if (!bd) return;
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, bd->gl_buf);
    /* R79-3: Removed trailing unbind — same pattern as R77-2. */
    glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);
}

/* R87-1: GPU-side buffer copy (non-blocking, avoids glMapBufferRange stall). */
void rhi_cmd_copy_buffer(RHICmdBuffer *cmd, RHIBuffer src, RHIBuffer dst, usize size) {
    (void)cmd;
    if (size == 0u) return;
    extern RHIDevice *g_current_device;
    GLBufferData *src_bd = (GLBufferData *)rhi_get_resource(g_current_device, src);
    GLBufferData *dst_bd = (GLBufferData *)rhi_get_resource(g_current_device, dst);
    if (!src_bd || !dst_bd) return;
    /* R177: Ensure prior SSBO writes are visible to COPY_READ. */
    glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT | GL_BUFFER_UPDATE_BARRIER_BIT);
    glBindBuffer(GL_COPY_READ_BUFFER, src_bd->gl_buf);
    glBindBuffer(GL_COPY_WRITE_BUFFER, dst_bd->gl_buf);
    glCopyBufferSubData(GL_COPY_READ_BUFFER, GL_COPY_WRITE_BUFFER, 0, 0, (GLsizeiptr)size);
}

/* R171: Recorded clear ordered with subsequent compute/indirect in the GL stream. */
void rhi_cmd_fill_buffer(RHICmdBuffer *cmd, RHIBuffer buf, usize offset, usize size, u32 value) {
    (void)cmd;
    if (size == 0u) return;
    extern RHIDevice *g_current_device;
    GLBufferData *bd = (GLBufferData *)rhi_get_resource(g_current_device, buf);
    if (!bd) return;
    /* R185: Wait prior indirect/SSBO reads before clearing (cascade reuse). */
    glMemoryBarrier(GL_COMMAND_BARRIER_BIT | GL_SHADER_STORAGE_BARRIER_BIT
                    | GL_BUFFER_UPDATE_BARRIER_BIT);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, bd->gl_buf);
    glClearBufferSubData(GL_SHADER_STORAGE_BUFFER, GL_R32UI,
                         (GLintptr)offset, (GLsizeiptr)size,
                         GL_RED_INTEGER, GL_UNSIGNED_INT, &value);
    /* R175: Clear is incoherent w.r.t. SSBO/indirect; barrier before compute/draw. */
    glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT | GL_COMMAND_BARRIER_BIT
                    | GL_BUFFER_UPDATE_BARRIER_BIT);
}

void rhi_cmd_update_buffer(RHICmdBuffer *cmd, RHIBuffer buf, usize offset,
                           const void *data, usize size) {
    (void)cmd;
    if (!data || size == 0u) return;
    extern RHIDevice *g_current_device;
    GLBufferData *bd = (GLBufferData *)rhi_get_resource(g_current_device, buf);
    if (!bd) return;
    if (offset + size > bd->size) {
        if (offset >= bd->size) return;
        size = bd->size - offset;
    }
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, bd->gl_buf);
    glBufferSubData(GL_SHADER_STORAGE_BUFFER, (GLintptr)offset, (GLsizeiptr)size, data);
    glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT | GL_COMMAND_BARRIER_BIT
                    | GL_BUFFER_UPDATE_BARRIER_BIT);
}

void rhi_cmd_bind_texel_buffers(RHICmdBuffer *cmd, RHIBuffer buf0, RHIBuffer buf1) {
    (void)cmd;
    extern RHIDevice *g_current_device;
    GLBufferData *bd0 = (GLBufferData *)rhi_get_resource(g_current_device, buf0);
    GLBufferData *bd1 = (GLBufferData *)rhi_get_resource(g_current_device, buf1);
    /* R77-1: Route through the file-scope texture cache — previously called
     * glActiveTexture + glBindTexture directly, leaving g_active_unit and
     * g_tex_cache[5/6] stale. This caused gl_bind_tex_unit to skip
     * glActiveTexture on the next call (false cache hit), binding textures
     * to the wrong unit. */
    if (bd0 && bd0->tbo_tex) {
        if (g_active_unit != 5) { glActiveTexture(GL_TEXTURE5); g_active_unit = 5; }
        if (g_tex_cache[5] != bd0->tbo_tex) {
            glBindTexture(GL_TEXTURE_BUFFER, bd0->tbo_tex);
            g_tex_cache[5] = bd0->tbo_tex;
        }
    }
    if (bd1 && bd1->tbo_tex) {
        if (g_active_unit != 6) { glActiveTexture(GL_TEXTURE6); g_active_unit = 6; }
        if (g_tex_cache[6] != bd1->tbo_tex) {
            glBindTexture(GL_TEXTURE_BUFFER, bd1->tbo_tex);
            g_tex_cache[6] = bd1->tbo_tex;
        }
    }
}

RHIOffscreenFBO rhi_offscreen_fbo_create_fmt(RHIDevice *dev, u32 width, u32 height, RHIFormat color_fmt) {
    (void)dev;
    RHIOffscreenFBO fbo = {0};
    fbo.width = width;
    fbo.height = height;

    GLFBOData *fd = calloc(1, sizeof(GLFBOData));
    if (!fd) return fbo;

    GLenum gl_internal = rhi_format_to_gl_internal(color_fmt);
    GLenum gl_format = rhi_format_to_gl_format(color_fmt);
    GLenum gl_type = (color_fmt == RHI_FORMAT_D32_FLOAT || color_fmt == RHI_FORMAT_R16G16B16A16_SFLOAT) ? GL_FLOAT : GL_UNSIGNED_BYTE;

    glGenFramebuffers(1, &fd->gl_fbo);
    gl_bind_fbo_cached(fd->gl_fbo);

    glGenTextures(1, &fd->color_tex);
    glBindTexture(GL_TEXTURE_2D, fd->color_tex);
    glTexImage2D(GL_TEXTURE_2D, 0, gl_internal, width, height, 0, gl_format, gl_type, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, fd->color_tex, 0);

    glGenRenderbuffers(1, &fd->depth_rb);
    glBindRenderbuffer(GL_RENDERBUFFER, fd->depth_rb);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, width, height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, fd->depth_rb);

    gl_bind_fbo_cached(0);

    u32 tidx = rhi_alloc_slot(dev);
    dev->slots[tidx].ptr = fd;
    dev->slots[tidx].type = RHI_RES_FRAMEBUFFER;

    u32 cidx = rhi_alloc_slot(dev);
    dev->slots[cidx].ptr = fd;
    dev->slots[cidx].type = RHI_RES_TEXTURE;

    fbo.fb = rhi_make_handle(tidx, dev->slots[tidx].generation);
    fbo.color_tex = rhi_make_handle(cidx, dev->slots[cidx].generation);

    return fbo;
}

RHIOffscreenFBO rhi_offscreen_fbo_create(RHIDevice *dev, u32 width, u32 height) {
    return rhi_offscreen_fbo_create_fmt(dev, width, height, RHI_FORMAT_R8G8B8A8_UNORM);
}

void rhi_offscreen_fbo_destroy(RHIDevice *dev, RHIOffscreenFBO *fbo) {
    if (!dev || !fbo) return;
    GLFBOData *fd = rhi_get_resource(dev, fbo->fb);
    if (!fd) return;
    glDeleteFramebuffers(1, &fd->gl_fbo);
    glDeleteTextures(1, &fd->color_tex);
    glDeleteRenderbuffers(1, &fd->depth_rb);
    free(fd);
    rhi_free_slot(dev, fbo->fb);
    rhi_free_slot(dev, fbo->color_tex);
    memset(fbo, 0, sizeof(*fbo));
}

void rhi_offscreen_fbo_bind(RHICmdBuffer *cmd, RHIOffscreenFBO *fbo) {
    (void)cmd;
    if (!fbo) return;
    GLFBOData *fd = rhi_get_resource(g_current_device, fbo->fb);
    if (!fd) return;
    gl_bind_fbo_cached(fd->gl_fbo);
    gl_set_viewport_cached(0, 0, fbo->width, fbo->height);
}

void rhi_offscreen_fbo_unbind(RHICmdBuffer *cmd, u32 screen_w, u32 screen_h) {
    (void)cmd;
    gl_bind_fbo_cached(0);
    gl_set_viewport_cached(0, 0, screen_w, screen_h);
}

void rhi_cmd_dispatch(RHICmdBuffer *cmd, u32 x, u32 y, u32 z) {
    (void)cmd;
    glDispatchCompute(x, y, z);
}

void rhi_cmd_bind_storage_buffer(RHICmdBuffer *cmd, RHIBuffer buf, u32 binding) {
    (void)cmd;
    extern RHIDevice *g_current_device;
    GLBufferData *bd = (GLBufferData *)rhi_get_resource(g_current_device, buf);
    /* R106-2: SSBO cache promoted to file scope for invalidation on destroy. */
    if (bd && binding < 8) {
        if (g_gl_ssbo_cache[binding] != bd->gl_buf) {
            glBindBufferBase(GL_SHADER_STORAGE_BUFFER, binding, bd->gl_buf);
            g_gl_ssbo_cache[binding] = bd->gl_buf;
        }
    } else if (bd) {
        glBindBufferBase(GL_SHADER_STORAGE_BUFFER, binding, bd->gl_buf);
    }
}

void rhi_cmd_memory_barrier(RHICmdBuffer *cmd) {
    (void)cmd;
    /* R168-B: Include COMMAND_BARRIER so compute writes to DrawIndirect /
     * DrawElementsIndirect buffers are visible to subsequent indirect draws.
     * R170: BUFFER_UPDATE so compute→copy_buffer (vis_flags staging) is ordered. */
    glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT | GL_SHADER_IMAGE_ACCESS_BARRIER_BIT
                    | GL_TEXTURE_FETCH_BARRIER_BIT | GL_COMMAND_BARRIER_BIT
                    | GL_BUFFER_UPDATE_BARRIER_BIT);
}

void rhi_cmd_bind_image_texture(RHICmdBuffer *cmd, RHITexture tex, u32 unit, u32 mip_level, bool write_only) {
    (void)cmd;
    GLTextureData *td = (GLTextureData *)rhi_get_resource(g_current_device, tex);
    if (!td) return;
    GLenum access = write_only ? GL_WRITE_ONLY : GL_READ_WRITE;
    /* Use recorded format; fall back to GL_RGBA16F for untracked textures. */
    GLenum fmt = td->gl_internal_format ? td->gl_internal_format : GL_RGBA16F;
    glBindImageTexture(unit, td->gl_tex, (GLint)mip_level, GL_FALSE, 0, access, fmt);
}

void rhi_cmd_bind_image_cubemap_face(RHICmdBuffer *cmd, RHICubemap cm, u32 face, u32 mip, u32 unit, bool write_only) {
    (void)cmd;
    GLTextureData *td = (GLTextureData *)rhi_get_resource(g_current_device, cm);
    if (!td || face >= 6u) return;
    GLenum access = write_only ? GL_WRITE_ONLY : GL_READ_WRITE;
    GLenum fmt = td->gl_internal_format ? td->gl_internal_format : GL_RGBA8;
    /* Bind a single face (layer) of the cubemap mip as an image. */
    glBindImageTexture(unit, td->gl_tex, (GLint)mip, GL_FALSE, (GLint)face, access, fmt);
}

void rhi_cmd_bind_cubemap_sampler(RHICmdBuffer *cmd, RHICubemap cm, RHISampler sampler, u32 unit) {
    /* GL: same as rhi_cmd_bind_cubemap — texture units are shared between
     * compute and graphics stages. */
    rhi_cmd_bind_cubemap(cmd, cm, sampler, unit);
}

void rhi_cmd_bind_texture_mip(RHICmdBuffer *cmd, RHITexture tex, RHISampler sampler, u32 unit, u32 mip_level) {
    (void)cmd;
    GLTextureData *td = (GLTextureData *)rhi_get_resource(g_current_device, tex);
    if (!td) return;
    /* R77-1: Use gl_bind_tex_unit for texture/sampler binding (updates cache).
     * Previously called glActiveTexture + glBindTexture directly, leaving
     * g_active_unit and g_tex_cache[unit] stale. */
    gl_bind_tex_unit(unit, tex, sampler);
    /* Only update mip clamps if the level changed for this texture. */
    static GLuint s_mip_tex = 0;
    static GLint  s_mip_level = -1;
    if (s_mip_tex != td->gl_tex || s_mip_level != (GLint)mip_level) {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, (GLint)mip_level);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, (GLint)mip_level);
        s_mip_tex = td->gl_tex;
        s_mip_level = (GLint)mip_level;
    }
}

void rhi_cmd_bind_texture_compute(RHICmdBuffer *cmd, RHITexture tex, RHISampler sampler, u32 unit) {
    (void)cmd;
    gl_bind_tex_unit(unit, tex, sampler);
}

void rhi_cmd_transition_depth_to_read(RHICmdBuffer *cmd, RHITexture depth_tex) {
    /* GL has no explicit image layouts; FBO depth -> texture sampling hazards
     * are resolved implicitly by the driver between draw calls. This is the GL
     * analogue of the Vulkan layout transition and is intentionally a no-op. */
    (void)cmd; (void)depth_tex;
}

void rhi_screenshot(RHIDevice *dev, u32 x, u32 y, u32 w, u32 h, u8 *pixels) {
    (void)dev;
    glReadPixels((GLint)x, (GLint)y, (GLint)w, (GLint)h, GL_RGB, GL_UNSIGNED_BYTE, pixels);
}

struct RHIGPUTimer {
    GLuint queries[2];
    bool   started;
    bool   result_ready;
};

RHIGPUTimer *rhi_gpu_timer_create(RHIDevice *dev) {
    (void)dev;
    RHIGPUTimer *t = calloc(1, sizeof(RHIGPUTimer));
    if (!t) return NULL;
    glGenQueries(2, t->queries);
    return t;
}

void rhi_gpu_timer_destroy(RHIDevice *dev, RHIGPUTimer *t) {
    (void)dev;
    if (!t) return;
    glDeleteQueries(2, t->queries);
    free(t);
}

void rhi_gpu_timer_begin(RHIGPUTimer *t) {
    if (!t) return;
    glQueryCounter(t->queries[0], GL_TIMESTAMP);
    t->started = true;
}

void rhi_gpu_timer_end(RHIGPUTimer *t) {
    if (!t || !t->started) return;
    glQueryCounter(t->queries[1], GL_TIMESTAMP);
    t->result_ready = true;
    t->started = false;
}

f64 rhi_gpu_timer_elapsed_ms(RHIGPUTimer *t) {
    if (!t || !t->result_ready) return 0.0;
    GLuint64 start_ns = 0, end_ns = 0;
    glGetQueryObjectui64v(t->queries[0], GL_QUERY_RESULT, &start_ns);
    glGetQueryObjectui64v(t->queries[1], GL_QUERY_RESULT, &end_ns);
    t->result_ready = false;
    return (f64)(end_ns - start_ns) / 1e6;
}

/* ======================================================================== */
/* MRT (Multiple Render Targets) framebuffer -- GL backend                  */
/* ======================================================================== */

RHIMRTFBO rhi_mrt_fbo_create(RHIDevice *dev, u32 width, u32 height,
                              const RHIFormat *formats, u32 attachment_count) {
    RHIMRTFBO fbo = {0};
    if (attachment_count == 0u || attachment_count > RHI_MRT_MAX_ATTACHMENTS) return fbo;
    fbo.attachment_count = attachment_count;
    fbo.width  = width;
    fbo.height = height;

    GLMRTFBOData *md = calloc(1, sizeof(GLMRTFBOData));
    if (!md) return fbo;
    md->attachment_count = attachment_count;

    glGenFramebuffers(1, &md->gl_fbo);
    gl_bind_fbo_cached(md->gl_fbo);

    GLenum draw_bufs[RHI_MRT_MAX_ATTACHMENTS];
    for (u32 i = 0; i < attachment_count; i++) {
        GLenum internal_fmt = rhi_format_to_gl_internal(formats[i]);
        GLenum gl_fmt       = rhi_format_to_gl_format(formats[i]);
        GLenum gl_type       = (formats[i] == RHI_FORMAT_R16G16B16A16_SFLOAT) ? GL_FLOAT : GL_UNSIGNED_BYTE;

        glGenTextures(1, &md->color_tex[i]);
        glBindTexture(GL_TEXTURE_2D, md->color_tex[i]);
        glTexImage2D(GL_TEXTURE_2D, 0, internal_fmt, width, height, 0, gl_fmt, gl_type, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i,
                               GL_TEXTURE_2D, md->color_tex[i], 0);
        draw_bufs[i] = GL_COLOR_ATTACHMENT0 + i;
    }
    glDrawBuffers((GLsizei)attachment_count, draw_bufs);

    /* Shared depth attachment (texture — readable in deferred lighting pass). */
    glGenTextures(1, &md->depth_tex);
    glBindTexture(GL_TEXTURE_2D, md->depth_tex);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32F,
                 (GLsizei)width, (GLsizei)height, 0,
                 GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,
                           GL_TEXTURE_2D, md->depth_tex, 0);

    gl_bind_fbo_cached(0);

    /* Register FBO handle. */
    u32 fidx = rhi_alloc_slot(dev);
    dev->slots[fidx].ptr  = md;
    dev->slots[fidx].type = RHI_RES_MRT_FBO;
    fbo.fb = rhi_make_handle(fidx, dev->slots[fidx].generation);

    /* Register each color texture as a separate texture handle. */
    for (u32 i = 0; i < attachment_count; i++) {
        GLTextureData *td = calloc(1, sizeof(GLTextureData));
        if (!td) return fbo;
        u32 cidx = rhi_alloc_slot(dev);
        td->gl_tex            = md->color_tex[i];
        td->width             = width;
        td->height            = height;
        td->gl_internal_format = rhi_format_to_gl_internal(formats[i]);
        dev->slots[cidx].ptr  = td;
        dev->slots[cidx].type = RHI_RES_TEXTURE;
        fbo.color_tex[i] = rhi_make_handle(cidx, dev->slots[cidx].generation);
    }

    /* Register depth as a texture handle (readable for deferred lighting). */
    if (md->depth_tex) {
        GLTextureData *dtd = calloc(1, sizeof(GLTextureData));
        if (!dtd) return fbo;
        u32 didx = rhi_alloc_slot(dev);
        dtd->gl_tex            = md->depth_tex;
        dtd->width             = width;
        dtd->height            = height;
        dtd->gl_internal_format = GL_DEPTH_COMPONENT32F;
        dev->slots[didx].ptr   = dtd;
        dev->slots[didx].type  = RHI_RES_TEXTURE;
        fbo.depth_tex = rhi_make_handle(didx, dev->slots[didx].generation);
    } else {
        fbo.depth_tex = RHI_HANDLE_NULL;
    }

    return fbo;
}

void rhi_mrt_fbo_destroy(RHIDevice *dev, RHIMRTFBO *fbo) {
    if (!dev || !fbo) return;
    GLMRTFBOData *md = (GLMRTFBOData *)rhi_get_resource(dev, fbo->fb);
    if (!md) { memset(fbo, 0, sizeof(*fbo)); return; }
    glDeleteFramebuffers(1, &md->gl_fbo);
    for (u32 i = 0; i < md->attachment_count; i++) {
        if (md->color_tex[i]) glDeleteTextures(1, &md->color_tex[i]);
        /* The texture slot shares the same GLTextureData pointer; null it
         * out so device-destroy skips the double-free. */
        if (rhi_handle_valid(fbo->color_tex[i])) {
            GLTextureData *td = (GLTextureData *)rhi_get_resource(dev, fbo->color_tex[i]);
            if (td) { free(td); }
            if (dev->slots[fbo->color_tex[i].index].ptr == td) {
                dev->slots[fbo->color_tex[i].index].ptr = NULL;
            }
            rhi_free_slot(dev, fbo->color_tex[i]);
        }
    }
    /* Depth texture is shared with the texture slot; clean up carefully. */
    if (rhi_handle_valid(fbo->depth_tex)) {
        GLTextureData *dtd = (GLTextureData *)rhi_get_resource(dev, fbo->depth_tex);
        if (dtd) { free(dtd); }
        if (dev->slots[fbo->depth_tex.index].ptr == dtd) {
            dev->slots[fbo->depth_tex.index].ptr = NULL;
        }
        rhi_free_slot(dev, fbo->depth_tex);
    } else if (md->depth_rb) {
        glDeleteRenderbuffers(1, &md->depth_rb);
    }
    if (md->depth_tex) glDeleteTextures(1, &md->depth_tex);
    free(md);
    rhi_free_slot(dev, fbo->fb);
    memset(fbo, 0, sizeof(*fbo));
}

void rhi_mrt_fbo_bind(RHICmdBuffer *cmd, RHIMRTFBO *fbo) {
    (void)cmd;
    if (!fbo) return;
    GLMRTFBOData *md = (GLMRTFBOData *)rhi_get_resource(g_current_device, fbo->fb);
    if (!md) return;
    gl_bind_fbo_cached(md->gl_fbo);
    gl_set_viewport_cached(0, 0, fbo->width, fbo->height);
}

void rhi_mrt_fbo_unbind(RHICmdBuffer *cmd, u32 screen_w, u32 screen_h) {
    (void)cmd;
    gl_bind_fbo_cached(0);
    gl_set_viewport_cached(0, 0, (GLsizei)screen_w, (GLsizei)screen_h);
}

/* ======================================================================== */
/* Depth cubemap FBO (point-light shadow maps) -- GL backend                */
/* ======================================================================== */

RHICubemapDepthFBO rhi_cubemap_depth_fbo_create(RHIDevice *dev, u32 size) {
    RHICubemapDepthFBO fbo = {0};
    fbo.size = size;

    GLCubemapDepthFBOData *cd = calloc(1, sizeof(GLCubemapDepthFBOData));
    if (!cd) return fbo;
    glGenTextures(1, &cd->depth_tex);
    glBindTexture(GL_TEXTURE_CUBE_MAP, cd->depth_tex);
    for (u32 face = 0; face < 6; face++) {
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + face, 0,
                     GL_DEPTH_COMPONENT24, (GLsizei)size, (GLsizei)size,
                     0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    /* Enable depth comparison for shadow sampling. */
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_REF_TO_TEXTURE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);
    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

    /* Create FBO (face attachments are set dynamically per-face). */
    glGenFramebuffers(1, &cd->gl_fbo);
    /* Set draw/read buffer once at creation time (depth-only, no color). */
    gl_bind_fbo_cached(cd->gl_fbo);
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);
    gl_bind_fbo_cached(0);

    /* Register depth texture handle. */
    GLTextureData *td = calloc(1, sizeof(GLTextureData));
    if (!td) return fbo;
    u32 tidx = rhi_alloc_slot(dev);
    td->gl_tex            = cd->depth_tex;
    td->width             = size;
    td->height            = size;
    td->gl_internal_format = GL_DEPTH_COMPONENT32F;
    dev->slots[tidx].ptr  = td;
    /* Tag as cubemap so gl_bind_tex_unit binds GL_TEXTURE_CUBE_MAP for the
     * point-shadow depth cube (sampled as samplerCubeShadow). */
    dev->slots[tidx].type = RHI_RES_CUBEMAP;
    fbo.depth_tex = rhi_make_handle(tidx, dev->slots[tidx].generation);

    /* Register FBO handle. */
    u32 fidx = rhi_alloc_slot(dev);
    dev->slots[fidx].ptr  = cd;
    dev->slots[fidx].type = RHI_RES_CUBEMAP_DEPTH_FBO;
    fbo.fb = rhi_make_handle(fidx, dev->slots[fidx].generation);

    return fbo;
}

void rhi_cubemap_depth_fbo_destroy(RHIDevice *dev, RHICubemapDepthFBO *fbo) {
    if (!dev || !fbo) return;
    GLCubemapDepthFBOData *cd = (GLCubemapDepthFBOData *)rhi_get_resource(dev, fbo->fb);
    if (!cd) { memset(fbo, 0, sizeof(*fbo)); return; }
    if (cd->gl_fbo) glDeleteFramebuffers(1, &cd->gl_fbo);
    /* depth_tex is freed via its own texture slot; just free the FBO here. */
    free(cd);
    rhi_free_slot(dev, fbo->fb);
    /* Caller is responsible for destroying the depth_tex handle separately
     * via rhi_texture_destroy if needed; for simplicity we also clean it. */
    if (rhi_handle_valid(fbo->depth_tex)) {
        GLTextureData *td = (GLTextureData *)rhi_get_resource(dev, fbo->depth_tex);
        if (td) { glDeleteTextures(1, &td->gl_tex); free(td); }
        rhi_free_slot(dev, fbo->depth_tex);
    }
    memset(fbo, 0, sizeof(*fbo));
}

void rhi_cubemap_depth_fbo_bind_face(RHICmdBuffer *cmd, RHICubemapDepthFBO *fbo, u32 face) {
    (void)cmd;
    if (!fbo || face >= 6u) return;
    GLCubemapDepthFBOData *cd = (GLCubemapDepthFBOData *)rhi_get_resource(g_current_device, fbo->fb);
    if (!cd) return;
    gl_bind_fbo_cached(cd->gl_fbo);
    /* Attach the requested cubemap face as the depth attachment. */
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,
                           GL_TEXTURE_CUBE_MAP_POSITIVE_X + face, cd->depth_tex, 0);
    /* draw/read buffer set once at FBO creation (depth-only) */
    gl_set_viewport_cached(0, 0, (GLsizei)fbo->size, (GLsizei)fbo->size);
    glClear(GL_DEPTH_BUFFER_BIT);
}

void rhi_cubemap_depth_fbo_unbind(RHICmdBuffer *cmd, u32 screen_w, u32 screen_h) {
    (void)cmd;
    gl_bind_fbo_cached(0);
    gl_set_viewport_cached(0, 0, (GLsizei)screen_w, (GLsizei)screen_h);
}
