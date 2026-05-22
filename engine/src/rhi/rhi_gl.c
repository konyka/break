#include <glad.h>
#include <GL/glx.h>
#include <X11/Xlib.h>

typedef struct {
    Display   *display;
    Window     window;
    GLXContext gl_ctx;
} GLBackend;

typedef struct {
    GLuint gl_vao;
    GLuint gl_vbo;
    GLuint gl_ibo;
    GLuint gl_program;
    u32    vertex_stride;
    bool   has_index;
    bool   alpha_blend;
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
} GLTextureData;

typedef struct {
    GLuint gl_sampler;
} GLSamplerData;

typedef struct {
    GLuint gl_fbo;
    GLuint color_tex;
    GLuint depth_rb;
} GLFBOData;

static bool gl_init(RHIDevice *dev, void *window_native, void *display_native, u32 w, u32 h) {
    GLBackend *gl = calloc(1, sizeof(GLBackend));
    if (!gl) return false;

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

    LOG_INFO("OpenGL %s initialized", (const char *)glGetString(GL_VERSION));
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glViewport(0, 0, w, h);

    dev->backend_data = gl;
    dev->width  = w;
    dev->height = h;
    return true;
}

static void gl_shutdown(RHIDevice *dev) {
    GLBackend *gl = (GLBackend *)dev->backend_data;
    if (!gl) return;
    glXMakeCurrent(gl->display, None, NULL);
    glXDestroyContext(gl->display, gl->gl_ctx);
    free(gl);
    dev->backend_data = NULL;
}

static void gl_resize(RHIDevice *dev, u32 w, u32 h) {
    glViewport(0, 0, w, h);
    dev->width  = w;
    dev->height = h;
}

static void *gl_frame_begin(RHIDevice *dev) {
    (void)dev;
    return NULL;
}

static void gl_frame_end(RHIDevice *dev) {
    (void)dev;
}

static void gl_present(RHIDevice *dev) {
    GLBackend *gl = (GLBackend *)dev->backend_data;
    glXSwapBuffers(gl->display, gl->window);
}

static void gl_cmd_begin_render_pass(void *cmd) {
    (void)cmd;
}

static void gl_cmd_end_render_pass(void *cmd) {
    (void)cmd;
}

static void gl_cmd_bind_pipeline(void *cmd, GLPipelineData *pd) {
    (void)cmd;
    glUseProgram(pd->gl_program);
    glBindVertexArray(pd->gl_vao);
    if (pd->alpha_blend) {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    } else {
        glDisable(GL_BLEND);
    }
}

static void gl_cmd_set_viewport(void *cmd, f32 x, f32 y, f32 w, f32 h) {
    (void)cmd;
    glViewport((GLint)x, (GLint)y, (GLsizei)w, (GLsizei)h);
}

static void gl_cmd_draw(void *cmd, u32 vertex_count, u32 instance_count) {
    (void)cmd;
    glDrawArrays(GL_TRIANGLES, 0, (GLsizei)vertex_count);
    (void)instance_count;
}

static void gl_cmd_draw_indexed(void *cmd, u32 index_count, u32 instance_count) {
    (void)cmd;
    glDrawElements(GL_TRIANGLES, (GLsizei)index_count, GL_UNSIGNED_INT, NULL);
    (void)instance_count;
}

static void gl_cmd_clear_color(void *cmd, f32 r, f32 g, f32 b, f32 a) {
    (void)cmd;
    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}


RHIDevice *rhi_device_create(RHIBackend backend, void *window_native, void *display_native, u32 w, u32 h) {
    RHIDevice *dev = calloc(1, sizeof(RHIDevice));
    if (!dev) return NULL;

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

    u32 idx = rhi_alloc_slot(dev);
    GLShaderData *sd = calloc(1, sizeof(GLShaderData));
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
    u32 idx = rhi_alloc_slot(dev);
    GLShaderData *sd = calloc(1, sizeof(GLShaderData));
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

        u32 idx = rhi_alloc_slot(dev);
        GLPipelineData *pd = calloc(1, sizeof(GLPipelineData));
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

    u32 idx = rhi_alloc_slot(dev);
    GLPipelineData *pd = calloc(1, sizeof(GLPipelineData));
    pd->gl_program     = program;
    pd->gl_vao         = vao;
    pd->vertex_stride  = stride;
    pd->alpha_blend    = desc->alpha_blend;
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

    u32 idx = rhi_alloc_slot(dev);
    GLBufferData *bd = calloc(1, sizeof(GLBufferData));
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
    if (pd) gl_cmd_bind_pipeline(cmd, pd);
}

void rhi_cmd_bind_vertex_buffer(RHICmdBuffer *cmd, RHIBuffer buf, usize offset) {
    (void)cmd;
    extern RHIDevice *g_current_device;
    GLBufferData *bd = (GLBufferData *)rhi_get_resource(g_current_device, buf);
    if (bd) {
        GLuint vao = 0;
        glGetIntegerv(GL_VERTEX_ARRAY_BINDING, (GLint *)&vao);
        GLint bound_program = 0;
        glGetIntegerv(GL_CURRENT_PROGRAM, &bound_program);
        if (bound_program) {
            for (u32 i = 0; i < g_current_device->next_slot && i < 4096; i++) {
                if (g_current_device->slots[i].alive && g_current_device->slots[i].type == RHI_RES_PIPELINE) {
                    GLPipelineData *pd = (GLPipelineData *)g_current_device->slots[i].ptr;
                    if (pd && pd->gl_program == (GLuint)bound_program) {
                        glBindVertexBuffer(0, bd->gl_buf, (GLintptr)offset, (GLsizei)pd->vertex_stride);
                        return;
                    }
                }
            }
        }
        glBindVertexBuffer(0, bd->gl_buf, (GLintptr)offset, 8 * sizeof(f32));
    }
}

void rhi_cmd_bind_index_buffer(RHICmdBuffer *cmd, RHIBuffer buf, usize offset) {
    (void)cmd; (void)offset;
    extern RHIDevice *g_current_device;
    GLBufferData *bd = (GLBufferData *)rhi_get_resource(g_current_device, buf);
    if (bd) glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bd->gl_buf);
}

void rhi_cmd_set_viewport(RHICmdBuffer *cmd, f32 x, f32 y, f32 w, f32 h) {
    gl_cmd_set_viewport(cmd, x, y, w, h);
}

void rhi_cmd_set_scissor(RHICmdBuffer *cmd, i32 x, i32 y, u32 w, u32 h) {
    (void)cmd; (void)x; (void)y; (void)w; (void)h;
}

void rhi_cmd_draw(RHICmdBuffer *cmd, u32 vertex_count, u32 instance_count) {
    gl_cmd_draw(cmd, vertex_count, instance_count);
}

void rhi_cmd_draw_indexed(RHICmdBuffer *cmd, u32 index_count, u32 instance_count) {
    gl_cmd_draw_indexed(cmd, index_count, instance_count);
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

    u32 idx = rhi_alloc_slot(dev);
    GLTextureData *td = calloc(1, sizeof(GLTextureData));
    td->gl_tex = gl_tex;
    td->width  = desc->width;
    td->height = desc->height;
    dev->slots[idx].ptr  = td;
    dev->slots[idx].type = RHI_RES_TEXTURE;
    return rhi_make_handle(idx, dev->slots[idx].generation);
}

void rhi_texture_destroy(RHIDevice *dev, RHITexture tex) {
    GLTextureData *td = (GLTextureData *)rhi_get_resource(dev, tex);
    if (!td) return;
    glDeleteTextures(1, &td->gl_tex);
    free(td);
    rhi_free_slot(dev, tex);
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

    u32 idx = rhi_alloc_slot(dev);
    GLSamplerData *sd = calloc(1, sizeof(GLSamplerData));
    sd->gl_sampler = gl_samp;
    dev->slots[idx].ptr  = sd;
    dev->slots[idx].type = RHI_RES_SAMPLER;
    return rhi_make_handle(idx, dev->slots[idx].generation);
}

void rhi_sampler_destroy(RHIDevice *dev, RHISampler sampler) {
    GLSamplerData *sd = (GLSamplerData *)rhi_get_resource(dev, sampler);
    if (!sd) return;
    glDeleteSamplers(1, &sd->gl_sampler);
    free(sd);
    rhi_free_slot(dev, sampler);
}

static void gl_bind_tex_unit(u32 unit, RHITexture tex, RHISampler sampler) {
    extern RHIDevice *g_current_device;
    GLTextureData *td = (GLTextureData *)rhi_get_resource(g_current_device, tex);
    GLSamplerData *sd = (GLSamplerData *)rhi_get_resource(g_current_device, sampler);
    if (td) {
        glActiveTexture(GL_TEXTURE0 + unit);
        glBindTexture(GL_TEXTURE_2D, td->gl_tex);
    }
    if (sd) {
        glBindSampler(unit, sd->gl_sampler);
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
    glBindFramebuffer(GL_FRAMEBUFFER, gl_fbo);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, td->gl_tex, 0);
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    u32 idx = rhi_alloc_slot(dev);
    GLFBOData *fd = calloc(1, sizeof(GLFBOData));
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
    if (fd) glBindFramebuffer(GL_FRAMEBUFFER, fd->gl_fbo);
    glViewport(0, 0, sm->width, sm->height);
    glClear(GL_DEPTH_BUFFER_BIT);
}

void rhi_cmd_unbind_shadow_map(RHICmdBuffer *cmd, u32 screen_w, u32 screen_h) {
    (void)cmd;
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glViewport(0, 0, (GLsizei)screen_w, (GLsizei)screen_h);
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

    for (u32 i = 0; i < 6; i++) {
        glTexImage2D(GL_CUBE_FACES[i], 0, GL_RGBA8,
                     (GLsizei)desc->size, (GLsizei)desc->size, 0,
                     GL_RGBA, GL_UNSIGNED_BYTE, desc->faces[i]);
    }

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

    u32 idx = rhi_alloc_slot(dev);
    GLTextureData *td = calloc(1, sizeof(GLTextureData));
    td->gl_tex = gl_tex;
    td->width  = desc->size;
    td->height = desc->size;
    dev->slots[idx].ptr  = td;
    dev->slots[idx].type = RHI_RES_CUBEMAP;
    return rhi_make_handle(idx, dev->slots[idx].generation);
}

void rhi_cubemap_destroy(RHIDevice *dev, RHICubemap cm) {
    GLTextureData *td = (GLTextureData *)rhi_get_resource(dev, cm);
    if (!td) return;
    glDeleteTextures(1, &td->gl_tex);
    free(td);
    rhi_free_slot(dev, cm);
}

void rhi_cmd_bind_cubemap(RHICmdBuffer *cmd, RHICubemap cm, RHISampler sampler, u32 unit) {
    (void)cmd;
    extern RHIDevice *g_current_device;
    GLTextureData *td = (GLTextureData *)rhi_get_resource(g_current_device, cm);
    GLSamplerData *sd = (GLSamplerData *)rhi_get_resource(g_current_device, sampler);
    if (td) {
        glActiveTexture(GL_TEXTURE0 + unit);
        glBindTexture(GL_TEXTURE_CUBE_MAP, td->gl_tex);
    }
    if (sd) {
        glBindSampler(unit, sd->gl_sampler);
    }
}

void rhi_cmd_set_depth_func_less_or_equal(RHICmdBuffer *cmd) {
    (void)cmd;
    glDepthFunc(GL_LEQUAL);
}

void rhi_cmd_set_depth_func_less(RHICmdBuffer *cmd) {
    (void)cmd;
    glDepthFunc(GL_LESS);
}

void rhi_buffer_update(RHIDevice *dev, RHIBuffer buf, const void *data, usize size) {
    GLBufferData *bd = (GLBufferData *)rhi_get_resource(dev, buf);
    if (!bd) return;
    glBindBuffer(GL_ARRAY_BUFFER, bd->gl_buf);
    glBufferSubData(GL_ARRAY_BUFFER, 0, (GLsizeiptr)size, data);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void* rhi_buffer_map(RHIDevice *dev, RHIBuffer buf) {
    GLBufferData *bd = (GLBufferData *)rhi_get_resource(dev, buf);
    if (!bd) return NULL;
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, bd->gl_buf);
    void *ptr = glMapBufferRange(GL_SHADER_STORAGE_BUFFER, 0, bd->size, GL_MAP_READ_BIT);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
    return ptr;
}

void rhi_buffer_unmap(RHIDevice *dev, RHIBuffer buf) {
    GLBufferData *bd = (GLBufferData *)rhi_get_resource(dev, buf);
    if (!bd) return;
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, bd->gl_buf);
    glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
}

void rhi_cmd_bind_texel_buffers(RHICmdBuffer *cmd, RHIBuffer buf0, RHIBuffer buf1) {
    (void)cmd;
    extern RHIDevice *g_current_device;
    GLBufferData *bd0 = (GLBufferData *)rhi_get_resource(g_current_device, buf0);
    GLBufferData *bd1 = (GLBufferData *)rhi_get_resource(g_current_device, buf1);
    if (bd0 && bd0->tbo_tex) {
        glActiveTexture(GL_TEXTURE5);
        glBindTexture(GL_TEXTURE_BUFFER, bd0->tbo_tex);
    }
    if (bd1 && bd1->tbo_tex) {
        glActiveTexture(GL_TEXTURE6);
        glBindTexture(GL_TEXTURE_BUFFER, bd1->tbo_tex);
    }
}

RHIOffscreenFBO rhi_offscreen_fbo_create_fmt(RHIDevice *dev, u32 width, u32 height, RHIFormat color_fmt) {
    (void)dev;
    RHIOffscreenFBO fbo = {0};
    fbo.width = width;
    fbo.height = height;

    GLFBOData *fd = calloc(1, sizeof(GLFBOData));

    GLenum gl_internal = rhi_format_to_gl_internal(color_fmt);
    GLenum gl_format = rhi_format_to_gl_format(color_fmt);
    GLenum gl_type = (color_fmt == RHI_FORMAT_D32_FLOAT || color_fmt == RHI_FORMAT_R16G16B16A16_SFLOAT) ? GL_FLOAT : GL_UNSIGNED_BYTE;

    glGenFramebuffers(1, &fd->gl_fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, fd->gl_fbo);

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

    glBindFramebuffer(GL_FRAMEBUFFER, 0);

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
    glBindFramebuffer(GL_FRAMEBUFFER, fd->gl_fbo);
    glViewport(0, 0, fbo->width, fbo->height);
}

void rhi_offscreen_fbo_unbind(RHICmdBuffer *cmd, u32 screen_w, u32 screen_h) {
    (void)cmd;
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glViewport(0, 0, screen_w, screen_h);
}

void rhi_cmd_dispatch(RHICmdBuffer *cmd, u32 x, u32 y, u32 z) {
    (void)cmd;
    glDispatchCompute(x, y, z);
}

void rhi_cmd_bind_storage_buffer(RHICmdBuffer *cmd, RHIBuffer buf, u32 binding) {
    (void)cmd;
    extern RHIDevice *g_current_device;
    GLBufferData *bd = (GLBufferData *)rhi_get_resource(g_current_device, buf);
    if (bd) glBindBufferBase(GL_SHADER_STORAGE_BUFFER, binding, bd->gl_buf);
}

void rhi_cmd_memory_barrier(RHICmdBuffer *cmd) {
    (void)cmd;
    glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);
}

void rhi_cmd_transition_depth_to_read(RHICmdBuffer *cmd, RHITexture depth_tex) {
    (void)cmd; (void)depth_tex;
}
